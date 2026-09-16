#include "recomp.h"
#include "funcs.h"

RECOMP_FUNC void ldiv_recomp(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800D2220: div         $zero, $a1, $a2
    lo = S32(S64(S32(ctx->r5)) / S64(S32(ctx->r6))); hi = S32(S64(S32(ctx->r5)) % S64(S32(ctx->r6)));
    // 0x800D2224: mflo        $v0
    ctx->r2 = lo;
    // 0x800D2228: addiu       $sp, $sp, -0x8
    ctx->r29 = ADD32(ctx->r29, -0X8);
    // 0x800D222C: bne         $a2, $zero, L_800D2238
    if (ctx->r6 != 0) {
        // 0x800D2230: nop
    
            goto L_800D2238;
    }
    // 0x800D2230: nop

    // 0x800D2234: break       7
    do_break(2148344372);
L_800D2238:
    // 0x800D2238: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x800D223C: bne         $a2, $at, L_800D2250
    if (ctx->r6 != ctx->r1) {
        // 0x800D2240: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_800D2250;
    }
    // 0x800D2240: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x800D2244: bne         $a1, $at, L_800D2250
    if (ctx->r5 != ctx->r1) {
        // 0x800D2248: nop
    
            goto L_800D2250;
    }
    // 0x800D2248: nop

    // 0x800D224C: break       6
    do_break(2148344396);
L_800D2250:
    // 0x800D2250: multu       $a2, $v0
    result = U64(U32(ctx->r6)) * U64(U32(ctx->r2)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x800D2254: sw          $v0, 0x0($sp)
    MEM_W(0X0, ctx->r29) = ctx->r2;
    // 0x800D2258: addiu       $t7, $sp, 0x0
    ctx->r15 = ADD32(ctx->r29, 0X0);
    // 0x800D225C: mflo        $t6
    ctx->r14 = lo;
    // 0x800D2260: subu        $v1, $a1, $t6
    ctx->r3 = SUB32(ctx->r5, ctx->r14);
    // 0x800D2264: bgez        $v0, L_800D2288
    if (SIGNED(ctx->r2) >= 0) {
        // 0x800D2268: sw          $v1, 0x4($sp)
        MEM_W(0X4, ctx->r29) = ctx->r3;
            goto L_800D2288;
    }
    // 0x800D2268: sw          $v1, 0x4($sp)
    MEM_W(0X4, ctx->r29) = ctx->r3;
    // 0x800D226C: sw          $v0, 0x0($sp)
    MEM_W(0X0, ctx->r29) = ctx->r2;
    // 0x800D2270: blez        $v1, L_800D2288
    if (SIGNED(ctx->r3) <= 0) {
        // 0x800D2274: sw          $v1, 0x4($sp)
        MEM_W(0X4, ctx->r29) = ctx->r3;
            goto L_800D2288;
    }
    // 0x800D2274: sw          $v1, 0x4($sp)
    MEM_W(0X4, ctx->r29) = ctx->r3;
    // 0x800D2278: addiu       $v0, $v0, 0x1
    ctx->r2 = ADD32(ctx->r2, 0X1);
    // 0x800D227C: subu        $v1, $v1, $a2
    ctx->r3 = SUB32(ctx->r3, ctx->r6);
    // 0x800D2280: sw          $v1, 0x4($sp)
    MEM_W(0X4, ctx->r29) = ctx->r3;
    // 0x800D2284: sw          $v0, 0x0($sp)
    MEM_W(0X0, ctx->r29) = ctx->r2;
L_800D2288:
    // 0x800D2288: lw          $at, 0x0($t7)
    ctx->r1 = MEM_W(ctx->r15, 0X0);
    // 0x800D228C: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x800D2290: sw          $at, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r1;
    // 0x800D2294: lw          $t0, 0x4($t7)
    ctx->r8 = MEM_W(ctx->r15, 0X4);
    // 0x800D2298: addiu       $sp, $sp, 0x8
    ctx->r29 = ADD32(ctx->r29, 0X8);
    // 0x800D229C: jr          $ra
    // 0x800D22A0: sw          $t0, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r8;
    return;
    // 0x800D22A0: sw          $t0, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r8;
    // 0x800D22A4: nop

    // 0x800D22A8: nop

    // 0x800D22AC: nop

;}
RECOMP_FUNC void func_801DAFA0(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801DAFA0: sw          $a1, 0x4($sp)
    MEM_W(0X4, ctx->r29) = ctx->r5;
    // 0x801DAFA4: lui         $at, 0x4040
    ctx->r1 = S32(0X4040 << 16);
    // 0x801DAFA8: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x801DAFAC: lw          $t6, 0x0($a0)
    ctx->r14 = MEM_W(ctx->r4, 0X0);
    // 0x801DAFB0: jr          $ra
    // 0x801DAFB4: swc1        $f4, 0x50($t6)
    MEM_W(0X50, ctx->r14) = ctx->f4.u32l;
    return;
    // 0x801DAFB4: swc1        $f4, 0x50($t6)
    MEM_W(0X50, ctx->r14) = ctx->f4.u32l;
;}
RECOMP_FUNC void func_801DAFB8(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801DAFB8: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x801DAFBC: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x801DAFC0: jal         0x80047E50
    // 0x801DAFC4: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    SysUtils_Rand(rdram, ctx);
        goto after_0;
    // 0x801DAFC4: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    after_0:
    // 0x801DAFC8: andi        $t6, $v0, 0x7
    ctx->r14 = ctx->r2 & 0X7;
    // 0x801DAFCC: beq         $t6, $zero, L_801DAFF4
    if (ctx->r14 == 0) {
        // 0x801DAFD0: nop
    
            goto L_801DAFF4;
    }
    // 0x801DAFD0: nop

    // 0x801DAFD4: jal         0x80047E50
    // 0x801DAFD8: nop

    SysUtils_Rand(rdram, ctx);
        goto after_1;
    // 0x801DAFD8: nop

    after_1:
    // 0x801DAFDC: addiu       $at, $zero, 0xF
    ctx->r1 = ADD32(0, 0XF);
    // 0x801DAFE0: divu        $zero, $v0, $at
    lo = S32(U32(ctx->r2) / U32(ctx->r1)); hi = S32(U32(ctx->r2) % U32(ctx->r1));
    // 0x801DAFE4: lw          $t8, 0x18($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X18);
    // 0x801DAFE8: mfhi        $t7
    ctx->r15 = hi;
    // 0x801DAFEC: b           L_801DB014
    // 0x801DAFF0: sw          $t7, 0x8($t8)
    MEM_W(0X8, ctx->r24) = ctx->r15;
        goto L_801DB014;
    // 0x801DAFF0: sw          $t7, 0x8($t8)
    MEM_W(0X8, ctx->r24) = ctx->r15;
L_801DAFF4:
    // 0x801DAFF4: jal         0x80047E50
    // 0x801DAFF8: nop

    SysUtils_Rand(rdram, ctx);
        goto after_2;
    // 0x801DAFF8: nop

    after_2:
    // 0x801DAFFC: addiu       $at, $zero, 0x13
    ctx->r1 = ADD32(0, 0X13);
    // 0x801DB000: divu        $zero, $v0, $at
    lo = S32(U32(ctx->r2) / U32(ctx->r1)); hi = S32(U32(ctx->r2) % U32(ctx->r1));
    // 0x801DB004: lw          $t1, 0x18($sp)
    ctx->r9 = MEM_W(ctx->r29, 0X18);
    // 0x801DB008: mfhi        $t9
    ctx->r25 = hi;
    // 0x801DB00C: addiu       $t0, $t9, 0x19
    ctx->r8 = ADD32(ctx->r25, 0X19);
    // 0x801DB010: sw          $t0, 0x8($t1)
    MEM_W(0X8, ctx->r9) = ctx->r8;
L_801DB014:
    // 0x801DB014: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x801DB018: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x801DB01C: jr          $ra
    // 0x801DB020: nop

    return;
    // 0x801DB020: nop

;}
RECOMP_FUNC void func_801DB024(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801DB024: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x801DB028: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x801DB02C: lw          $v0, 0x8($a0)
    ctx->r2 = MEM_W(ctx->r4, 0X8);
    // 0x801DB030: bltz        $v0, L_801DB074
    if (SIGNED(ctx->r2) < 0) {
        // 0x801DB034: slti        $at, $v0, 0x10
        ctx->r1 = SIGNED(ctx->r2) < 0X10 ? 1 : 0;
            goto L_801DB074;
    }
    // 0x801DB034: slti        $at, $v0, 0x10
    ctx->r1 = SIGNED(ctx->r2) < 0X10 ? 1 : 0;
    // 0x801DB038: beq         $at, $zero, L_801DB074
    if (ctx->r1 == 0) {
        // 0x801DB03C: addiu       $t6, $v0, 0x2
        ctx->r14 = ADD32(ctx->r2, 0X2);
            goto L_801DB074;
    }
    // 0x801DB03C: addiu       $t6, $v0, 0x2
    ctx->r14 = ADD32(ctx->r2, 0X2);
    // 0x801DB040: slti        $at, $t6, 0x10
    ctx->r1 = SIGNED(ctx->r14) < 0X10 ? 1 : 0;
    // 0x801DB044: bne         $at, $zero, L_801DB0D4
    if (ctx->r1 != 0) {
        // 0x801DB048: sw          $t6, 0x8($a0)
        MEM_W(0X8, ctx->r4) = ctx->r14;
            goto L_801DB0D4;
    }
    // 0x801DB048: sw          $t6, 0x8($a0)
    MEM_W(0X8, ctx->r4) = ctx->r14;
    // 0x801DB04C: jal         0x80047E50
    // 0x801DB050: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    SysUtils_Rand(rdram, ctx);
        goto after_0;
    // 0x801DB050: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    after_0:
    // 0x801DB054: andi        $t8, $v0, 0x7
    ctx->r24 = ctx->r2 & 0X7;
    // 0x801DB058: beq         $t8, $zero, L_801DB068
    if (ctx->r24 == 0) {
        // 0x801DB05C: lw          $a0, 0x18($sp)
        ctx->r4 = MEM_W(ctx->r29, 0X18);
            goto L_801DB068;
    }
    // 0x801DB05C: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
    // 0x801DB060: b           L_801DB0D4
    // 0x801DB064: sw          $zero, 0x8($a0)
    MEM_W(0X8, ctx->r4) = 0;
        goto L_801DB0D4;
    // 0x801DB064: sw          $zero, 0x8($a0)
    MEM_W(0X8, ctx->r4) = 0;
L_801DB068:
    // 0x801DB068: addiu       $t9, $zero, 0x10
    ctx->r25 = ADD32(0, 0X10);
    // 0x801DB06C: b           L_801DB0D4
    // 0x801DB070: sw          $t9, 0x8($a0)
    MEM_W(0X8, ctx->r4) = ctx->r25;
        goto L_801DB0D4;
    // 0x801DB070: sw          $t9, 0x8($a0)
    MEM_W(0X8, ctx->r4) = ctx->r25;
L_801DB074:
    // 0x801DB074: slti        $at, $v0, 0x19
    ctx->r1 = SIGNED(ctx->r2) < 0X19 ? 1 : 0;
    // 0x801DB078: bne         $at, $zero, L_801DB0C4
    if (ctx->r1 != 0) {
        // 0x801DB07C: addiu       $t5, $v0, 0x1
        ctx->r13 = ADD32(ctx->r2, 0X1);
            goto L_801DB0C4;
    }
    // 0x801DB07C: addiu       $t5, $v0, 0x1
    ctx->r13 = ADD32(ctx->r2, 0X1);
    // 0x801DB080: slti        $at, $v0, 0x2D
    ctx->r1 = SIGNED(ctx->r2) < 0X2D ? 1 : 0;
    // 0x801DB084: beq         $at, $zero, L_801DB0C4
    if (ctx->r1 == 0) {
        // 0x801DB088: addiu       $t0, $v0, 0x1
        ctx->r8 = ADD32(ctx->r2, 0X1);
            goto L_801DB0C4;
    }
    // 0x801DB088: addiu       $t0, $v0, 0x1
    ctx->r8 = ADD32(ctx->r2, 0X1);
    // 0x801DB08C: slti        $at, $t0, 0x2D
    ctx->r1 = SIGNED(ctx->r8) < 0X2D ? 1 : 0;
    // 0x801DB090: bne         $at, $zero, L_801DB0D4
    if (ctx->r1 != 0) {
        // 0x801DB094: sw          $t0, 0x8($a0)
        MEM_W(0X8, ctx->r4) = ctx->r8;
            goto L_801DB0D4;
    }
    // 0x801DB094: sw          $t0, 0x8($a0)
    MEM_W(0X8, ctx->r4) = ctx->r8;
    // 0x801DB098: jal         0x80047E50
    // 0x801DB09C: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    SysUtils_Rand(rdram, ctx);
        goto after_1;
    // 0x801DB09C: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    after_1:
    // 0x801DB0A0: andi        $t2, $v0, 0xF
    ctx->r10 = ctx->r2 & 0XF;
    // 0x801DB0A4: beq         $t2, $zero, L_801DB0B8
    if (ctx->r10 == 0) {
        // 0x801DB0A8: lw          $a0, 0x18($sp)
        ctx->r4 = MEM_W(ctx->r29, 0X18);
            goto L_801DB0B8;
    }
    // 0x801DB0A8: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
    // 0x801DB0AC: addiu       $t3, $zero, 0x2D
    ctx->r11 = ADD32(0, 0X2D);
    // 0x801DB0B0: b           L_801DB0D4
    // 0x801DB0B4: sw          $t3, 0x8($a0)
    MEM_W(0X8, ctx->r4) = ctx->r11;
        goto L_801DB0D4;
    // 0x801DB0B4: sw          $t3, 0x8($a0)
    MEM_W(0X8, ctx->r4) = ctx->r11;
L_801DB0B8:
    // 0x801DB0B8: addiu       $t4, $zero, 0x19
    ctx->r12 = ADD32(0, 0X19);
    // 0x801DB0BC: b           L_801DB0D4
    // 0x801DB0C0: sw          $t4, 0x8($a0)
    MEM_W(0X8, ctx->r4) = ctx->r12;
        goto L_801DB0D4;
    // 0x801DB0C0: sw          $t4, 0x8($a0)
    MEM_W(0X8, ctx->r4) = ctx->r12;
L_801DB0C4:
    // 0x801DB0C4: slti        $at, $t5, 0x37
    ctx->r1 = SIGNED(ctx->r13) < 0X37 ? 1 : 0;
    // 0x801DB0C8: bne         $at, $zero, L_801DB0D4
    if (ctx->r1 != 0) {
        // 0x801DB0CC: sw          $t5, 0x8($a0)
        MEM_W(0X8, ctx->r4) = ctx->r13;
            goto L_801DB0D4;
    }
    // 0x801DB0CC: sw          $t5, 0x8($a0)
    MEM_W(0X8, ctx->r4) = ctx->r13;
    // 0x801DB0D0: sw          $zero, 0x8($a0)
    MEM_W(0X8, ctx->r4) = 0;
L_801DB0D4:
    // 0x801DB0D4: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x801DB0D8: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x801DB0DC: jr          $ra
    // 0x801DB0E0: nop

    return;
    // 0x801DB0E0: nop

;}
RECOMP_FUNC void func_801DB0E4(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801DB0E4: addiu       $sp, $sp, -0x38
    ctx->r29 = ADD32(ctx->r29, -0X38);
    // 0x801DB0E8: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x801DB0EC: sw          $a1, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r5;
    // 0x801DB0F0: sw          $a2, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r6;
    // 0x801DB0F4: addiu       $t6, $zero, 0x3
    ctx->r14 = ADD32(0, 0X3);
    // 0x801DB0F8: sw          $t6, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r14;
    // 0x801DB0FC: sw          $zero, 0x4($a0)
    MEM_W(0X4, ctx->r4) = 0;
    // 0x801DB100: jal         0x801DAFB8
    // 0x801DB104: sw          $a0, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r4;
    func_801DAFB8(rdram, ctx);
        goto after_0;
    // 0x801DB104: sw          $a0, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r4;
    after_0:
    // 0x801DB108: lw          $a3, 0x38($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X38);
    // 0x801DB10C: lw          $a0, 0x3C($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X3C);
    // 0x801DB110: addiu       $v0, $sp, 0x2C
    ctx->r2 = ADD32(ctx->r29, 0X2C);
    // 0x801DB114: addiu       $a1, $sp, 0x38
    ctx->r5 = ADD32(ctx->r29, 0X38);
    // 0x801DB118: or          $v1, $a3, $zero
    ctx->r3 = ctx->r7 | 0;
L_801DB11C:
    // 0x801DB11C: lwc1        $f4, 0x0($a0)
    ctx->f4.u32l = MEM_W(ctx->r4, 0X0);
    // 0x801DB120: addiu       $v0, $v0, 0x4
    ctx->r2 = ADD32(ctx->r2, 0X4);
    // 0x801DB124: sltu        $at, $v0, $a1
    ctx->r1 = ctx->r2 < ctx->r5 ? 1 : 0;
    // 0x801DB128: swc1        $f4, 0xC($v1)
    MEM_W(0XC, ctx->r3) = ctx->f4.u32l;
    // 0x801DB12C: lwc1        $f8, 0x0($a0)
    ctx->f8.u32l = MEM_W(ctx->r4, 0X0);
    // 0x801DB130: lwc1        $f6, 0xC($a0)
    ctx->f6.u32l = MEM_W(ctx->r4, 0XC);
    // 0x801DB134: addiu       $v1, $v1, 0x4
    ctx->r3 = ADD32(ctx->r3, 0X4);
    // 0x801DB138: addiu       $a0, $a0, 0x4
    ctx->r4 = ADD32(ctx->r4, 0X4);
    // 0x801DB13C: sub.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = ctx->f6.fl - ctx->f8.fl;
    // 0x801DB140: bne         $at, $zero, L_801DB11C
    if (ctx->r1 != 0) {
        // 0x801DB144: swc1        $f10, -0x4($v0)
        MEM_W(-0X4, ctx->r2) = ctx->f10.u32l;
            goto L_801DB11C;
    }
    // 0x801DB144: swc1        $f10, -0x4($v0)
    MEM_W(-0X4, ctx->r2) = ctx->f10.u32l;
    // 0x801DB148: lwc1        $f2, 0x2C($sp)
    ctx->f2.u32l = MEM_W(ctx->r29, 0X2C);
    // 0x801DB14C: lwc1        $f14, 0x30($sp)
    ctx->f14.u32l = MEM_W(ctx->r29, 0X30);
    // 0x801DB150: lwc1        $f0, 0x34($sp)
    ctx->f0.u32l = MEM_W(ctx->r29, 0X34);
    // 0x801DB154: mul.s       $f16, $f2, $f2
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f16.fl = MUL_S(ctx->f2.fl, ctx->f2.fl);
    // 0x801DB158: sw          $a3, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r7;
    // 0x801DB15C: mul.s       $f18, $f14, $f14
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f18.fl = MUL_S(ctx->f14.fl, ctx->f14.fl);
    // 0x801DB160: add.s       $f4, $f16, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f4.fl = ctx->f16.fl + ctx->f18.fl;
    // 0x801DB164: mul.s       $f6, $f0, $f0
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f6.fl = MUL_S(ctx->f0.fl, ctx->f0.fl);
    // 0x801DB168: jal         0x800C7010
    // 0x801DB16C: add.s       $f12, $f6, $f4
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f12.fl = ctx->f6.fl + ctx->f4.fl;
    _nsqrtf(rdram, ctx);
        goto after_1;
    // 0x801DB16C: add.s       $f12, $f6, $f4
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f12.fl = ctx->f6.fl + ctx->f4.fl;
    after_1:
    // 0x801DB170: lw          $a3, 0x38($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X38);
    // 0x801DB174: addiu       $v0, $sp, 0x2C
    ctx->r2 = ADD32(ctx->r29, 0X2C);
    // 0x801DB178: addiu       $a0, $sp, 0x38
    ctx->r4 = ADD32(ctx->r29, 0X38);
    // 0x801DB17C: or          $v1, $a3, $zero
    ctx->r3 = ctx->r7 | 0;
L_801DB180:
    // 0x801DB180: lwc1        $f8, 0x0($v0)
    ctx->f8.u32l = MEM_W(ctx->r2, 0X0);
    // 0x801DB184: addiu       $v0, $v0, 0x4
    ctx->r2 = ADD32(ctx->r2, 0X4);
    // 0x801DB188: addiu       $v1, $v1, 0x4
    ctx->r3 = ADD32(ctx->r3, 0X4);
    // 0x801DB18C: div.s       $f10, $f8, $f0
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f10.fl = DIV_S(ctx->f8.fl, ctx->f0.fl);
    // 0x801DB190: bne         $v0, $a0, L_801DB180
    if (ctx->r2 != ctx->r4) {
        // 0x801DB194: swc1        $f10, 0x14($v1)
        MEM_W(0X14, ctx->r3) = ctx->f10.u32l;
            goto L_801DB180;
    }
    // 0x801DB194: swc1        $f10, 0x14($v1)
    MEM_W(0X14, ctx->r3) = ctx->f10.u32l;
    // 0x801DB198: mtc1        $zero, $f0
    ctx->f0.u32l = 0;
    // 0x801DB19C: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x801DB1A0: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
    // 0x801DB1A4: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801DB1A8: swc1        $f0, 0x24($a3)
    MEM_W(0X24, ctx->r7) = ctx->f0.u32l;
    // 0x801DB1AC: swc1        $f0, 0x2C($a3)
    MEM_W(0X2C, ctx->r7) = ctx->f0.u32l;
    // 0x801DB1B0: swc1        $f16, 0x28($a3)
    MEM_W(0X28, ctx->r7) = ctx->f16.u32l;
    // 0x801DB1B4: lwc1        $f18, 0x5F10($at)
    ctx->f18.u32l = MEM_W(ctx->r1, 0X5F10);
    // 0x801DB1B8: swc1        $f18, 0x30($a3)
    MEM_W(0X30, ctx->r7) = ctx->f18.u32l;
    // 0x801DB1BC: lw          $t7, 0x3C($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X3C);
    // 0x801DB1C0: lw          $t9, 0x40($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X40);
    // 0x801DB1C4: lw          $t8, 0x1C($t7)
    ctx->r24 = MEM_W(ctx->r15, 0X1C);
    // 0x801DB1C8: sw          $t8, 0x0($t9)
    MEM_W(0X0, ctx->r25) = ctx->r24;
    // 0x801DB1CC: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x801DB1D0: addiu       $sp, $sp, 0x38
    ctx->r29 = ADD32(ctx->r29, 0X38);
    // 0x801DB1D4: jr          $ra
    // 0x801DB1D8: nop

    return;
    // 0x801DB1D8: nop

;}
RECOMP_FUNC void func_801DB1DC(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801DB1DC: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x801DB1E0: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x801DB1E4: sw          $a2, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r6;
    // 0x801DB1E8: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    // 0x801DB1EC: jal         0x801DB024
    // 0x801DB1F0: sw          $a1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r5;
    func_801DB024(rdram, ctx);
        goto after_0;
    // 0x801DB1F0: sw          $a1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r5;
    after_0:
    // 0x801DB1F4: lw          $t6, 0x20($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X20);
    // 0x801DB1F8: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
    // 0x801DB1FC: lw          $a1, 0x1C($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X1C);
    // 0x801DB200: lw          $t7, 0x0($t6)
    ctx->r15 = MEM_W(ctx->r14, 0X0);
    // 0x801DB204: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
    // 0x801DB208: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x801DB20C: blezl       $t7, L_801DB274
    if (SIGNED(ctx->r15) <= 0) {
        // 0x801DB210: sw          $zero, 0x0($a0)
        MEM_W(0X0, ctx->r4) = 0;
            goto L_801DB274;
    }
    goto skip_0;
    // 0x801DB210: sw          $zero, 0x0($a0)
    MEM_W(0X0, ctx->r4) = 0;
    skip_0:
    // 0x801DB214: addiu       $a0, $zero, 0x3
    ctx->r4 = ADD32(0, 0X3);
    // 0x801DB218: lwc1        $f12, 0x18($v0)
    ctx->f12.u32l = MEM_W(ctx->r2, 0X18);
    // 0x801DB21C: lwc1        $f14, 0x18($a1)
    ctx->f14.u32l = MEM_W(ctx->r5, 0X18);
    // 0x801DB220: addiu       $v1, $v1, 0x1
    ctx->r3 = ADD32(ctx->r3, 0X1);
    // 0x801DB224: lwc1        $f16, 0xC($v0)
    ctx->f16.u32l = MEM_W(ctx->r2, 0XC);
    // 0x801DB228: mul.s       $f18, $f12, $f14
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f18.fl = MUL_S(ctx->f12.fl, ctx->f14.fl);
    // 0x801DB22C: beql        $v1, $a0, L_801DB260
    if (ctx->r3 == ctx->r4) {
        // 0x801DB230: add.s       $f14, $f16, $f18
        CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f14.fl = ctx->f16.fl + ctx->f18.fl;
            goto L_801DB260;
    }
    goto skip_1;
    // 0x801DB230: add.s       $f14, $f16, $f18
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f14.fl = ctx->f16.fl + ctx->f18.fl;
    skip_1:
    // 0x801DB234: add.s       $f14, $f16, $f18
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f14.fl = ctx->f16.fl + ctx->f18.fl;
L_801DB238:
    // 0x801DB238: lwc1        $f12, 0x1C($v0)
    ctx->f12.u32l = MEM_W(ctx->r2, 0X1C);
    // 0x801DB23C: lwc1        $f16, 0x10($v0)
    ctx->f16.u32l = MEM_W(ctx->r2, 0X10);
    // 0x801DB240: addiu       $v1, $v1, 0x1
    ctx->r3 = ADD32(ctx->r3, 0X1);
    // 0x801DB244: swc1        $f14, 0xC($v0)
    MEM_W(0XC, ctx->r2) = ctx->f14.u32l;
    // 0x801DB248: lwc1        $f14, 0x18($a1)
    ctx->f14.u32l = MEM_W(ctx->r5, 0X18);
    // 0x801DB24C: addiu       $v0, $v0, 0x4
    ctx->r2 = ADD32(ctx->r2, 0X4);
    // 0x801DB250: mul.s       $f18, $f12, $f14
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f18.fl = MUL_S(ctx->f12.fl, ctx->f14.fl);
    // 0x801DB254: bnel        $v1, $a0, L_801DB238
    if (ctx->r3 != ctx->r4) {
        // 0x801DB258: add.s       $f14, $f16, $f18
        CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f14.fl = ctx->f16.fl + ctx->f18.fl;
            goto L_801DB238;
    }
    goto skip_2;
    // 0x801DB258: add.s       $f14, $f16, $f18
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f14.fl = ctx->f16.fl + ctx->f18.fl;
    skip_2:
    // 0x801DB25C: add.s       $f14, $f16, $f18
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f14.fl = ctx->f16.fl + ctx->f18.fl;
L_801DB260:
    // 0x801DB260: addiu       $v0, $v0, 0x4
    ctx->r2 = ADD32(ctx->r2, 0X4);
    // 0x801DB264: swc1        $f14, 0x8($v0)
    MEM_W(0X8, ctx->r2) = ctx->f14.u32l;
    // 0x801DB268: b           L_801DB278
    // 0x801DB26C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_801DB278;
    // 0x801DB26C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x801DB270: sw          $zero, 0x0($a0)
    MEM_W(0X0, ctx->r4) = 0;
L_801DB274:
    // 0x801DB274: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_801DB278:
    // 0x801DB278: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x801DB27C: jr          $ra
    // 0x801DB280: nop

    return;
    // 0x801DB280: nop

;}
RECOMP_FUNC void func_801DB284(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801DB284: addiu       $sp, $sp, -0x58
    ctx->r29 = ADD32(ctx->r29, -0X58);
    // 0x801DB288: sw          $fp, 0x50($sp)
    MEM_W(0X50, ctx->r29) = ctx->r30;
    // 0x801DB28C: sw          $s6, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r22;
    // 0x801DB290: sw          $s4, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r20;
    // 0x801DB294: or          $s4, $a0, $zero
    ctx->r20 = ctx->r4 | 0;
    // 0x801DB298: or          $fp, $a3, $zero
    ctx->r30 = ctx->r7 | 0;
    // 0x801DB29C: sw          $ra, 0x54($sp)
    MEM_W(0X54, ctx->r29) = ctx->r31;
    // 0x801DB2A0: sw          $s7, 0x4C($sp)
    MEM_W(0X4C, ctx->r29) = ctx->r23;
    // 0x801DB2A4: sw          $s5, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r21;
    // 0x801DB2A8: sw          $s3, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r19;
    // 0x801DB2AC: sw          $s2, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r18;
    // 0x801DB2B0: sw          $s1, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r17;
    // 0x801DB2B4: sw          $s0, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r16;
    // 0x801DB2B8: sdc1        $f24, 0x28($sp)
    CHECK_FR(ctx, 24);
    SD(ctx->f24.u64, 0X28, ctx->r29);
    // 0x801DB2BC: sdc1        $f22, 0x20($sp)
    CHECK_FR(ctx, 22);
    SD(ctx->f22.u64, 0X20, ctx->r29);
    // 0x801DB2C0: sdc1        $f20, 0x18($sp)
    CHECK_FR(ctx, 20);
    SD(ctx->f20.u64, 0X18, ctx->r29);
    // 0x801DB2C4: sw          $a1, 0x5C($sp)
    MEM_W(0X5C, ctx->r29) = ctx->r5;
    // 0x801DB2C8: blez        $a3, L_801DB3F4
    if (SIGNED(ctx->r7) <= 0) {
        // 0x801DB2CC: or          $s6, $zero, $zero
        ctx->r22 = 0 | 0;
            goto L_801DB3F4;
    }
    // 0x801DB2CC: or          $s6, $zero, $zero
    ctx->r22 = 0 | 0;
    // 0x801DB2D0: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801DB2D4: lwc1        $f24, 0x5F14($at)
    ctx->f24.u32l = MEM_W(ctx->r1, 0X5F14);
    // 0x801DB2D8: lui         $at, 0x3F00
    ctx->r1 = S32(0X3F00 << 16);
    // 0x801DB2DC: mtc1        $at, $f22
    ctx->f22.u32l = ctx->r1;
    // 0x801DB2E0: lui         $at, 0x4380
    ctx->r1 = S32(0X4380 << 16);
    // 0x801DB2E4: mtc1        $at, $f20
    ctx->f20.u32l = ctx->r1;
    // 0x801DB2E8: or          $s5, $a2, $zero
    ctx->r21 = ctx->r6 | 0;
    // 0x801DB2EC: addiu       $s7, $zero, 0x168
    ctx->r23 = ADD32(0, 0X168);
    // 0x801DB2F0: addiu       $s3, $zero, 0x3
    ctx->r19 = ADD32(0, 0X3);
L_801DB2F4:
    // 0x801DB2F4: sw          $s3, 0x0($s4)
    MEM_W(0X0, ctx->r20) = ctx->r19;
    // 0x801DB2F8: sw          $zero, 0x4($s4)
    MEM_W(0X4, ctx->r20) = 0;
    // 0x801DB2FC: jal         0x801DAFB8
    // 0x801DB300: or          $a0, $s4, $zero
    ctx->r4 = ctx->r20 | 0;
    func_801DAFB8(rdram, ctx);
        goto after_0;
    // 0x801DB300: or          $a0, $s4, $zero
    ctx->r4 = ctx->r20 | 0;
    after_0:
    // 0x801DB304: or          $s1, $zero, $zero
    ctx->r17 = 0 | 0;
    // 0x801DB308: or          $s2, $s4, $zero
    ctx->r18 = ctx->r20 | 0;
    // 0x801DB30C: lw          $s0, 0x5C($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X5C);
L_801DB310:
    // 0x801DB310: jal         0x80047E50
    // 0x801DB314: nop

    SysUtils_Rand(rdram, ctx);
        goto after_1;
    // 0x801DB314: nop

    after_1:
    // 0x801DB318: lwc1        $f0, 0x18($s0)
    ctx->f0.u32l = MEM_W(ctx->r16, 0X18);
    // 0x801DB31C: lwc1        $f4, 0x0($s0)
    ctx->f4.u32l = MEM_W(ctx->r16, 0X0);
    // 0x801DB320: lwc1        $f6, 0xC($s0)
    ctx->f6.u32l = MEM_W(ctx->r16, 0XC);
    // 0x801DB324: mul.s       $f10, $f0, $f22
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f10.fl = MUL_S(ctx->f0.fl, ctx->f22.fl);
    // 0x801DB328: andi        $t6, $v0, 0xFF
    ctx->r14 = ctx->r2 & 0XFF;
    // 0x801DB32C: add.s       $f8, $f4, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = ctx->f4.fl + ctx->f6.fl;
    // 0x801DB330: mtc1        $t6, $f18
    ctx->f18.u32l = ctx->r14;
    // 0x801DB334: lui         $at, 0x4F80
    ctx->r1 = S32(0X4F80 << 16);
    // 0x801DB338: cvt.s.w     $f4, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    ctx->f4.fl = CVT_S_W(ctx->f18.u32l);
    // 0x801DB33C: bgez        $t6, L_801DB350
    if (SIGNED(ctx->r14) >= 0) {
        // 0x801DB340: sub.s       $f16, $f8, $f10
        CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f16.fl = ctx->f8.fl - ctx->f10.fl;
            goto L_801DB350;
    }
    // 0x801DB340: sub.s       $f16, $f8, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f16.fl = ctx->f8.fl - ctx->f10.fl;
    // 0x801DB344: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x801DB348: nop

    // 0x801DB34C: add.s       $f4, $f4, $f6
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f4.fl = ctx->f4.fl + ctx->f6.fl;
L_801DB350:
    // 0x801DB350: div.s       $f8, $f4, $f20
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f8.fl = DIV_S(ctx->f4.fl, ctx->f20.fl);
    // 0x801DB354: addiu       $s1, $s1, 0x1
    ctx->r17 = ADD32(ctx->r17, 0X1);
    // 0x801DB358: addiu       $s2, $s2, 0x4
    ctx->r18 = ADD32(ctx->r18, 0X4);
    // 0x801DB35C: addiu       $s0, $s0, 0x4
    ctx->r16 = ADD32(ctx->r16, 0X4);
    // 0x801DB360: mul.s       $f10, $f0, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = MUL_S(ctx->f0.fl, ctx->f8.fl);
    // 0x801DB364: add.s       $f18, $f10, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f18.fl = ctx->f10.fl + ctx->f16.fl;
    // 0x801DB368: bne         $s1, $s3, L_801DB310
    if (ctx->r17 != ctx->r19) {
        // 0x801DB36C: swc1        $f18, 0x8($s2)
        MEM_W(0X8, ctx->r18) = ctx->f18.u32l;
            goto L_801DB310;
    }
    // 0x801DB36C: swc1        $f18, 0x8($s2)
    MEM_W(0X8, ctx->r18) = ctx->f18.u32l;
    // 0x801DB370: jal         0x80047E50
    // 0x801DB374: swc1        $f24, 0x30($s4)
    MEM_W(0X30, ctx->r20) = ctx->f24.u32l;
    SysUtils_Rand(rdram, ctx);
        goto after_2;
    // 0x801DB374: swc1        $f24, 0x30($s4)
    MEM_W(0X30, ctx->r20) = ctx->f24.u32l;
    after_2:
    // 0x801DB378: divu        $zero, $v0, $s7
    lo = S32(U32(ctx->r2) / U32(ctx->r23)); hi = S32(U32(ctx->r2) % U32(ctx->r23));
    // 0x801DB37C: mfhi        $t7
    ctx->r15 = hi;
    // 0x801DB380: mtc1        $t7, $f6
    ctx->f6.u32l = ctx->r15;
    // 0x801DB384: bne         $s7, $zero, L_801DB390
    if (ctx->r23 != 0) {
        // 0x801DB388: nop
    
            goto L_801DB390;
    }
    // 0x801DB388: nop

    // 0x801DB38C: break       7
    do_break(2149430156);
L_801DB390:
    // 0x801DB390: lui         $at, 0x4F80
    ctx->r1 = S32(0X4F80 << 16);
    // 0x801DB394: bgez        $t7, L_801DB3A8
    if (SIGNED(ctx->r15) >= 0) {
        // 0x801DB398: cvt.s.w     $f4, $f6
        CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    ctx->f4.fl = CVT_S_W(ctx->f6.u32l);
            goto L_801DB3A8;
    }
    // 0x801DB398: cvt.s.w     $f4, $f6
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    ctx->f4.fl = CVT_S_W(ctx->f6.u32l);
    // 0x801DB39C: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x801DB3A0: nop

    // 0x801DB3A4: add.s       $f4, $f4, $f8
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f4.fl = ctx->f4.fl + ctx->f8.fl;
L_801DB3A8:
    // 0x801DB3A8: jal         0x80047E50
    // 0x801DB3AC: swc1        $f4, 0x0($s5)
    MEM_W(0X0, ctx->r21) = ctx->f4.u32l;
    SysUtils_Rand(rdram, ctx);
        goto after_3;
    // 0x801DB3AC: swc1        $f4, 0x0($s5)
    MEM_W(0X0, ctx->r21) = ctx->f4.u32l;
    after_3:
    // 0x801DB3B0: divu        $zero, $v0, $s7
    lo = S32(U32(ctx->r2) / U32(ctx->r23)); hi = S32(U32(ctx->r2) % U32(ctx->r23));
    // 0x801DB3B4: mfhi        $t8
    ctx->r24 = hi;
    // 0x801DB3B8: mtc1        $t8, $f10
    ctx->f10.u32l = ctx->r24;
    // 0x801DB3BC: bne         $s7, $zero, L_801DB3C8
    if (ctx->r23 != 0) {
        // 0x801DB3C0: nop
    
            goto L_801DB3C8;
    }
    // 0x801DB3C0: nop

    // 0x801DB3C4: break       7
    do_break(2149430212);
L_801DB3C8:
    // 0x801DB3C8: addiu       $s6, $s6, 0x1
    ctx->r22 = ADD32(ctx->r22, 0X1);
    // 0x801DB3CC: bgez        $t8, L_801DB3E4
    if (SIGNED(ctx->r24) >= 0) {
        // 0x801DB3D0: cvt.s.w     $f16, $f10
        CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    ctx->f16.fl = CVT_S_W(ctx->f10.u32l);
            goto L_801DB3E4;
    }
    // 0x801DB3D0: cvt.s.w     $f16, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    ctx->f16.fl = CVT_S_W(ctx->f10.u32l);
    // 0x801DB3D4: lui         $at, 0x4F80
    ctx->r1 = S32(0X4F80 << 16);
    // 0x801DB3D8: mtc1        $at, $f18
    ctx->f18.u32l = ctx->r1;
    // 0x801DB3DC: nop

    // 0x801DB3E0: add.s       $f16, $f16, $f18
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f16.fl = ctx->f16.fl + ctx->f18.fl;
L_801DB3E4:
    // 0x801DB3E4: addiu       $s5, $s5, 0x8
    ctx->r21 = ADD32(ctx->r21, 0X8);
    // 0x801DB3E8: addiu       $s4, $s4, 0x34
    ctx->r20 = ADD32(ctx->r20, 0X34);
    // 0x801DB3EC: bne         $s6, $fp, L_801DB2F4
    if (ctx->r22 != ctx->r30) {
        // 0x801DB3F0: swc1        $f16, -0x4($s5)
        MEM_W(-0X4, ctx->r21) = ctx->f16.u32l;
            goto L_801DB2F4;
    }
    // 0x801DB3F0: swc1        $f16, -0x4($s5)
    MEM_W(-0X4, ctx->r21) = ctx->f16.u32l;
L_801DB3F4:
    // 0x801DB3F4: lw          $ra, 0x54($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X54);
    // 0x801DB3F8: ldc1        $f20, 0x18($sp)
    CHECK_FR(ctx, 20);
    ctx->f20.u64 = LD(ctx->r29, 0X18);
    // 0x801DB3FC: ldc1        $f22, 0x20($sp)
    CHECK_FR(ctx, 22);
    ctx->f22.u64 = LD(ctx->r29, 0X20);
    // 0x801DB400: ldc1        $f24, 0x28($sp)
    CHECK_FR(ctx, 24);
    ctx->f24.u64 = LD(ctx->r29, 0X28);
    // 0x801DB404: lw          $s0, 0x30($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X30);
    // 0x801DB408: lw          $s1, 0x34($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X34);
    // 0x801DB40C: lw          $s2, 0x38($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X38);
    // 0x801DB410: lw          $s3, 0x3C($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X3C);
    // 0x801DB414: lw          $s4, 0x40($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X40);
    // 0x801DB418: lw          $s5, 0x44($sp)
    ctx->r21 = MEM_W(ctx->r29, 0X44);
    // 0x801DB41C: lw          $s6, 0x48($sp)
    ctx->r22 = MEM_W(ctx->r29, 0X48);
    // 0x801DB420: lw          $s7, 0x4C($sp)
    ctx->r23 = MEM_W(ctx->r29, 0X4C);
    // 0x801DB424: lw          $fp, 0x50($sp)
    ctx->r30 = MEM_W(ctx->r29, 0X50);
    // 0x801DB428: jr          $ra
    // 0x801DB42C: addiu       $sp, $sp, 0x58
    ctx->r29 = ADD32(ctx->r29, 0X58);
    return;
    // 0x801DB42C: addiu       $sp, $sp, 0x58
    ctx->r29 = ADD32(ctx->r29, 0X58);
;}
RECOMP_FUNC void func_801DB430(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801DB430: addiu       $sp, $sp, -0xA0
    ctx->r29 = ADD32(ctx->r29, -0XA0);
    // 0x801DB434: sw          $s7, 0x64($sp)
    MEM_W(0X64, ctx->r29) = ctx->r23;
    // 0x801DB438: sw          $s4, 0x58($sp)
    MEM_W(0X58, ctx->r29) = ctx->r20;
    // 0x801DB43C: sw          $s2, 0x50($sp)
    MEM_W(0X50, ctx->r29) = ctx->r18;
    // 0x801DB440: or          $s2, $a1, $zero
    ctx->r18 = ctx->r5 | 0;
    // 0x801DB444: or          $s4, $a0, $zero
    ctx->r20 = ctx->r4 | 0;
    // 0x801DB448: sw          $ra, 0x6C($sp)
    MEM_W(0X6C, ctx->r29) = ctx->r31;
    // 0x801DB44C: sw          $fp, 0x68($sp)
    MEM_W(0X68, ctx->r29) = ctx->r30;
    // 0x801DB450: sw          $s6, 0x60($sp)
    MEM_W(0X60, ctx->r29) = ctx->r22;
    // 0x801DB454: sw          $s5, 0x5C($sp)
    MEM_W(0X5C, ctx->r29) = ctx->r21;
    // 0x801DB458: sw          $s3, 0x54($sp)
    MEM_W(0X54, ctx->r29) = ctx->r19;
    // 0x801DB45C: sw          $s1, 0x4C($sp)
    MEM_W(0X4C, ctx->r29) = ctx->r17;
    // 0x801DB460: sw          $s0, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r16;
    // 0x801DB464: sdc1        $f30, 0x40($sp)
    CHECK_FR(ctx, 30);
    SD(ctx->f30.u64, 0X40, ctx->r29);
    // 0x801DB468: sdc1        $f28, 0x38($sp)
    CHECK_FR(ctx, 28);
    SD(ctx->f28.u64, 0X38, ctx->r29);
    // 0x801DB46C: sdc1        $f26, 0x30($sp)
    CHECK_FR(ctx, 26);
    SD(ctx->f26.u64, 0X30, ctx->r29);
    // 0x801DB470: sdc1        $f24, 0x28($sp)
    CHECK_FR(ctx, 24);
    SD(ctx->f24.u64, 0X28, ctx->r29);
    // 0x801DB474: sdc1        $f22, 0x20($sp)
    CHECK_FR(ctx, 22);
    SD(ctx->f22.u64, 0X20, ctx->r29);
    // 0x801DB478: sdc1        $f20, 0x18($sp)
    CHECK_FR(ctx, 20);
    SD(ctx->f20.u64, 0X18, ctx->r29);
    // 0x801DB47C: sw          $a3, 0xAC($sp)
    MEM_W(0XAC, ctx->r29) = ctx->r7;
    // 0x801DB480: blez        $a3, L_801DB8A8
    if (SIGNED(ctx->r7) <= 0) {
        // 0x801DB484: or          $s7, $zero, $zero
        ctx->r23 = 0 | 0;
            goto L_801DB8A8;
    }
    // 0x801DB484: or          $s7, $zero, $zero
    ctx->r23 = 0 | 0;
    // 0x801DB488: lui         $at, 0x41A0
    ctx->r1 = S32(0X41A0 << 16);
    // 0x801DB48C: mtc1        $at, $f30
    ctx->f30.u32l = ctx->r1;
    // 0x801DB490: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x801DB494: mtc1        $at, $f28
    ctx->f28.u32l = ctx->r1;
    // 0x801DB498: lui         $at, 0x4580
    ctx->r1 = S32(0X4580 << 16);
    // 0x801DB49C: mtc1        $at, $f26
    ctx->f26.u32l = ctx->r1;
    // 0x801DB4A0: lui         $at, 0x43B4
    ctx->r1 = S32(0X43B4 << 16);
    // 0x801DB4A4: lui         $s6, 0x8015
    ctx->r22 = S32(0X8015 << 16);
    // 0x801DB4A8: mtc1        $at, $f22
    ctx->f22.u32l = ctx->r1;
    // 0x801DB4AC: mtc1        $zero, $f24
    ctx->f24.u32l = 0;
    // 0x801DB4B0: addiu       $s6, $s6, 0x4350
    ctx->r22 = ADD32(ctx->r22, 0X4350);
    // 0x801DB4B4: or          $s3, $a2, $zero
    ctx->r19 = ctx->r6 | 0;
    // 0x801DB4B8: addiu       $fp, $zero, 0x1F
    ctx->r30 = ADD32(0, 0X1F);
    // 0x801DB4BC: addiu       $s5, $sp, 0x98
    ctx->r21 = ADD32(ctx->r29, 0X98);
L_801DB4C0:
    // 0x801DB4C0: jal         0x801DB024
    // 0x801DB4C4: or          $a0, $s4, $zero
    ctx->r4 = ctx->r20 | 0;
    func_801DB024(rdram, ctx);
        goto after_0;
    // 0x801DB4C4: or          $a0, $s4, $zero
    ctx->r4 = ctx->r20 | 0;
    after_0:
    // 0x801DB4C8: lwc1        $f4, 0x0($s3)
    ctx->f4.u32l = MEM_W(ctx->r19, 0X0);
    // 0x801DB4CC: mul.s       $f6, $f4, $f26
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 26);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f26.fl); 
    ctx->f6.fl = MUL_S(ctx->f4.fl, ctx->f26.fl);
    // 0x801DB4D0: div.s       $f8, $f6, $f22
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f8.fl = DIV_S(ctx->f6.fl, ctx->f22.fl);
    // 0x801DB4D4: trunc.w.s   $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.u32l = TRUNC_W_S(ctx->f8.fl);
    // 0x801DB4D8: mfc1        $t8, $f10
    ctx->r24 = (int32_t)ctx->f10.u32l;
    // 0x801DB4DC: nop

    // 0x801DB4E0: addiu       $t9, $t8, 0x400
    ctx->r25 = ADD32(ctx->r24, 0X400);
    // 0x801DB4E4: andi        $t0, $t9, 0xFFF
    ctx->r8 = ctx->r25 & 0XFFF;
    // 0x801DB4E8: sll         $t1, $t0, 2
    ctx->r9 = S32(ctx->r8 << 2);
    // 0x801DB4EC: addu        $t2, $s6, $t1
    ctx->r10 = ADD32(ctx->r22, ctx->r9);
    // 0x801DB4F0: lwc1        $f16, 0x0($t2)
    ctx->f16.u32l = MEM_W(ctx->r10, 0X0);
    // 0x801DB4F4: swc1        $f16, 0x8C($sp)
    MEM_W(0X8C, ctx->r29) = ctx->f16.u32l;
    // 0x801DB4F8: lwc1        $f18, 0x0($s3)
    ctx->f18.u32l = MEM_W(ctx->r19, 0X0);
    // 0x801DB4FC: mul.s       $f4, $f18, $f26
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 26);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f26.fl); 
    ctx->f4.fl = MUL_S(ctx->f18.fl, ctx->f26.fl);
    // 0x801DB500: div.s       $f6, $f4, $f22
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f6.fl = DIV_S(ctx->f4.fl, ctx->f22.fl);
    // 0x801DB504: trunc.w.s   $f8, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    ctx->f8.u32l = TRUNC_W_S(ctx->f6.fl);
    // 0x801DB508: mfc1        $t4, $f8
    ctx->r12 = (int32_t)ctx->f8.u32l;
    // 0x801DB50C: nop

    // 0x801DB510: andi        $t5, $t4, 0xFFF
    ctx->r13 = ctx->r12 & 0XFFF;
    // 0x801DB514: sll         $t6, $t5, 2
    ctx->r14 = S32(ctx->r13 << 2);
    // 0x801DB518: addu        $t7, $s6, $t6
    ctx->r15 = ADD32(ctx->r22, ctx->r14);
    // 0x801DB51C: lwc1        $f10, 0x0($t7)
    ctx->f10.u32l = MEM_W(ctx->r15, 0X0);
    // 0x801DB520: jal         0x80047E50
    // 0x801DB524: swc1        $f10, 0x94($sp)
    MEM_W(0X94, ctx->r29) = ctx->f10.u32l;
    SysUtils_Rand(rdram, ctx);
        goto after_1;
    // 0x801DB524: swc1        $f10, 0x94($sp)
    MEM_W(0X94, ctx->r29) = ctx->f10.u32l;
    after_1:
    // 0x801DB528: lwc1        $f16, 0x4($s3)
    ctx->f16.u32l = MEM_W(ctx->r19, 0X4);
    // 0x801DB52C: lwc1        $f10, 0x30($s2)
    ctx->f10.u32l = MEM_W(ctx->r18, 0X30);
    // 0x801DB530: andi        $t3, $v0, 0x3
    ctx->r11 = ctx->r2 & 0X3;
    // 0x801DB534: mul.s       $f18, $f16, $f26
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 26);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f26.fl); 
    ctx->f18.fl = MUL_S(ctx->f16.fl, ctx->f26.fl);
    // 0x801DB538: lui         $at, 0x4F80
    ctx->r1 = S32(0X4F80 << 16);
    // 0x801DB53C: div.s       $f4, $f18, $f22
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f4.fl = DIV_S(ctx->f18.fl, ctx->f22.fl);
    // 0x801DB540: mtc1        $t3, $f18
    ctx->f18.u32l = ctx->r11;
    // 0x801DB544: trunc.w.s   $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.u32l = TRUNC_W_S(ctx->f4.fl);
    // 0x801DB548: cvt.s.w     $f4, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    ctx->f4.fl = CVT_S_W(ctx->f18.u32l);
    // 0x801DB54C: mfc1        $t9, $f6
    ctx->r25 = (int32_t)ctx->f6.u32l;
    // 0x801DB550: nop

    // 0x801DB554: andi        $t0, $t9, 0xFFF
    ctx->r8 = ctx->r25 & 0XFFF;
    // 0x801DB558: sll         $t1, $t0, 2
    ctx->r9 = S32(ctx->r8 << 2);
    // 0x801DB55C: addu        $t2, $s6, $t1
    ctx->r10 = ADD32(ctx->r22, ctx->r9);
    // 0x801DB560: lwc1        $f8, 0x0($t2)
    ctx->f8.u32l = MEM_W(ctx->r10, 0X0);
    // 0x801DB564: mul.s       $f16, $f8, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f16.fl = MUL_S(ctx->f8.fl, ctx->f10.fl);
    // 0x801DB568: bgezl       $t3, L_801DB580
    if (SIGNED(ctx->r11) >= 0) {
        // 0x801DB56C: div.s       $f8, $f4, $f30
        CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 30);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f30.fl); 
    ctx->f8.fl = DIV_S(ctx->f4.fl, ctx->f30.fl);
            goto L_801DB580;
    }
    goto skip_0;
    // 0x801DB56C: div.s       $f8, $f4, $f30
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 30);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f30.fl); 
    ctx->f8.fl = DIV_S(ctx->f4.fl, ctx->f30.fl);
    skip_0:
    // 0x801DB570: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x801DB574: nop

    // 0x801DB578: add.s       $f4, $f4, $f6
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f4.fl = ctx->f4.fl + ctx->f6.fl;
    // 0x801DB57C: div.s       $f8, $f4, $f30
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 30);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f30.fl); 
    ctx->f8.fl = DIV_S(ctx->f4.fl, ctx->f30.fl);
L_801DB580:
    // 0x801DB580: mtc1        $zero, $f6
    ctx->f6.u32l = 0;
    // 0x801DB584: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801DB588: sub.s       $f10, $f28, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 28);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f28.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = ctx->f28.fl - ctx->f8.fl;
    // 0x801DB58C: mul.s       $f18, $f10, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f18.fl = MUL_S(ctx->f10.fl, ctx->f16.fl);
    // 0x801DB590: swc1        $f18, 0x90($sp)
    MEM_W(0X90, ctx->r29) = ctx->f18.u32l;
    // 0x801DB594: lwc1        $f8, 0x10($s4)
    ctx->f8.u32l = MEM_W(ctx->r20, 0X10);
    // 0x801DB598: lwc1        $f4, 0x4($s2)
    ctx->f4.u32l = MEM_W(ctx->r18, 0X4);
    // 0x801DB59C: sub.s       $f10, $f4, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = ctx->f4.fl - ctx->f8.fl;
    // 0x801DB5A0: mul.s       $f16, $f10, $f18
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f16.fl = MUL_S(ctx->f10.fl, ctx->f18.fl);
    // 0x801DB5A4: c.lt.s      $f6, $f16
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 16);
    c1cs = ctx->f6.fl < ctx->f16.fl;
    // 0x801DB5A8: nop

    // 0x801DB5AC: bc1fl       L_801DB5C4
    if (!c1cs) {
        // 0x801DB5B0: lwc1        $f0, 0x8C($sp)
        ctx->f0.u32l = MEM_W(ctx->r29, 0X8C);
            goto L_801DB5C4;
    }
    goto skip_1;
    // 0x801DB5B0: lwc1        $f0, 0x8C($sp)
    ctx->f0.u32l = MEM_W(ctx->r29, 0X8C);
    skip_1:
    // 0x801DB5B4: lwc1        $f4, 0x5F18($at)
    ctx->f4.u32l = MEM_W(ctx->r1, 0X5F18);
    // 0x801DB5B8: mul.s       $f14, $f18, $f4
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f14.fl = MUL_S(ctx->f18.fl, ctx->f4.fl);
    // 0x801DB5BC: swc1        $f14, 0x90($sp)
    MEM_W(0X90, ctx->r29) = ctx->f14.u32l;
    // 0x801DB5C0: lwc1        $f0, 0x8C($sp)
    ctx->f0.u32l = MEM_W(ctx->r29, 0X8C);
L_801DB5C4:
    // 0x801DB5C4: lwc1        $f14, 0x90($sp)
    ctx->f14.u32l = MEM_W(ctx->r29, 0X90);
    // 0x801DB5C8: lwc1        $f2, 0x94($sp)
    ctx->f2.u32l = MEM_W(ctx->r29, 0X94);
    // 0x801DB5CC: mul.s       $f8, $f0, $f0
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f8.fl = MUL_S(ctx->f0.fl, ctx->f0.fl);
    // 0x801DB5D0: nop

    // 0x801DB5D4: mul.s       $f10, $f14, $f14
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f10.fl = MUL_S(ctx->f14.fl, ctx->f14.fl);
    // 0x801DB5D8: add.s       $f6, $f8, $f10
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f6.fl = ctx->f8.fl + ctx->f10.fl;
    // 0x801DB5DC: mul.s       $f16, $f2, $f2
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f16.fl = MUL_S(ctx->f2.fl, ctx->f2.fl);
    // 0x801DB5E0: jal         0x800C7010
    // 0x801DB5E4: add.s       $f12, $f16, $f6
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f12.fl = ctx->f16.fl + ctx->f6.fl;
    _nsqrtf(rdram, ctx);
        goto after_2;
    // 0x801DB5E4: add.s       $f12, $f16, $f6
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f12.fl = ctx->f16.fl + ctx->f6.fl;
    after_2:
    // 0x801DB5E8: mov.s       $f20, $f0
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 0);
    ctx->f20.fl = ctx->f0.fl;
    // 0x801DB5EC: or          $s0, $s4, $zero
    ctx->r16 = ctx->r20 | 0;
    // 0x801DB5F0: addiu       $s1, $sp, 0x8C
    ctx->r17 = ADD32(ctx->r29, 0X8C);
L_801DB5F4:
    // 0x801DB5F4: lwc1        $f18, 0x0($s1)
    ctx->f18.u32l = MEM_W(ctx->r17, 0X0);
    // 0x801DB5F8: div.s       $f4, $f18, $f20
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f4.fl = DIV_S(ctx->f18.fl, ctx->f20.fl);
    // 0x801DB5FC: jal         0x80047E50
    // 0x801DB600: swc1        $f4, 0x18($s0)
    MEM_W(0X18, ctx->r16) = ctx->f4.u32l;
    SysUtils_Rand(rdram, ctx);
        goto after_3;
    // 0x801DB600: swc1        $f4, 0x18($s0)
    MEM_W(0X18, ctx->r16) = ctx->f4.u32l;
    after_3:
    // 0x801DB604: andi        $t4, $v0, 0x1
    ctx->r12 = ctx->r2 & 0X1;
    // 0x801DB608: mtc1        $t4, $f10
    ctx->f10.u32l = ctx->r12;
    // 0x801DB60C: lwc1        $f8, 0x24($s2)
    ctx->f8.u32l = MEM_W(ctx->r18, 0X24);
    // 0x801DB610: bgez        $t4, L_801DB628
    if (SIGNED(ctx->r12) >= 0) {
        // 0x801DB614: cvt.s.w     $f16, $f10
        CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    ctx->f16.fl = CVT_S_W(ctx->f10.u32l);
            goto L_801DB628;
    }
    // 0x801DB614: cvt.s.w     $f16, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    ctx->f16.fl = CVT_S_W(ctx->f10.u32l);
    // 0x801DB618: lui         $at, 0x4F80
    ctx->r1 = S32(0X4F80 << 16);
    // 0x801DB61C: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x801DB620: nop

    // 0x801DB624: add.s       $f16, $f16, $f6
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f16.fl = ctx->f16.fl + ctx->f6.fl;
L_801DB628:
    // 0x801DB628: add.s       $f18, $f8, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f18.fl = ctx->f8.fl + ctx->f16.fl;
    // 0x801DB62C: lwc1        $f4, 0x18($s0)
    ctx->f4.u32l = MEM_W(ctx->r16, 0X18);
    // 0x801DB630: lwc1        $f6, 0xC($s0)
    ctx->f6.u32l = MEM_W(ctx->r16, 0XC);
    // 0x801DB634: addiu       $s1, $s1, 0x4
    ctx->r17 = ADD32(ctx->r17, 0X4);
    // 0x801DB638: mul.s       $f10, $f4, $f18
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f10.fl = MUL_S(ctx->f4.fl, ctx->f18.fl);
    // 0x801DB63C: addiu       $s0, $s0, 0x4
    ctx->r16 = ADD32(ctx->r16, 0X4);
    // 0x801DB640: add.s       $f8, $f6, $f10
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f8.fl = ctx->f6.fl + ctx->f10.fl;
    // 0x801DB644: bne         $s1, $s5, L_801DB5F4
    if (ctx->r17 != ctx->r21) {
        // 0x801DB648: swc1        $f8, 0x8($s0)
        MEM_W(0X8, ctx->r16) = ctx->f8.u32l;
            goto L_801DB5F4;
    }
    // 0x801DB648: swc1        $f8, 0x8($s0)
    MEM_W(0X8, ctx->r16) = ctx->f8.u32l;
    // 0x801DB64C: lwc1        $f16, 0x0($s2)
    ctx->f16.u32l = MEM_W(ctx->r18, 0X0);
    // 0x801DB650: lwc1        $f4, 0xC($s4)
    ctx->f4.u32l = MEM_W(ctx->r20, 0XC);
    // 0x801DB654: sub.s       $f18, $f16, $f4
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f18.fl = ctx->f16.fl - ctx->f4.fl;
    // 0x801DB658: swc1        $f18, 0x8C($sp)
    MEM_W(0X8C, ctx->r29) = ctx->f18.u32l;
    // 0x801DB65C: lwc1        $f10, 0x14($s4)
    ctx->f10.u32l = MEM_W(ctx->r20, 0X14);
    // 0x801DB660: lwc1        $f6, 0x8($s2)
    ctx->f6.u32l = MEM_W(ctx->r18, 0X8);
    // 0x801DB664: lwc1        $f18, 0x8C($sp)
    ctx->f18.u32l = MEM_W(ctx->r29, 0X8C);
    // 0x801DB668: sub.s       $f8, $f6, $f10
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f8.fl = ctx->f6.fl - ctx->f10.fl;
    // 0x801DB66C: swc1        $f8, 0x94($sp)
    MEM_W(0X94, ctx->r29) = ctx->f8.u32l;
    // 0x801DB670: lwc1        $f16, 0x94($sp)
    ctx->f16.u32l = MEM_W(ctx->r29, 0X94);
    // 0x801DB674: mul.s       $f4, $f16, $f16
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f4.fl = MUL_S(ctx->f16.fl, ctx->f16.fl);
    // 0x801DB678: nop

    // 0x801DB67C: mul.s       $f6, $f18, $f18
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f6.fl = MUL_S(ctx->f18.fl, ctx->f18.fl);
    // 0x801DB680: jal         0x800C7010
    // 0x801DB684: add.s       $f12, $f4, $f6
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f12.fl = ctx->f4.fl + ctx->f6.fl;
    _nsqrtf(rdram, ctx);
        goto after_4;
    // 0x801DB684: add.s       $f12, $f4, $f6
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f12.fl = ctx->f4.fl + ctx->f6.fl;
    after_4:
    // 0x801DB688: c.lt.s      $f24, $f0
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 0);
    c1cs = ctx->f24.fl < ctx->f0.fl;
    // 0x801DB68C: mov.s       $f20, $f0
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 0);
    ctx->f20.fl = ctx->f0.fl;
    // 0x801DB690: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x801DB694: bc1fl       L_801DB6AC
    if (!c1cs) {
        // 0x801DB698: lui         $at, 0x4040
        ctx->r1 = S32(0X4040 << 16);
            goto L_801DB6AC;
    }
    goto skip_2;
    // 0x801DB698: lui         $at, 0x4040
    ctx->r1 = S32(0X4040 << 16);
    skip_2:
    // 0x801DB69C: mtc1        $at, $f10
    ctx->f10.u32l = ctx->r1;
    // 0x801DB6A0: nop

    // 0x801DB6A4: div.s       $f20, $f10, $f0
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f20.fl = DIV_S(ctx->f10.fl, ctx->f0.fl);
    // 0x801DB6A8: lui         $at, 0x4040
    ctx->r1 = S32(0X4040 << 16);
L_801DB6AC:
    // 0x801DB6AC: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x801DB6B0: lwc1        $f16, 0x8C($sp)
    ctx->f16.u32l = MEM_W(ctx->r29, 0X8C);
    // 0x801DB6B4: lwc1        $f4, 0x94($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X94);
    // 0x801DB6B8: mul.s       $f0, $f20, $f8
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f0.fl = MUL_S(ctx->f20.fl, ctx->f8.fl);
    // 0x801DB6BC: nop

    // 0x801DB6C0: mul.s       $f18, $f16, $f0
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f18.fl = MUL_S(ctx->f16.fl, ctx->f0.fl);
    // 0x801DB6C4: nop

    // 0x801DB6C8: mul.s       $f6, $f4, $f0
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f6.fl = MUL_S(ctx->f4.fl, ctx->f0.fl);
    // 0x801DB6CC: swc1        $f18, 0x8C($sp)
    MEM_W(0X8C, ctx->r29) = ctx->f18.u32l;
    // 0x801DB6D0: mul.s       $f4, $f18, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f4.fl = MUL_S(ctx->f18.fl, ctx->f18.fl);
    // 0x801DB6D4: swc1        $f6, 0x94($sp)
    MEM_W(0X94, ctx->r29) = ctx->f6.u32l;
    // 0x801DB6D8: lwc1        $f8, 0x28($s2)
    ctx->f8.u32l = MEM_W(ctx->r18, 0X28);
    // 0x801DB6DC: lwc1        $f10, 0x24($s2)
    ctx->f10.u32l = MEM_W(ctx->r18, 0X24);
    // 0x801DB6E0: div.s       $f16, $f10, $f8
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f16.fl = DIV_S(ctx->f10.fl, ctx->f8.fl);
    // 0x801DB6E4: swc1        $f16, 0x90($sp)
    MEM_W(0X90, ctx->r29) = ctx->f16.u32l;
    // 0x801DB6E8: lwc1        $f10, 0x90($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0X90);
    // 0x801DB6EC: mul.s       $f8, $f10, $f10
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f8.fl = MUL_S(ctx->f10.fl, ctx->f10.fl);
    // 0x801DB6F0: add.s       $f16, $f4, $f8
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f16.fl = ctx->f4.fl + ctx->f8.fl;
    // 0x801DB6F4: mul.s       $f18, $f6, $f6
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f18.fl = MUL_S(ctx->f6.fl, ctx->f6.fl);
    // 0x801DB6F8: jal         0x800C7010
    // 0x801DB6FC: add.s       $f12, $f18, $f16
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f12.fl = ctx->f18.fl + ctx->f16.fl;
    _nsqrtf(rdram, ctx);
        goto after_5;
    // 0x801DB6FC: add.s       $f12, $f18, $f16
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f12.fl = ctx->f18.fl + ctx->f16.fl;
    after_5:
    // 0x801DB700: lwc1        $f10, 0x8C($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0X8C);
    // 0x801DB704: div.s       $f4, $f10, $f0
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f4.fl = DIV_S(ctx->f10.fl, ctx->f0.fl);
    // 0x801DB708: lwc1        $f10, 0x18($s4)
    ctx->f10.u32l = MEM_W(ctx->r20, 0X18);
    // 0x801DB70C: swc1        $f4, 0x24($s4)
    MEM_W(0X24, ctx->r20) = ctx->f4.u32l;
    // 0x801DB710: lwc1        $f8, 0x90($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X90);
    // 0x801DB714: div.s       $f6, $f8, $f0
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f6.fl = DIV_S(ctx->f8.fl, ctx->f0.fl);
    // 0x801DB718: swc1        $f6, 0x28($s4)
    MEM_W(0X28, ctx->r20) = ctx->f6.u32l;
    // 0x801DB71C: lwc1        $f18, 0x94($sp)
    ctx->f18.u32l = MEM_W(ctx->r29, 0X94);
    // 0x801DB720: div.s       $f16, $f18, $f0
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f16.fl = DIV_S(ctx->f18.fl, ctx->f0.fl);
    // 0x801DB724: lwc1        $f18, 0x20($s4)
    ctx->f18.u32l = MEM_W(ctx->r20, 0X20);
    // 0x801DB728: swc1        $f16, 0x2C($s4)
    MEM_W(0X2C, ctx->r20) = ctx->f16.u32l;
    // 0x801DB72C: lwc1        $f4, 0x94($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X94);
    // 0x801DB730: lwc1        $f6, 0x8C($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X8C);
    // 0x801DB734: mul.s       $f8, $f10, $f4
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f8.fl = MUL_S(ctx->f10.fl, ctx->f4.fl);
    // 0x801DB738: nop

    // 0x801DB73C: mul.s       $f16, $f6, $f18
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f16.fl = MUL_S(ctx->f6.fl, ctx->f18.fl);
    // 0x801DB740: jal         0x80047E50
    // 0x801DB744: sub.s       $f20, $f8, $f16
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f20.fl = ctx->f8.fl - ctx->f16.fl;
    SysUtils_Rand(rdram, ctx);
        goto after_6;
    // 0x801DB744: sub.s       $f20, $f8, $f16
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f20.fl = ctx->f8.fl - ctx->f16.fl;
    after_6:
    // 0x801DB748: mtc1        $zero, $f10
    ctx->f10.u32l = 0;
    // 0x801DB74C: nop

    // 0x801DB750: c.le.s      $f10, $f20
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 20);
    c1cs = ctx->f10.fl <= ctx->f20.fl;
    // 0x801DB754: nop

    // 0x801DB758: bc1fl       L_801DB76C
    if (!c1cs) {
        // 0x801DB75C: lui         $at, 0xBF80
        ctx->r1 = S32(0XBF80 << 16);
            goto L_801DB76C;
    }
    goto skip_3;
    // 0x801DB75C: lui         $at, 0xBF80
    ctx->r1 = S32(0XBF80 << 16);
    skip_3:
    // 0x801DB760: b           L_801DB774
    // 0x801DB764: mov.s       $f0, $f28
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 28);
    ctx->f0.fl = ctx->f28.fl;
        goto L_801DB774;
    // 0x801DB764: mov.s       $f0, $f28
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 28);
    ctx->f0.fl = ctx->f28.fl;
    // 0x801DB768: lui         $at, 0xBF80
    ctx->r1 = S32(0XBF80 << 16);
L_801DB76C:
    // 0x801DB76C: mtc1        $at, $f0
    ctx->f0.u32l = ctx->r1;
    // 0x801DB770: nop

L_801DB774:
    // 0x801DB774: divu        $zero, $v0, $fp
    lo = S32(U32(ctx->r2) / U32(ctx->r30)); hi = S32(U32(ctx->r2) % U32(ctx->r30));
    // 0x801DB778: mfhi        $t5
    ctx->r13 = hi;
    // 0x801DB77C: mtc1        $t5, $f4
    ctx->f4.u32l = ctx->r13;
    // 0x801DB780: bne         $fp, $zero, L_801DB78C
    if (ctx->r30 != 0) {
        // 0x801DB784: nop
    
            goto L_801DB78C;
    }
    // 0x801DB784: nop

    // 0x801DB788: break       7
    do_break(2149431176);
L_801DB78C:
    // 0x801DB78C: lui         $at, 0x4F80
    ctx->r1 = S32(0X4F80 << 16);
    // 0x801DB790: bgez        $t5, L_801DB7A4
    if (SIGNED(ctx->r13) >= 0) {
        // 0x801DB794: cvt.s.w     $f6, $f4
        CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
            goto L_801DB7A4;
    }
    // 0x801DB794: cvt.s.w     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
    // 0x801DB798: mtc1        $at, $f18
    ctx->f18.u32l = ctx->r1;
    // 0x801DB79C: nop

    // 0x801DB7A0: add.s       $f6, $f6, $f18
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f6.fl = ctx->f6.fl + ctx->f18.fl;
L_801DB7A4:
    // 0x801DB7A4: lui         $at, 0x3E00
    ctx->r1 = S32(0X3E00 << 16);
    // 0x801DB7A8: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x801DB7AC: lwc1        $f10, 0x28($s2)
    ctx->f10.u32l = MEM_W(ctx->r18, 0X28);
    // 0x801DB7B0: lui         $at, 0xC3B4
    ctx->r1 = S32(0XC3B4 << 16);
    // 0x801DB7B4: mul.s       $f16, $f6, $f8
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f16.fl = MUL_S(ctx->f6.fl, ctx->f8.fl);
    // 0x801DB7B8: lwc1        $f6, 0x0($s3)
    ctx->f6.u32l = MEM_W(ctx->r19, 0X0);
    // 0x801DB7BC: add.s       $f4, $f10, $f16
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f4.fl = ctx->f10.fl + ctx->f16.fl;
    // 0x801DB7C0: mul.s       $f18, $f0, $f4
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f18.fl = MUL_S(ctx->f0.fl, ctx->f4.fl);
    // 0x801DB7C4: add.s       $f8, $f6, $f18
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f8.fl = ctx->f6.fl + ctx->f18.fl;
    // 0x801DB7C8: swc1        $f8, 0x0($s3)
    MEM_W(0X0, ctx->r19) = ctx->f8.u32l;
    // 0x801DB7CC: lwc1        $f2, 0x0($s3)
    ctx->f2.u32l = MEM_W(ctx->r19, 0X0);
    // 0x801DB7D0: c.lt.s      $f2, $f24
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 24);
    c1cs = ctx->f2.fl < ctx->f24.fl;
    // 0x801DB7D4: nop

    // 0x801DB7D8: bc1fl       L_801DB7EC
    if (!c1cs) {
        // 0x801DB7DC: mov.s       $f12, $f24
        CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 24);
    ctx->f12.fl = ctx->f24.fl;
            goto L_801DB7EC;
    }
    goto skip_4;
    // 0x801DB7DC: mov.s       $f12, $f24
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 24);
    ctx->f12.fl = ctx->f24.fl;
    skip_4:
    // 0x801DB7E0: b           L_801DB7EC
    // 0x801DB7E4: mov.s       $f12, $f22
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 22);
    ctx->f12.fl = ctx->f22.fl;
        goto L_801DB7EC;
    // 0x801DB7E4: mov.s       $f12, $f22
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 22);
    ctx->f12.fl = ctx->f22.fl;
    // 0x801DB7E8: mov.s       $f12, $f24
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 24);
    ctx->f12.fl = ctx->f24.fl;
L_801DB7EC:
    // 0x801DB7EC: c.lt.s      $f22, $f2
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 2);
    c1cs = ctx->f22.fl < ctx->f2.fl;
    // 0x801DB7F0: nop

    // 0x801DB7F4: bc1fl       L_801DB80C
    if (!c1cs) {
        // 0x801DB7F8: mov.s       $f0, $f24
        CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 24);
    ctx->f0.fl = ctx->f24.fl;
            goto L_801DB80C;
    }
    goto skip_5;
    // 0x801DB7F8: mov.s       $f0, $f24
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 24);
    ctx->f0.fl = ctx->f24.fl;
    skip_5:
    // 0x801DB7FC: mtc1        $at, $f0
    ctx->f0.u32l = ctx->r1;
    // 0x801DB800: b           L_801DB810
    // 0x801DB804: add.s       $f10, $f0, $f12
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f10.fl = ctx->f0.fl + ctx->f12.fl;
        goto L_801DB810;
    // 0x801DB804: add.s       $f10, $f0, $f12
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f10.fl = ctx->f0.fl + ctx->f12.fl;
    // 0x801DB808: mov.s       $f0, $f24
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 24);
    ctx->f0.fl = ctx->f24.fl;
L_801DB80C:
    // 0x801DB80C: add.s       $f10, $f0, $f12
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f10.fl = ctx->f0.fl + ctx->f12.fl;
L_801DB810:
    // 0x801DB810: add.s       $f16, $f2, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f16.fl = ctx->f2.fl + ctx->f10.fl;
    // 0x801DB814: jal         0x80047E50
    // 0x801DB818: swc1        $f16, 0x0($s3)
    MEM_W(0X0, ctx->r19) = ctx->f16.u32l;
    SysUtils_Rand(rdram, ctx);
        goto after_7;
    // 0x801DB818: swc1        $f16, 0x0($s3)
    MEM_W(0X0, ctx->r19) = ctx->f16.u32l;
    after_7:
    // 0x801DB81C: andi        $t6, $v0, 0x3
    ctx->r14 = ctx->r2 & 0X3;
    // 0x801DB820: mtc1        $t6, $f6
    ctx->f6.u32l = ctx->r14;
    // 0x801DB824: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801DB828: lwc1        $f4, 0x5F1C($at)
    ctx->f4.u32l = MEM_W(ctx->r1, 0X5F1C);
    // 0x801DB82C: bgez        $t6, L_801DB844
    if (SIGNED(ctx->r14) >= 0) {
        // 0x801DB830: cvt.s.w     $f18, $f6
        CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 6);
    ctx->f18.fl = CVT_S_W(ctx->f6.u32l);
            goto L_801DB844;
    }
    // 0x801DB830: cvt.s.w     $f18, $f6
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 6);
    ctx->f18.fl = CVT_S_W(ctx->f6.u32l);
    // 0x801DB834: lui         $at, 0x4F80
    ctx->r1 = S32(0X4F80 << 16);
    // 0x801DB838: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x801DB83C: nop

    // 0x801DB840: add.s       $f18, $f18, $f8
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f18.fl = ctx->f18.fl + ctx->f8.fl;
L_801DB844:
    // 0x801DB844: div.s       $f10, $f18, $f30
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 30);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f30.fl); 
    ctx->f10.fl = DIV_S(ctx->f18.fl, ctx->f30.fl);
    // 0x801DB848: lwc1        $f6, 0x2C($s2)
    ctx->f6.u32l = MEM_W(ctx->r18, 0X2C);
    // 0x801DB84C: lwc1        $f18, 0x4($s3)
    ctx->f18.u32l = MEM_W(ctx->r19, 0X4);
    // 0x801DB850: lui         $at, 0xC3B4
    ctx->r1 = S32(0XC3B4 << 16);
    // 0x801DB854: add.s       $f16, $f4, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f16.fl = ctx->f4.fl + ctx->f10.fl;
    // 0x801DB858: mul.s       $f8, $f6, $f16
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f8.fl = MUL_S(ctx->f6.fl, ctx->f16.fl);
    // 0x801DB85C: add.s       $f4, $f18, $f8
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f4.fl = ctx->f18.fl + ctx->f8.fl;
    // 0x801DB860: swc1        $f4, 0x4($s3)
    MEM_W(0X4, ctx->r19) = ctx->f4.u32l;
    // 0x801DB864: lwc1        $f2, 0x4($s3)
    ctx->f2.u32l = MEM_W(ctx->r19, 0X4);
    // 0x801DB868: c.lt.s      $f22, $f2
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 2);
    c1cs = ctx->f22.fl < ctx->f2.fl;
    // 0x801DB86C: nop

    // 0x801DB870: bc1fl       L_801DB888
    if (!c1cs) {
        // 0x801DB874: mov.s       $f0, $f24
        CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 24);
    ctx->f0.fl = ctx->f24.fl;
            goto L_801DB888;
    }
    goto skip_6;
    // 0x801DB874: mov.s       $f0, $f24
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 24);
    ctx->f0.fl = ctx->f24.fl;
    skip_6:
    // 0x801DB878: mtc1        $at, $f0
    ctx->f0.u32l = ctx->r1;
    // 0x801DB87C: b           L_801DB88C
    // 0x801DB880: add.s       $f10, $f2, $f0
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f10.fl = ctx->f2.fl + ctx->f0.fl;
        goto L_801DB88C;
    // 0x801DB880: add.s       $f10, $f2, $f0
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f10.fl = ctx->f2.fl + ctx->f0.fl;
    // 0x801DB884: mov.s       $f0, $f24
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 24);
    ctx->f0.fl = ctx->f24.fl;
L_801DB888:
    // 0x801DB888: add.s       $f10, $f2, $f0
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f10.fl = ctx->f2.fl + ctx->f0.fl;
L_801DB88C:
    // 0x801DB88C: addiu       $s7, $s7, 0x1
    ctx->r23 = ADD32(ctx->r23, 0X1);
    // 0x801DB890: addiu       $s3, $s3, 0x8
    ctx->r19 = ADD32(ctx->r19, 0X8);
    // 0x801DB894: addiu       $s4, $s4, 0x34
    ctx->r20 = ADD32(ctx->r20, 0X34);
    // 0x801DB898: swc1        $f10, -0x4($s3)
    MEM_W(-0X4, ctx->r19) = ctx->f10.u32l;
    // 0x801DB89C: lw          $t7, 0xAC($sp)
    ctx->r15 = MEM_W(ctx->r29, 0XAC);
    // 0x801DB8A0: bne         $s7, $t7, L_801DB4C0
    if (ctx->r23 != ctx->r15) {
        // 0x801DB8A4: nop
    
            goto L_801DB4C0;
    }
    // 0x801DB8A4: nop

L_801DB8A8:
    // 0x801DB8A8: lw          $ra, 0x6C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X6C);
    // 0x801DB8AC: ldc1        $f20, 0x18($sp)
    CHECK_FR(ctx, 20);
    ctx->f20.u64 = LD(ctx->r29, 0X18);
    // 0x801DB8B0: ldc1        $f22, 0x20($sp)
    CHECK_FR(ctx, 22);
    ctx->f22.u64 = LD(ctx->r29, 0X20);
    // 0x801DB8B4: ldc1        $f24, 0x28($sp)
    CHECK_FR(ctx, 24);
    ctx->f24.u64 = LD(ctx->r29, 0X28);
    // 0x801DB8B8: ldc1        $f26, 0x30($sp)
    CHECK_FR(ctx, 26);
    ctx->f26.u64 = LD(ctx->r29, 0X30);
    // 0x801DB8BC: ldc1        $f28, 0x38($sp)
    CHECK_FR(ctx, 28);
    ctx->f28.u64 = LD(ctx->r29, 0X38);
    // 0x801DB8C0: ldc1        $f30, 0x40($sp)
    CHECK_FR(ctx, 30);
    ctx->f30.u64 = LD(ctx->r29, 0X40);
    // 0x801DB8C4: lw          $s0, 0x48($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X48);
    // 0x801DB8C8: lw          $s1, 0x4C($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X4C);
    // 0x801DB8CC: lw          $s2, 0x50($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X50);
    // 0x801DB8D0: lw          $s3, 0x54($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X54);
    // 0x801DB8D4: lw          $s4, 0x58($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X58);
    // 0x801DB8D8: lw          $s5, 0x5C($sp)
    ctx->r21 = MEM_W(ctx->r29, 0X5C);
    // 0x801DB8DC: lw          $s6, 0x60($sp)
    ctx->r22 = MEM_W(ctx->r29, 0X60);
    // 0x801DB8E0: lw          $s7, 0x64($sp)
    ctx->r23 = MEM_W(ctx->r29, 0X64);
    // 0x801DB8E4: lw          $fp, 0x68($sp)
    ctx->r30 = MEM_W(ctx->r29, 0X68);
    // 0x801DB8E8: jr          $ra
    // 0x801DB8EC: addiu       $sp, $sp, 0xA0
    ctx->r29 = ADD32(ctx->r29, 0XA0);
    return;
    // 0x801DB8EC: addiu       $sp, $sp, 0xA0
    ctx->r29 = ADD32(ctx->r29, 0XA0);
;}
RECOMP_FUNC void func_801DB8F0(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801DB8F0: addiu       $sp, $sp, -0xD8
    ctx->r29 = ADD32(ctx->r29, -0XD8);
    // 0x801DB8F4: lui         $t7, 0x8022
    ctx->r15 = S32(0X8022 << 16);
    // 0x801DB8F8: sw          $ra, 0x5C($sp)
    MEM_W(0X5C, ctx->r29) = ctx->r31;
    // 0x801DB8FC: sw          $s6, 0x58($sp)
    MEM_W(0X58, ctx->r29) = ctx->r22;
    // 0x801DB900: sw          $s5, 0x54($sp)
    MEM_W(0X54, ctx->r29) = ctx->r21;
    // 0x801DB904: sw          $s4, 0x50($sp)
    MEM_W(0X50, ctx->r29) = ctx->r20;
    // 0x801DB908: sw          $s3, 0x4C($sp)
    MEM_W(0X4C, ctx->r29) = ctx->r19;
    // 0x801DB90C: sw          $s2, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r18;
    // 0x801DB910: sw          $s1, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r17;
    // 0x801DB914: sw          $s0, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r16;
    // 0x801DB918: sdc1        $f28, 0x38($sp)
    CHECK_FR(ctx, 28);
    SD(ctx->f28.u64, 0X38, ctx->r29);
    // 0x801DB91C: sdc1        $f26, 0x30($sp)
    CHECK_FR(ctx, 26);
    SD(ctx->f26.u64, 0X30, ctx->r29);
    // 0x801DB920: sdc1        $f24, 0x28($sp)
    CHECK_FR(ctx, 24);
    SD(ctx->f24.u64, 0X28, ctx->r29);
    // 0x801DB924: sdc1        $f22, 0x20($sp)
    CHECK_FR(ctx, 22);
    SD(ctx->f22.u64, 0X20, ctx->r29);
    // 0x801DB928: sdc1        $f20, 0x18($sp)
    CHECK_FR(ctx, 20);
    SD(ctx->f20.u64, 0X18, ctx->r29);
    // 0x801DB92C: sw          $a0, 0xD8($sp)
    MEM_W(0XD8, ctx->r29) = ctx->r4;
    // 0x801DB930: addiu       $t7, $t7, 0x5CB4
    ctx->r15 = ADD32(ctx->r15, 0X5CB4);
    // 0x801DB934: lw          $at, 0x0($t7)
    ctx->r1 = MEM_W(ctx->r15, 0X0);
    // 0x801DB938: addiu       $t6, $sp, 0xB0
    ctx->r14 = ADD32(ctx->r29, 0XB0);
    // 0x801DB93C: lw          $t0, 0x4($t7)
    ctx->r8 = MEM_W(ctx->r15, 0X4);
    // 0x801DB940: sw          $at, 0x0($t6)
    MEM_W(0X0, ctx->r14) = ctx->r1;
    // 0x801DB944: lw          $at, 0x8($t7)
    ctx->r1 = MEM_W(ctx->r15, 0X8);
    // 0x801DB948: lui         $t2, 0x8022
    ctx->r10 = S32(0X8022 << 16);
    // 0x801DB94C: addiu       $t2, $t2, 0x5CC0
    ctx->r10 = ADD32(ctx->r10, 0X5CC0);
    // 0x801DB950: addiu       $t5, $t2, 0x30
    ctx->r13 = ADD32(ctx->r10, 0X30);
    // 0x801DB954: addiu       $t1, $sp, 0x7C
    ctx->r9 = ADD32(ctx->r29, 0X7C);
    // 0x801DB958: sw          $t0, 0x4($t6)
    MEM_W(0X4, ctx->r14) = ctx->r8;
    // 0x801DB95C: sw          $at, 0x8($t6)
    MEM_W(0X8, ctx->r14) = ctx->r1;
L_801DB960:
    // 0x801DB960: lw          $at, 0x0($t2)
    ctx->r1 = MEM_W(ctx->r10, 0X0);
    // 0x801DB964: addiu       $t2, $t2, 0xC
    ctx->r10 = ADD32(ctx->r10, 0XC);
    // 0x801DB968: addiu       $t1, $t1, 0xC
    ctx->r9 = ADD32(ctx->r9, 0XC);
    // 0x801DB96C: sw          $at, -0xC($t1)
    MEM_W(-0XC, ctx->r9) = ctx->r1;
    // 0x801DB970: lw          $at, -0x8($t2)
    ctx->r1 = MEM_W(ctx->r10, -0X8);
    // 0x801DB974: sw          $at, -0x8($t1)
    MEM_W(-0X8, ctx->r9) = ctx->r1;
    // 0x801DB978: lw          $at, -0x4($t2)
    ctx->r1 = MEM_W(ctx->r10, -0X4);
    // 0x801DB97C: bne         $t2, $t5, L_801DB960
    if (ctx->r10 != ctx->r13) {
        // 0x801DB980: sw          $at, -0x4($t1)
        MEM_W(-0X4, ctx->r9) = ctx->r1;
            goto L_801DB960;
    }
    // 0x801DB980: sw          $at, -0x4($t1)
    MEM_W(-0X4, ctx->r9) = ctx->r1;
    // 0x801DB984: lw          $at, 0x0($t2)
    ctx->r1 = MEM_W(ctx->r10, 0X0);
    // 0x801DB988: sw          $at, 0x0($t1)
    MEM_W(0X0, ctx->r9) = ctx->r1;
    // 0x801DB98C: lw          $t9, 0xD8($sp)
    ctx->r25 = MEM_W(ctx->r29, 0XD8);
    // 0x801DB990: lw          $t8, 0x8($t9)
    ctx->r24 = MEM_W(ctx->r25, 0X8);
    // 0x801DB994: bnel        $t8, $zero, L_801DB9A8
    if (ctx->r24 != 0) {
        // 0x801DB998: lw          $t7, 0xD8($sp)
        ctx->r15 = MEM_W(ctx->r29, 0XD8);
            goto L_801DB9A8;
    }
    goto skip_0;
    // 0x801DB998: lw          $t7, 0xD8($sp)
    ctx->r15 = MEM_W(ctx->r29, 0XD8);
    skip_0:
    // 0x801DB99C: jal         0x800AB92C
    // 0x801DB9A0: nop

    func_800AB92C(rdram, ctx);
        goto after_0;
    // 0x801DB9A0: nop

    after_0:
    // 0x801DB9A4: lw          $t7, 0xD8($sp)
    ctx->r15 = MEM_W(ctx->r29, 0XD8);
L_801DB9A8:
    // 0x801DB9A8: addiu       $t6, $zero, 0xB
    ctx->r14 = ADD32(0, 0XB);
    // 0x801DB9AC: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801DB9B0: sw          $t6, -0x7858($at)
    MEM_W(-0X7858, ctx->r1) = ctx->r14;
    // 0x801DB9B4: lw          $v0, 0x8($t7)
    ctx->r2 = MEM_W(ctx->r15, 0X8);
    // 0x801DB9B8: lui         $s1, 0x8023
    ctx->r17 = S32(0X8023 << 16);
    // 0x801DB9BC: addiu       $s1, $s1, -0x7E3C
    ctx->r17 = ADD32(ctx->r17, -0X7E3C);
    // 0x801DB9C0: slti        $at, $v0, 0x35C
    ctx->r1 = SIGNED(ctx->r2) < 0X35C ? 1 : 0;
    // 0x801DB9C4: bne         $at, $zero, L_801DBE90
    if (ctx->r1 != 0) {
        // 0x801DB9C8: slti        $at, $v0, 0x5DD
        ctx->r1 = SIGNED(ctx->r2) < 0X5DD ? 1 : 0;
            goto L_801DBE90;
    }
    // 0x801DB9C8: slti        $at, $v0, 0x5DD
    ctx->r1 = SIGNED(ctx->r2) < 0X5DD ? 1 : 0;
    // 0x801DB9CC: beq         $at, $zero, L_801DBE90
    if (ctx->r1 == 0) {
        // 0x801DB9D0: addiu       $at, $zero, 0x35C
        ctx->r1 = ADD32(0, 0X35C);
            goto L_801DBE90;
    }
    // 0x801DB9D0: addiu       $at, $zero, 0x35C
    ctx->r1 = ADD32(0, 0X35C);
    // 0x801DB9D4: bne         $v0, $at, L_801DBC98
    if (ctx->r2 != ctx->r1) {
        // 0x801DB9D8: or          $s3, $zero, $zero
        ctx->r19 = 0 | 0;
            goto L_801DBC98;
    }
    // 0x801DB9D8: or          $s3, $zero, $zero
    ctx->r19 = 0 | 0;
    // 0x801DB9DC: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801DB9E0: lwc1        $f28, 0x5F20($at)
    ctx->f28.u32l = MEM_W(ctx->r1, 0X5F20);
    // 0x801DB9E4: lui         $at, 0x4080
    ctx->r1 = S32(0X4080 << 16);
    // 0x801DB9E8: mtc1        $at, $f24
    ctx->f24.u32l = ctx->r1;
    // 0x801DB9EC: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x801DB9F0: lui         $s1, 0x8023
    ctx->r17 = S32(0X8023 << 16);
    // 0x801DB9F4: lui         $s5, 0x8023
    ctx->r21 = S32(0X8023 << 16);
    // 0x801DB9F8: lui         $s2, 0x8023
    ctx->r18 = S32(0X8023 << 16);
    // 0x801DB9FC: mtc1        $at, $f22
    ctx->f22.u32l = ctx->r1;
    // 0x801DBA00: mtc1        $zero, $f26
    ctx->f26.u32l = 0;
    // 0x801DBA04: addiu       $s2, $s2, -0x7EE0
    ctx->r18 = ADD32(ctx->r18, -0X7EE0);
    // 0x801DBA08: addiu       $s5, $s5, -0x7EF0
    ctx->r21 = ADD32(ctx->r21, -0X7EF0);
    // 0x801DBA0C: addiu       $s1, $s1, -0x7E70
    ctx->r17 = ADD32(ctx->r17, -0X7E70);
    // 0x801DBA10: addiu       $s6, $zero, 0xF
    ctx->r22 = ADD32(0, 0XF);
    // 0x801DBA14: addiu       $s4, $zero, 0x3
    ctx->r20 = ADD32(0, 0X3);
L_801DBA18:
    // 0x801DBA18: sw          $s4, 0x0($s1)
    MEM_W(0X0, ctx->r17) = ctx->r20;
    // 0x801DBA1C: jal         0x80047E50
    // 0x801DBA20: sw          $zero, 0x4($s1)
    MEM_W(0X4, ctx->r17) = 0;
    SysUtils_Rand(rdram, ctx);
        goto after_1;
    // 0x801DBA20: sw          $zero, 0x4($s1)
    MEM_W(0X4, ctx->r17) = 0;
    after_1:
    // 0x801DBA24: divu        $zero, $v0, $s6
    lo = S32(U32(ctx->r2) / U32(ctx->r22)); hi = S32(U32(ctx->r2) % U32(ctx->r22));
    // 0x801DBA28: mfhi        $t0
    ctx->r8 = hi;
    // 0x801DBA2C: sw          $t0, 0x8($s1)
    MEM_W(0X8, ctx->r17) = ctx->r8;
    // 0x801DBA30: bne         $s6, $zero, L_801DBA3C
    if (ctx->r22 != 0) {
        // 0x801DBA34: nop
    
            goto L_801DBA3C;
    }
    // 0x801DBA34: nop

    // 0x801DBA38: break       7
    do_break(2149431864);
L_801DBA3C:
    // 0x801DBA3C: jal         0x80047E50
    // 0x801DBA40: nop

    SysUtils_Rand(rdram, ctx);
        goto after_2;
    // 0x801DBA40: nop

    after_2:
    // 0x801DBA44: mtc1        $s3, $f4
    ctx->f4.u32l = ctx->r19;
    // 0x801DBA48: lui         $at, 0x420C
    ctx->r1 = S32(0X420C << 16);
    // 0x801DBA4C: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x801DBA50: cvt.s.w     $f20, $f4
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 4);
    ctx->f20.fl = CVT_S_W(ctx->f4.u32l);
    // 0x801DBA54: andi        $t4, $v0, 0x7
    ctx->r12 = ctx->r2 & 0X7;
    // 0x801DBA58: mtc1        $t4, $f18
    ctx->f18.u32l = ctx->r12;
    // 0x801DBA5C: lwc1        $f6, 0xB0($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0XB0);
    // 0x801DBA60: lui         $at, 0x4F80
    ctx->r1 = S32(0X4F80 << 16);
    // 0x801DBA64: cvt.s.w     $f4, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    ctx->f4.fl = CVT_S_W(ctx->f18.u32l);
    // 0x801DBA68: mul.s       $f10, $f20, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = MUL_S(ctx->f20.fl, ctx->f8.fl);
    // 0x801DBA6C: bgez        $t4, L_801DBA80
    if (SIGNED(ctx->r12) >= 0) {
        // 0x801DBA70: add.s       $f16, $f6, $f10
        CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f16.fl = ctx->f6.fl + ctx->f10.fl;
            goto L_801DBA80;
    }
    // 0x801DBA70: add.s       $f16, $f6, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f16.fl = ctx->f6.fl + ctx->f10.fl;
    // 0x801DBA74: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x801DBA78: nop

    // 0x801DBA7C: add.s       $f4, $f4, $f8
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f4.fl = ctx->f4.fl + ctx->f8.fl;
L_801DBA80:
    // 0x801DBA80: add.s       $f6, $f4, $f16
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f6.fl = ctx->f4.fl + ctx->f16.fl;
    // 0x801DBA84: jal         0x80047E50
    // 0x801DBA88: swc1        $f6, 0xC($s1)
    MEM_W(0XC, ctx->r17) = ctx->f6.u32l;
    SysUtils_Rand(rdram, ctx);
        goto after_3;
    // 0x801DBA88: swc1        $f6, 0xC($s1)
    MEM_W(0XC, ctx->r17) = ctx->f6.u32l;
    after_3:
    // 0x801DBA8C: andi        $t3, $v0, 0x7FF
    ctx->r11 = ctx->r2 & 0X7FF;
    // 0x801DBA90: multu       $t3, $s3
    result = U64(U32(ctx->r11)) * U64(U32(ctx->r19)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x801DBA94: lui         $at, 0x4F80
    ctx->r1 = S32(0X4F80 << 16);
    // 0x801DBA98: mflo        $t5
    ctx->r13 = lo;
    // 0x801DBA9C: mtc1        $t5, $f10
    ctx->f10.u32l = ctx->r13;
    // 0x801DBAA0: bgez        $t5, L_801DBAB4
    if (SIGNED(ctx->r13) >= 0) {
        // 0x801DBAA4: cvt.s.w     $f12, $f10
        CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 10);
    ctx->f12.fl = CVT_S_W(ctx->f10.u32l);
            goto L_801DBAB4;
    }
    // 0x801DBAA4: cvt.s.w     $f12, $f10
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 10);
    ctx->f12.fl = CVT_S_W(ctx->f10.u32l);
    // 0x801DBAA8: mtc1        $at, $f18
    ctx->f18.u32l = ctx->r1;
    // 0x801DBAAC: nop

    // 0x801DBAB0: add.s       $f12, $f12, $f18
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f12.fl = ctx->f12.fl + ctx->f18.fl;
L_801DBAB4:
    // 0x801DBAB4: jal         0x800C7010
    // 0x801DBAB8: nop

    _nsqrtf(rdram, ctx);
        goto after_4;
    // 0x801DBAB8: nop

    after_4:
    // 0x801DBABC: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801DBAC0: lwc1        $f8, 0x5F24($at)
    ctx->f8.u32l = MEM_W(ctx->r1, 0X5F24);
    // 0x801DBAC4: lwc1        $f16, 0xB4($sp)
    ctx->f16.u32l = MEM_W(ctx->r29, 0XB4);
    // 0x801DBAC8: mul.s       $f4, $f0, $f8
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f4.fl = MUL_S(ctx->f0.fl, ctx->f8.fl);
    // 0x801DBACC: add.s       $f6, $f4, $f16
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f6.fl = ctx->f4.fl + ctx->f16.fl;
    // 0x801DBAD0: jal         0x80047E50
    // 0x801DBAD4: swc1        $f6, 0x10($s1)
    MEM_W(0X10, ctx->r17) = ctx->f6.u32l;
    SysUtils_Rand(rdram, ctx);
        goto after_5;
    // 0x801DBAD4: swc1        $f6, 0x10($s1)
    MEM_W(0X10, ctx->r17) = ctx->f6.u32l;
    after_5:
    // 0x801DBAD8: andi        $t2, $v0, 0x1FF
    ctx->r10 = ctx->r2 & 0X1FF;
    // 0x801DBADC: multu       $t2, $s3
    result = U64(U32(ctx->r10)) * U64(U32(ctx->r19)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x801DBAE0: lui         $at, 0x4F80
    ctx->r1 = S32(0X4F80 << 16);
    // 0x801DBAE4: mflo        $t1
    ctx->r9 = lo;
    // 0x801DBAE8: mtc1        $t1, $f10
    ctx->f10.u32l = ctx->r9;
    // 0x801DBAEC: bgez        $t1, L_801DBB00
    if (SIGNED(ctx->r9) >= 0) {
        // 0x801DBAF0: cvt.s.w     $f12, $f10
        CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 10);
    ctx->f12.fl = CVT_S_W(ctx->f10.u32l);
            goto L_801DBB00;
    }
    // 0x801DBAF0: cvt.s.w     $f12, $f10
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 10);
    ctx->f12.fl = CVT_S_W(ctx->f10.u32l);
    // 0x801DBAF4: mtc1        $at, $f18
    ctx->f18.u32l = ctx->r1;
    // 0x801DBAF8: nop

    // 0x801DBAFC: add.s       $f12, $f12, $f18
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f12.fl = ctx->f12.fl + ctx->f18.fl;
L_801DBB00:
    // 0x801DBB00: jal         0x800C7010
    // 0x801DBB04: nop

    _nsqrtf(rdram, ctx);
        goto after_6;
    // 0x801DBB04: nop

    after_6:
    // 0x801DBB08: andi        $t9, $s3, 0x4
    ctx->r25 = ctx->r19 & 0X4;
    // 0x801DBB0C: beq         $t9, $zero, L_801DBB1C
    if (ctx->r25 == 0) {
        // 0x801DBB10: mov.s       $f12, $f0
        CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 0);
    ctx->f12.fl = ctx->f0.fl;
            goto L_801DBB1C;
    }
    // 0x801DBB10: mov.s       $f12, $f0
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 0);
    ctx->f12.fl = ctx->f0.fl;
    // 0x801DBB14: b           L_801DBB28
    // 0x801DBB18: mov.s       $f2, $f22
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 22);
    ctx->f2.fl = ctx->f22.fl;
        goto L_801DBB28;
    // 0x801DBB18: mov.s       $f2, $f22
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 22);
    ctx->f2.fl = ctx->f22.fl;
L_801DBB1C:
    // 0x801DBB1C: lui         $at, 0xBF80
    ctx->r1 = S32(0XBF80 << 16);
    // 0x801DBB20: mtc1        $at, $f2
    ctx->f2.u32l = ctx->r1;
    // 0x801DBB24: nop

L_801DBB28:
    // 0x801DBB28: mul.s       $f8, $f2, $f12
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f8.fl = MUL_S(ctx->f2.fl, ctx->f12.fl);
    // 0x801DBB2C: lwc1        $f4, 0xB8($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0XB8);
    // 0x801DBB30: swc1        $f26, 0x24($s1)
    MEM_W(0X24, ctx->r17) = ctx->f26.u32l;
    // 0x801DBB34: swc1        $f22, 0x28($s1)
    MEM_W(0X28, ctx->r17) = ctx->f22.u32l;
    // 0x801DBB38: swc1        $f26, 0x2C($s1)
    MEM_W(0X2C, ctx->r17) = ctx->f26.u32l;
    // 0x801DBB3C: swc1        $f28, 0x30($s1)
    MEM_W(0X30, ctx->r17) = ctx->f28.u32l;
    // 0x801DBB40: add.s       $f16, $f8, $f4
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f16.fl = ctx->f8.fl + ctx->f4.fl;
    // 0x801DBB44: jal         0x80047E50
    // 0x801DBB48: swc1        $f16, 0x14($s1)
    MEM_W(0X14, ctx->r17) = ctx->f16.u32l;
    SysUtils_Rand(rdram, ctx);
        goto after_7;
    // 0x801DBB48: swc1        $f16, 0x14($s1)
    MEM_W(0X14, ctx->r17) = ctx->f16.u32l;
    after_7:
    // 0x801DBB4C: andi        $t8, $v0, 0xF
    ctx->r24 = ctx->r2 & 0XF;
    // 0x801DBB50: addiu       $t6, $t8, 0x3
    ctx->r14 = ADD32(ctx->r24, 0X3);
    // 0x801DBB54: sw          $t6, 0x0($s5)
    MEM_W(0X0, ctx->r21) = ctx->r14;
    // 0x801DBB58: jal         0x80047E50
    // 0x801DBB5C: swc1        $f26, 0x0($s2)
    MEM_W(0X0, ctx->r18) = ctx->f26.u32l;
    SysUtils_Rand(rdram, ctx);
        goto after_8;
    // 0x801DBB5C: swc1        $f26, 0x0($s2)
    MEM_W(0X0, ctx->r18) = ctx->f26.u32l;
    after_8:
    // 0x801DBB60: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
    // 0x801DBB64: jal         0x800C7010
    // 0x801DBB68: div.s       $f12, $f20, $f24
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 24);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f24.fl); 
    ctx->f12.fl = DIV_S(ctx->f20.fl, ctx->f24.fl);
    _nsqrtf(rdram, ctx);
        goto after_9;
    // 0x801DBB68: div.s       $f12, $f20, $f24
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 24);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f24.fl); 
    ctx->f12.fl = DIV_S(ctx->f20.fl, ctx->f24.fl);
    after_9:
    // 0x801DBB6C: andi        $t7, $s0, 0x3
    ctx->r15 = ctx->r16 & 0X3;
    // 0x801DBB70: addiu       $t0, $t7, 0x1
    ctx->r8 = ADD32(ctx->r15, 0X1);
    // 0x801DBB74: mtc1        $t0, $f6
    ctx->f6.u32l = ctx->r8;
    // 0x801DBB78: lui         $at, 0x4F80
    ctx->r1 = S32(0X4F80 << 16);
    // 0x801DBB7C: bgez        $t0, L_801DBB90
    if (SIGNED(ctx->r8) >= 0) {
        // 0x801DBB80: cvt.s.w     $f2, $f6
        CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 6);
    ctx->f2.fl = CVT_S_W(ctx->f6.u32l);
            goto L_801DBB90;
    }
    // 0x801DBB80: cvt.s.w     $f2, $f6
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 6);
    ctx->f2.fl = CVT_S_W(ctx->f6.u32l);
    // 0x801DBB84: mtc1        $at, $f10
    ctx->f10.u32l = ctx->r1;
    // 0x801DBB88: nop

    // 0x801DBB8C: add.s       $f2, $f2, $f10
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f2.fl = ctx->f2.fl + ctx->f10.fl;
L_801DBB90:
    // 0x801DBB90: add.s       $f18, $f2, $f2
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f18.fl = ctx->f2.fl + ctx->f2.fl;
    // 0x801DBB94: lui         $at, 0x4130
    ctx->r1 = S32(0X4130 << 16);
    // 0x801DBB98: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x801DBB9C: addiu       $s3, $s3, 0x1
    ctx->r19 = ADD32(ctx->r19, 0X1);
    // 0x801DBBA0: mul.s       $f8, $f0, $f18
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f8.fl = MUL_S(ctx->f0.fl, ctx->f18.fl);
    // 0x801DBBA4: slti        $at, $s3, 0x4
    ctx->r1 = SIGNED(ctx->r19) < 0X4 ? 1 : 0;
    // 0x801DBBA8: addiu       $s5, $s5, 0x4
    ctx->r21 = ADD32(ctx->r21, 0X4);
    // 0x801DBBAC: addiu       $s2, $s2, 0x8
    ctx->r18 = ADD32(ctx->r18, 0X8);
    // 0x801DBBB0: addiu       $s1, $s1, 0x34
    ctx->r17 = ADD32(ctx->r17, 0X34);
    // 0x801DBBB4: add.s       $f16, $f8, $f4
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f16.fl = ctx->f8.fl + ctx->f4.fl;
    // 0x801DBBB8: bne         $at, $zero, L_801DBA18
    if (ctx->r1 != 0) {
        // 0x801DBBBC: swc1        $f16, -0x4($s2)
        MEM_W(-0X4, ctx->r18) = ctx->f16.u32l;
            goto L_801DBA18;
    }
    // 0x801DBBBC: swc1        $f16, -0x4($s2)
    MEM_W(-0X4, ctx->r18) = ctx->f16.u32l;
    // 0x801DBBC0: jal         0x80047E50
    // 0x801DBBC4: or          $s3, $zero, $zero
    ctx->r19 = 0 | 0;
    SysUtils_Rand(rdram, ctx);
        goto after_10;
    // 0x801DBBC4: or          $s3, $zero, $zero
    ctx->r19 = 0 | 0;
    after_10:
    // 0x801DBBC8: andi        $t4, $v0, 0x3
    ctx->r12 = ctx->r2 & 0X3;
    // 0x801DBBCC: addiu       $t3, $t4, 0x2
    ctx->r11 = ADD32(ctx->r12, 0X2);
    // 0x801DBBD0: beq         $t3, $zero, L_801DBC98
    if (ctx->r11 == 0) {
        // 0x801DBBD4: lui         $at, 0x4148
        ctx->r1 = S32(0X4148 << 16);
            goto L_801DBC98;
    }
    // 0x801DBBD4: lui         $at, 0x4148
    ctx->r1 = S32(0X4148 << 16);
    // 0x801DBBD8: lui         $s5, 0x8023
    ctx->r21 = S32(0X8023 << 16);
    // 0x801DBBDC: lui         $s1, 0x8023
    ctx->r17 = S32(0X8023 << 16);
    // 0x801DBBE0: mtc1        $at, $f20
    ctx->f20.u32l = ctx->r1;
    // 0x801DBBE4: addiu       $s1, $s1, -0x7EF0
    ctx->r17 = ADD32(ctx->r17, -0X7EF0);
    // 0x801DBBE8: addiu       $s5, $s5, -0x7EE0
    ctx->r21 = ADD32(ctx->r21, -0X7EE0);
    // 0x801DBBEC: ori         $s2, $zero, 0xFFFF
    ctx->r18 = 0 | 0XFFFF;
L_801DBBF0:
    // 0x801DBBF0: jal         0x80047E50
    // 0x801DBBF4: nop

    SysUtils_Rand(rdram, ctx);
        goto after_11;
    // 0x801DBBF4: nop

    after_11:
    // 0x801DBBF8: andi        $t5, $v0, 0x3
    ctx->r13 = ctx->r2 & 0X3;
    // 0x801DBBFC: mtc1        $t5, $f6
    ctx->f6.u32l = ctx->r13;
    // 0x801DBC00: lui         $at, 0x4F80
    ctx->r1 = S32(0X4F80 << 16);
    // 0x801DBC04: bgez        $t5, L_801DBC18
    if (SIGNED(ctx->r13) >= 0) {
        // 0x801DBC08: cvt.s.w     $f10, $f6
        CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    ctx->f10.fl = CVT_S_W(ctx->f6.u32l);
            goto L_801DBC18;
    }
    // 0x801DBC08: cvt.s.w     $f10, $f6
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    ctx->f10.fl = CVT_S_W(ctx->f6.u32l);
    // 0x801DBC0C: mtc1        $at, $f18
    ctx->f18.u32l = ctx->r1;
    // 0x801DBC10: nop

    // 0x801DBC14: add.s       $f10, $f10, $f18
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f10.fl = ctx->f10.fl + ctx->f18.fl;
L_801DBC18:
    // 0x801DBC18: jal         0x800C7010
    // 0x801DBC1C: div.s       $f12, $f10, $f24
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 24);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f24.fl); 
    ctx->f12.fl = DIV_S(ctx->f10.fl, ctx->f24.fl);
    _nsqrtf(rdram, ctx);
        goto after_12;
    // 0x801DBC1C: div.s       $f12, $f10, $f24
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 24);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f24.fl); 
    ctx->f12.fl = DIV_S(ctx->f10.fl, ctx->f24.fl);
    after_12:
    // 0x801DBC20: jal         0x800C7010
    // 0x801DBC24: mov.s       $f12, $f0
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 0);
    ctx->f12.fl = ctx->f0.fl;
    _nsqrtf(rdram, ctx);
        goto after_13;
    // 0x801DBC24: mov.s       $f12, $f0
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 0);
    ctx->f12.fl = ctx->f0.fl;
    after_13:
    // 0x801DBC28: mul.s       $f8, $f0, $f24
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 24);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f24.fl); 
    ctx->f8.fl = MUL_S(ctx->f0.fl, ctx->f24.fl);
    // 0x801DBC2C: trunc.w.s   $f4, $f8
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    ctx->f4.u32l = TRUNC_W_S(ctx->f8.fl);
    // 0x801DBC30: mfc1        $v0, $f4
    ctx->r2 = (int32_t)ctx->f4.u32l;
    // 0x801DBC34: nop

    // 0x801DBC38: sll         $t1, $v0, 2
    ctx->r9 = S32(ctx->r2 << 2);
    // 0x801DBC3C: addu        $t9, $s1, $t1
    ctx->r25 = ADD32(ctx->r17, ctx->r9);
    // 0x801DBC40: sw          $s2, 0x0($t9)
    MEM_W(0X0, ctx->r25) = ctx->r18;
    // 0x801DBC44: jal         0x80047E50
    // 0x801DBC48: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
    SysUtils_Rand(rdram, ctx);
        goto after_14;
    // 0x801DBC48: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
    after_14:
    // 0x801DBC4C: andi        $t8, $v0, 0x3
    ctx->r24 = ctx->r2 & 0X3;
    // 0x801DBC50: mtc1        $t8, $f16
    ctx->f16.u32l = ctx->r24;
    // 0x801DBC54: sll         $t7, $s0, 3
    ctx->r15 = S32(ctx->r16 << 3);
    // 0x801DBC58: bgez        $t8, L_801DBC70
    if (SIGNED(ctx->r24) >= 0) {
        // 0x801DBC5C: cvt.s.w     $f6, $f16
        CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 16);
    ctx->f6.fl = CVT_S_W(ctx->f16.u32l);
            goto L_801DBC70;
    }
    // 0x801DBC5C: cvt.s.w     $f6, $f16
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 16);
    ctx->f6.fl = CVT_S_W(ctx->f16.u32l);
    // 0x801DBC60: lui         $at, 0x4F80
    ctx->r1 = S32(0X4F80 << 16);
    // 0x801DBC64: mtc1        $at, $f18
    ctx->f18.u32l = ctx->r1;
    // 0x801DBC68: nop

    // 0x801DBC6C: add.s       $f6, $f6, $f18
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f6.fl = ctx->f6.fl + ctx->f18.fl;
L_801DBC70:
    // 0x801DBC70: add.s       $f10, $f6, $f20
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f10.fl = ctx->f6.fl + ctx->f20.fl;
    // 0x801DBC74: addu        $t0, $s5, $t7
    ctx->r8 = ADD32(ctx->r21, ctx->r15);
    // 0x801DBC78: addiu       $s3, $s3, 0x1
    ctx->r19 = ADD32(ctx->r19, 0X1);
    // 0x801DBC7C: jal         0x80047E50
    // 0x801DBC80: swc1        $f10, 0x4($t0)
    MEM_W(0X4, ctx->r8) = ctx->f10.u32l;
    SysUtils_Rand(rdram, ctx);
        goto after_15;
    // 0x801DBC80: swc1        $f10, 0x4($t0)
    MEM_W(0X4, ctx->r8) = ctx->f10.u32l;
    after_15:
    // 0x801DBC84: andi        $t4, $v0, 0x3
    ctx->r12 = ctx->r2 & 0X3;
    // 0x801DBC88: addiu       $t3, $t4, 0x2
    ctx->r11 = ADD32(ctx->r12, 0X2);
    // 0x801DBC8C: sltu        $at, $s3, $t3
    ctx->r1 = ctx->r19 < ctx->r11 ? 1 : 0;
    // 0x801DBC90: bne         $at, $zero, L_801DBBF0
    if (ctx->r1 != 0) {
        // 0x801DBC94: nop
    
            goto L_801DBBF0;
    }
    // 0x801DBC94: nop

L_801DBC98:
    // 0x801DBC98: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801DBC9C: lwc1        $f28, 0x5F28($at)
    ctx->f28.u32l = MEM_W(ctx->r1, 0X5F28);
    // 0x801DBCA0: lui         $at, 0x4334
    ctx->r1 = S32(0X4334 << 16);
    // 0x801DBCA4: mtc1        $at, $f24
    ctx->f24.u32l = ctx->r1;
    // 0x801DBCA8: lui         $at, 0x43B4
    ctx->r1 = S32(0X43B4 << 16);
    // 0x801DBCAC: mtc1        $at, $f22
    ctx->f22.u32l = ctx->r1;
    // 0x801DBCB0: lui         $at, 0x4580
    ctx->r1 = S32(0X4580 << 16);
    // 0x801DBCB4: lui         $s1, 0x8023
    ctx->r17 = S32(0X8023 << 16);
    // 0x801DBCB8: lui         $s5, 0x8023
    ctx->r21 = S32(0X8023 << 16);
    // 0x801DBCBC: lui         $s2, 0x8023
    ctx->r18 = S32(0X8023 << 16);
    // 0x801DBCC0: lui         $s6, 0x8015
    ctx->r22 = S32(0X8015 << 16);
    // 0x801DBCC4: mtc1        $zero, $f26
    ctx->f26.u32l = 0;
    // 0x801DBCC8: mtc1        $at, $f20
    ctx->f20.u32l = ctx->r1;
    // 0x801DBCCC: addiu       $s4, $zero, 0x3
    ctx->r20 = ADD32(0, 0X3);
    // 0x801DBCD0: addiu       $s6, $s6, 0x4350
    ctx->r22 = ADD32(ctx->r22, 0X4350);
    // 0x801DBCD4: addiu       $s2, $s2, -0x7EE0
    ctx->r18 = ADD32(ctx->r18, -0X7EE0);
    // 0x801DBCD8: addiu       $s5, $s5, -0x7EF0
    ctx->r21 = ADD32(ctx->r21, -0X7EF0);
    // 0x801DBCDC: addiu       $s1, $s1, -0x7E70
    ctx->r17 = ADD32(ctx->r17, -0X7E70);
    // 0x801DBCE0: addiu       $s3, $sp, 0xCC
    ctx->r19 = ADD32(ctx->r29, 0XCC);
L_801DBCE4:
    // 0x801DBCE4: lw          $v0, 0x8($s1)
    ctx->r2 = MEM_W(ctx->r17, 0X8);
    // 0x801DBCE8: mul.s       $f10, $f28, $f28
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 28);
    CHECK_FR(ctx, 28);
    NAN_CHECK(ctx->f28.fl); NAN_CHECK(ctx->f28.fl); 
    ctx->f10.fl = MUL_S(ctx->f28.fl, ctx->f28.fl);
    // 0x801DBCEC: addiu       $s0, $zero, 0x1
    ctx->r16 = ADD32(0, 0X1);
    // 0x801DBCF0: slti        $at, $v0, 0x10
    ctx->r1 = SIGNED(ctx->r2) < 0X10 ? 1 : 0;
    // 0x801DBCF4: beq         $at, $zero, L_801DBD04
    if (ctx->r1 == 0) {
        // 0x801DBCF8: nop
    
            goto L_801DBD04;
    }
    // 0x801DBCF8: nop

    // 0x801DBCFC: b           L_801DBD04
    // 0x801DBD00: addiu       $s0, $zero, 0x2
    ctx->r16 = ADD32(0, 0X2);
        goto L_801DBD04;
    // 0x801DBD00: addiu       $s0, $zero, 0x2
    ctx->r16 = ADD32(0, 0X2);
L_801DBD04:
    // 0x801DBD04: addu        $t5, $v0, $s0
    ctx->r13 = ADD32(ctx->r2, ctx->r16);
    // 0x801DBD08: sw          $t5, 0x8($s1)
    MEM_W(0X8, ctx->r17) = ctx->r13;
    // 0x801DBD0C: lw          $t2, 0x0($s5)
    ctx->r10 = MEM_W(ctx->r21, 0X0);
    // 0x801DBD10: slti        $at, $t5, 0x10
    ctx->r1 = SIGNED(ctx->r13) < 0X10 ? 1 : 0;
    // 0x801DBD14: blezl       $t2, L_801DBD3C
    if (SIGNED(ctx->r10) <= 0) {
        // 0x801DBD18: lw          $t6, 0x8($s1)
        ctx->r14 = MEM_W(ctx->r17, 0X8);
            goto L_801DBD3C;
    }
    goto skip_1;
    // 0x801DBD18: lw          $t6, 0x8($s1)
    ctx->r14 = MEM_W(ctx->r17, 0X8);
    skip_1:
    // 0x801DBD1C: bnel        $at, $zero, L_801DBD54
    if (ctx->r1 != 0) {
        // 0x801DBD20: lwc1        $f8, 0x0($s2)
        ctx->f8.u32l = MEM_W(ctx->r18, 0X0);
            goto L_801DBD54;
    }
    goto skip_2;
    // 0x801DBD20: lwc1        $f8, 0x0($s2)
    ctx->f8.u32l = MEM_W(ctx->r18, 0X0);
    skip_2:
    // 0x801DBD24: sw          $zero, 0x8($s1)
    MEM_W(0X8, ctx->r17) = 0;
    // 0x801DBD28: lw          $t9, 0x0($s5)
    ctx->r25 = MEM_W(ctx->r21, 0X0);
    // 0x801DBD2C: addiu       $t8, $t9, -0x1
    ctx->r24 = ADD32(ctx->r25, -0X1);
    // 0x801DBD30: b           L_801DBD50
    // 0x801DBD34: sw          $t8, 0x0($s5)
    MEM_W(0X0, ctx->r21) = ctx->r24;
        goto L_801DBD50;
    // 0x801DBD34: sw          $t8, 0x0($s5)
    MEM_W(0X0, ctx->r21) = ctx->r24;
    // 0x801DBD38: lw          $t6, 0x8($s1)
    ctx->r14 = MEM_W(ctx->r17, 0X8);
L_801DBD3C:
    // 0x801DBD3C: addiu       $t7, $zero, 0x19
    ctx->r15 = ADD32(0, 0X19);
    // 0x801DBD40: slti        $at, $t6, 0x2D
    ctx->r1 = SIGNED(ctx->r14) < 0X2D ? 1 : 0;
    // 0x801DBD44: bnel        $at, $zero, L_801DBD54
    if (ctx->r1 != 0) {
        // 0x801DBD48: lwc1        $f8, 0x0($s2)
        ctx->f8.u32l = MEM_W(ctx->r18, 0X0);
            goto L_801DBD54;
    }
    goto skip_3;
    // 0x801DBD48: lwc1        $f8, 0x0($s2)
    ctx->f8.u32l = MEM_W(ctx->r18, 0X0);
    skip_3:
    // 0x801DBD4C: sw          $t7, 0x8($s1)
    MEM_W(0X8, ctx->r17) = ctx->r15;
L_801DBD50:
    // 0x801DBD50: lwc1        $f8, 0x0($s2)
    ctx->f8.u32l = MEM_W(ctx->r18, 0X0);
L_801DBD54:
    // 0x801DBD54: mul.s       $f4, $f8, $f20
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f4.fl = MUL_S(ctx->f8.fl, ctx->f20.fl);
    // 0x801DBD58: div.s       $f16, $f4, $f22
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f16.fl = DIV_S(ctx->f4.fl, ctx->f22.fl);
    // 0x801DBD5C: trunc.w.s   $f18, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    ctx->f18.u32l = TRUNC_W_S(ctx->f16.fl);
    // 0x801DBD60: mfc1        $v0, $f18
    ctx->r2 = (int32_t)ctx->f18.u32l;
    // 0x801DBD64: nop

    // 0x801DBD68: addiu       $t4, $v0, 0x400
    ctx->r12 = ADD32(ctx->r2, 0X400);
    // 0x801DBD6C: andi        $t3, $t4, 0xFFF
    ctx->r11 = ctx->r12 & 0XFFF;
    // 0x801DBD70: sll         $t5, $t3, 2
    ctx->r13 = S32(ctx->r11 << 2);
    // 0x801DBD74: addu        $t2, $s6, $t5
    ctx->r10 = ADD32(ctx->r22, ctx->r13);
    // 0x801DBD78: lwc1        $f0, 0x0($t2)
    ctx->f0.u32l = MEM_W(ctx->r10, 0X0);
    // 0x801DBD7C: andi        $t1, $v0, 0xFFF
    ctx->r9 = ctx->r2 & 0XFFF;
    // 0x801DBD80: sll         $t9, $t1, 2
    ctx->r25 = S32(ctx->r9 << 2);
    // 0x801DBD84: mul.s       $f6, $f0, $f0
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f6.fl = MUL_S(ctx->f0.fl, ctx->f0.fl);
    // 0x801DBD88: addu        $t8, $s6, $t9
    ctx->r24 = ADD32(ctx->r22, ctx->r25);
    // 0x801DBD8C: lwc1        $f14, 0x0($t8)
    ctx->f14.u32l = MEM_W(ctx->r24, 0X0);
    // 0x801DBD90: swc1        $f28, 0xC4($sp)
    MEM_W(0XC4, ctx->r29) = ctx->f28.u32l;
    // 0x801DBD94: swc1        $f0, 0xC0($sp)
    MEM_W(0XC0, ctx->r29) = ctx->f0.u32l;
    // 0x801DBD98: mul.s       $f4, $f14, $f14
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f4.fl = MUL_S(ctx->f14.fl, ctx->f14.fl);
    // 0x801DBD9C: swc1        $f14, 0xC8($sp)
    MEM_W(0XC8, ctx->r29) = ctx->f14.u32l;
    // 0x801DBDA0: add.s       $f8, $f6, $f10
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f8.fl = ctx->f6.fl + ctx->f10.fl;
    // 0x801DBDA4: jal         0x800C7010
    // 0x801DBDA8: add.s       $f12, $f4, $f8
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f12.fl = ctx->f4.fl + ctx->f8.fl;
    _nsqrtf(rdram, ctx);
        goto after_16;
    // 0x801DBDA8: add.s       $f12, $f4, $f8
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f12.fl = ctx->f4.fl + ctx->f8.fl;
    after_16:
    // 0x801DBDAC: or          $v0, $s1, $zero
    ctx->r2 = ctx->r17 | 0;
    // 0x801DBDB0: addiu       $v1, $sp, 0xC0
    ctx->r3 = ADD32(ctx->r29, 0XC0);
L_801DBDB4:
    // 0x801DBDB4: lwc1        $f16, 0x0($v1)
    ctx->f16.u32l = MEM_W(ctx->r3, 0X0);
    // 0x801DBDB8: addiu       $v1, $v1, 0x4
    ctx->r3 = ADD32(ctx->r3, 0X4);
    // 0x801DBDBC: sltu        $at, $v1, $s3
    ctx->r1 = ctx->r3 < ctx->r19 ? 1 : 0;
    // 0x801DBDC0: div.s       $f18, $f16, $f0
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f18.fl = DIV_S(ctx->f16.fl, ctx->f0.fl);
    // 0x801DBDC4: addiu       $v0, $v0, 0x4
    ctx->r2 = ADD32(ctx->r2, 0X4);
    // 0x801DBDC8: bne         $at, $zero, L_801DBDB4
    if (ctx->r1 != 0) {
        // 0x801DBDCC: swc1        $f18, 0x14($v0)
        MEM_W(0X14, ctx->r2) = ctx->f18.u32l;
            goto L_801DBDB4;
    }
    // 0x801DBDCC: swc1        $f18, 0x14($v0)
    MEM_W(0X14, ctx->r2) = ctx->f18.u32l;
    // 0x801DBDD0: or          $s0, $zero, $zero
    ctx->r16 = 0 | 0;
    // 0x801DBDD4: or          $v0, $s1, $zero
    ctx->r2 = ctx->r17 | 0;
    // 0x801DBDD8: lwc1        $f12, 0x18($v0)
    ctx->f12.u32l = MEM_W(ctx->r2, 0X18);
    // 0x801DBDDC: lwc1        $f14, 0x4($s2)
    ctx->f14.u32l = MEM_W(ctx->r18, 0X4);
    // 0x801DBDE0: addiu       $s0, $s0, 0x1
    ctx->r16 = ADD32(ctx->r16, 0X1);
    // 0x801DBDE4: lwc1        $f16, 0xC($v0)
    ctx->f16.u32l = MEM_W(ctx->r2, 0XC);
    // 0x801DBDE8: mul.s       $f18, $f12, $f14
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f18.fl = MUL_S(ctx->f12.fl, ctx->f14.fl);
    // 0x801DBDEC: beql        $s0, $s4, L_801DBE20
    if (ctx->r16 == ctx->r20) {
        // 0x801DBDF0: add.s       $f14, $f16, $f18
        CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f14.fl = ctx->f16.fl + ctx->f18.fl;
            goto L_801DBE20;
    }
    goto skip_4;
    // 0x801DBDF0: add.s       $f14, $f16, $f18
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f14.fl = ctx->f16.fl + ctx->f18.fl;
    skip_4:
    // 0x801DBDF4: add.s       $f14, $f16, $f18
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f14.fl = ctx->f16.fl + ctx->f18.fl;
L_801DBDF8:
    // 0x801DBDF8: lwc1        $f12, 0x1C($v0)
    ctx->f12.u32l = MEM_W(ctx->r2, 0X1C);
    // 0x801DBDFC: lwc1        $f16, 0x10($v0)
    ctx->f16.u32l = MEM_W(ctx->r2, 0X10);
    // 0x801DBE00: addiu       $s0, $s0, 0x1
    ctx->r16 = ADD32(ctx->r16, 0X1);
    // 0x801DBE04: swc1        $f14, 0xC($v0)
    MEM_W(0XC, ctx->r2) = ctx->f14.u32l;
    // 0x801DBE08: lwc1        $f14, 0x4($s2)
    ctx->f14.u32l = MEM_W(ctx->r18, 0X4);
    // 0x801DBE0C: addiu       $v0, $v0, 0x4
    ctx->r2 = ADD32(ctx->r2, 0X4);
    // 0x801DBE10: mul.s       $f18, $f12, $f14
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f18.fl = MUL_S(ctx->f12.fl, ctx->f14.fl);
    // 0x801DBE14: bnel        $s0, $s4, L_801DBDF8
    if (ctx->r16 != ctx->r20) {
        // 0x801DBE18: add.s       $f14, $f16, $f18
        CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f14.fl = ctx->f16.fl + ctx->f18.fl;
            goto L_801DBDF8;
    }
    goto skip_5;
    // 0x801DBE18: add.s       $f14, $f16, $f18
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f14.fl = ctx->f16.fl + ctx->f18.fl;
    skip_5:
    // 0x801DBE1C: add.s       $f14, $f16, $f18
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f14.fl = ctx->f16.fl + ctx->f18.fl;
L_801DBE20:
    // 0x801DBE20: addiu       $v0, $v0, 0x4
    ctx->r2 = ADD32(ctx->r2, 0X4);
    // 0x801DBE24: swc1        $f14, 0x8($v0)
    MEM_W(0X8, ctx->r2) = ctx->f14.u32l;
    // 0x801DBE28: lwc1        $f18, 0x14($s1)
    ctx->f18.u32l = MEM_W(ctx->r17, 0X14);
    // 0x801DBE2C: lwc1        $f6, 0xB8($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0XB8);
    // 0x801DBE30: sub.s       $f14, $f18, $f6
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f14.fl = ctx->f18.fl - ctx->f6.fl;
    // 0x801DBE34: c.le.s      $f26, $f14
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 14);
    c1cs = ctx->f26.fl <= ctx->f14.fl;
    // 0x801DBE38: nop

    // 0x801DBE3C: bc1f        L_801DBE54
    if (!c1cs) {
        // 0x801DBE40: nop
    
            goto L_801DBE54;
    }
    // 0x801DBE40: nop

    // 0x801DBE44: jal         0x800C7010
    // 0x801DBE48: mov.s       $f12, $f14
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 14);
    ctx->f12.fl = ctx->f14.fl;
    _nsqrtf(rdram, ctx);
        goto after_17;
    // 0x801DBE48: mov.s       $f12, $f14
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 14);
    ctx->f12.fl = ctx->f14.fl;
    after_17:
    // 0x801DBE4C: b           L_801DBE60
    // 0x801DBE50: mov.s       $f2, $f0
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 0);
    ctx->f2.fl = ctx->f0.fl;
        goto L_801DBE60;
    // 0x801DBE50: mov.s       $f2, $f0
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 0);
    ctx->f2.fl = ctx->f0.fl;
L_801DBE54:
    // 0x801DBE54: jal         0x800C7010
    // 0x801DBE58: neg.s       $f12, $f14
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f14.fl); 
    ctx->f12.fl = -ctx->f14.fl;
    _nsqrtf(rdram, ctx);
        goto after_18;
    // 0x801DBE58: neg.s       $f12, $f14
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f14.fl); 
    ctx->f12.fl = -ctx->f14.fl;
    after_18:
    // 0x801DBE5C: neg.s       $f2, $f0
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f0.fl); 
    ctx->f2.fl = -ctx->f0.fl;
L_801DBE60:
    // 0x801DBE60: div.s       $f8, $f2, $f24
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 24);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f24.fl); 
    ctx->f8.fl = DIV_S(ctx->f2.fl, ctx->f24.fl);
    // 0x801DBE64: lwc1        $f10, 0x0($s2)
    ctx->f10.u32l = MEM_W(ctx->r18, 0X0);
    // 0x801DBE68: lui         $t6, 0x8023
    ctx->r14 = S32(0X8023 << 16);
    // 0x801DBE6C: addiu       $t6, $t6, -0x7EC0
    ctx->r14 = ADD32(ctx->r14, -0X7EC0);
    // 0x801DBE70: addiu       $s2, $s2, 0x8
    ctx->r18 = ADD32(ctx->r18, 0X8);
    // 0x801DBE74: addiu       $s5, $s5, 0x4
    ctx->r21 = ADD32(ctx->r21, 0X4);
    // 0x801DBE78: addiu       $s1, $s1, 0x34
    ctx->r17 = ADD32(ctx->r17, 0X34);
    // 0x801DBE7C: add.s       $f4, $f10, $f8
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f4.fl = ctx->f10.fl + ctx->f8.fl;
    // 0x801DBE80: bne         $s2, $t6, L_801DBCE4
    if (ctx->r18 != ctx->r14) {
        // 0x801DBE84: swc1        $f4, -0x8($s2)
        MEM_W(-0X8, ctx->r18) = ctx->f4.u32l;
            goto L_801DBCE4;
    }
    // 0x801DBE84: swc1        $f4, -0x8($s2)
    MEM_W(-0X8, ctx->r18) = ctx->f4.u32l;
    // 0x801DBE88: b           L_801DBEAC
    // 0x801DBE8C: lw          $t7, 0xD8($sp)
    ctx->r15 = MEM_W(ctx->r29, 0XD8);
        goto L_801DBEAC;
    // 0x801DBE8C: lw          $t7, 0xD8($sp)
    ctx->r15 = MEM_W(ctx->r29, 0XD8);
L_801DBE90:
    // 0x801DBE90: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801DBE94: sw          $zero, -0x7E70($at)
    MEM_W(-0X7E70, ctx->r1) = 0;
    // 0x801DBE98: sw          $zero, 0x68($s1)
    MEM_W(0X68, ctx->r17) = 0;
    // 0x801DBE9C: sw          $zero, 0x34($s1)
    MEM_W(0X34, ctx->r17) = 0;
    // 0x801DBEA0: sw          $zero, 0x0($s1)
    MEM_W(0X0, ctx->r17) = 0;
    // 0x801DBEA4: addiu       $s1, $s1, 0x68
    ctx->r17 = ADD32(ctx->r17, 0X68);
    // 0x801DBEA8: lw          $t7, 0xD8($sp)
    ctx->r15 = MEM_W(ctx->r29, 0XD8);
L_801DBEAC:
    // 0x801DBEAC: lui         $s1, 0x8023
    ctx->r17 = S32(0X8023 << 16);
    // 0x801DBEB0: addiu       $s1, $s1, -0x7D6C
    ctx->r17 = ADD32(ctx->r17, -0X7D6C);
    // 0x801DBEB4: lw          $v0, 0x8($t7)
    ctx->r2 = MEM_W(ctx->r15, 0X8);
    // 0x801DBEB8: slti        $at, $v0, 0x320
    ctx->r1 = SIGNED(ctx->r2) < 0X320 ? 1 : 0;
    // 0x801DBEBC: bne         $at, $zero, L_801DBF08
    if (ctx->r1 != 0) {
        // 0x801DBEC0: addiu       $at, $zero, 0x320
        ctx->r1 = ADD32(0, 0X320);
            goto L_801DBF08;
    }
    // 0x801DBEC0: addiu       $at, $zero, 0x320
    ctx->r1 = ADD32(0, 0X320);
    // 0x801DBEC4: bne         $v0, $at, L_801DBEE4
    if (ctx->r2 != ctx->r1) {
        // 0x801DBEC8: lui         $a0, 0x8023
        ctx->r4 = S32(0X8023 << 16);
            goto L_801DBEE4;
    }
    // 0x801DBEC8: lui         $a0, 0x8023
    ctx->r4 = S32(0X8023 << 16);
    // 0x801DBECC: lui         $a2, 0x8023
    ctx->r6 = S32(0X8023 << 16);
    // 0x801DBED0: addiu       $a2, $a2, -0x7EC0
    ctx->r6 = ADD32(ctx->r6, -0X7EC0);
    // 0x801DBED4: addiu       $a0, $a0, -0x7DA0
    ctx->r4 = ADD32(ctx->r4, -0X7DA0);
    // 0x801DBED8: addiu       $a1, $sp, 0x7C
    ctx->r5 = ADD32(ctx->r29, 0X7C);
    // 0x801DBEDC: jal         0x801DB284
    // 0x801DBEE0: addiu       $a3, $zero, 0x7
    ctx->r7 = ADD32(0, 0X7);
    func_801DB284(rdram, ctx);
        goto after_19;
    // 0x801DBEE0: addiu       $a3, $zero, 0x7
    ctx->r7 = ADD32(0, 0X7);
    after_19:
L_801DBEE4:
    // 0x801DBEE4: lui         $a0, 0x8023
    ctx->r4 = S32(0X8023 << 16);
    // 0x801DBEE8: lui         $a2, 0x8023
    ctx->r6 = S32(0X8023 << 16);
    // 0x801DBEEC: addiu       $a2, $a2, -0x7EC0
    ctx->r6 = ADD32(ctx->r6, -0X7EC0);
    // 0x801DBEF0: addiu       $a0, $a0, -0x7DA0
    ctx->r4 = ADD32(ctx->r4, -0X7DA0);
    // 0x801DBEF4: addiu       $a1, $sp, 0x7C
    ctx->r5 = ADD32(ctx->r29, 0X7C);
    // 0x801DBEF8: jal         0x801DB430
    // 0x801DBEFC: addiu       $a3, $zero, 0x7
    ctx->r7 = ADD32(0, 0X7);
    func_801DB430(rdram, ctx);
        goto after_20;
    // 0x801DBEFC: addiu       $a3, $zero, 0x7
    ctx->r7 = ADD32(0, 0X7);
    after_20:
    // 0x801DBF00: b           L_801DBF30
    // 0x801DBF04: lw          $ra, 0x5C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X5C);
        goto L_801DBF30;
    // 0x801DBF04: lw          $ra, 0x5C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X5C);
L_801DBF08:
    // 0x801DBF08: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801DBF0C: sw          $zero, -0x7DA0($at)
    MEM_W(-0X7DA0, ctx->r1) = 0;
    // 0x801DBF10: sw          $zero, 0x104($s1)
    MEM_W(0X104, ctx->r17) = 0;
    // 0x801DBF14: sw          $zero, 0xD0($s1)
    MEM_W(0XD0, ctx->r17) = 0;
    // 0x801DBF18: sw          $zero, 0x9C($s1)
    MEM_W(0X9C, ctx->r17) = 0;
    // 0x801DBF1C: sw          $zero, 0x34($s1)
    MEM_W(0X34, ctx->r17) = 0;
    // 0x801DBF20: sw          $zero, 0x0($s1)
    MEM_W(0X0, ctx->r17) = 0;
    // 0x801DBF24: addiu       $s1, $s1, 0x104
    ctx->r17 = ADD32(ctx->r17, 0X104);
    // 0x801DBF28: sw          $zero, -0x9C($s1)
    MEM_W(-0X9C, ctx->r17) = 0;
    // 0x801DBF2C: lw          $ra, 0x5C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X5C);
L_801DBF30:
    // 0x801DBF30: ldc1        $f20, 0x18($sp)
    CHECK_FR(ctx, 20);
    ctx->f20.u64 = LD(ctx->r29, 0X18);
    // 0x801DBF34: ldc1        $f22, 0x20($sp)
    CHECK_FR(ctx, 22);
    ctx->f22.u64 = LD(ctx->r29, 0X20);
    // 0x801DBF38: ldc1        $f24, 0x28($sp)
    CHECK_FR(ctx, 24);
    ctx->f24.u64 = LD(ctx->r29, 0X28);
    // 0x801DBF3C: ldc1        $f26, 0x30($sp)
    CHECK_FR(ctx, 26);
    ctx->f26.u64 = LD(ctx->r29, 0X30);
    // 0x801DBF40: ldc1        $f28, 0x38($sp)
    CHECK_FR(ctx, 28);
    ctx->f28.u64 = LD(ctx->r29, 0X38);
    // 0x801DBF44: lw          $s0, 0x40($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X40);
    // 0x801DBF48: lw          $s1, 0x44($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X44);
    // 0x801DBF4C: lw          $s2, 0x48($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X48);
    // 0x801DBF50: lw          $s3, 0x4C($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X4C);
    // 0x801DBF54: lw          $s4, 0x50($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X50);
    // 0x801DBF58: lw          $s5, 0x54($sp)
    ctx->r21 = MEM_W(ctx->r29, 0X54);
    // 0x801DBF5C: lw          $s6, 0x58($sp)
    ctx->r22 = MEM_W(ctx->r29, 0X58);
    // 0x801DBF60: jr          $ra
    // 0x801DBF64: addiu       $sp, $sp, 0xD8
    ctx->r29 = ADD32(ctx->r29, 0XD8);
    return;
    // 0x801DBF64: addiu       $sp, $sp, 0xD8
    ctx->r29 = ADD32(ctx->r29, 0XD8);
;}
RECOMP_FUNC void func_801DBF68(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801DBF68: addiu       $sp, $sp, -0xF0
    ctx->r29 = ADD32(ctx->r29, -0XF0);
    // 0x801DBF6C: lui         $t7, 0x8022
    ctx->r15 = S32(0X8022 << 16);
    // 0x801DBF70: sw          $s5, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r21;
    // 0x801DBF74: addiu       $t7, $t7, 0x5CF4
    ctx->r15 = ADD32(ctx->r15, 0X5CF4);
    // 0x801DBF78: or          $s5, $a0, $zero
    ctx->r21 = ctx->r4 | 0;
    // 0x801DBF7C: sw          $ra, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r31;
    // 0x801DBF80: sw          $s7, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r23;
    // 0x801DBF84: sw          $s6, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r22;
    // 0x801DBF88: sw          $s4, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r20;
    // 0x801DBF8C: sw          $s3, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r19;
    // 0x801DBF90: sw          $s2, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r18;
    // 0x801DBF94: sw          $s1, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r17;
    // 0x801DBF98: sw          $s0, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r16;
    // 0x801DBF9C: addiu       $t0, $t7, 0x9C
    ctx->r8 = ADD32(ctx->r15, 0X9C);
    // 0x801DBFA0: addiu       $t6, $sp, 0x4C
    ctx->r14 = ADD32(ctx->r29, 0X4C);
L_801DBFA4:
    // 0x801DBFA4: lw          $at, 0x0($t7)
    ctx->r1 = MEM_W(ctx->r15, 0X0);
    // 0x801DBFA8: addiu       $t7, $t7, 0xC
    ctx->r15 = ADD32(ctx->r15, 0XC);
    // 0x801DBFAC: addiu       $t6, $t6, 0xC
    ctx->r14 = ADD32(ctx->r14, 0XC);
    // 0x801DBFB0: sw          $at, -0xC($t6)
    MEM_W(-0XC, ctx->r14) = ctx->r1;
    // 0x801DBFB4: lw          $at, -0x8($t7)
    ctx->r1 = MEM_W(ctx->r15, -0X8);
    // 0x801DBFB8: sw          $at, -0x8($t6)
    MEM_W(-0X8, ctx->r14) = ctx->r1;
    // 0x801DBFBC: lw          $at, -0x4($t7)
    ctx->r1 = MEM_W(ctx->r15, -0X4);
    // 0x801DBFC0: bne         $t7, $t0, L_801DBFA4
    if (ctx->r15 != ctx->r8) {
        // 0x801DBFC4: sw          $at, -0x4($t6)
        MEM_W(-0X4, ctx->r14) = ctx->r1;
            goto L_801DBFA4;
    }
    // 0x801DBFC4: sw          $at, -0x4($t6)
    MEM_W(-0X4, ctx->r14) = ctx->r1;
    // 0x801DBFC8: lw          $at, 0x0($t7)
    ctx->r1 = MEM_W(ctx->r15, 0X0);
    // 0x801DBFCC: sw          $at, 0x0($t6)
    MEM_W(0X0, ctx->r14) = ctx->r1;
    // 0x801DBFD0: lw          $t1, 0x8($s5)
    ctx->r9 = MEM_W(ctx->r21, 0X8);
    // 0x801DBFD4: bne         $t1, $zero, L_801DBFE4
    if (ctx->r9 != 0) {
        // 0x801DBFD8: nop
    
            goto L_801DBFE4;
    }
    // 0x801DBFD8: nop

    // 0x801DBFDC: jal         0x800AB92C
    // 0x801DBFE0: nop

    func_800AB92C(rdram, ctx);
        goto after_0;
    // 0x801DBFE0: nop

    after_0:
L_801DBFE4:
    // 0x801DBFE4: lui         $a0, 0x8023
    ctx->r4 = S32(0X8023 << 16);
    // 0x801DBFE8: lw          $a0, -0x7854($a0)
    ctx->r4 = MEM_W(ctx->r4, -0X7854);
    // 0x801DBFEC: or          $s2, $zero, $zero
    ctx->r18 = 0 | 0;
    // 0x801DBFF0: addiu       $s0, $sp, 0x4C
    ctx->r16 = ADD32(ctx->r29, 0X4C);
    // 0x801DBFF4: blez        $a0, L_801DC080
    if (SIGNED(ctx->r4) <= 0) {
        // 0x801DBFF8: addiu       $s7, $zero, 0x1
        ctx->r23 = ADD32(0, 0X1);
            goto L_801DC080;
    }
    // 0x801DBFF8: addiu       $s7, $zero, 0x1
    ctx->r23 = ADD32(0, 0X1);
    // 0x801DBFFC: lui         $s6, 0x8023
    ctx->r22 = S32(0X8023 << 16);
    // 0x801DC000: lui         $s4, 0x8023
    ctx->r20 = S32(0X8023 << 16);
    // 0x801DC004: lui         $s3, 0x8023
    ctx->r19 = S32(0X8023 << 16);
    // 0x801DC008: addiu       $s3, $s3, -0x7E70
    ctx->r19 = ADD32(ctx->r19, -0X7E70);
    // 0x801DC00C: addiu       $s4, $s4, -0x7EF0
    ctx->r20 = ADD32(ctx->r20, -0X7EF0);
    // 0x801DC010: addiu       $s6, $s6, -0x7858
    ctx->r22 = ADD32(ctx->r22, -0X7858);
L_801DC014:
    // 0x801DC014: lw          $v0, 0x8($s5)
    ctx->r2 = MEM_W(ctx->r21, 0X8);
    // 0x801DC018: lw          $v1, 0x0($s0)
    ctx->r3 = MEM_W(ctx->r16, 0X0);
    // 0x801DC01C: slt         $at, $v0, $v1
    ctx->r1 = SIGNED(ctx->r2) < SIGNED(ctx->r3) ? 1 : 0;
    // 0x801DC020: bnel        $at, $zero, L_801DC074
    if (ctx->r1 != 0) {
        // 0x801DC024: addiu       $s2, $s2, 0x1
        ctx->r18 = ADD32(ctx->r18, 0X1);
            goto L_801DC074;
    }
    goto skip_0;
    // 0x801DC024: addiu       $s2, $s2, 0x1
    ctx->r18 = ADD32(ctx->r18, 0X1);
    skip_0:
    // 0x801DC028: lw          $t2, 0x4($s0)
    ctx->r10 = MEM_W(ctx->r16, 0X4);
    // 0x801DC02C: slt         $at, $v0, $t2
    ctx->r1 = SIGNED(ctx->r2) < SIGNED(ctx->r10) ? 1 : 0;
    // 0x801DC030: beql        $at, $zero, L_801DC074
    if (ctx->r1 == 0) {
        // 0x801DC034: addiu       $s2, $s2, 0x1
        ctx->r18 = ADD32(ctx->r18, 0X1);
            goto L_801DC074;
    }
    goto skip_1;
    // 0x801DC034: addiu       $s2, $s2, 0x1
    ctx->r18 = ADD32(ctx->r18, 0X1);
    skip_1:
    // 0x801DC038: sw          $s7, 0x0($s6)
    MEM_W(0X0, ctx->r22) = ctx->r23;
    // 0x801DC03C: lw          $t3, 0x8($s5)
    ctx->r11 = MEM_W(ctx->r21, 0X8);
    // 0x801DC040: addiu       $s1, $s0, 0x8
    ctx->r17 = ADD32(ctx->r16, 0X8);
    // 0x801DC044: or          $a1, $s1, $zero
    ctx->r5 = ctx->r17 | 0;
    // 0x801DC048: bne         $t3, $v1, L_801DC058
    if (ctx->r11 != ctx->r3) {
        // 0x801DC04C: or          $a0, $s3, $zero
        ctx->r4 = ctx->r19 | 0;
            goto L_801DC058;
    }
    // 0x801DC04C: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
    // 0x801DC050: jal         0x801DB0E4
    // 0x801DC054: or          $a2, $s4, $zero
    ctx->r6 = ctx->r20 | 0;
    func_801DB0E4(rdram, ctx);
        goto after_1;
    // 0x801DC054: or          $a2, $s4, $zero
    ctx->r6 = ctx->r20 | 0;
    after_1:
L_801DC058:
    // 0x801DC058: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
    // 0x801DC05C: or          $a1, $s1, $zero
    ctx->r5 = ctx->r17 | 0;
    // 0x801DC060: jal         0x801DB1DC
    // 0x801DC064: or          $a2, $s4, $zero
    ctx->r6 = ctx->r20 | 0;
    func_801DB1DC(rdram, ctx);
        goto after_2;
    // 0x801DC064: or          $a2, $s4, $zero
    ctx->r6 = ctx->r20 | 0;
    after_2:
    // 0x801DC068: lui         $a0, 0x8023
    ctx->r4 = S32(0X8023 << 16);
    // 0x801DC06C: lw          $a0, -0x7854($a0)
    ctx->r4 = MEM_W(ctx->r4, -0X7854);
    // 0x801DC070: addiu       $s2, $s2, 0x1
    ctx->r18 = ADD32(ctx->r18, 0X1);
L_801DC074:
    // 0x801DC074: slt         $at, $s2, $a0
    ctx->r1 = SIGNED(ctx->r18) < SIGNED(ctx->r4) ? 1 : 0;
    // 0x801DC078: bne         $at, $zero, L_801DC014
    if (ctx->r1 != 0) {
        // 0x801DC07C: addiu       $s0, $s0, 0x28
        ctx->r16 = ADD32(ctx->r16, 0X28);
            goto L_801DC014;
    }
    // 0x801DC07C: addiu       $s0, $s0, 0x28
    ctx->r16 = ADD32(ctx->r16, 0X28);
L_801DC080:
    // 0x801DC080: lw          $ra, 0x34($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X34);
    // 0x801DC084: lw          $s0, 0x14($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X14);
    // 0x801DC088: lw          $s1, 0x18($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X18);
    // 0x801DC08C: lw          $s2, 0x1C($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X1C);
    // 0x801DC090: lw          $s3, 0x20($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X20);
    // 0x801DC094: lw          $s4, 0x24($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X24);
    // 0x801DC098: lw          $s5, 0x28($sp)
    ctx->r21 = MEM_W(ctx->r29, 0X28);
    // 0x801DC09C: lw          $s6, 0x2C($sp)
    ctx->r22 = MEM_W(ctx->r29, 0X2C);
    // 0x801DC0A0: lw          $s7, 0x30($sp)
    ctx->r23 = MEM_W(ctx->r29, 0X30);
    // 0x801DC0A4: jr          $ra
    // 0x801DC0A8: addiu       $sp, $sp, 0xF0
    ctx->r29 = ADD32(ctx->r29, 0XF0);
    return;
    // 0x801DC0A8: addiu       $sp, $sp, 0xF0
    ctx->r29 = ADD32(ctx->r29, 0XF0);
;}
RECOMP_FUNC void func_801DC0AC(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801DC0AC: addiu       $sp, $sp, -0xE8
    ctx->r29 = ADD32(ctx->r29, -0XE8);
    // 0x801DC0B0: lui         $t7, 0x8022
    ctx->r15 = S32(0X8022 << 16);
    // 0x801DC0B4: sw          $s5, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r21;
    // 0x801DC0B8: addiu       $t7, $t7, 0x5D94
    ctx->r15 = ADD32(ctx->r15, 0X5D94);
    // 0x801DC0BC: or          $s5, $a0, $zero
    ctx->r21 = ctx->r4 | 0;
    // 0x801DC0C0: sw          $ra, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r31;
    // 0x801DC0C4: sw          $s6, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r22;
    // 0x801DC0C8: sw          $s4, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r20;
    // 0x801DC0CC: sw          $s3, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r19;
    // 0x801DC0D0: sw          $s2, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r18;
    // 0x801DC0D4: sw          $s1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r17;
    // 0x801DC0D8: sw          $s0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r16;
    // 0x801DC0DC: addiu       $t0, $t7, 0x78
    ctx->r8 = ADD32(ctx->r15, 0X78);
    // 0x801DC0E0: addiu       $t6, $sp, 0x6C
    ctx->r14 = ADD32(ctx->r29, 0X6C);
L_801DC0E4:
    // 0x801DC0E4: lw          $at, 0x0($t7)
    ctx->r1 = MEM_W(ctx->r15, 0X0);
    // 0x801DC0E8: addiu       $t7, $t7, 0xC
    ctx->r15 = ADD32(ctx->r15, 0XC);
    // 0x801DC0EC: addiu       $t6, $t6, 0xC
    ctx->r14 = ADD32(ctx->r14, 0XC);
    // 0x801DC0F0: sw          $at, -0xC($t6)
    MEM_W(-0XC, ctx->r14) = ctx->r1;
    // 0x801DC0F4: lw          $at, -0x8($t7)
    ctx->r1 = MEM_W(ctx->r15, -0X8);
    // 0x801DC0F8: sw          $at, -0x8($t6)
    MEM_W(-0X8, ctx->r14) = ctx->r1;
    // 0x801DC0FC: lw          $at, -0x4($t7)
    ctx->r1 = MEM_W(ctx->r15, -0X4);
    // 0x801DC100: bne         $t7, $t0, L_801DC0E4
    if (ctx->r15 != ctx->r8) {
        // 0x801DC104: sw          $at, -0x4($t6)
        MEM_W(-0X4, ctx->r14) = ctx->r1;
            goto L_801DC0E4;
    }
    // 0x801DC104: sw          $at, -0x4($t6)
    MEM_W(-0X4, ctx->r14) = ctx->r1;
    // 0x801DC108: lui         $t2, 0x8022
    ctx->r10 = S32(0X8022 << 16);
    // 0x801DC10C: addiu       $t2, $t2, 0x5E0C
    ctx->r10 = ADD32(ctx->r10, 0X5E0C);
    // 0x801DC110: addiu       $t5, $t2, 0x24
    ctx->r13 = ADD32(ctx->r10, 0X24);
    // 0x801DC114: addiu       $t1, $sp, 0x44
    ctx->r9 = ADD32(ctx->r29, 0X44);
L_801DC118:
    // 0x801DC118: lw          $at, 0x0($t2)
    ctx->r1 = MEM_W(ctx->r10, 0X0);
    // 0x801DC11C: addiu       $t2, $t2, 0xC
    ctx->r10 = ADD32(ctx->r10, 0XC);
    // 0x801DC120: addiu       $t1, $t1, 0xC
    ctx->r9 = ADD32(ctx->r9, 0XC);
    // 0x801DC124: sw          $at, -0xC($t1)
    MEM_W(-0XC, ctx->r9) = ctx->r1;
    // 0x801DC128: lw          $at, -0x8($t2)
    ctx->r1 = MEM_W(ctx->r10, -0X8);
    // 0x801DC12C: sw          $at, -0x8($t1)
    MEM_W(-0X8, ctx->r9) = ctx->r1;
    // 0x801DC130: lw          $at, -0x4($t2)
    ctx->r1 = MEM_W(ctx->r10, -0X4);
    // 0x801DC134: bne         $t2, $t5, L_801DC118
    if (ctx->r10 != ctx->r13) {
        // 0x801DC138: sw          $at, -0x4($t1)
        MEM_W(-0X4, ctx->r9) = ctx->r1;
            goto L_801DC118;
    }
    // 0x801DC138: sw          $at, -0x4($t1)
    MEM_W(-0X4, ctx->r9) = ctx->r1;
    // 0x801DC13C: lw          $at, 0x0($t2)
    ctx->r1 = MEM_W(ctx->r10, 0X0);
    // 0x801DC140: sw          $at, 0x0($t1)
    MEM_W(0X0, ctx->r9) = ctx->r1;
    // 0x801DC144: lw          $v1, 0x8($s5)
    ctx->r3 = MEM_W(ctx->r21, 0X8);
    // 0x801DC148: bne         $v1, $zero, L_801DC15C
    if (ctx->r3 != 0) {
        // 0x801DC14C: nop
    
            goto L_801DC15C;
    }
    // 0x801DC14C: nop

    // 0x801DC150: jal         0x800AB92C
    // 0x801DC154: nop

    func_800AB92C(rdram, ctx);
        goto after_0;
    // 0x801DC154: nop

    after_0:
    // 0x801DC158: lw          $v1, 0x8($s5)
    ctx->r3 = MEM_W(ctx->r21, 0X8);
L_801DC15C:
    // 0x801DC15C: lui         $s4, 0x8023
    ctx->r20 = S32(0X8023 << 16);
    // 0x801DC160: lui         $s3, 0x8023
    ctx->r19 = S32(0X8023 << 16);
    // 0x801DC164: lui         $s2, 0x8023
    ctx->r18 = S32(0X8023 << 16);
    // 0x801DC168: addiu       $s2, $s2, -0x7E70
    ctx->r18 = ADD32(ctx->r18, -0X7E70);
    // 0x801DC16C: addiu       $s3, $s3, -0x7EF0
    ctx->r19 = ADD32(ctx->r19, -0X7EF0);
    // 0x801DC170: addiu       $s4, $s4, -0x7858
    ctx->r20 = ADD32(ctx->r20, -0X7858);
    // 0x801DC174: addiu       $s0, $sp, 0x6C
    ctx->r16 = ADD32(ctx->r29, 0X6C);
    // 0x801DC178: addiu       $s6, $sp, 0xE4
    ctx->r22 = ADD32(ctx->r29, 0XE4);
    // 0x801DC17C: lw          $v0, 0x0($s0)
    ctx->r2 = MEM_W(ctx->r16, 0X0);
L_801DC180:
    // 0x801DC180: slt         $at, $v1, $v0
    ctx->r1 = SIGNED(ctx->r3) < SIGNED(ctx->r2) ? 1 : 0;
    // 0x801DC184: bnel        $at, $zero, L_801DC1E0
    if (ctx->r1 != 0) {
        // 0x801DC188: addiu       $s0, $s0, 0x28
        ctx->r16 = ADD32(ctx->r16, 0X28);
            goto L_801DC1E0;
    }
    goto skip_0;
    // 0x801DC188: addiu       $s0, $s0, 0x28
    ctx->r16 = ADD32(ctx->r16, 0X28);
    skip_0:
    // 0x801DC18C: lw          $t9, 0x4($s0)
    ctx->r25 = MEM_W(ctx->r16, 0X4);
    // 0x801DC190: slt         $at, $v1, $t9
    ctx->r1 = SIGNED(ctx->r3) < SIGNED(ctx->r25) ? 1 : 0;
    // 0x801DC194: beql        $at, $zero, L_801DC1E0
    if (ctx->r1 == 0) {
        // 0x801DC198: addiu       $s0, $s0, 0x28
        ctx->r16 = ADD32(ctx->r16, 0X28);
            goto L_801DC1E0;
    }
    goto skip_1;
    // 0x801DC198: addiu       $s0, $s0, 0x28
    ctx->r16 = ADD32(ctx->r16, 0X28);
    skip_1:
    // 0x801DC19C: lw          $t8, 0x0($s4)
    ctx->r24 = MEM_W(ctx->r20, 0X0);
    // 0x801DC1A0: addiu       $s1, $s0, 0x8
    ctx->r17 = ADD32(ctx->r16, 0X8);
    // 0x801DC1A4: or          $a1, $s1, $zero
    ctx->r5 = ctx->r17 | 0;
    // 0x801DC1A8: addiu       $t0, $t8, 0x1
    ctx->r8 = ADD32(ctx->r24, 0X1);
    // 0x801DC1AC: sw          $t0, 0x0($s4)
    MEM_W(0X0, ctx->r20) = ctx->r8;
    // 0x801DC1B0: lw          $t7, 0x8($s5)
    ctx->r15 = MEM_W(ctx->r21, 0X8);
    // 0x801DC1B4: or          $a0, $s2, $zero
    ctx->r4 = ctx->r18 | 0;
    // 0x801DC1B8: bnel        $t7, $v0, L_801DC1CC
    if (ctx->r15 != ctx->r2) {
        // 0x801DC1BC: or          $a0, $s2, $zero
        ctx->r4 = ctx->r18 | 0;
            goto L_801DC1CC;
    }
    goto skip_2;
    // 0x801DC1BC: or          $a0, $s2, $zero
    ctx->r4 = ctx->r18 | 0;
    skip_2:
    // 0x801DC1C0: jal         0x801DB0E4
    // 0x801DC1C4: or          $a2, $s3, $zero
    ctx->r6 = ctx->r19 | 0;
    func_801DB0E4(rdram, ctx);
        goto after_1;
    // 0x801DC1C4: or          $a2, $s3, $zero
    ctx->r6 = ctx->r19 | 0;
    after_1:
    // 0x801DC1C8: or          $a0, $s2, $zero
    ctx->r4 = ctx->r18 | 0;
L_801DC1CC:
    // 0x801DC1CC: or          $a1, $s1, $zero
    ctx->r5 = ctx->r17 | 0;
    // 0x801DC1D0: jal         0x801DB1DC
    // 0x801DC1D4: or          $a2, $s3, $zero
    ctx->r6 = ctx->r19 | 0;
    func_801DB1DC(rdram, ctx);
        goto after_2;
    // 0x801DC1D4: or          $a2, $s3, $zero
    ctx->r6 = ctx->r19 | 0;
    after_2:
    // 0x801DC1D8: lw          $v1, 0x8($s5)
    ctx->r3 = MEM_W(ctx->r21, 0X8);
    // 0x801DC1DC: addiu       $s0, $s0, 0x28
    ctx->r16 = ADD32(ctx->r16, 0X28);
L_801DC1E0:
    // 0x801DC1E0: bnel        $s0, $s6, L_801DC180
    if (ctx->r16 != ctx->r22) {
        // 0x801DC1E4: lw          $v0, 0x0($s0)
        ctx->r2 = MEM_W(ctx->r16, 0X0);
            goto L_801DC180;
    }
    goto skip_3;
    // 0x801DC1E4: lw          $v0, 0x0($s0)
    ctx->r2 = MEM_W(ctx->r16, 0X0);
    skip_3:
    // 0x801DC1E8: lw          $t6, 0x44($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X44);
    // 0x801DC1EC: lw          $t4, 0x48($sp)
    ctx->r12 = MEM_W(ctx->r29, 0X48);
    // 0x801DC1F0: slt         $at, $v1, $t6
    ctx->r1 = SIGNED(ctx->r3) < SIGNED(ctx->r14) ? 1 : 0;
    // 0x801DC1F4: bne         $at, $zero, L_801DC24C
    if (ctx->r1 != 0) {
        // 0x801DC1F8: slt         $at, $v1, $t4
        ctx->r1 = SIGNED(ctx->r3) < SIGNED(ctx->r12) ? 1 : 0;
            goto L_801DC24C;
    }
    // 0x801DC1F8: slt         $at, $v1, $t4
    ctx->r1 = SIGNED(ctx->r3) < SIGNED(ctx->r12) ? 1 : 0;
    // 0x801DC1FC: beql        $at, $zero, L_801DC250
    if (ctx->r1 == 0) {
        // 0x801DC200: lw          $ra, 0x34($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X34);
            goto L_801DC250;
    }
    goto skip_4;
    // 0x801DC200: lw          $ra, 0x34($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X34);
    skip_4:
    // 0x801DC204: lw          $t3, 0x0($s4)
    ctx->r11 = MEM_W(ctx->r20, 0X0);
    // 0x801DC208: lw          $t2, 0x44($sp)
    ctx->r10 = MEM_W(ctx->r29, 0X44);
    // 0x801DC20C: lui         $a0, 0x8023
    ctx->r4 = S32(0X8023 << 16);
    // 0x801DC210: addiu       $t5, $t3, 0x1
    ctx->r13 = ADD32(ctx->r11, 0X1);
    // 0x801DC214: sw          $t5, 0x0($s4)
    MEM_W(0X0, ctx->r20) = ctx->r13;
    // 0x801DC218: lw          $t1, 0x8($s5)
    ctx->r9 = MEM_W(ctx->r21, 0X8);
    // 0x801DC21C: addiu       $a0, $a0, -0x7E3C
    ctx->r4 = ADD32(ctx->r4, -0X7E3C);
    // 0x801DC220: addiu       $a1, $sp, 0x4C
    ctx->r5 = ADD32(ctx->r29, 0X4C);
    // 0x801DC224: bne         $t2, $t1, L_801DC234
    if (ctx->r10 != ctx->r9) {
        // 0x801DC228: lui         $a2, 0x8023
        ctx->r6 = S32(0X8023 << 16);
            goto L_801DC234;
    }
    // 0x801DC228: lui         $a2, 0x8023
    ctx->r6 = S32(0X8023 << 16);
    // 0x801DC22C: jal         0x801DB0E4
    // 0x801DC230: addiu       $a2, $a2, -0x7EEC
    ctx->r6 = ADD32(ctx->r6, -0X7EEC);
    func_801DB0E4(rdram, ctx);
        goto after_3;
    // 0x801DC230: addiu       $a2, $a2, -0x7EEC
    ctx->r6 = ADD32(ctx->r6, -0X7EEC);
    after_3:
L_801DC234:
    // 0x801DC234: lui         $a0, 0x8023
    ctx->r4 = S32(0X8023 << 16);
    // 0x801DC238: lui         $a2, 0x8023
    ctx->r6 = S32(0X8023 << 16);
    // 0x801DC23C: addiu       $a2, $a2, -0x7EEC
    ctx->r6 = ADD32(ctx->r6, -0X7EEC);
    // 0x801DC240: addiu       $a0, $a0, -0x7E3C
    ctx->r4 = ADD32(ctx->r4, -0X7E3C);
    // 0x801DC244: jal         0x801DB1DC
    // 0x801DC248: addiu       $a1, $sp, 0x4C
    ctx->r5 = ADD32(ctx->r29, 0X4C);
    func_801DB1DC(rdram, ctx);
        goto after_4;
    // 0x801DC248: addiu       $a1, $sp, 0x4C
    ctx->r5 = ADD32(ctx->r29, 0X4C);
    after_4:
L_801DC24C:
    // 0x801DC24C: lw          $ra, 0x34($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X34);
L_801DC250:
    // 0x801DC250: lw          $s0, 0x18($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X18);
    // 0x801DC254: lw          $s1, 0x1C($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X1C);
    // 0x801DC258: lw          $s2, 0x20($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X20);
    // 0x801DC25C: lw          $s3, 0x24($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X24);
    // 0x801DC260: lw          $s4, 0x28($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X28);
    // 0x801DC264: lw          $s5, 0x2C($sp)
    ctx->r21 = MEM_W(ctx->r29, 0X2C);
    // 0x801DC268: lw          $s6, 0x30($sp)
    ctx->r22 = MEM_W(ctx->r29, 0X30);
    // 0x801DC26C: jr          $ra
    // 0x801DC270: addiu       $sp, $sp, 0xE8
    ctx->r29 = ADD32(ctx->r29, 0XE8);
    return;
    // 0x801DC270: addiu       $sp, $sp, 0xE8
    ctx->r29 = ADD32(ctx->r29, 0XE8);
;}
RECOMP_FUNC void func_801DC274(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801DC274: addiu       $sp, $sp, -0x38
    ctx->r29 = ADD32(ctx->r29, -0X38);
    // 0x801DC278: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x801DC27C: lw          $t6, 0x4($a0)
    ctx->r14 = MEM_W(ctx->r4, 0X4);
    // 0x801DC280: lui         $t7, 0x8022
    ctx->r15 = S32(0X8022 << 16);
    // 0x801DC284: addiu       $t7, $t7, 0x3A30
    ctx->r15 = ADD32(ctx->r15, 0X3A30);
    // 0x801DC288: addiu       $at, $zero, 0xC
    ctx->r1 = ADD32(0, 0XC);
    // 0x801DC28C: subu        $a1, $t6, $t7
    ctx->r5 = SUB32(ctx->r14, ctx->r15);
    // 0x801DC290: div         $zero, $a1, $at
    lo = S32(S64(S32(ctx->r5)) / S64(S32(ctx->r1))); hi = S32(S64(S32(ctx->r5)) % S64(S32(ctx->r1)));
    // 0x801DC294: mflo        $t8
    ctx->r24 = lo;
    // 0x801DC298: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x801DC29C: bne         $t8, $at, L_801DC3F4
    if (ctx->r24 != ctx->r1) {
        // 0x801DC2A0: addiu       $v0, $zero, 0x1
        ctx->r2 = ADD32(0, 0X1);
            goto L_801DC3F4;
    }
    // 0x801DC2A0: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
    // 0x801DC2A4: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801DC2A8: sw          $v0, -0x7858($at)
    MEM_W(-0X7858, ctx->r1) = ctx->r2;
    // 0x801DC2AC: lw          $t9, 0x8($a0)
    ctx->r25 = MEM_W(ctx->r4, 0X8);
    // 0x801DC2B0: bne         $v0, $t9, L_801DC334
    if (ctx->r2 != ctx->r25) {
        // 0x801DC2B4: nop
    
            goto L_801DC334;
    }
    // 0x801DC2B4: nop

    // 0x801DC2B8: jal         0x800AB92C
    // 0x801DC2BC: nop

    func_800AB92C(rdram, ctx);
        goto after_0;
    // 0x801DC2BC: nop

    after_0:
    // 0x801DC2C0: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801DC2C4: addiu       $t0, $zero, 0x6
    ctx->r8 = ADD32(0, 0X6);
    // 0x801DC2C8: addiu       $t1, $zero, 0x2
    ctx->r9 = ADD32(0, 0X2);
    // 0x801DC2CC: sw          $t0, -0x7E70($at)
    MEM_W(-0X7E70, ctx->r1) = ctx->r8;
    // 0x801DC2D0: sw          $t1, -0x7E6C($at)
    MEM_W(-0X7E6C, ctx->r1) = ctx->r9;
    // 0x801DC2D4: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801DC2D8: sw          $zero, -0x7E68($at)
    MEM_W(-0X7E68, ctx->r1) = 0;
    // 0x801DC2DC: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801DC2E0: lwc1        $f4, 0x5F2C($at)
    ctx->f4.u32l = MEM_W(ctx->r1, 0X5F2C);
    // 0x801DC2E4: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801DC2E8: mtc1        $zero, $f16
    ctx->f16.u32l = 0;
    // 0x801DC2EC: swc1        $f4, -0x7E40($at)
    MEM_W(-0X7E40, ctx->r1) = ctx->f4.u32l;
    // 0x801DC2F0: lui         $at, 0xC396
    ctx->r1 = S32(0XC396 << 16);
    // 0x801DC2F4: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x801DC2F8: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801DC2FC: swc1        $f6, -0x7E64($at)
    MEM_W(-0X7E64, ctx->r1) = ctx->f6.u32l;
    // 0x801DC300: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801DC304: swc1        $f16, -0x7E60($at)
    MEM_W(-0X7E60, ctx->r1) = ctx->f16.u32l;
    // 0x801DC308: lui         $at, 0xC407
    ctx->r1 = S32(0XC407 << 16);
    // 0x801DC30C: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x801DC310: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801DC314: swc1        $f8, -0x7E5C($at)
    MEM_W(-0X7E5C, ctx->r1) = ctx->f8.u32l;
    // 0x801DC318: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801DC31C: swc1        $f16, -0x7E4C($at)
    MEM_W(-0X7E4C, ctx->r1) = ctx->f16.u32l;
    // 0x801DC320: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x801DC324: mtc1        $at, $f10
    ctx->f10.u32l = ctx->r1;
    // 0x801DC328: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801DC32C: swc1        $f16, -0x7E44($at)
    MEM_W(-0X7E44, ctx->r1) = ctx->f16.u32l;
    // 0x801DC330: swc1        $f10, -0x7E48($at)
    MEM_W(-0X7E48, ctx->r1) = ctx->f10.u32l;
L_801DC334:
    // 0x801DC334: lui         $t2, 0x8023
    ctx->r10 = S32(0X8023 << 16);
    // 0x801DC338: lw          $t2, -0x7E68($t2)
    ctx->r10 = MEM_W(ctx->r10, -0X7E68);
    // 0x801DC33C: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801DC340: mtc1        $zero, $f2
    ctx->f2.u32l = 0;
    // 0x801DC344: addiu       $t3, $t2, 0x1
    ctx->r11 = ADD32(ctx->r10, 0X1);
    // 0x801DC348: sw          $t3, -0x7E68($at)
    MEM_W(-0X7E68, ctx->r1) = ctx->r11;
    // 0x801DC34C: lui         $at, 0xC040
    ctx->r1 = S32(0XC040 << 16);
    // 0x801DC350: mtc1        $at, $f0
    ctx->f0.u32l = ctx->r1;
    // 0x801DC354: lui         $at, 0xC0A0
    ctx->r1 = S32(0XC0A0 << 16);
    // 0x801DC358: mtc1        $at, $f14
    ctx->f14.u32l = ctx->r1;
    // 0x801DC35C: mul.s       $f18, $f0, $f0
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f18.fl = MUL_S(ctx->f0.fl, ctx->f0.fl);
    // 0x801DC360: swc1        $f2, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->f2.u32l;
    // 0x801DC364: swc1        $f0, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->f0.u32l;
    // 0x801DC368: mul.s       $f4, $f2, $f2
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f4.fl = MUL_S(ctx->f2.fl, ctx->f2.fl);
    // 0x801DC36C: swc1        $f14, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->f14.u32l;
    // 0x801DC370: mul.s       $f8, $f14, $f14
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f8.fl = MUL_S(ctx->f14.fl, ctx->f14.fl);
    // 0x801DC374: add.s       $f6, $f18, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = ctx->f18.fl + ctx->f4.fl;
    // 0x801DC378: jal         0x800C7010
    // 0x801DC37C: add.s       $f12, $f8, $f6
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f12.fl = ctx->f8.fl + ctx->f6.fl;
    _nsqrtf(rdram, ctx);
        goto after_1;
    // 0x801DC37C: add.s       $f12, $f8, $f6
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f12.fl = ctx->f8.fl + ctx->f6.fl;
    after_1:
    // 0x801DC380: lui         $at, 0x4100
    ctx->r1 = S32(0X4100 << 16);
    // 0x801DC384: lui         $v0, 0x8023
    ctx->r2 = S32(0X8023 << 16);
    // 0x801DC388: lui         $a0, 0x8023
    ctx->r4 = S32(0X8023 << 16);
    // 0x801DC38C: mtc1        $at, $f2
    ctx->f2.u32l = ctx->r1;
    // 0x801DC390: addiu       $a0, $a0, -0x7E64
    ctx->r4 = ADD32(ctx->r4, -0X7E64);
    // 0x801DC394: addiu       $v0, $v0, -0x7E70
    ctx->r2 = ADD32(ctx->r2, -0X7E70);
    // 0x801DC398: addiu       $v1, $sp, 0x28
    ctx->r3 = ADD32(ctx->r29, 0X28);
    // 0x801DC39C: lwc1        $f12, 0x0($v1)
    ctx->f12.u32l = MEM_W(ctx->r3, 0X0);
    // 0x801DC3A0: addiu       $v0, $v0, 0x4
    ctx->r2 = ADD32(ctx->r2, 0X4);
    // 0x801DC3A4: beq         $v0, $a0, L_801DC3D8
    if (ctx->r2 == ctx->r4) {
        // 0x801DC3A8: div.s       $f18, $f12, $f0
        CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f18.fl = DIV_S(ctx->f12.fl, ctx->f0.fl);
            goto L_801DC3D8;
    }
    // 0x801DC3A8: div.s       $f18, $f12, $f0
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f18.fl = DIV_S(ctx->f12.fl, ctx->f0.fl);
L_801DC3AC:
    // 0x801DC3AC: lwc1        $f16, 0x8($v0)
    ctx->f16.u32l = MEM_W(ctx->r2, 0X8);
    // 0x801DC3B0: swc1        $f18, 0x14($v0)
    MEM_W(0X14, ctx->r2) = ctx->f18.u32l;
    // 0x801DC3B4: lwc1        $f14, 0x14($v0)
    ctx->f14.u32l = MEM_W(ctx->r2, 0X14);
    // 0x801DC3B8: lwc1        $f12, 0x4($v1)
    ctx->f12.u32l = MEM_W(ctx->r3, 0X4);
    // 0x801DC3BC: addiu       $v0, $v0, 0x4
    ctx->r2 = ADD32(ctx->r2, 0X4);
    // 0x801DC3C0: mul.s       $f14, $f14, $f2
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f14.fl = MUL_S(ctx->f14.fl, ctx->f2.fl);
    // 0x801DC3C4: div.s       $f18, $f12, $f0
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f18.fl = DIV_S(ctx->f12.fl, ctx->f0.fl);
    // 0x801DC3C8: addiu       $v1, $v1, 0x4
    ctx->r3 = ADD32(ctx->r3, 0X4);
    // 0x801DC3CC: add.s       $f14, $f16, $f14
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f14.fl = ctx->f16.fl + ctx->f14.fl;
    // 0x801DC3D0: bne         $v0, $a0, L_801DC3AC
    if (ctx->r2 != ctx->r4) {
        // 0x801DC3D4: swc1        $f14, 0x4($v0)
        MEM_W(0X4, ctx->r2) = ctx->f14.u32l;
            goto L_801DC3AC;
    }
    // 0x801DC3D4: swc1        $f14, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->f14.u32l;
L_801DC3D8:
    // 0x801DC3D8: swc1        $f18, 0x14($v0)
    MEM_W(0X14, ctx->r2) = ctx->f18.u32l;
    // 0x801DC3DC: lwc1        $f14, 0x14($v0)
    ctx->f14.u32l = MEM_W(ctx->r2, 0X14);
    // 0x801DC3E0: lwc1        $f16, 0x8($v0)
    ctx->f16.u32l = MEM_W(ctx->r2, 0X8);
    // 0x801DC3E4: addiu       $v1, $v1, 0x4
    ctx->r3 = ADD32(ctx->r3, 0X4);
    // 0x801DC3E8: mul.s       $f14, $f14, $f2
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f14.fl = MUL_S(ctx->f14.fl, ctx->f2.fl);
    // 0x801DC3EC: add.s       $f14, $f16, $f14
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f14.fl = ctx->f16.fl + ctx->f14.fl;
    // 0x801DC3F0: swc1        $f14, 0x8($v0)
    MEM_W(0X8, ctx->r2) = ctx->f14.u32l;
L_801DC3F4:
    // 0x801DC3F4: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x801DC3F8: addiu       $sp, $sp, 0x38
    ctx->r29 = ADD32(ctx->r29, 0X38);
    // 0x801DC3FC: jr          $ra
    // 0x801DC400: nop

    return;
    // 0x801DC400: nop

;}
RECOMP_FUNC void func_801DC404(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801DC404: addiu       $sp, $sp, -0x90
    ctx->r29 = ADD32(ctx->r29, -0X90);
    // 0x801DC408: lui         $t6, 0x8022
    ctx->r14 = S32(0X8022 << 16);
    // 0x801DC40C: addiu       $v1, $sp, 0x54
    ctx->r3 = ADD32(ctx->r29, 0X54);
    // 0x801DC410: addiu       $t6, $t6, 0x5E34
    ctx->r14 = ADD32(ctx->r14, 0X5E34);
    // 0x801DC414: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x801DC418: sw          $a0, 0x90($sp)
    MEM_W(0X90, ctx->r29) = ctx->r4;
    // 0x801DC41C: addiu       $t9, $t6, 0x30
    ctx->r25 = ADD32(ctx->r14, 0X30);
    // 0x801DC420: or          $t0, $v1, $zero
    ctx->r8 = ctx->r3 | 0;
L_801DC424:
    // 0x801DC424: lw          $at, 0x0($t6)
    ctx->r1 = MEM_W(ctx->r14, 0X0);
    // 0x801DC428: addiu       $t6, $t6, 0xC
    ctx->r14 = ADD32(ctx->r14, 0XC);
    // 0x801DC42C: addiu       $t0, $t0, 0xC
    ctx->r8 = ADD32(ctx->r8, 0XC);
    // 0x801DC430: sw          $at, -0xC($t0)
    MEM_W(-0XC, ctx->r8) = ctx->r1;
    // 0x801DC434: lw          $at, -0x8($t6)
    ctx->r1 = MEM_W(ctx->r14, -0X8);
    // 0x801DC438: sw          $at, -0x8($t0)
    MEM_W(-0X8, ctx->r8) = ctx->r1;
    // 0x801DC43C: lw          $at, -0x4($t6)
    ctx->r1 = MEM_W(ctx->r14, -0X4);
    // 0x801DC440: bne         $t6, $t9, L_801DC424
    if (ctx->r14 != ctx->r25) {
        // 0x801DC444: sw          $at, -0x4($t0)
        MEM_W(-0X4, ctx->r8) = ctx->r1;
            goto L_801DC424;
    }
    // 0x801DC444: sw          $at, -0x4($t0)
    MEM_W(-0X4, ctx->r8) = ctx->r1;
    // 0x801DC448: lw          $at, 0x0($t6)
    ctx->r1 = MEM_W(ctx->r14, 0X0);
    // 0x801DC44C: addiu       $t1, $sp, 0x20
    ctx->r9 = ADD32(ctx->r29, 0X20);
    // 0x801DC450: or          $t5, $v1, $zero
    ctx->r13 = ctx->r3 | 0;
    // 0x801DC454: addiu       $t4, $v1, 0x30
    ctx->r12 = ADD32(ctx->r3, 0X30);
    // 0x801DC458: sw          $at, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r1;
L_801DC45C:
    // 0x801DC45C: lw          $at, 0x0($t5)
    ctx->r1 = MEM_W(ctx->r13, 0X0);
    // 0x801DC460: addiu       $t5, $t5, 0xC
    ctx->r13 = ADD32(ctx->r13, 0XC);
    // 0x801DC464: addiu       $t1, $t1, 0xC
    ctx->r9 = ADD32(ctx->r9, 0XC);
    // 0x801DC468: sw          $at, -0xC($t1)
    MEM_W(-0XC, ctx->r9) = ctx->r1;
    // 0x801DC46C: lw          $at, -0x8($t5)
    ctx->r1 = MEM_W(ctx->r13, -0X8);
    // 0x801DC470: sw          $at, -0x8($t1)
    MEM_W(-0X8, ctx->r9) = ctx->r1;
    // 0x801DC474: lw          $at, -0x4($t5)
    ctx->r1 = MEM_W(ctx->r13, -0X4);
    // 0x801DC478: bne         $t5, $t4, L_801DC45C
    if (ctx->r13 != ctx->r12) {
        // 0x801DC47C: sw          $at, -0x4($t1)
        MEM_W(-0X4, ctx->r9) = ctx->r1;
            goto L_801DC45C;
    }
    // 0x801DC47C: sw          $at, -0x4($t1)
    MEM_W(-0X4, ctx->r9) = ctx->r1;
    // 0x801DC480: lw          $at, 0x0($t5)
    ctx->r1 = MEM_W(ctx->r13, 0X0);
    // 0x801DC484: lui         $t9, 0x8022
    ctx->r25 = S32(0X8022 << 16);
    // 0x801DC488: addiu       $t9, $t9, 0x4B14
    ctx->r25 = ADD32(ctx->r25, 0X4B14);
    // 0x801DC48C: sw          $at, 0x0($t1)
    MEM_W(0X0, ctx->r9) = ctx->r1;
    // 0x801DC490: lw          $t8, 0x90($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X90);
    // 0x801DC494: addiu       $at, $zero, 0xC
    ctx->r1 = ADD32(0, 0XC);
    // 0x801DC498: addiu       $t0, $zero, 0x8
    ctx->r8 = ADD32(0, 0X8);
    // 0x801DC49C: lw          $t7, 0x4($t8)
    ctx->r15 = MEM_W(ctx->r24, 0X4);
    // 0x801DC4A0: subu        $v0, $t7, $t9
    ctx->r2 = SUB32(ctx->r15, ctx->r25);
    // 0x801DC4A4: div         $zero, $v0, $at
    lo = S32(S64(S32(ctx->r2)) / S64(S32(ctx->r1))); hi = S32(S64(S32(ctx->r2)) % S64(S32(ctx->r1)));
    // 0x801DC4A8: mflo        $t6
    ctx->r14 = lo;
    // 0x801DC4AC: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x801DC4B0: bnel        $t6, $at, L_801DC59C
    if (ctx->r14 != ctx->r1) {
        // 0x801DC4B4: lw          $ra, 0x14($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X14);
            goto L_801DC59C;
    }
    goto skip_0;
    // 0x801DC4B4: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    skip_0:
    // 0x801DC4B8: lw          $t3, 0x90($sp)
    ctx->r11 = MEM_W(ctx->r29, 0X90);
    // 0x801DC4BC: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801DC4C0: sw          $t0, -0x7858($at)
    MEM_W(-0X7858, ctx->r1) = ctx->r8;
    // 0x801DC4C4: lw          $v0, 0x8($t3)
    ctx->r2 = MEM_W(ctx->r11, 0X8);
    // 0x801DC4C8: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x801DC4CC: bnel        $v0, $at, L_801DC504
    if (ctx->r2 != ctx->r1) {
        // 0x801DC4D0: lw          $t4, 0x90($sp)
        ctx->r12 = MEM_W(ctx->r29, 0X90);
            goto L_801DC504;
    }
    goto skip_1;
    // 0x801DC4D0: lw          $t4, 0x90($sp)
    ctx->r12 = MEM_W(ctx->r29, 0X90);
    skip_1:
    // 0x801DC4D4: jal         0x800AB92C
    // 0x801DC4D8: nop

    func_800AB92C(rdram, ctx);
        goto after_0;
    // 0x801DC4D8: nop

    after_0:
    // 0x801DC4DC: lui         $a0, 0x8023
    ctx->r4 = S32(0X8023 << 16);
    // 0x801DC4E0: lui         $a2, 0x8023
    ctx->r6 = S32(0X8023 << 16);
    // 0x801DC4E4: addiu       $a2, $a2, -0x7EE0
    ctx->r6 = ADD32(ctx->r6, -0X7EE0);
    // 0x801DC4E8: addiu       $a0, $a0, -0x7E70
    ctx->r4 = ADD32(ctx->r4, -0X7E70);
    // 0x801DC4EC: addiu       $a1, $sp, 0x20
    ctx->r5 = ADD32(ctx->r29, 0X20);
    // 0x801DC4F0: jal         0x801DB284
    // 0x801DC4F4: addiu       $a3, $zero, 0x8
    ctx->r7 = ADD32(0, 0X8);
    func_801DB284(rdram, ctx);
        goto after_1;
    // 0x801DC4F4: addiu       $a3, $zero, 0x8
    ctx->r7 = ADD32(0, 0X8);
    after_1:
    // 0x801DC4F8: lw          $t2, 0x90($sp)
    ctx->r10 = MEM_W(ctx->r29, 0X90);
    // 0x801DC4FC: lw          $v0, 0x8($t2)
    ctx->r2 = MEM_W(ctx->r10, 0X8);
    // 0x801DC500: lw          $t4, 0x90($sp)
    ctx->r12 = MEM_W(ctx->r29, 0X90);
L_801DC504:
    // 0x801DC504: lwc1        $f6, 0x20($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X20);
    // 0x801DC508: lui         $a0, 0x8023
    ctx->r4 = S32(0X8023 << 16);
    // 0x801DC50C: lw          $t5, 0x4($t4)
    ctx->r13 = MEM_W(ctx->r12, 0X4);
    // 0x801DC510: lui         $a2, 0x8023
    ctx->r6 = S32(0X8023 << 16);
    // 0x801DC514: addiu       $a2, $a2, -0x7EE0
    ctx->r6 = ADD32(ctx->r6, -0X7EE0);
    // 0x801DC518: lw          $t1, 0x0($t5)
    ctx->r9 = MEM_W(ctx->r13, 0X0);
    // 0x801DC51C: addiu       $a0, $a0, -0x7E70
    ctx->r4 = ADD32(ctx->r4, -0X7E70);
    // 0x801DC520: addiu       $a1, $sp, 0x20
    ctx->r5 = ADD32(ctx->r29, 0X20);
    // 0x801DC524: div         $zero, $v0, $t1
    lo = S32(S64(S32(ctx->r2)) / S64(S32(ctx->r9))); hi = S32(S64(S32(ctx->r2)) % S64(S32(ctx->r9)));
    // 0x801DC528: mflo        $t8
    ctx->r24 = lo;
    // 0x801DC52C: mtc1        $t8, $f4
    ctx->f4.u32l = ctx->r24;
    // 0x801DC530: bne         $t1, $zero, L_801DC53C
    if (ctx->r9 != 0) {
        // 0x801DC534: nop
    
            goto L_801DC53C;
    }
    // 0x801DC534: nop

    // 0x801DC538: break       7
    do_break(2149434680);
L_801DC53C:
    // 0x801DC53C: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x801DC540: bne         $t1, $at, L_801DC554
    if (ctx->r9 != ctx->r1) {
        // 0x801DC544: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_801DC554;
    }
    // 0x801DC544: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x801DC548: bne         $v0, $at, L_801DC554
    if (ctx->r2 != ctx->r1) {
        // 0x801DC54C: nop
    
            goto L_801DC554;
    }
    // 0x801DC54C: nop

    // 0x801DC550: break       6
    do_break(2149434704);
L_801DC554:
    // 0x801DC554: cvt.s.w     $f0, $f4
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 4);
    ctx->f0.fl = CVT_S_W(ctx->f4.u32l);
    // 0x801DC558: lui         $at, 0x4396
    ctx->r1 = S32(0X4396 << 16);
    // 0x801DC55C: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x801DC560: lui         $at, 0xC348
    ctx->r1 = S32(0XC348 << 16);
    // 0x801DC564: mtc1        $at, $f18
    ctx->f18.u32l = ctx->r1;
    // 0x801DC568: lwc1        $f4, 0x24($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X24);
    // 0x801DC56C: mul.s       $f10, $f8, $f0
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f10.fl = MUL_S(ctx->f8.fl, ctx->f0.fl);
    // 0x801DC570: addiu       $a3, $zero, 0x8
    ctx->r7 = ADD32(0, 0X8);
    // 0x801DC574: mul.s       $f2, $f18, $f0
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f2.fl = MUL_S(ctx->f18.fl, ctx->f0.fl);
    // 0x801DC578: add.s       $f16, $f6, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f16.fl = ctx->f6.fl + ctx->f10.fl;
    // 0x801DC57C: lwc1        $f6, 0x28($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X28);
    // 0x801DC580: add.s       $f8, $f4, $f2
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f8.fl = ctx->f4.fl + ctx->f2.fl;
    // 0x801DC584: swc1        $f16, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->f16.u32l;
    // 0x801DC588: add.s       $f10, $f6, $f2
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f10.fl = ctx->f6.fl + ctx->f2.fl;
    // 0x801DC58C: swc1        $f8, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->f8.u32l;
    // 0x801DC590: jal         0x801DB430
    // 0x801DC594: swc1        $f10, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->f10.u32l;
    func_801DB430(rdram, ctx);
        goto after_2;
    // 0x801DC594: swc1        $f10, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->f10.u32l;
    after_2:
    // 0x801DC598: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_801DC59C:
    // 0x801DC59C: addiu       $sp, $sp, 0x90
    ctx->r29 = ADD32(ctx->r29, 0X90);
    // 0x801DC5A0: jr          $ra
    // 0x801DC5A4: nop

    return;
    // 0x801DC5A4: nop

;}
RECOMP_FUNC void func_801DC5A8(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801DC5A8: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x801DC5AC: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x801DC5B0: lw          $t6, 0x4($a0)
    ctx->r14 = MEM_W(ctx->r4, 0X4);
    // 0x801DC5B4: lui         $t7, 0x8022
    ctx->r15 = S32(0X8022 << 16);
    // 0x801DC5B8: addiu       $t7, $t7, 0x3F7C
    ctx->r15 = ADD32(ctx->r15, 0X3F7C);
    // 0x801DC5BC: addiu       $at, $zero, 0xC
    ctx->r1 = ADD32(0, 0XC);
    // 0x801DC5C0: subu        $v0, $t6, $t7
    ctx->r2 = SUB32(ctx->r14, ctx->r15);
    // 0x801DC5C4: div         $zero, $v0, $at
    lo = S32(S64(S32(ctx->r2)) / S64(S32(ctx->r1))); hi = S32(S64(S32(ctx->r2)) % S64(S32(ctx->r1)));
    // 0x801DC5C8: mflo        $t8
    ctx->r24 = lo;
    // 0x801DC5CC: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x801DC5D0: bnel        $t8, $at, L_801DC600
    if (ctx->r24 != ctx->r1) {
        // 0x801DC5D4: lw          $ra, 0x14($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X14);
            goto L_801DC600;
    }
    goto skip_0;
    // 0x801DC5D4: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    skip_0:
    // 0x801DC5D8: lw          $t9, 0x8($a0)
    ctx->r25 = MEM_W(ctx->r4, 0X8);
    // 0x801DC5DC: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x801DC5E0: bnel        $t9, $at, L_801DC600
    if (ctx->r25 != ctx->r1) {
        // 0x801DC5E4: lw          $ra, 0x14($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X14);
            goto L_801DC600;
    }
    goto skip_1;
    // 0x801DC5E4: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    skip_1:
    // 0x801DC5E8: jal         0x800AB92C
    // 0x801DC5EC: nop

    func_800AB92C(rdram, ctx);
        goto after_0;
    // 0x801DC5EC: nop

    after_0:
    // 0x801DC5F0: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    // 0x801DC5F4: jal         0x800AB95C
    // 0x801DC5F8: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800AB95C(rdram, ctx);
        goto after_1;
    // 0x801DC5F8: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_1:
    // 0x801DC5FC: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_801DC600:
    // 0x801DC600: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x801DC604: jr          $ra
    // 0x801DC608: nop

    return;
    // 0x801DC608: nop

;}
RECOMP_FUNC void func_801DC60C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801DC60C: addiu       $sp, $sp, -0xB0
    ctx->r29 = ADD32(ctx->r29, -0XB0);
    // 0x801DC610: sw          $ra, 0x6C($sp)
    MEM_W(0X6C, ctx->r29) = ctx->r31;
    // 0x801DC614: sw          $fp, 0x68($sp)
    MEM_W(0X68, ctx->r29) = ctx->r30;
    // 0x801DC618: sw          $s7, 0x64($sp)
    MEM_W(0X64, ctx->r29) = ctx->r23;
    // 0x801DC61C: sw          $s6, 0x60($sp)
    MEM_W(0X60, ctx->r29) = ctx->r22;
    // 0x801DC620: sw          $s5, 0x5C($sp)
    MEM_W(0X5C, ctx->r29) = ctx->r21;
    // 0x801DC624: sw          $s4, 0x58($sp)
    MEM_W(0X58, ctx->r29) = ctx->r20;
    // 0x801DC628: sw          $s3, 0x54($sp)
    MEM_W(0X54, ctx->r29) = ctx->r19;
    // 0x801DC62C: sw          $s2, 0x50($sp)
    MEM_W(0X50, ctx->r29) = ctx->r18;
    // 0x801DC630: sw          $s1, 0x4C($sp)
    MEM_W(0X4C, ctx->r29) = ctx->r17;
    // 0x801DC634: sw          $s0, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r16;
    // 0x801DC638: sdc1        $f30, 0x40($sp)
    CHECK_FR(ctx, 30);
    SD(ctx->f30.u64, 0X40, ctx->r29);
    // 0x801DC63C: sdc1        $f28, 0x38($sp)
    CHECK_FR(ctx, 28);
    SD(ctx->f28.u64, 0X38, ctx->r29);
    // 0x801DC640: sdc1        $f26, 0x30($sp)
    CHECK_FR(ctx, 26);
    SD(ctx->f26.u64, 0X30, ctx->r29);
    // 0x801DC644: sdc1        $f24, 0x28($sp)
    CHECK_FR(ctx, 24);
    SD(ctx->f24.u64, 0X28, ctx->r29);
    // 0x801DC648: sdc1        $f22, 0x20($sp)
    CHECK_FR(ctx, 22);
    SD(ctx->f22.u64, 0X20, ctx->r29);
    // 0x801DC64C: sdc1        $f20, 0x18($sp)
    CHECK_FR(ctx, 20);
    SD(ctx->f20.u64, 0X18, ctx->r29);
    // 0x801DC650: lw          $v1, 0x4($a0)
    ctx->r3 = MEM_W(ctx->r4, 0X4);
    // 0x801DC654: lui         $t8, 0x8022
    ctx->r24 = S32(0X8022 << 16);
    // 0x801DC658: addiu       $t8, $t8, 0x41E0
    ctx->r24 = ADD32(ctx->r24, 0X41E0);
    // 0x801DC65C: addiu       $at, $zero, 0xC
    ctx->r1 = ADD32(0, 0XC);
    // 0x801DC660: subu        $s4, $v1, $t8
    ctx->r20 = SUB32(ctx->r3, ctx->r24);
    // 0x801DC664: div         $zero, $s4, $at
    lo = S32(S64(S32(ctx->r20)) / S64(S32(ctx->r1))); hi = S32(S64(S32(ctx->r20)) % S64(S32(ctx->r1)));
    // 0x801DC668: lw          $t6, 0x0($a0)
    ctx->r14 = MEM_W(ctx->r4, 0X0);
    // 0x801DC66C: mflo        $t9
    ctx->r25 = lo;
    // 0x801DC670: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x801DC674: addiu       $t7, $t6, 0x5C
    ctx->r15 = ADD32(ctx->r14, 0X5C);
    // 0x801DC678: bne         $t9, $at, L_801DCCEC
    if (ctx->r25 != ctx->r1) {
        // 0x801DC67C: sw          $t7, 0xA8($sp)
        MEM_W(0XA8, ctx->r29) = ctx->r15;
            goto L_801DCCEC;
    }
    // 0x801DC67C: sw          $t7, 0xA8($sp)
    MEM_W(0XA8, ctx->r29) = ctx->r15;
    // 0x801DC680: addiu       $t0, $zero, 0x18
    ctx->r8 = ADD32(0, 0X18);
    // 0x801DC684: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801DC688: sw          $t0, -0x7858($at)
    MEM_W(-0X7858, ctx->r1) = ctx->r8;
    // 0x801DC68C: lw          $v0, 0x8($a0)
    ctx->r2 = MEM_W(ctx->r4, 0X8);
    // 0x801DC690: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x801DC694: bne         $v0, $at, L_801DC944
    if (ctx->r2 != ctx->r1) {
        // 0x801DC698: addiu       $s4, $v0, -0x1E
        ctx->r20 = ADD32(ctx->r2, -0X1E);
            goto L_801DC944;
    }
    // 0x801DC698: addiu       $s4, $v0, -0x1E
    ctx->r20 = ADD32(ctx->r2, -0X1E);
    // 0x801DC69C: jal         0x800AB92C
    // 0x801DC6A0: nop

    func_800AB92C(rdram, ctx);
        goto after_0;
    // 0x801DC6A0: nop

    after_0:
    // 0x801DC6A4: lui         $at, 0x4188
    ctx->r1 = S32(0X4188 << 16);
    // 0x801DC6A8: mtc1        $at, $f30
    ctx->f30.u32l = ctx->r1;
    // 0x801DC6AC: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801DC6B0: lwc1        $f28, 0x5F30($at)
    ctx->f28.u32l = MEM_W(ctx->r1, 0X5F30);
    // 0x801DC6B4: lui         $fp, 0x8023
    ctx->r30 = S32(0X8023 << 16);
    // 0x801DC6B8: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x801DC6BC: addiu       $fp, $fp, -0x7E70
    ctx->r30 = ADD32(ctx->r30, -0X7E70);
    // 0x801DC6C0: lui         $s2, 0x8023
    ctx->r18 = S32(0X8023 << 16);
    // 0x801DC6C4: lui         $s7, 0x8015
    ctx->r23 = S32(0X8015 << 16);
    // 0x801DC6C8: mtc1        $at, $f26
    ctx->f26.u32l = ctx->r1;
    // 0x801DC6CC: mtc1        $zero, $f24
    ctx->f24.u32l = 0;
    // 0x801DC6D0: addiu       $s7, $s7, 0x4350
    ctx->r23 = ADD32(ctx->r23, 0X4350);
    // 0x801DC6D4: addiu       $s2, $s2, -0x7EE0
    ctx->r18 = ADD32(ctx->r18, -0X7EE0);
    // 0x801DC6D8: or          $s1, $fp, $zero
    ctx->r17 = ctx->r30 | 0;
    // 0x801DC6DC: or          $s4, $zero, $zero
    ctx->r20 = 0 | 0;
    // 0x801DC6E0: addiu       $s6, $zero, 0x7
    ctx->r22 = ADD32(0, 0X7);
    // 0x801DC6E4: addiu       $s5, $zero, 0xA
    ctx->r21 = ADD32(0, 0XA);
L_801DC6E8:
    // 0x801DC6E8: addiu       $t1, $zero, 0x1
    ctx->r9 = ADD32(0, 0X1);
    // 0x801DC6EC: sw          $t1, 0x0($s1)
    MEM_W(0X0, ctx->r17) = ctx->r9;
    // 0x801DC6F0: jal         0x80047E50
    // 0x801DC6F4: sw          $zero, 0x4($s1)
    MEM_W(0X4, ctx->r17) = 0;
    SysUtils_Rand(rdram, ctx);
        goto after_1;
    // 0x801DC6F4: sw          $zero, 0x4($s1)
    MEM_W(0X4, ctx->r17) = 0;
    after_1:
    // 0x801DC6F8: divu        $zero, $v0, $s5
    lo = S32(U32(ctx->r2) / U32(ctx->r21)); hi = S32(U32(ctx->r2) % U32(ctx->r21));
    // 0x801DC6FC: mfhi        $t2
    ctx->r10 = hi;
    // 0x801DC700: sw          $t2, 0x8($s1)
    MEM_W(0X8, ctx->r17) = ctx->r10;
    // 0x801DC704: bne         $s5, $zero, L_801DC710
    if (ctx->r21 != 0) {
        // 0x801DC708: nop
    
            goto L_801DC710;
    }
    // 0x801DC708: nop

    // 0x801DC70C: break       7
    do_break(2149435148);
L_801DC710:
    // 0x801DC710: jal         0x80047E50
    // 0x801DC714: nop

    SysUtils_Rand(rdram, ctx);
        goto after_2;
    // 0x801DC714: nop

    after_2:
    // 0x801DC718: divu        $zero, $v0, $s6
    lo = S32(U32(ctx->r2) / U32(ctx->r22)); hi = S32(U32(ctx->r2) % U32(ctx->r22));
    // 0x801DC71C: mtc1        $s4, $f4
    ctx->f4.u32l = ctx->r20;
    // 0x801DC720: lui         $at, 0x41F0
    ctx->r1 = S32(0X41F0 << 16);
    // 0x801DC724: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x801DC728: cvt.s.w     $f20, $f4
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 4);
    ctx->f20.fl = CVT_S_W(ctx->f4.u32l);
    // 0x801DC72C: lw          $t3, 0xA8($sp)
    ctx->r11 = MEM_W(ctx->r29, 0XA8);
    // 0x801DC730: mfhi        $t4
    ctx->r12 = hi;
    // 0x801DC734: mtc1        $t4, $f4
    ctx->f4.u32l = ctx->r12;
    // 0x801DC738: lwc1        $f6, 0x0($t3)
    ctx->f6.u32l = MEM_W(ctx->r11, 0X0);
    // 0x801DC73C: lui         $at, 0x4F80
    ctx->r1 = S32(0X4F80 << 16);
    // 0x801DC740: mul.s       $f10, $f20, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = MUL_S(ctx->f20.fl, ctx->f8.fl);
    // 0x801DC744: cvt.s.w     $f8, $f4
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    ctx->f8.fl = CVT_S_W(ctx->f4.u32l);
    // 0x801DC748: sub.s       $f18, $f6, $f10
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f18.fl = ctx->f6.fl - ctx->f10.fl;
    // 0x801DC74C: bne         $s6, $zero, L_801DC758
    if (ctx->r22 != 0) {
        // 0x801DC750: nop
    
            goto L_801DC758;
    }
    // 0x801DC750: nop

    // 0x801DC754: break       7
    do_break(2149435220);
L_801DC758:
    // 0x801DC758: bgezl       $t4, L_801DC770
    if (SIGNED(ctx->r12) >= 0) {
        // 0x801DC75C: sub.s       $f10, $f18, $f8
        CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = ctx->f18.fl - ctx->f8.fl;
            goto L_801DC770;
    }
    goto skip_0;
    // 0x801DC75C: sub.s       $f10, $f18, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = ctx->f18.fl - ctx->f8.fl;
    skip_0:
    // 0x801DC760: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x801DC764: nop

    // 0x801DC768: add.s       $f8, $f8, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = ctx->f8.fl + ctx->f6.fl;
    // 0x801DC76C: sub.s       $f10, $f18, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = ctx->f18.fl - ctx->f8.fl;
L_801DC770:
    // 0x801DC770: lui         $at, 0x4396
    ctx->r1 = S32(0X4396 << 16);
    // 0x801DC774: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x801DC778: nop

    // 0x801DC77C: sub.s       $f6, $f10, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = ctx->f10.fl - ctx->f4.fl;
    // 0x801DC780: jal         0x80047E50
    // 0x801DC784: swc1        $f6, 0xC($s1)
    MEM_W(0XC, ctx->r17) = ctx->f6.u32l;
    SysUtils_Rand(rdram, ctx);
        goto after_3;
    // 0x801DC784: swc1        $f6, 0xC($s1)
    MEM_W(0XC, ctx->r17) = ctx->f6.u32l;
    after_3:
    // 0x801DC788: jal         0x80047E50
    // 0x801DC78C: or          $s3, $v0, $zero
    ctx->r19 = ctx->r2 | 0;
    SysUtils_Rand(rdram, ctx);
        goto after_4;
    // 0x801DC78C: or          $s3, $v0, $zero
    ctx->r19 = ctx->r2 | 0;
    after_4:
    // 0x801DC790: lui         $at, 0x41C0
    ctx->r1 = S32(0X41C0 << 16);
    // 0x801DC794: mtc1        $at, $f18
    ctx->f18.u32l = ctx->r1;
    // 0x801DC798: lui         $at, 0x4334
    ctx->r1 = S32(0X4334 << 16);
    // 0x801DC79C: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x801DC7A0: div.s       $f22, $f20, $f18
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f22.fl = DIV_S(ctx->f20.fl, ctx->f18.fl);
    // 0x801DC7A4: lui         $at, 0x4580
    ctx->r1 = S32(0X4580 << 16);
    // 0x801DC7A8: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x801DC7AC: lui         $at, 0x43B4
    ctx->r1 = S32(0X43B4 << 16);
    // 0x801DC7B0: mtc1        $at, $f18
    ctx->f18.u32l = ctx->r1;
    // 0x801DC7B4: andi        $t9, $v0, 0x3F
    ctx->r25 = ctx->r2 & 0X3F;
    // 0x801DC7B8: lui         $at, 0x4F80
    ctx->r1 = S32(0X4F80 << 16);
    // 0x801DC7BC: andi        $t1, $s3, 0x1F
    ctx->r9 = ctx->r19 & 0X1F;
    // 0x801DC7C0: mul.s       $f10, $f22, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = MUL_S(ctx->f22.fl, ctx->f8.fl);
    // 0x801DC7C4: nop

    // 0x801DC7C8: mul.s       $f6, $f10, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = MUL_S(ctx->f10.fl, ctx->f4.fl);
    // 0x801DC7CC: mtc1        $t9, $f4
    ctx->f4.u32l = ctx->r25;
    // 0x801DC7D0: div.s       $f8, $f6, $f18
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f8.fl = DIV_S(ctx->f6.fl, ctx->f18.fl);
    // 0x801DC7D4: cvt.s.w     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
    // 0x801DC7D8: trunc.w.s   $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.u32l = TRUNC_W_S(ctx->f8.fl);
    // 0x801DC7DC: mfc1        $t6, $f10
    ctx->r14 = (int32_t)ctx->f10.u32l;
    // 0x801DC7E0: nop

    // 0x801DC7E4: andi        $t7, $t6, 0xFFF
    ctx->r15 = ctx->r14 & 0XFFF;
    // 0x801DC7E8: sll         $t8, $t7, 2
    ctx->r24 = S32(ctx->r15 << 2);
    // 0x801DC7EC: bgez        $t9, L_801DC800
    if (SIGNED(ctx->r25) >= 0) {
        // 0x801DC7F0: addu        $s0, $s7, $t8
        ctx->r16 = ADD32(ctx->r23, ctx->r24);
            goto L_801DC800;
    }
    // 0x801DC7F0: addu        $s0, $s7, $t8
    ctx->r16 = ADD32(ctx->r23, ctx->r24);
    // 0x801DC7F4: mtc1        $at, $f18
    ctx->f18.u32l = ctx->r1;
    // 0x801DC7F8: nop

    // 0x801DC7FC: add.s       $f6, $f6, $f18
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f6.fl = ctx->f6.fl + ctx->f18.fl;
L_801DC800:
    // 0x801DC800: multu       $s4, $t1
    result = U64(U32(ctx->r20)) * U64(U32(ctx->r9)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x801DC804: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801DC808: lwc1        $f8, 0x5F34($at)
    ctx->f8.u32l = MEM_W(ctx->r1, 0X5F34);
    // 0x801DC80C: lwc1        $f4, 0x0($s0)
    ctx->f4.u32l = MEM_W(ctx->r16, 0X0);
    // 0x801DC810: lw          $t0, 0xA8($sp)
    ctx->r8 = MEM_W(ctx->r29, 0XA8);
    // 0x801DC814: mul.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = MUL_S(ctx->f6.fl, ctx->f8.fl);
    // 0x801DC818: lui         $at, 0x4F80
    ctx->r1 = S32(0X4F80 << 16);
    // 0x801DC81C: lwc1        $f6, 0x4($t0)
    ctx->f6.u32l = MEM_W(ctx->r8, 0X4);
    // 0x801DC820: mflo        $t2
    ctx->r10 = lo;
    // 0x801DC824: mtc1        $t2, $f8
    ctx->f8.u32l = ctx->r10;
    // 0x801DC828: mul.s       $f18, $f4, $f10
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f18.fl = MUL_S(ctx->f4.fl, ctx->f10.fl);
    // 0x801DC82C: bgez        $t2, L_801DC840
    if (SIGNED(ctx->r10) >= 0) {
        // 0x801DC830: cvt.s.w     $f4, $f8
        CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    ctx->f4.fl = CVT_S_W(ctx->f8.u32l);
            goto L_801DC840;
    }
    // 0x801DC830: cvt.s.w     $f4, $f8
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    ctx->f4.fl = CVT_S_W(ctx->f8.u32l);
    // 0x801DC834: mtc1        $at, $f10
    ctx->f10.u32l = ctx->r1;
    // 0x801DC838: nop

    // 0x801DC83C: add.s       $f4, $f4, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f4.fl = ctx->f4.fl + ctx->f10.fl;
L_801DC840:
    // 0x801DC840: sub.s       $f8, $f6, $f4
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f8.fl = ctx->f6.fl - ctx->f4.fl;
    // 0x801DC844: add.s       $f10, $f18, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = ctx->f18.fl + ctx->f8.fl;
    // 0x801DC848: jal         0x80047E50
    // 0x801DC84C: swc1        $f10, 0x10($s1)
    MEM_W(0X10, ctx->r17) = ctx->f10.u32l;
    SysUtils_Rand(rdram, ctx);
        goto after_5;
    // 0x801DC84C: swc1        $f10, 0x10($s1)
    MEM_W(0X10, ctx->r17) = ctx->f10.u32l;
    after_5:
    // 0x801DC850: andi        $t3, $v0, 0x7F
    ctx->r11 = ctx->r2 & 0X7F;
    // 0x801DC854: mtc1        $t3, $f4
    ctx->f4.u32l = ctx->r11;
    // 0x801DC858: lwc1        $f6, 0x0($s0)
    ctx->f6.u32l = MEM_W(ctx->r16, 0X0);
    // 0x801DC85C: bgez        $t3, L_801DC874
    if (SIGNED(ctx->r11) >= 0) {
        // 0x801DC860: cvt.s.w     $f18, $f4
        CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 4);
    ctx->f18.fl = CVT_S_W(ctx->f4.u32l);
            goto L_801DC874;
    }
    // 0x801DC860: cvt.s.w     $f18, $f4
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 4);
    ctx->f18.fl = CVT_S_W(ctx->f4.u32l);
    // 0x801DC864: lui         $at, 0x4F80
    ctx->r1 = S32(0X4F80 << 16);
    // 0x801DC868: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x801DC86C: nop

    // 0x801DC870: add.s       $f18, $f18, $f8
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f18.fl = ctx->f18.fl + ctx->f8.fl;
L_801DC874:
    // 0x801DC874: lw          $t4, 0xA8($sp)
    ctx->r12 = MEM_W(ctx->r29, 0XA8);
    // 0x801DC878: mul.s       $f10, $f6, $f18
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f10.fl = MUL_S(ctx->f6.fl, ctx->f18.fl);
    // 0x801DC87C: lwc1        $f4, 0x8($t4)
    ctx->f4.u32l = MEM_W(ctx->r12, 0X8);
    // 0x801DC880: swc1        $f24, 0x18($s1)
    MEM_W(0X18, ctx->r17) = ctx->f24.u32l;
    // 0x801DC884: swc1        $f24, 0x1C($s1)
    MEM_W(0X1C, ctx->r17) = ctx->f24.u32l;
    // 0x801DC888: swc1        $f26, 0x20($s1)
    MEM_W(0X20, ctx->r17) = ctx->f26.u32l;
    // 0x801DC88C: swc1        $f24, 0x24($s1)
    MEM_W(0X24, ctx->r17) = ctx->f24.u32l;
    // 0x801DC890: sub.s       $f8, $f4, $f10
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f8.fl = ctx->f4.fl - ctx->f10.fl;
    // 0x801DC894: swc1        $f26, 0x28($s1)
    MEM_W(0X28, ctx->r17) = ctx->f26.u32l;
    // 0x801DC898: swc1        $f24, 0x2C($s1)
    MEM_W(0X2C, ctx->r17) = ctx->f24.u32l;
    // 0x801DC89C: swc1        $f28, 0x30($s1)
    MEM_W(0X30, ctx->r17) = ctx->f28.u32l;
    // 0x801DC8A0: bne         $s4, $zero, L_801DC8B0
    if (ctx->r20 != 0) {
        // 0x801DC8A4: swc1        $f8, 0x14($s1)
        MEM_W(0X14, ctx->r17) = ctx->f8.u32l;
            goto L_801DC8B0;
    }
    // 0x801DC8A4: swc1        $f8, 0x14($s1)
    MEM_W(0X14, ctx->r17) = ctx->f8.u32l;
    // 0x801DC8A8: b           L_801DC928
    // 0x801DC8AC: swc1        $f30, 0x0($s2)
    MEM_W(0X0, ctx->r18) = ctx->f30.u32l;
        goto L_801DC928;
    // 0x801DC8AC: swc1        $f30, 0x0($s2)
    MEM_W(0X0, ctx->r18) = ctx->f30.u32l;
L_801DC8B0:
    // 0x801DC8B0: jal         0x80047E50
    // 0x801DC8B4: nop

    SysUtils_Rand(rdram, ctx);
        goto after_6;
    // 0x801DC8B4: nop

    after_6:
    // 0x801DC8B8: jal         0x80047E50
    // 0x801DC8BC: or          $s3, $v0, $zero
    ctx->r19 = ctx->r2 | 0;
    SysUtils_Rand(rdram, ctx);
        goto after_7;
    // 0x801DC8BC: or          $s3, $v0, $zero
    ctx->r19 = ctx->r2 | 0;
    after_7:
    // 0x801DC8C0: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
    // 0x801DC8C4: jal         0x800C7010
    // 0x801DC8C8: mov.s       $f12, $f22
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 22);
    ctx->f12.fl = ctx->f22.fl;
    _nsqrtf(rdram, ctx);
        goto after_8;
    // 0x801DC8C8: mov.s       $f12, $f22
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 22);
    ctx->f12.fl = ctx->f22.fl;
    after_8:
    // 0x801DC8CC: andi        $t5, $s3, 0x3
    ctx->r13 = ctx->r19 & 0X3;
    // 0x801DC8D0: mtc1        $t5, $f18
    ctx->f18.u32l = ctx->r13;
    // 0x801DC8D4: lui         $at, 0x4170
    ctx->r1 = S32(0X4170 << 16);
    // 0x801DC8D8: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x801DC8DC: bgez        $t5, L_801DC8F4
    if (SIGNED(ctx->r13) >= 0) {
        // 0x801DC8E0: cvt.s.w     $f4, $f18
        CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    ctx->f4.fl = CVT_S_W(ctx->f18.u32l);
            goto L_801DC8F4;
    }
    // 0x801DC8E0: cvt.s.w     $f4, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    ctx->f4.fl = CVT_S_W(ctx->f18.u32l);
    // 0x801DC8E4: lui         $at, 0x4F80
    ctx->r1 = S32(0X4F80 << 16);
    // 0x801DC8E8: mtc1        $at, $f10
    ctx->f10.u32l = ctx->r1;
    // 0x801DC8EC: nop

    // 0x801DC8F0: add.s       $f4, $f4, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f4.fl = ctx->f4.fl + ctx->f10.fl;
L_801DC8F4:
    // 0x801DC8F4: andi        $t6, $s0, 0x3
    ctx->r14 = ctx->r16 & 0X3;
    // 0x801DC8F8: addiu       $t7, $t6, 0x1
    ctx->r15 = ADD32(ctx->r14, 0X1);
    // 0x801DC8FC: mtc1        $t7, $f18
    ctx->f18.u32l = ctx->r15;
    // 0x801DC900: add.s       $f8, $f6, $f4
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f8.fl = ctx->f6.fl + ctx->f4.fl;
    // 0x801DC904: lui         $at, 0x4F80
    ctx->r1 = S32(0X4F80 << 16);
    // 0x801DC908: bgez        $t7, L_801DC91C
    if (SIGNED(ctx->r15) >= 0) {
        // 0x801DC90C: cvt.s.w     $f10, $f18
        CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 18);
    ctx->f10.fl = CVT_S_W(ctx->f18.u32l);
            goto L_801DC91C;
    }
    // 0x801DC90C: cvt.s.w     $f10, $f18
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 18);
    ctx->f10.fl = CVT_S_W(ctx->f18.u32l);
    // 0x801DC910: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x801DC914: nop

    // 0x801DC918: add.s       $f10, $f10, $f6
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f10.fl = ctx->f10.fl + ctx->f6.fl;
L_801DC91C:
    // 0x801DC91C: mul.s       $f4, $f0, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f4.fl = MUL_S(ctx->f0.fl, ctx->f10.fl);
    // 0x801DC920: add.s       $f18, $f4, $f8
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f18.fl = ctx->f4.fl + ctx->f8.fl;
    // 0x801DC924: swc1        $f18, 0x0($s2)
    MEM_W(0X0, ctx->r18) = ctx->f18.u32l;
L_801DC928:
    // 0x801DC928: addiu       $s4, $s4, 0x1
    ctx->r20 = ADD32(ctx->r20, 0X1);
    // 0x801DC92C: addiu       $at, $zero, 0x18
    ctx->r1 = ADD32(0, 0X18);
    // 0x801DC930: addiu       $s2, $s2, 0x4
    ctx->r18 = ADD32(ctx->r18, 0X4);
    // 0x801DC934: bne         $s4, $at, L_801DC6E8
    if (ctx->r20 != ctx->r1) {
        // 0x801DC938: addiu       $s1, $s1, 0x34
        ctx->r17 = ADD32(ctx->r17, 0X34);
            goto L_801DC6E8;
    }
    // 0x801DC938: addiu       $s1, $s1, 0x34
    ctx->r17 = ADD32(ctx->r17, 0X34);
    // 0x801DC93C: b           L_801DCCF0
    // 0x801DC940: lw          $ra, 0x6C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X6C);
        goto L_801DCCF0;
    // 0x801DC940: lw          $ra, 0x6C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X6C);
L_801DC944:
    // 0x801DC944: bltz        $s4, L_801DCCEC
    if (SIGNED(ctx->r20) < 0) {
        // 0x801DC948: lui         $at, 0x3F80
        ctx->r1 = S32(0X3F80 << 16);
            goto L_801DCCEC;
    }
    // 0x801DC948: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x801DC94C: mtc1        $s4, $f6
    ctx->f6.u32l = ctx->r20;
    // 0x801DC950: mtc1        $at, $f26
    ctx->f26.u32l = ctx->r1;
    // 0x801DC954: lui         $at, 0x4080
    ctx->r1 = S32(0X4080 << 16);
    // 0x801DC958: cvt.s.w     $f20, $f6
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 6);
    ctx->f20.fl = CVT_S_W(ctx->f6.u32l);
    // 0x801DC95C: lw          $a1, 0x0($v1)
    ctx->r5 = MEM_W(ctx->r3, 0X0);
    // 0x801DC960: mtc1        $at, $f10
    ctx->f10.u32l = ctx->r1;
    // 0x801DC964: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801DC968: lwc1        $f4, 0x5F38($at)
    ctx->f4.u32l = MEM_W(ctx->r1, 0X5F38);
    // 0x801DC96C: addiu       $a1, $a1, -0x1E
    ctx->r5 = ADD32(ctx->r5, -0X1E);
    // 0x801DC970: mtc1        $a1, $f6
    ctx->f6.u32l = ctx->r5;
    // 0x801DC974: mul.s       $f8, $f20, $f4
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f8.fl = MUL_S(ctx->f20.fl, ctx->f4.fl);
    // 0x801DC978: lui         $at, 0x4334
    ctx->r1 = S32(0X4334 << 16);
    // 0x801DC97C: lui         $s7, 0x8015
    ctx->r23 = S32(0X8015 << 16);
    // 0x801DC980: addiu       $s7, $s7, 0x4350
    ctx->r23 = ADD32(ctx->r23, 0X4350);
    // 0x801DC984: cvt.s.w     $f4, $f6
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    ctx->f4.fl = CVT_S_W(ctx->f6.u32l);
    // 0x801DC988: sub.s       $f18, $f10, $f8
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f18.fl = ctx->f10.fl - ctx->f8.fl;
    // 0x801DC98C: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x801DC990: lui         $at, 0x4580
    ctx->r1 = S32(0X4580 << 16);
    // 0x801DC994: div.s       $f10, $f20, $f4
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f10.fl = DIV_S(ctx->f20.fl, ctx->f4.fl);
    // 0x801DC998: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x801DC99C: lui         $at, 0x43B4
    ctx->r1 = S32(0X43B4 << 16);
    // 0x801DC9A0: swc1        $f18, 0x98($sp)
    MEM_W(0X98, ctx->r29) = ctx->f18.u32l;
    // 0x801DC9A4: mul.s       $f6, $f10, $f8
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f6.fl = MUL_S(ctx->f10.fl, ctx->f8.fl);
    // 0x801DC9A8: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x801DC9AC: mul.s       $f10, $f6, $f4
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f10.fl = MUL_S(ctx->f6.fl, ctx->f4.fl);
    // 0x801DC9B0: div.s       $f6, $f10, $f8
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f6.fl = DIV_S(ctx->f10.fl, ctx->f8.fl);
    // 0x801DC9B4: mul.s       $f8, $f18, $f18
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f8.fl = MUL_S(ctx->f18.fl, ctx->f18.fl);
    // 0x801DC9B8: trunc.w.s   $f4, $f6
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    ctx->f4.u32l = TRUNC_W_S(ctx->f6.fl);
    // 0x801DC9BC: mfc1        $t9, $f4
    ctx->r25 = (int32_t)ctx->f4.u32l;
    // 0x801DC9C0: nop

    // 0x801DC9C4: andi        $t0, $t9, 0xFFF
    ctx->r8 = ctx->r25 & 0XFFF;
    // 0x801DC9C8: sll         $t1, $t0, 2
    ctx->r9 = S32(ctx->r8 << 2);
    // 0x801DC9CC: addu        $t2, $s7, $t1
    ctx->r10 = ADD32(ctx->r23, ctx->r9);
    // 0x801DC9D0: lwc1        $f10, 0x0($t2)
    ctx->f10.u32l = MEM_W(ctx->r10, 0X0);
    // 0x801DC9D4: swc1        $f26, 0xA0($sp)
    MEM_W(0XA0, ctx->r29) = ctx->f26.u32l;
    // 0x801DC9D8: lwc1        $f18, 0xA0($sp)
    ctx->f18.u32l = MEM_W(ctx->r29, 0XA0);
    // 0x801DC9DC: swc1        $f10, 0x9C($sp)
    MEM_W(0X9C, ctx->r29) = ctx->f10.u32l;
    // 0x801DC9E0: lwc1        $f6, 0x9C($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X9C);
    // 0x801DC9E4: mul.s       $f4, $f6, $f6
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f4.fl = MUL_S(ctx->f6.fl, ctx->f6.fl);
    // 0x801DC9E8: add.s       $f10, $f8, $f4
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f10.fl = ctx->f8.fl + ctx->f4.fl;
    // 0x801DC9EC: mul.s       $f6, $f18, $f18
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f6.fl = MUL_S(ctx->f18.fl, ctx->f18.fl);
    // 0x801DC9F0: jal         0x800C7010
    // 0x801DC9F4: add.s       $f12, $f6, $f10
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f12.fl = ctx->f6.fl + ctx->f10.fl;
    _nsqrtf(rdram, ctx);
        goto after_9;
    // 0x801DC9F4: add.s       $f12, $f6, $f10
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f12.fl = ctx->f6.fl + ctx->f10.fl;
    after_9:
    // 0x801DC9F8: lui         $a0, 0x8023
    ctx->r4 = S32(0X8023 << 16);
    // 0x801DC9FC: addiu       $a0, $a0, -0x7E70
    ctx->r4 = ADD32(ctx->r4, -0X7E70);
    // 0x801DCA00: addiu       $v1, $sp, 0x98
    ctx->r3 = ADD32(ctx->r29, 0X98);
    // 0x801DCA04: addiu       $v0, $sp, 0xA4
    ctx->r2 = ADD32(ctx->r29, 0XA4);
    // 0x801DCA08: addiu       $v1, $v1, 0x4
    ctx->r3 = ADD32(ctx->r3, 0X4);
    // 0x801DCA0C: beq         $v1, $v0, L_801DCA2C
    if (ctx->r3 == ctx->r2) {
        // 0x801DCA10: lwc1        $f30, -0x4($v1)
        ctx->f30.u32l = MEM_W(ctx->r3, -0X4);
            goto L_801DCA2C;
    }
    // 0x801DCA10: lwc1        $f30, -0x4($v1)
    ctx->f30.u32l = MEM_W(ctx->r3, -0X4);
L_801DCA14:
    // 0x801DCA14: div.s       $f28, $f30, $f0
    CHECK_FR(ctx, 28);
    CHECK_FR(ctx, 30);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f30.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f28.fl = DIV_S(ctx->f30.fl, ctx->f0.fl);
    // 0x801DCA18: lwc1        $f30, 0x0($v1)
    ctx->f30.u32l = MEM_W(ctx->r3, 0X0);
    // 0x801DCA1C: addiu       $v1, $v1, 0x4
    ctx->r3 = ADD32(ctx->r3, 0X4);
    // 0x801DCA20: addiu       $a0, $a0, 0x4
    ctx->r4 = ADD32(ctx->r4, 0X4);
    // 0x801DCA24: bne         $v1, $v0, L_801DCA14
    if (ctx->r3 != ctx->r2) {
        // 0x801DCA28: swc1        $f28, 0x14($a0)
        MEM_W(0X14, ctx->r4) = ctx->f28.u32l;
            goto L_801DCA14;
    }
    // 0x801DCA28: swc1        $f28, 0x14($a0)
    MEM_W(0X14, ctx->r4) = ctx->f28.u32l;
L_801DCA2C:
    // 0x801DCA2C: div.s       $f28, $f30, $f0
    CHECK_FR(ctx, 28);
    CHECK_FR(ctx, 30);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f30.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f28.fl = DIV_S(ctx->f30.fl, ctx->f0.fl);
    // 0x801DCA30: addiu       $a0, $a0, 0x4
    ctx->r4 = ADD32(ctx->r4, 0X4);
    // 0x801DCA34: swc1        $f28, 0x14($a0)
    MEM_W(0X14, ctx->r4) = ctx->f28.u32l;
    // 0x801DCA38: lui         $at, 0x4188
    ctx->r1 = S32(0X4188 << 16);
    // 0x801DCA3C: mtc1        $at, $f30
    ctx->f30.u32l = ctx->r1;
    // 0x801DCA40: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801DCA44: lwc1        $f28, 0x5F3C($at)
    ctx->f28.u32l = MEM_W(ctx->r1, 0X5F3C);
    // 0x801DCA48: lui         $at, 0x3E00
    ctx->r1 = S32(0X3E00 << 16);
    // 0x801DCA4C: mtc1        $at, $f22
    ctx->f22.u32l = ctx->r1;
    // 0x801DCA50: addiu       $s4, $sp, 0xA4
    ctx->r20 = ADD32(ctx->r29, 0XA4);
    // 0x801DCA54: lui         $fp, 0x8023
    ctx->r30 = S32(0X8023 << 16);
    // 0x801DCA58: lui         $at, 0x40E0
    ctx->r1 = S32(0X40E0 << 16);
    // 0x801DCA5C: addiu       $fp, $fp, -0x7E70
    ctx->r30 = ADD32(ctx->r30, -0X7E70);
    // 0x801DCA60: lui         $s2, 0x8023
    ctx->r18 = S32(0X8023 << 16);
    // 0x801DCA64: mtc1        $at, $f20
    ctx->f20.u32l = ctx->r1;
    // 0x801DCA68: mtc1        $zero, $f24
    ctx->f24.u32l = 0;
    // 0x801DCA6C: addiu       $s2, $s2, -0x7EE0
    ctx->r18 = ADD32(ctx->r18, -0X7EE0);
    // 0x801DCA70: or          $s1, $fp, $zero
    ctx->r17 = ctx->r30 | 0;
    // 0x801DCA74: or          $s7, $s4, $zero
    ctx->r23 = ctx->r20 | 0;
    // 0x801DCA78: or          $s6, $s4, $zero
    ctx->r22 = ctx->r20 | 0;
    // 0x801DCA7C: or          $s5, $s4, $zero
    ctx->r21 = ctx->r20 | 0;
L_801DCA80:
    // 0x801DCA80: lwc1        $f0, 0x0($s2)
    ctx->f0.u32l = MEM_W(ctx->r18, 0X0);
    // 0x801DCA84: lui         $at, 0x4180
    ctx->r1 = S32(0X4180 << 16);
    // 0x801DCA88: mtc1        $at, $f18
    ctx->f18.u32l = ctx->r1;
    // 0x801DCA8C: c.lt.s      $f30, $f0
    CHECK_FR(ctx, 30);
    CHECK_FR(ctx, 0);
    c1cs = ctx->f30.fl < ctx->f0.fl;
    // 0x801DCA90: lui         $at, 0x4190
    ctx->r1 = S32(0X4190 << 16);
    // 0x801DCA94: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x801DCA98: addiu       $at, $zero, 0xA
    ctx->r1 = ADD32(0, 0XA);
    // 0x801DCA9C: bc1f        L_801DCAAC
    if (!c1cs) {
        // 0x801DCAA0: or          $v0, $zero, $zero
        ctx->r2 = 0 | 0;
            goto L_801DCAAC;
    }
    // 0x801DCAA0: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    // 0x801DCAA4: b           L_801DCAAC
    // 0x801DCAA8: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
        goto L_801DCAAC;
    // 0x801DCAA8: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
L_801DCAAC:
    // 0x801DCAAC: c.lt.s      $f18, $f0
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 0);
    c1cs = ctx->f18.fl < ctx->f0.fl;
    // 0x801DCAB0: lui         $a0, 0x8023
    ctx->r4 = S32(0X8023 << 16);
    // 0x801DCAB4: or          $s3, $zero, $zero
    ctx->r19 = 0 | 0;
    // 0x801DCAB8: or          $s0, $zero, $zero
    ctx->r16 = 0 | 0;
    // 0x801DCABC: bc1f        L_801DCACC
    if (!c1cs) {
        // 0x801DCAC0: addiu       $a0, $a0, -0x7E70
        ctx->r4 = ADD32(ctx->r4, -0X7E70);
            goto L_801DCACC;
    }
    // 0x801DCAC0: addiu       $a0, $a0, -0x7E70
    ctx->r4 = ADD32(ctx->r4, -0X7E70);
    // 0x801DCAC4: b           L_801DCACC
    // 0x801DCAC8: addiu       $s3, $zero, 0x1
    ctx->r19 = ADD32(0, 0X1);
        goto L_801DCACC;
    // 0x801DCAC8: addiu       $s3, $zero, 0x1
    ctx->r19 = ADD32(0, 0X1);
L_801DCACC:
    // 0x801DCACC: c.lt.s      $f6, $f0
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 0);
    c1cs = ctx->f6.fl < ctx->f0.fl;
    // 0x801DCAD0: addiu       $v1, $sp, 0x98
    ctx->r3 = ADD32(ctx->r29, 0X98);
    // 0x801DCAD4: bc1f        L_801DCAE4
    if (!c1cs) {
        // 0x801DCAD8: nop
    
            goto L_801DCAE4;
    }
    // 0x801DCAD8: nop

    // 0x801DCADC: b           L_801DCAE4
    // 0x801DCAE0: addiu       $s0, $zero, 0x1
    ctx->r16 = ADD32(0, 0X1);
        goto L_801DCAE4;
    // 0x801DCAE0: addiu       $s0, $zero, 0x1
    ctx->r16 = ADD32(0, 0X1);
L_801DCAE4:
    // 0x801DCAE4: lw          $t4, 0x8($s1)
    ctx->r12 = MEM_W(ctx->r17, 0X8);
    // 0x801DCAE8: lui         $t0, 0x8023
    ctx->r8 = S32(0X8023 << 16);
    // 0x801DCAEC: addiu       $t0, $t0, -0x7EDC
    ctx->r8 = ADD32(ctx->r8, -0X7EDC);
    // 0x801DCAF0: addu        $t5, $s0, $t4
    ctx->r13 = ADD32(ctx->r16, ctx->r12);
    // 0x801DCAF4: addu        $t6, $t5, $s3
    ctx->r14 = ADD32(ctx->r13, ctx->r19);
    // 0x801DCAF8: addu        $t7, $t6, $v0
    ctx->r15 = ADD32(ctx->r14, ctx->r2);
    // 0x801DCAFC: addiu       $t8, $t7, 0x1
    ctx->r24 = ADD32(ctx->r15, 0X1);
    // 0x801DCB00: div         $zero, $t8, $at
    lo = S32(S64(S32(ctx->r24)) / S64(S32(ctx->r1))); hi = S32(S64(S32(ctx->r24)) % S64(S32(ctx->r1)));
    // 0x801DCB04: mfhi        $t9
    ctx->r25 = hi;
    // 0x801DCB08: sltu        $at, $s2, $t0
    ctx->r1 = ctx->r18 < ctx->r8 ? 1 : 0;
    // 0x801DCB0C: bne         $at, $zero, L_801DCC34
    if (ctx->r1 != 0) {
        // 0x801DCB10: sw          $t9, 0x8($s1)
        MEM_W(0X8, ctx->r17) = ctx->r25;
            goto L_801DCC34;
    }
    // 0x801DCB10: sw          $t9, 0x8($s1)
    MEM_W(0X8, ctx->r17) = ctx->r25;
    // 0x801DCB14: or          $v0, $s1, $zero
    ctx->r2 = ctx->r17 | 0;
L_801DCB18:
    // 0x801DCB18: lwc1        $f10, 0xC($a0)
    ctx->f10.u32l = MEM_W(ctx->r4, 0XC);
    // 0x801DCB1C: lwc1        $f8, 0xC($v0)
    ctx->f8.u32l = MEM_W(ctx->r2, 0XC);
    // 0x801DCB20: addiu       $v1, $v1, 0x4
    ctx->r3 = ADD32(ctx->r3, 0X4);
    // 0x801DCB24: sltu        $at, $v1, $s4
    ctx->r1 = ctx->r3 < ctx->r20 ? 1 : 0;
    // 0x801DCB28: sub.s       $f4, $f10, $f8
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f4.fl = ctx->f10.fl - ctx->f8.fl;
    // 0x801DCB2C: addiu       $a0, $a0, 0x4
    ctx->r4 = ADD32(ctx->r4, 0X4);
    // 0x801DCB30: addiu       $v0, $v0, 0x4
    ctx->r2 = ADD32(ctx->r2, 0X4);
    // 0x801DCB34: bne         $at, $zero, L_801DCB18
    if (ctx->r1 != 0) {
        // 0x801DCB38: swc1        $f4, -0x4($v1)
        MEM_W(-0X4, ctx->r3) = ctx->f4.u32l;
            goto L_801DCB18;
    }
    // 0x801DCB38: swc1        $f4, -0x4($v1)
    MEM_W(-0X4, ctx->r3) = ctx->f4.u32l;
    // 0x801DCB3C: lwc1        $f0, 0x98($sp)
    ctx->f0.u32l = MEM_W(ctx->r29, 0X98);
    // 0x801DCB40: lwc1        $f14, 0x9C($sp)
    ctx->f14.u32l = MEM_W(ctx->r29, 0X9C);
    // 0x801DCB44: lwc1        $f16, 0xA0($sp)
    ctx->f16.u32l = MEM_W(ctx->r29, 0XA0);
    // 0x801DCB48: mul.s       $f18, $f0, $f0
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f18.fl = MUL_S(ctx->f0.fl, ctx->f0.fl);
    // 0x801DCB4C: nop

    // 0x801DCB50: mul.s       $f6, $f14, $f14
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f6.fl = MUL_S(ctx->f14.fl, ctx->f14.fl);
    // 0x801DCB54: add.s       $f10, $f18, $f6
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f10.fl = ctx->f18.fl + ctx->f6.fl;
    // 0x801DCB58: mul.s       $f8, $f16, $f16
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f8.fl = MUL_S(ctx->f16.fl, ctx->f16.fl);
    // 0x801DCB5C: jal         0x800C7010
    // 0x801DCB60: add.s       $f12, $f8, $f10
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f12.fl = ctx->f8.fl + ctx->f10.fl;
    _nsqrtf(rdram, ctx);
        goto after_10;
    // 0x801DCB60: add.s       $f12, $f8, $f10
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f12.fl = ctx->f8.fl + ctx->f10.fl;
    after_10:
    // 0x801DCB64: c.lt.s      $f0, $f28
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 28);
    c1cs = ctx->f0.fl < ctx->f28.fl;
    // 0x801DCB68: lui         $a0, 0x8023
    ctx->r4 = S32(0X8023 << 16);
    // 0x801DCB6C: mov.s       $f2, $f0
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 0);
    ctx->f2.fl = ctx->f0.fl;
    // 0x801DCB70: addiu       $a0, $a0, -0x7E70
    ctx->r4 = ADD32(ctx->r4, -0X7E70);
    // 0x801DCB74: bc1f        L_801DCB94
    if (!c1cs) {
        // 0x801DCB78: addiu       $v1, $sp, 0x98
        ctx->r3 = ADD32(ctx->r29, 0X98);
            goto L_801DCB94;
    }
    // 0x801DCB78: addiu       $v1, $sp, 0x98
    ctx->r3 = ADD32(ctx->r29, 0X98);
L_801DCB7C:
    // 0x801DCB7C: lwc1        $f4, 0x18($a0)
    ctx->f4.u32l = MEM_W(ctx->r4, 0X18);
    // 0x801DCB80: addiu       $v1, $v1, 0x4
    ctx->r3 = ADD32(ctx->r3, 0X4);
    // 0x801DCB84: addiu       $a0, $a0, 0x4
    ctx->r4 = ADD32(ctx->r4, 0X4);
    // 0x801DCB88: bne         $v1, $s5, L_801DCB7C
    if (ctx->r3 != ctx->r21) {
        // 0x801DCB8C: swc1        $f4, -0x4($v1)
        MEM_W(-0X4, ctx->r3) = ctx->f4.u32l;
            goto L_801DCB7C;
    }
    // 0x801DCB8C: swc1        $f4, -0x4($v1)
    MEM_W(-0X4, ctx->r3) = ctx->f4.u32l;
    // 0x801DCB90: mov.s       $f2, $f26
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 26);
    ctx->f2.fl = ctx->f26.fl;
L_801DCB94:
    // 0x801DCB94: lwc1        $f0, 0x98($sp)
    ctx->f0.u32l = MEM_W(ctx->r29, 0X98);
    // 0x801DCB98: lwc1        $f6, 0x18($fp)
    ctx->f6.u32l = MEM_W(ctx->r30, 0X18);
    // 0x801DCB9C: lwc1        $f14, 0x9C($sp)
    ctx->f14.u32l = MEM_W(ctx->r29, 0X9C);
    // 0x801DCBA0: div.s       $f18, $f0, $f2
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f18.fl = DIV_S(ctx->f0.fl, ctx->f2.fl);
    // 0x801DCBA4: lui         $at, 0x40A0
    ctx->r1 = S32(0X40A0 << 16);
    // 0x801DCBA8: lwc1        $f4, 0x1C($fp)
    ctx->f4.u32l = MEM_W(ctx->r30, 0X1C);
    // 0x801DCBAC: lwc1        $f16, 0xA0($sp)
    ctx->f16.u32l = MEM_W(ctx->r29, 0XA0);
    // 0x801DCBB0: mul.s       $f8, $f6, $f20
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f8.fl = MUL_S(ctx->f6.fl, ctx->f20.fl);
    // 0x801DCBB4: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x801DCBB8: lui         $at, 0x40C0
    ctx->r1 = S32(0X40C0 << 16);
    // 0x801DCBBC: add.s       $f10, $f18, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = ctx->f18.fl + ctx->f8.fl;
    // 0x801DCBC0: div.s       $f8, $f14, $f2
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f8.fl = DIV_S(ctx->f14.fl, ctx->f2.fl);
    // 0x801DCBC4: mul.s       $f0, $f10, $f22
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f0.fl = MUL_S(ctx->f10.fl, ctx->f22.fl);
    // 0x801DCBC8: nop

    // 0x801DCBCC: mul.s       $f18, $f4, $f6
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f18.fl = MUL_S(ctx->f4.fl, ctx->f6.fl);
    // 0x801DCBD0: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x801DCBD4: swc1        $f0, 0x98($sp)
    MEM_W(0X98, ctx->r29) = ctx->f0.u32l;
    // 0x801DCBD8: div.s       $f6, $f16, $f2
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f6.fl = DIV_S(ctx->f16.fl, ctx->f2.fl);
    // 0x801DCBDC: add.s       $f10, $f8, $f18
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f10.fl = ctx->f8.fl + ctx->f18.fl;
    // 0x801DCBE0: lwc1        $f8, 0x20($fp)
    ctx->f8.u32l = MEM_W(ctx->r30, 0X20);
    // 0x801DCBE4: mul.s       $f18, $f8, $f20
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f18.fl = MUL_S(ctx->f8.fl, ctx->f20.fl);
    // 0x801DCBE8: div.s       $f14, $f10, $f4
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f14.fl = DIV_S(ctx->f10.fl, ctx->f4.fl);
    // 0x801DCBEC: add.s       $f10, $f6, $f18
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f10.fl = ctx->f6.fl + ctx->f18.fl;
    // 0x801DCBF0: mul.s       $f16, $f10, $f22
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f16.fl = MUL_S(ctx->f10.fl, ctx->f22.fl);
    // 0x801DCBF4: swc1        $f16, 0xA0($sp)
    MEM_W(0XA0, ctx->r29) = ctx->f16.u32l;
    // 0x801DCBF8: mul.s       $f4, $f0, $f0
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f4.fl = MUL_S(ctx->f0.fl, ctx->f0.fl);
    // 0x801DCBFC: swc1        $f14, 0x9C($sp)
    MEM_W(0X9C, ctx->r29) = ctx->f14.u32l;
    // 0x801DCC00: mul.s       $f8, $f14, $f14
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f8.fl = MUL_S(ctx->f14.fl, ctx->f14.fl);
    // 0x801DCC04: add.s       $f6, $f4, $f8
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f6.fl = ctx->f4.fl + ctx->f8.fl;
    // 0x801DCC08: mul.s       $f18, $f16, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f18.fl = MUL_S(ctx->f16.fl, ctx->f16.fl);
    // 0x801DCC0C: jal         0x800C7010
    // 0x801DCC10: add.s       $f12, $f18, $f6
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f12.fl = ctx->f18.fl + ctx->f6.fl;
    _nsqrtf(rdram, ctx);
        goto after_11;
    // 0x801DCC10: add.s       $f12, $f18, $f6
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f12.fl = ctx->f18.fl + ctx->f6.fl;
    after_11:
    // 0x801DCC14: addiu       $v1, $sp, 0x98
    ctx->r3 = ADD32(ctx->r29, 0X98);
    // 0x801DCC18: or          $v0, $s1, $zero
    ctx->r2 = ctx->r17 | 0;
L_801DCC1C:
    // 0x801DCC1C: lwc1        $f10, 0x0($v1)
    ctx->f10.u32l = MEM_W(ctx->r3, 0X0);
    // 0x801DCC20: addiu       $v1, $v1, 0x4
    ctx->r3 = ADD32(ctx->r3, 0X4);
    // 0x801DCC24: addiu       $v0, $v0, 0x4
    ctx->r2 = ADD32(ctx->r2, 0X4);
    // 0x801DCC28: div.s       $f4, $f10, $f0
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f4.fl = DIV_S(ctx->f10.fl, ctx->f0.fl);
    // 0x801DCC2C: bne         $v1, $s6, L_801DCC1C
    if (ctx->r3 != ctx->r22) {
        // 0x801DCC30: swc1        $f4, 0x14($v0)
        MEM_W(0X14, ctx->r2) = ctx->f4.u32l;
            goto L_801DCC1C;
    }
    // 0x801DCC30: swc1        $f4, 0x14($v0)
    MEM_W(0X14, ctx->r2) = ctx->f4.u32l;
L_801DCC34:
    // 0x801DCC34: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x801DCC38: or          $v0, $s1, $zero
    ctx->r2 = ctx->r17 | 0;
L_801DCC3C:
    // 0x801DCC3C: lwc1        $f8, 0x18($v0)
    ctx->f8.u32l = MEM_W(ctx->r2, 0X18);
    // 0x801DCC40: lwc1        $f18, 0x0($s2)
    ctx->f18.u32l = MEM_W(ctx->r18, 0X0);
    // 0x801DCC44: lwc1        $f10, 0xC($v0)
    ctx->f10.u32l = MEM_W(ctx->r2, 0XC);
    // 0x801DCC48: addiu       $a1, $a1, 0x1
    ctx->r5 = ADD32(ctx->r5, 0X1);
    // 0x801DCC4C: mul.s       $f6, $f8, $f18
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f6.fl = MUL_S(ctx->f8.fl, ctx->f18.fl);
    // 0x801DCC50: slti        $at, $a1, 0x3
    ctx->r1 = SIGNED(ctx->r5) < 0X3 ? 1 : 0;
    // 0x801DCC54: addiu       $v0, $v0, 0x4
    ctx->r2 = ADD32(ctx->r2, 0X4);
    // 0x801DCC58: add.s       $f4, $f10, $f6
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f4.fl = ctx->f10.fl + ctx->f6.fl;
    // 0x801DCC5C: bne         $at, $zero, L_801DCC3C
    if (ctx->r1 != 0) {
        // 0x801DCC60: swc1        $f4, 0x8($v0)
        MEM_W(0X8, ctx->r2) = ctx->f4.u32l;
            goto L_801DCC3C;
    }
    // 0x801DCC60: swc1        $f4, 0x8($v0)
    MEM_W(0X8, ctx->r2) = ctx->f4.u32l;
    // 0x801DCC64: lw          $t1, 0xA8($sp)
    ctx->r9 = MEM_W(ctx->r29, 0XA8);
    // 0x801DCC68: lwc1        $f18, 0xC($s1)
    ctx->f18.u32l = MEM_W(ctx->r17, 0XC);
    // 0x801DCC6C: lui         $at, 0x4496
    ctx->r1 = S32(0X4496 << 16);
    // 0x801DCC70: lwc1        $f8, 0x0($t1)
    ctx->f8.u32l = MEM_W(ctx->r9, 0X0);
    // 0x801DCC74: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x801DCC78: swc1        $f24, 0xA0($sp)
    MEM_W(0XA0, ctx->r29) = ctx->f24.u32l;
    // 0x801DCC7C: sub.s       $f10, $f8, $f18
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f10.fl = ctx->f8.fl - ctx->f18.fl;
    // 0x801DCC80: swc1        $f6, 0x9C($sp)
    MEM_W(0X9C, ctx->r29) = ctx->f6.u32l;
    // 0x801DCC84: mul.s       $f4, $f10, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f4.fl = MUL_S(ctx->f10.fl, ctx->f10.fl);
    // 0x801DCC88: swc1        $f10, 0x98($sp)
    MEM_W(0X98, ctx->r29) = ctx->f10.u32l;
    // 0x801DCC8C: lwc1        $f10, 0xA0($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0XA0);
    // 0x801DCC90: mul.s       $f8, $f6, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = MUL_S(ctx->f6.fl, ctx->f6.fl);
    // 0x801DCC94: add.s       $f18, $f4, $f8
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f18.fl = ctx->f4.fl + ctx->f8.fl;
    // 0x801DCC98: mul.s       $f6, $f10, $f10
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f6.fl = MUL_S(ctx->f10.fl, ctx->f10.fl);
    // 0x801DCC9C: jal         0x800C7010
    // 0x801DCCA0: add.s       $f12, $f6, $f18
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f12.fl = ctx->f6.fl + ctx->f18.fl;
    _nsqrtf(rdram, ctx);
        goto after_12;
    // 0x801DCCA0: add.s       $f12, $f6, $f18
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f12.fl = ctx->f6.fl + ctx->f18.fl;
    after_12:
    // 0x801DCCA4: addiu       $v1, $sp, 0x98
    ctx->r3 = ADD32(ctx->r29, 0X98);
    // 0x801DCCA8: or          $v0, $s1, $zero
    ctx->r2 = ctx->r17 | 0;
L_801DCCAC:
    // 0x801DCCAC: lwc1        $f4, 0x0($v1)
    ctx->f4.u32l = MEM_W(ctx->r3, 0X0);
    // 0x801DCCB0: addiu       $v1, $v1, 0x4
    ctx->r3 = ADD32(ctx->r3, 0X4);
    // 0x801DCCB4: addiu       $v0, $v0, 0x4
    ctx->r2 = ADD32(ctx->r2, 0X4);
    // 0x801DCCB8: div.s       $f8, $f4, $f0
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f8.fl = DIV_S(ctx->f4.fl, ctx->f0.fl);
    // 0x801DCCBC: bne         $v1, $s7, L_801DCCAC
    if (ctx->r3 != ctx->r23) {
        // 0x801DCCC0: swc1        $f8, 0x20($v0)
        MEM_W(0X20, ctx->r2) = ctx->f8.u32l;
            goto L_801DCCAC;
    }
    // 0x801DCCC0: swc1        $f8, 0x20($v0)
    MEM_W(0X20, ctx->r2) = ctx->f8.u32l;
    // 0x801DCCC4: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801DCCC8: lwc1        $f6, 0x5F40($at)
    ctx->f6.u32l = MEM_W(ctx->r1, 0X5F40);
    // 0x801DCCCC: lwc1        $f10, 0x0($s2)
    ctx->f10.u32l = MEM_W(ctx->r18, 0X0);
    // 0x801DCCD0: lui         $t2, 0x8023
    ctx->r10 = S32(0X8023 << 16);
    // 0x801DCCD4: addiu       $t2, $t2, -0x7E80
    ctx->r10 = ADD32(ctx->r10, -0X7E80);
    // 0x801DCCD8: sub.s       $f18, $f10, $f6
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f18.fl = ctx->f10.fl - ctx->f6.fl;
    // 0x801DCCDC: addiu       $s2, $s2, 0x4
    ctx->r18 = ADD32(ctx->r18, 0X4);
    // 0x801DCCE0: addiu       $s1, $s1, 0x34
    ctx->r17 = ADD32(ctx->r17, 0X34);
    // 0x801DCCE4: bne         $s2, $t2, L_801DCA80
    if (ctx->r18 != ctx->r10) {
        // 0x801DCCE8: swc1        $f18, -0x4($s2)
        MEM_W(-0X4, ctx->r18) = ctx->f18.u32l;
            goto L_801DCA80;
    }
    // 0x801DCCE8: swc1        $f18, -0x4($s2)
    MEM_W(-0X4, ctx->r18) = ctx->f18.u32l;
L_801DCCEC:
    // 0x801DCCEC: lw          $ra, 0x6C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X6C);
L_801DCCF0:
    // 0x801DCCF0: ldc1        $f20, 0x18($sp)
    CHECK_FR(ctx, 20);
    ctx->f20.u64 = LD(ctx->r29, 0X18);
    // 0x801DCCF4: ldc1        $f22, 0x20($sp)
    CHECK_FR(ctx, 22);
    ctx->f22.u64 = LD(ctx->r29, 0X20);
    // 0x801DCCF8: ldc1        $f24, 0x28($sp)
    CHECK_FR(ctx, 24);
    ctx->f24.u64 = LD(ctx->r29, 0X28);
    // 0x801DCCFC: ldc1        $f26, 0x30($sp)
    CHECK_FR(ctx, 26);
    ctx->f26.u64 = LD(ctx->r29, 0X30);
    // 0x801DCD00: ldc1        $f28, 0x38($sp)
    CHECK_FR(ctx, 28);
    ctx->f28.u64 = LD(ctx->r29, 0X38);
    // 0x801DCD04: ldc1        $f30, 0x40($sp)
    CHECK_FR(ctx, 30);
    ctx->f30.u64 = LD(ctx->r29, 0X40);
    // 0x801DCD08: lw          $s0, 0x48($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X48);
    // 0x801DCD0C: lw          $s1, 0x4C($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X4C);
    // 0x801DCD10: lw          $s2, 0x50($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X50);
    // 0x801DCD14: lw          $s3, 0x54($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X54);
    // 0x801DCD18: lw          $s4, 0x58($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X58);
    // 0x801DCD1C: lw          $s5, 0x5C($sp)
    ctx->r21 = MEM_W(ctx->r29, 0X5C);
    // 0x801DCD20: lw          $s6, 0x60($sp)
    ctx->r22 = MEM_W(ctx->r29, 0X60);
    // 0x801DCD24: lw          $s7, 0x64($sp)
    ctx->r23 = MEM_W(ctx->r29, 0X64);
    // 0x801DCD28: lw          $fp, 0x68($sp)
    ctx->r30 = MEM_W(ctx->r29, 0X68);
    // 0x801DCD2C: jr          $ra
    // 0x801DCD30: addiu       $sp, $sp, 0xB0
    ctx->r29 = ADD32(ctx->r29, 0XB0);
    return;
    // 0x801DCD30: addiu       $sp, $sp, 0xB0
    ctx->r29 = ADD32(ctx->r29, 0XB0);
;}
RECOMP_FUNC void func_801DCD34(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801DCD34: addiu       $sp, $sp, -0x38
    ctx->r29 = ADD32(ctx->r29, -0X38);
    // 0x801DCD38: sw          $ra, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r31;
    // 0x801DCD3C: sw          $s3, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r19;
    // 0x801DCD40: sw          $s2, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r18;
    // 0x801DCD44: sw          $s1, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r17;
    // 0x801DCD48: sw          $s0, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r16;
    // 0x801DCD4C: sdc1        $f22, 0x18($sp)
    CHECK_FR(ctx, 22);
    SD(ctx->f22.u64, 0X18, ctx->r29);
    // 0x801DCD50: sdc1        $f20, 0x10($sp)
    CHECK_FR(ctx, 20);
    SD(ctx->f20.u64, 0X10, ctx->r29);
    // 0x801DCD54: lw          $t6, 0x4($a0)
    ctx->r14 = MEM_W(ctx->r4, 0X4);
    // 0x801DCD58: lui         $t7, 0x8022
    ctx->r15 = S32(0X8022 << 16);
    // 0x801DCD5C: addiu       $t7, $t7, 0x42C0
    ctx->r15 = ADD32(ctx->r15, 0X42C0);
    // 0x801DCD60: addiu       $at, $zero, 0xC
    ctx->r1 = ADD32(0, 0XC);
    // 0x801DCD64: subu        $a1, $t6, $t7
    ctx->r5 = SUB32(ctx->r14, ctx->r15);
    // 0x801DCD68: div         $zero, $a1, $at
    lo = S32(S64(S32(ctx->r5)) / S64(S32(ctx->r1))); hi = S32(S64(S32(ctx->r5)) % S64(S32(ctx->r1)));
    // 0x801DCD6C: mflo        $t8
    ctx->r24 = lo;
    // 0x801DCD70: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x801DCD74: bne         $t8, $at, L_801DD2AC
    if (ctx->r24 != ctx->r1) {
        // 0x801DCD78: or          $s3, $a0, $zero
        ctx->r19 = ctx->r4 | 0;
            goto L_801DD2AC;
    }
    // 0x801DCD78: or          $s3, $a0, $zero
    ctx->r19 = ctx->r4 | 0;
    // 0x801DCD7C: addiu       $s1, $zero, 0x1
    ctx->r17 = ADD32(0, 0X1);
    // 0x801DCD80: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801DCD84: sw          $s1, -0x7858($at)
    MEM_W(-0X7858, ctx->r1) = ctx->r17;
    // 0x801DCD88: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801DCD8C: lwc1        $f4, 0x5F44($at)
    ctx->f4.u32l = MEM_W(ctx->r1, 0X5F44);
    // 0x801DCD90: lui         $s0, 0x8023
    ctx->r16 = S32(0X8023 << 16);
    // 0x801DCD94: addiu       $s0, $s0, -0x7840
    ctx->r16 = ADD32(ctx->r16, -0X7840);
    // 0x801DCD98: swc1        $f4, 0x0($s0)
    MEM_W(0X0, ctx->r16) = ctx->f4.u32l;
    // 0x801DCD9C: lw          $v0, 0x8($a0)
    ctx->r2 = MEM_W(ctx->r4, 0X8);
    // 0x801DCDA0: addiu       $t9, $zero, 0x96
    ctx->r25 = ADD32(0, 0X96);
    // 0x801DCDA4: slti        $at, $v0, 0x96
    ctx->r1 = SIGNED(ctx->r2) < 0X96 ? 1 : 0;
    // 0x801DCDA8: beq         $at, $zero, L_801DCDD4
    if (ctx->r1 == 0) {
        // 0x801DCDAC: subu        $t0, $t9, $v0
        ctx->r8 = SUB32(ctx->r25, ctx->r2);
            goto L_801DCDD4;
    }
    // 0x801DCDAC: subu        $t0, $t9, $v0
    ctx->r8 = SUB32(ctx->r25, ctx->r2);
    // 0x801DCDB0: mtc1        $t0, $f6
    ctx->f6.u32l = ctx->r8;
    // 0x801DCDB4: jal         0x800C7010
    // 0x801DCDB8: cvt.s.w     $f12, $f6
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 6);
    ctx->f12.fl = CVT_S_W(ctx->f6.u32l);
    _nsqrtf(rdram, ctx);
        goto after_0;
    // 0x801DCDB8: cvt.s.w     $f12, $f6
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 6);
    ctx->f12.fl = CVT_S_W(ctx->f6.u32l);
    after_0:
    // 0x801DCDBC: lui         $at, 0x4140
    ctx->r1 = S32(0X4140 << 16);
    // 0x801DCDC0: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x801DCDC4: mtc1        $zero, $f22
    ctx->f22.u32l = 0;
    // 0x801DCDC8: mul.s       $f2, $f0, $f8
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f2.fl = MUL_S(ctx->f0.fl, ctx->f8.fl);
    // 0x801DCDCC: b           L_801DCDE0
    // 0x801DCDD0: nop

        goto L_801DCDE0;
    // 0x801DCDD0: nop

L_801DCDD4:
    // 0x801DCDD4: mtc1        $zero, $f22
    ctx->f22.u32l = 0;
    // 0x801DCDD8: nop

    // 0x801DCDDC: mov.s       $f2, $f22
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 22);
    ctx->f2.fl = ctx->f22.fl;
L_801DCDE0:
    // 0x801DCDE0: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801DCDE4: lwc1        $f10, 0x5F48($at)
    ctx->f10.u32l = MEM_W(ctx->r1, 0X5F48);
    // 0x801DCDE8: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801DCDEC: add.s       $f4, $f2, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f4.fl = ctx->f2.fl + ctx->f10.fl;
    // 0x801DCDF0: swc1        $f4, 0x4($s0)
    MEM_W(0X4, ctx->r16) = ctx->f4.u32l;
    // 0x801DCDF4: lwc1        $f6, 0x5F4C($at)
    ctx->f6.u32l = MEM_W(ctx->r1, 0X5F4C);
    // 0x801DCDF8: swc1        $f6, 0x8($s0)
    MEM_W(0X8, ctx->r16) = ctx->f6.u32l;
    // 0x801DCDFC: lw          $t1, 0x8($s3)
    ctx->r9 = MEM_W(ctx->r19, 0X8);
    // 0x801DCE00: bne         $s1, $t1, L_801DCE8C
    if (ctx->r17 != ctx->r9) {
        // 0x801DCE04: nop
    
            goto L_801DCE8C;
    }
    // 0x801DCE04: nop

    // 0x801DCE08: jal         0x800AB92C
    // 0x801DCE0C: nop

    func_800AB92C(rdram, ctx);
        goto after_1;
    // 0x801DCE0C: nop

    after_1:
    // 0x801DCE10: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801DCE14: addiu       $t2, $zero, 0xC
    ctx->r10 = ADD32(0, 0XC);
    // 0x801DCE18: sw          $t2, -0x7E70($at)
    MEM_W(-0X7E70, ctx->r1) = ctx->r10;
    // 0x801DCE1C: sw          $zero, -0x7E6C($at)
    MEM_W(-0X7E6C, ctx->r1) = 0;
    // 0x801DCE20: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801DCE24: sw          $zero, -0x7E68($at)
    MEM_W(-0X7E68, ctx->r1) = 0;
    // 0x801DCE28: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801DCE2C: lwc1        $f10, 0x5F50($at)
    ctx->f10.u32l = MEM_W(ctx->r1, 0X5F50);
    // 0x801DCE30: lwc1        $f8, 0x0($s0)
    ctx->f8.u32l = MEM_W(ctx->r16, 0X0);
    // 0x801DCE34: lui         $at, 0x43E1
    ctx->r1 = S32(0X43E1 << 16);
    // 0x801DCE38: lwc1        $f6, 0x4($s0)
    ctx->f6.u32l = MEM_W(ctx->r16, 0X4);
    // 0x801DCE3C: sub.s       $f4, $f8, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f4.fl = ctx->f8.fl - ctx->f10.fl;
    // 0x801DCE40: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x801DCE44: lui         $v0, 0x8023
    ctx->r2 = S32(0X8023 << 16);
    // 0x801DCE48: addiu       $v0, $v0, -0x7850
    ctx->r2 = ADD32(ctx->r2, -0X7850);
    // 0x801DCE4C: add.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = ctx->f6.fl + ctx->f8.fl;
    // 0x801DCE50: swc1        $f4, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->f4.u32l;
    // 0x801DCE54: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801DCE58: lwc1        $f4, 0x8($s0)
    ctx->f4.u32l = MEM_W(ctx->r16, 0X8);
    // 0x801DCE5C: swc1        $f10, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->f10.u32l;
    // 0x801DCE60: lwc1        $f6, 0x5F54($at)
    ctx->f6.u32l = MEM_W(ctx->r1, 0X5F54);
    // 0x801DCE64: lui         $at, 0x428C
    ctx->r1 = S32(0X428C << 16);
    // 0x801DCE68: mtc1        $at, $f10
    ctx->f10.u32l = ctx->r1;
    // 0x801DCE6C: sub.s       $f8, $f4, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = ctx->f4.fl - ctx->f6.fl;
    // 0x801DCE70: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801DCE74: swc1        $f8, 0x8($v0)
    MEM_W(0X8, ctx->r2) = ctx->f8.u32l;
    // 0x801DCE78: swc1        $f10, -0x7EE0($at)
    MEM_W(-0X7EE0, ctx->r1) = ctx->f10.u32l;
    // 0x801DCE7C: lui         $at, 0x3E80
    ctx->r1 = S32(0X3E80 << 16);
    // 0x801DCE80: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x801DCE84: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801DCE88: swc1        $f4, -0x7E40($at)
    MEM_W(-0X7E40, ctx->r1) = ctx->f4.u32l;
L_801DCE8C:
    // 0x801DCE8C: lui         $s1, 0x8023
    ctx->r17 = S32(0X8023 << 16);
    // 0x801DCE90: lui         $s0, 0x8023
    ctx->r16 = S32(0X8023 << 16);
    // 0x801DCE94: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801DCE98: lui         $s2, 0x8023
    ctx->r18 = S32(0X8023 << 16);
    // 0x801DCE9C: addiu       $s2, $s2, -0x7844
    ctx->r18 = ADD32(ctx->r18, -0X7844);
    // 0x801DCEA0: lwc1        $f20, 0x5F58($at)
    ctx->f20.u32l = MEM_W(ctx->r1, 0X5F58);
    // 0x801DCEA4: addiu       $s0, $s0, -0x7850
    ctx->r16 = ADD32(ctx->r16, -0X7850);
    // 0x801DCEA8: addiu       $s1, $s1, -0x7840
    ctx->r17 = ADD32(ctx->r17, -0X7840);
L_801DCEAC:
    // 0x801DCEAC: lwc1        $f6, 0x0($s1)
    ctx->f6.u32l = MEM_W(ctx->r17, 0X0);
    // 0x801DCEB0: lwc1        $f8, 0x0($s0)
    ctx->f8.u32l = MEM_W(ctx->r16, 0X0);
    // 0x801DCEB4: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801DCEB8: sub.s       $f14, $f6, $f8
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f14.fl = ctx->f6.fl - ctx->f8.fl;
    // 0x801DCEBC: c.le.s      $f22, $f14
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 14);
    c1cs = ctx->f22.fl <= ctx->f14.fl;
    // 0x801DCEC0: nop

    // 0x801DCEC4: bc1fl       L_801DCEE8
    if (!c1cs) {
        // 0x801DCEC8: neg.s       $f12, $f14
        CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f14.fl); 
    ctx->f12.fl = -ctx->f14.fl;
            goto L_801DCEE8;
    }
    goto skip_0;
    // 0x801DCEC8: neg.s       $f12, $f14
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f14.fl); 
    ctx->f12.fl = -ctx->f14.fl;
    skip_0:
    // 0x801DCECC: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801DCED0: swc1        $f14, -0x7824($at)
    MEM_W(-0X7824, ctx->r1) = ctx->f14.u32l;
    // 0x801DCED4: jal         0x800C7010
    // 0x801DCED8: mov.s       $f12, $f14
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 14);
    ctx->f12.fl = ctx->f14.fl;
    _nsqrtf(rdram, ctx);
        goto after_2;
    // 0x801DCED8: mov.s       $f12, $f14
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 14);
    ctx->f12.fl = ctx->f14.fl;
    after_2:
    // 0x801DCEDC: b           L_801DCEF4
    // 0x801DCEE0: mov.s       $f2, $f0
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 0);
    ctx->f2.fl = ctx->f0.fl;
        goto L_801DCEF4;
    // 0x801DCEE0: mov.s       $f2, $f0
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 0);
    ctx->f2.fl = ctx->f0.fl;
    // 0x801DCEE4: neg.s       $f12, $f14
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f14.fl); 
    ctx->f12.fl = -ctx->f14.fl;
L_801DCEE8:
    // 0x801DCEE8: jal         0x800C7010
    // 0x801DCEEC: swc1        $f14, -0x7824($at)
    MEM_W(-0X7824, ctx->r1) = ctx->f14.u32l;
    _nsqrtf(rdram, ctx);
        goto after_3;
    // 0x801DCEEC: swc1        $f14, -0x7824($at)
    MEM_W(-0X7824, ctx->r1) = ctx->f14.u32l;
    after_3:
    // 0x801DCEF0: neg.s       $f2, $f0
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f0.fl); 
    ctx->f2.fl = -ctx->f0.fl;
L_801DCEF4:
    // 0x801DCEF4: mul.s       $f4, $f2, $f20
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f4.fl = MUL_S(ctx->f2.fl, ctx->f20.fl);
    // 0x801DCEF8: lwc1        $f10, 0x0($s0)
    ctx->f10.u32l = MEM_W(ctx->r16, 0X0);
    // 0x801DCEFC: addiu       $s0, $s0, 0x4
    ctx->r16 = ADD32(ctx->r16, 0X4);
    // 0x801DCF00: sltu        $at, $s0, $s2
    ctx->r1 = ctx->r16 < ctx->r18 ? 1 : 0;
    // 0x801DCF04: addiu       $s1, $s1, 0x4
    ctx->r17 = ADD32(ctx->r17, 0X4);
    // 0x801DCF08: add.s       $f6, $f10, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = ctx->f10.fl + ctx->f4.fl;
    // 0x801DCF0C: bne         $at, $zero, L_801DCEAC
    if (ctx->r1 != 0) {
        // 0x801DCF10: swc1        $f6, -0x4($s0)
        MEM_W(-0X4, ctx->r16) = ctx->f6.u32l;
            goto L_801DCEAC;
    }
    // 0x801DCF10: swc1        $f6, -0x4($s0)
    MEM_W(-0X4, ctx->r16) = ctx->f6.u32l;
    // 0x801DCF14: lw          $t3, 0x8($s3)
    ctx->r11 = MEM_W(ctx->r19, 0X8);
    // 0x801DCF18: lui         $at, 0x4580
    ctx->r1 = S32(0X4580 << 16);
    // 0x801DCF1C: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
    // 0x801DCF20: addiu       $t4, $t3, -0x96
    ctx->r12 = ADD32(ctx->r11, -0X96);
    // 0x801DCF24: mtc1        $t4, $f8
    ctx->f8.u32l = ctx->r12;
    // 0x801DCF28: lui         $at, 0x43B4
    ctx->r1 = S32(0X43B4 << 16);
    // 0x801DCF2C: mtc1        $at, $f18
    ctx->f18.u32l = ctx->r1;
    // 0x801DCF30: cvt.s.w     $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.fl = CVT_S_W(ctx->f8.u32l);
    // 0x801DCF34: lui         $at, 0x4100
    ctx->r1 = S32(0X4100 << 16);
    // 0x801DCF38: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x801DCF3C: lui         $v0, 0x8015
    ctx->r2 = S32(0X8015 << 16);
    // 0x801DCF40: addiu       $v0, $v0, 0x4350
    ctx->r2 = ADD32(ctx->r2, 0X4350);
    // 0x801DCF44: lui         $at, 0x41A0
    ctx->r1 = S32(0X41A0 << 16);
    // 0x801DCF48: mul.s       $f6, $f10, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = MUL_S(ctx->f10.fl, ctx->f4.fl);
    // 0x801DCF4C: lui         $s0, 0x8023
    ctx->r16 = S32(0X8023 << 16);
    // 0x801DCF50: addiu       $s0, $s0, -0x7830
    ctx->r16 = ADD32(ctx->r16, -0X7830);
    // 0x801DCF54: mul.s       $f8, $f6, $f16
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f8.fl = MUL_S(ctx->f6.fl, ctx->f16.fl);
    // 0x801DCF58: div.s       $f10, $f8, $f18
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f10.fl = DIV_S(ctx->f8.fl, ctx->f18.fl);
    // 0x801DCF5C: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x801DCF60: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801DCF64: trunc.w.s   $f4, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    ctx->f4.u32l = TRUNC_W_S(ctx->f10.fl);
    // 0x801DCF68: mfc1        $t6, $f4
    ctx->r14 = (int32_t)ctx->f4.u32l;
    // 0x801DCF6C: lwc1        $f4, -0x7850($at)
    ctx->f4.u32l = MEM_W(ctx->r1, -0X7850);
    // 0x801DCF70: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801DCF74: andi        $t7, $t6, 0xFFF
    ctx->r15 = ctx->r14 & 0XFFF;
    // 0x801DCF78: sll         $t8, $t7, 2
    ctx->r24 = S32(ctx->r15 << 2);
    // 0x801DCF7C: addu        $t9, $v0, $t8
    ctx->r25 = ADD32(ctx->r2, ctx->r24);
    // 0x801DCF80: lwc1        $f6, 0x0($t9)
    ctx->f6.u32l = MEM_W(ctx->r25, 0X0);
    // 0x801DCF84: mul.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = MUL_S(ctx->f6.fl, ctx->f8.fl);
    // 0x801DCF88: sub.s       $f6, $f4, $f10
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f6.fl = ctx->f4.fl - ctx->f10.fl;
    // 0x801DCF8C: swc1        $f6, -0x7E64($at)
    MEM_W(-0X7E64, ctx->r1) = ctx->f6.u32l;
    // 0x801DCF90: lw          $t0, 0x8($s3)
    ctx->r8 = MEM_W(ctx->r19, 0X8);
    // 0x801DCF94: lui         $at, 0x4090
    ctx->r1 = S32(0X4090 << 16);
    // 0x801DCF98: mtc1        $at, $f10
    ctx->f10.u32l = ctx->r1;
    // 0x801DCF9C: addiu       $t1, $t0, -0x96
    ctx->r9 = ADD32(ctx->r8, -0X96);
    // 0x801DCFA0: mtc1        $t1, $f8
    ctx->f8.u32l = ctx->r9;
    // 0x801DCFA4: lui         $at, 0x4140
    ctx->r1 = S32(0X4140 << 16);
    // 0x801DCFA8: cvt.s.w     $f4, $f8
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    ctx->f4.fl = CVT_S_W(ctx->f8.u32l);
    // 0x801DCFAC: mul.s       $f6, $f4, $f10
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f6.fl = MUL_S(ctx->f4.fl, ctx->f10.fl);
    // 0x801DCFB0: nop

    // 0x801DCFB4: mul.s       $f8, $f6, $f16
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f8.fl = MUL_S(ctx->f6.fl, ctx->f16.fl);
    // 0x801DCFB8: div.s       $f4, $f8, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f4.fl = DIV_S(ctx->f8.fl, ctx->f18.fl);
    // 0x801DCFBC: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x801DCFC0: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801DCFC4: trunc.w.s   $f10, $f4
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    ctx->f10.u32l = TRUNC_W_S(ctx->f4.fl);
    // 0x801DCFC8: mfc1        $t3, $f10
    ctx->r11 = (int32_t)ctx->f10.u32l;
    // 0x801DCFCC: lwc1        $f10, -0x784C($at)
    ctx->f10.u32l = MEM_W(ctx->r1, -0X784C);
    // 0x801DCFD0: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801DCFD4: andi        $t4, $t3, 0xFFF
    ctx->r12 = ctx->r11 & 0XFFF;
    // 0x801DCFD8: sll         $t5, $t4, 2
    ctx->r13 = S32(ctx->r12 << 2);
    // 0x801DCFDC: addu        $t6, $v0, $t5
    ctx->r14 = ADD32(ctx->r2, ctx->r13);
    // 0x801DCFE0: lwc1        $f6, 0x0($t6)
    ctx->f6.u32l = MEM_W(ctx->r14, 0X0);
    // 0x801DCFE4: mul.s       $f4, $f6, $f8
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f4.fl = MUL_S(ctx->f6.fl, ctx->f8.fl);
    // 0x801DCFE8: sub.s       $f6, $f10, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = ctx->f10.fl - ctx->f4.fl;
    // 0x801DCFEC: swc1        $f6, -0x7E60($at)
    MEM_W(-0X7E60, ctx->r1) = ctx->f6.u32l;
    // 0x801DCFF0: lw          $t7, 0x8($s3)
    ctx->r15 = MEM_W(ctx->r19, 0X8);
    // 0x801DCFF4: lui         $at, 0x40F0
    ctx->r1 = S32(0X40F0 << 16);
    // 0x801DCFF8: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x801DCFFC: addiu       $t8, $t7, -0x96
    ctx->r24 = ADD32(ctx->r15, -0X96);
    // 0x801DD000: mtc1        $t8, $f8
    ctx->f8.u32l = ctx->r24;
    // 0x801DD004: lui         $at, 0x41C8
    ctx->r1 = S32(0X41C8 << 16);
    // 0x801DD008: cvt.s.w     $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.fl = CVT_S_W(ctx->f8.u32l);
    // 0x801DD00C: mul.s       $f6, $f10, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = MUL_S(ctx->f10.fl, ctx->f4.fl);
    // 0x801DD010: nop

    // 0x801DD014: mul.s       $f8, $f6, $f16
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f8.fl = MUL_S(ctx->f6.fl, ctx->f16.fl);
    // 0x801DD018: div.s       $f10, $f8, $f18
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f10.fl = DIV_S(ctx->f8.fl, ctx->f18.fl);
    // 0x801DD01C: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x801DD020: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801DD024: trunc.w.s   $f4, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    ctx->f4.u32l = TRUNC_W_S(ctx->f10.fl);
    // 0x801DD028: mfc1        $t0, $f4
    ctx->r8 = (int32_t)ctx->f4.u32l;
    // 0x801DD02C: lwc1        $f4, -0x7848($at)
    ctx->f4.u32l = MEM_W(ctx->r1, -0X7848);
    // 0x801DD030: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801DD034: andi        $t1, $t0, 0xFFF
    ctx->r9 = ctx->r8 & 0XFFF;
    // 0x801DD038: sll         $t2, $t1, 2
    ctx->r10 = S32(ctx->r9 << 2);
    // 0x801DD03C: addu        $t3, $v0, $t2
    ctx->r11 = ADD32(ctx->r2, ctx->r10);
    // 0x801DD040: lwc1        $f6, 0x0($t3)
    ctx->f6.u32l = MEM_W(ctx->r11, 0X0);
    // 0x801DD044: mul.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = MUL_S(ctx->f6.fl, ctx->f8.fl);
    // 0x801DD048: sub.s       $f6, $f4, $f10
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f6.fl = ctx->f4.fl - ctx->f10.fl;
    // 0x801DD04C: swc1        $f6, -0x7E5C($at)
    MEM_W(-0X7E5C, ctx->r1) = ctx->f6.u32l;
    // 0x801DD050: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801DD054: lwc1        $f8, -0x7EE0($at)
    ctx->f8.u32l = MEM_W(ctx->r1, -0X7EE0);
    // 0x801DD058: mul.s       $f4, $f8, $f16
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f4.fl = MUL_S(ctx->f8.fl, ctx->f16.fl);
    // 0x801DD05C: div.s       $f10, $f4, $f18
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f10.fl = DIV_S(ctx->f4.fl, ctx->f18.fl);
    // 0x801DD060: trunc.w.s   $f6, $f10
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    ctx->f6.u32l = TRUNC_W_S(ctx->f10.fl);
    // 0x801DD064: mfc1        $v1, $f6
    ctx->r3 = (int32_t)ctx->f6.u32l;
    // 0x801DD068: nop

    // 0x801DD06C: addiu       $t5, $v1, 0x400
    ctx->r13 = ADD32(ctx->r3, 0X400);
    // 0x801DD070: andi        $t6, $t5, 0xFFF
    ctx->r14 = ctx->r13 & 0XFFF;
    // 0x801DD074: sll         $t7, $t6, 2
    ctx->r15 = S32(ctx->r14 << 2);
    // 0x801DD078: addu        $t8, $v0, $t7
    ctx->r24 = ADD32(ctx->r2, ctx->r15);
    // 0x801DD07C: lwc1        $f8, 0x0($t8)
    ctx->f8.u32l = MEM_W(ctx->r24, 0X0);
    // 0x801DD080: andi        $t3, $v1, 0xFFF
    ctx->r11 = ctx->r3 & 0XFFF;
    // 0x801DD084: sll         $t4, $t3, 2
    ctx->r12 = S32(ctx->r11 << 2);
    // 0x801DD088: swc1        $f8, 0x0($s0)
    MEM_W(0X0, ctx->r16) = ctx->f8.u32l;
    // 0x801DD08C: lw          $t0, 0x4($s3)
    ctx->r8 = MEM_W(ctx->r19, 0X4);
    // 0x801DD090: lw          $t9, 0x8($s3)
    ctx->r25 = MEM_W(ctx->r19, 0X8);
    // 0x801DD094: lwc1        $f2, 0x0($s0)
    ctx->f2.u32l = MEM_W(ctx->r16, 0X0);
    // 0x801DD098: lw          $t1, 0x0($t0)
    ctx->r9 = MEM_W(ctx->r8, 0X0);
    // 0x801DD09C: addu        $t5, $v0, $t4
    ctx->r13 = ADD32(ctx->r2, ctx->r12);
    // 0x801DD0A0: div         $zero, $t9, $t1
    lo = S32(S64(S32(ctx->r25)) / S64(S32(ctx->r9))); hi = S32(S64(S32(ctx->r25)) % S64(S32(ctx->r9)));
    // 0x801DD0A4: mflo        $t2
    ctx->r10 = lo;
    // 0x801DD0A8: mtc1        $t2, $f4
    ctx->f4.u32l = ctx->r10;
    // 0x801DD0AC: bne         $t1, $zero, L_801DD0B8
    if (ctx->r9 != 0) {
        // 0x801DD0B0: nop
    
            goto L_801DD0B8;
    }
    // 0x801DD0B0: nop

    // 0x801DD0B4: break       7
    do_break(2149437620);
L_801DD0B8:
    // 0x801DD0B8: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x801DD0BC: bne         $t1, $at, L_801DD0D0
    if (ctx->r9 != ctx->r1) {
        // 0x801DD0C0: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_801DD0D0;
    }
    // 0x801DD0C0: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x801DD0C4: bne         $t9, $at, L_801DD0D0
    if (ctx->r25 != ctx->r1) {
        // 0x801DD0C8: nop
    
            goto L_801DD0D0;
    }
    // 0x801DD0C8: nop

    // 0x801DD0CC: break       6
    do_break(2149437644);
L_801DD0D0:
    // 0x801DD0D0: cvt.s.w     $f10, $f4
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    ctx->f10.fl = CVT_S_W(ctx->f4.u32l);
    // 0x801DD0D4: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801DD0D8: lwc1        $f6, 0x5F5C($at)
    ctx->f6.u32l = MEM_W(ctx->r1, 0X5F5C);
    // 0x801DD0DC: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801DD0E0: lwc1        $f4, 0x5F60($at)
    ctx->f4.u32l = MEM_W(ctx->r1, 0X5F60);
    // 0x801DD0E4: mul.s       $f8, $f10, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = MUL_S(ctx->f10.fl, ctx->f6.fl);
    // 0x801DD0E8: lwc1        $f6, 0x0($t5)
    ctx->f6.u32l = MEM_W(ctx->r13, 0X0);
    // 0x801DD0EC: swc1        $f6, 0x8($s0)
    MEM_W(0X8, ctx->r16) = ctx->f6.u32l;
    // 0x801DD0F0: lwc1        $f0, 0x8($s0)
    ctx->f0.u32l = MEM_W(ctx->r16, 0X8);
    // 0x801DD0F4: add.s       $f10, $f8, $f4
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f10.fl = ctx->f8.fl + ctx->f4.fl;
    // 0x801DD0F8: mul.s       $f8, $f2, $f2
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f8.fl = MUL_S(ctx->f2.fl, ctx->f2.fl);
    // 0x801DD0FC: swc1        $f10, 0x4($s0)
    MEM_W(0X4, ctx->r16) = ctx->f10.u32l;
    // 0x801DD100: lwc1        $f14, 0x4($s0)
    ctx->f14.u32l = MEM_W(ctx->r16, 0X4);
    // 0x801DD104: mul.s       $f4, $f14, $f14
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f4.fl = MUL_S(ctx->f14.fl, ctx->f14.fl);
    // 0x801DD108: add.s       $f10, $f8, $f4
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f10.fl = ctx->f8.fl + ctx->f4.fl;
    // 0x801DD10C: mul.s       $f6, $f0, $f0
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f6.fl = MUL_S(ctx->f0.fl, ctx->f0.fl);
    // 0x801DD110: jal         0x800C7010
    // 0x801DD114: add.s       $f12, $f6, $f10
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f12.fl = ctx->f6.fl + ctx->f10.fl;
    _nsqrtf(rdram, ctx);
        goto after_4;
    // 0x801DD114: add.s       $f12, $f6, $f10
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f12.fl = ctx->f6.fl + ctx->f10.fl;
    after_4:
    // 0x801DD118: lui         $v1, 0x8023
    ctx->r3 = S32(0X8023 << 16);
    // 0x801DD11C: lui         $v0, 0x8023
    ctx->r2 = S32(0X8023 << 16);
    // 0x801DD120: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801DD124: lui         $a0, 0x8023
    ctx->r4 = S32(0X8023 << 16);
    // 0x801DD128: addiu       $a0, $a0, -0x7E64
    ctx->r4 = ADD32(ctx->r4, -0X7E64);
    // 0x801DD12C: swc1        $f0, -0x7824($at)
    MEM_W(-0X7824, ctx->r1) = ctx->f0.u32l;
    // 0x801DD130: addiu       $v0, $v0, -0x7E70
    ctx->r2 = ADD32(ctx->r2, -0X7E70);
    // 0x801DD134: addiu       $v1, $v1, -0x7830
    ctx->r3 = ADD32(ctx->r3, -0X7830);
    // 0x801DD138: addiu       $v0, $v0, 0x4
    ctx->r2 = ADD32(ctx->r2, 0X4);
    // 0x801DD13C: sltu        $at, $v0, $a0
    ctx->r1 = ctx->r2 < ctx->r4 ? 1 : 0;
    // 0x801DD140: beq         $at, $zero, L_801DD164
    if (ctx->r1 == 0) {
        // 0x801DD144: lwc1        $f22, 0x0($v1)
        ctx->f22.u32l = MEM_W(ctx->r3, 0X0);
            goto L_801DD164;
    }
    // 0x801DD144: lwc1        $f22, 0x0($v1)
    ctx->f22.u32l = MEM_W(ctx->r3, 0X0);
L_801DD148:
    // 0x801DD148: div.s       $f20, $f22, $f0
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f20.fl = DIV_S(ctx->f22.fl, ctx->f0.fl);
    // 0x801DD14C: lwc1        $f22, 0x4($v1)
    ctx->f22.u32l = MEM_W(ctx->r3, 0X4);
    // 0x801DD150: addiu       $v0, $v0, 0x4
    ctx->r2 = ADD32(ctx->r2, 0X4);
    // 0x801DD154: sltu        $at, $v0, $a0
    ctx->r1 = ctx->r2 < ctx->r4 ? 1 : 0;
    // 0x801DD158: addiu       $v1, $v1, 0x4
    ctx->r3 = ADD32(ctx->r3, 0X4);
    // 0x801DD15C: bne         $at, $zero, L_801DD148
    if (ctx->r1 != 0) {
        // 0x801DD160: swc1        $f20, 0x10($v0)
        MEM_W(0X10, ctx->r2) = ctx->f20.u32l;
            goto L_801DD148;
    }
    // 0x801DD160: swc1        $f20, 0x10($v0)
    MEM_W(0X10, ctx->r2) = ctx->f20.u32l;
L_801DD164:
    // 0x801DD164: div.s       $f20, $f22, $f0
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f20.fl = DIV_S(ctx->f22.fl, ctx->f0.fl);
    // 0x801DD168: addiu       $v1, $v1, 0x4
    ctx->r3 = ADD32(ctx->r3, 0X4);
    // 0x801DD16C: swc1        $f20, 0x14($v0)
    MEM_W(0X14, ctx->r2) = ctx->f20.u32l;
    // 0x801DD170: lw          $t6, 0x4($s3)
    ctx->r14 = MEM_W(ctx->r19, 0X4);
    // 0x801DD174: lui         $at, 0x4320
    ctx->r1 = S32(0X4320 << 16);
    // 0x801DD178: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x801DD17C: lw          $t7, 0x0($t6)
    ctx->r15 = MEM_W(ctx->r14, 0X0);
    // 0x801DD180: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801DD184: mtc1        $t7, $f10
    ctx->f10.u32l = ctx->r15;
    // 0x801DD188: nop

    // 0x801DD18C: cvt.s.w     $f8, $f10
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    ctx->f8.fl = CVT_S_W(ctx->f10.u32l);
    // 0x801DD190: lwc1        $f10, -0x7EE0($at)
    ctx->f10.u32l = MEM_W(ctx->r1, -0X7EE0);
    // 0x801DD194: div.s       $f4, $f6, $f8
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f4.fl = DIV_S(ctx->f6.fl, ctx->f8.fl);
    // 0x801DD198: add.s       $f6, $f10, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = ctx->f10.fl + ctx->f4.fl;
    // 0x801DD19C: swc1        $f6, -0x7EE0($at)
    MEM_W(-0X7EE0, ctx->r1) = ctx->f6.u32l;
    // 0x801DD1A0: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801DD1A4: lwc1        $f8, -0x7850($at)
    ctx->f8.u32l = MEM_W(ctx->r1, -0X7850);
    // 0x801DD1A8: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801DD1AC: lwc1        $f10, -0x7E64($at)
    ctx->f10.u32l = MEM_W(ctx->r1, -0X7E64);
    // 0x801DD1B0: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801DD1B4: sub.s       $f4, $f8, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f4.fl = ctx->f8.fl - ctx->f10.fl;
    // 0x801DD1B8: jal         0x80047E50
    // 0x801DD1BC: swc1        $f4, -0x7830($at)
    MEM_W(-0X7830, ctx->r1) = ctx->f4.u32l;
    SysUtils_Rand(rdram, ctx);
        goto after_5;
    // 0x801DD1BC: swc1        $f4, -0x7830($at)
    MEM_W(-0X7830, ctx->r1) = ctx->f4.u32l;
    after_5:
    // 0x801DD1C0: andi        $t8, $v0, 0x1F
    ctx->r24 = ctx->r2 & 0X1F;
    // 0x801DD1C4: mtc1        $t8, $f6
    ctx->f6.u32l = ctx->r24;
    // 0x801DD1C8: lui         $at, 0x4F80
    ctx->r1 = S32(0X4F80 << 16);
    // 0x801DD1CC: bgez        $t8, L_801DD1E0
    if (SIGNED(ctx->r24) >= 0) {
        // 0x801DD1D0: cvt.s.w     $f8, $f6
        CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    ctx->f8.fl = CVT_S_W(ctx->f6.u32l);
            goto L_801DD1E0;
    }
    // 0x801DD1D0: cvt.s.w     $f8, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    ctx->f8.fl = CVT_S_W(ctx->f6.u32l);
    // 0x801DD1D4: mtc1        $at, $f10
    ctx->f10.u32l = ctx->r1;
    // 0x801DD1D8: nop

    // 0x801DD1DC: add.s       $f8, $f8, $f10
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f8.fl = ctx->f8.fl + ctx->f10.fl;
L_801DD1E0:
    // 0x801DD1E0: lui         $at, 0x4416
    ctx->r1 = S32(0X4416 << 16);
    // 0x801DD1E4: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x801DD1E8: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801DD1EC: add.s       $f6, $f8, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = ctx->f8.fl + ctx->f4.fl;
    // 0x801DD1F0: swc1        $f6, 0x4($s0)
    MEM_W(0X4, ctx->r16) = ctx->f6.u32l;
    // 0x801DD1F4: lwc1        $f10, -0x7848($at)
    ctx->f10.u32l = MEM_W(ctx->r1, -0X7848);
    // 0x801DD1F8: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801DD1FC: lwc1        $f8, -0x7E5C($at)
    ctx->f8.u32l = MEM_W(ctx->r1, -0X7E5C);
    // 0x801DD200: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801DD204: sub.s       $f4, $f10, $f8
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f4.fl = ctx->f10.fl - ctx->f8.fl;
    // 0x801DD208: swc1        $f4, -0x7828($at)
    MEM_W(-0X7828, ctx->r1) = ctx->f4.u32l;
    // 0x801DD20C: lwc1        $f2, 0x0($s0)
    ctx->f2.u32l = MEM_W(ctx->r16, 0X0);
    // 0x801DD210: lwc1        $f14, 0x4($s0)
    ctx->f14.u32l = MEM_W(ctx->r16, 0X4);
    // 0x801DD214: lwc1        $f0, 0x8($s0)
    ctx->f0.u32l = MEM_W(ctx->r16, 0X8);
    // 0x801DD218: mul.s       $f6, $f2, $f2
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f6.fl = MUL_S(ctx->f2.fl, ctx->f2.fl);
    // 0x801DD21C: nop

    // 0x801DD220: mul.s       $f10, $f14, $f14
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f10.fl = MUL_S(ctx->f14.fl, ctx->f14.fl);
    // 0x801DD224: add.s       $f8, $f6, $f10
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f8.fl = ctx->f6.fl + ctx->f10.fl;
    // 0x801DD228: mul.s       $f4, $f0, $f0
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f4.fl = MUL_S(ctx->f0.fl, ctx->f0.fl);
    // 0x801DD22C: jal         0x800C7010
    // 0x801DD230: add.s       $f12, $f4, $f8
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f12.fl = ctx->f4.fl + ctx->f8.fl;
    _nsqrtf(rdram, ctx);
        goto after_6;
    // 0x801DD230: add.s       $f12, $f4, $f8
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f12.fl = ctx->f4.fl + ctx->f8.fl;
    after_6:
    // 0x801DD234: lui         $v1, 0x8023
    ctx->r3 = S32(0X8023 << 16);
    // 0x801DD238: lui         $v0, 0x8023
    ctx->r2 = S32(0X8023 << 16);
    // 0x801DD23C: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801DD240: lui         $a0, 0x8023
    ctx->r4 = S32(0X8023 << 16);
    // 0x801DD244: addiu       $a0, $a0, -0x7E64
    ctx->r4 = ADD32(ctx->r4, -0X7E64);
    // 0x801DD248: swc1        $f0, -0x7824($at)
    MEM_W(-0X7824, ctx->r1) = ctx->f0.u32l;
    // 0x801DD24C: addiu       $v0, $v0, -0x7E70
    ctx->r2 = ADD32(ctx->r2, -0X7E70);
    // 0x801DD250: addiu       $v1, $v1, -0x7830
    ctx->r3 = ADD32(ctx->r3, -0X7830);
    // 0x801DD254: addiu       $v0, $v0, 0x4
    ctx->r2 = ADD32(ctx->r2, 0X4);
    // 0x801DD258: beq         $v0, $a0, L_801DD278
    if (ctx->r2 == ctx->r4) {
        // 0x801DD25C: lwc1        $f22, 0x0($v1)
        ctx->f22.u32l = MEM_W(ctx->r3, 0X0);
            goto L_801DD278;
    }
    // 0x801DD25C: lwc1        $f22, 0x0($v1)
    ctx->f22.u32l = MEM_W(ctx->r3, 0X0);
L_801DD260:
    // 0x801DD260: div.s       $f20, $f22, $f0
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f20.fl = DIV_S(ctx->f22.fl, ctx->f0.fl);
    // 0x801DD264: lwc1        $f22, 0x4($v1)
    ctx->f22.u32l = MEM_W(ctx->r3, 0X4);
    // 0x801DD268: addiu       $v0, $v0, 0x4
    ctx->r2 = ADD32(ctx->r2, 0X4);
    // 0x801DD26C: addiu       $v1, $v1, 0x4
    ctx->r3 = ADD32(ctx->r3, 0X4);
    // 0x801DD270: bne         $v0, $a0, L_801DD260
    if (ctx->r2 != ctx->r4) {
        // 0x801DD274: swc1        $f20, 0x1C($v0)
        MEM_W(0X1C, ctx->r2) = ctx->f20.u32l;
            goto L_801DD260;
    }
    // 0x801DD274: swc1        $f20, 0x1C($v0)
    MEM_W(0X1C, ctx->r2) = ctx->f20.u32l;
L_801DD278:
    // 0x801DD278: div.s       $f20, $f22, $f0
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f20.fl = DIV_S(ctx->f22.fl, ctx->f0.fl);
    // 0x801DD27C: addiu       $v1, $v1, 0x4
    ctx->r3 = ADD32(ctx->r3, 0X4);
    // 0x801DD280: swc1        $f20, 0x20($v0)
    MEM_W(0X20, ctx->r2) = ctx->f20.u32l;
    // 0x801DD284: lui         $t0, 0x8023
    ctx->r8 = S32(0X8023 << 16);
    // 0x801DD288: lw          $t0, -0x7E68($t0)
    ctx->r8 = MEM_W(ctx->r8, -0X7E68);
    // 0x801DD28C: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801DD290: addiu       $t9, $t0, 0x1
    ctx->r25 = ADD32(ctx->r8, 0X1);
    // 0x801DD294: bgez        $t9, L_801DD2A8
    if (SIGNED(ctx->r25) >= 0) {
        // 0x801DD298: andi        $t1, $t9, 0x1
        ctx->r9 = ctx->r25 & 0X1;
            goto L_801DD2A8;
    }
    // 0x801DD298: andi        $t1, $t9, 0x1
    ctx->r9 = ctx->r25 & 0X1;
    // 0x801DD29C: beq         $t1, $zero, L_801DD2A8
    if (ctx->r9 == 0) {
        // 0x801DD2A0: nop
    
            goto L_801DD2A8;
    }
    // 0x801DD2A0: nop

    // 0x801DD2A4: addiu       $t1, $t1, -0x2
    ctx->r9 = ADD32(ctx->r9, -0X2);
L_801DD2A8:
    // 0x801DD2A8: sw          $t1, -0x7E68($at)
    MEM_W(-0X7E68, ctx->r1) = ctx->r9;
L_801DD2AC:
    // 0x801DD2AC: lw          $ra, 0x34($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X34);
    // 0x801DD2B0: ldc1        $f20, 0x10($sp)
    CHECK_FR(ctx, 20);
    ctx->f20.u64 = LD(ctx->r29, 0X10);
    // 0x801DD2B4: ldc1        $f22, 0x18($sp)
    CHECK_FR(ctx, 22);
    ctx->f22.u64 = LD(ctx->r29, 0X18);
    // 0x801DD2B8: lw          $s0, 0x24($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X24);
    // 0x801DD2BC: lw          $s1, 0x28($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X28);
    // 0x801DD2C0: lw          $s2, 0x2C($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X2C);
    // 0x801DD2C4: lw          $s3, 0x30($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X30);
    // 0x801DD2C8: jr          $ra
    // 0x801DD2CC: addiu       $sp, $sp, 0x38
    ctx->r29 = ADD32(ctx->r29, 0X38);
    return;
    // 0x801DD2CC: addiu       $sp, $sp, 0x38
    ctx->r29 = ADD32(ctx->r29, 0X38);
;}
RECOMP_FUNC void func_801DD2D0(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801DD2D0: addiu       $sp, $sp, -0x128
    ctx->r29 = ADD32(ctx->r29, -0X128);
    // 0x801DD2D4: lui         $t7, 0x8022
    ctx->r15 = S32(0X8022 << 16);
    // 0x801DD2D8: addiu       $t7, $t7, 0x5E68
    ctx->r15 = ADD32(ctx->r15, 0X5E68);
    // 0x801DD2DC: sw          $ra, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r31;
    // 0x801DD2E0: sw          $fp, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r30;
    // 0x801DD2E4: sw          $s7, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r23;
    // 0x801DD2E8: sw          $s6, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r22;
    // 0x801DD2EC: sw          $s5, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r21;
    // 0x801DD2F0: sw          $s4, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r20;
    // 0x801DD2F4: sw          $s3, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r19;
    // 0x801DD2F8: sw          $s2, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r18;
    // 0x801DD2FC: sw          $s1, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r17;
    // 0x801DD300: sw          $s0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r16;
    // 0x801DD304: sdc1        $f20, 0x18($sp)
    CHECK_FR(ctx, 20);
    SD(ctx->f20.u64, 0X18, ctx->r29);
    // 0x801DD308: addiu       $t1, $t7, 0x30
    ctx->r9 = ADD32(ctx->r15, 0X30);
    // 0x801DD30C: addiu       $t6, $sp, 0xDC
    ctx->r14 = ADD32(ctx->r29, 0XDC);
L_801DD310:
    // 0x801DD310: lw          $at, 0x0($t7)
    ctx->r1 = MEM_W(ctx->r15, 0X0);
    // 0x801DD314: addiu       $t7, $t7, 0xC
    ctx->r15 = ADD32(ctx->r15, 0XC);
    // 0x801DD318: addiu       $t6, $t6, 0xC
    ctx->r14 = ADD32(ctx->r14, 0XC);
    // 0x801DD31C: sw          $at, -0xC($t6)
    MEM_W(-0XC, ctx->r14) = ctx->r1;
    // 0x801DD320: lw          $at, -0x8($t7)
    ctx->r1 = MEM_W(ctx->r15, -0X8);
    // 0x801DD324: sw          $at, -0x8($t6)
    MEM_W(-0X8, ctx->r14) = ctx->r1;
    // 0x801DD328: lw          $at, -0x4($t7)
    ctx->r1 = MEM_W(ctx->r15, -0X4);
    // 0x801DD32C: bne         $t7, $t1, L_801DD310
    if (ctx->r15 != ctx->r9) {
        // 0x801DD330: sw          $at, -0x4($t6)
        MEM_W(-0X4, ctx->r14) = ctx->r1;
            goto L_801DD310;
    }
    // 0x801DD330: sw          $at, -0x4($t6)
    MEM_W(-0X4, ctx->r14) = ctx->r1;
    // 0x801DD334: lui         $t3, 0x8022
    ctx->r11 = S32(0X8022 << 16);
    // 0x801DD338: addiu       $t3, $t3, 0x5E98
    ctx->r11 = ADD32(ctx->r11, 0X5E98);
    // 0x801DD33C: addiu       $t9, $t3, 0x78
    ctx->r25 = ADD32(ctx->r11, 0X78);
    // 0x801DD340: addiu       $t2, $sp, 0x64
    ctx->r10 = ADD32(ctx->r29, 0X64);
L_801DD344:
    // 0x801DD344: lw          $at, 0x0($t3)
    ctx->r1 = MEM_W(ctx->r11, 0X0);
    // 0x801DD348: addiu       $t3, $t3, 0xC
    ctx->r11 = ADD32(ctx->r11, 0XC);
    // 0x801DD34C: addiu       $t2, $t2, 0xC
    ctx->r10 = ADD32(ctx->r10, 0XC);
    // 0x801DD350: sw          $at, -0xC($t2)
    MEM_W(-0XC, ctx->r10) = ctx->r1;
    // 0x801DD354: lw          $at, -0x8($t3)
    ctx->r1 = MEM_W(ctx->r11, -0X8);
    // 0x801DD358: sw          $at, -0x8($t2)
    MEM_W(-0X8, ctx->r10) = ctx->r1;
    // 0x801DD35C: lw          $at, -0x4($t3)
    ctx->r1 = MEM_W(ctx->r11, -0X4);
    // 0x801DD360: bne         $t3, $t9, L_801DD344
    if (ctx->r11 != ctx->r25) {
        // 0x801DD364: sw          $at, -0x4($t2)
        MEM_W(-0X4, ctx->r10) = ctx->r1;
            goto L_801DD344;
    }
    // 0x801DD364: sw          $at, -0x4($t2)
    MEM_W(-0X4, ctx->r10) = ctx->r1;
    // 0x801DD368: lw          $t8, 0x4($a0)
    ctx->r24 = MEM_W(ctx->r4, 0X4);
    // 0x801DD36C: lui         $t1, 0x8022
    ctx->r9 = S32(0X8022 << 16);
    // 0x801DD370: addiu       $t1, $t1, 0x45B4
    ctx->r9 = ADD32(ctx->r9, 0X45B4);
    // 0x801DD374: addiu       $at, $zero, 0xC
    ctx->r1 = ADD32(0, 0XC);
    // 0x801DD378: subu        $v0, $t8, $t1
    ctx->r2 = SUB32(ctx->r24, ctx->r9);
    // 0x801DD37C: div         $zero, $v0, $at
    lo = S32(S64(S32(ctx->r2)) / S64(S32(ctx->r1))); hi = S32(S64(S32(ctx->r2)) % S64(S32(ctx->r1)));
    // 0x801DD380: mflo        $t7
    ctx->r15 = lo;
    // 0x801DD384: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x801DD388: bne         $t7, $at, L_801DD680
    if (ctx->r15 != ctx->r1) {
        // 0x801DD38C: addiu       $t6, $zero, 0x10
        ctx->r14 = ADD32(0, 0X10);
            goto L_801DD680;
    }
    // 0x801DD38C: addiu       $t6, $zero, 0x10
    ctx->r14 = ADD32(0, 0X10);
    // 0x801DD390: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801DD394: sw          $t6, -0x7858($at)
    MEM_W(-0X7858, ctx->r1) = ctx->r14;
    // 0x801DD398: lw          $t5, 0x8($a0)
    ctx->r13 = MEM_W(ctx->r4, 0X8);
    // 0x801DD39C: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x801DD3A0: bnel        $t5, $at, L_801DD4B0
    if (ctx->r13 != ctx->r1) {
        // 0x801DD3A4: lui         $at, 0x4140
        ctx->r1 = S32(0X4140 << 16);
            goto L_801DD4B0;
    }
    goto skip_0;
    // 0x801DD3A4: lui         $at, 0x4140
    ctx->r1 = S32(0X4140 << 16);
    skip_0:
    // 0x801DD3A8: jal         0x800AB92C
    // 0x801DD3AC: nop

    func_800AB92C(rdram, ctx);
        goto after_0;
    // 0x801DD3AC: nop

    after_0:
    // 0x801DD3B0: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801DD3B4: lwc1        $f12, 0x5F64($at)
    ctx->f12.u32l = MEM_W(ctx->r1, 0X5F64);
    // 0x801DD3B8: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x801DD3BC: lui         $s2, 0x8023
    ctx->r18 = S32(0X8023 << 16);
    // 0x801DD3C0: lui         $s5, 0x8023
    ctx->r21 = S32(0X8023 << 16);
    // 0x801DD3C4: lui         $a3, 0x8023
    ctx->r7 = S32(0X8023 << 16);
    // 0x801DD3C8: lui         $a1, 0x8023
    ctx->r5 = S32(0X8023 << 16);
    // 0x801DD3CC: mtc1        $at, $f2
    ctx->f2.u32l = ctx->r1;
    // 0x801DD3D0: mtc1        $zero, $f0
    ctx->f0.u32l = 0;
    // 0x801DD3D4: addiu       $a1, $a1, -0x7EF0
    ctx->r5 = ADD32(ctx->r5, -0X7EF0);
    // 0x801DD3D8: addiu       $a3, $a3, -0x7EE8
    ctx->r7 = ADD32(ctx->r7, -0X7EE8);
    // 0x801DD3DC: addiu       $s5, $s5, -0x7EF0
    ctx->r21 = ADD32(ctx->r21, -0X7EF0);
    // 0x801DD3E0: addiu       $s2, $s2, -0x7E70
    ctx->r18 = ADD32(ctx->r18, -0X7E70);
    // 0x801DD3E4: addiu       $s6, $sp, 0xDC
    ctx->r22 = ADD32(ctx->r29, 0XDC);
    // 0x801DD3E8: ori         $t0, $zero, 0xFFFF
    ctx->r8 = 0 | 0XFFFF;
    // 0x801DD3EC: addiu       $a2, $zero, 0x6
    ctx->r6 = ADD32(0, 0X6);
    // 0x801DD3F0: addiu       $a0, $zero, 0x3
    ctx->r4 = ADD32(0, 0X3);
L_801DD3F4:
    // 0x801DD3F4: sw          $a0, 0x0($s2)
    MEM_W(0X0, ctx->r18) = ctx->r4;
    // 0x801DD3F8: sw          $zero, 0x4($s2)
    MEM_W(0X4, ctx->r18) = 0;
    // 0x801DD3FC: sw          $zero, 0x8($s2)
    MEM_W(0X8, ctx->r18) = 0;
    // 0x801DD400: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
    // 0x801DD404: or          $v0, $s2, $zero
    ctx->r2 = ctx->r18 | 0;
    // 0x801DD408: or          $s1, $s6, $zero
    ctx->r17 = ctx->r22 | 0;
L_801DD40C:
    // 0x801DD40C: lwc1        $f4, 0x0($s1)
    ctx->f4.u32l = MEM_W(ctx->r17, 0X0);
    // 0x801DD410: addiu       $v1, $v1, 0x1
    ctx->r3 = ADD32(ctx->r3, 0X1);
    // 0x801DD414: addiu       $v0, $v0, 0x4
    ctx->r2 = ADD32(ctx->r2, 0X4);
    // 0x801DD418: addiu       $s1, $s1, 0x4
    ctx->r17 = ADD32(ctx->r17, 0X4);
    // 0x801DD41C: bne         $v1, $a0, L_801DD40C
    if (ctx->r3 != ctx->r4) {
        // 0x801DD420: swc1        $f4, 0x8($v0)
        MEM_W(0X8, ctx->r2) = ctx->f4.u32l;
            goto L_801DD40C;
    }
    // 0x801DD420: swc1        $f4, 0x8($v0)
    MEM_W(0X8, ctx->r2) = ctx->f4.u32l;
    // 0x801DD424: swc1        $f0, 0x24($s2)
    MEM_W(0X24, ctx->r18) = ctx->f0.u32l;
    // 0x801DD428: swc1        $f2, 0x28($s2)
    MEM_W(0X28, ctx->r18) = ctx->f2.u32l;
    // 0x801DD42C: swc1        $f0, 0x2C($s2)
    MEM_W(0X2C, ctx->r18) = ctx->f0.u32l;
    // 0x801DD430: bne         $s5, $a1, L_801DD440
    if (ctx->r21 != ctx->r5) {
        // 0x801DD434: swc1        $f12, 0x30($s2)
        MEM_W(0X30, ctx->r18) = ctx->f12.u32l;
            goto L_801DD440;
    }
    // 0x801DD434: swc1        $f12, 0x30($s2)
    MEM_W(0X30, ctx->r18) = ctx->f12.u32l;
    // 0x801DD438: b           L_801DD444
    // 0x801DD43C: sw          $a2, 0x0($s5)
    MEM_W(0X0, ctx->r21) = ctx->r6;
        goto L_801DD444;
    // 0x801DD43C: sw          $a2, 0x0($s5)
    MEM_W(0X0, ctx->r21) = ctx->r6;
L_801DD440:
    // 0x801DD440: sw          $t0, 0x0($s5)
    MEM_W(0X0, ctx->r21) = ctx->r8;
L_801DD444:
    // 0x801DD444: addiu       $s5, $s5, 0x4
    ctx->r21 = ADD32(ctx->r21, 0X4);
    // 0x801DD448: sltu        $at, $s5, $a3
    ctx->r1 = ctx->r21 < ctx->r7 ? 1 : 0;
    // 0x801DD44C: addiu       $s6, $s6, 0x18
    ctx->r22 = ADD32(ctx->r22, 0X18);
    // 0x801DD450: bne         $at, $zero, L_801DD3F4
    if (ctx->r1 != 0) {
        // 0x801DD454: addiu       $s2, $s2, 0x34
        ctx->r18 = ADD32(ctx->r18, 0X34);
            goto L_801DD3F4;
    }
    // 0x801DD454: addiu       $s2, $s2, 0x34
    ctx->r18 = ADD32(ctx->r18, 0X34);
    // 0x801DD458: lui         $fp, 0x8023
    ctx->r30 = S32(0X8023 << 16);
    // 0x801DD45C: addiu       $fp, $fp, -0x7EE0
    ctx->r30 = ADD32(ctx->r30, -0X7EE0);
    // 0x801DD460: addiu       $s0, $sp, 0x64
    ctx->r16 = ADD32(ctx->r29, 0X64);
    // 0x801DD464: addiu       $s1, $sp, 0x6C
    ctx->r17 = ADD32(ctx->r29, 0X6C);
    // 0x801DD468: addiu       $s7, $zero, 0x34
    ctx->r23 = ADD32(0, 0X34);
    // 0x801DD46C: addiu       $s2, $sp, 0xE4
    ctx->r18 = ADD32(ctx->r29, 0XE4);
L_801DD470:
    // 0x801DD470: lw          $v0, 0x0($s0)
    ctx->r2 = MEM_W(ctx->r16, 0X0);
    // 0x801DD474: lw          $t3, 0x4($s0)
    ctx->r11 = MEM_W(ctx->r16, 0X4);
    // 0x801DD478: lui         $t9, 0x8023
    ctx->r25 = S32(0X8023 << 16);
    // 0x801DD47C: multu       $v0, $s7
    result = U64(U32(ctx->r2)) * U64(U32(ctx->r23)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x801DD480: addiu       $t9, $t9, -0x7E70
    ctx->r25 = ADD32(ctx->r25, -0X7E70);
    // 0x801DD484: or          $a1, $s1, $zero
    ctx->r5 = ctx->r17 | 0;
    // 0x801DD488: or          $a2, $fp, $zero
    ctx->r6 = ctx->r30 | 0;
    // 0x801DD48C: subu        $a3, $t3, $v0
    ctx->r7 = SUB32(ctx->r11, ctx->r2);
    // 0x801DD490: mflo        $t4
    ctx->r12 = lo;
    // 0x801DD494: addu        $a0, $t4, $t9
    ctx->r4 = ADD32(ctx->r12, ctx->r25);
    // 0x801DD498: jal         0x801DB284
    // 0x801DD49C: nop

    func_801DB284(rdram, ctx);
        goto after_1;
    // 0x801DD49C: nop

    after_1:
    // 0x801DD4A0: addiu       $s1, $s1, 0x3C
    ctx->r17 = ADD32(ctx->r17, 0X3C);
    // 0x801DD4A4: bne         $s1, $s2, L_801DD470
    if (ctx->r17 != ctx->r18) {
        // 0x801DD4A8: addiu       $s0, $s0, 0x3C
        ctx->r16 = ADD32(ctx->r16, 0X3C);
            goto L_801DD470;
    }
    // 0x801DD4A8: addiu       $s0, $s0, 0x3C
    ctx->r16 = ADD32(ctx->r16, 0X3C);
    // 0x801DD4AC: lui         $at, 0x4140
    ctx->r1 = S32(0X4140 << 16);
L_801DD4B0:
    // 0x801DD4B0: lui         $fp, 0x8023
    ctx->r30 = S32(0X8023 << 16);
    // 0x801DD4B4: lui         $s2, 0x8023
    ctx->r18 = S32(0X8023 << 16);
    // 0x801DD4B8: lui         $s5, 0x8023
    ctx->r21 = S32(0X8023 << 16);
    // 0x801DD4BC: addiu       $s3, $sp, 0x124
    ctx->r19 = ADD32(ctx->r29, 0X124);
    // 0x801DD4C0: mtc1        $at, $f20
    ctx->f20.u32l = ctx->r1;
    // 0x801DD4C4: addiu       $fp, $fp, -0x7EE0
    ctx->r30 = ADD32(ctx->r30, -0X7EE0);
    // 0x801DD4C8: addiu       $s7, $zero, 0x34
    ctx->r23 = ADD32(0, 0X34);
    // 0x801DD4CC: or          $s4, $s3, $zero
    ctx->r20 = ctx->r19 | 0;
    // 0x801DD4D0: addiu       $s5, $s5, -0x7EF0
    ctx->r21 = ADD32(ctx->r21, -0X7EF0);
    // 0x801DD4D4: addiu       $s2, $s2, -0x7E70
    ctx->r18 = ADD32(ctx->r18, -0X7E70);
    // 0x801DD4D8: addiu       $s6, $sp, 0xDC
    ctx->r22 = ADD32(ctx->r29, 0XDC);
L_801DD4DC:
    // 0x801DD4DC: lw          $v0, 0x8($s2)
    ctx->r2 = MEM_W(ctx->r18, 0X8);
    // 0x801DD4E0: addiu       $v1, $zero, 0x1
    ctx->r3 = ADD32(0, 0X1);
    // 0x801DD4E4: or          $s1, $s6, $zero
    ctx->r17 = ctx->r22 | 0;
    // 0x801DD4E8: slti        $at, $v0, 0x10
    ctx->r1 = SIGNED(ctx->r2) < 0X10 ? 1 : 0;
    // 0x801DD4EC: beq         $at, $zero, L_801DD4FC
    if (ctx->r1 == 0) {
        // 0x801DD4F0: addiu       $s0, $sp, 0x118
        ctx->r16 = ADD32(ctx->r29, 0X118);
            goto L_801DD4FC;
    }
    // 0x801DD4F0: addiu       $s0, $sp, 0x118
    ctx->r16 = ADD32(ctx->r29, 0X118);
    // 0x801DD4F4: b           L_801DD4FC
    // 0x801DD4F8: addiu       $v1, $zero, 0x2
    ctx->r3 = ADD32(0, 0X2);
        goto L_801DD4FC;
    // 0x801DD4F8: addiu       $v1, $zero, 0x2
    ctx->r3 = ADD32(0, 0X2);
L_801DD4FC:
    // 0x801DD4FC: addu        $t8, $v0, $v1
    ctx->r24 = ADD32(ctx->r2, ctx->r3);
    // 0x801DD500: sw          $t8, 0x8($s2)
    MEM_W(0X8, ctx->r18) = ctx->r24;
    // 0x801DD504: lw          $t1, 0x0($s5)
    ctx->r9 = MEM_W(ctx->r21, 0X0);
    // 0x801DD508: slti        $at, $t8, 0x10
    ctx->r1 = SIGNED(ctx->r24) < 0X10 ? 1 : 0;
    // 0x801DD50C: blezl       $t1, L_801DD534
    if (SIGNED(ctx->r9) <= 0) {
        // 0x801DD510: lw          $t4, 0x8($s2)
        ctx->r12 = MEM_W(ctx->r18, 0X8);
            goto L_801DD534;
    }
    goto skip_1;
    // 0x801DD510: lw          $t4, 0x8($s2)
    ctx->r12 = MEM_W(ctx->r18, 0X8);
    skip_1:
    // 0x801DD514: bne         $at, $zero, L_801DD548
    if (ctx->r1 != 0) {
        // 0x801DD518: nop
    
            goto L_801DD548;
    }
    // 0x801DD518: nop

    // 0x801DD51C: sw          $zero, 0x8($s2)
    MEM_W(0X8, ctx->r18) = 0;
    // 0x801DD520: lw          $t6, 0x0($s5)
    ctx->r14 = MEM_W(ctx->r21, 0X0);
    // 0x801DD524: addiu       $t5, $t6, -0x1
    ctx->r13 = ADD32(ctx->r14, -0X1);
    // 0x801DD528: b           L_801DD548
    // 0x801DD52C: sw          $t5, 0x0($s5)
    MEM_W(0X0, ctx->r21) = ctx->r13;
        goto L_801DD548;
    // 0x801DD52C: sw          $t5, 0x0($s5)
    MEM_W(0X0, ctx->r21) = ctx->r13;
    // 0x801DD530: lw          $t4, 0x8($s2)
    ctx->r12 = MEM_W(ctx->r18, 0X8);
L_801DD534:
    // 0x801DD534: addiu       $t9, $zero, 0x19
    ctx->r25 = ADD32(0, 0X19);
    // 0x801DD538: slti        $at, $t4, 0x2D
    ctx->r1 = SIGNED(ctx->r12) < 0X2D ? 1 : 0;
    // 0x801DD53C: bne         $at, $zero, L_801DD548
    if (ctx->r1 != 0) {
        // 0x801DD540: nop
    
            goto L_801DD548;
    }
    // 0x801DD540: nop

    // 0x801DD544: sw          $t9, 0x8($s2)
    MEM_W(0X8, ctx->r18) = ctx->r25;
L_801DD548:
    // 0x801DD548: jal         0x80047E50
    // 0x801DD54C: nop

    SysUtils_Rand(rdram, ctx);
        goto after_2;
    // 0x801DD54C: nop

    after_2:
    // 0x801DD550: andi        $t3, $v0, 0x3
    ctx->r11 = ctx->r2 & 0X3;
    // 0x801DD554: mtc1        $t3, $f6
    ctx->f6.u32l = ctx->r11;
    // 0x801DD558: lui         $at, 0x4F80
    ctx->r1 = S32(0X4F80 << 16);
    // 0x801DD55C: bgez        $t3, L_801DD570
    if (SIGNED(ctx->r11) >= 0) {
        // 0x801DD560: cvt.s.w     $f8, $f6
        CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    ctx->f8.fl = CVT_S_W(ctx->f6.u32l);
            goto L_801DD570;
    }
    // 0x801DD560: cvt.s.w     $f8, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    ctx->f8.fl = CVT_S_W(ctx->f6.u32l);
    // 0x801DD564: mtc1        $at, $f10
    ctx->f10.u32l = ctx->r1;
    // 0x801DD568: nop

    // 0x801DD56C: add.s       $f8, $f8, $f10
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f8.fl = ctx->f8.fl + ctx->f10.fl;
L_801DD570:
    // 0x801DD570: lwc1        $f16, 0xC($s1)
    ctx->f16.u32l = MEM_W(ctx->r17, 0XC);
    // 0x801DD574: addiu       $s0, $s0, 0x4
    ctx->r16 = ADD32(ctx->r16, 0X4);
    // 0x801DD578: sltu        $at, $s0, $s3
    ctx->r1 = ctx->r16 < ctx->r19 ? 1 : 0;
    // 0x801DD57C: add.s       $f18, $f8, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f18.fl = ctx->f8.fl + ctx->f16.fl;
    // 0x801DD580: addiu       $s1, $s1, 0x4
    ctx->r17 = ADD32(ctx->r17, 0X4);
    // 0x801DD584: bne         $at, $zero, L_801DD548
    if (ctx->r1 != 0) {
        // 0x801DD588: swc1        $f18, -0x4($s0)
        MEM_W(-0X4, ctx->r16) = ctx->f18.u32l;
            goto L_801DD548;
    }
    // 0x801DD588: swc1        $f18, -0x4($s0)
    MEM_W(-0X4, ctx->r16) = ctx->f18.u32l;
    // 0x801DD58C: lwc1        $f2, 0x118($sp)
    ctx->f2.u32l = MEM_W(ctx->r29, 0X118);
    // 0x801DD590: lwc1        $f14, 0x11C($sp)
    ctx->f14.u32l = MEM_W(ctx->r29, 0X11C);
    // 0x801DD594: lwc1        $f0, 0x120($sp)
    ctx->f0.u32l = MEM_W(ctx->r29, 0X120);
    // 0x801DD598: mul.s       $f4, $f2, $f2
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f4.fl = MUL_S(ctx->f2.fl, ctx->f2.fl);
    // 0x801DD59C: nop

    // 0x801DD5A0: mul.s       $f6, $f14, $f14
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f6.fl = MUL_S(ctx->f14.fl, ctx->f14.fl);
    // 0x801DD5A4: add.s       $f10, $f4, $f6
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f10.fl = ctx->f4.fl + ctx->f6.fl;
    // 0x801DD5A8: mul.s       $f8, $f0, $f0
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f8.fl = MUL_S(ctx->f0.fl, ctx->f0.fl);
    // 0x801DD5AC: jal         0x800C7010
    // 0x801DD5B0: add.s       $f12, $f8, $f10
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f12.fl = ctx->f8.fl + ctx->f10.fl;
    _nsqrtf(rdram, ctx);
        goto after_3;
    // 0x801DD5B0: add.s       $f12, $f8, $f10
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f12.fl = ctx->f8.fl + ctx->f10.fl;
    after_3:
    // 0x801DD5B4: or          $v0, $s2, $zero
    ctx->r2 = ctx->r18 | 0;
    // 0x801DD5B8: addiu       $s0, $sp, 0x118
    ctx->r16 = ADD32(ctx->r29, 0X118);
    // 0x801DD5BC: addiu       $s0, $s0, 0x4
    ctx->r16 = ADD32(ctx->r16, 0X4);
    // 0x801DD5C0: lwc1        $f16, -0x4($s0)
    ctx->f16.u32l = MEM_W(ctx->r16, -0X4);
    // 0x801DD5C4: div.s       $f16, $f16, $f0
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f16.fl = DIV_S(ctx->f16.fl, ctx->f0.fl);
    // 0x801DD5C8: swc1        $f16, 0x18($v0)
    MEM_W(0X18, ctx->r2) = ctx->f16.u32l;
    // 0x801DD5CC: lwc1        $f16, 0x18($v0)
    ctx->f16.u32l = MEM_W(ctx->r2, 0X18);
    // 0x801DD5D0: mul.s       $f18, $f16, $f20
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f18.fl = MUL_S(ctx->f16.fl, ctx->f20.fl);
    // 0x801DD5D4: beql        $s0, $s4, L_801DD610
    if (ctx->r16 == ctx->r20) {
        // 0x801DD5D8: lwc1        $f16, 0xC($v0)
        ctx->f16.u32l = MEM_W(ctx->r2, 0XC);
            goto L_801DD610;
    }
    goto skip_2;
    // 0x801DD5D8: lwc1        $f16, 0xC($v0)
    ctx->f16.u32l = MEM_W(ctx->r2, 0XC);
    skip_2:
    // 0x801DD5DC: lwc1        $f16, 0xC($v0)
    ctx->f16.u32l = MEM_W(ctx->r2, 0XC);
L_801DD5E0:
    // 0x801DD5E0: addiu       $s0, $s0, 0x4
    ctx->r16 = ADD32(ctx->r16, 0X4);
    // 0x801DD5E4: addiu       $v0, $v0, 0x4
    ctx->r2 = ADD32(ctx->r2, 0X4);
    // 0x801DD5E8: add.s       $f16, $f16, $f18
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f16.fl = ctx->f16.fl + ctx->f18.fl;
    // 0x801DD5EC: swc1        $f16, 0x8($v0)
    MEM_W(0X8, ctx->r2) = ctx->f16.u32l;
    // 0x801DD5F0: lwc1        $f16, -0x4($s0)
    ctx->f16.u32l = MEM_W(ctx->r16, -0X4);
    // 0x801DD5F4: div.s       $f16, $f16, $f0
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f16.fl = DIV_S(ctx->f16.fl, ctx->f0.fl);
    // 0x801DD5F8: swc1        $f16, 0x18($v0)
    MEM_W(0X18, ctx->r2) = ctx->f16.u32l;
    // 0x801DD5FC: lwc1        $f16, 0x18($v0)
    ctx->f16.u32l = MEM_W(ctx->r2, 0X18);
    // 0x801DD600: mul.s       $f18, $f16, $f20
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f18.fl = MUL_S(ctx->f16.fl, ctx->f20.fl);
    // 0x801DD604: bnel        $s0, $s4, L_801DD5E0
    if (ctx->r16 != ctx->r20) {
        // 0x801DD608: lwc1        $f16, 0xC($v0)
        ctx->f16.u32l = MEM_W(ctx->r2, 0XC);
            goto L_801DD5E0;
    }
    goto skip_3;
    // 0x801DD608: lwc1        $f16, 0xC($v0)
    ctx->f16.u32l = MEM_W(ctx->r2, 0XC);
    skip_3:
    // 0x801DD60C: lwc1        $f16, 0xC($v0)
    ctx->f16.u32l = MEM_W(ctx->r2, 0XC);
L_801DD610:
    // 0x801DD610: addiu       $v0, $v0, 0x4
    ctx->r2 = ADD32(ctx->r2, 0X4);
    // 0x801DD614: add.s       $f16, $f16, $f18
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f16.fl = ctx->f16.fl + ctx->f18.fl;
    // 0x801DD618: swc1        $f16, 0x8($v0)
    MEM_W(0X8, ctx->r2) = ctx->f16.u32l;
    // 0x801DD61C: lui         $t2, 0x8023
    ctx->r10 = S32(0X8023 << 16);
    // 0x801DD620: addiu       $t2, $t2, -0x7EE8
    ctx->r10 = ADD32(ctx->r10, -0X7EE8);
    // 0x801DD624: addiu       $s5, $s5, 0x4
    ctx->r21 = ADD32(ctx->r21, 0X4);
    // 0x801DD628: sltu        $at, $s5, $t2
    ctx->r1 = ctx->r21 < ctx->r10 ? 1 : 0;
    // 0x801DD62C: addiu       $s6, $s6, 0x18
    ctx->r22 = ADD32(ctx->r22, 0X18);
    // 0x801DD630: bne         $at, $zero, L_801DD4DC
    if (ctx->r1 != 0) {
        // 0x801DD634: addiu       $s2, $s2, 0x34
        ctx->r18 = ADD32(ctx->r18, 0X34);
            goto L_801DD4DC;
    }
    // 0x801DD634: addiu       $s2, $s2, 0x34
    ctx->r18 = ADD32(ctx->r18, 0X34);
    // 0x801DD638: addiu       $s0, $sp, 0x64
    ctx->r16 = ADD32(ctx->r29, 0X64);
    // 0x801DD63C: addiu       $s1, $sp, 0x6C
    ctx->r17 = ADD32(ctx->r29, 0X6C);
    // 0x801DD640: addiu       $s2, $sp, 0xE4
    ctx->r18 = ADD32(ctx->r29, 0XE4);
L_801DD644:
    // 0x801DD644: lw          $v0, 0x0($s0)
    ctx->r2 = MEM_W(ctx->r16, 0X0);
    // 0x801DD648: lw          $t7, 0x4($s0)
    ctx->r15 = MEM_W(ctx->r16, 0X4);
    // 0x801DD64C: lui         $t1, 0x8023
    ctx->r9 = S32(0X8023 << 16);
    // 0x801DD650: multu       $v0, $s7
    result = U64(U32(ctx->r2)) * U64(U32(ctx->r23)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x801DD654: addiu       $t1, $t1, -0x7E70
    ctx->r9 = ADD32(ctx->r9, -0X7E70);
    // 0x801DD658: or          $a1, $s1, $zero
    ctx->r5 = ctx->r17 | 0;
    // 0x801DD65C: or          $a2, $fp, $zero
    ctx->r6 = ctx->r30 | 0;
    // 0x801DD660: subu        $a3, $t7, $v0
    ctx->r7 = SUB32(ctx->r15, ctx->r2);
    // 0x801DD664: mflo        $t8
    ctx->r24 = lo;
    // 0x801DD668: addu        $a0, $t8, $t1
    ctx->r4 = ADD32(ctx->r24, ctx->r9);
    // 0x801DD66C: jal         0x801DB430
    // 0x801DD670: nop

    func_801DB430(rdram, ctx);
        goto after_4;
    // 0x801DD670: nop

    after_4:
    // 0x801DD674: addiu       $s1, $s1, 0x3C
    ctx->r17 = ADD32(ctx->r17, 0X3C);
    // 0x801DD678: bne         $s1, $s2, L_801DD644
    if (ctx->r17 != ctx->r18) {
        // 0x801DD67C: addiu       $s0, $s0, 0x3C
        ctx->r16 = ADD32(ctx->r16, 0X3C);
            goto L_801DD644;
    }
    // 0x801DD67C: addiu       $s0, $s0, 0x3C
    ctx->r16 = ADD32(ctx->r16, 0X3C);
L_801DD680:
    // 0x801DD680: lw          $ra, 0x44($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X44);
    // 0x801DD684: ldc1        $f20, 0x18($sp)
    CHECK_FR(ctx, 20);
    ctx->f20.u64 = LD(ctx->r29, 0X18);
    // 0x801DD688: lw          $s0, 0x20($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X20);
    // 0x801DD68C: lw          $s1, 0x24($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X24);
    // 0x801DD690: lw          $s2, 0x28($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X28);
    // 0x801DD694: lw          $s3, 0x2C($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X2C);
    // 0x801DD698: lw          $s4, 0x30($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X30);
    // 0x801DD69C: lw          $s5, 0x34($sp)
    ctx->r21 = MEM_W(ctx->r29, 0X34);
    // 0x801DD6A0: lw          $s6, 0x38($sp)
    ctx->r22 = MEM_W(ctx->r29, 0X38);
    // 0x801DD6A4: lw          $s7, 0x3C($sp)
    ctx->r23 = MEM_W(ctx->r29, 0X3C);
    // 0x801DD6A8: lw          $fp, 0x40($sp)
    ctx->r30 = MEM_W(ctx->r29, 0X40);
    // 0x801DD6AC: jr          $ra
    // 0x801DD6B0: addiu       $sp, $sp, 0x128
    ctx->r29 = ADD32(ctx->r29, 0X128);
    return;
    // 0x801DD6B0: addiu       $sp, $sp, 0x128
    ctx->r29 = ADD32(ctx->r29, 0X128);
;}
RECOMP_FUNC void func_801DD6B4(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801DD6B4: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x801DD6B8: lw          $v0, -0x19C8($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X19C8);
    // 0x801DD6BC: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801DD6C0: sw          $zero, -0x7858($at)
    MEM_W(-0X7858, ctx->r1) = 0;
    // 0x801DD6C4: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x801DD6C8: addiu       $at, $zero, 0x8
    ctx->r1 = ADD32(0, 0X8);
    // 0x801DD6CC: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x801DD6D0: or          $a2, $a0, $zero
    ctx->r6 = ctx->r4 | 0;
    // 0x801DD6D4: beq         $v0, $at, L_801DD6F0
    if (ctx->r2 == ctx->r1) {
        // 0x801DD6D8: or          $v1, $zero, $zero
        ctx->r3 = 0 | 0;
            goto L_801DD6F0;
    }
    // 0x801DD6D8: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
    // 0x801DD6DC: addiu       $at, $zero, 0x15
    ctx->r1 = ADD32(0, 0X15);
    // 0x801DD6E0: beq         $v0, $at, L_801DD774
    if (ctx->r2 == ctx->r1) {
        // 0x801DD6E4: nop
    
            goto L_801DD774;
    }
    // 0x801DD6E4: nop

    // 0x801DD6E8: b           L_801DD828
    // 0x801DD6EC: nop

        goto L_801DD828;
    // 0x801DD6EC: nop

L_801DD6F0:
    // 0x801DD6F0: lui         $t6, 0x800E
    ctx->r14 = S32(0X800E << 16);
    // 0x801DD6F4: lw          $t6, -0x7E90($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X7E90);
    // 0x801DD6F8: sltiu       $at, $t6, 0x8
    ctx->r1 = ctx->r14 < 0X8 ? 1 : 0;
    // 0x801DD6FC: beq         $at, $zero, L_801DD828
    if (ctx->r1 == 0) {
        // 0x801DD700: sll         $t6, $t6, 2
        ctx->r14 = S32(ctx->r14 << 2);
            goto L_801DD828;
    }
    // 0x801DD700: sll         $t6, $t6, 2
    ctx->r14 = S32(ctx->r14 << 2);
    // 0x801DD704: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801DD708: addu        $at, $at, $t6
    gpr jr_addend_801DD710 = ctx->r14;
    ctx->r1 = ADD32(ctx->r1, ctx->r14);
    // 0x801DD70C: lw          $t6, 0x5F68($at)
    ctx->r14 = ADD32(ctx->r1, 0X5F68);
    // 0x801DD710: jr          $t6
    // 0x801DD714: nop

    switch (jr_addend_801DD710 >> 2) {
        case 0: goto L_801DD718; break;
        case 1: goto L_801DD724; break;
        case 2: goto L_801DD744; break;
        case 3: goto L_801DD828; break;
        case 4: goto L_801DD750; break;
        case 5: goto L_801DD75C; break;
        case 6: goto L_801DD828; break;
        case 7: goto L_801DD768; break;
        default: switch_error(__func__, 0x801DD710, 0x80225F68);
    }
    // 0x801DD714: nop

L_801DD718:
    // 0x801DD718: lui         $v1, 0x801E
    ctx->r3 = S32(0X801E << 16);
    // 0x801DD71C: b           L_801DD828
    // 0x801DD720: addiu       $v1, $v1, -0x3D8C
    ctx->r3 = ADD32(ctx->r3, -0X3D8C);
        goto L_801DD828;
    // 0x801DD720: addiu       $v1, $v1, -0x3D8C
    ctx->r3 = ADD32(ctx->r3, -0X3D8C);
L_801DD724:
    // 0x801DD724: lui         $t7, 0x801D
    ctx->r15 = S32(0X801D << 16);
    // 0x801DD728: lw          $t7, -0x4CC8($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X4CC8);
    // 0x801DD72C: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x801DD730: bne         $a1, $t7, L_801DD828
    if (ctx->r5 != ctx->r15) {
        // 0x801DD734: nop
    
            goto L_801DD828;
    }
    // 0x801DD734: nop

    // 0x801DD738: lui         $v1, 0x801E
    ctx->r3 = S32(0X801E << 16);
    // 0x801DD73C: b           L_801DD828
    // 0x801DD740: addiu       $v1, $v1, -0x3BFC
    ctx->r3 = ADD32(ctx->r3, -0X3BFC);
        goto L_801DD828;
    // 0x801DD740: addiu       $v1, $v1, -0x3BFC
    ctx->r3 = ADD32(ctx->r3, -0X3BFC);
L_801DD744:
    // 0x801DD744: lui         $v1, 0x801E
    ctx->r3 = S32(0X801E << 16);
    // 0x801DD748: b           L_801DD828
    // 0x801DD74C: addiu       $v1, $v1, -0x3A58
    ctx->r3 = ADD32(ctx->r3, -0X3A58);
        goto L_801DD828;
    // 0x801DD74C: addiu       $v1, $v1, -0x3A58
    ctx->r3 = ADD32(ctx->r3, -0X3A58);
L_801DD750:
    // 0x801DD750: lui         $v1, 0x801E
    ctx->r3 = S32(0X801E << 16);
    // 0x801DD754: b           L_801DD828
    // 0x801DD758: addiu       $v1, $v1, -0x39F4
    ctx->r3 = ADD32(ctx->r3, -0X39F4);
        goto L_801DD828;
    // 0x801DD758: addiu       $v1, $v1, -0x39F4
    ctx->r3 = ADD32(ctx->r3, -0X39F4);
L_801DD75C:
    // 0x801DD75C: lui         $v1, 0x801E
    ctx->r3 = S32(0X801E << 16);
    // 0x801DD760: b           L_801DD828
    // 0x801DD764: addiu       $v1, $v1, -0x32CC
    ctx->r3 = ADD32(ctx->r3, -0X32CC);
        goto L_801DD828;
    // 0x801DD764: addiu       $v1, $v1, -0x32CC
    ctx->r3 = ADD32(ctx->r3, -0X32CC);
L_801DD768:
    // 0x801DD768: lui         $v1, 0x801E
    ctx->r3 = S32(0X801E << 16);
    // 0x801DD76C: b           L_801DD828
    // 0x801DD770: addiu       $v1, $v1, -0x2D30
    ctx->r3 = ADD32(ctx->r3, -0X2D30);
        goto L_801DD828;
    // 0x801DD770: addiu       $v1, $v1, -0x2D30
    ctx->r3 = ADD32(ctx->r3, -0X2D30);
L_801DD774:
    // 0x801DD774: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x801DD778: lw          $v0, -0x4CC8($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X4CC8);
    // 0x801DD77C: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    // 0x801DD780: lui         $t8, 0x801C
    ctx->r24 = S32(0X801C << 16);
    // 0x801DD784: beq         $v0, $zero, L_801DD7A4
    if (ctx->r2 == 0) {
        // 0x801DD788: nop
    
            goto L_801DD7A4;
    }
    // 0x801DD788: nop

    // 0x801DD78C: beq         $v0, $a0, L_801DD7A4
    if (ctx->r2 == ctx->r4) {
        // 0x801DD790: addiu       $a1, $zero, 0x2
        ctx->r5 = ADD32(0, 0X2);
            goto L_801DD7A4;
    }
    // 0x801DD790: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x801DD794: beq         $v0, $a1, L_801DD7C8
    if (ctx->r2 == ctx->r5) {
        // 0x801DD798: nop
    
            goto L_801DD7C8;
    }
    // 0x801DD798: nop

    // 0x801DD79C: b           L_801DD828
    // 0x801DD7A0: nop

        goto L_801DD828;
    // 0x801DD7A0: nop

L_801DD7A4:
    // 0x801DD7A4: lw          $t8, 0x2C70($t8)
    ctx->r24 = MEM_W(ctx->r24, 0X2C70);
    // 0x801DD7A8: lui         $v0, 0x8023
    ctx->r2 = S32(0X8023 << 16);
    // 0x801DD7AC: addiu       $v0, $v0, -0x7854
    ctx->r2 = ADD32(ctx->r2, -0X7854);
    // 0x801DD7B0: slti        $at, $t8, 0x3
    ctx->r1 = SIGNED(ctx->r24) < 0X3 ? 1 : 0;
    // 0x801DD7B4: beq         $at, $zero, L_801DD828
    if (ctx->r1 == 0) {
        // 0x801DD7B8: sw          $t8, 0x0($v0)
        MEM_W(0X0, ctx->r2) = ctx->r24;
            goto L_801DD828;
    }
    // 0x801DD7B8: sw          $t8, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r24;
    // 0x801DD7BC: lui         $v1, 0x801E
    ctx->r3 = S32(0X801E << 16);
    // 0x801DD7C0: b           L_801DD828
    // 0x801DD7C4: addiu       $v1, $v1, -0x3F54
    ctx->r3 = ADD32(ctx->r3, -0X3F54);
        goto L_801DD828;
    // 0x801DD7C4: addiu       $v1, $v1, -0x3F54
    ctx->r3 = ADD32(ctx->r3, -0X3F54);
L_801DD7C8:
    // 0x801DD7C8: lui         $v0, 0x801C
    ctx->r2 = S32(0X801C << 16);
    // 0x801DD7CC: lw          $v0, 0x2C70($v0)
    ctx->r2 = MEM_W(ctx->r2, 0X2C70);
    // 0x801DD7D0: beq         $v0, $zero, L_801DD7F0
    if (ctx->r2 == 0) {
        // 0x801DD7D4: nop
    
            goto L_801DD7F0;
    }
    // 0x801DD7D4: nop

    // 0x801DD7D8: beq         $v0, $a0, L_801DD7FC
    if (ctx->r2 == ctx->r4) {
        // 0x801DD7DC: addiu       $t0, $zero, 0x4
        ctx->r8 = ADD32(0, 0X4);
            goto L_801DD7FC;
    }
    // 0x801DD7DC: addiu       $t0, $zero, 0x4
    ctx->r8 = ADD32(0, 0X4);
    // 0x801DD7E0: beq         $v0, $a1, L_801DD814
    if (ctx->r2 == ctx->r5) {
        // 0x801DD7E4: addiu       $t1, $zero, 0x3
        ctx->r9 = ADD32(0, 0X3);
            goto L_801DD814;
    }
    // 0x801DD7E4: addiu       $t1, $zero, 0x3
    ctx->r9 = ADD32(0, 0X3);
    // 0x801DD7E8: b           L_801DD828
    // 0x801DD7EC: nop

        goto L_801DD828;
    // 0x801DD7EC: nop

L_801DD7F0:
    // 0x801DD7F0: lui         $v1, 0x801E
    ctx->r3 = S32(0X801E << 16);
    // 0x801DD7F4: b           L_801DD828
    // 0x801DD7F8: addiu       $v1, $v1, -0x4710
    ctx->r3 = ADD32(ctx->r3, -0X4710);
        goto L_801DD828;
    // 0x801DD7F8: addiu       $v1, $v1, -0x4710
    ctx->r3 = ADD32(ctx->r3, -0X4710);
L_801DD7FC:
    // 0x801DD7FC: lui         $v0, 0x8023
    ctx->r2 = S32(0X8023 << 16);
    // 0x801DD800: addiu       $v0, $v0, -0x7854
    ctx->r2 = ADD32(ctx->r2, -0X7854);
    // 0x801DD804: lui         $v1, 0x801E
    ctx->r3 = S32(0X801E << 16);
    // 0x801DD808: sw          $t0, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r8;
    // 0x801DD80C: b           L_801DD828
    // 0x801DD810: addiu       $v1, $v1, -0x4098
    ctx->r3 = ADD32(ctx->r3, -0X4098);
        goto L_801DD828;
    // 0x801DD810: addiu       $v1, $v1, -0x4098
    ctx->r3 = ADD32(ctx->r3, -0X4098);
L_801DD814:
    // 0x801DD814: lui         $v0, 0x8023
    ctx->r2 = S32(0X8023 << 16);
    // 0x801DD818: addiu       $v0, $v0, -0x7854
    ctx->r2 = ADD32(ctx->r2, -0X7854);
    // 0x801DD81C: lui         $v1, 0x801E
    ctx->r3 = S32(0X801E << 16);
    // 0x801DD820: sw          $t1, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r9;
    // 0x801DD824: addiu       $v1, $v1, -0x4098
    ctx->r3 = ADD32(ctx->r3, -0X4098);
L_801DD828:
    // 0x801DD828: beql        $v1, $zero, L_801DD850
    if (ctx->r3 == 0) {
        // 0x801DD82C: lw          $ra, 0x14($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X14);
            goto L_801DD850;
    }
    goto skip_0;
    // 0x801DD82C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    skip_0:
    // 0x801DD830: jalr        $v1
    // 0x801DD834: or          $a0, $a2, $zero
    ctx->r4 = ctx->r6 | 0;
    LOOKUP_FUNC(ctx->r3)(rdram, ctx);
        goto after_0;
    // 0x801DD834: or          $a0, $a2, $zero
    ctx->r4 = ctx->r6 | 0;
    after_0:
    // 0x801DD838: lui         $a0, 0x8023
    ctx->r4 = S32(0X8023 << 16);
    // 0x801DD83C: lui         $a1, 0x8023
    ctx->r5 = S32(0X8023 << 16);
    // 0x801DD840: lw          $a1, -0x7858($a1)
    ctx->r5 = MEM_W(ctx->r5, -0X7858);
    // 0x801DD844: jal         0x800AC098
    // 0x801DD848: addiu       $a0, $a0, -0x7E70
    ctx->r4 = ADD32(ctx->r4, -0X7E70);
    func_800AC098(rdram, ctx);
        goto after_1;
    // 0x801DD848: addiu       $a0, $a0, -0x7E70
    ctx->r4 = ADD32(ctx->r4, -0X7E70);
    after_1:
    // 0x801DD84C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_801DD850:
    // 0x801DD850: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x801DD854: jr          $ra
    // 0x801DD858: nop

    return;
    // 0x801DD858: nop

;}
RECOMP_FUNC void func_801DD85C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801DD85C: addiu       $sp, $sp, -0xA0
    ctx->r29 = ADD32(ctx->r29, -0XA0);
    // 0x801DD860: sw          $fp, 0x60($sp)
    MEM_W(0X60, ctx->r29) = ctx->r30;
    // 0x801DD864: sw          $s7, 0x5C($sp)
    MEM_W(0X5C, ctx->r29) = ctx->r23;
    // 0x801DD868: sw          $s6, 0x58($sp)
    MEM_W(0X58, ctx->r29) = ctx->r22;
    // 0x801DD86C: sw          $s5, 0x54($sp)
    MEM_W(0X54, ctx->r29) = ctx->r21;
    // 0x801DD870: sw          $s4, 0x50($sp)
    MEM_W(0X50, ctx->r29) = ctx->r20;
    // 0x801DD874: sw          $s3, 0x4C($sp)
    MEM_W(0X4C, ctx->r29) = ctx->r19;
    // 0x801DD878: sw          $s1, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r17;
    // 0x801DD87C: sw          $s0, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r16;
    // 0x801DD880: sdc1        $f20, 0x38($sp)
    CHECK_FR(ctx, 20);
    SD(ctx->f20.u64, 0X38, ctx->r29);
    // 0x801DD884: lui         $t6, 0x8022
    ctx->r14 = S32(0X8022 << 16);
    // 0x801DD888: lui         $t7, 0x8022
    ctx->r15 = S32(0X8022 << 16);
    // 0x801DD88C: lui         $t8, 0x8022
    ctx->r24 = S32(0X8022 << 16);
    // 0x801DD890: lui         $t9, 0x8022
    ctx->r25 = S32(0X8022 << 16);
    // 0x801DD894: lui         $t0, 0x8022
    ctx->r8 = S32(0X8022 << 16);
    // 0x801DD898: sw          $s2, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r18;
    // 0x801DD89C: addiu       $t0, $t0, 0x7C98
    ctx->r8 = ADD32(ctx->r8, 0X7C98);
    // 0x801DD8A0: addiu       $t9, $t9, 0x7C94
    ctx->r25 = ADD32(ctx->r25, 0X7C94);
    // 0x801DD8A4: addiu       $t8, $t8, 0x7C90
    ctx->r24 = ADD32(ctx->r24, 0X7C90);
    // 0x801DD8A8: addiu       $t7, $t7, 0x7CA4
    ctx->r15 = ADD32(ctx->r15, 0X7CA4);
    // 0x801DD8AC: addiu       $t6, $t6, 0x7CA0
    ctx->r14 = ADD32(ctx->r14, 0X7CA0);
    // 0x801DD8B0: lui         $s0, 0x8022
    ctx->r16 = S32(0X8022 << 16);
    // 0x801DD8B4: lui         $s1, 0x8023
    ctx->r17 = S32(0X8023 << 16);
    // 0x801DD8B8: lui         $s3, 0x8022
    ctx->r19 = S32(0X8022 << 16);
    // 0x801DD8BC: lui         $s4, 0x8023
    ctx->r20 = S32(0X8023 << 16);
    // 0x801DD8C0: lui         $s5, 0x8022
    ctx->r21 = S32(0X8022 << 16);
    // 0x801DD8C4: lui         $s6, 0x8022
    ctx->r22 = S32(0X8022 << 16);
    // 0x801DD8C8: lui         $s7, 0x8022
    ctx->r23 = S32(0X8022 << 16);
    // 0x801DD8CC: lui         $fp, 0x8022
    ctx->r30 = S32(0X8022 << 16);
    // 0x801DD8D0: mtc1        $zero, $f20
    ctx->f20.u32l = 0;
    // 0x801DD8D4: sw          $ra, 0x64($sp)
    MEM_W(0X64, ctx->r29) = ctx->r31;
    // 0x801DD8D8: addiu       $fp, $fp, 0x7C9C
    ctx->r30 = ADD32(ctx->r30, 0X7C9C);
    // 0x801DD8DC: addiu       $s7, $s7, 0x7C8C
    ctx->r23 = ADD32(ctx->r23, 0X7C8C);
    // 0x801DD8E0: addiu       $s6, $s6, 0x7C88
    ctx->r22 = ADD32(ctx->r22, 0X7C88);
    // 0x801DD8E4: addiu       $s5, $s5, 0x7C84
    ctx->r21 = ADD32(ctx->r21, 0X7C84);
    // 0x801DD8E8: addiu       $s4, $s4, -0x7F38
    ctx->r20 = ADD32(ctx->r20, -0X7F38);
    // 0x801DD8EC: addiu       $s3, $s3, 0x7E98
    ctx->r19 = ADD32(ctx->r19, 0X7E98);
    // 0x801DD8F0: addiu       $s1, $s1, -0x7FA8
    ctx->r17 = ADD32(ctx->r17, -0X7FA8);
    // 0x801DD8F4: addiu       $s0, $s0, 0x7C80
    ctx->r16 = ADD32(ctx->r16, 0X7C80);
    // 0x801DD8F8: sw          $t6, 0x78($sp)
    MEM_W(0X78, ctx->r29) = ctx->r14;
    // 0x801DD8FC: sw          $t7, 0x74($sp)
    MEM_W(0X74, ctx->r29) = ctx->r15;
    // 0x801DD900: sw          $t8, 0x70($sp)
    MEM_W(0X70, ctx->r29) = ctx->r24;
    // 0x801DD904: sw          $t9, 0x6C($sp)
    MEM_W(0X6C, ctx->r29) = ctx->r25;
    // 0x801DD908: sw          $t0, 0x68($sp)
    MEM_W(0X68, ctx->r29) = ctx->r8;
    // 0x801DD90C: or          $s2, $zero, $zero
    ctx->r18 = 0 | 0;
L_801DD910:
    // 0x801DD910: addiu       $t1, $zero, 0x1
    ctx->r9 = ADD32(0, 0X1);
    // 0x801DD914: sw          $s2, 0xE8($s0)
    MEM_W(0XE8, ctx->r16) = ctx->r18;
    // 0x801DD918: sw          $t1, 0xEC($s0)
    MEM_W(0XEC, ctx->r16) = ctx->r9;
    // 0x801DD91C: sw          $zero, 0xF8($s0)
    MEM_W(0XF8, ctx->r16) = 0;
    // 0x801DD920: swc1        $f20, 0xFC($s0)
    MEM_W(0XFC, ctx->r16) = ctx->f20.u32l;
    // 0x801DD924: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    // 0x801DD928: jal         0x801DFD8C
    // 0x801DD92C: or          $a1, $s3, $zero
    ctx->r5 = ctx->r19 | 0;
    func_801DFD8C(rdram, ctx);
        goto after_0;
    // 0x801DD92C: or          $a1, $s3, $zero
    ctx->r5 = ctx->r19 | 0;
    after_0:
    // 0x801DD930: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    // 0x801DD934: jal         0x801DFDA0
    // 0x801DD938: or          $a1, $s4, $zero
    ctx->r5 = ctx->r20 | 0;
    func_801DFDA0(rdram, ctx);
        goto after_1;
    // 0x801DD938: or          $a1, $s4, $zero
    ctx->r5 = ctx->r20 | 0;
    after_1:
    // 0x801DD93C: lw          $t2, 0x78($sp)
    ctx->r10 = MEM_W(ctx->r29, 0X78);
    // 0x801DD940: lw          $t3, 0x74($sp)
    ctx->r11 = MEM_W(ctx->r29, 0X74);
    // 0x801DD944: lw          $t4, 0x70($sp)
    ctx->r12 = MEM_W(ctx->r29, 0X70);
    // 0x801DD948: lw          $t5, 0x6C($sp)
    ctx->r13 = MEM_W(ctx->r29, 0X6C);
    // 0x801DD94C: lw          $t6, 0x68($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X68);
    // 0x801DD950: lui         $t7, 0x8023
    ctx->r15 = S32(0X8023 << 16);
    // 0x801DD954: addiu       $t7, $t7, -0x7EF8
    ctx->r15 = ADD32(ctx->r15, -0X7EF8);
    // 0x801DD958: sw          $t7, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r15;
    // 0x801DD95C: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    // 0x801DD960: or          $a1, $s5, $zero
    ctx->r5 = ctx->r21 | 0;
    // 0x801DD964: or          $a2, $s6, $zero
    ctx->r6 = ctx->r22 | 0;
    // 0x801DD968: or          $a3, $s7, $zero
    ctx->r7 = ctx->r23 | 0;
    // 0x801DD96C: sw          $fp, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r30;
    // 0x801DD970: sw          $t2, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r10;
    // 0x801DD974: sw          $t3, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r11;
    // 0x801DD978: sw          $t4, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r12;
    // 0x801DD97C: sw          $t5, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r13;
    // 0x801DD980: jal         0x801DFDA8
    // 0x801DD984: sw          $t6, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r14;
    func_801DFDA8(rdram, ctx);
        goto after_2;
    // 0x801DD984: sw          $t6, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r14;
    after_2:
    // 0x801DD988: lw          $t8, 0x78($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X78);
    // 0x801DD98C: lw          $t0, 0x74($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X74);
    // 0x801DD990: lw          $t2, 0x70($sp)
    ctx->r10 = MEM_W(ctx->r29, 0X70);
    // 0x801DD994: lw          $t4, 0x6C($sp)
    ctx->r12 = MEM_W(ctx->r29, 0X6C);
    // 0x801DD998: lw          $t6, 0x68($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X68);
    // 0x801DD99C: addiu       $s2, $s2, 0x1
    ctx->r18 = ADD32(ctx->r18, 0X1);
    // 0x801DD9A0: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x801DD9A4: addiu       $t9, $t8, 0x10C
    ctx->r25 = ADD32(ctx->r24, 0X10C);
    // 0x801DD9A8: addiu       $t1, $t0, 0x10C
    ctx->r9 = ADD32(ctx->r8, 0X10C);
    // 0x801DD9AC: addiu       $t3, $t2, 0x10C
    ctx->r11 = ADD32(ctx->r10, 0X10C);
    // 0x801DD9B0: addiu       $t5, $t4, 0x10C
    ctx->r13 = ADD32(ctx->r12, 0X10C);
    // 0x801DD9B4: addiu       $t7, $t6, 0x10C
    ctx->r15 = ADD32(ctx->r14, 0X10C);
    // 0x801DD9B8: sw          $t7, 0x68($sp)
    MEM_W(0X68, ctx->r29) = ctx->r15;
    // 0x801DD9BC: sw          $t5, 0x6C($sp)
    MEM_W(0X6C, ctx->r29) = ctx->r13;
    // 0x801DD9C0: sw          $t3, 0x70($sp)
    MEM_W(0X70, ctx->r29) = ctx->r11;
    // 0x801DD9C4: sw          $t1, 0x74($sp)
    MEM_W(0X74, ctx->r29) = ctx->r9;
    // 0x801DD9C8: sw          $t9, 0x78($sp)
    MEM_W(0X78, ctx->r29) = ctx->r25;
    // 0x801DD9CC: addiu       $s0, $s0, 0x10C
    ctx->r16 = ADD32(ctx->r16, 0X10C);
    // 0x801DD9D0: addiu       $s1, $s1, 0x38
    ctx->r17 = ADD32(ctx->r17, 0X38);
    // 0x801DD9D4: addiu       $s3, $s3, 0xE0
    ctx->r19 = ADD32(ctx->r19, 0XE0);
    // 0x801DD9D8: addiu       $s4, $s4, 0x20
    ctx->r20 = ADD32(ctx->r20, 0X20);
    // 0x801DD9DC: addiu       $s5, $s5, 0x10C
    ctx->r21 = ADD32(ctx->r21, 0X10C);
    // 0x801DD9E0: addiu       $s6, $s6, 0x10C
    ctx->r22 = ADD32(ctx->r22, 0X10C);
    // 0x801DD9E4: addiu       $s7, $s7, 0x10C
    ctx->r23 = ADD32(ctx->r23, 0X10C);
    // 0x801DD9E8: bne         $s2, $at, L_801DD910
    if (ctx->r18 != ctx->r1) {
        // 0x801DD9EC: addiu       $fp, $fp, 0x10C
        ctx->r30 = ADD32(ctx->r30, 0X10C);
            goto L_801DD910;
    }
    // 0x801DD9EC: addiu       $fp, $fp, 0x10C
    ctx->r30 = ADD32(ctx->r30, 0X10C);
    // 0x801DD9F0: lw          $ra, 0x64($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X64);
    // 0x801DD9F4: ldc1        $f20, 0x38($sp)
    CHECK_FR(ctx, 20);
    ctx->f20.u64 = LD(ctx->r29, 0X38);
    // 0x801DD9F8: lw          $s0, 0x40($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X40);
    // 0x801DD9FC: lw          $s1, 0x44($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X44);
    // 0x801DDA00: lw          $s2, 0x48($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X48);
    // 0x801DDA04: lw          $s3, 0x4C($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X4C);
    // 0x801DDA08: lw          $s4, 0x50($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X50);
    // 0x801DDA0C: lw          $s5, 0x54($sp)
    ctx->r21 = MEM_W(ctx->r29, 0X54);
    // 0x801DDA10: lw          $s6, 0x58($sp)
    ctx->r22 = MEM_W(ctx->r29, 0X58);
    // 0x801DDA14: lw          $s7, 0x5C($sp)
    ctx->r23 = MEM_W(ctx->r29, 0X5C);
    // 0x801DDA18: lw          $fp, 0x60($sp)
    ctx->r30 = MEM_W(ctx->r29, 0X60);
    // 0x801DDA1C: jr          $ra
    // 0x801DDA20: addiu       $sp, $sp, 0xA0
    ctx->r29 = ADD32(ctx->r29, 0XA0);
    return;
    // 0x801DDA20: addiu       $sp, $sp, 0xA0
    ctx->r29 = ADD32(ctx->r29, 0XA0);
;}
RECOMP_FUNC void func_801DDA24(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801DDA24: addiu       $sp, $sp, -0x30
    ctx->r29 = ADD32(ctx->r29, -0X30);
    // 0x801DDA28: sw          $s4, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r20;
    // 0x801DDA2C: lui         $s4, 0x800E
    ctx->r20 = S32(0X800E << 16);
    // 0x801DDA30: addiu       $s4, $s4, -0x54D8
    ctx->r20 = ADD32(ctx->r20, -0X54D8);
    // 0x801DDA34: lw          $t6, 0x0($s4)
    ctx->r14 = MEM_W(ctx->r20, 0X0);
    // 0x801DDA38: sw          $s0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r16;
    // 0x801DDA3C: sw          $ra, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r31;
    // 0x801DDA40: sw          $s3, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r19;
    // 0x801DDA44: sw          $s2, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r18;
    // 0x801DDA48: sw          $s1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r17;
    // 0x801DDA4C: blez        $t6, L_801DDA98
    if (SIGNED(ctx->r14) <= 0) {
        // 0x801DDA50: or          $s0, $zero, $zero
        ctx->r16 = 0 | 0;
            goto L_801DDA98;
    }
    // 0x801DDA50: or          $s0, $zero, $zero
    ctx->r16 = 0 | 0;
    // 0x801DDA54: lui         $s1, 0x8022
    ctx->r17 = S32(0X8022 << 16);
    // 0x801DDA58: lui         $s2, 0x8022
    ctx->r18 = S32(0X8022 << 16);
    // 0x801DDA5C: lui         $s3, 0x8023
    ctx->r19 = S32(0X8023 << 16);
    // 0x801DDA60: addiu       $s3, $s3, -0x7FA8
    ctx->r19 = ADD32(ctx->r19, -0X7FA8);
    // 0x801DDA64: addiu       $s2, $s2, 0x7E98
    ctx->r18 = ADD32(ctx->r18, 0X7E98);
    // 0x801DDA68: addiu       $s1, $s1, 0x7C80
    ctx->r17 = ADD32(ctx->r17, 0X7C80);
L_801DDA6C:
    // 0x801DDA6C: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    // 0x801DDA70: or          $a1, $s2, $zero
    ctx->r5 = ctx->r18 | 0;
    // 0x801DDA74: jal         0x801DDAB8
    // 0x801DDA78: or          $a2, $s3, $zero
    ctx->r6 = ctx->r19 | 0;
    func_801DDAB8(rdram, ctx);
        goto after_0;
    // 0x801DDA78: or          $a2, $s3, $zero
    ctx->r6 = ctx->r19 | 0;
    after_0:
    // 0x801DDA7C: lw          $t7, 0x0($s4)
    ctx->r15 = MEM_W(ctx->r20, 0X0);
    // 0x801DDA80: addiu       $s0, $s0, 0x1
    ctx->r16 = ADD32(ctx->r16, 0X1);
    // 0x801DDA84: addiu       $s1, $s1, 0x10C
    ctx->r17 = ADD32(ctx->r17, 0X10C);
    // 0x801DDA88: slt         $at, $s0, $t7
    ctx->r1 = SIGNED(ctx->r16) < SIGNED(ctx->r15) ? 1 : 0;
    // 0x801DDA8C: addiu       $s2, $s2, 0xE0
    ctx->r18 = ADD32(ctx->r18, 0XE0);
    // 0x801DDA90: bne         $at, $zero, L_801DDA6C
    if (ctx->r1 != 0) {
        // 0x801DDA94: addiu       $s3, $s3, 0x38
        ctx->r19 = ADD32(ctx->r19, 0X38);
            goto L_801DDA6C;
    }
    // 0x801DDA94: addiu       $s3, $s3, 0x38
    ctx->r19 = ADD32(ctx->r19, 0X38);
L_801DDA98:
    // 0x801DDA98: lw          $ra, 0x2C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X2C);
    // 0x801DDA9C: lw          $s0, 0x18($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X18);
    // 0x801DDAA0: lw          $s1, 0x1C($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X1C);
    // 0x801DDAA4: lw          $s2, 0x20($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X20);
    // 0x801DDAA8: lw          $s3, 0x24($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X24);
    // 0x801DDAAC: lw          $s4, 0x28($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X28);
    // 0x801DDAB0: jr          $ra
    // 0x801DDAB4: addiu       $sp, $sp, 0x30
    ctx->r29 = ADD32(ctx->r29, 0X30);
    return;
    // 0x801DDAB4: addiu       $sp, $sp, 0x30
    ctx->r29 = ADD32(ctx->r29, 0X30);
;}
RECOMP_FUNC void func_801DDAB8(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801DDAB8: lui         $at, 0x4120
    ctx->r1 = S32(0X4120 << 16);
    // 0x801DDABC: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x801DDAC0: addiu       $sp, $sp, -0x28
    ctx->r29 = ADD32(ctx->r29, -0X28);
    // 0x801DDAC4: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x801DDAC8: sw          $s0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r16;
    // 0x801DDACC: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801DDAD0: swc1        $f4, 0x9C($a0)
    MEM_W(0X9C, ctx->r4) = ctx->f4.u32l;
    // 0x801DDAD4: lwc1        $f6, 0x5F88($at)
    ctx->f6.u32l = MEM_W(ctx->r1, 0X5F88);
    // 0x801DDAD8: lui         $t6, 0x8019
    ctx->r14 = S32(0X8019 << 16);
    // 0x801DDADC: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801DDAE0: swc1        $f6, 0xA0($a0)
    MEM_W(0XA0, ctx->r4) = ctx->f6.u32l;
    // 0x801DDAE4: lw          $t6, 0x2458($t6)
    ctx->r14 = MEM_W(ctx->r14, 0X2458);
    // 0x801DDAE8: or          $s0, $a1, $zero
    ctx->r16 = ctx->r5 | 0;
    // 0x801DDAEC: or          $a3, $a0, $zero
    ctx->r7 = ctx->r4 | 0;
    // 0x801DDAF0: mtc1        $t6, $f8
    ctx->f8.u32l = ctx->r14;
    // 0x801DDAF4: nop

    // 0x801DDAF8: cvt.s.w     $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.fl = CVT_S_W(ctx->f8.u32l);
    // 0x801DDAFC: swc1        $f10, -0x7EF8($at)
    MEM_W(-0X7EF8, ctx->r1) = ctx->f10.u32l;
    // 0x801DDB00: lw          $t7, 0x0($a0)
    ctx->r15 = MEM_W(ctx->r4, 0X0);
    // 0x801DDB04: addiu       $t8, $t7, -0x1
    ctx->r24 = ADD32(ctx->r15, -0X1);
    // 0x801DDB08: sltiu       $at, $t8, 0x8
    ctx->r1 = ctx->r24 < 0X8 ? 1 : 0;
    // 0x801DDB0C: beq         $at, $zero, L_801DDDFC
    if (ctx->r1 == 0) {
        // 0x801DDB10: sll         $t8, $t8, 2
        ctx->r24 = S32(ctx->r24 << 2);
            goto L_801DDDFC;
    }
    // 0x801DDB10: sll         $t8, $t8, 2
    ctx->r24 = S32(ctx->r24 << 2);
    // 0x801DDB14: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801DDB18: addu        $at, $at, $t8
    gpr jr_addend_801DDB20 = ctx->r24;
    ctx->r1 = ADD32(ctx->r1, ctx->r24);
    // 0x801DDB1C: lw          $t8, 0x5F8C($at)
    ctx->r24 = ADD32(ctx->r1, 0X5F8C);
    // 0x801DDB20: jr          $t8
    // 0x801DDB24: nop

    switch (jr_addend_801DDB20 >> 2) {
        case 0: goto L_801DDB28; break;
        case 1: goto L_801DDB44; break;
        case 2: goto L_801DDBA8; break;
        case 3: goto L_801DDDFC; break;
        case 4: goto L_801DDC90; break;
        case 5: goto L_801DDDFC; break;
        case 6: goto L_801DDDFC; break;
        case 7: goto L_801DDDD4; break;
        default: switch_error(__func__, 0x801DDB20, 0x80225F8C);
    }
    // 0x801DDB24: nop

L_801DDB28:
    // 0x801DDB28: lui         $a1, 0x8022
    ctx->r5 = S32(0X8022 << 16);
    // 0x801DDB2C: addiu       $a1, $a1, 0x5A84
    ctx->r5 = ADD32(ctx->r5, 0X5A84);
    // 0x801DDB30: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x801DDB34: jal         0x801DF008
    // 0x801DDB38: sw          $a3, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r7;
    func_801DF008(rdram, ctx);
        goto after_0;
    // 0x801DDB38: sw          $a3, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r7;
    after_0:
    // 0x801DDB3C: b           L_801DDDFC
    // 0x801DDB40: lw          $a3, 0x28($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X28);
        goto L_801DDDFC;
    // 0x801DDB40: lw          $a3, 0x28($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X28);
L_801DDB44:
    // 0x801DDB44: lui         $a1, 0x8022
    ctx->r5 = S32(0X8022 << 16);
    // 0x801DDB48: addiu       $a1, $a1, 0x5AFC
    ctx->r5 = ADD32(ctx->r5, 0X5AFC);
    // 0x801DDB4C: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x801DDB50: jal         0x801DF5F0
    // 0x801DDB54: sw          $a3, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r7;
    func_801DF5F0(rdram, ctx);
        goto after_1;
    // 0x801DDB54: sw          $a3, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r7;
    after_1:
    // 0x801DDB58: lui         $at, 0x42C8
    ctx->r1 = S32(0X42C8 << 16);
    // 0x801DDB5C: mtc1        $at, $f0
    ctx->f0.u32l = ctx->r1;
    // 0x801DDB60: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801DDB64: lwc1        $f16, -0x7EF8($at)
    ctx->f16.u32l = MEM_W(ctx->r1, -0X7EF8);
    // 0x801DDB68: lw          $a3, 0x28($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X28);
    // 0x801DDB6C: lui         $at, 0x42B4
    ctx->r1 = S32(0X42B4 << 16);
    // 0x801DDB70: swc1        $f16, 0x68($s0)
    MEM_W(0X68, ctx->r16) = ctx->f16.u32l;
    // 0x801DDB74: lwc1        $f4, 0x1C($a3)
    ctx->f4.u32l = MEM_W(ctx->r7, 0X1C);
    // 0x801DDB78: lwc1        $f18, 0x4($a3)
    ctx->f18.u32l = MEM_W(ctx->r7, 0X4);
    // 0x801DDB7C: mul.s       $f6, $f4, $f0
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f6.fl = MUL_S(ctx->f4.fl, ctx->f0.fl);
    // 0x801DDB80: sub.s       $f8, $f18, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = ctx->f18.fl - ctx->f6.fl;
    // 0x801DDB84: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x801DDB88: swc1        $f8, 0x74($s0)
    MEM_W(0X74, ctx->r16) = ctx->f8.u32l;
    // 0x801DDB8C: lwc1        $f16, 0x24($a3)
    ctx->f16.u32l = MEM_W(ctx->r7, 0X24);
    // 0x801DDB90: lwc1        $f10, 0xC($a3)
    ctx->f10.u32l = MEM_W(ctx->r7, 0XC);
    // 0x801DDB94: swc1        $f6, 0xB4($s0)
    MEM_W(0XB4, ctx->r16) = ctx->f6.u32l;
    // 0x801DDB98: mul.s       $f4, $f16, $f0
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f4.fl = MUL_S(ctx->f16.fl, ctx->f0.fl);
    // 0x801DDB9C: sub.s       $f18, $f10, $f4
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f18.fl = ctx->f10.fl - ctx->f4.fl;
    // 0x801DDBA0: b           L_801DDDFC
    // 0x801DDBA4: swc1        $f18, 0x78($s0)
    MEM_W(0X78, ctx->r16) = ctx->f18.u32l;
        goto L_801DDDFC;
    // 0x801DDBA4: swc1        $f18, 0x78($s0)
    MEM_W(0X78, ctx->r16) = ctx->f18.u32l;
L_801DDBA8:
    // 0x801DDBA8: lui         $a1, 0x8022
    ctx->r5 = S32(0X8022 << 16);
    // 0x801DDBAC: addiu       $a1, $a1, 0x5BD8
    ctx->r5 = ADD32(ctx->r5, 0X5BD8);
    // 0x801DDBB0: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x801DDBB4: jal         0x801DF5F0
    // 0x801DDBB8: sw          $a3, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r7;
    func_801DF5F0(rdram, ctx);
        goto after_2;
    // 0x801DDBB8: sw          $a3, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r7;
    after_2:
    // 0x801DDBBC: lui         $at, 0x42C8
    ctx->r1 = S32(0X42C8 << 16);
    // 0x801DDBC0: mtc1        $at, $f0
    ctx->f0.u32l = ctx->r1;
    // 0x801DDBC4: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801DDBC8: lwc1        $f8, -0x7EF8($at)
    ctx->f8.u32l = MEM_W(ctx->r1, -0X7EF8);
    // 0x801DDBCC: lw          $a3, 0x28($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X28);
    // 0x801DDBD0: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x801DDBD4: swc1        $f8, 0x68($s0)
    MEM_W(0X68, ctx->r16) = ctx->f8.u32l;
    // 0x801DDBD8: lwc1        $f10, 0x1C($a3)
    ctx->f10.u32l = MEM_W(ctx->r7, 0X1C);
    // 0x801DDBDC: lwc1        $f16, 0x4($a3)
    ctx->f16.u32l = MEM_W(ctx->r7, 0X4);
    // 0x801DDBE0: addiu       $at, $zero, 0x7
    ctx->r1 = ADD32(0, 0X7);
    // 0x801DDBE4: mul.s       $f4, $f10, $f0
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f4.fl = MUL_S(ctx->f10.fl, ctx->f0.fl);
    // 0x801DDBE8: addiu       $t7, $zero, 0x4
    ctx->r15 = ADD32(0, 0X4);
    // 0x801DDBEC: sub.s       $f18, $f16, $f4
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f18.fl = ctx->f16.fl - ctx->f4.fl;
    // 0x801DDBF0: swc1        $f18, 0x74($s0)
    MEM_W(0X74, ctx->r16) = ctx->f18.u32l;
    // 0x801DDBF4: lwc1        $f8, 0x24($a3)
    ctx->f8.u32l = MEM_W(ctx->r7, 0X24);
    // 0x801DDBF8: lwc1        $f6, 0xC($a3)
    ctx->f6.u32l = MEM_W(ctx->r7, 0XC);
    // 0x801DDBFC: mul.s       $f10, $f8, $f0
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f10.fl = MUL_S(ctx->f8.fl, ctx->f0.fl);
    // 0x801DDC00: sub.s       $f16, $f6, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f16.fl = ctx->f6.fl - ctx->f10.fl;
    // 0x801DDC04: swc1        $f16, 0x78($s0)
    MEM_W(0X78, ctx->r16) = ctx->f16.u32l;
    // 0x801DDC08: lw          $v0, -0x54DC($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X54DC);
    // 0x801DDC0C: beq         $v0, $at, L_801DDC1C
    if (ctx->r2 == ctx->r1) {
        // 0x801DDC10: addiu       $at, $zero, 0x8
        ctx->r1 = ADD32(0, 0X8);
            goto L_801DDC1C;
    }
    // 0x801DDC10: addiu       $at, $zero, 0x8
    ctx->r1 = ADD32(0, 0X8);
    // 0x801DDC14: bnel        $v0, $at, L_801DDC2C
    if (ctx->r2 != ctx->r1) {
        // 0x801DDC18: lw          $t9, 0xEC($a3)
        ctx->r25 = MEM_W(ctx->r7, 0XEC);
            goto L_801DDC2C;
    }
    goto skip_0;
    // 0x801DDC18: lw          $t9, 0xEC($a3)
    ctx->r25 = MEM_W(ctx->r7, 0XEC);
    skip_0:
L_801DDC1C:
    // 0x801DDC1C: mtc1        $zero, $f0
    ctx->f0.u32l = 0;
    // 0x801DDC20: b           L_801DDC88
    // 0x801DDC24: swc1        $f0, 0xFC($a3)
    MEM_W(0XFC, ctx->r7) = ctx->f0.u32l;
        goto L_801DDC88;
    // 0x801DDC24: swc1        $f0, 0xFC($a3)
    MEM_W(0XFC, ctx->r7) = ctx->f0.u32l;
    // 0x801DDC28: lw          $t9, 0xEC($a3)
    ctx->r25 = MEM_W(ctx->r7, 0XEC);
L_801DDC2C:
    // 0x801DDC2C: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801DDC30: sll         $t0, $t9, 2
    ctx->r8 = S32(ctx->r25 << 2);
    // 0x801DDC34: addu        $at, $at, $t0
    ctx->r1 = ADD32(ctx->r1, ctx->r8);
    // 0x801DDC38: lwc1        $f4, 0x3940($at)
    ctx->f4.u32l = MEM_W(ctx->r1, 0X3940);
    // 0x801DDC3C: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801DDC40: swc1        $f4, 0x38($s0)
    MEM_W(0X38, ctx->r16) = ctx->f4.u32l;
    // 0x801DDC44: lw          $t1, 0xEC($a3)
    ctx->r9 = MEM_W(ctx->r7, 0XEC);
    // 0x801DDC48: sll         $t2, $t1, 2
    ctx->r10 = S32(ctx->r9 << 2);
    // 0x801DDC4C: addu        $at, $at, $t2
    ctx->r1 = ADD32(ctx->r1, ctx->r10);
    // 0x801DDC50: lwc1        $f18, 0x3950($at)
    ctx->f18.u32l = MEM_W(ctx->r1, 0X3950);
    // 0x801DDC54: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801DDC58: swc1        $f18, 0xA4($s0)
    MEM_W(0XA4, ctx->r16) = ctx->f18.u32l;
    // 0x801DDC5C: lw          $t3, 0xEC($a3)
    ctx->r11 = MEM_W(ctx->r7, 0XEC);
    // 0x801DDC60: sll         $t4, $t3, 2
    ctx->r12 = S32(ctx->r11 << 2);
    // 0x801DDC64: addu        $at, $at, $t4
    ctx->r1 = ADD32(ctx->r1, ctx->r12);
    // 0x801DDC68: lwc1        $f8, 0x3960($at)
    ctx->f8.u32l = MEM_W(ctx->r1, 0X3960);
    // 0x801DDC6C: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801DDC70: swc1        $f8, 0xBC($s0)
    MEM_W(0XBC, ctx->r16) = ctx->f8.u32l;
    // 0x801DDC74: lw          $t5, 0xEC($a3)
    ctx->r13 = MEM_W(ctx->r7, 0XEC);
    // 0x801DDC78: sll         $t6, $t5, 2
    ctx->r14 = S32(ctx->r13 << 2);
    // 0x801DDC7C: addu        $at, $at, $t6
    ctx->r1 = ADD32(ctx->r1, ctx->r14);
    // 0x801DDC80: lwc1        $f6, 0x3970($at)
    ctx->f6.u32l = MEM_W(ctx->r1, 0X3970);
    // 0x801DDC84: swc1        $f6, 0xFC($a3)
    MEM_W(0XFC, ctx->r7) = ctx->f6.u32l;
L_801DDC88:
    // 0x801DDC88: b           L_801DDDFC
    // 0x801DDC8C: sw          $t7, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r15;
        goto L_801DDDFC;
    // 0x801DDC8C: sw          $t7, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r15;
L_801DDC90:
    // 0x801DDC90: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x801DDC94: lw          $v0, -0x19C8($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X19C8);
    // 0x801DDC98: addiu       $at, $zero, 0x8
    ctx->r1 = ADD32(0, 0X8);
    // 0x801DDC9C: addiu       $t9, $zero, 0x6
    ctx->r25 = ADD32(0, 0X6);
    // 0x801DDCA0: beq         $v0, $zero, L_801DDCB8
    if (ctx->r2 == 0) {
        // 0x801DDCA4: lui         $t0, 0x800E
        ctx->r8 = S32(0X800E << 16);
            goto L_801DDCB8;
    }
    // 0x801DDCA4: lui         $t0, 0x800E
    ctx->r8 = S32(0X800E << 16);
    // 0x801DDCA8: beql        $v0, $at, L_801DDCC8
    if (ctx->r2 == ctx->r1) {
        // 0x801DDCAC: sw          $t9, 0x0($a3)
        MEM_W(0X0, ctx->r7) = ctx->r25;
            goto L_801DDCC8;
    }
    goto skip_1;
    // 0x801DDCAC: sw          $t9, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r25;
    skip_1:
    // 0x801DDCB0: b           L_801DDCC8
    // 0x801DDCB4: sw          $t9, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r25;
        goto L_801DDCC8;
    // 0x801DDCB4: sw          $t9, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r25;
L_801DDCB8:
    // 0x801DDCB8: addiu       $t8, $zero, 0x3
    ctx->r24 = ADD32(0, 0X3);
    // 0x801DDCBC: b           L_801DDBA8
    // 0x801DDCC0: sw          $t8, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r24;
        goto L_801DDBA8;
    // 0x801DDCC0: sw          $t8, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r24;
    // 0x801DDCC4: sw          $t9, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r25;
L_801DDCC8:
    // 0x801DDCC8: lw          $t0, -0x7E90($t0)
    ctx->r8 = MEM_W(ctx->r8, -0X7E90);
    // 0x801DDCCC: sltiu       $at, $t0, 0x9
    ctx->r1 = ctx->r8 < 0X9 ? 1 : 0;
    // 0x801DDCD0: beq         $at, $zero, L_801DDDBC
    if (ctx->r1 == 0) {
        // 0x801DDCD4: sll         $t0, $t0, 2
        ctx->r8 = S32(ctx->r8 << 2);
            goto L_801DDDBC;
    }
    // 0x801DDCD4: sll         $t0, $t0, 2
    ctx->r8 = S32(ctx->r8 << 2);
    // 0x801DDCD8: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801DDCDC: addu        $at, $at, $t0
    gpr jr_addend_801DDCE4 = ctx->r8;
    ctx->r1 = ADD32(ctx->r1, ctx->r8);
    // 0x801DDCE0: lw          $t0, 0x5FAC($at)
    ctx->r8 = ADD32(ctx->r1, 0X5FAC);
    // 0x801DDCE4: jr          $t0
    // 0x801DDCE8: nop

    switch (jr_addend_801DDCE4 >> 2) {
        case 0: goto L_801DDCEC; break;
        case 1: goto L_801DDCFC; break;
        case 2: goto L_801DDD50; break;
        case 3: goto L_801DDD60; break;
        case 4: goto L_801DDD70; break;
        case 5: goto L_801DDD80; break;
        case 6: goto L_801DDD90; break;
        case 7: goto L_801DDDA0; break;
        case 8: goto L_801DDDB0; break;
        default: switch_error(__func__, 0x801DDCE4, 0x80225FAC);
    }
    // 0x801DDCE8: nop

L_801DDCEC:
    // 0x801DDCEC: lui         $t1, 0x8022
    ctx->r9 = S32(0X8022 << 16);
    // 0x801DDCF0: addiu       $t1, $t1, 0x3A30
    ctx->r9 = ADD32(ctx->r9, 0X3A30);
    // 0x801DDCF4: b           L_801DDDBC
    // 0x801DDCF8: sw          $t1, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r9;
        goto L_801DDDBC;
    // 0x801DDCF8: sw          $t1, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r9;
L_801DDCFC:
    // 0x801DDCFC: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x801DDD00: lw          $v0, -0x4CC8($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X4CC8);
    // 0x801DDD04: lui         $t2, 0x8022
    ctx->r10 = S32(0X8022 << 16);
    // 0x801DDD08: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x801DDD0C: beq         $v0, $zero, L_801DDD30
    if (ctx->r2 == 0) {
        // 0x801DDD10: addiu       $t2, $t2, 0x3D38
        ctx->r10 = ADD32(ctx->r10, 0X3D38);
            goto L_801DDD30;
    }
    // 0x801DDD10: addiu       $t2, $t2, 0x3D38
    ctx->r10 = ADD32(ctx->r10, 0X3D38);
    // 0x801DDD14: beq         $v0, $at, L_801DDD38
    if (ctx->r2 == ctx->r1) {
        // 0x801DDD18: lui         $t3, 0x8022
        ctx->r11 = S32(0X8022 << 16);
            goto L_801DDD38;
    }
    // 0x801DDD18: lui         $t3, 0x8022
    ctx->r11 = S32(0X8022 << 16);
    // 0x801DDD1C: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x801DDD20: beq         $v0, $at, L_801DDD44
    if (ctx->r2 == ctx->r1) {
        // 0x801DDD24: lui         $t4, 0x8022
        ctx->r12 = S32(0X8022 << 16);
            goto L_801DDD44;
    }
    // 0x801DDD24: lui         $t4, 0x8022
    ctx->r12 = S32(0X8022 << 16);
    // 0x801DDD28: b           L_801DDDC0
    // 0x801DDD2C: or          $a0, $a2, $zero
    ctx->r4 = ctx->r6 | 0;
        goto L_801DDDC0;
    // 0x801DDD2C: or          $a0, $a2, $zero
    ctx->r4 = ctx->r6 | 0;
L_801DDD30:
    // 0x801DDD30: b           L_801DDDBC
    // 0x801DDD34: sw          $t2, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r10;
        goto L_801DDDBC;
    // 0x801DDD34: sw          $t2, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r10;
L_801DDD38:
    // 0x801DDD38: addiu       $t3, $t3, 0x4944
    ctx->r11 = ADD32(ctx->r11, 0X4944);
    // 0x801DDD3C: b           L_801DDDBC
    // 0x801DDD40: sw          $t3, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r11;
        goto L_801DDDBC;
    // 0x801DDD40: sw          $t3, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r11;
L_801DDD44:
    // 0x801DDD44: addiu       $t4, $t4, 0x4B14
    ctx->r12 = ADD32(ctx->r12, 0X4B14);
    // 0x801DDD48: b           L_801DDDBC
    // 0x801DDD4C: sw          $t4, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r12;
        goto L_801DDDBC;
    // 0x801DDD4C: sw          $t4, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r12;
L_801DDD50:
    // 0x801DDD50: lui         $t5, 0x8022
    ctx->r13 = S32(0X8022 << 16);
    // 0x801DDD54: addiu       $t5, $t5, 0x3F7C
    ctx->r13 = ADD32(ctx->r13, 0X3F7C);
    // 0x801DDD58: b           L_801DDDBC
    // 0x801DDD5C: sw          $t5, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r13;
        goto L_801DDDBC;
    // 0x801DDD5C: sw          $t5, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r13;
L_801DDD60:
    // 0x801DDD60: lui         $t6, 0x8022
    ctx->r14 = S32(0X8022 << 16);
    // 0x801DDD64: addiu       $t6, $t6, 0x4060
    ctx->r14 = ADD32(ctx->r14, 0X4060);
    // 0x801DDD68: b           L_801DDDBC
    // 0x801DDD6C: sw          $t6, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r14;
        goto L_801DDDBC;
    // 0x801DDD6C: sw          $t6, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r14;
L_801DDD70:
    // 0x801DDD70: lui         $t7, 0x8022
    ctx->r15 = S32(0X8022 << 16);
    // 0x801DDD74: addiu       $t7, $t7, 0x41E0
    ctx->r15 = ADD32(ctx->r15, 0X41E0);
    // 0x801DDD78: b           L_801DDDBC
    // 0x801DDD7C: sw          $t7, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r15;
        goto L_801DDDBC;
    // 0x801DDD7C: sw          $t7, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r15;
L_801DDD80:
    // 0x801DDD80: lui         $t8, 0x8022
    ctx->r24 = S32(0X8022 << 16);
    // 0x801DDD84: addiu       $t8, $t8, 0x42C0
    ctx->r24 = ADD32(ctx->r24, 0X42C0);
    // 0x801DDD88: b           L_801DDDBC
    // 0x801DDD8C: sw          $t8, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r24;
        goto L_801DDDBC;
    // 0x801DDD8C: sw          $t8, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r24;
L_801DDD90:
    // 0x801DDD90: lui         $t9, 0x8022
    ctx->r25 = S32(0X8022 << 16);
    // 0x801DDD94: addiu       $t9, $t9, 0x4430
    ctx->r25 = ADD32(ctx->r25, 0X4430);
    // 0x801DDD98: b           L_801DDDBC
    // 0x801DDD9C: sw          $t9, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r25;
        goto L_801DDDBC;
    // 0x801DDD9C: sw          $t9, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r25;
L_801DDDA0:
    // 0x801DDDA0: lui         $t0, 0x8022
    ctx->r8 = S32(0X8022 << 16);
    // 0x801DDDA4: addiu       $t0, $t0, 0x45B4
    ctx->r8 = ADD32(ctx->r8, 0X45B4);
    // 0x801DDDA8: b           L_801DDDBC
    // 0x801DDDAC: sw          $t0, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r8;
        goto L_801DDDBC;
    // 0x801DDDAC: sw          $t0, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r8;
L_801DDDB0:
    // 0x801DDDB0: lui         $t1, 0x8022
    ctx->r9 = S32(0X8022 << 16);
    // 0x801DDDB4: addiu       $t1, $t1, 0x46B4
    ctx->r9 = ADD32(ctx->r9, 0X46B4);
    // 0x801DDDB8: sw          $t1, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r9;
L_801DDDBC:
    // 0x801DDDBC: or          $a0, $a2, $zero
    ctx->r4 = ctx->r6 | 0;
L_801DDDC0:
    // 0x801DDDC0: lw          $a1, 0x24($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X24);
    // 0x801DDDC4: jal         0x801DFD94
    // 0x801DDDC8: sw          $a3, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r7;
    func_801DFD94(rdram, ctx);
        goto after_3;
    // 0x801DDDC8: sw          $a3, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r7;
    after_3:
    // 0x801DDDCC: b           L_801DDDFC
    // 0x801DDDD0: lw          $a3, 0x28($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X28);
        goto L_801DDDFC;
    // 0x801DDDD0: lw          $a3, 0x28($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X28);
L_801DDDD4:
    // 0x801DDDD4: lui         $at, 0x4200
    ctx->r1 = S32(0X4200 << 16);
    // 0x801DDDD8: mtc1        $at, $f10
    ctx->f10.u32l = ctx->r1;
    // 0x801DDDDC: mtc1        $zero, $f0
    ctx->f0.u32l = 0;
    // 0x801DDDE0: sw          $zero, 0x8($a2)
    MEM_W(0X8, ctx->r6) = 0;
    // 0x801DDDE4: lui         $at, 0x4580
    ctx->r1 = S32(0X4580 << 16);
    // 0x801DDDE8: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
    // 0x801DDDEC: swc1        $f10, 0x9C($a3)
    MEM_W(0X9C, ctx->r7) = ctx->f10.u32l;
    // 0x801DDDF0: swc1        $f0, 0x94($a3)
    MEM_W(0X94, ctx->r7) = ctx->f0.u32l;
    // 0x801DDDF4: swc1        $f0, 0x98($a3)
    MEM_W(0X98, ctx->r7) = ctx->f0.u32l;
    // 0x801DDDF8: swc1        $f16, 0xA0($a3)
    MEM_W(0XA0, ctx->r7) = ctx->f16.u32l;
L_801DDDFC:
    // 0x801DDDFC: or          $a0, $a3, $zero
    ctx->r4 = ctx->r7 | 0;
    // 0x801DDE00: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    // 0x801DDE04: jal         0x801E0F8C
    // 0x801DDE08: sw          $a3, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r7;
    func_801E0F8C(rdram, ctx);
        goto after_4;
    // 0x801DDE08: sw          $a3, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r7;
    after_4:
    // 0x801DDE0C: jal         0x801E0FF0
    // 0x801DDE10: lw          $a0, 0x28($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X28);
    func_801E0FF0(rdram, ctx);
        goto after_5;
    // 0x801DDE10: lw          $a0, 0x28($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X28);
    after_5:
    // 0x801DDE14: lui         $a0, 0x8012
    ctx->r4 = S32(0X8012 << 16);
    // 0x801DDE18: lw          $a1, 0x28($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X28);
    // 0x801DDE1C: jal         0x801E11B4
    // 0x801DDE20: addiu       $a0, $a0, -0x718
    ctx->r4 = ADD32(ctx->r4, -0X718);
    func_801E11B4(rdram, ctx);
        goto after_6;
    // 0x801DDE20: addiu       $a0, $a0, -0x718
    ctx->r4 = ADD32(ctx->r4, -0X718);
    after_6:
    // 0x801DDE24: lui         $a0, 0x8014
    ctx->r4 = S32(0X8014 << 16);
    // 0x801DDE28: lw          $a1, 0x28($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X28);
    // 0x801DDE2C: jal         0x801E11B4
    // 0x801DDE30: addiu       $a0, $a0, -0x7730
    ctx->r4 = ADD32(ctx->r4, -0X7730);
    func_801E11B4(rdram, ctx);
        goto after_7;
    // 0x801DDE30: addiu       $a0, $a0, -0x7730
    ctx->r4 = ADD32(ctx->r4, -0X7730);
    after_7:
    // 0x801DDE34: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    // 0x801DDE38: lw          $s0, 0x18($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X18);
    // 0x801DDE3C: addiu       $sp, $sp, 0x28
    ctx->r29 = ADD32(ctx->r29, 0X28);
    // 0x801DDE40: jr          $ra
    // 0x801DDE44: nop

    return;
    // 0x801DDE44: nop

;}
RECOMP_FUNC void func_801DDE48(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801DDE48: addiu       $sp, $sp, -0x30
    ctx->r29 = ADD32(ctx->r29, -0X30);
    // 0x801DDE4C: sw          $s4, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r20;
    // 0x801DDE50: lui         $s4, 0x800E
    ctx->r20 = S32(0X800E << 16);
    // 0x801DDE54: addiu       $s4, $s4, -0x54D8
    ctx->r20 = ADD32(ctx->r20, -0X54D8);
    // 0x801DDE58: lw          $t6, 0x0($s4)
    ctx->r14 = MEM_W(ctx->r20, 0X0);
    // 0x801DDE5C: sw          $s0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r16;
    // 0x801DDE60: sw          $ra, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r31;
    // 0x801DDE64: sw          $s3, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r19;
    // 0x801DDE68: sw          $s2, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r18;
    // 0x801DDE6C: sw          $s1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r17;
    // 0x801DDE70: blez        $t6, L_801DDEBC
    if (SIGNED(ctx->r14) <= 0) {
        // 0x801DDE74: or          $s0, $zero, $zero
        ctx->r16 = 0 | 0;
            goto L_801DDEBC;
    }
    // 0x801DDE74: or          $s0, $zero, $zero
    ctx->r16 = 0 | 0;
    // 0x801DDE78: lui         $s1, 0x8022
    ctx->r17 = S32(0X8022 << 16);
    // 0x801DDE7C: lui         $s2, 0x8022
    ctx->r18 = S32(0X8022 << 16);
    // 0x801DDE80: lui         $s3, 0x8023
    ctx->r19 = S32(0X8023 << 16);
    // 0x801DDE84: addiu       $s3, $s3, -0x7FA8
    ctx->r19 = ADD32(ctx->r19, -0X7FA8);
    // 0x801DDE88: addiu       $s2, $s2, 0x7E98
    ctx->r18 = ADD32(ctx->r18, 0X7E98);
    // 0x801DDE8C: addiu       $s1, $s1, 0x7C80
    ctx->r17 = ADD32(ctx->r17, 0X7C80);
L_801DDE90:
    // 0x801DDE90: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    // 0x801DDE94: or          $a1, $s2, $zero
    ctx->r5 = ctx->r18 | 0;
    // 0x801DDE98: jal         0x801DDEDC
    // 0x801DDE9C: or          $a2, $s3, $zero
    ctx->r6 = ctx->r19 | 0;
    func_801DDEDC(rdram, ctx);
        goto after_0;
    // 0x801DDE9C: or          $a2, $s3, $zero
    ctx->r6 = ctx->r19 | 0;
    after_0:
    // 0x801DDEA0: lw          $t7, 0x0($s4)
    ctx->r15 = MEM_W(ctx->r20, 0X0);
    // 0x801DDEA4: addiu       $s0, $s0, 0x1
    ctx->r16 = ADD32(ctx->r16, 0X1);
    // 0x801DDEA8: addiu       $s1, $s1, 0x10C
    ctx->r17 = ADD32(ctx->r17, 0X10C);
    // 0x801DDEAC: slt         $at, $s0, $t7
    ctx->r1 = SIGNED(ctx->r16) < SIGNED(ctx->r15) ? 1 : 0;
    // 0x801DDEB0: addiu       $s2, $s2, 0xE0
    ctx->r18 = ADD32(ctx->r18, 0XE0);
    // 0x801DDEB4: bne         $at, $zero, L_801DDE90
    if (ctx->r1 != 0) {
        // 0x801DDEB8: addiu       $s3, $s3, 0x38
        ctx->r19 = ADD32(ctx->r19, 0X38);
            goto L_801DDE90;
    }
    // 0x801DDEB8: addiu       $s3, $s3, 0x38
    ctx->r19 = ADD32(ctx->r19, 0X38);
L_801DDEBC:
    // 0x801DDEBC: lw          $ra, 0x2C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X2C);
    // 0x801DDEC0: lw          $s0, 0x18($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X18);
    // 0x801DDEC4: lw          $s1, 0x1C($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X1C);
    // 0x801DDEC8: lw          $s2, 0x20($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X20);
    // 0x801DDECC: lw          $s3, 0x24($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X24);
    // 0x801DDED0: lw          $s4, 0x28($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X28);
    // 0x801DDED4: jr          $ra
    // 0x801DDED8: addiu       $sp, $sp, 0x30
    ctx->r29 = ADD32(ctx->r29, 0X30);
    return;
    // 0x801DDED8: addiu       $sp, $sp, 0x30
    ctx->r29 = ADD32(ctx->r29, 0X30);
;}
RECOMP_FUNC void func_801DDEDC(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801DDEDC: lui         $t6, 0x8019
    ctx->r14 = S32(0X8019 << 16);
    // 0x801DDEE0: lw          $t6, 0x2458($t6)
    ctx->r14 = MEM_W(ctx->r14, 0X2458);
    // 0x801DDEE4: addiu       $sp, $sp, -0x38
    ctx->r29 = ADD32(ctx->r29, -0X38);
    // 0x801DDEE8: lui         $v1, 0x8023
    ctx->r3 = S32(0X8023 << 16);
    // 0x801DDEEC: mtc1        $t6, $f4
    ctx->f4.u32l = ctx->r14;
    // 0x801DDEF0: addiu       $v1, $v1, -0x7EF8
    ctx->r3 = ADD32(ctx->r3, -0X7EF8);
    // 0x801DDEF4: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x801DDEF8: cvt.s.w     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
    // 0x801DDEFC: sw          $s1, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r17;
    // 0x801DDF00: sw          $s0, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r16;
    // 0x801DDF04: or          $s0, $a1, $zero
    ctx->r16 = ctx->r5 | 0;
    // 0x801DDF08: or          $s1, $a0, $zero
    ctx->r17 = ctx->r4 | 0;
    // 0x801DDF0C: swc1        $f6, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->f6.u32l;
    // 0x801DDF10: lwc1        $f8, 0x4C($a0)
    ctx->f8.u32l = MEM_W(ctx->r4, 0X4C);
    // 0x801DDF14: swc1        $f8, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->f8.u32l;
    // 0x801DDF18: lwc1        $f10, 0x50($a0)
    ctx->f10.u32l = MEM_W(ctx->r4, 0X50);
    // 0x801DDF1C: swc1        $f10, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->f10.u32l;
    // 0x801DDF20: lwc1        $f16, 0x54($a0)
    ctx->f16.u32l = MEM_W(ctx->r4, 0X54);
    // 0x801DDF24: swc1        $f16, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->f16.u32l;
    // 0x801DDF28: lw          $t7, 0x0($a0)
    ctx->r15 = MEM_W(ctx->r4, 0X0);
    // 0x801DDF2C: addiu       $t8, $t7, -0x1
    ctx->r24 = ADD32(ctx->r15, -0X1);
    // 0x801DDF30: sltiu       $at, $t8, 0x8
    ctx->r1 = ctx->r24 < 0X8 ? 1 : 0;
    // 0x801DDF34: beq         $at, $zero, L_801DE34C
    if (ctx->r1 == 0) {
        // 0x801DDF38: sll         $t8, $t8, 2
        ctx->r24 = S32(ctx->r24 << 2);
            goto L_801DE34C;
    }
    // 0x801DDF38: sll         $t8, $t8, 2
    ctx->r24 = S32(ctx->r24 << 2);
    // 0x801DDF3C: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801DDF40: addu        $at, $at, $t8
    gpr jr_addend_801DDF48 = ctx->r24;
    ctx->r1 = ADD32(ctx->r1, ctx->r24);
    // 0x801DDF44: lw          $t8, 0x5FD0($at)
    ctx->r24 = ADD32(ctx->r1, 0X5FD0);
    // 0x801DDF48: jr          $t8
    // 0x801DDF4C: nop

    switch (jr_addend_801DDF48 >> 2) {
        case 0: goto L_801DE34C; break;
        case 1: goto L_801DDF50; break;
        case 2: goto L_801DE34C; break;
        case 3: goto L_801DDFA8; break;
        case 4: goto L_801DE34C; break;
        case 5: goto L_801DE310; break;
        case 6: goto L_801DE10C; break;
        case 7: goto L_801DE32C; break;
        default: switch_error(__func__, 0x801DDF48, 0x80225FD0);
    }
    // 0x801DDF4C: nop

L_801DDF50:
    // 0x801DDF50: lwc1        $f18, 0x4($s1)
    ctx->f18.u32l = MEM_W(ctx->r17, 0X4);
    // 0x801DDF54: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x801DDF58: mtc1        $at, $f2
    ctx->f2.u32l = ctx->r1;
    // 0x801DDF5C: lui         $at, 0x41F0
    ctx->r1 = S32(0X41F0 << 16);
    // 0x801DDF60: swc1        $f18, 0x5C($s0)
    MEM_W(0X5C, ctx->r16) = ctx->f18.u32l;
    // 0x801DDF64: lwc1        $f4, 0x8($s1)
    ctx->f4.u32l = MEM_W(ctx->r17, 0X8);
    // 0x801DDF68: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x801DDF6C: nop

    // 0x801DDF70: add.s       $f8, $f4, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = ctx->f4.fl + ctx->f6.fl;
    // 0x801DDF74: lwc1        $f6, 0xB4($s0)
    ctx->f6.u32l = MEM_W(ctx->r16, 0XB4);
    // 0x801DDF78: swc1        $f8, 0x60($s0)
    MEM_W(0X60, ctx->r16) = ctx->f8.u32l;
    // 0x801DDF7C: lwc1        $f10, 0xC($s1)
    ctx->f10.u32l = MEM_W(ctx->r17, 0XC);
    // 0x801DDF80: add.s       $f8, $f6, $f2
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f8.fl = ctx->f6.fl + ctx->f2.fl;
    // 0x801DDF84: swc1        $f10, 0x64($s0)
    MEM_W(0X64, ctx->r16) = ctx->f10.u32l;
    // 0x801DDF88: lwc1        $f16, 0x0($v1)
    ctx->f16.u32l = MEM_W(ctx->r3, 0X0);
    // 0x801DDF8C: swc1        $f16, 0x68($s0)
    MEM_W(0X68, ctx->r16) = ctx->f16.u32l;
    // 0x801DDF90: lwc1        $f18, 0x1C($s1)
    ctx->f18.u32l = MEM_W(ctx->r17, 0X1C);
    // 0x801DDF94: swc1        $f18, 0x80($s0)
    MEM_W(0X80, ctx->r16) = ctx->f18.u32l;
    // 0x801DDF98: lwc1        $f4, 0x24($s1)
    ctx->f4.u32l = MEM_W(ctx->r17, 0X24);
    // 0x801DDF9C: swc1        $f8, 0xB4($s0)
    MEM_W(0XB4, ctx->r16) = ctx->f8.u32l;
    // 0x801DDFA0: b           L_801DE34C
    // 0x801DDFA4: swc1        $f4, 0x84($s0)
    MEM_W(0X84, ctx->r16) = ctx->f4.u32l;
        goto L_801DE34C;
    // 0x801DDFA4: swc1        $f4, 0x84($s0)
    MEM_W(0X84, ctx->r16) = ctx->f4.u32l;
L_801DDFA8:
    // 0x801DDFA8: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x801DDFAC: lw          $v0, -0x19E0($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X19E0);
    // 0x801DDFB0: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x801DDFB4: addiu       $at, $zero, 0x4
    ctx->r1 = ADD32(0, 0X4);
    // 0x801DDFB8: beql        $v0, $zero, L_801DDFD4
    if (ctx->r2 == 0) {
        // 0x801DDFBC: lw          $t9, 0xE8($s1)
        ctx->r25 = MEM_W(ctx->r17, 0XE8);
            goto L_801DDFD4;
    }
    goto skip_0;
    // 0x801DDFBC: lw          $t9, 0xE8($s1)
    ctx->r25 = MEM_W(ctx->r17, 0XE8);
    skip_0:
    // 0x801DDFC0: beq         $v0, $at, L_801DDFD0
    if (ctx->r2 == ctx->r1) {
        // 0x801DDFC4: addiu       $at, $zero, 0xB
        ctx->r1 = ADD32(0, 0XB);
            goto L_801DDFD0;
    }
    // 0x801DDFC4: addiu       $at, $zero, 0xB
    ctx->r1 = ADD32(0, 0XB);
    // 0x801DDFC8: bne         $v0, $at, L_801DE06C
    if (ctx->r2 != ctx->r1) {
        // 0x801DDFCC: nop
    
            goto L_801DE06C;
    }
    // 0x801DDFCC: nop

L_801DDFD0:
    // 0x801DDFD0: lw          $t9, 0xE8($s1)
    ctx->r25 = MEM_W(ctx->r17, 0XE8);
L_801DDFD4:
    // 0x801DDFD4: lui         $t1, 0x8019
    ctx->r9 = S32(0X8019 << 16);
    // 0x801DDFD8: sll         $t0, $t9, 2
    ctx->r8 = S32(ctx->r25 << 2);
    // 0x801DDFDC: subu        $t0, $t0, $t9
    ctx->r8 = SUB32(ctx->r8, ctx->r25);
    // 0x801DDFE0: sll         $t0, $t0, 3
    ctx->r8 = S32(ctx->r8 << 3);
    // 0x801DDFE4: subu        $t0, $t0, $t9
    ctx->r8 = SUB32(ctx->r8, ctx->r25);
    // 0x801DDFE8: sll         $t0, $t0, 3
    ctx->r8 = S32(ctx->r8 << 3);
    // 0x801DDFEC: addu        $t0, $t0, $t9
    ctx->r8 = ADD32(ctx->r8, ctx->r25);
    // 0x801DDFF0: sll         $t0, $t0, 2
    ctx->r8 = S32(ctx->r8 << 2);
    // 0x801DDFF4: subu        $t0, $t0, $t9
    ctx->r8 = SUB32(ctx->r8, ctx->r25);
    // 0x801DDFF8: sll         $t0, $t0, 3
    ctx->r8 = S32(ctx->r8 << 3);
    // 0x801DDFFC: addu        $t1, $t1, $t0
    ctx->r9 = ADD32(ctx->r9, ctx->r8);
    // 0x801DE000: lw          $t1, 0x3D58($t1)
    ctx->r9 = MEM_W(ctx->r9, 0X3D58);
    // 0x801DE004: addiu       $t2, $t1, -0x1
    ctx->r10 = ADD32(ctx->r9, -0X1);
    // 0x801DE008: sltiu       $at, $t2, 0x6
    ctx->r1 = ctx->r10 < 0X6 ? 1 : 0;
    // 0x801DE00C: beq         $at, $zero, L_801DE06C
    if (ctx->r1 == 0) {
        // 0x801DE010: sll         $t2, $t2, 2
        ctx->r10 = S32(ctx->r10 << 2);
            goto L_801DE06C;
    }
    // 0x801DE010: sll         $t2, $t2, 2
    ctx->r10 = S32(ctx->r10 << 2);
    // 0x801DE014: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801DE018: addu        $at, $at, $t2
    gpr jr_addend_801DE020 = ctx->r10;
    ctx->r1 = ADD32(ctx->r1, ctx->r10);
    // 0x801DE01C: lw          $t2, 0x5FF0($at)
    ctx->r10 = ADD32(ctx->r1, 0X5FF0);
    // 0x801DE020: jr          $t2
    // 0x801DE024: nop

    switch (jr_addend_801DE020 >> 2) {
        case 0: goto L_801DE028; break;
        case 1: goto L_801DE034; break;
        case 2: goto L_801DE040; break;
        case 3: goto L_801DE04C; break;
        case 4: goto L_801DE058; break;
        case 5: goto L_801DE064; break;
        default: switch_error(__func__, 0x801DE020, 0x80225FF0);
    }
    // 0x801DE024: nop

L_801DE028:
    // 0x801DE028: lui         $a1, 0x8022
    ctx->r5 = S32(0X8022 << 16);
    // 0x801DE02C: b           L_801DE06C
    // 0x801DE030: addiu       $a1, $a1, 0x4D9C
    ctx->r5 = ADD32(ctx->r5, 0X4D9C);
        goto L_801DE06C;
    // 0x801DE030: addiu       $a1, $a1, 0x4D9C
    ctx->r5 = ADD32(ctx->r5, 0X4D9C);
L_801DE034:
    // 0x801DE034: lui         $a1, 0x8022
    ctx->r5 = S32(0X8022 << 16);
    // 0x801DE038: b           L_801DE06C
    // 0x801DE03C: addiu       $a1, $a1, 0x4F98
    ctx->r5 = ADD32(ctx->r5, 0X4F98);
        goto L_801DE06C;
    // 0x801DE03C: addiu       $a1, $a1, 0x4F98
    ctx->r5 = ADD32(ctx->r5, 0X4F98);
L_801DE040:
    // 0x801DE040: lui         $a1, 0x8022
    ctx->r5 = S32(0X8022 << 16);
    // 0x801DE044: b           L_801DE06C
    // 0x801DE048: addiu       $a1, $a1, 0x512C
    ctx->r5 = ADD32(ctx->r5, 0X512C);
        goto L_801DE06C;
    // 0x801DE048: addiu       $a1, $a1, 0x512C
    ctx->r5 = ADD32(ctx->r5, 0X512C);
L_801DE04C:
    // 0x801DE04C: lui         $a1, 0x8022
    ctx->r5 = S32(0X8022 << 16);
    // 0x801DE050: b           L_801DE06C
    // 0x801DE054: addiu       $a1, $a1, 0x52B4
    ctx->r5 = ADD32(ctx->r5, 0X52B4);
        goto L_801DE06C;
    // 0x801DE054: addiu       $a1, $a1, 0x52B4
    ctx->r5 = ADD32(ctx->r5, 0X52B4);
L_801DE058:
    // 0x801DE058: lui         $a1, 0x8022
    ctx->r5 = S32(0X8022 << 16);
    // 0x801DE05C: b           L_801DE06C
    // 0x801DE060: addiu       $a1, $a1, 0x54F4
    ctx->r5 = ADD32(ctx->r5, 0X54F4);
        goto L_801DE06C;
    // 0x801DE060: addiu       $a1, $a1, 0x54F4
    ctx->r5 = ADD32(ctx->r5, 0X54F4);
L_801DE064:
    // 0x801DE064: lui         $a1, 0x8022
    ctx->r5 = S32(0X8022 << 16);
    // 0x801DE068: addiu       $a1, $a1, 0x5804
    ctx->r5 = ADD32(ctx->r5, 0X5804);
L_801DE06C:
    // 0x801DE06C: beq         $a1, $zero, L_801DE0B0
    if (ctx->r5 == 0) {
        // 0x801DE070: lui         $at, 0x3F80
        ctx->r1 = S32(0X3F80 << 16);
            goto L_801DE0B0;
    }
    // 0x801DE070: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x801DE074: mtc1        $zero, $f0
    ctx->f0.u32l = 0;
    // 0x801DE078: mtc1        $at, $f2
    ctx->f2.u32l = ctx->r1;
    // 0x801DE07C: sw          $zero, 0xDC($s0)
    MEM_W(0XDC, ctx->r16) = 0;
    // 0x801DE080: swc1        $f0, 0x28($s0)
    MEM_W(0X28, ctx->r16) = ctx->f0.u32l;
    // 0x801DE084: swc1        $f0, 0x30($s0)
    MEM_W(0X30, ctx->r16) = ctx->f0.u32l;
    // 0x801DE088: swc1        $f2, 0x2C($s0)
    MEM_W(0X2C, ctx->r16) = ctx->f2.u32l;
    // 0x801DE08C: sw          $a2, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r6;
    // 0x801DE090: jal         0x801DFD94
    // 0x801DE094: or          $a0, $a2, $zero
    ctx->r4 = ctx->r6 | 0;
    func_801DFD94(rdram, ctx);
        goto after_0;
    // 0x801DE094: or          $a0, $a2, $zero
    ctx->r4 = ctx->r6 | 0;
    after_0:
    // 0x801DE098: lui         $v1, 0x8023
    ctx->r3 = S32(0X8023 << 16);
    // 0x801DE09C: lw          $a2, 0x40($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X40);
    // 0x801DE0A0: addiu       $t3, $zero, 0x7
    ctx->r11 = ADD32(0, 0X7);
    // 0x801DE0A4: addiu       $v1, $v1, -0x7EF8
    ctx->r3 = ADD32(ctx->r3, -0X7EF8);
    // 0x801DE0A8: b           L_801DE10C
    // 0x801DE0AC: sw          $t3, 0x0($s1)
    MEM_W(0X0, ctx->r17) = ctx->r11;
        goto L_801DE10C;
    // 0x801DE0AC: sw          $t3, 0x0($s1)
    MEM_W(0X0, ctx->r17) = ctx->r11;
L_801DE0B0:
    // 0x801DE0B0: lwc1        $f10, 0x4($s1)
    ctx->f10.u32l = MEM_W(ctx->r17, 0X4);
    // 0x801DE0B4: swc1        $f10, 0x5C($s0)
    MEM_W(0X5C, ctx->r16) = ctx->f10.u32l;
    // 0x801DE0B8: lwc1        $f18, 0xFC($s1)
    ctx->f18.u32l = MEM_W(ctx->r17, 0XFC);
    // 0x801DE0BC: lwc1        $f16, 0x8($s1)
    ctx->f16.u32l = MEM_W(ctx->r17, 0X8);
    // 0x801DE0C0: add.s       $f4, $f16, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f4.fl = ctx->f16.fl + ctx->f18.fl;
    // 0x801DE0C4: swc1        $f4, 0x60($s0)
    MEM_W(0X60, ctx->r16) = ctx->f4.u32l;
    // 0x801DE0C8: lwc1        $f6, 0xC($s1)
    ctx->f6.u32l = MEM_W(ctx->r17, 0XC);
    // 0x801DE0CC: swc1        $f6, 0x64($s0)
    MEM_W(0X64, ctx->r16) = ctx->f6.u32l;
    // 0x801DE0D0: lwc1        $f8, 0x0($v1)
    ctx->f8.u32l = MEM_W(ctx->r3, 0X0);
    // 0x801DE0D4: swc1        $f8, 0x68($s0)
    MEM_W(0X68, ctx->r16) = ctx->f8.u32l;
    // 0x801DE0D8: lwc1        $f10, 0x1C($s1)
    ctx->f10.u32l = MEM_W(ctx->r17, 0X1C);
    // 0x801DE0DC: swc1        $f10, 0x80($s0)
    MEM_W(0X80, ctx->r16) = ctx->f10.u32l;
    // 0x801DE0E0: lwc1        $f16, 0x24($s1)
    ctx->f16.u32l = MEM_W(ctx->r17, 0X24);
    // 0x801DE0E4: swc1        $f16, 0x84($s0)
    MEM_W(0X84, ctx->r16) = ctx->f16.u32l;
    // 0x801DE0E8: lwc1        $f0, 0x10($s1)
    ctx->f0.u32l = MEM_W(ctx->r17, 0X10);
    // 0x801DE0EC: lwc1        $f2, 0x18($s1)
    ctx->f2.u32l = MEM_W(ctx->r17, 0X18);
    // 0x801DE0F0: mul.s       $f18, $f0, $f0
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f18.fl = MUL_S(ctx->f0.fl, ctx->f0.fl);
    // 0x801DE0F4: nop

    // 0x801DE0F8: mul.s       $f4, $f2, $f2
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f4.fl = MUL_S(ctx->f2.fl, ctx->f2.fl);
    // 0x801DE0FC: jal         0x800C7010
    // 0x801DE100: add.s       $f12, $f18, $f4
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f12.fl = ctx->f18.fl + ctx->f4.fl;
    _nsqrtf(rdram, ctx);
        goto after_1;
    // 0x801DE100: add.s       $f12, $f18, $f4
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f12.fl = ctx->f18.fl + ctx->f4.fl;
    after_1:
    // 0x801DE104: b           L_801DE34C
    // 0x801DE108: swc1        $f0, 0x90($s0)
    MEM_W(0X90, ctx->r16) = ctx->f0.u32l;
        goto L_801DE34C;
    // 0x801DE108: swc1        $f0, 0x90($s0)
    MEM_W(0X90, ctx->r16) = ctx->f0.u32l;
L_801DE10C:
    // 0x801DE10C: lwc1        $f0, 0xFC($s1)
    ctx->f0.u32l = MEM_W(ctx->r17, 0XFC);
    // 0x801DE110: mtc1        $zero, $f6
    ctx->f6.u32l = 0;
    // 0x801DE114: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801DE118: lwc1        $f10, 0x6008($at)
    ctx->f10.u32l = MEM_W(ctx->r1, 0X6008);
    // 0x801DE11C: sub.s       $f8, $f6, $f0
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f8.fl = ctx->f6.fl - ctx->f0.fl;
    // 0x801DE120: addiu       $at, $zero, -0x2
    ctx->r1 = ADD32(0, -0X2);
    // 0x801DE124: mul.s       $f16, $f8, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f16.fl = MUL_S(ctx->f8.fl, ctx->f10.fl);
    // 0x801DE128: add.s       $f18, $f0, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f18.fl = ctx->f0.fl + ctx->f16.fl;
    // 0x801DE12C: swc1        $f18, 0xFC($s1)
    MEM_W(0XFC, ctx->r17) = ctx->f18.u32l;
    // 0x801DE130: lw          $t4, 0x4($a2)
    ctx->r12 = MEM_W(ctx->r6, 0X4);
    // 0x801DE134: lw          $t5, 0x0($t4)
    ctx->r13 = MEM_W(ctx->r12, 0X0);
    // 0x801DE138: bnel        $t5, $at, L_801DE238
    if (ctx->r13 != ctx->r1) {
        // 0x801DE13C: lwc1        $f18, 0x8($s1)
        ctx->f18.u32l = MEM_W(ctx->r17, 0X8);
            goto L_801DE238;
    }
    goto skip_1;
    // 0x801DE13C: lwc1        $f18, 0x8($s1)
    ctx->f18.u32l = MEM_W(ctx->r17, 0X8);
    skip_1:
    // 0x801DE140: lw          $t6, 0x8($a2)
    ctx->r14 = MEM_W(ctx->r6, 0X8);
    // 0x801DE144: lui         $a1, 0x8022
    ctx->r5 = S32(0X8022 << 16);
    // 0x801DE148: addiu       $a1, $a1, 0x5BD8
    ctx->r5 = ADD32(ctx->r5, 0X5BD8);
    // 0x801DE14C: bne         $t6, $zero, L_801DE198
    if (ctx->r14 != 0) {
        // 0x801DE150: or          $a0, $s0, $zero
        ctx->r4 = ctx->r16 | 0;
            goto L_801DE198;
    }
    // 0x801DE150: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x801DE154: jal         0x801DF5F0
    // 0x801DE158: sw          $a2, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r6;
    func_801DF5F0(rdram, ctx);
        goto after_2;
    // 0x801DE158: sw          $a2, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r6;
    after_2:
    // 0x801DE15C: lui         $at, 0x42C8
    ctx->r1 = S32(0X42C8 << 16);
    // 0x801DE160: mtc1        $at, $f0
    ctx->f0.u32l = ctx->r1;
    // 0x801DE164: lwc1        $f6, 0x1C($s1)
    ctx->f6.u32l = MEM_W(ctx->r17, 0X1C);
    // 0x801DE168: lwc1        $f4, 0x4($s1)
    ctx->f4.u32l = MEM_W(ctx->r17, 0X4);
    // 0x801DE16C: lw          $a2, 0x40($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X40);
    // 0x801DE170: mul.s       $f8, $f6, $f0
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f8.fl = MUL_S(ctx->f6.fl, ctx->f0.fl);
    // 0x801DE174: lui         $v1, 0x8023
    ctx->r3 = S32(0X8023 << 16);
    // 0x801DE178: addiu       $v1, $v1, -0x7EF8
    ctx->r3 = ADD32(ctx->r3, -0X7EF8);
    // 0x801DE17C: sub.s       $f10, $f4, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = ctx->f4.fl - ctx->f8.fl;
    // 0x801DE180: swc1        $f10, 0x74($s0)
    MEM_W(0X74, ctx->r16) = ctx->f10.u32l;
    // 0x801DE184: lwc1        $f18, 0x24($s1)
    ctx->f18.u32l = MEM_W(ctx->r17, 0X24);
    // 0x801DE188: lwc1        $f16, 0xC($s1)
    ctx->f16.u32l = MEM_W(ctx->r17, 0XC);
    // 0x801DE18C: mul.s       $f6, $f18, $f0
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f6.fl = MUL_S(ctx->f18.fl, ctx->f0.fl);
    // 0x801DE190: sub.s       $f4, $f16, $f6
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f4.fl = ctx->f16.fl - ctx->f6.fl;
    // 0x801DE194: swc1        $f4, 0x78($s0)
    MEM_W(0X78, ctx->r16) = ctx->f4.u32l;
L_801DE198:
    // 0x801DE198: addiu       $t7, $zero, 0x1
    ctx->r15 = ADD32(0, 0X1);
    // 0x801DE19C: sw          $t7, 0x8($a2)
    MEM_W(0X8, ctx->r6) = ctx->r15;
    // 0x801DE1A0: lwc1        $f8, 0x4($s1)
    ctx->f8.u32l = MEM_W(ctx->r17, 0X4);
    // 0x801DE1A4: swc1        $f8, 0x5C($s0)
    MEM_W(0X5C, ctx->r16) = ctx->f8.u32l;
    // 0x801DE1A8: lwc1        $f18, 0xFC($s1)
    ctx->f18.u32l = MEM_W(ctx->r17, 0XFC);
    // 0x801DE1AC: lwc1        $f10, 0x8($s1)
    ctx->f10.u32l = MEM_W(ctx->r17, 0X8);
    // 0x801DE1B0: add.s       $f16, $f10, $f18
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f16.fl = ctx->f10.fl + ctx->f18.fl;
    // 0x801DE1B4: swc1        $f16, 0x60($s0)
    MEM_W(0X60, ctx->r16) = ctx->f16.u32l;
    // 0x801DE1B8: lwc1        $f6, 0xC($s1)
    ctx->f6.u32l = MEM_W(ctx->r17, 0XC);
    // 0x801DE1BC: swc1        $f6, 0x64($s0)
    MEM_W(0X64, ctx->r16) = ctx->f6.u32l;
    // 0x801DE1C0: lwc1        $f4, 0x0($v1)
    ctx->f4.u32l = MEM_W(ctx->r3, 0X0);
    // 0x801DE1C4: swc1        $f4, 0x68($s0)
    MEM_W(0X68, ctx->r16) = ctx->f4.u32l;
    // 0x801DE1C8: lwc1        $f8, 0x1C($s1)
    ctx->f8.u32l = MEM_W(ctx->r17, 0X1C);
    // 0x801DE1CC: swc1        $f8, 0x80($s0)
    MEM_W(0X80, ctx->r16) = ctx->f8.u32l;
    // 0x801DE1D0: lwc1        $f10, 0x24($s1)
    ctx->f10.u32l = MEM_W(ctx->r17, 0X24);
    // 0x801DE1D4: swc1        $f10, 0x84($s0)
    MEM_W(0X84, ctx->r16) = ctx->f10.u32l;
    // 0x801DE1D8: lwc1        $f0, 0x10($s1)
    ctx->f0.u32l = MEM_W(ctx->r17, 0X10);
    // 0x801DE1DC: lwc1        $f2, 0x18($s1)
    ctx->f2.u32l = MEM_W(ctx->r17, 0X18);
    // 0x801DE1E0: mul.s       $f18, $f0, $f0
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f18.fl = MUL_S(ctx->f0.fl, ctx->f0.fl);
    // 0x801DE1E4: nop

    // 0x801DE1E8: mul.s       $f16, $f2, $f2
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f16.fl = MUL_S(ctx->f2.fl, ctx->f2.fl);
    // 0x801DE1EC: jal         0x800C7010
    // 0x801DE1F0: add.s       $f12, $f18, $f16
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f12.fl = ctx->f18.fl + ctx->f16.fl;
    _nsqrtf(rdram, ctx);
        goto after_3;
    // 0x801DE1F0: add.s       $f12, $f18, $f16
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f12.fl = ctx->f18.fl + ctx->f16.fl;
    after_3:
    // 0x801DE1F4: lui         $at, 0x43B4
    ctx->r1 = S32(0X43B4 << 16);
    // 0x801DE1F8: mtc1        $at, $f12
    ctx->f12.u32l = ctx->r1;
    // 0x801DE1FC: swc1        $f0, 0x90($s0)
    MEM_W(0X90, ctx->r16) = ctx->f0.u32l;
    // 0x801DE200: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801DE204: lwc1        $f4, 0x600C($at)
    ctx->f4.u32l = MEM_W(ctx->r1, 0X600C);
    // 0x801DE208: lwc1        $f6, 0xB4($s0)
    ctx->f6.u32l = MEM_W(ctx->r16, 0XB4);
    // 0x801DE20C: add.s       $f8, $f6, $f4
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f8.fl = ctx->f6.fl + ctx->f4.fl;
    // 0x801DE210: swc1        $f8, 0xB4($s0)
    MEM_W(0XB4, ctx->r16) = ctx->f8.u32l;
    // 0x801DE214: lwc1        $f2, 0xB4($s0)
    ctx->f2.u32l = MEM_W(ctx->r16, 0XB4);
    // 0x801DE218: c.lt.s      $f12, $f2
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 2);
    c1cs = ctx->f12.fl < ctx->f2.fl;
    // 0x801DE21C: nop

    // 0x801DE220: bc1f        L_801DE34C
    if (!c1cs) {
        // 0x801DE224: nop
    
            goto L_801DE34C;
    }
    // 0x801DE224: nop

    // 0x801DE228: sub.s       $f10, $f2, $f12
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f10.fl = ctx->f2.fl - ctx->f12.fl;
    // 0x801DE22C: b           L_801DE34C
    // 0x801DE230: swc1        $f10, 0xB4($s0)
    MEM_W(0XB4, ctx->r16) = ctx->f10.u32l;
        goto L_801DE34C;
    // 0x801DE230: swc1        $f10, 0xB4($s0)
    MEM_W(0XB4, ctx->r16) = ctx->f10.u32l;
    // 0x801DE234: lwc1        $f18, 0x8($s1)
    ctx->f18.u32l = MEM_W(ctx->r17, 0X8);
L_801DE238:
    // 0x801DE238: lwc1        $f16, 0xFC($s1)
    ctx->f16.u32l = MEM_W(ctx->r17, 0XFC);
    // 0x801DE23C: or          $a0, $a2, $zero
    ctx->r4 = ctx->r6 | 0;
    // 0x801DE240: add.s       $f6, $f18, $f16
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f6.fl = ctx->f18.fl + ctx->f16.fl;
    // 0x801DE244: swc1        $f6, 0x8($s1)
    MEM_W(0X8, ctx->r17) = ctx->f6.u32l;
    // 0x801DE248: jal         0x801DFCB8
    // 0x801DE24C: sw          $a2, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r6;
    func_801DFCB8(rdram, ctx);
        goto after_4;
    // 0x801DE24C: sw          $a2, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r6;
    after_4:
    // 0x801DE250: lwc1        $f4, 0x8($s1)
    ctx->f4.u32l = MEM_W(ctx->r17, 0X8);
    // 0x801DE254: lwc1        $f8, 0xFC($s1)
    ctx->f8.u32l = MEM_W(ctx->r17, 0XFC);
    // 0x801DE258: lw          $a2, 0x40($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X40);
    // 0x801DE25C: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x801DE260: sub.s       $f10, $f4, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = ctx->f4.fl - ctx->f8.fl;
    // 0x801DE264: mtc1        $at, $f2
    ctx->f2.u32l = ctx->r1;
    // 0x801DE268: addiu       $at, $zero, 0x5
    ctx->r1 = ADD32(0, 0X5);
    // 0x801DE26C: swc1        $f10, 0x8($s1)
    MEM_W(0X8, ctx->r17) = ctx->f10.u32l;
    // 0x801DE270: lw          $t8, 0x0($a2)
    ctx->r24 = MEM_W(ctx->r6, 0X0);
    // 0x801DE274: lw          $t9, 0x0($t8)
    ctx->r25 = MEM_W(ctx->r24, 0X0);
    // 0x801DE278: bne         $t9, $at, L_801DE34C
    if (ctx->r25 != ctx->r1) {
        // 0x801DE27C: nop
    
            goto L_801DE34C;
    }
    // 0x801DE27C: nop

    // 0x801DE280: lwc1        $f18, 0x40($s0)
    ctx->f18.u32l = MEM_W(ctx->r16, 0X40);
    // 0x801DE284: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801DE288: ldc1        $f0, 0x6010($at)
    CHECK_FR(ctx, 0);
    ctx->f0.u64 = LD(ctx->r1, 0X6010);
    // 0x801DE28C: cvt.d.s     $f16, $f18
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f18.fl); 
    ctx->f16.d = CVT_D_S(ctx->f18.fl);
    // 0x801DE290: add.d       $f6, $f16, $f0
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f16.d); NAN_CHECK(ctx->f0.d); 
    ctx->f6.d = ctx->f16.d + ctx->f0.d;
    // 0x801DE294: cvt.s.d     $f4, $f6
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f6.d); 
    ctx->f4.fl = CVT_S_D(ctx->f6.d);
    // 0x801DE298: swc1        $f4, 0x40($s0)
    MEM_W(0X40, ctx->r16) = ctx->f4.u32l;
    // 0x801DE29C: lwc1        $f8, 0x40($s0)
    ctx->f8.u32l = MEM_W(ctx->r16, 0X40);
    // 0x801DE2A0: c.lt.s      $f2, $f8
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 8);
    c1cs = ctx->f2.fl < ctx->f8.fl;
    // 0x801DE2A4: nop

    // 0x801DE2A8: bc1fl       L_801DE2B8
    if (!c1cs) {
        // 0x801DE2AC: lwc1        $f10, 0xAC($s0)
        ctx->f10.u32l = MEM_W(ctx->r16, 0XAC);
            goto L_801DE2B8;
    }
    goto skip_2;
    // 0x801DE2AC: lwc1        $f10, 0xAC($s0)
    ctx->f10.u32l = MEM_W(ctx->r16, 0XAC);
    skip_2:
    // 0x801DE2B0: swc1        $f2, 0x40($s0)
    MEM_W(0X40, ctx->r16) = ctx->f2.u32l;
    // 0x801DE2B4: lwc1        $f10, 0xAC($s0)
    ctx->f10.u32l = MEM_W(ctx->r16, 0XAC);
L_801DE2B8:
    // 0x801DE2B8: cvt.d.s     $f18, $f10
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f10.fl); 
    ctx->f18.d = CVT_D_S(ctx->f10.fl);
    // 0x801DE2BC: add.d       $f16, $f18, $f0
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f18.d); NAN_CHECK(ctx->f0.d); 
    ctx->f16.d = ctx->f18.d + ctx->f0.d;
    // 0x801DE2C0: cvt.s.d     $f6, $f16
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f16.d); 
    ctx->f6.fl = CVT_S_D(ctx->f16.d);
    // 0x801DE2C4: swc1        $f6, 0xAC($s0)
    MEM_W(0XAC, ctx->r16) = ctx->f6.u32l;
    // 0x801DE2C8: lwc1        $f4, 0xAC($s0)
    ctx->f4.u32l = MEM_W(ctx->r16, 0XAC);
    // 0x801DE2CC: c.lt.s      $f2, $f4
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 4);
    c1cs = ctx->f2.fl < ctx->f4.fl;
    // 0x801DE2D0: nop

    // 0x801DE2D4: bc1fl       L_801DE2E4
    if (!c1cs) {
        // 0x801DE2D8: lwc1        $f8, 0xC4($s0)
        ctx->f8.u32l = MEM_W(ctx->r16, 0XC4);
            goto L_801DE2E4;
    }
    goto skip_3;
    // 0x801DE2D8: lwc1        $f8, 0xC4($s0)
    ctx->f8.u32l = MEM_W(ctx->r16, 0XC4);
    skip_3:
    // 0x801DE2DC: swc1        $f2, 0xAC($s0)
    MEM_W(0XAC, ctx->r16) = ctx->f2.u32l;
    // 0x801DE2E0: lwc1        $f8, 0xC4($s0)
    ctx->f8.u32l = MEM_W(ctx->r16, 0XC4);
L_801DE2E4:
    // 0x801DE2E4: cvt.d.s     $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f8.fl); 
    ctx->f10.d = CVT_D_S(ctx->f8.fl);
    // 0x801DE2E8: add.d       $f18, $f10, $f0
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f10.d); NAN_CHECK(ctx->f0.d); 
    ctx->f18.d = ctx->f10.d + ctx->f0.d;
    // 0x801DE2EC: cvt.s.d     $f16, $f18
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f18.d); 
    ctx->f16.fl = CVT_S_D(ctx->f18.d);
    // 0x801DE2F0: swc1        $f16, 0xC4($s0)
    MEM_W(0XC4, ctx->r16) = ctx->f16.u32l;
    // 0x801DE2F4: lwc1        $f6, 0xC4($s0)
    ctx->f6.u32l = MEM_W(ctx->r16, 0XC4);
    // 0x801DE2F8: c.lt.s      $f2, $f6
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 6);
    c1cs = ctx->f2.fl < ctx->f6.fl;
    // 0x801DE2FC: nop

    // 0x801DE300: bc1f        L_801DE34C
    if (!c1cs) {
        // 0x801DE304: nop
    
            goto L_801DE34C;
    }
    // 0x801DE304: nop

    // 0x801DE308: b           L_801DE34C
    // 0x801DE30C: swc1        $f2, 0xC4($s0)
    MEM_W(0XC4, ctx->r16) = ctx->f2.u32l;
        goto L_801DE34C;
    // 0x801DE30C: swc1        $f2, 0xC4($s0)
    MEM_W(0XC4, ctx->r16) = ctx->f2.u32l;
L_801DE310:
    // 0x801DE310: or          $a0, $a2, $zero
    ctx->r4 = ctx->r6 | 0;
    // 0x801DE314: jal         0x801DFCB8
    // 0x801DE318: sw          $a2, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r6;
    func_801DFCB8(rdram, ctx);
        goto after_5;
    // 0x801DE318: sw          $a2, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r6;
    after_5:
    // 0x801DE31C: jal         0x801DD6B4
    // 0x801DE320: lw          $a0, 0x40($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X40);
    func_801DD6B4(rdram, ctx);
        goto after_6;
    // 0x801DE320: lw          $a0, 0x40($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X40);
    after_6:
    // 0x801DE324: b           L_801DE34C
    // 0x801DE328: nop

        goto L_801DE34C;
    // 0x801DE328: nop

L_801DE32C:
    // 0x801DE32C: or          $a0, $a2, $zero
    ctx->r4 = ctx->r6 | 0;
    // 0x801DE330: jal         0x801DD6B4
    // 0x801DE334: sw          $a2, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r6;
    func_801DD6B4(rdram, ctx);
        goto after_7;
    // 0x801DE334: sw          $a2, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r6;
    after_7:
    // 0x801DE338: lw          $a2, 0x40($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X40);
    // 0x801DE33C: lw          $t0, 0x8($a2)
    ctx->r8 = MEM_W(ctx->r6, 0X8);
    // 0x801DE340: addiu       $t1, $t0, 0x1
    ctx->r9 = ADD32(ctx->r8, 0X1);
    // 0x801DE344: b           L_801DE354
    // 0x801DE348: sw          $t1, 0x8($a2)
    MEM_W(0X8, ctx->r6) = ctx->r9;
        goto L_801DE354;
    // 0x801DE348: sw          $t1, 0x8($a2)
    MEM_W(0X8, ctx->r6) = ctx->r9;
L_801DE34C:
    // 0x801DE34C: jal         0x801DFC48
    // 0x801DE350: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    func_801DFC48(rdram, ctx);
        goto after_8;
    // 0x801DE350: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_8:
L_801DE354:
    // 0x801DE354: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    // 0x801DE358: jal         0x801E0F8C
    // 0x801DE35C: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    func_801E0F8C(rdram, ctx);
        goto after_9;
    // 0x801DE35C: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    after_9:
    // 0x801DE360: jal         0x8009CB68
    // 0x801DE364: nop

    func_8009CB68(rdram, ctx);
        goto after_10;
    // 0x801DE364: nop

    after_10:
    // 0x801DE368: jal         0x8009CCE8
    // 0x801DE36C: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    func_8009CCE8(rdram, ctx);
        goto after_11;
    // 0x801DE36C: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    after_11:
    // 0x801DE370: lwc1        $f4, 0x4C($s1)
    ctx->f4.u32l = MEM_W(ctx->r17, 0X4C);
    // 0x801DE374: lwc1        $f8, 0x2C($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X2C);
    // 0x801DE378: lwc1        $f18, 0x50($s1)
    ctx->f18.u32l = MEM_W(ctx->r17, 0X50);
    // 0x801DE37C: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    // 0x801DE380: sub.s       $f10, $f4, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = ctx->f4.fl - ctx->f8.fl;
    // 0x801DE384: lwc1        $f4, 0x54($s1)
    ctx->f4.u32l = MEM_W(ctx->r17, 0X54);
    // 0x801DE388: swc1        $f10, 0x58($s1)
    MEM_W(0X58, ctx->r17) = ctx->f10.u32l;
    // 0x801DE38C: lwc1        $f16, 0x28($sp)
    ctx->f16.u32l = MEM_W(ctx->r29, 0X28);
    // 0x801DE390: sub.s       $f6, $f18, $f16
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f6.fl = ctx->f18.fl - ctx->f16.fl;
    // 0x801DE394: swc1        $f6, 0x5C($s1)
    MEM_W(0X5C, ctx->r17) = ctx->f6.u32l;
    // 0x801DE398: lwc1        $f8, 0x24($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X24);
    // 0x801DE39C: sub.s       $f10, $f4, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = ctx->f4.fl - ctx->f8.fl;
    // 0x801DE3A0: jal         0x801E0FF0
    // 0x801DE3A4: swc1        $f10, 0x60($s1)
    MEM_W(0X60, ctx->r17) = ctx->f10.u32l;
    func_801E0FF0(rdram, ctx);
        goto after_12;
    // 0x801DE3A4: swc1        $f10, 0x60($s1)
    MEM_W(0X60, ctx->r17) = ctx->f10.u32l;
    after_12:
    // 0x801DE3A8: lui         $a0, 0x8015
    ctx->r4 = S32(0X8015 << 16);
    // 0x801DE3AC: lw          $a0, 0x18B8($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X18B8);
    // 0x801DE3B0: jal         0x801E11B4
    // 0x801DE3B4: or          $a1, $s1, $zero
    ctx->r5 = ctx->r17 | 0;
    func_801E11B4(rdram, ctx);
        goto after_13;
    // 0x801DE3B4: or          $a1, $s1, $zero
    ctx->r5 = ctx->r17 | 0;
    after_13:
    // 0x801DE3B8: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    // 0x801DE3BC: lw          $s0, 0x14($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X14);
    // 0x801DE3C0: lw          $s1, 0x18($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X18);
    // 0x801DE3C4: jr          $ra
    // 0x801DE3C8: addiu       $sp, $sp, 0x38
    ctx->r29 = ADD32(ctx->r29, 0X38);
    return;
    // 0x801DE3C8: addiu       $sp, $sp, 0x38
    ctx->r29 = ADD32(ctx->r29, 0X38);
;}
RECOMP_FUNC void func_801DE3CC(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801DE3CC: addiu       $sp, $sp, -0x58
    ctx->r29 = ADD32(ctx->r29, -0X58);
    // 0x801DE3D0: lui         $t6, 0x800E
    ctx->r14 = S32(0X800E << 16);
    // 0x801DE3D4: lw          $t6, -0x54D8($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X54D8);
    // 0x801DE3D8: sw          $s3, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r19;
    // 0x801DE3DC: sw          $ra, 0x54($sp)
    MEM_W(0X54, ctx->r29) = ctx->r31;
    // 0x801DE3E0: sw          $fp, 0x50($sp)
    MEM_W(0X50, ctx->r29) = ctx->r30;
    // 0x801DE3E4: sw          $s7, 0x4C($sp)
    MEM_W(0X4C, ctx->r29) = ctx->r23;
    // 0x801DE3E8: sw          $s6, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r22;
    // 0x801DE3EC: sw          $s5, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r21;
    // 0x801DE3F0: sw          $s4, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r20;
    // 0x801DE3F4: sw          $s2, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r18;
    // 0x801DE3F8: sw          $s1, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r17;
    // 0x801DE3FC: sw          $s0, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r16;
    // 0x801DE400: sdc1        $f24, 0x28($sp)
    CHECK_FR(ctx, 24);
    SD(ctx->f24.u64, 0X28, ctx->r29);
    // 0x801DE404: sdc1        $f22, 0x20($sp)
    CHECK_FR(ctx, 22);
    SD(ctx->f22.u64, 0X20, ctx->r29);
    // 0x801DE408: sdc1        $f20, 0x18($sp)
    CHECK_FR(ctx, 20);
    SD(ctx->f20.u64, 0X18, ctx->r29);
    // 0x801DE40C: blez        $t6, L_801DE654
    if (SIGNED(ctx->r14) <= 0) {
        // 0x801DE410: or          $s3, $zero, $zero
        ctx->r19 = 0 | 0;
            goto L_801DE654;
    }
    // 0x801DE410: or          $s3, $zero, $zero
    ctx->r19 = 0 | 0;
    // 0x801DE414: lui         $s1, 0x8022
    ctx->r17 = S32(0X8022 << 16);
    // 0x801DE418: lui         $s5, 0x8022
    ctx->r21 = S32(0X8022 << 16);
    // 0x801DE41C: lui         $s4, 0x8022
    ctx->r20 = S32(0X8022 << 16);
    // 0x801DE420: lui         $s7, 0x8015
    ctx->r23 = S32(0X8015 << 16);
    // 0x801DE424: lui         $s6, 0x8019
    ctx->r22 = S32(0X8019 << 16);
    // 0x801DE428: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801DE42C: lui         $fp, 0x8022
    ctx->r30 = S32(0X8022 << 16);
    // 0x801DE430: mtc1        $zero, $f24
    ctx->f24.u32l = 0;
    // 0x801DE434: addiu       $fp, $fp, 0x3970
    ctx->r30 = ADD32(ctx->r30, 0X3970);
    // 0x801DE438: lwc1        $f22, 0x6018($at)
    ctx->f22.u32l = MEM_W(ctx->r1, 0X6018);
    // 0x801DE43C: addiu       $s6, $s6, 0x2690
    ctx->r22 = ADD32(ctx->r22, 0X2690);
    // 0x801DE440: addiu       $s7, $s7, 0x4330
    ctx->r23 = ADD32(ctx->r23, 0X4330);
    // 0x801DE444: addiu       $s4, $s4, 0x7EF4
    ctx->r20 = ADD32(ctx->r20, 0X7EF4);
    // 0x801DE448: addiu       $s5, $s5, 0x7E98
    ctx->r21 = ADD32(ctx->r21, 0X7E98);
    // 0x801DE44C: addiu       $s1, $s1, 0x7C80
    ctx->r17 = ADD32(ctx->r17, 0X7C80);
    // 0x801DE450: lw          $t7, 0x0($s7)
    ctx->r15 = MEM_W(ctx->r23, 0X0);
L_801DE454:
    // 0x801DE454: lui         $t0, 0x8015
    ctx->r8 = S32(0X8015 << 16);
    // 0x801DE458: addiu       $t0, $t0, 0x4308
    ctx->r8 = ADD32(ctx->r8, 0X4308);
    // 0x801DE45C: sll         $t8, $t7, 2
    ctx->r24 = S32(ctx->r15 << 2);
    // 0x801DE460: addu        $t8, $t8, $t7
    ctx->r24 = ADD32(ctx->r24, ctx->r15);
    // 0x801DE464: sll         $t8, $t8, 1
    ctx->r24 = S32(ctx->r24 << 1);
    // 0x801DE468: addiu       $t9, $t8, 0x2
    ctx->r25 = ADD32(ctx->r24, 0X2);
    // 0x801DE46C: addu        $s2, $t9, $t0
    ctx->r18 = ADD32(ctx->r25, ctx->r8);
    // 0x801DE470: lhu         $t1, 0x0($s2)
    ctx->r9 = MEM_HU(ctx->r18, 0X0);
    // 0x801DE474: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801DE478: lw          $s0, 0xEC($s1)
    ctx->r16 = MEM_W(ctx->r17, 0XEC);
    // 0x801DE47C: andi        $t2, $t1, 0x3
    ctx->r10 = ctx->r9 & 0X3;
    // 0x801DE480: beq         $t2, $zero, L_801DE4B8
    if (ctx->r10 == 0) {
        // 0x801DE484: lwc1        $f20, 0x601C($at)
        ctx->f20.u32l = MEM_W(ctx->r1, 0X601C);
            goto L_801DE4B8;
    }
    // 0x801DE484: lwc1        $f20, 0x601C($at)
    ctx->f20.u32l = MEM_W(ctx->r1, 0X601C);
    // 0x801DE488: lw          $t3, 0xF8($s1)
    ctx->r11 = MEM_W(ctx->r17, 0XF8);
    // 0x801DE48C: or          $a1, $s3, $zero
    ctx->r5 = ctx->r19 | 0;
    // 0x801DE490: addiu       $a0, $zero, 0x16
    ctx->r4 = ADD32(0, 0X16);
    // 0x801DE494: xori        $t4, $t3, 0x1
    ctx->r12 = ctx->r11 ^ 0X1;
    // 0x801DE498: beq         $t4, $zero, L_801DE4B0
    if (ctx->r12 == 0) {
        // 0x801DE49C: sw          $t4, 0xF8($s1)
        MEM_W(0XF8, ctx->r17) = ctx->r12;
            goto L_801DE4B0;
    }
    // 0x801DE49C: sw          $t4, 0xF8($s1)
    MEM_W(0XF8, ctx->r17) = ctx->r12;
    // 0x801DE4A0: jal         0x800C37F4
    // 0x801DE4A4: addiu       $a0, $zero, 0x11
    ctx->r4 = ADD32(0, 0X11);
    func_800C37F4(rdram, ctx);
        goto after_0;
    // 0x801DE4A4: addiu       $a0, $zero, 0x11
    ctx->r4 = ADD32(0, 0X11);
    after_0:
    // 0x801DE4A8: b           L_801DE4BC
    // 0x801DE4AC: lw          $t6, 0xF8($s1)
    ctx->r14 = MEM_W(ctx->r17, 0XF8);
        goto L_801DE4BC;
    // 0x801DE4AC: lw          $t6, 0xF8($s1)
    ctx->r14 = MEM_W(ctx->r17, 0XF8);
L_801DE4B0:
    // 0x801DE4B0: jal         0x800C37F4
    // 0x801DE4B4: or          $a1, $s3, $zero
    ctx->r5 = ctx->r19 | 0;
    func_800C37F4(rdram, ctx);
        goto after_1;
    // 0x801DE4B4: or          $a1, $s3, $zero
    ctx->r5 = ctx->r19 | 0;
    after_1:
L_801DE4B8:
    // 0x801DE4B8: lw          $t6, 0xF8($s1)
    ctx->r14 = MEM_W(ctx->r17, 0XF8);
L_801DE4BC:
    // 0x801DE4BC: addiu       $a0, $zero, 0x1D
    ctx->r4 = ADD32(0, 0X1D);
    // 0x801DE4C0: sw          $t6, 0x80($s4)
    MEM_W(0X80, ctx->r20) = ctx->r14;
    // 0x801DE4C4: lhu         $v0, 0x0($s2)
    ctx->r2 = MEM_HU(ctx->r18, 0X0);
    // 0x801DE4C8: andi        $t7, $v0, 0x8
    ctx->r15 = ctx->r2 & 0X8;
    // 0x801DE4CC: beq         $t7, $zero, L_801DE4D8
    if (ctx->r15 == 0) {
        // 0x801DE4D0: andi        $t8, $v0, 0x4
        ctx->r24 = ctx->r2 & 0X4;
            goto L_801DE4D8;
    }
    // 0x801DE4D0: andi        $t8, $v0, 0x4
    ctx->r24 = ctx->r2 & 0X4;
    // 0x801DE4D4: addiu       $s0, $s0, 0x1
    ctx->r16 = ADD32(ctx->r16, 0X1);
L_801DE4D8:
    // 0x801DE4D8: beq         $t8, $zero, L_801DE4E4
    if (ctx->r24 == 0) {
        // 0x801DE4DC: nop
    
            goto L_801DE4E4;
    }
    // 0x801DE4DC: nop

    // 0x801DE4E0: addiu       $s0, $s0, -0x1
    ctx->r16 = ADD32(ctx->r16, -0X1);
L_801DE4E4:
    // 0x801DE4E4: bgez        $s0, L_801DE4F8
    if (SIGNED(ctx->r16) >= 0) {
        // 0x801DE4E8: slti        $at, $s0, 0x4
        ctx->r1 = SIGNED(ctx->r16) < 0X4 ? 1 : 0;
            goto L_801DE4F8;
    }
    // 0x801DE4E8: slti        $at, $s0, 0x4
    ctx->r1 = SIGNED(ctx->r16) < 0X4 ? 1 : 0;
    // 0x801DE4EC: addiu       $s0, $zero, 0x3
    ctx->r16 = ADD32(0, 0X3);
    // 0x801DE4F0: b           L_801DE508
    // 0x801DE4F4: mov.s       $f20, $f22
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 22);
    ctx->f20.fl = ctx->f22.fl;
        goto L_801DE508;
    // 0x801DE4F4: mov.s       $f20, $f22
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 22);
    ctx->f20.fl = ctx->f22.fl;
L_801DE4F8:
    // 0x801DE4F8: bnel        $at, $zero, L_801DE50C
    if (ctx->r1 != 0) {
        // 0x801DE4FC: lw          $v0, 0xEC($s1)
        ctx->r2 = MEM_W(ctx->r17, 0XEC);
            goto L_801DE50C;
    }
    goto skip_0;
    // 0x801DE4FC: lw          $v0, 0xEC($s1)
    ctx->r2 = MEM_W(ctx->r17, 0XEC);
    skip_0:
    // 0x801DE500: or          $s0, $zero, $zero
    ctx->r16 = 0 | 0;
    // 0x801DE504: mov.s       $f20, $f22
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 22);
    ctx->f20.fl = ctx->f22.fl;
L_801DE508:
    // 0x801DE508: lw          $v0, 0xEC($s1)
    ctx->r2 = MEM_W(ctx->r17, 0XEC);
L_801DE50C:
    // 0x801DE50C: slt         $at, $v0, $s0
    ctx->r1 = SIGNED(ctx->r2) < SIGNED(ctx->r16) ? 1 : 0;
    // 0x801DE510: beql        $at, $zero, L_801DE52C
    if (ctx->r1 == 0) {
        // 0x801DE514: slt         $at, $s0, $v0
        ctx->r1 = SIGNED(ctx->r16) < SIGNED(ctx->r2) ? 1 : 0;
            goto L_801DE52C;
    }
    goto skip_1;
    // 0x801DE514: slt         $at, $s0, $v0
    ctx->r1 = SIGNED(ctx->r16) < SIGNED(ctx->r2) ? 1 : 0;
    skip_1:
    // 0x801DE518: jal         0x800C37F4
    // 0x801DE51C: or          $a1, $s3, $zero
    ctx->r5 = ctx->r19 | 0;
    func_800C37F4(rdram, ctx);
        goto after_2;
    // 0x801DE51C: or          $a1, $s3, $zero
    ctx->r5 = ctx->r19 | 0;
    after_2:
    // 0x801DE520: b           L_801DE540
    // 0x801DE524: swc1        $f20, 0x68($s4)
    MEM_W(0X68, ctx->r20) = ctx->f20.u32l;
        goto L_801DE540;
    // 0x801DE524: swc1        $f20, 0x68($s4)
    MEM_W(0X68, ctx->r20) = ctx->f20.u32l;
    // 0x801DE528: slt         $at, $s0, $v0
    ctx->r1 = SIGNED(ctx->r16) < SIGNED(ctx->r2) ? 1 : 0;
L_801DE52C:
    // 0x801DE52C: beq         $at, $zero, L_801DE53C
    if (ctx->r1 == 0) {
        // 0x801DE530: addiu       $a0, $zero, 0x1E
        ctx->r4 = ADD32(0, 0X1E);
            goto L_801DE53C;
    }
    // 0x801DE530: addiu       $a0, $zero, 0x1E
    ctx->r4 = ADD32(0, 0X1E);
    // 0x801DE534: jal         0x800C37F4
    // 0x801DE538: or          $a1, $s3, $zero
    ctx->r5 = ctx->r19 | 0;
    func_800C37F4(rdram, ctx);
        goto after_3;
    // 0x801DE538: or          $a1, $s3, $zero
    ctx->r5 = ctx->r19 | 0;
    after_3:
L_801DE53C:
    // 0x801DE53C: swc1        $f20, 0x68($s4)
    MEM_W(0X68, ctx->r20) = ctx->f20.u32l;
L_801DE540:
    // 0x801DE540: swc1        $f20, 0x50($s4)
    MEM_W(0X50, ctx->r20) = ctx->f20.u32l;
    // 0x801DE544: sll         $v1, $s0, 2
    ctx->r3 = S32(ctx->r16 << 2);
    // 0x801DE548: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801DE54C: swc1        $f20, 0x40($s5)
    MEM_W(0X40, ctx->r21) = ctx->f20.u32l;
    // 0x801DE550: addu        $at, $at, $v1
    ctx->r1 = ADD32(ctx->r1, ctx->r3);
    // 0x801DE554: lwc1        $f4, 0x3940($at)
    ctx->f4.u32l = MEM_W(ctx->r1, 0X3940);
    // 0x801DE558: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801DE55C: addu        $at, $at, $v1
    ctx->r1 = ADD32(ctx->r1, ctx->r3);
    // 0x801DE560: swc1        $f4, 0x3C($s5)
    MEM_W(0X3C, ctx->r21) = ctx->f4.u32l;
    // 0x801DE564: lwc1        $f6, 0x3950($at)
    ctx->f6.u32l = MEM_W(ctx->r1, 0X3950);
    // 0x801DE568: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801DE56C: addu        $at, $at, $v1
    ctx->r1 = ADD32(ctx->r1, ctx->r3);
    // 0x801DE570: swc1        $f6, 0x4C($s4)
    MEM_W(0X4C, ctx->r20) = ctx->f6.u32l;
    // 0x801DE574: lwc1        $f8, 0x3960($at)
    ctx->f8.u32l = MEM_W(ctx->r1, 0X3960);
    // 0x801DE578: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801DE57C: swc1        $f8, 0x64($s4)
    MEM_W(0X64, ctx->r20) = ctx->f8.u32l;
    // 0x801DE580: lw          $t9, 0xEC($s1)
    ctx->r25 = MEM_W(ctx->r17, 0XEC);
    // 0x801DE584: bnel        $s0, $t9, L_801DE594
    if (ctx->r16 != ctx->r25) {
        // 0x801DE588: lw          $v0, 0xC54($s6)
        ctx->r2 = MEM_W(ctx->r22, 0XC54);
            goto L_801DE594;
    }
    goto skip_2;
    // 0x801DE588: lw          $v0, 0xC54($s6)
    ctx->r2 = MEM_W(ctx->r22, 0XC54);
    skip_2:
    // 0x801DE58C: lwc1        $f20, 0x6020($at)
    ctx->f20.u32l = MEM_W(ctx->r1, 0X6020);
    // 0x801DE590: lw          $v0, 0xC54($s6)
    ctx->r2 = MEM_W(ctx->r22, 0XC54);
L_801DE594:
    // 0x801DE594: addiu       $at, $zero, 0x7
    ctx->r1 = ADD32(0, 0X7);
    // 0x801DE598: beq         $v0, $at, L_801DE5E8
    if (ctx->r2 == ctx->r1) {
        // 0x801DE59C: addiu       $at, $zero, 0x17
        ctx->r1 = ADD32(0, 0X17);
            goto L_801DE5E8;
    }
    // 0x801DE59C: addiu       $at, $zero, 0x17
    ctx->r1 = ADD32(0, 0X17);
    // 0x801DE5A0: beq         $v0, $at, L_801DE5C0
    if (ctx->r2 == ctx->r1) {
        // 0x801DE5A4: addiu       $at, $zero, 0x18
        ctx->r1 = ADD32(0, 0X18);
            goto L_801DE5C0;
    }
    // 0x801DE5A4: addiu       $at, $zero, 0x18
    ctx->r1 = ADD32(0, 0X18);
    // 0x801DE5A8: beq         $v0, $at, L_801DE5C0
    if (ctx->r2 == ctx->r1) {
        // 0x801DE5AC: addiu       $at, $zero, 0x19
        ctx->r1 = ADD32(0, 0X19);
            goto L_801DE5C0;
    }
    // 0x801DE5AC: addiu       $at, $zero, 0x19
    ctx->r1 = ADD32(0, 0X19);
    // 0x801DE5B0: beq         $v0, $at, L_801DE5C8
    if (ctx->r2 == ctx->r1) {
        // 0x801DE5B4: addu        $t2, $fp, $v1
        ctx->r10 = ADD32(ctx->r30, ctx->r3);
            goto L_801DE5C8;
    }
    // 0x801DE5B4: addu        $t2, $fp, $v1
    ctx->r10 = ADD32(ctx->r30, ctx->r3);
    // 0x801DE5B8: b           L_801DE610
    // 0x801DE5BC: lwc1        $f2, 0x0($t2)
    ctx->f2.u32l = MEM_W(ctx->r10, 0X0);
        goto L_801DE610;
    // 0x801DE5BC: lwc1        $f2, 0x0($t2)
    ctx->f2.u32l = MEM_W(ctx->r10, 0X0);
L_801DE5C0:
    // 0x801DE5C0: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801DE5C4: lwc1        $f20, 0x6024($at)
    ctx->f20.u32l = MEM_W(ctx->r1, 0X6024);
L_801DE5C8:
    // 0x801DE5C8: slti        $at, $s0, 0x2
    ctx->r1 = SIGNED(ctx->r16) < 0X2 ? 1 : 0;
    // 0x801DE5CC: bne         $at, $zero, L_801DE5E0
    if (ctx->r1 != 0) {
        // 0x801DE5D0: lui         $at, 0x4120
        ctx->r1 = S32(0X4120 << 16);
            goto L_801DE5E0;
    }
    // 0x801DE5D0: lui         $at, 0x4120
    ctx->r1 = S32(0X4120 << 16);
    // 0x801DE5D4: mtc1        $at, $f2
    ctx->f2.u32l = ctx->r1;
    // 0x801DE5D8: b           L_801DE614
    // 0x801DE5DC: lwc1        $f0, 0xFC($s1)
    ctx->f0.u32l = MEM_W(ctx->r17, 0XFC);
        goto L_801DE614;
    // 0x801DE5DC: lwc1        $f0, 0xFC($s1)
    ctx->f0.u32l = MEM_W(ctx->r17, 0XFC);
L_801DE5E0:
    // 0x801DE5E0: b           L_801DE610
    // 0x801DE5E4: mov.s       $f2, $f24
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 24);
    ctx->f2.fl = ctx->f24.fl;
        goto L_801DE610;
    // 0x801DE5E4: mov.s       $f2, $f24
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 24);
    ctx->f2.fl = ctx->f24.fl;
L_801DE5E8:
    // 0x801DE5E8: lw          $t0, 0xC58($s6)
    ctx->r8 = MEM_W(ctx->r22, 0XC58);
    // 0x801DE5EC: addu        $t1, $fp, $v1
    ctx->r9 = ADD32(ctx->r30, ctx->r3);
    // 0x801DE5F0: slti        $at, $t0, 0x38
    ctx->r1 = SIGNED(ctx->r8) < 0X38 ? 1 : 0;
    // 0x801DE5F4: beq         $at, $zero, L_801DE604
    if (ctx->r1 == 0) {
        // 0x801DE5F8: nop
    
            goto L_801DE604;
    }
    // 0x801DE5F8: nop

    // 0x801DE5FC: b           L_801DE610
    // 0x801DE600: mov.s       $f2, $f24
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 24);
    ctx->f2.fl = ctx->f24.fl;
        goto L_801DE610;
    // 0x801DE600: mov.s       $f2, $f24
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 24);
    ctx->f2.fl = ctx->f24.fl;
L_801DE604:
    // 0x801DE604: b           L_801DE610
    // 0x801DE608: lwc1        $f2, 0x0($t1)
    ctx->f2.u32l = MEM_W(ctx->r9, 0X0);
        goto L_801DE610;
    // 0x801DE608: lwc1        $f2, 0x0($t1)
    ctx->f2.u32l = MEM_W(ctx->r9, 0X0);
    // 0x801DE60C: lwc1        $f2, 0x0($t2)
    ctx->f2.u32l = MEM_W(ctx->r10, 0X0);
L_801DE610:
    // 0x801DE610: lwc1        $f0, 0xFC($s1)
    ctx->f0.u32l = MEM_W(ctx->r17, 0XFC);
L_801DE614:
    // 0x801DE614: lui         $t3, 0x800E
    ctx->r11 = S32(0X800E << 16);
    // 0x801DE618: sw          $s0, 0xEC($s1)
    MEM_W(0XEC, ctx->r17) = ctx->r16;
    // 0x801DE61C: sub.s       $f10, $f2, $f0
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f10.fl = ctx->f2.fl - ctx->f0.fl;
    // 0x801DE620: addiu       $s3, $s3, 0x1
    ctx->r19 = ADD32(ctx->r19, 0X1);
    // 0x801DE624: addiu       $s1, $s1, 0x10C
    ctx->r17 = ADD32(ctx->r17, 0X10C);
    // 0x801DE628: addiu       $s5, $s5, 0xE0
    ctx->r21 = ADD32(ctx->r21, 0XE0);
    // 0x801DE62C: mul.s       $f16, $f10, $f20
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f16.fl = MUL_S(ctx->f10.fl, ctx->f20.fl);
    // 0x801DE630: addiu       $s4, $s4, 0xE0
    ctx->r20 = ADD32(ctx->r20, 0XE0);
    // 0x801DE634: addiu       $s7, $s7, 0x4
    ctx->r23 = ADD32(ctx->r23, 0X4);
    // 0x801DE638: addiu       $s6, $s6, 0x1718
    ctx->r22 = ADD32(ctx->r22, 0X1718);
    // 0x801DE63C: add.s       $f18, $f0, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f18.fl = ctx->f0.fl + ctx->f16.fl;
    // 0x801DE640: swc1        $f18, -0x10($s1)
    MEM_W(-0X10, ctx->r17) = ctx->f18.u32l;
    // 0x801DE644: lw          $t3, -0x54D8($t3)
    ctx->r11 = MEM_W(ctx->r11, -0X54D8);
    // 0x801DE648: slt         $at, $s3, $t3
    ctx->r1 = SIGNED(ctx->r19) < SIGNED(ctx->r11) ? 1 : 0;
    // 0x801DE64C: bnel        $at, $zero, L_801DE454
    if (ctx->r1 != 0) {
        // 0x801DE650: lw          $t7, 0x0($s7)
        ctx->r15 = MEM_W(ctx->r23, 0X0);
            goto L_801DE454;
    }
    goto skip_3;
    // 0x801DE650: lw          $t7, 0x0($s7)
    ctx->r15 = MEM_W(ctx->r23, 0X0);
    skip_3:
L_801DE654:
    // 0x801DE654: lw          $ra, 0x54($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X54);
    // 0x801DE658: ldc1        $f20, 0x18($sp)
    CHECK_FR(ctx, 20);
    ctx->f20.u64 = LD(ctx->r29, 0X18);
    // 0x801DE65C: ldc1        $f22, 0x20($sp)
    CHECK_FR(ctx, 22);
    ctx->f22.u64 = LD(ctx->r29, 0X20);
    // 0x801DE660: ldc1        $f24, 0x28($sp)
    CHECK_FR(ctx, 24);
    ctx->f24.u64 = LD(ctx->r29, 0X28);
    // 0x801DE664: lw          $s0, 0x30($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X30);
    // 0x801DE668: lw          $s1, 0x34($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X34);
    // 0x801DE66C: lw          $s2, 0x38($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X38);
    // 0x801DE670: lw          $s3, 0x3C($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X3C);
    // 0x801DE674: lw          $s4, 0x40($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X40);
    // 0x801DE678: lw          $s5, 0x44($sp)
    ctx->r21 = MEM_W(ctx->r29, 0X44);
    // 0x801DE67C: lw          $s6, 0x48($sp)
    ctx->r22 = MEM_W(ctx->r29, 0X48);
    // 0x801DE680: lw          $s7, 0x4C($sp)
    ctx->r23 = MEM_W(ctx->r29, 0X4C);
    // 0x801DE684: lw          $fp, 0x50($sp)
    ctx->r30 = MEM_W(ctx->r29, 0X50);
    // 0x801DE688: jr          $ra
    // 0x801DE68C: addiu       $sp, $sp, 0x58
    ctx->r29 = ADD32(ctx->r29, 0X58);
    return;
    // 0x801DE68C: addiu       $sp, $sp, 0x58
    ctx->r29 = ADD32(ctx->r29, 0X58);
;}
RECOMP_FUNC void func_801DE690(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801DE690: bne         $a1, $zero, L_801DE74C
    if (ctx->r5 != 0) {
        // 0x801DE694: addiu       $sp, $sp, -0x28
        ctx->r29 = ADD32(ctx->r29, -0X28);
            goto L_801DE74C;
    }
    // 0x801DE694: addiu       $sp, $sp, -0x28
    ctx->r29 = ADD32(ctx->r29, -0X28);
    // 0x801DE698: lui         $at, 0x3F00
    ctx->r1 = S32(0X3F00 << 16);
    // 0x801DE69C: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
    // 0x801DE6A0: lui         $at, 0x4040
    ctx->r1 = S32(0X4040 << 16);
    // 0x801DE6A4: mtc1        $at, $f18
    ctx->f18.u32l = ctx->r1;
    // 0x801DE6A8: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x801DE6AC: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x801DE6B0: lui         $at, 0x41A8
    ctx->r1 = S32(0X41A8 << 16);
    // 0x801DE6B4: mtc1        $at, $f10
    ctx->f10.u32l = ctx->r1;
    // 0x801DE6B8: sub.s       $f0, $f4, $f12
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f0.fl = ctx->f4.fl - ctx->f12.fl;
    // 0x801DE6BC: lui         $at, 0x4140
    ctx->r1 = S32(0X4140 << 16);
    // 0x801DE6C0: mul.s       $f6, $f0, $f0
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f6.fl = MUL_S(ctx->f0.fl, ctx->f0.fl);
    // 0x801DE6C4: nop

    // 0x801DE6C8: mul.s       $f8, $f6, $f0
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f8.fl = MUL_S(ctx->f6.fl, ctx->f0.fl);
    // 0x801DE6CC: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x801DE6D0: lui         $at, 0x4110
    ctx->r1 = S32(0X4110 << 16);
    // 0x801DE6D4: mul.s       $f2, $f12, $f12
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f2.fl = MUL_S(ctx->f12.fl, ctx->f12.fl);
    // 0x801DE6D8: swc1        $f8, 0x4($sp)
    MEM_W(0X4, ctx->r29) = ctx->f8.u32l;
    // 0x801DE6DC: mul.s       $f14, $f2, $f12
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f14.fl = MUL_S(ctx->f2.fl, ctx->f12.fl);
    // 0x801DE6E0: nop

    // 0x801DE6E4: mul.s       $f4, $f14, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f4.fl = MUL_S(ctx->f14.fl, ctx->f10.fl);
    // 0x801DE6E8: mtc1        $at, $f10
    ctx->f10.u32l = ctx->r1;
    // 0x801DE6EC: lui         $at, 0x4130
    ctx->r1 = S32(0X4130 << 16);
    // 0x801DE6F0: div.s       $f8, $f4, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = DIV_S(ctx->f4.fl, ctx->f6.fl);
    // 0x801DE6F4: mul.s       $f4, $f2, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f4.fl = MUL_S(ctx->f2.fl, ctx->f10.fl);
    // 0x801DE6F8: nop

    // 0x801DE6FC: mul.s       $f6, $f4, $f16
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f6.fl = MUL_S(ctx->f4.fl, ctx->f16.fl);
    // 0x801DE700: sub.s       $f10, $f8, $f6
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f10.fl = ctx->f8.fl - ctx->f6.fl;
    // 0x801DE704: mul.s       $f4, $f12, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f4.fl = MUL_S(ctx->f12.fl, ctx->f18.fl);
    // 0x801DE708: neg.s       $f6, $f14
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f14.fl); 
    ctx->f6.fl = -ctx->f14.fl;
    // 0x801DE70C: add.s       $f8, $f10, $f4
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f8.fl = ctx->f10.fl + ctx->f4.fl;
    // 0x801DE710: mtc1        $at, $f10
    ctx->f10.u32l = ctx->r1;
    // 0x801DE714: lui         $at, 0x4140
    ctx->r1 = S32(0X4140 << 16);
    // 0x801DE718: mul.s       $f4, $f6, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f4.fl = MUL_S(ctx->f6.fl, ctx->f10.fl);
    // 0x801DE71C: swc1        $f8, 0x8($sp)
    MEM_W(0X8, ctx->r29) = ctx->f8.u32l;
    // 0x801DE720: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x801DE724: mul.s       $f10, $f2, $f18
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f10.fl = MUL_S(ctx->f2.fl, ctx->f18.fl);
    // 0x801DE728: lui         $at, 0x40C0
    ctx->r1 = S32(0X40C0 << 16);
    // 0x801DE72C: div.s       $f6, $f4, $f8
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f6.fl = DIV_S(ctx->f4.fl, ctx->f8.fl);
    // 0x801DE730: mul.s       $f4, $f10, $f16
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f4.fl = MUL_S(ctx->f10.fl, ctx->f16.fl);
    // 0x801DE734: mtc1        $at, $f10
    ctx->f10.u32l = ctx->r1;
    // 0x801DE738: add.s       $f8, $f6, $f4
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f8.fl = ctx->f6.fl + ctx->f4.fl;
    // 0x801DE73C: div.s       $f6, $f14, $f10
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f6.fl = DIV_S(ctx->f14.fl, ctx->f10.fl);
    // 0x801DE740: swc1        $f8, 0xC($sp)
    MEM_W(0XC, ctx->r29) = ctx->f8.u32l;
    // 0x801DE744: b           L_801DEA48
    // 0x801DE748: swc1        $f6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f6.u32l;
        goto L_801DEA48;
    // 0x801DE748: swc1        $f6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f6.u32l;
L_801DE74C:
    // 0x801DE74C: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x801DE750: bne         $a1, $at, L_801DE81C
    if (ctx->r5 != ctx->r1) {
        // 0x801DE754: lui         $at, 0x3F00
        ctx->r1 = S32(0X3F00 << 16);
            goto L_801DE81C;
    }
    // 0x801DE754: lui         $at, 0x3F00
    ctx->r1 = S32(0X3F00 << 16);
    // 0x801DE758: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
    // 0x801DE75C: lui         $at, 0x3E80
    ctx->r1 = S32(0X3E80 << 16);
    // 0x801DE760: mtc1        $at, $f18
    ctx->f18.u32l = ctx->r1;
    // 0x801DE764: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x801DE768: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x801DE76C: lui         $at, 0x40E0
    ctx->r1 = S32(0X40E0 << 16);
    // 0x801DE770: sub.s       $f0, $f4, $f12
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f0.fl = ctx->f4.fl - ctx->f12.fl;
    // 0x801DE774: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x801DE778: lui         $at, 0x4140
    ctx->r1 = S32(0X4140 << 16);
    // 0x801DE77C: mul.s       $f8, $f0, $f0
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f8.fl = MUL_S(ctx->f0.fl, ctx->f0.fl);
    // 0x801DE780: nop

    // 0x801DE784: mul.s       $f10, $f8, $f0
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f10.fl = MUL_S(ctx->f8.fl, ctx->f0.fl);
    // 0x801DE788: nop

    // 0x801DE78C: mul.s       $f6, $f10, $f18
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f6.fl = MUL_S(ctx->f10.fl, ctx->f18.fl);
    // 0x801DE790: mtc1        $at, $f10
    ctx->f10.u32l = ctx->r1;
    // 0x801DE794: lui         $at, 0x40A0
    ctx->r1 = S32(0X40A0 << 16);
    // 0x801DE798: mul.s       $f2, $f12, $f12
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f2.fl = MUL_S(ctx->f12.fl, ctx->f12.fl);
    // 0x801DE79C: swc1        $f6, 0x4($sp)
    MEM_W(0X4, ctx->r29) = ctx->f6.u32l;
    // 0x801DE7A0: mul.s       $f14, $f2, $f12
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f14.fl = MUL_S(ctx->f2.fl, ctx->f12.fl);
    // 0x801DE7A4: nop

    // 0x801DE7A8: mul.s       $f8, $f14, $f4
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f8.fl = MUL_S(ctx->f14.fl, ctx->f4.fl);
    // 0x801DE7AC: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x801DE7B0: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801DE7B4: div.s       $f6, $f8, $f10
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f6.fl = DIV_S(ctx->f8.fl, ctx->f10.fl);
    // 0x801DE7B8: mul.s       $f8, $f2, $f4
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f8.fl = MUL_S(ctx->f2.fl, ctx->f4.fl);
    // 0x801DE7BC: nop

    // 0x801DE7C0: mul.s       $f10, $f8, $f18
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f10.fl = MUL_S(ctx->f8.fl, ctx->f18.fl);
    // 0x801DE7C4: sub.s       $f4, $f6, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f4.fl = ctx->f6.fl - ctx->f10.fl;
    // 0x801DE7C8: mul.s       $f8, $f12, $f18
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f8.fl = MUL_S(ctx->f12.fl, ctx->f18.fl);
    // 0x801DE7CC: lwc1        $f10, 0x6028($at)
    ctx->f10.u32l = MEM_W(ctx->r1, 0X6028);
    // 0x801DE7D0: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801DE7D4: add.s       $f6, $f4, $f8
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f6.fl = ctx->f4.fl + ctx->f8.fl;
    // 0x801DE7D8: neg.s       $f8, $f14
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f14.fl); 
    ctx->f8.fl = -ctx->f14.fl;
    // 0x801DE7DC: add.s       $f4, $f6, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f4.fl = ctx->f6.fl + ctx->f10.fl;
    // 0x801DE7E0: mul.s       $f6, $f8, $f16
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f6.fl = MUL_S(ctx->f8.fl, ctx->f16.fl);
    // 0x801DE7E4: nop

    // 0x801DE7E8: mul.s       $f10, $f2, $f16
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f10.fl = MUL_S(ctx->f2.fl, ctx->f16.fl);
    // 0x801DE7EC: swc1        $f4, 0x8($sp)
    MEM_W(0X8, ctx->r29) = ctx->f4.u32l;
    // 0x801DE7F0: mul.s       $f8, $f12, $f16
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f8.fl = MUL_S(ctx->f12.fl, ctx->f16.fl);
    // 0x801DE7F4: add.s       $f4, $f6, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f4.fl = ctx->f6.fl + ctx->f10.fl;
    // 0x801DE7F8: lwc1        $f10, 0x602C($at)
    ctx->f10.u32l = MEM_W(ctx->r1, 0X602C);
    // 0x801DE7FC: lui         $at, 0x40C0
    ctx->r1 = S32(0X40C0 << 16);
    // 0x801DE800: add.s       $f6, $f4, $f8
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f6.fl = ctx->f4.fl + ctx->f8.fl;
    // 0x801DE804: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x801DE808: add.s       $f4, $f6, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f4.fl = ctx->f6.fl + ctx->f10.fl;
    // 0x801DE80C: div.s       $f6, $f14, $f8
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f6.fl = DIV_S(ctx->f14.fl, ctx->f8.fl);
    // 0x801DE810: swc1        $f4, 0xC($sp)
    MEM_W(0XC, ctx->r29) = ctx->f4.u32l;
    // 0x801DE814: b           L_801DEA48
    // 0x801DE818: swc1        $f6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f6.u32l;
        goto L_801DEA48;
    // 0x801DE818: swc1        $f6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f6.u32l;
L_801DE81C:
    // 0x801DE81C: slti        $at, $a3, 0x7
    ctx->r1 = SIGNED(ctx->r7) < 0X7 ? 1 : 0;
    // 0x801DE820: bne         $at, $zero, L_801DE834
    if (ctx->r1 != 0) {
        // 0x801DE824: addiu       $t6, $a3, -0x5
        ctx->r14 = ADD32(ctx->r7, -0X5);
            goto L_801DE834;
    }
    // 0x801DE824: addiu       $t6, $a3, -0x5
    ctx->r14 = ADD32(ctx->r7, -0X5);
    // 0x801DE828: slt         $at, $a1, $t6
    ctx->r1 = SIGNED(ctx->r5) < SIGNED(ctx->r14) ? 1 : 0;
    // 0x801DE82C: beq         $at, $zero, L_801DE8C8
    if (ctx->r1 == 0) {
        // 0x801DE830: addiu       $t7, $a1, 0x5
        ctx->r15 = ADD32(ctx->r5, 0X5);
            goto L_801DE8C8;
    }
    // 0x801DE830: addiu       $t7, $a1, 0x5
    ctx->r15 = ADD32(ctx->r5, 0X5);
L_801DE834:
    // 0x801DE834: lui         $at, 0x3F00
    ctx->r1 = S32(0X3F00 << 16);
    // 0x801DE838: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
    // 0x801DE83C: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x801DE840: mtc1        $at, $f10
    ctx->f10.u32l = ctx->r1;
    // 0x801DE844: lui         $at, 0x40C0
    ctx->r1 = S32(0X40C0 << 16);
    // 0x801DE848: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x801DE84C: sub.s       $f0, $f10, $f12
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f0.fl = ctx->f10.fl - ctx->f12.fl;
    // 0x801DE850: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801DE854: mul.s       $f4, $f0, $f0
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f4.fl = MUL_S(ctx->f0.fl, ctx->f0.fl);
    // 0x801DE858: nop

    // 0x801DE85C: mul.s       $f8, $f4, $f0
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f8.fl = MUL_S(ctx->f4.fl, ctx->f0.fl);
    // 0x801DE860: div.s       $f10, $f8, $f6
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f10.fl = DIV_S(ctx->f8.fl, ctx->f6.fl);
    // 0x801DE864: lwc1        $f6, 0x6030($at)
    ctx->f6.u32l = MEM_W(ctx->r1, 0X6030);
    // 0x801DE868: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801DE86C: mul.s       $f2, $f12, $f12
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f2.fl = MUL_S(ctx->f12.fl, ctx->f12.fl);
    // 0x801DE870: nop

    // 0x801DE874: mul.s       $f14, $f2, $f12
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f14.fl = MUL_S(ctx->f2.fl, ctx->f12.fl);
    // 0x801DE878: swc1        $f10, 0x4($sp)
    MEM_W(0X4, ctx->r29) = ctx->f10.u32l;
    // 0x801DE87C: mul.s       $f4, $f14, $f16
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f4.fl = MUL_S(ctx->f14.fl, ctx->f16.fl);
    // 0x801DE880: sub.s       $f8, $f4, $f2
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f8.fl = ctx->f4.fl - ctx->f2.fl;
    // 0x801DE884: neg.s       $f4, $f14
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f14.fl); 
    ctx->f4.fl = -ctx->f14.fl;
    // 0x801DE888: add.s       $f10, $f8, $f6
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f10.fl = ctx->f8.fl + ctx->f6.fl;
    // 0x801DE88C: mul.s       $f8, $f4, $f16
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f8.fl = MUL_S(ctx->f4.fl, ctx->f16.fl);
    // 0x801DE890: nop

    // 0x801DE894: mul.s       $f6, $f2, $f16
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f6.fl = MUL_S(ctx->f2.fl, ctx->f16.fl);
    // 0x801DE898: swc1        $f10, 0x8($sp)
    MEM_W(0X8, ctx->r29) = ctx->f10.u32l;
    // 0x801DE89C: mul.s       $f4, $f12, $f16
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f4.fl = MUL_S(ctx->f12.fl, ctx->f16.fl);
    // 0x801DE8A0: add.s       $f10, $f8, $f6
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f10.fl = ctx->f8.fl + ctx->f6.fl;
    // 0x801DE8A4: lwc1        $f6, 0x6034($at)
    ctx->f6.u32l = MEM_W(ctx->r1, 0X6034);
    // 0x801DE8A8: lui         $at, 0x40C0
    ctx->r1 = S32(0X40C0 << 16);
    // 0x801DE8AC: add.s       $f8, $f10, $f4
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f8.fl = ctx->f10.fl + ctx->f4.fl;
    // 0x801DE8B0: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x801DE8B4: add.s       $f10, $f8, $f6
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f10.fl = ctx->f8.fl + ctx->f6.fl;
    // 0x801DE8B8: div.s       $f8, $f14, $f4
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f8.fl = DIV_S(ctx->f14.fl, ctx->f4.fl);
    // 0x801DE8BC: swc1        $f10, 0xC($sp)
    MEM_W(0XC, ctx->r29) = ctx->f10.u32l;
    // 0x801DE8C0: b           L_801DEA48
    // 0x801DE8C4: swc1        $f8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f8.u32l;
        goto L_801DEA48;
    // 0x801DE8C4: swc1        $f8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f8.u32l;
L_801DE8C8:
    // 0x801DE8C8: bne         $a3, $t7, L_801DE990
    if (ctx->r7 != ctx->r15) {
        // 0x801DE8CC: addiu       $t8, $a1, 0x4
        ctx->r24 = ADD32(ctx->r5, 0X4);
            goto L_801DE990;
    }
    // 0x801DE8CC: addiu       $t8, $a1, 0x4
    ctx->r24 = ADD32(ctx->r5, 0X4);
    // 0x801DE8D0: lui         $at, 0x3F00
    ctx->r1 = S32(0X3F00 << 16);
    // 0x801DE8D4: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
    // 0x801DE8D8: lui         $at, 0x3E80
    ctx->r1 = S32(0X3E80 << 16);
    // 0x801DE8DC: mtc1        $at, $f18
    ctx->f18.u32l = ctx->r1;
    // 0x801DE8E0: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x801DE8E4: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x801DE8E8: lui         $at, 0x40C0
    ctx->r1 = S32(0X40C0 << 16);
    // 0x801DE8EC: mtc1        $at, $f10
    ctx->f10.u32l = ctx->r1;
    // 0x801DE8F0: sub.s       $f0, $f6, $f12
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f0.fl = ctx->f6.fl - ctx->f12.fl;
    // 0x801DE8F4: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801DE8F8: mul.s       $f2, $f0, $f0
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f2.fl = MUL_S(ctx->f0.fl, ctx->f0.fl);
    // 0x801DE8FC: nop

    // 0x801DE900: mul.s       $f14, $f2, $f0
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f14.fl = MUL_S(ctx->f2.fl, ctx->f0.fl);
    // 0x801DE904: div.s       $f4, $f14, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f4.fl = DIV_S(ctx->f14.fl, ctx->f10.fl);
    // 0x801DE908: neg.s       $f8, $f14
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f14.fl); 
    ctx->f8.fl = -ctx->f14.fl;
    // 0x801DE90C: mul.s       $f6, $f8, $f16
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f6.fl = MUL_S(ctx->f8.fl, ctx->f16.fl);
    // 0x801DE910: nop

    // 0x801DE914: mul.s       $f10, $f2, $f16
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f10.fl = MUL_S(ctx->f2.fl, ctx->f16.fl);
    // 0x801DE918: swc1        $f4, 0x4($sp)
    MEM_W(0X4, ctx->r29) = ctx->f4.u32l;
    // 0x801DE91C: mul.s       $f8, $f0, $f16
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f8.fl = MUL_S(ctx->f0.fl, ctx->f16.fl);
    // 0x801DE920: add.s       $f4, $f6, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f4.fl = ctx->f6.fl + ctx->f10.fl;
    // 0x801DE924: lwc1        $f10, 0x6038($at)
    ctx->f10.u32l = MEM_W(ctx->r1, 0X6038);
    // 0x801DE928: lui         $at, 0x40E0
    ctx->r1 = S32(0X40E0 << 16);
    // 0x801DE92C: add.s       $f6, $f4, $f8
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f6.fl = ctx->f4.fl + ctx->f8.fl;
    // 0x801DE930: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x801DE934: lui         $at, 0x4140
    ctx->r1 = S32(0X4140 << 16);
    // 0x801DE938: add.s       $f4, $f6, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f4.fl = ctx->f6.fl + ctx->f10.fl;
    // 0x801DE93C: mul.s       $f6, $f14, $f8
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f6.fl = MUL_S(ctx->f14.fl, ctx->f8.fl);
    // 0x801DE940: mtc1        $at, $f10
    ctx->f10.u32l = ctx->r1;
    // 0x801DE944: lui         $at, 0x40A0
    ctx->r1 = S32(0X40A0 << 16);
    // 0x801DE948: swc1        $f4, 0x8($sp)
    MEM_W(0X8, ctx->r29) = ctx->f4.u32l;
    // 0x801DE94C: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x801DE950: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801DE954: div.s       $f4, $f6, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f4.fl = DIV_S(ctx->f6.fl, ctx->f10.fl);
    // 0x801DE958: mul.s       $f6, $f2, $f8
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f6.fl = MUL_S(ctx->f2.fl, ctx->f8.fl);
    // 0x801DE95C: nop

    // 0x801DE960: mul.s       $f10, $f6, $f18
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f10.fl = MUL_S(ctx->f6.fl, ctx->f18.fl);
    // 0x801DE964: sub.s       $f8, $f4, $f10
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f8.fl = ctx->f4.fl - ctx->f10.fl;
    // 0x801DE968: mul.s       $f6, $f0, $f18
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f6.fl = MUL_S(ctx->f0.fl, ctx->f18.fl);
    // 0x801DE96C: lwc1        $f10, 0x603C($at)
    ctx->f10.u32l = MEM_W(ctx->r1, 0X603C);
    // 0x801DE970: add.s       $f4, $f8, $f6
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f4.fl = ctx->f8.fl + ctx->f6.fl;
    // 0x801DE974: mul.s       $f6, $f12, $f12
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f6.fl = MUL_S(ctx->f12.fl, ctx->f12.fl);
    // 0x801DE978: add.s       $f8, $f4, $f10
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f8.fl = ctx->f4.fl + ctx->f10.fl;
    // 0x801DE97C: mul.s       $f4, $f6, $f12
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f4.fl = MUL_S(ctx->f6.fl, ctx->f12.fl);
    // 0x801DE980: swc1        $f8, 0xC($sp)
    MEM_W(0XC, ctx->r29) = ctx->f8.u32l;
    // 0x801DE984: mul.s       $f10, $f4, $f18
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f10.fl = MUL_S(ctx->f4.fl, ctx->f18.fl);
    // 0x801DE988: b           L_801DEA48
    // 0x801DE98C: swc1        $f10, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f10.u32l;
        goto L_801DEA48;
    // 0x801DE98C: swc1        $f10, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f10.u32l;
L_801DE990:
    // 0x801DE990: bne         $a3, $t8, L_801DEA48
    if (ctx->r7 != ctx->r24) {
        // 0x801DE994: lui         $at, 0x3F00
        ctx->r1 = S32(0X3F00 << 16);
            goto L_801DEA48;
    }
    // 0x801DE994: lui         $at, 0x3F00
    ctx->r1 = S32(0X3F00 << 16);
    // 0x801DE998: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
    // 0x801DE99C: lui         $at, 0x4040
    ctx->r1 = S32(0X4040 << 16);
    // 0x801DE9A0: mtc1        $at, $f18
    ctx->f18.u32l = ctx->r1;
    // 0x801DE9A4: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x801DE9A8: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x801DE9AC: lui         $at, 0x40C0
    ctx->r1 = S32(0X40C0 << 16);
    // 0x801DE9B0: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x801DE9B4: sub.s       $f0, $f8, $f12
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f0.fl = ctx->f8.fl - ctx->f12.fl;
    // 0x801DE9B8: lui         $at, 0x4130
    ctx->r1 = S32(0X4130 << 16);
    // 0x801DE9BC: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x801DE9C0: lui         $at, 0x4140
    ctx->r1 = S32(0X4140 << 16);
    // 0x801DE9C4: mul.s       $f2, $f0, $f0
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f2.fl = MUL_S(ctx->f0.fl, ctx->f0.fl);
    // 0x801DE9C8: nop

    // 0x801DE9CC: mul.s       $f14, $f2, $f0
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f14.fl = MUL_S(ctx->f2.fl, ctx->f0.fl);
    // 0x801DE9D0: div.s       $f4, $f14, $f6
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f4.fl = DIV_S(ctx->f14.fl, ctx->f6.fl);
    // 0x801DE9D4: neg.s       $f10, $f14
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f14.fl); 
    ctx->f10.fl = -ctx->f14.fl;
    // 0x801DE9D8: mul.s       $f6, $f10, $f8
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f6.fl = MUL_S(ctx->f10.fl, ctx->f8.fl);
    // 0x801DE9DC: nop

    // 0x801DE9E0: mul.s       $f8, $f2, $f18
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f8.fl = MUL_S(ctx->f2.fl, ctx->f18.fl);
    // 0x801DE9E4: swc1        $f4, 0x4($sp)
    MEM_W(0X4, ctx->r29) = ctx->f4.u32l;
    // 0x801DE9E8: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x801DE9EC: lui         $at, 0x41A8
    ctx->r1 = S32(0X41A8 << 16);
    // 0x801DE9F0: div.s       $f10, $f6, $f4
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f10.fl = DIV_S(ctx->f6.fl, ctx->f4.fl);
    // 0x801DE9F4: mul.s       $f6, $f8, $f16
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f6.fl = MUL_S(ctx->f8.fl, ctx->f16.fl);
    // 0x801DE9F8: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x801DE9FC: lui         $at, 0x4140
    ctx->r1 = S32(0X4140 << 16);
    // 0x801DEA00: add.s       $f4, $f10, $f6
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f4.fl = ctx->f10.fl + ctx->f6.fl;
    // 0x801DEA04: mul.s       $f10, $f14, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = MUL_S(ctx->f14.fl, ctx->f8.fl);
    // 0x801DEA08: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x801DEA0C: lui         $at, 0x4110
    ctx->r1 = S32(0X4110 << 16);
    // 0x801DEA10: swc1        $f4, 0x8($sp)
    MEM_W(0X8, ctx->r29) = ctx->f4.u32l;
    // 0x801DEA14: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x801DEA18: div.s       $f4, $f10, $f6
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f4.fl = DIV_S(ctx->f10.fl, ctx->f6.fl);
    // 0x801DEA1C: mul.s       $f10, $f2, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = MUL_S(ctx->f2.fl, ctx->f8.fl);
    // 0x801DEA20: nop

    // 0x801DEA24: mul.s       $f6, $f10, $f16
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f6.fl = MUL_S(ctx->f10.fl, ctx->f16.fl);
    // 0x801DEA28: sub.s       $f8, $f4, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = ctx->f4.fl - ctx->f6.fl;
    // 0x801DEA2C: mul.s       $f10, $f0, $f18
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f10.fl = MUL_S(ctx->f0.fl, ctx->f18.fl);
    // 0x801DEA30: nop

    // 0x801DEA34: mul.s       $f6, $f12, $f12
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f6.fl = MUL_S(ctx->f12.fl, ctx->f12.fl);
    // 0x801DEA38: add.s       $f4, $f8, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f4.fl = ctx->f8.fl + ctx->f10.fl;
    // 0x801DEA3C: mul.s       $f8, $f6, $f12
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f8.fl = MUL_S(ctx->f6.fl, ctx->f12.fl);
    // 0x801DEA40: swc1        $f4, 0xC($sp)
    MEM_W(0XC, ctx->r29) = ctx->f4.u32l;
    // 0x801DEA44: swc1        $f8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f8.u32l;
L_801DEA48:
    // 0x801DEA48: sll         $t9, $a1, 2
    ctx->r25 = S32(ctx->r5 << 2);
    // 0x801DEA4C: addu        $v0, $a2, $t9
    ctx->r2 = ADD32(ctx->r6, ctx->r25);
    // 0x801DEA50: lwc1        $f4, 0x0($v0)
    ctx->f4.u32l = MEM_W(ctx->r2, 0X0);
    // 0x801DEA54: lwc1        $f10, 0x4($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0X4);
    // 0x801DEA58: lwc1        $f8, 0x8($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X8);
    // 0x801DEA5C: mul.s       $f6, $f10, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = MUL_S(ctx->f10.fl, ctx->f4.fl);
    // 0x801DEA60: lwc1        $f10, 0x4($v0)
    ctx->f10.u32l = MEM_W(ctx->r2, 0X4);
    // 0x801DEA64: mul.s       $f4, $f8, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f4.fl = MUL_S(ctx->f8.fl, ctx->f10.fl);
    // 0x801DEA68: lwc1        $f10, 0xC($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0XC);
    // 0x801DEA6C: add.s       $f8, $f6, $f4
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f8.fl = ctx->f6.fl + ctx->f4.fl;
    // 0x801DEA70: lwc1        $f6, 0x8($v0)
    ctx->f6.u32l = MEM_W(ctx->r2, 0X8);
    // 0x801DEA74: mul.s       $f4, $f10, $f6
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f4.fl = MUL_S(ctx->f10.fl, ctx->f6.fl);
    // 0x801DEA78: lwc1        $f6, 0xC($v0)
    ctx->f6.u32l = MEM_W(ctx->r2, 0XC);
    // 0x801DEA7C: add.s       $f10, $f8, $f4
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f10.fl = ctx->f8.fl + ctx->f4.fl;
    // 0x801DEA80: lwc1        $f8, 0x10($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X10);
    // 0x801DEA84: addiu       $sp, $sp, 0x28
    ctx->r29 = ADD32(ctx->r29, 0X28);
    // 0x801DEA88: mul.s       $f4, $f6, $f8
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f4.fl = MUL_S(ctx->f6.fl, ctx->f8.fl);
    // 0x801DEA8C: jr          $ra
    // 0x801DEA90: add.s       $f0, $f4, $f10
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f0.fl = ctx->f4.fl + ctx->f10.fl;
    return;
    // 0x801DEA90: add.s       $f0, $f4, $f10
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f0.fl = ctx->f4.fl + ctx->f10.fl;
;}
RECOMP_FUNC void func_801DEA94(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801DEA94: blez        $a1, L_801DEB00
    if (SIGNED(ctx->r5) <= 0) {
        // 0x801DEA98: or          $v0, $zero, $zero
        ctx->r2 = 0 | 0;
            goto L_801DEB00;
    }
    // 0x801DEA98: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    // 0x801DEA9C: andi        $a3, $a1, 0x3
    ctx->r7 = ctx->r5 & 0X3;
    // 0x801DEAA0: beq         $a3, $zero, L_801DEAC8
    if (ctx->r7 == 0) {
        // 0x801DEAA4: or          $a2, $a3, $zero
        ctx->r6 = ctx->r7 | 0;
            goto L_801DEAC8;
    }
    // 0x801DEAA4: or          $a2, $a3, $zero
    ctx->r6 = ctx->r7 | 0;
    // 0x801DEAA8: sll         $t6, $zero, 3
    ctx->r14 = S32(0 << 3);
    // 0x801DEAAC: addu        $v1, $a0, $t6
    ctx->r3 = ADD32(ctx->r4, ctx->r14);
L_801DEAB0:
    // 0x801DEAB0: addiu       $v0, $v0, 0x1
    ctx->r2 = ADD32(ctx->r2, 0X1);
    // 0x801DEAB4: sw          $zero, 0x4($v1)
    MEM_W(0X4, ctx->r3) = 0;
    // 0x801DEAB8: sw          $zero, 0x0($v1)
    MEM_W(0X0, ctx->r3) = 0;
    // 0x801DEABC: bne         $a2, $v0, L_801DEAB0
    if (ctx->r6 != ctx->r2) {
        // 0x801DEAC0: addiu       $v1, $v1, 0x8
        ctx->r3 = ADD32(ctx->r3, 0X8);
            goto L_801DEAB0;
    }
    // 0x801DEAC0: addiu       $v1, $v1, 0x8
    ctx->r3 = ADD32(ctx->r3, 0X8);
    // 0x801DEAC4: beq         $v0, $a1, L_801DEB00
    if (ctx->r2 == ctx->r5) {
        // 0x801DEAC8: sll         $t7, $v0, 3
        ctx->r15 = S32(ctx->r2 << 3);
            goto L_801DEB00;
    }
L_801DEAC8:
    // 0x801DEAC8: sll         $t7, $v0, 3
    ctx->r15 = S32(ctx->r2 << 3);
    // 0x801DEACC: sll         $t8, $a1, 3
    ctx->r24 = S32(ctx->r5 << 3);
    // 0x801DEAD0: addu        $a2, $t8, $a0
    ctx->r6 = ADD32(ctx->r24, ctx->r4);
    // 0x801DEAD4: addu        $v1, $a0, $t7
    ctx->r3 = ADD32(ctx->r4, ctx->r15);
L_801DEAD8:
    // 0x801DEAD8: addiu       $v1, $v1, 0x20
    ctx->r3 = ADD32(ctx->r3, 0X20);
    // 0x801DEADC: sw          $zero, -0x14($v1)
    MEM_W(-0X14, ctx->r3) = 0;
    // 0x801DEAE0: sw          $zero, -0x18($v1)
    MEM_W(-0X18, ctx->r3) = 0;
    // 0x801DEAE4: sw          $zero, -0xC($v1)
    MEM_W(-0XC, ctx->r3) = 0;
    // 0x801DEAE8: sw          $zero, -0x10($v1)
    MEM_W(-0X10, ctx->r3) = 0;
    // 0x801DEAEC: sw          $zero, -0x4($v1)
    MEM_W(-0X4, ctx->r3) = 0;
    // 0x801DEAF0: sw          $zero, -0x8($v1)
    MEM_W(-0X8, ctx->r3) = 0;
    // 0x801DEAF4: sw          $zero, -0x1C($v1)
    MEM_W(-0X1C, ctx->r3) = 0;
    // 0x801DEAF8: bne         $v1, $a2, L_801DEAD8
    if (ctx->r3 != ctx->r6) {
        // 0x801DEAFC: sw          $zero, -0x20($v1)
        MEM_W(-0X20, ctx->r3) = 0;
            goto L_801DEAD8;
    }
    // 0x801DEAFC: sw          $zero, -0x20($v1)
    MEM_W(-0X20, ctx->r3) = 0;
L_801DEB00:
    // 0x801DEB00: jr          $ra
    // 0x801DEB04: nop

    return;
    // 0x801DEB04: nop

;}
RECOMP_FUNC void func_801DEB08(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801DEB08: addiu       $sp, $sp, -0x28
    ctx->r29 = ADD32(ctx->r29, -0X28);
    // 0x801DEB0C: sw          $ra, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r31;
    // 0x801DEB10: sw          $s2, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r18;
    // 0x801DEB14: sw          $s1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r17;
    // 0x801DEB18: sw          $s0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r16;
    // 0x801DEB1C: sw          $a0, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r4;
    // 0x801DEB20: lw          $s0, 0x4($a1)
    ctx->r16 = MEM_W(ctx->r5, 0X4);
    // 0x801DEB24: lw          $t6, 0x8($a2)
    ctx->r14 = MEM_W(ctx->r6, 0X8);
    // 0x801DEB28: or          $s1, $a1, $zero
    ctx->r17 = ctx->r5 | 0;
    // 0x801DEB2C: sll         $t7, $s0, 2
    ctx->r15 = S32(ctx->r16 << 2);
    // 0x801DEB30: addu        $t8, $t6, $t7
    ctx->r24 = ADD32(ctx->r14, ctx->r15);
    // 0x801DEB34: lw          $v0, 0x0($t8)
    ctx->r2 = MEM_W(ctx->r24, 0X0);
    // 0x801DEB38: or          $s2, $a2, $zero
    ctx->r18 = ctx->r6 | 0;
    // 0x801DEB3C: bne         $v0, $zero, L_801DEB64
    if (ctx->r2 != 0) {
        // 0x801DEB40: addiu       $t9, $s0, 0x1
        ctx->r25 = ADD32(ctx->r16, 0X1);
            goto L_801DEB64;
    }
    // 0x801DEB40: addiu       $t9, $s0, 0x1
    ctx->r25 = ADD32(ctx->r16, 0X1);
L_801DEB44:
    // 0x801DEB44: sw          $t9, 0x4($s1)
    MEM_W(0X4, ctx->r17) = ctx->r25;
    // 0x801DEB48: lw          $t0, 0x8($s2)
    ctx->r8 = MEM_W(ctx->r18, 0X8);
    // 0x801DEB4C: sll         $t1, $t9, 2
    ctx->r9 = S32(ctx->r25 << 2);
    // 0x801DEB50: or          $s0, $t9, $zero
    ctx->r16 = ctx->r25 | 0;
    // 0x801DEB54: addu        $t2, $t0, $t1
    ctx->r10 = ADD32(ctx->r8, ctx->r9);
    // 0x801DEB58: lw          $v0, 0x0($t2)
    ctx->r2 = MEM_W(ctx->r10, 0X0);
    // 0x801DEB5C: beql        $v0, $zero, L_801DEB44
    if (ctx->r2 == 0) {
        // 0x801DEB60: addiu       $t9, $s0, 0x1
        ctx->r25 = ADD32(ctx->r16, 0X1);
            goto L_801DEB44;
    }
    goto skip_0;
    // 0x801DEB60: addiu       $t9, $s0, 0x1
    ctx->r25 = ADD32(ctx->r16, 0X1);
    skip_0:
L_801DEB64:
    // 0x801DEB64: lw          $t3, 0x0($s1)
    ctx->r11 = MEM_W(ctx->r17, 0X0);
    // 0x801DEB68: mtc1        $v0, $f8
    ctx->f8.u32l = ctx->r2;
    // 0x801DEB6C: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    // 0x801DEB70: mtc1        $t3, $f4
    ctx->f4.u32l = ctx->r11;
    // 0x801DEB74: cvt.s.w     $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.fl = CVT_S_W(ctx->f8.u32l);
    // 0x801DEB78: lw          $a2, 0x4($s2)
    ctx->r6 = MEM_W(ctx->r18, 0X4);
    // 0x801DEB7C: lw          $a3, 0x0($s2)
    ctx->r7 = MEM_W(ctx->r18, 0X0);
    // 0x801DEB80: cvt.s.w     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
    // 0x801DEB84: jal         0x801DE690
    // 0x801DEB88: div.s       $f12, $f6, $f10
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f12.fl = DIV_S(ctx->f6.fl, ctx->f10.fl);
    func_801DE690(rdram, ctx);
        goto after_0;
    // 0x801DEB88: div.s       $f12, $f6, $f10
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f12.fl = DIV_S(ctx->f6.fl, ctx->f10.fl);
    after_0:
    // 0x801DEB8C: lw          $t4, 0x28($sp)
    ctx->r12 = MEM_W(ctx->r29, 0X28);
    // 0x801DEB90: swc1        $f0, 0x0($t4)
    MEM_W(0X0, ctx->r12) = ctx->f0.u32l;
    // 0x801DEB94: lw          $t5, 0x0($s1)
    ctx->r13 = MEM_W(ctx->r17, 0X0);
    // 0x801DEB98: lw          $s0, 0x4($s1)
    ctx->r16 = MEM_W(ctx->r17, 0X4);
    // 0x801DEB9C: addiu       $t6, $t5, 0x1
    ctx->r14 = ADD32(ctx->r13, 0X1);
    // 0x801DEBA0: sw          $t6, 0x0($s1)
    MEM_W(0X0, ctx->r17) = ctx->r14;
    // 0x801DEBA4: lw          $t8, 0x8($s2)
    ctx->r24 = MEM_W(ctx->r18, 0X8);
    // 0x801DEBA8: sll         $t9, $s0, 2
    ctx->r25 = S32(ctx->r16 << 2);
    // 0x801DEBAC: addiu       $t2, $s0, 0x1
    ctx->r10 = ADD32(ctx->r16, 0X1);
    // 0x801DEBB0: addu        $t0, $t8, $t9
    ctx->r8 = ADD32(ctx->r24, ctx->r25);
    // 0x801DEBB4: lw          $t1, 0x0($t0)
    ctx->r9 = MEM_W(ctx->r8, 0X0);
    // 0x801DEBB8: slt         $at, $t6, $t1
    ctx->r1 = SIGNED(ctx->r14) < SIGNED(ctx->r9) ? 1 : 0;
    // 0x801DEBBC: bnel        $at, $zero, L_801DEBEC
    if (ctx->r1 != 0) {
        // 0x801DEBC0: lw          $ra, 0x24($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X24);
            goto L_801DEBEC;
    }
    goto skip_1;
    // 0x801DEBC0: lw          $ra, 0x24($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X24);
    skip_1:
    // 0x801DEBC4: sw          $zero, 0x0($s1)
    MEM_W(0X0, ctx->r17) = 0;
    // 0x801DEBC8: sw          $t2, 0x4($s1)
    MEM_W(0X4, ctx->r17) = ctx->r10;
    // 0x801DEBCC: lw          $t4, 0x0($s2)
    ctx->r12 = MEM_W(ctx->r18, 0X0);
    // 0x801DEBD0: addiu       $t6, $zero, -0x1
    ctx->r14 = ADD32(0, -0X1);
    // 0x801DEBD4: addiu       $t5, $t4, -0x3
    ctx->r13 = ADD32(ctx->r12, -0X3);
    // 0x801DEBD8: slt         $at, $t2, $t5
    ctx->r1 = SIGNED(ctx->r10) < SIGNED(ctx->r13) ? 1 : 0;
    // 0x801DEBDC: bnel        $at, $zero, L_801DEBEC
    if (ctx->r1 != 0) {
        // 0x801DEBE0: lw          $ra, 0x24($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X24);
            goto L_801DEBEC;
    }
    goto skip_2;
    // 0x801DEBE0: lw          $ra, 0x24($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X24);
    skip_2:
    // 0x801DEBE4: sw          $t6, 0x4($s1)
    MEM_W(0X4, ctx->r17) = ctx->r14;
    // 0x801DEBE8: lw          $ra, 0x24($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X24);
L_801DEBEC:
    // 0x801DEBEC: lw          $s0, 0x18($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X18);
    // 0x801DEBF0: lw          $s1, 0x1C($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X1C);
    // 0x801DEBF4: lw          $s2, 0x20($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X20);
    // 0x801DEBF8: jr          $ra
    // 0x801DEBFC: addiu       $sp, $sp, 0x28
    ctx->r29 = ADD32(ctx->r29, 0X28);
    return;
    // 0x801DEBFC: addiu       $sp, $sp, 0x28
    ctx->r29 = ADD32(ctx->r29, 0X28);
;}
RECOMP_FUNC void func_801DEC00(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801DEC00: addiu       $sp, $sp, -0x38
    ctx->r29 = ADD32(ctx->r29, -0X38);
    // 0x801DEC04: sw          $ra, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r31;
    // 0x801DEC08: sw          $s6, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r22;
    // 0x801DEC0C: sw          $s5, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r21;
    // 0x801DEC10: sw          $s4, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r20;
    // 0x801DEC14: sw          $s3, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r19;
    // 0x801DEC18: sw          $s2, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r18;
    // 0x801DEC1C: sw          $s1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r17;
    // 0x801DEC20: sw          $s0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r16;
    // 0x801DEC24: lw          $s0, 0x4($a1)
    ctx->r16 = MEM_W(ctx->r5, 0X4);
    // 0x801DEC28: lw          $t6, 0x10($a2)
    ctx->r14 = MEM_W(ctx->r6, 0X10);
    // 0x801DEC2C: or          $s5, $a2, $zero
    ctx->r21 = ctx->r6 | 0;
    // 0x801DEC30: sll         $t7, $s0, 2
    ctx->r15 = S32(ctx->r16 << 2);
    // 0x801DEC34: addu        $t8, $t6, $t7
    ctx->r24 = ADD32(ctx->r14, ctx->r15);
    // 0x801DEC38: lw          $t9, 0x0($t8)
    ctx->r25 = MEM_W(ctx->r24, 0X0);
    // 0x801DEC3C: or          $s4, $a1, $zero
    ctx->r20 = ctx->r5 | 0;
    // 0x801DEC40: or          $s2, $s5, $zero
    ctx->r18 = ctx->r21 | 0;
    // 0x801DEC44: bne         $t9, $zero, L_801DEC70
    if (ctx->r25 != 0) {
        // 0x801DEC48: or          $s1, $zero, $zero
        ctx->r17 = 0 | 0;
            goto L_801DEC70;
    }
    // 0x801DEC48: or          $s1, $zero, $zero
    ctx->r17 = 0 | 0;
    // 0x801DEC4C: addiu       $t0, $s0, 0x1
    ctx->r8 = ADD32(ctx->r16, 0X1);
L_801DEC50:
    // 0x801DEC50: sw          $t0, 0x4($s4)
    MEM_W(0X4, ctx->r20) = ctx->r8;
    // 0x801DEC54: lw          $t1, 0x10($s5)
    ctx->r9 = MEM_W(ctx->r21, 0X10);
    // 0x801DEC58: sll         $t2, $t0, 2
    ctx->r10 = S32(ctx->r8 << 2);
    // 0x801DEC5C: or          $s0, $t0, $zero
    ctx->r16 = ctx->r8 | 0;
    // 0x801DEC60: addu        $t3, $t1, $t2
    ctx->r11 = ADD32(ctx->r9, ctx->r10);
    // 0x801DEC64: lw          $t4, 0x0($t3)
    ctx->r12 = MEM_W(ctx->r11, 0X0);
    // 0x801DEC68: beql        $t4, $zero, L_801DEC50
    if (ctx->r12 == 0) {
        // 0x801DEC6C: addiu       $t0, $s0, 0x1
        ctx->r8 = ADD32(ctx->r16, 0X1);
            goto L_801DEC50;
    }
    goto skip_0;
    // 0x801DEC6C: addiu       $t0, $s0, 0x1
    ctx->r8 = ADD32(ctx->r16, 0X1);
    skip_0:
L_801DEC70:
    // 0x801DEC70: or          $s3, $a0, $zero
    ctx->r19 = ctx->r4 | 0;
    // 0x801DEC74: addiu       $s6, $zero, 0x3
    ctx->r22 = ADD32(0, 0X3);
L_801DEC78:
    // 0x801DEC78: lw          $s0, 0x4($s4)
    ctx->r16 = MEM_W(ctx->r20, 0X4);
    // 0x801DEC7C: lw          $t5, 0x10($s5)
    ctx->r13 = MEM_W(ctx->r21, 0X10);
    // 0x801DEC80: lw          $t9, 0x0($s4)
    ctx->r25 = MEM_W(ctx->r20, 0X0);
    // 0x801DEC84: sll         $t6, $s0, 2
    ctx->r14 = S32(ctx->r16 << 2);
    // 0x801DEC88: addu        $t7, $t5, $t6
    ctx->r15 = ADD32(ctx->r13, ctx->r14);
    // 0x801DEC8C: lw          $t8, 0x0($t7)
    ctx->r24 = MEM_W(ctx->r15, 0X0);
    // 0x801DEC90: mtc1        $t9, $f8
    ctx->f8.u32l = ctx->r25;
    // 0x801DEC94: lw          $a2, 0x4($s2)
    ctx->r6 = MEM_W(ctx->r18, 0X4);
    // 0x801DEC98: mtc1        $t8, $f4
    ctx->f4.u32l = ctx->r24;
    // 0x801DEC9C: cvt.s.w     $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.fl = CVT_S_W(ctx->f8.u32l);
    // 0x801DECA0: lw          $a3, 0x0($s5)
    ctx->r7 = MEM_W(ctx->r21, 0X0);
    // 0x801DECA4: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    // 0x801DECA8: cvt.s.w     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
    // 0x801DECAC: jal         0x801DE690
    // 0x801DECB0: div.s       $f12, $f10, $f6
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f12.fl = DIV_S(ctx->f10.fl, ctx->f6.fl);
    func_801DE690(rdram, ctx);
        goto after_0;
    // 0x801DECB0: div.s       $f12, $f10, $f6
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f12.fl = DIV_S(ctx->f10.fl, ctx->f6.fl);
    after_0:
    // 0x801DECB4: addiu       $s1, $s1, 0x1
    ctx->r17 = ADD32(ctx->r17, 0X1);
    // 0x801DECB8: addiu       $s2, $s2, 0x4
    ctx->r18 = ADD32(ctx->r18, 0X4);
    // 0x801DECBC: addiu       $s3, $s3, 0x4
    ctx->r19 = ADD32(ctx->r19, 0X4);
    // 0x801DECC0: bne         $s1, $s6, L_801DEC78
    if (ctx->r17 != ctx->r22) {
        // 0x801DECC4: swc1        $f0, -0x4($s3)
        MEM_W(-0X4, ctx->r19) = ctx->f0.u32l;
            goto L_801DEC78;
    }
    // 0x801DECC4: swc1        $f0, -0x4($s3)
    MEM_W(-0X4, ctx->r19) = ctx->f0.u32l;
    // 0x801DECC8: lw          $t0, 0x0($s4)
    ctx->r8 = MEM_W(ctx->r20, 0X0);
    // 0x801DECCC: lw          $s0, 0x4($s4)
    ctx->r16 = MEM_W(ctx->r20, 0X4);
    // 0x801DECD0: addiu       $t1, $t0, 0x1
    ctx->r9 = ADD32(ctx->r8, 0X1);
    // 0x801DECD4: sw          $t1, 0x0($s4)
    MEM_W(0X0, ctx->r20) = ctx->r9;
    // 0x801DECD8: lw          $t3, 0x10($s5)
    ctx->r11 = MEM_W(ctx->r21, 0X10);
    // 0x801DECDC: sll         $t4, $s0, 2
    ctx->r12 = S32(ctx->r16 << 2);
    // 0x801DECE0: addiu       $t7, $s0, 0x1
    ctx->r15 = ADD32(ctx->r16, 0X1);
    // 0x801DECE4: addu        $t5, $t3, $t4
    ctx->r13 = ADD32(ctx->r11, ctx->r12);
    // 0x801DECE8: lw          $t6, 0x0($t5)
    ctx->r14 = MEM_W(ctx->r13, 0X0);
    // 0x801DECEC: slt         $at, $t1, $t6
    ctx->r1 = SIGNED(ctx->r9) < SIGNED(ctx->r14) ? 1 : 0;
    // 0x801DECF0: bnel        $at, $zero, L_801DED20
    if (ctx->r1 != 0) {
        // 0x801DECF4: lw          $ra, 0x34($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X34);
            goto L_801DED20;
    }
    goto skip_1;
    // 0x801DECF4: lw          $ra, 0x34($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X34);
    skip_1:
    // 0x801DECF8: sw          $zero, 0x0($s4)
    MEM_W(0X0, ctx->r20) = 0;
    // 0x801DECFC: sw          $t7, 0x4($s4)
    MEM_W(0X4, ctx->r20) = ctx->r15;
    // 0x801DED00: lw          $t9, 0x0($s5)
    ctx->r25 = MEM_W(ctx->r21, 0X0);
    // 0x801DED04: addiu       $t1, $zero, -0x1
    ctx->r9 = ADD32(0, -0X1);
    // 0x801DED08: addiu       $t0, $t9, -0x3
    ctx->r8 = ADD32(ctx->r25, -0X3);
    // 0x801DED0C: slt         $at, $t7, $t0
    ctx->r1 = SIGNED(ctx->r15) < SIGNED(ctx->r8) ? 1 : 0;
    // 0x801DED10: bnel        $at, $zero, L_801DED20
    if (ctx->r1 != 0) {
        // 0x801DED14: lw          $ra, 0x34($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X34);
            goto L_801DED20;
    }
    goto skip_2;
    // 0x801DED14: lw          $ra, 0x34($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X34);
    skip_2:
    // 0x801DED18: sw          $t1, 0x4($s4)
    MEM_W(0X4, ctx->r20) = ctx->r9;
    // 0x801DED1C: lw          $ra, 0x34($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X34);
L_801DED20:
    // 0x801DED20: lw          $s0, 0x18($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X18);
    // 0x801DED24: lw          $s1, 0x1C($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X1C);
    // 0x801DED28: lw          $s2, 0x20($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X20);
    // 0x801DED2C: lw          $s3, 0x24($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X24);
    // 0x801DED30: lw          $s4, 0x28($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X28);
    // 0x801DED34: lw          $s5, 0x2C($sp)
    ctx->r21 = MEM_W(ctx->r29, 0X2C);
    // 0x801DED38: lw          $s6, 0x30($sp)
    ctx->r22 = MEM_W(ctx->r29, 0X30);
    // 0x801DED3C: jr          $ra
    // 0x801DED40: addiu       $sp, $sp, 0x38
    ctx->r29 = ADD32(ctx->r29, 0X38);
    return;
    // 0x801DED40: addiu       $sp, $sp, 0x38
    ctx->r29 = ADD32(ctx->r29, 0X38);
;}
RECOMP_FUNC void func_801DED44(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801DED44: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x801DED48: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x801DED4C: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    // 0x801DED50: sw          $a1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r5;
    // 0x801DED54: jal         0x801DEC00
    // 0x801DED58: sw          $a2, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r6;
    func_801DEC00(rdram, ctx);
        goto after_0;
    // 0x801DED58: sw          $a2, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r6;
    after_0:
    // 0x801DED5C: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
    // 0x801DED60: lw          $a1, 0x1C($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X1C);
    // 0x801DED64: lw          $a2, 0x20($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X20);
    // 0x801DED68: addiu       $a0, $a0, 0xC
    ctx->r4 = ADD32(ctx->r4, 0XC);
    // 0x801DED6C: addiu       $a1, $a1, 0x8
    ctx->r5 = ADD32(ctx->r5, 0X8);
    // 0x801DED70: jal         0x801DEC00
    // 0x801DED74: addiu       $a2, $a2, 0x14
    ctx->r6 = ADD32(ctx->r6, 0X14);
    func_801DEC00(rdram, ctx);
        goto after_1;
    // 0x801DED74: addiu       $a2, $a2, 0x14
    ctx->r6 = ADD32(ctx->r6, 0X14);
    after_1:
    // 0x801DED78: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x801DED7C: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x801DED80: jr          $ra
    // 0x801DED84: nop

    return;
    // 0x801DED84: nop

;}
RECOMP_FUNC void func_801DED88(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801DED88: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x801DED8C: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x801DED90: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    // 0x801DED94: sw          $a1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r5;
    // 0x801DED98: jal         0x801DEC00
    // 0x801DED9C: sw          $a2, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r6;
    func_801DEC00(rdram, ctx);
        goto after_0;
    // 0x801DED9C: sw          $a2, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r6;
    after_0:
    // 0x801DEDA0: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
    // 0x801DEDA4: lw          $a1, 0x1C($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X1C);
    // 0x801DEDA8: lw          $a2, 0x20($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X20);
    // 0x801DEDAC: addiu       $a0, $a0, 0xC
    ctx->r4 = ADD32(ctx->r4, 0XC);
    // 0x801DEDB0: addiu       $a1, $a1, 0x8
    ctx->r5 = ADD32(ctx->r5, 0X8);
    // 0x801DEDB4: jal         0x801DEC00
    // 0x801DEDB8: addiu       $a2, $a2, 0x14
    ctx->r6 = ADD32(ctx->r6, 0X14);
    func_801DEC00(rdram, ctx);
        goto after_1;
    // 0x801DEDB8: addiu       $a2, $a2, 0x14
    ctx->r6 = ADD32(ctx->r6, 0X14);
    after_1:
    // 0x801DEDBC: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
    // 0x801DEDC0: lw          $a1, 0x1C($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X1C);
    // 0x801DEDC4: lw          $a2, 0x20($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X20);
    // 0x801DEDC8: addiu       $a0, $a0, 0x18
    ctx->r4 = ADD32(ctx->r4, 0X18);
    // 0x801DEDCC: addiu       $a1, $a1, 0x10
    ctx->r5 = ADD32(ctx->r5, 0X10);
    // 0x801DEDD0: jal         0x801DEC00
    // 0x801DEDD4: addiu       $a2, $a2, 0x28
    ctx->r6 = ADD32(ctx->r6, 0X28);
    func_801DEC00(rdram, ctx);
        goto after_2;
    // 0x801DEDD4: addiu       $a2, $a2, 0x28
    ctx->r6 = ADD32(ctx->r6, 0X28);
    after_2:
    // 0x801DEDD8: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x801DEDDC: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x801DEDE0: jr          $ra
    // 0x801DEDE4: nop

    return;
    // 0x801DEDE4: nop

;}
RECOMP_FUNC void func_801DEDE8(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801DEDE8: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x801DEDEC: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x801DEDF0: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    // 0x801DEDF4: sw          $a1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r5;
    // 0x801DEDF8: jal         0x801DEC00
    // 0x801DEDFC: sw          $a2, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r6;
    func_801DEC00(rdram, ctx);
        goto after_0;
    // 0x801DEDFC: sw          $a2, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r6;
    after_0:
    // 0x801DEE00: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
    // 0x801DEE04: lw          $a1, 0x1C($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X1C);
    // 0x801DEE08: lw          $a2, 0x20($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X20);
    // 0x801DEE0C: addiu       $a0, $a0, 0xC
    ctx->r4 = ADD32(ctx->r4, 0XC);
    // 0x801DEE10: addiu       $a1, $a1, 0x8
    ctx->r5 = ADD32(ctx->r5, 0X8);
    // 0x801DEE14: jal         0x801DEC00
    // 0x801DEE18: addiu       $a2, $a2, 0x14
    ctx->r6 = ADD32(ctx->r6, 0X14);
    func_801DEC00(rdram, ctx);
        goto after_1;
    // 0x801DEE18: addiu       $a2, $a2, 0x14
    ctx->r6 = ADD32(ctx->r6, 0X14);
    after_1:
    // 0x801DEE1C: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
    // 0x801DEE20: lw          $a1, 0x1C($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X1C);
    // 0x801DEE24: lw          $a2, 0x20($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X20);
    // 0x801DEE28: addiu       $a0, $a0, 0x18
    ctx->r4 = ADD32(ctx->r4, 0X18);
    // 0x801DEE2C: addiu       $a1, $a1, 0x10
    ctx->r5 = ADD32(ctx->r5, 0X10);
    // 0x801DEE30: jal         0x801DEB08
    // 0x801DEE34: addiu       $a2, $a2, 0x28
    ctx->r6 = ADD32(ctx->r6, 0X28);
    func_801DEB08(rdram, ctx);
        goto after_2;
    // 0x801DEE34: addiu       $a2, $a2, 0x28
    ctx->r6 = ADD32(ctx->r6, 0X28);
    after_2:
    // 0x801DEE38: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x801DEE3C: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x801DEE40: jr          $ra
    // 0x801DEE44: nop

    return;
    // 0x801DEE44: nop

;}
RECOMP_FUNC void func_801DEE48(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801DEE48: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x801DEE4C: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x801DEE50: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    // 0x801DEE54: sw          $a1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r5;
    // 0x801DEE58: jal         0x801DEC00
    // 0x801DEE5C: sw          $a2, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r6;
    func_801DEC00(rdram, ctx);
        goto after_0;
    // 0x801DEE5C: sw          $a2, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r6;
    after_0:
    // 0x801DEE60: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
    // 0x801DEE64: lw          $a1, 0x1C($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X1C);
    // 0x801DEE68: lw          $a2, 0x20($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X20);
    // 0x801DEE6C: addiu       $a0, $a0, 0xC
    ctx->r4 = ADD32(ctx->r4, 0XC);
    // 0x801DEE70: addiu       $a1, $a1, 0x8
    ctx->r5 = ADD32(ctx->r5, 0X8);
    // 0x801DEE74: jal         0x801DEC00
    // 0x801DEE78: addiu       $a2, $a2, 0x14
    ctx->r6 = ADD32(ctx->r6, 0X14);
    func_801DEC00(rdram, ctx);
        goto after_1;
    // 0x801DEE78: addiu       $a2, $a2, 0x14
    ctx->r6 = ADD32(ctx->r6, 0X14);
    after_1:
    // 0x801DEE7C: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
    // 0x801DEE80: lw          $a1, 0x1C($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X1C);
    // 0x801DEE84: lw          $a2, 0x20($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X20);
    // 0x801DEE88: addiu       $a0, $a0, 0x18
    ctx->r4 = ADD32(ctx->r4, 0X18);
    // 0x801DEE8C: addiu       $a1, $a1, 0x10
    ctx->r5 = ADD32(ctx->r5, 0X10);
    // 0x801DEE90: jal         0x801DEC00
    // 0x801DEE94: addiu       $a2, $a2, 0x28
    ctx->r6 = ADD32(ctx->r6, 0X28);
    func_801DEC00(rdram, ctx);
        goto after_2;
    // 0x801DEE94: addiu       $a2, $a2, 0x28
    ctx->r6 = ADD32(ctx->r6, 0X28);
    after_2:
    // 0x801DEE98: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
    // 0x801DEE9C: lw          $a1, 0x1C($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X1C);
    // 0x801DEEA0: lw          $a2, 0x20($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X20);
    // 0x801DEEA4: addiu       $a0, $a0, 0x24
    ctx->r4 = ADD32(ctx->r4, 0X24);
    // 0x801DEEA8: addiu       $a1, $a1, 0x18
    ctx->r5 = ADD32(ctx->r5, 0X18);
    // 0x801DEEAC: jal         0x801DEB08
    // 0x801DEEB0: addiu       $a2, $a2, 0x3C
    ctx->r6 = ADD32(ctx->r6, 0X3C);
    func_801DEB08(rdram, ctx);
        goto after_3;
    // 0x801DEEB0: addiu       $a2, $a2, 0x3C
    ctx->r6 = ADD32(ctx->r6, 0X3C);
    after_3:
    // 0x801DEEB4: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x801DEEB8: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x801DEEBC: jr          $ra
    // 0x801DEEC0: nop

    return;
    // 0x801DEEC0: nop

;}
RECOMP_FUNC void func_801DEEC4(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801DEEC4: addiu       $v0, $a0, 0x4
    ctx->r2 = ADD32(ctx->r4, 0X4);
    // 0x801DEEC8: or          $a1, $v0, $zero
    ctx->r5 = ctx->r2 | 0;
    // 0x801DEECC: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
L_801DEED0:
    // 0x801DEED0: lwc1        $f0, 0x18($a1)
    ctx->f0.u32l = MEM_W(ctx->r5, 0X18);
    // 0x801DEED4: lwc1        $f4, 0x24($a1)
    ctx->f4.u32l = MEM_W(ctx->r5, 0X24);
    // 0x801DEED8: lwc1        $f8, 0x30($v0)
    ctx->f8.u32l = MEM_W(ctx->r2, 0X30);
    // 0x801DEEDC: addiu       $v1, $v1, 0x1
    ctx->r3 = ADD32(ctx->r3, 0X1);
    // 0x801DEEE0: sub.s       $f6, $f4, $f0
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f6.fl = ctx->f4.fl - ctx->f0.fl;
    // 0x801DEEE4: slti        $at, $v1, 0x3
    ctx->r1 = SIGNED(ctx->r3) < 0X3 ? 1 : 0;
    // 0x801DEEE8: addiu       $a1, $a1, 0x4
    ctx->r5 = ADD32(ctx->r5, 0X4);
    // 0x801DEEEC: mul.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = MUL_S(ctx->f6.fl, ctx->f8.fl);
    // 0x801DEEF0: add.s       $f16, $f0, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f16.fl = ctx->f0.fl + ctx->f10.fl;
    // 0x801DEEF4: bne         $at, $zero, L_801DEED0
    if (ctx->r1 != 0) {
        // 0x801DEEF8: swc1        $f16, 0x14($a1)
        MEM_W(0X14, ctx->r5) = ctx->f16.u32l;
            goto L_801DEED0;
    }
    // 0x801DEEF8: swc1        $f16, 0x14($a1)
    MEM_W(0X14, ctx->r5) = ctx->f16.u32l;
    // 0x801DEEFC: lwc1        $f0, 0x34($v0)
    ctx->f0.u32l = MEM_W(ctx->r2, 0X34);
    // 0x801DEF00: lwc1        $f18, 0x38($v0)
    ctx->f18.u32l = MEM_W(ctx->r2, 0X38);
    // 0x801DEF04: lwc1        $f6, 0x3C($v0)
    ctx->f6.u32l = MEM_W(ctx->r2, 0X3C);
    // 0x801DEF08: or          $a1, $v0, $zero
    ctx->r5 = ctx->r2 | 0;
    // 0x801DEF0C: sub.s       $f4, $f18, $f0
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f4.fl = ctx->f18.fl - ctx->f0.fl;
    // 0x801DEF10: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
    // 0x801DEF14: mul.s       $f8, $f4, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = MUL_S(ctx->f4.fl, ctx->f6.fl);
    // 0x801DEF18: add.s       $f10, $f0, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = ctx->f0.fl + ctx->f8.fl;
    // 0x801DEF1C: swc1        $f10, 0x34($v0)
    MEM_W(0X34, ctx->r2) = ctx->f10.u32l;
    // 0x801DEF20: addiu       $v0, $zero, 0x2
    ctx->r2 = ADD32(0, 0X2);
    // 0x801DEF24: lwc1        $f18, 0x40($a1)
    ctx->f18.u32l = MEM_W(ctx->r5, 0X40);
    // 0x801DEF28: lwc1        $f12, 0x48($a1)
    ctx->f12.u32l = MEM_W(ctx->r5, 0X48);
    // 0x801DEF2C: lwc1        $f10, 0x50($a1)
    ctx->f10.u32l = MEM_W(ctx->r5, 0X50);
    // 0x801DEF30: addiu       $v1, $v1, 0x1
    ctx->r3 = ADD32(ctx->r3, 0X1);
    // 0x801DEF34: sub.s       $f12, $f12, $f18
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f12.fl = ctx->f12.fl - ctx->f18.fl;
    // 0x801DEF38: mul.s       $f16, $f12, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f16.fl = MUL_S(ctx->f12.fl, ctx->f10.fl);
    // 0x801DEF3C: beql        $v1, $v0, L_801DEF74
    if (ctx->r3 == ctx->r2) {
        // 0x801DEF40: add.s       $f14, $f18, $f16
        CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f14.fl = ctx->f18.fl + ctx->f16.fl;
            goto L_801DEF74;
    }
    goto skip_0;
    // 0x801DEF40: add.s       $f14, $f18, $f16
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f14.fl = ctx->f18.fl + ctx->f16.fl;
    skip_0:
    // 0x801DEF44: add.s       $f14, $f18, $f16
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f14.fl = ctx->f18.fl + ctx->f16.fl;
L_801DEF48:
    // 0x801DEF48: lwc1        $f18, 0x44($a1)
    ctx->f18.u32l = MEM_W(ctx->r5, 0X44);
    // 0x801DEF4C: lwc1        $f12, 0x4C($a1)
    ctx->f12.u32l = MEM_W(ctx->r5, 0X4C);
    // 0x801DEF50: lwc1        $f10, 0x54($a1)
    ctx->f10.u32l = MEM_W(ctx->r5, 0X54);
    // 0x801DEF54: addiu       $v1, $v1, 0x1
    ctx->r3 = ADD32(ctx->r3, 0X1);
    // 0x801DEF58: sub.s       $f12, $f12, $f18
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f12.fl = ctx->f12.fl - ctx->f18.fl;
    // 0x801DEF5C: swc1        $f14, 0x40($a1)
    MEM_W(0X40, ctx->r5) = ctx->f14.u32l;
    // 0x801DEF60: addiu       $a1, $a1, 0x4
    ctx->r5 = ADD32(ctx->r5, 0X4);
    // 0x801DEF64: mul.s       $f16, $f12, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f16.fl = MUL_S(ctx->f12.fl, ctx->f10.fl);
    // 0x801DEF68: bnel        $v1, $v0, L_801DEF48
    if (ctx->r3 != ctx->r2) {
        // 0x801DEF6C: add.s       $f14, $f18, $f16
        CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f14.fl = ctx->f18.fl + ctx->f16.fl;
            goto L_801DEF48;
    }
    goto skip_1;
    // 0x801DEF6C: add.s       $f14, $f18, $f16
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f14.fl = ctx->f18.fl + ctx->f16.fl;
    skip_1:
    // 0x801DEF70: add.s       $f14, $f18, $f16
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f14.fl = ctx->f18.fl + ctx->f16.fl;
L_801DEF74:
    // 0x801DEF74: addiu       $a1, $a1, 0x4
    ctx->r5 = ADD32(ctx->r5, 0X4);
    // 0x801DEF78: swc1        $f14, 0x3C($a1)
    MEM_W(0X3C, ctx->r5) = ctx->f14.u32l;
    // 0x801DEF7C: jr          $ra
    // 0x801DEF80: nop

    return;
    // 0x801DEF80: nop

;}
RECOMP_FUNC void func_801DEF84(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801DEF84: addiu       $t6, $zero, 0x1
    ctx->r14 = ADD32(0, 0X1);
    // 0x801DEF88: sw          $t6, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r14;
    // 0x801DEF8C: or          $t9, $a1, $zero
    ctx->r25 = ctx->r5 | 0;
    // 0x801DEF90: or          $t0, $a0, $zero
    ctx->r8 = ctx->r4 | 0;
    // 0x801DEF94: addiu       $t8, $a1, 0x54
    ctx->r24 = ADD32(ctx->r5, 0X54);
L_801DEF98:
    // 0x801DEF98: lw          $at, 0x0($t9)
    ctx->r1 = MEM_W(ctx->r25, 0X0);
    // 0x801DEF9C: addiu       $t9, $t9, 0xC
    ctx->r25 = ADD32(ctx->r25, 0XC);
    // 0x801DEFA0: addiu       $t0, $t0, 0xC
    ctx->r8 = ADD32(ctx->r8, 0XC);
    // 0x801DEFA4: sw          $at, -0x8($t0)
    MEM_W(-0X8, ctx->r8) = ctx->r1;
    // 0x801DEFA8: lw          $at, -0x8($t9)
    ctx->r1 = MEM_W(ctx->r25, -0X8);
    // 0x801DEFAC: sw          $at, -0x4($t0)
    MEM_W(-0X4, ctx->r8) = ctx->r1;
    // 0x801DEFB0: lw          $at, -0x4($t9)
    ctx->r1 = MEM_W(ctx->r25, -0X4);
    // 0x801DEFB4: bne         $t9, $t8, L_801DEF98
    if (ctx->r25 != ctx->r24) {
        // 0x801DEFB8: sw          $at, 0x0($t0)
        MEM_W(0X0, ctx->r8) = ctx->r1;
            goto L_801DEF98;
    }
    // 0x801DEFB8: sw          $at, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r1;
    // 0x801DEFBC: lw          $at, 0x0($t9)
    ctx->r1 = MEM_W(ctx->r25, 0X0);
    // 0x801DEFC0: sw          $at, 0x4($t0)
    MEM_W(0X4, ctx->r8) = ctx->r1;
    // 0x801DEFC4: lw          $at, 0x0($a2)
    ctx->r1 = MEM_W(ctx->r6, 0X0);
    // 0x801DEFC8: sw          $at, 0x5C($a0)
    MEM_W(0X5C, ctx->r4) = ctx->r1;
    // 0x801DEFCC: lw          $t2, 0x4($a2)
    ctx->r10 = MEM_W(ctx->r6, 0X4);
    // 0x801DEFD0: sw          $t2, 0x60($a0)
    MEM_W(0X60, ctx->r4) = ctx->r10;
    // 0x801DEFD4: lw          $at, 0x8($a2)
    ctx->r1 = MEM_W(ctx->r6, 0X8);
    // 0x801DEFD8: sw          $at, 0x64($a0)
    MEM_W(0X64, ctx->r4) = ctx->r1;
    // 0x801DEFDC: lw          $t2, 0xC($a2)
    ctx->r10 = MEM_W(ctx->r6, 0XC);
    // 0x801DEFE0: sw          $t2, 0x68($a0)
    MEM_W(0X68, ctx->r4) = ctx->r10;
    // 0x801DEFE4: lw          $at, 0x10($a2)
    ctx->r1 = MEM_W(ctx->r6, 0X10);
    // 0x801DEFE8: sw          $at, 0x6C($a0)
    MEM_W(0X6C, ctx->r4) = ctx->r1;
    // 0x801DEFEC: lw          $t2, 0x14($a2)
    ctx->r10 = MEM_W(ctx->r6, 0X14);
    // 0x801DEFF0: sw          $t2, 0x70($a0)
    MEM_W(0X70, ctx->r4) = ctx->r10;
    // 0x801DEFF4: lw          $at, 0x18($a2)
    ctx->r1 = MEM_W(ctx->r6, 0X18);
    // 0x801DEFF8: sw          $at, 0x74($a0)
    MEM_W(0X74, ctx->r4) = ctx->r1;
    // 0x801DEFFC: lw          $t2, 0x1C($a2)
    ctx->r10 = MEM_W(ctx->r6, 0X1C);
    // 0x801DF000: jr          $ra
    // 0x801DF004: sw          $t2, 0x78($a0)
    MEM_W(0X78, ctx->r4) = ctx->r10;
    return;
    // 0x801DF004: sw          $t2, 0x78($a0)
    MEM_W(0X78, ctx->r4) = ctx->r10;
;}
RECOMP_FUNC void func_801DF008(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801DF008: addiu       $t6, $zero, 0x1
    ctx->r14 = ADD32(0, 0X1);
    // 0x801DF00C: sw          $t6, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r14;
    // 0x801DF010: or          $t9, $a1, $zero
    ctx->r25 = ctx->r5 | 0;
    // 0x801DF014: or          $t0, $a0, $zero
    ctx->r8 = ctx->r4 | 0;
    // 0x801DF018: addiu       $t8, $a1, 0x54
    ctx->r24 = ADD32(ctx->r5, 0X54);
L_801DF01C:
    // 0x801DF01C: lw          $at, 0x0($t9)
    ctx->r1 = MEM_W(ctx->r25, 0X0);
    // 0x801DF020: addiu       $t9, $t9, 0xC
    ctx->r25 = ADD32(ctx->r25, 0XC);
    // 0x801DF024: addiu       $t0, $t0, 0xC
    ctx->r8 = ADD32(ctx->r8, 0XC);
    // 0x801DF028: sw          $at, -0x8($t0)
    MEM_W(-0X8, ctx->r8) = ctx->r1;
    // 0x801DF02C: lw          $at, -0x8($t9)
    ctx->r1 = MEM_W(ctx->r25, -0X8);
    // 0x801DF030: sw          $at, -0x4($t0)
    MEM_W(-0X4, ctx->r8) = ctx->r1;
    // 0x801DF034: lw          $at, -0x4($t9)
    ctx->r1 = MEM_W(ctx->r25, -0X4);
    // 0x801DF038: bne         $t9, $t8, L_801DF01C
    if (ctx->r25 != ctx->r24) {
        // 0x801DF03C: sw          $at, 0x0($t0)
        MEM_W(0X0, ctx->r8) = ctx->r1;
            goto L_801DF01C;
    }
    // 0x801DF03C: sw          $at, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r1;
    // 0x801DF040: lw          $at, 0x0($t9)
    ctx->r1 = MEM_W(ctx->r25, 0X0);
    // 0x801DF044: sw          $at, 0x4($t0)
    MEM_W(0X4, ctx->r8) = ctx->r1;
    // 0x801DF048: lw          $at, 0x58($a1)
    ctx->r1 = MEM_W(ctx->r5, 0X58);
    // 0x801DF04C: sw          $at, 0x5C($a0)
    MEM_W(0X5C, ctx->r4) = ctx->r1;
    // 0x801DF050: lw          $t2, 0x5C($a1)
    ctx->r10 = MEM_W(ctx->r5, 0X5C);
    // 0x801DF054: sw          $t2, 0x60($a0)
    MEM_W(0X60, ctx->r4) = ctx->r10;
    // 0x801DF058: lw          $at, 0x60($a1)
    ctx->r1 = MEM_W(ctx->r5, 0X60);
    // 0x801DF05C: sw          $at, 0x64($a0)
    MEM_W(0X64, ctx->r4) = ctx->r1;
    // 0x801DF060: lw          $t2, 0x64($a1)
    ctx->r10 = MEM_W(ctx->r5, 0X64);
    // 0x801DF064: sw          $t2, 0x68($a0)
    MEM_W(0X68, ctx->r4) = ctx->r10;
    // 0x801DF068: lw          $at, 0x68($a1)
    ctx->r1 = MEM_W(ctx->r5, 0X68);
    // 0x801DF06C: sw          $at, 0x6C($a0)
    MEM_W(0X6C, ctx->r4) = ctx->r1;
    // 0x801DF070: lw          $t2, 0x6C($a1)
    ctx->r10 = MEM_W(ctx->r5, 0X6C);
    // 0x801DF074: sw          $t2, 0x70($a0)
    MEM_W(0X70, ctx->r4) = ctx->r10;
    // 0x801DF078: lw          $at, 0x70($a1)
    ctx->r1 = MEM_W(ctx->r5, 0X70);
    // 0x801DF07C: sw          $at, 0x74($a0)
    MEM_W(0X74, ctx->r4) = ctx->r1;
    // 0x801DF080: lw          $t2, 0x74($a1)
    ctx->r10 = MEM_W(ctx->r5, 0X74);
    // 0x801DF084: jr          $ra
    // 0x801DF088: sw          $t2, 0x78($a0)
    MEM_W(0X78, ctx->r4) = ctx->r10;
    return;
    // 0x801DF088: sw          $t2, 0x78($a0)
    MEM_W(0X78, ctx->r4) = ctx->r10;
;}
RECOMP_FUNC void func_801DF08C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801DF08C: beq         $a1, $zero, L_801DF0B8
    if (ctx->r5 == 0) {
        // 0x801DF090: or          $v0, $zero, $zero
        ctx->r2 = 0 | 0;
            goto L_801DF0B8;
    }
    // 0x801DF090: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    // 0x801DF094: or          $v1, $a1, $zero
    ctx->r3 = ctx->r5 | 0;
    // 0x801DF098: addiu       $t0, $a0, 0x5C
    ctx->r8 = ADD32(ctx->r4, 0X5C);
    // 0x801DF09C: addiu       $t1, $zero, 0x3
    ctx->r9 = ADD32(0, 0X3);
L_801DF0A0:
    // 0x801DF0A0: lwc1        $f4, 0x0($v1)
    ctx->f4.u32l = MEM_W(ctx->r3, 0X0);
    // 0x801DF0A4: addiu       $v0, $v0, 0x1
    ctx->r2 = ADD32(ctx->r2, 0X1);
    // 0x801DF0A8: addiu       $v1, $v1, 0x4
    ctx->r3 = ADD32(ctx->r3, 0X4);
    // 0x801DF0AC: addiu       $t0, $t0, 0x4
    ctx->r8 = ADD32(ctx->r8, 0X4);
    // 0x801DF0B0: bne         $v0, $t1, L_801DF0A0
    if (ctx->r2 != ctx->r9) {
        // 0x801DF0B4: swc1        $f4, -0x4($t0)
        MEM_W(-0X4, ctx->r8) = ctx->f4.u32l;
            goto L_801DF0A0;
    }
    // 0x801DF0B4: swc1        $f4, -0x4($t0)
    MEM_W(-0X4, ctx->r8) = ctx->f4.u32l;
L_801DF0B8:
    // 0x801DF0B8: beq         $a2, $zero, L_801DF0E4
    if (ctx->r6 == 0) {
        // 0x801DF0BC: addiu       $t1, $zero, 0x3
        ctx->r9 = ADD32(0, 0X3);
            goto L_801DF0E4;
    }
    // 0x801DF0BC: addiu       $t1, $zero, 0x3
    ctx->r9 = ADD32(0, 0X3);
    // 0x801DF0C0: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    // 0x801DF0C4: or          $v1, $a2, $zero
    ctx->r3 = ctx->r6 | 0;
    // 0x801DF0C8: addiu       $t0, $a0, 0x5C
    ctx->r8 = ADD32(ctx->r4, 0X5C);
L_801DF0CC:
    // 0x801DF0CC: lwc1        $f6, 0x0($v1)
    ctx->f6.u32l = MEM_W(ctx->r3, 0X0);
    // 0x801DF0D0: addiu       $v0, $v0, 0x1
    ctx->r2 = ADD32(ctx->r2, 0X1);
    // 0x801DF0D4: addiu       $v1, $v1, 0x4
    ctx->r3 = ADD32(ctx->r3, 0X4);
    // 0x801DF0D8: addiu       $t0, $t0, 0x4
    ctx->r8 = ADD32(ctx->r8, 0X4);
    // 0x801DF0DC: bne         $v0, $t1, L_801DF0CC
    if (ctx->r2 != ctx->r9) {
        // 0x801DF0E0: swc1        $f6, 0xC($t0)
        MEM_W(0XC, ctx->r8) = ctx->f6.u32l;
            goto L_801DF0CC;
    }
    // 0x801DF0E0: swc1        $f6, 0xC($t0)
    MEM_W(0XC, ctx->r8) = ctx->f6.u32l;
L_801DF0E4:
    // 0x801DF0E4: beq         $a3, $zero, L_801DF10C
    if (ctx->r7 == 0) {
        // 0x801DF0E8: or          $v0, $zero, $zero
        ctx->r2 = 0 | 0;
            goto L_801DF10C;
    }
    // 0x801DF0E8: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    // 0x801DF0EC: or          $v1, $a3, $zero
    ctx->r3 = ctx->r7 | 0;
    // 0x801DF0F0: addiu       $a1, $a0, 0x4
    ctx->r5 = ADD32(ctx->r4, 0X4);
L_801DF0F4:
    // 0x801DF0F4: lwc1        $f8, 0x0($v1)
    ctx->f8.u32l = MEM_W(ctx->r3, 0X0);
    // 0x801DF0F8: addiu       $v0, $v0, 0x1
    ctx->r2 = ADD32(ctx->r2, 0X1);
    // 0x801DF0FC: addiu       $v1, $v1, 0x4
    ctx->r3 = ADD32(ctx->r3, 0X4);
    // 0x801DF100: addiu       $a1, $a1, 0x4
    ctx->r5 = ADD32(ctx->r5, 0X4);
    // 0x801DF104: bne         $v0, $t1, L_801DF0F4
    if (ctx->r2 != ctx->r9) {
        // 0x801DF108: swc1        $f8, 0x20($a1)
        MEM_W(0X20, ctx->r5) = ctx->f8.u32l;
            goto L_801DF0F4;
    }
    // 0x801DF108: swc1        $f8, 0x20($a1)
    MEM_W(0X20, ctx->r5) = ctx->f8.u32l;
L_801DF10C:
    // 0x801DF10C: lw          $v0, 0x10($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X10);
    // 0x801DF110: beq         $v0, $zero, L_801DF120
    if (ctx->r2 == 0) {
        // 0x801DF114: nop
    
            goto L_801DF120;
    }
    // 0x801DF114: nop

    // 0x801DF118: lwc1        $f10, 0x0($v0)
    ctx->f10.u32l = MEM_W(ctx->r2, 0X0);
    // 0x801DF11C: swc1        $f10, 0x3C($a0)
    MEM_W(0X3C, ctx->r4) = ctx->f10.u32l;
L_801DF120:
    // 0x801DF120: jr          $ra
    // 0x801DF124: nop

    return;
    // 0x801DF124: nop

;}
RECOMP_FUNC void func_801DF128(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801DF128: addiu       $a2, $a0, 0x5C
    ctx->r6 = ADD32(ctx->r4, 0X5C);
    // 0x801DF12C: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x801DF130: or          $a3, $a0, $zero
    ctx->r7 = ctx->r4 | 0;
    // 0x801DF134: addiu       $v0, $a0, 0x4
    ctx->r2 = ADD32(ctx->r4, 0X4);
    // 0x801DF138: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x801DF13C: addiu       $a0, $zero, 0x3
    ctx->r4 = ADD32(0, 0X3);
    // 0x801DF140: or          $v1, $a2, $zero
    ctx->r3 = ctx->r6 | 0;
    // 0x801DF144: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x801DF148: lwc1        $f18, 0x0($v0)
    ctx->f18.u32l = MEM_W(ctx->r2, 0X0);
    // 0x801DF14C: lwc1        $f10, 0x0($v1)
    ctx->f10.u32l = MEM_W(ctx->r3, 0X0);
    // 0x801DF150: lwc1        $f12, 0xC($a2)
    ctx->f12.u32l = MEM_W(ctx->r6, 0XC);
    // 0x801DF154: addiu       $a1, $a1, 0x1
    ctx->r5 = ADD32(ctx->r5, 0X1);
    // 0x801DF158: sub.s       $f10, $f10, $f18
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f10.fl = ctx->f10.fl - ctx->f18.fl;
    // 0x801DF15C: mul.s       $f16, $f10, $f12
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f16.fl = MUL_S(ctx->f10.fl, ctx->f12.fl);
    // 0x801DF160: beql        $a1, $a0, L_801DF1B8
    if (ctx->r5 == ctx->r4) {
        // 0x801DF164: add.s       $f14, $f18, $f16
        CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f14.fl = ctx->f18.fl + ctx->f16.fl;
            goto L_801DF1B8;
    }
    goto skip_0;
    // 0x801DF164: add.s       $f14, $f18, $f16
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f14.fl = ctx->f18.fl + ctx->f16.fl;
    skip_0:
    // 0x801DF168: add.s       $f14, $f18, $f16
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f14.fl = ctx->f18.fl + ctx->f16.fl;
L_801DF16C:
    // 0x801DF16C: lwc1        $f12, 0xC($v0)
    ctx->f12.u32l = MEM_W(ctx->r2, 0XC);
    // 0x801DF170: lwc1        $f18, 0x4($v0)
    ctx->f18.u32l = MEM_W(ctx->r2, 0X4);
    // 0x801DF174: addiu       $a1, $a1, 0x1
    ctx->r5 = ADD32(ctx->r5, 0X1);
    // 0x801DF178: swc1        $f14, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->f14.u32l;
    // 0x801DF17C: lwc1        $f14, 0x10($v1)
    ctx->f14.u32l = MEM_W(ctx->r3, 0X10);
    // 0x801DF180: lwc1        $f10, 0x1C($a2)
    ctx->f10.u32l = MEM_W(ctx->r6, 0X1C);
    // 0x801DF184: addiu       $v0, $v0, 0x4
    ctx->r2 = ADD32(ctx->r2, 0X4);
    // 0x801DF188: sub.s       $f14, $f14, $f12
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f14.fl = ctx->f14.fl - ctx->f12.fl;
    // 0x801DF18C: addiu       $v1, $v1, 0x4
    ctx->r3 = ADD32(ctx->r3, 0X4);
    // 0x801DF190: mul.s       $f10, $f14, $f10
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f10.fl = MUL_S(ctx->f14.fl, ctx->f10.fl);
    // 0x801DF194: add.s       $f10, $f12, $f10
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f10.fl = ctx->f12.fl + ctx->f10.fl;
    // 0x801DF198: swc1        $f10, 0x8($v0)
    MEM_W(0X8, ctx->r2) = ctx->f10.u32l;
    // 0x801DF19C: lwc1        $f10, 0x0($v1)
    ctx->f10.u32l = MEM_W(ctx->r3, 0X0);
    // 0x801DF1A0: lwc1        $f12, 0xC($a2)
    ctx->f12.u32l = MEM_W(ctx->r6, 0XC);
    // 0x801DF1A4: sub.s       $f10, $f10, $f18
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f10.fl = ctx->f10.fl - ctx->f18.fl;
    // 0x801DF1A8: mul.s       $f16, $f10, $f12
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f16.fl = MUL_S(ctx->f10.fl, ctx->f12.fl);
    // 0x801DF1AC: bnel        $a1, $a0, L_801DF16C
    if (ctx->r5 != ctx->r4) {
        // 0x801DF1B0: add.s       $f14, $f18, $f16
        CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f14.fl = ctx->f18.fl + ctx->f16.fl;
            goto L_801DF16C;
    }
    goto skip_1;
    // 0x801DF1B0: add.s       $f14, $f18, $f16
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f14.fl = ctx->f18.fl + ctx->f16.fl;
    skip_1:
    // 0x801DF1B4: add.s       $f14, $f18, $f16
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f14.fl = ctx->f18.fl + ctx->f16.fl;
L_801DF1B8:
    // 0x801DF1B8: lwc1        $f12, 0xC($v0)
    ctx->f12.u32l = MEM_W(ctx->r2, 0XC);
    // 0x801DF1BC: addiu       $v0, $v0, 0x4
    ctx->r2 = ADD32(ctx->r2, 0X4);
    // 0x801DF1C0: addiu       $v1, $v1, 0x4
    ctx->r3 = ADD32(ctx->r3, 0X4);
    // 0x801DF1C4: swc1        $f14, -0x4($v0)
    MEM_W(-0X4, ctx->r2) = ctx->f14.u32l;
    // 0x801DF1C8: lwc1        $f14, 0xC($v1)
    ctx->f14.u32l = MEM_W(ctx->r3, 0XC);
    // 0x801DF1CC: lwc1        $f10, 0x1C($a2)
    ctx->f10.u32l = MEM_W(ctx->r6, 0X1C);
    // 0x801DF1D0: sub.s       $f14, $f14, $f12
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f14.fl = ctx->f14.fl - ctx->f12.fl;
    // 0x801DF1D4: mul.s       $f10, $f14, $f10
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f10.fl = MUL_S(ctx->f14.fl, ctx->f10.fl);
    // 0x801DF1D8: add.s       $f10, $f12, $f10
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f10.fl = ctx->f12.fl + ctx->f10.fl;
    // 0x801DF1DC: swc1        $f10, 0x8($v0)
    MEM_W(0X8, ctx->r2) = ctx->f10.u32l;
    // 0x801DF1E0: jal         0x801DEEC4
    // 0x801DF1E4: or          $a0, $a3, $zero
    ctx->r4 = ctx->r7 | 0;
    func_801DEEC4(rdram, ctx);
        goto after_0;
    // 0x801DF1E4: or          $a0, $a3, $zero
    ctx->r4 = ctx->r7 | 0;
    after_0:
    // 0x801DF1E8: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x801DF1EC: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x801DF1F0: jr          $ra
    // 0x801DF1F4: nop

    return;
    // 0x801DF1F4: nop

;}
RECOMP_FUNC void func_801DF1F8(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801DF1F8: sw          $a1, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r5;
    // 0x801DF1FC: or          $t8, $a2, $zero
    ctx->r24 = ctx->r6 | 0;
    // 0x801DF200: or          $t9, $a0, $zero
    ctx->r25 = ctx->r4 | 0;
    // 0x801DF204: addiu       $t7, $a2, 0x54
    ctx->r15 = ADD32(ctx->r6, 0X54);
L_801DF208:
    // 0x801DF208: lw          $at, 0x0($t8)
    ctx->r1 = MEM_W(ctx->r24, 0X0);
    // 0x801DF20C: addiu       $t8, $t8, 0xC
    ctx->r24 = ADD32(ctx->r24, 0XC);
    // 0x801DF210: addiu       $t9, $t9, 0xC
    ctx->r25 = ADD32(ctx->r25, 0XC);
    // 0x801DF214: sw          $at, -0x8($t9)
    MEM_W(-0X8, ctx->r25) = ctx->r1;
    // 0x801DF218: lw          $at, -0x8($t8)
    ctx->r1 = MEM_W(ctx->r24, -0X8);
    // 0x801DF21C: sw          $at, -0x4($t9)
    MEM_W(-0X4, ctx->r25) = ctx->r1;
    // 0x801DF220: lw          $at, -0x4($t8)
    ctx->r1 = MEM_W(ctx->r24, -0X4);
    // 0x801DF224: bne         $t8, $t7, L_801DF208
    if (ctx->r24 != ctx->r15) {
        // 0x801DF228: sw          $at, 0x0($t9)
        MEM_W(0X0, ctx->r25) = ctx->r1;
            goto L_801DF208;
    }
    // 0x801DF228: sw          $at, 0x0($t9)
    MEM_W(0X0, ctx->r25) = ctx->r1;
    // 0x801DF22C: lw          $at, 0x0($t8)
    ctx->r1 = MEM_W(ctx->r24, 0X0);
    // 0x801DF230: or          $t2, $a3, $zero
    ctx->r10 = ctx->r7 | 0;
    // 0x801DF234: or          $t3, $a0, $zero
    ctx->r11 = ctx->r4 | 0;
    // 0x801DF238: addiu       $t1, $a3, 0x30
    ctx->r9 = ADD32(ctx->r7, 0X30);
    // 0x801DF23C: sw          $at, 0x4($t9)
    MEM_W(0X4, ctx->r25) = ctx->r1;
L_801DF240:
    // 0x801DF240: lw          $at, 0x0($t2)
    ctx->r1 = MEM_W(ctx->r10, 0X0);
    // 0x801DF244: addiu       $t2, $t2, 0xC
    ctx->r10 = ADD32(ctx->r10, 0XC);
    // 0x801DF248: addiu       $t3, $t3, 0xC
    ctx->r11 = ADD32(ctx->r11, 0XC);
    // 0x801DF24C: sw          $at, 0x50($t3)
    MEM_W(0X50, ctx->r11) = ctx->r1;
    // 0x801DF250: lw          $at, -0x8($t2)
    ctx->r1 = MEM_W(ctx->r10, -0X8);
    // 0x801DF254: sw          $at, 0x54($t3)
    MEM_W(0X54, ctx->r11) = ctx->r1;
    // 0x801DF258: lw          $at, -0x4($t2)
    ctx->r1 = MEM_W(ctx->r10, -0X4);
    // 0x801DF25C: bne         $t2, $t1, L_801DF240
    if (ctx->r10 != ctx->r9) {
        // 0x801DF260: sw          $at, 0x58($t3)
        MEM_W(0X58, ctx->r11) = ctx->r1;
            goto L_801DF240;
    }
    // 0x801DF260: sw          $at, 0x58($t3)
    MEM_W(0X58, ctx->r11) = ctx->r1;
    // 0x801DF264: lw          $at, 0x0($t2)
    ctx->r1 = MEM_W(ctx->r10, 0X0);
    // 0x801DF268: sw          $at, 0x5C($t3)
    MEM_W(0X5C, ctx->r11) = ctx->r1;
    // 0x801DF26C: lw          $t1, 0x4($t2)
    ctx->r9 = MEM_W(ctx->r10, 0X4);
    // 0x801DF270: jr          $ra
    // 0x801DF274: sw          $t1, 0x60($t3)
    MEM_W(0X60, ctx->r11) = ctx->r9;
    return;
    // 0x801DF274: sw          $t1, 0x60($t3)
    MEM_W(0X60, ctx->r11) = ctx->r9;
;}
RECOMP_FUNC void func_801DF278(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801DF278: sw          $a1, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r5;
    // 0x801DF27C: or          $t8, $a2, $zero
    ctx->r24 = ctx->r6 | 0;
    // 0x801DF280: or          $t9, $a0, $zero
    ctx->r25 = ctx->r4 | 0;
    // 0x801DF284: addiu       $t7, $a2, 0x54
    ctx->r15 = ADD32(ctx->r6, 0X54);
L_801DF288:
    // 0x801DF288: lw          $at, 0x0($t8)
    ctx->r1 = MEM_W(ctx->r24, 0X0);
    // 0x801DF28C: addiu       $t8, $t8, 0xC
    ctx->r24 = ADD32(ctx->r24, 0XC);
    // 0x801DF290: addiu       $t9, $t9, 0xC
    ctx->r25 = ADD32(ctx->r25, 0XC);
    // 0x801DF294: sw          $at, -0x8($t9)
    MEM_W(-0X8, ctx->r25) = ctx->r1;
    // 0x801DF298: lw          $at, -0x8($t8)
    ctx->r1 = MEM_W(ctx->r24, -0X8);
    // 0x801DF29C: sw          $at, -0x4($t9)
    MEM_W(-0X4, ctx->r25) = ctx->r1;
    // 0x801DF2A0: lw          $at, -0x4($t8)
    ctx->r1 = MEM_W(ctx->r24, -0X4);
    // 0x801DF2A4: bne         $t8, $t7, L_801DF288
    if (ctx->r24 != ctx->r15) {
        // 0x801DF2A8: sw          $at, 0x0($t9)
        MEM_W(0X0, ctx->r25) = ctx->r1;
            goto L_801DF288;
    }
    // 0x801DF2A8: sw          $at, 0x0($t9)
    MEM_W(0X0, ctx->r25) = ctx->r1;
    // 0x801DF2AC: lw          $at, 0x0($t8)
    ctx->r1 = MEM_W(ctx->r24, 0X0);
    // 0x801DF2B0: or          $t2, $a2, $zero
    ctx->r10 = ctx->r6 | 0;
    // 0x801DF2B4: or          $t3, $a0, $zero
    ctx->r11 = ctx->r4 | 0;
    // 0x801DF2B8: addiu       $t1, $a2, 0x30
    ctx->r9 = ADD32(ctx->r6, 0X30);
    // 0x801DF2BC: sw          $at, 0x4($t9)
    MEM_W(0X4, ctx->r25) = ctx->r1;
L_801DF2C0:
    // 0x801DF2C0: lw          $at, 0x58($t2)
    ctx->r1 = MEM_W(ctx->r10, 0X58);
    // 0x801DF2C4: addiu       $t2, $t2, 0xC
    ctx->r10 = ADD32(ctx->r10, 0XC);
    // 0x801DF2C8: addiu       $t3, $t3, 0xC
    ctx->r11 = ADD32(ctx->r11, 0XC);
    // 0x801DF2CC: sw          $at, 0x50($t3)
    MEM_W(0X50, ctx->r11) = ctx->r1;
    // 0x801DF2D0: lw          $at, 0x50($t2)
    ctx->r1 = MEM_W(ctx->r10, 0X50);
    // 0x801DF2D4: sw          $at, 0x54($t3)
    MEM_W(0X54, ctx->r11) = ctx->r1;
    // 0x801DF2D8: lw          $at, 0x54($t2)
    ctx->r1 = MEM_W(ctx->r10, 0X54);
    // 0x801DF2DC: bne         $t2, $t1, L_801DF2C0
    if (ctx->r10 != ctx->r9) {
        // 0x801DF2E0: sw          $at, 0x58($t3)
        MEM_W(0X58, ctx->r11) = ctx->r1;
            goto L_801DF2C0;
    }
    // 0x801DF2E0: sw          $at, 0x58($t3)
    MEM_W(0X58, ctx->r11) = ctx->r1;
    // 0x801DF2E4: lw          $at, 0x58($t2)
    ctx->r1 = MEM_W(ctx->r10, 0X58);
    // 0x801DF2E8: sw          $at, 0x5C($t3)
    MEM_W(0X5C, ctx->r11) = ctx->r1;
    // 0x801DF2EC: lw          $t1, 0x5C($t2)
    ctx->r9 = MEM_W(ctx->r10, 0X5C);
    // 0x801DF2F0: jr          $ra
    // 0x801DF2F4: sw          $t1, 0x60($t3)
    MEM_W(0X60, ctx->r11) = ctx->r9;
    return;
    // 0x801DF2F4: sw          $t1, 0x60($t3)
    MEM_W(0X60, ctx->r11) = ctx->r9;
;}
RECOMP_FUNC void func_801DF2F8(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801DF2F8: beq         $a1, $zero, L_801DF324
    if (ctx->r5 == 0) {
        // 0x801DF2FC: or          $v0, $zero, $zero
        ctx->r2 = 0 | 0;
            goto L_801DF324;
    }
    // 0x801DF2FC: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    // 0x801DF300: or          $v1, $a1, $zero
    ctx->r3 = ctx->r5 | 0;
    // 0x801DF304: addiu       $t0, $a0, 0x5C
    ctx->r8 = ADD32(ctx->r4, 0X5C);
    // 0x801DF308: addiu       $t1, $zero, 0x3
    ctx->r9 = ADD32(0, 0X3);
L_801DF30C:
    // 0x801DF30C: lwc1        $f4, 0x0($v1)
    ctx->f4.u32l = MEM_W(ctx->r3, 0X0);
    // 0x801DF310: addiu       $v0, $v0, 0x1
    ctx->r2 = ADD32(ctx->r2, 0X1);
    // 0x801DF314: addiu       $v1, $v1, 0x4
    ctx->r3 = ADD32(ctx->r3, 0X4);
    // 0x801DF318: addiu       $t0, $t0, 0x4
    ctx->r8 = ADD32(ctx->r8, 0X4);
    // 0x801DF31C: bne         $v0, $t1, L_801DF30C
    if (ctx->r2 != ctx->r9) {
        // 0x801DF320: swc1        $f4, -0x4($t0)
        MEM_W(-0X4, ctx->r8) = ctx->f4.u32l;
            goto L_801DF30C;
    }
    // 0x801DF320: swc1        $f4, -0x4($t0)
    MEM_W(-0X4, ctx->r8) = ctx->f4.u32l;
L_801DF324:
    // 0x801DF324: beq         $a2, $zero, L_801DF348
    if (ctx->r6 == 0) {
        // 0x801DF328: addiu       $t1, $zero, 0x3
        ctx->r9 = ADD32(0, 0X3);
            goto L_801DF348;
    }
    // 0x801DF328: addiu       $t1, $zero, 0x3
    ctx->r9 = ADD32(0, 0X3);
    // 0x801DF32C: lwc1        $f6, 0x0($a2)
    ctx->f6.u32l = MEM_W(ctx->r6, 0X0);
    // 0x801DF330: addiu       $v0, $a0, 0x5C
    ctx->r2 = ADD32(ctx->r4, 0X5C);
    // 0x801DF334: swc1        $f6, 0x18($v0)
    MEM_W(0X18, ctx->r2) = ctx->f6.u32l;
    // 0x801DF338: lwc1        $f8, 0x4($a2)
    ctx->f8.u32l = MEM_W(ctx->r6, 0X4);
    // 0x801DF33C: swc1        $f8, 0x24($v0)
    MEM_W(0X24, ctx->r2) = ctx->f8.u32l;
    // 0x801DF340: lwc1        $f10, 0x8($a2)
    ctx->f10.u32l = MEM_W(ctx->r6, 0X8);
    // 0x801DF344: swc1        $f10, 0x30($v0)
    MEM_W(0X30, ctx->r2) = ctx->f10.u32l;
L_801DF348:
    // 0x801DF348: beq         $a3, $zero, L_801DF370
    if (ctx->r7 == 0) {
        // 0x801DF34C: or          $v0, $zero, $zero
        ctx->r2 = 0 | 0;
            goto L_801DF370;
    }
    // 0x801DF34C: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    // 0x801DF350: or          $v1, $a3, $zero
    ctx->r3 = ctx->r7 | 0;
    // 0x801DF354: addiu       $a1, $a0, 0x4
    ctx->r5 = ADD32(ctx->r4, 0X4);
L_801DF358:
    // 0x801DF358: lwc1        $f16, 0x0($v1)
    ctx->f16.u32l = MEM_W(ctx->r3, 0X0);
    // 0x801DF35C: addiu       $v0, $v0, 0x1
    ctx->r2 = ADD32(ctx->r2, 0X1);
    // 0x801DF360: addiu       $v1, $v1, 0x4
    ctx->r3 = ADD32(ctx->r3, 0X4);
    // 0x801DF364: addiu       $a1, $a1, 0x4
    ctx->r5 = ADD32(ctx->r5, 0X4);
    // 0x801DF368: bne         $v0, $t1, L_801DF358
    if (ctx->r2 != ctx->r9) {
        // 0x801DF36C: swc1        $f16, 0x20($a1)
        MEM_W(0X20, ctx->r5) = ctx->f16.u32l;
            goto L_801DF358;
    }
    // 0x801DF36C: swc1        $f16, 0x20($a1)
    MEM_W(0X20, ctx->r5) = ctx->f16.u32l;
L_801DF370:
    // 0x801DF370: lw          $v0, 0x10($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X10);
    // 0x801DF374: beq         $v0, $zero, L_801DF384
    if (ctx->r2 == 0) {
        // 0x801DF378: nop
    
            goto L_801DF384;
    }
    // 0x801DF378: nop

    // 0x801DF37C: lwc1        $f18, 0x0($v0)
    ctx->f18.u32l = MEM_W(ctx->r2, 0X0);
    // 0x801DF380: swc1        $f18, 0x3C($a0)
    MEM_W(0X3C, ctx->r4) = ctx->f18.u32l;
L_801DF384:
    // 0x801DF384: jr          $ra
    // 0x801DF388: nop

    return;
    // 0x801DF388: nop

;}
RECOMP_FUNC void func_801DF38C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801DF38C: addiu       $sp, $sp, -0x48
    ctx->r29 = ADD32(ctx->r29, -0X48);
    // 0x801DF390: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x801DF394: lwc1        $f0, 0x70($a0)
    ctx->f0.u32l = MEM_W(ctx->r4, 0X70);
    // 0x801DF398: lwc1        $f4, 0x74($a0)
    ctx->f4.u32l = MEM_W(ctx->r4, 0X74);
    // 0x801DF39C: lwc1        $f8, 0x78($a0)
    ctx->f8.u32l = MEM_W(ctx->r4, 0X78);
    // 0x801DF3A0: lwc1        $f2, 0x7C($a0)
    ctx->f2.u32l = MEM_W(ctx->r4, 0X7C);
    // 0x801DF3A4: sub.s       $f6, $f4, $f0
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f6.fl = ctx->f4.fl - ctx->f0.fl;
    // 0x801DF3A8: lwc1        $f12, 0x88($a0)
    ctx->f12.u32l = MEM_W(ctx->r4, 0X88);
    // 0x801DF3AC: lui         $at, 0x4580
    ctx->r1 = S32(0X4580 << 16);
    // 0x801DF3B0: lui         $a1, 0x8015
    ctx->r5 = S32(0X8015 << 16);
    // 0x801DF3B4: mul.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = MUL_S(ctx->f6.fl, ctx->f8.fl);
    // 0x801DF3B8: lwc1        $f6, 0x80($a0)
    ctx->f6.u32l = MEM_W(ctx->r4, 0X80);
    // 0x801DF3BC: addiu       $a1, $a1, 0x4350
    ctx->r5 = ADD32(ctx->r5, 0X4350);
    // 0x801DF3C0: or          $a2, $a0, $zero
    ctx->r6 = ctx->r4 | 0;
    // 0x801DF3C4: sub.s       $f8, $f6, $f2
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f8.fl = ctx->f6.fl - ctx->f2.fl;
    // 0x801DF3C8: add.s       $f4, $f0, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f4.fl = ctx->f0.fl + ctx->f10.fl;
    // 0x801DF3CC: lwc1        $f10, 0x84($a0)
    ctx->f10.u32l = MEM_W(ctx->r4, 0X84);
    // 0x801DF3D0: swc1        $f4, 0x70($a0)
    MEM_W(0X70, ctx->r4) = ctx->f4.u32l;
    // 0x801DF3D4: mul.s       $f4, $f8, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f4.fl = MUL_S(ctx->f8.fl, ctx->f10.fl);
    // 0x801DF3D8: lwc1        $f8, 0x8C($a0)
    ctx->f8.u32l = MEM_W(ctx->r4, 0X8C);
    // 0x801DF3DC: sub.s       $f10, $f8, $f12
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f10.fl = ctx->f8.fl - ctx->f12.fl;
    // 0x801DF3E0: add.s       $f6, $f2, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = ctx->f2.fl + ctx->f4.fl;
    // 0x801DF3E4: lwc1        $f4, 0x90($a0)
    ctx->f4.u32l = MEM_W(ctx->r4, 0X90);
    // 0x801DF3E8: swc1        $f6, 0x7C($a0)
    MEM_W(0X7C, ctx->r4) = ctx->f6.u32l;
    // 0x801DF3EC: mul.s       $f6, $f10, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = MUL_S(ctx->f10.fl, ctx->f4.fl);
    // 0x801DF3F0: lwc1        $f4, 0x7C($a0)
    ctx->f4.u32l = MEM_W(ctx->r4, 0X7C);
    // 0x801DF3F4: lwc1        $f10, 0x68($a0)
    ctx->f10.u32l = MEM_W(ctx->r4, 0X68);
    // 0x801DF3F8: add.s       $f16, $f10, $f4
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f16.fl = ctx->f10.fl + ctx->f4.fl;
    // 0x801DF3FC: mtc1        $at, $f10
    ctx->f10.u32l = ctx->r1;
    // 0x801DF400: lui         $at, 0x43B4
    ctx->r1 = S32(0X43B4 << 16);
    // 0x801DF404: add.s       $f8, $f12, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = ctx->f12.fl + ctx->f6.fl;
    // 0x801DF408: mul.s       $f4, $f16, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f4.fl = MUL_S(ctx->f16.fl, ctx->f10.fl);
    // 0x801DF40C: lwc1        $f6, 0x6C($a0)
    ctx->f6.u32l = MEM_W(ctx->r4, 0X6C);
    // 0x801DF410: swc1        $f8, 0x88($a0)
    MEM_W(0X88, ctx->r4) = ctx->f8.u32l;
    // 0x801DF414: lwc1        $f8, 0x88($a0)
    ctx->f8.u32l = MEM_W(ctx->r4, 0X88);
    // 0x801DF418: add.s       $f18, $f6, $f8
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f18.fl = ctx->f6.fl + ctx->f8.fl;
    // 0x801DF41C: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x801DF420: lui         $at, 0x4580
    ctx->r1 = S32(0X4580 << 16);
    // 0x801DF424: div.s       $f8, $f4, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = DIV_S(ctx->f4.fl, ctx->f6.fl);
    // 0x801DF428: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x801DF42C: lui         $at, 0x43B4
    ctx->r1 = S32(0X43B4 << 16);
    // 0x801DF430: mul.s       $f6, $f18, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = MUL_S(ctx->f18.fl, ctx->f4.fl);
    // 0x801DF434: trunc.w.s   $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.u32l = TRUNC_W_S(ctx->f8.fl);
    // 0x801DF438: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x801DF43C: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x801DF440: mfc1        $v0, $f10
    ctx->r2 = (int32_t)ctx->f10.u32l;
    // 0x801DF444: div.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = DIV_S(ctx->f6.fl, ctx->f8.fl);
    // 0x801DF448: lwc1        $f8, 0x70($a0)
    ctx->f8.u32l = MEM_W(ctx->r4, 0X70);
    // 0x801DF44C: addiu       $t2, $v0, 0x400
    ctx->r10 = ADD32(ctx->r2, 0X400);
    // 0x801DF450: andi        $t3, $t2, 0xFFF
    ctx->r11 = ctx->r10 & 0XFFF;
    // 0x801DF454: sll         $t4, $t3, 2
    ctx->r12 = S32(ctx->r11 << 2);
    // 0x801DF458: addu        $t5, $a1, $t4
    ctx->r13 = ADD32(ctx->r5, ctx->r12);
    // 0x801DF45C: lwc1        $f6, 0x0($t5)
    ctx->f6.u32l = MEM_W(ctx->r13, 0X0);
    // 0x801DF460: trunc.w.s   $f4, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    ctx->f4.u32l = TRUNC_W_S(ctx->f10.fl);
    // 0x801DF464: mfc1        $v1, $f4
    ctx->r3 = (int32_t)ctx->f4.u32l;
    // 0x801DF468: nop

    // 0x801DF46C: addiu       $t8, $v1, 0x400
    ctx->r24 = ADD32(ctx->r3, 0X400);
    // 0x801DF470: andi        $t9, $t8, 0xFFF
    ctx->r25 = ctx->r24 & 0XFFF;
    // 0x801DF474: sll         $t0, $t9, 2
    ctx->r8 = S32(ctx->r25 << 2);
    // 0x801DF478: addu        $t1, $a1, $t0
    ctx->r9 = ADD32(ctx->r5, ctx->r8);
    // 0x801DF47C: lwc1        $f14, 0x0($t1)
    ctx->f14.u32l = MEM_W(ctx->r9, 0X0);
    // 0x801DF480: andi        $t6, $v1, 0xFFF
    ctx->r14 = ctx->r3 & 0XFFF;
    // 0x801DF484: sll         $t7, $t6, 2
    ctx->r15 = S32(ctx->r14 << 2);
    // 0x801DF488: mul.s       $f10, $f8, $f14
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f10.fl = MUL_S(ctx->f8.fl, ctx->f14.fl);
    // 0x801DF48C: addu        $t8, $a1, $t7
    ctx->r24 = ADD32(ctx->r5, ctx->r15);
    // 0x801DF490: lwc1        $f8, 0x0($t8)
    ctx->f8.u32l = MEM_W(ctx->r24, 0X0);
    // 0x801DF494: andi        $t9, $v0, 0xFFF
    ctx->r25 = ctx->r2 & 0XFFF;
    // 0x801DF498: sll         $t0, $t9, 2
    ctx->r8 = S32(ctx->r25 << 2);
    // 0x801DF49C: addu        $t1, $a1, $t0
    ctx->r9 = ADD32(ctx->r5, ctx->r8);
    // 0x801DF4A0: addiu       $a1, $sp, 0x38
    ctx->r5 = ADD32(ctx->r29, 0X38);
    // 0x801DF4A4: mul.s       $f4, $f6, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f4.fl = MUL_S(ctx->f6.fl, ctx->f10.fl);
    // 0x801DF4A8: addiu       $v0, $sp, 0x2C
    ctx->r2 = ADD32(ctx->r29, 0X2C);
    // 0x801DF4AC: addiu       $v1, $a2, 0x4
    ctx->r3 = ADD32(ctx->r6, 0X4);
    // 0x801DF4B0: swc1        $f4, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->f4.u32l;
    // 0x801DF4B4: lwc1        $f6, 0x70($a0)
    ctx->f6.u32l = MEM_W(ctx->r4, 0X70);
    // 0x801DF4B8: lwc1        $f4, 0x0($t1)
    ctx->f4.u32l = MEM_W(ctx->r9, 0X0);
    // 0x801DF4BC: mul.s       $f10, $f8, $f6
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f10.fl = MUL_S(ctx->f8.fl, ctx->f6.fl);
    // 0x801DF4C0: swc1        $f10, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->f10.u32l;
    // 0x801DF4C4: lwc1        $f8, 0x70($a0)
    ctx->f8.u32l = MEM_W(ctx->r4, 0X70);
    // 0x801DF4C8: mul.s       $f6, $f8, $f14
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f6.fl = MUL_S(ctx->f8.fl, ctx->f14.fl);
    // 0x801DF4CC: nop

    // 0x801DF4D0: mul.s       $f10, $f4, $f6
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f10.fl = MUL_S(ctx->f4.fl, ctx->f6.fl);
    // 0x801DF4D4: swc1        $f10, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->f10.u32l;
    // 0x801DF4D8: lw          $a3, 0x0($a0)
    ctx->r7 = MEM_W(ctx->r4, 0X0);
    // 0x801DF4DC: addiu       $a0, $a2, 0x5C
    ctx->r4 = ADD32(ctx->r6, 0X5C);
    // 0x801DF4E0: beq         $a3, $at, L_801DF4FC
    if (ctx->r7 == ctx->r1) {
        // 0x801DF4E4: nop
    
            goto L_801DF4FC;
    }
    // 0x801DF4E4: nop

    // 0x801DF4E8: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x801DF4EC: beq         $a3, $at, L_801DF52C
    if (ctx->r7 == ctx->r1) {
        // 0x801DF4F0: addiu       $v0, $sp, 0x2C
        ctx->r2 = ADD32(ctx->r29, 0X2C);
            goto L_801DF52C;
    }
    // 0x801DF4F0: addiu       $v0, $sp, 0x2C
    ctx->r2 = ADD32(ctx->r29, 0X2C);
    // 0x801DF4F4: b           L_801DF560
    // 0x801DF4F8: nop

        goto L_801DF560;
    // 0x801DF4F8: nop

L_801DF4FC:
    // 0x801DF4FC: lwc1        $f8, 0x0($a0)
    ctx->f8.u32l = MEM_W(ctx->r4, 0X0);
    // 0x801DF500: addiu       $v0, $v0, 0x4
    ctx->r2 = ADD32(ctx->r2, 0X4);
    // 0x801DF504: addiu       $v1, $v1, 0x4
    ctx->r3 = ADD32(ctx->r3, 0X4);
    // 0x801DF508: swc1        $f8, -0x4($v1)
    MEM_W(-0X4, ctx->r3) = ctx->f8.u32l;
    // 0x801DF50C: lwc1        $f6, 0x0($a0)
    ctx->f6.u32l = MEM_W(ctx->r4, 0X0);
    // 0x801DF510: lwc1        $f4, -0x4($v0)
    ctx->f4.u32l = MEM_W(ctx->r2, -0X4);
    // 0x801DF514: addiu       $a0, $a0, 0x4
    ctx->r4 = ADD32(ctx->r4, 0X4);
    // 0x801DF518: add.s       $f10, $f4, $f6
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f10.fl = ctx->f4.fl + ctx->f6.fl;
    // 0x801DF51C: bne         $v0, $a1, L_801DF4FC
    if (ctx->r2 != ctx->r5) {
        // 0x801DF520: swc1        $f10, 0x8($v1)
        MEM_W(0X8, ctx->r3) = ctx->f10.u32l;
            goto L_801DF4FC;
    }
    // 0x801DF520: swc1        $f10, 0x8($v1)
    MEM_W(0X8, ctx->r3) = ctx->f10.u32l;
    // 0x801DF524: b           L_801DF560
    // 0x801DF528: nop

        goto L_801DF560;
    // 0x801DF528: nop

L_801DF52C:
    // 0x801DF52C: addiu       $v1, $a2, 0x4
    ctx->r3 = ADD32(ctx->r6, 0X4);
    // 0x801DF530: addiu       $a0, $a2, 0x5C
    ctx->r4 = ADD32(ctx->r6, 0X5C);
    // 0x801DF534: addiu       $a1, $sp, 0x38
    ctx->r5 = ADD32(ctx->r29, 0X38);
L_801DF538:
    // 0x801DF538: lwc1        $f8, 0x0($a0)
    ctx->f8.u32l = MEM_W(ctx->r4, 0X0);
    // 0x801DF53C: addiu       $v0, $v0, 0x4
    ctx->r2 = ADD32(ctx->r2, 0X4);
    // 0x801DF540: addiu       $v1, $v1, 0x4
    ctx->r3 = ADD32(ctx->r3, 0X4);
    // 0x801DF544: swc1        $f8, 0x8($v1)
    MEM_W(0X8, ctx->r3) = ctx->f8.u32l;
    // 0x801DF548: lwc1        $f6, 0x0($a0)
    ctx->f6.u32l = MEM_W(ctx->r4, 0X0);
    // 0x801DF54C: lwc1        $f4, -0x4($v0)
    ctx->f4.u32l = MEM_W(ctx->r2, -0X4);
    // 0x801DF550: addiu       $a0, $a0, 0x4
    ctx->r4 = ADD32(ctx->r4, 0X4);
    // 0x801DF554: add.s       $f10, $f4, $f6
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f10.fl = ctx->f4.fl + ctx->f6.fl;
    // 0x801DF558: bne         $v0, $a1, L_801DF538
    if (ctx->r2 != ctx->r5) {
        // 0x801DF55C: swc1        $f10, -0x4($v1)
        MEM_W(-0X4, ctx->r3) = ctx->f10.u32l;
            goto L_801DF538;
    }
    // 0x801DF55C: swc1        $f10, -0x4($v1)
    MEM_W(-0X4, ctx->r3) = ctx->f10.u32l;
L_801DF560:
    // 0x801DF560: jal         0x801DEEC4
    // 0x801DF564: or          $a0, $a2, $zero
    ctx->r4 = ctx->r6 | 0;
    func_801DEEC4(rdram, ctx);
        goto after_0;
    // 0x801DF564: or          $a0, $a2, $zero
    ctx->r4 = ctx->r6 | 0;
    after_0:
    // 0x801DF568: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x801DF56C: addiu       $sp, $sp, 0x48
    ctx->r29 = ADD32(ctx->r29, 0X48);
    // 0x801DF570: jr          $ra
    // 0x801DF574: nop

    return;
    // 0x801DF574: nop

;}
RECOMP_FUNC void func_801DF578(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801DF578: addiu       $t6, $zero, 0x5
    ctx->r14 = ADD32(0, 0X5);
    // 0x801DF57C: sw          $t6, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r14;
    // 0x801DF580: or          $t9, $a1, $zero
    ctx->r25 = ctx->r5 | 0;
    // 0x801DF584: or          $t0, $a0, $zero
    ctx->r8 = ctx->r4 | 0;
    // 0x801DF588: addiu       $t8, $a1, 0x54
    ctx->r24 = ADD32(ctx->r5, 0X54);
L_801DF58C:
    // 0x801DF58C: lw          $at, 0x0($t9)
    ctx->r1 = MEM_W(ctx->r25, 0X0);
    // 0x801DF590: addiu       $t9, $t9, 0xC
    ctx->r25 = ADD32(ctx->r25, 0XC);
    // 0x801DF594: addiu       $t0, $t0, 0xC
    ctx->r8 = ADD32(ctx->r8, 0XC);
    // 0x801DF598: sw          $at, -0x8($t0)
    MEM_W(-0X8, ctx->r8) = ctx->r1;
    // 0x801DF59C: lw          $at, -0x8($t9)
    ctx->r1 = MEM_W(ctx->r25, -0X8);
    // 0x801DF5A0: sw          $at, -0x4($t0)
    MEM_W(-0X4, ctx->r8) = ctx->r1;
    // 0x801DF5A4: lw          $at, -0x4($t9)
    ctx->r1 = MEM_W(ctx->r25, -0X4);
    // 0x801DF5A8: bne         $t9, $t8, L_801DF58C
    if (ctx->r25 != ctx->r24) {
        // 0x801DF5AC: sw          $at, 0x0($t0)
        MEM_W(0X0, ctx->r8) = ctx->r1;
            goto L_801DF58C;
    }
    // 0x801DF5AC: sw          $at, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r1;
    // 0x801DF5B0: lw          $at, 0x0($t9)
    ctx->r1 = MEM_W(ctx->r25, 0X0);
    // 0x801DF5B4: or          $t3, $a2, $zero
    ctx->r11 = ctx->r6 | 0;
    // 0x801DF5B8: or          $t4, $a0, $zero
    ctx->r12 = ctx->r4 | 0;
    // 0x801DF5BC: addiu       $t2, $a2, 0x84
    ctx->r10 = ADD32(ctx->r6, 0X84);
    // 0x801DF5C0: sw          $at, 0x4($t0)
    MEM_W(0X4, ctx->r8) = ctx->r1;
L_801DF5C4:
    // 0x801DF5C4: lw          $at, 0x0($t3)
    ctx->r1 = MEM_W(ctx->r11, 0X0);
    // 0x801DF5C8: addiu       $t3, $t3, 0xC
    ctx->r11 = ADD32(ctx->r11, 0XC);
    // 0x801DF5CC: addiu       $t4, $t4, 0xC
    ctx->r12 = ADD32(ctx->r12, 0XC);
    // 0x801DF5D0: sw          $at, 0x50($t4)
    MEM_W(0X50, ctx->r12) = ctx->r1;
    // 0x801DF5D4: lw          $at, -0x8($t3)
    ctx->r1 = MEM_W(ctx->r11, -0X8);
    // 0x801DF5D8: sw          $at, 0x54($t4)
    MEM_W(0X54, ctx->r12) = ctx->r1;
    // 0x801DF5DC: lw          $at, -0x4($t3)
    ctx->r1 = MEM_W(ctx->r11, -0X4);
    // 0x801DF5E0: bne         $t3, $t2, L_801DF5C4
    if (ctx->r11 != ctx->r10) {
        // 0x801DF5E4: sw          $at, 0x58($t4)
        MEM_W(0X58, ctx->r12) = ctx->r1;
            goto L_801DF5C4;
    }
    // 0x801DF5E4: sw          $at, 0x58($t4)
    MEM_W(0X58, ctx->r12) = ctx->r1;
    // 0x801DF5E8: jr          $ra
    // 0x801DF5EC: nop

    return;
    // 0x801DF5EC: nop

;}
RECOMP_FUNC void func_801DF5F0(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801DF5F0: addiu       $t6, $zero, 0x5
    ctx->r14 = ADD32(0, 0X5);
    // 0x801DF5F4: sw          $t6, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r14;
    // 0x801DF5F8: or          $t9, $a1, $zero
    ctx->r25 = ctx->r5 | 0;
    // 0x801DF5FC: or          $t0, $a0, $zero
    ctx->r8 = ctx->r4 | 0;
    // 0x801DF600: addiu       $t8, $a1, 0x54
    ctx->r24 = ADD32(ctx->r5, 0X54);
L_801DF604:
    // 0x801DF604: lw          $at, 0x0($t9)
    ctx->r1 = MEM_W(ctx->r25, 0X0);
    // 0x801DF608: addiu       $t9, $t9, 0xC
    ctx->r25 = ADD32(ctx->r25, 0XC);
    // 0x801DF60C: addiu       $t0, $t0, 0xC
    ctx->r8 = ADD32(ctx->r8, 0XC);
    // 0x801DF610: sw          $at, -0x8($t0)
    MEM_W(-0X8, ctx->r8) = ctx->r1;
    // 0x801DF614: lw          $at, -0x8($t9)
    ctx->r1 = MEM_W(ctx->r25, -0X8);
    // 0x801DF618: sw          $at, -0x4($t0)
    MEM_W(-0X4, ctx->r8) = ctx->r1;
    // 0x801DF61C: lw          $at, -0x4($t9)
    ctx->r1 = MEM_W(ctx->r25, -0X4);
    // 0x801DF620: bne         $t9, $t8, L_801DF604
    if (ctx->r25 != ctx->r24) {
        // 0x801DF624: sw          $at, 0x0($t0)
        MEM_W(0X0, ctx->r8) = ctx->r1;
            goto L_801DF604;
    }
    // 0x801DF624: sw          $at, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r1;
    // 0x801DF628: lw          $at, 0x0($t9)
    ctx->r1 = MEM_W(ctx->r25, 0X0);
    // 0x801DF62C: or          $t3, $a1, $zero
    ctx->r11 = ctx->r5 | 0;
    // 0x801DF630: or          $t4, $a0, $zero
    ctx->r12 = ctx->r4 | 0;
    // 0x801DF634: addiu       $t2, $a1, 0x84
    ctx->r10 = ADD32(ctx->r5, 0X84);
    // 0x801DF638: sw          $at, 0x4($t0)
    MEM_W(0X4, ctx->r8) = ctx->r1;
L_801DF63C:
    // 0x801DF63C: lw          $at, 0x58($t3)
    ctx->r1 = MEM_W(ctx->r11, 0X58);
    // 0x801DF640: addiu       $t3, $t3, 0xC
    ctx->r11 = ADD32(ctx->r11, 0XC);
    // 0x801DF644: addiu       $t4, $t4, 0xC
    ctx->r12 = ADD32(ctx->r12, 0XC);
    // 0x801DF648: sw          $at, 0x50($t4)
    MEM_W(0X50, ctx->r12) = ctx->r1;
    // 0x801DF64C: lw          $at, 0x50($t3)
    ctx->r1 = MEM_W(ctx->r11, 0X50);
    // 0x801DF650: sw          $at, 0x54($t4)
    MEM_W(0X54, ctx->r12) = ctx->r1;
    // 0x801DF654: lw          $at, 0x54($t3)
    ctx->r1 = MEM_W(ctx->r11, 0X54);
    // 0x801DF658: bne         $t3, $t2, L_801DF63C
    if (ctx->r11 != ctx->r10) {
        // 0x801DF65C: sw          $at, 0x58($t4)
        MEM_W(0X58, ctx->r12) = ctx->r1;
            goto L_801DF63C;
    }
    // 0x801DF65C: sw          $at, 0x58($t4)
    MEM_W(0X58, ctx->r12) = ctx->r1;
    // 0x801DF660: jr          $ra
    // 0x801DF664: nop

    return;
    // 0x801DF664: nop

;}
RECOMP_FUNC void func_801DF668(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801DF668: beq         $a1, $zero, L_801DF694
    if (ctx->r5 == 0) {
        // 0x801DF66C: or          $v0, $zero, $zero
        ctx->r2 = 0 | 0;
            goto L_801DF694;
    }
    // 0x801DF66C: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    // 0x801DF670: or          $v1, $a1, $zero
    ctx->r3 = ctx->r5 | 0;
    // 0x801DF674: addiu       $t0, $a0, 0x5C
    ctx->r8 = ADD32(ctx->r4, 0X5C);
    // 0x801DF678: addiu       $t1, $zero, 0x3
    ctx->r9 = ADD32(0, 0X3);
L_801DF67C:
    // 0x801DF67C: lwc1        $f4, 0x0($v1)
    ctx->f4.u32l = MEM_W(ctx->r3, 0X0);
    // 0x801DF680: addiu       $v0, $v0, 0x1
    ctx->r2 = ADD32(ctx->r2, 0X1);
    // 0x801DF684: addiu       $v1, $v1, 0x4
    ctx->r3 = ADD32(ctx->r3, 0X4);
    // 0x801DF688: addiu       $t0, $t0, 0x4
    ctx->r8 = ADD32(ctx->r8, 0X4);
    // 0x801DF68C: bne         $v0, $t1, L_801DF67C
    if (ctx->r2 != ctx->r9) {
        // 0x801DF690: swc1        $f4, -0x4($t0)
        MEM_W(-0X4, ctx->r8) = ctx->f4.u32l;
            goto L_801DF67C;
    }
    // 0x801DF690: swc1        $f4, -0x4($t0)
    MEM_W(-0X4, ctx->r8) = ctx->f4.u32l;
L_801DF694:
    // 0x801DF694: beq         $a2, $zero, L_801DF6C8
    if (ctx->r6 == 0) {
        // 0x801DF698: addiu       $t1, $zero, 0x3
        ctx->r9 = ADD32(0, 0X3);
            goto L_801DF6C8;
    }
    // 0x801DF698: addiu       $t1, $zero, 0x3
    ctx->r9 = ADD32(0, 0X3);
    // 0x801DF69C: addiu       $v0, $a0, 0x5C
    ctx->r2 = ADD32(ctx->r4, 0X5C);
    // 0x801DF6A0: lw          $t6, 0x74($v0)
    ctx->r14 = MEM_W(ctx->r2, 0X74);
    // 0x801DF6A4: lw          $t9, 0x78($v0)
    ctx->r25 = MEM_W(ctx->r2, 0X78);
    // 0x801DF6A8: sll         $t7, $t6, 2
    ctx->r15 = S32(ctx->r14 << 2);
    // 0x801DF6AC: addu        $t8, $a2, $t7
    ctx->r24 = ADD32(ctx->r6, ctx->r15);
    // 0x801DF6B0: lwc1        $f6, 0x0($t8)
    ctx->f6.u32l = MEM_W(ctx->r24, 0X0);
    // 0x801DF6B4: sll         $t2, $t9, 2
    ctx->r10 = S32(ctx->r25 << 2);
    // 0x801DF6B8: addu        $t3, $a2, $t2
    ctx->r11 = ADD32(ctx->r6, ctx->r10);
    // 0x801DF6BC: swc1        $f6, 0x24($v0)
    MEM_W(0X24, ctx->r2) = ctx->f6.u32l;
    // 0x801DF6C0: lwc1        $f8, 0x0($t3)
    ctx->f8.u32l = MEM_W(ctx->r11, 0X0);
    // 0x801DF6C4: swc1        $f8, 0x28($v0)
    MEM_W(0X28, ctx->r2) = ctx->f8.u32l;
L_801DF6C8:
    // 0x801DF6C8: beq         $a3, $zero, L_801DF6D8
    if (ctx->r7 == 0) {
        // 0x801DF6CC: addiu       $a2, $a0, 0x4
        ctx->r6 = ADD32(ctx->r4, 0X4);
            goto L_801DF6D8;
    }
    // 0x801DF6CC: addiu       $a2, $a0, 0x4
    ctx->r6 = ADD32(ctx->r4, 0X4);
    // 0x801DF6D0: lwc1        $f10, 0x0($a3)
    ctx->f10.u32l = MEM_W(ctx->r7, 0X0);
    // 0x801DF6D4: swc1        $f10, 0x90($a0)
    MEM_W(0X90, ctx->r4) = ctx->f10.u32l;
L_801DF6D8:
    // 0x801DF6D8: lw          $v1, 0x10($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X10);
    // 0x801DF6DC: beql        $v1, $zero, L_801DF704
    if (ctx->r3 == 0) {
        // 0x801DF6E0: lw          $v1, 0x14($sp)
        ctx->r3 = MEM_W(ctx->r29, 0X14);
            goto L_801DF704;
    }
    goto skip_0;
    // 0x801DF6E0: lw          $v1, 0x14($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X14);
    skip_0:
    // 0x801DF6E4: lwc1        $f16, 0x0($v1)
    ctx->f16.u32l = MEM_W(ctx->r3, 0X0);
    // 0x801DF6E8: addiu       $v0, $a0, 0x5C
    ctx->r2 = ADD32(ctx->r4, 0X5C);
    // 0x801DF6EC: swc1        $f16, 0x4C($v0)
    MEM_W(0X4C, ctx->r2) = ctx->f16.u32l;
    // 0x801DF6F0: lwc1        $f18, 0x4($v1)
    ctx->f18.u32l = MEM_W(ctx->r3, 0X4);
    // 0x801DF6F4: swc1        $f18, 0x58($v0)
    MEM_W(0X58, ctx->r2) = ctx->f18.u32l;
    // 0x801DF6F8: lwc1        $f4, 0x8($v1)
    ctx->f4.u32l = MEM_W(ctx->r3, 0X8);
    // 0x801DF6FC: swc1        $f4, 0x64($v0)
    MEM_W(0X64, ctx->r2) = ctx->f4.u32l;
    // 0x801DF700: lw          $v1, 0x14($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X14);
L_801DF704:
    // 0x801DF704: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    // 0x801DF708: beq         $v1, $zero, L_801DF728
    if (ctx->r3 == 0) {
        // 0x801DF70C: or          $a1, $v1, $zero
        ctx->r5 = ctx->r3 | 0;
            goto L_801DF728;
    }
    // 0x801DF70C: or          $a1, $v1, $zero
    ctx->r5 = ctx->r3 | 0;
L_801DF710:
    // 0x801DF710: lwc1        $f6, 0x0($a1)
    ctx->f6.u32l = MEM_W(ctx->r5, 0X0);
    // 0x801DF714: addiu       $v0, $v0, 0x1
    ctx->r2 = ADD32(ctx->r2, 0X1);
    // 0x801DF718: addiu       $a1, $a1, 0x4
    ctx->r5 = ADD32(ctx->r5, 0X4);
    // 0x801DF71C: addiu       $a2, $a2, 0x4
    ctx->r6 = ADD32(ctx->r6, 0X4);
    // 0x801DF720: bne         $v0, $t1, L_801DF710
    if (ctx->r2 != ctx->r9) {
        // 0x801DF724: swc1        $f6, 0x20($a2)
        MEM_W(0X20, ctx->r6) = ctx->f6.u32l;
            goto L_801DF710;
    }
    // 0x801DF724: swc1        $f6, 0x20($a2)
    MEM_W(0X20, ctx->r6) = ctx->f6.u32l;
L_801DF728:
    // 0x801DF728: lw          $v0, 0x18($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X18);
    // 0x801DF72C: beq         $v0, $zero, L_801DF73C
    if (ctx->r2 == 0) {
        // 0x801DF730: nop
    
            goto L_801DF73C;
    }
    // 0x801DF730: nop

    // 0x801DF734: lwc1        $f8, 0x0($v0)
    ctx->f8.u32l = MEM_W(ctx->r2, 0X0);
    // 0x801DF738: swc1        $f8, 0x3C($a0)
    MEM_W(0X3C, ctx->r4) = ctx->f8.u32l;
L_801DF73C:
    // 0x801DF73C: jr          $ra
    // 0x801DF740: nop

    return;
    // 0x801DF740: nop

;}
RECOMP_FUNC void func_801DF744(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801DF744: addiu       $sp, $sp, -0x50
    ctx->r29 = ADD32(ctx->r29, -0X50);
    // 0x801DF748: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x801DF74C: sw          $s0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r16;
    // 0x801DF750: lwc1        $f0, 0xA4($a0)
    ctx->f0.u32l = MEM_W(ctx->r4, 0XA4);
    // 0x801DF754: lwc1        $f4, 0xA8($a0)
    ctx->f4.u32l = MEM_W(ctx->r4, 0XA8);
    // 0x801DF758: lwc1        $f6, 0xAC($a0)
    ctx->f6.u32l = MEM_W(ctx->r4, 0XAC);
    // 0x801DF75C: lwc1        $f2, 0xBC($a0)
    ctx->f2.u32l = MEM_W(ctx->r4, 0XBC);
    // 0x801DF760: sub.s       $f8, $f4, $f0
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f8.fl = ctx->f4.fl - ctx->f0.fl;
    // 0x801DF764: lwc1        $f4, 0xC0($a0)
    ctx->f4.u32l = MEM_W(ctx->r4, 0XC0);
    // 0x801DF768: lwc1        $f14, 0xB0($a0)
    ctx->f14.u32l = MEM_W(ctx->r4, 0XB0);
    // 0x801DF76C: lw          $t8, 0xD0($a0)
    ctx->r24 = MEM_W(ctx->r4, 0XD0);
    // 0x801DF770: mul.s       $f18, $f8, $f6
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f18.fl = MUL_S(ctx->f8.fl, ctx->f6.fl);
    // 0x801DF774: sub.s       $f8, $f4, $f2
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f8.fl = ctx->f4.fl - ctx->f2.fl;
    // 0x801DF778: lwc1        $f6, 0xC4($a0)
    ctx->f6.u32l = MEM_W(ctx->r4, 0XC4);
    // 0x801DF77C: lwc1        $f4, 0xB4($a0)
    ctx->f4.u32l = MEM_W(ctx->r4, 0XB4);
    // 0x801DF780: sll         $t9, $t8, 2
    ctx->r25 = S32(ctx->r24 << 2);
    // 0x801DF784: addu        $t1, $a0, $t9
    ctx->r9 = ADD32(ctx->r4, ctx->r25);
    // 0x801DF788: or          $s0, $a0, $zero
    ctx->r16 = ctx->r4 | 0;
    // 0x801DF78C: add.s       $f10, $f0, $f18
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f10.fl = ctx->f0.fl + ctx->f18.fl;
    // 0x801DF790: mul.s       $f18, $f8, $f6
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f18.fl = MUL_S(ctx->f8.fl, ctx->f6.fl);
    // 0x801DF794: lwc1        $f6, 0xB8($a0)
    ctx->f6.u32l = MEM_W(ctx->r4, 0XB8);
    // 0x801DF798: sub.s       $f8, $f4, $f14
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f8.fl = ctx->f4.fl - ctx->f14.fl;
    // 0x801DF79C: swc1        $f10, 0xA4($a0)
    MEM_W(0XA4, ctx->r4) = ctx->f10.u32l;
    // 0x801DF7A0: lwc1        $f4, 0x74($a0)
    ctx->f4.u32l = MEM_W(ctx->r4, 0X74);
    // 0x801DF7A4: add.s       $f10, $f2, $f18
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f10.fl = ctx->f2.fl + ctx->f18.fl;
    // 0x801DF7A8: mul.s       $f18, $f8, $f6
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f18.fl = MUL_S(ctx->f8.fl, ctx->f6.fl);
    // 0x801DF7AC: swc1        $f10, 0xBC($a0)
    MEM_W(0XBC, ctx->r4) = ctx->f10.u32l;
    // 0x801DF7B0: add.s       $f10, $f14, $f18
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f10.fl = ctx->f14.fl + ctx->f18.fl;
    // 0x801DF7B4: swc1        $f10, 0xB0($a0)
    MEM_W(0XB0, ctx->r4) = ctx->f10.u32l;
    // 0x801DF7B8: lwc1        $f8, 0x5C($t1)
    ctx->f8.u32l = MEM_W(ctx->r9, 0X5C);
    // 0x801DF7BC: sub.s       $f6, $f4, $f8
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f6.fl = ctx->f4.fl - ctx->f8.fl;
    // 0x801DF7C0: swc1        $f6, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->f6.u32l;
    // 0x801DF7C4: lw          $t2, 0xD4($a0)
    ctx->r10 = MEM_W(ctx->r4, 0XD4);
    // 0x801DF7C8: lwc1        $f18, 0x78($a0)
    ctx->f18.u32l = MEM_W(ctx->r4, 0X78);
    // 0x801DF7CC: sll         $t3, $t2, 2
    ctx->r11 = S32(ctx->r10 << 2);
    // 0x801DF7D0: addu        $t4, $a0, $t3
    ctx->r12 = ADD32(ctx->r4, ctx->r11);
    // 0x801DF7D4: lwc1        $f10, 0x5C($t4)
    ctx->f10.u32l = MEM_W(ctx->r12, 0X5C);
    // 0x801DF7D8: sub.s       $f4, $f18, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f4.fl = ctx->f18.fl - ctx->f10.fl;
    // 0x801DF7DC: lwc1        $f18, 0x40($sp)
    ctx->f18.u32l = MEM_W(ctx->r29, 0X40);
    // 0x801DF7E0: swc1        $f4, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->f4.u32l;
    // 0x801DF7E4: lwc1        $f8, 0x44($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X44);
    // 0x801DF7E8: mul.s       $f6, $f8, $f8
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f6.fl = MUL_S(ctx->f8.fl, ctx->f8.fl);
    // 0x801DF7EC: nop

    // 0x801DF7F0: mul.s       $f10, $f18, $f18
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f10.fl = MUL_S(ctx->f18.fl, ctx->f18.fl);
    // 0x801DF7F4: jal         0x800C7010
    // 0x801DF7F8: add.s       $f12, $f6, $f10
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f12.fl = ctx->f6.fl + ctx->f10.fl;
    _nsqrtf(rdram, ctx);
        goto after_0;
    // 0x801DF7F8: add.s       $f12, $f6, $f10
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f12.fl = ctx->f6.fl + ctx->f10.fl;
    after_0:
    // 0x801DF7FC: addiu       $v0, $s0, 0x5C
    ctx->r2 = ADD32(ctx->r16, 0X5C);
    // 0x801DF800: lwc1        $f4, 0x20($v0)
    ctx->f4.u32l = MEM_W(ctx->r2, 0X20);
    // 0x801DF804: lwc1        $f8, 0x40($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X40);
    // 0x801DF808: lw          $t5, 0x74($v0)
    ctx->r13 = MEM_W(ctx->r2, 0X74);
    // 0x801DF80C: div.s       $f2, $f4, $f0
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f2.fl = DIV_S(ctx->f4.fl, ctx->f0.fl);
    // 0x801DF810: lw          $t8, 0x78($v0)
    ctx->r24 = MEM_W(ctx->r2, 0X78);
    // 0x801DF814: sll         $t6, $t5, 2
    ctx->r14 = S32(ctx->r13 << 2);
    // 0x801DF818: addu        $t7, $v0, $t6
    ctx->r15 = ADD32(ctx->r2, ctx->r14);
    // 0x801DF81C: lwc1        $f6, 0x0($t7)
    ctx->f6.u32l = MEM_W(ctx->r15, 0X0);
    // 0x801DF820: sll         $t9, $t8, 2
    ctx->r25 = S32(ctx->r24 << 2);
    // 0x801DF824: addu        $t1, $v0, $t9
    ctx->r9 = ADD32(ctx->r2, ctx->r25);
    // 0x801DF828: mul.s       $f18, $f8, $f2
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f18.fl = MUL_S(ctx->f8.fl, ctx->f2.fl);
    // 0x801DF82C: add.s       $f10, $f18, $f6
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f10.fl = ctx->f18.fl + ctx->f6.fl;
    // 0x801DF830: swc1        $f10, 0x18($v0)
    MEM_W(0X18, ctx->r2) = ctx->f10.u32l;
    // 0x801DF834: lwc1        $f4, 0x44($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X44);
    // 0x801DF838: lwc1        $f18, 0x0($t1)
    ctx->f18.u32l = MEM_W(ctx->r9, 0X0);
    // 0x801DF83C: mul.s       $f8, $f4, $f2
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f8.fl = MUL_S(ctx->f4.fl, ctx->f2.fl);
    // 0x801DF840: add.s       $f6, $f8, $f18
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f6.fl = ctx->f8.fl + ctx->f18.fl;
    // 0x801DF844: swc1        $f6, 0x1C($v0)
    MEM_W(0X1C, ctx->r2) = ctx->f6.u32l;
    // 0x801DF848: sw          $v0, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r2;
    // 0x801DF84C: lwc1        $f14, 0x40($sp)
    ctx->f14.u32l = MEM_W(ctx->r29, 0X40);
    // 0x801DF850: jal         0x801ED154
    // 0x801DF854: lwc1        $f12, 0x44($sp)
    ctx->f12.u32l = MEM_W(ctx->r29, 0X44);
    func_801ED154(rdram, ctx);
        goto after_1;
    // 0x801DF854: lwc1        $f12, 0x44($sp)
    ctx->f12.u32l = MEM_W(ctx->r29, 0X44);
    after_1:
    // 0x801DF858: lw          $v0, 0x28($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X28);
    // 0x801DF85C: lui         $at, 0x4580
    ctx->r1 = S32(0X4580 << 16);
    // 0x801DF860: mtc1        $at, $f14
    ctx->f14.u32l = ctx->r1;
    // 0x801DF864: lwc1        $f10, 0x54($v0)
    ctx->f10.u32l = MEM_W(ctx->r2, 0X54);
    // 0x801DF868: lui         $at, 0x43B4
    ctx->r1 = S32(0X43B4 << 16);
    // 0x801DF86C: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
    // 0x801DF870: add.s       $f2, $f0, $f10
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f2.fl = ctx->f0.fl + ctx->f10.fl;
    // 0x801DF874: lwc1        $f10, 0x60($v0)
    ctx->f10.u32l = MEM_W(ctx->r2, 0X60);
    // 0x801DF878: lui         $v1, 0x8015
    ctx->r3 = S32(0X8015 << 16);
    // 0x801DF87C: addiu       $v1, $v1, 0x4350
    ctx->r3 = ADD32(ctx->r3, 0X4350);
    // 0x801DF880: mul.s       $f4, $f2, $f14
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f4.fl = MUL_S(ctx->f2.fl, ctx->f14.fl);
    // 0x801DF884: lw          $a1, 0x74($v0)
    ctx->r5 = MEM_W(ctx->r2, 0X74);
    // 0x801DF888: lwc1        $f6, 0x48($v0)
    ctx->f6.u32l = MEM_W(ctx->r2, 0X48);
    // 0x801DF88C: addiu       $t0, $s0, 0x4
    ctx->r8 = ADD32(ctx->r16, 0X4);
    // 0x801DF890: sll         $t2, $a1, 2
    ctx->r10 = S32(ctx->r5 << 2);
    // 0x801DF894: or          $a1, $t2, $zero
    ctx->r5 = ctx->r10 | 0;
    // 0x801DF898: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x801DF89C: div.s       $f8, $f4, $f16
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f8.fl = DIV_S(ctx->f4.fl, ctx->f16.fl);
    // 0x801DF8A0: mul.s       $f4, $f10, $f14
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f4.fl = MUL_S(ctx->f10.fl, ctx->f14.fl);
    // 0x801DF8A4: trunc.w.s   $f18, $f8
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 8);
    ctx->f18.u32l = TRUNC_W_S(ctx->f8.fl);
    // 0x801DF8A8: div.s       $f8, $f4, $f16
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f8.fl = DIV_S(ctx->f4.fl, ctx->f16.fl);
    // 0x801DF8AC: mfc1        $a0, $f18
    ctx->r4 = (int32_t)ctx->f18.u32l;
    // 0x801DF8B0: nop

    // 0x801DF8B4: addiu       $t1, $a0, 0x400
    ctx->r9 = ADD32(ctx->r4, 0X400);
    // 0x801DF8B8: andi        $t2, $t1, 0xFFF
    ctx->r10 = ctx->r9 & 0XFFF;
    // 0x801DF8BC: sll         $t3, $t2, 2
    ctx->r11 = S32(ctx->r10 << 2);
    // 0x801DF8C0: addu        $t4, $v1, $t3
    ctx->r12 = ADD32(ctx->r3, ctx->r11);
    // 0x801DF8C4: trunc.w.s   $f18, $f8
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 8);
    ctx->f18.u32l = TRUNC_W_S(ctx->f8.fl);
    // 0x801DF8C8: lwc1        $f8, 0x0($t4)
    ctx->f8.u32l = MEM_W(ctx->r12, 0X0);
    // 0x801DF8CC: mfc1        $t5, $f18
    ctx->r13 = (int32_t)ctx->f18.u32l;
    // 0x801DF8D0: nop

    // 0x801DF8D4: addiu       $t6, $t5, 0x400
    ctx->r14 = ADD32(ctx->r13, 0X400);
    // 0x801DF8D8: andi        $t7, $t6, 0xFFF
    ctx->r15 = ctx->r14 & 0XFFF;
    // 0x801DF8DC: sll         $t8, $t7, 2
    ctx->r24 = S32(ctx->r15 << 2);
    // 0x801DF8E0: addu        $t9, $v1, $t8
    ctx->r25 = ADD32(ctx->r3, ctx->r24);
    // 0x801DF8E4: lwc1        $f10, 0x0($t9)
    ctx->f10.u32l = MEM_W(ctx->r25, 0X0);
    // 0x801DF8E8: addu        $t5, $v0, $a1
    ctx->r13 = ADD32(ctx->r2, ctx->r5);
    // 0x801DF8EC: addu        $t6, $t0, $a1
    ctx->r14 = ADD32(ctx->r8, ctx->r5);
    // 0x801DF8F0: mul.s       $f4, $f6, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f4.fl = MUL_S(ctx->f6.fl, ctx->f10.fl);
    // 0x801DF8F4: lwc1        $f6, 0x0($t5)
    ctx->f6.u32l = MEM_W(ctx->r13, 0X0);
    // 0x801DF8F8: andi        $t5, $a0, 0xFFF
    ctx->r13 = ctx->r4 & 0XFFF;
    // 0x801DF8FC: mul.s       $f18, $f8, $f4
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f18.fl = MUL_S(ctx->f8.fl, ctx->f4.fl);
    // 0x801DF900: add.s       $f10, $f18, $f6
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f10.fl = ctx->f18.fl + ctx->f6.fl;
    // 0x801DF904: swc1        $f10, 0xC($t6)
    MEM_W(0XC, ctx->r14) = ctx->f10.u32l;
    // 0x801DF908: lwc1        $f4, 0x60($v0)
    ctx->f4.u32l = MEM_W(ctx->r2, 0X60);
    // 0x801DF90C: lwc1        $f8, 0x48($v0)
    ctx->f8.u32l = MEM_W(ctx->r2, 0X48);
    // 0x801DF910: lw          $a2, 0x78($v0)
    ctx->r6 = MEM_W(ctx->r2, 0X78);
    // 0x801DF914: mul.s       $f18, $f4, $f14
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f18.fl = MUL_S(ctx->f4.fl, ctx->f14.fl);
    // 0x801DF918: sll         $t6, $t5, 2
    ctx->r14 = S32(ctx->r13 << 2);
    // 0x801DF91C: sll         $t7, $a2, 2
    ctx->r15 = S32(ctx->r6 << 2);
    // 0x801DF920: or          $a2, $t7, $zero
    ctx->r6 = ctx->r15 | 0;
    // 0x801DF924: addu        $t7, $v1, $t6
    ctx->r15 = ADD32(ctx->r3, ctx->r14);
    // 0x801DF928: addu        $t8, $v0, $a2
    ctx->r24 = ADD32(ctx->r2, ctx->r6);
    // 0x801DF92C: div.s       $f6, $f18, $f16
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f6.fl = DIV_S(ctx->f18.fl, ctx->f16.fl);
    // 0x801DF930: trunc.w.s   $f10, $f6
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    ctx->f10.u32l = TRUNC_W_S(ctx->f6.fl);
    // 0x801DF934: lwc1        $f6, 0x0($t7)
    ctx->f6.u32l = MEM_W(ctx->r15, 0X0);
    // 0x801DF938: mfc1        $t9, $f10
    ctx->r25 = (int32_t)ctx->f10.u32l;
    // 0x801DF93C: nop

    // 0x801DF940: addiu       $t1, $t9, 0x400
    ctx->r9 = ADD32(ctx->r25, 0X400);
    // 0x801DF944: andi        $t2, $t1, 0xFFF
    ctx->r10 = ctx->r9 & 0XFFF;
    // 0x801DF948: sll         $t3, $t2, 2
    ctx->r11 = S32(ctx->r10 << 2);
    // 0x801DF94C: addu        $t4, $v1, $t3
    ctx->r12 = ADD32(ctx->r3, ctx->r11);
    // 0x801DF950: lwc1        $f4, 0x0($t4)
    ctx->f4.u32l = MEM_W(ctx->r12, 0X0);
    // 0x801DF954: addu        $t9, $t0, $a2
    ctx->r25 = ADD32(ctx->r8, ctx->r6);
    // 0x801DF958: mul.s       $f18, $f8, $f4
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f18.fl = MUL_S(ctx->f8.fl, ctx->f4.fl);
    // 0x801DF95C: lwc1        $f8, 0x0($t8)
    ctx->f8.u32l = MEM_W(ctx->r24, 0X0);
    // 0x801DF960: mul.s       $f10, $f6, $f18
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f10.fl = MUL_S(ctx->f6.fl, ctx->f18.fl);
    // 0x801DF964: add.s       $f4, $f10, $f8
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f4.fl = ctx->f10.fl + ctx->f8.fl;
    // 0x801DF968: swc1        $f4, 0xC($t9)
    MEM_W(0XC, ctx->r25) = ctx->f4.u32l;
    // 0x801DF96C: lwc1        $f6, 0x60($v0)
    ctx->f6.u32l = MEM_W(ctx->r2, 0X60);
    // 0x801DF970: lw          $a3, 0x7C($v0)
    ctx->r7 = MEM_W(ctx->r2, 0X7C);
    // 0x801DF974: lwc1        $f12, 0xC($v0)
    ctx->f12.u32l = MEM_W(ctx->r2, 0XC);
    // 0x801DF978: mul.s       $f18, $f6, $f14
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f18.fl = MUL_S(ctx->f6.fl, ctx->f14.fl);
    // 0x801DF97C: sll         $t1, $a3, 2
    ctx->r9 = S32(ctx->r7 << 2);
    // 0x801DF980: addu        $t7, $v0, $t1
    ctx->r15 = ADD32(ctx->r2, ctx->r9);
    // 0x801DF984: lwc1        $f6, 0x48($v0)
    ctx->f6.u32l = MEM_W(ctx->r2, 0X48);
    // 0x801DF988: addu        $t8, $t0, $t1
    ctx->r24 = ADD32(ctx->r8, ctx->r9);
    // 0x801DF98C: div.s       $f10, $f18, $f16
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f10.fl = DIV_S(ctx->f18.fl, ctx->f16.fl);
    // 0x801DF990: trunc.w.s   $f8, $f10
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    ctx->f8.u32l = TRUNC_W_S(ctx->f10.fl);
    // 0x801DF994: lwc1        $f10, 0x0($t7)
    ctx->f10.u32l = MEM_W(ctx->r15, 0X0);
    // 0x801DF998: mfc1        $t3, $f8
    ctx->r11 = (int32_t)ctx->f8.u32l;
    // 0x801DF99C: sub.s       $f8, $f10, $f12
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f8.fl = ctx->f10.fl - ctx->f12.fl;
    // 0x801DF9A0: andi        $t4, $t3, 0xFFF
    ctx->r12 = ctx->r11 & 0XFFF;
    // 0x801DF9A4: sll         $t5, $t4, 2
    ctx->r13 = S32(ctx->r12 << 2);
    // 0x801DF9A8: addu        $t6, $v1, $t5
    ctx->r14 = ADD32(ctx->r3, ctx->r13);
    // 0x801DF9AC: lwc1        $f4, 0x0($t6)
    ctx->f4.u32l = MEM_W(ctx->r14, 0X0);
    // 0x801DF9B0: mul.s       $f18, $f4, $f6
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f18.fl = MUL_S(ctx->f4.fl, ctx->f6.fl);
    // 0x801DF9B4: lwc1        $f4, 0x6C($v0)
    ctx->f4.u32l = MEM_W(ctx->r2, 0X6C);
    // 0x801DF9B8: mul.s       $f6, $f8, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = MUL_S(ctx->f8.fl, ctx->f4.fl);
    // 0x801DF9BC: add.s       $f10, $f6, $f12
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f10.fl = ctx->f6.fl + ctx->f12.fl;
    // 0x801DF9C0: add.s       $f8, $f18, $f10
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f8.fl = ctx->f18.fl + ctx->f10.fl;
    // 0x801DF9C4: swc1        $f8, 0xC($t8)
    MEM_W(0XC, ctx->r24) = ctx->f8.u32l;
    // 0x801DF9C8: lwc1        $f6, 0x38($v0)
    ctx->f6.u32l = MEM_W(ctx->r2, 0X38);
    // 0x801DF9CC: lwc1        $f4, 0x34($v0)
    ctx->f4.u32l = MEM_W(ctx->r2, 0X34);
    // 0x801DF9D0: lwc1        $f0, 0x3C($v0)
    ctx->f0.u32l = MEM_W(ctx->r2, 0X3C);
    // 0x801DF9D4: mul.s       $f2, $f4, $f6
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f2.fl = MUL_S(ctx->f4.fl, ctx->f6.fl);
    // 0x801DF9D8: c.lt.s      $f2, $f0
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 0);
    c1cs = ctx->f2.fl < ctx->f0.fl;
    // 0x801DF9DC: nop

    // 0x801DF9E0: bc1fl       L_801DF9F4
    if (!c1cs) {
        // 0x801DF9E4: mtc1        $at, $f2
        ctx->f2.u32l = ctx->r1;
            goto L_801DF9F4;
    }
    goto skip_0;
    // 0x801DF9E4: mtc1        $at, $f2
    ctx->f2.u32l = ctx->r1;
    skip_0:
    // 0x801DF9E8: b           L_801DF9F8
    // 0x801DF9EC: div.s       $f2, $f2, $f0
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f2.fl = DIV_S(ctx->f2.fl, ctx->f0.fl);
        goto L_801DF9F8;
    // 0x801DF9EC: div.s       $f2, $f2, $f0
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f2.fl = DIV_S(ctx->f2.fl, ctx->f0.fl);
    // 0x801DF9F0: mtc1        $at, $f2
    ctx->f2.u32l = ctx->r1;
L_801DF9F4:
    // 0x801DF9F4: nop

L_801DF9F8:
    // 0x801DF9F8: lui         $at, 0xC000
    ctx->r1 = S32(0XC000 << 16);
    // 0x801DF9FC: mtc1        $at, $f18
    ctx->f18.u32l = ctx->r1;
    // 0x801DFA00: lui         $at, 0x4040
    ctx->r1 = S32(0X4040 << 16);
    // 0x801DFA04: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x801DFA08: mul.s       $f10, $f18, $f2
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f10.fl = MUL_S(ctx->f18.fl, ctx->f2.fl);
    // 0x801DFA0C: nop

    // 0x801DFA10: mul.s       $f8, $f10, $f2
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f8.fl = MUL_S(ctx->f10.fl, ctx->f2.fl);
    // 0x801DFA14: nop

    // 0x801DFA18: mul.s       $f4, $f8, $f2
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f4.fl = MUL_S(ctx->f8.fl, ctx->f2.fl);
    // 0x801DFA1C: lwc1        $f8, 0x24($v0)
    ctx->f8.u32l = MEM_W(ctx->r2, 0X24);
    // 0x801DFA20: mul.s       $f18, $f6, $f2
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f18.fl = MUL_S(ctx->f6.fl, ctx->f2.fl);
    // 0x801DFA24: nop

    // 0x801DFA28: mul.s       $f10, $f18, $f2
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f10.fl = MUL_S(ctx->f18.fl, ctx->f2.fl);
    // 0x801DFA2C: add.s       $f2, $f4, $f10
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f2.fl = ctx->f4.fl + ctx->f10.fl;
    // 0x801DFA30: lwc1        $f10, 0x40($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0X40);
    // 0x801DFA34: mul.s       $f6, $f8, $f2
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f6.fl = MUL_S(ctx->f8.fl, ctx->f2.fl);
    // 0x801DFA38: swc1        $f6, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->f6.u32l;
    // 0x801DFA3C: lwc1        $f18, 0x28($v0)
    ctx->f18.u32l = MEM_W(ctx->r2, 0X28);
    // 0x801DFA40: lwc1        $f8, 0x38($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X38);
    // 0x801DFA44: swc1        $f10, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->f10.u32l;
    // 0x801DFA48: mul.s       $f4, $f18, $f2
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f4.fl = MUL_S(ctx->f18.fl, ctx->f2.fl);
    // 0x801DFA4C: lwc1        $f18, 0x44($sp)
    ctx->f18.u32l = MEM_W(ctx->r29, 0X44);
    // 0x801DFA50: swc1        $f8, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->f8.u32l;
    // 0x801DFA54: mul.s       $f6, $f10, $f8
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f6.fl = MUL_S(ctx->f10.fl, ctx->f8.fl);
    // 0x801DFA58: lwc1        $f8, 0x20($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X20);
    // 0x801DFA5C: swc1        $f4, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->f4.u32l;
    // 0x801DFA60: lwc1        $f4, 0x3C($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X3C);
    // 0x801DFA64: mul.s       $f10, $f18, $f4
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f10.fl = MUL_S(ctx->f18.fl, ctx->f4.fl);
    // 0x801DFA68: swc1        $f4, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->f4.u32l;
    // 0x801DFA6C: add.s       $f6, $f6, $f10
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f6.fl = ctx->f6.fl + ctx->f10.fl;
    // 0x801DFA70: neg.s       $f10, $f6
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f6.fl); 
    ctx->f10.fl = -ctx->f6.fl;
    // 0x801DFA74: mul.s       $f6, $f18, $f18
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f6.fl = MUL_S(ctx->f18.fl, ctx->f18.fl);
    // 0x801DFA78: nop

    // 0x801DFA7C: mul.s       $f4, $f8, $f8
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f4.fl = MUL_S(ctx->f8.fl, ctx->f8.fl);
    // 0x801DFA80: add.s       $f6, $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = ctx->f6.fl + ctx->f4.fl;
    // 0x801DFA84: div.s       $f0, $f10, $f6
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f0.fl = DIV_S(ctx->f10.fl, ctx->f6.fl);
    // 0x801DFA88: lwc1        $f10, 0x24($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0X24);
    // 0x801DFA8C: mul.s       $f4, $f8, $f0
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f4.fl = MUL_S(ctx->f8.fl, ctx->f0.fl);
    // 0x801DFA90: lwc1        $f8, 0x2C($v0)
    ctx->f8.u32l = MEM_W(ctx->r2, 0X2C);
    // 0x801DFA94: add.s       $f6, $f4, $f10
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f6.fl = ctx->f4.fl + ctx->f10.fl;
    // 0x801DFA98: mul.s       $f4, $f6, $f8
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f4.fl = MUL_S(ctx->f6.fl, ctx->f8.fl);
    // 0x801DFA9C: lwc1        $f6, 0x20($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X20);
    // 0x801DFAA0: mul.s       $f10, $f18, $f0
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f10.fl = MUL_S(ctx->f18.fl, ctx->f0.fl);
    // 0x801DFAA4: swc1        $f4, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->f4.u32l;
    // 0x801DFAA8: lwc1        $f18, 0x2C($v0)
    ctx->f18.u32l = MEM_W(ctx->r2, 0X2C);
    // 0x801DFAAC: sw          $t0, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r8;
    // 0x801DFAB0: add.s       $f8, $f10, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = ctx->f10.fl + ctx->f6.fl;
    // 0x801DFAB4: sw          $v0, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r2;
    // 0x801DFAB8: mul.s       $f10, $f8, $f18
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f10.fl = MUL_S(ctx->f8.fl, ctx->f18.fl);
    // 0x801DFABC: nop

    // 0x801DFAC0: mul.s       $f6, $f10, $f10
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f6.fl = MUL_S(ctx->f10.fl, ctx->f10.fl);
    // 0x801DFAC4: swc1        $f10, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->f10.u32l;
    // 0x801DFAC8: mul.s       $f8, $f4, $f4
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f8.fl = MUL_S(ctx->f4.fl, ctx->f4.fl);
    // 0x801DFACC: jal         0x800C7010
    // 0x801DFAD0: add.s       $f12, $f6, $f8
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f12.fl = ctx->f6.fl + ctx->f8.fl;
    _nsqrtf(rdram, ctx);
        goto after_2;
    // 0x801DFAD0: add.s       $f12, $f6, $f8
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f12.fl = ctx->f6.fl + ctx->f8.fl;
    after_2:
    // 0x801DFAD4: lw          $v0, 0x28($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X28);
    // 0x801DFAD8: lw          $t0, 0x2C($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X2C);
    // 0x801DFADC: lwc1        $f12, 0x30($v0)
    ctx->f12.u32l = MEM_W(ctx->r2, 0X30);
    // 0x801DFAE0: c.lt.s      $f12, $f0
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 0);
    c1cs = ctx->f12.fl < ctx->f0.fl;
    // 0x801DFAE4: nop

    // 0x801DFAE8: bc1fl       L_801DFB14
    if (!c1cs) {
        // 0x801DFAEC: lw          $a1, 0x74($v0)
        ctx->r5 = MEM_W(ctx->r2, 0X74);
            goto L_801DFB14;
    }
    goto skip_1;
    // 0x801DFAEC: lw          $a1, 0x74($v0)
    ctx->r5 = MEM_W(ctx->r2, 0X74);
    skip_1:
    // 0x801DFAF0: div.s       $f2, $f12, $f0
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f2.fl = DIV_S(ctx->f12.fl, ctx->f0.fl);
    // 0x801DFAF4: lwc1        $f18, 0x40($sp)
    ctx->f18.u32l = MEM_W(ctx->r29, 0X40);
    // 0x801DFAF8: lwc1        $f4, 0x44($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X44);
    // 0x801DFAFC: mul.s       $f10, $f18, $f2
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f10.fl = MUL_S(ctx->f18.fl, ctx->f2.fl);
    // 0x801DFB00: nop

    // 0x801DFB04: mul.s       $f6, $f4, $f2
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f6.fl = MUL_S(ctx->f4.fl, ctx->f2.fl);
    // 0x801DFB08: swc1        $f10, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->f10.u32l;
    // 0x801DFB0C: swc1        $f6, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->f6.u32l;
    // 0x801DFB10: lw          $a1, 0x74($v0)
    ctx->r5 = MEM_W(ctx->r2, 0X74);
L_801DFB14:
    // 0x801DFB14: lwc1        $f8, 0x40($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X40);
    // 0x801DFB18: sll         $t9, $a1, 2
    ctx->r25 = S32(ctx->r5 << 2);
    // 0x801DFB1C: addu        $t1, $v0, $t9
    ctx->r9 = ADD32(ctx->r2, ctx->r25);
    // 0x801DFB20: lwc1        $f18, 0x0($t1)
    ctx->f18.u32l = MEM_W(ctx->r9, 0X0);
    // 0x801DFB24: addu        $t2, $t0, $t9
    ctx->r10 = ADD32(ctx->r8, ctx->r25);
    // 0x801DFB28: add.s       $f10, $f8, $f18
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f10.fl = ctx->f8.fl + ctx->f18.fl;
    // 0x801DFB2C: swc1        $f10, 0x0($t2)
    MEM_W(0X0, ctx->r10) = ctx->f10.u32l;
    // 0x801DFB30: lw          $a2, 0x78($v0)
    ctx->r6 = MEM_W(ctx->r2, 0X78);
    // 0x801DFB34: lwc1        $f4, 0x44($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X44);
    // 0x801DFB38: sll         $t3, $a2, 2
    ctx->r11 = S32(ctx->r6 << 2);
    // 0x801DFB3C: addu        $t4, $v0, $t3
    ctx->r12 = ADD32(ctx->r2, ctx->r11);
    // 0x801DFB40: lwc1        $f6, 0x0($t4)
    ctx->f6.u32l = MEM_W(ctx->r12, 0X0);
    // 0x801DFB44: addu        $t5, $t0, $t3
    ctx->r13 = ADD32(ctx->r8, ctx->r11);
    // 0x801DFB48: add.s       $f8, $f4, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = ctx->f4.fl + ctx->f6.fl;
    // 0x801DFB4C: swc1        $f8, 0x0($t5)
    MEM_W(0X0, ctx->r13) = ctx->f8.u32l;
    // 0x801DFB50: lw          $t6, 0x80($v0)
    ctx->r14 = MEM_W(ctx->r2, 0X80);
    // 0x801DFB54: lwc1        $f18, 0x40($sp)
    ctx->f18.u32l = MEM_W(ctx->r29, 0X40);
    // 0x801DFB58: beql        $t6, $zero, L_801DFB8C
    if (ctx->r14 == 0) {
        // 0x801DFB5C: mtc1        $zero, $f0
        ctx->f0.u32l = 0;
            goto L_801DFB8C;
    }
    goto skip_2;
    // 0x801DFB5C: mtc1        $zero, $f0
    ctx->f0.u32l = 0;
    skip_2:
    // 0x801DFB60: lwc1        $f10, 0x70($v0)
    ctx->f10.u32l = MEM_W(ctx->r2, 0X70);
    // 0x801DFB64: mul.s       $f4, $f18, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f4.fl = MUL_S(ctx->f18.fl, ctx->f10.fl);
    // 0x801DFB68: swc1        $f4, 0x28($s0)
    MEM_W(0X28, ctx->r16) = ctx->f4.u32l;
    // 0x801DFB6C: lwc1        $f6, 0x30($v0)
    ctx->f6.u32l = MEM_W(ctx->r2, 0X30);
    // 0x801DFB70: swc1        $f6, 0x2C($s0)
    MEM_W(0X2C, ctx->r16) = ctx->f6.u32l;
    // 0x801DFB74: lwc1        $f18, 0x70($v0)
    ctx->f18.u32l = MEM_W(ctx->r2, 0X70);
    // 0x801DFB78: lwc1        $f8, 0x44($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X44);
    // 0x801DFB7C: mul.s       $f10, $f8, $f18
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f10.fl = MUL_S(ctx->f8.fl, ctx->f18.fl);
    // 0x801DFB80: b           L_801DFBA0
    // 0x801DFB84: swc1        $f10, 0x30($s0)
    MEM_W(0X30, ctx->r16) = ctx->f10.u32l;
        goto L_801DFBA0;
    // 0x801DFB84: swc1        $f10, 0x30($s0)
    MEM_W(0X30, ctx->r16) = ctx->f10.u32l;
    // 0x801DFB88: mtc1        $zero, $f0
    ctx->f0.u32l = 0;
L_801DFB8C:
    // 0x801DFB8C: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x801DFB90: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x801DFB94: swc1        $f0, 0x28($s0)
    MEM_W(0X28, ctx->r16) = ctx->f0.u32l;
    // 0x801DFB98: swc1        $f0, 0x30($s0)
    MEM_W(0X30, ctx->r16) = ctx->f0.u32l;
    // 0x801DFB9C: swc1        $f4, 0x2C($s0)
    MEM_W(0X2C, ctx->r16) = ctx->f4.u32l;
L_801DFBA0:
    // 0x801DFBA0: lw          $a3, 0x7C($v0)
    ctx->r7 = MEM_W(ctx->r2, 0X7C);
    // 0x801DFBA4: lwc1        $f12, 0x10($v0)
    ctx->f12.u32l = MEM_W(ctx->r2, 0X10);
    // 0x801DFBA8: sll         $t7, $a3, 2
    ctx->r15 = S32(ctx->r7 << 2);
    // 0x801DFBAC: addu        $t8, $v0, $t7
    ctx->r24 = ADD32(ctx->r2, ctx->r15);
    // 0x801DFBB0: lwc1        $f14, 0x0($t8)
    ctx->f14.u32l = MEM_W(ctx->r24, 0X0);
    // 0x801DFBB4: or          $a3, $t7, $zero
    ctx->r7 = ctx->r15 | 0;
    // 0x801DFBB8: c.le.s      $f14, $f12
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 12);
    c1cs = ctx->f14.fl <= ctx->f12.fl;
    // 0x801DFBBC: nop

    // 0x801DFBC0: bc1fl       L_801DFBD4
    if (!c1cs) {
        // 0x801DFBC4: lwc1        $f16, 0x14($v0)
        ctx->f16.u32l = MEM_W(ctx->r2, 0X14);
            goto L_801DFBD4;
    }
    goto skip_3;
    // 0x801DFBC4: lwc1        $f16, 0x14($v0)
    ctx->f16.u32l = MEM_W(ctx->r2, 0X14);
    skip_3:
    // 0x801DFBC8: b           L_801DFC14
    // 0x801DFBCC: lwc1        $f2, 0x40($v0)
    ctx->f2.u32l = MEM_W(ctx->r2, 0X40);
        goto L_801DFC14;
    // 0x801DFBCC: lwc1        $f2, 0x40($v0)
    ctx->f2.u32l = MEM_W(ctx->r2, 0X40);
    // 0x801DFBD0: lwc1        $f16, 0x14($v0)
    ctx->f16.u32l = MEM_W(ctx->r2, 0X14);
L_801DFBD4:
    // 0x801DFBD4: c.le.s      $f16, $f14
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 14);
    c1cs = ctx->f16.fl <= ctx->f14.fl;
    // 0x801DFBD8: nop

    // 0x801DFBDC: bc1fl       L_801DFBF0
    if (!c1cs) {
        // 0x801DFBE0: sub.s       $f6, $f14, $f12
        CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f6.fl = ctx->f14.fl - ctx->f12.fl;
            goto L_801DFBF0;
    }
    goto skip_4;
    // 0x801DFBE0: sub.s       $f6, $f14, $f12
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f6.fl = ctx->f14.fl - ctx->f12.fl;
    skip_4:
    // 0x801DFBE4: b           L_801DFC14
    // 0x801DFBE8: lwc1        $f2, 0x44($v0)
    ctx->f2.u32l = MEM_W(ctx->r2, 0X44);
        goto L_801DFC14;
    // 0x801DFBE8: lwc1        $f2, 0x44($v0)
    ctx->f2.u32l = MEM_W(ctx->r2, 0X44);
    // 0x801DFBEC: sub.s       $f6, $f14, $f12
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f6.fl = ctx->f14.fl - ctx->f12.fl;
L_801DFBF0:
    // 0x801DFBF0: lwc1        $f0, 0x40($v0)
    ctx->f0.u32l = MEM_W(ctx->r2, 0X40);
    // 0x801DFBF4: lwc1        $f10, 0x44($v0)
    ctx->f10.u32l = MEM_W(ctx->r2, 0X44);
    // 0x801DFBF8: sub.s       $f8, $f16, $f12
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f8.fl = ctx->f16.fl - ctx->f12.fl;
    // 0x801DFBFC: sub.s       $f4, $f10, $f0
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f4.fl = ctx->f10.fl - ctx->f0.fl;
    // 0x801DFC00: div.s       $f2, $f6, $f8
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f2.fl = DIV_S(ctx->f6.fl, ctx->f8.fl);
    // 0x801DFC04: mul.s       $f18, $f2, $f2
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f18.fl = MUL_S(ctx->f2.fl, ctx->f2.fl);
    // 0x801DFC08: nop

    // 0x801DFC0C: mul.s       $f6, $f18, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = MUL_S(ctx->f18.fl, ctx->f4.fl);
    // 0x801DFC10: add.s       $f2, $f6, $f0
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f2.fl = ctx->f6.fl + ctx->f0.fl;
L_801DFC14:
    // 0x801DFC14: lwc1        $f12, 0xC($v0)
    ctx->f12.u32l = MEM_W(ctx->r2, 0XC);
    // 0x801DFC18: addu        $t9, $t0, $a3
    ctx->r25 = ADD32(ctx->r8, ctx->r7);
    // 0x801DFC1C: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x801DFC20: sub.s       $f8, $f14, $f12
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f8.fl = ctx->f14.fl - ctx->f12.fl;
    // 0x801DFC24: mul.s       $f10, $f8, $f2
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f10.fl = MUL_S(ctx->f8.fl, ctx->f2.fl);
    // 0x801DFC28: add.s       $f18, $f10, $f12
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f18.fl = ctx->f10.fl + ctx->f12.fl;
    // 0x801DFC2C: jal         0x801DEEC4
    // 0x801DFC30: swc1        $f18, 0x0($t9)
    MEM_W(0X0, ctx->r25) = ctx->f18.u32l;
    func_801DEEC4(rdram, ctx);
        goto after_3;
    // 0x801DFC30: swc1        $f18, 0x0($t9)
    MEM_W(0X0, ctx->r25) = ctx->f18.u32l;
    after_3:
    // 0x801DFC34: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    // 0x801DFC38: lw          $s0, 0x18($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X18);
    // 0x801DFC3C: addiu       $sp, $sp, 0x50
    ctx->r29 = ADD32(ctx->r29, 0X50);
    // 0x801DFC40: jr          $ra
    // 0x801DFC44: nop

    return;
    // 0x801DFC44: nop

;}
RECOMP_FUNC void func_801DFC48(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801DFC48: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x801DFC4C: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x801DFC50: lw          $v0, 0x0($a0)
    ctx->r2 = MEM_W(ctx->r4, 0X0);
    // 0x801DFC54: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x801DFC58: beq         $v0, $at, L_801DFC80
    if (ctx->r2 == ctx->r1) {
        // 0x801DFC5C: addiu       $at, $zero, 0x2
        ctx->r1 = ADD32(0, 0X2);
            goto L_801DFC80;
    }
    // 0x801DFC5C: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x801DFC60: beq         $v0, $at, L_801DFC90
    if (ctx->r2 == ctx->r1) {
        // 0x801DFC64: addiu       $at, $zero, 0x3
        ctx->r1 = ADD32(0, 0X3);
            goto L_801DFC90;
    }
    // 0x801DFC64: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x801DFC68: beq         $v0, $at, L_801DFC90
    if (ctx->r2 == ctx->r1) {
        // 0x801DFC6C: addiu       $at, $zero, 0x5
        ctx->r1 = ADD32(0, 0X5);
            goto L_801DFC90;
    }
    // 0x801DFC6C: addiu       $at, $zero, 0x5
    ctx->r1 = ADD32(0, 0X5);
    // 0x801DFC70: beq         $v0, $at, L_801DFCA0
    if (ctx->r2 == ctx->r1) {
        // 0x801DFC74: nop
    
            goto L_801DFCA0;
    }
    // 0x801DFC74: nop

    // 0x801DFC78: b           L_801DFCAC
    // 0x801DFC7C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_801DFCAC;
    // 0x801DFC7C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_801DFC80:
    // 0x801DFC80: jal         0x801DF128
    // 0x801DFC84: nop

    func_801DF128(rdram, ctx);
        goto after_0;
    // 0x801DFC84: nop

    after_0:
    // 0x801DFC88: b           L_801DFCAC
    // 0x801DFC8C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_801DFCAC;
    // 0x801DFC8C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_801DFC90:
    // 0x801DFC90: jal         0x801DF38C
    // 0x801DFC94: nop

    func_801DF38C(rdram, ctx);
        goto after_1;
    // 0x801DFC94: nop

    after_1:
    // 0x801DFC98: b           L_801DFCAC
    // 0x801DFC9C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_801DFCAC;
    // 0x801DFC9C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_801DFCA0:
    // 0x801DFCA0: jal         0x801DF744
    // 0x801DFCA4: nop

    func_801DF744(rdram, ctx);
        goto after_2;
    // 0x801DFCA4: nop

    after_2:
    // 0x801DFCA8: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_801DFCAC:
    // 0x801DFCAC: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x801DFCB0: jr          $ra
    // 0x801DFCB4: nop

    return;
    // 0x801DFCB4: nop

;}
RECOMP_FUNC void func_801DFCB8(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801DFCB8: addiu       $sp, $sp, -0x28
    ctx->r29 = ADD32(ctx->r29, -0X28);
    // 0x801DFCBC: sw          $s3, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r19;
    // 0x801DFCC0: sw          $s2, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r18;
    // 0x801DFCC4: sw          $s1, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r17;
    // 0x801DFCC8: or          $s1, $a0, $zero
    ctx->r17 = ctx->r4 | 0;
    // 0x801DFCCC: sw          $ra, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r31;
    // 0x801DFCD0: sw          $s0, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r16;
    // 0x801DFCD4: addiu       $s2, $zero, -0x2
    ctx->r18 = ADD32(0, -0X2);
    // 0x801DFCD8: addiu       $s3, $zero, -0x1
    ctx->r19 = ADD32(0, -0X1);
L_801DFCDC:
    // 0x801DFCDC: lw          $s0, 0x4($s1)
    ctx->r16 = MEM_W(ctx->r17, 0X4);
    // 0x801DFCE0: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    // 0x801DFCE4: beql        $s0, $zero, L_801DFD74
    if (ctx->r16 == 0) {
        // 0x801DFCE8: lw          $ra, 0x24($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X24);
            goto L_801DFD74;
    }
    goto skip_0;
    // 0x801DFCE8: lw          $ra, 0x24($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X24);
    skip_0:
    // 0x801DFCEC: lw          $v0, 0x4($s0)
    ctx->r2 = MEM_W(ctx->r16, 0X4);
    // 0x801DFCF0: beql        $v0, $zero, L_801DFD04
    if (ctx->r2 == 0) {
        // 0x801DFCF4: lw          $v0, 0x0($s0)
        ctx->r2 = MEM_W(ctx->r16, 0X0);
            goto L_801DFD04;
    }
    goto skip_1;
    // 0x801DFCF4: lw          $v0, 0x0($s0)
    ctx->r2 = MEM_W(ctx->r16, 0X0);
    skip_1:
    // 0x801DFCF8: jalr        $v0
    // 0x801DFCFC: lw          $a1, 0x8($s0)
    ctx->r5 = MEM_W(ctx->r16, 0X8);
    LOOKUP_FUNC(ctx->r2)(rdram, ctx);
        goto after_0;
    // 0x801DFCFC: lw          $a1, 0x8($s0)
    ctx->r5 = MEM_W(ctx->r16, 0X8);
    after_0:
    // 0x801DFD00: lw          $v0, 0x0($s0)
    ctx->r2 = MEM_W(ctx->r16, 0X0);
L_801DFD04:
    // 0x801DFD04: beql        $v0, $s2, L_801DFD3C
    if (ctx->r2 == ctx->r18) {
        // 0x801DFD08: lw          $t8, 0x8($s1)
        ctx->r24 = MEM_W(ctx->r17, 0X8);
            goto L_801DFD3C;
    }
    goto skip_2;
    // 0x801DFD08: lw          $t8, 0x8($s1)
    ctx->r24 = MEM_W(ctx->r17, 0X8);
    skip_2:
    // 0x801DFD0C: beql        $v0, $s3, L_801DFD30
    if (ctx->r2 == ctx->r19) {
        // 0x801DFD10: or          $s0, $zero, $zero
        ctx->r16 = 0 | 0;
            goto L_801DFD30;
    }
    goto skip_3;
    // 0x801DFD10: or          $s0, $zero, $zero
    ctx->r16 = 0 | 0;
    skip_3:
    // 0x801DFD14: bnel        $v0, $zero, L_801DFD4C
    if (ctx->r2 != 0) {
        // 0x801DFD18: lw          $t0, 0x8($s1)
        ctx->r8 = MEM_W(ctx->r17, 0X8);
            goto L_801DFD4C;
    }
    goto skip_4;
    // 0x801DFD18: lw          $t0, 0x8($s1)
    ctx->r8 = MEM_W(ctx->r17, 0X8);
    skip_4:
    // 0x801DFD1C: lw          $t6, 0x4($s1)
    ctx->r14 = MEM_W(ctx->r17, 0X4);
    // 0x801DFD20: addiu       $t7, $t6, 0xC
    ctx->r15 = ADD32(ctx->r14, 0XC);
    // 0x801DFD24: b           L_801DFCDC
    // 0x801DFD28: sw          $t7, 0x4($s1)
    MEM_W(0X4, ctx->r17) = ctx->r15;
        goto L_801DFCDC;
    // 0x801DFD28: sw          $t7, 0x4($s1)
    MEM_W(0X4, ctx->r17) = ctx->r15;
    // 0x801DFD2C: or          $s0, $zero, $zero
    ctx->r16 = 0 | 0;
L_801DFD30:
    // 0x801DFD30: b           L_801DFD6C
    // 0x801DFD34: sw          $zero, 0x8($s1)
    MEM_W(0X8, ctx->r17) = 0;
        goto L_801DFD6C;
    // 0x801DFD34: sw          $zero, 0x8($s1)
    MEM_W(0X8, ctx->r17) = 0;
    // 0x801DFD38: lw          $t8, 0x8($s1)
    ctx->r24 = MEM_W(ctx->r17, 0X8);
L_801DFD3C:
    // 0x801DFD3C: addiu       $t9, $t8, 0x1
    ctx->r25 = ADD32(ctx->r24, 0X1);
    // 0x801DFD40: b           L_801DFD6C
    // 0x801DFD44: sw          $t9, 0x8($s1)
    MEM_W(0X8, ctx->r17) = ctx->r25;
        goto L_801DFD6C;
    // 0x801DFD44: sw          $t9, 0x8($s1)
    MEM_W(0X8, ctx->r17) = ctx->r25;
    // 0x801DFD48: lw          $t0, 0x8($s1)
    ctx->r8 = MEM_W(ctx->r17, 0X8);
L_801DFD4C:
    // 0x801DFD4C: addiu       $t1, $t0, 0x1
    ctx->r9 = ADD32(ctx->r8, 0X1);
    // 0x801DFD50: sw          $t1, 0x8($s1)
    MEM_W(0X8, ctx->r17) = ctx->r9;
    // 0x801DFD54: lw          $t3, 0x0($s0)
    ctx->r11 = MEM_W(ctx->r16, 0X0);
    // 0x801DFD58: slt         $at, $t1, $t3
    ctx->r1 = SIGNED(ctx->r9) < SIGNED(ctx->r11) ? 1 : 0;
    // 0x801DFD5C: bnel        $at, $zero, L_801DFD70
    if (ctx->r1 != 0) {
        // 0x801DFD60: sw          $s0, 0x4($s1)
        MEM_W(0X4, ctx->r17) = ctx->r16;
            goto L_801DFD70;
    }
    goto skip_5;
    // 0x801DFD60: sw          $s0, 0x4($s1)
    MEM_W(0X4, ctx->r17) = ctx->r16;
    skip_5:
    // 0x801DFD64: addiu       $s0, $s0, 0xC
    ctx->r16 = ADD32(ctx->r16, 0XC);
    // 0x801DFD68: sw          $zero, 0x8($s1)
    MEM_W(0X8, ctx->r17) = 0;
L_801DFD6C:
    // 0x801DFD6C: sw          $s0, 0x4($s1)
    MEM_W(0X4, ctx->r17) = ctx->r16;
L_801DFD70:
    // 0x801DFD70: lw          $ra, 0x24($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X24);
L_801DFD74:
    // 0x801DFD74: lw          $s0, 0x14($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X14);
    // 0x801DFD78: lw          $s1, 0x18($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X18);
    // 0x801DFD7C: lw          $s2, 0x1C($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X1C);
    // 0x801DFD80: lw          $s3, 0x20($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X20);
    // 0x801DFD84: jr          $ra
    // 0x801DFD88: addiu       $sp, $sp, 0x28
    ctx->r29 = ADD32(ctx->r29, 0X28);
    return;
    // 0x801DFD88: addiu       $sp, $sp, 0x28
    ctx->r29 = ADD32(ctx->r29, 0X28);
;}
RECOMP_FUNC void func_801DFD8C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801DFD8C: jr          $ra
    // 0x801DFD90: sw          $a1, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r5;
    return;
    // 0x801DFD90: sw          $a1, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r5;
;}
RECOMP_FUNC void func_801DFD94(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801DFD94: sw          $a1, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r5;
    // 0x801DFD98: jr          $ra
    // 0x801DFD9C: sw          $zero, 0x8($a0)
    MEM_W(0X8, ctx->r4) = 0;
    return;
    // 0x801DFD9C: sw          $zero, 0x8($a0)
    MEM_W(0X8, ctx->r4) = 0;
;}
RECOMP_FUNC void func_801DFDA0(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801DFDA0: jr          $ra
    // 0x801DFDA4: sw          $a1, 0xC($a0)
    MEM_W(0XC, ctx->r4) = ctx->r5;
    return;
    // 0x801DFDA4: sw          $a1, 0xC($a0)
    MEM_W(0XC, ctx->r4) = ctx->r5;
;}
