#include "recomp.h"
#include "funcs.h"

RECOMP_FUNC void func_801DFDA8(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801DFDA8: sw          $a1, 0x10($a0)
    MEM_W(0X10, ctx->r4) = ctx->r5;
    // 0x801DFDAC: sw          $a2, 0x14($a0)
    MEM_W(0X14, ctx->r4) = ctx->r6;
    // 0x801DFDB0: sw          $a3, 0x18($a0)
    MEM_W(0X18, ctx->r4) = ctx->r7;
    // 0x801DFDB4: lw          $t6, 0x10($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X10);
    // 0x801DFDB8: sw          $t6, 0x1C($a0)
    MEM_W(0X1C, ctx->r4) = ctx->r14;
    // 0x801DFDBC: lw          $t7, 0x14($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X14);
    // 0x801DFDC0: sw          $t7, 0x20($a0)
    MEM_W(0X20, ctx->r4) = ctx->r15;
    // 0x801DFDC4: lw          $t8, 0x18($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X18);
    // 0x801DFDC8: sw          $t8, 0x24($a0)
    MEM_W(0X24, ctx->r4) = ctx->r24;
    // 0x801DFDCC: lw          $t9, 0x1C($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X1C);
    // 0x801DFDD0: sw          $t9, 0x28($a0)
    MEM_W(0X28, ctx->r4) = ctx->r25;
    // 0x801DFDD4: lw          $t0, 0x20($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X20);
    // 0x801DFDD8: sw          $t0, 0x2C($a0)
    MEM_W(0X2C, ctx->r4) = ctx->r8;
    // 0x801DFDDC: lw          $t1, 0x24($sp)
    ctx->r9 = MEM_W(ctx->r29, 0X24);
    // 0x801DFDE0: sw          $t1, 0x30($a0)
    MEM_W(0X30, ctx->r4) = ctx->r9;
    // 0x801DFDE4: lw          $t2, 0x28($sp)
    ctx->r10 = MEM_W(ctx->r29, 0X28);
    // 0x801DFDE8: jr          $ra
    // 0x801DFDEC: sw          $t2, 0x34($a0)
    MEM_W(0X34, ctx->r4) = ctx->r10;
    return;
    // 0x801DFDEC: sw          $t2, 0x34($a0)
    MEM_W(0X34, ctx->r4) = ctx->r10;
;}
RECOMP_FUNC void func_801DFDF0(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801DFDF0: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x801DFDF4: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x801DFDF8: jal         0x801DEA94
    // 0x801DFDFC: lw          $a0, 0xC($a0)
    ctx->r4 = MEM_W(ctx->r4, 0XC);
    func_801DEA94(rdram, ctx);
        goto after_0;
    // 0x801DFDFC: lw          $a0, 0xC($a0)
    ctx->r4 = MEM_W(ctx->r4, 0XC);
    after_0:
    // 0x801DFE00: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x801DFE04: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x801DFE08: jr          $ra
    // 0x801DFE0C: nop

    return;
    // 0x801DFE0C: nop

;}
RECOMP_FUNC void func_801DFE10(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801DFE10: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x801DFE14: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x801DFE18: jal         0x801DF008
    // 0x801DFE1C: lw          $a0, 0x0($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X0);
    func_801DF008(rdram, ctx);
        goto after_0;
    // 0x801DFE1C: lw          $a0, 0x0($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X0);
    after_0:
    // 0x801DFE20: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x801DFE24: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x801DFE28: jr          $ra
    // 0x801DFE2C: nop

    return;
    // 0x801DFE2C: nop

;}
RECOMP_FUNC void func_801DFE30(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801DFE30: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x801DFE34: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x801DFE38: or          $a2, $a1, $zero
    ctx->r6 = ctx->r5 | 0;
    // 0x801DFE3C: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x801DFE40: jal         0x801DF278
    // 0x801DFE44: lw          $a0, 0x0($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X0);
    func_801DF278(rdram, ctx);
        goto after_0;
    // 0x801DFE44: lw          $a0, 0x0($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X0);
    after_0:
    // 0x801DFE48: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x801DFE4C: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x801DFE50: jr          $ra
    // 0x801DFE54: nop

    return;
    // 0x801DFE54: nop

;}
RECOMP_FUNC void func_801DFE58(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801DFE58: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x801DFE5C: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x801DFE60: or          $a2, $a1, $zero
    ctx->r6 = ctx->r5 | 0;
    // 0x801DFE64: addiu       $a1, $zero, 0x3
    ctx->r5 = ADD32(0, 0X3);
    // 0x801DFE68: jal         0x801DF278
    // 0x801DFE6C: lw          $a0, 0x0($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X0);
    func_801DF278(rdram, ctx);
        goto after_0;
    // 0x801DFE6C: lw          $a0, 0x0($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X0);
    after_0:
    // 0x801DFE70: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x801DFE74: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x801DFE78: jr          $ra
    // 0x801DFE7C: nop

    return;
    // 0x801DFE7C: nop

;}
RECOMP_FUNC void func_801DFE80(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801DFE80: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x801DFE84: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x801DFE88: or          $a3, $a0, $zero
    ctx->r7 = ctx->r4 | 0;
    // 0x801DFE8C: lw          $a0, 0x0($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X0);
    // 0x801DFE90: jal         0x801DF5F0
    // 0x801DFE94: sw          $a3, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r7;
    func_801DF5F0(rdram, ctx);
        goto after_0;
    // 0x801DFE94: sw          $a3, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r7;
    after_0:
    // 0x801DFE98: lw          $a3, 0x18($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X18);
    // 0x801DFE9C: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
    // 0x801DFEA0: addiu       $a2, $zero, 0x2
    ctx->r6 = ADD32(0, 0X2);
    // 0x801DFEA4: lw          $a1, 0x0($a3)
    ctx->r5 = MEM_W(ctx->r7, 0X0);
    // 0x801DFEA8: or          $a0, $a3, $zero
    ctx->r4 = ctx->r7 | 0;
    // 0x801DFEAC: addiu       $a1, $a1, 0x5C
    ctx->r5 = ADD32(ctx->r5, 0X5C);
    // 0x801DFEB0: or          $v0, $a1, $zero
    ctx->r2 = ctx->r5 | 0;
L_801DFEB4:
    // 0x801DFEB4: lw          $t6, 0x10($a0)
    ctx->r14 = MEM_W(ctx->r4, 0X10);
    // 0x801DFEB8: addiu       $v1, $v1, 0x1
    ctx->r3 = ADD32(ctx->r3, 0X1);
    // 0x801DFEBC: slti        $at, $v1, 0x3
    ctx->r1 = SIGNED(ctx->r3) < 0X3 ? 1 : 0;
    // 0x801DFEC0: lwc1        $f4, 0x0($t6)
    ctx->f4.u32l = MEM_W(ctx->r14, 0X0);
    // 0x801DFEC4: addiu       $v0, $v0, 0x4
    ctx->r2 = ADD32(ctx->r2, 0X4);
    // 0x801DFEC8: addiu       $a0, $a0, 0x4
    ctx->r4 = ADD32(ctx->r4, 0X4);
    // 0x801DFECC: bne         $at, $zero, L_801DFEB4
    if (ctx->r1 != 0) {
        // 0x801DFED0: swc1        $f4, -0x4($v0)
        MEM_W(-0X4, ctx->r2) = ctx->f4.u32l;
            goto L_801DFEB4;
    }
    // 0x801DFED0: swc1        $f4, -0x4($v0)
    MEM_W(-0X4, ctx->r2) = ctx->f4.u32l;
    // 0x801DFED4: lui         $at, 0x42C8
    ctx->r1 = S32(0X42C8 << 16);
    // 0x801DFED8: mtc1        $at, $f0
    ctx->f0.u32l = ctx->r1;
    // 0x801DFEDC: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
    // 0x801DFEE0: or          $v0, $a1, $zero
    ctx->r2 = ctx->r5 | 0;
    // 0x801DFEE4: lw          $a1, 0x74($v0)
    ctx->r5 = MEM_W(ctx->r2, 0X74);
    // 0x801DFEE8: addiu       $v1, $v1, 0x1
    ctx->r3 = ADD32(ctx->r3, 0X1);
    // 0x801DFEEC: sll         $t7, $a1, 2
    ctx->r15 = S32(ctx->r5 << 2);
    // 0x801DFEF0: addu        $a0, $a3, $t7
    ctx->r4 = ADD32(ctx->r7, ctx->r15);
    // 0x801DFEF4: beq         $v1, $a2, L_801DFF30
    if (ctx->r3 == ctx->r6) {
        // 0x801DFEF8: lw          $t9, 0x1C($a0)
        ctx->r25 = MEM_W(ctx->r4, 0X1C);
            goto L_801DFF30;
    }
    // 0x801DFEF8: lw          $t9, 0x1C($a0)
    ctx->r25 = MEM_W(ctx->r4, 0X1C);
L_801DFEFC:
    // 0x801DFEFC: lwc1        $f18, 0x0($t9)
    ctx->f18.u32l = MEM_W(ctx->r25, 0X0);
    // 0x801DFF00: lw          $t8, 0x10($a0)
    ctx->r24 = MEM_W(ctx->r4, 0X10);
    // 0x801DFF04: lw          $a1, 0x78($v0)
    ctx->r5 = MEM_W(ctx->r2, 0X78);
    // 0x801DFF08: mul.s       $f18, $f18, $f0
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f18.fl = MUL_S(ctx->f18.fl, ctx->f0.fl);
    // 0x801DFF0C: lwc1        $f16, 0x0($t8)
    ctx->f16.u32l = MEM_W(ctx->r24, 0X0);
    // 0x801DFF10: sll         $t7, $a1, 2
    ctx->r15 = S32(ctx->r5 << 2);
    // 0x801DFF14: addu        $a0, $a3, $t7
    ctx->r4 = ADD32(ctx->r7, ctx->r15);
    // 0x801DFF18: addiu       $v1, $v1, 0x1
    ctx->r3 = ADD32(ctx->r3, 0X1);
    // 0x801DFF1C: addiu       $v0, $v0, 0x4
    ctx->r2 = ADD32(ctx->r2, 0X4);
    // 0x801DFF20: sub.s       $f18, $f16, $f18
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f18.fl = ctx->f16.fl - ctx->f18.fl;
    // 0x801DFF24: swc1        $f18, 0x14($v0)
    MEM_W(0X14, ctx->r2) = ctx->f18.u32l;
    // 0x801DFF28: bne         $v1, $a2, L_801DFEFC
    if (ctx->r3 != ctx->r6) {
        // 0x801DFF2C: lw          $t9, 0x1C($a0)
        ctx->r25 = MEM_W(ctx->r4, 0X1C);
            goto L_801DFEFC;
    }
    // 0x801DFF2C: lw          $t9, 0x1C($a0)
    ctx->r25 = MEM_W(ctx->r4, 0X1C);
L_801DFF30:
    // 0x801DFF30: lwc1        $f18, 0x0($t9)
    ctx->f18.u32l = MEM_W(ctx->r25, 0X0);
    // 0x801DFF34: lw          $t8, 0x10($a0)
    ctx->r24 = MEM_W(ctx->r4, 0X10);
    // 0x801DFF38: addiu       $v0, $v0, 0x4
    ctx->r2 = ADD32(ctx->r2, 0X4);
    // 0x801DFF3C: mul.s       $f18, $f18, $f0
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f18.fl = MUL_S(ctx->f18.fl, ctx->f0.fl);
    // 0x801DFF40: lwc1        $f16, 0x0($t8)
    ctx->f16.u32l = MEM_W(ctx->r24, 0X0);
    // 0x801DFF44: sub.s       $f18, $f16, $f18
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f18.fl = ctx->f16.fl - ctx->f18.fl;
    // 0x801DFF48: swc1        $f18, 0x14($v0)
    MEM_W(0X14, ctx->r2) = ctx->f18.u32l;
    // 0x801DFF4C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x801DFF50: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x801DFF54: jr          $ra
    // 0x801DFF58: nop

    return;
    // 0x801DFF58: nop

;}
RECOMP_FUNC void func_801DFF5C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801DFF5C: addiu       $sp, $sp, -0x38
    ctx->r29 = ADD32(ctx->r29, -0X38);
    // 0x801DFF60: sw          $a0, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r4;
    // 0x801DFF64: lw          $t6, 0x38($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X38);
    // 0x801DFF68: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x801DFF6C: or          $a2, $a1, $zero
    ctx->r6 = ctx->r5 | 0;
    // 0x801DFF70: addiu       $a0, $sp, 0x20
    ctx->r4 = ADD32(ctx->r29, 0X20);
    // 0x801DFF74: jal         0x801DED44
    // 0x801DFF78: lw          $a1, 0xC($t6)
    ctx->r5 = MEM_W(ctx->r14, 0XC);
    func_801DED44(rdram, ctx);
        goto after_0;
    // 0x801DFF78: lw          $a1, 0xC($t6)
    ctx->r5 = MEM_W(ctx->r14, 0XC);
    after_0:
    // 0x801DFF7C: lw          $t7, 0x38($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X38);
    // 0x801DFF80: addiu       $a1, $sp, 0x20
    ctx->r5 = ADD32(ctx->r29, 0X20);
    // 0x801DFF84: addiu       $a2, $sp, 0x2C
    ctx->r6 = ADD32(ctx->r29, 0X2C);
    // 0x801DFF88: lw          $a0, 0x0($t7)
    ctx->r4 = MEM_W(ctx->r15, 0X0);
    // 0x801DFF8C: sw          $zero, 0x10($sp)
    MEM_W(0X10, ctx->r29) = 0;
    // 0x801DFF90: jal         0x801DF08C
    // 0x801DFF94: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_801DF08C(rdram, ctx);
        goto after_1;
    // 0x801DFF94: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_1:
    // 0x801DFF98: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    // 0x801DFF9C: addiu       $sp, $sp, 0x38
    ctx->r29 = ADD32(ctx->r29, 0X38);
    // 0x801DFFA0: jr          $ra
    // 0x801DFFA4: nop

    return;
    // 0x801DFFA4: nop

;}
RECOMP_FUNC void func_801DFFA8(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801DFFA8: addiu       $sp, $sp, -0x48
    ctx->r29 = ADD32(ctx->r29, -0X48);
    // 0x801DFFAC: sw          $a0, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r4;
    // 0x801DFFB0: lw          $t6, 0x48($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X48);
    // 0x801DFFB4: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x801DFFB8: or          $a2, $a1, $zero
    ctx->r6 = ctx->r5 | 0;
    // 0x801DFFBC: addiu       $a0, $sp, 0x24
    ctx->r4 = ADD32(ctx->r29, 0X24);
    // 0x801DFFC0: jal         0x801DED88
    // 0x801DFFC4: lw          $a1, 0xC($t6)
    ctx->r5 = MEM_W(ctx->r14, 0XC);
    func_801DED88(rdram, ctx);
        goto after_0;
    // 0x801DFFC4: lw          $a1, 0xC($t6)
    ctx->r5 = MEM_W(ctx->r14, 0XC);
    after_0:
    // 0x801DFFC8: lw          $t7, 0x48($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X48);
    // 0x801DFFCC: addiu       $a1, $sp, 0x24
    ctx->r5 = ADD32(ctx->r29, 0X24);
    // 0x801DFFD0: addiu       $a2, $sp, 0x30
    ctx->r6 = ADD32(ctx->r29, 0X30);
    // 0x801DFFD4: lw          $a0, 0x0($t7)
    ctx->r4 = MEM_W(ctx->r15, 0X0);
    // 0x801DFFD8: sw          $zero, 0x10($sp)
    MEM_W(0X10, ctx->r29) = 0;
    // 0x801DFFDC: jal         0x801DF08C
    // 0x801DFFE0: addiu       $a3, $sp, 0x3C
    ctx->r7 = ADD32(ctx->r29, 0X3C);
    func_801DF08C(rdram, ctx);
        goto after_1;
    // 0x801DFFE0: addiu       $a3, $sp, 0x3C
    ctx->r7 = ADD32(ctx->r29, 0X3C);
    after_1:
    // 0x801DFFE4: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    // 0x801DFFE8: addiu       $sp, $sp, 0x48
    ctx->r29 = ADD32(ctx->r29, 0X48);
    // 0x801DFFEC: jr          $ra
    // 0x801DFFF0: nop

    return;
    // 0x801DFFF0: nop

;}
RECOMP_FUNC void func_801DFFF4(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801DFFF4: addiu       $sp, $sp, -0x40
    ctx->r29 = ADD32(ctx->r29, -0X40);
    // 0x801DFFF8: sw          $a0, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r4;
    // 0x801DFFFC: lw          $t6, 0x40($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X40);
    // 0x801E0000: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x801E0004: or          $a2, $a1, $zero
    ctx->r6 = ctx->r5 | 0;
    // 0x801E0008: addiu       $a0, $sp, 0x24
    ctx->r4 = ADD32(ctx->r29, 0X24);
    // 0x801E000C: jal         0x801DEDE8
    // 0x801E0010: lw          $a1, 0xC($t6)
    ctx->r5 = MEM_W(ctx->r14, 0XC);
    func_801DEDE8(rdram, ctx);
        goto after_0;
    // 0x801E0010: lw          $a1, 0xC($t6)
    ctx->r5 = MEM_W(ctx->r14, 0XC);
    after_0:
    // 0x801E0014: lw          $t7, 0x40($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X40);
    // 0x801E0018: addiu       $t8, $sp, 0x3C
    ctx->r24 = ADD32(ctx->r29, 0X3C);
    // 0x801E001C: addiu       $a1, $sp, 0x24
    ctx->r5 = ADD32(ctx->r29, 0X24);
    // 0x801E0020: lw          $a0, 0x0($t7)
    ctx->r4 = MEM_W(ctx->r15, 0X0);
    // 0x801E0024: sw          $t8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r24;
    // 0x801E0028: addiu       $a2, $sp, 0x30
    ctx->r6 = ADD32(ctx->r29, 0X30);
    // 0x801E002C: jal         0x801DF08C
    // 0x801E0030: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_801DF08C(rdram, ctx);
        goto after_1;
    // 0x801E0030: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_1:
    // 0x801E0034: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    // 0x801E0038: addiu       $sp, $sp, 0x40
    ctx->r29 = ADD32(ctx->r29, 0X40);
    // 0x801E003C: jr          $ra
    // 0x801E0040: nop

    return;
    // 0x801E0040: nop

;}
RECOMP_FUNC void func_801E0044(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801E0044: addiu       $sp, $sp, -0x48
    ctx->r29 = ADD32(ctx->r29, -0X48);
    // 0x801E0048: sw          $a0, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r4;
    // 0x801E004C: lw          $t6, 0x48($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X48);
    // 0x801E0050: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x801E0054: or          $a2, $a1, $zero
    ctx->r6 = ctx->r5 | 0;
    // 0x801E0058: addiu       $a0, $sp, 0x20
    ctx->r4 = ADD32(ctx->r29, 0X20);
    // 0x801E005C: jal         0x801DEE48
    // 0x801E0060: lw          $a1, 0xC($t6)
    ctx->r5 = MEM_W(ctx->r14, 0XC);
    func_801DEE48(rdram, ctx);
        goto after_0;
    // 0x801E0060: lw          $a1, 0xC($t6)
    ctx->r5 = MEM_W(ctx->r14, 0XC);
    after_0:
    // 0x801E0064: lw          $t7, 0x48($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X48);
    // 0x801E0068: addiu       $t8, $sp, 0x44
    ctx->r24 = ADD32(ctx->r29, 0X44);
    // 0x801E006C: addiu       $a1, $sp, 0x20
    ctx->r5 = ADD32(ctx->r29, 0X20);
    // 0x801E0070: lw          $a0, 0x0($t7)
    ctx->r4 = MEM_W(ctx->r15, 0X0);
    // 0x801E0074: sw          $t8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r24;
    // 0x801E0078: addiu       $a2, $sp, 0x2C
    ctx->r6 = ADD32(ctx->r29, 0X2C);
    // 0x801E007C: jal         0x801DF08C
    // 0x801E0080: addiu       $a3, $sp, 0x38
    ctx->r7 = ADD32(ctx->r29, 0X38);
    func_801DF08C(rdram, ctx);
        goto after_1;
    // 0x801E0080: addiu       $a3, $sp, 0x38
    ctx->r7 = ADD32(ctx->r29, 0X38);
    after_1:
    // 0x801E0084: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    // 0x801E0088: addiu       $sp, $sp, 0x48
    ctx->r29 = ADD32(ctx->r29, 0X48);
    // 0x801E008C: jr          $ra
    // 0x801E0090: nop

    return;
    // 0x801E0090: nop

;}
RECOMP_FUNC void func_801E0094(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801E0094: addiu       $sp, $sp, -0x38
    ctx->r29 = ADD32(ctx->r29, -0X38);
    // 0x801E0098: sw          $a0, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r4;
    // 0x801E009C: lw          $t6, 0x38($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X38);
    // 0x801E00A0: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x801E00A4: or          $a2, $a1, $zero
    ctx->r6 = ctx->r5 | 0;
    // 0x801E00A8: addiu       $a0, $sp, 0x20
    ctx->r4 = ADD32(ctx->r29, 0X20);
    // 0x801E00AC: jal         0x801DED44
    // 0x801E00B0: lw          $a1, 0xC($t6)
    ctx->r5 = MEM_W(ctx->r14, 0XC);
    func_801DED44(rdram, ctx);
        goto after_0;
    // 0x801E00B0: lw          $a1, 0xC($t6)
    ctx->r5 = MEM_W(ctx->r14, 0XC);
    after_0:
    // 0x801E00B4: lw          $t7, 0x38($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X38);
    // 0x801E00B8: addiu       $a1, $sp, 0x20
    ctx->r5 = ADD32(ctx->r29, 0X20);
    // 0x801E00BC: addiu       $a2, $sp, 0x2C
    ctx->r6 = ADD32(ctx->r29, 0X2C);
    // 0x801E00C0: lw          $a0, 0x0($t7)
    ctx->r4 = MEM_W(ctx->r15, 0X0);
    // 0x801E00C4: sw          $zero, 0x10($sp)
    MEM_W(0X10, ctx->r29) = 0;
    // 0x801E00C8: jal         0x801DF2F8
    // 0x801E00CC: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_801DF2F8(rdram, ctx);
        goto after_1;
    // 0x801E00CC: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_1:
    // 0x801E00D0: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    // 0x801E00D4: addiu       $sp, $sp, 0x38
    ctx->r29 = ADD32(ctx->r29, 0X38);
    // 0x801E00D8: jr          $ra
    // 0x801E00DC: nop

    return;
    // 0x801E00DC: nop

;}
RECOMP_FUNC void func_801E00E0(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801E00E0: addiu       $sp, $sp, -0x48
    ctx->r29 = ADD32(ctx->r29, -0X48);
    // 0x801E00E4: sw          $a0, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r4;
    // 0x801E00E8: lw          $t6, 0x48($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X48);
    // 0x801E00EC: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x801E00F0: or          $a2, $a1, $zero
    ctx->r6 = ctx->r5 | 0;
    // 0x801E00F4: addiu       $a0, $sp, 0x24
    ctx->r4 = ADD32(ctx->r29, 0X24);
    // 0x801E00F8: jal         0x801DED88
    // 0x801E00FC: lw          $a1, 0xC($t6)
    ctx->r5 = MEM_W(ctx->r14, 0XC);
    func_801DED88(rdram, ctx);
        goto after_0;
    // 0x801E00FC: lw          $a1, 0xC($t6)
    ctx->r5 = MEM_W(ctx->r14, 0XC);
    after_0:
    // 0x801E0100: lw          $t7, 0x48($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X48);
    // 0x801E0104: addiu       $a1, $sp, 0x24
    ctx->r5 = ADD32(ctx->r29, 0X24);
    // 0x801E0108: addiu       $a2, $sp, 0x30
    ctx->r6 = ADD32(ctx->r29, 0X30);
    // 0x801E010C: lw          $a0, 0x0($t7)
    ctx->r4 = MEM_W(ctx->r15, 0X0);
    // 0x801E0110: sw          $zero, 0x10($sp)
    MEM_W(0X10, ctx->r29) = 0;
    // 0x801E0114: jal         0x801DF2F8
    // 0x801E0118: addiu       $a3, $sp, 0x3C
    ctx->r7 = ADD32(ctx->r29, 0X3C);
    func_801DF2F8(rdram, ctx);
        goto after_1;
    // 0x801E0118: addiu       $a3, $sp, 0x3C
    ctx->r7 = ADD32(ctx->r29, 0X3C);
    after_1:
    // 0x801E011C: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    // 0x801E0120: addiu       $sp, $sp, 0x48
    ctx->r29 = ADD32(ctx->r29, 0X48);
    // 0x801E0124: jr          $ra
    // 0x801E0128: nop

    return;
    // 0x801E0128: nop

;}
RECOMP_FUNC void func_801E012C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801E012C: addiu       $sp, $sp, -0x40
    ctx->r29 = ADD32(ctx->r29, -0X40);
    // 0x801E0130: sw          $a0, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r4;
    // 0x801E0134: lw          $t6, 0x40($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X40);
    // 0x801E0138: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x801E013C: or          $a2, $a1, $zero
    ctx->r6 = ctx->r5 | 0;
    // 0x801E0140: addiu       $a0, $sp, 0x24
    ctx->r4 = ADD32(ctx->r29, 0X24);
    // 0x801E0144: jal         0x801DEDE8
    // 0x801E0148: lw          $a1, 0xC($t6)
    ctx->r5 = MEM_W(ctx->r14, 0XC);
    func_801DEDE8(rdram, ctx);
        goto after_0;
    // 0x801E0148: lw          $a1, 0xC($t6)
    ctx->r5 = MEM_W(ctx->r14, 0XC);
    after_0:
    // 0x801E014C: lw          $t7, 0x40($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X40);
    // 0x801E0150: addiu       $t8, $sp, 0x3C
    ctx->r24 = ADD32(ctx->r29, 0X3C);
    // 0x801E0154: addiu       $a1, $sp, 0x24
    ctx->r5 = ADD32(ctx->r29, 0X24);
    // 0x801E0158: lw          $a0, 0x0($t7)
    ctx->r4 = MEM_W(ctx->r15, 0X0);
    // 0x801E015C: sw          $t8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r24;
    // 0x801E0160: addiu       $a2, $sp, 0x30
    ctx->r6 = ADD32(ctx->r29, 0X30);
    // 0x801E0164: jal         0x801DF2F8
    // 0x801E0168: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_801DF2F8(rdram, ctx);
        goto after_1;
    // 0x801E0168: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_1:
    // 0x801E016C: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    // 0x801E0170: addiu       $sp, $sp, 0x40
    ctx->r29 = ADD32(ctx->r29, 0X40);
    // 0x801E0174: jr          $ra
    // 0x801E0178: nop

    return;
    // 0x801E0178: nop

;}
RECOMP_FUNC void func_801E017C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801E017C: addiu       $sp, $sp, -0x48
    ctx->r29 = ADD32(ctx->r29, -0X48);
    // 0x801E0180: sw          $a0, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r4;
    // 0x801E0184: lw          $t6, 0x48($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X48);
    // 0x801E0188: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x801E018C: or          $a2, $a1, $zero
    ctx->r6 = ctx->r5 | 0;
    // 0x801E0190: addiu       $a0, $sp, 0x20
    ctx->r4 = ADD32(ctx->r29, 0X20);
    // 0x801E0194: jal         0x801DEE48
    // 0x801E0198: lw          $a1, 0xC($t6)
    ctx->r5 = MEM_W(ctx->r14, 0XC);
    func_801DEE48(rdram, ctx);
        goto after_0;
    // 0x801E0198: lw          $a1, 0xC($t6)
    ctx->r5 = MEM_W(ctx->r14, 0XC);
    after_0:
    // 0x801E019C: lw          $t7, 0x48($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X48);
    // 0x801E01A0: addiu       $t8, $sp, 0x44
    ctx->r24 = ADD32(ctx->r29, 0X44);
    // 0x801E01A4: addiu       $a1, $sp, 0x20
    ctx->r5 = ADD32(ctx->r29, 0X20);
    // 0x801E01A8: lw          $a0, 0x0($t7)
    ctx->r4 = MEM_W(ctx->r15, 0X0);
    // 0x801E01AC: sw          $t8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r24;
    // 0x801E01B0: addiu       $a2, $sp, 0x2C
    ctx->r6 = ADD32(ctx->r29, 0X2C);
    // 0x801E01B4: jal         0x801DF2F8
    // 0x801E01B8: addiu       $a3, $sp, 0x38
    ctx->r7 = ADD32(ctx->r29, 0X38);
    func_801DF2F8(rdram, ctx);
        goto after_1;
    // 0x801E01B8: addiu       $a3, $sp, 0x38
    ctx->r7 = ADD32(ctx->r29, 0X38);
    after_1:
    // 0x801E01BC: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    // 0x801E01C0: addiu       $sp, $sp, 0x48
    ctx->r29 = ADD32(ctx->r29, 0X48);
    // 0x801E01C4: jr          $ra
    // 0x801E01C8: nop

    return;
    // 0x801E01C8: nop

;}
RECOMP_FUNC void func_801E01CC(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801E01CC: addiu       $sp, $sp, -0x38
    ctx->r29 = ADD32(ctx->r29, -0X38);
    // 0x801E01D0: sw          $a0, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r4;
    // 0x801E01D4: lw          $t6, 0x38($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X38);
    // 0x801E01D8: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x801E01DC: or          $a2, $a1, $zero
    ctx->r6 = ctx->r5 | 0;
    // 0x801E01E0: addiu       $a0, $sp, 0x20
    ctx->r4 = ADD32(ctx->r29, 0X20);
    // 0x801E01E4: jal         0x801DED44
    // 0x801E01E8: lw          $a1, 0xC($t6)
    ctx->r5 = MEM_W(ctx->r14, 0XC);
    func_801DED44(rdram, ctx);
        goto after_0;
    // 0x801E01E8: lw          $a1, 0xC($t6)
    ctx->r5 = MEM_W(ctx->r14, 0XC);
    after_0:
    // 0x801E01EC: lw          $t7, 0x38($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X38);
    // 0x801E01F0: addiu       $a1, $sp, 0x2C
    ctx->r5 = ADD32(ctx->r29, 0X2C);
    // 0x801E01F4: addiu       $a2, $sp, 0x20
    ctx->r6 = ADD32(ctx->r29, 0X20);
    // 0x801E01F8: lw          $a0, 0x0($t7)
    ctx->r4 = MEM_W(ctx->r15, 0X0);
    // 0x801E01FC: sw          $zero, 0x10($sp)
    MEM_W(0X10, ctx->r29) = 0;
    // 0x801E0200: jal         0x801DF2F8
    // 0x801E0204: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_801DF2F8(rdram, ctx);
        goto after_1;
    // 0x801E0204: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_1:
    // 0x801E0208: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    // 0x801E020C: addiu       $sp, $sp, 0x38
    ctx->r29 = ADD32(ctx->r29, 0X38);
    // 0x801E0210: jr          $ra
    // 0x801E0214: nop

    return;
    // 0x801E0214: nop

;}
RECOMP_FUNC void func_801E0218(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801E0218: addiu       $sp, $sp, -0x48
    ctx->r29 = ADD32(ctx->r29, -0X48);
    // 0x801E021C: sw          $a0, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r4;
    // 0x801E0220: lw          $t6, 0x48($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X48);
    // 0x801E0224: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x801E0228: or          $a2, $a1, $zero
    ctx->r6 = ctx->r5 | 0;
    // 0x801E022C: addiu       $a0, $sp, 0x24
    ctx->r4 = ADD32(ctx->r29, 0X24);
    // 0x801E0230: jal         0x801DED88
    // 0x801E0234: lw          $a1, 0xC($t6)
    ctx->r5 = MEM_W(ctx->r14, 0XC);
    func_801DED88(rdram, ctx);
        goto after_0;
    // 0x801E0234: lw          $a1, 0xC($t6)
    ctx->r5 = MEM_W(ctx->r14, 0XC);
    after_0:
    // 0x801E0238: lw          $t7, 0x48($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X48);
    // 0x801E023C: addiu       $a1, $sp, 0x30
    ctx->r5 = ADD32(ctx->r29, 0X30);
    // 0x801E0240: addiu       $a2, $sp, 0x24
    ctx->r6 = ADD32(ctx->r29, 0X24);
    // 0x801E0244: lw          $a0, 0x0($t7)
    ctx->r4 = MEM_W(ctx->r15, 0X0);
    // 0x801E0248: sw          $zero, 0x10($sp)
    MEM_W(0X10, ctx->r29) = 0;
    // 0x801E024C: jal         0x801DF2F8
    // 0x801E0250: addiu       $a3, $sp, 0x3C
    ctx->r7 = ADD32(ctx->r29, 0X3C);
    func_801DF2F8(rdram, ctx);
        goto after_1;
    // 0x801E0250: addiu       $a3, $sp, 0x3C
    ctx->r7 = ADD32(ctx->r29, 0X3C);
    after_1:
    // 0x801E0254: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    // 0x801E0258: addiu       $sp, $sp, 0x48
    ctx->r29 = ADD32(ctx->r29, 0X48);
    // 0x801E025C: jr          $ra
    // 0x801E0260: nop

    return;
    // 0x801E0260: nop

;}
RECOMP_FUNC void func_801E0264(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801E0264: addiu       $sp, $sp, -0x40
    ctx->r29 = ADD32(ctx->r29, -0X40);
    // 0x801E0268: sw          $a0, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r4;
    // 0x801E026C: lw          $t6, 0x40($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X40);
    // 0x801E0270: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x801E0274: or          $a2, $a1, $zero
    ctx->r6 = ctx->r5 | 0;
    // 0x801E0278: addiu       $a0, $sp, 0x24
    ctx->r4 = ADD32(ctx->r29, 0X24);
    // 0x801E027C: jal         0x801DEDE8
    // 0x801E0280: lw          $a1, 0xC($t6)
    ctx->r5 = MEM_W(ctx->r14, 0XC);
    func_801DEDE8(rdram, ctx);
        goto after_0;
    // 0x801E0280: lw          $a1, 0xC($t6)
    ctx->r5 = MEM_W(ctx->r14, 0XC);
    after_0:
    // 0x801E0284: lw          $t7, 0x40($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X40);
    // 0x801E0288: addiu       $t8, $sp, 0x3C
    ctx->r24 = ADD32(ctx->r29, 0X3C);
    // 0x801E028C: addiu       $a1, $sp, 0x30
    ctx->r5 = ADD32(ctx->r29, 0X30);
    // 0x801E0290: lw          $a0, 0x0($t7)
    ctx->r4 = MEM_W(ctx->r15, 0X0);
    // 0x801E0294: sw          $t8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r24;
    // 0x801E0298: addiu       $a2, $sp, 0x24
    ctx->r6 = ADD32(ctx->r29, 0X24);
    // 0x801E029C: jal         0x801DF2F8
    // 0x801E02A0: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_801DF2F8(rdram, ctx);
        goto after_1;
    // 0x801E02A0: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_1:
    // 0x801E02A4: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    // 0x801E02A8: addiu       $sp, $sp, 0x40
    ctx->r29 = ADD32(ctx->r29, 0X40);
    // 0x801E02AC: jr          $ra
    // 0x801E02B0: nop

    return;
    // 0x801E02B0: nop

;}
RECOMP_FUNC void func_801E02B4(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801E02B4: addiu       $sp, $sp, -0x48
    ctx->r29 = ADD32(ctx->r29, -0X48);
    // 0x801E02B8: sw          $a0, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r4;
    // 0x801E02BC: lw          $t6, 0x48($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X48);
    // 0x801E02C0: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x801E02C4: or          $a2, $a1, $zero
    ctx->r6 = ctx->r5 | 0;
    // 0x801E02C8: addiu       $a0, $sp, 0x20
    ctx->r4 = ADD32(ctx->r29, 0X20);
    // 0x801E02CC: jal         0x801DEE48
    // 0x801E02D0: lw          $a1, 0xC($t6)
    ctx->r5 = MEM_W(ctx->r14, 0XC);
    func_801DEE48(rdram, ctx);
        goto after_0;
    // 0x801E02D0: lw          $a1, 0xC($t6)
    ctx->r5 = MEM_W(ctx->r14, 0XC);
    after_0:
    // 0x801E02D4: lw          $t7, 0x48($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X48);
    // 0x801E02D8: addiu       $t8, $sp, 0x44
    ctx->r24 = ADD32(ctx->r29, 0X44);
    // 0x801E02DC: addiu       $a1, $sp, 0x2C
    ctx->r5 = ADD32(ctx->r29, 0X2C);
    // 0x801E02E0: lw          $a0, 0x0($t7)
    ctx->r4 = MEM_W(ctx->r15, 0X0);
    // 0x801E02E4: sw          $t8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r24;
    // 0x801E02E8: addiu       $a2, $sp, 0x20
    ctx->r6 = ADD32(ctx->r29, 0X20);
    // 0x801E02EC: jal         0x801DF2F8
    // 0x801E02F0: addiu       $a3, $sp, 0x38
    ctx->r7 = ADD32(ctx->r29, 0X38);
    func_801DF2F8(rdram, ctx);
        goto after_1;
    // 0x801E02F0: addiu       $a3, $sp, 0x38
    ctx->r7 = ADD32(ctx->r29, 0X38);
    after_1:
    // 0x801E02F4: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    // 0x801E02F8: addiu       $sp, $sp, 0x48
    ctx->r29 = ADD32(ctx->r29, 0X48);
    // 0x801E02FC: jr          $ra
    // 0x801E0300: nop

    return;
    // 0x801E0300: nop

;}
RECOMP_FUNC void func_801E0304(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801E0304: addiu       $sp, $sp, -0x68
    ctx->r29 = ADD32(ctx->r29, -0X68);
    // 0x801E0308: sw          $s0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r16;
    // 0x801E030C: or          $s0, $a0, $zero
    ctx->r16 = ctx->r4 | 0;
    // 0x801E0310: sw          $ra, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r31;
    // 0x801E0314: or          $a2, $a1, $zero
    ctx->r6 = ctx->r5 | 0;
    // 0x801E0318: lw          $a1, 0xC($s0)
    ctx->r5 = MEM_W(ctx->r16, 0XC);
    // 0x801E031C: jal         0x801DED44
    // 0x801E0320: addiu       $a0, $sp, 0x50
    ctx->r4 = ADD32(ctx->r29, 0X50);
    func_801DED44(rdram, ctx);
        goto after_0;
    // 0x801E0320: addiu       $a0, $sp, 0x50
    ctx->r4 = ADD32(ctx->r29, 0X50);
    after_0:
    // 0x801E0324: lw          $t1, 0x0($s0)
    ctx->r9 = MEM_W(ctx->r16, 0X0);
    // 0x801E0328: lw          $t6, 0x24($s0)
    ctx->r14 = MEM_W(ctx->r16, 0X24);
    // 0x801E032C: lw          $t7, 0x1C($s0)
    ctx->r15 = MEM_W(ctx->r16, 0X1C);
    // 0x801E0330: addiu       $t1, $t1, 0x5C
    ctx->r9 = ADD32(ctx->r9, 0X5C);
    // 0x801E0334: lwc1        $f12, 0x0($t6)
    ctx->f12.u32l = MEM_W(ctx->r14, 0X0);
    // 0x801E0338: lwc1        $f14, 0x0($t7)
    ctx->f14.u32l = MEM_W(ctx->r15, 0X0);
    // 0x801E033C: jal         0x801ED154
    // 0x801E0340: sw          $t1, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r9;
    func_801ED154(rdram, ctx);
        goto after_1;
    // 0x801E0340: sw          $t1, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r9;
    after_1:
    // 0x801E0344: lw          $t1, 0x38($sp)
    ctx->r9 = MEM_W(ctx->r29, 0X38);
    // 0x801E0348: mtc1        $zero, $f6
    ctx->f6.u32l = 0;
    // 0x801E034C: lui         $at, 0x4580
    ctx->r1 = S32(0X4580 << 16);
    // 0x801E0350: swc1        $f0, 0xC($t1)
    MEM_W(0XC, ctx->r9) = ctx->f0.u32l;
    // 0x801E0354: lwc1        $f4, 0x54($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X54);
    // 0x801E0358: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
    // 0x801E035C: swc1        $f6, 0x10($t1)
    MEM_W(0X10, ctx->r9) = ctx->f6.u32l;
    // 0x801E0360: add.s       $f12, $f4, $f0
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f12.fl = ctx->f4.fl + ctx->f0.fl;
    // 0x801E0364: lwc1        $f14, 0x58($sp)
    ctx->f14.u32l = MEM_W(ctx->r29, 0X58);
    // 0x801E0368: lui         $at, 0x43B4
    ctx->r1 = S32(0X43B4 << 16);
    // 0x801E036C: mtc1        $at, $f18
    ctx->f18.u32l = ctx->r1;
    // 0x801E0370: mul.s       $f8, $f12, $f16
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f8.fl = MUL_S(ctx->f12.fl, ctx->f16.fl);
    // 0x801E0374: lui         $t0, 0x8015
    ctx->r8 = S32(0X8015 << 16);
    // 0x801E0378: addiu       $t0, $t0, 0x4350
    ctx->r8 = ADD32(ctx->r8, 0X4350);
    // 0x801E037C: mul.s       $f6, $f14, $f16
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f6.fl = MUL_S(ctx->f14.fl, ctx->f16.fl);
    // 0x801E0380: addiu       $a1, $sp, 0x44
    ctx->r5 = ADD32(ctx->r29, 0X44);
    // 0x801E0384: addiu       $a2, $sp, 0x5C
    ctx->r6 = ADD32(ctx->r29, 0X5C);
    // 0x801E0388: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    // 0x801E038C: div.s       $f10, $f8, $f18
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f10.fl = DIV_S(ctx->f8.fl, ctx->f18.fl);
    // 0x801E0390: div.s       $f8, $f6, $f18
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f8.fl = DIV_S(ctx->f6.fl, ctx->f18.fl);
    // 0x801E0394: trunc.w.s   $f4, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    ctx->f4.u32l = TRUNC_W_S(ctx->f10.fl);
    // 0x801E0398: mfc1        $v0, $f4
    ctx->r2 = (int32_t)ctx->f4.u32l;
    // 0x801E039C: lwc1        $f4, 0x50($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X50);
    // 0x801E03A0: addiu       $t6, $v0, 0x400
    ctx->r14 = ADD32(ctx->r2, 0X400);
    // 0x801E03A4: andi        $t7, $t6, 0xFFF
    ctx->r15 = ctx->r14 & 0XFFF;
    // 0x801E03A8: sll         $t8, $t7, 2
    ctx->r24 = S32(ctx->r15 << 2);
    // 0x801E03AC: addu        $t9, $t0, $t8
    ctx->r25 = ADD32(ctx->r8, ctx->r24);
    // 0x801E03B0: andi        $t7, $v0, 0xFFF
    ctx->r15 = ctx->r2 & 0XFFF;
    // 0x801E03B4: sll         $t8, $t7, 2
    ctx->r24 = S32(ctx->r15 << 2);
    // 0x801E03B8: trunc.w.s   $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.u32l = TRUNC_W_S(ctx->f8.fl);
    // 0x801E03BC: lwc1        $f8, 0x0($t9)
    ctx->f8.u32l = MEM_W(ctx->r25, 0X0);
    // 0x801E03C0: addu        $t9, $t0, $t8
    ctx->r25 = ADD32(ctx->r8, ctx->r24);
    // 0x801E03C4: mfc1        $v1, $f10
    ctx->r3 = (int32_t)ctx->f10.u32l;
    // 0x801E03C8: nop

    // 0x801E03CC: addiu       $t2, $v1, 0x400
    ctx->r10 = ADD32(ctx->r3, 0X400);
    // 0x801E03D0: andi        $t3, $t2, 0xFFF
    ctx->r11 = ctx->r10 & 0XFFF;
    // 0x801E03D4: sll         $t4, $t3, 2
    ctx->r12 = S32(ctx->r11 << 2);
    // 0x801E03D8: addu        $t5, $t0, $t4
    ctx->r13 = ADD32(ctx->r8, ctx->r12);
    // 0x801E03DC: lwc1        $f6, 0x0($t5)
    ctx->f6.u32l = MEM_W(ctx->r13, 0X0);
    // 0x801E03E0: lw          $t2, 0x10($s0)
    ctx->r10 = MEM_W(ctx->r16, 0X10);
    // 0x801E03E4: andi        $t3, $v1, 0xFFF
    ctx->r11 = ctx->r3 & 0XFFF;
    // 0x801E03E8: mul.s       $f2, $f4, $f6
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f2.fl = MUL_S(ctx->f4.fl, ctx->f6.fl);
    // 0x801E03EC: lwc1        $f6, 0x0($t2)
    ctx->f6.u32l = MEM_W(ctx->r10, 0X0);
    // 0x801E03F0: sll         $t4, $t3, 2
    ctx->r12 = S32(ctx->r11 << 2);
    // 0x801E03F4: addu        $t5, $t0, $t4
    ctx->r13 = ADD32(ctx->r8, ctx->r12);
    // 0x801E03F8: mul.s       $f10, $f8, $f2
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f10.fl = MUL_S(ctx->f8.fl, ctx->f2.fl);
    // 0x801E03FC: add.s       $f8, $f10, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = ctx->f10.fl + ctx->f6.fl;
    // 0x801E0400: lwc1        $f10, 0x0($t5)
    ctx->f10.u32l = MEM_W(ctx->r13, 0X0);
    // 0x801E0404: mul.s       $f6, $f10, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = MUL_S(ctx->f10.fl, ctx->f4.fl);
    // 0x801E0408: swc1        $f8, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->f8.u32l;
    // 0x801E040C: lw          $t6, 0x14($s0)
    ctx->r14 = MEM_W(ctx->r16, 0X14);
    // 0x801E0410: lwc1        $f4, 0x0($t9)
    ctx->f4.u32l = MEM_W(ctx->r25, 0X0);
    // 0x801E0414: lwc1        $f8, 0x0($t6)
    ctx->f8.u32l = MEM_W(ctx->r14, 0X0);
    // 0x801E0418: add.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = ctx->f6.fl + ctx->f8.fl;
    // 0x801E041C: mul.s       $f6, $f4, $f2
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f6.fl = MUL_S(ctx->f4.fl, ctx->f2.fl);
    // 0x801E0420: swc1        $f10, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->f10.u32l;
    // 0x801E0424: lw          $t2, 0x18($s0)
    ctx->r10 = MEM_W(ctx->r16, 0X18);
    // 0x801E0428: lwc1        $f8, 0x0($t2)
    ctx->f8.u32l = MEM_W(ctx->r10, 0X0);
    // 0x801E042C: add.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = ctx->f6.fl + ctx->f8.fl;
    // 0x801E0430: swc1        $f10, 0x4C($sp)
    MEM_W(0X4C, ctx->r29) = ctx->f10.u32l;
    // 0x801E0434: lw          $a0, 0x0($s0)
    ctx->r4 = MEM_W(ctx->r16, 0X0);
    // 0x801E0438: jal         0x801DF2F8
    // 0x801E043C: sw          $zero, 0x10($sp)
    MEM_W(0X10, ctx->r29) = 0;
    func_801DF2F8(rdram, ctx);
        goto after_2;
    // 0x801E043C: sw          $zero, 0x10($sp)
    MEM_W(0X10, ctx->r29) = 0;
    after_2:
    // 0x801E0440: lw          $ra, 0x24($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X24);
    // 0x801E0444: lw          $s0, 0x20($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X20);
    // 0x801E0448: addiu       $sp, $sp, 0x68
    ctx->r29 = ADD32(ctx->r29, 0X68);
    // 0x801E044C: jr          $ra
    // 0x801E0450: nop

    return;
    // 0x801E0450: nop

;}
RECOMP_FUNC void func_801E0454(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801E0454: addiu       $sp, $sp, -0x70
    ctx->r29 = ADD32(ctx->r29, -0X70);
    // 0x801E0458: sw          $s0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r16;
    // 0x801E045C: or          $s0, $a0, $zero
    ctx->r16 = ctx->r4 | 0;
    // 0x801E0460: sw          $ra, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r31;
    // 0x801E0464: or          $a2, $a1, $zero
    ctx->r6 = ctx->r5 | 0;
    // 0x801E0468: lw          $a1, 0xC($s0)
    ctx->r5 = MEM_W(ctx->r16, 0XC);
    // 0x801E046C: jal         0x801DED88
    // 0x801E0470: addiu       $a0, $sp, 0x4C
    ctx->r4 = ADD32(ctx->r29, 0X4C);
    func_801DED88(rdram, ctx);
        goto after_0;
    // 0x801E0470: addiu       $a0, $sp, 0x4C
    ctx->r4 = ADD32(ctx->r29, 0X4C);
    after_0:
    // 0x801E0474: lw          $t1, 0x0($s0)
    ctx->r9 = MEM_W(ctx->r16, 0X0);
    // 0x801E0478: lw          $t6, 0x24($s0)
    ctx->r14 = MEM_W(ctx->r16, 0X24);
    // 0x801E047C: lw          $t7, 0x1C($s0)
    ctx->r15 = MEM_W(ctx->r16, 0X1C);
    // 0x801E0480: addiu       $t1, $t1, 0x5C
    ctx->r9 = ADD32(ctx->r9, 0X5C);
    // 0x801E0484: lwc1        $f12, 0x0($t6)
    ctx->f12.u32l = MEM_W(ctx->r14, 0X0);
    // 0x801E0488: lwc1        $f14, 0x0($t7)
    ctx->f14.u32l = MEM_W(ctx->r15, 0X0);
    // 0x801E048C: jal         0x801ED154
    // 0x801E0490: sw          $t1, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r9;
    func_801ED154(rdram, ctx);
        goto after_1;
    // 0x801E0490: sw          $t1, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r9;
    after_1:
    // 0x801E0494: lw          $t1, 0x34($sp)
    ctx->r9 = MEM_W(ctx->r29, 0X34);
    // 0x801E0498: mtc1        $zero, $f6
    ctx->f6.u32l = 0;
    // 0x801E049C: lui         $at, 0x4580
    ctx->r1 = S32(0X4580 << 16);
    // 0x801E04A0: swc1        $f0, 0xC($t1)
    MEM_W(0XC, ctx->r9) = ctx->f0.u32l;
    // 0x801E04A4: lwc1        $f4, 0x50($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X50);
    // 0x801E04A8: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
    // 0x801E04AC: swc1        $f6, 0x10($t1)
    MEM_W(0X10, ctx->r9) = ctx->f6.u32l;
    // 0x801E04B0: add.s       $f12, $f4, $f0
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f12.fl = ctx->f4.fl + ctx->f0.fl;
    // 0x801E04B4: lwc1        $f14, 0x54($sp)
    ctx->f14.u32l = MEM_W(ctx->r29, 0X54);
    // 0x801E04B8: lui         $at, 0x43B4
    ctx->r1 = S32(0X43B4 << 16);
    // 0x801E04BC: mtc1        $at, $f18
    ctx->f18.u32l = ctx->r1;
    // 0x801E04C0: mul.s       $f8, $f12, $f16
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f8.fl = MUL_S(ctx->f12.fl, ctx->f16.fl);
    // 0x801E04C4: lui         $t0, 0x8015
    ctx->r8 = S32(0X8015 << 16);
    // 0x801E04C8: addiu       $t0, $t0, 0x4350
    ctx->r8 = ADD32(ctx->r8, 0X4350);
    // 0x801E04CC: mul.s       $f6, $f14, $f16
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f6.fl = MUL_S(ctx->f14.fl, ctx->f16.fl);
    // 0x801E04D0: addiu       $a1, $sp, 0x40
    ctx->r5 = ADD32(ctx->r29, 0X40);
    // 0x801E04D4: addiu       $a2, $sp, 0x58
    ctx->r6 = ADD32(ctx->r29, 0X58);
    // 0x801E04D8: addiu       $a3, $sp, 0x64
    ctx->r7 = ADD32(ctx->r29, 0X64);
    // 0x801E04DC: div.s       $f10, $f8, $f18
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f10.fl = DIV_S(ctx->f8.fl, ctx->f18.fl);
    // 0x801E04E0: div.s       $f8, $f6, $f18
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f8.fl = DIV_S(ctx->f6.fl, ctx->f18.fl);
    // 0x801E04E4: trunc.w.s   $f4, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    ctx->f4.u32l = TRUNC_W_S(ctx->f10.fl);
    // 0x801E04E8: mfc1        $v0, $f4
    ctx->r2 = (int32_t)ctx->f4.u32l;
    // 0x801E04EC: lwc1        $f4, 0x4C($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X4C);
    // 0x801E04F0: addiu       $t6, $v0, 0x400
    ctx->r14 = ADD32(ctx->r2, 0X400);
    // 0x801E04F4: andi        $t7, $t6, 0xFFF
    ctx->r15 = ctx->r14 & 0XFFF;
    // 0x801E04F8: sll         $t8, $t7, 2
    ctx->r24 = S32(ctx->r15 << 2);
    // 0x801E04FC: addu        $t9, $t0, $t8
    ctx->r25 = ADD32(ctx->r8, ctx->r24);
    // 0x801E0500: andi        $t7, $v0, 0xFFF
    ctx->r15 = ctx->r2 & 0XFFF;
    // 0x801E0504: sll         $t8, $t7, 2
    ctx->r24 = S32(ctx->r15 << 2);
    // 0x801E0508: trunc.w.s   $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.u32l = TRUNC_W_S(ctx->f8.fl);
    // 0x801E050C: lwc1        $f8, 0x0($t9)
    ctx->f8.u32l = MEM_W(ctx->r25, 0X0);
    // 0x801E0510: addu        $t9, $t0, $t8
    ctx->r25 = ADD32(ctx->r8, ctx->r24);
    // 0x801E0514: mfc1        $v1, $f10
    ctx->r3 = (int32_t)ctx->f10.u32l;
    // 0x801E0518: nop

    // 0x801E051C: addiu       $t2, $v1, 0x400
    ctx->r10 = ADD32(ctx->r3, 0X400);
    // 0x801E0520: andi        $t3, $t2, 0xFFF
    ctx->r11 = ctx->r10 & 0XFFF;
    // 0x801E0524: sll         $t4, $t3, 2
    ctx->r12 = S32(ctx->r11 << 2);
    // 0x801E0528: addu        $t5, $t0, $t4
    ctx->r13 = ADD32(ctx->r8, ctx->r12);
    // 0x801E052C: lwc1        $f6, 0x0($t5)
    ctx->f6.u32l = MEM_W(ctx->r13, 0X0);
    // 0x801E0530: lw          $t2, 0x10($s0)
    ctx->r10 = MEM_W(ctx->r16, 0X10);
    // 0x801E0534: andi        $t3, $v1, 0xFFF
    ctx->r11 = ctx->r3 & 0XFFF;
    // 0x801E0538: mul.s       $f2, $f4, $f6
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f2.fl = MUL_S(ctx->f4.fl, ctx->f6.fl);
    // 0x801E053C: lwc1        $f6, 0x0($t2)
    ctx->f6.u32l = MEM_W(ctx->r10, 0X0);
    // 0x801E0540: sll         $t4, $t3, 2
    ctx->r12 = S32(ctx->r11 << 2);
    // 0x801E0544: addu        $t5, $t0, $t4
    ctx->r13 = ADD32(ctx->r8, ctx->r12);
    // 0x801E0548: mul.s       $f10, $f8, $f2
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f10.fl = MUL_S(ctx->f8.fl, ctx->f2.fl);
    // 0x801E054C: add.s       $f8, $f10, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = ctx->f10.fl + ctx->f6.fl;
    // 0x801E0550: lwc1        $f10, 0x0($t5)
    ctx->f10.u32l = MEM_W(ctx->r13, 0X0);
    // 0x801E0554: mul.s       $f6, $f10, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = MUL_S(ctx->f10.fl, ctx->f4.fl);
    // 0x801E0558: swc1        $f8, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->f8.u32l;
    // 0x801E055C: lw          $t6, 0x14($s0)
    ctx->r14 = MEM_W(ctx->r16, 0X14);
    // 0x801E0560: lwc1        $f4, 0x0($t9)
    ctx->f4.u32l = MEM_W(ctx->r25, 0X0);
    // 0x801E0564: lwc1        $f8, 0x0($t6)
    ctx->f8.u32l = MEM_W(ctx->r14, 0X0);
    // 0x801E0568: add.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = ctx->f6.fl + ctx->f8.fl;
    // 0x801E056C: mul.s       $f6, $f4, $f2
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f6.fl = MUL_S(ctx->f4.fl, ctx->f2.fl);
    // 0x801E0570: swc1        $f10, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->f10.u32l;
    // 0x801E0574: lw          $t2, 0x18($s0)
    ctx->r10 = MEM_W(ctx->r16, 0X18);
    // 0x801E0578: lwc1        $f8, 0x0($t2)
    ctx->f8.u32l = MEM_W(ctx->r10, 0X0);
    // 0x801E057C: add.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = ctx->f6.fl + ctx->f8.fl;
    // 0x801E0580: swc1        $f10, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->f10.u32l;
    // 0x801E0584: lw          $a0, 0x0($s0)
    ctx->r4 = MEM_W(ctx->r16, 0X0);
    // 0x801E0588: jal         0x801DF2F8
    // 0x801E058C: sw          $zero, 0x10($sp)
    MEM_W(0X10, ctx->r29) = 0;
    func_801DF2F8(rdram, ctx);
        goto after_2;
    // 0x801E058C: sw          $zero, 0x10($sp)
    MEM_W(0X10, ctx->r29) = 0;
    after_2:
    // 0x801E0590: lw          $ra, 0x24($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X24);
    // 0x801E0594: lw          $s0, 0x20($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X20);
    // 0x801E0598: addiu       $sp, $sp, 0x70
    ctx->r29 = ADD32(ctx->r29, 0X70);
    // 0x801E059C: jr          $ra
    // 0x801E05A0: nop

    return;
    // 0x801E05A0: nop

;}
RECOMP_FUNC void func_801E05A4(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801E05A4: addiu       $sp, $sp, -0x68
    ctx->r29 = ADD32(ctx->r29, -0X68);
    // 0x801E05A8: sw          $s0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r16;
    // 0x801E05AC: or          $s0, $a0, $zero
    ctx->r16 = ctx->r4 | 0;
    // 0x801E05B0: sw          $ra, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r31;
    // 0x801E05B4: or          $a2, $a1, $zero
    ctx->r6 = ctx->r5 | 0;
    // 0x801E05B8: lw          $a1, 0xC($s0)
    ctx->r5 = MEM_W(ctx->r16, 0XC);
    // 0x801E05BC: jal         0x801DEDE8
    // 0x801E05C0: addiu       $a0, $sp, 0x4C
    ctx->r4 = ADD32(ctx->r29, 0X4C);
    func_801DEDE8(rdram, ctx);
        goto after_0;
    // 0x801E05C0: addiu       $a0, $sp, 0x4C
    ctx->r4 = ADD32(ctx->r29, 0X4C);
    after_0:
    // 0x801E05C4: lw          $t1, 0x0($s0)
    ctx->r9 = MEM_W(ctx->r16, 0X0);
    // 0x801E05C8: lw          $t6, 0x24($s0)
    ctx->r14 = MEM_W(ctx->r16, 0X24);
    // 0x801E05CC: lw          $t7, 0x1C($s0)
    ctx->r15 = MEM_W(ctx->r16, 0X1C);
    // 0x801E05D0: addiu       $t1, $t1, 0x5C
    ctx->r9 = ADD32(ctx->r9, 0X5C);
    // 0x801E05D4: lwc1        $f12, 0x0($t6)
    ctx->f12.u32l = MEM_W(ctx->r14, 0X0);
    // 0x801E05D8: lwc1        $f14, 0x0($t7)
    ctx->f14.u32l = MEM_W(ctx->r15, 0X0);
    // 0x801E05DC: jal         0x801ED154
    // 0x801E05E0: sw          $t1, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r9;
    func_801ED154(rdram, ctx);
        goto after_1;
    // 0x801E05E0: sw          $t1, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r9;
    after_1:
    // 0x801E05E4: lw          $t1, 0x34($sp)
    ctx->r9 = MEM_W(ctx->r29, 0X34);
    // 0x801E05E8: mtc1        $zero, $f6
    ctx->f6.u32l = 0;
    // 0x801E05EC: lui         $at, 0x4580
    ctx->r1 = S32(0X4580 << 16);
    // 0x801E05F0: swc1        $f0, 0xC($t1)
    MEM_W(0XC, ctx->r9) = ctx->f0.u32l;
    // 0x801E05F4: lwc1        $f4, 0x50($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X50);
    // 0x801E05F8: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
    // 0x801E05FC: swc1        $f6, 0x10($t1)
    MEM_W(0X10, ctx->r9) = ctx->f6.u32l;
    // 0x801E0600: add.s       $f12, $f4, $f0
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f12.fl = ctx->f4.fl + ctx->f0.fl;
    // 0x801E0604: lwc1        $f14, 0x54($sp)
    ctx->f14.u32l = MEM_W(ctx->r29, 0X54);
    // 0x801E0608: lui         $at, 0x43B4
    ctx->r1 = S32(0X43B4 << 16);
    // 0x801E060C: mtc1        $at, $f18
    ctx->f18.u32l = ctx->r1;
    // 0x801E0610: mul.s       $f8, $f12, $f16
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f8.fl = MUL_S(ctx->f12.fl, ctx->f16.fl);
    // 0x801E0614: lui         $t0, 0x8015
    ctx->r8 = S32(0X8015 << 16);
    // 0x801E0618: addiu       $t0, $t0, 0x4350
    ctx->r8 = ADD32(ctx->r8, 0X4350);
    // 0x801E061C: mul.s       $f6, $f14, $f16
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f6.fl = MUL_S(ctx->f14.fl, ctx->f16.fl);
    // 0x801E0620: addiu       $a1, $sp, 0x40
    ctx->r5 = ADD32(ctx->r29, 0X40);
    // 0x801E0624: addiu       $a2, $sp, 0x58
    ctx->r6 = ADD32(ctx->r29, 0X58);
    // 0x801E0628: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    // 0x801E062C: div.s       $f10, $f8, $f18
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f10.fl = DIV_S(ctx->f8.fl, ctx->f18.fl);
    // 0x801E0630: div.s       $f8, $f6, $f18
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f8.fl = DIV_S(ctx->f6.fl, ctx->f18.fl);
    // 0x801E0634: trunc.w.s   $f4, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    ctx->f4.u32l = TRUNC_W_S(ctx->f10.fl);
    // 0x801E0638: mfc1        $v0, $f4
    ctx->r2 = (int32_t)ctx->f4.u32l;
    // 0x801E063C: lwc1        $f4, 0x4C($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X4C);
    // 0x801E0640: addiu       $t6, $v0, 0x400
    ctx->r14 = ADD32(ctx->r2, 0X400);
    // 0x801E0644: andi        $t7, $t6, 0xFFF
    ctx->r15 = ctx->r14 & 0XFFF;
    // 0x801E0648: sll         $t8, $t7, 2
    ctx->r24 = S32(ctx->r15 << 2);
    // 0x801E064C: addu        $t9, $t0, $t8
    ctx->r25 = ADD32(ctx->r8, ctx->r24);
    // 0x801E0650: andi        $t7, $v0, 0xFFF
    ctx->r15 = ctx->r2 & 0XFFF;
    // 0x801E0654: sll         $t8, $t7, 2
    ctx->r24 = S32(ctx->r15 << 2);
    // 0x801E0658: trunc.w.s   $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.u32l = TRUNC_W_S(ctx->f8.fl);
    // 0x801E065C: lwc1        $f8, 0x0($t9)
    ctx->f8.u32l = MEM_W(ctx->r25, 0X0);
    // 0x801E0660: addu        $t9, $t0, $t8
    ctx->r25 = ADD32(ctx->r8, ctx->r24);
    // 0x801E0664: mfc1        $v1, $f10
    ctx->r3 = (int32_t)ctx->f10.u32l;
    // 0x801E0668: nop

    // 0x801E066C: addiu       $t2, $v1, 0x400
    ctx->r10 = ADD32(ctx->r3, 0X400);
    // 0x801E0670: andi        $t3, $t2, 0xFFF
    ctx->r11 = ctx->r10 & 0XFFF;
    // 0x801E0674: sll         $t4, $t3, 2
    ctx->r12 = S32(ctx->r11 << 2);
    // 0x801E0678: addu        $t5, $t0, $t4
    ctx->r13 = ADD32(ctx->r8, ctx->r12);
    // 0x801E067C: lwc1        $f6, 0x0($t5)
    ctx->f6.u32l = MEM_W(ctx->r13, 0X0);
    // 0x801E0680: lw          $t2, 0x10($s0)
    ctx->r10 = MEM_W(ctx->r16, 0X10);
    // 0x801E0684: andi        $t3, $v1, 0xFFF
    ctx->r11 = ctx->r3 & 0XFFF;
    // 0x801E0688: mul.s       $f2, $f4, $f6
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f2.fl = MUL_S(ctx->f4.fl, ctx->f6.fl);
    // 0x801E068C: lwc1        $f6, 0x0($t2)
    ctx->f6.u32l = MEM_W(ctx->r10, 0X0);
    // 0x801E0690: sll         $t4, $t3, 2
    ctx->r12 = S32(ctx->r11 << 2);
    // 0x801E0694: addu        $t5, $t0, $t4
    ctx->r13 = ADD32(ctx->r8, ctx->r12);
    // 0x801E0698: addiu       $t3, $sp, 0x64
    ctx->r11 = ADD32(ctx->r29, 0X64);
    // 0x801E069C: mul.s       $f10, $f8, $f2
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f10.fl = MUL_S(ctx->f8.fl, ctx->f2.fl);
    // 0x801E06A0: add.s       $f8, $f10, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = ctx->f10.fl + ctx->f6.fl;
    // 0x801E06A4: lwc1        $f10, 0x0($t5)
    ctx->f10.u32l = MEM_W(ctx->r13, 0X0);
    // 0x801E06A8: mul.s       $f6, $f10, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = MUL_S(ctx->f10.fl, ctx->f4.fl);
    // 0x801E06AC: swc1        $f8, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->f8.u32l;
    // 0x801E06B0: lw          $t6, 0x14($s0)
    ctx->r14 = MEM_W(ctx->r16, 0X14);
    // 0x801E06B4: lwc1        $f4, 0x0($t9)
    ctx->f4.u32l = MEM_W(ctx->r25, 0X0);
    // 0x801E06B8: lwc1        $f8, 0x0($t6)
    ctx->f8.u32l = MEM_W(ctx->r14, 0X0);
    // 0x801E06BC: add.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = ctx->f6.fl + ctx->f8.fl;
    // 0x801E06C0: mul.s       $f6, $f4, $f2
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f6.fl = MUL_S(ctx->f4.fl, ctx->f2.fl);
    // 0x801E06C4: swc1        $f10, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->f10.u32l;
    // 0x801E06C8: lw          $t2, 0x18($s0)
    ctx->r10 = MEM_W(ctx->r16, 0X18);
    // 0x801E06CC: lwc1        $f8, 0x0($t2)
    ctx->f8.u32l = MEM_W(ctx->r10, 0X0);
    // 0x801E06D0: add.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = ctx->f6.fl + ctx->f8.fl;
    // 0x801E06D4: swc1        $f10, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->f10.u32l;
    // 0x801E06D8: lw          $a0, 0x0($s0)
    ctx->r4 = MEM_W(ctx->r16, 0X0);
    // 0x801E06DC: jal         0x801DF2F8
    // 0x801E06E0: sw          $t3, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r11;
    func_801DF2F8(rdram, ctx);
        goto after_2;
    // 0x801E06E0: sw          $t3, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r11;
    after_2:
    // 0x801E06E4: lw          $ra, 0x24($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X24);
    // 0x801E06E8: lw          $s0, 0x20($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X20);
    // 0x801E06EC: addiu       $sp, $sp, 0x68
    ctx->r29 = ADD32(ctx->r29, 0X68);
    // 0x801E06F0: jr          $ra
    // 0x801E06F4: nop

    return;
    // 0x801E06F4: nop

;}
RECOMP_FUNC void func_801E06F8(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801E06F8: addiu       $sp, $sp, -0x78
    ctx->r29 = ADD32(ctx->r29, -0X78);
    // 0x801E06FC: sw          $s0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r16;
    // 0x801E0700: or          $s0, $a0, $zero
    ctx->r16 = ctx->r4 | 0;
    // 0x801E0704: sw          $ra, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r31;
    // 0x801E0708: or          $a2, $a1, $zero
    ctx->r6 = ctx->r5 | 0;
    // 0x801E070C: lw          $a1, 0xC($s0)
    ctx->r5 = MEM_W(ctx->r16, 0XC);
    // 0x801E0710: jal         0x801DEE48
    // 0x801E0714: addiu       $a0, $sp, 0x50
    ctx->r4 = ADD32(ctx->r29, 0X50);
    func_801DEE48(rdram, ctx);
        goto after_0;
    // 0x801E0714: addiu       $a0, $sp, 0x50
    ctx->r4 = ADD32(ctx->r29, 0X50);
    after_0:
    // 0x801E0718: lw          $t1, 0x0($s0)
    ctx->r9 = MEM_W(ctx->r16, 0X0);
    // 0x801E071C: lw          $t6, 0x24($s0)
    ctx->r14 = MEM_W(ctx->r16, 0X24);
    // 0x801E0720: lw          $t7, 0x1C($s0)
    ctx->r15 = MEM_W(ctx->r16, 0X1C);
    // 0x801E0724: addiu       $t1, $t1, 0x5C
    ctx->r9 = ADD32(ctx->r9, 0X5C);
    // 0x801E0728: lwc1        $f12, 0x0($t6)
    ctx->f12.u32l = MEM_W(ctx->r14, 0X0);
    // 0x801E072C: lwc1        $f14, 0x0($t7)
    ctx->f14.u32l = MEM_W(ctx->r15, 0X0);
    // 0x801E0730: jal         0x801ED154
    // 0x801E0734: sw          $t1, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r9;
    func_801ED154(rdram, ctx);
        goto after_1;
    // 0x801E0734: sw          $t1, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r9;
    after_1:
    // 0x801E0738: lw          $t1, 0x38($sp)
    ctx->r9 = MEM_W(ctx->r29, 0X38);
    // 0x801E073C: mtc1        $zero, $f6
    ctx->f6.u32l = 0;
    // 0x801E0740: lui         $at, 0x4580
    ctx->r1 = S32(0X4580 << 16);
    // 0x801E0744: swc1        $f0, 0xC($t1)
    MEM_W(0XC, ctx->r9) = ctx->f0.u32l;
    // 0x801E0748: lwc1        $f4, 0x54($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X54);
    // 0x801E074C: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
    // 0x801E0750: swc1        $f6, 0x10($t1)
    MEM_W(0X10, ctx->r9) = ctx->f6.u32l;
    // 0x801E0754: add.s       $f12, $f4, $f0
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f12.fl = ctx->f4.fl + ctx->f0.fl;
    // 0x801E0758: lwc1        $f14, 0x58($sp)
    ctx->f14.u32l = MEM_W(ctx->r29, 0X58);
    // 0x801E075C: lui         $at, 0x43B4
    ctx->r1 = S32(0X43B4 << 16);
    // 0x801E0760: mtc1        $at, $f18
    ctx->f18.u32l = ctx->r1;
    // 0x801E0764: mul.s       $f8, $f12, $f16
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f8.fl = MUL_S(ctx->f12.fl, ctx->f16.fl);
    // 0x801E0768: lui         $t0, 0x8015
    ctx->r8 = S32(0X8015 << 16);
    // 0x801E076C: addiu       $t0, $t0, 0x4350
    ctx->r8 = ADD32(ctx->r8, 0X4350);
    // 0x801E0770: mul.s       $f6, $f14, $f16
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f6.fl = MUL_S(ctx->f14.fl, ctx->f16.fl);
    // 0x801E0774: addiu       $a1, $sp, 0x44
    ctx->r5 = ADD32(ctx->r29, 0X44);
    // 0x801E0778: addiu       $a2, $sp, 0x5C
    ctx->r6 = ADD32(ctx->r29, 0X5C);
    // 0x801E077C: addiu       $a3, $sp, 0x68
    ctx->r7 = ADD32(ctx->r29, 0X68);
    // 0x801E0780: div.s       $f10, $f8, $f18
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f10.fl = DIV_S(ctx->f8.fl, ctx->f18.fl);
    // 0x801E0784: div.s       $f8, $f6, $f18
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f8.fl = DIV_S(ctx->f6.fl, ctx->f18.fl);
    // 0x801E0788: trunc.w.s   $f4, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    ctx->f4.u32l = TRUNC_W_S(ctx->f10.fl);
    // 0x801E078C: mfc1        $v0, $f4
    ctx->r2 = (int32_t)ctx->f4.u32l;
    // 0x801E0790: lwc1        $f4, 0x50($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X50);
    // 0x801E0794: addiu       $t6, $v0, 0x400
    ctx->r14 = ADD32(ctx->r2, 0X400);
    // 0x801E0798: andi        $t7, $t6, 0xFFF
    ctx->r15 = ctx->r14 & 0XFFF;
    // 0x801E079C: sll         $t8, $t7, 2
    ctx->r24 = S32(ctx->r15 << 2);
    // 0x801E07A0: addu        $t9, $t0, $t8
    ctx->r25 = ADD32(ctx->r8, ctx->r24);
    // 0x801E07A4: andi        $t7, $v0, 0xFFF
    ctx->r15 = ctx->r2 & 0XFFF;
    // 0x801E07A8: sll         $t8, $t7, 2
    ctx->r24 = S32(ctx->r15 << 2);
    // 0x801E07AC: trunc.w.s   $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.u32l = TRUNC_W_S(ctx->f8.fl);
    // 0x801E07B0: lwc1        $f8, 0x0($t9)
    ctx->f8.u32l = MEM_W(ctx->r25, 0X0);
    // 0x801E07B4: addu        $t9, $t0, $t8
    ctx->r25 = ADD32(ctx->r8, ctx->r24);
    // 0x801E07B8: mfc1        $v1, $f10
    ctx->r3 = (int32_t)ctx->f10.u32l;
    // 0x801E07BC: nop

    // 0x801E07C0: addiu       $t2, $v1, 0x400
    ctx->r10 = ADD32(ctx->r3, 0X400);
    // 0x801E07C4: andi        $t3, $t2, 0xFFF
    ctx->r11 = ctx->r10 & 0XFFF;
    // 0x801E07C8: sll         $t4, $t3, 2
    ctx->r12 = S32(ctx->r11 << 2);
    // 0x801E07CC: addu        $t5, $t0, $t4
    ctx->r13 = ADD32(ctx->r8, ctx->r12);
    // 0x801E07D0: lwc1        $f6, 0x0($t5)
    ctx->f6.u32l = MEM_W(ctx->r13, 0X0);
    // 0x801E07D4: lw          $t2, 0x10($s0)
    ctx->r10 = MEM_W(ctx->r16, 0X10);
    // 0x801E07D8: andi        $t3, $v1, 0xFFF
    ctx->r11 = ctx->r3 & 0XFFF;
    // 0x801E07DC: mul.s       $f2, $f4, $f6
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f2.fl = MUL_S(ctx->f4.fl, ctx->f6.fl);
    // 0x801E07E0: lwc1        $f6, 0x0($t2)
    ctx->f6.u32l = MEM_W(ctx->r10, 0X0);
    // 0x801E07E4: sll         $t4, $t3, 2
    ctx->r12 = S32(ctx->r11 << 2);
    // 0x801E07E8: addu        $t5, $t0, $t4
    ctx->r13 = ADD32(ctx->r8, ctx->r12);
    // 0x801E07EC: addiu       $t3, $sp, 0x74
    ctx->r11 = ADD32(ctx->r29, 0X74);
    // 0x801E07F0: mul.s       $f10, $f8, $f2
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f10.fl = MUL_S(ctx->f8.fl, ctx->f2.fl);
    // 0x801E07F4: add.s       $f8, $f10, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = ctx->f10.fl + ctx->f6.fl;
    // 0x801E07F8: lwc1        $f10, 0x0($t5)
    ctx->f10.u32l = MEM_W(ctx->r13, 0X0);
    // 0x801E07FC: mul.s       $f6, $f10, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = MUL_S(ctx->f10.fl, ctx->f4.fl);
    // 0x801E0800: swc1        $f8, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->f8.u32l;
    // 0x801E0804: lw          $t6, 0x14($s0)
    ctx->r14 = MEM_W(ctx->r16, 0X14);
    // 0x801E0808: lwc1        $f4, 0x0($t9)
    ctx->f4.u32l = MEM_W(ctx->r25, 0X0);
    // 0x801E080C: lwc1        $f8, 0x0($t6)
    ctx->f8.u32l = MEM_W(ctx->r14, 0X0);
    // 0x801E0810: add.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = ctx->f6.fl + ctx->f8.fl;
    // 0x801E0814: mul.s       $f6, $f4, $f2
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f6.fl = MUL_S(ctx->f4.fl, ctx->f2.fl);
    // 0x801E0818: swc1        $f10, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->f10.u32l;
    // 0x801E081C: lw          $t2, 0x18($s0)
    ctx->r10 = MEM_W(ctx->r16, 0X18);
    // 0x801E0820: lwc1        $f8, 0x0($t2)
    ctx->f8.u32l = MEM_W(ctx->r10, 0X0);
    // 0x801E0824: add.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = ctx->f6.fl + ctx->f8.fl;
    // 0x801E0828: swc1        $f10, 0x4C($sp)
    MEM_W(0X4C, ctx->r29) = ctx->f10.u32l;
    // 0x801E082C: lw          $a0, 0x0($s0)
    ctx->r4 = MEM_W(ctx->r16, 0X0);
    // 0x801E0830: jal         0x801DF2F8
    // 0x801E0834: sw          $t3, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r11;
    func_801DF2F8(rdram, ctx);
        goto after_2;
    // 0x801E0834: sw          $t3, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r11;
    after_2:
    // 0x801E0838: lw          $ra, 0x24($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X24);
    // 0x801E083C: lw          $s0, 0x20($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X20);
    // 0x801E0840: addiu       $sp, $sp, 0x78
    ctx->r29 = ADD32(ctx->r29, 0X78);
    // 0x801E0844: jr          $ra
    // 0x801E0848: nop

    return;
    // 0x801E0848: nop

;}
RECOMP_FUNC void func_801E084C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801E084C: addiu       $sp, $sp, -0x70
    ctx->r29 = ADD32(ctx->r29, -0X70);
    // 0x801E0850: sw          $s0, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r16;
    // 0x801E0854: or          $s0, $a0, $zero
    ctx->r16 = ctx->r4 | 0;
    // 0x801E0858: sw          $ra, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r31;
    // 0x801E085C: or          $a2, $a1, $zero
    ctx->r6 = ctx->r5 | 0;
    // 0x801E0860: lw          $a1, 0xC($s0)
    ctx->r5 = MEM_W(ctx->r16, 0XC);
    // 0x801E0864: jal         0x801DED44
    // 0x801E0868: addiu       $a0, $sp, 0x58
    ctx->r4 = ADD32(ctx->r29, 0X58);
    func_801DED44(rdram, ctx);
        goto after_0;
    // 0x801E0868: addiu       $a0, $sp, 0x58
    ctx->r4 = ADD32(ctx->r29, 0X58);
    after_0:
    // 0x801E086C: lw          $v0, 0x0($s0)
    ctx->r2 = MEM_W(ctx->r16, 0X0);
    // 0x801E0870: lw          $t6, 0x24($s0)
    ctx->r14 = MEM_W(ctx->r16, 0X24);
    // 0x801E0874: lw          $t7, 0x1C($s0)
    ctx->r15 = MEM_W(ctx->r16, 0X1C);
    // 0x801E0878: addiu       $v0, $v0, 0x5C
    ctx->r2 = ADD32(ctx->r2, 0X5C);
    // 0x801E087C: lwc1        $f12, 0x0($t6)
    ctx->f12.u32l = MEM_W(ctx->r14, 0X0);
    // 0x801E0880: lwc1        $f14, 0x0($t7)
    ctx->f14.u32l = MEM_W(ctx->r15, 0X0);
    // 0x801E0884: jal         0x801ED154
    // 0x801E0888: sw          $v0, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r2;
    func_801ED154(rdram, ctx);
        goto after_1;
    // 0x801E0888: sw          $v0, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r2;
    after_1:
    // 0x801E088C: lwc1        $f4, 0x5C($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X5C);
    // 0x801E0890: lui         $at, 0x4580
    ctx->r1 = S32(0X4580 << 16);
    // 0x801E0894: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x801E0898: add.s       $f18, $f4, $f0
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f18.fl = ctx->f4.fl + ctx->f0.fl;
    // 0x801E089C: lui         $at, 0x43B4
    ctx->r1 = S32(0X43B4 << 16);
    // 0x801E08A0: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x801E08A4: lui         $at, 0x4580
    ctx->r1 = S32(0X4580 << 16);
    // 0x801E08A8: mul.s       $f10, $f18, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = MUL_S(ctx->f18.fl, ctx->f8.fl);
    // 0x801E08AC: lwc1        $f6, 0x60($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X60);
    // 0x801E08B0: lui         $a3, 0x8015
    ctx->r7 = S32(0X8015 << 16);
    // 0x801E08B4: addiu       $a3, $a3, 0x4350
    ctx->r7 = ADD32(ctx->r7, 0X4350);
    // 0x801E08B8: swc1        $f6, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->f6.u32l;
    // 0x801E08BC: lw          $t8, 0x10($s0)
    ctx->r24 = MEM_W(ctx->r16, 0X10);
    // 0x801E08C0: lw          $v0, 0x40($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X40);
    // 0x801E08C4: div.s       $f8, $f10, $f4
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f8.fl = DIV_S(ctx->f10.fl, ctx->f4.fl);
    // 0x801E08C8: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x801E08CC: lui         $at, 0x43B4
    ctx->r1 = S32(0X43B4 << 16);
    // 0x801E08D0: trunc.w.s   $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.u32l = TRUNC_W_S(ctx->f8.fl);
    // 0x801E08D4: mul.s       $f8, $f6, $f4
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f8.fl = MUL_S(ctx->f6.fl, ctx->f4.fl);
    // 0x801E08D8: mfc1        $v1, $f10
    ctx->r3 = (int32_t)ctx->f10.u32l;
    // 0x801E08DC: mtc1        $at, $f10
    ctx->f10.u32l = ctx->r1;
    // 0x801E08E0: addiu       $t4, $v1, 0x400
    ctx->r12 = ADD32(ctx->r3, 0X400);
    // 0x801E08E4: div.s       $f6, $f8, $f10
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f6.fl = DIV_S(ctx->f8.fl, ctx->f10.fl);
    // 0x801E08E8: lwc1        $f8, 0x58($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X58);
    // 0x801E08EC: andi        $t5, $t4, 0xFFF
    ctx->r13 = ctx->r12 & 0XFFF;
    // 0x801E08F0: sll         $t6, $t5, 2
    ctx->r14 = S32(ctx->r13 << 2);
    // 0x801E08F4: addu        $t7, $a3, $t6
    ctx->r15 = ADD32(ctx->r7, ctx->r14);
    // 0x801E08F8: trunc.w.s   $f4, $f6
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    ctx->f4.u32l = TRUNC_W_S(ctx->f6.fl);
    // 0x801E08FC: lwc1        $f6, 0x0($t7)
    ctx->f6.u32l = MEM_W(ctx->r15, 0X0);
    // 0x801E0900: mfc1        $a0, $f4
    ctx->r4 = (int32_t)ctx->f4.u32l;
    // 0x801E0904: nop

    // 0x801E0908: addiu       $t0, $a0, 0x400
    ctx->r8 = ADD32(ctx->r4, 0X400);
    // 0x801E090C: andi        $t1, $t0, 0xFFF
    ctx->r9 = ctx->r8 & 0XFFF;
    // 0x801E0910: sll         $t2, $t1, 2
    ctx->r10 = S32(ctx->r9 << 2);
    // 0x801E0914: addu        $t3, $a3, $t2
    ctx->r11 = ADD32(ctx->r7, ctx->r10);
    // 0x801E0918: lwc1        $f10, 0x0($t3)
    ctx->f10.u32l = MEM_W(ctx->r11, 0X0);
    // 0x801E091C: andi        $t9, $a0, 0xFFF
    ctx->r25 = ctx->r4 & 0XFFF;
    // 0x801E0920: sll         $t0, $t9, 2
    ctx->r8 = S32(ctx->r25 << 2);
    // 0x801E0924: mul.s       $f2, $f8, $f10
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f2.fl = MUL_S(ctx->f8.fl, ctx->f10.fl);
    // 0x801E0928: lwc1        $f10, 0x0($t8)
    ctx->f10.u32l = MEM_W(ctx->r24, 0X0);
    // 0x801E092C: addu        $t1, $a3, $t0
    ctx->r9 = ADD32(ctx->r7, ctx->r8);
    // 0x801E0930: andi        $t3, $v1, 0xFFF
    ctx->r11 = ctx->r3 & 0XFFF;
    // 0x801E0934: sll         $t4, $t3, 2
    ctx->r12 = S32(ctx->r11 << 2);
    // 0x801E0938: addu        $t5, $a3, $t4
    ctx->r13 = ADD32(ctx->r7, ctx->r12);
    // 0x801E093C: mul.s       $f4, $f6, $f2
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f4.fl = MUL_S(ctx->f6.fl, ctx->f2.fl);
    // 0x801E0940: add.s       $f6, $f4, $f10
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f6.fl = ctx->f4.fl + ctx->f10.fl;
    // 0x801E0944: lwc1        $f4, 0x0($t1)
    ctx->f4.u32l = MEM_W(ctx->r9, 0X0);
    // 0x801E0948: mul.s       $f10, $f4, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = MUL_S(ctx->f4.fl, ctx->f8.fl);
    // 0x801E094C: swc1        $f6, 0x4C($sp)
    MEM_W(0X4C, ctx->r29) = ctx->f6.u32l;
    // 0x801E0950: lw          $t2, 0x14($s0)
    ctx->r10 = MEM_W(ctx->r16, 0X14);
    // 0x801E0954: lwc1        $f8, 0x0($t5)
    ctx->f8.u32l = MEM_W(ctx->r13, 0X0);
    // 0x801E0958: lwc1        $f6, 0x0($t2)
    ctx->f6.u32l = MEM_W(ctx->r10, 0X0);
    // 0x801E095C: add.s       $f4, $f10, $f6
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f4.fl = ctx->f10.fl + ctx->f6.fl;
    // 0x801E0960: mul.s       $f10, $f8, $f2
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f10.fl = MUL_S(ctx->f8.fl, ctx->f2.fl);
    // 0x801E0964: swc1        $f4, 0x50($sp)
    MEM_W(0X50, ctx->r29) = ctx->f4.u32l;
    // 0x801E0968: lw          $t6, 0x18($s0)
    ctx->r14 = MEM_W(ctx->r16, 0X18);
    // 0x801E096C: lwc1        $f6, 0x0($t6)
    ctx->f6.u32l = MEM_W(ctx->r14, 0X0);
    // 0x801E0970: add.s       $f4, $f10, $f6
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f4.fl = ctx->f10.fl + ctx->f6.fl;
    // 0x801E0974: swc1        $f4, 0x54($sp)
    MEM_W(0X54, ctx->r29) = ctx->f4.u32l;
    // 0x801E0978: lw          $t7, 0x34($s0)
    ctx->r15 = MEM_W(ctx->r16, 0X34);
    // 0x801E097C: lw          $t8, 0x74($v0)
    ctx->r24 = MEM_W(ctx->r2, 0X74);
    // 0x801E0980: lw          $t1, 0x78($v0)
    ctx->r9 = MEM_W(ctx->r2, 0X78);
    // 0x801E0984: lwc1        $f8, 0x0($t7)
    ctx->f8.u32l = MEM_W(ctx->r15, 0X0);
    // 0x801E0988: sll         $t9, $t8, 2
    ctx->r25 = S32(ctx->r24 << 2);
    // 0x801E098C: addu        $a1, $s0, $t9
    ctx->r5 = ADD32(ctx->r16, ctx->r25);
    // 0x801E0990: swc1        $f8, 0xC($v0)
    MEM_W(0XC, ctx->r2) = ctx->f8.u32l;
    // 0x801E0994: lw          $t0, 0x1C($a1)
    ctx->r8 = MEM_W(ctx->r5, 0X1C);
    // 0x801E0998: sll         $t2, $t1, 2
    ctx->r10 = S32(ctx->r9 << 2);
    // 0x801E099C: addu        $a2, $s0, $t2
    ctx->r6 = ADD32(ctx->r16, ctx->r10);
    // 0x801E09A0: lwc1        $f10, 0x0($t0)
    ctx->f10.u32l = MEM_W(ctx->r8, 0X0);
    // 0x801E09A4: swc1        $f10, 0x24($v0)
    MEM_W(0X24, ctx->r2) = ctx->f10.u32l;
    // 0x801E09A8: lw          $t3, 0x1C($a2)
    ctx->r11 = MEM_W(ctx->r6, 0X1C);
    // 0x801E09AC: lwc1        $f6, 0x0($t3)
    ctx->f6.u32l = MEM_W(ctx->r11, 0X0);
    // 0x801E09B0: swc1        $f6, 0x28($v0)
    MEM_W(0X28, ctx->r2) = ctx->f6.u32l;
    // 0x801E09B4: lw          $t4, 0x28($a2)
    ctx->r12 = MEM_W(ctx->r6, 0X28);
    // 0x801E09B8: lw          $t5, 0x28($a1)
    ctx->r13 = MEM_W(ctx->r5, 0X28);
    // 0x801E09BC: lwc1        $f14, 0x0($t4)
    ctx->f14.u32l = MEM_W(ctx->r12, 0X0);
    // 0x801E09C0: lwc1        $f16, 0x0($t5)
    ctx->f16.u32l = MEM_W(ctx->r13, 0X0);
    // 0x801E09C4: mul.s       $f4, $f14, $f14
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f4.fl = MUL_S(ctx->f14.fl, ctx->f14.fl);
    // 0x801E09C8: nop

    // 0x801E09CC: mul.s       $f8, $f16, $f16
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f8.fl = MUL_S(ctx->f16.fl, ctx->f16.fl);
    // 0x801E09D0: jal         0x800C7010
    // 0x801E09D4: add.s       $f12, $f4, $f8
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f12.fl = ctx->f4.fl + ctx->f8.fl;
    _nsqrtf(rdram, ctx);
        goto after_2;
    // 0x801E09D4: add.s       $f12, $f4, $f8
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f12.fl = ctx->f4.fl + ctx->f8.fl;
    after_2:
    // 0x801E09D8: lw          $v0, 0x40($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X40);
    // 0x801E09DC: addiu       $t6, $sp, 0x64
    ctx->r14 = ADD32(ctx->r29, 0X64);
    // 0x801E09E0: addiu       $a1, $sp, 0x4C
    ctx->r5 = ADD32(ctx->r29, 0X4C);
    // 0x801E09E4: swc1        $f0, 0x34($v0)
    MEM_W(0X34, ctx->r2) = ctx->f0.u32l;
    // 0x801E09E8: lw          $a0, 0x0($s0)
    ctx->r4 = MEM_W(ctx->r16, 0X0);
    // 0x801E09EC: sw          $zero, 0x18($sp)
    MEM_W(0X18, ctx->r29) = 0;
    // 0x801E09F0: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    // 0x801E09F4: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x801E09F8: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x801E09FC: jal         0x801DF668
    // 0x801E0A00: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_801DF668(rdram, ctx);
        goto after_3;
    // 0x801E0A00: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_3:
    // 0x801E0A04: lw          $ra, 0x2C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X2C);
    // 0x801E0A08: lw          $s0, 0x28($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X28);
    // 0x801E0A0C: addiu       $sp, $sp, 0x70
    ctx->r29 = ADD32(ctx->r29, 0X70);
    // 0x801E0A10: jr          $ra
    // 0x801E0A14: nop

    return;
    // 0x801E0A14: nop

;}
RECOMP_FUNC void func_801E0A18(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801E0A18: addiu       $sp, $sp, -0x80
    ctx->r29 = ADD32(ctx->r29, -0X80);
    // 0x801E0A1C: sw          $s0, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r16;
    // 0x801E0A20: or          $s0, $a0, $zero
    ctx->r16 = ctx->r4 | 0;
    // 0x801E0A24: sw          $ra, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r31;
    // 0x801E0A28: or          $a2, $a1, $zero
    ctx->r6 = ctx->r5 | 0;
    // 0x801E0A2C: lw          $a1, 0xC($s0)
    ctx->r5 = MEM_W(ctx->r16, 0XC);
    // 0x801E0A30: jal         0x801DED88
    // 0x801E0A34: addiu       $a0, $sp, 0x5C
    ctx->r4 = ADD32(ctx->r29, 0X5C);
    func_801DED88(rdram, ctx);
        goto after_0;
    // 0x801E0A34: addiu       $a0, $sp, 0x5C
    ctx->r4 = ADD32(ctx->r29, 0X5C);
    after_0:
    // 0x801E0A38: lw          $v0, 0x0($s0)
    ctx->r2 = MEM_W(ctx->r16, 0X0);
    // 0x801E0A3C: lw          $t6, 0x24($s0)
    ctx->r14 = MEM_W(ctx->r16, 0X24);
    // 0x801E0A40: lw          $t7, 0x1C($s0)
    ctx->r15 = MEM_W(ctx->r16, 0X1C);
    // 0x801E0A44: addiu       $v0, $v0, 0x5C
    ctx->r2 = ADD32(ctx->r2, 0X5C);
    // 0x801E0A48: lwc1        $f12, 0x0($t6)
    ctx->f12.u32l = MEM_W(ctx->r14, 0X0);
    // 0x801E0A4C: lwc1        $f14, 0x0($t7)
    ctx->f14.u32l = MEM_W(ctx->r15, 0X0);
    // 0x801E0A50: jal         0x801ED154
    // 0x801E0A54: sw          $v0, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r2;
    func_801ED154(rdram, ctx);
        goto after_1;
    // 0x801E0A54: sw          $v0, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r2;
    after_1:
    // 0x801E0A58: lwc1        $f4, 0x60($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X60);
    // 0x801E0A5C: lui         $at, 0x4580
    ctx->r1 = S32(0X4580 << 16);
    // 0x801E0A60: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x801E0A64: add.s       $f18, $f4, $f0
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f18.fl = ctx->f4.fl + ctx->f0.fl;
    // 0x801E0A68: lui         $at, 0x43B4
    ctx->r1 = S32(0X43B4 << 16);
    // 0x801E0A6C: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x801E0A70: lui         $at, 0x4580
    ctx->r1 = S32(0X4580 << 16);
    // 0x801E0A74: mul.s       $f10, $f18, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = MUL_S(ctx->f18.fl, ctx->f8.fl);
    // 0x801E0A78: lwc1        $f6, 0x64($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X64);
    // 0x801E0A7C: lui         $a3, 0x8015
    ctx->r7 = S32(0X8015 << 16);
    // 0x801E0A80: addiu       $a3, $a3, 0x4350
    ctx->r7 = ADD32(ctx->r7, 0X4350);
    // 0x801E0A84: swc1        $f6, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->f6.u32l;
    // 0x801E0A88: lw          $t8, 0x10($s0)
    ctx->r24 = MEM_W(ctx->r16, 0X10);
    // 0x801E0A8C: lw          $v0, 0x44($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X44);
    // 0x801E0A90: div.s       $f8, $f10, $f4
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f8.fl = DIV_S(ctx->f10.fl, ctx->f4.fl);
    // 0x801E0A94: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x801E0A98: lui         $at, 0x43B4
    ctx->r1 = S32(0X43B4 << 16);
    // 0x801E0A9C: trunc.w.s   $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.u32l = TRUNC_W_S(ctx->f8.fl);
    // 0x801E0AA0: mul.s       $f8, $f6, $f4
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f8.fl = MUL_S(ctx->f6.fl, ctx->f4.fl);
    // 0x801E0AA4: mfc1        $v1, $f10
    ctx->r3 = (int32_t)ctx->f10.u32l;
    // 0x801E0AA8: mtc1        $at, $f10
    ctx->f10.u32l = ctx->r1;
    // 0x801E0AAC: addiu       $t4, $v1, 0x400
    ctx->r12 = ADD32(ctx->r3, 0X400);
    // 0x801E0AB0: div.s       $f6, $f8, $f10
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f6.fl = DIV_S(ctx->f8.fl, ctx->f10.fl);
    // 0x801E0AB4: lwc1        $f8, 0x5C($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X5C);
    // 0x801E0AB8: andi        $t5, $t4, 0xFFF
    ctx->r13 = ctx->r12 & 0XFFF;
    // 0x801E0ABC: sll         $t6, $t5, 2
    ctx->r14 = S32(ctx->r13 << 2);
    // 0x801E0AC0: addu        $t7, $a3, $t6
    ctx->r15 = ADD32(ctx->r7, ctx->r14);
    // 0x801E0AC4: trunc.w.s   $f4, $f6
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    ctx->f4.u32l = TRUNC_W_S(ctx->f6.fl);
    // 0x801E0AC8: lwc1        $f6, 0x0($t7)
    ctx->f6.u32l = MEM_W(ctx->r15, 0X0);
    // 0x801E0ACC: mfc1        $a0, $f4
    ctx->r4 = (int32_t)ctx->f4.u32l;
    // 0x801E0AD0: nop

    // 0x801E0AD4: addiu       $t0, $a0, 0x400
    ctx->r8 = ADD32(ctx->r4, 0X400);
    // 0x801E0AD8: andi        $t1, $t0, 0xFFF
    ctx->r9 = ctx->r8 & 0XFFF;
    // 0x801E0ADC: sll         $t2, $t1, 2
    ctx->r10 = S32(ctx->r9 << 2);
    // 0x801E0AE0: addu        $t3, $a3, $t2
    ctx->r11 = ADD32(ctx->r7, ctx->r10);
    // 0x801E0AE4: lwc1        $f10, 0x0($t3)
    ctx->f10.u32l = MEM_W(ctx->r11, 0X0);
    // 0x801E0AE8: andi        $t9, $a0, 0xFFF
    ctx->r25 = ctx->r4 & 0XFFF;
    // 0x801E0AEC: sll         $t0, $t9, 2
    ctx->r8 = S32(ctx->r25 << 2);
    // 0x801E0AF0: mul.s       $f2, $f8, $f10
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f2.fl = MUL_S(ctx->f8.fl, ctx->f10.fl);
    // 0x801E0AF4: lwc1        $f10, 0x0($t8)
    ctx->f10.u32l = MEM_W(ctx->r24, 0X0);
    // 0x801E0AF8: addu        $t1, $a3, $t0
    ctx->r9 = ADD32(ctx->r7, ctx->r8);
    // 0x801E0AFC: andi        $t3, $v1, 0xFFF
    ctx->r11 = ctx->r3 & 0XFFF;
    // 0x801E0B00: sll         $t4, $t3, 2
    ctx->r12 = S32(ctx->r11 << 2);
    // 0x801E0B04: addu        $t5, $a3, $t4
    ctx->r13 = ADD32(ctx->r7, ctx->r12);
    // 0x801E0B08: mul.s       $f4, $f6, $f2
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f4.fl = MUL_S(ctx->f6.fl, ctx->f2.fl);
    // 0x801E0B0C: add.s       $f6, $f4, $f10
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f6.fl = ctx->f4.fl + ctx->f10.fl;
    // 0x801E0B10: lwc1        $f4, 0x0($t1)
    ctx->f4.u32l = MEM_W(ctx->r9, 0X0);
    // 0x801E0B14: mul.s       $f10, $f4, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = MUL_S(ctx->f4.fl, ctx->f8.fl);
    // 0x801E0B18: swc1        $f6, 0x50($sp)
    MEM_W(0X50, ctx->r29) = ctx->f6.u32l;
    // 0x801E0B1C: lw          $t2, 0x14($s0)
    ctx->r10 = MEM_W(ctx->r16, 0X14);
    // 0x801E0B20: lwc1        $f8, 0x0($t5)
    ctx->f8.u32l = MEM_W(ctx->r13, 0X0);
    // 0x801E0B24: lwc1        $f6, 0x0($t2)
    ctx->f6.u32l = MEM_W(ctx->r10, 0X0);
    // 0x801E0B28: add.s       $f4, $f10, $f6
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f4.fl = ctx->f10.fl + ctx->f6.fl;
    // 0x801E0B2C: mul.s       $f10, $f8, $f2
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f10.fl = MUL_S(ctx->f8.fl, ctx->f2.fl);
    // 0x801E0B30: swc1        $f4, 0x54($sp)
    MEM_W(0X54, ctx->r29) = ctx->f4.u32l;
    // 0x801E0B34: lw          $t6, 0x18($s0)
    ctx->r14 = MEM_W(ctx->r16, 0X18);
    // 0x801E0B38: lwc1        $f6, 0x0($t6)
    ctx->f6.u32l = MEM_W(ctx->r14, 0X0);
    // 0x801E0B3C: add.s       $f4, $f10, $f6
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f4.fl = ctx->f10.fl + ctx->f6.fl;
    // 0x801E0B40: swc1        $f4, 0x58($sp)
    MEM_W(0X58, ctx->r29) = ctx->f4.u32l;
    // 0x801E0B44: lw          $t7, 0x34($s0)
    ctx->r15 = MEM_W(ctx->r16, 0X34);
    // 0x801E0B48: lw          $t8, 0x74($v0)
    ctx->r24 = MEM_W(ctx->r2, 0X74);
    // 0x801E0B4C: lw          $t1, 0x78($v0)
    ctx->r9 = MEM_W(ctx->r2, 0X78);
    // 0x801E0B50: lwc1        $f8, 0x0($t7)
    ctx->f8.u32l = MEM_W(ctx->r15, 0X0);
    // 0x801E0B54: sll         $t9, $t8, 2
    ctx->r25 = S32(ctx->r24 << 2);
    // 0x801E0B58: addu        $a1, $s0, $t9
    ctx->r5 = ADD32(ctx->r16, ctx->r25);
    // 0x801E0B5C: swc1        $f8, 0xC($v0)
    MEM_W(0XC, ctx->r2) = ctx->f8.u32l;
    // 0x801E0B60: lw          $t0, 0x1C($a1)
    ctx->r8 = MEM_W(ctx->r5, 0X1C);
    // 0x801E0B64: sll         $t2, $t1, 2
    ctx->r10 = S32(ctx->r9 << 2);
    // 0x801E0B68: addu        $a2, $s0, $t2
    ctx->r6 = ADD32(ctx->r16, ctx->r10);
    // 0x801E0B6C: lwc1        $f10, 0x0($t0)
    ctx->f10.u32l = MEM_W(ctx->r8, 0X0);
    // 0x801E0B70: swc1        $f10, 0x24($v0)
    MEM_W(0X24, ctx->r2) = ctx->f10.u32l;
    // 0x801E0B74: lw          $t3, 0x1C($a2)
    ctx->r11 = MEM_W(ctx->r6, 0X1C);
    // 0x801E0B78: lwc1        $f6, 0x0($t3)
    ctx->f6.u32l = MEM_W(ctx->r11, 0X0);
    // 0x801E0B7C: swc1        $f6, 0x28($v0)
    MEM_W(0X28, ctx->r2) = ctx->f6.u32l;
    // 0x801E0B80: lw          $t4, 0x28($a2)
    ctx->r12 = MEM_W(ctx->r6, 0X28);
    // 0x801E0B84: lw          $t5, 0x28($a1)
    ctx->r13 = MEM_W(ctx->r5, 0X28);
    // 0x801E0B88: lwc1        $f14, 0x0($t4)
    ctx->f14.u32l = MEM_W(ctx->r12, 0X0);
    // 0x801E0B8C: lwc1        $f16, 0x0($t5)
    ctx->f16.u32l = MEM_W(ctx->r13, 0X0);
    // 0x801E0B90: mul.s       $f4, $f14, $f14
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f4.fl = MUL_S(ctx->f14.fl, ctx->f14.fl);
    // 0x801E0B94: nop

    // 0x801E0B98: mul.s       $f8, $f16, $f16
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f8.fl = MUL_S(ctx->f16.fl, ctx->f16.fl);
    // 0x801E0B9C: jal         0x800C7010
    // 0x801E0BA0: add.s       $f12, $f4, $f8
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f12.fl = ctx->f4.fl + ctx->f8.fl;
    _nsqrtf(rdram, ctx);
        goto after_2;
    // 0x801E0BA0: add.s       $f12, $f4, $f8
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f12.fl = ctx->f4.fl + ctx->f8.fl;
    after_2:
    // 0x801E0BA4: lw          $v0, 0x44($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X44);
    // 0x801E0BA8: addiu       $t6, $sp, 0x68
    ctx->r14 = ADD32(ctx->r29, 0X68);
    // 0x801E0BAC: addiu       $t7, $sp, 0x74
    ctx->r15 = ADD32(ctx->r29, 0X74);
    // 0x801E0BB0: swc1        $f0, 0x34($v0)
    MEM_W(0X34, ctx->r2) = ctx->f0.u32l;
    // 0x801E0BB4: lw          $a0, 0x0($s0)
    ctx->r4 = MEM_W(ctx->r16, 0X0);
    // 0x801E0BB8: sw          $zero, 0x18($sp)
    MEM_W(0X18, ctx->r29) = 0;
    // 0x801E0BBC: sw          $t7, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r15;
    // 0x801E0BC0: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x801E0BC4: addiu       $a1, $sp, 0x50
    ctx->r5 = ADD32(ctx->r29, 0X50);
    // 0x801E0BC8: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x801E0BCC: jal         0x801DF668
    // 0x801E0BD0: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_801DF668(rdram, ctx);
        goto after_3;
    // 0x801E0BD0: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_3:
    // 0x801E0BD4: lw          $ra, 0x2C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X2C);
    // 0x801E0BD8: lw          $s0, 0x28($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X28);
    // 0x801E0BDC: addiu       $sp, $sp, 0x80
    ctx->r29 = ADD32(ctx->r29, 0X80);
    // 0x801E0BE0: jr          $ra
    // 0x801E0BE4: nop

    return;
    // 0x801E0BE4: nop

;}
RECOMP_FUNC void func_801E0BE8(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801E0BE8: addiu       $sp, $sp, -0x78
    ctx->r29 = ADD32(ctx->r29, -0X78);
    // 0x801E0BEC: sw          $s0, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r16;
    // 0x801E0BF0: or          $s0, $a0, $zero
    ctx->r16 = ctx->r4 | 0;
    // 0x801E0BF4: sw          $ra, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r31;
    // 0x801E0BF8: or          $a2, $a1, $zero
    ctx->r6 = ctx->r5 | 0;
    // 0x801E0BFC: lw          $a1, 0xC($s0)
    ctx->r5 = MEM_W(ctx->r16, 0XC);
    // 0x801E0C00: jal         0x801DEDE8
    // 0x801E0C04: addiu       $a0, $sp, 0x5C
    ctx->r4 = ADD32(ctx->r29, 0X5C);
    func_801DEDE8(rdram, ctx);
        goto after_0;
    // 0x801E0C04: addiu       $a0, $sp, 0x5C
    ctx->r4 = ADD32(ctx->r29, 0X5C);
    after_0:
    // 0x801E0C08: lw          $v0, 0x0($s0)
    ctx->r2 = MEM_W(ctx->r16, 0X0);
    // 0x801E0C0C: lw          $t6, 0x24($s0)
    ctx->r14 = MEM_W(ctx->r16, 0X24);
    // 0x801E0C10: lw          $t7, 0x1C($s0)
    ctx->r15 = MEM_W(ctx->r16, 0X1C);
    // 0x801E0C14: addiu       $v0, $v0, 0x5C
    ctx->r2 = ADD32(ctx->r2, 0X5C);
    // 0x801E0C18: lwc1        $f12, 0x0($t6)
    ctx->f12.u32l = MEM_W(ctx->r14, 0X0);
    // 0x801E0C1C: lwc1        $f14, 0x0($t7)
    ctx->f14.u32l = MEM_W(ctx->r15, 0X0);
    // 0x801E0C20: jal         0x801ED154
    // 0x801E0C24: sw          $v0, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r2;
    func_801ED154(rdram, ctx);
        goto after_1;
    // 0x801E0C24: sw          $v0, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r2;
    after_1:
    // 0x801E0C28: lwc1        $f4, 0x60($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X60);
    // 0x801E0C2C: lui         $at, 0x4580
    ctx->r1 = S32(0X4580 << 16);
    // 0x801E0C30: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x801E0C34: add.s       $f18, $f4, $f0
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f18.fl = ctx->f4.fl + ctx->f0.fl;
    // 0x801E0C38: lui         $at, 0x43B4
    ctx->r1 = S32(0X43B4 << 16);
    // 0x801E0C3C: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x801E0C40: lui         $at, 0x4580
    ctx->r1 = S32(0X4580 << 16);
    // 0x801E0C44: mul.s       $f10, $f18, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = MUL_S(ctx->f18.fl, ctx->f8.fl);
    // 0x801E0C48: lwc1        $f6, 0x64($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X64);
    // 0x801E0C4C: lui         $a3, 0x8015
    ctx->r7 = S32(0X8015 << 16);
    // 0x801E0C50: addiu       $a3, $a3, 0x4350
    ctx->r7 = ADD32(ctx->r7, 0X4350);
    // 0x801E0C54: swc1        $f6, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->f6.u32l;
    // 0x801E0C58: lw          $t8, 0x10($s0)
    ctx->r24 = MEM_W(ctx->r16, 0X10);
    // 0x801E0C5C: lw          $v0, 0x44($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X44);
    // 0x801E0C60: div.s       $f8, $f10, $f4
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f8.fl = DIV_S(ctx->f10.fl, ctx->f4.fl);
    // 0x801E0C64: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x801E0C68: lui         $at, 0x43B4
    ctx->r1 = S32(0X43B4 << 16);
    // 0x801E0C6C: trunc.w.s   $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.u32l = TRUNC_W_S(ctx->f8.fl);
    // 0x801E0C70: mul.s       $f8, $f6, $f4
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f8.fl = MUL_S(ctx->f6.fl, ctx->f4.fl);
    // 0x801E0C74: mfc1        $v1, $f10
    ctx->r3 = (int32_t)ctx->f10.u32l;
    // 0x801E0C78: mtc1        $at, $f10
    ctx->f10.u32l = ctx->r1;
    // 0x801E0C7C: addiu       $t4, $v1, 0x400
    ctx->r12 = ADD32(ctx->r3, 0X400);
    // 0x801E0C80: div.s       $f6, $f8, $f10
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f6.fl = DIV_S(ctx->f8.fl, ctx->f10.fl);
    // 0x801E0C84: lwc1        $f8, 0x5C($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X5C);
    // 0x801E0C88: andi        $t5, $t4, 0xFFF
    ctx->r13 = ctx->r12 & 0XFFF;
    // 0x801E0C8C: sll         $t6, $t5, 2
    ctx->r14 = S32(ctx->r13 << 2);
    // 0x801E0C90: addu        $t7, $a3, $t6
    ctx->r15 = ADD32(ctx->r7, ctx->r14);
    // 0x801E0C94: trunc.w.s   $f4, $f6
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    ctx->f4.u32l = TRUNC_W_S(ctx->f6.fl);
    // 0x801E0C98: lwc1        $f6, 0x0($t7)
    ctx->f6.u32l = MEM_W(ctx->r15, 0X0);
    // 0x801E0C9C: mfc1        $a0, $f4
    ctx->r4 = (int32_t)ctx->f4.u32l;
    // 0x801E0CA0: nop

    // 0x801E0CA4: addiu       $t0, $a0, 0x400
    ctx->r8 = ADD32(ctx->r4, 0X400);
    // 0x801E0CA8: andi        $t1, $t0, 0xFFF
    ctx->r9 = ctx->r8 & 0XFFF;
    // 0x801E0CAC: sll         $t2, $t1, 2
    ctx->r10 = S32(ctx->r9 << 2);
    // 0x801E0CB0: addu        $t3, $a3, $t2
    ctx->r11 = ADD32(ctx->r7, ctx->r10);
    // 0x801E0CB4: lwc1        $f10, 0x0($t3)
    ctx->f10.u32l = MEM_W(ctx->r11, 0X0);
    // 0x801E0CB8: andi        $t9, $a0, 0xFFF
    ctx->r25 = ctx->r4 & 0XFFF;
    // 0x801E0CBC: sll         $t0, $t9, 2
    ctx->r8 = S32(ctx->r25 << 2);
    // 0x801E0CC0: mul.s       $f2, $f8, $f10
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f2.fl = MUL_S(ctx->f8.fl, ctx->f10.fl);
    // 0x801E0CC4: lwc1        $f10, 0x0($t8)
    ctx->f10.u32l = MEM_W(ctx->r24, 0X0);
    // 0x801E0CC8: addu        $t1, $a3, $t0
    ctx->r9 = ADD32(ctx->r7, ctx->r8);
    // 0x801E0CCC: andi        $t3, $v1, 0xFFF
    ctx->r11 = ctx->r3 & 0XFFF;
    // 0x801E0CD0: sll         $t4, $t3, 2
    ctx->r12 = S32(ctx->r11 << 2);
    // 0x801E0CD4: addu        $t5, $a3, $t4
    ctx->r13 = ADD32(ctx->r7, ctx->r12);
    // 0x801E0CD8: mul.s       $f4, $f6, $f2
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f4.fl = MUL_S(ctx->f6.fl, ctx->f2.fl);
    // 0x801E0CDC: add.s       $f6, $f4, $f10
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f6.fl = ctx->f4.fl + ctx->f10.fl;
    // 0x801E0CE0: lwc1        $f4, 0x0($t1)
    ctx->f4.u32l = MEM_W(ctx->r9, 0X0);
    // 0x801E0CE4: mul.s       $f10, $f4, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = MUL_S(ctx->f4.fl, ctx->f8.fl);
    // 0x801E0CE8: swc1        $f6, 0x50($sp)
    MEM_W(0X50, ctx->r29) = ctx->f6.u32l;
    // 0x801E0CEC: lw          $t2, 0x14($s0)
    ctx->r10 = MEM_W(ctx->r16, 0X14);
    // 0x801E0CF0: lwc1        $f8, 0x0($t5)
    ctx->f8.u32l = MEM_W(ctx->r13, 0X0);
    // 0x801E0CF4: lwc1        $f6, 0x0($t2)
    ctx->f6.u32l = MEM_W(ctx->r10, 0X0);
    // 0x801E0CF8: add.s       $f4, $f10, $f6
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f4.fl = ctx->f10.fl + ctx->f6.fl;
    // 0x801E0CFC: mul.s       $f10, $f8, $f2
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f10.fl = MUL_S(ctx->f8.fl, ctx->f2.fl);
    // 0x801E0D00: swc1        $f4, 0x54($sp)
    MEM_W(0X54, ctx->r29) = ctx->f4.u32l;
    // 0x801E0D04: lw          $t6, 0x18($s0)
    ctx->r14 = MEM_W(ctx->r16, 0X18);
    // 0x801E0D08: lwc1        $f6, 0x0($t6)
    ctx->f6.u32l = MEM_W(ctx->r14, 0X0);
    // 0x801E0D0C: add.s       $f4, $f10, $f6
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f4.fl = ctx->f10.fl + ctx->f6.fl;
    // 0x801E0D10: swc1        $f4, 0x58($sp)
    MEM_W(0X58, ctx->r29) = ctx->f4.u32l;
    // 0x801E0D14: lw          $t7, 0x34($s0)
    ctx->r15 = MEM_W(ctx->r16, 0X34);
    // 0x801E0D18: lw          $t8, 0x74($v0)
    ctx->r24 = MEM_W(ctx->r2, 0X74);
    // 0x801E0D1C: lw          $t1, 0x78($v0)
    ctx->r9 = MEM_W(ctx->r2, 0X78);
    // 0x801E0D20: lwc1        $f8, 0x0($t7)
    ctx->f8.u32l = MEM_W(ctx->r15, 0X0);
    // 0x801E0D24: sll         $t9, $t8, 2
    ctx->r25 = S32(ctx->r24 << 2);
    // 0x801E0D28: addu        $a1, $s0, $t9
    ctx->r5 = ADD32(ctx->r16, ctx->r25);
    // 0x801E0D2C: swc1        $f8, 0xC($v0)
    MEM_W(0XC, ctx->r2) = ctx->f8.u32l;
    // 0x801E0D30: lw          $t0, 0x1C($a1)
    ctx->r8 = MEM_W(ctx->r5, 0X1C);
    // 0x801E0D34: sll         $t2, $t1, 2
    ctx->r10 = S32(ctx->r9 << 2);
    // 0x801E0D38: addu        $a2, $s0, $t2
    ctx->r6 = ADD32(ctx->r16, ctx->r10);
    // 0x801E0D3C: lwc1        $f10, 0x0($t0)
    ctx->f10.u32l = MEM_W(ctx->r8, 0X0);
    // 0x801E0D40: swc1        $f10, 0x24($v0)
    MEM_W(0X24, ctx->r2) = ctx->f10.u32l;
    // 0x801E0D44: lw          $t3, 0x1C($a2)
    ctx->r11 = MEM_W(ctx->r6, 0X1C);
    // 0x801E0D48: lwc1        $f6, 0x0($t3)
    ctx->f6.u32l = MEM_W(ctx->r11, 0X0);
    // 0x801E0D4C: swc1        $f6, 0x28($v0)
    MEM_W(0X28, ctx->r2) = ctx->f6.u32l;
    // 0x801E0D50: lw          $t4, 0x28($a2)
    ctx->r12 = MEM_W(ctx->r6, 0X28);
    // 0x801E0D54: lw          $t5, 0x28($a1)
    ctx->r13 = MEM_W(ctx->r5, 0X28);
    // 0x801E0D58: lwc1        $f14, 0x0($t4)
    ctx->f14.u32l = MEM_W(ctx->r12, 0X0);
    // 0x801E0D5C: lwc1        $f16, 0x0($t5)
    ctx->f16.u32l = MEM_W(ctx->r13, 0X0);
    // 0x801E0D60: mul.s       $f4, $f14, $f14
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f4.fl = MUL_S(ctx->f14.fl, ctx->f14.fl);
    // 0x801E0D64: nop

    // 0x801E0D68: mul.s       $f8, $f16, $f16
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f8.fl = MUL_S(ctx->f16.fl, ctx->f16.fl);
    // 0x801E0D6C: jal         0x800C7010
    // 0x801E0D70: add.s       $f12, $f4, $f8
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f12.fl = ctx->f4.fl + ctx->f8.fl;
    _nsqrtf(rdram, ctx);
        goto after_2;
    // 0x801E0D70: add.s       $f12, $f4, $f8
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f12.fl = ctx->f4.fl + ctx->f8.fl;
    after_2:
    // 0x801E0D74: lw          $v0, 0x44($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X44);
    // 0x801E0D78: addiu       $t6, $sp, 0x68
    ctx->r14 = ADD32(ctx->r29, 0X68);
    // 0x801E0D7C: addiu       $t7, $sp, 0x74
    ctx->r15 = ADD32(ctx->r29, 0X74);
    // 0x801E0D80: swc1        $f0, 0x34($v0)
    MEM_W(0X34, ctx->r2) = ctx->f0.u32l;
    // 0x801E0D84: lw          $a0, 0x0($s0)
    ctx->r4 = MEM_W(ctx->r16, 0X0);
    // 0x801E0D88: sw          $t7, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r15;
    // 0x801E0D8C: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    // 0x801E0D90: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x801E0D94: addiu       $a1, $sp, 0x50
    ctx->r5 = ADD32(ctx->r29, 0X50);
    // 0x801E0D98: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x801E0D9C: jal         0x801DF668
    // 0x801E0DA0: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_801DF668(rdram, ctx);
        goto after_3;
    // 0x801E0DA0: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_3:
    // 0x801E0DA4: lw          $ra, 0x2C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X2C);
    // 0x801E0DA8: lw          $s0, 0x28($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X28);
    // 0x801E0DAC: addiu       $sp, $sp, 0x78
    ctx->r29 = ADD32(ctx->r29, 0X78);
    // 0x801E0DB0: jr          $ra
    // 0x801E0DB4: nop

    return;
    // 0x801E0DB4: nop

;}
RECOMP_FUNC void func_801E0DB8(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801E0DB8: addiu       $sp, $sp, -0x80
    ctx->r29 = ADD32(ctx->r29, -0X80);
    // 0x801E0DBC: sw          $s0, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r16;
    // 0x801E0DC0: or          $s0, $a0, $zero
    ctx->r16 = ctx->r4 | 0;
    // 0x801E0DC4: sw          $ra, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r31;
    // 0x801E0DC8: or          $a2, $a1, $zero
    ctx->r6 = ctx->r5 | 0;
    // 0x801E0DCC: lw          $a1, 0xC($s0)
    ctx->r5 = MEM_W(ctx->r16, 0XC);
    // 0x801E0DD0: jal         0x801DEE48
    // 0x801E0DD4: addiu       $a0, $sp, 0x58
    ctx->r4 = ADD32(ctx->r29, 0X58);
    func_801DEE48(rdram, ctx);
        goto after_0;
    // 0x801E0DD4: addiu       $a0, $sp, 0x58
    ctx->r4 = ADD32(ctx->r29, 0X58);
    after_0:
    // 0x801E0DD8: lw          $v0, 0x0($s0)
    ctx->r2 = MEM_W(ctx->r16, 0X0);
    // 0x801E0DDC: lw          $t6, 0x24($s0)
    ctx->r14 = MEM_W(ctx->r16, 0X24);
    // 0x801E0DE0: lw          $t7, 0x1C($s0)
    ctx->r15 = MEM_W(ctx->r16, 0X1C);
    // 0x801E0DE4: addiu       $v0, $v0, 0x5C
    ctx->r2 = ADD32(ctx->r2, 0X5C);
    // 0x801E0DE8: lwc1        $f12, 0x0($t6)
    ctx->f12.u32l = MEM_W(ctx->r14, 0X0);
    // 0x801E0DEC: lwc1        $f14, 0x0($t7)
    ctx->f14.u32l = MEM_W(ctx->r15, 0X0);
    // 0x801E0DF0: jal         0x801ED154
    // 0x801E0DF4: sw          $v0, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r2;
    func_801ED154(rdram, ctx);
        goto after_1;
    // 0x801E0DF4: sw          $v0, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r2;
    after_1:
    // 0x801E0DF8: lwc1        $f4, 0x5C($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X5C);
    // 0x801E0DFC: lui         $at, 0x4580
    ctx->r1 = S32(0X4580 << 16);
    // 0x801E0E00: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x801E0E04: add.s       $f18, $f4, $f0
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f18.fl = ctx->f4.fl + ctx->f0.fl;
    // 0x801E0E08: lui         $at, 0x43B4
    ctx->r1 = S32(0X43B4 << 16);
    // 0x801E0E0C: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x801E0E10: lui         $at, 0x4580
    ctx->r1 = S32(0X4580 << 16);
    // 0x801E0E14: mul.s       $f10, $f18, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = MUL_S(ctx->f18.fl, ctx->f8.fl);
    // 0x801E0E18: lwc1        $f6, 0x60($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X60);
    // 0x801E0E1C: lui         $a3, 0x8015
    ctx->r7 = S32(0X8015 << 16);
    // 0x801E0E20: addiu       $a3, $a3, 0x4350
    ctx->r7 = ADD32(ctx->r7, 0X4350);
    // 0x801E0E24: swc1        $f6, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->f6.u32l;
    // 0x801E0E28: lw          $t8, 0x10($s0)
    ctx->r24 = MEM_W(ctx->r16, 0X10);
    // 0x801E0E2C: lw          $v0, 0x40($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X40);
    // 0x801E0E30: div.s       $f8, $f10, $f4
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f8.fl = DIV_S(ctx->f10.fl, ctx->f4.fl);
    // 0x801E0E34: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x801E0E38: lui         $at, 0x43B4
    ctx->r1 = S32(0X43B4 << 16);
    // 0x801E0E3C: trunc.w.s   $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.u32l = TRUNC_W_S(ctx->f8.fl);
    // 0x801E0E40: mul.s       $f8, $f6, $f4
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f8.fl = MUL_S(ctx->f6.fl, ctx->f4.fl);
    // 0x801E0E44: mfc1        $v1, $f10
    ctx->r3 = (int32_t)ctx->f10.u32l;
    // 0x801E0E48: mtc1        $at, $f10
    ctx->f10.u32l = ctx->r1;
    // 0x801E0E4C: addiu       $t4, $v1, 0x400
    ctx->r12 = ADD32(ctx->r3, 0X400);
    // 0x801E0E50: div.s       $f6, $f8, $f10
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f6.fl = DIV_S(ctx->f8.fl, ctx->f10.fl);
    // 0x801E0E54: lwc1        $f8, 0x58($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X58);
    // 0x801E0E58: andi        $t5, $t4, 0xFFF
    ctx->r13 = ctx->r12 & 0XFFF;
    // 0x801E0E5C: sll         $t6, $t5, 2
    ctx->r14 = S32(ctx->r13 << 2);
    // 0x801E0E60: addu        $t7, $a3, $t6
    ctx->r15 = ADD32(ctx->r7, ctx->r14);
    // 0x801E0E64: trunc.w.s   $f4, $f6
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    ctx->f4.u32l = TRUNC_W_S(ctx->f6.fl);
    // 0x801E0E68: lwc1        $f6, 0x0($t7)
    ctx->f6.u32l = MEM_W(ctx->r15, 0X0);
    // 0x801E0E6C: mfc1        $a0, $f4
    ctx->r4 = (int32_t)ctx->f4.u32l;
    // 0x801E0E70: nop

    // 0x801E0E74: addiu       $t0, $a0, 0x400
    ctx->r8 = ADD32(ctx->r4, 0X400);
    // 0x801E0E78: andi        $t1, $t0, 0xFFF
    ctx->r9 = ctx->r8 & 0XFFF;
    // 0x801E0E7C: sll         $t2, $t1, 2
    ctx->r10 = S32(ctx->r9 << 2);
    // 0x801E0E80: addu        $t3, $a3, $t2
    ctx->r11 = ADD32(ctx->r7, ctx->r10);
    // 0x801E0E84: lwc1        $f10, 0x0($t3)
    ctx->f10.u32l = MEM_W(ctx->r11, 0X0);
    // 0x801E0E88: andi        $t9, $a0, 0xFFF
    ctx->r25 = ctx->r4 & 0XFFF;
    // 0x801E0E8C: sll         $t0, $t9, 2
    ctx->r8 = S32(ctx->r25 << 2);
    // 0x801E0E90: mul.s       $f2, $f8, $f10
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f2.fl = MUL_S(ctx->f8.fl, ctx->f10.fl);
    // 0x801E0E94: lwc1        $f10, 0x0($t8)
    ctx->f10.u32l = MEM_W(ctx->r24, 0X0);
    // 0x801E0E98: addu        $t1, $a3, $t0
    ctx->r9 = ADD32(ctx->r7, ctx->r8);
    // 0x801E0E9C: andi        $t3, $v1, 0xFFF
    ctx->r11 = ctx->r3 & 0XFFF;
    // 0x801E0EA0: sll         $t4, $t3, 2
    ctx->r12 = S32(ctx->r11 << 2);
    // 0x801E0EA4: addu        $t5, $a3, $t4
    ctx->r13 = ADD32(ctx->r7, ctx->r12);
    // 0x801E0EA8: mul.s       $f4, $f6, $f2
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f4.fl = MUL_S(ctx->f6.fl, ctx->f2.fl);
    // 0x801E0EAC: add.s       $f6, $f4, $f10
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f6.fl = ctx->f4.fl + ctx->f10.fl;
    // 0x801E0EB0: lwc1        $f4, 0x0($t1)
    ctx->f4.u32l = MEM_W(ctx->r9, 0X0);
    // 0x801E0EB4: mul.s       $f10, $f4, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = MUL_S(ctx->f4.fl, ctx->f8.fl);
    // 0x801E0EB8: swc1        $f6, 0x4C($sp)
    MEM_W(0X4C, ctx->r29) = ctx->f6.u32l;
    // 0x801E0EBC: lw          $t2, 0x14($s0)
    ctx->r10 = MEM_W(ctx->r16, 0X14);
    // 0x801E0EC0: lwc1        $f8, 0x0($t5)
    ctx->f8.u32l = MEM_W(ctx->r13, 0X0);
    // 0x801E0EC4: lwc1        $f6, 0x0($t2)
    ctx->f6.u32l = MEM_W(ctx->r10, 0X0);
    // 0x801E0EC8: add.s       $f4, $f10, $f6
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f4.fl = ctx->f10.fl + ctx->f6.fl;
    // 0x801E0ECC: mul.s       $f10, $f8, $f2
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f10.fl = MUL_S(ctx->f8.fl, ctx->f2.fl);
    // 0x801E0ED0: swc1        $f4, 0x50($sp)
    MEM_W(0X50, ctx->r29) = ctx->f4.u32l;
    // 0x801E0ED4: lw          $t6, 0x18($s0)
    ctx->r14 = MEM_W(ctx->r16, 0X18);
    // 0x801E0ED8: lwc1        $f6, 0x0($t6)
    ctx->f6.u32l = MEM_W(ctx->r14, 0X0);
    // 0x801E0EDC: add.s       $f4, $f10, $f6
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f4.fl = ctx->f10.fl + ctx->f6.fl;
    // 0x801E0EE0: swc1        $f4, 0x54($sp)
    MEM_W(0X54, ctx->r29) = ctx->f4.u32l;
    // 0x801E0EE4: lw          $t7, 0x34($s0)
    ctx->r15 = MEM_W(ctx->r16, 0X34);
    // 0x801E0EE8: lw          $t8, 0x74($v0)
    ctx->r24 = MEM_W(ctx->r2, 0X74);
    // 0x801E0EEC: lw          $t1, 0x78($v0)
    ctx->r9 = MEM_W(ctx->r2, 0X78);
    // 0x801E0EF0: lwc1        $f8, 0x0($t7)
    ctx->f8.u32l = MEM_W(ctx->r15, 0X0);
    // 0x801E0EF4: sll         $t9, $t8, 2
    ctx->r25 = S32(ctx->r24 << 2);
    // 0x801E0EF8: addu        $a1, $s0, $t9
    ctx->r5 = ADD32(ctx->r16, ctx->r25);
    // 0x801E0EFC: swc1        $f8, 0xC($v0)
    MEM_W(0XC, ctx->r2) = ctx->f8.u32l;
    // 0x801E0F00: lw          $t0, 0x1C($a1)
    ctx->r8 = MEM_W(ctx->r5, 0X1C);
    // 0x801E0F04: sll         $t2, $t1, 2
    ctx->r10 = S32(ctx->r9 << 2);
    // 0x801E0F08: addu        $a2, $s0, $t2
    ctx->r6 = ADD32(ctx->r16, ctx->r10);
    // 0x801E0F0C: lwc1        $f10, 0x0($t0)
    ctx->f10.u32l = MEM_W(ctx->r8, 0X0);
    // 0x801E0F10: swc1        $f10, 0x24($v0)
    MEM_W(0X24, ctx->r2) = ctx->f10.u32l;
    // 0x801E0F14: lw          $t3, 0x1C($a2)
    ctx->r11 = MEM_W(ctx->r6, 0X1C);
    // 0x801E0F18: lwc1        $f6, 0x0($t3)
    ctx->f6.u32l = MEM_W(ctx->r11, 0X0);
    // 0x801E0F1C: swc1        $f6, 0x28($v0)
    MEM_W(0X28, ctx->r2) = ctx->f6.u32l;
    // 0x801E0F20: lw          $t4, 0x28($a2)
    ctx->r12 = MEM_W(ctx->r6, 0X28);
    // 0x801E0F24: lw          $t5, 0x28($a1)
    ctx->r13 = MEM_W(ctx->r5, 0X28);
    // 0x801E0F28: lwc1        $f14, 0x0($t4)
    ctx->f14.u32l = MEM_W(ctx->r12, 0X0);
    // 0x801E0F2C: lwc1        $f16, 0x0($t5)
    ctx->f16.u32l = MEM_W(ctx->r13, 0X0);
    // 0x801E0F30: mul.s       $f4, $f14, $f14
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f4.fl = MUL_S(ctx->f14.fl, ctx->f14.fl);
    // 0x801E0F34: nop

    // 0x801E0F38: mul.s       $f8, $f16, $f16
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f8.fl = MUL_S(ctx->f16.fl, ctx->f16.fl);
    // 0x801E0F3C: jal         0x800C7010
    // 0x801E0F40: add.s       $f12, $f4, $f8
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f12.fl = ctx->f4.fl + ctx->f8.fl;
    _nsqrtf(rdram, ctx);
        goto after_2;
    // 0x801E0F40: add.s       $f12, $f4, $f8
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f12.fl = ctx->f4.fl + ctx->f8.fl;
    after_2:
    // 0x801E0F44: lw          $v0, 0x40($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X40);
    // 0x801E0F48: addiu       $t6, $sp, 0x64
    ctx->r14 = ADD32(ctx->r29, 0X64);
    // 0x801E0F4C: addiu       $t7, $sp, 0x70
    ctx->r15 = ADD32(ctx->r29, 0X70);
    // 0x801E0F50: swc1        $f0, 0x34($v0)
    MEM_W(0X34, ctx->r2) = ctx->f0.u32l;
    // 0x801E0F54: lw          $a0, 0x0($s0)
    ctx->r4 = MEM_W(ctx->r16, 0X0);
    // 0x801E0F58: addiu       $t8, $sp, 0x7C
    ctx->r24 = ADD32(ctx->r29, 0X7C);
    // 0x801E0F5C: sw          $t8, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r24;
    // 0x801E0F60: sw          $t7, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r15;
    // 0x801E0F64: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x801E0F68: addiu       $a1, $sp, 0x4C
    ctx->r5 = ADD32(ctx->r29, 0X4C);
    // 0x801E0F6C: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x801E0F70: jal         0x801DF668
    // 0x801E0F74: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_801DF668(rdram, ctx);
        goto after_3;
    // 0x801E0F74: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_3:
    // 0x801E0F78: lw          $ra, 0x2C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X2C);
    // 0x801E0F7C: lw          $s0, 0x28($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X28);
    // 0x801E0F80: addiu       $sp, $sp, 0x80
    ctx->r29 = ADD32(ctx->r29, 0X80);
    // 0x801E0F84: jr          $ra
    // 0x801E0F88: nop

    return;
    // 0x801E0F88: nop

;}
RECOMP_FUNC void func_801E0F8C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801E0F8C: lwc1        $f4, 0x10($a1)
    ctx->f4.u32l = MEM_W(ctx->r5, 0X10);
    // 0x801E0F90: swc1        $f4, 0x4C($a0)
    MEM_W(0X4C, ctx->r4) = ctx->f4.u32l;
    // 0x801E0F94: lwc1        $f6, 0x14($a1)
    ctx->f6.u32l = MEM_W(ctx->r5, 0X14);
    // 0x801E0F98: swc1        $f6, 0x50($a0)
    MEM_W(0X50, ctx->r4) = ctx->f6.u32l;
    // 0x801E0F9C: lwc1        $f8, 0x18($a1)
    ctx->f8.u32l = MEM_W(ctx->r5, 0X18);
    // 0x801E0FA0: swc1        $f8, 0x54($a0)
    MEM_W(0X54, ctx->r4) = ctx->f8.u32l;
    // 0x801E0FA4: lwc1        $f10, 0x4($a1)
    ctx->f10.u32l = MEM_W(ctx->r5, 0X4);
    // 0x801E0FA8: swc1        $f10, 0x7C($a0)
    MEM_W(0X7C, ctx->r4) = ctx->f10.u32l;
    // 0x801E0FAC: lwc1        $f16, 0x8($a1)
    ctx->f16.u32l = MEM_W(ctx->r5, 0X8);
    // 0x801E0FB0: swc1        $f16, 0x80($a0)
    MEM_W(0X80, ctx->r4) = ctx->f16.u32l;
    // 0x801E0FB4: lwc1        $f18, 0xC($a1)
    ctx->f18.u32l = MEM_W(ctx->r5, 0XC);
    // 0x801E0FB8: swc1        $f18, 0x84($a0)
    MEM_W(0X84, ctx->r4) = ctx->f18.u32l;
    // 0x801E0FBC: lwc1        $f4, 0x1C($a1)
    ctx->f4.u32l = MEM_W(ctx->r5, 0X1C);
    // 0x801E0FC0: swc1        $f4, 0x70($a0)
    MEM_W(0X70, ctx->r4) = ctx->f4.u32l;
    // 0x801E0FC4: lwc1        $f6, 0x20($a1)
    ctx->f6.u32l = MEM_W(ctx->r5, 0X20);
    // 0x801E0FC8: swc1        $f6, 0x74($a0)
    MEM_W(0X74, ctx->r4) = ctx->f6.u32l;
    // 0x801E0FCC: lwc1        $f8, 0x24($a1)
    ctx->f8.u32l = MEM_W(ctx->r5, 0X24);
    // 0x801E0FD0: swc1        $f8, 0x78($a0)
    MEM_W(0X78, ctx->r4) = ctx->f8.u32l;
    // 0x801E0FD4: lwc1        $f10, 0x38($a1)
    ctx->f10.u32l = MEM_W(ctx->r5, 0X38);
    // 0x801E0FD8: swc1        $f10, 0x88($a0)
    MEM_W(0X88, ctx->r4) = ctx->f10.u32l;
    // 0x801E0FDC: lwc1        $f16, 0x44($a1)
    ctx->f16.u32l = MEM_W(ctx->r5, 0X44);
    // 0x801E0FE0: swc1        $f16, 0x94($a0)
    MEM_W(0X94, ctx->r4) = ctx->f16.u32l;
    // 0x801E0FE4: lwc1        $f18, 0x48($a1)
    ctx->f18.u32l = MEM_W(ctx->r5, 0X48);
    // 0x801E0FE8: jr          $ra
    // 0x801E0FEC: swc1        $f18, 0x98($a0)
    MEM_W(0X98, ctx->r4) = ctx->f18.u32l;
    return;
    // 0x801E0FEC: swc1        $f18, 0x98($a0)
    MEM_W(0X98, ctx->r4) = ctx->f18.u32l;
;}
RECOMP_FUNC void func_801E0FF0(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801E0FF0: addiu       $sp, $sp, -0x38
    ctx->r29 = ADD32(ctx->r29, -0X38);
    // 0x801E0FF4: sw          $ra, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r31;
    // 0x801E0FF8: sw          $s0, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r16;
    // 0x801E0FFC: sdc1        $f24, 0x28($sp)
    CHECK_FR(ctx, 24);
    SD(ctx->f24.u64, 0X28, ctx->r29);
    // 0x801E1000: sdc1        $f22, 0x20($sp)
    CHECK_FR(ctx, 22);
    SD(ctx->f22.u64, 0X20, ctx->r29);
    // 0x801E1004: sdc1        $f20, 0x18($sp)
    CHECK_FR(ctx, 20);
    SD(ctx->f20.u64, 0X18, ctx->r29);
    // 0x801E1008: lwc1        $f6, 0x4C($a0)
    ctx->f6.u32l = MEM_W(ctx->r4, 0X4C);
    // 0x801E100C: lwc1        $f4, 0x7C($a0)
    ctx->f4.u32l = MEM_W(ctx->r4, 0X7C);
    // 0x801E1010: lwc1        $f10, 0x50($a0)
    ctx->f10.u32l = MEM_W(ctx->r4, 0X50);
    // 0x801E1014: lwc1        $f8, 0x80($a0)
    ctx->f8.u32l = MEM_W(ctx->r4, 0X80);
    // 0x801E1018: sub.s       $f0, $f4, $f6
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f0.fl = ctx->f4.fl - ctx->f6.fl;
    // 0x801E101C: lwc1        $f6, 0x54($a0)
    ctx->f6.u32l = MEM_W(ctx->r4, 0X54);
    // 0x801E1020: lwc1        $f4, 0x84($a0)
    ctx->f4.u32l = MEM_W(ctx->r4, 0X84);
    // 0x801E1024: sub.s       $f2, $f8, $f10
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f2.fl = ctx->f8.fl - ctx->f10.fl;
    // 0x801E1028: mul.s       $f8, $f0, $f0
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f8.fl = MUL_S(ctx->f0.fl, ctx->f0.fl);
    // 0x801E102C: or          $s0, $a0, $zero
    ctx->r16 = ctx->r4 | 0;
    // 0x801E1030: sub.s       $f14, $f4, $f6
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f14.fl = ctx->f4.fl - ctx->f6.fl;
    // 0x801E1034: mul.s       $f10, $f2, $f2
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f10.fl = MUL_S(ctx->f2.fl, ctx->f2.fl);
    // 0x801E1038: swc1        $f0, 0x64($a0)
    MEM_W(0X64, ctx->r4) = ctx->f0.u32l;
    // 0x801E103C: swc1        $f2, 0x68($a0)
    MEM_W(0X68, ctx->r4) = ctx->f2.u32l;
    // 0x801E1040: mul.s       $f6, $f14, $f14
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f6.fl = MUL_S(ctx->f14.fl, ctx->f14.fl);
    // 0x801E1044: swc1        $f14, 0x6C($a0)
    MEM_W(0X6C, ctx->r4) = ctx->f14.u32l;
    // 0x801E1048: add.s       $f4, $f8, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f4.fl = ctx->f8.fl + ctx->f10.fl;
    // 0x801E104C: jal         0x800C7010
    // 0x801E1050: add.s       $f12, $f4, $f6
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f12.fl = ctx->f4.fl + ctx->f6.fl;
    _nsqrtf(rdram, ctx);
        goto after_0;
    // 0x801E1050: add.s       $f12, $f4, $f6
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f12.fl = ctx->f4.fl + ctx->f6.fl;
    after_0:
    // 0x801E1054: lwc1        $f8, 0x64($s0)
    ctx->f8.u32l = MEM_W(ctx->r16, 0X64);
    // 0x801E1058: lwc1        $f4, 0x68($s0)
    ctx->f4.u32l = MEM_W(ctx->r16, 0X68);
    // 0x801E105C: div.s       $f10, $f8, $f0
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f10.fl = DIV_S(ctx->f8.fl, ctx->f0.fl);
    // 0x801E1060: lwc1        $f8, 0x6C($s0)
    ctx->f8.u32l = MEM_W(ctx->r16, 0X6C);
    // 0x801E1064: div.s       $f6, $f4, $f0
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f6.fl = DIV_S(ctx->f4.fl, ctx->f0.fl);
    // 0x801E1068: swc1        $f10, 0x64($s0)
    MEM_W(0X64, ctx->r16) = ctx->f10.u32l;
    // 0x801E106C: lwc1        $f2, 0x64($s0)
    ctx->f2.u32l = MEM_W(ctx->r16, 0X64);
    // 0x801E1070: mul.s       $f4, $f2, $f2
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f4.fl = MUL_S(ctx->f2.fl, ctx->f2.fl);
    // 0x801E1074: div.s       $f10, $f8, $f0
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f10.fl = DIV_S(ctx->f8.fl, ctx->f0.fl);
    // 0x801E1078: swc1        $f6, 0x68($s0)
    MEM_W(0X68, ctx->r16) = ctx->f6.u32l;
    // 0x801E107C: swc1        $f10, 0x6C($s0)
    MEM_W(0X6C, ctx->r16) = ctx->f10.u32l;
    // 0x801E1080: lwc1        $f14, 0x6C($s0)
    ctx->f14.u32l = MEM_W(ctx->r16, 0X6C);
    // 0x801E1084: mul.s       $f6, $f14, $f14
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f6.fl = MUL_S(ctx->f14.fl, ctx->f14.fl);
    // 0x801E1088: jal         0x800C7010
    // 0x801E108C: add.s       $f12, $f4, $f6
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f12.fl = ctx->f4.fl + ctx->f6.fl;
    _nsqrtf(rdram, ctx);
        goto after_1;
    // 0x801E108C: add.s       $f12, $f4, $f6
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f12.fl = ctx->f4.fl + ctx->f6.fl;
    after_1:
    // 0x801E1090: lwc1        $f14, 0x6C($s0)
    ctx->f14.u32l = MEM_W(ctx->r16, 0X6C);
    // 0x801E1094: lwc1        $f2, 0x64($s0)
    ctx->f2.u32l = MEM_W(ctx->r16, 0X64);
    // 0x801E1098: lwc1        $f24, 0x68($s0)
    ctx->f24.u32l = MEM_W(ctx->r16, 0X68);
    // 0x801E109C: div.s       $f10, $f14, $f0
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f10.fl = DIV_S(ctx->f14.fl, ctx->f0.fl);
    // 0x801E10A0: lwc1        $f18, 0x70($s0)
    ctx->f18.u32l = MEM_W(ctx->r16, 0X70);
    // 0x801E10A4: lwc1        $f20, 0x74($s0)
    ctx->f20.u32l = MEM_W(ctx->r16, 0X74);
    // 0x801E10A8: lwc1        $f22, 0x78($s0)
    ctx->f22.u32l = MEM_W(ctx->r16, 0X78);
    // 0x801E10AC: mul.s       $f4, $f2, $f2
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f4.fl = MUL_S(ctx->f2.fl, ctx->f2.fl);
    // 0x801E10B0: nop

    // 0x801E10B4: mul.s       $f6, $f24, $f24
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 24);
    NAN_CHECK(ctx->f24.fl); NAN_CHECK(ctx->f24.fl); 
    ctx->f6.fl = MUL_S(ctx->f24.fl, ctx->f24.fl);
    // 0x801E10B8: div.s       $f8, $f2, $f0
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f8.fl = DIV_S(ctx->f2.fl, ctx->f0.fl);
    // 0x801E10BC: swc1        $f10, 0xF4($s0)
    MEM_W(0XF4, ctx->r16) = ctx->f10.u32l;
    // 0x801E10C0: mul.s       $f10, $f14, $f14
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f10.fl = MUL_S(ctx->f14.fl, ctx->f14.fl);
    // 0x801E10C4: swc1        $f8, 0xF0($s0)
    MEM_W(0XF0, ctx->r16) = ctx->f8.u32l;
    // 0x801E10C8: add.s       $f8, $f4, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = ctx->f4.fl + ctx->f6.fl;
    // 0x801E10CC: mul.s       $f4, $f2, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f4.fl = MUL_S(ctx->f2.fl, ctx->f18.fl);
    // 0x801E10D0: nop

    // 0x801E10D4: mul.s       $f6, $f24, $f20
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f24.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f6.fl = MUL_S(ctx->f24.fl, ctx->f20.fl);
    // 0x801E10D8: add.s       $f16, $f8, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f16.fl = ctx->f8.fl + ctx->f10.fl;
    // 0x801E10DC: mul.s       $f10, $f14, $f22
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f10.fl = MUL_S(ctx->f14.fl, ctx->f22.fl);
    // 0x801E10E0: add.s       $f8, $f4, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = ctx->f4.fl + ctx->f6.fl;
    // 0x801E10E4: add.s       $f4, $f8, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f4.fl = ctx->f8.fl + ctx->f10.fl;
    // 0x801E10E8: neg.s       $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = -ctx->f4.fl;
    // 0x801E10EC: div.s       $f16, $f6, $f16
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f16.fl = DIV_S(ctx->f6.fl, ctx->f16.fl);
    // 0x801E10F0: mul.s       $f8, $f2, $f16
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f8.fl = MUL_S(ctx->f2.fl, ctx->f16.fl);
    // 0x801E10F4: add.s       $f10, $f18, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = ctx->f18.fl + ctx->f8.fl;
    // 0x801E10F8: mul.s       $f4, $f24, $f16
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f24.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f4.fl = MUL_S(ctx->f24.fl, ctx->f16.fl);
    // 0x801E10FC: swc1        $f10, 0x70($s0)
    MEM_W(0X70, ctx->r16) = ctx->f10.u32l;
    // 0x801E1100: mul.s       $f8, $f14, $f16
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f8.fl = MUL_S(ctx->f14.fl, ctx->f16.fl);
    // 0x801E1104: lwc1        $f18, 0x70($s0)
    ctx->f18.u32l = MEM_W(ctx->r16, 0X70);
    // 0x801E1108: add.s       $f6, $f20, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = ctx->f20.fl + ctx->f4.fl;
    // 0x801E110C: mul.s       $f4, $f18, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f4.fl = MUL_S(ctx->f18.fl, ctx->f18.fl);
    // 0x801E1110: add.s       $f10, $f22, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = ctx->f22.fl + ctx->f8.fl;
    // 0x801E1114: swc1        $f6, 0x74($s0)
    MEM_W(0X74, ctx->r16) = ctx->f6.u32l;
    // 0x801E1118: lwc1        $f20, 0x74($s0)
    ctx->f20.u32l = MEM_W(ctx->r16, 0X74);
    // 0x801E111C: swc1        $f10, 0x78($s0)
    MEM_W(0X78, ctx->r16) = ctx->f10.u32l;
    // 0x801E1120: mul.s       $f6, $f20, $f20
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f6.fl = MUL_S(ctx->f20.fl, ctx->f20.fl);
    // 0x801E1124: lwc1        $f22, 0x78($s0)
    ctx->f22.u32l = MEM_W(ctx->r16, 0X78);
    // 0x801E1128: mul.s       $f10, $f22, $f22
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f10.fl = MUL_S(ctx->f22.fl, ctx->f22.fl);
    // 0x801E112C: add.s       $f8, $f4, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = ctx->f4.fl + ctx->f6.fl;
    // 0x801E1130: jal         0x800C7010
    // 0x801E1134: add.s       $f12, $f8, $f10
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f12.fl = ctx->f8.fl + ctx->f10.fl;
    _nsqrtf(rdram, ctx);
        goto after_2;
    // 0x801E1134: add.s       $f12, $f8, $f10
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f12.fl = ctx->f8.fl + ctx->f10.fl;
    after_2:
    // 0x801E1138: lwc1        $f4, 0x70($s0)
    ctx->f4.u32l = MEM_W(ctx->r16, 0X70);
    // 0x801E113C: lwc1        $f8, 0x74($s0)
    ctx->f8.u32l = MEM_W(ctx->r16, 0X74);
    // 0x801E1140: div.s       $f6, $f4, $f0
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f6.fl = DIV_S(ctx->f4.fl, ctx->f0.fl);
    // 0x801E1144: lwc1        $f4, 0x78($s0)
    ctx->f4.u32l = MEM_W(ctx->r16, 0X78);
    // 0x801E1148: div.s       $f10, $f8, $f0
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f10.fl = DIV_S(ctx->f8.fl, ctx->f0.fl);
    // 0x801E114C: swc1        $f6, 0x70($s0)
    MEM_W(0X70, ctx->r16) = ctx->f6.u32l;
    // 0x801E1150: lwc1        $f8, 0x4C($s0)
    ctx->f8.u32l = MEM_W(ctx->r16, 0X4C);
    // 0x801E1154: div.s       $f6, $f4, $f0
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f6.fl = DIV_S(ctx->f4.fl, ctx->f0.fl);
    // 0x801E1158: swc1        $f10, 0x74($s0)
    MEM_W(0X74, ctx->r16) = ctx->f10.u32l;
    // 0x801E115C: lwc1        $f10, 0x7C($s0)
    ctx->f10.u32l = MEM_W(ctx->r16, 0X7C);
    // 0x801E1160: lwc1        $f4, 0x54($s0)
    ctx->f4.u32l = MEM_W(ctx->r16, 0X54);
    // 0x801E1164: sub.s       $f2, $f8, $f10
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f2.fl = ctx->f8.fl - ctx->f10.fl;
    // 0x801E1168: mul.s       $f8, $f2, $f2
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f8.fl = MUL_S(ctx->f2.fl, ctx->f2.fl);
    // 0x801E116C: swc1        $f6, 0x78($s0)
    MEM_W(0X78, ctx->r16) = ctx->f6.u32l;
    // 0x801E1170: lwc1        $f6, 0x84($s0)
    ctx->f6.u32l = MEM_W(ctx->r16, 0X84);
    // 0x801E1174: sub.s       $f14, $f4, $f6
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f14.fl = ctx->f4.fl - ctx->f6.fl;
    // 0x801E1178: mul.s       $f10, $f14, $f14
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f10.fl = MUL_S(ctx->f14.fl, ctx->f14.fl);
    // 0x801E117C: jal         0x800C7010
    // 0x801E1180: add.s       $f12, $f8, $f10
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f12.fl = ctx->f8.fl + ctx->f10.fl;
    _nsqrtf(rdram, ctx);
        goto after_3;
    // 0x801E1180: add.s       $f12, $f8, $f10
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f12.fl = ctx->f8.fl + ctx->f10.fl;
    after_3:
    // 0x801E1184: lwc1        $f4, 0x50($s0)
    ctx->f4.u32l = MEM_W(ctx->r16, 0X50);
    // 0x801E1188: lwc1        $f6, 0x80($s0)
    ctx->f6.u32l = MEM_W(ctx->r16, 0X80);
    // 0x801E118C: swc1        $f0, 0x8C($s0)
    MEM_W(0X8C, ctx->r16) = ctx->f0.u32l;
    // 0x801E1190: sub.s       $f8, $f4, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = ctx->f4.fl - ctx->f6.fl;
    // 0x801E1194: swc1        $f8, 0x90($s0)
    MEM_W(0X90, ctx->r16) = ctx->f8.u32l;
    // 0x801E1198: lw          $ra, 0x34($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X34);
    // 0x801E119C: lw          $s0, 0x30($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X30);
    // 0x801E11A0: ldc1        $f24, 0x28($sp)
    CHECK_FR(ctx, 24);
    ctx->f24.u64 = LD(ctx->r29, 0X28);
    // 0x801E11A4: ldc1        $f22, 0x20($sp)
    CHECK_FR(ctx, 22);
    ctx->f22.u64 = LD(ctx->r29, 0X20);
    // 0x801E11A8: ldc1        $f20, 0x18($sp)
    CHECK_FR(ctx, 20);
    ctx->f20.u64 = LD(ctx->r29, 0X18);
    // 0x801E11AC: jr          $ra
    // 0x801E11B0: addiu       $sp, $sp, 0x38
    ctx->r29 = ADD32(ctx->r29, 0X38);
    return;
    // 0x801E11B0: addiu       $sp, $sp, 0x38
    ctx->r29 = ADD32(ctx->r29, 0X38);
;}
RECOMP_FUNC void func_801E11B4(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801E11B4: addiu       $sp, $sp, -0x40
    ctx->r29 = ADD32(ctx->r29, -0X40);
    // 0x801E11B8: sw          $s0, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r16;
    // 0x801E11BC: or          $s0, $a1, $zero
    ctx->r16 = ctx->r5 | 0;
    // 0x801E11C0: sw          $ra, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r31;
    // 0x801E11C4: sw          $a0, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r4;
    // 0x801E11C8: lwc1        $f4, 0x9C($s0)
    ctx->f4.u32l = MEM_W(ctx->r16, 0X9C);
    // 0x801E11CC: lw          $t7, 0xE8($a1)
    ctx->r15 = MEM_W(ctx->r5, 0XE8);
    // 0x801E11D0: lw          $a2, 0x88($s0)
    ctx->r6 = MEM_W(ctx->r16, 0X88);
    { extern uint32_t wr64_camera_fov_lens(const uint8_t*, uint32_t, uint32_t, uint32_t); ctx->r6 = S32(wr64_camera_fov_lens(rdram, (uint32_t)ctx->r16, (uint32_t)ctx->r4, (uint32_t)ctx->r6)); }
    // 0x801E11D4: swc1        $f4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f4.u32l;
    // 0x801E11D8: lwc1        $f6, 0xA0($s0)
    ctx->f6.u32l = MEM_W(ctx->r16, 0XA0);
    // 0x801E11DC: sll         $t8, $t7, 6
    ctx->r24 = S32(ctx->r15 << 6);
    // 0x801E11E0: addu        $a0, $a0, $t8
    ctx->r4 = ADD32(ctx->r4, ctx->r24);
    // 0x801E11E4: swc1        $f6, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->f6.u32l;
    // 0x801E11E8: lwc1        $f8, 0x94($s0)
    ctx->f8.u32l = MEM_W(ctx->r16, 0X94);
    // 0x801E11EC: ori         $at, $zero, 0xE008
    ctx->r1 = 0 | 0XE008;
    // 0x801E11F0: lui         $a3, 0x3FE2
    ctx->r7 = S32(0X3FE2 << 16);
    // 0x801E11F4: addiu       $a3, $a3, 0x2222
    ctx->r7 = ADD32(ctx->r7, 0X2222);
    // 0x801E11F8: swc1        $f8, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->f8.u32l;
    // 0x801E11FC: lwc1        $f10, 0x98($s0)
    ctx->f10.u32l = MEM_W(ctx->r16, 0X98);
    // 0x801E1200: addu        $a0, $a0, $at
    ctx->r4 = ADD32(ctx->r4, ctx->r1);
    // 0x801E1204: addiu       $a1, $a1, 0xE4
    ctx->r5 = ADD32(ctx->r5, 0XE4);
    // 0x801E1208: jal         0x800481E0
    // 0x801E120C: swc1        $f10, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->f10.u32l;
    func_800481E0(rdram, ctx);
        goto after_0;
    // 0x801E120C: swc1        $f10, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->f10.u32l;
    after_0:
    // 0x801E1210: lwc1        $f16, 0x54($s0)
    ctx->f16.u32l = MEM_W(ctx->r16, 0X54);
    // 0x801E1214: lw          $t0, 0xE8($s0)
    ctx->r8 = MEM_W(ctx->r16, 0XE8);
    // 0x801E1218: lw          $a2, 0x4C($s0)
    ctx->r6 = MEM_W(ctx->r16, 0X4C);
    // 0x801E121C: lw          $a3, 0x50($s0)
    ctx->r7 = MEM_W(ctx->r16, 0X50);
    // 0x801E1220: swc1        $f16, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f16.u32l;
    // 0x801E1224: lwc1        $f18, 0x7C($s0)
    ctx->f18.u32l = MEM_W(ctx->r16, 0X7C);
    // 0x801E1228: lw          $t9, 0x40($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X40);
    // 0x801E122C: sll         $t1, $t0, 6
    ctx->r9 = S32(ctx->r8 << 6);
    // 0x801E1230: swc1        $f18, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->f18.u32l;
    // 0x801E1234: lwc1        $f4, 0x80($s0)
    ctx->f4.u32l = MEM_W(ctx->r16, 0X80);
    // 0x801E1238: ori         $at, $zero, 0xE088
    ctx->r1 = 0 | 0XE088;
    // 0x801E123C: addu        $a0, $t9, $t1
    ctx->r4 = ADD32(ctx->r25, ctx->r9);
    // 0x801E1240: swc1        $f4, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->f4.u32l;
    // 0x801E1244: lwc1        $f6, 0x84($s0)
    ctx->f6.u32l = MEM_W(ctx->r16, 0X84);
    // 0x801E1248: addu        $a0, $a0, $at
    ctx->r4 = ADD32(ctx->r4, ctx->r1);
    // 0x801E124C: addiu       $a1, $s0, 0xA4
    ctx->r5 = ADD32(ctx->r16, 0XA4);
    // 0x801E1250: swc1        $f6, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->f6.u32l;
    // 0x801E1254: lwc1        $f8, 0x70($s0)
    ctx->f8.u32l = MEM_W(ctx->r16, 0X70);
    // 0x801E1258: swc1        $f8, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->f8.u32l;
    // 0x801E125C: lwc1        $f10, 0x74($s0)
    ctx->f10.u32l = MEM_W(ctx->r16, 0X74);
    // 0x801E1260: swc1        $f10, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->f10.u32l;
    // 0x801E1264: lwc1        $f16, 0x78($s0)
    ctx->f16.u32l = MEM_W(ctx->r16, 0X78);
    // 0x801E1268: jal         0x800484C8
    // 0x801E126C: swc1        $f16, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->f16.u32l;
    func_800484C8(rdram, ctx);
        goto after_1;
    // 0x801E126C: swc1        $f16, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->f16.u32l;
    after_1:
    // 0x801E1270: lw          $ra, 0x3C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X3C);
    // 0x801E1274: lw          $s0, 0x38($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X38);
    // 0x801E1278: addiu       $sp, $sp, 0x40
    ctx->r29 = ADD32(ctx->r29, 0X40);
    // 0x801E127C: jr          $ra
    // 0x801E1280: nop

    return;
    // 0x801E1280: nop

    // 0x801E1284: nop

    // 0x801E1288: nop

    // 0x801E128C: nop

;}
RECOMP_FUNC void func_801E1290(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801E1290: addiu       $sp, $sp, -0x258
    ctx->r29 = ADD32(ctx->r29, -0X258);
    // 0x801E1294: lui         $t6, 0x801D
    ctx->r14 = S32(0X801D << 16);
    // 0x801E1298: lw          $t6, -0x19C4($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X19C4);
    // 0x801E129C: sw          $ra, 0x54($sp)
    MEM_W(0X54, ctx->r29) = ctx->r31;
    // 0x801E12A0: sw          $s5, 0x50($sp)
    MEM_W(0X50, ctx->r29) = ctx->r21;
    // 0x801E12A4: sw          $s4, 0x4C($sp)
    MEM_W(0X4C, ctx->r29) = ctx->r20;
    // 0x801E12A8: sw          $s3, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r19;
    // 0x801E12AC: sw          $s2, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r18;
    // 0x801E12B0: sw          $s1, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r17;
    // 0x801E12B4: sw          $s0, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r16;
    // 0x801E12B8: sdc1        $f20, 0x30($sp)
    CHECK_FR(ctx, 20);
    SD(ctx->f20.u64, 0X30, ctx->r29);
    // 0x801E12BC: beq         $t6, $zero, L_801E12E0
    if (ctx->r14 == 0) {
        // 0x801E12C0: sw          $zero, 0x248($sp)
        MEM_W(0X248, ctx->r29) = 0;
            goto L_801E12E0;
    }
    // 0x801E12C0: sw          $zero, 0x248($sp)
    MEM_W(0X248, ctx->r29) = 0;
    // 0x801E12C4: lui         $t7, 0x800E
    ctx->r15 = S32(0X800E << 16);
    // 0x801E12C8: lw          $t7, -0x54DC($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X54DC);
    // 0x801E12CC: addiu       $at, $zero, 0x64
    ctx->r1 = ADD32(0, 0X64);
    // 0x801E12D0: bne         $t7, $at, L_801E12E0
    if (ctx->r15 != ctx->r1) {
        // 0x801E12D4: nop
    
            goto L_801E12E0;
    }
    // 0x801E12D4: nop

    // 0x801E12D8: jal         0x801E1BA8
    // 0x801E12DC: nop

    func_801E1BA8(rdram, ctx);
        goto after_0;
    // 0x801E12DC: nop

    after_0:
L_801E12E0:
    // 0x801E12E0: lui         $a2, 0x8022
    ctx->r6 = S32(0X8022 << 16);
    // 0x801E12E4: addiu       $a2, $a2, 0x61C8
    ctx->r6 = ADD32(ctx->r6, 0X61C8);
    // 0x801E12E8: lw          $v0, 0x0($a2)
    ctx->r2 = MEM_W(ctx->r6, 0X0);
    // 0x801E12EC: sltiu       $at, $v0, 0xA
    ctx->r1 = ctx->r2 < 0XA ? 1 : 0;
    // 0x801E12F0: beq         $at, $zero, L_801E17F4
    if (ctx->r1 == 0) {
        // 0x801E12F4: sll         $t8, $v0, 2
        ctx->r24 = S32(ctx->r2 << 2);
            goto L_801E17F4;
    }
    // 0x801E12F4: sll         $t8, $v0, 2
    ctx->r24 = S32(ctx->r2 << 2);
    // 0x801E12F8: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E12FC: addu        $at, $at, $t8
    gpr jr_addend_801E1304 = ctx->r24;
    ctx->r1 = ADD32(ctx->r1, ctx->r24);
    // 0x801E1300: lw          $t8, 0x6288($at)
    ctx->r24 = ADD32(ctx->r1, 0X6288);
    // 0x801E1304: jr          $t8
    // 0x801E1308: nop

    switch (jr_addend_801E1304 >> 2) {
        case 0: goto L_801E130C; break;
        case 1: goto L_801E1374; break;
        case 2: goto L_801E1380; break;
        case 3: goto L_801E1488; break;
        case 4: goto L_801E1584; break;
        case 5: goto L_801E17F4; break;
        case 6: goto L_801E175C; break;
        case 7: goto L_801E1790; break;
        case 8: goto L_801E1380; break;
        case 9: goto L_801E1488; break;
        default: switch_error(__func__, 0x801E1304, 0x80226288);
    }
    // 0x801E1308: nop

L_801E130C:
    // 0x801E130C: lui         $v1, 0x8022
    ctx->r3 = S32(0X8022 << 16);
    // 0x801E1310: addiu       $v1, $v1, 0x61E0
    ctx->r3 = ADD32(ctx->r3, 0X61E0);
    // 0x801E1314: lw          $v0, 0x0($v1)
    ctx->r2 = MEM_W(ctx->r3, 0X0);
    // 0x801E1318: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E131C: lwc1        $f2, 0x62B0($at)
    ctx->f2.u32l = MEM_W(ctx->r1, 0X62B0);
    // 0x801E1320: mtc1        $v0, $f4
    ctx->f4.u32l = ctx->r2;
    // 0x801E1324: lui         $at, 0x41F0
    ctx->r1 = S32(0X41F0 << 16);
    // 0x801E1328: mtc1        $at, $f10
    ctx->f10.u32l = ctx->r1;
    // 0x801E132C: cvt.s.w     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
    // 0x801E1330: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E1334: addiu       $t9, $v0, 0x1
    ctx->r25 = ADD32(ctx->r2, 0X1);
    // 0x801E1338: addiu       $t1, $zero, 0x1
    ctx->r9 = ADD32(0, 0X1);
    // 0x801E133C: addiu       $t2, $zero, 0x1
    ctx->r10 = ADD32(0, 0X1);
    // 0x801E1340: mul.s       $f8, $f6, $f2
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f8.fl = MUL_S(ctx->f6.fl, ctx->f2.fl);
    // 0x801E1344: div.s       $f16, $f8, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f16.fl = DIV_S(ctx->f8.fl, ctx->f10.fl);
    // 0x801E1348: swc1        $f16, 0x61CC($at)
    MEM_W(0X61CC, ctx->r1) = ctx->f16.u32l;
    // 0x801E134C: slti        $at, $t9, 0x1F
    ctx->r1 = SIGNED(ctx->r25) < 0X1F ? 1 : 0;
    // 0x801E1350: bne         $at, $zero, L_801E17F4
    if (ctx->r1 != 0) {
        // 0x801E1354: sw          $t9, 0x0($v1)
        MEM_W(0X0, ctx->r3) = ctx->r25;
            goto L_801E17F4;
    }
    // 0x801E1354: sw          $t9, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r25;
    // 0x801E1358: sw          $zero, 0x0($v1)
    MEM_W(0X0, ctx->r3) = 0;
    // 0x801E135C: sw          $t1, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r9;
    // 0x801E1360: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E1364: swc1        $f2, 0x61CC($at)
    MEM_W(0X61CC, ctx->r1) = ctx->f2.u32l;
    // 0x801E1368: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E136C: b           L_801E17F4
    // 0x801E1370: sw          $t2, 0x61E8($at)
    MEM_W(0X61E8, ctx->r1) = ctx->r10;
        goto L_801E17F4;
    // 0x801E1370: sw          $t2, 0x61E8($at)
    MEM_W(0X61E8, ctx->r1) = ctx->r10;
L_801E1374:
    // 0x801E1374: addiu       $t3, $zero, 0x1
    ctx->r11 = ADD32(0, 0X1);
    // 0x801E1378: b           L_801E17F4
    // 0x801E137C: sw          $t3, 0x248($sp)
    MEM_W(0X248, ctx->r29) = ctx->r11;
        goto L_801E17F4;
    // 0x801E137C: sw          $t3, 0x248($sp)
    MEM_W(0X248, ctx->r29) = ctx->r11;
L_801E1380:
    // 0x801E1380: addiu       $s0, $zero, 0x8
    ctx->r16 = ADD32(0, 0X8);
    // 0x801E1384: addiu       $t4, $zero, 0x1
    ctx->r12 = ADD32(0, 0X1);
    // 0x801E1388: bne         $s0, $v0, L_801E139C
    if (ctx->r16 != ctx->r2) {
        // 0x801E138C: sw          $t4, 0x248($sp)
        MEM_W(0X248, ctx->r29) = ctx->r12;
            goto L_801E139C;
    }
    // 0x801E138C: sw          $t4, 0x248($sp)
    MEM_W(0X248, ctx->r29) = ctx->r12;
    // 0x801E1390: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E1394: b           L_801E13DC
    // 0x801E1398: lwc1        $f12, 0x62B4($at)
    ctx->f12.u32l = MEM_W(ctx->r1, 0X62B4);
        goto L_801E13DC;
    // 0x801E1398: lwc1        $f12, 0x62B4($at)
    ctx->f12.u32l = MEM_W(ctx->r1, 0X62B4);
L_801E139C:
    // 0x801E139C: lui         $t5, 0x8022
    ctx->r13 = S32(0X8022 << 16);
    // 0x801E13A0: lh          $t5, 0x61DC($t5)
    ctx->r13 = MEM_H(ctx->r13, 0X61DC);
    // 0x801E13A4: beq         $t5, $zero, L_801E13C4
    if (ctx->r13 == 0) {
        // 0x801E13A8: nop
    
            goto L_801E13C4;
    }
    // 0x801E13A8: nop

    // 0x801E13AC: jal         0x801E31A0
    // 0x801E13B0: nop

    func_801E31A0(rdram, ctx);
        goto after_1;
    // 0x801E13B0: nop

    after_1:
    // 0x801E13B4: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E13B8: lui         $a2, 0x8022
    ctx->r6 = S32(0X8022 << 16);
    // 0x801E13BC: addiu       $a2, $a2, 0x61C8
    ctx->r6 = ADD32(ctx->r6, 0X61C8);
    // 0x801E13C0: swc1        $f0, 0x61D8($at)
    MEM_W(0X61D8, ctx->r1) = ctx->f0.u32l;
L_801E13C4:
    // 0x801E13C4: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E13C8: lwc1        $f18, 0x62B8($at)
    ctx->f18.u32l = MEM_W(ctx->r1, 0X62B8);
    // 0x801E13CC: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E13D0: lwc1        $f4, 0x61D8($at)
    ctx->f4.u32l = MEM_W(ctx->r1, 0X61D8);
    // 0x801E13D4: mul.s       $f12, $f18, $f4
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f12.fl = MUL_S(ctx->f18.fl, ctx->f4.fl);
    // 0x801E13D8: nop

L_801E13DC:
    // 0x801E13DC: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E13E0: lwc1        $f6, 0x61D0($at)
    ctx->f6.u32l = MEM_W(ctx->r1, 0X61D0);
    // 0x801E13E4: mtc1        $zero, $f20
    ctx->f20.u32l = 0;
    // 0x801E13E8: sub.s       $f8, $f6, $f12
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f8.fl = ctx->f6.fl - ctx->f12.fl;
    // 0x801E13EC: c.lt.s      $f8, $f20
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 20);
    c1cs = ctx->f8.fl < ctx->f20.fl;
    // 0x801E13F0: swc1        $f8, 0x61D0($at)
    MEM_W(0X61D0, ctx->r1) = ctx->f8.u32l;
    // 0x801E13F4: mov.s       $f0, $f8
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 8);
    ctx->f0.fl = ctx->f8.fl;
    // 0x801E13F8: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E13FC: bc1f        L_801E1430
    if (!c1cs) {
        // 0x801E1400: nop
    
            goto L_801E1430;
    }
    // 0x801E1400: nop

    // 0x801E1404: lwc1        $f10, 0x61D4($at)
    ctx->f10.u32l = MEM_W(ctx->r1, 0X61D4);
    // 0x801E1408: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E140C: c.eq.s      $f20, $f10
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 10);
    c1cs = ctx->f20.fl == ctx->f10.fl;
    // 0x801E1410: nop

    // 0x801E1414: bc1t        L_801E1430
    if (c1cs) {
        // 0x801E1418: nop
    
            goto L_801E1430;
    }
    // 0x801E1418: nop

    // 0x801E141C: lwc1        $f16, 0x62BC($at)
    ctx->f16.u32l = MEM_W(ctx->r1, 0X62BC);
    // 0x801E1420: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E1424: add.s       $f18, $f8, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f18.fl = ctx->f8.fl + ctx->f16.fl;
    // 0x801E1428: swc1        $f18, 0x61D0($at)
    MEM_W(0X61D0, ctx->r1) = ctx->f18.u32l;
    // 0x801E142C: lwc1        $f0, 0x61D0($at)
    ctx->f0.u32l = MEM_W(ctx->r1, 0X61D0);
L_801E1430:
    // 0x801E1430: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E1434: lwc1        $f2, 0x61D4($at)
    ctx->f2.u32l = MEM_W(ctx->r1, 0X61D4);
    // 0x801E1438: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E143C: c.le.s      $f0, $f2
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    c1cs = ctx->f0.fl <= ctx->f2.fl;
    // 0x801E1440: nop

    // 0x801E1444: bc1f        L_801E17F4
    if (!c1cs) {
        // 0x801E1448: nop
    
            goto L_801E17F4;
    }
    // 0x801E1448: nop

    // 0x801E144C: swc1        $f2, 0x61D0($at)
    MEM_W(0X61D0, ctx->r1) = ctx->f2.u32l;
    // 0x801E1450: lw          $t6, 0x0($a2)
    ctx->r14 = MEM_W(ctx->r6, 0X0);
    // 0x801E1454: lui         $t7, 0x8023
    ctx->r15 = S32(0X8023 << 16);
    // 0x801E1458: addiu       $t0, $zero, 0x1
    ctx->r8 = ADD32(0, 0X1);
    // 0x801E145C: bne         $s0, $t6, L_801E1480
    if (ctx->r16 != ctx->r14) {
        // 0x801E1460: nop
    
            goto L_801E1480;
    }
    // 0x801E1460: nop

    // 0x801E1464: lhu         $t7, -0x7714($t7)
    ctx->r15 = MEM_HU(ctx->r15, -0X7714);
    // 0x801E1468: addiu       $t9, $zero, 0xA
    ctx->r25 = ADD32(0, 0XA);
    // 0x801E146C: andi        $t8, $t7, 0x1
    ctx->r24 = ctx->r15 & 0X1;
    // 0x801E1470: beq         $t8, $zero, L_801E1480
    if (ctx->r24 == 0) {
        // 0x801E1474: nop
    
            goto L_801E1480;
    }
    // 0x801E1474: nop

    // 0x801E1478: b           L_801E17F4
    // 0x801E147C: sw          $t9, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r25;
        goto L_801E17F4;
    // 0x801E147C: sw          $t9, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r25;
L_801E1480:
    // 0x801E1480: b           L_801E17F4
    // 0x801E1484: sw          $t0, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r8;
        goto L_801E17F4;
    // 0x801E1484: sw          $t0, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r8;
L_801E1488:
    // 0x801E1488: addiu       $s0, $zero, 0x9
    ctx->r16 = ADD32(0, 0X9);
    // 0x801E148C: addiu       $t1, $zero, 0x1
    ctx->r9 = ADD32(0, 0X1);
    // 0x801E1490: bne         $s0, $v0, L_801E14A4
    if (ctx->r16 != ctx->r2) {
        // 0x801E1494: sw          $t1, 0x248($sp)
        MEM_W(0X248, ctx->r29) = ctx->r9;
            goto L_801E14A4;
    }
    // 0x801E1494: sw          $t1, 0x248($sp)
    MEM_W(0X248, ctx->r29) = ctx->r9;
    // 0x801E1498: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E149C: b           L_801E14E4
    // 0x801E14A0: lwc1        $f12, 0x62C0($at)
    ctx->f12.u32l = MEM_W(ctx->r1, 0X62C0);
        goto L_801E14E4;
    // 0x801E14A0: lwc1        $f12, 0x62C0($at)
    ctx->f12.u32l = MEM_W(ctx->r1, 0X62C0);
L_801E14A4:
    // 0x801E14A4: lui         $t2, 0x8022
    ctx->r10 = S32(0X8022 << 16);
    // 0x801E14A8: lh          $t2, 0x61DC($t2)
    ctx->r10 = MEM_H(ctx->r10, 0X61DC);
    // 0x801E14AC: beq         $t2, $zero, L_801E14CC
    if (ctx->r10 == 0) {
        // 0x801E14B0: nop
    
            goto L_801E14CC;
    }
    // 0x801E14B0: nop

    // 0x801E14B4: jal         0x801E31A0
    // 0x801E14B8: nop

    func_801E31A0(rdram, ctx);
        goto after_2;
    // 0x801E14B8: nop

    after_2:
    // 0x801E14BC: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E14C0: lui         $a2, 0x8022
    ctx->r6 = S32(0X8022 << 16);
    // 0x801E14C4: addiu       $a2, $a2, 0x61C8
    ctx->r6 = ADD32(ctx->r6, 0X61C8);
    // 0x801E14C8: swc1        $f0, 0x61D8($at)
    MEM_W(0X61D8, ctx->r1) = ctx->f0.u32l;
L_801E14CC:
    // 0x801E14CC: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E14D0: lwc1        $f4, 0x62C4($at)
    ctx->f4.u32l = MEM_W(ctx->r1, 0X62C4);
    // 0x801E14D4: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E14D8: lwc1        $f6, 0x61D8($at)
    ctx->f6.u32l = MEM_W(ctx->r1, 0X61D8);
    // 0x801E14DC: mul.s       $f12, $f4, $f6
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f12.fl = MUL_S(ctx->f4.fl, ctx->f6.fl);
    // 0x801E14E0: nop

L_801E14E4:
    // 0x801E14E4: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E14E8: lwc1        $f8, 0x61D0($at)
    ctx->f8.u32l = MEM_W(ctx->r1, 0X61D0);
    // 0x801E14EC: add.s       $f0, $f8, $f12
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f0.fl = ctx->f8.fl + ctx->f12.fl;
    // 0x801E14F0: swc1        $f0, 0x61D0($at)
    MEM_W(0X61D0, ctx->r1) = ctx->f0.u32l;
    // 0x801E14F4: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E14F8: lwc1        $f2, 0x61D4($at)
    ctx->f2.u32l = MEM_W(ctx->r1, 0X61D4);
    // 0x801E14FC: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E1500: c.le.s      $f2, $f0
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 0);
    c1cs = ctx->f2.fl <= ctx->f0.fl;
    // 0x801E1504: nop

    // 0x801E1508: bc1f        L_801E1554
    if (!c1cs) {
        // 0x801E150C: nop
    
            goto L_801E1554;
    }
    // 0x801E150C: nop

    // 0x801E1510: swc1        $f2, 0x61D0($at)
    MEM_W(0X61D0, ctx->r1) = ctx->f2.u32l;
    // 0x801E1514: lw          $t3, 0x0($a2)
    ctx->r11 = MEM_W(ctx->r6, 0X0);
    // 0x801E1518: lui         $t4, 0x8023
    ctx->r12 = S32(0X8023 << 16);
    // 0x801E151C: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E1520: bne         $s0, $t3, L_801E154C
    if (ctx->r16 != ctx->r11) {
        // 0x801E1524: addiu       $t7, $zero, 0x1
        ctx->r15 = ADD32(0, 0X1);
            goto L_801E154C;
    }
    // 0x801E1524: addiu       $t7, $zero, 0x1
    ctx->r15 = ADD32(0, 0X1);
    // 0x801E1528: lhu         $t4, -0x7714($t4)
    ctx->r12 = MEM_HU(ctx->r12, -0X7714);
    // 0x801E152C: addiu       $t6, $zero, 0xA
    ctx->r14 = ADD32(0, 0XA);
    // 0x801E1530: andi        $t5, $t4, 0x2
    ctx->r13 = ctx->r12 & 0X2;
    // 0x801E1534: beql        $t5, $zero, L_801E1550
    if (ctx->r13 == 0) {
        // 0x801E1538: sw          $t7, 0x0($a2)
        MEM_W(0X0, ctx->r6) = ctx->r15;
            goto L_801E1550;
    }
    goto skip_0;
    // 0x801E1538: sw          $t7, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r15;
    skip_0:
    // 0x801E153C: sw          $t6, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r14;
    // 0x801E1540: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E1544: b           L_801E1554
    // 0x801E1548: lwc1        $f0, 0x61D0($at)
    ctx->f0.u32l = MEM_W(ctx->r1, 0X61D0);
        goto L_801E1554;
    // 0x801E1548: lwc1        $f0, 0x61D0($at)
    ctx->f0.u32l = MEM_W(ctx->r1, 0X61D0);
L_801E154C:
    // 0x801E154C: sw          $t7, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r15;
L_801E1550:
    // 0x801E1550: lwc1        $f0, 0x61D0($at)
    ctx->f0.u32l = MEM_W(ctx->r1, 0X61D0);
L_801E1554:
    // 0x801E1554: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E1558: lwc1        $f16, 0x62C8($at)
    ctx->f16.u32l = MEM_W(ctx->r1, 0X62C8);
    // 0x801E155C: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E1560: c.le.s      $f16, $f0
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 0);
    c1cs = ctx->f16.fl <= ctx->f0.fl;
    // 0x801E1564: nop

    // 0x801E1568: bc1f        L_801E17F4
    if (!c1cs) {
        // 0x801E156C: nop
    
            goto L_801E17F4;
    }
    // 0x801E156C: nop

    // 0x801E1570: lwc1        $f18, 0x62CC($at)
    ctx->f18.u32l = MEM_W(ctx->r1, 0X62CC);
    // 0x801E1574: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E1578: sub.s       $f4, $f0, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f4.fl = ctx->f0.fl - ctx->f18.fl;
    // 0x801E157C: b           L_801E17F4
    // 0x801E1580: swc1        $f4, 0x61D0($at)
    MEM_W(0X61D0, ctx->r1) = ctx->f4.u32l;
        goto L_801E17F4;
    // 0x801E1580: swc1        $f4, 0x61D0($at)
    MEM_W(0X61D0, ctx->r1) = ctx->f4.u32l;
L_801E1584:
    // 0x801E1584: lui         $v1, 0x8022
    ctx->r3 = S32(0X8022 << 16);
    // 0x801E1588: addiu       $v1, $v1, 0x61E0
    ctx->r3 = ADD32(ctx->r3, 0X61E0);
    // 0x801E158C: lw          $t9, 0x0($v1)
    ctx->r25 = MEM_W(ctx->r3, 0X0);
    // 0x801E1590: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E1594: mtc1        $zero, $f18
    ctx->f18.u32l = 0;
    // 0x801E1598: addiu       $v0, $t9, 0x1
    ctx->r2 = ADD32(ctx->r25, 0X1);
    // 0x801E159C: mtc1        $v0, $f6
    ctx->f6.u32l = ctx->r2;
    // 0x801E15A0: sw          $v0, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r2;
    // 0x801E15A4: ldc1        $f10, 0x62D0($at)
    CHECK_FR(ctx, 10);
    ctx->f10.u64 = LD(ctx->r1, 0X62D0);
    // 0x801E15A8: cvt.s.w     $f0, $f6
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 6);
    ctx->f0.fl = CVT_S_W(ctx->f6.u32l);
    // 0x801E15AC: lui         $at, 0x4030
    ctx->r1 = S32(0X4030 << 16);
    // 0x801E15B0: mtc1        $at, $f19
    ctx->f_odd[(19 - 1) * 2] = ctx->r1;
    // 0x801E15B4: addiu       $t8, $zero, 0x1
    ctx->r24 = ADD32(0, 0X1);
    // 0x801E15B8: slti        $at, $v0, 0x10
    ctx->r1 = SIGNED(ctx->r2) < 0X10 ? 1 : 0;
    // 0x801E15BC: sw          $t8, 0x248($sp)
    MEM_W(0X248, ctx->r29) = ctx->r24;
    // 0x801E15C0: cvt.d.s     $f8, $f0
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f0.fl); 
    ctx->f8.d = CVT_D_S(ctx->f0.fl);
    // 0x801E15C4: lui         $t1, 0x8022
    ctx->r9 = S32(0X8022 << 16);
    // 0x801E15C8: mul.d       $f16, $f8, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.d); NAN_CHECK(ctx->f10.d); 
    ctx->f16.d = MUL_D(ctx->f8.d, ctx->f10.d);
    // 0x801E15CC: lui         $a1, 0x8023
    ctx->r5 = S32(0X8023 << 16);
    // 0x801E15D0: div.d       $f4, $f16, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f16.d); NAN_CHECK(ctx->f18.d); 
    ctx->f4.d = DIV_D(ctx->f16.d, ctx->f18.d);
    // 0x801E15D4: cvt.s.d     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f4.d); 
    ctx->f6.fl = CVT_S_D(ctx->f4.d);
    // 0x801E15D8: bne         $at, $zero, L_801E16F0
    if (ctx->r1 != 0) {
        // 0x801E15DC: swc1        $f6, 0x238($sp)
        MEM_W(0X238, ctx->r29) = ctx->f6.u32l;
            goto L_801E16F0;
    }
    // 0x801E15DC: swc1        $f6, 0x238($sp)
    MEM_W(0X238, ctx->r29) = ctx->f6.u32l;
    // 0x801E15E0: lw          $t1, 0x61C4($t1)
    ctx->r9 = MEM_W(ctx->r9, 0X61C4);
    // 0x801E15E4: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E15E8: lwc1        $f2, 0x62D8($at)
    ctx->f2.u32l = MEM_W(ctx->r1, 0X62D8);
    // 0x801E15EC: sll         $t2, $t1, 2
    ctx->r10 = S32(ctx->r9 << 2);
    // 0x801E15F0: addu        $a1, $a1, $t2
    ctx->r5 = ADD32(ctx->r5, ctx->r10);
    // 0x801E15F4: lw          $a1, -0x7818($a1)
    ctx->r5 = MEM_W(ctx->r5, -0X7818);
    // 0x801E15F8: addiu       $at, $zero, 0x1E
    ctx->r1 = ADD32(0, 0X1E);
    // 0x801E15FC: swc1        $f2, 0x23C($sp)
    MEM_W(0X23C, ctx->r29) = ctx->f2.u32l;
    // 0x801E1600: bne         $a1, $at, L_801E163C
    if (ctx->r5 != ctx->r1) {
        // 0x801E1604: or          $a0, $a1, $zero
        ctx->r4 = ctx->r5 | 0;
            goto L_801E163C;
    }
    // 0x801E1604: or          $a0, $a1, $zero
    ctx->r4 = ctx->r5 | 0;
    // 0x801E1608: lui         $t3, 0x801D
    ctx->r11 = S32(0X801D << 16);
    // 0x801E160C: lw          $t3, -0x19F8($t3)
    ctx->r11 = MEM_W(ctx->r11, -0X19F8);
    // 0x801E1610: addiu       $at, $zero, 0x4
    ctx->r1 = ADD32(0, 0X4);
    // 0x801E1614: addiu       $t4, $zero, 0x5
    ctx->r12 = ADD32(0, 0X5);
    // 0x801E1618: bne         $t3, $at, L_801E1628
    if (ctx->r11 != ctx->r1) {
        // 0x801E161C: addiu       $t5, $zero, 0x7
        ctx->r13 = ADD32(0, 0X7);
            goto L_801E1628;
    }
    // 0x801E161C: addiu       $t5, $zero, 0x7
    ctx->r13 = ADD32(0, 0X7);
    // 0x801E1620: b           L_801E17F4
    // 0x801E1624: sw          $t4, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r12;
        goto L_801E17F4;
    // 0x801E1624: sw          $t4, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r12;
L_801E1628:
    // 0x801E1628: sw          $t5, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r13;
    // 0x801E162C: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E1630: sw          $zero, 0x61E8($at)
    MEM_W(0X61E8, ctx->r1) = 0;
    // 0x801E1634: b           L_801E17F4
    // 0x801E1638: sw          $zero, 0x0($v1)
    MEM_W(0X0, ctx->r3) = 0;
        goto L_801E17F4;
    // 0x801E1638: sw          $zero, 0x0($v1)
    MEM_W(0X0, ctx->r3) = 0;
L_801E163C:
    // 0x801E163C: addiu       $at, $zero, 0x1D
    ctx->r1 = ADD32(0, 0X1D);
    // 0x801E1640: bne         $a0, $at, L_801E167C
    if (ctx->r4 != ctx->r1) {
        // 0x801E1644: lui         $v1, 0x8022
        ctx->r3 = S32(0X8022 << 16);
            goto L_801E167C;
    }
    // 0x801E1644: lui         $v1, 0x8022
    ctx->r3 = S32(0X8022 << 16);
    // 0x801E1648: lui         $v1, 0x8022
    ctx->r3 = S32(0X8022 << 16);
    // 0x801E164C: addiu       $v1, $v1, 0x61E4
    ctx->r3 = ADD32(ctx->r3, 0X61E4);
    // 0x801E1650: lw          $v0, 0x0($v1)
    ctx->r2 = MEM_W(ctx->r3, 0X0);
    // 0x801E1654: addiu       $t6, $zero, 0x1
    ctx->r14 = ADD32(0, 0X1);
    // 0x801E1658: sw          $t6, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r14;
    // 0x801E165C: blez        $v0, L_801E1670
    if (SIGNED(ctx->r2) <= 0) {
        // 0x801E1660: lui         $at, 0x8023
        ctx->r1 = S32(0X8023 << 16);
            goto L_801E1670;
    }
    // 0x801E1660: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801E1664: addiu       $t7, $v0, -0x1
    ctx->r15 = ADD32(ctx->r2, -0X1);
    // 0x801E1668: sw          $t7, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r15;
    // 0x801E166C: or          $v0, $t7, $zero
    ctx->r2 = ctx->r15 | 0;
L_801E1670:
    // 0x801E1670: addu        $at, $at, $v0
    ctx->r1 = ADD32(ctx->r1, ctx->r2);
    // 0x801E1674: b           L_801E17F4
    // 0x801E1678: sb          $zero, -0x7718($at)
    MEM_B(-0X7718, ctx->r1) = 0;
        goto L_801E17F4;
    // 0x801E1678: sb          $zero, -0x7718($at)
    MEM_B(-0X7718, ctx->r1) = 0;
L_801E167C:
    // 0x801E167C: sll         $t8, $a0, 2
    ctx->r24 = S32(ctx->r4 << 2);
    // 0x801E1680: lui         $t9, 0x8022
    ctx->r25 = S32(0X8022 << 16);
    // 0x801E1684: addu        $t9, $t9, $t8
    ctx->r25 = ADD32(ctx->r25, ctx->r24);
    // 0x801E1688: lw          $t9, 0x60BC($t9)
    ctx->r25 = MEM_W(ctx->r25, 0X60BC);
    // 0x801E168C: addiu       $v1, $v1, 0x61E4
    ctx->r3 = ADD32(ctx->r3, 0X61E4);
    // 0x801E1690: lw          $v0, 0x0($v1)
    ctx->r2 = MEM_W(ctx->r3, 0X0);
    // 0x801E1694: lb          $t0, 0x0($t9)
    ctx->r8 = MEM_B(ctx->r25, 0X0);
    // 0x801E1698: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801E169C: addu        $at, $at, $v0
    ctx->r1 = ADD32(ctx->r1, ctx->r2);
    // 0x801E16A0: sb          $t0, -0x7718($at)
    MEM_B(-0X7718, ctx->r1) = ctx->r8;
    // 0x801E16A4: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x801E16A8: addiu       $t1, $v0, 0x1
    ctx->r9 = ADD32(ctx->r2, 0X1);
    // 0x801E16AC: bne         $t1, $at, L_801E16E4
    if (ctx->r9 != ctx->r1) {
        // 0x801E16B0: sw          $t1, 0x0($v1)
        MEM_W(0X0, ctx->r3) = ctx->r9;
            goto L_801E16E4;
    }
    // 0x801E16B0: sw          $t1, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r9;
    // 0x801E16B4: addiu       $t3, $zero, 0xA
    ctx->r11 = ADD32(0, 0XA);
    // 0x801E16B8: slti        $at, $a1, 0x10
    ctx->r1 = SIGNED(ctx->r5) < 0X10 ? 1 : 0;
    // 0x801E16BC: bne         $at, $zero, L_801E16D4
    if (ctx->r1 != 0) {
        // 0x801E16C0: sw          $t3, 0x0($a2)
        MEM_W(0X0, ctx->r6) = ctx->r11;
            goto L_801E16D4;
    }
    // 0x801E16C0: sw          $t3, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r11;
    // 0x801E16C4: addiu       $t4, $zero, 0x2
    ctx->r12 = ADD32(0, 0X2);
    // 0x801E16C8: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801E16CC: b           L_801E17F4
    // 0x801E16D0: sh          $t4, -0x7714($at)
    MEM_H(-0X7714, ctx->r1) = ctx->r12;
        goto L_801E17F4;
    // 0x801E16D0: sh          $t4, -0x7714($at)
    MEM_H(-0X7714, ctx->r1) = ctx->r12;
L_801E16D4:
    // 0x801E16D4: addiu       $t5, $zero, 0x1
    ctx->r13 = ADD32(0, 0X1);
    // 0x801E16D8: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801E16DC: b           L_801E17F4
    // 0x801E16E0: sh          $t5, -0x7714($at)
    MEM_H(-0X7714, ctx->r1) = ctx->r13;
        goto L_801E17F4;
    // 0x801E16E0: sh          $t5, -0x7714($at)
    MEM_H(-0X7714, ctx->r1) = ctx->r13;
L_801E16E4:
    // 0x801E16E4: addiu       $t6, $zero, 0x1
    ctx->r14 = ADD32(0, 0X1);
    // 0x801E16E8: b           L_801E17F4
    // 0x801E16EC: sw          $t6, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r14;
        goto L_801E17F4;
    // 0x801E16EC: sw          $t6, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r14;
L_801E16F0:
    // 0x801E16F0: slti        $at, $v0, 0x8
    ctx->r1 = SIGNED(ctx->r2) < 0X8 ? 1 : 0;
    // 0x801E16F4: bne         $at, $zero, L_801E1730
    if (ctx->r1 != 0) {
        // 0x801E16F8: addiu       $t7, $v0, -0x8
        ctx->r15 = ADD32(ctx->r2, -0X8);
            goto L_801E1730;
    }
    // 0x801E16F8: addiu       $t7, $v0, -0x8
    ctx->r15 = ADD32(ctx->r2, -0X8);
    // 0x801E16FC: mtc1        $t7, $f8
    ctx->f8.u32l = ctx->r15;
    // 0x801E1700: lui         $at, 0x43C8
    ctx->r1 = S32(0X43C8 << 16);
    // 0x801E1704: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
    // 0x801E1708: cvt.s.w     $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.fl = CVT_S_W(ctx->f8.u32l);
    // 0x801E170C: lui         $at, 0x4100
    ctx->r1 = S32(0X4100 << 16);
    // 0x801E1710: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x801E1714: lui         $at, 0x43AF
    ctx->r1 = S32(0X43AF << 16);
    // 0x801E1718: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x801E171C: mul.s       $f18, $f10, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f18.fl = MUL_S(ctx->f10.fl, ctx->f16.fl);
    // 0x801E1720: div.s       $f6, $f18, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = DIV_S(ctx->f18.fl, ctx->f4.fl);
    // 0x801E1724: add.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = ctx->f6.fl + ctx->f8.fl;
    // 0x801E1728: b           L_801E17F4
    // 0x801E172C: swc1        $f10, 0x23C($sp)
    MEM_W(0X23C, ctx->r29) = ctx->f10.u32l;
        goto L_801E17F4;
    // 0x801E172C: swc1        $f10, 0x23C($sp)
    MEM_W(0X23C, ctx->r29) = ctx->f10.u32l;
L_801E1730:
    // 0x801E1730: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E1734: lwc1        $f2, 0x62DC($at)
    ctx->f2.u32l = MEM_W(ctx->r1, 0X62DC);
    // 0x801E1738: lui         $at, 0x43C8
    ctx->r1 = S32(0X43C8 << 16);
    // 0x801E173C: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
    // 0x801E1740: lui         $at, 0x4100
    ctx->r1 = S32(0X4100 << 16);
    // 0x801E1744: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x801E1748: mul.s       $f18, $f0, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f18.fl = MUL_S(ctx->f0.fl, ctx->f16.fl);
    // 0x801E174C: div.s       $f6, $f18, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = DIV_S(ctx->f18.fl, ctx->f4.fl);
    // 0x801E1750: sub.s       $f8, $f2, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = ctx->f2.fl - ctx->f6.fl;
    // 0x801E1754: b           L_801E17F4
    // 0x801E1758: swc1        $f8, 0x23C($sp)
    MEM_W(0X23C, ctx->r29) = ctx->f8.u32l;
        goto L_801E17F4;
    // 0x801E1758: swc1        $f8, 0x23C($sp)
    MEM_W(0X23C, ctx->r29) = ctx->f8.u32l;
L_801E175C:
    // 0x801E175C: lui         $v1, 0x8022
    ctx->r3 = S32(0X8022 << 16);
    // 0x801E1760: addiu       $v1, $v1, 0x61E0
    ctx->r3 = ADD32(ctx->r3, 0X61E0);
    // 0x801E1764: lw          $t8, 0x0($v1)
    ctx->r24 = MEM_W(ctx->r3, 0X0);
    // 0x801E1768: addiu       $t1, $zero, 0x7
    ctx->r9 = ADD32(0, 0X7);
    // 0x801E176C: addiu       $t9, $t8, 0x1
    ctx->r25 = ADD32(ctx->r24, 0X1);
    // 0x801E1770: slti        $at, $t9, 0xB
    ctx->r1 = SIGNED(ctx->r25) < 0XB ? 1 : 0;
    // 0x801E1774: bne         $at, $zero, L_801E17F4
    if (ctx->r1 != 0) {
        // 0x801E1778: sw          $t9, 0x0($v1)
        MEM_W(0X0, ctx->r3) = ctx->r25;
            goto L_801E17F4;
    }
    // 0x801E1778: sw          $t9, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r25;
    // 0x801E177C: sw          $t1, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r9;
    // 0x801E1780: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E1784: sw          $zero, 0x61E8($at)
    MEM_W(0X61E8, ctx->r1) = 0;
    // 0x801E1788: b           L_801E17F4
    // 0x801E178C: sw          $zero, 0x0($v1)
    MEM_W(0X0, ctx->r3) = 0;
        goto L_801E17F4;
    // 0x801E178C: sw          $zero, 0x0($v1)
    MEM_W(0X0, ctx->r3) = 0;
L_801E1790:
    // 0x801E1790: lui         $v1, 0x8022
    ctx->r3 = S32(0X8022 << 16);
    // 0x801E1794: addiu       $v1, $v1, 0x61E0
    ctx->r3 = ADD32(ctx->r3, 0X61E0);
    // 0x801E1798: lw          $v0, 0x0($v1)
    ctx->r2 = MEM_W(ctx->r3, 0X0);
    // 0x801E179C: addiu       $t2, $zero, 0x1E
    ctx->r10 = ADD32(0, 0X1E);
    // 0x801E17A0: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E17A4: subu        $t3, $t2, $v0
    ctx->r11 = SUB32(ctx->r10, ctx->r2);
    // 0x801E17A8: mtc1        $t3, $f10
    ctx->f10.u32l = ctx->r11;
    // 0x801E17AC: lwc1        $f2, 0x62E0($at)
    ctx->f2.u32l = MEM_W(ctx->r1, 0X62E0);
    // 0x801E17B0: lui         $at, 0x41F0
    ctx->r1 = S32(0X41F0 << 16);
    // 0x801E17B4: cvt.s.w     $f16, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    ctx->f16.fl = CVT_S_W(ctx->f10.u32l);
    // 0x801E17B8: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x801E17BC: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E17C0: addiu       $t4, $v0, 0x1
    ctx->r12 = ADD32(ctx->r2, 0X1);
    // 0x801E17C4: addiu       $t6, $zero, 0x5
    ctx->r14 = ADD32(0, 0X5);
    // 0x801E17C8: mul.s       $f18, $f16, $f2
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f18.fl = MUL_S(ctx->f16.fl, ctx->f2.fl);
    // 0x801E17CC: div.s       $f6, $f18, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = DIV_S(ctx->f18.fl, ctx->f4.fl);
    // 0x801E17D0: swc1        $f6, 0x61CC($at)
    MEM_W(0X61CC, ctx->r1) = ctx->f6.u32l;
    // 0x801E17D4: slti        $at, $t4, 0x1F
    ctx->r1 = SIGNED(ctx->r12) < 0X1F ? 1 : 0;
    // 0x801E17D8: bne         $at, $zero, L_801E17F4
    if (ctx->r1 != 0) {
        // 0x801E17DC: sw          $t4, 0x0($v1)
        MEM_W(0X0, ctx->r3) = ctx->r12;
            goto L_801E17F4;
    }
    // 0x801E17DC: sw          $t4, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r12;
    // 0x801E17E0: mtc1        $zero, $f8
    ctx->f8.u32l = 0;
    // 0x801E17E4: sw          $zero, 0x0($v1)
    MEM_W(0X0, ctx->r3) = 0;
    // 0x801E17E8: sw          $t6, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r14;
    // 0x801E17EC: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E17F0: swc1        $f8, 0x61CC($at)
    MEM_W(0X61CC, ctx->r1) = ctx->f8.u32l;
L_801E17F4:
    // 0x801E17F4: lui         $v0, 0x8022
    ctx->r2 = S32(0X8022 << 16);
    // 0x801E17F8: lw          $v0, 0x61C4($v0)
    ctx->r2 = MEM_W(ctx->r2, 0X61C4);
    // 0x801E17FC: lui         $a0, 0x8023
    ctx->r4 = S32(0X8023 << 16);
    // 0x801E1800: addiu       $a0, $a0, -0x7820
    ctx->r4 = ADD32(ctx->r4, -0X7820);
    // 0x801E1804: mtc1        $zero, $f20
    ctx->f20.u32l = 0;
    // 0x801E1808: addiu       $t7, $v0, -0x3
    ctx->r15 = ADD32(ctx->r2, -0X3);
    // 0x801E180C: bgez        $t7, L_801E181C
    if (SIGNED(ctx->r15) >= 0) {
        // 0x801E1810: sw          $t7, 0x0($a0)
        MEM_W(0X0, ctx->r4) = ctx->r15;
            goto L_801E181C;
    }
    // 0x801E1810: sw          $t7, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r15;
    // 0x801E1814: addiu       $t8, $t7, 0x10
    ctx->r24 = ADD32(ctx->r15, 0X10);
    // 0x801E1818: sw          $t8, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r24;
L_801E181C:
    // 0x801E181C: lui         $a0, 0x8023
    ctx->r4 = S32(0X8023 << 16);
    // 0x801E1820: addiu       $t9, $v0, 0x3
    ctx->r25 = ADD32(ctx->r2, 0X3);
    // 0x801E1824: addiu       $a0, $a0, -0x781C
    ctx->r4 = ADD32(ctx->r4, -0X781C);
    // 0x801E1828: slti        $at, $t9, 0x10
    ctx->r1 = SIGNED(ctx->r25) < 0X10 ? 1 : 0;
    // 0x801E182C: bne         $at, $zero, L_801E183C
    if (ctx->r1 != 0) {
        // 0x801E1830: sw          $t9, 0x0($a0)
        MEM_W(0X0, ctx->r4) = ctx->r25;
            goto L_801E183C;
    }
    // 0x801E1830: sw          $t9, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r25;
    // 0x801E1834: addiu       $t0, $t9, -0x10
    ctx->r8 = ADD32(ctx->r25, -0X10);
    // 0x801E1838: sw          $t0, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r8;
L_801E183C:
    // 0x801E183C: lui         $s4, 0x8023
    ctx->r20 = S32(0X8023 << 16);
    // 0x801E1840: lui         $s2, 0x8023
    ctx->r18 = S32(0X8023 << 16);
    // 0x801E1844: lui         $s3, 0x8023
    ctx->r19 = S32(0X8023 << 16);
    // 0x801E1848: addiu       $s3, $s3, -0x7758
    ctx->r19 = ADD32(ctx->r19, -0X7758);
    // 0x801E184C: addiu       $s2, $s2, -0x77D8
    ctx->r18 = ADD32(ctx->r18, -0X77D8);
    // 0x801E1850: addiu       $s4, $s4, -0x7798
    ctx->r20 = ADD32(ctx->r20, -0X7798);
    // 0x801E1854: or          $s1, $zero, $zero
    ctx->r17 = 0 | 0;
    // 0x801E1858: or          $s5, $zero, $zero
    ctx->r21 = 0 | 0;
L_801E185C:
    // 0x801E185C: mtc1        $s1, $f10
    ctx->f10.u32l = ctx->r17;
    // 0x801E1860: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E1864: lwc1        $f18, 0x62E4($at)
    ctx->f18.u32l = MEM_W(ctx->r1, 0X62E4);
    // 0x801E1868: cvt.s.w     $f16, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    ctx->f16.fl = CVT_S_W(ctx->f10.u32l);
    // 0x801E186C: lui         $at, 0x4180
    ctx->r1 = S32(0X4180 << 16);
    // 0x801E1870: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x801E1874: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E1878: lwc1        $f10, 0x61D0($at)
    ctx->f10.u32l = MEM_W(ctx->r1, 0X61D0);
    // 0x801E187C: lui         $at, 0xC407
    ctx->r1 = S32(0XC407 << 16);
    // 0x801E1880: mul.s       $f4, $f16, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f4.fl = MUL_S(ctx->f16.fl, ctx->f18.fl);
    // 0x801E1884: mtc1        $at, $f18
    ctx->f18.u32l = ctx->r1;
    // 0x801E1888: mfc1        $a2, $f20
    ctx->r6 = (int32_t)ctx->f20.u32l;
    // 0x801E188C: lui         $a3, 0xBE4C
    ctx->r7 = S32(0XBE4C << 16);
    // 0x801E1890: ori         $a3, $a3, 0xCCCD
    ctx->r7 = ctx->r7 | 0XCCCD;
    // 0x801E1894: addiu       $a0, $sp, 0x1F0
    ctx->r4 = ADD32(ctx->r29, 0X1F0);
    // 0x801E1898: addiu       $a1, $sp, 0x170
    ctx->r5 = ADD32(ctx->r29, 0X170);
    // 0x801E189C: div.s       $f8, $f4, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = DIV_S(ctx->f4.fl, ctx->f6.fl);
    // 0x801E18A0: swc1        $f20, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->f20.u32l;
    // 0x801E18A4: swc1        $f20, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->f20.u32l;
    // 0x801E18A8: or          $s0, $zero, $zero
    ctx->r16 = 0 | 0;
    // 0x801E18AC: swc1        $f18, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->f18.u32l;
    // 0x801E18B0: sub.s       $f16, $f10, $f8
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f16.fl = ctx->f10.fl - ctx->f8.fl;
    // 0x801E18B4: jal         0x80049A94
    // 0x801E18B8: swc1        $f16, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f16.u32l;
    func_80049A94(rdram, ctx);
        goto after_3;
    // 0x801E18B8: swc1        $f16, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f16.u32l;
    after_3:
    // 0x801E18BC: lui         $t1, 0x8022
    ctx->r9 = S32(0X8022 << 16);
    // 0x801E18C0: lw          $t1, 0x61C8($t1)
    ctx->r9 = MEM_W(ctx->r9, 0X61C8);
    // 0x801E18C4: addiu       $at, $zero, 0x4
    ctx->r1 = ADD32(0, 0X4);
    // 0x801E18C8: lui         $t2, 0x8022
    ctx->r10 = S32(0X8022 << 16);
    // 0x801E18CC: bne         $t1, $at, L_801E1918
    if (ctx->r9 != ctx->r1) {
        // 0x801E18D0: addiu       $a0, $sp, 0x1F0
        ctx->r4 = ADD32(ctx->r29, 0X1F0);
            goto L_801E1918;
    }
    // 0x801E18D0: addiu       $a0, $sp, 0x1F0
    ctx->r4 = ADD32(ctx->r29, 0X1F0);
    // 0x801E18D4: lw          $t2, 0x61C4($t2)
    ctx->r10 = MEM_W(ctx->r10, 0X61C4);
    // 0x801E18D8: addiu       $a1, $sp, 0x130
    ctx->r5 = ADD32(ctx->r29, 0X130);
    // 0x801E18DC: lw          $a2, 0x238($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X238);
    // 0x801E18E0: bne         $s1, $t2, L_801E1918
    if (ctx->r17 != ctx->r10) {
        // 0x801E18E4: lui         $a3, 0x3FE2
        ctx->r7 = S32(0X3FE2 << 16);
            goto L_801E1918;
    }
    // 0x801E18E4: lui         $a3, 0x3FE2
    ctx->r7 = S32(0X3FE2 << 16);
    // 0x801E18E8: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E18EC: lwc1        $f4, 0x62E8($at)
    ctx->f4.u32l = MEM_W(ctx->r1, 0X62E8);
    // 0x801E18F0: lwc1        $f6, 0x23C($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X23C);
    // 0x801E18F4: addiu       $a0, $sp, 0x1F0
    ctx->r4 = ADD32(ctx->r29, 0X1F0);
    // 0x801E18F8: ori         $a3, $a3, 0xA975
    ctx->r7 = ctx->r7 | 0XA975;
    // 0x801E18FC: swc1        $f20, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->f20.u32l;
    // 0x801E1900: swc1        $f20, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->f20.u32l;
    // 0x801E1904: swc1        $f4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f4.u32l;
    // 0x801E1908: jal         0x80049A94
    // 0x801E190C: swc1        $f6, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->f6.u32l;
    func_80049A94(rdram, ctx);
        goto after_4;
    // 0x801E190C: swc1        $f6, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->f6.u32l;
    after_4:
    // 0x801E1910: b           L_801E1950
    // 0x801E1914: addiu       $a0, $sp, 0x170
    ctx->r4 = ADD32(ctx->r29, 0X170);
        goto L_801E1950;
    // 0x801E1914: addiu       $a0, $sp, 0x170
    ctx->r4 = ADD32(ctx->r29, 0X170);
L_801E1918:
    // 0x801E1918: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E191C: lwc1        $f10, 0x62EC($at)
    ctx->f10.u32l = MEM_W(ctx->r1, 0X62EC);
    // 0x801E1920: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E1924: lwc1        $f8, 0x61CC($at)
    ctx->f8.u32l = MEM_W(ctx->r1, 0X61CC);
    // 0x801E1928: mfc1        $a2, $f20
    ctx->r6 = (int32_t)ctx->f20.u32l;
    // 0x801E192C: lui         $a3, 0x3FE2
    ctx->r7 = S32(0X3FE2 << 16);
    // 0x801E1930: ori         $a3, $a3, 0xA975
    ctx->r7 = ctx->r7 | 0XA975;
    // 0x801E1934: addiu       $a1, $sp, 0x130
    ctx->r5 = ADD32(ctx->r29, 0X130);
    // 0x801E1938: swc1        $f20, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->f20.u32l;
    // 0x801E193C: swc1        $f20, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->f20.u32l;
    // 0x801E1940: swc1        $f10, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f10.u32l;
    // 0x801E1944: jal         0x80049A94
    // 0x801E1948: swc1        $f8, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->f8.u32l;
    func_80049A94(rdram, ctx);
        goto after_5;
    // 0x801E1948: swc1        $f8, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->f8.u32l;
    after_5:
    // 0x801E194C: addiu       $a0, $sp, 0x170
    ctx->r4 = ADD32(ctx->r29, 0X170);
L_801E1950:
    // 0x801E1950: addiu       $a1, $sp, 0x130
    ctx->r5 = ADD32(ctx->r29, 0X130);
    // 0x801E1954: jal         0x80049EB8
    // 0x801E1958: addiu       $a2, $sp, 0xF0
    ctx->r6 = ADD32(ctx->r29, 0XF0);
    SysUtils_MatrixAffineMultiply(rdram, ctx);
        goto after_6;
    // 0x801E1958: addiu       $a2, $sp, 0xF0
    ctx->r6 = ADD32(ctx->r29, 0XF0);
    after_6:
    // 0x801E195C: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x801E1960: mtc1        $at, $f0
    ctx->f0.u32l = ctx->r1;
    // 0x801E1964: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E1968: lwc1        $f16, 0x62F0($at)
    ctx->f16.u32l = MEM_W(ctx->r1, 0X62F0);
    // 0x801E196C: mfc1        $a1, $f20
    ctx->r5 = (int32_t)ctx->f20.u32l;
    // 0x801E1970: mfc1        $a2, $f20
    ctx->r6 = (int32_t)ctx->f20.u32l;
    // 0x801E1974: mfc1        $a3, $f0
    ctx->r7 = (int32_t)ctx->f0.u32l;
    // 0x801E1978: addiu       $a0, $sp, 0x1B0
    ctx->r4 = ADD32(ctx->r29, 0X1B0);
    // 0x801E197C: swc1        $f20, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f20.u32l;
    // 0x801E1980: swc1        $f20, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->f20.u32l;
    // 0x801E1984: swc1        $f20, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->f20.u32l;
    // 0x801E1988: swc1        $f20, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->f20.u32l;
    // 0x801E198C: swc1        $f20, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->f20.u32l;
    // 0x801E1990: swc1        $f0, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->f0.u32l;
    // 0x801E1994: jal         0x80048A88
    // 0x801E1998: swc1        $f16, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->f16.u32l;
    func_80048A88(rdram, ctx);
        goto after_7;
    // 0x801E1998: swc1        $f16, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->f16.u32l;
    after_7:
    // 0x801E199C: addiu       $a0, $sp, 0x1B0
    ctx->r4 = ADD32(ctx->r29, 0X1B0);
    // 0x801E19A0: jal         0x80047E78
    // 0x801E19A4: addiu       $a1, $sp, 0xB0
    ctx->r5 = ADD32(ctx->r29, 0XB0);
    SysUtils_MtxToMtxF(rdram, ctx);
        goto after_8;
    // 0x801E19A4: addiu       $a1, $sp, 0xB0
    ctx->r5 = ADD32(ctx->r29, 0XB0);
    after_8:
    // 0x801E19A8: addiu       $a0, $sp, 0xF0
    ctx->r4 = ADD32(ctx->r29, 0XF0);
    // 0x801E19AC: addiu       $a1, $sp, 0xB0
    ctx->r5 = ADD32(ctx->r29, 0XB0);
    // 0x801E19B0: jal         0x80049EB8
    // 0x801E19B4: addiu       $a2, $sp, 0x70
    ctx->r6 = ADD32(ctx->r29, 0X70);
    SysUtils_MatrixAffineMultiply(rdram, ctx);
        goto after_9;
    // 0x801E19B4: addiu       $a2, $sp, 0x70
    ctx->r6 = ADD32(ctx->r29, 0X70);
    after_9:
    // 0x801E19B8: lui         $t3, 0x801D
    ctx->r11 = S32(0X801D << 16);
    // 0x801E19BC: lw          $t3, -0x1A08($t3)
    ctx->r11 = MEM_W(ctx->r11, -0X1A08);
    // 0x801E19C0: addiu       $a0, $sp, 0x70
    ctx->r4 = ADD32(ctx->r29, 0X70);
    // 0x801E19C4: addu        $a1, $t3, $s5
    ctx->r5 = ADD32(ctx->r11, ctx->r21);
    // 0x801E19C8: jal         0x80047EE0
    // 0x801E19CC: addiu       $a1, $a1, 0x1380
    ctx->r5 = ADD32(ctx->r5, 0X1380);
    SysUtils_MtxFToMtx(rdram, ctx);
        goto after_10;
    // 0x801E19CC: addiu       $a1, $a1, 0x1380
    ctx->r5 = ADD32(ctx->r5, 0X1380);
    after_10:
    // 0x801E19D0: lui         $t4, 0x801D
    ctx->r12 = S32(0X801D << 16);
    // 0x801E19D4: lw          $t4, -0x19C4($t4)
    ctx->r12 = MEM_W(ctx->r12, -0X19C4);
    // 0x801E19D8: lw          $t5, 0x248($sp)
    ctx->r13 = MEM_W(ctx->r29, 0X248);
    // 0x801E19DC: bnel        $t4, $zero, L_801E1B50
    if (ctx->r12 != 0) {
        // 0x801E19E0: lwc1        $f6, 0x120($sp)
        ctx->f6.u32l = MEM_W(ctx->r29, 0X120);
            goto L_801E1B50;
    }
    goto skip_1;
    // 0x801E19E0: lwc1        $f6, 0x120($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X120);
    skip_1:
    // 0x801E19E4: lwc1        $f0, 0x0($s4)
    ctx->f0.u32l = MEM_W(ctx->r20, 0X0);
    // 0x801E19E8: lwc1        $f18, 0x124($sp)
    ctx->f18.u32l = MEM_W(ctx->r29, 0X124);
    // 0x801E19EC: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x801E19F0: c.lt.s      $f0, $f20
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 20);
    c1cs = ctx->f0.fl < ctx->f20.fl;
    // 0x801E19F4: lui         $t8, 0x8022
    ctx->r24 = S32(0X8022 << 16);
    // 0x801E19F8: bc1fl       L_801E1A1C
    if (!c1cs) {
        // 0x801E19FC: c.le.s      $f20, $f0
        CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 0);
    c1cs = ctx->f20.fl <= ctx->f0.fl;
            goto L_801E1A1C;
    }
    goto skip_2;
    // 0x801E19FC: c.le.s      $f20, $f0
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 0);
    c1cs = ctx->f20.fl <= ctx->f0.fl;
    skip_2:
    // 0x801E1A00: c.le.s      $f20, $f18
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 18);
    c1cs = ctx->f20.fl <= ctx->f18.fl;
    // 0x801E1A04: nop

    // 0x801E1A08: bc1fl       L_801E1A1C
    if (!c1cs) {
        // 0x801E1A0C: c.le.s      $f20, $f0
        CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 0);
    c1cs = ctx->f20.fl <= ctx->f0.fl;
            goto L_801E1A1C;
    }
    goto skip_3;
    // 0x801E1A0C: c.le.s      $f20, $f0
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 0);
    c1cs = ctx->f20.fl <= ctx->f0.fl;
    skip_3:
    // 0x801E1A10: b           L_801E1A3C
    // 0x801E1A14: addiu       $s0, $zero, 0x1
    ctx->r16 = ADD32(0, 0X1);
        goto L_801E1A3C;
    // 0x801E1A14: addiu       $s0, $zero, 0x1
    ctx->r16 = ADD32(0, 0X1);
    // 0x801E1A18: c.le.s      $f20, $f0
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 0);
    c1cs = ctx->f20.fl <= ctx->f0.fl;
L_801E1A1C:
    // 0x801E1A1C: lwc1        $f4, 0x124($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X124);
    // 0x801E1A20: bc1f        L_801E1A3C
    if (!c1cs) {
        // 0x801E1A24: nop
    
            goto L_801E1A3C;
    }
    // 0x801E1A24: nop

    // 0x801E1A28: c.lt.s      $f4, $f20
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 20);
    c1cs = ctx->f4.fl < ctx->f20.fl;
    // 0x801E1A2C: nop

    // 0x801E1A30: bc1f        L_801E1A3C
    if (!c1cs) {
        // 0x801E1A34: nop
    
            goto L_801E1A3C;
    }
    // 0x801E1A34: nop

    // 0x801E1A38: addiu       $s0, $zero, 0x2
    ctx->r16 = ADD32(0, 0X2);
L_801E1A3C:
    // 0x801E1A3C: bne         $t5, $zero, L_801E1AA4
    if (ctx->r13 != 0) {
        // 0x801E1A40: nop
    
            goto L_801E1AA4;
    }
    // 0x801E1A40: nop

    // 0x801E1A44: bne         $s0, $at, L_801E1A70
    if (ctx->r16 != ctx->r1) {
        // 0x801E1A48: lui         $at, 0x8022
        ctx->r1 = S32(0X8022 << 16);
            goto L_801E1A70;
    }
    // 0x801E1A48: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E1A4C: lwc1        $f6, 0x61FC($at)
    ctx->f6.u32l = MEM_W(ctx->r1, 0X61FC);
    // 0x801E1A50: lwc1        $f12, 0x120($sp)
    ctx->f12.u32l = MEM_W(ctx->r29, 0X120);
    // 0x801E1A54: lwc1        $f14, 0x128($sp)
    ctx->f14.u32l = MEM_W(ctx->r29, 0X128);
    // 0x801E1A58: trunc.w.s   $f10, $f6
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    ctx->f10.u32l = TRUNC_W_S(ctx->f6.fl);
    // 0x801E1A5C: mfc1        $a2, $f10
    ctx->r6 = (int32_t)ctx->f10.u32l;
    // 0x801E1A60: jal         0x8004EFB4
    // 0x801E1A64: nop

    func_8004EFB4(rdram, ctx);
        goto after_11;
    // 0x801E1A64: nop

    after_11:
    // 0x801E1A68: b           L_801E1B50
    // 0x801E1A6C: lwc1        $f6, 0x120($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X120);
        goto L_801E1B50;
    // 0x801E1A6C: lwc1        $f6, 0x120($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X120);
L_801E1A70:
    // 0x801E1A70: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x801E1A74: bne         $s0, $at, L_801E1B4C
    if (ctx->r16 != ctx->r1) {
        // 0x801E1A78: lui         $at, 0x8022
        ctx->r1 = S32(0X8022 << 16);
            goto L_801E1B4C;
    }
    // 0x801E1A78: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E1A7C: lwc1        $f8, 0x61FC($at)
    ctx->f8.u32l = MEM_W(ctx->r1, 0X61FC);
    // 0x801E1A80: lwc1        $f12, 0x120($sp)
    ctx->f12.u32l = MEM_W(ctx->r29, 0X120);
    // 0x801E1A84: lwc1        $f14, 0x128($sp)
    ctx->f14.u32l = MEM_W(ctx->r29, 0X128);
    // 0x801E1A88: sub.s       $f16, $f20, $f8
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f16.fl = ctx->f20.fl - ctx->f8.fl;
    // 0x801E1A8C: trunc.w.s   $f18, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    ctx->f18.u32l = TRUNC_W_S(ctx->f16.fl);
    // 0x801E1A90: mfc1        $a2, $f18
    ctx->r6 = (int32_t)ctx->f18.u32l;
    // 0x801E1A94: jal         0x8004EFB4
    // 0x801E1A98: nop

    func_8004EFB4(rdram, ctx);
        goto after_12;
    // 0x801E1A98: nop

    after_12:
    // 0x801E1A9C: b           L_801E1B50
    // 0x801E1AA0: lwc1        $f6, 0x120($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X120);
        goto L_801E1B50;
    // 0x801E1AA0: lwc1        $f6, 0x120($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X120);
L_801E1AA4:
    // 0x801E1AA4: lw          $t8, 0x61C4($t8)
    ctx->r24 = MEM_W(ctx->r24, 0X61C4);
    // 0x801E1AA8: lwc1        $f4, 0x124($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X124);
    // 0x801E1AAC: lwc1        $f6, 0x120($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X120);
    // 0x801E1AB0: bne         $s1, $t8, L_801E1ADC
    if (ctx->r17 != ctx->r24) {
        // 0x801E1AB4: addiu       $at, $zero, 0x1
        ctx->r1 = ADD32(0, 0X1);
            goto L_801E1ADC;
    }
    // 0x801E1AB4: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x801E1AB8: c.lt.s      $f4, $f20
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 20);
    c1cs = ctx->f4.fl < ctx->f20.fl;
    // 0x801E1ABC: lwc1        $f12, 0x120($sp)
    ctx->f12.u32l = MEM_W(ctx->r29, 0X120);
    // 0x801E1AC0: lwc1        $f14, 0x128($sp)
    ctx->f14.u32l = MEM_W(ctx->r29, 0X128);
    // 0x801E1AC4: bc1fl       L_801E1B50
    if (!c1cs) {
        // 0x801E1AC8: lwc1        $f6, 0x120($sp)
        ctx->f6.u32l = MEM_W(ctx->r29, 0X120);
            goto L_801E1B50;
    }
    goto skip_4;
    // 0x801E1AC8: lwc1        $f6, 0x120($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X120);
    skip_4:
    // 0x801E1ACC: jal         0x8004EFB4
    // 0x801E1AD0: addiu       $a2, $zero, -0x32
    ctx->r6 = ADD32(0, -0X32);
    func_8004EFB4(rdram, ctx);
        goto after_13;
    // 0x801E1AD0: addiu       $a2, $zero, -0x32
    ctx->r6 = ADD32(0, -0X32);
    after_13:
    // 0x801E1AD4: b           L_801E1B50
    // 0x801E1AD8: lwc1        $f6, 0x120($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X120);
        goto L_801E1B50;
    // 0x801E1AD8: lwc1        $f6, 0x120($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X120);
L_801E1ADC:
    // 0x801E1ADC: c.le.s      $f20, $f6
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 6);
    c1cs = ctx->f20.fl <= ctx->f6.fl;
    // 0x801E1AE0: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    // 0x801E1AE4: bc1f        L_801E1AF4
    if (!c1cs) {
        // 0x801E1AE8: nop
    
            goto L_801E1AF4;
    }
    // 0x801E1AE8: nop

    // 0x801E1AEC: b           L_801E1AF4
    // 0x801E1AF0: addiu       $a3, $zero, 0x1
    ctx->r7 = ADD32(0, 0X1);
        goto L_801E1AF4;
    // 0x801E1AF0: addiu       $a3, $zero, 0x1
    ctx->r7 = ADD32(0, 0X1);
L_801E1AF4:
    // 0x801E1AF4: bne         $s0, $at, L_801E1B20
    if (ctx->r16 != ctx->r1) {
        // 0x801E1AF8: lui         $at, 0x8022
        ctx->r1 = S32(0X8022 << 16);
            goto L_801E1B20;
    }
    // 0x801E1AF8: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E1AFC: lwc1        $f10, 0x61FC($at)
    ctx->f10.u32l = MEM_W(ctx->r1, 0X61FC);
    // 0x801E1B00: lwc1        $f12, 0x0($s2)
    ctx->f12.u32l = MEM_W(ctx->r18, 0X0);
    // 0x801E1B04: lwc1        $f14, 0x0($s3)
    ctx->f14.u32l = MEM_W(ctx->r19, 0X0);
    // 0x801E1B08: trunc.w.s   $f8, $f10
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    ctx->f8.u32l = TRUNC_W_S(ctx->f10.fl);
    // 0x801E1B0C: mfc1        $a2, $f8
    ctx->r6 = (int32_t)ctx->f8.u32l;
    // 0x801E1B10: jal         0x8004F1EC
    // 0x801E1B14: nop

    func_8004F1EC(rdram, ctx);
        goto after_14;
    // 0x801E1B14: nop

    after_14:
    // 0x801E1B18: b           L_801E1B50
    // 0x801E1B1C: lwc1        $f6, 0x120($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X120);
        goto L_801E1B50;
    // 0x801E1B1C: lwc1        $f6, 0x120($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X120);
L_801E1B20:
    // 0x801E1B20: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x801E1B24: bne         $s0, $at, L_801E1B4C
    if (ctx->r16 != ctx->r1) {
        // 0x801E1B28: lui         $at, 0x8022
        ctx->r1 = S32(0X8022 << 16);
            goto L_801E1B4C;
    }
    // 0x801E1B28: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E1B2C: lwc1        $f16, 0x61FC($at)
    ctx->f16.u32l = MEM_W(ctx->r1, 0X61FC);
    // 0x801E1B30: lwc1        $f12, 0x0($s2)
    ctx->f12.u32l = MEM_W(ctx->r18, 0X0);
    // 0x801E1B34: lwc1        $f14, 0x0($s3)
    ctx->f14.u32l = MEM_W(ctx->r19, 0X0);
    // 0x801E1B38: sub.s       $f18, $f20, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f18.fl = ctx->f20.fl - ctx->f16.fl;
    // 0x801E1B3C: trunc.w.s   $f4, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    ctx->f4.u32l = TRUNC_W_S(ctx->f18.fl);
    // 0x801E1B40: mfc1        $a2, $f4
    ctx->r6 = (int32_t)ctx->f4.u32l;
    // 0x801E1B44: jal         0x8004F1EC
    // 0x801E1B48: nop

    func_8004F1EC(rdram, ctx);
        goto after_15;
    // 0x801E1B48: nop

    after_15:
L_801E1B4C:
    // 0x801E1B4C: lwc1        $f6, 0x120($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X120);
L_801E1B50:
    // 0x801E1B50: lwc1        $f10, 0x124($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0X124);
    // 0x801E1B54: lwc1        $f8, 0x128($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X128);
    // 0x801E1B58: addiu       $s1, $s1, 0x1
    ctx->r17 = ADD32(ctx->r17, 0X1);
    // 0x801E1B5C: addiu       $at, $zero, 0x10
    ctx->r1 = ADD32(0, 0X10);
    // 0x801E1B60: addiu       $s5, $s5, 0x40
    ctx->r21 = ADD32(ctx->r21, 0X40);
    // 0x801E1B64: addiu       $s4, $s4, 0x4
    ctx->r20 = ADD32(ctx->r20, 0X4);
    // 0x801E1B68: addiu       $s2, $s2, 0x4
    ctx->r18 = ADD32(ctx->r18, 0X4);
    // 0x801E1B6C: addiu       $s3, $s3, 0x4
    ctx->r19 = ADD32(ctx->r19, 0X4);
    // 0x801E1B70: swc1        $f6, -0x4($s2)
    MEM_W(-0X4, ctx->r18) = ctx->f6.u32l;
    // 0x801E1B74: swc1        $f10, -0x4($s4)
    MEM_W(-0X4, ctx->r20) = ctx->f10.u32l;
    // 0x801E1B78: bne         $s1, $at, L_801E185C
    if (ctx->r17 != ctx->r1) {
        // 0x801E1B7C: swc1        $f8, -0x4($s3)
        MEM_W(-0X4, ctx->r19) = ctx->f8.u32l;
            goto L_801E185C;
    }
    // 0x801E1B7C: swc1        $f8, -0x4($s3)
    MEM_W(-0X4, ctx->r19) = ctx->f8.u32l;
    // 0x801E1B80: lw          $ra, 0x54($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X54);
    // 0x801E1B84: ldc1        $f20, 0x30($sp)
    CHECK_FR(ctx, 20);
    ctx->f20.u64 = LD(ctx->r29, 0X30);
    // 0x801E1B88: lw          $s0, 0x3C($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X3C);
    // 0x801E1B8C: lw          $s1, 0x40($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X40);
    // 0x801E1B90: lw          $s2, 0x44($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X44);
    // 0x801E1B94: lw          $s3, 0x48($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X48);
    // 0x801E1B98: lw          $s4, 0x4C($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X4C);
    // 0x801E1B9C: lw          $s5, 0x50($sp)
    ctx->r21 = MEM_W(ctx->r29, 0X50);
    // 0x801E1BA0: jr          $ra
    // 0x801E1BA4: addiu       $sp, $sp, 0x258
    ctx->r29 = ADD32(ctx->r29, 0X258);
    return;
    // 0x801E1BA4: addiu       $sp, $sp, 0x258
    ctx->r29 = ADD32(ctx->r29, 0X258);
;}
RECOMP_FUNC void func_801E1BA8(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801E1BA8: lui         $a3, 0x8022
    ctx->r7 = S32(0X8022 << 16);
    // 0x801E1BAC: addiu       $a3, $a3, 0x61C4
    ctx->r7 = ADD32(ctx->r7, 0X61C4);
    // 0x801E1BB0: mtc1        $zero, $f0
    ctx->f0.u32l = 0;
    // 0x801E1BB4: sw          $zero, 0x0($a3)
    MEM_W(0X0, ctx->r7) = 0;
    // 0x801E1BB8: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E1BBC: sw          $zero, 0x61C8($at)
    MEM_W(0X61C8, ctx->r1) = 0;
    // 0x801E1BC0: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E1BC4: swc1        $f0, 0x61CC($at)
    MEM_W(0X61CC, ctx->r1) = ctx->f0.u32l;
    // 0x801E1BC8: lui         $t0, 0x8022
    ctx->r8 = S32(0X8022 << 16);
    // 0x801E1BCC: lui         $t1, 0x8022
    ctx->r9 = S32(0X8022 << 16);
    // 0x801E1BD0: addiu       $t1, $t1, 0x61D4
    ctx->r9 = ADD32(ctx->r9, 0X61D4);
    // 0x801E1BD4: addiu       $t0, $t0, 0x61D0
    ctx->r8 = ADD32(ctx->r8, 0X61D0);
    // 0x801E1BD8: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E1BDC: swc1        $f0, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->f0.u32l;
    // 0x801E1BE0: swc1        $f0, 0x0($t1)
    MEM_W(0X0, ctx->r9) = ctx->f0.u32l;
    // 0x801E1BE4: lui         $t2, 0x8022
    ctx->r10 = S32(0X8022 << 16);
    // 0x801E1BE8: sw          $zero, 0x61E0($at)
    MEM_W(0X61E0, ctx->r1) = 0;
    // 0x801E1BEC: addiu       $t2, $t2, 0x61E4
    ctx->r10 = ADD32(ctx->r10, 0X61E4);
    // 0x801E1BF0: sw          $zero, 0x0($t2)
    MEM_W(0X0, ctx->r10) = 0;
    // 0x801E1BF4: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E1BF8: sw          $zero, 0x61E8($at)
    MEM_W(0X61E8, ctx->r1) = 0;
    // 0x801E1BFC: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801E1C00: lui         $v1, 0x8023
    ctx->r3 = S32(0X8023 << 16);
    // 0x801E1C04: sh          $zero, -0x7714($at)
    MEM_H(-0X7714, ctx->r1) = 0;
    // 0x801E1C08: addiu       $v1, $v1, -0x7818
    ctx->r3 = ADD32(ctx->r3, -0X7818);
    // 0x801E1C0C: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_801E1C10:
    // 0x801E1C10: slti        $at, $v0, 0x8
    ctx->r1 = SIGNED(ctx->r2) < 0X8 ? 1 : 0;
    // 0x801E1C14: beq         $at, $zero, L_801E1C24
    if (ctx->r1 == 0) {
        // 0x801E1C18: addiu       $t6, $v0, 0xF
        ctx->r14 = ADD32(ctx->r2, 0XF);
            goto L_801E1C24;
    }
    // 0x801E1C18: addiu       $t6, $v0, 0xF
    ctx->r14 = ADD32(ctx->r2, 0XF);
    // 0x801E1C1C: b           L_801E1C28
    // 0x801E1C20: sw          $v0, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r2;
        goto L_801E1C28;
    // 0x801E1C20: sw          $v0, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r2;
L_801E1C24:
    // 0x801E1C24: sw          $t6, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r14;
L_801E1C28:
    // 0x801E1C28: addiu       $v0, $v0, 0x1
    ctx->r2 = ADD32(ctx->r2, 0X1);
    // 0x801E1C2C: slti        $at, $v0, 0x10
    ctx->r1 = SIGNED(ctx->r2) < 0X10 ? 1 : 0;
    // 0x801E1C30: bne         $at, $zero, L_801E1C10
    if (ctx->r1 != 0) {
        // 0x801E1C34: addiu       $v1, $v1, 0x4
        ctx->r3 = ADD32(ctx->r3, 0X4);
            goto L_801E1C10;
    }
    // 0x801E1C34: addiu       $v1, $v1, 0x4
    ctx->r3 = ADD32(ctx->r3, 0X4);
    // 0x801E1C38: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x801E1C3C: addiu       $v0, $v0, -0x5494
    ctx->r2 = ADD32(ctx->r2, -0X5494);
    // 0x801E1C40: lh          $t7, 0x0($v0)
    ctx->r15 = MEM_H(ctx->r2, 0X0);
    // 0x801E1C44: lui         $v1, 0x8023
    ctx->r3 = S32(0X8023 << 16);
    // 0x801E1C48: addiu       $v1, $v1, -0x7718
    ctx->r3 = ADD32(ctx->r3, -0X7718);
    // 0x801E1C4C: beq         $t7, $zero, L_801E1C70
    if (ctx->r15 == 0) {
        // 0x801E1C50: lui         $a0, 0x801D
        ctx->r4 = S32(0X801D << 16);
            goto L_801E1C70;
    }
    // 0x801E1C50: lui         $a0, 0x801D
    ctx->r4 = S32(0X801D << 16);
    // 0x801E1C54: sh          $zero, 0x0($v0)
    MEM_H(0X0, ctx->r2) = 0;
    // 0x801E1C58: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801E1C5C: sb          $zero, -0x7718($at)
    MEM_B(-0X7718, ctx->r1) = 0;
    // 0x801E1C60: sb          $zero, -0x7717($at)
    MEM_B(-0X7717, ctx->r1) = 0;
    // 0x801E1C64: sb          $zero, -0x7716($at)
    MEM_B(-0X7716, ctx->r1) = 0;
    // 0x801E1C68: b           L_801E1D6C
    // 0x801E1C6C: sb          $zero, -0x7715($at)
    MEM_B(-0X7715, ctx->r1) = 0;
        goto L_801E1D6C;
    // 0x801E1C6C: sb          $zero, -0x7715($at)
    MEM_B(-0X7715, ctx->r1) = 0;
L_801E1C70:
    // 0x801E1C70: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x801E1C74: addiu       $v0, $v0, -0x18FC
    ctx->r2 = ADD32(ctx->r2, -0X18FC);
    // 0x801E1C78: addiu       $a0, $a0, -0x1900
    ctx->r4 = ADD32(ctx->r4, -0X1900);
L_801E1C7C:
    // 0x801E1C7C: lb          $t8, 0x0($a0)
    ctx->r24 = MEM_B(ctx->r4, 0X0);
    // 0x801E1C80: addiu       $a0, $a0, 0x1
    ctx->r4 = ADD32(ctx->r4, 0X1);
    // 0x801E1C84: sltu        $at, $a0, $v0
    ctx->r1 = ctx->r4 < ctx->r2 ? 1 : 0;
    // 0x801E1C88: addiu       $v1, $v1, 0x1
    ctx->r3 = ADD32(ctx->r3, 0X1);
    // 0x801E1C8C: bne         $at, $zero, L_801E1C7C
    if (ctx->r1 != 0) {
        // 0x801E1C90: sb          $t8, -0x1($v1)
        MEM_B(-0X1, ctx->r3) = ctx->r24;
            goto L_801E1C7C;
    }
    // 0x801E1C90: sb          $t8, -0x1($v1)
    MEM_B(-0X1, ctx->r3) = ctx->r24;
    // 0x801E1C94: lui         $v1, 0x8023
    ctx->r3 = S32(0X8023 << 16);
    // 0x801E1C98: addiu       $v1, $v1, -0x7718
    ctx->r3 = ADD32(ctx->r3, -0X7718);
    // 0x801E1C9C: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    // 0x801E1CA0: addiu       $a0, $zero, 0x3
    ctx->r4 = ADD32(0, 0X3);
L_801E1CA4:
    // 0x801E1CA4: lb          $t9, 0x0($v1)
    ctx->r25 = MEM_B(ctx->r3, 0X0);
    // 0x801E1CA8: beql        $t9, $zero, L_801E1CC0
    if (ctx->r25 == 0) {
        // 0x801E1CAC: lw          $a0, 0x0($a3)
        ctx->r4 = MEM_W(ctx->r7, 0X0);
            goto L_801E1CC0;
    }
    goto skip_0;
    // 0x801E1CAC: lw          $a0, 0x0($a3)
    ctx->r4 = MEM_W(ctx->r7, 0X0);
    skip_0:
    // 0x801E1CB0: addiu       $v0, $v0, 0x1
    ctx->r2 = ADD32(ctx->r2, 0X1);
    // 0x801E1CB4: bne         $v0, $a0, L_801E1CA4
    if (ctx->r2 != ctx->r4) {
        // 0x801E1CB8: addiu       $v1, $v1, 0x1
        ctx->r3 = ADD32(ctx->r3, 0X1);
            goto L_801E1CA4;
    }
    // 0x801E1CB8: addiu       $v1, $v1, 0x1
    ctx->r3 = ADD32(ctx->r3, 0X1);
    // 0x801E1CBC: lw          $a0, 0x0($a3)
    ctx->r4 = MEM_W(ctx->r7, 0X0);
L_801E1CC0:
    // 0x801E1CC0: lui         $t3, 0x8023
    ctx->r11 = S32(0X8023 << 16);
    // 0x801E1CC4: addiu       $t3, $t3, -0x7818
    ctx->r11 = ADD32(ctx->r11, -0X7818);
    // 0x801E1CC8: addiu       $v1, $a0, 0x8
    ctx->r3 = ADD32(ctx->r4, 0X8);
    // 0x801E1CCC: sw          $v0, 0x0($t2)
    MEM_W(0X0, ctx->r10) = ctx->r2;
    // 0x801E1CD0: bgez        $v1, L_801E1CE4
    if (SIGNED(ctx->r3) >= 0) {
        // 0x801E1CD4: andi        $t4, $v1, 0xF
        ctx->r12 = ctx->r3 & 0XF;
            goto L_801E1CE4;
    }
    // 0x801E1CD4: andi        $t4, $v1, 0xF
    ctx->r12 = ctx->r3 & 0XF;
    // 0x801E1CD8: beq         $t4, $zero, L_801E1CE4
    if (ctx->r12 == 0) {
        // 0x801E1CDC: nop
    
            goto L_801E1CE4;
    }
    // 0x801E1CDC: nop

    // 0x801E1CE0: addiu       $t4, $t4, -0x10
    ctx->r12 = ADD32(ctx->r12, -0X10);
L_801E1CE4:
    // 0x801E1CE4: addiu       $t6, $t4, 0x1
    ctx->r14 = ADD32(ctx->r12, 0X1);
    // 0x801E1CE8: or          $v1, $t4, $zero
    ctx->r3 = ctx->r12 | 0;
    // 0x801E1CEC: sll         $t5, $t4, 2
    ctx->r13 = S32(ctx->r12 << 2);
    // 0x801E1CF0: addu        $a1, $t3, $t5
    ctx->r5 = ADD32(ctx->r11, ctx->r13);
    // 0x801E1CF4: bgez        $t6, L_801E1D08
    if (SIGNED(ctx->r14) >= 0) {
        // 0x801E1CF8: andi        $t7, $t6, 0xF
        ctx->r15 = ctx->r14 & 0XF;
            goto L_801E1D08;
    }
    // 0x801E1CF8: andi        $t7, $t6, 0xF
    ctx->r15 = ctx->r14 & 0XF;
    // 0x801E1CFC: beq         $t7, $zero, L_801E1D08
    if (ctx->r15 == 0) {
        // 0x801E1D00: nop
    
            goto L_801E1D08;
    }
    // 0x801E1D00: nop

    // 0x801E1D04: addiu       $t7, $t7, -0x10
    ctx->r15 = ADD32(ctx->r15, -0X10);
L_801E1D08:
    // 0x801E1D08: sll         $t8, $t7, 2
    ctx->r24 = S32(ctx->r15 << 2);
    // 0x801E1D0C: addu        $t9, $t3, $t8
    ctx->r25 = ADD32(ctx->r11, ctx->r24);
    // 0x801E1D10: lw          $t4, 0x0($t9)
    ctx->r12 = MEM_W(ctx->r25, 0X0);
    // 0x801E1D14: addiu       $t7, $a0, -0x1
    ctx->r15 = ADD32(ctx->r4, -0X1);
    // 0x801E1D18: or          $a0, $t7, $zero
    ctx->r4 = ctx->r15 | 0;
    // 0x801E1D1C: addiu       $t5, $t4, -0x1
    ctx->r13 = ADD32(ctx->r12, -0X1);
    // 0x801E1D20: bgez        $t5, L_801E1D30
    if (SIGNED(ctx->r13) >= 0) {
        // 0x801E1D24: sw          $t5, 0x0($a1)
        MEM_W(0X0, ctx->r5) = ctx->r13;
            goto L_801E1D30;
    }
    // 0x801E1D24: sw          $t5, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r13;
    // 0x801E1D28: addiu       $t6, $t5, 0x1F
    ctx->r14 = ADD32(ctx->r13, 0X1F);
    // 0x801E1D2C: sw          $t6, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r14;
L_801E1D30:
    // 0x801E1D30: bgez        $t7, L_801E1D40
    if (SIGNED(ctx->r15) >= 0) {
        // 0x801E1D34: sw          $t7, 0x0($a3)
        MEM_W(0X0, ctx->r7) = ctx->r15;
            goto L_801E1D40;
    }
    // 0x801E1D34: sw          $t7, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r15;
    // 0x801E1D38: addiu       $a0, $zero, 0xF
    ctx->r4 = ADD32(0, 0XF);
    // 0x801E1D3C: sw          $a0, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r4;
L_801E1D40:
    // 0x801E1D40: mtc1        $a0, $f4
    ctx->f4.u32l = ctx->r4;
    // 0x801E1D44: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E1D48: lwc1        $f8, 0x62F4($at)
    ctx->f8.u32l = MEM_W(ctx->r1, 0X62F4);
    // 0x801E1D4C: cvt.s.w     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
    // 0x801E1D50: lui         $at, 0x4180
    ctx->r1 = S32(0X4180 << 16);
    // 0x801E1D54: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
    // 0x801E1D58: mul.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = MUL_S(ctx->f6.fl, ctx->f8.fl);
    // 0x801E1D5C: div.s       $f18, $f10, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f18.fl = DIV_S(ctx->f10.fl, ctx->f16.fl);
    // 0x801E1D60: swc1        $f18, 0x0($t1)
    MEM_W(0X0, ctx->r9) = ctx->f18.u32l;
    // 0x801E1D64: lwc1        $f4, 0x0($t1)
    ctx->f4.u32l = MEM_W(ctx->r9, 0X0);
    // 0x801E1D68: swc1        $f4, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->f4.u32l;
L_801E1D6C:
    // 0x801E1D6C: lui         $t0, 0x8022
    ctx->r8 = S32(0X8022 << 16);
    // 0x801E1D70: addiu       $t0, $t0, 0x61F8
    ctx->r8 = ADD32(ctx->r8, 0X61F8);
    // 0x801E1D74: sw          $zero, 0x0($t0)
    MEM_W(0X0, ctx->r8) = 0;
    // 0x801E1D78: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x801E1D7C: lw          $v0, -0x19F8($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X19F8);
    // 0x801E1D80: addiu       $at, $zero, 0x4
    ctx->r1 = ADD32(0, 0X4);
    // 0x801E1D84: lui         $t4, 0x801C
    ctx->r12 = S32(0X801C << 16);
    // 0x801E1D88: beq         $v0, $zero, L_801E1E48
    if (ctx->r2 == 0) {
        // 0x801E1D8C: nop
    
            goto L_801E1E48;
    }
    // 0x801E1D8C: nop

    // 0x801E1D90: beq         $v0, $at, L_801E1DAC
    if (ctx->r2 == ctx->r1) {
        // 0x801E1D94: lui         $v1, 0x801D
        ctx->r3 = S32(0X801D << 16);
            goto L_801E1DAC;
    }
    // 0x801E1D94: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x801E1D98: addiu       $at, $zero, 0xB
    ctx->r1 = ADD32(0, 0XB);
    // 0x801E1D9C: beq         $v0, $at, L_801E1E70
    if (ctx->r2 == ctx->r1) {
        // 0x801E1DA0: lui         $t6, 0x801C
        ctx->r14 = S32(0X801C << 16);
            goto L_801E1E70;
    }
    // 0x801E1DA0: lui         $t6, 0x801C
    ctx->r14 = S32(0X801C << 16);
    // 0x801E1DA4: jr          $ra
    // 0x801E1DA8: nop

    return;
    // 0x801E1DA8: nop

L_801E1DAC:
    // 0x801E1DAC: lw          $v1, -0x4CC8($v1)
    ctx->r3 = MEM_W(ctx->r3, -0X4CC8);
    // 0x801E1DB0: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    // 0x801E1DB4: lui         $a1, 0x801D
    ctx->r5 = S32(0X801D << 16);
    // 0x801E1DB8: bne         $v1, $zero, L_801E1DC8
    if (ctx->r3 != 0) {
        // 0x801E1DBC: sll         $t9, $v1, 4
        ctx->r25 = S32(ctx->r3 << 4);
            goto L_801E1DC8;
    }
    // 0x801E1DBC: sll         $t9, $v1, 4
    ctx->r25 = S32(ctx->r3 << 4);
    // 0x801E1DC0: b           L_801E1DC8
    // 0x801E1DC4: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
        goto L_801E1DC8;
    // 0x801E1DC4: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
L_801E1DC8:
    // 0x801E1DC8: lw          $a1, -0x4CCC($a1)
    ctx->r5 = MEM_W(ctx->r5, -0X4CCC);
    // 0x801E1DCC: lui         $t5, 0x800F
    ctx->r13 = S32(0X800F << 16);
    // 0x801E1DD0: addiu       $t5, $t5, -0x53EC
    ctx->r13 = ADD32(ctx->r13, -0X53EC);
    // 0x801E1DD4: addiu       $a1, $a1, 0x1
    ctx->r5 = ADD32(ctx->r5, 0X1);
    // 0x801E1DD8: slt         $at, $a0, $a1
    ctx->r1 = SIGNED(ctx->r4) < SIGNED(ctx->r5) ? 1 : 0;
    // 0x801E1DDC: beq         $at, $zero, L_801E1E84
    if (ctx->r1 == 0) {
        // 0x801E1DE0: sll         $a0, $a0, 1
        ctx->r4 = S32(ctx->r4 << 1);
            goto L_801E1E84;
    }
    // 0x801E1DE0: sll         $a0, $a0, 1
    ctx->r4 = S32(ctx->r4 << 1);
    // 0x801E1DE4: addu        $t4, $t9, $a0
    ctx->r12 = ADD32(ctx->r25, ctx->r4);
    // 0x801E1DE8: sll         $a3, $a1, 1
    ctx->r7 = S32(ctx->r5 << 1);
    // 0x801E1DEC: lui         $t2, 0x801C
    ctx->r10 = S32(0X801C << 16);
    // 0x801E1DF0: lui         $t1, 0x801C
    ctx->r9 = S32(0X801C << 16);
    // 0x801E1DF4: addiu       $t1, $t1, 0x2660
    ctx->r9 = ADD32(ctx->r9, 0X2660);
    // 0x801E1DF8: addiu       $t2, $t2, 0x2690
    ctx->r10 = ADD32(ctx->r10, 0X2690);
    // 0x801E1DFC: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x801E1E00: addu        $a2, $t4, $t5
    ctx->r6 = ADD32(ctx->r12, ctx->r13);
L_801E1E04:
    // 0x801E1E04: lh          $v0, 0x0($a2)
    ctx->r2 = MEM_H(ctx->r6, 0X0);
    // 0x801E1E08: addiu       $a0, $a0, 0x2
    ctx->r4 = ADD32(ctx->r4, 0X2);
    // 0x801E1E0C: slt         $at, $a0, $a3
    ctx->r1 = SIGNED(ctx->r4) < SIGNED(ctx->r7) ? 1 : 0;
    // 0x801E1E10: sll         $v1, $v0, 2
    ctx->r3 = S32(ctx->r2 << 2);
    // 0x801E1E14: addu        $t6, $t1, $v1
    ctx->r14 = ADD32(ctx->r9, ctx->r3);
    // 0x801E1E18: lw          $t7, 0x0($t6)
    ctx->r15 = MEM_W(ctx->r14, 0X0);
    // 0x801E1E1C: addu        $t8, $t2, $v1
    ctx->r24 = ADD32(ctx->r10, ctx->r3);
    // 0x801E1E20: beql        $a1, $t7, L_801E1E38
    if (ctx->r5 == ctx->r15) {
        // 0x801E1E24: sw          $a1, 0x0($t0)
        MEM_W(0X0, ctx->r8) = ctx->r5;
            goto L_801E1E38;
    }
    goto skip_1;
    // 0x801E1E24: sw          $a1, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r5;
    skip_1:
    // 0x801E1E28: lw          $t9, 0x0($t8)
    ctx->r25 = MEM_W(ctx->r24, 0X0);
    // 0x801E1E2C: beq         $t9, $zero, L_801E1E38
    if (ctx->r25 == 0) {
        // 0x801E1E30: nop
    
            goto L_801E1E38;
    }
    // 0x801E1E30: nop

    // 0x801E1E34: sw          $a1, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r5;
L_801E1E38:
    // 0x801E1E38: bne         $at, $zero, L_801E1E04
    if (ctx->r1 != 0) {
        // 0x801E1E3C: addiu       $a2, $a2, 0x2
        ctx->r6 = ADD32(ctx->r6, 0X2);
            goto L_801E1E04;
    }
    // 0x801E1E3C: addiu       $a2, $a2, 0x2
    ctx->r6 = ADD32(ctx->r6, 0X2);
    // 0x801E1E40: jr          $ra
    // 0x801E1E44: nop

    return;
    // 0x801E1E44: nop

L_801E1E48:
    // 0x801E1E48: lw          $t4, 0x2650($t4)
    ctx->r12 = MEM_W(ctx->r12, 0X2650);
    // 0x801E1E4C: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x801E1E50: lui         $t5, 0x801C
    ctx->r13 = S32(0X801C << 16);
    // 0x801E1E54: beq         $a1, $t4, L_801E1E68
    if (ctx->r5 == ctx->r12) {
        // 0x801E1E58: nop
    
            goto L_801E1E68;
    }
    // 0x801E1E58: nop

    // 0x801E1E5C: lw          $t5, 0x2654($t5)
    ctx->r13 = MEM_W(ctx->r13, 0X2654);
    // 0x801E1E60: beq         $t5, $zero, L_801E1E84
    if (ctx->r13 == 0) {
        // 0x801E1E64: nop
    
            goto L_801E1E84;
    }
    // 0x801E1E64: nop

L_801E1E68:
    // 0x801E1E68: jr          $ra
    // 0x801E1E6C: sw          $a1, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r5;
    return;
    // 0x801E1E6C: sw          $a1, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r5;
L_801E1E70:
    // 0x801E1E70: lw          $t6, 0x2928($t6)
    ctx->r14 = MEM_W(ctx->r14, 0X2928);
    // 0x801E1E74: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x801E1E78: bne         $a1, $t6, L_801E1E84
    if (ctx->r5 != ctx->r14) {
        // 0x801E1E7C: nop
    
            goto L_801E1E84;
    }
    // 0x801E1E7C: nop

    // 0x801E1E80: sw          $a1, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r5;
L_801E1E84:
    // 0x801E1E84: jr          $ra
    // 0x801E1E88: nop

    return;
    // 0x801E1E88: nop

;}
RECOMP_FUNC void func_801E1E8C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801E1E8C: addiu       $sp, $sp, -0x38
    ctx->r29 = ADD32(ctx->r29, -0X38);
    // 0x801E1E90: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x801E1E94: addiu       $v0, $v0, -0x19C4
    ctx->r2 = ADD32(ctx->r2, -0X19C4);
    // 0x801E1E98: lw          $t6, 0x0($v0)
    ctx->r14 = MEM_W(ctx->r2, 0X0);
    // 0x801E1E9C: sw          $ra, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r31;
    // 0x801E1EA0: sw          $s6, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r22;
    // 0x801E1EA4: sw          $s5, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r21;
    // 0x801E1EA8: sw          $s4, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r20;
    // 0x801E1EAC: sw          $s3, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r19;
    // 0x801E1EB0: sw          $s2, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r18;
    // 0x801E1EB4: sw          $s1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r17;
    // 0x801E1EB8: beq         $t6, $zero, L_801E1EC4
    if (ctx->r14 == 0) {
        // 0x801E1EBC: sw          $s0, 0x18($sp)
        MEM_W(0X18, ctx->r29) = ctx->r16;
            goto L_801E1EC4;
    }
    // 0x801E1EBC: sw          $s0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r16;
    // 0x801E1EC0: sw          $zero, 0x0($v0)
    MEM_W(0X0, ctx->r2) = 0;
L_801E1EC4:
    // 0x801E1EC4: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x801E1EC8: jal         0x80093F78
    // 0x801E1ECC: sw          $zero, -0x54D4($at)
    MEM_W(-0X54D4, ctx->r1) = 0;
    func_80093F78(rdram, ctx);
        goto after_0;
    // 0x801E1ECC: sw          $zero, -0x54D4($at)
    MEM_W(-0X54D4, ctx->r1) = 0;
    after_0:
    // 0x801E1ED0: jal         0x8008FB74
    // 0x801E1ED4: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    func_8008FB74(rdram, ctx);
        goto after_1;
    // 0x801E1ED4: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    after_1:
    // 0x801E1ED8: jal         0x801E2058
    // 0x801E1EDC: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    func_801E2058(rdram, ctx);
        goto after_2;
    // 0x801E1EDC: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    after_2:
    // 0x801E1EE0: lui         $t7, 0x102
    ctx->r15 = S32(0X102 << 16);
    // 0x801E1EE4: lui         $t8, 0x8012
    ctx->r24 = S32(0X8012 << 16);
    // 0x801E1EE8: addiu       $t8, $t8, -0x7E0
    ctx->r24 = ADD32(ctx->r24, -0X7E0);
    // 0x801E1EEC: ori         $t7, $t7, 0x40
    ctx->r15 = ctx->r15 | 0X40;
    // 0x801E1EF0: sw          $t7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r15;
    // 0x801E1EF4: sw          $t8, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r24;
    // 0x801E1EF8: lui         $a1, 0x800E
    ctx->r5 = S32(0X800E << 16);
    // 0x801E1EFC: lw          $a1, -0x7E90($a1)
    ctx->r5 = MEM_W(ctx->r5, -0X7E90);
    // 0x801E1F00: jal         0x80094A44
    // 0x801E1F04: addiu       $a0, $v0, 0x8
    ctx->r4 = ADD32(ctx->r2, 0X8);
    func_80094A44(rdram, ctx);
        goto after_3;
    // 0x801E1F04: addiu       $a0, $v0, 0x8
    ctx->r4 = ADD32(ctx->r2, 0X8);
    after_3:
    // 0x801E1F08: jal         0x80090F58
    // 0x801E1F0C: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    Draw_WaterEffects(rdram, ctx);
        goto after_4;
    // 0x801E1F0C: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    after_4:
    // 0x801E1F10: jal         0x801E229C
    // 0x801E1F14: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    func_801E229C(rdram, ctx);
        goto after_5;
    // 0x801E1F14: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    after_5:
    // 0x801E1F18: lui         $t9, 0x800E
    ctx->r25 = S32(0X800E << 16);
    // 0x801E1F1C: lw          $t9, -0x54DC($t9)
    ctx->r25 = MEM_W(ctx->r25, -0X54DC);
    // 0x801E1F20: addiu       $at, $zero, 0x64
    ctx->r1 = ADD32(0, 0X64);
    // 0x801E1F24: sw          $v0, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r2;
    // 0x801E1F28: bne         $t9, $at, L_801E1F40
    if (ctx->r25 != ctx->r1) {
        // 0x801E1F2C: lui         $t0, 0x8023
        ctx->r8 = S32(0X8023 << 16);
            goto L_801E1F40;
    }
    // 0x801E1F2C: lui         $t0, 0x8023
    ctx->r8 = S32(0X8023 << 16);
    // 0x801E1F30: jal         0x801E2530
    // 0x801E1F34: nop

    func_801E2530(rdram, ctx);
        goto after_6;
    // 0x801E1F34: nop

    after_6:
    // 0x801E1F38: b           L_801E2030
    // 0x801E1F3C: lw          $ra, 0x34($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X34);
        goto L_801E2030;
    // 0x801E1F3C: lw          $ra, 0x34($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X34);
L_801E1F40:
    // 0x801E1F40: lh          $t0, -0x75EA($t0)
    ctx->r8 = MEM_H(ctx->r8, -0X75EA);
    // 0x801E1F44: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x801E1F48: lui         $t1, 0x801D
    ctx->r9 = S32(0X801D << 16);
    // 0x801E1F4C: bnel        $t0, $at, L_801E2030
    if (ctx->r8 != ctx->r1) {
        // 0x801E1F50: lw          $ra, 0x34($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X34);
            goto L_801E2030;
    }
    goto skip_0;
    // 0x801E1F50: lw          $ra, 0x34($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X34);
    skip_0:
    // 0x801E1F54: lw          $t1, -0x19F8($t1)
    ctx->r9 = MEM_W(ctx->r9, -0X19F8);
    // 0x801E1F58: addiu       $at, $zero, 0x4
    ctx->r1 = ADD32(0, 0X4);
    // 0x801E1F5C: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x801E1F60: bne         $t1, $at, L_801E2024
    if (ctx->r9 != ctx->r1) {
        // 0x801E1F64: nop
    
            goto L_801E2024;
    }
    // 0x801E1F64: nop

    // 0x801E1F68: lw          $v1, -0x4CCC($v1)
    ctx->r3 = MEM_W(ctx->r3, -0X4CCC);
    // 0x801E1F6C: or          $s0, $zero, $zero
    ctx->r16 = 0 | 0;
    // 0x801E1F70: or          $s1, $zero, $zero
    ctx->r17 = 0 | 0;
    // 0x801E1F74: addiu       $v1, $v1, 0x1
    ctx->r3 = ADD32(ctx->r3, 0X1);
    // 0x801E1F78: blez        $v1, L_801E2024
    if (SIGNED(ctx->r3) <= 0) {
        // 0x801E1F7C: lui         $s6, 0x800E
        ctx->r22 = S32(0X800E << 16);
            goto L_801E2024;
    }
    // 0x801E1F7C: lui         $s6, 0x800E
    ctx->r22 = S32(0X800E << 16);
    // 0x801E1F80: lui         $s5, 0x801C
    ctx->r21 = S32(0X801C << 16);
    // 0x801E1F84: lui         $s4, 0x801C
    ctx->r20 = S32(0X801C << 16);
    // 0x801E1F88: lui         $s3, 0x801D
    ctx->r19 = S32(0X801D << 16);
    // 0x801E1F8C: lui         $s2, 0x800F
    ctx->r18 = S32(0X800F << 16);
    // 0x801E1F90: addiu       $s2, $s2, -0x53EC
    ctx->r18 = ADD32(ctx->r18, -0X53EC);
    // 0x801E1F94: addiu       $s3, $s3, -0x4CC8
    ctx->r19 = ADD32(ctx->r19, -0X4CC8);
    // 0x801E1F98: addiu       $s4, $s4, 0x2660
    ctx->r20 = ADD32(ctx->r20, 0X2660);
    // 0x801E1F9C: addiu       $s5, $s5, 0x2690
    ctx->r21 = ADD32(ctx->r21, 0X2690);
    // 0x801E1FA0: addiu       $s6, $s6, -0x5498
    ctx->r22 = ADD32(ctx->r22, -0X5498);
L_801E1FA4:
    // 0x801E1FA4: lw          $t2, 0x0($s3)
    ctx->r10 = MEM_W(ctx->r19, 0X0);
    // 0x801E1FA8: sll         $t3, $t2, 4
    ctx->r11 = S32(ctx->r10 << 4);
    // 0x801E1FAC: addu        $t4, $s2, $t3
    ctx->r12 = ADD32(ctx->r18, ctx->r11);
    // 0x801E1FB0: addu        $t5, $t4, $s1
    ctx->r13 = ADD32(ctx->r12, ctx->r17);
    // 0x801E1FB4: lh          $a0, 0x0($t5)
    ctx->r4 = MEM_H(ctx->r13, 0X0);
    // 0x801E1FB8: sll         $v0, $a0, 2
    ctx->r2 = S32(ctx->r4 << 2);
    // 0x801E1FBC: addu        $t6, $s4, $v0
    ctx->r14 = ADD32(ctx->r20, ctx->r2);
    // 0x801E1FC0: lw          $t7, 0x0($t6)
    ctx->r15 = MEM_W(ctx->r14, 0X0);
    // 0x801E1FC4: addu        $t8, $s5, $v0
    ctx->r24 = ADD32(ctx->r21, ctx->r2);
    // 0x801E1FC8: bnel        $t7, $zero, L_801E1FE0
    if (ctx->r15 != 0) {
        // 0x801E1FCC: lh          $t0, 0x0($s6)
        ctx->r8 = MEM_H(ctx->r22, 0X0);
            goto L_801E1FE0;
    }
    goto skip_1;
    // 0x801E1FCC: lh          $t0, 0x0($s6)
    ctx->r8 = MEM_H(ctx->r22, 0X0);
    skip_1:
    // 0x801E1FD0: lw          $t9, 0x0($t8)
    ctx->r25 = MEM_W(ctx->r24, 0X0);
    // 0x801E1FD4: beql        $t9, $zero, L_801E2018
    if (ctx->r25 == 0) {
        // 0x801E1FD8: addiu       $s0, $s0, 0x1
        ctx->r16 = ADD32(ctx->r16, 0X1);
            goto L_801E2018;
    }
    goto skip_2;
    // 0x801E1FD8: addiu       $s0, $s0, 0x1
    ctx->r16 = ADD32(ctx->r16, 0X1);
    skip_2:
    // 0x801E1FDC: lh          $t0, 0x0($s6)
    ctx->r8 = MEM_H(ctx->r22, 0X0);
L_801E1FE0:
    // 0x801E1FE0: beq         $t0, $zero, L_801E2000
    if (ctx->r8 == 0) {
        // 0x801E1FE4: nop
    
            goto L_801E2000;
    }
    // 0x801E1FE4: nop

    // 0x801E1FE8: jal         0x8007C204
    // 0x801E1FEC: nop

    func_8007C204(rdram, ctx);
        goto after_7;
    // 0x801E1FEC: nop

    after_7:
    // 0x801E1FF0: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x801E1FF4: lw          $v1, -0x4CCC($v1)
    ctx->r3 = MEM_W(ctx->r3, -0X4CCC);
    // 0x801E1FF8: b           L_801E2014
    // 0x801E1FFC: addiu       $v1, $v1, 0x1
    ctx->r3 = ADD32(ctx->r3, 0X1);
        goto L_801E2014;
    // 0x801E1FFC: addiu       $v1, $v1, 0x1
    ctx->r3 = ADD32(ctx->r3, 0X1);
L_801E2000:
    // 0x801E2000: jal         0x8007BEA4
    // 0x801E2004: nop

    func_8007BEA4(rdram, ctx);
        goto after_8;
    // 0x801E2004: nop

    after_8:
    // 0x801E2008: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x801E200C: lw          $v1, -0x4CCC($v1)
    ctx->r3 = MEM_W(ctx->r3, -0X4CCC);
    // 0x801E2010: addiu       $v1, $v1, 0x1
    ctx->r3 = ADD32(ctx->r3, 0X1);
L_801E2014:
    // 0x801E2014: addiu       $s0, $s0, 0x1
    ctx->r16 = ADD32(ctx->r16, 0X1);
L_801E2018:
    // 0x801E2018: slt         $at, $s0, $v1
    ctx->r1 = SIGNED(ctx->r16) < SIGNED(ctx->r3) ? 1 : 0;
    // 0x801E201C: bne         $at, $zero, L_801E1FA4
    if (ctx->r1 != 0) {
        // 0x801E2020: addiu       $s1, $s1, 0x2
        ctx->r17 = ADD32(ctx->r17, 0X2);
            goto L_801E1FA4;
    }
    // 0x801E2020: addiu       $s1, $s1, 0x2
    ctx->r17 = ADD32(ctx->r17, 0X2);
L_801E2024:
    // 0x801E2024: jal         0x801EC500
    // 0x801E2028: nop

    func_801EC500(rdram, ctx);
        goto after_9;
    // 0x801E2028: nop

    after_9:
    // 0x801E202C: lw          $ra, 0x34($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X34);
L_801E2030:
    // 0x801E2030: lw          $v0, 0x38($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X38);
    // 0x801E2034: lw          $s0, 0x18($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X18);
    // 0x801E2038: lw          $s1, 0x1C($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X1C);
    // 0x801E203C: lw          $s2, 0x20($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X20);
    // 0x801E2040: lw          $s3, 0x24($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X24);
    // 0x801E2044: lw          $s4, 0x28($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X28);
    // 0x801E2048: lw          $s5, 0x2C($sp)
    ctx->r21 = MEM_W(ctx->r29, 0X2C);
    // 0x801E204C: lw          $s6, 0x30($sp)
    ctx->r22 = MEM_W(ctx->r29, 0X30);
    // 0x801E2050: jr          $ra
    // 0x801E2054: addiu       $sp, $sp, 0x38
    ctx->r29 = ADD32(ctx->r29, 0X38);
    return;
    // 0x801E2054: addiu       $sp, $sp, 0x38
    ctx->r29 = ADD32(ctx->r29, 0X38);
;}
RECOMP_FUNC void func_801E2058(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801E2058: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x801E205C: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x801E2060: lui         $a1, 0x800E
    ctx->r5 = S32(0X800E << 16);
    // 0x801E2064: sw          $s0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r16;
    // 0x801E2068: sw          $a0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r4;
    // 0x801E206C: jal         0x800949B8
    // 0x801E2070: lw          $a1, -0x7E90($a1)
    ctx->r5 = MEM_W(ctx->r5, -0X7E90);
    func_800949B8(rdram, ctx);
        goto after_0;
    // 0x801E2070: lw          $a1, -0x7E90($a1)
    ctx->r5 = MEM_W(ctx->r5, -0X7E90);
    after_0:
    // 0x801E2074: addiu       $t6, $v0, 0x8
    ctx->r14 = ADD32(ctx->r2, 0X8);
    // 0x801E2078: sw          $t6, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r14;
    // 0x801E207C: lui         $t7, 0x107
    ctx->r15 = S32(0X107 << 16);
    // 0x801E2080: lui         $s0, 0x600
    ctx->r16 = S32(0X600 << 16);
    // 0x801E2084: addiu       $t7, $t7, -0x940
    ctx->r15 = ADD32(ctx->r15, -0X940);
    // 0x801E2088: sw          $t7, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r15;
    // 0x801E208C: sw          $s0, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r16;
    // 0x801E2090: lui         $t8, 0x8022
    ctx->r24 = S32(0X8022 << 16);
    // 0x801E2094: lw          $t8, 0x61F8($t8)
    ctx->r24 = MEM_W(ctx->r24, 0X61F8);
    // 0x801E2098: beq         $t8, $zero, L_801E20A8
    if (ctx->r24 == 0) {
        // 0x801E209C: nop
    
            goto L_801E20A8;
    }
    // 0x801E209C: nop

    // 0x801E20A0: jal         0x8006DE24
    // 0x801E20A4: addiu       $a0, $sp, 0x20
    ctx->r4 = ADD32(ctx->r29, 0X20);
    func_8006DE24(rdram, ctx);
        goto after_1;
    // 0x801E20A4: addiu       $a0, $sp, 0x20
    ctx->r4 = ADD32(ctx->r29, 0X20);
    after_1:
L_801E20A8:
    // 0x801E20A8: lui         $t0, 0x8023
    ctx->r8 = S32(0X8023 << 16);
    // 0x801E20AC: addiu       $t0, $t0, -0x781C
    ctx->r8 = ADD32(ctx->r8, -0X781C);
    // 0x801E20B0: lui         $t9, 0x8023
    ctx->r25 = S32(0X8023 << 16);
    // 0x801E20B4: lw          $t9, -0x7820($t9)
    ctx->r25 = MEM_W(ctx->r25, -0X7820);
    // 0x801E20B8: lw          $t6, 0x0($t0)
    ctx->r14 = MEM_W(ctx->r8, 0X0);
    // 0x801E20BC: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x801E20C0: lui         $ra, 0xBD00
    ctx->r31 = S32(0XBD00 << 16);
    // 0x801E20C4: slt         $at, $t9, $t6
    ctx->r1 = SIGNED(ctx->r25) < SIGNED(ctx->r14) ? 1 : 0;
    // 0x801E20C8: beq         $at, $zero, L_801E20D8
    if (ctx->r1 == 0) {
        // 0x801E20CC: lui         $t5, 0x8023
        ctx->r13 = S32(0X8023 << 16);
            goto L_801E20D8;
    }
    // 0x801E20CC: lui         $t5, 0x8023
    ctx->r13 = S32(0X8023 << 16);
    // 0x801E20D0: b           L_801E20DC
    // 0x801E20D4: or          $t1, $zero, $zero
    ctx->r9 = 0 | 0;
        goto L_801E20DC;
    // 0x801E20D4: or          $t1, $zero, $zero
    ctx->r9 = 0 | 0;
L_801E20D8:
    // 0x801E20D8: addiu       $t1, $zero, 0x1
    ctx->r9 = ADD32(0, 0X1);
L_801E20DC:
    // 0x801E20DC: lui         $t4, 0x8022
    ctx->r12 = S32(0X8022 << 16);
    // 0x801E20E0: lui         $t3, 0x801D
    ctx->r11 = S32(0X801D << 16);
    // 0x801E20E4: lui         $t2, 0x106
    ctx->r10 = S32(0X106 << 16);
    // 0x801E20E8: ori         $t2, $t2, 0x40
    ctx->r10 = ctx->r10 | 0X40;
    // 0x801E20EC: addiu       $t3, $t3, -0x1A08
    ctx->r11 = ADD32(ctx->r11, -0X1A08);
    // 0x801E20F0: addiu       $t4, $t4, 0x6040
    ctx->r12 = ADD32(ctx->r12, 0X6040);
    // 0x801E20F4: addiu       $t5, $t5, -0x7818
    ctx->r13 = ADD32(ctx->r13, -0X7818);
L_801E20F8:
    // 0x801E20F8: lui         $a3, 0x8023
    ctx->r7 = S32(0X8023 << 16);
    // 0x801E20FC: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x801E2100: bne         $t1, $zero, L_801E212C
    if (ctx->r9 != 0) {
        // 0x801E2104: lw          $a3, -0x7820($a3)
        ctx->r7 = MEM_W(ctx->r7, -0X7820);
            goto L_801E212C;
    }
    // 0x801E2104: lw          $a3, -0x7820($a3)
    ctx->r7 = MEM_W(ctx->r7, -0X7820);
    // 0x801E2108: slt         $at, $a1, $a3
    ctx->r1 = SIGNED(ctx->r5) < SIGNED(ctx->r7) ? 1 : 0;
    // 0x801E210C: bnel        $at, $zero, L_801E2150
    if (ctx->r1 != 0) {
        // 0x801E2110: sltu        $v0, $zero, $a2
        ctx->r2 = 0 < ctx->r6 ? 1 : 0;
            goto L_801E2150;
    }
    goto skip_0;
    // 0x801E2110: sltu        $v0, $zero, $a2
    ctx->r2 = 0 < ctx->r6 ? 1 : 0;
    skip_0:
    // 0x801E2114: lw          $t7, 0x0($t0)
    ctx->r15 = MEM_W(ctx->r8, 0X0);
    // 0x801E2118: slt         $at, $t7, $a1
    ctx->r1 = SIGNED(ctx->r15) < SIGNED(ctx->r5) ? 1 : 0;
    // 0x801E211C: bnel        $at, $zero, L_801E2150
    if (ctx->r1 != 0) {
        // 0x801E2120: sltu        $v0, $zero, $a2
        ctx->r2 = 0 < ctx->r6 ? 1 : 0;
            goto L_801E2150;
    }
    goto skip_1;
    // 0x801E2120: sltu        $v0, $zero, $a2
    ctx->r2 = 0 < ctx->r6 ? 1 : 0;
    skip_1:
    // 0x801E2124: b           L_801E214C
    // 0x801E2128: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
        goto L_801E214C;
    // 0x801E2128: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
L_801E212C:
    // 0x801E212C: slt         $at, $a1, $a3
    ctx->r1 = SIGNED(ctx->r5) < SIGNED(ctx->r7) ? 1 : 0;
    // 0x801E2130: beql        $at, $zero, L_801E214C
    if (ctx->r1 == 0) {
        // 0x801E2134: addiu       $a2, $zero, 0x1
        ctx->r6 = ADD32(0, 0X1);
            goto L_801E214C;
    }
    goto skip_2;
    // 0x801E2134: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    skip_2:
    // 0x801E2138: lw          $t8, 0x0($t0)
    ctx->r24 = MEM_W(ctx->r8, 0X0);
    // 0x801E213C: slt         $at, $t8, $a1
    ctx->r1 = SIGNED(ctx->r24) < SIGNED(ctx->r5) ? 1 : 0;
    // 0x801E2140: bnel        $at, $zero, L_801E2150
    if (ctx->r1 != 0) {
        // 0x801E2144: sltu        $v0, $zero, $a2
        ctx->r2 = 0 < ctx->r6 ? 1 : 0;
            goto L_801E2150;
    }
    goto skip_3;
    // 0x801E2144: sltu        $v0, $zero, $a2
    ctx->r2 = 0 < ctx->r6 ? 1 : 0;
    skip_3:
    // 0x801E2148: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
L_801E214C:
    // 0x801E214C: sltu        $v0, $zero, $a2
    ctx->r2 = 0 < ctx->r6 ? 1 : 0;
L_801E2150:
    // 0x801E2150: beq         $v0, $zero, L_801E21C4
    if (ctx->r2 == 0) {
        // 0x801E2154: or          $a2, $zero, $zero
        ctx->r6 = 0 | 0;
            goto L_801E21C4;
    }
    // 0x801E2154: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x801E2158: lw          $v0, 0x20($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X20);
    // 0x801E215C: sll         $t8, $a1, 6
    ctx->r24 = S32(ctx->r5 << 6);
    // 0x801E2160: lui         $a3, 0x8023
    ctx->r7 = S32(0X8023 << 16);
    // 0x801E2164: addiu       $t6, $v0, 0x8
    ctx->r14 = ADD32(ctx->r2, 0X8);
    // 0x801E2168: sw          $t6, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r14;
    // 0x801E216C: sw          $t2, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r10;
    // 0x801E2170: lw          $t7, 0x0($t3)
    ctx->r15 = MEM_W(ctx->r11, 0X0);
    // 0x801E2174: addu        $t9, $t7, $t8
    ctx->r25 = ADD32(ctx->r15, ctx->r24);
    // 0x801E2178: addiu       $t6, $t9, 0x1380
    ctx->r14 = ADD32(ctx->r25, 0X1380);
    // 0x801E217C: sw          $t6, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r14;
    // 0x801E2180: lw          $v1, 0x20($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X20);
    // 0x801E2184: sll         $t9, $a1, 2
    ctx->r25 = S32(ctx->r5 << 2);
    // 0x801E2188: addu        $t6, $t5, $t9
    ctx->r14 = ADD32(ctx->r13, ctx->r25);
    // 0x801E218C: addiu       $t8, $v1, 0x8
    ctx->r24 = ADD32(ctx->r3, 0X8);
    // 0x801E2190: sw          $t8, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r24;
    // 0x801E2194: sw          $s0, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r16;
    // 0x801E2198: lw          $t7, 0x0($t6)
    ctx->r15 = MEM_W(ctx->r14, 0X0);
    // 0x801E219C: sll         $t8, $t7, 2
    ctx->r24 = S32(ctx->r15 << 2);
    // 0x801E21A0: addu        $t9, $t4, $t8
    ctx->r25 = ADD32(ctx->r12, ctx->r24);
    // 0x801E21A4: lw          $t6, 0x0($t9)
    ctx->r14 = MEM_W(ctx->r25, 0X0);
    // 0x801E21A8: sw          $t6, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r14;
    // 0x801E21AC: lw          $t7, 0x20($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X20);
    // 0x801E21B0: addiu       $t8, $t7, 0x8
    ctx->r24 = ADD32(ctx->r15, 0X8);
    // 0x801E21B4: sw          $t8, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r24;
    // 0x801E21B8: sw          $zero, 0x4($t7)
    MEM_W(0X4, ctx->r15) = 0;
    // 0x801E21BC: sw          $ra, 0x0($t7)
    MEM_W(0X0, ctx->r15) = ctx->r31;
    // 0x801E21C0: lw          $a3, -0x7820($a3)
    ctx->r7 = MEM_W(ctx->r7, -0X7820);
L_801E21C4:
    // 0x801E21C4: bne         $t1, $zero, L_801E21F0
    if (ctx->r9 != 0) {
        // 0x801E21C8: addiu       $v0, $a3, -0x1
        ctx->r2 = ADD32(ctx->r7, -0X1);
            goto L_801E21F0;
    }
    // 0x801E21C8: addiu       $v0, $a3, -0x1
    ctx->r2 = ADD32(ctx->r7, -0X1);
    // 0x801E21CC: slt         $at, $a1, $v0
    ctx->r1 = SIGNED(ctx->r5) < SIGNED(ctx->r2) ? 1 : 0;
    // 0x801E21D0: bne         $at, $zero, L_801E2210
    if (ctx->r1 != 0) {
        // 0x801E21D4: nop
    
            goto L_801E2210;
    }
    // 0x801E21D4: nop

    // 0x801E21D8: lw          $t9, 0x0($t0)
    ctx->r25 = MEM_W(ctx->r8, 0X0);
    // 0x801E21DC: slt         $at, $a1, $t9
    ctx->r1 = SIGNED(ctx->r5) < SIGNED(ctx->r25) ? 1 : 0;
    // 0x801E21E0: beq         $at, $zero, L_801E2210
    if (ctx->r1 == 0) {
        // 0x801E21E4: nop
    
            goto L_801E2210;
    }
    // 0x801E21E4: nop

    // 0x801E21E8: b           L_801E2210
    // 0x801E21EC: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
        goto L_801E2210;
    // 0x801E21EC: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
L_801E21F0:
    // 0x801E21F0: slt         $at, $a1, $v0
    ctx->r1 = SIGNED(ctx->r5) < SIGNED(ctx->r2) ? 1 : 0;
    // 0x801E21F4: beql        $at, $zero, L_801E2210
    if (ctx->r1 == 0) {
        // 0x801E21F8: addiu       $a2, $zero, 0x1
        ctx->r6 = ADD32(0, 0X1);
            goto L_801E2210;
    }
    goto skip_4;
    // 0x801E21F8: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    skip_4:
    // 0x801E21FC: lw          $t6, 0x0($t0)
    ctx->r14 = MEM_W(ctx->r8, 0X0);
    // 0x801E2200: slt         $at, $a1, $t6
    ctx->r1 = SIGNED(ctx->r5) < SIGNED(ctx->r14) ? 1 : 0;
    // 0x801E2204: beq         $at, $zero, L_801E2210
    if (ctx->r1 == 0) {
        // 0x801E2208: nop
    
            goto L_801E2210;
    }
    // 0x801E2208: nop

    // 0x801E220C: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
L_801E2210:
    // 0x801E2210: beq         $a2, $zero, L_801E227C
    if (ctx->r6 == 0) {
        // 0x801E2214: addiu       $at, $zero, 0x10
        ctx->r1 = ADD32(0, 0X10);
            goto L_801E227C;
    }
    // 0x801E2214: addiu       $at, $zero, 0x10
    ctx->r1 = ADD32(0, 0X10);
    // 0x801E2218: lw          $v0, 0x20($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X20);
    // 0x801E221C: sll         $t6, $a1, 6
    ctx->r14 = S32(ctx->r5 << 6);
    // 0x801E2220: addiu       $t8, $v0, 0x8
    ctx->r24 = ADD32(ctx->r2, 0X8);
    // 0x801E2224: sw          $t8, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r24;
    // 0x801E2228: sw          $t2, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r10;
    // 0x801E222C: lw          $t9, 0x0($t3)
    ctx->r25 = MEM_W(ctx->r11, 0X0);
    // 0x801E2230: addu        $t7, $t9, $t6
    ctx->r15 = ADD32(ctx->r25, ctx->r14);
    // 0x801E2234: addiu       $t8, $t7, 0x13C0
    ctx->r24 = ADD32(ctx->r15, 0X13C0);
    // 0x801E2238: sw          $t8, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r24;
    // 0x801E223C: lw          $v1, 0x20($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X20);
    // 0x801E2240: sll         $t7, $a1, 2
    ctx->r15 = S32(ctx->r5 << 2);
    // 0x801E2244: addu        $t8, $t5, $t7
    ctx->r24 = ADD32(ctx->r13, ctx->r15);
    // 0x801E2248: addiu       $t6, $v1, 0x8
    ctx->r14 = ADD32(ctx->r3, 0X8);
    // 0x801E224C: sw          $t6, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r14;
    // 0x801E2250: sw          $s0, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r16;
    // 0x801E2254: lw          $t9, 0x4($t8)
    ctx->r25 = MEM_W(ctx->r24, 0X4);
    // 0x801E2258: sll         $t6, $t9, 2
    ctx->r14 = S32(ctx->r25 << 2);
    // 0x801E225C: addu        $t7, $t4, $t6
    ctx->r15 = ADD32(ctx->r12, ctx->r14);
    // 0x801E2260: lw          $t8, 0x0($t7)
    ctx->r24 = MEM_W(ctx->r15, 0X0);
    // 0x801E2264: sw          $t8, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r24;
    // 0x801E2268: lw          $t9, 0x20($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X20);
    // 0x801E226C: addiu       $t6, $t9, 0x8
    ctx->r14 = ADD32(ctx->r25, 0X8);
    // 0x801E2270: sw          $t6, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r14;
    // 0x801E2274: sw          $zero, 0x4($t9)
    MEM_W(0X4, ctx->r25) = 0;
    // 0x801E2278: sw          $ra, 0x0($t9)
    MEM_W(0X0, ctx->r25) = ctx->r31;
L_801E227C:
    // 0x801E227C: addiu       $a1, $a1, 0x2
    ctx->r5 = ADD32(ctx->r5, 0X2);
    // 0x801E2280: bne         $a1, $at, L_801E20F8
    if (ctx->r5 != ctx->r1) {
        // 0x801E2284: nop
    
            goto L_801E20F8;
    }
    // 0x801E2284: nop

    // 0x801E2288: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    // 0x801E228C: lw          $v0, 0x20($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X20);
    // 0x801E2290: lw          $s0, 0x18($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X18);
    // 0x801E2294: jr          $ra
    // 0x801E2298: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    return;
    // 0x801E2298: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
;}
RECOMP_FUNC void func_801E229C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801E229C: addiu       $sp, $sp, -0x88
    ctx->r29 = ADD32(ctx->r29, -0X88);
    // 0x801E22A0: lui         $t6, 0x8022
    ctx->r14 = S32(0X8022 << 16);
    // 0x801E22A4: lw          $t6, 0x61E8($t6)
    ctx->r14 = MEM_W(ctx->r14, 0X61E8);
    // 0x801E22A8: sw          $s3, 0x4C($sp)
    MEM_W(0X4C, ctx->r29) = ctx->r19;
    // 0x801E22AC: or          $s3, $a0, $zero
    ctx->r19 = ctx->r4 | 0;
    // 0x801E22B0: sw          $ra, 0x5C($sp)
    MEM_W(0X5C, ctx->r29) = ctx->r31;
    // 0x801E22B4: sw          $s6, 0x58($sp)
    MEM_W(0X58, ctx->r29) = ctx->r22;
    // 0x801E22B8: sw          $s5, 0x54($sp)
    MEM_W(0X54, ctx->r29) = ctx->r21;
    // 0x801E22BC: sw          $s4, 0x50($sp)
    MEM_W(0X50, ctx->r29) = ctx->r20;
    // 0x801E22C0: sw          $s2, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r18;
    // 0x801E22C4: sw          $s1, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r17;
    // 0x801E22C8: bne         $t6, $zero, L_801E22D8
    if (ctx->r14 != 0) {
        // 0x801E22CC: sw          $s0, 0x40($sp)
        MEM_W(0X40, ctx->r29) = ctx->r16;
            goto L_801E22D8;
    }
    // 0x801E22CC: sw          $s0, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r16;
    // 0x801E22D0: b           L_801E2508
    // 0x801E22D4: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
        goto L_801E2508;
    // 0x801E22D4: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
L_801E22D8:
    // 0x801E22D8: or          $v0, $s3, $zero
    ctx->r2 = ctx->r19 | 0;
    // 0x801E22DC: lui         $t7, 0x107
    ctx->r15 = S32(0X107 << 16);
    // 0x801E22E0: lui         $s4, 0x600
    ctx->r20 = S32(0X600 << 16);
    // 0x801E22E4: addiu       $t7, $t7, -0x9D8
    ctx->r15 = ADD32(ctx->r15, -0X9D8);
    // 0x801E22E8: sw          $t7, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r15;
    // 0x801E22EC: sw          $s4, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r20;
    // 0x801E22F0: addiu       $t8, $zero, 0x13B
    ctx->r24 = ADD32(0, 0X13B);
    // 0x801E22F4: addiu       $t9, $zero, 0x18
    ctx->r25 = ADD32(0, 0X18);
    // 0x801E22F8: addiu       $a0, $s3, 0x8
    ctx->r4 = ADD32(ctx->r19, 0X8);
    // 0x801E22FC: sw          $t9, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r25;
    // 0x801E2300: sw          $t8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r24;
    // 0x801E2304: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x801E2308: addiu       $a2, $zero, 0x36
    ctx->r6 = ADD32(0, 0X36);
    // 0x801E230C: jal         0x80094338
    // 0x801E2310: addiu       $a3, $zero, 0x20
    ctx->r7 = ADD32(0, 0X20);
    func_80094338(rdram, ctx);
        goto after_0;
    // 0x801E2310: addiu       $a3, $zero, 0x20
    ctx->r7 = ADD32(0, 0X20);
    after_0:
    // 0x801E2314: addiu       $t0, $zero, 0x75
    ctx->r8 = ADD32(0, 0X75);
    // 0x801E2318: addiu       $t1, $zero, 0x1C
    ctx->r9 = ADD32(0, 0X1C);
    // 0x801E231C: sw          $t1, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r9;
    // 0x801E2320: sw          $t0, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r8;
    // 0x801E2324: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x801E2328: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x801E232C: addiu       $a2, $zero, 0x99
    ctx->r6 = ADD32(0, 0X99);
    // 0x801E2330: jal         0x80094338
    // 0x801E2334: addiu       $a3, $zero, 0xB1
    ctx->r7 = ADD32(0, 0XB1);
    func_80094338(rdram, ctx);
        goto after_1;
    // 0x801E2334: addiu       $a3, $zero, 0xB1
    ctx->r7 = ADD32(0, 0XB1);
    after_1:
    // 0x801E2338: lui         $s1, 0x8022
    ctx->r17 = S32(0X8022 << 16);
    // 0x801E233C: lui         $s2, 0x8022
    ctx->r18 = S32(0X8022 << 16);
    // 0x801E2340: or          $s3, $v0, $zero
    ctx->r19 = ctx->r2 | 0;
    // 0x801E2344: addiu       $s2, $s2, 0x61E4
    ctx->r18 = ADD32(ctx->r18, 0X61E4);
    // 0x801E2348: addiu       $s1, $s1, 0x61EC
    ctx->r17 = ADD32(ctx->r17, 0X61EC);
    // 0x801E234C: or          $s0, $zero, $zero
    ctx->r16 = 0 | 0;
L_801E2350:
    // 0x801E2350: lw          $t2, 0x0($s2)
    ctx->r10 = MEM_W(ctx->r18, 0X0);
    // 0x801E2354: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
    // 0x801E2358: addiu       $a2, $zero, 0xFF
    ctx->r6 = ADD32(0, 0XFF);
    // 0x801E235C: bne         $s0, $t2, L_801E236C
    if (ctx->r16 != ctx->r10) {
        // 0x801E2360: addiu       $a3, $zero, 0xFF
        ctx->r7 = ADD32(0, 0XFF);
            goto L_801E236C;
    }
    // 0x801E2360: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    // 0x801E2364: b           L_801E2370
    // 0x801E2368: addiu       $a1, $zero, 0x6
    ctx->r5 = ADD32(0, 0X6);
        goto L_801E2370;
    // 0x801E2368: addiu       $a1, $zero, 0x6
    ctx->r5 = ADD32(0, 0X6);
L_801E236C:
    // 0x801E236C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
L_801E2370:
    // 0x801E2370: addiu       $t3, $zero, 0xFF
    ctx->r11 = ADD32(0, 0XFF);
    // 0x801E2374: addiu       $t4, $zero, 0xFF
    ctx->r12 = ADD32(0, 0XFF);
    // 0x801E2378: addiu       $t5, $zero, 0xFF
    ctx->r13 = ADD32(0, 0XFF);
    // 0x801E237C: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x801E2380: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x801E2384: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x801E2388: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x801E238C: addiu       $t0, $zero, 0xFF
    ctx->r8 = ADD32(0, 0XFF);
    // 0x801E2390: addiu       $t1, $zero, 0xFF
    ctx->r9 = ADD32(0, 0XFF);
    // 0x801E2394: addiu       $t2, $zero, 0xFF
    ctx->r10 = ADD32(0, 0XFF);
    // 0x801E2398: sw          $t2, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r10;
    // 0x801E239C: sw          $t1, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r9;
    // 0x801E23A0: sw          $t0, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r8;
    // 0x801E23A4: sw          $t9, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r25;
    // 0x801E23A8: sw          $t8, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r24;
    // 0x801E23AC: sw          $t7, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r15;
    // 0x801E23B0: sw          $t6, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r14;
    // 0x801E23B4: sw          $t5, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r13;
    // 0x801E23B8: sw          $t4, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r12;
    // 0x801E23BC: jal         0x801E946C
    // 0x801E23C0: sw          $t3, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r11;
    func_801E946C(rdram, ctx);
        goto after_2;
    // 0x801E23C0: sw          $t3, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r11;
    after_2:
    // 0x801E23C4: sw          $s4, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r20;
    // 0x801E23C8: lw          $t3, 0x0($s1)
    ctx->r11 = MEM_W(ctx->r17, 0X0);
    // 0x801E23CC: addiu       $s0, $s0, 0x1
    ctx->r16 = ADD32(ctx->r16, 0X1);
    // 0x801E23D0: slti        $at, $s0, 0x3
    ctx->r1 = SIGNED(ctx->r16) < 0X3 ? 1 : 0;
    // 0x801E23D4: addiu       $s1, $s1, 0x4
    ctx->r17 = ADD32(ctx->r17, 0X4);
    // 0x801E23D8: addiu       $s3, $v0, 0x8
    ctx->r19 = ADD32(ctx->r2, 0X8);
    // 0x801E23DC: bne         $at, $zero, L_801E2350
    if (ctx->r1 != 0) {
        // 0x801E23E0: sw          $t3, 0x4($v0)
        MEM_W(0X4, ctx->r2) = ctx->r11;
            goto L_801E2350;
    }
    // 0x801E23E0: sw          $t3, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r11;
    // 0x801E23E4: addiu       $t4, $zero, 0xFF
    ctx->r12 = ADD32(0, 0XFF);
    // 0x801E23E8: addiu       $t5, $zero, 0xFF
    ctx->r13 = ADD32(0, 0XFF);
    // 0x801E23EC: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x801E23F0: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x801E23F4: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x801E23F8: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x801E23FC: addiu       $t0, $zero, 0xFF
    ctx->r8 = ADD32(0, 0XFF);
    // 0x801E2400: addiu       $t1, $zero, 0xFF
    ctx->r9 = ADD32(0, 0XFF);
    // 0x801E2404: addiu       $t2, $zero, 0xFF
    ctx->r10 = ADD32(0, 0XFF);
    // 0x801E2408: addiu       $t3, $zero, 0xFF
    ctx->r11 = ADD32(0, 0XFF);
    // 0x801E240C: sw          $t3, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r11;
    // 0x801E2410: sw          $t2, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r10;
    // 0x801E2414: sw          $t1, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r9;
    // 0x801E2418: sw          $t0, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r8;
    // 0x801E241C: sw          $t9, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r25;
    // 0x801E2420: sw          $t8, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r24;
    // 0x801E2424: sw          $t7, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r15;
    // 0x801E2428: sw          $t6, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r14;
    // 0x801E242C: sw          $t5, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r13;
    // 0x801E2430: sw          $t4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r12;
    // 0x801E2434: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
    // 0x801E2438: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x801E243C: addiu       $a2, $zero, 0xFF
    ctx->r6 = ADD32(0, 0XFF);
    // 0x801E2440: jal         0x801E946C
    // 0x801E2444: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    func_801E946C(rdram, ctx);
        goto after_3;
    // 0x801E2444: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    after_3:
    // 0x801E2448: addiu       $t4, $zero, 0x23
    ctx->r12 = ADD32(0, 0X23);
    // 0x801E244C: sw          $t4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r12;
    // 0x801E2450: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x801E2454: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x801E2458: addiu       $a2, $zero, 0x1D
    ctx->r6 = ADD32(0, 0X1D);
    // 0x801E245C: addiu       $a3, $zero, 0x7C
    ctx->r7 = ADD32(0, 0X7C);
    // 0x801E2460: jal         0x801E3EE0
    // 0x801E2464: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    func_801E3EE0(rdram, ctx);
        goto after_4;
    // 0x801E2464: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    after_4:
    // 0x801E2468: lui         $s2, 0x8023
    ctx->r18 = S32(0X8023 << 16);
    // 0x801E246C: lui         $s6, 0x8022
    ctx->r22 = S32(0X8022 << 16);
    // 0x801E2470: or          $s3, $v0, $zero
    ctx->r19 = ctx->r2 | 0;
    // 0x801E2474: addiu       $s6, $s6, 0x6150
    ctx->r22 = ADD32(ctx->r22, 0X6150);
    // 0x801E2478: addiu       $s2, $s2, -0x7718
    ctx->r18 = ADD32(ctx->r18, -0X7718);
    // 0x801E247C: or          $s1, $zero, $zero
    ctx->r17 = 0 | 0;
    // 0x801E2480: addiu       $s5, $zero, 0x4E
    ctx->r21 = ADD32(0, 0X4E);
    // 0x801E2484: addiu       $s4, $sp, 0x74
    ctx->r20 = ADD32(ctx->r29, 0X74);
    // 0x801E2488: addiu       $s0, $zero, 0x1D
    ctx->r16 = ADD32(0, 0X1D);
L_801E248C:
    // 0x801E248C: lb          $t5, 0x0($s2)
    ctx->r13 = MEM_B(ctx->r18, 0X0);
    // 0x801E2490: lui         $v0, 0x8022
    ctx->r2 = S32(0X8022 << 16);
    // 0x801E2494: sb          $zero, 0x75($sp)
    MEM_B(0X75, ctx->r29) = 0;
    // 0x801E2498: addiu       $v0, $v0, 0x6130
    ctx->r2 = ADD32(ctx->r2, 0X6130);
    // 0x801E249C: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
    // 0x801E24A0: sb          $t5, 0x74($sp)
    MEM_B(0X74, ctx->r29) = ctx->r13;
L_801E24A4:
    // 0x801E24A4: lb          $t6, 0x74($sp)
    ctx->r14 = MEM_B(ctx->r29, 0X74);
    // 0x801E24A8: lb          $t7, 0x0($v0)
    ctx->r15 = MEM_B(ctx->r2, 0X0);
    // 0x801E24AC: beq         $t6, $t7, L_801E24C0
    if (ctx->r14 == ctx->r15) {
        // 0x801E24B0: nop
    
            goto L_801E24C0;
    }
    // 0x801E24B0: nop

    // 0x801E24B4: addiu       $v1, $v1, 0x1
    ctx->r3 = ADD32(ctx->r3, 0X1);
    // 0x801E24B8: bne         $v1, $s0, L_801E24A4
    if (ctx->r3 != ctx->r16) {
        // 0x801E24BC: addiu       $v0, $v0, 0x1
        ctx->r2 = ADD32(ctx->r2, 0X1);
            goto L_801E24A4;
    }
    // 0x801E24BC: addiu       $v0, $v0, 0x1
    ctx->r2 = ADD32(ctx->r2, 0X1);
L_801E24C0:
    // 0x801E24C0: bne         $v1, $s0, L_801E24D0
    if (ctx->r3 != ctx->r16) {
        // 0x801E24C4: or          $a0, $s3, $zero
        ctx->r4 = ctx->r19 | 0;
            goto L_801E24D0;
    }
    // 0x801E24C4: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
    // 0x801E24C8: b           L_801E24DC
    // 0x801E24CC: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
        goto L_801E24DC;
    // 0x801E24CC: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_801E24D0:
    // 0x801E24D0: sll         $t8, $v1, 2
    ctx->r24 = S32(ctx->r3 << 2);
    // 0x801E24D4: addu        $t9, $s6, $t8
    ctx->r25 = ADD32(ctx->r22, ctx->r24);
    // 0x801E24D8: lw          $v0, 0x0($t9)
    ctx->r2 = MEM_W(ctx->r25, 0X0);
L_801E24DC:
    // 0x801E24DC: addu        $a3, $s1, $v0
    ctx->r7 = ADD32(ctx->r17, ctx->r2);
    // 0x801E24E0: addiu       $t0, $zero, 0xB4
    ctx->r8 = ADD32(0, 0XB4);
    // 0x801E24E4: sw          $t0, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r8;
    // 0x801E24E8: addiu       $a3, $a3, 0xAE
    ctx->r7 = ADD32(ctx->r7, 0XAE);
    // 0x801E24EC: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x801E24F0: jal         0x801E9858
    // 0x801E24F4: or          $a2, $s4, $zero
    ctx->r6 = ctx->r20 | 0;
    func_801E9858(rdram, ctx);
        goto after_5;
    // 0x801E24F4: or          $a2, $s4, $zero
    ctx->r6 = ctx->r20 | 0;
    after_5:
    // 0x801E24F8: addiu       $s1, $s1, 0x1A
    ctx->r17 = ADD32(ctx->r17, 0X1A);
    // 0x801E24FC: addiu       $s2, $s2, 0x1
    ctx->r18 = ADD32(ctx->r18, 0X1);
    // 0x801E2500: bne         $s1, $s5, L_801E248C
    if (ctx->r17 != ctx->r21) {
        // 0x801E2504: or          $s3, $v0, $zero
        ctx->r19 = ctx->r2 | 0;
            goto L_801E248C;
    }
    // 0x801E2504: or          $s3, $v0, $zero
    ctx->r19 = ctx->r2 | 0;
L_801E2508:
    // 0x801E2508: lw          $ra, 0x5C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X5C);
    // 0x801E250C: lw          $s0, 0x40($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X40);
    // 0x801E2510: lw          $s1, 0x44($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X44);
    // 0x801E2514: lw          $s2, 0x48($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X48);
    // 0x801E2518: lw          $s3, 0x4C($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X4C);
    // 0x801E251C: lw          $s4, 0x50($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X50);
    // 0x801E2520: lw          $s5, 0x54($sp)
    ctx->r21 = MEM_W(ctx->r29, 0X54);
    // 0x801E2524: lw          $s6, 0x58($sp)
    ctx->r22 = MEM_W(ctx->r29, 0X58);
    // 0x801E2528: jr          $ra
    // 0x801E252C: addiu       $sp, $sp, 0x88
    ctx->r29 = ADD32(ctx->r29, 0X88);
    return;
    // 0x801E252C: addiu       $sp, $sp, 0x88
    ctx->r29 = ADD32(ctx->r29, 0X88);
;}
RECOMP_FUNC void func_801E2530(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801E2530: lui         $t1, 0x8022
    ctx->r9 = S32(0X8022 << 16);
    // 0x801E2534: addiu       $t1, $t1, 0x61C8
    ctx->r9 = ADD32(ctx->r9, 0X61C8);
    // 0x801E2538: lw          $v0, 0x0($t1)
    ctx->r2 = MEM_W(ctx->r9, 0X0);
    // 0x801E253C: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x801E2540: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x801E2544: sltiu       $at, $v0, 0xB
    ctx->r1 = ctx->r2 < 0XB ? 1 : 0;
    // 0x801E2548: beq         $at, $zero, L_801E27C8
    if (ctx->r1 == 0) {
        // 0x801E254C: sll         $t6, $v0, 2
        ctx->r14 = S32(ctx->r2 << 2);
            goto L_801E27C8;
    }
    // 0x801E254C: sll         $t6, $v0, 2
    ctx->r14 = S32(ctx->r2 << 2);
    // 0x801E2550: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E2554: addu        $at, $at, $t6
    gpr jr_addend_801E255C = ctx->r14;
    ctx->r1 = ADD32(ctx->r1, ctx->r14);
    // 0x801E2558: lw          $t6, 0x62F8($at)
    ctx->r14 = ADD32(ctx->r1, 0X62F8);
    // 0x801E255C: jr          $t6
    // 0x801E2560: nop

    switch (jr_addend_801E255C >> 2) {
        case 0: goto L_801E2B7C; break;
        case 1: goto L_801E27C8; break;
        case 2: goto L_801E27C8; break;
        case 3: goto L_801E27C8; break;
        case 4: goto L_801E27C8; break;
        case 5: goto L_801E2564; break;
        case 6: goto L_801E2B7C; break;
        case 7: goto L_801E2B7C; break;
        case 8: goto L_801E2B7C; break;
        case 9: goto L_801E2B7C; break;
        case 10: goto L_801E25DC; break;
        default: switch_error(__func__, 0x801E255C, 0x802262F8);
    }
    // 0x801E2560: nop

L_801E2564:
    // 0x801E2564: jal         0x801E2C14
    // 0x801E2568: nop

    func_801E2C14(rdram, ctx);
        goto after_0;
    // 0x801E2568: nop

    after_0:
    // 0x801E256C: lui         $a0, 0x801D
    ctx->r4 = S32(0X801D << 16);
    // 0x801E2570: lui         $a1, 0x8022
    ctx->r5 = S32(0X8022 << 16);
    // 0x801E2574: lui         $a2, 0x8023
    ctx->r6 = S32(0X8023 << 16);
    // 0x801E2578: addiu       $a2, $a2, -0x7718
    ctx->r6 = ADD32(ctx->r6, -0X7718);
    // 0x801E257C: addiu       $a1, $a1, 0x6284
    ctx->r5 = ADD32(ctx->r5, 0X6284);
    // 0x801E2580: jal         0x800CA210
    // 0x801E2584: addiu       $a0, $a0, -0x1900
    ctx->r4 = ADD32(ctx->r4, -0X1900);
    func_800CA210(rdram, ctx);
        goto after_1;
    // 0x801E2584: addiu       $a0, $a0, -0x1900
    ctx->r4 = ADD32(ctx->r4, -0X1900);
    after_1:
    // 0x801E2588: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x801E258C: lw          $v0, -0x19F8($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X19F8);
    // 0x801E2590: addiu       $at, $zero, 0x4
    ctx->r1 = ADD32(0, 0X4);
    // 0x801E2594: bne         $v0, $at, L_801E25AC
    if (ctx->r2 != ctx->r1) {
        // 0x801E2598: nop
    
            goto L_801E25AC;
    }
    // 0x801E2598: nop

    // 0x801E259C: jal         0x801E2B8C
    // 0x801E25A0: addiu       $a0, $zero, 0x42
    ctx->r4 = ADD32(0, 0X42);
    func_801E2B8C(rdram, ctx);
        goto after_2;
    // 0x801E25A0: addiu       $a0, $zero, 0x42
    ctx->r4 = ADD32(0, 0X42);
    after_2:
    // 0x801E25A4: b           L_801E2B80
    // 0x801E25A8: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_801E2B80;
    // 0x801E25A8: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_801E25AC:
    // 0x801E25AC: bne         $v0, $zero, L_801E25C4
    if (ctx->r2 != 0) {
        // 0x801E25B0: addiu       $at, $zero, 0xB
        ctx->r1 = ADD32(0, 0XB);
            goto L_801E25C4;
    }
    // 0x801E25B0: addiu       $at, $zero, 0xB
    ctx->r1 = ADD32(0, 0XB);
    // 0x801E25B4: jal         0x801EC20C
    // 0x801E25B8: nop

    func_801EC20C(rdram, ctx);
        goto after_3;
    // 0x801E25B8: nop

    after_3:
    // 0x801E25BC: b           L_801E2B80
    // 0x801E25C0: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_801E2B80;
    // 0x801E25C0: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_801E25C4:
    // 0x801E25C4: bnel        $v0, $at, L_801E2B80
    if (ctx->r2 != ctx->r1) {
        // 0x801E25C8: lw          $ra, 0x14($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X14);
            goto L_801E2B80;
    }
    goto skip_0;
    // 0x801E25C8: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    skip_0:
    // 0x801E25CC: jal         0x801ED004
    // 0x801E25D0: nop

    func_801ED004(rdram, ctx);
        goto after_4;
    // 0x801E25D0: nop

    after_4:
    // 0x801E25D4: b           L_801E2B80
    // 0x801E25D8: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_801E2B80;
    // 0x801E25D8: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_801E25DC:
    // 0x801E25DC: lui         $t2, 0x8023
    ctx->r10 = S32(0X8023 << 16);
    // 0x801E25E0: addiu       $t2, $t2, -0x7714
    ctx->r10 = ADD32(ctx->r10, -0X7714);
    // 0x801E25E4: lhu         $v0, 0x0($t2)
    ctx->r2 = MEM_HU(ctx->r10, 0X0);
    // 0x801E25E8: lui         $a3, 0x8022
    ctx->r7 = S32(0X8022 << 16);
    // 0x801E25EC: addiu       $a3, $a3, 0x61C4
    ctx->r7 = ADD32(ctx->r7, 0X61C4);
    // 0x801E25F0: andi        $t7, $v0, 0x1
    ctx->r15 = ctx->r2 & 0X1;
    // 0x801E25F4: beq         $t7, $zero, L_801E26D8
    if (ctx->r15 == 0) {
        // 0x801E25F8: andi        $t9, $v0, 0x2
        ctx->r25 = ctx->r2 & 0X2;
            goto L_801E26D8;
    }
    // 0x801E25F8: andi        $t9, $v0, 0x2
    ctx->r25 = ctx->r2 & 0X2;
    // 0x801E25FC: lw          $v1, 0x0($a3)
    ctx->r3 = MEM_W(ctx->r7, 0X0);
    // 0x801E2600: lui         $t0, 0x8023
    ctx->r8 = S32(0X8023 << 16);
    // 0x801E2604: addiu       $t0, $t0, -0x7818
    ctx->r8 = ADD32(ctx->r8, -0X7818);
    // 0x801E2608: addiu       $a0, $v1, 0x8
    ctx->r4 = ADD32(ctx->r3, 0X8);
    // 0x801E260C: addiu       $t8, $zero, 0x8
    ctx->r24 = ADD32(0, 0X8);
    // 0x801E2610: sw          $t8, 0x0($t1)
    MEM_W(0X0, ctx->r9) = ctx->r24;
    // 0x801E2614: bgez        $a0, L_801E2628
    if (SIGNED(ctx->r4) >= 0) {
        // 0x801E2618: andi        $t9, $a0, 0xF
        ctx->r25 = ctx->r4 & 0XF;
            goto L_801E2628;
    }
    // 0x801E2618: andi        $t9, $a0, 0xF
    ctx->r25 = ctx->r4 & 0XF;
    // 0x801E261C: beq         $t9, $zero, L_801E2628
    if (ctx->r25 == 0) {
        // 0x801E2620: nop
    
            goto L_801E2628;
    }
    // 0x801E2620: nop

    // 0x801E2624: addiu       $t9, $t9, -0x10
    ctx->r25 = ADD32(ctx->r25, -0X10);
L_801E2628:
    // 0x801E2628: addiu       $t4, $t9, 0x1
    ctx->r12 = ADD32(ctx->r25, 0X1);
    // 0x801E262C: sll         $t3, $t9, 2
    ctx->r11 = S32(ctx->r25 << 2);
    // 0x801E2630: or          $a0, $t9, $zero
    ctx->r4 = ctx->r25 | 0;
    // 0x801E2634: addu        $v0, $t0, $t3
    ctx->r2 = ADD32(ctx->r8, ctx->r11);
    // 0x801E2638: bgez        $t4, L_801E264C
    if (SIGNED(ctx->r12) >= 0) {
        // 0x801E263C: andi        $t5, $t4, 0xF
        ctx->r13 = ctx->r12 & 0XF;
            goto L_801E264C;
    }
    // 0x801E263C: andi        $t5, $t4, 0xF
    ctx->r13 = ctx->r12 & 0XF;
    // 0x801E2640: beq         $t5, $zero, L_801E264C
    if (ctx->r13 == 0) {
        // 0x801E2644: nop
    
            goto L_801E264C;
    }
    // 0x801E2644: nop

    // 0x801E2648: addiu       $t5, $t5, -0x10
    ctx->r13 = ADD32(ctx->r13, -0X10);
L_801E264C:
    // 0x801E264C: sll         $t6, $t5, 2
    ctx->r14 = S32(ctx->r13 << 2);
    // 0x801E2650: addu        $t7, $t0, $t6
    ctx->r15 = ADD32(ctx->r8, ctx->r14);
    // 0x801E2654: lw          $t8, 0x0($t7)
    ctx->r24 = MEM_W(ctx->r15, 0X0);
    // 0x801E2658: addiu       $t4, $v1, -0x1
    ctx->r12 = ADD32(ctx->r3, -0X1);
    // 0x801E265C: or          $v1, $t4, $zero
    ctx->r3 = ctx->r12 | 0;
    // 0x801E2660: addiu       $t9, $t8, -0x1
    ctx->r25 = ADD32(ctx->r24, -0X1);
    // 0x801E2664: bgez        $t9, L_801E2674
    if (SIGNED(ctx->r25) >= 0) {
        // 0x801E2668: sw          $t9, 0x0($v0)
        MEM_W(0X0, ctx->r2) = ctx->r25;
            goto L_801E2674;
    }
    // 0x801E2668: sw          $t9, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r25;
    // 0x801E266C: addiu       $t3, $t9, 0x1F
    ctx->r11 = ADD32(ctx->r25, 0X1F);
    // 0x801E2670: sw          $t3, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r11;
L_801E2674:
    // 0x801E2674: bgez        $t4, L_801E2684
    if (SIGNED(ctx->r12) >= 0) {
        // 0x801E2678: sw          $t4, 0x0($a3)
        MEM_W(0X0, ctx->r7) = ctx->r12;
            goto L_801E2684;
    }
    // 0x801E2678: sw          $t4, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r12;
    // 0x801E267C: addiu       $v1, $zero, 0xF
    ctx->r3 = ADD32(0, 0XF);
    // 0x801E2680: sw          $v1, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r3;
L_801E2684:
    // 0x801E2684: sll         $t6, $v1, 2
    ctx->r14 = S32(ctx->r3 << 2);
    // 0x801E2688: addu        $t7, $t0, $t6
    ctx->r15 = ADD32(ctx->r8, ctx->r14);
    // 0x801E268C: lw          $t8, 0x0($t7)
    ctx->r24 = MEM_W(ctx->r15, 0X0);
    // 0x801E2690: mtc1        $v1, $f4
    ctx->f4.u32l = ctx->r3;
    // 0x801E2694: addiu       $at, $zero, 0x1E
    ctx->r1 = ADD32(0, 0X1E);
    // 0x801E2698: bne         $t8, $at, L_801E26A4
    if (ctx->r24 != ctx->r1) {
        // 0x801E269C: cvt.s.w     $f6, $f4
        CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
            goto L_801E26A4;
    }
    // 0x801E269C: cvt.s.w     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
    // 0x801E26A0: sh          $zero, 0x0($t2)
    MEM_H(0X0, ctx->r10) = 0;
L_801E26A4:
    // 0x801E26A4: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E26A8: lwc1        $f8, 0x6324($at)
    ctx->f8.u32l = MEM_W(ctx->r1, 0X6324);
    // 0x801E26AC: lui         $at, 0x4180
    ctx->r1 = S32(0X4180 << 16);
    // 0x801E26B0: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
    // 0x801E26B4: mul.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = MUL_S(ctx->f6.fl, ctx->f8.fl);
    // 0x801E26B8: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E26BC: addiu       $a0, $zero, 0x2E
    ctx->r4 = ADD32(0, 0X2E);
    // 0x801E26C0: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x801E26C4: div.s       $f18, $f10, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f18.fl = DIV_S(ctx->f10.fl, ctx->f16.fl);
    // 0x801E26C8: jal         0x800C37F4
    // 0x801E26CC: swc1        $f18, 0x61D4($at)
    MEM_W(0X61D4, ctx->r1) = ctx->f18.u32l;
    func_800C37F4(rdram, ctx);
        goto after_5;
    // 0x801E26CC: swc1        $f18, 0x61D4($at)
    MEM_W(0X61D4, ctx->r1) = ctx->f18.u32l;
    after_5:
    // 0x801E26D0: b           L_801E2B80
    // 0x801E26D4: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_801E2B80;
    // 0x801E26D4: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_801E26D8:
    // 0x801E26D8: beq         $t9, $zero, L_801E2B7C
    if (ctx->r25 == 0) {
        // 0x801E26DC: lui         $a3, 0x8022
        ctx->r7 = S32(0X8022 << 16);
            goto L_801E2B7C;
    }
    // 0x801E26DC: lui         $a3, 0x8022
    ctx->r7 = S32(0X8022 << 16);
    // 0x801E26E0: addiu       $a3, $a3, 0x61C4
    ctx->r7 = ADD32(ctx->r7, 0X61C4);
    // 0x801E26E4: lw          $v1, 0x0($a3)
    ctx->r3 = MEM_W(ctx->r7, 0X0);
    // 0x801E26E8: addiu       $t3, $zero, 0x9
    ctx->r11 = ADD32(0, 0X9);
    // 0x801E26EC: sw          $t3, 0x0($t1)
    MEM_W(0X0, ctx->r9) = ctx->r11;
    // 0x801E26F0: addiu       $a0, $v1, 0x8
    ctx->r4 = ADD32(ctx->r3, 0X8);
    // 0x801E26F4: bgez        $a0, L_801E2708
    if (SIGNED(ctx->r4) >= 0) {
        // 0x801E26F8: andi        $t4, $a0, 0xF
        ctx->r12 = ctx->r4 & 0XF;
            goto L_801E2708;
    }
    // 0x801E26F8: andi        $t4, $a0, 0xF
    ctx->r12 = ctx->r4 & 0XF;
    // 0x801E26FC: beq         $t4, $zero, L_801E2708
    if (ctx->r12 == 0) {
        // 0x801E2700: nop
    
            goto L_801E2708;
    }
    // 0x801E2700: nop

    // 0x801E2704: addiu       $t4, $t4, -0x10
    ctx->r12 = ADD32(ctx->r12, -0X10);
L_801E2708:
    // 0x801E2708: addiu       $v0, $t4, -0x1
    ctx->r2 = ADD32(ctx->r12, -0X1);
    // 0x801E270C: or          $a0, $t4, $zero
    ctx->r4 = ctx->r12 | 0;
    // 0x801E2710: bgez        $v0, L_801E271C
    if (SIGNED(ctx->r2) >= 0) {
        // 0x801E2714: or          $a2, $v0, $zero
        ctx->r6 = ctx->r2 | 0;
            goto L_801E271C;
    }
    // 0x801E2714: or          $a2, $v0, $zero
    ctx->r6 = ctx->r2 | 0;
    // 0x801E2718: addiu       $a2, $v0, 0x10
    ctx->r6 = ADD32(ctx->r2, 0X10);
L_801E271C:
    // 0x801E271C: lui         $t0, 0x8023
    ctx->r8 = S32(0X8023 << 16);
    // 0x801E2720: addiu       $t0, $t0, -0x7818
    ctx->r8 = ADD32(ctx->r8, -0X7818);
    // 0x801E2724: sll         $t6, $a2, 2
    ctx->r14 = S32(ctx->r6 << 2);
    // 0x801E2728: addu        $t7, $t0, $t6
    ctx->r15 = ADD32(ctx->r8, ctx->r14);
    // 0x801E272C: lw          $t8, 0x0($t7)
    ctx->r24 = MEM_W(ctx->r15, 0X0);
    // 0x801E2730: sll         $t5, $a0, 2
    ctx->r13 = S32(ctx->r4 << 2);
    // 0x801E2734: addu        $v0, $t0, $t5
    ctx->r2 = ADD32(ctx->r8, ctx->r13);
    // 0x801E2738: addiu       $t9, $t8, 0x1
    ctx->r25 = ADD32(ctx->r24, 0X1);
    // 0x801E273C: slti        $at, $t9, 0x1F
    ctx->r1 = SIGNED(ctx->r25) < 0X1F ? 1 : 0;
    // 0x801E2740: bne         $at, $zero, L_801E2750
    if (ctx->r1 != 0) {
        // 0x801E2744: sw          $t9, 0x0($v0)
        MEM_W(0X0, ctx->r2) = ctx->r25;
            goto L_801E2750;
    }
    // 0x801E2744: sw          $t9, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r25;
    // 0x801E2748: addiu       $t3, $t9, -0x1F
    ctx->r11 = ADD32(ctx->r25, -0X1F);
    // 0x801E274C: sw          $t3, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r11;
L_801E2750:
    // 0x801E2750: addiu       $t4, $v1, 0x1
    ctx->r12 = ADD32(ctx->r3, 0X1);
    // 0x801E2754: or          $v1, $t4, $zero
    ctx->r3 = ctx->r12 | 0;
    // 0x801E2758: mtc1        $v1, $f4
    ctx->f4.u32l = ctx->r3;
    // 0x801E275C: sw          $t4, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r12;
    // 0x801E2760: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E2764: cvt.s.w     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
    // 0x801E2768: lwc1        $f8, 0x6328($at)
    ctx->f8.u32l = MEM_W(ctx->r1, 0X6328);
    // 0x801E276C: lui         $at, 0x4180
    ctx->r1 = S32(0X4180 << 16);
    // 0x801E2770: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
    // 0x801E2774: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E2778: addiu       $a0, $zero, 0x2F
    ctx->r4 = ADD32(0, 0X2F);
    // 0x801E277C: mul.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = MUL_S(ctx->f6.fl, ctx->f8.fl);
    // 0x801E2780: div.s       $f18, $f10, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f18.fl = DIV_S(ctx->f10.fl, ctx->f16.fl);
    // 0x801E2784: swc1        $f18, 0x61D4($at)
    MEM_W(0X61D4, ctx->r1) = ctx->f18.u32l;
    // 0x801E2788: slti        $at, $t4, 0x10
    ctx->r1 = SIGNED(ctx->r12) < 0X10 ? 1 : 0;
    // 0x801E278C: bnel        $at, $zero, L_801E27A0
    if (ctx->r1 != 0) {
        // 0x801E2790: sll         $t5, $v1, 2
        ctx->r13 = S32(ctx->r3 << 2);
            goto L_801E27A0;
    }
    goto skip_1;
    // 0x801E2790: sll         $t5, $v1, 2
    ctx->r13 = S32(ctx->r3 << 2);
    skip_1:
    // 0x801E2794: sw          $zero, 0x0($a3)
    MEM_W(0X0, ctx->r7) = 0;
    // 0x801E2798: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
    // 0x801E279C: sll         $t5, $v1, 2
    ctx->r13 = S32(ctx->r3 << 2);
L_801E27A0:
    // 0x801E27A0: addu        $t6, $t0, $t5
    ctx->r14 = ADD32(ctx->r8, ctx->r13);
    // 0x801E27A4: lw          $t7, 0x0($t6)
    ctx->r15 = MEM_W(ctx->r14, 0X0);
    // 0x801E27A8: addiu       $at, $zero, 0x1E
    ctx->r1 = ADD32(0, 0X1E);
    // 0x801E27AC: bne         $t7, $at, L_801E27B8
    if (ctx->r15 != ctx->r1) {
        // 0x801E27B0: nop
    
            goto L_801E27B8;
    }
    // 0x801E27B0: nop

    // 0x801E27B4: sh          $zero, 0x0($t2)
    MEM_H(0X0, ctx->r10) = 0;
L_801E27B8:
    // 0x801E27B8: jal         0x800C37F4
    // 0x801E27BC: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_6;
    // 0x801E27BC: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_6:
    // 0x801E27C0: b           L_801E2B80
    // 0x801E27C4: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_801E2B80;
    // 0x801E27C4: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_801E27C8:
    // 0x801E27C8: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x801E27CC: lhu         $v1, -0x19A6($v1)
    ctx->r3 = MEM_HU(ctx->r3, -0X19A6);
    // 0x801E27D0: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    // 0x801E27D4: andi        $t8, $v1, 0xB000
    ctx->r24 = ctx->r3 & 0XB000;
    // 0x801E27D8: beq         $t8, $zero, L_801E28B8
    if (ctx->r24 == 0) {
        // 0x801E27DC: andi        $t7, $v1, 0x4000
        ctx->r15 = ctx->r3 & 0X4000;
            goto L_801E28B8;
    }
    // 0x801E27DC: andi        $t7, $v1, 0x4000
    ctx->r15 = ctx->r3 & 0X4000;
    // 0x801E27E0: bne         $a0, $v0, L_801E2B7C
    if (ctx->r4 != ctx->r2) {
        // 0x801E27E4: lui         $a1, 0x8022
        ctx->r5 = S32(0X8022 << 16);
            goto L_801E2B7C;
    }
    // 0x801E27E4: lui         $a1, 0x8022
    ctx->r5 = S32(0X8022 << 16);
    // 0x801E27E8: lui         $a3, 0x8022
    ctx->r7 = S32(0X8022 << 16);
    // 0x801E27EC: addiu       $a3, $a3, 0x61C4
    ctx->r7 = ADD32(ctx->r7, 0X61C4);
    // 0x801E27F0: lw          $t9, 0x0($a3)
    ctx->r25 = MEM_W(ctx->r7, 0X0);
    // 0x801E27F4: addiu       $a1, $a1, 0x61E4
    ctx->r5 = ADD32(ctx->r5, 0X61E4);
    // 0x801E27F8: lw          $t5, 0x0($a1)
    ctx->r13 = MEM_W(ctx->r5, 0X0);
    // 0x801E27FC: lui         $t0, 0x8023
    ctx->r8 = S32(0X8023 << 16);
    // 0x801E2800: addiu       $t0, $t0, -0x7818
    ctx->r8 = ADD32(ctx->r8, -0X7818);
    // 0x801E2804: sll         $t3, $t9, 2
    ctx->r11 = S32(ctx->r25 << 2);
    // 0x801E2808: addu        $t4, $t0, $t3
    ctx->r12 = ADD32(ctx->r8, ctx->r11);
    // 0x801E280C: slti        $at, $t5, 0x3
    ctx->r1 = SIGNED(ctx->r13) < 0X3 ? 1 : 0;
    // 0x801E2810: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    // 0x801E2814: beq         $at, $zero, L_801E2830
    if (ctx->r1 == 0) {
        // 0x801E2818: lw          $v1, 0x0($t4)
        ctx->r3 = MEM_W(ctx->r12, 0X0);
            goto L_801E2830;
    }
    // 0x801E2818: lw          $v1, 0x0($t4)
    ctx->r3 = MEM_W(ctx->r12, 0X0);
    // 0x801E281C: addiu       $at, $zero, 0x1E
    ctx->r1 = ADD32(0, 0X1E);
    // 0x801E2820: bne         $v1, $at, L_801E2854
    if (ctx->r3 != ctx->r1) {
        // 0x801E2824: or          $v0, $a0, $zero
        ctx->r2 = ctx->r4 | 0;
            goto L_801E2854;
    }
    // 0x801E2824: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x801E2828: b           L_801E2854
    // 0x801E282C: addiu       $v0, $zero, 0x2
    ctx->r2 = ADD32(0, 0X2);
        goto L_801E2854;
    // 0x801E282C: addiu       $v0, $zero, 0x2
    ctx->r2 = ADD32(0, 0X2);
L_801E2830:
    // 0x801E2830: addiu       $at, $zero, 0x1E
    ctx->r1 = ADD32(0, 0X1E);
    // 0x801E2834: bnel        $v1, $at, L_801E2848
    if (ctx->r3 != ctx->r1) {
        // 0x801E2838: addiu       $at, $zero, 0x1D
        ctx->r1 = ADD32(0, 0X1D);
            goto L_801E2848;
    }
    goto skip_2;
    // 0x801E2838: addiu       $at, $zero, 0x1D
    ctx->r1 = ADD32(0, 0X1D);
    skip_2:
    // 0x801E283C: b           L_801E2854
    // 0x801E2840: addiu       $v0, $zero, 0x2
    ctx->r2 = ADD32(0, 0X2);
        goto L_801E2854;
    // 0x801E2840: addiu       $v0, $zero, 0x2
    ctx->r2 = ADD32(0, 0X2);
    // 0x801E2844: addiu       $at, $zero, 0x1D
    ctx->r1 = ADD32(0, 0X1D);
L_801E2848:
    // 0x801E2848: bne         $v1, $at, L_801E2854
    if (ctx->r3 != ctx->r1) {
        // 0x801E284C: nop
    
            goto L_801E2854;
    }
    // 0x801E284C: nop

    // 0x801E2850: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
L_801E2854:
    // 0x801E2854: beq         $v0, $zero, L_801E2B7C
    if (ctx->r2 == 0) {
        // 0x801E2858: addiu       $t6, $zero, 0x4
        ctx->r14 = ADD32(0, 0X4);
            goto L_801E2B7C;
    }
    // 0x801E2858: addiu       $t6, $zero, 0x4
    ctx->r14 = ADD32(0, 0X4);
    // 0x801E285C: sw          $t6, 0x0($t1)
    MEM_W(0X0, ctx->r9) = ctx->r14;
    // 0x801E2860: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E2864: bne         $v0, $a0, L_801E2880
    if (ctx->r2 != ctx->r4) {
        // 0x801E2868: sw          $zero, 0x61E0($at)
        MEM_W(0X61E0, ctx->r1) = 0;
            goto L_801E2880;
    }
    // 0x801E2868: sw          $zero, 0x61E0($at)
    MEM_W(0X61E0, ctx->r1) = 0;
    // 0x801E286C: addiu       $a0, $zero, 0x1A
    ctx->r4 = ADD32(0, 0X1A);
    // 0x801E2870: jal         0x800C37F4
    // 0x801E2874: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_7;
    // 0x801E2874: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_7:
    // 0x801E2878: b           L_801E2B80
    // 0x801E287C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_801E2B80;
    // 0x801E287C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_801E2880:
    // 0x801E2880: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x801E2884: bne         $v0, $at, L_801E289C
    if (ctx->r2 != ctx->r1) {
        // 0x801E2888: addiu       $a0, $zero, 0x30
        ctx->r4 = ADD32(0, 0X30);
            goto L_801E289C;
    }
    // 0x801E2888: addiu       $a0, $zero, 0x30
    ctx->r4 = ADD32(0, 0X30);
    // 0x801E288C: jal         0x800C37F4
    // 0x801E2890: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_8;
    // 0x801E2890: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_8:
    // 0x801E2894: b           L_801E2B80
    // 0x801E2898: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_801E2B80;
    // 0x801E2898: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_801E289C:
    // 0x801E289C: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x801E28A0: bne         $v0, $at, L_801E2B7C
    if (ctx->r2 != ctx->r1) {
        // 0x801E28A4: addiu       $a0, $zero, 0x12
        ctx->r4 = ADD32(0, 0X12);
            goto L_801E2B7C;
    }
    // 0x801E28A4: addiu       $a0, $zero, 0x12
    ctx->r4 = ADD32(0, 0X12);
    // 0x801E28A8: jal         0x800C37F4
    // 0x801E28AC: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_9;
    // 0x801E28AC: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_9:
    // 0x801E28B0: b           L_801E2B80
    // 0x801E28B4: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_801E2B80;
    // 0x801E28B4: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_801E28B8:
    // 0x801E28B8: beq         $t7, $zero, L_801E2904
    if (ctx->r15 == 0) {
        // 0x801E28BC: lui         $t9, 0x8015
        ctx->r25 = S32(0X8015 << 16);
            goto L_801E2904;
    }
    // 0x801E28BC: lui         $t9, 0x8015
    ctx->r25 = S32(0X8015 << 16);
    // 0x801E28C0: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    // 0x801E28C4: bne         $a0, $v0, L_801E2B7C
    if (ctx->r4 != ctx->r2) {
        // 0x801E28C8: lui         $a1, 0x8022
        ctx->r5 = S32(0X8022 << 16);
            goto L_801E2B7C;
    }
    // 0x801E28C8: lui         $a1, 0x8022
    ctx->r5 = S32(0X8022 << 16);
    // 0x801E28CC: addiu       $a1, $a1, 0x61E4
    ctx->r5 = ADD32(ctx->r5, 0X61E4);
    // 0x801E28D0: lw          $v0, 0x0($a1)
    ctx->r2 = MEM_W(ctx->r5, 0X0);
    // 0x801E28D4: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801E28D8: addiu       $a0, $zero, 0x12
    ctx->r4 = ADD32(0, 0X12);
    // 0x801E28DC: blez        $v0, L_801E28EC
    if (SIGNED(ctx->r2) <= 0) {
        // 0x801E28E0: addiu       $t8, $v0, -0x1
        ctx->r24 = ADD32(ctx->r2, -0X1);
            goto L_801E28EC;
    }
    // 0x801E28E0: addiu       $t8, $v0, -0x1
    ctx->r24 = ADD32(ctx->r2, -0X1);
    // 0x801E28E4: sw          $t8, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r24;
    // 0x801E28E8: or          $v0, $t8, $zero
    ctx->r2 = ctx->r24 | 0;
L_801E28EC:
    // 0x801E28EC: addu        $at, $at, $v0
    ctx->r1 = ADD32(ctx->r1, ctx->r2);
    // 0x801E28F0: sb          $zero, -0x7718($at)
    MEM_B(-0X7718, ctx->r1) = 0;
    // 0x801E28F4: jal         0x800C37F4
    // 0x801E28F8: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_10;
    // 0x801E28F8: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_10:
    // 0x801E28FC: b           L_801E2B80
    // 0x801E2900: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_801E2B80;
    // 0x801E2900: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_801E2904:
    // 0x801E2904: lw          $t9, 0x4330($t9)
    ctx->r25 = MEM_W(ctx->r25, 0X4330);
    // 0x801E2908: lui         $t4, 0x8015
    ctx->r12 = S32(0X8015 << 16);
    // 0x801E290C: addiu       $t4, $t4, 0x4308
    ctx->r12 = ADD32(ctx->r12, 0X4308);
    // 0x801E2910: sll         $t3, $t9, 2
    ctx->r11 = S32(ctx->r25 << 2);
    // 0x801E2914: addu        $t3, $t3, $t9
    ctx->r11 = ADD32(ctx->r11, ctx->r25);
    // 0x801E2918: sll         $t3, $t3, 1
    ctx->r11 = S32(ctx->r11 << 1);
    // 0x801E291C: addu        $v1, $t3, $t4
    ctx->r3 = ADD32(ctx->r11, ctx->r12);
    // 0x801E2920: lhu         $a0, 0x0($v1)
    ctx->r4 = MEM_HU(ctx->r3, 0X0);
    // 0x801E2924: andi        $a1, $a0, 0x200
    ctx->r5 = ctx->r4 & 0X200;
    // 0x801E2928: bnel        $a1, $zero, L_801E2948
    if (ctx->r5 != 0) {
        // 0x801E292C: addiu       $a0, $zero, 0x1
        ctx->r4 = ADD32(0, 0X1);
            goto L_801E2948;
    }
    goto skip_3;
    // 0x801E292C: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    skip_3:
    // 0x801E2930: lb          $a2, 0x8($v1)
    ctx->r6 = MEM_B(ctx->r3, 0X8);
    // 0x801E2934: andi        $v1, $a0, 0x100
    ctx->r3 = ctx->r4 & 0X100;
    // 0x801E2938: slti        $at, $a2, -0xC
    ctx->r1 = SIGNED(ctx->r6) < -0XC ? 1 : 0;
    // 0x801E293C: beq         $at, $zero, L_801E2A60
    if (ctx->r1 == 0) {
        // 0x801E2940: nop
    
            goto L_801E2A60;
    }
    // 0x801E2940: nop

    // 0x801E2944: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
L_801E2948:
    // 0x801E2948: bnel        $a0, $v0, L_801E2B80
    if (ctx->r4 != ctx->r2) {
        // 0x801E294C: lw          $ra, 0x14($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X14);
            goto L_801E2B80;
    }
    goto skip_4;
    // 0x801E294C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    skip_4:
    // 0x801E2950: beq         $a1, $zero, L_801E2970
    if (ctx->r5 == 0) {
        // 0x801E2954: lui         $at, 0x3F80
        ctx->r1 = S32(0X3F80 << 16);
            goto L_801E2970;
    }
    // 0x801E2954: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x801E2958: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x801E295C: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E2960: swc1        $f4, 0x61D8($at)
    MEM_W(0X61D8, ctx->r1) = ctx->f4.u32l;
    // 0x801E2964: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E2968: b           L_801E2994
    // 0x801E296C: sh          $zero, 0x61DC($at)
    MEM_H(0X61DC, ctx->r1) = 0;
        goto L_801E2994;
    // 0x801E296C: sh          $zero, 0x61DC($at)
    MEM_H(0X61DC, ctx->r1) = 0;
L_801E2970:
    // 0x801E2970: jal         0x801E31A0
    // 0x801E2974: nop

    func_801E31A0(rdram, ctx);
        goto after_11;
    // 0x801E2974: nop

    after_11:
    // 0x801E2978: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E297C: swc1        $f0, 0x61D8($at)
    MEM_W(0X61D8, ctx->r1) = ctx->f0.u32l;
    // 0x801E2980: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    // 0x801E2984: lui         $t1, 0x8022
    ctx->r9 = S32(0X8022 << 16);
    // 0x801E2988: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E298C: addiu       $t1, $t1, 0x61C8
    ctx->r9 = ADD32(ctx->r9, 0X61C8);
    // 0x801E2990: sh          $a0, 0x61DC($at)
    MEM_H(0X61DC, ctx->r1) = ctx->r4;
L_801E2994:
    // 0x801E2994: lui         $a3, 0x8022
    ctx->r7 = S32(0X8022 << 16);
    // 0x801E2998: addiu       $a3, $a3, 0x61C4
    ctx->r7 = ADD32(ctx->r7, 0X61C4);
    // 0x801E299C: lw          $v1, 0x0($a3)
    ctx->r3 = MEM_W(ctx->r7, 0X0);
    // 0x801E29A0: lui         $t0, 0x8023
    ctx->r8 = S32(0X8023 << 16);
    // 0x801E29A4: addiu       $t0, $t0, -0x7818
    ctx->r8 = ADD32(ctx->r8, -0X7818);
    // 0x801E29A8: addiu       $a0, $v1, 0x8
    ctx->r4 = ADD32(ctx->r3, 0X8);
    // 0x801E29AC: addiu       $t5, $zero, 0x2
    ctx->r13 = ADD32(0, 0X2);
    // 0x801E29B0: sw          $t5, 0x0($t1)
    MEM_W(0X0, ctx->r9) = ctx->r13;
    // 0x801E29B4: bgez        $a0, L_801E29C8
    if (SIGNED(ctx->r4) >= 0) {
        // 0x801E29B8: andi        $t6, $a0, 0xF
        ctx->r14 = ctx->r4 & 0XF;
            goto L_801E29C8;
    }
    // 0x801E29B8: andi        $t6, $a0, 0xF
    ctx->r14 = ctx->r4 & 0XF;
    // 0x801E29BC: beq         $t6, $zero, L_801E29C8
    if (ctx->r14 == 0) {
        // 0x801E29C0: nop
    
            goto L_801E29C8;
    }
    // 0x801E29C0: nop

    // 0x801E29C4: addiu       $t6, $t6, -0x10
    ctx->r14 = ADD32(ctx->r14, -0X10);
L_801E29C8:
    // 0x801E29C8: addiu       $t8, $t6, 0x1
    ctx->r24 = ADD32(ctx->r14, 0X1);
    // 0x801E29CC: sll         $t7, $t6, 2
    ctx->r15 = S32(ctx->r14 << 2);
    // 0x801E29D0: or          $a0, $t6, $zero
    ctx->r4 = ctx->r14 | 0;
    // 0x801E29D4: addu        $v0, $t0, $t7
    ctx->r2 = ADD32(ctx->r8, ctx->r15);
    // 0x801E29D8: bgez        $t8, L_801E29EC
    if (SIGNED(ctx->r24) >= 0) {
        // 0x801E29DC: andi        $t9, $t8, 0xF
        ctx->r25 = ctx->r24 & 0XF;
            goto L_801E29EC;
    }
    // 0x801E29DC: andi        $t9, $t8, 0xF
    ctx->r25 = ctx->r24 & 0XF;
    // 0x801E29E0: beq         $t9, $zero, L_801E29EC
    if (ctx->r25 == 0) {
        // 0x801E29E4: nop
    
            goto L_801E29EC;
    }
    // 0x801E29E4: nop

    // 0x801E29E8: addiu       $t9, $t9, -0x10
    ctx->r25 = ADD32(ctx->r25, -0X10);
L_801E29EC:
    // 0x801E29EC: sll         $t3, $t9, 2
    ctx->r11 = S32(ctx->r25 << 2);
    // 0x801E29F0: addu        $t4, $t0, $t3
    ctx->r12 = ADD32(ctx->r8, ctx->r11);
    // 0x801E29F4: lw          $t5, 0x0($t4)
    ctx->r13 = MEM_W(ctx->r12, 0X0);
    // 0x801E29F8: addiu       $t8, $v1, -0x1
    ctx->r24 = ADD32(ctx->r3, -0X1);
    // 0x801E29FC: or          $v1, $t8, $zero
    ctx->r3 = ctx->r24 | 0;
    // 0x801E2A00: addiu       $t6, $t5, -0x1
    ctx->r14 = ADD32(ctx->r13, -0X1);
    // 0x801E2A04: bgez        $t6, L_801E2A14
    if (SIGNED(ctx->r14) >= 0) {
        // 0x801E2A08: sw          $t6, 0x0($v0)
        MEM_W(0X0, ctx->r2) = ctx->r14;
            goto L_801E2A14;
    }
    // 0x801E2A08: sw          $t6, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r14;
    // 0x801E2A0C: addiu       $t7, $t6, 0x1F
    ctx->r15 = ADD32(ctx->r14, 0X1F);
    // 0x801E2A10: sw          $t7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r15;
L_801E2A14:
    // 0x801E2A14: bgez        $t8, L_801E2A24
    if (SIGNED(ctx->r24) >= 0) {
        // 0x801E2A18: sw          $t8, 0x0($a3)
        MEM_W(0X0, ctx->r7) = ctx->r24;
            goto L_801E2A24;
    }
    // 0x801E2A18: sw          $t8, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r24;
    // 0x801E2A1C: addiu       $v1, $zero, 0xF
    ctx->r3 = ADD32(0, 0XF);
    // 0x801E2A20: sw          $v1, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r3;
L_801E2A24:
    // 0x801E2A24: mtc1        $v1, $f6
    ctx->f6.u32l = ctx->r3;
    // 0x801E2A28: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E2A2C: lwc1        $f10, 0x632C($at)
    ctx->f10.u32l = MEM_W(ctx->r1, 0X632C);
    // 0x801E2A30: cvt.s.w     $f8, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    ctx->f8.fl = CVT_S_W(ctx->f6.u32l);
    // 0x801E2A34: lui         $at, 0x4180
    ctx->r1 = S32(0X4180 << 16);
    // 0x801E2A38: mtc1        $at, $f18
    ctx->f18.u32l = ctx->r1;
    // 0x801E2A3C: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E2A40: addiu       $a0, $zero, 0x2E
    ctx->r4 = ADD32(0, 0X2E);
    // 0x801E2A44: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x801E2A48: mul.s       $f16, $f8, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f16.fl = MUL_S(ctx->f8.fl, ctx->f10.fl);
    // 0x801E2A4C: div.s       $f4, $f16, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f4.fl = DIV_S(ctx->f16.fl, ctx->f18.fl);
    // 0x801E2A50: jal         0x800C37F4
    // 0x801E2A54: swc1        $f4, 0x61D4($at)
    MEM_W(0X61D4, ctx->r1) = ctx->f4.u32l;
    func_800C37F4(rdram, ctx);
        goto after_12;
    // 0x801E2A54: swc1        $f4, 0x61D4($at)
    MEM_W(0X61D4, ctx->r1) = ctx->f4.u32l;
    after_12:
    // 0x801E2A58: b           L_801E2B80
    // 0x801E2A5C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_801E2B80;
    // 0x801E2A5C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_801E2A60:
    // 0x801E2A60: bne         $v1, $zero, L_801E2A6C
    if (ctx->r3 != 0) {
        // 0x801E2A64: slti        $at, $a2, 0xD
        ctx->r1 = SIGNED(ctx->r6) < 0XD ? 1 : 0;
            goto L_801E2A6C;
    }
    // 0x801E2A64: slti        $at, $a2, 0xD
    ctx->r1 = SIGNED(ctx->r6) < 0XD ? 1 : 0;
    // 0x801E2A68: bne         $at, $zero, L_801E2B7C
    if (ctx->r1 != 0) {
        // 0x801E2A6C: addiu       $a0, $zero, 0x1
        ctx->r4 = ADD32(0, 0X1);
            goto L_801E2B7C;
    }
L_801E2A6C:
    // 0x801E2A6C: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    // 0x801E2A70: bnel        $a0, $v0, L_801E2B80
    if (ctx->r4 != ctx->r2) {
        // 0x801E2A74: lw          $ra, 0x14($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X14);
            goto L_801E2B80;
    }
    goto skip_5;
    // 0x801E2A74: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    skip_5:
    // 0x801E2A78: beq         $v1, $zero, L_801E2A98
    if (ctx->r3 == 0) {
        // 0x801E2A7C: lui         $at, 0x3F80
        ctx->r1 = S32(0X3F80 << 16);
            goto L_801E2A98;
    }
    // 0x801E2A7C: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x801E2A80: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x801E2A84: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E2A88: swc1        $f6, 0x61D8($at)
    MEM_W(0X61D8, ctx->r1) = ctx->f6.u32l;
    // 0x801E2A8C: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E2A90: b           L_801E2ABC
    // 0x801E2A94: sh          $zero, 0x61DC($at)
    MEM_H(0X61DC, ctx->r1) = 0;
        goto L_801E2ABC;
    // 0x801E2A94: sh          $zero, 0x61DC($at)
    MEM_H(0X61DC, ctx->r1) = 0;
L_801E2A98:
    // 0x801E2A98: jal         0x801E31A0
    // 0x801E2A9C: nop

    func_801E31A0(rdram, ctx);
        goto after_13;
    // 0x801E2A9C: nop

    after_13:
    // 0x801E2AA0: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E2AA4: swc1        $f0, 0x61D8($at)
    MEM_W(0X61D8, ctx->r1) = ctx->f0.u32l;
    // 0x801E2AA8: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    // 0x801E2AAC: lui         $t1, 0x8022
    ctx->r9 = S32(0X8022 << 16);
    // 0x801E2AB0: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E2AB4: addiu       $t1, $t1, 0x61C8
    ctx->r9 = ADD32(ctx->r9, 0X61C8);
    // 0x801E2AB8: sh          $a0, 0x61DC($at)
    MEM_H(0X61DC, ctx->r1) = ctx->r4;
L_801E2ABC:
    // 0x801E2ABC: lui         $a3, 0x8022
    ctx->r7 = S32(0X8022 << 16);
    // 0x801E2AC0: addiu       $a3, $a3, 0x61C4
    ctx->r7 = ADD32(ctx->r7, 0X61C4);
    // 0x801E2AC4: lw          $v1, 0x0($a3)
    ctx->r3 = MEM_W(ctx->r7, 0X0);
    // 0x801E2AC8: addiu       $t3, $zero, 0x3
    ctx->r11 = ADD32(0, 0X3);
    // 0x801E2ACC: sw          $t3, 0x0($t1)
    MEM_W(0X0, ctx->r9) = ctx->r11;
    // 0x801E2AD0: addiu       $a0, $v1, 0x8
    ctx->r4 = ADD32(ctx->r3, 0X8);
    // 0x801E2AD4: bgez        $a0, L_801E2AE8
    if (SIGNED(ctx->r4) >= 0) {
        // 0x801E2AD8: andi        $t4, $a0, 0xF
        ctx->r12 = ctx->r4 & 0XF;
            goto L_801E2AE8;
    }
    // 0x801E2AD8: andi        $t4, $a0, 0xF
    ctx->r12 = ctx->r4 & 0XF;
    // 0x801E2ADC: beq         $t4, $zero, L_801E2AE8
    if (ctx->r12 == 0) {
        // 0x801E2AE0: nop
    
            goto L_801E2AE8;
    }
    // 0x801E2AE0: nop

    // 0x801E2AE4: addiu       $t4, $t4, -0x10
    ctx->r12 = ADD32(ctx->r12, -0X10);
L_801E2AE8:
    // 0x801E2AE8: addiu       $v0, $t4, -0x1
    ctx->r2 = ADD32(ctx->r12, -0X1);
    // 0x801E2AEC: or          $a0, $t4, $zero
    ctx->r4 = ctx->r12 | 0;
    // 0x801E2AF0: bgez        $v0, L_801E2AFC
    if (SIGNED(ctx->r2) >= 0) {
        // 0x801E2AF4: or          $a2, $v0, $zero
        ctx->r6 = ctx->r2 | 0;
            goto L_801E2AFC;
    }
    // 0x801E2AF4: or          $a2, $v0, $zero
    ctx->r6 = ctx->r2 | 0;
    // 0x801E2AF8: addiu       $a2, $v0, 0x10
    ctx->r6 = ADD32(ctx->r2, 0X10);
L_801E2AFC:
    // 0x801E2AFC: lui         $t0, 0x8023
    ctx->r8 = S32(0X8023 << 16);
    // 0x801E2B00: addiu       $t0, $t0, -0x7818
    ctx->r8 = ADD32(ctx->r8, -0X7818);
    // 0x801E2B04: sll         $t6, $a2, 2
    ctx->r14 = S32(ctx->r6 << 2);
    // 0x801E2B08: addu        $t7, $t0, $t6
    ctx->r15 = ADD32(ctx->r8, ctx->r14);
    // 0x801E2B0C: lw          $t8, 0x0($t7)
    ctx->r24 = MEM_W(ctx->r15, 0X0);
    // 0x801E2B10: sll         $t5, $a0, 2
    ctx->r13 = S32(ctx->r4 << 2);
    // 0x801E2B14: addu        $v0, $t0, $t5
    ctx->r2 = ADD32(ctx->r8, ctx->r13);
    // 0x801E2B18: addiu       $t9, $t8, 0x1
    ctx->r25 = ADD32(ctx->r24, 0X1);
    // 0x801E2B1C: slti        $at, $t9, 0x1F
    ctx->r1 = SIGNED(ctx->r25) < 0X1F ? 1 : 0;
    // 0x801E2B20: bne         $at, $zero, L_801E2B30
    if (ctx->r1 != 0) {
        // 0x801E2B24: sw          $t9, 0x0($v0)
        MEM_W(0X0, ctx->r2) = ctx->r25;
            goto L_801E2B30;
    }
    // 0x801E2B24: sw          $t9, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r25;
    // 0x801E2B28: addiu       $t3, $t9, -0x1F
    ctx->r11 = ADD32(ctx->r25, -0X1F);
    // 0x801E2B2C: sw          $t3, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r11;
L_801E2B30:
    // 0x801E2B30: addiu       $t4, $v1, 0x1
    ctx->r12 = ADD32(ctx->r3, 0X1);
    // 0x801E2B34: mtc1        $t4, $f8
    ctx->f8.u32l = ctx->r12;
    // 0x801E2B38: sw          $t4, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r12;
    // 0x801E2B3C: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E2B40: cvt.s.w     $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.fl = CVT_S_W(ctx->f8.u32l);
    // 0x801E2B44: lwc1        $f16, 0x6330($at)
    ctx->f16.u32l = MEM_W(ctx->r1, 0X6330);
    // 0x801E2B48: lui         $at, 0x4180
    ctx->r1 = S32(0X4180 << 16);
    // 0x801E2B4C: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x801E2B50: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E2B54: addiu       $a0, $zero, 0x2F
    ctx->r4 = ADD32(0, 0X2F);
    // 0x801E2B58: mul.s       $f18, $f10, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f18.fl = MUL_S(ctx->f10.fl, ctx->f16.fl);
    // 0x801E2B5C: div.s       $f6, $f18, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = DIV_S(ctx->f18.fl, ctx->f4.fl);
    // 0x801E2B60: swc1        $f6, 0x61D4($at)
    MEM_W(0X61D4, ctx->r1) = ctx->f6.u32l;
    // 0x801E2B64: slti        $at, $t4, 0x10
    ctx->r1 = SIGNED(ctx->r12) < 0X10 ? 1 : 0;
    // 0x801E2B68: bne         $at, $zero, L_801E2B74
    if (ctx->r1 != 0) {
        // 0x801E2B6C: nop
    
            goto L_801E2B74;
    }
    // 0x801E2B6C: nop

    // 0x801E2B70: sw          $zero, 0x0($a3)
    MEM_W(0X0, ctx->r7) = 0;
L_801E2B74:
    // 0x801E2B74: jal         0x800C37F4
    // 0x801E2B78: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_14;
    // 0x801E2B78: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_14:
L_801E2B7C:
    // 0x801E2B7C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_801E2B80:
    // 0x801E2B80: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x801E2B84: jr          $ra
    // 0x801E2B88: nop

    return;
    // 0x801E2B88: nop

;}
RECOMP_FUNC void func_801E2B8C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801E2B8C: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x801E2B90: addiu       $v0, $v0, -0x54DC
    ctx->r2 = ADD32(ctx->r2, -0X54DC);
    // 0x801E2B94: lw          $t6, 0x0($v0)
    ctx->r14 = MEM_W(ctx->r2, 0X0);
    // 0x801E2B98: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801E2B9C: addiu       $t7, $zero, 0x65
    ctx->r15 = ADD32(0, 0X65);
    // 0x801E2BA0: sw          $t6, -0x19CC($at)
    MEM_W(-0X19CC, ctx->r1) = ctx->r14;
    // 0x801E2BA4: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801E2BA8: sw          $a0, -0x19D0($at)
    MEM_W(-0X19D0, ctx->r1) = ctx->r4;
    // 0x801E2BAC: sw          $t7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r15;
    // 0x801E2BB0: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801E2BB4: addiu       $t8, $zero, 0x6
    ctx->r24 = ADD32(0, 0X6);
    // 0x801E2BB8: sw          $t8, -0x19C8($at)
    MEM_W(-0X19C8, ctx->r1) = ctx->r24;
    // 0x801E2BBC: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801E2BC0: addiu       $t9, $zero, 0x1
    ctx->r25 = ADD32(0, 0X1);
    // 0x801E2BC4: sw          $t9, -0x19C4($at)
    MEM_W(-0X19C4, ctx->r1) = ctx->r25;
    // 0x801E2BC8: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801E2BCC: sw          $zero, -0x19C0($at)
    MEM_W(-0X19C0, ctx->r1) = 0;
    // 0x801E2BD0: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801E2BD4: sw          $zero, -0x19BC($at)
    MEM_W(-0X19BC, ctx->r1) = 0;
    // 0x801E2BD8: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x801E2BDC: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x801E2BE0: sw          $zero, -0x54E4($at)
    MEM_W(-0X54E4, ctx->r1) = 0;
    // 0x801E2BE4: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x801E2BE8: lui         $at, 0x800D
    ctx->r1 = S32(0X800D << 16);
    // 0x801E2BEC: addiu       $t0, $zero, 0x2
    ctx->r8 = ADD32(0, 0X2);
    // 0x801E2BF0: sw          $t0, 0x461C($at)
    MEM_W(0X461C, ctx->r1) = ctx->r8;
    // 0x801E2BF4: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    // 0x801E2BF8: addiu       $a1, $zero, 0xE
    ctx->r5 = ADD32(0, 0XE);
    // 0x801E2BFC: jal         0x801E6FB0
    // 0x801E2C00: addiu       $a2, $zero, 0x14
    ctx->r6 = ADD32(0, 0X14);
    FadeTransition_SetProps(rdram, ctx);
        goto after_0;
    // 0x801E2C00: addiu       $a2, $zero, 0x14
    ctx->r6 = ADD32(0, 0X14);
    after_0:
    // 0x801E2C04: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x801E2C08: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x801E2C0C: jr          $ra
    // 0x801E2C10: nop

    return;
    // 0x801E2C10: nop

;}
RECOMP_FUNC void func_801E2C14(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801E2C14: lui         $t6, 0x8023
    ctx->r14 = S32(0X8023 << 16);
    // 0x801E2C18: lb          $t6, -0x7718($t6)
    ctx->r14 = MEM_B(ctx->r14, -0X7718);
    // 0x801E2C1C: addiu       $sp, $sp, -0x38
    ctx->r29 = ADD32(ctx->r29, -0X38);
    // 0x801E2C20: sw          $s2, 0xC($sp)
    MEM_W(0XC, ctx->r29) = ctx->r18;
    // 0x801E2C24: sw          $s1, 0x8($sp)
    MEM_W(0X8, ctx->r29) = ctx->r17;
    // 0x801E2C28: bne         $t6, $zero, L_801E2C84
    if (ctx->r14 != 0) {
        // 0x801E2C2C: sw          $s0, 0x4($sp)
        MEM_W(0X4, ctx->r29) = ctx->r16;
            goto L_801E2C84;
    }
    // 0x801E2C2C: sw          $s0, 0x4($sp)
    MEM_W(0X4, ctx->r29) = ctx->r16;
    // 0x801E2C30: lui         $t7, 0x800E
    ctx->r15 = S32(0X800E << 16);
    // 0x801E2C34: lw          $t7, -0x5650($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X5650);
    // 0x801E2C38: lui         $t9, 0x801D
    ctx->r25 = S32(0X801D << 16);
    // 0x801E2C3C: addiu       $t9, $t9, -0x4D68
    ctx->r25 = ADD32(ctx->r25, -0X4D68);
    // 0x801E2C40: sll         $t8, $t7, 3
    ctx->r24 = S32(ctx->r15 << 3);
    // 0x801E2C44: subu        $t8, $t8, $t7
    ctx->r24 = SUB32(ctx->r24, ctx->r15);
    // 0x801E2C48: sll         $t8, $t8, 1
    ctx->r24 = S32(ctx->r24 << 1);
    // 0x801E2C4C: lui         $v1, 0x8023
    ctx->r3 = S32(0X8023 << 16);
    // 0x801E2C50: lui         $v0, 0x8023
    ctx->r2 = S32(0X8023 << 16);
    // 0x801E2C54: addiu       $v0, $v0, -0x7715
    ctx->r2 = ADD32(ctx->r2, -0X7715);
    // 0x801E2C58: addiu       $v1, $v1, -0x7718
    ctx->r3 = ADD32(ctx->r3, -0X7718);
    // 0x801E2C5C: addu        $a0, $t8, $t9
    ctx->r4 = ADD32(ctx->r24, ctx->r25);
L_801E2C60:
    // 0x801E2C60: lb          $t6, 0x0($a0)
    ctx->r14 = MEM_B(ctx->r4, 0X0);
    // 0x801E2C64: addiu       $v1, $v1, 0x1
    ctx->r3 = ADD32(ctx->r3, 0X1);
    // 0x801E2C68: addiu       $a0, $a0, 0x1
    ctx->r4 = ADD32(ctx->r4, 0X1);
    // 0x801E2C6C: bne         $v1, $v0, L_801E2C60
    if (ctx->r3 != ctx->r2) {
        // 0x801E2C70: sb          $t6, -0x1($v1)
        MEM_B(-0X1, ctx->r3) = ctx->r14;
            goto L_801E2C60;
    }
    // 0x801E2C70: sb          $t6, -0x1($v1)
    MEM_B(-0X1, ctx->r3) = ctx->r14;
    // 0x801E2C74: sb          $zero, 0x0($v1)
    MEM_B(0X0, ctx->r3) = 0;
    // 0x801E2C78: addiu       $t7, $zero, 0x1
    ctx->r15 = ADD32(0, 0X1);
    // 0x801E2C7C: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x801E2C80: sh          $t7, -0x5494($at)
    MEM_H(-0X5494, ctx->r1) = ctx->r15;
L_801E2C84:
    // 0x801E2C84: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x801E2C88: lw          $v0, -0x19F8($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X19F8);
    // 0x801E2C8C: addiu       $at, $zero, 0x4
    ctx->r1 = ADD32(0, 0X4);
    // 0x801E2C90: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x801E2C94: bnel        $v0, $at, L_801E2ED8
    if (ctx->r2 != ctx->r1) {
        // 0x801E2C98: addiu       $at, $zero, 0xB
        ctx->r1 = ADD32(0, 0XB);
            goto L_801E2ED8;
    }
    goto skip_0;
    // 0x801E2C98: addiu       $at, $zero, 0xB
    ctx->r1 = ADD32(0, 0XB);
    skip_0:
    // 0x801E2C9C: lw          $v1, -0x4CCC($v1)
    ctx->r3 = MEM_W(ctx->r3, -0X4CCC);
    // 0x801E2CA0: or          $t1, $zero, $zero
    ctx->r9 = 0 | 0;
    // 0x801E2CA4: lui         $t8, 0x801D
    ctx->r24 = S32(0X801D << 16);
    // 0x801E2CA8: addiu       $v1, $v1, 0x1
    ctx->r3 = ADD32(ctx->r3, 0X1);
    // 0x801E2CAC: blez        $v1, L_801E318C
    if (SIGNED(ctx->r3) <= 0) {
        // 0x801E2CB0: lui         $t6, 0x800F
        ctx->r14 = S32(0X800F << 16);
            goto L_801E318C;
    }
    // 0x801E2CB0: lui         $t6, 0x800F
    ctx->r14 = S32(0X800F << 16);
    // 0x801E2CB4: lw          $t8, -0x4CC8($t8)
    ctx->r24 = MEM_W(ctx->r24, -0X4CC8);
    // 0x801E2CB8: sll         $t7, $v1, 1
    ctx->r15 = S32(ctx->r3 << 1);
    // 0x801E2CBC: lui         $v1, 0x8023
    ctx->r3 = S32(0X8023 << 16);
    // 0x801E2CC0: addiu       $t6, $t6, -0x53EC
    ctx->r14 = ADD32(ctx->r14, -0X53EC);
    // 0x801E2CC4: lui         $s2, 0x801C
    ctx->r18 = S32(0X801C << 16);
    // 0x801E2CC8: lui         $s1, 0x801C
    ctx->r17 = S32(0X801C << 16);
    // 0x801E2CCC: lui         $s0, 0x801C
    ctx->r16 = S32(0X801C << 16);
    // 0x801E2CD0: lui         $a3, 0x801C
    ctx->r7 = S32(0X801C << 16);
    // 0x801E2CD4: lui         $a2, 0x8023
    ctx->r6 = S32(0X8023 << 16);
    // 0x801E2CD8: lui         $a1, 0x8023
    ctx->r5 = S32(0X8023 << 16);
    // 0x801E2CDC: lui         $a0, 0x8023
    ctx->r4 = S32(0X8023 << 16);
    // 0x801E2CE0: sll         $t9, $t8, 4
    ctx->r25 = S32(ctx->r24 << 4);
    // 0x801E2CE4: addu        $t2, $t9, $t6
    ctx->r10 = ADD32(ctx->r25, ctx->r14);
    // 0x801E2CE8: lb          $a0, -0x7716($a0)
    ctx->r4 = MEM_B(ctx->r4, -0X7716);
    // 0x801E2CEC: lb          $a1, -0x7718($a1)
    ctx->r5 = MEM_B(ctx->r5, -0X7718);
    // 0x801E2CF0: lb          $a2, -0x7717($a2)
    ctx->r6 = MEM_B(ctx->r6, -0X7717);
    // 0x801E2CF4: addiu       $a3, $a3, 0x2660
    ctx->r7 = ADD32(ctx->r7, 0X2660);
    // 0x801E2CF8: addiu       $s0, $s0, 0x23B0
    ctx->r16 = ADD32(ctx->r16, 0X23B0);
    // 0x801E2CFC: addiu       $s1, $s1, 0x1FF0
    ctx->r17 = ADD32(ctx->r17, 0X1FF0);
    // 0x801E2D00: addiu       $s2, $s2, 0x22C0
    ctx->r18 = ADD32(ctx->r18, 0X22C0);
    // 0x801E2D04: lb          $v1, -0x7715($v1)
    ctx->r3 = MEM_B(ctx->r3, -0X7715);
    // 0x801E2D08: sw          $t7, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r15;
    // 0x801E2D0C: lh          $t0, 0x0($t2)
    ctx->r8 = MEM_H(ctx->r10, 0X0);
L_801E2D10:
    // 0x801E2D10: lui         $t5, 0x800E
    ctx->r13 = S32(0X800E << 16);
    // 0x801E2D14: sll         $t3, $t0, 2
    ctx->r11 = S32(ctx->r8 << 2);
    // 0x801E2D18: addu        $t8, $a3, $t3
    ctx->r24 = ADD32(ctx->r7, ctx->r11);
    // 0x801E2D1C: lw          $t4, 0x0($t8)
    ctx->r12 = MEM_W(ctx->r24, 0X0);
    // 0x801E2D20: beq         $t4, $zero, L_801E2E78
    if (ctx->r12 == 0) {
        // 0x801E2D24: nop
    
            goto L_801E2E78;
    }
    // 0x801E2D24: nop

    // 0x801E2D28: lh          $t5, -0x5498($t5)
    ctx->r13 = MEM_H(ctx->r13, -0X5498);
    // 0x801E2D2C: sll         $t7, $t0, 4
    ctx->r15 = S32(ctx->r8 << 4);
    // 0x801E2D30: subu        $t7, $t7, $t0
    ctx->r15 = SUB32(ctx->r15, ctx->r8);
    // 0x801E2D34: beq         $t5, $zero, L_801E2D54
    if (ctx->r13 == 0) {
        // 0x801E2D38: sll         $t7, $t7, 2
        ctx->r15 = S32(ctx->r15 << 2);
            goto L_801E2D54;
    }
    // 0x801E2D38: sll         $t7, $t7, 2
    ctx->r15 = S32(ctx->r15 << 2);
    // 0x801E2D3C: sll         $t9, $t0, 2
    ctx->r25 = S32(ctx->r8 << 2);
    // 0x801E2D40: addu        $t9, $t9, $t0
    ctx->r25 = ADD32(ctx->r25, ctx->r8);
    // 0x801E2D44: sll         $t9, $t9, 2
    ctx->r25 = S32(ctx->r25 << 2);
    // 0x801E2D48: addu        $t6, $s0, $t9
    ctx->r14 = ADD32(ctx->r16, ctx->r25);
    // 0x801E2D4C: b           L_801E2D6C
    // 0x801E2D50: sb          $a1, 0x10($t6)
    MEM_B(0X10, ctx->r14) = ctx->r5;
        goto L_801E2D6C;
    // 0x801E2D50: sb          $a1, 0x10($t6)
    MEM_B(0X10, ctx->r14) = ctx->r5;
L_801E2D54:
    // 0x801E2D54: sll         $t9, $t4, 2
    ctx->r25 = S32(ctx->r12 << 2);
    // 0x801E2D58: addu        $t9, $t9, $t4
    ctx->r25 = ADD32(ctx->r25, ctx->r12);
    // 0x801E2D5C: sll         $t9, $t9, 2
    ctx->r25 = S32(ctx->r25 << 2);
    // 0x801E2D60: addu        $t8, $s1, $t7
    ctx->r24 = ADD32(ctx->r17, ctx->r15);
    // 0x801E2D64: addu        $t6, $t8, $t9
    ctx->r14 = ADD32(ctx->r24, ctx->r25);
    // 0x801E2D68: sb          $a1, -0x4($t6)
    MEM_B(-0X4, ctx->r14) = ctx->r5;
L_801E2D6C:
    // 0x801E2D6C: beq         $t5, $zero, L_801E2D8C
    if (ctx->r13 == 0) {
        // 0x801E2D70: sll         $t9, $t0, 4
        ctx->r25 = S32(ctx->r8 << 4);
            goto L_801E2D8C;
    }
    // 0x801E2D70: sll         $t9, $t0, 4
    ctx->r25 = S32(ctx->r8 << 4);
    // 0x801E2D74: sll         $t7, $t0, 2
    ctx->r15 = S32(ctx->r8 << 2);
    // 0x801E2D78: addu        $t7, $t7, $t0
    ctx->r15 = ADD32(ctx->r15, ctx->r8);
    // 0x801E2D7C: sll         $t7, $t7, 2
    ctx->r15 = S32(ctx->r15 << 2);
    // 0x801E2D80: addu        $t8, $s0, $t7
    ctx->r24 = ADD32(ctx->r16, ctx->r15);
    // 0x801E2D84: b           L_801E2DAC
    // 0x801E2D88: sb          $a2, 0x11($t8)
    MEM_B(0X11, ctx->r24) = ctx->r6;
        goto L_801E2DAC;
    // 0x801E2D88: sb          $a2, 0x11($t8)
    MEM_B(0X11, ctx->r24) = ctx->r6;
L_801E2D8C:
    // 0x801E2D8C: subu        $t9, $t9, $t0
    ctx->r25 = SUB32(ctx->r25, ctx->r8);
    // 0x801E2D90: sll         $t7, $t4, 2
    ctx->r15 = S32(ctx->r12 << 2);
    // 0x801E2D94: addu        $t7, $t7, $t4
    ctx->r15 = ADD32(ctx->r15, ctx->r12);
    // 0x801E2D98: sll         $t9, $t9, 2
    ctx->r25 = S32(ctx->r25 << 2);
    // 0x801E2D9C: addu        $t6, $s1, $t9
    ctx->r14 = ADD32(ctx->r17, ctx->r25);
    // 0x801E2DA0: sll         $t7, $t7, 2
    ctx->r15 = S32(ctx->r15 << 2);
    // 0x801E2DA4: addu        $t8, $t6, $t7
    ctx->r24 = ADD32(ctx->r14, ctx->r15);
    // 0x801E2DA8: sb          $a2, -0x3($t8)
    MEM_B(-0X3, ctx->r24) = ctx->r6;
L_801E2DAC:
    // 0x801E2DAC: beq         $t5, $zero, L_801E2DCC
    if (ctx->r13 == 0) {
        // 0x801E2DB0: sll         $t7, $t0, 4
        ctx->r15 = S32(ctx->r8 << 4);
            goto L_801E2DCC;
    }
    // 0x801E2DB0: sll         $t7, $t0, 4
    ctx->r15 = S32(ctx->r8 << 4);
    // 0x801E2DB4: sll         $t9, $t0, 2
    ctx->r25 = S32(ctx->r8 << 2);
    // 0x801E2DB8: addu        $t9, $t9, $t0
    ctx->r25 = ADD32(ctx->r25, ctx->r8);
    // 0x801E2DBC: sll         $t9, $t9, 2
    ctx->r25 = S32(ctx->r25 << 2);
    // 0x801E2DC0: addu        $t6, $s0, $t9
    ctx->r14 = ADD32(ctx->r16, ctx->r25);
    // 0x801E2DC4: b           L_801E2DEC
    // 0x801E2DC8: sb          $a0, 0x12($t6)
    MEM_B(0X12, ctx->r14) = ctx->r4;
        goto L_801E2DEC;
    // 0x801E2DC8: sb          $a0, 0x12($t6)
    MEM_B(0X12, ctx->r14) = ctx->r4;
L_801E2DCC:
    // 0x801E2DCC: subu        $t7, $t7, $t0
    ctx->r15 = SUB32(ctx->r15, ctx->r8);
    // 0x801E2DD0: sll         $t9, $t4, 2
    ctx->r25 = S32(ctx->r12 << 2);
    // 0x801E2DD4: addu        $t9, $t9, $t4
    ctx->r25 = ADD32(ctx->r25, ctx->r12);
    // 0x801E2DD8: sll         $t7, $t7, 2
    ctx->r15 = S32(ctx->r15 << 2);
    // 0x801E2DDC: addu        $t8, $s1, $t7
    ctx->r24 = ADD32(ctx->r17, ctx->r15);
    // 0x801E2DE0: sll         $t9, $t9, 2
    ctx->r25 = S32(ctx->r25 << 2);
    // 0x801E2DE4: addu        $t6, $t8, $t9
    ctx->r14 = ADD32(ctx->r24, ctx->r25);
    // 0x801E2DE8: sb          $a0, -0x2($t6)
    MEM_B(-0X2, ctx->r14) = ctx->r4;
L_801E2DEC:
    // 0x801E2DEC: beq         $t5, $zero, L_801E2E0C
    if (ctx->r13 == 0) {
        // 0x801E2DF0: sll         $t9, $t0, 4
        ctx->r25 = S32(ctx->r8 << 4);
            goto L_801E2E0C;
    }
    // 0x801E2DF0: sll         $t9, $t0, 4
    ctx->r25 = S32(ctx->r8 << 4);
    // 0x801E2DF4: sll         $t7, $t0, 2
    ctx->r15 = S32(ctx->r8 << 2);
    // 0x801E2DF8: addu        $t7, $t7, $t0
    ctx->r15 = ADD32(ctx->r15, ctx->r8);
    // 0x801E2DFC: sll         $t7, $t7, 2
    ctx->r15 = S32(ctx->r15 << 2);
    // 0x801E2E00: addu        $t8, $s0, $t7
    ctx->r24 = ADD32(ctx->r16, ctx->r15);
    // 0x801E2E04: b           L_801E2E2C
    // 0x801E2E08: sb          $v1, 0x13($t8)
    MEM_B(0X13, ctx->r24) = ctx->r3;
        goto L_801E2E2C;
    // 0x801E2E08: sb          $v1, 0x13($t8)
    MEM_B(0X13, ctx->r24) = ctx->r3;
L_801E2E0C:
    // 0x801E2E0C: subu        $t9, $t9, $t0
    ctx->r25 = SUB32(ctx->r25, ctx->r8);
    // 0x801E2E10: sll         $t7, $t4, 2
    ctx->r15 = S32(ctx->r12 << 2);
    // 0x801E2E14: addu        $t7, $t7, $t4
    ctx->r15 = ADD32(ctx->r15, ctx->r12);
    // 0x801E2E18: sll         $t9, $t9, 2
    ctx->r25 = S32(ctx->r25 << 2);
    // 0x801E2E1C: addu        $t6, $s1, $t9
    ctx->r14 = ADD32(ctx->r17, ctx->r25);
    // 0x801E2E20: sll         $t7, $t7, 2
    ctx->r15 = S32(ctx->r15 << 2);
    // 0x801E2E24: addu        $t8, $t6, $t7
    ctx->r24 = ADD32(ctx->r14, ctx->r15);
    // 0x801E2E28: sb          $v1, -0x1($t8)
    MEM_B(-0X1, ctx->r24) = ctx->r3;
L_801E2E2C:
    // 0x801E2E2C: beq         $t5, $zero, L_801E2E50
    if (ctx->r13 == 0) {
        // 0x801E2E30: addiu       $v0, $zero, 0x4
        ctx->r2 = ADD32(0, 0X4);
            goto L_801E2E50;
    }
    // 0x801E2E30: addiu       $v0, $zero, 0x4
    ctx->r2 = ADD32(0, 0X4);
    // 0x801E2E34: sll         $t9, $t0, 2
    ctx->r25 = S32(ctx->r8 << 2);
    // 0x801E2E38: addu        $t9, $t9, $t0
    ctx->r25 = ADD32(ctx->r25, ctx->r8);
    // 0x801E2E3C: sll         $t9, $t9, 2
    ctx->r25 = S32(ctx->r25 << 2);
    // 0x801E2E40: addu        $t6, $s0, $t9
    ctx->r14 = ADD32(ctx->r16, ctx->r25);
    // 0x801E2E44: addu        $t7, $t6, $v0
    ctx->r15 = ADD32(ctx->r14, ctx->r2);
    // 0x801E2E48: b           L_801E2E78
    // 0x801E2E4C: sb          $zero, 0x10($t7)
    MEM_B(0X10, ctx->r15) = 0;
        goto L_801E2E78;
    // 0x801E2E4C: sb          $zero, 0x10($t7)
    MEM_B(0X10, ctx->r15) = 0;
L_801E2E50:
    // 0x801E2E50: sll         $t8, $t0, 4
    ctx->r24 = S32(ctx->r8 << 4);
    // 0x801E2E54: subu        $t8, $t8, $t0
    ctx->r24 = SUB32(ctx->r24, ctx->r8);
    // 0x801E2E58: sll         $t6, $t4, 2
    ctx->r14 = S32(ctx->r12 << 2);
    // 0x801E2E5C: addu        $t6, $t6, $t4
    ctx->r14 = ADD32(ctx->r14, ctx->r12);
    // 0x801E2E60: sll         $t8, $t8, 2
    ctx->r24 = S32(ctx->r24 << 2);
    // 0x801E2E64: addu        $t9, $s1, $t8
    ctx->r25 = ADD32(ctx->r17, ctx->r24);
    // 0x801E2E68: sll         $t6, $t6, 2
    ctx->r14 = S32(ctx->r14 << 2);
    // 0x801E2E6C: addu        $t7, $t9, $t6
    ctx->r15 = ADD32(ctx->r25, ctx->r14);
    // 0x801E2E70: addu        $t8, $t7, $v0
    ctx->r24 = ADD32(ctx->r15, ctx->r2);
    // 0x801E2E74: sb          $zero, -0x4($t8)
    MEM_B(-0X4, ctx->r24) = 0;
L_801E2E78:
    // 0x801E2E78: lui         $t9, 0x801C
    ctx->r25 = S32(0X801C << 16);
    // 0x801E2E7C: addu        $t9, $t9, $t3
    ctx->r25 = ADD32(ctx->r25, ctx->r11);
    // 0x801E2E80: lw          $t9, 0x2690($t9)
    ctx->r25 = MEM_W(ctx->r25, 0X2690);
    // 0x801E2E84: sll         $t6, $t0, 2
    ctx->r14 = S32(ctx->r8 << 2);
    // 0x801E2E88: addu        $t6, $t6, $t0
    ctx->r14 = ADD32(ctx->r14, ctx->r8);
    // 0x801E2E8C: beq         $t9, $zero, L_801E2EB4
    if (ctx->r25 == 0) {
        // 0x801E2E90: sll         $t6, $t6, 2
        ctx->r14 = S32(ctx->r14 << 2);
            goto L_801E2EB4;
    }
    // 0x801E2E90: sll         $t6, $t6, 2
    ctx->r14 = S32(ctx->r14 << 2);
    // 0x801E2E94: addu        $t3, $s2, $t6
    ctx->r11 = ADD32(ctx->r18, ctx->r14);
    // 0x801E2E98: addiu       $v0, $zero, 0x4
    ctx->r2 = ADD32(0, 0X4);
    // 0x801E2E9C: sb          $a2, 0x11($t3)
    MEM_B(0X11, ctx->r11) = ctx->r6;
    // 0x801E2EA0: sb          $a0, 0x12($t3)
    MEM_B(0X12, ctx->r11) = ctx->r4;
    // 0x801E2EA4: sb          $v1, 0x13($t3)
    MEM_B(0X13, ctx->r11) = ctx->r3;
    // 0x801E2EA8: sb          $a1, 0x10($t3)
    MEM_B(0X10, ctx->r11) = ctx->r5;
    // 0x801E2EAC: addu        $t7, $t3, $v0
    ctx->r15 = ADD32(ctx->r11, ctx->r2);
    // 0x801E2EB0: sb          $zero, 0x10($t7)
    MEM_B(0X10, ctx->r15) = 0;
L_801E2EB4:
    // 0x801E2EB4: lw          $t8, 0x10($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X10);
    // 0x801E2EB8: addiu       $t1, $t1, 0x2
    ctx->r9 = ADD32(ctx->r9, 0X2);
    // 0x801E2EBC: addiu       $t2, $t2, 0x2
    ctx->r10 = ADD32(ctx->r10, 0X2);
    // 0x801E2EC0: slt         $at, $t1, $t8
    ctx->r1 = SIGNED(ctx->r9) < SIGNED(ctx->r24) ? 1 : 0;
    // 0x801E2EC4: bnel        $at, $zero, L_801E2D10
    if (ctx->r1 != 0) {
        // 0x801E2EC8: lh          $t0, 0x0($t2)
        ctx->r8 = MEM_H(ctx->r10, 0X0);
            goto L_801E2D10;
    }
    goto skip_1;
    // 0x801E2EC8: lh          $t0, 0x0($t2)
    ctx->r8 = MEM_H(ctx->r10, 0X0);
    skip_1:
    // 0x801E2ECC: b           L_801E3190
    // 0x801E2ED0: lw          $s0, 0x4($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X4);
        goto L_801E3190;
    // 0x801E2ED0: lw          $s0, 0x4($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X4);
    // 0x801E2ED4: addiu       $at, $zero, 0xB
    ctx->r1 = ADD32(0, 0XB);
L_801E2ED8:
    // 0x801E2ED8: bne         $v0, $at, L_801E2F54
    if (ctx->r2 != ctx->r1) {
        // 0x801E2EDC: lui         $t0, 0x800E
        ctx->r8 = S32(0X800E << 16);
            goto L_801E2F54;
    }
    // 0x801E2EDC: lui         $t0, 0x800E
    ctx->r8 = S32(0X800E << 16);
    // 0x801E2EE0: lui         $a3, 0x801C
    ctx->r7 = S32(0X801C << 16);
    // 0x801E2EE4: lw          $a3, 0x2928($a3)
    ctx->r7 = MEM_W(ctx->r7, 0X2928);
    // 0x801E2EE8: lui         $v1, 0x8023
    ctx->r3 = S32(0X8023 << 16);
    // 0x801E2EEC: lui         $a0, 0x8023
    ctx->r4 = S32(0X8023 << 16);
    // 0x801E2EF0: beq         $a3, $zero, L_801E318C
    if (ctx->r7 == 0) {
        // 0x801E2EF4: lui         $a1, 0x8023
        ctx->r5 = S32(0X8023 << 16);
            goto L_801E318C;
    }
    // 0x801E2EF4: lui         $a1, 0x8023
    ctx->r5 = S32(0X8023 << 16);
    // 0x801E2EF8: lui         $t9, 0x800E
    ctx->r25 = S32(0X800E << 16);
    // 0x801E2EFC: lw          $t9, -0x7E90($t9)
    ctx->r25 = MEM_W(ctx->r25, -0X7E90);
    // 0x801E2F00: sll         $t7, $a3, 4
    ctx->r15 = S32(ctx->r7 << 4);
    // 0x801E2F04: lui         $a2, 0x8023
    ctx->r6 = S32(0X8023 << 16);
    // 0x801E2F08: sll         $t6, $t9, 2
    ctx->r14 = S32(ctx->r25 << 2);
    // 0x801E2F0C: subu        $t6, $t6, $t9
    ctx->r14 = SUB32(ctx->r14, ctx->r25);
    // 0x801E2F10: sll         $t6, $t6, 4
    ctx->r14 = S32(ctx->r14 << 4);
    // 0x801E2F14: lui         $t9, 0x801C
    ctx->r25 = S32(0X801C << 16);
    // 0x801E2F18: addiu       $t9, $t9, 0x26E8
    ctx->r25 = ADD32(ctx->r25, 0X26E8);
    // 0x801E2F1C: addu        $t8, $t6, $t7
    ctx->r24 = ADD32(ctx->r14, ctx->r15);
    // 0x801E2F20: addu        $t0, $t8, $t9
    ctx->r8 = ADD32(ctx->r24, ctx->r25);
    // 0x801E2F24: lb          $a2, -0x7717($a2)
    ctx->r6 = MEM_B(ctx->r6, -0X7717);
    // 0x801E2F28: lb          $v1, -0x7715($v1)
    ctx->r3 = MEM_B(ctx->r3, -0X7715);
    // 0x801E2F2C: lb          $a0, -0x7716($a0)
    ctx->r4 = MEM_B(ctx->r4, -0X7716);
    // 0x801E2F30: lb          $a1, -0x7718($a1)
    ctx->r5 = MEM_B(ctx->r5, -0X7718);
    // 0x801E2F34: addiu       $v0, $zero, 0x4
    ctx->r2 = ADD32(0, 0X4);
    // 0x801E2F38: addu        $t6, $t0, $v0
    ctx->r14 = ADD32(ctx->r8, ctx->r2);
    // 0x801E2F3C: sb          $a2, -0x3($t0)
    MEM_B(-0X3, ctx->r8) = ctx->r6;
    // 0x801E2F40: sb          $v1, -0x1($t0)
    MEM_B(-0X1, ctx->r8) = ctx->r3;
    // 0x801E2F44: sb          $a0, -0x2($t0)
    MEM_B(-0X2, ctx->r8) = ctx->r4;
    // 0x801E2F48: sb          $a1, -0x4($t0)
    MEM_B(-0X4, ctx->r8) = ctx->r5;
    // 0x801E2F4C: b           L_801E318C
    // 0x801E2F50: sb          $zero, -0x4($t6)
    MEM_B(-0X4, ctx->r14) = 0;
        goto L_801E318C;
    // 0x801E2F50: sb          $zero, -0x4($t6)
    MEM_B(-0X4, ctx->r14) = 0;
L_801E2F54:
    // 0x801E2F54: lw          $t0, -0x7E90($t0)
    ctx->r8 = MEM_W(ctx->r8, -0X7E90);
    // 0x801E2F58: lui         $a3, 0x801C
    ctx->r7 = S32(0X801C << 16);
    // 0x801E2F5C: addiu       $a3, $a3, 0x2660
    ctx->r7 = ADD32(ctx->r7, 0X2660);
    // 0x801E2F60: sll         $t1, $t0, 2
    ctx->r9 = S32(ctx->r8 << 2);
    // 0x801E2F64: addu        $t7, $a3, $t1
    ctx->r15 = ADD32(ctx->r7, ctx->r9);
    // 0x801E2F68: lw          $t2, 0x0($t7)
    ctx->r10 = MEM_W(ctx->r15, 0X0);
    // 0x801E2F6C: lui         $t5, 0x800E
    ctx->r13 = S32(0X800E << 16);
    // 0x801E2F70: beq         $t2, $zero, L_801E3128
    if (ctx->r10 == 0) {
        // 0x801E2F74: nop
    
            goto L_801E3128;
    }
    // 0x801E2F74: nop

    // 0x801E2F78: lh          $t5, -0x5498($t5)
    ctx->r13 = MEM_H(ctx->r13, -0X5498);
    // 0x801E2F7C: lui         $s0, 0x801C
    ctx->r16 = S32(0X801C << 16);
    // 0x801E2F80: addiu       $s0, $s0, 0x23B0
    ctx->r16 = ADD32(ctx->r16, 0X23B0);
    // 0x801E2F84: beq         $t5, $zero, L_801E2FB0
    if (ctx->r13 == 0) {
        // 0x801E2F88: lui         $a1, 0x8023
        ctx->r5 = S32(0X8023 << 16);
            goto L_801E2FB0;
    }
    // 0x801E2F88: lui         $a1, 0x8023
    ctx->r5 = S32(0X8023 << 16);
    // 0x801E2F8C: sll         $t8, $t0, 2
    ctx->r24 = S32(ctx->r8 << 2);
    // 0x801E2F90: addu        $t8, $t8, $t0
    ctx->r24 = ADD32(ctx->r24, ctx->r8);
    // 0x801E2F94: lb          $a1, -0x7718($a1)
    ctx->r5 = MEM_B(ctx->r5, -0X7718);
    // 0x801E2F98: sll         $t8, $t8, 2
    ctx->r24 = S32(ctx->r24 << 2);
    // 0x801E2F9C: addu        $t9, $s0, $t8
    ctx->r25 = ADD32(ctx->r16, ctx->r24);
    // 0x801E2FA0: lui         $s1, 0x801C
    ctx->r17 = S32(0X801C << 16);
    // 0x801E2FA4: addiu       $s1, $s1, 0x1FF0
    ctx->r17 = ADD32(ctx->r17, 0X1FF0);
    // 0x801E2FA8: b           L_801E2FEC
    // 0x801E2FAC: sb          $a1, 0x10($t9)
    MEM_B(0X10, ctx->r25) = ctx->r5;
        goto L_801E2FEC;
    // 0x801E2FAC: sb          $a1, 0x10($t9)
    MEM_B(0X10, ctx->r25) = ctx->r5;
L_801E2FB0:
    // 0x801E2FB0: sll         $t6, $t0, 4
    ctx->r14 = S32(ctx->r8 << 4);
    // 0x801E2FB4: lui         $a1, 0x8023
    ctx->r5 = S32(0X8023 << 16);
    // 0x801E2FB8: lui         $s1, 0x801C
    ctx->r17 = S32(0X801C << 16);
    // 0x801E2FBC: subu        $t6, $t6, $t0
    ctx->r14 = SUB32(ctx->r14, ctx->r8);
    // 0x801E2FC0: sll         $t8, $t2, 2
    ctx->r24 = S32(ctx->r10 << 2);
    // 0x801E2FC4: lb          $a1, -0x7718($a1)
    ctx->r5 = MEM_B(ctx->r5, -0X7718);
    // 0x801E2FC8: addiu       $s1, $s1, 0x1FF0
    ctx->r17 = ADD32(ctx->r17, 0X1FF0);
    // 0x801E2FCC: addu        $t8, $t8, $t2
    ctx->r24 = ADD32(ctx->r24, ctx->r10);
    // 0x801E2FD0: sll         $t6, $t6, 2
    ctx->r14 = S32(ctx->r14 << 2);
    // 0x801E2FD4: addu        $t7, $s1, $t6
    ctx->r15 = ADD32(ctx->r17, ctx->r14);
    // 0x801E2FD8: sll         $t8, $t8, 2
    ctx->r24 = S32(ctx->r24 << 2);
    // 0x801E2FDC: addu        $t9, $t7, $t8
    ctx->r25 = ADD32(ctx->r15, ctx->r24);
    // 0x801E2FE0: lui         $s0, 0x801C
    ctx->r16 = S32(0X801C << 16);
    // 0x801E2FE4: addiu       $s0, $s0, 0x23B0
    ctx->r16 = ADD32(ctx->r16, 0X23B0);
    // 0x801E2FE8: sb          $a1, -0x4($t9)
    MEM_B(-0X4, ctx->r25) = ctx->r5;
L_801E2FEC:
    // 0x801E2FEC: beq         $t5, $zero, L_801E3014
    if (ctx->r13 == 0) {
        // 0x801E2FF0: lui         $a2, 0x8023
        ctx->r6 = S32(0X8023 << 16);
            goto L_801E3014;
    }
    // 0x801E2FF0: lui         $a2, 0x8023
    ctx->r6 = S32(0X8023 << 16);
    // 0x801E2FF4: sll         $t6, $t0, 2
    ctx->r14 = S32(ctx->r8 << 2);
    // 0x801E2FF8: addu        $t6, $t6, $t0
    ctx->r14 = ADD32(ctx->r14, ctx->r8);
    // 0x801E2FFC: lui         $a2, 0x8023
    ctx->r6 = S32(0X8023 << 16);
    // 0x801E3000: lb          $a2, -0x7717($a2)
    ctx->r6 = MEM_B(ctx->r6, -0X7717);
    // 0x801E3004: sll         $t6, $t6, 2
    ctx->r14 = S32(ctx->r14 << 2);
    // 0x801E3008: addu        $t7, $s0, $t6
    ctx->r15 = ADD32(ctx->r16, ctx->r14);
    // 0x801E300C: b           L_801E303C
    // 0x801E3010: sb          $a2, 0x11($t7)
    MEM_B(0X11, ctx->r15) = ctx->r6;
        goto L_801E303C;
    // 0x801E3010: sb          $a2, 0x11($t7)
    MEM_B(0X11, ctx->r15) = ctx->r6;
L_801E3014:
    // 0x801E3014: sll         $t8, $t0, 4
    ctx->r24 = S32(ctx->r8 << 4);
    // 0x801E3018: subu        $t8, $t8, $t0
    ctx->r24 = SUB32(ctx->r24, ctx->r8);
    // 0x801E301C: sll         $t6, $t2, 2
    ctx->r14 = S32(ctx->r10 << 2);
    // 0x801E3020: lb          $a2, -0x7717($a2)
    ctx->r6 = MEM_B(ctx->r6, -0X7717);
    // 0x801E3024: addu        $t6, $t6, $t2
    ctx->r14 = ADD32(ctx->r14, ctx->r10);
    // 0x801E3028: sll         $t8, $t8, 2
    ctx->r24 = S32(ctx->r24 << 2);
    // 0x801E302C: addu        $t9, $s1, $t8
    ctx->r25 = ADD32(ctx->r17, ctx->r24);
    // 0x801E3030: sll         $t6, $t6, 2
    ctx->r14 = S32(ctx->r14 << 2);
    // 0x801E3034: addu        $t7, $t9, $t6
    ctx->r15 = ADD32(ctx->r25, ctx->r14);
    // 0x801E3038: sb          $a2, -0x3($t7)
    MEM_B(-0X3, ctx->r15) = ctx->r6;
L_801E303C:
    // 0x801E303C: beq         $t5, $zero, L_801E3064
    if (ctx->r13 == 0) {
        // 0x801E3040: lui         $a0, 0x8023
        ctx->r4 = S32(0X8023 << 16);
            goto L_801E3064;
    }
    // 0x801E3040: lui         $a0, 0x8023
    ctx->r4 = S32(0X8023 << 16);
    // 0x801E3044: sll         $t8, $t0, 2
    ctx->r24 = S32(ctx->r8 << 2);
    // 0x801E3048: addu        $t8, $t8, $t0
    ctx->r24 = ADD32(ctx->r24, ctx->r8);
    // 0x801E304C: lui         $a0, 0x8023
    ctx->r4 = S32(0X8023 << 16);
    // 0x801E3050: lb          $a0, -0x7716($a0)
    ctx->r4 = MEM_B(ctx->r4, -0X7716);
    // 0x801E3054: sll         $t8, $t8, 2
    ctx->r24 = S32(ctx->r24 << 2);
    // 0x801E3058: addu        $t9, $s0, $t8
    ctx->r25 = ADD32(ctx->r16, ctx->r24);
    // 0x801E305C: b           L_801E308C
    // 0x801E3060: sb          $a0, 0x12($t9)
    MEM_B(0X12, ctx->r25) = ctx->r4;
        goto L_801E308C;
    // 0x801E3060: sb          $a0, 0x12($t9)
    MEM_B(0X12, ctx->r25) = ctx->r4;
L_801E3064:
    // 0x801E3064: sll         $t6, $t0, 4
    ctx->r14 = S32(ctx->r8 << 4);
    // 0x801E3068: subu        $t6, $t6, $t0
    ctx->r14 = SUB32(ctx->r14, ctx->r8);
    // 0x801E306C: sll         $t8, $t2, 2
    ctx->r24 = S32(ctx->r10 << 2);
    // 0x801E3070: lb          $a0, -0x7716($a0)
    ctx->r4 = MEM_B(ctx->r4, -0X7716);
    // 0x801E3074: addu        $t8, $t8, $t2
    ctx->r24 = ADD32(ctx->r24, ctx->r10);
    // 0x801E3078: sll         $t6, $t6, 2
    ctx->r14 = S32(ctx->r14 << 2);
    // 0x801E307C: addu        $t7, $s1, $t6
    ctx->r15 = ADD32(ctx->r17, ctx->r14);
    // 0x801E3080: sll         $t8, $t8, 2
    ctx->r24 = S32(ctx->r24 << 2);
    // 0x801E3084: addu        $t9, $t7, $t8
    ctx->r25 = ADD32(ctx->r15, ctx->r24);
    // 0x801E3088: sb          $a0, -0x2($t9)
    MEM_B(-0X2, ctx->r25) = ctx->r4;
L_801E308C:
    // 0x801E308C: beq         $t5, $zero, L_801E30B4
    if (ctx->r13 == 0) {
        // 0x801E3090: lui         $v1, 0x8023
        ctx->r3 = S32(0X8023 << 16);
            goto L_801E30B4;
    }
    // 0x801E3090: lui         $v1, 0x8023
    ctx->r3 = S32(0X8023 << 16);
    // 0x801E3094: sll         $t6, $t0, 2
    ctx->r14 = S32(ctx->r8 << 2);
    // 0x801E3098: addu        $t6, $t6, $t0
    ctx->r14 = ADD32(ctx->r14, ctx->r8);
    // 0x801E309C: lui         $v1, 0x8023
    ctx->r3 = S32(0X8023 << 16);
    // 0x801E30A0: lb          $v1, -0x7715($v1)
    ctx->r3 = MEM_B(ctx->r3, -0X7715);
    // 0x801E30A4: sll         $t6, $t6, 2
    ctx->r14 = S32(ctx->r14 << 2);
    // 0x801E30A8: addu        $t7, $s0, $t6
    ctx->r15 = ADD32(ctx->r16, ctx->r14);
    // 0x801E30AC: b           L_801E30DC
    // 0x801E30B0: sb          $v1, 0x13($t7)
    MEM_B(0X13, ctx->r15) = ctx->r3;
        goto L_801E30DC;
    // 0x801E30B0: sb          $v1, 0x13($t7)
    MEM_B(0X13, ctx->r15) = ctx->r3;
L_801E30B4:
    // 0x801E30B4: sll         $t8, $t0, 4
    ctx->r24 = S32(ctx->r8 << 4);
    // 0x801E30B8: subu        $t8, $t8, $t0
    ctx->r24 = SUB32(ctx->r24, ctx->r8);
    // 0x801E30BC: sll         $t6, $t2, 2
    ctx->r14 = S32(ctx->r10 << 2);
    // 0x801E30C0: lb          $v1, -0x7715($v1)
    ctx->r3 = MEM_B(ctx->r3, -0X7715);
    // 0x801E30C4: addu        $t6, $t6, $t2
    ctx->r14 = ADD32(ctx->r14, ctx->r10);
    // 0x801E30C8: sll         $t8, $t8, 2
    ctx->r24 = S32(ctx->r24 << 2);
    // 0x801E30CC: addu        $t9, $s1, $t8
    ctx->r25 = ADD32(ctx->r17, ctx->r24);
    // 0x801E30D0: sll         $t6, $t6, 2
    ctx->r14 = S32(ctx->r14 << 2);
    // 0x801E30D4: addu        $t7, $t9, $t6
    ctx->r15 = ADD32(ctx->r25, ctx->r14);
    // 0x801E30D8: sb          $v1, -0x1($t7)
    MEM_B(-0X1, ctx->r15) = ctx->r3;
L_801E30DC:
    // 0x801E30DC: beq         $t5, $zero, L_801E3100
    if (ctx->r13 == 0) {
        // 0x801E30E0: addiu       $v0, $zero, 0x4
        ctx->r2 = ADD32(0, 0X4);
            goto L_801E3100;
    }
    // 0x801E30E0: addiu       $v0, $zero, 0x4
    ctx->r2 = ADD32(0, 0X4);
    // 0x801E30E4: sll         $t8, $t0, 2
    ctx->r24 = S32(ctx->r8 << 2);
    // 0x801E30E8: addu        $t8, $t8, $t0
    ctx->r24 = ADD32(ctx->r24, ctx->r8);
    // 0x801E30EC: sll         $t8, $t8, 2
    ctx->r24 = S32(ctx->r24 << 2);
    // 0x801E30F0: addu        $t9, $s0, $t8
    ctx->r25 = ADD32(ctx->r16, ctx->r24);
    // 0x801E30F4: addu        $t6, $t9, $v0
    ctx->r14 = ADD32(ctx->r25, ctx->r2);
    // 0x801E30F8: b           L_801E3128
    // 0x801E30FC: sb          $zero, 0x10($t6)
    MEM_B(0X10, ctx->r14) = 0;
        goto L_801E3128;
    // 0x801E30FC: sb          $zero, 0x10($t6)
    MEM_B(0X10, ctx->r14) = 0;
L_801E3100:
    // 0x801E3100: sll         $t7, $t0, 4
    ctx->r15 = S32(ctx->r8 << 4);
    // 0x801E3104: subu        $t7, $t7, $t0
    ctx->r15 = SUB32(ctx->r15, ctx->r8);
    // 0x801E3108: sll         $t9, $t2, 2
    ctx->r25 = S32(ctx->r10 << 2);
    // 0x801E310C: addu        $t9, $t9, $t2
    ctx->r25 = ADD32(ctx->r25, ctx->r10);
    // 0x801E3110: sll         $t7, $t7, 2
    ctx->r15 = S32(ctx->r15 << 2);
    // 0x801E3114: addu        $t8, $s1, $t7
    ctx->r24 = ADD32(ctx->r17, ctx->r15);
    // 0x801E3118: sll         $t9, $t9, 2
    ctx->r25 = S32(ctx->r25 << 2);
    // 0x801E311C: addu        $t6, $t8, $t9
    ctx->r14 = ADD32(ctx->r24, ctx->r25);
    // 0x801E3120: addu        $t7, $t6, $v0
    ctx->r15 = ADD32(ctx->r14, ctx->r2);
    // 0x801E3124: sb          $zero, -0x4($t7)
    MEM_B(-0X4, ctx->r15) = 0;
L_801E3128:
    // 0x801E3128: lui         $t8, 0x801C
    ctx->r24 = S32(0X801C << 16);
    // 0x801E312C: addu        $t8, $t8, $t1
    ctx->r24 = ADD32(ctx->r24, ctx->r9);
    // 0x801E3130: lw          $t8, 0x2690($t8)
    ctx->r24 = MEM_W(ctx->r24, 0X2690);
    // 0x801E3134: lui         $v1, 0x8023
    ctx->r3 = S32(0X8023 << 16);
    // 0x801E3138: lui         $a0, 0x8023
    ctx->r4 = S32(0X8023 << 16);
    // 0x801E313C: lui         $a1, 0x8023
    ctx->r5 = S32(0X8023 << 16);
    // 0x801E3140: lui         $a2, 0x8023
    ctx->r6 = S32(0X8023 << 16);
    // 0x801E3144: lb          $a2, -0x7717($a2)
    ctx->r6 = MEM_B(ctx->r6, -0X7717);
    // 0x801E3148: lb          $a1, -0x7718($a1)
    ctx->r5 = MEM_B(ctx->r5, -0X7718);
    // 0x801E314C: lb          $a0, -0x7716($a0)
    ctx->r4 = MEM_B(ctx->r4, -0X7716);
    // 0x801E3150: beq         $t8, $zero, L_801E318C
    if (ctx->r24 == 0) {
        // 0x801E3154: lb          $v1, -0x7715($v1)
        ctx->r3 = MEM_B(ctx->r3, -0X7715);
            goto L_801E318C;
    }
    // 0x801E3154: lb          $v1, -0x7715($v1)
    ctx->r3 = MEM_B(ctx->r3, -0X7715);
    // 0x801E3158: sll         $t9, $t0, 2
    ctx->r25 = S32(ctx->r8 << 2);
    // 0x801E315C: lui         $s2, 0x801C
    ctx->r18 = S32(0X801C << 16);
    // 0x801E3160: addu        $t9, $t9, $t0
    ctx->r25 = ADD32(ctx->r25, ctx->r8);
    // 0x801E3164: addiu       $s2, $s2, 0x22C0
    ctx->r18 = ADD32(ctx->r18, 0X22C0);
    // 0x801E3168: sll         $t9, $t9, 2
    ctx->r25 = S32(ctx->r25 << 2);
    // 0x801E316C: addu        $a3, $s2, $t9
    ctx->r7 = ADD32(ctx->r18, ctx->r25);
    // 0x801E3170: addiu       $v0, $zero, 0x4
    ctx->r2 = ADD32(0, 0X4);
    // 0x801E3174: sb          $a2, 0x11($a3)
    MEM_B(0X11, ctx->r7) = ctx->r6;
    // 0x801E3178: sb          $a0, 0x12($a3)
    MEM_B(0X12, ctx->r7) = ctx->r4;
    // 0x801E317C: sb          $v1, 0x13($a3)
    MEM_B(0X13, ctx->r7) = ctx->r3;
    // 0x801E3180: sb          $a1, 0x10($a3)
    MEM_B(0X10, ctx->r7) = ctx->r5;
    // 0x801E3184: addu        $t6, $a3, $v0
    ctx->r14 = ADD32(ctx->r7, ctx->r2);
    // 0x801E3188: sb          $zero, 0x10($t6)
    MEM_B(0X10, ctx->r14) = 0;
L_801E318C:
    // 0x801E318C: lw          $s0, 0x4($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X4);
L_801E3190:
    // 0x801E3190: lw          $s1, 0x8($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X8);
    // 0x801E3194: lw          $s2, 0xC($sp)
    ctx->r18 = MEM_W(ctx->r29, 0XC);
    // 0x801E3198: jr          $ra
    // 0x801E319C: addiu       $sp, $sp, 0x38
    ctx->r29 = ADD32(ctx->r29, 0X38);
    return;
    // 0x801E319C: addiu       $sp, $sp, 0x38
    ctx->r29 = ADD32(ctx->r29, 0X38);
;}
RECOMP_FUNC void func_801E31A0(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801E31A0: lui         $t6, 0x8015
    ctx->r14 = S32(0X8015 << 16);
    // 0x801E31A4: lw          $t6, 0x4330($t6)
    ctx->r14 = MEM_W(ctx->r14, 0X4330);
    // 0x801E31A8: lui         $v0, 0x8015
    ctx->r2 = S32(0X8015 << 16);
    // 0x801E31AC: sll         $t7, $t6, 2
    ctx->r15 = S32(ctx->r14 << 2);
    // 0x801E31B0: addu        $t7, $t7, $t6
    ctx->r15 = ADD32(ctx->r15, ctx->r14);
    // 0x801E31B4: sll         $t7, $t7, 1
    ctx->r15 = S32(ctx->r15 << 1);
    // 0x801E31B8: addu        $v0, $v0, $t7
    ctx->r2 = ADD32(ctx->r2, ctx->r15);
    // 0x801E31BC: lb          $v0, 0x4310($v0)
    ctx->r2 = MEM_B(ctx->r2, 0X4310);
    // 0x801E31C0: bgezl       $v0, L_801E31D0
    if (SIGNED(ctx->r2) >= 0) {
        // 0x801E31C4: slti        $at, $v0, 0x47
        ctx->r1 = SIGNED(ctx->r2) < 0X47 ? 1 : 0;
            goto L_801E31D0;
    }
    goto skip_0;
    // 0x801E31C4: slti        $at, $v0, 0x47
    ctx->r1 = SIGNED(ctx->r2) < 0X47 ? 1 : 0;
    skip_0:
    // 0x801E31C8: negu        $v0, $v0
    ctx->r2 = SUB32(0, ctx->r2);
    // 0x801E31CC: slti        $at, $v0, 0x47
    ctx->r1 = SIGNED(ctx->r2) < 0X47 ? 1 : 0;
L_801E31D0:
    // 0x801E31D0: bnel        $at, $zero, L_801E31E4
    if (ctx->r1 != 0) {
        // 0x801E31D4: slti        $at, $v0, 0xC
        ctx->r1 = SIGNED(ctx->r2) < 0XC ? 1 : 0;
            goto L_801E31E4;
    }
    goto skip_1;
    // 0x801E31D4: slti        $at, $v0, 0xC
    ctx->r1 = SIGNED(ctx->r2) < 0XC ? 1 : 0;
    skip_1:
    // 0x801E31D8: b           L_801E31F0
    // 0x801E31DC: addiu       $v0, $zero, 0x46
    ctx->r2 = ADD32(0, 0X46);
        goto L_801E31F0;
    // 0x801E31DC: addiu       $v0, $zero, 0x46
    ctx->r2 = ADD32(0, 0X46);
    // 0x801E31E0: slti        $at, $v0, 0xC
    ctx->r1 = SIGNED(ctx->r2) < 0XC ? 1 : 0;
L_801E31E4:
    // 0x801E31E4: beql        $at, $zero, L_801E31F4
    if (ctx->r1 == 0) {
        // 0x801E31E8: addiu       $v0, $v0, -0xC
        ctx->r2 = ADD32(ctx->r2, -0XC);
            goto L_801E31F4;
    }
    goto skip_2;
    // 0x801E31E8: addiu       $v0, $v0, -0xC
    ctx->r2 = ADD32(ctx->r2, -0XC);
    skip_2:
    // 0x801E31EC: addiu       $v0, $zero, 0xC
    ctx->r2 = ADD32(0, 0XC);
L_801E31F0:
    // 0x801E31F0: addiu       $v0, $v0, -0xC
    ctx->r2 = ADD32(ctx->r2, -0XC);
L_801E31F4:
    // 0x801E31F4: mtc1        $v0, $f4
    ctx->f4.u32l = ctx->r2;
    // 0x801E31F8: addiu       $t8, $zero, 0x3A
    ctx->r24 = ADD32(0, 0X3A);
    // 0x801E31FC: mtc1        $t8, $f8
    ctx->f8.u32l = ctx->r24;
    // 0x801E3200: cvt.s.w     $f0, $f4
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 4);
    ctx->f0.fl = CVT_S_W(ctx->f4.u32l);
    // 0x801E3204: lui         $at, 0x4000
    ctx->r1 = S32(0X4000 << 16);
    // 0x801E3208: mtc1        $at, $f14
    ctx->f14.u32l = ctx->r1;
    // 0x801E320C: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E3210: cvt.s.w     $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.fl = CVT_S_W(ctx->f8.u32l);
    // 0x801E3214: add.s       $f6, $f0, $f0
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f6.fl = ctx->f0.fl + ctx->f0.fl;
    // 0x801E3218: div.s       $f2, $f6, $f10
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f2.fl = DIV_S(ctx->f6.fl, ctx->f10.fl);
    // 0x801E321C: c.lt.s      $f14, $f2
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 2);
    c1cs = ctx->f14.fl < ctx->f2.fl;
    // 0x801E3220: nop

    // 0x801E3224: bc1f        L_801E3230
    if (!c1cs) {
        // 0x801E3228: nop
    
            goto L_801E3230;
    }
    // 0x801E3228: nop

    // 0x801E322C: mov.s       $f2, $f14
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 14);
    ctx->f2.fl = ctx->f14.fl;
L_801E3230:
    // 0x801E3230: lwc1        $f0, 0x6334($at)
    ctx->f0.u32l = MEM_W(ctx->r1, 0X6334);
    // 0x801E3234: c.lt.s      $f2, $f0
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 0);
    c1cs = ctx->f2.fl < ctx->f0.fl;
    // 0x801E3238: nop

    // 0x801E323C: bc1f        L_801E3248
    if (!c1cs) {
        // 0x801E3240: nop
    
            goto L_801E3248;
    }
    // 0x801E3240: nop

    // 0x801E3244: mov.s       $f2, $f0
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 0);
    ctx->f2.fl = ctx->f0.fl;
L_801E3248:
    // 0x801E3248: jr          $ra
    // 0x801E324C: mov.s       $f0, $f2
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    ctx->f0.fl = ctx->f2.fl;
    return;
    // 0x801E324C: mov.s       $f0, $f2
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    ctx->f0.fl = ctx->f2.fl;
;}
RECOMP_FUNC void func_801E3250(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801E3250: addiu       $sp, $sp, -0x1B8
    ctx->r29 = ADD32(ctx->r29, -0X1B8);
    // 0x801E3254: lui         $t6, 0x801D
    ctx->r14 = S32(0X801D << 16);
    // 0x801E3258: lw          $t6, -0x19C4($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X19C4);
    // 0x801E325C: sw          $ra, 0x5C($sp)
    MEM_W(0X5C, ctx->r29) = ctx->r31;
    // 0x801E3260: sw          $fp, 0x58($sp)
    MEM_W(0X58, ctx->r29) = ctx->r30;
    // 0x801E3264: sw          $s7, 0x54($sp)
    MEM_W(0X54, ctx->r29) = ctx->r23;
    // 0x801E3268: sw          $s6, 0x50($sp)
    MEM_W(0X50, ctx->r29) = ctx->r22;
    // 0x801E326C: sw          $s5, 0x4C($sp)
    MEM_W(0X4C, ctx->r29) = ctx->r21;
    // 0x801E3270: sw          $s4, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r20;
    // 0x801E3274: sw          $s3, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r19;
    // 0x801E3278: sw          $s2, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r18;
    // 0x801E327C: sw          $s1, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r17;
    // 0x801E3280: beq         $t6, $zero, L_801E32B0
    if (ctx->r14 == 0) {
        // 0x801E3284: sw          $s0, 0x38($sp)
        MEM_W(0X38, ctx->r29) = ctx->r16;
            goto L_801E32B0;
    }
    // 0x801E3284: sw          $s0, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r16;
    // 0x801E3288: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801E328C: sw          $zero, -0x770C($at)
    MEM_W(-0X770C, ctx->r1) = 0;
    // 0x801E3290: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801E3294: sw          $zero, -0x7710($at)
    MEM_W(-0X7710, ctx->r1) = 0;
    // 0x801E3298: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801E329C: addiu       $t7, $zero, 0x1A8
    ctx->r15 = ADD32(0, 0X1A8);
    // 0x801E32A0: sw          $t7, -0x7708($at)
    MEM_W(-0X7708, ctx->r1) = ctx->r15;
    // 0x801E32A4: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801E32A8: addiu       $t8, $zero, -0x108
    ctx->r24 = ADD32(0, -0X108);
    // 0x801E32AC: sw          $t8, -0x7704($at)
    MEM_W(-0X7704, ctx->r1) = ctx->r24;
L_801E32B0:
    // 0x801E32B0: lui         $at, 0x4180
    ctx->r1 = S32(0X4180 << 16);
    // 0x801E32B4: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x801E32B8: lui         $s5, 0x801D
    ctx->r21 = S32(0X801D << 16);
    // 0x801E32BC: mtc1        $zero, $f0
    ctx->f0.u32l = 0;
    // 0x801E32C0: addiu       $s5, $s5, -0x1A08
    ctx->r21 = ADD32(ctx->r21, -0X1A08);
    // 0x801E32C4: lui         $at, 0x4580
    ctx->r1 = S32(0X4580 << 16);
    // 0x801E32C8: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x801E32CC: lw          $a0, 0x0($s5)
    ctx->r4 = MEM_W(ctx->r21, 0X0);
    // 0x801E32D0: lui         $a1, 0x8023
    ctx->r5 = S32(0X8023 << 16);
    // 0x801E32D4: addiu       $a1, $a1, -0x7700
    ctx->r5 = ADD32(ctx->r5, -0X7700);
    // 0x801E32D8: lui         $a2, 0x4204
    ctx->r6 = S32(0X4204 << 16);
    // 0x801E32DC: lui         $a3, 0x3F80
    ctx->r7 = S32(0X3F80 << 16);
    // 0x801E32E0: swc1        $f4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f4.u32l;
    // 0x801E32E4: swc1        $f0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->f0.u32l;
    // 0x801E32E8: swc1        $f0, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->f0.u32l;
    // 0x801E32EC: addiu       $a0, $a0, 0xA40
    ctx->r4 = ADD32(ctx->r4, 0XA40);
    // 0x801E32F0: jal         0x800481E0
    // 0x801E32F4: swc1        $f6, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->f6.u32l;
    func_800481E0(rdram, ctx);
        goto after_0;
    // 0x801E32F4: swc1        $f6, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->f6.u32l;
    after_0:
    // 0x801E32F8: mtc1        $zero, $f0
    ctx->f0.u32l = 0;
    // 0x801E32FC: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x801E3300: mtc1        $at, $f2
    ctx->f2.u32l = ctx->r1;
    // 0x801E3304: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E3308: lwc1        $f8, 0x63A4($at)
    ctx->f8.u32l = MEM_W(ctx->r1, 0X63A4);
    // 0x801E330C: addiu       $s0, $sp, 0xB0
    ctx->r16 = ADD32(ctx->r29, 0XB0);
    // 0x801E3310: mfc1        $a1, $f0
    ctx->r5 = (int32_t)ctx->f0.u32l;
    // 0x801E3314: mfc1        $a2, $f0
    ctx->r6 = (int32_t)ctx->f0.u32l;
    // 0x801E3318: mfc1        $a3, $f2
    ctx->r7 = (int32_t)ctx->f2.u32l;
    // 0x801E331C: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x801E3320: swc1        $f0, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f0.u32l;
    // 0x801E3324: swc1        $f0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->f0.u32l;
    // 0x801E3328: swc1        $f0, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->f0.u32l;
    // 0x801E332C: swc1        $f0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->f0.u32l;
    // 0x801E3330: swc1        $f0, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->f0.u32l;
    // 0x801E3334: swc1        $f2, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->f2.u32l;
    // 0x801E3338: jal         0x80048A88
    // 0x801E333C: swc1        $f8, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->f8.u32l;
    func_80048A88(rdram, ctx);
        goto after_1;
    // 0x801E333C: swc1        $f8, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->f8.u32l;
    after_1:
    // 0x801E3340: mtc1        $zero, $f0
    ctx->f0.u32l = 0;
    // 0x801E3344: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x801E3348: mtc1        $at, $f10
    ctx->f10.u32l = ctx->r1;
    // 0x801E334C: addiu       $s1, $sp, 0x130
    ctx->r17 = ADD32(ctx->r29, 0X130);
    // 0x801E3350: mfc1        $a3, $f0
    ctx->r7 = (int32_t)ctx->f0.u32l;
    // 0x801E3354: or          $a1, $s1, $zero
    ctx->r5 = ctx->r17 | 0;
    // 0x801E3358: addiu       $a0, $sp, 0x70
    ctx->r4 = ADD32(ctx->r29, 0X70);
    // 0x801E335C: lui         $a2, 0x43FA
    ctx->r6 = S32(0X43FA << 16);
    // 0x801E3360: swc1        $f0, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f0.u32l;
    // 0x801E3364: swc1        $f0, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->f0.u32l;
    // 0x801E3368: swc1        $f0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->f0.u32l;
    // 0x801E336C: swc1        $f0, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->f0.u32l;
    // 0x801E3370: swc1        $f0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->f0.u32l;
    // 0x801E3374: swc1        $f0, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->f0.u32l;
    // 0x801E3378: jal         0x800484C8
    // 0x801E337C: swc1        $f10, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->f10.u32l;
    func_800484C8(rdram, ctx);
        goto after_2;
    // 0x801E337C: swc1        $f10, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->f10.u32l;
    after_2:
    // 0x801E3380: addiu       $s2, $sp, 0x170
    ctx->r18 = ADD32(ctx->r29, 0X170);
    // 0x801E3384: or          $a1, $s2, $zero
    ctx->r5 = ctx->r18 | 0;
    // 0x801E3388: jal         0x80047E78
    // 0x801E338C: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    SysUtils_MtxToMtxF(rdram, ctx);
        goto after_3;
    // 0x801E338C: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_3:
    // 0x801E3390: addiu       $fp, $sp, 0xF0
    ctx->r30 = ADD32(ctx->r29, 0XF0);
    // 0x801E3394: or          $a2, $fp, $zero
    ctx->r6 = ctx->r30 | 0;
    // 0x801E3398: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    // 0x801E339C: jal         0x80049EB8
    // 0x801E33A0: or          $a1, $s2, $zero
    ctx->r5 = ctx->r18 | 0;
    SysUtils_MatrixAffineMultiply(rdram, ctx);
        goto after_4;
    // 0x801E33A0: or          $a1, $s2, $zero
    ctx->r5 = ctx->r18 | 0;
    after_4:
    // 0x801E33A4: lui         $s7, 0x8022
    ctx->r23 = S32(0X8022 << 16);
    // 0x801E33A8: addiu       $s7, $s7, 0x6340
    ctx->r23 = ADD32(ctx->r23, 0X6340);
    // 0x801E33AC: or          $s1, $zero, $zero
    ctx->r17 = 0 | 0;
    // 0x801E33B0: or          $s3, $zero, $zero
    ctx->r19 = 0 | 0;
    // 0x801E33B4: or          $s2, $zero, $zero
    ctx->r18 = 0 | 0;
    // 0x801E33B8: addiu       $s4, $zero, 0x7A
    ctx->r20 = ADD32(0, 0X7A);
    // 0x801E33BC: addiu       $s6, $zero, 0x3
    ctx->r22 = ADD32(0, 0X3);
L_801E33C0:
    // 0x801E33C0: andi        $t9, $s1, 0x1
    ctx->r25 = ctx->r17 & 0X1;
    // 0x801E33C4: beq         $t9, $zero, L_801E33D8
    if (ctx->r25 == 0) {
        // 0x801E33C8: lui         $s0, 0x8023
        ctx->r16 = S32(0X8023 << 16);
            goto L_801E33D8;
    }
    // 0x801E33C8: lui         $s0, 0x8023
    ctx->r16 = S32(0X8023 << 16);
    // 0x801E33CC: lui         $s0, 0x8023
    ctx->r16 = S32(0X8023 << 16);
    // 0x801E33D0: b           L_801E33DC
    // 0x801E33D4: lw          $s0, -0x7704($s0)
    ctx->r16 = MEM_W(ctx->r16, -0X7704);
        goto L_801E33DC;
    // 0x801E33D4: lw          $s0, -0x7704($s0)
    ctx->r16 = MEM_W(ctx->r16, -0X7704);
L_801E33D8:
    // 0x801E33D8: lw          $s0, -0x7708($s0)
    ctx->r16 = MEM_W(ctx->r16, -0X7708);
L_801E33DC:
    // 0x801E33DC: lw          $t0, 0x0($s5)
    ctx->r8 = MEM_W(ctx->r21, 0X0);
    // 0x801E33E0: or          $a0, $fp, $zero
    ctx->r4 = ctx->r30 | 0;
    // 0x801E33E4: addu        $a1, $t0, $s3
    ctx->r5 = ADD32(ctx->r8, ctx->r19);
    // 0x801E33E8: jal         0x80047EE0
    // 0x801E33EC: addiu       $a1, $a1, 0xA80
    ctx->r5 = ADD32(ctx->r5, 0XA80);
    SysUtils_MtxFToMtx(rdram, ctx);
        goto after_5;
    // 0x801E33EC: addiu       $a1, $a1, 0xA80
    ctx->r5 = ADD32(ctx->r5, 0XA80);
    after_5:
    // 0x801E33F0: lw          $t1, 0x0($s5)
    ctx->r9 = MEM_W(ctx->r21, 0X0);
    // 0x801E33F4: lw          $at, 0x0($s7)
    ctx->r1 = MEM_W(ctx->r23, 0X0);
    // 0x801E33F8: addiu       $t6, $s0, 0x38
    ctx->r14 = ADD32(ctx->r16, 0X38);
    // 0x801E33FC: addu        $t2, $t1, $s2
    ctx->r10 = ADD32(ctx->r9, ctx->r18);
    // 0x801E3400: sw          $at, 0x1280($t2)
    MEM_W(0X1280, ctx->r10) = ctx->r1;
    // 0x801E3404: lw          $t5, 0x4($s7)
    ctx->r13 = MEM_W(ctx->r23, 0X4);
    // 0x801E3408: sll         $t7, $t6, 2
    ctx->r15 = S32(ctx->r14 << 2);
    // 0x801E340C: addiu       $s1, $s1, 0x1
    ctx->r17 = ADD32(ctx->r17, 0X1);
    // 0x801E3410: sw          $t5, 0x1284($t2)
    MEM_W(0X1284, ctx->r10) = ctx->r13;
    // 0x801E3414: lw          $at, 0x8($s7)
    ctx->r1 = MEM_W(ctx->r23, 0X8);
    // 0x801E3418: sll         $t0, $s4, 2
    ctx->r8 = S32(ctx->r20 << 2);
    // 0x801E341C: addiu       $s4, $s4, 0x12
    ctx->r20 = ADD32(ctx->r20, 0X12);
    // 0x801E3420: sw          $at, 0x1288($t2)
    MEM_W(0X1288, ctx->r10) = ctx->r1;
    // 0x801E3424: lw          $t5, 0xC($s7)
    ctx->r13 = MEM_W(ctx->r23, 0XC);
    // 0x801E3428: addiu       $s3, $s3, 0x40
    ctx->r19 = ADD32(ctx->r19, 0X40);
    // 0x801E342C: sw          $t5, 0x128C($t2)
    MEM_W(0X128C, ctx->r10) = ctx->r13;
    // 0x801E3430: lw          $t8, 0x0($s5)
    ctx->r24 = MEM_W(ctx->r21, 0X0);
    // 0x801E3434: addu        $t9, $t8, $s2
    ctx->r25 = ADD32(ctx->r24, ctx->r18);
    // 0x801E3438: sh          $t7, 0x1288($t9)
    MEM_H(0X1288, ctx->r25) = ctx->r15;
    // 0x801E343C: lw          $t1, 0x0($s5)
    ctx->r9 = MEM_W(ctx->r21, 0X0);
    // 0x801E3440: addu        $t4, $t1, $s2
    ctx->r12 = ADD32(ctx->r9, ctx->r18);
    // 0x801E3444: addiu       $s2, $s2, 0x10
    ctx->r18 = ADD32(ctx->r18, 0X10);
    // 0x801E3448: bne         $s1, $s6, L_801E33C0
    if (ctx->r17 != ctx->r22) {
        // 0x801E344C: sh          $t0, 0x128A($t4)
        MEM_H(0X128A, ctx->r12) = ctx->r8;
            goto L_801E33C0;
    }
    // 0x801E344C: sh          $t0, 0x128A($t4)
    MEM_H(0X128A, ctx->r12) = ctx->r8;
    // 0x801E3450: lui         $t3, 0x801C
    ctx->r11 = S32(0X801C << 16);
    // 0x801E3454: lw          $t3, 0x2928($t3)
    ctx->r11 = MEM_W(ctx->r11, 0X2928);
    // 0x801E3458: bnel        $t3, $zero, L_801E34CC
    if (ctx->r11 != 0) {
        // 0x801E345C: lw          $ra, 0x5C($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X5C);
            goto L_801E34CC;
    }
    goto skip_0;
    // 0x801E345C: lw          $ra, 0x5C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X5C);
    skip_0:
    // 0x801E3460: lw          $t2, 0x0($s5)
    ctx->r10 = MEM_W(ctx->r21, 0X0);
    // 0x801E3464: or          $a0, $fp, $zero
    ctx->r4 = ctx->r30 | 0;
    // 0x801E3468: addu        $a1, $t2, $s3
    ctx->r5 = ADD32(ctx->r10, ctx->r19);
    // 0x801E346C: jal         0x80047EE0
    // 0x801E3470: addiu       $a1, $a1, 0xA80
    ctx->r5 = ADD32(ctx->r5, 0XA80);
    SysUtils_MtxFToMtx(rdram, ctx);
        goto after_6;
    // 0x801E3470: addiu       $a1, $a1, 0xA80
    ctx->r5 = ADD32(ctx->r5, 0XA80);
    after_6:
    // 0x801E3474: lw          $t5, 0x0($s5)
    ctx->r13 = MEM_W(ctx->r21, 0X0);
    // 0x801E3478: lw          $at, 0x0($s7)
    ctx->r1 = MEM_W(ctx->r23, 0X0);
    // 0x801E347C: lui         $t9, 0x8023
    ctx->r25 = S32(0X8023 << 16);
    // 0x801E3480: addu        $t6, $t5, $s2
    ctx->r14 = ADD32(ctx->r13, ctx->r18);
    // 0x801E3484: sw          $at, 0x1280($t6)
    MEM_W(0X1280, ctx->r14) = ctx->r1;
    // 0x801E3488: lw          $t7, 0x4($s7)
    ctx->r15 = MEM_W(ctx->r23, 0X4);
    // 0x801E348C: addiu       $t2, $zero, 0x338
    ctx->r10 = ADD32(0, 0X338);
    // 0x801E3490: sw          $t7, 0x1284($t6)
    MEM_W(0X1284, ctx->r14) = ctx->r15;
    // 0x801E3494: lw          $at, 0x8($s7)
    ctx->r1 = MEM_W(ctx->r23, 0X8);
    // 0x801E3498: sw          $at, 0x1288($t6)
    MEM_W(0X1288, ctx->r14) = ctx->r1;
    // 0x801E349C: lw          $t7, 0xC($s7)
    ctx->r15 = MEM_W(ctx->r23, 0XC);
    // 0x801E34A0: sw          $t7, 0x128C($t6)
    MEM_W(0X128C, ctx->r14) = ctx->r15;
    // 0x801E34A4: lw          $t9, -0x7704($t9)
    ctx->r25 = MEM_W(ctx->r25, -0X7704);
    // 0x801E34A8: lw          $t4, 0x0($s5)
    ctx->r12 = MEM_W(ctx->r21, 0X0);
    // 0x801E34AC: addiu       $t1, $t9, 0x38
    ctx->r9 = ADD32(ctx->r25, 0X38);
    // 0x801E34B0: sll         $t0, $t1, 2
    ctx->r8 = S32(ctx->r9 << 2);
    // 0x801E34B4: addu        $t3, $t4, $s2
    ctx->r11 = ADD32(ctx->r12, ctx->r18);
    // 0x801E34B8: sh          $t0, 0x1288($t3)
    MEM_H(0X1288, ctx->r11) = ctx->r8;
    // 0x801E34BC: lw          $t5, 0x0($s5)
    ctx->r13 = MEM_W(ctx->r21, 0X0);
    // 0x801E34C0: addu        $t8, $t5, $s2
    ctx->r24 = ADD32(ctx->r13, ctx->r18);
    // 0x801E34C4: sh          $t2, 0x128A($t8)
    MEM_H(0X128A, ctx->r24) = ctx->r10;
    // 0x801E34C8: lw          $ra, 0x5C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X5C);
L_801E34CC:
    // 0x801E34CC: lw          $s0, 0x38($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X38);
    // 0x801E34D0: lw          $s1, 0x3C($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X3C);
    // 0x801E34D4: lw          $s2, 0x40($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X40);
    // 0x801E34D8: lw          $s3, 0x44($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X44);
    // 0x801E34DC: lw          $s4, 0x48($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X48);
    // 0x801E34E0: lw          $s5, 0x4C($sp)
    ctx->r21 = MEM_W(ctx->r29, 0X4C);
    // 0x801E34E4: lw          $s6, 0x50($sp)
    ctx->r22 = MEM_W(ctx->r29, 0X50);
    // 0x801E34E8: lw          $s7, 0x54($sp)
    ctx->r23 = MEM_W(ctx->r29, 0X54);
    // 0x801E34EC: lw          $fp, 0x58($sp)
    ctx->r30 = MEM_W(ctx->r29, 0X58);
    // 0x801E34F0: jr          $ra
    // 0x801E34F4: addiu       $sp, $sp, 0x1B8
    ctx->r29 = ADD32(ctx->r29, 0X1B8);
    return;
    // 0x801E34F4: addiu       $sp, $sp, 0x1B8
    ctx->r29 = ADD32(ctx->r29, 0X1B8);
;}
RECOMP_FUNC void func_801E34F8(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801E34F8: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x801E34FC: addiu       $v0, $v0, -0x19C4
    ctx->r2 = ADD32(ctx->r2, -0X19C4);
    // 0x801E3500: lw          $t6, 0x0($v0)
    ctx->r14 = MEM_W(ctx->r2, 0X0);
    // 0x801E3504: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x801E3508: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x801E350C: beq         $t6, $zero, L_801E3518
    if (ctx->r14 == 0) {
        // 0x801E3510: lui         $at, 0x800E
        ctx->r1 = S32(0X800E << 16);
            goto L_801E3518;
    }
    // 0x801E3510: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x801E3514: sw          $zero, 0x0($v0)
    MEM_W(0X0, ctx->r2) = 0;
L_801E3518:
    // 0x801E3518: jal         0x8008FB74
    // 0x801E351C: sw          $zero, -0x54D4($at)
    MEM_W(-0X54D4, ctx->r1) = 0;
    func_8008FB74(rdram, ctx);
        goto after_0;
    // 0x801E351C: sw          $zero, -0x54D4($at)
    MEM_W(-0X54D4, ctx->r1) = 0;
    after_0:
    // 0x801E3520: lui         $a1, 0x800E
    ctx->r5 = S32(0X800E << 16);
    // 0x801E3524: lw          $a1, -0x7E90($a1)
    ctx->r5 = MEM_W(ctx->r5, -0X7E90);
    // 0x801E3528: jal         0x800949B8
    // 0x801E352C: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    func_800949B8(rdram, ctx);
        goto after_1;
    // 0x801E352C: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    after_1:
    // 0x801E3530: jal         0x80090F58
    // 0x801E3534: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    Draw_WaterEffects(rdram, ctx);
        goto after_2;
    // 0x801E3534: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    after_2:
    // 0x801E3538: jal         0x801E3698
    // 0x801E353C: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    func_801E3698(rdram, ctx);
        goto after_3;
    // 0x801E353C: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    after_3:
    // 0x801E3540: jal         0x801E355C
    // 0x801E3544: sw          $v0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r2;
    func_801E355C(rdram, ctx);
        goto after_4;
    // 0x801E3544: sw          $v0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r2;
    after_4:
    // 0x801E3548: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x801E354C: lw          $v0, 0x18($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X18);
    // 0x801E3550: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x801E3554: jr          $ra
    // 0x801E3558: nop

    return;
    // 0x801E3558: nop

;}
RECOMP_FUNC void func_801E355C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801E355C: lui         $v1, 0x8023
    ctx->r3 = S32(0X8023 << 16);
    // 0x801E3560: addiu       $v1, $v1, -0x7710
    ctx->r3 = ADD32(ctx->r3, -0X7710);
    // 0x801E3564: lw          $t6, 0x0($v1)
    ctx->r14 = MEM_W(ctx->r3, 0X0);
    // 0x801E3568: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x801E356C: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x801E3570: sltiu       $at, $t6, 0x5
    ctx->r1 = ctx->r14 < 0X5 ? 1 : 0;
    // 0x801E3574: beq         $at, $zero, L_801E3658
    if (ctx->r1 == 0) {
        // 0x801E3578: or          $a1, $zero, $zero
        ctx->r5 = 0 | 0;
            goto L_801E3658;
    }
    // 0x801E3578: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x801E357C: sll         $t6, $t6, 2
    ctx->r14 = S32(ctx->r14 << 2);
    // 0x801E3580: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E3584: addu        $at, $at, $t6
    gpr jr_addend_801E358C = ctx->r14;
    ctx->r1 = ADD32(ctx->r1, ctx->r14);
    // 0x801E3588: lw          $t6, 0x63A8($at)
    ctx->r14 = ADD32(ctx->r1, 0X63A8);
    // 0x801E358C: jr          $t6
    // 0x801E3590: nop

    switch (jr_addend_801E358C >> 2) {
        case 0: goto L_801E3594; break;
        case 1: goto L_801E35A4; break;
        case 2: goto L_801E35D4; break;
        case 3: goto L_801E35F4; break;
        case 4: goto L_801E3630; break;
        default: switch_error(__func__, 0x801E358C, 0x802263A8);
    }
    // 0x801E3590: nop

L_801E3594:
    // 0x801E3594: addiu       $t7, $zero, 0x1
    ctx->r15 = ADD32(0, 0X1);
    // 0x801E3598: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x801E359C: b           L_801E3658
    // 0x801E35A0: sw          $t7, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r15;
        goto L_801E3658;
    // 0x801E35A0: sw          $t7, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r15;
L_801E35A4:
    // 0x801E35A4: lui         $v0, 0x8023
    ctx->r2 = S32(0X8023 << 16);
    // 0x801E35A8: addiu       $v0, $v0, -0x7708
    ctx->r2 = ADD32(ctx->r2, -0X7708);
    // 0x801E35AC: lw          $t8, 0x0($v0)
    ctx->r24 = MEM_W(ctx->r2, 0X0);
    // 0x801E35B0: addiu       $t1, $zero, 0x2
    ctx->r9 = ADD32(0, 0X2);
    // 0x801E35B4: addiu       $t2, $zero, 0x14
    ctx->r10 = ADD32(0, 0X14);
    // 0x801E35B8: addiu       $t9, $t8, -0x14
    ctx->r25 = ADD32(ctx->r24, -0X14);
    // 0x801E35BC: slti        $at, $t9, 0x14
    ctx->r1 = SIGNED(ctx->r25) < 0X14 ? 1 : 0;
    // 0x801E35C0: beq         $at, $zero, L_801E3658
    if (ctx->r1 == 0) {
        // 0x801E35C4: sw          $t9, 0x0($v0)
        MEM_W(0X0, ctx->r2) = ctx->r25;
            goto L_801E3658;
    }
    // 0x801E35C4: sw          $t9, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r25;
    // 0x801E35C8: sw          $t1, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r9;
    // 0x801E35CC: b           L_801E3658
    // 0x801E35D0: sw          $t2, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r10;
        goto L_801E3658;
    // 0x801E35D0: sw          $t2, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r10;
L_801E35D4:
    // 0x801E35D4: lui         $t3, 0x801D
    ctx->r11 = S32(0X801D << 16);
    // 0x801E35D8: lhu         $t3, -0x19A6($t3)
    ctx->r11 = MEM_HU(ctx->r11, -0X19A6);
    // 0x801E35DC: andi        $t4, $t3, 0xB000
    ctx->r12 = ctx->r11 & 0XB000;
    // 0x801E35E0: beq         $t4, $zero, L_801E3658
    if (ctx->r12 == 0) {
        // 0x801E35E4: addiu       $t5, $zero, 0x3
        ctx->r13 = ADD32(0, 0X3);
            goto L_801E3658;
    }
    // 0x801E35E4: addiu       $t5, $zero, 0x3
    ctx->r13 = ADD32(0, 0X3);
    // 0x801E35E8: sw          $t5, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r13;
    // 0x801E35EC: b           L_801E3658
    // 0x801E35F0: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
        goto L_801E3658;
    // 0x801E35F0: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
L_801E35F4:
    // 0x801E35F4: lui         $v0, 0x8023
    ctx->r2 = S32(0X8023 << 16);
    // 0x801E35F8: addiu       $v0, $v0, -0x7708
    ctx->r2 = ADD32(ctx->r2, -0X7708);
    // 0x801E35FC: lw          $t6, 0x0($v0)
    ctx->r14 = MEM_W(ctx->r2, 0X0);
    // 0x801E3600: lui         $a0, 0x8023
    ctx->r4 = S32(0X8023 << 16);
    // 0x801E3604: addiu       $a0, $a0, -0x770C
    ctx->r4 = ADD32(ctx->r4, -0X770C);
    // 0x801E3608: addiu       $t7, $t6, -0x14
    ctx->r15 = ADD32(ctx->r14, -0X14);
    // 0x801E360C: slti        $at, $t7, -0x170
    ctx->r1 = SIGNED(ctx->r15) < -0X170 ? 1 : 0;
    // 0x801E3610: beq         $at, $zero, L_801E3658
    if (ctx->r1 == 0) {
        // 0x801E3614: sw          $t7, 0x0($v0)
        MEM_W(0X0, ctx->r2) = ctx->r15;
            goto L_801E3658;
    }
    // 0x801E3614: sw          $t7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r15;
    // 0x801E3618: addiu       $t9, $zero, -0x170
    ctx->r25 = ADD32(0, -0X170);
    // 0x801E361C: addiu       $t0, $zero, 0x4
    ctx->r8 = ADD32(0, 0X4);
    // 0x801E3620: sw          $t9, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r25;
    // 0x801E3624: sw          $t0, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r8;
    // 0x801E3628: b           L_801E3658
    // 0x801E362C: sw          $zero, 0x0($a0)
    MEM_W(0X0, ctx->r4) = 0;
        goto L_801E3658;
    // 0x801E362C: sw          $zero, 0x0($a0)
    MEM_W(0X0, ctx->r4) = 0;
L_801E3630:
    // 0x801E3630: lui         $a0, 0x8023
    ctx->r4 = S32(0X8023 << 16);
    // 0x801E3634: addiu       $a0, $a0, -0x770C
    ctx->r4 = ADD32(ctx->r4, -0X770C);
    // 0x801E3638: lw          $t1, 0x0($a0)
    ctx->r9 = MEM_W(ctx->r4, 0X0);
    // 0x801E363C: addiu       $t2, $t1, 0x1
    ctx->r10 = ADD32(ctx->r9, 0X1);
    // 0x801E3640: slti        $at, $t2, 0x3
    ctx->r1 = SIGNED(ctx->r10) < 0X3 ? 1 : 0;
    // 0x801E3644: bne         $at, $zero, L_801E3658
    if (ctx->r1 != 0) {
        // 0x801E3648: sw          $t2, 0x0($a0)
        MEM_W(0X0, ctx->r4) = ctx->r10;
            goto L_801E3658;
    }
    // 0x801E3648: sw          $t2, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r10;
    // 0x801E364C: jal         0x801EC830
    // 0x801E3650: sw          $a1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r5;
    func_801EC830(rdram, ctx);
        goto after_0;
    // 0x801E3650: sw          $a1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r5;
    after_0:
    // 0x801E3654: lw          $a1, 0x1C($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X1C);
L_801E3658:
    // 0x801E3658: lui         $v0, 0x8023
    ctx->r2 = S32(0X8023 << 16);
    // 0x801E365C: beq         $a1, $zero, L_801E3678
    if (ctx->r5 == 0) {
        // 0x801E3660: addiu       $v0, $v0, -0x7708
        ctx->r2 = ADD32(ctx->r2, -0X7708);
            goto L_801E3678;
    }
    // 0x801E3660: addiu       $v0, $v0, -0x7708
    ctx->r2 = ADD32(ctx->r2, -0X7708);
    // 0x801E3664: addiu       $a0, $zero, 0x31
    ctx->r4 = ADD32(0, 0X31);
    // 0x801E3668: jal         0x800C37F4
    // 0x801E366C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_1;
    // 0x801E366C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_1:
    // 0x801E3670: lui         $v0, 0x8023
    ctx->r2 = S32(0X8023 << 16);
    // 0x801E3674: addiu       $v0, $v0, -0x7708
    ctx->r2 = ADD32(ctx->r2, -0X7708);
L_801E3678:
    // 0x801E3678: lw          $t4, 0x0($v0)
    ctx->r12 = MEM_W(ctx->r2, 0X0);
    // 0x801E367C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x801E3680: addiu       $t5, $zero, 0x28
    ctx->r13 = ADD32(0, 0X28);
    // 0x801E3684: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801E3688: subu        $t6, $t5, $t4
    ctx->r14 = SUB32(ctx->r13, ctx->r12);
    // 0x801E368C: sw          $t6, -0x7704($at)
    MEM_W(-0X7704, ctx->r1) = ctx->r14;
    // 0x801E3690: jr          $ra
    // 0x801E3694: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    return;
    // 0x801E3694: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
;}
RECOMP_FUNC void func_801E3698(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801E3698: addiu       $sp, $sp, -0xB8
    ctx->r29 = ADD32(ctx->r29, -0XB8);
    // 0x801E369C: sw          $s5, 0x54($sp)
    MEM_W(0X54, ctx->r29) = ctx->r21;
    // 0x801E36A0: sw          $ra, 0x64($sp)
    MEM_W(0X64, ctx->r29) = ctx->r31;
    // 0x801E36A4: sw          $fp, 0x60($sp)
    MEM_W(0X60, ctx->r29) = ctx->r30;
    // 0x801E36A8: sw          $s7, 0x5C($sp)
    MEM_W(0X5C, ctx->r29) = ctx->r23;
    // 0x801E36AC: sw          $s6, 0x58($sp)
    MEM_W(0X58, ctx->r29) = ctx->r22;
    // 0x801E36B0: sw          $s4, 0x50($sp)
    MEM_W(0X50, ctx->r29) = ctx->r20;
    // 0x801E36B4: sw          $s3, 0x4C($sp)
    MEM_W(0X4C, ctx->r29) = ctx->r19;
    // 0x801E36B8: sw          $s2, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r18;
    // 0x801E36BC: sw          $s1, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r17;
    // 0x801E36C0: sw          $s0, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r16;
    // 0x801E36C4: lui         $t6, 0x107
    ctx->r14 = S32(0X107 << 16);
    // 0x801E36C8: lui         $s5, 0x600
    ctx->r21 = S32(0X600 << 16);
    // 0x801E36CC: addiu       $t6, $t6, -0x9D8
    ctx->r14 = ADD32(ctx->r14, -0X9D8);
    // 0x801E36D0: sw          $t6, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r14;
    // 0x801E36D4: sw          $s5, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r21;
    // 0x801E36D8: lui         $a2, 0x8023
    ctx->r6 = S32(0X8023 << 16);
    // 0x801E36DC: lw          $a2, -0x7708($a2)
    ctx->r6 = MEM_W(ctx->r6, -0X7708);
    // 0x801E36E0: addiu       $s3, $a0, 0x8
    ctx->r19 = ADD32(ctx->r4, 0X8);
    // 0x801E36E4: addiu       $t7, $zero, 0x170
    ctx->r15 = ADD32(0, 0X170);
    // 0x801E36E8: addiu       $t8, $zero, 0x18
    ctx->r24 = ADD32(0, 0X18);
    // 0x801E36EC: sw          $t8, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r24;
    // 0x801E36F0: sw          $t7, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r15;
    // 0x801E36F4: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
    // 0x801E36F8: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x801E36FC: addiu       $a3, $zero, 0x1E
    ctx->r7 = ADD32(0, 0X1E);
    // 0x801E3700: jal         0x80094338
    // 0x801E3704: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    func_80094338(rdram, ctx);
        goto after_0;
    // 0x801E3704: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    after_0:
    // 0x801E3708: lui         $a2, 0x8023
    ctx->r6 = S32(0X8023 << 16);
    // 0x801E370C: lw          $a2, -0x7704($a2)
    ctx->r6 = MEM_W(ctx->r6, -0X7704);
    // 0x801E3710: addiu       $t9, $zero, 0x170
    ctx->r25 = ADD32(0, 0X170);
    // 0x801E3714: addiu       $t0, $zero, 0x10
    ctx->r8 = ADD32(0, 0X10);
    // 0x801E3718: sw          $t0, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r8;
    // 0x801E371C: sw          $t9, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r25;
    // 0x801E3720: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x801E3724: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x801E3728: addiu       $a3, $zero, 0x58
    ctx->r7 = ADD32(0, 0X58);
    // 0x801E372C: jal         0x80094338
    // 0x801E3730: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    func_80094338(rdram, ctx);
        goto after_1;
    // 0x801E3730: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    after_1:
    // 0x801E3734: or          $s3, $v0, $zero
    ctx->r19 = ctx->r2 | 0;
    // 0x801E3738: or          $s1, $zero, $zero
    ctx->r17 = 0 | 0;
    // 0x801E373C: addiu       $s2, $zero, 0x6E
    ctx->r18 = ADD32(0, 0X6E);
L_801E3740:
    // 0x801E3740: andi        $t1, $s1, 0x1
    ctx->r9 = ctx->r17 & 0X1;
    // 0x801E3744: beq         $t1, $zero, L_801E3758
    if (ctx->r9 == 0) {
        // 0x801E3748: or          $a0, $s3, $zero
        ctx->r4 = ctx->r19 | 0;
            goto L_801E3758;
    }
    // 0x801E3748: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
    // 0x801E374C: lui         $s0, 0x8023
    ctx->r16 = S32(0X8023 << 16);
    // 0x801E3750: b           L_801E3760
    // 0x801E3754: lw          $s0, -0x7704($s0)
    ctx->r16 = MEM_W(ctx->r16, -0X7704);
        goto L_801E3760;
    // 0x801E3754: lw          $s0, -0x7704($s0)
    ctx->r16 = MEM_W(ctx->r16, -0X7704);
L_801E3758:
    // 0x801E3758: lui         $s0, 0x8023
    ctx->r16 = S32(0X8023 << 16);
    // 0x801E375C: lw          $s0, -0x7708($s0)
    ctx->r16 = MEM_W(ctx->r16, -0X7708);
L_801E3760:
    // 0x801E3760: addiu       $t2, $zero, 0x170
    ctx->r10 = ADD32(0, 0X170);
    // 0x801E3764: addiu       $t3, $zero, 0x10
    ctx->r11 = ADD32(0, 0X10);
    // 0x801E3768: sw          $t3, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r11;
    // 0x801E376C: sw          $t2, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r10;
    // 0x801E3770: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x801E3774: addiu       $a2, $s0, 0x8
    ctx->r6 = ADD32(ctx->r16, 0X8);
    // 0x801E3778: jal         0x80094338
    // 0x801E377C: or          $a3, $s2, $zero
    ctx->r7 = ctx->r18 | 0;
    func_80094338(rdram, ctx);
        goto after_2;
    // 0x801E377C: or          $a3, $s2, $zero
    ctx->r7 = ctx->r18 | 0;
    after_2:
    // 0x801E3780: addiu       $s1, $s1, 0x1
    ctx->r17 = ADD32(ctx->r17, 0X1);
    // 0x801E3784: slti        $at, $s1, 0x3
    ctx->r1 = SIGNED(ctx->r17) < 0X3 ? 1 : 0;
    // 0x801E3788: addiu       $s2, $s2, 0x12
    ctx->r18 = ADD32(ctx->r18, 0X12);
    // 0x801E378C: bne         $at, $zero, L_801E3740
    if (ctx->r1 != 0) {
        // 0x801E3790: or          $s3, $v0, $zero
        ctx->r19 = ctx->r2 | 0;
            goto L_801E3740;
    }
    // 0x801E3790: or          $s3, $v0, $zero
    ctx->r19 = ctx->r2 | 0;
    // 0x801E3794: lui         $t4, 0x801C
    ctx->r12 = S32(0X801C << 16);
    // 0x801E3798: lw          $t4, 0x2928($t4)
    ctx->r12 = MEM_W(ctx->r12, 0X2928);
    // 0x801E379C: bne         $t4, $zero, L_801E37FC
    if (ctx->r12 != 0) {
        // 0x801E37A0: lui         $a2, 0x8023
        ctx->r6 = S32(0X8023 << 16);
            goto L_801E37FC;
    }
    // 0x801E37A0: lui         $a2, 0x8023
    ctx->r6 = S32(0X8023 << 16);
    // 0x801E37A4: lw          $a2, -0x7704($a2)
    ctx->r6 = MEM_W(ctx->r6, -0X7704);
    // 0x801E37A8: addiu       $t5, $zero, 0x170
    ctx->r13 = ADD32(0, 0X170);
    // 0x801E37AC: addiu       $t6, $zero, 0xA
    ctx->r14 = ADD32(0, 0XA);
    // 0x801E37B0: sw          $t6, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r14;
    // 0x801E37B4: sw          $t5, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r13;
    // 0x801E37B8: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x801E37BC: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x801E37C0: addiu       $a3, $zero, 0xB7
    ctx->r7 = ADD32(0, 0XB7);
    // 0x801E37C4: jal         0x80094338
    // 0x801E37C8: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    func_80094338(rdram, ctx);
        goto after_3;
    // 0x801E37C8: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    after_3:
    // 0x801E37CC: lui         $a2, 0x8023
    ctx->r6 = S32(0X8023 << 16);
    // 0x801E37D0: lw          $a2, -0x7704($a2)
    ctx->r6 = MEM_W(ctx->r6, -0X7704);
    // 0x801E37D4: addiu       $t7, $zero, 0x170
    ctx->r15 = ADD32(0, 0X170);
    // 0x801E37D8: addiu       $t8, $zero, 0x10
    ctx->r24 = ADD32(0, 0X10);
    // 0x801E37DC: sw          $t8, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r24;
    // 0x801E37E0: sw          $t7, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r15;
    // 0x801E37E4: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x801E37E8: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x801E37EC: addiu       $a3, $zero, 0xC2
    ctx->r7 = ADD32(0, 0XC2);
    // 0x801E37F0: jal         0x80094338
    // 0x801E37F4: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    func_80094338(rdram, ctx);
        goto after_4;
    // 0x801E37F4: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    after_4:
    // 0x801E37F8: or          $s3, $v0, $zero
    ctx->r19 = ctx->r2 | 0;
L_801E37FC:
    // 0x801E37FC: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x801E3800: sw          $t9, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r25;
    // 0x801E3804: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
    // 0x801E3808: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x801E380C: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x801E3810: jal         0x801E7E74
    // 0x801E3814: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_801E7E74(rdram, ctx);
        goto after_5;
    // 0x801E3814: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_5:
    // 0x801E3818: or          $s3, $v0, $zero
    ctx->r19 = ctx->r2 | 0;
    // 0x801E381C: or          $s1, $zero, $zero
    ctx->r17 = 0 | 0;
    // 0x801E3820: addiu       $s4, $zero, 0x70
    ctx->r20 = ADD32(0, 0X70);
    // 0x801E3824: addiu       $s2, $zero, 0x7C
    ctx->r18 = ADD32(0, 0X7C);
L_801E3828:
    // 0x801E3828: andi        $t0, $s1, 0x1
    ctx->r8 = ctx->r17 & 0X1;
    // 0x801E382C: beq         $t0, $zero, L_801E3840
    if (ctx->r8 == 0) {
        // 0x801E3830: or          $a0, $s3, $zero
        ctx->r4 = ctx->r19 | 0;
            goto L_801E3840;
    }
    // 0x801E3830: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
    // 0x801E3834: lui         $s0, 0x8023
    ctx->r16 = S32(0X8023 << 16);
    // 0x801E3838: b           L_801E3848
    // 0x801E383C: lw          $s0, -0x7704($s0)
    ctx->r16 = MEM_W(ctx->r16, -0X7704);
        goto L_801E3848;
    // 0x801E383C: lw          $s0, -0x7704($s0)
    ctx->r16 = MEM_W(ctx->r16, -0X7704);
L_801E3840:
    // 0x801E3840: lui         $s0, 0x8023
    ctx->r16 = S32(0X8023 << 16);
    // 0x801E3844: lw          $s0, -0x7708($s0)
    ctx->r16 = MEM_W(ctx->r16, -0X7708);
L_801E3848:
    // 0x801E3848: addiu       $a1, $s0, 0x28
    ctx->r5 = ADD32(ctx->r16, 0X28);
    // 0x801E384C: or          $a2, $s4, $zero
    ctx->r6 = ctx->r20 | 0;
    // 0x801E3850: addiu       $a3, $s0, 0x42
    ctx->r7 = ADD32(ctx->r16, 0X42);
    // 0x801E3854: jal         0x801E7FD8
    // 0x801E3858: sw          $s2, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r18;
    func_801E7FD8(rdram, ctx);
        goto after_6;
    // 0x801E3858: sw          $s2, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r18;
    after_6:
    // 0x801E385C: addiu       $s1, $s1, 0x1
    ctx->r17 = ADD32(ctx->r17, 0X1);
    // 0x801E3860: slti        $at, $s1, 0x3
    ctx->r1 = SIGNED(ctx->r17) < 0X3 ? 1 : 0;
    // 0x801E3864: addiu       $s4, $s4, 0x12
    ctx->r20 = ADD32(ctx->r20, 0X12);
    // 0x801E3868: addiu       $s2, $s2, 0x12
    ctx->r18 = ADD32(ctx->r18, 0X12);
    // 0x801E386C: bne         $at, $zero, L_801E3828
    if (ctx->r1 != 0) {
        // 0x801E3870: or          $s3, $v0, $zero
        ctx->r19 = ctx->r2 | 0;
            goto L_801E3828;
    }
    // 0x801E3870: or          $s3, $v0, $zero
    ctx->r19 = ctx->r2 | 0;
    // 0x801E3874: lui         $t1, 0x801C
    ctx->r9 = S32(0X801C << 16);
    // 0x801E3878: lw          $t1, 0x2928($t1)
    ctx->r9 = MEM_W(ctx->r9, 0X2928);
    // 0x801E387C: bnel        $t1, $zero, L_801E38AC
    if (ctx->r9 != 0) {
        // 0x801E3880: addiu       $s3, $v0, 0x8
        ctx->r19 = ADD32(ctx->r2, 0X8);
            goto L_801E38AC;
    }
    goto skip_0;
    // 0x801E3880: addiu       $s3, $v0, 0x8
    ctx->r19 = ADD32(ctx->r2, 0X8);
    skip_0:
    // 0x801E3884: lui         $v0, 0x8023
    ctx->r2 = S32(0X8023 << 16);
    // 0x801E3888: lw          $v0, -0x7704($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X7704);
    // 0x801E388C: addiu       $t2, $zero, 0xD0
    ctx->r10 = ADD32(0, 0XD0);
    // 0x801E3890: sw          $t2, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r10;
    // 0x801E3894: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
    // 0x801E3898: addiu       $a2, $zero, 0xC4
    ctx->r6 = ADD32(0, 0XC4);
    // 0x801E389C: addiu       $a1, $v0, 0x28
    ctx->r5 = ADD32(ctx->r2, 0X28);
    // 0x801E38A0: jal         0x801E7FD8
    // 0x801E38A4: addiu       $a3, $v0, 0x42
    ctx->r7 = ADD32(ctx->r2, 0X42);
    func_801E7FD8(rdram, ctx);
        goto after_7;
    // 0x801E38A4: addiu       $a3, $v0, 0x42
    ctx->r7 = ADD32(ctx->r2, 0X42);
    after_7:
    // 0x801E38A8: addiu       $s3, $v0, 0x8
    ctx->r19 = ADD32(ctx->r2, 0X8);
L_801E38AC:
    // 0x801E38AC: lui         $t3, 0xE700
    ctx->r11 = S32(0XE700 << 16);
    // 0x801E38B0: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
    // 0x801E38B4: sw          $t3, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r11;
    // 0x801E38B8: sw          $zero, 0x4($v0)
    MEM_W(0X4, ctx->r2) = 0;
    // 0x801E38BC: lui         $t4, 0xED02
    ctx->r12 = S32(0XED02 << 16);
    // 0x801E38C0: addiu       $t4, $t4, 0x30
    ctx->r12 = ADD32(ctx->r12, 0X30);
    // 0x801E38C4: lui         $t5, 0x68
    ctx->r13 = S32(0X68 << 16);
    // 0x801E38C8: addiu       $t5, $t5, -0x3C6C
    ctx->r13 = ADD32(ctx->r13, -0X3C6C);
    // 0x801E38CC: addiu       $s3, $s3, 0x8
    ctx->r19 = ADD32(ctx->r19, 0X8);
    // 0x801E38D0: sw          $t4, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r12;
    // 0x801E38D4: sw          $t5, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r13;
    // 0x801E38D8: or          $a1, $s3, $zero
    ctx->r5 = ctx->r19 | 0;
    // 0x801E38DC: lui         $t6, 0xB400
    ctx->r14 = S32(0XB400 << 16);
    // 0x801E38E0: sw          $t6, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r14;
    // 0x801E38E4: lui         $t7, 0x8023
    ctx->r15 = S32(0X8023 << 16);
    // 0x801E38E8: lhu         $t7, -0x7700($t7)
    ctx->r15 = MEM_HU(ctx->r15, -0X7700);
    // 0x801E38EC: addiu       $s3, $s3, 0x8
    ctx->r19 = ADD32(ctx->r19, 0X8);
    // 0x801E38F0: or          $a2, $s3, $zero
    ctx->r6 = ctx->r19 | 0;
    // 0x801E38F4: lui         $t8, 0x103
    ctx->r24 = S32(0X103 << 16);
    // 0x801E38F8: lui         $t9, 0x700
    ctx->r25 = S32(0X700 << 16);
    // 0x801E38FC: sw          $t7, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r15;
    // 0x801E3900: addiu       $t9, $t9, 0xA40
    ctx->r25 = ADD32(ctx->r25, 0XA40);
    // 0x801E3904: ori         $t8, $t8, 0x40
    ctx->r24 = ctx->r24 | 0X40;
    // 0x801E3908: addiu       $s3, $s3, 0x8
    ctx->r19 = ADD32(ctx->r19, 0X8);
    // 0x801E390C: sw          $t8, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r24;
    // 0x801E3910: sw          $t9, 0x4($a2)
    MEM_W(0X4, ctx->r6) = ctx->r25;
    // 0x801E3914: or          $a3, $s3, $zero
    ctx->r7 = ctx->r19 | 0;
    // 0x801E3918: sw          $s5, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r21;
    // 0x801E391C: lui         $t0, 0x107
    ctx->r8 = S32(0X107 << 16);
    // 0x801E3920: addiu       $t0, $t0, -0xB78
    ctx->r8 = ADD32(ctx->r8, -0XB78);
    // 0x801E3924: lui         $s5, 0x700
    ctx->r21 = S32(0X700 << 16);
    // 0x801E3928: lui         $s4, 0x700
    ctx->r20 = S32(0X700 << 16);
    // 0x801E392C: lui         $s1, 0x380
    ctx->r17 = S32(0X380 << 16);
    // 0x801E3930: sw          $t0, 0x4($a3)
    MEM_W(0X4, ctx->r7) = ctx->r8;
    // 0x801E3934: addiu       $s3, $s3, 0x8
    ctx->r19 = ADD32(ctx->r19, 0X8);
    // 0x801E3938: ori         $s1, $s1, 0x10
    ctx->r17 = ctx->r17 | 0X10;
    // 0x801E393C: addiu       $s4, $s4, 0x1280
    ctx->r20 = ADD32(ctx->r20, 0X1280);
    // 0x801E3940: addiu       $s5, $s5, 0xA80
    ctx->r21 = ADD32(ctx->r21, 0XA80);
    // 0x801E3944: or          $s6, $zero, $zero
    ctx->r22 = 0 | 0;
    // 0x801E3948: or          $s0, $zero, $zero
    ctx->r16 = 0 | 0;
L_801E394C:
    // 0x801E394C: lui         $t1, 0x800E
    ctx->r9 = S32(0X800E << 16);
    // 0x801E3950: lw          $t1, -0x7E90($t1)
    ctx->r9 = MEM_W(ctx->r9, -0X7E90);
    // 0x801E3954: or          $v0, $s3, $zero
    ctx->r2 = ctx->r19 | 0;
    // 0x801E3958: sw          $s1, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r17;
    // 0x801E395C: sw          $s4, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r20;
    // 0x801E3960: addiu       $v1, $s3, 0x8
    ctx->r3 = ADD32(ctx->r19, 0X8);
    // 0x801E3964: lui         $t5, 0x102
    ctx->r13 = S32(0X102 << 16);
    // 0x801E3968: ori         $t5, $t5, 0x40
    ctx->r13 = ctx->r13 | 0X40;
    // 0x801E396C: sw          $t5, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r13;
    // 0x801E3970: sw          $s5, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r21;
    // 0x801E3974: lui         $t6, 0x801D
    ctx->r14 = S32(0X801D << 16);
    // 0x801E3978: sll         $t2, $t1, 2
    ctx->r10 = S32(ctx->r9 << 2);
    // 0x801E397C: lw          $t6, -0x1A08($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X1A08);
    // 0x801E3980: subu        $t2, $t2, $t1
    ctx->r10 = SUB32(ctx->r10, ctx->r9);
    // 0x801E3984: sll         $t2, $t2, 4
    ctx->r10 = S32(ctx->r10 << 4);
    // 0x801E3988: lui         $t4, 0x801C
    ctx->r12 = S32(0X801C << 16);
    // 0x801E398C: addiu       $t4, $t4, 0x26E8
    ctx->r12 = ADD32(ctx->r12, 0X26E8);
    // 0x801E3990: addu        $t3, $t2, $s6
    ctx->r11 = ADD32(ctx->r10, ctx->r22);
    // 0x801E3994: addu        $s2, $t3, $t4
    ctx->r18 = ADD32(ctx->r11, ctx->r12);
    // 0x801E3998: addu        $t7, $t6, $s0
    ctx->r15 = ADD32(ctx->r14, ctx->r16);
    // 0x801E399C: addiu       $t8, $t7, 0xC80
    ctx->r24 = ADD32(ctx->r15, 0XC80);
    // 0x801E39A0: lw          $a1, 0x4($s2)
    ctx->r5 = MEM_W(ctx->r18, 0X4);
    // 0x801E39A4: addiu       $a0, $v1, 0x8
    ctx->r4 = ADD32(ctx->r3, 0X8);
    // 0x801E39A8: sw          $t8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r24;
    // 0x801E39AC: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x801E39B0: jal         0x801E4FE8
    // 0x801E39B4: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_801E4FE8(rdram, ctx);
        goto after_8;
    // 0x801E39B4: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_8:
    // 0x801E39B8: addiu       $s0, $s0, 0xC0
    ctx->r16 = ADD32(ctx->r16, 0XC0);
    // 0x801E39BC: slti        $at, $s0, 0x240
    ctx->r1 = SIGNED(ctx->r16) < 0X240 ? 1 : 0;
    // 0x801E39C0: addiu       $s6, $s6, 0x10
    ctx->r22 = ADD32(ctx->r22, 0X10);
    // 0x801E39C4: addiu       $s4, $s4, 0x10
    ctx->r20 = ADD32(ctx->r20, 0X10);
    // 0x801E39C8: addiu       $s5, $s5, 0x40
    ctx->r21 = ADD32(ctx->r21, 0X40);
    // 0x801E39CC: bne         $at, $zero, L_801E394C
    if (ctx->r1 != 0) {
        // 0x801E39D0: or          $s3, $v0, $zero
        ctx->r19 = ctx->r2 | 0;
            goto L_801E394C;
    }
    // 0x801E39D0: or          $s3, $v0, $zero
    ctx->r19 = ctx->r2 | 0;
    // 0x801E39D4: lui         $t9, 0x801C
    ctx->r25 = S32(0X801C << 16);
    // 0x801E39D8: lw          $t9, 0x2928($t9)
    ctx->r25 = MEM_W(ctx->r25, 0X2928);
    // 0x801E39DC: addiu       $v1, $s3, 0x8
    ctx->r3 = ADD32(ctx->r19, 0X8);
    // 0x801E39E0: addiu       $a0, $v1, 0x8
    ctx->r4 = ADD32(ctx->r3, 0X8);
    // 0x801E39E4: bne         $t9, $zero, L_801E3A3C
    if (ctx->r25 != 0) {
        // 0x801E39E8: lui         $t0, 0x102
        ctx->r8 = S32(0X102 << 16);
            goto L_801E3A3C;
    }
    // 0x801E39E8: lui         $t0, 0x102
    ctx->r8 = S32(0X102 << 16);
    // 0x801E39EC: sw          $s1, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r17;
    // 0x801E39F0: sw          $s4, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r20;
    // 0x801E39F4: ori         $t0, $t0, 0x40
    ctx->r8 = ctx->r8 | 0X40;
    // 0x801E39F8: sw          $t0, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r8;
    // 0x801E39FC: sw          $s5, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r21;
    // 0x801E3A00: lui         $t1, 0x800D
    ctx->r9 = S32(0X800D << 16);
    // 0x801E3A04: lui         $t3, 0x801D
    ctx->r11 = S32(0X801D << 16);
    // 0x801E3A08: lw          $t3, -0x1A08($t3)
    ctx->r11 = MEM_W(ctx->r11, -0X1A08);
    // 0x801E3A0C: lw          $t1, 0x48DC($t1)
    ctx->r9 = MEM_W(ctx->r9, 0X48DC);
    // 0x801E3A10: lui         $a1, 0x800E
    ctx->r5 = S32(0X800E << 16);
    // 0x801E3A14: addu        $t4, $t3, $s0
    ctx->r12 = ADD32(ctx->r11, ctx->r16);
    // 0x801E3A18: sll         $t2, $t1, 2
    ctx->r10 = S32(ctx->r9 << 2);
    // 0x801E3A1C: addu        $a1, $a1, $t2
    ctx->r5 = ADD32(ctx->r5, ctx->r10);
    // 0x801E3A20: addiu       $t5, $t4, 0xC80
    ctx->r13 = ADD32(ctx->r12, 0XC80);
    // 0x801E3A24: sw          $t5, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r13;
    // 0x801E3A28: lw          $a1, -0x5650($a1)
    ctx->r5 = MEM_W(ctx->r5, -0X5650);
    // 0x801E3A2C: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x801E3A30: jal         0x801E4FE8
    // 0x801E3A34: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_801E4FE8(rdram, ctx);
        goto after_9;
    // 0x801E3A34: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_9:
    // 0x801E3A38: or          $s3, $v0, $zero
    ctx->r19 = ctx->r2 | 0;
L_801E3A3C:
    // 0x801E3A3C: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x801E3A40: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x801E3A44: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x801E3A48: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x801E3A4C: addiu       $t0, $zero, 0xFF
    ctx->r8 = ADD32(0, 0XFF);
    // 0x801E3A50: addiu       $t1, $zero, 0xFF
    ctx->r9 = ADD32(0, 0XFF);
    // 0x801E3A54: addiu       $t2, $zero, 0xFF
    ctx->r10 = ADD32(0, 0XFF);
    // 0x801E3A58: addiu       $t3, $zero, 0xFF
    ctx->r11 = ADD32(0, 0XFF);
    // 0x801E3A5C: addiu       $t4, $zero, 0xFF
    ctx->r12 = ADD32(0, 0XFF);
    // 0x801E3A60: addiu       $t5, $zero, 0xFF
    ctx->r13 = ADD32(0, 0XFF);
    // 0x801E3A64: sw          $t5, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r13;
    // 0x801E3A68: sw          $t4, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r12;
    // 0x801E3A6C: sw          $t3, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r11;
    // 0x801E3A70: sw          $t2, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r10;
    // 0x801E3A74: sw          $t1, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r9;
    // 0x801E3A78: sw          $t0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r8;
    // 0x801E3A7C: sw          $t9, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r25;
    // 0x801E3A80: sw          $t8, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r24;
    // 0x801E3A84: sw          $t7, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r15;
    // 0x801E3A88: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x801E3A8C: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
    // 0x801E3A90: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x801E3A94: addiu       $a2, $zero, 0xFF
    ctx->r6 = ADD32(0, 0XFF);
    // 0x801E3A98: jal         0x801E946C
    // 0x801E3A9C: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    func_801E946C(rdram, ctx);
        goto after_10;
    // 0x801E3A9C: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    after_10:
    // 0x801E3AA0: lui         $v1, 0x800E
    ctx->r3 = S32(0X800E << 16);
    // 0x801E3AA4: lw          $v1, -0x7E90($v1)
    ctx->r3 = MEM_W(ctx->r3, -0X7E90);
    // 0x801E3AA8: lui         $t7, 0x8022
    ctx->r15 = S32(0X8022 << 16);
    // 0x801E3AAC: lui         $t8, 0x8023
    ctx->r24 = S32(0X8023 << 16);
    // 0x801E3AB0: sll         $t6, $v1, 2
    ctx->r14 = S32(ctx->r3 << 2);
    // 0x801E3AB4: addu        $t7, $t7, $t6
    ctx->r15 = ADD32(ctx->r15, ctx->r14);
    // 0x801E3AB8: lw          $t7, 0x6350($t7)
    ctx->r15 = MEM_W(ctx->r15, 0X6350);
    // 0x801E3ABC: lw          $t8, -0x7708($t8)
    ctx->r24 = MEM_W(ctx->r24, -0X7708);
    // 0x801E3AC0: lui         $a2, 0x800E
    ctx->r6 = S32(0X800E << 16);
    // 0x801E3AC4: addu        $a2, $a2, $t6
    ctx->r6 = ADD32(ctx->r6, ctx->r14);
    // 0x801E3AC8: addiu       $t9, $zero, 0x21
    ctx->r25 = ADD32(0, 0X21);
    // 0x801E3ACC: addu        $a3, $t7, $t8
    ctx->r7 = ADD32(ctx->r15, ctx->r24);
    // 0x801E3AD0: addiu       $a3, $a3, 0x6C
    ctx->r7 = ADD32(ctx->r7, 0X6C);
    // 0x801E3AD4: sw          $t9, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r25;
    // 0x801E3AD8: lw          $a2, -0x55CC($a2)
    ctx->r6 = MEM_W(ctx->r6, -0X55CC);
    // 0x801E3ADC: or          $v1, $t6, $zero
    ctx->r3 = ctx->r14 | 0;
    // 0x801E3AE0: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x801E3AE4: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x801E3AE8: jal         0x801E3EE0
    // 0x801E3AEC: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    func_801E3EE0(rdram, ctx);
        goto after_11;
    // 0x801E3AEC: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    after_11:
    // 0x801E3AF0: lui         $a3, 0x8023
    ctx->r7 = S32(0X8023 << 16);
    // 0x801E3AF4: lw          $a3, -0x7704($a3)
    ctx->r7 = MEM_W(ctx->r7, -0X7704);
    // 0x801E3AF8: addiu       $t0, $zero, 0x5B
    ctx->r8 = ADD32(0, 0X5B);
    // 0x801E3AFC: sw          $t0, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r8;
    // 0x801E3B00: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x801E3B04: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x801E3B08: addiu       $a2, $zero, 0x1F
    ctx->r6 = ADD32(0, 0X1F);
    // 0x801E3B0C: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    // 0x801E3B10: jal         0x801E3EE0
    // 0x801E3B14: addiu       $a3, $a3, 0x17
    ctx->r7 = ADD32(ctx->r7, 0X17);
    func_801E3EE0(rdram, ctx);
        goto after_12;
    // 0x801E3B14: addiu       $a3, $a3, 0x17
    ctx->r7 = ADD32(ctx->r7, 0X17);
    after_12:
    // 0x801E3B18: lui         $a3, 0x8023
    ctx->r7 = S32(0X8023 << 16);
    // 0x801E3B1C: lw          $a3, -0x7704($a3)
    ctx->r7 = MEM_W(ctx->r7, -0X7704);
    // 0x801E3B20: addiu       $t1, $zero, 0x5B
    ctx->r9 = ADD32(0, 0X5B);
    // 0x801E3B24: sw          $t1, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r9;
    // 0x801E3B28: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x801E3B2C: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x801E3B30: addiu       $a2, $zero, 0x20
    ctx->r6 = ADD32(0, 0X20);
    // 0x801E3B34: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    // 0x801E3B38: jal         0x801E3EE0
    // 0x801E3B3C: addiu       $a3, $a3, 0xAB
    ctx->r7 = ADD32(ctx->r7, 0XAB);
    func_801E3EE0(rdram, ctx);
        goto after_13;
    // 0x801E3B3C: addiu       $a3, $a3, 0xAB
    ctx->r7 = ADD32(ctx->r7, 0XAB);
    after_13:
    // 0x801E3B40: lui         $a3, 0x8023
    ctx->r7 = S32(0X8023 << 16);
    // 0x801E3B44: lw          $a3, -0x7704($a3)
    ctx->r7 = MEM_W(ctx->r7, -0X7704);
    // 0x801E3B48: addiu       $t2, $zero, 0x5B
    ctx->r10 = ADD32(0, 0X5B);
    // 0x801E3B4C: sw          $t2, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r10;
    // 0x801E3B50: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x801E3B54: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x801E3B58: addiu       $a2, $zero, 0x3E
    ctx->r6 = ADD32(0, 0X3E);
    // 0x801E3B5C: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    // 0x801E3B60: jal         0x801E3EE0
    // 0x801E3B64: addiu       $a3, $a3, 0x142
    ctx->r7 = ADD32(ctx->r7, 0X142);
    func_801E3EE0(rdram, ctx);
        goto after_14;
    // 0x801E3B64: addiu       $a3, $a3, 0x142
    ctx->r7 = ADD32(ctx->r7, 0X142);
    after_14:
    // 0x801E3B68: lui         $v1, 0x801C
    ctx->r3 = S32(0X801C << 16);
    // 0x801E3B6C: addiu       $v1, $v1, 0x2928
    ctx->r3 = ADD32(ctx->r3, 0X2928);
    // 0x801E3B70: lw          $t3, 0x0($v1)
    ctx->r11 = MEM_W(ctx->r3, 0X0);
    // 0x801E3B74: or          $s3, $v0, $zero
    ctx->r19 = ctx->r2 | 0;
    // 0x801E3B78: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x801E3B7C: bne         $t3, $zero, L_801E3BA8
    if (ctx->r11 != 0) {
        // 0x801E3B80: or          $a1, $zero, $zero
        ctx->r5 = 0 | 0;
            goto L_801E3BA8;
    }
    // 0x801E3B80: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x801E3B84: lui         $a3, 0x8023
    ctx->r7 = S32(0X8023 << 16);
    // 0x801E3B88: lw          $a3, -0x7704($a3)
    ctx->r7 = MEM_W(ctx->r7, -0X7704);
    // 0x801E3B8C: addiu       $t4, $zero, 0xB8
    ctx->r12 = ADD32(0, 0XB8);
    // 0x801E3B90: sw          $t4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r12;
    // 0x801E3B94: addiu       $a2, $zero, 0x1A
    ctx->r6 = ADD32(0, 0X1A);
    // 0x801E3B98: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    // 0x801E3B9C: jal         0x801E3EE0
    // 0x801E3BA0: addiu       $a3, $a3, 0x12
    ctx->r7 = ADD32(ctx->r7, 0X12);
    func_801E3EE0(rdram, ctx);
        goto after_15;
    // 0x801E3BA0: addiu       $a3, $a3, 0x12
    ctx->r7 = ADD32(ctx->r7, 0X12);
    after_15:
    // 0x801E3BA4: or          $s3, $v0, $zero
    ctx->r19 = ctx->r2 | 0;
L_801E3BA8:
    // 0x801E3BA8: lui         $fp, 0x8022
    ctx->r30 = S32(0X8022 << 16);
    // 0x801E3BAC: addiu       $fp, $fp, 0x6E44
    ctx->r30 = ADD32(ctx->r30, 0X6E44);
    // 0x801E3BB0: or          $s1, $zero, $zero
    ctx->r17 = 0 | 0;
    // 0x801E3BB4: addiu       $s4, $zero, 0x70
    ctx->r20 = ADD32(0, 0X70);
    // 0x801E3BB8: or          $s6, $zero, $zero
    ctx->r22 = 0 | 0;
    // 0x801E3BBC: addiu       $s7, $sp, 0xA4
    ctx->r23 = ADD32(ctx->r29, 0XA4);
L_801E3BC0:
    // 0x801E3BC0: lui         $v1, 0x801C
    ctx->r3 = S32(0X801C << 16);
    // 0x801E3BC4: addiu       $v1, $v1, 0x2928
    ctx->r3 = ADD32(ctx->r3, 0X2928);
    // 0x801E3BC8: lw          $v0, 0x0($v1)
    ctx->r2 = MEM_W(ctx->r3, 0X0);
    // 0x801E3BCC: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
    // 0x801E3BD0: addiu       $a2, $zero, 0xFF
    ctx->r6 = ADD32(0, 0XFF);
    // 0x801E3BD4: beq         $v0, $zero, L_801E3C1C
    if (ctx->r2 == 0) {
        // 0x801E3BD8: addiu       $a3, $zero, 0xFF
        ctx->r7 = ADD32(0, 0XFF);
            goto L_801E3C1C;
    }
    // 0x801E3BD8: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    // 0x801E3BDC: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x801E3BE0: bne         $v0, $at, L_801E3C04
    if (ctx->r2 != ctx->r1) {
        // 0x801E3BE4: addiu       $t6, $s1, 0x1
        ctx->r14 = ADD32(ctx->r17, 0X1);
            goto L_801E3C04;
    }
    // 0x801E3BE4: addiu       $t6, $s1, 0x1
    ctx->r14 = ADD32(ctx->r17, 0X1);
    // 0x801E3BE8: addiu       $t5, $s1, 0x1
    ctx->r13 = ADD32(ctx->r17, 0X1);
    // 0x801E3BEC: bne         $t5, $v0, L_801E3BFC
    if (ctx->r13 != ctx->r2) {
        // 0x801E3BF0: nop
    
            goto L_801E3BFC;
    }
    // 0x801E3BF0: nop

    // 0x801E3BF4: b           L_801E3C20
    // 0x801E3BF8: addiu       $a1, $zero, 0x4
    ctx->r5 = ADD32(0, 0X4);
        goto L_801E3C20;
    // 0x801E3BF8: addiu       $a1, $zero, 0x4
    ctx->r5 = ADD32(0, 0X4);
L_801E3BFC:
    // 0x801E3BFC: b           L_801E3C20
    // 0x801E3C00: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
        goto L_801E3C20;
    // 0x801E3C00: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
L_801E3C04:
    // 0x801E3C04: bne         $t6, $v0, L_801E3C14
    if (ctx->r14 != ctx->r2) {
        // 0x801E3C08: nop
    
            goto L_801E3C14;
    }
    // 0x801E3C08: nop

    // 0x801E3C0C: b           L_801E3C20
    // 0x801E3C10: addiu       $a1, $zero, 0x6
    ctx->r5 = ADD32(0, 0X6);
        goto L_801E3C20;
    // 0x801E3C10: addiu       $a1, $zero, 0x6
    ctx->r5 = ADD32(0, 0X6);
L_801E3C14:
    // 0x801E3C14: b           L_801E3C20
    // 0x801E3C18: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
        goto L_801E3C20;
    // 0x801E3C18: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
L_801E3C1C:
    // 0x801E3C1C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
L_801E3C20:
    // 0x801E3C20: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x801E3C24: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x801E3C28: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x801E3C2C: addiu       $t0, $zero, 0xFF
    ctx->r8 = ADD32(0, 0XFF);
    // 0x801E3C30: addiu       $t1, $zero, 0xFF
    ctx->r9 = ADD32(0, 0XFF);
    // 0x801E3C34: addiu       $t2, $zero, 0xFF
    ctx->r10 = ADD32(0, 0XFF);
    // 0x801E3C38: addiu       $t3, $zero, 0xFF
    ctx->r11 = ADD32(0, 0XFF);
    // 0x801E3C3C: addiu       $t4, $zero, 0xFF
    ctx->r12 = ADD32(0, 0XFF);
    // 0x801E3C40: addiu       $t5, $zero, 0xFF
    ctx->r13 = ADD32(0, 0XFF);
    // 0x801E3C44: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x801E3C48: sw          $t6, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r14;
    // 0x801E3C4C: sw          $t5, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r13;
    // 0x801E3C50: sw          $t4, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r12;
    // 0x801E3C54: sw          $t3, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r11;
    // 0x801E3C58: sw          $t2, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r10;
    // 0x801E3C5C: sw          $t1, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r9;
    // 0x801E3C60: sw          $t0, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r8;
    // 0x801E3C64: sw          $t9, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r25;
    // 0x801E3C68: sw          $t8, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r24;
    // 0x801E3C6C: jal         0x801E946C
    // 0x801E3C70: sw          $t7, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r15;
    func_801E946C(rdram, ctx);
        goto after_16;
    // 0x801E3C70: sw          $t7, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r15;
    after_16:
    // 0x801E3C74: lui         $t7, 0x800E
    ctx->r15 = S32(0X800E << 16);
    // 0x801E3C78: lw          $t7, -0x7E90($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X7E90);
    // 0x801E3C7C: lui         $t0, 0x801C
    ctx->r8 = S32(0X801C << 16);
    // 0x801E3C80: addiu       $t0, $t0, 0x26E8
    ctx->r8 = ADD32(ctx->r8, 0X26E8);
    // 0x801E3C84: sll         $t8, $t7, 2
    ctx->r24 = S32(ctx->r15 << 2);
    // 0x801E3C88: subu        $t8, $t8, $t7
    ctx->r24 = SUB32(ctx->r24, ctx->r15);
    // 0x801E3C8C: sll         $t8, $t8, 4
    ctx->r24 = S32(ctx->r24 << 4);
    // 0x801E3C90: addu        $t9, $t8, $s6
    ctx->r25 = ADD32(ctx->r24, ctx->r22);
    // 0x801E3C94: andi        $t1, $s1, 0x1
    ctx->r9 = ctx->r17 & 0X1;
    // 0x801E3C98: or          $s3, $v0, $zero
    ctx->r19 = ctx->r2 | 0;
    // 0x801E3C9C: beq         $t1, $zero, L_801E3CB0
    if (ctx->r9 == 0) {
        // 0x801E3CA0: addu        $s2, $t9, $t0
        ctx->r18 = ADD32(ctx->r25, ctx->r8);
            goto L_801E3CB0;
    }
    // 0x801E3CA0: addu        $s2, $t9, $t0
    ctx->r18 = ADD32(ctx->r25, ctx->r8);
    // 0x801E3CA4: lui         $s0, 0x8023
    ctx->r16 = S32(0X8023 << 16);
    // 0x801E3CA8: b           L_801E3CB8
    // 0x801E3CAC: lw          $s0, -0x7704($s0)
    ctx->r16 = MEM_W(ctx->r16, -0X7704);
        goto L_801E3CB8;
    // 0x801E3CAC: lw          $s0, -0x7704($s0)
    ctx->r16 = MEM_W(ctx->r16, -0X7704);
L_801E3CB0:
    // 0x801E3CB0: lui         $s0, 0x8023
    ctx->r16 = S32(0X8023 << 16);
    // 0x801E3CB4: lw          $s0, -0x7708($s0)
    ctx->r16 = MEM_W(ctx->r16, -0X7708);
L_801E3CB8:
    // 0x801E3CB8: lui         $a1, 0x8022
    ctx->r5 = S32(0X8022 << 16);
    // 0x801E3CBC: addiu       $s5, $s1, 0x1
    ctx->r21 = ADD32(ctx->r17, 0X1);
    // 0x801E3CC0: or          $a2, $s5, $zero
    ctx->r6 = ctx->r21 | 0;
    // 0x801E3CC4: addiu       $a1, $a1, 0x6380
    ctx->r5 = ADD32(ctx->r5, 0X6380);
    // 0x801E3CC8: jal         0x800CA210
    // 0x801E3CCC: or          $a0, $s7, $zero
    ctx->r4 = ctx->r23 | 0;
    func_800CA210(rdram, ctx);
        goto after_17;
    // 0x801E3CCC: or          $a0, $s7, $zero
    ctx->r4 = ctx->r23 | 0;
    after_17:
    // 0x801E3CD0: lb          $t2, 0x1($fp)
    ctx->r10 = MEM_B(ctx->r30, 0X1);
    // 0x801E3CD4: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
    // 0x801E3CD8: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x801E3CDC: addu        $a3, $t2, $s0
    ctx->r7 = ADD32(ctx->r10, ctx->r16);
    // 0x801E3CE0: addiu       $a3, $a3, 0x11
    ctx->r7 = ADD32(ctx->r7, 0X11);
    // 0x801E3CE4: or          $a2, $s7, $zero
    ctx->r6 = ctx->r23 | 0;
    // 0x801E3CE8: jal         0x801E9858
    // 0x801E3CEC: sw          $s4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r20;
    func_801E9858(rdram, ctx);
        goto after_18;
    // 0x801E3CEC: sw          $s4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r20;
    after_18:
    // 0x801E3CF0: lw          $t3, 0x8($s2)
    ctx->r11 = MEM_W(ctx->r18, 0X8);
    // 0x801E3CF4: or          $s3, $v0, $zero
    ctx->r19 = ctx->r2 | 0;
    // 0x801E3CF8: or          $a0, $s7, $zero
    ctx->r4 = ctx->r23 | 0;
    // 0x801E3CFC: bne         $t3, $zero, L_801E3D24
    if (ctx->r11 != 0) {
        // 0x801E3D00: lui         $a1, 0x8022
        ctx->r5 = S32(0X8022 << 16);
            goto L_801E3D24;
    }
    // 0x801E3D00: lui         $a1, 0x8022
    ctx->r5 = S32(0X8022 << 16);
    // 0x801E3D04: lui         $a1, 0x8022
    ctx->r5 = S32(0X8022 << 16);
    // 0x801E3D08: lui         $a2, 0x8022
    ctx->r6 = S32(0X8022 << 16);
    // 0x801E3D0C: addiu       $a2, $a2, 0x6388
    ctx->r6 = ADD32(ctx->r6, 0X6388);
    // 0x801E3D10: addiu       $a1, $a1, 0x6384
    ctx->r5 = ADD32(ctx->r5, 0X6384);
    // 0x801E3D14: jal         0x800CA210
    // 0x801E3D18: or          $a0, $s7, $zero
    ctx->r4 = ctx->r23 | 0;
    func_800CA210(rdram, ctx);
        goto after_19;
    // 0x801E3D18: or          $a0, $s7, $zero
    ctx->r4 = ctx->r23 | 0;
    after_19:
    // 0x801E3D1C: b           L_801E3D38
    // 0x801E3D20: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
        goto L_801E3D38;
    // 0x801E3D20: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
L_801E3D24:
    // 0x801E3D24: lui         $a2, 0x8022
    ctx->r6 = S32(0X8022 << 16);
    // 0x801E3D28: addiu       $a2, $a2, 0x6390
    ctx->r6 = ADD32(ctx->r6, 0X6390);
    // 0x801E3D2C: jal         0x800CA210
    // 0x801E3D30: addiu       $a1, $a1, 0x638C
    ctx->r5 = ADD32(ctx->r5, 0X638C);
    func_800CA210(rdram, ctx);
        goto after_20;
    // 0x801E3D30: addiu       $a1, $a1, 0x638C
    ctx->r5 = ADD32(ctx->r5, 0X638C);
    after_20:
    // 0x801E3D34: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
L_801E3D38:
    // 0x801E3D38: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x801E3D3C: or          $a2, $s7, $zero
    ctx->r6 = ctx->r23 | 0;
    // 0x801E3D40: addiu       $a3, $s0, 0x3B
    ctx->r7 = ADD32(ctx->r16, 0X3B);
    // 0x801E3D44: jal         0x801E9858
    // 0x801E3D48: sw          $s4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r20;
    func_801E9858(rdram, ctx);
        goto after_21;
    // 0x801E3D48: sw          $s4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r20;
    after_21:
    // 0x801E3D4C: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x801E3D50: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x801E3D54: addiu       $a2, $s2, 0xC
    ctx->r6 = ADD32(ctx->r18, 0XC);
    // 0x801E3D58: addiu       $a3, $s0, 0xAB
    ctx->r7 = ADD32(ctx->r16, 0XAB);
    // 0x801E3D5C: jal         0x801E9858
    // 0x801E3D60: sw          $s4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r20;
    func_801E9858(rdram, ctx);
        goto after_22;
    // 0x801E3D60: sw          $s4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r20;
    after_22:
    // 0x801E3D64: lw          $a2, 0x0($s2)
    ctx->r6 = MEM_W(ctx->r18, 0X0);
    // 0x801E3D68: sw          $s4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r20;
    // 0x801E3D6C: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x801E3D70: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x801E3D74: jal         0x80094200
    // 0x801E3D78: addiu       $a3, $s0, 0x138
    ctx->r7 = ADD32(ctx->r16, 0X138);
    func_80094200(rdram, ctx);
        goto after_23;
    // 0x801E3D78: addiu       $a3, $s0, 0x138
    ctx->r7 = ADD32(ctx->r16, 0X138);
    after_23:
    // 0x801E3D7C: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x801E3D80: or          $s1, $s5, $zero
    ctx->r17 = ctx->r21 | 0;
    // 0x801E3D84: addiu       $s4, $s4, 0x12
    ctx->r20 = ADD32(ctx->r20, 0X12);
    // 0x801E3D88: addiu       $s6, $s6, 0x10
    ctx->r22 = ADD32(ctx->r22, 0X10);
    // 0x801E3D8C: addiu       $fp, $fp, 0x1
    ctx->r30 = ADD32(ctx->r30, 0X1);
    // 0x801E3D90: bne         $s5, $at, L_801E3BC0
    if (ctx->r21 != ctx->r1) {
        // 0x801E3D94: or          $s3, $v0, $zero
        ctx->r19 = ctx->r2 | 0;
            goto L_801E3BC0;
    }
    // 0x801E3D94: or          $s3, $v0, $zero
    ctx->r19 = ctx->r2 | 0;
    // 0x801E3D98: lui         $t4, 0x801C
    ctx->r12 = S32(0X801C << 16);
    // 0x801E3D9C: lw          $t4, 0x2928($t4)
    ctx->r12 = MEM_W(ctx->r12, 0X2928);
    // 0x801E3DA0: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x801E3DA4: addiu       $a1, $zero, 0x6
    ctx->r5 = ADD32(0, 0X6);
    // 0x801E3DA8: bne         $t4, $zero, L_801E3EA0
    if (ctx->r12 != 0) {
        // 0x801E3DAC: addiu       $a2, $zero, 0xFF
        ctx->r6 = ADD32(0, 0XFF);
            goto L_801E3EA0;
    }
    // 0x801E3DAC: addiu       $a2, $zero, 0xFF
    ctx->r6 = ADD32(0, 0XFF);
    // 0x801E3DB0: addiu       $t5, $zero, 0xFF
    ctx->r13 = ADD32(0, 0XFF);
    // 0x801E3DB4: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x801E3DB8: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x801E3DBC: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x801E3DC0: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x801E3DC4: addiu       $t0, $zero, 0xFF
    ctx->r8 = ADD32(0, 0XFF);
    // 0x801E3DC8: addiu       $t1, $zero, 0xFF
    ctx->r9 = ADD32(0, 0XFF);
    // 0x801E3DCC: addiu       $t2, $zero, 0xFF
    ctx->r10 = ADD32(0, 0XFF);
    // 0x801E3DD0: addiu       $t3, $zero, 0xFF
    ctx->r11 = ADD32(0, 0XFF);
    // 0x801E3DD4: addiu       $t4, $zero, 0xFF
    ctx->r12 = ADD32(0, 0XFF);
    // 0x801E3DD8: sw          $t4, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r12;
    // 0x801E3DDC: sw          $t3, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r11;
    // 0x801E3DE0: sw          $t2, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r10;
    // 0x801E3DE4: sw          $t1, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r9;
    // 0x801E3DE8: sw          $t0, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r8;
    // 0x801E3DEC: sw          $t9, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r25;
    // 0x801E3DF0: sw          $t8, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r24;
    // 0x801E3DF4: sw          $t7, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r15;
    // 0x801E3DF8: sw          $t6, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r14;
    // 0x801E3DFC: sw          $t5, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r13;
    // 0x801E3E00: jal         0x801E946C
    // 0x801E3E04: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    func_801E946C(rdram, ctx);
        goto after_24;
    // 0x801E3E04: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    after_24:
    // 0x801E3E08: lui         $t5, 0x801D
    ctx->r13 = S32(0X801D << 16);
    // 0x801E3E0C: lw          $t5, -0x4CD4($t5)
    ctx->r13 = MEM_W(ctx->r13, -0X4CD4);
    // 0x801E3E10: or          $s3, $v0, $zero
    ctx->r19 = ctx->r2 | 0;
    // 0x801E3E14: or          $a0, $s7, $zero
    ctx->r4 = ctx->r23 | 0;
    // 0x801E3E18: bne         $t5, $zero, L_801E3E40
    if (ctx->r13 != 0) {
        // 0x801E3E1C: lui         $a1, 0x8022
        ctx->r5 = S32(0X8022 << 16);
            goto L_801E3E40;
    }
    // 0x801E3E1C: lui         $a1, 0x8022
    ctx->r5 = S32(0X8022 << 16);
    // 0x801E3E20: lui         $a1, 0x8022
    ctx->r5 = S32(0X8022 << 16);
    // 0x801E3E24: lui         $a2, 0x8022
    ctx->r6 = S32(0X8022 << 16);
    // 0x801E3E28: addiu       $a2, $a2, 0x6398
    ctx->r6 = ADD32(ctx->r6, 0X6398);
    // 0x801E3E2C: addiu       $a1, $a1, 0x6394
    ctx->r5 = ADD32(ctx->r5, 0X6394);
    // 0x801E3E30: jal         0x800CA210
    // 0x801E3E34: or          $a0, $s7, $zero
    ctx->r4 = ctx->r23 | 0;
    func_800CA210(rdram, ctx);
        goto after_25;
    // 0x801E3E34: or          $a0, $s7, $zero
    ctx->r4 = ctx->r23 | 0;
    after_25:
    // 0x801E3E38: b           L_801E3E50
    // 0x801E3E3C: nop

        goto L_801E3E50;
    // 0x801E3E3C: nop

L_801E3E40:
    // 0x801E3E40: lui         $a2, 0x8022
    ctx->r6 = S32(0X8022 << 16);
    // 0x801E3E44: addiu       $a2, $a2, 0x63A0
    ctx->r6 = ADD32(ctx->r6, 0X63A0);
    // 0x801E3E48: jal         0x800CA210
    // 0x801E3E4C: addiu       $a1, $a1, 0x639C
    ctx->r5 = ADD32(ctx->r5, 0X639C);
    func_800CA210(rdram, ctx);
        goto after_26;
    // 0x801E3E4C: addiu       $a1, $a1, 0x639C
    ctx->r5 = ADD32(ctx->r5, 0X639C);
    after_26:
L_801E3E50:
    // 0x801E3E50: lui         $a3, 0x8023
    ctx->r7 = S32(0X8023 << 16);
    // 0x801E3E54: lw          $a3, -0x7704($a3)
    ctx->r7 = MEM_W(ctx->r7, -0X7704);
    // 0x801E3E58: addiu       $t6, $zero, 0xC4
    ctx->r14 = ADD32(0, 0XC4);
    // 0x801E3E5C: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x801E3E60: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
    // 0x801E3E64: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x801E3E68: or          $a2, $s7, $zero
    ctx->r6 = ctx->r23 | 0;
    // 0x801E3E6C: jal         0x801E9858
    // 0x801E3E70: addiu       $a3, $a3, 0x3B
    ctx->r7 = ADD32(ctx->r7, 0X3B);
    func_801E9858(rdram, ctx);
        goto after_27;
    // 0x801E3E70: addiu       $a3, $a3, 0x3B
    ctx->r7 = ADD32(ctx->r7, 0X3B);
    after_27:
    // 0x801E3E74: lui         $a3, 0x8023
    ctx->r7 = S32(0X8023 << 16);
    // 0x801E3E78: lw          $a3, -0x7704($a3)
    ctx->r7 = MEM_W(ctx->r7, -0X7704);
    // 0x801E3E7C: lui         $a2, 0x801C
    ctx->r6 = S32(0X801C << 16);
    // 0x801E3E80: addiu       $t7, $zero, 0xC4
    ctx->r15 = ADD32(0, 0XC4);
    // 0x801E3E84: sw          $t7, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r15;
    // 0x801E3E88: lw          $a2, 0x26D0($a2)
    ctx->r6 = MEM_W(ctx->r6, 0X26D0);
    // 0x801E3E8C: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x801E3E90: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x801E3E94: jal         0x80094200
    // 0x801E3E98: addiu       $a3, $s0, 0x138
    ctx->r7 = ADD32(ctx->r16, 0X138);
    func_80094200(rdram, ctx);
        goto after_28;
    // 0x801E3E98: addiu       $a3, $s0, 0x138
    ctx->r7 = ADD32(ctx->r16, 0X138);
    after_28:
    // 0x801E3E9C: or          $s3, $v0, $zero
    ctx->r19 = ctx->r2 | 0;
L_801E3EA0:
    // 0x801E3EA0: lw          $ra, 0x64($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X64);
    // 0x801E3EA4: or          $v0, $s3, $zero
    ctx->r2 = ctx->r19 | 0;
    // 0x801E3EA8: lw          $s3, 0x4C($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X4C);
    // 0x801E3EAC: lw          $s0, 0x40($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X40);
    // 0x801E3EB0: lw          $s1, 0x44($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X44);
    // 0x801E3EB4: lw          $s2, 0x48($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X48);
    // 0x801E3EB8: lw          $s4, 0x50($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X50);
    // 0x801E3EBC: lw          $s5, 0x54($sp)
    ctx->r21 = MEM_W(ctx->r29, 0X54);
    // 0x801E3EC0: lw          $s6, 0x58($sp)
    ctx->r22 = MEM_W(ctx->r29, 0X58);
    // 0x801E3EC4: lw          $s7, 0x5C($sp)
    ctx->r23 = MEM_W(ctx->r29, 0X5C);
    // 0x801E3EC8: lw          $fp, 0x60($sp)
    ctx->r30 = MEM_W(ctx->r29, 0X60);
    // 0x801E3ECC: jr          $ra
    // 0x801E3ED0: addiu       $sp, $sp, 0xB8
    ctx->r29 = ADD32(ctx->r29, 0XB8);
    return;
    // 0x801E3ED0: addiu       $sp, $sp, 0xB8
    ctx->r29 = ADD32(ctx->r29, 0XB8);
    // 0x801E3ED4: nop

    // 0x801E3ED8: nop

    // 0x801E3EDC: nop

;}
RECOMP_FUNC void func_801E3EE0(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // Message-text strips use the same signed menu plane as their frames.
    extern int32_t wr64_menu_half_extension(void);
    extern void wr64_menu_promote_waku_rect(uint8_t*, uint32_t, int32_t, int32_t);
    const int32_t wr64MessageHalf = wr64_menu_half_extension();
    const int32_t wr64MessageX = (int32_t)ctx->r7;
    // 0x801E3EE0: addiu       $sp, $sp, -0x48
    ctx->r29 = ADD32(ctx->r29, -0X48);
    // 0x801E3EE4: sltiu       $at, $a1, 0x5
    ctx->r1 = ctx->r5 < 0X5 ? 1 : 0;
    // 0x801E3EE8: sw          $ra, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r31;
    // 0x801E3EEC: sw          $fp, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r30;
    // 0x801E3EF0: sw          $s7, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r23;
    // 0x801E3EF4: sw          $s6, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r22;
    // 0x801E3EF8: sw          $s5, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r21;
    // 0x801E3EFC: sw          $s4, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r20;
    // 0x801E3F00: sw          $s3, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r19;
    // 0x801E3F04: sw          $s2, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r18;
    // 0x801E3F08: sw          $s1, 0xC($sp)
    MEM_W(0XC, ctx->r29) = ctx->r17;
    // 0x801E3F0C: sw          $s0, 0x8($sp)
    MEM_W(0X8, ctx->r29) = ctx->r16;
    // 0x801E3F10: sw          $a3, 0x54($sp)
    MEM_W(0X54, ctx->r29) = ctx->r7;
    // 0x801E3F14: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
    // 0x801E3F18: beq         $at, $zero, L_801E4030
    if (ctx->r1 == 0) {
        // 0x801E3F1C: addiu       $v1, $zero, 0x1
        ctx->r3 = ADD32(0, 0X1);
            goto L_801E4030;
    }
    // 0x801E3F1C: addiu       $v1, $zero, 0x1
    ctx->r3 = ADD32(0, 0X1);
    // 0x801E3F20: sll         $t6, $a1, 2
    ctx->r14 = S32(ctx->r5 << 2);
    // 0x801E3F24: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E3F28: addu        $at, $at, $t6
    gpr jr_addend_801E3F30 = ctx->r14;
    ctx->r1 = ADD32(ctx->r1, ctx->r14);
    // 0x801E3F2C: lw          $t6, 0x6B80($at)
    ctx->r14 = ADD32(ctx->r1, 0X6B80);
    // 0x801E3F30: jr          $t6
    // 0x801E3F34: nop

    switch (jr_addend_801E3F30 >> 2) {
        case 0: goto L_801E3F38; break;
        case 1: goto L_801E3F78; break;
        case 2: goto L_801E3FA0; break;
        case 3: goto L_801E3FDC; break;
        case 4: goto L_801E3F58; break;
        default: switch_error(__func__, 0x801E3F30, 0x80226B80);
    }
    // 0x801E3F34: nop

L_801E3F38:
    // 0x801E3F38: lui         $t8, 0x8022
    ctx->r24 = S32(0X8022 << 16);
    // 0x801E3F3C: addiu       $t8, $t8, 0x63C0
    ctx->r24 = ADD32(ctx->r24, 0X63C0);
    // 0x801E3F40: sll         $t7, $a2, 3
    ctx->r15 = S32(ctx->r6 << 3);
    // 0x801E3F44: addiu       $t4, $zero, 0x8
    ctx->r12 = ADD32(0, 0X8);
    // 0x801E3F48: addu        $t1, $t7, $t8
    ctx->r9 = ADD32(ctx->r15, ctx->r24);
    // 0x801E3F4C: sw          $t1, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r9;
    // 0x801E3F50: b           L_801E4030
    // 0x801E3F54: sw          $t4, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r12;
        goto L_801E4030;
    // 0x801E3F54: sw          $t4, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r12;
L_801E3F58:
    // 0x801E3F58: lui         $t6, 0x8022
    ctx->r14 = S32(0X8022 << 16);
    // 0x801E3F5C: addiu       $t6, $t6, 0x64F8
    ctx->r14 = ADD32(ctx->r14, 0X64F8);
    // 0x801E3F60: sll         $t9, $a2, 3
    ctx->r25 = S32(ctx->r6 << 3);
    // 0x801E3F64: addiu       $t4, $zero, 0xA
    ctx->r12 = ADD32(0, 0XA);
    // 0x801E3F68: addu        $t1, $t9, $t6
    ctx->r9 = ADD32(ctx->r25, ctx->r14);
    // 0x801E3F6C: sw          $t1, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r9;
    // 0x801E3F70: b           L_801E4030
    // 0x801E3F74: sw          $t4, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r12;
        goto L_801E4030;
    // 0x801E3F74: sw          $t4, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r12;
L_801E3F78:
    // 0x801E3F78: lw          $a1, 0x5C($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X5C);
    // 0x801E3F7C: lui         $t8, 0x8022
    ctx->r24 = S32(0X8022 << 16);
    // 0x801E3F80: addiu       $t8, $t8, 0x6568
    ctx->r24 = ADD32(ctx->r24, 0X6568);
    // 0x801E3F84: sll         $t7, $a2, 3
    ctx->r15 = S32(ctx->r6 << 3);
    // 0x801E3F88: addu        $a3, $t7, $t8
    ctx->r7 = ADD32(ctx->r15, ctx->r24);
    // 0x801E3F8C: addiu       $t4, $a1, 0xA
    ctx->r12 = ADD32(ctx->r5, 0XA);
    // 0x801E3F90: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    // 0x801E3F94: sw          $t4, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r12;
    // 0x801E3F98: b           L_801E4030
    // 0x801E3F9C: sw          $a3, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r7;
        goto L_801E4030;
    // 0x801E3F9C: sw          $a3, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r7;
L_801E3FA0:
    // 0x801E3FA0: lui         $t6, 0x8022
    ctx->r14 = S32(0X8022 << 16);
    // 0x801E3FA4: addiu       $t6, $t6, 0x6A48
    ctx->r14 = ADD32(ctx->r14, 0X6A48);
    // 0x801E3FA8: sll         $t9, $a2, 3
    ctx->r25 = S32(ctx->r6 << 3);
    // 0x801E3FAC: addu        $t1, $t9, $t6
    ctx->r9 = ADD32(ctx->r25, ctx->r14);
    // 0x801E3FB0: lw          $t7, 0x4($t1)
    ctx->r15 = MEM_W(ctx->r9, 0X4);
    // 0x801E3FB4: addiu       $t4, $zero, 0x12
    ctx->r12 = ADD32(0, 0X12);
    // 0x801E3FB8: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    // 0x801E3FBC: slti        $at, $t7, 0xE4
    ctx->r1 = SIGNED(ctx->r15) < 0XE4 ? 1 : 0;
    // 0x801E3FC0: bnel        $at, $zero, L_801E3FD4
    if (ctx->r1 != 0) {
        // 0x801E3FC4: sw          $t1, 0x34($sp)
        MEM_W(0X34, ctx->r29) = ctx->r9;
            goto L_801E3FD4;
    }
    goto skip_0;
    // 0x801E3FC4: sw          $t1, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r9;
    skip_0:
    // 0x801E3FC8: addiu       $v1, $zero, 0x2
    ctx->r3 = ADD32(0, 0X2);
    // 0x801E3FCC: addiu       $t4, $zero, 0x9
    ctx->r12 = ADD32(0, 0X9);
    // 0x801E3FD0: sw          $t1, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r9;
L_801E3FD4:
    // 0x801E3FD4: b           L_801E4030
    // 0x801E3FD8: sw          $t4, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r12;
        goto L_801E4030;
    // 0x801E3FD8: sw          $t4, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r12;
L_801E3FDC:
    // 0x801E3FDC: lw          $a1, 0x5C($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X5C);
    // 0x801E3FE0: lui         $t9, 0x8022
    ctx->r25 = S32(0X8022 << 16);
    // 0x801E3FE4: addiu       $t9, $t9, 0x6890
    ctx->r25 = ADD32(ctx->r25, 0X6890);
    // 0x801E3FE8: sll         $t8, $a2, 3
    ctx->r24 = S32(ctx->r6 << 3);
    // 0x801E3FEC: addu        $a3, $t8, $t9
    ctx->r7 = ADD32(ctx->r24, ctx->r25);
    // 0x801E3FF0: addiu       $at, $zero, 0x6
    ctx->r1 = ADD32(0, 0X6);
    // 0x801E3FF4: or          $t1, $a3, $zero
    ctx->r9 = ctx->r7 | 0;
    // 0x801E3FF8: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    // 0x801E3FFC: bne         $a1, $at, L_801E4010
    if (ctx->r5 != ctx->r1) {
        // 0x801E4000: addiu       $t4, $a1, 0xE
        ctx->r12 = ADD32(ctx->r5, 0XE);
            goto L_801E4010;
    }
    // 0x801E4000: addiu       $t4, $a1, 0xE
    ctx->r12 = ADD32(ctx->r5, 0XE);
    // 0x801E4004: addiu       $v1, $zero, 0x5
    ctx->r3 = ADD32(0, 0X5);
    // 0x801E4008: b           L_801E4028
    // 0x801E400C: addiu       $t4, $zero, 0x4
    ctx->r12 = ADD32(0, 0X4);
        goto L_801E4028;
    // 0x801E400C: addiu       $t4, $zero, 0x4
    ctx->r12 = ADD32(0, 0X4);
L_801E4010:
    // 0x801E4010: lw          $t6, 0x4($a3)
    ctx->r14 = MEM_W(ctx->r7, 0X4);
    // 0x801E4014: slti        $at, $t6, 0x123
    ctx->r1 = SIGNED(ctx->r14) < 0X123 ? 1 : 0;
    // 0x801E4018: bnel        $at, $zero, L_801E402C
    if (ctx->r1 != 0) {
        // 0x801E401C: sw          $t1, 0x34($sp)
        MEM_W(0X34, ctx->r29) = ctx->r9;
            goto L_801E402C;
    }
    goto skip_1;
    // 0x801E401C: sw          $t1, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r9;
    skip_1:
    // 0x801E4020: addiu       $v1, $zero, 0x2
    ctx->r3 = ADD32(0, 0X2);
    // 0x801E4024: addiu       $t4, $zero, 0x7
    ctx->r12 = ADD32(0, 0X7);
L_801E4028:
    // 0x801E4028: sw          $t1, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r9;
L_801E402C:
    // 0x801E402C: sw          $t4, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r12;
L_801E4030:
    // 0x801E4030: lw          $t1, 0x34($sp)
    ctx->r9 = MEM_W(ctx->r29, 0X34);
    // 0x801E4034: lw          $t4, 0x40($sp)
    ctx->r12 = MEM_W(ctx->r29, 0X40);
    // 0x801E4038: or          $t5, $zero, $zero
    ctx->r13 = 0 | 0;
    // 0x801E403C: sw          $v0, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r2;
    // 0x801E4040: blez        $v1, L_801E4408
    if (SIGNED(ctx->r3) <= 0) {
        // 0x801E4044: sw          $v1, 0x38($sp)
        MEM_W(0X38, ctx->r29) = ctx->r3;
            goto L_801E4408;
    }
    // 0x801E4044: sw          $v1, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r3;
    // 0x801E4048: lw          $s3, 0x54($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X54);
    // 0x801E404C: lw          $s0, 0x58($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X58);
    // 0x801E4050: lui         $ra, 0x8
    ctx->r31 = S32(0X8 << 16);
    // 0x801E4054: sll         $t7, $s3, 2
    ctx->r15 = S32(ctx->r19 << 2);
    // 0x801E4058: sll         $s4, $t7, 10
    ctx->r20 = S32(ctx->r15 << 10);
    // 0x801E405C: sra         $t8, $s4, 7
    ctx->r24 = S32(SIGNED(ctx->r20) >> 7);
    // 0x801E4060: lui         $s5, 0x708
    ctx->r21 = S32(0X708 << 16);
    // 0x801E4064: ori         $s5, $s5, 0x200
    ctx->r21 = ctx->r21 | 0X200;
    // 0x801E4068: or          $s4, $t8, $zero
    ctx->r20 = ctx->r24 | 0;
    // 0x801E406C: or          $s3, $t7, $zero
    ctx->r19 = ctx->r15 | 0;
    // 0x801E4070: ori         $ra, $ra, 0x200
    ctx->r31 = ctx->r31 | 0X200;
    // 0x801E4074: lui         $fp, 0xE700
    ctx->r30 = S32(0XE700 << 16);
    // 0x801E4078: lui         $s7, 0x700
    ctx->r23 = S32(0X700 << 16);
    // 0x801E407C: lui         $s6, 0xE600
    ctx->r22 = S32(0XE600 << 16);
    // 0x801E4080: lui         $s2, 0xF568
    ctx->r18 = S32(0XF568 << 16);
    // 0x801E4084: addu        $s1, $s0, $t4
    ctx->r17 = ADD32(ctx->r16, ctx->r12);
L_801E4088:
    // 0x801E4088: lw          $t9, 0x3C($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X3C);
    // 0x801E408C: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x801E4090: lui         $t6, 0xFD70
    ctx->r14 = S32(0XFD70 << 16);
    // 0x801E4094: beq         $t9, $zero, L_801E41D8
    if (ctx->r25 == 0) {
        // 0x801E4098: lui         $t8, 0xF570
        ctx->r24 = S32(0XF570 << 16);
            goto L_801E41D8;
    }
    // 0x801E4098: lui         $t8, 0xF570
    ctx->r24 = S32(0XF570 << 16);
    // 0x801E409C: sw          $t6, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r14;
    // 0x801E40A0: lw          $t7, 0x0($t1)
    ctx->r15 = MEM_W(ctx->r9, 0X0);
    // 0x801E40A4: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x801E40A8: or          $v1, $a0, $zero
    ctx->r3 = ctx->r4 | 0;
    // 0x801E40AC: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x801E40B0: sw          $t7, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r15;
    // 0x801E40B4: or          $a1, $a0, $zero
    ctx->r5 = ctx->r4 | 0;
    // 0x801E40B8: sw          $s5, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r21;
    // 0x801E40BC: sw          $t8, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r24;
    // 0x801E40C0: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x801E40C4: or          $t2, $a0, $zero
    ctx->r10 = ctx->r4 | 0;
    // 0x801E40C8: sw          $zero, 0x4($a1)
    MEM_W(0X4, ctx->r5) = 0;
    // 0x801E40CC: sw          $s6, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r22;
    // 0x801E40D0: lui         $t9, 0xF300
    ctx->r25 = S32(0XF300 << 16);
    // 0x801E40D4: sw          $t9, 0x0($t2)
    MEM_W(0X0, ctx->r10) = ctx->r25;
    // 0x801E40D8: lw          $a2, 0x4($t1)
    ctx->r6 = MEM_W(ctx->r9, 0X4);
    // 0x801E40DC: addiu       $t3, $t4, -0x1
    ctx->r11 = ADD32(ctx->r12, -0X1);
    // 0x801E40E0: sll         $t7, $t3, 2
    ctx->r15 = S32(ctx->r11 << 2);
    // 0x801E40E4: multu       $a2, $t4
    result = U64(U32(ctx->r6)) * U64(U32(ctx->r12)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x801E40E8: andi        $t8, $t7, 0xFFF
    ctx->r24 = ctx->r15 & 0XFFF;
    // 0x801E40EC: srl         $v1, $a2, 3
    ctx->r3 = S32(U32(ctx->r6) >> 3);
    // 0x801E40F0: or          $v0, $v1, $zero
    ctx->r2 = ctx->r3 | 0;
    // 0x801E40F4: or          $t3, $t8, $zero
    ctx->r11 = ctx->r24 | 0;
    // 0x801E40F8: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x801E40FC: addiu       $t0, $zero, 0x7FF
    ctx->r8 = ADD32(0, 0X7FF);
    // 0x801E4100: mflo        $a3
    ctx->r7 = lo;
    // 0x801E4104: addiu       $a3, $a3, 0x1
    ctx->r7 = ADD32(ctx->r7, 0X1);
    // 0x801E4108: srl         $t6, $a3, 1
    ctx->r14 = S32(U32(ctx->r7) >> 1);
    // 0x801E410C: addiu       $a3, $t6, -0x1
    ctx->r7 = ADD32(ctx->r14, -0X1);
    // 0x801E4110: sltiu       $at, $a3, 0x7FF
    ctx->r1 = ctx->r7 < 0X7FF ? 1 : 0;
    // 0x801E4114: beq         $at, $zero, L_801E4124
    if (ctx->r1 == 0) {
        // 0x801E4118: nop
    
            goto L_801E4124;
    }
    // 0x801E4118: nop

    // 0x801E411C: b           L_801E4124
    // 0x801E4120: or          $t0, $a3, $zero
    ctx->r8 = ctx->r7 | 0;
        goto L_801E4124;
    // 0x801E4120: or          $t0, $a3, $zero
    ctx->r8 = ctx->r7 | 0;
L_801E4124:
    // 0x801E4124: bne         $v1, $zero, L_801E4134
    if (ctx->r3 != 0) {
        // 0x801E4128: or          $a3, $v1, $zero
        ctx->r7 = ctx->r3 | 0;
            goto L_801E4134;
    }
    // 0x801E4128: or          $a3, $v1, $zero
    ctx->r7 = ctx->r3 | 0;
    // 0x801E412C: b           L_801E4134
    // 0x801E4130: addiu       $a3, $zero, 0x1
    ctx->r7 = ADD32(0, 0X1);
        goto L_801E4134;
    // 0x801E4130: addiu       $a3, $zero, 0x1
    ctx->r7 = ADD32(0, 0X1);
L_801E4134:
    // 0x801E4134: bne         $v1, $zero, L_801E4144
    if (ctx->r3 != 0) {
        // 0x801E4138: addiu       $t9, $a3, 0x7FF
        ctx->r25 = ADD32(ctx->r7, 0X7FF);
            goto L_801E4144;
    }
    // 0x801E4138: addiu       $t9, $a3, 0x7FF
    ctx->r25 = ADD32(ctx->r7, 0X7FF);
    // 0x801E413C: b           L_801E4144
    // 0x801E4140: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
        goto L_801E4144;
    // 0x801E4140: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
L_801E4144:
    // 0x801E4144: divu        $zero, $t9, $v0
    lo = S32(U32(ctx->r25) / U32(ctx->r2)); hi = S32(U32(ctx->r25) % U32(ctx->r2));
    // 0x801E4148: mflo        $t6
    ctx->r14 = lo;
    // 0x801E414C: andi        $t7, $t6, 0xFFF
    ctx->r15 = ctx->r14 & 0XFFF;
    // 0x801E4150: andi        $t9, $t0, 0xFFF
    ctx->r25 = ctx->r8 & 0XFFF;
    // 0x801E4154: sll         $t6, $t9, 12
    ctx->r14 = S32(ctx->r25 << 12);
    // 0x801E4158: or          $t8, $t7, $s7
    ctx->r24 = ctx->r15 | ctx->r23;
    // 0x801E415C: or          $t7, $t8, $t6
    ctx->r15 = ctx->r24 | ctx->r14;
    // 0x801E4160: sw          $t7, 0x4($t2)
    MEM_W(0X4, ctx->r10) = ctx->r15;
    // 0x801E4164: or          $v1, $a0, $zero
    ctx->r3 = ctx->r4 | 0;
    // 0x801E4168: sw          $fp, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r30;
    // 0x801E416C: sw          $zero, 0x4($v1)
    MEM_W(0X4, ctx->r3) = 0;
    // 0x801E4170: lw          $t9, 0x4($t1)
    ctx->r25 = MEM_W(ctx->r9, 0X4);
    // 0x801E4174: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x801E4178: or          $a1, $a0, $zero
    ctx->r5 = ctx->r4 | 0;
    // 0x801E417C: addiu       $t8, $t9, 0x7
    ctx->r24 = ADD32(ctx->r25, 0X7);
    // 0x801E4180: srl         $t6, $t8, 3
    ctx->r14 = S32(U32(ctx->r24) >> 3);
    // 0x801E4184: andi        $t7, $t6, 0x1FF
    ctx->r15 = ctx->r14 & 0X1FF;
    // 0x801E4188: sll         $t9, $t7, 9
    ctx->r25 = S32(ctx->r15 << 9);
    // 0x801E418C: or          $t8, $t9, $s2
    ctx->r24 = ctx->r25 | ctx->r18;
    // 0x801E4190: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x801E4194: or          $a2, $a0, $zero
    ctx->r6 = ctx->r4 | 0;
    // 0x801E4198: sw          $t8, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r24;
    // 0x801E419C: lui         $t6, 0xF200
    ctx->r14 = S32(0XF200 << 16);
    // 0x801E41A0: sw          $ra, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r31;
    // 0x801E41A4: sw          $t6, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r14;
    // 0x801E41A8: lw          $t7, 0x4($t1)
    ctx->r15 = MEM_W(ctx->r9, 0X4);
    // 0x801E41AC: bne         $v0, $zero, L_801E41B8
    if (ctx->r2 != 0) {
        // 0x801E41B0: nop
    
            goto L_801E41B8;
    }
    // 0x801E41B0: nop

    // 0x801E41B4: break       7
    do_break(2149466548);
L_801E41B8:
    // 0x801E41B8: addiu       $t9, $t7, -0x1
    ctx->r25 = ADD32(ctx->r15, -0X1);
    // 0x801E41BC: sll         $t8, $t9, 2
    ctx->r24 = S32(ctx->r25 << 2);
    // 0x801E41C0: andi        $t6, $t8, 0xFFF
    ctx->r14 = ctx->r24 & 0XFFF;
    // 0x801E41C4: sll         $t7, $t6, 12
    ctx->r15 = S32(ctx->r14 << 12);
    // 0x801E41C8: or          $t9, $t7, $t3
    ctx->r25 = ctx->r15 | ctx->r11;
    // 0x801E41CC: sw          $t9, 0x4($a2)
    MEM_W(0X4, ctx->r6) = ctx->r25;
    // 0x801E41D0: b           L_801E42F8
    // 0x801E41D4: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
        goto L_801E42F8;
    // 0x801E41D4: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
L_801E41D8:
    // 0x801E41D8: lw          $t8, 0x4($t1)
    ctx->r24 = MEM_W(ctx->r9, 0X4);
    // 0x801E41DC: lui         $at, 0xFD68
    ctx->r1 = S32(0XFD68 << 16);
    // 0x801E41E0: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x801E41E4: addiu       $t6, $t8, -0x1
    ctx->r14 = ADD32(ctx->r24, -0X1);
    // 0x801E41E8: andi        $t7, $t6, 0xFFF
    ctx->r15 = ctx->r14 & 0XFFF;
    // 0x801E41EC: or          $t9, $t7, $at
    ctx->r25 = ctx->r15 | ctx->r1;
    // 0x801E41F0: sw          $t9, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r25;
    // 0x801E41F4: lw          $t6, 0x4($t1)
    ctx->r14 = MEM_W(ctx->r9, 0X4);
    // 0x801E41F8: lw          $t8, 0x0($t1)
    ctx->r24 = MEM_W(ctx->r9, 0X0);
    // 0x801E41FC: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x801E4200: multu       $t6, $t4
    result = U64(U32(ctx->r14)) * U64(U32(ctx->r12)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x801E4204: or          $v1, $a0, $zero
    ctx->r3 = ctx->r4 | 0;
    // 0x801E4208: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x801E420C: or          $a1, $a0, $zero
    ctx->r5 = ctx->r4 | 0;
    // 0x801E4210: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x801E4214: or          $a2, $a0, $zero
    ctx->r6 = ctx->r4 | 0;
    // 0x801E4218: addiu       $a3, $t4, -0x1
    ctx->r7 = ADD32(ctx->r12, -0X1);
    // 0x801E421C: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x801E4220: mflo        $t7
    ctx->r15 = lo;
    // 0x801E4224: nop

    // 0x801E4228: nop

    // 0x801E422C: multu       $t7, $t5
    result = U64(U32(ctx->r15)) * U64(U32(ctx->r13)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x801E4230: mflo        $t9
    ctx->r25 = lo;
    // 0x801E4234: addu        $t6, $t8, $t9
    ctx->r14 = ADD32(ctx->r24, ctx->r25);
    // 0x801E4238: sw          $t6, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r14;
    // 0x801E423C: lw          $t7, 0x4($t1)
    ctx->r15 = MEM_W(ctx->r9, 0X4);
    // 0x801E4240: sw          $s5, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r21;
    // 0x801E4244: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x801E4248: addiu       $t8, $t7, 0x7
    ctx->r24 = ADD32(ctx->r15, 0X7);
    // 0x801E424C: srl         $t9, $t8, 3
    ctx->r25 = S32(U32(ctx->r24) >> 3);
    // 0x801E4250: andi        $t6, $t9, 0x1FF
    ctx->r14 = ctx->r25 & 0X1FF;
    // 0x801E4254: sll         $t7, $t6, 9
    ctx->r15 = S32(ctx->r14 << 9);
    // 0x801E4258: or          $t8, $t7, $s2
    ctx->r24 = ctx->r15 | ctx->r18;
    // 0x801E425C: sw          $t8, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r24;
    // 0x801E4260: sw          $zero, 0x4($a1)
    MEM_W(0X4, ctx->r5) = 0;
    // 0x801E4264: sw          $s6, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r22;
    // 0x801E4268: lui         $t7, 0xF400
    ctx->r15 = S32(0XF400 << 16);
    // 0x801E426C: sw          $t7, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r15;
    // 0x801E4270: lw          $t8, 0x4($t1)
    ctx->r24 = MEM_W(ctx->r9, 0X4);
    // 0x801E4274: sll         $t9, $a3, 2
    ctx->r25 = S32(ctx->r7 << 2);
    // 0x801E4278: andi        $a3, $t9, 0xFFF
    ctx->r7 = ctx->r25 & 0XFFF;
    // 0x801E427C: addiu       $t9, $t8, -0x1
    ctx->r25 = ADD32(ctx->r24, -0X1);
    // 0x801E4280: sll         $t6, $t9, 2
    ctx->r14 = S32(ctx->r25 << 2);
    // 0x801E4284: andi        $t7, $t6, 0xFFF
    ctx->r15 = ctx->r14 & 0XFFF;
    // 0x801E4288: sll         $t8, $t7, 12
    ctx->r24 = S32(ctx->r15 << 12);
    // 0x801E428C: or          $t9, $t8, $s7
    ctx->r25 = ctx->r24 | ctx->r23;
    // 0x801E4290: or          $t6, $t9, $a3
    ctx->r14 = ctx->r25 | ctx->r7;
    // 0x801E4294: sw          $t6, 0x4($a2)
    MEM_W(0X4, ctx->r6) = ctx->r14;
    // 0x801E4298: sw          $zero, 0x4($v0)
    MEM_W(0X4, ctx->r2) = 0;
    // 0x801E429C: sw          $fp, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r30;
    // 0x801E42A0: lw          $t7, 0x4($t1)
    ctx->r15 = MEM_W(ctx->r9, 0X4);
    // 0x801E42A4: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x801E42A8: or          $v1, $a0, $zero
    ctx->r3 = ctx->r4 | 0;
    // 0x801E42AC: addiu       $t8, $t7, 0x7
    ctx->r24 = ADD32(ctx->r15, 0X7);
    // 0x801E42B0: srl         $t9, $t8, 3
    ctx->r25 = S32(U32(ctx->r24) >> 3);
    // 0x801E42B4: andi        $t6, $t9, 0x1FF
    ctx->r14 = ctx->r25 & 0X1FF;
    // 0x801E42B8: sll         $t7, $t6, 9
    ctx->r15 = S32(ctx->r14 << 9);
    // 0x801E42BC: or          $t8, $t7, $s2
    ctx->r24 = ctx->r15 | ctx->r18;
    // 0x801E42C0: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x801E42C4: or          $a1, $a0, $zero
    ctx->r5 = ctx->r4 | 0;
    // 0x801E42C8: sw          $t8, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r24;
    // 0x801E42CC: lui         $t9, 0xF200
    ctx->r25 = S32(0XF200 << 16);
    // 0x801E42D0: sw          $ra, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r31;
    // 0x801E42D4: sw          $t9, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r25;
    // 0x801E42D8: lw          $t6, 0x4($t1)
    ctx->r14 = MEM_W(ctx->r9, 0X4);
    // 0x801E42DC: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x801E42E0: addiu       $t7, $t6, -0x1
    ctx->r15 = ADD32(ctx->r14, -0X1);
    // 0x801E42E4: sll         $t8, $t7, 2
    ctx->r24 = S32(ctx->r15 << 2);
    // 0x801E42E8: andi        $t9, $t8, 0xFFF
    ctx->r25 = ctx->r24 & 0XFFF;
    // 0x801E42EC: sll         $t6, $t9, 12
    ctx->r14 = S32(ctx->r25 << 12);
    // 0x801E42F0: or          $t7, $t6, $a3
    ctx->r15 = ctx->r14 | ctx->r7;
    // 0x801E42F4: sw          $t7, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r15;
L_801E42F8:
    // 0x801E42F8: lw          $t8, 0x4($t1)
    ctx->r24 = MEM_W(ctx->r9, 0X4);
    // 0x801E42FC: lw          $t9, 0x54($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X54);
    // 0x801E4300: or          $t0, $a0, $zero
    ctx->r8 = ctx->r4 | 0;
    // 0x801E4304: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x801E4308: addu        $v0, $t8, $t9
    ctx->r2 = ADD32(ctx->r24, ctx->r25);
    // 0x801E430C: sll         $t6, $v0, 2
    ctx->r14 = S32(ctx->r2 << 2);
    // 0x801E4310: blez        $t6, L_801E4320
    if (SIGNED(ctx->r14) <= 0) {
        // 0x801E4314: sll         $v1, $s1, 2
        ctx->r3 = S32(ctx->r17 << 2);
            goto L_801E4320;
    }
    // 0x801E4314: sll         $v1, $s1, 2
    ctx->r3 = S32(ctx->r17 << 2);
    // 0x801E4318: b           L_801E4324
    // 0x801E431C: or          $a3, $t6, $zero
    ctx->r7 = ctx->r14 | 0;
        goto L_801E4324;
    // 0x801E431C: or          $a3, $t6, $zero
    ctx->r7 = ctx->r14 | 0;
L_801E4320:
    // 0x801E4320: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
L_801E4324:
    // 0x801E4324: blez        $v1, L_801E4334
    if (SIGNED(ctx->r3) <= 0) {
        // 0x801E4328: lui         $at, 0xE400
        ctx->r1 = S32(0XE400 << 16);
            goto L_801E4334;
    }
    // 0x801E4328: lui         $at, 0xE400
    ctx->r1 = S32(0XE400 << 16);
    // 0x801E432C: b           L_801E4338
    // 0x801E4330: or          $v0, $v1, $zero
    ctx->r2 = ctx->r3 | 0;
        goto L_801E4338;
    // 0x801E4330: or          $v0, $v1, $zero
    ctx->r2 = ctx->r3 | 0;
L_801E4334:
    // 0x801E4334: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_801E4338:
    // 0x801E4338: andi        $t7, $v0, 0xFFF
    ctx->r15 = ctx->r2 & 0XFFF;
    // 0x801E433C: andi        $t9, $a3, 0xFFF
    ctx->r25 = ctx->r7 & 0XFFF;
    // 0x801E4340: sll         $t6, $t9, 12
    ctx->r14 = S32(ctx->r25 << 12);
    // 0x801E4344: or          $t8, $t7, $at
    ctx->r24 = ctx->r15 | ctx->r1;
    // 0x801E4348: or          $t7, $t8, $t6
    ctx->r15 = ctx->r24 | ctx->r14;
    // 0x801E434C: blez        $s3, L_801E435C
    if (SIGNED(ctx->r19) <= 0) {
        // 0x801E4350: sw          $t7, 0x0($t0)
        MEM_W(0X0, ctx->r8) = ctx->r15;
            goto L_801E435C;
    }
    // 0x801E4350: sw          $t7, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r15;
    // 0x801E4354: b           L_801E4360
    // 0x801E4358: or          $a3, $s3, $zero
    ctx->r7 = ctx->r19 | 0;
        goto L_801E4360;
    // 0x801E4358: or          $a3, $s3, $zero
    ctx->r7 = ctx->r19 | 0;
L_801E435C:
    // 0x801E435C: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
L_801E4360:
    // 0x801E4360: sll         $a1, $s0, 2
    ctx->r5 = S32(ctx->r16 << 2);
    // 0x801E4364: blez        $a1, L_801E4374
    if (SIGNED(ctx->r5) <= 0) {
        // 0x801E4368: andi        $t8, $a3, 0xFFF
        ctx->r24 = ctx->r7 & 0XFFF;
            goto L_801E4374;
    }
    // 0x801E4368: andi        $t8, $a3, 0xFFF
    ctx->r24 = ctx->r7 & 0XFFF;
    // 0x801E436C: b           L_801E4378
    // 0x801E4370: or          $v0, $a1, $zero
    ctx->r2 = ctx->r5 | 0;
        goto L_801E4378;
    // 0x801E4370: or          $v0, $a1, $zero
    ctx->r2 = ctx->r5 | 0;
L_801E4374:
    // 0x801E4374: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_801E4378:
    // 0x801E4378: andi        $t9, $v0, 0xFFF
    ctx->r25 = ctx->r2 & 0XFFF;
    // 0x801E437C: sll         $t6, $t8, 12
    ctx->r14 = S32(ctx->r24 << 12);
    // 0x801E4380: or          $t7, $t9, $t6
    ctx->r15 = ctx->r25 | ctx->r14;
    // 0x801E4384: sw          $t7, 0x4($t0)
    MEM_W(0X4, ctx->r8) = ctx->r15;
    // 0x801E4388: lui         $t8, 0xB300
    ctx->r24 = S32(0XB300 << 16);
    // 0x801E438C: or          $a2, $a0, $zero
    ctx->r6 = ctx->r4 | 0;
    // 0x801E4390: sw          $t8, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r24;
    // 0x801E4394: bgez        $s4, L_801E43A4
    if (SIGNED(ctx->r20) >= 0) {
        // 0x801E4398: addiu       $a0, $a0, 0x8
        ctx->r4 = ADD32(ctx->r4, 0X8);
            goto L_801E43A4;
    }
    // 0x801E4398: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x801E439C: b           L_801E43A8
    // 0x801E43A0: or          $a3, $s4, $zero
    ctx->r7 = ctx->r20 | 0;
        goto L_801E43A8;
    // 0x801E43A0: or          $a3, $s4, $zero
    ctx->r7 = ctx->r20 | 0;
L_801E43A4:
    // 0x801E43A4: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
L_801E43A8:
    // 0x801E43A8: sll         $v1, $a1, 10
    ctx->r3 = S32(ctx->r5 << 10);
    // 0x801E43AC: sra         $t9, $v1, 7
    ctx->r25 = S32(SIGNED(ctx->r3) >> 7);
    // 0x801E43B0: bgez        $t9, L_801E43C0
    if (SIGNED(ctx->r25) >= 0) {
        // 0x801E43B4: or          $v1, $a0, $zero
        ctx->r3 = ctx->r4 | 0;
            goto L_801E43C0;
    }
    // 0x801E43B4: or          $v1, $a0, $zero
    ctx->r3 = ctx->r4 | 0;
    // 0x801E43B8: b           L_801E43C4
    // 0x801E43BC: or          $v0, $t9, $zero
    ctx->r2 = ctx->r25 | 0;
        goto L_801E43C4;
    // 0x801E43BC: or          $v0, $t9, $zero
    ctx->r2 = ctx->r25 | 0;
L_801E43C0:
    // 0x801E43C0: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_801E43C4:
    // 0x801E43C4: negu        $t6, $v0
    ctx->r14 = SUB32(0, ctx->r2);
    // 0x801E43C8: andi        $t7, $t6, 0xFFFF
    ctx->r15 = ctx->r14 & 0XFFFF;
    // 0x801E43CC: negu        $t9, $a3
    ctx->r25 = SUB32(0, ctx->r7);
    // 0x801E43D0: sll         $t6, $t9, 16
    ctx->r14 = S32(ctx->r25 << 16);
    // 0x801E43D4: or          $t8, $t7, $t6
    ctx->r24 = ctx->r15 | ctx->r14;
    // 0x801E43D8: sw          $t8, 0x4($a2)
    MEM_W(0X4, ctx->r6) = ctx->r24;
    // 0x801E43DC: lui         $t7, 0x400
    ctx->r15 = S32(0X400 << 16);
    // 0x801E43E0: ori         $t7, $t7, 0x400
    ctx->r15 = ctx->r15 | 0X400;
    // 0x801E43E4: lui         $t9, 0xB200
    ctx->r25 = S32(0XB200 << 16);
    // 0x801E43E8: sw          $t9, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r25;
    // 0x801E43EC: sw          $t7, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r15;
    // 0x801E43F0: lw          $t6, 0x38($sp)
    if (wr64MessageHalf > 0) wr64_menu_promote_waku_rect(rdram, (uint32_t)ctx->r8,
        wr64MessageX, MEM_W(4, MEM_W(0x34, ctx->r29)));
    ctx->r14 = MEM_W(ctx->r29, 0X38);
    // 0x801E43F4: addiu       $t5, $t5, 0x1
    ctx->r13 = ADD32(ctx->r13, 0X1);
    // 0x801E43F8: addu        $s0, $s0, $t4
    ctx->r16 = ADD32(ctx->r16, ctx->r12);
    // 0x801E43FC: addu        $s1, $s1, $t4
    ctx->r17 = ADD32(ctx->r17, ctx->r12);
    // 0x801E4400: bne         $t5, $t6, L_801E4088
    if (ctx->r13 != ctx->r14) {
        // 0x801E4404: addiu       $a0, $a0, 0x8
        ctx->r4 = ADD32(ctx->r4, 0X8);
            goto L_801E4088;
    }
    // 0x801E4404: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
L_801E4408:
    // 0x801E4408: lw          $ra, 0x2C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X2C);
    // 0x801E440C: lw          $s0, 0x8($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X8);
    // 0x801E4410: lw          $s1, 0xC($sp)
    ctx->r17 = MEM_W(ctx->r29, 0XC);
    // 0x801E4414: lw          $s2, 0x10($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X10);
    // 0x801E4418: lw          $s3, 0x14($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X14);
    // 0x801E441C: lw          $s4, 0x18($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X18);
    // 0x801E4420: lw          $s5, 0x1C($sp)
    ctx->r21 = MEM_W(ctx->r29, 0X1C);
    // 0x801E4424: lw          $s6, 0x20($sp)
    ctx->r22 = MEM_W(ctx->r29, 0X20);
    // 0x801E4428: lw          $s7, 0x24($sp)
    ctx->r23 = MEM_W(ctx->r29, 0X24);
    // 0x801E442C: lw          $fp, 0x28($sp)
    ctx->r30 = MEM_W(ctx->r29, 0X28);
    // 0x801E4430: addiu       $sp, $sp, 0x48
    ctx->r29 = ADD32(ctx->r29, 0X48);
    // 0x801E4434: jr          $ra
    // 0x801E4438: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    return;
    // 0x801E4438: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x801E443C: nop

;}
RECOMP_FUNC void func_801E4440(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801E4440: lui         $t0, 0x801D
    ctx->r8 = S32(0X801D << 16);
    // 0x801E4444: addiu       $t0, $t0, -0x19DC
    ctx->r8 = ADD32(ctx->r8, -0X19DC);
    // 0x801E4448: lh          $a1, 0x0($t0)
    ctx->r5 = MEM_H(ctx->r8, 0X0);
    // 0x801E444C: addiu       $sp, $sp, -0x70
    ctx->r29 = ADD32(ctx->r29, -0X70);
    // 0x801E4450: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x801E4454: sw          $ra, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r31;
    // 0x801E4458: sw          $a0, 0x70($sp)
    MEM_W(0X70, ctx->r29) = ctx->r4;
    // 0x801E445C: bne         $a1, $at, L_801E4644
    if (ctx->r5 != ctx->r1) {
        // 0x801E4460: sw          $zero, 0x60($sp)
        MEM_W(0X60, ctx->r29) = 0;
            goto L_801E4644;
    }
    // 0x801E4460: sw          $zero, 0x60($sp)
    MEM_W(0X60, ctx->r29) = 0;
    // 0x801E4464: lui         $a2, 0x801D
    ctx->r6 = S32(0X801D << 16);
    // 0x801E4468: addiu       $a2, $a2, -0x19D8
    ctx->r6 = ADD32(ctx->r6, -0X19D8);
    // 0x801E446C: lh          $t6, 0x0($a2)
    ctx->r14 = MEM_H(ctx->r6, 0X0);
    // 0x801E4470: lui         $t7, 0x801D
    ctx->r15 = S32(0X801D << 16);
    // 0x801E4474: lui         $t8, 0x800E
    ctx->r24 = S32(0X800E << 16);
    // 0x801E4478: beq         $t6, $zero, L_801E4484
    if (ctx->r14 == 0) {
        // 0x801E447C: nop
    
            goto L_801E4484;
    }
    // 0x801E447C: nop

    // 0x801E4480: sh          $zero, 0x0($a2)
    MEM_H(0X0, ctx->r6) = 0;
L_801E4484:
    // 0x801E4484: lh          $t7, -0x19D6($t7)
    ctx->r15 = MEM_H(ctx->r15, -0X19D6);
    // 0x801E4488: beq         $t7, $zero, L_801E4630
    if (ctx->r15 == 0) {
        // 0x801E448C: nop
    
            goto L_801E4630;
    }
    // 0x801E448C: nop

    // 0x801E4490: lw          $t8, -0x54D8($t8)
    ctx->r24 = MEM_W(ctx->r24, -0X54D8);
    // 0x801E4494: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    // 0x801E4498: sw          $zero, 0x68($sp)
    MEM_W(0X68, ctx->r29) = 0;
    // 0x801E449C: bne         $a2, $t8, L_801E44EC
    if (ctx->r6 != ctx->r24) {
        // 0x801E44A0: lui         $a0, 0x801D
        ctx->r4 = S32(0X801D << 16);
            goto L_801E44EC;
    }
    // 0x801E44A0: lui         $a0, 0x801D
    ctx->r4 = S32(0X801D << 16);
    // 0x801E44A4: lui         $a0, 0x801D
    ctx->r4 = S32(0X801D << 16);
    // 0x801E44A8: addiu       $a0, $a0, -0x19A8
    ctx->r4 = ADD32(ctx->r4, -0X19A8);
    // 0x801E44AC: lhu         $t9, 0x2($a0)
    ctx->r25 = MEM_HU(ctx->r4, 0X2);
    // 0x801E44B0: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801E44B4: addiu       $a0, $zero, 0x3
    ctx->r4 = ADD32(0, 0X3);
    // 0x801E44B8: andi        $t3, $t9, 0x1000
    ctx->r11 = ctx->r25 & 0X1000;
    // 0x801E44BC: beq         $t3, $zero, L_801E4574
    if (ctx->r11 == 0) {
        // 0x801E44C0: addiu       $a1, $zero, 0x2
        ctx->r5 = ADD32(0, 0X2);
            goto L_801E4574;
    }
    // 0x801E44C0: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x801E44C4: sw          $a2, 0x68($sp)
    MEM_W(0X68, ctx->r29) = ctx->r6;
    // 0x801E44C8: jal         0x801E6A4C
    // 0x801E44CC: sh          $a2, -0x19D4($at)
    MEM_H(-0X19D4, ctx->r1) = ctx->r6;
    func_801E6A4C(rdram, ctx);
        goto after_0;
    // 0x801E44CC: sh          $a2, -0x19D4($at)
    MEM_H(-0X19D4, ctx->r1) = ctx->r6;
    after_0:
    // 0x801E44D0: addiu       $a0, $zero, 0x3
    ctx->r4 = ADD32(0, 0X3);
    // 0x801E44D4: jal         0x801E6A4C
    // 0x801E44D8: addiu       $a1, $zero, 0x3
    ctx->r5 = ADD32(0, 0X3);
    func_801E6A4C(rdram, ctx);
        goto after_1;
    // 0x801E44D8: addiu       $a1, $zero, 0x3
    ctx->r5 = ADD32(0, 0X3);
    after_1:
    // 0x801E44DC: lui         $t0, 0x801D
    ctx->r8 = S32(0X801D << 16);
    // 0x801E44E0: addiu       $t0, $t0, -0x19DC
    ctx->r8 = ADD32(ctx->r8, -0X19DC);
    // 0x801E44E4: b           L_801E4574
    // 0x801E44E8: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
        goto L_801E4574;
    // 0x801E44E8: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
L_801E44EC:
    // 0x801E44EC: addiu       $a0, $a0, -0x19A8
    ctx->r4 = ADD32(ctx->r4, -0X19A8);
    // 0x801E44F0: lhu         $t4, 0x2($a0)
    ctx->r12 = MEM_HU(ctx->r4, 0X2);
    // 0x801E44F4: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801E44F8: addiu       $a1, $zero, 0x4
    ctx->r5 = ADD32(0, 0X4);
    // 0x801E44FC: andi        $t5, $t4, 0x1000
    ctx->r13 = ctx->r12 & 0X1000;
    // 0x801E4500: beql        $t5, $zero, L_801E4538
    if (ctx->r13 == 0) {
        // 0x801E4504: lhu         $t6, 0x1E($a0)
        ctx->r14 = MEM_HU(ctx->r4, 0X1E);
            goto L_801E4538;
    }
    goto skip_0;
    // 0x801E4504: lhu         $t6, 0x1E($a0)
    ctx->r14 = MEM_HU(ctx->r4, 0X1E);
    skip_0:
    // 0x801E4508: sw          $a2, 0x68($sp)
    MEM_W(0X68, ctx->r29) = ctx->r6;
    // 0x801E450C: sh          $a2, -0x19D4($at)
    MEM_H(-0X19D4, ctx->r1) = ctx->r6;
    // 0x801E4510: jal         0x801E6A4C
    // 0x801E4514: addiu       $a0, $zero, 0x3
    ctx->r4 = ADD32(0, 0X3);
    func_801E6A4C(rdram, ctx);
        goto after_2;
    // 0x801E4514: addiu       $a0, $zero, 0x3
    ctx->r4 = ADD32(0, 0X3);
    after_2:
    // 0x801E4518: addiu       $a0, $zero, 0x3
    ctx->r4 = ADD32(0, 0X3);
    // 0x801E451C: jal         0x801E6A4C
    // 0x801E4520: addiu       $a1, $zero, 0x5
    ctx->r5 = ADD32(0, 0X5);
    func_801E6A4C(rdram, ctx);
        goto after_3;
    // 0x801E4520: addiu       $a1, $zero, 0x5
    ctx->r5 = ADD32(0, 0X5);
    after_3:
    // 0x801E4524: lui         $t0, 0x801D
    ctx->r8 = S32(0X801D << 16);
    // 0x801E4528: addiu       $t0, $t0, -0x19DC
    ctx->r8 = ADD32(ctx->r8, -0X19DC);
    // 0x801E452C: b           L_801E4574
    // 0x801E4530: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
        goto L_801E4574;
    // 0x801E4530: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    // 0x801E4534: lhu         $t6, 0x1E($a0)
    ctx->r14 = MEM_HU(ctx->r4, 0X1E);
L_801E4538:
    // 0x801E4538: addiu       $t8, $zero, 0x2
    ctx->r24 = ADD32(0, 0X2);
    // 0x801E453C: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801E4540: andi        $t7, $t6, 0x1000
    ctx->r15 = ctx->r14 & 0X1000;
    // 0x801E4544: beq         $t7, $zero, L_801E4574
    if (ctx->r15 == 0) {
        // 0x801E4548: addiu       $a0, $zero, 0x3
        ctx->r4 = ADD32(0, 0X3);
            goto L_801E4574;
    }
    // 0x801E4548: addiu       $a0, $zero, 0x3
    ctx->r4 = ADD32(0, 0X3);
    // 0x801E454C: sw          $a2, 0x68($sp)
    MEM_W(0X68, ctx->r29) = ctx->r6;
    // 0x801E4550: sh          $t8, -0x19D4($at)
    MEM_H(-0X19D4, ctx->r1) = ctx->r24;
    // 0x801E4554: jal         0x801E6A4C
    // 0x801E4558: addiu       $a1, $zero, 0x6
    ctx->r5 = ADD32(0, 0X6);
    func_801E6A4C(rdram, ctx);
        goto after_4;
    // 0x801E4558: addiu       $a1, $zero, 0x6
    ctx->r5 = ADD32(0, 0X6);
    after_4:
    // 0x801E455C: addiu       $a0, $zero, 0x3
    ctx->r4 = ADD32(0, 0X3);
    // 0x801E4560: jal         0x801E6A4C
    // 0x801E4564: addiu       $a1, $zero, 0x7
    ctx->r5 = ADD32(0, 0X7);
    func_801E6A4C(rdram, ctx);
        goto after_5;
    // 0x801E4564: addiu       $a1, $zero, 0x7
    ctx->r5 = ADD32(0, 0X7);
    after_5:
    // 0x801E4568: lui         $t0, 0x801D
    ctx->r8 = S32(0X801D << 16);
    // 0x801E456C: addiu       $t0, $t0, -0x19DC
    ctx->r8 = ADD32(ctx->r8, -0X19DC);
    // 0x801E4570: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
L_801E4574:
    // 0x801E4574: lw          $t9, 0x68($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X68);
    // 0x801E4578: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x801E457C: addiu       $v1, $v1, -0x19B8
    ctx->r3 = ADD32(ctx->r3, -0X19B8);
    // 0x801E4580: beq         $t9, $zero, L_801E4630
    if (ctx->r25 == 0) {
        // 0x801E4584: lui         $v0, 0x801D
        ctx->r2 = S32(0X801D << 16);
            goto L_801E4630;
    }
    // 0x801E4584: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x801E4588: sh          $zero, 0x0($t0)
    MEM_H(0X0, ctx->r8) = 0;
    // 0x801E458C: lw          $v0, -0x19F8($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X19F8);
    // 0x801E4590: addiu       $a0, $zero, 0x4
    ctx->r4 = ADD32(0, 0X4);
    // 0x801E4594: lui         $t3, 0x800E
    ctx->r11 = S32(0X800E << 16);
    // 0x801E4598: bne         $a0, $v0, L_801E45B0
    if (ctx->r4 != ctx->r2) {
        // 0x801E459C: addiu       $t5, $zero, 0x5
        ctx->r13 = ADD32(0, 0X5);
            goto L_801E45B0;
    }
    // 0x801E459C: addiu       $t5, $zero, 0x5
    ctx->r13 = ADD32(0, 0X5);
    // 0x801E45A0: lw          $t3, -0x7E90($t3)
    ctx->r11 = MEM_W(ctx->r11, -0X7E90);
    // 0x801E45A4: bnel        $t3, $zero, L_801E45B4
    if (ctx->r11 != 0) {
        // 0x801E45A8: lw          $t4, 0x0($v1)
        ctx->r12 = MEM_W(ctx->r3, 0X0);
            goto L_801E45B4;
    }
    goto skip_1;
    // 0x801E45A8: lw          $t4, 0x0($v1)
    ctx->r12 = MEM_W(ctx->r3, 0X0);
    skip_1:
    // 0x801E45AC: sh          $a2, 0x0($t0)
    MEM_H(0X0, ctx->r8) = ctx->r6;
L_801E45B0:
    // 0x801E45B0: lw          $t4, 0x0($v1)
    ctx->r12 = MEM_W(ctx->r3, 0X0);
L_801E45B4:
    // 0x801E45B4: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801E45B8: sw          $t4, -0x76F0($at)
    MEM_W(-0X76F0, ctx->r1) = ctx->r12;
    // 0x801E45BC: beq         $v0, $zero, L_801E45CC
    if (ctx->r2 == 0) {
        // 0x801E45C0: sw          $zero, 0x0($v1)
        MEM_W(0X0, ctx->r3) = 0;
            goto L_801E45CC;
    }
    // 0x801E45C0: sw          $zero, 0x0($v1)
    MEM_W(0X0, ctx->r3) = 0;
    // 0x801E45C4: addiu       $at, $zero, 0xB
    ctx->r1 = ADD32(0, 0XB);
    // 0x801E45C8: bne         $v0, $at, L_801E45D8
    if (ctx->r2 != ctx->r1) {
        // 0x801E45CC: lui         $at, 0x801D
        ctx->r1 = S32(0X801D << 16);
            goto L_801E45D8;
    }
L_801E45CC:
    // 0x801E45CC: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801E45D0: b           L_801E4614
    // 0x801E45D4: sh          $t5, -0x19DA($at)
    MEM_H(-0X19DA, ctx->r1) = ctx->r13;
        goto L_801E4614;
    // 0x801E45D4: sh          $t5, -0x19DA($at)
    MEM_H(-0X19DA, ctx->r1) = ctx->r13;
L_801E45D8:
    // 0x801E45D8: bne         $a0, $v0, L_801E460C
    if (ctx->r4 != ctx->r2) {
        // 0x801E45DC: addiu       $t8, $zero, 0x2
        ctx->r24 = ADD32(0, 0X2);
            goto L_801E460C;
    }
    // 0x801E45DC: addiu       $t8, $zero, 0x2
    ctx->r24 = ADD32(0, 0X2);
    // 0x801E45E0: lui         $t6, 0x800E
    ctx->r14 = S32(0X800E << 16);
    // 0x801E45E4: lw          $t6, -0x7E90($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X7E90);
    // 0x801E45E8: addiu       $t7, $zero, 0x3
    ctx->r15 = ADD32(0, 0X3);
    // 0x801E45EC: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801E45F0: bne         $t6, $zero, L_801E4604
    if (ctx->r14 != 0) {
        // 0x801E45F4: nop
    
            goto L_801E4604;
    }
    // 0x801E45F4: nop

    // 0x801E45F8: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801E45FC: b           L_801E4614
    // 0x801E4600: sh          $t7, -0x19DA($at)
    MEM_H(-0X19DA, ctx->r1) = ctx->r15;
        goto L_801E4614;
    // 0x801E4600: sh          $t7, -0x19DA($at)
    MEM_H(-0X19DA, ctx->r1) = ctx->r15;
L_801E4604:
    // 0x801E4604: b           L_801E4614
    // 0x801E4608: sh          $a0, -0x19DA($at)
    MEM_H(-0X19DA, ctx->r1) = ctx->r4;
        goto L_801E4614;
    // 0x801E4608: sh          $a0, -0x19DA($at)
    MEM_H(-0X19DA, ctx->r1) = ctx->r4;
L_801E460C:
    // 0x801E460C: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801E4610: sh          $t8, -0x19DA($at)
    MEM_H(-0X19DA, ctx->r1) = ctx->r24;
L_801E4614:
    // 0x801E4614: jal         0x800C3DE0
    // 0x801E4618: nop

    func_800C3DE0(rdram, ctx);
        goto after_6;
    // 0x801E4618: nop

    after_6:
    // 0x801E461C: addiu       $a0, $zero, 0x20
    ctx->r4 = ADD32(0, 0X20);
    // 0x801E4620: jal         0x800C37F4
    // 0x801E4624: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_7;
    // 0x801E4624: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_7:
    // 0x801E4628: lui         $t0, 0x801D
    ctx->r8 = S32(0X801D << 16);
    // 0x801E462C: addiu       $t0, $t0, -0x19DC
    ctx->r8 = ADD32(ctx->r8, -0X19DC);
L_801E4630:
    // 0x801E4630: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x801E4634: lw          $v0, -0x54D8($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X54D8);
    // 0x801E4638: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    // 0x801E463C: b           L_801E49D4
    // 0x801E4640: lh          $a1, 0x0($t0)
    ctx->r5 = MEM_H(ctx->r8, 0X0);
        goto L_801E49D4;
    // 0x801E4640: lh          $a1, 0x0($t0)
    ctx->r5 = MEM_H(ctx->r8, 0X0);
L_801E4644:
    // 0x801E4644: lui         $a2, 0x801D
    ctx->r6 = S32(0X801D << 16);
    // 0x801E4648: addiu       $a2, $a2, -0x19D8
    ctx->r6 = ADD32(ctx->r6, -0X19D8);
    // 0x801E464C: lh          $t9, 0x0($a2)
    ctx->r25 = MEM_H(ctx->r6, 0X0);
    // 0x801E4650: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
    // 0x801E4654: lui         $t3, 0x800E
    ctx->r11 = S32(0X800E << 16);
    // 0x801E4658: bne         $t9, $zero, L_801E4738
    if (ctx->r25 != 0) {
        // 0x801E465C: addiu       $at, $zero, 0x2
        ctx->r1 = ADD32(0, 0X2);
            goto L_801E4738;
    }
    // 0x801E465C: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x801E4660: lw          $t3, -0x54D8($t3)
    ctx->r11 = MEM_W(ctx->r11, -0X54D8);
    // 0x801E4664: addiu       $a3, $zero, 0x1
    ctx->r7 = ADD32(0, 0X1);
    // 0x801E4668: lui         $a0, 0x801D
    ctx->r4 = S32(0X801D << 16);
    // 0x801E466C: bne         $a3, $t3, L_801E46B0
    if (ctx->r7 != ctx->r11) {
        // 0x801E4670: lui         $t7, 0x801D
        ctx->r15 = S32(0X801D << 16);
            goto L_801E46B0;
    }
    // 0x801E4670: lui         $t7, 0x801D
    ctx->r15 = S32(0X801D << 16);
    // 0x801E4674: addiu       $a0, $a0, -0x19A8
    ctx->r4 = ADD32(ctx->r4, -0X19A8);
    // 0x801E4678: lhu         $v0, 0x2($a0)
    ctx->r2 = MEM_HU(ctx->r4, 0X2);
    // 0x801E467C: andi        $t4, $v0, 0xB000
    ctx->r12 = ctx->r2 & 0XB000;
    // 0x801E4680: beq         $t4, $zero, L_801E4690
    if (ctx->r12 == 0) {
        // 0x801E4684: andi        $t5, $v0, 0x800
        ctx->r13 = ctx->r2 & 0X800;
            goto L_801E4690;
    }
    // 0x801E4684: andi        $t5, $v0, 0x800
    ctx->r13 = ctx->r2 & 0X800;
    // 0x801E4688: b           L_801E4738
    // 0x801E468C: or          $v1, $a3, $zero
    ctx->r3 = ctx->r7 | 0;
        goto L_801E4738;
    // 0x801E468C: or          $v1, $a3, $zero
    ctx->r3 = ctx->r7 | 0;
L_801E4690:
    // 0x801E4690: beq         $t5, $zero, L_801E46A0
    if (ctx->r13 == 0) {
        // 0x801E4694: andi        $t6, $v0, 0x400
        ctx->r14 = ctx->r2 & 0X400;
            goto L_801E46A0;
    }
    // 0x801E4694: andi        $t6, $v0, 0x400
    ctx->r14 = ctx->r2 & 0X400;
    // 0x801E4698: b           L_801E4738
    // 0x801E469C: addiu       $v1, $zero, 0x2
    ctx->r3 = ADD32(0, 0X2);
        goto L_801E4738;
    // 0x801E469C: addiu       $v1, $zero, 0x2
    ctx->r3 = ADD32(0, 0X2);
L_801E46A0:
    // 0x801E46A0: beql        $t6, $zero, L_801E473C
    if (ctx->r14 == 0) {
        // 0x801E46A4: addiu       $a3, $zero, 0x1
        ctx->r7 = ADD32(0, 0X1);
            goto L_801E473C;
    }
    goto skip_2;
    // 0x801E46A4: addiu       $a3, $zero, 0x1
    ctx->r7 = ADD32(0, 0X1);
    skip_2:
    // 0x801E46A8: b           L_801E4738
    // 0x801E46AC: addiu       $v1, $zero, 0x3
    ctx->r3 = ADD32(0, 0X3);
        goto L_801E4738;
    // 0x801E46AC: addiu       $v1, $zero, 0x3
    ctx->r3 = ADD32(0, 0X3);
L_801E46B0:
    // 0x801E46B0: lh          $t7, -0x19D4($t7)
    ctx->r15 = MEM_H(ctx->r15, -0X19D4);
    // 0x801E46B4: lui         $a0, 0x801D
    ctx->r4 = S32(0X801D << 16);
    // 0x801E46B8: addiu       $a0, $a0, -0x19A8
    ctx->r4 = ADD32(ctx->r4, -0X19A8);
    // 0x801E46BC: bnel        $a3, $t7, L_801E4708
    if (ctx->r7 != ctx->r15) {
        // 0x801E46C0: lhu         $v0, 0x1E($a0)
        ctx->r2 = MEM_HU(ctx->r4, 0X1E);
            goto L_801E4708;
    }
    goto skip_3;
    // 0x801E46C0: lhu         $v0, 0x1E($a0)
    ctx->r2 = MEM_HU(ctx->r4, 0X1E);
    skip_3:
    // 0x801E46C4: lui         $a0, 0x801D
    ctx->r4 = S32(0X801D << 16);
    // 0x801E46C8: addiu       $a0, $a0, -0x19A8
    ctx->r4 = ADD32(ctx->r4, -0X19A8);
    // 0x801E46CC: lhu         $v0, 0x2($a0)
    ctx->r2 = MEM_HU(ctx->r4, 0X2);
    // 0x801E46D0: andi        $t8, $v0, 0xB000
    ctx->r24 = ctx->r2 & 0XB000;
    // 0x801E46D4: beq         $t8, $zero, L_801E46E4
    if (ctx->r24 == 0) {
        // 0x801E46D8: andi        $t9, $v0, 0x800
        ctx->r25 = ctx->r2 & 0X800;
            goto L_801E46E4;
    }
    // 0x801E46D8: andi        $t9, $v0, 0x800
    ctx->r25 = ctx->r2 & 0X800;
    // 0x801E46DC: b           L_801E4738
    // 0x801E46E0: or          $v1, $a3, $zero
    ctx->r3 = ctx->r7 | 0;
        goto L_801E4738;
    // 0x801E46E0: or          $v1, $a3, $zero
    ctx->r3 = ctx->r7 | 0;
L_801E46E4:
    // 0x801E46E4: beq         $t9, $zero, L_801E46F4
    if (ctx->r25 == 0) {
        // 0x801E46E8: andi        $t3, $v0, 0x400
        ctx->r11 = ctx->r2 & 0X400;
            goto L_801E46F4;
    }
    // 0x801E46E8: andi        $t3, $v0, 0x400
    ctx->r11 = ctx->r2 & 0X400;
    // 0x801E46EC: b           L_801E4738
    // 0x801E46F0: addiu       $v1, $zero, 0x2
    ctx->r3 = ADD32(0, 0X2);
        goto L_801E4738;
    // 0x801E46F0: addiu       $v1, $zero, 0x2
    ctx->r3 = ADD32(0, 0X2);
L_801E46F4:
    // 0x801E46F4: beql        $t3, $zero, L_801E473C
    if (ctx->r11 == 0) {
        // 0x801E46F8: addiu       $a3, $zero, 0x1
        ctx->r7 = ADD32(0, 0X1);
            goto L_801E473C;
    }
    goto skip_4;
    // 0x801E46F8: addiu       $a3, $zero, 0x1
    ctx->r7 = ADD32(0, 0X1);
    skip_4:
    // 0x801E46FC: b           L_801E4738
    // 0x801E4700: addiu       $v1, $zero, 0x3
    ctx->r3 = ADD32(0, 0X3);
        goto L_801E4738;
    // 0x801E4700: addiu       $v1, $zero, 0x3
    ctx->r3 = ADD32(0, 0X3);
    // 0x801E4704: lhu         $v0, 0x1E($a0)
    ctx->r2 = MEM_HU(ctx->r4, 0X1E);
L_801E4708:
    // 0x801E4708: andi        $t4, $v0, 0xB000
    ctx->r12 = ctx->r2 & 0XB000;
    // 0x801E470C: beq         $t4, $zero, L_801E471C
    if (ctx->r12 == 0) {
        // 0x801E4710: andi        $t5, $v0, 0x800
        ctx->r13 = ctx->r2 & 0X800;
            goto L_801E471C;
    }
    // 0x801E4710: andi        $t5, $v0, 0x800
    ctx->r13 = ctx->r2 & 0X800;
    // 0x801E4714: b           L_801E4738
    // 0x801E4718: or          $v1, $a3, $zero
    ctx->r3 = ctx->r7 | 0;
        goto L_801E4738;
    // 0x801E4718: or          $v1, $a3, $zero
    ctx->r3 = ctx->r7 | 0;
L_801E471C:
    // 0x801E471C: beq         $t5, $zero, L_801E472C
    if (ctx->r13 == 0) {
        // 0x801E4720: andi        $t6, $v0, 0x400
        ctx->r14 = ctx->r2 & 0X400;
            goto L_801E472C;
    }
    // 0x801E4720: andi        $t6, $v0, 0x400
    ctx->r14 = ctx->r2 & 0X400;
    // 0x801E4724: b           L_801E4738
    // 0x801E4728: addiu       $v1, $zero, 0x2
    ctx->r3 = ADD32(0, 0X2);
        goto L_801E4738;
    // 0x801E4728: addiu       $v1, $zero, 0x2
    ctx->r3 = ADD32(0, 0X2);
L_801E472C:
    // 0x801E472C: beql        $t6, $zero, L_801E473C
    if (ctx->r14 == 0) {
        // 0x801E4730: addiu       $a3, $zero, 0x1
        ctx->r7 = ADD32(0, 0X1);
            goto L_801E473C;
    }
    goto skip_5;
    // 0x801E4730: addiu       $a3, $zero, 0x1
    ctx->r7 = ADD32(0, 0X1);
    skip_5:
    // 0x801E4734: addiu       $v1, $zero, 0x3
    ctx->r3 = ADD32(0, 0X3);
L_801E4738:
    // 0x801E4738: addiu       $a3, $zero, 0x1
    ctx->r7 = ADD32(0, 0X1);
L_801E473C:
    // 0x801E473C: beq         $v1, $a3, L_801E4768
    if (ctx->r3 == ctx->r7) {
        // 0x801E4740: lui         $v0, 0x801D
        ctx->r2 = S32(0X801D << 16);
            goto L_801E4768;
    }
    // 0x801E4740: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x801E4744: beq         $v1, $at, L_801E4954
    if (ctx->r3 == ctx->r1) {
        // 0x801E4748: addiu       $t9, $a1, -0x1
        ctx->r25 = ADD32(ctx->r5, -0X1);
            goto L_801E4954;
    }
    // 0x801E4748: addiu       $t9, $a1, -0x1
    ctx->r25 = ADD32(ctx->r5, -0X1);
    // 0x801E474C: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x801E4750: beq         $v1, $at, L_801E4998
    if (ctx->r3 == ctx->r1) {
        // 0x801E4754: addiu       $t6, $a1, 0x1
        ctx->r14 = ADD32(ctx->r5, 0X1);
            goto L_801E4998;
    }
    // 0x801E4754: addiu       $t6, $a1, 0x1
    ctx->r14 = ADD32(ctx->r5, 0X1);
    // 0x801E4758: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x801E475C: lw          $v0, -0x54D8($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X54D8);
    // 0x801E4760: b           L_801E49D4
    // 0x801E4764: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
        goto L_801E49D4;
    // 0x801E4764: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
L_801E4768:
    // 0x801E4768: lw          $v0, -0x19F8($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X19F8);
    // 0x801E476C: addiu       $at, $zero, 0xB
    ctx->r1 = ADD32(0, 0XB);
    // 0x801E4770: sll         $t7, $a1, 3
    ctx->r15 = S32(ctx->r5 << 3);
    // 0x801E4774: beq         $v0, $zero, L_801E4780
    if (ctx->r2 == 0) {
        // 0x801E4778: lui         $t8, 0x8022
        ctx->r24 = S32(0X8022 << 16);
            goto L_801E4780;
    }
    // 0x801E4778: lui         $t8, 0x8022
    ctx->r24 = S32(0X8022 << 16);
    // 0x801E477C: bne         $v0, $at, L_801E478C
    if (ctx->r2 != ctx->r1) {
        // 0x801E4780: addiu       $t8, $t8, 0x6BE8
        ctx->r24 = ADD32(ctx->r24, 0X6BE8);
            goto L_801E478C;
    }
L_801E4780:
    // 0x801E4780: addiu       $t8, $t8, 0x6BE8
    ctx->r24 = ADD32(ctx->r24, 0X6BE8);
    // 0x801E4784: b           L_801E47D8
    // 0x801E4788: addu        $v1, $t7, $t8
    ctx->r3 = ADD32(ctx->r15, ctx->r24);
        goto L_801E47D8;
    // 0x801E4788: addu        $v1, $t7, $t8
    ctx->r3 = ADD32(ctx->r15, ctx->r24);
L_801E478C:
    // 0x801E478C: addiu       $at, $zero, 0x4
    ctx->r1 = ADD32(0, 0X4);
    // 0x801E4790: bne         $v0, $at, L_801E47CC
    if (ctx->r2 != ctx->r1) {
        // 0x801E4794: sll         $t7, $a1, 3
        ctx->r15 = S32(ctx->r5 << 3);
            goto L_801E47CC;
    }
    // 0x801E4794: sll         $t7, $a1, 3
    ctx->r15 = S32(ctx->r5 << 3);
    // 0x801E4798: lui         $t9, 0x800E
    ctx->r25 = S32(0X800E << 16);
    // 0x801E479C: lw          $t9, -0x7E90($t9)
    ctx->r25 = MEM_W(ctx->r25, -0X7E90);
    // 0x801E47A0: lui         $t6, 0x8022
    ctx->r14 = S32(0X8022 << 16);
    // 0x801E47A4: addiu       $t6, $t6, 0x6BB0
    ctx->r14 = ADD32(ctx->r14, 0X6BB0);
    // 0x801E47A8: bne         $t9, $zero, L_801E47C4
    if (ctx->r25 != 0) {
        // 0x801E47AC: sll         $t5, $a1, 3
        ctx->r13 = S32(ctx->r5 << 3);
            goto L_801E47C4;
    }
    // 0x801E47AC: sll         $t5, $a1, 3
    ctx->r13 = S32(ctx->r5 << 3);
    // 0x801E47B0: lui         $t4, 0x8022
    ctx->r12 = S32(0X8022 << 16);
    // 0x801E47B4: addiu       $t4, $t4, 0x6BD0
    ctx->r12 = ADD32(ctx->r12, 0X6BD0);
    // 0x801E47B8: sll         $t3, $a1, 3
    ctx->r11 = S32(ctx->r5 << 3);
    // 0x801E47BC: b           L_801E47D8
    // 0x801E47C0: addu        $v1, $t3, $t4
    ctx->r3 = ADD32(ctx->r11, ctx->r12);
        goto L_801E47D8;
    // 0x801E47C0: addu        $v1, $t3, $t4
    ctx->r3 = ADD32(ctx->r11, ctx->r12);
L_801E47C4:
    // 0x801E47C4: b           L_801E47D8
    // 0x801E47C8: addu        $v1, $t5, $t6
    ctx->r3 = ADD32(ctx->r13, ctx->r14);
        goto L_801E47D8;
    // 0x801E47C8: addu        $v1, $t5, $t6
    ctx->r3 = ADD32(ctx->r13, ctx->r14);
L_801E47CC:
    // 0x801E47CC: lui         $t8, 0x8022
    ctx->r24 = S32(0X8022 << 16);
    // 0x801E47D0: addiu       $t8, $t8, 0x6BA0
    ctx->r24 = ADD32(ctx->r24, 0X6BA0);
    // 0x801E47D4: addu        $v1, $t7, $t8
    ctx->r3 = ADD32(ctx->r15, ctx->r24);
L_801E47D8:
    // 0x801E47D8: lhu         $t9, 0x0($v1)
    ctx->r25 = MEM_HU(ctx->r3, 0X0);
    // 0x801E47DC: sltiu       $at, $t9, 0x8
    ctx->r1 = ctx->r25 < 0X8 ? 1 : 0;
    // 0x801E47E0: beq         $at, $zero, L_801E491C
    if (ctx->r1 == 0) {
        // 0x801E47E4: sll         $t9, $t9, 2
        ctx->r25 = S32(ctx->r25 << 2);
            goto L_801E491C;
    }
    // 0x801E47E4: sll         $t9, $t9, 2
    ctx->r25 = S32(ctx->r25 << 2);
    // 0x801E47E8: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E47EC: addu        $at, $at, $t9
    gpr jr_addend_801E47F4 = ctx->r25;
    ctx->r1 = ADD32(ctx->r1, ctx->r25);
    // 0x801E47F0: lw          $t9, 0x6C10($at)
    ctx->r25 = ADD32(ctx->r1, 0X6C10);
    // 0x801E47F4: jr          $t9
    // 0x801E47F8: nop

    switch (jr_addend_801E47F4 >> 2) {
        case 0: goto L_801E47FC; break;
        case 1: goto L_801E4820; break;
        case 2: goto L_801E4844; break;
        case 3: goto L_801E4884; break;
        case 4: goto L_801E48A4; break;
        case 5: goto L_801E48C4; break;
        case 6: goto L_801E48E4; break;
        case 7: goto L_801E4904; break;
        default: switch_error(__func__, 0x801E47F4, 0x80226C10);
    }
    // 0x801E47F8: nop

L_801E47FC:
    // 0x801E47FC: addiu       $t3, $zero, -0x1
    ctx->r11 = ADD32(0, -0X1);
    // 0x801E4800: sh          $t3, 0x0($t0)
    MEM_H(0X0, ctx->r8) = ctx->r11;
    // 0x801E4804: lui         $t4, 0x8023
    ctx->r12 = S32(0X8023 << 16);
    // 0x801E4808: lw          $t4, -0x76F0($t4)
    ctx->r12 = MEM_W(ctx->r12, -0X76F0);
    // 0x801E480C: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x801E4810: addiu       $v1, $v1, -0x19B8
    ctx->r3 = ADD32(ctx->r3, -0X19B8);
    // 0x801E4814: sh          $zero, 0x0($a2)
    MEM_H(0X0, ctx->r6) = 0;
    // 0x801E4818: b           L_801E491C
    // 0x801E481C: sw          $t4, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r12;
        goto L_801E491C;
    // 0x801E481C: sw          $t4, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r12;
L_801E4820:
    // 0x801E4820: addiu       $t5, $zero, 0x4
    ctx->r13 = ADD32(0, 0X4);
    // 0x801E4824: sh          $t5, 0x0($a2)
    MEM_H(0X0, ctx->r6) = ctx->r13;
    // 0x801E4828: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x801E482C: sw          $a3, 0x60($sp)
    MEM_W(0X60, ctx->r29) = ctx->r7;
    // 0x801E4830: sw          $a3, -0x7E84($at)
    MEM_W(-0X7E84, ctx->r1) = ctx->r7;
    // 0x801E4834: jal         0x802C744C
    // 0x801E4838: addiu       $a0, $zero, 0x2
    ctx->r4 = ADD32(0, 0X2);
    func_i1_802C744C(rdram, ctx);
        goto after_8;
    // 0x801E4838: addiu       $a0, $zero, 0x2
    ctx->r4 = ADD32(0, 0X2);
    after_8:
    // 0x801E483C: b           L_801E491C
    // 0x801E4840: nop

        goto L_801E491C;
    // 0x801E4840: nop

L_801E4844:
    // 0x801E4844: addiu       $t6, $zero, -0x1
    ctx->r14 = ADD32(0, -0X1);
    // 0x801E4848: sh          $t6, 0x0($t0)
    MEM_H(0X0, ctx->r8) = ctx->r14;
    // 0x801E484C: lui         $t7, 0x8023
    ctx->r15 = S32(0X8023 << 16);
    // 0x801E4850: lw          $t7, -0x76F0($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X76F0);
    // 0x801E4854: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x801E4858: addiu       $v1, $v1, -0x19B8
    ctx->r3 = ADD32(ctx->r3, -0X19B8);
    // 0x801E485C: lui         $t8, 0x801D
    ctx->r24 = S32(0X801D << 16);
    // 0x801E4860: sw          $t7, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r15;
    // 0x801E4864: lh          $t8, -0x19D4($t8)
    ctx->r24 = MEM_H(ctx->r24, -0X19D4);
    // 0x801E4868: addiu       $t9, $zero, 0x2
    ctx->r25 = ADD32(0, 0X2);
    // 0x801E486C: bne         $a3, $t8, L_801E487C
    if (ctx->r7 != ctx->r24) {
        // 0x801E4870: nop
    
            goto L_801E487C;
    }
    // 0x801E4870: nop

    // 0x801E4874: b           L_801E491C
    // 0x801E4878: sh          $a3, 0x0($a2)
    MEM_H(0X0, ctx->r6) = ctx->r7;
        goto L_801E491C;
    // 0x801E4878: sh          $a3, 0x0($a2)
    MEM_H(0X0, ctx->r6) = ctx->r7;
L_801E487C:
    // 0x801E487C: b           L_801E491C
    // 0x801E4880: sh          $t9, 0x0($a2)
    MEM_H(0X0, ctx->r6) = ctx->r25;
        goto L_801E491C;
    // 0x801E4880: sh          $t9, 0x0($a2)
    MEM_H(0X0, ctx->r6) = ctx->r25;
L_801E4884:
    // 0x801E4884: addiu       $t3, $zero, 0x3
    ctx->r11 = ADD32(0, 0X3);
    // 0x801E4888: sh          $t3, 0x0($a2)
    MEM_H(0X0, ctx->r6) = ctx->r11;
    // 0x801E488C: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x801E4890: sw          $a3, -0x7E84($at)
    MEM_W(-0X7E84, ctx->r1) = ctx->r7;
    // 0x801E4894: jal         0x802C744C
    // 0x801E4898: addiu       $a0, $zero, 0x28
    ctx->r4 = ADD32(0, 0X28);
    func_i1_802C744C(rdram, ctx);
        goto after_9;
    // 0x801E4898: addiu       $a0, $zero, 0x28
    ctx->r4 = ADD32(0, 0X28);
    after_9:
    // 0x801E489C: b           L_801E491C
    // 0x801E48A0: nop

        goto L_801E491C;
    // 0x801E48A0: nop

L_801E48A4:
    // 0x801E48A4: addiu       $t4, $zero, 0x5
    ctx->r12 = ADD32(0, 0X5);
    // 0x801E48A8: sh          $t4, 0x0($a2)
    MEM_H(0X0, ctx->r6) = ctx->r12;
    // 0x801E48AC: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x801E48B0: sw          $a3, -0x7E84($at)
    MEM_W(-0X7E84, ctx->r1) = ctx->r7;
    // 0x801E48B4: jal         0x802C744C
    // 0x801E48B8: addiu       $a0, $zero, 0xA
    ctx->r4 = ADD32(0, 0XA);
    func_i1_802C744C(rdram, ctx);
        goto after_10;
    // 0x801E48B8: addiu       $a0, $zero, 0xA
    ctx->r4 = ADD32(0, 0XA);
    after_10:
    // 0x801E48BC: b           L_801E491C
    // 0x801E48C0: nop

        goto L_801E491C;
    // 0x801E48C0: nop

L_801E48C4:
    // 0x801E48C4: addiu       $t5, $zero, 0x6
    ctx->r13 = ADD32(0, 0X6);
    // 0x801E48C8: sh          $t5, 0x0($a2)
    MEM_H(0X0, ctx->r6) = ctx->r13;
    // 0x801E48CC: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x801E48D0: sw          $a3, -0x7E84($at)
    MEM_W(-0X7E84, ctx->r1) = ctx->r7;
    // 0x801E48D4: jal         0x802C744C
    // 0x801E48D8: addiu       $a0, $zero, 0x14
    ctx->r4 = ADD32(0, 0X14);
    func_i1_802C744C(rdram, ctx);
        goto after_11;
    // 0x801E48D8: addiu       $a0, $zero, 0x14
    ctx->r4 = ADD32(0, 0X14);
    after_11:
    // 0x801E48DC: b           L_801E491C
    // 0x801E48E0: nop

        goto L_801E491C;
    // 0x801E48E0: nop

L_801E48E4:
    // 0x801E48E4: addiu       $t6, $zero, 0x7
    ctx->r14 = ADD32(0, 0X7);
    // 0x801E48E8: sh          $t6, 0x0($a2)
    MEM_H(0X0, ctx->r6) = ctx->r14;
    // 0x801E48EC: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x801E48F0: sw          $a3, -0x7E84($at)
    MEM_W(-0X7E84, ctx->r1) = ctx->r7;
    // 0x801E48F4: jal         0x802C744C
    // 0x801E48F8: addiu       $a0, $zero, 0x1E
    ctx->r4 = ADD32(0, 0X1E);
    func_i1_802C744C(rdram, ctx);
        goto after_12;
    // 0x801E48F8: addiu       $a0, $zero, 0x1E
    ctx->r4 = ADD32(0, 0X1E);
    after_12:
    // 0x801E48FC: b           L_801E491C
    // 0x801E4900: nop

        goto L_801E491C;
    // 0x801E4900: nop

L_801E4904:
    // 0x801E4904: addiu       $t7, $zero, 0x8
    ctx->r15 = ADD32(0, 0X8);
    // 0x801E4908: sh          $t7, 0x0($a2)
    MEM_H(0X0, ctx->r6) = ctx->r15;
    // 0x801E490C: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x801E4910: sw          $a3, -0x7E84($at)
    MEM_W(-0X7E84, ctx->r1) = ctx->r7;
    // 0x801E4914: jal         0x802C744C
    // 0x801E4918: addiu       $a0, $zero, 0x1E
    ctx->r4 = ADD32(0, 0X1E);
    func_i1_802C744C(rdram, ctx);
        goto after_13;
    // 0x801E4918: addiu       $a0, $zero, 0x1E
    ctx->r4 = ADD32(0, 0X1E);
    after_13:
L_801E491C:
    // 0x801E491C: jal         0x800C3E18
    // 0x801E4920: nop

    func_800C3E18(rdram, ctx);
        goto after_14;
    // 0x801E4920: nop

    after_14:
    // 0x801E4924: lw          $t8, 0x60($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X60);
    // 0x801E4928: addiu       $a0, $zero, 0x11
    ctx->r4 = ADD32(0, 0X11);
    // 0x801E492C: beq         $t8, $zero, L_801E493C
    if (ctx->r24 == 0) {
        // 0x801E4930: nop
    
            goto L_801E493C;
    }
    // 0x801E4930: nop

    // 0x801E4934: jal         0x800C37F4
    // 0x801E4938: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_15;
    // 0x801E4938: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_15:
L_801E493C:
    // 0x801E493C: lui         $a1, 0x801D
    ctx->r5 = S32(0X801D << 16);
    // 0x801E4940: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x801E4944: lw          $v0, -0x54D8($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X54D8);
    // 0x801E4948: lh          $a1, -0x19DC($a1)
    ctx->r5 = MEM_H(ctx->r5, -0X19DC);
    // 0x801E494C: b           L_801E49D4
    // 0x801E4950: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
        goto L_801E49D4;
    // 0x801E4950: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
L_801E4954:
    // 0x801E4954: sh          $t9, 0x0($t0)
    MEM_H(0X0, ctx->r8) = ctx->r25;
    // 0x801E4958: lh          $t3, 0x0($t0)
    ctx->r11 = MEM_H(ctx->r8, 0X0);
    // 0x801E495C: lui         $t4, 0x801D
    ctx->r12 = S32(0X801D << 16);
    // 0x801E4960: addiu       $a0, $zero, 0x10
    ctx->r4 = ADD32(0, 0X10);
    // 0x801E4964: bgez        $t3, L_801E4978
    if (SIGNED(ctx->r11) >= 0) {
        // 0x801E4968: nop
    
            goto L_801E4978;
    }
    // 0x801E4968: nop

    // 0x801E496C: lh          $t4, -0x19DA($t4)
    ctx->r12 = MEM_H(ctx->r12, -0X19DA);
    // 0x801E4970: addiu       $t5, $t4, -0x1
    ctx->r13 = ADD32(ctx->r12, -0X1);
    // 0x801E4974: sh          $t5, 0x0($t0)
    MEM_H(0X0, ctx->r8) = ctx->r13;
L_801E4978:
    // 0x801E4978: jal         0x800C37F4
    // 0x801E497C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_16;
    // 0x801E497C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_16:
    // 0x801E4980: lui         $a1, 0x801D
    ctx->r5 = S32(0X801D << 16);
    // 0x801E4984: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x801E4988: lw          $v0, -0x54D8($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X54D8);
    // 0x801E498C: lh          $a1, -0x19DC($a1)
    ctx->r5 = MEM_H(ctx->r5, -0X19DC);
    // 0x801E4990: b           L_801E49D4
    // 0x801E4994: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
        goto L_801E49D4;
    // 0x801E4994: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
L_801E4998:
    // 0x801E4998: sh          $t6, 0x0($t0)
    MEM_H(0X0, ctx->r8) = ctx->r14;
    // 0x801E499C: lui         $t7, 0x801D
    ctx->r15 = S32(0X801D << 16);
    // 0x801E49A0: lh          $t7, -0x19DA($t7)
    ctx->r15 = MEM_H(ctx->r15, -0X19DA);
    // 0x801E49A4: lh          $t8, 0x0($t0)
    ctx->r24 = MEM_H(ctx->r8, 0X0);
    // 0x801E49A8: addiu       $a0, $zero, 0x10
    ctx->r4 = ADD32(0, 0X10);
    // 0x801E49AC: bne         $t7, $t8, L_801E49B8
    if (ctx->r15 != ctx->r24) {
        // 0x801E49B0: nop
    
            goto L_801E49B8;
    }
    // 0x801E49B0: nop

    // 0x801E49B4: sh          $zero, 0x0($t0)
    MEM_H(0X0, ctx->r8) = 0;
L_801E49B8:
    // 0x801E49B8: jal         0x800C37F4
    // 0x801E49BC: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_17;
    // 0x801E49BC: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_17:
    // 0x801E49C0: lui         $a1, 0x801D
    ctx->r5 = S32(0X801D << 16);
    // 0x801E49C4: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x801E49C8: lw          $v0, -0x54D8($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X54D8);
    // 0x801E49CC: lh          $a1, -0x19DC($a1)
    ctx->r5 = MEM_H(ctx->r5, -0X19DC);
    // 0x801E49D0: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
L_801E49D4:
    // 0x801E49D4: bne         $a2, $v0, L_801E49E8
    if (ctx->r6 != ctx->r2) {
        // 0x801E49D8: addiu       $at, $zero, -0x1
        ctx->r1 = ADD32(0, -0X1);
            goto L_801E49E8;
    }
    // 0x801E49D8: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x801E49DC: addiu       $t9, $zero, 0x41
    ctx->r25 = ADD32(0, 0X41);
    // 0x801E49E0: b           L_801E4A0C
    // 0x801E49E4: sw          $t9, 0x54($sp)
    MEM_W(0X54, ctx->r29) = ctx->r25;
        goto L_801E4A0C;
    // 0x801E49E4: sw          $t9, 0x54($sp)
    MEM_W(0X54, ctx->r29) = ctx->r25;
L_801E49E8:
    // 0x801E49E8: lui         $t3, 0x801D
    ctx->r11 = S32(0X801D << 16);
    // 0x801E49EC: lh          $t3, -0x19D4($t3)
    ctx->r11 = MEM_H(ctx->r11, -0X19D4);
    // 0x801E49F0: addiu       $t4, $zero, 0x28
    ctx->r12 = ADD32(0, 0X28);
    // 0x801E49F4: addiu       $t5, $zero, 0x96
    ctx->r13 = ADD32(0, 0X96);
    // 0x801E49F8: bnel        $a2, $t3, L_801E4A0C
    if (ctx->r6 != ctx->r11) {
        // 0x801E49FC: sw          $t5, 0x54($sp)
        MEM_W(0X54, ctx->r29) = ctx->r13;
            goto L_801E4A0C;
    }
    goto skip_6;
    // 0x801E49FC: sw          $t5, 0x54($sp)
    MEM_W(0X54, ctx->r29) = ctx->r13;
    skip_6:
    // 0x801E4A00: b           L_801E4A0C
    // 0x801E4A04: sw          $t4, 0x54($sp)
    MEM_W(0X54, ctx->r29) = ctx->r12;
        goto L_801E4A0C;
    // 0x801E4A04: sw          $t4, 0x54($sp)
    MEM_W(0X54, ctx->r29) = ctx->r12;
    // 0x801E4A08: sw          $t5, 0x54($sp)
    MEM_W(0X54, ctx->r29) = ctx->r13;
L_801E4A0C:
    // 0x801E4A0C: beql        $a1, $at, L_801E4BF8
    if (ctx->r5 == ctx->r1) {
        // 0x801E4A10: lw          $ra, 0x3C($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X3C);
            goto L_801E4BF8;
    }
    goto skip_7;
    // 0x801E4A10: lw          $ra, 0x3C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X3C);
    skip_7:
    // 0x801E4A14: bne         $a2, $v0, L_801E4A54
    if (ctx->r6 != ctx->r2) {
        // 0x801E4A18: lw          $a0, 0x70($sp)
        ctx->r4 = MEM_W(ctx->r29, 0X70);
            goto L_801E4A54;
    }
    // 0x801E4A18: lw          $a0, 0x70($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X70);
    // 0x801E4A1C: addiu       $t6, $zero, 0xF0
    ctx->r14 = ADD32(0, 0XF0);
    // 0x801E4A20: addiu       $t7, $zero, 0xA0
    ctx->r15 = ADD32(0, 0XA0);
    // 0x801E4A24: sw          $t7, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r15;
    // 0x801E4A28: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x801E4A2C: lw          $a0, 0x70($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X70);
    // 0x801E4A30: addiu       $a1, $zero, 0x0
    ctx->r5 = ADD32(0, 0X0);
    // 0x801E4A34: addiu       $a2, $zero, 0x0
    ctx->r6 = ADD32(0, 0X0);
    // 0x801E4A38: addiu       $a3, $zero, 0x1A8
    ctx->r7 = ADD32(0, 0X1A8);
    // 0x801E4A3C: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    // 0x801E4A40: sw          $zero, 0x18($sp)
    MEM_W(0X18, ctx->r29) = 0;
    // 0x801E4A44: jal         0x801E7C58
    // 0x801E4A48: sw          $zero, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = 0;
    func_801E7C58(rdram, ctx);
        goto after_18;
    // 0x801E4A48: sw          $zero, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = 0;
    after_18:
    // 0x801E4A4C: b           L_801E4A84
    // 0x801E4A50: sw          $v0, 0x70($sp)
    MEM_W(0X70, ctx->r29) = ctx->r2;
        goto L_801E4A84;
    // 0x801E4A50: sw          $v0, 0x70($sp)
    MEM_W(0X70, ctx->r29) = ctx->r2;
L_801E4A54:
    // 0x801E4A54: addiu       $t8, $zero, 0xF0
    ctx->r24 = ADD32(0, 0XF0);
    // 0x801E4A58: addiu       $t9, $zero, 0xA0
    ctx->r25 = ADD32(0, 0XA0);
    // 0x801E4A5C: sw          $t9, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r25;
    // 0x801E4A60: sw          $t8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r24;
    // 0x801E4A64: addiu       $a1, $zero, 0x0
    ctx->r5 = ADD32(0, 0X0);
    // 0x801E4A68: addiu       $a2, $zero, 0x0
    ctx->r6 = ADD32(0, 0X0);
    // 0x801E4A6C: addiu       $a3, $zero, 0x1A8
    ctx->r7 = ADD32(0, 0X1A8);
    // 0x801E4A70: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    // 0x801E4A74: sw          $zero, 0x18($sp)
    MEM_W(0X18, ctx->r29) = 0;
    // 0x801E4A78: jal         0x801E7C58
    // 0x801E4A7C: sw          $zero, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = 0;
    func_801E7C58(rdram, ctx);
        goto after_19;
    // 0x801E4A7C: sw          $zero, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = 0;
    after_19:
    // 0x801E4A80: sw          $v0, 0x70($sp)
    MEM_W(0X70, ctx->r29) = ctx->r2;
L_801E4A84:
    { extern uint32_t wr64_split_screen_pause(uint8_t*, uint32_t, int); MEM_W(0x70, ctx->r29) = wr64_split_screen_pause(rdram, MEM_W(0x70, ctx->r29), 1); }
    // 0x801E4A84: lui         $t3, 0x801D
    ctx->r11 = S32(0X801D << 16);
    // 0x801E4A88: lh          $t3, -0x19DA($t3)
    ctx->r11 = MEM_H(ctx->r11, -0X19DA);
    // 0x801E4A8C: lw          $a0, 0x70($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X70);
    // 0x801E4A90: or          $t1, $zero, $zero
    ctx->r9 = 0 | 0;
    // 0x801E4A94: blez        $t3, L_801E4BE8
    if (SIGNED(ctx->r11) <= 0) {
        // 0x801E4A98: or          $t0, $zero, $zero
        ctx->r8 = 0 | 0;
            goto L_801E4BE8;
    }
    // 0x801E4A98: or          $t0, $zero, $zero
    ctx->r8 = 0 | 0;
    // 0x801E4A9C: or          $t2, $zero, $zero
    ctx->r10 = 0 | 0;
    // 0x801E4AA0: sw          $a0, 0x70($sp)
    MEM_W(0X70, ctx->r29) = ctx->r4;
L_801E4AA4:
    // 0x801E4AA4: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x801E4AA8: lw          $v0, -0x19F8($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X19F8);
    // 0x801E4AAC: lw          $a0, 0x70($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X70);
    // 0x801E4AB0: lui         $t9, 0x801D
    ctx->r25 = S32(0X801D << 16);
    // 0x801E4AB4: beq         $v0, $zero, L_801E4AC4
    if (ctx->r2 == 0) {
        // 0x801E4AB8: addiu       $a2, $zero, 0xFF
        ctx->r6 = ADD32(0, 0XFF);
            goto L_801E4AC4;
    }
    // 0x801E4AB8: addiu       $a2, $zero, 0xFF
    ctx->r6 = ADD32(0, 0XFF);
    // 0x801E4ABC: addiu       $at, $zero, 0xB
    ctx->r1 = ADD32(0, 0XB);
    // 0x801E4AC0: bne         $v0, $at, L_801E4AD4
    if (ctx->r2 != ctx->r1) {
        // 0x801E4AC4: lui         $t4, 0x8022
        ctx->r12 = S32(0X8022 << 16);
            goto L_801E4AD4;
    }
L_801E4AC4:
    // 0x801E4AC4: lui         $t4, 0x8022
    ctx->r12 = S32(0X8022 << 16);
    // 0x801E4AC8: addiu       $t4, $t4, 0x6BE8
    ctx->r12 = ADD32(ctx->r12, 0X6BE8);
    // 0x801E4ACC: b           L_801E4B14
    // 0x801E4AD0: addu        $v1, $t0, $t4
    ctx->r3 = ADD32(ctx->r8, ctx->r12);
        goto L_801E4B14;
    // 0x801E4AD0: addu        $v1, $t0, $t4
    ctx->r3 = ADD32(ctx->r8, ctx->r12);
L_801E4AD4:
    // 0x801E4AD4: addiu       $at, $zero, 0x4
    ctx->r1 = ADD32(0, 0X4);
    // 0x801E4AD8: bne         $v0, $at, L_801E4B0C
    if (ctx->r2 != ctx->r1) {
        // 0x801E4ADC: lui         $t8, 0x8022
        ctx->r24 = S32(0X8022 << 16);
            goto L_801E4B0C;
    }
    // 0x801E4ADC: lui         $t8, 0x8022
    ctx->r24 = S32(0X8022 << 16);
    // 0x801E4AE0: lui         $t5, 0x800E
    ctx->r13 = S32(0X800E << 16);
    // 0x801E4AE4: lw          $t5, -0x7E90($t5)
    ctx->r13 = MEM_W(ctx->r13, -0X7E90);
    // 0x801E4AE8: lui         $t7, 0x8022
    ctx->r15 = S32(0X8022 << 16);
    // 0x801E4AEC: lui         $t6, 0x8022
    ctx->r14 = S32(0X8022 << 16);
    // 0x801E4AF0: bne         $t5, $zero, L_801E4B04
    if (ctx->r13 != 0) {
        // 0x801E4AF4: addiu       $t7, $t7, 0x6BB0
        ctx->r15 = ADD32(ctx->r15, 0X6BB0);
            goto L_801E4B04;
    }
    // 0x801E4AF4: addiu       $t7, $t7, 0x6BB0
    ctx->r15 = ADD32(ctx->r15, 0X6BB0);
    // 0x801E4AF8: addiu       $t6, $t6, 0x6BD0
    ctx->r14 = ADD32(ctx->r14, 0X6BD0);
    // 0x801E4AFC: b           L_801E4B14
    // 0x801E4B00: addu        $v1, $t0, $t6
    ctx->r3 = ADD32(ctx->r8, ctx->r14);
        goto L_801E4B14;
    // 0x801E4B00: addu        $v1, $t0, $t6
    ctx->r3 = ADD32(ctx->r8, ctx->r14);
L_801E4B04:
    // 0x801E4B04: b           L_801E4B14
    // 0x801E4B08: addu        $v1, $t0, $t7
    ctx->r3 = ADD32(ctx->r8, ctx->r15);
        goto L_801E4B14;
    // 0x801E4B08: addu        $v1, $t0, $t7
    ctx->r3 = ADD32(ctx->r8, ctx->r15);
L_801E4B0C:
    // 0x801E4B0C: addiu       $t8, $t8, 0x6BA0
    ctx->r24 = ADD32(ctx->r24, 0X6BA0);
    // 0x801E4B10: addu        $v1, $t0, $t8
    ctx->r3 = ADD32(ctx->r8, ctx->r24);
L_801E4B14:
    // 0x801E4B14: lh          $t9, -0x19DC($t9)
    ctx->r25 = MEM_H(ctx->r25, -0X19DC);
    // 0x801E4B18: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    // 0x801E4B1C: addiu       $t3, $zero, 0xFF
    ctx->r11 = ADD32(0, 0XFF);
    // 0x801E4B20: bne         $t1, $t9, L_801E4B30
    if (ctx->r9 != ctx->r25) {
        // 0x801E4B24: addiu       $t4, $zero, 0xFF
        ctx->r12 = ADD32(0, 0XFF);
            goto L_801E4B30;
    }
    // 0x801E4B24: addiu       $t4, $zero, 0xFF
    ctx->r12 = ADD32(0, 0XFF);
    // 0x801E4B28: b           L_801E4B34
    // 0x801E4B2C: addiu       $a1, $zero, 0x6
    ctx->r5 = ADD32(0, 0X6);
        goto L_801E4B34;
    // 0x801E4B2C: addiu       $a1, $zero, 0x6
    ctx->r5 = ADD32(0, 0X6);
L_801E4B30:
    // 0x801E4B30: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
L_801E4B34:
    // 0x801E4B34: addiu       $t5, $zero, 0xFF
    ctx->r13 = ADD32(0, 0XFF);
    // 0x801E4B38: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x801E4B3C: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x801E4B40: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x801E4B44: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x801E4B48: sw          $t9, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r25;
    // 0x801E4B4C: sw          $t8, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r24;
    // 0x801E4B50: sw          $t7, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r15;
    // 0x801E4B54: sw          $t6, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r14;
    // 0x801E4B58: sw          $t5, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r13;
    // 0x801E4B5C: sw          $t5, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r13;
    // 0x801E4B60: sw          $t3, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r11;
    // 0x801E4B64: sw          $t4, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r12;
    // 0x801E4B68: sw          $t3, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r11;
    // 0x801E4B6C: sw          $t4, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r12;
    // 0x801E4B70: sw          $v1, 0x50($sp)
    MEM_W(0X50, ctx->r29) = ctx->r3;
    // 0x801E4B74: sw          $t0, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r8;
    // 0x801E4B78: sw          $t1, 0x6C($sp)
    MEM_W(0X6C, ctx->r29) = ctx->r9;
    // 0x801E4B7C: jal         0x801E946C
    // 0x801E4B80: sw          $t2, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r10;
    func_801E946C(rdram, ctx);
        goto after_20;
    // 0x801E4B80: sw          $t2, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r10;
    after_20:
    // 0x801E4B84: lw          $v1, 0x50($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X50);
    // 0x801E4B88: lw          $t2, 0x40($sp)
    ctx->r10 = MEM_W(ctx->r29, 0X40);
    // 0x801E4B8C: lw          $t6, 0x54($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X54);
    // 0x801E4B90: lh          $a3, 0x2($v1)
    ctx->r7 = MEM_H(ctx->r3, 0X2);
    // 0x801E4B94: lw          $a2, 0x4($v1)
    ctx->r6 = MEM_W(ctx->r3, 0X4);
    // 0x801E4B98: addu        $t7, $t6, $t2
    ctx->r15 = ADD32(ctx->r14, ctx->r10);
    // 0x801E4B9C: addiu       $t8, $t7, 0x1E
    ctx->r24 = ADD32(ctx->r15, 0X1E);
    // 0x801E4BA0: sw          $t8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r24;
    // 0x801E4BA4: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    // 0x801E4BA8: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x801E4BAC: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x801E4BB0: jal         0x801E3EE0
    // 0x801E4BB4: addiu       $a3, $a3, 0xB4
    ctx->r7 = ADD32(ctx->r7, 0XB4);
    func_801E3EE0(rdram, ctx);
        goto after_21;
    // 0x801E4BB4: addiu       $a3, $a3, 0xB4
    ctx->r7 = ADD32(ctx->r7, 0XB4);
    after_21:
    // 0x801E4BB8: lw          $t1, 0x6C($sp)
    ctx->r9 = MEM_W(ctx->r29, 0X6C);
    // 0x801E4BBC: lui         $t9, 0x801D
    ctx->r25 = S32(0X801D << 16);
    // 0x801E4BC0: lh          $t9, -0x19DA($t9)
    ctx->r25 = MEM_H(ctx->r25, -0X19DA);
    // 0x801E4BC4: lw          $t0, 0x48($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X48);
    // 0x801E4BC8: lw          $t2, 0x40($sp)
    ctx->r10 = MEM_W(ctx->r29, 0X40);
    // 0x801E4BCC: addiu       $t1, $t1, 0x1
    ctx->r9 = ADD32(ctx->r9, 0X1);
    // 0x801E4BD0: slt         $at, $t1, $t9
    ctx->r1 = SIGNED(ctx->r9) < SIGNED(ctx->r25) ? 1 : 0;
    // 0x801E4BD4: sw          $v0, 0x70($sp)
    MEM_W(0X70, ctx->r29) = ctx->r2;
    // 0x801E4BD8: addiu       $t0, $t0, 0x8
    ctx->r8 = ADD32(ctx->r8, 0X8);
    // 0x801E4BDC: bne         $at, $zero, L_801E4AA4
    if (ctx->r1 != 0) {
        // 0x801E4BE0: addiu       $t2, $t2, 0xF
        ctx->r10 = ADD32(ctx->r10, 0XF);
            goto L_801E4AA4;
    }
    // 0x801E4BE0: addiu       $t2, $t2, 0xF
    ctx->r10 = ADD32(ctx->r10, 0XF);
    // 0x801E4BE4: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
L_801E4BE8:
    // 0x801E4BE8: jal         0x801E5554
    // 0x801E4BEC: nop

    func_801E5554(rdram, ctx);
        goto after_22;
    // 0x801E4BEC: nop

    after_22:
    // 0x801E4BF0: sw          $v0, 0x70($sp)
    MEM_W(0X70, ctx->r29) = ctx->r2;
    { extern uint32_t wr64_split_screen_pause(uint8_t*, uint32_t, int); MEM_W(0x70, ctx->r29) = wr64_split_screen_pause(rdram, MEM_W(0x70, ctx->r29), 0); }
    // 0x801E4BF4: lw          $ra, 0x3C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X3C);
L_801E4BF8:
    // 0x801E4BF8: lw          $v0, 0x70($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X70);
    // 0x801E4BFC: addiu       $sp, $sp, 0x70
    ctx->r29 = ADD32(ctx->r29, 0X70);
    // 0x801E4C00: jr          $ra
    // 0x801E4C04: nop

    return;
    // 0x801E4C04: nop

;}
RECOMP_FUNC void func_801E4C08(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801E4C08: addiu       $t6, $zero, 0x1
    ctx->r14 = ADD32(0, 0X1);
    // 0x801E4C0C: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801E4C10: sh          $t6, -0x19D4($at)
    MEM_H(-0X19D4, ctx->r1) = ctx->r14;
    // 0x801E4C14: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x801E4C18: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801E4C1C: addiu       $v0, $v0, -0x19B8
    ctx->r2 = ADD32(ctx->r2, -0X19B8);
    // 0x801E4C20: sh          $zero, -0x19DC($at)
    MEM_H(-0X19DC, ctx->r1) = 0;
    // 0x801E4C24: lw          $t7, 0x0($v0)
    ctx->r15 = MEM_W(ctx->r2, 0X0);
    // 0x801E4C28: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801E4C2C: sw          $t7, -0x76F0($at)
    MEM_W(-0X76F0, ctx->r1) = ctx->r15;
    // 0x801E4C30: jr          $ra
    // 0x801E4C34: sw          $zero, 0x0($v0)
    MEM_W(0X0, ctx->r2) = 0;
    return;
    // 0x801E4C34: sw          $zero, 0x0($v0)
    MEM_W(0X0, ctx->r2) = 0;
;}
RECOMP_FUNC void func_801E4C38(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801E4C38: lui         $t7, 0x8023
    ctx->r15 = S32(0X8023 << 16);
    // 0x801E4C3C: lw          $t7, -0x76F0($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X76F0);
    // 0x801E4C40: addiu       $t6, $zero, -0x1
    ctx->r14 = ADD32(0, -0X1);
    // 0x801E4C44: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801E4C48: sh          $t6, -0x19DC($at)
    MEM_H(-0X19DC, ctx->r1) = ctx->r14;
    // 0x801E4C4C: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801E4C50: sw          $t7, -0x19B8($at)
    MEM_W(-0X19B8, ctx->r1) = ctx->r15;
    // 0x801E4C54: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801E4C58: jr          $ra
    // 0x801E4C5C: sh          $zero, -0x19D8($at)
    MEM_H(-0X19D8, ctx->r1) = 0;
    return;
    // 0x801E4C5C: sh          $zero, -0x19D8($at)
    MEM_H(-0X19D8, ctx->r1) = 0;
;}
RECOMP_FUNC void func_801E4C60(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801E4C60: mtc1        $a1, $f14
    ctx->f14.u32l = ctx->r5;
    // 0x801E4C64: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E4C68: ldc1        $f0, 0x6C40($at)
    CHECK_FR(ctx, 0);
    ctx->f0.u64 = LD(ctx->r1, 0X6C40);
    // 0x801E4C6C: cvt.d.s     $f4, $f14
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f14.fl); 
    ctx->f4.d = CVT_D_S(ctx->f14.fl);
    // 0x801E4C70: addiu       $sp, $sp, -0x70
    ctx->r29 = ADD32(ctx->r29, -0X70);
    // 0x801E4C74: div.d       $f6, $f4, $f0
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f4.d); NAN_CHECK(ctx->f0.d); 
    ctx->f6.d = DIV_D(ctx->f4.d, ctx->f0.d);
    // 0x801E4C78: sdc1        $f20, 0x10($sp)
    CHECK_FR(ctx, 20);
    SD(ctx->f20.u64, 0X10, ctx->r29);
    // 0x801E4C7C: mtc1        $a2, $f20
    ctx->f20.u32l = ctx->r6;
    // 0x801E4C80: sdc1        $f22, 0x18($sp)
    CHECK_FR(ctx, 22);
    SD(ctx->f22.u64, 0X18, ctx->r29);
    // 0x801E4C84: mtc1        $a3, $f22
    ctx->f22.u32l = ctx->r7;
    // 0x801E4C88: cvt.d.s     $f8, $f20
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f20.fl); 
    ctx->f8.d = CVT_D_S(ctx->f20.fl);
    // 0x801E4C8C: sdc1        $f24, 0x20($sp)
    CHECK_FR(ctx, 24);
    SD(ctx->f24.u64, 0X20, ctx->r29);
    // 0x801E4C90: cvt.d.s     $f4, $f22
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f22.fl); 
    ctx->f4.d = CVT_D_S(ctx->f22.fl);
    // 0x801E4C94: lwc1        $f24, 0x80($sp)
    ctx->f24.u32l = MEM_W(ctx->r29, 0X80);
    // 0x801E4C98: sdc1        $f26, 0x28($sp)
    CHECK_FR(ctx, 26);
    SD(ctx->f26.u64, 0X28, ctx->r29);
    // 0x801E4C9C: lwc1        $f26, 0x84($sp)
    ctx->f26.u32l = MEM_W(ctx->r29, 0X84);
    // 0x801E4CA0: sdc1        $f28, 0x30($sp)
    CHECK_FR(ctx, 28);
    SD(ctx->f28.u64, 0X30, ctx->r29);
    // 0x801E4CA4: lwc1        $f28, 0x88($sp)
    ctx->f28.u32l = MEM_W(ctx->r29, 0X88);
    // 0x801E4CA8: lui         $at, 0x4780
    ctx->r1 = S32(0X4780 << 16);
    // 0x801E4CAC: sw          $ra, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r31;
    // 0x801E4CB0: lui         $t1, 0xFFFF
    ctx->r9 = S32(0XFFFF << 16);
    // 0x801E4CB4: div.d       $f10, $f8, $f0
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f8.d); NAN_CHECK(ctx->f0.d); 
    ctx->f10.d = DIV_D(ctx->f8.d, ctx->f0.d);
    // 0x801E4CB8: cvt.s.d     $f14, $f6
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f6.d); 
    ctx->f14.fl = CVT_S_D(ctx->f6.d);
    // 0x801E4CBC: cvt.d.s     $f8, $f24
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 24);
    NAN_CHECK(ctx->f24.fl); 
    ctx->f8.d = CVT_D_S(ctx->f24.fl);
    // 0x801E4CC0: div.d       $f6, $f4, $f0
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f4.d); NAN_CHECK(ctx->f0.d); 
    ctx->f6.d = DIV_D(ctx->f4.d, ctx->f0.d);
    // 0x801E4CC4: cvt.s.d     $f20, $f10
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f10.d); 
    ctx->f20.fl = CVT_S_D(ctx->f10.d);
    // 0x801E4CC8: cvt.d.s     $f4, $f26
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 26);
    NAN_CHECK(ctx->f26.fl); 
    ctx->f4.d = CVT_D_S(ctx->f26.fl);
    // 0x801E4CCC: div.d       $f10, $f8, $f0
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f8.d); NAN_CHECK(ctx->f0.d); 
    ctx->f10.d = DIV_D(ctx->f8.d, ctx->f0.d);
    // 0x801E4CD0: cvt.s.d     $f22, $f6
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f6.d); 
    ctx->f22.fl = CVT_S_D(ctx->f6.d);
    // 0x801E4CD4: cvt.d.s     $f8, $f28
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 28);
    NAN_CHECK(ctx->f28.fl); 
    ctx->f8.d = CVT_D_S(ctx->f28.fl);
    // 0x801E4CD8: div.d       $f6, $f4, $f0
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f4.d); NAN_CHECK(ctx->f0.d); 
    ctx->f6.d = DIV_D(ctx->f4.d, ctx->f0.d);
    // 0x801E4CDC: lwc1        $f4, 0x98($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X98);
    // 0x801E4CE0: cvt.s.d     $f24, $f10
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f10.d); 
    ctx->f24.fl = CVT_S_D(ctx->f10.d);
    // 0x801E4CE4: div.d       $f10, $f8, $f0
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f8.d); NAN_CHECK(ctx->f0.d); 
    ctx->f10.d = DIV_D(ctx->f8.d, ctx->f0.d);
    // 0x801E4CE8: cvt.s.d     $f26, $f6
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f6.d); 
    ctx->f26.fl = CVT_S_D(ctx->f6.d);
    // 0x801E4CEC: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x801E4CF0: nop

    // 0x801E4CF4: mul.s       $f16, $f4, $f6
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f16.fl = MUL_S(ctx->f4.fl, ctx->f6.fl);
    // 0x801E4CF8: nop

    // 0x801E4CFC: mul.s       $f8, $f14, $f16
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f8.fl = MUL_S(ctx->f14.fl, ctx->f16.fl);
    // 0x801E4D00: nop

    // 0x801E4D04: mul.s       $f4, $f20, $f16
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f4.fl = MUL_S(ctx->f20.fl, ctx->f16.fl);
    // 0x801E4D08: trunc.w.s   $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.u32l = TRUNC_W_S(ctx->f4.fl);
    // 0x801E4D0C: cvt.s.d     $f28, $f10
    CHECK_FR(ctx, 28);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f10.d); 
    ctx->f28.fl = CVT_S_D(ctx->f10.d);
    // 0x801E4D10: mfc1        $v1, $f6
    ctx->r3 = (int32_t)ctx->f6.u32l;
    // 0x801E4D14: trunc.w.s   $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.u32l = TRUNC_W_S(ctx->f8.fl);
    // 0x801E4D18: mul.s       $f8, $f22, $f16
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f8.fl = MUL_S(ctx->f22.fl, ctx->f16.fl);
    // 0x801E4D1C: andi        $t6, $v1, 0xFFFF
    ctx->r14 = ctx->r3 & 0XFFFF;
    // 0x801E4D20: srl         $t9, $v1, 16
    ctx->r25 = S32(U32(ctx->r3) >> 16);
    // 0x801E4D24: mul.s       $f4, $f26, $f22
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f26.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f4.fl = MUL_S(ctx->f26.fl, ctx->f22.fl);
    // 0x801E4D28: mfc1        $v0, $f10
    ctx->r2 = (int32_t)ctx->f10.u32l;
    // 0x801E4D2C: mul.s       $f6, $f28, $f20
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 28);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f28.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f6.fl = MUL_S(ctx->f28.fl, ctx->f20.fl);
    // 0x801E4D30: and         $t8, $v0, $t1
    ctx->r24 = ctx->r2 & ctx->r9;
    // 0x801E4D34: or          $t2, $t8, $t9
    ctx->r10 = ctx->r24 | ctx->r25;
    // 0x801E4D38: sll         $t5, $v0, 16
    ctx->r13 = S32(ctx->r2 << 16);
    // 0x801E4D3C: or          $t7, $t5, $t6
    ctx->r15 = ctx->r13 | ctx->r14;
    // 0x801E4D40: sw          $t2, 0x10($a0)
    MEM_W(0X10, ctx->r4) = ctx->r10;
    // 0x801E4D44: trunc.w.s   $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.u32l = TRUNC_W_S(ctx->f8.fl);
    // 0x801E4D48: mul.s       $f8, $f28, $f14
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 28);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f28.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f8.fl = MUL_S(ctx->f28.fl, ctx->f14.fl);
    // 0x801E4D4C: sw          $t7, 0x30($a0)
    MEM_W(0X30, ctx->r4) = ctx->r15;
    // 0x801E4D50: sub.s       $f18, $f4, $f6
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f18.fl = ctx->f4.fl - ctx->f6.fl;
    // 0x801E4D54: mfc1        $a1, $f10
    ctx->r5 = (int32_t)ctx->f10.u32l;
    // 0x801E4D58: mul.s       $f10, $f24, $f22
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f24.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f10.fl = MUL_S(ctx->f24.fl, ctx->f22.fl);
    // 0x801E4D5C: and         $t4, $a1, $t1
    ctx->r12 = ctx->r5 & ctx->r9;
    // 0x801E4D60: mul.s       $f4, $f24, $f20
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f24.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f4.fl = MUL_S(ctx->f24.fl, ctx->f20.fl);
    // 0x801E4D64: sll         $t8, $a1, 16
    ctx->r24 = S32(ctx->r5 << 16);
    // 0x801E4D68: sw          $t4, 0x14($a0)
    MEM_W(0X14, ctx->r4) = ctx->r12;
    // 0x801E4D6C: mul.s       $f6, $f26, $f14
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f26.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f6.fl = MUL_S(ctx->f26.fl, ctx->f14.fl);
    // 0x801E4D70: sw          $t8, 0x34($a0)
    MEM_W(0X34, ctx->r4) = ctx->r24;
    // 0x801E4D74: sub.s       $f2, $f8, $f10
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f2.fl = ctx->f8.fl - ctx->f10.fl;
    // 0x801E4D78: swc1        $f2, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->f2.u32l;
    // 0x801E4D7C: lwc1        $f8, 0x48($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X48);
    // 0x801E4D80: sub.s       $f0, $f4, $f6
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f0.fl = ctx->f4.fl - ctx->f6.fl;
    // 0x801E4D84: swc1        $f2, 0x64($sp)
    MEM_W(0X64, ctx->r29) = ctx->f2.u32l;
    // 0x801E4D88: mul.s       $f10, $f8, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = MUL_S(ctx->f8.fl, ctx->f8.fl);
    // 0x801E4D8C: swc1        $f0, 0x60($sp)
    MEM_W(0X60, ctx->r29) = ctx->f0.u32l;
    // 0x801E4D90: mul.s       $f4, $f18, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f4.fl = MUL_S(ctx->f18.fl, ctx->f18.fl);
    // 0x801E4D94: mtc1        $zero, $f5
    ctx->f_odd[(5 - 1) * 2] = 0;
    // 0x801E4D98: mul.s       $f8, $f0, $f0
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f8.fl = MUL_S(ctx->f0.fl, ctx->f0.fl);
    // 0x801E4D9C: add.s       $f6, $f4, $f10
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f6.fl = ctx->f4.fl + ctx->f10.fl;
    // 0x801E4DA0: mtc1        $zero, $f4
    ctx->f4.u32l = 0;
    // 0x801E4DA4: add.s       $f2, $f6, $f8
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f2.fl = ctx->f6.fl + ctx->f8.fl;
    // 0x801E4DA8: cvt.d.s     $f10, $f2
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f2.fl); 
    ctx->f10.d = CVT_D_S(ctx->f2.fl);
    // 0x801E4DAC: c.eq.d      $f4, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    c1cs = ctx->f4.d == ctx->f10.d;
    // 0x801E4DB0: nop

    // 0x801E4DB4: bc1t        L_801E4FC8
    if (c1cs) {
        // 0x801E4DB8: nop
    
            goto L_801E4FC8;
    }
    // 0x801E4DB8: nop

    // 0x801E4DBC: mov.s       $f12, $f2
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 2);
    ctx->f12.fl = ctx->f2.fl;
    // 0x801E4DC0: sw          $a0, 0x70($sp)
    MEM_W(0X70, ctx->r29) = ctx->r4;
    // 0x801E4DC4: swc1        $f14, 0x74($sp)
    MEM_W(0X74, ctx->r29) = ctx->f14.u32l;
    // 0x801E4DC8: swc1        $f16, 0x50($sp)
    MEM_W(0X50, ctx->r29) = ctx->f16.u32l;
    // 0x801E4DCC: jal         0x800C7010
    // 0x801E4DD0: swc1        $f18, 0x68($sp)
    MEM_W(0X68, ctx->r29) = ctx->f18.u32l;
    _nsqrtf(rdram, ctx);
        goto after_0;
    // 0x801E4DD0: swc1        $f18, 0x68($sp)
    MEM_W(0X68, ctx->r29) = ctx->f18.u32l;
    after_0:
    // 0x801E4DD4: lwc1        $f16, 0x50($sp)
    ctx->f16.u32l = MEM_W(ctx->r29, 0X50);
    // 0x801E4DD8: lwc1        $f18, 0x68($sp)
    ctx->f18.u32l = MEM_W(ctx->r29, 0X68);
    // 0x801E4DDC: lwc1        $f4, 0x64($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X64);
    // 0x801E4DE0: div.s       $f2, $f16, $f0
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f2.fl = DIV_S(ctx->f16.fl, ctx->f0.fl);
    // 0x801E4DE4: lw          $a0, 0x70($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X70);
    // 0x801E4DE8: lui         $t1, 0xFFFF
    ctx->r9 = S32(0XFFFF << 16);
    // 0x801E4DEC: lwc1        $f14, 0x74($sp)
    ctx->f14.u32l = MEM_W(ctx->r29, 0X74);
    // 0x801E4DF0: mul.s       $f6, $f18, $f2
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f6.fl = MUL_S(ctx->f18.fl, ctx->f2.fl);
    // 0x801E4DF4: nop

    // 0x801E4DF8: mul.s       $f10, $f4, $f2
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f10.fl = MUL_S(ctx->f4.fl, ctx->f2.fl);
    // 0x801E4DFC: trunc.w.s   $f8, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    ctx->f8.u32l = TRUNC_W_S(ctx->f6.fl);
    // 0x801E4E00: trunc.w.s   $f6, $f10
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    ctx->f6.u32l = TRUNC_W_S(ctx->f10.fl);
    // 0x801E4E04: mfc1        $v0, $f8
    ctx->r2 = (int32_t)ctx->f8.u32l;
    // 0x801E4E08: mfc1        $v1, $f6
    ctx->r3 = (int32_t)ctx->f6.u32l;
    // 0x801E4E0C: and         $t3, $v0, $t1
    ctx->r11 = ctx->r2 & ctx->r9;
    // 0x801E4E10: sll         $t8, $v0, 16
    ctx->r24 = S32(ctx->r2 << 16);
    // 0x801E4E14: srl         $t4, $v1, 16
    ctx->r12 = S32(U32(ctx->r3) >> 16);
    // 0x801E4E18: or          $t5, $t3, $t4
    ctx->r13 = ctx->r11 | ctx->r12;
    // 0x801E4E1C: sw          $t5, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r13;
    // 0x801E4E20: lwc1        $f8, 0x60($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X60);
    // 0x801E4E24: andi        $t9, $v1, 0xFFFF
    ctx->r25 = ctx->r3 & 0XFFFF;
    // 0x801E4E28: or          $t2, $t8, $t9
    ctx->r10 = ctx->r24 | ctx->r25;
    // 0x801E4E2C: mul.s       $f4, $f8, $f2
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f4.fl = MUL_S(ctx->f8.fl, ctx->f2.fl);
    // 0x801E4E30: sw          $t2, 0x20($a0)
    MEM_W(0X20, ctx->r4) = ctx->r10;
    // 0x801E4E34: trunc.w.s   $f10, $f4
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    ctx->f10.u32l = TRUNC_W_S(ctx->f4.fl);
    // 0x801E4E38: mfc1        $a1, $f10
    ctx->r5 = (int32_t)ctx->f10.u32l;
    // 0x801E4E3C: nop

    // 0x801E4E40: and         $t7, $a1, $t1
    ctx->r15 = ctx->r5 & ctx->r9;
    // 0x801E4E44: sll         $t3, $a1, 16
    ctx->r11 = S32(ctx->r5 << 16);
    // 0x801E4E48: sw          $t7, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r15;
    // 0x801E4E4C: sw          $t3, 0x24($a0)
    MEM_W(0X24, ctx->r4) = ctx->r11;
    // 0x801E4E50: lwc1        $f6, 0x60($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X60);
    // 0x801E4E54: lwc1        $f4, 0x64($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X64);
    // 0x801E4E58: swc1        $f16, 0x50($sp)
    MEM_W(0X50, ctx->r29) = ctx->f16.u32l;
    // 0x801E4E5C: mul.s       $f8, $f20, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = MUL_S(ctx->f20.fl, ctx->f6.fl);
    // 0x801E4E60: sw          $a0, 0x70($sp)
    MEM_W(0X70, ctx->r29) = ctx->r4;
    // 0x801E4E64: mul.s       $f10, $f22, $f4
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f10.fl = MUL_S(ctx->f22.fl, ctx->f4.fl);
    // 0x801E4E68: sub.s       $f12, $f8, $f10
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f12.fl = ctx->f8.fl - ctx->f10.fl;
    // 0x801E4E6C: mul.s       $f8, $f22, $f18
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f8.fl = MUL_S(ctx->f22.fl, ctx->f18.fl);
    // 0x801E4E70: nop

    // 0x801E4E74: mul.s       $f10, $f14, $f6
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f10.fl = MUL_S(ctx->f14.fl, ctx->f6.fl);
    // 0x801E4E78: swc1        $f12, 0x4C($sp)
    MEM_W(0X4C, ctx->r29) = ctx->f12.u32l;
    // 0x801E4E7C: lwc1        $f0, 0x4C($sp)
    ctx->f0.u32l = MEM_W(ctx->r29, 0X4C);
    // 0x801E4E80: mov.s       $f24, $f12
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 12);
    ctx->f24.fl = ctx->f12.fl;
    // 0x801E4E84: sub.s       $f26, $f8, $f10
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f26.fl = ctx->f8.fl - ctx->f10.fl;
    // 0x801E4E88: mul.s       $f8, $f14, $f4
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f8.fl = MUL_S(ctx->f14.fl, ctx->f4.fl);
    // 0x801E4E8C: nop

    // 0x801E4E90: mul.s       $f10, $f20, $f18
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f10.fl = MUL_S(ctx->f20.fl, ctx->f18.fl);
    // 0x801E4E94: swc1        $f26, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->f26.u32l;
    // 0x801E4E98: sub.s       $f28, $f8, $f10
    CHECK_FR(ctx, 28);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f28.fl = ctx->f8.fl - ctx->f10.fl;
    // 0x801E4E9C: mul.s       $f8, $f0, $f0
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f8.fl = MUL_S(ctx->f0.fl, ctx->f0.fl);
    // 0x801E4EA0: nop

    // 0x801E4EA4: mul.s       $f10, $f26, $f26
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 26);
    NAN_CHECK(ctx->f26.fl); NAN_CHECK(ctx->f26.fl); 
    ctx->f10.fl = MUL_S(ctx->f26.fl, ctx->f26.fl);
    // 0x801E4EA8: swc1        $f28, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->f28.u32l;
    // 0x801E4EAC: mul.s       $f4, $f28, $f28
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 28);
    CHECK_FR(ctx, 28);
    NAN_CHECK(ctx->f28.fl); NAN_CHECK(ctx->f28.fl); 
    ctx->f4.fl = MUL_S(ctx->f28.fl, ctx->f28.fl);
    // 0x801E4EB0: add.s       $f6, $f8, $f10
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f6.fl = ctx->f8.fl + ctx->f10.fl;
    // 0x801E4EB4: jal         0x800C7010
    // 0x801E4EB8: add.s       $f12, $f6, $f4
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f12.fl = ctx->f6.fl + ctx->f4.fl;
    _nsqrtf(rdram, ctx);
        goto after_1;
    // 0x801E4EB8: add.s       $f12, $f6, $f4
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f12.fl = ctx->f6.fl + ctx->f4.fl;
    after_1:
    // 0x801E4EBC: lui         $at, 0x4780
    ctx->r1 = S32(0X4780 << 16);
    // 0x801E4EC0: mtc1        $at, $f12
    ctx->f12.u32l = ctx->r1;
    // 0x801E4EC4: lui         $at, 0x3FF0
    ctx->r1 = S32(0X3FF0 << 16);
    // 0x801E4EC8: mtc1        $at, $f9
    ctx->f_odd[(9 - 1) * 2] = ctx->r1;
    // 0x801E4ECC: mtc1        $zero, $f8
    ctx->f8.u32l = 0;
    // 0x801E4ED0: cvt.d.s     $f10, $f0
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f0.fl); 
    ctx->f10.d = CVT_D_S(ctx->f0.fl);
    // 0x801E4ED4: lwc1        $f16, 0x50($sp)
    ctx->f16.u32l = MEM_W(ctx->r29, 0X50);
    // 0x801E4ED8: div.d       $f6, $f8, $f10
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.d); NAN_CHECK(ctx->f10.d); 
    ctx->f6.d = DIV_D(ctx->f8.d, ctx->f10.d);
    // 0x801E4EDC: lw          $a0, 0x70($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X70);
    // 0x801E4EE0: lui         $t1, 0xFFFF
    ctx->r9 = S32(0XFFFF << 16);
    // 0x801E4EE4: cvt.s.d     $f2, $f6
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f6.d); 
    ctx->f2.fl = CVT_S_D(ctx->f6.d);
    // 0x801E4EE8: mul.s       $f24, $f24, $f2
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f24.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f24.fl = MUL_S(ctx->f24.fl, ctx->f2.fl);
    // 0x801E4EEC: nop

    // 0x801E4EF0: mul.s       $f26, $f26, $f2
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f26.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f26.fl = MUL_S(ctx->f26.fl, ctx->f2.fl);
    // 0x801E4EF4: nop

    // 0x801E4EF8: mul.s       $f28, $f28, $f2
    CHECK_FR(ctx, 28);
    CHECK_FR(ctx, 28);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f28.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f28.fl = MUL_S(ctx->f28.fl, ctx->f2.fl);
    // 0x801E4EFC: nop

    // 0x801E4F00: mul.s       $f4, $f24, $f16
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f24.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f4.fl = MUL_S(ctx->f24.fl, ctx->f16.fl);
    // 0x801E4F04: trunc.w.s   $f8, $f4
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    ctx->f8.u32l = TRUNC_W_S(ctx->f4.fl);
    // 0x801E4F08: mul.s       $f10, $f26, $f16
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f26.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f10.fl = MUL_S(ctx->f26.fl, ctx->f16.fl);
    // 0x801E4F0C: nop

    // 0x801E4F10: mul.s       $f4, $f28, $f16
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 28);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f28.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f4.fl = MUL_S(ctx->f28.fl, ctx->f16.fl);
    // 0x801E4F14: mfc1        $v0, $f8
    ctx->r2 = (int32_t)ctx->f8.u32l;
    // 0x801E4F18: nop

    // 0x801E4F1C: and         $t6, $v0, $t1
    ctx->r14 = ctx->r2 & ctx->r9;
    // 0x801E4F20: sll         $t3, $v0, 16
    ctx->r11 = S32(ctx->r2 << 16);
    // 0x801E4F24: trunc.w.s   $f6, $f10
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    ctx->f6.u32l = TRUNC_W_S(ctx->f10.fl);
    // 0x801E4F28: trunc.w.s   $f8, $f4
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    ctx->f8.u32l = TRUNC_W_S(ctx->f4.fl);
    // 0x801E4F2C: mfc1        $v1, $f6
    ctx->r3 = (int32_t)ctx->f6.u32l;
    // 0x801E4F30: mfc1        $a1, $f8
    ctx->r5 = (int32_t)ctx->f8.u32l;
    // 0x801E4F34: srl         $t7, $v1, 16
    ctx->r15 = S32(U32(ctx->r3) >> 16);
    // 0x801E4F38: or          $t8, $t6, $t7
    ctx->r24 = ctx->r14 | ctx->r15;
    // 0x801E4F3C: andi        $t4, $v1, 0xFFFF
    ctx->r12 = ctx->r3 & 0XFFFF;
    // 0x801E4F40: or          $t5, $t3, $t4
    ctx->r13 = ctx->r11 | ctx->r12;
    // 0x801E4F44: and         $t2, $a1, $t1
    ctx->r10 = ctx->r5 & ctx->r9;
    // 0x801E4F48: sll         $t6, $a1, 16
    ctx->r14 = S32(ctx->r5 << 16);
    // 0x801E4F4C: sw          $t8, 0x8($a0)
    MEM_W(0X8, ctx->r4) = ctx->r24;
    // 0x801E4F50: sw          $t2, 0xC($a0)
    MEM_W(0XC, ctx->r4) = ctx->r10;
    // 0x801E4F54: sw          $t5, 0x28($a0)
    MEM_W(0X28, ctx->r4) = ctx->r13;
    // 0x801E4F58: sw          $t6, 0x2C($a0)
    MEM_W(0X2C, ctx->r4) = ctx->r14;
    // 0x801E4F5C: lwc1        $f10, 0x8C($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0X8C);
    // 0x801E4F60: lwc1        $f8, 0x90($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X90);
    // 0x801E4F64: mul.s       $f6, $f12, $f10
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f6.fl = MUL_S(ctx->f12.fl, ctx->f10.fl);
    // 0x801E4F68: nop

    // 0x801E4F6C: mul.s       $f10, $f12, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = MUL_S(ctx->f12.fl, ctx->f8.fl);
    // 0x801E4F70: trunc.w.s   $f4, $f6
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    ctx->f4.u32l = TRUNC_W_S(ctx->f6.fl);
    // 0x801E4F74: trunc.w.s   $f6, $f10
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    ctx->f6.u32l = TRUNC_W_S(ctx->f10.fl);
    // 0x801E4F78: mfc1        $a2, $f4
    ctx->r6 = (int32_t)ctx->f4.u32l;
    // 0x801E4F7C: mfc1        $a3, $f6
    ctx->r7 = (int32_t)ctx->f6.u32l;
    // 0x801E4F80: and         $t9, $a2, $t1
    ctx->r25 = ctx->r6 & ctx->r9;
    // 0x801E4F84: sll         $t7, $a2, 16
    ctx->r15 = S32(ctx->r6 << 16);
    // 0x801E4F88: srl         $t2, $a3, 16
    ctx->r10 = S32(U32(ctx->r7) >> 16);
    // 0x801E4F8C: or          $t3, $t9, $t2
    ctx->r11 = ctx->r25 | ctx->r10;
    // 0x801E4F90: sw          $t3, 0x18($a0)
    MEM_W(0X18, ctx->r4) = ctx->r11;
    // 0x801E4F94: lwc1        $f4, 0x94($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X94);
    // 0x801E4F98: andi        $t8, $a3, 0xFFFF
    ctx->r24 = ctx->r7 & 0XFFFF;
    // 0x801E4F9C: or          $t9, $t7, $t8
    ctx->r25 = ctx->r15 | ctx->r24;
    // 0x801E4FA0: mul.s       $f8, $f12, $f4
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f8.fl = MUL_S(ctx->f12.fl, ctx->f4.fl);
    // 0x801E4FA4: sw          $t9, 0x38($a0)
    MEM_W(0X38, ctx->r4) = ctx->r25;
    // 0x801E4FA8: trunc.w.s   $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.u32l = TRUNC_W_S(ctx->f8.fl);
    // 0x801E4FAC: mfc1        $t0, $f10
    ctx->r8 = (int32_t)ctx->f10.u32l;
    // 0x801E4FB0: nop

    // 0x801E4FB4: and         $t5, $t0, $t1
    ctx->r13 = ctx->r8 & ctx->r9;
    // 0x801E4FB8: ori         $t6, $t5, 0x1
    ctx->r14 = ctx->r13 | 0X1;
    // 0x801E4FBC: sll         $t2, $t0, 16
    ctx->r10 = S32(ctx->r8 << 16);
    // 0x801E4FC0: sw          $t6, 0x1C($a0)
    MEM_W(0X1C, ctx->r4) = ctx->r14;
    // 0x801E4FC4: sw          $t2, 0x3C($a0)
    MEM_W(0X3C, ctx->r4) = ctx->r10;
L_801E4FC8:
    // 0x801E4FC8: lw          $ra, 0x3C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X3C);
    // 0x801E4FCC: ldc1        $f20, 0x10($sp)
    CHECK_FR(ctx, 20);
    ctx->f20.u64 = LD(ctx->r29, 0X10);
    // 0x801E4FD0: ldc1        $f22, 0x18($sp)
    CHECK_FR(ctx, 22);
    ctx->f22.u64 = LD(ctx->r29, 0X18);
    // 0x801E4FD4: ldc1        $f24, 0x20($sp)
    CHECK_FR(ctx, 24);
    ctx->f24.u64 = LD(ctx->r29, 0X20);
    // 0x801E4FD8: ldc1        $f26, 0x28($sp)
    CHECK_FR(ctx, 26);
    ctx->f26.u64 = LD(ctx->r29, 0X28);
    // 0x801E4FDC: ldc1        $f28, 0x30($sp)
    CHECK_FR(ctx, 28);
    ctx->f28.u64 = LD(ctx->r29, 0X30);
    // 0x801E4FE0: jr          $ra
    // 0x801E4FE4: addiu       $sp, $sp, 0x70
    ctx->r29 = ADD32(ctx->r29, 0X70);
    return;
    // 0x801E4FE4: addiu       $sp, $sp, 0x70
    ctx->r29 = ADD32(ctx->r29, 0X70);
;}
RECOMP_FUNC void func_801E4FE8(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801E4FE8: addiu       $sp, $sp, -0x80
    ctx->r29 = ADD32(ctx->r29, -0X80);
    // 0x801E4FEC: lui         $t7, 0x8023
    ctx->r15 = S32(0X8023 << 16);
    // 0x801E4FF0: lw          $t7, -0x76E0($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X76E0);
    // 0x801E4FF4: sw          $s0, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r16;
    // 0x801E4FF8: or          $s0, $a0, $zero
    ctx->r16 = ctx->r4 | 0;
    // 0x801E4FFC: sw          $ra, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r31;
    // 0x801E5000: sw          $a1, 0x84($sp)
    MEM_W(0X84, ctx->r29) = ctx->r5;
    // 0x801E5004: sw          $a2, 0x88($sp)
    MEM_W(0X88, ctx->r29) = ctx->r6;
    // 0x801E5008: beq         $a2, $t7, L_801E5018
    if (ctx->r6 == ctx->r15) {
        // 0x801E500C: sw          $a3, 0x8C($sp)
        MEM_W(0X8C, ctx->r29) = ctx->r7;
            goto L_801E5018;
    }
    // 0x801E500C: sw          $a3, 0x8C($sp)
    MEM_W(0X8C, ctx->r29) = ctx->r7;
    // 0x801E5010: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801E5014: sw          $zero, 0x6C30($at)
    MEM_W(0X6C30, ctx->r1) = 0;
L_801E5018:
    // 0x801E5018: lw          $t8, 0x88($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X88);
    // 0x801E501C: lui         $t4, 0x8022
    ctx->r12 = S32(0X8022 << 16);
    // 0x801E5020: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801E5024: sll         $t9, $t8, 2
    ctx->r25 = S32(ctx->r24 << 2);
    // 0x801E5028: addu        $t4, $t4, $t9
    ctx->r12 = ADD32(ctx->r12, ctx->r25);
    // 0x801E502C: lw          $t4, 0x38DC($t4)
    ctx->r12 = MEM_W(ctx->r12, 0X38DC);
    // 0x801E5030: lui         $t6, 0x8022
    ctx->r14 = S32(0X8022 << 16);
    // 0x801E5034: lw          $t6, 0x6C30($t6)
    ctx->r14 = MEM_W(ctx->r14, 0X6C30);
    // 0x801E5038: sw          $t8, -0x76E0($at)
    MEM_W(-0X76E0, ctx->r1) = ctx->r24;
    // 0x801E503C: lw          $t5, 0x44($t4)
    ctx->r13 = MEM_W(ctx->r12, 0X44);
    // 0x801E5040: sll         $t7, $t6, 1
    ctx->r15 = S32(ctx->r14 << 1);
    // 0x801E5044: lw          $t9, 0x4($t4)
    ctx->r25 = MEM_W(ctx->r12, 0X4);
    // 0x801E5048: addu        $t8, $t5, $t7
    ctx->r24 = ADD32(ctx->r13, ctx->r15);
    // 0x801E504C: lh          $v1, 0x0($t8)
    ctx->r3 = MEM_H(ctx->r24, 0X0);
    // 0x801E5050: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x801E5054: lw          $a0, 0x90($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X90);
    // 0x801E5058: sll         $t6, $v1, 2
    ctx->r14 = S32(ctx->r3 << 2);
    // 0x801E505C: subu        $t6, $t6, $v1
    ctx->r14 = SUB32(ctx->r14, ctx->r3);
    // 0x801E5060: sll         $t6, $t6, 2
    ctx->r14 = S32(ctx->r14 << 2);
    // 0x801E5064: addu        $v0, $t9, $t6
    ctx->r2 = ADD32(ctx->r25, ctx->r14);
    // 0x801E5068: lb          $t9, 0x9($v0)
    ctx->r25 = MEM_B(ctx->r2, 0X9);
    // 0x801E506C: lb          $t5, 0x6($v0)
    ctx->r13 = MEM_B(ctx->r2, 0X6);
    // 0x801E5070: lb          $t7, 0x7($v0)
    ctx->r15 = MEM_B(ctx->r2, 0X7);
    // 0x801E5074: mtc1        $t9, $f10
    ctx->f10.u32l = ctx->r25;
    // 0x801E5078: mtc1        $t5, $f4
    ctx->f4.u32l = ctx->r13;
    // 0x801E507C: lb          $t8, 0x8($v0)
    ctx->r24 = MEM_B(ctx->r2, 0X8);
    // 0x801E5080: cvt.s.w     $f16, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    ctx->f16.fl = CVT_S_W(ctx->f10.u32l);
    // 0x801E5084: mtc1        $t7, $f6
    ctx->f6.u32l = ctx->r15;
    // 0x801E5088: mtc1        $t8, $f8
    ctx->f8.u32l = ctx->r24;
    // 0x801E508C: cvt.s.w     $f4, $f4
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 4);
    ctx->f4.fl = CVT_S_W(ctx->f4.u32l);
    // 0x801E5090: swc1        $f16, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f16.u32l;
    // 0x801E5094: lb          $t6, 0xA($v0)
    ctx->r14 = MEM_B(ctx->r2, 0XA);
    // 0x801E5098: mtc1        $t6, $f18
    ctx->f18.u32l = ctx->r14;
    // 0x801E509C: mfc1        $a1, $f4
    ctx->r5 = (int32_t)ctx->f4.u32l;
    // 0x801E50A0: cvt.s.w     $f6, $f6
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 6);
    ctx->f6.fl = CVT_S_W(ctx->f6.u32l);
    // 0x801E50A4: cvt.s.w     $f4, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    ctx->f4.fl = CVT_S_W(ctx->f18.u32l);
    // 0x801E50A8: mfc1        $a2, $f6
    ctx->r6 = (int32_t)ctx->f6.u32l;
    // 0x801E50AC: cvt.s.w     $f8, $f8
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 8);
    ctx->f8.fl = CVT_S_W(ctx->f8.u32l);
    // 0x801E50B0: swc1        $f4, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->f4.u32l;
    // 0x801E50B4: lb          $t5, 0xB($v0)
    ctx->r13 = MEM_B(ctx->r2, 0XB);
    // 0x801E50B8: mtc1        $t5, $f6
    ctx->f6.u32l = ctx->r13;
    // 0x801E50BC: mfc1        $a3, $f8
    ctx->r7 = (int32_t)ctx->f8.u32l;
    // 0x801E50C0: cvt.s.w     $f8, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    ctx->f8.fl = CVT_S_W(ctx->f6.u32l);
    // 0x801E50C4: swc1        $f8, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->f8.u32l;
    // 0x801E50C8: lh          $t7, 0x0($v0)
    ctx->r15 = MEM_H(ctx->r2, 0X0);
    // 0x801E50CC: mtc1        $t7, $f10
    ctx->f10.u32l = ctx->r15;
    // 0x801E50D0: nop

    // 0x801E50D4: cvt.s.w     $f16, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    ctx->f16.fl = CVT_S_W(ctx->f10.u32l);
    // 0x801E50D8: mtc1        $at, $f10
    ctx->f10.u32l = ctx->r1;
    // 0x801E50DC: swc1        $f16, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->f16.u32l;
    // 0x801E50E0: lh          $t8, 0x2($v0)
    ctx->r24 = MEM_H(ctx->r2, 0X2);
    // 0x801E50E4: mtc1        $t8, $f18
    ctx->f18.u32l = ctx->r24;
    // 0x801E50E8: nop

    // 0x801E50EC: cvt.s.w     $f4, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    ctx->f4.fl = CVT_S_W(ctx->f18.u32l);
    // 0x801E50F0: swc1        $f4, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->f4.u32l;
    // 0x801E50F4: lh          $t9, 0x4($v0)
    ctx->r25 = MEM_H(ctx->r2, 0X4);
    // 0x801E50F8: sw          $t4, 0x7C($sp)
    MEM_W(0X7C, ctx->r29) = ctx->r12;
    // 0x801E50FC: swc1        $f10, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->f10.u32l;
    // 0x801E5100: mtc1        $t9, $f6
    ctx->f6.u32l = ctx->r25;
    // 0x801E5104: nop

    // 0x801E5108: cvt.s.w     $f8, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    ctx->f8.fl = CVT_S_W(ctx->f6.u32l);
    // 0x801E510C: jal         0x801E4C60
    // 0x801E5110: swc1        $f8, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->f8.u32l;
    func_801E4C60(rdram, ctx);
        goto after_0;
    // 0x801E5110: swc1        $f8, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->f8.u32l;
    after_0:
    // 0x801E5114: lw          $t1, 0x90($sp)
    ctx->r9 = MEM_W(ctx->r29, 0X90);
    // 0x801E5118: lui         $at, 0x1FFF
    ctx->r1 = S32(0X1FFF << 16);
    // 0x801E511C: lw          $v1, 0x84($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X84);
    // 0x801E5120: lw          $t4, 0x7C($sp)
    ctx->r12 = MEM_W(ctx->r29, 0X7C);
    // 0x801E5124: ori         $at, $at, 0xFFFF
    ctx->r1 = ctx->r1 | 0XFFFF;
    // 0x801E5128: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
    // 0x801E512C: lui         $t6, 0x104
    ctx->r14 = S32(0X104 << 16);
    // 0x801E5130: ori         $t6, $t6, 0x40
    ctx->r14 = ctx->r14 | 0X40;
    // 0x801E5134: and         $t5, $t1, $at
    ctx->r13 = ctx->r9 & ctx->r1;
    // 0x801E5138: sw          $t5, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r13;
    // 0x801E513C: sw          $t6, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r14;
    // 0x801E5140: lui         $t7, 0x801D
    ctx->r15 = S32(0X801D << 16);
    // 0x801E5144: lw          $t7, -0x19C8($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X19C8);
    // 0x801E5148: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801E514C: addiu       $at, $zero, 0x15
    ctx->r1 = ADD32(0, 0X15);
    // 0x801E5150: bne         $t7, $at, L_801E5198
    if (ctx->r15 != ctx->r1) {
        // 0x801E5154: or          $v0, $s0, $zero
        ctx->r2 = ctx->r16 | 0;
            goto L_801E5198;
    }
    // 0x801E5154: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
    // 0x801E5158: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
    // 0x801E515C: lui         $t8, 0x600
    ctx->r24 = S32(0X600 << 16);
    // 0x801E5160: sll         $t9, $v1, 2
    ctx->r25 = S32(ctx->r3 << 2);
    // 0x801E5164: lui         $t6, 0x801D
    ctx->r14 = S32(0X801D << 16);
    // 0x801E5168: addu        $t6, $t6, $t9
    ctx->r14 = ADD32(ctx->r14, ctx->r25);
    // 0x801E516C: sw          $t8, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r24;
    // 0x801E5170: sll         $t5, $v1, 4
    ctx->r13 = S32(ctx->r3 << 4);
    // 0x801E5174: lw          $t6, -0x1660($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X1660);
    // 0x801E5178: addu        $t5, $t5, $v1
    ctx->r13 = ADD32(ctx->r13, ctx->r3);
    // 0x801E517C: lui         $t7, 0x8022
    ctx->r15 = S32(0X8022 << 16);
    // 0x801E5180: addiu       $t7, $t7, 0x7A60
    ctx->r15 = ADD32(ctx->r15, 0X7A60);
    // 0x801E5184: sll         $t5, $t5, 2
    ctx->r13 = S32(ctx->r13 << 2);
    // 0x801E5188: addu        $t3, $t5, $t7
    ctx->r11 = ADD32(ctx->r13, ctx->r15);
    // 0x801E518C: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801E5190: b           L_801E51C4
    // 0x801E5194: sw          $t6, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r14;
        goto L_801E51C4;
    // 0x801E5194: sw          $t6, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r14;
L_801E5198:
    // 0x801E5198: sll         $t9, $v1, 4
    ctx->r25 = S32(ctx->r3 << 4);
    // 0x801E519C: addu        $t9, $t9, $v1
    ctx->r25 = ADD32(ctx->r25, ctx->r3);
    // 0x801E51A0: lui         $t6, 0x8022
    ctx->r14 = S32(0X8022 << 16);
    // 0x801E51A4: addiu       $t6, $t6, 0x7A60
    ctx->r14 = ADD32(ctx->r14, 0X7A60);
    // 0x801E51A8: sll         $t9, $t9, 2
    ctx->r25 = S32(ctx->r25 << 2);
    // 0x801E51AC: lui         $t8, 0x600
    ctx->r24 = S32(0X600 << 16);
    // 0x801E51B0: sw          $t8, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r24;
    // 0x801E51B4: addu        $t3, $t9, $t6
    ctx->r11 = ADD32(ctx->r25, ctx->r14);
    // 0x801E51B8: lw          $t5, 0x8($t3)
    ctx->r13 = MEM_W(ctx->r11, 0X8);
    // 0x801E51BC: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801E51C0: sw          $t5, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r13;
L_801E51C4:
    // 0x801E51C4: or          $t0, $s0, $zero
    ctx->r8 = ctx->r16 | 0;
    // 0x801E51C8: lui         $t7, 0xBD00
    ctx->r15 = S32(0XBD00 << 16);
    // 0x801E51CC: sw          $t7, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r15;
    // 0x801E51D0: sw          $zero, 0x4($t0)
    MEM_W(0X4, ctx->r8) = 0;
    // 0x801E51D4: lui         $t9, 0x8022
    ctx->r25 = S32(0X8022 << 16);
    // 0x801E51D8: lw          $t9, 0x6C30($t9)
    ctx->r25 = MEM_W(ctx->r25, 0X6C30);
    // 0x801E51DC: lw          $t8, 0x48($t4)
    ctx->r24 = MEM_W(ctx->r12, 0X48);
    // 0x801E51E0: lw          $t7, 0x4($t4)
    ctx->r15 = MEM_W(ctx->r12, 0X4);
    // 0x801E51E4: sll         $t6, $t9, 1
    ctx->r14 = S32(ctx->r25 << 1);
    // 0x801E51E8: addu        $t5, $t8, $t6
    ctx->r13 = ADD32(ctx->r24, ctx->r14);
    // 0x801E51EC: lh          $v1, 0x0($t5)
    ctx->r3 = MEM_H(ctx->r13, 0X0);
    // 0x801E51F0: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x801E51F4: addiu       $a0, $t1, 0x40
    ctx->r4 = ADD32(ctx->r9, 0X40);
    // 0x801E51F8: sll         $t9, $v1, 2
    ctx->r25 = S32(ctx->r3 << 2);
    // 0x801E51FC: subu        $t9, $t9, $v1
    ctx->r25 = SUB32(ctx->r25, ctx->r3);
    // 0x801E5200: sll         $t9, $t9, 2
    ctx->r25 = S32(ctx->r25 << 2);
    // 0x801E5204: addu        $v0, $t7, $t9
    ctx->r2 = ADD32(ctx->r15, ctx->r25);
    // 0x801E5208: lb          $t7, 0x9($v0)
    ctx->r15 = MEM_B(ctx->r2, 0X9);
    // 0x801E520C: lb          $t8, 0x6($v0)
    ctx->r24 = MEM_B(ctx->r2, 0X6);
    // 0x801E5210: lb          $t6, 0x7($v0)
    ctx->r14 = MEM_B(ctx->r2, 0X7);
    // 0x801E5214: mtc1        $t7, $f6
    ctx->f6.u32l = ctx->r15;
    // 0x801E5218: mtc1        $t8, $f16
    ctx->f16.u32l = ctx->r24;
    // 0x801E521C: lb          $t5, 0x8($v0)
    ctx->r13 = MEM_B(ctx->r2, 0X8);
    // 0x801E5220: cvt.s.w     $f8, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    ctx->f8.fl = CVT_S_W(ctx->f6.u32l);
    // 0x801E5224: mtc1        $t6, $f18
    ctx->f18.u32l = ctx->r14;
    // 0x801E5228: mtc1        $t5, $f4
    ctx->f4.u32l = ctx->r13;
    // 0x801E522C: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801E5230: cvt.s.w     $f16, $f16
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 16);
    ctx->f16.fl = CVT_S_W(ctx->f16.u32l);
    // 0x801E5234: swc1        $f8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f8.u32l;
    // 0x801E5238: lb          $t9, 0xA($v0)
    ctx->r25 = MEM_B(ctx->r2, 0XA);
    // 0x801E523C: mtc1        $t9, $f10
    ctx->f10.u32l = ctx->r25;
    // 0x801E5240: mfc1        $a1, $f16
    ctx->r5 = (int32_t)ctx->f16.u32l;
    // 0x801E5244: cvt.s.w     $f18, $f18
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 18);
    ctx->f18.fl = CVT_S_W(ctx->f18.u32l);
    // 0x801E5248: cvt.s.w     $f16, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    ctx->f16.fl = CVT_S_W(ctx->f10.u32l);
    // 0x801E524C: mfc1        $a2, $f18
    ctx->r6 = (int32_t)ctx->f18.u32l;
    // 0x801E5250: cvt.s.w     $f4, $f4
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 4);
    ctx->f4.fl = CVT_S_W(ctx->f4.u32l);
    // 0x801E5254: swc1        $f16, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->f16.u32l;
    // 0x801E5258: lb          $t8, 0xB($v0)
    ctx->r24 = MEM_B(ctx->r2, 0XB);
    // 0x801E525C: mtc1        $t8, $f18
    ctx->f18.u32l = ctx->r24;
    // 0x801E5260: mfc1        $a3, $f4
    ctx->r7 = (int32_t)ctx->f4.u32l;
    // 0x801E5264: cvt.s.w     $f4, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    ctx->f4.fl = CVT_S_W(ctx->f18.u32l);
    // 0x801E5268: swc1        $f4, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->f4.u32l;
    // 0x801E526C: lh          $t6, 0x0($v0)
    ctx->r14 = MEM_H(ctx->r2, 0X0);
    // 0x801E5270: mtc1        $t6, $f6
    ctx->f6.u32l = ctx->r14;
    // 0x801E5274: nop

    // 0x801E5278: cvt.s.w     $f8, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    ctx->f8.fl = CVT_S_W(ctx->f6.u32l);
    // 0x801E527C: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x801E5280: swc1        $f8, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->f8.u32l;
    // 0x801E5284: lh          $t5, 0x2($v0)
    ctx->r13 = MEM_H(ctx->r2, 0X2);
    // 0x801E5288: mtc1        $t5, $f10
    ctx->f10.u32l = ctx->r13;
    // 0x801E528C: nop

    // 0x801E5290: cvt.s.w     $f16, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    ctx->f16.fl = CVT_S_W(ctx->f10.u32l);
    // 0x801E5294: swc1        $f16, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->f16.u32l;
    // 0x801E5298: lh          $t7, 0x4($v0)
    ctx->r15 = MEM_H(ctx->r2, 0X4);
    // 0x801E529C: sw          $t4, 0x7C($sp)
    MEM_W(0X7C, ctx->r29) = ctx->r12;
    // 0x801E52A0: sw          $t3, 0x4C($sp)
    MEM_W(0X4C, ctx->r29) = ctx->r11;
    // 0x801E52A4: mtc1        $t7, $f18
    ctx->f18.u32l = ctx->r15;
    // 0x801E52A8: sw          $a0, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r4;
    // 0x801E52AC: swc1        $f6, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->f6.u32l;
    // 0x801E52B0: cvt.s.w     $f4, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    ctx->f4.fl = CVT_S_W(ctx->f18.u32l);
    // 0x801E52B4: jal         0x801E4C60
    // 0x801E52B8: swc1        $f4, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->f4.u32l;
    func_801E4C60(rdram, ctx);
        goto after_1;
    // 0x801E52B8: swc1        $f4, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->f4.u32l;
    after_1:
    // 0x801E52BC: lui         $t9, 0x104
    ctx->r25 = S32(0X104 << 16);
    // 0x801E52C0: lw          $t3, 0x4C($sp)
    ctx->r11 = MEM_W(ctx->r29, 0X4C);
    // 0x801E52C4: lw          $t4, 0x7C($sp)
    ctx->r12 = MEM_W(ctx->r29, 0X7C);
    // 0x801E52C8: ori         $t9, $t9, 0x40
    ctx->r25 = ctx->r25 | 0X40;
    // 0x801E52CC: or          $t0, $s0, $zero
    ctx->r8 = ctx->r16 | 0;
    // 0x801E52D0: sw          $t9, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r25;
    // 0x801E52D4: lw          $t8, 0x48($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X48);
    // 0x801E52D8: lui         $at, 0x1FFF
    ctx->r1 = S32(0X1FFF << 16);
    // 0x801E52DC: ori         $at, $at, 0xFFFF
    ctx->r1 = ctx->r1 | 0XFFFF;
    // 0x801E52E0: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801E52E4: and         $t6, $t8, $at
    ctx->r14 = ctx->r24 & ctx->r1;
    // 0x801E52E8: sw          $t6, 0x4($t0)
    MEM_W(0X4, ctx->r8) = ctx->r14;
    // 0x801E52EC: or          $t1, $s0, $zero
    ctx->r9 = ctx->r16 | 0;
    // 0x801E52F0: lui         $t5, 0x600
    ctx->r13 = S32(0X600 << 16);
    // 0x801E52F4: sw          $t5, 0x0($t1)
    MEM_W(0X0, ctx->r9) = ctx->r13;
    // 0x801E52F8: lw          $t7, 0x4($t3)
    ctx->r15 = MEM_W(ctx->r11, 0X4);
    // 0x801E52FC: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801E5300: or          $t2, $s0, $zero
    ctx->r10 = ctx->r16 | 0;
    // 0x801E5304: sw          $t7, 0x4($t1)
    MEM_W(0X4, ctx->r9) = ctx->r15;
    // 0x801E5308: lui         $t9, 0xBD00
    ctx->r25 = S32(0XBD00 << 16);
    // 0x801E530C: sw          $t9, 0x0($t2)
    MEM_W(0X0, ctx->r10) = ctx->r25;
    // 0x801E5310: sw          $zero, 0x4($t2)
    MEM_W(0X4, ctx->r10) = 0;
    // 0x801E5314: lui         $t6, 0x8022
    ctx->r14 = S32(0X8022 << 16);
    // 0x801E5318: lw          $t6, 0x6C30($t6)
    ctx->r14 = MEM_W(ctx->r14, 0X6C30);
    // 0x801E531C: lw          $t8, 0x4C($t4)
    ctx->r24 = MEM_W(ctx->r12, 0X4C);
    // 0x801E5320: lw          $t9, 0x4($t4)
    ctx->r25 = MEM_W(ctx->r12, 0X4);
    // 0x801E5324: sll         $t5, $t6, 1
    ctx->r13 = S32(ctx->r14 << 1);
    // 0x801E5328: addu        $t7, $t8, $t5
    ctx->r15 = ADD32(ctx->r24, ctx->r13);
    // 0x801E532C: lh          $v1, 0x0($t7)
    ctx->r3 = MEM_H(ctx->r15, 0X0);
    // 0x801E5330: lw          $a0, 0x90($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X90);
    // 0x801E5334: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x801E5338: sll         $t6, $v1, 2
    ctx->r14 = S32(ctx->r3 << 2);
    // 0x801E533C: subu        $t6, $t6, $v1
    ctx->r14 = SUB32(ctx->r14, ctx->r3);
    // 0x801E5340: sll         $t6, $t6, 2
    ctx->r14 = S32(ctx->r14 << 2);
    // 0x801E5344: addu        $v0, $t9, $t6
    ctx->r2 = ADD32(ctx->r25, ctx->r14);
    // 0x801E5348: lb          $t9, 0x9($v0)
    ctx->r25 = MEM_B(ctx->r2, 0X9);
    // 0x801E534C: lb          $t8, 0x6($v0)
    ctx->r24 = MEM_B(ctx->r2, 0X6);
    // 0x801E5350: lb          $t5, 0x7($v0)
    ctx->r13 = MEM_B(ctx->r2, 0X7);
    // 0x801E5354: mtc1        $t9, $f18
    ctx->f18.u32l = ctx->r25;
    // 0x801E5358: mtc1        $t8, $f8
    ctx->f8.u32l = ctx->r24;
    // 0x801E535C: lb          $t7, 0x8($v0)
    ctx->r15 = MEM_B(ctx->r2, 0X8);
    // 0x801E5360: cvt.s.w     $f4, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    ctx->f4.fl = CVT_S_W(ctx->f18.u32l);
    // 0x801E5364: mtc1        $t5, $f10
    ctx->f10.u32l = ctx->r13;
    // 0x801E5368: mtc1        $t7, $f16
    ctx->f16.u32l = ctx->r15;
    // 0x801E536C: addiu       $a0, $a0, 0x80
    ctx->r4 = ADD32(ctx->r4, 0X80);
    // 0x801E5370: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801E5374: cvt.s.w     $f8, $f8
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 8);
    ctx->f8.fl = CVT_S_W(ctx->f8.u32l);
    // 0x801E5378: swc1        $f4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f4.u32l;
    // 0x801E537C: lb          $t6, 0xA($v0)
    ctx->r14 = MEM_B(ctx->r2, 0XA);
    // 0x801E5380: mtc1        $t6, $f6
    ctx->f6.u32l = ctx->r14;
    // 0x801E5384: mfc1        $a1, $f8
    ctx->r5 = (int32_t)ctx->f8.u32l;
    // 0x801E5388: cvt.s.w     $f10, $f10
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 10);
    ctx->f10.fl = CVT_S_W(ctx->f10.u32l);
    // 0x801E538C: cvt.s.w     $f8, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    ctx->f8.fl = CVT_S_W(ctx->f6.u32l);
    // 0x801E5390: mfc1        $a2, $f10
    ctx->r6 = (int32_t)ctx->f10.u32l;
    // 0x801E5394: cvt.s.w     $f16, $f16
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 16);
    ctx->f16.fl = CVT_S_W(ctx->f16.u32l);
    // 0x801E5398: swc1        $f8, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->f8.u32l;
    // 0x801E539C: lb          $t8, 0xB($v0)
    ctx->r24 = MEM_B(ctx->r2, 0XB);
    // 0x801E53A0: mtc1        $t8, $f10
    ctx->f10.u32l = ctx->r24;
    // 0x801E53A4: mfc1        $a3, $f16
    ctx->r7 = (int32_t)ctx->f16.u32l;
    // 0x801E53A8: cvt.s.w     $f16, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    ctx->f16.fl = CVT_S_W(ctx->f10.u32l);
    // 0x801E53AC: swc1        $f16, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->f16.u32l;
    // 0x801E53B0: lh          $t5, 0x0($v0)
    ctx->r13 = MEM_H(ctx->r2, 0X0);
    // 0x801E53B4: mtc1        $t5, $f18
    ctx->f18.u32l = ctx->r13;
    // 0x801E53B8: nop

    // 0x801E53BC: cvt.s.w     $f4, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    ctx->f4.fl = CVT_S_W(ctx->f18.u32l);
    // 0x801E53C0: mtc1        $at, $f18
    ctx->f18.u32l = ctx->r1;
    // 0x801E53C4: swc1        $f4, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->f4.u32l;
    // 0x801E53C8: lh          $t7, 0x2($v0)
    ctx->r15 = MEM_H(ctx->r2, 0X2);
    // 0x801E53CC: mtc1        $t7, $f6
    ctx->f6.u32l = ctx->r15;
    // 0x801E53D0: nop

    // 0x801E53D4: cvt.s.w     $f8, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    ctx->f8.fl = CVT_S_W(ctx->f6.u32l);
    // 0x801E53D8: swc1        $f8, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->f8.u32l;
    // 0x801E53DC: lh          $t9, 0x4($v0)
    ctx->r25 = MEM_H(ctx->r2, 0X4);
    // 0x801E53E0: sw          $a0, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r4;
    // 0x801E53E4: swc1        $f18, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->f18.u32l;
    // 0x801E53E8: mtc1        $t9, $f10
    ctx->f10.u32l = ctx->r25;
    // 0x801E53EC: nop

    // 0x801E53F0: cvt.s.w     $f16, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    ctx->f16.fl = CVT_S_W(ctx->f10.u32l);
    // 0x801E53F4: jal         0x801E4C60
    // 0x801E53F8: swc1        $f16, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->f16.u32l;
    func_801E4C60(rdram, ctx);
        goto after_2;
    // 0x801E53F8: swc1        $f16, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->f16.u32l;
    after_2:
    // 0x801E53FC: lui         $t6, 0x104
    ctx->r14 = S32(0X104 << 16);
    // 0x801E5400: lw          $t3, 0x4C($sp)
    ctx->r11 = MEM_W(ctx->r29, 0X4C);
    // 0x801E5404: ori         $t6, $t6, 0x40
    ctx->r14 = ctx->r14 | 0X40;
    // 0x801E5408: or          $v1, $s0, $zero
    ctx->r3 = ctx->r16 | 0;
    // 0x801E540C: sw          $t6, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r14;
    // 0x801E5410: lw          $t8, 0x44($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X44);
    // 0x801E5414: lui         $at, 0x1FFF
    ctx->r1 = S32(0X1FFF << 16);
    // 0x801E5418: ori         $at, $at, 0xFFFF
    ctx->r1 = ctx->r1 | 0XFFFF;
    // 0x801E541C: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801E5420: and         $t5, $t8, $at
    ctx->r13 = ctx->r24 & ctx->r1;
    // 0x801E5424: sw          $t5, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r13;
    // 0x801E5428: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x801E542C: lui         $t7, 0x600
    ctx->r15 = S32(0X600 << 16);
    // 0x801E5430: sw          $t7, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r15;
    // 0x801E5434: lw          $t9, 0x0($t3)
    ctx->r25 = MEM_W(ctx->r11, 0X0);
    // 0x801E5438: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801E543C: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    // 0x801E5440: sw          $t9, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r25;
    // 0x801E5444: lui         $t6, 0xBD00
    ctx->r14 = S32(0XBD00 << 16);
    // 0x801E5448: sw          $t6, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r14;
    // 0x801E544C: sw          $zero, 0x4($a1)
    MEM_W(0X4, ctx->r5) = 0;
    // 0x801E5450: lw          $ra, 0x3C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X3C);
    // 0x801E5454: addiu       $v0, $s0, 0x8
    ctx->r2 = ADD32(ctx->r16, 0X8);
    // 0x801E5458: lw          $s0, 0x38($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X38);
    // 0x801E545C: jr          $ra
    // 0x801E5460: addiu       $sp, $sp, 0x80
    ctx->r29 = ADD32(ctx->r29, 0X80);
    return;
    // 0x801E5460: addiu       $sp, $sp, 0x80
    ctx->r29 = ADD32(ctx->r29, 0X80);
    // 0x801E5464: nop

    // 0x801E5468: nop

    // 0x801E546C: nop

;}
RECOMP_FUNC void func_801E5470(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801E5470: addiu       $sp, $sp, -0x38
    ctx->r29 = ADD32(ctx->r29, -0X38);
    // 0x801E5474: sw          $s6, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r22;
    // 0x801E5478: sw          $s0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r16;
    // 0x801E547C: sw          $s5, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r21;
    // 0x801E5480: sw          $s4, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r20;
    // 0x801E5484: sw          $s3, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r19;
    // 0x801E5488: sw          $s2, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r18;
    // 0x801E548C: sw          $s1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r17;
    // 0x801E5490: lui         $s0, 0x8023
    ctx->r16 = S32(0X8023 << 16);
    // 0x801E5494: lui         $s6, 0x8023
    ctx->r22 = S32(0X8023 << 16);
    // 0x801E5498: sw          $ra, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r31;
    // 0x801E549C: addiu       $s6, $s6, -0x75F4
    ctx->r22 = ADD32(ctx->r22, -0X75F4);
    // 0x801E54A0: addiu       $s0, $s0, -0x76D0
    ctx->r16 = ADD32(ctx->r16, -0X76D0);
    // 0x801E54A4: addiu       $s1, $zero, 0x1
    ctx->r17 = ADD32(0, 0X1);
    // 0x801E54A8: addiu       $s2, $zero, 0x1
    ctx->r18 = ADD32(0, 0X1);
    // 0x801E54AC: addiu       $s3, $zero, 0x2
    ctx->r19 = ADD32(0, 0X2);
    // 0x801E54B0: addiu       $s4, $zero, 0x3
    ctx->r20 = ADD32(0, 0X3);
    // 0x801E54B4: addiu       $s5, $zero, 0x4
    ctx->r21 = ADD32(0, 0X4);
    // 0x801E54B8: lhu         $v0, 0x0($s0)
    ctx->r2 = MEM_HU(ctx->r16, 0X0);
L_801E54BC:
    // 0x801E54BC: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x801E54C0: beq         $v0, $s2, L_801E54E8
    if (ctx->r2 == ctx->r18) {
        // 0x801E54C4: nop
    
            goto L_801E54E8;
    }
    // 0x801E54C4: nop

    // 0x801E54C8: beq         $v0, $s3, L_801E54F8
    if (ctx->r2 == ctx->r19) {
        // 0x801E54CC: or          $a0, $s0, $zero
        ctx->r4 = ctx->r16 | 0;
            goto L_801E54F8;
    }
    // 0x801E54CC: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x801E54D0: beq         $v0, $s4, L_801E5508
    if (ctx->r2 == ctx->r20) {
        // 0x801E54D4: or          $a0, $s0, $zero
        ctx->r4 = ctx->r16 | 0;
            goto L_801E5508;
    }
    // 0x801E54D4: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x801E54D8: beq         $v0, $s5, L_801E5518
    if (ctx->r2 == ctx->r21) {
        // 0x801E54DC: or          $a0, $s0, $zero
        ctx->r4 = ctx->r16 | 0;
            goto L_801E5518;
    }
    // 0x801E54DC: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x801E54E0: b           L_801E5524
    // 0x801E54E4: addiu       $s0, $s0, 0x2C
    ctx->r16 = ADD32(ctx->r16, 0X2C);
        goto L_801E5524;
    // 0x801E54E4: addiu       $s0, $s0, 0x2C
    ctx->r16 = ADD32(ctx->r16, 0X2C);
L_801E54E8:
    // 0x801E54E8: jal         0x801E6074
    // 0x801E54EC: sh          $s1, 0x6($s0)
    MEM_H(0X6, ctx->r16) = ctx->r17;
    func_801E6074(rdram, ctx);
        goto after_0;
    // 0x801E54EC: sh          $s1, 0x6($s0)
    MEM_H(0X6, ctx->r16) = ctx->r17;
    after_0:
    // 0x801E54F0: b           L_801E5524
    // 0x801E54F4: addiu       $s0, $s0, 0x2C
    ctx->r16 = ADD32(ctx->r16, 0X2C);
        goto L_801E5524;
    // 0x801E54F4: addiu       $s0, $s0, 0x2C
    ctx->r16 = ADD32(ctx->r16, 0X2C);
L_801E54F8:
    // 0x801E54F8: jal         0x801E62A8
    // 0x801E54FC: sh          $s1, 0x6($s0)
    MEM_H(0X6, ctx->r16) = ctx->r17;
    func_801E62A8(rdram, ctx);
        goto after_1;
    // 0x801E54FC: sh          $s1, 0x6($s0)
    MEM_H(0X6, ctx->r16) = ctx->r17;
    after_1:
    // 0x801E5500: b           L_801E5524
    // 0x801E5504: addiu       $s0, $s0, 0x2C
    ctx->r16 = ADD32(ctx->r16, 0X2C);
        goto L_801E5524;
    // 0x801E5504: addiu       $s0, $s0, 0x2C
    ctx->r16 = ADD32(ctx->r16, 0X2C);
L_801E5508:
    // 0x801E5508: jal         0x801E66F4
    // 0x801E550C: sh          $s1, 0x6($s0)
    MEM_H(0X6, ctx->r16) = ctx->r17;
    func_801E66F4(rdram, ctx);
        goto after_2;
    // 0x801E550C: sh          $s1, 0x6($s0)
    MEM_H(0X6, ctx->r16) = ctx->r17;
    after_2:
    // 0x801E5510: b           L_801E5524
    // 0x801E5514: addiu       $s0, $s0, 0x2C
    ctx->r16 = ADD32(ctx->r16, 0X2C);
        goto L_801E5524;
    // 0x801E5514: addiu       $s0, $s0, 0x2C
    ctx->r16 = ADD32(ctx->r16, 0X2C);
L_801E5518:
    // 0x801E5518: jal         0x801E68EC
    // 0x801E551C: sh          $s1, 0x6($s0)
    MEM_H(0X6, ctx->r16) = ctx->r17;
    func_801E68EC(rdram, ctx);
        goto after_3;
    // 0x801E551C: sh          $s1, 0x6($s0)
    MEM_H(0X6, ctx->r16) = ctx->r17;
    after_3:
    // 0x801E5520: addiu       $s0, $s0, 0x2C
    ctx->r16 = ADD32(ctx->r16, 0X2C);
L_801E5524:
    // 0x801E5524: bnel        $s0, $s6, L_801E54BC
    if (ctx->r16 != ctx->r22) {
        // 0x801E5528: lhu         $v0, 0x0($s0)
        ctx->r2 = MEM_HU(ctx->r16, 0X0);
            goto L_801E54BC;
    }
    goto skip_0;
    // 0x801E5528: lhu         $v0, 0x0($s0)
    ctx->r2 = MEM_HU(ctx->r16, 0X0);
    skip_0:
    // 0x801E552C: lw          $ra, 0x34($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X34);
    // 0x801E5530: lw          $s0, 0x18($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X18);
    // 0x801E5534: lw          $s1, 0x1C($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X1C);
    // 0x801E5538: lw          $s2, 0x20($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X20);
    // 0x801E553C: lw          $s3, 0x24($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X24);
    // 0x801E5540: lw          $s4, 0x28($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X28);
    // 0x801E5544: lw          $s5, 0x2C($sp)
    ctx->r21 = MEM_W(ctx->r29, 0X2C);
    // 0x801E5548: lw          $s6, 0x30($sp)
    ctx->r22 = MEM_W(ctx->r29, 0X30);
    // 0x801E554C: jr          $ra
    // 0x801E5550: addiu       $sp, $sp, 0x38
    ctx->r29 = ADD32(ctx->r29, 0X38);
    return;
    // 0x801E5550: addiu       $sp, $sp, 0x38
    ctx->r29 = ADD32(ctx->r29, 0X38);
;}
RECOMP_FUNC void func_801E5554(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801E5554: addiu       $sp, $sp, -0x1B0
    ctx->r29 = ADD32(ctx->r29, -0X1B0);
    // 0x801E5558: sw          $fp, 0x78($sp)
    MEM_W(0X78, ctx->r29) = ctx->r30;
    // 0x801E555C: sw          $s4, 0x68($sp)
    MEM_W(0X68, ctx->r29) = ctx->r20;
    // 0x801E5560: sw          $s3, 0x64($sp)
    MEM_W(0X64, ctx->r29) = ctx->r19;
    // 0x801E5564: sw          $s0, 0x58($sp)
    MEM_W(0X58, ctx->r29) = ctx->r16;
    // 0x801E5568: sdc1        $f20, 0x50($sp)
    CHECK_FR(ctx, 20);
    SD(ctx->f20.u64, 0X50, ctx->r29);
    // 0x801E556C: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x801E5570: or          $s0, $a0, $zero
    ctx->r16 = ctx->r4 | 0;
    // 0x801E5574: sw          $ra, 0x7C($sp)
    MEM_W(0X7C, ctx->r29) = ctx->r31;
    // 0x801E5578: sw          $s7, 0x74($sp)
    MEM_W(0X74, ctx->r29) = ctx->r23;
    // 0x801E557C: sw          $s6, 0x70($sp)
    MEM_W(0X70, ctx->r29) = ctx->r22;
    // 0x801E5580: sw          $s5, 0x6C($sp)
    MEM_W(0X6C, ctx->r29) = ctx->r21;
    // 0x801E5584: lui         $s3, 0x8023
    ctx->r19 = S32(0X8023 << 16);
    // 0x801E5588: lui         $s4, 0x708
    ctx->r20 = S32(0X708 << 16);
    // 0x801E558C: lui         $fp, 0x8
    ctx->r30 = S32(0X8 << 16);
    // 0x801E5590: mtc1        $at, $f20
    ctx->f20.u32l = ctx->r1;
    // 0x801E5594: sw          $s2, 0x60($sp)
    MEM_W(0X60, ctx->r29) = ctx->r18;
    // 0x801E5598: sw          $s1, 0x5C($sp)
    MEM_W(0X5C, ctx->r29) = ctx->r17;
    // 0x801E559C: ori         $fp, $fp, 0x200
    ctx->r30 = ctx->r30 | 0X200;
    // 0x801E55A0: ori         $s4, $s4, 0x200
    ctx->r20 = ctx->r20 | 0X200;
    // 0x801E55A4: addiu       $s3, $s3, -0x76D0
    ctx->r19 = ADD32(ctx->r19, -0X76D0);
    // 0x801E55A8: lui         $s5, 0xE600
    ctx->r21 = S32(0XE600 << 16);
    // 0x801E55AC: lui         $s6, 0xF400
    ctx->r22 = S32(0XF400 << 16);
    // 0x801E55B0: lui         $s7, 0xE700
    ctx->r23 = S32(0XE700 << 16);
    // 0x801E55B4: lui         $ra, 0xE400
    ctx->r31 = S32(0XE400 << 16);
    // 0x801E55B8: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    // 0x801E55BC: lui         $t5, 0xF200
    ctx->r13 = S32(0XF200 << 16);
    // 0x801E55C0: lhu         $t6, 0x6($s3)
    ctx->r14 = MEM_HU(ctx->r19, 0X6);
L_801E55C4:
    // 0x801E55C4: beq         $t6, $zero, L_801E6028
    if (ctx->r14 == 0) {
        // 0x801E55C8: nop
    
            goto L_801E6028;
    }
    // 0x801E55C8: nop

    // 0x801E55CC: lhu         $v1, 0x0($s3)
    ctx->r3 = MEM_HU(ctx->r19, 0X0);
    // 0x801E55D0: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x801E55D4: or          $s2, $zero, $zero
    ctx->r18 = 0 | 0;
    // 0x801E55D8: beq         $v1, $a0, L_801E5604
    if (ctx->r3 == ctx->r4) {
        // 0x801E55DC: or          $s1, $zero, $zero
        ctx->r17 = 0 | 0;
            goto L_801E5604;
    }
    // 0x801E55DC: or          $s1, $zero, $zero
    ctx->r17 = 0 | 0;
    // 0x801E55E0: beq         $v1, $at, L_801E5874
    if (ctx->r3 == ctx->r1) {
        // 0x801E55E4: addiu       $at, $zero, 0x3
        ctx->r1 = ADD32(0, 0X3);
            goto L_801E5874;
    }
    // 0x801E55E4: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x801E55E8: beq         $v1, $at, L_801E5D24
    if (ctx->r3 == ctx->r1) {
        // 0x801E55EC: lui         $a2, 0x700
        ctx->r6 = S32(0X700 << 16);
            goto L_801E5D24;
    }
    // 0x801E55EC: lui         $a2, 0x700
    ctx->r6 = S32(0X700 << 16);
    // 0x801E55F0: addiu       $at, $zero, 0x4
    ctx->r1 = ADD32(0, 0X4);
    // 0x801E55F4: beq         $v1, $at, L_801E5DA4
    if (ctx->r3 == ctx->r1) {
        // 0x801E55F8: or          $v0, $s0, $zero
        ctx->r2 = ctx->r16 | 0;
            goto L_801E5DA4;
    }
    // 0x801E55F8: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
    // 0x801E55FC: b           L_801E6028
    // 0x801E5600: nop

        goto L_801E6028;
    // 0x801E5600: nop

L_801E5604:
    // 0x801E5604: lhu         $t7, 0x2($s3)
    ctx->r15 = MEM_HU(ctx->r19, 0X2);
    // 0x801E5608: lui         $a2, 0x700
    ctx->r6 = S32(0X700 << 16);
    // 0x801E560C: addiu       $a2, $a2, 0x0
    ctx->r6 = ADD32(ctx->r6, 0X0);
    // 0x801E5610: bne         $a0, $t7, L_801E5638
    if (ctx->r4 != ctx->r15) {
        // 0x801E5614: or          $v0, $s0, $zero
        ctx->r2 = ctx->r16 | 0;
            goto L_801E5638;
    }
    // 0x801E5614: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
    // 0x801E5618: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
    // 0x801E561C: lui         $t9, 0x107
    ctx->r25 = S32(0X107 << 16);
    // 0x801E5620: addiu       $t9, $t9, -0xFD0
    ctx->r25 = ADD32(ctx->r25, -0XFD0);
    // 0x801E5624: lui         $t8, 0x600
    ctx->r24 = S32(0X600 << 16);
    // 0x801E5628: sw          $t8, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r24;
    // 0x801E562C: sw          $t9, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r25;
    // 0x801E5630: b           L_801E56B0
    // 0x801E5634: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
        goto L_801E56B0;
    // 0x801E5634: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
L_801E5638:
    // 0x801E5638: lui         $t7, 0x107
    ctx->r15 = S32(0X107 << 16);
    // 0x801E563C: addiu       $t7, $t7, -0xF58
    ctx->r15 = ADD32(ctx->r15, -0XF58);
    // 0x801E5640: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801E5644: lui         $t6, 0x600
    ctx->r14 = S32(0X600 << 16);
    // 0x801E5648: sw          $t6, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r14;
    // 0x801E564C: sw          $t7, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r15;
    // 0x801E5650: or          $v1, $s0, $zero
    ctx->r3 = ctx->r16 | 0;
    // 0x801E5654: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801E5658: lui         $t8, 0xFCFF
    ctx->r24 = S32(0XFCFF << 16);
    // 0x801E565C: lui         $t9, 0xFFFC
    ctx->r25 = S32(0XFFFC << 16);
    // 0x801E5660: ori         $t9, $t9, 0xF279
    ctx->r25 = ctx->r25 | 0XF279;
    // 0x801E5664: ori         $t8, $t8, 0xFFFF
    ctx->r24 = ctx->r24 | 0XFFFF;
    // 0x801E5668: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x801E566C: sw          $t8, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r24;
    // 0x801E5670: sw          $t9, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r25;
    // 0x801E5674: lui         $t6, 0x103
    ctx->r14 = S32(0X103 << 16);
    // 0x801E5678: ori         $t6, $t6, 0x40
    ctx->r14 = ctx->r14 | 0X40;
    // 0x801E567C: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801E5680: lui         $t7, 0x102
    ctx->r15 = S32(0X102 << 16);
    // 0x801E5684: sw          $t6, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r14;
    // 0x801E5688: sw          $a2, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r6;
    // 0x801E568C: ori         $t7, $t7, 0x40
    ctx->r15 = ctx->r15 | 0X40;
    // 0x801E5690: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    // 0x801E5694: sw          $t7, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r15;
    // 0x801E5698: lhu         $t8, 0x4($s3)
    ctx->r24 = MEM_HU(ctx->r19, 0X4);
    // 0x801E569C: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801E56A0: sll         $t9, $t8, 6
    ctx->r25 = S32(ctx->r24 << 6);
    // 0x801E56A4: addu        $t6, $a2, $t9
    ctx->r14 = ADD32(ctx->r6, ctx->r25);
    // 0x801E56A8: addiu       $t7, $t6, 0x900
    ctx->r15 = ADD32(ctx->r14, 0X900);
    // 0x801E56AC: sw          $t7, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r15;
L_801E56B0:
    // 0x801E56B0: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
    // 0x801E56B4: lui         $t8, 0xFD18
    ctx->r24 = S32(0XFD18 << 16);
    // 0x801E56B8: lui         $t6, 0x804
    ctx->r14 = S32(0X804 << 16);
    // 0x801E56BC: addiu       $t6, $t6, 0x2008
    ctx->r14 = ADD32(ctx->r14, 0X2008);
    // 0x801E56C0: ori         $t8, $t8, 0x9F
    ctx->r24 = ctx->r24 | 0X9F;
    // 0x801E56C4: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801E56C8: sll         $t9, $s2, 2
    ctx->r25 = S32(ctx->r18 << 2);
    // 0x801E56CC: addu        $t7, $t9, $t6
    ctx->r15 = ADD32(ctx->r25, ctx->r14);
    // 0x801E56D0: or          $v1, $s0, $zero
    ctx->r3 = ctx->r16 | 0;
    // 0x801E56D4: sw          $t8, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r24;
    // 0x801E56D8: lui         $t8, 0xF518
    ctx->r24 = S32(0XF518 << 16);
    // 0x801E56DC: sw          $t7, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r15;
    // 0x801E56E0: ori         $t8, $t8, 0x5000
    ctx->r24 = ctx->r24 | 0X5000;
    // 0x801E56E4: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801E56E8: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x801E56EC: sw          $t8, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r24;
    // 0x801E56F0: sw          $s4, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r20;
    // 0x801E56F4: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801E56F8: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    // 0x801E56FC: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801E5700: sw          $zero, 0x4($a0)
    MEM_W(0X4, ctx->r4) = 0;
    // 0x801E5704: sw          $s5, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r21;
    // 0x801E5708: lui         $t9, 0x727
    ctx->r25 = S32(0X727 << 16);
    // 0x801E570C: ori         $t9, $t9, 0xC010
    ctx->r25 = ctx->r25 | 0XC010;
    // 0x801E5710: or          $a2, $s0, $zero
    ctx->r6 = ctx->r16 | 0;
    // 0x801E5714: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801E5718: sw          $t9, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r25;
    // 0x801E571C: sw          $s6, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r22;
    // 0x801E5720: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
    // 0x801E5724: sw          $zero, 0x4($a2)
    MEM_W(0X4, ctx->r6) = 0;
    // 0x801E5728: sw          $s7, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r23;
    // 0x801E572C: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801E5730: or          $v1, $s0, $zero
    ctx->r3 = ctx->r16 | 0;
    // 0x801E5734: sw          $fp, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r30;
    // 0x801E5738: sw          $t8, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r24;
    // 0x801E573C: lui         $t7, 0x27
    ctx->r15 = S32(0X27 << 16);
    // 0x801E5740: ori         $t7, $t7, 0xC010
    ctx->r15 = ctx->r15 | 0XC010;
    // 0x801E5744: sw          $t7, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r15;
    // 0x801E5748: sw          $t5, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r13;
    // 0x801E574C: lhu         $t8, 0x2($s3)
    ctx->r24 = MEM_HU(ctx->r19, 0X2);
    // 0x801E5750: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801E5754: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x801E5758: bne         $t8, $at, L_801E57F8
    if (ctx->r24 != ctx->r1) {
        // 0x801E575C: or          $a0, $s0, $zero
        ctx->r4 = ctx->r16 | 0;
            goto L_801E57F8;
    }
    // 0x801E575C: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x801E5760: lw          $t9, 0x8($s3)
    ctx->r25 = MEM_W(ctx->r19, 0X8);
    // 0x801E5764: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
    // 0x801E5768: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801E576C: addiu       $t6, $t9, 0xA0
    ctx->r14 = ADD32(ctx->r25, 0XA0);
    // 0x801E5770: sll         $t7, $t6, 2
    ctx->r15 = S32(ctx->r14 << 2);
    // 0x801E5774: andi        $t8, $t7, 0xFFF
    ctx->r24 = ctx->r15 & 0XFFF;
    // 0x801E5778: lw          $t7, 0xC($s3)
    ctx->r15 = MEM_W(ctx->r19, 0XC);
    // 0x801E577C: sll         $t9, $t8, 12
    ctx->r25 = S32(ctx->r24 << 12);
    // 0x801E5780: or          $t6, $t9, $ra
    ctx->r14 = ctx->r25 | ctx->r31;
    // 0x801E5784: addu        $t8, $t7, $s1
    ctx->r24 = ADD32(ctx->r15, ctx->r17);
    // 0x801E5788: addiu       $t9, $t8, 0x5
    ctx->r25 = ADD32(ctx->r24, 0X5);
    // 0x801E578C: sll         $t7, $t9, 2
    ctx->r15 = S32(ctx->r25 << 2);
    // 0x801E5790: andi        $t8, $t7, 0xFFF
    ctx->r24 = ctx->r15 & 0XFFF;
    // 0x801E5794: or          $t9, $t6, $t8
    ctx->r25 = ctx->r14 | ctx->r24;
    // 0x801E5798: sw          $t9, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r25;
    // 0x801E579C: lw          $t7, 0x8($s3)
    ctx->r15 = MEM_W(ctx->r19, 0X8);
    // 0x801E57A0: or          $v1, $s0, $zero
    ctx->r3 = ctx->r16 | 0;
    // 0x801E57A4: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801E57A8: sll         $t6, $t7, 2
    ctx->r14 = S32(ctx->r15 << 2);
    // 0x801E57AC: lw          $t7, 0xC($s3)
    ctx->r15 = MEM_W(ctx->r19, 0XC);
    // 0x801E57B0: andi        $t8, $t6, 0xFFF
    ctx->r24 = ctx->r14 & 0XFFF;
    // 0x801E57B4: sll         $t9, $t8, 12
    ctx->r25 = S32(ctx->r24 << 12);
    // 0x801E57B8: addu        $t6, $t7, $s1
    ctx->r14 = ADD32(ctx->r15, ctx->r17);
    // 0x801E57BC: sll         $t8, $t6, 2
    ctx->r24 = S32(ctx->r14 << 2);
    // 0x801E57C0: andi        $t7, $t8, 0xFFF
    ctx->r15 = ctx->r24 & 0XFFF;
    // 0x801E57C4: or          $t6, $t9, $t7
    ctx->r14 = ctx->r25 | ctx->r15;
    // 0x801E57C8: sw          $t6, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r14;
    // 0x801E57CC: lui         $t7, 0x400
    ctx->r15 = S32(0X400 << 16);
    // 0x801E57D0: lui         $t8, 0xB300
    ctx->r24 = S32(0XB300 << 16);
    // 0x801E57D4: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x801E57D8: sw          $t8, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r24;
    // 0x801E57DC: ori         $t7, $t7, 0x400
    ctx->r15 = ctx->r15 | 0X400;
    // 0x801E57E0: sw          $zero, 0x4($v1)
    MEM_W(0X4, ctx->r3) = 0;
    // 0x801E57E4: lui         $t9, 0xB200
    ctx->r25 = S32(0XB200 << 16);
    // 0x801E57E8: sw          $t9, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r25;
    // 0x801E57EC: sw          $t7, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r15;
    // 0x801E57F0: b           L_801E585C
    // 0x801E57F4: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
        goto L_801E585C;
    // 0x801E57F4: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
L_801E57F8:
    // 0x801E57F8: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x801E57FC: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x801E5800: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x801E5804: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x801E5808: sw          $t7, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r15;
    // 0x801E580C: sw          $t7, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r15;
    // 0x801E5810: sw          $t7, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r15;
    // 0x801E5814: sw          $t9, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r25;
    // 0x801E5818: sw          $t9, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r25;
    // 0x801E581C: sw          $t9, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r25;
    // 0x801E5820: sw          $t8, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r24;
    // 0x801E5824: sw          $t8, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r24;
    // 0x801E5828: sw          $t8, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r24;
    // 0x801E582C: sw          $t6, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r14;
    // 0x801E5830: sw          $t6, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r14;
    // 0x801E5834: sw          $t6, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r14;
    // 0x801E5838: addiu       $a1, $zero, 0xA0
    ctx->r5 = ADD32(0, 0XA0);
    // 0x801E583C: addiu       $a2, $zero, 0x6
    ctx->r6 = ADD32(0, 0X6);
    // 0x801E5840: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    // 0x801E5844: sw          $s1, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r17;
    // 0x801E5848: jal         0x801E8800
    // 0x801E584C: swc1        $f20, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->f20.u32l;
    func_801E8800(rdram, ctx);
        goto after_0;
    // 0x801E584C: swc1        $f20, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->f20.u32l;
    after_0:
    // 0x801E5850: lui         $t5, 0xF200
    ctx->r13 = S32(0XF200 << 16);
    // 0x801E5854: lui         $ra, 0xE400
    ctx->r31 = S32(0XE400 << 16);
    // 0x801E5858: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
L_801E585C:
    // 0x801E585C: addiu       $s1, $s1, 0x5
    ctx->r17 = ADD32(ctx->r17, 0X5);
    // 0x801E5860: addiu       $at, $zero, 0x28
    ctx->r1 = ADD32(0, 0X28);
    // 0x801E5864: bne         $s1, $at, L_801E56B0
    if (ctx->r17 != ctx->r1) {
        // 0x801E5868: addiu       $s2, $s2, 0x320
        ctx->r18 = ADD32(ctx->r18, 0X320);
            goto L_801E56B0;
    }
    // 0x801E5868: addiu       $s2, $s2, 0x320
    ctx->r18 = ADD32(ctx->r18, 0X320);
    // 0x801E586C: b           L_801E6028
    // 0x801E5870: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
        goto L_801E6028;
    // 0x801E5870: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
L_801E5874:
    // 0x801E5874: lhu         $t6, 0x2($s3)
    ctx->r14 = MEM_HU(ctx->r19, 0X2);
    // 0x801E5878: lui         $a2, 0x700
    ctx->r6 = S32(0X700 << 16);
    // 0x801E587C: addiu       $a2, $a2, 0x0
    ctx->r6 = ADD32(ctx->r6, 0X0);
    // 0x801E5880: bne         $a0, $t6, L_801E58A8
    if (ctx->r4 != ctx->r14) {
        // 0x801E5884: or          $v0, $s0, $zero
        ctx->r2 = ctx->r16 | 0;
            goto L_801E58A8;
    }
    // 0x801E5884: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
    // 0x801E5888: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
    // 0x801E588C: lui         $t9, 0x107
    ctx->r25 = S32(0X107 << 16);
    // 0x801E5890: addiu       $t9, $t9, -0xFD0
    ctx->r25 = ADD32(ctx->r25, -0XFD0);
    // 0x801E5894: lui         $t8, 0x600
    ctx->r24 = S32(0X600 << 16);
    // 0x801E5898: sw          $t8, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r24;
    // 0x801E589C: sw          $t9, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r25;
    // 0x801E58A0: b           L_801E5920
    // 0x801E58A4: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
        goto L_801E5920;
    // 0x801E58A4: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
L_801E58A8:
    // 0x801E58A8: lui         $t6, 0x107
    ctx->r14 = S32(0X107 << 16);
    // 0x801E58AC: addiu       $t6, $t6, -0xF58
    ctx->r14 = ADD32(ctx->r14, -0XF58);
    // 0x801E58B0: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801E58B4: lui         $t7, 0x600
    ctx->r15 = S32(0X600 << 16);
    // 0x801E58B8: sw          $t7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r15;
    // 0x801E58BC: sw          $t6, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r14;
    // 0x801E58C0: or          $v1, $s0, $zero
    ctx->r3 = ctx->r16 | 0;
    // 0x801E58C4: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801E58C8: lui         $t8, 0xFCFF
    ctx->r24 = S32(0XFCFF << 16);
    // 0x801E58CC: lui         $t9, 0xFFFC
    ctx->r25 = S32(0XFFFC << 16);
    // 0x801E58D0: ori         $t9, $t9, 0xF279
    ctx->r25 = ctx->r25 | 0XF279;
    // 0x801E58D4: ori         $t8, $t8, 0xFFFF
    ctx->r24 = ctx->r24 | 0XFFFF;
    // 0x801E58D8: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x801E58DC: sw          $t8, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r24;
    // 0x801E58E0: sw          $t9, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r25;
    // 0x801E58E4: lui         $t7, 0x103
    ctx->r15 = S32(0X103 << 16);
    // 0x801E58E8: ori         $t7, $t7, 0x40
    ctx->r15 = ctx->r15 | 0X40;
    // 0x801E58EC: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801E58F0: lui         $t6, 0x102
    ctx->r14 = S32(0X102 << 16);
    // 0x801E58F4: sw          $t7, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r15;
    // 0x801E58F8: sw          $a2, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r6;
    // 0x801E58FC: ori         $t6, $t6, 0x40
    ctx->r14 = ctx->r14 | 0X40;
    // 0x801E5900: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    // 0x801E5904: sw          $t6, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r14;
    // 0x801E5908: lhu         $t8, 0x4($s3)
    ctx->r24 = MEM_HU(ctx->r19, 0X4);
    // 0x801E590C: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801E5910: sll         $t9, $t8, 6
    ctx->r25 = S32(ctx->r24 << 6);
    // 0x801E5914: addu        $t7, $a2, $t9
    ctx->r15 = ADD32(ctx->r6, ctx->r25);
    // 0x801E5918: addiu       $t6, $t7, 0x900
    ctx->r14 = ADD32(ctx->r15, 0X900);
    // 0x801E591C: sw          $t6, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r14;
L_801E5920:
    // 0x801E5920: lw          $t8, 0x28($s3)
    ctx->r24 = MEM_W(ctx->r19, 0X28);
    // 0x801E5924: or          $s2, $zero, $zero
    ctx->r18 = 0 | 0;
    // 0x801E5928: or          $s1, $zero, $zero
    ctx->r17 = 0 | 0;
    // 0x801E592C: beq         $t8, $zero, L_801E5B10
    if (ctx->r24 == 0) {
        // 0x801E5930: nop
    
            goto L_801E5B10;
    }
    // 0x801E5930: nop

    // 0x801E5934: or          $s1, $zero, $zero
    ctx->r17 = 0 | 0;
    // 0x801E5938: or          $s2, $zero, $zero
    ctx->r18 = 0 | 0;
L_801E593C:
    // 0x801E593C: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
    // 0x801E5940: lui         $t9, 0xFD18
    ctx->r25 = S32(0XFD18 << 16);
    // 0x801E5944: lui         $t6, 0x805
    ctx->r14 = S32(0X805 << 16);
    // 0x801E5948: addiu       $t6, $t6, -0x6FF8
    ctx->r14 = ADD32(ctx->r14, -0X6FF8);
    // 0x801E594C: ori         $t9, $t9, 0xCB
    ctx->r25 = ctx->r25 | 0XCB;
    // 0x801E5950: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801E5954: sll         $t7, $s2, 2
    ctx->r15 = S32(ctx->r18 << 2);
    // 0x801E5958: addu        $t8, $t7, $t6
    ctx->r24 = ADD32(ctx->r15, ctx->r14);
    // 0x801E595C: or          $v1, $s0, $zero
    ctx->r3 = ctx->r16 | 0;
    // 0x801E5960: sw          $t9, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r25;
    // 0x801E5964: lui         $t9, 0xF518
    ctx->r25 = S32(0XF518 << 16);
    // 0x801E5968: sw          $t8, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r24;
    // 0x801E596C: ori         $t9, $t9, 0x6600
    ctx->r25 = ctx->r25 | 0X6600;
    // 0x801E5970: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801E5974: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x801E5978: sw          $t9, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r25;
    // 0x801E597C: sw          $s4, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r20;
    // 0x801E5980: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801E5984: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    // 0x801E5988: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801E598C: sw          $zero, 0x4($a0)
    MEM_W(0X4, ctx->r4) = 0;
    // 0x801E5990: sw          $s5, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r21;
    // 0x801E5994: lui         $t7, 0x732
    ctx->r15 = S32(0X732 << 16);
    // 0x801E5998: ori         $t7, $t7, 0xC010
    ctx->r15 = ctx->r15 | 0XC010;
    // 0x801E599C: or          $a2, $s0, $zero
    ctx->r6 = ctx->r16 | 0;
    // 0x801E59A0: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801E59A4: sw          $t7, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r15;
    // 0x801E59A8: sw          $s6, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r22;
    // 0x801E59AC: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
    // 0x801E59B0: sw          $zero, 0x4($a2)
    MEM_W(0X4, ctx->r6) = 0;
    // 0x801E59B4: sw          $s7, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r23;
    // 0x801E59B8: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801E59BC: or          $v1, $s0, $zero
    ctx->r3 = ctx->r16 | 0;
    // 0x801E59C0: sw          $fp, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r30;
    // 0x801E59C4: sw          $t9, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r25;
    // 0x801E59C8: lui         $t8, 0x32
    ctx->r24 = S32(0X32 << 16);
    // 0x801E59CC: ori         $t8, $t8, 0xC010
    ctx->r24 = ctx->r24 | 0XC010;
    // 0x801E59D0: sw          $t8, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r24;
    // 0x801E59D4: sw          $t5, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r13;
    // 0x801E59D8: lhu         $t9, 0x2($s3)
    ctx->r25 = MEM_HU(ctx->r19, 0X2);
    // 0x801E59DC: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801E59E0: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x801E59E4: bne         $t9, $at, L_801E5A84
    if (ctx->r25 != ctx->r1) {
        // 0x801E59E8: or          $a0, $s0, $zero
        ctx->r4 = ctx->r16 | 0;
            goto L_801E5A84;
    }
    // 0x801E59E8: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x801E59EC: lw          $t7, 0x8($s3)
    ctx->r15 = MEM_W(ctx->r19, 0X8);
    // 0x801E59F0: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
    // 0x801E59F4: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801E59F8: addiu       $t6, $t7, 0xCC
    ctx->r14 = ADD32(ctx->r15, 0XCC);
    // 0x801E59FC: sll         $t8, $t6, 2
    ctx->r24 = S32(ctx->r14 << 2);
    // 0x801E5A00: andi        $t9, $t8, 0xFFF
    ctx->r25 = ctx->r24 & 0XFFF;
    // 0x801E5A04: lw          $t8, 0xC($s3)
    ctx->r24 = MEM_W(ctx->r19, 0XC);
    // 0x801E5A08: sll         $t7, $t9, 12
    ctx->r15 = S32(ctx->r25 << 12);
    // 0x801E5A0C: or          $t6, $t7, $ra
    ctx->r14 = ctx->r15 | ctx->r31;
    // 0x801E5A10: addu        $t9, $t8, $s1
    ctx->r25 = ADD32(ctx->r24, ctx->r17);
    // 0x801E5A14: addiu       $t7, $t9, 0x5
    ctx->r15 = ADD32(ctx->r25, 0X5);
    // 0x801E5A18: sll         $t8, $t7, 2
    ctx->r24 = S32(ctx->r15 << 2);
    // 0x801E5A1C: andi        $t9, $t8, 0xFFF
    ctx->r25 = ctx->r24 & 0XFFF;
    // 0x801E5A20: or          $t7, $t6, $t9
    ctx->r15 = ctx->r14 | ctx->r25;
    // 0x801E5A24: sw          $t7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r15;
    // 0x801E5A28: lw          $t8, 0x8($s3)
    ctx->r24 = MEM_W(ctx->r19, 0X8);
    // 0x801E5A2C: or          $v1, $s0, $zero
    ctx->r3 = ctx->r16 | 0;
    // 0x801E5A30: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801E5A34: sll         $t6, $t8, 2
    ctx->r14 = S32(ctx->r24 << 2);
    // 0x801E5A38: lw          $t8, 0xC($s3)
    ctx->r24 = MEM_W(ctx->r19, 0XC);
    // 0x801E5A3C: andi        $t9, $t6, 0xFFF
    ctx->r25 = ctx->r14 & 0XFFF;
    // 0x801E5A40: sll         $t7, $t9, 12
    ctx->r15 = S32(ctx->r25 << 12);
    // 0x801E5A44: addu        $t6, $t8, $s1
    ctx->r14 = ADD32(ctx->r24, ctx->r17);
    // 0x801E5A48: sll         $t9, $t6, 2
    ctx->r25 = S32(ctx->r14 << 2);
    // 0x801E5A4C: andi        $t8, $t9, 0xFFF
    ctx->r24 = ctx->r25 & 0XFFF;
    // 0x801E5A50: or          $t6, $t7, $t8
    ctx->r14 = ctx->r15 | ctx->r24;
    // 0x801E5A54: sw          $t6, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r14;
    // 0x801E5A58: lui         $t8, 0x400
    ctx->r24 = S32(0X400 << 16);
    // 0x801E5A5C: lui         $t9, 0xB300
    ctx->r25 = S32(0XB300 << 16);
    // 0x801E5A60: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x801E5A64: sw          $t9, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r25;
    // 0x801E5A68: ori         $t8, $t8, 0x400
    ctx->r24 = ctx->r24 | 0X400;
    // 0x801E5A6C: sw          $zero, 0x4($v1)
    MEM_W(0X4, ctx->r3) = 0;
    // 0x801E5A70: lui         $t7, 0xB200
    ctx->r15 = S32(0XB200 << 16);
    // 0x801E5A74: sw          $t7, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r15;
    // 0x801E5A78: sw          $t8, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r24;
    // 0x801E5A7C: b           L_801E5AF8
    // 0x801E5A80: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
        goto L_801E5AF8;
    // 0x801E5A80: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
L_801E5A84:
    // 0x801E5A84: addiu       $at, $zero, 0x13EC
    ctx->r1 = ADD32(0, 0X13EC);
    // 0x801E5A88: bne         $s2, $at, L_801E5A98
    if (ctx->r18 != ctx->r1) {
        // 0x801E5A8C: addiu       $a1, $zero, 0xCC
        ctx->r5 = ADD32(0, 0XCC);
            goto L_801E5A98;
    }
    // 0x801E5A8C: addiu       $a1, $zero, 0xCC
    ctx->r5 = ADD32(0, 0XCC);
    // 0x801E5A90: b           L_801E5A9C
    // 0x801E5A94: addiu       $a2, $zero, 0x4
    ctx->r6 = ADD32(0, 0X4);
        goto L_801E5A9C;
    // 0x801E5A94: addiu       $a2, $zero, 0x4
    ctx->r6 = ADD32(0, 0X4);
L_801E5A98:
    // 0x801E5A98: addiu       $a2, $zero, 0x6
    ctx->r6 = ADD32(0, 0X6);
L_801E5A9C:
    // 0x801E5A9C: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x801E5AA0: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x801E5AA4: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x801E5AA8: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x801E5AAC: sw          $t8, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r24;
    // 0x801E5AB0: sw          $t8, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r24;
    // 0x801E5AB4: sw          $t8, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r24;
    // 0x801E5AB8: sw          $t7, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r15;
    // 0x801E5ABC: sw          $t7, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r15;
    // 0x801E5AC0: sw          $t7, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r15;
    // 0x801E5AC4: sw          $t9, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r25;
    // 0x801E5AC8: sw          $t9, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r25;
    // 0x801E5ACC: sw          $t9, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r25;
    // 0x801E5AD0: sw          $t6, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r14;
    // 0x801E5AD4: sw          $t6, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r14;
    // 0x801E5AD8: sw          $t6, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r14;
    // 0x801E5ADC: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    // 0x801E5AE0: sw          $s1, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r17;
    // 0x801E5AE4: jal         0x801E8800
    // 0x801E5AE8: swc1        $f20, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->f20.u32l;
    func_801E8800(rdram, ctx);
        goto after_1;
    // 0x801E5AE8: swc1        $f20, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->f20.u32l;
    after_1:
    // 0x801E5AEC: lui         $t5, 0xF200
    ctx->r13 = S32(0XF200 << 16);
    // 0x801E5AF0: lui         $ra, 0xE400
    ctx->r31 = S32(0XE400 << 16);
    // 0x801E5AF4: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
L_801E5AF8:
    // 0x801E5AF8: addiu       $s2, $s2, 0x3FC
    ctx->r18 = ADD32(ctx->r18, 0X3FC);
    // 0x801E5AFC: addiu       $at, $zero, 0x17E8
    ctx->r1 = ADD32(0, 0X17E8);
    // 0x801E5B00: bne         $s2, $at, L_801E593C
    if (ctx->r18 != ctx->r1) {
        // 0x801E5B04: addiu       $s1, $s1, 0x5
        ctx->r17 = ADD32(ctx->r17, 0X5);
            goto L_801E593C;
    }
    // 0x801E5B04: addiu       $s1, $s1, 0x5
    ctx->r17 = ADD32(ctx->r17, 0X5);
    // 0x801E5B08: b           L_801E6028
    // 0x801E5B0C: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
        goto L_801E6028;
    // 0x801E5B0C: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
L_801E5B10:
    // 0x801E5B10: lui         $t6, 0xFD18
    ctx->r14 = S32(0XFD18 << 16);
    // 0x801E5B14: ori         $t6, $t6, 0x4F
    ctx->r14 = ctx->r14 | 0X4F;
    // 0x801E5B18: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
    // 0x801E5B1C: sw          $t6, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r14;
    // 0x801E5B20: lui         $t9, 0x800D
    ctx->r25 = S32(0X800D << 16);
    // 0x801E5B24: lw          $t9, 0x48DC($t9)
    ctx->r25 = MEM_W(ctx->r25, 0X48DC);
    // 0x801E5B28: lui         $t8, 0x801C
    ctx->r24 = S32(0X801C << 16);
    // 0x801E5B2C: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801E5B30: sll         $t7, $t9, 3
    ctx->r15 = S32(ctx->r25 << 3);
    // 0x801E5B34: subu        $t7, $t7, $t9
    ctx->r15 = SUB32(ctx->r15, ctx->r25);
    // 0x801E5B38: sll         $t7, $t7, 4
    ctx->r15 = S32(ctx->r15 << 4);
    // 0x801E5B3C: subu        $t7, $t7, $t9
    ctx->r15 = SUB32(ctx->r15, ctx->r25);
    // 0x801E5B40: sll         $t7, $t7, 3
    ctx->r15 = S32(ctx->r15 << 3);
    // 0x801E5B44: addu        $t8, $t8, $t7
    ctx->r24 = ADD32(ctx->r24, ctx->r15);
    // 0x801E5B48: lw          $t8, 0x293C($t8)
    ctx->r24 = MEM_W(ctx->r24, 0X293C);
    // 0x801E5B4C: sll         $t7, $s2, 2
    ctx->r15 = S32(ctx->r18 << 2);
    // 0x801E5B50: or          $v1, $s0, $zero
    ctx->r3 = ctx->r16 | 0;
    // 0x801E5B54: sll         $t6, $t8, 2
    ctx->r14 = S32(ctx->r24 << 2);
    // 0x801E5B58: subu        $t6, $t6, $t8
    ctx->r14 = SUB32(ctx->r14, ctx->r24);
    // 0x801E5B5C: sll         $t6, $t6, 3
    ctx->r14 = S32(ctx->r14 << 3);
    // 0x801E5B60: addu        $t6, $t6, $t8
    ctx->r14 = ADD32(ctx->r14, ctx->r24);
    // 0x801E5B64: sll         $t9, $t6, 9
    ctx->r25 = S32(ctx->r14 << 9);
    // 0x801E5B68: lui         $t6, 0x805
    ctx->r14 = S32(0X805 << 16);
    // 0x801E5B6C: addiu       $t6, $t6, -0x6FF8
    ctx->r14 = ADD32(ctx->r14, -0X6FF8);
    // 0x801E5B70: addu        $t8, $t9, $t7
    ctx->r24 = ADD32(ctx->r25, ctx->r15);
    // 0x801E5B74: addu        $t9, $t8, $t6
    ctx->r25 = ADD32(ctx->r24, ctx->r14);
    // 0x801E5B78: sw          $t9, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r25;
    // 0x801E5B7C: lui         $t7, 0xF518
    ctx->r15 = S32(0XF518 << 16);
    // 0x801E5B80: ori         $t7, $t7, 0x2800
    ctx->r15 = ctx->r15 | 0X2800;
    // 0x801E5B84: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801E5B88: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x801E5B8C: sw          $t7, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r15;
    // 0x801E5B90: sw          $s4, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r20;
    // 0x801E5B94: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801E5B98: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    // 0x801E5B9C: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801E5BA0: sw          $zero, 0x4($a0)
    MEM_W(0X4, ctx->r4) = 0;
    // 0x801E5BA4: sw          $s5, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r21;
    // 0x801E5BA8: lui         $t8, 0x713
    ctx->r24 = S32(0X713 << 16);
    // 0x801E5BAC: ori         $t8, $t8, 0xC008
    ctx->r24 = ctx->r24 | 0XC008;
    // 0x801E5BB0: or          $a2, $s0, $zero
    ctx->r6 = ctx->r16 | 0;
    // 0x801E5BB4: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801E5BB8: sw          $t8, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r24;
    // 0x801E5BBC: sw          $s6, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r22;
    // 0x801E5BC0: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
    // 0x801E5BC4: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801E5BC8: sw          $zero, 0x4($a2)
    MEM_W(0X4, ctx->r6) = 0;
    // 0x801E5BCC: sw          $s7, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r23;
    // 0x801E5BD0: or          $v1, $s0, $zero
    ctx->r3 = ctx->r16 | 0;
    // 0x801E5BD4: lui         $t9, 0x13
    ctx->r25 = S32(0X13 << 16);
    // 0x801E5BD8: ori         $t9, $t9, 0xC008
    ctx->r25 = ctx->r25 | 0XC008;
    // 0x801E5BDC: sw          $fp, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r30;
    // 0x801E5BE0: sw          $t7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r15;
    // 0x801E5BE4: addiu       $at, $zero, 0x26
    ctx->r1 = ADD32(0, 0X26);
    // 0x801E5BE8: sw          $t9, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r25;
    // 0x801E5BEC: sw          $t5, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r13;
    // 0x801E5BF0: bne         $s1, $at, L_801E5C00
    if (ctx->r17 != ctx->r1) {
        // 0x801E5BF4: addiu       $s0, $s0, 0x8
        ctx->r16 = ADD32(ctx->r16, 0X8);
            goto L_801E5C00;
    }
    // 0x801E5BF4: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801E5BF8: b           L_801E5C04
    // 0x801E5BFC: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
        goto L_801E5C04;
    // 0x801E5BFC: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
L_801E5C00:
    // 0x801E5C00: addiu       $a2, $zero, 0x3
    ctx->r6 = ADD32(0, 0X3);
L_801E5C04:
    // 0x801E5C04: lhu         $t7, 0x2($s3)
    ctx->r15 = MEM_HU(ctx->r19, 0X2);
    // 0x801E5C08: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x801E5C0C: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x801E5C10: bne         $t7, $at, L_801E5CB0
    if (ctx->r15 != ctx->r1) {
        // 0x801E5C14: addiu       $a1, $zero, 0x50
        ctx->r5 = ADD32(0, 0X50);
            goto L_801E5CB0;
    }
    // 0x801E5C14: addiu       $a1, $zero, 0x50
    ctx->r5 = ADD32(0, 0X50);
    // 0x801E5C18: lw          $t8, 0x8($s3)
    ctx->r24 = MEM_W(ctx->r19, 0X8);
    // 0x801E5C1C: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
    // 0x801E5C20: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801E5C24: addiu       $t6, $t8, 0x50
    ctx->r14 = ADD32(ctx->r24, 0X50);
    // 0x801E5C28: sll         $t9, $t6, 2
    ctx->r25 = S32(ctx->r14 << 2);
    // 0x801E5C2C: andi        $t7, $t9, 0xFFF
    ctx->r15 = ctx->r25 & 0XFFF;
    // 0x801E5C30: lw          $t9, 0xC($s3)
    ctx->r25 = MEM_W(ctx->r19, 0XC);
    // 0x801E5C34: sll         $t8, $t7, 12
    ctx->r24 = S32(ctx->r15 << 12);
    // 0x801E5C38: or          $t6, $t8, $ra
    ctx->r14 = ctx->r24 | ctx->r31;
    // 0x801E5C3C: addu        $t7, $t9, $s1
    ctx->r15 = ADD32(ctx->r25, ctx->r17);
    // 0x801E5C40: addiu       $t8, $t7, 0x2
    ctx->r24 = ADD32(ctx->r15, 0X2);
    // 0x801E5C44: sll         $t9, $t8, 2
    ctx->r25 = S32(ctx->r24 << 2);
    // 0x801E5C48: andi        $t7, $t9, 0xFFF
    ctx->r15 = ctx->r25 & 0XFFF;
    // 0x801E5C4C: or          $t8, $t6, $t7
    ctx->r24 = ctx->r14 | ctx->r15;
    // 0x801E5C50: sw          $t8, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r24;
    // 0x801E5C54: lw          $t9, 0x8($s3)
    ctx->r25 = MEM_W(ctx->r19, 0X8);
    // 0x801E5C58: or          $v1, $s0, $zero
    ctx->r3 = ctx->r16 | 0;
    // 0x801E5C5C: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801E5C60: sll         $t6, $t9, 2
    ctx->r14 = S32(ctx->r25 << 2);
    // 0x801E5C64: lw          $t9, 0xC($s3)
    ctx->r25 = MEM_W(ctx->r19, 0XC);
    // 0x801E5C68: andi        $t7, $t6, 0xFFF
    ctx->r15 = ctx->r14 & 0XFFF;
    // 0x801E5C6C: sll         $t8, $t7, 12
    ctx->r24 = S32(ctx->r15 << 12);
    // 0x801E5C70: addu        $t6, $t9, $s1
    ctx->r14 = ADD32(ctx->r25, ctx->r17);
    // 0x801E5C74: sll         $t7, $t6, 2
    ctx->r15 = S32(ctx->r14 << 2);
    // 0x801E5C78: andi        $t9, $t7, 0xFFF
    ctx->r25 = ctx->r15 & 0XFFF;
    // 0x801E5C7C: or          $t6, $t8, $t9
    ctx->r14 = ctx->r24 | ctx->r25;
    // 0x801E5C80: sw          $t6, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r14;
    // 0x801E5C84: lui         $t9, 0x400
    ctx->r25 = S32(0X400 << 16);
    // 0x801E5C88: lui         $t7, 0xB300
    ctx->r15 = S32(0XB300 << 16);
    // 0x801E5C8C: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x801E5C90: sw          $t7, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r15;
    // 0x801E5C94: ori         $t9, $t9, 0x400
    ctx->r25 = ctx->r25 | 0X400;
    // 0x801E5C98: sw          $zero, 0x4($v1)
    MEM_W(0X4, ctx->r3) = 0;
    // 0x801E5C9C: lui         $t8, 0xB200
    ctx->r24 = S32(0XB200 << 16);
    // 0x801E5CA0: sw          $t8, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r24;
    // 0x801E5CA4: sw          $t9, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r25;
    // 0x801E5CA8: b           L_801E5D0C
    // 0x801E5CAC: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
        goto L_801E5D0C;
    // 0x801E5CAC: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
L_801E5CB0:
    // 0x801E5CB0: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x801E5CB4: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x801E5CB8: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x801E5CBC: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x801E5CC0: sw          $t9, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r25;
    // 0x801E5CC4: sw          $t9, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r25;
    // 0x801E5CC8: sw          $t9, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r25;
    // 0x801E5CCC: sw          $t8, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r24;
    // 0x801E5CD0: sw          $t8, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r24;
    // 0x801E5CD4: sw          $t8, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r24;
    // 0x801E5CD8: sw          $t7, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r15;
    // 0x801E5CDC: sw          $t7, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r15;
    // 0x801E5CE0: sw          $t7, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r15;
    // 0x801E5CE4: sw          $t6, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r14;
    // 0x801E5CE8: sw          $t6, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r14;
    // 0x801E5CEC: sw          $t6, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r14;
    // 0x801E5CF0: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    // 0x801E5CF4: sw          $s1, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r17;
    // 0x801E5CF8: jal         0x801E8800
    // 0x801E5CFC: swc1        $f20, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->f20.u32l;
    func_801E8800(rdram, ctx);
        goto after_2;
    // 0x801E5CFC: swc1        $f20, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->f20.u32l;
    after_2:
    // 0x801E5D00: lui         $t5, 0xF200
    ctx->r13 = S32(0XF200 << 16);
    // 0x801E5D04: lui         $ra, 0xE400
    ctx->r31 = S32(0XE400 << 16);
    // 0x801E5D08: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
L_801E5D0C:
    // 0x801E5D0C: addiu       $s1, $s1, 0x2
    ctx->r17 = ADD32(ctx->r17, 0X2);
    // 0x801E5D10: addiu       $at, $zero, 0x28
    ctx->r1 = ADD32(0, 0X28);
    // 0x801E5D14: bne         $s1, $at, L_801E5B10
    if (ctx->r17 != ctx->r1) {
        // 0x801E5D18: addiu       $s2, $s2, 0xA0
        ctx->r18 = ADD32(ctx->r18, 0XA0);
            goto L_801E5B10;
    }
    // 0x801E5D18: addiu       $s2, $s2, 0xA0
    ctx->r18 = ADD32(ctx->r18, 0XA0);
    // 0x801E5D1C: b           L_801E6028
    // 0x801E5D20: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
        goto L_801E6028;
    // 0x801E5D20: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
L_801E5D24:
    // 0x801E5D24: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
    // 0x801E5D28: lui         $t6, 0x103
    ctx->r14 = S32(0X103 << 16);
    // 0x801E5D2C: addiu       $a2, $a2, 0x0
    ctx->r6 = ADD32(ctx->r6, 0X0);
    // 0x801E5D30: ori         $t6, $t6, 0x40
    ctx->r14 = ctx->r14 | 0X40;
    // 0x801E5D34: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801E5D38: lui         $t7, 0x102
    ctx->r15 = S32(0X102 << 16);
    // 0x801E5D3C: sw          $t6, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r14;
    // 0x801E5D40: sw          $a2, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r6;
    // 0x801E5D44: ori         $t7, $t7, 0x40
    ctx->r15 = ctx->r15 | 0X40;
    // 0x801E5D48: or          $v1, $s0, $zero
    ctx->r3 = ctx->r16 | 0;
    // 0x801E5D4C: sw          $t7, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r15;
    // 0x801E5D50: lhu         $t8, 0x4($s3)
    ctx->r24 = MEM_HU(ctx->r19, 0X4);
    // 0x801E5D54: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801E5D58: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x801E5D5C: sll         $t9, $t8, 6
    ctx->r25 = S32(ctx->r24 << 6);
    // 0x801E5D60: addu        $t6, $a2, $t9
    ctx->r14 = ADD32(ctx->r6, ctx->r25);
    // 0x801E5D64: addiu       $t7, $t6, 0x900
    ctx->r15 = ADD32(ctx->r14, 0X900);
    // 0x801E5D68: sw          $t7, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r15;
    // 0x801E5D6C: lui         $t8, 0x107
    ctx->r24 = S32(0X107 << 16);
    // 0x801E5D70: lui         $a3, 0x600
    ctx->r7 = S32(0X600 << 16);
    // 0x801E5D74: addiu       $t8, $t8, -0xC60
    ctx->r24 = ADD32(ctx->r24, -0XC60);
    // 0x801E5D78: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801E5D7C: sw          $t8, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r24;
    // 0x801E5D80: sw          $a3, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r7;
    // 0x801E5D84: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    // 0x801E5D88: lui         $t9, 0x107
    ctx->r25 = S32(0X107 << 16);
    // 0x801E5D8C: addiu       $t9, $t9, -0xBF8
    ctx->r25 = ADD32(ctx->r25, -0XBF8);
    // 0x801E5D90: sw          $t9, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r25;
    // 0x801E5D94: sw          $a3, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r7;
    // 0x801E5D98: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801E5D9C: b           L_801E6028
    // 0x801E5DA0: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
        goto L_801E6028;
    // 0x801E5DA0: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
L_801E5DA4:
    // 0x801E5DA4: lw          $t6, 0x28($s3)
    ctx->r14 = MEM_W(ctx->r19, 0X28);
    // 0x801E5DA8: lui         $a1, 0x107
    ctx->r5 = S32(0X107 << 16);
    // 0x801E5DAC: addiu       $a1, $a1, -0xFD0
    ctx->r5 = ADD32(ctx->r5, -0XFD0);
    // 0x801E5DB0: beq         $t6, $zero, L_801E5DD0
    if (ctx->r14 == 0) {
        // 0x801E5DB4: addiu       $s0, $s0, 0x8
        ctx->r16 = ADD32(ctx->r16, 0X8);
            goto L_801E5DD0;
    }
    // 0x801E5DB4: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801E5DB8: lui         $t7, 0x807
    ctx->r15 = S32(0X807 << 16);
    // 0x801E5DBC: addiu       $t7, $t7, 0x1008
    ctx->r15 = ADD32(ctx->r15, 0X1008);
    // 0x801E5DC0: addiu       $t2, $zero, -0x8
    ctx->r10 = ADD32(0, -0X8);
    // 0x801E5DC4: addiu       $t4, $zero, 0xB0
    ctx->r12 = ADD32(0, 0XB0);
    // 0x801E5DC8: b           L_801E5DE4
    // 0x801E5DCC: sw          $t7, 0x194($sp)
    MEM_W(0X194, ctx->r29) = ctx->r15;
        goto L_801E5DE4;
    // 0x801E5DCC: sw          $t7, 0x194($sp)
    MEM_W(0X194, ctx->r29) = ctx->r15;
L_801E5DD0:
    // 0x801E5DD0: lui         $t8, 0x806
    ctx->r24 = S32(0X806 << 16);
    // 0x801E5DD4: addiu       $t8, $t8, -0x7FF8
    ctx->r24 = ADD32(ctx->r24, -0X7FF8);
    // 0x801E5DD8: or          $t2, $zero, $zero
    ctx->r10 = 0 | 0;
    // 0x801E5DDC: addiu       $t4, $zero, 0xA0
    ctx->r12 = ADD32(0, 0XA0);
    // 0x801E5DE0: sw          $t8, 0x194($sp)
    MEM_W(0X194, ctx->r29) = ctx->r24;
L_801E5DE4:
    // 0x801E5DE4: addiu       $v1, $t4, -0x1
    ctx->r3 = ADD32(ctx->r12, -0X1);
    // 0x801E5DE8: sll         $t3, $v1, 1
    ctx->r11 = S32(ctx->r3 << 1);
    // 0x801E5DEC: addiu       $t3, $t3, 0x9
    ctx->r11 = ADD32(ctx->r11, 0X9);
    // 0x801E5DF0: lui         $t9, 0x600
    ctx->r25 = S32(0X600 << 16);
    // 0x801E5DF4: srl         $t7, $t3, 3
    ctx->r15 = S32(U32(ctx->r11) >> 3);
    // 0x801E5DF8: andi        $s2, $v1, 0xFFF
    ctx->r18 = ctx->r3 & 0XFFF;
    // 0x801E5DFC: lui         $at, 0xFD18
    ctx->r1 = S32(0XFD18 << 16);
    // 0x801E5E00: sw          $t9, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r25;
    // 0x801E5E04: or          $t6, $s2, $at
    ctx->r14 = ctx->r18 | ctx->r1;
    // 0x801E5E08: andi        $t8, $t7, 0x1FF
    ctx->r24 = ctx->r15 & 0X1FF;
    // 0x801E5E0C: sll         $t9, $t8, 9
    ctx->r25 = S32(ctx->r24 << 9);
    // 0x801E5E10: lui         $at, 0xF518
    ctx->r1 = S32(0XF518 << 16);
    // 0x801E5E14: sll         $a0, $v1, 2
    ctx->r4 = S32(ctx->r3 << 2);
    // 0x801E5E18: andi        $t7, $a0, 0xFFF
    ctx->r15 = ctx->r4 & 0XFFF;
    // 0x801E5E1C: or          $t3, $t9, $at
    ctx->r11 = ctx->r25 | ctx->r1;
    // 0x801E5E20: lui         $at, 0x700
    ctx->r1 = S32(0X700 << 16);
    // 0x801E5E24: sll         $t8, $t7, 12
    ctx->r24 = S32(ctx->r15 << 12);
    // 0x801E5E28: sw          $a1, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r5;
    // 0x801E5E2C: or          $t9, $t8, $at
    ctx->r25 = ctx->r24 | ctx->r1;
    // 0x801E5E30: or          $s2, $t6, $zero
    ctx->r18 = ctx->r14 | 0;
    // 0x801E5E34: ori         $t6, $t9, 0x10
    ctx->r14 = ctx->r25 | 0X10;
    // 0x801E5E38: ori         $t7, $t8, 0x10
    ctx->r15 = ctx->r24 | 0X10;
    // 0x801E5E3C: sw          $t7, 0x84($sp)
    MEM_W(0X84, ctx->r29) = ctx->r15;
    // 0x801E5E40: sw          $t6, 0x88($sp)
    MEM_W(0X88, ctx->r29) = ctx->r14;
    // 0x801E5E44: or          $t1, $zero, $zero
    ctx->r9 = 0 | 0;
    // 0x801E5E48: or          $s1, $zero, $zero
    ctx->r17 = 0 | 0;
    // 0x801E5E4C: or          $t0, $zero, $zero
    ctx->r8 = 0 | 0;
L_801E5E50:
    // 0x801E5E50: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
    // 0x801E5E54: sw          $s2, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r18;
    // 0x801E5E58: lw          $t9, 0x194($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X194);
    // 0x801E5E5C: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801E5E60: sll         $t8, $t0, 2
    ctx->r24 = S32(ctx->r8 << 2);
    // 0x801E5E64: or          $v1, $s0, $zero
    ctx->r3 = ctx->r16 | 0;
    // 0x801E5E68: addu        $t6, $t8, $t9
    ctx->r14 = ADD32(ctx->r24, ctx->r25);
    // 0x801E5E6C: sw          $t6, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r14;
    // 0x801E5E70: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801E5E74: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x801E5E78: sw          $s4, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r20;
    // 0x801E5E7C: sw          $t3, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r11;
    // 0x801E5E80: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801E5E84: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    // 0x801E5E88: sw          $zero, 0x4($a0)
    MEM_W(0X4, ctx->r4) = 0;
    // 0x801E5E8C: sw          $s5, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r21;
    // 0x801E5E90: sw          $s6, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r22;
    // 0x801E5E94: lw          $t7, 0x88($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X88);
    // 0x801E5E98: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801E5E9C: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
    // 0x801E5EA0: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801E5EA4: sw          $t7, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r15;
    // 0x801E5EA8: or          $v1, $s0, $zero
    ctx->r3 = ctx->r16 | 0;
    // 0x801E5EAC: sw          $zero, 0x4($v0)
    MEM_W(0X4, ctx->r2) = 0;
    // 0x801E5EB0: sw          $s7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r23;
    // 0x801E5EB4: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801E5EB8: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x801E5EBC: sw          $fp, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r30;
    // 0x801E5EC0: sw          $t3, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r11;
    // 0x801E5EC4: sw          $t5, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r13;
    // 0x801E5EC8: lw          $t8, 0x84($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X84);
    // 0x801E5ECC: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801E5ED0: or          $a3, $s0, $zero
    ctx->r7 = ctx->r16 | 0;
    // 0x801E5ED4: sw          $t8, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r24;
    // 0x801E5ED8: lw          $t9, 0x8($s3)
    ctx->r25 = MEM_W(ctx->r19, 0X8);
    // 0x801E5EDC: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801E5EE0: addiu       $t1, $t1, 0x1
    ctx->r9 = ADD32(ctx->r9, 0X1);
    // 0x801E5EE4: addu        $t6, $t9, $t2
    ctx->r14 = ADD32(ctx->r25, ctx->r10);
    // 0x801E5EE8: addu        $a2, $t6, $t4
    ctx->r6 = ADD32(ctx->r14, ctx->r12);
    // 0x801E5EEC: sll         $t7, $a2, 2
    ctx->r15 = S32(ctx->r6 << 2);
    // 0x801E5EF0: beq         $t7, $zero, L_801E5F00
    if (ctx->r15 == 0) {
        // 0x801E5EF4: or          $a1, $s0, $zero
        ctx->r5 = ctx->r16 | 0;
            goto L_801E5F00;
    }
    // 0x801E5EF4: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    // 0x801E5EF8: b           L_801E5F04
    // 0x801E5EFC: or          $a0, $t7, $zero
    ctx->r4 = ctx->r15 | 0;
        goto L_801E5F04;
    // 0x801E5EFC: or          $a0, $t7, $zero
    ctx->r4 = ctx->r15 | 0;
L_801E5F00:
    // 0x801E5F00: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
L_801E5F04:
    // 0x801E5F04: lw          $t8, 0xC($s3)
    ctx->r24 = MEM_W(ctx->r19, 0XC);
    // 0x801E5F08: addiu       $at, $zero, 0x8
    ctx->r1 = ADD32(0, 0X8);
    // 0x801E5F0C: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
    // 0x801E5F10: addu        $v0, $t8, $s1
    ctx->r2 = ADD32(ctx->r24, ctx->r17);
    // 0x801E5F14: addiu       $v0, $v0, 0x5
    ctx->r2 = ADD32(ctx->r2, 0X5);
    // 0x801E5F18: sll         $t9, $v0, 2
    ctx->r25 = S32(ctx->r2 << 2);
    // 0x801E5F1C: blez        $t9, L_801E5F2C
    if (SIGNED(ctx->r25) <= 0) {
        // 0x801E5F20: andi        $t8, $a0, 0xFFF
        ctx->r24 = ctx->r4 & 0XFFF;
            goto L_801E5F2C;
    }
    // 0x801E5F20: andi        $t8, $a0, 0xFFF
    ctx->r24 = ctx->r4 & 0XFFF;
    // 0x801E5F24: b           L_801E5F2C
    // 0x801E5F28: or          $v1, $t9, $zero
    ctx->r3 = ctx->r25 | 0;
        goto L_801E5F2C;
    // 0x801E5F28: or          $v1, $t9, $zero
    ctx->r3 = ctx->r25 | 0;
L_801E5F2C:
    // 0x801E5F2C: andi        $t6, $v1, 0xFFF
    ctx->r14 = ctx->r3 & 0XFFF;
    // 0x801E5F30: or          $t7, $t6, $ra
    ctx->r15 = ctx->r14 | ctx->r31;
    // 0x801E5F34: sll         $t9, $t8, 12
    ctx->r25 = S32(ctx->r24 << 12);
    // 0x801E5F38: or          $t6, $t7, $t9
    ctx->r14 = ctx->r15 | ctx->r25;
    // 0x801E5F3C: sw          $t6, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r14;
    // 0x801E5F40: lw          $t8, 0x8($s3)
    ctx->r24 = MEM_W(ctx->r19, 0X8);
    // 0x801E5F44: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
    // 0x801E5F48: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    // 0x801E5F4C: addu        $v0, $t8, $t2
    ctx->r2 = ADD32(ctx->r24, ctx->r10);
    // 0x801E5F50: sll         $t7, $v0, 2
    ctx->r15 = S32(ctx->r2 << 2);
    // 0x801E5F54: blez        $t7, L_801E5F64
    if (SIGNED(ctx->r15) <= 0) {
        // 0x801E5F58: nop
    
            goto L_801E5F64;
    }
    // 0x801E5F58: nop

    // 0x801E5F5C: b           L_801E5F64
    // 0x801E5F60: or          $a0, $t7, $zero
    ctx->r4 = ctx->r15 | 0;
        goto L_801E5F64;
    // 0x801E5F60: or          $a0, $t7, $zero
    ctx->r4 = ctx->r15 | 0;
L_801E5F64:
    // 0x801E5F64: lw          $t9, 0xC($s3)
    ctx->r25 = MEM_W(ctx->r19, 0XC);
    // 0x801E5F68: andi        $t7, $a0, 0xFFF
    ctx->r15 = ctx->r4 & 0XFFF;
    // 0x801E5F6C: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    // 0x801E5F70: addu        $v0, $t9, $s1
    ctx->r2 = ADD32(ctx->r25, ctx->r17);
    // 0x801E5F74: sll         $t6, $v0, 2
    ctx->r14 = S32(ctx->r2 << 2);
    // 0x801E5F78: blez        $t6, L_801E5F88
    if (SIGNED(ctx->r14) <= 0) {
        // 0x801E5F7C: sll         $t9, $t7, 12
        ctx->r25 = S32(ctx->r15 << 12);
            goto L_801E5F88;
    }
    // 0x801E5F7C: sll         $t9, $t7, 12
    ctx->r25 = S32(ctx->r15 << 12);
    // 0x801E5F80: b           L_801E5F88
    // 0x801E5F84: or          $v1, $t6, $zero
    ctx->r3 = ctx->r14 | 0;
        goto L_801E5F88;
    // 0x801E5F84: or          $v1, $t6, $zero
    ctx->r3 = ctx->r14 | 0;
L_801E5F88:
    // 0x801E5F88: andi        $t8, $v1, 0xFFF
    ctx->r24 = ctx->r3 & 0XFFF;
    // 0x801E5F8C: or          $t6, $t8, $t9
    ctx->r14 = ctx->r24 | ctx->r25;
    // 0x801E5F90: sw          $t6, 0x4($a3)
    MEM_W(0X4, ctx->r7) = ctx->r14;
    // 0x801E5F94: lui         $t7, 0xB300
    ctx->r15 = S32(0XB300 << 16);
    // 0x801E5F98: sw          $t7, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r15;
    // 0x801E5F9C: lw          $t8, 0x8($s3)
    ctx->r24 = MEM_W(ctx->r19, 0X8);
    // 0x801E5FA0: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801E5FA4: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
    // 0x801E5FA8: addu        $t9, $t8, $t2
    ctx->r25 = ADD32(ctx->r24, ctx->r10);
    // 0x801E5FAC: sll         $t6, $t9, 12
    ctx->r14 = S32(ctx->r25 << 12);
    // 0x801E5FB0: sra         $t7, $t6, 7
    ctx->r15 = S32(SIGNED(ctx->r14) >> 7);
    // 0x801E5FB4: bgez        $t7, L_801E5FC4
    if (SIGNED(ctx->r15) >= 0) {
        // 0x801E5FB8: addiu       $s0, $s0, 0x8
        ctx->r16 = ADD32(ctx->r16, 0X8);
            goto L_801E5FC4;
    }
    // 0x801E5FB8: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801E5FBC: b           L_801E5FC4
    // 0x801E5FC0: or          $a0, $t7, $zero
    ctx->r4 = ctx->r15 | 0;
        goto L_801E5FC4;
    // 0x801E5FC0: or          $a0, $t7, $zero
    ctx->r4 = ctx->r15 | 0;
L_801E5FC4:
    // 0x801E5FC4: lw          $t8, 0xC($s3)
    ctx->r24 = MEM_W(ctx->r19, 0XC);
    // 0x801E5FC8: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
    // 0x801E5FCC: addu        $t9, $t8, $s1
    ctx->r25 = ADD32(ctx->r24, ctx->r17);
    // 0x801E5FD0: sll         $t6, $t9, 12
    ctx->r14 = S32(ctx->r25 << 12);
    // 0x801E5FD4: sra         $t7, $t6, 7
    ctx->r15 = S32(SIGNED(ctx->r14) >> 7);
    // 0x801E5FD8: bgez        $t7, L_801E5FE8
    if (SIGNED(ctx->r15) >= 0) {
        // 0x801E5FDC: addiu       $s1, $s1, 0x5
        ctx->r17 = ADD32(ctx->r17, 0X5);
            goto L_801E5FE8;
    }
    // 0x801E5FDC: addiu       $s1, $s1, 0x5
    ctx->r17 = ADD32(ctx->r17, 0X5);
    // 0x801E5FE0: b           L_801E5FE8
    // 0x801E5FE4: or          $v1, $t7, $zero
    ctx->r3 = ctx->r15 | 0;
        goto L_801E5FE8;
    // 0x801E5FE4: or          $v1, $t7, $zero
    ctx->r3 = ctx->r15 | 0;
L_801E5FE8:
    // 0x801E5FE8: negu        $t8, $v1
    ctx->r24 = SUB32(0, ctx->r3);
    // 0x801E5FEC: andi        $t9, $t8, 0xFFFF
    ctx->r25 = ctx->r24 & 0XFFFF;
    // 0x801E5FF0: negu        $t7, $a0
    ctx->r15 = SUB32(0, ctx->r4);
    // 0x801E5FF4: sll         $t8, $t7, 16
    ctx->r24 = S32(ctx->r15 << 16);
    // 0x801E5FF8: or          $t6, $t9, $t8
    ctx->r14 = ctx->r25 | ctx->r24;
    // 0x801E5FFC: sll         $t8, $t4, 2
    ctx->r24 = S32(ctx->r12 << 2);
    // 0x801E6000: lui         $t9, 0x400
    ctx->r25 = S32(0X400 << 16);
    // 0x801E6004: addu        $t8, $t8, $t4
    ctx->r24 = ADD32(ctx->r24, ctx->r12);
    // 0x801E6008: ori         $t9, $t9, 0x400
    ctx->r25 = ctx->r25 | 0X400;
    // 0x801E600C: sw          $t6, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r14;
    // 0x801E6010: lui         $t7, 0xB200
    ctx->r15 = S32(0XB200 << 16);
    // 0x801E6014: addu        $t0, $t0, $t8
    ctx->r8 = ADD32(ctx->r8, ctx->r24);
    // 0x801E6018: sw          $t7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r15;
    // 0x801E601C: bne         $t1, $at, L_801E5E50
    if (ctx->r9 != ctx->r1) {
        // 0x801E6020: sw          $t9, 0x4($v0)
        MEM_W(0X4, ctx->r2) = ctx->r25;
            goto L_801E5E50;
    }
    // 0x801E6020: sw          $t9, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r25;
    // 0x801E6024: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
L_801E6028:
    // 0x801E6028: lui         $t6, 0x8023
    ctx->r14 = S32(0X8023 << 16);
    // 0x801E602C: addiu       $t6, $t6, -0x75F4
    ctx->r14 = ADD32(ctx->r14, -0X75F4);
    // 0x801E6030: addiu       $s3, $s3, 0x2C
    ctx->r19 = ADD32(ctx->r19, 0X2C);
    // 0x801E6034: bnel        $s3, $t6, L_801E55C4
    if (ctx->r19 != ctx->r14) {
        // 0x801E6038: lhu         $t6, 0x6($s3)
        ctx->r14 = MEM_HU(ctx->r19, 0X6);
            goto L_801E55C4;
    }
    goto skip_0;
    // 0x801E6038: lhu         $t6, 0x6($s3)
    ctx->r14 = MEM_HU(ctx->r19, 0X6);
    skip_0:
    // 0x801E603C: lw          $ra, 0x7C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X7C);
    // 0x801E6040: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
    // 0x801E6044: lw          $s0, 0x58($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X58);
    // 0x801E6048: ldc1        $f20, 0x50($sp)
    CHECK_FR(ctx, 20);
    ctx->f20.u64 = LD(ctx->r29, 0X50);
    // 0x801E604C: lw          $s1, 0x5C($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X5C);
    // 0x801E6050: lw          $s2, 0x60($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X60);
    // 0x801E6054: lw          $s3, 0x64($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X64);
    // 0x801E6058: lw          $s4, 0x68($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X68);
    // 0x801E605C: lw          $s5, 0x6C($sp)
    ctx->r21 = MEM_W(ctx->r29, 0X6C);
    // 0x801E6060: lw          $s6, 0x70($sp)
    ctx->r22 = MEM_W(ctx->r29, 0X70);
    // 0x801E6064: lw          $s7, 0x74($sp)
    ctx->r23 = MEM_W(ctx->r29, 0X74);
    // 0x801E6068: lw          $fp, 0x78($sp)
    ctx->r30 = MEM_W(ctx->r29, 0X78);
    // 0x801E606C: jr          $ra
    // 0x801E6070: addiu       $sp, $sp, 0x1B0
    ctx->r29 = ADD32(ctx->r29, 0X1B0);
    return;
    // 0x801E6070: addiu       $sp, $sp, 0x1B0
    ctx->r29 = ADD32(ctx->r29, 0X1B0);
;}
