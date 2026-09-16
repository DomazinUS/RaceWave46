#include "recomp.h"
#include "funcs.h"

RECOMP_FUNC void func_8009A97C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8009A97C: lui         $t6, 0x801D
    ctx->r14 = S32(0X801D << 16);
    // 0x8009A980: lw          $t6, -0x19C8($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X19C8);
    // 0x8009A984: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x8009A988: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x8009A98C: bne         $t6, $zero, L_8009A9EC
    if (ctx->r14 != 0) {
        // 0x8009A990: sw          $a0, 0x18($sp)
        MEM_W(0X18, ctx->r29) = ctx->r4;
            goto L_8009A9EC;
    }
    // 0x8009A990: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    // 0x8009A994: lui         $t7, 0x800D
    ctx->r15 = S32(0X800D << 16);
    // 0x8009A998: lw          $t7, 0x48DC($t7)
    ctx->r15 = MEM_W(ctx->r15, 0X48DC);
    // 0x8009A99C: lui         $v0, 0x8019
    ctx->r2 = S32(0X8019 << 16);
    // 0x8009A9A0: addiu       $at, $zero, 0x18
    ctx->r1 = ADD32(0, 0X18);
    // 0x8009A9A4: sll         $t8, $t7, 2
    ctx->r24 = S32(ctx->r15 << 2);
    // 0x8009A9A8: subu        $t8, $t8, $t7
    ctx->r24 = SUB32(ctx->r24, ctx->r15);
    // 0x8009A9AC: sll         $t8, $t8, 3
    ctx->r24 = S32(ctx->r24 << 3);
    // 0x8009A9B0: subu        $t8, $t8, $t7
    ctx->r24 = SUB32(ctx->r24, ctx->r15);
    // 0x8009A9B4: sll         $t8, $t8, 3
    ctx->r24 = S32(ctx->r24 << 3);
    // 0x8009A9B8: addu        $t8, $t8, $t7
    ctx->r24 = ADD32(ctx->r24, ctx->r15);
    // 0x8009A9BC: sll         $t8, $t8, 2
    ctx->r24 = S32(ctx->r24 << 2);
    // 0x8009A9C0: subu        $t8, $t8, $t7
    ctx->r24 = SUB32(ctx->r24, ctx->r15);
    // 0x8009A9C4: sll         $t8, $t8, 3
    ctx->r24 = S32(ctx->r24 << 3);
    // 0x8009A9C8: addu        $v0, $v0, $t8
    ctx->r2 = ADD32(ctx->r2, ctx->r24);
    // 0x8009A9CC: lw          $v0, 0x32E4($v0)
    ctx->r2 = MEM_W(ctx->r2, 0X32E4);
    // 0x8009A9D0: addiu       $a0, $zero, 0x89
    ctx->r4 = ADD32(0, 0X89);
    // 0x8009A9D4: beq         $v0, $at, L_8009A9E4
    if (ctx->r2 == ctx->r1) {
        // 0x8009A9D8: addiu       $at, $zero, 0x17
        ctx->r1 = ADD32(0, 0X17);
            goto L_8009A9E4;
    }
    // 0x8009A9D8: addiu       $at, $zero, 0x17
    ctx->r1 = ADD32(0, 0X17);
    // 0x8009A9DC: bnel        $v0, $at, L_8009A9F0
    if (ctx->r2 != ctx->r1) {
        // 0x8009A9E0: lw          $ra, 0x14($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X14);
            goto L_8009A9F0;
    }
    goto skip_0;
    // 0x8009A9E0: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    skip_0:
L_8009A9E4:
    // 0x8009A9E4: jal         0x8009A404
    // 0x8009A9E8: addiu       $a1, $zero, 0x6
    ctx->r5 = ADD32(0, 0X6);
    func_8009A404(rdram, ctx);
        goto after_0;
    // 0x8009A9E8: addiu       $a1, $zero, 0x6
    ctx->r5 = ADD32(0, 0X6);
    after_0:
L_8009A9EC:
    // 0x8009A9EC: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_8009A9F0:
    // 0x8009A9F0: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x8009A9F4: jr          $ra
    // 0x8009A9F8: nop

    return;
    // 0x8009A9F8: nop

