#include "recomp.h"
#include "funcs.h"

RECOMP_FUNC void func_800BFA80(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800BFA80: andi        $t6, $a2, 0xFF
    ctx->r14 = ctx->r6 & 0XFF;
    // 0x800BFA84: mtc1        $t6, $f4
    ctx->f4.u32l = ctx->r14;
    // 0x800BFA88: lui         $at, 0x42C8
    ctx->r1 = S32(0X42C8 << 16);
    // 0x800BFA8C: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x800BFA90: cvt.s.w     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
    // 0x800BFA94: sll         $t7, $a0, 2
    ctx->r15 = S32(ctx->r4 << 2);
    // 0x800BFA98: addu        $t7, $t7, $a0
    ctx->r15 = ADD32(ctx->r15, ctx->r4);
    // 0x800BFA9C: lui         $t8, 0x8004
    ctx->r24 = S32(0X8004 << 16);
    // 0x800BFAA0: addiu       $t8, $t8, -0x338
    ctx->r24 = ADD32(ctx->r24, -0X338);
    // 0x800BFAA4: sll         $t7, $t7, 6
    ctx->r15 = S32(ctx->r15 << 6);
    // 0x800BFAA8: div.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = DIV_S(ctx->f6.fl, ctx->f8.fl);
    // 0x800BFAAC: addu        $v0, $t7, $t8
    ctx->r2 = ADD32(ctx->r15, ctx->r24);
    // 0x800BFAB0: lwc1        $f2, 0x18($v0)
    ctx->f2.u32l = MEM_W(ctx->r2, 0X18);
    // 0x800BFAB4: sw          $a2, 0x8($sp)
    MEM_W(0X8, ctx->r29) = ctx->r6;
    // 0x800BFAB8: sh          $zero, 0x10($v0)
    MEM_H(0X10, ctx->r2) = 0;
    // 0x800BFABC: swc1        $f2, 0x20($v0)
    MEM_W(0X20, ctx->r2) = ctx->f2.u32l;
    // 0x800BFAC0: mul.s       $f0, $f10, $f2
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f0.fl = MUL_S(ctx->f10.fl, ctx->f2.fl);
    // 0x800BFAC4: bnel        $a1, $zero, L_800BFAD8
    if (ctx->r5 != 0) {
        // 0x800BFAC8: mtc1        $a1, $f18
        ctx->f18.u32l = ctx->r5;
            goto L_800BFAD8;
    }
    goto skip_0;
    // 0x800BFAC8: mtc1        $a1, $f18
    ctx->f18.u32l = ctx->r5;
    skip_0:
    // 0x800BFACC: jr          $ra
    // 0x800BFAD0: swc1        $f0, 0x18($v0)
    MEM_W(0X18, ctx->r2) = ctx->f0.u32l;
    return;
    // 0x800BFAD0: swc1        $f0, 0x18($v0)
    MEM_W(0X18, ctx->r2) = ctx->f0.u32l;
    // 0x800BFAD4: mtc1        $a1, $f18
    ctx->f18.u32l = ctx->r5;
L_800BFAD8:
    // 0x800BFAD8: sub.s       $f16, $f0, $f2
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f16.fl = ctx->f0.fl - ctx->f2.fl;
    // 0x800BFADC: sb          $zero, 0x1($v0)
    MEM_B(0X1, ctx->r2) = 0;
    // 0x800BFAE0: sh          $a1, 0x10($v0)
    MEM_H(0X10, ctx->r2) = ctx->r5;
    // 0x800BFAE4: cvt.s.w     $f4, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    ctx->f4.fl = CVT_S_W(ctx->f18.u32l);
    // 0x800BFAE8: div.s       $f6, $f16, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = DIV_S(ctx->f16.fl, ctx->f4.fl);
    // 0x800BFAEC: swc1        $f6, 0x1C($v0)
    MEM_W(0X1C, ctx->r2) = ctx->f6.u32l;
    // 0x800BFAF0: jr          $ra
    // 0x800BFAF4: nop

    return;
    // 0x800BFAF4: nop

;}
RECOMP_FUNC void func_800BFAF8(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800BFAF8: sll         $t6, $a0, 2
    ctx->r14 = S32(ctx->r4 << 2);
    // 0x800BFAFC: addu        $t6, $t6, $a0
    ctx->r14 = ADD32(ctx->r14, ctx->r4);
    // 0x800BFB00: lui         $t7, 0x8004
    ctx->r15 = S32(0X8004 << 16);
    // 0x800BFB04: addiu       $t7, $t7, -0x338
    ctx->r15 = ADD32(ctx->r15, -0X338);
    // 0x800BFB08: sll         $t6, $t6, 6
    ctx->r14 = S32(ctx->r14 << 6);
    // 0x800BFB0C: addu        $v0, $t6, $t7
    ctx->r2 = ADD32(ctx->r14, ctx->r15);
    // 0x800BFB10: bne         $a1, $zero, L_800BFB24
    if (ctx->r5 != 0) {
        // 0x800BFB14: sh          $zero, 0x10($v0)
        MEM_H(0X10, ctx->r2) = 0;
            goto L_800BFB24;
    }
    // 0x800BFB14: sh          $zero, 0x10($v0)
    MEM_H(0X10, ctx->r2) = 0;
    // 0x800BFB18: lwc1        $f4, 0x20($v0)
    ctx->f4.u32l = MEM_W(ctx->r2, 0X20);
    // 0x800BFB1C: jr          $ra
    // 0x800BFB20: swc1        $f4, 0x18($v0)
    MEM_W(0X18, ctx->r2) = ctx->f4.u32l;
    return;
    // 0x800BFB20: swc1        $f4, 0x18($v0)
    MEM_W(0X18, ctx->r2) = ctx->f4.u32l;
L_800BFB24:
    // 0x800BFB24: mtc1        $a1, $f16
    ctx->f16.u32l = ctx->r5;
    // 0x800BFB28: lwc1        $f6, 0x20($v0)
    ctx->f6.u32l = MEM_W(ctx->r2, 0X20);
    // 0x800BFB2C: lwc1        $f8, 0x18($v0)
    ctx->f8.u32l = MEM_W(ctx->r2, 0X18);
    // 0x800BFB30: cvt.s.w     $f18, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    ctx->f18.fl = CVT_S_W(ctx->f16.u32l);
    // 0x800BFB34: sb          $zero, 0x1($v0)
    MEM_B(0X1, ctx->r2) = 0;
    // 0x800BFB38: sh          $a1, 0x10($v0)
    MEM_H(0X10, ctx->r2) = ctx->r5;
    // 0x800BFB3C: sub.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = ctx->f6.fl - ctx->f8.fl;
    // 0x800BFB40: div.s       $f4, $f10, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f4.fl = DIV_S(ctx->f10.fl, ctx->f18.fl);
    // 0x800BFB44: swc1        $f4, 0x1C($v0)
    MEM_W(0X1C, ctx->r2) = ctx->f4.u32l;
    // 0x800BFB48: jr          $ra
    // 0x800BFB4C: nop

    return;
    // 0x800BFB4C: nop

;}
RECOMP_FUNC void func_800BFB50(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800BFB50: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x800BFB54: mtc1        $at, $f0
    ctx->f0.u32l = ctx->r1;
    // 0x800BFB58: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x800BFB5C: addiu       $t6, $zero, 0x40
    ctx->r14 = ADD32(0, 0X40);
    // 0x800BFB60: swc1        $f0, 0x7E20($at)
    MEM_W(0X7E20, ctx->r1) = ctx->f0.u32l;
    // 0x800BFB64: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x800BFB68: swc1        $f0, 0x7E24($at)
    MEM_W(0X7E24, ctx->r1) = ctx->f0.u32l;
    // 0x800BFB6C: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x800BFB70: sb          $t6, 0x7E28($at)
    MEM_B(0X7E28, ctx->r1) = ctx->r14;
    // 0x800BFB74: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x800BFB78: addiu       $t7, $zero, 0x10
    ctx->r15 = ADD32(0, 0X10);
    // 0x800BFB7C: jr          $ra
    // 0x800BFB80: sb          $t7, 0x7E29($at)
    MEM_B(0X7E29, ctx->r1) = ctx->r15;
    return;
    // 0x800BFB80: sb          $t7, 0x7E29($at)
    MEM_B(0X7E29, ctx->r1) = ctx->r15;
;}
RECOMP_FUNC void func_800BFB84(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800BFB84: addiu       $sp, $sp, -0x38
    ctx->r29 = ADD32(ctx->r29, -0X38);
    // 0x800BFB88: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800BFB8C: lwc1        $f6, 0x0($a2)
    ctx->f6.u32l = MEM_W(ctx->r6, 0X0);
    // 0x800BFB90: lwc1        $f4, 0x0($a3)
    ctx->f4.u32l = MEM_W(ctx->r7, 0X0);
    // 0x800BFB94: sub.s       $f8, $f4, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = ctx->f4.fl - ctx->f6.fl;
    // 0x800BFB98: swc1        $f8, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->f8.u32l;
    // 0x800BFB9C: lwc1        $f4, 0x8($a2)
    ctx->f4.u32l = MEM_W(ctx->r6, 0X8);
    // 0x800BFBA0: lwc1        $f10, 0x8($a3)
    ctx->f10.u32l = MEM_W(ctx->r7, 0X8);
    // 0x800BFBA4: sub.s       $f6, $f10, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = ctx->f10.fl - ctx->f4.fl;
    // 0x800BFBA8: swc1        $f6, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->f6.u32l;
    // 0x800BFBAC: lwc1        $f10, 0x0($a0)
    ctx->f10.u32l = MEM_W(ctx->r4, 0X0);
    // 0x800BFBB0: lwc1        $f8, 0x0($a1)
    ctx->f8.u32l = MEM_W(ctx->r5, 0X0);
    // 0x800BFBB4: lwc1        $f6, 0x8($a0)
    ctx->f6.u32l = MEM_W(ctx->r4, 0X8);
    // 0x800BFBB8: lwc1        $f4, 0x8($a1)
    ctx->f4.u32l = MEM_W(ctx->r5, 0X8);
    // 0x800BFBBC: sub.s       $f18, $f8, $f10
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f18.fl = ctx->f8.fl - ctx->f10.fl;
    // 0x800BFBC0: sub.s       $f0, $f4, $f6
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f0.fl = ctx->f4.fl - ctx->f6.fl;
    // 0x800BFBC4: mul.s       $f8, $f18, $f18
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f8.fl = MUL_S(ctx->f18.fl, ctx->f18.fl);
    // 0x800BFBC8: swc1        $f18, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->f18.u32l;
    // 0x800BFBCC: mul.s       $f10, $f0, $f0
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f10.fl = MUL_S(ctx->f0.fl, ctx->f0.fl);
    // 0x800BFBD0: swc1        $f0, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->f0.u32l;
    // 0x800BFBD4: jal         0x800C7010
    // 0x800BFBD8: add.s       $f12, $f8, $f10
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f12.fl = ctx->f8.fl + ctx->f10.fl;
    _nsqrtf(rdram, ctx);
        goto after_0;
    // 0x800BFBD8: add.s       $f12, $f8, $f10
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f12.fl = ctx->f8.fl + ctx->f10.fl;
    after_0:
    // 0x800BFBDC: lwc1        $f18, 0x28($sp)
    ctx->f18.u32l = MEM_W(ctx->r29, 0X28);
    // 0x800BFBE0: lwc1        $f4, 0x30($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X30);
    // 0x800BFBE4: lwc1        $f6, 0x24($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X24);
    // 0x800BFBE8: lwc1        $f8, 0x2C($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X2C);
    // 0x800BFBEC: add.s       $f2, $f18, $f4
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f2.fl = ctx->f18.fl + ctx->f4.fl;
    // 0x800BFBF0: swc1        $f0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->f0.u32l;
    // 0x800BFBF4: add.s       $f14, $f6, $f8
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f14.fl = ctx->f6.fl + ctx->f8.fl;
    // 0x800BFBF8: mul.s       $f10, $f2, $f2
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f10.fl = MUL_S(ctx->f2.fl, ctx->f2.fl);
    // 0x800BFBFC: nop

    // 0x800BFC00: mul.s       $f4, $f14, $f14
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f4.fl = MUL_S(ctx->f14.fl, ctx->f14.fl);
    // 0x800BFC04: jal         0x800C7010
    // 0x800BFC08: add.s       $f12, $f10, $f4
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f12.fl = ctx->f10.fl + ctx->f4.fl;
    _nsqrtf(rdram, ctx);
        goto after_1;
    // 0x800BFC08: add.s       $f12, $f10, $f4
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f12.fl = ctx->f10.fl + ctx->f4.fl;
    after_1:
    // 0x800BFC0C: lwc1        $f16, 0x18($sp)
    ctx->f16.u32l = MEM_W(ctx->r29, 0X18);
    // 0x800BFC10: lui         $at, 0x4396
    ctx->r1 = S32(0X4396 << 16);
    // 0x800BFC14: mtc1        $at, $f14
    ctx->f14.u32l = ctx->r1;
    // 0x800BFC18: sub.s       $f12, $f16, $f0
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f12.fl = ctx->f16.fl - ctx->f0.fl;
    // 0x800BFC1C: lui         $at, 0x43B4
    ctx->r1 = S32(0X43B4 << 16);
    // 0x800BFC20: mtc1        $at, $f0
    ctx->f0.u32l = ctx->r1;
    // 0x800BFC24: lui         $at, 0x42FE
    ctx->r1 = S32(0X42FE << 16);
    // 0x800BFC28: c.lt.s      $f14, $f12
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 12);
    c1cs = ctx->f14.fl < ctx->f12.fl;
    // 0x800BFC2C: addiu       $t6, $zero, 0x10
    ctx->r14 = ADD32(0, 0X10);
    // 0x800BFC30: bc1fl       L_800BFC40
    if (!c1cs) {
        // 0x800BFC34: c.le.s      $f16, $f0
        CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 0);
    c1cs = ctx->f16.fl <= ctx->f0.fl;
            goto L_800BFC40;
    }
    goto skip_0;
    // 0x800BFC34: c.le.s      $f16, $f0
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 0);
    c1cs = ctx->f16.fl <= ctx->f0.fl;
    skip_0:
    // 0x800BFC38: mov.s       $f12, $f14
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 14);
    ctx->f12.fl = ctx->f14.fl;
    // 0x800BFC3C: c.le.s      $f16, $f0
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 0);
    c1cs = ctx->f16.fl <= ctx->f0.fl;
L_800BFC40:
    // 0x800BFC40: nop

    // 0x800BFC44: bc1fl       L_800BFC6C
    if (!c1cs) {
        // 0x800BFC48: mtc1        $at, $f2
        ctx->f2.u32l = ctx->r1;
            goto L_800BFC6C;
    }
    goto skip_1;
    // 0x800BFC48: mtc1        $at, $f2
    ctx->f2.u32l = ctx->r1;
    skip_1:
    // 0x800BFC4C: lui         $at, 0x42FE
    ctx->r1 = S32(0X42FE << 16);
    // 0x800BFC50: mtc1        $at, $f2
    ctx->f2.u32l = ctx->r1;
    // 0x800BFC54: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x800BFC58: mtc1        $zero, $f14
    ctx->f14.u32l = 0;
    // 0x800BFC5C: sb          $t6, 0x7E29($at)
    MEM_B(0X7E29, ctx->r1) = ctx->r14;
    // 0x800BFC60: b           L_800BFCC8
    // 0x800BFC64: mov.s       $f0, $f2
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    ctx->f0.fl = ctx->f2.fl;
        goto L_800BFCC8;
    // 0x800BFC64: mov.s       $f0, $f2
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    ctx->f0.fl = ctx->f2.fl;
    // 0x800BFC68: mtc1        $at, $f2
    ctx->f2.u32l = ctx->r1;
L_800BFC6C:
    // 0x800BFC6C: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x800BFC70: lwc1        $f6, -0x3C9C($at)
    ctx->f6.u32l = MEM_W(ctx->r1, -0X3C9C);
    // 0x800BFC74: mtc1        $zero, $f14
    ctx->f14.u32l = 0;
    // 0x800BFC78: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x800BFC7C: div.s       $f8, $f6, $f16
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f8.fl = DIV_S(ctx->f6.fl, ctx->f16.fl);
    // 0x800BFC80: c.lt.s      $f14, $f12
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 12);
    c1cs = ctx->f14.fl < ctx->f12.fl;
    // 0x800BFC84: sub.s       $f16, $f16, $f0
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f16.fl = ctx->f16.fl - ctx->f0.fl;
    // 0x800BFC88: sub.s       $f10, $f2, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = ctx->f2.fl - ctx->f8.fl;
    // 0x800BFC8C: trunc.w.s   $f4, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    ctx->f4.u32l = TRUNC_W_S(ctx->f10.fl);
    // 0x800BFC90: mfc1        $t8, $f4
    ctx->r24 = (int32_t)ctx->f4.u32l;
    // 0x800BFC94: bc1f        L_800BFCB4
    if (!c1cs) {
        // 0x800BFC98: sb          $t8, 0x7E29($at)
        MEM_B(0X7E29, ctx->r1) = ctx->r24;
            goto L_800BFCB4;
    }
    // 0x800BFC98: sb          $t8, 0x7E29($at)
    MEM_B(0X7E29, ctx->r1) = ctx->r24;
    // 0x800BFC9C: lui         $at, 0x4190
    ctx->r1 = S32(0X4190 << 16);
    // 0x800BFCA0: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x800BFCA4: nop

    // 0x800BFCA8: div.s       $f8, $f16, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = DIV_S(ctx->f16.fl, ctx->f6.fl);
    // 0x800BFCAC: b           L_800BFCC8
    // 0x800BFCB0: sub.s       $f0, $f2, $f8
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f0.fl = ctx->f2.fl - ctx->f8.fl;
        goto L_800BFCC8;
    // 0x800BFCB0: sub.s       $f0, $f2, $f8
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f0.fl = ctx->f2.fl - ctx->f8.fl;
L_800BFCB4:
    // 0x800BFCB4: lui         $at, 0x3D80
    ctx->r1 = S32(0X3D80 << 16);
    // 0x800BFCB8: mtc1        $at, $f10
    ctx->f10.u32l = ctx->r1;
    // 0x800BFCBC: nop

    // 0x800BFCC0: mul.s       $f4, $f16, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f4.fl = MUL_S(ctx->f16.fl, ctx->f10.fl);
    // 0x800BFCC4: sub.s       $f0, $f2, $f4
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f0.fl = ctx->f2.fl - ctx->f4.fl;
L_800BFCC8:
    // 0x800BFCC8: div.s       $f0, $f0, $f2
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f0.fl = DIV_S(ctx->f0.fl, ctx->f2.fl);
    // 0x800BFCCC: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x800BFCD0: mtc1        $at, $f2
    ctx->f2.u32l = ctx->r1;
    // 0x800BFCD4: lui         $at, 0x43C8
    ctx->r1 = S32(0X43C8 << 16);
    // 0x800BFCD8: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x800BFCDC: nop

    // 0x800BFCE0: div.s       $f8, $f12, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = DIV_S(ctx->f12.fl, ctx->f6.fl);
    // 0x800BFCE4: c.lt.s      $f0, $f14
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 14);
    c1cs = ctx->f0.fl < ctx->f14.fl;
    // 0x800BFCE8: nop

    // 0x800BFCEC: bc1fl       L_800BFCFC
    if (!c1cs) {
        // 0x800BFCF0: sub.s       $f10, $f2, $f8
        CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = ctx->f2.fl - ctx->f8.fl;
            goto L_800BFCFC;
    }
    goto skip_2;
    // 0x800BFCF0: sub.s       $f10, $f2, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = ctx->f2.fl - ctx->f8.fl;
    skip_2:
    // 0x800BFCF4: mov.s       $f0, $f14
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 14);
    ctx->f0.fl = ctx->f14.fl;
    // 0x800BFCF8: sub.s       $f10, $f2, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = ctx->f2.fl - ctx->f8.fl;
L_800BFCFC:
    // 0x800BFCFC: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x800BFD00: lwc1        $f6, -0x3C98($at)
    ctx->f6.u32l = MEM_W(ctx->r1, -0X3C98);
    // 0x800BFD04: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x800BFD08: div.s       $f4, $f2, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f4.fl = DIV_S(ctx->f2.fl, ctx->f10.fl);
    // 0x800BFD0C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800BFD10: lbu         $t9, 0x4B($sp)
    ctx->r25 = MEM_BU(ctx->r29, 0X4B);
    // 0x800BFD14: addiu       $sp, $sp, 0x38
    ctx->r29 = ADD32(ctx->r29, 0X38);
    // 0x800BFD18: add.s       $f8, $f4, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = ctx->f4.fl + ctx->f6.fl;
    // 0x800BFD1C: swc1        $f8, 0x7E20($at)
    MEM_W(0X7E20, ctx->r1) = ctx->f8.u32l;
    // 0x800BFD20: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x800BFD24: swc1        $f0, 0x7E24($at)
    MEM_W(0X7E24, ctx->r1) = ctx->f0.u32l;
    // 0x800BFD28: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x800BFD2C: jr          $ra
    // 0x800BFD30: sb          $t9, 0x7E28($at)
    MEM_B(0X7E28, ctx->r1) = ctx->r25;
    return;
    // 0x800BFD30: sb          $t9, 0x7E28($at)
    MEM_B(0X7E28, ctx->r1) = ctx->r25;
;}
RECOMP_FUNC void func_800BFD34(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800BFD34: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800BFD38: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800BFD3C: addiu       $t6, $zero, 0x1
    ctx->r14 = ADD32(0, 0X1);
    // 0x800BFD40: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x800BFD44: lui         $a0, 0x600
    ctx->r4 = S32(0X600 << 16);
    // 0x800BFD48: sw          $t6, 0x7CBC($at)
    MEM_W(0X7CBC, ctx->r1) = ctx->r14;
    // 0x800BFD4C: ori         $a0, $a0, 0x4
    ctx->r4 = ctx->r4 | 0X4;
    // 0x800BFD50: jal         0x800C53D4
    // 0x800BFD54: addiu       $a1, $zero, -0x1
    ctx->r5 = ADD32(0, -0X1);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_0;
    // 0x800BFD54: addiu       $a1, $zero, -0x1
    ctx->r5 = ADD32(0, -0X1);
    after_0:
    // 0x800BFD58: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800BFD5C: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800BFD60: jr          $ra
    // 0x800BFD64: nop

    return;
    // 0x800BFD64: nop

;}
RECOMP_FUNC void func_800BFD68(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800BFD68: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800BFD6C: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800BFD70: addiu       $t6, $zero, 0x1
    ctx->r14 = ADD32(0, 0X1);
    // 0x800BFD74: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x800BFD78: lui         $a0, 0x600
    ctx->r4 = S32(0X600 << 16);
    // 0x800BFD7C: sw          $t6, 0x7CC0($at)
    MEM_W(0X7CC0, ctx->r1) = ctx->r14;
    // 0x800BFD80: ori         $a0, $a0, 0x304
    ctx->r4 = ctx->r4 | 0X304;
    // 0x800BFD84: jal         0x800C53D4
    // 0x800BFD88: addiu       $a1, $zero, -0x1
    ctx->r5 = ADD32(0, -0X1);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_0;
    // 0x800BFD88: addiu       $a1, $zero, -0x1
    ctx->r5 = ADD32(0, -0X1);
    after_0:
    // 0x800BFD8C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800BFD90: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800BFD94: jr          $ra
    // 0x800BFD98: nop

    return;
    // 0x800BFD98: nop

;}
RECOMP_FUNC void func_800BFD9C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800BFD9C: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
    // 0x800BFDA0: sb          $zero, 0x1D($a0)
    MEM_B(0X1D, ctx->r4) = 0;
    // 0x800BFDA4: sb          $v0, 0x7($a0)
    MEM_B(0X7, ctx->r4) = ctx->r2;
    // 0x800BFDA8: sb          $v0, 0x3($a0)
    MEM_B(0X3, ctx->r4) = ctx->r2;
    // 0x800BFDAC: sb          $zero, 0x8($a0)
    MEM_B(0X8, ctx->r4) = 0;
    // 0x800BFDB0: sb          $zero, 0x9($a0)
    MEM_B(0X9, ctx->r4) = 0;
    // 0x800BFDB4: sb          $zero, 0x13($a0)
    MEM_B(0X13, ctx->r4) = 0;
    // 0x800BFDB8: sb          $zero, 0x12($a0)
    MEM_B(0X12, ctx->r4) = 0;
    // 0x800BFDBC: sb          $zero, 0x11($a0)
    MEM_B(0X11, ctx->r4) = 0;
    // 0x800BFDC0: sb          $zero, 0x4($a0)
    MEM_B(0X4, ctx->r4) = 0;
    // 0x800BFDC4: sb          $zero, 0x6($a0)
    MEM_B(0X6, ctx->r4) = 0;
    // 0x800BFDC8: jr          $ra
    // 0x800BFDCC: sb          $zero, 0x19($a0)
    MEM_B(0X19, ctx->r4) = 0;
    return;
    // 0x800BFDCC: sb          $zero, 0x19($a0)
    MEM_B(0X19, ctx->r4) = 0;
