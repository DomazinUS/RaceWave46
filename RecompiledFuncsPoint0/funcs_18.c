#include "recomp.h"
#include "funcs.h"

RECOMP_FUNC void func_801E6074(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801E6074: addiu       $sp, $sp, -0x90
    ctx->r29 = ADD32(ctx->r29, -0X90);
    // 0x801E6078: sw          $ra, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r31;
    // 0x801E607C: sw          $s0, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r16;
    // 0x801E6080: lhu         $v0, 0x2($a0)
    ctx->r2 = MEM_HU(ctx->r4, 0X2);
    // 0x801E6084: or          $s0, $a0, $zero
    ctx->r16 = ctx->r4 | 0;
    // 0x801E6088: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x801E608C: beql        $v0, $zero, L_801E60A8
    if (ctx->r2 == 0) {
        // 0x801E6090: lw          $t6, 0x18($s0)
        ctx->r14 = MEM_W(ctx->r16, 0X18);
            goto L_801E60A8;
    }
    goto skip_0;
    // 0x801E6090: lw          $t6, 0x18($s0)
    ctx->r14 = MEM_W(ctx->r16, 0X18);
    skip_0:
    // 0x801E6094: beql        $v0, $at, L_801E61B4
    if (ctx->r2 == ctx->r1) {
        // 0x801E6098: lui         $at, 0x3F80
        ctx->r1 = S32(0X3F80 << 16);
            goto L_801E61B4;
    }
    goto skip_1;
    // 0x801E6098: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    skip_1:
    // 0x801E609C: b           L_801E6298
    // 0x801E60A0: lw          $ra, 0x3C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X3C);
        goto L_801E6298;
    // 0x801E60A0: lw          $ra, 0x3C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X3C);
    // 0x801E60A4: lw          $t6, 0x18($s0)
    ctx->r14 = MEM_W(ctx->r16, 0X18);
L_801E60A8:
    // 0x801E60A8: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x801E60AC: mtc1        $at, $f14
    ctx->f14.u32l = ctx->r1;
    // 0x801E60B0: mtc1        $t6, $f4
    ctx->f4.u32l = ctx->r14;
    // 0x801E60B4: lui         $at, 0x40A0
    ctx->r1 = S32(0X40A0 << 16);
    // 0x801E60B8: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x801E60BC: cvt.s.w     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
    // 0x801E60C0: lui         $at, 0x3FC0
    ctx->r1 = S32(0X3FC0 << 16);
    // 0x801E60C4: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
    // 0x801E60C8: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x801E60CC: mtc1        $at, $f18
    ctx->f18.u32l = ctx->r1;
    // 0x801E60D0: lui         $at, 0x4294
    ctx->r1 = S32(0X4294 << 16);
    // 0x801E60D4: div.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = DIV_S(ctx->f6.fl, ctx->f8.fl);
    // 0x801E60D8: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x801E60DC: lui         $at, 0x4304
    ctx->r1 = S32(0X4304 << 16);
    // 0x801E60E0: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x801E60E4: lui         $at, 0x41A0
    ctx->r1 = S32(0X41A0 << 16);
    // 0x801E60E8: lhu         $t0, 0x4($s0)
    ctx->r8 = MEM_HU(ctx->r16, 0X4);
    // 0x801E60EC: mtc1        $zero, $f0
    ctx->f0.u32l = 0;
    // 0x801E60F0: lui         $t9, 0x801D
    ctx->r25 = S32(0X801D << 16);
    // 0x801E60F4: sll         $t1, $t0, 6
    ctx->r9 = S32(ctx->r8 << 6);
    // 0x801E60F8: mfc1        $a3, $f14
    ctx->r7 = (int32_t)ctx->f14.u32l;
    // 0x801E60FC: mfc1        $a1, $f0
    ctx->r5 = (int32_t)ctx->f0.u32l;
    // 0x801E6100: mfc1        $a2, $f0
    ctx->r6 = (int32_t)ctx->f0.u32l;
    // 0x801E6104: mul.s       $f2, $f10, $f16
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f2.fl = MUL_S(ctx->f10.fl, ctx->f16.fl);
    // 0x801E6108: sub.s       $f12, $f18, $f2
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f12.fl = ctx->f18.fl - ctx->f2.fl;
    // 0x801E610C: mtc1        $at, $f18
    ctx->f18.u32l = ctx->r1;
    // 0x801E6110: lui         $at, 0x42BA
    ctx->r1 = S32(0X42BA << 16);
    // 0x801E6114: mul.s       $f6, $f12, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = MUL_S(ctx->f12.fl, ctx->f4.fl);
    // 0x801E6118: add.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = ctx->f6.fl + ctx->f8.fl;
    // 0x801E611C: mul.s       $f4, $f12, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f4.fl = MUL_S(ctx->f12.fl, ctx->f18.fl);
    // 0x801E6120: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x801E6124: trunc.w.s   $f16, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    ctx->f16.u32l = TRUNC_W_S(ctx->f10.fl);
    // 0x801E6128: add.s       $f8, $f4, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = ctx->f4.fl + ctx->f6.fl;
    // 0x801E612C: mfc1        $v0, $f16
    ctx->r2 = (int32_t)ctx->f16.u32l;
    // 0x801E6130: trunc.w.s   $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.u32l = TRUNC_W_S(ctx->f8.fl);
    // 0x801E6134: mtc1        $v0, $f16
    ctx->f16.u32l = ctx->r2;
    // 0x801E6138: sw          $v0, 0x8($s0)
    MEM_W(0X8, ctx->r16) = ctx->r2;
    // 0x801E613C: mfc1        $v1, $f10
    ctx->r3 = (int32_t)ctx->f10.u32l;
    // 0x801E6140: cvt.s.w     $f18, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    ctx->f18.fl = CVT_S_W(ctx->f16.u32l);
    // 0x801E6144: mtc1        $v1, $f4
    ctx->f4.u32l = ctx->r3;
    // 0x801E6148: sw          $v1, 0xC($s0)
    MEM_W(0XC, ctx->r16) = ctx->r3;
    // 0x801E614C: lw          $t9, -0x1A08($t9)
    ctx->r25 = MEM_W(ctx->r25, -0X1A08);
    // 0x801E6150: cvt.s.w     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
    // 0x801E6154: swc1        $f2, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->f2.u32l;
    // 0x801E6158: addu        $a0, $t9, $t1
    ctx->r4 = ADD32(ctx->r25, ctx->r9);
    // 0x801E615C: addiu       $a0, $a0, 0x900
    ctx->r4 = ADD32(ctx->r4, 0X900);
    // 0x801E6160: swc1        $f18, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->f18.u32l;
    // 0x801E6164: swc1        $f14, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->f14.u32l;
    // 0x801E6168: swc1        $f6, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->f6.u32l;
    // 0x801E616C: swc1        $f0, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->f0.u32l;
    // 0x801E6170: swc1        $f0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->f0.u32l;
    // 0x801E6174: jal         0x80048A88
    // 0x801E6178: swc1        $f0, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f0.u32l;
    func_80048A88(rdram, ctx);
        goto after_0;
    // 0x801E6178: swc1        $f0, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f0.u32l;
    after_0:
    // 0x801E617C: lw          $t2, 0x18($s0)
    ctx->r10 = MEM_W(ctx->r16, 0X18);
    // 0x801E6180: addiu       $t5, $zero, 0x1
    ctx->r13 = ADD32(0, 0X1);
    // 0x801E6184: addiu       $t6, $zero, 0x84
    ctx->r14 = ADD32(0, 0X84);
    // 0x801E6188: addiu       $t3, $t2, 0x1
    ctx->r11 = ADD32(ctx->r10, 0X1);
    // 0x801E618C: slti        $at, $t3, 0x6
    ctx->r1 = SIGNED(ctx->r11) < 0X6 ? 1 : 0;
    // 0x801E6190: bne         $at, $zero, L_801E6294
    if (ctx->r1 != 0) {
        // 0x801E6194: sw          $t3, 0x18($s0)
        MEM_W(0X18, ctx->r16) = ctx->r11;
            goto L_801E6294;
    }
    // 0x801E6194: sw          $t3, 0x18($s0)
    MEM_W(0X18, ctx->r16) = ctx->r11;
    // 0x801E6198: addiu       $t7, $zero, 0x5D
    ctx->r15 = ADD32(0, 0X5D);
    // 0x801E619C: sh          $t5, 0x2($s0)
    MEM_H(0X2, ctx->r16) = ctx->r13;
    // 0x801E61A0: sw          $t6, 0x8($s0)
    MEM_W(0X8, ctx->r16) = ctx->r14;
    // 0x801E61A4: sw          $t7, 0xC($s0)
    MEM_W(0XC, ctx->r16) = ctx->r15;
    // 0x801E61A8: b           L_801E6294
    // 0x801E61AC: sw          $zero, 0x18($s0)
    MEM_W(0X18, ctx->r16) = 0;
        goto L_801E6294;
    // 0x801E61AC: sw          $zero, 0x18($s0)
    MEM_W(0X18, ctx->r16) = 0;
    // 0x801E61B0: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
L_801E61B4:
    // 0x801E61B4: mtc1        $at, $f14
    ctx->f14.u32l = ctx->r1;
    // 0x801E61B8: mtc1        $zero, $f0
    ctx->f0.u32l = 0;
    // 0x801E61BC: lhu         $t0, 0x4($s0)
    ctx->r8 = MEM_HU(ctx->r16, 0X4);
    // 0x801E61C0: swc1        $f14, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->f14.u32l;
    // 0x801E61C4: swc1        $f14, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f14.u32l;
    // 0x801E61C8: swc1        $f0, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->f0.u32l;
    // 0x801E61CC: swc1        $f0, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->f0.u32l;
    // 0x801E61D0: lw          $t1, 0x8($s0)
    ctx->r9 = MEM_W(ctx->r16, 0X8);
    // 0x801E61D4: lui         $t8, 0x801D
    ctx->r24 = S32(0X801D << 16);
    // 0x801E61D8: lw          $t8, -0x1A08($t8)
    ctx->r24 = MEM_W(ctx->r24, -0X1A08);
    // 0x801E61DC: mtc1        $t1, $f8
    ctx->f8.u32l = ctx->r9;
    // 0x801E61E0: sll         $t9, $t0, 6
    ctx->r25 = S32(ctx->r8 << 6);
    // 0x801E61E4: mfc1        $a2, $f0
    ctx->r6 = (int32_t)ctx->f0.u32l;
    // 0x801E61E8: cvt.s.w     $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.fl = CVT_S_W(ctx->f8.u32l);
    // 0x801E61EC: mfc1        $a3, $f0
    ctx->r7 = (int32_t)ctx->f0.u32l;
    // 0x801E61F0: addu        $a0, $t8, $t9
    ctx->r4 = ADD32(ctx->r24, ctx->r25);
    // 0x801E61F4: addiu       $a0, $a0, 0x900
    ctx->r4 = ADD32(ctx->r4, 0X900);
    // 0x801E61F8: addiu       $a1, $sp, 0x50
    ctx->r5 = ADD32(ctx->r29, 0X50);
    // 0x801E61FC: swc1        $f10, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->f10.u32l;
    // 0x801E6200: lw          $t2, 0xC($s0)
    ctx->r10 = MEM_W(ctx->r16, 0XC);
    // 0x801E6204: swc1        $f0, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->f0.u32l;
    // 0x801E6208: mtc1        $t2, $f16
    ctx->f16.u32l = ctx->r10;
    // 0x801E620C: nop

    // 0x801E6210: cvt.s.w     $f18, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    ctx->f18.fl = CVT_S_W(ctx->f16.u32l);
    // 0x801E6214: jal         0x80048854
    // 0x801E6218: swc1        $f18, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->f18.u32l;
    SysUtils_MatrixLookAt(rdram, ctx);
        goto after_1;
    // 0x801E6218: swc1        $f18, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->f18.u32l;
    after_1:
    // 0x801E621C: lw          $t3, 0x18($s0)
    ctx->r11 = MEM_W(ctx->r16, 0X18);
    // 0x801E6220: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x801E6224: addiu       $at, $zero, 0x4
    ctx->r1 = ADD32(0, 0X4);
    // 0x801E6228: addiu       $t4, $t3, 0x1
    ctx->r12 = ADD32(ctx->r11, 0X1);
    // 0x801E622C: sw          $t4, 0x18($s0)
    MEM_W(0X18, ctx->r16) = ctx->r12;
    // 0x801E6230: lw          $v0, -0x19F8($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X19F8);
    // 0x801E6234: bne         $v0, $at, L_801E6258
    if (ctx->r2 != ctx->r1) {
        // 0x801E6238: slti        $at, $t4, 0xB
        ctx->r1 = SIGNED(ctx->r12) < 0XB ? 1 : 0;
            goto L_801E6258;
    }
    // 0x801E6238: slti        $at, $t4, 0xB
    ctx->r1 = SIGNED(ctx->r12) < 0XB ? 1 : 0;
    // 0x801E623C: bne         $at, $zero, L_801E6294
    if (ctx->r1 != 0) {
        // 0x801E6240: addiu       $a0, $zero, 0x2
        ctx->r4 = ADD32(0, 0X2);
            goto L_801E6294;
    }
    // 0x801E6240: addiu       $a0, $zero, 0x2
    ctx->r4 = ADD32(0, 0X2);
    // 0x801E6244: sh          $zero, 0x0($s0)
    MEM_H(0X0, ctx->r16) = 0;
    // 0x801E6248: jal         0x801E6A4C
    // 0x801E624C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_801E6A4C(rdram, ctx);
        goto after_2;
    // 0x801E624C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_2:
    // 0x801E6250: b           L_801E6298
    // 0x801E6254: lw          $ra, 0x3C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X3C);
        goto L_801E6298;
    // 0x801E6254: lw          $ra, 0x3C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X3C);
L_801E6258:
    // 0x801E6258: bnel        $v0, $zero, L_801E6298
    if (ctx->r2 != 0) {
        // 0x801E625C: lw          $ra, 0x3C($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X3C);
            goto L_801E6298;
    }
    goto skip_2;
    // 0x801E625C: lw          $ra, 0x3C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X3C);
    skip_2:
    // 0x801E6260: lw          $t6, 0x18($s0)
    ctx->r14 = MEM_W(ctx->r16, 0X18);
    // 0x801E6264: lui         $t7, 0x801C
    ctx->r15 = S32(0X801C << 16);
    // 0x801E6268: slti        $at, $t6, 0xB
    ctx->r1 = SIGNED(ctx->r14) < 0XB ? 1 : 0;
    // 0x801E626C: bnel        $at, $zero, L_801E6298
    if (ctx->r1 != 0) {
        // 0x801E6270: lw          $ra, 0x3C($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X3C);
            goto L_801E6298;
    }
    goto skip_3;
    // 0x801E6270: lw          $ra, 0x3C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X3C);
    skip_3:
    // 0x801E6274: sh          $zero, 0x0($s0)
    MEM_H(0X0, ctx->r16) = 0;
    // 0x801E6278: lw          $t7, 0x2650($t7)
    ctx->r15 = MEM_W(ctx->r15, 0X2650);
    // 0x801E627C: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x801E6280: addiu       $a0, $zero, 0x2
    ctx->r4 = ADD32(0, 0X2);
    // 0x801E6284: bnel        $t7, $at, L_801E6298
    if (ctx->r15 != ctx->r1) {
        // 0x801E6288: lw          $ra, 0x3C($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X3C);
            goto L_801E6298;
    }
    goto skip_4;
    // 0x801E6288: lw          $ra, 0x3C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X3C);
    skip_4:
    // 0x801E628C: jal         0x801E6A4C
    // 0x801E6290: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    func_801E6A4C(rdram, ctx);
        goto after_3;
    // 0x801E6290: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    after_3:
L_801E6294:
    // 0x801E6294: lw          $ra, 0x3C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X3C);
L_801E6298:
    // 0x801E6298: lw          $s0, 0x38($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X38);
    // 0x801E629C: addiu       $sp, $sp, 0x90
    ctx->r29 = ADD32(ctx->r29, 0X90);
    // 0x801E62A0: jr          $ra
    // 0x801E62A4: nop

    return;
    // 0x801E62A4: nop

;}
RECOMP_FUNC void func_801E62A8(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801E62A8: addiu       $sp, $sp, -0x90
    ctx->r29 = ADD32(ctx->r29, -0X90);
    // 0x801E62AC: sw          $ra, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r31;
    // 0x801E62B0: sw          $s0, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r16;
    // 0x801E62B4: lhu         $v0, 0x2($a0)
    ctx->r2 = MEM_HU(ctx->r4, 0X2);
    // 0x801E62B8: or          $s0, $a0, $zero
    ctx->r16 = ctx->r4 | 0;
    // 0x801E62BC: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x801E62C0: beql        $v0, $zero, L_801E62DC
    if (ctx->r2 == 0) {
        // 0x801E62C4: lw          $t6, 0x18($s0)
        ctx->r14 = MEM_W(ctx->r16, 0X18);
            goto L_801E62DC;
    }
    goto skip_0;
    // 0x801E62C4: lw          $t6, 0x18($s0)
    ctx->r14 = MEM_W(ctx->r16, 0X18);
    skip_0:
    // 0x801E62C8: beql        $v0, $at, L_801E6660
    if (ctx->r2 == ctx->r1) {
        // 0x801E62CC: lui         $at, 0x3F80
        ctx->r1 = S32(0X3F80 << 16);
            goto L_801E6660;
    }
    goto skip_1;
    // 0x801E62CC: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    skip_1:
    // 0x801E62D0: b           L_801E66E4
    // 0x801E62D4: lw          $ra, 0x3C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X3C);
        goto L_801E66E4;
    // 0x801E62D4: lw          $ra, 0x3C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X3C);
    // 0x801E62D8: lw          $t6, 0x18($s0)
    ctx->r14 = MEM_W(ctx->r16, 0X18);
L_801E62DC:
    // 0x801E62DC: lui         $at, 0x40A0
    ctx->r1 = S32(0X40A0 << 16);
    // 0x801E62E0: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x801E62E4: mtc1        $t6, $f4
    ctx->f4.u32l = ctx->r14;
    // 0x801E62E8: lui         $at, 0x3FC0
    ctx->r1 = S32(0X3FC0 << 16);
    // 0x801E62EC: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
    // 0x801E62F0: cvt.s.w     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
    // 0x801E62F4: lw          $t7, 0x28($s0)
    ctx->r15 = MEM_W(ctx->r16, 0X28);
    // 0x801E62F8: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x801E62FC: div.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = DIV_S(ctx->f6.fl, ctx->f8.fl);
    // 0x801E6300: mul.s       $f2, $f10, $f16
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f2.fl = MUL_S(ctx->f10.fl, ctx->f16.fl);
    // 0x801E6304: beql        $t7, $zero, L_801E6460
    if (ctx->r15 == 0) {
        // 0x801E6308: mtc1        $at, $f16
        ctx->f16.u32l = ctx->r1;
            goto L_801E6460;
    }
    goto skip_2;
    // 0x801E6308: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
    skip_2:
    // 0x801E630C: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x801E6310: mtc1        $at, $f18
    ctx->f18.u32l = ctx->r1;
    // 0x801E6314: lui         $at, 0x42CC
    ctx->r1 = S32(0X42CC << 16);
    // 0x801E6318: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x801E631C: sub.s       $f0, $f18, $f2
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f0.fl = ctx->f18.fl - ctx->f2.fl;
    // 0x801E6320: lui         $at, 0x42DC
    ctx->r1 = S32(0X42DC << 16);
    // 0x801E6324: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x801E6328: addiu       $t9, $zero, 0x1
    ctx->r25 = ADD32(0, 0X1);
    // 0x801E632C: mul.s       $f6, $f0, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = MUL_S(ctx->f0.fl, ctx->f4.fl);
    // 0x801E6330: lui         $at, 0x4F00
    ctx->r1 = S32(0X4F00 << 16);
    // 0x801E6334: add.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = ctx->f6.fl + ctx->f8.fl;
    // 0x801E6338: cfc1        $t8, $FpcCsr
    ctx->r24 = get_cop1_cs();
    // 0x801E633C: ctc1        $t9, $FpcCsr
    set_cop1_cs(ctx->r25);
    // 0x801E6340: nop

    // 0x801E6344: cvt.w.s     $f16, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    ctx->f16.u32l = CVT_W_S(ctx->f10.fl);
    // 0x801E6348: cfc1        $t9, $FpcCsr
    ctx->r25 = get_cop1_cs();
    // 0x801E634C: nop

    // 0x801E6350: andi        $t9, $t9, 0x78
    ctx->r25 = ctx->r25 & 0X78;
    // 0x801E6354: beql        $t9, $zero, L_801E63A4
    if (ctx->r25 == 0) {
        // 0x801E6358: mfc1        $t9, $f16
        ctx->r25 = (int32_t)ctx->f16.u32l;
            goto L_801E63A4;
    }
    goto skip_3;
    // 0x801E6358: mfc1        $t9, $f16
    ctx->r25 = (int32_t)ctx->f16.u32l;
    skip_3:
    // 0x801E635C: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
    // 0x801E6360: addiu       $t9, $zero, 0x1
    ctx->r25 = ADD32(0, 0X1);
    // 0x801E6364: sub.s       $f16, $f10, $f16
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f16.fl = ctx->f10.fl - ctx->f16.fl;
    // 0x801E6368: ctc1        $t9, $FpcCsr
    set_cop1_cs(ctx->r25);
    // 0x801E636C: nop

    // 0x801E6370: cvt.w.s     $f16, $f16
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 16);
    ctx->f16.u32l = CVT_W_S(ctx->f16.fl);
    // 0x801E6374: cfc1        $t9, $FpcCsr
    ctx->r25 = get_cop1_cs();
    // 0x801E6378: nop

    // 0x801E637C: andi        $t9, $t9, 0x78
    ctx->r25 = ctx->r25 & 0X78;
    // 0x801E6380: bne         $t9, $zero, L_801E6398
    if (ctx->r25 != 0) {
        // 0x801E6384: nop
    
            goto L_801E6398;
    }
    // 0x801E6384: nop

    // 0x801E6388: mfc1        $t9, $f16
    ctx->r25 = (int32_t)ctx->f16.u32l;
    // 0x801E638C: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x801E6390: b           L_801E63B0
    // 0x801E6394: or          $t9, $t9, $at
    ctx->r25 = ctx->r25 | ctx->r1;
        goto L_801E63B0;
    // 0x801E6394: or          $t9, $t9, $at
    ctx->r25 = ctx->r25 | ctx->r1;
L_801E6398:
    // 0x801E6398: b           L_801E63B0
    // 0x801E639C: addiu       $t9, $zero, -0x1
    ctx->r25 = ADD32(0, -0X1);
        goto L_801E63B0;
    // 0x801E639C: addiu       $t9, $zero, -0x1
    ctx->r25 = ADD32(0, -0X1);
    // 0x801E63A0: mfc1        $t9, $f16
    ctx->r25 = (int32_t)ctx->f16.u32l;
L_801E63A4:
    // 0x801E63A4: nop

    // 0x801E63A8: bltz        $t9, L_801E6398
    if (SIGNED(ctx->r25) < 0) {
        // 0x801E63AC: nop
    
            goto L_801E6398;
    }
    // 0x801E63AC: nop

L_801E63B0:
    // 0x801E63B0: lui         $at, 0x4170
    ctx->r1 = S32(0X4170 << 16);
    // 0x801E63B4: ctc1        $t8, $FpcCsr
    set_cop1_cs(ctx->r24);
    // 0x801E63B8: mtc1        $at, $f18
    ctx->f18.u32l = ctx->r1;
    // 0x801E63BC: lui         $at, 0x42BA
    ctx->r1 = S32(0X42BA << 16);
    // 0x801E63C0: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x801E63C4: mul.s       $f4, $f0, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f4.fl = MUL_S(ctx->f0.fl, ctx->f18.fl);
    // 0x801E63C8: addiu       $t1, $zero, 0x1
    ctx->r9 = ADD32(0, 0X1);
    // 0x801E63CC: sw          $t9, 0x8($s0)
    MEM_W(0X8, ctx->r16) = ctx->r25;
    // 0x801E63D0: lui         $at, 0x4F00
    ctx->r1 = S32(0X4F00 << 16);
    // 0x801E63D4: add.s       $f8, $f4, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = ctx->f4.fl + ctx->f6.fl;
    // 0x801E63D8: cfc1        $t0, $FpcCsr
    ctx->r8 = get_cop1_cs();
    // 0x801E63DC: ctc1        $t1, $FpcCsr
    set_cop1_cs(ctx->r9);
    // 0x801E63E0: nop

    // 0x801E63E4: cvt.w.s     $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.u32l = CVT_W_S(ctx->f8.fl);
    // 0x801E63E8: cfc1        $t1, $FpcCsr
    ctx->r9 = get_cop1_cs();
    // 0x801E63EC: nop

    // 0x801E63F0: andi        $t1, $t1, 0x78
    ctx->r9 = ctx->r9 & 0X78;
    // 0x801E63F4: beql        $t1, $zero, L_801E6444
    if (ctx->r9 == 0) {
        // 0x801E63F8: mfc1        $t1, $f10
        ctx->r9 = (int32_t)ctx->f10.u32l;
            goto L_801E6444;
    }
    goto skip_4;
    // 0x801E63F8: mfc1        $t1, $f10
    ctx->r9 = (int32_t)ctx->f10.u32l;
    skip_4:
    // 0x801E63FC: mtc1        $at, $f10
    ctx->f10.u32l = ctx->r1;
    // 0x801E6400: addiu       $t1, $zero, 0x1
    ctx->r9 = ADD32(0, 0X1);
    // 0x801E6404: sub.s       $f10, $f8, $f10
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f10.fl = ctx->f8.fl - ctx->f10.fl;
    // 0x801E6408: ctc1        $t1, $FpcCsr
    set_cop1_cs(ctx->r9);
    // 0x801E640C: nop

    // 0x801E6410: cvt.w.s     $f10, $f10
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 10);
    ctx->f10.u32l = CVT_W_S(ctx->f10.fl);
    // 0x801E6414: cfc1        $t1, $FpcCsr
    ctx->r9 = get_cop1_cs();
    // 0x801E6418: nop

    // 0x801E641C: andi        $t1, $t1, 0x78
    ctx->r9 = ctx->r9 & 0X78;
    // 0x801E6420: bne         $t1, $zero, L_801E6438
    if (ctx->r9 != 0) {
        // 0x801E6424: nop
    
            goto L_801E6438;
    }
    // 0x801E6424: nop

    // 0x801E6428: mfc1        $t1, $f10
    ctx->r9 = (int32_t)ctx->f10.u32l;
    // 0x801E642C: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x801E6430: b           L_801E6450
    // 0x801E6434: or          $t1, $t1, $at
    ctx->r9 = ctx->r9 | ctx->r1;
        goto L_801E6450;
    // 0x801E6434: or          $t1, $t1, $at
    ctx->r9 = ctx->r9 | ctx->r1;
L_801E6438:
    // 0x801E6438: b           L_801E6450
    // 0x801E643C: addiu       $t1, $zero, -0x1
    ctx->r9 = ADD32(0, -0X1);
        goto L_801E6450;
    // 0x801E643C: addiu       $t1, $zero, -0x1
    ctx->r9 = ADD32(0, -0X1);
    // 0x801E6440: mfc1        $t1, $f10
    ctx->r9 = (int32_t)ctx->f10.u32l;
L_801E6444:
    // 0x801E6444: nop

    // 0x801E6448: bltz        $t1, L_801E6438
    if (SIGNED(ctx->r9) < 0) {
        // 0x801E644C: nop
    
            goto L_801E6438;
    }
    // 0x801E644C: nop

L_801E6450:
    // 0x801E6450: ctc1        $t0, $FpcCsr
    set_cop1_cs(ctx->r8);
    // 0x801E6454: b           L_801E65A8
    // 0x801E6458: sw          $t1, 0xC($s0)
    MEM_W(0XC, ctx->r16) = ctx->r9;
        goto L_801E65A8;
    // 0x801E6458: sw          $t1, 0xC($s0)
    MEM_W(0XC, ctx->r16) = ctx->r9;
    // 0x801E645C: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
L_801E6460:
    // 0x801E6460: lui         $at, 0x4218
    ctx->r1 = S32(0X4218 << 16);
    // 0x801E6464: mtc1        $at, $f18
    ctx->f18.u32l = ctx->r1;
    // 0x801E6468: sub.s       $f0, $f16, $f2
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f0.fl = ctx->f16.fl - ctx->f2.fl;
    // 0x801E646C: lui         $at, 0x432C
    ctx->r1 = S32(0X432C << 16);
    // 0x801E6470: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x801E6474: addiu       $t3, $zero, 0x1
    ctx->r11 = ADD32(0, 0X1);
    // 0x801E6478: mul.s       $f4, $f0, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f4.fl = MUL_S(ctx->f0.fl, ctx->f18.fl);
    // 0x801E647C: lui         $at, 0x4F00
    ctx->r1 = S32(0X4F00 << 16);
    // 0x801E6480: add.s       $f8, $f4, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = ctx->f4.fl + ctx->f6.fl;
    // 0x801E6484: cfc1        $t2, $FpcCsr
    ctx->r10 = get_cop1_cs();
    // 0x801E6488: ctc1        $t3, $FpcCsr
    set_cop1_cs(ctx->r11);
    // 0x801E648C: nop

    // 0x801E6490: cvt.w.s     $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.u32l = CVT_W_S(ctx->f8.fl);
    // 0x801E6494: cfc1        $t3, $FpcCsr
    ctx->r11 = get_cop1_cs();
    // 0x801E6498: nop

    // 0x801E649C: andi        $t3, $t3, 0x78
    ctx->r11 = ctx->r11 & 0X78;
    // 0x801E64A0: beql        $t3, $zero, L_801E64F0
    if (ctx->r11 == 0) {
        // 0x801E64A4: mfc1        $t3, $f10
        ctx->r11 = (int32_t)ctx->f10.u32l;
            goto L_801E64F0;
    }
    goto skip_5;
    // 0x801E64A4: mfc1        $t3, $f10
    ctx->r11 = (int32_t)ctx->f10.u32l;
    skip_5:
    // 0x801E64A8: mtc1        $at, $f10
    ctx->f10.u32l = ctx->r1;
    // 0x801E64AC: addiu       $t3, $zero, 0x1
    ctx->r11 = ADD32(0, 0X1);
    // 0x801E64B0: sub.s       $f10, $f8, $f10
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f10.fl = ctx->f8.fl - ctx->f10.fl;
    // 0x801E64B4: ctc1        $t3, $FpcCsr
    set_cop1_cs(ctx->r11);
    // 0x801E64B8: nop

    // 0x801E64BC: cvt.w.s     $f10, $f10
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 10);
    ctx->f10.u32l = CVT_W_S(ctx->f10.fl);
    // 0x801E64C0: cfc1        $t3, $FpcCsr
    ctx->r11 = get_cop1_cs();
    // 0x801E64C4: nop

    // 0x801E64C8: andi        $t3, $t3, 0x78
    ctx->r11 = ctx->r11 & 0X78;
    // 0x801E64CC: bne         $t3, $zero, L_801E64E4
    if (ctx->r11 != 0) {
        // 0x801E64D0: nop
    
            goto L_801E64E4;
    }
    // 0x801E64D0: nop

    // 0x801E64D4: mfc1        $t3, $f10
    ctx->r11 = (int32_t)ctx->f10.u32l;
    // 0x801E64D8: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x801E64DC: b           L_801E64FC
    // 0x801E64E0: or          $t3, $t3, $at
    ctx->r11 = ctx->r11 | ctx->r1;
        goto L_801E64FC;
    // 0x801E64E0: or          $t3, $t3, $at
    ctx->r11 = ctx->r11 | ctx->r1;
L_801E64E4:
    // 0x801E64E4: b           L_801E64FC
    // 0x801E64E8: addiu       $t3, $zero, -0x1
    ctx->r11 = ADD32(0, -0X1);
        goto L_801E64FC;
    // 0x801E64E8: addiu       $t3, $zero, -0x1
    ctx->r11 = ADD32(0, -0X1);
    // 0x801E64EC: mfc1        $t3, $f10
    ctx->r11 = (int32_t)ctx->f10.u32l;
L_801E64F0:
    // 0x801E64F0: nop

    // 0x801E64F4: bltz        $t3, L_801E64E4
    if (SIGNED(ctx->r11) < 0) {
        // 0x801E64F8: nop
    
            goto L_801E64E4;
    }
    // 0x801E64F8: nop

L_801E64FC:
    // 0x801E64FC: lui         $at, 0x41A0
    ctx->r1 = S32(0X41A0 << 16);
    // 0x801E6500: ctc1        $t2, $FpcCsr
    set_cop1_cs(ctx->r10);
    // 0x801E6504: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
    // 0x801E6508: lui         $at, 0x42BA
    ctx->r1 = S32(0X42BA << 16);
    // 0x801E650C: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x801E6510: mul.s       $f18, $f0, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f18.fl = MUL_S(ctx->f0.fl, ctx->f16.fl);
    // 0x801E6514: addiu       $t5, $zero, 0x1
    ctx->r13 = ADD32(0, 0X1);
    // 0x801E6518: sw          $t3, 0x8($s0)
    MEM_W(0X8, ctx->r16) = ctx->r11;
    // 0x801E651C: lui         $at, 0x4F00
    ctx->r1 = S32(0X4F00 << 16);
    // 0x801E6520: add.s       $f6, $f18, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = ctx->f18.fl + ctx->f4.fl;
    // 0x801E6524: cfc1        $t4, $FpcCsr
    ctx->r12 = get_cop1_cs();
    // 0x801E6528: ctc1        $t5, $FpcCsr
    set_cop1_cs(ctx->r13);
    // 0x801E652C: nop

    // 0x801E6530: cvt.w.s     $f8, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    ctx->f8.u32l = CVT_W_S(ctx->f6.fl);
    // 0x801E6534: cfc1        $t5, $FpcCsr
    ctx->r13 = get_cop1_cs();
    // 0x801E6538: nop

    // 0x801E653C: andi        $t5, $t5, 0x78
    ctx->r13 = ctx->r13 & 0X78;
    // 0x801E6540: beql        $t5, $zero, L_801E6590
    if (ctx->r13 == 0) {
        // 0x801E6544: mfc1        $t5, $f8
        ctx->r13 = (int32_t)ctx->f8.u32l;
            goto L_801E6590;
    }
    goto skip_6;
    // 0x801E6544: mfc1        $t5, $f8
    ctx->r13 = (int32_t)ctx->f8.u32l;
    skip_6:
    // 0x801E6548: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x801E654C: addiu       $t5, $zero, 0x1
    ctx->r13 = ADD32(0, 0X1);
    // 0x801E6550: sub.s       $f8, $f6, $f8
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f8.fl = ctx->f6.fl - ctx->f8.fl;
    // 0x801E6554: ctc1        $t5, $FpcCsr
    set_cop1_cs(ctx->r13);
    // 0x801E6558: nop

    // 0x801E655C: cvt.w.s     $f8, $f8
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 8);
    ctx->f8.u32l = CVT_W_S(ctx->f8.fl);
    // 0x801E6560: cfc1        $t5, $FpcCsr
    ctx->r13 = get_cop1_cs();
    // 0x801E6564: nop

    // 0x801E6568: andi        $t5, $t5, 0x78
    ctx->r13 = ctx->r13 & 0X78;
    // 0x801E656C: bne         $t5, $zero, L_801E6584
    if (ctx->r13 != 0) {
        // 0x801E6570: nop
    
            goto L_801E6584;
    }
    // 0x801E6570: nop

    // 0x801E6574: mfc1        $t5, $f8
    ctx->r13 = (int32_t)ctx->f8.u32l;
    // 0x801E6578: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x801E657C: b           L_801E659C
    // 0x801E6580: or          $t5, $t5, $at
    ctx->r13 = ctx->r13 | ctx->r1;
        goto L_801E659C;
    // 0x801E6580: or          $t5, $t5, $at
    ctx->r13 = ctx->r13 | ctx->r1;
L_801E6584:
    // 0x801E6584: b           L_801E659C
    // 0x801E6588: addiu       $t5, $zero, -0x1
    ctx->r13 = ADD32(0, -0X1);
        goto L_801E659C;
    // 0x801E6588: addiu       $t5, $zero, -0x1
    ctx->r13 = ADD32(0, -0X1);
    // 0x801E658C: mfc1        $t5, $f8
    ctx->r13 = (int32_t)ctx->f8.u32l;
L_801E6590:
    // 0x801E6590: nop

    // 0x801E6594: bltz        $t5, L_801E6584
    if (SIGNED(ctx->r13) < 0) {
        // 0x801E6598: nop
    
            goto L_801E6584;
    }
    // 0x801E6598: nop

L_801E659C:
    // 0x801E659C: ctc1        $t4, $FpcCsr
    set_cop1_cs(ctx->r12);
    // 0x801E65A0: sw          $t5, 0xC($s0)
    MEM_W(0XC, ctx->r16) = ctx->r13;
    // 0x801E65A4: nop

L_801E65A8:
    // 0x801E65A8: mtc1        $zero, $f0
    ctx->f0.u32l = 0;
    // 0x801E65AC: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x801E65B0: mtc1        $at, $f12
    ctx->f12.u32l = ctx->r1;
    // 0x801E65B4: lhu         $t7, 0x4($s0)
    ctx->r15 = MEM_HU(ctx->r16, 0X4);
    // 0x801E65B8: swc1        $f0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->f0.u32l;
    // 0x801E65BC: swc1        $f0, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f0.u32l;
    // 0x801E65C0: swc1        $f12, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->f12.u32l;
    // 0x801E65C4: lw          $t9, 0x8($s0)
    ctx->r25 = MEM_W(ctx->r16, 0X8);
    // 0x801E65C8: lui         $t6, 0x801D
    ctx->r14 = S32(0X801D << 16);
    // 0x801E65CC: lw          $t6, -0x1A08($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X1A08);
    // 0x801E65D0: mtc1        $t9, $f10
    ctx->f10.u32l = ctx->r25;
    // 0x801E65D4: sll         $t8, $t7, 6
    ctx->r24 = S32(ctx->r15 << 6);
    // 0x801E65D8: mfc1        $a1, $f0
    ctx->r5 = (int32_t)ctx->f0.u32l;
    // 0x801E65DC: cvt.s.w     $f16, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    ctx->f16.fl = CVT_S_W(ctx->f10.u32l);
    // 0x801E65E0: mfc1        $a2, $f0
    ctx->r6 = (int32_t)ctx->f0.u32l;
    // 0x801E65E4: mfc1        $a3, $f12
    ctx->r7 = (int32_t)ctx->f12.u32l;
    // 0x801E65E8: addu        $a0, $t6, $t8
    ctx->r4 = ADD32(ctx->r14, ctx->r24);
    // 0x801E65EC: addiu       $a0, $a0, 0x900
    ctx->r4 = ADD32(ctx->r4, 0X900);
    // 0x801E65F0: swc1        $f16, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->f16.u32l;
    // 0x801E65F4: lw          $t0, 0xC($s0)
    ctx->r8 = MEM_W(ctx->r16, 0XC);
    // 0x801E65F8: swc1        $f2, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->f2.u32l;
    // 0x801E65FC: swc1        $f0, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->f0.u32l;
    // 0x801E6600: mtc1        $t0, $f18
    ctx->f18.u32l = ctx->r8;
    // 0x801E6604: nop

    // 0x801E6608: cvt.s.w     $f4, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    ctx->f4.fl = CVT_S_W(ctx->f18.u32l);
    // 0x801E660C: jal         0x80048A88
    // 0x801E6610: swc1        $f4, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->f4.u32l;
    func_80048A88(rdram, ctx);
        goto after_0;
    // 0x801E6610: swc1        $f4, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->f4.u32l;
    after_0:
    // 0x801E6614: lw          $t1, 0x18($s0)
    ctx->r9 = MEM_W(ctx->r16, 0X18);
    // 0x801E6618: addiu       $t8, $zero, 0x5D
    ctx->r24 = ADD32(0, 0X5D);
    // 0x801E661C: addiu       $t2, $t1, 0x1
    ctx->r10 = ADD32(ctx->r9, 0X1);
    // 0x801E6620: slti        $at, $t2, 0x6
    ctx->r1 = SIGNED(ctx->r10) < 0X6 ? 1 : 0;
    // 0x801E6624: bne         $at, $zero, L_801E66E0
    if (ctx->r1 != 0) {
        // 0x801E6628: sw          $t2, 0x18($s0)
        MEM_W(0X18, ctx->r16) = ctx->r10;
            goto L_801E66E0;
    }
    // 0x801E6628: sw          $t2, 0x18($s0)
    MEM_W(0X18, ctx->r16) = ctx->r10;
    // 0x801E662C: lw          $t5, 0x28($s0)
    ctx->r13 = MEM_W(ctx->r16, 0X28);
    // 0x801E6630: addiu       $t4, $zero, 0x1
    ctx->r12 = ADD32(0, 0X1);
    // 0x801E6634: sh          $t4, 0x2($s0)
    MEM_H(0X2, ctx->r16) = ctx->r12;
    // 0x801E6638: beq         $t5, $zero, L_801E664C
    if (ctx->r13 == 0) {
        // 0x801E663C: addiu       $t6, $zero, 0xAC
        ctx->r14 = ADD32(0, 0XAC);
            goto L_801E664C;
    }
    // 0x801E663C: addiu       $t6, $zero, 0xAC
    ctx->r14 = ADD32(0, 0XAC);
    // 0x801E6640: addiu       $t7, $zero, 0x6E
    ctx->r15 = ADD32(0, 0X6E);
    // 0x801E6644: b           L_801E6650
    // 0x801E6648: sw          $t7, 0x8($s0)
    MEM_W(0X8, ctx->r16) = ctx->r15;
        goto L_801E6650;
    // 0x801E6648: sw          $t7, 0x8($s0)
    MEM_W(0X8, ctx->r16) = ctx->r15;
L_801E664C:
    // 0x801E664C: sw          $t6, 0x8($s0)
    MEM_W(0X8, ctx->r16) = ctx->r14;
L_801E6650:
    // 0x801E6650: sw          $t8, 0xC($s0)
    MEM_W(0XC, ctx->r16) = ctx->r24;
    // 0x801E6654: b           L_801E66E0
    // 0x801E6658: sw          $zero, 0x18($s0)
    MEM_W(0X18, ctx->r16) = 0;
        goto L_801E66E0;
    // 0x801E6658: sw          $zero, 0x18($s0)
    MEM_W(0X18, ctx->r16) = 0;
    // 0x801E665C: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
L_801E6660:
    // 0x801E6660: mtc1        $at, $f12
    ctx->f12.u32l = ctx->r1;
    // 0x801E6664: mtc1        $zero, $f0
    ctx->f0.u32l = 0;
    // 0x801E6668: lhu         $t0, 0x4($s0)
    ctx->r8 = MEM_HU(ctx->r16, 0X4);
    // 0x801E666C: swc1        $f12, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->f12.u32l;
    // 0x801E6670: swc1        $f12, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f12.u32l;
    // 0x801E6674: swc1        $f0, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->f0.u32l;
    // 0x801E6678: swc1        $f0, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->f0.u32l;
    // 0x801E667C: lw          $t2, 0x8($s0)
    ctx->r10 = MEM_W(ctx->r16, 0X8);
    // 0x801E6680: lui         $t9, 0x801D
    ctx->r25 = S32(0X801D << 16);
    // 0x801E6684: lw          $t9, -0x1A08($t9)
    ctx->r25 = MEM_W(ctx->r25, -0X1A08);
    // 0x801E6688: mtc1        $t2, $f6
    ctx->f6.u32l = ctx->r10;
    // 0x801E668C: sll         $t1, $t0, 6
    ctx->r9 = S32(ctx->r8 << 6);
    // 0x801E6690: mfc1        $a2, $f0
    ctx->r6 = (int32_t)ctx->f0.u32l;
    // 0x801E6694: cvt.s.w     $f8, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    ctx->f8.fl = CVT_S_W(ctx->f6.u32l);
    // 0x801E6698: mfc1        $a3, $f0
    ctx->r7 = (int32_t)ctx->f0.u32l;
    // 0x801E669C: addu        $a0, $t9, $t1
    ctx->r4 = ADD32(ctx->r25, ctx->r9);
    // 0x801E66A0: addiu       $a0, $a0, 0x900
    ctx->r4 = ADD32(ctx->r4, 0X900);
    // 0x801E66A4: addiu       $a1, $sp, 0x50
    ctx->r5 = ADD32(ctx->r29, 0X50);
    // 0x801E66A8: swc1        $f8, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->f8.u32l;
    // 0x801E66AC: lw          $t3, 0xC($s0)
    ctx->r11 = MEM_W(ctx->r16, 0XC);
    // 0x801E66B0: swc1        $f0, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->f0.u32l;
    // 0x801E66B4: mtc1        $t3, $f10
    ctx->f10.u32l = ctx->r11;
    // 0x801E66B8: nop

    // 0x801E66BC: cvt.s.w     $f16, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    ctx->f16.fl = CVT_S_W(ctx->f10.u32l);
    // 0x801E66C0: jal         0x80048854
    // 0x801E66C4: swc1        $f16, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->f16.u32l;
    SysUtils_MatrixLookAt(rdram, ctx);
        goto after_1;
    // 0x801E66C4: swc1        $f16, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->f16.u32l;
    after_1:
    // 0x801E66C8: lw          $t4, 0x18($s0)
    ctx->r12 = MEM_W(ctx->r16, 0X18);
    // 0x801E66CC: addiu       $t5, $t4, 0x1
    ctx->r13 = ADD32(ctx->r12, 0X1);
    // 0x801E66D0: slti        $at, $t5, 0x1F
    ctx->r1 = SIGNED(ctx->r13) < 0X1F ? 1 : 0;
    // 0x801E66D4: bne         $at, $zero, L_801E66E0
    if (ctx->r1 != 0) {
        // 0x801E66D8: sw          $t5, 0x18($s0)
        MEM_W(0X18, ctx->r16) = ctx->r13;
            goto L_801E66E0;
    }
    // 0x801E66D8: sw          $t5, 0x18($s0)
    MEM_W(0X18, ctx->r16) = ctx->r13;
    // 0x801E66DC: sh          $zero, 0x0($s0)
    MEM_H(0X0, ctx->r16) = 0;
L_801E66E0:
    // 0x801E66E0: lw          $ra, 0x3C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X3C);
L_801E66E4:
    // 0x801E66E4: lw          $s0, 0x38($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X38);
    // 0x801E66E8: addiu       $sp, $sp, 0x90
    ctx->r29 = ADD32(ctx->r29, 0X90);
    // 0x801E66EC: jr          $ra
    // 0x801E66F0: nop

    return;
    // 0x801E66F0: nop

;}
RECOMP_FUNC void func_801E66F4(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801E66F4: addiu       $sp, $sp, -0x100
    ctx->r29 = ADD32(ctx->r29, -0X100);
    // 0x801E66F8: sw          $ra, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r31;
    // 0x801E66FC: sw          $s0, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r16;
    // 0x801E6700: lhu         $v0, 0x2($a0)
    ctx->r2 = MEM_HU(ctx->r4, 0X2);
    // 0x801E6704: or          $s0, $a0, $zero
    ctx->r16 = ctx->r4 | 0;
    // 0x801E6708: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x801E670C: beql        $v0, $zero, L_801E6728
    if (ctx->r2 == 0) {
        // 0x801E6710: lw          $t1, 0x18($s0)
        ctx->r9 = MEM_W(ctx->r16, 0X18);
            goto L_801E6728;
    }
    goto skip_0;
    // 0x801E6710: lw          $t1, 0x18($s0)
    ctx->r9 = MEM_W(ctx->r16, 0X18);
    skip_0:
    // 0x801E6714: beq         $v0, $at, L_801E67FC
    if (ctx->r2 == ctx->r1) {
        // 0x801E6718: nop
    
            goto L_801E67FC;
    }
    // 0x801E6718: nop

    // 0x801E671C: b           L_801E68DC
    // 0x801E6720: lw          $ra, 0x2C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X2C);
        goto L_801E68DC;
    // 0x801E6720: lw          $ra, 0x2C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X2C);
    // 0x801E6724: lw          $t1, 0x18($s0)
    ctx->r9 = MEM_W(ctx->r16, 0X18);
L_801E6728:
    // 0x801E6728: lui         $at, 0x4220
    ctx->r1 = S32(0X4220 << 16);
    // 0x801E672C: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x801E6730: mtc1        $t1, $f4
    ctx->f4.u32l = ctx->r9;
    // 0x801E6734: lui         $t7, 0x802C
    ctx->r15 = S32(0X802C << 16);
    // 0x801E6738: lw          $t7, 0x6EE4($t7)
    ctx->r15 = MEM_W(ctx->r15, 0X6EE4);
    // 0x801E673C: cvt.s.w     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
    // 0x801E6740: lui         $t6, 0x802C
    ctx->r14 = S32(0X802C << 16);
    // 0x801E6744: lw          $t6, 0x6BD0($t6)
    ctx->r14 = MEM_W(ctx->r14, 0X6BD0);
    // 0x801E6748: sll         $t8, $t7, 2
    ctx->r24 = S32(ctx->r15 << 2);
    // 0x801E674C: addu        $t8, $t8, $t7
    ctx->r24 = ADD32(ctx->r24, ctx->r15);
    // 0x801E6750: sll         $t8, $t8, 2
    ctx->r24 = S32(ctx->r24 << 2);
    // 0x801E6754: div.s       $f2, $f6, $f8
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f2.fl = DIV_S(ctx->f6.fl, ctx->f8.fl);
    // 0x801E6758: mtc1        $zero, $f18
    ctx->f18.u32l = 0;
    // 0x801E675C: addu        $t9, $t6, $t8
    ctx->r25 = ADD32(ctx->r14, ctx->r24);
    // 0x801E6760: addiu       $t0, $t9, 0x6
    ctx->r8 = ADD32(ctx->r25, 0X6);
    // 0x801E6764: lhu         $t3, 0x4($s0)
    ctx->r11 = MEM_HU(ctx->r16, 0X4);
    // 0x801E6768: sw          $t0, 0xC($s0)
    MEM_W(0XC, ctx->r16) = ctx->r8;
    // 0x801E676C: swc1        $f18, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f18.u32l;
    // 0x801E6770: lw          $t5, 0x8($s0)
    ctx->r13 = MEM_W(ctx->r16, 0X8);
    // 0x801E6774: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E6778: lwc1        $f16, 0x6C80($at)
    ctx->f16.u32l = MEM_W(ctx->r1, 0X6C80);
    // 0x801E677C: mtc1        $t5, $f4
    ctx->f4.u32l = ctx->r13;
    // 0x801E6780: lui         $t2, 0x801D
    ctx->r10 = S32(0X801D << 16);
    // 0x801E6784: lw          $t2, -0x1A08($t2)
    ctx->r10 = MEM_W(ctx->r10, -0X1A08);
    // 0x801E6788: sll         $t4, $t3, 6
    ctx->r12 = S32(ctx->r11 << 6);
    // 0x801E678C: addiu       $a1, $sp, 0xC0
    ctx->r5 = ADD32(ctx->r29, 0XC0);
    // 0x801E6790: addu        $a0, $t2, $t4
    ctx->r4 = ADD32(ctx->r10, ctx->r12);
    // 0x801E6794: addiu       $a0, $a0, 0x900
    ctx->r4 = ADD32(ctx->r4, 0X900);
    // 0x801E6798: cvt.s.w     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
    // 0x801E679C: add.s       $f10, $f2, $f2
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f10.fl = ctx->f2.fl + ctx->f2.fl;
    // 0x801E67A0: swc1        $f6, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->f6.u32l;
    // 0x801E67A4: lw          $t7, 0xC($s0)
    ctx->r15 = MEM_W(ctx->r16, 0XC);
    // 0x801E67A8: mul.s       $f0, $f10, $f16
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f0.fl = MUL_S(ctx->f10.fl, ctx->f16.fl);
    // 0x801E67AC: mtc1        $t7, $f8
    ctx->f8.u32l = ctx->r15;
    // 0x801E67B0: mtc1        $zero, $f16
    ctx->f16.u32l = 0;
    // 0x801E67B4: nop

    // 0x801E67B8: swc1        $f16, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->f16.u32l;
    // 0x801E67BC: cvt.s.w     $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.fl = CVT_S_W(ctx->f8.u32l);
    // 0x801E67C0: mfc1        $a2, $f0
    ctx->r6 = (int32_t)ctx->f0.u32l;
    // 0x801E67C4: mfc1        $a3, $f0
    ctx->r7 = (int32_t)ctx->f0.u32l;
    // 0x801E67C8: jal         0x80049A94
    // 0x801E67CC: swc1        $f10, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->f10.u32l;
    func_80049A94(rdram, ctx);
        goto after_0;
    // 0x801E67CC: swc1        $f10, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->f10.u32l;
    after_0:
    // 0x801E67D0: lw          $t6, 0x18($s0)
    ctx->r14 = MEM_W(ctx->r16, 0X18);
    // 0x801E67D4: addiu       $t8, $t6, 0x1
    ctx->r24 = ADD32(ctx->r14, 0X1);
    // 0x801E67D8: slti        $at, $t8, 0x28
    ctx->r1 = SIGNED(ctx->r24) < 0X28 ? 1 : 0;
    // 0x801E67DC: bne         $at, $zero, L_801E67EC
    if (ctx->r1 != 0) {
        // 0x801E67E0: sw          $t8, 0x18($s0)
        MEM_W(0X18, ctx->r16) = ctx->r24;
            goto L_801E67EC;
    }
    // 0x801E67E0: sw          $t8, 0x18($s0)
    MEM_W(0X18, ctx->r16) = ctx->r24;
    // 0x801E67E4: addiu       $t9, $t8, -0x28
    ctx->r25 = ADD32(ctx->r24, -0X28);
    // 0x801E67E8: sw          $t9, 0x18($s0)
    MEM_W(0X18, ctx->r16) = ctx->r25;
L_801E67EC:
    // 0x801E67EC: lw          $t0, 0x20($s0)
    ctx->r8 = MEM_W(ctx->r16, 0X20);
    // 0x801E67F0: addiu       $t1, $t0, 0x4
    ctx->r9 = ADD32(ctx->r8, 0X4);
    // 0x801E67F4: b           L_801E68D8
    // 0x801E67F8: sw          $t1, 0x20($s0)
    MEM_W(0X20, ctx->r16) = ctx->r9;
        goto L_801E68D8;
    // 0x801E67F8: sw          $t1, 0x20($s0)
    MEM_W(0X20, ctx->r16) = ctx->r9;
L_801E67FC:
    // 0x801E67FC: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x801E6800: lh          $v0, -0x19DC($v0)
    ctx->r2 = MEM_H(ctx->r2, -0X19DC);
    // 0x801E6804: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x801E6808: bnel        $v0, $at, L_801E681C
    if (ctx->r2 != ctx->r1) {
        // 0x801E680C: lw          $t5, 0x18($s0)
        ctx->r13 = MEM_W(ctx->r16, 0X18);
            goto L_801E681C;
    }
    goto skip_1;
    // 0x801E680C: lw          $t5, 0x18($s0)
    ctx->r13 = MEM_W(ctx->r16, 0X18);
    skip_1:
    // 0x801E6810: b           L_801E68D8
    // 0x801E6814: sh          $zero, 0x0($s0)
    MEM_H(0X0, ctx->r16) = 0;
        goto L_801E68D8;
    // 0x801E6814: sh          $zero, 0x0($s0)
    MEM_H(0X0, ctx->r16) = 0;
    // 0x801E6818: lw          $t5, 0x18($s0)
    ctx->r13 = MEM_W(ctx->r16, 0X18);
L_801E681C:
    // 0x801E681C: lui         $at, 0x4220
    ctx->r1 = S32(0X4220 << 16);
    // 0x801E6820: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x801E6824: mtc1        $t5, $f18
    ctx->f18.u32l = ctx->r13;
    // 0x801E6828: lw          $t3, 0x24($s0)
    ctx->r11 = MEM_W(ctx->r16, 0X24);
    // 0x801E682C: sll         $t2, $v0, 4
    ctx->r10 = S32(ctx->r2 << 4);
    // 0x801E6830: cvt.s.w     $f4, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    ctx->f4.fl = CVT_S_W(ctx->f18.u32l);
    // 0x801E6834: mtc1        $zero, $f16
    ctx->f16.u32l = 0;
    // 0x801E6838: subu        $t2, $t2, $v0
    ctx->r10 = SUB32(ctx->r10, ctx->r2);
    // 0x801E683C: addu        $t4, $t3, $t2
    ctx->r12 = ADD32(ctx->r11, ctx->r10);
    // 0x801E6840: lhu         $t6, 0x4($s0)
    ctx->r14 = MEM_HU(ctx->r16, 0X4);
    // 0x801E6844: sw          $t4, 0xC($s0)
    MEM_W(0XC, ctx->r16) = ctx->r12;
    // 0x801E6848: div.s       $f2, $f4, $f6
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f2.fl = DIV_S(ctx->f4.fl, ctx->f6.fl);
    // 0x801E684C: swc1        $f16, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f16.u32l;
    // 0x801E6850: lw          $t9, 0x8($s0)
    ctx->r25 = MEM_W(ctx->r16, 0X8);
    // 0x801E6854: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E6858: lwc1        $f10, 0x6C84($at)
    ctx->f10.u32l = MEM_W(ctx->r1, 0X6C84);
    // 0x801E685C: mtc1        $t9, $f18
    ctx->f18.u32l = ctx->r25;
    // 0x801E6860: lui         $t7, 0x801D
    ctx->r15 = S32(0X801D << 16);
    // 0x801E6864: lw          $t7, -0x1A08($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X1A08);
    // 0x801E6868: cvt.s.w     $f4, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    ctx->f4.fl = CVT_S_W(ctx->f18.u32l);
    // 0x801E686C: sll         $t8, $t6, 6
    ctx->r24 = S32(ctx->r14 << 6);
    // 0x801E6870: addu        $a0, $t7, $t8
    ctx->r4 = ADD32(ctx->r15, ctx->r24);
    // 0x801E6874: addiu       $a0, $a0, 0x900
    ctx->r4 = ADD32(ctx->r4, 0X900);
    // 0x801E6878: addiu       $a1, $sp, 0xC0
    ctx->r5 = ADD32(ctx->r29, 0XC0);
    // 0x801E687C: swc1        $f4, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->f4.u32l;
    // 0x801E6880: lw          $t0, 0xC($s0)
    ctx->r8 = MEM_W(ctx->r16, 0XC);
    // 0x801E6884: mtc1        $t0, $f6
    ctx->f6.u32l = ctx->r8;
    // 0x801E6888: add.s       $f8, $f2, $f2
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f8.fl = ctx->f2.fl + ctx->f2.fl;
    // 0x801E688C: mul.s       $f0, $f8, $f10
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f0.fl = MUL_S(ctx->f8.fl, ctx->f10.fl);
    // 0x801E6890: mtc1        $zero, $f10
    ctx->f10.u32l = 0;
    // 0x801E6894: nop

    // 0x801E6898: swc1        $f10, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->f10.u32l;
    // 0x801E689C: cvt.s.w     $f8, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    ctx->f8.fl = CVT_S_W(ctx->f6.u32l);
    // 0x801E68A0: mfc1        $a2, $f0
    ctx->r6 = (int32_t)ctx->f0.u32l;
    // 0x801E68A4: mfc1        $a3, $f0
    ctx->r7 = (int32_t)ctx->f0.u32l;
    // 0x801E68A8: jal         0x80049A94
    // 0x801E68AC: swc1        $f8, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->f8.u32l;
    func_80049A94(rdram, ctx);
        goto after_1;
    // 0x801E68AC: swc1        $f8, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->f8.u32l;
    after_1:
    // 0x801E68B0: lw          $t1, 0x18($s0)
    ctx->r9 = MEM_W(ctx->r16, 0X18);
    // 0x801E68B4: addiu       $t3, $t1, 0x1
    ctx->r11 = ADD32(ctx->r9, 0X1);
    // 0x801E68B8: slti        $at, $t3, 0x28
    ctx->r1 = SIGNED(ctx->r11) < 0X28 ? 1 : 0;
    // 0x801E68BC: bne         $at, $zero, L_801E68CC
    if (ctx->r1 != 0) {
        // 0x801E68C0: sw          $t3, 0x18($s0)
        MEM_W(0X18, ctx->r16) = ctx->r11;
            goto L_801E68CC;
    }
    // 0x801E68C0: sw          $t3, 0x18($s0)
    MEM_W(0X18, ctx->r16) = ctx->r11;
    // 0x801E68C4: addiu       $t2, $t3, -0x28
    ctx->r10 = ADD32(ctx->r11, -0X28);
    // 0x801E68C8: sw          $t2, 0x18($s0)
    MEM_W(0X18, ctx->r16) = ctx->r10;
L_801E68CC:
    // 0x801E68CC: lw          $t4, 0x20($s0)
    ctx->r12 = MEM_W(ctx->r16, 0X20);
    // 0x801E68D0: addiu       $t5, $t4, 0x4
    ctx->r13 = ADD32(ctx->r12, 0X4);
    // 0x801E68D4: sw          $t5, 0x20($s0)
    MEM_W(0X20, ctx->r16) = ctx->r13;
L_801E68D8:
    // 0x801E68D8: lw          $ra, 0x2C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X2C);
L_801E68DC:
    // 0x801E68DC: lw          $s0, 0x28($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X28);
    // 0x801E68E0: addiu       $sp, $sp, 0x100
    ctx->r29 = ADD32(ctx->r29, 0X100);
    // 0x801E68E4: jr          $ra
    // 0x801E68E8: nop

    return;
    // 0x801E68E8: nop

;}
RECOMP_FUNC void func_801E68EC(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801E68EC: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x801E68F0: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x801E68F4: lhu         $v0, 0x2($a0)
    ctx->r2 = MEM_HU(ctx->r4, 0X2);
    // 0x801E68F8: addiu       $v1, $zero, 0x1
    ctx->r3 = ADD32(0, 0X1);
    // 0x801E68FC: beql        $v0, $zero, L_801E6920
    if (ctx->r2 == 0) {
        // 0x801E6900: lw          $v0, 0x18($a0)
        ctx->r2 = MEM_W(ctx->r4, 0X18);
            goto L_801E6920;
    }
    goto skip_0;
    // 0x801E6900: lw          $v0, 0x18($a0)
    ctx->r2 = MEM_W(ctx->r4, 0X18);
    skip_0:
    // 0x801E6904: beq         $v0, $v1, L_801E6994
    if (ctx->r2 == ctx->r3) {
        // 0x801E6908: addiu       $at, $zero, 0x2
        ctx->r1 = ADD32(0, 0X2);
            goto L_801E6994;
    }
    // 0x801E6908: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x801E690C: beql        $v0, $at, L_801E6A40
    if (ctx->r2 == ctx->r1) {
        // 0x801E6910: lw          $ra, 0x14($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X14);
            goto L_801E6A40;
    }
    goto skip_1;
    // 0x801E6910: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    skip_1:
    // 0x801E6914: b           L_801E6A40
    // 0x801E6918: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_801E6A40;
    // 0x801E6918: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x801E691C: lw          $v0, 0x18($a0)
    ctx->r2 = MEM_W(ctx->r4, 0X18);
L_801E6920:
    // 0x801E6920: lui         $at, 0x4040
    ctx->r1 = S32(0X4040 << 16);
    // 0x801E6924: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x801E6928: mtc1        $v0, $f4
    ctx->f4.u32l = ctx->r2;
    // 0x801E692C: addiu       $t9, $v0, 0x1
    ctx->r25 = ADD32(ctx->r2, 0X1);
    // 0x801E6930: sw          $t9, 0x18($a0)
    MEM_W(0X18, ctx->r4) = ctx->r25;
    // 0x801E6934: cvt.s.w     $f0, $f4
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 4);
    ctx->f0.fl = CVT_S_W(ctx->f4.u32l);
    // 0x801E6938: addiu       $v1, $zero, 0x1
    ctx->r3 = ADD32(0, 0X1);
    // 0x801E693C: addiu       $a1, $zero, 0x3F
    ctx->r5 = ADD32(0, 0X3F);
    // 0x801E6940: addiu       $t1, $zero, 0x1
    ctx->r9 = ADD32(0, 0X1);
    // 0x801E6944: mul.s       $f8, $f0, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = MUL_S(ctx->f0.fl, ctx->f6.fl);
    // 0x801E6948: nop

    // 0x801E694C: mul.s       $f10, $f8, $f0
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f10.fl = MUL_S(ctx->f8.fl, ctx->f0.fl);
    // 0x801E6950: trunc.w.s   $f16, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    ctx->f16.u32l = TRUNC_W_S(ctx->f10.fl);
    // 0x801E6954: mfc1        $t7, $f16
    ctx->r15 = (int32_t)ctx->f16.u32l;
    // 0x801E6958: nop

    // 0x801E695C: addiu       $t8, $t7, -0x28
    ctx->r24 = ADD32(ctx->r15, -0X28);
    // 0x801E6960: slti        $at, $t8, 0x3F
    ctx->r1 = SIGNED(ctx->r24) < 0X3F ? 1 : 0;
    // 0x801E6964: bne         $at, $zero, L_801E6A3C
    if (ctx->r1 != 0) {
        // 0x801E6968: sw          $t8, 0xC($a0)
        MEM_W(0XC, ctx->r4) = ctx->r24;
            goto L_801E6A3C;
    }
    // 0x801E6968: sw          $t8, 0xC($a0)
    MEM_W(0XC, ctx->r4) = ctx->r24;
    // 0x801E696C: lui         $at, 0x4180
    ctx->r1 = S32(0X4180 << 16);
    // 0x801E6970: mtc1        $at, $f18
    ctx->f18.u32l = ctx->r1;
    // 0x801E6974: sh          $t1, 0x2($a0)
    MEM_H(0X2, ctx->r4) = ctx->r9;
    // 0x801E6978: sw          $a1, 0xC($a0)
    MEM_W(0XC, ctx->r4) = ctx->r5;
    // 0x801E697C: sw          $v1, 0x18($a0)
    MEM_W(0X18, ctx->r4) = ctx->r3;
    // 0x801E6980: sw          $v1, 0x1C($a0)
    MEM_W(0X1C, ctx->r4) = ctx->r3;
    // 0x801E6984: jal         0x800C30BC
    // 0x801E6988: swc1        $f18, 0x14($a0)
    MEM_W(0X14, ctx->r4) = ctx->f18.u32l;
    func_800C30BC(rdram, ctx);
        goto after_0;
    // 0x801E6988: swc1        $f18, 0x14($a0)
    MEM_W(0X14, ctx->r4) = ctx->f18.u32l;
    after_0:
    // 0x801E698C: b           L_801E6A40
    // 0x801E6990: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_801E6A40;
    // 0x801E6990: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_801E6994:
    // 0x801E6994: lw          $v0, 0x18($a0)
    ctx->r2 = MEM_W(ctx->r4, 0X18);
    // 0x801E6998: lwc1        $f2, 0x14($a0)
    ctx->f2.u32l = MEM_W(ctx->r4, 0X14);
    // 0x801E699C: lui         $at, 0x3FC0
    ctx->r1 = S32(0X3FC0 << 16);
    // 0x801E69A0: mtc1        $v0, $f4
    ctx->f4.u32l = ctx->r2;
    // 0x801E69A4: mtc1        $at, $f12
    ctx->f12.u32l = ctx->r1;
    // 0x801E69A8: addiu       $a1, $zero, 0x3F
    ctx->r5 = ADD32(0, 0X3F);
    // 0x801E69AC: cvt.s.w     $f0, $f4
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 4);
    ctx->f0.fl = CVT_S_W(ctx->f4.u32l);
    // 0x801E69B0: addiu       $t8, $v0, 0x1
    ctx->r24 = ADD32(ctx->r2, 0X1);
    // 0x801E69B4: sw          $t8, 0x18($a0)
    MEM_W(0X18, ctx->r4) = ctx->r24;
    // 0x801E69B8: mul.s       $f6, $f2, $f0
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f6.fl = MUL_S(ctx->f2.fl, ctx->f0.fl);
    // 0x801E69BC: nop

    // 0x801E69C0: mul.s       $f10, $f12, $f0
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f10.fl = MUL_S(ctx->f12.fl, ctx->f0.fl);
    // 0x801E69C4: trunc.w.s   $f8, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    ctx->f8.u32l = TRUNC_W_S(ctx->f6.fl);
    // 0x801E69C8: mul.s       $f16, $f10, $f0
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f16.fl = MUL_S(ctx->f10.fl, ctx->f0.fl);
    // 0x801E69CC: mfc1        $t3, $f8
    ctx->r11 = (int32_t)ctx->f8.u32l;
    // 0x801E69D0: nop

    // 0x801E69D4: subu        $t4, $a1, $t3
    ctx->r12 = SUB32(ctx->r5, ctx->r11);
    // 0x801E69D8: trunc.w.s   $f18, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    ctx->f18.u32l = TRUNC_W_S(ctx->f16.fl);
    // 0x801E69DC: mfc1        $t6, $f18
    ctx->r14 = (int32_t)ctx->f18.u32l;
    // 0x801E69E0: nop

    // 0x801E69E4: addu        $t7, $t4, $t6
    ctx->r15 = ADD32(ctx->r12, ctx->r14);
    // 0x801E69E8: slti        $at, $t7, 0x40
    ctx->r1 = SIGNED(ctx->r15) < 0X40 ? 1 : 0;
    // 0x801E69EC: bne         $at, $zero, L_801E6A3C
    if (ctx->r1 != 0) {
        // 0x801E69F0: sw          $t7, 0xC($a0)
        MEM_W(0XC, ctx->r4) = ctx->r15;
            goto L_801E6A3C;
    }
    // 0x801E69F0: sw          $t7, 0xC($a0)
    MEM_W(0XC, ctx->r4) = ctx->r15;
    // 0x801E69F4: sw          $a1, 0xC($a0)
    MEM_W(0XC, ctx->r4) = ctx->r5;
    // 0x801E69F8: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E69FC: lwc1        $f4, 0x6C88($at)
    ctx->f4.u32l = MEM_W(ctx->r1, 0X6C88);
    // 0x801E6A00: lw          $t0, 0x1C($a0)
    ctx->r8 = MEM_W(ctx->r4, 0X1C);
    // 0x801E6A04: sw          $v1, 0x18($a0)
    MEM_W(0X18, ctx->r4) = ctx->r3;
    // 0x801E6A08: mul.s       $f6, $f2, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = MUL_S(ctx->f2.fl, ctx->f4.fl);
    // 0x801E6A0C: addiu       $t1, $t0, 0x1
    ctx->r9 = ADD32(ctx->r8, 0X1);
    // 0x801E6A10: sw          $t1, 0x1C($a0)
    MEM_W(0X1C, ctx->r4) = ctx->r9;
    // 0x801E6A14: addiu       $t2, $zero, 0x2
    ctx->r10 = ADD32(0, 0X2);
    // 0x801E6A18: swc1        $f6, 0x14($a0)
    MEM_W(0X14, ctx->r4) = ctx->f6.u32l;
    // 0x801E6A1C: lwc1        $f8, 0x14($a0)
    ctx->f8.u32l = MEM_W(ctx->r4, 0X14);
    // 0x801E6A20: c.lt.s      $f8, $f12
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 12);
    c1cs = ctx->f8.fl < ctx->f12.fl;
    // 0x801E6A24: nop

    // 0x801E6A28: bc1fl       L_801E6A40
    if (!c1cs) {
        // 0x801E6A2C: lw          $ra, 0x14($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X14);
            goto L_801E6A40;
    }
    goto skip_2;
    // 0x801E6A2C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    skip_2:
    // 0x801E6A30: sh          $t2, 0x2($a0)
    MEM_H(0X2, ctx->r4) = ctx->r10;
    // 0x801E6A34: sw          $zero, 0x1C($a0)
    MEM_W(0X1C, ctx->r4) = 0;
    // 0x801E6A38: sw          $zero, 0x18($a0)
    MEM_W(0X18, ctx->r4) = 0;
L_801E6A3C:
    // 0x801E6A3C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_801E6A40:
    // 0x801E6A40: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x801E6A44: jr          $ra
    // 0x801E6A48: nop

    return;
    // 0x801E6A48: nop

;}
RECOMP_FUNC void func_801E6A4C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801E6A4C: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x801E6A50: andi        $t6, $a0, 0xFFFF
    ctx->r14 = ctx->r4 & 0XFFFF;
    // 0x801E6A54: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    // 0x801E6A58: sltiu       $at, $t6, 0x5
    ctx->r1 = ctx->r14 < 0X5 ? 1 : 0;
    // 0x801E6A5C: or          $a0, $t6, $zero
    ctx->r4 = ctx->r14 | 0;
    // 0x801E6A60: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x801E6A64: sw          $a1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r5;
    // 0x801E6A68: beq         $at, $zero, L_801E6F5C
    if (ctx->r1 == 0) {
        // 0x801E6A6C: andi        $a3, $a1, 0xFFFF
        ctx->r7 = ctx->r5 & 0XFFFF;
            goto L_801E6F5C;
    }
    // 0x801E6A6C: andi        $a3, $a1, 0xFFFF
    ctx->r7 = ctx->r5 & 0XFFFF;
    // 0x801E6A70: sll         $t7, $t6, 2
    ctx->r15 = S32(ctx->r14 << 2);
    // 0x801E6A74: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E6A78: addu        $at, $at, $t7
    gpr jr_addend_801E6A80 = ctx->r15;
    ctx->r1 = ADD32(ctx->r1, ctx->r15);
    // 0x801E6A7C: lw          $t7, 0x6C8C($at)
    ctx->r15 = ADD32(ctx->r1, 0X6C8C);
    // 0x801E6A80: jr          $t7
    // 0x801E6A84: nop

    switch (jr_addend_801E6A80 >> 2) {
        case 0: goto L_801E6A88; break;
        case 1: goto L_801E6BFC; break;
        case 2: goto L_801E6C98; break;
        case 3: goto L_801E6D48; break;
        case 4: goto L_801E6EC0; break;
        default: switch_error(__func__, 0x801E6A80, 0x80226C8C);
    }
    // 0x801E6A84: nop

L_801E6A88:
    // 0x801E6A88: bne         $a3, $zero, L_801E6F5C
    if (ctx->r7 != 0) {
        // 0x801E6A8C: lui         $v1, 0x8022
        ctx->r3 = S32(0X8022 << 16);
            goto L_801E6F5C;
    }
    // 0x801E6A8C: lui         $v1, 0x8022
    ctx->r3 = S32(0X8022 << 16);
    // 0x801E6A90: addiu       $v1, $v1, 0x6C50
    ctx->r3 = ADD32(ctx->r3, 0X6C50);
    // 0x801E6A94: lui         $a1, 0x8023
    ctx->r5 = S32(0X8023 << 16);
    // 0x801E6A98: addiu       $a1, $a1, -0x76D0
    ctx->r5 = ADD32(ctx->r5, -0X76D0);
    // 0x801E6A9C: or          $t1, $a1, $zero
    ctx->r9 = ctx->r5 | 0;
    // 0x801E6AA0: or          $t0, $v1, $zero
    ctx->r8 = ctx->r3 | 0;
    // 0x801E6AA4: addiu       $t9, $v1, 0x24
    ctx->r25 = ADD32(ctx->r3, 0X24);
L_801E6AA8:
    // 0x801E6AA8: lw          $at, 0x0($t0)
    ctx->r1 = MEM_W(ctx->r8, 0X0);
    // 0x801E6AAC: addiu       $t0, $t0, 0xC
    ctx->r8 = ADD32(ctx->r8, 0XC);
    // 0x801E6AB0: addiu       $t1, $t1, 0xC
    ctx->r9 = ADD32(ctx->r9, 0XC);
    // 0x801E6AB4: sw          $at, -0xC($t1)
    MEM_W(-0XC, ctx->r9) = ctx->r1;
    // 0x801E6AB8: lw          $at, -0x8($t0)
    ctx->r1 = MEM_W(ctx->r8, -0X8);
    // 0x801E6ABC: sw          $at, -0x8($t1)
    MEM_W(-0X8, ctx->r9) = ctx->r1;
    // 0x801E6AC0: lw          $at, -0x4($t0)
    ctx->r1 = MEM_W(ctx->r8, -0X4);
    // 0x801E6AC4: bne         $t0, $t9, L_801E6AA8
    if (ctx->r8 != ctx->r25) {
        // 0x801E6AC8: sw          $at, -0x4($t1)
        MEM_W(-0X4, ctx->r9) = ctx->r1;
            goto L_801E6AA8;
    }
    // 0x801E6AC8: sw          $at, -0x4($t1)
    MEM_W(-0X4, ctx->r9) = ctx->r1;
    // 0x801E6ACC: lw          $at, 0x0($t0)
    ctx->r1 = MEM_W(ctx->r8, 0X0);
    // 0x801E6AD0: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    // 0x801E6AD4: sll         $t2, $a0, 2
    ctx->r10 = S32(ctx->r4 << 2);
    // 0x801E6AD8: subu        $t2, $t2, $a0
    ctx->r10 = SUB32(ctx->r10, ctx->r4);
    // 0x801E6ADC: sll         $t2, $t2, 2
    ctx->r10 = S32(ctx->r10 << 2);
    // 0x801E6AE0: sw          $at, 0x0($t1)
    MEM_W(0X0, ctx->r9) = ctx->r1;
    // 0x801E6AE4: lw          $t9, 0x4($t0)
    ctx->r25 = MEM_W(ctx->r8, 0X4);
    // 0x801E6AE8: subu        $t2, $t2, $a0
    ctx->r10 = SUB32(ctx->r10, ctx->r4);
    // 0x801E6AEC: sll         $t2, $t2, 2
    ctx->r10 = S32(ctx->r10 << 2);
    // 0x801E6AF0: addu        $v0, $a1, $t2
    ctx->r2 = ADD32(ctx->r5, ctx->r10);
    // 0x801E6AF4: or          $t6, $v0, $zero
    ctx->r14 = ctx->r2 | 0;
    // 0x801E6AF8: or          $t5, $v1, $zero
    ctx->r13 = ctx->r3 | 0;
    // 0x801E6AFC: addiu       $t4, $v1, 0x24
    ctx->r12 = ADD32(ctx->r3, 0X24);
    // 0x801E6B00: sw          $t9, 0x4($t1)
    MEM_W(0X4, ctx->r9) = ctx->r25;
L_801E6B04:
    // 0x801E6B04: lw          $at, 0x0($t5)
    ctx->r1 = MEM_W(ctx->r13, 0X0);
    // 0x801E6B08: addiu       $t5, $t5, 0xC
    ctx->r13 = ADD32(ctx->r13, 0XC);
    // 0x801E6B0C: addiu       $t6, $t6, 0xC
    ctx->r14 = ADD32(ctx->r14, 0XC);
    // 0x801E6B10: sw          $at, -0xC($t6)
    MEM_W(-0XC, ctx->r14) = ctx->r1;
    // 0x801E6B14: lw          $at, -0x8($t5)
    ctx->r1 = MEM_W(ctx->r13, -0X8);
    // 0x801E6B18: sw          $at, -0x8($t6)
    MEM_W(-0X8, ctx->r14) = ctx->r1;
    // 0x801E6B1C: lw          $at, -0x4($t5)
    ctx->r1 = MEM_W(ctx->r13, -0X4);
    // 0x801E6B20: bne         $t5, $t4, L_801E6B04
    if (ctx->r13 != ctx->r12) {
        // 0x801E6B24: sw          $at, -0x4($t6)
        MEM_W(-0X4, ctx->r14) = ctx->r1;
            goto L_801E6B04;
    }
    // 0x801E6B24: sw          $at, -0x4($t6)
    MEM_W(-0X4, ctx->r14) = ctx->r1;
    // 0x801E6B28: lw          $at, 0x0($t5)
    ctx->r1 = MEM_W(ctx->r13, 0X0);
    // 0x801E6B2C: or          $t9, $v1, $zero
    ctx->r25 = ctx->r3 | 0;
    // 0x801E6B30: or          $t0, $v0, $zero
    ctx->r8 = ctx->r2 | 0;
    // 0x801E6B34: sw          $at, 0x0($t6)
    MEM_W(0X0, ctx->r14) = ctx->r1;
    // 0x801E6B38: lw          $t4, 0x4($t5)
    ctx->r12 = MEM_W(ctx->r13, 0X4);
    // 0x801E6B3C: addiu       $t8, $v1, 0x24
    ctx->r24 = ADD32(ctx->r3, 0X24);
    // 0x801E6B40: sw          $t4, 0x4($t6)
    MEM_W(0X4, ctx->r14) = ctx->r12;
L_801E6B44:
    // 0x801E6B44: lw          $at, 0x0($t9)
    ctx->r1 = MEM_W(ctx->r25, 0X0);
    // 0x801E6B48: addiu       $t9, $t9, 0xC
    ctx->r25 = ADD32(ctx->r25, 0XC);
    // 0x801E6B4C: addiu       $t0, $t0, 0xC
    ctx->r8 = ADD32(ctx->r8, 0XC);
    // 0x801E6B50: sw          $at, 0x20($t0)
    MEM_W(0X20, ctx->r8) = ctx->r1;
    // 0x801E6B54: lw          $at, -0x8($t9)
    ctx->r1 = MEM_W(ctx->r25, -0X8);
    // 0x801E6B58: sw          $at, 0x24($t0)
    MEM_W(0X24, ctx->r8) = ctx->r1;
    // 0x801E6B5C: lw          $at, -0x4($t9)
    ctx->r1 = MEM_W(ctx->r25, -0X4);
    // 0x801E6B60: bne         $t9, $t8, L_801E6B44
    if (ctx->r25 != ctx->r24) {
        // 0x801E6B64: sw          $at, 0x28($t0)
        MEM_W(0X28, ctx->r8) = ctx->r1;
            goto L_801E6B44;
    }
    // 0x801E6B64: sw          $at, 0x28($t0)
    MEM_W(0X28, ctx->r8) = ctx->r1;
    // 0x801E6B68: lw          $at, 0x0($t9)
    ctx->r1 = MEM_W(ctx->r25, 0X0);
    // 0x801E6B6C: or          $t3, $v1, $zero
    ctx->r11 = ctx->r3 | 0;
    // 0x801E6B70: or          $t4, $v0, $zero
    ctx->r12 = ctx->r2 | 0;
    // 0x801E6B74: sw          $at, 0x2C($t0)
    MEM_W(0X2C, ctx->r8) = ctx->r1;
    // 0x801E6B78: lw          $t8, 0x4($t9)
    ctx->r24 = MEM_W(ctx->r25, 0X4);
    // 0x801E6B7C: addiu       $t2, $v1, 0x24
    ctx->r10 = ADD32(ctx->r3, 0X24);
    // 0x801E6B80: sw          $t8, 0x30($t0)
    MEM_W(0X30, ctx->r8) = ctx->r24;
L_801E6B84:
    // 0x801E6B84: lw          $at, 0x0($t3)
    ctx->r1 = MEM_W(ctx->r11, 0X0);
    // 0x801E6B88: addiu       $t3, $t3, 0xC
    ctx->r11 = ADD32(ctx->r11, 0XC);
    // 0x801E6B8C: addiu       $t4, $t4, 0xC
    ctx->r12 = ADD32(ctx->r12, 0XC);
    // 0x801E6B90: sw          $at, 0x4C($t4)
    MEM_W(0X4C, ctx->r12) = ctx->r1;
    // 0x801E6B94: lw          $at, -0x8($t3)
    ctx->r1 = MEM_W(ctx->r11, -0X8);
    // 0x801E6B98: sw          $at, 0x50($t4)
    MEM_W(0X50, ctx->r12) = ctx->r1;
    // 0x801E6B9C: lw          $at, -0x4($t3)
    ctx->r1 = MEM_W(ctx->r11, -0X4);
    // 0x801E6BA0: bne         $t3, $t2, L_801E6B84
    if (ctx->r11 != ctx->r10) {
        // 0x801E6BA4: sw          $at, 0x54($t4)
        MEM_W(0X54, ctx->r12) = ctx->r1;
            goto L_801E6B84;
    }
    // 0x801E6BA4: sw          $at, 0x54($t4)
    MEM_W(0X54, ctx->r12) = ctx->r1;
    // 0x801E6BA8: lw          $at, 0x0($t3)
    ctx->r1 = MEM_W(ctx->r11, 0X0);
    // 0x801E6BAC: or          $t7, $v1, $zero
    ctx->r15 = ctx->r3 | 0;
    // 0x801E6BB0: or          $t8, $v0, $zero
    ctx->r24 = ctx->r2 | 0;
    // 0x801E6BB4: sw          $at, 0x58($t4)
    MEM_W(0X58, ctx->r12) = ctx->r1;
    // 0x801E6BB8: lw          $t2, 0x4($t3)
    ctx->r10 = MEM_W(ctx->r11, 0X4);
    // 0x801E6BBC: addiu       $t6, $v1, 0x24
    ctx->r14 = ADD32(ctx->r3, 0X24);
    // 0x801E6BC0: sw          $t2, 0x5C($t4)
    MEM_W(0X5C, ctx->r12) = ctx->r10;
L_801E6BC4:
    // 0x801E6BC4: lw          $at, 0x0($t7)
    ctx->r1 = MEM_W(ctx->r15, 0X0);
    // 0x801E6BC8: addiu       $t7, $t7, 0xC
    ctx->r15 = ADD32(ctx->r15, 0XC);
    // 0x801E6BCC: addiu       $t8, $t8, 0xC
    ctx->r24 = ADD32(ctx->r24, 0XC);
    // 0x801E6BD0: sw          $at, 0x78($t8)
    MEM_W(0X78, ctx->r24) = ctx->r1;
    // 0x801E6BD4: lw          $at, -0x8($t7)
    ctx->r1 = MEM_W(ctx->r15, -0X8);
    // 0x801E6BD8: sw          $at, 0x7C($t8)
    MEM_W(0X7C, ctx->r24) = ctx->r1;
    // 0x801E6BDC: lw          $at, -0x4($t7)
    ctx->r1 = MEM_W(ctx->r15, -0X4);
    // 0x801E6BE0: bne         $t7, $t6, L_801E6BC4
    if (ctx->r15 != ctx->r14) {
        // 0x801E6BE4: sw          $at, 0x80($t8)
        MEM_W(0X80, ctx->r24) = ctx->r1;
            goto L_801E6BC4;
    }
    // 0x801E6BE4: sw          $at, 0x80($t8)
    MEM_W(0X80, ctx->r24) = ctx->r1;
    // 0x801E6BE8: lw          $at, 0x0($t7)
    ctx->r1 = MEM_W(ctx->r15, 0X0);
    // 0x801E6BEC: sw          $at, 0x84($t8)
    MEM_W(0X84, ctx->r24) = ctx->r1;
    // 0x801E6BF0: lw          $t6, 0x4($t7)
    ctx->r14 = MEM_W(ctx->r15, 0X4);
    // 0x801E6BF4: b           L_801E6F5C
    // 0x801E6BF8: sw          $t6, 0x88($t8)
    MEM_W(0X88, ctx->r24) = ctx->r14;
        goto L_801E6F5C;
    // 0x801E6BF8: sw          $t6, 0x88($t8)
    MEM_W(0X88, ctx->r24) = ctx->r14;
L_801E6BFC:
    // 0x801E6BFC: jal         0x801E6F6C
    // 0x801E6C00: nop

    func_801E6F6C(rdram, ctx);
        goto after_0;
    // 0x801E6C00: nop

    after_0:
    // 0x801E6C04: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x801E6C08: beq         $v0, $at, L_801E6F5C
    if (ctx->r2 == ctx->r1) {
        // 0x801E6C0C: lui         $v1, 0x8022
        ctx->r3 = S32(0X8022 << 16);
            goto L_801E6F5C;
    }
    // 0x801E6C0C: lui         $v1, 0x8022
    ctx->r3 = S32(0X8022 << 16);
    // 0x801E6C10: sll         $t9, $v0, 2
    ctx->r25 = S32(ctx->r2 << 2);
    // 0x801E6C14: subu        $t9, $t9, $v0
    ctx->r25 = SUB32(ctx->r25, ctx->r2);
    // 0x801E6C18: sll         $t9, $t9, 2
    ctx->r25 = S32(ctx->r25 << 2);
    // 0x801E6C1C: lui         $a1, 0x8023
    ctx->r5 = S32(0X8023 << 16);
    // 0x801E6C20: subu        $t9, $t9, $v0
    ctx->r25 = SUB32(ctx->r25, ctx->r2);
    // 0x801E6C24: addiu       $a1, $a1, -0x76D0
    ctx->r5 = ADD32(ctx->r5, -0X76D0);
    // 0x801E6C28: sll         $t9, $t9, 2
    ctx->r25 = S32(ctx->r25 << 2);
    // 0x801E6C2C: addiu       $t2, $v1, 0x6C50
    ctx->r10 = ADD32(ctx->r3, 0X6C50);
    // 0x801E6C30: addu        $a0, $a1, $t9
    ctx->r4 = ADD32(ctx->r5, ctx->r25);
    // 0x801E6C34: or          $t3, $a0, $zero
    ctx->r11 = ctx->r4 | 0;
    // 0x801E6C38: addiu       $t1, $t2, 0x24
    ctx->r9 = ADD32(ctx->r10, 0X24);
L_801E6C3C:
    // 0x801E6C3C: lw          $at, 0x0($t2)
    ctx->r1 = MEM_W(ctx->r10, 0X0);
    // 0x801E6C40: addiu       $t2, $t2, 0xC
    ctx->r10 = ADD32(ctx->r10, 0XC);
    // 0x801E6C44: addiu       $t3, $t3, 0xC
    ctx->r11 = ADD32(ctx->r11, 0XC);
    // 0x801E6C48: sw          $at, -0xC($t3)
    MEM_W(-0XC, ctx->r11) = ctx->r1;
    // 0x801E6C4C: lw          $at, -0x8($t2)
    ctx->r1 = MEM_W(ctx->r10, -0X8);
    // 0x801E6C50: sw          $at, -0x8($t3)
    MEM_W(-0X8, ctx->r11) = ctx->r1;
    // 0x801E6C54: lw          $at, -0x4($t2)
    ctx->r1 = MEM_W(ctx->r10, -0X4);
    // 0x801E6C58: bne         $t2, $t1, L_801E6C3C
    if (ctx->r10 != ctx->r9) {
        // 0x801E6C5C: sw          $at, -0x4($t3)
        MEM_W(-0X4, ctx->r11) = ctx->r1;
            goto L_801E6C3C;
    }
    // 0x801E6C5C: sw          $at, -0x4($t3)
    MEM_W(-0X4, ctx->r11) = ctx->r1;
    // 0x801E6C60: lw          $at, 0x0($t2)
    ctx->r1 = MEM_W(ctx->r10, 0X0);
    // 0x801E6C64: addiu       $t4, $zero, 0x1
    ctx->r12 = ADD32(0, 0X1);
    // 0x801E6C68: addiu       $t5, $zero, 0x50
    ctx->r13 = ADD32(0, 0X50);
    // 0x801E6C6C: sw          $at, 0x0($t3)
    MEM_W(0X0, ctx->r11) = ctx->r1;
    // 0x801E6C70: lw          $t1, 0x4($t2)
    ctx->r9 = MEM_W(ctx->r10, 0X4);
    // 0x801E6C74: addiu       $t6, $zero, 0x5D
    ctx->r14 = ADD32(0, 0X5D);
    // 0x801E6C78: sw          $t1, 0x4($t3)
    MEM_W(0X4, ctx->r11) = ctx->r9;
    // 0x801E6C7C: sh          $v0, 0x4($a0)
    MEM_H(0X4, ctx->r4) = ctx->r2;
    // 0x801E6C80: sh          $t4, 0x0($a0)
    MEM_H(0X0, ctx->r4) = ctx->r12;
    // 0x801E6C84: sh          $zero, 0x2($a0)
    MEM_H(0X2, ctx->r4) = 0;
    // 0x801E6C88: sw          $t5, 0x8($a0)
    MEM_W(0X8, ctx->r4) = ctx->r13;
    // 0x801E6C8C: sw          $t6, 0xC($a0)
    MEM_W(0XC, ctx->r4) = ctx->r14;
    // 0x801E6C90: b           L_801E6F5C
    // 0x801E6C94: sw          $zero, 0x18($a0)
    MEM_W(0X18, ctx->r4) = 0;
        goto L_801E6F5C;
    // 0x801E6C94: sw          $zero, 0x18($a0)
    MEM_W(0X18, ctx->r4) = 0;
L_801E6C98:
    // 0x801E6C98: jal         0x801E6F6C
    // 0x801E6C9C: sh          $a3, 0x1E($sp)
    MEM_H(0X1E, ctx->r29) = ctx->r7;
    func_801E6F6C(rdram, ctx);
        goto after_1;
    // 0x801E6C9C: sh          $a3, 0x1E($sp)
    MEM_H(0X1E, ctx->r29) = ctx->r7;
    after_1:
    // 0x801E6CA0: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x801E6CA4: beq         $v0, $at, L_801E6F5C
    if (ctx->r2 == ctx->r1) {
        // 0x801E6CA8: lhu         $a3, 0x1E($sp)
        ctx->r7 = MEM_HU(ctx->r29, 0X1E);
            goto L_801E6F5C;
    }
    // 0x801E6CA8: lhu         $a3, 0x1E($sp)
    ctx->r7 = MEM_HU(ctx->r29, 0X1E);
    // 0x801E6CAC: sll         $t7, $v0, 2
    ctx->r15 = S32(ctx->r2 << 2);
    // 0x801E6CB0: subu        $t7, $t7, $v0
    ctx->r15 = SUB32(ctx->r15, ctx->r2);
    // 0x801E6CB4: sll         $t7, $t7, 2
    ctx->r15 = S32(ctx->r15 << 2);
    // 0x801E6CB8: lui         $a1, 0x8023
    ctx->r5 = S32(0X8023 << 16);
    // 0x801E6CBC: subu        $t7, $t7, $v0
    ctx->r15 = SUB32(ctx->r15, ctx->r2);
    // 0x801E6CC0: addiu       $a1, $a1, -0x76D0
    ctx->r5 = ADD32(ctx->r5, -0X76D0);
    // 0x801E6CC4: lui         $v1, 0x8022
    ctx->r3 = S32(0X8022 << 16);
    // 0x801E6CC8: sll         $t7, $t7, 2
    ctx->r15 = S32(ctx->r15 << 2);
    // 0x801E6CCC: addiu       $t0, $v1, 0x6C50
    ctx->r8 = ADD32(ctx->r3, 0X6C50);
    // 0x801E6CD0: addu        $a0, $a1, $t7
    ctx->r4 = ADD32(ctx->r5, ctx->r15);
    // 0x801E6CD4: or          $t1, $a0, $zero
    ctx->r9 = ctx->r4 | 0;
    // 0x801E6CD8: addiu       $t9, $t0, 0x24
    ctx->r25 = ADD32(ctx->r8, 0X24);
L_801E6CDC:
    // 0x801E6CDC: lw          $at, 0x0($t0)
    ctx->r1 = MEM_W(ctx->r8, 0X0);
    // 0x801E6CE0: addiu       $t0, $t0, 0xC
    ctx->r8 = ADD32(ctx->r8, 0XC);
    // 0x801E6CE4: addiu       $t1, $t1, 0xC
    ctx->r9 = ADD32(ctx->r9, 0XC);
    // 0x801E6CE8: sw          $at, -0xC($t1)
    MEM_W(-0XC, ctx->r9) = ctx->r1;
    // 0x801E6CEC: lw          $at, -0x8($t0)
    ctx->r1 = MEM_W(ctx->r8, -0X8);
    // 0x801E6CF0: sw          $at, -0x8($t1)
    MEM_W(-0X8, ctx->r9) = ctx->r1;
    // 0x801E6CF4: lw          $at, -0x4($t0)
    ctx->r1 = MEM_W(ctx->r8, -0X4);
    // 0x801E6CF8: bne         $t0, $t9, L_801E6CDC
    if (ctx->r8 != ctx->r25) {
        // 0x801E6CFC: sw          $at, -0x4($t1)
        MEM_W(-0X4, ctx->r9) = ctx->r1;
            goto L_801E6CDC;
    }
    // 0x801E6CFC: sw          $at, -0x4($t1)
    MEM_W(-0X4, ctx->r9) = ctx->r1;
    // 0x801E6D00: lw          $at, 0x0($t0)
    ctx->r1 = MEM_W(ctx->r8, 0X0);
    // 0x801E6D04: addiu       $t2, $zero, 0x2
    ctx->r10 = ADD32(0, 0X2);
    // 0x801E6D08: addiu       $t3, $zero, 0x6E
    ctx->r11 = ADD32(0, 0X6E);
    // 0x801E6D0C: sw          $at, 0x0($t1)
    MEM_W(0X0, ctx->r9) = ctx->r1;
    // 0x801E6D10: lw          $t9, 0x4($t0)
    ctx->r25 = MEM_W(ctx->r8, 0X4);
    // 0x801E6D14: addiu       $t4, $zero, 0x78
    ctx->r12 = ADD32(0, 0X78);
    // 0x801E6D18: addiu       $t5, $zero, 0x5D
    ctx->r13 = ADD32(0, 0X5D);
    // 0x801E6D1C: sw          $t9, 0x4($t1)
    MEM_W(0X4, ctx->r9) = ctx->r25;
    // 0x801E6D20: sh          $v0, 0x4($a0)
    MEM_H(0X4, ctx->r4) = ctx->r2;
    // 0x801E6D24: sh          $t2, 0x0($a0)
    MEM_H(0X0, ctx->r4) = ctx->r10;
    // 0x801E6D28: beq         $a3, $zero, L_801E6D38
    if (ctx->r7 == 0) {
        // 0x801E6D2C: sh          $zero, 0x2($a0)
        MEM_H(0X2, ctx->r4) = 0;
            goto L_801E6D38;
    }
    // 0x801E6D2C: sh          $zero, 0x2($a0)
    MEM_H(0X2, ctx->r4) = 0;
    // 0x801E6D30: b           L_801E6D3C
    // 0x801E6D34: sw          $t3, 0x8($a0)
    MEM_W(0X8, ctx->r4) = ctx->r11;
        goto L_801E6D3C;
    // 0x801E6D34: sw          $t3, 0x8($a0)
    MEM_W(0X8, ctx->r4) = ctx->r11;
L_801E6D38:
    // 0x801E6D38: sw          $t4, 0x8($a0)
    MEM_W(0X8, ctx->r4) = ctx->r12;
L_801E6D3C:
    // 0x801E6D3C: sw          $t5, 0xC($a0)
    MEM_W(0XC, ctx->r4) = ctx->r13;
    // 0x801E6D40: b           L_801E6F5C
    // 0x801E6D44: sw          $a3, 0x28($a0)
    MEM_W(0X28, ctx->r4) = ctx->r7;
        goto L_801E6F5C;
    // 0x801E6D44: sw          $a3, 0x28($a0)
    MEM_W(0X28, ctx->r4) = ctx->r7;
L_801E6D48:
    // 0x801E6D48: jal         0x801E6F6C
    // 0x801E6D4C: sh          $a3, 0x1E($sp)
    MEM_H(0X1E, ctx->r29) = ctx->r7;
    func_801E6F6C(rdram, ctx);
        goto after_2;
    // 0x801E6D4C: sh          $a3, 0x1E($sp)
    MEM_H(0X1E, ctx->r29) = ctx->r7;
    after_2:
    // 0x801E6D50: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x801E6D54: beq         $v0, $at, L_801E6F5C
    if (ctx->r2 == ctx->r1) {
        // 0x801E6D58: lhu         $a3, 0x1E($sp)
        ctx->r7 = MEM_HU(ctx->r29, 0X1E);
            goto L_801E6F5C;
    }
    // 0x801E6D58: lhu         $a3, 0x1E($sp)
    ctx->r7 = MEM_HU(ctx->r29, 0X1E);
    // 0x801E6D5C: sll         $t6, $v0, 2
    ctx->r14 = S32(ctx->r2 << 2);
    // 0x801E6D60: subu        $t6, $t6, $v0
    ctx->r14 = SUB32(ctx->r14, ctx->r2);
    // 0x801E6D64: sll         $t6, $t6, 2
    ctx->r14 = S32(ctx->r14 << 2);
    // 0x801E6D68: lui         $a1, 0x8023
    ctx->r5 = S32(0X8023 << 16);
    // 0x801E6D6C: subu        $t6, $t6, $v0
    ctx->r14 = SUB32(ctx->r14, ctx->r2);
    // 0x801E6D70: addiu       $a1, $a1, -0x76D0
    ctx->r5 = ADD32(ctx->r5, -0X76D0);
    // 0x801E6D74: lui         $v1, 0x8022
    ctx->r3 = S32(0X8022 << 16);
    // 0x801E6D78: sll         $t6, $t6, 2
    ctx->r14 = S32(ctx->r14 << 2);
    // 0x801E6D7C: addiu       $t9, $v1, 0x6C50
    ctx->r25 = ADD32(ctx->r3, 0X6C50);
    // 0x801E6D80: addu        $a0, $a1, $t6
    ctx->r4 = ADD32(ctx->r5, ctx->r14);
    // 0x801E6D84: or          $t0, $a0, $zero
    ctx->r8 = ctx->r4 | 0;
    // 0x801E6D88: addiu       $t8, $t9, 0x24
    ctx->r24 = ADD32(ctx->r25, 0X24);
L_801E6D8C:
    // 0x801E6D8C: lw          $at, 0x0($t9)
    ctx->r1 = MEM_W(ctx->r25, 0X0);
    // 0x801E6D90: addiu       $t9, $t9, 0xC
    ctx->r25 = ADD32(ctx->r25, 0XC);
    // 0x801E6D94: addiu       $t0, $t0, 0xC
    ctx->r8 = ADD32(ctx->r8, 0XC);
    // 0x801E6D98: sw          $at, -0xC($t0)
    MEM_W(-0XC, ctx->r8) = ctx->r1;
    // 0x801E6D9C: lw          $at, -0x8($t9)
    ctx->r1 = MEM_W(ctx->r25, -0X8);
    // 0x801E6DA0: sw          $at, -0x8($t0)
    MEM_W(-0X8, ctx->r8) = ctx->r1;
    // 0x801E6DA4: lw          $at, -0x4($t9)
    ctx->r1 = MEM_W(ctx->r25, -0X4);
    // 0x801E6DA8: bne         $t9, $t8, L_801E6D8C
    if (ctx->r25 != ctx->r24) {
        // 0x801E6DAC: sw          $at, -0x4($t0)
        MEM_W(-0X4, ctx->r8) = ctx->r1;
            goto L_801E6D8C;
    }
    // 0x801E6DAC: sw          $at, -0x4($t0)
    MEM_W(-0X4, ctx->r8) = ctx->r1;
    // 0x801E6DB0: lw          $at, 0x0($t9)
    ctx->r1 = MEM_W(ctx->r25, 0X0);
    // 0x801E6DB4: addiu       $t1, $zero, 0x3
    ctx->r9 = ADD32(0, 0X3);
    // 0x801E6DB8: or          $a2, $a3, $zero
    ctx->r6 = ctx->r7 | 0;
    // 0x801E6DBC: sw          $at, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r1;
    // 0x801E6DC0: lw          $t8, 0x4($t9)
    ctx->r24 = MEM_W(ctx->r25, 0X4);
    // 0x801E6DC4: sltiu       $at, $a3, 0x8
    ctx->r1 = ctx->r7 < 0X8 ? 1 : 0;
    // 0x801E6DC8: sll         $t2, $a3, 2
    ctx->r10 = S32(ctx->r7 << 2);
    // 0x801E6DCC: sw          $t8, 0x4($t0)
    MEM_W(0X4, ctx->r8) = ctx->r24;
    // 0x801E6DD0: sh          $v0, 0x4($a0)
    MEM_H(0X4, ctx->r4) = ctx->r2;
    // 0x801E6DD4: beq         $at, $zero, L_801E6EB4
    if (ctx->r1 == 0) {
        // 0x801E6DD8: sh          $t1, 0x0($a0)
        MEM_H(0X0, ctx->r4) = ctx->r9;
            goto L_801E6EB4;
    }
    // 0x801E6DD8: sh          $t1, 0x0($a0)
    MEM_H(0X0, ctx->r4) = ctx->r9;
    // 0x801E6DDC: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E6DE0: addu        $at, $at, $t2
    gpr jr_addend_801E6DE8 = ctx->r10;
    ctx->r1 = ADD32(ctx->r1, ctx->r10);
    // 0x801E6DE4: lw          $t2, 0x6CA0($at)
    ctx->r10 = ADD32(ctx->r1, 0X6CA0);
    // 0x801E6DE8: jr          $t2
    // 0x801E6DEC: nop

    switch (jr_addend_801E6DE8 >> 2) {
        case 0: goto L_801E6DF0; break;
        case 1: goto L_801E6E08; break;
        case 2: goto L_801E6E20; break;
        case 3: goto L_801E6E6C; break;
        case 4: goto L_801E6E20; break;
        case 5: goto L_801E6E6C; break;
        case 6: goto L_801E6E20; break;
        case 7: goto L_801E6E6C; break;
        default: switch_error(__func__, 0x801E6DE8, 0x80226CA0);
    }
    // 0x801E6DEC: nop

L_801E6DF0:
    // 0x801E6DF0: addiu       $t3, $zero, 0x86
    ctx->r11 = ADD32(0, 0X86);
    // 0x801E6DF4: addiu       $t4, $zero, 0x54
    ctx->r12 = ADD32(0, 0X54);
    // 0x801E6DF8: sh          $zero, 0x2($a0)
    MEM_H(0X2, ctx->r4) = 0;
    // 0x801E6DFC: sw          $t3, 0x8($a0)
    MEM_W(0X8, ctx->r4) = ctx->r11;
    // 0x801E6E00: b           L_801E6EB4
    // 0x801E6E04: sw          $t4, 0xC($a0)
    MEM_W(0XC, ctx->r4) = ctx->r12;
        goto L_801E6EB4;
    // 0x801E6E04: sw          $t4, 0xC($a0)
    MEM_W(0XC, ctx->r4) = ctx->r12;
L_801E6E08:
    // 0x801E6E08: addiu       $t5, $zero, 0x123
    ctx->r13 = ADD32(0, 0X123);
    // 0x801E6E0C: addiu       $t4, $zero, 0x54
    ctx->r12 = ADD32(0, 0X54);
    // 0x801E6E10: sh          $zero, 0x2($a0)
    MEM_H(0X2, ctx->r4) = 0;
    // 0x801E6E14: sw          $t5, 0x8($a0)
    MEM_W(0X8, ctx->r4) = ctx->r13;
    // 0x801E6E18: b           L_801E6EB4
    // 0x801E6E1C: sw          $t6, 0xC($a0)
    MEM_W(0XC, ctx->r4) = ctx->r14;
        goto L_801E6EB4;
    // 0x801E6E1C: sw          $t6, 0xC($a0)
    MEM_W(0XC, ctx->r4) = ctx->r14;
L_801E6E20:
    // 0x801E6E20: addiu       $t7, $zero, 0x1
    ctx->r15 = ADD32(0, 0X1);
    // 0x801E6E24: addiu       $t8, $zero, 0x84
    ctx->r24 = ADD32(0, 0X84);
    // 0x801E6E28: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x801E6E2C: sh          $t7, 0x2($a0)
    MEM_H(0X2, ctx->r4) = ctx->r15;
    // 0x801E6E30: bne         $a2, $at, L_801E6E44
    if (ctx->r6 != ctx->r1) {
        // 0x801E6E34: sw          $t8, 0x8($a0)
        MEM_W(0X8, ctx->r4) = ctx->r24;
            goto L_801E6E44;
    }
    // 0x801E6E34: sw          $t8, 0x8($a0)
    MEM_W(0X8, ctx->r4) = ctx->r24;
    // 0x801E6E38: addiu       $t9, $zero, 0x65
    ctx->r25 = ADD32(0, 0X65);
    // 0x801E6E3C: b           L_801E6E60
    // 0x801E6E40: sw          $t9, 0xC($a0)
    MEM_W(0XC, ctx->r4) = ctx->r25;
        goto L_801E6E60;
    // 0x801E6E40: sw          $t9, 0xC($a0)
    MEM_W(0XC, ctx->r4) = ctx->r25;
L_801E6E44:
    // 0x801E6E44: addiu       $at, $zero, 0x4
    ctx->r1 = ADD32(0, 0X4);
    // 0x801E6E48: bne         $a2, $at, L_801E6E5C
    if (ctx->r6 != ctx->r1) {
        // 0x801E6E4C: addiu       $t1, $zero, 0xBA
        ctx->r9 = ADD32(0, 0XBA);
            goto L_801E6E5C;
    }
    // 0x801E6E4C: addiu       $t1, $zero, 0xBA
    ctx->r9 = ADD32(0, 0XBA);
    // 0x801E6E50: addiu       $t0, $zero, 0x4C
    ctx->r8 = ADD32(0, 0X4C);
    // 0x801E6E54: b           L_801E6E60
    // 0x801E6E58: sw          $t0, 0xC($a0)
    MEM_W(0XC, ctx->r4) = ctx->r8;
        goto L_801E6E60;
    // 0x801E6E58: sw          $t0, 0xC($a0)
    MEM_W(0XC, ctx->r4) = ctx->r8;
L_801E6E5C:
    // 0x801E6E5C: sw          $t1, 0xC($a0)
    MEM_W(0XC, ctx->r4) = ctx->r9;
L_801E6E60:
    // 0x801E6E60: lw          $t2, 0xC($a0)
    ctx->r10 = MEM_W(ctx->r4, 0XC);
    // 0x801E6E64: b           L_801E6EB4
    // 0x801E6E68: sw          $t2, 0x24($a0)
    MEM_W(0X24, ctx->r4) = ctx->r10;
        goto L_801E6EB4;
    // 0x801E6E68: sw          $t2, 0x24($a0)
    MEM_W(0X24, ctx->r4) = ctx->r10;
L_801E6E6C:
    // 0x801E6E6C: addiu       $t3, $zero, 0x1
    ctx->r11 = ADD32(0, 0X1);
    // 0x801E6E70: addiu       $t4, $zero, 0x124
    ctx->r12 = ADD32(0, 0X124);
    // 0x801E6E74: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x801E6E78: sh          $t3, 0x2($a0)
    MEM_H(0X2, ctx->r4) = ctx->r11;
    // 0x801E6E7C: bne         $a2, $at, L_801E6E90
    if (ctx->r6 != ctx->r1) {
        // 0x801E6E80: sw          $t4, 0x8($a0)
        MEM_W(0X8, ctx->r4) = ctx->r12;
            goto L_801E6E90;
    }
    // 0x801E6E80: sw          $t4, 0x8($a0)
    MEM_W(0X8, ctx->r4) = ctx->r12;
    // 0x801E6E84: addiu       $t5, $zero, 0x65
    ctx->r13 = ADD32(0, 0X65);
    // 0x801E6E88: b           L_801E6EAC
    // 0x801E6E8C: sw          $t5, 0xC($a0)
    MEM_W(0XC, ctx->r4) = ctx->r13;
        goto L_801E6EAC;
    // 0x801E6E8C: sw          $t5, 0xC($a0)
    MEM_W(0XC, ctx->r4) = ctx->r13;
L_801E6E90:
    // 0x801E6E90: addiu       $at, $zero, 0x5
    ctx->r1 = ADD32(0, 0X5);
    // 0x801E6E94: bne         $a2, $at, L_801E6EA8
    if (ctx->r6 != ctx->r1) {
        // 0x801E6E98: addiu       $t7, $zero, 0xBA
        ctx->r15 = ADD32(0, 0XBA);
            goto L_801E6EA8;
    }
    // 0x801E6E98: addiu       $t7, $zero, 0xBA
    ctx->r15 = ADD32(0, 0XBA);
    // 0x801E6E9C: addiu       $t6, $zero, 0x4C
    ctx->r14 = ADD32(0, 0X4C);
    // 0x801E6EA0: b           L_801E6EAC
    // 0x801E6EA4: sw          $t6, 0xC($a0)
    MEM_W(0XC, ctx->r4) = ctx->r14;
        goto L_801E6EAC;
    // 0x801E6EA4: sw          $t6, 0xC($a0)
    MEM_W(0XC, ctx->r4) = ctx->r14;
L_801E6EA8:
    // 0x801E6EA8: sw          $t7, 0xC($a0)
    MEM_W(0XC, ctx->r4) = ctx->r15;
L_801E6EAC:
    // 0x801E6EAC: lw          $t8, 0xC($a0)
    ctx->r24 = MEM_W(ctx->r4, 0XC);
    // 0x801E6EB0: sw          $t8, 0x24($a0)
    MEM_W(0X24, ctx->r4) = ctx->r24;
L_801E6EB4:
    // 0x801E6EB4: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x801E6EB8: b           L_801E6F5C
    // 0x801E6EBC: sw          $t9, 0x20($a0)
    MEM_W(0X20, ctx->r4) = ctx->r25;
        goto L_801E6F5C;
    // 0x801E6EBC: sw          $t9, 0x20($a0)
    MEM_W(0X20, ctx->r4) = ctx->r25;
L_801E6EC0:
    // 0x801E6EC0: jal         0x801E6F6C
    // 0x801E6EC4: sh          $a3, 0x1E($sp)
    MEM_H(0X1E, ctx->r29) = ctx->r7;
    func_801E6F6C(rdram, ctx);
        goto after_3;
    // 0x801E6EC4: sh          $a3, 0x1E($sp)
    MEM_H(0X1E, ctx->r29) = ctx->r7;
    after_3:
    // 0x801E6EC8: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x801E6ECC: beq         $v0, $at, L_801E6F5C
    if (ctx->r2 == ctx->r1) {
        // 0x801E6ED0: lhu         $a3, 0x1E($sp)
        ctx->r7 = MEM_HU(ctx->r29, 0X1E);
            goto L_801E6F5C;
    }
    // 0x801E6ED0: lhu         $a3, 0x1E($sp)
    ctx->r7 = MEM_HU(ctx->r29, 0X1E);
    // 0x801E6ED4: sll         $t0, $v0, 2
    ctx->r8 = S32(ctx->r2 << 2);
    // 0x801E6ED8: subu        $t0, $t0, $v0
    ctx->r8 = SUB32(ctx->r8, ctx->r2);
    // 0x801E6EDC: sll         $t0, $t0, 2
    ctx->r8 = S32(ctx->r8 << 2);
    // 0x801E6EE0: lui         $a1, 0x8023
    ctx->r5 = S32(0X8023 << 16);
    // 0x801E6EE4: subu        $t0, $t0, $v0
    ctx->r8 = SUB32(ctx->r8, ctx->r2);
    // 0x801E6EE8: addiu       $a1, $a1, -0x76D0
    ctx->r5 = ADD32(ctx->r5, -0X76D0);
    // 0x801E6EEC: lui         $v1, 0x8022
    ctx->r3 = S32(0X8022 << 16);
    // 0x801E6EF0: sll         $t0, $t0, 2
    ctx->r8 = S32(ctx->r8 << 2);
    // 0x801E6EF4: addiu       $t3, $v1, 0x6C50
    ctx->r11 = ADD32(ctx->r3, 0X6C50);
    // 0x801E6EF8: addu        $a0, $a1, $t0
    ctx->r4 = ADD32(ctx->r5, ctx->r8);
    // 0x801E6EFC: or          $t4, $a0, $zero
    ctx->r12 = ctx->r4 | 0;
    // 0x801E6F00: addiu       $t2, $t3, 0x24
    ctx->r10 = ADD32(ctx->r11, 0X24);
L_801E6F04:
    // 0x801E6F04: lw          $at, 0x0($t3)
    ctx->r1 = MEM_W(ctx->r11, 0X0);
    // 0x801E6F08: addiu       $t3, $t3, 0xC
    ctx->r11 = ADD32(ctx->r11, 0XC);
    // 0x801E6F0C: addiu       $t4, $t4, 0xC
    ctx->r12 = ADD32(ctx->r12, 0XC);
    // 0x801E6F10: sw          $at, -0xC($t4)
    MEM_W(-0XC, ctx->r12) = ctx->r1;
    // 0x801E6F14: lw          $at, -0x8($t3)
    ctx->r1 = MEM_W(ctx->r11, -0X8);
    // 0x801E6F18: sw          $at, -0x8($t4)
    MEM_W(-0X8, ctx->r12) = ctx->r1;
    // 0x801E6F1C: lw          $at, -0x4($t3)
    ctx->r1 = MEM_W(ctx->r11, -0X4);
    // 0x801E6F20: bne         $t3, $t2, L_801E6F04
    if (ctx->r11 != ctx->r10) {
        // 0x801E6F24: sw          $at, -0x4($t4)
        MEM_W(-0X4, ctx->r12) = ctx->r1;
            goto L_801E6F04;
    }
    // 0x801E6F24: sw          $at, -0x4($t4)
    MEM_W(-0X4, ctx->r12) = ctx->r1;
    // 0x801E6F28: lw          $at, 0x0($t3)
    ctx->r1 = MEM_W(ctx->r11, 0X0);
    // 0x801E6F2C: addiu       $t5, $zero, 0x4
    ctx->r13 = ADD32(0, 0X4);
    // 0x801E6F30: addiu       $t6, $zero, 0x84
    ctx->r14 = ADD32(0, 0X84);
    // 0x801E6F34: sw          $at, 0x0($t4)
    MEM_W(0X0, ctx->r12) = ctx->r1;
    // 0x801E6F38: lw          $t2, 0x4($t3)
    ctx->r10 = MEM_W(ctx->r11, 0X4);
    // 0x801E6F3C: addiu       $t7, $zero, -0x28
    ctx->r15 = ADD32(0, -0X28);
    // 0x801E6F40: sw          $t2, 0x4($t4)
    MEM_W(0X4, ctx->r12) = ctx->r10;
    // 0x801E6F44: sh          $v0, 0x4($a0)
    MEM_H(0X4, ctx->r4) = ctx->r2;
    // 0x801E6F48: sh          $t5, 0x0($a0)
    MEM_H(0X0, ctx->r4) = ctx->r13;
    // 0x801E6F4C: sh          $zero, 0x2($a0)
    MEM_H(0X2, ctx->r4) = 0;
    // 0x801E6F50: sw          $t6, 0x8($a0)
    MEM_W(0X8, ctx->r4) = ctx->r14;
    // 0x801E6F54: sw          $t7, 0xC($a0)
    MEM_W(0XC, ctx->r4) = ctx->r15;
    // 0x801E6F58: sw          $a3, 0x28($a0)
    MEM_W(0X28, ctx->r4) = ctx->r7;
L_801E6F5C:
    // 0x801E6F5C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x801E6F60: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x801E6F64: jr          $ra
    // 0x801E6F68: nop

    return;
    // 0x801E6F68: nop

;}
RECOMP_FUNC void func_801E6F6C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801E6F6C: lui         $v1, 0x8023
    ctx->r3 = S32(0X8023 << 16);
    // 0x801E6F70: addiu       $v1, $v1, -0x76D0
    ctx->r3 = ADD32(ctx->r3, -0X76D0);
    // 0x801E6F74: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    // 0x801E6F78: addiu       $a0, $zero, 0x5
    ctx->r4 = ADD32(0, 0X5);
L_801E6F7C:
    // 0x801E6F7C: lhu         $t6, 0x0($v1)
    ctx->r14 = MEM_HU(ctx->r3, 0X0);
    // 0x801E6F80: beq         $t6, $zero, L_801E6F94
    if (ctx->r14 == 0) {
        // 0x801E6F84: nop
    
            goto L_801E6F94;
    }
    // 0x801E6F84: nop

    // 0x801E6F88: addiu       $v0, $v0, 0x1
    ctx->r2 = ADD32(ctx->r2, 0X1);
    // 0x801E6F8C: bne         $v0, $a0, L_801E6F7C
    if (ctx->r2 != ctx->r4) {
        // 0x801E6F90: addiu       $v1, $v1, 0x2C
        ctx->r3 = ADD32(ctx->r3, 0X2C);
            goto L_801E6F7C;
    }
    // 0x801E6F90: addiu       $v1, $v1, 0x2C
    ctx->r3 = ADD32(ctx->r3, 0X2C);
L_801E6F94:
    // 0x801E6F94: bne         $v0, $a0, L_801E6FA4
    if (ctx->r2 != ctx->r4) {
        // 0x801E6F98: or          $v1, $v0, $zero
        ctx->r3 = ctx->r2 | 0;
            goto L_801E6FA4;
    }
    // 0x801E6F98: or          $v1, $v0, $zero
    ctx->r3 = ctx->r2 | 0;
    // 0x801E6F9C: jr          $ra
    // 0x801E6FA0: addiu       $v0, $zero, -0x1
    ctx->r2 = ADD32(0, -0X1);
    return;
    // 0x801E6FA0: addiu       $v0, $zero, -0x1
    ctx->r2 = ADD32(0, -0X1);
L_801E6FA4:
    // 0x801E6FA4: jr          $ra
    // 0x801E6FA8: or          $v0, $v1, $zero
    ctx->r2 = ctx->r3 | 0;
    return;
    // 0x801E6FA8: or          $v0, $v1, $zero
    ctx->r2 = ctx->r3 | 0;
    // 0x801E6FAC: nop

;}
RECOMP_FUNC void FadeTransition_SetProps(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801E6FB0: lui         $t7, 0x8022
    ctx->r15 = S32(0X8022 << 16);
    // 0x801E6FB4: addiu       $t7, $t7, 0x6CC0
    ctx->r15 = ADD32(ctx->r15, 0X6CC0);
    // 0x801E6FB8: lui         $t6, 0x8023
    ctx->r14 = S32(0X8023 << 16);
    // 0x801E6FBC: addiu       $t6, $t6, -0x75F0
    ctx->r14 = ADD32(ctx->r14, -0X75F0);
    // 0x801E6FC0: addiu       $t0, $t7, 0x24
    ctx->r8 = ADD32(ctx->r15, 0X24);
L_801E6FC4:
    // 0x801E6FC4: lw          $at, 0x0($t7)
    ctx->r1 = MEM_W(ctx->r15, 0X0);
    // 0x801E6FC8: addiu       $t7, $t7, 0xC
    ctx->r15 = ADD32(ctx->r15, 0XC);
    // 0x801E6FCC: addiu       $t6, $t6, 0xC
    ctx->r14 = ADD32(ctx->r14, 0XC);
    // 0x801E6FD0: sw          $at, -0xC($t6)
    MEM_W(-0XC, ctx->r14) = ctx->r1;
    // 0x801E6FD4: lw          $at, -0x8($t7)
    ctx->r1 = MEM_W(ctx->r15, -0X8);
    // 0x801E6FD8: sw          $at, -0x8($t6)
    MEM_W(-0X8, ctx->r14) = ctx->r1;
    // 0x801E6FDC: lw          $at, -0x4($t7)
    ctx->r1 = MEM_W(ctx->r15, -0X4);
    // 0x801E6FE0: bne         $t7, $t0, L_801E6FC4
    if (ctx->r15 != ctx->r8) {
        // 0x801E6FE4: sw          $at, -0x4($t6)
        MEM_W(-0X4, ctx->r14) = ctx->r1;
            goto L_801E6FC4;
    }
    // 0x801E6FE4: sw          $at, -0x4($t6)
    MEM_W(-0X4, ctx->r14) = ctx->r1;
    // 0x801E6FE8: addiu       $t1, $a0, -0x1
    ctx->r9 = ADD32(ctx->r4, -0X1);
    // 0x801E6FEC: sltiu       $at, $t1, 0x7
    ctx->r1 = ctx->r9 < 0X7 ? 1 : 0;
    // 0x801E6FF0: beq         $at, $zero, L_801E71A0
    if (ctx->r1 == 0) {
        // 0x801E6FF4: sll         $t1, $t1, 2
        ctx->r9 = S32(ctx->r9 << 2);
            goto L_801E71A0;
    }
    // 0x801E6FF4: sll         $t1, $t1, 2
    ctx->r9 = S32(ctx->r9 << 2);
    // 0x801E6FF8: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E6FFC: addu        $at, $at, $t1
    gpr jr_addend_801E7004 = ctx->r9;
    ctx->r1 = ADD32(ctx->r1, ctx->r9);
    // 0x801E7000: lw          $t1, 0x6D10($at)
    ctx->r9 = ADD32(ctx->r1, 0X6D10);
    // 0x801E7004: jr          $t1
    // 0x801E7008: nop

    switch (jr_addend_801E7004 >> 2) {
        case 0: goto L_801E700C; break;
        case 1: goto L_801E7044; break;
        case 2: goto L_801E70C8; break;
        case 3: goto L_801E7114; break;
        case 4: goto L_801E715C; break;
        case 5: goto L_801E710C; break;
        case 6: goto L_801E7080; break;
        default: switch_error(__func__, 0x801E7004, 0x80226D10);
    }
    // 0x801E7008: nop

L_801E700C:
    // 0x801E700C: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801E7010: addiu       $t2, $zero, 0x1
    ctx->r10 = ADD32(0, 0X1);
    // 0x801E7014: sh          $t2, -0x75F0($at)
    MEM_H(-0X75F0, ctx->r1) = ctx->r10;
    // 0x801E7018: sh          $zero, -0x75EE($at)
    MEM_H(-0X75EE, ctx->r1) = 0;
    // 0x801E701C: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801E7020: sh          $a2, -0x75E6($at)
    MEM_H(-0X75E6, ctx->r1) = ctx->r6;
    // 0x801E7024: sh          $a1, -0x75E4($at)
    MEM_H(-0X75E4, ctx->r1) = ctx->r5;
    // 0x801E7028: sh          $zero, -0x75E2($at)
    MEM_H(-0X75E2, ctx->r1) = 0;
    // 0x801E702C: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801E7030: sh          $zero, -0x75E0($at)
    MEM_H(-0X75E0, ctx->r1) = 0;
    // 0x801E7034: sh          $zero, -0x75DE($at)
    MEM_H(-0X75DE, ctx->r1) = 0;
    // 0x801E7038: sh          $zero, -0x75DC($at)
    MEM_H(-0X75DC, ctx->r1) = 0;
    // 0x801E703C: jr          $ra
    // 0x801E7040: sh          $zero, -0x75DA($at)
    MEM_H(-0X75DA, ctx->r1) = 0;
    return;
    // 0x801E7040: sh          $zero, -0x75DA($at)
    MEM_H(-0X75DA, ctx->r1) = 0;
L_801E7044:
    // 0x801E7044: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801E7048: addiu       $t3, $zero, 0x2
    ctx->r11 = ADD32(0, 0X2);
    // 0x801E704C: sh          $t3, -0x75F0($at)
    MEM_H(-0X75F0, ctx->r1) = ctx->r11;
    // 0x801E7050: sh          $zero, -0x75EE($at)
    MEM_H(-0X75EE, ctx->r1) = 0;
    // 0x801E7054: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801E7058: sh          $a2, -0x75E6($at)
    MEM_H(-0X75E6, ctx->r1) = ctx->r6;
    // 0x801E705C: sh          $a1, -0x75E4($at)
    MEM_H(-0X75E4, ctx->r1) = ctx->r5;
    // 0x801E7060: sh          $zero, -0x75E2($at)
    MEM_H(-0X75E2, ctx->r1) = 0;
    // 0x801E7064: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801E7068: addiu       $t4, $zero, 0xFF
    ctx->r12 = ADD32(0, 0XFF);
    // 0x801E706C: sh          $zero, -0x75E0($at)
    MEM_H(-0X75E0, ctx->r1) = 0;
    // 0x801E7070: sh          $zero, -0x75DE($at)
    MEM_H(-0X75DE, ctx->r1) = 0;
    // 0x801E7074: sh          $zero, -0x75DC($at)
    MEM_H(-0X75DC, ctx->r1) = 0;
    // 0x801E7078: jr          $ra
    // 0x801E707C: sh          $t4, -0x75DA($at)
    MEM_H(-0X75DA, ctx->r1) = ctx->r12;
    return;
    // 0x801E707C: sh          $t4, -0x75DA($at)
    MEM_H(-0X75DA, ctx->r1) = ctx->r12;
L_801E7080:
    // 0x801E7080: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801E7084: addiu       $t5, $zero, 0x7
    ctx->r13 = ADD32(0, 0X7);
    // 0x801E7088: sh          $t5, -0x75F0($at)
    MEM_H(-0X75F0, ctx->r1) = ctx->r13;
    // 0x801E708C: sh          $zero, -0x75EE($at)
    MEM_H(-0X75EE, ctx->r1) = 0;
    // 0x801E7090: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801E7094: sh          $a2, -0x75E6($at)
    MEM_H(-0X75E6, ctx->r1) = ctx->r6;
    // 0x801E7098: sh          $a1, -0x75E4($at)
    MEM_H(-0X75E4, ctx->r1) = ctx->r5;
    // 0x801E709C: sh          $zero, -0x75E2($at)
    MEM_H(-0X75E2, ctx->r1) = 0;
    // 0x801E70A0: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801E70A4: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x801E70A8: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x801E70AC: addiu       $t0, $zero, 0xFF
    ctx->r8 = ADD32(0, 0XFF);
    // 0x801E70B0: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x801E70B4: sh          $t0, -0x75DC($at)
    MEM_H(-0X75DC, ctx->r1) = ctx->r8;
    // 0x801E70B8: sh          $t8, -0x75DE($at)
    MEM_H(-0X75DE, ctx->r1) = ctx->r24;
    // 0x801E70BC: sh          $t9, -0x75E0($at)
    MEM_H(-0X75E0, ctx->r1) = ctx->r25;
    // 0x801E70C0: jr          $ra
    // 0x801E70C4: sh          $t7, -0x75DA($at)
    MEM_H(-0X75DA, ctx->r1) = ctx->r15;
    return;
    // 0x801E70C4: sh          $t7, -0x75DA($at)
    MEM_H(-0X75DA, ctx->r1) = ctx->r15;
L_801E70C8:
    // 0x801E70C8: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801E70CC: addiu       $t6, $zero, 0x3
    ctx->r14 = ADD32(0, 0X3);
    // 0x801E70D0: sh          $t6, -0x75F0($at)
    MEM_H(-0X75F0, ctx->r1) = ctx->r14;
    // 0x801E70D4: sh          $zero, -0x75EE($at)
    MEM_H(-0X75EE, ctx->r1) = 0;
    // 0x801E70D8: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801E70DC: sh          $a2, -0x75E6($at)
    MEM_H(-0X75E6, ctx->r1) = ctx->r6;
    // 0x801E70E0: sh          $a1, -0x75E4($at)
    MEM_H(-0X75E4, ctx->r1) = ctx->r5;
    // 0x801E70E4: sh          $zero, -0x75E2($at)
    MEM_H(-0X75E2, ctx->r1) = 0;
    // 0x801E70E8: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801E70EC: addiu       $t1, $zero, 0xFF
    ctx->r9 = ADD32(0, 0XFF);
    // 0x801E70F0: addiu       $t2, $zero, 0xFF
    ctx->r10 = ADD32(0, 0XFF);
    // 0x801E70F4: addiu       $t3, $zero, 0xFF
    ctx->r11 = ADD32(0, 0XFF);
    // 0x801E70F8: sh          $t3, -0x75DC($at)
    MEM_H(-0X75DC, ctx->r1) = ctx->r11;
    // 0x801E70FC: sh          $t2, -0x75DE($at)
    MEM_H(-0X75DE, ctx->r1) = ctx->r10;
    // 0x801E7100: sh          $t1, -0x75E0($at)
    MEM_H(-0X75E0, ctx->r1) = ctx->r9;
    // 0x801E7104: jr          $ra
    // 0x801E7108: sh          $zero, -0x75DA($at)
    MEM_H(-0X75DA, ctx->r1) = 0;
    return;
    // 0x801E7108: sh          $zero, -0x75DA($at)
    MEM_H(-0X75DA, ctx->r1) = 0;
L_801E710C:
    // 0x801E710C: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801E7110: sh          $zero, -0x75D0($at)
    MEM_H(-0X75D0, ctx->r1) = 0;
L_801E7114:
    // 0x801E7114: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801E7118: addiu       $t4, $zero, 0x4
    ctx->r12 = ADD32(0, 0X4);
    // 0x801E711C: sh          $t4, -0x75F0($at)
    MEM_H(-0X75F0, ctx->r1) = ctx->r12;
    // 0x801E7120: sh          $zero, -0x75EE($at)
    MEM_H(-0X75EE, ctx->r1) = 0;
    // 0x801E7124: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801E7128: addiu       $t5, $zero, 0x1
    ctx->r13 = ADD32(0, 0X1);
    // 0x801E712C: sh          $a2, -0x75E6($at)
    MEM_H(-0X75E6, ctx->r1) = ctx->r6;
    // 0x801E7130: sh          $a1, -0x75E4($at)
    MEM_H(-0X75E4, ctx->r1) = ctx->r5;
    // 0x801E7134: sh          $t5, -0x75E2($at)
    MEM_H(-0X75E2, ctx->r1) = ctx->r13;
    // 0x801E7138: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801E713C: addiu       $t9, $zero, 0x46
    ctx->r25 = ADD32(0, 0X46);
    // 0x801E7140: addiu       $t8, $zero, 0x41
    ctx->r24 = ADD32(0, 0X41);
    // 0x801E7144: sh          $t9, -0x75D8($at)
    MEM_H(-0X75D8, ctx->r1) = ctx->r25;
    // 0x801E7148: sh          $t8, -0x75D6($at)
    MEM_H(-0X75D6, ctx->r1) = ctx->r24;
    // 0x801E714C: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801E7150: addiu       $t0, $zero, 0x1
    ctx->r8 = ADD32(0, 0X1);
    // 0x801E7154: jr          $ra
    // 0x801E7158: sh          $t0, -0x75CE($at)
    MEM_H(-0X75CE, ctx->r1) = ctx->r8;
    return;
    // 0x801E7158: sh          $t0, -0x75CE($at)
    MEM_H(-0X75CE, ctx->r1) = ctx->r8;
L_801E715C:
    // 0x801E715C: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801E7160: addiu       $t7, $zero, 0x5
    ctx->r15 = ADD32(0, 0X5);
    // 0x801E7164: sh          $t7, -0x75F0($at)
    MEM_H(-0X75F0, ctx->r1) = ctx->r15;
    // 0x801E7168: sh          $zero, -0x75EE($at)
    MEM_H(-0X75EE, ctx->r1) = 0;
    // 0x801E716C: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801E7170: addiu       $t6, $zero, 0x1
    ctx->r14 = ADD32(0, 0X1);
    // 0x801E7174: sh          $a2, -0x75E6($at)
    MEM_H(-0X75E6, ctx->r1) = ctx->r6;
    // 0x801E7178: sh          $a1, -0x75E4($at)
    MEM_H(-0X75E4, ctx->r1) = ctx->r5;
    // 0x801E717C: sh          $t6, -0x75E2($at)
    MEM_H(-0X75E2, ctx->r1) = ctx->r14;
    // 0x801E7180: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801E7184: addiu       $t1, $zero, -0x109
    ctx->r9 = ADD32(0, -0X109);
    // 0x801E7188: addiu       $t2, $zero, 0x41
    ctx->r10 = ADD32(0, 0X41);
    // 0x801E718C: sh          $t1, -0x75D8($at)
    MEM_H(-0X75D8, ctx->r1) = ctx->r9;
    // 0x801E7190: sh          $t2, -0x75D6($at)
    MEM_H(-0X75D6, ctx->r1) = ctx->r10;
    // 0x801E7194: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801E7198: addiu       $t3, $zero, 0x1
    ctx->r11 = ADD32(0, 0X1);
    // 0x801E719C: sh          $t3, -0x75CE($at)
    MEM_H(-0X75CE, ctx->r1) = ctx->r11;
L_801E71A0:
    // 0x801E71A0: jr          $ra
    // 0x801E71A4: nop

    return;
    // 0x801E71A4: nop

;}
RECOMP_FUNC void func_801E71A8(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801E71A8: lui         $a0, 0x8023
    ctx->r4 = S32(0X8023 << 16);
    // 0x801E71AC: addiu       $a0, $a0, -0x75F0
    ctx->r4 = ADD32(ctx->r4, -0X75F0);
    // 0x801E71B0: lh          $t6, 0x6($a0)
    ctx->r14 = MEM_H(ctx->r4, 0X6);
    // 0x801E71B4: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x801E71B8: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x801E71BC: bne         $t6, $at, L_801E71CC
    if (ctx->r14 != ctx->r1) {
        // 0x801E71C0: sw          $ra, 0x14($sp)
        MEM_W(0X14, ctx->r29) = ctx->r31;
            goto L_801E71CC;
    }
    // 0x801E71C0: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x801E71C4: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801E71C8: sh          $zero, -0x75EA($at)
    MEM_H(-0X75EA, ctx->r1) = 0;
L_801E71CC:
    // 0x801E71CC: lui         $t7, 0x8023
    ctx->r15 = S32(0X8023 << 16);
    // 0x801E71D0: lh          $t7, -0x75F0($t7)
    ctx->r15 = MEM_H(ctx->r15, -0X75F0);
    // 0x801E71D4: addiu       $t8, $t7, -0x1
    ctx->r24 = ADD32(ctx->r15, -0X1);
    // 0x801E71D8: sltiu       $at, $t8, 0x7
    ctx->r1 = ctx->r24 < 0X7 ? 1 : 0;
    // 0x801E71DC: beq         $at, $zero, L_801E7270
    if (ctx->r1 == 0) {
        // 0x801E71E0: sll         $t8, $t8, 2
        ctx->r24 = S32(ctx->r24 << 2);
            goto L_801E7270;
    }
    // 0x801E71E0: sll         $t8, $t8, 2
    ctx->r24 = S32(ctx->r24 << 2);
    // 0x801E71E4: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E71E8: addu        $at, $at, $t8
    gpr jr_addend_801E71F0 = ctx->r24;
    ctx->r1 = ADD32(ctx->r1, ctx->r24);
    // 0x801E71EC: lw          $t8, 0x6D2C($at)
    ctx->r24 = ADD32(ctx->r1, 0X6D2C);
    // 0x801E71F0: jr          $t8
    // 0x801E71F4: nop

    switch (jr_addend_801E71F0 >> 2) {
        case 0: goto L_801E71F8; break;
        case 1: goto L_801E7218; break;
        case 2: goto L_801E71F8; break;
        case 3: goto L_801E7238; break;
        case 4: goto L_801E7258; break;
        case 5: goto L_801E7238; break;
        case 6: goto L_801E7218; break;
        default: switch_error(__func__, 0x801E71F0, 0x80226D2C);
    }
    // 0x801E71F4: nop

L_801E71F8:
    // 0x801E71F8: addiu       $t9, $zero, 0x1
    ctx->r25 = ADD32(0, 0X1);
    // 0x801E71FC: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801E7200: addiu       $t0, $zero, 0x2
    ctx->r8 = ADD32(0, 0X2);
    // 0x801E7204: sh          $t9, -0x75EC($at)
    MEM_H(-0X75EC, ctx->r1) = ctx->r25;
    // 0x801E7208: jal         0x801E7280
    // 0x801E720C: sh          $t0, -0x75EA($at)
    MEM_H(-0X75EA, ctx->r1) = ctx->r8;
    func_801E7280(rdram, ctx);
        goto after_0;
    // 0x801E720C: sh          $t0, -0x75EA($at)
    MEM_H(-0X75EA, ctx->r1) = ctx->r8;
    after_0:
    // 0x801E7210: b           L_801E7274
    // 0x801E7214: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_801E7274;
    // 0x801E7214: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_801E7218:
    // 0x801E7218: addiu       $t1, $zero, 0x1
    ctx->r9 = ADD32(0, 0X1);
    // 0x801E721C: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801E7220: addiu       $t2, $zero, 0x2
    ctx->r10 = ADD32(0, 0X2);
    // 0x801E7224: sh          $t1, -0x75EC($at)
    MEM_H(-0X75EC, ctx->r1) = ctx->r9;
    // 0x801E7228: jal         0x801E73A0
    // 0x801E722C: sh          $t2, -0x75EA($at)
    MEM_H(-0X75EA, ctx->r1) = ctx->r10;
    func_801E73A0(rdram, ctx);
        goto after_1;
    // 0x801E722C: sh          $t2, -0x75EA($at)
    MEM_H(-0X75EA, ctx->r1) = ctx->r10;
    after_1:
    // 0x801E7230: b           L_801E7274
    // 0x801E7234: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_801E7274;
    // 0x801E7234: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_801E7238:
    // 0x801E7238: addiu       $t3, $zero, 0x1
    ctx->r11 = ADD32(0, 0X1);
    // 0x801E723C: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801E7240: addiu       $t4, $zero, 0x2
    ctx->r12 = ADD32(0, 0X2);
    // 0x801E7244: sh          $t3, -0x75EC($at)
    MEM_H(-0X75EC, ctx->r1) = ctx->r11;
    // 0x801E7248: jal         0x801E74BC
    // 0x801E724C: sh          $t4, -0x75EA($at)
    MEM_H(-0X75EA, ctx->r1) = ctx->r12;
    func_801E74BC(rdram, ctx);
        goto after_2;
    // 0x801E724C: sh          $t4, -0x75EA($at)
    MEM_H(-0X75EA, ctx->r1) = ctx->r12;
    after_2:
    // 0x801E7250: b           L_801E7274
    // 0x801E7254: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_801E7274;
    // 0x801E7254: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_801E7258:
    // 0x801E7258: addiu       $t5, $zero, 0x1
    ctx->r13 = ADD32(0, 0X1);
    // 0x801E725C: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801E7260: addiu       $t6, $zero, 0x2
    ctx->r14 = ADD32(0, 0X2);
    // 0x801E7264: sh          $t5, -0x75EC($at)
    MEM_H(-0X75EC, ctx->r1) = ctx->r13;
    // 0x801E7268: jal         0x801E76C0
    // 0x801E726C: sh          $t6, -0x75EA($at)
    MEM_H(-0X75EA, ctx->r1) = ctx->r14;
    func_801E76C0(rdram, ctx);
        goto after_3;
    // 0x801E726C: sh          $t6, -0x75EA($at)
    MEM_H(-0X75EA, ctx->r1) = ctx->r14;
    after_3:
L_801E7270:
    // 0x801E7270: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_801E7274:
    // 0x801E7274: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x801E7278: jr          $ra
    // 0x801E727C: nop

    return;
    // 0x801E727C: nop

;}
RECOMP_FUNC void func_801E7280(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801E7280: lh          $v0, 0x2($a0)
    ctx->r2 = MEM_H(ctx->r4, 0X2);
    // 0x801E7284: addiu       $v1, $zero, 0x1
    ctx->r3 = ADD32(0, 0X1);
    // 0x801E7288: beql        $v0, $zero, L_801E72AC
    if (ctx->r2 == 0) {
        // 0x801E728C: lh          $v0, 0x8($a0)
        ctx->r2 = MEM_H(ctx->r4, 0X8);
            goto L_801E72AC;
    }
    goto skip_0;
    // 0x801E728C: lh          $v0, 0x8($a0)
    ctx->r2 = MEM_H(ctx->r4, 0X8);
    skip_0:
    // 0x801E7290: beq         $v0, $v1, L_801E72DC
    if (ctx->r2 == ctx->r3) {
        // 0x801E7294: addiu       $at, $zero, 0x2
        ctx->r1 = ADD32(0, 0X2);
            goto L_801E72DC;
    }
    // 0x801E7294: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x801E7298: beql        $v0, $at, L_801E7344
    if (ctx->r2 == ctx->r1) {
        // 0x801E729C: lh          $v0, 0x8($a0)
        ctx->r2 = MEM_H(ctx->r4, 0X8);
            goto L_801E7344;
    }
    goto skip_1;
    // 0x801E729C: lh          $v0, 0x8($a0)
    ctx->r2 = MEM_H(ctx->r4, 0X8);
    skip_1:
    // 0x801E72A0: jr          $ra
    // 0x801E72A4: nop

    return;
    // 0x801E72A4: nop

    // 0x801E72A8: lh          $v0, 0x8($a0)
    ctx->r2 = MEM_H(ctx->r4, 0X8);
L_801E72AC:
    // 0x801E72AC: lh          $t6, 0xA($a0)
    ctx->r14 = MEM_H(ctx->r4, 0XA);
    // 0x801E72B0: addiu       $v1, $zero, 0x1
    ctx->r3 = ADD32(0, 0X1);
    // 0x801E72B4: addiu       $t7, $v0, 0x1
    ctx->r15 = ADD32(ctx->r2, 0X1);
    // 0x801E72B8: slt         $at, $v0, $t6
    ctx->r1 = SIGNED(ctx->r2) < SIGNED(ctx->r14) ? 1 : 0;
    // 0x801E72BC: bnel        $at, $zero, L_801E72D4
    if (ctx->r1 != 0) {
        // 0x801E72C0: sh          $zero, 0x16($a0)
        MEM_H(0X16, ctx->r4) = 0;
            goto L_801E72D4;
    }
    goto skip_2;
    // 0x801E72C0: sh          $zero, 0x16($a0)
    MEM_H(0X16, ctx->r4) = 0;
    skip_2:
    // 0x801E72C4: sh          $v1, 0x2($a0)
    MEM_H(0X2, ctx->r4) = ctx->r3;
    // 0x801E72C8: jr          $ra
    // 0x801E72CC: sh          $zero, 0x8($a0)
    MEM_H(0X8, ctx->r4) = 0;
    return;
    // 0x801E72CC: sh          $zero, 0x8($a0)
    MEM_H(0X8, ctx->r4) = 0;
    // 0x801E72D0: sh          $zero, 0x16($a0)
    MEM_H(0X16, ctx->r4) = 0;
L_801E72D4:
    // 0x801E72D4: jr          $ra
    // 0x801E72D8: sh          $t7, 0x8($a0)
    MEM_H(0X8, ctx->r4) = ctx->r15;
    return;
    // 0x801E72D8: sh          $t7, 0x8($a0)
    MEM_H(0X8, ctx->r4) = ctx->r15;
L_801E72DC:
    // 0x801E72DC: lh          $v1, 0xC($a0)
    ctx->r3 = MEM_H(ctx->r4, 0XC);
    // 0x801E72E0: lh          $v0, 0x8($a0)
    ctx->r2 = MEM_H(ctx->r4, 0X8);
    // 0x801E72E4: addiu       $t1, $zero, 0x2
    ctx->r9 = ADD32(0, 0X2);
    // 0x801E72E8: addiu       $t2, $zero, 0xFF
    ctx->r10 = ADD32(0, 0XFF);
    // 0x801E72EC: slt         $at, $v1, $v0
    ctx->r1 = SIGNED(ctx->r3) < SIGNED(ctx->r2) ? 1 : 0;
    // 0x801E72F0: bnel        $at, $zero, L_801E7334
    if (ctx->r1 != 0) {
        // 0x801E72F4: sh          $t1, 0x2($a0)
        MEM_H(0X2, ctx->r4) = ctx->r9;
            goto L_801E7334;
    }
    goto skip_3;
    // 0x801E72F4: sh          $t1, 0x2($a0)
    MEM_H(0X2, ctx->r4) = ctx->r9;
    skip_3:
    // 0x801E72F8: mtc1        $v0, $f4
    ctx->f4.u32l = ctx->r2;
    // 0x801E72FC: lui         $at, 0x437F
    ctx->r1 = S32(0X437F << 16);
    // 0x801E7300: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x801E7304: cvt.s.w     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
    // 0x801E7308: mtc1        $v1, $f16
    ctx->f16.u32l = ctx->r3;
    // 0x801E730C: addiu       $t0, $v0, 0x1
    ctx->r8 = ADD32(ctx->r2, 0X1);
    // 0x801E7310: sh          $t0, 0x8($a0)
    MEM_H(0X8, ctx->r4) = ctx->r8;
    // 0x801E7314: cvt.s.w     $f18, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    ctx->f18.fl = CVT_S_W(ctx->f16.u32l);
    // 0x801E7318: mul.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = MUL_S(ctx->f6.fl, ctx->f8.fl);
    // 0x801E731C: div.s       $f4, $f10, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f4.fl = DIV_S(ctx->f10.fl, ctx->f18.fl);
    // 0x801E7320: trunc.w.s   $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.u32l = TRUNC_W_S(ctx->f4.fl);
    // 0x801E7324: mfc1        $t9, $f6
    ctx->r25 = (int32_t)ctx->f6.u32l;
    // 0x801E7328: jr          $ra
    // 0x801E732C: sh          $t9, 0x16($a0)
    MEM_H(0X16, ctx->r4) = ctx->r25;
    return;
    // 0x801E732C: sh          $t9, 0x16($a0)
    MEM_H(0X16, ctx->r4) = ctx->r25;
    // 0x801E7330: sh          $t1, 0x2($a0)
    MEM_H(0X2, ctx->r4) = ctx->r9;
L_801E7334:
    // 0x801E7334: sh          $zero, 0x8($a0)
    MEM_H(0X8, ctx->r4) = 0;
    // 0x801E7338: jr          $ra
    // 0x801E733C: sh          $t2, 0x16($a0)
    MEM_H(0X16, ctx->r4) = ctx->r10;
    return;
    // 0x801E733C: sh          $t2, 0x16($a0)
    MEM_H(0X16, ctx->r4) = ctx->r10;
    // 0x801E7340: lh          $v0, 0x8($a0)
    ctx->r2 = MEM_H(ctx->r4, 0X8);
L_801E7344:
    // 0x801E7344: lh          $t3, 0xE($a0)
    ctx->r11 = MEM_H(ctx->r4, 0XE);
    // 0x801E7348: lui         $t4, 0x8023
    ctx->r12 = S32(0X8023 << 16);
    // 0x801E734C: addiu       $t4, $t4, -0x75F0
    ctx->r12 = ADD32(ctx->r12, -0X75F0);
    // 0x801E7350: slt         $at, $v0, $t3
    ctx->r1 = SIGNED(ctx->r2) < SIGNED(ctx->r11) ? 1 : 0;
    // 0x801E7354: bne         $at, $zero, L_801E7394
    if (ctx->r1 != 0) {
        // 0x801E7358: addiu       $t8, $v0, 0x1
        ctx->r24 = ADD32(ctx->r2, 0X1);
            goto L_801E7394;
    }
    // 0x801E7358: addiu       $t8, $v0, 0x1
    ctx->r24 = ADD32(ctx->r2, 0X1);
    // 0x801E735C: lui         $t5, 0x8022
    ctx->r13 = S32(0X8022 << 16);
    // 0x801E7360: addiu       $t5, $t5, 0x6CC0
    ctx->r13 = ADD32(ctx->r13, 0X6CC0);
    // 0x801E7364: addiu       $t7, $t5, 0x24
    ctx->r15 = ADD32(ctx->r13, 0X24);
L_801E7368:
    // 0x801E7368: lw          $at, 0x0($t5)
    ctx->r1 = MEM_W(ctx->r13, 0X0);
    // 0x801E736C: addiu       $t5, $t5, 0xC
    ctx->r13 = ADD32(ctx->r13, 0XC);
    // 0x801E7370: addiu       $t4, $t4, 0xC
    ctx->r12 = ADD32(ctx->r12, 0XC);
    // 0x801E7374: sw          $at, -0xC($t4)
    MEM_W(-0XC, ctx->r12) = ctx->r1;
    // 0x801E7378: lw          $at, -0x8($t5)
    ctx->r1 = MEM_W(ctx->r13, -0X8);
    // 0x801E737C: sw          $at, -0x8($t4)
    MEM_W(-0X8, ctx->r12) = ctx->r1;
    // 0x801E7380: lw          $at, -0x4($t5)
    ctx->r1 = MEM_W(ctx->r13, -0X4);
    // 0x801E7384: bne         $t5, $t7, L_801E7368
    if (ctx->r13 != ctx->r15) {
        // 0x801E7388: sw          $at, -0x4($t4)
        MEM_W(-0X4, ctx->r12) = ctx->r1;
            goto L_801E7368;
    }
    // 0x801E7388: sw          $at, -0x4($t4)
    MEM_W(-0X4, ctx->r12) = ctx->r1;
    // 0x801E738C: jr          $ra
    // 0x801E7390: sh          $v1, 0x6($a0)
    MEM_H(0X6, ctx->r4) = ctx->r3;
    return;
    // 0x801E7390: sh          $v1, 0x6($a0)
    MEM_H(0X6, ctx->r4) = ctx->r3;
L_801E7394:
    // 0x801E7394: sh          $t8, 0x8($a0)
    MEM_H(0X8, ctx->r4) = ctx->r24;
    // 0x801E7398: jr          $ra
    // 0x801E739C: nop

    return;
    // 0x801E739C: nop

;}
RECOMP_FUNC void func_801E73A0(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801E73A0: lh          $v0, 0x2($a0)
    ctx->r2 = MEM_H(ctx->r4, 0X2);
    // 0x801E73A4: addiu       $v1, $zero, 0x1
    ctx->r3 = ADD32(0, 0X1);
    // 0x801E73A8: beql        $v0, $zero, L_801E73CC
    if (ctx->r2 == 0) {
        // 0x801E73AC: lh          $v0, 0x8($a0)
        ctx->r2 = MEM_H(ctx->r4, 0X8);
            goto L_801E73CC;
    }
    goto skip_0;
    // 0x801E73AC: lh          $v0, 0x8($a0)
    ctx->r2 = MEM_H(ctx->r4, 0X8);
    skip_0:
    // 0x801E73B0: beq         $v0, $v1, L_801E73FC
    if (ctx->r2 == ctx->r3) {
        // 0x801E73B4: addiu       $at, $zero, 0x2
        ctx->r1 = ADD32(0, 0X2);
            goto L_801E73FC;
    }
    // 0x801E73B4: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x801E73B8: beql        $v0, $at, L_801E7460
    if (ctx->r2 == ctx->r1) {
        // 0x801E73BC: lh          $v0, 0x8($a0)
        ctx->r2 = MEM_H(ctx->r4, 0X8);
            goto L_801E7460;
    }
    goto skip_1;
    // 0x801E73BC: lh          $v0, 0x8($a0)
    ctx->r2 = MEM_H(ctx->r4, 0X8);
    skip_1:
    // 0x801E73C0: jr          $ra
    // 0x801E73C4: nop

    return;
    // 0x801E73C4: nop

    // 0x801E73C8: lh          $v0, 0x8($a0)
    ctx->r2 = MEM_H(ctx->r4, 0X8);
L_801E73CC:
    // 0x801E73CC: lh          $t6, 0xA($a0)
    ctx->r14 = MEM_H(ctx->r4, 0XA);
    // 0x801E73D0: addiu       $v1, $zero, 0x1
    ctx->r3 = ADD32(0, 0X1);
    // 0x801E73D4: addiu       $t7, $v0, 0x1
    ctx->r15 = ADD32(ctx->r2, 0X1);
    // 0x801E73D8: slt         $at, $v0, $t6
    ctx->r1 = SIGNED(ctx->r2) < SIGNED(ctx->r14) ? 1 : 0;
    // 0x801E73DC: bnel        $at, $zero, L_801E73F4
    if (ctx->r1 != 0) {
        // 0x801E73E0: sh          $zero, 0x16($a0)
        MEM_H(0X16, ctx->r4) = 0;
            goto L_801E73F4;
    }
    goto skip_2;
    // 0x801E73E0: sh          $zero, 0x16($a0)
    MEM_H(0X16, ctx->r4) = 0;
    skip_2:
    // 0x801E73E4: sh          $v1, 0x2($a0)
    MEM_H(0X2, ctx->r4) = ctx->r3;
    // 0x801E73E8: jr          $ra
    // 0x801E73EC: sh          $zero, 0x8($a0)
    MEM_H(0X8, ctx->r4) = 0;
    return;
    // 0x801E73EC: sh          $zero, 0x8($a0)
    MEM_H(0X8, ctx->r4) = 0;
    // 0x801E73F0: sh          $zero, 0x16($a0)
    MEM_H(0X16, ctx->r4) = 0;
L_801E73F4:
    // 0x801E73F4: jr          $ra
    // 0x801E73F8: sh          $t7, 0x8($a0)
    MEM_H(0X8, ctx->r4) = ctx->r15;
    return;
    // 0x801E73F8: sh          $t7, 0x8($a0)
    MEM_H(0X8, ctx->r4) = ctx->r15;
L_801E73FC:
    // 0x801E73FC: lh          $v1, 0xC($a0)
    ctx->r3 = MEM_H(ctx->r4, 0XC);
    // 0x801E7400: lh          $v0, 0x8($a0)
    ctx->r2 = MEM_H(ctx->r4, 0X8);
    // 0x801E7404: addiu       $t2, $zero, 0x2
    ctx->r10 = ADD32(0, 0X2);
    // 0x801E7408: slt         $at, $v1, $v0
    ctx->r1 = SIGNED(ctx->r3) < SIGNED(ctx->r2) ? 1 : 0;
    // 0x801E740C: bne         $at, $zero, L_801E744C
    if (ctx->r1 != 0) {
        // 0x801E7410: subu        $t8, $v1, $v0
        ctx->r24 = SUB32(ctx->r3, ctx->r2);
            goto L_801E744C;
    }
    // 0x801E7410: subu        $t8, $v1, $v0
    ctx->r24 = SUB32(ctx->r3, ctx->r2);
    // 0x801E7414: mtc1        $t8, $f4
    ctx->f4.u32l = ctx->r24;
    // 0x801E7418: mtc1        $v1, $f8
    ctx->f8.u32l = ctx->r3;
    // 0x801E741C: lui         $at, 0x437F
    ctx->r1 = S32(0X437F << 16);
    // 0x801E7420: cvt.s.w     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
    // 0x801E7424: mtc1        $at, $f18
    ctx->f18.u32l = ctx->r1;
    // 0x801E7428: addiu       $t1, $v0, 0x1
    ctx->r9 = ADD32(ctx->r2, 0X1);
    // 0x801E742C: sh          $t1, 0x8($a0)
    MEM_H(0X8, ctx->r4) = ctx->r9;
    // 0x801E7430: cvt.s.w     $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.fl = CVT_S_W(ctx->f8.u32l);
    // 0x801E7434: div.s       $f16, $f6, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f16.fl = DIV_S(ctx->f6.fl, ctx->f10.fl);
    // 0x801E7438: mul.s       $f4, $f16, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f4.fl = MUL_S(ctx->f16.fl, ctx->f18.fl);
    // 0x801E743C: trunc.w.s   $f8, $f4
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    ctx->f8.u32l = TRUNC_W_S(ctx->f4.fl);
    // 0x801E7440: mfc1        $t0, $f8
    ctx->r8 = (int32_t)ctx->f8.u32l;
    // 0x801E7444: jr          $ra
    // 0x801E7448: sh          $t0, 0x16($a0)
    MEM_H(0X16, ctx->r4) = ctx->r8;
    return;
    // 0x801E7448: sh          $t0, 0x16($a0)
    MEM_H(0X16, ctx->r4) = ctx->r8;
L_801E744C:
    // 0x801E744C: sh          $t2, 0x2($a0)
    MEM_H(0X2, ctx->r4) = ctx->r10;
    // 0x801E7450: sh          $zero, 0x8($a0)
    MEM_H(0X8, ctx->r4) = 0;
    // 0x801E7454: jr          $ra
    // 0x801E7458: sh          $zero, 0x16($a0)
    MEM_H(0X16, ctx->r4) = 0;
    return;
    // 0x801E7458: sh          $zero, 0x16($a0)
    MEM_H(0X16, ctx->r4) = 0;
    // 0x801E745C: lh          $v0, 0x8($a0)
    ctx->r2 = MEM_H(ctx->r4, 0X8);
L_801E7460:
    // 0x801E7460: lh          $t3, 0xE($a0)
    ctx->r11 = MEM_H(ctx->r4, 0XE);
    // 0x801E7464: lui         $t4, 0x8023
    ctx->r12 = S32(0X8023 << 16);
    // 0x801E7468: addiu       $t4, $t4, -0x75F0
    ctx->r12 = ADD32(ctx->r12, -0X75F0);
    // 0x801E746C: slt         $at, $v0, $t3
    ctx->r1 = SIGNED(ctx->r2) < SIGNED(ctx->r11) ? 1 : 0;
    // 0x801E7470: bne         $at, $zero, L_801E74B0
    if (ctx->r1 != 0) {
        // 0x801E7474: addiu       $t8, $v0, 0x1
        ctx->r24 = ADD32(ctx->r2, 0X1);
            goto L_801E74B0;
    }
    // 0x801E7474: addiu       $t8, $v0, 0x1
    ctx->r24 = ADD32(ctx->r2, 0X1);
    // 0x801E7478: lui         $t5, 0x8022
    ctx->r13 = S32(0X8022 << 16);
    // 0x801E747C: addiu       $t5, $t5, 0x6CC0
    ctx->r13 = ADD32(ctx->r13, 0X6CC0);
    // 0x801E7480: addiu       $t7, $t5, 0x24
    ctx->r15 = ADD32(ctx->r13, 0X24);
L_801E7484:
    // 0x801E7484: lw          $at, 0x0($t5)
    ctx->r1 = MEM_W(ctx->r13, 0X0);
    // 0x801E7488: addiu       $t5, $t5, 0xC
    ctx->r13 = ADD32(ctx->r13, 0XC);
    // 0x801E748C: addiu       $t4, $t4, 0xC
    ctx->r12 = ADD32(ctx->r12, 0XC);
    // 0x801E7490: sw          $at, -0xC($t4)
    MEM_W(-0XC, ctx->r12) = ctx->r1;
    // 0x801E7494: lw          $at, -0x8($t5)
    ctx->r1 = MEM_W(ctx->r13, -0X8);
    // 0x801E7498: sw          $at, -0x8($t4)
    MEM_W(-0X8, ctx->r12) = ctx->r1;
    // 0x801E749C: lw          $at, -0x4($t5)
    ctx->r1 = MEM_W(ctx->r13, -0X4);
    // 0x801E74A0: bne         $t5, $t7, L_801E7484
    if (ctx->r13 != ctx->r15) {
        // 0x801E74A4: sw          $at, -0x4($t4)
        MEM_W(-0X4, ctx->r12) = ctx->r1;
            goto L_801E7484;
    }
    // 0x801E74A4: sw          $at, -0x4($t4)
    MEM_W(-0X4, ctx->r12) = ctx->r1;
    // 0x801E74A8: jr          $ra
    // 0x801E74AC: sh          $v1, 0x6($a0)
    MEM_H(0X6, ctx->r4) = ctx->r3;
    return;
    // 0x801E74AC: sh          $v1, 0x6($a0)
    MEM_H(0X6, ctx->r4) = ctx->r3;
L_801E74B0:
    // 0x801E74B0: sh          $t8, 0x8($a0)
    MEM_H(0X8, ctx->r4) = ctx->r24;
    // 0x801E74B4: jr          $ra
    // 0x801E74B8: nop

    return;
    // 0x801E74B8: nop

;}
RECOMP_FUNC void func_801E74BC(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801E74BC: addiu       $sp, $sp, -0x40
    ctx->r29 = ADD32(ctx->r29, -0X40);
    // 0x801E74C0: sw          $ra, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r31;
    // 0x801E74C4: sw          $s0, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r16;
    // 0x801E74C8: lh          $v0, 0x2($a0)
    ctx->r2 = MEM_H(ctx->r4, 0X2);
    // 0x801E74CC: or          $s0, $a0, $zero
    ctx->r16 = ctx->r4 | 0;
    // 0x801E74D0: mtc1        $zero, $f0
    ctx->f0.u32l = 0;
    // 0x801E74D4: beq         $v0, $zero, L_801E74F8
    if (ctx->r2 == 0) {
        // 0x801E74D8: lui         $a0, 0x801D
        ctx->r4 = S32(0X801D << 16);
            goto L_801E74F8;
    }
    // 0x801E74D8: lui         $a0, 0x801D
    ctx->r4 = S32(0X801D << 16);
    // 0x801E74DC: addiu       $v1, $zero, 0x1
    ctx->r3 = ADD32(0, 0X1);
    // 0x801E74E0: beq         $v0, $v1, L_801E7528
    if (ctx->r2 == ctx->r3) {
        // 0x801E74E4: addiu       $at, $zero, 0x2
        ctx->r1 = ADD32(0, 0X2);
            goto L_801E7528;
    }
    // 0x801E74E4: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x801E74E8: beql        $v0, $at, L_801E7584
    if (ctx->r2 == ctx->r1) {
        // 0x801E74EC: lh          $v0, 0x8($s0)
        ctx->r2 = MEM_H(ctx->r16, 0X8);
            goto L_801E7584;
    }
    goto skip_0;
    // 0x801E74EC: lh          $v0, 0x8($s0)
    ctx->r2 = MEM_H(ctx->r16, 0X8);
    skip_0:
    // 0x801E74F0: b           L_801E75DC
    // 0x801E74F4: lui         $at, 0x4180
    ctx->r1 = S32(0X4180 << 16);
        goto L_801E75DC;
    // 0x801E74F4: lui         $at, 0x4180
    ctx->r1 = S32(0X4180 << 16);
L_801E74F8:
    // 0x801E74F8: lh          $v0, 0x8($s0)
    ctx->r2 = MEM_H(ctx->r16, 0X8);
    // 0x801E74FC: lh          $t6, 0xA($s0)
    ctx->r14 = MEM_H(ctx->r16, 0XA);
    // 0x801E7500: addiu       $v1, $zero, 0x1
    ctx->r3 = ADD32(0, 0X1);
    // 0x801E7504: addiu       $t7, $v0, 0x1
    ctx->r15 = ADD32(ctx->r2, 0X1);
    // 0x801E7508: slt         $at, $v0, $t6
    ctx->r1 = SIGNED(ctx->r2) < SIGNED(ctx->r14) ? 1 : 0;
    // 0x801E750C: bne         $at, $zero, L_801E7520
    if (ctx->r1 != 0) {
        // 0x801E7510: nop
    
            goto L_801E7520;
    }
    // 0x801E7510: nop

    // 0x801E7514: sh          $v1, 0x2($s0)
    MEM_H(0X2, ctx->r16) = ctx->r3;
    // 0x801E7518: b           L_801E75D8
    // 0x801E751C: sh          $zero, 0x8($s0)
    MEM_H(0X8, ctx->r16) = 0;
        goto L_801E75D8;
    // 0x801E751C: sh          $zero, 0x8($s0)
    MEM_H(0X8, ctx->r16) = 0;
L_801E7520:
    // 0x801E7520: b           L_801E75D8
    // 0x801E7524: sh          $t7, 0x8($s0)
    MEM_H(0X8, ctx->r16) = ctx->r15;
        goto L_801E75D8;
    // 0x801E7524: sh          $t7, 0x8($s0)
    MEM_H(0X8, ctx->r16) = ctx->r15;
L_801E7528:
    // 0x801E7528: lh          $t8, 0x8($s0)
    ctx->r24 = MEM_H(ctx->r16, 0X8);
    // 0x801E752C: lh          $t0, 0xC($s0)
    ctx->r8 = MEM_H(ctx->r16, 0XC);
    // 0x801E7530: addiu       $t6, $zero, 0x2
    ctx->r14 = ADD32(0, 0X2);
    // 0x801E7534: addiu       $t9, $t8, 0x1
    ctx->r25 = ADD32(ctx->r24, 0X1);
    // 0x801E7538: bne         $t0, $zero, L_801E7550
    if (ctx->r8 != 0) {
        // 0x801E753C: sh          $t9, 0x8($s0)
        MEM_H(0X8, ctx->r16) = ctx->r25;
            goto L_801E7550;
    }
    // 0x801E753C: sh          $t9, 0x8($s0)
    MEM_H(0X8, ctx->r16) = ctx->r25;
    // 0x801E7540: lh          $t1, 0x18($s0)
    ctx->r9 = MEM_H(ctx->r16, 0X18);
    // 0x801E7544: addiu       $t2, $t1, 0x14
    ctx->r10 = ADD32(ctx->r9, 0X14);
    // 0x801E7548: b           L_801E755C
    // 0x801E754C: sh          $t2, 0x18($s0)
    MEM_H(0X18, ctx->r16) = ctx->r10;
        goto L_801E755C;
    // 0x801E754C: sh          $t2, 0x18($s0)
    MEM_H(0X18, ctx->r16) = ctx->r10;
L_801E7550:
    // 0x801E7550: lh          $t3, 0x18($s0)
    ctx->r11 = MEM_H(ctx->r16, 0X18);
    // 0x801E7554: addiu       $t4, $t3, 0x14
    ctx->r12 = ADD32(ctx->r11, 0X14);
    // 0x801E7558: sh          $t4, 0x18($s0)
    MEM_H(0X18, ctx->r16) = ctx->r12;
L_801E755C:
    // 0x801E755C: lh          $t5, 0x18($s0)
    ctx->r13 = MEM_H(ctx->r16, 0X18);
    // 0x801E7560: addiu       $t7, $zero, 0xFA
    ctx->r15 = ADD32(0, 0XFA);
    // 0x801E7564: slti        $at, $t5, 0xFA
    ctx->r1 = SIGNED(ctx->r13) < 0XFA ? 1 : 0;
    // 0x801E7568: bnel        $at, $zero, L_801E75DC
    if (ctx->r1 != 0) {
        // 0x801E756C: lui         $at, 0x4180
        ctx->r1 = S32(0X4180 << 16);
            goto L_801E75DC;
    }
    goto skip_1;
    // 0x801E756C: lui         $at, 0x4180
    ctx->r1 = S32(0X4180 << 16);
    skip_1:
    // 0x801E7570: sh          $t6, 0x2($s0)
    MEM_H(0X2, ctx->r16) = ctx->r14;
    // 0x801E7574: sh          $t7, 0x18($s0)
    MEM_H(0X18, ctx->r16) = ctx->r15;
    // 0x801E7578: b           L_801E75D8
    // 0x801E757C: sh          $zero, 0x8($s0)
    MEM_H(0X8, ctx->r16) = 0;
        goto L_801E75D8;
    // 0x801E757C: sh          $zero, 0x8($s0)
    MEM_H(0X8, ctx->r16) = 0;
    // 0x801E7580: lh          $v0, 0x8($s0)
    ctx->r2 = MEM_H(ctx->r16, 0X8);
L_801E7584:
    // 0x801E7584: lh          $t8, 0xE($s0)
    ctx->r24 = MEM_H(ctx->r16, 0XE);
    // 0x801E7588: lui         $t9, 0x8023
    ctx->r25 = S32(0X8023 << 16);
    // 0x801E758C: addiu       $t9, $t9, -0x75F0
    ctx->r25 = ADD32(ctx->r25, -0X75F0);
    // 0x801E7590: slt         $at, $v0, $t8
    ctx->r1 = SIGNED(ctx->r2) < SIGNED(ctx->r24) ? 1 : 0;
    // 0x801E7594: bne         $at, $zero, L_801E75D4
    if (ctx->r1 != 0) {
        // 0x801E7598: addiu       $t3, $v0, 0x1
        ctx->r11 = ADD32(ctx->r2, 0X1);
            goto L_801E75D4;
    }
    // 0x801E7598: addiu       $t3, $v0, 0x1
    ctx->r11 = ADD32(ctx->r2, 0X1);
    // 0x801E759C: lui         $t0, 0x8022
    ctx->r8 = S32(0X8022 << 16);
    // 0x801E75A0: addiu       $t0, $t0, 0x6CC0
    ctx->r8 = ADD32(ctx->r8, 0X6CC0);
    // 0x801E75A4: addiu       $t2, $t0, 0x24
    ctx->r10 = ADD32(ctx->r8, 0X24);
L_801E75A8:
    // 0x801E75A8: lw          $at, 0x0($t0)
    ctx->r1 = MEM_W(ctx->r8, 0X0);
    // 0x801E75AC: addiu       $t0, $t0, 0xC
    ctx->r8 = ADD32(ctx->r8, 0XC);
    // 0x801E75B0: addiu       $t9, $t9, 0xC
    ctx->r25 = ADD32(ctx->r25, 0XC);
    // 0x801E75B4: sw          $at, -0xC($t9)
    MEM_W(-0XC, ctx->r25) = ctx->r1;
    // 0x801E75B8: lw          $at, -0x8($t0)
    ctx->r1 = MEM_W(ctx->r8, -0X8);
    // 0x801E75BC: sw          $at, -0x8($t9)
    MEM_W(-0X8, ctx->r25) = ctx->r1;
    // 0x801E75C0: lw          $at, -0x4($t0)
    ctx->r1 = MEM_W(ctx->r8, -0X4);
    // 0x801E75C4: bne         $t0, $t2, L_801E75A8
    if (ctx->r8 != ctx->r10) {
        // 0x801E75C8: sw          $at, -0x4($t9)
        MEM_W(-0X4, ctx->r25) = ctx->r1;
            goto L_801E75A8;
    }
    // 0x801E75C8: sw          $at, -0x4($t9)
    MEM_W(-0X4, ctx->r25) = ctx->r1;
    // 0x801E75CC: b           L_801E75D8
    // 0x801E75D0: sh          $v1, 0x6($s0)
    MEM_H(0X6, ctx->r16) = ctx->r3;
        goto L_801E75D8;
    // 0x801E75D0: sh          $v1, 0x6($s0)
    MEM_H(0X6, ctx->r16) = ctx->r3;
L_801E75D4:
    // 0x801E75D4: sh          $t3, 0x8($s0)
    MEM_H(0X8, ctx->r16) = ctx->r11;
L_801E75D8:
    // 0x801E75D8: lui         $at, 0x4180
    ctx->r1 = S32(0X4180 << 16);
L_801E75DC:
    // 0x801E75DC: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x801E75E0: lui         $at, 0x4580
    ctx->r1 = S32(0X4580 << 16);
    // 0x801E75E4: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x801E75E8: lw          $a0, -0x1A08($a0)
    ctx->r4 = MEM_W(ctx->r4, -0X1A08);
    // 0x801E75EC: lui         $a1, 0x8023
    ctx->r5 = S32(0X8023 << 16);
    // 0x801E75F0: addiu       $a1, $a1, -0x75CC
    ctx->r5 = ADD32(ctx->r5, -0X75CC);
    // 0x801E75F4: lui         $a2, 0x4204
    ctx->r6 = S32(0X4204 << 16);
    // 0x801E75F8: lui         $a3, 0x3F80
    ctx->r7 = S32(0X3F80 << 16);
    // 0x801E75FC: swc1        $f0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->f0.u32l;
    // 0x801E7600: swc1        $f0, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->f0.u32l;
    // 0x801E7604: swc1        $f4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f4.u32l;
    // 0x801E7608: addiu       $a0, $a0, 0x1300
    ctx->r4 = ADD32(ctx->r4, 0X1300);
    // 0x801E760C: jal         0x800481E0
    // 0x801E7610: swc1        $f6, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->f6.u32l;
    func_800481E0(rdram, ctx);
        goto after_0;
    // 0x801E7610: swc1        $f6, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->f6.u32l;
    after_0:
    // 0x801E7614: mtc1        $zero, $f0
    ctx->f0.u32l = 0;
    // 0x801E7618: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x801E761C: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x801E7620: swc1        $f0, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f0.u32l;
    // 0x801E7624: swc1        $f0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->f0.u32l;
    // 0x801E7628: swc1        $f8, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->f8.u32l;
    // 0x801E762C: lh          $t4, 0x18($s0)
    ctx->r12 = MEM_H(ctx->r16, 0X18);
    // 0x801E7630: lui         $at, 0xC360
    ctx->r1 = S32(0XC360 << 16);
    // 0x801E7634: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x801E7638: mtc1        $t4, $f10
    ctx->f10.u32l = ctx->r12;
    // 0x801E763C: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E7640: lui         $a0, 0x801D
    ctx->r4 = S32(0X801D << 16);
    // 0x801E7644: cvt.s.w     $f16, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    ctx->f16.fl = CVT_S_W(ctx->f10.u32l);
    // 0x801E7648: lw          $a0, -0x1A08($a0)
    ctx->r4 = MEM_W(ctx->r4, -0X1A08);
    // 0x801E764C: lwc1        $f8, 0x6D48($at)
    ctx->f8.u32l = MEM_W(ctx->r1, 0X6D48);
    // 0x801E7650: mfc1        $a1, $f0
    ctx->r5 = (int32_t)ctx->f0.u32l;
    // 0x801E7654: mfc1        $a2, $f0
    ctx->r6 = (int32_t)ctx->f0.u32l;
    // 0x801E7658: lui         $a3, 0xBF80
    ctx->r7 = S32(0XBF80 << 16);
    // 0x801E765C: swc1        $f16, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->f16.u32l;
    // 0x801E7660: lh          $t5, 0x1A($s0)
    ctx->r13 = MEM_H(ctx->r16, 0X1A);
    // 0x801E7664: swc1        $f6, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->f6.u32l;
    // 0x801E7668: addiu       $a0, $a0, 0x1340
    ctx->r4 = ADD32(ctx->r4, 0X1340);
    // 0x801E766C: mtc1        $t5, $f18
    ctx->f18.u32l = ctx->r13;
    // 0x801E7670: swc1        $f8, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->f8.u32l;
    // 0x801E7674: cvt.s.w     $f4, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    ctx->f4.fl = CVT_S_W(ctx->f18.u32l);
    // 0x801E7678: jal         0x80048A88
    // 0x801E767C: swc1        $f4, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->f4.u32l;
    func_80048A88(rdram, ctx);
        goto after_1;
    // 0x801E767C: swc1        $f4, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->f4.u32l;
    after_1:
    // 0x801E7680: lh          $t6, 0x1E($s0)
    ctx->r14 = MEM_H(ctx->r16, 0X1E);
    // 0x801E7684: addiu       $t7, $t6, 0x1
    ctx->r15 = ADD32(ctx->r14, 0X1);
    // 0x801E7688: sh          $t7, 0x1E($s0)
    MEM_H(0X1E, ctx->r16) = ctx->r15;
    // 0x801E768C: lh          $t8, 0x1E($s0)
    ctx->r24 = MEM_H(ctx->r16, 0X1E);
    // 0x801E7690: slti        $at, $t8, 0x2
    ctx->r1 = SIGNED(ctx->r24) < 0X2 ? 1 : 0;
    // 0x801E7694: bnel        $at, $zero, L_801E76B0
    if (ctx->r1 != 0) {
        // 0x801E7698: lw          $ra, 0x3C($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X3C);
            goto L_801E76B0;
    }
    goto skip_2;
    // 0x801E7698: lw          $ra, 0x3C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X3C);
    skip_2:
    // 0x801E769C: lh          $t1, 0x1C($s0)
    ctx->r9 = MEM_H(ctx->r16, 0X1C);
    // 0x801E76A0: sh          $zero, 0x1E($s0)
    MEM_H(0X1E, ctx->r16) = 0;
    // 0x801E76A4: xori        $t2, $t1, 0x1
    ctx->r10 = ctx->r9 ^ 0X1;
    // 0x801E76A8: sh          $t2, 0x1C($s0)
    MEM_H(0X1C, ctx->r16) = ctx->r10;
    // 0x801E76AC: lw          $ra, 0x3C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X3C);
L_801E76B0:
    // 0x801E76B0: lw          $s0, 0x38($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X38);
    // 0x801E76B4: addiu       $sp, $sp, 0x40
    ctx->r29 = ADD32(ctx->r29, 0X40);
    // 0x801E76B8: jr          $ra
    // 0x801E76BC: nop

    return;
    // 0x801E76BC: nop

;}
RECOMP_FUNC void func_801E76C0(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801E76C0: addiu       $sp, $sp, -0x40
    ctx->r29 = ADD32(ctx->r29, -0X40);
    // 0x801E76C4: sw          $ra, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r31;
    // 0x801E76C8: sw          $s0, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r16;
    // 0x801E76CC: lh          $v0, 0x2($a0)
    ctx->r2 = MEM_H(ctx->r4, 0X2);
    // 0x801E76D0: or          $s0, $a0, $zero
    ctx->r16 = ctx->r4 | 0;
    // 0x801E76D4: addiu       $v1, $zero, 0x1
    ctx->r3 = ADD32(0, 0X1);
    // 0x801E76D8: beql        $v0, $zero, L_801E76FC
    if (ctx->r2 == 0) {
        // 0x801E76DC: lh          $v0, 0x8($s0)
        ctx->r2 = MEM_H(ctx->r16, 0X8);
            goto L_801E76FC;
    }
    goto skip_0;
    // 0x801E76DC: lh          $v0, 0x8($s0)
    ctx->r2 = MEM_H(ctx->r16, 0X8);
    skip_0:
    // 0x801E76E0: beq         $v0, $v1, L_801E7768
    if (ctx->r2 == ctx->r3) {
        // 0x801E76E4: addiu       $at, $zero, 0x2
        ctx->r1 = ADD32(0, 0X2);
            goto L_801E7768;
    }
    // 0x801E76E4: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x801E76E8: beql        $v0, $at, L_801E77C4
    if (ctx->r2 == ctx->r1) {
        // 0x801E76EC: lh          $v0, 0x8($s0)
        ctx->r2 = MEM_H(ctx->r16, 0X8);
            goto L_801E77C4;
    }
    goto skip_1;
    // 0x801E76EC: lh          $v0, 0x8($s0)
    ctx->r2 = MEM_H(ctx->r16, 0X8);
    skip_1:
    // 0x801E76F0: b           L_801E781C
    // 0x801E76F4: lui         $at, 0x4180
    ctx->r1 = S32(0X4180 << 16);
        goto L_801E781C;
    // 0x801E76F4: lui         $at, 0x4180
    ctx->r1 = S32(0X4180 << 16);
    // 0x801E76F8: lh          $v0, 0x8($s0)
    ctx->r2 = MEM_H(ctx->r16, 0X8);
L_801E76FC:
    // 0x801E76FC: lh          $t6, 0xA($s0)
    ctx->r14 = MEM_H(ctx->r16, 0XA);
    // 0x801E7700: addiu       $v1, $zero, 0x1
    ctx->r3 = ADD32(0, 0X1);
    // 0x801E7704: lui         $t7, 0x801D
    ctx->r15 = S32(0X801D << 16);
    // 0x801E7708: slt         $at, $v0, $t6
    ctx->r1 = SIGNED(ctx->r2) < SIGNED(ctx->r14) ? 1 : 0;
    // 0x801E770C: bne         $at, $zero, L_801E7760
    if (ctx->r1 != 0) {
        // 0x801E7710: addiu       $t9, $v0, 0x1
        ctx->r25 = ADD32(ctx->r2, 0X1);
            goto L_801E7760;
    }
    // 0x801E7710: addiu       $t9, $v0, 0x1
    ctx->r25 = ADD32(ctx->r2, 0X1);
    // 0x801E7714: sh          $v1, 0x2($s0)
    MEM_H(0X2, ctx->r16) = ctx->r3;
    // 0x801E7718: sh          $zero, 0x8($s0)
    MEM_H(0X8, ctx->r16) = 0;
    // 0x801E771C: lw          $t7, -0x19C8($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X19C8);
    // 0x801E7720: addiu       $at, $zero, 0x8
    ctx->r1 = ADD32(0, 0X8);
    // 0x801E7724: beql        $t7, $at, L_801E781C
    if (ctx->r15 == ctx->r1) {
        // 0x801E7728: lui         $at, 0x4180
        ctx->r1 = S32(0X4180 << 16);
            goto L_801E781C;
    }
    goto skip_2;
    // 0x801E7728: lui         $at, 0x4180
    ctx->r1 = S32(0X4180 << 16);
    skip_2:
    // 0x801E772C: lh          $t8, 0xC($s0)
    ctx->r24 = MEM_H(ctx->r16, 0XC);
    // 0x801E7730: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x801E7734: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x801E7738: bne         $t8, $at, L_801E7750
    if (ctx->r24 != ctx->r1) {
        // 0x801E773C: addiu       $a0, $zero, 0x2A
        ctx->r4 = ADD32(0, 0X2A);
            goto L_801E7750;
    }
    // 0x801E773C: addiu       $a0, $zero, 0x2A
    ctx->r4 = ADD32(0, 0X2A);
    // 0x801E7740: jal         0x800C37F4
    // 0x801E7744: addiu       $a0, $zero, 0x38
    ctx->r4 = ADD32(0, 0X38);
    func_800C37F4(rdram, ctx);
        goto after_0;
    // 0x801E7744: addiu       $a0, $zero, 0x38
    ctx->r4 = ADD32(0, 0X38);
    after_0:
    // 0x801E7748: b           L_801E781C
    // 0x801E774C: lui         $at, 0x4180
    ctx->r1 = S32(0X4180 << 16);
        goto L_801E781C;
    // 0x801E774C: lui         $at, 0x4180
    ctx->r1 = S32(0X4180 << 16);
L_801E7750:
    // 0x801E7750: jal         0x800C37F4
    // 0x801E7754: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_1;
    // 0x801E7754: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_1:
    // 0x801E7758: b           L_801E781C
    // 0x801E775C: lui         $at, 0x4180
    ctx->r1 = S32(0X4180 << 16);
        goto L_801E781C;
    // 0x801E775C: lui         $at, 0x4180
    ctx->r1 = S32(0X4180 << 16);
L_801E7760:
    // 0x801E7760: b           L_801E7818
    // 0x801E7764: sh          $t9, 0x8($s0)
    MEM_H(0X8, ctx->r16) = ctx->r25;
        goto L_801E7818;
    // 0x801E7764: sh          $t9, 0x8($s0)
    MEM_H(0X8, ctx->r16) = ctx->r25;
L_801E7768:
    // 0x801E7768: lh          $t0, 0x8($s0)
    ctx->r8 = MEM_H(ctx->r16, 0X8);
    // 0x801E776C: lh          $t2, 0xC($s0)
    ctx->r10 = MEM_H(ctx->r16, 0XC);
    // 0x801E7770: addiu       $t8, $zero, 0x2
    ctx->r24 = ADD32(0, 0X2);
    // 0x801E7774: addiu       $t1, $t0, 0x1
    ctx->r9 = ADD32(ctx->r8, 0X1);
    // 0x801E7778: bne         $t2, $zero, L_801E7790
    if (ctx->r10 != 0) {
        // 0x801E777C: sh          $t1, 0x8($s0)
        MEM_H(0X8, ctx->r16) = ctx->r9;
            goto L_801E7790;
    }
    // 0x801E777C: sh          $t1, 0x8($s0)
    MEM_H(0X8, ctx->r16) = ctx->r9;
    // 0x801E7780: lh          $t3, 0x18($s0)
    ctx->r11 = MEM_H(ctx->r16, 0X18);
    // 0x801E7784: addiu       $t4, $t3, 0x14
    ctx->r12 = ADD32(ctx->r11, 0X14);
    // 0x801E7788: b           L_801E779C
    // 0x801E778C: sh          $t4, 0x18($s0)
    MEM_H(0X18, ctx->r16) = ctx->r12;
        goto L_801E779C;
    // 0x801E778C: sh          $t4, 0x18($s0)
    MEM_H(0X18, ctx->r16) = ctx->r12;
L_801E7790:
    // 0x801E7790: lh          $t5, 0x18($s0)
    ctx->r13 = MEM_H(ctx->r16, 0X18);
    // 0x801E7794: addiu       $t6, $t5, 0x14
    ctx->r14 = ADD32(ctx->r13, 0X14);
    // 0x801E7798: sh          $t6, 0x18($s0)
    MEM_H(0X18, ctx->r16) = ctx->r14;
L_801E779C:
    // 0x801E779C: lh          $t7, 0x18($s0)
    ctx->r15 = MEM_H(ctx->r16, 0X18);
    // 0x801E77A0: addiu       $t9, $zero, -0x55
    ctx->r25 = ADD32(0, -0X55);
    // 0x801E77A4: slti        $at, $t7, -0x55
    ctx->r1 = SIGNED(ctx->r15) < -0X55 ? 1 : 0;
    // 0x801E77A8: bnel        $at, $zero, L_801E781C
    if (ctx->r1 != 0) {
        // 0x801E77AC: lui         $at, 0x4180
        ctx->r1 = S32(0X4180 << 16);
            goto L_801E781C;
    }
    goto skip_3;
    // 0x801E77AC: lui         $at, 0x4180
    ctx->r1 = S32(0X4180 << 16);
    skip_3:
    // 0x801E77B0: sh          $t8, 0x2($s0)
    MEM_H(0X2, ctx->r16) = ctx->r24;
    // 0x801E77B4: sh          $t9, 0x18($s0)
    MEM_H(0X18, ctx->r16) = ctx->r25;
    // 0x801E77B8: b           L_801E7818
    // 0x801E77BC: sh          $zero, 0x8($s0)
    MEM_H(0X8, ctx->r16) = 0;
        goto L_801E7818;
    // 0x801E77BC: sh          $zero, 0x8($s0)
    MEM_H(0X8, ctx->r16) = 0;
    // 0x801E77C0: lh          $v0, 0x8($s0)
    ctx->r2 = MEM_H(ctx->r16, 0X8);
L_801E77C4:
    // 0x801E77C4: lh          $t0, 0xE($s0)
    ctx->r8 = MEM_H(ctx->r16, 0XE);
    // 0x801E77C8: lui         $t1, 0x8023
    ctx->r9 = S32(0X8023 << 16);
    // 0x801E77CC: addiu       $t1, $t1, -0x75F0
    ctx->r9 = ADD32(ctx->r9, -0X75F0);
    // 0x801E77D0: slt         $at, $v0, $t0
    ctx->r1 = SIGNED(ctx->r2) < SIGNED(ctx->r8) ? 1 : 0;
    // 0x801E77D4: bne         $at, $zero, L_801E7814
    if (ctx->r1 != 0) {
        // 0x801E77D8: addiu       $t5, $v0, 0x1
        ctx->r13 = ADD32(ctx->r2, 0X1);
            goto L_801E7814;
    }
    // 0x801E77D8: addiu       $t5, $v0, 0x1
    ctx->r13 = ADD32(ctx->r2, 0X1);
    // 0x801E77DC: lui         $t2, 0x8022
    ctx->r10 = S32(0X8022 << 16);
    // 0x801E77E0: addiu       $t2, $t2, 0x6CC0
    ctx->r10 = ADD32(ctx->r10, 0X6CC0);
    // 0x801E77E4: addiu       $t4, $t2, 0x24
    ctx->r12 = ADD32(ctx->r10, 0X24);
L_801E77E8:
    // 0x801E77E8: lw          $at, 0x0($t2)
    ctx->r1 = MEM_W(ctx->r10, 0X0);
    // 0x801E77EC: addiu       $t2, $t2, 0xC
    ctx->r10 = ADD32(ctx->r10, 0XC);
    // 0x801E77F0: addiu       $t1, $t1, 0xC
    ctx->r9 = ADD32(ctx->r9, 0XC);
    // 0x801E77F4: sw          $at, -0xC($t1)
    MEM_W(-0XC, ctx->r9) = ctx->r1;
    // 0x801E77F8: lw          $at, -0x8($t2)
    ctx->r1 = MEM_W(ctx->r10, -0X8);
    // 0x801E77FC: sw          $at, -0x8($t1)
    MEM_W(-0X8, ctx->r9) = ctx->r1;
    // 0x801E7800: lw          $at, -0x4($t2)
    ctx->r1 = MEM_W(ctx->r10, -0X4);
    // 0x801E7804: bne         $t2, $t4, L_801E77E8
    if (ctx->r10 != ctx->r12) {
        // 0x801E7808: sw          $at, -0x4($t1)
        MEM_W(-0X4, ctx->r9) = ctx->r1;
            goto L_801E77E8;
    }
    // 0x801E7808: sw          $at, -0x4($t1)
    MEM_W(-0X4, ctx->r9) = ctx->r1;
    // 0x801E780C: b           L_801E7818
    // 0x801E7810: sh          $v1, 0x6($s0)
    MEM_H(0X6, ctx->r16) = ctx->r3;
        goto L_801E7818;
    // 0x801E7810: sh          $v1, 0x6($s0)
    MEM_H(0X6, ctx->r16) = ctx->r3;
L_801E7814:
    // 0x801E7814: sh          $t5, 0x8($s0)
    MEM_H(0X8, ctx->r16) = ctx->r13;
L_801E7818:
    // 0x801E7818: lui         $at, 0x4180
    ctx->r1 = S32(0X4180 << 16);
L_801E781C:
    // 0x801E781C: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x801E7820: mtc1        $zero, $f0
    ctx->f0.u32l = 0;
    // 0x801E7824: lui         $at, 0x4580
    ctx->r1 = S32(0X4580 << 16);
    // 0x801E7828: lui         $a0, 0x801D
    ctx->r4 = S32(0X801D << 16);
    // 0x801E782C: lw          $a0, -0x1A08($a0)
    ctx->r4 = MEM_W(ctx->r4, -0X1A08);
    // 0x801E7830: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x801E7834: lui         $a1, 0x8023
    ctx->r5 = S32(0X8023 << 16);
    // 0x801E7838: addiu       $a1, $a1, -0x75CC
    ctx->r5 = ADD32(ctx->r5, -0X75CC);
    // 0x801E783C: lui         $a2, 0x4204
    ctx->r6 = S32(0X4204 << 16);
    // 0x801E7840: lui         $a3, 0x3F80
    ctx->r7 = S32(0X3F80 << 16);
    // 0x801E7844: swc1        $f4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f4.u32l;
    // 0x801E7848: swc1        $f0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->f0.u32l;
    // 0x801E784C: swc1        $f0, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->f0.u32l;
    // 0x801E7850: addiu       $a0, $a0, 0x1300
    ctx->r4 = ADD32(ctx->r4, 0X1300);
    // 0x801E7854: jal         0x800481E0
    // 0x801E7858: swc1        $f6, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->f6.u32l;
    func_800481E0(rdram, ctx);
        goto after_2;
    // 0x801E7858: swc1        $f6, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->f6.u32l;
    after_2:
    // 0x801E785C: mtc1        $zero, $f0
    ctx->f0.u32l = 0;
    // 0x801E7860: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x801E7864: mtc1        $at, $f2
    ctx->f2.u32l = ctx->r1;
    // 0x801E7868: swc1        $f0, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f0.u32l;
    // 0x801E786C: swc1        $f0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->f0.u32l;
    // 0x801E7870: swc1        $f2, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->f2.u32l;
    // 0x801E7874: lh          $t6, 0x18($s0)
    ctx->r14 = MEM_H(ctx->r16, 0X18);
    // 0x801E7878: lui         $at, 0xC360
    ctx->r1 = S32(0XC360 << 16);
    // 0x801E787C: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x801E7880: mtc1        $t6, $f8
    ctx->f8.u32l = ctx->r14;
    // 0x801E7884: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E7888: lui         $a0, 0x801D
    ctx->r4 = S32(0X801D << 16);
    // 0x801E788C: cvt.s.w     $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.fl = CVT_S_W(ctx->f8.u32l);
    // 0x801E7890: lw          $a0, -0x1A08($a0)
    ctx->r4 = MEM_W(ctx->r4, -0X1A08);
    // 0x801E7894: lwc1        $f6, 0x6D4C($at)
    ctx->f6.u32l = MEM_W(ctx->r1, 0X6D4C);
    // 0x801E7898: mfc1        $a1, $f0
    ctx->r5 = (int32_t)ctx->f0.u32l;
    // 0x801E789C: mfc1        $a2, $f0
    ctx->r6 = (int32_t)ctx->f0.u32l;
    // 0x801E78A0: mfc1        $a3, $f2
    ctx->r7 = (int32_t)ctx->f2.u32l;
    // 0x801E78A4: swc1        $f10, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->f10.u32l;
    // 0x801E78A8: lh          $t7, 0x1A($s0)
    ctx->r15 = MEM_H(ctx->r16, 0X1A);
    // 0x801E78AC: swc1        $f4, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->f4.u32l;
    // 0x801E78B0: addiu       $a0, $a0, 0x1340
    ctx->r4 = ADD32(ctx->r4, 0X1340);
    // 0x801E78B4: mtc1        $t7, $f16
    ctx->f16.u32l = ctx->r15;
    // 0x801E78B8: swc1        $f6, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->f6.u32l;
    // 0x801E78BC: cvt.s.w     $f18, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    ctx->f18.fl = CVT_S_W(ctx->f16.u32l);
    // 0x801E78C0: jal         0x80048A88
    // 0x801E78C4: swc1        $f18, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->f18.u32l;
    func_80048A88(rdram, ctx);
        goto after_3;
    // 0x801E78C4: swc1        $f18, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->f18.u32l;
    after_3:
    // 0x801E78C8: lh          $t8, 0x1E($s0)
    ctx->r24 = MEM_H(ctx->r16, 0X1E);
    // 0x801E78CC: addiu       $t9, $t8, 0x1
    ctx->r25 = ADD32(ctx->r24, 0X1);
    // 0x801E78D0: sh          $t9, 0x1E($s0)
    MEM_H(0X1E, ctx->r16) = ctx->r25;
    // 0x801E78D4: lh          $t0, 0x1E($s0)
    ctx->r8 = MEM_H(ctx->r16, 0X1E);
    // 0x801E78D8: slti        $at, $t0, 0x2
    ctx->r1 = SIGNED(ctx->r8) < 0X2 ? 1 : 0;
    // 0x801E78DC: bnel        $at, $zero, L_801E78F8
    if (ctx->r1 != 0) {
        // 0x801E78E0: lw          $ra, 0x3C($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X3C);
            goto L_801E78F8;
    }
    goto skip_4;
    // 0x801E78E0: lw          $ra, 0x3C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X3C);
    skip_4:
    // 0x801E78E4: lh          $t3, 0x1C($s0)
    ctx->r11 = MEM_H(ctx->r16, 0X1C);
    // 0x801E78E8: sh          $zero, 0x1E($s0)
    MEM_H(0X1E, ctx->r16) = 0;
    // 0x801E78EC: xori        $t4, $t3, 0x1
    ctx->r12 = ctx->r11 ^ 0X1;
    // 0x801E78F0: sh          $t4, 0x1C($s0)
    MEM_H(0X1C, ctx->r16) = ctx->r12;
    // 0x801E78F4: lw          $ra, 0x3C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X3C);
L_801E78F8:
    // 0x801E78F8: lw          $s0, 0x38($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X38);
    // 0x801E78FC: addiu       $sp, $sp, 0x40
    ctx->r29 = ADD32(ctx->r29, 0X40);
    // 0x801E7900: jr          $ra
    // 0x801E7904: nop

    return;
    // 0x801E7904: nop

;}
RECOMP_FUNC void func_801E7908(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801E7908: lui         $t6, 0x8023
    ctx->r14 = S32(0X8023 << 16);
    // 0x801E790C: lh          $t6, -0x75F0($t6)
    ctx->r14 = MEM_H(ctx->r14, -0X75F0);
    // 0x801E7910: addiu       $sp, $sp, -0x38
    ctx->r29 = ADD32(ctx->r29, -0X38);
    // 0x801E7914: sw          $s0, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r16;
    // 0x801E7918: or          $s0, $a0, $zero
    ctx->r16 = ctx->r4 | 0;
    // 0x801E791C: beq         $t6, $zero, L_801E793C
    if (ctx->r14 == 0) {
        // 0x801E7920: sw          $ra, 0x34($sp)
        MEM_W(0X34, ctx->r29) = ctx->r31;
            goto L_801E793C;
    }
    // 0x801E7920: sw          $ra, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r31;
    // 0x801E7924: lui         $t7, 0x8023
    ctx->r15 = S32(0X8023 << 16);
    // 0x801E7928: lh          $t7, -0x75EC($t7)
    ctx->r15 = MEM_H(ctx->r15, -0X75EC);
    // 0x801E792C: lui         $t8, 0x8023
    ctx->r24 = S32(0X8023 << 16);
    // 0x801E7930: lui         $t9, 0x8023
    ctx->r25 = S32(0X8023 << 16);
    // 0x801E7934: bne         $t7, $zero, L_801E7944
    if (ctx->r15 != 0) {
        // 0x801E7938: nop
    
            goto L_801E7944;
    }
    // 0x801E7938: nop

L_801E793C:
    // 0x801E793C: b           L_801E7C44
    // 0x801E7940: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
        goto L_801E7C44;
    // 0x801E7940: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
L_801E7944:
    // 0x801E7944: lh          $t8, -0x75CA($t8)
    ctx->r24 = MEM_H(ctx->r24, -0X75CA);
    // 0x801E7948: lh          $t9, -0x75D0($t9)
    ctx->r25 = MEM_H(ctx->r25, -0X75D0);
    // 0x801E794C: lui         $t4, 0x8023
    ctx->r12 = S32(0X8023 << 16);
    // 0x801E7950: beq         $t8, $t9, L_801E7960
    if (ctx->r24 == ctx->r25) {
        // 0x801E7954: nop
    
            goto L_801E7960;
    }
    // 0x801E7954: nop

    // 0x801E7958: b           L_801E7C44
    // 0x801E795C: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
        goto L_801E7C44;
    // 0x801E795C: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
L_801E7960:
    // 0x801E7960: lh          $t4, -0x75F0($t4)
    ctx->r12 = MEM_H(ctx->r12, -0X75F0);
    // 0x801E7964: addiu       $t5, $t4, -0x1
    ctx->r13 = ADD32(ctx->r12, -0X1);
    // 0x801E7968: sltiu       $at, $t5, 0x7
    ctx->r1 = ctx->r13 < 0X7 ? 1 : 0;
    // 0x801E796C: beq         $at, $zero, L_801E7C40
    if (ctx->r1 == 0) {
        // 0x801E7970: sll         $t5, $t5, 2
        ctx->r13 = S32(ctx->r13 << 2);
            goto L_801E7C40;
    }
    // 0x801E7970: sll         $t5, $t5, 2
    ctx->r13 = S32(ctx->r13 << 2);
    // 0x801E7974: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E7978: addu        $at, $at, $t5
    gpr jr_addend_801E7980 = ctx->r13;
    ctx->r1 = ADD32(ctx->r1, ctx->r13);
    // 0x801E797C: lw          $t5, 0x6D50($at)
    ctx->r13 = ADD32(ctx->r1, 0X6D50);
    // 0x801E7980: jr          $t5
    // 0x801E7984: nop

    switch (jr_addend_801E7980 >> 2) {
        case 0: goto L_801E7988; break;
        case 1: goto L_801E7988; break;
        case 2: goto L_801E7A40; break;
        case 3: goto L_801E7AF8; break;
        case 4: goto L_801E7AF8; break;
        case 5: goto L_801E7AF8; break;
        case 6: goto L_801E7A40; break;
        default: switch_error(__func__, 0x801E7980, 0x80226D50);
    }
    // 0x801E7984: nop

L_801E7988:
    // 0x801E7988: lui         $t6, 0x800E
    ctx->r14 = S32(0X800E << 16);
    // 0x801E798C: lw          $t6, -0x54D8($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X54D8);
    // 0x801E7990: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x801E7994: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x801E7998: bne         $t6, $at, L_801E79F4
    if (ctx->r14 != ctx->r1) {
        // 0x801E799C: addiu       $a1, $zero, 0x0
        ctx->r5 = ADD32(0, 0X0);
            goto L_801E79F4;
    }
    // 0x801E799C: addiu       $a1, $zero, 0x0
    ctx->r5 = ADD32(0, 0X0);
    // 0x801E79A0: lui         $t8, 0x8023
    ctx->r24 = S32(0X8023 << 16);
    // 0x801E79A4: lui         $t9, 0x8023
    ctx->r25 = S32(0X8023 << 16);
    // 0x801E79A8: lui         $t4, 0x8023
    ctx->r12 = S32(0X8023 << 16);
    // 0x801E79AC: lui         $t5, 0x8023
    ctx->r13 = S32(0X8023 << 16);
    // 0x801E79B0: lh          $t5, -0x75DA($t5)
    ctx->r13 = MEM_H(ctx->r13, -0X75DA);
    // 0x801E79B4: lh          $t4, -0x75DC($t4)
    ctx->r12 = MEM_H(ctx->r12, -0X75DC);
    // 0x801E79B8: lh          $t9, -0x75DE($t9)
    ctx->r25 = MEM_H(ctx->r25, -0X75DE);
    // 0x801E79BC: lh          $t8, -0x75E0($t8)
    ctx->r24 = MEM_H(ctx->r24, -0X75E0);
    // 0x801E79C0: addiu       $t7, $zero, 0xF0
    ctx->r15 = ADD32(0, 0XF0);
    // 0x801E79C4: sw          $t7, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r15;
    // 0x801E79C8: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x801E79CC: addiu       $a1, $zero, 0x0
    ctx->r5 = ADD32(0, 0X0);
    // 0x801E79D0: addiu       $a2, $zero, 0x0
    ctx->r6 = ADD32(0, 0X0);
    // 0x801E79D4: addiu       $a3, $zero, 0x1A8
    ctx->r7 = ADD32(0, 0X1A8);
    // 0x801E79D8: sw          $t5, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r13;
    // 0x801E79DC: sw          $t4, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r12;
    // 0x801E79E0: sw          $t9, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r25;
    // 0x801E79E4: jal         0x801E7C58
    // 0x801E79E8: sw          $t8, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r24;
    func_801E7C58(rdram, ctx);
        goto after_0;
    // 0x801E79E8: sw          $t8, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r24;
    after_0:
    // 0x801E79EC: b           L_801E7C40
    // 0x801E79F0: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
        goto L_801E7C40;
    // 0x801E79F0: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
L_801E79F4:
    // 0x801E79F4: lui         $t7, 0x8023
    ctx->r15 = S32(0X8023 << 16);
    // 0x801E79F8: lui         $t8, 0x8023
    ctx->r24 = S32(0X8023 << 16);
    // 0x801E79FC: lui         $t9, 0x8023
    ctx->r25 = S32(0X8023 << 16);
    // 0x801E7A00: lui         $t4, 0x8023
    ctx->r12 = S32(0X8023 << 16);
    // 0x801E7A04: lh          $t4, -0x75DA($t4)
    ctx->r12 = MEM_H(ctx->r12, -0X75DA);
    // 0x801E7A08: lh          $t9, -0x75DC($t9)
    ctx->r25 = MEM_H(ctx->r25, -0X75DC);
    // 0x801E7A0C: lh          $t8, -0x75DE($t8)
    ctx->r24 = MEM_H(ctx->r24, -0X75DE);
    // 0x801E7A10: lh          $t7, -0x75E0($t7)
    ctx->r15 = MEM_H(ctx->r15, -0X75E0);
    // 0x801E7A14: addiu       $t6, $zero, 0xF0
    ctx->r14 = ADD32(0, 0XF0);
    // 0x801E7A18: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x801E7A1C: addiu       $a2, $zero, 0x0
    ctx->r6 = ADD32(0, 0X0);
    // 0x801E7A20: addiu       $a3, $zero, 0x1A8
    ctx->r7 = ADD32(0, 0X1A8);
    // 0x801E7A24: sw          $t4, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r12;
    // 0x801E7A28: sw          $t9, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r25;
    // 0x801E7A2C: sw          $t8, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r24;
    // 0x801E7A30: jal         0x801E7C58
    // 0x801E7A34: sw          $t7, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r15;
    func_801E7C58(rdram, ctx);
        goto after_1;
    // 0x801E7A34: sw          $t7, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r15;
    after_1:
    // 0x801E7A38: b           L_801E7C40
    // 0x801E7A3C: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
        goto L_801E7C40;
    // 0x801E7A3C: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
L_801E7A40:
    // 0x801E7A40: lui         $t5, 0x800E
    ctx->r13 = S32(0X800E << 16);
    // 0x801E7A44: lw          $t5, -0x54D8($t5)
    ctx->r13 = MEM_W(ctx->r13, -0X54D8);
    // 0x801E7A48: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x801E7A4C: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x801E7A50: bne         $t5, $at, L_801E7AAC
    if (ctx->r13 != ctx->r1) {
        // 0x801E7A54: addiu       $a1, $zero, 0x0
        ctx->r5 = ADD32(0, 0X0);
            goto L_801E7AAC;
    }
    // 0x801E7A54: addiu       $a1, $zero, 0x0
    ctx->r5 = ADD32(0, 0X0);
    // 0x801E7A58: lui         $t7, 0x8023
    ctx->r15 = S32(0X8023 << 16);
    // 0x801E7A5C: lui         $t8, 0x8023
    ctx->r24 = S32(0X8023 << 16);
    // 0x801E7A60: lui         $t9, 0x8023
    ctx->r25 = S32(0X8023 << 16);
    // 0x801E7A64: lui         $t4, 0x8023
    ctx->r12 = S32(0X8023 << 16);
    // 0x801E7A68: lh          $t4, -0x75DA($t4)
    ctx->r12 = MEM_H(ctx->r12, -0X75DA);
    // 0x801E7A6C: lh          $t9, -0x75DC($t9)
    ctx->r25 = MEM_H(ctx->r25, -0X75DC);
    // 0x801E7A70: lh          $t8, -0x75DE($t8)
    ctx->r24 = MEM_H(ctx->r24, -0X75DE);
    // 0x801E7A74: lh          $t7, -0x75E0($t7)
    ctx->r15 = MEM_H(ctx->r15, -0X75E0);
    // 0x801E7A78: addiu       $t6, $zero, 0xF0
    ctx->r14 = ADD32(0, 0XF0);
    // 0x801E7A7C: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x801E7A80: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x801E7A84: addiu       $a1, $zero, 0x0
    ctx->r5 = ADD32(0, 0X0);
    // 0x801E7A88: addiu       $a2, $zero, 0x0
    ctx->r6 = ADD32(0, 0X0);
    // 0x801E7A8C: addiu       $a3, $zero, 0x1A8
    ctx->r7 = ADD32(0, 0X1A8);
    // 0x801E7A90: sw          $t4, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r12;
    // 0x801E7A94: sw          $t9, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r25;
    // 0x801E7A98: sw          $t8, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r24;
    // 0x801E7A9C: jal         0x801E7C58
    // 0x801E7AA0: sw          $t7, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r15;
    func_801E7C58(rdram, ctx);
        goto after_2;
    // 0x801E7AA0: sw          $t7, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r15;
    after_2:
    // 0x801E7AA4: b           L_801E7C40
    // 0x801E7AA8: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
        goto L_801E7C40;
    // 0x801E7AA8: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
L_801E7AAC:
    // 0x801E7AAC: lui         $t6, 0x8023
    ctx->r14 = S32(0X8023 << 16);
    // 0x801E7AB0: lui         $t7, 0x8023
    ctx->r15 = S32(0X8023 << 16);
    // 0x801E7AB4: lui         $t8, 0x8023
    ctx->r24 = S32(0X8023 << 16);
    // 0x801E7AB8: lui         $t9, 0x8023
    ctx->r25 = S32(0X8023 << 16);
    // 0x801E7ABC: lh          $t9, -0x75DA($t9)
    ctx->r25 = MEM_H(ctx->r25, -0X75DA);
    // 0x801E7AC0: lh          $t8, -0x75DC($t8)
    ctx->r24 = MEM_H(ctx->r24, -0X75DC);
    // 0x801E7AC4: lh          $t7, -0x75DE($t7)
    ctx->r15 = MEM_H(ctx->r15, -0X75DE);
    // 0x801E7AC8: lh          $t6, -0x75E0($t6)
    ctx->r14 = MEM_H(ctx->r14, -0X75E0);
    // 0x801E7ACC: addiu       $t5, $zero, 0xF0
    ctx->r13 = ADD32(0, 0XF0);
    // 0x801E7AD0: sw          $t5, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r13;
    // 0x801E7AD4: addiu       $a2, $zero, 0x0
    ctx->r6 = ADD32(0, 0X0);
    // 0x801E7AD8: addiu       $a3, $zero, 0x1A8
    ctx->r7 = ADD32(0, 0X1A8);
    // 0x801E7ADC: sw          $t9, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r25;
    // 0x801E7AE0: sw          $t8, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r24;
    // 0x801E7AE4: sw          $t7, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r15;
    // 0x801E7AE8: jal         0x801E7C58
    // 0x801E7AEC: sw          $t6, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r14;
    func_801E7C58(rdram, ctx);
        goto after_3;
    // 0x801E7AEC: sw          $t6, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r14;
    after_3:
    // 0x801E7AF0: b           L_801E7C40
    // 0x801E7AF4: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
        goto L_801E7C40;
    // 0x801E7AF4: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
L_801E7AF8:
    // 0x801E7AF8: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
    // 0x801E7AFC: lui         $t4, 0xB400
    ctx->r12 = S32(0XB400 << 16);
    // 0x801E7B00: sw          $t4, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r12;
    // 0x801E7B04: lui         $t5, 0x8023
    ctx->r13 = S32(0X8023 << 16);
    // 0x801E7B08: lhu         $t5, -0x75CC($t5)
    ctx->r13 = MEM_HU(ctx->r13, -0X75CC);
    // 0x801E7B0C: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801E7B10: or          $v1, $s0, $zero
    ctx->r3 = ctx->r16 | 0;
    // 0x801E7B14: sw          $t5, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r13;
    // 0x801E7B18: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801E7B1C: lui         $t6, 0x103
    ctx->r14 = S32(0X103 << 16);
    // 0x801E7B20: lui         $t7, 0x700
    ctx->r15 = S32(0X700 << 16);
    // 0x801E7B24: addiu       $t7, $t7, 0x1300
    ctx->r15 = ADD32(ctx->r15, 0X1300);
    // 0x801E7B28: ori         $t6, $t6, 0x40
    ctx->r14 = ctx->r14 | 0X40;
    // 0x801E7B2C: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x801E7B30: sw          $t6, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r14;
    // 0x801E7B34: sw          $t7, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r15;
    // 0x801E7B38: lui         $t8, 0x102
    ctx->r24 = S32(0X102 << 16);
    // 0x801E7B3C: lui         $t9, 0x700
    ctx->r25 = S32(0X700 << 16);
    // 0x801E7B40: addiu       $t9, $t9, 0x1340
    ctx->r25 = ADD32(ctx->r25, 0X1340);
    // 0x801E7B44: ori         $t8, $t8, 0x40
    ctx->r24 = ctx->r24 | 0X40;
    // 0x801E7B48: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801E7B4C: sw          $t8, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r24;
    // 0x801E7B50: sw          $t9, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r25;
    // 0x801E7B54: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    // 0x801E7B58: lui         $t4, 0x107
    ctx->r12 = S32(0X107 << 16);
    // 0x801E7B5C: lui         $t2, 0x600
    ctx->r10 = S32(0X600 << 16);
    // 0x801E7B60: addiu       $t4, $t4, -0xA50
    ctx->r12 = ADD32(ctx->r12, -0XA50);
    // 0x801E7B64: sw          $t4, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r12;
    // 0x801E7B68: sw          $t2, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r10;
    // 0x801E7B6C: lui         $t5, 0x8023
    ctx->r13 = S32(0X8023 << 16);
    // 0x801E7B70: lh          $t5, -0x75E4($t5)
    ctx->r13 = MEM_H(ctx->r13, -0X75E4);
    // 0x801E7B74: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801E7B78: lui         $t3, 0xE700
    ctx->r11 = S32(0XE700 << 16);
    // 0x801E7B7C: bne         $t5, $zero, L_801E7BA4
    if (ctx->r13 != 0) {
        // 0x801E7B80: or          $v0, $s0, $zero
        ctx->r2 = ctx->r16 | 0;
            goto L_801E7BA4;
    }
    // 0x801E7B80: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
    // 0x801E7B84: lui         $t6, 0x8023
    ctx->r14 = S32(0X8023 << 16);
    // 0x801E7B88: lh          $t6, -0x75E8($t6)
    ctx->r14 = MEM_H(ctx->r14, -0X75E8);
    // 0x801E7B8C: lui         $t9, 0x8022
    ctx->r25 = S32(0X8022 << 16);
    // 0x801E7B90: addiu       $t9, $t9, 0x6CE4
    ctx->r25 = ADD32(ctx->r25, 0X6CE4);
    // 0x801E7B94: andi        $t7, $t6, 0x1
    ctx->r15 = ctx->r14 & 0X1;
    // 0x801E7B98: sll         $t8, $t7, 3
    ctx->r24 = S32(ctx->r15 << 3);
    // 0x801E7B9C: b           L_801E7BC0
    // 0x801E7BA0: addu        $a2, $t8, $t9
    ctx->r6 = ADD32(ctx->r24, ctx->r25);
        goto L_801E7BC0;
    // 0x801E7BA0: addu        $a2, $t8, $t9
    ctx->r6 = ADD32(ctx->r24, ctx->r25);
L_801E7BA4:
    // 0x801E7BA4: lui         $t4, 0x8023
    ctx->r12 = S32(0X8023 << 16);
    // 0x801E7BA8: lh          $t4, -0x75E8($t4)
    ctx->r12 = MEM_H(ctx->r12, -0X75E8);
    // 0x801E7BAC: lui         $t7, 0x8022
    ctx->r15 = S32(0X8022 << 16);
    // 0x801E7BB0: addiu       $t7, $t7, 0x6CF4
    ctx->r15 = ADD32(ctx->r15, 0X6CF4);
    // 0x801E7BB4: andi        $t5, $t4, 0x1
    ctx->r13 = ctx->r12 & 0X1;
    // 0x801E7BB8: sll         $t6, $t5, 3
    ctx->r14 = S32(ctx->r13 << 3);
    // 0x801E7BBC: addu        $a2, $t6, $t7
    ctx->r6 = ADD32(ctx->r14, ctx->r15);
L_801E7BC0:
    // 0x801E7BC0: lw          $a3, 0x0($a2)
    ctx->r7 = MEM_W(ctx->r6, 0X0);
    // 0x801E7BC4: lw          $t1, 0x4($a2)
    ctx->r9 = MEM_W(ctx->r6, 0X4);
    // 0x801E7BC8: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801E7BCC: sw          $zero, 0x4($v0)
    MEM_W(0X4, ctx->r2) = 0;
    // 0x801E7BD0: sw          $t3, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r11;
    // 0x801E7BD4: or          $v1, $s0, $zero
    ctx->r3 = ctx->r16 | 0;
    // 0x801E7BD8: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801E7BDC: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x801E7BE0: sw          $t2, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r10;
    // 0x801E7BE4: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801E7BE8: sw          $a3, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r7;
    // 0x801E7BEC: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    // 0x801E7BF0: sw          $zero, 0x4($a0)
    MEM_W(0X4, ctx->r4) = 0;
    // 0x801E7BF4: sw          $t3, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r11;
    // 0x801E7BF8: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801E7BFC: lui         $t8, 0xB900
    ctx->r24 = S32(0XB900 << 16);
    // 0x801E7C00: lui         $t9, 0xC18
    ctx->r25 = S32(0XC18 << 16);
    // 0x801E7C04: ori         $t9, $t9, 0x4240
    ctx->r25 = ctx->r25 | 0X4240;
    // 0x801E7C08: ori         $t8, $t8, 0x31D
    ctx->r24 = ctx->r24 | 0X31D;
    // 0x801E7C0C: or          $t0, $s0, $zero
    ctx->r8 = ctx->r16 | 0;
    // 0x801E7C10: sw          $t8, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r24;
    // 0x801E7C14: sw          $t9, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r25;
    // 0x801E7C18: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801E7C1C: lui         $t5, 0x6A
    ctx->r13 = S32(0X6A << 16);
    // 0x801E7C20: addiu       $t5, $t5, -0x3C44
    ctx->r13 = ADD32(ctx->r13, -0X3C44);
    // 0x801E7C24: lui         $t4, 0xED00
    ctx->r12 = S32(0XED00 << 16);
    // 0x801E7C28: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
    // 0x801E7C2C: sw          $t4, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r12;
    // 0x801E7C30: sw          $t5, 0x4($t0)
    MEM_W(0X4, ctx->r8) = ctx->r13;
    // 0x801E7C34: sw          $t2, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r10;
    // 0x801E7C38: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801E7C3C: sw          $t1, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r9;
L_801E7C40:
    // 0x801E7C40: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
L_801E7C44:
    // 0x801E7C44: lw          $ra, 0x34($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X34);
    // 0x801E7C48: lw          $s0, 0x30($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X30);
    // 0x801E7C4C: addiu       $sp, $sp, 0x38
    ctx->r29 = ADD32(ctx->r29, 0X38);
    // 0x801E7C50: jr          $ra
    // 0x801E7C54: nop

    return;
    // 0x801E7C54: nop

;}
RECOMP_FUNC void func_801E7C58(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801E7C58: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x801E7C5C: lw          $t6, 0x2C($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X2C);
    // 0x801E7C60: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x801E7C64: sltiu       $at, $t6, 0x100
    ctx->r1 = ctx->r14 < 0X100 ? 1 : 0;
    // 0x801E7C68: bnel        $at, $zero, L_801E7C78
    if (ctx->r1 != 0) {
        // 0x801E7C6C: lw          $t0, 0x30($sp)
        ctx->r8 = MEM_W(ctx->r29, 0X30);
            goto L_801E7C78;
    }
    goto skip_0;
    // 0x801E7C6C: lw          $t0, 0x30($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X30);
    skip_0:
    // 0x801E7C70: sw          $t7, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r15;
    // 0x801E7C74: lw          $t0, 0x30($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X30);
L_801E7C78:
    // 0x801E7C78: lw          $t1, 0x34($sp)
    ctx->r9 = MEM_W(ctx->r29, 0X34);
    // 0x801E7C7C: lw          $v0, 0x38($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X38);
    // 0x801E7C80: sltiu       $at, $t0, 0x100
    ctx->r1 = ctx->r8 < 0X100 ? 1 : 0;
    // 0x801E7C84: bnel        $at, $zero, L_801E7C94
    if (ctx->r1 != 0) {
        // 0x801E7C88: sltiu       $at, $t1, 0x100
        ctx->r1 = ctx->r9 < 0X100 ? 1 : 0;
            goto L_801E7C94;
    }
    goto skip_1;
    // 0x801E7C88: sltiu       $at, $t1, 0x100
    ctx->r1 = ctx->r9 < 0X100 ? 1 : 0;
    skip_1:
    // 0x801E7C8C: addiu       $t0, $zero, 0xFF
    ctx->r8 = ADD32(0, 0XFF);
    // 0x801E7C90: sltiu       $at, $t1, 0x100
    ctx->r1 = ctx->r9 < 0X100 ? 1 : 0;
L_801E7C94:
    // 0x801E7C94: bnel        $at, $zero, L_801E7CA4
    if (ctx->r1 != 0) {
        // 0x801E7C98: sltiu       $at, $v0, 0x100
        ctx->r1 = ctx->r2 < 0X100 ? 1 : 0;
            goto L_801E7CA4;
    }
    goto skip_2;
    // 0x801E7C98: sltiu       $at, $v0, 0x100
    ctx->r1 = ctx->r2 < 0X100 ? 1 : 0;
    skip_2:
    // 0x801E7C9C: addiu       $t1, $zero, 0xFF
    ctx->r9 = ADD32(0, 0XFF);
    // 0x801E7CA0: sltiu       $at, $v0, 0x100
    ctx->r1 = ctx->r2 < 0X100 ? 1 : 0;
L_801E7CA4:
    // 0x801E7CA4: bnel        $at, $zero, L_801E7CB4
    if (ctx->r1 != 0) {
        // 0x801E7CA8: sltiu       $at, $a1, 0x1A8
        ctx->r1 = ctx->r5 < 0X1A8 ? 1 : 0;
            goto L_801E7CB4;
    }
    goto skip_3;
    // 0x801E7CA8: sltiu       $at, $a1, 0x1A8
    ctx->r1 = ctx->r5 < 0X1A8 ? 1 : 0;
    skip_3:
    // 0x801E7CAC: addiu       $v0, $zero, 0xFF
    ctx->r2 = ADD32(0, 0XFF);
    // 0x801E7CB0: sltiu       $at, $a1, 0x1A8
    ctx->r1 = ctx->r5 < 0X1A8 ? 1 : 0;
L_801E7CB4:
    // 0x801E7CB4: bne         $at, $zero, L_801E7CCC
    if (ctx->r1 != 0) {
        // 0x801E7CB8: sltiu       $at, $a3, 0x1A8
        ctx->r1 = ctx->r7 < 0X1A8 ? 1 : 0;
            goto L_801E7CCC;
    }
    // 0x801E7CB8: sltiu       $at, $a3, 0x1A8
    ctx->r1 = ctx->r7 < 0X1A8 ? 1 : 0;
    // 0x801E7CBC: bnel        $at, $zero, L_801E7CD0
    if (ctx->r1 != 0) {
        // 0x801E7CC0: sltiu       $at, $a2, 0xF0
        ctx->r1 = ctx->r6 < 0XF0 ? 1 : 0;
            goto L_801E7CD0;
    }
    goto skip_4;
    // 0x801E7CC0: sltiu       $at, $a2, 0xF0
    ctx->r1 = ctx->r6 < 0XF0 ? 1 : 0;
    skip_4:
    // 0x801E7CC4: b           L_801E7E6C
    // 0x801E7CC8: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
        goto L_801E7E6C;
    // 0x801E7CC8: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
L_801E7CCC:
    // 0x801E7CCC: sltiu       $at, $a2, 0xF0
    ctx->r1 = ctx->r6 < 0XF0 ? 1 : 0;
L_801E7CD0:
    // 0x801E7CD0: bne         $at, $zero, L_801E7CEC
    if (ctx->r1 != 0) {
        // 0x801E7CD4: lw          $v1, 0x28($sp)
        ctx->r3 = MEM_W(ctx->r29, 0X28);
            goto L_801E7CEC;
    }
    // 0x801E7CD4: lw          $v1, 0x28($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X28);
    // 0x801E7CD8: sltiu       $at, $v1, 0xF0
    ctx->r1 = ctx->r3 < 0XF0 ? 1 : 0;
    // 0x801E7CDC: bnel        $at, $zero, L_801E7CF0
    if (ctx->r1 != 0) {
        // 0x801E7CE0: sltiu       $at, $a1, 0x1A8
        ctx->r1 = ctx->r5 < 0X1A8 ? 1 : 0;
            goto L_801E7CF0;
    }
    goto skip_5;
    // 0x801E7CE0: sltiu       $at, $a1, 0x1A8
    ctx->r1 = ctx->r5 < 0X1A8 ? 1 : 0;
    skip_5:
    // 0x801E7CE4: b           L_801E7E6C
    // 0x801E7CE8: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
        goto L_801E7E6C;
    // 0x801E7CE8: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
L_801E7CEC:
    // 0x801E7CEC: sltiu       $at, $a1, 0x1A8
    ctx->r1 = ctx->r5 < 0X1A8 ? 1 : 0;
L_801E7CF0:
    // 0x801E7CF0: bne         $at, $zero, L_801E7CFC
    if (ctx->r1 != 0) {
        // 0x801E7CF4: lw          $v1, 0x28($sp)
        ctx->r3 = MEM_W(ctx->r29, 0X28);
            goto L_801E7CFC;
    }
    // 0x801E7CF4: lw          $v1, 0x28($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X28);
    // 0x801E7CF8: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
L_801E7CFC:
    // 0x801E7CFC: sltiu       $at, $a3, 0x1A7
    ctx->r1 = ctx->r7 < 0X1A7 ? 1 : 0;
    // 0x801E7D00: bne         $at, $zero, L_801E7D0C
    if (ctx->r1 != 0) {
        // 0x801E7D04: or          $t2, $a0, $zero
        ctx->r10 = ctx->r4 | 0;
            goto L_801E7D0C;
    }
    // 0x801E7D04: or          $t2, $a0, $zero
    ctx->r10 = ctx->r4 | 0;
    // 0x801E7D08: addiu       $a3, $zero, 0x1A8
    ctx->r7 = ADD32(0, 0X1A8);
L_801E7D0C:
    // 0x801E7D0C: sltiu       $at, $a2, 0xF0
    ctx->r1 = ctx->r6 < 0XF0 ? 1 : 0;
    // 0x801E7D10: bne         $at, $zero, L_801E7D1C
    if (ctx->r1 != 0) {
        // 0x801E7D14: addiu       $t3, $a0, 0x8
        ctx->r11 = ADD32(ctx->r4, 0X8);
            goto L_801E7D1C;
    }
    // 0x801E7D14: addiu       $t3, $a0, 0x8
    ctx->r11 = ADD32(ctx->r4, 0X8);
    // 0x801E7D18: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
L_801E7D1C:
    // 0x801E7D1C: sltiu       $at, $v1, 0xEF
    ctx->r1 = ctx->r3 < 0XEF ? 1 : 0;
    // 0x801E7D20: bne         $at, $zero, L_801E7D2C
    if (ctx->r1 != 0) {
        // 0x801E7D24: lui         $t8, 0x380
        ctx->r24 = S32(0X380 << 16);
            goto L_801E7D2C;
    }
    // 0x801E7D24: lui         $t8, 0x380
    ctx->r24 = S32(0X380 << 16);
    // 0x801E7D28: addiu       $v1, $zero, 0xF0
    ctx->r3 = ADD32(0, 0XF0);
L_801E7D2C:
    // 0x801E7D2C: lui         $t9, 0x107
    ctx->r25 = S32(0X107 << 16);
    // 0x801E7D30: addiu       $t9, $t9, -0xFF8
    ctx->r25 = ADD32(ctx->r25, -0XFF8);
    // 0x801E7D34: ori         $t8, $t8, 0x10
    ctx->r24 = ctx->r24 | 0X10;
    // 0x801E7D38: sw          $t8, 0x0($t2)
    MEM_W(0X0, ctx->r10) = ctx->r24;
    // 0x801E7D3C: sw          $t9, 0x4($t2)
    MEM_W(0X4, ctx->r10) = ctx->r25;
    // 0x801E7D40: lui         $t6, 0xB600
    ctx->r14 = S32(0XB600 << 16);
    // 0x801E7D44: sw          $t6, 0x0($t3)
    MEM_W(0X0, ctx->r11) = ctx->r14;
    // 0x801E7D48: addiu       $t4, $t3, 0x8
    ctx->r12 = ADD32(ctx->r11, 0X8);
    // 0x801E7D4C: addiu       $t7, $zero, -0x1
    ctx->r15 = ADD32(0, -0X1);
    // 0x801E7D50: sw          $t7, 0x4($t3)
    MEM_W(0X4, ctx->r11) = ctx->r15;
    // 0x801E7D54: addiu       $t5, $t4, 0x8
    ctx->r13 = ADD32(ctx->r12, 0X8);
    // 0x801E7D58: addiu       $t9, $zero, 0x4
    ctx->r25 = ADD32(0, 0X4);
    // 0x801E7D5C: lui         $t8, 0xB700
    ctx->r24 = S32(0XB700 << 16);
    // 0x801E7D60: sw          $t8, 0x0($t4)
    MEM_W(0X0, ctx->r12) = ctx->r24;
    // 0x801E7D64: sw          $t9, 0x4($t4)
    MEM_W(0X4, ctx->r12) = ctx->r25;
    // 0x801E7D68: lui         $t6, 0xBB00
    ctx->r14 = S32(0XBB00 << 16);
    // 0x801E7D6C: sw          $t6, 0x0($t5)
    MEM_W(0X0, ctx->r13) = ctx->r14;
    // 0x801E7D70: sw          $zero, 0x4($t5)
    MEM_W(0X4, ctx->r13) = 0;
    // 0x801E7D74: addiu       $a0, $t5, 0x8
    ctx->r4 = ADD32(ctx->r13, 0X8);
    // 0x801E7D78: sw          $a0, 0x4($sp)
    MEM_W(0X4, ctx->r29) = ctx->r4;
    // 0x801E7D7C: lw          $t8, 0x4($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X4);
    // 0x801E7D80: addiu       $t2, $a0, 0x8
    ctx->r10 = ADD32(ctx->r4, 0X8);
    // 0x801E7D84: lui         $t7, 0xE700
    ctx->r15 = S32(0XE700 << 16);
    // 0x801E7D88: lui         $t9, 0xBA00
    ctx->r25 = S32(0XBA00 << 16);
    // 0x801E7D8C: sw          $t7, 0x0($t8)
    MEM_W(0X0, ctx->r24) = ctx->r15;
    // 0x801E7D90: sw          $zero, 0x4($t8)
    MEM_W(0X4, ctx->r24) = 0;
    // 0x801E7D94: ori         $t9, $t9, 0x1402
    ctx->r25 = ctx->r25 | 0X1402;
    // 0x801E7D98: sw          $t9, 0x0($t2)
    MEM_W(0X0, ctx->r10) = ctx->r25;
    // 0x801E7D9C: sw          $zero, 0x4($t2)
    MEM_W(0X4, ctx->r10) = 0;
    // 0x801E7DA0: addiu       $t3, $t2, 0x8
    ctx->r11 = ADD32(ctx->r10, 0X8);
    // 0x801E7DA4: lui         $t6, 0xFA00
    ctx->r14 = S32(0XFA00 << 16);
    // 0x801E7DA8: sw          $t6, 0x0($t3)
    MEM_W(0X0, ctx->r11) = ctx->r14;
    // 0x801E7DAC: lw          $t8, 0x2C($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X2C);
    // 0x801E7DB0: andi        $t6, $t0, 0xFF
    ctx->r14 = ctx->r8 & 0XFF;
    // 0x801E7DB4: sll         $t7, $t6, 16
    ctx->r15 = S32(ctx->r14 << 16);
    // 0x801E7DB8: sll         $t9, $t8, 24
    ctx->r25 = S32(ctx->r24 << 24);
    // 0x801E7DBC: or          $t8, $t9, $t7
    ctx->r24 = ctx->r25 | ctx->r15;
    // 0x801E7DC0: andi        $t6, $t1, 0xFF
    ctx->r14 = ctx->r9 & 0XFF;
    // 0x801E7DC4: sll         $t9, $t6, 8
    ctx->r25 = S32(ctx->r14 << 8);
    // 0x801E7DC8: or          $t7, $t8, $t9
    ctx->r15 = ctx->r24 | ctx->r25;
    // 0x801E7DCC: andi        $t6, $v0, 0xFF
    ctx->r14 = ctx->r2 & 0XFF;
    // 0x801E7DD0: or          $t8, $t7, $t6
    ctx->r24 = ctx->r15 | ctx->r14;
    // 0x801E7DD4: sw          $t8, 0x4($t3)
    MEM_W(0X4, ctx->r11) = ctx->r24;
    // 0x801E7DD8: addiu       $t4, $t3, 0x8
    ctx->r12 = ADD32(ctx->r11, 0X8);
    // 0x801E7DDC: lui         $t7, 0xFFFD
    ctx->r15 = S32(0XFFFD << 16);
    // 0x801E7DE0: lui         $t9, 0xFCFF
    ctx->r25 = S32(0XFCFF << 16);
    // 0x801E7DE4: ori         $t9, $t9, 0xFFFF
    ctx->r25 = ctx->r25 | 0XFFFF;
    // 0x801E7DE8: ori         $t7, $t7, 0xF6FB
    ctx->r15 = ctx->r15 | 0XF6FB;
    // 0x801E7DEC: sw          $t7, 0x4($t4)
    MEM_W(0X4, ctx->r12) = ctx->r15;
    // 0x801E7DF0: sw          $t9, 0x0($t4)
    MEM_W(0X0, ctx->r12) = ctx->r25;
    // 0x801E7DF4: lui         $t6, 0xB900
    ctx->r14 = S32(0XB900 << 16);
    // 0x801E7DF8: addiu       $t5, $t4, 0x8
    ctx->r13 = ADD32(ctx->r12, 0X8);
    // 0x801E7DFC: ori         $t6, $t6, 0x31D
    ctx->r14 = ctx->r14 | 0X31D;
    // 0x801E7E00: addiu       $t9, $a3, 0x1
    ctx->r25 = ADD32(ctx->r7, 0X1);
    // 0x801E7E04: sw          $t6, 0x0($t5)
    MEM_W(0X0, ctx->r13) = ctx->r14;
    // 0x801E7E08: lui         $t8, 0x50
    ctx->r24 = S32(0X50 << 16);
    // 0x801E7E0C: andi        $t7, $t9, 0x3FF
    ctx->r15 = ctx->r25 & 0X3FF;
    // 0x801E7E10: ori         $t8, $t8, 0x41C8
    ctx->r24 = ctx->r24 | 0X41C8;
    // 0x801E7E14: sll         $t6, $t7, 14
    ctx->r14 = S32(ctx->r15 << 14);
    // 0x801E7E18: sw          $t8, 0x4($t5)
    MEM_W(0X4, ctx->r13) = ctx->r24;
    // 0x801E7E1C: addiu       $t9, $v1, 0x1
    ctx->r25 = ADD32(ctx->r3, 0X1);
    // 0x801E7E20: lui         $at, 0xF600
    ctx->r1 = S32(0XF600 << 16);
    // 0x801E7E24: or          $t8, $t6, $at
    ctx->r24 = ctx->r14 | ctx->r1;
    // 0x801E7E28: andi        $t7, $t9, 0x3FF
    ctx->r15 = ctx->r25 & 0X3FF;
    // 0x801E7E2C: sll         $t6, $t7, 2
    ctx->r14 = S32(ctx->r15 << 2);
    // 0x801E7E30: or          $t9, $t8, $t6
    ctx->r25 = ctx->r24 | ctx->r14;
    // 0x801E7E34: addiu       $t0, $t5, 0x8
    ctx->r8 = ADD32(ctx->r13, 0X8);
    // 0x801E7E38: sw          $t9, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r25;
    // 0x801E7E3C: andi        $t6, $a2, 0x3FF
    ctx->r14 = ctx->r6 & 0X3FF;
    // 0x801E7E40: andi        $t7, $a1, 0x3FF
    ctx->r15 = ctx->r5 & 0X3FF;
    // 0x801E7E44: sll         $t8, $t7, 14
    ctx->r24 = S32(ctx->r15 << 14);
    // 0x801E7E48: sll         $t9, $t6, 2
    ctx->r25 = S32(ctx->r14 << 2);
    // 0x801E7E4C: or          $t7, $t8, $t9
    ctx->r15 = ctx->r24 | ctx->r25;
    // 0x801E7E50: addiu       $t1, $t0, 0x8
    ctx->r9 = ADD32(ctx->r8, 0X8);
    // 0x801E7E54: sw          $t7, 0x4($t0)
    MEM_W(0X4, ctx->r8) = ctx->r15;
    // 0x801E7E58: lui         $t6, 0xB900
    ctx->r14 = S32(0XB900 << 16);
    // 0x801E7E5C: ori         $t6, $t6, 0x2
    ctx->r14 = ctx->r14 | 0X2;
    // 0x801E7E60: sw          $t6, 0x0($t1)
    MEM_W(0X0, ctx->r9) = ctx->r14;
    // 0x801E7E64: sw          $zero, 0x4($t1)
    MEM_W(0X4, ctx->r9) = 0;
    // 0x801E7E68: addiu       $v0, $t1, 0x8
    ctx->r2 = ADD32(ctx->r9, 0X8);
L_801E7E6C:
    // 0x801E7E6C: jr          $ra
    // 0x801E7E70: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    return;
    // 0x801E7E70: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
;}
RECOMP_FUNC void func_801E7E74(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801E7E74: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x801E7E78: lui         $t6, 0x380
    ctx->r14 = S32(0X380 << 16);
    // 0x801E7E7C: ori         $t6, $t6, 0x10
    ctx->r14 = ctx->r14 | 0X10;
    // 0x801E7E80: lui         $t7, 0x107
    ctx->r15 = S32(0X107 << 16);
    // 0x801E7E84: addiu       $t7, $t7, -0xFF8
    ctx->r15 = ADD32(ctx->r15, -0XFF8);
    // 0x801E7E88: sw          $t6, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r14;
    // 0x801E7E8C: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x801E7E90: sw          $t7, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r15;
    // 0x801E7E94: or          $v1, $a0, $zero
    ctx->r3 = ctx->r4 | 0;
    // 0x801E7E98: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x801E7E9C: lui         $t8, 0xB600
    ctx->r24 = S32(0XB600 << 16);
    // 0x801E7EA0: addiu       $t9, $zero, -0x1
    ctx->r25 = ADD32(0, -0X1);
    // 0x801E7EA4: or          $t0, $a0, $zero
    ctx->r8 = ctx->r4 | 0;
    // 0x801E7EA8: sw          $t9, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r25;
    // 0x801E7EAC: sw          $t8, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r24;
    // 0x801E7EB0: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x801E7EB4: lui         $t3, 0xB700
    ctx->r11 = S32(0XB700 << 16);
    // 0x801E7EB8: addiu       $t4, $zero, 0x4
    ctx->r12 = ADD32(0, 0X4);
    // 0x801E7EBC: or          $t1, $a0, $zero
    ctx->r9 = ctx->r4 | 0;
    // 0x801E7EC0: sw          $t4, 0x4($t0)
    MEM_W(0X4, ctx->r8) = ctx->r12;
    // 0x801E7EC4: sw          $t3, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r11;
    // 0x801E7EC8: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x801E7ECC: lui         $t5, 0xBB00
    ctx->r13 = S32(0XBB00 << 16);
    // 0x801E7ED0: or          $t2, $a0, $zero
    ctx->r10 = ctx->r4 | 0;
    // 0x801E7ED4: sw          $t5, 0x0($t1)
    MEM_W(0X0, ctx->r9) = ctx->r13;
    // 0x801E7ED8: sw          $zero, 0x4($t1)
    MEM_W(0X4, ctx->r9) = 0;
    // 0x801E7EDC: lui         $t6, 0xE700
    ctx->r14 = S32(0XE700 << 16);
    // 0x801E7EE0: sw          $t6, 0x0($t2)
    MEM_W(0X0, ctx->r10) = ctx->r14;
    // 0x801E7EE4: sw          $zero, 0x4($t2)
    MEM_W(0X4, ctx->r10) = 0;
    // 0x801E7EE8: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x801E7EEC: lw          $v1, 0x10($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X10);
    // 0x801E7EF0: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x801E7EF4: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x801E7EF8: lui         $t7, 0xBA00
    ctx->r15 = S32(0XBA00 << 16);
    // 0x801E7EFC: ori         $t7, $t7, 0x1402
    ctx->r15 = ctx->r15 | 0X1402;
    // 0x801E7F00: or          $t0, $a0, $zero
    ctx->r8 = ctx->r4 | 0;
    // 0x801E7F04: lui         $t8, 0xFCFF
    ctx->r24 = S32(0XFCFF << 16);
    // 0x801E7F08: lui         $t9, 0xFFFD
    ctx->r25 = S32(0XFFFD << 16);
    // 0x801E7F0C: sw          $t7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r15;
    // 0x801E7F10: sw          $zero, 0x4($v0)
    MEM_W(0X4, ctx->r2) = 0;
    // 0x801E7F14: ori         $t9, $t9, 0xF6FB
    ctx->r25 = ctx->r25 | 0XF6FB;
    // 0x801E7F18: ori         $t8, $t8, 0xFFFF
    ctx->r24 = ctx->r24 | 0XFFFF;
    // 0x801E7F1C: addiu       $at, $zero, 0xFF
    ctx->r1 = ADD32(0, 0XFF);
    // 0x801E7F20: sw          $t8, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r24;
    // 0x801E7F24: sw          $t9, 0x4($t0)
    MEM_W(0X4, ctx->r8) = ctx->r25;
    // 0x801E7F28: bne         $v1, $at, L_801E7F54
    if (ctx->r3 != ctx->r1) {
        // 0x801E7F2C: addiu       $a0, $a0, 0x8
        ctx->r4 = ADD32(ctx->r4, 0X8);
            goto L_801E7F54;
    }
    // 0x801E7F2C: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x801E7F30: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x801E7F34: lui         $t3, 0xB900
    ctx->r11 = S32(0XB900 << 16);
    // 0x801E7F38: lui         $t4, 0xF0A
    ctx->r12 = S32(0XF0A << 16);
    // 0x801E7F3C: ori         $t4, $t4, 0x4000
    ctx->r12 = ctx->r12 | 0X4000;
    // 0x801E7F40: ori         $t3, $t3, 0x31D
    ctx->r11 = ctx->r11 | 0X31D;
    // 0x801E7F44: sw          $t3, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r11;
    // 0x801E7F48: sw          $t4, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r12;
    // 0x801E7F4C: b           L_801E7F74
    // 0x801E7F50: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
        goto L_801E7F74;
    // 0x801E7F50: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
L_801E7F54:
    // 0x801E7F54: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x801E7F58: lui         $t5, 0xB900
    ctx->r13 = S32(0XB900 << 16);
    // 0x801E7F5C: lui         $t6, 0x50
    ctx->r14 = S32(0X50 << 16);
    // 0x801E7F60: ori         $t6, $t6, 0x41C8
    ctx->r14 = ctx->r14 | 0X41C8;
    // 0x801E7F64: ori         $t5, $t5, 0x31D
    ctx->r13 = ctx->r13 | 0X31D;
    // 0x801E7F68: sw          $t5, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r13;
    // 0x801E7F6C: sw          $t6, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r14;
    // 0x801E7F70: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
L_801E7F74:
    // 0x801E7F74: lui         $t7, 0xED00
    ctx->r15 = S32(0XED00 << 16);
    // 0x801E7F78: lui         $t8, 0x6A
    ctx->r24 = S32(0X6A << 16);
    // 0x801E7F7C: addiu       $t8, $t8, -0x3C44
    ctx->r24 = ADD32(ctx->r24, -0X3C44);
    // 0x801E7F80: sw          $t7, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r15;
    // 0x801E7F84: addiu       $t1, $a0, 0x8
    ctx->r9 = ADD32(ctx->r4, 0X8);
    // 0x801E7F88: lui         $t9, 0xB900
    ctx->r25 = S32(0XB900 << 16);
    // 0x801E7F8C: sw          $t8, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r24;
    // 0x801E7F90: ori         $t9, $t9, 0x2
    ctx->r25 = ctx->r25 | 0X2;
    // 0x801E7F94: sw          $t9, 0x0($t1)
    MEM_W(0X0, ctx->r9) = ctx->r25;
    // 0x801E7F98: sw          $zero, 0x4($t1)
    MEM_W(0X4, ctx->r9) = 0;
    // 0x801E7F9C: addiu       $t2, $t1, 0x8
    ctx->r10 = ADD32(ctx->r9, 0X8);
    // 0x801E7FA0: lui         $t3, 0xFA00
    ctx->r11 = S32(0XFA00 << 16);
    // 0x801E7FA4: andi        $t6, $a2, 0xFF
    ctx->r14 = ctx->r6 & 0XFF;
    // 0x801E7FA8: sll         $t7, $t6, 16
    ctx->r15 = S32(ctx->r14 << 16);
    // 0x801E7FAC: sw          $t3, 0x0($t2)
    MEM_W(0X0, ctx->r10) = ctx->r11;
    // 0x801E7FB0: andi        $t9, $a3, 0xFF
    ctx->r25 = ctx->r7 & 0XFF;
    // 0x801E7FB4: sll         $t5, $a1, 24
    ctx->r13 = S32(ctx->r5 << 24);
    // 0x801E7FB8: or          $t8, $t5, $t7
    ctx->r24 = ctx->r13 | ctx->r15;
    // 0x801E7FBC: sll         $t3, $t9, 8
    ctx->r11 = S32(ctx->r25 << 8);
    // 0x801E7FC0: or          $t4, $t8, $t3
    ctx->r12 = ctx->r24 | ctx->r11;
    // 0x801E7FC4: andi        $t6, $v1, 0xFF
    ctx->r14 = ctx->r3 & 0XFF;
    // 0x801E7FC8: or          $t5, $t4, $t6
    ctx->r13 = ctx->r12 | ctx->r14;
    // 0x801E7FCC: sw          $t5, 0x4($t2)
    MEM_W(0X4, ctx->r10) = ctx->r13;
    // 0x801E7FD0: jr          $ra
    // 0x801E7FD4: addiu       $v0, $t2, 0x8
    ctx->r2 = ADD32(ctx->r10, 0X8);
    return;
    // 0x801E7FD4: addiu       $v0, $t2, 0x8
    ctx->r2 = ADD32(ctx->r10, 0X8);
;}
RECOMP_FUNC void func_801E7FD8(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    extern int32_t wr64_menu_half_extension(void);
    extern uint32_t wr64_menu_fill_rect(uint8_t*, uint32_t, int32_t, int32_t, int32_t, int32_t, int32_t);
    const int32_t wr64MenuHalf = wr64_menu_half_extension();
    if (wr64MenuHalf > 0) {
        ctx->r2 = S32(wr64_menu_fill_rect(rdram, (uint32_t)ctx->r4,
            (int32_t)ctx->r5, (int32_t)ctx->r6, (int32_t)ctx->r7,
            MEM_W(0x10, ctx->r29), wr64MenuHalf));
        return;
    }
    // 0x801E7FD8: slti        $at, $a1, 0x1A8
    ctx->r1 = SIGNED(ctx->r5) < 0X1A8 ? 1 : 0;
    // 0x801E7FDC: bne         $at, $zero, L_801E7FF0
    if (ctx->r1 != 0) {
        // 0x801E7FE0: addiu       $v0, $zero, 0x1
        ctx->r2 = ADD32(0, 0X1);
            goto L_801E7FF0;
    }
    // 0x801E7FE0: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
    // 0x801E7FE4: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    // 0x801E7FE8: b           L_801E8024
    // 0x801E7FEC: lw          $v1, 0x10($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X10);
        goto L_801E8024;
    // 0x801E7FEC: lw          $v1, 0x10($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X10);
L_801E7FF0:
    // 0x801E7FF0: bgez        $a3, L_801E8004
    if (SIGNED(ctx->r7) >= 0) {
        // 0x801E7FF4: slti        $at, $a2, 0xF0
        ctx->r1 = SIGNED(ctx->r6) < 0XF0 ? 1 : 0;
            goto L_801E8004;
    }
    // 0x801E7FF4: slti        $at, $a2, 0xF0
    ctx->r1 = SIGNED(ctx->r6) < 0XF0 ? 1 : 0;
    // 0x801E7FF8: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    // 0x801E7FFC: b           L_801E8024
    // 0x801E8000: lw          $v1, 0x10($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X10);
        goto L_801E8024;
    // 0x801E8000: lw          $v1, 0x10($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X10);
L_801E8004:
    // 0x801E8004: bne         $at, $zero, L_801E8018
    if (ctx->r1 != 0) {
        // 0x801E8008: lw          $v1, 0x10($sp)
        ctx->r3 = MEM_W(ctx->r29, 0X10);
            goto L_801E8018;
    }
    // 0x801E8008: lw          $v1, 0x10($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X10);
    // 0x801E800C: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    // 0x801E8010: b           L_801E8024
    // 0x801E8014: lw          $v1, 0x10($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X10);
        goto L_801E8024;
    // 0x801E8014: lw          $v1, 0x10($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X10);
L_801E8018:
    // 0x801E8018: bgez        $v1, L_801E8024
    if (SIGNED(ctx->r3) >= 0) {
        // 0x801E801C: nop
    
            goto L_801E8024;
    }
    // 0x801E801C: nop

    // 0x801E8020: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_801E8024:
    // 0x801E8024: bne         $v0, $zero, L_801E8034
    if (ctx->r2 != 0) {
        // 0x801E8028: slti        $at, $a3, 0x1A8
        ctx->r1 = SIGNED(ctx->r7) < 0X1A8 ? 1 : 0;
            goto L_801E8034;
    }
    // 0x801E8028: slti        $at, $a3, 0x1A8
    ctx->r1 = SIGNED(ctx->r7) < 0X1A8 ? 1 : 0;
    // 0x801E802C: jr          $ra
    // 0x801E8030: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    return;
    // 0x801E8030: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
L_801E8034:
    // 0x801E8034: bgez        $a1, L_801E8040
    if (SIGNED(ctx->r5) >= 0) {
        // 0x801E8038: addiu       $v0, $a0, 0x8
        ctx->r2 = ADD32(ctx->r4, 0X8);
            goto L_801E8040;
    }
    // 0x801E8038: addiu       $v0, $a0, 0x8
    ctx->r2 = ADD32(ctx->r4, 0X8);
    // 0x801E803C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
L_801E8040:
    // 0x801E8040: bne         $at, $zero, L_801E804C
    if (ctx->r1 != 0) {
        // 0x801E8044: andi        $t5, $a1, 0x3FF
        ctx->r13 = ctx->r5 & 0X3FF;
            goto L_801E804C;
    }
    // 0x801E8044: andi        $t5, $a1, 0x3FF
    ctx->r13 = ctx->r5 & 0X3FF;
    // 0x801E8048: addiu       $a3, $zero, 0x1A7
    ctx->r7 = ADD32(0, 0X1A7);
L_801E804C:
    // 0x801E804C: bgez        $a2, L_801E8058
    if (SIGNED(ctx->r6) >= 0) {
        // 0x801E8050: slti        $at, $v1, 0xF0
        ctx->r1 = SIGNED(ctx->r3) < 0XF0 ? 1 : 0;
            goto L_801E8058;
    }
    // 0x801E8050: slti        $at, $v1, 0xF0
    ctx->r1 = SIGNED(ctx->r3) < 0XF0 ? 1 : 0;
    // 0x801E8054: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
L_801E8058:
    // 0x801E8058: bne         $at, $zero, L_801E8064
    if (ctx->r1 != 0) {
        // 0x801E805C: addiu       $t6, $a3, 0x1
        ctx->r14 = ADD32(ctx->r7, 0X1);
            goto L_801E8064;
    }
    // 0x801E805C: addiu       $t6, $a3, 0x1
    ctx->r14 = ADD32(ctx->r7, 0X1);
    // 0x801E8060: addiu       $v1, $zero, 0xEF
    ctx->r3 = ADD32(0, 0XEF);
L_801E8064:
    // 0x801E8064: andi        $t7, $t6, 0x3FF
    ctx->r15 = ctx->r14 & 0X3FF;
    // 0x801E8068: sll         $t8, $t7, 14
    ctx->r24 = S32(ctx->r15 << 14);
    // 0x801E806C: lui         $at, 0xF600
    ctx->r1 = S32(0XF600 << 16);
    // 0x801E8070: addiu       $t1, $v1, 0x1
    ctx->r9 = ADD32(ctx->r3, 0X1);
    // 0x801E8074: andi        $t2, $t1, 0x3FF
    ctx->r10 = ctx->r9 & 0X3FF;
    // 0x801E8078: or          $t9, $t8, $at
    ctx->r25 = ctx->r24 | ctx->r1;
    // 0x801E807C: andi        $t7, $a2, 0x3FF
    ctx->r15 = ctx->r6 & 0X3FF;
    // 0x801E8080: sll         $t8, $t7, 2
    ctx->r24 = S32(ctx->r15 << 2);
    // 0x801E8084: sll         $t3, $t2, 2
    ctx->r11 = S32(ctx->r10 << 2);
    // 0x801E8088: sll         $t6, $t5, 14
    ctx->r14 = S32(ctx->r13 << 14);
    // 0x801E808C: or          $t1, $t6, $t8
    ctx->r9 = ctx->r14 | ctx->r24;
    // 0x801E8090: or          $t4, $t9, $t3
    ctx->r12 = ctx->r25 | ctx->r11;
    // 0x801E8094: sw          $t4, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r12;
    // 0x801E8098: sw          $t1, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r9;
    // 0x801E809C: jr          $ra
    // 0x801E80A0: nop

    return;
    // 0x801E80A0: nop

    // 0x801E80A4: nop

    // 0x801E80A8: nop

    // 0x801E80AC: nop

;}
RECOMP_FUNC void func_801E80B0(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // Regular menu glyphs share the frame's centered signed coordinate plane.
    // The separate vertex-font path keeps its original producer behavior.
    extern int32_t wr64_menu_half_extension(void);
    extern void wr64_menu_promote_waku_rect(uint8_t*, uint32_t, int32_t, int32_t);
    const int32_t wr64FontHalf = MEM_W(0x14, ctx->r29) != 2 ? wr64_menu_half_extension() : 0;
    const int32_t wr64FontX = (int32_t)ctx->r7;
    // 0x801E80B0: addiu       $sp, $sp, -0x70
    ctx->r29 = ADD32(ctx->r29, -0X70);
    // 0x801E80B4: lw          $t6, 0x84($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X84);
    // 0x801E80B8: sw          $s0, 0x50($sp)
    MEM_W(0X50, ctx->r29) = ctx->r16;
    // 0x801E80BC: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x801E80C0: or          $s0, $a0, $zero
    ctx->r16 = ctx->r4 | 0;
    // 0x801E80C4: sw          $ra, 0x54($sp)
    MEM_W(0X54, ctx->r29) = ctx->r31;
    // 0x801E80C8: sw          $a3, 0x7C($sp)
    MEM_W(0X7C, ctx->r29) = ctx->r7;
    // 0x801E80CC: bne         $t6, $at, L_801E80D8
    if (ctx->r14 != ctx->r1) {
        // 0x801E80D0: addiu       $t3, $zero, 0x1
        ctx->r11 = ADD32(0, 0X1);
            goto L_801E80D8;
    }
    // 0x801E80D0: addiu       $t3, $zero, 0x1
    ctx->r11 = ADD32(0, 0X1);
    // 0x801E80D4: or          $t3, $zero, $zero
    ctx->r11 = 0 | 0;
L_801E80D8:
    // 0x801E80D8: sltiu       $at, $a1, 0x6
    ctx->r1 = ctx->r5 < 0X6 ? 1 : 0;
    // 0x801E80DC: beq         $at, $zero, L_801E8278
    if (ctx->r1 == 0) {
        // 0x801E80E0: sll         $t7, $a1, 2
        ctx->r15 = S32(ctx->r5 << 2);
            goto L_801E8278;
    }
    // 0x801E80E0: sll         $t7, $a1, 2
    ctx->r15 = S32(ctx->r5 << 2);
    // 0x801E80E4: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E80E8: addu        $at, $at, $t7
    gpr jr_addend_801E80F0 = ctx->r15;
    ctx->r1 = ADD32(ctx->r1, ctx->r15);
    // 0x801E80EC: lw          $t7, 0x6E54($at)
    ctx->r15 = ADD32(ctx->r1, 0X6E54);
    // 0x801E80F0: jr          $t7
    // 0x801E80F4: nop

    switch (jr_addend_801E80F0 >> 2) {
        case 0: goto L_801E80F8; break;
        case 1: goto L_801E8138; break;
        case 2: goto L_801E8170; break;
        case 3: goto L_801E81B0; break;
        case 4: goto L_801E81F4; break;
        case 5: goto L_801E8238; break;
        default: switch_error(__func__, 0x801E80F0, 0x80226E54);
    }
    // 0x801E80F4: nop

L_801E80F8:
    // 0x801E80F8: sltiu       $at, $a2, 0x28
    ctx->r1 = ctx->r6 < 0X28 ? 1 : 0;
    // 0x801E80FC: bne         $at, $zero, L_801E8108
    if (ctx->r1 != 0) {
        // 0x801E8100: addiu       $t8, $zero, 0x18
        ctx->r24 = ADD32(0, 0X18);
            goto L_801E8108;
    }
    // 0x801E8100: addiu       $t8, $zero, 0x18
    ctx->r24 = ADD32(0, 0X18);
    // 0x801E8104: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
L_801E8108:
    // 0x801E8108: sll         $t4, $a2, 4
    ctx->r12 = S32(ctx->r6 << 4);
    // 0x801E810C: subu        $t4, $t4, $a2
    ctx->r12 = SUB32(ctx->r12, ctx->r6);
    // 0x801E8110: lui         $t5, 0x103
    ctx->r13 = S32(0X103 << 16);
    // 0x801E8114: addiu       $t5, $t5, 0x3CB8
    ctx->r13 = ADD32(ctx->r13, 0X3CB8);
    // 0x801E8118: sll         $t4, $t4, 5
    ctx->r12 = S32(ctx->r12 << 5);
    // 0x801E811C: addiu       $t9, $zero, 0x14
    ctx->r25 = ADD32(0, 0X14);
    // 0x801E8120: addu        $a3, $t4, $t5
    ctx->r7 = ADD32(ctx->r12, ctx->r13);
    // 0x801E8124: sw          $t8, 0x64($sp)
    MEM_W(0X64, ctx->r29) = ctx->r24;
    // 0x801E8128: sw          $t9, 0x5C($sp)
    MEM_W(0X5C, ctx->r29) = ctx->r25;
    // 0x801E812C: sw          $a3, 0x6C($sp)
    MEM_W(0X6C, ctx->r29) = ctx->r7;
    // 0x801E8130: b           L_801E8278
    // 0x801E8134: sw          $zero, 0x58($sp)
    MEM_W(0X58, ctx->r29) = 0;
        goto L_801E8278;
    // 0x801E8134: sw          $zero, 0x58($sp)
    MEM_W(0X58, ctx->r29) = 0;
L_801E8138:
    // 0x801E8138: sltiu       $at, $a2, 0x2A
    ctx->r1 = ctx->r6 < 0X2A ? 1 : 0;
    // 0x801E813C: bne         $at, $zero, L_801E8148
    if (ctx->r1 != 0) {
        // 0x801E8140: addiu       $t6, $zero, 0x8
        ctx->r14 = ADD32(0, 0X8);
            goto L_801E8148;
    }
    // 0x801E8140: addiu       $t6, $zero, 0x8
    ctx->r14 = ADD32(0, 0X8);
    // 0x801E8144: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
L_801E8148:
    // 0x801E8148: lui         $t9, 0x104
    ctx->r25 = S32(0X104 << 16);
    // 0x801E814C: addiu       $t9, $t9, -0x7840
    ctx->r25 = ADD32(ctx->r25, -0X7840);
    // 0x801E8150: sll         $t8, $a2, 6
    ctx->r24 = S32(ctx->r6 << 6);
    // 0x801E8154: addiu       $t7, $zero, 0x8
    ctx->r15 = ADD32(0, 0X8);
    // 0x801E8158: addu        $a3, $t8, $t9
    ctx->r7 = ADD32(ctx->r24, ctx->r25);
    // 0x801E815C: sw          $t6, 0x64($sp)
    MEM_W(0X64, ctx->r29) = ctx->r14;
    // 0x801E8160: sw          $t7, 0x5C($sp)
    MEM_W(0X5C, ctx->r29) = ctx->r15;
    // 0x801E8164: sw          $a3, 0x6C($sp)
    MEM_W(0X6C, ctx->r29) = ctx->r7;
    // 0x801E8168: b           L_801E8278
    // 0x801E816C: sw          $zero, 0x58($sp)
    MEM_W(0X58, ctx->r29) = 0;
        goto L_801E8278;
    // 0x801E816C: sw          $zero, 0x58($sp)
    MEM_W(0X58, ctx->r29) = 0;
L_801E8170:
    // 0x801E8170: sltiu       $at, $a2, 0x2E
    ctx->r1 = ctx->r6 < 0X2E ? 1 : 0;
    // 0x801E8174: bne         $at, $zero, L_801E8180
    if (ctx->r1 != 0) {
        // 0x801E8178: addiu       $t4, $zero, 0x10
        ctx->r12 = ADD32(0, 0X10);
            goto L_801E8180;
    }
    // 0x801E8178: addiu       $t4, $zero, 0x10
    ctx->r12 = ADD32(0, 0X10);
    // 0x801E817C: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
L_801E8180:
    // 0x801E8180: sll         $t6, $a2, 2
    ctx->r14 = S32(ctx->r6 << 2);
    // 0x801E8184: subu        $t6, $t6, $a2
    ctx->r14 = SUB32(ctx->r14, ctx->r6);
    // 0x801E8188: lui         $t7, 0x104
    ctx->r15 = S32(0X104 << 16);
    // 0x801E818C: addiu       $t7, $t7, -0x6DB8
    ctx->r15 = ADD32(ctx->r15, -0X6DB8);
    // 0x801E8190: sll         $t6, $t6, 6
    ctx->r14 = S32(ctx->r14 << 6);
    // 0x801E8194: addiu       $t5, $zero, 0xC
    ctx->r13 = ADD32(0, 0XC);
    // 0x801E8198: addu        $a3, $t6, $t7
    ctx->r7 = ADD32(ctx->r14, ctx->r15);
    // 0x801E819C: sw          $t4, 0x64($sp)
    MEM_W(0X64, ctx->r29) = ctx->r12;
    // 0x801E81A0: sw          $t5, 0x5C($sp)
    MEM_W(0X5C, ctx->r29) = ctx->r13;
    // 0x801E81A4: sw          $a3, 0x6C($sp)
    MEM_W(0X6C, ctx->r29) = ctx->r7;
    // 0x801E81A8: b           L_801E8278
    // 0x801E81AC: sw          $zero, 0x58($sp)
    MEM_W(0X58, ctx->r29) = 0;
        goto L_801E8278;
    // 0x801E81AC: sw          $zero, 0x58($sp)
    MEM_W(0X58, ctx->r29) = 0;
L_801E81B0:
    // 0x801E81B0: sltiu       $at, $a2, 0xC
    ctx->r1 = ctx->r6 < 0XC ? 1 : 0;
    // 0x801E81B4: bne         $at, $zero, L_801E81C0
    if (ctx->r1 != 0) {
        // 0x801E81B8: addiu       $t8, $zero, 0xC
        ctx->r24 = ADD32(0, 0XC);
            goto L_801E81C0;
    }
    // 0x801E81B8: addiu       $t8, $zero, 0xC
    ctx->r24 = ADD32(0, 0XC);
    // 0x801E81BC: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
L_801E81C0:
    // 0x801E81C0: sll         $t4, $a2, 2
    ctx->r12 = S32(ctx->r6 << 2);
    // 0x801E81C4: subu        $t4, $t4, $a2
    ctx->r12 = SUB32(ctx->r12, ctx->r6);
    // 0x801E81C8: lui         $t6, 0x104
    ctx->r14 = S32(0X104 << 16);
    // 0x801E81CC: addiu       $t6, $t6, -0x4B30
    ctx->r14 = ADD32(ctx->r14, -0X4B30);
    // 0x801E81D0: sll         $t5, $t4, 8
    ctx->r13 = S32(ctx->r12 << 8);
    // 0x801E81D4: addiu       $t9, $zero, 0x10
    ctx->r25 = ADD32(0, 0X10);
    // 0x801E81D8: addu        $a3, $t5, $t6
    ctx->r7 = ADD32(ctx->r13, ctx->r14);
    // 0x801E81DC: addiu       $v1, $zero, 0x1
    ctx->r3 = ADD32(0, 0X1);
    // 0x801E81E0: sw          $t8, 0x64($sp)
    MEM_W(0X64, ctx->r29) = ctx->r24;
    // 0x801E81E4: sw          $t9, 0x5C($sp)
    MEM_W(0X5C, ctx->r29) = ctx->r25;
    // 0x801E81E8: sw          $v1, 0x58($sp)
    MEM_W(0X58, ctx->r29) = ctx->r3;
    // 0x801E81EC: b           L_801E8278
    // 0x801E81F0: sw          $a3, 0x6C($sp)
    MEM_W(0X6C, ctx->r29) = ctx->r7;
        goto L_801E8278;
    // 0x801E81F0: sw          $a3, 0x6C($sp)
    MEM_W(0X6C, ctx->r29) = ctx->r7;
L_801E81F4:
    // 0x801E81F4: sltiu       $at, $a2, 0xA
    ctx->r1 = ctx->r6 < 0XA ? 1 : 0;
    // 0x801E81F8: bne         $at, $zero, L_801E8204
    if (ctx->r1 != 0) {
        // 0x801E81FC: addiu       $t7, $zero, 0xC
        ctx->r15 = ADD32(0, 0XC);
            goto L_801E8204;
    }
    // 0x801E81FC: addiu       $t7, $zero, 0xC
    ctx->r15 = ADD32(0, 0XC);
    // 0x801E8200: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
L_801E8204:
    // 0x801E8204: sll         $t9, $a2, 2
    ctx->r25 = S32(ctx->r6 << 2);
    // 0x801E8208: subu        $t9, $t9, $a2
    ctx->r25 = SUB32(ctx->r25, ctx->r6);
    // 0x801E820C: lui         $t5, 0x104
    ctx->r13 = S32(0X104 << 16);
    // 0x801E8210: addiu       $t5, $t5, -0x4B30
    ctx->r13 = ADD32(ctx->r13, -0X4B30);
    // 0x801E8214: sll         $t4, $t9, 8
    ctx->r12 = S32(ctx->r25 << 8);
    // 0x801E8218: addiu       $t8, $zero, 0x10
    ctx->r24 = ADD32(0, 0X10);
    // 0x801E821C: addu        $a3, $t4, $t5
    ctx->r7 = ADD32(ctx->r12, ctx->r13);
    // 0x801E8220: addiu       $v1, $zero, 0x1
    ctx->r3 = ADD32(0, 0X1);
    // 0x801E8224: sw          $t7, 0x64($sp)
    MEM_W(0X64, ctx->r29) = ctx->r15;
    // 0x801E8228: sw          $t8, 0x5C($sp)
    MEM_W(0X5C, ctx->r29) = ctx->r24;
    // 0x801E822C: sw          $v1, 0x58($sp)
    MEM_W(0X58, ctx->r29) = ctx->r3;
    // 0x801E8230: b           L_801E8278
    // 0x801E8234: sw          $a3, 0x6C($sp)
    MEM_W(0X6C, ctx->r29) = ctx->r7;
        goto L_801E8278;
    // 0x801E8234: sw          $a3, 0x6C($sp)
    MEM_W(0X6C, ctx->r29) = ctx->r7;
L_801E8238:
    // 0x801E8238: sltiu       $at, $a2, 0xB
    ctx->r1 = ctx->r6 < 0XB ? 1 : 0;
    // 0x801E823C: bne         $at, $zero, L_801E8248
    if (ctx->r1 != 0) {
        // 0x801E8240: addiu       $t6, $zero, 0x10
        ctx->r14 = ADD32(0, 0X10);
            goto L_801E8248;
    }
    // 0x801E8240: addiu       $t6, $zero, 0x10
    ctx->r14 = ADD32(0, 0X10);
    // 0x801E8244: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
L_801E8248:
    // 0x801E8248: sll         $t8, $a2, 2
    ctx->r24 = S32(ctx->r6 << 2);
    // 0x801E824C: addu        $t8, $t8, $a2
    ctx->r24 = ADD32(ctx->r24, ctx->r6);
    // 0x801E8250: lui         $t4, 0x104
    ctx->r12 = S32(0X104 << 16);
    // 0x801E8254: addiu       $t4, $t4, -0x2728
    ctx->r12 = ADD32(ctx->r12, -0X2728);
    // 0x801E8258: sll         $t9, $t8, 8
    ctx->r25 = S32(ctx->r24 << 8);
    // 0x801E825C: addiu       $t7, $zero, 0x14
    ctx->r15 = ADD32(0, 0X14);
    // 0x801E8260: addu        $a3, $t9, $t4
    ctx->r7 = ADD32(ctx->r25, ctx->r12);
    // 0x801E8264: addiu       $v1, $zero, 0x1
    ctx->r3 = ADD32(0, 0X1);
    // 0x801E8268: sw          $t6, 0x64($sp)
    MEM_W(0X64, ctx->r29) = ctx->r14;
    // 0x801E826C: sw          $t7, 0x5C($sp)
    MEM_W(0X5C, ctx->r29) = ctx->r15;
    // 0x801E8270: sw          $v1, 0x58($sp)
    MEM_W(0X58, ctx->r29) = ctx->r3;
    // 0x801E8274: sw          $a3, 0x6C($sp)
    MEM_W(0X6C, ctx->r29) = ctx->r7;
L_801E8278:
    // 0x801E8278: lw          $t5, 0x7C($sp)
    ctx->r13 = MEM_W(ctx->r29, 0X7C);
    // 0x801E827C: lw          $v1, 0x58($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X58);
    // 0x801E8280: lw          $a3, 0x6C($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X6C);
    // 0x801E8284: slti        $at, $t5, 0x1A8
    ctx->r1 = SIGNED(ctx->r13) < 0X1A8 ? 1 : 0;
    if (wr64FontHalf > 0) ctx->r1 = wr64FontX < 424 + wr64FontHalf;
    // 0x801E8288: bne         $at, $zero, L_801E82A0
    if (ctx->r1 != 0) {
        // 0x801E828C: addiu       $v0, $zero, 0x1
        ctx->r2 = ADD32(0, 0X1);
            goto L_801E82A0;
    }
    // 0x801E828C: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
    // 0x801E8290: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    // 0x801E8294: lwc1        $f0, 0xB8($sp)
    ctx->f0.u32l = MEM_W(ctx->r29, 0XB8);
    // 0x801E8298: b           L_801E8344
    // 0x801E829C: lw          $t2, 0x80($sp)
    ctx->r10 = MEM_W(ctx->r29, 0X80);
        goto L_801E8344;
    // 0x801E829C: lw          $t2, 0x80($sp)
    ctx->r10 = MEM_W(ctx->r29, 0X80);
L_801E82A0:
    // 0x801E82A0: lw          $t6, 0x64($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X64);
    // 0x801E82A4: lwc1        $f0, 0xB8($sp)
    ctx->f0.u32l = MEM_W(ctx->r29, 0XB8);
    // 0x801E82A8: lui         $at, 0x4F80
    ctx->r1 = S32(0X4F80 << 16);
    // 0x801E82AC: mtc1        $t6, $f4
    ctx->f4.u32l = ctx->r14;
    // 0x801E82B0: lw          $t2, 0x80($sp)
    ctx->r10 = MEM_W(ctx->r29, 0X80);
    // 0x801E82B4: bgez        $t6, L_801E82C8
    if (SIGNED(ctx->r14) >= 0) {
        // 0x801E82B8: cvt.s.w     $f6, $f4
        CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
            goto L_801E82C8;
    }
    // 0x801E82B8: cvt.s.w     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
    // 0x801E82BC: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x801E82C0: nop

    // 0x801E82C4: add.s       $f6, $f6, $f8
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f6.fl = ctx->f6.fl + ctx->f8.fl;
L_801E82C8:
    // 0x801E82C8: mul.s       $f10, $f6, $f0
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f10.fl = MUL_S(ctx->f6.fl, ctx->f0.fl);
    // 0x801E82CC: lw          $t9, 0x7C($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X7C);
    // 0x801E82D0: slti        $at, $t2, 0xF0
    ctx->r1 = SIGNED(ctx->r10) < 0XF0 ? 1 : 0;
    // 0x801E82D4: trunc.w.s   $f16, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    ctx->f16.u32l = TRUNC_W_S(ctx->f10.fl);
    // 0x801E82D8: mfc1        $t8, $f16
    ctx->r24 = (int32_t)ctx->f16.u32l;
    // 0x801E82DC: nop

    // 0x801E82E0: addu        $t4, $t8, $t9
    ctx->r12 = ADD32(ctx->r24, ctx->r25);
    if (wr64FontHalf > 0) ctx->r12 = ADD32(ctx->r12, wr64FontHalf);
    // 0x801E82E4: bgez        $t4, L_801E82F8
    if (SIGNED(ctx->r12) >= 0) {
        // 0x801E82E8: nop
    
            goto L_801E82F8;
    }
    // 0x801E82E8: nop

    // 0x801E82EC: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    // 0x801E82F0: b           L_801E8344
    // 0x801E82F4: lw          $t2, 0x80($sp)
    ctx->r10 = MEM_W(ctx->r29, 0X80);
        goto L_801E8344;
    // 0x801E82F4: lw          $t2, 0x80($sp)
    ctx->r10 = MEM_W(ctx->r29, 0X80);
L_801E82F8:
    // 0x801E82F8: bne         $at, $zero, L_801E8308
    if (ctx->r1 != 0) {
        // 0x801E82FC: lw          $t5, 0x5C($sp)
        ctx->r13 = MEM_W(ctx->r29, 0X5C);
            goto L_801E8308;
    }
    // 0x801E82FC: lw          $t5, 0x5C($sp)
    ctx->r13 = MEM_W(ctx->r29, 0X5C);
    // 0x801E8300: b           L_801E8344
    // 0x801E8304: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
        goto L_801E8344;
    // 0x801E8304: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_801E8308:
    // 0x801E8308: mtc1        $t5, $f18
    ctx->f18.u32l = ctx->r13;
    // 0x801E830C: lui         $at, 0x4F80
    ctx->r1 = S32(0X4F80 << 16);
    // 0x801E8310: bgez        $t5, L_801E8324
    if (SIGNED(ctx->r13) >= 0) {
        // 0x801E8314: cvt.s.w     $f4, $f18
        CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    ctx->f4.fl = CVT_S_W(ctx->f18.u32l);
            goto L_801E8324;
    }
    // 0x801E8314: cvt.s.w     $f4, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    ctx->f4.fl = CVT_S_W(ctx->f18.u32l);
    // 0x801E8318: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x801E831C: nop

    // 0x801E8320: add.s       $f4, $f4, $f8
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f4.fl = ctx->f4.fl + ctx->f8.fl;
L_801E8324:
    // 0x801E8324: mul.s       $f6, $f4, $f0
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f6.fl = MUL_S(ctx->f4.fl, ctx->f0.fl);
    // 0x801E8328: trunc.w.s   $f10, $f6
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    ctx->f10.u32l = TRUNC_W_S(ctx->f6.fl);
    // 0x801E832C: mfc1        $t7, $f10
    ctx->r15 = (int32_t)ctx->f10.u32l;
    // 0x801E8330: nop

    // 0x801E8334: addu        $t8, $t7, $t2
    ctx->r24 = ADD32(ctx->r15, ctx->r10);
    // 0x801E8338: bgez        $t8, L_801E8344
    if (SIGNED(ctx->r24) >= 0) {
        // 0x801E833C: nop
    
            goto L_801E8344;
    }
    // 0x801E833C: nop

    // 0x801E8340: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_801E8344:
    // 0x801E8344: bne         $v0, $zero, L_801E8354
    if (ctx->r2 != 0) {
        // 0x801E8348: nop
    
            goto L_801E8354;
    }
    // 0x801E8348: nop

    // 0x801E834C: b           L_801E87EC
    // 0x801E8350: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
        goto L_801E87EC;
    // 0x801E8350: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
L_801E8354:
    // 0x801E8354: lui         $v0, 0x8022
    ctx->r2 = S32(0X8022 << 16);
    // 0x801E8358: addiu       $v0, $v0, 0x6E2C
    ctx->r2 = ADD32(ctx->r2, 0X6E2C);
    // 0x801E835C: lw          $t9, 0x0($v0)
    ctx->r25 = MEM_W(ctx->r2, 0X0);
    // 0x801E8360: lui         $t4, 0xFD70
    ctx->r12 = S32(0XFD70 << 16);
    // 0x801E8364: lui         $t5, 0xF570
    ctx->r13 = S32(0XF570 << 16);
    // 0x801E8368: beq         $a1, $t9, L_801E8374
    if (ctx->r5 == ctx->r25) {
        // 0x801E836C: addiu       $at, $zero, 0x1
        ctx->r1 = ADD32(0, 0X1);
            goto L_801E8374;
    }
    // 0x801E836C: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x801E8370: sw          $a1, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r5;
L_801E8374:
    // 0x801E8374: bne         $v1, $zero, L_801E84D8
    if (ctx->r3 != 0) {
        // 0x801E8378: or          $v0, $s0, $zero
        ctx->r2 = ctx->r16 | 0;
            goto L_801E84D8;
    }
    // 0x801E8378: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
    // 0x801E837C: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801E8380: or          $v1, $s0, $zero
    ctx->r3 = ctx->r16 | 0;
    // 0x801E8384: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801E8388: sw          $t4, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r12;
    // 0x801E838C: sw          $a3, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r7;
    // 0x801E8390: lui         $t6, 0x708
    ctx->r14 = S32(0X708 << 16);
    // 0x801E8394: ori         $t6, $t6, 0x200
    ctx->r14 = ctx->r14 | 0X200;
    // 0x801E8398: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x801E839C: sw          $t6, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r14;
    // 0x801E83A0: sw          $t5, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r13;
    // 0x801E83A4: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801E83A8: lui         $t7, 0xE600
    ctx->r15 = S32(0XE600 << 16);
    // 0x801E83AC: sw          $t7, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r15;
    // 0x801E83B0: or          $t1, $s0, $zero
    ctx->r9 = ctx->r16 | 0;
    // 0x801E83B4: sw          $zero, 0x4($a0)
    MEM_W(0X4, ctx->r4) = 0;
    // 0x801E83B8: lui         $t8, 0xF300
    ctx->r24 = S32(0XF300 << 16);
    // 0x801E83BC: sw          $t8, 0x0($t1)
    MEM_W(0X0, ctx->r9) = ctx->r24;
    // 0x801E83C0: lw          $t9, 0x64($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X64);
    // 0x801E83C4: lw          $t4, 0x5C($sp)
    ctx->r12 = MEM_W(ctx->r29, 0X5C);
    // 0x801E83C8: lw          $t0, 0x64($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X64);
    // 0x801E83CC: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801E83D0: multu       $t9, $t4
    result = U64(U32(ctx->r25)) * U64(U32(ctx->r12)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x801E83D4: srl         $v1, $t0, 3
    ctx->r3 = S32(U32(ctx->r8) >> 3);
    // 0x801E83D8: or          $a2, $v1, $zero
    ctx->r6 = ctx->r3 | 0;
    // 0x801E83DC: or          $v0, $v1, $zero
    ctx->r2 = ctx->r3 | 0;
    // 0x801E83E0: addiu       $a3, $zero, 0x7FF
    ctx->r7 = ADD32(0, 0X7FF);
    // 0x801E83E4: mflo        $a1
    ctx->r5 = lo;
    // 0x801E83E8: addiu       $a1, $a1, 0x1
    ctx->r5 = ADD32(ctx->r5, 0X1);
    // 0x801E83EC: srl         $t5, $a1, 1
    ctx->r13 = S32(U32(ctx->r5) >> 1);
    // 0x801E83F0: addiu       $a1, $t5, -0x1
    ctx->r5 = ADD32(ctx->r13, -0X1);
    // 0x801E83F4: sltiu       $at, $a1, 0x7FF
    ctx->r1 = ctx->r5 < 0X7FF ? 1 : 0;
    // 0x801E83F8: beq         $at, $zero, L_801E8408
    if (ctx->r1 == 0) {
        // 0x801E83FC: nop
    
            goto L_801E8408;
    }
    // 0x801E83FC: nop

    // 0x801E8400: b           L_801E8408
    // 0x801E8404: or          $a3, $a1, $zero
    ctx->r7 = ctx->r5 | 0;
        goto L_801E8408;
    // 0x801E8404: or          $a3, $a1, $zero
    ctx->r7 = ctx->r5 | 0;
L_801E8408:
    // 0x801E8408: bne         $v1, $zero, L_801E8418
    if (ctx->r3 != 0) {
        // 0x801E840C: lui         $at, 0x700
        ctx->r1 = S32(0X700 << 16);
            goto L_801E8418;
    }
    // 0x801E840C: lui         $at, 0x700
    ctx->r1 = S32(0X700 << 16);
    // 0x801E8410: b           L_801E8418
    // 0x801E8414: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
        goto L_801E8418;
    // 0x801E8414: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
L_801E8418:
    // 0x801E8418: bne         $v1, $zero, L_801E8428
    if (ctx->r3 != 0) {
        // 0x801E841C: addiu       $t6, $a2, 0x7FF
        ctx->r14 = ADD32(ctx->r6, 0X7FF);
            goto L_801E8428;
    }
    // 0x801E841C: addiu       $t6, $a2, 0x7FF
    ctx->r14 = ADD32(ctx->r6, 0X7FF);
    // 0x801E8420: b           L_801E8428
    // 0x801E8424: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
        goto L_801E8428;
    // 0x801E8424: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
L_801E8428:
    // 0x801E8428: divu        $zero, $t6, $v0
    lo = S32(U32(ctx->r14) / U32(ctx->r2)); hi = S32(U32(ctx->r14) % U32(ctx->r2));
    // 0x801E842C: mflo        $t7
    ctx->r15 = lo;
    // 0x801E8430: andi        $t8, $t7, 0xFFF
    ctx->r24 = ctx->r15 & 0XFFF;
    // 0x801E8434: andi        $t4, $a3, 0xFFF
    ctx->r12 = ctx->r7 & 0XFFF;
    // 0x801E8438: sll         $t5, $t4, 12
    ctx->r13 = S32(ctx->r12 << 12);
    // 0x801E843C: or          $t9, $t8, $at
    ctx->r25 = ctx->r24 | ctx->r1;
    // 0x801E8440: or          $t6, $t9, $t5
    ctx->r14 = ctx->r25 | ctx->r13;
    // 0x801E8444: sw          $t6, 0x4($t1)
    MEM_W(0X4, ctx->r9) = ctx->r14;
    // 0x801E8448: addiu       $t8, $t0, 0x7
    ctx->r24 = ADD32(ctx->r8, 0X7);
    // 0x801E844C: or          $v1, $s0, $zero
    ctx->r3 = ctx->r16 | 0;
    // 0x801E8450: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801E8454: srl         $t4, $t8, 3
    ctx->r12 = S32(U32(ctx->r24) >> 3);
    // 0x801E8458: lui         $t7, 0xE700
    ctx->r15 = S32(0XE700 << 16);
    // 0x801E845C: sw          $t7, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r15;
    // 0x801E8460: andi        $t9, $t4, 0x1FF
    ctx->r25 = ctx->r12 & 0X1FF;
    // 0x801E8464: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x801E8468: sll         $t5, $t9, 9
    ctx->r13 = S32(ctx->r25 << 9);
    // 0x801E846C: lui         $t7, 0x8
    ctx->r15 = S32(0X8 << 16);
    // 0x801E8470: sw          $zero, 0x4($v1)
    MEM_W(0X4, ctx->r3) = 0;
    // 0x801E8474: lui         $at, 0xF568
    ctx->r1 = S32(0XF568 << 16);
    // 0x801E8478: or          $t6, $t5, $at
    ctx->r14 = ctx->r13 | ctx->r1;
    // 0x801E847C: ori         $t7, $t7, 0x200
    ctx->r15 = ctx->r15 | 0X200;
    // 0x801E8480: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801E8484: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    // 0x801E8488: sw          $t7, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r15;
    // 0x801E848C: sw          $t6, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r14;
    // 0x801E8490: lui         $t8, 0xF200
    ctx->r24 = S32(0XF200 << 16);
    // 0x801E8494: sw          $t8, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r24;
    // 0x801E8498: lw          $t4, 0x64($sp)
    ctx->r12 = MEM_W(ctx->r29, 0X64);
    // 0x801E849C: lw          $t8, 0x5C($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X5C);
    // 0x801E84A0: bne         $v0, $zero, L_801E84AC
    if (ctx->r2 != 0) {
        // 0x801E84A4: nop
    
            goto L_801E84AC;
    }
    // 0x801E84A4: nop

    // 0x801E84A8: break       7
    do_break(2149483688);
L_801E84AC:
    // 0x801E84AC: addiu       $t9, $t4, -0x1
    ctx->r25 = ADD32(ctx->r12, -0X1);
    // 0x801E84B0: sll         $t5, $t9, 2
    ctx->r13 = S32(ctx->r25 << 2);
    // 0x801E84B4: andi        $t6, $t5, 0xFFF
    ctx->r14 = ctx->r13 & 0XFFF;
    // 0x801E84B8: addiu       $t4, $t8, -0x1
    ctx->r12 = ADD32(ctx->r24, -0X1);
    // 0x801E84BC: sll         $t9, $t4, 2
    ctx->r25 = S32(ctx->r12 << 2);
    // 0x801E84C0: andi        $t5, $t9, 0xFFF
    ctx->r13 = ctx->r25 & 0XFFF;
    // 0x801E84C4: sll         $t7, $t6, 12
    ctx->r15 = S32(ctx->r14 << 12);
    // 0x801E84C8: or          $t6, $t7, $t5
    ctx->r14 = ctx->r15 | ctx->r13;
    // 0x801E84CC: sw          $t6, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r14;
    // 0x801E84D0: b           L_801E8644
    // 0x801E84D4: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
        goto L_801E8644;
    // 0x801E84D4: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
L_801E84D8:
    // 0x801E84D8: bne         $v1, $at, L_801E8644
    if (ctx->r3 != ctx->r1) {
        // 0x801E84DC: lui         $t1, 0xF518
        ctx->r9 = S32(0XF518 << 16);
            goto L_801E8644;
    }
    // 0x801E84DC: lui         $t1, 0xF518
    ctx->r9 = S32(0XF518 << 16);
    // 0x801E84E0: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
    // 0x801E84E4: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801E84E8: or          $v1, $s0, $zero
    ctx->r3 = ctx->r16 | 0;
    // 0x801E84EC: lui         $t8, 0xFD18
    ctx->r24 = S32(0XFD18 << 16);
    // 0x801E84F0: sw          $t8, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r24;
    // 0x801E84F4: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801E84F8: sw          $a3, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r7;
    // 0x801E84FC: lui         $t4, 0x708
    ctx->r12 = S32(0X708 << 16);
    // 0x801E8500: ori         $t4, $t4, 0x200
    ctx->r12 = ctx->r12 | 0X200;
    // 0x801E8504: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x801E8508: sw          $t4, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r12;
    // 0x801E850C: sw          $t1, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r9;
    // 0x801E8510: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801E8514: lui         $t9, 0xE600
    ctx->r25 = S32(0XE600 << 16);
    // 0x801E8518: sw          $t9, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r25;
    // 0x801E851C: or          $t0, $s0, $zero
    ctx->r8 = ctx->r16 | 0;
    // 0x801E8520: sw          $zero, 0x4($a0)
    MEM_W(0X4, ctx->r4) = 0;
    // 0x801E8524: lui         $t7, 0xF300
    ctx->r15 = S32(0XF300 << 16);
    // 0x801E8528: sw          $t7, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r15;
    // 0x801E852C: lw          $t5, 0x64($sp)
    ctx->r13 = MEM_W(ctx->r29, 0X64);
    // 0x801E8530: lw          $t6, 0x5C($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X5C);
    // 0x801E8534: lw          $v1, 0x64($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X64);
    // 0x801E8538: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801E853C: multu       $t5, $t6
    result = U64(U32(ctx->r13)) * U64(U32(ctx->r14)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x801E8540: sll         $t8, $v1, 2
    ctx->r24 = S32(ctx->r3 << 2);
    // 0x801E8544: srl         $t4, $t8, 3
    ctx->r12 = S32(U32(ctx->r24) >> 3);
    // 0x801E8548: addiu       $a3, $zero, 0x7FF
    ctx->r7 = ADD32(0, 0X7FF);
    // 0x801E854C: mflo        $a1
    ctx->r5 = lo;
    // 0x801E8550: addiu       $a1, $a1, -0x1
    ctx->r5 = ADD32(ctx->r5, -0X1);
    // 0x801E8554: sltiu       $at, $a1, 0x7FF
    ctx->r1 = ctx->r5 < 0X7FF ? 1 : 0;
    // 0x801E8558: beq         $at, $zero, L_801E8568
    if (ctx->r1 == 0) {
        // 0x801E855C: nop
    
            goto L_801E8568;
    }
    // 0x801E855C: nop

    // 0x801E8560: b           L_801E8568
    // 0x801E8564: or          $a3, $a1, $zero
    ctx->r7 = ctx->r5 | 0;
        goto L_801E8568;
    // 0x801E8564: or          $a3, $a1, $zero
    ctx->r7 = ctx->r5 | 0;
L_801E8568:
    // 0x801E8568: bne         $t4, $zero, L_801E8578
    if (ctx->r12 != 0) {
        // 0x801E856C: or          $v1, $t4, $zero
        ctx->r3 = ctx->r12 | 0;
            goto L_801E8578;
    }
    // 0x801E856C: or          $v1, $t4, $zero
    ctx->r3 = ctx->r12 | 0;
    // 0x801E8570: b           L_801E857C
    // 0x801E8574: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
        goto L_801E857C;
    // 0x801E8574: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
L_801E8578:
    // 0x801E8578: or          $a2, $v1, $zero
    ctx->r6 = ctx->r3 | 0;
L_801E857C:
    // 0x801E857C: bne         $v1, $zero, L_801E858C
    if (ctx->r3 != 0) {
        // 0x801E8580: addiu       $t9, $a2, 0x7FF
        ctx->r25 = ADD32(ctx->r6, 0X7FF);
            goto L_801E858C;
    }
    // 0x801E8580: addiu       $t9, $a2, 0x7FF
    ctx->r25 = ADD32(ctx->r6, 0X7FF);
    // 0x801E8584: b           L_801E8590
    // 0x801E8588: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
        goto L_801E8590;
    // 0x801E8588: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
L_801E858C:
    // 0x801E858C: or          $v0, $v1, $zero
    ctx->r2 = ctx->r3 | 0;
L_801E8590:
    // 0x801E8590: divu        $zero, $t9, $v0
    lo = S32(U32(ctx->r25) / U32(ctx->r2)); hi = S32(U32(ctx->r25) % U32(ctx->r2));
    // 0x801E8594: mflo        $t7
    ctx->r15 = lo;
    // 0x801E8598: andi        $t5, $t7, 0xFFF
    ctx->r13 = ctx->r15 & 0XFFF;
    // 0x801E859C: lui         $at, 0x700
    ctx->r1 = S32(0X700 << 16);
    // 0x801E85A0: andi        $t8, $a3, 0xFFF
    ctx->r24 = ctx->r7 & 0XFFF;
    // 0x801E85A4: sll         $t4, $t8, 12
    ctx->r12 = S32(ctx->r24 << 12);
    // 0x801E85A8: or          $t6, $t5, $at
    ctx->r14 = ctx->r13 | ctx->r1;
    // 0x801E85AC: or          $t9, $t6, $t4
    ctx->r25 = ctx->r14 | ctx->r12;
    // 0x801E85B0: sw          $t9, 0x4($t0)
    MEM_W(0X4, ctx->r8) = ctx->r25;
    // 0x801E85B4: or          $v1, $s0, $zero
    ctx->r3 = ctx->r16 | 0;
    // 0x801E85B8: lui         $t7, 0xE700
    ctx->r15 = S32(0XE700 << 16);
    // 0x801E85BC: sw          $t7, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r15;
    // 0x801E85C0: sw          $zero, 0x4($v1)
    MEM_W(0X4, ctx->r3) = 0;
    // 0x801E85C4: lw          $t5, 0x64($sp)
    ctx->r13 = MEM_W(ctx->r29, 0X64);
    // 0x801E85C8: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801E85CC: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x801E85D0: sll         $t8, $t5, 1
    ctx->r24 = S32(ctx->r13 << 1);
    // 0x801E85D4: addiu       $t6, $t8, 0x7
    ctx->r14 = ADD32(ctx->r24, 0X7);
    // 0x801E85D8: srl         $t4, $t6, 3
    ctx->r12 = S32(U32(ctx->r14) >> 3);
    // 0x801E85DC: andi        $t9, $t4, 0x1FF
    ctx->r25 = ctx->r12 & 0X1FF;
    // 0x801E85E0: sll         $t7, $t9, 9
    ctx->r15 = S32(ctx->r25 << 9);
    // 0x801E85E4: lui         $t8, 0x8
    ctx->r24 = S32(0X8 << 16);
    // 0x801E85E8: ori         $t8, $t8, 0x200
    ctx->r24 = ctx->r24 | 0X200;
    // 0x801E85EC: or          $t5, $t7, $t1
    ctx->r13 = ctx->r15 | ctx->r9;
    // 0x801E85F0: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801E85F4: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    // 0x801E85F8: sw          $t5, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r13;
    // 0x801E85FC: sw          $t8, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r24;
    // 0x801E8600: lui         $t6, 0xF200
    ctx->r14 = S32(0XF200 << 16);
    // 0x801E8604: sw          $t6, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r14;
    // 0x801E8608: lw          $t4, 0x64($sp)
    ctx->r12 = MEM_W(ctx->r29, 0X64);
    // 0x801E860C: lw          $t6, 0x5C($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X5C);
    // 0x801E8610: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801E8614: addiu       $t9, $t4, -0x1
    ctx->r25 = ADD32(ctx->r12, -0X1);
    // 0x801E8618: sll         $t7, $t9, 2
    ctx->r15 = S32(ctx->r25 << 2);
    // 0x801E861C: andi        $t5, $t7, 0xFFF
    ctx->r13 = ctx->r15 & 0XFFF;
    // 0x801E8620: addiu       $t4, $t6, -0x1
    ctx->r12 = ADD32(ctx->r14, -0X1);
    // 0x801E8624: sll         $t9, $t4, 2
    ctx->r25 = S32(ctx->r12 << 2);
    // 0x801E8628: andi        $t7, $t9, 0xFFF
    ctx->r15 = ctx->r25 & 0XFFF;
    // 0x801E862C: sll         $t8, $t5, 12
    ctx->r24 = S32(ctx->r13 << 12);
    // 0x801E8630: or          $t5, $t8, $t7
    ctx->r13 = ctx->r24 | ctx->r15;
    // 0x801E8634: sw          $t5, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r13;
    // 0x801E8638: bne         $v0, $zero, L_801E8644
    if (ctx->r2 != 0) {
        // 0x801E863C: nop
    
            goto L_801E8644;
    }
    // 0x801E863C: nop

    // 0x801E8640: break       7
    do_break(2149484096);
L_801E8644:
    // 0x801E8644: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x801E8648: bne         $t3, $at, L_801E876C
    if (ctx->r11 != ctx->r1) {
        // 0x801E864C: or          $a0, $s0, $zero
        ctx->r4 = ctx->r16 | 0;
            goto L_801E876C;
    }
    // 0x801E864C: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x801E8650: lw          $t6, 0x64($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X64);
    // 0x801E8654: lw          $t4, 0x7C($sp)
    ctx->r12 = MEM_W(ctx->r29, 0X7C);
    // 0x801E8658: or          $t0, $s0, $zero
    ctx->r8 = ctx->r16 | 0;
    // 0x801E865C: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801E8660: addu        $v0, $t6, $t4
    ctx->r2 = ADD32(ctx->r14, ctx->r12);
    // 0x801E8664: sll         $t9, $v0, 2
    ctx->r25 = S32(ctx->r2 << 2);
    // 0x801E8668: blez        $t9, L_801E8678
    if (SIGNED(ctx->r25) <= 0) {
        // 0x801E866C: lw          $t8, 0x5C($sp)
        ctx->r24 = MEM_W(ctx->r29, 0X5C);
            goto L_801E8678;
    }
    // 0x801E866C: lw          $t8, 0x5C($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X5C);
    // 0x801E8670: b           L_801E867C
    // 0x801E8674: or          $a2, $t9, $zero
    ctx->r6 = ctx->r25 | 0;
        goto L_801E867C;
    // 0x801E8674: or          $a2, $t9, $zero
    ctx->r6 = ctx->r25 | 0;
L_801E8678:
    // 0x801E8678: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
L_801E867C:
    // 0x801E867C: addu        $v1, $t8, $t2
    ctx->r3 = ADD32(ctx->r24, ctx->r10);
    // 0x801E8680: sll         $t7, $v1, 2
    ctx->r15 = S32(ctx->r3 << 2);
    // 0x801E8684: blez        $t7, L_801E8694
    if (SIGNED(ctx->r15) <= 0) {
        // 0x801E8688: lui         $at, 0xE400
        ctx->r1 = S32(0XE400 << 16);
            goto L_801E8694;
    }
    // 0x801E8688: lui         $at, 0xE400
    ctx->r1 = S32(0XE400 << 16);
    // 0x801E868C: b           L_801E8698
    // 0x801E8690: or          $v0, $t7, $zero
    ctx->r2 = ctx->r15 | 0;
        goto L_801E8698;
    // 0x801E8690: or          $v0, $t7, $zero
    ctx->r2 = ctx->r15 | 0;
L_801E8694:
    // 0x801E8694: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_801E8698:
    // 0x801E8698: andi        $t5, $v0, 0xFFF
    ctx->r13 = ctx->r2 & 0XFFF;
    // 0x801E869C: andi        $t4, $a2, 0xFFF
    ctx->r12 = ctx->r6 & 0XFFF;
    // 0x801E86A0: sll         $t9, $t4, 12
    ctx->r25 = S32(ctx->r12 << 12);
    // 0x801E86A4: or          $t6, $t5, $at
    ctx->r14 = ctx->r13 | ctx->r1;
    // 0x801E86A8: or          $t8, $t6, $t9
    ctx->r24 = ctx->r14 | ctx->r25;
    // 0x801E86AC: sw          $t8, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r24;
    // 0x801E86B0: lw          $a0, 0x7C($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X7C);
    // 0x801E86B4: sll         $a1, $t2, 2
    ctx->r5 = S32(ctx->r10 << 2);
    // 0x801E86B8: or          $a3, $s0, $zero
    ctx->r7 = ctx->r16 | 0;
    // 0x801E86BC: sll         $t7, $a0, 2
    ctx->r15 = S32(ctx->r4 << 2);
    // 0x801E86C0: blez        $t7, L_801E86D0
    if (SIGNED(ctx->r15) <= 0) {
        // 0x801E86C4: or          $a0, $t7, $zero
        ctx->r4 = ctx->r15 | 0;
            goto L_801E86D0;
    }
    // 0x801E86C4: or          $a0, $t7, $zero
    ctx->r4 = ctx->r15 | 0;
    // 0x801E86C8: b           L_801E86D4
    // 0x801E86CC: or          $a2, $t7, $zero
    ctx->r6 = ctx->r15 | 0;
        goto L_801E86D4;
    // 0x801E86CC: or          $a2, $t7, $zero
    ctx->r6 = ctx->r15 | 0;
L_801E86D0:
    // 0x801E86D0: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
L_801E86D4:
    // 0x801E86D4: blez        $a1, L_801E86E4
    if (SIGNED(ctx->r5) <= 0) {
        // 0x801E86D8: andi        $t4, $a2, 0xFFF
        ctx->r12 = ctx->r6 & 0XFFF;
            goto L_801E86E4;
    }
    // 0x801E86D8: andi        $t4, $a2, 0xFFF
    ctx->r12 = ctx->r6 & 0XFFF;
    // 0x801E86DC: b           L_801E86E8
    // 0x801E86E0: or          $v0, $a1, $zero
    ctx->r2 = ctx->r5 | 0;
        goto L_801E86E8;
    // 0x801E86E0: or          $v0, $a1, $zero
    ctx->r2 = ctx->r5 | 0;
L_801E86E4:
    // 0x801E86E4: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_801E86E8:
    // 0x801E86E8: andi        $t5, $v0, 0xFFF
    ctx->r13 = ctx->r2 & 0XFFF;
    // 0x801E86EC: sll         $t6, $t4, 12
    ctx->r14 = S32(ctx->r12 << 12);
    // 0x801E86F0: or          $t9, $t5, $t6
    ctx->r25 = ctx->r13 | ctx->r14;
    // 0x801E86F4: sll         $v1, $a0, 10
    ctx->r3 = S32(ctx->r4 << 10);
    // 0x801E86F8: sra         $t7, $v1, 7
    ctx->r15 = S32(SIGNED(ctx->r3) >> 7);
    // 0x801E86FC: sw          $t9, 0x4($t0)
    MEM_W(0X4, ctx->r8) = ctx->r25;
    // 0x801E8700: lui         $t8, 0xB300
    ctx->r24 = S32(0XB300 << 16);
    // 0x801E8704: sw          $t8, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r24;
    // 0x801E8708: bgez        $t7, L_801E8718
    if (SIGNED(ctx->r15) >= 0) {
        // 0x801E870C: addiu       $s0, $s0, 0x8
        ctx->r16 = ADD32(ctx->r16, 0X8);
            goto L_801E8718;
    }
    // 0x801E870C: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801E8710: b           L_801E871C
    // 0x801E8714: or          $a2, $t7, $zero
    ctx->r6 = ctx->r15 | 0;
        goto L_801E871C;
    // 0x801E8714: or          $a2, $t7, $zero
    ctx->r6 = ctx->r15 | 0;
L_801E8718:
    // 0x801E8718: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
L_801E871C:
    // 0x801E871C: sll         $v1, $a1, 10
    ctx->r3 = S32(ctx->r5 << 10);
    // 0x801E8720: sra         $t4, $v1, 7
    ctx->r12 = S32(SIGNED(ctx->r3) >> 7);
    // 0x801E8724: bgez        $t4, L_801E8734
    if (SIGNED(ctx->r12) >= 0) {
        // 0x801E8728: negu        $t8, $a2
        ctx->r24 = SUB32(0, ctx->r6);
            goto L_801E8734;
    }
    // 0x801E8728: negu        $t8, $a2
    ctx->r24 = SUB32(0, ctx->r6);
    // 0x801E872C: b           L_801E8738
    // 0x801E8730: or          $v0, $t4, $zero
    ctx->r2 = ctx->r12 | 0;
        goto L_801E8738;
    // 0x801E8730: or          $v0, $t4, $zero
    ctx->r2 = ctx->r12 | 0;
L_801E8734:
    // 0x801E8734: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_801E8738:
    // 0x801E8738: negu        $t5, $v0
    ctx->r13 = SUB32(0, ctx->r2);
    // 0x801E873C: andi        $t6, $t5, 0xFFFF
    ctx->r14 = ctx->r13 & 0XFFFF;
    // 0x801E8740: sll         $t7, $t8, 16
    ctx->r15 = S32(ctx->r24 << 16);
    // 0x801E8744: or          $t4, $t6, $t7
    ctx->r12 = ctx->r14 | ctx->r15;
    // 0x801E8748: or          $v1, $s0, $zero
    ctx->r3 = ctx->r16 | 0;
    // 0x801E874C: lui         $t9, 0x400
    ctx->r25 = S32(0X400 << 16);
    // 0x801E8750: ori         $t9, $t9, 0x400
    ctx->r25 = ctx->r25 | 0X400;
    // 0x801E8754: sw          $t4, 0x4($a3)
    MEM_W(0X4, ctx->r7) = ctx->r12;
    // 0x801E8758: lui         $t5, 0xB200
    ctx->r13 = S32(0XB200 << 16);
    // 0x801E875C: sw          $t5, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r13;
    // 0x801E8760: sw          $t9, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r25;
    if (wr64FontHalf > 0) wr64_menu_promote_waku_rect(rdram, (uint32_t)ctx->r8, wr64FontX, MEM_W(0x64, ctx->r29));
    // 0x801E8764: b           L_801E87E8
    // 0x801E8768: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
        goto L_801E87E8;
    // 0x801E8768: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
L_801E876C:
    // 0x801E876C: lbu         $t8, 0x8B($sp)
    ctx->r24 = MEM_BU(ctx->r29, 0X8B);
    // 0x801E8770: lbu         $t6, 0x8F($sp)
    ctx->r14 = MEM_BU(ctx->r29, 0X8F);
    // 0x801E8774: lbu         $t7, 0x93($sp)
    ctx->r15 = MEM_BU(ctx->r29, 0X93);
    // 0x801E8778: lbu         $t4, 0x97($sp)
    ctx->r12 = MEM_BU(ctx->r29, 0X97);
    // 0x801E877C: lbu         $t5, 0x9B($sp)
    ctx->r13 = MEM_BU(ctx->r29, 0X9B);
    // 0x801E8780: lbu         $t9, 0x9F($sp)
    ctx->r25 = MEM_BU(ctx->r29, 0X9F);
    // 0x801E8784: sw          $t8, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r24;
    // 0x801E8788: sw          $t6, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r14;
    // 0x801E878C: sw          $t7, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r15;
    // 0x801E8790: sw          $t4, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r12;
    // 0x801E8794: sw          $t5, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r13;
    // 0x801E8798: sw          $t9, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r25;
    // 0x801E879C: lbu         $t9, 0xB7($sp)
    ctx->r25 = MEM_BU(ctx->r29, 0XB7);
    // 0x801E87A0: lbu         $t5, 0xB3($sp)
    ctx->r13 = MEM_BU(ctx->r29, 0XB3);
    // 0x801E87A4: lbu         $t4, 0xAF($sp)
    ctx->r12 = MEM_BU(ctx->r29, 0XAF);
    // 0x801E87A8: lbu         $t7, 0xAB($sp)
    ctx->r15 = MEM_BU(ctx->r29, 0XAB);
    // 0x801E87AC: lbu         $t6, 0xA7($sp)
    ctx->r14 = MEM_BU(ctx->r29, 0XA7);
    // 0x801E87B0: lbu         $t8, 0xA3($sp)
    ctx->r24 = MEM_BU(ctx->r29, 0XA3);
    // 0x801E87B4: lw          $a1, 0x64($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X64);
    // 0x801E87B8: lw          $a2, 0x5C($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X5C);
    // 0x801E87BC: lw          $a3, 0x7C($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X7C);
    // 0x801E87C0: sw          $t2, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r10;
    // 0x801E87C4: swc1        $f0, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->f0.u32l;
    // 0x801E87C8: sw          $t9, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r25;
    // 0x801E87CC: sw          $t5, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r13;
    // 0x801E87D0: sw          $t4, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r12;
    // 0x801E87D4: sw          $t7, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r15;
    // 0x801E87D8: sw          $t6, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r14;
    // 0x801E87DC: jal         0x801E8800
    // 0x801E87E0: sw          $t8, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r24;
    func_801E8800(rdram, ctx);
        goto after_0;
    // 0x801E87E0: sw          $t8, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r24;
    after_0:
    // 0x801E87E4: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
L_801E87E8:
    // 0x801E87E8: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
L_801E87EC:
    // 0x801E87EC: lw          $ra, 0x54($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X54);
    // 0x801E87F0: lw          $s0, 0x50($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X50);
    // 0x801E87F4: addiu       $sp, $sp, 0x70
    ctx->r29 = ADD32(ctx->r29, 0X70);
    // 0x801E87F8: jr          $ra
    // 0x801E87FC: nop

    return;
    // 0x801E87FC: nop

;}
RECOMP_FUNC void func_801E8800(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801E8800: addiu       $sp, $sp, -0x30
    ctx->r29 = ADD32(ctx->r29, -0X30);
    // 0x801E8804: sw          $fp, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r30;
    // 0x801E8808: sw          $ra, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r31;
    // 0x801E880C: sw          $s7, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r23;
    // 0x801E8810: sw          $s6, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r22;
    // 0x801E8814: sw          $s5, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r21;
    // 0x801E8818: sw          $s4, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r20;
    // 0x801E881C: sw          $s3, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r19;
    // 0x801E8820: sw          $s2, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r18;
    // 0x801E8824: sw          $s1, 0xC($sp)
    MEM_W(0XC, ctx->r29) = ctx->r17;
    // 0x801E8828: sw          $s0, 0x8($sp)
    MEM_W(0X8, ctx->r29) = ctx->r16;
    // 0x801E882C: sw          $a0, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r4;
    // 0x801E8830: lui         $fp, 0x801D
    ctx->r30 = S32(0X801D << 16);
    // 0x801E8834: lui         $t1, 0x8023
    ctx->r9 = S32(0X8023 << 16);
    // 0x801E8838: addiu       $t1, $t1, -0x75C0
    ctx->r9 = ADD32(ctx->r9, -0X75C0);
    // 0x801E883C: addiu       $fp, $fp, -0x1A08
    ctx->r30 = ADD32(ctx->r30, -0X1A08);
    // 0x801E8840: lw          $a0, 0x40($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X40);
    // 0x801E8844: lbu         $s0, 0x57($sp)
    ctx->r16 = MEM_BU(ctx->r29, 0X57);
    // 0x801E8848: lbu         $s1, 0x5B($sp)
    ctx->r17 = MEM_BU(ctx->r29, 0X5B);
    // 0x801E884C: lbu         $s2, 0x5F($sp)
    ctx->r18 = MEM_BU(ctx->r29, 0X5F);
    // 0x801E8850: lbu         $s3, 0x63($sp)
    ctx->r19 = MEM_BU(ctx->r29, 0X63);
    // 0x801E8854: lbu         $s4, 0x67($sp)
    ctx->r20 = MEM_BU(ctx->r29, 0X67);
    // 0x801E8858: lbu         $s5, 0x6B($sp)
    ctx->r21 = MEM_BU(ctx->r29, 0X6B);
    // 0x801E885C: lbu         $s6, 0x6F($sp)
    ctx->r22 = MEM_BU(ctx->r29, 0X6F);
    // 0x801E8860: lbu         $s7, 0x73($sp)
    ctx->r23 = MEM_BU(ctx->r29, 0X73);
    // 0x801E8864: addiu       $ra, $zero, 0x10
    ctx->r31 = ADD32(0, 0X10);
    // 0x801E8868: lwc1        $f0, 0x74($sp)
    ctx->f0.u32l = MEM_W(ctx->r29, 0X74);
    // 0x801E886C: lbu         $t5, 0x53($sp)
    ctx->r13 = MEM_BU(ctx->r29, 0X53);
    // 0x801E8870: lbu         $t4, 0x4F($sp)
    ctx->r12 = MEM_BU(ctx->r29, 0X4F);
    // 0x801E8874: lbu         $t3, 0x4B($sp)
    ctx->r11 = MEM_BU(ctx->r29, 0X4B);
    // 0x801E8878: lbu         $t2, 0x47($sp)
    ctx->r10 = MEM_BU(ctx->r29, 0X47);
    // 0x801E887C: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
    // 0x801E8880: addiu       $t0, $zero, -0x20
    ctx->r8 = ADD32(0, -0X20);
L_801E8884:
    // 0x801E8884: lw          $t7, 0x0($t1)
    ctx->r15 = MEM_W(ctx->r9, 0X0);
    // 0x801E8888: lw          $t6, 0x0($fp)
    ctx->r14 = MEM_W(ctx->r30, 0X0);
    // 0x801E888C: addiu       $at, $zero, 0x30
    ctx->r1 = ADD32(0, 0X30);
    // 0x801E8890: sll         $t8, $t7, 4
    ctx->r24 = S32(ctx->r15 << 4);
    // 0x801E8894: addu        $t9, $t6, $t8
    ctx->r25 = ADD32(ctx->r14, ctx->r24);
    // 0x801E8898: addu        $v0, $t9, $v1
    ctx->r2 = ADD32(ctx->r25, ctx->r3);
    // 0x801E889C: beq         $v1, $ra, L_801E88AC
    if (ctx->r3 == ctx->r31) {
        // 0x801E88A0: addiu       $v0, $v0, 0x40
        ctx->r2 = ADD32(ctx->r2, 0X40);
            goto L_801E88AC;
    }
    // 0x801E88A0: addiu       $v0, $v0, 0x40
    ctx->r2 = ADD32(ctx->r2, 0X40);
    // 0x801E88A4: bnel        $v1, $at, L_801E88FC
    if (ctx->r3 != ctx->r1) {
        // 0x801E88A8: sh          $a3, 0x0($v0)
        MEM_H(0X0, ctx->r2) = ctx->r7;
            goto L_801E88FC;
    }
    goto skip_0;
    // 0x801E88A8: sh          $a3, 0x0($v0)
    MEM_H(0X0, ctx->r2) = ctx->r7;
    skip_0:
L_801E88AC:
    // 0x801E88AC: mtc1        $a1, $f4
    ctx->f4.u32l = ctx->r5;
    // 0x801E88B0: lui         $at, 0x4F80
    ctx->r1 = S32(0X4F80 << 16);
    // 0x801E88B4: bgez        $a1, L_801E88C8
    if (SIGNED(ctx->r5) >= 0) {
        // 0x801E88B8: cvt.s.w     $f6, $f4
        CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
            goto L_801E88C8;
    }
    // 0x801E88B8: cvt.s.w     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
    // 0x801E88BC: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x801E88C0: nop

    // 0x801E88C4: add.s       $f6, $f6, $f8
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f6.fl = ctx->f6.fl + ctx->f8.fl;
L_801E88C8:
    // 0x801E88C8: mul.s       $f10, $f6, $f0
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f10.fl = MUL_S(ctx->f6.fl, ctx->f0.fl);
    // 0x801E88CC: sll         $t7, $a1, 1
    ctx->r15 = S32(ctx->r5 << 1);
    // 0x801E88D0: trunc.w.s   $f16, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    ctx->f16.u32l = TRUNC_W_S(ctx->f10.fl);
    // 0x801E88D4: mfc1        $t6, $f16
    ctx->r14 = (int32_t)ctx->f16.u32l;
    // 0x801E88D8: nop

    // 0x801E88DC: addu        $t8, $t6, $a3
    ctx->r24 = ADD32(ctx->r14, ctx->r7);
    // 0x801E88E0: addiu       $t9, $t8, -0x1
    ctx->r25 = ADD32(ctx->r24, -0X1);
    // 0x801E88E4: addiu       $t6, $t7, 0x1
    ctx->r14 = ADD32(ctx->r15, 0X1);
    // 0x801E88E8: sll         $t8, $t6, 5
    ctx->r24 = S32(ctx->r14 << 5);
    // 0x801E88EC: sh          $t9, 0x0($v0)
    MEM_H(0X0, ctx->r2) = ctx->r25;
    // 0x801E88F0: b           L_801E8900
    // 0x801E88F4: sh          $t8, 0x8($v0)
    MEM_H(0X8, ctx->r2) = ctx->r24;
        goto L_801E8900;
    // 0x801E88F4: sh          $t8, 0x8($v0)
    MEM_H(0X8, ctx->r2) = ctx->r24;
    // 0x801E88F8: sh          $a3, 0x0($v0)
    MEM_H(0X0, ctx->r2) = ctx->r7;
L_801E88FC:
    // 0x801E88FC: sh          $t0, 0x8($v0)
    MEM_H(0X8, ctx->r2) = ctx->r8;
L_801E8900:
    // 0x801E8900: addiu       $at, $zero, 0x20
    ctx->r1 = ADD32(0, 0X20);
    // 0x801E8904: beq         $v1, $at, L_801E8914
    if (ctx->r3 == ctx->r1) {
        // 0x801E8908: addiu       $at, $zero, 0x30
        ctx->r1 = ADD32(0, 0X30);
            goto L_801E8914;
    }
    // 0x801E8908: addiu       $at, $zero, 0x30
    ctx->r1 = ADD32(0, 0X30);
    // 0x801E890C: bnel        $v1, $at, L_801E895C
    if (ctx->r3 != ctx->r1) {
        // 0x801E8910: sh          $a0, 0x2($v0)
        MEM_H(0X2, ctx->r2) = ctx->r4;
            goto L_801E895C;
    }
    goto skip_1;
    // 0x801E8910: sh          $a0, 0x2($v0)
    MEM_H(0X2, ctx->r2) = ctx->r4;
    skip_1:
L_801E8914:
    // 0x801E8914: mtc1        $a2, $f18
    ctx->f18.u32l = ctx->r6;
    // 0x801E8918: lui         $at, 0x4F80
    ctx->r1 = S32(0X4F80 << 16);
    // 0x801E891C: bgez        $a2, L_801E8930
    if (SIGNED(ctx->r6) >= 0) {
        // 0x801E8920: cvt.s.w     $f4, $f18
        CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    ctx->f4.fl = CVT_S_W(ctx->f18.u32l);
            goto L_801E8930;
    }
    // 0x801E8920: cvt.s.w     $f4, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    ctx->f4.fl = CVT_S_W(ctx->f18.u32l);
    // 0x801E8924: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x801E8928: nop

    // 0x801E892C: add.s       $f4, $f4, $f8
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f4.fl = ctx->f4.fl + ctx->f8.fl;
L_801E8930:
    // 0x801E8930: mul.s       $f6, $f4, $f0
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f6.fl = MUL_S(ctx->f4.fl, ctx->f0.fl);
    // 0x801E8934: trunc.w.s   $f10, $f6
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    ctx->f10.u32l = TRUNC_W_S(ctx->f6.fl);
    // 0x801E8938: mfc1        $t7, $f10
    ctx->r15 = (int32_t)ctx->f10.u32l;
    // 0x801E893C: nop

    // 0x801E8940: addu        $t6, $t7, $a0
    ctx->r14 = ADD32(ctx->r15, ctx->r4);
    // 0x801E8944: addiu       $t8, $t6, -0x1
    ctx->r24 = ADD32(ctx->r14, -0X1);
    // 0x801E8948: sll         $t7, $a2, 6
    ctx->r15 = S32(ctx->r6 << 6);
    // 0x801E894C: sh          $t8, 0x2($v0)
    MEM_H(0X2, ctx->r2) = ctx->r24;
    // 0x801E8950: b           L_801E8960
    // 0x801E8954: sh          $t7, 0xA($v0)
    MEM_H(0XA, ctx->r2) = ctx->r15;
        goto L_801E8960;
    // 0x801E8954: sh          $t7, 0xA($v0)
    MEM_H(0XA, ctx->r2) = ctx->r15;
    // 0x801E8958: sh          $a0, 0x2($v0)
    MEM_H(0X2, ctx->r2) = ctx->r4;
L_801E895C:
    // 0x801E895C: sh          $t0, 0xA($v0)
    MEM_H(0XA, ctx->r2) = ctx->r8;
L_801E8960:
    // 0x801E8960: sh          $zero, 0x4($v0)
    MEM_H(0X4, ctx->r2) = 0;
    // 0x801E8964: bne         $v1, $zero, L_801E897C
    if (ctx->r3 != 0) {
        // 0x801E8968: sh          $zero, 0x6($v0)
        MEM_H(0X6, ctx->r2) = 0;
            goto L_801E897C;
    }
    // 0x801E8968: sh          $zero, 0x6($v0)
    MEM_H(0X6, ctx->r2) = 0;
    // 0x801E896C: sb          $t2, 0xC($v0)
    MEM_B(0XC, ctx->r2) = ctx->r10;
    // 0x801E8970: sb          $t3, 0xD($v0)
    MEM_B(0XD, ctx->r2) = ctx->r11;
    // 0x801E8974: b           L_801E89C0
    // 0x801E8978: sb          $t4, 0xE($v0)
    MEM_B(0XE, ctx->r2) = ctx->r12;
        goto L_801E89C0;
    // 0x801E8978: sb          $t4, 0xE($v0)
    MEM_B(0XE, ctx->r2) = ctx->r12;
L_801E897C:
    // 0x801E897C: addiu       $at, $zero, 0x10
    ctx->r1 = ADD32(0, 0X10);
    // 0x801E8980: bnel        $v1, $at, L_801E899C
    if (ctx->r3 != ctx->r1) {
        // 0x801E8984: addiu       $at, $zero, 0x20
        ctx->r1 = ADD32(0, 0X20);
            goto L_801E899C;
    }
    goto skip_2;
    // 0x801E8984: addiu       $at, $zero, 0x20
    ctx->r1 = ADD32(0, 0X20);
    skip_2:
    // 0x801E8988: sb          $t5, 0xC($v0)
    MEM_B(0XC, ctx->r2) = ctx->r13;
    // 0x801E898C: sb          $s0, 0xD($v0)
    MEM_B(0XD, ctx->r2) = ctx->r16;
    // 0x801E8990: b           L_801E89C0
    // 0x801E8994: sb          $s1, 0xE($v0)
    MEM_B(0XE, ctx->r2) = ctx->r17;
        goto L_801E89C0;
    // 0x801E8994: sb          $s1, 0xE($v0)
    MEM_B(0XE, ctx->r2) = ctx->r17;
    // 0x801E8998: addiu       $at, $zero, 0x20
    ctx->r1 = ADD32(0, 0X20);
L_801E899C:
    // 0x801E899C: bnel        $v1, $at, L_801E89B8
    if (ctx->r3 != ctx->r1) {
        // 0x801E89A0: sb          $s5, 0xC($v0)
        MEM_B(0XC, ctx->r2) = ctx->r21;
            goto L_801E89B8;
    }
    goto skip_3;
    // 0x801E89A0: sb          $s5, 0xC($v0)
    MEM_B(0XC, ctx->r2) = ctx->r21;
    skip_3:
    // 0x801E89A4: sb          $s2, 0xC($v0)
    MEM_B(0XC, ctx->r2) = ctx->r18;
    // 0x801E89A8: sb          $s3, 0xD($v0)
    MEM_B(0XD, ctx->r2) = ctx->r19;
    // 0x801E89AC: b           L_801E89C0
    // 0x801E89B0: sb          $s4, 0xE($v0)
    MEM_B(0XE, ctx->r2) = ctx->r20;
        goto L_801E89C0;
    // 0x801E89B0: sb          $s4, 0xE($v0)
    MEM_B(0XE, ctx->r2) = ctx->r20;
    // 0x801E89B4: sb          $s5, 0xC($v0)
    MEM_B(0XC, ctx->r2) = ctx->r21;
L_801E89B8:
    // 0x801E89B8: sb          $s6, 0xD($v0)
    MEM_B(0XD, ctx->r2) = ctx->r22;
    // 0x801E89BC: sb          $s7, 0xE($v0)
    MEM_B(0XE, ctx->r2) = ctx->r23;
L_801E89C0:
    // 0x801E89C0: addiu       $v1, $v1, 0x10
    ctx->r3 = ADD32(ctx->r3, 0X10);
    // 0x801E89C4: addiu       $at, $zero, 0x40
    ctx->r1 = ADD32(0, 0X40);
    // 0x801E89C8: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x801E89CC: bne         $v1, $at, L_801E8884
    if (ctx->r3 != ctx->r1) {
        // 0x801E89D0: sb          $t6, 0xF($v0)
        MEM_B(0XF, ctx->r2) = ctx->r14;
            goto L_801E8884;
    }
    // 0x801E89D0: sb          $t6, 0xF($v0)
    MEM_B(0XF, ctx->r2) = ctx->r14;
    // 0x801E89D4: lw          $a2, 0x30($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X30);
    // 0x801E89D8: lui         $t8, 0x400
    ctx->r24 = S32(0X400 << 16);
    // 0x801E89DC: ori         $t8, $t8, 0x83F
    ctx->r24 = ctx->r24 | 0X83F;
    // 0x801E89E0: or          $v0, $a2, $zero
    ctx->r2 = ctx->r6 | 0;
    // 0x801E89E4: sw          $t8, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r24;
    // 0x801E89E8: lw          $t9, 0x0($t1)
    ctx->r25 = MEM_W(ctx->r9, 0X0);
    // 0x801E89EC: lui         $t8, 0x700
    ctx->r24 = S32(0X700 << 16);
    // 0x801E89F0: addiu       $t8, $t8, 0x0
    ctx->r24 = ADD32(ctx->r24, 0X0);
    // 0x801E89F4: sll         $t7, $t9, 4
    ctx->r15 = S32(ctx->r25 << 4);
    // 0x801E89F8: addiu       $t6, $t7, 0x40
    ctx->r14 = ADD32(ctx->r15, 0X40);
    // 0x801E89FC: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x801E8A00: addu        $t9, $t6, $t8
    ctx->r25 = ADD32(ctx->r14, ctx->r24);
    // 0x801E8A04: or          $v1, $a2, $zero
    ctx->r3 = ctx->r6 | 0;
    // 0x801E8A08: sw          $t9, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r25;
    // 0x801E8A0C: lui         $a1, 0xBF00
    ctx->r5 = S32(0XBF00 << 16);
    // 0x801E8A10: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x801E8A14: addiu       $t7, $zero, 0xF05
    ctx->r15 = ADD32(0, 0XF05);
    // 0x801E8A18: sw          $t7, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r15;
    // 0x801E8A1C: sw          $a1, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r5;
    // 0x801E8A20: or          $a0, $a2, $zero
    ctx->r4 = ctx->r6 | 0;
    // 0x801E8A24: addiu       $t6, $zero, 0xA0F
    ctx->r14 = ADD32(0, 0XA0F);
    // 0x801E8A28: sw          $t6, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r14;
    // 0x801E8A2C: sw          $a1, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r5;
    // 0x801E8A30: lw          $t8, 0x0($t1)
    ctx->r24 = MEM_W(ctx->r9, 0X0);
    // 0x801E8A34: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x801E8A38: or          $v0, $a2, $zero
    ctx->r2 = ctx->r6 | 0;
    // 0x801E8A3C: addiu       $t9, $t8, 0x4
    ctx->r25 = ADD32(ctx->r24, 0X4);
    // 0x801E8A40: slti        $at, $t9, 0x78
    ctx->r1 = SIGNED(ctx->r25) < 0X78 ? 1 : 0;
    // 0x801E8A44: bne         $at, $zero, L_801E8A54
    if (ctx->r1 != 0) {
        // 0x801E8A48: sw          $t9, 0x0($t1)
        MEM_W(0X0, ctx->r9) = ctx->r25;
            goto L_801E8A54;
    }
    // 0x801E8A48: sw          $t9, 0x0($t1)
    MEM_W(0X0, ctx->r9) = ctx->r25;
    // 0x801E8A4C: addiu       $t6, $zero, 0x74
    ctx->r14 = ADD32(0, 0X74);
    // 0x801E8A50: sw          $t6, 0x0($t1)
    MEM_W(0X0, ctx->r9) = ctx->r14;
L_801E8A54:
    // 0x801E8A54: lw          $ra, 0x2C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X2C);
    // 0x801E8A58: lw          $s0, 0x8($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X8);
    // 0x801E8A5C: lw          $s1, 0xC($sp)
    ctx->r17 = MEM_W(ctx->r29, 0XC);
    // 0x801E8A60: lw          $s2, 0x10($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X10);
    // 0x801E8A64: lw          $s3, 0x14($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X14);
    // 0x801E8A68: lw          $s4, 0x18($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X18);
    // 0x801E8A6C: lw          $s5, 0x1C($sp)
    ctx->r21 = MEM_W(ctx->r29, 0X1C);
    // 0x801E8A70: lw          $s6, 0x20($sp)
    ctx->r22 = MEM_W(ctx->r29, 0X20);
    // 0x801E8A74: lw          $s7, 0x24($sp)
    ctx->r23 = MEM_W(ctx->r29, 0X24);
    // 0x801E8A78: lw          $fp, 0x28($sp)
    ctx->r30 = MEM_W(ctx->r29, 0X28);
    // 0x801E8A7C: jr          $ra
    // 0x801E8A80: addiu       $sp, $sp, 0x30
    ctx->r29 = ADD32(ctx->r29, 0X30);
    return;
    // 0x801E8A80: addiu       $sp, $sp, 0x30
    ctx->r29 = ADD32(ctx->r29, 0X30);
;}
RECOMP_FUNC void func_801E8A84(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801E8A84: addiu       $sp, $sp, -0x40
    ctx->r29 = ADD32(ctx->r29, -0X40);
    // 0x801E8A88: lbu         $t6, 0x63($sp)
    ctx->r14 = MEM_BU(ctx->r29, 0X63);
    // 0x801E8A8C: lbu         $t7, 0x67($sp)
    ctx->r15 = MEM_BU(ctx->r29, 0X67);
    // 0x801E8A90: lbu         $t8, 0x6B($sp)
    ctx->r24 = MEM_BU(ctx->r29, 0X6B);
    // 0x801E8A94: lbu         $t9, 0x6F($sp)
    ctx->r25 = MEM_BU(ctx->r29, 0X6F);
    // 0x801E8A98: lbu         $t0, 0x73($sp)
    ctx->r8 = MEM_BU(ctx->r29, 0X73);
    // 0x801E8A9C: lbu         $t1, 0x77($sp)
    ctx->r9 = MEM_BU(ctx->r29, 0X77);
    // 0x801E8AA0: lbu         $t2, 0x7B($sp)
    ctx->r10 = MEM_BU(ctx->r29, 0X7B);
    // 0x801E8AA4: lbu         $t3, 0x7F($sp)
    ctx->r11 = MEM_BU(ctx->r29, 0X7F);
    // 0x801E8AA8: lbu         $t4, 0x83($sp)
    ctx->r12 = MEM_BU(ctx->r29, 0X83);
    // 0x801E8AAC: lbu         $t5, 0x87($sp)
    ctx->r13 = MEM_BU(ctx->r29, 0X87);
    // 0x801E8AB0: sw          $ra, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r31;
    // 0x801E8AB4: sw          $a1, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r5;
    // 0x801E8AB8: sw          $a2, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r6;
    // 0x801E8ABC: sw          $a3, 0x4C($sp)
    MEM_W(0X4C, ctx->r29) = ctx->r7;
    // 0x801E8AC0: lbu         $a3, 0x5F($sp)
    ctx->r7 = MEM_BU(ctx->r29, 0X5F);
    // 0x801E8AC4: lbu         $a2, 0x5B($sp)
    ctx->r6 = MEM_BU(ctx->r29, 0X5B);
    // 0x801E8AC8: lw          $a1, 0x54($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X54);
    // 0x801E8ACC: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x801E8AD0: sw          $t7, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r15;
    // 0x801E8AD4: sw          $t8, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r24;
    // 0x801E8AD8: sw          $t9, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r25;
    // 0x801E8ADC: sw          $t0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r8;
    // 0x801E8AE0: sw          $t1, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r9;
    // 0x801E8AE4: sw          $t2, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r10;
    // 0x801E8AE8: sw          $t3, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r11;
    // 0x801E8AEC: sw          $t4, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r12;
    // 0x801E8AF0: jal         0x801E946C
    // 0x801E8AF4: sw          $t5, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r13;
    func_801E946C(rdram, ctx);
        goto after_0;
    // 0x801E8AF4: sw          $t5, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r13;
    after_0:
    // 0x801E8AF8: lw          $t6, 0x50($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X50);
    // 0x801E8AFC: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x801E8B00: lw          $a1, 0x44($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X44);
    // 0x801E8B04: lw          $a2, 0x48($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X48);
    // 0x801E8B08: lw          $a3, 0x4C($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X4C);
    // 0x801E8B0C: jal         0x801E8B24
    // 0x801E8B10: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    func_801E8B24(rdram, ctx);
        goto after_1;
    // 0x801E8B10: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    after_1:
    // 0x801E8B14: lw          $ra, 0x3C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X3C);
    // 0x801E8B18: addiu       $sp, $sp, 0x40
    ctx->r29 = ADD32(ctx->r29, 0X40);
    // 0x801E8B1C: jr          $ra
    // 0x801E8B20: nop

    return;
    // 0x801E8B20: nop

;}
RECOMP_FUNC void func_801E8B24(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801E8B24: addiu       $sp, $sp, -0xB8
    ctx->r29 = ADD32(ctx->r29, -0XB8);
    // 0x801E8B28: sw          $s7, 0x78($sp)
    MEM_W(0X78, ctx->r29) = ctx->r23;
    // 0x801E8B2C: sltiu       $at, $a1, 0x6
    ctx->r1 = ctx->r5 < 0X6 ? 1 : 0;
    // 0x801E8B30: or          $s7, $a1, $zero
    ctx->r23 = ctx->r5 | 0;
    // 0x801E8B34: sw          $ra, 0x7C($sp)
    MEM_W(0X7C, ctx->r29) = ctx->r31;
    // 0x801E8B38: sw          $s6, 0x74($sp)
    MEM_W(0X74, ctx->r29) = ctx->r22;
    // 0x801E8B3C: sw          $s5, 0x70($sp)
    MEM_W(0X70, ctx->r29) = ctx->r21;
    // 0x801E8B40: sw          $s4, 0x6C($sp)
    MEM_W(0X6C, ctx->r29) = ctx->r20;
    // 0x801E8B44: sw          $s3, 0x68($sp)
    MEM_W(0X68, ctx->r29) = ctx->r19;
    // 0x801E8B48: sw          $s2, 0x64($sp)
    MEM_W(0X64, ctx->r29) = ctx->r18;
    // 0x801E8B4C: sw          $s1, 0x60($sp)
    MEM_W(0X60, ctx->r29) = ctx->r17;
    // 0x801E8B50: sw          $s0, 0x5C($sp)
    MEM_W(0X5C, ctx->r29) = ctx->r16;
    // 0x801E8B54: sdc1        $f20, 0x50($sp)
    CHECK_FR(ctx, 20);
    SD(ctx->f20.u64, 0X50, ctx->r29);
    // 0x801E8B58: beq         $at, $zero, L_801E8C8C
    if (ctx->r1 == 0) {
        // 0x801E8B5C: sw          $a2, 0xC0($sp)
        MEM_W(0XC0, ctx->r29) = ctx->r6;
            goto L_801E8C8C;
    }
    // 0x801E8B5C: sw          $a2, 0xC0($sp)
    MEM_W(0XC0, ctx->r29) = ctx->r6;
    // 0x801E8B60: sll         $t6, $a1, 2
    ctx->r14 = S32(ctx->r5 << 2);
    // 0x801E8B64: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E8B68: addu        $at, $at, $t6
    gpr jr_addend_801E8B70 = ctx->r14;
    ctx->r1 = ADD32(ctx->r1, ctx->r14);
    // 0x801E8B6C: lw          $t6, 0x6E6C($at)
    ctx->r14 = ADD32(ctx->r1, 0X6E6C);
    // 0x801E8B70: jr          $t6
    // 0x801E8B74: nop

    switch (jr_addend_801E8B70 >> 2) {
        case 0: goto L_801E8B78; break;
        case 1: goto L_801E8BAC; break;
        case 2: goto L_801E8BE0; break;
        case 3: goto L_801E8C14; break;
        case 4: goto L_801E8C48; break;
        case 5: goto L_801E8C6C; break;
        default: switch_error(__func__, 0x801E8B70, 0x80226E6C);
    }
    // 0x801E8B74: nop

L_801E8B78:
    // 0x801E8B78: lui         $v0, 0x8022
    ctx->r2 = S32(0X8022 << 16);
    // 0x801E8B7C: addiu       $v0, $v0, 0x6D70
    ctx->r2 = ADD32(ctx->r2, 0X6D70);
    // 0x801E8B80: lbu         $t0, 0x25($v0)
    ctx->r8 = MEM_BU(ctx->r2, 0X25);
    // 0x801E8B84: lbu         $t1, 0x26($v0)
    ctx->r9 = MEM_BU(ctx->r2, 0X26);
    // 0x801E8B88: addiu       $t7, $zero, 0x18
    ctx->r15 = ADD32(0, 0X18);
    // 0x801E8B8C: addiu       $t8, $zero, 0x25
    ctx->r24 = ADD32(0, 0X25);
    // 0x801E8B90: addiu       $t9, $zero, 0x26
    ctx->r25 = ADD32(0, 0X26);
    // 0x801E8B94: sw          $t7, 0xB0($sp)
    MEM_W(0XB0, ctx->r29) = ctx->r15;
    // 0x801E8B98: sw          $t8, 0xAC($sp)
    MEM_W(0XAC, ctx->r29) = ctx->r24;
    // 0x801E8B9C: sw          $t9, 0xA8($sp)
    MEM_W(0XA8, ctx->r29) = ctx->r25;
    // 0x801E8BA0: sw          $t0, 0xA4($sp)
    MEM_W(0XA4, ctx->r29) = ctx->r8;
    // 0x801E8BA4: b           L_801E8C8C
    // 0x801E8BA8: sw          $t1, 0xA0($sp)
    MEM_W(0XA0, ctx->r29) = ctx->r9;
        goto L_801E8C8C;
    // 0x801E8BA8: sw          $t1, 0xA0($sp)
    MEM_W(0XA0, ctx->r29) = ctx->r9;
L_801E8BAC:
    // 0x801E8BAC: lui         $v0, 0x8022
    ctx->r2 = S32(0X8022 << 16);
    // 0x801E8BB0: addiu       $v0, $v0, 0x6D98
    ctx->r2 = ADD32(ctx->r2, 0X6D98);
    // 0x801E8BB4: lbu         $t5, 0x25($v0)
    ctx->r13 = MEM_BU(ctx->r2, 0X25);
    // 0x801E8BB8: lbu         $t6, 0x26($v0)
    ctx->r14 = MEM_BU(ctx->r2, 0X26);
    // 0x801E8BBC: addiu       $t2, $zero, 0x8
    ctx->r10 = ADD32(0, 0X8);
    // 0x801E8BC0: addiu       $t3, $zero, 0x25
    ctx->r11 = ADD32(0, 0X25);
    // 0x801E8BC4: addiu       $t4, $zero, 0x26
    ctx->r12 = ADD32(0, 0X26);
    // 0x801E8BC8: sw          $t2, 0xB0($sp)
    MEM_W(0XB0, ctx->r29) = ctx->r10;
    // 0x801E8BCC: sw          $t3, 0xAC($sp)
    MEM_W(0XAC, ctx->r29) = ctx->r11;
    // 0x801E8BD0: sw          $t4, 0xA8($sp)
    MEM_W(0XA8, ctx->r29) = ctx->r12;
    // 0x801E8BD4: sw          $t5, 0xA4($sp)
    MEM_W(0XA4, ctx->r29) = ctx->r13;
    // 0x801E8BD8: b           L_801E8C8C
    // 0x801E8BDC: sw          $t6, 0xA0($sp)
    MEM_W(0XA0, ctx->r29) = ctx->r14;
        goto L_801E8C8C;
    // 0x801E8BDC: sw          $t6, 0xA0($sp)
    MEM_W(0XA0, ctx->r29) = ctx->r14;
L_801E8BE0:
    // 0x801E8BE0: lui         $v0, 0x8022
    ctx->r2 = S32(0X8022 << 16);
    // 0x801E8BE4: addiu       $v0, $v0, 0x6DC4
    ctx->r2 = ADD32(ctx->r2, 0X6DC4);
    // 0x801E8BE8: lbu         $t0, 0x26($v0)
    ctx->r8 = MEM_BU(ctx->r2, 0X26);
    // 0x801E8BEC: lbu         $t1, 0x27($v0)
    ctx->r9 = MEM_BU(ctx->r2, 0X27);
    // 0x801E8BF0: addiu       $t7, $zero, 0xA
    ctx->r15 = ADD32(0, 0XA);
    // 0x801E8BF4: addiu       $t8, $zero, 0x26
    ctx->r24 = ADD32(0, 0X26);
    // 0x801E8BF8: addiu       $t9, $zero, 0x27
    ctx->r25 = ADD32(0, 0X27);
    // 0x801E8BFC: sw          $t7, 0xB0($sp)
    MEM_W(0XB0, ctx->r29) = ctx->r15;
    // 0x801E8C00: sw          $t8, 0xAC($sp)
    MEM_W(0XAC, ctx->r29) = ctx->r24;
    // 0x801E8C04: sw          $t9, 0xA8($sp)
    MEM_W(0XA8, ctx->r29) = ctx->r25;
    // 0x801E8C08: sw          $t0, 0xA4($sp)
    MEM_W(0XA4, ctx->r29) = ctx->r8;
    // 0x801E8C0C: b           L_801E8C8C
    // 0x801E8C10: sw          $t1, 0xA0($sp)
    MEM_W(0XA0, ctx->r29) = ctx->r9;
        goto L_801E8C8C;
    // 0x801E8C10: sw          $t1, 0xA0($sp)
    MEM_W(0XA0, ctx->r29) = ctx->r9;
L_801E8C14:
    // 0x801E8C14: lui         $v0, 0x8022
    ctx->r2 = S32(0X8022 << 16);
    // 0x801E8C18: addiu       $v0, $v0, 0x6DF4
    ctx->r2 = ADD32(ctx->r2, 0X6DF4);
    // 0x801E8C1C: lbu         $t5, 0xA($v0)
    ctx->r13 = MEM_BU(ctx->r2, 0XA);
    // 0x801E8C20: lbu         $t6, 0xB($v0)
    ctx->r14 = MEM_BU(ctx->r2, 0XB);
    // 0x801E8C24: addiu       $t2, $zero, 0xC
    ctx->r10 = ADD32(0, 0XC);
    // 0x801E8C28: addiu       $t3, $zero, 0xA
    ctx->r11 = ADD32(0, 0XA);
    // 0x801E8C2C: addiu       $t4, $zero, 0xB
    ctx->r12 = ADD32(0, 0XB);
    // 0x801E8C30: sw          $t2, 0xB0($sp)
    MEM_W(0XB0, ctx->r29) = ctx->r10;
    // 0x801E8C34: sw          $t3, 0xAC($sp)
    MEM_W(0XAC, ctx->r29) = ctx->r11;
    // 0x801E8C38: sw          $t4, 0xA8($sp)
    MEM_W(0XA8, ctx->r29) = ctx->r12;
    // 0x801E8C3C: sw          $t5, 0xA4($sp)
    MEM_W(0XA4, ctx->r29) = ctx->r13;
    // 0x801E8C40: b           L_801E8C8C
    // 0x801E8C44: sw          $t6, 0xA0($sp)
    MEM_W(0XA0, ctx->r29) = ctx->r14;
        goto L_801E8C8C;
    // 0x801E8C44: sw          $t6, 0xA0($sp)
    MEM_W(0XA0, ctx->r29) = ctx->r14;
L_801E8C48:
    // 0x801E8C48: lui         $v0, 0x8022
    ctx->r2 = S32(0X8022 << 16);
    // 0x801E8C4C: lbu         $v0, 0x6E00($v0)
    ctx->r2 = MEM_BU(ctx->r2, 0X6E00);
    // 0x801E8C50: addiu       $t7, $zero, 0xC
    ctx->r15 = ADD32(0, 0XC);
    // 0x801E8C54: sw          $t7, 0xB0($sp)
    MEM_W(0XB0, ctx->r29) = ctx->r15;
    // 0x801E8C58: sw          $zero, 0xAC($sp)
    MEM_W(0XAC, ctx->r29) = 0;
    // 0x801E8C5C: sw          $zero, 0xA8($sp)
    MEM_W(0XA8, ctx->r29) = 0;
    // 0x801E8C60: sw          $v0, 0xA4($sp)
    MEM_W(0XA4, ctx->r29) = ctx->r2;
    // 0x801E8C64: b           L_801E8C8C
    // 0x801E8C68: sw          $v0, 0xA0($sp)
    MEM_W(0XA0, ctx->r29) = ctx->r2;
        goto L_801E8C8C;
    // 0x801E8C68: sw          $v0, 0xA0($sp)
    MEM_W(0XA0, ctx->r29) = ctx->r2;
L_801E8C6C:
    // 0x801E8C6C: lui         $v0, 0x8022
    ctx->r2 = S32(0X8022 << 16);
    // 0x801E8C70: lbu         $v0, 0x6E0C($v0)
    ctx->r2 = MEM_BU(ctx->r2, 0X6E0C);
    // 0x801E8C74: addiu       $t8, $zero, 0x10
    ctx->r24 = ADD32(0, 0X10);
    // 0x801E8C78: sw          $t8, 0xB0($sp)
    MEM_W(0XB0, ctx->r29) = ctx->r24;
    // 0x801E8C7C: sw          $zero, 0xAC($sp)
    MEM_W(0XAC, ctx->r29) = 0;
    // 0x801E8C80: sw          $zero, 0xA8($sp)
    MEM_W(0XA8, ctx->r29) = 0;
    // 0x801E8C84: sw          $v0, 0xA4($sp)
    MEM_W(0XA4, ctx->r29) = ctx->r2;
    // 0x801E8C88: sw          $v0, 0xA0($sp)
    MEM_W(0XA0, ctx->r29) = ctx->r2;
L_801E8C8C:
    // 0x801E8C8C: lw          $v0, 0xC0($sp)
    ctx->r2 = MEM_W(ctx->r29, 0XC0);
    // 0x801E8C90: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x801E8C94: mtc1        $at, $f20
    ctx->f20.u32l = ctx->r1;
    // 0x801E8C98: addiu       $at, $zero, 0x3E8
    ctx->r1 = ADD32(0, 0X3E8);
    // 0x801E8C9C: div         $zero, $v0, $at
    lo = S32(S64(S32(ctx->r2)) / S64(S32(ctx->r1))); hi = S32(S64(S32(ctx->r2)) % S64(S32(ctx->r1)));
    // 0x801E8CA0: mflo        $t9
    ctx->r25 = lo;
    // 0x801E8CA4: addiu       $at, $zero, 0x3C
    ctx->r1 = ADD32(0, 0X3C);
    // 0x801E8CA8: addiu       $s5, $zero, 0xA
    ctx->r21 = ADD32(0, 0XA);
    // 0x801E8CAC: div         $zero, $t9, $at
    lo = S32(S64(S32(ctx->r25)) / S64(S32(ctx->r1))); hi = S32(S64(S32(ctx->r25)) % S64(S32(ctx->r1)));
    // 0x801E8CB0: mflo        $t0
    ctx->r8 = lo;
    // 0x801E8CB4: lui         $s0, 0x8023
    ctx->r16 = S32(0X8023 << 16);
    // 0x801E8CB8: lui         $s1, 0x8023
    ctx->r17 = S32(0X8023 << 16);
    // 0x801E8CBC: div         $zero, $t0, $s5
    lo = S32(S64(S32(ctx->r8)) / S64(S32(ctx->r21))); hi = S32(S64(S32(ctx->r8)) % S64(S32(ctx->r21)));
    // 0x801E8CC0: lui         $s6, 0x8023
    ctx->r22 = S32(0X8023 << 16);
    // 0x801E8CC4: addiu       $s6, $s6, -0x75BC
    ctx->r22 = ADD32(ctx->r22, -0X75BC);
    // 0x801E8CC8: addiu       $s1, $s1, -0x75A8
    ctx->r17 = ADD32(ctx->r17, -0X75A8);
    // 0x801E8CCC: addiu       $s0, $s0, -0x75B8
    ctx->r16 = ADD32(ctx->r16, -0X75B8);
    // 0x801E8CD0: lui         $s2, 0x8023
    ctx->r18 = S32(0X8023 << 16);
    // 0x801E8CD4: lw          $t2, 0x0($s0)
    ctx->r10 = MEM_W(ctx->r16, 0X0);
    // 0x801E8CD8: lw          $t3, 0x0($s1)
    ctx->r11 = MEM_W(ctx->r17, 0X0);
    // 0x801E8CDC: lw          $t1, 0x0($s6)
    ctx->r9 = MEM_W(ctx->r22, 0X0);
    // 0x801E8CE0: addiu       $s2, $s2, -0x7598
    ctx->r18 = ADD32(ctx->r18, -0X7598);
    // 0x801E8CE4: or          $v0, $t9, $zero
    ctx->r2 = ctx->r25 | 0;
    // 0x801E8CE8: sw          $t2, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r10;
    // 0x801E8CEC: sw          $t3, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r11;
    // 0x801E8CF0: sw          $t1, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r9;
    // 0x801E8CF4: lw          $s4, 0xC8($sp)
    ctx->r20 = MEM_W(ctx->r29, 0XC8);
    // 0x801E8CF8: lw          $t1, 0xC($s0)
    ctx->r9 = MEM_W(ctx->r16, 0XC);
    // 0x801E8CFC: lw          $t3, 0xC($s2)
    ctx->r11 = MEM_W(ctx->r18, 0XC);
    // 0x801E8D00: lw          $t2, 0xC($s1)
    ctx->r10 = MEM_W(ctx->r17, 0XC);
    // 0x801E8D04: lw          $t9, 0x8($s1)
    ctx->r25 = MEM_W(ctx->r17, 0X8);
    // 0x801E8D08: lw          $t4, 0x0($s2)
    ctx->r12 = MEM_W(ctx->r18, 0X0);
    // 0x801E8D0C: lw          $t7, 0x4($s2)
    ctx->r15 = MEM_W(ctx->r18, 0X4);
    // 0x801E8D10: lw          $t5, 0x4($s0)
    ctx->r13 = MEM_W(ctx->r16, 0X4);
    // 0x801E8D14: lw          $t8, 0x8($s0)
    ctx->r24 = MEM_W(ctx->r16, 0X8);
    // 0x801E8D18: lw          $t6, 0x4($s1)
    ctx->r14 = MEM_W(ctx->r17, 0X4);
    // 0x801E8D1C: mfhi        $a2
    ctx->r6 = hi;
    // 0x801E8D20: or          $s3, $a3, $zero
    ctx->r19 = ctx->r7 | 0;
    // 0x801E8D24: sw          $v0, 0x84($sp)
    MEM_W(0X84, ctx->r29) = ctx->r2;
    // 0x801E8D28: or          $a1, $s7, $zero
    ctx->r5 = ctx->r23 | 0;
    // 0x801E8D2C: bne         $s5, $zero, L_801E8D38
    if (ctx->r21 != 0) {
        // 0x801E8D30: nop
    
            goto L_801E8D38;
    }
    // 0x801E8D30: nop

    // 0x801E8D34: break       7
    do_break(2149485876);
L_801E8D38:
    // 0x801E8D38: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x801E8D3C: bne         $s5, $at, L_801E8D50
    if (ctx->r21 != ctx->r1) {
        // 0x801E8D40: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_801E8D50;
    }
    // 0x801E8D40: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x801E8D44: bne         $t0, $at, L_801E8D50
    if (ctx->r8 != ctx->r1) {
        // 0x801E8D48: nop
    
            goto L_801E8D50;
    }
    // 0x801E8D48: nop

    // 0x801E8D4C: break       6
    do_break(2149485900);
L_801E8D50:
    // 0x801E8D50: lw          $t0, 0x8($s2)
    ctx->r8 = MEM_W(ctx->r18, 0X8);
    // 0x801E8D54: sw          $a3, 0xC4($sp)
    MEM_W(0XC4, ctx->r29) = ctx->r7;
    // 0x801E8D58: swc1        $f20, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->f20.u32l;
    // 0x801E8D5C: sw          $s4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r20;
    // 0x801E8D60: sw          $t1, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r9;
    // 0x801E8D64: sw          $t3, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r11;
    // 0x801E8D68: sw          $t2, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r10;
    // 0x801E8D6C: sw          $t9, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r25;
    // 0x801E8D70: sw          $t4, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r12;
    // 0x801E8D74: sw          $t7, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r15;
    // 0x801E8D78: sw          $t5, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r13;
    // 0x801E8D7C: sw          $t8, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r24;
    // 0x801E8D80: sw          $t6, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r14;
    // 0x801E8D84: jal         0x801E80B0
    // 0x801E8D88: sw          $t0, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r8;
    func_801E80B0(rdram, ctx);
        goto after_0;
    // 0x801E8D88: sw          $t0, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r8;
    after_0:
    // 0x801E8D8C: lw          $t4, 0xC4($sp)
    ctx->r12 = MEM_W(ctx->r29, 0XC4);
    // 0x801E8D90: lw          $t5, 0xB0($sp)
    ctx->r13 = MEM_W(ctx->r29, 0XB0);
    // 0x801E8D94: lw          $t6, 0x0($s6)
    ctx->r14 = MEM_W(ctx->r22, 0X0);
    // 0x801E8D98: lw          $t7, 0x0($s0)
    ctx->r15 = MEM_W(ctx->r16, 0X0);
    // 0x801E8D9C: lw          $t8, 0x0($s1)
    ctx->r24 = MEM_W(ctx->r17, 0X0);
    // 0x801E8DA0: addu        $s3, $t4, $t5
    ctx->r19 = ADD32(ctx->r12, ctx->r13);
    // 0x801E8DA4: sw          $t6, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r14;
    // 0x801E8DA8: sw          $t7, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r15;
    // 0x801E8DAC: sw          $t8, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r24;
    // 0x801E8DB0: lw          $t8, 0xC($s2)
    ctx->r24 = MEM_W(ctx->r18, 0XC);
    // 0x801E8DB4: lw          $t7, 0xC($s1)
    ctx->r15 = MEM_W(ctx->r17, 0XC);
    // 0x801E8DB8: lw          $t6, 0xC($s0)
    ctx->r14 = MEM_W(ctx->r16, 0XC);
    // 0x801E8DBC: lw          $t5, 0x8($s2)
    ctx->r13 = MEM_W(ctx->r18, 0X8);
    // 0x801E8DC0: lw          $t4, 0x8($s1)
    ctx->r12 = MEM_W(ctx->r17, 0X8);
    // 0x801E8DC4: lw          $t9, 0x0($s2)
    ctx->r25 = MEM_W(ctx->r18, 0X0);
    // 0x801E8DC8: lw          $t0, 0x4($s0)
    ctx->r8 = MEM_W(ctx->r16, 0X4);
    // 0x801E8DCC: lw          $t1, 0x4($s1)
    ctx->r9 = MEM_W(ctx->r17, 0X4);
    // 0x801E8DD0: lw          $t2, 0x4($s2)
    ctx->r10 = MEM_W(ctx->r18, 0X4);
    // 0x801E8DD4: lw          $t3, 0x8($s0)
    ctx->r11 = MEM_W(ctx->r16, 0X8);
    // 0x801E8DD8: or          $a3, $s3, $zero
    ctx->r7 = ctx->r19 | 0;
    // 0x801E8DDC: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x801E8DE0: or          $a1, $s7, $zero
    ctx->r5 = ctx->r23 | 0;
    // 0x801E8DE4: lw          $a2, 0xAC($sp)
    ctx->r6 = MEM_W(ctx->r29, 0XAC);
    // 0x801E8DE8: sw          $s4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r20;
    // 0x801E8DEC: swc1        $f20, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->f20.u32l;
    // 0x801E8DF0: sw          $t8, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r24;
    // 0x801E8DF4: sw          $t7, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r15;
    // 0x801E8DF8: sw          $t6, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r14;
    // 0x801E8DFC: sw          $t5, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r13;
    // 0x801E8E00: sw          $t4, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r12;
    // 0x801E8E04: sw          $t9, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r25;
    // 0x801E8E08: sw          $t0, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r8;
    // 0x801E8E0C: sw          $t1, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r9;
    // 0x801E8E10: sw          $t2, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r10;
    // 0x801E8E14: jal         0x801E80B0
    // 0x801E8E18: sw          $t3, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r11;
    func_801E80B0(rdram, ctx);
        goto after_1;
    // 0x801E8E18: sw          $t3, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r11;
    after_1:
    // 0x801E8E1C: lw          $v1, 0x84($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X84);
    // 0x801E8E20: addiu       $at, $zero, 0x3C
    ctx->r1 = ADD32(0, 0X3C);
    // 0x801E8E24: lw          $t9, 0xA4($sp)
    ctx->r25 = MEM_W(ctx->r29, 0XA4);
    // 0x801E8E28: div         $zero, $v1, $at
    lo = S32(S64(S32(ctx->r3)) / S64(S32(ctx->r1))); hi = S32(S64(S32(ctx->r3)) % S64(S32(ctx->r1)));
    // 0x801E8E2C: mfhi        $t0
    ctx->r8 = hi;
    // 0x801E8E30: or          $v1, $t0, $zero
    ctx->r3 = ctx->r8 | 0;
    // 0x801E8E34: lw          $t2, 0x0($s6)
    ctx->r10 = MEM_W(ctx->r22, 0X0);
    // 0x801E8E38: div         $zero, $t0, $s5
    lo = S32(S64(S32(ctx->r8)) / S64(S32(ctx->r21))); hi = S32(S64(S32(ctx->r8)) % S64(S32(ctx->r21)));
    // 0x801E8E3C: mflo        $t1
    ctx->r9 = lo;
    // 0x801E8E40: lw          $t3, 0x0($s0)
    ctx->r11 = MEM_W(ctx->r16, 0X0);
    // 0x801E8E44: lw          $t4, 0x0($s1)
    ctx->r12 = MEM_W(ctx->r17, 0X0);
    // 0x801E8E48: div         $zero, $t1, $s5
    lo = S32(S64(S32(ctx->r9)) / S64(S32(ctx->r21))); hi = S32(S64(S32(ctx->r9)) % S64(S32(ctx->r21)));
    // 0x801E8E4C: addu        $s3, $s3, $t9
    ctx->r19 = ADD32(ctx->r19, ctx->r25);
    // 0x801E8E50: sw          $t2, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r10;
    // 0x801E8E54: sw          $t3, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r11;
    // 0x801E8E58: sw          $t4, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r12;
    // 0x801E8E5C: lw          $t4, 0xC($s2)
    ctx->r12 = MEM_W(ctx->r18, 0XC);
    // 0x801E8E60: lw          $t3, 0xC($s1)
    ctx->r11 = MEM_W(ctx->r17, 0XC);
    // 0x801E8E64: lw          $t2, 0xC($s0)
    ctx->r10 = MEM_W(ctx->r16, 0XC);
    // 0x801E8E68: lw          $t9, 0x8($s0)
    ctx->r25 = MEM_W(ctx->r16, 0X8);
    // 0x801E8E6C: lw          $t0, 0x8($s1)
    ctx->r8 = MEM_W(ctx->r17, 0X8);
    // 0x801E8E70: lw          $t5, 0x0($s2)
    ctx->r13 = MEM_W(ctx->r18, 0X0);
    // 0x801E8E74: lw          $t6, 0x4($s0)
    ctx->r14 = MEM_W(ctx->r16, 0X4);
    // 0x801E8E78: lw          $t7, 0x4($s1)
    ctx->r15 = MEM_W(ctx->r17, 0X4);
    // 0x801E8E7C: lw          $t8, 0x4($s2)
    ctx->r24 = MEM_W(ctx->r18, 0X4);
    // 0x801E8E80: mfhi        $a2
    ctx->r6 = hi;
    // 0x801E8E84: or          $a3, $s3, $zero
    ctx->r7 = ctx->r19 | 0;
    // 0x801E8E88: sw          $v1, 0x80($sp)
    MEM_W(0X80, ctx->r29) = ctx->r3;
    // 0x801E8E8C: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x801E8E90: or          $a1, $s7, $zero
    ctx->r5 = ctx->r23 | 0;
    // 0x801E8E94: bne         $s5, $zero, L_801E8EA0
    if (ctx->r21 != 0) {
        // 0x801E8E98: nop
    
            goto L_801E8EA0;
    }
    // 0x801E8E98: nop

    // 0x801E8E9C: break       7
    do_break(2149486236);
L_801E8EA0:
    // 0x801E8EA0: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x801E8EA4: bne         $s5, $at, L_801E8EB8
    if (ctx->r21 != ctx->r1) {
        // 0x801E8EA8: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_801E8EB8;
    }
    // 0x801E8EA8: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x801E8EAC: bne         $v1, $at, L_801E8EB8
    if (ctx->r3 != ctx->r1) {
        // 0x801E8EB0: nop
    
            goto L_801E8EB8;
    }
    // 0x801E8EB0: nop

    // 0x801E8EB4: break       6
    do_break(2149486260);
L_801E8EB8:
    // 0x801E8EB8: sw          $s4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r20;
    // 0x801E8EBC: bne         $s5, $zero, L_801E8EC8
    if (ctx->r21 != 0) {
        // 0x801E8EC0: nop
    
            goto L_801E8EC8;
    }
    // 0x801E8EC0: nop

    // 0x801E8EC4: break       7
    do_break(2149486276);
L_801E8EC8:
    // 0x801E8EC8: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x801E8ECC: bne         $s5, $at, L_801E8EE0
    if (ctx->r21 != ctx->r1) {
        // 0x801E8ED0: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_801E8EE0;
    }
    // 0x801E8ED0: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x801E8ED4: bne         $t1, $at, L_801E8EE0
    if (ctx->r9 != ctx->r1) {
        // 0x801E8ED8: nop
    
            goto L_801E8EE0;
    }
    // 0x801E8ED8: nop

    // 0x801E8EDC: break       6
    do_break(2149486300);
L_801E8EE0:
    // 0x801E8EE0: lw          $t1, 0x8($s2)
    ctx->r9 = MEM_W(ctx->r18, 0X8);
    // 0x801E8EE4: swc1        $f20, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->f20.u32l;
    // 0x801E8EE8: sw          $t4, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r12;
    // 0x801E8EEC: sw          $t3, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r11;
    // 0x801E8EF0: sw          $t2, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r10;
    // 0x801E8EF4: sw          $t9, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r25;
    // 0x801E8EF8: sw          $t0, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r8;
    // 0x801E8EFC: sw          $t5, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r13;
    // 0x801E8F00: sw          $t6, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r14;
    // 0x801E8F04: sw          $t7, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r15;
    // 0x801E8F08: sw          $t8, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r24;
    // 0x801E8F0C: jal         0x801E80B0
    // 0x801E8F10: sw          $t1, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r9;
    func_801E80B0(rdram, ctx);
        goto after_2;
    // 0x801E8F10: sw          $t1, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r9;
    after_2:
    // 0x801E8F14: lw          $v1, 0x80($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X80);
    // 0x801E8F18: lw          $t5, 0xB0($sp)
    ctx->r13 = MEM_W(ctx->r29, 0XB0);
    // 0x801E8F1C: lw          $t6, 0x0($s6)
    ctx->r14 = MEM_W(ctx->r22, 0X0);
    // 0x801E8F20: div         $zero, $v1, $s5
    lo = S32(S64(S32(ctx->r3)) / S64(S32(ctx->r21))); hi = S32(S64(S32(ctx->r3)) % S64(S32(ctx->r21)));
    // 0x801E8F24: lw          $t7, 0x0($s0)
    ctx->r15 = MEM_W(ctx->r16, 0X0);
    // 0x801E8F28: lw          $t8, 0x0($s1)
    ctx->r24 = MEM_W(ctx->r17, 0X0);
    // 0x801E8F2C: addu        $s3, $s3, $t5
    ctx->r19 = ADD32(ctx->r19, ctx->r13);
    // 0x801E8F30: sw          $t6, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r14;
    // 0x801E8F34: sw          $t7, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r15;
    // 0x801E8F38: sw          $t8, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r24;
    // 0x801E8F3C: lw          $t8, 0xC($s2)
    ctx->r24 = MEM_W(ctx->r18, 0XC);
    // 0x801E8F40: lw          $t7, 0xC($s1)
    ctx->r15 = MEM_W(ctx->r17, 0XC);
    // 0x801E8F44: lw          $t6, 0xC($s0)
    ctx->r14 = MEM_W(ctx->r16, 0XC);
    // 0x801E8F48: lw          $t5, 0x8($s2)
    ctx->r13 = MEM_W(ctx->r18, 0X8);
    // 0x801E8F4C: lw          $t9, 0x0($s2)
    ctx->r25 = MEM_W(ctx->r18, 0X0);
    // 0x801E8F50: lw          $t0, 0x4($s0)
    ctx->r8 = MEM_W(ctx->r16, 0X4);
    // 0x801E8F54: lw          $t1, 0x4($s1)
    ctx->r9 = MEM_W(ctx->r17, 0X4);
    // 0x801E8F58: lw          $t2, 0x4($s2)
    ctx->r10 = MEM_W(ctx->r18, 0X4);
    // 0x801E8F5C: lw          $t3, 0x8($s0)
    ctx->r11 = MEM_W(ctx->r16, 0X8);
    // 0x801E8F60: lw          $t4, 0x8($s1)
    ctx->r12 = MEM_W(ctx->r17, 0X8);
    // 0x801E8F64: mfhi        $a2
    ctx->r6 = hi;
    // 0x801E8F68: or          $a3, $s3, $zero
    ctx->r7 = ctx->r19 | 0;
    // 0x801E8F6C: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x801E8F70: or          $a1, $s7, $zero
    ctx->r5 = ctx->r23 | 0;
    // 0x801E8F74: bne         $s5, $zero, L_801E8F80
    if (ctx->r21 != 0) {
        // 0x801E8F78: nop
    
            goto L_801E8F80;
    }
    // 0x801E8F78: nop

    // 0x801E8F7C: break       7
    do_break(2149486460);
L_801E8F80:
    // 0x801E8F80: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x801E8F84: bne         $s5, $at, L_801E8F98
    if (ctx->r21 != ctx->r1) {
        // 0x801E8F88: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_801E8F98;
    }
    // 0x801E8F88: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x801E8F8C: bne         $v1, $at, L_801E8F98
    if (ctx->r3 != ctx->r1) {
        // 0x801E8F90: nop
    
            goto L_801E8F98;
    }
    // 0x801E8F90: nop

    // 0x801E8F94: break       6
    do_break(2149486484);
L_801E8F98:
    // 0x801E8F98: sw          $s4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r20;
    // 0x801E8F9C: swc1        $f20, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->f20.u32l;
    // 0x801E8FA0: sw          $t8, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r24;
    // 0x801E8FA4: sw          $t7, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r15;
    // 0x801E8FA8: sw          $t6, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r14;
    // 0x801E8FAC: sw          $t5, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r13;
    // 0x801E8FB0: sw          $t9, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r25;
    // 0x801E8FB4: sw          $t0, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r8;
    // 0x801E8FB8: sw          $t1, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r9;
    // 0x801E8FBC: sw          $t2, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r10;
    // 0x801E8FC0: sw          $t3, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r11;
    // 0x801E8FC4: jal         0x801E80B0
    // 0x801E8FC8: sw          $t4, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r12;
    func_801E80B0(rdram, ctx);
        goto after_3;
    // 0x801E8FC8: sw          $t4, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r12;
    after_3:
    // 0x801E8FCC: lw          $t9, 0xB0($sp)
    ctx->r25 = MEM_W(ctx->r29, 0XB0);
    // 0x801E8FD0: lw          $t0, 0x0($s6)
    ctx->r8 = MEM_W(ctx->r22, 0X0);
    // 0x801E8FD4: lw          $t1, 0x0($s0)
    ctx->r9 = MEM_W(ctx->r16, 0X0);
    // 0x801E8FD8: lw          $t2, 0x0($s1)
    ctx->r10 = MEM_W(ctx->r17, 0X0);
    // 0x801E8FDC: addu        $s3, $s3, $t9
    ctx->r19 = ADD32(ctx->r19, ctx->r25);
    // 0x801E8FE0: sw          $t0, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r8;
    // 0x801E8FE4: sw          $t1, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r9;
    // 0x801E8FE8: sw          $t2, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r10;
    // 0x801E8FEC: lw          $t2, 0xC($s2)
    ctx->r10 = MEM_W(ctx->r18, 0XC);
    // 0x801E8FF0: lw          $t1, 0xC($s1)
    ctx->r9 = MEM_W(ctx->r17, 0XC);
    // 0x801E8FF4: lw          $t0, 0xC($s0)
    ctx->r8 = MEM_W(ctx->r16, 0XC);
    // 0x801E8FF8: lw          $t9, 0x8($s2)
    ctx->r25 = MEM_W(ctx->r18, 0X8);
    // 0x801E8FFC: lw          $t3, 0x0($s2)
    ctx->r11 = MEM_W(ctx->r18, 0X0);
    // 0x801E9000: lw          $t4, 0x4($s0)
    ctx->r12 = MEM_W(ctx->r16, 0X4);
    // 0x801E9004: lw          $t5, 0x4($s1)
    ctx->r13 = MEM_W(ctx->r17, 0X4);
    // 0x801E9008: lw          $t6, 0x4($s2)
    ctx->r14 = MEM_W(ctx->r18, 0X4);
    // 0x801E900C: lw          $t7, 0x8($s0)
    ctx->r15 = MEM_W(ctx->r16, 0X8);
    // 0x801E9010: lw          $t8, 0x8($s1)
    ctx->r24 = MEM_W(ctx->r17, 0X8);
    // 0x801E9014: or          $a3, $s3, $zero
    ctx->r7 = ctx->r19 | 0;
    // 0x801E9018: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x801E901C: or          $a1, $s7, $zero
    ctx->r5 = ctx->r23 | 0;
    // 0x801E9020: lw          $a2, 0xA8($sp)
    ctx->r6 = MEM_W(ctx->r29, 0XA8);
    // 0x801E9024: sw          $s4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r20;
    // 0x801E9028: swc1        $f20, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->f20.u32l;
    // 0x801E902C: sw          $t2, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r10;
    // 0x801E9030: sw          $t1, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r9;
    // 0x801E9034: sw          $t0, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r8;
    // 0x801E9038: sw          $t9, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r25;
    // 0x801E903C: sw          $t3, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r11;
    // 0x801E9040: sw          $t4, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r12;
    // 0x801E9044: sw          $t5, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r13;
    // 0x801E9048: sw          $t6, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r14;
    // 0x801E904C: sw          $t7, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r15;
    // 0x801E9050: jal         0x801E80B0
    // 0x801E9054: sw          $t8, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r24;
    func_801E80B0(rdram, ctx);
        goto after_4;
    // 0x801E9054: sw          $t8, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r24;
    after_4:
    // 0x801E9058: lw          $v1, 0xC0($sp)
    ctx->r3 = MEM_W(ctx->r29, 0XC0);
    // 0x801E905C: addiu       $at, $zero, 0x3E8
    ctx->r1 = ADD32(0, 0X3E8);
    // 0x801E9060: lw          $t3, 0xA0($sp)
    ctx->r11 = MEM_W(ctx->r29, 0XA0);
    // 0x801E9064: div         $zero, $v1, $at
    lo = S32(S64(S32(ctx->r3)) / S64(S32(ctx->r1))); hi = S32(S64(S32(ctx->r3)) % S64(S32(ctx->r1)));
    // 0x801E9068: mfhi        $t4
    ctx->r12 = hi;
    // 0x801E906C: addiu       $at, $zero, 0x64
    ctx->r1 = ADD32(0, 0X64);
    // 0x801E9070: lw          $t6, 0x0($s6)
    ctx->r14 = MEM_W(ctx->r22, 0X0);
    // 0x801E9074: div         $zero, $t4, $at
    lo = S32(S64(S32(ctx->r12)) / S64(S32(ctx->r1))); hi = S32(S64(S32(ctx->r12)) % S64(S32(ctx->r1)));
    // 0x801E9078: mflo        $t5
    ctx->r13 = lo;
    // 0x801E907C: lw          $t7, 0x0($s0)
    ctx->r15 = MEM_W(ctx->r16, 0X0);
    // 0x801E9080: lw          $t8, 0x0($s1)
    ctx->r24 = MEM_W(ctx->r17, 0X0);
    // 0x801E9084: div         $zero, $t5, $s5
    lo = S32(S64(S32(ctx->r13)) / S64(S32(ctx->r21))); hi = S32(S64(S32(ctx->r13)) % S64(S32(ctx->r21)));
    // 0x801E9088: or          $v1, $t4, $zero
    ctx->r3 = ctx->r12 | 0;
    // 0x801E908C: addu        $s3, $s3, $t3
    ctx->r19 = ADD32(ctx->r19, ctx->r11);
    // 0x801E9090: sw          $t6, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r14;
    // 0x801E9094: sw          $t7, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r15;
    // 0x801E9098: sw          $t8, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r24;
    // 0x801E909C: lw          $t8, 0xC($s2)
    ctx->r24 = MEM_W(ctx->r18, 0XC);
    // 0x801E90A0: lw          $t7, 0xC($s1)
    ctx->r15 = MEM_W(ctx->r17, 0XC);
    // 0x801E90A4: lw          $t6, 0xC($s0)
    ctx->r14 = MEM_W(ctx->r16, 0XC);
    // 0x801E90A8: lw          $t3, 0x8($s0)
    ctx->r11 = MEM_W(ctx->r16, 0X8);
    // 0x801E90AC: lw          $t4, 0x8($s1)
    ctx->r12 = MEM_W(ctx->r17, 0X8);
    // 0x801E90B0: lw          $t9, 0x0($s2)
    ctx->r25 = MEM_W(ctx->r18, 0X0);
    // 0x801E90B4: lw          $t0, 0x4($s0)
    ctx->r8 = MEM_W(ctx->r16, 0X4);
    // 0x801E90B8: lw          $t1, 0x4($s1)
    ctx->r9 = MEM_W(ctx->r17, 0X4);
    // 0x801E90BC: lw          $t2, 0x4($s2)
    ctx->r10 = MEM_W(ctx->r18, 0X4);
    // 0x801E90C0: mfhi        $a2
    ctx->r6 = hi;
    // 0x801E90C4: or          $a3, $s3, $zero
    ctx->r7 = ctx->r19 | 0;
    // 0x801E90C8: sw          $v1, 0x84($sp)
    MEM_W(0X84, ctx->r29) = ctx->r3;
    // 0x801E90CC: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x801E90D0: or          $a1, $s7, $zero
    ctx->r5 = ctx->r23 | 0;
    // 0x801E90D4: bne         $s5, $zero, L_801E90E0
    if (ctx->r21 != 0) {
        // 0x801E90D8: nop
    
            goto L_801E90E0;
    }
    // 0x801E90D8: nop

    // 0x801E90DC: break       7
    do_break(2149486812);
L_801E90E0:
    // 0x801E90E0: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x801E90E4: bne         $s5, $at, L_801E90F8
    if (ctx->r21 != ctx->r1) {
        // 0x801E90E8: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_801E90F8;
    }
    // 0x801E90E8: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x801E90EC: bne         $t5, $at, L_801E90F8
    if (ctx->r13 != ctx->r1) {
        // 0x801E90F0: nop
    
            goto L_801E90F8;
    }
    // 0x801E90F0: nop

    // 0x801E90F4: break       6
    do_break(2149486836);
L_801E90F8:
    // 0x801E90F8: lw          $t5, 0x8($s2)
    ctx->r13 = MEM_W(ctx->r18, 0X8);
    // 0x801E90FC: sw          $s4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r20;
    // 0x801E9100: swc1        $f20, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->f20.u32l;
    // 0x801E9104: sw          $t8, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r24;
    // 0x801E9108: sw          $t7, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r15;
    // 0x801E910C: sw          $t6, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r14;
    // 0x801E9110: sw          $t3, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r11;
    // 0x801E9114: sw          $t4, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r12;
    // 0x801E9118: sw          $t9, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r25;
    // 0x801E911C: sw          $t0, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r8;
    // 0x801E9120: sw          $t1, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r9;
    // 0x801E9124: sw          $t2, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r10;
    // 0x801E9128: jal         0x801E80B0
    // 0x801E912C: sw          $t5, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r13;
    func_801E80B0(rdram, ctx);
        goto after_5;
    // 0x801E912C: sw          $t5, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r13;
    after_5:
    // 0x801E9130: lw          $t0, 0x84($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X84);
    // 0x801E9134: lw          $t9, 0xB0($sp)
    ctx->r25 = MEM_W(ctx->r29, 0XB0);
    // 0x801E9138: lw          $t2, 0x0($s6)
    ctx->r10 = MEM_W(ctx->r22, 0X0);
    // 0x801E913C: div         $zero, $t0, $s5
    lo = S32(S64(S32(ctx->r8)) / S64(S32(ctx->r21))); hi = S32(S64(S32(ctx->r8)) % S64(S32(ctx->r21)));
    // 0x801E9140: mflo        $t1
    ctx->r9 = lo;
    // 0x801E9144: lw          $t3, 0x0($s0)
    ctx->r11 = MEM_W(ctx->r16, 0X0);
    // 0x801E9148: lw          $t4, 0x0($s1)
    ctx->r12 = MEM_W(ctx->r17, 0X0);
    // 0x801E914C: div         $zero, $t1, $s5
    lo = S32(S64(S32(ctx->r9)) / S64(S32(ctx->r21))); hi = S32(S64(S32(ctx->r9)) % S64(S32(ctx->r21)));
    // 0x801E9150: addu        $s3, $s3, $t9
    ctx->r19 = ADD32(ctx->r19, ctx->r25);
    // 0x801E9154: sw          $t2, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r10;
    // 0x801E9158: sw          $t3, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r11;
    // 0x801E915C: sw          $t4, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r12;
    // 0x801E9160: lw          $t4, 0xC($s2)
    ctx->r12 = MEM_W(ctx->r18, 0XC);
    // 0x801E9164: lw          $t3, 0xC($s1)
    ctx->r11 = MEM_W(ctx->r17, 0XC);
    // 0x801E9168: lw          $t2, 0xC($s0)
    ctx->r10 = MEM_W(ctx->r16, 0XC);
    // 0x801E916C: lw          $t9, 0x8($s0)
    ctx->r25 = MEM_W(ctx->r16, 0X8);
    // 0x801E9170: lw          $t5, 0x0($s2)
    ctx->r13 = MEM_W(ctx->r18, 0X0);
    // 0x801E9174: lw          $t6, 0x4($s0)
    ctx->r14 = MEM_W(ctx->r16, 0X4);
    // 0x801E9178: lw          $t7, 0x4($s1)
    ctx->r15 = MEM_W(ctx->r17, 0X4);
    // 0x801E917C: lw          $t8, 0x4($s2)
    ctx->r24 = MEM_W(ctx->r18, 0X4);
    // 0x801E9180: mfhi        $a2
    ctx->r6 = hi;
    // 0x801E9184: or          $a3, $s3, $zero
    ctx->r7 = ctx->r19 | 0;
    // 0x801E9188: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x801E918C: or          $a1, $s7, $zero
    ctx->r5 = ctx->r23 | 0;
    // 0x801E9190: bne         $s5, $zero, L_801E919C
    if (ctx->r21 != 0) {
        // 0x801E9194: nop
    
            goto L_801E919C;
    }
    // 0x801E9194: nop

    // 0x801E9198: break       7
    do_break(2149487000);
L_801E919C:
    // 0x801E919C: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x801E91A0: bne         $s5, $at, L_801E91B4
    if (ctx->r21 != ctx->r1) {
        // 0x801E91A4: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_801E91B4;
    }
    // 0x801E91A4: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x801E91A8: bne         $t0, $at, L_801E91B4
    if (ctx->r8 != ctx->r1) {
        // 0x801E91AC: nop
    
            goto L_801E91B4;
    }
    // 0x801E91AC: nop

    // 0x801E91B0: break       6
    do_break(2149487024);
L_801E91B4:
    // 0x801E91B4: lw          $t0, 0x8($s1)
    ctx->r8 = MEM_W(ctx->r17, 0X8);
    // 0x801E91B8: bne         $s5, $zero, L_801E91C4
    if (ctx->r21 != 0) {
        // 0x801E91BC: nop
    
            goto L_801E91C4;
    }
    // 0x801E91BC: nop

    // 0x801E91C0: break       7
    do_break(2149487040);
L_801E91C4:
    // 0x801E91C4: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x801E91C8: bne         $s5, $at, L_801E91DC
    if (ctx->r21 != ctx->r1) {
        // 0x801E91CC: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_801E91DC;
    }
    // 0x801E91CC: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x801E91D0: bne         $t1, $at, L_801E91DC
    if (ctx->r9 != ctx->r1) {
        // 0x801E91D4: nop
    
            goto L_801E91DC;
    }
    // 0x801E91D4: nop

    // 0x801E91D8: break       6
    do_break(2149487064);
L_801E91DC:
    // 0x801E91DC: lw          $t1, 0x8($s2)
    ctx->r9 = MEM_W(ctx->r18, 0X8);
    // 0x801E91E0: sw          $s4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r20;
    // 0x801E91E4: swc1        $f20, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->f20.u32l;
    // 0x801E91E8: sw          $t4, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r12;
    // 0x801E91EC: sw          $t3, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r11;
    // 0x801E91F0: sw          $t2, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r10;
    // 0x801E91F4: sw          $t9, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r25;
    // 0x801E91F8: sw          $t5, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r13;
    // 0x801E91FC: sw          $t6, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r14;
    // 0x801E9200: sw          $t7, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r15;
    // 0x801E9204: sw          $t8, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r24;
    // 0x801E9208: sw          $t0, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r8;
    // 0x801E920C: jal         0x801E80B0
    // 0x801E9210: sw          $t1, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r9;
    func_801E80B0(rdram, ctx);
        goto after_6;
    // 0x801E9210: sw          $t1, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r9;
    after_6:
    // 0x801E9214: lw          $t6, 0x84($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X84);
    // 0x801E9218: lw          $t5, 0xB0($sp)
    ctx->r13 = MEM_W(ctx->r29, 0XB0);
    // 0x801E921C: lw          $t7, 0x0($s6)
    ctx->r15 = MEM_W(ctx->r22, 0X0);
    // 0x801E9220: div         $zero, $t6, $s5
    lo = S32(S64(S32(ctx->r14)) / S64(S32(ctx->r21))); hi = S32(S64(S32(ctx->r14)) % S64(S32(ctx->r21)));
    // 0x801E9224: lw          $t8, 0x0($s0)
    ctx->r24 = MEM_W(ctx->r16, 0X0);
    // 0x801E9228: lw          $t9, 0x0($s1)
    ctx->r25 = MEM_W(ctx->r17, 0X0);
    // 0x801E922C: addu        $s3, $s3, $t5
    ctx->r19 = ADD32(ctx->r19, ctx->r13);
    // 0x801E9230: sw          $t7, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r15;
    // 0x801E9234: sw          $t8, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r24;
    // 0x801E9238: sw          $t9, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r25;
    // 0x801E923C: lw          $t9, 0xC($s2)
    ctx->r25 = MEM_W(ctx->r18, 0XC);
    // 0x801E9240: lw          $t8, 0xC($s1)
    ctx->r24 = MEM_W(ctx->r17, 0XC);
    // 0x801E9244: lw          $t7, 0xC($s0)
    ctx->r15 = MEM_W(ctx->r16, 0XC);
    // 0x801E9248: lw          $t5, 0x8($s1)
    ctx->r13 = MEM_W(ctx->r17, 0X8);
    // 0x801E924C: lw          $t0, 0x0($s2)
    ctx->r8 = MEM_W(ctx->r18, 0X0);
    // 0x801E9250: lw          $t1, 0x4($s0)
    ctx->r9 = MEM_W(ctx->r16, 0X4);
    // 0x801E9254: lw          $t2, 0x4($s1)
    ctx->r10 = MEM_W(ctx->r17, 0X4);
    // 0x801E9258: lw          $t3, 0x4($s2)
    ctx->r11 = MEM_W(ctx->r18, 0X4);
    // 0x801E925C: lw          $t4, 0x8($s0)
    ctx->r12 = MEM_W(ctx->r16, 0X8);
    // 0x801E9260: mfhi        $a2
    ctx->r6 = hi;
    // 0x801E9264: or          $a3, $s3, $zero
    ctx->r7 = ctx->r19 | 0;
    // 0x801E9268: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x801E926C: or          $a1, $s7, $zero
    ctx->r5 = ctx->r23 | 0;
    // 0x801E9270: bne         $s5, $zero, L_801E927C
    if (ctx->r21 != 0) {
        // 0x801E9274: nop
    
            goto L_801E927C;
    }
    // 0x801E9274: nop

    // 0x801E9278: break       7
    do_break(2149487224);
L_801E927C:
    // 0x801E927C: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x801E9280: bne         $s5, $at, L_801E9294
    if (ctx->r21 != ctx->r1) {
        // 0x801E9284: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_801E9294;
    }
    // 0x801E9284: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x801E9288: bne         $t6, $at, L_801E9294
    if (ctx->r14 != ctx->r1) {
        // 0x801E928C: nop
    
            goto L_801E9294;
    }
    // 0x801E928C: nop

    // 0x801E9290: break       6
    do_break(2149487248);
L_801E9294:
    // 0x801E9294: lw          $t6, 0x8($s2)
    ctx->r14 = MEM_W(ctx->r18, 0X8);
    // 0x801E9298: sw          $s4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r20;
    // 0x801E929C: swc1        $f20, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->f20.u32l;
    // 0x801E92A0: sw          $t9, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r25;
    // 0x801E92A4: sw          $t8, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r24;
    // 0x801E92A8: sw          $t7, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r15;
    // 0x801E92AC: sw          $t5, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r13;
    // 0x801E92B0: sw          $t0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r8;
    // 0x801E92B4: sw          $t1, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r9;
    // 0x801E92B8: sw          $t2, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r10;
    // 0x801E92BC: sw          $t3, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r11;
    // 0x801E92C0: sw          $t4, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r12;
    // 0x801E92C4: jal         0x801E80B0
    // 0x801E92C8: sw          $t6, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r14;
    func_801E80B0(rdram, ctx);
        goto after_7;
    // 0x801E92C8: sw          $t6, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r14;
    after_7:
    // 0x801E92CC: lw          $ra, 0x7C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X7C);
    // 0x801E92D0: ldc1        $f20, 0x50($sp)
    CHECK_FR(ctx, 20);
    ctx->f20.u64 = LD(ctx->r29, 0X50);
    // 0x801E92D4: lw          $s0, 0x5C($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X5C);
    // 0x801E92D8: lw          $s1, 0x60($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X60);
    // 0x801E92DC: lw          $s2, 0x64($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X64);
    // 0x801E92E0: lw          $s3, 0x68($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X68);
    // 0x801E92E4: lw          $s4, 0x6C($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X6C);
    // 0x801E92E8: lw          $s5, 0x70($sp)
    ctx->r21 = MEM_W(ctx->r29, 0X70);
    // 0x801E92EC: lw          $s6, 0x74($sp)
    ctx->r22 = MEM_W(ctx->r29, 0X74);
    // 0x801E92F0: lw          $s7, 0x78($sp)
    ctx->r23 = MEM_W(ctx->r29, 0X78);
    // 0x801E92F4: jr          $ra
    // 0x801E92F8: addiu       $sp, $sp, 0xB8
    ctx->r29 = ADD32(ctx->r29, 0XB8);
    return;
    // 0x801E92F8: addiu       $sp, $sp, 0xB8
    ctx->r29 = ADD32(ctx->r29, 0XB8);
;}
RECOMP_FUNC void func_801E92FC(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801E92FC: addiu       $sp, $sp, -0x40
    ctx->r29 = ADD32(ctx->r29, -0X40);
    // 0x801E9300: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x801E9304: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x801E9308: lbu         $t6, 0x63($sp)
    ctx->r14 = MEM_BU(ctx->r29, 0X63);
    // 0x801E930C: lbu         $t7, 0x67($sp)
    ctx->r15 = MEM_BU(ctx->r29, 0X67);
    // 0x801E9310: lbu         $t8, 0x6B($sp)
    ctx->r24 = MEM_BU(ctx->r29, 0X6B);
    // 0x801E9314: lbu         $t9, 0x6F($sp)
    ctx->r25 = MEM_BU(ctx->r29, 0X6F);
    // 0x801E9318: lbu         $t0, 0x73($sp)
    ctx->r8 = MEM_BU(ctx->r29, 0X73);
    // 0x801E931C: lbu         $t1, 0x77($sp)
    ctx->r9 = MEM_BU(ctx->r29, 0X77);
    // 0x801E9320: lbu         $t2, 0x7B($sp)
    ctx->r10 = MEM_BU(ctx->r29, 0X7B);
    // 0x801E9324: lbu         $t3, 0x7F($sp)
    ctx->r11 = MEM_BU(ctx->r29, 0X7F);
    // 0x801E9328: lbu         $t4, 0x83($sp)
    ctx->r12 = MEM_BU(ctx->r29, 0X83);
    // 0x801E932C: lbu         $t5, 0x87($sp)
    ctx->r13 = MEM_BU(ctx->r29, 0X87);
    // 0x801E9330: sw          $ra, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r31;
    // 0x801E9334: sw          $a1, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r5;
    // 0x801E9338: sw          $a2, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r6;
    // 0x801E933C: sw          $a3, 0x4C($sp)
    MEM_W(0X4C, ctx->r29) = ctx->r7;
    // 0x801E9340: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E9344: lbu         $a3, 0x5F($sp)
    ctx->r7 = MEM_BU(ctx->r29, 0X5F);
    // 0x801E9348: lbu         $a2, 0x5B($sp)
    ctx->r6 = MEM_BU(ctx->r29, 0X5B);
    // 0x801E934C: lw          $a1, 0x54($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X54);
    // 0x801E9350: swc1        $f4, 0x6E24($at)
    MEM_W(0X6E24, ctx->r1) = ctx->f4.u32l;
    // 0x801E9354: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x801E9358: sw          $t7, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r15;
    // 0x801E935C: sw          $t8, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r24;
    // 0x801E9360: sw          $t9, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r25;
    // 0x801E9364: sw          $t0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r8;
    // 0x801E9368: sw          $t1, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r9;
    // 0x801E936C: sw          $t2, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r10;
    // 0x801E9370: sw          $t3, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r11;
    // 0x801E9374: sw          $t4, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r12;
    // 0x801E9378: jal         0x801E946C
    // 0x801E937C: sw          $t5, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r13;
    func_801E946C(rdram, ctx);
        goto after_0;
    // 0x801E937C: sw          $t5, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r13;
    after_0:
    // 0x801E9380: lw          $t6, 0x50($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X50);
    // 0x801E9384: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E9388: sh          $zero, 0x6E28($at)
    MEM_H(0X6E28, ctx->r1) = 0;
    // 0x801E938C: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x801E9390: lw          $a1, 0x44($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X44);
    // 0x801E9394: lw          $a2, 0x48($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X48);
    // 0x801E9398: lw          $a3, 0x4C($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X4C);
    // 0x801E939C: jal         0x801E9858
    // 0x801E93A0: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    func_801E9858(rdram, ctx);
        goto after_1;
    // 0x801E93A0: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    after_1:
    // 0x801E93A4: lw          $ra, 0x3C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X3C);
    // 0x801E93A8: addiu       $sp, $sp, 0x40
    ctx->r29 = ADD32(ctx->r29, 0X40);
    // 0x801E93AC: jr          $ra
    // 0x801E93B0: nop

    return;
    // 0x801E93B0: nop

;}
RECOMP_FUNC void func_801E93B4(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801E93B4: addiu       $sp, $sp, -0x40
    ctx->r29 = ADD32(ctx->r29, -0X40);
    // 0x801E93B8: lwc1        $f4, 0x88($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X88);
    // 0x801E93BC: lbu         $t6, 0x63($sp)
    ctx->r14 = MEM_BU(ctx->r29, 0X63);
    // 0x801E93C0: lbu         $t7, 0x67($sp)
    ctx->r15 = MEM_BU(ctx->r29, 0X67);
    // 0x801E93C4: lbu         $t8, 0x6B($sp)
    ctx->r24 = MEM_BU(ctx->r29, 0X6B);
    // 0x801E93C8: lbu         $t9, 0x6F($sp)
    ctx->r25 = MEM_BU(ctx->r29, 0X6F);
    // 0x801E93CC: lbu         $t0, 0x73($sp)
    ctx->r8 = MEM_BU(ctx->r29, 0X73);
    // 0x801E93D0: lbu         $t1, 0x77($sp)
    ctx->r9 = MEM_BU(ctx->r29, 0X77);
    // 0x801E93D4: lbu         $t2, 0x7B($sp)
    ctx->r10 = MEM_BU(ctx->r29, 0X7B);
    // 0x801E93D8: lbu         $t3, 0x7F($sp)
    ctx->r11 = MEM_BU(ctx->r29, 0X7F);
    // 0x801E93DC: lbu         $t4, 0x83($sp)
    ctx->r12 = MEM_BU(ctx->r29, 0X83);
    // 0x801E93E0: lbu         $t5, 0x87($sp)
    ctx->r13 = MEM_BU(ctx->r29, 0X87);
    // 0x801E93E4: sw          $ra, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r31;
    // 0x801E93E8: sw          $a1, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r5;
    // 0x801E93EC: sw          $a2, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r6;
    // 0x801E93F0: sw          $a3, 0x4C($sp)
    MEM_W(0X4C, ctx->r29) = ctx->r7;
    // 0x801E93F4: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E93F8: lbu         $a3, 0x5F($sp)
    ctx->r7 = MEM_BU(ctx->r29, 0X5F);
    // 0x801E93FC: lbu         $a2, 0x5B($sp)
    ctx->r6 = MEM_BU(ctx->r29, 0X5B);
    // 0x801E9400: lw          $a1, 0x54($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X54);
    // 0x801E9404: swc1        $f4, 0x6E24($at)
    MEM_W(0X6E24, ctx->r1) = ctx->f4.u32l;
    // 0x801E9408: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x801E940C: sw          $t7, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r15;
    // 0x801E9410: sw          $t8, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r24;
    // 0x801E9414: sw          $t9, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r25;
    // 0x801E9418: sw          $t0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r8;
    // 0x801E941C: sw          $t1, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r9;
    // 0x801E9420: sw          $t2, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r10;
    // 0x801E9424: sw          $t3, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r11;
    // 0x801E9428: sw          $t4, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r12;
    // 0x801E942C: jal         0x801E946C
    // 0x801E9430: sw          $t5, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r13;
    func_801E946C(rdram, ctx);
        goto after_0;
    // 0x801E9430: sw          $t5, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r13;
    after_0:
    // 0x801E9434: lw          $t7, 0x50($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X50);
    // 0x801E9438: addiu       $t6, $zero, 0x1
    ctx->r14 = ADD32(0, 0X1);
    // 0x801E943C: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E9440: sh          $t6, 0x6E28($at)
    MEM_H(0X6E28, ctx->r1) = ctx->r14;
    // 0x801E9444: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x801E9448: lw          $a1, 0x44($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X44);
    // 0x801E944C: lw          $a2, 0x48($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X48);
    // 0x801E9450: lw          $a3, 0x4C($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X4C);
    // 0x801E9454: jal         0x801E9858
    // 0x801E9458: sw          $t7, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r15;
    func_801E9858(rdram, ctx);
        goto after_1;
    // 0x801E9458: sw          $t7, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r15;
    after_1:
    // 0x801E945C: lw          $ra, 0x3C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X3C);
    // 0x801E9460: addiu       $sp, $sp, 0x40
    ctx->r29 = ADD32(ctx->r29, 0X40);
    // 0x801E9464: jr          $ra
    // 0x801E9468: nop

    return;
    // 0x801E9468: nop

;}
RECOMP_FUNC void func_801E946C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801E946C: addiu       $t8, $zero, 0x64
    ctx->r24 = ADD32(0, 0X64);
    // 0x801E9470: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E9474: sw          $t8, 0x6E2C($at)
    MEM_W(0X6E2C, ctx->r1) = ctx->r24;
    // 0x801E9478: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801E947C: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x801E9480: sw          $a1, -0x75BC($at)
    MEM_W(-0X75BC, ctx->r1) = ctx->r5;
    // 0x801E9484: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E9488: sh          $zero, 0x6E28($at)
    MEM_H(0X6E28, ctx->r1) = 0;
    // 0x801E948C: lbu         $t9, 0x2B($sp)
    ctx->r25 = MEM_BU(ctx->r29, 0X2B);
    // 0x801E9490: lbu         $t2, 0x2F($sp)
    ctx->r10 = MEM_BU(ctx->r29, 0X2F);
    // 0x801E9494: lbu         $t3, 0x33($sp)
    ctx->r11 = MEM_BU(ctx->r29, 0X33);
    // 0x801E9498: lui         $v0, 0x8023
    ctx->r2 = S32(0X8023 << 16);
    // 0x801E949C: lui         $v1, 0x8023
    ctx->r3 = S32(0X8023 << 16);
    // 0x801E94A0: addiu       $v1, $v1, -0x75A8
    ctx->r3 = ADD32(ctx->r3, -0X75A8);
    // 0x801E94A4: addiu       $v0, $v0, -0x75B8
    ctx->r2 = ADD32(ctx->r2, -0X75B8);
    // 0x801E94A8: andi        $t6, $a2, 0xFF
    ctx->r14 = ctx->r6 & 0XFF;
    // 0x801E94AC: andi        $t7, $a3, 0xFF
    ctx->r15 = ctx->r7 & 0XFF;
    // 0x801E94B0: lui         $t0, 0x8023
    ctx->r8 = S32(0X8023 << 16);
    // 0x801E94B4: addiu       $t0, $t0, -0x7598
    ctx->r8 = ADD32(ctx->r8, -0X7598);
    // 0x801E94B8: sw          $a2, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r6;
    // 0x801E94BC: sw          $a3, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r7;
    // 0x801E94C0: or          $a3, $t7, $zero
    ctx->r7 = ctx->r15 | 0;
    // 0x801E94C4: or          $a2, $t6, $zero
    ctx->r6 = ctx->r14 | 0;
    // 0x801E94C8: sw          $t7, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r15;
    // 0x801E94CC: sw          $t6, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r14;
    // 0x801E94D0: sw          $t9, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r25;
    // 0x801E94D4: sw          $t2, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r10;
    // 0x801E94D8: sw          $t3, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r11;
    // 0x801E94DC: lbu         $t4, 0x37($sp)
    ctx->r12 = MEM_BU(ctx->r29, 0X37);
    // 0x801E94E0: lbu         $t6, 0x3F($sp)
    ctx->r14 = MEM_BU(ctx->r29, 0X3F);
    // 0x801E94E4: lbu         $t7, 0x43($sp)
    ctx->r15 = MEM_BU(ctx->r29, 0X43);
    // 0x801E94E8: lbu         $t5, 0x3B($sp)
    ctx->r13 = MEM_BU(ctx->r29, 0X3B);
    // 0x801E94EC: lbu         $t2, 0x4F($sp)
    ctx->r10 = MEM_BU(ctx->r29, 0X4F);
    // 0x801E94F0: lbu         $t9, 0x4B($sp)
    ctx->r25 = MEM_BU(ctx->r29, 0X4B);
    // 0x801E94F4: lbu         $t8, 0x47($sp)
    ctx->r24 = MEM_BU(ctx->r29, 0X47);
    // 0x801E94F8: addiu       $t3, $a1, -0x1
    ctx->r11 = ADD32(ctx->r5, -0X1);
    // 0x801E94FC: sltiu       $at, $t3, 0xA
    ctx->r1 = ctx->r11 < 0XA ? 1 : 0;
    // 0x801E9500: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x801E9504: or          $t1, $a1, $zero
    ctx->r9 = ctx->r5 | 0;
    // 0x801E9508: sw          $t4, 0x4($t0)
    MEM_W(0X4, ctx->r8) = ctx->r12;
    // 0x801E950C: sw          $t6, 0x8($v1)
    MEM_W(0X8, ctx->r3) = ctx->r14;
    // 0x801E9510: sw          $t7, 0x8($t0)
    MEM_W(0X8, ctx->r8) = ctx->r15;
    // 0x801E9514: sw          $t5, 0x8($v0)
    MEM_W(0X8, ctx->r2) = ctx->r13;
    // 0x801E9518: sw          $t2, 0xC($t0)
    MEM_W(0XC, ctx->r8) = ctx->r10;
    // 0x801E951C: sw          $t9, 0xC($v1)
    MEM_W(0XC, ctx->r3) = ctx->r25;
    // 0x801E9520: beq         $at, $zero, L_801E9828
    if (ctx->r1 == 0) {
        // 0x801E9524: sw          $t8, 0xC($v0)
        MEM_W(0XC, ctx->r2) = ctx->r24;
            goto L_801E9828;
    }
    // 0x801E9524: sw          $t8, 0xC($v0)
    MEM_W(0XC, ctx->r2) = ctx->r24;
    // 0x801E9528: sll         $t3, $t3, 2
    ctx->r11 = S32(ctx->r11 << 2);
    // 0x801E952C: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E9530: addu        $at, $at, $t3
    gpr jr_addend_801E9538 = ctx->r11;
    ctx->r1 = ADD32(ctx->r1, ctx->r11);
    // 0x801E9534: lw          $t3, 0x6E84($at)
    ctx->r11 = ADD32(ctx->r1, 0X6E84);
    // 0x801E9538: jr          $t3
    // 0x801E953C: nop

    switch (jr_addend_801E9538 >> 2) {
        case 0: goto L_801E9540; break;
        case 1: goto L_801E95B4; break;
        case 2: goto L_801E9614; break;
        case 3: goto L_801E9614; break;
        case 4: goto L_801E9614; break;
        case 5: goto L_801E9614; break;
        case 6: goto L_801E9754; break;
        case 7: goto L_801E9614; break;
        case 8: goto L_801E9614; break;
        case 9: goto L_801E97C8; break;
        default: switch_error(__func__, 0x801E9538, 0x80226E84);
    }
    // 0x801E953C: nop

L_801E9540:
    // 0x801E9540: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x801E9544: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x801E9548: lui         $t5, 0x107
    ctx->r13 = S32(0X107 << 16);
    // 0x801E954C: addiu       $t5, $t5, -0xFD0
    ctx->r13 = ADD32(ctx->r13, -0XFD0);
    // 0x801E9550: lui         $t4, 0x600
    ctx->r12 = S32(0X600 << 16);
    // 0x801E9554: or          $v1, $a0, $zero
    ctx->r3 = ctx->r4 | 0;
    // 0x801E9558: sw          $t4, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r12;
    // 0x801E955C: sw          $t5, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r13;
    // 0x801E9560: lui         $t6, 0xFCFF
    ctx->r14 = S32(0XFCFF << 16);
    // 0x801E9564: lui         $t7, 0xFFFD
    ctx->r15 = S32(0XFFFD << 16);
    // 0x801E9568: ori         $t7, $t7, 0xF2F9
    ctx->r15 = ctx->r15 | 0XF2F9;
    // 0x801E956C: ori         $t6, $t6, 0xFFFF
    ctx->r14 = ctx->r14 | 0XFFFF;
    // 0x801E9570: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x801E9574: sw          $t6, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r14;
    // 0x801E9578: sw          $t7, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r15;
    // 0x801E957C: or          $a1, $a0, $zero
    ctx->r5 = ctx->r4 | 0;
    // 0x801E9580: lui         $t8, 0xFA00
    ctx->r24 = S32(0XFA00 << 16);
    // 0x801E9584: sw          $t8, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r24;
    // 0x801E9588: lbu         $t7, 0x2B($sp)
    ctx->r15 = MEM_BU(ctx->r29, 0X2B);
    // 0x801E958C: andi        $t3, $a3, 0xFF
    ctx->r11 = ctx->r7 & 0XFF;
    // 0x801E9590: sll         $t4, $t3, 16
    ctx->r12 = S32(ctx->r11 << 16);
    // 0x801E9594: sll         $t2, $a2, 24
    ctx->r10 = S32(ctx->r6 << 24);
    // 0x801E9598: or          $t5, $t2, $t4
    ctx->r13 = ctx->r10 | ctx->r12;
    // 0x801E959C: sll         $t8, $t7, 8
    ctx->r24 = S32(ctx->r15 << 8);
    // 0x801E95A0: or          $t9, $t5, $t8
    ctx->r25 = ctx->r13 | ctx->r24;
    // 0x801E95A4: ori         $t3, $t9, 0xFF
    ctx->r11 = ctx->r25 | 0XFF;
    // 0x801E95A8: sw          $t3, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r11;
    // 0x801E95AC: b           L_801E9844
    // 0x801E95B0: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
        goto L_801E9844;
    // 0x801E95B0: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
L_801E95B4:
    // 0x801E95B4: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x801E95B8: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x801E95BC: lui         $t4, 0x107
    ctx->r12 = S32(0X107 << 16);
    // 0x801E95C0: addiu       $t4, $t4, -0xF58
    ctx->r12 = ADD32(ctx->r12, -0XF58);
    // 0x801E95C4: lui         $t2, 0x600
    ctx->r10 = S32(0X600 << 16);
    // 0x801E95C8: or          $v1, $a0, $zero
    ctx->r3 = ctx->r4 | 0;
    // 0x801E95CC: sw          $t2, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r10;
    // 0x801E95D0: sw          $t4, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r12;
    // 0x801E95D4: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x801E95D8: lui         $t6, 0x103
    ctx->r14 = S32(0X103 << 16);
    // 0x801E95DC: lui         $t7, 0x700
    ctx->r15 = S32(0X700 << 16);
    // 0x801E95E0: addiu       $t7, $t7, 0x0
    ctx->r15 = ADD32(ctx->r15, 0X0);
    // 0x801E95E4: ori         $t6, $t6, 0x40
    ctx->r14 = ctx->r14 | 0X40;
    // 0x801E95E8: or          $a1, $a0, $zero
    ctx->r5 = ctx->r4 | 0;
    // 0x801E95EC: lui         $t5, 0x102
    ctx->r13 = S32(0X102 << 16);
    // 0x801E95F0: lui         $t8, 0x200
    ctx->r24 = S32(0X200 << 16);
    // 0x801E95F4: sw          $t6, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r14;
    // 0x801E95F8: sw          $t7, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r15;
    // 0x801E95FC: addiu       $t8, $t8, 0xA40
    ctx->r24 = ADD32(ctx->r24, 0XA40);
    // 0x801E9600: ori         $t5, $t5, 0x40
    ctx->r13 = ctx->r13 | 0X40;
    // 0x801E9604: sw          $t5, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r13;
    // 0x801E9608: sw          $t8, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r24;
    // 0x801E960C: b           L_801E9844
    // 0x801E9610: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
        goto L_801E9844;
    // 0x801E9610: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
L_801E9614:
    // 0x801E9614: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x801E9618: lui         $t3, 0x107
    ctx->r11 = S32(0X107 << 16);
    // 0x801E961C: addiu       $t3, $t3, -0xFD0
    ctx->r11 = ADD32(ctx->r11, -0XFD0);
    // 0x801E9620: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x801E9624: lui         $t9, 0x600
    ctx->r25 = S32(0X600 << 16);
    // 0x801E9628: sw          $t9, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r25;
    // 0x801E962C: sw          $t3, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r11;
    // 0x801E9630: or          $v1, $a0, $zero
    ctx->r3 = ctx->r4 | 0;
    // 0x801E9634: lui         $t2, 0xFC11
    ctx->r10 = S32(0XFC11 << 16);
    // 0x801E9638: lui         $t4, 0xFF2F
    ctx->r12 = S32(0XFF2F << 16);
    // 0x801E963C: lui         $a1, 0x8023
    ctx->r5 = S32(0X8023 << 16);
    // 0x801E9640: ori         $t4, $t4, 0xFFFF
    ctx->r12 = ctx->r12 | 0XFFFF;
    // 0x801E9644: ori         $t2, $t2, 0x9623
    ctx->r10 = ctx->r10 | 0X9623;
    // 0x801E9648: addiu       $t7, $t1, -0x3
    ctx->r15 = ADD32(ctx->r9, -0X3);
    // 0x801E964C: addiu       $a1, $a1, -0x7588
    ctx->r5 = ADD32(ctx->r5, -0X7588);
    // 0x801E9650: sw          $t2, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r10;
    // 0x801E9654: sw          $t4, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r12;
    // 0x801E9658: addiu       $t6, $zero, 0x1
    ctx->r14 = ADD32(0, 0X1);
    // 0x801E965C: sltiu       $at, $t7, 0x7
    ctx->r1 = ctx->r15 < 0X7 ? 1 : 0;
    // 0x801E9660: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x801E9664: beq         $at, $zero, L_801E9710
    if (ctx->r1 == 0) {
        // 0x801E9668: sh          $t6, 0x0($a1)
        MEM_H(0X0, ctx->r5) = ctx->r14;
            goto L_801E9710;
    }
    // 0x801E9668: sh          $t6, 0x0($a1)
    MEM_H(0X0, ctx->r5) = ctx->r14;
    // 0x801E966C: sll         $t7, $t7, 2
    ctx->r15 = S32(ctx->r15 << 2);
    // 0x801E9670: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E9674: addu        $at, $at, $t7
    gpr jr_addend_801E967C = ctx->r15;
    ctx->r1 = ADD32(ctx->r1, ctx->r15);
    // 0x801E9678: lw          $t7, 0x6EAC($at)
    ctx->r15 = ADD32(ctx->r1, 0X6EAC);
    // 0x801E967C: jr          $t7
    // 0x801E9680: nop

    switch (jr_addend_801E967C >> 2) {
        case 0: goto L_801E9684; break;
        case 1: goto L_801E969C; break;
        case 2: goto L_801E96B4; break;
        case 3: goto L_801E96CC; break;
        case 4: goto L_801E9710; break;
        case 5: goto L_801E96E4; break;
        case 6: goto L_801E96FC; break;
        default: switch_error(__func__, 0x801E967C, 0x80226EAC);
    }
    // 0x801E9680: nop

L_801E9684:
    // 0x801E9684: jal         0x801E9D6C
    // 0x801E9688: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    func_801E9D6C(rdram, ctx);
        goto after_0;
    // 0x801E9688: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    after_0:
    // 0x801E968C: lui         $a1, 0x8023
    ctx->r5 = S32(0X8023 << 16);
    // 0x801E9690: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
    // 0x801E9694: b           L_801E9710
    // 0x801E9698: addiu       $a1, $a1, -0x7588
    ctx->r5 = ADD32(ctx->r5, -0X7588);
        goto L_801E9710;
    // 0x801E9698: addiu       $a1, $a1, -0x7588
    ctx->r5 = ADD32(ctx->r5, -0X7588);
L_801E969C:
    // 0x801E969C: jal         0x801EA0B0
    // 0x801E96A0: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    func_801EA0B0(rdram, ctx);
        goto after_1;
    // 0x801E96A0: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    after_1:
    // 0x801E96A4: lui         $a1, 0x8023
    ctx->r5 = S32(0X8023 << 16);
    // 0x801E96A8: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
    // 0x801E96AC: b           L_801E9710
    // 0x801E96B0: addiu       $a1, $a1, -0x7588
    ctx->r5 = ADD32(ctx->r5, -0X7588);
        goto L_801E9710;
    // 0x801E96B0: addiu       $a1, $a1, -0x7588
    ctx->r5 = ADD32(ctx->r5, -0X7588);
L_801E96B4:
    // 0x801E96B4: jal         0x801EA3EC
    // 0x801E96B8: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    func_801EA3EC(rdram, ctx);
        goto after_2;
    // 0x801E96B8: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    after_2:
    // 0x801E96BC: lui         $a1, 0x8023
    ctx->r5 = S32(0X8023 << 16);
    // 0x801E96C0: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
    // 0x801E96C4: b           L_801E9710
    // 0x801E96C8: addiu       $a1, $a1, -0x7588
    ctx->r5 = ADD32(ctx->r5, -0X7588);
        goto L_801E9710;
    // 0x801E96C8: addiu       $a1, $a1, -0x7588
    ctx->r5 = ADD32(ctx->r5, -0X7588);
L_801E96CC:
    // 0x801E96CC: jal         0x801EA730
    // 0x801E96D0: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    func_801EA730(rdram, ctx);
        goto after_3;
    // 0x801E96D0: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    after_3:
    // 0x801E96D4: lui         $a1, 0x8023
    ctx->r5 = S32(0X8023 << 16);
    // 0x801E96D8: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
    // 0x801E96DC: b           L_801E9710
    // 0x801E96E0: addiu       $a1, $a1, -0x7588
    ctx->r5 = ADD32(ctx->r5, -0X7588);
        goto L_801E9710;
    // 0x801E96E0: addiu       $a1, $a1, -0x7588
    ctx->r5 = ADD32(ctx->r5, -0X7588);
L_801E96E4:
    // 0x801E96E4: jal         0x801EAA6C
    // 0x801E96E8: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    func_801EAA6C(rdram, ctx);
        goto after_4;
    // 0x801E96E8: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    after_4:
    // 0x801E96EC: lui         $a1, 0x8023
    ctx->r5 = S32(0X8023 << 16);
    // 0x801E96F0: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
    // 0x801E96F4: b           L_801E9710
    // 0x801E96F8: addiu       $a1, $a1, -0x7588
    ctx->r5 = ADD32(ctx->r5, -0X7588);
        goto L_801E9710;
    // 0x801E96F8: addiu       $a1, $a1, -0x7588
    ctx->r5 = ADD32(ctx->r5, -0X7588);
L_801E96FC:
    // 0x801E96FC: jal         0x801EADB0
    // 0x801E9700: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    func_801EADB0(rdram, ctx);
        goto after_5;
    // 0x801E9700: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    after_5:
    // 0x801E9704: lui         $a1, 0x8023
    ctx->r5 = S32(0X8023 << 16);
    // 0x801E9708: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
    // 0x801E970C: addiu       $a1, $a1, -0x7588
    ctx->r5 = ADD32(ctx->r5, -0X7588);
L_801E9710:
    // 0x801E9710: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x801E9714: lui         $t5, 0xFA00
    ctx->r13 = S32(0XFA00 << 16);
    // 0x801E9718: sw          $t5, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r13;
    // 0x801E971C: lh          $t2, 0xE($a1)
    ctx->r10 = MEM_H(ctx->r5, 0XE);
    // 0x801E9720: lh          $t9, 0xC($a1)
    ctx->r25 = MEM_H(ctx->r5, 0XC);
    // 0x801E9724: lh          $t5, 0x10($a1)
    ctx->r13 = MEM_H(ctx->r5, 0X10);
    // 0x801E9728: andi        $t4, $t2, 0xFF
    ctx->r12 = ctx->r10 & 0XFF;
    // 0x801E972C: sll         $t3, $t9, 24
    ctx->r11 = S32(ctx->r25 << 24);
    // 0x801E9730: sll         $t6, $t4, 16
    ctx->r14 = S32(ctx->r12 << 16);
    // 0x801E9734: andi        $t8, $t5, 0xFF
    ctx->r24 = ctx->r13 & 0XFF;
    // 0x801E9738: sll         $t9, $t8, 8
    ctx->r25 = S32(ctx->r24 << 8);
    // 0x801E973C: or          $t7, $t3, $t6
    ctx->r15 = ctx->r11 | ctx->r14;
    // 0x801E9740: or          $t2, $t7, $t9
    ctx->r10 = ctx->r15 | ctx->r25;
    // 0x801E9744: ori         $t4, $t2, 0xFF
    ctx->r12 = ctx->r10 | 0XFF;
    // 0x801E9748: sw          $t4, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r12;
    // 0x801E974C: b           L_801E9844
    // 0x801E9750: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
        goto L_801E9844;
    // 0x801E9750: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
L_801E9754:
    // 0x801E9754: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x801E9758: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x801E975C: lui         $t6, 0x107
    ctx->r14 = S32(0X107 << 16);
    // 0x801E9760: addiu       $t6, $t6, -0xFD0
    ctx->r14 = ADD32(ctx->r14, -0XFD0);
    // 0x801E9764: lui         $t3, 0x600
    ctx->r11 = S32(0X600 << 16);
    // 0x801E9768: or          $v1, $a0, $zero
    ctx->r3 = ctx->r4 | 0;
    // 0x801E976C: sw          $t3, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r11;
    // 0x801E9770: sw          $t6, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r14;
    // 0x801E9774: lui         $t5, 0xFC11
    ctx->r13 = S32(0XFC11 << 16);
    // 0x801E9778: lui         $t8, 0xFF2F
    ctx->r24 = S32(0XFF2F << 16);
    // 0x801E977C: ori         $t8, $t8, 0xFFFF
    ctx->r24 = ctx->r24 | 0XFFFF;
    // 0x801E9780: ori         $t5, $t5, 0x9623
    ctx->r13 = ctx->r13 | 0X9623;
    // 0x801E9784: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x801E9788: sw          $t5, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r13;
    // 0x801E978C: sw          $t8, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r24;
    // 0x801E9790: or          $a1, $a0, $zero
    ctx->r5 = ctx->r4 | 0;
    // 0x801E9794: lui         $t7, 0xFA00
    ctx->r15 = S32(0XFA00 << 16);
    // 0x801E9798: sw          $t7, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r15;
    // 0x801E979C: lbu         $t8, 0x2B($sp)
    ctx->r24 = MEM_BU(ctx->r29, 0X2B);
    // 0x801E97A0: andi        $t4, $a3, 0xFF
    ctx->r12 = ctx->r7 & 0XFF;
    // 0x801E97A4: sll         $t3, $t4, 16
    ctx->r11 = S32(ctx->r12 << 16);
    // 0x801E97A8: sll         $t2, $a2, 24
    ctx->r10 = S32(ctx->r6 << 24);
    // 0x801E97AC: or          $t6, $t2, $t3
    ctx->r14 = ctx->r10 | ctx->r11;
    // 0x801E97B0: sll         $t7, $t8, 8
    ctx->r15 = S32(ctx->r24 << 8);
    // 0x801E97B4: or          $t9, $t6, $t7
    ctx->r25 = ctx->r14 | ctx->r15;
    // 0x801E97B8: ori         $t4, $t9, 0xFF
    ctx->r12 = ctx->r25 | 0XFF;
    // 0x801E97BC: sw          $t4, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r12;
    // 0x801E97C0: b           L_801E9844
    // 0x801E97C4: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
        goto L_801E9844;
    // 0x801E97C4: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
L_801E97C8:
    // 0x801E97C8: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x801E97CC: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x801E97D0: lui         $t3, 0x107
    ctx->r11 = S32(0X107 << 16);
    // 0x801E97D4: addiu       $t3, $t3, -0xFD0
    ctx->r11 = ADD32(ctx->r11, -0XFD0);
    // 0x801E97D8: lui         $t2, 0x600
    ctx->r10 = S32(0X600 << 16);
    // 0x801E97DC: or          $v1, $a0, $zero
    ctx->r3 = ctx->r4 | 0;
    // 0x801E97E0: sw          $t2, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r10;
    // 0x801E97E4: sw          $t3, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r11;
    // 0x801E97E8: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x801E97EC: lui         $t5, 0xFC11
    ctx->r13 = S32(0XFC11 << 16);
    // 0x801E97F0: lui         $t8, 0xFF2F
    ctx->r24 = S32(0XFF2F << 16);
    // 0x801E97F4: ori         $t8, $t8, 0xFFFF
    ctx->r24 = ctx->r24 | 0XFFFF;
    // 0x801E97F8: ori         $t5, $t5, 0x9623
    ctx->r13 = ctx->r13 | 0X9623;
    // 0x801E97FC: or          $a1, $a0, $zero
    ctx->r5 = ctx->r4 | 0;
    // 0x801E9800: andi        $t7, $a2, 0xFF
    ctx->r15 = ctx->r6 & 0XFF;
    // 0x801E9804: addiu       $at, $zero, -0x100
    ctx->r1 = ADD32(0, -0X100);
    // 0x801E9808: sw          $t5, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r13;
    // 0x801E980C: sw          $t8, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r24;
    // 0x801E9810: or          $t9, $t7, $at
    ctx->r25 = ctx->r15 | ctx->r1;
    // 0x801E9814: lui         $t6, 0xFA00
    ctx->r14 = S32(0XFA00 << 16);
    // 0x801E9818: sw          $t6, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r14;
    // 0x801E981C: sw          $t9, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r25;
    // 0x801E9820: b           L_801E9844
    // 0x801E9824: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
        goto L_801E9844;
    // 0x801E9824: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
L_801E9828:
    // 0x801E9828: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x801E982C: lui         $t2, 0x107
    ctx->r10 = S32(0X107 << 16);
    // 0x801E9830: addiu       $t2, $t2, -0xFD0
    ctx->r10 = ADD32(ctx->r10, -0XFD0);
    // 0x801E9834: lui         $t4, 0x600
    ctx->r12 = S32(0X600 << 16);
    // 0x801E9838: sw          $t4, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r12;
    // 0x801E983C: sw          $t2, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r10;
    // 0x801E9840: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
L_801E9844:
    // 0x801E9844: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x801E9848: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x801E984C: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x801E9850: jr          $ra
    // 0x801E9854: nop

    return;
    // 0x801E9854: nop

;}
RECOMP_FUNC void func_801E9858(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801E9858: addiu       $sp, $sp, -0xA0
    ctx->r29 = ADD32(ctx->r29, -0XA0);
    // 0x801E985C: sw          $s6, 0x78($sp)
    MEM_W(0X78, ctx->r29) = ctx->r22;
    // 0x801E9860: sw          $s5, 0x74($sp)
    MEM_W(0X74, ctx->r29) = ctx->r21;
    // 0x801E9864: sw          $s4, 0x70($sp)
    MEM_W(0X70, ctx->r29) = ctx->r20;
    // 0x801E9868: sdc1        $f20, 0x58($sp)
    CHECK_FR(ctx, 20);
    SD(ctx->f20.u64, 0X58, ctx->r29);
    // 0x801E986C: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x801E9870: sw          $fp, 0x80($sp)
    MEM_W(0X80, ctx->r29) = ctx->r30;
    // 0x801E9874: sw          $s7, 0x7C($sp)
    MEM_W(0X7C, ctx->r29) = ctx->r23;
    // 0x801E9878: sw          $s2, 0x68($sp)
    MEM_W(0X68, ctx->r29) = ctx->r18;
    // 0x801E987C: sw          $s1, 0x64($sp)
    MEM_W(0X64, ctx->r29) = ctx->r17;
    // 0x801E9880: sw          $s0, 0x60($sp)
    MEM_W(0X60, ctx->r29) = ctx->r16;
    // 0x801E9884: lui         $s4, 0x8023
    ctx->r20 = S32(0X8023 << 16);
    // 0x801E9888: lui         $s5, 0x8023
    ctx->r21 = S32(0X8023 << 16);
    // 0x801E988C: lui         $s6, 0x8023
    ctx->r22 = S32(0X8023 << 16);
    // 0x801E9890: mtc1        $at, $f20
    ctx->f20.u32l = ctx->r1;
    // 0x801E9894: or          $fp, $a1, $zero
    ctx->r30 = ctx->r5 | 0;
    // 0x801E9898: sw          $ra, 0x84($sp)
    MEM_W(0X84, ctx->r29) = ctx->r31;
    // 0x801E989C: sw          $s3, 0x6C($sp)
    MEM_W(0X6C, ctx->r29) = ctx->r19;
    // 0x801E98A0: sw          $a0, 0xA0($sp)
    MEM_W(0XA0, ctx->r29) = ctx->r4;
    // 0x801E98A4: or          $s7, $a2, $zero
    ctx->r23 = ctx->r6 | 0;
    // 0x801E98A8: or          $s0, $a3, $zero
    ctx->r16 = ctx->r7 | 0;
    // 0x801E98AC: addiu       $s6, $s6, -0x7598
    ctx->r22 = ADD32(ctx->r22, -0X7598);
    // 0x801E98B0: addiu       $s5, $s5, -0x75A8
    ctx->r21 = ADD32(ctx->r21, -0X75A8);
    // 0x801E98B4: addiu       $s4, $s4, -0x75B8
    ctx->r20 = ADD32(ctx->r20, -0X75B8);
    // 0x801E98B8: lw          $s1, 0x88($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X88);
    // 0x801E98BC: lw          $s2, 0x8C($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X8C);
L_801E98C0:
    // 0x801E98C0: lb          $a1, 0x0($s7)
    ctx->r5 = MEM_B(ctx->r23, 0X0);
L_801E98C4:
    // 0x801E98C4: or          $a0, $fp, $zero
    ctx->r4 = ctx->r30 | 0;
    // 0x801E98C8: beql        $a1, $zero, L_801E9AD0
    if (ctx->r5 == 0) {
        // 0x801E98CC: lw          $ra, 0x84($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X84);
            goto L_801E9AD0;
    }
    goto skip_0;
    // 0x801E98CC: lw          $ra, 0x84($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X84);
    skip_0:
    // 0x801E98D0: jal         0x801E9B04
    // 0x801E98D4: or          $s3, $fp, $zero
    ctx->r19 = ctx->r30 | 0;
    func_801E9B04(rdram, ctx);
        goto after_0;
    // 0x801E98D4: or          $s3, $fp, $zero
    ctx->r19 = ctx->r30 | 0;
    after_0:
    // 0x801E98D8: lui         $v1, 0x8022
    ctx->r3 = S32(0X8022 << 16);
    // 0x801E98DC: lui         $t0, 0x8022
    ctx->r8 = S32(0X8022 << 16);
    // 0x801E98E0: sltiu       $at, $s3, 0x7
    ctx->r1 = ctx->r19 < 0X7 ? 1 : 0;
    // 0x801E98E4: addiu       $t0, $t0, 0x6E24
    ctx->r8 = ADD32(ctx->r8, 0X6E24);
    // 0x801E98E8: addiu       $v1, $v1, 0x6E28
    ctx->r3 = ADD32(ctx->r3, 0X6E28);
    // 0x801E98EC: beq         $at, $zero, L_801E9994
    if (ctx->r1 == 0) {
        // 0x801E98F0: or          $a2, $v0, $zero
        ctx->r6 = ctx->r2 | 0;
            goto L_801E9994;
    }
    // 0x801E98F0: or          $a2, $v0, $zero
    ctx->r6 = ctx->r2 | 0;
    // 0x801E98F4: sll         $t6, $s3, 2
    ctx->r14 = S32(ctx->r19 << 2);
    // 0x801E98F8: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E98FC: addu        $at, $at, $t6
    gpr jr_addend_801E9904 = ctx->r14;
    ctx->r1 = ADD32(ctx->r1, ctx->r14);
    // 0x801E9900: lw          $t6, 0x6EC8($at)
    ctx->r14 = ADD32(ctx->r1, 0X6EC8);
    // 0x801E9904: jr          $t6
    // 0x801E9908: nop

    switch (jr_addend_801E9904 >> 2) {
        case 0: goto L_801E990C; break;
        case 1: goto L_801E9920; break;
        case 2: goto L_801E9934; break;
        case 3: goto L_801E9948; break;
        case 4: goto L_801E995C; break;
        case 5: goto L_801E9970; break;
        case 6: goto L_801E9984; break;
        default: switch_error(__func__, 0x801E9904, 0x80226EC8);
    }
    // 0x801E9908: nop

L_801E990C:
    // 0x801E990C: lui         $s1, 0x8022
    ctx->r17 = S32(0X8022 << 16);
    // 0x801E9910: addu        $s1, $s1, $v0
    ctx->r17 = ADD32(ctx->r17, ctx->r2);
    // 0x801E9914: lbu         $s1, 0x6D70($s1)
    ctx->r17 = MEM_BU(ctx->r17, 0X6D70);
    // 0x801E9918: b           L_801E9994
    // 0x801E991C: addiu       $s2, $zero, 0x18
    ctx->r18 = ADD32(0, 0X18);
        goto L_801E9994;
    // 0x801E991C: addiu       $s2, $zero, 0x18
    ctx->r18 = ADD32(0, 0X18);
L_801E9920:
    // 0x801E9920: lui         $s1, 0x8022
    ctx->r17 = S32(0X8022 << 16);
    // 0x801E9924: addu        $s1, $s1, $v0
    ctx->r17 = ADD32(ctx->r17, ctx->r2);
    // 0x801E9928: lbu         $s1, 0x6D98($s1)
    ctx->r17 = MEM_BU(ctx->r17, 0X6D98);
    // 0x801E992C: b           L_801E9994
    // 0x801E9930: addiu       $s2, $zero, 0x8
    ctx->r18 = ADD32(0, 0X8);
        goto L_801E9994;
    // 0x801E9930: addiu       $s2, $zero, 0x8
    ctx->r18 = ADD32(0, 0X8);
L_801E9934:
    // 0x801E9934: lui         $s1, 0x8022
    ctx->r17 = S32(0X8022 << 16);
    // 0x801E9938: addu        $s1, $s1, $v0
    ctx->r17 = ADD32(ctx->r17, ctx->r2);
    // 0x801E993C: lbu         $s1, 0x6DC4($s1)
    ctx->r17 = MEM_BU(ctx->r17, 0X6DC4);
    // 0x801E9940: b           L_801E9994
    // 0x801E9944: addiu       $s2, $zero, 0xC
    ctx->r18 = ADD32(0, 0XC);
        goto L_801E9994;
    // 0x801E9944: addiu       $s2, $zero, 0xC
    ctx->r18 = ADD32(0, 0XC);
L_801E9948:
    // 0x801E9948: lui         $s1, 0x8022
    ctx->r17 = S32(0X8022 << 16);
    // 0x801E994C: addu        $s1, $s1, $v0
    ctx->r17 = ADD32(ctx->r17, ctx->r2);
    // 0x801E9950: lbu         $s1, 0x6DF4($s1)
    ctx->r17 = MEM_BU(ctx->r17, 0X6DF4);
    // 0x801E9954: b           L_801E9994
    // 0x801E9958: addiu       $s2, $zero, 0xC
    ctx->r18 = ADD32(0, 0XC);
        goto L_801E9994;
    // 0x801E9958: addiu       $s2, $zero, 0xC
    ctx->r18 = ADD32(0, 0XC);
L_801E995C:
    // 0x801E995C: lui         $s1, 0x8022
    ctx->r17 = S32(0X8022 << 16);
    // 0x801E9960: addu        $s1, $s1, $v0
    ctx->r17 = ADD32(ctx->r17, ctx->r2);
    // 0x801E9964: lbu         $s1, 0x6E00($s1)
    ctx->r17 = MEM_BU(ctx->r17, 0X6E00);
    // 0x801E9968: b           L_801E9994
    // 0x801E996C: addiu       $s2, $zero, 0xC
    ctx->r18 = ADD32(0, 0XC);
        goto L_801E9994;
    // 0x801E996C: addiu       $s2, $zero, 0xC
    ctx->r18 = ADD32(0, 0XC);
L_801E9970:
    // 0x801E9970: lui         $s1, 0x8022
    ctx->r17 = S32(0X8022 << 16);
    // 0x801E9974: addu        $s1, $s1, $v0
    ctx->r17 = ADD32(ctx->r17, ctx->r2);
    // 0x801E9978: lbu         $s1, 0x6E0C($s1)
    ctx->r17 = MEM_BU(ctx->r17, 0X6E0C);
    // 0x801E997C: b           L_801E9994
    // 0x801E9980: addiu       $s2, $zero, 0x10
    ctx->r18 = ADD32(0, 0X10);
        goto L_801E9994;
    // 0x801E9980: addiu       $s2, $zero, 0x10
    ctx->r18 = ADD32(0, 0X10);
L_801E9984:
    // 0x801E9984: lui         $s1, 0x8022
    ctx->r17 = S32(0X8022 << 16);
    // 0x801E9988: addu        $s1, $s1, $v0
    ctx->r17 = ADD32(ctx->r17, ctx->r2);
    // 0x801E998C: lbu         $s1, 0x6E18($s1)
    ctx->r17 = MEM_BU(ctx->r17, 0X6E18);
    // 0x801E9990: addiu       $s2, $zero, 0x28
    ctx->r18 = ADD32(0, 0X28);
L_801E9994:
    // 0x801E9994: addiu       $at, $zero, 0xFF
    ctx->r1 = ADD32(0, 0XFF);
    // 0x801E9998: bne         $v0, $at, L_801E99E8
    if (ctx->r2 != ctx->r1) {
        // 0x801E999C: lw          $a0, 0xA0($sp)
        ctx->r4 = MEM_W(ctx->r29, 0XA0);
            goto L_801E99E8;
    }
    // 0x801E999C: lw          $a0, 0xA0($sp)
    ctx->r4 = MEM_W(ctx->r29, 0XA0);
    // 0x801E99A0: lh          $t7, 0x0($v1)
    ctx->r15 = MEM_H(ctx->r3, 0X0);
    // 0x801E99A4: beql        $t7, $zero, L_801E99E0
    if (ctx->r15 == 0) {
        // 0x801E99A8: addu        $s0, $s0, $s2
        ctx->r16 = ADD32(ctx->r16, ctx->r18);
            goto L_801E99E0;
    }
    goto skip_1;
    // 0x801E99A8: addu        $s0, $s0, $s2
    ctx->r16 = ADD32(ctx->r16, ctx->r18);
    skip_1:
    // 0x801E99AC: mtc1        $s2, $f4
    ctx->f4.u32l = ctx->r18;
    // 0x801E99B0: lwc1        $f8, 0x0($t0)
    ctx->f8.u32l = MEM_W(ctx->r8, 0X0);
    // 0x801E99B4: mtc1        $s0, $f16
    ctx->f16.u32l = ctx->r16;
    // 0x801E99B8: cvt.s.w     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
    // 0x801E99BC: addiu       $s7, $s7, 0x1
    ctx->r23 = ADD32(ctx->r23, 0X1);
    // 0x801E99C0: cvt.s.w     $f18, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    ctx->f18.fl = CVT_S_W(ctx->f16.u32l);
    // 0x801E99C4: mul.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = MUL_S(ctx->f6.fl, ctx->f8.fl);
    // 0x801E99C8: add.s       $f4, $f18, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f4.fl = ctx->f18.fl + ctx->f10.fl;
    // 0x801E99CC: trunc.w.s   $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.u32l = TRUNC_W_S(ctx->f4.fl);
    // 0x801E99D0: mfc1        $s0, $f6
    ctx->r16 = (int32_t)ctx->f6.u32l;
    // 0x801E99D4: b           L_801E98C4
    // 0x801E99D8: lb          $a1, 0x0($s7)
    ctx->r5 = MEM_B(ctx->r23, 0X0);
        goto L_801E98C4;
    // 0x801E99D8: lb          $a1, 0x0($s7)
    ctx->r5 = MEM_B(ctx->r23, 0X0);
    // 0x801E99DC: addu        $s0, $s0, $s2
    ctx->r16 = ADD32(ctx->r16, ctx->r18);
L_801E99E0:
    // 0x801E99E0: b           L_801E98C0
    // 0x801E99E4: addiu       $s7, $s7, 0x1
    ctx->r23 = ADD32(ctx->r23, 0X1);
        goto L_801E98C0;
    // 0x801E99E4: addiu       $s7, $s7, 0x1
    ctx->r23 = ADD32(ctx->r23, 0X1);
L_801E99E8:
    // 0x801E99E8: lh          $t9, 0x0($v1)
    ctx->r25 = MEM_H(ctx->r3, 0X0);
    // 0x801E99EC: or          $a1, $fp, $zero
    ctx->r5 = ctx->r30 | 0;
    // 0x801E99F0: or          $a3, $s0, $zero
    ctx->r7 = ctx->r16 | 0;
    // 0x801E99F4: beq         $t9, $zero, L_801E9A04
    if (ctx->r25 == 0) {
        // 0x801E99F8: lw          $t1, 0xB0($sp)
        ctx->r9 = MEM_W(ctx->r29, 0XB0);
            goto L_801E9A04;
    }
    // 0x801E99F8: lw          $t1, 0xB0($sp)
    ctx->r9 = MEM_W(ctx->r29, 0XB0);
    // 0x801E99FC: b           L_801E9A08
    // 0x801E9A00: lwc1        $f0, 0x0($t0)
    ctx->f0.u32l = MEM_W(ctx->r8, 0X0);
        goto L_801E9A08;
    // 0x801E9A00: lwc1        $f0, 0x0($t0)
    ctx->f0.u32l = MEM_W(ctx->r8, 0X0);
L_801E9A04:
    // 0x801E9A04: mov.s       $f0, $f20
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 20);
    ctx->f0.fl = ctx->f20.fl;
L_801E9A08:
    // 0x801E9A08: lui         $t2, 0x8023
    ctx->r10 = S32(0X8023 << 16);
    // 0x801E9A0C: lw          $t2, -0x75BC($t2)
    ctx->r10 = MEM_W(ctx->r10, -0X75BC);
    // 0x801E9A10: lw          $t3, 0x0($s4)
    ctx->r11 = MEM_W(ctx->r20, 0X0);
    // 0x801E9A14: lw          $t4, 0x0($s5)
    ctx->r12 = MEM_W(ctx->r21, 0X0);
    // 0x801E9A18: lw          $t5, 0x0($s6)
    ctx->r13 = MEM_W(ctx->r22, 0X0);
    // 0x801E9A1C: sw          $t1, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r9;
    // 0x801E9A20: sw          $t2, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r10;
    // 0x801E9A24: sw          $t3, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r11;
    // 0x801E9A28: sw          $t4, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r12;
    // 0x801E9A2C: sw          $t5, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r13;
    // 0x801E9A30: lw          $t5, 0xC($s6)
    ctx->r13 = MEM_W(ctx->r22, 0XC);
    // 0x801E9A34: lw          $t4, 0xC($s5)
    ctx->r12 = MEM_W(ctx->r21, 0XC);
    // 0x801E9A38: lw          $t3, 0xC($s4)
    ctx->r11 = MEM_W(ctx->r20, 0XC);
    // 0x801E9A3C: lw          $t2, 0x8($s6)
    ctx->r10 = MEM_W(ctx->r22, 0X8);
    // 0x801E9A40: lw          $t1, 0x8($s5)
    ctx->r9 = MEM_W(ctx->r21, 0X8);
    // 0x801E9A44: lw          $t6, 0x4($s4)
    ctx->r14 = MEM_W(ctx->r20, 0X4);
    // 0x801E9A48: lw          $t7, 0x4($s5)
    ctx->r15 = MEM_W(ctx->r21, 0X4);
    // 0x801E9A4C: lw          $t8, 0x4($s6)
    ctx->r24 = MEM_W(ctx->r22, 0X4);
    // 0x801E9A50: lw          $t9, 0x8($s4)
    ctx->r25 = MEM_W(ctx->r20, 0X8);
    // 0x801E9A54: swc1        $f0, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->f0.u32l;
    // 0x801E9A58: sw          $t5, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r13;
    // 0x801E9A5C: sw          $t4, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r12;
    // 0x801E9A60: sw          $t3, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r11;
    // 0x801E9A64: sw          $t2, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r10;
    // 0x801E9A68: sw          $t1, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r9;
    // 0x801E9A6C: sw          $t6, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r14;
    // 0x801E9A70: sw          $t7, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r15;
    // 0x801E9A74: sw          $t8, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r24;
    // 0x801E9A78: jal         0x801E80B0
    // 0x801E9A7C: sw          $t9, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r25;
    func_801E80B0(rdram, ctx);
        goto after_1;
    // 0x801E9A7C: sw          $t9, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r25;
    after_1:
    // 0x801E9A80: lui         $v1, 0x8022
    ctx->r3 = S32(0X8022 << 16);
    // 0x801E9A84: addiu       $v1, $v1, 0x6E28
    ctx->r3 = ADD32(ctx->r3, 0X6E28);
    // 0x801E9A88: lh          $t6, 0x0($v1)
    ctx->r14 = MEM_H(ctx->r3, 0X0);
    // 0x801E9A8C: lui         $t0, 0x8022
    ctx->r8 = S32(0X8022 << 16);
    // 0x801E9A90: addiu       $t0, $t0, 0x6E24
    ctx->r8 = ADD32(ctx->r8, 0X6E24);
    // 0x801E9A94: beq         $t6, $zero, L_801E9AC0
    if (ctx->r14 == 0) {
        // 0x801E9A98: sw          $v0, 0xA0($sp)
        MEM_W(0XA0, ctx->r29) = ctx->r2;
            goto L_801E9AC0;
    }
    // 0x801E9A98: sw          $v0, 0xA0($sp)
    MEM_W(0XA0, ctx->r29) = ctx->r2;
    // 0x801E9A9C: mtc1        $s1, $f8
    ctx->f8.u32l = ctx->r17;
    // 0x801E9AA0: lwc1        $f18, 0x0($t0)
    ctx->f18.u32l = MEM_W(ctx->r8, 0X0);
    // 0x801E9AA4: addiu       $s7, $s7, 0x1
    ctx->r23 = ADD32(ctx->r23, 0X1);
    // 0x801E9AA8: cvt.s.w     $f16, $f8
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 8);
    ctx->f16.fl = CVT_S_W(ctx->f8.u32l);
    // 0x801E9AAC: mul.s       $f10, $f16, $f18
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f10.fl = MUL_S(ctx->f16.fl, ctx->f18.fl);
    // 0x801E9AB0: trunc.w.s   $f4, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    ctx->f4.u32l = TRUNC_W_S(ctx->f10.fl);
    // 0x801E9AB4: mfc1        $t8, $f4
    ctx->r24 = (int32_t)ctx->f4.u32l;
    // 0x801E9AB8: b           L_801E98C0
    // 0x801E9ABC: addu        $s0, $s0, $t8
    ctx->r16 = ADD32(ctx->r16, ctx->r24);
        goto L_801E98C0;
    // 0x801E9ABC: addu        $s0, $s0, $t8
    ctx->r16 = ADD32(ctx->r16, ctx->r24);
L_801E9AC0:
    // 0x801E9AC0: addu        $s0, $s0, $s1
    ctx->r16 = ADD32(ctx->r16, ctx->r17);
    // 0x801E9AC4: b           L_801E98C0
    // 0x801E9AC8: addiu       $s7, $s7, 0x1
    ctx->r23 = ADD32(ctx->r23, 0X1);
        goto L_801E98C0;
    // 0x801E9AC8: addiu       $s7, $s7, 0x1
    ctx->r23 = ADD32(ctx->r23, 0X1);
    // 0x801E9ACC: lw          $ra, 0x84($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X84);
L_801E9AD0:
    // 0x801E9AD0: lw          $v0, 0xA0($sp)
    ctx->r2 = MEM_W(ctx->r29, 0XA0);
    // 0x801E9AD4: ldc1        $f20, 0x58($sp)
    CHECK_FR(ctx, 20);
    ctx->f20.u64 = LD(ctx->r29, 0X58);
    // 0x801E9AD8: lw          $s0, 0x60($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X60);
    // 0x801E9ADC: lw          $s1, 0x64($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X64);
    // 0x801E9AE0: lw          $s2, 0x68($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X68);
    // 0x801E9AE4: lw          $s3, 0x6C($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X6C);
    // 0x801E9AE8: lw          $s4, 0x70($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X70);
    // 0x801E9AEC: lw          $s5, 0x74($sp)
    ctx->r21 = MEM_W(ctx->r29, 0X74);
    // 0x801E9AF0: lw          $s6, 0x78($sp)
    ctx->r22 = MEM_W(ctx->r29, 0X78);
    // 0x801E9AF4: lw          $s7, 0x7C($sp)
    ctx->r23 = MEM_W(ctx->r29, 0X7C);
    // 0x801E9AF8: lw          $fp, 0x80($sp)
    ctx->r30 = MEM_W(ctx->r29, 0X80);
    // 0x801E9AFC: jr          $ra
    // 0x801E9B00: addiu       $sp, $sp, 0xA0
    ctx->r29 = ADD32(ctx->r29, 0XA0);
    return;
    // 0x801E9B00: addiu       $sp, $sp, 0xA0
    ctx->r29 = ADD32(ctx->r29, 0XA0);
;}
RECOMP_FUNC void func_801E9B04(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801E9B04: sll         $t6, $a1, 24
    ctx->r14 = S32(ctx->r5 << 24);
    // 0x801E9B08: sra         $t7, $t6, 24
    ctx->r15 = S32(SIGNED(ctx->r14) >> 24);
    // 0x801E9B0C: sw          $a1, 0x4($sp)
    MEM_W(0X4, ctx->r29) = ctx->r5;
    // 0x801E9B10: slti        $at, $t7, 0x30
    ctx->r1 = SIGNED(ctx->r15) < 0X30 ? 1 : 0;
    // 0x801E9B14: or          $a1, $t7, $zero
    ctx->r5 = ctx->r15 | 0;
    // 0x801E9B18: bne         $at, $zero, L_801E9B34
    if (ctx->r1 != 0) {
        // 0x801E9B1C: or          $v1, $zero, $zero
        ctx->r3 = 0 | 0;
            goto L_801E9B34;
    }
    // 0x801E9B1C: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
    // 0x801E9B20: slti        $at, $t7, 0x3A
    ctx->r1 = SIGNED(ctx->r15) < 0X3A ? 1 : 0;
    // 0x801E9B24: beql        $at, $zero, L_801E9B38
    if (ctx->r1 == 0) {
        // 0x801E9B28: slti        $at, $a1, 0x41
        ctx->r1 = SIGNED(ctx->r5) < 0X41 ? 1 : 0;
            goto L_801E9B38;
    }
    goto skip_0;
    // 0x801E9B28: slti        $at, $a1, 0x41
    ctx->r1 = SIGNED(ctx->r5) < 0X41 ? 1 : 0;
    skip_0:
    // 0x801E9B2C: jr          $ra
    // 0x801E9B30: addiu       $v0, $t7, -0x30
    ctx->r2 = ADD32(ctx->r15, -0X30);
    return;
    // 0x801E9B30: addiu       $v0, $t7, -0x30
    ctx->r2 = ADD32(ctx->r15, -0X30);
L_801E9B34:
    // 0x801E9B34: slti        $at, $a1, 0x41
    ctx->r1 = SIGNED(ctx->r5) < 0X41 ? 1 : 0;
L_801E9B38:
    // 0x801E9B38: bne         $at, $zero, L_801E9B68
    if (ctx->r1 != 0) {
        // 0x801E9B3C: slti        $at, $a1, 0x5B
        ctx->r1 = SIGNED(ctx->r5) < 0X5B ? 1 : 0;
            goto L_801E9B68;
    }
    // 0x801E9B3C: slti        $at, $a1, 0x5B
    ctx->r1 = SIGNED(ctx->r5) < 0X5B ? 1 : 0;
    // 0x801E9B40: beql        $at, $zero, L_801E9B6C
    if (ctx->r1 == 0) {
        // 0x801E9B44: addiu       $at, $zero, 0x2F
        ctx->r1 = ADD32(0, 0X2F);
            goto L_801E9B6C;
    }
    goto skip_1;
    // 0x801E9B44: addiu       $at, $zero, 0x2F
    ctx->r1 = ADD32(0, 0X2F);
    skip_1:
    // 0x801E9B48: beq         $a0, $zero, L_801E9B60
    if (ctx->r4 == 0) {
        // 0x801E9B4C: addiu       $at, $zero, 0x1
        ctx->r1 = ADD32(0, 0X1);
            goto L_801E9B60;
    }
    // 0x801E9B4C: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x801E9B50: beq         $a0, $at, L_801E9B60
    if (ctx->r4 == ctx->r1) {
        // 0x801E9B54: addiu       $at, $zero, 0x2
        ctx->r1 = ADD32(0, 0X2);
            goto L_801E9B60;
    }
    // 0x801E9B54: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x801E9B58: bne         $a0, $at, L_801E9D64
    if (ctx->r4 != ctx->r1) {
        // 0x801E9B5C: nop
    
            goto L_801E9D64;
    }
    // 0x801E9B5C: nop

L_801E9B60:
    // 0x801E9B60: jr          $ra
    // 0x801E9B64: addiu       $v0, $a1, -0x37
    ctx->r2 = ADD32(ctx->r5, -0X37);
    return;
    // 0x801E9B64: addiu       $v0, $a1, -0x37
    ctx->r2 = ADD32(ctx->r5, -0X37);
L_801E9B68:
    // 0x801E9B68: addiu       $at, $zero, 0x2F
    ctx->r1 = ADD32(0, 0X2F);
L_801E9B6C:
    // 0x801E9B6C: bne         $a1, $at, L_801E9B94
    if (ctx->r5 != ctx->r1) {
        // 0x801E9B70: addiu       $at, $zero, 0x2
        ctx->r1 = ADD32(0, 0X2);
            goto L_801E9B94;
    }
    // 0x801E9B70: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x801E9B74: beq         $a0, $at, L_801E9B8C
    if (ctx->r4 == ctx->r1) {
        // 0x801E9B78: addiu       $at, $zero, 0x5
        ctx->r1 = ADD32(0, 0X5);
            goto L_801E9B8C;
    }
    // 0x801E9B78: addiu       $at, $zero, 0x5
    ctx->r1 = ADD32(0, 0X5);
    // 0x801E9B7C: bne         $a0, $at, L_801E9D64
    if (ctx->r4 != ctx->r1) {
        // 0x801E9B80: nop
    
            goto L_801E9D64;
    }
    // 0x801E9B80: nop

    // 0x801E9B84: jr          $ra
    // 0x801E9B88: addiu       $v0, $zero, 0xA
    ctx->r2 = ADD32(0, 0XA);
    return;
    // 0x801E9B88: addiu       $v0, $zero, 0xA
    ctx->r2 = ADD32(0, 0XA);
L_801E9B8C:
    // 0x801E9B8C: jr          $ra
    // 0x801E9B90: addiu       $v0, $zero, 0x28
    ctx->r2 = ADD32(0, 0X28);
    return;
    // 0x801E9B90: addiu       $v0, $zero, 0x28
    ctx->r2 = ADD32(0, 0X28);
L_801E9B94:
    // 0x801E9B94: addiu       $at, $zero, 0x2D
    ctx->r1 = ADD32(0, 0X2D);
    // 0x801E9B98: bnel        $a1, $at, L_801E9BD4
    if (ctx->r5 != ctx->r1) {
        // 0x801E9B9C: addiu       $at, $zero, 0x27
        ctx->r1 = ADD32(0, 0X27);
            goto L_801E9BD4;
    }
    goto skip_2;
    // 0x801E9B9C: addiu       $at, $zero, 0x27
    ctx->r1 = ADD32(0, 0X27);
    skip_2:
    // 0x801E9BA0: beq         $a0, $zero, L_801E9BC0
    if (ctx->r4 == 0) {
        // 0x801E9BA4: addiu       $at, $zero, 0x1
        ctx->r1 = ADD32(0, 0X1);
            goto L_801E9BC0;
    }
    // 0x801E9BA4: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x801E9BA8: beq         $a0, $at, L_801E9BC0
    if (ctx->r4 == ctx->r1) {
        // 0x801E9BAC: addiu       $at, $zero, 0x2
        ctx->r1 = ADD32(0, 0X2);
            goto L_801E9BC0;
    }
    // 0x801E9BAC: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x801E9BB0: beq         $a0, $at, L_801E9BC8
    if (ctx->r4 == ctx->r1) {
        // 0x801E9BB4: nop
    
            goto L_801E9BC8;
    }
    // 0x801E9BB4: nop

    // 0x801E9BB8: jr          $ra
    // 0x801E9BBC: or          $v0, $v1, $zero
    ctx->r2 = ctx->r3 | 0;
    return;
    // 0x801E9BBC: or          $v0, $v1, $zero
    ctx->r2 = ctx->r3 | 0;
L_801E9BC0:
    // 0x801E9BC0: jr          $ra
    // 0x801E9BC4: addiu       $v0, $zero, 0x24
    ctx->r2 = ADD32(0, 0X24);
    return;
    // 0x801E9BC4: addiu       $v0, $zero, 0x24
    ctx->r2 = ADD32(0, 0X24);
L_801E9BC8:
    // 0x801E9BC8: jr          $ra
    // 0x801E9BCC: addiu       $v0, $zero, 0x25
    ctx->r2 = ADD32(0, 0X25);
    return;
    // 0x801E9BCC: addiu       $v0, $zero, 0x25
    ctx->r2 = ADD32(0, 0X25);
    // 0x801E9BD0: addiu       $at, $zero, 0x27
    ctx->r1 = ADD32(0, 0X27);
L_801E9BD4:
    // 0x801E9BD4: bnel        $a1, $at, L_801E9C20
    if (ctx->r5 != ctx->r1) {
        // 0x801E9BD8: addiu       $at, $zero, 0x40
        ctx->r1 = ADD32(0, 0X40);
            goto L_801E9C20;
    }
    goto skip_3;
    // 0x801E9BD8: addiu       $at, $zero, 0x40
    ctx->r1 = ADD32(0, 0X40);
    skip_3:
    // 0x801E9BDC: beq         $a0, $zero, L_801E9C04
    if (ctx->r4 == 0) {
        // 0x801E9BE0: addiu       $at, $zero, 0x1
        ctx->r1 = ADD32(0, 0X1);
            goto L_801E9C04;
    }
    // 0x801E9BE0: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x801E9BE4: beq         $a0, $at, L_801E9C04
    if (ctx->r4 == ctx->r1) {
        // 0x801E9BE8: addiu       $at, $zero, 0x2
        ctx->r1 = ADD32(0, 0X2);
            goto L_801E9C04;
    }
    // 0x801E9BE8: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x801E9BEC: beq         $a0, $at, L_801E9C0C
    if (ctx->r4 == ctx->r1) {
        // 0x801E9BF0: addiu       $at, $zero, 0x3
        ctx->r1 = ADD32(0, 0X3);
            goto L_801E9C0C;
    }
    // 0x801E9BF0: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x801E9BF4: beq         $a0, $at, L_801E9C14
    if (ctx->r4 == ctx->r1) {
        // 0x801E9BF8: nop
    
            goto L_801E9C14;
    }
    // 0x801E9BF8: nop

    // 0x801E9BFC: jr          $ra
    // 0x801E9C00: or          $v0, $v1, $zero
    ctx->r2 = ctx->r3 | 0;
    return;
    // 0x801E9C00: or          $v0, $v1, $zero
    ctx->r2 = ctx->r3 | 0;
L_801E9C04:
    // 0x801E9C04: jr          $ra
    // 0x801E9C08: addiu       $v0, $zero, 0x25
    ctx->r2 = ADD32(0, 0X25);
    return;
    // 0x801E9C08: addiu       $v0, $zero, 0x25
    ctx->r2 = ADD32(0, 0X25);
L_801E9C0C:
    // 0x801E9C0C: jr          $ra
    // 0x801E9C10: addiu       $v0, $zero, 0x26
    ctx->r2 = ADD32(0, 0X26);
    return;
    // 0x801E9C10: addiu       $v0, $zero, 0x26
    ctx->r2 = ADD32(0, 0X26);
L_801E9C14:
    // 0x801E9C14: jr          $ra
    // 0x801E9C18: addiu       $v0, $zero, 0xA
    ctx->r2 = ADD32(0, 0XA);
    return;
    // 0x801E9C18: addiu       $v0, $zero, 0xA
    ctx->r2 = ADD32(0, 0XA);
    // 0x801E9C1C: addiu       $at, $zero, 0x40
    ctx->r1 = ADD32(0, 0X40);
L_801E9C20:
    // 0x801E9C20: bnel        $a1, $at, L_801E9C6C
    if (ctx->r5 != ctx->r1) {
        // 0x801E9C24: addiu       $at, $zero, 0x26
        ctx->r1 = ADD32(0, 0X26);
            goto L_801E9C6C;
    }
    goto skip_4;
    // 0x801E9C24: addiu       $at, $zero, 0x26
    ctx->r1 = ADD32(0, 0X26);
    skip_4:
    // 0x801E9C28: beq         $a0, $zero, L_801E9C50
    if (ctx->r4 == 0) {
        // 0x801E9C2C: addiu       $at, $zero, 0x1
        ctx->r1 = ADD32(0, 0X1);
            goto L_801E9C50;
    }
    // 0x801E9C2C: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x801E9C30: beq         $a0, $at, L_801E9C50
    if (ctx->r4 == ctx->r1) {
        // 0x801E9C34: addiu       $at, $zero, 0x2
        ctx->r1 = ADD32(0, 0X2);
            goto L_801E9C50;
    }
    // 0x801E9C34: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x801E9C38: beq         $a0, $at, L_801E9C58
    if (ctx->r4 == ctx->r1) {
        // 0x801E9C3C: addiu       $at, $zero, 0x3
        ctx->r1 = ADD32(0, 0X3);
            goto L_801E9C58;
    }
    // 0x801E9C3C: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x801E9C40: beq         $a0, $at, L_801E9C60
    if (ctx->r4 == ctx->r1) {
        // 0x801E9C44: nop
    
            goto L_801E9C60;
    }
    // 0x801E9C44: nop

    // 0x801E9C48: jr          $ra
    // 0x801E9C4C: or          $v0, $v1, $zero
    ctx->r2 = ctx->r3 | 0;
    return;
    // 0x801E9C4C: or          $v0, $v1, $zero
    ctx->r2 = ctx->r3 | 0;
L_801E9C50:
    // 0x801E9C50: jr          $ra
    // 0x801E9C54: addiu       $v0, $zero, 0x26
    ctx->r2 = ADD32(0, 0X26);
    return;
    // 0x801E9C54: addiu       $v0, $zero, 0x26
    ctx->r2 = ADD32(0, 0X26);
L_801E9C58:
    // 0x801E9C58: jr          $ra
    // 0x801E9C5C: addiu       $v0, $zero, 0x27
    ctx->r2 = ADD32(0, 0X27);
    return;
    // 0x801E9C5C: addiu       $v0, $zero, 0x27
    ctx->r2 = ADD32(0, 0X27);
L_801E9C60:
    // 0x801E9C60: jr          $ra
    // 0x801E9C64: addiu       $v0, $zero, 0xB
    ctx->r2 = ADD32(0, 0XB);
    return;
    // 0x801E9C64: addiu       $v0, $zero, 0xB
    ctx->r2 = ADD32(0, 0XB);
    // 0x801E9C68: addiu       $at, $zero, 0x26
    ctx->r1 = ADD32(0, 0X26);
L_801E9C6C:
    // 0x801E9C6C: bne         $a1, $at, L_801E9C84
    if (ctx->r5 != ctx->r1) {
        // 0x801E9C70: addiu       $at, $zero, 0x2
        ctx->r1 = ADD32(0, 0X2);
            goto L_801E9C84;
    }
    // 0x801E9C70: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x801E9C74: bne         $a0, $at, L_801E9D64
    if (ctx->r4 != ctx->r1) {
        // 0x801E9C78: nop
    
            goto L_801E9D64;
    }
    // 0x801E9C78: nop

    // 0x801E9C7C: jr          $ra
    // 0x801E9C80: addiu       $v0, $zero, 0x24
    ctx->r2 = ADD32(0, 0X24);
    return;
    // 0x801E9C80: addiu       $v0, $zero, 0x24
    ctx->r2 = ADD32(0, 0X24);
L_801E9C84:
    // 0x801E9C84: addiu       $at, $zero, 0x2E
    ctx->r1 = ADD32(0, 0X2E);
    // 0x801E9C88: bnel        $a1, $at, L_801E9CCC
    if (ctx->r5 != ctx->r1) {
        // 0x801E9C8C: addiu       $at, $zero, 0x7C
        ctx->r1 = ADD32(0, 0X7C);
            goto L_801E9CCC;
    }
    goto skip_5;
    // 0x801E9C8C: addiu       $at, $zero, 0x7C
    ctx->r1 = ADD32(0, 0X7C);
    skip_5:
    // 0x801E9C90: beq         $a0, $zero, L_801E9CB0
    if (ctx->r4 == 0) {
        // 0x801E9C94: addiu       $at, $zero, 0x1
        ctx->r1 = ADD32(0, 0X1);
            goto L_801E9CB0;
    }
    // 0x801E9C94: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x801E9C98: beq         $a0, $at, L_801E9CC0
    if (ctx->r4 == ctx->r1) {
        // 0x801E9C9C: addiu       $at, $zero, 0x2
        ctx->r1 = ADD32(0, 0X2);
            goto L_801E9CC0;
    }
    // 0x801E9C9C: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x801E9CA0: beq         $a0, $at, L_801E9CB8
    if (ctx->r4 == ctx->r1) {
        // 0x801E9CA4: nop
    
            goto L_801E9CB8;
    }
    // 0x801E9CA4: nop

    // 0x801E9CA8: jr          $ra
    // 0x801E9CAC: or          $v0, $v1, $zero
    ctx->r2 = ctx->r3 | 0;
    return;
    // 0x801E9CAC: or          $v0, $v1, $zero
    ctx->r2 = ctx->r3 | 0;
L_801E9CB0:
    // 0x801E9CB0: jr          $ra
    // 0x801E9CB4: addiu       $v0, $zero, 0x27
    ctx->r2 = ADD32(0, 0X27);
    return;
    // 0x801E9CB4: addiu       $v0, $zero, 0x27
    ctx->r2 = ADD32(0, 0X27);
L_801E9CB8:
    // 0x801E9CB8: jr          $ra
    // 0x801E9CBC: addiu       $v0, $zero, 0x29
    ctx->r2 = ADD32(0, 0X29);
    return;
    // 0x801E9CBC: addiu       $v0, $zero, 0x29
    ctx->r2 = ADD32(0, 0X29);
L_801E9CC0:
    // 0x801E9CC0: jr          $ra
    // 0x801E9CC4: addiu       $v0, $zero, 0x29
    ctx->r2 = ADD32(0, 0X29);
    return;
    // 0x801E9CC4: addiu       $v0, $zero, 0x29
    ctx->r2 = ADD32(0, 0X29);
    // 0x801E9CC8: addiu       $at, $zero, 0x7C
    ctx->r1 = ADD32(0, 0X7C);
L_801E9CCC:
    // 0x801E9CCC: bne         $a1, $at, L_801E9CE4
    if (ctx->r5 != ctx->r1) {
        // 0x801E9CD0: addiu       $at, $zero, 0x2
        ctx->r1 = ADD32(0, 0X2);
            goto L_801E9CE4;
    }
    // 0x801E9CD0: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x801E9CD4: bne         $a0, $at, L_801E9D64
    if (ctx->r4 != ctx->r1) {
        // 0x801E9CD8: nop
    
            goto L_801E9D64;
    }
    // 0x801E9CD8: nop

    // 0x801E9CDC: jr          $ra
    // 0x801E9CE0: addiu       $v0, $zero, 0x2A
    ctx->r2 = ADD32(0, 0X2A);
    return;
    // 0x801E9CE0: addiu       $v0, $zero, 0x2A
    ctx->r2 = ADD32(0, 0X2A);
L_801E9CE4:
    // 0x801E9CE4: addiu       $at, $zero, 0x3C
    ctx->r1 = ADD32(0, 0X3C);
    // 0x801E9CE8: bne         $a1, $at, L_801E9D00
    if (ctx->r5 != ctx->r1) {
        // 0x801E9CEC: addiu       $at, $zero, 0x2
        ctx->r1 = ADD32(0, 0X2);
            goto L_801E9D00;
    }
    // 0x801E9CEC: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x801E9CF0: bne         $a0, $at, L_801E9D64
    if (ctx->r4 != ctx->r1) {
        // 0x801E9CF4: nop
    
            goto L_801E9D64;
    }
    // 0x801E9CF4: nop

    // 0x801E9CF8: jr          $ra
    // 0x801E9CFC: addiu       $v0, $zero, 0x2B
    ctx->r2 = ADD32(0, 0X2B);
    return;
    // 0x801E9CFC: addiu       $v0, $zero, 0x2B
    ctx->r2 = ADD32(0, 0X2B);
L_801E9D00:
    // 0x801E9D00: addiu       $at, $zero, 0x3E
    ctx->r1 = ADD32(0, 0X3E);
    // 0x801E9D04: bne         $a1, $at, L_801E9D1C
    if (ctx->r5 != ctx->r1) {
        // 0x801E9D08: addiu       $at, $zero, 0x2
        ctx->r1 = ADD32(0, 0X2);
            goto L_801E9D1C;
    }
    // 0x801E9D08: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x801E9D0C: bne         $a0, $at, L_801E9D64
    if (ctx->r4 != ctx->r1) {
        // 0x801E9D10: nop
    
            goto L_801E9D64;
    }
    // 0x801E9D10: nop

    // 0x801E9D14: jr          $ra
    // 0x801E9D18: addiu       $v0, $zero, 0x2C
    ctx->r2 = ADD32(0, 0X2C);
    return;
    // 0x801E9D18: addiu       $v0, $zero, 0x2C
    ctx->r2 = ADD32(0, 0X2C);
L_801E9D1C:
    // 0x801E9D1C: addiu       $at, $zero, 0xA
    ctx->r1 = ADD32(0, 0XA);
    // 0x801E9D20: bne         $a1, $at, L_801E9D38
    if (ctx->r5 != ctx->r1) {
        // 0x801E9D24: addiu       $at, $zero, 0x1
        ctx->r1 = ADD32(0, 0X1);
            goto L_801E9D38;
    }
    // 0x801E9D24: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x801E9D28: bne         $a0, $at, L_801E9D64
    if (ctx->r4 != ctx->r1) {
        // 0x801E9D2C: nop
    
            goto L_801E9D64;
    }
    // 0x801E9D2C: nop

    // 0x801E9D30: jr          $ra
    // 0x801E9D34: addiu       $v0, $zero, 0x28
    ctx->r2 = ADD32(0, 0X28);
    return;
    // 0x801E9D34: addiu       $v0, $zero, 0x28
    ctx->r2 = ADD32(0, 0X28);
L_801E9D38:
    // 0x801E9D38: addiu       $at, $zero, 0x2B
    ctx->r1 = ADD32(0, 0X2B);
    // 0x801E9D3C: bne         $a1, $at, L_801E9D54
    if (ctx->r5 != ctx->r1) {
        // 0x801E9D40: addiu       $at, $zero, 0x2
        ctx->r1 = ADD32(0, 0X2);
            goto L_801E9D54;
    }
    // 0x801E9D40: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x801E9D44: bne         $a0, $at, L_801E9D64
    if (ctx->r4 != ctx->r1) {
        // 0x801E9D48: nop
    
            goto L_801E9D64;
    }
    // 0x801E9D48: nop

    // 0x801E9D4C: jr          $ra
    // 0x801E9D50: addiu       $v0, $zero, 0x2D
    ctx->r2 = ADD32(0, 0X2D);
    return;
    // 0x801E9D50: addiu       $v0, $zero, 0x2D
    ctx->r2 = ADD32(0, 0X2D);
L_801E9D54:
    // 0x801E9D54: addiu       $at, $zero, 0x20
    ctx->r1 = ADD32(0, 0X20);
    // 0x801E9D58: bne         $a1, $at, L_801E9D64
    if (ctx->r5 != ctx->r1) {
        // 0x801E9D5C: nop
    
            goto L_801E9D64;
    }
    // 0x801E9D5C: nop

    // 0x801E9D60: addiu       $v1, $zero, 0xFF
    ctx->r3 = ADD32(0, 0XFF);
L_801E9D64:
    // 0x801E9D64: jr          $ra
    // 0x801E9D68: or          $v0, $v1, $zero
    ctx->r2 = ctx->r3 | 0;
    return;
    // 0x801E9D68: or          $v0, $v1, $zero
    ctx->r2 = ctx->r3 | 0;
;}
RECOMP_FUNC void func_801E9D6C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801E9D6C: lui         $v1, 0x8023
    ctx->r3 = S32(0X8023 << 16);
    // 0x801E9D70: addiu       $v1, $v1, -0x7588
    ctx->r3 = ADD32(ctx->r3, -0X7588);
    // 0x801E9D74: lh          $v0, 0x2($v1)
    ctx->r2 = MEM_H(ctx->r3, 0X2);
    // 0x801E9D78: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x801E9D7C: beql        $v0, $zero, L_801E9DA8
    if (ctx->r2 == 0) {
        // 0x801E9D80: lw          $t6, 0x4($v1)
        ctx->r14 = MEM_W(ctx->r3, 0X4);
            goto L_801E9DA8;
    }
    goto skip_0;
    // 0x801E9D80: lw          $t6, 0x4($v1)
    ctx->r14 = MEM_W(ctx->r3, 0X4);
    skip_0:
    // 0x801E9D84: beq         $v0, $at, L_801E9E64
    if (ctx->r2 == ctx->r1) {
        // 0x801E9D88: addiu       $at, $zero, 0x2
        ctx->r1 = ADD32(0, 0X2);
            goto L_801E9E64;
    }
    // 0x801E9D88: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x801E9D8C: beq         $v0, $at, L_801E9F24
    if (ctx->r2 == ctx->r1) {
        // 0x801E9D90: addiu       $at, $zero, 0x3
        ctx->r1 = ADD32(0, 0X3);
            goto L_801E9F24;
    }
    // 0x801E9D90: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x801E9D94: beql        $v0, $at, L_801E9FEC
    if (ctx->r2 == ctx->r1) {
        // 0x801E9D98: lw          $v0, 0x8($v1)
        ctx->r2 = MEM_W(ctx->r3, 0X8);
            goto L_801E9FEC;
    }
    goto skip_1;
    // 0x801E9D98: lw          $v0, 0x8($v1)
    ctx->r2 = MEM_W(ctx->r3, 0X8);
    skip_1:
    // 0x801E9D9C: jr          $ra
    // 0x801E9DA0: nop

    return;
    // 0x801E9DA0: nop

    // 0x801E9DA4: lw          $t6, 0x4($v1)
    ctx->r14 = MEM_W(ctx->r3, 0X4);
L_801E9DA8:
    // 0x801E9DA8: lw          $t7, 0x8($v1)
    ctx->r15 = MEM_W(ctx->r3, 0X8);
    // 0x801E9DAC: lui         $at, 0x437F
    ctx->r1 = S32(0X437F << 16);
    // 0x801E9DB0: mtc1        $t6, $f4
    ctx->f4.u32l = ctx->r14;
    // 0x801E9DB4: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x801E9DB8: mtc1        $t7, $f16
    ctx->f16.u32l = ctx->r15;
    // 0x801E9DBC: cvt.s.w     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
    // 0x801E9DC0: addiu       $t9, $zero, 0x1
    ctx->r25 = ADD32(0, 0X1);
    // 0x801E9DC4: addiu       $a0, $zero, 0xFF
    ctx->r4 = ADD32(0, 0XFF);
    // 0x801E9DC8: sh          $a0, 0xC($v1)
    MEM_H(0XC, ctx->r3) = ctx->r4;
    // 0x801E9DCC: lui         $at, 0x4F00
    ctx->r1 = S32(0X4F00 << 16);
    // 0x801E9DD0: cvt.s.w     $f18, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    ctx->f18.fl = CVT_S_W(ctx->f16.u32l);
    // 0x801E9DD4: mul.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = MUL_S(ctx->f6.fl, ctx->f8.fl);
    // 0x801E9DD8: div.s       $f4, $f10, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f4.fl = DIV_S(ctx->f10.fl, ctx->f18.fl);
    // 0x801E9DDC: cfc1        $t8, $FpcCsr
    ctx->r24 = get_cop1_cs();
    // 0x801E9DE0: ctc1        $t9, $FpcCsr
    set_cop1_cs(ctx->r25);
    // 0x801E9DE4: nop

    // 0x801E9DE8: cvt.w.s     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.u32l = CVT_W_S(ctx->f4.fl);
    // 0x801E9DEC: cfc1        $t9, $FpcCsr
    ctx->r25 = get_cop1_cs();
    // 0x801E9DF0: nop

    // 0x801E9DF4: andi        $t9, $t9, 0x78
    ctx->r25 = ctx->r25 & 0X78;
    // 0x801E9DF8: beql        $t9, $zero, L_801E9E48
    if (ctx->r25 == 0) {
        // 0x801E9DFC: mfc1        $t9, $f6
        ctx->r25 = (int32_t)ctx->f6.u32l;
            goto L_801E9E48;
    }
    goto skip_2;
    // 0x801E9DFC: mfc1        $t9, $f6
    ctx->r25 = (int32_t)ctx->f6.u32l;
    skip_2:
    // 0x801E9E00: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x801E9E04: addiu       $t9, $zero, 0x1
    ctx->r25 = ADD32(0, 0X1);
    // 0x801E9E08: sub.s       $f6, $f4, $f6
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f6.fl = ctx->f4.fl - ctx->f6.fl;
    // 0x801E9E0C: ctc1        $t9, $FpcCsr
    set_cop1_cs(ctx->r25);
    // 0x801E9E10: nop

    // 0x801E9E14: cvt.w.s     $f6, $f6
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 6);
    ctx->f6.u32l = CVT_W_S(ctx->f6.fl);
    // 0x801E9E18: cfc1        $t9, $FpcCsr
    ctx->r25 = get_cop1_cs();
    // 0x801E9E1C: nop

    // 0x801E9E20: andi        $t9, $t9, 0x78
    ctx->r25 = ctx->r25 & 0X78;
    // 0x801E9E24: bne         $t9, $zero, L_801E9E3C
    if (ctx->r25 != 0) {
        // 0x801E9E28: nop
    
            goto L_801E9E3C;
    }
    // 0x801E9E28: nop

    // 0x801E9E2C: mfc1        $t9, $f6
    ctx->r25 = (int32_t)ctx->f6.u32l;
    // 0x801E9E30: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x801E9E34: b           L_801E9E54
    // 0x801E9E38: or          $t9, $t9, $at
    ctx->r25 = ctx->r25 | ctx->r1;
        goto L_801E9E54;
    // 0x801E9E38: or          $t9, $t9, $at
    ctx->r25 = ctx->r25 | ctx->r1;
L_801E9E3C:
    // 0x801E9E3C: b           L_801E9E54
    // 0x801E9E40: addiu       $t9, $zero, -0x1
    ctx->r25 = ADD32(0, -0X1);
        goto L_801E9E54;
    // 0x801E9E40: addiu       $t9, $zero, -0x1
    ctx->r25 = ADD32(0, -0X1);
    // 0x801E9E44: mfc1        $t9, $f6
    ctx->r25 = (int32_t)ctx->f6.u32l;
L_801E9E48:
    // 0x801E9E48: nop

    // 0x801E9E4C: bltz        $t9, L_801E9E3C
    if (SIGNED(ctx->r25) < 0) {
        // 0x801E9E50: nop
    
            goto L_801E9E3C;
    }
    // 0x801E9E50: nop

L_801E9E54:
    // 0x801E9E54: ctc1        $t8, $FpcCsr
    set_cop1_cs(ctx->r24);
    // 0x801E9E58: sh          $t9, 0xE($v1)
    MEM_H(0XE, ctx->r3) = ctx->r25;
    // 0x801E9E5C: jr          $ra
    // 0x801E9E60: sh          $zero, 0x10($v1)
    MEM_H(0X10, ctx->r3) = 0;
    return;
    // 0x801E9E60: sh          $zero, 0x10($v1)
    MEM_H(0X10, ctx->r3) = 0;
L_801E9E64:
    // 0x801E9E64: lw          $t0, 0x4($v1)
    ctx->r8 = MEM_W(ctx->r3, 0X4);
    // 0x801E9E68: lw          $t1, 0x8($v1)
    ctx->r9 = MEM_W(ctx->r3, 0X8);
    // 0x801E9E6C: lui         $at, 0x437F
    ctx->r1 = S32(0X437F << 16);
    // 0x801E9E70: mtc1        $t0, $f8
    ctx->f8.u32l = ctx->r8;
    // 0x801E9E74: mtc1        $at, $f10
    ctx->f10.u32l = ctx->r1;
    // 0x801E9E78: mtc1        $t1, $f4
    ctx->f4.u32l = ctx->r9;
    // 0x801E9E7C: cvt.s.w     $f16, $f8
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 8);
    ctx->f16.fl = CVT_S_W(ctx->f8.u32l);
    // 0x801E9E80: addiu       $t3, $zero, 0x1
    ctx->r11 = ADD32(0, 0X1);
    // 0x801E9E84: addiu       $a0, $zero, 0xFF
    ctx->r4 = ADD32(0, 0XFF);
    // 0x801E9E88: sh          $a0, 0xC($v1)
    MEM_H(0XC, ctx->r3) = ctx->r4;
    // 0x801E9E8C: sh          $a0, 0xE($v1)
    MEM_H(0XE, ctx->r3) = ctx->r4;
    // 0x801E9E90: cvt.s.w     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
    // 0x801E9E94: mul.s       $f18, $f16, $f10
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f18.fl = MUL_S(ctx->f16.fl, ctx->f10.fl);
    // 0x801E9E98: lui         $at, 0x4F00
    ctx->r1 = S32(0X4F00 << 16);
    // 0x801E9E9C: div.s       $f8, $f18, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = DIV_S(ctx->f18.fl, ctx->f6.fl);
    // 0x801E9EA0: cfc1        $t2, $FpcCsr
    ctx->r10 = get_cop1_cs();
    // 0x801E9EA4: ctc1        $t3, $FpcCsr
    set_cop1_cs(ctx->r11);
    // 0x801E9EA8: nop

    // 0x801E9EAC: cvt.w.s     $f16, $f8
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 8);
    ctx->f16.u32l = CVT_W_S(ctx->f8.fl);
    // 0x801E9EB0: cfc1        $t3, $FpcCsr
    ctx->r11 = get_cop1_cs();
    // 0x801E9EB4: nop

    // 0x801E9EB8: andi        $t3, $t3, 0x78
    ctx->r11 = ctx->r11 & 0X78;
    // 0x801E9EBC: beql        $t3, $zero, L_801E9F0C
    if (ctx->r11 == 0) {
        // 0x801E9EC0: mfc1        $t3, $f16
        ctx->r11 = (int32_t)ctx->f16.u32l;
            goto L_801E9F0C;
    }
    goto skip_3;
    // 0x801E9EC0: mfc1        $t3, $f16
    ctx->r11 = (int32_t)ctx->f16.u32l;
    skip_3:
    // 0x801E9EC4: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
    // 0x801E9EC8: addiu       $t3, $zero, 0x1
    ctx->r11 = ADD32(0, 0X1);
    // 0x801E9ECC: sub.s       $f16, $f8, $f16
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f16.fl = ctx->f8.fl - ctx->f16.fl;
    // 0x801E9ED0: ctc1        $t3, $FpcCsr
    set_cop1_cs(ctx->r11);
    // 0x801E9ED4: nop

    // 0x801E9ED8: cvt.w.s     $f16, $f16
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 16);
    ctx->f16.u32l = CVT_W_S(ctx->f16.fl);
    // 0x801E9EDC: cfc1        $t3, $FpcCsr
    ctx->r11 = get_cop1_cs();
    // 0x801E9EE0: nop

    // 0x801E9EE4: andi        $t3, $t3, 0x78
    ctx->r11 = ctx->r11 & 0X78;
    // 0x801E9EE8: bne         $t3, $zero, L_801E9F00
    if (ctx->r11 != 0) {
        // 0x801E9EEC: nop
    
            goto L_801E9F00;
    }
    // 0x801E9EEC: nop

    // 0x801E9EF0: mfc1        $t3, $f16
    ctx->r11 = (int32_t)ctx->f16.u32l;
    // 0x801E9EF4: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x801E9EF8: b           L_801E9F18
    // 0x801E9EFC: or          $t3, $t3, $at
    ctx->r11 = ctx->r11 | ctx->r1;
        goto L_801E9F18;
    // 0x801E9EFC: or          $t3, $t3, $at
    ctx->r11 = ctx->r11 | ctx->r1;
L_801E9F00:
    // 0x801E9F00: b           L_801E9F18
    // 0x801E9F04: addiu       $t3, $zero, -0x1
    ctx->r11 = ADD32(0, -0X1);
        goto L_801E9F18;
    // 0x801E9F04: addiu       $t3, $zero, -0x1
    ctx->r11 = ADD32(0, -0X1);
    // 0x801E9F08: mfc1        $t3, $f16
    ctx->r11 = (int32_t)ctx->f16.u32l;
L_801E9F0C:
    // 0x801E9F0C: nop

    // 0x801E9F10: bltz        $t3, L_801E9F00
    if (SIGNED(ctx->r11) < 0) {
        // 0x801E9F14: nop
    
            goto L_801E9F00;
    }
    // 0x801E9F14: nop

L_801E9F18:
    // 0x801E9F18: ctc1        $t2, $FpcCsr
    set_cop1_cs(ctx->r10);
    // 0x801E9F1C: jr          $ra
    // 0x801E9F20: sh          $t3, 0x10($v1)
    MEM_H(0X10, ctx->r3) = ctx->r11;
    return;
    // 0x801E9F20: sh          $t3, 0x10($v1)
    MEM_H(0X10, ctx->r3) = ctx->r11;
L_801E9F24:
    // 0x801E9F24: lw          $v0, 0x8($v1)
    ctx->r2 = MEM_W(ctx->r3, 0X8);
    // 0x801E9F28: lw          $t4, 0x4($v1)
    ctx->r12 = MEM_W(ctx->r3, 0X4);
    // 0x801E9F2C: lui         $at, 0x437F
    ctx->r1 = S32(0X437F << 16);
    // 0x801E9F30: mtc1        $at, $f18
    ctx->f18.u32l = ctx->r1;
    // 0x801E9F34: subu        $t5, $v0, $t4
    ctx->r13 = SUB32(ctx->r2, ctx->r12);
    // 0x801E9F38: mtc1        $t5, $f10
    ctx->f10.u32l = ctx->r13;
    // 0x801E9F3C: mtc1        $v0, $f8
    ctx->f8.u32l = ctx->r2;
    // 0x801E9F40: addiu       $t7, $zero, 0x1
    ctx->r15 = ADD32(0, 0X1);
    // 0x801E9F44: cvt.s.w     $f4, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    ctx->f4.fl = CVT_S_W(ctx->f10.u32l);
    // 0x801E9F48: addiu       $a0, $zero, 0xFF
    ctx->r4 = ADD32(0, 0XFF);
    // 0x801E9F4C: sh          $a0, 0xC($v1)
    MEM_H(0XC, ctx->r3) = ctx->r4;
    // 0x801E9F50: sh          $a0, 0xE($v1)
    MEM_H(0XE, ctx->r3) = ctx->r4;
    // 0x801E9F54: lui         $at, 0x4F00
    ctx->r1 = S32(0X4F00 << 16);
    // 0x801E9F58: cvt.s.w     $f16, $f8
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 8);
    ctx->f16.fl = CVT_S_W(ctx->f8.u32l);
    // 0x801E9F5C: mul.s       $f6, $f4, $f18
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f6.fl = MUL_S(ctx->f4.fl, ctx->f18.fl);
    // 0x801E9F60: div.s       $f10, $f6, $f16
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f10.fl = DIV_S(ctx->f6.fl, ctx->f16.fl);
    // 0x801E9F64: cfc1        $t6, $FpcCsr
    ctx->r14 = get_cop1_cs();
    // 0x801E9F68: ctc1        $t7, $FpcCsr
    set_cop1_cs(ctx->r15);
    // 0x801E9F6C: nop

    // 0x801E9F70: cvt.w.s     $f4, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    ctx->f4.u32l = CVT_W_S(ctx->f10.fl);
    // 0x801E9F74: cfc1        $t7, $FpcCsr
    ctx->r15 = get_cop1_cs();
    // 0x801E9F78: nop

    // 0x801E9F7C: andi        $t7, $t7, 0x78
    ctx->r15 = ctx->r15 & 0X78;
    // 0x801E9F80: beql        $t7, $zero, L_801E9FD0
    if (ctx->r15 == 0) {
        // 0x801E9F84: mfc1        $t7, $f4
        ctx->r15 = (int32_t)ctx->f4.u32l;
            goto L_801E9FD0;
    }
    goto skip_4;
    // 0x801E9F84: mfc1        $t7, $f4
    ctx->r15 = (int32_t)ctx->f4.u32l;
    skip_4:
    // 0x801E9F88: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x801E9F8C: addiu       $t7, $zero, 0x1
    ctx->r15 = ADD32(0, 0X1);
    // 0x801E9F90: sub.s       $f4, $f10, $f4
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f4.fl = ctx->f10.fl - ctx->f4.fl;
    // 0x801E9F94: ctc1        $t7, $FpcCsr
    set_cop1_cs(ctx->r15);
    // 0x801E9F98: nop

    // 0x801E9F9C: cvt.w.s     $f4, $f4
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 4);
    ctx->f4.u32l = CVT_W_S(ctx->f4.fl);
    // 0x801E9FA0: cfc1        $t7, $FpcCsr
    ctx->r15 = get_cop1_cs();
    // 0x801E9FA4: nop

    // 0x801E9FA8: andi        $t7, $t7, 0x78
    ctx->r15 = ctx->r15 & 0X78;
    // 0x801E9FAC: bne         $t7, $zero, L_801E9FC4
    if (ctx->r15 != 0) {
        // 0x801E9FB0: nop
    
            goto L_801E9FC4;
    }
    // 0x801E9FB0: nop

    // 0x801E9FB4: mfc1        $t7, $f4
    ctx->r15 = (int32_t)ctx->f4.u32l;
    // 0x801E9FB8: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x801E9FBC: b           L_801E9FDC
    // 0x801E9FC0: or          $t7, $t7, $at
    ctx->r15 = ctx->r15 | ctx->r1;
        goto L_801E9FDC;
    // 0x801E9FC0: or          $t7, $t7, $at
    ctx->r15 = ctx->r15 | ctx->r1;
L_801E9FC4:
    // 0x801E9FC4: b           L_801E9FDC
    // 0x801E9FC8: addiu       $t7, $zero, -0x1
    ctx->r15 = ADD32(0, -0X1);
        goto L_801E9FDC;
    // 0x801E9FC8: addiu       $t7, $zero, -0x1
    ctx->r15 = ADD32(0, -0X1);
    // 0x801E9FCC: mfc1        $t7, $f4
    ctx->r15 = (int32_t)ctx->f4.u32l;
L_801E9FD0:
    // 0x801E9FD0: nop

    // 0x801E9FD4: bltz        $t7, L_801E9FC4
    if (SIGNED(ctx->r15) < 0) {
        // 0x801E9FD8: nop
    
            goto L_801E9FC4;
    }
    // 0x801E9FD8: nop

L_801E9FDC:
    // 0x801E9FDC: ctc1        $t6, $FpcCsr
    set_cop1_cs(ctx->r14);
    // 0x801E9FE0: jr          $ra
    // 0x801E9FE4: sh          $t7, 0x10($v1)
    MEM_H(0X10, ctx->r3) = ctx->r15;
    return;
    // 0x801E9FE4: sh          $t7, 0x10($v1)
    MEM_H(0X10, ctx->r3) = ctx->r15;
    // 0x801E9FE8: lw          $v0, 0x8($v1)
    ctx->r2 = MEM_W(ctx->r3, 0X8);
L_801E9FEC:
    // 0x801E9FEC: lw          $t8, 0x4($v1)
    ctx->r24 = MEM_W(ctx->r3, 0X4);
    // 0x801E9FF0: lui         $at, 0x437F
    ctx->r1 = S32(0X437F << 16);
    // 0x801E9FF4: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x801E9FF8: subu        $t9, $v0, $t8
    ctx->r25 = SUB32(ctx->r2, ctx->r24);
    // 0x801E9FFC: mtc1        $t9, $f18
    ctx->f18.u32l = ctx->r25;
    // 0x801EA000: mtc1        $v0, $f10
    ctx->f10.u32l = ctx->r2;
    // 0x801EA004: addiu       $t1, $zero, 0x1
    ctx->r9 = ADD32(0, 0X1);
    // 0x801EA008: cvt.s.w     $f8, $f18
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 18);
    ctx->f8.fl = CVT_S_W(ctx->f18.u32l);
    // 0x801EA00C: addiu       $a0, $zero, 0xFF
    ctx->r4 = ADD32(0, 0XFF);
    // 0x801EA010: sh          $a0, 0xC($v1)
    MEM_H(0XC, ctx->r3) = ctx->r4;
    // 0x801EA014: lui         $at, 0x4F00
    ctx->r1 = S32(0X4F00 << 16);
    // 0x801EA018: cvt.s.w     $f4, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    ctx->f4.fl = CVT_S_W(ctx->f10.u32l);
    // 0x801EA01C: mul.s       $f16, $f8, $f6
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f16.fl = MUL_S(ctx->f8.fl, ctx->f6.fl);
    // 0x801EA020: div.s       $f18, $f16, $f4
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f18.fl = DIV_S(ctx->f16.fl, ctx->f4.fl);
    // 0x801EA024: cfc1        $t0, $FpcCsr
    ctx->r8 = get_cop1_cs();
    // 0x801EA028: ctc1        $t1, $FpcCsr
    set_cop1_cs(ctx->r9);
    // 0x801EA02C: nop

    // 0x801EA030: cvt.w.s     $f8, $f18
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 18);
    ctx->f8.u32l = CVT_W_S(ctx->f18.fl);
    // 0x801EA034: cfc1        $t1, $FpcCsr
    ctx->r9 = get_cop1_cs();
    // 0x801EA038: nop

    // 0x801EA03C: andi        $t1, $t1, 0x78
    ctx->r9 = ctx->r9 & 0X78;
    // 0x801EA040: beql        $t1, $zero, L_801EA090
    if (ctx->r9 == 0) {
        // 0x801EA044: mfc1        $t1, $f8
        ctx->r9 = (int32_t)ctx->f8.u32l;
            goto L_801EA090;
    }
    goto skip_5;
    // 0x801EA044: mfc1        $t1, $f8
    ctx->r9 = (int32_t)ctx->f8.u32l;
    skip_5:
    // 0x801EA048: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x801EA04C: addiu       $t1, $zero, 0x1
    ctx->r9 = ADD32(0, 0X1);
    // 0x801EA050: sub.s       $f8, $f18, $f8
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f8.fl = ctx->f18.fl - ctx->f8.fl;
    // 0x801EA054: ctc1        $t1, $FpcCsr
    set_cop1_cs(ctx->r9);
    // 0x801EA058: nop

    // 0x801EA05C: cvt.w.s     $f8, $f8
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 8);
    ctx->f8.u32l = CVT_W_S(ctx->f8.fl);
    // 0x801EA060: cfc1        $t1, $FpcCsr
    ctx->r9 = get_cop1_cs();
    // 0x801EA064: nop

    // 0x801EA068: andi        $t1, $t1, 0x78
    ctx->r9 = ctx->r9 & 0X78;
    // 0x801EA06C: bne         $t1, $zero, L_801EA084
    if (ctx->r9 != 0) {
        // 0x801EA070: nop
    
            goto L_801EA084;
    }
    // 0x801EA070: nop

    // 0x801EA074: mfc1        $t1, $f8
    ctx->r9 = (int32_t)ctx->f8.u32l;
    // 0x801EA078: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x801EA07C: b           L_801EA09C
    // 0x801EA080: or          $t1, $t1, $at
    ctx->r9 = ctx->r9 | ctx->r1;
        goto L_801EA09C;
    // 0x801EA080: or          $t1, $t1, $at
    ctx->r9 = ctx->r9 | ctx->r1;
L_801EA084:
    // 0x801EA084: b           L_801EA09C
    // 0x801EA088: addiu       $t1, $zero, -0x1
    ctx->r9 = ADD32(0, -0X1);
        goto L_801EA09C;
    // 0x801EA088: addiu       $t1, $zero, -0x1
    ctx->r9 = ADD32(0, -0X1);
    // 0x801EA08C: mfc1        $t1, $f8
    ctx->r9 = (int32_t)ctx->f8.u32l;
L_801EA090:
    // 0x801EA090: nop

    // 0x801EA094: bltz        $t1, L_801EA084
    if (SIGNED(ctx->r9) < 0) {
        // 0x801EA098: nop
    
            goto L_801EA084;
    }
    // 0x801EA098: nop

L_801EA09C:
    // 0x801EA09C: ctc1        $t0, $FpcCsr
    set_cop1_cs(ctx->r8);
    // 0x801EA0A0: sh          $t1, 0xE($v1)
    MEM_H(0XE, ctx->r3) = ctx->r9;
    // 0x801EA0A4: sh          $zero, 0x10($v1)
    MEM_H(0X10, ctx->r3) = 0;
    // 0x801EA0A8: jr          $ra
    // 0x801EA0AC: nop

    return;
    // 0x801EA0AC: nop

;}
RECOMP_FUNC void func_801EA0B0(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801EA0B0: lui         $v1, 0x8023
    ctx->r3 = S32(0X8023 << 16);
    // 0x801EA0B4: addiu       $v1, $v1, -0x7588
    ctx->r3 = ADD32(ctx->r3, -0X7588);
    // 0x801EA0B8: lh          $v0, 0x2($v1)
    ctx->r2 = MEM_H(ctx->r3, 0X2);
    // 0x801EA0BC: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x801EA0C0: beql        $v0, $zero, L_801EA0EC
    if (ctx->r2 == 0) {
        // 0x801EA0C4: lw          $t6, 0x4($v1)
        ctx->r14 = MEM_W(ctx->r3, 0X4);
            goto L_801EA0EC;
    }
    goto skip_0;
    // 0x801EA0C4: lw          $t6, 0x4($v1)
    ctx->r14 = MEM_W(ctx->r3, 0X4);
    skip_0:
    // 0x801EA0C8: beq         $v0, $at, L_801EA1A4
    if (ctx->r2 == ctx->r1) {
        // 0x801EA0CC: addiu       $at, $zero, 0x2
        ctx->r1 = ADD32(0, 0X2);
            goto L_801EA1A4;
    }
    // 0x801EA0CC: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x801EA0D0: beq         $v0, $at, L_801EA264
    if (ctx->r2 == ctx->r1) {
        // 0x801EA0D4: addiu       $at, $zero, 0x3
        ctx->r1 = ADD32(0, 0X3);
            goto L_801EA264;
    }
    // 0x801EA0D4: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x801EA0D8: beql        $v0, $at, L_801EA32C
    if (ctx->r2 == ctx->r1) {
        // 0x801EA0DC: lw          $v0, 0x8($v1)
        ctx->r2 = MEM_W(ctx->r3, 0X8);
            goto L_801EA32C;
    }
    goto skip_1;
    // 0x801EA0DC: lw          $v0, 0x8($v1)
    ctx->r2 = MEM_W(ctx->r3, 0X8);
    skip_1:
    // 0x801EA0E0: jr          $ra
    // 0x801EA0E4: nop

    return;
    // 0x801EA0E4: nop

    // 0x801EA0E8: lw          $t6, 0x4($v1)
    ctx->r14 = MEM_W(ctx->r3, 0X4);
L_801EA0EC:
    // 0x801EA0EC: lw          $t7, 0x8($v1)
    ctx->r15 = MEM_W(ctx->r3, 0X8);
    // 0x801EA0F0: lui         $at, 0x437F
    ctx->r1 = S32(0X437F << 16);
    // 0x801EA0F4: mtc1        $t6, $f4
    ctx->f4.u32l = ctx->r14;
    // 0x801EA0F8: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x801EA0FC: mtc1        $t7, $f16
    ctx->f16.u32l = ctx->r15;
    // 0x801EA100: cvt.s.w     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
    // 0x801EA104: addiu       $t9, $zero, 0x1
    ctx->r25 = ADD32(0, 0X1);
    // 0x801EA108: lui         $at, 0x4F00
    ctx->r1 = S32(0X4F00 << 16);
    // 0x801EA10C: cvt.s.w     $f18, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    ctx->f18.fl = CVT_S_W(ctx->f16.u32l);
    // 0x801EA110: mul.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = MUL_S(ctx->f6.fl, ctx->f8.fl);
    // 0x801EA114: div.s       $f4, $f10, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f4.fl = DIV_S(ctx->f10.fl, ctx->f18.fl);
    // 0x801EA118: cfc1        $t8, $FpcCsr
    ctx->r24 = get_cop1_cs();
    // 0x801EA11C: ctc1        $t9, $FpcCsr
    set_cop1_cs(ctx->r25);
    // 0x801EA120: nop

    // 0x801EA124: cvt.w.s     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.u32l = CVT_W_S(ctx->f4.fl);
    // 0x801EA128: cfc1        $t9, $FpcCsr
    ctx->r25 = get_cop1_cs();
    // 0x801EA12C: nop

    // 0x801EA130: andi        $t9, $t9, 0x78
    ctx->r25 = ctx->r25 & 0X78;
    // 0x801EA134: beql        $t9, $zero, L_801EA184
    if (ctx->r25 == 0) {
        // 0x801EA138: mfc1        $t9, $f6
        ctx->r25 = (int32_t)ctx->f6.u32l;
            goto L_801EA184;
    }
    goto skip_2;
    // 0x801EA138: mfc1        $t9, $f6
    ctx->r25 = (int32_t)ctx->f6.u32l;
    skip_2:
    // 0x801EA13C: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x801EA140: addiu       $t9, $zero, 0x1
    ctx->r25 = ADD32(0, 0X1);
    // 0x801EA144: sub.s       $f6, $f4, $f6
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f6.fl = ctx->f4.fl - ctx->f6.fl;
    // 0x801EA148: ctc1        $t9, $FpcCsr
    set_cop1_cs(ctx->r25);
    // 0x801EA14C: nop

    // 0x801EA150: cvt.w.s     $f6, $f6
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 6);
    ctx->f6.u32l = CVT_W_S(ctx->f6.fl);
    // 0x801EA154: cfc1        $t9, $FpcCsr
    ctx->r25 = get_cop1_cs();
    // 0x801EA158: nop

    // 0x801EA15C: andi        $t9, $t9, 0x78
    ctx->r25 = ctx->r25 & 0X78;
    // 0x801EA160: bne         $t9, $zero, L_801EA178
    if (ctx->r25 != 0) {
        // 0x801EA164: nop
    
            goto L_801EA178;
    }
    // 0x801EA164: nop

    // 0x801EA168: mfc1        $t9, $f6
    ctx->r25 = (int32_t)ctx->f6.u32l;
    // 0x801EA16C: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x801EA170: b           L_801EA190
    // 0x801EA174: or          $t9, $t9, $at
    ctx->r25 = ctx->r25 | ctx->r1;
        goto L_801EA190;
    // 0x801EA174: or          $t9, $t9, $at
    ctx->r25 = ctx->r25 | ctx->r1;
L_801EA178:
    // 0x801EA178: b           L_801EA190
    // 0x801EA17C: addiu       $t9, $zero, -0x1
    ctx->r25 = ADD32(0, -0X1);
        goto L_801EA190;
    // 0x801EA17C: addiu       $t9, $zero, -0x1
    ctx->r25 = ADD32(0, -0X1);
    // 0x801EA180: mfc1        $t9, $f6
    ctx->r25 = (int32_t)ctx->f6.u32l;
L_801EA184:
    // 0x801EA184: nop

    // 0x801EA188: bltz        $t9, L_801EA178
    if (SIGNED(ctx->r25) < 0) {
        // 0x801EA18C: nop
    
            goto L_801EA178;
    }
    // 0x801EA18C: nop

L_801EA190:
    // 0x801EA190: ctc1        $t8, $FpcCsr
    set_cop1_cs(ctx->r24);
    // 0x801EA194: sh          $t9, 0xC($v1)
    MEM_H(0XC, ctx->r3) = ctx->r25;
    // 0x801EA198: sh          $zero, 0xE($v1)
    MEM_H(0XE, ctx->r3) = 0;
    // 0x801EA19C: jr          $ra
    // 0x801EA1A0: sh          $zero, 0x10($v1)
    MEM_H(0X10, ctx->r3) = 0;
    return;
    // 0x801EA1A0: sh          $zero, 0x10($v1)
    MEM_H(0X10, ctx->r3) = 0;
L_801EA1A4:
    // 0x801EA1A4: lw          $t1, 0x4($v1)
    ctx->r9 = MEM_W(ctx->r3, 0X4);
    // 0x801EA1A8: lw          $t2, 0x8($v1)
    ctx->r10 = MEM_W(ctx->r3, 0X8);
    // 0x801EA1AC: lui         $at, 0x437F
    ctx->r1 = S32(0X437F << 16);
    // 0x801EA1B0: mtc1        $t1, $f8
    ctx->f8.u32l = ctx->r9;
    // 0x801EA1B4: mtc1        $at, $f10
    ctx->f10.u32l = ctx->r1;
    // 0x801EA1B8: mtc1        $t2, $f4
    ctx->f4.u32l = ctx->r10;
    // 0x801EA1BC: cvt.s.w     $f16, $f8
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 8);
    ctx->f16.fl = CVT_S_W(ctx->f8.u32l);
    // 0x801EA1C0: addiu       $t4, $zero, 0x1
    ctx->r12 = ADD32(0, 0X1);
    // 0x801EA1C4: addiu       $t0, $zero, 0xFF
    ctx->r8 = ADD32(0, 0XFF);
    // 0x801EA1C8: sh          $t0, 0xC($v1)
    MEM_H(0XC, ctx->r3) = ctx->r8;
    // 0x801EA1CC: lui         $at, 0x4F00
    ctx->r1 = S32(0X4F00 << 16);
    // 0x801EA1D0: cvt.s.w     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
    // 0x801EA1D4: mul.s       $f18, $f16, $f10
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f18.fl = MUL_S(ctx->f16.fl, ctx->f10.fl);
    // 0x801EA1D8: div.s       $f8, $f18, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = DIV_S(ctx->f18.fl, ctx->f6.fl);
    // 0x801EA1DC: cfc1        $t3, $FpcCsr
    ctx->r11 = get_cop1_cs();
    // 0x801EA1E0: ctc1        $t4, $FpcCsr
    set_cop1_cs(ctx->r12);
    // 0x801EA1E4: nop

    // 0x801EA1E8: cvt.w.s     $f16, $f8
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 8);
    ctx->f16.u32l = CVT_W_S(ctx->f8.fl);
    // 0x801EA1EC: cfc1        $t4, $FpcCsr
    ctx->r12 = get_cop1_cs();
    // 0x801EA1F0: nop

    // 0x801EA1F4: andi        $t4, $t4, 0x78
    ctx->r12 = ctx->r12 & 0X78;
    // 0x801EA1F8: beql        $t4, $zero, L_801EA248
    if (ctx->r12 == 0) {
        // 0x801EA1FC: mfc1        $t4, $f16
        ctx->r12 = (int32_t)ctx->f16.u32l;
            goto L_801EA248;
    }
    goto skip_3;
    // 0x801EA1FC: mfc1        $t4, $f16
    ctx->r12 = (int32_t)ctx->f16.u32l;
    skip_3:
    // 0x801EA200: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
    // 0x801EA204: addiu       $t4, $zero, 0x1
    ctx->r12 = ADD32(0, 0X1);
    // 0x801EA208: sub.s       $f16, $f8, $f16
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f16.fl = ctx->f8.fl - ctx->f16.fl;
    // 0x801EA20C: ctc1        $t4, $FpcCsr
    set_cop1_cs(ctx->r12);
    // 0x801EA210: nop

    // 0x801EA214: cvt.w.s     $f16, $f16
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 16);
    ctx->f16.u32l = CVT_W_S(ctx->f16.fl);
    // 0x801EA218: cfc1        $t4, $FpcCsr
    ctx->r12 = get_cop1_cs();
    // 0x801EA21C: nop

    // 0x801EA220: andi        $t4, $t4, 0x78
    ctx->r12 = ctx->r12 & 0X78;
    // 0x801EA224: bne         $t4, $zero, L_801EA23C
    if (ctx->r12 != 0) {
        // 0x801EA228: nop
    
            goto L_801EA23C;
    }
    // 0x801EA228: nop

    // 0x801EA22C: mfc1        $t4, $f16
    ctx->r12 = (int32_t)ctx->f16.u32l;
    // 0x801EA230: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x801EA234: b           L_801EA254
    // 0x801EA238: or          $t4, $t4, $at
    ctx->r12 = ctx->r12 | ctx->r1;
        goto L_801EA254;
    // 0x801EA238: or          $t4, $t4, $at
    ctx->r12 = ctx->r12 | ctx->r1;
L_801EA23C:
    // 0x801EA23C: b           L_801EA254
    // 0x801EA240: addiu       $t4, $zero, -0x1
    ctx->r12 = ADD32(0, -0X1);
        goto L_801EA254;
    // 0x801EA240: addiu       $t4, $zero, -0x1
    ctx->r12 = ADD32(0, -0X1);
    // 0x801EA244: mfc1        $t4, $f16
    ctx->r12 = (int32_t)ctx->f16.u32l;
L_801EA248:
    // 0x801EA248: nop

    // 0x801EA24C: bltz        $t4, L_801EA23C
    if (SIGNED(ctx->r12) < 0) {
        // 0x801EA250: nop
    
            goto L_801EA23C;
    }
    // 0x801EA250: nop

L_801EA254:
    // 0x801EA254: ctc1        $t3, $FpcCsr
    set_cop1_cs(ctx->r11);
    // 0x801EA258: sh          $t4, 0xE($v1)
    MEM_H(0XE, ctx->r3) = ctx->r12;
    // 0x801EA25C: jr          $ra
    // 0x801EA260: sh          $zero, 0x10($v1)
    MEM_H(0X10, ctx->r3) = 0;
    return;
    // 0x801EA260: sh          $zero, 0x10($v1)
    MEM_H(0X10, ctx->r3) = 0;
L_801EA264:
    // 0x801EA264: lw          $v0, 0x8($v1)
    ctx->r2 = MEM_W(ctx->r3, 0X8);
    // 0x801EA268: lw          $t6, 0x4($v1)
    ctx->r14 = MEM_W(ctx->r3, 0X4);
    // 0x801EA26C: lui         $at, 0x437F
    ctx->r1 = S32(0X437F << 16);
    // 0x801EA270: mtc1        $at, $f18
    ctx->f18.u32l = ctx->r1;
    // 0x801EA274: subu        $t7, $v0, $t6
    ctx->r15 = SUB32(ctx->r2, ctx->r14);
    // 0x801EA278: mtc1        $t7, $f10
    ctx->f10.u32l = ctx->r15;
    // 0x801EA27C: mtc1        $v0, $f8
    ctx->f8.u32l = ctx->r2;
    // 0x801EA280: addiu       $t9, $zero, 0x1
    ctx->r25 = ADD32(0, 0X1);
    // 0x801EA284: cvt.s.w     $f4, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    ctx->f4.fl = CVT_S_W(ctx->f10.u32l);
    // 0x801EA288: addiu       $t5, $zero, 0xFF
    ctx->r13 = ADD32(0, 0XFF);
    // 0x801EA28C: sh          $t5, 0xC($v1)
    MEM_H(0XC, ctx->r3) = ctx->r13;
    // 0x801EA290: lui         $at, 0x4F00
    ctx->r1 = S32(0X4F00 << 16);
    // 0x801EA294: cvt.s.w     $f16, $f8
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 8);
    ctx->f16.fl = CVT_S_W(ctx->f8.u32l);
    // 0x801EA298: mul.s       $f6, $f4, $f18
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f6.fl = MUL_S(ctx->f4.fl, ctx->f18.fl);
    // 0x801EA29C: div.s       $f10, $f6, $f16
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f10.fl = DIV_S(ctx->f6.fl, ctx->f16.fl);
    // 0x801EA2A0: cfc1        $t8, $FpcCsr
    ctx->r24 = get_cop1_cs();
    // 0x801EA2A4: ctc1        $t9, $FpcCsr
    set_cop1_cs(ctx->r25);
    // 0x801EA2A8: nop

    // 0x801EA2AC: cvt.w.s     $f4, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    ctx->f4.u32l = CVT_W_S(ctx->f10.fl);
    // 0x801EA2B0: cfc1        $t9, $FpcCsr
    ctx->r25 = get_cop1_cs();
    // 0x801EA2B4: nop

    // 0x801EA2B8: andi        $t9, $t9, 0x78
    ctx->r25 = ctx->r25 & 0X78;
    // 0x801EA2BC: beql        $t9, $zero, L_801EA30C
    if (ctx->r25 == 0) {
        // 0x801EA2C0: mfc1        $t9, $f4
        ctx->r25 = (int32_t)ctx->f4.u32l;
            goto L_801EA30C;
    }
    goto skip_4;
    // 0x801EA2C0: mfc1        $t9, $f4
    ctx->r25 = (int32_t)ctx->f4.u32l;
    skip_4:
    // 0x801EA2C4: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x801EA2C8: addiu       $t9, $zero, 0x1
    ctx->r25 = ADD32(0, 0X1);
    // 0x801EA2CC: sub.s       $f4, $f10, $f4
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f4.fl = ctx->f10.fl - ctx->f4.fl;
    // 0x801EA2D0: ctc1        $t9, $FpcCsr
    set_cop1_cs(ctx->r25);
    // 0x801EA2D4: nop

    // 0x801EA2D8: cvt.w.s     $f4, $f4
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 4);
    ctx->f4.u32l = CVT_W_S(ctx->f4.fl);
    // 0x801EA2DC: cfc1        $t9, $FpcCsr
    ctx->r25 = get_cop1_cs();
    // 0x801EA2E0: nop

    // 0x801EA2E4: andi        $t9, $t9, 0x78
    ctx->r25 = ctx->r25 & 0X78;
    // 0x801EA2E8: bne         $t9, $zero, L_801EA300
    if (ctx->r25 != 0) {
        // 0x801EA2EC: nop
    
            goto L_801EA300;
    }
    // 0x801EA2EC: nop

    // 0x801EA2F0: mfc1        $t9, $f4
    ctx->r25 = (int32_t)ctx->f4.u32l;
    // 0x801EA2F4: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x801EA2F8: b           L_801EA318
    // 0x801EA2FC: or          $t9, $t9, $at
    ctx->r25 = ctx->r25 | ctx->r1;
        goto L_801EA318;
    // 0x801EA2FC: or          $t9, $t9, $at
    ctx->r25 = ctx->r25 | ctx->r1;
L_801EA300:
    // 0x801EA300: b           L_801EA318
    // 0x801EA304: addiu       $t9, $zero, -0x1
    ctx->r25 = ADD32(0, -0X1);
        goto L_801EA318;
    // 0x801EA304: addiu       $t9, $zero, -0x1
    ctx->r25 = ADD32(0, -0X1);
    // 0x801EA308: mfc1        $t9, $f4
    ctx->r25 = (int32_t)ctx->f4.u32l;
L_801EA30C:
    // 0x801EA30C: nop

    // 0x801EA310: bltz        $t9, L_801EA300
    if (SIGNED(ctx->r25) < 0) {
        // 0x801EA314: nop
    
            goto L_801EA300;
    }
    // 0x801EA314: nop

L_801EA318:
    // 0x801EA318: ctc1        $t8, $FpcCsr
    set_cop1_cs(ctx->r24);
    // 0x801EA31C: sh          $t9, 0xE($v1)
    MEM_H(0XE, ctx->r3) = ctx->r25;
    // 0x801EA320: jr          $ra
    // 0x801EA324: sh          $zero, 0x10($v1)
    MEM_H(0X10, ctx->r3) = 0;
    return;
    // 0x801EA324: sh          $zero, 0x10($v1)
    MEM_H(0X10, ctx->r3) = 0;
    // 0x801EA328: lw          $v0, 0x8($v1)
    ctx->r2 = MEM_W(ctx->r3, 0X8);
L_801EA32C:
    // 0x801EA32C: lw          $t0, 0x4($v1)
    ctx->r8 = MEM_W(ctx->r3, 0X4);
    // 0x801EA330: lui         $at, 0x437F
    ctx->r1 = S32(0X437F << 16);
    // 0x801EA334: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x801EA338: subu        $t1, $v0, $t0
    ctx->r9 = SUB32(ctx->r2, ctx->r8);
    // 0x801EA33C: mtc1        $t1, $f18
    ctx->f18.u32l = ctx->r9;
    // 0x801EA340: mtc1        $v0, $f10
    ctx->f10.u32l = ctx->r2;
    // 0x801EA344: addiu       $t3, $zero, 0x1
    ctx->r11 = ADD32(0, 0X1);
    // 0x801EA348: cvt.s.w     $f8, $f18
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 18);
    ctx->f8.fl = CVT_S_W(ctx->f18.u32l);
    // 0x801EA34C: lui         $at, 0x4F00
    ctx->r1 = S32(0X4F00 << 16);
    // 0x801EA350: cvt.s.w     $f4, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    ctx->f4.fl = CVT_S_W(ctx->f10.u32l);
    // 0x801EA354: mul.s       $f16, $f8, $f6
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f16.fl = MUL_S(ctx->f8.fl, ctx->f6.fl);
    // 0x801EA358: div.s       $f18, $f16, $f4
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f18.fl = DIV_S(ctx->f16.fl, ctx->f4.fl);
    // 0x801EA35C: cfc1        $t2, $FpcCsr
    ctx->r10 = get_cop1_cs();
    // 0x801EA360: ctc1        $t3, $FpcCsr
    set_cop1_cs(ctx->r11);
    // 0x801EA364: nop

    // 0x801EA368: cvt.w.s     $f8, $f18
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 18);
    ctx->f8.u32l = CVT_W_S(ctx->f18.fl);
    // 0x801EA36C: cfc1        $t3, $FpcCsr
    ctx->r11 = get_cop1_cs();
    // 0x801EA370: nop

    // 0x801EA374: andi        $t3, $t3, 0x78
    ctx->r11 = ctx->r11 & 0X78;
    // 0x801EA378: beql        $t3, $zero, L_801EA3C8
    if (ctx->r11 == 0) {
        // 0x801EA37C: mfc1        $t3, $f8
        ctx->r11 = (int32_t)ctx->f8.u32l;
            goto L_801EA3C8;
    }
    goto skip_5;
    // 0x801EA37C: mfc1        $t3, $f8
    ctx->r11 = (int32_t)ctx->f8.u32l;
    skip_5:
    // 0x801EA380: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x801EA384: addiu       $t3, $zero, 0x1
    ctx->r11 = ADD32(0, 0X1);
    // 0x801EA388: sub.s       $f8, $f18, $f8
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f8.fl = ctx->f18.fl - ctx->f8.fl;
    // 0x801EA38C: ctc1        $t3, $FpcCsr
    set_cop1_cs(ctx->r11);
    // 0x801EA390: nop

    // 0x801EA394: cvt.w.s     $f8, $f8
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 8);
    ctx->f8.u32l = CVT_W_S(ctx->f8.fl);
    // 0x801EA398: cfc1        $t3, $FpcCsr
    ctx->r11 = get_cop1_cs();
    // 0x801EA39C: nop

    // 0x801EA3A0: andi        $t3, $t3, 0x78
    ctx->r11 = ctx->r11 & 0X78;
    // 0x801EA3A4: bne         $t3, $zero, L_801EA3BC
    if (ctx->r11 != 0) {
        // 0x801EA3A8: nop
    
            goto L_801EA3BC;
    }
    // 0x801EA3A8: nop

    // 0x801EA3AC: mfc1        $t3, $f8
    ctx->r11 = (int32_t)ctx->f8.u32l;
    // 0x801EA3B0: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x801EA3B4: b           L_801EA3D4
    // 0x801EA3B8: or          $t3, $t3, $at
    ctx->r11 = ctx->r11 | ctx->r1;
        goto L_801EA3D4;
    // 0x801EA3B8: or          $t3, $t3, $at
    ctx->r11 = ctx->r11 | ctx->r1;
L_801EA3BC:
    // 0x801EA3BC: b           L_801EA3D4
    // 0x801EA3C0: addiu       $t3, $zero, -0x1
    ctx->r11 = ADD32(0, -0X1);
        goto L_801EA3D4;
    // 0x801EA3C0: addiu       $t3, $zero, -0x1
    ctx->r11 = ADD32(0, -0X1);
    // 0x801EA3C4: mfc1        $t3, $f8
    ctx->r11 = (int32_t)ctx->f8.u32l;
L_801EA3C8:
    // 0x801EA3C8: nop

    // 0x801EA3CC: bltz        $t3, L_801EA3BC
    if (SIGNED(ctx->r11) < 0) {
        // 0x801EA3D0: nop
    
            goto L_801EA3BC;
    }
    // 0x801EA3D0: nop

L_801EA3D4:
    // 0x801EA3D4: ctc1        $t2, $FpcCsr
    set_cop1_cs(ctx->r10);
    // 0x801EA3D8: sh          $t3, 0xC($v1)
    MEM_H(0XC, ctx->r3) = ctx->r11;
    // 0x801EA3DC: sh          $zero, 0xE($v1)
    MEM_H(0XE, ctx->r3) = 0;
    // 0x801EA3E0: sh          $zero, 0x10($v1)
    MEM_H(0X10, ctx->r3) = 0;
    // 0x801EA3E4: jr          $ra
    // 0x801EA3E8: nop

    return;
    // 0x801EA3E8: nop

;}
RECOMP_FUNC void func_801EA3EC(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801EA3EC: lui         $v1, 0x8023
    ctx->r3 = S32(0X8023 << 16);
    // 0x801EA3F0: addiu       $v1, $v1, -0x7588
    ctx->r3 = ADD32(ctx->r3, -0X7588);
    // 0x801EA3F4: lh          $v0, 0x2($v1)
    ctx->r2 = MEM_H(ctx->r3, 0X2);
    // 0x801EA3F8: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x801EA3FC: beql        $v0, $zero, L_801EA428
    if (ctx->r2 == 0) {
        // 0x801EA400: lw          $t6, 0x4($v1)
        ctx->r14 = MEM_W(ctx->r3, 0X4);
            goto L_801EA428;
    }
    goto skip_0;
    // 0x801EA400: lw          $t6, 0x4($v1)
    ctx->r14 = MEM_W(ctx->r3, 0X4);
    skip_0:
    // 0x801EA404: beq         $v0, $at, L_801EA4E4
    if (ctx->r2 == ctx->r1) {
        // 0x801EA408: addiu       $at, $zero, 0x2
        ctx->r1 = ADD32(0, 0X2);
            goto L_801EA4E4;
    }
    // 0x801EA408: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x801EA40C: beq         $v0, $at, L_801EA5A4
    if (ctx->r2 == ctx->r1) {
        // 0x801EA410: addiu       $at, $zero, 0x3
        ctx->r1 = ADD32(0, 0X3);
            goto L_801EA5A4;
    }
    // 0x801EA410: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x801EA414: beql        $v0, $at, L_801EA66C
    if (ctx->r2 == ctx->r1) {
        // 0x801EA418: lw          $v0, 0x8($v1)
        ctx->r2 = MEM_W(ctx->r3, 0X8);
            goto L_801EA66C;
    }
    goto skip_1;
    // 0x801EA418: lw          $v0, 0x8($v1)
    ctx->r2 = MEM_W(ctx->r3, 0X8);
    skip_1:
    // 0x801EA41C: jr          $ra
    // 0x801EA420: nop

    return;
    // 0x801EA420: nop

    // 0x801EA424: lw          $t6, 0x4($v1)
    ctx->r14 = MEM_W(ctx->r3, 0X4);
L_801EA428:
    // 0x801EA428: lw          $t7, 0x8($v1)
    ctx->r15 = MEM_W(ctx->r3, 0X8);
    // 0x801EA42C: lui         $at, 0x437F
    ctx->r1 = S32(0X437F << 16);
    // 0x801EA430: mtc1        $t6, $f4
    ctx->f4.u32l = ctx->r14;
    // 0x801EA434: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x801EA438: mtc1        $t7, $f16
    ctx->f16.u32l = ctx->r15;
    // 0x801EA43C: cvt.s.w     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
    // 0x801EA440: addiu       $t9, $zero, 0x1
    ctx->r25 = ADD32(0, 0X1);
    // 0x801EA444: addiu       $a0, $zero, 0xFF
    ctx->r4 = ADD32(0, 0XFF);
    // 0x801EA448: lui         $at, 0x4F00
    ctx->r1 = S32(0X4F00 << 16);
    // 0x801EA44C: cvt.s.w     $f18, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    ctx->f18.fl = CVT_S_W(ctx->f16.u32l);
    // 0x801EA450: mul.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = MUL_S(ctx->f6.fl, ctx->f8.fl);
    // 0x801EA454: div.s       $f4, $f10, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f4.fl = DIV_S(ctx->f10.fl, ctx->f18.fl);
    // 0x801EA458: cfc1        $t8, $FpcCsr
    ctx->r24 = get_cop1_cs();
    // 0x801EA45C: ctc1        $t9, $FpcCsr
    set_cop1_cs(ctx->r25);
    // 0x801EA460: nop

    // 0x801EA464: cvt.w.s     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.u32l = CVT_W_S(ctx->f4.fl);
    // 0x801EA468: cfc1        $t9, $FpcCsr
    ctx->r25 = get_cop1_cs();
    // 0x801EA46C: nop

    // 0x801EA470: andi        $t9, $t9, 0x78
    ctx->r25 = ctx->r25 & 0X78;
    // 0x801EA474: beql        $t9, $zero, L_801EA4C4
    if (ctx->r25 == 0) {
        // 0x801EA478: mfc1        $t9, $f6
        ctx->r25 = (int32_t)ctx->f6.u32l;
            goto L_801EA4C4;
    }
    goto skip_2;
    // 0x801EA478: mfc1        $t9, $f6
    ctx->r25 = (int32_t)ctx->f6.u32l;
    skip_2:
    // 0x801EA47C: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x801EA480: addiu       $t9, $zero, 0x1
    ctx->r25 = ADD32(0, 0X1);
    // 0x801EA484: sub.s       $f6, $f4, $f6
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f6.fl = ctx->f4.fl - ctx->f6.fl;
    // 0x801EA488: ctc1        $t9, $FpcCsr
    set_cop1_cs(ctx->r25);
    // 0x801EA48C: nop

    // 0x801EA490: cvt.w.s     $f6, $f6
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 6);
    ctx->f6.u32l = CVT_W_S(ctx->f6.fl);
    // 0x801EA494: cfc1        $t9, $FpcCsr
    ctx->r25 = get_cop1_cs();
    // 0x801EA498: nop

    // 0x801EA49C: andi        $t9, $t9, 0x78
    ctx->r25 = ctx->r25 & 0X78;
    // 0x801EA4A0: bne         $t9, $zero, L_801EA4B8
    if (ctx->r25 != 0) {
        // 0x801EA4A4: nop
    
            goto L_801EA4B8;
    }
    // 0x801EA4A4: nop

    // 0x801EA4A8: mfc1        $t9, $f6
    ctx->r25 = (int32_t)ctx->f6.u32l;
    // 0x801EA4AC: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x801EA4B0: b           L_801EA4D0
    // 0x801EA4B4: or          $t9, $t9, $at
    ctx->r25 = ctx->r25 | ctx->r1;
        goto L_801EA4D0;
    // 0x801EA4B4: or          $t9, $t9, $at
    ctx->r25 = ctx->r25 | ctx->r1;
L_801EA4B8:
    // 0x801EA4B8: b           L_801EA4D0
    // 0x801EA4BC: addiu       $t9, $zero, -0x1
    ctx->r25 = ADD32(0, -0X1);
        goto L_801EA4D0;
    // 0x801EA4BC: addiu       $t9, $zero, -0x1
    ctx->r25 = ADD32(0, -0X1);
    // 0x801EA4C0: mfc1        $t9, $f6
    ctx->r25 = (int32_t)ctx->f6.u32l;
L_801EA4C4:
    // 0x801EA4C4: nop

    // 0x801EA4C8: bltz        $t9, L_801EA4B8
    if (SIGNED(ctx->r25) < 0) {
        // 0x801EA4CC: nop
    
            goto L_801EA4B8;
    }
    // 0x801EA4CC: nop

L_801EA4D0:
    // 0x801EA4D0: ctc1        $t8, $FpcCsr
    set_cop1_cs(ctx->r24);
    // 0x801EA4D4: sh          $t9, 0xC($v1)
    MEM_H(0XC, ctx->r3) = ctx->r25;
    // 0x801EA4D8: sh          $a0, 0xE($v1)
    MEM_H(0XE, ctx->r3) = ctx->r4;
    // 0x801EA4DC: jr          $ra
    // 0x801EA4E0: sh          $zero, 0x10($v1)
    MEM_H(0X10, ctx->r3) = 0;
    return;
    // 0x801EA4E0: sh          $zero, 0x10($v1)
    MEM_H(0X10, ctx->r3) = 0;
L_801EA4E4:
    // 0x801EA4E4: lw          $t0, 0x4($v1)
    ctx->r8 = MEM_W(ctx->r3, 0X4);
    // 0x801EA4E8: lw          $t1, 0x8($v1)
    ctx->r9 = MEM_W(ctx->r3, 0X8);
    // 0x801EA4EC: lui         $at, 0x437F
    ctx->r1 = S32(0X437F << 16);
    // 0x801EA4F0: mtc1        $t0, $f8
    ctx->f8.u32l = ctx->r8;
    // 0x801EA4F4: mtc1        $at, $f10
    ctx->f10.u32l = ctx->r1;
    // 0x801EA4F8: mtc1        $t1, $f4
    ctx->f4.u32l = ctx->r9;
    // 0x801EA4FC: cvt.s.w     $f16, $f8
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 8);
    ctx->f16.fl = CVT_S_W(ctx->f8.u32l);
    // 0x801EA500: addiu       $t3, $zero, 0x1
    ctx->r11 = ADD32(0, 0X1);
    // 0x801EA504: addiu       $a0, $zero, 0xFF
    ctx->r4 = ADD32(0, 0XFF);
    // 0x801EA508: sh          $a0, 0xC($v1)
    MEM_H(0XC, ctx->r3) = ctx->r4;
    // 0x801EA50C: sh          $a0, 0xE($v1)
    MEM_H(0XE, ctx->r3) = ctx->r4;
    // 0x801EA510: cvt.s.w     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
    // 0x801EA514: mul.s       $f18, $f16, $f10
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f18.fl = MUL_S(ctx->f16.fl, ctx->f10.fl);
    // 0x801EA518: lui         $at, 0x4F00
    ctx->r1 = S32(0X4F00 << 16);
    // 0x801EA51C: div.s       $f8, $f18, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = DIV_S(ctx->f18.fl, ctx->f6.fl);
    // 0x801EA520: cfc1        $t2, $FpcCsr
    ctx->r10 = get_cop1_cs();
    // 0x801EA524: ctc1        $t3, $FpcCsr
    set_cop1_cs(ctx->r11);
    // 0x801EA528: nop

    // 0x801EA52C: cvt.w.s     $f16, $f8
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 8);
    ctx->f16.u32l = CVT_W_S(ctx->f8.fl);
    // 0x801EA530: cfc1        $t3, $FpcCsr
    ctx->r11 = get_cop1_cs();
    // 0x801EA534: nop

    // 0x801EA538: andi        $t3, $t3, 0x78
    ctx->r11 = ctx->r11 & 0X78;
    // 0x801EA53C: beql        $t3, $zero, L_801EA58C
    if (ctx->r11 == 0) {
        // 0x801EA540: mfc1        $t3, $f16
        ctx->r11 = (int32_t)ctx->f16.u32l;
            goto L_801EA58C;
    }
    goto skip_3;
    // 0x801EA540: mfc1        $t3, $f16
    ctx->r11 = (int32_t)ctx->f16.u32l;
    skip_3:
    // 0x801EA544: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
    // 0x801EA548: addiu       $t3, $zero, 0x1
    ctx->r11 = ADD32(0, 0X1);
    // 0x801EA54C: sub.s       $f16, $f8, $f16
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f16.fl = ctx->f8.fl - ctx->f16.fl;
    // 0x801EA550: ctc1        $t3, $FpcCsr
    set_cop1_cs(ctx->r11);
    // 0x801EA554: nop

    // 0x801EA558: cvt.w.s     $f16, $f16
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 16);
    ctx->f16.u32l = CVT_W_S(ctx->f16.fl);
    // 0x801EA55C: cfc1        $t3, $FpcCsr
    ctx->r11 = get_cop1_cs();
    // 0x801EA560: nop

    // 0x801EA564: andi        $t3, $t3, 0x78
    ctx->r11 = ctx->r11 & 0X78;
    // 0x801EA568: bne         $t3, $zero, L_801EA580
    if (ctx->r11 != 0) {
        // 0x801EA56C: nop
    
            goto L_801EA580;
    }
    // 0x801EA56C: nop

    // 0x801EA570: mfc1        $t3, $f16
    ctx->r11 = (int32_t)ctx->f16.u32l;
    // 0x801EA574: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x801EA578: b           L_801EA598
    // 0x801EA57C: or          $t3, $t3, $at
    ctx->r11 = ctx->r11 | ctx->r1;
        goto L_801EA598;
    // 0x801EA57C: or          $t3, $t3, $at
    ctx->r11 = ctx->r11 | ctx->r1;
L_801EA580:
    // 0x801EA580: b           L_801EA598
    // 0x801EA584: addiu       $t3, $zero, -0x1
    ctx->r11 = ADD32(0, -0X1);
        goto L_801EA598;
    // 0x801EA584: addiu       $t3, $zero, -0x1
    ctx->r11 = ADD32(0, -0X1);
    // 0x801EA588: mfc1        $t3, $f16
    ctx->r11 = (int32_t)ctx->f16.u32l;
L_801EA58C:
    // 0x801EA58C: nop

    // 0x801EA590: bltz        $t3, L_801EA580
    if (SIGNED(ctx->r11) < 0) {
        // 0x801EA594: nop
    
            goto L_801EA580;
    }
    // 0x801EA594: nop

L_801EA598:
    // 0x801EA598: ctc1        $t2, $FpcCsr
    set_cop1_cs(ctx->r10);
    // 0x801EA59C: jr          $ra
    // 0x801EA5A0: sh          $t3, 0x10($v1)
    MEM_H(0X10, ctx->r3) = ctx->r11;
    return;
    // 0x801EA5A0: sh          $t3, 0x10($v1)
    MEM_H(0X10, ctx->r3) = ctx->r11;
L_801EA5A4:
    // 0x801EA5A4: lw          $v0, 0x8($v1)
    ctx->r2 = MEM_W(ctx->r3, 0X8);
    // 0x801EA5A8: lw          $t4, 0x4($v1)
    ctx->r12 = MEM_W(ctx->r3, 0X4);
    // 0x801EA5AC: lui         $at, 0x437F
    ctx->r1 = S32(0X437F << 16);
    // 0x801EA5B0: mtc1        $at, $f18
    ctx->f18.u32l = ctx->r1;
    // 0x801EA5B4: subu        $t5, $v0, $t4
    ctx->r13 = SUB32(ctx->r2, ctx->r12);
    // 0x801EA5B8: mtc1        $t5, $f10
    ctx->f10.u32l = ctx->r13;
    // 0x801EA5BC: mtc1        $v0, $f8
    ctx->f8.u32l = ctx->r2;
    // 0x801EA5C0: addiu       $t7, $zero, 0x1
    ctx->r15 = ADD32(0, 0X1);
    // 0x801EA5C4: cvt.s.w     $f4, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    ctx->f4.fl = CVT_S_W(ctx->f10.u32l);
    // 0x801EA5C8: addiu       $a0, $zero, 0xFF
    ctx->r4 = ADD32(0, 0XFF);
    // 0x801EA5CC: sh          $a0, 0xC($v1)
    MEM_H(0XC, ctx->r3) = ctx->r4;
    // 0x801EA5D0: sh          $a0, 0xE($v1)
    MEM_H(0XE, ctx->r3) = ctx->r4;
    // 0x801EA5D4: lui         $at, 0x4F00
    ctx->r1 = S32(0X4F00 << 16);
    // 0x801EA5D8: cvt.s.w     $f16, $f8
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 8);
    ctx->f16.fl = CVT_S_W(ctx->f8.u32l);
    // 0x801EA5DC: mul.s       $f6, $f4, $f18
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f6.fl = MUL_S(ctx->f4.fl, ctx->f18.fl);
    // 0x801EA5E0: div.s       $f10, $f6, $f16
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f10.fl = DIV_S(ctx->f6.fl, ctx->f16.fl);
    // 0x801EA5E4: cfc1        $t6, $FpcCsr
    ctx->r14 = get_cop1_cs();
    // 0x801EA5E8: ctc1        $t7, $FpcCsr
    set_cop1_cs(ctx->r15);
    // 0x801EA5EC: nop

    // 0x801EA5F0: cvt.w.s     $f4, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    ctx->f4.u32l = CVT_W_S(ctx->f10.fl);
    // 0x801EA5F4: cfc1        $t7, $FpcCsr
    ctx->r15 = get_cop1_cs();
    // 0x801EA5F8: nop

    // 0x801EA5FC: andi        $t7, $t7, 0x78
    ctx->r15 = ctx->r15 & 0X78;
    // 0x801EA600: beql        $t7, $zero, L_801EA650
    if (ctx->r15 == 0) {
        // 0x801EA604: mfc1        $t7, $f4
        ctx->r15 = (int32_t)ctx->f4.u32l;
            goto L_801EA650;
    }
    goto skip_4;
    // 0x801EA604: mfc1        $t7, $f4
    ctx->r15 = (int32_t)ctx->f4.u32l;
    skip_4:
    // 0x801EA608: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x801EA60C: addiu       $t7, $zero, 0x1
    ctx->r15 = ADD32(0, 0X1);
    // 0x801EA610: sub.s       $f4, $f10, $f4
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f4.fl = ctx->f10.fl - ctx->f4.fl;
    // 0x801EA614: ctc1        $t7, $FpcCsr
    set_cop1_cs(ctx->r15);
    // 0x801EA618: nop

    // 0x801EA61C: cvt.w.s     $f4, $f4
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 4);
    ctx->f4.u32l = CVT_W_S(ctx->f4.fl);
    // 0x801EA620: cfc1        $t7, $FpcCsr
    ctx->r15 = get_cop1_cs();
    // 0x801EA624: nop

    // 0x801EA628: andi        $t7, $t7, 0x78
    ctx->r15 = ctx->r15 & 0X78;
    // 0x801EA62C: bne         $t7, $zero, L_801EA644
    if (ctx->r15 != 0) {
        // 0x801EA630: nop
    
            goto L_801EA644;
    }
    // 0x801EA630: nop

    // 0x801EA634: mfc1        $t7, $f4
    ctx->r15 = (int32_t)ctx->f4.u32l;
    // 0x801EA638: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x801EA63C: b           L_801EA65C
    // 0x801EA640: or          $t7, $t7, $at
    ctx->r15 = ctx->r15 | ctx->r1;
        goto L_801EA65C;
    // 0x801EA640: or          $t7, $t7, $at
    ctx->r15 = ctx->r15 | ctx->r1;
L_801EA644:
    // 0x801EA644: b           L_801EA65C
    // 0x801EA648: addiu       $t7, $zero, -0x1
    ctx->r15 = ADD32(0, -0X1);
        goto L_801EA65C;
    // 0x801EA648: addiu       $t7, $zero, -0x1
    ctx->r15 = ADD32(0, -0X1);
    // 0x801EA64C: mfc1        $t7, $f4
    ctx->r15 = (int32_t)ctx->f4.u32l;
L_801EA650:
    // 0x801EA650: nop

    // 0x801EA654: bltz        $t7, L_801EA644
    if (SIGNED(ctx->r15) < 0) {
        // 0x801EA658: nop
    
            goto L_801EA644;
    }
    // 0x801EA658: nop

L_801EA65C:
    // 0x801EA65C: ctc1        $t6, $FpcCsr
    set_cop1_cs(ctx->r14);
    // 0x801EA660: jr          $ra
    // 0x801EA664: sh          $t7, 0x10($v1)
    MEM_H(0X10, ctx->r3) = ctx->r15;
    return;
    // 0x801EA664: sh          $t7, 0x10($v1)
    MEM_H(0X10, ctx->r3) = ctx->r15;
    // 0x801EA668: lw          $v0, 0x8($v1)
    ctx->r2 = MEM_W(ctx->r3, 0X8);
L_801EA66C:
    // 0x801EA66C: lw          $t8, 0x4($v1)
    ctx->r24 = MEM_W(ctx->r3, 0X4);
    // 0x801EA670: lui         $at, 0x437F
    ctx->r1 = S32(0X437F << 16);
    // 0x801EA674: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x801EA678: subu        $t9, $v0, $t8
    ctx->r25 = SUB32(ctx->r2, ctx->r24);
    // 0x801EA67C: mtc1        $t9, $f18
    ctx->f18.u32l = ctx->r25;
    // 0x801EA680: mtc1        $v0, $f10
    ctx->f10.u32l = ctx->r2;
    // 0x801EA684: addiu       $t1, $zero, 0x1
    ctx->r9 = ADD32(0, 0X1);
    // 0x801EA688: cvt.s.w     $f8, $f18
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 18);
    ctx->f8.fl = CVT_S_W(ctx->f18.u32l);
    // 0x801EA68C: addiu       $a0, $zero, 0xFF
    ctx->r4 = ADD32(0, 0XFF);
    // 0x801EA690: lui         $at, 0x4F00
    ctx->r1 = S32(0X4F00 << 16);
    // 0x801EA694: cvt.s.w     $f4, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    ctx->f4.fl = CVT_S_W(ctx->f10.u32l);
    // 0x801EA698: mul.s       $f16, $f8, $f6
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f16.fl = MUL_S(ctx->f8.fl, ctx->f6.fl);
    // 0x801EA69C: div.s       $f18, $f16, $f4
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f18.fl = DIV_S(ctx->f16.fl, ctx->f4.fl);
    // 0x801EA6A0: cfc1        $t0, $FpcCsr
    ctx->r8 = get_cop1_cs();
    // 0x801EA6A4: ctc1        $t1, $FpcCsr
    set_cop1_cs(ctx->r9);
    // 0x801EA6A8: nop

    // 0x801EA6AC: cvt.w.s     $f8, $f18
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 18);
    ctx->f8.u32l = CVT_W_S(ctx->f18.fl);
    // 0x801EA6B0: cfc1        $t1, $FpcCsr
    ctx->r9 = get_cop1_cs();
    // 0x801EA6B4: nop

    // 0x801EA6B8: andi        $t1, $t1, 0x78
    ctx->r9 = ctx->r9 & 0X78;
    // 0x801EA6BC: beql        $t1, $zero, L_801EA70C
    if (ctx->r9 == 0) {
        // 0x801EA6C0: mfc1        $t1, $f8
        ctx->r9 = (int32_t)ctx->f8.u32l;
            goto L_801EA70C;
    }
    goto skip_5;
    // 0x801EA6C0: mfc1        $t1, $f8
    ctx->r9 = (int32_t)ctx->f8.u32l;
    skip_5:
    // 0x801EA6C4: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x801EA6C8: addiu       $t1, $zero, 0x1
    ctx->r9 = ADD32(0, 0X1);
    // 0x801EA6CC: sub.s       $f8, $f18, $f8
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f8.fl = ctx->f18.fl - ctx->f8.fl;
    // 0x801EA6D0: ctc1        $t1, $FpcCsr
    set_cop1_cs(ctx->r9);
    // 0x801EA6D4: nop

    // 0x801EA6D8: cvt.w.s     $f8, $f8
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 8);
    ctx->f8.u32l = CVT_W_S(ctx->f8.fl);
    // 0x801EA6DC: cfc1        $t1, $FpcCsr
    ctx->r9 = get_cop1_cs();
    // 0x801EA6E0: nop

    // 0x801EA6E4: andi        $t1, $t1, 0x78
    ctx->r9 = ctx->r9 & 0X78;
    // 0x801EA6E8: bne         $t1, $zero, L_801EA700
    if (ctx->r9 != 0) {
        // 0x801EA6EC: nop
    
            goto L_801EA700;
    }
    // 0x801EA6EC: nop

    // 0x801EA6F0: mfc1        $t1, $f8
    ctx->r9 = (int32_t)ctx->f8.u32l;
    // 0x801EA6F4: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x801EA6F8: b           L_801EA718
    // 0x801EA6FC: or          $t1, $t1, $at
    ctx->r9 = ctx->r9 | ctx->r1;
        goto L_801EA718;
    // 0x801EA6FC: or          $t1, $t1, $at
    ctx->r9 = ctx->r9 | ctx->r1;
L_801EA700:
    // 0x801EA700: b           L_801EA718
    // 0x801EA704: addiu       $t1, $zero, -0x1
    ctx->r9 = ADD32(0, -0X1);
        goto L_801EA718;
    // 0x801EA704: addiu       $t1, $zero, -0x1
    ctx->r9 = ADD32(0, -0X1);
    // 0x801EA708: mfc1        $t1, $f8
    ctx->r9 = (int32_t)ctx->f8.u32l;
L_801EA70C:
    // 0x801EA70C: nop

    // 0x801EA710: bltz        $t1, L_801EA700
    if (SIGNED(ctx->r9) < 0) {
        // 0x801EA714: nop
    
            goto L_801EA700;
    }
    // 0x801EA714: nop

L_801EA718:
    // 0x801EA718: ctc1        $t0, $FpcCsr
    set_cop1_cs(ctx->r8);
    // 0x801EA71C: sh          $t1, 0xC($v1)
    MEM_H(0XC, ctx->r3) = ctx->r9;
    // 0x801EA720: sh          $a0, 0xE($v1)
    MEM_H(0XE, ctx->r3) = ctx->r4;
    // 0x801EA724: sh          $zero, 0x10($v1)
    MEM_H(0X10, ctx->r3) = 0;
    // 0x801EA728: jr          $ra
    // 0x801EA72C: nop

    return;
    // 0x801EA72C: nop

;}
RECOMP_FUNC void func_801EA730(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801EA730: lui         $v1, 0x8023
    ctx->r3 = S32(0X8023 << 16);
    // 0x801EA734: addiu       $v1, $v1, -0x7588
    ctx->r3 = ADD32(ctx->r3, -0X7588);
    // 0x801EA738: lh          $v0, 0x2($v1)
    ctx->r2 = MEM_H(ctx->r3, 0X2);
    // 0x801EA73C: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x801EA740: beql        $v0, $zero, L_801EA774
    if (ctx->r2 == 0) {
        // 0x801EA744: lw          $t6, 0x4($v1)
        ctx->r14 = MEM_W(ctx->r3, 0X4);
            goto L_801EA774;
    }
    goto skip_0;
    // 0x801EA744: lw          $t6, 0x4($v1)
    ctx->r14 = MEM_W(ctx->r3, 0X4);
    skip_0:
    // 0x801EA748: beq         $v0, $at, L_801EA82C
    if (ctx->r2 == ctx->r1) {
        // 0x801EA74C: addiu       $t4, $zero, 0xFF
        ctx->r12 = ADD32(0, 0XFF);
            goto L_801EA82C;
    }
    // 0x801EA74C: addiu       $t4, $zero, 0xFF
    ctx->r12 = ADD32(0, 0XFF);
    // 0x801EA750: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x801EA754: beq         $v0, $at, L_801EA8E8
    if (ctx->r2 == ctx->r1) {
        // 0x801EA758: addiu       $t9, $zero, 0xFF
        ctx->r25 = ADD32(0, 0XFF);
            goto L_801EA8E8;
    }
    // 0x801EA758: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x801EA75C: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x801EA760: beql        $v0, $at, L_801EA9AC
    if (ctx->r2 == ctx->r1) {
        // 0x801EA764: lw          $v0, 0x8($v1)
        ctx->r2 = MEM_W(ctx->r3, 0X8);
            goto L_801EA9AC;
    }
    goto skip_1;
    // 0x801EA764: lw          $v0, 0x8($v1)
    ctx->r2 = MEM_W(ctx->r3, 0X8);
    skip_1:
    // 0x801EA768: jr          $ra
    // 0x801EA76C: nop

    return;
    // 0x801EA76C: nop

    // 0x801EA770: lw          $t6, 0x4($v1)
    ctx->r14 = MEM_W(ctx->r3, 0X4);
L_801EA774:
    // 0x801EA774: lw          $t7, 0x8($v1)
    ctx->r15 = MEM_W(ctx->r3, 0X8);
    // 0x801EA778: lui         $at, 0x437F
    ctx->r1 = S32(0X437F << 16);
    // 0x801EA77C: mtc1        $t6, $f4
    ctx->f4.u32l = ctx->r14;
    // 0x801EA780: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x801EA784: mtc1        $t7, $f16
    ctx->f16.u32l = ctx->r15;
    // 0x801EA788: cvt.s.w     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
    // 0x801EA78C: addiu       $t9, $zero, 0x1
    ctx->r25 = ADD32(0, 0X1);
    // 0x801EA790: sh          $zero, 0xC($v1)
    MEM_H(0XC, ctx->r3) = 0;
    // 0x801EA794: lui         $at, 0x4F00
    ctx->r1 = S32(0X4F00 << 16);
    // 0x801EA798: cvt.s.w     $f18, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    ctx->f18.fl = CVT_S_W(ctx->f16.u32l);
    // 0x801EA79C: mul.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = MUL_S(ctx->f6.fl, ctx->f8.fl);
    // 0x801EA7A0: div.s       $f4, $f10, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f4.fl = DIV_S(ctx->f10.fl, ctx->f18.fl);
    // 0x801EA7A4: cfc1        $t8, $FpcCsr
    ctx->r24 = get_cop1_cs();
    // 0x801EA7A8: ctc1        $t9, $FpcCsr
    set_cop1_cs(ctx->r25);
    // 0x801EA7AC: nop

    // 0x801EA7B0: cvt.w.s     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.u32l = CVT_W_S(ctx->f4.fl);
    // 0x801EA7B4: cfc1        $t9, $FpcCsr
    ctx->r25 = get_cop1_cs();
    // 0x801EA7B8: nop

    // 0x801EA7BC: andi        $t9, $t9, 0x78
    ctx->r25 = ctx->r25 & 0X78;
    // 0x801EA7C0: beql        $t9, $zero, L_801EA810
    if (ctx->r25 == 0) {
        // 0x801EA7C4: mfc1        $t9, $f6
        ctx->r25 = (int32_t)ctx->f6.u32l;
            goto L_801EA810;
    }
    goto skip_2;
    // 0x801EA7C4: mfc1        $t9, $f6
    ctx->r25 = (int32_t)ctx->f6.u32l;
    skip_2:
    // 0x801EA7C8: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x801EA7CC: addiu       $t9, $zero, 0x1
    ctx->r25 = ADD32(0, 0X1);
    // 0x801EA7D0: sub.s       $f6, $f4, $f6
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f6.fl = ctx->f4.fl - ctx->f6.fl;
    // 0x801EA7D4: ctc1        $t9, $FpcCsr
    set_cop1_cs(ctx->r25);
    // 0x801EA7D8: nop

    // 0x801EA7DC: cvt.w.s     $f6, $f6
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 6);
    ctx->f6.u32l = CVT_W_S(ctx->f6.fl);
    // 0x801EA7E0: cfc1        $t9, $FpcCsr
    ctx->r25 = get_cop1_cs();
    // 0x801EA7E4: nop

    // 0x801EA7E8: andi        $t9, $t9, 0x78
    ctx->r25 = ctx->r25 & 0X78;
    // 0x801EA7EC: bne         $t9, $zero, L_801EA804
    if (ctx->r25 != 0) {
        // 0x801EA7F0: nop
    
            goto L_801EA804;
    }
    // 0x801EA7F0: nop

    // 0x801EA7F4: mfc1        $t9, $f6
    ctx->r25 = (int32_t)ctx->f6.u32l;
    // 0x801EA7F8: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x801EA7FC: b           L_801EA81C
    // 0x801EA800: or          $t9, $t9, $at
    ctx->r25 = ctx->r25 | ctx->r1;
        goto L_801EA81C;
    // 0x801EA800: or          $t9, $t9, $at
    ctx->r25 = ctx->r25 | ctx->r1;
L_801EA804:
    // 0x801EA804: b           L_801EA81C
    // 0x801EA808: addiu       $t9, $zero, -0x1
    ctx->r25 = ADD32(0, -0X1);
        goto L_801EA81C;
    // 0x801EA808: addiu       $t9, $zero, -0x1
    ctx->r25 = ADD32(0, -0X1);
    // 0x801EA80C: mfc1        $t9, $f6
    ctx->r25 = (int32_t)ctx->f6.u32l;
L_801EA810:
    // 0x801EA810: nop

    // 0x801EA814: bltz        $t9, L_801EA804
    if (SIGNED(ctx->r25) < 0) {
        // 0x801EA818: nop
    
            goto L_801EA804;
    }
    // 0x801EA818: nop

L_801EA81C:
    // 0x801EA81C: ctc1        $t8, $FpcCsr
    set_cop1_cs(ctx->r24);
    // 0x801EA820: sh          $t9, 0xE($v1)
    MEM_H(0XE, ctx->r3) = ctx->r25;
    // 0x801EA824: jr          $ra
    // 0x801EA828: sh          $zero, 0x10($v1)
    MEM_H(0X10, ctx->r3) = 0;
    return;
    // 0x801EA828: sh          $zero, 0x10($v1)
    MEM_H(0X10, ctx->r3) = 0;
L_801EA82C:
    // 0x801EA82C: lw          $t0, 0x4($v1)
    ctx->r8 = MEM_W(ctx->r3, 0X4);
    // 0x801EA830: lw          $t1, 0x8($v1)
    ctx->r9 = MEM_W(ctx->r3, 0X8);
    // 0x801EA834: lui         $at, 0x437F
    ctx->r1 = S32(0X437F << 16);
    // 0x801EA838: mtc1        $t0, $f8
    ctx->f8.u32l = ctx->r8;
    // 0x801EA83C: mtc1        $at, $f10
    ctx->f10.u32l = ctx->r1;
    // 0x801EA840: mtc1        $t1, $f4
    ctx->f4.u32l = ctx->r9;
    // 0x801EA844: cvt.s.w     $f16, $f8
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 8);
    ctx->f16.fl = CVT_S_W(ctx->f8.u32l);
    // 0x801EA848: addiu       $t3, $zero, 0x1
    ctx->r11 = ADD32(0, 0X1);
    // 0x801EA84C: lui         $at, 0x4F00
    ctx->r1 = S32(0X4F00 << 16);
    // 0x801EA850: cvt.s.w     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
    // 0x801EA854: mul.s       $f18, $f16, $f10
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f18.fl = MUL_S(ctx->f16.fl, ctx->f10.fl);
    // 0x801EA858: div.s       $f8, $f18, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = DIV_S(ctx->f18.fl, ctx->f6.fl);
    // 0x801EA85C: cfc1        $t2, $FpcCsr
    ctx->r10 = get_cop1_cs();
    // 0x801EA860: ctc1        $t3, $FpcCsr
    set_cop1_cs(ctx->r11);
    // 0x801EA864: nop

    // 0x801EA868: cvt.w.s     $f16, $f8
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 8);
    ctx->f16.u32l = CVT_W_S(ctx->f8.fl);
    // 0x801EA86C: cfc1        $t3, $FpcCsr
    ctx->r11 = get_cop1_cs();
    // 0x801EA870: nop

    // 0x801EA874: andi        $t3, $t3, 0x78
    ctx->r11 = ctx->r11 & 0X78;
    // 0x801EA878: beql        $t3, $zero, L_801EA8C8
    if (ctx->r11 == 0) {
        // 0x801EA87C: mfc1        $t3, $f16
        ctx->r11 = (int32_t)ctx->f16.u32l;
            goto L_801EA8C8;
    }
    goto skip_3;
    // 0x801EA87C: mfc1        $t3, $f16
    ctx->r11 = (int32_t)ctx->f16.u32l;
    skip_3:
    // 0x801EA880: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
    // 0x801EA884: addiu       $t3, $zero, 0x1
    ctx->r11 = ADD32(0, 0X1);
    // 0x801EA888: sub.s       $f16, $f8, $f16
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f16.fl = ctx->f8.fl - ctx->f16.fl;
    // 0x801EA88C: ctc1        $t3, $FpcCsr
    set_cop1_cs(ctx->r11);
    // 0x801EA890: nop

    // 0x801EA894: cvt.w.s     $f16, $f16
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 16);
    ctx->f16.u32l = CVT_W_S(ctx->f16.fl);
    // 0x801EA898: cfc1        $t3, $FpcCsr
    ctx->r11 = get_cop1_cs();
    // 0x801EA89C: nop

    // 0x801EA8A0: andi        $t3, $t3, 0x78
    ctx->r11 = ctx->r11 & 0X78;
    // 0x801EA8A4: bne         $t3, $zero, L_801EA8BC
    if (ctx->r11 != 0) {
        // 0x801EA8A8: nop
    
            goto L_801EA8BC;
    }
    // 0x801EA8A8: nop

    // 0x801EA8AC: mfc1        $t3, $f16
    ctx->r11 = (int32_t)ctx->f16.u32l;
    // 0x801EA8B0: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x801EA8B4: b           L_801EA8D4
    // 0x801EA8B8: or          $t3, $t3, $at
    ctx->r11 = ctx->r11 | ctx->r1;
        goto L_801EA8D4;
    // 0x801EA8B8: or          $t3, $t3, $at
    ctx->r11 = ctx->r11 | ctx->r1;
L_801EA8BC:
    // 0x801EA8BC: b           L_801EA8D4
    // 0x801EA8C0: addiu       $t3, $zero, -0x1
    ctx->r11 = ADD32(0, -0X1);
        goto L_801EA8D4;
    // 0x801EA8C0: addiu       $t3, $zero, -0x1
    ctx->r11 = ADD32(0, -0X1);
    // 0x801EA8C4: mfc1        $t3, $f16
    ctx->r11 = (int32_t)ctx->f16.u32l;
L_801EA8C8:
    // 0x801EA8C8: nop

    // 0x801EA8CC: bltz        $t3, L_801EA8BC
    if (SIGNED(ctx->r11) < 0) {
        // 0x801EA8D0: nop
    
            goto L_801EA8BC;
    }
    // 0x801EA8D0: nop

L_801EA8D4:
    // 0x801EA8D4: ctc1        $t2, $FpcCsr
    set_cop1_cs(ctx->r10);
    // 0x801EA8D8: sh          $t3, 0xC($v1)
    MEM_H(0XC, ctx->r3) = ctx->r11;
    // 0x801EA8DC: sh          $t4, 0xE($v1)
    MEM_H(0XE, ctx->r3) = ctx->r12;
    // 0x801EA8E0: jr          $ra
    // 0x801EA8E4: sh          $zero, 0x10($v1)
    MEM_H(0X10, ctx->r3) = 0;
    return;
    // 0x801EA8E4: sh          $zero, 0x10($v1)
    MEM_H(0X10, ctx->r3) = 0;
L_801EA8E8:
    // 0x801EA8E8: lw          $v0, 0x8($v1)
    ctx->r2 = MEM_W(ctx->r3, 0X8);
    // 0x801EA8EC: lw          $t5, 0x4($v1)
    ctx->r13 = MEM_W(ctx->r3, 0X4);
    // 0x801EA8F0: lui         $at, 0x437F
    ctx->r1 = S32(0X437F << 16);
    // 0x801EA8F4: mtc1        $at, $f18
    ctx->f18.u32l = ctx->r1;
    // 0x801EA8F8: subu        $t6, $v0, $t5
    ctx->r14 = SUB32(ctx->r2, ctx->r13);
    // 0x801EA8FC: mtc1        $t6, $f10
    ctx->f10.u32l = ctx->r14;
    // 0x801EA900: mtc1        $v0, $f8
    ctx->f8.u32l = ctx->r2;
    // 0x801EA904: addiu       $t8, $zero, 0x1
    ctx->r24 = ADD32(0, 0X1);
    // 0x801EA908: cvt.s.w     $f4, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    ctx->f4.fl = CVT_S_W(ctx->f10.u32l);
    // 0x801EA90C: lui         $at, 0x4F00
    ctx->r1 = S32(0X4F00 << 16);
    // 0x801EA910: cvt.s.w     $f16, $f8
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 8);
    ctx->f16.fl = CVT_S_W(ctx->f8.u32l);
    // 0x801EA914: mul.s       $f6, $f4, $f18
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f6.fl = MUL_S(ctx->f4.fl, ctx->f18.fl);
    // 0x801EA918: div.s       $f10, $f6, $f16
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f10.fl = DIV_S(ctx->f6.fl, ctx->f16.fl);
    // 0x801EA91C: cfc1        $t7, $FpcCsr
    ctx->r15 = get_cop1_cs();
    // 0x801EA920: ctc1        $t8, $FpcCsr
    set_cop1_cs(ctx->r24);
    // 0x801EA924: nop

    // 0x801EA928: cvt.w.s     $f4, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    ctx->f4.u32l = CVT_W_S(ctx->f10.fl);
    // 0x801EA92C: cfc1        $t8, $FpcCsr
    ctx->r24 = get_cop1_cs();
    // 0x801EA930: nop

    // 0x801EA934: andi        $t8, $t8, 0x78
    ctx->r24 = ctx->r24 & 0X78;
    // 0x801EA938: beql        $t8, $zero, L_801EA988
    if (ctx->r24 == 0) {
        // 0x801EA93C: mfc1        $t8, $f4
        ctx->r24 = (int32_t)ctx->f4.u32l;
            goto L_801EA988;
    }
    goto skip_4;
    // 0x801EA93C: mfc1        $t8, $f4
    ctx->r24 = (int32_t)ctx->f4.u32l;
    skip_4:
    // 0x801EA940: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x801EA944: addiu       $t8, $zero, 0x1
    ctx->r24 = ADD32(0, 0X1);
    // 0x801EA948: sub.s       $f4, $f10, $f4
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f4.fl = ctx->f10.fl - ctx->f4.fl;
    // 0x801EA94C: ctc1        $t8, $FpcCsr
    set_cop1_cs(ctx->r24);
    // 0x801EA950: nop

    // 0x801EA954: cvt.w.s     $f4, $f4
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 4);
    ctx->f4.u32l = CVT_W_S(ctx->f4.fl);
    // 0x801EA958: cfc1        $t8, $FpcCsr
    ctx->r24 = get_cop1_cs();
    // 0x801EA95C: nop

    // 0x801EA960: andi        $t8, $t8, 0x78
    ctx->r24 = ctx->r24 & 0X78;
    // 0x801EA964: bne         $t8, $zero, L_801EA97C
    if (ctx->r24 != 0) {
        // 0x801EA968: nop
    
            goto L_801EA97C;
    }
    // 0x801EA968: nop

    // 0x801EA96C: mfc1        $t8, $f4
    ctx->r24 = (int32_t)ctx->f4.u32l;
    // 0x801EA970: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x801EA974: b           L_801EA994
    // 0x801EA978: or          $t8, $t8, $at
    ctx->r24 = ctx->r24 | ctx->r1;
        goto L_801EA994;
    // 0x801EA978: or          $t8, $t8, $at
    ctx->r24 = ctx->r24 | ctx->r1;
L_801EA97C:
    // 0x801EA97C: b           L_801EA994
    // 0x801EA980: addiu       $t8, $zero, -0x1
    ctx->r24 = ADD32(0, -0X1);
        goto L_801EA994;
    // 0x801EA980: addiu       $t8, $zero, -0x1
    ctx->r24 = ADD32(0, -0X1);
    // 0x801EA984: mfc1        $t8, $f4
    ctx->r24 = (int32_t)ctx->f4.u32l;
L_801EA988:
    // 0x801EA988: nop

    // 0x801EA98C: bltz        $t8, L_801EA97C
    if (SIGNED(ctx->r24) < 0) {
        // 0x801EA990: nop
    
            goto L_801EA97C;
    }
    // 0x801EA990: nop

L_801EA994:
    // 0x801EA994: ctc1        $t7, $FpcCsr
    set_cop1_cs(ctx->r15);
    // 0x801EA998: sh          $t8, 0xC($v1)
    MEM_H(0XC, ctx->r3) = ctx->r24;
    // 0x801EA99C: sh          $t9, 0xE($v1)
    MEM_H(0XE, ctx->r3) = ctx->r25;
    // 0x801EA9A0: jr          $ra
    // 0x801EA9A4: sh          $zero, 0x10($v1)
    MEM_H(0X10, ctx->r3) = 0;
    return;
    // 0x801EA9A4: sh          $zero, 0x10($v1)
    MEM_H(0X10, ctx->r3) = 0;
    // 0x801EA9A8: lw          $v0, 0x8($v1)
    ctx->r2 = MEM_W(ctx->r3, 0X8);
L_801EA9AC:
    // 0x801EA9AC: lw          $t0, 0x4($v1)
    ctx->r8 = MEM_W(ctx->r3, 0X4);
    // 0x801EA9B0: lui         $at, 0x437F
    ctx->r1 = S32(0X437F << 16);
    // 0x801EA9B4: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x801EA9B8: subu        $t1, $v0, $t0
    ctx->r9 = SUB32(ctx->r2, ctx->r8);
    // 0x801EA9BC: mtc1        $t1, $f18
    ctx->f18.u32l = ctx->r9;
    // 0x801EA9C0: mtc1        $v0, $f10
    ctx->f10.u32l = ctx->r2;
    // 0x801EA9C4: addiu       $t3, $zero, 0x1
    ctx->r11 = ADD32(0, 0X1);
    // 0x801EA9C8: cvt.s.w     $f8, $f18
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 18);
    ctx->f8.fl = CVT_S_W(ctx->f18.u32l);
    // 0x801EA9CC: sh          $zero, 0xC($v1)
    MEM_H(0XC, ctx->r3) = 0;
    // 0x801EA9D0: lui         $at, 0x4F00
    ctx->r1 = S32(0X4F00 << 16);
    // 0x801EA9D4: cvt.s.w     $f4, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    ctx->f4.fl = CVT_S_W(ctx->f10.u32l);
    // 0x801EA9D8: mul.s       $f16, $f8, $f6
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f16.fl = MUL_S(ctx->f8.fl, ctx->f6.fl);
    // 0x801EA9DC: div.s       $f18, $f16, $f4
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f18.fl = DIV_S(ctx->f16.fl, ctx->f4.fl);
    // 0x801EA9E0: cfc1        $t2, $FpcCsr
    ctx->r10 = get_cop1_cs();
    // 0x801EA9E4: ctc1        $t3, $FpcCsr
    set_cop1_cs(ctx->r11);
    // 0x801EA9E8: nop

    // 0x801EA9EC: cvt.w.s     $f8, $f18
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 18);
    ctx->f8.u32l = CVT_W_S(ctx->f18.fl);
    // 0x801EA9F0: cfc1        $t3, $FpcCsr
    ctx->r11 = get_cop1_cs();
    // 0x801EA9F4: nop

    // 0x801EA9F8: andi        $t3, $t3, 0x78
    ctx->r11 = ctx->r11 & 0X78;
    // 0x801EA9FC: beql        $t3, $zero, L_801EAA4C
    if (ctx->r11 == 0) {
        // 0x801EAA00: mfc1        $t3, $f8
        ctx->r11 = (int32_t)ctx->f8.u32l;
            goto L_801EAA4C;
    }
    goto skip_5;
    // 0x801EAA00: mfc1        $t3, $f8
    ctx->r11 = (int32_t)ctx->f8.u32l;
    skip_5:
    // 0x801EAA04: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x801EAA08: addiu       $t3, $zero, 0x1
    ctx->r11 = ADD32(0, 0X1);
    // 0x801EAA0C: sub.s       $f8, $f18, $f8
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f8.fl = ctx->f18.fl - ctx->f8.fl;
    // 0x801EAA10: ctc1        $t3, $FpcCsr
    set_cop1_cs(ctx->r11);
    // 0x801EAA14: nop

    // 0x801EAA18: cvt.w.s     $f8, $f8
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 8);
    ctx->f8.u32l = CVT_W_S(ctx->f8.fl);
    // 0x801EAA1C: cfc1        $t3, $FpcCsr
    ctx->r11 = get_cop1_cs();
    // 0x801EAA20: nop

    // 0x801EAA24: andi        $t3, $t3, 0x78
    ctx->r11 = ctx->r11 & 0X78;
    // 0x801EAA28: bne         $t3, $zero, L_801EAA40
    if (ctx->r11 != 0) {
        // 0x801EAA2C: nop
    
            goto L_801EAA40;
    }
    // 0x801EAA2C: nop

    // 0x801EAA30: mfc1        $t3, $f8
    ctx->r11 = (int32_t)ctx->f8.u32l;
    // 0x801EAA34: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x801EAA38: b           L_801EAA58
    // 0x801EAA3C: or          $t3, $t3, $at
    ctx->r11 = ctx->r11 | ctx->r1;
        goto L_801EAA58;
    // 0x801EAA3C: or          $t3, $t3, $at
    ctx->r11 = ctx->r11 | ctx->r1;
L_801EAA40:
    // 0x801EAA40: b           L_801EAA58
    // 0x801EAA44: addiu       $t3, $zero, -0x1
    ctx->r11 = ADD32(0, -0X1);
        goto L_801EAA58;
    // 0x801EAA44: addiu       $t3, $zero, -0x1
    ctx->r11 = ADD32(0, -0X1);
    // 0x801EAA48: mfc1        $t3, $f8
    ctx->r11 = (int32_t)ctx->f8.u32l;
L_801EAA4C:
    // 0x801EAA4C: nop

    // 0x801EAA50: bltz        $t3, L_801EAA40
    if (SIGNED(ctx->r11) < 0) {
        // 0x801EAA54: nop
    
            goto L_801EAA40;
    }
    // 0x801EAA54: nop

L_801EAA58:
    // 0x801EAA58: ctc1        $t2, $FpcCsr
    set_cop1_cs(ctx->r10);
    // 0x801EAA5C: sh          $t3, 0xE($v1)
    MEM_H(0XE, ctx->r3) = ctx->r11;
    // 0x801EAA60: sh          $zero, 0x10($v1)
    MEM_H(0X10, ctx->r3) = 0;
    // 0x801EAA64: jr          $ra
    // 0x801EAA68: nop

    return;
    // 0x801EAA68: nop

;}
RECOMP_FUNC void func_801EAA6C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801EAA6C: lui         $v1, 0x8023
    ctx->r3 = S32(0X8023 << 16);
    // 0x801EAA70: addiu       $v1, $v1, -0x7588
    ctx->r3 = ADD32(ctx->r3, -0X7588);
    // 0x801EAA74: lh          $v0, 0x2($v1)
    ctx->r2 = MEM_H(ctx->r3, 0X2);
    // 0x801EAA78: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x801EAA7C: beql        $v0, $zero, L_801EAAA8
    if (ctx->r2 == 0) {
        // 0x801EAA80: lw          $v0, 0x8($v1)
        ctx->r2 = MEM_W(ctx->r3, 0X8);
            goto L_801EAAA8;
    }
    goto skip_0;
    // 0x801EAA80: lw          $v0, 0x8($v1)
    ctx->r2 = MEM_W(ctx->r3, 0X8);
    skip_0:
    // 0x801EAA84: beq         $v0, $at, L_801EAB68
    if (ctx->r2 == ctx->r1) {
        // 0x801EAA88: addiu       $at, $zero, 0x2
        ctx->r1 = ADD32(0, 0X2);
            goto L_801EAB68;
    }
    // 0x801EAA88: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x801EAA8C: beq         $v0, $at, L_801EAC2C
    if (ctx->r2 == ctx->r1) {
        // 0x801EAA90: addiu       $at, $zero, 0x3
        ctx->r1 = ADD32(0, 0X3);
            goto L_801EAC2C;
    }
    // 0x801EAA90: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x801EAA94: beql        $v0, $at, L_801EACF0
    if (ctx->r2 == ctx->r1) {
        // 0x801EAA98: lw          $t8, 0x4($v1)
        ctx->r24 = MEM_W(ctx->r3, 0X4);
            goto L_801EACF0;
    }
    goto skip_1;
    // 0x801EAA98: lw          $t8, 0x4($v1)
    ctx->r24 = MEM_W(ctx->r3, 0X4);
    skip_1:
    // 0x801EAA9C: jr          $ra
    // 0x801EAAA0: nop

    return;
    // 0x801EAAA0: nop

    // 0x801EAAA4: lw          $v0, 0x8($v1)
    ctx->r2 = MEM_W(ctx->r3, 0X8);
L_801EAAA8:
    // 0x801EAAA8: lw          $t6, 0x4($v1)
    ctx->r14 = MEM_W(ctx->r3, 0X4);
    // 0x801EAAAC: lui         $at, 0x4300
    ctx->r1 = S32(0X4300 << 16);
    // 0x801EAAB0: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x801EAAB4: subu        $t7, $v0, $t6
    ctx->r15 = SUB32(ctx->r2, ctx->r14);
    // 0x801EAAB8: mtc1        $t7, $f4
    ctx->f4.u32l = ctx->r15;
    // 0x801EAABC: mtc1        $v0, $f16
    ctx->f16.u32l = ctx->r2;
    // 0x801EAAC0: addiu       $t9, $zero, 0x1
    ctx->r25 = ADD32(0, 0X1);
    // 0x801EAAC4: cvt.s.w     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
    // 0x801EAAC8: addiu       $a0, $zero, 0xFF
    ctx->r4 = ADD32(0, 0XFF);
    // 0x801EAACC: sh          $a0, 0xC($v1)
    MEM_H(0XC, ctx->r3) = ctx->r4;
    // 0x801EAAD0: lui         $at, 0x4F00
    ctx->r1 = S32(0X4F00 << 16);
    // 0x801EAAD4: cvt.s.w     $f18, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    ctx->f18.fl = CVT_S_W(ctx->f16.u32l);
    // 0x801EAAD8: mul.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = MUL_S(ctx->f6.fl, ctx->f8.fl);
    // 0x801EAADC: div.s       $f4, $f10, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f4.fl = DIV_S(ctx->f10.fl, ctx->f18.fl);
    // 0x801EAAE0: cfc1        $t8, $FpcCsr
    ctx->r24 = get_cop1_cs();
    // 0x801EAAE4: ctc1        $t9, $FpcCsr
    set_cop1_cs(ctx->r25);
    // 0x801EAAE8: nop

    // 0x801EAAEC: cvt.w.s     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.u32l = CVT_W_S(ctx->f4.fl);
    // 0x801EAAF0: cfc1        $t9, $FpcCsr
    ctx->r25 = get_cop1_cs();
    // 0x801EAAF4: nop

    // 0x801EAAF8: andi        $t9, $t9, 0x78
    ctx->r25 = ctx->r25 & 0X78;
    // 0x801EAAFC: beql        $t9, $zero, L_801EAB4C
    if (ctx->r25 == 0) {
        // 0x801EAB00: mfc1        $t9, $f6
        ctx->r25 = (int32_t)ctx->f6.u32l;
            goto L_801EAB4C;
    }
    goto skip_2;
    // 0x801EAB00: mfc1        $t9, $f6
    ctx->r25 = (int32_t)ctx->f6.u32l;
    skip_2:
    // 0x801EAB04: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x801EAB08: addiu       $t9, $zero, 0x1
    ctx->r25 = ADD32(0, 0X1);
    // 0x801EAB0C: sub.s       $f6, $f4, $f6
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f6.fl = ctx->f4.fl - ctx->f6.fl;
    // 0x801EAB10: ctc1        $t9, $FpcCsr
    set_cop1_cs(ctx->r25);
    // 0x801EAB14: nop

    // 0x801EAB18: cvt.w.s     $f6, $f6
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 6);
    ctx->f6.u32l = CVT_W_S(ctx->f6.fl);
    // 0x801EAB1C: cfc1        $t9, $FpcCsr
    ctx->r25 = get_cop1_cs();
    // 0x801EAB20: nop

    // 0x801EAB24: andi        $t9, $t9, 0x78
    ctx->r25 = ctx->r25 & 0X78;
    // 0x801EAB28: bne         $t9, $zero, L_801EAB40
    if (ctx->r25 != 0) {
        // 0x801EAB2C: nop
    
            goto L_801EAB40;
    }
    // 0x801EAB2C: nop

    // 0x801EAB30: mfc1        $t9, $f6
    ctx->r25 = (int32_t)ctx->f6.u32l;
    // 0x801EAB34: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x801EAB38: b           L_801EAB58
    // 0x801EAB3C: or          $t9, $t9, $at
    ctx->r25 = ctx->r25 | ctx->r1;
        goto L_801EAB58;
    // 0x801EAB3C: or          $t9, $t9, $at
    ctx->r25 = ctx->r25 | ctx->r1;
L_801EAB40:
    // 0x801EAB40: b           L_801EAB58
    // 0x801EAB44: addiu       $t9, $zero, -0x1
    ctx->r25 = ADD32(0, -0X1);
        goto L_801EAB58;
    // 0x801EAB44: addiu       $t9, $zero, -0x1
    ctx->r25 = ADD32(0, -0X1);
    // 0x801EAB48: mfc1        $t9, $f6
    ctx->r25 = (int32_t)ctx->f6.u32l;
L_801EAB4C:
    // 0x801EAB4C: nop

    // 0x801EAB50: bltz        $t9, L_801EAB40
    if (SIGNED(ctx->r25) < 0) {
        // 0x801EAB54: nop
    
            goto L_801EAB40;
    }
    // 0x801EAB54: nop

L_801EAB58:
    // 0x801EAB58: ctc1        $t8, $FpcCsr
    set_cop1_cs(ctx->r24);
    // 0x801EAB5C: sh          $t9, 0xE($v1)
    MEM_H(0XE, ctx->r3) = ctx->r25;
    // 0x801EAB60: jr          $ra
    // 0x801EAB64: sh          $a0, 0x10($v1)
    MEM_H(0X10, ctx->r3) = ctx->r4;
    return;
    // 0x801EAB64: sh          $a0, 0x10($v1)
    MEM_H(0X10, ctx->r3) = ctx->r4;
L_801EAB68:
    // 0x801EAB68: lw          $v0, 0x8($v1)
    ctx->r2 = MEM_W(ctx->r3, 0X8);
    // 0x801EAB6C: lw          $t0, 0x4($v1)
    ctx->r8 = MEM_W(ctx->r3, 0X4);
    // 0x801EAB70: lui         $at, 0x437F
    ctx->r1 = S32(0X437F << 16);
    // 0x801EAB74: mtc1        $at, $f10
    ctx->f10.u32l = ctx->r1;
    // 0x801EAB78: subu        $t1, $v0, $t0
    ctx->r9 = SUB32(ctx->r2, ctx->r8);
    // 0x801EAB7C: mtc1        $t1, $f8
    ctx->f8.u32l = ctx->r9;
    // 0x801EAB80: mtc1        $v0, $f4
    ctx->f4.u32l = ctx->r2;
    // 0x801EAB84: addiu       $t3, $zero, 0x1
    ctx->r11 = ADD32(0, 0X1);
    // 0x801EAB88: cvt.s.w     $f16, $f8
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 8);
    ctx->f16.fl = CVT_S_W(ctx->f8.u32l);
    // 0x801EAB8C: addiu       $a0, $zero, 0xFF
    ctx->r4 = ADD32(0, 0XFF);
    // 0x801EAB90: sh          $a0, 0xC($v1)
    MEM_H(0XC, ctx->r3) = ctx->r4;
    // 0x801EAB94: sh          $zero, 0xE($v1)
    MEM_H(0XE, ctx->r3) = 0;
    // 0x801EAB98: lui         $at, 0x4F00
    ctx->r1 = S32(0X4F00 << 16);
    // 0x801EAB9C: cvt.s.w     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
    // 0x801EABA0: mul.s       $f18, $f16, $f10
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f18.fl = MUL_S(ctx->f16.fl, ctx->f10.fl);
    // 0x801EABA4: div.s       $f8, $f18, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = DIV_S(ctx->f18.fl, ctx->f6.fl);
    // 0x801EABA8: cfc1        $t2, $FpcCsr
    ctx->r10 = get_cop1_cs();
    // 0x801EABAC: ctc1        $t3, $FpcCsr
    set_cop1_cs(ctx->r11);
    // 0x801EABB0: nop

    // 0x801EABB4: cvt.w.s     $f16, $f8
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 8);
    ctx->f16.u32l = CVT_W_S(ctx->f8.fl);
    // 0x801EABB8: cfc1        $t3, $FpcCsr
    ctx->r11 = get_cop1_cs();
    // 0x801EABBC: nop

    // 0x801EABC0: andi        $t3, $t3, 0x78
    ctx->r11 = ctx->r11 & 0X78;
    // 0x801EABC4: beql        $t3, $zero, L_801EAC14
    if (ctx->r11 == 0) {
        // 0x801EABC8: mfc1        $t3, $f16
        ctx->r11 = (int32_t)ctx->f16.u32l;
            goto L_801EAC14;
    }
    goto skip_3;
    // 0x801EABC8: mfc1        $t3, $f16
    ctx->r11 = (int32_t)ctx->f16.u32l;
    skip_3:
    // 0x801EABCC: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
    // 0x801EABD0: addiu       $t3, $zero, 0x1
    ctx->r11 = ADD32(0, 0X1);
    // 0x801EABD4: sub.s       $f16, $f8, $f16
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f16.fl = ctx->f8.fl - ctx->f16.fl;
    // 0x801EABD8: ctc1        $t3, $FpcCsr
    set_cop1_cs(ctx->r11);
    // 0x801EABDC: nop

    // 0x801EABE0: cvt.w.s     $f16, $f16
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 16);
    ctx->f16.u32l = CVT_W_S(ctx->f16.fl);
    // 0x801EABE4: cfc1        $t3, $FpcCsr
    ctx->r11 = get_cop1_cs();
    // 0x801EABE8: nop

    // 0x801EABEC: andi        $t3, $t3, 0x78
    ctx->r11 = ctx->r11 & 0X78;
    // 0x801EABF0: bne         $t3, $zero, L_801EAC08
    if (ctx->r11 != 0) {
        // 0x801EABF4: nop
    
            goto L_801EAC08;
    }
    // 0x801EABF4: nop

    // 0x801EABF8: mfc1        $t3, $f16
    ctx->r11 = (int32_t)ctx->f16.u32l;
    // 0x801EABFC: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x801EAC00: b           L_801EAC20
    // 0x801EAC04: or          $t3, $t3, $at
    ctx->r11 = ctx->r11 | ctx->r1;
        goto L_801EAC20;
    // 0x801EAC04: or          $t3, $t3, $at
    ctx->r11 = ctx->r11 | ctx->r1;
L_801EAC08:
    // 0x801EAC08: b           L_801EAC20
    // 0x801EAC0C: addiu       $t3, $zero, -0x1
    ctx->r11 = ADD32(0, -0X1);
        goto L_801EAC20;
    // 0x801EAC0C: addiu       $t3, $zero, -0x1
    ctx->r11 = ADD32(0, -0X1);
    // 0x801EAC10: mfc1        $t3, $f16
    ctx->r11 = (int32_t)ctx->f16.u32l;
L_801EAC14:
    // 0x801EAC14: nop

    // 0x801EAC18: bltz        $t3, L_801EAC08
    if (SIGNED(ctx->r11) < 0) {
        // 0x801EAC1C: nop
    
            goto L_801EAC08;
    }
    // 0x801EAC1C: nop

L_801EAC20:
    // 0x801EAC20: ctc1        $t2, $FpcCsr
    set_cop1_cs(ctx->r10);
    // 0x801EAC24: jr          $ra
    // 0x801EAC28: sh          $t3, 0x10($v1)
    MEM_H(0X10, ctx->r3) = ctx->r11;
    return;
    // 0x801EAC28: sh          $t3, 0x10($v1)
    MEM_H(0X10, ctx->r3) = ctx->r11;
L_801EAC2C:
    // 0x801EAC2C: lw          $t4, 0x4($v1)
    ctx->r12 = MEM_W(ctx->r3, 0X4);
    // 0x801EAC30: lw          $t5, 0x8($v1)
    ctx->r13 = MEM_W(ctx->r3, 0X8);
    // 0x801EAC34: lui         $at, 0x437F
    ctx->r1 = S32(0X437F << 16);
    // 0x801EAC38: mtc1        $t4, $f10
    ctx->f10.u32l = ctx->r12;
    // 0x801EAC3C: mtc1        $at, $f18
    ctx->f18.u32l = ctx->r1;
    // 0x801EAC40: mtc1        $t5, $f8
    ctx->f8.u32l = ctx->r13;
    // 0x801EAC44: cvt.s.w     $f4, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    ctx->f4.fl = CVT_S_W(ctx->f10.u32l);
    // 0x801EAC48: addiu       $t7, $zero, 0x1
    ctx->r15 = ADD32(0, 0X1);
    // 0x801EAC4C: addiu       $a0, $zero, 0xFF
    ctx->r4 = ADD32(0, 0XFF);
    // 0x801EAC50: sh          $a0, 0xC($v1)
    MEM_H(0XC, ctx->r3) = ctx->r4;
    // 0x801EAC54: sh          $zero, 0xE($v1)
    MEM_H(0XE, ctx->r3) = 0;
    // 0x801EAC58: cvt.s.w     $f16, $f8
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 8);
    ctx->f16.fl = CVT_S_W(ctx->f8.u32l);
    // 0x801EAC5C: mul.s       $f6, $f4, $f18
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f6.fl = MUL_S(ctx->f4.fl, ctx->f18.fl);
    // 0x801EAC60: lui         $at, 0x4F00
    ctx->r1 = S32(0X4F00 << 16);
    // 0x801EAC64: div.s       $f10, $f6, $f16
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f10.fl = DIV_S(ctx->f6.fl, ctx->f16.fl);
    // 0x801EAC68: cfc1        $t6, $FpcCsr
    ctx->r14 = get_cop1_cs();
    // 0x801EAC6C: ctc1        $t7, $FpcCsr
    set_cop1_cs(ctx->r15);
    // 0x801EAC70: nop

    // 0x801EAC74: cvt.w.s     $f4, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    ctx->f4.u32l = CVT_W_S(ctx->f10.fl);
    // 0x801EAC78: cfc1        $t7, $FpcCsr
    ctx->r15 = get_cop1_cs();
    // 0x801EAC7C: nop

    // 0x801EAC80: andi        $t7, $t7, 0x78
    ctx->r15 = ctx->r15 & 0X78;
    // 0x801EAC84: beql        $t7, $zero, L_801EACD4
    if (ctx->r15 == 0) {
        // 0x801EAC88: mfc1        $t7, $f4
        ctx->r15 = (int32_t)ctx->f4.u32l;
            goto L_801EACD4;
    }
    goto skip_4;
    // 0x801EAC88: mfc1        $t7, $f4
    ctx->r15 = (int32_t)ctx->f4.u32l;
    skip_4:
    // 0x801EAC8C: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x801EAC90: addiu       $t7, $zero, 0x1
    ctx->r15 = ADD32(0, 0X1);
    // 0x801EAC94: sub.s       $f4, $f10, $f4
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f4.fl = ctx->f10.fl - ctx->f4.fl;
    // 0x801EAC98: ctc1        $t7, $FpcCsr
    set_cop1_cs(ctx->r15);
    // 0x801EAC9C: nop

    // 0x801EACA0: cvt.w.s     $f4, $f4
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 4);
    ctx->f4.u32l = CVT_W_S(ctx->f4.fl);
    // 0x801EACA4: cfc1        $t7, $FpcCsr
    ctx->r15 = get_cop1_cs();
    // 0x801EACA8: nop

    // 0x801EACAC: andi        $t7, $t7, 0x78
    ctx->r15 = ctx->r15 & 0X78;
    // 0x801EACB0: bne         $t7, $zero, L_801EACC8
    if (ctx->r15 != 0) {
        // 0x801EACB4: nop
    
            goto L_801EACC8;
    }
    // 0x801EACB4: nop

    // 0x801EACB8: mfc1        $t7, $f4
    ctx->r15 = (int32_t)ctx->f4.u32l;
    // 0x801EACBC: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x801EACC0: b           L_801EACE0
    // 0x801EACC4: or          $t7, $t7, $at
    ctx->r15 = ctx->r15 | ctx->r1;
        goto L_801EACE0;
    // 0x801EACC4: or          $t7, $t7, $at
    ctx->r15 = ctx->r15 | ctx->r1;
L_801EACC8:
    // 0x801EACC8: b           L_801EACE0
    // 0x801EACCC: addiu       $t7, $zero, -0x1
    ctx->r15 = ADD32(0, -0X1);
        goto L_801EACE0;
    // 0x801EACCC: addiu       $t7, $zero, -0x1
    ctx->r15 = ADD32(0, -0X1);
    // 0x801EACD0: mfc1        $t7, $f4
    ctx->r15 = (int32_t)ctx->f4.u32l;
L_801EACD4:
    // 0x801EACD4: nop

    // 0x801EACD8: bltz        $t7, L_801EACC8
    if (SIGNED(ctx->r15) < 0) {
        // 0x801EACDC: nop
    
            goto L_801EACC8;
    }
    // 0x801EACDC: nop

L_801EACE0:
    // 0x801EACE0: ctc1        $t6, $FpcCsr
    set_cop1_cs(ctx->r14);
    // 0x801EACE4: jr          $ra
    // 0x801EACE8: sh          $t7, 0x10($v1)
    MEM_H(0X10, ctx->r3) = ctx->r15;
    return;
    // 0x801EACE8: sh          $t7, 0x10($v1)
    MEM_H(0X10, ctx->r3) = ctx->r15;
    // 0x801EACEC: lw          $t8, 0x4($v1)
    ctx->r24 = MEM_W(ctx->r3, 0X4);
L_801EACF0:
    // 0x801EACF0: lw          $t9, 0x8($v1)
    ctx->r25 = MEM_W(ctx->r3, 0X8);
    // 0x801EACF4: lui         $at, 0x4300
    ctx->r1 = S32(0X4300 << 16);
    // 0x801EACF8: mtc1        $t8, $f18
    ctx->f18.u32l = ctx->r24;
    // 0x801EACFC: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x801EAD00: mtc1        $t9, $f10
    ctx->f10.u32l = ctx->r25;
    // 0x801EAD04: cvt.s.w     $f8, $f18
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 18);
    ctx->f8.fl = CVT_S_W(ctx->f18.u32l);
    // 0x801EAD08: addiu       $t1, $zero, 0x1
    ctx->r9 = ADD32(0, 0X1);
    // 0x801EAD0C: addiu       $a0, $zero, 0xFF
    ctx->r4 = ADD32(0, 0XFF);
    // 0x801EAD10: sh          $a0, 0xC($v1)
    MEM_H(0XC, ctx->r3) = ctx->r4;
    // 0x801EAD14: lui         $at, 0x4F00
    ctx->r1 = S32(0X4F00 << 16);
    // 0x801EAD18: cvt.s.w     $f4, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    ctx->f4.fl = CVT_S_W(ctx->f10.u32l);
    // 0x801EAD1C: mul.s       $f16, $f8, $f6
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f16.fl = MUL_S(ctx->f8.fl, ctx->f6.fl);
    // 0x801EAD20: div.s       $f18, $f16, $f4
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f18.fl = DIV_S(ctx->f16.fl, ctx->f4.fl);
    // 0x801EAD24: cfc1        $t0, $FpcCsr
    ctx->r8 = get_cop1_cs();
    // 0x801EAD28: ctc1        $t1, $FpcCsr
    set_cop1_cs(ctx->r9);
    // 0x801EAD2C: nop

    // 0x801EAD30: cvt.w.s     $f8, $f18
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 18);
    ctx->f8.u32l = CVT_W_S(ctx->f18.fl);
    // 0x801EAD34: cfc1        $t1, $FpcCsr
    ctx->r9 = get_cop1_cs();
    // 0x801EAD38: nop

    // 0x801EAD3C: andi        $t1, $t1, 0x78
    ctx->r9 = ctx->r9 & 0X78;
    // 0x801EAD40: beql        $t1, $zero, L_801EAD90
    if (ctx->r9 == 0) {
        // 0x801EAD44: mfc1        $t1, $f8
        ctx->r9 = (int32_t)ctx->f8.u32l;
            goto L_801EAD90;
    }
    goto skip_5;
    // 0x801EAD44: mfc1        $t1, $f8
    ctx->r9 = (int32_t)ctx->f8.u32l;
    skip_5:
    // 0x801EAD48: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x801EAD4C: addiu       $t1, $zero, 0x1
    ctx->r9 = ADD32(0, 0X1);
    // 0x801EAD50: sub.s       $f8, $f18, $f8
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f8.fl = ctx->f18.fl - ctx->f8.fl;
    // 0x801EAD54: ctc1        $t1, $FpcCsr
    set_cop1_cs(ctx->r9);
    // 0x801EAD58: nop

    // 0x801EAD5C: cvt.w.s     $f8, $f8
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 8);
    ctx->f8.u32l = CVT_W_S(ctx->f8.fl);
    // 0x801EAD60: cfc1        $t1, $FpcCsr
    ctx->r9 = get_cop1_cs();
    // 0x801EAD64: nop

    // 0x801EAD68: andi        $t1, $t1, 0x78
    ctx->r9 = ctx->r9 & 0X78;
    // 0x801EAD6C: bne         $t1, $zero, L_801EAD84
    if (ctx->r9 != 0) {
        // 0x801EAD70: nop
    
            goto L_801EAD84;
    }
    // 0x801EAD70: nop

    // 0x801EAD74: mfc1        $t1, $f8
    ctx->r9 = (int32_t)ctx->f8.u32l;
    // 0x801EAD78: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x801EAD7C: b           L_801EAD9C
    // 0x801EAD80: or          $t1, $t1, $at
    ctx->r9 = ctx->r9 | ctx->r1;
        goto L_801EAD9C;
    // 0x801EAD80: or          $t1, $t1, $at
    ctx->r9 = ctx->r9 | ctx->r1;
L_801EAD84:
    // 0x801EAD84: b           L_801EAD9C
    // 0x801EAD88: addiu       $t1, $zero, -0x1
    ctx->r9 = ADD32(0, -0X1);
        goto L_801EAD9C;
    // 0x801EAD88: addiu       $t1, $zero, -0x1
    ctx->r9 = ADD32(0, -0X1);
    // 0x801EAD8C: mfc1        $t1, $f8
    ctx->r9 = (int32_t)ctx->f8.u32l;
L_801EAD90:
    // 0x801EAD90: nop

    // 0x801EAD94: bltz        $t1, L_801EAD84
    if (SIGNED(ctx->r9) < 0) {
        // 0x801EAD98: nop
    
            goto L_801EAD84;
    }
    // 0x801EAD98: nop

L_801EAD9C:
    // 0x801EAD9C: ctc1        $t0, $FpcCsr
    set_cop1_cs(ctx->r8);
    // 0x801EADA0: sh          $t1, 0xE($v1)
    MEM_H(0XE, ctx->r3) = ctx->r9;
    // 0x801EADA4: sh          $a0, 0x10($v1)
    MEM_H(0X10, ctx->r3) = ctx->r4;
    // 0x801EADA8: jr          $ra
    // 0x801EADAC: nop

    return;
    // 0x801EADAC: nop

;}
RECOMP_FUNC void func_801EADB0(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801EADB0: lui         $a0, 0x8023
    ctx->r4 = S32(0X8023 << 16);
    // 0x801EADB4: addiu       $a0, $a0, -0x7588
    ctx->r4 = ADD32(ctx->r4, -0X7588);
    // 0x801EADB8: lh          $v0, 0x2($a0)
    ctx->r2 = MEM_H(ctx->r4, 0X2);
    // 0x801EADBC: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x801EADC0: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x801EADC4: beql        $v0, $zero, L_801EADF4
    if (ctx->r2 == 0) {
        // 0x801EADC8: lw          $t6, 0x4($a0)
        ctx->r14 = MEM_W(ctx->r4, 0X4);
            goto L_801EADF4;
    }
    goto skip_0;
    // 0x801EADC8: lw          $t6, 0x4($a0)
    ctx->r14 = MEM_W(ctx->r4, 0X4);
    skip_0:
    // 0x801EADCC: beq         $v0, $at, L_801EAEB0
    if (ctx->r2 == ctx->r1) {
        // 0x801EADD0: addiu       $t3, $zero, 0xFF
        ctx->r11 = ADD32(0, 0XFF);
            goto L_801EAEB0;
    }
    // 0x801EADD0: addiu       $t3, $zero, 0xFF
    ctx->r11 = ADD32(0, 0XFF);
    // 0x801EADD4: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x801EADD8: beq         $v0, $at, L_801EADF0
    if (ctx->r2 == ctx->r1) {
        // 0x801EADDC: addiu       $at, $zero, 0x3
        ctx->r1 = ADD32(0, 0X3);
            goto L_801EADF0;
    }
    // 0x801EADDC: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x801EADE0: beql        $v0, $at, L_801EAEB4
    if (ctx->r2 == ctx->r1) {
        // 0x801EADE4: lw          $v0, 0x8($a0)
        ctx->r2 = MEM_W(ctx->r4, 0X8);
            goto L_801EAEB4;
    }
    goto skip_1;
    // 0x801EADE4: lw          $v0, 0x8($a0)
    ctx->r2 = MEM_W(ctx->r4, 0X8);
    skip_1:
    // 0x801EADE8: jr          $ra
    // 0x801EADEC: nop

    return;
    // 0x801EADEC: nop

L_801EADF0:
    // 0x801EADF0: lw          $t6, 0x4($a0)
    ctx->r14 = MEM_W(ctx->r4, 0X4);
L_801EADF4:
    // 0x801EADF4: lw          $t7, 0x8($a0)
    ctx->r15 = MEM_W(ctx->r4, 0X8);
    // 0x801EADF8: lui         $at, 0x42FE
    ctx->r1 = S32(0X42FE << 16);
    // 0x801EADFC: mtc1        $t6, $f4
    ctx->f4.u32l = ctx->r14;
    // 0x801EAE00: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x801EAE04: mtc1        $t7, $f16
    ctx->f16.u32l = ctx->r15;
    // 0x801EAE08: cvt.s.w     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
    // 0x801EAE0C: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
    // 0x801EAE10: lui         $at, 0x4F00
    ctx->r1 = S32(0X4F00 << 16);
    // 0x801EAE14: cvt.s.w     $f18, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    ctx->f18.fl = CVT_S_W(ctx->f16.u32l);
    // 0x801EAE18: mul.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = MUL_S(ctx->f6.fl, ctx->f8.fl);
    // 0x801EAE1C: div.s       $f4, $f10, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f4.fl = DIV_S(ctx->f10.fl, ctx->f18.fl);
    // 0x801EAE20: cfc1        $t8, $FpcCsr
    ctx->r24 = get_cop1_cs();
    // 0x801EAE24: ctc1        $v0, $FpcCsr
    set_cop1_cs(ctx->r2);
    // 0x801EAE28: nop

    // 0x801EAE2C: cvt.w.s     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.u32l = CVT_W_S(ctx->f4.fl);
    // 0x801EAE30: cfc1        $v0, $FpcCsr
    ctx->r2 = get_cop1_cs();
    // 0x801EAE34: nop

    // 0x801EAE38: andi        $v0, $v0, 0x78
    ctx->r2 = ctx->r2 & 0X78;
    // 0x801EAE3C: beql        $v0, $zero, L_801EAE8C
    if (ctx->r2 == 0) {
        // 0x801EAE40: mfc1        $v0, $f6
        ctx->r2 = (int32_t)ctx->f6.u32l;
            goto L_801EAE8C;
    }
    goto skip_2;
    // 0x801EAE40: mfc1        $v0, $f6
    ctx->r2 = (int32_t)ctx->f6.u32l;
    skip_2:
    // 0x801EAE44: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x801EAE48: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
    // 0x801EAE4C: sub.s       $f6, $f4, $f6
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f6.fl = ctx->f4.fl - ctx->f6.fl;
    // 0x801EAE50: ctc1        $v0, $FpcCsr
    set_cop1_cs(ctx->r2);
    // 0x801EAE54: nop

    // 0x801EAE58: cvt.w.s     $f6, $f6
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 6);
    ctx->f6.u32l = CVT_W_S(ctx->f6.fl);
    // 0x801EAE5C: cfc1        $v0, $FpcCsr
    ctx->r2 = get_cop1_cs();
    // 0x801EAE60: nop

    // 0x801EAE64: andi        $v0, $v0, 0x78
    ctx->r2 = ctx->r2 & 0X78;
    // 0x801EAE68: bne         $v0, $zero, L_801EAE80
    if (ctx->r2 != 0) {
        // 0x801EAE6C: nop
    
            goto L_801EAE80;
    }
    // 0x801EAE6C: nop

    // 0x801EAE70: mfc1        $v0, $f6
    ctx->r2 = (int32_t)ctx->f6.u32l;
    // 0x801EAE74: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x801EAE78: b           L_801EAE98
    // 0x801EAE7C: or          $v0, $v0, $at
    ctx->r2 = ctx->r2 | ctx->r1;
        goto L_801EAE98;
    // 0x801EAE7C: or          $v0, $v0, $at
    ctx->r2 = ctx->r2 | ctx->r1;
L_801EAE80:
    // 0x801EAE80: b           L_801EAE98
    // 0x801EAE84: addiu       $v0, $zero, -0x1
    ctx->r2 = ADD32(0, -0X1);
        goto L_801EAE98;
    // 0x801EAE84: addiu       $v0, $zero, -0x1
    ctx->r2 = ADD32(0, -0X1);
    // 0x801EAE88: mfc1        $v0, $f6
    ctx->r2 = (int32_t)ctx->f6.u32l;
L_801EAE8C:
    // 0x801EAE8C: nop

    // 0x801EAE90: bltz        $v0, L_801EAE80
    if (SIGNED(ctx->r2) < 0) {
        // 0x801EAE94: nop
    
            goto L_801EAE80;
    }
    // 0x801EAE94: nop

L_801EAE98:
    // 0x801EAE98: ctc1        $t8, $FpcCsr
    set_cop1_cs(ctx->r24);
    // 0x801EAE9C: addiu       $v0, $v0, 0x80
    ctx->r2 = ADD32(ctx->r2, 0X80);
    // 0x801EAEA0: sh          $v0, 0xC($a0)
    MEM_H(0XC, ctx->r4) = ctx->r2;
    // 0x801EAEA4: sh          $t9, 0xE($a0)
    MEM_H(0XE, ctx->r4) = ctx->r25;
    // 0x801EAEA8: jr          $ra
    // 0x801EAEAC: sh          $v0, 0x10($a0)
    MEM_H(0X10, ctx->r4) = ctx->r2;
    return;
    // 0x801EAEAC: sh          $v0, 0x10($a0)
    MEM_H(0X10, ctx->r4) = ctx->r2;
L_801EAEB0:
    // 0x801EAEB0: lw          $v0, 0x8($a0)
    ctx->r2 = MEM_W(ctx->r4, 0X8);
L_801EAEB4:
    // 0x801EAEB4: lw          $t0, 0x4($a0)
    ctx->r8 = MEM_W(ctx->r4, 0X4);
    // 0x801EAEB8: lui         $at, 0x42FE
    ctx->r1 = S32(0X42FE << 16);
    // 0x801EAEBC: mtc1        $at, $f10
    ctx->f10.u32l = ctx->r1;
    // 0x801EAEC0: subu        $t1, $v0, $t0
    ctx->r9 = SUB32(ctx->r2, ctx->r8);
    // 0x801EAEC4: mtc1        $t1, $f8
    ctx->f8.u32l = ctx->r9;
    // 0x801EAEC8: mtc1        $v0, $f4
    ctx->f4.u32l = ctx->r2;
    // 0x801EAECC: addiu       $v1, $zero, 0x1
    ctx->r3 = ADD32(0, 0X1);
    // 0x801EAED0: cvt.s.w     $f16, $f8
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 8);
    ctx->f16.fl = CVT_S_W(ctx->f8.u32l);
    // 0x801EAED4: lui         $at, 0x4F00
    ctx->r1 = S32(0X4F00 << 16);
    // 0x801EAED8: cvt.s.w     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
    // 0x801EAEDC: mul.s       $f18, $f16, $f10
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f18.fl = MUL_S(ctx->f16.fl, ctx->f10.fl);
    // 0x801EAEE0: div.s       $f8, $f18, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = DIV_S(ctx->f18.fl, ctx->f6.fl);
    // 0x801EAEE4: cfc1        $t2, $FpcCsr
    ctx->r10 = get_cop1_cs();
    // 0x801EAEE8: ctc1        $v1, $FpcCsr
    set_cop1_cs(ctx->r3);
    // 0x801EAEEC: nop

    // 0x801EAEF0: cvt.w.s     $f16, $f8
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 8);
    ctx->f16.u32l = CVT_W_S(ctx->f8.fl);
    // 0x801EAEF4: cfc1        $v1, $FpcCsr
    ctx->r3 = get_cop1_cs();
    // 0x801EAEF8: nop

    // 0x801EAEFC: andi        $v1, $v1, 0x78
    ctx->r3 = ctx->r3 & 0X78;
    // 0x801EAF00: beql        $v1, $zero, L_801EAF50
    if (ctx->r3 == 0) {
        // 0x801EAF04: mfc1        $v1, $f16
        ctx->r3 = (int32_t)ctx->f16.u32l;
            goto L_801EAF50;
    }
    goto skip_3;
    // 0x801EAF04: mfc1        $v1, $f16
    ctx->r3 = (int32_t)ctx->f16.u32l;
    skip_3:
    // 0x801EAF08: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
    // 0x801EAF0C: addiu       $v1, $zero, 0x1
    ctx->r3 = ADD32(0, 0X1);
    // 0x801EAF10: sub.s       $f16, $f8, $f16
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f16.fl = ctx->f8.fl - ctx->f16.fl;
    // 0x801EAF14: ctc1        $v1, $FpcCsr
    set_cop1_cs(ctx->r3);
    // 0x801EAF18: nop

    // 0x801EAF1C: cvt.w.s     $f16, $f16
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 16);
    ctx->f16.u32l = CVT_W_S(ctx->f16.fl);
    // 0x801EAF20: cfc1        $v1, $FpcCsr
    ctx->r3 = get_cop1_cs();
    // 0x801EAF24: nop

    // 0x801EAF28: andi        $v1, $v1, 0x78
    ctx->r3 = ctx->r3 & 0X78;
    // 0x801EAF2C: bne         $v1, $zero, L_801EAF44
    if (ctx->r3 != 0) {
        // 0x801EAF30: nop
    
            goto L_801EAF44;
    }
    // 0x801EAF30: nop

    // 0x801EAF34: mfc1        $v1, $f16
    ctx->r3 = (int32_t)ctx->f16.u32l;
    // 0x801EAF38: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x801EAF3C: b           L_801EAF5C
    // 0x801EAF40: or          $v1, $v1, $at
    ctx->r3 = ctx->r3 | ctx->r1;
        goto L_801EAF5C;
    // 0x801EAF40: or          $v1, $v1, $at
    ctx->r3 = ctx->r3 | ctx->r1;
L_801EAF44:
    // 0x801EAF44: b           L_801EAF5C
    // 0x801EAF48: addiu       $v1, $zero, -0x1
    ctx->r3 = ADD32(0, -0X1);
        goto L_801EAF5C;
    // 0x801EAF48: addiu       $v1, $zero, -0x1
    ctx->r3 = ADD32(0, -0X1);
    // 0x801EAF4C: mfc1        $v1, $f16
    ctx->r3 = (int32_t)ctx->f16.u32l;
L_801EAF50:
    // 0x801EAF50: nop

    // 0x801EAF54: bltz        $v1, L_801EAF44
    if (SIGNED(ctx->r3) < 0) {
        // 0x801EAF58: nop
    
            goto L_801EAF44;
    }
    // 0x801EAF58: nop

L_801EAF5C:
    // 0x801EAF5C: addiu       $v1, $v1, 0x80
    ctx->r3 = ADD32(ctx->r3, 0X80);
    // 0x801EAF60: ctc1        $t2, $FpcCsr
    set_cop1_cs(ctx->r10);
    // 0x801EAF64: sh          $v1, 0xC($a0)
    MEM_H(0XC, ctx->r4) = ctx->r3;
    // 0x801EAF68: sh          $t3, 0xE($a0)
    MEM_H(0XE, ctx->r4) = ctx->r11;
    // 0x801EAF6C: sh          $v1, 0x10($a0)
    MEM_H(0X10, ctx->r4) = ctx->r3;
    // 0x801EAF70: jr          $ra
    // 0x801EAF74: nop

    return;
    // 0x801EAF74: nop

;}
RECOMP_FUNC void func_801EAF78(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801EAF78: lui         $t7, 0x8022
    ctx->r15 = S32(0X8022 << 16);
    // 0x801EAF7C: addiu       $t7, $t7, 0x6E30
    ctx->r15 = ADD32(ctx->r15, 0X6E30);
    // 0x801EAF80: lw          $at, 0x0($t7)
    ctx->r1 = MEM_W(ctx->r15, 0X0);
    // 0x801EAF84: lui         $t6, 0x8023
    ctx->r14 = S32(0X8023 << 16);
    // 0x801EAF88: addiu       $t6, $t6, -0x7588
    ctx->r14 = ADD32(ctx->r14, -0X7588);
    // 0x801EAF8C: sw          $at, 0x0($t6)
    MEM_W(0X0, ctx->r14) = ctx->r1;
    // 0x801EAF90: lw          $at, 0x8($t7)
    ctx->r1 = MEM_W(ctx->r15, 0X8);
    // 0x801EAF94: lw          $t0, 0x4($t7)
    ctx->r8 = MEM_W(ctx->r15, 0X4);
    // 0x801EAF98: sw          $at, 0x8($t6)
    MEM_W(0X8, ctx->r14) = ctx->r1;
    // 0x801EAF9C: sw          $t0, 0x4($t6)
    MEM_W(0X4, ctx->r14) = ctx->r8;
    // 0x801EAFA0: lw          $t0, 0xC($t7)
    ctx->r8 = MEM_W(ctx->r15, 0XC);
    // 0x801EAFA4: lw          $at, 0x10($t7)
    ctx->r1 = MEM_W(ctx->r15, 0X10);
    // 0x801EAFA8: sw          $t0, 0xC($t6)
    MEM_W(0XC, ctx->r14) = ctx->r8;
    // 0x801EAFAC: jr          $ra
    // 0x801EAFB0: sw          $at, 0x10($t6)
    MEM_W(0X10, ctx->r14) = ctx->r1;
    return;
    // 0x801EAFB0: sw          $at, 0x10($t6)
    MEM_W(0X10, ctx->r14) = ctx->r1;
;}
RECOMP_FUNC void func_801EAFB4(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801EAFB4: lui         $v0, 0x8023
    ctx->r2 = S32(0X8023 << 16);
    // 0x801EAFB8: addiu       $v0, $v0, -0x7588
    ctx->r2 = ADD32(ctx->r2, -0X7588);
    // 0x801EAFBC: lh          $t6, 0x0($v0)
    ctx->r14 = MEM_H(ctx->r2, 0X0);
    // 0x801EAFC0: beq         $t6, $zero, L_801EB004
    if (ctx->r14 == 0) {
        // 0x801EAFC4: nop
    
            goto L_801EB004;
    }
    // 0x801EAFC4: nop

    // 0x801EAFC8: lw          $t7, 0x4($v0)
    ctx->r15 = MEM_W(ctx->r2, 0X4);
    // 0x801EAFCC: lw          $t0, 0x8($v0)
    ctx->r8 = MEM_W(ctx->r2, 0X8);
    // 0x801EAFD0: addiu       $t8, $t7, 0x1
    ctx->r24 = ADD32(ctx->r15, 0X1);
    // 0x801EAFD4: slt         $at, $t8, $t0
    ctx->r1 = SIGNED(ctx->r24) < SIGNED(ctx->r8) ? 1 : 0;
    // 0x801EAFD8: bne         $at, $zero, L_801EB004
    if (ctx->r1 != 0) {
        // 0x801EAFDC: sw          $t8, 0x4($v0)
        MEM_W(0X4, ctx->r2) = ctx->r24;
            goto L_801EB004;
    }
    // 0x801EAFDC: sw          $t8, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r24;
    // 0x801EAFE0: lh          $t1, 0x2($v0)
    ctx->r9 = MEM_H(ctx->r2, 0X2);
    // 0x801EAFE4: addiu       $at, $zero, 0x4
    ctx->r1 = ADD32(0, 0X4);
    // 0x801EAFE8: sw          $zero, 0x4($v0)
    MEM_W(0X4, ctx->r2) = 0;
    // 0x801EAFEC: addiu       $t2, $t1, 0x1
    ctx->r10 = ADD32(ctx->r9, 0X1);
    // 0x801EAFF0: sh          $t2, 0x2($v0)
    MEM_H(0X2, ctx->r2) = ctx->r10;
    // 0x801EAFF4: lh          $t3, 0x2($v0)
    ctx->r11 = MEM_H(ctx->r2, 0X2);
    // 0x801EAFF8: bne         $t3, $at, L_801EB004
    if (ctx->r11 != ctx->r1) {
        // 0x801EAFFC: nop
    
            goto L_801EB004;
    }
    // 0x801EAFFC: nop

    // 0x801EB000: sh          $zero, 0x2($v0)
    MEM_H(0X2, ctx->r2) = 0;
L_801EB004:
    // 0x801EB004: jr          $ra
    // 0x801EB008: nop

    return;
    // 0x801EB008: nop

;}
RECOMP_FUNC void func_801EB00C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801EB00C: addiu       $sp, $sp, -0x60
    ctx->r29 = ADD32(ctx->r29, -0X60);
    // 0x801EB010: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x801EB014: sw          $a0, 0x60($sp)
    MEM_W(0X60, ctx->r29) = ctx->r4;
    // 0x801EB018: sw          $a1, 0x64($sp)
    MEM_W(0X64, ctx->r29) = ctx->r5;
    // 0x801EB01C: sw          $a2, 0x68($sp)
    MEM_W(0X68, ctx->r29) = ctx->r6;
    // 0x801EB020: bne         $a1, $zero, L_801EB034
    if (ctx->r5 != 0) {
        // 0x801EB024: sw          $a3, 0x6C($sp)
        MEM_W(0X6C, ctx->r29) = ctx->r7;
            goto L_801EB034;
    }
    // 0x801EB024: sw          $a3, 0x6C($sp)
    MEM_W(0X6C, ctx->r29) = ctx->r7;
    // 0x801EB028: lui         $t3, 0x8022
    ctx->r11 = S32(0X8022 << 16);
    // 0x801EB02C: b           L_801EB054
    // 0x801EB030: addiu       $t3, $t3, 0x6D70
    ctx->r11 = ADD32(ctx->r11, 0X6D70);
        goto L_801EB054;
    // 0x801EB030: addiu       $t3, $t3, 0x6D70
    ctx->r11 = ADD32(ctx->r11, 0X6D70);
L_801EB034:
    // 0x801EB034: lw          $t7, 0x64($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X64);
    // 0x801EB038: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x801EB03C: lui         $t3, 0x8022
    ctx->r11 = S32(0X8022 << 16);
    // 0x801EB040: bne         $t7, $at, L_801EB054
    if (ctx->r15 != ctx->r1) {
        // 0x801EB044: addiu       $t3, $t3, 0x6D98
        ctx->r11 = ADD32(ctx->r11, 0X6D98);
            goto L_801EB054;
    }
    // 0x801EB044: addiu       $t3, $t3, 0x6D98
    ctx->r11 = ADD32(ctx->r11, 0X6D98);
    // 0x801EB048: lui         $t3, 0x8022
    ctx->r11 = S32(0X8022 << 16);
    // 0x801EB04C: b           L_801EB054
    // 0x801EB050: addiu       $t3, $t3, 0x6DC4
    ctx->r11 = ADD32(ctx->r11, 0X6DC4);
        goto L_801EB054;
    // 0x801EB050: addiu       $t3, $t3, 0x6DC4
    ctx->r11 = ADD32(ctx->r11, 0X6DC4);
L_801EB054:
    // 0x801EB054: lui         $a1, 0x8022
    ctx->r5 = S32(0X8022 << 16);
    // 0x801EB058: addiu       $a1, $a1, 0x6E50
    ctx->r5 = ADD32(ctx->r5, 0X6E50);
    // 0x801EB05C: addiu       $a0, $sp, 0x30
    ctx->r4 = ADD32(ctx->r29, 0X30);
    // 0x801EB060: lw          $a2, 0x68($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X68);
    // 0x801EB064: jal         0x800CA210
    // 0x801EB068: sw          $t3, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r11;
    func_800CA210(rdram, ctx);
        goto after_0;
    // 0x801EB068: sw          $t3, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r11;
    after_0:
    // 0x801EB06C: lw          $t3, 0x3C($sp)
    ctx->r11 = MEM_W(ctx->r29, 0X3C);
    // 0x801EB070: lw          $v1, 0x68($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X68);
    // 0x801EB074: addiu       $a0, $sp, 0x4C
    ctx->r4 = ADD32(ctx->r29, 0X4C);
    // 0x801EB078: addiu       $a1, $sp, 0x58
    ctx->r5 = ADD32(ctx->r29, 0X58);
    // 0x801EB07C: addiu       $v0, $zero, 0xA
    ctx->r2 = ADD32(0, 0XA);
L_801EB080:
    // 0x801EB080: div         $zero, $v1, $v0
    lo = S32(S64(S32(ctx->r3)) / S64(S32(ctx->r2))); hi = S32(S64(S32(ctx->r3)) % S64(S32(ctx->r2)));
    // 0x801EB084: bne         $v0, $zero, L_801EB090
    if (ctx->r2 != 0) {
        // 0x801EB088: nop
    
            goto L_801EB090;
    }
    // 0x801EB088: nop

    // 0x801EB08C: break       7
    do_break(2149494924);
L_801EB090:
    // 0x801EB090: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x801EB094: bne         $v0, $at, L_801EB0A8
    if (ctx->r2 != ctx->r1) {
        // 0x801EB098: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_801EB0A8;
    }
    // 0x801EB098: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x801EB09C: bne         $v1, $at, L_801EB0A8
    if (ctx->r3 != ctx->r1) {
        // 0x801EB0A0: nop
    
            goto L_801EB0A8;
    }
    // 0x801EB0A0: nop

    // 0x801EB0A4: break       6
    do_break(2149494948);
L_801EB0A8:
    // 0x801EB0A8: addiu       $a0, $a0, 0x4
    ctx->r4 = ADD32(ctx->r4, 0X4);
    // 0x801EB0AC: sltu        $at, $a0, $a1
    ctx->r1 = ctx->r4 < ctx->r5 ? 1 : 0;
    // 0x801EB0B0: mfhi        $t8
    ctx->r24 = hi;
    // 0x801EB0B4: mflo        $v1
    ctx->r3 = lo;
    // 0x801EB0B8: sw          $t8, -0x4($a0)
    MEM_W(-0X4, ctx->r4) = ctx->r24;
    // 0x801EB0BC: bne         $at, $zero, L_801EB080
    if (ctx->r1 != 0) {
        // 0x801EB0C0: nop
    
            goto L_801EB080;
    }
    // 0x801EB0C0: nop

    // 0x801EB0C4: or          $t2, $zero, $zero
    ctx->r10 = 0 | 0;
    // 0x801EB0C8: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x801EB0CC: addiu       $a0, $sp, 0x50
    ctx->r4 = ADD32(ctx->r29, 0X50);
    // 0x801EB0D0: addiu       $v1, $sp, 0x58
    ctx->r3 = ADD32(ctx->r29, 0X58);
L_801EB0D4:
    // 0x801EB0D4: lw          $a3, 0x0($a0)
    ctx->r7 = MEM_W(ctx->r4, 0X0);
    // 0x801EB0D8: addiu       $a0, $a0, 0x4
    ctx->r4 = ADD32(ctx->r4, 0X4);
    // 0x801EB0DC: or          $t0, $zero, $zero
    ctx->r8 = 0 | 0;
    // 0x801EB0E0: beq         $a3, $zero, L_801EB0FC
    if (ctx->r7 == 0) {
        // 0x801EB0E4: addiu       $a2, $a1, 0x1
        ctx->r6 = ADD32(ctx->r5, 0X1);
            goto L_801EB0FC;
    }
    // 0x801EB0E4: addiu       $a2, $a1, 0x1
    ctx->r6 = ADD32(ctx->r5, 0X1);
    // 0x801EB0E8: addu        $t9, $t3, $a3
    ctx->r25 = ADD32(ctx->r11, ctx->r7);
    // 0x801EB0EC: lbu         $t4, 0x0($t9)
    ctx->r12 = MEM_BU(ctx->r25, 0X0);
    // 0x801EB0F0: addiu       $a2, $a1, 0x1
    ctx->r6 = ADD32(ctx->r5, 0X1);
    // 0x801EB0F4: b           L_801EB144
    // 0x801EB0F8: subu        $t2, $t2, $t4
    ctx->r10 = SUB32(ctx->r10, ctx->r12);
        goto L_801EB144;
    // 0x801EB0F8: subu        $t2, $t2, $t4
    ctx->r10 = SUB32(ctx->r10, ctx->r12);
L_801EB0FC:
    // 0x801EB0FC: slti        $at, $a2, 0x3
    ctx->r1 = SIGNED(ctx->r6) < 0X3 ? 1 : 0;
    // 0x801EB100: beq         $at, $zero, L_801EB134
    if (ctx->r1 == 0) {
        // 0x801EB104: or          $t1, $a2, $zero
        ctx->r9 = ctx->r6 | 0;
            goto L_801EB134;
    }
    // 0x801EB104: or          $t1, $a2, $zero
    ctx->r9 = ctx->r6 | 0;
    // 0x801EB108: sll         $t5, $t1, 2
    ctx->r13 = S32(ctx->r9 << 2);
    // 0x801EB10C: addiu       $t6, $sp, 0x4C
    ctx->r14 = ADD32(ctx->r29, 0X4C);
    // 0x801EB110: addu        $v0, $t5, $t6
    ctx->r2 = ADD32(ctx->r13, ctx->r14);
    // 0x801EB114: lw          $t7, 0x0($v0)
    ctx->r15 = MEM_W(ctx->r2, 0X0);
L_801EB118:
    // 0x801EB118: addiu       $v0, $v0, 0x4
    ctx->r2 = ADD32(ctx->r2, 0X4);
    // 0x801EB11C: beq         $t7, $zero, L_801EB12C
    if (ctx->r15 == 0) {
        // 0x801EB120: nop
    
            goto L_801EB12C;
    }
    // 0x801EB120: nop

    // 0x801EB124: b           L_801EB134
    // 0x801EB128: addiu       $t0, $zero, 0x1
    ctx->r8 = ADD32(0, 0X1);
        goto L_801EB134;
    // 0x801EB128: addiu       $t0, $zero, 0x1
    ctx->r8 = ADD32(0, 0X1);
L_801EB12C:
    // 0x801EB12C: bnel        $v0, $v1, L_801EB118
    if (ctx->r2 != ctx->r3) {
        // 0x801EB130: lw          $t7, 0x0($v0)
        ctx->r15 = MEM_W(ctx->r2, 0X0);
            goto L_801EB118;
    }
    goto skip_0;
    // 0x801EB130: lw          $t7, 0x0($v0)
    ctx->r15 = MEM_W(ctx->r2, 0X0);
    skip_0:
L_801EB134:
    // 0x801EB134: beq         $t0, $zero, L_801EB150
    if (ctx->r8 == 0) {
        // 0x801EB138: addu        $t8, $t3, $a3
        ctx->r24 = ADD32(ctx->r11, ctx->r7);
            goto L_801EB150;
    }
    // 0x801EB138: addu        $t8, $t3, $a3
    ctx->r24 = ADD32(ctx->r11, ctx->r7);
    // 0x801EB13C: lbu         $t9, 0x0($t8)
    ctx->r25 = MEM_BU(ctx->r24, 0X0);
    // 0x801EB140: subu        $t2, $t2, $t9
    ctx->r10 = SUB32(ctx->r10, ctx->r25);
L_801EB144:
    // 0x801EB144: slti        $at, $a2, 0x3
    ctx->r1 = SIGNED(ctx->r6) < 0X3 ? 1 : 0;
    // 0x801EB148: bne         $at, $zero, L_801EB0D4
    if (ctx->r1 != 0) {
        // 0x801EB14C: or          $a1, $a2, $zero
        ctx->r5 = ctx->r6 | 0;
            goto L_801EB0D4;
    }
    // 0x801EB14C: or          $a1, $a2, $zero
    ctx->r5 = ctx->r6 | 0;
L_801EB150:
    // 0x801EB150: lw          $t4, 0x6C($sp)
    ctx->r12 = MEM_W(ctx->r29, 0X6C);
    // 0x801EB154: lw          $t5, 0x70($sp)
    ctx->r13 = MEM_W(ctx->r29, 0X70);
    // 0x801EB158: lw          $a0, 0x60($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X60);
    // 0x801EB15C: lw          $a1, 0x64($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X64);
    // 0x801EB160: addiu       $a2, $sp, 0x30
    ctx->r6 = ADD32(ctx->r29, 0X30);
    // 0x801EB164: addu        $a3, $t4, $t2
    ctx->r7 = ADD32(ctx->r12, ctx->r10);
    // 0x801EB168: jal         0x801E9858
    // 0x801EB16C: sw          $t5, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r13;
    func_801E9858(rdram, ctx);
        goto after_1;
    // 0x801EB16C: sw          $t5, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r13;
    after_1:
    // 0x801EB170: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    // 0x801EB174: addiu       $sp, $sp, 0x60
    ctx->r29 = ADD32(ctx->r29, 0X60);
    // 0x801EB178: jr          $ra
    // 0x801EB17C: nop

    return;
    // 0x801EB17C: nop

;}
RECOMP_FUNC void func_801EB180(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801EB180: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x801EB184: addiu       $v0, $v0, -0x54DC
    ctx->r2 = ADD32(ctx->r2, -0X54DC);
    // 0x801EB188: lw          $t6, 0x0($v0)
    ctx->r14 = MEM_W(ctx->r2, 0X0);
    // 0x801EB18C: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EB190: addiu       $v1, $zero, 0x2
    ctx->r3 = ADD32(0, 0X2);
    // 0x801EB194: sw          $t6, -0x19CC($at)
    MEM_W(-0X19CC, ctx->r1) = ctx->r14;
    // 0x801EB198: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EB19C: sw          $zero, -0x19D0($at)
    MEM_W(-0X19D0, ctx->r1) = 0;
    // 0x801EB1A0: sw          $v1, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r3;
    // 0x801EB1A4: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EB1A8: sw          $zero, -0x19C8($at)
    MEM_W(-0X19C8, ctx->r1) = 0;
    // 0x801EB1AC: addiu       $t2, $zero, 0x1
    ctx->r10 = ADD32(0, 0X1);
    // 0x801EB1B0: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EB1B4: sw          $t2, -0x19C4($at)
    MEM_W(-0X19C4, ctx->r1) = ctx->r10;
    // 0x801EB1B8: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EB1BC: sw          $zero, -0x19C0($at)
    MEM_W(-0X19C0, ctx->r1) = 0;
    // 0x801EB1C0: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EB1C4: sw          $zero, -0x19BC($at)
    MEM_W(-0X19BC, ctx->r1) = 0;
    // 0x801EB1C8: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x801EB1CC: sw          $zero, -0x54E4($at)
    MEM_W(-0X54E4, ctx->r1) = 0;
    // 0x801EB1D0: addiu       $t3, $zero, 0x3
    ctx->r11 = ADD32(0, 0X3);
    // 0x801EB1D4: lui         $at, 0x800D
    ctx->r1 = S32(0X800D << 16);
    // 0x801EB1D8: sw          $t3, 0x461C($at)
    MEM_W(0X461C, ctx->r1) = ctx->r11;
    // 0x801EB1DC: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EB1E0: sw          $zero, -0x19E0($at)
    MEM_W(-0X19E0, ctx->r1) = 0;
    // 0x801EB1E4: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x801EB1E8: lui         $a1, 0x801A
    ctx->r5 = S32(0X801A << 16);
    // 0x801EB1EC: sw          $t2, -0x54D8($at)
    MEM_W(-0X54D8, ctx->r1) = ctx->r10;
    // 0x801EB1F0: addiu       $a1, $a1, -0x7D10
    ctx->r5 = ADD32(ctx->r5, -0X7D10);
    // 0x801EB1F4: sw          $v1, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r3;
    // 0x801EB1F8: lui         $at, 0x800D
    ctx->r1 = S32(0X800D << 16);
    // 0x801EB1FC: addiu       $t7, $zero, 0x14
    ctx->r15 = ADD32(0, 0X14);
    // 0x801EB200: sw          $t7, 0x49B0($at)
    MEM_W(0X49B0, ctx->r1) = ctx->r15;
    // 0x801EB204: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x801EB208: addiu       $t8, $zero, 0x5
    ctx->r24 = ADD32(0, 0X5);
    // 0x801EB20C: sw          $t8, -0x7E8C($at)
    MEM_W(-0X7E8C, ctx->r1) = ctx->r24;
    // 0x801EB210: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EB214: sw          $t3, -0x18D8($at)
    MEM_W(-0X18D8, ctx->r1) = ctx->r11;
    // 0x801EB218: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x801EB21C: sw          $t2, -0x7E88($at)
    MEM_W(-0X7E88, ctx->r1) = ctx->r10;
    // 0x801EB220: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EB224: sw          $zero, -0x1A00($at)
    MEM_W(-0X1A00, ctx->r1) = 0;
    // 0x801EB228: lui         $t9, 0x800E
    ctx->r25 = S32(0X800E << 16);
    // 0x801EB22C: lw          $t9, -0x7DC0($t9)
    ctx->r25 = MEM_W(ctx->r25, -0X7DC0);
    // 0x801EB230: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EB234: sw          $zero, -0x1908($at)
    MEM_W(-0X1908, ctx->r1) = 0;
    // 0x801EB238: addiu       $sp, $sp, -0x30
    ctx->r29 = ADD32(ctx->r29, -0X30);
    // 0x801EB23C: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EB240: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x801EB244: bne         $t9, $zero, L_801EB254
    if (ctx->r25 != 0) {
        // 0x801EB248: sw          $zero, -0x4CCC($at)
        MEM_W(-0X4CCC, ctx->r1) = 0;
            goto L_801EB254;
    }
    // 0x801EB248: sw          $zero, -0x4CCC($at)
    MEM_W(-0X4CCC, ctx->r1) = 0;
    // 0x801EB24C: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x801EB250: sw          $zero, -0x7E90($at)
    MEM_W(-0X7E90, ctx->r1) = 0;
L_801EB254:
    // 0x801EB254: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EB258: lui         $t4, 0x801D
    ctx->r12 = S32(0X801D << 16);
    // 0x801EB25C: lb          $t4, -0x4D80($t4)
    ctx->r12 = MEM_B(ctx->r12, -0X4D80);
    // 0x801EB260: sh          $zero, -0x1910($at)
    MEM_H(-0X1910, ctx->r1) = 0;
    // 0x801EB264: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x801EB268: sh          $zero, -0x5498($at)
    MEM_H(-0X5498, ctx->r1) = 0;
    // 0x801EB26C: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x801EB270: andi        $t5, $t4, 0x10
    ctx->r13 = ctx->r12 & 0X10;
    // 0x801EB274: beq         $t5, $zero, L_801EB288
    if (ctx->r13 == 0) {
        // 0x801EB278: sh          $zero, -0x54F4($at)
        MEM_H(-0X54F4, ctx->r1) = 0;
            goto L_801EB288;
    }
    // 0x801EB278: sh          $zero, -0x54F4($at)
    MEM_H(-0X54F4, ctx->r1) = 0;
    // 0x801EB27C: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x801EB280: b           L_801EB290
    // 0x801EB284: sh          $t2, -0x54A0($at)
    MEM_H(-0X54A0, ctx->r1) = ctx->r10;
        goto L_801EB290;
    // 0x801EB284: sh          $t2, -0x54A0($at)
    MEM_H(-0X54A0, ctx->r1) = ctx->r10;
L_801EB288:
    // 0x801EB288: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x801EB28C: sh          $zero, -0x54A0($at)
    MEM_H(-0X54A0, ctx->r1) = 0;
L_801EB290:
    // 0x801EB290: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x801EB294: sh          $zero, -0x549C($at)
    MEM_H(-0X549C, ctx->r1) = 0;
    // 0x801EB298: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x801EB29C: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x801EB2A0: addiu       $v0, $v0, -0x5608
    ctx->r2 = ADD32(ctx->r2, -0X5608);
    // 0x801EB2A4: sw          $zero, -0x55F8($at)
    MEM_W(-0X55F8, ctx->r1) = 0;
    // 0x801EB2A8: lw          $t6, 0x0($v0)
    ctx->r14 = MEM_W(ctx->r2, 0X0);
    // 0x801EB2AC: addiu       $t7, $t6, 0x1
    ctx->r15 = ADD32(ctx->r14, 0X1);
    // 0x801EB2B0: slti        $at, $t7, 0x3
    ctx->r1 = SIGNED(ctx->r15) < 0X3 ? 1 : 0;
    // 0x801EB2B4: bne         $at, $zero, L_801EB2C0
    if (ctx->r1 != 0) {
        // 0x801EB2B8: sw          $t7, 0x0($v0)
        MEM_W(0X0, ctx->r2) = ctx->r15;
            goto L_801EB2C0;
    }
    // 0x801EB2B8: sw          $t7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r15;
    // 0x801EB2BC: sw          $zero, 0x0($v0)
    MEM_W(0X0, ctx->r2) = 0;
L_801EB2C0:
    // 0x801EB2C0: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x801EB2C4: addiu       $v0, $v0, -0x5604
    ctx->r2 = ADD32(ctx->r2, -0X5604);
    // 0x801EB2C8: lw          $t9, 0x0($v0)
    ctx->r25 = MEM_W(ctx->r2, 0X0);
    // 0x801EB2CC: lui         $t6, 0x800F
    ctx->r14 = S32(0X800F << 16);
    // 0x801EB2D0: addiu       $t6, $t6, -0x53BC
    ctx->r14 = ADD32(ctx->r14, -0X53BC);
    // 0x801EB2D4: addiu       $v1, $t9, 0x1
    ctx->r3 = ADD32(ctx->r25, 0X1);
    // 0x801EB2D8: slti        $at, $v1, 0x4
    ctx->r1 = SIGNED(ctx->r3) < 0X4 ? 1 : 0;
    // 0x801EB2DC: bne         $at, $zero, L_801EB2EC
    if (ctx->r1 != 0) {
        // 0x801EB2E0: sw          $v1, 0x0($v0)
        MEM_W(0X0, ctx->r2) = ctx->r3;
            goto L_801EB2EC;
    }
    // 0x801EB2E0: sw          $v1, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r3;
    // 0x801EB2E4: sw          $zero, 0x0($v0)
    MEM_W(0X0, ctx->r2) = 0;
    // 0x801EB2E8: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
L_801EB2EC:
    // 0x801EB2EC: sll         $t5, $v1, 3
    ctx->r13 = S32(ctx->r3 << 3);
    // 0x801EB2F0: lw          $t1, 0x0($a1)
    ctx->r9 = MEM_W(ctx->r5, 0X0);
    // 0x801EB2F4: addu        $v0, $t5, $t6
    ctx->r2 = ADD32(ctx->r13, ctx->r14);
    // 0x801EB2F8: lh          $t7, 0x0($v0)
    ctx->r15 = MEM_H(ctx->r2, 0X0);
    // 0x801EB2FC: lh          $a2, 0x2($v0)
    ctx->r6 = MEM_H(ctx->r2, 0X2);
    // 0x801EB300: blez        $t1, L_801EB390
    if (SIGNED(ctx->r9) <= 0) {
        // 0x801EB304: sw          $t7, 0x24($sp)
        MEM_W(0X24, ctx->r29) = ctx->r15;
            goto L_801EB390;
    }
    // 0x801EB304: sw          $t7, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r15;
    // 0x801EB308: lui         $t9, 0x800E
    ctx->r25 = S32(0X800E << 16);
    // 0x801EB30C: lw          $t9, -0x7E90($t9)
    ctx->r25 = MEM_W(ctx->r25, -0X7E90);
    // 0x801EB310: sll         $t5, $a2, 2
    ctx->r13 = S32(ctx->r6 << 2);
    // 0x801EB314: subu        $t5, $t5, $a2
    ctx->r13 = SUB32(ctx->r13, ctx->r6);
    // 0x801EB318: sll         $t4, $t9, 2
    ctx->r12 = S32(ctx->r25 << 2);
    // 0x801EB31C: subu        $t4, $t4, $t9
    ctx->r12 = SUB32(ctx->r12, ctx->r25);
    // 0x801EB320: sll         $t9, $t1, 2
    ctx->r25 = S32(ctx->r9 << 2);
    // 0x801EB324: subu        $t9, $t9, $t1
    ctx->r25 = SUB32(ctx->r25, ctx->r9);
    // 0x801EB328: sll         $t9, $t9, 3
    ctx->r25 = S32(ctx->r25 << 3);
    // 0x801EB32C: subu        $t9, $t9, $t1
    ctx->r25 = SUB32(ctx->r25, ctx->r9);
    // 0x801EB330: sll         $t9, $t9, 3
    ctx->r25 = S32(ctx->r25 << 3);
    // 0x801EB334: sll         $t4, $t4, 4
    ctx->r12 = S32(ctx->r12 << 4);
    // 0x801EB338: sll         $t5, $t5, 2
    ctx->r13 = S32(ctx->r13 << 2);
    // 0x801EB33C: lui         $t7, 0x800E
    ctx->r15 = S32(0X800E << 16);
    // 0x801EB340: addiu       $t7, $t7, -0x695C
    ctx->r15 = ADD32(ctx->r15, -0X695C);
    // 0x801EB344: addu        $t6, $t4, $t5
    ctx->r14 = ADD32(ctx->r12, ctx->r13);
    // 0x801EB348: addu        $t9, $t9, $t1
    ctx->r25 = ADD32(ctx->r25, ctx->r9);
    // 0x801EB34C: sll         $t9, $t9, 2
    ctx->r25 = S32(ctx->r25 << 2);
    // 0x801EB350: addu        $t0, $t6, $t7
    ctx->r8 = ADD32(ctx->r14, ctx->r15);
    // 0x801EB354: subu        $t9, $t9, $t1
    ctx->r25 = SUB32(ctx->r25, ctx->r9);
    // 0x801EB358: lui         $t8, 0x8019
    ctx->r24 = S32(0X8019 << 16);
    // 0x801EB35C: addiu       $v0, $t8, 0x2690
    ctx->r2 = ADD32(ctx->r24, 0X2690);
    // 0x801EB360: sll         $t9, $t9, 3
    ctx->r25 = S32(ctx->r25 << 3);
    // 0x801EB364: addu        $a3, $t9, $v0
    ctx->r7 = ADD32(ctx->r25, ctx->r2);
    // 0x801EB368: lw          $v1, 0x0($t0)
    ctx->r3 = MEM_W(ctx->r8, 0X0);
    // 0x801EB36C: lw          $a0, 0x4($t0)
    ctx->r4 = MEM_W(ctx->r8, 0X4);
    // 0x801EB370: lw          $a1, 0x8($t0)
    ctx->r5 = MEM_W(ctx->r8, 0X8);
L_801EB374:
    // 0x801EB374: addiu       $v0, $v0, 0x1718
    ctx->r2 = ADD32(ctx->r2, 0X1718);
    // 0x801EB378: sltu        $at, $v0, $a3
    ctx->r1 = ctx->r2 < ctx->r7 ? 1 : 0;
    // 0x801EB37C: sw          $a2, -0xBB0($v0)
    MEM_W(-0XBB0, ctx->r2) = ctx->r6;
    // 0x801EB380: sw          $v1, -0xBAC($v0)
    MEM_W(-0XBAC, ctx->r2) = ctx->r3;
    // 0x801EB384: sw          $a0, -0xBA8($v0)
    MEM_W(-0XBA8, ctx->r2) = ctx->r4;
    // 0x801EB388: bne         $at, $zero, L_801EB374
    if (ctx->r1 != 0) {
        // 0x801EB38C: sw          $a1, -0xBA4($v0)
        MEM_W(-0XBA4, ctx->r2) = ctx->r5;
            goto L_801EB374;
    }
    // 0x801EB38C: sw          $a1, -0xBA4($v0)
    MEM_W(-0XBA4, ctx->r2) = ctx->r5;
L_801EB390:
    // 0x801EB390: lui         $t4, 0x800D
    ctx->r12 = S32(0X800D << 16);
    // 0x801EB394: lw          $t4, 0x48DC($t4)
    ctx->r12 = MEM_W(ctx->r12, 0X48DC);
    // 0x801EB398: lw          $t7, 0x24($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X24);
    // 0x801EB39C: lui         $t6, 0x8019
    ctx->r14 = S32(0X8019 << 16);
    // 0x801EB3A0: sll         $t5, $t4, 2
    ctx->r13 = S32(ctx->r12 << 2);
    // 0x801EB3A4: subu        $t5, $t5, $t4
    ctx->r13 = SUB32(ctx->r13, ctx->r12);
    // 0x801EB3A8: sll         $t5, $t5, 3
    ctx->r13 = S32(ctx->r13 << 3);
    // 0x801EB3AC: subu        $t5, $t5, $t4
    ctx->r13 = SUB32(ctx->r13, ctx->r12);
    // 0x801EB3B0: sll         $t5, $t5, 3
    ctx->r13 = S32(ctx->r13 << 3);
    // 0x801EB3B4: addu        $t5, $t5, $t4
    ctx->r13 = ADD32(ctx->r13, ctx->r12);
    // 0x801EB3B8: sll         $t5, $t5, 2
    ctx->r13 = S32(ctx->r13 << 2);
    // 0x801EB3BC: subu        $t5, $t5, $t4
    ctx->r13 = SUB32(ctx->r13, ctx->r12);
    // 0x801EB3C0: sll         $t5, $t5, 3
    ctx->r13 = S32(ctx->r13 << 3);
    // 0x801EB3C4: addiu       $t6, $t6, 0x2690
    ctx->r14 = ADD32(ctx->r14, 0X2690);
    // 0x801EB3C8: addu        $v0, $t5, $t6
    ctx->r2 = ADD32(ctx->r13, ctx->r14);
    // 0x801EB3CC: lui         $t9, 0x800E
    ctx->r25 = S32(0X800E << 16);
    // 0x801EB3D0: sw          $t7, 0xB68($v0)
    MEM_W(0XB68, ctx->r2) = ctx->r15;
    // 0x801EB3D4: lw          $t9, -0x7E90($t9)
    ctx->r25 = MEM_W(ctx->r25, -0X7E90);
    // 0x801EB3D8: lw          $t4, 0x24($sp)
    ctx->r12 = MEM_W(ctx->r29, 0X24);
    // 0x801EB3DC: lui         $t7, 0x800E
    ctx->r15 = S32(0X800E << 16);
    // 0x801EB3E0: sll         $t8, $t9, 2
    ctx->r24 = S32(ctx->r25 << 2);
    // 0x801EB3E4: sll         $t5, $t4, 2
    ctx->r13 = S32(ctx->r12 << 2);
    // 0x801EB3E8: subu        $t8, $t8, $t9
    ctx->r24 = SUB32(ctx->r24, ctx->r25);
    // 0x801EB3EC: subu        $t5, $t5, $t4
    ctx->r13 = SUB32(ctx->r13, ctx->r12);
    // 0x801EB3F0: sll         $t5, $t5, 2
    ctx->r13 = S32(ctx->r13 << 2);
    // 0x801EB3F4: sll         $t8, $t8, 4
    ctx->r24 = S32(ctx->r24 << 4);
    // 0x801EB3F8: addu        $t6, $t8, $t5
    ctx->r14 = ADD32(ctx->r24, ctx->r13);
    // 0x801EB3FC: addiu       $t7, $t7, -0x695C
    ctx->r15 = ADD32(ctx->r15, -0X695C);
    // 0x801EB400: lui         $t0, 0x801D
    ctx->r8 = S32(0X801D << 16);
    // 0x801EB404: addu        $v1, $t6, $t7
    ctx->r3 = ADD32(ctx->r14, ctx->r15);
    // 0x801EB408: addiu       $t0, $t0, -0x190C
    ctx->r8 = ADD32(ctx->r8, -0X190C);
    // 0x801EB40C: sh          $zero, 0x2($t0)
    MEM_H(0X2, ctx->r8) = 0;
    // 0x801EB410: lw          $t9, 0x0($v1)
    ctx->r25 = MEM_W(ctx->r3, 0X0);
    // 0x801EB414: lw          $t4, 0x4($v1)
    ctx->r12 = MEM_W(ctx->r3, 0X4);
    // 0x801EB418: lw          $t8, 0x8($v1)
    ctx->r24 = MEM_W(ctx->r3, 0X8);
    // 0x801EB41C: lh          $t5, 0x2($t0)
    ctx->r13 = MEM_H(ctx->r8, 0X2);
    // 0x801EB420: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EB424: sw          $t9, 0xB6C($v0)
    MEM_W(0XB6C, ctx->r2) = ctx->r25;
    // 0x801EB428: sw          $t4, 0xB70($v0)
    MEM_W(0XB70, ctx->r2) = ctx->r12;
    // 0x801EB42C: sw          $t8, 0xB74($v0)
    MEM_W(0XB74, ctx->r2) = ctx->r24;
    // 0x801EB430: sh          $t5, 0x0($t0)
    MEM_H(0X0, ctx->r8) = ctx->r13;
    // 0x801EB434: sw          $t2, -0x19B8($at)
    MEM_W(-0X19B8, ctx->r1) = ctx->r10;
    // 0x801EB438: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EB43C: sw          $zero, -0x19B4($at)
    MEM_W(-0X19B4, ctx->r1) = 0;
    // 0x801EB440: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EB444: sw          $t3, -0x19B0($at)
    MEM_W(-0X19B0, ctx->r1) = ctx->r11;
    // 0x801EB448: or          $a0, $t2, $zero
    ctx->r4 = ctx->r10 | 0;
    // 0x801EB44C: lw          $a1, 0x24($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X24);
    // 0x801EB450: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    // 0x801EB454: jal         0x80096960
    // 0x801EB458: sw          $zero, 0x10($sp)
    MEM_W(0X10, ctx->r29) = 0;
    func_80096960(rdram, ctx);
        goto after_0;
    // 0x801EB458: sw          $zero, 0x10($sp)
    MEM_W(0X10, ctx->r29) = 0;
    after_0:
    // 0x801EB45C: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x801EB460: lw          $v0, -0x7E90($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X7E90);
    // 0x801EB464: lui         $t7, 0x800E
    ctx->r15 = S32(0X800E << 16);
    // 0x801EB468: addiu       $t7, $t7, -0x4A98
    ctx->r15 = ADD32(ctx->r15, -0X4A98);
    // 0x801EB46C: bgez        $v0, L_801EB478
    if (SIGNED(ctx->r2) >= 0) {
        // 0x801EB470: lui         $a0, 0x806
        ctx->r4 = S32(0X806 << 16);
            goto L_801EB478;
    }
    // 0x801EB470: lui         $a0, 0x806
    ctx->r4 = S32(0X806 << 16);
    // 0x801EB474: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_801EB478:
    // 0x801EB478: slti        $at, $v0, 0x9
    ctx->r1 = SIGNED(ctx->r2) < 0X9 ? 1 : 0;
    // 0x801EB47C: bnel        $at, $zero, L_801EB48C
    if (ctx->r1 != 0) {
        // 0x801EB480: sll         $t6, $v0, 2
        ctx->r14 = S32(ctx->r2 << 2);
            goto L_801EB48C;
    }
    goto skip_0;
    // 0x801EB480: sll         $t6, $v0, 2
    ctx->r14 = S32(ctx->r2 << 2);
    skip_0:
    // 0x801EB484: addiu       $v0, $zero, 0x8
    ctx->r2 = ADD32(0, 0X8);
    // 0x801EB488: sll         $t6, $v0, 2
    ctx->r14 = S32(ctx->r2 << 2);
L_801EB48C:
    // 0x801EB48C: addu        $v1, $t6, $t7
    ctx->r3 = ADD32(ctx->r14, ctx->r15);
    // 0x801EB490: lh          $a1, 0x0($v1)
    ctx->r5 = MEM_H(ctx->r3, 0X0);
    // 0x801EB494: jal         0x8009684C
    // 0x801EB498: lh          $a2, 0x2($v1)
    ctx->r6 = MEM_H(ctx->r3, 0X2);
    func_8009684C(rdram, ctx);
        goto after_1;
    // 0x801EB498: lh          $a2, 0x2($v1)
    ctx->r6 = MEM_H(ctx->r3, 0X2);
    after_1:
    // 0x801EB49C: jal         0x8004A208
    // 0x801EB4A0: nop

    func_8004A208(rdram, ctx);
        goto after_2;
    // 0x801EB4A0: nop

    after_2:
    // 0x801EB4A4: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    // 0x801EB4A8: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x801EB4AC: jal         0x801E6FB0
    // 0x801EB4B0: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    FadeTransition_SetProps(rdram, ctx);
        goto after_3;
    // 0x801EB4B0: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    after_3:
    // 0x801EB4B4: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    // 0x801EB4B8: jal         0x801E6A4C
    // 0x801EB4BC: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_801E6A4C(rdram, ctx);
        goto after_4;
    // 0x801EB4BC: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_4:
    // 0x801EB4C0: addiu       $t9, $zero, 0x5
    ctx->r25 = ADD32(0, 0X5);
    // 0x801EB4C4: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801EB4C8: sw          $t9, 0x7C80($at)
    MEM_W(0X7C80, ctx->r1) = ctx->r25;
    // 0x801EB4CC: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x801EB4D0: addiu       $t4, $zero, 0x1
    ctx->r12 = ADD32(0, 0X1);
    // 0x801EB4D4: sh          $t4, -0x5654($at)
    MEM_H(-0X5654, ctx->r1) = ctx->r12;
    // 0x801EB4D8: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    // 0x801EB4DC: jal         0x800C21F4
    // 0x801EB4E0: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C21F4(rdram, ctx);
        goto after_5;
    // 0x801EB4E0: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_5:
    // 0x801EB4E4: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    // 0x801EB4E8: addiu       $sp, $sp, 0x30
    ctx->r29 = ADD32(ctx->r29, 0X30);
    // 0x801EB4EC: jr          $ra
    // 0x801EB4F0: nop

    return;
    // 0x801EB4F0: nop

;}
RECOMP_FUNC void func_801EB4F4(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801EB4F4: lui         $v1, 0x800E
    ctx->r3 = S32(0X800E << 16);
    // 0x801EB4F8: addiu       $v1, $v1, -0x54DC
    ctx->r3 = ADD32(ctx->r3, -0X54DC);
    // 0x801EB4FC: lw          $t6, 0x0($v1)
    ctx->r14 = MEM_W(ctx->r3, 0X0);
    // 0x801EB500: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EB504: addiu       $sp, $sp, -0x58
    ctx->r29 = ADD32(ctx->r29, -0X58);
    // 0x801EB508: sw          $t6, -0x19CC($at)
    MEM_W(-0X19CC, ctx->r1) = ctx->r14;
    // 0x801EB50C: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EB510: sw          $zero, -0x19D0($at)
    MEM_W(-0X19D0, ctx->r1) = 0;
    // 0x801EB514: sw          $s0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r16;
    // 0x801EB518: addiu       $t7, $zero, 0x7
    ctx->r15 = ADD32(0, 0X7);
    // 0x801EB51C: addiu       $s0, $zero, 0x1
    ctx->r16 = ADD32(0, 0X1);
    // 0x801EB520: sw          $t7, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r15;
    // 0x801EB524: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EB528: sw          $s0, -0x19C8($at)
    MEM_W(-0X19C8, ctx->r1) = ctx->r16;
    // 0x801EB52C: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EB530: sw          $s0, -0x19C4($at)
    MEM_W(-0X19C4, ctx->r1) = ctx->r16;
    // 0x801EB534: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EB538: sw          $zero, -0x19C0($at)
    MEM_W(-0X19C0, ctx->r1) = 0;
    // 0x801EB53C: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EB540: sw          $zero, -0x19BC($at)
    MEM_W(-0X19BC, ctx->r1) = 0;
    // 0x801EB544: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x801EB548: sw          $zero, -0x54E4($at)
    MEM_W(-0X54E4, ctx->r1) = 0;
    // 0x801EB54C: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x801EB550: lw          $v0, -0x5608($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X5608);
    // 0x801EB554: lui         $at, 0x800D
    ctx->r1 = S32(0X800D << 16);
    // 0x801EB558: addiu       $t8, $zero, 0x3
    ctx->r24 = ADD32(0, 0X3);
    // 0x801EB55C: sw          $t8, 0x461C($at)
    MEM_W(0X461C, ctx->r1) = ctx->r24;
    // 0x801EB560: addiu       $t2, $zero, 0x2
    ctx->r10 = ADD32(0, 0X2);
    // 0x801EB564: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EB568: sw          $ra, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r31;
    // 0x801EB56C: beq         $v0, $zero, L_801EB584
    if (ctx->r2 == 0) {
        // 0x801EB570: sw          $t2, -0x4CC8($at)
        MEM_W(-0X4CC8, ctx->r1) = ctx->r10;
            goto L_801EB584;
    }
    // 0x801EB570: sw          $t2, -0x4CC8($at)
    MEM_W(-0X4CC8, ctx->r1) = ctx->r10;
    // 0x801EB574: beq         $v0, $s0, L_801EB630
    if (ctx->r2 == ctx->r16) {
        // 0x801EB578: lui         $t0, 0x801D
        ctx->r8 = S32(0X801D << 16);
            goto L_801EB630;
    }
    // 0x801EB578: lui         $t0, 0x801D
    ctx->r8 = S32(0X801D << 16);
    // 0x801EB57C: b           L_801EB6C0
    // 0x801EB580: lui         $t0, 0x801D
    ctx->r8 = S32(0X801D << 16);
        goto L_801EB6C0;
    // 0x801EB580: lui         $t0, 0x801D
    ctx->r8 = S32(0X801D << 16);
L_801EB584:
    // 0x801EB584: addiu       $t1, $zero, 0x4
    ctx->r9 = ADD32(0, 0X4);
    // 0x801EB588: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EB58C: sw          $t1, -0x19E0($at)
    MEM_W(-0X19E0, ctx->r1) = ctx->r9;
    // 0x801EB590: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x801EB594: sw          $s0, -0x54D8($at)
    MEM_W(-0X54D8, ctx->r1) = ctx->r16;
    // 0x801EB598: lui         $t0, 0x801D
    ctx->r8 = S32(0X801D << 16);
    // 0x801EB59C: lui         $at, 0x801A
    ctx->r1 = S32(0X801A << 16);
    // 0x801EB5A0: addiu       $t0, $t0, -0x4CD0
    ctx->r8 = ADD32(ctx->r8, -0X4CD0);
    // 0x801EB5A4: sw          $t1, -0x7D10($at)
    MEM_W(-0X7D10, ctx->r1) = ctx->r9;
    // 0x801EB5A8: sw          $t2, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r10;
    // 0x801EB5AC: lui         $t3, 0x800E
    ctx->r11 = S32(0X800E << 16);
    // 0x801EB5B0: lw          $t3, -0x5604($t3)
    ctx->r11 = MEM_W(ctx->r11, -0X5604);
    // 0x801EB5B4: lui         $t5, 0x800F
    ctx->r13 = S32(0X800F << 16);
    // 0x801EB5B8: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x801EB5BC: addiu       $t5, $t5, -0x53BC
    ctx->r13 = ADD32(ctx->r13, -0X53BC);
    // 0x801EB5C0: sll         $t4, $t3, 3
    ctx->r12 = S32(ctx->r11 << 3);
    // 0x801EB5C4: sw          $t2, -0x7E90($at)
    MEM_W(-0X7E90, ctx->r1) = ctx->r10;
    // 0x801EB5C8: addu        $v0, $t4, $t5
    ctx->r2 = ADD32(ctx->r12, ctx->r13);
    // 0x801EB5CC: lh          $v1, 0x6($v0)
    ctx->r3 = MEM_H(ctx->r2, 0X6);
    // 0x801EB5D0: lh          $a1, 0x0($v0)
    ctx->r5 = MEM_H(ctx->r2, 0X0);
    // 0x801EB5D4: lh          $a2, 0x2($v0)
    ctx->r6 = MEM_H(ctx->r2, 0X2);
    // 0x801EB5D8: lh          $a3, 0x4($v0)
    ctx->r7 = MEM_H(ctx->r2, 0X4);
    // 0x801EB5DC: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    // 0x801EB5E0: sw          $v1, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r3;
    // 0x801EB5E4: sw          $v1, 0x4C($sp)
    MEM_W(0X4C, ctx->r29) = ctx->r3;
    // 0x801EB5E8: sw          $a1, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r5;
    // 0x801EB5EC: sw          $a2, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r6;
    // 0x801EB5F0: jal         0x80096960
    // 0x801EB5F4: sw          $a3, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r7;
    func_80096960(rdram, ctx);
        goto after_0;
    // 0x801EB5F4: sw          $a3, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r7;
    after_0:
    // 0x801EB5F8: addiu       $t6, $zero, 0x3
    ctx->r14 = ADD32(0, 0X3);
    // 0x801EB5FC: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EB600: sw          $t6, -0x18D8($at)
    MEM_W(-0X18D8, ctx->r1) = ctx->r14;
    // 0x801EB604: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EB608: sw          $s0, -0x1908($at)
    MEM_W(-0X1908, ctx->r1) = ctx->r16;
    // 0x801EB60C: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EB610: addiu       $t7, $zero, 0x4
    ctx->r15 = ADD32(0, 0X4);
    // 0x801EB614: lui         $a1, 0x800E
    ctx->r5 = S32(0X800E << 16);
    // 0x801EB618: sw          $t7, -0x18FC($at)
    MEM_W(-0X18FC, ctx->r1) = ctx->r15;
    // 0x801EB61C: lw          $a1, -0x7E90($a1)
    ctx->r5 = MEM_W(ctx->r5, -0X7E90);
    // 0x801EB620: jal         0x800C4998
    // 0x801EB624: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    func_800C4998(rdram, ctx);
        goto after_1;
    // 0x801EB624: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    after_1:
    // 0x801EB628: b           L_801EB754
    // 0x801EB62C: nop

        goto L_801EB754;
    // 0x801EB62C: nop

L_801EB630:
    // 0x801EB630: addiu       $t8, $zero, 0xB
    ctx->r24 = ADD32(0, 0XB);
    // 0x801EB634: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EB638: sw          $t8, -0x19E0($at)
    MEM_W(-0X19E0, ctx->r1) = ctx->r24;
    // 0x801EB63C: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x801EB640: sw          $s0, -0x54D8($at)
    MEM_W(-0X54D8, ctx->r1) = ctx->r16;
    // 0x801EB644: lui         $at, 0x801A
    ctx->r1 = S32(0X801A << 16);
    // 0x801EB648: addiu       $t0, $t0, -0x4CD0
    ctx->r8 = ADD32(ctx->r8, -0X4CD0);
    // 0x801EB64C: sw          $s0, -0x7D10($at)
    MEM_W(-0X7D10, ctx->r1) = ctx->r16;
    // 0x801EB650: sw          $s0, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r16;
    // 0x801EB654: lui         $t3, 0x800E
    ctx->r11 = S32(0X800E << 16);
    // 0x801EB658: lw          $t3, -0x5604($t3)
    ctx->r11 = MEM_W(ctx->r11, -0X5604);
    // 0x801EB65C: lui         $a1, 0x800F
    ctx->r5 = S32(0X800F << 16);
    // 0x801EB660: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x801EB664: sll         $t4, $t3, 3
    ctx->r12 = S32(ctx->r11 << 3);
    // 0x801EB668: addu        $a1, $a1, $t4
    ctx->r5 = ADD32(ctx->r5, ctx->r12);
    // 0x801EB66C: lh          $a1, -0x53BC($a1)
    ctx->r5 = MEM_H(ctx->r5, -0X53BC);
    // 0x801EB670: sw          $s0, -0x7E90($at)
    MEM_W(-0X7E90, ctx->r1) = ctx->r16;
    // 0x801EB674: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x801EB678: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    // 0x801EB67C: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    // 0x801EB680: sw          $zero, 0x10($sp)
    MEM_W(0X10, ctx->r29) = 0;
    // 0x801EB684: sw          $zero, 0x4C($sp)
    MEM_W(0X4C, ctx->r29) = 0;
    // 0x801EB688: sw          $zero, 0x44($sp)
    MEM_W(0X44, ctx->r29) = 0;
    // 0x801EB68C: sw          $zero, 0x48($sp)
    MEM_W(0X48, ctx->r29) = 0;
    // 0x801EB690: jal         0x80096960
    // 0x801EB694: sw          $a1, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r5;
    func_80096960(rdram, ctx);
        goto after_2;
    // 0x801EB694: sw          $a1, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r5;
    after_2:
    // 0x801EB698: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EB69C: sw          $s0, -0x18D8($at)
    MEM_W(-0X18D8, ctx->r1) = ctx->r16;
    // 0x801EB6A0: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EB6A4: lui         $a1, 0x800E
    ctx->r5 = S32(0X800E << 16);
    // 0x801EB6A8: sw          $zero, -0x1908($at)
    MEM_W(-0X1908, ctx->r1) = 0;
    // 0x801EB6AC: lw          $a1, -0x7E90($a1)
    ctx->r5 = MEM_W(ctx->r5, -0X7E90);
    // 0x801EB6B0: jal         0x800C4998
    // 0x801EB6B4: addiu       $a0, $zero, 0x3
    ctx->r4 = ADD32(0, 0X3);
    func_800C4998(rdram, ctx);
        goto after_3;
    // 0x801EB6B4: addiu       $a0, $zero, 0x3
    ctx->r4 = ADD32(0, 0X3);
    after_3:
    // 0x801EB6B8: b           L_801EB754
    // 0x801EB6BC: nop

        goto L_801EB754;
    // 0x801EB6BC: nop

L_801EB6C0:
    // 0x801EB6C0: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EB6C4: sw          $s0, -0x19E0($at)
    MEM_W(-0X19E0, ctx->r1) = ctx->r16;
    // 0x801EB6C8: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x801EB6CC: sw          $t2, -0x54D8($at)
    MEM_W(-0X54D8, ctx->r1) = ctx->r10;
    // 0x801EB6D0: lui         $at, 0x801A
    ctx->r1 = S32(0X801A << 16);
    // 0x801EB6D4: addiu       $t0, $t0, -0x4CD0
    ctx->r8 = ADD32(ctx->r8, -0X4CD0);
    // 0x801EB6D8: sw          $t2, -0x7D10($at)
    MEM_W(-0X7D10, ctx->r1) = ctx->r10;
    // 0x801EB6DC: sw          $s0, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r16;
    // 0x801EB6E0: lui         $t6, 0x800E
    ctx->r14 = S32(0X800E << 16);
    // 0x801EB6E4: lw          $t6, -0x5604($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X5604);
    // 0x801EB6E8: lui         $t8, 0x800F
    ctx->r24 = S32(0X800F << 16);
    // 0x801EB6EC: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x801EB6F0: addiu       $t8, $t8, -0x53BC
    ctx->r24 = ADD32(ctx->r24, -0X53BC);
    // 0x801EB6F4: sll         $t7, $t6, 3
    ctx->r15 = S32(ctx->r14 << 3);
    // 0x801EB6F8: sw          $s0, -0x7E90($at)
    MEM_W(-0X7E90, ctx->r1) = ctx->r16;
    // 0x801EB6FC: addu        $v0, $t7, $t8
    ctx->r2 = ADD32(ctx->r15, ctx->r24);
    // 0x801EB700: lh          $a1, 0x0($v0)
    ctx->r5 = MEM_H(ctx->r2, 0X0);
    // 0x801EB704: lh          $a2, 0x2($v0)
    ctx->r6 = MEM_H(ctx->r2, 0X2);
    // 0x801EB708: sw          $zero, 0x48($sp)
    MEM_W(0X48, ctx->r29) = 0;
    // 0x801EB70C: addiu       $a0, $zero, 0x4
    ctx->r4 = ADD32(0, 0X4);
    // 0x801EB710: sw          $zero, 0x4C($sp)
    MEM_W(0X4C, ctx->r29) = 0;
    // 0x801EB714: or          $a3, $a1, $zero
    ctx->r7 = ctx->r5 | 0;
    // 0x801EB718: sw          $a1, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r5;
    // 0x801EB71C: sw          $a2, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r6;
    // 0x801EB720: jal         0x80096960
    // 0x801EB724: sw          $a2, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r6;
    func_80096960(rdram, ctx);
        goto after_4;
    // 0x801EB724: sw          $a2, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r6;
    after_4:
    // 0x801EB728: addiu       $t9, $zero, 0x3
    ctx->r25 = ADD32(0, 0X3);
    // 0x801EB72C: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EB730: sw          $t9, -0x18D8($at)
    MEM_W(-0X18D8, ctx->r1) = ctx->r25;
    // 0x801EB734: lui         $at, 0x800D
    ctx->r1 = S32(0X800D << 16);
    // 0x801EB738: sh          $zero, 0x4970($at)
    MEM_H(0X4970, ctx->r1) = 0;
    // 0x801EB73C: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EB740: lui         $a1, 0x800E
    ctx->r5 = S32(0X800E << 16);
    // 0x801EB744: sw          $zero, -0x1908($at)
    MEM_W(-0X1908, ctx->r1) = 0;
    // 0x801EB748: lw          $a1, -0x7E90($a1)
    ctx->r5 = MEM_W(ctx->r5, -0X7E90);
    // 0x801EB74C: jal         0x800C4998
    // 0x801EB750: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    func_800C4998(rdram, ctx);
        goto after_5;
    // 0x801EB750: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_5:
L_801EB754:
    // 0x801EB754: lui         $a1, 0x800D
    ctx->r5 = S32(0X800D << 16);
    // 0x801EB758: lui         $a2, 0x800E
    ctx->r6 = S32(0X800E << 16);
    // 0x801EB75C: addiu       $a2, $a2, -0x7E8C
    ctx->r6 = ADD32(ctx->r6, -0X7E8C);
    // 0x801EB760: addiu       $a1, $a1, 0x49B0
    ctx->r5 = ADD32(ctx->r5, 0X49B0);
    // 0x801EB764: addiu       $t3, $zero, 0x14
    ctx->r11 = ADD32(0, 0X14);
    // 0x801EB768: addiu       $t4, $zero, 0x5
    ctx->r12 = ADD32(0, 0X5);
    // 0x801EB76C: sw          $t3, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r11;
    // 0x801EB770: sw          $t4, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r12;
    // 0x801EB774: lui         $t5, 0x801D
    ctx->r13 = S32(0X801D << 16);
    // 0x801EB778: lw          $t5, -0x19E0($t5)
    ctx->r13 = MEM_W(ctx->r13, -0X19E0);
    // 0x801EB77C: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x801EB780: addiu       $v0, $v0, -0x19F8
    ctx->r2 = ADD32(ctx->r2, -0X19F8);
    // 0x801EB784: lui         $t6, 0x800E
    ctx->r14 = S32(0X800E << 16);
    // 0x801EB788: sw          $t5, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r13;
    // 0x801EB78C: lw          $t6, -0x54D8($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X54D8);
    // 0x801EB790: lui         $a0, 0x801A
    ctx->r4 = S32(0X801A << 16);
    // 0x801EB794: lui         $t9, 0x801D
    ctx->r25 = S32(0X801D << 16);
    // 0x801EB798: sh          $t6, 0x4($v0)
    MEM_H(0X4, ctx->r2) = ctx->r14;
    // 0x801EB79C: lw          $a0, -0x7D10($a0)
    ctx->r4 = MEM_W(ctx->r4, -0X7D10);
    // 0x801EB7A0: sw          $t3, 0x8($v0)
    MEM_W(0X8, ctx->r2) = ctx->r11;
    // 0x801EB7A4: sw          $t4, 0xC($v0)
    MEM_W(0XC, ctx->r2) = ctx->r12;
    // 0x801EB7A8: sh          $a0, 0x6($v0)
    MEM_H(0X6, ctx->r2) = ctx->r4;
    // 0x801EB7AC: lw          $t9, -0x18D8($t9)
    ctx->r25 = MEM_W(ctx->r25, -0X18D8);
    // 0x801EB7B0: sw          $zero, 0x14($v0)
    MEM_W(0X14, ctx->r2) = 0;
    // 0x801EB7B4: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x801EB7B8: sw          $t9, 0x10($v0)
    MEM_W(0X10, ctx->r2) = ctx->r25;
    // 0x801EB7BC: sw          $zero, -0x7E88($at)
    MEM_W(-0X7E88, ctx->r1) = 0;
    // 0x801EB7C0: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EB7C4: sw          $s0, -0x1A00($at)
    MEM_W(-0X1A00, ctx->r1) = ctx->r16;
    // 0x801EB7C8: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EB7CC: sw          $zero, -0x4CCC($at)
    MEM_W(-0X4CCC, ctx->r1) = 0;
    // 0x801EB7D0: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EB7D4: sh          $zero, -0x1910($at)
    MEM_H(-0X1910, ctx->r1) = 0;
    // 0x801EB7D8: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x801EB7DC: blez        $a0, L_801EB858
    if (SIGNED(ctx->r4) <= 0) {
        // 0x801EB7E0: sh          $zero, -0x5498($at)
        MEM_H(-0X5498, ctx->r1) = 0;
            goto L_801EB858;
    }
    // 0x801EB7E0: sh          $zero, -0x5498($at)
    MEM_H(-0X5498, ctx->r1) = 0;
    // 0x801EB7E4: lui         $t4, 0x800E
    ctx->r12 = S32(0X800E << 16);
    // 0x801EB7E8: lw          $t4, -0x7E90($t4)
    ctx->r12 = MEM_W(ctx->r12, -0X7E90);
    // 0x801EB7EC: lui         $t6, 0x800E
    ctx->r14 = S32(0X800E << 16);
    // 0x801EB7F0: addiu       $t6, $t6, -0x695C
    ctx->r14 = ADD32(ctx->r14, -0X695C);
    // 0x801EB7F4: sll         $t5, $t4, 2
    ctx->r13 = S32(ctx->r12 << 2);
    // 0x801EB7F8: subu        $t5, $t5, $t4
    ctx->r13 = SUB32(ctx->r13, ctx->r12);
    // 0x801EB7FC: sll         $t5, $t5, 4
    ctx->r13 = S32(ctx->r13 << 4);
    // 0x801EB800: lui         $v1, 0x8019
    ctx->r3 = S32(0X8019 << 16);
    // 0x801EB804: addiu       $a1, $sp, 0x40
    ctx->r5 = ADD32(ctx->r29, 0X40);
    // 0x801EB808: sll         $t7, $a0, 2
    ctx->r15 = S32(ctx->r4 << 2);
    // 0x801EB80C: addu        $t0, $t7, $a1
    ctx->r8 = ADD32(ctx->r15, ctx->r5);
    // 0x801EB810: addiu       $v1, $v1, 0x2690
    ctx->r3 = ADD32(ctx->r3, 0X2690);
    // 0x801EB814: addu        $a3, $t5, $t6
    ctx->r7 = ADD32(ctx->r13, ctx->r14);
    // 0x801EB818: addiu       $a2, $zero, 0xC
    ctx->r6 = ADD32(0, 0XC);
L_801EB81C:
    // 0x801EB81C: lw          $a0, 0x0($a1)
    ctx->r4 = MEM_W(ctx->r5, 0X0);
    // 0x801EB820: addiu       $a1, $a1, 0x4
    ctx->r5 = ADD32(ctx->r5, 0X4);
    // 0x801EB824: sltu        $at, $a1, $t0
    ctx->r1 = ctx->r5 < ctx->r8 ? 1 : 0;
    // 0x801EB828: multu       $a0, $a2
    result = U64(U32(ctx->r4)) * U64(U32(ctx->r6)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x801EB82C: addiu       $v1, $v1, 0x1718
    ctx->r3 = ADD32(ctx->r3, 0X1718);
    // 0x801EB830: sw          $a0, -0xBB0($v1)
    MEM_W(-0XBB0, ctx->r3) = ctx->r4;
    // 0x801EB834: mflo        $t8
    ctx->r24 = lo;
    // 0x801EB838: addu        $v0, $a3, $t8
    ctx->r2 = ADD32(ctx->r7, ctx->r24);
    // 0x801EB83C: lw          $t9, 0x0($v0)
    ctx->r25 = MEM_W(ctx->r2, 0X0);
    // 0x801EB840: lw          $t4, 0x4($v0)
    ctx->r12 = MEM_W(ctx->r2, 0X4);
    // 0x801EB844: lw          $t5, 0x8($v0)
    ctx->r13 = MEM_W(ctx->r2, 0X8);
    // 0x801EB848: sw          $t9, -0xBAC($v1)
    MEM_W(-0XBAC, ctx->r3) = ctx->r25;
    // 0x801EB84C: sw          $t4, -0xBA8($v1)
    MEM_W(-0XBA8, ctx->r3) = ctx->r12;
    // 0x801EB850: bne         $at, $zero, L_801EB81C
    if (ctx->r1 != 0) {
        // 0x801EB854: sw          $t5, -0xBA4($v1)
        MEM_W(-0XBA4, ctx->r3) = ctx->r13;
            goto L_801EB81C;
    }
    // 0x801EB854: sw          $t5, -0xBA4($v1)
    MEM_W(-0XBA4, ctx->r3) = ctx->r13;
L_801EB858:
    // 0x801EB858: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x801EB85C: addiu       $v1, $v1, -0x190C
    ctx->r3 = ADD32(ctx->r3, -0X190C);
    // 0x801EB860: sh          $zero, 0x2($v1)
    MEM_H(0X2, ctx->r3) = 0;
    // 0x801EB864: lh          $t6, 0x2($v1)
    ctx->r14 = MEM_H(ctx->r3, 0X2);
    // 0x801EB868: addiu       $t7, $zero, 0x2
    ctx->r15 = ADD32(0, 0X2);
    // 0x801EB86C: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EB870: sh          $t6, 0x0($v1)
    MEM_H(0X0, ctx->r3) = ctx->r14;
    // 0x801EB874: sw          $t7, -0x19B8($at)
    MEM_W(-0X19B8, ctx->r1) = ctx->r15;
    // 0x801EB878: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x801EB87C: lw          $v0, -0x7E90($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X7E90);
    // 0x801EB880: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EB884: sw          $zero, -0x19B4($at)
    MEM_W(-0X19B4, ctx->r1) = 0;
    // 0x801EB888: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EB88C: bgez        $v0, L_801EB898
    if (SIGNED(ctx->r2) >= 0) {
        // 0x801EB890: sw          $zero, -0x19B0($at)
        MEM_W(-0X19B0, ctx->r1) = 0;
            goto L_801EB898;
    }
    // 0x801EB890: sw          $zero, -0x19B0($at)
    MEM_W(-0X19B0, ctx->r1) = 0;
    // 0x801EB894: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_801EB898:
    // 0x801EB898: slti        $at, $v0, 0x9
    ctx->r1 = SIGNED(ctx->r2) < 0X9 ? 1 : 0;
    // 0x801EB89C: bne         $at, $zero, L_801EB8A8
    if (ctx->r1 != 0) {
        // 0x801EB8A0: lui         $a0, 0x806
        ctx->r4 = S32(0X806 << 16);
            goto L_801EB8A8;
    }
    // 0x801EB8A0: lui         $a0, 0x806
    ctx->r4 = S32(0X806 << 16);
    // 0x801EB8A4: addiu       $v0, $zero, 0x8
    ctx->r2 = ADD32(0, 0X8);
L_801EB8A8:
    // 0x801EB8A8: lui         $t8, 0x800E
    ctx->r24 = S32(0X800E << 16);
    // 0x801EB8AC: addiu       $t8, $t8, -0x4A98
    ctx->r24 = ADD32(ctx->r24, -0X4A98);
    // 0x801EB8B0: sll         $t3, $v0, 2
    ctx->r11 = S32(ctx->r2 << 2);
    // 0x801EB8B4: addu        $v1, $t3, $t8
    ctx->r3 = ADD32(ctx->r11, ctx->r24);
    // 0x801EB8B8: lh          $a1, 0x0($v1)
    ctx->r5 = MEM_H(ctx->r3, 0X0);
    // 0x801EB8BC: jal         0x8009684C
    // 0x801EB8C0: lh          $a2, 0x2($v1)
    ctx->r6 = MEM_H(ctx->r3, 0X2);
    func_8009684C(rdram, ctx);
        goto after_6;
    // 0x801EB8C0: lh          $a2, 0x2($v1)
    ctx->r6 = MEM_H(ctx->r3, 0X2);
    after_6:
    // 0x801EB8C4: addiu       $a0, $zero, 0x2
    ctx->r4 = ADD32(0, 0X2);
    // 0x801EB8C8: addiu       $a1, $zero, 0x4
    ctx->r5 = ADD32(0, 0X4);
    // 0x801EB8CC: jal         0x801E6FB0
    // 0x801EB8D0: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    FadeTransition_SetProps(rdram, ctx);
        goto after_7;
    // 0x801EB8D0: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    after_7:
    // 0x801EB8D4: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    // 0x801EB8D8: jal         0x801E6A4C
    // 0x801EB8DC: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_801E6A4C(rdram, ctx);
        goto after_8;
    // 0x801EB8DC: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_8:
    // 0x801EB8E0: lui         $v0, 0x8022
    ctx->r2 = S32(0X8022 << 16);
    // 0x801EB8E4: addiu       $v0, $v0, 0x7C80
    ctx->r2 = ADD32(ctx->r2, 0X7C80);
    // 0x801EB8E8: addiu       $t9, $zero, 0x3
    ctx->r25 = ADD32(0, 0X3);
    // 0x801EB8EC: sw          $t9, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r25;
    // 0x801EB8F0: lui         $t4, 0x800E
    ctx->r12 = S32(0X800E << 16);
    // 0x801EB8F4: lw          $t4, -0x54D8($t4)
    ctx->r12 = MEM_W(ctx->r12, -0X54D8);
    // 0x801EB8F8: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x801EB8FC: bnel        $t4, $at, L_801EB90C
    if (ctx->r12 != ctx->r1) {
        // 0x801EB900: lw          $ra, 0x24($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X24);
            goto L_801EB90C;
    }
    goto skip_0;
    // 0x801EB900: lw          $ra, 0x24($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X24);
    skip_0:
    // 0x801EB904: sw          $t9, 0x10C($v0)
    MEM_W(0X10C, ctx->r2) = ctx->r25;
    // 0x801EB908: lw          $ra, 0x24($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X24);
L_801EB90C:
    // 0x801EB90C: lw          $s0, 0x20($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X20);
    // 0x801EB910: addiu       $sp, $sp, 0x58
    ctx->r29 = ADD32(ctx->r29, 0X58);
    // 0x801EB914: jr          $ra
    // 0x801EB918: nop

    return;
    // 0x801EB918: nop

;}
RECOMP_FUNC void func_801EB91C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801EB91C: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x801EB920: addiu       $v0, $v0, -0x54DC
    ctx->r2 = ADD32(ctx->r2, -0X54DC);
    // 0x801EB924: lw          $t6, 0x0($v0)
    ctx->r14 = MEM_W(ctx->r2, 0X0);
    // 0x801EB928: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EB92C: addiu       $t7, $zero, 0x1E
    ctx->r15 = ADD32(0, 0X1E);
    // 0x801EB930: sw          $t6, -0x19CC($at)
    MEM_W(-0X19CC, ctx->r1) = ctx->r14;
    // 0x801EB934: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EB938: sw          $zero, -0x19D0($at)
    MEM_W(-0X19D0, ctx->r1) = 0;
    // 0x801EB93C: sw          $t7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r15;
    // 0x801EB940: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EB944: addiu       $t8, $zero, 0x8
    ctx->r24 = ADD32(0, 0X8);
    // 0x801EB948: sw          $t8, -0x19C8($at)
    MEM_W(-0X19C8, ctx->r1) = ctx->r24;
    // 0x801EB94C: addiu       $a3, $zero, 0x1
    ctx->r7 = ADD32(0, 0X1);
    // 0x801EB950: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EB954: sw          $a3, -0x19C4($at)
    MEM_W(-0X19C4, ctx->r1) = ctx->r7;
    // 0x801EB958: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EB95C: sw          $zero, -0x19C0($at)
    MEM_W(-0X19C0, ctx->r1) = 0;
    // 0x801EB960: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EB964: sw          $zero, -0x19BC($at)
    MEM_W(-0X19BC, ctx->r1) = 0;
    // 0x801EB968: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x801EB96C: sw          $zero, -0x54E4($at)
    MEM_W(-0X54E4, ctx->r1) = 0;
    // 0x801EB970: lui         $t9, 0x800E
    ctx->r25 = S32(0X800E << 16);
    // 0x801EB974: lw          $t9, -0x7DC0($t9)
    ctx->r25 = MEM_W(ctx->r25, -0X7DC0);
    // 0x801EB978: addiu       $t1, $zero, 0x3
    ctx->r9 = ADD32(0, 0X3);
    // 0x801EB97C: lui         $at, 0x800D
    ctx->r1 = S32(0X800D << 16);
    // 0x801EB980: sw          $t1, 0x461C($at)
    MEM_W(0X461C, ctx->r1) = ctx->r9;
    // 0x801EB984: addiu       $sp, $sp, -0x28
    ctx->r29 = ADD32(ctx->r29, -0X28);
    // 0x801EB988: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x801EB98C: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x801EB990: beq         $t9, $zero, L_801EB9AC
    if (ctx->r25 == 0) {
        // 0x801EB994: sw          $a3, -0x54D8($at)
        MEM_W(-0X54D8, ctx->r1) = ctx->r7;
            goto L_801EB9AC;
    }
    // 0x801EB994: sw          $a3, -0x54D8($at)
    MEM_W(-0X54D8, ctx->r1) = ctx->r7;
    // 0x801EB998: lui         $t4, 0x801C
    ctx->r12 = S32(0X801C << 16);
    // 0x801EB99C: lw          $t4, 0x3A10($t4)
    ctx->r12 = MEM_W(ctx->r12, 0X3A10);
    // 0x801EB9A0: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x801EB9A4: addiu       $v1, $v1, -0x4CD0
    ctx->r3 = ADD32(ctx->r3, -0X4CD0);
    // 0x801EB9A8: sw          $t4, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r12;
L_801EB9AC:
    // 0x801EB9AC: lui         $t5, 0x801D
    ctx->r13 = S32(0X801D << 16);
    // 0x801EB9B0: lui         $t7, 0x801D
    ctx->r15 = S32(0X801D << 16);
    // 0x801EB9B4: lw          $t7, -0x4CCC($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X4CCC);
    // 0x801EB9B8: lw          $t5, -0x4CC8($t5)
    ctx->r13 = MEM_W(ctx->r13, -0X4CC8);
    // 0x801EB9BC: lui         $t4, 0x800F
    ctx->r12 = S32(0X800F << 16);
    // 0x801EB9C0: sll         $t8, $t7, 1
    ctx->r24 = S32(ctx->r15 << 1);
    // 0x801EB9C4: sll         $t6, $t5, 4
    ctx->r14 = S32(ctx->r13 << 4);
    // 0x801EB9C8: addu        $t9, $t6, $t8
    ctx->r25 = ADD32(ctx->r14, ctx->r24);
    // 0x801EB9CC: addu        $t4, $t4, $t9
    ctx->r12 = ADD32(ctx->r12, ctx->r25);
    // 0x801EB9D0: lh          $t0, -0x53EC($t4)
    ctx->r8 = MEM_H(ctx->r12, -0X53EC);
    // 0x801EB9D4: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x801EB9D8: lui         $t2, 0x800E
    ctx->r10 = S32(0X800E << 16);
    // 0x801EB9DC: addiu       $t2, $t2, -0x7E90
    ctx->r10 = ADD32(ctx->r10, -0X7E90);
    // 0x801EB9E0: addiu       $v1, $v1, -0x4CD0
    ctx->r3 = ADD32(ctx->r3, -0X4CD0);
    // 0x801EB9E4: sw          $t0, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r8;
    // 0x801EB9E8: sw          $t0, 0x0($t2)
    MEM_W(0X0, ctx->r10) = ctx->r8;
    // 0x801EB9EC: bne         $t0, $zero, L_801EBA10
    if (ctx->r8 != 0) {
        // 0x801EB9F0: or          $v0, $t0, $zero
        ctx->r2 = ctx->r8 | 0;
            goto L_801EBA10;
    }
    // 0x801EB9F0: or          $v0, $t0, $zero
    ctx->r2 = ctx->r8 | 0;
    // 0x801EB9F4: lui         $a0, 0x800E
    ctx->r4 = S32(0X800E << 16);
    // 0x801EB9F8: addiu       $a0, $a0, -0x5600
    ctx->r4 = ADD32(ctx->r4, -0X5600);
    // 0x801EB9FC: lh          $v1, 0x0($a0)
    ctx->r3 = MEM_H(ctx->r4, 0X0);
    // 0x801EBA00: slti        $at, $v1, 0x270F
    ctx->r1 = SIGNED(ctx->r3) < 0X270F ? 1 : 0;
    // 0x801EBA04: beq         $at, $zero, L_801EBA10
    if (ctx->r1 == 0) {
        // 0x801EBA08: addiu       $t5, $v1, 0x1
        ctx->r13 = ADD32(ctx->r3, 0X1);
            goto L_801EBA10;
    }
    // 0x801EBA08: addiu       $t5, $v1, 0x1
    ctx->r13 = ADD32(ctx->r3, 0X1);
    // 0x801EBA0C: sh          $t5, 0x0($a0)
    MEM_H(0X0, ctx->r4) = ctx->r13;
L_801EBA10:
    // 0x801EBA10: sll         $t6, $v0, 1
    ctx->r14 = S32(ctx->r2 << 1);
    // 0x801EBA14: lui         $t8, 0x800F
    ctx->r24 = S32(0X800F << 16);
    // 0x801EBA18: addu        $t8, $t8, $t6
    ctx->r24 = ADD32(ctx->r24, ctx->r14);
    // 0x801EBA1C: lh          $t8, -0x5414($t8)
    ctx->r24 = MEM_H(ctx->r24, -0X5414);
    // 0x801EBA20: addiu       $t7, $zero, 0xA
    ctx->r15 = ADD32(0, 0XA);
    // 0x801EBA24: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EBA28: sw          $t7, -0x19E0($at)
    MEM_W(-0X19E0, ctx->r1) = ctx->r15;
    // 0x801EBA2C: lui         $at, 0x800D
    ctx->r1 = S32(0X800D << 16);
    // 0x801EBA30: sw          $t8, 0x49B0($at)
    MEM_W(0X49B0, ctx->r1) = ctx->r24;
    // 0x801EBA34: addiu       $v1, $zero, 0x5
    ctx->r3 = ADD32(0, 0X5);
    // 0x801EBA38: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x801EBA3C: bne         $a3, $t0, L_801EBA54
    if (ctx->r7 != ctx->r8) {
        // 0x801EBA40: sw          $v1, -0x7E8C($at)
        MEM_W(-0X7E8C, ctx->r1) = ctx->r3;
            goto L_801EBA54;
    }
    // 0x801EBA40: sw          $v1, -0x7E8C($at)
    MEM_W(-0X7E8C, ctx->r1) = ctx->r3;
    // 0x801EBA44: addiu       $t9, $zero, 0x4
    ctx->r25 = ADD32(0, 0X4);
    // 0x801EBA48: lui         $at, 0x801A
    ctx->r1 = S32(0X801A << 16);
    // 0x801EBA4C: b           L_801EBA74
    // 0x801EBA50: sw          $t9, -0x7D10($at)
    MEM_W(-0X7D10, ctx->r1) = ctx->r25;
        goto L_801EBA74;
    // 0x801EBA50: sw          $t9, -0x7D10($at)
    MEM_W(-0X7D10, ctx->r1) = ctx->r25;
L_801EBA54:
    // 0x801EBA54: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x801EBA58: bne         $t0, $at, L_801EBA6C
    if (ctx->r8 != ctx->r1) {
        // 0x801EBA5C: addiu       $t4, $zero, 0x2
        ctx->r12 = ADD32(0, 0X2);
            goto L_801EBA6C;
    }
    // 0x801EBA5C: addiu       $t4, $zero, 0x2
    ctx->r12 = ADD32(0, 0X2);
    // 0x801EBA60: lui         $at, 0x801A
    ctx->r1 = S32(0X801A << 16);
    // 0x801EBA64: b           L_801EBA74
    // 0x801EBA68: sw          $t4, -0x7D10($at)
    MEM_W(-0X7D10, ctx->r1) = ctx->r12;
        goto L_801EBA74;
    // 0x801EBA68: sw          $t4, -0x7D10($at)
    MEM_W(-0X7D10, ctx->r1) = ctx->r12;
L_801EBA6C:
    // 0x801EBA6C: lui         $at, 0x801A
    ctx->r1 = S32(0X801A << 16);
    // 0x801EBA70: sw          $a3, -0x7D10($at)
    MEM_W(-0X7D10, ctx->r1) = ctx->r7;
L_801EBA74:
    // 0x801EBA74: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801EBA78: beq         $a3, $t0, L_801EBA8C
    if (ctx->r7 == ctx->r8) {
        // 0x801EBA7C: sw          $v1, 0x7C80($at)
        MEM_W(0X7C80, ctx->r1) = ctx->r3;
            goto L_801EBA8C;
    }
    // 0x801EBA7C: sw          $v1, 0x7C80($at)
    MEM_W(0X7C80, ctx->r1) = ctx->r3;
    // 0x801EBA80: addiu       $at, $zero, 0x4
    ctx->r1 = ADD32(0, 0X4);
    // 0x801EBA84: bne         $t0, $at, L_801EBA98
    if (ctx->r8 != ctx->r1) {
        // 0x801EBA88: addiu       $t5, $zero, 0x2
        ctx->r13 = ADD32(0, 0X2);
            goto L_801EBA98;
    }
    // 0x801EBA88: addiu       $t5, $zero, 0x2
    ctx->r13 = ADD32(0, 0X2);
L_801EBA8C:
    // 0x801EBA8C: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EBA90: b           L_801EBAA0
    // 0x801EBA94: sw          $a3, -0x19B8($at)
    MEM_W(-0X19B8, ctx->r1) = ctx->r7;
        goto L_801EBAA0;
    // 0x801EBA94: sw          $a3, -0x19B8($at)
    MEM_W(-0X19B8, ctx->r1) = ctx->r7;
L_801EBA98:
    // 0x801EBA98: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EBA9C: sw          $t5, -0x19B8($at)
    MEM_W(-0X19B8, ctx->r1) = ctx->r13;
L_801EBAA0:
    // 0x801EBAA0: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EBAA4: sw          $zero, -0x19B4($at)
    MEM_W(-0X19B4, ctx->r1) = 0;
    // 0x801EBAA8: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EBAAC: sw          $t1, -0x19B0($at)
    MEM_W(-0X19B0, ctx->r1) = ctx->r9;
    // 0x801EBAB0: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x801EBAB4: sw          $a3, -0x7E88($at)
    MEM_W(-0X7E88, ctx->r1) = ctx->r7;
    // 0x801EBAB8: addiu       $a0, $zero, 0x4
    ctx->r4 = ADD32(0, 0X4);
    // 0x801EBABC: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x801EBAC0: jal         0x801E6FB0
    // 0x801EBAC4: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    FadeTransition_SetProps(rdram, ctx);
        goto after_0;
    // 0x801EBAC4: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    after_0:
    // 0x801EBAC8: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    // 0x801EBACC: jal         0x801E6A4C
    // 0x801EBAD0: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_801E6A4C(rdram, ctx);
        goto after_1;
    // 0x801EBAD0: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_1:
    // 0x801EBAD4: lui         $t7, 0x800D
    ctx->r15 = S32(0X800D << 16);
    // 0x801EBAD8: lw          $t7, 0x48DC($t7)
    ctx->r15 = MEM_W(ctx->r15, 0X48DC);
    // 0x801EBADC: lui         $t3, 0x800E
    ctx->r11 = S32(0X800E << 16);
    // 0x801EBAE0: addiu       $t3, $t3, -0x5650
    ctx->r11 = ADD32(ctx->r11, -0X5650);
    // 0x801EBAE4: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x801EBAE8: sll         $t6, $t7, 2
    ctx->r14 = S32(ctx->r15 << 2);
    // 0x801EBAEC: sw          $zero, -0x55F8($at)
    MEM_W(-0X55F8, ctx->r1) = 0;
    // 0x801EBAF0: addu        $t8, $t3, $t6
    ctx->r24 = ADD32(ctx->r11, ctx->r14);
    // 0x801EBAF4: lw          $a1, 0x0($t8)
    ctx->r5 = MEM_W(ctx->r24, 0X0);
    // 0x801EBAF8: jal         0x80047E50
    // 0x801EBAFC: sw          $a1, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r5;
    SysUtils_Rand(rdram, ctx);
        goto after_2;
    // 0x801EBAFC: sw          $a1, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r5;
    after_2:
    // 0x801EBB00: lw          $a1, 0x20($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X20);
    // 0x801EBB04: lui         $t3, 0x800E
    ctx->r11 = S32(0X800E << 16);
    // 0x801EBB08: andi        $v1, $v0, 0x3
    ctx->r3 = ctx->r2 & 0X3;
    // 0x801EBB0C: or          $a2, $v1, $zero
    ctx->r6 = ctx->r3 | 0;
    // 0x801EBB10: addiu       $t3, $t3, -0x5650
    ctx->r11 = ADD32(ctx->r11, -0X5650);
    // 0x801EBB14: bne         $a1, $v1, L_801EBB38
    if (ctx->r5 != ctx->r3) {
        // 0x801EBB18: addiu       $a3, $zero, 0x1
        ctx->r7 = ADD32(0, 0X1);
            goto L_801EBB38;
    }
    // 0x801EBB18: addiu       $a3, $zero, 0x1
    ctx->r7 = ADD32(0, 0X1);
    // 0x801EBB1C: addiu       $a2, $v1, 0x1
    ctx->r6 = ADD32(ctx->r3, 0X1);
    // 0x801EBB20: bgez        $a2, L_801EBB34
    if (SIGNED(ctx->r6) >= 0) {
        // 0x801EBB24: andi        $t9, $a2, 0x3
        ctx->r25 = ctx->r6 & 0X3;
            goto L_801EBB34;
    }
    // 0x801EBB24: andi        $t9, $a2, 0x3
    ctx->r25 = ctx->r6 & 0X3;
    // 0x801EBB28: beq         $t9, $zero, L_801EBB34
    if (ctx->r25 == 0) {
        // 0x801EBB2C: nop
    
            goto L_801EBB34;
    }
    // 0x801EBB2C: nop

    // 0x801EBB30: addiu       $t9, $t9, -0x4
    ctx->r25 = ADD32(ctx->r25, -0X4);
L_801EBB34:
    // 0x801EBB34: or          $a2, $t9, $zero
    ctx->r6 = ctx->r25 | 0;
L_801EBB38:
    // 0x801EBB38: lui         $t4, 0x801D
    ctx->r12 = S32(0X801D << 16);
    // 0x801EBB3C: lh          $t4, -0x190C($t4)
    ctx->r12 = MEM_H(ctx->r12, -0X190C);
    // 0x801EBB40: lui         $t5, 0x800E
    ctx->r13 = S32(0X800E << 16);
    // 0x801EBB44: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    // 0x801EBB48: beq         $t4, $zero, L_801EBB54
    if (ctx->r12 == 0) {
        // 0x801EBB4C: nop
    
            goto L_801EBB54;
    }
    // 0x801EBB4C: nop

    // 0x801EBB50: addiu       $a1, $a1, 0x4
    ctx->r5 = ADD32(ctx->r5, 0X4);
L_801EBB54:
    // 0x801EBB54: lw          $t5, -0x7E90($t5)
    ctx->r13 = MEM_W(ctx->r13, -0X7E90);
    // 0x801EBB58: bnel        $a3, $t5, L_801EBB88
    if (ctx->r7 != ctx->r13) {
        // 0x801EBB5C: or          $a3, $zero, $zero
        ctx->r7 = 0 | 0;
            goto L_801EBB88;
    }
    goto skip_0;
    // 0x801EBB5C: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    skip_0:
    // 0x801EBB60: lw          $t7, 0xC($t3)
    ctx->r15 = MEM_W(ctx->r11, 0XC);
    // 0x801EBB64: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    // 0x801EBB68: lw          $a2, 0x4($t3)
    ctx->r6 = MEM_W(ctx->r11, 0X4);
    // 0x801EBB6C: lw          $a3, 0x8($t3)
    ctx->r7 = MEM_W(ctx->r11, 0X8);
    // 0x801EBB70: jal         0x80096960
    // 0x801EBB74: sw          $t7, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r15;
    func_80096960(rdram, ctx);
        goto after_3;
    // 0x801EBB74: sw          $t7, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r15;
    after_3:
    // 0x801EBB78: lui         $t3, 0x800E
    ctx->r11 = S32(0X800E << 16);
    // 0x801EBB7C: b           L_801EBB98
    // 0x801EBB80: addiu       $t3, $t3, -0x5650
    ctx->r11 = ADD32(ctx->r11, -0X5650);
        goto L_801EBB98;
    // 0x801EBB80: addiu       $t3, $t3, -0x5650
    ctx->r11 = ADD32(ctx->r11, -0X5650);
    // 0x801EBB84: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
L_801EBB88:
    // 0x801EBB88: jal         0x80096960
    // 0x801EBB8C: sw          $zero, 0x10($sp)
    MEM_W(0X10, ctx->r29) = 0;
    func_80096960(rdram, ctx);
        goto after_4;
    // 0x801EBB8C: sw          $zero, 0x10($sp)
    MEM_W(0X10, ctx->r29) = 0;
    after_4:
    // 0x801EBB90: lui         $t3, 0x800E
    ctx->r11 = S32(0X800E << 16);
    // 0x801EBB94: addiu       $t3, $t3, -0x5650
    ctx->r11 = ADD32(ctx->r11, -0X5650);
L_801EBB98:
    // 0x801EBB98: lui         $a1, 0x800D
    ctx->r5 = S32(0X800D << 16);
    // 0x801EBB9C: lw          $a1, 0x48DC($a1)
    ctx->r5 = MEM_W(ctx->r5, 0X48DC);
    // 0x801EBBA0: addiu       $a3, $zero, 0x1718
    ctx->r7 = ADD32(0, 0X1718);
    // 0x801EBBA4: addiu       $t2, $zero, 0xE
    ctx->r10 = ADD32(0, 0XE);
    // 0x801EBBA8: multu       $a1, $a3
    result = U64(U32(ctx->r5)) * U64(U32(ctx->r7)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x801EBBAC: sll         $t8, $a1, 2
    ctx->r24 = S32(ctx->r5 << 2);
    // 0x801EBBB0: addu        $t9, $t3, $t8
    ctx->r25 = ADD32(ctx->r11, ctx->r24);
    // 0x801EBBB4: lw          $a2, 0x0($t9)
    ctx->r6 = MEM_W(ctx->r25, 0X0);
    // 0x801EBBB8: lui         $t1, 0x801D
    ctx->r9 = S32(0X801D << 16);
    // 0x801EBBBC: addiu       $t1, $t1, -0x4D68
    ctx->r9 = ADD32(ctx->r9, -0X4D68);
    // 0x801EBBC0: lui         $v0, 0x8019
    ctx->r2 = S32(0X8019 << 16);
    // 0x801EBBC4: addiu       $v0, $v0, 0x2690
    ctx->r2 = ADD32(ctx->r2, 0X2690);
    // 0x801EBBC8: lui         $t0, 0x800E
    ctx->r8 = S32(0X800E << 16);
    // 0x801EBBCC: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x801EBBD0: mflo        $t6
    ctx->r14 = lo;
    // 0x801EBBD4: addu        $v1, $v0, $t6
    ctx->r3 = ADD32(ctx->r2, ctx->r14);
    // 0x801EBBD8: sw          $a2, 0xB68($v1)
    MEM_W(0XB68, ctx->r3) = ctx->r6;
    // 0x801EBBDC: multu       $a2, $t2
    result = U64(U32(ctx->r6)) * U64(U32(ctx->r10)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x801EBBE0: lui         $t8, 0x800D
    ctx->r24 = S32(0X800D << 16);
    // 0x801EBBE4: mflo        $t4
    ctx->r12 = lo;
    // 0x801EBBE8: addu        $a0, $t1, $t4
    ctx->r4 = ADD32(ctx->r9, ctx->r12);
    // 0x801EBBEC: lb          $t5, 0xB($a0)
    ctx->r13 = MEM_B(ctx->r4, 0XB);
    // 0x801EBBF0: lb          $t7, 0xC($a0)
    ctx->r15 = MEM_B(ctx->r4, 0XC);
    // 0x801EBBF4: lb          $t6, 0xD($a0)
    ctx->r14 = MEM_B(ctx->r4, 0XD);
    // 0x801EBBF8: sw          $t5, 0xB6C($v1)
    MEM_W(0XB6C, ctx->r3) = ctx->r13;
    // 0x801EBBFC: sw          $t7, 0xB70($v1)
    MEM_W(0XB70, ctx->r3) = ctx->r15;
    // 0x801EBC00: sw          $t6, 0xB74($v1)
    MEM_W(0XB74, ctx->r3) = ctx->r14;
    // 0x801EBC04: lw          $t0, -0x7E90($t0)
    ctx->r8 = MEM_W(ctx->r8, -0X7E90);
    // 0x801EBC08: lui         $a0, 0x800D
    ctx->r4 = S32(0X800D << 16);
    // 0x801EBC0C: bne         $t0, $at, L_801EBC2C
    if (ctx->r8 != ctx->r1) {
        // 0x801EBC10: nop
    
            goto L_801EBC2C;
    }
    // 0x801EBC10: nop

    // 0x801EBC14: lw          $t8, 0x48E0($t8)
    ctx->r24 = MEM_W(ctx->r24, 0X48E0);
    // 0x801EBC18: multu       $t8, $a3
    result = U64(U32(ctx->r24)) * U64(U32(ctx->r7)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x801EBC1C: mflo        $t9
    ctx->r25 = lo;
    // 0x801EBC20: addu        $v1, $v0, $t9
    ctx->r3 = ADD32(ctx->r2, ctx->r25);
    // 0x801EBC24: b           L_801EBC4C
    // 0x801EBC28: sw          $a2, 0xB68($v1)
    MEM_W(0XB68, ctx->r3) = ctx->r6;
        goto L_801EBC4C;
    // 0x801EBC28: sw          $a2, 0xB68($v1)
    MEM_W(0XB68, ctx->r3) = ctx->r6;
L_801EBC2C:
    // 0x801EBC2C: lw          $a0, 0x48E0($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X48E0);
    // 0x801EBC30: multu       $a0, $a3
    result = U64(U32(ctx->r4)) * U64(U32(ctx->r7)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x801EBC34: sll         $t5, $a0, 2
    ctx->r13 = S32(ctx->r4 << 2);
    // 0x801EBC38: addu        $t7, $t3, $t5
    ctx->r15 = ADD32(ctx->r11, ctx->r13);
    // 0x801EBC3C: lw          $t6, 0x0($t7)
    ctx->r14 = MEM_W(ctx->r15, 0X0);
    // 0x801EBC40: mflo        $t4
    ctx->r12 = lo;
    // 0x801EBC44: addu        $v1, $v0, $t4
    ctx->r3 = ADD32(ctx->r2, ctx->r12);
    // 0x801EBC48: sw          $t6, 0xB68($v1)
    MEM_W(0XB68, ctx->r3) = ctx->r14;
L_801EBC4C:
    // 0x801EBC4C: lw          $t8, 0xB68($v1)
    ctx->r24 = MEM_W(ctx->r3, 0XB68);
    // 0x801EBC50: lw          $t6, 0x8($t3)
    ctx->r14 = MEM_W(ctx->r11, 0X8);
    // 0x801EBC54: or          $a3, $t0, $zero
    ctx->r7 = ctx->r8 | 0;
    // 0x801EBC58: multu       $t8, $t2
    result = U64(U32(ctx->r24)) * U64(U32(ctx->r10)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x801EBC5C: lui         $t8, 0x800E
    ctx->r24 = S32(0X800E << 16);
    // 0x801EBC60: addiu       $t8, $t8, -0x4A74
    ctx->r24 = ADD32(ctx->r24, -0X4A74);
    // 0x801EBC64: mflo        $t9
    ctx->r25 = lo;
    // 0x801EBC68: addu        $a0, $t1, $t9
    ctx->r4 = ADD32(ctx->r9, ctx->r25);
    // 0x801EBC6C: lb          $t4, 0xB($a0)
    ctx->r12 = MEM_B(ctx->r4, 0XB);
    // 0x801EBC70: multu       $t6, $t2
    result = U64(U32(ctx->r14)) * U64(U32(ctx->r10)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x801EBC74: lb          $t5, 0xC($a0)
    ctx->r13 = MEM_B(ctx->r4, 0XC);
    // 0x801EBC78: lb          $t7, 0xD($a0)
    ctx->r15 = MEM_B(ctx->r4, 0XD);
    // 0x801EBC7C: sw          $t4, 0xB6C($v1)
    MEM_W(0XB6C, ctx->r3) = ctx->r12;
    // 0x801EBC80: sw          $t5, 0xB70($v1)
    MEM_W(0XB70, ctx->r3) = ctx->r13;
    // 0x801EBC84: sw          $t7, 0xB74($v1)
    MEM_W(0XB74, ctx->r3) = ctx->r15;
    // 0x801EBC88: sw          $t6, 0x3998($v0)
    MEM_W(0X3998, ctx->r2) = ctx->r14;
    // 0x801EBC8C: lw          $t6, 0xC($t3)
    ctx->r14 = MEM_W(ctx->r11, 0XC);
    // 0x801EBC90: lui         $a0, 0x806
    ctx->r4 = S32(0X806 << 16);
    // 0x801EBC94: mflo        $t9
    ctx->r25 = lo;
    // 0x801EBC98: addu        $a1, $t1, $t9
    ctx->r5 = ADD32(ctx->r9, ctx->r25);
    // 0x801EBC9C: lb          $t4, 0xB($a1)
    ctx->r12 = MEM_B(ctx->r5, 0XB);
    // 0x801EBCA0: multu       $t6, $t2
    result = U64(U32(ctx->r14)) * U64(U32(ctx->r10)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x801EBCA4: lb          $t5, 0xC($a1)
    ctx->r13 = MEM_B(ctx->r5, 0XC);
    // 0x801EBCA8: lb          $t7, 0xD($a1)
    ctx->r15 = MEM_B(ctx->r5, 0XD);
    // 0x801EBCAC: sw          $t4, 0x399C($v0)
    MEM_W(0X399C, ctx->r2) = ctx->r12;
    // 0x801EBCB0: sw          $t5, 0x39A0($v0)
    MEM_W(0X39A0, ctx->r2) = ctx->r13;
    // 0x801EBCB4: sw          $t7, 0x39A4($v0)
    MEM_W(0X39A4, ctx->r2) = ctx->r15;
    // 0x801EBCB8: sw          $t6, 0x50B0($v0)
    MEM_W(0X50B0, ctx->r2) = ctx->r14;
    // 0x801EBCBC: mflo        $t9
    ctx->r25 = lo;
    // 0x801EBCC0: addu        $a2, $t1, $t9
    ctx->r6 = ADD32(ctx->r9, ctx->r25);
    // 0x801EBCC4: lb          $t4, 0xB($a2)
    ctx->r12 = MEM_B(ctx->r6, 0XB);
    // 0x801EBCC8: lb          $t5, 0xC($a2)
    ctx->r13 = MEM_B(ctx->r6, 0XC);
    // 0x801EBCCC: lb          $t7, 0xD($a2)
    ctx->r15 = MEM_B(ctx->r6, 0XD);
    // 0x801EBCD0: sw          $t4, 0x50B4($v0)
    MEM_W(0X50B4, ctx->r2) = ctx->r12;
    // 0x801EBCD4: sw          $t5, 0x50B8($v0)
    MEM_W(0X50B8, ctx->r2) = ctx->r13;
    // 0x801EBCD8: bgez        $t0, L_801EBCE4
    if (SIGNED(ctx->r8) >= 0) {
        // 0x801EBCDC: sw          $t7, 0x50BC($v0)
        MEM_W(0X50BC, ctx->r2) = ctx->r15;
            goto L_801EBCE4;
    }
    // 0x801EBCDC: sw          $t7, 0x50BC($v0)
    MEM_W(0X50BC, ctx->r2) = ctx->r15;
    // 0x801EBCE0: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
L_801EBCE4:
    // 0x801EBCE4: slti        $at, $a3, 0x9
    ctx->r1 = SIGNED(ctx->r7) < 0X9 ? 1 : 0;
    // 0x801EBCE8: bnel        $at, $zero, L_801EBCF8
    if (ctx->r1 != 0) {
        // 0x801EBCEC: sll         $t6, $a3, 2
        ctx->r14 = S32(ctx->r7 << 2);
            goto L_801EBCF8;
    }
    goto skip_1;
    // 0x801EBCEC: sll         $t6, $a3, 2
    ctx->r14 = S32(ctx->r7 << 2);
    skip_1:
    // 0x801EBCF0: addiu       $a3, $zero, 0x8
    ctx->r7 = ADD32(0, 0X8);
    // 0x801EBCF4: sll         $t6, $a3, 2
    ctx->r14 = S32(ctx->r7 << 2);
L_801EBCF8:
    // 0x801EBCF8: addu        $v0, $t6, $t8
    ctx->r2 = ADD32(ctx->r14, ctx->r24);
    // 0x801EBCFC: lh          $a1, 0x0($v0)
    ctx->r5 = MEM_H(ctx->r2, 0X0);
    // 0x801EBD00: jal         0x8009684C
    // 0x801EBD04: lh          $a2, 0x2($v0)
    ctx->r6 = MEM_H(ctx->r2, 0X2);
    func_8009684C(rdram, ctx);
        goto after_5;
    // 0x801EBD04: lh          $a2, 0x2($v0)
    ctx->r6 = MEM_H(ctx->r2, 0X2);
    after_5:
    // 0x801EBD08: lui         $a1, 0x800E
    ctx->r5 = S32(0X800E << 16);
    // 0x801EBD0C: lw          $a1, -0x7E90($a1)
    ctx->r5 = MEM_W(ctx->r5, -0X7E90);
    // 0x801EBD10: jal         0x800C21F4
    // 0x801EBD14: addiu       $a0, $zero, 0x2
    ctx->r4 = ADD32(0, 0X2);
    func_800C21F4(rdram, ctx);
        goto after_6;
    // 0x801EBD14: addiu       $a0, $zero, 0x2
    ctx->r4 = ADD32(0, 0X2);
    after_6:
    // 0x801EBD18: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    // 0x801EBD1C: addiu       $sp, $sp, 0x28
    ctx->r29 = ADD32(ctx->r29, 0X28);
    // 0x801EBD20: jr          $ra
    // 0x801EBD24: nop

    return;
    // 0x801EBD24: nop

;}
RECOMP_FUNC void func_801EBD28(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801EBD28: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x801EBD2C: addiu       $v0, $v0, -0x54DC
    ctx->r2 = ADD32(ctx->r2, -0X54DC);
    // 0x801EBD30: lw          $t6, 0x0($v0)
    ctx->r14 = MEM_W(ctx->r2, 0X0);
    // 0x801EBD34: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EBD38: addiu       $v1, $zero, 0xA
    ctx->r3 = ADD32(0, 0XA);
    // 0x801EBD3C: sw          $t6, -0x19CC($at)
    MEM_W(-0X19CC, ctx->r1) = ctx->r14;
    // 0x801EBD40: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EBD44: sw          $zero, -0x19D0($at)
    MEM_W(-0X19D0, ctx->r1) = 0;
    // 0x801EBD48: sw          $v1, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r3;
    // 0x801EBD4C: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EBD50: addiu       $t7, $zero, 0x4
    ctx->r15 = ADD32(0, 0X4);
    // 0x801EBD54: sw          $t7, -0x19C8($at)
    MEM_W(-0X19C8, ctx->r1) = ctx->r15;
    // 0x801EBD58: addiu       $t1, $zero, 0x1
    ctx->r9 = ADD32(0, 0X1);
    // 0x801EBD5C: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EBD60: sw          $t1, -0x19C4($at)
    MEM_W(-0X19C4, ctx->r1) = ctx->r9;
    // 0x801EBD64: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EBD68: sw          $zero, -0x19C0($at)
    MEM_W(-0X19C0, ctx->r1) = 0;
    // 0x801EBD6C: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EBD70: sw          $zero, -0x19BC($at)
    MEM_W(-0X19BC, ctx->r1) = 0;
    // 0x801EBD74: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x801EBD78: sw          $zero, -0x54E4($at)
    MEM_W(-0X54E4, ctx->r1) = 0;
    // 0x801EBD7C: lui         $t8, 0x801D
    ctx->r24 = S32(0X801D << 16);
    // 0x801EBD80: lh          $t8, -0x19F4($t8)
    ctx->r24 = MEM_H(ctx->r24, -0X19F4);
    // 0x801EBD84: addiu       $t2, $zero, 0x3
    ctx->r10 = ADD32(0, 0X3);
    // 0x801EBD88: lui         $at, 0x800D
    ctx->r1 = S32(0X800D << 16);
    // 0x801EBD8C: sw          $t2, 0x461C($at)
    MEM_W(0X461C, ctx->r1) = ctx->r10;
    // 0x801EBD90: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x801EBD94: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EBD98: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x801EBD9C: bne         $t1, $t8, L_801EBDC0
    if (ctx->r9 != ctx->r24) {
        // 0x801EBDA0: sw          $zero, -0x19E0($at)
        MEM_W(-0X19E0, ctx->r1) = 0;
            goto L_801EBDC0;
    }
    // 0x801EBDA0: sw          $zero, -0x19E0($at)
    MEM_W(-0X19E0, ctx->r1) = 0;
    // 0x801EBDA4: lui         $a2, 0x800E
    ctx->r6 = S32(0X800E << 16);
    // 0x801EBDA8: addiu       $a2, $a2, -0x54D8
    ctx->r6 = ADD32(ctx->r6, -0X54D8);
    // 0x801EBDAC: sw          $t1, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r9;
    // 0x801EBDB0: lui         $at, 0x801A
    ctx->r1 = S32(0X801A << 16);
    // 0x801EBDB4: sw          $t1, -0x7D10($at)
    MEM_W(-0X7D10, ctx->r1) = ctx->r9;
    // 0x801EBDB8: b           L_801EBDD8
    // 0x801EBDBC: addiu       $t0, $zero, 0x2
    ctx->r8 = ADD32(0, 0X2);
        goto L_801EBDD8;
    // 0x801EBDBC: addiu       $t0, $zero, 0x2
    ctx->r8 = ADD32(0, 0X2);
L_801EBDC0:
    // 0x801EBDC0: lui         $a2, 0x800E
    ctx->r6 = S32(0X800E << 16);
    // 0x801EBDC4: addiu       $a2, $a2, -0x54D8
    ctx->r6 = ADD32(ctx->r6, -0X54D8);
    // 0x801EBDC8: addiu       $t0, $zero, 0x2
    ctx->r8 = ADD32(0, 0X2);
    // 0x801EBDCC: sw          $t0, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r8;
    // 0x801EBDD0: lui         $at, 0x801A
    ctx->r1 = S32(0X801A << 16);
    // 0x801EBDD4: sw          $t0, -0x7D10($at)
    MEM_W(-0X7D10, ctx->r1) = ctx->r8;
L_801EBDD8:
    // 0x801EBDD8: lui         $at, 0x800D
    ctx->r1 = S32(0X800D << 16);
    // 0x801EBDDC: sw          $v1, 0x49B0($at)
    MEM_W(0X49B0, ctx->r1) = ctx->r3;
    // 0x801EBDE0: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x801EBDE4: addiu       $t9, $zero, 0x5
    ctx->r25 = ADD32(0, 0X5);
    // 0x801EBDE8: sw          $t9, -0x7E8C($at)
    MEM_W(-0X7E8C, ctx->r1) = ctx->r25;
    // 0x801EBDEC: lui         $t7, 0x800E
    ctx->r15 = S32(0X800E << 16);
    // 0x801EBDF0: lh          $t7, -0x5654($t7)
    ctx->r15 = MEM_H(ctx->r15, -0X5654);
    // 0x801EBDF4: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EBDF8: sw          $t2, -0x18D8($at)
    MEM_W(-0X18D8, ctx->r1) = ctx->r10;
    // 0x801EBDFC: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x801EBE00: addiu       $t6, $zero, 0x9
    ctx->r14 = ADD32(0, 0X9);
    // 0x801EBE04: beq         $t7, $zero, L_801EBE2C
    if (ctx->r15 == 0) {
        // 0x801EBE08: sw          $t6, -0x7E90($at)
        MEM_W(-0X7E90, ctx->r1) = ctx->r14;
            goto L_801EBE2C;
    }
    // 0x801EBE08: sw          $t6, -0x7E90($at)
    MEM_W(-0X7E90, ctx->r1) = ctx->r14;
    // 0x801EBE0C: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x801EBE10: lui         $a1, 0x800E
    ctx->r5 = S32(0X800E << 16);
    // 0x801EBE14: addiu       $a1, $a1, -0x5640
    ctx->r5 = ADD32(ctx->r5, -0X5640);
    // 0x801EBE18: addiu       $v0, $v0, -0x5638
    ctx->r2 = ADD32(ctx->r2, -0X5638);
    // 0x801EBE1C: sw          $zero, 0x0($a1)
    MEM_W(0X0, ctx->r5) = 0;
    // 0x801EBE20: sw          $t2, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r10;
    // 0x801EBE24: sw          $zero, 0x4($v0)
    MEM_W(0X4, ctx->r2) = 0;
    // 0x801EBE28: sw          $zero, 0x0($v0)
    MEM_W(0X0, ctx->r2) = 0;
L_801EBE2C:
    // 0x801EBE2C: lui         $t9, 0x800D
    ctx->r25 = S32(0X800D << 16);
    // 0x801EBE30: lw          $t9, 0x48DC($t9)
    ctx->r25 = MEM_W(ctx->r25, 0X48DC);
    // 0x801EBE34: addiu       $t3, $zero, 0x1718
    ctx->r11 = ADD32(0, 0X1718);
    // 0x801EBE38: lui         $a1, 0x800E
    ctx->r5 = S32(0X800E << 16);
    // 0x801EBE3C: multu       $t9, $t3
    result = U64(U32(ctx->r25)) * U64(U32(ctx->r11)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x801EBE40: addiu       $a1, $a1, -0x5640
    ctx->r5 = ADD32(ctx->r5, -0X5640);
    // 0x801EBE44: lw          $t7, 0x0($a1)
    ctx->r15 = MEM_W(ctx->r5, 0X0);
    // 0x801EBE48: lui         $t4, 0x8022
    ctx->r12 = S32(0X8022 << 16);
    // 0x801EBE4C: addiu       $t4, $t4, 0x6EF0
    ctx->r12 = ADD32(ctx->r12, 0X6EF0);
    // 0x801EBE50: sll         $t8, $t7, 2
    ctx->r24 = S32(ctx->r15 << 2);
    // 0x801EBE54: addu        $t9, $t4, $t8
    ctx->r25 = ADD32(ctx->r12, ctx->r24);
    // 0x801EBE58: lw          $a0, 0x0($t9)
    ctx->r4 = MEM_W(ctx->r25, 0X0);
    // 0x801EBE5C: addiu       $ra, $zero, 0xE
    ctx->r31 = ADD32(0, 0XE);
    // 0x801EBE60: lui         $a3, 0x8019
    ctx->r7 = S32(0X8019 << 16);
    // 0x801EBE64: mflo        $t6
    ctx->r14 = lo;
    // 0x801EBE68: addiu       $a3, $a3, 0x2690
    ctx->r7 = ADD32(ctx->r7, 0X2690);
    // 0x801EBE6C: lui         $t5, 0x800E
    ctx->r13 = S32(0X800E << 16);
    // 0x801EBE70: multu       $a0, $ra
    result = U64(U32(ctx->r4)) * U64(U32(ctx->r31)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x801EBE74: addu        $v0, $a3, $t6
    ctx->r2 = ADD32(ctx->r7, ctx->r14);
    // 0x801EBE78: addiu       $t5, $t5, -0x56B0
    ctx->r13 = ADD32(ctx->r13, -0X56B0);
    // 0x801EBE7C: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EBE80: sw          $a0, 0xB68($v0)
    MEM_W(0XB68, ctx->r2) = ctx->r4;
    // 0x801EBE84: mflo        $t6
    ctx->r14 = lo;
    // 0x801EBE88: addu        $v1, $t5, $t6
    ctx->r3 = ADD32(ctx->r13, ctx->r14);
    // 0x801EBE8C: lw          $t6, 0x0($a2)
    ctx->r14 = MEM_W(ctx->r6, 0X0);
    // 0x801EBE90: lb          $t7, 0xB($v1)
    ctx->r15 = MEM_B(ctx->r3, 0XB);
    // 0x801EBE94: lb          $t8, 0xC($v1)
    ctx->r24 = MEM_B(ctx->r3, 0XC);
    // 0x801EBE98: lb          $t9, 0xD($v1)
    ctx->r25 = MEM_B(ctx->r3, 0XD);
    // 0x801EBE9C: sw          $t7, 0xB6C($v0)
    MEM_W(0XB6C, ctx->r2) = ctx->r15;
    // 0x801EBEA0: sw          $t8, 0xB70($v0)
    MEM_W(0XB70, ctx->r2) = ctx->r24;
    // 0x801EBEA4: bne         $t0, $t6, L_801EBEF8
    if (ctx->r8 != ctx->r14) {
        // 0x801EBEA8: sw          $t9, 0xB74($v0)
        MEM_W(0XB74, ctx->r2) = ctx->r25;
            goto L_801EBEF8;
    }
    // 0x801EBEA8: sw          $t9, 0xB74($v0)
    MEM_W(0XB74, ctx->r2) = ctx->r25;
    // 0x801EBEAC: lui         $t7, 0x800D
    ctx->r15 = S32(0X800D << 16);
    // 0x801EBEB0: lw          $t7, 0x48E0($t7)
    ctx->r15 = MEM_W(ctx->r15, 0X48E0);
    // 0x801EBEB4: lw          $t9, 0x4($a1)
    ctx->r25 = MEM_W(ctx->r5, 0X4);
    // 0x801EBEB8: multu       $t7, $t3
    result = U64(U32(ctx->r15)) * U64(U32(ctx->r11)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x801EBEBC: sll         $t6, $t9, 2
    ctx->r14 = S32(ctx->r25 << 2);
    // 0x801EBEC0: addu        $t7, $t4, $t6
    ctx->r15 = ADD32(ctx->r12, ctx->r14);
    // 0x801EBEC4: lw          $a0, 0x0($t7)
    ctx->r4 = MEM_W(ctx->r15, 0X0);
    // 0x801EBEC8: mflo        $t8
    ctx->r24 = lo;
    // 0x801EBECC: addu        $v0, $a3, $t8
    ctx->r2 = ADD32(ctx->r7, ctx->r24);
    // 0x801EBED0: sw          $a0, 0xB68($v0)
    MEM_W(0XB68, ctx->r2) = ctx->r4;
    // 0x801EBED4: multu       $a0, $ra
    result = U64(U32(ctx->r4)) * U64(U32(ctx->r31)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x801EBED8: mflo        $t8
    ctx->r24 = lo;
    // 0x801EBEDC: addu        $v1, $t5, $t8
    ctx->r3 = ADD32(ctx->r13, ctx->r24);
    // 0x801EBEE0: lb          $t9, 0xB($v1)
    ctx->r25 = MEM_B(ctx->r3, 0XB);
    // 0x801EBEE4: lb          $t6, 0xC($v1)
    ctx->r14 = MEM_B(ctx->r3, 0XC);
    // 0x801EBEE8: lb          $t7, 0xD($v1)
    ctx->r15 = MEM_B(ctx->r3, 0XD);
    // 0x801EBEEC: sw          $t9, 0xB6C($v0)
    MEM_W(0XB6C, ctx->r2) = ctx->r25;
    // 0x801EBEF0: sw          $t6, 0xB70($v0)
    MEM_W(0XB70, ctx->r2) = ctx->r14;
    // 0x801EBEF4: sw          $t7, 0xB74($v0)
    MEM_W(0XB74, ctx->r2) = ctx->r15;
L_801EBEF8:
    // 0x801EBEF8: sw          $t0, -0x19B8($at)
    MEM_W(-0X19B8, ctx->r1) = ctx->r8;
    // 0x801EBEFC: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EBF00: sw          $t0, -0x19B4($at)
    MEM_W(-0X19B4, ctx->r1) = ctx->r8;
    // 0x801EBF04: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EBF08: sw          $t2, -0x19B0($at)
    MEM_W(-0X19B0, ctx->r1) = ctx->r10;
    // 0x801EBF0C: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x801EBF10: sh          $zero, -0x549C($at)
    MEM_H(-0X549C, ctx->r1) = 0;
    // 0x801EBF14: or          $a0, $t2, $zero
    ctx->r4 = ctx->r10 | 0;
    // 0x801EBF18: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x801EBF1C: or          $a2, $t1, $zero
    ctx->r6 = ctx->r9 | 0;
    // 0x801EBF20: or          $a3, $t0, $zero
    ctx->r7 = ctx->r8 | 0;
    // 0x801EBF24: jal         0x80096960
    // 0x801EBF28: sw          $t2, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r10;
    func_80096960(rdram, ctx);
        goto after_0;
    // 0x801EBF28: sw          $t2, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r10;
    after_0:
    // 0x801EBF2C: addiu       $a0, $zero, 0x2
    ctx->r4 = ADD32(0, 0X2);
    // 0x801EBF30: addiu       $a1, $zero, 0x4
    ctx->r5 = ADD32(0, 0X4);
    // 0x801EBF34: jal         0x801E6FB0
    // 0x801EBF38: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    FadeTransition_SetProps(rdram, ctx);
        goto after_1;
    // 0x801EBF38: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    after_1:
    // 0x801EBF3C: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    // 0x801EBF40: jal         0x801E6A4C
    // 0x801EBF44: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_801E6A4C(rdram, ctx);
        goto after_2;
    // 0x801EBF44: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_2:
    // 0x801EBF48: lui         $v1, 0x8022
    ctx->r3 = S32(0X8022 << 16);
    // 0x801EBF4C: addiu       $v1, $v1, 0x7C80
    ctx->r3 = ADD32(ctx->r3, 0X7C80);
    // 0x801EBF50: addiu       $t0, $zero, 0x2
    ctx->r8 = ADD32(0, 0X2);
    // 0x801EBF54: sw          $t0, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r8;
    // 0x801EBF58: sw          $t0, 0x10C($v1)
    MEM_W(0X10C, ctx->r3) = ctx->r8;
    // 0x801EBF5C: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x801EBF60: lw          $v0, -0x19F8($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X19F8);
    // 0x801EBF64: addiu       $t1, $zero, 0x1
    ctx->r9 = ADD32(0, 0X1);
    // 0x801EBF68: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    // 0x801EBF6C: beq         $v0, $zero, L_801EBFAC
    if (ctx->r2 == 0) {
        // 0x801EBF70: nop
    
            goto L_801EBFAC;
    }
    // 0x801EBF70: nop

    // 0x801EBF74: beq         $v0, $t1, L_801EBFCC
    if (ctx->r2 == ctx->r9) {
        // 0x801EBF78: addiu       $a0, $zero, 0x1
        ctx->r4 = ADD32(0, 0X1);
            goto L_801EBFCC;
    }
    // 0x801EBF78: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    // 0x801EBF7C: addiu       $at, $zero, 0x4
    ctx->r1 = ADD32(0, 0X4);
    // 0x801EBF80: beq         $v0, $at, L_801EBF9C
    if (ctx->r2 == ctx->r1) {
        // 0x801EBF84: addiu       $a0, $zero, 0x1
        ctx->r4 = ADD32(0, 0X1);
            goto L_801EBF9C;
    }
    // 0x801EBF84: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    // 0x801EBF88: addiu       $at, $zero, 0xB
    ctx->r1 = ADD32(0, 0XB);
    // 0x801EBF8C: beq         $v0, $at, L_801EBFBC
    if (ctx->r2 == ctx->r1) {
        // 0x801EBF90: addiu       $a0, $zero, 0x1
        ctx->r4 = ADD32(0, 0X1);
            goto L_801EBFBC;
    }
    // 0x801EBF90: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    // 0x801EBF94: b           L_801EBFD8
    // 0x801EBF98: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
        goto L_801EBFD8;
    // 0x801EBF98: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
L_801EBF9C:
    // 0x801EBF9C: jal         0x800C21F4
    // 0x801EBFA0: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C21F4(rdram, ctx);
        goto after_3;
    // 0x801EBFA0: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_3:
    // 0x801EBFA4: b           L_801EBFD8
    // 0x801EBFA8: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
        goto L_801EBFD8;
    // 0x801EBFA8: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
L_801EBFAC:
    // 0x801EBFAC: jal         0x800C21F4
    // 0x801EBFB0: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    func_800C21F4(rdram, ctx);
        goto after_4;
    // 0x801EBFB0: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    after_4:
    // 0x801EBFB4: b           L_801EBFD8
    // 0x801EBFB8: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
        goto L_801EBFD8;
    // 0x801EBFB8: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
L_801EBFBC:
    // 0x801EBFBC: jal         0x800C21F4
    // 0x801EBFC0: addiu       $a1, $zero, 0x3
    ctx->r5 = ADD32(0, 0X3);
    func_800C21F4(rdram, ctx);
        goto after_5;
    // 0x801EBFC0: addiu       $a1, $zero, 0x3
    ctx->r5 = ADD32(0, 0X3);
    after_5:
    // 0x801EBFC4: b           L_801EBFD8
    // 0x801EBFC8: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
        goto L_801EBFD8;
    // 0x801EBFC8: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
L_801EBFCC:
    // 0x801EBFCC: jal         0x800C21F4
    // 0x801EBFD0: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    func_800C21F4(rdram, ctx);
        goto after_6;
    // 0x801EBFD0: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    after_6:
    // 0x801EBFD4: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
L_801EBFD8:
    // 0x801EBFD8: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x801EBFDC: jr          $ra
    // 0x801EBFE0: nop

    return;
    // 0x801EBFE0: nop

;}
RECOMP_FUNC void func_801EBFE4(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801EBFE4: lui         $v1, 0x800E
    ctx->r3 = S32(0X800E << 16);
    // 0x801EBFE8: addiu       $v1, $v1, -0x54DC
    ctx->r3 = ADD32(ctx->r3, -0X54DC);
    // 0x801EBFEC: lw          $t6, 0x0($v1)
    ctx->r14 = MEM_W(ctx->r3, 0X0);
    // 0x801EBFF0: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EBFF4: addiu       $t7, $zero, 0x14
    ctx->r15 = ADD32(0, 0X14);
    // 0x801EBFF8: sw          $t6, -0x19CC($at)
    MEM_W(-0X19CC, ctx->r1) = ctx->r14;
    // 0x801EBFFC: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EC000: sw          $zero, -0x19D0($at)
    MEM_W(-0X19D0, ctx->r1) = 0;
    // 0x801EC004: sw          $t7, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r15;
    // 0x801EC008: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EC00C: addiu       $t8, $zero, 0x5
    ctx->r24 = ADD32(0, 0X5);
    // 0x801EC010: sw          $t8, -0x19C8($at)
    MEM_W(-0X19C8, ctx->r1) = ctx->r24;
    // 0x801EC014: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
    // 0x801EC018: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EC01C: sw          $v0, -0x19C4($at)
    MEM_W(-0X19C4, ctx->r1) = ctx->r2;
    // 0x801EC020: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EC024: sw          $zero, -0x19C0($at)
    MEM_W(-0X19C0, ctx->r1) = 0;
    // 0x801EC028: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EC02C: sw          $zero, -0x19BC($at)
    MEM_W(-0X19BC, ctx->r1) = 0;
    // 0x801EC030: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x801EC034: sw          $zero, -0x54E4($at)
    MEM_W(-0X54E4, ctx->r1) = 0;
    // 0x801EC038: lui         $at, 0x800D
    ctx->r1 = S32(0X800D << 16);
    // 0x801EC03C: addiu       $t9, $zero, 0x2
    ctx->r25 = ADD32(0, 0X2);
    // 0x801EC040: sw          $t9, 0x461C($at)
    MEM_W(0X461C, ctx->r1) = ctx->r25;
    // 0x801EC044: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x801EC048: sw          $v0, -0x54D8($at)
    MEM_W(-0X54D8, ctx->r1) = ctx->r2;
    // 0x801EC04C: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x801EC050: sw          $v0, -0x7E90($at)
    MEM_W(-0X7E90, ctx->r1) = ctx->r2;
    // 0x801EC054: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EC058: sw          $v0, -0x19B8($at)
    MEM_W(-0X19B8, ctx->r1) = ctx->r2;
    // 0x801EC05C: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EC060: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x801EC064: sw          $v0, -0x19B4($at)
    MEM_W(-0X19B4, ctx->r1) = ctx->r2;
    // 0x801EC068: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x801EC06C: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EC070: sw          $zero, -0x19B0($at)
    MEM_W(-0X19B0, ctx->r1) = 0;
    // 0x801EC074: addiu       $a0, $zero, 0x2
    ctx->r4 = ADD32(0, 0X2);
    // 0x801EC078: addiu       $a1, $zero, 0x4
    ctx->r5 = ADD32(0, 0X4);
    // 0x801EC07C: jal         0x801E6FB0
    // 0x801EC080: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    FadeTransition_SetProps(rdram, ctx);
        goto after_0;
    // 0x801EC080: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    after_0:
    // 0x801EC084: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    // 0x801EC088: jal         0x801E6A4C
    // 0x801EC08C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_801E6A4C(rdram, ctx);
        goto after_1;
    // 0x801EC08C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_1:
    // 0x801EC090: lui         $t0, 0x800E
    ctx->r8 = S32(0X800E << 16);
    // 0x801EC094: lh          $t0, -0x5654($t0)
    ctx->r8 = MEM_H(ctx->r8, -0X5654);
    // 0x801EC098: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
    // 0x801EC09C: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801EC0A0: beq         $t0, $zero, L_801EC0B0
    if (ctx->r8 == 0) {
        // 0x801EC0A4: sw          $v0, 0x7C80($at)
        MEM_W(0X7C80, ctx->r1) = ctx->r2;
            goto L_801EC0B0;
    }
    // 0x801EC0A4: sw          $v0, 0x7C80($at)
    MEM_W(0X7C80, ctx->r1) = ctx->r2;
    // 0x801EC0A8: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x801EC0AC: sw          $zero, -0x5630($at)
    MEM_W(-0X5630, ctx->r1) = 0;
L_801EC0B0:
    // 0x801EC0B0: addiu       $a0, $zero, 0xA
    ctx->r4 = ADD32(0, 0XA);
    // 0x801EC0B4: jal         0x800C21F4
    // 0x801EC0B8: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C21F4(rdram, ctx);
        goto after_2;
    // 0x801EC0B8: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_2:
    // 0x801EC0BC: jal         0x800C6AD0
    // 0x801EC0C0: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    osViBlack_recomp(rdram, ctx);
        goto after_3;
    // 0x801EC0C0: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    after_3:
    // 0x801EC0C4: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x801EC0C8: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x801EC0CC: jr          $ra
    // 0x801EC0D0: nop

    return;
    // 0x801EC0D0: nop

;}
RECOMP_FUNC void func_801EC0D4(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801EC0D4: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x801EC0D8: addiu       $v0, $v0, -0x54DC
    ctx->r2 = ADD32(ctx->r2, -0X54DC);
    // 0x801EC0DC: lw          $t6, 0x0($v0)
    ctx->r14 = MEM_W(ctx->r2, 0X0);
    // 0x801EC0E0: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EC0E4: addiu       $t7, $zero, 0x34
    ctx->r15 = ADD32(0, 0X34);
    // 0x801EC0E8: sw          $t6, -0x19CC($at)
    MEM_W(-0X19CC, ctx->r1) = ctx->r14;
    // 0x801EC0EC: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EC0F0: sw          $zero, -0x19D0($at)
    MEM_W(-0X19D0, ctx->r1) = 0;
    // 0x801EC0F4: sw          $t7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r15;
    // 0x801EC0F8: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EC0FC: addiu       $t8, $zero, 0x9
    ctx->r24 = ADD32(0, 0X9);
    // 0x801EC100: sw          $t8, -0x19C8($at)
    MEM_W(-0X19C8, ctx->r1) = ctx->r24;
    // 0x801EC104: addiu       $v1, $zero, 0x1
    ctx->r3 = ADD32(0, 0X1);
    // 0x801EC108: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EC10C: sw          $v1, -0x19C4($at)
    MEM_W(-0X19C4, ctx->r1) = ctx->r3;
    // 0x801EC110: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EC114: sw          $zero, -0x19C0($at)
    MEM_W(-0X19C0, ctx->r1) = 0;
    // 0x801EC118: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EC11C: sw          $zero, -0x19BC($at)
    MEM_W(-0X19BC, ctx->r1) = 0;
    // 0x801EC120: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x801EC124: sw          $zero, -0x54E4($at)
    MEM_W(-0X54E4, ctx->r1) = 0;
    // 0x801EC128: lui         $at, 0x800D
    ctx->r1 = S32(0X800D << 16);
    // 0x801EC12C: addiu       $t9, $zero, 0x2
    ctx->r25 = ADD32(0, 0X2);
    // 0x801EC130: sw          $t9, 0x461C($at)
    MEM_W(0X461C, ctx->r1) = ctx->r25;
    // 0x801EC134: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x801EC138: sw          $v1, -0x54D8($at)
    MEM_W(-0X54D8, ctx->r1) = ctx->r3;
    // 0x801EC13C: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EC140: addiu       $sp, $sp, -0x38
    ctx->r29 = ADD32(ctx->r29, -0X38);
    // 0x801EC144: sw          $v1, -0x19B8($at)
    MEM_W(-0X19B8, ctx->r1) = ctx->r3;
    // 0x801EC148: lui         $t0, 0x801D
    ctx->r8 = S32(0X801D << 16);
    // 0x801EC14C: lh          $t0, -0x190C($t0)
    ctx->r8 = MEM_H(ctx->r8, -0X190C);
    // 0x801EC150: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EC154: sw          $v1, -0x19B4($at)
    MEM_W(-0X19B4, ctx->r1) = ctx->r3;
    // 0x801EC158: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EC15C: addiu       $v0, $zero, 0x3
    ctx->r2 = ADD32(0, 0X3);
    // 0x801EC160: addiu       $a3, $zero, 0x2
    ctx->r7 = ADD32(0, 0X2);
    // 0x801EC164: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x801EC168: sw          $zero, -0x19B0($at)
    MEM_W(-0X19B0, ctx->r1) = 0;
    // 0x801EC16C: sw          $a3, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r7;
    // 0x801EC170: sw          $v0, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r2;
    // 0x801EC174: sw          $zero, 0x24($sp)
    MEM_W(0X24, ctx->r29) = 0;
    // 0x801EC178: beq         $t0, $zero, L_801EC1B0
    if (ctx->r8 == 0) {
        // 0x801EC17C: sw          $v1, 0x28($sp)
        MEM_W(0X28, ctx->r29) = ctx->r3;
            goto L_801EC1B0;
    }
    // 0x801EC17C: sw          $v1, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r3;
    // 0x801EC180: lui         $t1, 0x800D
    ctx->r9 = S32(0X800D << 16);
    // 0x801EC184: lw          $t1, 0x48DC($t1)
    ctx->r9 = MEM_W(ctx->r9, 0X48DC);
    // 0x801EC188: lui         $t3, 0x800E
    ctx->r11 = S32(0X800E << 16);
    // 0x801EC18C: addiu       $t5, $sp, 0x24
    ctx->r13 = ADD32(ctx->r29, 0X24);
    // 0x801EC190: sll         $t2, $t1, 2
    ctx->r10 = S32(ctx->r9 << 2);
    // 0x801EC194: addu        $t3, $t3, $t2
    ctx->r11 = ADD32(ctx->r11, ctx->r10);
    // 0x801EC198: lw          $t3, -0x5650($t3)
    ctx->r11 = MEM_W(ctx->r11, -0X5650);
    // 0x801EC19C: sll         $t4, $t3, 2
    ctx->r12 = S32(ctx->r11 << 2);
    // 0x801EC1A0: addu        $v0, $t4, $t5
    ctx->r2 = ADD32(ctx->r12, ctx->r13);
    // 0x801EC1A4: lw          $t6, 0x0($v0)
    ctx->r14 = MEM_W(ctx->r2, 0X0);
    // 0x801EC1A8: addiu       $t7, $t6, 0x4
    ctx->r15 = ADD32(ctx->r14, 0X4);
    // 0x801EC1AC: sw          $t7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r15;
L_801EC1B0:
    // 0x801EC1B0: lw          $v0, 0x30($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X30);
    // 0x801EC1B4: lw          $a1, 0x24($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X24);
    // 0x801EC1B8: lw          $a2, 0x28($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X28);
    // 0x801EC1BC: lw          $a3, 0x2C($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X2C);
    // 0x801EC1C0: addiu       $a0, $zero, 0x2
    ctx->r4 = ADD32(0, 0X2);
    // 0x801EC1C4: jal         0x80096960
    // 0x801EC1C8: sw          $v0, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r2;
    func_80096960(rdram, ctx);
        goto after_0;
    // 0x801EC1C8: sw          $v0, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r2;
    after_0:
    // 0x801EC1CC: addiu       $a0, $zero, 0x4
    ctx->r4 = ADD32(0, 0X4);
    // 0x801EC1D0: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x801EC1D4: jal         0x801E6FB0
    // 0x801EC1D8: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    FadeTransition_SetProps(rdram, ctx);
        goto after_1;
    // 0x801EC1D8: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    after_1:
    // 0x801EC1DC: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    // 0x801EC1E0: jal         0x801E6A4C
    // 0x801EC1E4: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_801E6A4C(rdram, ctx);
        goto after_2;
    // 0x801EC1E4: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_2:
    // 0x801EC1E8: addiu       $v1, $zero, 0x1
    ctx->r3 = ADD32(0, 0X1);
    // 0x801EC1EC: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801EC1F0: sw          $v1, 0x7C80($at)
    MEM_W(0X7C80, ctx->r1) = ctx->r3;
    // 0x801EC1F4: jal         0x800C6AD0
    // 0x801EC1F8: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    osViBlack_recomp(rdram, ctx);
        goto after_3;
    // 0x801EC1F8: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    after_3:
    // 0x801EC1FC: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    // 0x801EC200: addiu       $sp, $sp, 0x38
    ctx->r29 = ADD32(ctx->r29, 0X38);
    // 0x801EC204: jr          $ra
    // 0x801EC208: nop

    return;
    // 0x801EC208: nop

;}
RECOMP_FUNC void func_801EC20C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801EC20C: lui         $a0, 0x800E
    ctx->r4 = S32(0X800E << 16);
    // 0x801EC210: addiu       $a0, $a0, -0x54DC
    ctx->r4 = ADD32(ctx->r4, -0X54DC);
    // 0x801EC214: lw          $t6, 0x0($a0)
    ctx->r14 = MEM_W(ctx->r4, 0X0);
    // 0x801EC218: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x801EC21C: addiu       $v1, $v1, -0x19CC
    ctx->r3 = ADD32(ctx->r3, -0X19CC);
    // 0x801EC220: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EC224: sw          $t6, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r14;
    // 0x801EC228: sw          $zero, -0x19D0($at)
    MEM_W(-0X19D0, ctx->r1) = 0;
    // 0x801EC22C: addiu       $t7, $zero, 0x32
    ctx->r15 = ADD32(0, 0X32);
    // 0x801EC230: sw          $t7, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r15;
    // 0x801EC234: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EC238: addiu       $t8, $zero, 0x3
    ctx->r24 = ADD32(0, 0X3);
    // 0x801EC23C: sw          $t8, -0x19C8($at)
    MEM_W(-0X19C8, ctx->r1) = ctx->r24;
    // 0x801EC240: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
    // 0x801EC244: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EC248: sw          $v0, -0x19C4($at)
    MEM_W(-0X19C4, ctx->r1) = ctx->r2;
    // 0x801EC24C: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EC250: sw          $zero, -0x19C0($at)
    MEM_W(-0X19C0, ctx->r1) = 0;
    // 0x801EC254: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EC258: sw          $zero, -0x19BC($at)
    MEM_W(-0X19BC, ctx->r1) = 0;
    // 0x801EC25C: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x801EC260: sw          $zero, -0x54E4($at)
    MEM_W(-0X54E4, ctx->r1) = 0;
    // 0x801EC264: lui         $at, 0x800D
    ctx->r1 = S32(0X800D << 16);
    // 0x801EC268: addiu       $t9, $zero, 0x2
    ctx->r25 = ADD32(0, 0X2);
    // 0x801EC26C: sw          $t9, 0x461C($at)
    MEM_W(0X461C, ctx->r1) = ctx->r25;
    // 0x801EC270: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x801EC274: sw          $v0, -0x54D8($at)
    MEM_W(-0X54D8, ctx->r1) = ctx->r2;
    // 0x801EC278: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EC27C: sw          $v0, -0x19B8($at)
    MEM_W(-0X19B8, ctx->r1) = ctx->r2;
    // 0x801EC280: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EC284: sw          $v0, -0x19B4($at)
    MEM_W(-0X19B4, ctx->r1) = ctx->r2;
    // 0x801EC288: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EC28C: sw          $zero, -0x19B0($at)
    MEM_W(-0X19B0, ctx->r1) = 0;
    // 0x801EC290: lw          $t0, 0x0($v1)
    ctx->r8 = MEM_W(ctx->r3, 0X0);
    // 0x801EC294: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x801EC298: addiu       $at, $zero, 0x64
    ctx->r1 = ADD32(0, 0X64);
    // 0x801EC29C: beq         $t0, $at, L_801EC2E0
    if (ctx->r8 == ctx->r1) {
        // 0x801EC2A0: sw          $ra, 0x1C($sp)
        MEM_W(0X1C, ctx->r29) = ctx->r31;
            goto L_801EC2E0;
    }
    // 0x801EC2A0: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x801EC2A4: addiu       $t1, $zero, 0x3
    ctx->r9 = ADD32(0, 0X3);
    // 0x801EC2A8: sw          $t1, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r9;
    // 0x801EC2AC: addiu       $a0, $zero, 0x2
    ctx->r4 = ADD32(0, 0X2);
    // 0x801EC2B0: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x801EC2B4: or          $a2, $v0, $zero
    ctx->r6 = ctx->r2 | 0;
    // 0x801EC2B8: jal         0x80096960
    // 0x801EC2BC: addiu       $a3, $zero, 0x2
    ctx->r7 = ADD32(0, 0X2);
    func_80096960(rdram, ctx);
        goto after_0;
    // 0x801EC2BC: addiu       $a3, $zero, 0x2
    ctx->r7 = ADD32(0, 0X2);
    after_0:
    // 0x801EC2C0: addiu       $a0, $zero, 0x4
    ctx->r4 = ADD32(0, 0X4);
    // 0x801EC2C4: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x801EC2C8: jal         0x801E6FB0
    // 0x801EC2CC: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    FadeTransition_SetProps(rdram, ctx);
        goto after_1;
    // 0x801EC2CC: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    after_1:
    // 0x801EC2D0: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    // 0x801EC2D4: jal         0x801E6A4C
    // 0x801EC2D8: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_801E6A4C(rdram, ctx);
        goto after_2;
    // 0x801EC2D8: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_2:
    // 0x801EC2DC: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
L_801EC2E0:
    // 0x801EC2E0: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801EC2E4: sw          $v0, 0x7C80($at)
    MEM_W(0X7C80, ctx->r1) = ctx->r2;
    // 0x801EC2E8: addiu       $a0, $zero, 0x3
    ctx->r4 = ADD32(0, 0X3);
    // 0x801EC2EC: jal         0x800C21F4
    // 0x801EC2F0: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C21F4(rdram, ctx);
        goto after_3;
    // 0x801EC2F0: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_3:
    // 0x801EC2F4: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    // 0x801EC2F8: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x801EC2FC: jr          $ra
    // 0x801EC300: nop

    return;
    // 0x801EC300: nop

;}
RECOMP_FUNC void func_801EC304(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801EC304: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x801EC308: addiu       $v0, $v0, -0x54DC
    ctx->r2 = ADD32(ctx->r2, -0X54DC);
    // 0x801EC30C: lw          $t6, 0x0($v0)
    ctx->r14 = MEM_W(ctx->r2, 0X0);
    // 0x801EC310: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EC314: addiu       $t7, $zero, 0x3C
    ctx->r15 = ADD32(0, 0X3C);
    // 0x801EC318: sw          $t6, -0x19CC($at)
    MEM_W(-0X19CC, ctx->r1) = ctx->r14;
    // 0x801EC31C: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EC320: sw          $zero, -0x19D0($at)
    MEM_W(-0X19D0, ctx->r1) = 0;
    // 0x801EC324: sw          $t7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r15;
    // 0x801EC328: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EC32C: addiu       $t8, $zero, 0x7
    ctx->r24 = ADD32(0, 0X7);
    // 0x801EC330: sw          $t8, -0x19C8($at)
    MEM_W(-0X19C8, ctx->r1) = ctx->r24;
    // 0x801EC334: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EC338: addiu       $t9, $zero, 0x1
    ctx->r25 = ADD32(0, 0X1);
    // 0x801EC33C: sw          $t9, -0x19C4($at)
    MEM_W(-0X19C4, ctx->r1) = ctx->r25;
    // 0x801EC340: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EC344: sw          $zero, -0x19C0($at)
    MEM_W(-0X19C0, ctx->r1) = 0;
    // 0x801EC348: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EC34C: sw          $zero, -0x19BC($at)
    MEM_W(-0X19BC, ctx->r1) = 0;
    // 0x801EC350: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x801EC354: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x801EC358: sw          $zero, -0x54E4($at)
    MEM_W(-0X54E4, ctx->r1) = 0;
    // 0x801EC35C: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x801EC360: lui         $at, 0x800D
    ctx->r1 = S32(0X800D << 16);
    // 0x801EC364: addiu       $t0, $zero, 0x2
    ctx->r8 = ADD32(0, 0X2);
    // 0x801EC368: sw          $t0, 0x461C($at)
    MEM_W(0X461C, ctx->r1) = ctx->r8;
    // 0x801EC36C: addiu       $a0, $zero, 0x2
    ctx->r4 = ADD32(0, 0X2);
    // 0x801EC370: addiu       $a1, $zero, 0x4
    ctx->r5 = ADD32(0, 0X4);
    // 0x801EC374: jal         0x801E6FB0
    // 0x801EC378: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    FadeTransition_SetProps(rdram, ctx);
        goto after_0;
    // 0x801EC378: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    after_0:
    // 0x801EC37C: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    // 0x801EC380: jal         0x801E6A4C
    // 0x801EC384: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_801E6A4C(rdram, ctx);
        goto after_1;
    // 0x801EC384: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_1:
    // 0x801EC388: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x801EC38C: sb          $zero, 0x5134($at)
    MEM_B(0X5134, ctx->r1) = 0;
    // 0x801EC390: addiu       $a0, $zero, 0x9
    ctx->r4 = ADD32(0, 0X9);
    // 0x801EC394: jal         0x800C21F4
    // 0x801EC398: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C21F4(rdram, ctx);
        goto after_2;
    // 0x801EC398: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_2:
    // 0x801EC39C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x801EC3A0: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x801EC3A4: jr          $ra
    // 0x801EC3A8: nop

    return;
    // 0x801EC3A8: nop

;}
RECOMP_FUNC void func_801EC3AC(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801EC3AC: lui         $t2, 0x800E
    ctx->r10 = S32(0X800E << 16);
    // 0x801EC3B0: addiu       $t2, $t2, -0x54DC
    ctx->r10 = ADD32(ctx->r10, -0X54DC);
    // 0x801EC3B4: lw          $t6, 0x0($t2)
    ctx->r14 = MEM_W(ctx->r10, 0X0);
    // 0x801EC3B8: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EC3BC: addiu       $t7, $zero, 0x3E
    ctx->r15 = ADD32(0, 0X3E);
    // 0x801EC3C0: sw          $t6, -0x19CC($at)
    MEM_W(-0X19CC, ctx->r1) = ctx->r14;
    // 0x801EC3C4: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EC3C8: sw          $zero, -0x19D0($at)
    MEM_W(-0X19D0, ctx->r1) = 0;
    // 0x801EC3CC: sw          $t7, 0x0($t2)
    MEM_W(0X0, ctx->r10) = ctx->r15;
    // 0x801EC3D0: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EC3D4: addiu       $t8, $zero, 0xA
    ctx->r24 = ADD32(0, 0XA);
    // 0x801EC3D8: sw          $t8, -0x19C8($at)
    MEM_W(-0X19C8, ctx->r1) = ctx->r24;
    // 0x801EC3DC: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    // 0x801EC3E0: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EC3E4: sw          $a2, -0x19C4($at)
    MEM_W(-0X19C4, ctx->r1) = ctx->r6;
    // 0x801EC3E8: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EC3EC: sw          $zero, -0x19C0($at)
    MEM_W(-0X19C0, ctx->r1) = 0;
    // 0x801EC3F0: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EC3F4: sw          $zero, -0x19BC($at)
    MEM_W(-0X19BC, ctx->r1) = 0;
    // 0x801EC3F8: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x801EC3FC: sw          $zero, -0x54E4($at)
    MEM_W(-0X54E4, ctx->r1) = 0;
    // 0x801EC400: addiu       $t3, $zero, 0x3
    ctx->r11 = ADD32(0, 0X3);
    // 0x801EC404: lui         $at, 0x800D
    ctx->r1 = S32(0X800D << 16);
    // 0x801EC408: sw          $t3, 0x461C($at)
    MEM_W(0X461C, ctx->r1) = ctx->r11;
    // 0x801EC40C: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x801EC410: sw          $a2, -0x54D8($at)
    MEM_W(-0X54D8, ctx->r1) = ctx->r6;
    // 0x801EC414: lui         $at, 0x801A
    ctx->r1 = S32(0X801A << 16);
    // 0x801EC418: lui         $t5, 0x800D
    ctx->r13 = S32(0X800D << 16);
    // 0x801EC41C: lw          $t5, 0x48DC($t5)
    ctx->r13 = MEM_W(ctx->r13, 0X48DC);
    // 0x801EC420: sw          $a2, -0x7D10($at)
    MEM_W(-0X7D10, ctx->r1) = ctx->r6;
    // 0x801EC424: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x801EC428: addiu       $t9, $zero, 0x9
    ctx->r25 = ADD32(0, 0X9);
    // 0x801EC42C: sw          $t9, -0x7E90($at)
    MEM_W(-0X7E90, ctx->r1) = ctx->r25;
    // 0x801EC430: addiu       $a3, $zero, 0x2
    ctx->r7 = ADD32(0, 0X2);
    // 0x801EC434: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EC438: sll         $t6, $t5, 2
    ctx->r14 = S32(ctx->r13 << 2);
    // 0x801EC43C: sw          $a3, -0x19B8($at)
    MEM_W(-0X19B8, ctx->r1) = ctx->r7;
    // 0x801EC440: subu        $t6, $t6, $t5
    ctx->r14 = SUB32(ctx->r14, ctx->r13);
    // 0x801EC444: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EC448: sll         $t6, $t6, 3
    ctx->r14 = S32(ctx->r14 << 3);
    // 0x801EC44C: sw          $a3, -0x19B4($at)
    MEM_W(-0X19B4, ctx->r1) = ctx->r7;
    // 0x801EC450: subu        $t6, $t6, $t5
    ctx->r14 = SUB32(ctx->r14, ctx->r13);
    // 0x801EC454: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EC458: sll         $t6, $t6, 3
    ctx->r14 = S32(ctx->r14 << 3);
    // 0x801EC45C: sw          $t3, -0x19B0($at)
    MEM_W(-0X19B0, ctx->r1) = ctx->r11;
    // 0x801EC460: addu        $t6, $t6, $t5
    ctx->r14 = ADD32(ctx->r14, ctx->r13);
    // 0x801EC464: sll         $t6, $t6, 2
    ctx->r14 = S32(ctx->r14 << 2);
    // 0x801EC468: lui         $t0, 0x800E
    ctx->r8 = S32(0X800E << 16);
    // 0x801EC46C: lui         $t7, 0x8019
    ctx->r15 = S32(0X8019 << 16);
    // 0x801EC470: subu        $t6, $t6, $t5
    ctx->r14 = SUB32(ctx->r14, ctx->r13);
    // 0x801EC474: addiu       $t0, $t0, -0x56B0
    ctx->r8 = ADD32(ctx->r8, -0X56B0);
    // 0x801EC478: lui         $t1, 0x801D
    ctx->r9 = S32(0X801D << 16);
    // 0x801EC47C: sll         $t6, $t6, 3
    ctx->r14 = S32(ctx->r14 << 3);
    // 0x801EC480: addiu       $t7, $t7, 0x2690
    ctx->r15 = ADD32(ctx->r15, 0X2690);
    // 0x801EC484: addiu       $t1, $t1, -0x190C
    ctx->r9 = ADD32(ctx->r9, -0X190C);
    // 0x801EC488: addu        $v0, $t6, $t7
    ctx->r2 = ADD32(ctx->r14, ctx->r15);
    // 0x801EC48C: sh          $zero, 0x2($t1)
    MEM_H(0X2, ctx->r9) = 0;
    // 0x801EC490: lb          $t8, 0xB($t0)
    ctx->r24 = MEM_B(ctx->r8, 0XB);
    // 0x801EC494: lb          $t9, 0xC($t0)
    ctx->r25 = MEM_B(ctx->r8, 0XC);
    // 0x801EC498: lb          $t5, 0xD($t0)
    ctx->r13 = MEM_B(ctx->r8, 0XD);
    // 0x801EC49C: lh          $t6, 0x2($t1)
    ctx->r14 = MEM_H(ctx->r9, 0X2);
    // 0x801EC4A0: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x801EC4A4: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x801EC4A8: sw          $zero, 0xB68($v0)
    MEM_W(0XB68, ctx->r2) = 0;
    // 0x801EC4AC: sw          $t3, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r11;
    // 0x801EC4B0: or          $a0, $a3, $zero
    ctx->r4 = ctx->r7 | 0;
    // 0x801EC4B4: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x801EC4B8: sw          $t8, 0xB6C($v0)
    MEM_W(0XB6C, ctx->r2) = ctx->r24;
    // 0x801EC4BC: sw          $t9, 0xB70($v0)
    MEM_W(0XB70, ctx->r2) = ctx->r25;
    // 0x801EC4C0: sw          $t5, 0xB74($v0)
    MEM_W(0XB74, ctx->r2) = ctx->r13;
    // 0x801EC4C4: jal         0x80096960
    // 0x801EC4C8: sh          $t6, 0x0($t1)
    MEM_H(0X0, ctx->r9) = ctx->r14;
    func_80096960(rdram, ctx);
        goto after_0;
    // 0x801EC4C8: sh          $t6, 0x0($t1)
    MEM_H(0X0, ctx->r9) = ctx->r14;
    after_0:
    // 0x801EC4CC: addiu       $a0, $zero, 0x2
    ctx->r4 = ADD32(0, 0X2);
    // 0x801EC4D0: addiu       $a1, $zero, 0x4
    ctx->r5 = ADD32(0, 0X4);
    // 0x801EC4D4: jal         0x801E6FB0
    // 0x801EC4D8: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    FadeTransition_SetProps(rdram, ctx);
        goto after_1;
    // 0x801EC4D8: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    after_1:
    // 0x801EC4DC: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    // 0x801EC4E0: jal         0x801E6A4C
    // 0x801EC4E4: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_801E6A4C(rdram, ctx);
        goto after_2;
    // 0x801EC4E4: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_2:
    // 0x801EC4E8: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    // 0x801EC4EC: addiu       $t7, $zero, 0x2
    ctx->r15 = ADD32(0, 0X2);
    // 0x801EC4F0: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801EC4F4: sw          $t7, 0x7C80($at)
    MEM_W(0X7C80, ctx->r1) = ctx->r15;
    // 0x801EC4F8: jr          $ra
    // 0x801EC4FC: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    return;
    // 0x801EC4FC: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
;}
RECOMP_FUNC void func_801EC500(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801EC500: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x801EC504: addiu       $v0, $v0, -0x54DC
    ctx->r2 = ADD32(ctx->r2, -0X54DC);
    // 0x801EC508: lw          $t6, 0x0($v0)
    ctx->r14 = MEM_W(ctx->r2, 0X0);
    // 0x801EC50C: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EC510: addiu       $t7, $zero, 0x42
    ctx->r15 = ADD32(0, 0X42);
    // 0x801EC514: sw          $t6, -0x19CC($at)
    MEM_W(-0X19CC, ctx->r1) = ctx->r14;
    // 0x801EC518: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EC51C: sw          $zero, -0x19D0($at)
    MEM_W(-0X19D0, ctx->r1) = 0;
    // 0x801EC520: sw          $t7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r15;
    // 0x801EC524: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EC528: addiu       $t8, $zero, 0xC
    ctx->r24 = ADD32(0, 0XC);
    // 0x801EC52C: sw          $t8, -0x19C8($at)
    MEM_W(-0X19C8, ctx->r1) = ctx->r24;
    // 0x801EC530: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    // 0x801EC534: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EC538: sw          $a2, -0x19C4($at)
    MEM_W(-0X19C4, ctx->r1) = ctx->r6;
    // 0x801EC53C: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EC540: sw          $zero, -0x19C0($at)
    MEM_W(-0X19C0, ctx->r1) = 0;
    // 0x801EC544: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EC548: sw          $zero, -0x19BC($at)
    MEM_W(-0X19BC, ctx->r1) = 0;
    // 0x801EC54C: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x801EC550: sw          $zero, -0x54E4($at)
    MEM_W(-0X54E4, ctx->r1) = 0;
    // 0x801EC554: lui         $at, 0x800D
    ctx->r1 = S32(0X800D << 16);
    // 0x801EC558: addiu       $t9, $zero, 0x2
    ctx->r25 = ADD32(0, 0X2);
    // 0x801EC55C: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x801EC560: sw          $t9, 0x461C($at)
    MEM_W(0X461C, ctx->r1) = ctx->r25;
    // 0x801EC564: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x801EC568: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x801EC56C: addiu       $t0, $zero, 0x3
    ctx->r8 = ADD32(0, 0X3);
    // 0x801EC570: sw          $a2, -0x54D8($at)
    MEM_W(-0X54D8, ctx->r1) = ctx->r6;
    // 0x801EC574: sw          $t0, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r8;
    // 0x801EC578: addiu       $a0, $zero, 0x2
    ctx->r4 = ADD32(0, 0X2);
    // 0x801EC57C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x801EC580: jal         0x80096960
    // 0x801EC584: addiu       $a3, $zero, 0x2
    ctx->r7 = ADD32(0, 0X2);
    func_80096960(rdram, ctx);
        goto after_0;
    // 0x801EC584: addiu       $a3, $zero, 0x2
    ctx->r7 = ADD32(0, 0X2);
    after_0:
    // 0x801EC588: addiu       $a0, $zero, 0x2
    ctx->r4 = ADD32(0, 0X2);
    // 0x801EC58C: addiu       $a1, $zero, 0x4
    ctx->r5 = ADD32(0, 0X4);
    // 0x801EC590: jal         0x801E6FB0
    // 0x801EC594: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    FadeTransition_SetProps(rdram, ctx);
        goto after_1;
    // 0x801EC594: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    after_1:
    // 0x801EC598: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    // 0x801EC59C: jal         0x801E6A4C
    // 0x801EC5A0: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_801E6A4C(rdram, ctx);
        goto after_2;
    // 0x801EC5A0: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_2:
    // 0x801EC5A4: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    // 0x801EC5A8: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x801EC5AC: jr          $ra
    // 0x801EC5B0: nop

    return;
    // 0x801EC5B0: nop

;}
RECOMP_FUNC void func_801EC5B4(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801EC5B4: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x801EC5B8: addiu       $v0, $v0, -0x54DC
    ctx->r2 = ADD32(ctx->r2, -0X54DC);
    // 0x801EC5BC: lw          $t6, 0x0($v0)
    ctx->r14 = MEM_W(ctx->r2, 0X0);
    // 0x801EC5C0: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EC5C4: addiu       $t7, $zero, 0x44
    ctx->r15 = ADD32(0, 0X44);
    // 0x801EC5C8: sw          $t6, -0x19CC($at)
    MEM_W(-0X19CC, ctx->r1) = ctx->r14;
    // 0x801EC5CC: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EC5D0: sw          $zero, -0x19D0($at)
    MEM_W(-0X19D0, ctx->r1) = 0;
    // 0x801EC5D4: sw          $t7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r15;
    // 0x801EC5D8: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EC5DC: addiu       $t8, $zero, 0xE
    ctx->r24 = ADD32(0, 0XE);
    // 0x801EC5E0: sw          $t8, -0x19C8($at)
    MEM_W(-0X19C8, ctx->r1) = ctx->r24;
    // 0x801EC5E4: addiu       $v1, $zero, 0x1
    ctx->r3 = ADD32(0, 0X1);
    // 0x801EC5E8: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EC5EC: sw          $v1, -0x19C4($at)
    MEM_W(-0X19C4, ctx->r1) = ctx->r3;
    // 0x801EC5F0: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EC5F4: sw          $zero, -0x19C0($at)
    MEM_W(-0X19C0, ctx->r1) = 0;
    // 0x801EC5F8: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EC5FC: sw          $zero, -0x19BC($at)
    MEM_W(-0X19BC, ctx->r1) = 0;
    // 0x801EC600: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x801EC604: sw          $zero, -0x54E4($at)
    MEM_W(-0X54E4, ctx->r1) = 0;
    // 0x801EC608: lui         $at, 0x800D
    ctx->r1 = S32(0X800D << 16);
    // 0x801EC60C: addiu       $t9, $zero, 0x2
    ctx->r25 = ADD32(0, 0X2);
    // 0x801EC610: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x801EC614: sw          $t9, 0x461C($at)
    MEM_W(0X461C, ctx->r1) = ctx->r25;
    // 0x801EC618: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x801EC61C: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x801EC620: sw          $v1, -0x54D8($at)
    MEM_W(-0X54D8, ctx->r1) = ctx->r3;
    // 0x801EC624: addiu       $a0, $zero, 0x2
    ctx->r4 = ADD32(0, 0X2);
    // 0x801EC628: addiu       $a1, $zero, 0x4
    ctx->r5 = ADD32(0, 0X4);
    // 0x801EC62C: jal         0x801E6FB0
    // 0x801EC630: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    FadeTransition_SetProps(rdram, ctx);
        goto after_0;
    // 0x801EC630: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    after_0:
    // 0x801EC634: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    // 0x801EC638: jal         0x801E6A4C
    // 0x801EC63C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_801E6A4C(rdram, ctx);
        goto after_1;
    // 0x801EC63C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_1:
    // 0x801EC640: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x801EC644: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x801EC648: jr          $ra
    // 0x801EC64C: nop

    return;
    // 0x801EC64C: nop

;}
RECOMP_FUNC void func_801EC650(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801EC650: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x801EC654: addiu       $v0, $v0, -0x54DC
    ctx->r2 = ADD32(ctx->r2, -0X54DC);
    // 0x801EC658: lw          $t6, 0x0($v0)
    ctx->r14 = MEM_W(ctx->r2, 0X0);
    // 0x801EC65C: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EC660: addiu       $t7, $zero, 0x48
    ctx->r15 = ADD32(0, 0X48);
    // 0x801EC664: sw          $t6, -0x19CC($at)
    MEM_W(-0X19CC, ctx->r1) = ctx->r14;
    // 0x801EC668: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EC66C: sw          $zero, -0x19D0($at)
    MEM_W(-0X19D0, ctx->r1) = 0;
    // 0x801EC670: sw          $t7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r15;
    // 0x801EC674: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EC678: addiu       $t8, $zero, 0x14
    ctx->r24 = ADD32(0, 0X14);
    // 0x801EC67C: sw          $t8, -0x19C8($at)
    MEM_W(-0X19C8, ctx->r1) = ctx->r24;
    // 0x801EC680: addiu       $v1, $zero, 0x1
    ctx->r3 = ADD32(0, 0X1);
    // 0x801EC684: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EC688: sw          $v1, -0x19C4($at)
    MEM_W(-0X19C4, ctx->r1) = ctx->r3;
    // 0x801EC68C: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EC690: sw          $zero, -0x19C0($at)
    MEM_W(-0X19C0, ctx->r1) = 0;
    // 0x801EC694: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EC698: sw          $zero, -0x19BC($at)
    MEM_W(-0X19BC, ctx->r1) = 0;
    // 0x801EC69C: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x801EC6A0: sw          $zero, -0x54E4($at)
    MEM_W(-0X54E4, ctx->r1) = 0;
    // 0x801EC6A4: lui         $at, 0x800D
    ctx->r1 = S32(0X800D << 16);
    // 0x801EC6A8: addiu       $t9, $zero, 0x2
    ctx->r25 = ADD32(0, 0X2);
    // 0x801EC6AC: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x801EC6B0: sw          $t9, 0x461C($at)
    MEM_W(0X461C, ctx->r1) = ctx->r25;
    // 0x801EC6B4: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x801EC6B8: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x801EC6BC: sw          $v1, -0x54D8($at)
    MEM_W(-0X54D8, ctx->r1) = ctx->r3;
    // 0x801EC6C0: addiu       $a0, $zero, 0x2
    ctx->r4 = ADD32(0, 0X2);
    // 0x801EC6C4: addiu       $a1, $zero, 0x4
    ctx->r5 = ADD32(0, 0X4);
    // 0x801EC6C8: jal         0x801E6FB0
    // 0x801EC6CC: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    FadeTransition_SetProps(rdram, ctx);
        goto after_0;
    // 0x801EC6CC: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    after_0:
    // 0x801EC6D0: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    // 0x801EC6D4: jal         0x801E6A4C
    // 0x801EC6D8: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_801E6A4C(rdram, ctx);
        goto after_1;
    // 0x801EC6D8: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_1:
    // 0x801EC6DC: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x801EC6E0: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x801EC6E4: jr          $ra
    // 0x801EC6E8: nop

    return;
    // 0x801EC6E8: nop

;}
RECOMP_FUNC void func_801EC6EC(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801EC6EC: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x801EC6F0: addiu       $v0, $v0, -0x54DC
    ctx->r2 = ADD32(ctx->r2, -0X54DC);
    // 0x801EC6F4: lw          $t6, 0x0($v0)
    ctx->r14 = MEM_W(ctx->r2, 0X0);
    // 0x801EC6F8: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EC6FC: addiu       $t7, $zero, 0x46
    ctx->r15 = ADD32(0, 0X46);
    // 0x801EC700: sw          $t6, -0x19CC($at)
    MEM_W(-0X19CC, ctx->r1) = ctx->r14;
    // 0x801EC704: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EC708: sw          $zero, -0x19D0($at)
    MEM_W(-0X19D0, ctx->r1) = 0;
    // 0x801EC70C: sw          $t7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r15;
    // 0x801EC710: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EC714: addiu       $t8, $zero, 0x10
    ctx->r24 = ADD32(0, 0X10);
    // 0x801EC718: sw          $t8, -0x19C8($at)
    MEM_W(-0X19C8, ctx->r1) = ctx->r24;
    // 0x801EC71C: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EC720: addiu       $t9, $zero, 0x1
    ctx->r25 = ADD32(0, 0X1);
    // 0x801EC724: sw          $t9, -0x19C4($at)
    MEM_W(-0X19C4, ctx->r1) = ctx->r25;
    // 0x801EC728: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EC72C: sw          $zero, -0x19C0($at)
    MEM_W(-0X19C0, ctx->r1) = 0;
    // 0x801EC730: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EC734: sw          $zero, -0x19BC($at)
    MEM_W(-0X19BC, ctx->r1) = 0;
    // 0x801EC738: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x801EC73C: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x801EC740: sw          $zero, -0x54E4($at)
    MEM_W(-0X54E4, ctx->r1) = 0;
    // 0x801EC744: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x801EC748: lui         $at, 0x800D
    ctx->r1 = S32(0X800D << 16);
    // 0x801EC74C: addiu       $t0, $zero, 0x2
    ctx->r8 = ADD32(0, 0X2);
    // 0x801EC750: sw          $t0, 0x461C($at)
    MEM_W(0X461C, ctx->r1) = ctx->r8;
    // 0x801EC754: addiu       $a0, $zero, 0x2
    ctx->r4 = ADD32(0, 0X2);
    // 0x801EC758: addiu       $a1, $zero, 0x4
    ctx->r5 = ADD32(0, 0X4);
    // 0x801EC75C: jal         0x801E6FB0
    // 0x801EC760: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    FadeTransition_SetProps(rdram, ctx);
        goto after_0;
    // 0x801EC760: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    after_0:
    // 0x801EC764: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    // 0x801EC768: jal         0x801E6A4C
    // 0x801EC76C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_801E6A4C(rdram, ctx);
        goto after_1;
    // 0x801EC76C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_1:
    // 0x801EC770: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x801EC774: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x801EC778: jr          $ra
    // 0x801EC77C: nop

    return;
    // 0x801EC77C: nop

;}
RECOMP_FUNC void func_801EC780(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801EC780: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x801EC784: addiu       $v0, $v0, -0x54DC
    ctx->r2 = ADD32(ctx->r2, -0X54DC);
    // 0x801EC788: lw          $t6, 0x0($v0)
    ctx->r14 = MEM_W(ctx->r2, 0X0);
    // 0x801EC78C: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EC790: addiu       $t7, $zero, 0x40
    ctx->r15 = ADD32(0, 0X40);
    // 0x801EC794: sw          $t6, -0x19CC($at)
    MEM_W(-0X19CC, ctx->r1) = ctx->r14;
    // 0x801EC798: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EC79C: sw          $zero, -0x19D0($at)
    MEM_W(-0X19D0, ctx->r1) = 0;
    // 0x801EC7A0: sw          $t7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r15;
    // 0x801EC7A4: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EC7A8: addiu       $t8, $zero, 0xB
    ctx->r24 = ADD32(0, 0XB);
    // 0x801EC7AC: sw          $t8, -0x19C8($at)
    MEM_W(-0X19C8, ctx->r1) = ctx->r24;
    // 0x801EC7B0: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EC7B4: addiu       $t9, $zero, 0x1
    ctx->r25 = ADD32(0, 0X1);
    // 0x801EC7B8: sw          $t9, -0x19C4($at)
    MEM_W(-0X19C4, ctx->r1) = ctx->r25;
    // 0x801EC7BC: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EC7C0: sw          $zero, -0x19C0($at)
    MEM_W(-0X19C0, ctx->r1) = 0;
    // 0x801EC7C4: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EC7C8: sw          $zero, -0x19BC($at)
    MEM_W(-0X19BC, ctx->r1) = 0;
    // 0x801EC7CC: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x801EC7D0: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x801EC7D4: sw          $zero, -0x54E4($at)
    MEM_W(-0X54E4, ctx->r1) = 0;
    // 0x801EC7D8: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x801EC7DC: lui         $at, 0x800D
    ctx->r1 = S32(0X800D << 16);
    // 0x801EC7E0: addiu       $t0, $zero, 0x2
    ctx->r8 = ADD32(0, 0X2);
    // 0x801EC7E4: addiu       $t1, $zero, 0x3
    ctx->r9 = ADD32(0, 0X3);
    // 0x801EC7E8: sw          $t0, 0x461C($at)
    MEM_W(0X461C, ctx->r1) = ctx->r8;
    // 0x801EC7EC: sw          $t1, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r9;
    // 0x801EC7F0: addiu       $a0, $zero, 0x2
    ctx->r4 = ADD32(0, 0X2);
    // 0x801EC7F4: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x801EC7F8: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    // 0x801EC7FC: jal         0x80096960
    // 0x801EC800: addiu       $a3, $zero, 0x2
    ctx->r7 = ADD32(0, 0X2);
    func_80096960(rdram, ctx);
        goto after_0;
    // 0x801EC800: addiu       $a3, $zero, 0x2
    ctx->r7 = ADD32(0, 0X2);
    after_0:
    // 0x801EC804: addiu       $a0, $zero, 0x2
    ctx->r4 = ADD32(0, 0X2);
    // 0x801EC808: addiu       $a1, $zero, 0x4
    ctx->r5 = ADD32(0, 0X4);
    // 0x801EC80C: jal         0x801E6FB0
    // 0x801EC810: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    FadeTransition_SetProps(rdram, ctx);
        goto after_1;
    // 0x801EC810: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    after_1:
    // 0x801EC814: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    // 0x801EC818: jal         0x801E6A4C
    // 0x801EC81C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_801E6A4C(rdram, ctx);
        goto after_2;
    // 0x801EC81C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_2:
    // 0x801EC820: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    // 0x801EC824: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x801EC828: jr          $ra
    // 0x801EC82C: nop

    return;
    // 0x801EC82C: nop

;}
RECOMP_FUNC void func_801EC830(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801EC830: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x801EC834: addiu       $v0, $v0, -0x54DC
    ctx->r2 = ADD32(ctx->r2, -0X54DC);
    // 0x801EC838: lw          $t6, 0x0($v0)
    ctx->r14 = MEM_W(ctx->r2, 0X0);
    // 0x801EC83C: lui         $a0, 0x801D
    ctx->r4 = S32(0X801D << 16);
    // 0x801EC840: addiu       $a0, $a0, -0x19CC
    ctx->r4 = ADD32(ctx->r4, -0X19CC);
    // 0x801EC844: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EC848: sw          $t6, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r14;
    // 0x801EC84C: sw          $zero, -0x19D0($at)
    MEM_W(-0X19D0, ctx->r1) = 0;
    // 0x801EC850: addiu       $t7, $zero, 0x50
    ctx->r15 = ADD32(0, 0X50);
    // 0x801EC854: sw          $t7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r15;
    // 0x801EC858: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EC85C: addiu       $t8, $zero, 0xD
    ctx->r24 = ADD32(0, 0XD);
    // 0x801EC860: sw          $t8, -0x19C8($at)
    MEM_W(-0X19C8, ctx->r1) = ctx->r24;
    // 0x801EC864: addiu       $a3, $zero, 0x1
    ctx->r7 = ADD32(0, 0X1);
    // 0x801EC868: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EC86C: sw          $a3, -0x19C4($at)
    MEM_W(-0X19C4, ctx->r1) = ctx->r7;
    // 0x801EC870: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EC874: sw          $zero, -0x19C0($at)
    MEM_W(-0X19C0, ctx->r1) = 0;
    // 0x801EC878: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EC87C: sw          $zero, -0x19BC($at)
    MEM_W(-0X19BC, ctx->r1) = 0;
    // 0x801EC880: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x801EC884: sw          $zero, -0x54E4($at)
    MEM_W(-0X54E4, ctx->r1) = 0;
    // 0x801EC888: lui         $at, 0x800D
    ctx->r1 = S32(0X800D << 16);
    // 0x801EC88C: addiu       $t9, $zero, 0x2
    ctx->r25 = ADD32(0, 0X2);
    // 0x801EC890: sw          $t9, 0x461C($at)
    MEM_W(0X461C, ctx->r1) = ctx->r25;
    // 0x801EC894: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x801EC898: sw          $a3, -0x54D8($at)
    MEM_W(-0X54D8, ctx->r1) = ctx->r7;
    // 0x801EC89C: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EC8A0: sw          $a3, -0x19B8($at)
    MEM_W(-0X19B8, ctx->r1) = ctx->r7;
    // 0x801EC8A4: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EC8A8: sw          $a3, -0x19B4($at)
    MEM_W(-0X19B4, ctx->r1) = ctx->r7;
    // 0x801EC8AC: lui         $t0, 0x801D
    ctx->r8 = S32(0X801D << 16);
    // 0x801EC8B0: lw          $t0, -0x19F8($t0)
    ctx->r8 = MEM_W(ctx->r8, -0X19F8);
    // 0x801EC8B4: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EC8B8: sw          $zero, -0x19B0($at)
    MEM_W(-0X19B0, ctx->r1) = 0;
    // 0x801EC8BC: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x801EC8C0: addiu       $at, $zero, 0x4
    ctx->r1 = ADD32(0, 0X4);
    // 0x801EC8C4: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x801EC8C8: bne         $t0, $at, L_801EC8E8
    if (ctx->r8 != ctx->r1) {
        // 0x801EC8CC: or          $v1, $zero, $zero
        ctx->r3 = 0 | 0;
            goto L_801EC8E8;
    }
    // 0x801EC8CC: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
    // 0x801EC8D0: lw          $t1, 0x0($a0)
    ctx->r9 = MEM_W(ctx->r4, 0X0);
    // 0x801EC8D4: addiu       $at, $zero, 0x43
    ctx->r1 = ADD32(0, 0X43);
    // 0x801EC8D8: bne         $t1, $at, L_801EC904
    if (ctx->r9 != ctx->r1) {
        // 0x801EC8DC: nop
    
            goto L_801EC904;
    }
    // 0x801EC8DC: nop

    // 0x801EC8E0: b           L_801EC904
    // 0x801EC8E4: or          $v1, $a3, $zero
    ctx->r3 = ctx->r7 | 0;
        goto L_801EC904;
    // 0x801EC8E4: or          $v1, $a3, $zero
    ctx->r3 = ctx->r7 | 0;
L_801EC8E8:
    // 0x801EC8E8: lw          $v0, 0x0($a0)
    ctx->r2 = MEM_W(ctx->r4, 0X0);
    // 0x801EC8EC: addiu       $at, $zero, 0x32
    ctx->r1 = ADD32(0, 0X32);
    // 0x801EC8F0: beq         $v0, $at, L_801EC904
    if (ctx->r2 == ctx->r1) {
        // 0x801EC8F4: addiu       $at, $zero, 0x39
        ctx->r1 = ADD32(0, 0X39);
            goto L_801EC904;
    }
    // 0x801EC8F4: addiu       $at, $zero, 0x39
    ctx->r1 = ADD32(0, 0X39);
    // 0x801EC8F8: beq         $v0, $at, L_801EC904
    if (ctx->r2 == ctx->r1) {
        // 0x801EC8FC: nop
    
            goto L_801EC904;
    }
    // 0x801EC8FC: nop

    // 0x801EC900: or          $v1, $a3, $zero
    ctx->r3 = ctx->r7 | 0;
L_801EC904:
    // 0x801EC904: beq         $v1, $zero, L_801EC920
    if (ctx->r3 == 0) {
        // 0x801EC908: addiu       $a0, $zero, 0x4
        ctx->r4 = ADD32(0, 0X4);
            goto L_801EC920;
    }
    // 0x801EC908: addiu       $a0, $zero, 0x4
    ctx->r4 = ADD32(0, 0X4);
    // 0x801EC90C: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x801EC910: jal         0x801E6FB0
    // 0x801EC914: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    FadeTransition_SetProps(rdram, ctx);
        goto after_0;
    // 0x801EC914: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    after_0:
    // 0x801EC918: jal         0x800C6AD0
    // 0x801EC91C: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    osViBlack_recomp(rdram, ctx);
        goto after_1;
    // 0x801EC91C: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    after_1:
L_801EC920:
    // 0x801EC920: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    // 0x801EC924: jal         0x801E6A4C
    // 0x801EC928: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_801E6A4C(rdram, ctx);
        goto after_2;
    // 0x801EC928: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_2:
    // 0x801EC92C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x801EC930: addiu       $a3, $zero, 0x1
    ctx->r7 = ADD32(0, 0X1);
    // 0x801EC934: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801EC938: sw          $a3, 0x7C80($at)
    MEM_W(0X7C80, ctx->r1) = ctx->r7;
    // 0x801EC93C: jr          $ra
    // 0x801EC940: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    return;
    // 0x801EC940: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
;}
RECOMP_FUNC void func_801EC944(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801EC944: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x801EC948: addiu       $v0, $v0, -0x54DC
    ctx->r2 = ADD32(ctx->r2, -0X54DC);
    // 0x801EC94C: lw          $t6, 0x0($v0)
    ctx->r14 = MEM_W(ctx->r2, 0X0);
    // 0x801EC950: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EC954: addiu       $t7, $zero, 0x5A
    ctx->r15 = ADD32(0, 0X5A);
    // 0x801EC958: sw          $t6, -0x19CC($at)
    MEM_W(-0X19CC, ctx->r1) = ctx->r14;
    // 0x801EC95C: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EC960: sw          $zero, -0x19D0($at)
    MEM_W(-0X19D0, ctx->r1) = 0;
    // 0x801EC964: sw          $t7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r15;
    // 0x801EC968: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EC96C: addiu       $t8, $zero, 0xF
    ctx->r24 = ADD32(0, 0XF);
    // 0x801EC970: sw          $t8, -0x19C8($at)
    MEM_W(-0X19C8, ctx->r1) = ctx->r24;
    // 0x801EC974: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EC978: addiu       $t9, $zero, 0x1
    ctx->r25 = ADD32(0, 0X1);
    // 0x801EC97C: sw          $t9, -0x19C4($at)
    MEM_W(-0X19C4, ctx->r1) = ctx->r25;
    // 0x801EC980: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EC984: sw          $zero, -0x19C0($at)
    MEM_W(-0X19C0, ctx->r1) = 0;
    // 0x801EC988: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EC98C: sw          $zero, -0x19BC($at)
    MEM_W(-0X19BC, ctx->r1) = 0;
    // 0x801EC990: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x801EC994: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x801EC998: sw          $zero, -0x54E4($at)
    MEM_W(-0X54E4, ctx->r1) = 0;
    // 0x801EC99C: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x801EC9A0: lui         $at, 0x800D
    ctx->r1 = S32(0X800D << 16);
    // 0x801EC9A4: addiu       $t0, $zero, 0x2
    ctx->r8 = ADD32(0, 0X2);
    // 0x801EC9A8: sw          $t0, 0x461C($at)
    MEM_W(0X461C, ctx->r1) = ctx->r8;
    // 0x801EC9AC: addiu       $a0, $zero, 0x5
    ctx->r4 = ADD32(0, 0X5);
    // 0x801EC9B0: jal         0x800C21F4
    // 0x801EC9B4: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C21F4(rdram, ctx);
        goto after_0;
    // 0x801EC9B4: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_0:
    // 0x801EC9B8: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x801EC9BC: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x801EC9C0: jr          $ra
    // 0x801EC9C4: nop

    return;
    // 0x801EC9C4: nop

;}