;}
RECOMP_FUNC void func_8009A9FC(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8009A9FC: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x8009AA00: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x8009AA04: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    // 0x8009AA08: addiu       $a0, $zero, 0x89
    ctx->r4 = ADD32(0, 0X89);
    // 0x8009AA0C: jal         0x8009A404
    // 0x8009AA10: addiu       $a1, $zero, 0xA
    ctx->r5 = ADD32(0, 0XA);
    func_8009A404(rdram, ctx);
        goto after_0;
    // 0x8009AA10: addiu       $a1, $zero, 0xA
    ctx->r5 = ADD32(0, 0XA);
    after_0:
    // 0x8009AA14: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x8009AA18: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x8009AA1C: jr          $ra
    // 0x8009AA20: nop

    return;
    // 0x8009AA20: nop

;}
RECOMP_FUNC void func_8009AA24(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8009AA24: lui         $t6, 0x801D
    ctx->r14 = S32(0X801D << 16);
    // 0x8009AA28: lw          $t6, -0x19C8($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X19C8);
    // 0x8009AA2C: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x8009AA30: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x8009AA34: bne         $t6, $zero, L_8009AB10
    if (ctx->r14 != 0) {
        // 0x8009AA38: lui         $a1, 0x800D
        ctx->r5 = S32(0X800D << 16);
            goto L_8009AB10;
    }
    // 0x8009AA38: lui         $a1, 0x800D
    ctx->r5 = S32(0X800D << 16);
    // 0x8009AA3C: addiu       $a1, $a1, 0x48DC
    ctx->r5 = ADD32(ctx->r5, 0X48DC);
    // 0x8009AA40: lw          $t7, 0x0($a1)
    ctx->r15 = MEM_W(ctx->r5, 0X0);
    // 0x8009AA44: addiu       $a2, $zero, 0x1718
    ctx->r6 = ADD32(0, 0X1718);
    // 0x8009AA48: lui         $v1, 0x8019
    ctx->r3 = S32(0X8019 << 16);
    // 0x8009AA4C: multu       $t7, $a2
    result = U64(U32(ctx->r15)) * U64(U32(ctx->r6)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x8009AA50: addiu       $v1, $v1, 0x2690
    ctx->r3 = ADD32(ctx->r3, 0X2690);
    // 0x8009AA54: mtc1        $zero, $f4
    ctx->f4.u32l = 0;
    // 0x8009AA58: addiu       $t0, $zero, 0x10
    ctx->r8 = ADD32(0, 0X10);
    // 0x8009AA5C: mflo        $t8
    ctx->r24 = lo;
    // 0x8009AA60: addu        $t9, $v1, $t8
    ctx->r25 = ADD32(ctx->r3, ctx->r24);
    // 0x8009AA64: lwc1        $f6, 0xC48($t9)
    ctx->f6.u32l = MEM_W(ctx->r25, 0XC48);
    // 0x8009AA68: c.lt.s      $f4, $f6
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    c1cs = ctx->f4.fl < ctx->f6.fl;
    // 0x8009AA6C: nop

    // 0x8009AA70: bc1fl       L_8009AA80
    if (!c1cs) {
        // 0x8009AA74: lbu         $v0, 0x94($a0)
        ctx->r2 = MEM_BU(ctx->r4, 0X94);
            goto L_8009AA80;
    }
    goto skip_0;
    // 0x8009AA74: lbu         $v0, 0x94($a0)
    ctx->r2 = MEM_BU(ctx->r4, 0X94);
    skip_0:
    // 0x8009AA78: sb          $t0, 0x94($a0)
    MEM_B(0X94, ctx->r4) = ctx->r8;
    // 0x8009AA7C: lbu         $v0, 0x94($a0)
    ctx->r2 = MEM_BU(ctx->r4, 0X94);
L_8009AA80:
    // 0x8009AA80: blez        $v0, L_8009AB10
    if (SIGNED(ctx->r2) <= 0) {
        // 0x8009AA84: addiu       $t1, $v0, -0x1
        ctx->r9 = ADD32(ctx->r2, -0X1);
            goto L_8009AB10;
    }
    // 0x8009AA84: addiu       $t1, $v0, -0x1
    ctx->r9 = ADD32(ctx->r2, -0X1);
    // 0x8009AA88: sb          $t1, 0x94($a0)
    MEM_B(0X94, ctx->r4) = ctx->r9;
    // 0x8009AA8C: lw          $t2, 0x0($a1)
    ctx->r10 = MEM_W(ctx->r5, 0X0);
    // 0x8009AA90: lui         $t5, 0x8019
    ctx->r13 = S32(0X8019 << 16);
    // 0x8009AA94: lw          $t5, 0x2458($t5)
    ctx->r13 = MEM_W(ctx->r13, 0X2458);
    // 0x8009AA98: multu       $t2, $a2
    result = U64(U32(ctx->r10)) * U64(U32(ctx->r6)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x8009AA9C: lui         $at, 0x42C8
    ctx->r1 = S32(0X42C8 << 16);
    // 0x8009AAA0: mtc1        $t5, $f16
    ctx->f16.u32l = ctx->r13;
    // 0x8009AAA4: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x8009AAA8: lui         $t6, 0x801D
    ctx->r14 = S32(0X801D << 16);
    // 0x8009AAAC: cvt.s.w     $f18, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    ctx->f18.fl = CVT_S_W(ctx->f16.u32l);
    // 0x8009AAB0: mflo        $t3
    ctx->r11 = lo;
    // 0x8009AAB4: addu        $t4, $v1, $t3
    ctx->r12 = ADD32(ctx->r3, ctx->r11);
    // 0x8009AAB8: lwc1        $f10, 0x48($t4)
    ctx->f10.u32l = MEM_W(ctx->r12, 0X48);
    // 0x8009AABC: sub.s       $f4, $f10, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f4.fl = ctx->f10.fl - ctx->f18.fl;
    // 0x8009AAC0: c.lt.s      $f8, $f4
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    c1cs = ctx->f8.fl < ctx->f4.fl;
    // 0x8009AAC4: nop

    // 0x8009AAC8: bc1fl       L_8009AB14
    if (!c1cs) {
        // 0x8009AACC: lw          $ra, 0x14($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X14);
            goto L_8009AB14;
    }
    goto skip_1;
    // 0x8009AACC: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    skip_1:
    // 0x8009AAD0: lbu         $t6, -0x155C($t6)
    ctx->r14 = MEM_BU(ctx->r14, -0X155C);
    // 0x8009AAD4: addiu       $at, $zero, 0x86
    ctx->r1 = ADD32(0, 0X86);
    // 0x8009AAD8: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x8009AADC: bne         $t6, $at, L_8009AAF4
    if (ctx->r14 != ctx->r1) {
        // 0x8009AAE0: addiu       $a0, $zero, 0x86
        ctx->r4 = ADD32(0, 0X86);
            goto L_8009AAF4;
    }
    // 0x8009AAE0: addiu       $a0, $zero, 0x86
    ctx->r4 = ADD32(0, 0X86);
    // 0x8009AAE4: jal         0x8009A404
    // 0x8009AAE8: addiu       $a0, $zero, 0x87
    ctx->r4 = ADD32(0, 0X87);
    func_8009A404(rdram, ctx);
        goto after_0;
    // 0x8009AAE8: addiu       $a0, $zero, 0x87
    ctx->r4 = ADD32(0, 0X87);
    after_0:
    // 0x8009AAEC: b           L_8009AAFC
    // 0x8009AAF0: nop

        goto L_8009AAFC;
    // 0x8009AAF0: nop

L_8009AAF4:
    // 0x8009AAF4: jal         0x8009A404
    // 0x8009AAF8: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_8009A404(rdram, ctx);
        goto after_1;
    // 0x8009AAF8: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_1:
L_8009AAFC:
    // 0x8009AAFC: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x8009AB00: addiu       $v0, $v0, -0x1558
    ctx->r2 = ADD32(ctx->r2, -0X1558);
    // 0x8009AB04: lbu         $t7, 0x0($v0)
    ctx->r15 = MEM_BU(ctx->r2, 0X0);
    // 0x8009AB08: addiu       $t8, $t7, 0x1
    ctx->r24 = ADD32(ctx->r15, 0X1);
    // 0x8009AB0C: sb          $t8, 0x0($v0)
    MEM_B(0X0, ctx->r2) = ctx->r24;
L_8009AB10:
    // 0x8009AB10: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_8009AB14:
    // 0x8009AB14: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x8009AB18: jr          $ra
    // 0x8009AB1C: nop

    return;
    // 0x8009AB1C: nop

;}
RECOMP_FUNC void func_8009AB20(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8009AB20: addiu       $sp, $sp, -0x48
    ctx->r29 = ADD32(ctx->r29, -0X48);
    // 0x8009AB24: mtc1        $a1, $f12
    ctx->f12.u32l = ctx->r5;
    // 0x8009AB28: mtc1        $a2, $f14
    ctx->f14.u32l = ctx->r6;
    // 0x8009AB2C: sw          $a3, 0x54($sp)
    MEM_W(0X54, ctx->r29) = ctx->r7;
    // 0x8009AB30: lwc1        $f4, 0x54($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X54);
    // 0x8009AB34: sw          $a0, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r4;
    // 0x8009AB38: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x8009AB3C: lui         $a0, 0x801D
    ctx->r4 = S32(0X801D << 16);
    // 0x8009AB40: lui         $a1, 0x800D
    ctx->r5 = S32(0X800D << 16);
    // 0x8009AB44: mfc1        $a2, $f12
    ctx->r6 = (int32_t)ctx->f12.u32l;
    // 0x8009AB48: mfc1        $a3, $f14
    ctx->r7 = (int32_t)ctx->f14.u32l;
    // 0x8009AB4C: lw          $a1, 0x48DC($a1)
    ctx->r5 = MEM_W(ctx->r5, 0X48DC);
    // 0x8009AB50: addiu       $a0, $a0, -0x1390
    ctx->r4 = ADD32(ctx->r4, -0X1390);
    // 0x8009AB54: jal         0x800989E0
    // 0x8009AB58: swc1        $f4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f4.u32l;
    func_800989E0(rdram, ctx);
        goto after_0;
    // 0x8009AB58: swc1        $f4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f4.u32l;
    after_0:
    // 0x8009AB5C: lui         $t6, 0x800D
    ctx->r14 = S32(0X800D << 16);
    // 0x8009AB60: lw          $t6, 0x48DC($t6)
    ctx->r14 = MEM_W(ctx->r14, 0X48DC);
    // 0x8009AB64: lui         $t8, 0x8019
    ctx->r24 = S32(0X8019 << 16);
    // 0x8009AB68: addiu       $t8, $t8, 0x2690
    ctx->r24 = ADD32(ctx->r24, 0X2690);
    // 0x8009AB6C: sll         $t7, $t6, 2
    ctx->r15 = S32(ctx->r14 << 2);
    // 0x8009AB70: subu        $t7, $t7, $t6
    ctx->r15 = SUB32(ctx->r15, ctx->r14);
    // 0x8009AB74: sll         $t7, $t7, 3
    ctx->r15 = S32(ctx->r15 << 3);
    // 0x8009AB78: subu        $t7, $t7, $t6
    ctx->r15 = SUB32(ctx->r15, ctx->r14);
    // 0x8009AB7C: sll         $t7, $t7, 3
    ctx->r15 = S32(ctx->r15 << 3);
    // 0x8009AB80: addu        $t7, $t7, $t6
    ctx->r15 = ADD32(ctx->r15, ctx->r14);
    // 0x8009AB84: sll         $t7, $t7, 2
    ctx->r15 = S32(ctx->r15 << 2);
    // 0x8009AB88: subu        $t7, $t7, $t6
    ctx->r15 = SUB32(ctx->r15, ctx->r14);
    // 0x8009AB8C: sll         $t7, $t7, 3
    ctx->r15 = S32(ctx->r15 << 3);
    // 0x8009AB90: addu        $v0, $t7, $t8
    ctx->r2 = ADD32(ctx->r15, ctx->r24);
    // 0x8009AB94: lw          $a1, 0x44($v0)
    ctx->r5 = MEM_W(ctx->r2, 0X44);
    // 0x8009AB98: lw          $a2, 0x48($v0)
    ctx->r6 = MEM_W(ctx->r2, 0X48);
    // 0x8009AB9C: lw          $a3, 0x4C($v0)
    ctx->r7 = MEM_W(ctx->r2, 0X4C);
    // 0x8009ABA0: jal         0x800984F4
    // 0x8009ABA4: addiu       $a0, $sp, 0x3C
    ctx->r4 = ADD32(ctx->r29, 0X3C);
    Math_Vec3f_Set(rdram, ctx);
        goto after_1;
    // 0x8009ABA4: addiu       $a0, $sp, 0x3C
    ctx->r4 = ADD32(ctx->r29, 0X3C);
    after_1:
    // 0x8009ABA8: lui         $a0, 0x801D
    ctx->r4 = S32(0X801D << 16);
    // 0x8009ABAC: lui         $a2, 0x801D
    ctx->r6 = S32(0X801D << 16);
    // 0x8009ABB0: lui         $a3, 0x801D
    ctx->r7 = S32(0X801D << 16);
    // 0x8009ABB4: addiu       $a3, $a3, -0x1384
    ctx->r7 = ADD32(ctx->r7, -0X1384);
    // 0x8009ABB8: addiu       $a2, $a2, -0x1360
    ctx->r6 = ADD32(ctx->r6, -0X1360);
    // 0x8009ABBC: addiu       $a0, $a0, -0x1378
    ctx->r4 = ADD32(ctx->r4, -0X1378);
    // 0x8009ABC0: jal         0x8009917C
    // 0x8009ABC4: addiu       $a1, $sp, 0x3C
    ctx->r5 = ADD32(ctx->r29, 0X3C);
    func_8009917C(rdram, ctx);
        goto after_2;
    // 0x8009ABC4: addiu       $a1, $sp, 0x3C
    ctx->r5 = ADD32(ctx->r29, 0X3C);
    after_2:
    // 0x8009ABC8: lui         $t9, 0x800D
    ctx->r25 = S32(0X800D << 16);
    // 0x8009ABCC: lw          $t9, 0x48DC($t9)
    ctx->r25 = MEM_W(ctx->r25, 0X48DC);
    // 0x8009ABD0: lw          $v0, 0x48($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X48);
    // 0x8009ABD4: lui         $at, 0x8019
    ctx->r1 = S32(0X8019 << 16);
    // 0x8009ABD8: sll         $t0, $t9, 2
    ctx->r8 = S32(ctx->r25 << 2);
    // 0x8009ABDC: subu        $t0, $t0, $t9
    ctx->r8 = SUB32(ctx->r8, ctx->r25);
    // 0x8009ABE0: sll         $t0, $t0, 3
    ctx->r8 = S32(ctx->r8 << 3);
    // 0x8009ABE4: subu        $t0, $t0, $t9
    ctx->r8 = SUB32(ctx->r8, ctx->r25);
    // 0x8009ABE8: sll         $t0, $t0, 3
    ctx->r8 = S32(ctx->r8 << 3);
    // 0x8009ABEC: addu        $t0, $t0, $t9
    ctx->r8 = ADD32(ctx->r8, ctx->r25);
    // 0x8009ABF0: sll         $t0, $t0, 2
    ctx->r8 = S32(ctx->r8 << 2);
    // 0x8009ABF4: subu        $t0, $t0, $t9
    ctx->r8 = SUB32(ctx->r8, ctx->r25);
    // 0x8009ABF8: sll         $t0, $t0, 3
    ctx->r8 = S32(ctx->r8 << 3);
    // 0x8009ABFC: addu        $at, $at, $t0
    ctx->r1 = ADD32(ctx->r1, ctx->r8);
    // 0x8009AC00: lwc1        $f6, 0x26D8($at)
    ctx->f6.u32l = MEM_W(ctx->r1, 0X26D8);
    // 0x8009AC04: lwc1        $f0, 0x4($v0)
    ctx->f0.u32l = MEM_W(ctx->r2, 0X4);
    // 0x8009AC08: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x8009AC0C: lwc1        $f10, -0x4B34($at)
    ctx->f10.u32l = MEM_W(ctx->r1, -0X4B34);
    // 0x8009AC10: sub.s       $f8, $f6, $f0
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f8.fl = ctx->f6.fl - ctx->f0.fl;
    // 0x8009AC14: lui         $a1, 0x801D
    ctx->r5 = S32(0X801D << 16);
    // 0x8009AC18: addiu       $a1, $a1, -0x1390
    ctx->r5 = ADD32(ctx->r5, -0X1390);
    // 0x8009AC1C: addiu       $a0, $v0, 0xC
    ctx->r4 = ADD32(ctx->r2, 0XC);
    // 0x8009AC20: mul.s       $f16, $f8, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f16.fl = MUL_S(ctx->f8.fl, ctx->f10.fl);
    // 0x8009AC24: add.s       $f18, $f16, $f0
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f18.fl = ctx->f16.fl + ctx->f0.fl;
    // 0x8009AC28: jal         0x8009852C
    // 0x8009AC2C: swc1        $f18, 0x1C($a1)
    MEM_W(0X1C, ctx->r5) = ctx->f18.u32l;
    Math_Vec3f_Copy(rdram, ctx);
        goto after_3;
    // 0x8009AC2C: swc1        $f18, 0x1C($a1)
    MEM_W(0X1C, ctx->r5) = ctx->f18.u32l;
    after_3:
    // 0x8009AC30: lui         $a1, 0x801D
    ctx->r5 = S32(0X801D << 16);
    // 0x8009AC34: addiu       $a1, $a1, -0x1378
    ctx->r5 = ADD32(ctx->r5, -0X1378);
    // 0x8009AC38: jal         0x8009852C
    // 0x8009AC3C: lw          $a0, 0x48($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X48);
    Math_Vec3f_Copy(rdram, ctx);
        goto after_4;
    // 0x8009AC3C: lw          $a0, 0x48($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X48);
    after_4:
    // 0x8009AC40: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    // 0x8009AC44: addiu       $sp, $sp, 0x48
    ctx->r29 = ADD32(ctx->r29, 0X48);
    // 0x8009AC48: jr          $ra
    // 0x8009AC4C: nop

    return;
    // 0x8009AC4C: nop

;}
RECOMP_FUNC void func_8009AC50(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8009AC50: mtc1        $a2, $f12
    ctx->f12.u32l = ctx->r6;
    // 0x8009AC54: mtc1        $a3, $f14
    ctx->f14.u32l = ctx->r7;
    // 0x8009AC58: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x8009AC5C: sw          $a0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r4;
    // 0x8009AC60: sw          $a1, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r5;
    // 0x8009AC64: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x8009AC68: lui         $a0, 0x801D
    ctx->r4 = S32(0X801D << 16);
    // 0x8009AC6C: mfc1        $a1, $f12
    ctx->r5 = (int32_t)ctx->f12.u32l;
    // 0x8009AC70: mfc1        $a2, $f14
    ctx->r6 = (int32_t)ctx->f14.u32l;
    // 0x8009AC74: addiu       $a0, $a0, -0x1360
    ctx->r4 = ADD32(ctx->r4, -0X1360);
    // 0x8009AC78: jal         0x800984F4
    // 0x8009AC7C: lw          $a3, 0x30($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X30);
    Math_Vec3f_Set(rdram, ctx);
        goto after_0;
    // 0x8009AC7C: lw          $a3, 0x30($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X30);
    after_0:
    // 0x8009AC80: lui         $a0, 0x800D
    ctx->r4 = S32(0X800D << 16);
    // 0x8009AC84: jal         0x8009898C
    // 0x8009AC88: lw          $a0, 0x48DC($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X48DC);
    func_8009898C(rdram, ctx);
        goto after_1;
    // 0x8009AC88: lw          $a0, 0x48DC($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X48DC);
    after_1:
    // 0x8009AC8C: mtc1        $zero, $f2
    ctx->f2.u32l = 0;
    // 0x8009AC90: lui         $a0, 0x801D
    ctx->r4 = S32(0X801D << 16);
    // 0x8009AC94: mfc1        $a2, $f0
    ctx->r6 = (int32_t)ctx->f0.u32l;
    // 0x8009AC98: mfc1        $a1, $f2
    ctx->r5 = (int32_t)ctx->f2.u32l;
    // 0x8009AC9C: mfc1        $a3, $f2
    ctx->r7 = (int32_t)ctx->f2.u32l;
    // 0x8009ACA0: jal         0x800984F4
    // 0x8009ACA4: addiu       $a0, $a0, -0x1384
    ctx->r4 = ADD32(ctx->r4, -0X1384);
    Math_Vec3f_Set(rdram, ctx);
        goto after_2;
    // 0x8009ACA4: addiu       $a0, $a0, -0x1384
    ctx->r4 = ADD32(ctx->r4, -0X1384);
    after_2:
    // 0x8009ACA8: lui         $a0, 0x801D
    ctx->r4 = S32(0X801D << 16);
    // 0x8009ACAC: addiu       $a0, $a0, -0x12A0
    ctx->r4 = ADD32(ctx->r4, -0X12A0);
    // 0x8009ACB0: lw          $a1, 0x24($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X24);
    // 0x8009ACB4: jal         0x800998B0
    // 0x8009ACB8: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    func_800998B0(rdram, ctx);
        goto after_3;
    // 0x8009ACB8: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    after_3:
    // 0x8009ACBC: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x8009ACC0: lw          $v0, 0x5138($v0)
    ctx->r2 = MEM_W(ctx->r2, 0X5138);
    // 0x8009ACC4: lui         $t9, 0x801D
    ctx->r25 = S32(0X801D << 16);
    // 0x8009ACC8: lw          $a1, 0x20($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X20);
    // 0x8009ACCC: addiu       $t9, $t9, -0x1020
    ctx->r25 = ADD32(ctx->r25, -0X1020);
    // 0x8009ACD0: lui         $t7, 0x801D
    ctx->r15 = S32(0X801D << 16);
    // 0x8009ACD4: sll         $t8, $v0, 2
    ctx->r24 = S32(ctx->r2 << 2);
    // 0x8009ACD8: addu        $t0, $t8, $t9
    ctx->r8 = ADD32(ctx->r24, ctx->r25);
    // 0x8009ACDC: addiu       $t7, $t7, -0x1018
    ctx->r15 = ADD32(ctx->r15, -0X1018);
    // 0x8009ACE0: lui         $a0, 0x801D
    ctx->r4 = S32(0X801D << 16);
    // 0x8009ACE4: lui         $a2, 0x801D
    ctx->r6 = S32(0X801D << 16);
    // 0x8009ACE8: sll         $t6, $v0, 1
    ctx->r14 = S32(ctx->r2 << 1);
    // 0x8009ACEC: addu        $a3, $t6, $t7
    ctx->r7 = ADD32(ctx->r14, ctx->r15);
    // 0x8009ACF0: addiu       $a2, $a2, -0x12A0
    ctx->r6 = ADD32(ctx->r6, -0X12A0);
    // 0x8009ACF4: addiu       $a0, $a0, -0x1390
    ctx->r4 = ADD32(ctx->r4, -0X1390);
    // 0x8009ACF8: sw          $t0, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r8;
    // 0x8009ACFC: jal         0x80099514
    // 0x8009AD00: addiu       $a1, $a1, 0x18
    ctx->r5 = ADD32(ctx->r5, 0X18);
    func_80099514(rdram, ctx);
        goto after_4;
    // 0x8009AD00: addiu       $a1, $a1, 0x18
    ctx->r5 = ADD32(ctx->r5, 0X18);
    after_4:
    // 0x8009AD04: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    // 0x8009AD08: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x8009AD0C: jr          $ra
    // 0x8009AD10: nop

    return;
    // 0x8009AD10: nop

;}
RECOMP_FUNC void func_8009AD14(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8009AD14: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x8009AD18: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    // 0x8009AD1C: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x8009AD20: lui         $a0, 0x800E
    ctx->r4 = S32(0X800E << 16);
    // 0x8009AD24: jal         0x800988D8
    // 0x8009AD28: lw          $a0, 0x5138($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X5138);
    func_800988D8(rdram, ctx);
        goto after_0;
    // 0x8009AD28: lw          $a0, 0x5138($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X5138);
    after_0:
    // 0x8009AD2C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x8009AD30: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x8009AD34: jr          $ra
    // 0x8009AD38: nop

    return;
    // 0x8009AD38: nop

;}
RECOMP_FUNC void func_8009AD3C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8009AD3C: lui         $at, 0x42C8
    ctx->r1 = S32(0X42C8 << 16);
    // 0x8009AD40: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x8009AD44: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x8009AD48: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x8009AD4C: lui         $a1, 0x800E
    ctx->r5 = S32(0X800E << 16);
    // 0x8009AD50: addiu       $a1, $a1, 0x549C
    ctx->r5 = ADD32(ctx->r5, 0X549C);
    // 0x8009AD54: lui         $a2, 0xC316
    ctx->r6 = S32(0XC316 << 16);
    // 0x8009AD58: addiu       $a3, $zero, 0x0
    ctx->r7 = ADD32(0, 0X0);
    // 0x8009AD5C: jal         0x8009AC50
    // 0x8009AD60: swc1        $f4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f4.u32l;
    func_8009AC50(rdram, ctx);
        goto after_0;
    // 0x8009AD60: swc1        $f4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f4.u32l;
    after_0:
    // 0x8009AD64: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    // 0x8009AD68: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x8009AD6C: jr          $ra
    // 0x8009AD70: nop

    return;
    // 0x8009AD70: nop

;}
RECOMP_FUNC void func_8009AD74(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8009AD74: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x8009AD78: lwc1        $f0, -0x4B30($at)
    ctx->f0.u32l = MEM_W(ctx->r1, -0X4B30);
    // 0x8009AD7C: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x8009AD80: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x8009AD84: lui         $a2, 0x3EF0
    ctx->r6 = S32(0X3EF0 << 16);
    // 0x8009AD88: mfc1        $a1, $f0
    ctx->r5 = (int32_t)ctx->f0.u32l;
    // 0x8009AD8C: mfc1        $a3, $f0
    ctx->r7 = (int32_t)ctx->f0.u32l;
    // 0x8009AD90: jal         0x8009AB20
    // 0x8009AD94: ori         $a2, $a2, 0xA3D7
    ctx->r6 = ctx->r6 | 0XA3D7;
    func_8009AB20(rdram, ctx);
        goto after_0;
    // 0x8009AD94: ori         $a2, $a2, 0xA3D7
    ctx->r6 = ctx->r6 | 0XA3D7;
    after_0:
    // 0x8009AD98: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x8009AD9C: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x8009ADA0: jr          $ra
    // 0x8009ADA4: nop

    return;
    // 0x8009ADA4: nop

;}
RECOMP_FUNC void func_8009ADA8(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8009ADA8: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x8009ADAC: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x8009ADB0: sw          $a0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r4;
    // 0x8009ADB4: addiu       $t6, $zero, 0x1
    ctx->r14 = ADD32(0, 0X1);
    // 0x8009ADB8: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x8009ADBC: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    // 0x8009ADC0: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x8009ADC4: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    // 0x8009ADC8: jal         0x80098AC4
    // 0x8009ADCC: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_80098AC4(rdram, ctx);
        goto after_0;
    // 0x8009ADCC: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_0:
    // 0x8009ADD0: lui         $a0, 0x800A
    ctx->r4 = S32(0X800A << 16);
    // 0x8009ADD4: addiu       $a0, $a0, -0x52EC
    ctx->r4 = ADD32(ctx->r4, -0X52EC);
    // 0x8009ADD8: lw          $a1, 0x20($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X20);
    // 0x8009ADDC: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x8009ADE0: jal         0x8009A460
    // 0x8009ADE4: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_8009A460(rdram, ctx);
        goto after_1;
    // 0x8009ADE4: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_1:
    // 0x8009ADE8: lui         $a1, 0x800E
    ctx->r5 = S32(0X800E << 16);
    // 0x8009ADEC: lui         $a2, 0x800E
    ctx->r6 = S32(0X800E << 16);
    // 0x8009ADF0: addiu       $a2, $a2, 0x54D0
    ctx->r6 = ADD32(ctx->r6, 0X54D0);
    // 0x8009ADF4: addiu       $a1, $a1, 0x54B0
    ctx->r5 = ADD32(ctx->r5, 0X54B0);
    // 0x8009ADF8: lw          $a0, 0x20($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X20);
    // 0x8009ADFC: jal         0x80099A00
    // 0x8009AE00: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_80099A00(rdram, ctx);
        goto after_2;
    // 0x8009AE00: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_2:
    // 0x8009AE04: lui         $t7, 0x800D
    ctx->r15 = S32(0X800D << 16);
    // 0x8009AE08: lw          $t7, 0x48DC($t7)
    ctx->r15 = MEM_W(ctx->r15, 0X48DC);
    // 0x8009AE0C: lw          $v0, 0x20($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X20);
    // 0x8009AE10: lui         $at, 0x8019
    ctx->r1 = S32(0X8019 << 16);
    // 0x8009AE14: sll         $t8, $t7, 2
    ctx->r24 = S32(ctx->r15 << 2);
    // 0x8009AE18: subu        $t8, $t8, $t7
    ctx->r24 = SUB32(ctx->r24, ctx->r15);
    // 0x8009AE1C: sll         $t8, $t8, 3
    ctx->r24 = S32(ctx->r24 << 3);
    // 0x8009AE20: subu        $t8, $t8, $t7
    ctx->r24 = SUB32(ctx->r24, ctx->r15);
    // 0x8009AE24: sll         $t8, $t8, 3
    ctx->r24 = S32(ctx->r24 << 3);
    // 0x8009AE28: addu        $t8, $t8, $t7
    ctx->r24 = ADD32(ctx->r24, ctx->r15);
    // 0x8009AE2C: sll         $t8, $t8, 2
    ctx->r24 = S32(ctx->r24 << 2);
    // 0x8009AE30: subu        $t8, $t8, $t7
    ctx->r24 = SUB32(ctx->r24, ctx->r15);
    // 0x8009AE34: sll         $t8, $t8, 3
    ctx->r24 = S32(ctx->r24 << 3);
    // 0x8009AE38: addu        $at, $at, $t8
    ctx->r1 = ADD32(ctx->r1, ctx->r24);
    // 0x8009AE3C: lwc1        $f4, 0x26D8($at)
    ctx->f4.u32l = MEM_W(ctx->r1, 0X26D8);
    // 0x8009AE40: lwc1        $f0, 0x4($v0)
    ctx->f0.u32l = MEM_W(ctx->r2, 0X4);
    // 0x8009AE44: lui         $at, 0x3F00
    ctx->r1 = S32(0X3F00 << 16);
    // 0x8009AE48: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x8009AE4C: sub.s       $f6, $f4, $f0
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f6.fl = ctx->f4.fl - ctx->f0.fl;
    // 0x8009AE50: mul.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = MUL_S(ctx->f6.fl, ctx->f8.fl);
    // 0x8009AE54: add.s       $f16, $f10, $f0
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f16.fl = ctx->f10.fl + ctx->f0.fl;
    // 0x8009AE58: swc1        $f16, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->f16.u32l;
    // 0x8009AE5C: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    // 0x8009AE60: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x8009AE64: jr          $ra
    // 0x8009AE68: nop

    return;
    // 0x8009AE68: nop

;}
RECOMP_FUNC void func_8009AE6C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8009AE6C: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x8009AE70: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x8009AE74: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    // 0x8009AE78: addiu       $a0, $zero, 0x89
    ctx->r4 = ADD32(0, 0X89);
    // 0x8009AE7C: jal         0x8009A404
    // 0x8009AE80: addiu       $a1, $zero, 0x6
    ctx->r5 = ADD32(0, 0X6);
    func_8009A404(rdram, ctx);
        goto after_0;
    // 0x8009AE80: addiu       $a1, $zero, 0x6
    ctx->r5 = ADD32(0, 0X6);
    after_0:
    // 0x8009AE84: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x8009AE88: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x8009AE8C: jr          $ra
    // 0x8009AE90: nop

    return;
    // 0x8009AE90: nop

;}
RECOMP_FUNC void func_8009AE94(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8009AE94: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x8009AE98: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x8009AE9C: sw          $a0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r4;
    // 0x8009AEA0: addiu       $t6, $zero, 0x1
    ctx->r14 = ADD32(0, 0X1);
    // 0x8009AEA4: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x8009AEA8: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    // 0x8009AEAC: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x8009AEB0: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    // 0x8009AEB4: jal         0x80098AC4
    // 0x8009AEB8: addiu       $a3, $zero, 0x1
    ctx->r7 = ADD32(0, 0X1);
    func_80098AC4(rdram, ctx);
        goto after_0;
    // 0x8009AEB8: addiu       $a3, $zero, 0x1
    ctx->r7 = ADD32(0, 0X1);
    after_0:
    // 0x8009AEBC: lui         $a0, 0x800A
    ctx->r4 = S32(0X800A << 16);
    // 0x8009AEC0: addiu       $a0, $a0, -0x52EC
    ctx->r4 = ADD32(ctx->r4, -0X52EC);
    // 0x8009AEC4: lw          $a1, 0x20($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X20);
    // 0x8009AEC8: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x8009AECC: jal         0x8009A460
    // 0x8009AED0: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_8009A460(rdram, ctx);
        goto after_1;
    // 0x8009AED0: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_1:
    // 0x8009AED4: lui         $a0, 0x800A
    ctx->r4 = S32(0X800A << 16);
    // 0x8009AED8: addiu       $a0, $a0, -0x52C4
    ctx->r4 = ADD32(ctx->r4, -0X52C4);
    // 0x8009AEDC: lw          $a1, 0x20($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X20);
    // 0x8009AEE0: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x8009AEE4: jal         0x8009A460
    // 0x8009AEE8: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_8009A460(rdram, ctx);
        goto after_2;
    // 0x8009AEE8: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_2:
    // 0x8009AEEC: lui         $a0, 0x800A
    ctx->r4 = S32(0X800A << 16);
    // 0x8009AEF0: addiu       $a0, $a0, -0x528C
    ctx->r4 = ADD32(ctx->r4, -0X528C);
    // 0x8009AEF4: lw          $a1, 0x20($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X20);
    // 0x8009AEF8: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x8009AEFC: jal         0x8009A460
    // 0x8009AF00: addiu       $a3, $zero, -0x1
    ctx->r7 = ADD32(0, -0X1);
    func_8009A460(rdram, ctx);
        goto after_3;
    // 0x8009AF00: addiu       $a3, $zero, -0x1
    ctx->r7 = ADD32(0, -0X1);
    after_3:
    // 0x8009AF04: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    // 0x8009AF08: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x8009AF0C: jr          $ra
    // 0x8009AF10: nop

    return;
    // 0x8009AF10: nop

;}
RECOMP_FUNC void func_8009AF14(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8009AF14: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x8009AF18: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x8009AF1C: jal         0x8009ADA8
    // 0x8009AF20: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    func_8009ADA8(rdram, ctx);
        goto after_0;
    // 0x8009AF20: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    after_0:
    // 0x8009AF24: lui         $a0, 0x800A
    ctx->r4 = S32(0X800A << 16);
    // 0x8009AF28: addiu       $a0, $a0, -0x55DC
    ctx->r4 = ADD32(ctx->r4, -0X55DC);
    // 0x8009AF2C: lw          $a1, 0x18($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X18);
    // 0x8009AF30: addiu       $a2, $zero, 0x1E
    ctx->r6 = ADD32(0, 0X1E);
    // 0x8009AF34: jal         0x8009A460
    // 0x8009AF38: addiu       $a3, $zero, -0x1
    ctx->r7 = ADD32(0, -0X1);
    func_8009A460(rdram, ctx);
        goto after_1;
    // 0x8009AF38: addiu       $a3, $zero, -0x1
    ctx->r7 = ADD32(0, -0X1);
    after_1:
    // 0x8009AF3C: lui         $a0, 0x800A
    ctx->r4 = S32(0X800A << 16);
    // 0x8009AF40: addiu       $a0, $a0, -0x5194
    ctx->r4 = ADD32(ctx->r4, -0X5194);
    // 0x8009AF44: lw          $a1, 0x18($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X18);
    // 0x8009AF48: addiu       $a2, $zero, 0x50
    ctx->r6 = ADD32(0, 0X50);
    // 0x8009AF4C: jal         0x8009A460
    // 0x8009AF50: addiu       $a3, $zero, 0x50
    ctx->r7 = ADD32(0, 0X50);
    func_8009A460(rdram, ctx);
        goto after_2;
    // 0x8009AF50: addiu       $a3, $zero, 0x50
    ctx->r7 = ADD32(0, 0X50);
    after_2:
    // 0x8009AF54: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x8009AF58: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x8009AF5C: jr          $ra
    // 0x8009AF60: nop

    return;
    // 0x8009AF60: nop

;}
RECOMP_FUNC void func_8009AF64(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8009AF64: mtc1        $zero, $f0
    ctx->f0.u32l = 0;
    // 0x8009AF68: lui         $at, 0xC248
    ctx->r1 = S32(0XC248 << 16);
    // 0x8009AF6C: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x8009AF70: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x8009AF74: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x8009AF78: lui         $a1, 0x800E
    ctx->r5 = S32(0X800E << 16);
    // 0x8009AF7C: mfc1        $a2, $f0
    ctx->r6 = (int32_t)ctx->f0.u32l;
    // 0x8009AF80: mfc1        $a3, $f0
    ctx->r7 = (int32_t)ctx->f0.u32l;
    // 0x8009AF84: addiu       $a1, $a1, 0x5518
    ctx->r5 = ADD32(ctx->r5, 0X5518);
    // 0x8009AF88: jal         0x8009AC50
    // 0x8009AF8C: swc1        $f4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f4.u32l;
    func_8009AC50(rdram, ctx);
        goto after_0;
    // 0x8009AF8C: swc1        $f4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f4.u32l;
    after_0:
    // 0x8009AF90: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    // 0x8009AF94: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x8009AF98: jr          $ra
    // 0x8009AF9C: nop

    return;
    // 0x8009AF9C: nop

;}
RECOMP_FUNC void func_8009AFA0(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8009AFA0: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x8009AFA4: lwc1        $f0, -0x4B2C($at)
    ctx->f0.u32l = MEM_W(ctx->r1, -0X4B2C);
    // 0x8009AFA8: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x8009AFAC: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x8009AFB0: lui         $a2, 0x3EF0
    ctx->r6 = S32(0X3EF0 << 16);
    // 0x8009AFB4: mfc1        $a1, $f0
    ctx->r5 = (int32_t)ctx->f0.u32l;
    // 0x8009AFB8: mfc1        $a3, $f0
    ctx->r7 = (int32_t)ctx->f0.u32l;
    // 0x8009AFBC: ori         $a2, $a2, 0xA3D7
    ctx->r6 = ctx->r6 | 0XA3D7;
    // 0x8009AFC0: jal         0x8009AB20
    // 0x8009AFC4: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    func_8009AB20(rdram, ctx);
        goto after_0;
    // 0x8009AFC4: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    after_0:
    // 0x8009AFC8: lui         $t6, 0x800D
    ctx->r14 = S32(0X800D << 16);
    // 0x8009AFCC: lw          $t6, 0x48DC($t6)
    ctx->r14 = MEM_W(ctx->r14, 0X48DC);
    // 0x8009AFD0: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
    // 0x8009AFD4: lui         $at, 0x8019
    ctx->r1 = S32(0X8019 << 16);
    // 0x8009AFD8: sll         $t7, $t6, 2
    ctx->r15 = S32(ctx->r14 << 2);
    // 0x8009AFDC: subu        $t7, $t7, $t6
    ctx->r15 = SUB32(ctx->r15, ctx->r14);
    // 0x8009AFE0: sll         $t7, $t7, 3
    ctx->r15 = S32(ctx->r15 << 3);
    // 0x8009AFE4: subu        $t7, $t7, $t6
    ctx->r15 = SUB32(ctx->r15, ctx->r14);
    // 0x8009AFE8: sll         $t7, $t7, 3
    ctx->r15 = S32(ctx->r15 << 3);
    // 0x8009AFEC: addu        $t7, $t7, $t6
    ctx->r15 = ADD32(ctx->r15, ctx->r14);
    // 0x8009AFF0: sll         $t7, $t7, 2
    ctx->r15 = S32(ctx->r15 << 2);
    // 0x8009AFF4: subu        $t7, $t7, $t6
    ctx->r15 = SUB32(ctx->r15, ctx->r14);
    // 0x8009AFF8: sll         $t7, $t7, 3
    ctx->r15 = S32(ctx->r15 << 3);
    // 0x8009AFFC: addu        $at, $at, $t7
    ctx->r1 = ADD32(ctx->r1, ctx->r15);
    // 0x8009B000: lwc1        $f4, 0x26D8($at)
    ctx->f4.u32l = MEM_W(ctx->r1, 0X26D8);
    // 0x8009B004: lwc1        $f0, 0x10($a0)
    ctx->f0.u32l = MEM_W(ctx->r4, 0X10);
    // 0x8009B008: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x8009B00C: lwc1        $f8, -0x4B28($at)
    ctx->f8.u32l = MEM_W(ctx->r1, -0X4B28);
    // 0x8009B010: sub.s       $f6, $f4, $f0
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f6.fl = ctx->f4.fl - ctx->f0.fl;
    // 0x8009B014: mul.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = MUL_S(ctx->f6.fl, ctx->f8.fl);
    // 0x8009B018: add.s       $f16, $f10, $f0
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f16.fl = ctx->f10.fl + ctx->f0.fl;
    // 0x8009B01C: swc1        $f16, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->f16.u32l;
    // 0x8009B020: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x8009B024: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x8009B028: jr          $ra
    // 0x8009B02C: nop

    return;
    // 0x8009B02C: nop

;}
RECOMP_FUNC void func_8009B030(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8009B030: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x8009B034: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x8009B038: sw          $a0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r4;
    // 0x8009B03C: addiu       $t6, $zero, 0x1
    ctx->r14 = ADD32(0, 0X1);
    // 0x8009B040: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x8009B044: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    // 0x8009B048: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x8009B04C: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    // 0x8009B050: jal         0x80098AC4
    // 0x8009B054: addiu       $a3, $zero, 0x1
    ctx->r7 = ADD32(0, 0X1);
    func_80098AC4(rdram, ctx);
        goto after_0;
    // 0x8009B054: addiu       $a3, $zero, 0x1
    ctx->r7 = ADD32(0, 0X1);
    after_0:
    // 0x8009B058: lui         $a0, 0x800A
    ctx->r4 = S32(0X800A << 16);
    // 0x8009B05C: addiu       $a0, $a0, -0x52EC
    ctx->r4 = ADD32(ctx->r4, -0X52EC);
    // 0x8009B060: lw          $a1, 0x20($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X20);
    // 0x8009B064: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x8009B068: jal         0x8009A460
    // 0x8009B06C: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_8009A460(rdram, ctx);
        goto after_1;
    // 0x8009B06C: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_1:
    // 0x8009B070: lui         $a0, 0x800A
    ctx->r4 = S32(0X800A << 16);
    // 0x8009B074: addiu       $a0, $a0, -0x509C
    ctx->r4 = ADD32(ctx->r4, -0X509C);
    // 0x8009B078: lw          $a1, 0x20($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X20);
    // 0x8009B07C: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x8009B080: jal         0x8009A460
    // 0x8009B084: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_8009A460(rdram, ctx);
        goto after_2;
    // 0x8009B084: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_2:
    // 0x8009B088: lui         $a0, 0x800A
    ctx->r4 = S32(0X800A << 16);
    // 0x8009B08C: addiu       $a0, $a0, -0x5060
    ctx->r4 = ADD32(ctx->r4, -0X5060);
    // 0x8009B090: lw          $a1, 0x20($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X20);
    // 0x8009B094: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x8009B098: jal         0x8009A460
    // 0x8009B09C: addiu       $a3, $zero, -0x1
    ctx->r7 = ADD32(0, -0X1);
    func_8009A460(rdram, ctx);
        goto after_3;
    // 0x8009B09C: addiu       $a3, $zero, -0x1
    ctx->r7 = ADD32(0, -0X1);
    after_3:
    // 0x8009B0A0: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x8009B0A4: addiu       $v0, $v0, -0x1390
    ctx->r2 = ADD32(ctx->r2, -0X1390);
    // 0x8009B0A8: lui         $at, 0x41A0
    ctx->r1 = S32(0X41A0 << 16);
    // 0x8009B0AC: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x8009B0B0: lwc1        $f4, 0x18($v0)
    ctx->f4.u32l = MEM_W(ctx->r2, 0X18);
    // 0x8009B0B4: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    // 0x8009B0B8: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x8009B0BC: sub.s       $f8, $f4, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = ctx->f4.fl - ctx->f6.fl;
    // 0x8009B0C0: jr          $ra
    // 0x8009B0C4: swc1        $f8, 0x18($v0)
    MEM_W(0X18, ctx->r2) = ctx->f8.u32l;
    return;
    // 0x8009B0C4: swc1        $f8, 0x18($v0)
    MEM_W(0X18, ctx->r2) = ctx->f8.u32l;
;}
RECOMP_FUNC void func_8009B0C8(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8009B0C8: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x8009B0CC: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x8009B0D0: jal         0x8009ADA8
    // 0x8009B0D4: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    func_8009ADA8(rdram, ctx);
        goto after_0;
    // 0x8009B0D4: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    after_0:
    // 0x8009B0D8: lui         $a0, 0x800A
    ctx->r4 = S32(0X800A << 16);
    // 0x8009B0DC: addiu       $a0, $a0, -0x5194
    ctx->r4 = ADD32(ctx->r4, -0X5194);
    // 0x8009B0E0: lw          $a1, 0x18($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X18);
    // 0x8009B0E4: addiu       $a2, $zero, 0x3C
    ctx->r6 = ADD32(0, 0X3C);
    // 0x8009B0E8: jal         0x8009A460
    // 0x8009B0EC: addiu       $a3, $zero, 0x3C
    ctx->r7 = ADD32(0, 0X3C);
    func_8009A460(rdram, ctx);
        goto after_1;
    // 0x8009B0EC: addiu       $a3, $zero, 0x3C
    ctx->r7 = ADD32(0, 0X3C);
    after_1:
    // 0x8009B0F0: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x8009B0F4: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x8009B0F8: jr          $ra
    // 0x8009B0FC: nop

    return;
    // 0x8009B0FC: nop

;}
RECOMP_FUNC void func_8009B100(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8009B100: jr          $ra
    // 0x8009B104: nop

    return;
    // 0x8009B104: nop

;}
RECOMP_FUNC void func_8009B108(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8009B108: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x8009B10C: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x8009B110: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    // 0x8009B114: addiu       $a0, $zero, 0x89
    ctx->r4 = ADD32(0, 0X89);
    // 0x8009B118: jal         0x8009A404
    // 0x8009B11C: addiu       $a1, $zero, 0x6
    ctx->r5 = ADD32(0, 0X6);
    func_8009A404(rdram, ctx);
        goto after_0;
    // 0x8009B11C: addiu       $a1, $zero, 0x6
    ctx->r5 = ADD32(0, 0X6);
    after_0:
    // 0x8009B120: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x8009B124: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x8009B128: jr          $ra
    // 0x8009B12C: nop

    return;
    // 0x8009B12C: nop

;}
RECOMP_FUNC void func_8009B130(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8009B130: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x8009B134: sw          $a0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r4;
    // 0x8009B138: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x8009B13C: lui         $a0, 0x800E
    ctx->r4 = S32(0X800E << 16);
    // 0x8009B140: jal         0x800988D8
    // 0x8009B144: lw          $a0, 0x5138($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X5138);
    func_800988D8(rdram, ctx);
        goto after_0;
    // 0x8009B144: lw          $a0, 0x5138($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X5138);
    after_0:
    // 0x8009B148: addiu       $t6, $zero, 0x1
    ctx->r14 = ADD32(0, 0X1);
    // 0x8009B14C: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x8009B150: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    // 0x8009B154: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x8009B158: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    // 0x8009B15C: jal         0x80098AC4
    // 0x8009B160: addiu       $a3, $zero, 0x1
    ctx->r7 = ADD32(0, 0X1);
    func_80098AC4(rdram, ctx);
        goto after_1;
    // 0x8009B160: addiu       $a3, $zero, 0x1
    ctx->r7 = ADD32(0, 0X1);
    after_1:
    // 0x8009B164: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    // 0x8009B168: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x8009B16C: sb          $zero, 0x5148($at)
    MEM_B(0X5148, ctx->r1) = 0;
    // 0x8009B170: jr          $ra
    // 0x8009B174: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    return;
    // 0x8009B174: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
;}
RECOMP_FUNC void func_8009B178(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8009B178: lui         $t7, 0x800E
    ctx->r15 = S32(0X800E << 16);
    // 0x8009B17C: lw          $t7, 0x5138($t7)
    ctx->r15 = MEM_W(ctx->r15, 0X5138);
    // 0x8009B180: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x8009B184: addiu       $t6, $zero, 0x3FFF
    ctx->r14 = ADD32(0, 0X3FFF);
    // 0x8009B188: sll         $t8, $t7, 1
    ctx->r24 = S32(ctx->r15 << 1);
    // 0x8009B18C: addu        $at, $at, $t8
    ctx->r1 = ADD32(ctx->r1, ctx->r24);
    // 0x8009B190: sw          $a0, 0x0($sp)
    MEM_W(0X0, ctx->r29) = ctx->r4;
    // 0x8009B194: jr          $ra
    // 0x8009B198: sh          $t6, -0x1568($at)
    MEM_H(-0X1568, ctx->r1) = ctx->r14;
    return;
    // 0x8009B198: sh          $t6, -0x1568($at)
    MEM_H(-0X1568, ctx->r1) = ctx->r14;
;}
RECOMP_FUNC void func_8009B19C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8009B19C: lui         $t6, 0x800E
    ctx->r14 = S32(0X800E << 16);
    // 0x8009B1A0: lw          $t6, 0x5138($t6)
    ctx->r14 = MEM_W(ctx->r14, 0X5138);
    // 0x8009B1A4: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x8009B1A8: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x8009B1AC: sll         $t7, $t6, 2
    ctx->r15 = S32(ctx->r14 << 2);
    // 0x8009B1B0: addu        $v0, $v0, $t7
    ctx->r2 = ADD32(ctx->r2, ctx->r15);
    // 0x8009B1B4: lw          $v0, -0xFA8($v0)
    ctx->r2 = MEM_W(ctx->r2, -0XFA8);
    // 0x8009B1B8: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    // 0x8009B1BC: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x8009B1C0: beq         $v0, $zero, L_8009B1D8
    if (ctx->r2 == 0) {
        // 0x8009B1C4: lui         $a0, 0x800A
        ctx->r4 = S32(0X800A << 16);
            goto L_8009B1D8;
    }
    // 0x8009B1C4: lui         $a0, 0x800A
    ctx->r4 = S32(0X800A << 16);
    // 0x8009B1C8: lui         $at, 0x4234
    ctx->r1 = S32(0X4234 << 16);
    // 0x8009B1CC: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x8009B1D0: nop

    // 0x8009B1D4: swc1        $f4, 0x88($v0)
    MEM_W(0X88, ctx->r2) = ctx->f4.u32l;