;}
RECOMP_FUNC void func_800BFDD0(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800BFDD0: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x800BFDD4: sw          $zero, 0x7CBC($at)
    MEM_W(0X7CBC, ctx->r1) = 0;
    // 0x800BFDD8: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x800BFDDC: addiu       $t6, $zero, 0x190
    ctx->r14 = ADD32(0, 0X190);
    // 0x800BFDE0: sw          $t6, 0x7CE8($at)
    MEM_W(0X7CE8, ctx->r1) = ctx->r14;
    // 0x800BFDE4: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800BFDE8: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x800BFDEC: sw          $zero, 0x7CAC($at)
    MEM_W(0X7CAC, ctx->r1) = 0;
    // 0x800BFDF0: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800BFDF4: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    // 0x800BFDF8: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x800BFDFC: sw          $zero, 0x7DD8($at)
    MEM_W(0X7DD8, ctx->r1) = 0;
    // 0x800BFE00: lui         $a0, 0x100
    ctx->r4 = S32(0X100 << 16);
    // 0x800BFE04: jal         0x800C538C
    // 0x800BFE08: lui         $a1, 0x3F80
    ctx->r5 = S32(0X3F80 << 16);
    AudioThread_QueueCmdF32(rdram, ctx);
        goto after_0;
    // 0x800BFE08: lui         $a1, 0x3F80
    ctx->r5 = S32(0X3F80 << 16);
    after_0:
    // 0x800BFE0C: lui         $a0, 0x100
    ctx->r4 = S32(0X100 << 16);
    // 0x800BFE10: ori         $a0, $a0, 0x200
    ctx->r4 = ctx->r4 | 0X200;
    // 0x800BFE14: jal         0x800C538C
    // 0x800BFE18: lui         $a1, 0x3F80
    ctx->r5 = S32(0X3F80 << 16);
    AudioThread_QueueCmdF32(rdram, ctx);
        goto after_1;
    // 0x800BFE18: lui         $a1, 0x3F80
    ctx->r5 = S32(0X3F80 << 16);
    after_1:
    // 0x800BFE1C: lui         $a1, 0x3DCC
    ctx->r5 = S32(0X3DCC << 16);
    // 0x800BFE20: ori         $a1, $a1, 0xCCCD
    ctx->r5 = ctx->r5 | 0XCCCD;
    // 0x800BFE24: jal         0x800C538C
    // 0x800BFE28: lui         $a0, 0x400
    ctx->r4 = S32(0X400 << 16);
    AudioThread_QueueCmdF32(rdram, ctx);
        goto after_2;
    // 0x800BFE28: lui         $a0, 0x400
    ctx->r4 = S32(0X400 << 16);
    after_2:
    // 0x800BFE2C: lui         $a0, 0x600
    ctx->r4 = S32(0X600 << 16);
    // 0x800BFE30: jal         0x800C53D4
    // 0x800BFE34: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_3;
    // 0x800BFE34: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    after_3:
    // 0x800BFE38: jal         0x800BFD9C
    // 0x800BFE3C: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
    func_800BFD9C(rdram, ctx);
        goto after_4;
    // 0x800BFE3C: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
    after_4:
    // 0x800BFE40: mtc1        $zero, $f4
    ctx->f4.u32l = 0;
    // 0x800BFE44: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800BFE48: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x800BFE4C: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x800BFE50: addiu       $v0, $v0, 0x7DF8
    ctx->r2 = ADD32(ctx->r2, 0X7DF8);
    // 0x800BFE54: swc1        $f4, 0x7CC8($at)
    MEM_W(0X7CC8, ctx->r1) = ctx->f4.u32l;
    // 0x800BFE58: addiu       $t7, $zero, -0x1
    ctx->r15 = ADD32(0, -0X1);
    // 0x800BFE5C: sb          $zero, 0x0($v0)
    MEM_B(0X0, ctx->r2) = 0;
    // 0x800BFE60: sb          $zero, 0x1($v0)
    MEM_B(0X1, ctx->r2) = 0;
    // 0x800BFE64: sb          $t7, 0x3($v0)
    MEM_B(0X3, ctx->r2) = ctx->r15;
    // 0x800BFE68: jr          $ra
    // 0x800BFE6C: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    return;
    // 0x800BFE6C: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
;}
RECOMP_FUNC void func_800BFE70(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800BFE70: lui         $t6, 0x801D
    ctx->r14 = S32(0X801D << 16);
    // 0x800BFE74: lw          $t6, 0x7DC4($t6)
    ctx->r14 = MEM_W(ctx->r14, 0X7DC4);
    // 0x800BFE78: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800BFE7C: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800BFE80: beq         $t6, $zero, L_800BFE98
    if (ctx->r14 == 0) {
        // 0x800BFE84: or          $a2, $a0, $zero
        ctx->r6 = ctx->r4 | 0;
            goto L_800BFE98;
    }
    // 0x800BFE84: or          $a2, $a0, $zero
    ctx->r6 = ctx->r4 | 0;
    // 0x800BFE88: jal         0x800BFEF8
    // 0x800BFE8C: nop

    func_800BFEF8(rdram, ctx);
        goto after_0;
    // 0x800BFE8C: nop

    after_0:
    // 0x800BFE90: b           L_800BFEEC
    // 0x800BFE94: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_800BFEEC;
    // 0x800BFE94: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_800BFE98:
    // 0x800BFE98: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x800BFE9C: sw          $zero, 0x7CBC($at)
    MEM_W(0X7CBC, ctx->r1) = 0;
    // 0x800BFEA0: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x800BFEA4: addiu       $t7, $zero, 0x1
    ctx->r15 = ADD32(0, 0X1);
    // 0x800BFEA8: lui         $a0, 0x100
    ctx->r4 = S32(0X100 << 16);
    // 0x800BFEAC: sw          $t7, 0x7CAC($at)
    MEM_W(0X7CAC, ctx->r1) = ctx->r15;
    // 0x800BFEB0: ori         $a0, $a0, 0x200
    ctx->r4 = ctx->r4 | 0X200;
    // 0x800BFEB4: lui         $a1, 0x3F80
    ctx->r5 = S32(0X3F80 << 16);
    // 0x800BFEB8: jal         0x800C538C
    // 0x800BFEBC: sw          $a2, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r6;
    AudioThread_QueueCmdF32(rdram, ctx);
        goto after_1;
    // 0x800BFEBC: sw          $a2, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r6;
    after_1:
    // 0x800BFEC0: jal         0x800BFD9C
    // 0x800BFEC4: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
    func_800BFD9C(rdram, ctx);
        goto after_2;
    // 0x800BFEC4: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
    after_2:
    // 0x800BFEC8: mtc1        $zero, $f4
    ctx->f4.u32l = 0;
    // 0x800BFECC: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x800BFED0: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x800BFED4: addiu       $v0, $v0, 0x7DF8
    ctx->r2 = ADD32(ctx->r2, 0X7DF8);
    // 0x800BFED8: swc1        $f4, 0x7CC8($at)
    MEM_W(0X7CC8, ctx->r1) = ctx->f4.u32l;
    // 0x800BFEDC: addiu       $t8, $zero, -0x1
    ctx->r24 = ADD32(0, -0X1);
    // 0x800BFEE0: sb          $zero, 0x0($v0)
    MEM_B(0X0, ctx->r2) = 0;
    // 0x800BFEE4: sb          $t8, 0x3($v0)
    MEM_B(0X3, ctx->r2) = ctx->r24;
    // 0x800BFEE8: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_800BFEEC:
    // 0x800BFEEC: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800BFEF0: jr          $ra
    // 0x800BFEF4: nop

    return;
    // 0x800BFEF4: nop

;}
RECOMP_FUNC void func_800BFEF8(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800BFEF8: lui         $t6, 0x801D
    ctx->r14 = S32(0X801D << 16);
    // 0x800BFEFC: lw          $t6, 0x7DC0($t6)
    ctx->r14 = MEM_W(ctx->r14, 0X7DC0);
    // 0x800BFF00: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800BFF04: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x800BFF08: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800BFF0C: beq         $t6, $at, L_800BFF9C
    if (ctx->r14 == ctx->r1) {
        // 0x800BFF10: sw          $a0, 0x18($sp)
        MEM_W(0X18, ctx->r29) = ctx->r4;
            goto L_800BFF9C;
    }
    // 0x800BFF10: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    // 0x800BFF14: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x800BFF18: sw          $zero, 0x7CC0($at)
    MEM_W(0X7CC0, ctx->r1) = 0;
    // 0x800BFF1C: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x800BFF20: lui         $a0, 0x100
    ctx->r4 = S32(0X100 << 16);
    // 0x800BFF24: sw          $zero, 0x7DDC($at)
    MEM_W(0X7DDC, ctx->r1) = 0;
    // 0x800BFF28: ori         $a0, $a0, 0x300
    ctx->r4 = ctx->r4 | 0X300;
    // 0x800BFF2C: jal         0x800C538C
    // 0x800BFF30: lui         $a1, 0x3F80
    ctx->r5 = S32(0X3F80 << 16);
    AudioThread_QueueCmdF32(rdram, ctx);
        goto after_0;
    // 0x800BFF30: lui         $a1, 0x3F80
    ctx->r5 = S32(0X3F80 << 16);
    after_0:
    // 0x800BFF34: lui         $a0, 0x400
    ctx->r4 = S32(0X400 << 16);
    // 0x800BFF38: lui         $a1, 0x3DCC
    ctx->r5 = S32(0X3DCC << 16);
    // 0x800BFF3C: ori         $a1, $a1, 0xCCCD
    ctx->r5 = ctx->r5 | 0XCCCD;
    // 0x800BFF40: jal         0x800C538C
    // 0x800BFF44: ori         $a0, $a0, 0x300
    ctx->r4 = ctx->r4 | 0X300;
    AudioThread_QueueCmdF32(rdram, ctx);
        goto after_1;
    // 0x800BFF44: ori         $a0, $a0, 0x300
    ctx->r4 = ctx->r4 | 0X300;
    after_1:
    // 0x800BFF48: lui         $a0, 0x600
    ctx->r4 = S32(0X600 << 16);
    // 0x800BFF4C: ori         $a0, $a0, 0x300
    ctx->r4 = ctx->r4 | 0X300;
    // 0x800BFF50: jal         0x800C53D4
    // 0x800BFF54: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_2;
    // 0x800BFF54: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    after_2:
    // 0x800BFF58: lui         $a0, 0x100
    ctx->r4 = S32(0X100 << 16);
    // 0x800BFF5C: ori         $a0, $a0, 0x200
    ctx->r4 = ctx->r4 | 0X200;
    // 0x800BFF60: jal         0x800C538C
    // 0x800BFF64: lui         $a1, 0x3F80
    ctx->r5 = S32(0X3F80 << 16);
    AudioThread_QueueCmdF32(rdram, ctx);
        goto after_3;
    // 0x800BFF64: lui         $a1, 0x3F80
    ctx->r5 = S32(0X3F80 << 16);
    after_3:
    // 0x800BFF68: jal         0x800BFD9C
    // 0x800BFF6C: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
    func_800BFD9C(rdram, ctx);
        goto after_4;
    // 0x800BFF6C: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
    after_4:
    // 0x800BFF70: mtc1        $zero, $f0
    ctx->f0.u32l = 0;
    // 0x800BFF74: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x800BFF78: addiu       $v0, $v0, 0x7E00
    ctx->r2 = ADD32(ctx->r2, 0X7E00);
    // 0x800BFF7C: lui         $v1, 0x800E
    ctx->r3 = S32(0X800E << 16);
    // 0x800BFF80: addiu       $v1, $v1, 0x7CC8
    ctx->r3 = ADD32(ctx->r3, 0X7CC8);
    // 0x800BFF84: addiu       $t7, $zero, -0x1
    ctx->r15 = ADD32(0, -0X1);
    // 0x800BFF88: sb          $zero, 0x0($v0)
    MEM_B(0X0, ctx->r2) = 0;
    // 0x800BFF8C: sb          $t7, 0x3($v0)
    MEM_B(0X3, ctx->r2) = ctx->r15;
    // 0x800BFF90: sb          $zero, 0x1($v0)
    MEM_B(0X1, ctx->r2) = 0;
    // 0x800BFF94: swc1        $f0, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->f0.u32l;
    // 0x800BFF98: swc1        $f0, 0x8($v1)
    MEM_W(0X8, ctx->r3) = ctx->f0.u32l;
L_800BFF9C:
    // 0x800BFF9C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800BFFA0: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800BFFA4: jr          $ra
    // 0x800BFFA8: nop

    return;
    // 0x800BFFA8: nop

;}
RECOMP_FUNC void func_800BFFAC(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800BFFAC: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800BFFB0: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800BFFB4: jal         0x800BFEF8
    // 0x800BFFB8: nop

    func_800BFEF8(rdram, ctx);
        goto after_0;
    // 0x800BFFB8: nop

    after_0:
    // 0x800BFFBC: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800BFFC0: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800BFFC4: jr          $ra
    // 0x800BFFC8: nop

    return;
    // 0x800BFFC8: nop

;}
RECOMP_FUNC void func_800BFFCC(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800BFFCC: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800BFFD0: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800BFFD4: jal         0x800BFD68
    // 0x800BFFD8: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    func_800BFD68(rdram, ctx);
        goto after_0;
    // 0x800BFFD8: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    after_0:
    // 0x800BFFDC: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800BFFE0: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800BFFE4: jr          $ra
    // 0x800BFFE8: nop

    return;
    // 0x800BFFE8: nop

;}
RECOMP_FUNC void func_800BFFEC(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800BFFEC: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x800BFFF0: sw          $a0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r4;
    // 0x800BFFF4: lbu         $t7, 0x23($sp)
    ctx->r15 = MEM_BU(ctx->r29, 0X23);
    // 0x800BFFF8: sw          $a1, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r5;
    // 0x800BFFFC: sll         $a1, $a2, 24
    ctx->r5 = S32(ctx->r6 << 24);
    // 0x800C0000: lui         $at, 0x600
    ctx->r1 = S32(0X600 << 16);
    // 0x800C0004: sll         $t8, $t7, 8
    ctx->r24 = S32(ctx->r15 << 8);
    // 0x800C0008: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800C000C: or          $a3, $t8, $at
    ctx->r7 = ctx->r24 | ctx->r1;
    // 0x800C0010: sra         $t0, $a1, 24
    ctx->r8 = S32(SIGNED(ctx->r5) >> 24);
    // 0x800C0014: sw          $a2, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r6;
    // 0x800C0018: or          $a1, $t0, $zero
    ctx->r5 = ctx->r8 | 0;
    // 0x800C001C: ori         $a0, $a3, 0x5
    ctx->r4 = ctx->r7 | 0X5;
    // 0x800C0020: jal         0x800C53D4
    // 0x800C0024: sw          $a3, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r7;
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_0;
    // 0x800C0024: sw          $a3, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r7;
    after_0:
    // 0x800C0028: lw          $a0, 0x1C($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X1C);
    // 0x800C002C: jal         0x800C53D4
    // 0x800C0030: lb          $a1, 0x27($sp)
    ctx->r5 = MEM_B(ctx->r29, 0X27);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_1;
    // 0x800C0030: lb          $a1, 0x27($sp)
    ctx->r5 = MEM_B(ctx->r29, 0X27);
    after_1:
    // 0x800C0034: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800C0038: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x800C003C: jr          $ra
    // 0x800C0040: nop

    return;
    // 0x800C0040: nop

;}
RECOMP_FUNC void func_800C0044(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C0044: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x800C0048: or          $a3, $a0, $zero
    ctx->r7 = ctx->r4 | 0;
    // 0x800C004C: sw          $a1, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r5;
    // 0x800C0050: andi        $v0, $a3, 0xFF
    ctx->r2 = ctx->r7 & 0XFF;
    // 0x800C0054: sll         $t7, $v0, 8
    ctx->r15 = S32(ctx->r2 << 8);
    // 0x800C0058: sll         $a1, $a2, 24
    ctx->r5 = S32(ctx->r6 << 24);
    // 0x800C005C: lui         $at, 0x600
    ctx->r1 = S32(0X600 << 16);
    // 0x800C0060: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800C0064: sw          $a0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r4;
    // 0x800C0068: or          $v0, $t7, $at
    ctx->r2 = ctx->r15 | ctx->r1;
    // 0x800C006C: sra         $t9, $a1, 24
    ctx->r25 = S32(SIGNED(ctx->r5) >> 24);
    // 0x800C0070: sw          $a2, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r6;
    // 0x800C0074: or          $a1, $t9, $zero
    ctx->r5 = ctx->r25 | 0;
    // 0x800C0078: ori         $a0, $v0, 0x6
    ctx->r4 = ctx->r2 | 0X6;
    // 0x800C007C: jal         0x800C53D4
    // 0x800C0080: sw          $v0, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r2;
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_0;
    // 0x800C0080: sw          $v0, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r2;
    after_0:
    // 0x800C0084: lw          $v0, 0x1C($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X1C);
    // 0x800C0088: lb          $a1, 0x27($sp)
    ctx->r5 = MEM_B(ctx->r29, 0X27);
    // 0x800C008C: jal         0x800C53D4
    // 0x800C0090: ori         $a0, $v0, 0x1
    ctx->r4 = ctx->r2 | 0X1;
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_1;
    // 0x800C0090: ori         $a0, $v0, 0x1
    ctx->r4 = ctx->r2 | 0X1;
    after_1:
    // 0x800C0094: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800C0098: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x800C009C: jr          $ra
    // 0x800C00A0: nop

    return;
    // 0x800C00A0: nop

;}
RECOMP_FUNC void alSynFreeFX(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C00A4: sw          $a0, 0x0($sp)
    MEM_W(0X0, ctx->r29) = ctx->r4;
    // 0x800C00A8: jr          $ra
    // 0x800C00AC: sw          $a1, 0x4($sp)
    MEM_W(0X4, ctx->r29) = ctx->r5;
    return;
    // 0x800C00AC: sw          $a1, 0x4($sp)
    MEM_W(0X4, ctx->r29) = ctx->r5;
;}
RECOMP_FUNC void func_800C00B0(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C00B0: mtc1        $a1, $f12
    ctx->f12.u32l = ctx->r5;
    // 0x800C00B4: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800C00B8: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    // 0x800C00BC: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800C00C0: lui         $a0, 0x400
    ctx->r4 = S32(0X400 << 16);
    // 0x800C00C4: mfc1        $a1, $f12
    ctx->r5 = (int32_t)ctx->f12.u32l;
    // 0x800C00C8: jal         0x800C538C
    // 0x800C00CC: ori         $a0, $a0, 0x300
    ctx->r4 = ctx->r4 | 0X300;
    AudioThread_QueueCmdF32(rdram, ctx);
        goto after_0;
    // 0x800C00CC: ori         $a0, $a0, 0x300
    ctx->r4 = ctx->r4 | 0X300;
    after_0:
    // 0x800C00D0: lb          $t6, 0x1B($sp)
    ctx->r14 = MEM_B(ctx->r29, 0X1B);
    // 0x800C00D4: lui         $at, 0x42FE
    ctx->r1 = S32(0X42FE << 16);
    // 0x800C00D8: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x800C00DC: mtc1        $t6, $f4
    ctx->f4.u32l = ctx->r14;
    // 0x800C00E0: lui         $a0, 0x100
    ctx->r4 = S32(0X100 << 16);
    // 0x800C00E4: ori         $a0, $a0, 0x300
    ctx->r4 = ctx->r4 | 0X300;
    // 0x800C00E8: cvt.s.w     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
    // 0x800C00EC: div.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = DIV_S(ctx->f6.fl, ctx->f8.fl);
    // 0x800C00F0: mfc1        $a1, $f10
    ctx->r5 = (int32_t)ctx->f10.u32l;
    // 0x800C00F4: jal         0x800C538C
    // 0x800C00F8: nop

    AudioThread_QueueCmdF32(rdram, ctx);
        goto after_1;
    // 0x800C00F8: nop

    after_1:
    // 0x800C00FC: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800C0100: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800C0104: jr          $ra
    // 0x800C0108: nop

    return;
    // 0x800C0108: nop

;}
RECOMP_FUNC void func_800C010C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C010C: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x800C0110: lb          $v0, 0x7C94($v0)
    ctx->r2 = MEM_B(ctx->r2, 0X7C94);
    // 0x800C0114: addiu       $sp, $sp, -0x60
    ctx->r29 = ADD32(ctx->r29, -0X60);
    // 0x800C0118: sw          $s0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r16;
    // 0x800C011C: addiu       $at, $zero, 0x4
    ctx->r1 = ADD32(0, 0X4);
    // 0x800C0120: or          $s0, $a0, $zero
    ctx->r16 = ctx->r4 | 0;
    // 0x800C0124: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x800C0128: bne         $v0, $at, L_800C0170
    if (ctx->r2 != ctx->r1) {
        // 0x800C012C: sw          $a1, 0x64($sp)
        MEM_W(0X64, ctx->r29) = ctx->r5;
            goto L_800C0170;
    }
    // 0x800C012C: sw          $a1, 0x64($sp)
    MEM_W(0X64, ctx->r29) = ctx->r5;
    // 0x800C0130: lb          $t6, 0x18($s0)
    ctx->r14 = MEM_B(ctx->r16, 0X18);
    // 0x800C0134: lb          $t7, 0x67($sp)
    ctx->r15 = MEM_B(ctx->r29, 0X67);
    // 0x800C0138: beq         $t6, $zero, L_800C1178
    if (ctx->r14 == 0) {
        // 0x800C013C: slti        $at, $t7, 0x2
        ctx->r1 = SIGNED(ctx->r15) < 0X2 ? 1 : 0;
            goto L_800C1178;
    }
    // 0x800C013C: slti        $at, $t7, 0x2
    ctx->r1 = SIGNED(ctx->r15) < 0X2 ? 1 : 0;
    // 0x800C0140: beq         $at, $zero, L_800C1178
    if (ctx->r1 == 0) {
        // 0x800C0144: lbu         $a3, 0x57($sp)
        ctx->r7 = MEM_BU(ctx->r29, 0X57);
            goto L_800C1178;
    }
    // 0x800C0144: lbu         $a3, 0x57($sp)
    ctx->r7 = MEM_BU(ctx->r29, 0X57);
    // 0x800C0148: multu       $a3, $t7
    result = U64(U32(ctx->r7)) * U64(U32(ctx->r15)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x800C014C: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x800C0150: addiu       $a2, $zero, 0x7F
    ctx->r6 = ADD32(0, 0X7F);
    // 0x800C0154: mflo        $a0
    ctx->r4 = lo;
    // 0x800C0158: addiu       $a0, $a0, 0x2
    ctx->r4 = ADD32(ctx->r4, 0X2);
    // 0x800C015C: andi        $t8, $a0, 0xFF
    ctx->r24 = ctx->r4 & 0XFF;
    // 0x800C0160: jal         0x800BFFEC
    // 0x800C0164: or          $a0, $t8, $zero
    ctx->r4 = ctx->r24 | 0;
    func_800BFFEC(rdram, ctx);
        goto after_0;
    // 0x800C0164: or          $a0, $t8, $zero
    ctx->r4 = ctx->r24 | 0;
    after_0:
    // 0x800C0168: b           L_800C1178
    // 0x800C016C: sb          $zero, 0x18($s0)
    MEM_B(0X18, ctx->r16) = 0;
        goto L_800C1178;
    // 0x800C016C: sb          $zero, 0x18($s0)
    MEM_B(0X18, ctx->r16) = 0;
L_800C0170:
    // 0x800C0170: addiu       $at, $zero, 0x7
    ctx->r1 = ADD32(0, 0X7);
    // 0x800C0174: bne         $v0, $at, L_800C1178
    if (ctx->r2 != ctx->r1) {
        // 0x800C0178: lui         $v1, 0x801D
        ctx->r3 = S32(0X801D << 16);
            goto L_800C1178;
    }
    // 0x800C0178: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x800C017C: lw          $v1, 0x7DC0($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X7DC0);
    // 0x800C0180: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x800C0184: bne         $v1, $zero, L_800C02AC
    if (ctx->r3 != 0) {
        // 0x800C0188: nop
    
            goto L_800C02AC;
    }
    // 0x800C0188: nop

    // 0x800C018C: lb          $t9, 0x67($sp)
    ctx->r25 = MEM_B(ctx->r29, 0X67);
    // 0x800C0190: lui         $t3, 0x800E
    ctx->r11 = S32(0X800E << 16);
    // 0x800C0194: bnel        $t9, $zero, L_800C02E4
    if (ctx->r25 != 0) {
        // 0x800C0198: addiu       $t0, $zero, 0x3
        ctx->r8 = ADD32(0, 0X3);
            goto L_800C02E4;
    }
    goto skip_0;
    // 0x800C0198: addiu       $t0, $zero, 0x3
    ctx->r8 = ADD32(0, 0X3);
    skip_0:
    // 0x800C019C: lw          $t3, 0x7CE8($t3)
    ctx->r11 = MEM_W(ctx->r11, 0X7CE8);
    // 0x800C01A0: bnel        $t3, $zero, L_800C0294
    if (ctx->r11 != 0) {
        // 0x800C01A4: lb          $v0, 0x19($s0)
        ctx->r2 = MEM_B(ctx->r16, 0X19);
            goto L_800C0294;
    }
    goto skip_1;
    // 0x800C01A4: lb          $v0, 0x19($s0)
    ctx->r2 = MEM_B(ctx->r16, 0X19);
    skip_1:
    // 0x800C01A8: lb          $v0, 0x19($s0)
    ctx->r2 = MEM_B(ctx->r16, 0X19);
    // 0x800C01AC: lb          $v1, 0x1A($s0)
    ctx->r3 = MEM_B(ctx->r16, 0X1A);
    // 0x800C01B0: slt         $at, $v0, $v1
    ctx->r1 = SIGNED(ctx->r2) < SIGNED(ctx->r3) ? 1 : 0;
    // 0x800C01B4: beql        $at, $zero, L_800C0228
    if (ctx->r1 == 0) {
        // 0x800C01B8: slt         $at, $v1, $v0
        ctx->r1 = SIGNED(ctx->r3) < SIGNED(ctx->r2) ? 1 : 0;
            goto L_800C0228;
    }
    goto skip_2;
    // 0x800C01B8: slt         $at, $v1, $v0
    ctx->r1 = SIGNED(ctx->r3) < SIGNED(ctx->r2) ? 1 : 0;
    skip_2:
    // 0x800C01BC: jal         0x800C1EB8
    // 0x800C01C0: addiu       $a0, $zero, 0xC
    ctx->r4 = ADD32(0, 0XC);
    func_800C1EB8(rdram, ctx);
        goto after_1;
    // 0x800C01C0: addiu       $a0, $zero, 0xC
    ctx->r4 = ADD32(0, 0XC);
    after_1:
    // 0x800C01C4: lui         $v0, 0x8004
    ctx->r2 = S32(0X8004 << 16);
    // 0x800C01C8: lw          $v0, 0x562C($v0)
    ctx->r2 = MEM_W(ctx->r2, 0X562C);
    // 0x800C01CC: addiu       $at, $zero, 0x30
    ctx->r1 = ADD32(0, 0X30);
    // 0x800C01D0: addiu       $a1, $zero, 0x14
    ctx->r5 = ADD32(0, 0X14);
    // 0x800C01D4: andi        $t4, $v0, 0x30
    ctx->r12 = ctx->r2 & 0X30;
    // 0x800C01D8: bne         $t4, $at, L_800C0204
    if (ctx->r12 != ctx->r1) {
        // 0x800C01DC: andi        $a0, $v0, 0x3
        ctx->r4 = ctx->r2 & 0X3;
            goto L_800C0204;
    }
    // 0x800C01DC: andi        $a0, $v0, 0x3
    ctx->r4 = ctx->r2 & 0X3;
    // 0x800C01E0: lb          $t5, 0x19($s0)
    ctx->r13 = MEM_B(ctx->r16, 0X19);
    // 0x800C01E4: addiu       $t6, $zero, 0x49
    ctx->r14 = ADD32(0, 0X49);
    // 0x800C01E8: addiu       $a1, $zero, 0x14
    ctx->r5 = ADD32(0, 0X14);
    // 0x800C01EC: addiu       $a2, $zero, 0x46
    ctx->r6 = ADD32(0, 0X46);
    // 0x800C01F0: addiu       $a3, $zero, 0x1E
    ctx->r7 = ADD32(0, 0X1E);
    // 0x800C01F4: jal         0x800C33C8
    // 0x800C01F8: subu        $a0, $t6, $t5
    ctx->r4 = SUB32(ctx->r14, ctx->r13);
    func_800C33C8(rdram, ctx);
        goto after_2;
    // 0x800C01F8: subu        $a0, $t6, $t5
    ctx->r4 = SUB32(ctx->r14, ctx->r13);
    after_2:
    // 0x800C01FC: b           L_800C0218
    // 0x800C0200: addiu       $t7, $zero, 0x64
    ctx->r15 = ADD32(0, 0X64);
        goto L_800C0218;
    // 0x800C0200: addiu       $t7, $zero, 0x64
    ctx->r15 = ADD32(0, 0X64);
L_800C0204:
    // 0x800C0204: addiu       $a0, $a0, 0x42
    ctx->r4 = ADD32(ctx->r4, 0X42);
    // 0x800C0208: addiu       $a2, $zero, 0x46
    ctx->r6 = ADD32(0, 0X46);
    // 0x800C020C: jal         0x800C33C8
    // 0x800C0210: addiu       $a3, $zero, 0x1E
    ctx->r7 = ADD32(0, 0X1E);
    func_800C33C8(rdram, ctx);
        goto after_3;
    // 0x800C0210: addiu       $a3, $zero, 0x1E
    ctx->r7 = ADD32(0, 0X1E);
    after_3:
    // 0x800C0214: addiu       $t7, $zero, 0x64
    ctx->r15 = ADD32(0, 0X64);
L_800C0218:
    // 0x800C0218: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x800C021C: b           L_800C0290
    // 0x800C0220: sw          $t7, 0x7CE8($at)
    MEM_W(0X7CE8, ctx->r1) = ctx->r15;
        goto L_800C0290;
    // 0x800C0220: sw          $t7, 0x7CE8($at)
    MEM_W(0X7CE8, ctx->r1) = ctx->r15;
    // 0x800C0224: slt         $at, $v1, $v0
    ctx->r1 = SIGNED(ctx->r3) < SIGNED(ctx->r2) ? 1 : 0;
L_800C0228:
    // 0x800C0228: beql        $at, $zero, L_800C0294
    if (ctx->r1 == 0) {
        // 0x800C022C: lb          $v0, 0x19($s0)
        ctx->r2 = MEM_B(ctx->r16, 0X19);
            goto L_800C0294;
    }
    goto skip_3;
    // 0x800C022C: lb          $v0, 0x19($s0)
    ctx->r2 = MEM_B(ctx->r16, 0X19);
    skip_3:
    // 0x800C0230: jal         0x800C1EB8
    // 0x800C0234: addiu       $a0, $zero, 0xD
    ctx->r4 = ADD32(0, 0XD);
    func_800C1EB8(rdram, ctx);
        goto after_4;
    // 0x800C0234: addiu       $a0, $zero, 0xD
    ctx->r4 = ADD32(0, 0XD);
    after_4:
    // 0x800C0238: lui         $v0, 0x8004
    ctx->r2 = S32(0X8004 << 16);
    // 0x800C023C: lw          $v0, 0x562C($v0)
    ctx->r2 = MEM_W(ctx->r2, 0X562C);
    // 0x800C0240: addiu       $at, $zero, 0x30
    ctx->r1 = ADD32(0, 0X30);
    // 0x800C0244: addiu       $a1, $zero, 0x14
    ctx->r5 = ADD32(0, 0X14);
    // 0x800C0248: andi        $t8, $v0, 0x30
    ctx->r24 = ctx->r2 & 0X30;
    // 0x800C024C: bne         $t8, $at, L_800C0274
    if (ctx->r24 != ctx->r1) {
        // 0x800C0250: andi        $a0, $v0, 0x1
        ctx->r4 = ctx->r2 & 0X1;
            goto L_800C0274;
    }
    // 0x800C0250: andi        $a0, $v0, 0x1
    ctx->r4 = ctx->r2 & 0X1;
    // 0x800C0254: lb          $a0, 0x19($s0)
    ctx->r4 = MEM_B(ctx->r16, 0X19);
    // 0x800C0258: addiu       $a1, $zero, 0x14
    ctx->r5 = ADD32(0, 0X14);
    // 0x800C025C: addiu       $a2, $zero, 0x3C
    ctx->r6 = ADD32(0, 0X3C);
    // 0x800C0260: addiu       $a3, $zero, 0x1E
    ctx->r7 = ADD32(0, 0X1E);
    // 0x800C0264: jal         0x800C33C8
    // 0x800C0268: addiu       $a0, $a0, 0x4C
    ctx->r4 = ADD32(ctx->r4, 0X4C);
    func_800C33C8(rdram, ctx);
        goto after_5;
    // 0x800C0268: addiu       $a0, $a0, 0x4C
    ctx->r4 = ADD32(ctx->r4, 0X4C);
    after_5:
    // 0x800C026C: b           L_800C0288
    // 0x800C0270: addiu       $t9, $zero, 0x64
    ctx->r25 = ADD32(0, 0X64);
        goto L_800C0288;
    // 0x800C0270: addiu       $t9, $zero, 0x64
    ctx->r25 = ADD32(0, 0X64);
L_800C0274:
    // 0x800C0274: addiu       $a0, $a0, 0x4B
    ctx->r4 = ADD32(ctx->r4, 0X4B);
    // 0x800C0278: addiu       $a2, $zero, 0x3C
    ctx->r6 = ADD32(0, 0X3C);
    // 0x800C027C: jal         0x800C33C8
    // 0x800C0280: addiu       $a3, $zero, 0x1E
    ctx->r7 = ADD32(0, 0X1E);
    func_800C33C8(rdram, ctx);
        goto after_6;
    // 0x800C0280: addiu       $a3, $zero, 0x1E
    ctx->r7 = ADD32(0, 0X1E);
    after_6:
    // 0x800C0284: addiu       $t9, $zero, 0x64
    ctx->r25 = ADD32(0, 0X64);
L_800C0288:
    // 0x800C0288: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x800C028C: sw          $t9, 0x7CE8($at)
    MEM_W(0X7CE8, ctx->r1) = ctx->r25;
L_800C0290:
    // 0x800C0290: lb          $v0, 0x19($s0)
    ctx->r2 = MEM_B(ctx->r16, 0X19);
L_800C0294:
    // 0x800C0294: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x800C0298: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x800C029C: sb          $v0, 0x1A($s0)
    MEM_B(0X1A, ctx->r16) = ctx->r2;
    // 0x800C02A0: lw          $v1, 0x7DC0($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X7DC0);
    // 0x800C02A4: b           L_800C02E0
    // 0x800C02A8: sw          $v0, 0x7DC8($at)
    MEM_W(0X7DC8, ctx->r1) = ctx->r2;
        goto L_800C02E0;
    // 0x800C02A8: sw          $v0, 0x7DC8($at)
    MEM_W(0X7DC8, ctx->r1) = ctx->r2;
L_800C02AC:
    // 0x800C02AC: bne         $v1, $at, L_800C02E0
    if (ctx->r3 != ctx->r1) {
        // 0x800C02B0: lb          $t3, 0x67($sp)
        ctx->r11 = MEM_B(ctx->r29, 0X67);
            goto L_800C02E0;
    }
    // 0x800C02B0: lb          $t3, 0x67($sp)
    ctx->r11 = MEM_B(ctx->r29, 0X67);
    // 0x800C02B4: bnel        $t3, $zero, L_800C02E4
    if (ctx->r11 != 0) {
        // 0x800C02B8: addiu       $t0, $zero, 0x3
        ctx->r8 = ADD32(0, 0X3);
            goto L_800C02E4;
    }
    goto skip_4;
    // 0x800C02B8: addiu       $t0, $zero, 0x3
    ctx->r8 = ADD32(0, 0X3);
    skip_4:
    // 0x800C02BC: lui         $t6, 0x801D
    ctx->r14 = S32(0X801D << 16);
    // 0x800C02C0: lb          $t6, 0x7DFA($t6)
    ctx->r14 = MEM_B(ctx->r14, 0X7DFA);
    // 0x800C02C4: lb          $t4, 0x19($s0)
    ctx->r12 = MEM_B(ctx->r16, 0X19);
    // 0x800C02C8: beql        $t4, $t6, L_800C02E4
    if (ctx->r12 == ctx->r14) {
        // 0x800C02CC: addiu       $t0, $zero, 0x3
        ctx->r8 = ADD32(0, 0X3);
            goto L_800C02E4;
    }
    goto skip_5;
    // 0x800C02CC: addiu       $t0, $zero, 0x3
    ctx->r8 = ADD32(0, 0X3);
    skip_5:
    // 0x800C02D0: jal         0x800C1EB8
    // 0x800C02D4: addiu       $a0, $zero, 0xC
    ctx->r4 = ADD32(0, 0XC);
    func_800C1EB8(rdram, ctx);
        goto after_7;
    // 0x800C02D4: addiu       $a0, $zero, 0xC
    ctx->r4 = ADD32(0, 0XC);
    after_7:
    // 0x800C02D8: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x800C02DC: lw          $v1, 0x7DC0($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X7DC0);
L_800C02E0:
    // 0x800C02E0: addiu       $t0, $zero, 0x3
    ctx->r8 = ADD32(0, 0X3);
L_800C02E4:
    // 0x800C02E4: beq         $t0, $v1, L_800C0304
    if (ctx->r8 == ctx->r3) {
        // 0x800C02E8: lui         $t1, 0x801D
        ctx->r9 = S32(0X801D << 16);
            goto L_800C0304;
    }
    // 0x800C02E8: lui         $t1, 0x801D
    ctx->r9 = S32(0X801D << 16);
    // 0x800C02EC: bnel        $v1, $zero, L_800C0310
    if (ctx->r3 != 0) {
        // 0x800C02F0: lb          $t7, 0x67($sp)
        ctx->r15 = MEM_B(ctx->r29, 0X67);
            goto L_800C0310;
    }
    goto skip_6;
    // 0x800C02F0: lb          $t7, 0x67($sp)
    ctx->r15 = MEM_B(ctx->r29, 0X67);
    skip_6:
    // 0x800C02F4: lui         $t5, 0x801D
    ctx->r13 = S32(0X801D << 16);
    // 0x800C02F8: lw          $t5, 0x7DC4($t5)
    ctx->r13 = MEM_W(ctx->r13, 0X7DC4);
    // 0x800C02FC: bnel        $t5, $zero, L_800C0310
    if (ctx->r13 != 0) {
        // 0x800C0300: lb          $t7, 0x67($sp)
        ctx->r15 = MEM_B(ctx->r29, 0X67);
            goto L_800C0310;
    }
    goto skip_7;
    // 0x800C0300: lb          $t7, 0x67($sp)
    ctx->r15 = MEM_B(ctx->r29, 0X67);
    skip_7:
L_800C0304:
    // 0x800C0304: sb          $t0, 0xE($s0)
    MEM_B(0XE, ctx->r16) = ctx->r8;
    // 0x800C0308: sb          $t0, 0x9($s0)
    MEM_B(0X9, ctx->r16) = ctx->r8;
    // 0x800C030C: lb          $t7, 0x67($sp)
    ctx->r15 = MEM_B(ctx->r29, 0X67);
L_800C0310:
    // 0x800C0310: bnel        $t7, $zero, L_800C0348
    if (ctx->r15 != 0) {
        // 0x800C0314: lb          $t6, 0x67($sp)
        ctx->r14 = MEM_B(ctx->r29, 0X67);
            goto L_800C0348;
    }
    goto skip_8;
    // 0x800C0314: lb          $t6, 0x67($sp)
    ctx->r14 = MEM_B(ctx->r29, 0X67);
    skip_8:
    // 0x800C0318: lb          $t8, 0x19($s0)
    ctx->r24 = MEM_B(ctx->r16, 0X19);
    // 0x800C031C: addiu       $t1, $t1, 0x7DF8
    ctx->r9 = ADD32(ctx->r9, 0X7DF8);
    // 0x800C0320: lb          $t3, 0x3($t1)
    ctx->r11 = MEM_B(ctx->r9, 0X3);
    // 0x800C0324: sb          $t8, 0x2($t1)
    MEM_B(0X2, ctx->r9) = ctx->r24;
    // 0x800C0328: lb          $t9, 0x2($t1)
    ctx->r25 = MEM_B(ctx->r9, 0X2);
    // 0x800C032C: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    // 0x800C0330: addiu       $t4, $zero, -0x1
    ctx->r12 = ADD32(0, -0X1);
    // 0x800C0334: beql        $t9, $t3, L_800C0384
    if (ctx->r25 == ctx->r11) {
        // 0x800C0338: lb          $t3, 0x15($s0)
        ctx->r11 = MEM_B(ctx->r16, 0X15);
            goto L_800C0384;
    }
    goto skip_9;
    // 0x800C0338: lb          $t3, 0x15($s0)
    ctx->r11 = MEM_B(ctx->r16, 0X15);
    skip_9:
    // 0x800C033C: b           L_800C0380
    // 0x800C0340: sb          $t4, 0x3($t1)
    MEM_B(0X3, ctx->r9) = ctx->r12;
        goto L_800C0380;
    // 0x800C0340: sb          $t4, 0x3($t1)
    MEM_B(0X3, ctx->r9) = ctx->r12;
    // 0x800C0344: lb          $t6, 0x67($sp)
    ctx->r14 = MEM_B(ctx->r29, 0X67);
L_800C0348:
    // 0x800C0348: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x800C034C: addiu       $a3, $zero, 0x3
    ctx->r7 = ADD32(0, 0X3);
    // 0x800C0350: bnel        $t6, $at, L_800C0384
    if (ctx->r14 != ctx->r1) {
        // 0x800C0354: lb          $t3, 0x15($s0)
        ctx->r11 = MEM_B(ctx->r16, 0X15);
            goto L_800C0384;
    }
    goto skip_10;
    // 0x800C0354: lb          $t3, 0x15($s0)
    ctx->r11 = MEM_B(ctx->r16, 0X15);
    skip_10:
    // 0x800C0358: lb          $t5, 0x19($s0)
    ctx->r13 = MEM_B(ctx->r16, 0X19);
    // 0x800C035C: lui         $t2, 0x801D
    ctx->r10 = S32(0X801D << 16);
    // 0x800C0360: addiu       $t2, $t2, 0x7E00
    ctx->r10 = ADD32(ctx->r10, 0X7E00);
    // 0x800C0364: sb          $t5, 0x2($t2)
    MEM_B(0X2, ctx->r10) = ctx->r13;
    // 0x800C0368: lb          $t7, 0x2($t2)
    ctx->r15 = MEM_B(ctx->r10, 0X2);
    // 0x800C036C: lb          $t8, 0x3($t2)
    ctx->r24 = MEM_B(ctx->r10, 0X3);
    // 0x800C0370: beql        $t7, $t8, L_800C0384
    if (ctx->r15 == ctx->r24) {
        // 0x800C0374: lb          $t3, 0x15($s0)
        ctx->r11 = MEM_B(ctx->r16, 0X15);
            goto L_800C0384;
    }
    goto skip_11;
    // 0x800C0374: lb          $t3, 0x15($s0)
    ctx->r11 = MEM_B(ctx->r16, 0X15);
    skip_11:
    // 0x800C0378: addiu       $t9, $zero, -0x1
    ctx->r25 = ADD32(0, -0X1);
    // 0x800C037C: sb          $t9, 0x3($t2)
    MEM_B(0X3, ctx->r10) = ctx->r25;
L_800C0380:
    // 0x800C0380: lb          $t3, 0x15($s0)
    ctx->r11 = MEM_B(ctx->r16, 0X15);
L_800C0384:
    // 0x800C0384: lui         $t1, 0x801D
    ctx->r9 = S32(0X801D << 16);
    // 0x800C0388: lui         $t2, 0x801D
    ctx->r10 = S32(0X801D << 16);
    // 0x800C038C: addiu       $t2, $t2, 0x7E00
    ctx->r10 = ADD32(ctx->r10, 0X7E00);
    // 0x800C0390: beq         $t3, $zero, L_800C039C
    if (ctx->r11 == 0) {
        // 0x800C0394: addiu       $t1, $t1, 0x7DF8
        ctx->r9 = ADD32(ctx->r9, 0X7DF8);
            goto L_800C039C;
    }
    // 0x800C0394: addiu       $t1, $t1, 0x7DF8
    ctx->r9 = ADD32(ctx->r9, 0X7DF8);
    // 0x800C0398: sb          $zero, 0x4($s0)
    MEM_B(0X4, ctx->r16) = 0;
L_800C039C:
    // 0x800C039C: lb          $t4, 0x0($s0)
    ctx->r12 = MEM_B(ctx->r16, 0X0);
    // 0x800C03A0: slti        $at, $t4, 0x1E
    ctx->r1 = SIGNED(ctx->r12) < 0X1E ? 1 : 0;
    // 0x800C03A4: beql        $at, $zero, L_800C03B8
    if (ctx->r1 == 0) {
        // 0x800C03A8: lb          $v0, 0x8($s0)
        ctx->r2 = MEM_B(ctx->r16, 0X8);
            goto L_800C03B8;
    }
    goto skip_12;
    // 0x800C03A8: lb          $v0, 0x8($s0)
    ctx->r2 = MEM_B(ctx->r16, 0X8);
    skip_12:
    // 0x800C03AC: addiu       $t6, $zero, 0x46
    ctx->r14 = ADD32(0, 0X46);
    // 0x800C03B0: sb          $t6, 0x8($s0)
    MEM_B(0X8, ctx->r16) = ctx->r14;
    // 0x800C03B4: lb          $v0, 0x8($s0)
    ctx->r2 = MEM_B(ctx->r16, 0X8);
L_800C03B8:
    // 0x800C03B8: lb          $v1, 0x1($s0)
    ctx->r3 = MEM_B(ctx->r16, 0X1);
    // 0x800C03BC: slt         $at, $v0, $v1
    ctx->r1 = SIGNED(ctx->r2) < SIGNED(ctx->r3) ? 1 : 0;
    // 0x800C03C0: beql        $at, $zero, L_800C03DC
    if (ctx->r1 == 0) {
        // 0x800C03C4: slt         $at, $v1, $v0
        ctx->r1 = SIGNED(ctx->r3) < SIGNED(ctx->r2) ? 1 : 0;
            goto L_800C03DC;
    }
    goto skip_13;
    // 0x800C03C4: slt         $at, $v1, $v0
    ctx->r1 = SIGNED(ctx->r3) < SIGNED(ctx->r2) ? 1 : 0;
    skip_13:
    // 0x800C03C8: addiu       $t5, $v0, 0x1
    ctx->r13 = ADD32(ctx->r2, 0X1);
    // 0x800C03CC: sb          $t5, 0x8($s0)
    MEM_B(0X8, ctx->r16) = ctx->r13;
    // 0x800C03D0: b           L_800C03F0
    // 0x800C03D4: lb          $v0, 0x8($s0)
    ctx->r2 = MEM_B(ctx->r16, 0X8);
        goto L_800C03F0;
    // 0x800C03D4: lb          $v0, 0x8($s0)
    ctx->r2 = MEM_B(ctx->r16, 0X8);
    // 0x800C03D8: slt         $at, $v1, $v0
    ctx->r1 = SIGNED(ctx->r3) < SIGNED(ctx->r2) ? 1 : 0;
L_800C03DC:
    // 0x800C03DC: beq         $at, $zero, L_800C03F0
    if (ctx->r1 == 0) {
        // 0x800C03E0: nop
    
            goto L_800C03F0;
    }
    // 0x800C03E0: nop

    // 0x800C03E4: addiu       $t7, $v0, -0x1
    ctx->r15 = ADD32(ctx->r2, -0X1);
    // 0x800C03E8: sb          $t7, 0x8($s0)
    MEM_B(0X8, ctx->r16) = ctx->r15;
    // 0x800C03EC: lb          $v0, 0x8($s0)
    ctx->r2 = MEM_B(ctx->r16, 0X8);
L_800C03F0:
    // 0x800C03F0: div         $zero, $v0, $t0
    lo = S32(S64(S32(ctx->r2)) / S64(S32(ctx->r8))); hi = S32(S64(S32(ctx->r2)) % S64(S32(ctx->r8)));
    // 0x800C03F4: mflo        $t8
    ctx->r24 = lo;
    // 0x800C03F8: addiu       $t9, $t8, 0x60
    ctx->r25 = ADD32(ctx->r24, 0X60);
    // 0x800C03FC: sw          $t9, 0x58($sp)
    MEM_W(0X58, ctx->r29) = ctx->r25;
    // 0x800C0400: lb          $t3, 0x0($s0)
    ctx->r11 = MEM_B(ctx->r16, 0X0);
    // 0x800C0404: bne         $t0, $zero, L_800C0410
    if (ctx->r8 != 0) {
        // 0x800C0408: nop
    
            goto L_800C0410;
    }
    // 0x800C0408: nop

    // 0x800C040C: break       7
    do_break(2148271116);
L_800C0410:
    // 0x800C0410: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x800C0414: bne         $t0, $at, L_800C0428
    if (ctx->r8 != ctx->r1) {
        // 0x800C0418: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_800C0428;
    }
    // 0x800C0418: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x800C041C: bne         $v0, $at, L_800C0428
    if (ctx->r2 != ctx->r1) {
        // 0x800C0420: nop
    
            goto L_800C0428;
    }
    // 0x800C0420: nop

    // 0x800C0424: break       6
    do_break(2148271140);
L_800C0428:
    // 0x800C0428: sw          $t3, 0x5C($sp)
    MEM_W(0X5C, ctx->r29) = ctx->r11;
    // 0x800C042C: lb          $v1, 0x7($s0)
    ctx->r3 = MEM_B(ctx->r16, 0X7);
    // 0x800C0430: beq         $v1, $zero, L_800C0444
    if (ctx->r3 == 0) {
        // 0x800C0434: nop
    
            goto L_800C0444;
    }
    // 0x800C0434: nop

    // 0x800C0438: sh          $zero, 0xA($s0)
    MEM_H(0XA, ctx->r16) = 0;
    // 0x800C043C: b           L_800C0474
    // 0x800C0440: lb          $v1, 0x7($s0)
    ctx->r3 = MEM_B(ctx->r16, 0X7);
        goto L_800C0474;
    // 0x800C0440: lb          $v1, 0x7($s0)
    ctx->r3 = MEM_B(ctx->r16, 0X7);
L_800C0444:
    // 0x800C0444: lui         $t4, 0x801D
    ctx->r12 = S32(0X801D << 16);
    // 0x800C0448: lw          $t4, 0x7DC0($t4)
    ctx->r12 = MEM_W(ctx->r12, 0X7DC0);
    // 0x800C044C: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x800C0450: lb          $t6, 0x67($sp)
    ctx->r14 = MEM_B(ctx->r29, 0X67);
    // 0x800C0454: beq         $t4, $at, L_800C0474
    if (ctx->r12 == ctx->r1) {
        // 0x800C0458: slti        $at, $t6, 0x2
        ctx->r1 = SIGNED(ctx->r14) < 0X2 ? 1 : 0;
            goto L_800C0474;
    }
    // 0x800C0458: slti        $at, $t6, 0x2
    ctx->r1 = SIGNED(ctx->r14) < 0X2 ? 1 : 0;
    // 0x800C045C: beql        $at, $zero, L_800C0478
    if (ctx->r1 == 0) {
        // 0x800C0460: lb          $v0, 0x3($s0)
        ctx->r2 = MEM_B(ctx->r16, 0X3);
            goto L_800C0478;
    }
    goto skip_14;
    // 0x800C0460: lb          $v0, 0x3($s0)
    ctx->r2 = MEM_B(ctx->r16, 0X3);
    skip_14:
    // 0x800C0464: lh          $t5, 0xA($s0)
    ctx->r13 = MEM_H(ctx->r16, 0XA);
    // 0x800C0468: lb          $v1, 0x7($s0)
    ctx->r3 = MEM_B(ctx->r16, 0X7);
    // 0x800C046C: addiu       $t7, $t5, 0x1
    ctx->r15 = ADD32(ctx->r13, 0X1);
    // 0x800C0470: sh          $t7, 0xA($s0)
    MEM_H(0XA, ctx->r16) = ctx->r15;
L_800C0474:
    // 0x800C0474: lb          $v0, 0x3($s0)
    ctx->r2 = MEM_B(ctx->r16, 0X3);
L_800C0478:
    // 0x800C0478: beql        $v1, $v0, L_800C05C4
    if (ctx->r3 == ctx->r2) {
        // 0x800C047C: lb          $t4, 0xF($s0)
        ctx->r12 = MEM_B(ctx->r16, 0XF);
            goto L_800C05C4;
    }
    goto skip_15;
    // 0x800C047C: lb          $t4, 0xF($s0)
    ctx->r12 = MEM_B(ctx->r16, 0XF);
    skip_15:
    // 0x800C0480: beq         $v0, $zero, L_800C05B4
    if (ctx->r2 == 0) {
        // 0x800C0484: or          $v1, $zero, $zero
        ctx->r3 = 0 | 0;
            goto L_800C05B4;
    }
    // 0x800C0484: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
    // 0x800C0488: slti        $at, $v0, 0x65
    ctx->r1 = SIGNED(ctx->r2) < 0X65 ? 1 : 0;
    // 0x800C048C: bne         $at, $zero, L_800C04CC
    if (ctx->r1 != 0) {
        // 0x800C0490: addiu       $a0, $a3, 0x2
        ctx->r4 = ADD32(ctx->r7, 0X2);
            goto L_800C04CC;
    }
    // 0x800C0490: addiu       $a0, $a3, 0x2
    ctx->r4 = ADD32(ctx->r7, 0X2);
    // 0x800C0494: andi        $t8, $a0, 0xFF
    ctx->r24 = ctx->r4 & 0XFF;
    // 0x800C0498: or          $a0, $t8, $zero
    ctx->r4 = ctx->r24 | 0;
    // 0x800C049C: addiu       $a1, $zero, 0xB
    ctx->r5 = ADD32(0, 0XB);
    // 0x800C04A0: bgez        $v0, L_800C04B0
    if (SIGNED(ctx->r2) >= 0) {
        // 0x800C04A4: sra         $a2, $v0, 1
        ctx->r6 = S32(SIGNED(ctx->r2) >> 1);
            goto L_800C04B0;
    }
    // 0x800C04A4: sra         $a2, $v0, 1
    ctx->r6 = S32(SIGNED(ctx->r2) >> 1);
    // 0x800C04A8: addiu       $at, $v0, 0x1
    ctx->r1 = ADD32(ctx->r2, 0X1);
    // 0x800C04AC: sra         $a2, $at, 1
    ctx->r6 = S32(SIGNED(ctx->r1) >> 1);
L_800C04B0:
    // 0x800C04B0: addiu       $a2, $a2, 0x3C
    ctx->r6 = ADD32(ctx->r6, 0X3C);
    // 0x800C04B4: andi        $t9, $a2, 0xFF
    ctx->r25 = ctx->r6 & 0XFF;
    // 0x800C04B8: or          $a2, $t9, $zero
    ctx->r6 = ctx->r25 | 0;
    // 0x800C04BC: jal         0x800BFFEC
    // 0x800C04C0: sb          $a3, 0x57($sp)
    MEM_B(0X57, ctx->r29) = ctx->r7;
    func_800BFFEC(rdram, ctx);
        goto after_8;
    // 0x800C04C0: sb          $a3, 0x57($sp)
    MEM_B(0X57, ctx->r29) = ctx->r7;
    after_8:
    // 0x800C04C4: b           L_800C059C
    // 0x800C04C8: lbu         $a3, 0x57($sp)
    ctx->r7 = MEM_BU(ctx->r29, 0X57);
        goto L_800C059C;
    // 0x800C04C8: lbu         $a3, 0x57($sp)
    ctx->r7 = MEM_BU(ctx->r29, 0X57);
L_800C04CC:
    // 0x800C04CC: slti        $at, $v0, 0x51
    ctx->r1 = SIGNED(ctx->r2) < 0X51 ? 1 : 0;
    // 0x800C04D0: bne         $at, $zero, L_800C0510
    if (ctx->r1 != 0) {
        // 0x800C04D4: addiu       $a0, $a3, 0x2
        ctx->r4 = ADD32(ctx->r7, 0X2);
            goto L_800C0510;
    }
    // 0x800C04D4: addiu       $a0, $a3, 0x2
    ctx->r4 = ADD32(ctx->r7, 0X2);
    // 0x800C04D8: andi        $t3, $a0, 0xFF
    ctx->r11 = ctx->r4 & 0XFF;
    // 0x800C04DC: or          $a0, $t3, $zero
    ctx->r4 = ctx->r11 | 0;
    // 0x800C04E0: addiu       $a1, $zero, 0xC
    ctx->r5 = ADD32(0, 0XC);
    // 0x800C04E4: bgez        $v0, L_800C04F4
    if (SIGNED(ctx->r2) >= 0) {
        // 0x800C04E8: sra         $a2, $v0, 1
        ctx->r6 = S32(SIGNED(ctx->r2) >> 1);
            goto L_800C04F4;
    }
    // 0x800C04E8: sra         $a2, $v0, 1
    ctx->r6 = S32(SIGNED(ctx->r2) >> 1);
    // 0x800C04EC: addiu       $at, $v0, 0x1
    ctx->r1 = ADD32(ctx->r2, 0X1);
    // 0x800C04F0: sra         $a2, $at, 1
    ctx->r6 = S32(SIGNED(ctx->r1) >> 1);
L_800C04F4:
    // 0x800C04F4: addiu       $a2, $a2, 0x4B
    ctx->r6 = ADD32(ctx->r6, 0X4B);
    // 0x800C04F8: andi        $t4, $a2, 0xFF
    ctx->r12 = ctx->r6 & 0XFF;
    // 0x800C04FC: or          $a2, $t4, $zero
    ctx->r6 = ctx->r12 | 0;
    // 0x800C0500: jal         0x800BFFEC
    // 0x800C0504: sb          $a3, 0x57($sp)
    MEM_B(0X57, ctx->r29) = ctx->r7;
    func_800BFFEC(rdram, ctx);
        goto after_9;
    // 0x800C0504: sb          $a3, 0x57($sp)
    MEM_B(0X57, ctx->r29) = ctx->r7;
    after_9:
    // 0x800C0508: b           L_800C059C
    // 0x800C050C: lbu         $a3, 0x57($sp)
    ctx->r7 = MEM_BU(ctx->r29, 0X57);
        goto L_800C059C;
    // 0x800C050C: lbu         $a3, 0x57($sp)
    ctx->r7 = MEM_BU(ctx->r29, 0X57);
L_800C0510:
    // 0x800C0510: slti        $at, $v0, 0x29
    ctx->r1 = SIGNED(ctx->r2) < 0X29 ? 1 : 0;
    // 0x800C0514: beq         $at, $zero, L_800C0534
    if (ctx->r1 == 0) {
        // 0x800C0518: addiu       $a0, $a3, 0x2
        ctx->r4 = ADD32(ctx->r7, 0X2);
            goto L_800C0534;
    }
    // 0x800C0518: addiu       $a0, $a3, 0x2
    ctx->r4 = ADD32(ctx->r7, 0X2);
    // 0x800C051C: slti        $at, $v0, 0xB
    ctx->r1 = SIGNED(ctx->r2) < 0XB ? 1 : 0;
    // 0x800C0520: bnel        $at, $zero, L_800C0570
    if (ctx->r1 != 0) {
        // 0x800C0524: slti        $at, $v0, 0xB
        ctx->r1 = SIGNED(ctx->r2) < 0XB ? 1 : 0;
            goto L_800C0570;
    }
    goto skip_16;
    // 0x800C0524: slti        $at, $v0, 0xB
    ctx->r1 = SIGNED(ctx->r2) < 0XB ? 1 : 0;
    skip_16:
    // 0x800C0528: lb          $t6, 0x1F($s0)
    ctx->r14 = MEM_B(ctx->r16, 0X1F);
    // 0x800C052C: slti        $at, $t6, 0x1F
    ctx->r1 = SIGNED(ctx->r14) < 0X1F ? 1 : 0;
    // 0x800C0530: bne         $at, $zero, L_800C056C
    if (ctx->r1 != 0) {
        // 0x800C0534: andi        $t5, $a0, 0xFF
        ctx->r13 = ctx->r4 & 0XFF;
            goto L_800C056C;
    }
L_800C0534:
    // 0x800C0534: andi        $t5, $a0, 0xFF
    ctx->r13 = ctx->r4 & 0XFF;
    // 0x800C0538: or          $a0, $t5, $zero
    ctx->r4 = ctx->r13 | 0;
    // 0x800C053C: addiu       $a1, $zero, 0xD
    ctx->r5 = ADD32(0, 0XD);
    // 0x800C0540: bgez        $v0, L_800C0550
    if (SIGNED(ctx->r2) >= 0) {
        // 0x800C0544: sra         $a2, $v0, 1
        ctx->r6 = S32(SIGNED(ctx->r2) >> 1);
            goto L_800C0550;
    }
    // 0x800C0544: sra         $a2, $v0, 1
    ctx->r6 = S32(SIGNED(ctx->r2) >> 1);
    // 0x800C0548: addiu       $at, $v0, 0x1
    ctx->r1 = ADD32(ctx->r2, 0X1);
    // 0x800C054C: sra         $a2, $at, 1
    ctx->r6 = S32(SIGNED(ctx->r1) >> 1);
L_800C0550:
    // 0x800C0550: addiu       $a2, $a2, 0x56
    ctx->r6 = ADD32(ctx->r6, 0X56);
    // 0x800C0554: andi        $t7, $a2, 0xFF
    ctx->r15 = ctx->r6 & 0XFF;
    // 0x800C0558: or          $a2, $t7, $zero
    ctx->r6 = ctx->r15 | 0;
    // 0x800C055C: jal         0x800BFFEC
    // 0x800C0560: sb          $a3, 0x57($sp)
    MEM_B(0X57, ctx->r29) = ctx->r7;
    func_800BFFEC(rdram, ctx);
        goto after_10;
    // 0x800C0560: sb          $a3, 0x57($sp)
    MEM_B(0X57, ctx->r29) = ctx->r7;
    after_10:
    // 0x800C0564: b           L_800C059C
    // 0x800C0568: lbu         $a3, 0x57($sp)
    ctx->r7 = MEM_BU(ctx->r29, 0X57);
        goto L_800C059C;
    // 0x800C0568: lbu         $a3, 0x57($sp)
    ctx->r7 = MEM_BU(ctx->r29, 0X57);
L_800C056C:
    // 0x800C056C: slti        $at, $v0, 0xB
    ctx->r1 = SIGNED(ctx->r2) < 0XB ? 1 : 0;
L_800C0570:
    // 0x800C0570: bne         $at, $zero, L_800C059C
    if (ctx->r1 != 0) {
        // 0x800C0574: addiu       $a0, $a3, 0x2
        ctx->r4 = ADD32(ctx->r7, 0X2);
            goto L_800C059C;
    }
    // 0x800C0574: addiu       $a0, $a3, 0x2
    ctx->r4 = ADD32(ctx->r7, 0X2);
    // 0x800C0578: addiu       $a2, $v0, 0x50
    ctx->r6 = ADD32(ctx->r2, 0X50);
    // 0x800C057C: andi        $t9, $a2, 0xFF
    ctx->r25 = ctx->r6 & 0XFF;
    // 0x800C0580: andi        $t8, $a0, 0xFF
    ctx->r24 = ctx->r4 & 0XFF;
    // 0x800C0584: or          $a0, $t8, $zero
    ctx->r4 = ctx->r24 | 0;
    // 0x800C0588: or          $a2, $t9, $zero
    ctx->r6 = ctx->r25 | 0;
    // 0x800C058C: addiu       $a1, $zero, 0xE
    ctx->r5 = ADD32(0, 0XE);
    // 0x800C0590: jal         0x800BFFEC
    // 0x800C0594: sb          $a3, 0x57($sp)
    MEM_B(0X57, ctx->r29) = ctx->r7;
    func_800BFFEC(rdram, ctx);
        goto after_11;
    // 0x800C0594: sb          $a3, 0x57($sp)
    MEM_B(0X57, ctx->r29) = ctx->r7;
    after_11:
    // 0x800C0598: lbu         $a3, 0x57($sp)
    ctx->r7 = MEM_BU(ctx->r29, 0X57);
L_800C059C:
    // 0x800C059C: addiu       $t3, $zero, 0x1
    ctx->r11 = ADD32(0, 0X1);
    // 0x800C05A0: sb          $t3, 0x3($s0)
    MEM_B(0X3, ctx->r16) = ctx->r11;
    // 0x800C05A4: sw          $a3, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r7;
    // 0x800C05A8: addiu       $v1, $zero, 0xFF
    ctx->r3 = ADD32(0, 0XFF);
    // 0x800C05AC: b           L_800C05B8
    // 0x800C05B0: lb          $v0, 0x3($s0)
    ctx->r2 = MEM_B(ctx->r16, 0X3);
        goto L_800C05B8;
    // 0x800C05B0: lb          $v0, 0x3($s0)
    ctx->r2 = MEM_B(ctx->r16, 0X3);
L_800C05B4:
    // 0x800C05B4: sw          $a3, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r7;
L_800C05B8:
    // 0x800C05B8: b           L_800C05E0
    // 0x800C05BC: sb          $v0, 0x7($s0)
    MEM_B(0X7, ctx->r16) = ctx->r2;
        goto L_800C05E0;
    // 0x800C05BC: sb          $v0, 0x7($s0)
    MEM_B(0X7, ctx->r16) = ctx->r2;
    // 0x800C05C0: lb          $t4, 0xF($s0)
    ctx->r12 = MEM_B(ctx->r16, 0XF);
L_800C05C4:
    // 0x800C05C4: addiu       $t5, $zero, 0x7F
    ctx->r13 = ADD32(0, 0X7F);
    // 0x800C05C8: sw          $a3, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r7;
    // 0x800C05CC: bgez        $t4, L_800C05DC
    if (SIGNED(ctx->r12) >= 0) {
        // 0x800C05D0: sra         $t6, $t4, 2
        ctx->r14 = S32(SIGNED(ctx->r12) >> 2);
            goto L_800C05DC;
    }
    // 0x800C05D0: sra         $t6, $t4, 2
    ctx->r14 = S32(SIGNED(ctx->r12) >> 2);
    // 0x800C05D4: addiu       $at, $t4, 0x3
    ctx->r1 = ADD32(ctx->r12, 0X3);
    // 0x800C05D8: sra         $t6, $at, 2
    ctx->r14 = S32(SIGNED(ctx->r1) >> 2);
L_800C05DC:
    // 0x800C05DC: subu        $v1, $t5, $t6
    ctx->r3 = SUB32(ctx->r13, ctx->r14);
L_800C05E0:
    // 0x800C05E0: lw          $a0, 0x30($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X30);
    // 0x800C05E4: lui         $at, 0x600
    ctx->r1 = S32(0X600 << 16);
    // 0x800C05E8: sll         $a1, $v1, 24
    ctx->r5 = S32(ctx->r3 << 24);
    // 0x800C05EC: andi        $t7, $a0, 0xFF
    ctx->r15 = ctx->r4 & 0XFF;
    // 0x800C05F0: sll         $t8, $t7, 8
    ctx->r24 = S32(ctx->r15 << 8);
    // 0x800C05F4: or          $t9, $t8, $at
    ctx->r25 = ctx->r24 | ctx->r1;
    // 0x800C05F8: sra         $t4, $a1, 24
    ctx->r12 = S32(SIGNED(ctx->r5) >> 24);
    // 0x800C05FC: or          $a1, $t4, $zero
    ctx->r5 = ctx->r12 | 0;
    // 0x800C0600: jal         0x800C53D4
    // 0x800C0604: ori         $a0, $t9, 0x6
    ctx->r4 = ctx->r25 | 0X6;
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_12;
    // 0x800C0604: ori         $a0, $t9, 0x6
    ctx->r4 = ctx->r25 | 0X6;
    after_12:
    // 0x800C0608: lb          $t5, 0x7($s0)
    ctx->r13 = MEM_B(ctx->r16, 0X7);
    // 0x800C060C: bnel        $t5, $zero, L_800C0630
    if (ctx->r13 != 0) {
        // 0x800C0610: lb          $v0, 0x4($s0)
        ctx->r2 = MEM_B(ctx->r16, 0X4);
            goto L_800C0630;
    }
    goto skip_17;
    // 0x800C0610: lb          $v0, 0x4($s0)
    ctx->r2 = MEM_B(ctx->r16, 0X4);
    skip_17:
    // 0x800C0614: lw          $t6, 0x58($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X58);
    // 0x800C0618: lw          $t8, 0x5C($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X5C);
    // 0x800C061C: addiu       $t7, $t6, 0x10
    ctx->r15 = ADD32(ctx->r14, 0X10);
    // 0x800C0620: addiu       $t9, $t8, 0x20
    ctx->r25 = ADD32(ctx->r24, 0X20);
    // 0x800C0624: sw          $t7, 0x58($sp)
    MEM_W(0X58, ctx->r29) = ctx->r15;
    // 0x800C0628: sw          $t9, 0x5C($sp)
    MEM_W(0X5C, ctx->r29) = ctx->r25;
    // 0x800C062C: lb          $v0, 0x4($s0)
    ctx->r2 = MEM_B(ctx->r16, 0X4);
L_800C0630:
    // 0x800C0630: beql        $v0, $zero, L_800C0720
    if (ctx->r2 == 0) {
        // 0x800C0634: addiu       $t5, $zero, 0xFF
        ctx->r13 = ADD32(0, 0XFF);
            goto L_800C0720;
    }
    goto skip_18;
    // 0x800C0634: addiu       $t5, $zero, 0xFF
    ctx->r13 = ADD32(0, 0XFF);
    skip_18:
    // 0x800C0638: lb          $t3, 0x6($s0)
    ctx->r11 = MEM_B(ctx->r16, 0X6);
    // 0x800C063C: addiu       $t4, $zero, 0x4
    ctx->r12 = ADD32(0, 0X4);
    // 0x800C0640: bnel        $t3, $zero, L_800C06FC
    if (ctx->r11 != 0) {
        // 0x800C0644: lbu         $v1, 0x5($s0)
        ctx->r3 = MEM_BU(ctx->r16, 0X5);
            goto L_800C06FC;
    }
    goto skip_19;
    // 0x800C0644: lbu         $v1, 0x5($s0)
    ctx->r3 = MEM_BU(ctx->r16, 0X5);
    skip_19:
    // 0x800C0648: sb          $t4, 0x5($s0)
    MEM_B(0X5, ctx->r16) = ctx->r12;
    // 0x800C064C: lb          $t5, 0x67($sp)
    ctx->r13 = MEM_B(ctx->r29, 0X67);
    // 0x800C0650: slti        $at, $t5, 0x2
    ctx->r1 = SIGNED(ctx->r13) < 0X2 ? 1 : 0;
    // 0x800C0654: beq         $at, $zero, L_800C06F0
    if (ctx->r1 == 0) {
        // 0x800C0658: nop
    
            goto L_800C06F0;
    }
    // 0x800C0658: nop

    // 0x800C065C: lb          $v0, 0x0($s0)
    ctx->r2 = MEM_B(ctx->r16, 0X0);
    // 0x800C0660: lui         $t6, 0x800E
    ctx->r14 = S32(0X800E << 16);
    // 0x800C0664: bne         $v0, $zero, L_800C06C4
    if (ctx->r2 != 0) {
        // 0x800C0668: slti        $at, $v0, 0x1E
        ctx->r1 = SIGNED(ctx->r2) < 0X1E ? 1 : 0;
            goto L_800C06C4;
    }
    // 0x800C0668: slti        $at, $v0, 0x1E
    ctx->r1 = SIGNED(ctx->r2) < 0X1E ? 1 : 0;
    // 0x800C066C: lw          $t6, 0x7CA0($t6)
    ctx->r14 = MEM_W(ctx->r14, 0X7CA0);
    // 0x800C0670: lui         $t7, 0x800E
    ctx->r15 = S32(0X800E << 16);
    // 0x800C0674: bne         $t6, $zero, L_800C06C4
    if (ctx->r14 != 0) {
        // 0x800C0678: nop
    
            goto L_800C06C4;
    }
    // 0x800C0678: nop

    // 0x800C067C: lw          $t7, 0x7CAC($t7)
    ctx->r15 = MEM_W(ctx->r15, 0X7CAC);
    // 0x800C0680: lw          $a0, 0x30($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X30);
    // 0x800C0684: addiu       $a1, $zero, 0xF
    ctx->r5 = ADD32(0, 0XF);
    // 0x800C0688: bne         $t7, $zero, L_800C06C4
    if (ctx->r15 != 0) {
        // 0x800C068C: addiu       $a0, $a0, 0x2
        ctx->r4 = ADD32(ctx->r4, 0X2);
            goto L_800C06C4;
    }
    // 0x800C068C: addiu       $a0, $a0, 0x2
    ctx->r4 = ADD32(ctx->r4, 0X2);
    // 0x800C0690: andi        $t8, $a0, 0xFF
    ctx->r24 = ctx->r4 & 0XFF;
    // 0x800C0694: or          $a0, $t8, $zero
    ctx->r4 = ctx->r24 | 0;
    // 0x800C0698: jal         0x800BFFEC
    // 0x800C069C: addiu       $a2, $zero, 0x7F
    ctx->r6 = ADD32(0, 0X7F);
    func_800BFFEC(rdram, ctx);
        goto after_13;
    // 0x800C069C: addiu       $a2, $zero, 0x7F
    ctx->r6 = ADD32(0, 0X7F);
    after_13:
    // 0x800C06A0: lb          $t3, 0x67($sp)
    ctx->r11 = MEM_B(ctx->r29, 0X67);
    // 0x800C06A4: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x800C06A8: addiu       $t9, $zero, 0x1
    ctx->r25 = ADD32(0, 0X1);
    // 0x800C06AC: sll         $t4, $t3, 2
    ctx->r12 = S32(ctx->r11 << 2);
    // 0x800C06B0: addu        $at, $at, $t4
    ctx->r1 = ADD32(ctx->r1, ctx->r12);
    // 0x800C06B4: sw          $t9, 0x7DD8($at)
    MEM_W(0X7DD8, ctx->r1) = ctx->r25;
    // 0x800C06B8: addiu       $t5, $zero, 0x1D
    ctx->r13 = ADD32(0, 0X1D);
    // 0x800C06BC: b           L_800C06F0
    // 0x800C06C0: sb          $t5, 0x1D($s0)
    MEM_B(0X1D, ctx->r16) = ctx->r13;
        goto L_800C06F0;
    // 0x800C06C0: sb          $t5, 0x1D($s0)
    MEM_B(0X1D, ctx->r16) = ctx->r13;
L_800C06C4:
    // 0x800C06C4: beq         $at, $zero, L_800C06D4
    if (ctx->r1 == 0) {
        // 0x800C06C8: addiu       $t6, $zero, 0x14
        ctx->r14 = ADD32(0, 0X14);
            goto L_800C06D4;
    }
    // 0x800C06C8: addiu       $t6, $zero, 0x14
    ctx->r14 = ADD32(0, 0X14);
    // 0x800C06CC: b           L_800C06F0
    // 0x800C06D0: sb          $t6, 0x1D($s0)
    MEM_B(0X1D, ctx->r16) = ctx->r14;
        goto L_800C06F0;
    // 0x800C06D0: sb          $t6, 0x1D($s0)
    MEM_B(0X1D, ctx->r16) = ctx->r14;
L_800C06D4:
    // 0x800C06D4: slti        $at, $v0, 0x32
    ctx->r1 = SIGNED(ctx->r2) < 0X32 ? 1 : 0;
    // 0x800C06D8: beq         $at, $zero, L_800C06EC
    if (ctx->r1 == 0) {
        // 0x800C06DC: addiu       $t8, $zero, 0x4
        ctx->r24 = ADD32(0, 0X4);
            goto L_800C06EC;
    }
    // 0x800C06DC: addiu       $t8, $zero, 0x4
    ctx->r24 = ADD32(0, 0X4);
    // 0x800C06E0: addiu       $t7, $zero, 0x8
    ctx->r15 = ADD32(0, 0X8);
    // 0x800C06E4: b           L_800C06F0
    // 0x800C06E8: sb          $t7, 0x1D($s0)
    MEM_B(0X1D, ctx->r16) = ctx->r15;
        goto L_800C06F0;
    // 0x800C06E8: sb          $t7, 0x1D($s0)
    MEM_B(0X1D, ctx->r16) = ctx->r15;
L_800C06EC:
    // 0x800C06EC: sb          $t8, 0x1D($s0)
    MEM_B(0X1D, ctx->r16) = ctx->r24;
L_800C06F0:
    // 0x800C06F0: b           L_800C070C
    // 0x800C06F4: lb          $v0, 0x4($s0)
    ctx->r2 = MEM_B(ctx->r16, 0X4);
        goto L_800C070C;
    // 0x800C06F4: lb          $v0, 0x4($s0)
    ctx->r2 = MEM_B(ctx->r16, 0X4);
    // 0x800C06F8: lbu         $v1, 0x5($s0)
    ctx->r3 = MEM_BU(ctx->r16, 0X5);
L_800C06FC:
    // 0x800C06FC: beq         $v1, $zero, L_800C070C
    if (ctx->r3 == 0) {
        // 0x800C0700: addiu       $t3, $v1, -0x1
        ctx->r11 = ADD32(ctx->r3, -0X1);
            goto L_800C070C;
    }
    // 0x800C0700: addiu       $t3, $v1, -0x1
    ctx->r11 = ADD32(ctx->r3, -0X1);
    // 0x800C0704: sb          $t3, 0x5($s0)
    MEM_B(0X5, ctx->r16) = ctx->r11;
    // 0x800C0708: lb          $v0, 0x4($s0)
    ctx->r2 = MEM_B(ctx->r16, 0X4);
L_800C070C:
    // 0x800C070C: lb          $t9, 0x67($sp)
    ctx->r25 = MEM_B(ctx->r29, 0X67);
    // 0x800C0710: sll         $t4, $t9, 2
    ctx->r12 = S32(ctx->r25 << 2);
    // 0x800C0714: b           L_800C0734
    // 0x800C0718: sw          $t4, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r12;
        goto L_800C0734;
    // 0x800C0718: sw          $t4, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r12;
    // 0x800C071C: addiu       $t5, $zero, 0xFF
    ctx->r13 = ADD32(0, 0XFF);
L_800C0720:
    // 0x800C0720: sb          $t5, 0x5($s0)
    MEM_B(0X5, ctx->r16) = ctx->r13;
    // 0x800C0724: lb          $t6, 0x67($sp)
    ctx->r14 = MEM_B(ctx->r29, 0X67);
    // 0x800C0728: lb          $v0, 0x4($s0)
    ctx->r2 = MEM_B(ctx->r16, 0X4);
    // 0x800C072C: sll         $t7, $t6, 2
    ctx->r15 = S32(ctx->r14 << 2);
    // 0x800C0730: sw          $t7, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r15;
L_800C0734:
    // 0x800C0734: lb          $t8, 0x1C($s0)
    ctx->r24 = MEM_B(ctx->r16, 0X1C);
    // 0x800C0738: sb          $v0, 0x6($s0)
    MEM_B(0X6, ctx->r16) = ctx->r2;
    // 0x800C073C: beq         $t8, $zero, L_800C079C
    if (ctx->r24 == 0) {
        // 0x800C0740: lui         $t3, 0x800E
        ctx->r11 = S32(0X800E << 16);
            goto L_800C079C;
    }
    // 0x800C0740: lui         $t3, 0x800E
    ctx->r11 = S32(0X800E << 16);
    // 0x800C0744: lw          $t3, 0x7CAC($t3)
    ctx->r11 = MEM_W(ctx->r11, 0X7CAC);
    // 0x800C0748: lui         $a2, 0x8004
    ctx->r6 = S32(0X8004 << 16);
    // 0x800C074C: addiu       $a0, $zero, 0x5
    ctx->r4 = ADD32(0, 0X5);
    // 0x800C0750: bne         $t3, $zero, L_800C0790
    if (ctx->r11 != 0) {
        // 0x800C0754: addiu       $a1, $zero, 0xA
        ctx->r5 = ADD32(0, 0XA);
            goto L_800C0790;
    }
    // 0x800C0754: addiu       $a1, $zero, 0xA
    ctx->r5 = ADD32(0, 0XA);
    // 0x800C0758: lw          $a2, 0x562C($a2)
    ctx->r6 = MEM_W(ctx->r6, 0X562C);
    // 0x800C075C: lw          $a0, 0x30($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X30);
    // 0x800C0760: addiu       $a1, $zero, 0xF
    ctx->r5 = ADD32(0, 0XF);
    // 0x800C0764: andi        $t4, $a2, 0x1F
    ctx->r12 = ctx->r6 & 0X1F;
    // 0x800C0768: addiu       $a2, $t4, 0x60
    ctx->r6 = ADD32(ctx->r12, 0X60);
    // 0x800C076C: addiu       $a0, $a0, 0x2
    ctx->r4 = ADD32(ctx->r4, 0X2);
    // 0x800C0770: andi        $t9, $a0, 0xFF
    ctx->r25 = ctx->r4 & 0XFF;
    // 0x800C0774: andi        $t5, $a2, 0xFF
    ctx->r13 = ctx->r6 & 0XFF;
    // 0x800C0778: or          $a2, $t5, $zero
    ctx->r6 = ctx->r13 | 0;
    // 0x800C077C: jal         0x800BFFEC
    // 0x800C0780: or          $a0, $t9, $zero
    ctx->r4 = ctx->r25 | 0;
    func_800BFFEC(rdram, ctx);
        goto after_14;
    // 0x800C0780: or          $a0, $t9, $zero
    ctx->r4 = ctx->r25 | 0;
    after_14:
    // 0x800C0784: addiu       $t6, $zero, 0x1D
    ctx->r14 = ADD32(0, 0X1D);
    // 0x800C0788: b           L_800C0798
    // 0x800C078C: sb          $t6, 0x1D($s0)
    MEM_B(0X1D, ctx->r16) = ctx->r14;
        goto L_800C0798;
    // 0x800C078C: sb          $t6, 0x1D($s0)
    MEM_B(0X1D, ctx->r16) = ctx->r14;
L_800C0790:
    // 0x800C0790: jal         0x800BFFEC
    // 0x800C0794: addiu       $a2, $zero, 0x7F
    ctx->r6 = ADD32(0, 0X7F);
    func_800BFFEC(rdram, ctx);
        goto after_15;
    // 0x800C0794: addiu       $a2, $zero, 0x7F
    ctx->r6 = ADD32(0, 0X7F);
    after_15:
L_800C0798:
    // 0x800C0798: sb          $zero, 0x1C($s0)
    MEM_B(0X1C, ctx->r16) = 0;
L_800C079C:
    // 0x800C079C: lb          $t7, 0x67($sp)
    ctx->r15 = MEM_B(ctx->r29, 0X67);
    // 0x800C07A0: slti        $at, $t7, 0x2
    ctx->r1 = SIGNED(ctx->r15) < 0X2 ? 1 : 0;
    // 0x800C07A4: beql        $at, $zero, L_800C07E4
    if (ctx->r1 == 0) {
        // 0x800C07A8: lb          $t8, 0x4($s0)
        ctx->r24 = MEM_B(ctx->r16, 0X4);
            goto L_800C07E4;
    }
    goto skip_20;
    // 0x800C07A8: lb          $t8, 0x4($s0)
    ctx->r24 = MEM_B(ctx->r16, 0X4);
    skip_20:
    // 0x800C07AC: lb          $v0, 0x9($s0)
    ctx->r2 = MEM_B(ctx->r16, 0X9);
    // 0x800C07B0: beql        $v0, $zero, L_800C07C8
    if (ctx->r2 == 0) {
        // 0x800C07B4: lb          $a0, 0xE($s0)
        ctx->r4 = MEM_B(ctx->r16, 0XE);
            goto L_800C07C8;
    }
    goto skip_21;
    // 0x800C07B4: lb          $a0, 0xE($s0)
    ctx->r4 = MEM_B(ctx->r16, 0XE);
    skip_21:
    // 0x800C07B8: lb          $a0, 0xE($s0)
    ctx->r4 = MEM_B(ctx->r16, 0XE);
    // 0x800C07BC: beql        $a0, $zero, L_800C07E0
    if (ctx->r4 == 0) {
        // 0x800C07C0: sb          $a0, 0x9($s0)
        MEM_B(0X9, ctx->r16) = ctx->r4;
            goto L_800C07E0;
    }
    goto skip_22;
    // 0x800C07C0: sb          $a0, 0x9($s0)
    MEM_B(0X9, ctx->r16) = ctx->r4;
    skip_22:
    // 0x800C07C4: lb          $a0, 0xE($s0)
    ctx->r4 = MEM_B(ctx->r16, 0XE);
L_800C07C8:
    // 0x800C07C8: beql        $a0, $v0, L_800C07E0
    if (ctx->r4 == ctx->r2) {
        // 0x800C07CC: sb          $a0, 0x9($s0)
        MEM_B(0X9, ctx->r16) = ctx->r4;
            goto L_800C07E0;
    }
    goto skip_23;
    // 0x800C07CC: sb          $a0, 0x9($s0)
    MEM_B(0X9, ctx->r16) = ctx->r4;
    skip_23:
    // 0x800C07D0: jal         0x800C36F8
    // 0x800C07D4: nop

    func_800C36F8(rdram, ctx);
        goto after_16;
    // 0x800C07D4: nop

    after_16:
    // 0x800C07D8: lb          $a0, 0xE($s0)
    ctx->r4 = MEM_B(ctx->r16, 0XE);
    // 0x800C07DC: sb          $a0, 0x9($s0)
    MEM_B(0X9, ctx->r16) = ctx->r4;
L_800C07E0:
    // 0x800C07E0: lb          $t8, 0x4($s0)
    ctx->r24 = MEM_B(ctx->r16, 0X4);
L_800C07E4:
    // 0x800C07E4: lb          $t3, 0x67($sp)
    ctx->r11 = MEM_B(ctx->r29, 0X67);
    // 0x800C07E8: beql        $t8, $zero, L_800C0828
    if (ctx->r24 == 0) {
        // 0x800C07EC: mtc1        $zero, $f2
        ctx->f2.u32l = 0;
            goto L_800C0828;
    }
    goto skip_24;
    // 0x800C07EC: mtc1        $zero, $f2
    ctx->f2.u32l = 0;
    skip_24:
    // 0x800C07F0: lb          $a0, 0xE($s0)
    ctx->r4 = MEM_B(ctx->r16, 0XE);
    // 0x800C07F4: addiu       $at, $zero, 0x5
    ctx->r1 = ADD32(0, 0X5);
    // 0x800C07F8: bne         $a0, $at, L_800C0808
    if (ctx->r4 != ctx->r1) {
        // 0x800C07FC: lui         $at, 0x800F
        ctx->r1 = S32(0X800F << 16);
            goto L_800C0808;
    }
    // 0x800C07FC: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x800C0800: b           L_800C082C
    // 0x800C0804: lwc1        $f2, -0x3C94($at)
    ctx->f2.u32l = MEM_W(ctx->r1, -0X3C94);
        goto L_800C082C;
    // 0x800C0804: lwc1        $f2, -0x3C94($at)
    ctx->f2.u32l = MEM_W(ctx->r1, -0X3C94);
L_800C0808:
    // 0x800C0808: mtc1        $a0, $f4
    ctx->f4.u32l = ctx->r4;
    // 0x800C080C: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x800C0810: lwc1        $f8, -0x3C90($at)
    ctx->f8.u32l = MEM_W(ctx->r1, -0X3C90);
    // 0x800C0814: cvt.s.w     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
    // 0x800C0818: mul.s       $f2, $f6, $f8
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f2.fl = MUL_S(ctx->f6.fl, ctx->f8.fl);
    // 0x800C081C: b           L_800C082C
    // 0x800C0820: nop

        goto L_800C082C;
    // 0x800C0820: nop

    // 0x800C0824: mtc1        $zero, $f2
    ctx->f2.u32l = 0;
L_800C0828:
    // 0x800C0828: nop

L_800C082C:
    // 0x800C082C: bnel        $t3, $zero, L_800C0844
    if (ctx->r11 != 0) {
        // 0x800C0830: lb          $t4, 0x67($sp)
        ctx->r12 = MEM_B(ctx->r29, 0X67);
            goto L_800C0844;
    }
    goto skip_25;
    // 0x800C0830: lb          $t4, 0x67($sp)
    ctx->r12 = MEM_B(ctx->r29, 0X67);
    skip_25:
    // 0x800C0834: lb          $t9, 0xE($s0)
    ctx->r25 = MEM_B(ctx->r16, 0XE);
    // 0x800C0838: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x800C083C: sb          $t9, 0x7DFC($at)
    MEM_B(0X7DFC, ctx->r1) = ctx->r25;
    // 0x800C0840: lb          $t4, 0x67($sp)
    ctx->r12 = MEM_B(ctx->r29, 0X67);
L_800C0844:
    // 0x800C0844: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x800C0848: bnel        $t4, $at, L_800C0860
    if (ctx->r12 != ctx->r1) {
        // 0x800C084C: lw          $t6, 0x5C($sp)
        ctx->r14 = MEM_W(ctx->r29, 0X5C);
            goto L_800C0860;
    }
    goto skip_26;
    // 0x800C084C: lw          $t6, 0x5C($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X5C);
    skip_26:
    // 0x800C0850: lb          $t5, 0xE($s0)
    ctx->r13 = MEM_B(ctx->r16, 0XE);
    // 0x800C0854: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x800C0858: sb          $t5, 0x7E04($at)
    MEM_B(0X7E04, ctx->r1) = ctx->r13;
    // 0x800C085C: lw          $t6, 0x5C($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X5C);
L_800C0860:
    // 0x800C0860: bgezl       $t6, L_800C0870
    if (SIGNED(ctx->r14) >= 0) {
        // 0x800C0864: lw          $t7, 0x58($sp)
        ctx->r15 = MEM_W(ctx->r29, 0X58);
            goto L_800C0870;
    }
    goto skip_27;
    // 0x800C0864: lw          $t7, 0x58($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X58);
    skip_27:
    // 0x800C0868: sw          $zero, 0x5C($sp)
    MEM_W(0X5C, ctx->r29) = 0;
    // 0x800C086C: lw          $t7, 0x58($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X58);
L_800C0870:
    // 0x800C0870: lw          $a0, 0x5C($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X5C);
    // 0x800C0874: bgez        $t7, L_800C0880
    if (SIGNED(ctx->r15) >= 0) {
        // 0x800C0878: slti        $at, $a0, 0x64
        ctx->r1 = SIGNED(ctx->r4) < 0X64 ? 1 : 0;
            goto L_800C0880;
    }
    // 0x800C0878: slti        $at, $a0, 0x64
    ctx->r1 = SIGNED(ctx->r4) < 0X64 ? 1 : 0;
    // 0x800C087C: sw          $zero, 0x58($sp)
    MEM_W(0X58, ctx->r29) = 0;
L_800C0880:
    // 0x800C0880: bne         $at, $zero, L_800C088C
    if (ctx->r1 != 0) {
        // 0x800C0884: lw          $t8, 0x58($sp)
        ctx->r24 = MEM_W(ctx->r29, 0X58);
            goto L_800C088C;
    }
    // 0x800C0884: lw          $t8, 0x58($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X58);
    // 0x800C0888: addiu       $a0, $zero, 0x63
    ctx->r4 = ADD32(0, 0X63);
L_800C088C:
    // 0x800C088C: slti        $at, $t8, 0x80
    ctx->r1 = SIGNED(ctx->r24) < 0X80 ? 1 : 0;
    // 0x800C0890: bne         $at, $zero, L_800C089C
    if (ctx->r1 != 0) {
        // 0x800C0894: addiu       $t3, $zero, 0x7F
        ctx->r11 = ADD32(0, 0X7F);
            goto L_800C089C;
    }
    // 0x800C0894: addiu       $t3, $zero, 0x7F
    ctx->r11 = ADD32(0, 0X7F);
    // 0x800C0898: sw          $t3, 0x58($sp)
    MEM_W(0X58, ctx->r29) = ctx->r11;
L_800C089C:
    // 0x800C089C: lb          $v0, 0x1D($s0)
    ctx->r2 = MEM_B(ctx->r16, 0X1D);
    // 0x800C08A0: beq         $v0, $zero, L_800C0904
    if (ctx->r2 == 0) {
        // 0x800C08A4: negu        $t4, $v0
        ctx->r12 = SUB32(0, ctx->r2);
            goto L_800C0904;
    }
    // 0x800C08A4: negu        $t4, $v0
    ctx->r12 = SUB32(0, ctx->r2);
    // 0x800C08A8: lui         $t5, 0x800E
    ctx->r13 = S32(0X800E << 16);
    // 0x800C08AC: addu        $t5, $t5, $t4
    ctx->r13 = ADD32(ctx->r13, ctx->r12);
    // 0x800C08B0: lb          $t5, 0x7F75($t5)
    ctx->r13 = MEM_B(ctx->r13, 0X7F75);
    // 0x800C08B4: addiu       $t9, $zero, 0x7F
    ctx->r25 = ADD32(0, 0X7F);
    // 0x800C08B8: lui         $v1, 0x800E
    ctx->r3 = S32(0X800E << 16);
    // 0x800C08BC: sw          $t9, 0x58($sp)
    MEM_W(0X58, ctx->r29) = ctx->r25;
    // 0x800C08C0: addiu       $v1, $v1, 0x7DC8
    ctx->r3 = ADD32(ctx->r3, 0X7DC8);
    // 0x800C08C4: sll         $t9, $v0, 2
    ctx->r25 = S32(ctx->r2 << 2);
    // 0x800C08C8: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x800C08CC: sll         $t6, $t5, 2
    ctx->r14 = S32(ctx->r13 << 2);
    // 0x800C08D0: addu        $t7, $v1, $t6
    ctx->r15 = ADD32(ctx->r3, ctx->r14);
    // 0x800C08D4: addu        $at, $at, $t9
    ctx->r1 = ADD32(ctx->r1, ctx->r25);
    // 0x800C08D8: lwc1        $f0, 0x0($t7)
    ctx->f0.u32l = MEM_W(ctx->r15, 0X0);
    // 0x800C08DC: lwc1        $f16, 0x7F78($at)
    ctx->f16.u32l = MEM_W(ctx->r1, 0X7F78);
    // 0x800C08E0: sll         $t8, $a0, 2
    ctx->r24 = S32(ctx->r4 << 2);
    // 0x800C08E4: addu        $t3, $v1, $t8
    ctx->r11 = ADD32(ctx->r3, ctx->r24);
    // 0x800C08E8: mul.s       $f18, $f0, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f18.fl = MUL_S(ctx->f0.fl, ctx->f16.fl);
    // 0x800C08EC: lwc1        $f10, 0x0($t3)
    ctx->f10.u32l = MEM_W(ctx->r11, 0X0);
    // 0x800C08F0: addiu       $t4, $v0, -0x1
    ctx->r12 = ADD32(ctx->r2, -0X1);
    // 0x800C08F4: sb          $t4, 0x1D($s0)
    MEM_B(0X1D, ctx->r16) = ctx->r12;
    // 0x800C08F8: add.s       $f2, $f2, $f10
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f2.fl = ctx->f2.fl + ctx->f10.fl;
    // 0x800C08FC: b           L_800C091C
    // 0x800C0900: add.s       $f2, $f2, $f18
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f2.fl = ctx->f2.fl + ctx->f18.fl;
        goto L_800C091C;
    // 0x800C0900: add.s       $f2, $f2, $f18
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f2.fl = ctx->f2.fl + ctx->f18.fl;
L_800C0904:
    // 0x800C0904: lui         $v1, 0x800E
    ctx->r3 = S32(0X800E << 16);
    // 0x800C0908: addiu       $v1, $v1, 0x7DC8
    ctx->r3 = ADD32(ctx->r3, 0X7DC8);
    // 0x800C090C: sll         $t5, $a0, 2
    ctx->r13 = S32(ctx->r4 << 2);
    // 0x800C0910: addu        $t6, $v1, $t5
    ctx->r14 = ADD32(ctx->r3, ctx->r13);
    // 0x800C0914: lwc1        $f4, 0x0($t6)
    ctx->f4.u32l = MEM_W(ctx->r14, 0X0);
    // 0x800C0918: add.s       $f2, $f2, $f4
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f2.fl = ctx->f2.fl + ctx->f4.fl;
L_800C091C:
    // 0x800C091C: lw          $t7, 0x28($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X28);
    // 0x800C0920: lui         $t8, 0x800E
    ctx->r24 = S32(0X800E << 16);
    // 0x800C0924: addiu       $t8, $t8, 0x7CC8
    ctx->r24 = ADD32(ctx->r24, 0X7CC8);
    // 0x800C0928: addu        $t3, $t7, $t8
    ctx->r11 = ADD32(ctx->r15, ctx->r24);
    // 0x800C092C: sw          $t3, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r11;
    // 0x800C0930: lwc1        $f0, 0x0($t3)
    ctx->f0.u32l = MEM_W(ctx->r11, 0X0);
    // 0x800C0934: lui         $at, 0x4020
    ctx->r1 = S32(0X4020 << 16);
    // 0x800C0938: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x800C093C: sub.s       $f6, $f2, $f0
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f6.fl = ctx->f2.fl - ctx->f0.fl;
    // 0x800C0940: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x800C0944: div.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = DIV_S(ctx->f6.fl, ctx->f8.fl);
    // 0x800C0948: add.s       $f2, $f10, $f0
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f2.fl = ctx->f10.fl + ctx->f0.fl;
    // 0x800C094C: swc1        $f2, 0x0($t3)
    MEM_W(0X0, ctx->r11) = ctx->f2.u32l;
    // 0x800C0950: lwc1        $f16, -0x3C8C($at)
    ctx->f16.u32l = MEM_W(ctx->r1, -0X3C8C);
    // 0x800C0954: c.lt.s      $f2, $f16
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 16);
    c1cs = ctx->f2.fl < ctx->f16.fl;
    // 0x800C0958: nop

    // 0x800C095C: bc1f        L_800C098C
    if (!c1cs) {
        // 0x800C0960: lui         $a0, 0x600
        ctx->r4 = S32(0X600 << 16);
            goto L_800C098C;
    }
    // 0x800C0960: lui         $a0, 0x600
    ctx->r4 = S32(0X600 << 16);
    // 0x800C0964: ori         $a0, $a0, 0x5
    ctx->r4 = ctx->r4 | 0X5;
    // 0x800C0968: addiu       $a1, $zero, -0x3
    ctx->r5 = ADD32(0, -0X3);
    // 0x800C096C: jal         0x800C53D4
    // 0x800C0970: swc1        $f2, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->f2.u32l;
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_17;
    // 0x800C0970: swc1        $f2, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->f2.u32l;
    after_17:
    // 0x800C0974: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x800C0978: lwc1        $f18, -0x3C88($at)
    ctx->f18.u32l = MEM_W(ctx->r1, -0X3C88);
    // 0x800C097C: lwc1        $f2, 0x3C($sp)
    ctx->f2.u32l = MEM_W(ctx->r29, 0X3C);
    // 0x800C0980: mul.s       $f2, $f2, $f18
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f2.fl = MUL_S(ctx->f2.fl, ctx->f18.fl);
    // 0x800C0984: b           L_800C09E4
    // 0x800C0988: lb          $t9, 0x67($sp)
    ctx->r25 = MEM_B(ctx->r29, 0X67);
        goto L_800C09E4;
    // 0x800C0988: lb          $t9, 0x67($sp)
    ctx->r25 = MEM_B(ctx->r29, 0X67);
