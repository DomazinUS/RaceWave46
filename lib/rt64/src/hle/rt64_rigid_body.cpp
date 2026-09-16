//
// RT64
//

#include "rt64_rigid_body.h"

#include "common/rt64_wr64_lerpgate_trace.h"

#include "../include/rt64_extended_gbi.h"
#include "common/rt64_math.h"

namespace RT64 {
    // RigidBody

    RigidBody::RigidBody() {
        transforms[0] = {};
        transforms[1] = {};
        linearVelocity = { 0.0f, 0.0f, 0.0f };
    }

    // LERPGATE-FIX-R1 (2026-07-29). The AUTO discontinuity test used to divide the
    // current speed by the dot product of the previous and current velocity
    // directions, with that dot floored at 1e-6:
    //
    //     dotCurVel = max(dot(prevDir, curDir), 1e-6)
    //     curVelMag /= dotCurVel
    //     lerpTranslation = (curVelMag < 5) || (curVelMag / prevVelMag) < 10
    //
    // Measured over 520,489 transform evaluations while wandering Sunny Beach, it
    // switched translation interpolation off for 11,264 of them - 2.164%, on 50.7%
    // of all frames. Two things were wrong with it:
    //
    //  * When the object was not moving last frame, prevDir is a normalised
    //    near-zero vector, so the dot is noise and lands on the 1e-6 floor. The
    //    division then inflates the step by a factor of a million. 28.7% of all
    //    gates were this, and their median step was 0.03 units - objects that had
    //    barely moved at all were being classified as teleports. The inflation
    //    also happens BEFORE the "< VelocityTolerance" clause, so that clause
    //    could never protect them.
    //  * A change of DIRECTION was treated as an increase in SPEED. 57.1% of gates
    //    had the dot on its floor, i.e. a reversal, and 55.7% of all gates would
    //    not have fired without the inflation. Inflated magnitudes ran to a median
    //    of 3.4 million and a max of 7.4 billion, which is a divide-by-almost-zero
    //    rather than a measurement. A bounce or a hover is not a teleport.
    //
    // The replacement keeps the intent - do not interpolate across a genuine jump -
    // and drops the degeneracy. A teleport still shows up as a magnitude jump:
    // either as a ratio against a usable previous speed (6.8 -> 5327 units), or,
    // for an object that was sitting still, as an absolute step past
    // JumpTolerance - which is how the recycled buoy arrows are caught. Applied
    // to the recorded gates this rule leaves 29% of them standing, and every one
    // of the 257 fast-object gates that looked like flock mis-pairing goes away.
    //
    // WR64_LERPGATE_FIX=0 restores the original behaviour for A/B.
    void RigidBody::updateLinear(const hlslpp::float4x4 &prevTransform, const hlslpp::float4x4 &curTransform, uint8_t componentInterpolation) {
        if (componentInterpolation == G_EX_COMPONENT_AUTO) {
            const float Epsilon = 1e-6f;
            const float VelocityTolerance = 5.0f; // TODO: Make configurable.
            const float MagnitudeThreshold = 10.0f; // TODO: Make configurable.
            hlslpp::float3 prevPosition = prevTransform[3].xyz;
            hlslpp::float3 curPosition = curTransform[3].xyz;
            hlslpp::float3 curLinearVelocity = curPosition - prevPosition;
            float prevVelMag = hlslpp::length(linearVelocity);
            float curVelMag = hlslpp::length(curLinearVelocity);
            if (wr64LerpGateFixEnabled()) {
                if (curVelMag < VelocityTolerance) {
                    // Barely moved: nothing to be discontinuous about.
                    lerpTranslation = true;
                }
                else if (prevVelMag >= VelocityTolerance) {
                    // Speed did not explode. Direction is deliberately not consulted:
                    // reversing direction is what bouncing and hovering objects do.
                    lerpTranslation = ((curVelMag / prevVelMag) < MagnitudeThreshold);
                }
                else {
                    // R2. No usable history, so a ratio would be meaningless - but
                    // "no history" must not mean "always interpolate". The buoy
                    // direction arrows sit still and are then RECYCLED to the next
                    // buoy, and R1 let that teleport lerp: the arrow visibly flew
                    // from one buoy to the next as you passed it.
                    //
                    // The measured data separates the two cases cleanly. Of the
                    // 5,715 recorded gates with no usable history, the histogram of
                    // the step they took is:
                    //
                    //        0 -   1 : 3224      100 -  200 :    2   <- the gap
                    //        1 -   5 :  850      200 -  400 :   32
                    //        5 -  10 :  172      400 -  800 :   40
                    //       10 -  25 :  226      800 - 1600 :   88
                    //       25 -  50 :  569     1600 - 3200 :  268
                    //       50 - 100 :  121     3200 - 6400 :  117
                    //
                    // 5,065 of them moved under 100 units - real, tiny motion that
                    // should interpolate - and 553 jumped past 200. Only 2 rows in
                    // the entire run land between. JumpTolerance sits in that gap.
                    lerpTranslation = (curVelMag < wr64LerpGateJumpTolerance());
                }
            }
            else {
                float dotCurVel = std::max(hlslpp::dot(linearVelocity / std::max(prevVelMag, Epsilon), curLinearVelocity / std::max(curVelMag, Epsilon))[0], Epsilon);
                curVelMag /= dotCurVel;
                lerpTranslation = (curVelMag < VelocityTolerance) || (curVelMag / std::max(prevVelMag, Epsilon)) < MagnitudeThreshold;
            }
            linearVelocity = curLinearVelocity;
        }
        else {
            lerpTranslation = (componentInterpolation == G_EX_COMPONENT_INTERPOLATE);
            linearVelocity = 0.0f;
        }
    }