L_8009B1D8:
    // 0x8009B1D8: addiu       $a0, $a0, -0x4ED0
    ctx->r4 = ADD32(ctx->r4, -0X4ED0);
    // 0x8009B1DC: lw          $a1, 0x18($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X18);
    // 0x8009B1E0: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x8009B1E4: jal         0x8009A460
    // 0x8009B1E8: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_8009A460(rdram, ctx);
        goto after_0;
    // 0x8009B1E8: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_0:
    // 0x8009B1EC: lui         $a1, 0x800E
    ctx->r5 = S32(0X800E << 16);
    // 0x8009B1F0: lui         $a2, 0x800E
    ctx->r6 = S32(0X800E << 16);
    // 0x8009B1F4: addiu       $a2, $a2, 0x557C
    ctx->r6 = ADD32(ctx->r6, 0X557C);
    // 0x8009B1F8: addiu       $a1, $a1, 0x552C
    ctx->r5 = ADD32(ctx->r5, 0X552C);
    // 0x8009B1FC: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
    // 0x8009B200: jal         0x80099A00
    // 0x8009B204: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_80099A00(rdram, ctx);
        goto after_1;
    // 0x8009B204: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_1:
    // 0x8009B208: lui         $t8, 0x800E
    ctx->r24 = S32(0X800E << 16);
    // 0x8009B20C: lbu         $t8, 0x5148($t8)
    ctx->r24 = MEM_BU(ctx->r24, 0X5148);
    // 0x8009B210: beq         $t8, $zero, L_8009B228
    if (ctx->r24 == 0) {
        // 0x8009B214: nop
    
            goto L_8009B228;
    }
    // 0x8009B214: nop

    // 0x8009B218: jal         0x8009B178
    // 0x8009B21C: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
    func_8009B178(rdram, ctx);
        goto after_2;
    // 0x8009B21C: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
    after_2:
    // 0x8009B220: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x8009B224: sb          $zero, 0x5148($at)
    MEM_B(0X5148, ctx->r1) = 0;