L_800C098C:
    // 0x800C098C: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x800C0990: lwc1        $f4, -0x3C84($at)
    ctx->f4.u32l = MEM_W(ctx->r1, -0X3C84);
    // 0x800C0994: lui         $a0, 0x600
    ctx->r4 = S32(0X600 << 16);
    // 0x800C0998: ori         $a0, $a0, 0x5
    ctx->r4 = ctx->r4 | 0X5;
    // 0x800C099C: c.lt.s      $f4, $f2
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 2);
    c1cs = ctx->f4.fl < ctx->f2.fl;
    // 0x800C09A0: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x800C09A4: bc1f        L_800C09D4
    if (!c1cs) {
        // 0x800C09A8: nop
    
            goto L_800C09D4;
    }
    // 0x800C09A8: nop

    // 0x800C09AC: lui         $a0, 0x600
    ctx->r4 = S32(0X600 << 16);
    // 0x800C09B0: ori         $a0, $a0, 0x5
    ctx->r4 = ctx->r4 | 0X5;
    // 0x800C09B4: addiu       $a1, $zero, 0x3
    ctx->r5 = ADD32(0, 0X3);
    // 0x800C09B8: jal         0x800C53D4
    // 0x800C09BC: swc1        $f2, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->f2.u32l;
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_18;
    // 0x800C09BC: swc1        $f2, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->f2.u32l;
    after_18:
    // 0x800C09C0: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x800C09C4: lwc1        $f6, -0x3C80($at)
    ctx->f6.u32l = MEM_W(ctx->r1, -0X3C80);
    // 0x800C09C8: lwc1        $f2, 0x3C($sp)
    ctx->f2.u32l = MEM_W(ctx->r29, 0X3C);
    // 0x800C09CC: b           L_800C09E0
    // 0x800C09D0: div.s       $f2, $f2, $f6
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f2.fl = DIV_S(ctx->f2.fl, ctx->f6.fl);
        goto L_800C09E0;
    // 0x800C09D0: div.s       $f2, $f2, $f6
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f2.fl = DIV_S(ctx->f2.fl, ctx->f6.fl);
L_800C09D4:
    // 0x800C09D4: jal         0x800C53D4
    // 0x800C09D8: swc1        $f2, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->f2.u32l;
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_19;
    // 0x800C09D8: swc1        $f2, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->f2.u32l;
    after_19:
    // 0x800C09DC: lwc1        $f2, 0x3C($sp)
    ctx->f2.u32l = MEM_W(ctx->r29, 0X3C);