    void RigidBody::updateAngular(const hlslpp::float4x4 &prevTransform, const hlslpp::float4x4 &curTransform, uint8_t rotInterpolation, uint8_t scaleInterpolation, uint8_t skewInterpolation) {
        // TODO independent scale and skew auto, currently assumed to match the result of rotation auto calculation.
        // If rotation isn't auto then these default to false for their auto settings.
        lerpScale = (scaleInterpolation == G_EX_COMPONENT_INTERPOLATE);
        lerpSkew = (skewInterpolation == G_EX_COMPONENT_INTERPOLATE);
        
        if (rotInterpolation == G_EX_COMPONENT_AUTO) {
            // Track angular velocity.
            const hlslpp::float3x3 invPrevRotation = hlslpp::inverse(rotationFrom3x3(extract3x3(prevTransform)));
            const hlslpp::float3x3 diffRotation = hlslpp::mul(invPrevRotation, rotationFrom3x3(extract3x3(curTransform)));
            float diffTrace = traceFrom3x3(diffRotation);
            float curAngularVelocity = std::acos((diffTrace - 1.0f) / 2.0f);
            angularVelocity = curAngularVelocity;

            // FIXME: Defaults to always interpolate.
            lerpRotation = true;

            // If scale or skew are also set to auto, use the result of rotation auto calculation for their value as well.
            if (scaleInterpolation == G_EX_COMPONENT_AUTO) {
                lerpScale = lerpRotation;
            }

            if (skewInterpolation == G_EX_COMPONENT_AUTO) {
                lerpSkew = lerpRotation;
            }
        }
        else {
            lerpRotation = (rotInterpolation == G_EX_COMPONENT_INTERPOLATE);
            angularVelocity = 0.0f;
        }
    }

    void RigidBody::updatePerspective(const hlslpp::float4x4 &prevTransform, const hlslpp::float4x4 &curTransform, uint8_t perspInterpolation) {
        // TODO auto perspective interpolation.
        lerpPerspective = (perspInterpolation == G_EX_COMPONENT_INTERPOLATE);
    }