L_8009B228:
    // 0x8009B228: lui         $a0, 0x800A
    ctx->r4 = S32(0X800A << 16);
    // 0x8009B22C: addiu       $a0, $a0, -0x5684
    ctx->r4 = ADD32(ctx->r4, -0X5684);
    // 0x8009B230: lw          $a1, 0x18($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X18);
    // 0x8009B234: addiu       $a2, $zero, 0xA0
    ctx->r6 = ADD32(0, 0XA0);
    // 0x8009B238: jal         0x8009A460
    // 0x8009B23C: addiu       $a3, $zero, -0x1
    ctx->r7 = ADD32(0, -0X1);
    func_8009A460(rdram, ctx);
        goto after_3;
    // 0x8009B23C: addiu       $a3, $zero, -0x1
    ctx->r7 = ADD32(0, -0X1);
    after_3:
    // 0x8009B240: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x8009B244: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x8009B248: jr          $ra
    // 0x8009B24C: nop

    return;
    // 0x8009B24C: nop

;}
RECOMP_FUNC void func_8009B250(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8009B250: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x8009B254: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    // 0x8009B258: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x8009B25C: lui         $a0, 0x800A
    ctx->r4 = S32(0X800A << 16);
    // 0x8009B260: addiu       $a0, $a0, -0x4ED0
    ctx->r4 = ADD32(ctx->r4, -0X4ED0);
    // 0x8009B264: lw          $a1, 0x18($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X18);
    // 0x8009B268: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x8009B26C: jal         0x8009A460
    // 0x8009B270: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_8009A460(rdram, ctx);
        goto after_0;
    // 0x8009B270: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_0:
    // 0x8009B274: lui         $a1, 0x800E
    ctx->r5 = S32(0X800E << 16);
    // 0x8009B278: lui         $a2, 0x800E
    ctx->r6 = S32(0X800E << 16);
    // 0x8009B27C: addiu       $a2, $a2, 0x55EC
    ctx->r6 = ADD32(ctx->r6, 0X55EC);
    // 0x8009B280: addiu       $a1, $a1, 0x55CC
    ctx->r5 = ADD32(ctx->r5, 0X55CC);
    // 0x8009B284: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
    // 0x8009B288: jal         0x80099A00
    // 0x8009B28C: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_80099A00(rdram, ctx);
        goto after_1;
    // 0x8009B28C: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_1:
    // 0x8009B290: lui         $a0, 0x800A
    ctx->r4 = S32(0X800A << 16);
    // 0x8009B294: addiu       $a0, $a0, -0x5684
    ctx->r4 = ADD32(ctx->r4, -0X5684);
    // 0x8009B298: lw          $a1, 0x18($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X18);
    // 0x8009B29C: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x8009B2A0: jal         0x8009A460
    // 0x8009B2A4: addiu       $a3, $zero, -0x1
    ctx->r7 = ADD32(0, -0X1);
    func_8009A460(rdram, ctx);
        goto after_2;
    // 0x8009B2A4: addiu       $a3, $zero, -0x1
    ctx->r7 = ADD32(0, -0X1);
    after_2:
    // 0x8009B2A8: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x8009B2AC: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x8009B2B0: jr          $ra
    // 0x8009B2B4: nop

    return;
    // 0x8009B2B4: nop

;}
RECOMP_FUNC void func_8009B2B8(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8009B2B8: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x8009B2BC: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x8009B2C0: sw          $a0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r4;
    // 0x8009B2C4: addiu       $t6, $zero, 0x1
    ctx->r14 = ADD32(0, 0X1);
    // 0x8009B2C8: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x8009B2CC: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    // 0x8009B2D0: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x8009B2D4: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    // 0x8009B2D8: jal         0x80098AC4
    // 0x8009B2DC: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_80098AC4(rdram, ctx);
        goto after_0;
    // 0x8009B2DC: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_0:
    // 0x8009B2E0: lui         $a0, 0x800A
    ctx->r4 = S32(0X800A << 16);
    // 0x8009B2E4: addiu       $a0, $a0, -0x4ED0
    ctx->r4 = ADD32(ctx->r4, -0X4ED0);
    // 0x8009B2E8: lw          $a1, 0x20($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X20);
    // 0x8009B2EC: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x8009B2F0: jal         0x8009A460
    // 0x8009B2F4: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_8009A460(rdram, ctx);
        goto after_1;
    // 0x8009B2F4: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_1:
    // 0x8009B2F8: lui         $a1, 0x800E
    ctx->r5 = S32(0X800E << 16);
    // 0x8009B2FC: lui         $a2, 0x800E
    ctx->r6 = S32(0X800E << 16);
    // 0x8009B300: addiu       $a2, $a2, 0x5620
    ctx->r6 = ADD32(ctx->r6, 0X5620);
    // 0x8009B304: addiu       $a1, $a1, 0x560C
    ctx->r5 = ADD32(ctx->r5, 0X560C);
    // 0x8009B308: lw          $a0, 0x20($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X20);
    // 0x8009B30C: jal         0x80099A00
    // 0x8009B310: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_80099A00(rdram, ctx);
        goto after_2;
    // 0x8009B310: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_2:
    // 0x8009B314: lui         $a0, 0x800A
    ctx->r4 = S32(0X800A << 16);
    // 0x8009B318: addiu       $a0, $a0, -0x5684
    ctx->r4 = ADD32(ctx->r4, -0X5684);
    // 0x8009B31C: lw          $a1, 0x20($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X20);
    // 0x8009B320: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x8009B324: jal         0x8009A460
    // 0x8009B328: addiu       $a3, $zero, -0x1
    ctx->r7 = ADD32(0, -0X1);
    func_8009A460(rdram, ctx);
        goto after_3;
    // 0x8009B328: addiu       $a3, $zero, -0x1
    ctx->r7 = ADD32(0, -0X1);
    after_3:
    // 0x8009B32C: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    // 0x8009B330: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x8009B334: jr          $ra
    // 0x8009B338: nop

    return;
    // 0x8009B338: nop

;}
RECOMP_FUNC void func_8009B33C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8009B33C: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x8009B340: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x8009B344: sw          $a0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r4;
    // 0x8009B348: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    // 0x8009B34C: sw          $zero, 0x10($sp)
    MEM_W(0X10, ctx->r29) = 0;
    // 0x8009B350: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x8009B354: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x8009B358: jal         0x80098AC4
    // 0x8009B35C: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_80098AC4(rdram, ctx);
        goto after_0;
    // 0x8009B35C: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_0:
    // 0x8009B360: lui         $a0, 0x800A
    ctx->r4 = S32(0X800A << 16);
    // 0x8009B364: addiu       $a0, $a0, -0x4ED0
    ctx->r4 = ADD32(ctx->r4, -0X4ED0);
    // 0x8009B368: lw          $a1, 0x20($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X20);
    // 0x8009B36C: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x8009B370: jal         0x8009A460
    // 0x8009B374: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_8009A460(rdram, ctx);
        goto after_1;
    // 0x8009B374: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_1:
    // 0x8009B378: lui         $a1, 0x800E
    ctx->r5 = S32(0X800E << 16);
    // 0x8009B37C: lui         $a2, 0x800E
    ctx->r6 = S32(0X800E << 16);
    // 0x8009B380: addiu       $a2, $a2, 0x5648
    ctx->r6 = ADD32(ctx->r6, 0X5648);
    // 0x8009B384: addiu       $a1, $a1, 0x5634
    ctx->r5 = ADD32(ctx->r5, 0X5634);
    // 0x8009B388: lw          $a0, 0x20($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X20);
    // 0x8009B38C: jal         0x80099A00
    // 0x8009B390: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_80099A00(rdram, ctx);
        goto after_2;
    // 0x8009B390: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_2:
    // 0x8009B394: lui         $a1, 0x800D
    ctx->r5 = S32(0X800D << 16);
    // 0x8009B398: lw          $a1, 0x48DC($a1)
    ctx->r5 = MEM_W(ctx->r5, 0X48DC);
    // 0x8009B39C: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x8009B3A0: lwc1        $f0, -0x4B24($at)
    ctx->f0.u32l = MEM_W(ctx->r1, -0X4B24);
    // 0x8009B3A4: sll         $t6, $a1, 2
    ctx->r14 = S32(ctx->r5 << 2);
    // 0x8009B3A8: lui         $t7, 0x801D
    ctx->r15 = S32(0X801D << 16);
    // 0x8009B3AC: subu        $t6, $t6, $a1
    ctx->r14 = SUB32(ctx->r14, ctx->r5);
    // 0x8009B3B0: sll         $t6, $t6, 3
    ctx->r14 = S32(ctx->r14 << 3);
    // 0x8009B3B4: addiu       $t7, $t7, -0x1008
    ctx->r15 = ADD32(ctx->r15, -0X1008);
    // 0x8009B3B8: mfc1        $a2, $f0
    ctx->r6 = (int32_t)ctx->f0.u32l;
    // 0x8009B3BC: addu        $a0, $t6, $t7
    ctx->r4 = ADD32(ctx->r14, ctx->r15);
    // 0x8009B3C0: addiu       $a3, $zero, 0x0
    ctx->r7 = ADD32(0, 0X0);
    // 0x8009B3C4: jal         0x800989E0
    // 0x8009B3C8: swc1        $f0, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f0.u32l;
    func_800989E0(rdram, ctx);
        goto after_3;
    // 0x8009B3C8: swc1        $f0, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f0.u32l;
    after_3:
    // 0x8009B3CC: lui         $a0, 0x800A
    ctx->r4 = S32(0X800A << 16);
    // 0x8009B3D0: addiu       $a0, $a0, -0x5684
    ctx->r4 = ADD32(ctx->r4, -0X5684);
    // 0x8009B3D4: lw          $a1, 0x20($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X20);
    // 0x8009B3D8: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x8009B3DC: jal         0x8009A460
    // 0x8009B3E0: addiu       $a3, $zero, -0x1
    ctx->r7 = ADD32(0, -0X1);
    func_8009A460(rdram, ctx);
        goto after_4;
    // 0x8009B3E0: addiu       $a3, $zero, -0x1
    ctx->r7 = ADD32(0, -0X1);
    after_4:
    // 0x8009B3E4: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    // 0x8009B3E8: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x8009B3EC: jr          $ra
    // 0x8009B3F0: nop

    return;
    // 0x8009B3F0: nop

;}
RECOMP_FUNC void func_8009B3F4(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8009B3F4: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x8009B3F8: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x8009B3FC: sw          $a0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r4;
    // 0x8009B400: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    // 0x8009B404: sw          $zero, 0x10($sp)
    MEM_W(0X10, ctx->r29) = 0;
    // 0x8009B408: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x8009B40C: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x8009B410: jal         0x80098AC4
    // 0x8009B414: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_80098AC4(rdram, ctx);
        goto after_0;
    // 0x8009B414: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_0:
    // 0x8009B418: lui         $a0, 0x800A
    ctx->r4 = S32(0X800A << 16);
    // 0x8009B41C: addiu       $a0, $a0, -0x4ED0
    ctx->r4 = ADD32(ctx->r4, -0X4ED0);
    // 0x8009B420: lw          $a1, 0x20($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X20);
    // 0x8009B424: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x8009B428: jal         0x8009A460
    // 0x8009B42C: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_8009A460(rdram, ctx);
        goto after_1;
    // 0x8009B42C: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_1:
    // 0x8009B430: lui         $a1, 0x800E
    ctx->r5 = S32(0X800E << 16);
    // 0x8009B434: lui         $a2, 0x800E
    ctx->r6 = S32(0X800E << 16);
    // 0x8009B438: addiu       $a2, $a2, 0x5670
    ctx->r6 = ADD32(ctx->r6, 0X5670);
    // 0x8009B43C: addiu       $a1, $a1, 0x565C
    ctx->r5 = ADD32(ctx->r5, 0X565C);
    // 0x8009B440: lw          $a0, 0x20($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X20);
    // 0x8009B444: jal         0x80099A00
    // 0x8009B448: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_80099A00(rdram, ctx);
        goto after_2;
    // 0x8009B448: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_2:
    // 0x8009B44C: lui         $a1, 0x800D
    ctx->r5 = S32(0X800D << 16);
    // 0x8009B450: lw          $a1, 0x48DC($a1)
    ctx->r5 = MEM_W(ctx->r5, 0X48DC);
    // 0x8009B454: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x8009B458: lwc1        $f0, -0x4B20($at)
    ctx->f0.u32l = MEM_W(ctx->r1, -0X4B20);
    // 0x8009B45C: sll         $t6, $a1, 2
    ctx->r14 = S32(ctx->r5 << 2);
    // 0x8009B460: lui         $t7, 0x801D
    ctx->r15 = S32(0X801D << 16);
    // 0x8009B464: subu        $t6, $t6, $a1
    ctx->r14 = SUB32(ctx->r14, ctx->r5);
    // 0x8009B468: sll         $t6, $t6, 3
    ctx->r14 = S32(ctx->r14 << 3);
    // 0x8009B46C: addiu       $t7, $t7, -0x1008
    ctx->r15 = ADD32(ctx->r15, -0X1008);
    // 0x8009B470: mfc1        $a2, $f0
    ctx->r6 = (int32_t)ctx->f0.u32l;
    // 0x8009B474: addu        $a0, $t6, $t7
    ctx->r4 = ADD32(ctx->r14, ctx->r15);
    // 0x8009B478: addiu       $a3, $zero, 0x0
    ctx->r7 = ADD32(0, 0X0);
    // 0x8009B47C: jal         0x800989E0
    // 0x8009B480: swc1        $f0, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f0.u32l;
    func_800989E0(rdram, ctx);
        goto after_3;
    // 0x8009B480: swc1        $f0, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f0.u32l;
    after_3:
    // 0x8009B484: lui         $a0, 0x800A
    ctx->r4 = S32(0X800A << 16);
    // 0x8009B488: addiu       $a0, $a0, -0x5684
    ctx->r4 = ADD32(ctx->r4, -0X5684);
    // 0x8009B48C: lw          $a1, 0x20($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X20);
    // 0x8009B490: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x8009B494: jal         0x8009A460
    // 0x8009B498: addiu       $a3, $zero, -0x1
    ctx->r7 = ADD32(0, -0X1);
    func_8009A460(rdram, ctx);
        goto after_4;
    // 0x8009B498: addiu       $a3, $zero, -0x1
    ctx->r7 = ADD32(0, -0X1);
    after_4:
    // 0x8009B49C: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    // 0x8009B4A0: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x8009B4A4: jr          $ra
    // 0x8009B4A8: nop

    return;
    // 0x8009B4A8: nop

;}
RECOMP_FUNC void func_8009B4AC(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8009B4AC: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x8009B4B0: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x8009B4B4: sw          $a0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r4;
    // 0x8009B4B8: addiu       $t6, $zero, 0x1
    ctx->r14 = ADD32(0, 0X1);
    // 0x8009B4BC: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x8009B4C0: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    // 0x8009B4C4: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x8009B4C8: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    // 0x8009B4CC: jal         0x80098AC4
    // 0x8009B4D0: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_80098AC4(rdram, ctx);
        goto after_0;
    // 0x8009B4D0: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_0:
    // 0x8009B4D4: lui         $a0, 0x800A
    ctx->r4 = S32(0X800A << 16);
    // 0x8009B4D8: addiu       $a0, $a0, -0x4ED0
    ctx->r4 = ADD32(ctx->r4, -0X4ED0);
    // 0x8009B4DC: lw          $a1, 0x20($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X20);
    // 0x8009B4E0: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x8009B4E4: jal         0x8009A460
    // 0x8009B4E8: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_8009A460(rdram, ctx);
        goto after_1;
    // 0x8009B4E8: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_1:
    // 0x8009B4EC: lui         $a1, 0x800E
    ctx->r5 = S32(0X800E << 16);
    // 0x8009B4F0: lui         $a2, 0x800E
    ctx->r6 = S32(0X800E << 16);
    // 0x8009B4F4: addiu       $a2, $a2, 0x5698
    ctx->r6 = ADD32(ctx->r6, 0X5698);
    // 0x8009B4F8: addiu       $a1, $a1, 0x5684
    ctx->r5 = ADD32(ctx->r5, 0X5684);
    // 0x8009B4FC: lw          $a0, 0x20($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X20);
    // 0x8009B500: jal         0x80099A00
    // 0x8009B504: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_80099A00(rdram, ctx);
        goto after_2;
    // 0x8009B504: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_2:
    // 0x8009B508: lui         $a0, 0x800A
    ctx->r4 = S32(0X800A << 16);
    // 0x8009B50C: addiu       $a0, $a0, -0x5684
    ctx->r4 = ADD32(ctx->r4, -0X5684);
    // 0x8009B510: lw          $a1, 0x20($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X20);
    // 0x8009B514: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x8009B518: jal         0x8009A460
    // 0x8009B51C: addiu       $a3, $zero, -0x1
    ctx->r7 = ADD32(0, -0X1);
    func_8009A460(rdram, ctx);
        goto after_3;
    // 0x8009B51C: addiu       $a3, $zero, -0x1
    ctx->r7 = ADD32(0, -0X1);
    after_3:
    // 0x8009B520: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    // 0x8009B524: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x8009B528: jr          $ra
    // 0x8009B52C: nop

    return;
    // 0x8009B52C: nop

;}
RECOMP_FUNC void func_8009B530(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8009B530: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x8009B534: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    // 0x8009B538: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x8009B53C: lui         $a0, 0x801D
    ctx->r4 = S32(0X801D << 16);
    // 0x8009B540: addiu       $a0, $a0, -0x1390
    ctx->r4 = ADD32(ctx->r4, -0X1390);
    // 0x8009B544: lui         $a1, 0x4260
    ctx->r5 = S32(0X4260 << 16);
    // 0x8009B548: lui         $a2, 0x4248
    ctx->r6 = S32(0X4248 << 16);
    // 0x8009B54C: jal         0x800984F4
    // 0x8009B550: lui         $a3, 0xC36E
    ctx->r7 = S32(0XC36E << 16);
    Math_Vec3f_Set(rdram, ctx);
        goto after_0;
    // 0x8009B550: lui         $a3, 0xC36E
    ctx->r7 = S32(0XC36E << 16);
    after_0:
    // 0x8009B554: lui         $a0, 0x801D
    ctx->r4 = S32(0X801D << 16);
    // 0x8009B558: addiu       $a0, $a0, -0x1378
    ctx->r4 = ADD32(ctx->r4, -0X1378);
    // 0x8009B55C: lui         $a1, 0xC2C8
    ctx->r5 = S32(0XC2C8 << 16);
    // 0x8009B560: lui         $a2, 0xC2A0
    ctx->r6 = S32(0XC2A0 << 16);
    // 0x8009B564: jal         0x800984F4
    // 0x8009B568: lui         $a3, 0xC248
    ctx->r7 = S32(0XC248 << 16);
    Math_Vec3f_Set(rdram, ctx);
        goto after_1;
    // 0x8009B568: lui         $a3, 0xC248
    ctx->r7 = S32(0XC248 << 16);
    after_1:
    // 0x8009B56C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x8009B570: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x8009B574: jr          $ra
    // 0x8009B578: nop

    return;
    // 0x8009B578: nop

;}
RECOMP_FUNC void func_8009B57C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8009B57C: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x8009B580: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x8009B584: sw          $a0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r4;
    // 0x8009B588: addiu       $t6, $zero, 0x1
    ctx->r14 = ADD32(0, 0X1);
    // 0x8009B58C: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x8009B590: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    // 0x8009B594: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x8009B598: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    // 0x8009B59C: jal         0x80098AC4
    // 0x8009B5A0: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_80098AC4(rdram, ctx);
        goto after_0;
    // 0x8009B5A0: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_0:
    // 0x8009B5A4: lui         $a0, 0x800E
    ctx->r4 = S32(0X800E << 16);
    // 0x8009B5A8: jal         0x800988D8
    // 0x8009B5AC: lw          $a0, 0x5138($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X5138);
    func_800988D8(rdram, ctx);
        goto after_1;
    // 0x8009B5AC: lw          $a0, 0x5138($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X5138);
    after_1:
    // 0x8009B5B0: lui         $t7, 0x800D
    ctx->r15 = S32(0X800D << 16);
    // 0x8009B5B4: lw          $t7, 0x48DC($t7)
    ctx->r15 = MEM_W(ctx->r15, 0X48DC);
    // 0x8009B5B8: lui         $t9, 0x801D
    ctx->r25 = S32(0X801D << 16);
    // 0x8009B5BC: addiu       $t9, $t9, -0x1008
    ctx->r25 = ADD32(ctx->r25, -0X1008);
    // 0x8009B5C0: sll         $t8, $t7, 2
    ctx->r24 = S32(ctx->r15 << 2);
    // 0x8009B5C4: subu        $t8, $t8, $t7
    ctx->r24 = SUB32(ctx->r24, ctx->r15);
    // 0x8009B5C8: sll         $t8, $t8, 3
    ctx->r24 = S32(ctx->r24 << 3);
    // 0x8009B5CC: addu        $a1, $t8, $t9
    ctx->r5 = ADD32(ctx->r24, ctx->r25);
    // 0x8009B5D0: lui         $a0, 0x801D
    ctx->r4 = S32(0X801D << 16);
    // 0x8009B5D4: lui         $a2, 0x801D
    ctx->r6 = S32(0X801D << 16);
    // 0x8009B5D8: addiu       $a2, $a2, -0x1390
    ctx->r6 = ADD32(ctx->r6, -0X1390);
    // 0x8009B5DC: addiu       $a0, $a0, -0x1360
    ctx->r4 = ADD32(ctx->r4, -0X1360);
    // 0x8009B5E0: jal         0x8009917C
    // 0x8009B5E4: addiu       $a3, $a1, 0xC
    ctx->r7 = ADD32(ctx->r5, 0XC);
    func_8009917C(rdram, ctx);
        goto after_2;
    // 0x8009B5E4: addiu       $a3, $a1, 0xC
    ctx->r7 = ADD32(ctx->r5, 0XC);
    after_2:
    // 0x8009B5E8: lui         $t0, 0x800D
    ctx->r8 = S32(0X800D << 16);
    // 0x8009B5EC: lw          $t0, 0x48DC($t0)
    ctx->r8 = MEM_W(ctx->r8, 0X48DC);
    // 0x8009B5F0: lui         $t2, 0x801D
    ctx->r10 = S32(0X801D << 16);
    // 0x8009B5F4: addiu       $t2, $t2, -0x1008
    ctx->r10 = ADD32(ctx->r10, -0X1008);
    // 0x8009B5F8: sll         $t1, $t0, 2
    ctx->r9 = S32(ctx->r8 << 2);
    // 0x8009B5FC: subu        $t1, $t1, $t0
    ctx->r9 = SUB32(ctx->r9, ctx->r8);
    // 0x8009B600: sll         $t1, $t1, 3
    ctx->r9 = S32(ctx->r9 << 3);
    // 0x8009B604: addu        $a1, $t1, $t2
    ctx->r5 = ADD32(ctx->r9, ctx->r10);
    // 0x8009B608: lui         $a0, 0x801D
    ctx->r4 = S32(0X801D << 16);
    // 0x8009B60C: lui         $a2, 0x801D
    ctx->r6 = S32(0X801D << 16);
    // 0x8009B610: addiu       $a2, $a2, -0x1378
    ctx->r6 = ADD32(ctx->r6, -0X1378);
    // 0x8009B614: addiu       $a0, $a0, -0x1348
    ctx->r4 = ADD32(ctx->r4, -0X1348);
    // 0x8009B618: jal         0x8009917C
    // 0x8009B61C: addiu       $a3, $a1, 0xC
    ctx->r7 = ADD32(ctx->r5, 0XC);
    func_8009917C(rdram, ctx);
        goto after_3;
    // 0x8009B61C: addiu       $a3, $a1, 0xC
    ctx->r7 = ADD32(ctx->r5, 0XC);
    after_3:
    // 0x8009B620: lui         $t3, 0x8019
    ctx->r11 = S32(0X8019 << 16);
    // 0x8009B624: lw          $t3, 0x2458($t3)
    ctx->r11 = MEM_W(ctx->r11, 0X2458);
    // 0x8009B628: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x8009B62C: addiu       $v0, $v0, -0x1390
    ctx->r2 = ADD32(ctx->r2, -0X1390);
    // 0x8009B630: mtc1        $t3, $f6
    ctx->f6.u32l = ctx->r11;
    // 0x8009B634: lwc1        $f4, 0x4($v0)
    ctx->f4.u32l = MEM_W(ctx->r2, 0X4);
    // 0x8009B638: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    // 0x8009B63C: cvt.s.w     $f8, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    ctx->f8.fl = CVT_S_W(ctx->f6.u32l);
    // 0x8009B640: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x8009B644: add.s       $f10, $f4, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = ctx->f4.fl + ctx->f8.fl;
    // 0x8009B648: jr          $ra
    // 0x8009B64C: swc1        $f10, 0x34($v0)
    MEM_W(0X34, ctx->r2) = ctx->f10.u32l;
    return;
    // 0x8009B64C: swc1        $f10, 0x34($v0)
    MEM_W(0X34, ctx->r2) = ctx->f10.u32l;