L_800C09E0:
    // 0x800C09E0: lb          $t9, 0x67($sp)
    ctx->r25 = MEM_B(ctx->r29, 0X67);
L_800C09E4:
    // 0x800C09E4: beq         $t9, $zero, L_800C0A08
    if (ctx->r25 == 0) {
        // 0x800C09E8: addiu       $at, $zero, 0x1
        ctx->r1 = ADD32(0, 0X1);
            goto L_800C0A08;
    }
    // 0x800C09E8: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x800C09EC: beq         $t9, $at, L_800C0A78
    if (ctx->r25 == ctx->r1) {
        // 0x800C09F0: lui         $t7, 0x8004
        ctx->r15 = S32(0X8004 << 16);
            goto L_800C0A78;
    }
    // 0x800C09F0: lui         $t7, 0x8004
    ctx->r15 = S32(0X8004 << 16);
    // 0x800C09F4: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x800C09F8: beq         $t9, $at, L_800C0AEC
    if (ctx->r25 == ctx->r1) {
        // 0x800C09FC: nop
    
            goto L_800C0AEC;
    }
    // 0x800C09FC: nop

    // 0x800C0A00: b           L_800C0B90
    // 0x800C0A04: lb          $v0, 0x11($s0)
    ctx->r2 = MEM_B(ctx->r16, 0X11);
        goto L_800C0B90;
    // 0x800C0A04: lb          $v0, 0x11($s0)
    ctx->r2 = MEM_B(ctx->r16, 0X11);
L_800C0A08:
    // 0x800C0A08: lui         $t4, 0x8004
    ctx->r12 = S32(0X8004 << 16);
    // 0x800C0A0C: lw          $t4, 0x562C($t4)
    ctx->r12 = MEM_W(ctx->r12, 0X562C);
    // 0x800C0A10: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x800C0A14: lwc1        $f16, -0x3C7C($at)
    ctx->f16.u32l = MEM_W(ctx->r1, -0X3C7C);
    // 0x800C0A18: andi        $t5, $t4, 0xF
    ctx->r13 = ctx->r12 & 0XF;
    // 0x800C0A1C: mtc1        $t5, $f8
    ctx->f8.u32l = ctx->r13;
    // 0x800C0A20: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x800C0A24: lwc1        $f4, -0x3C78($at)
    ctx->f4.u32l = MEM_W(ctx->r1, -0X3C78);
    // 0x800C0A28: cvt.s.w     $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.fl = CVT_S_W(ctx->f8.u32l);
    // 0x800C0A2C: lui         $a0, 0x400
    ctx->r4 = S32(0X400 << 16);
    // 0x800C0A30: mul.s       $f18, $f10, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f18.fl = MUL_S(ctx->f10.fl, ctx->f16.fl);
    // 0x800C0A34: add.s       $f0, $f18, $f4
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f0.fl = ctx->f18.fl + ctx->f4.fl;
    // 0x800C0A38: mul.s       $f6, $f2, $f0
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f6.fl = MUL_S(ctx->f2.fl, ctx->f0.fl);
    // 0x800C0A3C: mfc1        $a1, $f6
    ctx->r5 = (int32_t)ctx->f6.u32l;
    // 0x800C0A40: jal         0x800C538C
    // 0x800C0A44: nop

    AudioThread_QueueCmdF32(rdram, ctx);
        goto after_20;
    // 0x800C0A44: nop

    after_20:
    // 0x800C0A48: lw          $t6, 0x58($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X58);
    // 0x800C0A4C: lui         $at, 0x42FE
    ctx->r1 = S32(0X42FE << 16);
    // 0x800C0A50: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
    // 0x800C0A54: mtc1        $t6, $f8
    ctx->f8.u32l = ctx->r14;
    // 0x800C0A58: lui         $a0, 0x100
    ctx->r4 = S32(0X100 << 16);
    // 0x800C0A5C: cvt.s.w     $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.fl = CVT_S_W(ctx->f8.u32l);
    // 0x800C0A60: div.s       $f18, $f10, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f18.fl = DIV_S(ctx->f10.fl, ctx->f16.fl);
    // 0x800C0A64: mfc1        $a1, $f18
    ctx->r5 = (int32_t)ctx->f18.u32l;
    // 0x800C0A68: jal         0x800C538C
    // 0x800C0A6C: nop

    AudioThread_QueueCmdF32(rdram, ctx);
        goto after_21;
    // 0x800C0A6C: nop

    after_21:
    // 0x800C0A70: b           L_800C0B90
    // 0x800C0A74: lb          $v0, 0x11($s0)
    ctx->r2 = MEM_B(ctx->r16, 0X11);
        goto L_800C0B90;
    // 0x800C0A74: lb          $v0, 0x11($s0)
    ctx->r2 = MEM_B(ctx->r16, 0X11);
L_800C0A78:
    // 0x800C0A78: lw          $t7, 0x562C($t7)
    ctx->r15 = MEM_W(ctx->r15, 0X562C);
    // 0x800C0A7C: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x800C0A80: lwc1        $f8, -0x3C74($at)
    ctx->f8.u32l = MEM_W(ctx->r1, -0X3C74);
    // 0x800C0A84: andi        $t8, $t7, 0xF
    ctx->r24 = ctx->r15 & 0XF;
    // 0x800C0A88: mtc1        $t8, $f4
    ctx->f4.u32l = ctx->r24;
    // 0x800C0A8C: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x800C0A90: lwc1        $f16, -0x3C70($at)
    ctx->f16.u32l = MEM_W(ctx->r1, -0X3C70);
    // 0x800C0A94: cvt.s.w     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
    // 0x800C0A98: lui         $a0, 0x400
    ctx->r4 = S32(0X400 << 16);
    // 0x800C0A9C: ori         $a0, $a0, 0x300
    ctx->r4 = ctx->r4 | 0X300;
    // 0x800C0AA0: mul.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = MUL_S(ctx->f6.fl, ctx->f8.fl);
    // 0x800C0AA4: add.s       $f0, $f10, $f16
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f0.fl = ctx->f10.fl + ctx->f16.fl;
    // 0x800C0AA8: mul.s       $f18, $f2, $f0
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f18.fl = MUL_S(ctx->f2.fl, ctx->f0.fl);
    // 0x800C0AAC: mfc1        $a1, $f18
    ctx->r5 = (int32_t)ctx->f18.u32l;
    // 0x800C0AB0: jal         0x800C538C
    // 0x800C0AB4: nop

    AudioThread_QueueCmdF32(rdram, ctx);
        goto after_22;
    // 0x800C0AB4: nop

    after_22:
    // 0x800C0AB8: lw          $t3, 0x58($sp)
    ctx->r11 = MEM_W(ctx->r29, 0X58);
    // 0x800C0ABC: lui         $at, 0x42FE
    ctx->r1 = S32(0X42FE << 16);
    // 0x800C0AC0: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x800C0AC4: mtc1        $t3, $f4
    ctx->f4.u32l = ctx->r11;
    // 0x800C0AC8: lui         $a0, 0x100
    ctx->r4 = S32(0X100 << 16);
    // 0x800C0ACC: ori         $a0, $a0, 0x300
    ctx->r4 = ctx->r4 | 0X300;
    // 0x800C0AD0: cvt.s.w     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
    // 0x800C0AD4: div.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = DIV_S(ctx->f6.fl, ctx->f8.fl);
    // 0x800C0AD8: mfc1        $a1, $f10
    ctx->r5 = (int32_t)ctx->f10.u32l;
    // 0x800C0ADC: jal         0x800C538C
    // 0x800C0AE0: nop

    AudioThread_QueueCmdF32(rdram, ctx);
        goto after_23;
    // 0x800C0AE0: nop

    after_23:
    // 0x800C0AE4: b           L_800C0B90
    // 0x800C0AE8: lb          $v0, 0x11($s0)
    ctx->r2 = MEM_B(ctx->r16, 0X11);
        goto L_800C0B90;
    // 0x800C0AE8: lb          $v0, 0x11($s0)
    ctx->r2 = MEM_B(ctx->r16, 0X11);
L_800C0AEC:
    // 0x800C0AEC: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x800C0AF0: lwc1        $f16, 0x7E20($at)
    ctx->f16.u32l = MEM_W(ctx->r1, 0X7E20);
    // 0x800C0AF4: lb          $a0, 0x5B($sp)
    ctx->r4 = MEM_B(ctx->r29, 0X5B);
    // 0x800C0AF8: mul.s       $f18, $f2, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f18.fl = MUL_S(ctx->f2.fl, ctx->f16.fl);
    // 0x800C0AFC: mfc1        $a1, $f18
    ctx->r5 = (int32_t)ctx->f18.u32l;
    // 0x800C0B00: jal         0x800C00B0
    // 0x800C0B04: nop

    func_800C00B0(rdram, ctx);
        goto after_24;
    // 0x800C0B04: nop

    after_24:
    // 0x800C0B08: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x800C0B0C: lwc1        $f4, 0x7E24($at)
    ctx->f4.u32l = MEM_W(ctx->r1, 0X7E24);
    // 0x800C0B10: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x800C0B14: lwc1        $f6, -0x3C6C($at)
    ctx->f6.u32l = MEM_W(ctx->r1, -0X3C6C);
    // 0x800C0B18: lui         $a0, 0x100
    ctx->r4 = S32(0X100 << 16);
    // 0x800C0B1C: ori         $a0, $a0, 0x300
    ctx->r4 = ctx->r4 | 0X300;
    // 0x800C0B20: mul.s       $f8, $f4, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = MUL_S(ctx->f4.fl, ctx->f6.fl);
    // 0x800C0B24: mfc1        $a1, $f8
    ctx->r5 = (int32_t)ctx->f8.u32l;
    // 0x800C0B28: jal         0x800C538C
    // 0x800C0B2C: nop

    AudioThread_QueueCmdF32(rdram, ctx);
        goto after_25;
    // 0x800C0B2C: nop

    after_25:
    // 0x800C0B30: lui         $a0, 0x100
    ctx->r4 = S32(0X100 << 16);
    // 0x800C0B34: lui         $a1, 0x801D
    ctx->r5 = S32(0X801D << 16);
    // 0x800C0B38: lw          $a1, 0x7E24($a1)
    ctx->r5 = MEM_W(ctx->r5, 0X7E24);
    // 0x800C0B3C: jal         0x800C538C
    // 0x800C0B40: ori         $a0, $a0, 0x500
    ctx->r4 = ctx->r4 | 0X500;
    AudioThread_QueueCmdF32(rdram, ctx);
        goto after_26;
    // 0x800C0B40: ori         $a0, $a0, 0x500
    ctx->r4 = ctx->r4 | 0X500;
    after_26:
    // 0x800C0B44: lui         $a0, 0x300
    ctx->r4 = S32(0X300 << 16);
    // 0x800C0B48: lui         $a1, 0x801D
    ctx->r5 = S32(0X801D << 16);
    // 0x800C0B4C: lb          $a1, 0x7E28($a1)
    ctx->r5 = MEM_B(ctx->r5, 0X7E28);
    // 0x800C0B50: jal         0x800C53D4
    // 0x800C0B54: ori         $a0, $a0, 0x300
    ctx->r4 = ctx->r4 | 0X300;
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_27;
    // 0x800C0B54: ori         $a0, $a0, 0x300
    ctx->r4 = ctx->r4 | 0X300;
    after_27:
    // 0x800C0B58: lui         $a0, 0x300
    ctx->r4 = S32(0X300 << 16);
    // 0x800C0B5C: lui         $a1, 0x801D
    ctx->r5 = S32(0X801D << 16);
    // 0x800C0B60: lb          $a1, 0x7E28($a1)
    ctx->r5 = MEM_B(ctx->r5, 0X7E28);
    // 0x800C0B64: jal         0x800C53D4
    // 0x800C0B68: ori         $a0, $a0, 0x500
    ctx->r4 = ctx->r4 | 0X500;
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_28;
    // 0x800C0B68: ori         $a0, $a0, 0x500
    ctx->r4 = ctx->r4 | 0X500;
    after_28:
    // 0x800C0B6C: lui         $t9, 0x801D
    ctx->r25 = S32(0X801D << 16);
    // 0x800C0B70: lhu         $t9, 0x7DE8($t9)
    ctx->r25 = MEM_HU(ctx->r25, 0X7DE8);
    // 0x800C0B74: lui         $a0, 0x500
    ctx->r4 = S32(0X500 << 16);
    // 0x800C0B78: ori         $a0, $a0, 0x300
    ctx->r4 = ctx->r4 | 0X300;
    // 0x800C0B7C: bne         $t9, $zero, L_800C0B8C
    if (ctx->r25 != 0) {
        // 0x800C0B80: lui         $a1, 0x801D
        ctx->r5 = S32(0X801D << 16);
            goto L_800C0B8C;
    }
    // 0x800C0B80: lui         $a1, 0x801D
    ctx->r5 = S32(0X801D << 16);
    // 0x800C0B84: jal         0x800C53D4
    // 0x800C0B88: lb          $a1, 0x7E29($a1)
    ctx->r5 = MEM_B(ctx->r5, 0X7E29);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_29;
    // 0x800C0B88: lb          $a1, 0x7E29($a1)
    ctx->r5 = MEM_B(ctx->r5, 0X7E29);
    after_29:
L_800C0B8C:
    // 0x800C0B8C: lb          $v0, 0x11($s0)
    ctx->r2 = MEM_B(ctx->r16, 0X11);
L_800C0B90:
    // 0x800C0B90: slti        $at, $v0, 0x64
    ctx->r1 = SIGNED(ctx->r2) < 0X64 ? 1 : 0;
    // 0x800C0B94: beq         $at, $zero, L_800C0BDC
    if (ctx->r1 == 0) {
        // 0x800C0B98: lui         $t4, 0x800E
        ctx->r12 = S32(0X800E << 16);
            goto L_800C0BDC;
    }
    // 0x800C0B98: lui         $t4, 0x800E
    ctx->r12 = S32(0X800E << 16);
    // 0x800C0B9C: lw          $t4, 0x7CAC($t4)
    ctx->r12 = MEM_W(ctx->r12, 0X7CAC);
    // 0x800C0BA0: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x800C0BA4: bnel        $t4, $at, L_800C0BE0
    if (ctx->r12 != ctx->r1) {
        // 0x800C0BA8: slti        $at, $v0, 0x32
        ctx->r1 = SIGNED(ctx->r2) < 0X32 ? 1 : 0;
            goto L_800C0BE0;
    }
    goto skip_28;
    // 0x800C0BA8: slti        $at, $v0, 0x32
    ctx->r1 = SIGNED(ctx->r2) < 0X32 ? 1 : 0;
    skip_28:
    // 0x800C0BAC: lb          $t5, 0x0($s0)
    ctx->r13 = MEM_B(ctx->r16, 0X0);
    // 0x800C0BB0: lui         $t6, 0x8004
    ctx->r14 = S32(0X8004 << 16);
    // 0x800C0BB4: slti        $at, $t5, 0x15
    ctx->r1 = SIGNED(ctx->r13) < 0X15 ? 1 : 0;
    // 0x800C0BB8: bnel        $at, $zero, L_800C0BE0
    if (ctx->r1 != 0) {
        // 0x800C0BBC: slti        $at, $v0, 0x32
        ctx->r1 = SIGNED(ctx->r2) < 0X32 ? 1 : 0;
            goto L_800C0BE0;
    }
    goto skip_29;
    // 0x800C0BBC: slti        $at, $v0, 0x32
    ctx->r1 = SIGNED(ctx->r2) < 0X32 ? 1 : 0;
    skip_29:
    // 0x800C0BC0: lw          $t6, 0x562C($t6)
    ctx->r14 = MEM_W(ctx->r14, 0X562C);
    // 0x800C0BC4: addiu       $t3, $zero, 0x1
    ctx->r11 = ADD32(0, 0X1);
    // 0x800C0BC8: sb          $t3, 0x10($s0)
    MEM_B(0X10, ctx->r16) = ctx->r11;
    // 0x800C0BCC: andi        $t7, $t6, 0xF
    ctx->r15 = ctx->r14 & 0XF;
    // 0x800C0BD0: addiu       $t8, $t7, 0x64
    ctx->r24 = ADD32(ctx->r15, 0X64);
    // 0x800C0BD4: sb          $t8, 0x11($s0)
    MEM_B(0X11, ctx->r16) = ctx->r24;
    // 0x800C0BD8: lb          $v0, 0x11($s0)
    ctx->r2 = MEM_B(ctx->r16, 0X11);
L_800C0BDC:
    // 0x800C0BDC: slti        $at, $v0, 0x32
    ctx->r1 = SIGNED(ctx->r2) < 0X32 ? 1 : 0;
L_800C0BE0:
    // 0x800C0BE0: beql        $at, $zero, L_800C0BF0
    if (ctx->r1 == 0) {
        // 0x800C0BE4: lb          $t9, 0x7($s0)
        ctx->r25 = MEM_B(ctx->r16, 0X7);
            goto L_800C0BF0;
    }
    goto skip_30;
    // 0x800C0BE4: lb          $t9, 0x7($s0)
    ctx->r25 = MEM_B(ctx->r16, 0X7);
    skip_30:
    // 0x800C0BE8: sb          $zero, 0x11($s0)
    MEM_B(0X11, ctx->r16) = 0;
    // 0x800C0BEC: lb          $t9, 0x7($s0)
    ctx->r25 = MEM_B(ctx->r16, 0X7);
L_800C0BF0:
    // 0x800C0BF0: bnel        $t9, $zero, L_800C0C00
    if (ctx->r25 != 0) {
        // 0x800C0BF4: lb          $t4, 0x67($sp)
        ctx->r12 = MEM_B(ctx->r29, 0X67);
            goto L_800C0C00;
    }
    goto skip_31;
    // 0x800C0BF4: lb          $t4, 0x67($sp)
    ctx->r12 = MEM_B(ctx->r29, 0X67);
    skip_31:
    // 0x800C0BF8: sb          $zero, 0x11($s0)
    MEM_B(0X11, ctx->r16) = 0;
    // 0x800C0BFC: lb          $t4, 0x67($sp)
    ctx->r12 = MEM_B(ctx->r29, 0X67);
L_800C0C00:
    // 0x800C0C00: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x800C0C04: bnel        $t4, $at, L_800C0C14
    if (ctx->r12 != ctx->r1) {
        // 0x800C0C08: lb          $v0, 0x11($s0)
        ctx->r2 = MEM_B(ctx->r16, 0X11);
            goto L_800C0C14;
    }
    goto skip_32;
    // 0x800C0C08: lb          $v0, 0x11($s0)
    ctx->r2 = MEM_B(ctx->r16, 0X11);
    skip_32:
    // 0x800C0C0C: sb          $zero, 0x11($s0)
    MEM_B(0X11, ctx->r16) = 0;
    // 0x800C0C10: lb          $v0, 0x11($s0)
    ctx->r2 = MEM_B(ctx->r16, 0X11);
L_800C0C14:
    // 0x800C0C14: beq         $v0, $zero, L_800C0D10
    if (ctx->r2 == 0) {
        // 0x800C0C18: addiu       $t5, $v0, -0x32
        ctx->r13 = ADD32(ctx->r2, -0X32);
            goto L_800C0D10;
    }
    // 0x800C0C18: addiu       $t5, $v0, -0x32
    ctx->r13 = ADD32(ctx->r2, -0X32);
    // 0x800C0C1C: sb          $t5, 0x11($s0)
    MEM_B(0X11, ctx->r16) = ctx->r13;
    // 0x800C0C20: lw          $v1, 0x30($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X30);
    // 0x800C0C24: lb          $v0, 0x11($s0)
    ctx->r2 = MEM_B(ctx->r16, 0X11);
    // 0x800C0C28: addiu       $v1, $v1, 0x2
    ctx->r3 = ADD32(ctx->r3, 0X2);
    // 0x800C0C2C: slti        $at, $v0, 0x29
    ctx->r1 = SIGNED(ctx->r2) < 0X29 ? 1 : 0;
    // 0x800C0C30: bne         $at, $zero, L_800C0C48
    if (ctx->r1 != 0) {
        // 0x800C0C34: andi        $a3, $v1, 0xFF
        ctx->r7 = ctx->r3 & 0XFF;
            goto L_800C0C48;
    }
    // 0x800C0C34: andi        $a3, $v1, 0xFF
    ctx->r7 = ctx->r3 & 0XFF;
    // 0x800C0C38: sll         $t6, $v0, 1
    ctx->r14 = S32(ctx->r2 << 1);
    // 0x800C0C3C: addiu       $t7, $t6, -0x1E
    ctx->r15 = ADD32(ctx->r14, -0X1E);
    // 0x800C0C40: b           L_800C0C60
    // 0x800C0C44: sb          $t7, 0x11($s0)
    MEM_B(0X11, ctx->r16) = ctx->r15;
        goto L_800C0C60;
    // 0x800C0C44: sb          $t7, 0x11($s0)
    MEM_B(0X11, ctx->r16) = ctx->r15;
L_800C0C48:
    // 0x800C0C48: bgez        $v0, L_800C0C58
    if (SIGNED(ctx->r2) >= 0) {
        // 0x800C0C4C: sra         $t8, $v0, 1
        ctx->r24 = S32(SIGNED(ctx->r2) >> 1);
            goto L_800C0C58;
    }
    // 0x800C0C4C: sra         $t8, $v0, 1
    ctx->r24 = S32(SIGNED(ctx->r2) >> 1);
    // 0x800C0C50: addiu       $at, $v0, 0x1
    ctx->r1 = ADD32(ctx->r2, 0X1);
    // 0x800C0C54: sra         $t8, $at, 1
    ctx->r24 = S32(SIGNED(ctx->r1) >> 1);