    void RigidBody::updateDecomposition(const hlslpp::float4x4 &curTransform, bool decompose) {
        uint8_t newTransformIndex = transformIndex ^ 1;
        if (decompose) {
            transforms[newTransformIndex] = DecomposedTransform(curTransform);
        } else {
            transforms[newTransformIndex] = DecomposedTransform();
        }
        transformIndex = newTransformIndex;
        lerpDecompose = decompose;
    }

    
    hlslpp::float4x4 RigidBody::lerp(float weight, const hlslpp::float4x4& fallbackPrev, const hlslpp::float4x4& fallbackCur, bool slerp) const {
        // Return a linear component-wise interpolation of the fallback matrices if decomposition is disabled or if either decomposition is invalid.
        if (!lerpDecompose || !transforms[0].valid || !transforms[1].valid) {
            return lerpMatrixComponents(fallbackPrev, fallbackCur, lerpTranslation, lerpRotation, lerpPerspective, weight);
        }

        const DecomposedTransform &prevTransform = transforms[transformIndex ^ 1];
        DecomposedTransform prevTransformCopy = prevTransform;
        const DecomposedTransform &curTransform = transforms[transformIndex];
        DecomposedTransform lerpedTransform;
        
        // When the coordinate system is flipped between transforms due to a different sign in the determinant, we bias the rotation and scale of the
        // previous transform to be similar to the new one by producing a transform that produces an equivalent matrix but with a rotation and scale
        // that are closer to what's intended. This is necessary to improve interpolation between objects that use mirroring in animations.
        if (prevTransformCopy.coordinateFlip != curTransform.coordinateFlip) {
            constexpr float Pi = 3.14159265f;
            const hlslpp::quaternion &prevRot = prevTransformCopy.rotation;
            hlslpp::quaternion xRot = hlslpp::mul(prevTransformCopy.rotation, hlslpp::quaternion::rotation_axis(hlslpp::float3(1.0f, 0.0, 0.0f), Pi));
            hlslpp::quaternion yRot = hlslpp::mul(prevTransformCopy.rotation, hlslpp::quaternion::rotation_axis(hlslpp::float3(0.0f, 1.0, 0.0f), Pi));
            hlslpp::quaternion zRot = hlslpp::mul(prevTransformCopy.rotation, hlslpp::quaternion::rotation_axis(hlslpp::float3(0.0f, 0.0, 1.0f), Pi));
            float rotDotProduct = abs(hlslpp::dot(prevTransformCopy.rotation, curTransform.rotation));
            float xRotDotProduct = abs(hlslpp::dot(xRot, curTransform.rotation));
            float yRotDotProduct = abs(hlslpp::dot(yRot, curTransform.rotation));
            float zRotDotProduct = abs(hlslpp::dot(zRot, curTransform.rotation));
            if (xRotDotProduct > rotDotProduct) {
                prevTransformCopy.rotation = xRot;
                prevTransformCopy.scale = hlslpp::float3(prevTransform.scale.x, -prevTransform.scale.y, -prevTransform.scale.z);
                rotDotProduct = xRotDotProduct;
            }

            if (yRotDotProduct > rotDotProduct) {
                prevTransformCopy.rotation = yRot;
                prevTransformCopy.scale = hlslpp::float3(-prevTransform.scale.x, prevTransform.scale.y, -prevTransform.scale.z);
                rotDotProduct = yRotDotProduct;
            }

            if (zRotDotProduct > rotDotProduct) {
                prevTransformCopy.rotation = zRot;
                prevTransformCopy.scale = hlslpp::float3(-prevTransform.scale.x, -prevTransform.scale.y, prevTransform.scale.z);
            }
        }

        // Lerp the two transforms.
        lerpedTransform = lerpTransforms(prevTransformCopy, curTransform, weight, lerpTranslation, lerpRotation, lerpScale, lerpSkew, lerpPerspective, slerp);

        // Compose a matrix from the resultant transform.
        return recomposeMatrix(lerpedTransform.rotation, lerpedTransform.scale, lerpedTransform.skew, lerpedTransform.translation, lerpedTransform.perspective);
    }
};