;}
RECOMP_FUNC void func_8009B650(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8009B650: addiu       $sp, $sp, -0x50
    ctx->r29 = ADD32(ctx->r29, -0X50);
    // 0x8009B654: sw          $s0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r16;
    // 0x8009B658: or          $s0, $a0, $zero
    ctx->r16 = ctx->r4 | 0;
    // 0x8009B65C: sw          $a1, 0x54($sp)
    MEM_W(0X54, ctx->r29) = ctx->r5;
    // 0x8009B660: sw          $ra, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r31;
    // 0x8009B664: lui         $a1, 0x801D
    ctx->r5 = S32(0X801D << 16);
    // 0x8009B668: addiu       $a0, $a0, 0xC
    ctx->r4 = ADD32(ctx->r4, 0XC);
    // 0x8009B66C: sw          $a2, 0x58($sp)
    MEM_W(0X58, ctx->r29) = ctx->r6;
    // 0x8009B670: sw          $a0, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r4;
    // 0x8009B674: jal         0x8009852C
    // 0x8009B678: addiu       $a1, $a1, -0x1360
    ctx->r5 = ADD32(ctx->r5, -0X1360);
    Math_Vec3f_Copy(rdram, ctx);
        goto after_0;
    // 0x8009B678: addiu       $a1, $a1, -0x1360
    ctx->r5 = ADD32(ctx->r5, -0X1360);
    after_0:
    // 0x8009B67C: lui         $a1, 0x801D
    ctx->r5 = S32(0X801D << 16);
    // 0x8009B680: addiu       $a1, $a1, -0x1348
    ctx->r5 = ADD32(ctx->r5, -0X1348);
    // 0x8009B684: jal         0x8009852C
    // 0x8009B688: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    Math_Vec3f_Copy(rdram, ctx);
        goto after_1;
    // 0x8009B688: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_1:
    // 0x8009B68C: addiu       $t6, $sp, 0x30
    ctx->r14 = ADD32(ctx->r29, 0X30);
    // 0x8009B690: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x8009B694: lw          $a0, 0x28($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X28);
    // 0x8009B698: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    // 0x8009B69C: addiu       $a2, $sp, 0x2C
    ctx->r6 = ADD32(ctx->r29, 0X2C);
    // 0x8009B6A0: jal         0x80098FF8
    // 0x8009B6A4: addiu       $a3, $sp, 0x34
    ctx->r7 = ADD32(ctx->r29, 0X34);
    func_80098FF8(rdram, ctx);
        goto after_2;
    // 0x8009B6A4: addiu       $a3, $sp, 0x34
    ctx->r7 = ADD32(ctx->r29, 0X34);
    after_2:
    // 0x8009B6A8: lwc1        $f0, 0x34($sp)
    ctx->f0.u32l = MEM_W(ctx->r29, 0X34);
    // 0x8009B6AC: mtc1        $zero, $f4
    ctx->f4.u32l = 0;
    // 0x8009B6B0: lui         $at, 0x42B4
    ctx->r1 = S32(0X42B4 << 16);
    // 0x8009B6B4: c.le.s      $f4, $f0
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    c1cs = ctx->f4.fl <= ctx->f0.fl;
    // 0x8009B6B8: nop

    // 0x8009B6BC: bc1fl       L_8009B6E8
    if (!c1cs) {
        // 0x8009B6C0: lui         $at, 0x43AB
        ctx->r1 = S32(0X43AB << 16);
            goto L_8009B6E8;
    }
    goto skip_0;
    // 0x8009B6C0: lui         $at, 0x43AB
    ctx->r1 = S32(0X43AB << 16);
    skip_0:
    // 0x8009B6C4: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x8009B6C8: lui         $at, 0x43AB
    ctx->r1 = S32(0X43AB << 16);
    // 0x8009B6CC: c.le.s      $f0, $f6
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 6);
    c1cs = ctx->f0.fl <= ctx->f6.fl;
    // 0x8009B6D0: nop

    // 0x8009B6D4: bc1fl       L_8009B6E8
    if (!c1cs) {
        // 0x8009B6D8: lui         $at, 0x43AB
        ctx->r1 = S32(0X43AB << 16);
            goto L_8009B6E8;
    }
    goto skip_1;
    // 0x8009B6D8: lui         $at, 0x43AB
    ctx->r1 = S32(0X43AB << 16);
    skip_1:
    // 0x8009B6DC: mtc1        $at, $f0
    ctx->f0.u32l = ctx->r1;
    // 0x8009B6E0: nop

    // 0x8009B6E4: lui         $at, 0x43AB
    ctx->r1 = S32(0X43AB << 16);
L_8009B6E8:
    // 0x8009B6E8: mtc1        $at, $f2
    ctx->f2.u32l = ctx->r1;
    // 0x8009B6EC: lui         $at, 0x3F40
    ctx->r1 = S32(0X3F40 << 16);
    // 0x8009B6F0: c.lt.s      $f2, $f0
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 0);
    c1cs = ctx->f2.fl < ctx->f0.fl;
    // 0x8009B6F4: nop

    // 0x8009B6F8: bc1fl       L_8009B708
    if (!c1cs) {
        // 0x8009B6FC: sub.s       $f8, $f0, $f2
        CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f8.fl = ctx->f0.fl - ctx->f2.fl;
            goto L_8009B708;
    }
    goto skip_2;
    // 0x8009B6FC: sub.s       $f8, $f0, $f2
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f8.fl = ctx->f0.fl - ctx->f2.fl;
    skip_2:
    // 0x8009B700: mov.s       $f0, $f2
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    ctx->f0.fl = ctx->f2.fl;
    // 0x8009B704: sub.s       $f8, $f0, $f2
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f8.fl = ctx->f0.fl - ctx->f2.fl;
L_8009B708:
    // 0x8009B708: mtc1        $at, $f10
    ctx->f10.u32l = ctx->r1;
    // 0x8009B70C: lwc1        $f18, 0x30($sp)
    ctx->f18.u32l = MEM_W(ctx->r29, 0X30);
    // 0x8009B710: lw          $a0, 0x28($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X28);
    // 0x8009B714: mul.s       $f16, $f8, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f16.fl = MUL_S(ctx->f8.fl, ctx->f10.fl);
    // 0x8009B718: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    // 0x8009B71C: lw          $a2, 0x2C($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X2C);
    // 0x8009B720: swc1        $f18, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f18.u32l;
    // 0x8009B724: add.s       $f0, $f16, $f2
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f0.fl = ctx->f16.fl + ctx->f2.fl;
    // 0x8009B728: mfc1        $a3, $f0
    ctx->r7 = (int32_t)ctx->f0.u32l;
    // 0x8009B72C: jal         0x800990A8
    // 0x8009B730: swc1        $f0, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->f0.u32l;
    func_800990A8(rdram, ctx);
        goto after_3;
    // 0x8009B730: swc1        $f0, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->f0.u32l;
    after_3:
    // 0x8009B734: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    // 0x8009B738: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x8009B73C: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    // 0x8009B740: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    // 0x8009B744: jal         0x80098AC4
    // 0x8009B748: sw          $zero, 0x10($sp)
    MEM_W(0X10, ctx->r29) = 0;
    func_80098AC4(rdram, ctx);
        goto after_4;
    // 0x8009B748: sw          $zero, 0x10($sp)
    MEM_W(0X10, ctx->r29) = 0;
    after_4:
    // 0x8009B74C: lui         $t7, 0x800D
    ctx->r15 = S32(0X800D << 16);
    // 0x8009B750: lw          $t7, 0x48DC($t7)
    ctx->r15 = MEM_W(ctx->r15, 0X48DC);
    // 0x8009B754: lui         $t9, 0x801D
    ctx->r25 = S32(0X801D << 16);
    // 0x8009B758: addiu       $t9, $t9, -0x1008
    ctx->r25 = ADD32(ctx->r25, -0X1008);
    // 0x8009B75C: sll         $t8, $t7, 2
    ctx->r24 = S32(ctx->r15 << 2);
    // 0x8009B760: subu        $t8, $t8, $t7
    ctx->r24 = SUB32(ctx->r24, ctx->r15);
    // 0x8009B764: sll         $t8, $t8, 3
    ctx->r24 = S32(ctx->r24 << 3);
    // 0x8009B768: addu        $a1, $t8, $t9
    ctx->r5 = ADD32(ctx->r24, ctx->r25);
    // 0x8009B76C: lui         $a2, 0x801D
    ctx->r6 = S32(0X801D << 16);
    // 0x8009B770: addiu       $a2, $a2, -0x1378
    ctx->r6 = ADD32(ctx->r6, -0X1378);
    // 0x8009B774: addiu       $a3, $a1, 0xC
    ctx->r7 = ADD32(ctx->r5, 0XC);
    // 0x8009B778: jal         0x8009917C
    // 0x8009B77C: addiu       $a0, $sp, 0x38
    ctx->r4 = ADD32(ctx->r29, 0X38);
    func_8009917C(rdram, ctx);
        goto after_5;
    // 0x8009B77C: addiu       $a0, $sp, 0x38
    ctx->r4 = ADD32(ctx->r29, 0X38);
    after_5:
    // 0x8009B780: lui         $a0, 0x801D
    ctx->r4 = S32(0X801D << 16);
    // 0x8009B784: lui         $a2, 0x3E99
    ctx->r6 = S32(0X3E99 << 16);
    // 0x8009B788: ori         $a2, $a2, 0x999A
    ctx->r6 = ctx->r6 | 0X999A;
    // 0x8009B78C: addiu       $a0, $a0, -0x1348
    ctx->r4 = ADD32(ctx->r4, -0X1348);
    // 0x8009B790: jal         0x80098714
    // 0x8009B794: lw          $a1, 0x38($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X38);
    func_80098714(rdram, ctx);
        goto after_6;
    // 0x8009B794: lw          $a1, 0x38($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X38);
    after_6:
    // 0x8009B798: lui         $a0, 0x801D
    ctx->r4 = S32(0X801D << 16);
    // 0x8009B79C: lui         $a2, 0x3E99
    ctx->r6 = S32(0X3E99 << 16);
    // 0x8009B7A0: ori         $a2, $a2, 0x999A
    ctx->r6 = ctx->r6 | 0X999A;
    // 0x8009B7A4: addiu       $a0, $a0, -0x1340
    ctx->r4 = ADD32(ctx->r4, -0X1340);
    // 0x8009B7A8: jal         0x80098714
    // 0x8009B7AC: lw          $a1, 0x40($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X40);
    func_80098714(rdram, ctx);
        goto after_7;
    // 0x8009B7AC: lw          $a1, 0x40($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X40);
    after_7:
    // 0x8009B7B0: lwc1        $f4, 0x58($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X58);
    // 0x8009B7B4: lui         $a0, 0x801D
    ctx->r4 = S32(0X801D << 16);
    // 0x8009B7B8: lui         $a1, 0x800D
    ctx->r5 = S32(0X800D << 16);
    // 0x8009B7BC: lw          $a1, 0x48DC($a1)
    ctx->r5 = MEM_W(ctx->r5, 0X48DC);
    // 0x8009B7C0: addiu       $a0, $a0, -0x1360
    ctx->r4 = ADD32(ctx->r4, -0X1360);
    // 0x8009B7C4: lw          $a2, 0x54($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X54);
    // 0x8009B7C8: addiu       $a3, $zero, 0x0
    ctx->r7 = ADD32(0, 0X0);
    // 0x8009B7CC: jal         0x800989E0
    // 0x8009B7D0: swc1        $f4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f4.u32l;
    func_800989E0(rdram, ctx);
        goto after_8;
    // 0x8009B7D0: swc1        $f4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f4.u32l;
    after_8:
    // 0x8009B7D4: lwc1        $f6, 0x58($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X58);
    // 0x8009B7D8: lui         $a0, 0x801D
    ctx->r4 = S32(0X801D << 16);
    // 0x8009B7DC: lui         $a1, 0x800D
    ctx->r5 = S32(0X800D << 16);
    // 0x8009B7E0: lw          $a1, 0x48DC($a1)
    ctx->r5 = MEM_W(ctx->r5, 0X48DC);
    // 0x8009B7E4: addiu       $a0, $a0, -0x1348
    ctx->r4 = ADD32(ctx->r4, -0X1348);
    // 0x8009B7E8: lw          $a2, 0x54($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X54);
    // 0x8009B7EC: addiu       $a3, $zero, 0x0
    ctx->r7 = ADD32(0, 0X0);
    // 0x8009B7F0: jal         0x800989E0
    // 0x8009B7F4: swc1        $f6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f6.u32l;
    func_800989E0(rdram, ctx);
        goto after_9;
    // 0x8009B7F4: swc1        $f6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f6.u32l;
    after_9:
    // 0x8009B7F8: lui         $a0, 0x800A
    ctx->r4 = S32(0X800A << 16);
    // 0x8009B7FC: addiu       $a0, $a0, -0x55DC
    ctx->r4 = ADD32(ctx->r4, -0X55DC);
    // 0x8009B800: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    // 0x8009B804: addiu       $a2, $zero, 0xA
    ctx->r6 = ADD32(0, 0XA);
    // 0x8009B808: jal         0x8009A460
    // 0x8009B80C: addiu       $a3, $zero, -0x1
    ctx->r7 = ADD32(0, -0X1);
    func_8009A460(rdram, ctx);
        goto after_10;
    // 0x8009B80C: addiu       $a3, $zero, -0x1
    ctx->r7 = ADD32(0, -0X1);
    after_10:
    // 0x8009B810: lw          $ra, 0x24($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X24);
    // 0x8009B814: lw          $s0, 0x20($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X20);
    // 0x8009B818: addiu       $sp, $sp, 0x50
    ctx->r29 = ADD32(ctx->r29, 0X50);
    // 0x8009B81C: jr          $ra
    // 0x8009B820: nop

    return;
    // 0x8009B820: nop