L_800C0C58:
    // 0x800C0C58: addiu       $t3, $t8, 0x14
    ctx->r11 = ADD32(ctx->r24, 0X14);
    // 0x800C0C5C: sb          $t3, 0x11($s0)
    MEM_B(0X11, ctx->r16) = ctx->r11;
L_800C0C60:
    // 0x800C0C60: lb          $t5, 0x0($s0)
    ctx->r13 = MEM_B(ctx->r16, 0X0);
    // 0x800C0C64: andi        $a0, $v1, 0xFF
    ctx->r4 = ctx->r3 & 0XFF;
    // 0x800C0C68: sll         $t9, $a0, 8
    ctx->r25 = S32(ctx->r4 << 8);
    // 0x800C0C6C: mtc1        $t5, $f10
    ctx->f10.u32l = ctx->r13;
    // 0x800C0C70: lui         $at, 0x400
    ctx->r1 = S32(0X400 << 16);
    // 0x800C0C74: or          $a0, $t9, $at
    ctx->r4 = ctx->r25 | ctx->r1;
    // 0x800C0C78: cvt.s.w     $f16, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    ctx->f16.fl = CVT_S_W(ctx->f10.u32l);
    // 0x800C0C7C: lui         $at, 0x42C8
    ctx->r1 = S32(0X42C8 << 16);
    // 0x800C0C80: mtc1        $at, $f18
    ctx->f18.u32l = ctx->r1;
    // 0x800C0C84: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x800C0C88: lwc1        $f6, -0x3C68($at)
    ctx->f6.u32l = MEM_W(ctx->r1, -0X3C68);
    // 0x800C0C8C: sw          $a3, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r7;
    // 0x800C0C90: div.s       $f4, $f16, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f4.fl = DIV_S(ctx->f16.fl, ctx->f18.fl);
    // 0x800C0C94: add.s       $f8, $f4, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = ctx->f4.fl + ctx->f6.fl;
    // 0x800C0C98: mfc1        $a1, $f8
    ctx->r5 = (int32_t)ctx->f8.u32l;
    // 0x800C0C9C: jal         0x800C538C
    // 0x800C0CA0: nop

    AudioThread_QueueCmdF32(rdram, ctx);
        goto after_30;
    // 0x800C0CA0: nop

    after_30:
    // 0x800C0CA4: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x800C0CA8: lw          $v0, 0x7DC4($v0)
    ctx->r2 = MEM_W(ctx->r2, 0X7DC4);
    // 0x800C0CAC: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x800C0CB0: lw          $a3, 0x28($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X28);
    // 0x800C0CB4: beq         $v0, $at, L_800C0CD4
    if (ctx->r2 == ctx->r1) {
        // 0x800C0CB8: addiu       $at, $zero, 0x6
        ctx->r1 = ADD32(0, 0X6);
            goto L_800C0CD4;
    }
    // 0x800C0CB8: addiu       $at, $zero, 0x6
    ctx->r1 = ADD32(0, 0X6);
    // 0x800C0CBC: beq         $v0, $at, L_800C0CD4
    if (ctx->r2 == ctx->r1) {
        // 0x800C0CC0: lui         $v0, 0x8004
        ctx->r2 = S32(0X8004 << 16);
            goto L_800C0CD4;
    }
    // 0x800C0CC0: lui         $v0, 0x8004
    ctx->r2 = S32(0X8004 << 16);
    // 0x800C0CC4: lw          $v0, 0x562C($v0)
    ctx->r2 = MEM_W(ctx->r2, 0X562C);
    // 0x800C0CC8: andi        $t6, $v0, 0x3
    ctx->r14 = ctx->r2 & 0X3;
    // 0x800C0CCC: b           L_800C0CF0
    // 0x800C0CD0: sll         $v0, $t6, 2
    ctx->r2 = S32(ctx->r14 << 2);
        goto L_800C0CF0;
    // 0x800C0CD0: sll         $v0, $t6, 2
    ctx->r2 = S32(ctx->r14 << 2);
L_800C0CD4:
    // 0x800C0CD4: lui         $v0, 0x8004
    ctx->r2 = S32(0X8004 << 16);
    // 0x800C0CD8: lw          $v0, 0x562C($v0)
    ctx->r2 = MEM_W(ctx->r2, 0X562C);
    // 0x800C0CDC: addiu       $at, $zero, 0x5
    ctx->r1 = ADD32(0, 0X5);
    // 0x800C0CE0: divu        $zero, $v0, $at
    lo = S32(U32(ctx->r2) / U32(ctx->r1)); hi = S32(U32(ctx->r2) % U32(ctx->r1));
    // 0x800C0CE4: mfhi        $t8
    ctx->r24 = hi;
    // 0x800C0CE8: sll         $v0, $t8, 2
    ctx->r2 = S32(ctx->r24 << 2);
    // 0x800C0CEC: nop

L_800C0CF0:
    // 0x800C0CF0: lb          $t9, 0x10($s0)
    ctx->r25 = MEM_B(ctx->r16, 0X10);
    // 0x800C0CF4: andi        $a0, $a3, 0xFF
    ctx->r4 = ctx->r7 & 0XFF;
    // 0x800C0CF8: lbu         $a2, 0x11($s0)
    ctx->r6 = MEM_BU(ctx->r16, 0X11);
    // 0x800C0CFC: addu        $a1, $t9, $v0
    ctx->r5 = ADD32(ctx->r25, ctx->r2);
    // 0x800C0D00: andi        $t4, $a1, 0xFF
    ctx->r12 = ctx->r5 & 0XFF;
    // 0x800C0D04: jal         0x800C0044
    // 0x800C0D08: or          $a1, $t4, $zero
    ctx->r5 = ctx->r12 | 0;
    func_800C0044(rdram, ctx);
        goto after_31;
    // 0x800C0D08: or          $a1, $t4, $zero
    ctx->r5 = ctx->r12 | 0;
    after_31:
    // 0x800C0D0C: sb          $zero, 0x11($s0)
    MEM_B(0X11, ctx->r16) = 0;
L_800C0D10:
    // 0x800C0D10: lh          $t5, 0xC($s0)
    ctx->r13 = MEM_H(ctx->r16, 0XC);
    // 0x800C0D14: slti        $at, $t5, 0x5
    ctx->r1 = SIGNED(ctx->r13) < 0X5 ? 1 : 0;
    // 0x800C0D18: bnel        $at, $zero, L_800C0D38
    if (ctx->r1 != 0) {
        // 0x800C0D1C: lb          $t8, 0x12($s0)
        ctx->r24 = MEM_B(ctx->r16, 0X12);
            goto L_800C0D38;
    }
    goto skip_33;
    // 0x800C0D1C: lb          $t8, 0x12($s0)
    ctx->r24 = MEM_B(ctx->r16, 0X12);
    skip_33:
    // 0x800C0D20: lb          $t6, 0x16($s0)
    ctx->r14 = MEM_B(ctx->r16, 0X16);
    // 0x800C0D24: lb          $t7, 0x12($s0)
    ctx->r15 = MEM_B(ctx->r16, 0X12);
    // 0x800C0D28: bnel        $t6, $t7, L_800C0D38
    if (ctx->r14 != ctx->r15) {
        // 0x800C0D2C: lb          $t8, 0x12($s0)
        ctx->r24 = MEM_B(ctx->r16, 0X12);
            goto L_800C0D38;
    }
    goto skip_34;
    // 0x800C0D2C: lb          $t8, 0x12($s0)
    ctx->r24 = MEM_B(ctx->r16, 0X12);
    skip_34:
    // 0x800C0D30: sb          $zero, 0x13($s0)
    MEM_B(0X13, ctx->r16) = 0;
    // 0x800C0D34: lb          $t8, 0x12($s0)
    ctx->r24 = MEM_B(ctx->r16, 0X12);
L_800C0D38:
    // 0x800C0D38: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x800C0D3C: bne         $t8, $at, L_800C0D58
    if (ctx->r24 != ctx->r1) {
        // 0x800C0D40: lui         $a0, 0x600
        ctx->r4 = S32(0X600 << 16);
            goto L_800C0D58;
    }
    // 0x800C0D40: lui         $a0, 0x600
    ctx->r4 = S32(0X600 << 16);
    // 0x800C0D44: ori         $a0, $a0, 0x700
    ctx->r4 = ctx->r4 | 0X700;
    // 0x800C0D48: jal         0x800C53D4
    // 0x800C0D4C: addiu       $a1, $zero, 0x13
    ctx->r5 = ADD32(0, 0X13);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_32;
    // 0x800C0D4C: addiu       $a1, $zero, 0x13
    ctx->r5 = ADD32(0, 0X13);
    after_32:
    // 0x800C0D50: sb          $zero, 0x13($s0)
    MEM_B(0X13, ctx->r16) = 0;
    // 0x800C0D54: sb          $zero, 0x12($s0)
    MEM_B(0X12, ctx->r16) = 0;
L_800C0D58:
    // 0x800C0D58: lb          $v1, 0x13($s0)
    ctx->r3 = MEM_B(ctx->r16, 0X13);
    // 0x800C0D5C: lh          $v0, 0xC($s0)
    ctx->r2 = MEM_H(ctx->r16, 0XC);
    // 0x800C0D60: beq         $v1, $zero, L_800C1064
    if (ctx->r3 == 0) {
        // 0x800C0D64: nop
    
            goto L_800C1064;
    }
    // 0x800C0D64: nop

    // 0x800C0D68: bnel        $v0, $zero, L_800C0DE0
    if (ctx->r2 != 0) {
        // 0x800C0D6C: lb          $v0, 0x1F($s0)
        ctx->r2 = MEM_B(ctx->r16, 0X1F);
            goto L_800C0DE0;
    }
    goto skip_35;
    // 0x800C0D6C: lb          $v0, 0x1F($s0)
    ctx->r2 = MEM_B(ctx->r16, 0X1F);
    skip_35:
    // 0x800C0D70: lb          $v0, 0x1F($s0)
    ctx->r2 = MEM_B(ctx->r16, 0X1F);
    // 0x800C0D74: slti        $at, $v0, 0x24
    ctx->r1 = SIGNED(ctx->r2) < 0X24 ? 1 : 0;
    // 0x800C0D78: bnel        $at, $zero, L_800C0DA0
    if (ctx->r1 != 0) {
        // 0x800C0D7C: slti        $at, $v0, 0x10
        ctx->r1 = SIGNED(ctx->r2) < 0X10 ? 1 : 0;
            goto L_800C0DA0;
    }
    goto skip_36;
    // 0x800C0D7C: slti        $at, $v0, 0x10
    ctx->r1 = SIGNED(ctx->r2) < 0X10 ? 1 : 0;
    skip_36:
    // 0x800C0D80: bgez        $v1, L_800C0D90
    if (SIGNED(ctx->r3) >= 0) {
        // 0x800C0D84: sra         $t3, $v1, 2
        ctx->r11 = S32(SIGNED(ctx->r3) >> 2);
            goto L_800C0D90;
    }
    // 0x800C0D84: sra         $t3, $v1, 2
    ctx->r11 = S32(SIGNED(ctx->r3) >> 2);
    // 0x800C0D88: addiu       $at, $v1, 0x3
    ctx->r1 = ADD32(ctx->r3, 0X3);
    // 0x800C0D8C: sra         $t3, $at, 2
    ctx->r11 = S32(SIGNED(ctx->r1) >> 2);
L_800C0D90:
    // 0x800C0D90: addiu       $t9, $t3, 0x60
    ctx->r25 = ADD32(ctx->r11, 0X60);
    // 0x800C0D94: b           L_800C0E44
    // 0x800C0D98: sb          $t9, 0x13($s0)
    MEM_B(0X13, ctx->r16) = ctx->r25;
        goto L_800C0E44;
    // 0x800C0D98: sb          $t9, 0x13($s0)
    MEM_B(0X13, ctx->r16) = ctx->r25;
    // 0x800C0D9C: slti        $at, $v0, 0x10
    ctx->r1 = SIGNED(ctx->r2) < 0X10 ? 1 : 0;
L_800C0DA0:
    // 0x800C0DA0: bne         $at, $zero, L_800C0DC4
    if (ctx->r1 != 0) {
        // 0x800C0DA4: nop
    
            goto L_800C0DC4;
    }
    // 0x800C0DA4: nop

    // 0x800C0DA8: bgez        $v1, L_800C0DB8
    if (SIGNED(ctx->r3) >= 0) {
        // 0x800C0DAC: sra         $t4, $v1, 2
        ctx->r12 = S32(SIGNED(ctx->r3) >> 2);
            goto L_800C0DB8;
    }
    // 0x800C0DAC: sra         $t4, $v1, 2
    ctx->r12 = S32(SIGNED(ctx->r3) >> 2);
    // 0x800C0DB0: addiu       $at, $v1, 0x3
    ctx->r1 = ADD32(ctx->r3, 0X3);
    // 0x800C0DB4: sra         $t4, $at, 2
    ctx->r12 = S32(SIGNED(ctx->r1) >> 2);
L_800C0DB8:
    // 0x800C0DB8: addiu       $t5, $t4, 0x40
    ctx->r13 = ADD32(ctx->r12, 0X40);
    // 0x800C0DBC: b           L_800C0E44
    // 0x800C0DC0: sb          $t5, 0x13($s0)
    MEM_B(0X13, ctx->r16) = ctx->r13;
        goto L_800C0E44;
    // 0x800C0DC0: sb          $t5, 0x13($s0)
    MEM_B(0X13, ctx->r16) = ctx->r13;
L_800C0DC4:
    // 0x800C0DC4: bgez        $v1, L_800C0DD4
    if (SIGNED(ctx->r3) >= 0) {
        // 0x800C0DC8: sra         $t6, $v1, 1
        ctx->r14 = S32(SIGNED(ctx->r3) >> 1);
            goto L_800C0DD4;
    }
    // 0x800C0DC8: sra         $t6, $v1, 1
    ctx->r14 = S32(SIGNED(ctx->r3) >> 1);
    // 0x800C0DCC: addiu       $at, $v1, 0x1
    ctx->r1 = ADD32(ctx->r3, 0X1);
    // 0x800C0DD0: sra         $t6, $at, 1
    ctx->r14 = S32(SIGNED(ctx->r1) >> 1);
L_800C0DD4:
    // 0x800C0DD4: b           L_800C0E44
    // 0x800C0DD8: sb          $t6, 0x13($s0)
    MEM_B(0X13, ctx->r16) = ctx->r14;
        goto L_800C0E44;
    // 0x800C0DD8: sb          $t6, 0x13($s0)
    MEM_B(0X13, ctx->r16) = ctx->r14;
    // 0x800C0DDC: lb          $v0, 0x1F($s0)
    ctx->r2 = MEM_B(ctx->r16, 0X1F);
L_800C0DE0:
    // 0x800C0DE0: slti        $at, $v0, 0x24
    ctx->r1 = SIGNED(ctx->r2) < 0X24 ? 1 : 0;
    // 0x800C0DE4: bnel        $at, $zero, L_800C0E0C
    if (ctx->r1 != 0) {
        // 0x800C0DE8: slti        $at, $v0, 0x10
        ctx->r1 = SIGNED(ctx->r2) < 0X10 ? 1 : 0;
            goto L_800C0E0C;
    }
    goto skip_37;
    // 0x800C0DE8: slti        $at, $v0, 0x10
    ctx->r1 = SIGNED(ctx->r2) < 0X10 ? 1 : 0;
    skip_37:
    // 0x800C0DEC: bgez        $v1, L_800C0DFC
    if (SIGNED(ctx->r3) >= 0) {
        // 0x800C0DF0: sra         $t7, $v1, 2
        ctx->r15 = S32(SIGNED(ctx->r3) >> 2);
            goto L_800C0DFC;
    }
    // 0x800C0DF0: sra         $t7, $v1, 2
    ctx->r15 = S32(SIGNED(ctx->r3) >> 2);
    // 0x800C0DF4: addiu       $at, $v1, 0x3
    ctx->r1 = ADD32(ctx->r3, 0X3);
    // 0x800C0DF8: sra         $t7, $at, 2
    ctx->r15 = S32(SIGNED(ctx->r1) >> 2);
L_800C0DFC:
    // 0x800C0DFC: addiu       $t8, $t7, 0x30
    ctx->r24 = ADD32(ctx->r15, 0X30);
    // 0x800C0E00: b           L_800C0E44
    // 0x800C0E04: sb          $t8, 0x13($s0)
    MEM_B(0X13, ctx->r16) = ctx->r24;
        goto L_800C0E44;
    // 0x800C0E04: sb          $t8, 0x13($s0)
    MEM_B(0X13, ctx->r16) = ctx->r24;
    // 0x800C0E08: slti        $at, $v0, 0x10
    ctx->r1 = SIGNED(ctx->r2) < 0X10 ? 1 : 0;
L_800C0E0C:
    // 0x800C0E0C: bne         $at, $zero, L_800C0E30
    if (ctx->r1 != 0) {
        // 0x800C0E10: nop
    
            goto L_800C0E30;
    }
    // 0x800C0E10: nop

    // 0x800C0E14: bgez        $v1, L_800C0E24
    if (SIGNED(ctx->r3) >= 0) {
        // 0x800C0E18: sra         $t3, $v1, 2
        ctx->r11 = S32(SIGNED(ctx->r3) >> 2);
            goto L_800C0E24;
    }
    // 0x800C0E18: sra         $t3, $v1, 2
    ctx->r11 = S32(SIGNED(ctx->r3) >> 2);
    // 0x800C0E1C: addiu       $at, $v1, 0x3
    ctx->r1 = ADD32(ctx->r3, 0X3);
    // 0x800C0E20: sra         $t3, $at, 2
    ctx->r11 = S32(SIGNED(ctx->r1) >> 2);
L_800C0E24:
    // 0x800C0E24: addiu       $t9, $t3, 0x20
    ctx->r25 = ADD32(ctx->r11, 0X20);
    // 0x800C0E28: b           L_800C0E44
    // 0x800C0E2C: sb          $t9, 0x13($s0)
    MEM_B(0X13, ctx->r16) = ctx->r25;
        goto L_800C0E44;
    // 0x800C0E2C: sb          $t9, 0x13($s0)
    MEM_B(0X13, ctx->r16) = ctx->r25;
L_800C0E30:
    // 0x800C0E30: bgez        $v1, L_800C0E40
    if (SIGNED(ctx->r3) >= 0) {
        // 0x800C0E34: sra         $t4, $v1, 2
        ctx->r12 = S32(SIGNED(ctx->r3) >> 2);
            goto L_800C0E40;
    }
    // 0x800C0E34: sra         $t4, $v1, 2
    ctx->r12 = S32(SIGNED(ctx->r3) >> 2);
    // 0x800C0E38: addiu       $at, $v1, 0x3
    ctx->r1 = ADD32(ctx->r3, 0X3);
    // 0x800C0E3C: sra         $t4, $at, 2
    ctx->r12 = S32(SIGNED(ctx->r1) >> 2);
L_800C0E40:
    // 0x800C0E40: sb          $t4, 0x13($s0)
    MEM_B(0X13, ctx->r16) = ctx->r12;
L_800C0E44:
    // 0x800C0E44: lb          $v0, 0x12($s0)
    ctx->r2 = MEM_B(ctx->r16, 0X12);
    // 0x800C0E48: lw          $a0, 0x30($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X30);
    // 0x800C0E4C: addiu       $at, $zero, 0x1C
    ctx->r1 = ADD32(0, 0X1C);
    // 0x800C0E50: bne         $v0, $at, L_800C0E88
    if (ctx->r2 != ctx->r1) {
        // 0x800C0E54: addiu       $a0, $a0, 0x2
        ctx->r4 = ADD32(ctx->r4, 0X2);
            goto L_800C0E88;
    }
    // 0x800C0E54: addiu       $a0, $a0, 0x2
    ctx->r4 = ADD32(ctx->r4, 0X2);
    // 0x800C0E58: lui         $t7, 0x801D
    ctx->r15 = S32(0X801D << 16);
    // 0x800C0E5C: lw          $t7, 0x7E08($t7)
    ctx->r15 = MEM_W(ctx->r15, 0X7E08);
    // 0x800C0E60: lb          $t6, 0x14($s0)
    ctx->r14 = MEM_B(ctx->r16, 0X14);
    // 0x800C0E64: andi        $t5, $a0, 0xFF
    ctx->r13 = ctx->r4 & 0XFF;
    // 0x800C0E68: or          $a0, $t5, $zero
    ctx->r4 = ctx->r13 | 0;
    // 0x800C0E6C: addu        $a1, $t6, $t7
    ctx->r5 = ADD32(ctx->r14, ctx->r15);
    // 0x800C0E70: andi        $t8, $a1, 0xFF
    ctx->r24 = ctx->r5 & 0XFF;
    // 0x800C0E74: or          $a1, $t8, $zero
    ctx->r5 = ctx->r24 | 0;
    // 0x800C0E78: jal         0x800BFFEC
    // 0x800C0E7C: lbu         $a2, 0x13($s0)
    ctx->r6 = MEM_BU(ctx->r16, 0X13);
    func_800BFFEC(rdram, ctx);
        goto after_33;
    // 0x800C0E7C: lbu         $a2, 0x13($s0)
    ctx->r6 = MEM_BU(ctx->r16, 0X13);
    after_33:
    // 0x800C0E80: b           L_800C0F44
    // 0x800C0E84: lb          $v0, 0x12($s0)
    ctx->r2 = MEM_B(ctx->r16, 0X12);
        goto L_800C0F44;
    // 0x800C0E84: lb          $v0, 0x12($s0)
    ctx->r2 = MEM_B(ctx->r16, 0X12);
L_800C0E88:
    // 0x800C0E88: addiu       $at, $zero, 0x40
    ctx->r1 = ADD32(0, 0X40);
    // 0x800C0E8C: bnel        $v0, $at, L_800C0ED8
    if (ctx->r2 != ctx->r1) {
        // 0x800C0E90: addiu       $at, $zero, 0x41
        ctx->r1 = ADD32(0, 0X41);
            goto L_800C0ED8;
    }
    goto skip_38;
    // 0x800C0E90: addiu       $at, $zero, 0x41
    ctx->r1 = ADD32(0, 0X41);
    skip_38:
    // 0x800C0E94: lb          $t3, 0x7($s0)
    ctx->r11 = MEM_B(ctx->r16, 0X7);
    // 0x800C0E98: lw          $a0, 0x30($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X30);
    // 0x800C0E9C: lui         $t5, 0x801D
    ctx->r13 = S32(0X801D << 16);
    // 0x800C0EA0: beq         $t3, $zero, L_800C0F44
    if (ctx->r11 == 0) {
        // 0x800C0EA4: addiu       $a0, $a0, 0x2
        ctx->r4 = ADD32(ctx->r4, 0X2);
            goto L_800C0F44;
    }
    // 0x800C0EA4: addiu       $a0, $a0, 0x2
    ctx->r4 = ADD32(ctx->r4, 0X2);
    // 0x800C0EA8: lb          $t4, 0x14($s0)
    ctx->r12 = MEM_B(ctx->r16, 0X14);
    // 0x800C0EAC: lw          $t5, 0x7E0C($t5)
    ctx->r13 = MEM_W(ctx->r13, 0X7E0C);
    // 0x800C0EB0: andi        $t9, $a0, 0xFF
    ctx->r25 = ctx->r4 & 0XFF;
    // 0x800C0EB4: or          $a0, $t9, $zero
    ctx->r4 = ctx->r25 | 0;
    // 0x800C0EB8: addu        $a1, $t4, $t5
    ctx->r5 = ADD32(ctx->r12, ctx->r13);
    // 0x800C0EBC: andi        $t6, $a1, 0xFF
    ctx->r14 = ctx->r5 & 0XFF;
    // 0x800C0EC0: or          $a1, $t6, $zero
    ctx->r5 = ctx->r14 | 0;
    // 0x800C0EC4: jal         0x800BFFEC
    // 0x800C0EC8: lbu         $a2, 0x13($s0)
    ctx->r6 = MEM_BU(ctx->r16, 0X13);
    func_800BFFEC(rdram, ctx);
        goto after_34;
    // 0x800C0EC8: lbu         $a2, 0x13($s0)
    ctx->r6 = MEM_BU(ctx->r16, 0X13);
    after_34:
    // 0x800C0ECC: b           L_800C0F44
    // 0x800C0ED0: lb          $v0, 0x12($s0)
    ctx->r2 = MEM_B(ctx->r16, 0X12);
        goto L_800C0F44;
    // 0x800C0ED0: lb          $v0, 0x12($s0)
    ctx->r2 = MEM_B(ctx->r16, 0X12);
    // 0x800C0ED4: addiu       $at, $zero, 0x41
    ctx->r1 = ADD32(0, 0X41);
L_800C0ED8:
    // 0x800C0ED8: bne         $v0, $at, L_800C0F1C
    if (ctx->r2 != ctx->r1) {
        // 0x800C0EDC: lw          $a0, 0x30($sp)
        ctx->r4 = MEM_W(ctx->r29, 0X30);
            goto L_800C0F1C;
    }
    // 0x800C0EDC: lw          $a0, 0x30($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X30);
    // 0x800C0EE0: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x800C0EE4: lw          $v0, 0x7E10($v0)
    ctx->r2 = MEM_W(ctx->r2, 0X7E10);
    // 0x800C0EE8: lw          $a0, 0x30($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X30);
    // 0x800C0EEC: beq         $v0, $zero, L_800C105C
    if (ctx->r2 == 0) {
        // 0x800C0EF0: addiu       $a0, $a0, 0x2
        ctx->r4 = ADD32(ctx->r4, 0X2);
            goto L_800C105C;
    }
    // 0x800C0EF0: addiu       $a0, $a0, 0x2
    ctx->r4 = ADD32(ctx->r4, 0X2);
    // 0x800C0EF4: lb          $t8, 0x14($s0)
    ctx->r24 = MEM_B(ctx->r16, 0X14);
    // 0x800C0EF8: andi        $t7, $a0, 0xFF
    ctx->r15 = ctx->r4 & 0XFF;
    // 0x800C0EFC: or          $a0, $t7, $zero
    ctx->r4 = ctx->r15 | 0;
    // 0x800C0F00: addu        $a1, $t8, $v0
    ctx->r5 = ADD32(ctx->r24, ctx->r2);
    // 0x800C0F04: andi        $t3, $a1, 0xFF
    ctx->r11 = ctx->r5 & 0XFF;
    // 0x800C0F08: or          $a1, $t3, $zero
    ctx->r5 = ctx->r11 | 0;
    // 0x800C0F0C: jal         0x800BFFEC
    // 0x800C0F10: lbu         $a2, 0x13($s0)
    ctx->r6 = MEM_BU(ctx->r16, 0X13);
    func_800BFFEC(rdram, ctx);
        goto after_35;
    // 0x800C0F10: lbu         $a2, 0x13($s0)
    ctx->r6 = MEM_BU(ctx->r16, 0X13);
    after_35:
    // 0x800C0F14: b           L_800C0F44
    // 0x800C0F18: lb          $v0, 0x12($s0)
    ctx->r2 = MEM_B(ctx->r16, 0X12);
        goto L_800C0F44;
    // 0x800C0F18: lb          $v0, 0x12($s0)
    ctx->r2 = MEM_B(ctx->r16, 0X12);
L_800C0F1C:
    // 0x800C0F1C: lb          $t4, 0x14($s0)
    ctx->r12 = MEM_B(ctx->r16, 0X14);
    // 0x800C0F20: addiu       $a0, $a0, 0x2
    ctx->r4 = ADD32(ctx->r4, 0X2);
    // 0x800C0F24: andi        $t9, $a0, 0xFF
    ctx->r25 = ctx->r4 & 0XFF;
    // 0x800C0F28: addu        $a1, $v0, $t4
    ctx->r5 = ADD32(ctx->r2, ctx->r12);
    // 0x800C0F2C: andi        $t5, $a1, 0xFF
    ctx->r13 = ctx->r5 & 0XFF;
    // 0x800C0F30: or          $a1, $t5, $zero
    ctx->r5 = ctx->r13 | 0;
    // 0x800C0F34: or          $a0, $t9, $zero
    ctx->r4 = ctx->r25 | 0;
    // 0x800C0F38: jal         0x800BFFEC
    // 0x800C0F3C: lbu         $a2, 0x13($s0)
    ctx->r6 = MEM_BU(ctx->r16, 0X13);
    func_800BFFEC(rdram, ctx);
        goto after_36;
    // 0x800C0F3C: lbu         $a2, 0x13($s0)
    ctx->r6 = MEM_BU(ctx->r16, 0X13);
    after_36:
    // 0x800C0F40: lb          $v0, 0x12($s0)
    ctx->r2 = MEM_B(ctx->r16, 0X12);
L_800C0F44:
    // 0x800C0F44: addiu       $at, $zero, 0x14
    ctx->r1 = ADD32(0, 0X14);
    // 0x800C0F48: bne         $v0, $at, L_800C1044
    if (ctx->r2 != ctx->r1) {
        // 0x800C0F4C: lb          $t6, 0x67($sp)
        ctx->r14 = MEM_B(ctx->r29, 0X67);
            goto L_800C1044;
    }
    // 0x800C0F4C: lb          $t6, 0x67($sp)
    ctx->r14 = MEM_B(ctx->r29, 0X67);
    // 0x800C0F50: bne         $t6, $zero, L_800C0F7C
    if (ctx->r14 != 0) {
        // 0x800C0F54: lui         $t4, 0x800E
        ctx->r12 = S32(0X800E << 16);
            goto L_800C0F7C;
    }
    // 0x800C0F54: lui         $t4, 0x800E
    ctx->r12 = S32(0X800E << 16);
    // 0x800C0F58: lb          $t7, 0x13($s0)
    ctx->r15 = MEM_B(ctx->r16, 0X13);
    // 0x800C0F5C: addiu       $t8, $zero, 0x1
    ctx->r24 = ADD32(0, 0X1);
    // 0x800C0F60: slti        $at, $t7, 0x65
    ctx->r1 = SIGNED(ctx->r15) < 0X65 ? 1 : 0;
    // 0x800C0F64: bne         $at, $zero, L_800C0F7C
    if (ctx->r1 != 0) {
        // 0x800C0F68: lui         $at, 0x800E
        ctx->r1 = S32(0X800E << 16);
            goto L_800C0F7C;
    }
    // 0x800C0F68: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x800C0F6C: sw          $t8, 0x7CB4($at)
    MEM_W(0X7CB4, ctx->r1) = ctx->r24;
    // 0x800C0F70: lb          $t3, 0x14($s0)
    ctx->r11 = MEM_B(ctx->r16, 0X14);
    // 0x800C0F74: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x800C0F78: sw          $t3, 0x7DE0($at)
    MEM_W(0X7DE0, ctx->r1) = ctx->r11;
L_800C0F7C:
    // 0x800C0F7C: lb          $t9, 0x67($sp)
    ctx->r25 = MEM_B(ctx->r29, 0X67);
    // 0x800C0F80: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x800C0F84: bne         $t9, $at, L_800C103C
    if (ctx->r25 != ctx->r1) {
        // 0x800C0F88: nop
    
            goto L_800C103C;
    }
    // 0x800C0F88: nop

    // 0x800C0F8C: lw          $t4, 0x7CB4($t4)
    ctx->r12 = MEM_W(ctx->r12, 0X7CB4);
    // 0x800C0F90: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x800C0F94: beq         $t4, $zero, L_800C103C
    if (ctx->r12 == 0) {
        // 0x800C0F98: nop
    
            goto L_800C103C;
    }
    // 0x800C0F98: nop

    // 0x800C0F9C: lw          $v0, 0x7DE0($v0)
    ctx->r2 = MEM_W(ctx->r2, 0X7DE0);
    // 0x800C0FA0: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x800C0FA4: lui         $t7, 0x8004
    ctx->r15 = S32(0X8004 << 16);
    // 0x800C0FA8: beql        $v0, $zero, L_800C0FDC
    if (ctx->r2 == 0) {
        // 0x800C0FAC: lb          $t5, 0x1B($s0)
        ctx->r13 = MEM_B(ctx->r16, 0X1B);
            goto L_800C0FDC;
    }
    goto skip_39;
    // 0x800C0FAC: lb          $t5, 0x1B($s0)
    ctx->r13 = MEM_B(ctx->r16, 0X1B);
    skip_39:
    // 0x800C0FB0: beq         $v0, $at, L_800C1018
    if (ctx->r2 == ctx->r1) {
        // 0x800C0FB4: lui         $t8, 0x8004
        ctx->r24 = S32(0X8004 << 16);
            goto L_800C1018;
    }
    // 0x800C0FB4: lui         $t8, 0x8004
    ctx->r24 = S32(0X8004 << 16);
    // 0x800C0FB8: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x800C0FBC: beq         $v0, $at, L_800C0FF8
    if (ctx->r2 == ctx->r1) {
        // 0x800C0FC0: lui         $t4, 0x8004
        ctx->r12 = S32(0X8004 << 16);
            goto L_800C0FF8;
    }
    // 0x800C0FC0: lui         $t4, 0x8004
    ctx->r12 = S32(0X8004 << 16);
    // 0x800C0FC4: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x800C0FC8: beql        $v0, $at, L_800C101C
    if (ctx->r2 == ctx->r1) {
        // 0x800C0FCC: lb          $t7, 0x1B($s0)
        ctx->r15 = MEM_B(ctx->r16, 0X1B);
            goto L_800C101C;
    }
    goto skip_40;
    // 0x800C0FCC: lb          $t7, 0x1B($s0)
    ctx->r15 = MEM_B(ctx->r16, 0X1B);
    skip_40:
    // 0x800C0FD0: b           L_800C101C
    // 0x800C0FD4: lb          $t7, 0x1B($s0)
    ctx->r15 = MEM_B(ctx->r16, 0X1B);
        goto L_800C101C;
    // 0x800C0FD4: lb          $t7, 0x1B($s0)
    ctx->r15 = MEM_B(ctx->r16, 0X1B);
    // 0x800C0FD8: lb          $t5, 0x1B($s0)
    ctx->r13 = MEM_B(ctx->r16, 0X1B);
L_800C0FDC:
    // 0x800C0FDC: lw          $t7, 0x562C($t7)
    ctx->r15 = MEM_W(ctx->r15, 0X562C);
    // 0x800C0FE0: sll         $t6, $t5, 2
    ctx->r14 = S32(ctx->r13 << 2);
    // 0x800C0FE4: andi        $t8, $t7, 0x1
    ctx->r24 = ctx->r15 & 0X1;
    // 0x800C0FE8: jal         0x800C3240
    // 0x800C0FEC: addu        $a0, $t6, $t8
    ctx->r4 = ADD32(ctx->r14, ctx->r24);
    func_800C3240(rdram, ctx);
        goto after_37;
    // 0x800C0FEC: addu        $a0, $t6, $t8
    ctx->r4 = ADD32(ctx->r14, ctx->r24);
    after_37:
    // 0x800C0FF0: b           L_800C1034
    // 0x800C0FF4: nop

        goto L_800C1034;
    // 0x800C0FF4: nop

L_800C0FF8:
    // 0x800C0FF8: lb          $t3, 0x1B($s0)
    ctx->r11 = MEM_B(ctx->r16, 0X1B);
    // 0x800C0FFC: lw          $t4, 0x562C($t4)
    ctx->r12 = MEM_W(ctx->r12, 0X562C);
    // 0x800C1000: sll         $t9, $t3, 2
    ctx->r25 = S32(ctx->r11 << 2);
    // 0x800C1004: andi        $t5, $t4, 0x1
    ctx->r13 = ctx->r12 & 0X1;
    // 0x800C1008: jal         0x800C3270
    // 0x800C100C: addu        $a0, $t9, $t5
    ctx->r4 = ADD32(ctx->r25, ctx->r13);
    func_800C3270(rdram, ctx);
        goto after_38;
    // 0x800C100C: addu        $a0, $t9, $t5
    ctx->r4 = ADD32(ctx->r25, ctx->r13);
    after_38:
    // 0x800C1010: b           L_800C1034
    // 0x800C1014: nop

        goto L_800C1034;
    // 0x800C1014: nop

L_800C1018:
    // 0x800C1018: lb          $t7, 0x1B($s0)
    ctx->r15 = MEM_B(ctx->r16, 0X1B);
L_800C101C:
    // 0x800C101C: lw          $t8, 0x562C($t8)
    ctx->r24 = MEM_W(ctx->r24, 0X562C);
    // 0x800C1020: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    // 0x800C1024: sll         $t6, $t7, 2
    ctx->r14 = S32(ctx->r15 << 2);
    // 0x800C1028: andi        $t3, $t8, 0x1
    ctx->r11 = ctx->r24 & 0X1;
    // 0x800C102C: jal         0x800C317C
    // 0x800C1030: addu        $a1, $t6, $t3
    ctx->r5 = ADD32(ctx->r14, ctx->r11);
    func_800C317C(rdram, ctx);
        goto after_39;
    // 0x800C1030: addu        $a1, $t6, $t3
    ctx->r5 = ADD32(ctx->r14, ctx->r11);
    after_39:
L_800C1034:
    // 0x800C1034: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x800C1038: sw          $zero, 0x7CB4($at)
    MEM_W(0X7CB4, ctx->r1) = 0;
L_800C103C:
    // 0x800C103C: b           L_800C1050
    // 0x800C1040: lb          $v0, 0x12($s0)
    ctx->r2 = MEM_B(ctx->r16, 0X12);
        goto L_800C1050;
    // 0x800C1040: lb          $v0, 0x12($s0)
    ctx->r2 = MEM_B(ctx->r16, 0X12);
L_800C1044:
    // 0x800C1044: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x800C1048: sw          $zero, 0x7CB4($at)
    MEM_W(0X7CB4, ctx->r1) = 0;
    // 0x800C104C: lb          $v0, 0x12($s0)
    ctx->r2 = MEM_B(ctx->r16, 0X12);
L_800C1050:
    // 0x800C1050: addiu       $t4, $zero, 0x8
    ctx->r12 = ADD32(0, 0X8);
    // 0x800C1054: sb          $v0, 0x16($s0)
    MEM_B(0X16, ctx->r16) = ctx->r2;
    // 0x800C1058: sh          $t4, 0xC($s0)
    MEM_H(0XC, ctx->r16) = ctx->r12;
L_800C105C:
    // 0x800C105C: sb          $zero, 0x13($s0)
    MEM_B(0X13, ctx->r16) = 0;
    // 0x800C1060: lh          $v0, 0xC($s0)
    ctx->r2 = MEM_H(ctx->r16, 0XC);
L_800C1064:
    // 0x800C1064: beq         $v0, $zero, L_800C1070
    if (ctx->r2 == 0) {
        // 0x800C1068: addiu       $t9, $v0, -0x1
        ctx->r25 = ADD32(ctx->r2, -0X1);
            goto L_800C1070;
    }
    // 0x800C1068: addiu       $t9, $v0, -0x1
    ctx->r25 = ADD32(ctx->r2, -0X1);
    // 0x800C106C: sh          $t9, 0xC($s0)
    MEM_H(0XC, ctx->r16) = ctx->r25;
L_800C1070:
    // 0x800C1070: lb          $t5, 0x17($s0)
    ctx->r13 = MEM_B(ctx->r16, 0X17);
    // 0x800C1074: bnel        $t5, $zero, L_800C10F0
    if (ctx->r13 != 0) {
        // 0x800C1078: lb          $v0, 0x15($s0)
        ctx->r2 = MEM_B(ctx->r16, 0X15);
            goto L_800C10F0;
    }
    goto skip_41;
    // 0x800C1078: lb          $v0, 0x15($s0)
    ctx->r2 = MEM_B(ctx->r16, 0X15);
    skip_41:
    // 0x800C107C: lb          $t7, 0x67($sp)
    ctx->r15 = MEM_B(ctx->r29, 0X67);
    // 0x800C1080: slti        $at, $t7, 0x2
    ctx->r1 = SIGNED(ctx->r15) < 0X2 ? 1 : 0;
    // 0x800C1084: beql        $at, $zero, L_800C10F0
    if (ctx->r1 == 0) {
        // 0x800C1088: lb          $v0, 0x15($s0)
        ctx->r2 = MEM_B(ctx->r16, 0X15);
            goto L_800C10F0;
    }
    goto skip_42;
    // 0x800C1088: lb          $v0, 0x15($s0)
    ctx->r2 = MEM_B(ctx->r16, 0X15);
    skip_42:
    // 0x800C108C: lb          $v0, 0x15($s0)
    ctx->r2 = MEM_B(ctx->r16, 0X15);
    // 0x800C1090: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x800C1094: beql        $v0, $zero, L_800C10F0
    if (ctx->r2 == 0) {
        // 0x800C1098: lb          $v0, 0x15($s0)
        ctx->r2 = MEM_B(ctx->r16, 0X15);
            goto L_800C10F0;
    }
    goto skip_43;
    // 0x800C1098: lb          $v0, 0x15($s0)
    ctx->r2 = MEM_B(ctx->r16, 0X15);
    skip_43:
    // 0x800C109C: bne         $v0, $at, L_800C10CC
    if (ctx->r2 != ctx->r1) {
        // 0x800C10A0: lui         $t3, 0x8004
        ctx->r11 = S32(0X8004 << 16);
            goto L_800C10CC;
    }
    // 0x800C10A0: lui         $t3, 0x8004
    ctx->r11 = S32(0X8004 << 16);
    // 0x800C10A4: lb          $t8, 0x1B($s0)
    ctx->r24 = MEM_B(ctx->r16, 0X1B);
    // 0x800C10A8: lw          $t3, 0x562C($t3)
    ctx->r11 = MEM_W(ctx->r11, 0X562C);
    // 0x800C10AC: or          $a0, $t7, $zero
    ctx->r4 = ctx->r15 | 0;
    // 0x800C10B0: sll         $t6, $t8, 2
    ctx->r14 = S32(ctx->r24 << 2);
    // 0x800C10B4: andi        $t4, $t3, 0x1
    ctx->r12 = ctx->r11 & 0X1;
    // 0x800C10B8: addu        $a1, $t6, $t4
    ctx->r5 = ADD32(ctx->r14, ctx->r12);
    // 0x800C10BC: jal         0x800C317C
    // 0x800C10C0: addiu       $a1, $a1, 0x2
    ctx->r5 = ADD32(ctx->r5, 0X2);
    func_800C317C(rdram, ctx);
        goto after_40;
    // 0x800C10C0: addiu       $a1, $a1, 0x2
    ctx->r5 = ADD32(ctx->r5, 0X2);
    after_40:
    // 0x800C10C4: b           L_800C10F0
    // 0x800C10C8: lb          $v0, 0x15($s0)
    ctx->r2 = MEM_B(ctx->r16, 0X15);
        goto L_800C10F0;
    // 0x800C10C8: lb          $v0, 0x15($s0)
    ctx->r2 = MEM_B(ctx->r16, 0X15);
L_800C10CC:
    // 0x800C10CC: lui         $t7, 0x8004
    ctx->r15 = S32(0X8004 << 16);
    // 0x800C10D0: lw          $t7, 0x562C($t7)
    ctx->r15 = MEM_W(ctx->r15, 0X562C);
    // 0x800C10D4: lb          $t9, 0x1B($s0)
    ctx->r25 = MEM_B(ctx->r16, 0X1B);
    // 0x800C10D8: lb          $a0, 0x67($sp)
    ctx->r4 = MEM_B(ctx->r29, 0X67);
    // 0x800C10DC: andi        $t8, $t7, 0x1
    ctx->r24 = ctx->r15 & 0X1;
    // 0x800C10E0: sll         $t5, $t9, 2
    ctx->r13 = S32(ctx->r25 << 2);
    // 0x800C10E4: jal         0x800C317C
    // 0x800C10E8: addu        $a1, $t5, $t8
    ctx->r5 = ADD32(ctx->r13, ctx->r24);
    func_800C317C(rdram, ctx);
        goto after_41;
    // 0x800C10E8: addu        $a1, $t5, $t8
    ctx->r5 = ADD32(ctx->r13, ctx->r24);
    after_41:
    // 0x800C10EC: lb          $v0, 0x15($s0)
    ctx->r2 = MEM_B(ctx->r16, 0X15);
L_800C10F0:
    // 0x800C10F0: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x800C10F4: bne         $v0, $at, L_800C1108
    if (ctx->r2 != ctx->r1) {
        // 0x800C10F8: sb          $v0, 0x17($s0)
        MEM_B(0X17, ctx->r16) = ctx->r2;
            goto L_800C1108;
    }
    // 0x800C10F8: sb          $v0, 0x17($s0)
    MEM_B(0X17, ctx->r16) = ctx->r2;
    // 0x800C10FC: addiu       $t3, $zero, 0x1
    ctx->r11 = ADD32(0, 0X1);
    // 0x800C1100: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x800C1104: sw          $t3, 0x7CA4($at)
    MEM_W(0X7CA4, ctx->r1) = ctx->r11;
L_800C1108:
    // 0x800C1108: lb          $t6, 0x18($s0)
    ctx->r14 = MEM_B(ctx->r16, 0X18);
    // 0x800C110C: beql        $t6, $zero, L_800C1174
    if (ctx->r14 == 0) {
        // 0x800C1110: lb          $t8, 0x0($s0)
        ctx->r24 = MEM_B(ctx->r16, 0X0);
            goto L_800C1174;
    }
    goto skip_44;
    // 0x800C1110: lb          $t8, 0x0($s0)
    ctx->r24 = MEM_B(ctx->r16, 0X0);
    skip_44:
    // 0x800C1114: lw          $t4, 0x24($sp)
    ctx->r12 = MEM_W(ctx->r29, 0X24);
    // 0x800C1118: lui         $t9, 0x800E
    ctx->r25 = S32(0X800E << 16);
    // 0x800C111C: addiu       $t9, $t9, 0x7CD0
    ctx->r25 = ADD32(ctx->r25, 0X7CD0);
    // 0x800C1120: sltu        $at, $t4, $t9
    ctx->r1 = ctx->r12 < ctx->r25 ? 1 : 0;
    // 0x800C1124: beq         $at, $zero, L_800C1170
    if (ctx->r1 == 0) {
        // 0x800C1128: lw          $a0, 0x30($sp)
        ctx->r4 = MEM_W(ctx->r29, 0X30);
            goto L_800C1170;
    }
    // 0x800C1128: lw          $a0, 0x30($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X30);
    // 0x800C112C: addiu       $a0, $a0, 0x2
    ctx->r4 = ADD32(ctx->r4, 0X2);
    // 0x800C1130: andi        $t7, $a0, 0xFF
    ctx->r15 = ctx->r4 & 0XFF;
    // 0x800C1134: or          $a0, $t7, $zero
    ctx->r4 = ctx->r15 | 0;
    // 0x800C1138: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x800C113C: jal         0x800BFFEC
    // 0x800C1140: addiu       $a2, $zero, 0x7F
    ctx->r6 = ADD32(0, 0X7F);
    func_800BFFEC(rdram, ctx);
        goto after_42;
    // 0x800C1140: addiu       $a2, $zero, 0x7F
    ctx->r6 = ADD32(0, 0X7F);
    after_42:
    // 0x800C1144: lui         $a0, 0x8004
    ctx->r4 = S32(0X8004 << 16);
    // 0x800C1148: lw          $a0, 0x562C($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X562C);
    // 0x800C114C: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x800C1150: addiu       $a1, $zero, 0xA
    ctx->r5 = ADD32(0, 0XA);
    // 0x800C1154: divu        $zero, $a0, $at
    lo = S32(U32(ctx->r4) / U32(ctx->r1)); hi = S32(U32(ctx->r4) % U32(ctx->r1));
    // 0x800C1158: mfhi        $t5
    ctx->r13 = hi;
    // 0x800C115C: addiu       $a0, $t5, 0x50
    ctx->r4 = ADD32(ctx->r13, 0X50);
    // 0x800C1160: addiu       $a2, $zero, 0x50
    ctx->r6 = ADD32(0, 0X50);
    // 0x800C1164: jal         0x800C33C8
    // 0x800C1168: addiu       $a3, $zero, 0x28
    ctx->r7 = ADD32(0, 0X28);
    func_800C33C8(rdram, ctx);
        goto after_43;
    // 0x800C1168: addiu       $a3, $zero, 0x28
    ctx->r7 = ADD32(0, 0X28);
    after_43:
    // 0x800C116C: sb          $zero, 0x18($s0)
    MEM_B(0X18, ctx->r16) = 0;
L_800C1170:
    // 0x800C1170: lb          $t8, 0x0($s0)
    ctx->r24 = MEM_B(ctx->r16, 0X0);
L_800C1174:
    // 0x800C1174: sb          $t8, 0x1F($s0)
    MEM_B(0X1F, ctx->r16) = ctx->r24;
L_800C1178:
    // 0x800C1178: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    // 0x800C117C: lw          $s0, 0x18($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X18);
    // 0x800C1180: addiu       $sp, $sp, 0x60
    ctx->r29 = ADD32(ctx->r29, 0X60);
    // 0x800C1184: jr          $ra
    // 0x800C1188: nop

    return;
    // 0x800C1188: nop

;}
RECOMP_FUNC void func_800C118C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C118C: lui         $t6, 0x800E
    ctx->r14 = S32(0X800E << 16);
    // 0x800C1190: lw          $t6, 0x7CBC($t6)
    ctx->r14 = MEM_W(ctx->r14, 0X7CBC);
    // 0x800C1194: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800C1198: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800C119C: beq         $t6, $zero, L_800C11B4
    if (ctx->r14 == 0) {
        // 0x800C11A0: lui         $t7, 0x800E
        ctx->r15 = S32(0X800E << 16);
            goto L_800C11B4;
    }
    // 0x800C11A0: lui         $t7, 0x800E
    ctx->r15 = S32(0X800E << 16);
    // 0x800C11A4: lb          $t7, 0x7C94($t7)
    ctx->r15 = MEM_B(ctx->r15, 0X7C94);
    // 0x800C11A8: addiu       $at, $zero, 0x4
    ctx->r1 = ADD32(0, 0X4);
    // 0x800C11AC: bnel        $t7, $at, L_800C11C0
    if (ctx->r15 != ctx->r1) {
        // 0x800C11B0: lw          $ra, 0x14($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X14);
            goto L_800C11C0;
    }
    goto skip_0;
    // 0x800C11B0: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    skip_0:
L_800C11B4:
    // 0x800C11B4: jal         0x800C010C
    // 0x800C11B8: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C010C(rdram, ctx);
        goto after_0;
    // 0x800C11B8: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_0:
    // 0x800C11BC: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_800C11C0:
    // 0x800C11C0: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800C11C4: jr          $ra
    // 0x800C11C8: nop

    return;
    // 0x800C11C8: nop

;}
RECOMP_FUNC void func_800C11CC(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C11CC: lui         $t6, 0x800E
    ctx->r14 = S32(0X800E << 16);
    // 0x800C11D0: lw          $t6, 0x7CC0($t6)
    ctx->r14 = MEM_W(ctx->r14, 0X7CC0);
    // 0x800C11D4: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800C11D8: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800C11DC: beq         $t6, $zero, L_800C11F0
    if (ctx->r14 == 0) {
        // 0x800C11E0: lui         $t7, 0x800E
        ctx->r15 = S32(0X800E << 16);
            goto L_800C11F0;
    }
    // 0x800C11E0: lui         $t7, 0x800E
    ctx->r15 = S32(0X800E << 16);
    // 0x800C11E4: lb          $t7, 0x7C94($t7)
    ctx->r15 = MEM_B(ctx->r15, 0X7C94);
    // 0x800C11E8: addiu       $at, $zero, 0x4
    ctx->r1 = ADD32(0, 0X4);
    // 0x800C11EC: bne         $t7, $at, L_800C122C
    if (ctx->r15 != ctx->r1) {
        // 0x800C11F0: lui         $v0, 0x800E
        ctx->r2 = S32(0X800E << 16);
            goto L_800C122C;
    }
L_800C11F0:
    // 0x800C11F0: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x800C11F4: lb          $v0, 0x7C90($v0)
    ctx->r2 = MEM_B(ctx->r2, 0X7C90);
    // 0x800C11F8: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x800C11FC: beq         $v0, $zero, L_800C1214
    if (ctx->r2 == 0) {
        // 0x800C1200: nop
    
            goto L_800C1214;
    }
    // 0x800C1200: nop

    // 0x800C1204: beq         $v0, $at, L_800C1224
    if (ctx->r2 == ctx->r1) {
        // 0x800C1208: nop
    
            goto L_800C1224;
    }
    // 0x800C1208: nop

    // 0x800C120C: b           L_800C1230
    // 0x800C1210: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_800C1230;
    // 0x800C1210: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_800C1214:
    // 0x800C1214: jal         0x800C010C
    // 0x800C1218: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    func_800C010C(rdram, ctx);
        goto after_0;
    // 0x800C1218: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    after_0:
    // 0x800C121C: b           L_800C1230
    // 0x800C1220: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_800C1230;
    // 0x800C1220: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_800C1224:
    // 0x800C1224: jal         0x800C010C
    // 0x800C1228: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    func_800C010C(rdram, ctx);
        goto after_1;
    // 0x800C1228: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    after_1:
L_800C122C:
    // 0x800C122C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_800C1230:
    // 0x800C1230: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800C1234: jr          $ra
    // 0x800C1238: nop

    return;
    // 0x800C1238: nop

;}
RECOMP_FUNC void func_800C123C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C123C: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x800C1240: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x800C1244: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
    // 0x800C1248: addiu       $t6, $zero, 0x3F
    ctx->r14 = ADD32(0, 0X3F);
    // 0x800C124C: sb          $v0, 0x4($a0)
    MEM_B(0X4, ctx->r4) = ctx->r2;
    // 0x800C1250: sb          $v0, 0x5($a0)
    MEM_B(0X5, ctx->r4) = ctx->r2;
    // 0x800C1254: sb          $zero, 0x6($a0)
    MEM_B(0X6, ctx->r4) = 0;
    // 0x800C1258: sb          $t6, 0x7($a0)
    MEM_B(0X7, ctx->r4) = ctx->r14;
    // 0x800C125C: sb          $zero, 0x8($a0)
    MEM_B(0X8, ctx->r4) = 0;
    // 0x800C1260: jr          $ra
    // 0x800C1264: swc1        $f4, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->f4.u32l;
    return;
    // 0x800C1264: swc1        $f4, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->f4.u32l;
;}
RECOMP_FUNC void func_800C1268(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C1268: lui         $t6, 0x800E
    ctx->r14 = S32(0X800E << 16);
    // 0x800C126C: lb          $t6, 0x7C94($t6)
    ctx->r14 = MEM_B(ctx->r14, 0X7C94);
    // 0x800C1270: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800C1274: addiu       $at, $zero, 0x7
    ctx->r1 = ADD32(0, 0X7);
    // 0x800C1278: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800C127C: bne         $t6, $at, L_800C139C
    if (ctx->r14 != ctx->r1) {
        // 0x800C1280: or          $a3, $a0, $zero
        ctx->r7 = ctx->r4 | 0;
            goto L_800C139C;
    }
    // 0x800C1280: or          $a3, $a0, $zero
    ctx->r7 = ctx->r4 | 0;
    // 0x800C1284: lui         $t7, 0x801D
    ctx->r15 = S32(0X801D << 16);
    // 0x800C1288: lw          $t7, 0x7DC4($t7)
    ctx->r15 = MEM_W(ctx->r15, 0X7DC4);
    // 0x800C128C: bnel        $t7, $zero, L_800C13A0
    if (ctx->r15 != 0) {
        // 0x800C1290: lw          $ra, 0x14($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X14);
            goto L_800C13A0;
    }
    goto skip_0;
    // 0x800C1290: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    skip_0:
    // 0x800C1294: lb          $v0, 0x5($a0)
    ctx->r2 = MEM_B(ctx->r4, 0X5);
    // 0x800C1298: lb          $t8, 0x4($a0)
    ctx->r24 = MEM_B(ctx->r4, 0X4);
    // 0x800C129C: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x800C12A0: beql        $t8, $v0, L_800C12EC
    if (ctx->r24 == ctx->r2) {
        // 0x800C12A4: lb          $v0, 0x8($a3)
        ctx->r2 = MEM_B(ctx->r7, 0X8);
            goto L_800C12EC;
    }
    goto skip_1;
    // 0x800C12A4: lb          $v0, 0x8($a3)
    ctx->r2 = MEM_B(ctx->r7, 0X8);
    skip_1:
    // 0x800C12A8: bne         $v0, $at, L_800C12CC
    if (ctx->r2 != ctx->r1) {
        // 0x800C12AC: addiu       $a0, $zero, 0x5
        ctx->r4 = ADD32(0, 0X5);
            goto L_800C12CC;
    }
    // 0x800C12AC: addiu       $a0, $zero, 0x5
    ctx->r4 = ADD32(0, 0X5);
    // 0x800C12B0: addiu       $a0, $zero, 0x5
    ctx->r4 = ADD32(0, 0X5);
    // 0x800C12B4: addiu       $a1, $zero, 0x9
    ctx->r5 = ADD32(0, 0X9);
    // 0x800C12B8: addiu       $a2, $zero, 0x7F
    ctx->r6 = ADD32(0, 0X7F);
    // 0x800C12BC: jal         0x800BFFEC
    // 0x800C12C0: sw          $a3, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r7;
    func_800BFFEC(rdram, ctx);
        goto after_0;
    // 0x800C12C0: sw          $a3, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r7;
    after_0:
    // 0x800C12C4: b           L_800C12E0
    // 0x800C12C8: lw          $a3, 0x18($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X18);
        goto L_800C12E0;
    // 0x800C12C8: lw          $a3, 0x18($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X18);
L_800C12CC:
    // 0x800C12CC: addiu       $a1, $zero, 0x8
    ctx->r5 = ADD32(0, 0X8);
    // 0x800C12D0: addiu       $a2, $zero, 0x7F
    ctx->r6 = ADD32(0, 0X7F);
    // 0x800C12D4: jal         0x800BFFEC
    // 0x800C12D8: sw          $a3, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r7;
    func_800BFFEC(rdram, ctx);
        goto after_1;
    // 0x800C12D8: sw          $a3, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r7;
    after_1:
    // 0x800C12DC: lw          $a3, 0x18($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X18);
L_800C12E0:
    // 0x800C12E0: lb          $t9, 0x5($a3)
    ctx->r25 = MEM_B(ctx->r7, 0X5);
    // 0x800C12E4: sb          $t9, 0x4($a3)
    MEM_B(0X4, ctx->r7) = ctx->r25;
    // 0x800C12E8: lb          $v0, 0x8($a3)
    ctx->r2 = MEM_B(ctx->r7, 0X8);
L_800C12EC:
    // 0x800C12EC: lui         $t0, 0x801D
    ctx->r8 = S32(0X801D << 16);
    // 0x800C12F0: beql        $v0, $zero, L_800C1320
    if (ctx->r2 == 0) {
        // 0x800C12F4: lui         $at, 0x4080
        ctx->r1 = S32(0X4080 << 16);
            goto L_800C1320;
    }
    goto skip_2;
    // 0x800C12F4: lui         $at, 0x4080
    ctx->r1 = S32(0X4080 << 16);
    skip_2:
    // 0x800C12F8: lw          $t0, 0x7DC0($t0)
    ctx->r8 = MEM_W(ctx->r8, 0X7DC0);
    // 0x800C12FC: addiu       $a0, $zero, 0x5
    ctx->r4 = ADD32(0, 0X5);
    // 0x800C1300: andi        $a1, $v0, 0xFF
    ctx->r5 = ctx->r2 & 0XFF;
    // 0x800C1304: bne         $t0, $zero, L_800C131C
    if (ctx->r8 != 0) {
        // 0x800C1308: addiu       $a2, $zero, 0x7F
        ctx->r6 = ADD32(0, 0X7F);
            goto L_800C131C;
    }
    // 0x800C1308: addiu       $a2, $zero, 0x7F
    ctx->r6 = ADD32(0, 0X7F);
    // 0x800C130C: jal         0x800BFFEC
    // 0x800C1310: sw          $a3, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r7;
    func_800BFFEC(rdram, ctx);
        goto after_2;
    // 0x800C1310: sw          $a3, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r7;
    after_2:
    // 0x800C1314: lw          $a3, 0x18($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X18);
    // 0x800C1318: sb          $zero, 0x8($a3)
    MEM_B(0X8, ctx->r7) = 0;
L_800C131C:
    // 0x800C131C: lui         $at, 0x4080
    ctx->r1 = S32(0X4080 << 16);
L_800C1320:
    // 0x800C1320: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x800C1324: lwc1        $f0, 0x0($a3)
    ctx->f0.u32l = MEM_W(ctx->r7, 0X0);
    // 0x800C1328: lui         $at, 0x43FE
    ctx->r1 = S32(0X43FE << 16);
    // 0x800C132C: addiu       $v0, $zero, 0x7F
    ctx->r2 = ADD32(0, 0X7F);
    // 0x800C1330: c.lt.s      $f4, $f0
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    c1cs = ctx->f4.fl < ctx->f0.fl;
    // 0x800C1334: nop

    // 0x800C1338: bc1f        L_800C135C
    if (!c1cs) {
        // 0x800C133C: nop
    
            goto L_800C135C;
    }
    // 0x800C133C: nop

    // 0x800C1340: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x800C1344: nop

    // 0x800C1348: div.s       $f8, $f6, $f0
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f8.fl = DIV_S(ctx->f6.fl, ctx->f0.fl);
    // 0x800C134C: trunc.w.s   $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.u32l = TRUNC_W_S(ctx->f8.fl);
    // 0x800C1350: mfc1        $v0, $f10
    ctx->r2 = (int32_t)ctx->f10.u32l;
    // 0x800C1354: b           L_800C1360
    // 0x800C1358: mtc1        $v0, $f16
    ctx->f16.u32l = ctx->r2;
        goto L_800C1360;
    // 0x800C1358: mtc1        $v0, $f16
    ctx->f16.u32l = ctx->r2;
L_800C135C:
    // 0x800C135C: mtc1        $v0, $f16
    ctx->f16.u32l = ctx->r2;
L_800C1360:
    // 0x800C1360: lui         $at, 0x42FE
    ctx->r1 = S32(0X42FE << 16);
    // 0x800C1364: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x800C1368: cvt.s.w     $f18, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    ctx->f18.fl = CVT_S_W(ctx->f16.u32l);
    // 0x800C136C: lui         $a0, 0x100
    ctx->r4 = S32(0X100 << 16);
    // 0x800C1370: ori         $a0, $a0, 0x500
    ctx->r4 = ctx->r4 | 0X500;
    // 0x800C1374: sw          $a3, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r7;
    // 0x800C1378: div.s       $f6, $f18, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = DIV_S(ctx->f18.fl, ctx->f4.fl);
    // 0x800C137C: mfc1        $a1, $f6
    ctx->r5 = (int32_t)ctx->f6.u32l;
    // 0x800C1380: jal         0x800C538C
    // 0x800C1384: nop

    AudioThread_QueueCmdF32(rdram, ctx);
        goto after_3;
    // 0x800C1384: nop

    after_3:
    // 0x800C1388: lw          $a3, 0x18($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X18);
    // 0x800C138C: lui         $a0, 0x300
    ctx->r4 = S32(0X300 << 16);
    // 0x800C1390: ori         $a0, $a0, 0x500
    ctx->r4 = ctx->r4 | 0X500;
    // 0x800C1394: jal         0x800C53D4
    // 0x800C1398: lb          $a1, 0x7($a3)
    ctx->r5 = MEM_B(ctx->r7, 0X7);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_4;
    // 0x800C1398: lb          $a1, 0x7($a3)
    ctx->r5 = MEM_B(ctx->r7, 0X7);
    after_4:
L_800C139C:
    // 0x800C139C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_800C13A0:
    // 0x800C13A0: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800C13A4: jr          $ra
    // 0x800C13A8: nop

    return;
    // 0x800C13A8: nop

;}
RECOMP_FUNC void func_800C13AC(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C13AC: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x800C13B0: lui         $at, 0x8004
    ctx->r1 = S32(0X8004 << 16);
    // 0x800C13B4: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800C13B8: sb          $a0, -0x331($at)
    MEM_B(-0X331, ctx->r1) = ctx->r4;
    // 0x800C13BC: lui         $a0, 0x8200
    ctx->r4 = S32(0X8200 << 16);
    // 0x800C13C0: jal         0x800C53B0
    // 0x800C13C4: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    AudioThread_QueueCmdS32(rdram, ctx);
        goto after_0;
    // 0x800C13C4: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_0:
    // 0x800C13C8: jal         0x800C5404
    // 0x800C13CC: nop

    AudioThread_ScheduleProcessCmds(rdram, ctx);
        goto after_1;
    // 0x800C13CC: nop

    after_1:
    // 0x800C13D0: lui         $a0, 0x800F
    ctx->r4 = S32(0X800F << 16);
    // 0x800C13D4: lw          $a0, -0x7A08($a0)
    ctx->r4 = MEM_W(ctx->r4, -0X7A08);
    // 0x800C13D8: addiu       $a1, $sp, 0x18
    ctx->r5 = ADD32(ctx->r29, 0X18);
    // 0x800C13DC: jal         0x800C5C60
    // 0x800C13E0: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    osRecvMesg_recomp(rdram, ctx);
        goto after_2;
    // 0x800C13E0: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    after_2:
    // 0x800C13E4: lui         $a0, 0x800F
    ctx->r4 = S32(0X800F << 16);
    // 0x800C13E8: lw          $a0, -0x7A08($a0)
    ctx->r4 = MEM_W(ctx->r4, -0X7A08);
    // 0x800C13EC: addiu       $a1, $sp, 0x18
    ctx->r5 = ADD32(ctx->r29, 0X18);
    // 0x800C13F0: jal         0x800C5C60
    // 0x800C13F4: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    osRecvMesg_recomp(rdram, ctx);
        goto after_3;
    // 0x800C13F4: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    after_3:
    // 0x800C13F8: lui         $a0, 0x800F
    ctx->r4 = S32(0X800F << 16);
    // 0x800C13FC: lw          $a0, -0x7A08($a0)
    ctx->r4 = MEM_W(ctx->r4, -0X7A08);
    // 0x800C1400: addiu       $a1, $sp, 0x18
    ctx->r5 = ADD32(ctx->r29, 0X18);
    // 0x800C1404: jal         0x800C5C60
    // 0x800C1408: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    osRecvMesg_recomp(rdram, ctx);
        goto after_4;
    // 0x800C1408: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    after_4:
    // 0x800C140C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800C1410: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x800C1414: jr          $ra
    // 0x800C1418: nop

    return;
    // 0x800C1418: nop

;}
RECOMP_FUNC void func_800C141C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C141C: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x800C1420: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800C1424: lui         $a0, 0x8200
    ctx->r4 = S32(0X8200 << 16);
    // 0x800C1428: ori         $a0, $a0, 0x200
    ctx->r4 = ctx->r4 | 0X200;
    // 0x800C142C: jal         0x800C53B0
    // 0x800C1430: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    AudioThread_QueueCmdS32(rdram, ctx);
        goto after_0;
    // 0x800C1430: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_0:
    // 0x800C1434: jal         0x800C5404
    // 0x800C1438: nop

    AudioThread_ScheduleProcessCmds(rdram, ctx);
        goto after_1;
    // 0x800C1438: nop

    after_1:
    // 0x800C143C: lui         $a0, 0x800F
    ctx->r4 = S32(0X800F << 16);
    // 0x800C1440: lw          $a0, -0x7A08($a0)
    ctx->r4 = MEM_W(ctx->r4, -0X7A08);
    // 0x800C1444: addiu       $a1, $sp, 0x1C
    ctx->r5 = ADD32(ctx->r29, 0X1C);
    // 0x800C1448: jal         0x800C5C60
    // 0x800C144C: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    osRecvMesg_recomp(rdram, ctx);
        goto after_2;
    // 0x800C144C: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    after_2:
    // 0x800C1450: lui         $a0, 0x800F
    ctx->r4 = S32(0X800F << 16);
    // 0x800C1454: lw          $a0, -0x7A08($a0)
    ctx->r4 = MEM_W(ctx->r4, -0X7A08);
    // 0x800C1458: addiu       $a1, $sp, 0x1C
    ctx->r5 = ADD32(ctx->r29, 0X1C);
    // 0x800C145C: jal         0x800C5C60
    // 0x800C1460: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    osRecvMesg_recomp(rdram, ctx);
        goto after_3;
    // 0x800C1460: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    after_3:
    // 0x800C1464: lui         $a0, 0x800F
    ctx->r4 = S32(0X800F << 16);
    // 0x800C1468: lw          $a0, -0x7A08($a0)
    ctx->r4 = MEM_W(ctx->r4, -0X7A08);
    // 0x800C146C: addiu       $a1, $sp, 0x1C
    ctx->r5 = ADD32(ctx->r29, 0X1C);
    // 0x800C1470: jal         0x800C5C60
    // 0x800C1474: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    osRecvMesg_recomp(rdram, ctx);
        goto after_4;
    // 0x800C1474: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    after_4:
    // 0x800C1478: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800C147C: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x800C1480: jr          $ra
    // 0x800C1484: nop

    return;
    // 0x800C1484: nop