;}
RECOMP_FUNC void func_8009B824(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8009B824: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x8009B828: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    // 0x8009B82C: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x8009B830: lui         $a0, 0x800A
    ctx->r4 = S32(0X800A << 16);
    // 0x8009B834: addiu       $a0, $a0, -0x4AD0
    ctx->r4 = ADD32(ctx->r4, -0X4AD0);
    // 0x8009B838: lw          $a1, 0x18($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X18);
    // 0x8009B83C: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x8009B840: jal         0x8009A460
    // 0x8009B844: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_8009A460(rdram, ctx);
        goto after_0;
    // 0x8009B844: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_0:
    // 0x8009B848: lui         $a0, 0x800A
    ctx->r4 = S32(0X800A << 16);
    // 0x8009B84C: addiu       $a0, $a0, -0x4A84
    ctx->r4 = ADD32(ctx->r4, -0X4A84);
    // 0x8009B850: lw          $a1, 0x18($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X18);
    // 0x8009B854: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x8009B858: jal         0x8009A460
    // 0x8009B85C: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_8009A460(rdram, ctx);
        goto after_1;
    // 0x8009B85C: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_1:
    // 0x8009B860: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x8009B864: lwc1        $f0, -0x4B1C($at)
    ctx->f0.u32l = MEM_W(ctx->r1, -0X4B1C);
    // 0x8009B868: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
    // 0x8009B86C: mfc1        $a1, $f0
    ctx->r5 = (int32_t)ctx->f0.u32l;
    // 0x8009B870: mfc1        $a2, $f0
    ctx->r6 = (int32_t)ctx->f0.u32l;
    // 0x8009B874: jal         0x8009B650
    // 0x8009B878: nop

    func_8009B650(rdram, ctx);
        goto after_2;
    // 0x8009B878: nop

    after_2:
    // 0x8009B87C: lui         $at, 0x4040
    ctx->r1 = S32(0X4040 << 16);
    // 0x8009B880: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x8009B884: lw          $t6, 0x18($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X18);
    // 0x8009B888: swc1        $f4, 0x18($t6)
    MEM_W(0X18, ctx->r14) = ctx->f4.u32l;
    // 0x8009B88C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x8009B890: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x8009B894: jr          $ra
    // 0x8009B898: nop

    return;
    // 0x8009B898: nop

;}
RECOMP_FUNC void func_8009B89C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8009B89C: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x8009B8A0: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    // 0x8009B8A4: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x8009B8A8: lui         $a0, 0x800A
    ctx->r4 = S32(0X800A << 16);
    // 0x8009B8AC: addiu       $a0, $a0, -0x4AD0
    ctx->r4 = ADD32(ctx->r4, -0X4AD0);
    // 0x8009B8B0: lw          $a1, 0x18($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X18);
    // 0x8009B8B4: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x8009B8B8: jal         0x8009A460
    // 0x8009B8BC: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_8009A460(rdram, ctx);
        goto after_0;
    // 0x8009B8BC: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_0:
    // 0x8009B8C0: lui         $a0, 0x800A
    ctx->r4 = S32(0X800A << 16);
    // 0x8009B8C4: addiu       $a0, $a0, -0x4A84
    ctx->r4 = ADD32(ctx->r4, -0X4A84);
    // 0x8009B8C8: lw          $a1, 0x18($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X18);
    // 0x8009B8CC: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x8009B8D0: jal         0x8009A460
    // 0x8009B8D4: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_8009A460(rdram, ctx);
        goto after_1;
    // 0x8009B8D4: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_1:
    // 0x8009B8D8: lui         $a1, 0x3E99
    ctx->r5 = S32(0X3E99 << 16);
    // 0x8009B8DC: lui         $a2, 0x3F33
    ctx->r6 = S32(0X3F33 << 16);
    // 0x8009B8E0: ori         $a2, $a2, 0x3333
    ctx->r6 = ctx->r6 | 0X3333;
    // 0x8009B8E4: ori         $a1, $a1, 0x999A
    ctx->r5 = ctx->r5 | 0X999A;
    // 0x8009B8E8: jal         0x8009B650
    // 0x8009B8EC: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
    func_8009B650(rdram, ctx);
        goto after_2;
    // 0x8009B8EC: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
    after_2:
    // 0x8009B8F0: lui         $at, 0xC080
    ctx->r1 = S32(0XC080 << 16);
    // 0x8009B8F4: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x8009B8F8: lw          $t6, 0x18($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X18);
    // 0x8009B8FC: swc1        $f4, 0x18($t6)
    MEM_W(0X18, ctx->r14) = ctx->f4.u32l;
    // 0x8009B900: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x8009B904: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x8009B908: jr          $ra
    // 0x8009B90C: nop

    return;
    // 0x8009B90C: nop

;}
RECOMP_FUNC void func_8009B910(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8009B910: lui         $t6, 0x800E
    ctx->r14 = S32(0X800E << 16);
    // 0x8009B914: lw          $t6, 0x5138($t6)
    ctx->r14 = MEM_W(ctx->r14, 0X5138);
    // 0x8009B918: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x8009B91C: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x8009B920: sll         $t7, $t6, 2
    ctx->r15 = S32(ctx->r14 << 2);
    // 0x8009B924: addu        $v0, $v0, $t7
    ctx->r2 = ADD32(ctx->r2, ctx->r15);
    // 0x8009B928: lw          $v0, -0xFA8($v0)
    ctx->r2 = MEM_W(ctx->r2, -0XFA8);
    // 0x8009B92C: sw          $a0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r4;
    // 0x8009B930: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x8009B934: beq         $v0, $zero, L_8009B94C
    if (ctx->r2 == 0) {
        // 0x8009B938: addiu       $a0, $zero, 0x1
        ctx->r4 = ADD32(0, 0X1);
            goto L_8009B94C;
    }
    // 0x8009B938: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    // 0x8009B93C: lui         $at, 0x4234
    ctx->r1 = S32(0X4234 << 16);
    // 0x8009B940: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x8009B944: nop

    // 0x8009B948: swc1        $f4, 0x88($v0)
    MEM_W(0X88, ctx->r2) = ctx->f4.u32l;
L_8009B94C:
    // 0x8009B94C: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x8009B950: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    // 0x8009B954: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    // 0x8009B958: jal         0x80098AC4
    // 0x8009B95C: sw          $zero, 0x10($sp)
    MEM_W(0X10, ctx->r29) = 0;
    func_80098AC4(rdram, ctx);
        goto after_0;
    // 0x8009B95C: sw          $zero, 0x10($sp)
    MEM_W(0X10, ctx->r29) = 0;
    after_0:
    // 0x8009B960: lui         $a0, 0x800A
    ctx->r4 = S32(0X800A << 16);
    // 0x8009B964: addiu       $a0, $a0, -0x4ED0
    ctx->r4 = ADD32(ctx->r4, -0X4ED0);
    // 0x8009B968: lw          $a1, 0x20($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X20);
    // 0x8009B96C: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x8009B970: jal         0x8009A460
    // 0x8009B974: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_8009A460(rdram, ctx);
        goto after_1;
    // 0x8009B974: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_1:
    // 0x8009B978: lui         $t8, 0x801D
    ctx->r24 = S32(0X801D << 16);
    // 0x8009B97C: lbu         $t8, -0x1558($t8)
    ctx->r24 = MEM_BU(ctx->r24, -0X1558);
    // 0x8009B980: lui         $a1, 0x800E
    ctx->r5 = S32(0X800E << 16);
    // 0x8009B984: addiu       $a1, $a1, 0x56AC
    ctx->r5 = ADD32(ctx->r5, 0X56AC);
    // 0x8009B988: bne         $t8, $zero, L_8009B9B8
    if (ctx->r24 != 0) {
        // 0x8009B98C: lui         $a2, 0x800E
        ctx->r6 = S32(0X800E << 16);
            goto L_8009B9B8;
    }
    // 0x8009B98C: lui         $a2, 0x800E
    ctx->r6 = S32(0X800E << 16);
    // 0x8009B990: lui         $t9, 0x800D
    ctx->r25 = S32(0X800D << 16);
    // 0x8009B994: lw          $t9, 0x48DC($t9)
    ctx->r25 = MEM_W(ctx->r25, 0X48DC);
    // 0x8009B998: lui         $at, 0x4325
    ctx->r1 = S32(0X4325 << 16);
    // 0x8009B99C: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x8009B9A0: sll         $t0, $t9, 2
    ctx->r8 = S32(ctx->r25 << 2);
    // 0x8009B9A4: subu        $t0, $t0, $t9
    ctx->r8 = SUB32(ctx->r8, ctx->r25);
    // 0x8009B9A8: sll         $t0, $t0, 3
    ctx->r8 = S32(ctx->r8 << 3);
    // 0x8009B9AC: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x8009B9B0: addu        $at, $at, $t0
    ctx->r1 = ADD32(ctx->r1, ctx->r8);
    // 0x8009B9B4: swc1        $f6, -0xFF8($at)
    MEM_W(-0XFF8, ctx->r1) = ctx->f6.u32l;
L_8009B9B8:
    // 0x8009B9B8: lw          $a0, 0x20($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X20);
    // 0x8009B9BC: addiu       $a2, $a2, 0x56E0
    ctx->r6 = ADD32(ctx->r6, 0X56E0);
    // 0x8009B9C0: jal         0x80099A00
    // 0x8009B9C4: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_80099A00(rdram, ctx);
        goto after_2;
    // 0x8009B9C4: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_2:
    // 0x8009B9C8: lui         $a0, 0x800A
    ctx->r4 = S32(0X800A << 16);
    // 0x8009B9CC: addiu       $a0, $a0, -0x55DC
    ctx->r4 = ADD32(ctx->r4, -0X55DC);
    // 0x8009B9D0: lw          $a1, 0x20($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X20);
    // 0x8009B9D4: addiu       $a2, $zero, 0xA
    ctx->r6 = ADD32(0, 0XA);
    // 0x8009B9D8: jal         0x8009A460
    // 0x8009B9DC: addiu       $a3, $zero, -0x1
    ctx->r7 = ADD32(0, -0X1);
    func_8009A460(rdram, ctx);
        goto after_3;
    // 0x8009B9DC: addiu       $a3, $zero, -0x1
    ctx->r7 = ADD32(0, -0X1);
    after_3:
    // 0x8009B9E0: lui         $t1, 0x800E
    ctx->r9 = S32(0X800E << 16);
    // 0x8009B9E4: lbu         $t1, 0x514C($t1)
    ctx->r9 = MEM_BU(ctx->r9, 0X514C);
    // 0x8009B9E8: lui         $a0, 0x800A
    ctx->r4 = S32(0X800A << 16);
    // 0x8009B9EC: addiu       $a0, $a0, -0x5604
    ctx->r4 = ADD32(ctx->r4, -0X5604);
    // 0x8009B9F0: beq         $t1, $zero, L_8009BA04
    if (ctx->r9 == 0) {
        // 0x8009B9F4: lw          $a1, 0x20($sp)
        ctx->r5 = MEM_W(ctx->r29, 0X20);
            goto L_8009BA04;
    }
    // 0x8009B9F4: lw          $a1, 0x20($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X20);
    // 0x8009B9F8: addiu       $a2, $zero, 0x77
    ctx->r6 = ADD32(0, 0X77);
    // 0x8009B9FC: jal         0x8009A460
    // 0x8009BA00: addiu       $a3, $zero, 0x77
    ctx->r7 = ADD32(0, 0X77);
    func_8009A460(rdram, ctx);
        goto after_4;
    // 0x8009BA00: addiu       $a3, $zero, 0x77
    ctx->r7 = ADD32(0, 0X77);
    after_4:
L_8009BA04:
    // 0x8009BA04: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    // 0x8009BA08: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x8009BA0C: jr          $ra
    // 0x8009BA10: nop

    return;
    // 0x8009BA10: nop

;}
RECOMP_FUNC void func_8009BA14(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8009BA14: lui         $t6, 0x800E
    ctx->r14 = S32(0X800E << 16);
    // 0x8009BA18: lw          $t6, 0x5138($t6)
    ctx->r14 = MEM_W(ctx->r14, 0X5138);
    // 0x8009BA1C: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x8009BA20: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x8009BA24: sll         $t7, $t6, 2
    ctx->r15 = S32(ctx->r14 << 2);
    // 0x8009BA28: addu        $v0, $v0, $t7
    ctx->r2 = ADD32(ctx->r2, ctx->r15);
    // 0x8009BA2C: lw          $v0, -0xFA8($v0)
    ctx->r2 = MEM_W(ctx->r2, -0XFA8);
    // 0x8009BA30: sw          $a0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r4;
    // 0x8009BA34: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x8009BA38: beq         $v0, $zero, L_8009BA50
    if (ctx->r2 == 0) {
        // 0x8009BA3C: lui         $a0, 0x800A
        ctx->r4 = S32(0X800A << 16);
            goto L_8009BA50;
    }
    // 0x8009BA3C: lui         $a0, 0x800A
    ctx->r4 = S32(0X800A << 16);
    // 0x8009BA40: lui         $at, 0x4234
    ctx->r1 = S32(0X4234 << 16);
    // 0x8009BA44: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x8009BA48: nop

    // 0x8009BA4C: swc1        $f4, 0x88($v0)
    MEM_W(0X88, ctx->r2) = ctx->f4.u32l;
L_8009BA50:
    // 0x8009BA50: addiu       $a0, $a0, -0x4ED0
    ctx->r4 = ADD32(ctx->r4, -0X4ED0);
    // 0x8009BA54: lw          $a1, 0x20($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X20);
    // 0x8009BA58: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x8009BA5C: jal         0x8009A460
    // 0x8009BA60: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_8009A460(rdram, ctx);
        goto after_0;
    // 0x8009BA60: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_0:
    // 0x8009BA64: lui         $a1, 0x800D
    ctx->r5 = S32(0X800D << 16);
    // 0x8009BA68: lw          $a1, 0x48DC($a1)
    ctx->r5 = MEM_W(ctx->r5, 0X48DC);
    // 0x8009BA6C: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x8009BA70: lwc1        $f0, -0x4B18($at)
    ctx->f0.u32l = MEM_W(ctx->r1, -0X4B18);
    // 0x8009BA74: sll         $t8, $a1, 2
    ctx->r24 = S32(ctx->r5 << 2);
    // 0x8009BA78: lui         $t9, 0x801D
    ctx->r25 = S32(0X801D << 16);
    // 0x8009BA7C: subu        $t8, $t8, $a1
    ctx->r24 = SUB32(ctx->r24, ctx->r5);
    // 0x8009BA80: sll         $t8, $t8, 3
    ctx->r24 = S32(ctx->r24 << 3);
    // 0x8009BA84: addiu       $t9, $t9, -0x1008
    ctx->r25 = ADD32(ctx->r25, -0X1008);
    // 0x8009BA88: mfc1        $a2, $f0
    ctx->r6 = (int32_t)ctx->f0.u32l;
    // 0x8009BA8C: addu        $a0, $t8, $t9
    ctx->r4 = ADD32(ctx->r24, ctx->r25);
    // 0x8009BA90: addiu       $a3, $zero, 0x0
    ctx->r7 = ADD32(0, 0X0);
    // 0x8009BA94: jal         0x800989E0
    // 0x8009BA98: swc1        $f0, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f0.u32l;
    func_800989E0(rdram, ctx);
        goto after_1;
    // 0x8009BA98: swc1        $f0, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f0.u32l;
    after_1:
    // 0x8009BA9C: lui         $a1, 0x800E
    ctx->r5 = S32(0X800E << 16);
    // 0x8009BAA0: lui         $a2, 0x800E
    ctx->r6 = S32(0X800E << 16);
    // 0x8009BAA4: addiu       $a2, $a2, 0x573C
    ctx->r6 = ADD32(ctx->r6, 0X573C);
    // 0x8009BAA8: addiu       $a1, $a1, 0x5714
    ctx->r5 = ADD32(ctx->r5, 0X5714);
    // 0x8009BAAC: lw          $a0, 0x20($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X20);
    // 0x8009BAB0: jal         0x80099A00
    // 0x8009BAB4: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_80099A00(rdram, ctx);
        goto after_2;
    // 0x8009BAB4: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_2:
    // 0x8009BAB8: lui         $a0, 0x800A
    ctx->r4 = S32(0X800A << 16);
    // 0x8009BABC: addiu       $a0, $a0, -0x55DC
    ctx->r4 = ADD32(ctx->r4, -0X55DC);
    // 0x8009BAC0: lw          $a1, 0x20($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X20);
    // 0x8009BAC4: addiu       $a2, $zero, 0xA
    ctx->r6 = ADD32(0, 0XA);
    // 0x8009BAC8: jal         0x8009A460
    // 0x8009BACC: addiu       $a3, $zero, -0x1
    ctx->r7 = ADD32(0, -0X1);
    func_8009A460(rdram, ctx);
        goto after_3;
    // 0x8009BACC: addiu       $a3, $zero, -0x1
    ctx->r7 = ADD32(0, -0X1);
    after_3:
    // 0x8009BAD0: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    // 0x8009BAD4: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x8009BAD8: jr          $ra
    // 0x8009BADC: nop

    return;
    // 0x8009BADC: nop

;}
RECOMP_FUNC void func_8009BAE0(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8009BAE0: lui         $t6, 0x800E
    ctx->r14 = S32(0X800E << 16);
    // 0x8009BAE4: lw          $t6, 0x5138($t6)
    ctx->r14 = MEM_W(ctx->r14, 0X5138);
    // 0x8009BAE8: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x8009BAEC: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x8009BAF0: sll         $t7, $t6, 2
    ctx->r15 = S32(ctx->r14 << 2);
    // 0x8009BAF4: addu        $v0, $v0, $t7
    ctx->r2 = ADD32(ctx->r2, ctx->r15);
    // 0x8009BAF8: lw          $v0, -0xFA8($v0)
    ctx->r2 = MEM_W(ctx->r2, -0XFA8);
    // 0x8009BAFC: sw          $a0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r4;
    // 0x8009BB00: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x8009BB04: beq         $v0, $zero, L_8009BB1C
    if (ctx->r2 == 0) {
        // 0x8009BB08: lui         $a0, 0x800A
        ctx->r4 = S32(0X800A << 16);
            goto L_8009BB1C;
    }
    // 0x8009BB08: lui         $a0, 0x800A
    ctx->r4 = S32(0X800A << 16);
    // 0x8009BB0C: lui         $at, 0x4234
    ctx->r1 = S32(0X4234 << 16);
    // 0x8009BB10: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x8009BB14: nop

    // 0x8009BB18: swc1        $f4, 0x88($v0)
    MEM_W(0X88, ctx->r2) = ctx->f4.u32l;
L_8009BB1C:
    // 0x8009BB1C: addiu       $a0, $a0, -0x4ED0
    ctx->r4 = ADD32(ctx->r4, -0X4ED0);
    // 0x8009BB20: lw          $a1, 0x20($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X20);
    // 0x8009BB24: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x8009BB28: jal         0x8009A460
    // 0x8009BB2C: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_8009A460(rdram, ctx);
        goto after_0;
    // 0x8009BB2C: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_0:
    // 0x8009BB30: addiu       $t8, $zero, 0x1
    ctx->r24 = ADD32(0, 0X1);
    // 0x8009BB34: sw          $t8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r24;
    // 0x8009BB38: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    // 0x8009BB3C: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x8009BB40: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    // 0x8009BB44: jal         0x80098AC4
    // 0x8009BB48: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_80098AC4(rdram, ctx);
        goto after_1;
    // 0x8009BB48: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_1:
    // 0x8009BB4C: lui         $a1, 0x800E
    ctx->r5 = S32(0X800E << 16);
    // 0x8009BB50: lui         $a2, 0x800E
    ctx->r6 = S32(0X800E << 16);
    // 0x8009BB54: addiu       $a2, $a2, 0x5798
    ctx->r6 = ADD32(ctx->r6, 0X5798);
    // 0x8009BB58: addiu       $a1, $a1, 0x5764
    ctx->r5 = ADD32(ctx->r5, 0X5764);
    // 0x8009BB5C: lw          $a0, 0x20($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X20);
    // 0x8009BB60: jal         0x80099A00
    // 0x8009BB64: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_80099A00(rdram, ctx);
        goto after_2;
    // 0x8009BB64: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_2:
    // 0x8009BB68: lui         $a0, 0x800A
    ctx->r4 = S32(0X800A << 16);
    // 0x8009BB6C: addiu       $a0, $a0, -0x55DC
    ctx->r4 = ADD32(ctx->r4, -0X55DC);
    // 0x8009BB70: lw          $a1, 0x20($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X20);
    // 0x8009BB74: addiu       $a2, $zero, 0xA
    ctx->r6 = ADD32(0, 0XA);
    // 0x8009BB78: jal         0x8009A460
    // 0x8009BB7C: addiu       $a3, $zero, -0x1
    ctx->r7 = ADD32(0, -0X1);
    func_8009A460(rdram, ctx);
        goto after_3;
    // 0x8009BB7C: addiu       $a3, $zero, -0x1
    ctx->r7 = ADD32(0, -0X1);
    after_3:
    // 0x8009BB80: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    // 0x8009BB84: addiu       $t9, $zero, 0x1
    ctx->r25 = ADD32(0, 0X1);
    // 0x8009BB88: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x8009BB8C: sb          $t9, 0x514C($at)
    MEM_B(0X514C, ctx->r1) = ctx->r25;
    // 0x8009BB90: jr          $ra
    // 0x8009BB94: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    return;
    // 0x8009BB94: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
;}
RECOMP_FUNC void func_8009BB98(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8009BB98: lui         $t6, 0x800E
    ctx->r14 = S32(0X800E << 16);
    // 0x8009BB9C: lw          $t6, 0x5138($t6)
    ctx->r14 = MEM_W(ctx->r14, 0X5138);
    // 0x8009BBA0: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x8009BBA4: addiu       $sp, $sp, -0x28
    ctx->r29 = ADD32(ctx->r29, -0X28);
    // 0x8009BBA8: sll         $t7, $t6, 2
    ctx->r15 = S32(ctx->r14 << 2);
    // 0x8009BBAC: addu        $v0, $v0, $t7
    ctx->r2 = ADD32(ctx->r2, ctx->r15);
    // 0x8009BBB0: lw          $v0, -0xFA8($v0)
    ctx->r2 = MEM_W(ctx->r2, -0XFA8);
    // 0x8009BBB4: sw          $s0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r16;
    // 0x8009BBB8: or          $s0, $a0, $zero
    ctx->r16 = ctx->r4 | 0;
    // 0x8009BBBC: beq         $v0, $zero, L_8009BBD4
    if (ctx->r2 == 0) {
        // 0x8009BBC0: sw          $ra, 0x24($sp)
        MEM_W(0X24, ctx->r29) = ctx->r31;
            goto L_8009BBD4;
    }
    // 0x8009BBC0: sw          $ra, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r31;
    // 0x8009BBC4: lui         $at, 0x4234
    ctx->r1 = S32(0X4234 << 16);
    // 0x8009BBC8: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x8009BBCC: nop

    // 0x8009BBD0: swc1        $f4, 0x88($v0)
    MEM_W(0X88, ctx->r2) = ctx->f4.u32l;
L_8009BBD4:
    // 0x8009BBD4: lui         $a0, 0x800A
    ctx->r4 = S32(0X800A << 16);
    // 0x8009BBD8: addiu       $a0, $a0, -0x4ED0
    ctx->r4 = ADD32(ctx->r4, -0X4ED0);
    // 0x8009BBDC: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    // 0x8009BBE0: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x8009BBE4: jal         0x8009A460
    // 0x8009BBE8: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_8009A460(rdram, ctx);
        goto after_0;
    // 0x8009BBE8: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_0:
    // 0x8009BBEC: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    // 0x8009BBF0: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x8009BBF4: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    // 0x8009BBF8: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    // 0x8009BBFC: jal         0x80098AC4
    // 0x8009BC00: sw          $zero, 0x10($sp)
    MEM_W(0X10, ctx->r29) = 0;
    func_80098AC4(rdram, ctx);
        goto after_1;
    // 0x8009BC00: sw          $zero, 0x10($sp)
    MEM_W(0X10, ctx->r29) = 0;
    after_1:
    // 0x8009BC04: lui         $a1, 0x800E
    ctx->r5 = S32(0X800E << 16);
    // 0x8009BC08: lui         $a2, 0x800E
    ctx->r6 = S32(0X800E << 16);
    // 0x8009BC0C: addiu       $a2, $a2, 0x57F4
    ctx->r6 = ADD32(ctx->r6, 0X57F4);
    // 0x8009BC10: addiu       $a1, $a1, 0x57CC
    ctx->r5 = ADD32(ctx->r5, 0X57CC);
    // 0x8009BC14: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x8009BC18: jal         0x80099A00
    // 0x8009BC1C: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_80099A00(rdram, ctx);
        goto after_2;
    // 0x8009BC1C: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_2:
    // 0x8009BC20: lui         $t0, 0x8019
    ctx->r8 = S32(0X8019 << 16);
    // 0x8009BC24: lw          $t0, 0x2458($t0)
    ctx->r8 = MEM_W(ctx->r8, 0X2458);
    // 0x8009BC28: lui         $t8, 0x800D
    ctx->r24 = S32(0X800D << 16);
    // 0x8009BC2C: lw          $t8, 0x48DC($t8)
    ctx->r24 = MEM_W(ctx->r24, 0X48DC);
    // 0x8009BC30: mtc1        $t0, $f8
    ctx->f8.u32l = ctx->r8;
    // 0x8009BC34: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x8009BC38: sll         $t9, $t8, 2
    ctx->r25 = S32(ctx->r24 << 2);
    // 0x8009BC3C: cvt.s.w     $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.fl = CVT_S_W(ctx->f8.u32l);
    // 0x8009BC40: subu        $t9, $t9, $t8
    ctx->r25 = SUB32(ctx->r25, ctx->r24);
    // 0x8009BC44: sll         $t9, $t9, 3
    ctx->r25 = S32(ctx->r25 << 3);
    // 0x8009BC48: addu        $at, $at, $t9
    ctx->r1 = ADD32(ctx->r1, ctx->r25);
    // 0x8009BC4C: lwc1        $f6, -0x1004($at)
    ctx->f6.u32l = MEM_W(ctx->r1, -0X1004);
    // 0x8009BC50: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x8009BC54: lwc1        $f18, -0x4B14($at)
    ctx->f18.u32l = MEM_W(ctx->r1, -0X4B14);
    // 0x8009BC58: sub.s       $f16, $f6, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f16.fl = ctx->f6.fl - ctx->f10.fl;
    // 0x8009BC5C: lwc1        $f4, 0x10($s0)
    ctx->f4.u32l = MEM_W(ctx->r16, 0X10);
    // 0x8009BC60: lwc1        $f6, 0x4($s0)
    ctx->f6.u32l = MEM_W(ctx->r16, 0X4);
    // 0x8009BC64: lui         $a0, 0x800A
    ctx->r4 = S32(0X800A << 16);
    // 0x8009BC68: mul.s       $f0, $f16, $f18
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f0.fl = MUL_S(ctx->f16.fl, ctx->f18.fl);
    // 0x8009BC6C: addiu       $a0, $a0, -0x55DC
    ctx->r4 = ADD32(ctx->r4, -0X55DC);
    // 0x8009BC70: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    // 0x8009BC74: addiu       $a2, $zero, 0xA
    ctx->r6 = ADD32(0, 0XA);
    // 0x8009BC78: addiu       $a3, $zero, -0x1
    ctx->r7 = ADD32(0, -0X1);
    // 0x8009BC7C: add.s       $f8, $f4, $f0
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f8.fl = ctx->f4.fl + ctx->f0.fl;
    // 0x8009BC80: add.s       $f10, $f6, $f0
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f10.fl = ctx->f6.fl + ctx->f0.fl;
    // 0x8009BC84: swc1        $f8, 0x10($s0)
    MEM_W(0X10, ctx->r16) = ctx->f8.u32l;
    // 0x8009BC88: jal         0x8009A460
    // 0x8009BC8C: swc1        $f10, 0x4($s0)
    MEM_W(0X4, ctx->r16) = ctx->f10.u32l;
    func_8009A460(rdram, ctx);
        goto after_3;
    // 0x8009BC8C: swc1        $f10, 0x4($s0)
    MEM_W(0X4, ctx->r16) = ctx->f10.u32l;
    after_3:
    // 0x8009BC90: lw          $ra, 0x24($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X24);
    // 0x8009BC94: lw          $s0, 0x20($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X20);
    // 0x8009BC98: addiu       $sp, $sp, 0x28
    ctx->r29 = ADD32(ctx->r29, 0X28);
    // 0x8009BC9C: jr          $ra
    // 0x8009BCA0: nop

    return;
    // 0x8009BCA0: nop

;}
RECOMP_FUNC void func_8009BCA4(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8009BCA4: lui         $t6, 0x800E
    ctx->r14 = S32(0X800E << 16);
    // 0x8009BCA8: lw          $t6, 0x5138($t6)
    ctx->r14 = MEM_W(ctx->r14, 0X5138);
    // 0x8009BCAC: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x8009BCB0: addiu       $sp, $sp, -0x28
    ctx->r29 = ADD32(ctx->r29, -0X28);
    // 0x8009BCB4: sll         $t7, $t6, 2
    ctx->r15 = S32(ctx->r14 << 2);
    // 0x8009BCB8: addu        $v0, $v0, $t7
    ctx->r2 = ADD32(ctx->r2, ctx->r15);
    // 0x8009BCBC: lw          $v0, -0xFA8($v0)
    ctx->r2 = MEM_W(ctx->r2, -0XFA8);
    // 0x8009BCC0: sw          $s0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r16;
    // 0x8009BCC4: or          $s0, $a0, $zero
    ctx->r16 = ctx->r4 | 0;
    // 0x8009BCC8: beq         $v0, $zero, L_8009BCE0
    if (ctx->r2 == 0) {
        // 0x8009BCCC: sw          $ra, 0x24($sp)
        MEM_W(0X24, ctx->r29) = ctx->r31;
            goto L_8009BCE0;
    }
    // 0x8009BCCC: sw          $ra, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r31;
    // 0x8009BCD0: lui         $at, 0x4234
    ctx->r1 = S32(0X4234 << 16);
    // 0x8009BCD4: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x8009BCD8: nop

    // 0x8009BCDC: swc1        $f4, 0x88($v0)
    MEM_W(0X88, ctx->r2) = ctx->f4.u32l;
L_8009BCE0:
    // 0x8009BCE0: lui         $a0, 0x800A
    ctx->r4 = S32(0X800A << 16);
    // 0x8009BCE4: addiu       $a0, $a0, -0x4ED0
    ctx->r4 = ADD32(ctx->r4, -0X4ED0);
    // 0x8009BCE8: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    // 0x8009BCEC: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x8009BCF0: jal         0x8009A460
    // 0x8009BCF4: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_8009A460(rdram, ctx);
        goto after_0;
    // 0x8009BCF4: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_0:
    // 0x8009BCF8: addiu       $t8, $zero, 0x1
    ctx->r24 = ADD32(0, 0X1);
    // 0x8009BCFC: sw          $t8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r24;
    // 0x8009BD00: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    // 0x8009BD04: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x8009BD08: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    // 0x8009BD0C: jal         0x80098AC4
    // 0x8009BD10: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_80098AC4(rdram, ctx);
        goto after_1;
    // 0x8009BD10: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_1:
    // 0x8009BD14: lui         $a1, 0x800E
    ctx->r5 = S32(0X800E << 16);
    // 0x8009BD18: lui         $a2, 0x800E
    ctx->r6 = S32(0X800E << 16);
    // 0x8009BD1C: addiu       $a2, $a2, 0x58B4
    ctx->r6 = ADD32(ctx->r6, 0X58B4);
    // 0x8009BD20: addiu       $a1, $a1, 0x581C
    ctx->r5 = ADD32(ctx->r5, 0X581C);
    // 0x8009BD24: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x8009BD28: jal         0x80099A00
    // 0x8009BD2C: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_80099A00(rdram, ctx);
        goto after_2;
    // 0x8009BD2C: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_2:
    // 0x8009BD30: lui         $t1, 0x8019
    ctx->r9 = S32(0X8019 << 16);
    // 0x8009BD34: lw          $t1, 0x2458($t1)
    ctx->r9 = MEM_W(ctx->r9, 0X2458);
    // 0x8009BD38: lui         $t9, 0x800D
    ctx->r25 = S32(0X800D << 16);
    // 0x8009BD3C: lw          $t9, 0x48DC($t9)
    ctx->r25 = MEM_W(ctx->r25, 0X48DC);
    // 0x8009BD40: mtc1        $t1, $f8
    ctx->f8.u32l = ctx->r9;
    // 0x8009BD44: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x8009BD48: sll         $t0, $t9, 2
    ctx->r8 = S32(ctx->r25 << 2);
    // 0x8009BD4C: cvt.s.w     $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.fl = CVT_S_W(ctx->f8.u32l);
    // 0x8009BD50: subu        $t0, $t0, $t9
    ctx->r8 = SUB32(ctx->r8, ctx->r25);
    // 0x8009BD54: sll         $t0, $t0, 3
    ctx->r8 = S32(ctx->r8 << 3);
    // 0x8009BD58: addu        $at, $at, $t0
    ctx->r1 = ADD32(ctx->r1, ctx->r8);
    // 0x8009BD5C: lwc1        $f6, -0x1004($at)
    ctx->f6.u32l = MEM_W(ctx->r1, -0X1004);
    // 0x8009BD60: lui         $at, 0x3F40
    ctx->r1 = S32(0X3F40 << 16);
    // 0x8009BD64: mtc1        $at, $f18
    ctx->f18.u32l = ctx->r1;
    // 0x8009BD68: sub.s       $f16, $f6, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f16.fl = ctx->f6.fl - ctx->f10.fl;
    // 0x8009BD6C: lwc1        $f4, 0x10($s0)
    ctx->f4.u32l = MEM_W(ctx->r16, 0X10);
    // 0x8009BD70: lwc1        $f6, 0x4($s0)
    ctx->f6.u32l = MEM_W(ctx->r16, 0X4);
    // 0x8009BD74: lui         $a0, 0x800A
    ctx->r4 = S32(0X800A << 16);
    // 0x8009BD78: mul.s       $f0, $f16, $f18
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f0.fl = MUL_S(ctx->f16.fl, ctx->f18.fl);
    // 0x8009BD7C: addiu       $a0, $a0, -0x55DC
    ctx->r4 = ADD32(ctx->r4, -0X55DC);
    // 0x8009BD80: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    // 0x8009BD84: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x8009BD88: addiu       $a3, $zero, -0x1
    ctx->r7 = ADD32(0, -0X1);
    // 0x8009BD8C: add.s       $f8, $f4, $f0
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f8.fl = ctx->f4.fl + ctx->f0.fl;
    // 0x8009BD90: add.s       $f10, $f6, $f0
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f10.fl = ctx->f6.fl + ctx->f0.fl;
    // 0x8009BD94: swc1        $f8, 0x10($s0)
    MEM_W(0X10, ctx->r16) = ctx->f8.u32l;
    // 0x8009BD98: jal         0x8009A460
    // 0x8009BD9C: swc1        $f10, 0x4($s0)
    MEM_W(0X4, ctx->r16) = ctx->f10.u32l;
    func_8009A460(rdram, ctx);
        goto after_3;
    // 0x8009BD9C: swc1        $f10, 0x4($s0)
    MEM_W(0X4, ctx->r16) = ctx->f10.u32l;
    after_3:
    // 0x8009BDA0: lui         $a0, 0x800A
    ctx->r4 = S32(0X800A << 16);
    // 0x8009BDA4: addiu       $a0, $a0, -0x4EF8
    ctx->r4 = ADD32(ctx->r4, -0X4EF8);
    // 0x8009BDA8: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    // 0x8009BDAC: addiu       $a2, $zero, 0x118
    ctx->r6 = ADD32(0, 0X118);
    // 0x8009BDB0: jal         0x8009A460
    // 0x8009BDB4: addiu       $a3, $zero, 0x118
    ctx->r7 = ADD32(0, 0X118);
    func_8009A460(rdram, ctx);
        goto after_4;
    // 0x8009BDB4: addiu       $a3, $zero, 0x118
    ctx->r7 = ADD32(0, 0X118);
    after_4:
    // 0x8009BDB8: lui         $a0, 0x800A
    ctx->r4 = S32(0X800A << 16);
    // 0x8009BDBC: addiu       $a0, $a0, -0x5684
    ctx->r4 = ADD32(ctx->r4, -0X5684);
    // 0x8009BDC0: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    // 0x8009BDC4: addiu       $a2, $zero, 0x14
    ctx->r6 = ADD32(0, 0X14);
    // 0x8009BDC8: jal         0x8009A460
    // 0x8009BDCC: addiu       $a3, $zero, -0x1
    ctx->r7 = ADD32(0, -0X1);
    func_8009A460(rdram, ctx);
        goto after_5;
    // 0x8009BDCC: addiu       $a3, $zero, -0x1
    ctx->r7 = ADD32(0, -0X1);
    after_5:
    // 0x8009BDD0: lw          $ra, 0x24($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X24);
    // 0x8009BDD4: lw          $s0, 0x20($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X20);
    // 0x8009BDD8: addiu       $sp, $sp, 0x28
    ctx->r29 = ADD32(ctx->r29, 0X28);
    // 0x8009BDDC: jr          $ra
    // 0x8009BDE0: nop

    return;
    // 0x8009BDE0: nop

;}
RECOMP_FUNC void func_8009BDE4(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8009BDE4: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x8009BDE8: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    // 0x8009BDEC: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x8009BDF0: lui         $a0, 0x800E
    ctx->r4 = S32(0X800E << 16);
    // 0x8009BDF4: jal         0x800988D8
    // 0x8009BDF8: lw          $a0, 0x5138($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X5138);
    func_800988D8(rdram, ctx);
        goto after_0;
    // 0x8009BDF8: lw          $a0, 0x5138($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X5138);
    after_0:
    // 0x8009BDFC: lui         $t6, 0x800D
    ctx->r14 = S32(0X800D << 16);
    // 0x8009BE00: mtc1        $zero, $f0
    ctx->f0.u32l = 0;
    // 0x8009BE04: lw          $t6, 0x48DC($t6)
    ctx->r14 = MEM_W(ctx->r14, 0X48DC);
    // 0x8009BE08: lui         $t8, 0x801D
    ctx->r24 = S32(0X801D << 16);
    // 0x8009BE0C: addiu       $t8, $t8, -0x1008
    ctx->r24 = ADD32(ctx->r24, -0X1008);
    // 0x8009BE10: sll         $t7, $t6, 2
    ctx->r15 = S32(ctx->r14 << 2);
    // 0x8009BE14: subu        $t7, $t7, $t6
    ctx->r15 = SUB32(ctx->r15, ctx->r14);
    // 0x8009BE18: sll         $t7, $t7, 3
    ctx->r15 = S32(ctx->r15 << 3);
    // 0x8009BE1C: mfc1        $a1, $f0
    ctx->r5 = (int32_t)ctx->f0.u32l;
    // 0x8009BE20: mfc1        $a2, $f0
    ctx->r6 = (int32_t)ctx->f0.u32l;
    // 0x8009BE24: mfc1        $a3, $f0
    ctx->r7 = (int32_t)ctx->f0.u32l;
    // 0x8009BE28: jal         0x800984F4
    // 0x8009BE2C: addu        $a0, $t7, $t8
    ctx->r4 = ADD32(ctx->r15, ctx->r24);
    Math_Vec3f_Set(rdram, ctx);
        goto after_1;
    // 0x8009BE2C: addu        $a0, $t7, $t8
    ctx->r4 = ADD32(ctx->r15, ctx->r24);
    after_1:
    // 0x8009BE30: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x8009BE34: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x8009BE38: jr          $ra
    // 0x8009BE3C: nop

    return;
    // 0x8009BE3C: nop

;}
RECOMP_FUNC void func_8009BE40(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8009BE40: lui         $t6, 0x800E
    ctx->r14 = S32(0X800E << 16);
    // 0x8009BE44: lw          $t6, 0x5138($t6)
    ctx->r14 = MEM_W(ctx->r14, 0X5138);
    // 0x8009BE48: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x8009BE4C: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x8009BE50: sll         $t7, $t6, 2
    ctx->r15 = S32(ctx->r14 << 2);
    // 0x8009BE54: addu        $v0, $v0, $t7
    ctx->r2 = ADD32(ctx->r2, ctx->r15);
    // 0x8009BE58: lw          $v0, -0xFA8($v0)
    ctx->r2 = MEM_W(ctx->r2, -0XFA8);
    // 0x8009BE5C: mtc1        $a3, $f12
    ctx->f12.u32l = ctx->r7;
    // 0x8009BE60: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x8009BE64: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    // 0x8009BE68: sw          $a1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r5;
    // 0x8009BE6C: beq         $v0, $zero, L_8009BE78
    if (ctx->r2 == 0) {
        // 0x8009BE70: sw          $a2, 0x20($sp)
        MEM_W(0X20, ctx->r29) = ctx->r6;
            goto L_8009BE78;
    }
    // 0x8009BE70: sw          $a2, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r6;
    // 0x8009BE74: swc1        $f12, 0x88($v0)
    MEM_W(0X88, ctx->r2) = ctx->f12.u32l;
L_8009BE78:
    // 0x8009BE78: lui         $a0, 0x800A
    ctx->r4 = S32(0X800A << 16);
    // 0x8009BE7C: addiu       $a0, $a0, -0x421C
    ctx->r4 = ADD32(ctx->r4, -0X421C);
    // 0x8009BE80: lw          $a1, 0x18($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X18);
    // 0x8009BE84: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x8009BE88: jal         0x8009A460
    // 0x8009BE8C: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_8009A460(rdram, ctx);
        goto after_0;
    // 0x8009BE8C: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_0:
    // 0x8009BE90: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
    // 0x8009BE94: lw          $a1, 0x1C($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X1C);
    // 0x8009BE98: lw          $a2, 0x20($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X20);
    // 0x8009BE9C: jal         0x80099A00
    // 0x8009BEA0: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_80099A00(rdram, ctx);
        goto after_1;
    // 0x8009BEA0: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_1:
    // 0x8009BEA4: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x8009BEA8: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x8009BEAC: jr          $ra
    // 0x8009BEB0: nop

    return;
    // 0x8009BEB0: nop

    // 0x8009BEB4: jr          $ra
    // 0x8009BEB8: nop

    return;
    // 0x8009BEB8: nop

;}
RECOMP_FUNC void func_8009BEBC(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8009BEBC: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x8009BEC0: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x8009BEC4: lui         $a1, 0x800E
    ctx->r5 = S32(0X800E << 16);
    // 0x8009BEC8: lui         $a2, 0x800E
    ctx->r6 = S32(0X800E << 16);
    // 0x8009BECC: addiu       $a2, $a2, 0x5A84
    ctx->r6 = ADD32(ctx->r6, 0X5A84);
    // 0x8009BED0: addiu       $a1, $a1, 0x5A3C
    ctx->r5 = ADD32(ctx->r5, 0X5A3C);
    // 0x8009BED4: jal         0x8009BE40
    // 0x8009BED8: lui         $a3, 0x4234
    ctx->r7 = S32(0X4234 << 16);
    func_8009BE40(rdram, ctx);
        goto after_0;
    // 0x8009BED8: lui         $a3, 0x4234
    ctx->r7 = S32(0X4234 << 16);
    after_0:
    // 0x8009BEDC: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x8009BEE0: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x8009BEE4: jr          $ra
    // 0x8009BEE8: nop

    return;
    // 0x8009BEE8: nop

;}
RECOMP_FUNC void func_8009BEEC(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8009BEEC: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x8009BEF0: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x8009BEF4: lui         $a1, 0x800E
    ctx->r5 = S32(0X800E << 16);
    // 0x8009BEF8: lui         $a2, 0x800E
    ctx->r6 = S32(0X800E << 16);
    // 0x8009BEFC: addiu       $a2, $a2, 0x5B1C
    ctx->r6 = ADD32(ctx->r6, 0X5B1C);
    // 0x8009BF00: addiu       $a1, $a1, 0x5ACC
    ctx->r5 = ADD32(ctx->r5, 0X5ACC);
    // 0x8009BF04: jal         0x8009BE40
    // 0x8009BF08: lui         $a3, 0x4234
    ctx->r7 = S32(0X4234 << 16);
    func_8009BE40(rdram, ctx);
        goto after_0;
    // 0x8009BF08: lui         $a3, 0x4234
    ctx->r7 = S32(0X4234 << 16);
    after_0:
    // 0x8009BF0C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x8009BF10: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x8009BF14: jr          $ra
    // 0x8009BF18: nop

    return;
    // 0x8009BF18: nop

;}
RECOMP_FUNC void func_8009BF1C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8009BF1C: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x8009BF20: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x8009BF24: lui         $a1, 0x800E
    ctx->r5 = S32(0X800E << 16);
    // 0x8009BF28: lui         $a2, 0x800E
    ctx->r6 = S32(0X800E << 16);
    // 0x8009BF2C: addiu       $a2, $a2, 0x5974
    ctx->r6 = ADD32(ctx->r6, 0X5974);
    // 0x8009BF30: addiu       $a1, $a1, 0x594C
    ctx->r5 = ADD32(ctx->r5, 0X594C);
    // 0x8009BF34: jal         0x8009BE40
    // 0x8009BF38: lui         $a3, 0x4234
    ctx->r7 = S32(0X4234 << 16);
    func_8009BE40(rdram, ctx);
        goto after_0;
    // 0x8009BF38: lui         $a3, 0x4234
    ctx->r7 = S32(0X4234 << 16);
    after_0:
    // 0x8009BF3C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x8009BF40: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x8009BF44: jr          $ra
    // 0x8009BF48: nop

    return;
    // 0x8009BF48: nop