;}
RECOMP_FUNC void func_800C1488(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C1488: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800C148C: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800C1490: lui         $a0, 0x8300
    ctx->r4 = S32(0X8300 << 16);
    // 0x800C1494: jal         0x800C53B0
    // 0x800C1498: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    AudioThread_QueueCmdS32(rdram, ctx);
        goto after_0;
    // 0x800C1498: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_0:
    // 0x800C149C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800C14A0: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800C14A4: jr          $ra
    // 0x800C14A8: nop

    return;
    // 0x800C14A8: nop

;}
RECOMP_FUNC void func_800C14AC(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C14AC: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800C14B0: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800C14B4: lui         $a0, 0x8300
    ctx->r4 = S32(0X8300 << 16);
    // 0x800C14B8: jal         0x800C53B0
    // 0x800C14BC: addiu       $a1, $zero, 0xB4
    ctx->r5 = ADD32(0, 0XB4);
    AudioThread_QueueCmdS32(rdram, ctx);
        goto after_0;
    // 0x800C14BC: addiu       $a1, $zero, 0xB4
    ctx->r5 = ADD32(0, 0XB4);
    after_0:
    // 0x800C14C0: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800C14C4: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800C14C8: jr          $ra
    // 0x800C14CC: nop

    return;
    // 0x800C14CC: nop

;}
RECOMP_FUNC void func_800C14D0(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C14D0: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800C14D4: andi        $a0, $a0, 0xFF
    ctx->r4 = ctx->r4 & 0XFF;
    // 0x800C14D8: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800C14DC: sll         $t6, $a0, 8
    ctx->r14 = S32(ctx->r4 << 8);
    // 0x800C14E0: lui         $at, 0x8100
    ctx->r1 = S32(0X8100 << 16);
    // 0x800C14E4: or          $a0, $t6, $at
    ctx->r4 = ctx->r14 | ctx->r1;
    // 0x800C14E8: jal         0x800C53B0
    // 0x800C14EC: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    AudioThread_QueueCmdS32(rdram, ctx);
        goto after_0;
    // 0x800C14EC: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_0:
    // 0x800C14F0: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800C14F4: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800C14F8: jr          $ra
    // 0x800C14FC: nop

    return;
    // 0x800C14FC: nop

;}
RECOMP_FUNC void func_800C1500(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C1500: andi        $a0, $a0, 0xFF
    ctx->r4 = ctx->r4 & 0XFF;
    // 0x800C1504: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800C1508: sll         $t6, $a0, 8
    ctx->r14 = S32(ctx->r4 << 8);
    // 0x800C150C: lui         $at, 0x8201
    ctx->r1 = S32(0X8201 << 16);
    // 0x800C1510: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800C1514: or          $t7, $t6, $at
    ctx->r15 = ctx->r14 | ctx->r1;
    // 0x800C1518: jal         0x800C53B0
    // 0x800C151C: ori         $a0, $t7, 0x1
    ctx->r4 = ctx->r15 | 0X1;
    AudioThread_QueueCmdS32(rdram, ctx);
        goto after_0;
    // 0x800C151C: ori         $a0, $t7, 0x1
    ctx->r4 = ctx->r15 | 0X1;
    after_0:
    // 0x800C1520: lui         $a1, 0x3F0C
    ctx->r5 = S32(0X3F0C << 16);
    // 0x800C1524: ori         $a1, $a1, 0xCCCD
    ctx->r5 = ctx->r5 | 0XCCCD;
    // 0x800C1528: jal         0x800C538C
    // 0x800C152C: lui         $a0, 0x4101
    ctx->r4 = S32(0X4101 << 16);
    AudioThread_QueueCmdF32(rdram, ctx);
        goto after_1;
    // 0x800C152C: lui         $a0, 0x4101
    ctx->r4 = S32(0X4101 << 16);
    after_1:
    // 0x800C1530: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800C1534: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800C1538: jr          $ra
    // 0x800C153C: nop

    return;
    // 0x800C153C: nop

;}
RECOMP_FUNC void func_800C1540(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C1540: lui         $at, 0x8004
    ctx->r1 = S32(0X8004 << 16);
    // 0x800C1544: sb          $a2, -0xB1($at)
    MEM_B(-0XB1, ctx->r1) = ctx->r6;
    // 0x800C1548: andi        $a0, $a0, 0xFF
    ctx->r4 = ctx->r4 & 0XFF;
    // 0x800C154C: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800C1550: sll         $t6, $a0, 8
    ctx->r14 = S32(ctx->r4 << 8);
    // 0x800C1554: lui         $at, 0x8202
    ctx->r1 = S32(0X8202 << 16);
    // 0x800C1558: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800C155C: or          $t7, $t6, $at
    ctx->r15 = ctx->r14 | ctx->r1;
    // 0x800C1560: jal         0x800C53B0
    // 0x800C1564: ori         $a0, $t7, 0x1
    ctx->r4 = ctx->r15 | 0X1;
    AudioThread_QueueCmdS32(rdram, ctx);
        goto after_0;
    // 0x800C1564: ori         $a0, $t7, 0x1
    ctx->r4 = ctx->r15 | 0X1;
    after_0:
    // 0x800C1568: lui         $a1, 0x3F0C
    ctx->r5 = S32(0X3F0C << 16);
    // 0x800C156C: ori         $a1, $a1, 0xCCCD
    ctx->r5 = ctx->r5 | 0XCCCD;
    // 0x800C1570: jal         0x800C538C
    // 0x800C1574: lui         $a0, 0x4102
    ctx->r4 = S32(0X4102 << 16);
    AudioThread_QueueCmdF32(rdram, ctx);
        goto after_1;
    // 0x800C1574: lui         $a0, 0x4102
    ctx->r4 = S32(0X4102 << 16);
    after_1:
    // 0x800C1578: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800C157C: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800C1580: jr          $ra
    // 0x800C1584: nop

    return;
    // 0x800C1584: nop

;}
RECOMP_FUNC void func_800C1588(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C1588: andi        $a0, $a0, 0xFF
    ctx->r4 = ctx->r4 & 0XFF;
    // 0x800C158C: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800C1590: sll         $t6, $a0, 8
    ctx->r14 = S32(ctx->r4 << 8);
    // 0x800C1594: lui         $at, 0x8202
    ctx->r1 = S32(0X8202 << 16);
    // 0x800C1598: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800C159C: or          $t7, $t6, $at
    ctx->r15 = ctx->r14 | ctx->r1;
    // 0x800C15A0: jal         0x800C53B0
    // 0x800C15A4: ori         $a0, $t7, 0x1
    ctx->r4 = ctx->r15 | 0X1;
    AudioThread_QueueCmdS32(rdram, ctx);
        goto after_0;
    // 0x800C15A4: ori         $a0, $t7, 0x1
    ctx->r4 = ctx->r15 | 0X1;
    after_0:
    // 0x800C15A8: lui         $a1, 0x3F0C
    ctx->r5 = S32(0X3F0C << 16);
    // 0x800C15AC: ori         $a1, $a1, 0xCCCD
    ctx->r5 = ctx->r5 | 0XCCCD;
    // 0x800C15B0: jal         0x800C538C
    // 0x800C15B4: lui         $a0, 0x4102
    ctx->r4 = S32(0X4102 << 16);
    AudioThread_QueueCmdF32(rdram, ctx);
        goto after_1;
    // 0x800C15B4: lui         $a0, 0x4102
    ctx->r4 = S32(0X4102 << 16);
    after_1:
    // 0x800C15B8: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800C15BC: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800C15C0: jr          $ra
    // 0x800C15C4: nop

    return;
    // 0x800C15C4: nop

;}
RECOMP_FUNC void func_800C15C8(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C15C8: andi        $a0, $a0, 0xFF
    ctx->r4 = ctx->r4 & 0XFF;
    // 0x800C15CC: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800C15D0: sll         $t6, $a0, 8
    ctx->r14 = S32(ctx->r4 << 8);
    // 0x800C15D4: lui         $at, 0x8203
    ctx->r1 = S32(0X8203 << 16);
    // 0x800C15D8: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800C15DC: or          $t7, $t6, $at
    ctx->r15 = ctx->r14 | ctx->r1;
    // 0x800C15E0: jal         0x800C53B0
    // 0x800C15E4: ori         $a0, $t7, 0x1
    ctx->r4 = ctx->r15 | 0X1;
    AudioThread_QueueCmdS32(rdram, ctx);
        goto after_0;
    // 0x800C15E4: ori         $a0, $t7, 0x1
    ctx->r4 = ctx->r15 | 0X1;
    after_0:
    // 0x800C15E8: lui         $a1, 0x3F33
    ctx->r5 = S32(0X3F33 << 16);
    // 0x800C15EC: ori         $a1, $a1, 0x3333
    ctx->r5 = ctx->r5 | 0X3333;
    // 0x800C15F0: jal         0x800C538C
    // 0x800C15F4: lui         $a0, 0x4103
    ctx->r4 = S32(0X4103 << 16);
    AudioThread_QueueCmdF32(rdram, ctx);
        goto after_1;
    // 0x800C15F4: lui         $a0, 0x4103
    ctx->r4 = S32(0X4103 << 16);
    after_1:
    // 0x800C15F8: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800C15FC: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800C1600: jr          $ra
    // 0x800C1604: nop

    return;
    // 0x800C1604: nop

;}
RECOMP_FUNC void func_800C1608(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C1608: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800C160C: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800C1610: or          $a1, $a0, $zero
    ctx->r5 = ctx->r4 | 0;
    // 0x800C1614: jal         0x800C53B0
    // 0x800C1618: lui         $a0, 0x8303
    ctx->r4 = S32(0X8303 << 16);
    AudioThread_QueueCmdS32(rdram, ctx);
        goto after_0;
    // 0x800C1618: lui         $a0, 0x8303
    ctx->r4 = S32(0X8303 << 16);
    after_0:
    // 0x800C161C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800C1620: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800C1624: jr          $ra
    // 0x800C1628: nop

    return;
    // 0x800C1628: nop

;}
RECOMP_FUNC void func_800C162C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C162C: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800C1630: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800C1634: or          $a1, $a0, $zero
    ctx->r5 = ctx->r4 | 0;
    // 0x800C1638: jal         0x800C53B0
    // 0x800C163C: lui         $a0, 0x8300
    ctx->r4 = S32(0X8300 << 16);
    AudioThread_QueueCmdS32(rdram, ctx);
        goto after_0;
    // 0x800C163C: lui         $a0, 0x8300
    ctx->r4 = S32(0X8300 << 16);
    after_0:
    // 0x800C1640: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800C1644: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800C1648: jr          $ra
    // 0x800C164C: nop

    return;
    // 0x800C164C: nop

;}
RECOMP_FUNC void func_800C1650(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C1650: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800C1654: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800C1658: or          $a1, $a0, $zero
    ctx->r5 = ctx->r4 | 0;
    // 0x800C165C: jal         0x800C53B0
    // 0x800C1660: lui         $a0, 0x8301
    ctx->r4 = S32(0X8301 << 16);
    AudioThread_QueueCmdS32(rdram, ctx);
        goto after_0;
    // 0x800C1660: lui         $a0, 0x8301
    ctx->r4 = S32(0X8301 << 16);
    after_0:
    // 0x800C1664: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800C1668: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800C166C: jr          $ra
    // 0x800C1670: nop

    return;
    // 0x800C1670: nop

;}
RECOMP_FUNC void AudioGeneral_DisableSeqPlayer2(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C1674: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800C1678: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800C167C: or          $a1, $a0, $zero
    ctx->r5 = ctx->r4 | 0;
    // 0x800C1680: jal         0x800C53B0
    // 0x800C1684: lui         $a0, 0x8302
    ctx->r4 = S32(0X8302 << 16);
    AudioThread_QueueCmdS32(rdram, ctx);
        goto after_0;
    // 0x800C1684: lui         $a0, 0x8302
    ctx->r4 = S32(0X8302 << 16);
    after_0:
    // 0x800C1688: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800C168C: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800C1690: jr          $ra
    // 0x800C1694: nop

    return;
    // 0x800C1694: nop

;}
RECOMP_FUNC void func_800C1698(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C1698: addiu       $sp, $sp, -0x28
    ctx->r29 = ADD32(ctx->r29, -0X28);
    // 0x800C169C: sw          $s2, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r18;
    // 0x800C16A0: sw          $s1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r17;
    // 0x800C16A4: sw          $s0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r16;
    // 0x800C16A8: sw          $ra, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r31;
    // 0x800C16AC: or          $s0, $zero, $zero
    ctx->r16 = 0 | 0;
    // 0x800C16B0: lui         $s1, 0x8300
    ctx->r17 = S32(0X8300 << 16);
    // 0x800C16B4: addiu       $s2, $zero, 0x4
    ctx->r18 = ADD32(0, 0X4);
    // 0x800C16B8: andi        $t6, $s0, 0xFF
    ctx->r14 = ctx->r16 & 0XFF;
L_800C16BC:
    // 0x800C16BC: sll         $t7, $t6, 16
    ctx->r15 = S32(ctx->r14 << 16);
    // 0x800C16C0: or          $a0, $t7, $s1
    ctx->r4 = ctx->r15 | ctx->r17;
    // 0x800C16C4: jal         0x800C53B0
    // 0x800C16C8: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    AudioThread_QueueCmdS32(rdram, ctx);
        goto after_0;
    // 0x800C16C8: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_0:
    // 0x800C16CC: addiu       $s0, $s0, 0x1
    ctx->r16 = ADD32(ctx->r16, 0X1);
    // 0x800C16D0: bnel        $s0, $s2, L_800C16BC
    if (ctx->r16 != ctx->r18) {
        // 0x800C16D4: andi        $t6, $s0, 0xFF
        ctx->r14 = ctx->r16 & 0XFF;
            goto L_800C16BC;
    }
    goto skip_0;
    // 0x800C16D4: andi        $t6, $s0, 0xFF
    ctx->r14 = ctx->r16 & 0XFF;
    skip_0:
    // 0x800C16D8: lw          $ra, 0x24($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X24);
    // 0x800C16DC: lw          $s0, 0x18($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X18);
    // 0x800C16E0: lw          $s1, 0x1C($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X1C);
    // 0x800C16E4: lw          $s2, 0x20($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X20);
    // 0x800C16E8: jr          $ra
    // 0x800C16EC: addiu       $sp, $sp, 0x28
    ctx->r29 = ADD32(ctx->r29, 0X28);
    return;
    // 0x800C16EC: addiu       $sp, $sp, 0x28
    ctx->r29 = ADD32(ctx->r29, 0X28);
;}
RECOMP_FUNC void func_800C16F0(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C16F0: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800C16F4: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800C16F8: lui         $a0, 0xF200
    ctx->r4 = S32(0XF200 << 16);
    // 0x800C16FC: jal         0x800C53B0
    // 0x800C1700: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    AudioThread_QueueCmdS32(rdram, ctx);
        goto after_0;
    // 0x800C1700: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_0:
    // 0x800C1704: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800C1708: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800C170C: jr          $ra
    // 0x800C1710: nop

    return;
    // 0x800C1710: nop

;}
RECOMP_FUNC void func_800C1714(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C1714: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x800C1718: sw          $a0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r4;
    // 0x800C171C: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800C1720: lui         $a0, 0x800F
    ctx->r4 = S32(0X800F << 16);
    // 0x800C1724: lw          $a0, -0x79FC($a0)
    ctx->r4 = MEM_W(ctx->r4, -0X79FC);
    // 0x800C1728: addiu       $a1, $sp, 0x1C
    ctx->r5 = ADD32(ctx->r29, 0X1C);
    // 0x800C172C: jal         0x800C5C60
    // 0x800C1730: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    osRecvMesg_recomp(rdram, ctx);
        goto after_0;
    // 0x800C1730: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    after_0:
    // 0x800C1734: lui         $a0, 0x800F
    ctx->r4 = S32(0X800F << 16);
    // 0x800C1738: lw          $a0, -0x7A00($a0)
    ctx->r4 = MEM_W(ctx->r4, -0X7A00);
    // 0x800C173C: lw          $a1, 0x20($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X20);
    // 0x800C1740: jal         0x800C57A0
    // 0x800C1744: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    osSendMesg_recomp(rdram, ctx);
        goto after_1;
    // 0x800C1744: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    after_1:
    // 0x800C1748: lui         $a0, 0x800F
    ctx->r4 = S32(0X800F << 16);
    // 0x800C174C: lw          $a0, -0x79FC($a0)
    ctx->r4 = MEM_W(ctx->r4, -0X79FC);
    // 0x800C1750: addiu       $a1, $sp, 0x1C
    ctx->r5 = ADD32(ctx->r29, 0X1C);
    // 0x800C1754: jal         0x800C5C60
    // 0x800C1758: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    osRecvMesg_recomp(rdram, ctx);
        goto after_2;
    // 0x800C1758: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    after_2:
    // 0x800C175C: lw          $t6, 0x1C($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X1C);
    // 0x800C1760: lw          $t7, 0x20($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X20);
    // 0x800C1764: lui         $a0, 0x800F
    ctx->r4 = S32(0X800F << 16);
    // 0x800C1768: addiu       $a1, $sp, 0x1C
    ctx->r5 = ADD32(ctx->r29, 0X1C);
    // 0x800C176C: beq         $t6, $t7, L_800C177C
    if (ctx->r14 == ctx->r15) {
        // 0x800C1770: addiu       $a2, $zero, 0x1
        ctx->r6 = ADD32(0, 0X1);
            goto L_800C177C;
    }
    // 0x800C1770: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    // 0x800C1774: jal         0x800C5C60
    // 0x800C1778: lw          $a0, -0x79FC($a0)
    ctx->r4 = MEM_W(ctx->r4, -0X79FC);
    osRecvMesg_recomp(rdram, ctx);
        goto after_3;
    // 0x800C1778: lw          $a0, -0x79FC($a0)
    ctx->r4 = MEM_W(ctx->r4, -0X79FC);
    after_3:
L_800C177C:
    // 0x800C177C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800C1780: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x800C1784: jr          $ra
    // 0x800C1788: nop

    return;
    // 0x800C1788: nop

;}
RECOMP_FUNC void func_800C178C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C178C: lui         $t6, 0x8004
    ctx->r14 = S32(0X8004 << 16);
    // 0x800C1790: lw          $t6, -0xB8($t6)
    ctx->r14 = MEM_W(ctx->r14, -0XB8);
    // 0x800C1794: lui         $v1, 0x8004
    ctx->r3 = S32(0X8004 << 16);
    // 0x800C1798: addiu       $v1, $v1, -0x338
    ctx->r3 = ADD32(ctx->r3, -0X338);
    // 0x800C179C: srl         $t7, $t6, 31
    ctx->r15 = S32(U32(ctx->r14) >> 31);
    // 0x800C17A0: beq         $t7, $zero, L_800C1800
    if (ctx->r15 == 0) {
        // 0x800C17A4: lui         $a1, 0x8004
        ctx->r5 = S32(0X8004 << 16);
            goto L_800C1800;
    }
    // 0x800C17A4: lui         $a1, 0x8004
    ctx->r5 = S32(0X8004 << 16);
    // 0x800C17A8: lui         $a0, 0x8004
    ctx->r4 = S32(0X8004 << 16);
    // 0x800C17AC: addiu       $a0, $a0, 0x4688
    ctx->r4 = ADD32(ctx->r4, 0X4688);
    // 0x800C17B0: addiu       $a1, $a1, -0x2F8
    ctx->r5 = ADD32(ctx->r5, -0X2F8);
    // 0x800C17B4: lw          $v0, 0x2B0($v1)
    ctx->r2 = MEM_W(ctx->r3, 0X2B0);
L_800C17B8:
    // 0x800C17B8: beql        $v0, $a0, L_800C17C8
    if (ctx->r2 == ctx->r4) {
        // 0x800C17BC: lw          $v0, 0x2B4($v1)
        ctx->r2 = MEM_W(ctx->r3, 0X2B4);
            goto L_800C17C8;
    }
    goto skip_0;
    // 0x800C17BC: lw          $v0, 0x2B4($v1)
    ctx->r2 = MEM_W(ctx->r3, 0X2B4);
    skip_0:
    // 0x800C17C0: swc1        $f12, 0x30($v0)
    MEM_W(0X30, ctx->r2) = ctx->f12.u32l;
    // 0x800C17C4: lw          $v0, 0x2B4($v1)
    ctx->r2 = MEM_W(ctx->r3, 0X2B4);
L_800C17C8:
    // 0x800C17C8: beql        $v0, $a0, L_800C17D8
    if (ctx->r2 == ctx->r4) {
        // 0x800C17CC: lw          $v0, 0x2B8($v1)
        ctx->r2 = MEM_W(ctx->r3, 0X2B8);
            goto L_800C17D8;
    }
    goto skip_1;
    // 0x800C17CC: lw          $v0, 0x2B8($v1)
    ctx->r2 = MEM_W(ctx->r3, 0X2B8);
    skip_1:
    // 0x800C17D0: swc1        $f12, 0x30($v0)
    MEM_W(0X30, ctx->r2) = ctx->f12.u32l;
    // 0x800C17D4: lw          $v0, 0x2B8($v1)
    ctx->r2 = MEM_W(ctx->r3, 0X2B8);
L_800C17D8:
    // 0x800C17D8: beql        $v0, $a0, L_800C17E8
    if (ctx->r2 == ctx->r4) {
        // 0x800C17DC: lw          $v0, 0x2BC($v1)
        ctx->r2 = MEM_W(ctx->r3, 0X2BC);
            goto L_800C17E8;
    }
    goto skip_2;
    // 0x800C17DC: lw          $v0, 0x2BC($v1)
    ctx->r2 = MEM_W(ctx->r3, 0X2BC);
    skip_2:
    // 0x800C17E0: swc1        $f12, 0x30($v0)
    MEM_W(0X30, ctx->r2) = ctx->f12.u32l;
    // 0x800C17E4: lw          $v0, 0x2BC($v1)
    ctx->r2 = MEM_W(ctx->r3, 0X2BC);
L_800C17E8:
    // 0x800C17E8: addiu       $v1, $v1, 0x10
    ctx->r3 = ADD32(ctx->r3, 0X10);
    // 0x800C17EC: beq         $v0, $a0, L_800C17F8
    if (ctx->r2 == ctx->r4) {
        // 0x800C17F0: nop
    
            goto L_800C17F8;
    }
    // 0x800C17F0: nop

    // 0x800C17F4: swc1        $f12, 0x30($v0)
    MEM_W(0X30, ctx->r2) = ctx->f12.u32l;
L_800C17F8:
    // 0x800C17F8: bnel        $v1, $a1, L_800C17B8
    if (ctx->r3 != ctx->r5) {
        // 0x800C17FC: lw          $v0, 0x2B0($v1)
        ctx->r2 = MEM_W(ctx->r3, 0X2B0);
            goto L_800C17B8;
    }
    goto skip_3;
    // 0x800C17FC: lw          $v0, 0x2B0($v1)
    ctx->r2 = MEM_W(ctx->r3, 0X2B0);
    skip_3:
L_800C1800:
    // 0x800C1800: jr          $ra
    // 0x800C1804: nop

    return;
    // 0x800C1804: nop

;}
RECOMP_FUNC void func_800C1808(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C1808: lui         $t6, 0x8004
    ctx->r14 = S32(0X8004 << 16);
    // 0x800C180C: lw          $t6, -0xB8($t6)
    ctx->r14 = MEM_W(ctx->r14, -0XB8);
    // 0x800C1810: lui         $v1, 0x8004
    ctx->r3 = S32(0X8004 << 16);
    // 0x800C1814: addiu       $v1, $v1, -0x338
    ctx->r3 = ADD32(ctx->r3, -0X338);
    // 0x800C1818: srl         $t7, $t6, 31
    ctx->r15 = S32(U32(ctx->r14) >> 31);
    // 0x800C181C: beq         $t7, $zero, L_800C187C
    if (ctx->r15 == 0) {
        // 0x800C1820: lui         $a1, 0x8004
        ctx->r5 = S32(0X8004 << 16);
            goto L_800C187C;
    }
    // 0x800C1820: lui         $a1, 0x8004
    ctx->r5 = S32(0X8004 << 16);
    // 0x800C1824: lui         $a0, 0x8004
    ctx->r4 = S32(0X8004 << 16);
    // 0x800C1828: addiu       $a0, $a0, 0x4688
    ctx->r4 = ADD32(ctx->r4, 0X4688);
    // 0x800C182C: addiu       $a1, $a1, -0x2F8
    ctx->r5 = ADD32(ctx->r5, -0X2F8);
    // 0x800C1830: lw          $v0, 0x2B0($v1)
    ctx->r2 = MEM_W(ctx->r3, 0X2B0);
L_800C1834:
    // 0x800C1834: beql        $v0, $a0, L_800C1844
    if (ctx->r2 == ctx->r4) {
        // 0x800C1838: lw          $v0, 0x2B4($v1)
        ctx->r2 = MEM_W(ctx->r3, 0X2B4);
            goto L_800C1844;
    }
    goto skip_0;
    // 0x800C1838: lw          $v0, 0x2B4($v1)
    ctx->r2 = MEM_W(ctx->r3, 0X2B4);
    skip_0:
    // 0x800C183C: swc1        $f12, 0x20($v0)
    MEM_W(0X20, ctx->r2) = ctx->f12.u32l;
    // 0x800C1840: lw          $v0, 0x2B4($v1)
    ctx->r2 = MEM_W(ctx->r3, 0X2B4);
L_800C1844:
    // 0x800C1844: beql        $v0, $a0, L_800C1854
    if (ctx->r2 == ctx->r4) {
        // 0x800C1848: lw          $v0, 0x2B8($v1)
        ctx->r2 = MEM_W(ctx->r3, 0X2B8);
            goto L_800C1854;
    }
    goto skip_1;
    // 0x800C1848: lw          $v0, 0x2B8($v1)
    ctx->r2 = MEM_W(ctx->r3, 0X2B8);
    skip_1:
    // 0x800C184C: swc1        $f12, 0x20($v0)
    MEM_W(0X20, ctx->r2) = ctx->f12.u32l;
    // 0x800C1850: lw          $v0, 0x2B8($v1)
    ctx->r2 = MEM_W(ctx->r3, 0X2B8);
L_800C1854:
    // 0x800C1854: beql        $v0, $a0, L_800C1864
    if (ctx->r2 == ctx->r4) {
        // 0x800C1858: lw          $v0, 0x2BC($v1)
        ctx->r2 = MEM_W(ctx->r3, 0X2BC);
            goto L_800C1864;
    }
    goto skip_2;
    // 0x800C1858: lw          $v0, 0x2BC($v1)
    ctx->r2 = MEM_W(ctx->r3, 0X2BC);
    skip_2:
    // 0x800C185C: swc1        $f12, 0x20($v0)
    MEM_W(0X20, ctx->r2) = ctx->f12.u32l;
    // 0x800C1860: lw          $v0, 0x2BC($v1)
    ctx->r2 = MEM_W(ctx->r3, 0X2BC);
L_800C1864:
    // 0x800C1864: addiu       $v1, $v1, 0x10
    ctx->r3 = ADD32(ctx->r3, 0X10);
    // 0x800C1868: beq         $v0, $a0, L_800C1874
    if (ctx->r2 == ctx->r4) {
        // 0x800C186C: nop
    
            goto L_800C1874;
    }
    // 0x800C186C: nop

    // 0x800C1870: swc1        $f12, 0x20($v0)
    MEM_W(0X20, ctx->r2) = ctx->f12.u32l;
L_800C1874:
    // 0x800C1874: bnel        $v1, $a1, L_800C1834
    if (ctx->r3 != ctx->r5) {
        // 0x800C1878: lw          $v0, 0x2B0($v1)
        ctx->r2 = MEM_W(ctx->r3, 0X2B0);
            goto L_800C1834;
    }
    goto skip_3;
    // 0x800C1878: lw          $v0, 0x2B0($v1)
    ctx->r2 = MEM_W(ctx->r3, 0X2B0);
    skip_3:
L_800C187C:
    // 0x800C187C: jr          $ra
    // 0x800C1880: nop

    return;
    // 0x800C1880: nop

;}
RECOMP_FUNC void func_800C1884(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C1884: lui         $at, 0x3F00
    ctx->r1 = S32(0X3F00 << 16);
    // 0x800C1888: lui         $v1, 0x8004
    ctx->r3 = S32(0X8004 << 16);
    // 0x800C188C: lui         $a2, 0x8004
    ctx->r6 = S32(0X8004 << 16);
    // 0x800C1890: lui         $a1, 0x8004
    ctx->r5 = S32(0X8004 << 16);
    // 0x800C1894: mtc1        $at, $f0
    ctx->f0.u32l = ctx->r1;
    // 0x800C1898: addiu       $a1, $a1, 0x4688
    ctx->r5 = ADD32(ctx->r5, 0X4688);
    // 0x800C189C: addiu       $a2, $a2, -0x2F8
    ctx->r6 = ADD32(ctx->r6, -0X2F8);
    // 0x800C18A0: addiu       $v1, $v1, -0x338
    ctx->r3 = ADD32(ctx->r3, -0X338);
L_800C18A4:
    // 0x800C18A4: lw          $v0, 0x2B0($v1)
    ctx->r2 = MEM_W(ctx->r3, 0X2B0);
    // 0x800C18A8: beql        $v0, $a1, L_800C18B8
    if (ctx->r2 == ctx->r5) {
        // 0x800C18AC: swc1        $f0, 0x20($v0)
        MEM_W(0X20, ctx->r2) = ctx->f0.u32l;
            goto L_800C18B8;
    }
    goto skip_0;
    // 0x800C18AC: swc1        $f0, 0x20($v0)
    MEM_W(0X20, ctx->r2) = ctx->f0.u32l;
    skip_0:
    // 0x800C18B0: sb          $a0, 0x8($v0)
    MEM_B(0X8, ctx->r2) = ctx->r4;
    // 0x800C18B4: swc1        $f0, 0x20($v0)
    MEM_W(0X20, ctx->r2) = ctx->f0.u32l;
L_800C18B8:
    // 0x800C18B8: lw          $v0, 0x2B4($v1)
    ctx->r2 = MEM_W(ctx->r3, 0X2B4);
    // 0x800C18BC: beql        $v0, $a1, L_800C18CC
    if (ctx->r2 == ctx->r5) {
        // 0x800C18C0: swc1        $f0, 0x20($v0)
        MEM_W(0X20, ctx->r2) = ctx->f0.u32l;
            goto L_800C18CC;
    }
    goto skip_1;
    // 0x800C18C0: swc1        $f0, 0x20($v0)
    MEM_W(0X20, ctx->r2) = ctx->f0.u32l;
    skip_1:
    // 0x800C18C4: sb          $a0, 0x8($v0)
    MEM_B(0X8, ctx->r2) = ctx->r4;
    // 0x800C18C8: swc1        $f0, 0x20($v0)
    MEM_W(0X20, ctx->r2) = ctx->f0.u32l;
L_800C18CC:
    // 0x800C18CC: lw          $v0, 0x2B8($v1)
    ctx->r2 = MEM_W(ctx->r3, 0X2B8);
    // 0x800C18D0: beql        $v0, $a1, L_800C18E0
    if (ctx->r2 == ctx->r5) {
        // 0x800C18D4: swc1        $f0, 0x20($v0)
        MEM_W(0X20, ctx->r2) = ctx->f0.u32l;
            goto L_800C18E0;
    }
    goto skip_2;
    // 0x800C18D4: swc1        $f0, 0x20($v0)
    MEM_W(0X20, ctx->r2) = ctx->f0.u32l;
    skip_2:
    // 0x800C18D8: sb          $a0, 0x8($v0)
    MEM_B(0X8, ctx->r2) = ctx->r4;
    // 0x800C18DC: swc1        $f0, 0x20($v0)
    MEM_W(0X20, ctx->r2) = ctx->f0.u32l;
L_800C18E0:
    // 0x800C18E0: lw          $v0, 0x2BC($v1)
    ctx->r2 = MEM_W(ctx->r3, 0X2BC);
    // 0x800C18E4: addiu       $v1, $v1, 0x10
    ctx->r3 = ADD32(ctx->r3, 0X10);
    // 0x800C18E8: beq         $v0, $a1, L_800C18F4
    if (ctx->r2 == ctx->r5) {
        // 0x800C18EC: nop
    
            goto L_800C18F4;
    }
    // 0x800C18EC: nop

    // 0x800C18F0: sb          $a0, 0x8($v0)
    MEM_B(0X8, ctx->r2) = ctx->r4;
L_800C18F4:
    // 0x800C18F4: bne         $v1, $a2, L_800C18A4
    if (ctx->r3 != ctx->r6) {
        // 0x800C18F8: swc1        $f0, 0x20($v0)
        MEM_W(0X20, ctx->r2) = ctx->f0.u32l;
            goto L_800C18A4;
    }
    // 0x800C18F8: swc1        $f0, 0x20($v0)
    MEM_W(0X20, ctx->r2) = ctx->f0.u32l;
    // 0x800C18FC: jr          $ra
    // 0x800C1900: nop

    return;
    // 0x800C1900: nop

;}
RECOMP_FUNC void func_800C1904(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C1904: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x800C1908: addiu       $v1, $v1, 0x7DE8
    ctx->r3 = ADD32(ctx->r3, 0X7DE8);
    // 0x800C190C: lhu         $t6, 0x0($v1)
    ctx->r14 = MEM_HU(ctx->r3, 0X0);
    // 0x800C1910: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800C1914: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800C1918: bne         $t6, $zero, L_800C1960
    if (ctx->r14 != 0) {
        // 0x800C191C: lui         $t2, 0x801D
        ctx->r10 = S32(0X801D << 16);
            goto L_800C1960;
    }
    // 0x800C191C: lui         $t2, 0x801D
    ctx->r10 = S32(0X801D << 16);
    // 0x800C1920: lui         $v0, 0x8004
    ctx->r2 = S32(0X8004 << 16);
    // 0x800C1924: addiu       $v0, $v0, -0x7EF0
    ctx->r2 = ADD32(ctx->r2, -0X7EF0);
    // 0x800C1928: lhu         $t7, 0x110($v0)
    ctx->r15 = MEM_HU(ctx->r2, 0X110);
    // 0x800C192C: lui         $t8, 0x801D
    ctx->r24 = S32(0X801D << 16);
    // 0x800C1930: lw          $t8, 0x7DC4($t8)
    ctx->r24 = MEM_W(ctx->r24, 0X7DC4);
    // 0x800C1934: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x800C1938: sh          $t7, 0x7DE6($at)
    MEM_H(0X7DE6, ctx->r1) = ctx->r15;
    // 0x800C193C: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x800C1940: bne         $t8, $at, L_800C1954
    if (ctx->r24 != ctx->r1) {
        // 0x800C1944: addiu       $t1, $zero, 0x1
        ctx->r9 = ADD32(0, 0X1);
            goto L_800C1954;
    }
    // 0x800C1944: addiu       $t1, $zero, 0x1
    ctx->r9 = ADD32(0, 0X1);
    // 0x800C1948: addiu       $t9, $zero, 0x61FF
    ctx->r25 = ADD32(0, 0X61FF);
    // 0x800C194C: b           L_800C195C
    // 0x800C1950: sh          $t9, 0x110($v0)
    MEM_H(0X110, ctx->r2) = ctx->r25;
        goto L_800C195C;
    // 0x800C1950: sh          $t9, 0x110($v0)
    MEM_H(0X110, ctx->r2) = ctx->r25;
L_800C1954:
    // 0x800C1954: addiu       $t0, $zero, 0x5FFF
    ctx->r8 = ADD32(0, 0X5FFF);
    // 0x800C1958: sh          $t0, 0x110($v0)
    MEM_H(0X110, ctx->r2) = ctx->r8;
L_800C195C:
    // 0x800C195C: sh          $t1, 0x0($v1)
    MEM_H(0X0, ctx->r3) = ctx->r9;
L_800C1960:
    // 0x800C1960: lw          $t2, 0x7DC0($t2)
    ctx->r10 = MEM_W(ctx->r10, 0X7DC0);
    // 0x800C1964: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x800C1968: addiu       $a1, $zero, 0x66
    ctx->r5 = ADD32(0, 0X66);
    // 0x800C196C: beq         $t2, $at, L_800C19B4
    if (ctx->r10 == ctx->r1) {
        // 0x800C1970: nop
    
            goto L_800C19B4;
    }
    // 0x800C1970: nop

    // 0x800C1974: jal         0x800C53D4
    // 0x800C1978: lui         $a0, 0x500
    ctx->r4 = S32(0X500 << 16);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_0;
    // 0x800C1978: lui         $a0, 0x500
    ctx->r4 = S32(0X500 << 16);
    after_0:
    // 0x800C197C: lui         $a0, 0x500
    ctx->r4 = S32(0X500 << 16);
    // 0x800C1980: ori         $a0, $a0, 0x200
    ctx->r4 = ctx->r4 | 0X200;
    // 0x800C1984: jal         0x800C53D4
    // 0x800C1988: addiu       $a1, $zero, 0x66
    ctx->r5 = ADD32(0, 0X66);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_1;
    // 0x800C1988: addiu       $a1, $zero, 0x66
    ctx->r5 = ADD32(0, 0X66);
    after_1:
    // 0x800C198C: lui         $a0, 0x500
    ctx->r4 = S32(0X500 << 16);
    // 0x800C1990: ori         $a0, $a0, 0x300
    ctx->r4 = ctx->r4 | 0X300;
    // 0x800C1994: jal         0x800C53D4
    // 0x800C1998: addiu       $a1, $zero, 0x66
    ctx->r5 = ADD32(0, 0X66);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_2;
    // 0x800C1998: addiu       $a1, $zero, 0x66
    ctx->r5 = ADD32(0, 0X66);
    after_2:
    // 0x800C199C: lui         $a0, 0x500
    ctx->r4 = S32(0X500 << 16);
    // 0x800C19A0: ori         $a0, $a0, 0x500
    ctx->r4 = ctx->r4 | 0X500;
    // 0x800C19A4: jal         0x800C53D4
    // 0x800C19A8: addiu       $a1, $zero, 0x66
    ctx->r5 = ADD32(0, 0X66);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_3;
    // 0x800C19A8: addiu       $a1, $zero, 0x66
    ctx->r5 = ADD32(0, 0X66);
    after_3:
    // 0x800C19AC: b           L_800C1A14
    // 0x800C19B0: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_800C1A14;
    // 0x800C19B0: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_800C19B4:
    // 0x800C19B4: bne         $a0, $zero, L_800C19E8
    if (ctx->r4 != 0) {
        // 0x800C19B8: addiu       $a1, $zero, 0x66
        ctx->r5 = ADD32(0, 0X66);
            goto L_800C19E8;
    }
    // 0x800C19B8: addiu       $a1, $zero, 0x66
    ctx->r5 = ADD32(0, 0X66);
    // 0x800C19BC: lui         $a0, 0x500
    ctx->r4 = S32(0X500 << 16);
    // 0x800C19C0: jal         0x800C53D4
    // 0x800C19C4: addiu       $a1, $zero, 0x66
    ctx->r5 = ADD32(0, 0X66);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_4;
    // 0x800C19C4: addiu       $a1, $zero, 0x66
    ctx->r5 = ADD32(0, 0X66);
    after_4:
    // 0x800C19C8: lui         $a0, 0x500
    ctx->r4 = S32(0X500 << 16);
    // 0x800C19CC: ori         $a0, $a0, 0x200
    ctx->r4 = ctx->r4 | 0X200;
    // 0x800C19D0: jal         0x800C53D4
    // 0x800C19D4: addiu       $a1, $zero, 0x66
    ctx->r5 = ADD32(0, 0X66);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_5;
    // 0x800C19D4: addiu       $a1, $zero, 0x66
    ctx->r5 = ADD32(0, 0X66);
    after_5:
    // 0x800C19D8: addiu       $t3, $zero, 0x1
    ctx->r11 = ADD32(0, 0X1);
    // 0x800C19DC: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x800C19E0: b           L_800C1A10
    // 0x800C19E4: sh          $t3, 0x7DEC($at)
    MEM_H(0X7DEC, ctx->r1) = ctx->r11;
        goto L_800C1A10;
    // 0x800C19E4: sh          $t3, 0x7DEC($at)
    MEM_H(0X7DEC, ctx->r1) = ctx->r11;
L_800C19E8:
    // 0x800C19E8: lui         $a0, 0x500
    ctx->r4 = S32(0X500 << 16);
    // 0x800C19EC: jal         0x800C53D4
    // 0x800C19F0: ori         $a0, $a0, 0x300
    ctx->r4 = ctx->r4 | 0X300;
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_6;
    // 0x800C19F0: ori         $a0, $a0, 0x300
    ctx->r4 = ctx->r4 | 0X300;
    after_6:
    // 0x800C19F4: lui         $a0, 0x500
    ctx->r4 = S32(0X500 << 16);
    // 0x800C19F8: ori         $a0, $a0, 0x500
    ctx->r4 = ctx->r4 | 0X500;
    // 0x800C19FC: jal         0x800C53D4
    // 0x800C1A00: addiu       $a1, $zero, 0x66
    ctx->r5 = ADD32(0, 0X66);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_7;
    // 0x800C1A00: addiu       $a1, $zero, 0x66
    ctx->r5 = ADD32(0, 0X66);
    after_7:
    // 0x800C1A04: addiu       $t4, $zero, 0x1
    ctx->r12 = ADD32(0, 0X1);
    // 0x800C1A08: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x800C1A0C: sh          $t4, 0x7DEE($at)
    MEM_H(0X7DEE, ctx->r1) = ctx->r12;
L_800C1A10:
    // 0x800C1A10: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_800C1A14:
    // 0x800C1A14: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800C1A18: jr          $ra
    // 0x800C1A1C: nop

    return;
    // 0x800C1A1C: nop

;}
RECOMP_FUNC void func_800C1A20(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C1A20: lui         $t6, 0x801D
    ctx->r14 = S32(0X801D << 16);
    // 0x800C1A24: lhu         $t6, 0x7DE8($t6)
    ctx->r14 = MEM_HU(ctx->r14, 0X7DE8);
    // 0x800C1A28: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800C1A2C: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800C1A30: beq         $t6, $zero, L_800C1B20
    if (ctx->r14 == 0) {
        // 0x800C1A34: lui         $t7, 0x801D
        ctx->r15 = S32(0X801D << 16);
            goto L_800C1B20;
    }
    // 0x800C1A34: lui         $t7, 0x801D
    ctx->r15 = S32(0X801D << 16);
    // 0x800C1A38: lw          $t7, 0x7DC0($t7)
    ctx->r15 = MEM_W(ctx->r15, 0X7DC0);
    // 0x800C1A3C: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x800C1A40: addiu       $a1, $zero, 0x10
    ctx->r5 = ADD32(0, 0X10);
    // 0x800C1A44: beq         $t7, $at, L_800C1A90
    if (ctx->r15 == ctx->r1) {
        // 0x800C1A48: nop
    
            goto L_800C1A90;
    }
    // 0x800C1A48: nop

    // 0x800C1A4C: jal         0x800C53D4
    // 0x800C1A50: lui         $a0, 0x500
    ctx->r4 = S32(0X500 << 16);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_0;
    // 0x800C1A50: lui         $a0, 0x500
    ctx->r4 = S32(0X500 << 16);
    after_0:
    // 0x800C1A54: lui         $a0, 0x500
    ctx->r4 = S32(0X500 << 16);
    // 0x800C1A58: ori         $a0, $a0, 0x200
    ctx->r4 = ctx->r4 | 0X200;
    // 0x800C1A5C: jal         0x800C53D4
    // 0x800C1A60: addiu       $a1, $zero, 0x10
    ctx->r5 = ADD32(0, 0X10);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_1;
    // 0x800C1A60: addiu       $a1, $zero, 0x10
    ctx->r5 = ADD32(0, 0X10);
    after_1:
    // 0x800C1A64: lui         $a0, 0x500
    ctx->r4 = S32(0X500 << 16);
    // 0x800C1A68: ori         $a0, $a0, 0x300
    ctx->r4 = ctx->r4 | 0X300;
    // 0x800C1A6C: jal         0x800C53D4
    // 0x800C1A70: addiu       $a1, $zero, 0x10
    ctx->r5 = ADD32(0, 0X10);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_2;
    // 0x800C1A70: addiu       $a1, $zero, 0x10
    ctx->r5 = ADD32(0, 0X10);
    after_2:
    // 0x800C1A74: lui         $a0, 0x500
    ctx->r4 = S32(0X500 << 16);
    // 0x800C1A78: ori         $a0, $a0, 0x500
    ctx->r4 = ctx->r4 | 0X500;
    // 0x800C1A7C: jal         0x800C53D4
    // 0x800C1A80: addiu       $a1, $zero, 0x10
    ctx->r5 = ADD32(0, 0X10);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_3;
    // 0x800C1A80: addiu       $a1, $zero, 0x10
    ctx->r5 = ADD32(0, 0X10);
    after_3:
    // 0x800C1A84: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x800C1A88: b           L_800C1B00
    // 0x800C1A8C: sh          $zero, 0x7DE8($at)
    MEM_H(0X7DE8, ctx->r1) = 0;
        goto L_800C1B00;
    // 0x800C1A8C: sh          $zero, 0x7DE8($at)
    MEM_H(0X7DE8, ctx->r1) = 0;
L_800C1A90:
    // 0x800C1A90: bne         $a0, $zero, L_800C1AC0
    if (ctx->r4 != 0) {
        // 0x800C1A94: addiu       $a1, $zero, 0x10
        ctx->r5 = ADD32(0, 0X10);
            goto L_800C1AC0;
    }
    // 0x800C1A94: addiu       $a1, $zero, 0x10
    ctx->r5 = ADD32(0, 0X10);
    // 0x800C1A98: jal         0x800C53D4
    // 0x800C1A9C: lui         $a0, 0x500
    ctx->r4 = S32(0X500 << 16);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_4;
    // 0x800C1A9C: lui         $a0, 0x500
    ctx->r4 = S32(0X500 << 16);
    after_4:
    // 0x800C1AA0: lui         $a0, 0x500
    ctx->r4 = S32(0X500 << 16);
    // 0x800C1AA4: ori         $a0, $a0, 0x200
    ctx->r4 = ctx->r4 | 0X200;
    // 0x800C1AA8: jal         0x800C53D4
    // 0x800C1AAC: addiu       $a1, $zero, 0x10
    ctx->r5 = ADD32(0, 0X10);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_5;
    // 0x800C1AAC: addiu       $a1, $zero, 0x10
    ctx->r5 = ADD32(0, 0X10);
    after_5:
    // 0x800C1AB0: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x800C1AB4: addiu       $v0, $v0, 0x7DEC
    ctx->r2 = ADD32(ctx->r2, 0X7DEC);
    // 0x800C1AB8: b           L_800C1AEC
    // 0x800C1ABC: sh          $zero, 0x0($v0)
    MEM_H(0X0, ctx->r2) = 0;
        goto L_800C1AEC;
    // 0x800C1ABC: sh          $zero, 0x0($v0)
    MEM_H(0X0, ctx->r2) = 0;
L_800C1AC0:
    // 0x800C1AC0: lui         $a0, 0x500
    ctx->r4 = S32(0X500 << 16);
    // 0x800C1AC4: ori         $a0, $a0, 0x300
    ctx->r4 = ctx->r4 | 0X300;
    // 0x800C1AC8: jal         0x800C53D4
    // 0x800C1ACC: addiu       $a1, $zero, 0x10
    ctx->r5 = ADD32(0, 0X10);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_6;
    // 0x800C1ACC: addiu       $a1, $zero, 0x10
    ctx->r5 = ADD32(0, 0X10);
    after_6:
    // 0x800C1AD0: lui         $a0, 0x500
    ctx->r4 = S32(0X500 << 16);
    // 0x800C1AD4: ori         $a0, $a0, 0x500
    ctx->r4 = ctx->r4 | 0X500;
    // 0x800C1AD8: jal         0x800C53D4
    // 0x800C1ADC: addiu       $a1, $zero, 0x10
    ctx->r5 = ADD32(0, 0X10);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_7;
    // 0x800C1ADC: addiu       $a1, $zero, 0x10
    ctx->r5 = ADD32(0, 0X10);
    after_7:
    // 0x800C1AE0: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x800C1AE4: addiu       $v0, $v0, 0x7DEC
    ctx->r2 = ADD32(ctx->r2, 0X7DEC);
    // 0x800C1AE8: sh          $zero, 0x2($v0)
    MEM_H(0X2, ctx->r2) = 0;
L_800C1AEC:
    // 0x800C1AEC: lhu         $t8, 0x2($v0)
    ctx->r24 = MEM_HU(ctx->r2, 0X2);
    // 0x800C1AF0: lhu         $t9, 0x0($v0)
    ctx->r25 = MEM_HU(ctx->r2, 0X0);
    // 0x800C1AF4: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x800C1AF8: addu        $t0, $t8, $t9
    ctx->r8 = ADD32(ctx->r24, ctx->r25);
    // 0x800C1AFC: sh          $t0, 0x7DE8($at)
    MEM_H(0X7DE8, ctx->r1) = ctx->r8;
L_800C1B00:
    // 0x800C1B00: lui         $t1, 0x801D
    ctx->r9 = S32(0X801D << 16);
    // 0x800C1B04: lhu         $t1, 0x7DE8($t1)
    ctx->r9 = MEM_HU(ctx->r9, 0X7DE8);
    // 0x800C1B08: lui         $t2, 0x801D
    ctx->r10 = S32(0X801D << 16);
    // 0x800C1B0C: bnel        $t1, $zero, L_800C1B24
    if (ctx->r9 != 0) {
        // 0x800C1B10: lw          $ra, 0x14($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X14);
            goto L_800C1B24;
    }
    goto skip_0;
    // 0x800C1B10: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    skip_0:
    // 0x800C1B14: lhu         $t2, 0x7DE6($t2)
    ctx->r10 = MEM_HU(ctx->r10, 0X7DE6);
    // 0x800C1B18: lui         $at, 0x8004
    ctx->r1 = S32(0X8004 << 16);
    // 0x800C1B1C: sh          $t2, -0x7DE0($at)
    MEM_H(-0X7DE0, ctx->r1) = ctx->r10;
L_800C1B20:
    // 0x800C1B20: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_800C1B24:
    // 0x800C1B24: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800C1B28: jr          $ra
    // 0x800C1B2C: nop

    return;
    // 0x800C1B2C: nop

;}
RECOMP_FUNC void func_800C1B30(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C1B30: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800C1B34: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800C1B38: lui         $a0, 0x600
    ctx->r4 = S32(0X600 << 16);
    // 0x800C1B3C: ori         $a0, $a0, 0x700
    ctx->r4 = ctx->r4 | 0X700;
    // 0x800C1B40: jal         0x800C53D4
    // 0x800C1B44: addiu       $a1, $zero, 0x10
    ctx->r5 = ADD32(0, 0X10);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_0;
    // 0x800C1B44: addiu       $a1, $zero, 0x10
    ctx->r5 = ADD32(0, 0X10);
    after_0:
    // 0x800C1B48: addiu       $a0, $zero, 0x10
    ctx->r4 = ADD32(0, 0X10);
    // 0x800C1B4C: jal         0x800C37F4
    // 0x800C1B50: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_1;
    // 0x800C1B50: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_1:
    // 0x800C1B54: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800C1B58: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800C1B5C: jr          $ra
    // 0x800C1B60: nop

    return;
    // 0x800C1B60: nop

;}
RECOMP_FUNC void func_800C1B64(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C1B64: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800C1B68: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800C1B6C: addiu       $t6, $zero, 0x5
    ctx->r14 = ADD32(0, 0X5);
    // 0x800C1B70: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x800C1B74: lui         $a0, 0x600
    ctx->r4 = S32(0X600 << 16);
    // 0x800C1B78: sw          $t6, 0x7C9C($at)
    MEM_W(0X7C9C, ctx->r1) = ctx->r14;
    // 0x800C1B7C: ori         $a0, $a0, 0x700
    ctx->r4 = ctx->r4 | 0X700;
    // 0x800C1B80: jal         0x800C53D4
    // 0x800C1B84: addiu       $a1, $zero, 0x11
    ctx->r5 = ADD32(0, 0X11);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_0;
    // 0x800C1B84: addiu       $a1, $zero, 0x11
    ctx->r5 = ADD32(0, 0X11);
    after_0:
    // 0x800C1B88: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800C1B8C: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800C1B90: jr          $ra
    // 0x800C1B94: nop

    return;
    // 0x800C1B94: nop

;}
RECOMP_FUNC void func_800C1B98(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C1B98: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800C1B9C: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800C1BA0: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x800C1BA4: lui         $a0, 0x600
    ctx->r4 = S32(0X600 << 16);
    // 0x800C1BA8: sw          $zero, 0x7C9C($at)
    MEM_W(0X7C9C, ctx->r1) = 0;
    // 0x800C1BAC: ori         $a0, $a0, 0x700
    ctx->r4 = ctx->r4 | 0X700;
    // 0x800C1BB0: jal         0x800C53D4
    // 0x800C1BB4: addiu       $a1, $zero, -0x1
    ctx->r5 = ADD32(0, -0X1);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_0;
    // 0x800C1BB4: addiu       $a1, $zero, -0x1
    ctx->r5 = ADD32(0, -0X1);
    after_0:
    // 0x800C1BB8: lui         $a0, 0x600
    ctx->r4 = S32(0X600 << 16);
    // 0x800C1BBC: ori         $a0, $a0, 0x704
    ctx->r4 = ctx->r4 | 0X704;
    // 0x800C1BC0: jal         0x800C53D4
    // 0x800C1BC4: addiu       $a1, $zero, -0x1
    ctx->r5 = ADD32(0, -0X1);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_1;
    // 0x800C1BC4: addiu       $a1, $zero, -0x1
    ctx->r5 = ADD32(0, -0X1);
    after_1:
    // 0x800C1BC8: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800C1BCC: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800C1BD0: jr          $ra
    // 0x800C1BD4: nop

    return;
    // 0x800C1BD4: nop

;}
RECOMP_FUNC void func_800C1BD8(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C1BD8: lui         $t6, 0x800E
    ctx->r14 = S32(0X800E << 16);
    // 0x800C1BDC: lw          $t6, 0x7C9C($t6)
    ctx->r14 = MEM_W(ctx->r14, 0X7C9C);
    // 0x800C1BE0: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x800C1BE4: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800C1BE8: beq         $t6, $zero, L_800C1D90
    if (ctx->r14 == 0) {
        // 0x800C1BEC: swc1        $f14, 0x24($sp)
        MEM_W(0X24, ctx->r29) = ctx->f14.u32l;
            goto L_800C1D90;
    }
    // 0x800C1BEC: swc1        $f14, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->f14.u32l;
    // 0x800C1BF0: lui         $at, 0x4380
    ctx->r1 = S32(0X4380 << 16);
    // 0x800C1BF4: mtc1        $at, $f2
    ctx->f2.u32l = ctx->r1;
    // 0x800C1BF8: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x800C1BFC: lui         $at, 0x4240
    ctx->r1 = S32(0X4240 << 16);
    // 0x800C1C00: c.le.s      $f2, $f12
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 12);
    c1cs = ctx->f2.fl <= ctx->f12.fl;
    // 0x800C1C04: lui         $t7, 0x801D
    ctx->r15 = S32(0X801D << 16);
    // 0x800C1C08: lui         $t8, 0x801D
    ctx->r24 = S32(0X801D << 16);
    // 0x800C1C0C: addiu       $v1, $v1, 0x7DEC
    ctx->r3 = ADD32(ctx->r3, 0X7DEC);
    // 0x800C1C10: bc1fl       L_800C1C28
    if (!c1cs) {
        // 0x800C1C14: mtc1        $at, $f4
        ctx->f4.u32l = ctx->r1;
            goto L_800C1C28;
    }
    goto skip_0;
    // 0x800C1C14: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    skip_0:
    // 0x800C1C18: mtc1        $zero, $f0
    ctx->f0.u32l = 0;
    // 0x800C1C1C: b           L_800C1C5C
    // 0x800C1C20: nop

        goto L_800C1C5C;
    // 0x800C1C20: nop

    // 0x800C1C24: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