;}
RECOMP_FUNC void func_8009BF4C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8009BF4C: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x8009BF50: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x8009BF54: lui         $a1, 0x800E
    ctx->r5 = S32(0X800E << 16);
    // 0x8009BF58: lui         $a2, 0x800E
    ctx->r6 = S32(0X800E << 16);
    // 0x8009BF5C: addiu       $a2, $a2, 0x59C4
    ctx->r6 = ADD32(ctx->r6, 0X59C4);
    // 0x8009BF60: addiu       $a1, $a1, 0x599C
    ctx->r5 = ADD32(ctx->r5, 0X599C);
    // 0x8009BF64: jal         0x8009BE40
    // 0x8009BF68: lui         $a3, 0x4234
    ctx->r7 = S32(0X4234 << 16);
    func_8009BE40(rdram, ctx);
        goto after_0;
    // 0x8009BF68: lui         $a3, 0x4234
    ctx->r7 = S32(0X4234 << 16);
    after_0:
    // 0x8009BF6C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x8009BF70: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x8009BF74: jr          $ra
    // 0x8009BF78: nop

    return;
    // 0x8009BF78: nop

;}
RECOMP_FUNC void func_8009BF7C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8009BF7C: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x8009BF80: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x8009BF84: lui         $a1, 0x800E
    ctx->r5 = S32(0X800E << 16);
    // 0x8009BF88: lui         $a2, 0x800E
    ctx->r6 = S32(0X800E << 16);
    // 0x8009BF8C: addiu       $a2, $a2, 0x5A14
    ctx->r6 = ADD32(ctx->r6, 0X5A14);
    // 0x8009BF90: addiu       $a1, $a1, 0x59EC
    ctx->r5 = ADD32(ctx->r5, 0X59EC);
    // 0x8009BF94: jal         0x8009BE40
    // 0x8009BF98: lui         $a3, 0x4234
    ctx->r7 = S32(0X4234 << 16);
    func_8009BE40(rdram, ctx);
        goto after_0;
    // 0x8009BF98: lui         $a3, 0x4234
    ctx->r7 = S32(0X4234 << 16);
    after_0:
    // 0x8009BF9C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x8009BFA0: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x8009BFA4: jr          $ra
    // 0x8009BFA8: nop

    return;
    // 0x8009BFA8: nop

;}
RECOMP_FUNC void func_8009BFAC(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8009BFAC: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x8009BFB0: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x8009BFB4: lui         $a1, 0x800E
    ctx->r5 = S32(0X800E << 16);
    // 0x8009BFB8: lui         $a2, 0x800E
    ctx->r6 = S32(0X800E << 16);
    // 0x8009BFBC: addiu       $a2, $a2, 0x5B8C
    ctx->r6 = ADD32(ctx->r6, 0X5B8C);
    // 0x8009BFC0: addiu       $a1, $a1, 0x5B6C
    ctx->r5 = ADD32(ctx->r5, 0X5B6C);
    // 0x8009BFC4: jal         0x8009BE40
    // 0x8009BFC8: lui         $a3, 0x4234
    ctx->r7 = S32(0X4234 << 16);
    func_8009BE40(rdram, ctx);
        goto after_0;
    // 0x8009BFC8: lui         $a3, 0x4234
    ctx->r7 = S32(0X4234 << 16);
    after_0:
    // 0x8009BFCC: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x8009BFD0: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x8009BFD4: jr          $ra
    // 0x8009BFD8: nop

    return;
    // 0x8009BFD8: nop

;}
RECOMP_FUNC void func_8009BFDC(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8009BFDC: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x8009BFE0: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x8009BFE4: lui         $a1, 0x800E
    ctx->r5 = S32(0X800E << 16);
    // 0x8009BFE8: lui         $a2, 0x800E
    ctx->r6 = S32(0X800E << 16);
    // 0x8009BFEC: addiu       $a2, $a2, 0x5BCC
    ctx->r6 = ADD32(ctx->r6, 0X5BCC);
    // 0x8009BFF0: addiu       $a1, $a1, 0x5BAC
    ctx->r5 = ADD32(ctx->r5, 0X5BAC);
    // 0x8009BFF4: jal         0x8009BE40
    // 0x8009BFF8: lui         $a3, 0x4234
    ctx->r7 = S32(0X4234 << 16);
    func_8009BE40(rdram, ctx);
        goto after_0;
    // 0x8009BFF8: lui         $a3, 0x4234
    ctx->r7 = S32(0X4234 << 16);
    after_0:
    // 0x8009BFFC: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x8009C000: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x8009C004: jr          $ra
    // 0x8009C008: nop

    return;
    // 0x8009C008: nop

;}
RECOMP_FUNC void func_8009C00C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8009C00C: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x8009C010: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x8009C014: lui         $a1, 0x800E
    ctx->r5 = S32(0X800E << 16);
    // 0x8009C018: lui         $a2, 0x800E
    ctx->r6 = S32(0X800E << 16);
    // 0x8009C01C: addiu       $a2, $a2, 0x5C0C
    ctx->r6 = ADD32(ctx->r6, 0X5C0C);
    // 0x8009C020: addiu       $a1, $a1, 0x5BEC
    ctx->r5 = ADD32(ctx->r5, 0X5BEC);
    // 0x8009C024: jal         0x8009BE40
    // 0x8009C028: lui         $a3, 0x4234
    ctx->r7 = S32(0X4234 << 16);
    func_8009BE40(rdram, ctx);
        goto after_0;
    // 0x8009C028: lui         $a3, 0x4234
    ctx->r7 = S32(0X4234 << 16);
    after_0:
    // 0x8009C02C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x8009C030: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x8009C034: jr          $ra
    // 0x8009C038: nop

    return;
    // 0x8009C038: nop

    // 0x8009C03C: jr          $ra
    // 0x8009C040: nop

    return;
    // 0x8009C040: nop

;}
RECOMP_FUNC void func_8009C044(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8009C044: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x8009C048: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x8009C04C: lui         $a1, 0x800E
    ctx->r5 = S32(0X800E << 16);
    // 0x8009C050: lui         $a2, 0x800E
    ctx->r6 = S32(0X800E << 16);
    // 0x8009C054: addiu       $a2, $a2, 0x5C8C
    ctx->r6 = ADD32(ctx->r6, 0X5C8C);
    // 0x8009C058: addiu       $a1, $a1, 0x5C6C
    ctx->r5 = ADD32(ctx->r5, 0X5C6C);
    // 0x8009C05C: jal         0x8009BE40
    // 0x8009C060: lui         $a3, 0x4234
    ctx->r7 = S32(0X4234 << 16);
    func_8009BE40(rdram, ctx);
        goto after_0;
    // 0x8009C060: lui         $a3, 0x4234
    ctx->r7 = S32(0X4234 << 16);
    after_0:
    // 0x8009C064: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x8009C068: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x8009C06C: jr          $ra
    // 0x8009C070: nop

    return;
    // 0x8009C070: nop

;}
RECOMP_FUNC void func_8009C074(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8009C074: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x8009C078: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x8009C07C: lui         $a1, 0x800E
    ctx->r5 = S32(0X800E << 16);
    // 0x8009C080: lui         $a2, 0x800E
    ctx->r6 = S32(0X800E << 16);
    // 0x8009C084: addiu       $a2, $a2, 0x5CC0
    ctx->r6 = ADD32(ctx->r6, 0X5CC0);
    // 0x8009C088: addiu       $a1, $a1, 0x5CAC
    ctx->r5 = ADD32(ctx->r5, 0X5CAC);
    // 0x8009C08C: jal         0x8009BE40
    // 0x8009C090: lui         $a3, 0x4234
    ctx->r7 = S32(0X4234 << 16);
    func_8009BE40(rdram, ctx);
        goto after_0;
    // 0x8009C090: lui         $a3, 0x4234
    ctx->r7 = S32(0X4234 << 16);
    after_0:
    // 0x8009C094: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x8009C098: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x8009C09C: jr          $ra
    // 0x8009C0A0: nop

    return;
    // 0x8009C0A0: nop

;}
RECOMP_FUNC void func_8009C0A4(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8009C0A4: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x8009C0A8: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x8009C0AC: lui         $a1, 0x800E
    ctx->r5 = S32(0X800E << 16);
    // 0x8009C0B0: lui         $a2, 0x800E
    ctx->r6 = S32(0X800E << 16);
    // 0x8009C0B4: addiu       $a2, $a2, 0x5D4C
    ctx->r6 = ADD32(ctx->r6, 0X5D4C);
    // 0x8009C0B8: addiu       $a1, $a1, 0x5CD4
    ctx->r5 = ADD32(ctx->r5, 0X5CD4);
    // 0x8009C0BC: jal         0x8009BE40
    // 0x8009C0C0: lui         $a3, 0x4234
    ctx->r7 = S32(0X4234 << 16);
    func_8009BE40(rdram, ctx);
        goto after_0;
    // 0x8009C0C0: lui         $a3, 0x4234
    ctx->r7 = S32(0X4234 << 16);
    after_0:
    // 0x8009C0C4: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x8009C0C8: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x8009C0CC: jr          $ra
    // 0x8009C0D0: nop

    return;
    // 0x8009C0D0: nop

;}
RECOMP_FUNC void func_8009C0D4(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8009C0D4: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x8009C0D8: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x8009C0DC: lui         $a1, 0x800E
    ctx->r5 = S32(0X800E << 16);
    // 0x8009C0E0: lui         $a2, 0x800E
    ctx->r6 = S32(0X800E << 16);
    // 0x8009C0E4: addiu       $a2, $a2, 0x5E0C
    ctx->r6 = ADD32(ctx->r6, 0X5E0C);
    // 0x8009C0E8: addiu       $a1, $a1, 0x5DC4
    ctx->r5 = ADD32(ctx->r5, 0X5DC4);
    // 0x8009C0EC: jal         0x8009BE40
    // 0x8009C0F0: lui         $a3, 0x4234
    ctx->r7 = S32(0X4234 << 16);
    func_8009BE40(rdram, ctx);
        goto after_0;
    // 0x8009C0F0: lui         $a3, 0x4234
    ctx->r7 = S32(0X4234 << 16);
    after_0:
    // 0x8009C0F4: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x8009C0F8: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x8009C0FC: jr          $ra
    // 0x8009C100: nop

    return;
    // 0x8009C100: nop

;}