L_800C1C28:
    // 0x800C1C28: lui         $at, 0x4350
    ctx->r1 = S32(0X4350 << 16);
    // 0x800C1C2C: c.le.s      $f12, $f4
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    c1cs = ctx->f12.fl <= ctx->f4.fl;
    // 0x800C1C30: nop

    // 0x800C1C34: bc1fl       L_800C1C50
    if (!c1cs) {
        // 0x800C1C38: sub.s       $f6, $f2, $f12
        CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f6.fl = ctx->f2.fl - ctx->f12.fl;
            goto L_800C1C50;
    }
    goto skip_1;
    // 0x800C1C38: sub.s       $f6, $f2, $f12
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f6.fl = ctx->f2.fl - ctx->f12.fl;
    skip_1:
    // 0x800C1C3C: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x800C1C40: mtc1        $at, $f0
    ctx->f0.u32l = ctx->r1;
    // 0x800C1C44: b           L_800C1C5C
    // 0x800C1C48: nop

        goto L_800C1C5C;
    // 0x800C1C48: nop

    // 0x800C1C4C: sub.s       $f6, $f2, $f12
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f6.fl = ctx->f2.fl - ctx->f12.fl;
L_800C1C50:
    // 0x800C1C50: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x800C1C54: nop

    // 0x800C1C58: div.s       $f0, $f6, $f8
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f0.fl = DIV_S(ctx->f6.fl, ctx->f8.fl);
L_800C1C5C:
    // 0x800C1C5C: lw          $t7, 0x7DC0($t7)
    ctx->r15 = MEM_W(ctx->r15, 0X7DC0);
    // 0x800C1C60: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    // 0x800C1C64: beql        $a0, $t7, L_800C1CA4
    if (ctx->r4 == ctx->r15) {
        // 0x800C1C68: lhu         $t9, 0x2($v1)
        ctx->r25 = MEM_HU(ctx->r3, 0X2);
            goto L_800C1CA4;
    }
    goto skip_2;
    // 0x800C1C68: lhu         $t9, 0x2($v1)
    ctx->r25 = MEM_HU(ctx->r3, 0X2);
    skip_2:
    // 0x800C1C6C: lhu         $t8, 0x7DE8($t8)
    ctx->r24 = MEM_HU(ctx->r24, 0X7DE8);
    // 0x800C1C70: lui         $a0, 0x100
    ctx->r4 = S32(0X100 << 16);
    // 0x800C1C74: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x800C1C78: beq         $t8, $zero, L_800C1C8C
    if (ctx->r24 == 0) {
        // 0x800C1C7C: ori         $a0, $a0, 0x700
        ctx->r4 = ctx->r4 | 0X700;
            goto L_800C1C8C;
    }
    // 0x800C1C7C: ori         $a0, $a0, 0x700
    ctx->r4 = ctx->r4 | 0X700;
    // 0x800C1C80: lwc1        $f10, -0x3C64($at)
    ctx->f10.u32l = MEM_W(ctx->r1, -0X3C64);
    // 0x800C1C84: mul.s       $f0, $f0, $f10
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f0.fl = MUL_S(ctx->f0.fl, ctx->f10.fl);
    // 0x800C1C88: nop

L_800C1C8C:
    // 0x800C1C8C: mfc1        $a1, $f0
    ctx->r5 = (int32_t)ctx->f0.u32l;
    // 0x800C1C90: jal         0x800C538C
    // 0x800C1C94: swc1        $f0, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->f0.u32l;
    AudioThread_QueueCmdF32(rdram, ctx);
        goto after_0;
    // 0x800C1C94: swc1        $f0, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->f0.u32l;
    after_0:
    // 0x800C1C98: b           L_800C1D30
    // 0x800C1C9C: lwc1        $f0, 0x1C($sp)
    ctx->f0.u32l = MEM_W(ctx->r29, 0X1C);
        goto L_800C1D30;
    // 0x800C1C9C: lwc1        $f0, 0x1C($sp)
    ctx->f0.u32l = MEM_W(ctx->r29, 0X1C);
    // 0x800C1CA0: lhu         $t9, 0x2($v1)
    ctx->r25 = MEM_HU(ctx->r3, 0X2);
L_800C1CA4:
    // 0x800C1CA4: lhu         $t1, 0x0($v1)
    ctx->r9 = MEM_HU(ctx->r3, 0X0);
    // 0x800C1CA8: addiu       $a1, $zero, 0x40
    ctx->r5 = ADD32(0, 0X40);
    // 0x800C1CAC: sll         $t0, $t9, 1
    ctx->r8 = S32(ctx->r25 << 1);
    // 0x800C1CB0: addu        $v0, $t0, $t1
    ctx->r2 = ADD32(ctx->r8, ctx->r9);
    // 0x800C1CB4: beq         $v0, $zero, L_800C1D1C
    if (ctx->r2 == 0) {
        // 0x800C1CB8: nop
    
            goto L_800C1D1C;
    }
    // 0x800C1CB8: nop

    // 0x800C1CBC: beq         $v0, $a0, L_800C1CE0
    if (ctx->r2 == ctx->r4) {
        // 0x800C1CC0: lui         $at, 0x800F
        ctx->r1 = S32(0X800F << 16);
            goto L_800C1CE0;
    }
    // 0x800C1CC0: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x800C1CC4: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x800C1CC8: beq         $v0, $at, L_800C1CF4
    if (ctx->r2 == ctx->r1) {
        // 0x800C1CCC: addiu       $at, $zero, 0x3
        ctx->r1 = ADD32(0, 0X3);
            goto L_800C1CF4;
    }
    // 0x800C1CCC: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x800C1CD0: beq         $v0, $at, L_800C1D0C
    if (ctx->r2 == ctx->r1) {
        // 0x800C1CD4: nop
    
            goto L_800C1D0C;
    }
    // 0x800C1CD4: nop

    // 0x800C1CD8: b           L_800C1D1C
    // 0x800C1CDC: nop

        goto L_800C1D1C;
    // 0x800C1CDC: nop

L_800C1CE0:
    // 0x800C1CE0: lwc1        $f16, -0x3C60($at)
    ctx->f16.u32l = MEM_W(ctx->r1, -0X3C60);
    // 0x800C1CE4: addiu       $a1, $zero, 0x20
    ctx->r5 = ADD32(0, 0X20);
    // 0x800C1CE8: mul.s       $f0, $f0, $f16
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f0.fl = MUL_S(ctx->f0.fl, ctx->f16.fl);
    // 0x800C1CEC: b           L_800C1D20
    // 0x800C1CF0: lui         $a0, 0x300
    ctx->r4 = S32(0X300 << 16);
        goto L_800C1D20;
    // 0x800C1CF0: lui         $a0, 0x300
    ctx->r4 = S32(0X300 << 16);
L_800C1CF4:
    // 0x800C1CF4: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x800C1CF8: lwc1        $f18, -0x3C5C($at)
    ctx->f18.u32l = MEM_W(ctx->r1, -0X3C5C);
    // 0x800C1CFC: addiu       $a1, $zero, 0x60
    ctx->r5 = ADD32(0, 0X60);
    // 0x800C1D00: mul.s       $f0, $f0, $f18
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f0.fl = MUL_S(ctx->f0.fl, ctx->f18.fl);
    // 0x800C1D04: b           L_800C1D20
    // 0x800C1D08: lui         $a0, 0x300
    ctx->r4 = S32(0X300 << 16);
        goto L_800C1D20;
    // 0x800C1D08: lui         $a0, 0x300
    ctx->r4 = S32(0X300 << 16);
L_800C1D0C:
    // 0x800C1D0C: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x800C1D10: lwc1        $f4, -0x3C58($at)
    ctx->f4.u32l = MEM_W(ctx->r1, -0X3C58);
    // 0x800C1D14: mul.s       $f0, $f0, $f4
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f0.fl = MUL_S(ctx->f0.fl, ctx->f4.fl);
    // 0x800C1D18: nop

L_800C1D1C:
    // 0x800C1D1C: lui         $a0, 0x300
    ctx->r4 = S32(0X300 << 16);
L_800C1D20:
    // 0x800C1D20: ori         $a0, $a0, 0x700
    ctx->r4 = ctx->r4 | 0X700;
    // 0x800C1D24: jal         0x800C53D4
    // 0x800C1D28: swc1        $f0, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->f0.u32l;
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_1;
    // 0x800C1D28: swc1        $f0, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->f0.u32l;
    after_1:
    // 0x800C1D2C: lwc1        $f0, 0x1C($sp)
    ctx->f0.u32l = MEM_W(ctx->r29, 0X1C);
L_800C1D30:
    // 0x800C1D30: lui         $a0, 0x100
    ctx->r4 = S32(0X100 << 16);
    // 0x800C1D34: mfc1        $a1, $f0
    ctx->r5 = (int32_t)ctx->f0.u32l;
    // 0x800C1D38: jal         0x800C538C
    // 0x800C1D3C: ori         $a0, $a0, 0x700
    ctx->r4 = ctx->r4 | 0X700;
    AudioThread_QueueCmdF32(rdram, ctx);
        goto after_2;
    // 0x800C1D3C: ori         $a0, $a0, 0x700
    ctx->r4 = ctx->r4 | 0X700;
    after_2:
    // 0x800C1D40: mtc1        $zero, $f6
    ctx->f6.u32l = 0;
    // 0x800C1D44: lwc1        $f8, 0x24($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X24);
    // 0x800C1D48: lui         $a0, 0x400
    ctx->r4 = S32(0X400 << 16);
    // 0x800C1D4C: ori         $a0, $a0, 0x700
    ctx->r4 = ctx->r4 | 0X700;
    // 0x800C1D50: c.lt.s      $f6, $f8
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    c1cs = ctx->f6.fl < ctx->f8.fl;
    // 0x800C1D54: lui         $a1, 0x3F75
    ctx->r5 = S32(0X3F75 << 16);
    // 0x800C1D58: bc1f        L_800C1D78
    if (!c1cs) {
        // 0x800C1D5C: nop
    
            goto L_800C1D78;
    }
    // 0x800C1D5C: nop

    // 0x800C1D60: lui         $a0, 0x400
    ctx->r4 = S32(0X400 << 16);
    // 0x800C1D64: ori         $a0, $a0, 0x700
    ctx->r4 = ctx->r4 | 0X700;
    // 0x800C1D68: jal         0x800C538C
    // 0x800C1D6C: lui         $a1, 0x3F80
    ctx->r5 = S32(0X3F80 << 16);
    AudioThread_QueueCmdF32(rdram, ctx);
        goto after_3;
    // 0x800C1D6C: lui         $a1, 0x3F80
    ctx->r5 = S32(0X3F80 << 16);
    after_3:
    // 0x800C1D70: b           L_800C1D84
    // 0x800C1D74: addiu       $t2, $zero, 0x5
    ctx->r10 = ADD32(0, 0X5);
        goto L_800C1D84;
    // 0x800C1D74: addiu       $t2, $zero, 0x5
    ctx->r10 = ADD32(0, 0X5);
L_800C1D78:
    // 0x800C1D78: jal         0x800C538C
    // 0x800C1D7C: ori         $a1, $a1, 0xC28F
    ctx->r5 = ctx->r5 | 0XC28F;
    AudioThread_QueueCmdF32(rdram, ctx);
        goto after_4;
    // 0x800C1D7C: ori         $a1, $a1, 0xC28F
    ctx->r5 = ctx->r5 | 0XC28F;
    after_4:
    // 0x800C1D80: addiu       $t2, $zero, 0x5
    ctx->r10 = ADD32(0, 0X5);
L_800C1D84:
    // 0x800C1D84: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x800C1D88: b           L_800C1D98
    // 0x800C1D8C: sw          $t2, 0x7C9C($at)
    MEM_W(0X7C9C, ctx->r1) = ctx->r10;
        goto L_800C1D98;
    // 0x800C1D8C: sw          $t2, 0x7C9C($at)
    MEM_W(0X7C9C, ctx->r1) = ctx->r10;
L_800C1D90:
    // 0x800C1D90: jal         0x800C1B98
    // 0x800C1D94: nop

    func_800C1B98(rdram, ctx);
        goto after_5;
    // 0x800C1D94: nop

    after_5:
L_800C1D98:
    // 0x800C1D98: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800C1D9C: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x800C1DA0: jr          $ra
    // 0x800C1DA4: nop

    return;
    // 0x800C1DA4: nop

;}
RECOMP_FUNC void func_800C1DA8(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C1DA8: lui         $t6, 0x800E
    ctx->r14 = S32(0X800E << 16);
    // 0x800C1DAC: lb          $t6, 0x7C94($t6)
    ctx->r14 = MEM_B(ctx->r14, 0X7C94);
    // 0x800C1DB0: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800C1DB4: addiu       $at, $zero, 0x7
    ctx->r1 = ADD32(0, 0X7);
    // 0x800C1DB8: bne         $t6, $at, L_800C1DDC
    if (ctx->r14 != ctx->r1) {
        // 0x800C1DBC: sw          $ra, 0x14($sp)
        MEM_W(0X14, ctx->r29) = ctx->r31;
            goto L_800C1DDC;
    }
    // 0x800C1DBC: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800C1DC0: addiu       $t7, $zero, 0x5
    ctx->r15 = ADD32(0, 0X5);
    // 0x800C1DC4: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x800C1DC8: lui         $a0, 0x600
    ctx->r4 = S32(0X600 << 16);
    // 0x800C1DCC: sw          $t7, 0x7C9C($at)
    MEM_W(0X7C9C, ctx->r1) = ctx->r15;
    // 0x800C1DD0: ori         $a0, $a0, 0x700
    ctx->r4 = ctx->r4 | 0X700;
    // 0x800C1DD4: jal         0x800C53D4
    // 0x800C1DD8: addiu       $a1, $zero, 0x12
    ctx->r5 = ADD32(0, 0X12);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_0;
    // 0x800C1DD8: addiu       $a1, $zero, 0x12
    ctx->r5 = ADD32(0, 0X12);
    after_0:
L_800C1DDC:
    // 0x800C1DDC: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800C1DE0: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800C1DE4: jr          $ra
    // 0x800C1DE8: nop

    return;
    // 0x800C1DE8: nop

;}
RECOMP_FUNC void func_800C1DEC(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C1DEC: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800C1DF0: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800C1DF4: jal         0x800C1B98
    // 0x800C1DF8: nop

    func_800C1B98(rdram, ctx);
        goto after_0;
    // 0x800C1DF8: nop

    after_0:
    // 0x800C1DFC: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800C1E00: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800C1E04: jr          $ra
    // 0x800C1E08: nop

    return;
    // 0x800C1E08: nop

;}
RECOMP_FUNC void func_800C1E0C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C1E0C: lui         $t6, 0x800E
    ctx->r14 = S32(0X800E << 16);
    // 0x800C1E10: lw          $t6, 0x7C9C($t6)
    ctx->r14 = MEM_W(ctx->r14, 0X7C9C);
    // 0x800C1E14: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800C1E18: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800C1E1C: beq         $t6, $zero, L_800C1EA0
    if (ctx->r14 == 0) {
        // 0x800C1E20: lui         $at, 0x4248
        ctx->r1 = S32(0X4248 << 16);
            goto L_800C1EA0;
    }
    // 0x800C1E20: lui         $at, 0x4248
    ctx->r1 = S32(0X4248 << 16);
    // 0x800C1E24: mtc1        $at, $f2
    ctx->f2.u32l = ctx->r1;
    // 0x800C1E28: lui         $at, 0x4000
    ctx->r1 = S32(0X4000 << 16);
    // 0x800C1E2C: lui         $a0, 0x100
    ctx->r4 = S32(0X100 << 16);
    // 0x800C1E30: c.le.s      $f2, $f12
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 12);
    c1cs = ctx->f2.fl <= ctx->f12.fl;
    // 0x800C1E34: nop

    // 0x800C1E38: bc1fl       L_800C1E50
    if (!c1cs) {
        // 0x800C1E3C: mtc1        $at, $f4
        ctx->f4.u32l = ctx->r1;
            goto L_800C1E50;
    }
    goto skip_0;
    // 0x800C1E3C: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    skip_0:
    // 0x800C1E40: mtc1        $zero, $f0
    ctx->f0.u32l = 0;
    // 0x800C1E44: b           L_800C1E88
    // 0x800C1E48: mfc1        $a1, $f0
    ctx->r5 = (int32_t)ctx->f0.u32l;
        goto L_800C1E88;
    // 0x800C1E48: mfc1        $a1, $f0
    ctx->r5 = (int32_t)ctx->f0.u32l;
    // 0x800C1E4C: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
L_800C1E50:
    // 0x800C1E50: lui         $at, 0x4240
    ctx->r1 = S32(0X4240 << 16);
    // 0x800C1E54: c.le.s      $f12, $f4
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    c1cs = ctx->f12.fl <= ctx->f4.fl;
    // 0x800C1E58: nop

    // 0x800C1E5C: bc1fl       L_800C1E78
    if (!c1cs) {
        // 0x800C1E60: sub.s       $f6, $f2, $f12
        CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f6.fl = ctx->f2.fl - ctx->f12.fl;
            goto L_800C1E78;
    }
    goto skip_1;
    // 0x800C1E60: sub.s       $f6, $f2, $f12
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f6.fl = ctx->f2.fl - ctx->f12.fl;
    skip_1:
    // 0x800C1E64: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x800C1E68: mtc1        $at, $f0
    ctx->f0.u32l = ctx->r1;
    // 0x800C1E6C: b           L_800C1E88
    // 0x800C1E70: mfc1        $a1, $f0
    ctx->r5 = (int32_t)ctx->f0.u32l;
        goto L_800C1E88;
    // 0x800C1E70: mfc1        $a1, $f0
    ctx->r5 = (int32_t)ctx->f0.u32l;
    // 0x800C1E74: sub.s       $f6, $f2, $f12
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f6.fl = ctx->f2.fl - ctx->f12.fl;
L_800C1E78:
    // 0x800C1E78: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x800C1E7C: nop

    // 0x800C1E80: div.s       $f0, $f6, $f8
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f0.fl = DIV_S(ctx->f6.fl, ctx->f8.fl);
    // 0x800C1E84: mfc1        $a1, $f0
    ctx->r5 = (int32_t)ctx->f0.u32l;
L_800C1E88:
    // 0x800C1E88: jal         0x800C538C
    // 0x800C1E8C: ori         $a0, $a0, 0x700
    ctx->r4 = ctx->r4 | 0X700;
    AudioThread_QueueCmdF32(rdram, ctx);
        goto after_0;
    // 0x800C1E8C: ori         $a0, $a0, 0x700
    ctx->r4 = ctx->r4 | 0X700;
    after_0:
    // 0x800C1E90: addiu       $t7, $zero, 0x5
    ctx->r15 = ADD32(0, 0X5);
    // 0x800C1E94: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x800C1E98: b           L_800C1EA8
    // 0x800C1E9C: sw          $t7, 0x7C9C($at)
    MEM_W(0X7C9C, ctx->r1) = ctx->r15;
        goto L_800C1EA8;
    // 0x800C1E9C: sw          $t7, 0x7C9C($at)
    MEM_W(0X7C9C, ctx->r1) = ctx->r15;
L_800C1EA0:
    // 0x800C1EA0: jal         0x800C1DEC
    // 0x800C1EA4: nop

    func_800C1DEC(rdram, ctx);
        goto after_1;
    // 0x800C1EA4: nop

    after_1:
L_800C1EA8:
    // 0x800C1EA8: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800C1EAC: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800C1EB0: jr          $ra
    // 0x800C1EB4: nop

    return;
    // 0x800C1EB4: nop

;}
RECOMP_FUNC void func_800C1EB8(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C1EB8: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x800C1EBC: lbu         $v0, 0x7E05($v0)
    ctx->r2 = MEM_BU(ctx->r2, 0X7E05);
    // 0x800C1EC0: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800C1EC4: addiu       $at, $zero, 0xFF
    ctx->r1 = ADD32(0, 0XFF);
    // 0x800C1EC8: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800C1ECC: beq         $v0, $at, L_800C1F20
    if (ctx->r2 == ctx->r1) {
        // 0x800C1ED0: or          $a2, $a0, $zero
        ctx->r6 = ctx->r4 | 0;
            goto L_800C1F20;
    }
    // 0x800C1ED0: or          $a2, $a0, $zero
    ctx->r6 = ctx->r4 | 0;
    // 0x800C1ED4: beq         $a0, $zero, L_800C1EEC
    if (ctx->r4 == 0) {
        // 0x800C1ED8: addiu       $at, $zero, 0x1
        ctx->r1 = ADD32(0, 0X1);
            goto L_800C1EEC;
    }
    // 0x800C1ED8: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x800C1EDC: beq         $a0, $at, L_800C1EEC
    if (ctx->r4 == ctx->r1) {
        // 0x800C1EE0: addiu       $at, $zero, 0x2
        ctx->r1 = ADD32(0, 0X2);
            goto L_800C1EEC;
    }
    // 0x800C1EE0: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x800C1EE4: bne         $a0, $at, L_800C1F0C
    if (ctx->r4 != ctx->r1) {
        // 0x800C1EE8: sll         $a1, $a2, 24
        ctx->r5 = S32(ctx->r6 << 24);
            goto L_800C1F0C;
    }
    // 0x800C1EE8: sll         $a1, $a2, 24
    ctx->r5 = S32(ctx->r6 << 24);
L_800C1EEC:
    // 0x800C1EEC: addu        $a1, $v0, $a2
    ctx->r5 = ADD32(ctx->r2, ctx->r6);
    // 0x800C1EF0: sll         $t6, $a1, 24
    ctx->r14 = S32(ctx->r5 << 24);
    // 0x800C1EF4: lui         $a0, 0x600
    ctx->r4 = S32(0X600 << 16);
    // 0x800C1EF8: ori         $a0, $a0, 0xB00
    ctx->r4 = ctx->r4 | 0XB00;
    // 0x800C1EFC: jal         0x800C53D4
    // 0x800C1F00: sra         $a1, $t6, 24
    ctx->r5 = S32(SIGNED(ctx->r14) >> 24);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_0;
    // 0x800C1F00: sra         $a1, $t6, 24
    ctx->r5 = S32(SIGNED(ctx->r14) >> 24);
    after_0:
    // 0x800C1F04: b           L_800C1F24
    // 0x800C1F08: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_800C1F24;
    // 0x800C1F08: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_800C1F0C:
    // 0x800C1F0C: lui         $a0, 0x600
    ctx->r4 = S32(0X600 << 16);
    // 0x800C1F10: sra         $t8, $a1, 24
    ctx->r24 = S32(SIGNED(ctx->r5) >> 24);
    // 0x800C1F14: or          $a1, $t8, $zero
    ctx->r5 = ctx->r24 | 0;
    // 0x800C1F18: jal         0x800C53D4
    // 0x800C1F1C: ori         $a0, $a0, 0xB00
    ctx->r4 = ctx->r4 | 0XB00;
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_1;
    // 0x800C1F1C: ori         $a0, $a0, 0xB00
    ctx->r4 = ctx->r4 | 0XB00;
    after_1:
L_800C1F20:
    // 0x800C1F20: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_800C1F24:
    // 0x800C1F24: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800C1F28: jr          $ra
    // 0x800C1F2C: nop

    return;
    // 0x800C1F2C: nop

;}
