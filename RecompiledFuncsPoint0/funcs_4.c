#include "recomp.h"
#include "funcs.h"

RECOMP_FUNC void func_8007B110(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8007B110: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x8007B114: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x8007B118: sw          $s1, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r17;
    // 0x8007B11C: sw          $s0, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r16;
    // 0x8007B120: lbu         $t0, 0x0($a0)
    ctx->r8 = MEM_BU(ctx->r4, 0X0);
    // 0x8007B124: lbu         $a2, 0x1($a0)
    ctx->r6 = MEM_BU(ctx->r4, 0X1);
    // 0x8007B128: lbu         $a3, 0x2($a0)
    ctx->r7 = MEM_BU(ctx->r4, 0X2);
    // 0x8007B12C: andi        $t6, $t0, 0x1F
    ctx->r14 = ctx->r8 & 0X1F;
    // 0x8007B130: sll         $t7, $t6, 16
    ctx->r15 = S32(ctx->r14 << 16);
    // 0x8007B134: sll         $t8, $a2, 8
    ctx->r24 = S32(ctx->r6 << 8);
    // 0x8007B138: addu        $t9, $t7, $t8
    ctx->r25 = ADD32(ctx->r15, ctx->r24);
    // 0x8007B13C: addu        $v1, $t9, $a3
    ctx->r3 = ADD32(ctx->r25, ctx->r7);
    // 0x8007B140: or          $s0, $a0, $zero
    ctx->r16 = ctx->r4 | 0;
    // 0x8007B144: bgez        $v1, L_8007B150
    if (SIGNED(ctx->r3) >= 0) {
        // 0x8007B148: or          $s1, $a1, $zero
        ctx->r17 = ctx->r5 | 0;
            goto L_8007B150;
    }
    // 0x8007B148: or          $s1, $a1, $zero
    ctx->r17 = ctx->r5 | 0;
    // 0x8007B14C: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
L_8007B150:
    // 0x8007B150: lui         $at, 0x9
    ctx->r1 = S32(0X9 << 16);
    // 0x8007B154: ori         $at, $at, 0x27C0
    ctx->r1 = ctx->r1 | 0X27C0;
    // 0x8007B158: slt         $at, $v1, $at
    ctx->r1 = SIGNED(ctx->r3) < SIGNED(ctx->r1) ? 1 : 0;
    // 0x8007B15C: bne         $at, $zero, L_8007B16C
    if (ctx->r1 != 0) {
        // 0x8007B160: srl         $t1, $t0, 5
        ctx->r9 = S32(U32(ctx->r8) >> 5);
            goto L_8007B16C;
    }
    // 0x8007B160: srl         $t1, $t0, 5
    ctx->r9 = S32(U32(ctx->r8) >> 5);
    // 0x8007B164: lui         $v1, 0x9
    ctx->r3 = S32(0X9 << 16);
    // 0x8007B168: ori         $v1, $v1, 0x27BF
    ctx->r3 = ctx->r3 | 0X27BF;
L_8007B16C:
    // 0x8007B16C: andi        $t2, $t1, 0x7
    ctx->r10 = ctx->r9 & 0X7;
    // 0x8007B170: sw          $v1, 0x0($s1)
    MEM_W(0X0, ctx->r17) = ctx->r3;
    // 0x8007B174: sw          $t2, 0x4($s1)
    MEM_W(0X4, ctx->r17) = ctx->r10;
    // 0x8007B178: addiu       $a0, $s1, 0x10
    ctx->r4 = ADD32(ctx->r17, 0X10);
    // 0x8007B17C: jal         0x8007AEFC
    // 0x8007B180: addiu       $a1, $s0, 0x3
    ctx->r5 = ADD32(ctx->r16, 0X3);
    func_8007AEFC(rdram, ctx);
        goto after_0;
    // 0x8007B180: addiu       $a1, $s0, 0x3
    ctx->r5 = ADD32(ctx->r16, 0X3);
    after_0:
    // 0x8007B184: sb          $zero, 0x13($s1)
    MEM_B(0X13, ctx->r17) = 0;
    // 0x8007B188: lbu         $t3, 0x3($s0)
    ctx->r11 = MEM_BU(ctx->r16, 0X3);
    // 0x8007B18C: sra         $t4, $t3, 7
    ctx->r12 = S32(SIGNED(ctx->r11) >> 7);
    // 0x8007B190: andi        $t5, $t4, 0x1
    ctx->r13 = ctx->r12 & 0X1;
    // 0x8007B194: sw          $t5, 0x8($s1)
    MEM_W(0X8, ctx->r17) = ctx->r13;
    // 0x8007B198: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    // 0x8007B19C: lw          $s1, 0x18($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X18);
    // 0x8007B1A0: lw          $s0, 0x14($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X14);
    // 0x8007B1A4: jr          $ra
    // 0x8007B1A8: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    return;
    // 0x8007B1A8: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
;}
RECOMP_FUNC void func_8007B1AC(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8007B1AC: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x8007B1B0: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x8007B1B4: lw          $t3, 0x0($a0)
    ctx->r11 = MEM_W(ctx->r4, 0X0);
    // 0x8007B1B8: lbu         $t8, 0x7($a0)
    ctx->r24 = MEM_BU(ctx->r4, 0X7);
    // 0x8007B1BC: or          $a3, $a0, $zero
    ctx->r7 = ctx->r4 | 0;
    // 0x8007B1C0: sra         $t7, $t3, 16
    ctx->r15 = S32(SIGNED(ctx->r11) >> 16);
    // 0x8007B1C4: sll         $t9, $t8, 5
    ctx->r25 = S32(ctx->r24 << 5);
    // 0x8007B1C8: addu        $t0, $t7, $t9
    ctx->r8 = ADD32(ctx->r15, ctx->r25);
    // 0x8007B1CC: sra         $t2, $t3, 8
    ctx->r10 = S32(SIGNED(ctx->r11) >> 8);
    // 0x8007B1D0: sb          $t0, 0x0($a1)
    MEM_B(0X0, ctx->r5) = ctx->r8;
    // 0x8007B1D4: sb          $t2, 0x1($a1)
    MEM_B(0X1, ctx->r5) = ctx->r10;
    // 0x8007B1D8: sb          $t3, 0x2($a1)
    MEM_B(0X2, ctx->r5) = ctx->r11;
    // 0x8007B1DC: or          $a2, $a1, $zero
    ctx->r6 = ctx->r5 | 0;
    // 0x8007B1E0: addiu       $a0, $a1, 0x3
    ctx->r4 = ADD32(ctx->r5, 0X3);
    // 0x8007B1E4: addiu       $a1, $a3, 0xC
    ctx->r5 = ADD32(ctx->r7, 0XC);
    // 0x8007B1E8: sw          $a2, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r6;
    // 0x8007B1EC: jal         0x8007AE8C
    // 0x8007B1F0: sw          $a3, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r7;
    func_8007AE8C(rdram, ctx);
        goto after_0;
    // 0x8007B1F0: sw          $a3, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r7;
    after_0:
    // 0x8007B1F4: lw          $a3, 0x18($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X18);
    // 0x8007B1F8: lw          $a2, 0x1C($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X1C);
    // 0x8007B1FC: lbu         $t5, 0xB($a3)
    ctx->r13 = MEM_BU(ctx->r7, 0XB);
    // 0x8007B200: lbu         $t4, 0x3($a2)
    ctx->r12 = MEM_BU(ctx->r6, 0X3);
    // 0x8007B204: sll         $t6, $t5, 7
    ctx->r14 = S32(ctx->r13 << 7);
    // 0x8007B208: xor         $t8, $t4, $t6
    ctx->r24 = ctx->r12 ^ ctx->r14;
    // 0x8007B20C: sb          $t8, 0x3($a2)
    MEM_B(0X3, ctx->r6) = ctx->r24;
    // 0x8007B210: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x8007B214: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x8007B218: jr          $ra
    // 0x8007B21C: nop

    return;
    // 0x8007B21C: nop

;}
RECOMP_FUNC void func_8007B220(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8007B220: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x8007B224: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x8007B228: sw          $s1, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r17;
    // 0x8007B22C: sw          $s0, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r16;
    // 0x8007B230: lbu         $t0, 0x0($a0)
    ctx->r8 = MEM_BU(ctx->r4, 0X0);
    // 0x8007B234: lbu         $a2, 0x1($a0)
    ctx->r6 = MEM_BU(ctx->r4, 0X1);
    // 0x8007B238: lbu         $a3, 0x2($a0)
    ctx->r7 = MEM_BU(ctx->r4, 0X2);
    // 0x8007B23C: andi        $t6, $t0, 0x1F
    ctx->r14 = ctx->r8 & 0X1F;
    // 0x8007B240: sll         $t7, $t6, 16
    ctx->r15 = S32(ctx->r14 << 16);
    // 0x8007B244: sll         $t8, $a2, 8
    ctx->r24 = S32(ctx->r6 << 8);
    // 0x8007B248: addu        $t9, $t7, $t8
    ctx->r25 = ADD32(ctx->r15, ctx->r24);
    // 0x8007B24C: addu        $v1, $t9, $a3
    ctx->r3 = ADD32(ctx->r25, ctx->r7);
    // 0x8007B250: or          $s0, $a0, $zero
    ctx->r16 = ctx->r4 | 0;
    // 0x8007B254: bgez        $v1, L_8007B260
    if (SIGNED(ctx->r3) >= 0) {
        // 0x8007B258: or          $s1, $a1, $zero
        ctx->r17 = ctx->r5 | 0;
            goto L_8007B260;
    }
    // 0x8007B258: or          $s1, $a1, $zero
    ctx->r17 = ctx->r5 | 0;
    // 0x8007B25C: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
L_8007B260:
    // 0x8007B260: lui         $at, 0x1
    ctx->r1 = S32(0X1 << 16);
    // 0x8007B264: ori         $at, $at, 0x86A0
    ctx->r1 = ctx->r1 | 0X86A0;
    // 0x8007B268: slt         $at, $v1, $at
    ctx->r1 = SIGNED(ctx->r3) < SIGNED(ctx->r1) ? 1 : 0;
    // 0x8007B26C: bne         $at, $zero, L_8007B27C
    if (ctx->r1 != 0) {
        // 0x8007B270: srl         $t1, $t0, 5
        ctx->r9 = S32(U32(ctx->r8) >> 5);
            goto L_8007B27C;
    }
    // 0x8007B270: srl         $t1, $t0, 5
    ctx->r9 = S32(U32(ctx->r8) >> 5);
    // 0x8007B274: lui         $v1, 0x1
    ctx->r3 = S32(0X1 << 16);
    // 0x8007B278: ori         $v1, $v1, 0x869F
    ctx->r3 = ctx->r3 | 0X869F;
L_8007B27C:
    // 0x8007B27C: andi        $t2, $t1, 0x7
    ctx->r10 = ctx->r9 & 0X7;
    // 0x8007B280: sw          $v1, 0x0($s1)
    MEM_W(0X0, ctx->r17) = ctx->r3;
    // 0x8007B284: sw          $t2, 0x4($s1)
    MEM_W(0X4, ctx->r17) = ctx->r10;
    // 0x8007B288: addiu       $a0, $s1, 0xC
    ctx->r4 = ADD32(ctx->r17, 0XC);
    // 0x8007B28C: jal         0x8007AEFC
    // 0x8007B290: addiu       $a1, $s0, 0x3
    ctx->r5 = ADD32(ctx->r16, 0X3);
    func_8007AEFC(rdram, ctx);
        goto after_0;
    // 0x8007B290: addiu       $a1, $s0, 0x3
    ctx->r5 = ADD32(ctx->r16, 0X3);
    after_0:
    // 0x8007B294: sb          $zero, 0xF($s1)
    MEM_B(0XF, ctx->r17) = 0;
    // 0x8007B298: lbu         $t3, 0x3($s0)
    ctx->r11 = MEM_BU(ctx->r16, 0X3);
    // 0x8007B29C: sra         $t4, $t3, 7
    ctx->r12 = S32(SIGNED(ctx->r11) >> 7);
    // 0x8007B2A0: andi        $t5, $t4, 0x1
    ctx->r13 = ctx->r12 & 0X1;
    // 0x8007B2A4: sw          $t5, 0x8($s1)
    MEM_W(0X8, ctx->r17) = ctx->r13;
    // 0x8007B2A8: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    // 0x8007B2AC: lw          $s1, 0x18($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X18);
    // 0x8007B2B0: lw          $s0, 0x14($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X14);
    // 0x8007B2B4: jr          $ra
    // 0x8007B2B8: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    return;
    // 0x8007B2B8: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
;}
RECOMP_FUNC void func_8007B2BC(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8007B2BC: bgezl       $a0, L_8007B2D0
    if (SIGNED(ctx->r4) >= 0) {
        // 0x8007B2C0: sra         $t6, $a0, 16
        ctx->r14 = S32(SIGNED(ctx->r4) >> 16);
            goto L_8007B2D0;
    }
    goto skip_0;
    // 0x8007B2C0: sra         $t6, $a0, 16
    ctx->r14 = S32(SIGNED(ctx->r4) >> 16);
    skip_0:
    // 0x8007B2C4: lui         $a0, 0xFF
    ctx->r4 = S32(0XFF << 16);
    // 0x8007B2C8: ori         $a0, $a0, 0xFFFF
    ctx->r4 = ctx->r4 | 0XFFFF;
    // 0x8007B2CC: sra         $t6, $a0, 16
    ctx->r14 = S32(SIGNED(ctx->r4) >> 16);
L_8007B2D0:
    // 0x8007B2D0: sra         $t8, $a0, 8
    ctx->r24 = S32(SIGNED(ctx->r4) >> 8);
    // 0x8007B2D4: sb          $t6, 0x0($a1)
    MEM_B(0X0, ctx->r5) = ctx->r14;
    // 0x8007B2D8: sb          $t8, 0x1($a1)
    MEM_B(0X1, ctx->r5) = ctx->r24;
    // 0x8007B2DC: jr          $ra
    // 0x8007B2E0: sb          $a0, 0x2($a1)
    MEM_B(0X2, ctx->r5) = ctx->r4;
    return;
    // 0x8007B2E0: sb          $a0, 0x2($a1)
    MEM_B(0X2, ctx->r5) = ctx->r4;
;}
RECOMP_FUNC void func_8007B2E4(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8007B2E4: lbu         $v0, 0x0($a0)
    ctx->r2 = MEM_BU(ctx->r4, 0X0);
    // 0x8007B2E8: lbu         $v1, 0x1($a0)
    ctx->r3 = MEM_BU(ctx->r4, 0X1);
    // 0x8007B2EC: lbu         $a1, 0x2($a0)
    ctx->r5 = MEM_BU(ctx->r4, 0X2);
    // 0x8007B2F0: sll         $t6, $v0, 16
    ctx->r14 = S32(ctx->r2 << 16);
    // 0x8007B2F4: sll         $t7, $v1, 8
    ctx->r15 = S32(ctx->r3 << 8);
    // 0x8007B2F8: addu        $t8, $t6, $t7
    ctx->r24 = ADD32(ctx->r14, ctx->r15);
    // 0x8007B2FC: lui         $at, 0xFF
    ctx->r1 = S32(0XFF << 16);
    // 0x8007B300: ori         $at, $at, 0xFFFF
    ctx->r1 = ctx->r1 | 0XFFFF;
    // 0x8007B304: addu        $a2, $t8, $a1
    ctx->r6 = ADD32(ctx->r24, ctx->r5);
    // 0x8007B308: bne         $a2, $at, L_8007B314
    if (ctx->r6 != ctx->r1) {
        // 0x8007B30C: nop
    
            goto L_8007B314;
    }
    // 0x8007B30C: nop

    // 0x8007B310: addiu       $a2, $zero, -0x1
    ctx->r6 = ADD32(0, -0X1);
L_8007B314:
    // 0x8007B314: jr          $ra
    // 0x8007B318: or          $v0, $a2, $zero
    ctx->r2 = ctx->r6 | 0;
    return;
    // 0x8007B318: or          $v0, $a2, $zero
    ctx->r2 = ctx->r6 | 0;
;}
RECOMP_FUNC void func_8007B31C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8007B31C: lui         $t6, 0x801D
    ctx->r14 = S32(0X801D << 16);
    // 0x8007B320: lb          $t6, -0x4D80($t6)
    ctx->r14 = MEM_B(ctx->r14, -0X4D80);
    // 0x8007B324: lui         $t7, 0x801D
    ctx->r15 = S32(0X801D << 16);
    // 0x8007B328: lw          $t7, -0x4D78($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X4D78);
    // 0x8007B32C: lui         $at, 0x801B
    ctx->r1 = S32(0X801B << 16);
    // 0x8007B330: lui         $t8, 0x801D
    ctx->r24 = S32(0X801D << 16);
    // 0x8007B334: sb          $t6, -0x15DC($at)
    MEM_B(-0X15DC, ctx->r1) = ctx->r14;
    // 0x8007B338: lw          $t8, -0x4D74($t8)
    ctx->r24 = MEM_W(ctx->r24, -0X4D74);
    // 0x8007B33C: lui         $at, 0x801B
    ctx->r1 = S32(0X801B << 16);
    // 0x8007B340: lui         $t9, 0x801D
    ctx->r25 = S32(0X801D << 16);
    // 0x8007B344: sb          $t7, -0x15E0($at)
    MEM_B(-0X15E0, ctx->r1) = ctx->r15;
    // 0x8007B348: lw          $t9, -0x4D70($t9)
    ctx->r25 = MEM_W(ctx->r25, -0X4D70);
    // 0x8007B34C: lui         $at, 0x801B
    ctx->r1 = S32(0X801B << 16);
    // 0x8007B350: sb          $t8, -0x15DF($at)
    MEM_B(-0X15DF, ctx->r1) = ctx->r24;
    // 0x8007B354: lui         $at, 0x801B
    ctx->r1 = S32(0X801B << 16);
    // 0x8007B358: lui         $t0, 0x801D
    ctx->r8 = S32(0X801D << 16);
    // 0x8007B35C: lw          $t0, -0x4D6C($t0)
    ctx->r8 = MEM_W(ctx->r8, -0X4D6C);
    // 0x8007B360: sb          $t9, -0x15DE($at)
    MEM_B(-0X15DE, ctx->r1) = ctx->r25;
    // 0x8007B364: lui         $at, 0x801B
    ctx->r1 = S32(0X801B << 16);
    // 0x8007B368: jr          $ra
    // 0x8007B36C: sb          $t0, -0x15DD($at)
    MEM_B(-0X15DD, ctx->r1) = ctx->r8;
    return;
    // 0x8007B36C: sb          $t0, -0x15DD($at)
    MEM_B(-0X15DD, ctx->r1) = ctx->r8;
;}
RECOMP_FUNC void func_8007B370(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8007B370: addiu       $sp, $sp, -0x78
    ctx->r29 = ADD32(ctx->r29, -0X78);
    // 0x8007B374: sw          $s6, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r22;
    // 0x8007B378: sw          $s3, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r19;
    // 0x8007B37C: or          $s6, $a0, $zero
    ctx->r22 = ctx->r4 | 0;
    // 0x8007B380: sw          $ra, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r31;
    // 0x8007B384: sw          $fp, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r30;
    // 0x8007B388: sw          $s7, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r23;
    // 0x8007B38C: sw          $s5, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r21;
    // 0x8007B390: sw          $s4, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r20;
    // 0x8007B394: sw          $s2, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r18;
    // 0x8007B398: sw          $s1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r17;
    // 0x8007B39C: sw          $s0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r16;
    // 0x8007B3A0: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x8007B3A4: or          $s3, $zero, $zero
    ctx->r19 = 0 | 0;
    // 0x8007B3A8: addiu       $v1, $zero, 0xFF
    ctx->r3 = ADD32(0, 0XFF);
L_8007B3AC:
    // 0x8007B3AC: addiu       $s3, $s3, 0x1
    ctx->r19 = ADD32(ctx->r19, 0X1);
    // 0x8007B3B0: slti        $at, $s3, 0x200
    ctx->r1 = SIGNED(ctx->r19) < 0X200 ? 1 : 0;
    // 0x8007B3B4: sb          $v1, 0x0($v0)
    MEM_B(0X0, ctx->r2) = ctx->r3;
    // 0x8007B3B8: bne         $at, $zero, L_8007B3AC
    if (ctx->r1 != 0) {
        // 0x8007B3BC: addiu       $v0, $v0, 0x1
        ctx->r2 = ADD32(ctx->r2, 0X1);
            goto L_8007B3AC;
    }
    // 0x8007B3BC: addiu       $v0, $v0, 0x1
    ctx->r2 = ADD32(ctx->r2, 0X1);
    // 0x8007B3C0: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x8007B3C4: lui         $a0, 0x800E
    ctx->r4 = S32(0X800E << 16);
    // 0x8007B3C8: addiu       $a0, $a0, -0x7D96
    ctx->r4 = ADD32(ctx->r4, -0X7D96);
    // 0x8007B3CC: addiu       $v0, $v0, -0x7D98
    ctx->r2 = ADD32(ctx->r2, -0X7D98);
    // 0x8007B3D0: or          $v1, $s6, $zero
    ctx->r3 = ctx->r22 | 0;
L_8007B3D4:
    // 0x8007B3D4: lbu         $t6, 0x0($v0)
    ctx->r14 = MEM_BU(ctx->r2, 0X0);
    // 0x8007B3D8: addiu       $v0, $v0, 0x1
    ctx->r2 = ADD32(ctx->r2, 0X1);
    // 0x8007B3DC: sltu        $at, $v0, $a0
    ctx->r1 = ctx->r2 < ctx->r4 ? 1 : 0;
    // 0x8007B3E0: addiu       $v1, $v1, 0x1
    ctx->r3 = ADD32(ctx->r3, 0X1);
    // 0x8007B3E4: bne         $at, $zero, L_8007B3D4
    if (ctx->r1 != 0) {
        // 0x8007B3E8: sb          $t6, -0x1($v1)
        MEM_B(-0X1, ctx->r3) = ctx->r14;
            goto L_8007B3D4;
    }
    // 0x8007B3E8: sb          $t6, -0x1($v1)
    MEM_B(-0X1, ctx->r3) = ctx->r14;
    // 0x8007B3EC: lui         $t7, 0x800E
    ctx->r15 = S32(0X800E << 16);
    // 0x8007B3F0: addiu       $s5, $t7, -0x7D08
    ctx->r21 = ADD32(ctx->r15, -0X7D08);
    // 0x8007B3F4: or          $s7, $s5, $zero
    ctx->r23 = ctx->r21 | 0;
    // 0x8007B3F8: or          $fp, $s6, $zero
    ctx->r30 = ctx->r22 | 0;
    // 0x8007B3FC: sw          $s6, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r22;
    // 0x8007B400: addiu       $s4, $zero, 0x2
    ctx->r20 = ADD32(0, 0X2);
L_8007B404:
    // 0x8007B404: or          $s1, $s7, $zero
    ctx->r17 = ctx->r23 | 0;
    // 0x8007B408: or          $s2, $zero, $zero
    ctx->r18 = 0 | 0;
    // 0x8007B40C: addiu       $s3, $fp, 0x60
    ctx->r19 = ADD32(ctx->r30, 0X60);
L_8007B410:
    // 0x8007B410: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    // 0x8007B414: jal         0x8007AF78
    // 0x8007B418: or          $a1, $s3, $zero
    ctx->r5 = ctx->r19 | 0;
    func_8007AF78(rdram, ctx);
        goto after_0;
    // 0x8007B418: or          $a1, $s3, $zero
    ctx->r5 = ctx->r19 | 0;
    after_0:
    // 0x8007B41C: addiu       $s2, $s2, 0x6
    ctx->r18 = ADD32(ctx->r18, 0X6);
    // 0x8007B420: slti        $at, $s2, 0x18
    ctx->r1 = SIGNED(ctx->r18) < 0X18 ? 1 : 0;
    // 0x8007B424: addiu       $s1, $s1, 0x14
    ctx->r17 = ADD32(ctx->r17, 0X14);
    // 0x8007B428: bne         $at, $zero, L_8007B410
    if (ctx->r1 != 0) {
        // 0x8007B42C: addiu       $s3, $s3, 0x6
        ctx->r19 = ADD32(ctx->r19, 0X6);
            goto L_8007B410;
    }
    // 0x8007B42C: addiu       $s3, $s3, 0x6
    ctx->r19 = ADD32(ctx->r19, 0X6);
    // 0x8007B430: lw          $s1, 0x44($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X44);
    // 0x8007B434: or          $s0, $zero, $zero
    ctx->r16 = 0 | 0;
    // 0x8007B438: addiu       $s1, $s1, 0x1A8
    ctx->r17 = ADD32(ctx->r17, 0X1A8);
L_8007B43C:
    // 0x8007B43C: lw          $t8, 0x3C($s5)
    ctx->r24 = MEM_W(ctx->r21, 0X3C);
    // 0x8007B440: addiu       $s2, $s0, 0x1
    ctx->r18 = ADD32(ctx->r16, 0X1);
    // 0x8007B444: or          $a1, $s1, $zero
    ctx->r5 = ctx->r17 | 0;
    // 0x8007B448: multu       $t8, $s2
    result = U64(U32(ctx->r24)) * U64(U32(ctx->r18)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x8007B44C: mflo        $a0
    ctx->r4 = lo;
    // 0x8007B450: jal         0x8007B2BC
    // 0x8007B454: nop

    func_8007B2BC(rdram, ctx);
        goto after_1;
    // 0x8007B454: nop

    after_1:
    // 0x8007B458: or          $s0, $s2, $zero
    ctx->r16 = ctx->r18 | 0;
    // 0x8007B45C: bne         $s2, $s4, L_8007B43C
    if (ctx->r18 != ctx->r20) {
        // 0x8007B460: addiu       $s1, $s1, 0x3
        ctx->r17 = ADD32(ctx->r17, 0X3);
            goto L_8007B43C;
    }
    // 0x8007B460: addiu       $s1, $s1, 0x3
    ctx->r17 = ADD32(ctx->r17, 0X3);
    // 0x8007B464: lw          $t9, 0x44($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X44);
    // 0x8007B468: lui         $t1, 0x800E
    ctx->r9 = S32(0X800E << 16);
    // 0x8007B46C: addiu       $t1, $t1, -0x7A88
    ctx->r9 = ADD32(ctx->r9, -0X7A88);
    // 0x8007B470: addiu       $s5, $s5, 0x50
    ctx->r21 = ADD32(ctx->r21, 0X50);
    // 0x8007B474: sltu        $at, $s5, $t1
    ctx->r1 = ctx->r21 < ctx->r9 ? 1 : 0;
    // 0x8007B478: addiu       $t0, $t9, 0x6
    ctx->r8 = ADD32(ctx->r25, 0X6);
    // 0x8007B47C: sw          $t0, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r8;
    // 0x8007B480: addiu       $s7, $s7, 0x50
    ctx->r23 = ADD32(ctx->r23, 0X50);
    // 0x8007B484: bne         $at, $zero, L_8007B404
    if (ctx->r1 != 0) {
        // 0x8007B488: addiu       $fp, $fp, 0x18
        ctx->r30 = ADD32(ctx->r30, 0X18);
            goto L_8007B404;
    }
    // 0x8007B488: addiu       $fp, $fp, 0x18
    ctx->r30 = ADD32(ctx->r30, 0X18);
    // 0x8007B48C: lui         $s5, 0x800E
    ctx->r21 = S32(0X800E << 16);
    // 0x8007B490: lui         $fp, 0x800E
    ctx->r30 = S32(0X800E << 16);
    // 0x8007B494: addiu       $fp, $fp, -0x78D8
    ctx->r30 = ADD32(ctx->r30, -0X78D8);
    // 0x8007B498: addiu       $s5, $s5, -0x7A88
    ctx->r21 = ADD32(ctx->r21, -0X7A88);
    // 0x8007B49C: or          $s7, $s6, $zero
    ctx->r23 = ctx->r22 | 0;
    // 0x8007B4A0: addiu       $s4, $zero, 0xF
    ctx->r20 = ADD32(0, 0XF);
L_8007B4A4:
    // 0x8007B4A4: or          $s1, $s5, $zero
    ctx->r17 = ctx->r21 | 0;
    // 0x8007B4A8: or          $s2, $zero, $zero
    ctx->r18 = 0 | 0;
    // 0x8007B4AC: addiu       $s3, $s7, 0x120
    ctx->r19 = ADD32(ctx->r23, 0X120);
L_8007B4B0:
    // 0x8007B4B0: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    // 0x8007B4B4: jal         0x8007B1AC
    // 0x8007B4B8: or          $a1, $s3, $zero
    ctx->r5 = ctx->r19 | 0;
    func_8007B1AC(rdram, ctx);
        goto after_2;
    // 0x8007B4B8: or          $a1, $s3, $zero
    ctx->r5 = ctx->r19 | 0;
    after_2:
    // 0x8007B4BC: addiu       $s2, $s2, 0x5
    ctx->r18 = ADD32(ctx->r18, 0X5);
    // 0x8007B4C0: addiu       $s1, $s1, 0x10
    ctx->r17 = ADD32(ctx->r17, 0X10);
    // 0x8007B4C4: bne         $s2, $s4, L_8007B4B0
    if (ctx->r18 != ctx->r20) {
        // 0x8007B4C8: addiu       $s3, $s3, 0x5
        ctx->r19 = ADD32(ctx->r19, 0X5);
            goto L_8007B4B0;
    }
    // 0x8007B4C8: addiu       $s3, $s3, 0x5
    ctx->r19 = ADD32(ctx->r19, 0X5);
    // 0x8007B4CC: addiu       $s5, $s5, 0x30
    ctx->r21 = ADD32(ctx->r21, 0X30);
    // 0x8007B4D0: sltu        $at, $s5, $fp
    ctx->r1 = ctx->r21 < ctx->r30 ? 1 : 0;
    // 0x8007B4D4: bne         $at, $zero, L_8007B4A4
    if (ctx->r1 != 0) {
        // 0x8007B4D8: addiu       $s7, $s7, 0xF
        ctx->r23 = ADD32(ctx->r23, 0XF);
            goto L_8007B4A4;
    }
    // 0x8007B4D8: addiu       $s7, $s7, 0xF
    ctx->r23 = ADD32(ctx->r23, 0XF);
    // 0x8007B4DC: lui         $s2, 0x800E
    ctx->r18 = S32(0X800E << 16);
    // 0x8007B4E0: addiu       $s2, $s2, -0x78D8
    ctx->r18 = ADD32(ctx->r18, -0X78D8);
    // 0x8007B4E4: or          $s0, $zero, $zero
    ctx->r16 = 0 | 0;
    // 0x8007B4E8: addiu       $s1, $s6, 0x1D8
    ctx->r17 = ADD32(ctx->r22, 0X1D8);
L_8007B4EC:
    // 0x8007B4EC: or          $a0, $s2, $zero
    ctx->r4 = ctx->r18 | 0;
    // 0x8007B4F0: jal         0x8007B09C
    // 0x8007B4F4: or          $a1, $s1, $zero
    ctx->r5 = ctx->r17 | 0;
    func_8007B09C(rdram, ctx);
        goto after_3;
    // 0x8007B4F4: or          $a1, $s1, $zero
    ctx->r5 = ctx->r17 | 0;
    after_3:
    // 0x8007B4F8: addiu       $s0, $s0, 0x5
    ctx->r16 = ADD32(ctx->r16, 0X5);
    // 0x8007B4FC: slti        $at, $s0, 0x28
    ctx->r1 = SIGNED(ctx->r16) < 0X28 ? 1 : 0;
    // 0x8007B500: bne         $at, $zero, L_8007B4EC
    if (ctx->r1 != 0) {
        // 0x8007B504: addiu       $s1, $s1, 0x5
        ctx->r17 = ADD32(ctx->r17, 0X5);
            goto L_8007B4EC;
    }
    // 0x8007B504: addiu       $s1, $s1, 0x5
    ctx->r17 = ADD32(ctx->r17, 0X5);
    // 0x8007B508: lui         $t2, 0x800E
    ctx->r10 = S32(0X800E << 16);
    // 0x8007B50C: addiu       $s2, $t2, -0x56B0
    ctx->r18 = ADD32(ctx->r10, -0X56B0);
    // 0x8007B510: or          $s5, $s2, $zero
    ctx->r21 = ctx->r18 | 0;
    // 0x8007B514: or          $s3, $zero, $zero
    ctx->r19 = 0 | 0;
    // 0x8007B518: addiu       $s4, $s6, 0x10
    ctx->r20 = ADD32(ctx->r22, 0X10);
    // 0x8007B51C: addiu       $s1, $zero, 0x3
    ctx->r17 = ADD32(0, 0X3);
L_8007B520:
    // 0x8007B520: or          $a0, $s4, $zero
    ctx->r4 = ctx->r20 | 0;
    // 0x8007B524: or          $a1, $s5, $zero
    ctx->r5 = ctx->r21 | 0;
    // 0x8007B528: jal         0x8006A140
    // 0x8007B52C: addiu       $a2, $zero, 0xA
    ctx->r6 = ADD32(0, 0XA);
    Libc_strncpy(rdram, ctx);
        goto after_4;
    // 0x8007B52C: addiu       $a2, $zero, 0xA
    ctx->r6 = ADD32(0, 0XA);
    after_4:
    // 0x8007B530: sll         $t3, $s3, 2
    ctx->r11 = S32(ctx->r19 << 2);
    // 0x8007B534: subu        $t3, $t3, $s3
    ctx->r11 = SUB32(ctx->r11, ctx->r19);
    // 0x8007B538: addu        $a1, $s6, $t3
    ctx->r5 = ADD32(ctx->r22, ctx->r11);
    // 0x8007B53C: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
L_8007B540:
    // 0x8007B540: or          $s0, $zero, $zero
    ctx->r16 = 0 | 0;
    // 0x8007B544: or          $v0, $a1, $zero
    ctx->r2 = ctx->r5 | 0;
    // 0x8007B548: or          $v1, $s2, $zero
    ctx->r3 = ctx->r18 | 0;
L_8007B54C:
    // 0x8007B54C: lb          $t4, 0xB($v1)
    ctx->r12 = MEM_B(ctx->r3, 0XB);
    // 0x8007B550: addiu       $s0, $s0, 0x1
    ctx->r16 = ADD32(ctx->r16, 0X1);
    // 0x8007B554: addiu       $v0, $v0, 0x1
    ctx->r2 = ADD32(ctx->r2, 0X1);
    // 0x8007B558: addiu       $v1, $v1, 0x1
    ctx->r3 = ADD32(ctx->r3, 0X1);
    // 0x8007B55C: bne         $s0, $s1, L_8007B54C
    if (ctx->r16 != ctx->r17) {
        // 0x8007B560: sb          $t4, 0x37($v0)
        MEM_B(0X37, ctx->r2) = ctx->r12;
            goto L_8007B54C;
    }
    // 0x8007B560: sb          $t4, 0x37($v0)
    MEM_B(0X37, ctx->r2) = ctx->r12;
    // 0x8007B564: addiu       $a0, $a0, 0x1
    ctx->r4 = ADD32(ctx->r4, 0X1);
    // 0x8007B568: slti        $at, $a0, 0x2
    ctx->r1 = SIGNED(ctx->r4) < 0X2 ? 1 : 0;
    // 0x8007B56C: bne         $at, $zero, L_8007B540
    if (ctx->r1 != 0) {
        // 0x8007B570: addiu       $a1, $a1, 0xC
        ctx->r5 = ADD32(ctx->r5, 0XC);
            goto L_8007B540;
    }
    // 0x8007B570: addiu       $a1, $a1, 0xC
    ctx->r5 = ADD32(ctx->r5, 0XC);
    // 0x8007B574: addiu       $s3, $s3, 0x1
    ctx->r19 = ADD32(ctx->r19, 0X1);
    // 0x8007B578: slti        $at, $s3, 0x4
    ctx->r1 = SIGNED(ctx->r19) < 0X4 ? 1 : 0;
    // 0x8007B57C: addiu       $s4, $s4, 0xA
    ctx->r20 = ADD32(ctx->r20, 0XA);
    // 0x8007B580: addiu       $s5, $s5, 0xE
    ctx->r21 = ADD32(ctx->r21, 0XE);
    // 0x8007B584: bne         $at, $zero, L_8007B520
    if (ctx->r1 != 0) {
        // 0x8007B588: addiu       $s2, $s2, 0xE
        ctx->r18 = ADD32(ctx->r18, 0XE);
            goto L_8007B520;
    }
    // 0x8007B588: addiu       $s2, $s2, 0xE
    ctx->r18 = ADD32(ctx->r18, 0XE);
    // 0x8007B58C: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x8007B590: lui         $a0, 0x800E
    ctx->r4 = S32(0X800E << 16);
    // 0x8007B594: sb          $zero, 0xC($s6)
    MEM_B(0XC, ctx->r22) = 0;
    // 0x8007B598: addiu       $a0, $a0, -0x56B0
    ctx->r4 = ADD32(ctx->r4, -0X56B0);
    // 0x8007B59C: addiu       $v0, $v0, -0x56C0
    ctx->r2 = ADD32(ctx->r2, -0X56C0);
    // 0x8007B5A0: or          $v1, $s6, $zero
    ctx->r3 = ctx->r22 | 0;
L_8007B5A4:
    // 0x8007B5A4: lw          $t5, 0x0($v0)
    ctx->r13 = MEM_W(ctx->r2, 0X0);
    // 0x8007B5A8: addiu       $v0, $v0, 0x4
    ctx->r2 = ADD32(ctx->r2, 0X4);
    // 0x8007B5AC: sltu        $at, $v0, $a0
    ctx->r1 = ctx->r2 < ctx->r4 ? 1 : 0;
    // 0x8007B5B0: addiu       $v1, $v1, 0x1
    ctx->r3 = ADD32(ctx->r3, 0X1);
    // 0x8007B5B4: bne         $at, $zero, L_8007B5A4
    if (ctx->r1 != 0) {
        // 0x8007B5B8: sb          $t5, 0x7($v1)
        MEM_B(0X7, ctx->r3) = ctx->r13;
            goto L_8007B5A4;
    }
    // 0x8007B5B8: sb          $t5, 0x7($v1)
    MEM_B(0X7, ctx->r3) = ctx->r13;
    // 0x8007B5BC: lui         $a0, 0x800E
    ctx->r4 = S32(0X800E << 16);
    // 0x8007B5C0: lui         $a2, 0x800E
    ctx->r6 = S32(0X800E << 16);
    // 0x8007B5C4: addiu       $a2, $a2, -0x5654
    ctx->r6 = ADD32(ctx->r6, -0X5654);
    // 0x8007B5C8: addiu       $a0, $a0, -0x5678
    ctx->r4 = ADD32(ctx->r4, -0X5678);
    // 0x8007B5CC: or          $a1, $s6, $zero
    ctx->r5 = ctx->r22 | 0;
L_8007B5D0:
    // 0x8007B5D0: or          $s0, $zero, $zero
    ctx->r16 = 0 | 0;
    // 0x8007B5D4: or          $v0, $a1, $zero
    ctx->r2 = ctx->r5 | 0;
    // 0x8007B5D8: or          $v1, $a0, $zero
    ctx->r3 = ctx->r4 | 0;
L_8007B5DC:
    // 0x8007B5DC: lw          $t6, 0x0($v1)
    ctx->r14 = MEM_W(ctx->r3, 0X0);
    // 0x8007B5E0: addiu       $s0, $s0, 0x1
    ctx->r16 = ADD32(ctx->r16, 0X1);
    // 0x8007B5E4: addiu       $v0, $v0, 0x1
    ctx->r2 = ADD32(ctx->r2, 0X1);
    // 0x8007B5E8: addiu       $v1, $v1, 0x4
    ctx->r3 = ADD32(ctx->r3, 0X4);
    // 0x8007B5EC: bne         $s0, $s1, L_8007B5DC
    if (ctx->r16 != ctx->r17) {
        // 0x8007B5F0: sb          $t6, 0x4F($v0)
        MEM_B(0X4F, ctx->r2) = ctx->r14;
            goto L_8007B5DC;
    }
    // 0x8007B5F0: sb          $t6, 0x4F($v0)
    MEM_B(0X4F, ctx->r2) = ctx->r14;
    // 0x8007B5F4: addiu       $a0, $a0, 0xC
    ctx->r4 = ADD32(ctx->r4, 0XC);
    // 0x8007B5F8: bne         $a0, $a2, L_8007B5D0
    if (ctx->r4 != ctx->r6) {
        // 0x8007B5FC: addiu       $a1, $a1, 0x3
        ctx->r5 = ADD32(ctx->r5, 0X3);
            goto L_8007B5D0;
    }
    // 0x8007B5FC: addiu       $a1, $a1, 0x3
    ctx->r5 = ADD32(ctx->r5, 0X3);
    // 0x8007B600: lw          $ra, 0x3C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X3C);
    // 0x8007B604: lw          $s0, 0x18($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X18);
    // 0x8007B608: lw          $s1, 0x1C($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X1C);
    // 0x8007B60C: lw          $s2, 0x20($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X20);
    // 0x8007B610: lw          $s3, 0x24($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X24);
    // 0x8007B614: lw          $s4, 0x28($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X28);
    // 0x8007B618: lw          $s5, 0x2C($sp)
    ctx->r21 = MEM_W(ctx->r29, 0X2C);
    // 0x8007B61C: lw          $s6, 0x30($sp)
    ctx->r22 = MEM_W(ctx->r29, 0X30);
    // 0x8007B620: lw          $s7, 0x34($sp)
    ctx->r23 = MEM_W(ctx->r29, 0X34);
    // 0x8007B624: lw          $fp, 0x38($sp)
    ctx->r30 = MEM_W(ctx->r29, 0X38);
    // 0x8007B628: jr          $ra
    // 0x8007B62C: addiu       $sp, $sp, 0x78
    ctx->r29 = ADD32(ctx->r29, 0X78);
    return;
    // 0x8007B62C: addiu       $sp, $sp, 0x78
    ctx->r29 = ADD32(ctx->r29, 0X78);
;}
RECOMP_FUNC void func_8007B630(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8007B630: addiu       $sp, $sp, -0x88
    ctx->r29 = ADD32(ctx->r29, -0X88);
    // 0x8007B634: sw          $fp, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r30;
    // 0x8007B638: sw          $s7, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r23;
    // 0x8007B63C: sw          $s5, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r21;
    // 0x8007B640: lui         $t6, 0x801B
    ctx->r14 = S32(0X801B << 16);
    // 0x8007B644: lui         $t7, 0x801C
    ctx->r15 = S32(0X801C << 16);
    // 0x8007B648: sw          $s6, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r22;
    // 0x8007B64C: sw          $s4, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r20;
    // 0x8007B650: sw          $s3, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r19;
    // 0x8007B654: addiu       $t7, $t7, 0x22D4
    ctx->r15 = ADD32(ctx->r15, 0X22D4);
    // 0x8007B658: addiu       $s7, $t6, -0x15E8
    ctx->r23 = ADD32(ctx->r14, -0X15E8);
    // 0x8007B65C: lui         $s5, 0x801C
    ctx->r21 = S32(0X801C << 16);
    // 0x8007B660: lui         $fp, 0x801C
    ctx->r30 = S32(0X801C << 16);
    // 0x8007B664: sw          $ra, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r31;
    // 0x8007B668: sw          $s2, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r18;
    // 0x8007B66C: sw          $s1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r17;
    // 0x8007B670: sw          $s0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r16;
    // 0x8007B674: addiu       $fp, $fp, 0x24C4
    ctx->r30 = ADD32(ctx->r30, 0X24C4);
    // 0x8007B678: addiu       $s5, $s5, 0x202C
    ctx->r21 = ADD32(ctx->r21, 0X202C);
    // 0x8007B67C: or          $s6, $s7, $zero
    ctx->r22 = ctx->r23 | 0;
    // 0x8007B680: sw          $t7, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r15;
    // 0x8007B684: addiu       $s3, $zero, 0x6
    ctx->r19 = ADD32(0, 0X6);
    // 0x8007B688: addiu       $s4, $zero, 0x1
    ctx->r20 = ADD32(0, 0X1);
L_8007B68C:
    // 0x8007B68C: addiu       $s0, $s6, 0x60
    ctx->r16 = ADD32(ctx->r22, 0X60);
    // 0x8007B690: or          $s1, $zero, $zero
    ctx->r17 = 0 | 0;
    // 0x8007B694: or          $s2, $s5, $zero
    ctx->r18 = ctx->r21 | 0;
L_8007B698:
    // 0x8007B698: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x8007B69C: jal         0x8007AFF4
    // 0x8007B6A0: or          $a1, $s2, $zero
    ctx->r5 = ctx->r18 | 0;
    func_8007AFF4(rdram, ctx);
        goto after_0;
    // 0x8007B6A0: or          $a1, $s2, $zero
    ctx->r5 = ctx->r18 | 0;
    after_0:
    // 0x8007B6A4: addiu       $s1, $s1, 0x14
    ctx->r17 = ADD32(ctx->r17, 0X14);
    // 0x8007B6A8: slti        $at, $s1, 0x3C
    ctx->r1 = SIGNED(ctx->r17) < 0X3C ? 1 : 0;
    // 0x8007B6AC: addiu       $s0, $s0, 0x6
    ctx->r16 = ADD32(ctx->r16, 0X6);
    // 0x8007B6B0: bne         $at, $zero, L_8007B698
    if (ctx->r1 != 0) {
        // 0x8007B6B4: addiu       $s2, $s2, 0x14
        ctx->r18 = ADD32(ctx->r18, 0X14);
            goto L_8007B698;
    }
    // 0x8007B6B4: addiu       $s2, $s2, 0x14
    ctx->r18 = ADD32(ctx->r18, 0X14);
    // 0x8007B6B8: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x8007B6BC: jal         0x8007AFF4
    // 0x8007B6C0: lw          $a1, 0x44($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X44);
    func_8007AFF4(rdram, ctx);
        goto after_1;
    // 0x8007B6C0: lw          $a1, 0x44($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X44);
    after_1:
    // 0x8007B6C4: or          $s0, $zero, $zero
    ctx->r16 = 0 | 0;
    // 0x8007B6C8: addiu       $s1, $s7, 0x1A8
    ctx->r17 = ADD32(ctx->r23, 0X1A8);
    // 0x8007B6CC: or          $s2, $fp, $zero
    ctx->r18 = ctx->r30 | 0;
L_8007B6D0:
    // 0x8007B6D0: jal         0x8007B2E4
    // 0x8007B6D4: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    func_8007B2E4(rdram, ctx);
        goto after_2;
    // 0x8007B6D4: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    after_2:
    // 0x8007B6D8: addiu       $s0, $s0, 0x3
    ctx->r16 = ADD32(ctx->r16, 0X3);
    // 0x8007B6DC: addiu       $s1, $s1, 0x3
    ctx->r17 = ADD32(ctx->r17, 0X3);
    // 0x8007B6E0: addiu       $s2, $s2, 0x4
    ctx->r18 = ADD32(ctx->r18, 0X4);
    // 0x8007B6E4: bne         $s0, $s3, L_8007B6D0
    if (ctx->r16 != ctx->r19) {
        // 0x8007B6E8: sw          $v0, -0x4($s2)
        MEM_W(-0X4, ctx->r18) = ctx->r2;
            goto L_8007B6D0;
    }
    // 0x8007B6E8: sw          $v0, -0x4($s2)
    MEM_W(-0X4, ctx->r18) = ctx->r2;
    // 0x8007B6EC: lw          $t8, 0x44($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X44);
    // 0x8007B6F0: lui         $t0, 0x801C
    ctx->r8 = S32(0X801C << 16);
    // 0x8007B6F4: addiu       $t0, $t0, 0x220C
    ctx->r8 = ADD32(ctx->r8, 0X220C);
    // 0x8007B6F8: addiu       $s5, $s5, 0x3C
    ctx->r21 = ADD32(ctx->r21, 0X3C);
    // 0x8007B6FC: sltu        $at, $s5, $t0
    ctx->r1 = ctx->r21 < ctx->r8 ? 1 : 0;
    // 0x8007B700: addiu       $t9, $t8, 0x14
    ctx->r25 = ADD32(ctx->r24, 0X14);
    // 0x8007B704: sw          $t9, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r25;
    // 0x8007B708: addiu       $s4, $s4, 0x1
    ctx->r20 = ADD32(ctx->r20, 0X1);
    // 0x8007B70C: addiu       $s6, $s6, 0x18
    ctx->r22 = ADD32(ctx->r22, 0X18);
    // 0x8007B710: addiu       $s7, $s7, 0x6
    ctx->r23 = ADD32(ctx->r23, 0X6);
    // 0x8007B714: bne         $at, $zero, L_8007B68C
    if (ctx->r1 != 0) {
        // 0x8007B718: addiu       $fp, $fp, 0x24
        ctx->r30 = ADD32(ctx->r30, 0X24);
            goto L_8007B68C;
    }
    // 0x8007B718: addiu       $fp, $fp, 0x24
    ctx->r30 = ADD32(ctx->r30, 0X24);
    // 0x8007B71C: lui         $s6, 0x801B
    ctx->r22 = S32(0X801B << 16);
    // 0x8007B720: lui         $s5, 0x801C
    ctx->r21 = S32(0X801C << 16);
    // 0x8007B724: lui         $s7, 0x801C
    ctx->r23 = S32(0X801C << 16);
    // 0x8007B728: addiu       $s7, $s7, 0x2898
    ctx->r23 = ADD32(ctx->r23, 0X2898);
    // 0x8007B72C: addiu       $s5, $s5, 0x26E8
    ctx->r21 = ADD32(ctx->r21, 0X26E8);
    // 0x8007B730: addiu       $s6, $s6, -0x15E8
    ctx->r22 = ADD32(ctx->r22, -0X15E8);
    // 0x8007B734: addiu       $s4, $zero, 0x1
    ctx->r20 = ADD32(0, 0X1);
    // 0x8007B738: addiu       $s3, $zero, 0x30
    ctx->r19 = ADD32(0, 0X30);
L_8007B73C:
    // 0x8007B73C: addiu       $s0, $s6, 0x120
    ctx->r16 = ADD32(ctx->r22, 0X120);
    // 0x8007B740: or          $s1, $zero, $zero
    ctx->r17 = 0 | 0;
    // 0x8007B744: or          $s2, $s5, $zero
    ctx->r18 = ctx->r21 | 0;
L_8007B748:
    // 0x8007B748: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x8007B74C: jal         0x8007B220
    // 0x8007B750: or          $a1, $s2, $zero
    ctx->r5 = ctx->r18 | 0;
    func_8007B220(rdram, ctx);
        goto after_3;
    // 0x8007B750: or          $a1, $s2, $zero
    ctx->r5 = ctx->r18 | 0;
    after_3:
    // 0x8007B754: addiu       $s1, $s1, 0x10
    ctx->r17 = ADD32(ctx->r17, 0X10);
    // 0x8007B758: addiu       $s0, $s0, 0x5
    ctx->r16 = ADD32(ctx->r16, 0X5);
    // 0x8007B75C: bne         $s1, $s3, L_8007B748
    if (ctx->r17 != ctx->r19) {
        // 0x8007B760: addiu       $s2, $s2, 0x10
        ctx->r18 = ADD32(ctx->r18, 0X10);
            goto L_8007B748;
    }
    // 0x8007B760: addiu       $s2, $s2, 0x10
    ctx->r18 = ADD32(ctx->r18, 0X10);
    // 0x8007B764: addiu       $s5, $s5, 0x30
    ctx->r21 = ADD32(ctx->r21, 0X30);
    // 0x8007B768: sltu        $at, $s5, $s7
    ctx->r1 = ctx->r21 < ctx->r23 ? 1 : 0;
    // 0x8007B76C: addiu       $s4, $s4, 0x1
    ctx->r20 = ADD32(ctx->r20, 0X1);
    // 0x8007B770: bne         $at, $zero, L_8007B73C
    if (ctx->r1 != 0) {
        // 0x8007B774: addiu       $s6, $s6, 0xF
        ctx->r22 = ADD32(ctx->r22, 0XF);
            goto L_8007B73C;
    }
    // 0x8007B774: addiu       $s6, $s6, 0xF
    ctx->r22 = ADD32(ctx->r22, 0XF);
    // 0x8007B778: lui         $s2, 0x801B
    ctx->r18 = S32(0X801B << 16);
    // 0x8007B77C: lui         $s0, 0x801C
    ctx->r16 = S32(0X801C << 16);
    // 0x8007B780: lui         $s1, 0x801C
    ctx->r17 = S32(0X801C << 16);
    // 0x8007B784: addiu       $s1, $s1, 0x2464
    ctx->r17 = ADD32(ctx->r17, 0X2464);
    // 0x8007B788: addiu       $s0, $s0, 0x23C4
    ctx->r16 = ADD32(ctx->r16, 0X23C4);
    // 0x8007B78C: addiu       $s2, $s2, -0x1410
    ctx->r18 = ADD32(ctx->r18, -0X1410);
    // 0x8007B790: addiu       $s4, $zero, 0x1
    ctx->r20 = ADD32(0, 0X1);
L_8007B794:
    // 0x8007B794: or          $a0, $s2, $zero
    ctx->r4 = ctx->r18 | 0;
    // 0x8007B798: jal         0x8007B110
    // 0x8007B79C: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    func_8007B110(rdram, ctx);
        goto after_4;
    // 0x8007B79C: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    after_4:
    // 0x8007B7A0: addiu       $s0, $s0, 0x14
    ctx->r16 = ADD32(ctx->r16, 0X14);
    // 0x8007B7A4: sltu        $at, $s0, $s1
    ctx->r1 = ctx->r16 < ctx->r17 ? 1 : 0;
    // 0x8007B7A8: addiu       $s4, $s4, 0x1
    ctx->r20 = ADD32(ctx->r20, 0X1);
    // 0x8007B7AC: bne         $at, $zero, L_8007B794
    if (ctx->r1 != 0) {
        // 0x8007B7B0: addiu       $s2, $s2, 0x5
        ctx->r18 = ADD32(ctx->r18, 0X5);
            goto L_8007B794;
    }
    // 0x8007B7B0: addiu       $s2, $s2, 0x5
    ctx->r18 = ADD32(ctx->r18, 0X5);
    // 0x8007B7B4: lui         $s2, 0x801D
    ctx->r18 = S32(0X801D << 16);
    // 0x8007B7B8: lui         $s3, 0x801B
    ctx->r19 = S32(0X801B << 16);
    // 0x8007B7BC: lui         $s5, 0x801B
    ctx->r21 = S32(0X801B << 16);
    // 0x8007B7C0: addiu       $s5, $s5, -0x15D0
    ctx->r21 = ADD32(ctx->r21, -0X15D0);
    // 0x8007B7C4: addiu       $s3, $s3, -0x15D8
    ctx->r19 = ADD32(ctx->r19, -0X15D8);
    // 0x8007B7C8: addiu       $s2, $s2, -0x4D68
    ctx->r18 = ADD32(ctx->r18, -0X4D68);
    // 0x8007B7CC: or          $s1, $zero, $zero
    ctx->r17 = 0 | 0;
    // 0x8007B7D0: addiu       $s4, $zero, 0x1
    ctx->r20 = ADD32(0, 0X1);
    // 0x8007B7D4: addiu       $s0, $zero, 0x3
    ctx->r16 = ADD32(0, 0X3);
L_8007B7D8:
    // 0x8007B7D8: or          $a0, $s2, $zero
    ctx->r4 = ctx->r18 | 0;
    // 0x8007B7DC: or          $a1, $s3, $zero
    ctx->r5 = ctx->r19 | 0;
    // 0x8007B7E0: jal         0x8006A140
    // 0x8007B7E4: addiu       $a2, $zero, 0xA
    ctx->r6 = ADD32(0, 0XA);
    Libc_strncpy(rdram, ctx);
        goto after_5;
    // 0x8007B7E4: addiu       $a2, $zero, 0xA
    ctx->r6 = ADD32(0, 0XA);
    after_5:
    // 0x8007B7E8: sll         $t1, $s1, 3
    ctx->r9 = S32(ctx->r17 << 3);
    // 0x8007B7EC: subu        $t1, $t1, $s1
    ctx->r9 = SUB32(ctx->r9, ctx->r17);
    // 0x8007B7F0: lui         $t2, 0x801D
    ctx->r10 = S32(0X801D << 16);
    // 0x8007B7F4: lui         $t3, 0x801B
    ctx->r11 = S32(0X801B << 16);
    // 0x8007B7F8: sll         $t4, $s1, 2
    ctx->r12 = S32(ctx->r17 << 2);
    // 0x8007B7FC: subu        $t4, $t4, $s1
    ctx->r12 = SUB32(ctx->r12, ctx->r17);
    // 0x8007B800: addiu       $a2, $t3, -0x15E8
    ctx->r6 = ADD32(ctx->r11, -0X15E8);
    // 0x8007B804: addiu       $t2, $t2, -0x4D68
    ctx->r10 = ADD32(ctx->r10, -0X4D68);
    // 0x8007B808: sll         $t1, $t1, 1
    ctx->r9 = S32(ctx->r9 << 1);
    // 0x8007B80C: sb          $zero, 0xA($s2)
    MEM_B(0XA, ctx->r18) = 0;
    // 0x8007B810: addu        $a1, $t1, $t2
    ctx->r5 = ADD32(ctx->r9, ctx->r10);
    // 0x8007B814: addu        $a3, $t4, $a2
    ctx->r7 = ADD32(ctx->r12, ctx->r6);
L_8007B818:
    // 0x8007B818: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    // 0x8007B81C: or          $v0, $a1, $zero
    ctx->r2 = ctx->r5 | 0;
    // 0x8007B820: or          $v1, $a3, $zero
    ctx->r3 = ctx->r7 | 0;
L_8007B824:
    // 0x8007B824: lb          $t5, 0x38($v1)
    ctx->r13 = MEM_B(ctx->r3, 0X38);
    // 0x8007B828: addiu       $a0, $a0, 0x1
    ctx->r4 = ADD32(ctx->r4, 0X1);
    // 0x8007B82C: addiu       $v0, $v0, 0x1
    ctx->r2 = ADD32(ctx->r2, 0X1);
    // 0x8007B830: addiu       $v1, $v1, 0x1
    ctx->r3 = ADD32(ctx->r3, 0X1);
    // 0x8007B834: bne         $a0, $s0, L_8007B824
    if (ctx->r4 != ctx->r16) {
        // 0x8007B838: sb          $t5, 0xA($v0)
        MEM_B(0XA, ctx->r2) = ctx->r13;
            goto L_8007B824;
    }
    // 0x8007B838: sb          $t5, 0xA($v0)
    MEM_B(0XA, ctx->r2) = ctx->r13;
    // 0x8007B83C: addiu       $a2, $a2, 0xC
    ctx->r6 = ADD32(ctx->r6, 0XC);
    // 0x8007B840: sltu        $at, $a2, $s5
    ctx->r1 = ctx->r6 < ctx->r21 ? 1 : 0;
    // 0x8007B844: addiu       $a1, $a1, 0x38
    ctx->r5 = ADD32(ctx->r5, 0X38);
    // 0x8007B848: bne         $at, $zero, L_8007B818
    if (ctx->r1 != 0) {
        // 0x8007B84C: addiu       $a3, $a3, 0xC
        ctx->r7 = ADD32(ctx->r7, 0XC);
            goto L_8007B818;
    }
    // 0x8007B84C: addiu       $a3, $a3, 0xC
    ctx->r7 = ADD32(ctx->r7, 0XC);
    // 0x8007B850: or          $s1, $s4, $zero
    ctx->r17 = ctx->r20 | 0;
    // 0x8007B854: slti        $at, $s1, 0x4
    ctx->r1 = SIGNED(ctx->r17) < 0X4 ? 1 : 0;
    // 0x8007B858: addiu       $s4, $s4, 0x1
    ctx->r20 = ADD32(ctx->r20, 0X1);
    // 0x8007B85C: addiu       $s2, $s2, 0xE
    ctx->r18 = ADD32(ctx->r18, 0XE);
    // 0x8007B860: bne         $at, $zero, L_8007B7D8
    if (ctx->r1 != 0) {
        // 0x8007B864: addiu       $s3, $s3, 0xA
        ctx->r19 = ADD32(ctx->r19, 0XA);
            goto L_8007B7D8;
    }
    // 0x8007B864: addiu       $s3, $s3, 0xA
    ctx->r19 = ADD32(ctx->r19, 0XA);
    // 0x8007B868: lui         $t6, 0x801B
    ctx->r14 = S32(0X801B << 16);
    // 0x8007B86C: lb          $t6, -0x15DC($t6)
    ctx->r14 = MEM_B(ctx->r14, -0X15DC);
    // 0x8007B870: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x8007B874: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x8007B878: lui         $v0, 0x801B
    ctx->r2 = S32(0X801B << 16);
    // 0x8007B87C: lui         $a0, 0x801B
    ctx->r4 = S32(0X801B << 16);
    // 0x8007B880: addiu       $a0, $a0, -0x15E4
    ctx->r4 = ADD32(ctx->r4, -0X15E4);
    // 0x8007B884: addiu       $v0, $v0, -0x15E8
    ctx->r2 = ADD32(ctx->r2, -0X15E8);
    // 0x8007B888: addiu       $v1, $v1, -0x4D78
    ctx->r3 = ADD32(ctx->r3, -0X4D78);
    // 0x8007B88C: addiu       $s4, $zero, 0x1
    ctx->r20 = ADD32(0, 0X1);
    // 0x8007B890: sb          $t6, -0x4D80($at)
    MEM_B(-0X4D80, ctx->r1) = ctx->r14;
L_8007B894:
    // 0x8007B894: lb          $t7, 0x8($v0)
    ctx->r15 = MEM_B(ctx->r2, 0X8);
    // 0x8007B898: addiu       $v0, $v0, 0x1
    ctx->r2 = ADD32(ctx->r2, 0X1);
    // 0x8007B89C: sltu        $at, $v0, $a0
    ctx->r1 = ctx->r2 < ctx->r4 ? 1 : 0;
    // 0x8007B8A0: addiu       $s4, $s4, 0x1
    ctx->r20 = ADD32(ctx->r20, 0X1);
    // 0x8007B8A4: addiu       $v1, $v1, 0x4
    ctx->r3 = ADD32(ctx->r3, 0X4);
    // 0x8007B8A8: bne         $at, $zero, L_8007B894
    if (ctx->r1 != 0) {
        // 0x8007B8AC: sw          $t7, -0x4($v1)
        MEM_W(-0X4, ctx->r3) = ctx->r15;
            goto L_8007B894;
    }
    // 0x8007B8AC: sw          $t7, -0x4($v1)
    MEM_W(-0X4, ctx->r3) = ctx->r15;
    // 0x8007B8B0: lui         $a2, 0x801D
    ctx->r6 = S32(0X801D << 16);
    // 0x8007B8B4: lui         $a1, 0x801B
    ctx->r5 = S32(0X801B << 16);
    // 0x8007B8B8: lui         $a3, 0x801B
    ctx->r7 = S32(0X801B << 16);
    // 0x8007B8BC: addiu       $a3, $a3, -0x15DF
    ctx->r7 = ADD32(ctx->r7, -0X15DF);
    // 0x8007B8C0: addiu       $a1, $a1, -0x15E8
    ctx->r5 = ADD32(ctx->r5, -0X15E8);
    // 0x8007B8C4: addiu       $a2, $a2, -0x4CF8
    ctx->r6 = ADD32(ctx->r6, -0X4CF8);
    // 0x8007B8C8: addiu       $s4, $zero, 0x1
    ctx->r20 = ADD32(0, 0X1);
L_8007B8CC:
    // 0x8007B8CC: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    // 0x8007B8D0: or          $v0, $a2, $zero
    ctx->r2 = ctx->r6 | 0;
    // 0x8007B8D4: or          $v1, $a1, $zero
    ctx->r3 = ctx->r5 | 0;
L_8007B8D8:
    // 0x8007B8D8: lb          $t8, 0x50($v1)
    ctx->r24 = MEM_B(ctx->r3, 0X50);
    // 0x8007B8DC: addiu       $a0, $a0, 0x1
    ctx->r4 = ADD32(ctx->r4, 0X1);
    // 0x8007B8E0: addiu       $v0, $v0, 0x4
    ctx->r2 = ADD32(ctx->r2, 0X4);
    // 0x8007B8E4: addiu       $v1, $v1, 0x1
    ctx->r3 = ADD32(ctx->r3, 0X1);
    // 0x8007B8E8: bne         $a0, $s0, L_8007B8D8
    if (ctx->r4 != ctx->r16) {
        // 0x8007B8EC: sw          $t8, -0x4($v0)
        MEM_W(-0X4, ctx->r2) = ctx->r24;
            goto L_8007B8D8;
    }
    // 0x8007B8EC: sw          $t8, -0x4($v0)
    MEM_W(-0X4, ctx->r2) = ctx->r24;
    // 0x8007B8F0: addiu       $a1, $a1, 0x3
    ctx->r5 = ADD32(ctx->r5, 0X3);
    // 0x8007B8F4: addiu       $s4, $s4, 0x1
    ctx->r20 = ADD32(ctx->r20, 0X1);
    // 0x8007B8F8: bne         $a1, $a3, L_8007B8CC
    if (ctx->r5 != ctx->r7) {
        // 0x8007B8FC: addiu       $a2, $a2, 0xC
        ctx->r6 = ADD32(ctx->r6, 0XC);
            goto L_8007B8CC;
    }
    // 0x8007B8FC: addiu       $a2, $a2, 0xC
    ctx->r6 = ADD32(ctx->r6, 0XC);
    // 0x8007B900: lw          $ra, 0x3C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X3C);
    // 0x8007B904: lw          $s0, 0x18($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X18);
    // 0x8007B908: lw          $s1, 0x1C($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X1C);
    // 0x8007B90C: lw          $s2, 0x20($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X20);
    // 0x8007B910: lw          $s3, 0x24($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X24);
    // 0x8007B914: lw          $s4, 0x28($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X28);
    // 0x8007B918: lw          $s5, 0x2C($sp)
    ctx->r21 = MEM_W(ctx->r29, 0X2C);
    // 0x8007B91C: lw          $s6, 0x30($sp)
    ctx->r22 = MEM_W(ctx->r29, 0X30);
    // 0x8007B920: lw          $s7, 0x34($sp)
    ctx->r23 = MEM_W(ctx->r29, 0X34);
    // 0x8007B924: lw          $fp, 0x38($sp)
    ctx->r30 = MEM_W(ctx->r29, 0X38);
    // 0x8007B928: jr          $ra
    // 0x8007B92C: addiu       $sp, $sp, 0x88
    ctx->r29 = ADD32(ctx->r29, 0X88);
    return;
    // 0x8007B92C: addiu       $sp, $sp, 0x88
    ctx->r29 = ADD32(ctx->r29, 0X88);
;}
RECOMP_FUNC void func_8007B930(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8007B930: addiu       $sp, $sp, -0x78
    ctx->r29 = ADD32(ctx->r29, -0X78);
    // 0x8007B934: sw          $fp, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r30;
    // 0x8007B938: sw          $s7, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r23;
    // 0x8007B93C: sw          $s4, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r20;
    // 0x8007B940: lui         $t6, 0x801B
    ctx->r14 = S32(0X801B << 16);
    // 0x8007B944: lui         $t7, 0x801C
    ctx->r15 = S32(0X801C << 16);
    // 0x8007B948: sw          $s6, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r22;
    // 0x8007B94C: sw          $s5, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r21;
    // 0x8007B950: sw          $s3, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r19;
    // 0x8007B954: addiu       $t7, $t7, 0x22D4
    ctx->r15 = ADD32(ctx->r15, 0X22D4);
    // 0x8007B958: addiu       $s7, $t6, -0x15E8
    ctx->r23 = ADD32(ctx->r14, -0X15E8);
    // 0x8007B95C: lui         $s4, 0x801C
    ctx->r20 = S32(0X801C << 16);
    // 0x8007B960: lui         $fp, 0x801C
    ctx->r30 = S32(0X801C << 16);
    // 0x8007B964: sw          $ra, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r31;
    // 0x8007B968: sw          $s2, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r18;
    // 0x8007B96C: sw          $s1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r17;
    // 0x8007B970: sw          $s0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r16;
    // 0x8007B974: addiu       $fp, $fp, 0x24C4
    ctx->r30 = ADD32(ctx->r30, 0X24C4);
    // 0x8007B978: addiu       $s4, $s4, 0x202C
    ctx->r20 = ADD32(ctx->r20, 0X202C);
    // 0x8007B97C: or          $s6, $s7, $zero
    ctx->r22 = ctx->r23 | 0;
    // 0x8007B980: sw          $t7, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r15;
    // 0x8007B984: addiu       $s3, $zero, 0x6
    ctx->r19 = ADD32(0, 0X6);
    // 0x8007B988: addiu       $s5, $zero, 0x1
    ctx->r21 = ADD32(0, 0X1);
L_8007B98C:
    // 0x8007B98C: or          $s1, $zero, $zero
    ctx->r17 = 0 | 0;
    // 0x8007B990: addiu       $s0, $s6, 0x60
    ctx->r16 = ADD32(ctx->r22, 0X60);
    // 0x8007B994: or          $s2, $s4, $zero
    ctx->r18 = ctx->r20 | 0;
L_8007B998:
    // 0x8007B998: or          $a0, $s2, $zero
    ctx->r4 = ctx->r18 | 0;
    // 0x8007B99C: jal         0x8007AF78
    // 0x8007B9A0: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    func_8007AF78(rdram, ctx);
        goto after_0;
    // 0x8007B9A0: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    after_0:
    // 0x8007B9A4: addiu       $s1, $s1, 0x6
    ctx->r17 = ADD32(ctx->r17, 0X6);
    // 0x8007B9A8: slti        $at, $s1, 0x12
    ctx->r1 = SIGNED(ctx->r17) < 0X12 ? 1 : 0;
    // 0x8007B9AC: addiu       $s0, $s0, 0x6
    ctx->r16 = ADD32(ctx->r16, 0X6);
    // 0x8007B9B0: bne         $at, $zero, L_8007B998
    if (ctx->r1 != 0) {
        // 0x8007B9B4: addiu       $s2, $s2, 0x14
        ctx->r18 = ADD32(ctx->r18, 0X14);
            goto L_8007B998;
    }
    // 0x8007B9B4: addiu       $s2, $s2, 0x14
    ctx->r18 = ADD32(ctx->r18, 0X14);
    // 0x8007B9B8: lw          $a0, 0x44($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X44);
    // 0x8007B9BC: jal         0x8007AF78
    // 0x8007B9C0: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    func_8007AF78(rdram, ctx);
        goto after_1;
    // 0x8007B9C0: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    after_1:
    // 0x8007B9C4: or          $s0, $zero, $zero
    ctx->r16 = 0 | 0;
    // 0x8007B9C8: addiu       $s1, $s7, 0x1A8
    ctx->r17 = ADD32(ctx->r23, 0X1A8);
    // 0x8007B9CC: or          $s2, $fp, $zero
    ctx->r18 = ctx->r30 | 0;
L_8007B9D0:
    // 0x8007B9D0: lw          $a0, 0x0($s2)
    ctx->r4 = MEM_W(ctx->r18, 0X0);
    // 0x8007B9D4: jal         0x8007B2BC
    // 0x8007B9D8: or          $a1, $s1, $zero
    ctx->r5 = ctx->r17 | 0;
    func_8007B2BC(rdram, ctx);
        goto after_2;
    // 0x8007B9D8: or          $a1, $s1, $zero
    ctx->r5 = ctx->r17 | 0;
    after_2:
    // 0x8007B9DC: addiu       $s0, $s0, 0x3
    ctx->r16 = ADD32(ctx->r16, 0X3);
    // 0x8007B9E0: addiu       $s1, $s1, 0x3
    ctx->r17 = ADD32(ctx->r17, 0X3);
    // 0x8007B9E4: bne         $s0, $s3, L_8007B9D0
    if (ctx->r16 != ctx->r19) {
        // 0x8007B9E8: addiu       $s2, $s2, 0x4
        ctx->r18 = ADD32(ctx->r18, 0X4);
            goto L_8007B9D0;
    }
    // 0x8007B9E8: addiu       $s2, $s2, 0x4
    ctx->r18 = ADD32(ctx->r18, 0X4);
    // 0x8007B9EC: lw          $t8, 0x44($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X44);
    // 0x8007B9F0: lui         $t0, 0x801C
    ctx->r8 = S32(0X801C << 16);
    // 0x8007B9F4: addiu       $t0, $t0, 0x220C
    ctx->r8 = ADD32(ctx->r8, 0X220C);
    // 0x8007B9F8: addiu       $s4, $s4, 0x3C
    ctx->r20 = ADD32(ctx->r20, 0X3C);
    // 0x8007B9FC: sltu        $at, $s4, $t0
    ctx->r1 = ctx->r20 < ctx->r8 ? 1 : 0;
    // 0x8007BA00: addiu       $t9, $t8, 0x14
    ctx->r25 = ADD32(ctx->r24, 0X14);
    // 0x8007BA04: sw          $t9, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r25;
    // 0x8007BA08: addiu       $s5, $s5, 0x1
    ctx->r21 = ADD32(ctx->r21, 0X1);
    // 0x8007BA0C: addiu       $s6, $s6, 0x18
    ctx->r22 = ADD32(ctx->r22, 0X18);
    // 0x8007BA10: addiu       $s7, $s7, 0x6
    ctx->r23 = ADD32(ctx->r23, 0X6);
    // 0x8007BA14: bne         $at, $zero, L_8007B98C
    if (ctx->r1 != 0) {
        // 0x8007BA18: addiu       $fp, $fp, 0x24
        ctx->r30 = ADD32(ctx->r30, 0X24);
            goto L_8007B98C;
    }
    // 0x8007BA18: addiu       $fp, $fp, 0x24
    ctx->r30 = ADD32(ctx->r30, 0X24);
    // 0x8007BA1C: lui         $s6, 0x801C
    ctx->r22 = S32(0X801C << 16);
    // 0x8007BA20: lui         $s4, 0x801B
    ctx->r20 = S32(0X801B << 16);
    // 0x8007BA24: lui         $s7, 0x801B
    ctx->r23 = S32(0X801B << 16);
    // 0x8007BA28: addiu       $s7, $s7, -0x1561
    ctx->r23 = ADD32(ctx->r23, -0X1561);
    // 0x8007BA2C: addiu       $s4, $s4, -0x15E8
    ctx->r20 = ADD32(ctx->r20, -0X15E8);
    // 0x8007BA30: addiu       $s6, $s6, 0x26E8
    ctx->r22 = ADD32(ctx->r22, 0X26E8);
    // 0x8007BA34: addiu       $s5, $zero, 0x1
    ctx->r21 = ADD32(0, 0X1);
    // 0x8007BA38: addiu       $s3, $zero, 0xF
    ctx->r19 = ADD32(0, 0XF);
L_8007BA3C:
    // 0x8007BA3C: or          $s0, $s6, $zero
    ctx->r16 = ctx->r22 | 0;
    // 0x8007BA40: or          $s1, $zero, $zero
    ctx->r17 = 0 | 0;
    // 0x8007BA44: addiu       $s2, $s4, 0x120
    ctx->r18 = ADD32(ctx->r20, 0X120);
L_8007BA48:
    // 0x8007BA48: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x8007BA4C: jal         0x8007B1AC
    // 0x8007BA50: or          $a1, $s2, $zero
    ctx->r5 = ctx->r18 | 0;
    func_8007B1AC(rdram, ctx);
        goto after_3;
    // 0x8007BA50: or          $a1, $s2, $zero
    ctx->r5 = ctx->r18 | 0;
    after_3:
    // 0x8007BA54: addiu       $s1, $s1, 0x5
    ctx->r17 = ADD32(ctx->r17, 0X5);
    // 0x8007BA58: addiu       $s0, $s0, 0x10
    ctx->r16 = ADD32(ctx->r16, 0X10);
    // 0x8007BA5C: bne         $s1, $s3, L_8007BA48
    if (ctx->r17 != ctx->r19) {
        // 0x8007BA60: addiu       $s2, $s2, 0x5
        ctx->r18 = ADD32(ctx->r18, 0X5);
            goto L_8007BA48;
    }
    // 0x8007BA60: addiu       $s2, $s2, 0x5
    ctx->r18 = ADD32(ctx->r18, 0X5);
    // 0x8007BA64: addiu       $s4, $s4, 0xF
    ctx->r20 = ADD32(ctx->r20, 0XF);
    // 0x8007BA68: sltu        $at, $s4, $s7
    ctx->r1 = ctx->r20 < ctx->r23 ? 1 : 0;
    // 0x8007BA6C: addiu       $s5, $s5, 0x1
    ctx->r21 = ADD32(ctx->r21, 0X1);
    // 0x8007BA70: bne         $at, $zero, L_8007BA3C
    if (ctx->r1 != 0) {
        // 0x8007BA74: addiu       $s6, $s6, 0x30
        ctx->r22 = ADD32(ctx->r22, 0X30);
            goto L_8007BA3C;
    }
    // 0x8007BA74: addiu       $s6, $s6, 0x30
    ctx->r22 = ADD32(ctx->r22, 0X30);
    // 0x8007BA78: lui         $s1, 0x801C
    ctx->r17 = S32(0X801C << 16);
    // 0x8007BA7C: lui         $s0, 0x801B
    ctx->r16 = S32(0X801B << 16);
    // 0x8007BA80: lui         $s2, 0x801B
    ctx->r18 = S32(0X801B << 16);
    // 0x8007BA84: addiu       $s2, $s2, -0x13E8
    ctx->r18 = ADD32(ctx->r18, -0X13E8);
    // 0x8007BA88: addiu       $s0, $s0, -0x1410
    ctx->r16 = ADD32(ctx->r16, -0X1410);
    // 0x8007BA8C: addiu       $s1, $s1, 0x23C4
    ctx->r17 = ADD32(ctx->r17, 0X23C4);
    // 0x8007BA90: addiu       $s5, $zero, 0x1
    ctx->r21 = ADD32(0, 0X1);
L_8007BA94:
    // 0x8007BA94: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    // 0x8007BA98: jal         0x8007B09C
    // 0x8007BA9C: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    func_8007B09C(rdram, ctx);
        goto after_4;
    // 0x8007BA9C: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    after_4:
    // 0x8007BAA0: addiu       $s0, $s0, 0x5
    ctx->r16 = ADD32(ctx->r16, 0X5);
    // 0x8007BAA4: sltu        $at, $s0, $s2
    ctx->r1 = ctx->r16 < ctx->r18 ? 1 : 0;
    // 0x8007BAA8: addiu       $s5, $s5, 0x1
    ctx->r21 = ADD32(ctx->r21, 0X1);
    // 0x8007BAAC: bne         $at, $zero, L_8007BA94
    if (ctx->r1 != 0) {
        // 0x8007BAB0: addiu       $s1, $s1, 0x14
        ctx->r17 = ADD32(ctx->r17, 0X14);
            goto L_8007BA94;
    }
    // 0x8007BAB0: addiu       $s1, $s1, 0x14
    ctx->r17 = ADD32(ctx->r17, 0X14);
    // 0x8007BAB4: lui         $s3, 0x801B
    ctx->r19 = S32(0X801B << 16);
    // 0x8007BAB8: lui         $s4, 0x801D
    ctx->r20 = S32(0X801D << 16);
    // 0x8007BABC: lui         $s1, 0x801D
    ctx->r17 = S32(0X801D << 16);
    // 0x8007BAC0: addiu       $s1, $s1, -0x4CF8
    ctx->r17 = ADD32(ctx->r17, -0X4CF8);
    // 0x8007BAC4: addiu       $s4, $s4, -0x4D68
    ctx->r20 = ADD32(ctx->r20, -0X4D68);
    // 0x8007BAC8: addiu       $s3, $s3, -0x15D8
    ctx->r19 = ADD32(ctx->r19, -0X15D8);
    // 0x8007BACC: or          $s2, $zero, $zero
    ctx->r18 = 0 | 0;
    // 0x8007BAD0: addiu       $s5, $zero, 0x1
    ctx->r21 = ADD32(0, 0X1);
    // 0x8007BAD4: addiu       $s0, $zero, 0x3
    ctx->r16 = ADD32(0, 0X3);
L_8007BAD8:
    // 0x8007BAD8: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
    // 0x8007BADC: or          $a1, $s4, $zero
    ctx->r5 = ctx->r20 | 0;
    // 0x8007BAE0: jal         0x8006A140
    // 0x8007BAE4: addiu       $a2, $zero, 0xA
    ctx->r6 = ADD32(0, 0XA);
    Libc_strncpy(rdram, ctx);
        goto after_5;
    // 0x8007BAE4: addiu       $a2, $zero, 0xA
    ctx->r6 = ADD32(0, 0XA);
    after_5:
    // 0x8007BAE8: sll         $t4, $s2, 3
    ctx->r12 = S32(ctx->r18 << 3);
    // 0x8007BAEC: subu        $t4, $t4, $s2
    ctx->r12 = SUB32(ctx->r12, ctx->r18);
    // 0x8007BAF0: sll         $t1, $s2, 2
    ctx->r9 = S32(ctx->r18 << 2);
    // 0x8007BAF4: lui         $t2, 0x801B
    ctx->r10 = S32(0X801B << 16);
    // 0x8007BAF8: lui         $t3, 0x801D
    ctx->r11 = S32(0X801D << 16);
    // 0x8007BAFC: addiu       $a2, $t3, -0x4D68
    ctx->r6 = ADD32(ctx->r11, -0X4D68);
    // 0x8007BB00: addiu       $t2, $t2, -0x15E8
    ctx->r10 = ADD32(ctx->r10, -0X15E8);
    // 0x8007BB04: subu        $t1, $t1, $s2
    ctx->r9 = SUB32(ctx->r9, ctx->r18);
    // 0x8007BB08: sll         $t4, $t4, 1
    ctx->r12 = S32(ctx->r12 << 1);
    // 0x8007BB0C: addu        $a3, $t4, $a2
    ctx->r7 = ADD32(ctx->r12, ctx->r6);
    // 0x8007BB10: addu        $a1, $t1, $t2
    ctx->r5 = ADD32(ctx->r9, ctx->r10);
L_8007BB14:
    // 0x8007BB14: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    // 0x8007BB18: or          $v0, $a1, $zero
    ctx->r2 = ctx->r5 | 0;
    // 0x8007BB1C: or          $v1, $a3, $zero
    ctx->r3 = ctx->r7 | 0;
L_8007BB20:
    // 0x8007BB20: lb          $t5, 0xB($v1)
    ctx->r13 = MEM_B(ctx->r3, 0XB);
    // 0x8007BB24: addiu       $a0, $a0, 0x1
    ctx->r4 = ADD32(ctx->r4, 0X1);
    // 0x8007BB28: addiu       $v0, $v0, 0x1
    ctx->r2 = ADD32(ctx->r2, 0X1);
    // 0x8007BB2C: addiu       $v1, $v1, 0x1
    ctx->r3 = ADD32(ctx->r3, 0X1);
    // 0x8007BB30: bne         $a0, $s0, L_8007BB20
    if (ctx->r4 != ctx->r16) {
        // 0x8007BB34: sb          $t5, 0x37($v0)
        MEM_B(0X37, ctx->r2) = ctx->r13;
            goto L_8007BB20;
    }
    // 0x8007BB34: sb          $t5, 0x37($v0)
    MEM_B(0X37, ctx->r2) = ctx->r13;
    // 0x8007BB38: addiu       $a2, $a2, 0x38
    ctx->r6 = ADD32(ctx->r6, 0X38);
    // 0x8007BB3C: addiu       $a1, $a1, 0xC
    ctx->r5 = ADD32(ctx->r5, 0XC);
    // 0x8007BB40: bne         $a2, $s1, L_8007BB14
    if (ctx->r6 != ctx->r17) {
        // 0x8007BB44: addiu       $a3, $a3, 0x38
        ctx->r7 = ADD32(ctx->r7, 0X38);
            goto L_8007BB14;
    }
    // 0x8007BB44: addiu       $a3, $a3, 0x38
    ctx->r7 = ADD32(ctx->r7, 0X38);
    // 0x8007BB48: or          $s2, $s5, $zero
    ctx->r18 = ctx->r21 | 0;
    // 0x8007BB4C: slti        $at, $s2, 0x4
    ctx->r1 = SIGNED(ctx->r18) < 0X4 ? 1 : 0;
    // 0x8007BB50: addiu       $s5, $s5, 0x1
    ctx->r21 = ADD32(ctx->r21, 0X1);
    // 0x8007BB54: addiu       $s3, $s3, 0xA
    ctx->r19 = ADD32(ctx->r19, 0XA);
    // 0x8007BB58: bne         $at, $zero, L_8007BAD8
    if (ctx->r1 != 0) {
        // 0x8007BB5C: addiu       $s4, $s4, 0xE
        ctx->r20 = ADD32(ctx->r20, 0XE);
            goto L_8007BAD8;
    }
    // 0x8007BB5C: addiu       $s4, $s4, 0xE
    ctx->r20 = ADD32(ctx->r20, 0XE);
    // 0x8007BB60: jal         0x8007B31C
    // 0x8007BB64: nop

    func_8007B31C(rdram, ctx);
        goto after_6;
    // 0x8007BB64: nop

    after_6:
    // 0x8007BB68: lui         $a2, 0x801B
    ctx->r6 = S32(0X801B << 16);
    // 0x8007BB6C: lui         $a1, 0x801D
    ctx->r5 = S32(0X801D << 16);
    // 0x8007BB70: lui         $a3, 0x801D
    ctx->r7 = S32(0X801D << 16);
    // 0x8007BB74: addiu       $a3, $a3, -0x4CD4
    ctx->r7 = ADD32(ctx->r7, -0X4CD4);
    // 0x8007BB78: addiu       $a1, $a1, -0x4CF8
    ctx->r5 = ADD32(ctx->r5, -0X4CF8);
    // 0x8007BB7C: addiu       $a2, $a2, -0x15E8
    ctx->r6 = ADD32(ctx->r6, -0X15E8);
    // 0x8007BB80: addiu       $s5, $zero, 0x1
    ctx->r21 = ADD32(0, 0X1);
L_8007BB84:
    // 0x8007BB84: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    // 0x8007BB88: or          $v0, $a2, $zero
    ctx->r2 = ctx->r6 | 0;
    // 0x8007BB8C: or          $v1, $a1, $zero
    ctx->r3 = ctx->r5 | 0;
L_8007BB90:
    // 0x8007BB90: lw          $t6, 0x0($v1)
    ctx->r14 = MEM_W(ctx->r3, 0X0);
    // 0x8007BB94: addiu       $a0, $a0, 0x1
    ctx->r4 = ADD32(ctx->r4, 0X1);
    // 0x8007BB98: addiu       $v0, $v0, 0x1
    ctx->r2 = ADD32(ctx->r2, 0X1);
    // 0x8007BB9C: addiu       $v1, $v1, 0x4
    ctx->r3 = ADD32(ctx->r3, 0X4);
    // 0x8007BBA0: bne         $a0, $s0, L_8007BB90
    if (ctx->r4 != ctx->r16) {
        // 0x8007BBA4: sb          $t6, 0x4F($v0)
        MEM_B(0X4F, ctx->r2) = ctx->r14;
            goto L_8007BB90;
    }
    // 0x8007BBA4: sb          $t6, 0x4F($v0)
    MEM_B(0X4F, ctx->r2) = ctx->r14;
    // 0x8007BBA8: addiu       $a1, $a1, 0xC
    ctx->r5 = ADD32(ctx->r5, 0XC);
    // 0x8007BBAC: addiu       $s5, $s5, 0x1
    ctx->r21 = ADD32(ctx->r21, 0X1);
    // 0x8007BBB0: bne         $a1, $a3, L_8007BB84
    if (ctx->r5 != ctx->r7) {
        // 0x8007BBB4: addiu       $a2, $a2, 0x3
        ctx->r6 = ADD32(ctx->r6, 0X3);
            goto L_8007BB84;
    }
    // 0x8007BBB4: addiu       $a2, $a2, 0x3
    ctx->r6 = ADD32(ctx->r6, 0X3);
    // 0x8007BBB8: lw          $ra, 0x3C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X3C);
    // 0x8007BBBC: lw          $s0, 0x18($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X18);
    // 0x8007BBC0: lw          $s1, 0x1C($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X1C);
    // 0x8007BBC4: lw          $s2, 0x20($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X20);
    // 0x8007BBC8: lw          $s3, 0x24($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X24);
    // 0x8007BBCC: lw          $s4, 0x28($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X28);
    // 0x8007BBD0: lw          $s5, 0x2C($sp)
    ctx->r21 = MEM_W(ctx->r29, 0X2C);
    // 0x8007BBD4: lw          $s6, 0x30($sp)
    ctx->r22 = MEM_W(ctx->r29, 0X30);
    // 0x8007BBD8: lw          $s7, 0x34($sp)
    ctx->r23 = MEM_W(ctx->r29, 0X34);
    // 0x8007BBDC: lw          $fp, 0x38($sp)
    ctx->r30 = MEM_W(ctx->r29, 0X38);
    // 0x8007BBE0: jr          $ra
    // 0x8007BBE4: addiu       $sp, $sp, 0x78
    ctx->r29 = ADD32(ctx->r29, 0X78);
    return;
    // 0x8007BBE4: addiu       $sp, $sp, 0x78
    ctx->r29 = ADD32(ctx->r29, 0X78);
;}
RECOMP_FUNC void func_8007BBE8(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8007BBE8: jr          $ra
    // 0x8007BBEC: nop

    return;
    // 0x8007BBEC: nop

;}
RECOMP_FUNC void func_8007BBF0(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8007BBF0: jr          $ra
    // 0x8007BBF4: nop

    return;
    // 0x8007BBF4: nop

;}
RECOMP_FUNC void Save_GenCheckSum(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8007BBF8: addiu       $v0, $a0, 0x4
    ctx->r2 = ADD32(ctx->r4, 0X4);
    // 0x8007BBFC: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
    // 0x8007BC00: addiu       $a0, $zero, 0x1FC
    ctx->r4 = ADD32(0, 0X1FC);
    // 0x8007BC04: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
L_8007BC08:
    // 0x8007BC08: lbu         $t6, 0x0($v0)
    ctx->r14 = MEM_BU(ctx->r2, 0X0);
    // 0x8007BC0C: lbu         $t8, 0x1($v0)
    ctx->r24 = MEM_BU(ctx->r2, 0X1);
    // 0x8007BC10: lbu         $t0, 0x2($v0)
    ctx->r8 = MEM_BU(ctx->r2, 0X2);
    // 0x8007BC14: lbu         $t2, 0x3($v0)
    ctx->r10 = MEM_BU(ctx->r2, 0X3);
    // 0x8007BC18: addu        $t7, $v1, $t6
    ctx->r15 = ADD32(ctx->r3, ctx->r14);
    // 0x8007BC1C: addu        $t9, $t7, $t8
    ctx->r25 = ADD32(ctx->r15, ctx->r24);
    // 0x8007BC20: addu        $t1, $t9, $t0
    ctx->r9 = ADD32(ctx->r25, ctx->r8);
    // 0x8007BC24: addu        $v1, $t1, $t2
    ctx->r3 = ADD32(ctx->r9, ctx->r10);
    // 0x8007BC28: andi        $t3, $v1, 0xFFFF
    ctx->r11 = ctx->r3 & 0XFFFF;
    // 0x8007BC2C: addiu       $a1, $a1, 0x4
    ctx->r5 = ADD32(ctx->r5, 0X4);
    // 0x8007BC30: or          $v1, $t3, $zero
    ctx->r3 = ctx->r11 | 0;
    // 0x8007BC34: bne         $a1, $a0, L_8007BC08
    if (ctx->r5 != ctx->r4) {
        // 0x8007BC38: addiu       $v0, $v0, 0x4
        ctx->r2 = ADD32(ctx->r2, 0X4);
            goto L_8007BC08;
    }
    // 0x8007BC38: addiu       $v0, $v0, 0x4
    ctx->r2 = ADD32(ctx->r2, 0X4);
    // 0x8007BC3C: jr          $ra
    // 0x8007BC40: or          $v0, $t3, $zero
    ctx->r2 = ctx->r11 | 0;
    return;
    // 0x8007BC40: or          $v0, $t3, $zero
    ctx->r2 = ctx->r11 | 0;
;}
RECOMP_FUNC void func_8007BC44(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8007BC44: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x8007BC48: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x8007BC4C: lui         $a0, 0x8015
    ctx->r4 = S32(0X8015 << 16);
    // 0x8007BC50: lui         $a2, 0x801B
    ctx->r6 = S32(0X801B << 16);
    // 0x8007BC54: addiu       $a2, $a2, -0x15E8
    ctx->r6 = ADD32(ctx->r6, -0X15E8);
    // 0x8007BC58: addiu       $a0, $a0, 0x40D0
    ctx->r4 = ADD32(ctx->r4, 0X40D0);
    // 0x8007BC5C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x8007BC60: jal         0x800C82D0
    // 0x8007BC64: addiu       $a3, $zero, 0x200
    ctx->r7 = ADD32(0, 0X200);
    osEepromLongRead_recomp(rdram, ctx);
        goto after_0;
    // 0x8007BC64: addiu       $a3, $zero, 0x200
    ctx->r7 = ADD32(0, 0X200);
    after_0:
    // 0x8007BC68: beq         $v0, $zero, L_8007BC78
    if (ctx->r2 == 0) {
        // 0x8007BC6C: or          $a1, $zero, $zero
        ctx->r5 = 0 | 0;
            goto L_8007BC78;
    }
    // 0x8007BC6C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x8007BC70: b           L_8007BD10
    // 0x8007BC74: addiu       $v0, $zero, 0x2
    ctx->r2 = ADD32(0, 0X2);
        goto L_8007BD10;
    // 0x8007BC74: addiu       $v0, $zero, 0x2
    ctx->r2 = ADD32(0, 0X2);
L_8007BC78:
    // 0x8007BC78: lui         $v1, 0x801B
    ctx->r3 = S32(0X801B << 16);
    // 0x8007BC7C: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x8007BC80: lui         $a0, 0x800E
    ctx->r4 = S32(0X800E << 16);
    // 0x8007BC84: addiu       $a0, $a0, -0x7D96
    ctx->r4 = ADD32(ctx->r4, -0X7D96);
    // 0x8007BC88: addiu       $v0, $v0, -0x7D98
    ctx->r2 = ADD32(ctx->r2, -0X7D98);
    // 0x8007BC8C: addiu       $v1, $v1, -0x15E8
    ctx->r3 = ADD32(ctx->r3, -0X15E8);
L_8007BC90:
    // 0x8007BC90: lbu         $t6, 0x0($v1)
    ctx->r14 = MEM_BU(ctx->r3, 0X0);
    // 0x8007BC94: lbu         $t7, 0x0($v0)
    ctx->r15 = MEM_BU(ctx->r2, 0X0);
    // 0x8007BC98: addiu       $v0, $v0, 0x1
    ctx->r2 = ADD32(ctx->r2, 0X1);
    // 0x8007BC9C: beq         $t6, $t7, L_8007BCAC
    if (ctx->r14 == ctx->r15) {
        // 0x8007BCA0: nop
    
            goto L_8007BCAC;
    }
    // 0x8007BCA0: nop

    // 0x8007BCA4: b           L_8007BCB4
    // 0x8007BCA8: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
        goto L_8007BCB4;
    // 0x8007BCA8: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
L_8007BCAC:
    // 0x8007BCAC: bne         $v0, $a0, L_8007BC90
    if (ctx->r2 != ctx->r4) {
        // 0x8007BCB0: addiu       $v1, $v1, 0x1
        ctx->r3 = ADD32(ctx->r3, 0X1);
            goto L_8007BC90;
    }
    // 0x8007BCB0: addiu       $v1, $v1, 0x1
    ctx->r3 = ADD32(ctx->r3, 0X1);
L_8007BCB4:
    // 0x8007BCB4: bne         $a1, $zero, L_8007BCEC
    if (ctx->r5 != 0) {
        // 0x8007BCB8: lui         $a0, 0x801B
        ctx->r4 = S32(0X801B << 16);
            goto L_8007BCEC;
    }
    // 0x8007BCB8: lui         $a0, 0x801B
    ctx->r4 = S32(0X801B << 16);
    // 0x8007BCBC: addiu       $a0, $a0, -0x15E8
    ctx->r4 = ADD32(ctx->r4, -0X15E8);
    // 0x8007BCC0: jal         0x8007BBF8
    // 0x8007BCC4: sw          $a1, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r5;
    Save_GenCheckSum(rdram, ctx);
        goto after_1;
    // 0x8007BCC4: sw          $a1, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r5;
    after_1:
    // 0x8007BCC8: lui         $t8, 0x801B
    ctx->r24 = S32(0X801B << 16);
    // 0x8007BCCC: lhu         $t8, -0x15E6($t8)
    ctx->r24 = MEM_HU(ctx->r24, -0X15E6);
    // 0x8007BCD0: lw          $a1, 0x18($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X18);
    // 0x8007BCD4: beq         $v0, $t8, L_8007BCEC
    if (ctx->r2 == ctx->r24) {
        // 0x8007BCD8: nop
    
            goto L_8007BCEC;
    }
    // 0x8007BCD8: nop

    // 0x8007BCDC: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x8007BCE0: jal         0x8007BBF0
    // 0x8007BCE4: sw          $a1, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r5;
    func_8007BBF0(rdram, ctx);
        goto after_2;
    // 0x8007BCE4: sw          $a1, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r5;
    after_2:
    // 0x8007BCE8: lw          $a1, 0x18($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X18);
L_8007BCEC:
    // 0x8007BCEC: beql        $a1, $zero, L_8007BD10
    if (ctx->r5 == 0) {
        // 0x8007BCF0: or          $v0, $zero, $zero
        ctx->r2 = 0 | 0;
            goto L_8007BD10;
    }
    goto skip_0;
    // 0x8007BCF0: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    skip_0:
    // 0x8007BCF4: jal         0x8007BDB8
    // 0x8007BCF8: nop

    func_8007BDB8(rdram, ctx);
        goto after_3;
    // 0x8007BCF8: nop

    after_3:
    // 0x8007BCFC: beql        $v0, $zero, L_8007BD10
    if (ctx->r2 == 0) {
        // 0x8007BD00: or          $v0, $zero, $zero
        ctx->r2 = 0 | 0;
            goto L_8007BD10;
    }
    goto skip_1;
    // 0x8007BD00: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    skip_1:
    // 0x8007BD04: b           L_8007BD14
    // 0x8007BD08: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_8007BD14;
    // 0x8007BD08: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x8007BD0C: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_8007BD10:
    // 0x8007BD10: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_8007BD14:
    // 0x8007BD14: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x8007BD18: jr          $ra
    // 0x8007BD1C: nop

    return;
    // 0x8007BD1C: nop

;}
RECOMP_FUNC void func_8007BD20(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8007BD20: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x8007BD24: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x8007BD28: lui         $a0, 0x801B
    ctx->r4 = S32(0X801B << 16);
    // 0x8007BD2C: jal         0x8007BBF8
    // 0x8007BD30: addiu       $a0, $a0, -0x15E8
    ctx->r4 = ADD32(ctx->r4, -0X15E8);
    Save_GenCheckSum(rdram, ctx);
        goto after_0;
    // 0x8007BD30: addiu       $a0, $a0, -0x15E8
    ctx->r4 = ADD32(ctx->r4, -0X15E8);
    after_0:
    // 0x8007BD34: lui         $a2, 0x801B
    ctx->r6 = S32(0X801B << 16);
    // 0x8007BD38: addiu       $a2, $a2, -0x15E8
    ctx->r6 = ADD32(ctx->r6, -0X15E8);
    // 0x8007BD3C: lui         $a0, 0x8015
    ctx->r4 = S32(0X8015 << 16);
    // 0x8007BD40: sh          $v0, 0x2($a2)
    MEM_H(0X2, ctx->r6) = ctx->r2;
    // 0x8007BD44: addiu       $a0, $a0, 0x40D0
    ctx->r4 = ADD32(ctx->r4, 0X40D0);
    // 0x8007BD48: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x8007BD4C: jal         0x800C8410
    // 0x8007BD50: addiu       $a3, $zero, 0x200
    ctx->r7 = ADD32(0, 0X200);
    osEepromLongWrite_recomp(rdram, ctx);
        goto after_1;
    // 0x8007BD50: addiu       $a3, $zero, 0x200
    ctx->r7 = ADD32(0, 0X200);
    after_1:
    // 0x8007BD54: beq         $v0, $zero, L_8007BD64
    if (ctx->r2 == 0) {
        // 0x8007BD58: lw          $ra, 0x14($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X14);
            goto L_8007BD64;
    }
    // 0x8007BD58: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x8007BD5C: b           L_8007BD68
    // 0x8007BD60: addiu       $v0, $zero, 0x3
    ctx->r2 = ADD32(0, 0X3);
        goto L_8007BD68;
    // 0x8007BD60: addiu       $v0, $zero, 0x3
    ctx->r2 = ADD32(0, 0X3);
L_8007BD64:
    // 0x8007BD64: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_8007BD68:
    // 0x8007BD68: jr          $ra
    // 0x8007BD6C: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    return;
    // 0x8007BD6C: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
;}
RECOMP_FUNC void func_8007BD70(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8007BD70: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x8007BD74: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x8007BD78: lui         $a0, 0x8015
    ctx->r4 = S32(0X8015 << 16);
    // 0x8007BD7C: jal         0x800C8550
    // 0x8007BD80: addiu       $a0, $a0, 0x40D0
    ctx->r4 = ADD32(ctx->r4, 0X40D0);
    osEepromProbe_recomp(rdram, ctx);
        goto after_0;
    // 0x8007BD80: addiu       $a0, $a0, 0x40D0
    ctx->r4 = ADD32(ctx->r4, 0X40D0);
    after_0:
    // 0x8007BD84: bne         $v0, $zero, L_8007BD9C
    if (ctx->r2 != 0) {
        // 0x8007BD88: addiu       $t6, $zero, 0x1
        ctx->r14 = ADD32(0, 0X1);
            goto L_8007BD9C;
    }
    // 0x8007BD88: addiu       $t6, $zero, 0x1
    ctx->r14 = ADD32(0, 0X1);
    // 0x8007BD8C: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x8007BD90: sw          $zero, -0x7DA0($at)
    MEM_W(-0X7DA0, ctx->r1) = 0;
    // 0x8007BD94: b           L_8007BDA8
    // 0x8007BD98: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
        goto L_8007BDA8;
    // 0x8007BD98: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
L_8007BD9C:
    // 0x8007BD9C: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x8007BDA0: sw          $t6, -0x7DA0($at)
    MEM_W(-0X7DA0, ctx->r1) = ctx->r14;
    // 0x8007BDA4: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_8007BDA8:
    // 0x8007BDA8: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x8007BDAC: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x8007BDB0: jr          $ra
    // 0x8007BDB4: nop

    return;
    // 0x8007BDB4: nop

;}
RECOMP_FUNC void func_8007BDB8(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8007BDB8: lui         $t6, 0x800E
    ctx->r14 = S32(0X800E << 16);
    // 0x8007BDBC: lw          $t6, -0x7DA0($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X7DA0);
    // 0x8007BDC0: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x8007BDC4: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x8007BDC8: bne         $t6, $zero, L_8007BDD8
    if (ctx->r14 != 0) {
        // 0x8007BDCC: lui         $a0, 0x801B
        ctx->r4 = S32(0X801B << 16);
            goto L_8007BDD8;
    }
    // 0x8007BDCC: lui         $a0, 0x801B
    ctx->r4 = S32(0X801B << 16);
    // 0x8007BDD0: b           L_8007BDF0
    // 0x8007BDD4: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
        goto L_8007BDF0;
    // 0x8007BDD4: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
L_8007BDD8:
    // 0x8007BDD8: jal         0x8007B370
    // 0x8007BDDC: addiu       $a0, $a0, -0x15E8
    ctx->r4 = ADD32(ctx->r4, -0X15E8);
    func_8007B370(rdram, ctx);
        goto after_0;
    // 0x8007BDDC: addiu       $a0, $a0, -0x15E8
    ctx->r4 = ADD32(ctx->r4, -0X15E8);
    after_0:
    // 0x8007BDE0: jal         0x8007B630
    // 0x8007BDE4: nop

    func_8007B630(rdram, ctx);
        goto after_1;
    // 0x8007BDE4: nop

    after_1:
    // 0x8007BDE8: jal         0x8007BD20
    // 0x8007BDEC: nop

    func_8007BD20(rdram, ctx);
        goto after_2;
    // 0x8007BDEC: nop

    after_2:
L_8007BDF0:
    // 0x8007BDF0: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x8007BDF4: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x8007BDF8: jr          $ra
    // 0x8007BDFC: nop

    return;
    // 0x8007BDFC: nop

;}
RECOMP_FUNC void func_8007BE00(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8007BE00: lui         $t6, 0x800E
    ctx->r14 = S32(0X800E << 16);
    // 0x8007BE04: lw          $t6, -0x7DA0($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X7DA0);
    // 0x8007BE08: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x8007BE0C: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x8007BE10: bne         $t6, $zero, L_8007BE30
    if (ctx->r14 != 0) {
        // 0x8007BE14: lui         $a0, 0x801B
        ctx->r4 = S32(0X801B << 16);
            goto L_8007BE30;
    }
    // 0x8007BE14: lui         $a0, 0x801B
    ctx->r4 = S32(0X801B << 16);
    // 0x8007BE18: jal         0x8007B370
    // 0x8007BE1C: addiu       $a0, $a0, -0x15E8
    ctx->r4 = ADD32(ctx->r4, -0X15E8);
    func_8007B370(rdram, ctx);
        goto after_0;
    // 0x8007BE1C: addiu       $a0, $a0, -0x15E8
    ctx->r4 = ADD32(ctx->r4, -0X15E8);
    after_0:
    // 0x8007BE20: jal         0x8007B630
    // 0x8007BE24: nop

    func_8007B630(rdram, ctx);
        goto after_1;
    // 0x8007BE24: nop

    after_1:
    // 0x8007BE28: b           L_8007BE54
    // 0x8007BE2C: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
        goto L_8007BE54;
    // 0x8007BE2C: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
L_8007BE30:
    // 0x8007BE30: jal         0x8007BC44
    // 0x8007BE34: nop

    func_8007BC44(rdram, ctx);
        goto after_2;
    // 0x8007BE34: nop

    after_2:
    // 0x8007BE38: beq         $v0, $zero, L_8007BE48
    if (ctx->r2 == 0) {
        // 0x8007BE3C: nop
    
            goto L_8007BE48;
    }
    // 0x8007BE3C: nop

    // 0x8007BE40: b           L_8007BE58
    // 0x8007BE44: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_8007BE58;
    // 0x8007BE44: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_8007BE48:
    // 0x8007BE48: jal         0x8007B630
    // 0x8007BE4C: nop

    func_8007B630(rdram, ctx);
        goto after_3;
    // 0x8007BE4C: nop

    after_3:
    // 0x8007BE50: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_8007BE54:
    // 0x8007BE54: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_8007BE58:
    // 0x8007BE58: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x8007BE5C: jr          $ra
    // 0x8007BE60: nop

    return;
    // 0x8007BE60: nop

;}
RECOMP_FUNC void func_8007BE64(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8007BE64: lui         $t6, 0x800E
    ctx->r14 = S32(0X800E << 16);
    // 0x8007BE68: lw          $t6, -0x7DA0($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X7DA0);
    // 0x8007BE6C: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x8007BE70: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x8007BE74: bne         $t6, $zero, L_8007BE84
    if (ctx->r14 != 0) {
        // 0x8007BE78: nop
    
            goto L_8007BE84;
    }
    // 0x8007BE78: nop

    // 0x8007BE7C: b           L_8007BE94
    // 0x8007BE80: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
        goto L_8007BE94;
    // 0x8007BE80: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
L_8007BE84:
    // 0x8007BE84: jal         0x8007B930
    // 0x8007BE88: nop

    func_8007B930(rdram, ctx);
        goto after_0;
    // 0x8007BE88: nop

    after_0:
    // 0x8007BE8C: jal         0x8007BD20
    // 0x8007BE90: nop

    func_8007BD20(rdram, ctx);
        goto after_1;
    // 0x8007BE90: nop

    after_1:
L_8007BE94:
    // 0x8007BE94: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x8007BE98: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x8007BE9C: jr          $ra
    // 0x8007BEA0: nop

    return;
    // 0x8007BEA0: nop

;}
RECOMP_FUNC void func_8007BEA4(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8007BEA4: addiu       $sp, $sp, -0x38
    ctx->r29 = ADD32(ctx->r29, -0X38);
    // 0x8007BEA8: lui         $t6, 0x800E
    ctx->r14 = S32(0X800E << 16);
    // 0x8007BEAC: lw          $t6, -0x7DA0($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X7DA0);
    // 0x8007BEB0: sw          $s3, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r19;
    // 0x8007BEB4: or          $s3, $a0, $zero
    ctx->r19 = ctx->r4 | 0;
    // 0x8007BEB8: sw          $ra, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r31;
    // 0x8007BEBC: sw          $s2, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r18;
    // 0x8007BEC0: sw          $s1, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r17;
    // 0x8007BEC4: bne         $t6, $zero, L_8007BED4
    if (ctx->r14 != 0) {
        // 0x8007BEC8: sw          $s0, 0x14($sp)
        MEM_W(0X14, ctx->r29) = ctx->r16;
            goto L_8007BED4;
    }
    // 0x8007BEC8: sw          $s0, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r16;
    // 0x8007BECC: b           L_8007C09C
    // 0x8007BED0: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
        goto L_8007C09C;
    // 0x8007BED0: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
L_8007BED4:
    // 0x8007BED4: blez        $s3, L_8007BEE4
    if (SIGNED(ctx->r19) <= 0) {
        // 0x8007BED8: slti        $at, $s3, 0x9
        ctx->r1 = SIGNED(ctx->r19) < 0X9 ? 1 : 0;
            goto L_8007BEE4;
    }
    // 0x8007BED8: slti        $at, $s3, 0x9
    ctx->r1 = SIGNED(ctx->r19) < 0X9 ? 1 : 0;
    // 0x8007BEDC: bne         $at, $zero, L_8007BEEC
    if (ctx->r1 != 0) {
        // 0x8007BEE0: addiu       $v1, $s3, -0x1
        ctx->r3 = ADD32(ctx->r19, -0X1);
            goto L_8007BEEC;
    }
    // 0x8007BEE0: addiu       $v1, $s3, -0x1
    ctx->r3 = ADD32(ctx->r19, -0X1);
L_8007BEE4:
    // 0x8007BEE4: b           L_8007C09C
    // 0x8007BEE8: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
        goto L_8007C09C;
    // 0x8007BEE8: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_8007BEEC:
    // 0x8007BEEC: sll         $t9, $v1, 2
    ctx->r25 = S32(ctx->r3 << 2);
    // 0x8007BEF0: subu        $t9, $t9, $v1
    ctx->r25 = SUB32(ctx->r25, ctx->r3);
    // 0x8007BEF4: sll         $t7, $s3, 4
    ctx->r15 = S32(ctx->r19 << 4);
    // 0x8007BEF8: subu        $t7, $t7, $s3
    ctx->r15 = SUB32(ctx->r15, ctx->r19);
    // 0x8007BEFC: sll         $t9, $t9, 3
    ctx->r25 = S32(ctx->r25 << 3);
    // 0x8007BF00: lui         $t8, 0x801C
    ctx->r24 = S32(0X801C << 16);
    // 0x8007BF04: lui         $t1, 0x801B
    ctx->r9 = S32(0X801B << 16);
    // 0x8007BF08: addiu       $t1, $t1, -0x15E8
    ctx->r9 = ADD32(ctx->r9, -0X15E8);
    // 0x8007BF0C: addiu       $t8, $t8, 0x1FF0
    ctx->r24 = ADD32(ctx->r24, 0X1FF0);
    // 0x8007BF10: addiu       $t0, $t9, 0x60
    ctx->r8 = ADD32(ctx->r25, 0X60);
    // 0x8007BF14: sll         $t7, $t7, 2
    ctx->r15 = S32(ctx->r15 << 2);
    // 0x8007BF18: addu        $s1, $t7, $t8
    ctx->r17 = ADD32(ctx->r15, ctx->r24);
    // 0x8007BF1C: addu        $s0, $t0, $t1
    ctx->r16 = ADD32(ctx->r8, ctx->r9);
    // 0x8007BF20: or          $s2, $zero, $zero
    ctx->r18 = 0 | 0;
    // 0x8007BF24: sw          $v1, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r3;
L_8007BF28:
    // 0x8007BF28: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    // 0x8007BF2C: jal         0x8007AF78
    // 0x8007BF30: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    func_8007AF78(rdram, ctx);
        goto after_0;
    // 0x8007BF30: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    after_0:
    // 0x8007BF34: addiu       $s2, $s2, 0x6
    ctx->r18 = ADD32(ctx->r18, 0X6);
    // 0x8007BF38: slti        $at, $s2, 0x12
    ctx->r1 = SIGNED(ctx->r18) < 0X12 ? 1 : 0;
    // 0x8007BF3C: addiu       $s1, $s1, 0x14
    ctx->r17 = ADD32(ctx->r17, 0X14);
    // 0x8007BF40: bne         $at, $zero, L_8007BF28
    if (ctx->r1 != 0) {
        // 0x8007BF44: addiu       $s0, $s0, 0x6
        ctx->r16 = ADD32(ctx->r16, 0X6);
            goto L_8007BF28;
    }
    // 0x8007BF44: addiu       $s0, $s0, 0x6
    ctx->r16 = ADD32(ctx->r16, 0X6);
    // 0x8007BF48: sll         $t2, $s3, 2
    ctx->r10 = S32(ctx->r19 << 2);
    // 0x8007BF4C: addu        $t2, $t2, $s3
    ctx->r10 = ADD32(ctx->r10, ctx->r19);
    // 0x8007BF50: lui         $t3, 0x801C
    ctx->r11 = S32(0X801C << 16);
    // 0x8007BF54: addiu       $t3, $t3, 0x22C0
    ctx->r11 = ADD32(ctx->r11, 0X22C0);
    // 0x8007BF58: sll         $t2, $t2, 2
    ctx->r10 = S32(ctx->r10 << 2);
    // 0x8007BF5C: addu        $a0, $t2, $t3
    ctx->r4 = ADD32(ctx->r10, ctx->r11);
    // 0x8007BF60: jal         0x8007AF78
    // 0x8007BF64: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    func_8007AF78(rdram, ctx);
        goto after_1;
    // 0x8007BF64: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    after_1:
    // 0x8007BF68: lw          $t6, 0x2C($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X2C);
    // 0x8007BF6C: sll         $t4, $s3, 3
    ctx->r12 = S32(ctx->r19 << 3);
    // 0x8007BF70: addu        $t4, $t4, $s3
    ctx->r12 = ADD32(ctx->r12, ctx->r19);
    // 0x8007BF74: sll         $t7, $t6, 2
    ctx->r15 = S32(ctx->r14 << 2);
    // 0x8007BF78: subu        $t7, $t7, $t6
    ctx->r15 = SUB32(ctx->r15, ctx->r14);
    // 0x8007BF7C: sll         $t7, $t7, 1
    ctx->r15 = S32(ctx->r15 << 1);
    // 0x8007BF80: lui         $t5, 0x801C
    ctx->r13 = S32(0X801C << 16);
    // 0x8007BF84: lui         $t9, 0x801B
    ctx->r25 = S32(0X801B << 16);
    // 0x8007BF88: addiu       $t9, $t9, -0x15E8
    ctx->r25 = ADD32(ctx->r25, -0X15E8);
    // 0x8007BF8C: addiu       $t5, $t5, 0x24A0
    ctx->r13 = ADD32(ctx->r13, 0X24A0);
    // 0x8007BF90: addiu       $t8, $t7, 0x1A8
    ctx->r24 = ADD32(ctx->r15, 0X1A8);
    // 0x8007BF94: sll         $t4, $t4, 2
    ctx->r12 = S32(ctx->r12 << 2);
    // 0x8007BF98: addu        $s0, $t4, $t5
    ctx->r16 = ADD32(ctx->r12, ctx->r13);
    // 0x8007BF9C: addu        $s2, $t8, $t9
    ctx->r18 = ADD32(ctx->r24, ctx->r25);
    // 0x8007BFA0: addiu       $s3, $zero, 0x6
    ctx->r19 = ADD32(0, 0X6);
    // 0x8007BFA4: or          $s1, $zero, $zero
    ctx->r17 = 0 | 0;
L_8007BFA8:
    // 0x8007BFA8: lw          $a0, 0x0($s0)
    ctx->r4 = MEM_W(ctx->r16, 0X0);
    // 0x8007BFAC: jal         0x8007B2BC
    // 0x8007BFB0: or          $a1, $s2, $zero
    ctx->r5 = ctx->r18 | 0;
    func_8007B2BC(rdram, ctx);
        goto after_2;
    // 0x8007BFB0: or          $a1, $s2, $zero
    ctx->r5 = ctx->r18 | 0;
    after_2:
    // 0x8007BFB4: addiu       $s1, $s1, 0x3
    ctx->r17 = ADD32(ctx->r17, 0X3);
    // 0x8007BFB8: addiu       $s0, $s0, 0x4
    ctx->r16 = ADD32(ctx->r16, 0X4);
    // 0x8007BFBC: bne         $s1, $s3, L_8007BFA8
    if (ctx->r17 != ctx->r19) {
        // 0x8007BFC0: addiu       $s2, $s2, 0x3
        ctx->r18 = ADD32(ctx->r18, 0X3);
            goto L_8007BFA8;
    }
    // 0x8007BFC0: addiu       $s2, $s2, 0x3
    ctx->r18 = ADD32(ctx->r18, 0X3);
    // 0x8007BFC4: jal         0x8007B31C
    // 0x8007BFC8: nop

    func_8007B31C(rdram, ctx);
        goto after_3;
    // 0x8007BFC8: nop

    after_3:
    // 0x8007BFCC: lui         $s0, 0x801B
    ctx->r16 = S32(0X801B << 16);
    // 0x8007BFD0: addiu       $s0, $s0, -0x15E8
    ctx->r16 = ADD32(ctx->r16, -0X15E8);
    // 0x8007BFD4: jal         0x8007BBF8
    // 0x8007BFD8: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    Save_GenCheckSum(rdram, ctx);
        goto after_4;
    // 0x8007BFD8: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_4:
    // 0x8007BFDC: lui         $s2, 0x8015
    ctx->r18 = S32(0X8015 << 16);
    // 0x8007BFE0: addiu       $s2, $s2, 0x40D0
    ctx->r18 = ADD32(ctx->r18, 0X40D0);
    // 0x8007BFE4: sh          $v0, 0x2($s0)
    MEM_H(0X2, ctx->r16) = ctx->r2;
    // 0x8007BFE8: or          $a0, $s2, $zero
    ctx->r4 = ctx->r18 | 0;
    // 0x8007BFEC: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x8007BFF0: or          $a2, $s0, $zero
    ctx->r6 = ctx->r16 | 0;
    // 0x8007BFF4: jal         0x800C8410
    // 0x8007BFF8: addiu       $a3, $zero, 0x10
    ctx->r7 = ADD32(0, 0X10);
    osEepromLongWrite_recomp(rdram, ctx);
        goto after_5;
    // 0x8007BFF8: addiu       $a3, $zero, 0x10
    ctx->r7 = ADD32(0, 0X10);
    after_5:
    // 0x8007BFFC: beq         $v0, $zero, L_8007C00C
    if (ctx->r2 == 0) {
        // 0x8007C000: or          $a0, $s2, $zero
        ctx->r4 = ctx->r18 | 0;
            goto L_8007C00C;
    }
    // 0x8007C000: or          $a0, $s2, $zero
    ctx->r4 = ctx->r18 | 0;
    // 0x8007C004: b           L_8007C09C
    // 0x8007C008: addiu       $v0, $zero, 0x3
    ctx->r2 = ADD32(0, 0X3);
        goto L_8007C09C;
    // 0x8007C008: addiu       $v0, $zero, 0x3
    ctx->r2 = ADD32(0, 0X3);
L_8007C00C:
    // 0x8007C00C: lw          $t0, 0x2C($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X2C);
    // 0x8007C010: or          $s1, $s0, $zero
    ctx->r17 = ctx->r16 | 0;
    // 0x8007C014: addiu       $a3, $zero, 0x18
    ctx->r7 = ADD32(0, 0X18);
    // 0x8007C018: sll         $t1, $t0, 2
    ctx->r9 = S32(ctx->r8 << 2);
    // 0x8007C01C: subu        $t1, $t1, $t0
    ctx->r9 = SUB32(ctx->r9, ctx->r8);
    // 0x8007C020: sll         $t1, $t1, 3
    ctx->r9 = S32(ctx->r9 << 3);
    // 0x8007C024: addu        $a2, $s0, $t1
    ctx->r6 = ADD32(ctx->r16, ctx->r9);
    // 0x8007C028: addiu       $a2, $a2, 0x60
    ctx->r6 = ADD32(ctx->r6, 0X60);
    // 0x8007C02C: subu        $a1, $a2, $s0
    ctx->r5 = SUB32(ctx->r6, ctx->r16);
    // 0x8007C030: srl         $t2, $a1, 3
    ctx->r10 = S32(U32(ctx->r5) >> 3);
    // 0x8007C034: jal         0x800C8410
    // 0x8007C038: andi        $a1, $t2, 0xFF
    ctx->r5 = ctx->r10 & 0XFF;
    osEepromLongWrite_recomp(rdram, ctx);
        goto after_6;
    // 0x8007C038: andi        $a1, $t2, 0xFF
    ctx->r5 = ctx->r10 & 0XFF;
    after_6:
    // 0x8007C03C: beq         $v0, $zero, L_8007C04C
    if (ctx->r2 == 0) {
        // 0x8007C040: lw          $t4, 0x2C($sp)
        ctx->r12 = MEM_W(ctx->r29, 0X2C);
            goto L_8007C04C;
    }
    // 0x8007C040: lw          $t4, 0x2C($sp)
    ctx->r12 = MEM_W(ctx->r29, 0X2C);
    // 0x8007C044: b           L_8007C09C
    // 0x8007C048: addiu       $v0, $zero, 0x3
    ctx->r2 = ADD32(0, 0X3);
        goto L_8007C09C;
    // 0x8007C048: addiu       $v0, $zero, 0x3
    ctx->r2 = ADD32(0, 0X3);
L_8007C04C:
    // 0x8007C04C: sll         $t5, $t4, 2
    ctx->r13 = S32(ctx->r12 << 2);
    // 0x8007C050: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x8007C054: addu        $v0, $v0, $t5
    ctx->r2 = ADD32(ctx->r2, ctx->r13);
    // 0x8007C058: lw          $v0, -0x7D50($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X7D50);
    // 0x8007C05C: lui         $t6, 0x801B
    ctx->r14 = S32(0X801B << 16);
    // 0x8007C060: addiu       $t6, $t6, -0x1440
    ctx->r14 = ADD32(ctx->r14, -0X1440);
    // 0x8007C064: subu        $t7, $t6, $s1
    ctx->r15 = SUB32(ctx->r14, ctx->r17);
    // 0x8007C068: addu        $a1, $t7, $v0
    ctx->r5 = ADD32(ctx->r15, ctx->r2);
    // 0x8007C06C: srl         $t8, $a1, 3
    ctx->r24 = S32(U32(ctx->r5) >> 3);
    // 0x8007C070: addu        $a2, $s0, $v0
    ctx->r6 = ADD32(ctx->r16, ctx->r2);
    // 0x8007C074: addiu       $a2, $a2, 0x1A8
    ctx->r6 = ADD32(ctx->r6, 0X1A8);
    // 0x8007C078: andi        $a1, $t8, 0xFF
    ctx->r5 = ctx->r24 & 0XFF;
    // 0x8007C07C: or          $a0, $s2, $zero
    ctx->r4 = ctx->r18 | 0;
    // 0x8007C080: jal         0x800C8410
    // 0x8007C084: addiu       $a3, $zero, 0x10
    ctx->r7 = ADD32(0, 0X10);
    osEepromLongWrite_recomp(rdram, ctx);
        goto after_7;
    // 0x8007C084: addiu       $a3, $zero, 0x10
    ctx->r7 = ADD32(0, 0X10);
    after_7:
    // 0x8007C088: beql        $v0, $zero, L_8007C09C
    if (ctx->r2 == 0) {
        // 0x8007C08C: or          $v0, $zero, $zero
        ctx->r2 = 0 | 0;
            goto L_8007C09C;
    }
    goto skip_0;
    // 0x8007C08C: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    skip_0:
    // 0x8007C090: b           L_8007C09C
    // 0x8007C094: addiu       $v0, $zero, 0x3
    ctx->r2 = ADD32(0, 0X3);
        goto L_8007C09C;
    // 0x8007C094: addiu       $v0, $zero, 0x3
    ctx->r2 = ADD32(0, 0X3);
    // 0x8007C098: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_8007C09C:
    // 0x8007C09C: lw          $ra, 0x24($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X24);
    // 0x8007C0A0: lw          $s0, 0x14($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X14);
    // 0x8007C0A4: lw          $s1, 0x18($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X18);
    // 0x8007C0A8: lw          $s2, 0x1C($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X1C);
    // 0x8007C0AC: lw          $s3, 0x20($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X20);
    // 0x8007C0B0: jr          $ra
    // 0x8007C0B4: addiu       $sp, $sp, 0x38
    ctx->r29 = ADD32(ctx->r29, 0X38);
    return;
    // 0x8007C0B4: addiu       $sp, $sp, 0x38
    ctx->r29 = ADD32(ctx->r29, 0X38);
;}
RECOMP_FUNC void func_8007C0B8(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8007C0B8: addiu       $sp, $sp, -0x28
    ctx->r29 = ADD32(ctx->r29, -0X28);
    // 0x8007C0BC: lui         $t6, 0x800E
    ctx->r14 = S32(0X800E << 16);
    // 0x8007C0C0: lw          $t6, -0x7DA0($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X7DA0);
    // 0x8007C0C4: sw          $ra, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r31;
    // 0x8007C0C8: sw          $s3, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r19;
    // 0x8007C0CC: sw          $s2, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r18;
    // 0x8007C0D0: sw          $s1, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r17;
    // 0x8007C0D4: sw          $s0, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r16;
    // 0x8007C0D8: bne         $t6, $zero, L_8007C0E8
    if (ctx->r14 != 0) {
        // 0x8007C0DC: or          $a2, $a0, $zero
        ctx->r6 = ctx->r4 | 0;
            goto L_8007C0E8;
    }
    // 0x8007C0DC: or          $a2, $a0, $zero
    ctx->r6 = ctx->r4 | 0;
    // 0x8007C0E0: b           L_8007C1E8
    // 0x8007C0E4: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
        goto L_8007C1E8;
    // 0x8007C0E4: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
L_8007C0E8:
    // 0x8007C0E8: slti        $at, $a2, 0x9
    ctx->r1 = SIGNED(ctx->r6) < 0X9 ? 1 : 0;
    // 0x8007C0EC: bne         $at, $zero, L_8007C0FC
    if (ctx->r1 != 0) {
        // 0x8007C0F0: sll         $t7, $a2, 2
        ctx->r15 = S32(ctx->r6 << 2);
            goto L_8007C0FC;
    }
    // 0x8007C0F0: sll         $t7, $a2, 2
    ctx->r15 = S32(ctx->r6 << 2);
    // 0x8007C0F4: b           L_8007C1E8
    // 0x8007C0F8: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
        goto L_8007C1E8;
    // 0x8007C0F8: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_8007C0FC:
    // 0x8007C0FC: sll         $t9, $a2, 4
    ctx->r25 = S32(ctx->r6 << 4);
    // 0x8007C100: subu        $t9, $t9, $a2
    ctx->r25 = SUB32(ctx->r25, ctx->r6);
    // 0x8007C104: subu        $t7, $t7, $a2
    ctx->r15 = SUB32(ctx->r15, ctx->r6);
    // 0x8007C108: lui         $t8, 0x801C
    ctx->r24 = S32(0X801C << 16);
    // 0x8007C10C: lui         $t1, 0x801B
    ctx->r9 = S32(0X801B << 16);
    // 0x8007C110: addiu       $t1, $t1, -0x15E8
    ctx->r9 = ADD32(ctx->r9, -0X15E8);
    // 0x8007C114: addiu       $t8, $t8, 0x26E8
    ctx->r24 = ADD32(ctx->r24, 0X26E8);
    // 0x8007C118: sll         $t7, $t7, 4
    ctx->r15 = S32(ctx->r15 << 4);
    // 0x8007C11C: addiu       $t0, $t9, 0x120
    ctx->r8 = ADD32(ctx->r25, 0X120);
    // 0x8007C120: addu        $s2, $t0, $t1
    ctx->r18 = ADD32(ctx->r8, ctx->r9);
    // 0x8007C124: addu        $s0, $t7, $t8
    ctx->r16 = ADD32(ctx->r15, ctx->r24);
    // 0x8007C128: or          $s1, $zero, $zero
    ctx->r17 = 0 | 0;
    // 0x8007C12C: sw          $a2, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r6;
    // 0x8007C130: addiu       $s3, $zero, 0xF
    ctx->r19 = ADD32(0, 0XF);
L_8007C134:
    // 0x8007C134: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x8007C138: jal         0x8007B1AC
    // 0x8007C13C: or          $a1, $s2, $zero
    ctx->r5 = ctx->r18 | 0;
    func_8007B1AC(rdram, ctx);
        goto after_0;
    // 0x8007C13C: or          $a1, $s2, $zero
    ctx->r5 = ctx->r18 | 0;
    after_0:
    // 0x8007C140: addiu       $s1, $s1, 0x5
    ctx->r17 = ADD32(ctx->r17, 0X5);
    // 0x8007C144: addiu       $s0, $s0, 0x10
    ctx->r16 = ADD32(ctx->r16, 0X10);
    // 0x8007C148: bne         $s1, $s3, L_8007C134
    if (ctx->r17 != ctx->r19) {
        // 0x8007C14C: addiu       $s2, $s2, 0x5
        ctx->r18 = ADD32(ctx->r18, 0X5);
            goto L_8007C134;
    }
    // 0x8007C14C: addiu       $s2, $s2, 0x5
    ctx->r18 = ADD32(ctx->r18, 0X5);
    // 0x8007C150: jal         0x8007B31C
    // 0x8007C154: nop

    func_8007B31C(rdram, ctx);
        goto after_1;
    // 0x8007C154: nop

    after_1:
    // 0x8007C158: lui         $s0, 0x801B
    ctx->r16 = S32(0X801B << 16);
    // 0x8007C15C: addiu       $s0, $s0, -0x15E8
    ctx->r16 = ADD32(ctx->r16, -0X15E8);
    // 0x8007C160: jal         0x8007BBF8
    // 0x8007C164: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    Save_GenCheckSum(rdram, ctx);
        goto after_2;
    // 0x8007C164: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_2:
    // 0x8007C168: lui         $s1, 0x8015
    ctx->r17 = S32(0X8015 << 16);
    // 0x8007C16C: addiu       $s1, $s1, 0x40D0
    ctx->r17 = ADD32(ctx->r17, 0X40D0);
    // 0x8007C170: sh          $v0, 0x2($s0)
    MEM_H(0X2, ctx->r16) = ctx->r2;
    // 0x8007C174: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    // 0x8007C178: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x8007C17C: or          $a2, $s0, $zero
    ctx->r6 = ctx->r16 | 0;
    // 0x8007C180: jal         0x800C8410
    // 0x8007C184: addiu       $a3, $zero, 0x10
    ctx->r7 = ADD32(0, 0X10);
    osEepromLongWrite_recomp(rdram, ctx);
        goto after_3;
    // 0x8007C184: addiu       $a3, $zero, 0x10
    ctx->r7 = ADD32(0, 0X10);
    after_3:
    // 0x8007C188: beq         $v0, $zero, L_8007C198
    if (ctx->r2 == 0) {
        // 0x8007C18C: lw          $t2, 0x28($sp)
        ctx->r10 = MEM_W(ctx->r29, 0X28);
            goto L_8007C198;
    }
    // 0x8007C18C: lw          $t2, 0x28($sp)
    ctx->r10 = MEM_W(ctx->r29, 0X28);
    // 0x8007C190: b           L_8007C1E8
    // 0x8007C194: addiu       $v0, $zero, 0x3
    ctx->r2 = ADD32(0, 0X3);
        goto L_8007C1E8;
    // 0x8007C194: addiu       $v0, $zero, 0x3
    ctx->r2 = ADD32(0, 0X3);
L_8007C198:
    // 0x8007C198: sll         $t3, $t2, 2
    ctx->r11 = S32(ctx->r10 << 2);
    // 0x8007C19C: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x8007C1A0: addu        $v0, $v0, $t3
    ctx->r2 = ADD32(ctx->r2, ctx->r11);
    // 0x8007C1A4: lw          $v0, -0x7D94($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X7D94);
    // 0x8007C1A8: lui         $t4, 0x801B
    ctx->r12 = S32(0X801B << 16);
    // 0x8007C1AC: addiu       $t4, $t4, -0x14C8
    ctx->r12 = ADD32(ctx->r12, -0X14C8);
    // 0x8007C1B0: subu        $t5, $t4, $s0
    ctx->r13 = SUB32(ctx->r12, ctx->r16);
    // 0x8007C1B4: addu        $a1, $t5, $v0
    ctx->r5 = ADD32(ctx->r13, ctx->r2);
    // 0x8007C1B8: srl         $t6, $a1, 3
    ctx->r14 = S32(U32(ctx->r5) >> 3);
    // 0x8007C1BC: addu        $a2, $s0, $v0
    ctx->r6 = ADD32(ctx->r16, ctx->r2);
    // 0x8007C1C0: addiu       $a2, $a2, 0x120
    ctx->r6 = ADD32(ctx->r6, 0X120);
    // 0x8007C1C4: andi        $a1, $t6, 0xFF
    ctx->r5 = ctx->r14 & 0XFF;
    // 0x8007C1C8: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    // 0x8007C1CC: jal         0x800C8410
    // 0x8007C1D0: addiu       $a3, $zero, 0x18
    ctx->r7 = ADD32(0, 0X18);
    osEepromLongWrite_recomp(rdram, ctx);
        goto after_4;
    // 0x8007C1D0: addiu       $a3, $zero, 0x18
    ctx->r7 = ADD32(0, 0X18);
    after_4:
    // 0x8007C1D4: beql        $v0, $zero, L_8007C1E8
    if (ctx->r2 == 0) {
        // 0x8007C1D8: or          $v0, $zero, $zero
        ctx->r2 = 0 | 0;
            goto L_8007C1E8;
    }
    goto skip_0;
    // 0x8007C1D8: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    skip_0:
    // 0x8007C1DC: b           L_8007C1E8
    // 0x8007C1E0: addiu       $v0, $zero, 0x3
    ctx->r2 = ADD32(0, 0X3);
        goto L_8007C1E8;
    // 0x8007C1E0: addiu       $v0, $zero, 0x3
    ctx->r2 = ADD32(0, 0X3);
    // 0x8007C1E4: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_8007C1E8:
    // 0x8007C1E8: lw          $ra, 0x24($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X24);
    // 0x8007C1EC: lw          $s0, 0x14($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X14);
    // 0x8007C1F0: lw          $s1, 0x18($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X18);
    // 0x8007C1F4: lw          $s2, 0x1C($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X1C);
    // 0x8007C1F8: lw          $s3, 0x20($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X20);
    // 0x8007C1FC: jr          $ra
    // 0x8007C200: addiu       $sp, $sp, 0x28
    ctx->r29 = ADD32(ctx->r29, 0X28);
    return;
    // 0x8007C200: addiu       $sp, $sp, 0x28
    ctx->r29 = ADD32(ctx->r29, 0X28);
;}
RECOMP_FUNC void func_8007C204(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8007C204: lui         $t6, 0x800E
    ctx->r14 = S32(0X800E << 16);
    // 0x8007C208: lw          $t6, -0x7DA0($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X7DA0);
    // 0x8007C20C: addiu       $sp, $sp, -0x30
    ctx->r29 = ADD32(ctx->r29, -0X30);
    // 0x8007C210: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x8007C214: sw          $s0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r16;
    // 0x8007C218: bne         $t6, $zero, L_8007C228
    if (ctx->r14 != 0) {
        // 0x8007C21C: or          $a2, $a0, $zero
        ctx->r6 = ctx->r4 | 0;
            goto L_8007C228;
    }
    // 0x8007C21C: or          $a2, $a0, $zero
    ctx->r6 = ctx->r4 | 0;
    // 0x8007C220: b           L_8007C308
    // 0x8007C224: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
        goto L_8007C308;
    // 0x8007C224: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
L_8007C228:
    // 0x8007C228: blez        $a2, L_8007C238
    if (SIGNED(ctx->r6) <= 0) {
        // 0x8007C22C: slti        $at, $a2, 0x9
        ctx->r1 = SIGNED(ctx->r6) < 0X9 ? 1 : 0;
            goto L_8007C238;
    }
    // 0x8007C22C: slti        $at, $a2, 0x9
    ctx->r1 = SIGNED(ctx->r6) < 0X9 ? 1 : 0;
    // 0x8007C230: bne         $at, $zero, L_8007C240
    if (ctx->r1 != 0) {
        // 0x8007C234: lui         $s0, 0x801B
        ctx->r16 = S32(0X801B << 16);
            goto L_8007C240;
    }
    // 0x8007C234: lui         $s0, 0x801B
    ctx->r16 = S32(0X801B << 16);
L_8007C238:
    // 0x8007C238: b           L_8007C308
    // 0x8007C23C: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
        goto L_8007C308;
    // 0x8007C23C: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_8007C240:
    // 0x8007C240: sll         $t8, $a2, 2
    ctx->r24 = S32(ctx->r6 << 2);
    // 0x8007C244: sll         $t0, $a2, 2
    ctx->r8 = S32(ctx->r6 << 2);
    // 0x8007C248: addiu       $s0, $s0, -0x15E8
    ctx->r16 = ADD32(ctx->r16, -0X15E8);
    // 0x8007C24C: addu        $t0, $t0, $a2
    ctx->r8 = ADD32(ctx->r8, ctx->r6);
    // 0x8007C250: addu        $t8, $t8, $a2
    ctx->r24 = ADD32(ctx->r24, ctx->r6);
    // 0x8007C254: lui         $t9, 0x801C
    ctx->r25 = S32(0X801C << 16);
    // 0x8007C258: addiu       $t7, $a2, -0x1
    ctx->r15 = ADD32(ctx->r6, -0X1);
    // 0x8007C25C: addiu       $t9, $t9, 0x23B0
    ctx->r25 = ADD32(ctx->r25, 0X23B0);
    // 0x8007C260: sll         $t8, $t8, 2
    ctx->r24 = S32(ctx->r24 << 2);
    // 0x8007C264: addu        $a1, $s0, $t0
    ctx->r5 = ADD32(ctx->r16, ctx->r8);
    // 0x8007C268: sw          $t7, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r15;
    // 0x8007C26C: addiu       $a1, $a1, 0x1D3
    ctx->r5 = ADD32(ctx->r5, 0X1D3);
    // 0x8007C270: jal         0x8007B09C
    // 0x8007C274: addu        $a0, $t8, $t9
    ctx->r4 = ADD32(ctx->r24, ctx->r25);
    func_8007B09C(rdram, ctx);
        goto after_0;
    // 0x8007C274: addu        $a0, $t8, $t9
    ctx->r4 = ADD32(ctx->r24, ctx->r25);
    after_0:
    // 0x8007C278: jal         0x8007B31C
    // 0x8007C27C: nop

    func_8007B31C(rdram, ctx);
        goto after_1;
    // 0x8007C27C: nop

    after_1:
    // 0x8007C280: jal         0x8007BBF8
    // 0x8007C284: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    Save_GenCheckSum(rdram, ctx);
        goto after_2;
    // 0x8007C284: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_2:
    // 0x8007C288: lui         $a0, 0x8015
    ctx->r4 = S32(0X8015 << 16);
    // 0x8007C28C: sh          $v0, 0x2($s0)
    MEM_H(0X2, ctx->r16) = ctx->r2;
    // 0x8007C290: addiu       $a0, $a0, 0x40D0
    ctx->r4 = ADD32(ctx->r4, 0X40D0);
    // 0x8007C294: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x8007C298: or          $a2, $s0, $zero
    ctx->r6 = ctx->r16 | 0;
    // 0x8007C29C: jal         0x800C8410
    // 0x8007C2A0: addiu       $a3, $zero, 0x10
    ctx->r7 = ADD32(0, 0X10);
    osEepromLongWrite_recomp(rdram, ctx);
        goto after_3;
    // 0x8007C2A0: addiu       $a3, $zero, 0x10
    ctx->r7 = ADD32(0, 0X10);
    after_3:
    // 0x8007C2A4: beq         $v0, $zero, L_8007C2B4
    if (ctx->r2 == 0) {
        // 0x8007C2A8: lw          $t1, 0x24($sp)
        ctx->r9 = MEM_W(ctx->r29, 0X24);
            goto L_8007C2B4;
    }
    // 0x8007C2A8: lw          $t1, 0x24($sp)
    ctx->r9 = MEM_W(ctx->r29, 0X24);
    // 0x8007C2AC: b           L_8007C308
    // 0x8007C2B0: addiu       $v0, $zero, 0x3
    ctx->r2 = ADD32(0, 0X3);
        goto L_8007C308;
    // 0x8007C2B0: addiu       $v0, $zero, 0x3
    ctx->r2 = ADD32(0, 0X3);
L_8007C2B4:
    // 0x8007C2B4: sll         $t2, $t1, 2
    ctx->r10 = S32(ctx->r9 << 2);
    // 0x8007C2B8: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x8007C2BC: addu        $v0, $v0, $t2
    ctx->r2 = ADD32(ctx->r2, ctx->r10);
    // 0x8007C2C0: lw          $v0, -0x7D70($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X7D70);
    // 0x8007C2C4: lui         $t3, 0x801B
    ctx->r11 = S32(0X801B << 16);
    // 0x8007C2C8: addiu       $t3, $t3, -0x1410
    ctx->r11 = ADD32(ctx->r11, -0X1410);
    // 0x8007C2CC: subu        $t4, $t3, $s0
    ctx->r12 = SUB32(ctx->r11, ctx->r16);
    // 0x8007C2D0: addu        $a1, $t4, $v0
    ctx->r5 = ADD32(ctx->r12, ctx->r2);
    // 0x8007C2D4: srl         $t5, $a1, 3
    ctx->r13 = S32(U32(ctx->r5) >> 3);
    // 0x8007C2D8: lui         $a0, 0x8015
    ctx->r4 = S32(0X8015 << 16);
    // 0x8007C2DC: addu        $a2, $s0, $v0
    ctx->r6 = ADD32(ctx->r16, ctx->r2);
    // 0x8007C2E0: addiu       $a2, $a2, 0x1D8
    ctx->r6 = ADD32(ctx->r6, 0X1D8);
    // 0x8007C2E4: addiu       $a0, $a0, 0x40D0
    ctx->r4 = ADD32(ctx->r4, 0X40D0);
    // 0x8007C2E8: andi        $a1, $t5, 0xFF
    ctx->r5 = ctx->r13 & 0XFF;
    // 0x8007C2EC: jal         0x800C8410
    // 0x8007C2F0: addiu       $a3, $zero, 0x10
    ctx->r7 = ADD32(0, 0X10);
    osEepromLongWrite_recomp(rdram, ctx);
        goto after_4;
    // 0x8007C2F0: addiu       $a3, $zero, 0x10
    ctx->r7 = ADD32(0, 0X10);
    after_4:
    // 0x8007C2F4: beql        $v0, $zero, L_8007C308
    if (ctx->r2 == 0) {
        // 0x8007C2F8: or          $v0, $zero, $zero
        ctx->r2 = 0 | 0;
            goto L_8007C308;
    }
    goto skip_0;
    // 0x8007C2F8: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    skip_0:
    // 0x8007C2FC: b           L_8007C308
    // 0x8007C300: addiu       $v0, $zero, 0x3
    ctx->r2 = ADD32(0, 0X3);
        goto L_8007C308;
    // 0x8007C300: addiu       $v0, $zero, 0x3
    ctx->r2 = ADD32(0, 0X3);
    // 0x8007C304: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_8007C308:
    // 0x8007C308: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    // 0x8007C30C: lw          $s0, 0x18($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X18);
    // 0x8007C310: addiu       $sp, $sp, 0x30
    ctx->r29 = ADD32(ctx->r29, 0X30);
    // 0x8007C314: jr          $ra
    // 0x8007C318: nop

    return;
    // 0x8007C318: nop

;}
RECOMP_FUNC void func_8007C31C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8007C31C: addiu       $sp, $sp, -0x30
    ctx->r29 = ADD32(ctx->r29, -0X30);
    // 0x8007C320: lui         $t6, 0x800E
    ctx->r14 = S32(0X800E << 16);
    // 0x8007C324: lw          $t6, -0x7DA0($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X7DA0);
    // 0x8007C328: sw          $ra, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r31;
    // 0x8007C32C: sw          $s5, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r21;
    // 0x8007C330: sw          $s4, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r20;
    // 0x8007C334: sw          $s3, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r19;
    // 0x8007C338: sw          $s2, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r18;
    // 0x8007C33C: sw          $s1, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r17;
    // 0x8007C340: bne         $t6, $zero, L_8007C350
    if (ctx->r14 != 0) {
        // 0x8007C344: sw          $s0, 0x14($sp)
        MEM_W(0X14, ctx->r29) = ctx->r16;
            goto L_8007C350;
    }
    // 0x8007C344: sw          $s0, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r16;
    // 0x8007C348: b           L_8007C470
    // 0x8007C34C: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
        goto L_8007C470;
    // 0x8007C34C: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
L_8007C350:
    // 0x8007C350: lui         $s3, 0x801B
    ctx->r19 = S32(0X801B << 16);
    // 0x8007C354: lui         $s4, 0x801D
    ctx->r20 = S32(0X801D << 16);
    // 0x8007C358: lui         $s1, 0x801D
    ctx->r17 = S32(0X801D << 16);
    // 0x8007C35C: addiu       $s1, $s1, -0x4CF8
    ctx->r17 = ADD32(ctx->r17, -0X4CF8);
    // 0x8007C360: addiu       $s4, $s4, -0x4D68
    ctx->r20 = ADD32(ctx->r20, -0X4D68);
    // 0x8007C364: addiu       $s3, $s3, -0x15D8
    ctx->r19 = ADD32(ctx->r19, -0X15D8);
    // 0x8007C368: or          $s2, $zero, $zero
    ctx->r18 = 0 | 0;
    // 0x8007C36C: addiu       $s5, $zero, 0x4
    ctx->r21 = ADD32(0, 0X4);
    // 0x8007C370: addiu       $s0, $zero, 0x3
    ctx->r16 = ADD32(0, 0X3);
L_8007C374:
    // 0x8007C374: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
    // 0x8007C378: or          $a1, $s4, $zero
    ctx->r5 = ctx->r20 | 0;
    // 0x8007C37C: jal         0x8006A140
    // 0x8007C380: addiu       $a2, $zero, 0xA
    ctx->r6 = ADD32(0, 0XA);
    Libc_strncpy(rdram, ctx);
        goto after_0;
    // 0x8007C380: addiu       $a2, $zero, 0xA
    ctx->r6 = ADD32(0, 0XA);
    after_0:
    // 0x8007C384: sll         $t0, $s2, 3
    ctx->r8 = S32(ctx->r18 << 3);
    // 0x8007C388: subu        $t0, $t0, $s2
    ctx->r8 = SUB32(ctx->r8, ctx->r18);
    // 0x8007C38C: sll         $t7, $s2, 2
    ctx->r15 = S32(ctx->r18 << 2);
    // 0x8007C390: lui         $t8, 0x801B
    ctx->r24 = S32(0X801B << 16);
    // 0x8007C394: lui         $t9, 0x801D
    ctx->r25 = S32(0X801D << 16);
    // 0x8007C398: addiu       $a2, $t9, -0x4D68
    ctx->r6 = ADD32(ctx->r25, -0X4D68);
    // 0x8007C39C: addiu       $t8, $t8, -0x15E8
    ctx->r24 = ADD32(ctx->r24, -0X15E8);
    // 0x8007C3A0: subu        $t7, $t7, $s2
    ctx->r15 = SUB32(ctx->r15, ctx->r18);
    // 0x8007C3A4: sll         $t0, $t0, 1
    ctx->r8 = S32(ctx->r8 << 1);
    // 0x8007C3A8: addu        $a3, $t0, $a2
    ctx->r7 = ADD32(ctx->r8, ctx->r6);
    // 0x8007C3AC: addu        $a1, $t7, $t8
    ctx->r5 = ADD32(ctx->r15, ctx->r24);
L_8007C3B0:
    // 0x8007C3B0: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    // 0x8007C3B4: or          $v1, $a1, $zero
    ctx->r3 = ctx->r5 | 0;
    // 0x8007C3B8: or          $a0, $a3, $zero
    ctx->r4 = ctx->r7 | 0;
L_8007C3BC:
    // 0x8007C3BC: lb          $t1, 0xB($a0)
    ctx->r9 = MEM_B(ctx->r4, 0XB);
    // 0x8007C3C0: addiu       $v0, $v0, 0x1
    ctx->r2 = ADD32(ctx->r2, 0X1);
    // 0x8007C3C4: addiu       $v1, $v1, 0x1
    ctx->r3 = ADD32(ctx->r3, 0X1);
    // 0x8007C3C8: addiu       $a0, $a0, 0x1
    ctx->r4 = ADD32(ctx->r4, 0X1);
    // 0x8007C3CC: bne         $v0, $s0, L_8007C3BC
    if (ctx->r2 != ctx->r16) {
        // 0x8007C3D0: sb          $t1, 0x37($v1)
        MEM_B(0X37, ctx->r3) = ctx->r9;
            goto L_8007C3BC;
    }
    // 0x8007C3D0: sb          $t1, 0x37($v1)
    MEM_B(0X37, ctx->r3) = ctx->r9;
    // 0x8007C3D4: addiu       $a2, $a2, 0x38
    ctx->r6 = ADD32(ctx->r6, 0X38);
    // 0x8007C3D8: sltu        $at, $a2, $s1
    ctx->r1 = ctx->r6 < ctx->r17 ? 1 : 0;
    // 0x8007C3DC: addiu       $a1, $a1, 0xC
    ctx->r5 = ADD32(ctx->r5, 0XC);
    // 0x8007C3E0: bne         $at, $zero, L_8007C3B0
    if (ctx->r1 != 0) {
        // 0x8007C3E4: addiu       $a3, $a3, 0x38
        ctx->r7 = ADD32(ctx->r7, 0X38);
            goto L_8007C3B0;
    }
    // 0x8007C3E4: addiu       $a3, $a3, 0x38
    ctx->r7 = ADD32(ctx->r7, 0X38);
    // 0x8007C3E8: addiu       $s2, $s2, 0x1
    ctx->r18 = ADD32(ctx->r18, 0X1);
    // 0x8007C3EC: addiu       $s3, $s3, 0xA
    ctx->r19 = ADD32(ctx->r19, 0XA);
    // 0x8007C3F0: bne         $s2, $s5, L_8007C374
    if (ctx->r18 != ctx->r21) {
        // 0x8007C3F4: addiu       $s4, $s4, 0xE
        ctx->r20 = ADD32(ctx->r20, 0XE);
            goto L_8007C374;
    }
    // 0x8007C3F4: addiu       $s4, $s4, 0xE
    ctx->r20 = ADD32(ctx->r20, 0XE);
    // 0x8007C3F8: jal         0x8007B31C
    // 0x8007C3FC: nop

    func_8007B31C(rdram, ctx);
        goto after_1;
    // 0x8007C3FC: nop

    after_1:
    // 0x8007C400: lui         $s0, 0x801B
    ctx->r16 = S32(0X801B << 16);
    // 0x8007C404: addiu       $s0, $s0, -0x15E8
    ctx->r16 = ADD32(ctx->r16, -0X15E8);
    // 0x8007C408: jal         0x8007BBF8
    // 0x8007C40C: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    Save_GenCheckSum(rdram, ctx);
        goto after_2;
    // 0x8007C40C: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_2:
    // 0x8007C410: lui         $s1, 0x8015
    ctx->r17 = S32(0X8015 << 16);
    // 0x8007C414: addiu       $s1, $s1, 0x40D0
    ctx->r17 = ADD32(ctx->r17, 0X40D0);
    // 0x8007C418: sh          $v0, 0x2($s0)
    MEM_H(0X2, ctx->r16) = ctx->r2;
    // 0x8007C41C: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    // 0x8007C420: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x8007C424: or          $a2, $s0, $zero
    ctx->r6 = ctx->r16 | 0;
    // 0x8007C428: jal         0x800C8410
    // 0x8007C42C: addiu       $a3, $zero, 0x10
    ctx->r7 = ADD32(0, 0X10);
    osEepromLongWrite_recomp(rdram, ctx);
        goto after_3;
    // 0x8007C42C: addiu       $a3, $zero, 0x10
    ctx->r7 = ADD32(0, 0X10);
    after_3:
    // 0x8007C430: beq         $v0, $zero, L_8007C440
    if (ctx->r2 == 0) {
        // 0x8007C434: lui         $a2, 0x801B
        ctx->r6 = S32(0X801B << 16);
            goto L_8007C440;
    }
    // 0x8007C434: lui         $a2, 0x801B
    ctx->r6 = S32(0X801B << 16);
    // 0x8007C438: b           L_8007C470
    // 0x8007C43C: addiu       $v0, $zero, 0x3
    ctx->r2 = ADD32(0, 0X3);
        goto L_8007C470;
    // 0x8007C43C: addiu       $v0, $zero, 0x3
    ctx->r2 = ADD32(0, 0X3);
L_8007C440:
    // 0x8007C440: addiu       $a2, $a2, -0x15D8
    ctx->r6 = ADD32(ctx->r6, -0X15D8);
    // 0x8007C444: subu        $a1, $a2, $s0
    ctx->r5 = SUB32(ctx->r6, ctx->r16);
    // 0x8007C448: srl         $t2, $a1, 3
    ctx->r10 = S32(U32(ctx->r5) >> 3);
    // 0x8007C44C: andi        $a1, $t2, 0xFF
    ctx->r5 = ctx->r10 & 0XFF;
    // 0x8007C450: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    // 0x8007C454: jal         0x800C8410
    // 0x8007C458: addiu       $a3, $zero, 0x40
    ctx->r7 = ADD32(0, 0X40);
    osEepromLongWrite_recomp(rdram, ctx);
        goto after_4;
    // 0x8007C458: addiu       $a3, $zero, 0x40
    ctx->r7 = ADD32(0, 0X40);
    after_4:
    // 0x8007C45C: beql        $v0, $zero, L_8007C470
    if (ctx->r2 == 0) {
        // 0x8007C460: or          $v0, $zero, $zero
        ctx->r2 = 0 | 0;
            goto L_8007C470;
    }
    goto skip_0;
    // 0x8007C460: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    skip_0:
    // 0x8007C464: b           L_8007C470
    // 0x8007C468: addiu       $v0, $zero, 0x3
    ctx->r2 = ADD32(0, 0X3);
        goto L_8007C470;
    // 0x8007C468: addiu       $v0, $zero, 0x3
    ctx->r2 = ADD32(0, 0X3);
    // 0x8007C46C: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_8007C470:
    // 0x8007C470: lw          $ra, 0x2C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X2C);
    // 0x8007C474: lw          $s0, 0x14($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X14);
    // 0x8007C478: lw          $s1, 0x18($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X18);
    // 0x8007C47C: lw          $s2, 0x1C($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X1C);
    // 0x8007C480: lw          $s3, 0x20($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X20);
    // 0x8007C484: lw          $s4, 0x24($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X24);
    // 0x8007C488: lw          $s5, 0x28($sp)
    ctx->r21 = MEM_W(ctx->r29, 0X28);
    // 0x8007C48C: jr          $ra
    // 0x8007C490: addiu       $sp, $sp, 0x30
    ctx->r29 = ADD32(ctx->r29, 0X30);
    return;
    // 0x8007C490: addiu       $sp, $sp, 0x30
    ctx->r29 = ADD32(ctx->r29, 0X30);
;}
RECOMP_FUNC void func_8007C494(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8007C494: lui         $t6, 0x800E
    ctx->r14 = S32(0X800E << 16);
    // 0x8007C498: lw          $t6, -0x7DA0($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X7DA0);
    // 0x8007C49C: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x8007C4A0: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x8007C4A4: bne         $t6, $zero, L_8007C4B4
    if (ctx->r14 != 0) {
        // 0x8007C4A8: nop
    
            goto L_8007C4B4;
    }
    // 0x8007C4A8: nop

    // 0x8007C4AC: b           L_8007C4FC
    // 0x8007C4B0: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
        goto L_8007C4FC;
    // 0x8007C4B0: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
L_8007C4B4:
    // 0x8007C4B4: jal         0x8007B31C
    // 0x8007C4B8: nop

    func_8007B31C(rdram, ctx);
        goto after_0;
    // 0x8007C4B8: nop

    after_0:
    // 0x8007C4BC: lui         $a0, 0x801B
    ctx->r4 = S32(0X801B << 16);
    // 0x8007C4C0: jal         0x8007BBF8
    // 0x8007C4C4: addiu       $a0, $a0, -0x15E8
    ctx->r4 = ADD32(ctx->r4, -0X15E8);
    Save_GenCheckSum(rdram, ctx);
        goto after_1;
    // 0x8007C4C4: addiu       $a0, $a0, -0x15E8
    ctx->r4 = ADD32(ctx->r4, -0X15E8);
    after_1:
    // 0x8007C4C8: lui         $a2, 0x801B
    ctx->r6 = S32(0X801B << 16);
    // 0x8007C4CC: addiu       $a2, $a2, -0x15E8
    ctx->r6 = ADD32(ctx->r6, -0X15E8);
    // 0x8007C4D0: lui         $a0, 0x8015
    ctx->r4 = S32(0X8015 << 16);
    // 0x8007C4D4: sh          $v0, 0x2($a2)
    MEM_H(0X2, ctx->r6) = ctx->r2;
    // 0x8007C4D8: addiu       $a0, $a0, 0x40D0
    ctx->r4 = ADD32(ctx->r4, 0X40D0);
    // 0x8007C4DC: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x8007C4E0: jal         0x800C8410
    // 0x8007C4E4: addiu       $a3, $zero, 0x10
    ctx->r7 = ADD32(0, 0X10);
    osEepromLongWrite_recomp(rdram, ctx);
        goto after_2;
    // 0x8007C4E4: addiu       $a3, $zero, 0x10
    ctx->r7 = ADD32(0, 0X10);
    after_2:
    // 0x8007C4E8: beql        $v0, $zero, L_8007C4FC
    if (ctx->r2 == 0) {
        // 0x8007C4EC: or          $v0, $zero, $zero
        ctx->r2 = 0 | 0;
            goto L_8007C4FC;
    }
    goto skip_0;
    // 0x8007C4EC: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    skip_0:
    // 0x8007C4F0: b           L_8007C4FC
    // 0x8007C4F4: addiu       $v0, $zero, 0x3
    ctx->r2 = ADD32(0, 0X3);
        goto L_8007C4FC;
    // 0x8007C4F4: addiu       $v0, $zero, 0x3
    ctx->r2 = ADD32(0, 0X3);
    // 0x8007C4F8: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_8007C4FC:
    // 0x8007C4FC: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x8007C500: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x8007C504: jr          $ra
    // 0x8007C508: nop

    return;
    // 0x8007C508: nop

;}
RECOMP_FUNC void func_8007C50C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8007C50C: lui         $t6, 0x800E
    ctx->r14 = S32(0X800E << 16);
    // 0x8007C510: lw          $t6, -0x7DA0($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X7DA0);
    // 0x8007C514: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x8007C518: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x8007C51C: bne         $t6, $zero, L_8007C52C
    if (ctx->r14 != 0) {
        // 0x8007C520: lui         $a3, 0x801B
        ctx->r7 = S32(0X801B << 16);
            goto L_8007C52C;
    }
    // 0x8007C520: lui         $a3, 0x801B
    ctx->r7 = S32(0X801B << 16);
    // 0x8007C524: b           L_8007C5F4
    // 0x8007C528: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
        goto L_8007C5F4;
    // 0x8007C528: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
L_8007C52C:
    // 0x8007C52C: lui         $a2, 0x801D
    ctx->r6 = S32(0X801D << 16);
    // 0x8007C530: lui         $t0, 0x801D
    ctx->r8 = S32(0X801D << 16);
    // 0x8007C534: addiu       $t0, $t0, -0x4CD4
    ctx->r8 = ADD32(ctx->r8, -0X4CD4);
    // 0x8007C538: addiu       $a2, $a2, -0x4CF8
    ctx->r6 = ADD32(ctx->r6, -0X4CF8);
    // 0x8007C53C: addiu       $a3, $a3, -0x15E8
    ctx->r7 = ADD32(ctx->r7, -0X15E8);
    // 0x8007C540: addiu       $a1, $zero, 0x3
    ctx->r5 = ADD32(0, 0X3);
L_8007C544:
    // 0x8007C544: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    // 0x8007C548: or          $v1, $a3, $zero
    ctx->r3 = ctx->r7 | 0;
    // 0x8007C54C: or          $a0, $a2, $zero
    ctx->r4 = ctx->r6 | 0;
L_8007C550:
    // 0x8007C550: lw          $t7, 0x0($a0)
    ctx->r15 = MEM_W(ctx->r4, 0X0);
    // 0x8007C554: addiu       $v0, $v0, 0x1
    ctx->r2 = ADD32(ctx->r2, 0X1);
    // 0x8007C558: addiu       $v1, $v1, 0x1
    ctx->r3 = ADD32(ctx->r3, 0X1);
    // 0x8007C55C: addiu       $a0, $a0, 0x4
    ctx->r4 = ADD32(ctx->r4, 0X4);
    // 0x8007C560: bne         $v0, $a1, L_8007C550
    if (ctx->r2 != ctx->r5) {
        // 0x8007C564: sb          $t7, 0x4F($v1)
        MEM_B(0X4F, ctx->r3) = ctx->r15;
            goto L_8007C550;
    }
    // 0x8007C564: sb          $t7, 0x4F($v1)
    MEM_B(0X4F, ctx->r3) = ctx->r15;
    // 0x8007C568: addiu       $a2, $a2, 0xC
    ctx->r6 = ADD32(ctx->r6, 0XC);
    // 0x8007C56C: bne         $a2, $t0, L_8007C544
    if (ctx->r6 != ctx->r8) {
        // 0x8007C570: addiu       $a3, $a3, 0x3
        ctx->r7 = ADD32(ctx->r7, 0X3);
            goto L_8007C544;
    }
    // 0x8007C570: addiu       $a3, $a3, 0x3
    ctx->r7 = ADD32(ctx->r7, 0X3);
    // 0x8007C574: jal         0x8007B31C
    // 0x8007C578: nop

    func_8007B31C(rdram, ctx);
        goto after_0;
    // 0x8007C578: nop

    after_0:
    // 0x8007C57C: lui         $a0, 0x801B
    ctx->r4 = S32(0X801B << 16);
    // 0x8007C580: jal         0x8007BBF8
    // 0x8007C584: addiu       $a0, $a0, -0x15E8
    ctx->r4 = ADD32(ctx->r4, -0X15E8);
    Save_GenCheckSum(rdram, ctx);
        goto after_1;
    // 0x8007C584: addiu       $a0, $a0, -0x15E8
    ctx->r4 = ADD32(ctx->r4, -0X15E8);
    after_1:
    // 0x8007C588: lui         $a2, 0x801B
    ctx->r6 = S32(0X801B << 16);
    // 0x8007C58C: addiu       $a2, $a2, -0x15E8
    ctx->r6 = ADD32(ctx->r6, -0X15E8);
    // 0x8007C590: lui         $a0, 0x8015
    ctx->r4 = S32(0X8015 << 16);
    // 0x8007C594: sh          $v0, 0x2($a2)
    MEM_H(0X2, ctx->r6) = ctx->r2;
    // 0x8007C598: addiu       $a0, $a0, 0x40D0
    ctx->r4 = ADD32(ctx->r4, 0X40D0);
    // 0x8007C59C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x8007C5A0: jal         0x800C8410
    // 0x8007C5A4: addiu       $a3, $zero, 0x10
    ctx->r7 = ADD32(0, 0X10);
    osEepromLongWrite_recomp(rdram, ctx);
        goto after_2;
    // 0x8007C5A4: addiu       $a3, $zero, 0x10
    ctx->r7 = ADD32(0, 0X10);
    after_2:
    // 0x8007C5A8: beq         $v0, $zero, L_8007C5B8
    if (ctx->r2 == 0) {
        // 0x8007C5AC: lui         $a2, 0x801B
        ctx->r6 = S32(0X801B << 16);
            goto L_8007C5B8;
    }
    // 0x8007C5AC: lui         $a2, 0x801B
    ctx->r6 = S32(0X801B << 16);
    // 0x8007C5B0: b           L_8007C5F4
    // 0x8007C5B4: addiu       $v0, $zero, 0x3
    ctx->r2 = ADD32(0, 0X3);
        goto L_8007C5F4;
    // 0x8007C5B4: addiu       $v0, $zero, 0x3
    ctx->r2 = ADD32(0, 0X3);
L_8007C5B8:
    // 0x8007C5B8: lui         $t8, 0x801B
    ctx->r24 = S32(0X801B << 16);
    // 0x8007C5BC: addiu       $a2, $a2, -0x1598
    ctx->r6 = ADD32(ctx->r6, -0X1598);
    // 0x8007C5C0: addiu       $t8, $t8, -0x15E8
    ctx->r24 = ADD32(ctx->r24, -0X15E8);
    // 0x8007C5C4: subu        $a1, $a2, $t8
    ctx->r5 = SUB32(ctx->r6, ctx->r24);
    // 0x8007C5C8: srl         $t9, $a1, 3
    ctx->r25 = S32(U32(ctx->r5) >> 3);
    // 0x8007C5CC: lui         $a0, 0x8015
    ctx->r4 = S32(0X8015 << 16);
    // 0x8007C5D0: addiu       $a0, $a0, 0x40D0
    ctx->r4 = ADD32(ctx->r4, 0X40D0);
    // 0x8007C5D4: andi        $a1, $t9, 0xFF
    ctx->r5 = ctx->r25 & 0XFF;
    // 0x8007C5D8: jal         0x800C8410
    // 0x8007C5DC: addiu       $a3, $zero, 0x10
    ctx->r7 = ADD32(0, 0X10);
    osEepromLongWrite_recomp(rdram, ctx);
        goto after_3;
    // 0x8007C5DC: addiu       $a3, $zero, 0x10
    ctx->r7 = ADD32(0, 0X10);
    after_3:
    // 0x8007C5E0: beql        $v0, $zero, L_8007C5F4
    if (ctx->r2 == 0) {
        // 0x8007C5E4: or          $v0, $zero, $zero
        ctx->r2 = 0 | 0;
            goto L_8007C5F4;
    }
    goto skip_0;
    // 0x8007C5E4: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    skip_0:
    // 0x8007C5E8: b           L_8007C5F4
    // 0x8007C5EC: addiu       $v0, $zero, 0x3
    ctx->r2 = ADD32(0, 0X3);
        goto L_8007C5F4;
    // 0x8007C5EC: addiu       $v0, $zero, 0x3
    ctx->r2 = ADD32(0, 0X3);
    // 0x8007C5F0: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_8007C5F4:
    // 0x8007C5F4: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x8007C5F8: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x8007C5FC: jr          $ra
    // 0x8007C600: nop

    return;
    // 0x8007C600: nop

;}
RECOMP_FUNC void func_8007C604(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8007C604: addiu       $sp, $sp, -0x58
    ctx->r29 = ADD32(ctx->r29, -0X58);
    // 0x8007C608: addiu       $a2, $a0, -0x1
    ctx->r6 = ADD32(ctx->r4, -0X1);
    // 0x8007C60C: sll         $t7, $a0, 4
    ctx->r15 = S32(ctx->r4 << 4);
    // 0x8007C610: subu        $t7, $t7, $a0
    ctx->r15 = SUB32(ctx->r15, ctx->r4);
    // 0x8007C614: sll         $t9, $a2, 2
    ctx->r25 = S32(ctx->r6 << 2);
    // 0x8007C618: lui         $t8, 0x801C
    ctx->r24 = S32(0X801C << 16);
    // 0x8007C61C: addiu       $t8, $t8, 0x1FF0
    ctx->r24 = ADD32(ctx->r24, 0X1FF0);
    // 0x8007C620: addu        $t9, $t9, $a2
    ctx->r25 = ADD32(ctx->r25, ctx->r6);
    // 0x8007C624: sll         $t7, $t7, 2
    ctx->r15 = S32(ctx->r15 << 2);
    // 0x8007C628: lui         $t1, 0x800E
    ctx->r9 = S32(0X800E << 16);
    // 0x8007C62C: sw          $s0, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r16;
    // 0x8007C630: addiu       $t1, $t1, -0x7D08
    ctx->r9 = ADD32(ctx->r9, -0X7D08);
    // 0x8007C634: addu        $a3, $t7, $t8
    ctx->r7 = ADD32(ctx->r15, ctx->r24);
    // 0x8007C638: sll         $t9, $t9, 4
    ctx->r25 = S32(ctx->r25 << 4);
    // 0x8007C63C: sw          $ra, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r31;
    // 0x8007C640: sw          $s3, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r19;
    // 0x8007C644: sw          $s2, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r18;
    // 0x8007C648: sw          $s1, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r17;
    // 0x8007C64C: sw          $a0, 0x58($sp)
    MEM_W(0X58, ctx->r29) = ctx->r4;
    // 0x8007C650: addu        $v0, $t9, $t1
    ctx->r2 = ADD32(ctx->r25, ctx->r9);
    // 0x8007C654: or          $s0, $a3, $zero
    ctx->r16 = ctx->r7 | 0;
    // 0x8007C658: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
L_8007C65C:
    // 0x8007C65C: lw          $at, 0x0($v0)
    ctx->r1 = MEM_W(ctx->r2, 0X0);
    // 0x8007C660: lw          $t4, 0x4($v0)
    ctx->r12 = MEM_W(ctx->r2, 0X4);
    // 0x8007C664: addiu       $v1, $v1, 0x1
    ctx->r3 = ADD32(ctx->r3, 0X1);
    // 0x8007C668: sw          $at, 0x0($s0)
    MEM_W(0X0, ctx->r16) = ctx->r1;
    // 0x8007C66C: lw          $at, 0x8($v0)
    ctx->r1 = MEM_W(ctx->r2, 0X8);
    // 0x8007C670: sw          $t4, 0x4($s0)
    MEM_W(0X4, ctx->r16) = ctx->r12;
    // 0x8007C674: lw          $t4, 0xC($v0)
    ctx->r12 = MEM_W(ctx->r2, 0XC);
    // 0x8007C678: sw          $at, 0x8($s0)
    MEM_W(0X8, ctx->r16) = ctx->r1;
    // 0x8007C67C: lw          $at, 0x10($v0)
    ctx->r1 = MEM_W(ctx->r2, 0X10);
    // 0x8007C680: addiu       $s0, $s0, 0x14
    ctx->r16 = ADD32(ctx->r16, 0X14);
    // 0x8007C684: addiu       $v0, $v0, 0x14
    ctx->r2 = ADD32(ctx->r2, 0X14);
    // 0x8007C688: sw          $at, -0x4($s0)
    MEM_W(-0X4, ctx->r16) = ctx->r1;
    // 0x8007C68C: slti        $at, $v1, 0x3
    ctx->r1 = SIGNED(ctx->r3) < 0X3 ? 1 : 0;
    // 0x8007C690: bne         $at, $zero, L_8007C65C
    if (ctx->r1 != 0) {
        // 0x8007C694: sw          $t4, -0x8($s0)
        MEM_W(-0X8, ctx->r16) = ctx->r12;
            goto L_8007C65C;
    }
    // 0x8007C694: sw          $t4, -0x8($s0)
    MEM_W(-0X8, ctx->r16) = ctx->r12;
    // 0x8007C698: lw          $a1, 0x58($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X58);
    // 0x8007C69C: lw          $at, 0x0($v0)
    ctx->r1 = MEM_W(ctx->r2, 0X0);
    // 0x8007C6A0: lui         $t6, 0x801C
    ctx->r14 = S32(0X801C << 16);
    // 0x8007C6A4: sll         $t5, $a1, 2
    ctx->r13 = S32(ctx->r5 << 2);
    // 0x8007C6A8: addu        $t5, $t5, $a1
    ctx->r13 = ADD32(ctx->r13, ctx->r5);
    // 0x8007C6AC: sll         $a1, $t5, 2
    ctx->r5 = S32(ctx->r13 << 2);
    // 0x8007C6B0: addiu       $t6, $t6, 0x22C0
    ctx->r14 = ADD32(ctx->r14, 0X22C0);
    // 0x8007C6B4: addu        $s3, $a1, $t6
    ctx->r19 = ADD32(ctx->r5, ctx->r14);
    // 0x8007C6B8: sw          $at, 0x0($s3)
    MEM_W(0X0, ctx->r19) = ctx->r1;
    // 0x8007C6BC: lw          $at, 0x8($v0)
    ctx->r1 = MEM_W(ctx->r2, 0X8);
    // 0x8007C6C0: lw          $t8, 0x4($v0)
    ctx->r24 = MEM_W(ctx->r2, 0X4);
    // 0x8007C6C4: lw          $t9, 0x58($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X58);
    // 0x8007C6C8: sw          $at, 0x8($s3)
    MEM_W(0X8, ctx->r19) = ctx->r1;
    // 0x8007C6CC: sw          $t8, 0x4($s3)
    MEM_W(0X4, ctx->r19) = ctx->r24;
    // 0x8007C6D0: lw          $t8, 0xC($v0)
    ctx->r24 = MEM_W(ctx->r2, 0XC);
    // 0x8007C6D4: lw          $at, 0x10($v0)
    ctx->r1 = MEM_W(ctx->r2, 0X10);
    // 0x8007C6D8: sll         $t2, $a2, 2
    ctx->r10 = S32(ctx->r6 << 2);
    // 0x8007C6DC: sll         $t1, $t9, 3
    ctx->r9 = S32(ctx->r25 << 3);
    // 0x8007C6E0: addu        $t2, $t2, $a2
    ctx->r10 = ADD32(ctx->r10, ctx->r6);
    // 0x8007C6E4: lui         $t3, 0x801C
    ctx->r11 = S32(0X801C << 16);
    // 0x8007C6E8: addu        $t1, $t1, $t9
    ctx->r9 = ADD32(ctx->r9, ctx->r25);
    // 0x8007C6EC: sll         $t1, $t1, 2
    ctx->r9 = S32(ctx->r9 << 2);
    // 0x8007C6F0: addiu       $t3, $t3, 0x24A0
    ctx->r11 = ADD32(ctx->r11, 0X24A0);
    // 0x8007C6F4: sll         $t2, $t2, 4
    ctx->r10 = S32(ctx->r10 << 4);
    // 0x8007C6F8: lui         $a0, 0x800E
    ctx->r4 = S32(0X800E << 16);
    // 0x8007C6FC: addu        $a0, $a0, $t2
    ctx->r4 = ADD32(ctx->r4, ctx->r10);
    // 0x8007C700: addu        $t0, $t1, $t3
    ctx->r8 = ADD32(ctx->r9, ctx->r11);
    // 0x8007C704: sw          $t8, 0xC($s3)
    MEM_W(0XC, ctx->r19) = ctx->r24;
    // 0x8007C708: sw          $at, 0x10($s3)
    MEM_W(0X10, ctx->r19) = ctx->r1;
    // 0x8007C70C: lw          $a0, -0x7CCC($a0)
    ctx->r4 = MEM_W(ctx->r4, -0X7CCC);
    // 0x8007C710: or          $s0, $t0, $zero
    ctx->r16 = ctx->r8 | 0;
    // 0x8007C714: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
    // 0x8007C718: addiu       $v0, $v1, 0x1
    ctx->r2 = ADD32(ctx->r3, 0X1);
L_8007C71C:
    // 0x8007C71C: multu       $a0, $v0
    result = U64(U32(ctx->r4)) * U64(U32(ctx->r2)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x8007C720: slti        $at, $v0, 0x2
    ctx->r1 = SIGNED(ctx->r2) < 0X2 ? 1 : 0;
    // 0x8007C724: or          $v1, $v0, $zero
    ctx->r3 = ctx->r2 | 0;
    // 0x8007C728: addiu       $s0, $s0, 0x4
    ctx->r16 = ADD32(ctx->r16, 0X4);
    // 0x8007C72C: mflo        $t4
    ctx->r12 = lo;
    // 0x8007C730: sw          $t4, -0x4($s0)
    MEM_W(-0X4, ctx->r16) = ctx->r12;
    // 0x8007C734: bnel        $at, $zero, L_8007C71C
    if (ctx->r1 != 0) {
        // 0x8007C738: addiu       $v0, $v1, 0x1
        ctx->r2 = ADD32(ctx->r3, 0X1);
            goto L_8007C71C;
    }
    goto skip_0;
    // 0x8007C738: addiu       $v0, $v1, 0x1
    ctx->r2 = ADD32(ctx->r3, 0X1);
    skip_0:
    // 0x8007C73C: lui         $t6, 0x800E
    ctx->r14 = S32(0X800E << 16);
    // 0x8007C740: addiu       $t6, $t6, -0x78D8
    ctx->r14 = ADD32(ctx->r14, -0X78D8);
    // 0x8007C744: lw          $at, 0x0($t6)
    ctx->r1 = MEM_W(ctx->r14, 0X0);
    // 0x8007C748: lui         $t5, 0x801C
    ctx->r13 = S32(0X801C << 16);
    // 0x8007C74C: addiu       $t5, $t5, 0x23B0
    ctx->r13 = ADD32(ctx->r13, 0X23B0);
    // 0x8007C750: addu        $v0, $a1, $t5
    ctx->r2 = ADD32(ctx->r5, ctx->r13);
    // 0x8007C754: sw          $at, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r1;
    // 0x8007C758: lw          $t8, 0x4($t6)
    ctx->r24 = MEM_W(ctx->r14, 0X4);
    // 0x8007C75C: sll         $t9, $a2, 2
    ctx->r25 = S32(ctx->r6 << 2);
    // 0x8007C760: subu        $t9, $t9, $a2
    ctx->r25 = SUB32(ctx->r25, ctx->r6);
    // 0x8007C764: sw          $t8, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r24;
    // 0x8007C768: lw          $at, 0x8($t6)
    ctx->r1 = MEM_W(ctx->r14, 0X8);
    // 0x8007C76C: sll         $t9, $t9, 3
    ctx->r25 = S32(ctx->r25 << 3);
    // 0x8007C770: lui         $t3, 0x801B
    ctx->r11 = S32(0X801B << 16);
    // 0x8007C774: sw          $at, 0x8($v0)
    MEM_W(0X8, ctx->r2) = ctx->r1;
    // 0x8007C778: lw          $t8, 0xC($t6)
    ctx->r24 = MEM_W(ctx->r14, 0XC);
    // 0x8007C77C: addiu       $t3, $t3, -0x15E8
    ctx->r11 = ADD32(ctx->r11, -0X15E8);
    // 0x8007C780: addiu       $t1, $t9, 0x60
    ctx->r9 = ADD32(ctx->r25, 0X60);
    // 0x8007C784: sw          $t8, 0xC($v0)
    MEM_W(0XC, ctx->r2) = ctx->r24;
    // 0x8007C788: lw          $at, 0x10($t6)
    ctx->r1 = MEM_W(ctx->r14, 0X10);
    // 0x8007C78C: sw          $t0, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r8;
    // 0x8007C790: sw          $a2, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r6;
    // 0x8007C794: sw          $v0, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r2;
    // 0x8007C798: addu        $s1, $t1, $t3
    ctx->r17 = ADD32(ctx->r9, ctx->r11);
    // 0x8007C79C: or          $s0, $a3, $zero
    ctx->r16 = ctx->r7 | 0;
    // 0x8007C7A0: or          $s2, $zero, $zero
    ctx->r18 = 0 | 0;
    // 0x8007C7A4: sw          $at, 0x10($v0)
    MEM_W(0X10, ctx->r2) = ctx->r1;
L_8007C7A8:
    // 0x8007C7A8: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x8007C7AC: jal         0x8007AF78
    // 0x8007C7B0: or          $a1, $s1, $zero
    ctx->r5 = ctx->r17 | 0;
    func_8007AF78(rdram, ctx);
        goto after_0;
    // 0x8007C7B0: or          $a1, $s1, $zero
    ctx->r5 = ctx->r17 | 0;
    after_0:
    // 0x8007C7B4: addiu       $s2, $s2, 0x6
    ctx->r18 = ADD32(ctx->r18, 0X6);
    // 0x8007C7B8: slti        $at, $s2, 0x12
    ctx->r1 = SIGNED(ctx->r18) < 0X12 ? 1 : 0;
    // 0x8007C7BC: addiu       $s0, $s0, 0x14
    ctx->r16 = ADD32(ctx->r16, 0X14);
    // 0x8007C7C0: bne         $at, $zero, L_8007C7A8
    if (ctx->r1 != 0) {
        // 0x8007C7C4: addiu       $s1, $s1, 0x6
        ctx->r17 = ADD32(ctx->r17, 0X6);
            goto L_8007C7A8;
    }
    // 0x8007C7C4: addiu       $s1, $s1, 0x6
    ctx->r17 = ADD32(ctx->r17, 0X6);
    // 0x8007C7C8: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
    // 0x8007C7CC: jal         0x8007AF78
    // 0x8007C7D0: or          $a1, $s1, $zero
    ctx->r5 = ctx->r17 | 0;
    func_8007AF78(rdram, ctx);
        goto after_1;
    // 0x8007C7D0: or          $a1, $s1, $zero
    ctx->r5 = ctx->r17 | 0;
    after_1:
    // 0x8007C7D4: lw          $t2, 0x48($sp)
    ctx->r10 = MEM_W(ctx->r29, 0X48);
    // 0x8007C7D8: lui         $t7, 0x801B
    ctx->r15 = S32(0X801B << 16);
    // 0x8007C7DC: addiu       $t7, $t7, -0x15E8
    ctx->r15 = ADD32(ctx->r15, -0X15E8);
    // 0x8007C7E0: sll         $t4, $t2, 2
    ctx->r12 = S32(ctx->r10 << 2);
    // 0x8007C7E4: subu        $t4, $t4, $t2
    ctx->r12 = SUB32(ctx->r12, ctx->r10);
    // 0x8007C7E8: sll         $t4, $t4, 1
    ctx->r12 = S32(ctx->r12 << 1);
    // 0x8007C7EC: addiu       $t5, $t4, 0x1A8
    ctx->r13 = ADD32(ctx->r12, 0X1A8);
    // 0x8007C7F0: addu        $s2, $t5, $t7
    ctx->r18 = ADD32(ctx->r13, ctx->r15);
    // 0x8007C7F4: lw          $s0, 0x28($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X28);
    // 0x8007C7F8: or          $s1, $zero, $zero
    ctx->r17 = 0 | 0;
    // 0x8007C7FC: addiu       $s3, $zero, 0x6
    ctx->r19 = ADD32(0, 0X6);
L_8007C800:
    // 0x8007C800: lw          $a0, 0x0($s0)
    ctx->r4 = MEM_W(ctx->r16, 0X0);
    // 0x8007C804: jal         0x8007B2BC
    // 0x8007C808: or          $a1, $s2, $zero
    ctx->r5 = ctx->r18 | 0;
    func_8007B2BC(rdram, ctx);
        goto after_2;
    // 0x8007C808: or          $a1, $s2, $zero
    ctx->r5 = ctx->r18 | 0;
    after_2:
    // 0x8007C80C: addiu       $s1, $s1, 0x3
    ctx->r17 = ADD32(ctx->r17, 0X3);
    // 0x8007C810: addiu       $s0, $s0, 0x4
    ctx->r16 = ADD32(ctx->r16, 0X4);
    // 0x8007C814: bne         $s1, $s3, L_8007C800
    if (ctx->r17 != ctx->r19) {
        // 0x8007C818: addiu       $s2, $s2, 0x3
        ctx->r18 = ADD32(ctx->r18, 0X3);
            goto L_8007C800;
    }
    // 0x8007C818: addiu       $s2, $s2, 0x3
    ctx->r18 = ADD32(ctx->r18, 0X3);
    // 0x8007C81C: lw          $t6, 0x48($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X48);
    // 0x8007C820: lui         $s0, 0x801B
    ctx->r16 = S32(0X801B << 16);
    // 0x8007C824: addiu       $s0, $s0, -0x15E8
    ctx->r16 = ADD32(ctx->r16, -0X15E8);
    // 0x8007C828: sll         $t8, $t6, 2
    ctx->r24 = S32(ctx->r14 << 2);
    // 0x8007C82C: addu        $t8, $t8, $t6
    ctx->r24 = ADD32(ctx->r24, ctx->r14);
    // 0x8007C830: addu        $a1, $s0, $t8
    ctx->r5 = ADD32(ctx->r16, ctx->r24);
    // 0x8007C834: addiu       $a1, $a1, 0x1D8
    ctx->r5 = ADD32(ctx->r5, 0X1D8);
    // 0x8007C838: jal         0x8007B09C
    // 0x8007C83C: lw          $a0, 0x34($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X34);
    func_8007B09C(rdram, ctx);
        goto after_3;
    // 0x8007C83C: lw          $a0, 0x34($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X34);
    after_3:
    // 0x8007C840: jal         0x8007B31C
    // 0x8007C844: nop

    func_8007B31C(rdram, ctx);
        goto after_4;
    // 0x8007C844: nop

    after_4:
    // 0x8007C848: jal         0x8007BBF8
    // 0x8007C84C: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    Save_GenCheckSum(rdram, ctx);
        goto after_5;
    // 0x8007C84C: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_5:
    // 0x8007C850: sh          $v0, 0x2($s0)
    MEM_H(0X2, ctx->r16) = ctx->r2;
    // 0x8007C854: lui         $t9, 0x800E
    ctx->r25 = S32(0X800E << 16);
    // 0x8007C858: lw          $t9, -0x7DA0($t9)
    ctx->r25 = MEM_W(ctx->r25, -0X7DA0);
    // 0x8007C85C: lui         $s3, 0x8015
    ctx->r19 = S32(0X8015 << 16);
    // 0x8007C860: addiu       $s3, $s3, 0x40D0
    ctx->r19 = ADD32(ctx->r19, 0X40D0);
    // 0x8007C864: bne         $t9, $zero, L_8007C874
    if (ctx->r25 != 0) {
        // 0x8007C868: or          $a0, $s3, $zero
        ctx->r4 = ctx->r19 | 0;
            goto L_8007C874;
    }
    // 0x8007C868: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
    // 0x8007C86C: b           L_8007C9B8
    // 0x8007C870: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
        goto L_8007C9B8;
    // 0x8007C870: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
L_8007C874:
    // 0x8007C874: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x8007C878: or          $a2, $s0, $zero
    ctx->r6 = ctx->r16 | 0;
    // 0x8007C87C: jal         0x800C8410
    // 0x8007C880: addiu       $a3, $zero, 0x10
    ctx->r7 = ADD32(0, 0X10);
    osEepromLongWrite_recomp(rdram, ctx);
        goto after_6;
    // 0x8007C880: addiu       $a3, $zero, 0x10
    ctx->r7 = ADD32(0, 0X10);
    after_6:
    // 0x8007C884: beq         $v0, $zero, L_8007C894
    if (ctx->r2 == 0) {
        // 0x8007C888: or          $a0, $s3, $zero
        ctx->r4 = ctx->r19 | 0;
            goto L_8007C894;
    }
    // 0x8007C888: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
    // 0x8007C88C: b           L_8007C9B8
    // 0x8007C890: addiu       $v0, $zero, 0x3
    ctx->r2 = ADD32(0, 0X3);
        goto L_8007C9B8;
    // 0x8007C890: addiu       $v0, $zero, 0x3
    ctx->r2 = ADD32(0, 0X3);
L_8007C894:
    // 0x8007C894: lw          $t1, 0x48($sp)
    ctx->r9 = MEM_W(ctx->r29, 0X48);
    // 0x8007C898: or          $s1, $s0, $zero
    ctx->r17 = ctx->r16 | 0;
    // 0x8007C89C: addiu       $a3, $zero, 0x18
    ctx->r7 = ADD32(0, 0X18);
    // 0x8007C8A0: sll         $t3, $t1, 2
    ctx->r11 = S32(ctx->r9 << 2);
    // 0x8007C8A4: subu        $t3, $t3, $t1
    ctx->r11 = SUB32(ctx->r11, ctx->r9);
    // 0x8007C8A8: sll         $t3, $t3, 3
    ctx->r11 = S32(ctx->r11 << 3);
    // 0x8007C8AC: addu        $a2, $s0, $t3
    ctx->r6 = ADD32(ctx->r16, ctx->r11);
    // 0x8007C8B0: addiu       $a2, $a2, 0x60
    ctx->r6 = ADD32(ctx->r6, 0X60);
    // 0x8007C8B4: subu        $a1, $a2, $s0
    ctx->r5 = SUB32(ctx->r6, ctx->r16);
    // 0x8007C8B8: srl         $t2, $a1, 3
    ctx->r10 = S32(U32(ctx->r5) >> 3);
    // 0x8007C8BC: jal         0x800C8410
    // 0x8007C8C0: andi        $a1, $t2, 0xFF
    ctx->r5 = ctx->r10 & 0XFF;
    osEepromLongWrite_recomp(rdram, ctx);
        goto after_7;
    // 0x8007C8C0: andi        $a1, $t2, 0xFF
    ctx->r5 = ctx->r10 & 0XFF;
    after_7:
    // 0x8007C8C4: beq         $v0, $zero, L_8007C8D4
    if (ctx->r2 == 0) {
        // 0x8007C8C8: lw          $t5, 0x58($sp)
        ctx->r13 = MEM_W(ctx->r29, 0X58);
            goto L_8007C8D4;
    }
    // 0x8007C8C8: lw          $t5, 0x58($sp)
    ctx->r13 = MEM_W(ctx->r29, 0X58);
    // 0x8007C8CC: b           L_8007C9B8
    // 0x8007C8D0: addiu       $v0, $zero, 0x3
    ctx->r2 = ADD32(0, 0X3);
        goto L_8007C9B8;
    // 0x8007C8D0: addiu       $v0, $zero, 0x3
    ctx->r2 = ADD32(0, 0X3);
L_8007C8D4:
    // 0x8007C8D4: sll         $t7, $t5, 2
    ctx->r15 = S32(ctx->r13 << 2);
    // 0x8007C8D8: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x8007C8DC: addu        $v0, $v0, $t7
    ctx->r2 = ADD32(ctx->r2, ctx->r15);
    // 0x8007C8E0: lw          $v0, -0x7D94($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X7D94);
    // 0x8007C8E4: lui         $t6, 0x801B
    ctx->r14 = S32(0X801B << 16);
    // 0x8007C8E8: addiu       $t6, $t6, -0x14C8
    ctx->r14 = ADD32(ctx->r14, -0X14C8);
    // 0x8007C8EC: subu        $t8, $t6, $s1
    ctx->r24 = SUB32(ctx->r14, ctx->r17);
    // 0x8007C8F0: addu        $a1, $t8, $v0
    ctx->r5 = ADD32(ctx->r24, ctx->r2);
    // 0x8007C8F4: srl         $t9, $a1, 3
    ctx->r25 = S32(U32(ctx->r5) >> 3);
    // 0x8007C8F8: addu        $a2, $s0, $v0
    ctx->r6 = ADD32(ctx->r16, ctx->r2);
    // 0x8007C8FC: addiu       $a2, $a2, 0x120
    ctx->r6 = ADD32(ctx->r6, 0X120);
    // 0x8007C900: andi        $a1, $t9, 0xFF
    ctx->r5 = ctx->r25 & 0XFF;
    // 0x8007C904: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
    // 0x8007C908: jal         0x800C8410
    // 0x8007C90C: addiu       $a3, $zero, 0x18
    ctx->r7 = ADD32(0, 0X18);
    osEepromLongWrite_recomp(rdram, ctx);
        goto after_8;
    // 0x8007C90C: addiu       $a3, $zero, 0x18
    ctx->r7 = ADD32(0, 0X18);
    after_8:
    // 0x8007C910: beq         $v0, $zero, L_8007C920
    if (ctx->r2 == 0) {
        // 0x8007C914: lw          $s2, 0x48($sp)
        ctx->r18 = MEM_W(ctx->r29, 0X48);
            goto L_8007C920;
    }
    // 0x8007C914: lw          $s2, 0x48($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X48);
    // 0x8007C918: b           L_8007C9B8
    // 0x8007C91C: addiu       $v0, $zero, 0x3
    ctx->r2 = ADD32(0, 0X3);
        goto L_8007C9B8;
    // 0x8007C91C: addiu       $v0, $zero, 0x3
    ctx->r2 = ADD32(0, 0X3);
L_8007C920:
    // 0x8007C920: sll         $t3, $s2, 2
    ctx->r11 = S32(ctx->r18 << 2);
    // 0x8007C924: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x8007C928: addu        $v0, $v0, $t3
    ctx->r2 = ADD32(ctx->r2, ctx->r11);
    // 0x8007C92C: lw          $v0, -0x7D50($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X7D50);
    // 0x8007C930: lui         $t2, 0x801B
    ctx->r10 = S32(0X801B << 16);
    // 0x8007C934: addiu       $t2, $t2, -0x1440
    ctx->r10 = ADD32(ctx->r10, -0X1440);
    // 0x8007C938: subu        $t4, $t2, $s1
    ctx->r12 = SUB32(ctx->r10, ctx->r17);
    // 0x8007C93C: addu        $a1, $t4, $v0
    ctx->r5 = ADD32(ctx->r12, ctx->r2);
    // 0x8007C940: srl         $t5, $a1, 3
    ctx->r13 = S32(U32(ctx->r5) >> 3);
    // 0x8007C944: addu        $a2, $s0, $v0
    ctx->r6 = ADD32(ctx->r16, ctx->r2);
    // 0x8007C948: or          $s2, $t3, $zero
    ctx->r18 = ctx->r11 | 0;
    // 0x8007C94C: addiu       $a2, $a2, 0x1A8
    ctx->r6 = ADD32(ctx->r6, 0X1A8);
    // 0x8007C950: andi        $a1, $t5, 0xFF
    ctx->r5 = ctx->r13 & 0XFF;
    // 0x8007C954: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
    // 0x8007C958: jal         0x800C8410
    // 0x8007C95C: addiu       $a3, $zero, 0x10
    ctx->r7 = ADD32(0, 0X10);
    osEepromLongWrite_recomp(rdram, ctx);
        goto after_9;
    // 0x8007C95C: addiu       $a3, $zero, 0x10
    ctx->r7 = ADD32(0, 0X10);
    after_9:
    // 0x8007C960: beq         $v0, $zero, L_8007C970
    if (ctx->r2 == 0) {
        // 0x8007C964: or          $a0, $s3, $zero
        ctx->r4 = ctx->r19 | 0;
            goto L_8007C970;
    }
    // 0x8007C964: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
    // 0x8007C968: b           L_8007C9B8
    // 0x8007C96C: addiu       $v0, $zero, 0x3
    ctx->r2 = ADD32(0, 0X3);
        goto L_8007C9B8;
    // 0x8007C96C: addiu       $v0, $zero, 0x3
    ctx->r2 = ADD32(0, 0X3);
L_8007C970:
    // 0x8007C970: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x8007C974: addu        $v0, $v0, $s2
    ctx->r2 = ADD32(ctx->r2, ctx->r18);
    // 0x8007C978: lw          $v0, -0x7D70($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X7D70);
    // 0x8007C97C: lui         $t6, 0x801B
    ctx->r14 = S32(0X801B << 16);
    // 0x8007C980: addiu       $t6, $t6, -0x1410
    ctx->r14 = ADD32(ctx->r14, -0X1410);
    // 0x8007C984: subu        $t8, $t6, $s1
    ctx->r24 = SUB32(ctx->r14, ctx->r17);
    // 0x8007C988: addu        $a1, $t8, $v0
    ctx->r5 = ADD32(ctx->r24, ctx->r2);
    // 0x8007C98C: srl         $t9, $a1, 3
    ctx->r25 = S32(U32(ctx->r5) >> 3);
    // 0x8007C990: addu        $a2, $s0, $v0
    ctx->r6 = ADD32(ctx->r16, ctx->r2);
    // 0x8007C994: addiu       $a2, $a2, 0x1D8
    ctx->r6 = ADD32(ctx->r6, 0X1D8);
    // 0x8007C998: andi        $a1, $t9, 0xFF
    ctx->r5 = ctx->r25 & 0XFF;
    // 0x8007C99C: jal         0x800C8410
    // 0x8007C9A0: addiu       $a3, $zero, 0x10
    ctx->r7 = ADD32(0, 0X10);
    osEepromLongWrite_recomp(rdram, ctx);
        goto after_10;
    // 0x8007C9A0: addiu       $a3, $zero, 0x10
    ctx->r7 = ADD32(0, 0X10);
    after_10:
    // 0x8007C9A4: beql        $v0, $zero, L_8007C9B8
    if (ctx->r2 == 0) {
        // 0x8007C9A8: or          $v0, $zero, $zero
        ctx->r2 = 0 | 0;
            goto L_8007C9B8;
    }
    goto skip_1;
    // 0x8007C9A8: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    skip_1:
    // 0x8007C9AC: b           L_8007C9B8
    // 0x8007C9B0: addiu       $v0, $zero, 0x3
    ctx->r2 = ADD32(0, 0X3);
        goto L_8007C9B8;
    // 0x8007C9B0: addiu       $v0, $zero, 0x3
    ctx->r2 = ADD32(0, 0X3);
    // 0x8007C9B4: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_8007C9B8:
    // 0x8007C9B8: lw          $ra, 0x24($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X24);
    // 0x8007C9BC: lw          $s0, 0x14($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X14);
    // 0x8007C9C0: lw          $s1, 0x18($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X18);
    // 0x8007C9C4: lw          $s2, 0x1C($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X1C);
    // 0x8007C9C8: lw          $s3, 0x20($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X20);
    // 0x8007C9CC: jr          $ra
    // 0x8007C9D0: addiu       $sp, $sp, 0x58
    ctx->r29 = ADD32(ctx->r29, 0X58);
    return;
    // 0x8007C9D0: addiu       $sp, $sp, 0x58
    ctx->r29 = ADD32(ctx->r29, 0X58);
;}
RECOMP_FUNC void func_8007C9D4(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8007C9D4: addiu       $sp, $sp, -0x28
    ctx->r29 = ADD32(ctx->r29, -0X28);
    // 0x8007C9D8: sll         $t6, $a0, 2
    ctx->r14 = S32(ctx->r4 << 2);
    // 0x8007C9DC: subu        $t6, $t6, $a0
    ctx->r14 = SUB32(ctx->r14, ctx->r4);
    // 0x8007C9E0: lui         $t7, 0x801C
    ctx->r15 = S32(0X801C << 16);
    // 0x8007C9E4: sll         $t8, $a0, 2
    ctx->r24 = S32(ctx->r4 << 2);
    // 0x8007C9E8: subu        $t8, $t8, $a0
    ctx->r24 = SUB32(ctx->r24, ctx->r4);
    // 0x8007C9EC: addiu       $t7, $t7, 0x26E8
    ctx->r15 = ADD32(ctx->r15, 0X26E8);
    // 0x8007C9F0: sll         $t6, $t6, 4
    ctx->r14 = S32(ctx->r14 << 4);
    // 0x8007C9F4: lui         $t9, 0x800E
    ctx->r25 = S32(0X800E << 16);
    // 0x8007C9F8: sw          $s0, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r16;
    // 0x8007C9FC: addiu       $t9, $t9, -0x7A88
    ctx->r25 = ADD32(ctx->r25, -0X7A88);
    // 0x8007CA00: addu        $a1, $t6, $t7
    ctx->r5 = ADD32(ctx->r14, ctx->r15);
    // 0x8007CA04: sll         $t8, $t8, 4
    ctx->r24 = S32(ctx->r24 << 4);
    // 0x8007CA08: sw          $ra, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r31;
    // 0x8007CA0C: sw          $s3, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r19;
    // 0x8007CA10: sw          $s2, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r18;
    // 0x8007CA14: sw          $s1, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r17;
    // 0x8007CA18: or          $a2, $a0, $zero
    ctx->r6 = ctx->r4 | 0;
    // 0x8007CA1C: addu        $v1, $t8, $t9
    ctx->r3 = ADD32(ctx->r24, ctx->r25);
    // 0x8007CA20: or          $s0, $a1, $zero
    ctx->r16 = ctx->r5 | 0;
    // 0x8007CA24: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_8007CA28:
    // 0x8007CA28: lw          $at, 0x0($v1)
    ctx->r1 = MEM_W(ctx->r3, 0X0);
    // 0x8007CA2C: lw          $t2, 0x4($v1)
    ctx->r10 = MEM_W(ctx->r3, 0X4);
    // 0x8007CA30: addiu       $v0, $v0, 0x1
    ctx->r2 = ADD32(ctx->r2, 0X1);
    // 0x8007CA34: sw          $at, 0x0($s0)
    MEM_W(0X0, ctx->r16) = ctx->r1;
    // 0x8007CA38: lw          $at, 0x8($v1)
    ctx->r1 = MEM_W(ctx->r3, 0X8);
    // 0x8007CA3C: sw          $t2, 0x4($s0)
    MEM_W(0X4, ctx->r16) = ctx->r10;
    // 0x8007CA40: lw          $t2, 0xC($v1)
    ctx->r10 = MEM_W(ctx->r3, 0XC);
    // 0x8007CA44: sw          $at, 0x8($s0)
    MEM_W(0X8, ctx->r16) = ctx->r1;
    // 0x8007CA48: slti        $at, $v0, 0x3
    ctx->r1 = SIGNED(ctx->r2) < 0X3 ? 1 : 0;
    // 0x8007CA4C: addiu       $s0, $s0, 0x10
    ctx->r16 = ADD32(ctx->r16, 0X10);
    // 0x8007CA50: addiu       $v1, $v1, 0x10
    ctx->r3 = ADD32(ctx->r3, 0X10);
    // 0x8007CA54: bne         $at, $zero, L_8007CA28
    if (ctx->r1 != 0) {
        // 0x8007CA58: sw          $t2, -0x4($s0)
        MEM_W(-0X4, ctx->r16) = ctx->r10;
            goto L_8007CA28;
    }
    // 0x8007CA58: sw          $t2, -0x4($s0)
    MEM_W(-0X4, ctx->r16) = ctx->r10;
    // 0x8007CA5C: sll         $t3, $a2, 4
    ctx->r11 = S32(ctx->r6 << 4);
    // 0x8007CA60: subu        $t3, $t3, $a2
    ctx->r11 = SUB32(ctx->r11, ctx->r6);
    // 0x8007CA64: lui         $t5, 0x801B
    ctx->r13 = S32(0X801B << 16);
    // 0x8007CA68: addiu       $t5, $t5, -0x15E8
    ctx->r13 = ADD32(ctx->r13, -0X15E8);
    // 0x8007CA6C: addiu       $t4, $t3, 0x120
    ctx->r12 = ADD32(ctx->r11, 0X120);
    // 0x8007CA70: addu        $s2, $t4, $t5
    ctx->r18 = ADD32(ctx->r12, ctx->r13);
    // 0x8007CA74: or          $s0, $a1, $zero
    ctx->r16 = ctx->r5 | 0;
    // 0x8007CA78: or          $s1, $zero, $zero
    ctx->r17 = 0 | 0;
    // 0x8007CA7C: sw          $a2, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r6;
    // 0x8007CA80: addiu       $s3, $zero, 0xF
    ctx->r19 = ADD32(0, 0XF);
L_8007CA84:
    // 0x8007CA84: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x8007CA88: jal         0x8007B1AC
    // 0x8007CA8C: or          $a1, $s2, $zero
    ctx->r5 = ctx->r18 | 0;
    func_8007B1AC(rdram, ctx);
        goto after_0;
    // 0x8007CA8C: or          $a1, $s2, $zero
    ctx->r5 = ctx->r18 | 0;
    after_0:
    // 0x8007CA90: addiu       $s1, $s1, 0x5
    ctx->r17 = ADD32(ctx->r17, 0X5);
    // 0x8007CA94: addiu       $s0, $s0, 0x10
    ctx->r16 = ADD32(ctx->r16, 0X10);
    // 0x8007CA98: bne         $s1, $s3, L_8007CA84
    if (ctx->r17 != ctx->r19) {
        // 0x8007CA9C: addiu       $s2, $s2, 0x5
        ctx->r18 = ADD32(ctx->r18, 0X5);
            goto L_8007CA84;
    }
    // 0x8007CA9C: addiu       $s2, $s2, 0x5
    ctx->r18 = ADD32(ctx->r18, 0X5);
    // 0x8007CAA0: jal         0x8007B31C
    // 0x8007CAA4: nop

    func_8007B31C(rdram, ctx);
        goto after_1;
    // 0x8007CAA4: nop

    after_1:
    // 0x8007CAA8: lui         $s0, 0x801B
    ctx->r16 = S32(0X801B << 16);
    // 0x8007CAAC: addiu       $s0, $s0, -0x15E8
    ctx->r16 = ADD32(ctx->r16, -0X15E8);
    // 0x8007CAB0: jal         0x8007BBF8
    // 0x8007CAB4: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    Save_GenCheckSum(rdram, ctx);
        goto after_2;
    // 0x8007CAB4: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_2:
    // 0x8007CAB8: sh          $v0, 0x2($s0)
    MEM_H(0X2, ctx->r16) = ctx->r2;
    // 0x8007CABC: lui         $t6, 0x800E
    ctx->r14 = S32(0X800E << 16);
    // 0x8007CAC0: lw          $t6, -0x7DA0($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X7DA0);
    // 0x8007CAC4: lui         $s1, 0x8015
    ctx->r17 = S32(0X8015 << 16);
    // 0x8007CAC8: addiu       $s1, $s1, 0x40D0
    ctx->r17 = ADD32(ctx->r17, 0X40D0);
    // 0x8007CACC: bne         $t6, $zero, L_8007CADC
    if (ctx->r14 != 0) {
        // 0x8007CAD0: or          $a0, $s1, $zero
        ctx->r4 = ctx->r17 | 0;
            goto L_8007CADC;
    }
    // 0x8007CAD0: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    // 0x8007CAD4: b           L_8007CB4C
    // 0x8007CAD8: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
        goto L_8007CB4C;
    // 0x8007CAD8: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
L_8007CADC:
    // 0x8007CADC: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x8007CAE0: or          $a2, $s0, $zero
    ctx->r6 = ctx->r16 | 0;
    // 0x8007CAE4: jal         0x800C8410
    // 0x8007CAE8: addiu       $a3, $zero, 0x10
    ctx->r7 = ADD32(0, 0X10);
    osEepromLongWrite_recomp(rdram, ctx);
        goto after_3;
    // 0x8007CAE8: addiu       $a3, $zero, 0x10
    ctx->r7 = ADD32(0, 0X10);
    after_3:
    // 0x8007CAEC: beq         $v0, $zero, L_8007CAFC
    if (ctx->r2 == 0) {
        // 0x8007CAF0: lw          $t7, 0x28($sp)
        ctx->r15 = MEM_W(ctx->r29, 0X28);
            goto L_8007CAFC;
    }
    // 0x8007CAF0: lw          $t7, 0x28($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X28);
    // 0x8007CAF4: b           L_8007CB4C
    // 0x8007CAF8: addiu       $v0, $zero, 0x3
    ctx->r2 = ADD32(0, 0X3);
        goto L_8007CB4C;
    // 0x8007CAF8: addiu       $v0, $zero, 0x3
    ctx->r2 = ADD32(0, 0X3);
L_8007CAFC:
    // 0x8007CAFC: sll         $t8, $t7, 2
    ctx->r24 = S32(ctx->r15 << 2);
    // 0x8007CB00: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x8007CB04: addu        $v0, $v0, $t8
    ctx->r2 = ADD32(ctx->r2, ctx->r24);
    // 0x8007CB08: lw          $v0, -0x7D94($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X7D94);
    // 0x8007CB0C: lui         $t9, 0x801B
    ctx->r25 = S32(0X801B << 16);
    // 0x8007CB10: addiu       $t9, $t9, -0x14C8
    ctx->r25 = ADD32(ctx->r25, -0X14C8);
    // 0x8007CB14: subu        $t1, $t9, $s0
    ctx->r9 = SUB32(ctx->r25, ctx->r16);
    // 0x8007CB18: addu        $a1, $t1, $v0
    ctx->r5 = ADD32(ctx->r9, ctx->r2);
    // 0x8007CB1C: srl         $t0, $a1, 3
    ctx->r8 = S32(U32(ctx->r5) >> 3);
    // 0x8007CB20: addu        $a2, $s0, $v0
    ctx->r6 = ADD32(ctx->r16, ctx->r2);
    // 0x8007CB24: addiu       $a2, $a2, 0x120
    ctx->r6 = ADD32(ctx->r6, 0X120);
    // 0x8007CB28: andi        $a1, $t0, 0xFF
    ctx->r5 = ctx->r8 & 0XFF;
    // 0x8007CB2C: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    // 0x8007CB30: jal         0x800C8410
    // 0x8007CB34: addiu       $a3, $zero, 0x18
    ctx->r7 = ADD32(0, 0X18);
    osEepromLongWrite_recomp(rdram, ctx);
        goto after_4;
    // 0x8007CB34: addiu       $a3, $zero, 0x18
    ctx->r7 = ADD32(0, 0X18);
    after_4:
    // 0x8007CB38: beql        $v0, $zero, L_8007CB4C
    if (ctx->r2 == 0) {
        // 0x8007CB3C: or          $v0, $zero, $zero
        ctx->r2 = 0 | 0;
            goto L_8007CB4C;
    }
    goto skip_0;
    // 0x8007CB3C: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    skip_0:
    // 0x8007CB40: b           L_8007CB4C
    // 0x8007CB44: addiu       $v0, $zero, 0x3
    ctx->r2 = ADD32(0, 0X3);
        goto L_8007CB4C;
    // 0x8007CB44: addiu       $v0, $zero, 0x3
    ctx->r2 = ADD32(0, 0X3);
    // 0x8007CB48: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_8007CB4C:
    // 0x8007CB4C: lw          $ra, 0x24($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X24);
    // 0x8007CB50: lw          $s0, 0x14($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X14);
    // 0x8007CB54: lw          $s1, 0x18($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X18);
    // 0x8007CB58: lw          $s2, 0x1C($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X1C);
    // 0x8007CB5C: lw          $s3, 0x20($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X20);
    // 0x8007CB60: jr          $ra
    // 0x8007CB64: addiu       $sp, $sp, 0x28
    ctx->r29 = ADD32(ctx->r29, 0X28);
    return;
    // 0x8007CB64: addiu       $sp, $sp, 0x28
    ctx->r29 = ADD32(ctx->r29, 0X28);
;}
RECOMP_FUNC void func_8007CB68(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8007CB68: addiu       $sp, $sp, -0x170
    ctx->r29 = ADD32(ctx->r29, -0X170);
    // 0x8007CB6C: sw          $s7, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r23;
    // 0x8007CB70: sw          $s6, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r22;
    // 0x8007CB74: lui         $v0, 0x801B
    ctx->r2 = S32(0X801B << 16);
    // 0x8007CB78: lui         $v1, 0x801B
    ctx->r3 = S32(0X801B << 16);
    // 0x8007CB7C: sw          $fp, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r30;
    // 0x8007CB80: sw          $s3, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r19;
    // 0x8007CB84: addiu       $v1, $v1, -0x13E8
    ctx->r3 = ADD32(ctx->r3, -0X13E8);
    // 0x8007CB88: addiu       $v0, $v0, -0x15E8
    ctx->r2 = ADD32(ctx->r2, -0X15E8);
    // 0x8007CB8C: lui         $s6, 0x9
    ctx->r22 = S32(0X9 << 16);
    // 0x8007CB90: addiu       $s7, $sp, 0x118
    ctx->r23 = ADD32(ctx->r29, 0X118);
    // 0x8007CB94: sw          $ra, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r31;
    // 0x8007CB98: sw          $s5, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r21;
    // 0x8007CB9C: sw          $s4, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r20;
    // 0x8007CBA0: sw          $s2, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r18;
    // 0x8007CBA4: sw          $s1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r17;
    // 0x8007CBA8: sw          $s0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r16;
    // 0x8007CBAC: or          $fp, $s7, $zero
    ctx->r30 = ctx->r23 | 0;
    // 0x8007CBB0: ori         $s6, $s6, 0x27BF
    ctx->r22 = ctx->r22 | 0X27BF;
    // 0x8007CBB4: sw          $v0, 0x54($sp)
    MEM_W(0X54, ctx->r29) = ctx->r2;
    // 0x8007CBB8: sw          $v1, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r3;
    // 0x8007CBBC: addiu       $s3, $sp, 0xC8
    ctx->r19 = ADD32(ctx->r29, 0XC8);
    // 0x8007CBC0: sw          $zero, 0x16C($sp)
    MEM_W(0X16C, ctx->r29) = 0;
L_8007CBC4:
    // 0x8007CBC4: lw          $v0, 0x54($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X54);
    // 0x8007CBC8: lw          $v1, 0x48($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X48);
    // 0x8007CBCC: addiu       $s1, $sp, 0x118
    ctx->r17 = ADD32(ctx->r29, 0X118);
    // 0x8007CBD0: addiu       $s2, $sp, 0xDC
    ctx->r18 = ADD32(ctx->r29, 0XDC);
    // 0x8007CBD4: or          $s5, $zero, $zero
    ctx->r21 = 0 | 0;
    // 0x8007CBD8: addiu       $s0, $v0, 0x60
    ctx->r16 = ADD32(ctx->r2, 0X60);
    // 0x8007CBDC: addiu       $s4, $v1, 0x60
    ctx->r20 = ADD32(ctx->r3, 0X60);
L_8007CBE0:
    // 0x8007CBE0: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x8007CBE4: jal         0x8007AFF4
    // 0x8007CBE8: or          $a1, $s1, $zero
    ctx->r5 = ctx->r17 | 0;
    func_8007AFF4(rdram, ctx);
        goto after_0;
    // 0x8007CBE8: or          $a1, $s1, $zero
    ctx->r5 = ctx->r17 | 0;
    after_0:
    // 0x8007CBEC: or          $a0, $s4, $zero
    ctx->r4 = ctx->r20 | 0;
    // 0x8007CBF0: jal         0x8007AFF4
    // 0x8007CBF4: or          $a1, $s2, $zero
    ctx->r5 = ctx->r18 | 0;
    func_8007AFF4(rdram, ctx);
        goto after_1;
    // 0x8007CBF4: or          $a1, $s2, $zero
    ctx->r5 = ctx->r18 | 0;
    after_1:
    // 0x8007CBF8: addiu       $s2, $s2, 0x14
    ctx->r18 = ADD32(ctx->r18, 0X14);
    // 0x8007CBFC: addiu       $t7, $sp, 0x118
    ctx->r15 = ADD32(ctx->r29, 0X118);
    // 0x8007CC00: sltu        $at, $s2, $t7
    ctx->r1 = ctx->r18 < ctx->r15 ? 1 : 0;
    // 0x8007CC04: addiu       $s0, $s0, 0x6
    ctx->r16 = ADD32(ctx->r16, 0X6);
    // 0x8007CC08: addiu       $s1, $s1, 0x14
    ctx->r17 = ADD32(ctx->r17, 0X14);
    // 0x8007CC0C: bne         $at, $zero, L_8007CBE0
    if (ctx->r1 != 0) {
        // 0x8007CC10: addiu       $s4, $s4, 0x6
        ctx->r20 = ADD32(ctx->r20, 0X6);
            goto L_8007CBE0;
    }
    // 0x8007CC10: addiu       $s4, $s4, 0x6
    ctx->r20 = ADD32(ctx->r20, 0X6);
    // 0x8007CC14: addiu       $s1, $sp, 0x118
    ctx->r17 = ADD32(ctx->r29, 0X118);
    // 0x8007CC18: addiu       $s0, $sp, 0xDC
    ctx->r16 = ADD32(ctx->r29, 0XDC);
L_8007CC1C:
    // 0x8007CC1C: lw          $t8, 0x0($s1)
    ctx->r24 = MEM_W(ctx->r17, 0X0);
L_8007CC20:
    // 0x8007CC20: lw          $t9, 0x0($s0)
    ctx->r25 = MEM_W(ctx->r16, 0X0);
    // 0x8007CC24: bnel        $t8, $t9, L_8007CC6C
    if (ctx->r24 != ctx->r25) {
        // 0x8007CC28: addiu       $s0, $s0, 0x14
        ctx->r16 = ADD32(ctx->r16, 0X14);
            goto L_8007CC6C;
    }
    goto skip_0;
    // 0x8007CC28: addiu       $s0, $s0, 0x14
    ctx->r16 = ADD32(ctx->r16, 0X14);
    skip_0:
    // 0x8007CC2C: lw          $t2, 0x4($s1)
    ctx->r10 = MEM_W(ctx->r17, 0X4);
    // 0x8007CC30: lw          $t3, 0x4($s0)
    ctx->r11 = MEM_W(ctx->r16, 0X4);
    // 0x8007CC34: bnel        $t2, $t3, L_8007CC6C
    if (ctx->r10 != ctx->r11) {
        // 0x8007CC38: addiu       $s0, $s0, 0x14
        ctx->r16 = ADD32(ctx->r16, 0X14);
            goto L_8007CC6C;
    }
    goto skip_1;
    // 0x8007CC38: addiu       $s0, $s0, 0x14
    ctx->r16 = ADD32(ctx->r16, 0X14);
    skip_1:
    // 0x8007CC3C: lw          $t4, 0x8($s1)
    ctx->r12 = MEM_W(ctx->r17, 0X8);
    // 0x8007CC40: lw          $t5, 0x8($s0)
    ctx->r13 = MEM_W(ctx->r16, 0X8);
    // 0x8007CC44: addiu       $a0, $s1, 0x10
    ctx->r4 = ADD32(ctx->r17, 0X10);
    // 0x8007CC48: addiu       $a1, $s0, 0x10
    ctx->r5 = ADD32(ctx->r16, 0X10);
    // 0x8007CC4C: bnel        $t4, $t5, L_8007CC6C
    if (ctx->r12 != ctx->r13) {
        // 0x8007CC50: addiu       $s0, $s0, 0x14
        ctx->r16 = ADD32(ctx->r16, 0X14);
            goto L_8007CC6C;
    }
    goto skip_2;
    // 0x8007CC50: addiu       $s0, $s0, 0x14
    ctx->r16 = ADD32(ctx->r16, 0X14);
    skip_2:
    // 0x8007CC54: jal         0x8006A1CC
    // 0x8007CC58: addiu       $a2, $zero, 0x3
    ctx->r6 = ADD32(0, 0X3);
    Libc_strncmp(rdram, ctx);
        goto after_2;
    // 0x8007CC58: addiu       $a2, $zero, 0x3
    ctx->r6 = ADD32(0, 0X3);
    after_2:
    // 0x8007CC5C: bnel        $v0, $zero, L_8007CC6C
    if (ctx->r2 != 0) {
        // 0x8007CC60: addiu       $s0, $s0, 0x14
        ctx->r16 = ADD32(ctx->r16, 0X14);
            goto L_8007CC6C;
    }
    goto skip_3;
    // 0x8007CC60: addiu       $s0, $s0, 0x14
    ctx->r16 = ADD32(ctx->r16, 0X14);
    skip_3:
    // 0x8007CC64: sw          $s6, 0x0($s0)
    MEM_W(0X0, ctx->r16) = ctx->r22;
    // 0x8007CC68: addiu       $s0, $s0, 0x14
    ctx->r16 = ADD32(ctx->r16, 0X14);
L_8007CC6C:
    // 0x8007CC6C: bnel        $s0, $s7, L_8007CC20
    if (ctx->r16 != ctx->r23) {
        // 0x8007CC70: lw          $t8, 0x0($s1)
        ctx->r24 = MEM_W(ctx->r17, 0X0);
            goto L_8007CC20;
    }
    goto skip_4;
    // 0x8007CC70: lw          $t8, 0x0($s1)
    ctx->r24 = MEM_W(ctx->r17, 0X0);
    skip_4:
    // 0x8007CC74: addiu       $s1, $s1, 0x14
    ctx->r17 = ADD32(ctx->r17, 0X14);
    // 0x8007CC78: addiu       $t6, $sp, 0x154
    ctx->r14 = ADD32(ctx->r29, 0X154);
    // 0x8007CC7C: sltu        $at, $s1, $t6
    ctx->r1 = ctx->r17 < ctx->r14 ? 1 : 0;
    // 0x8007CC80: bnel        $at, $zero, L_8007CC1C
    if (ctx->r1 != 0) {
        // 0x8007CC84: addiu       $s0, $sp, 0xDC
        ctx->r16 = ADD32(ctx->r29, 0XDC);
            goto L_8007CC1C;
    }
    goto skip_5;
    // 0x8007CC84: addiu       $s0, $sp, 0xDC
    ctx->r16 = ADD32(ctx->r29, 0XDC);
    skip_5:
    // 0x8007CC88: addiu       $s1, $sp, 0x118
    ctx->r17 = ADD32(ctx->r29, 0X118);
    // 0x8007CC8C: addiu       $v1, $sp, 0x154
    ctx->r3 = ADD32(ctx->r29, 0X154);
    // 0x8007CC90: addiu       $v0, $sp, 0x118
    ctx->r2 = ADD32(ctx->r29, 0X118);
    // 0x8007CC94: addiu       $s0, $sp, 0xDC
    ctx->r16 = ADD32(ctx->r29, 0XDC);
L_8007CC98:
    // 0x8007CC98: lw          $t7, 0x0($s0)
    ctx->r15 = MEM_W(ctx->r16, 0X0);
L_8007CC9C:
    // 0x8007CC9C: lw          $t8, 0x0($s1)
    ctx->r24 = MEM_W(ctx->r17, 0X0);
    // 0x8007CCA0: slt         $at, $t7, $t8
    ctx->r1 = SIGNED(ctx->r15) < SIGNED(ctx->r24) ? 1 : 0;
    // 0x8007CCA4: beql        $at, $zero, L_8007CD2C
    if (ctx->r1 == 0) {
        // 0x8007CCA8: addiu       $s0, $s0, 0x14
        ctx->r16 = ADD32(ctx->r16, 0X14);
            goto L_8007CD2C;
    }
    goto skip_6;
    // 0x8007CCA8: addiu       $s0, $s0, 0x14
    ctx->r16 = ADD32(ctx->r16, 0X14);
    skip_6:
    // 0x8007CCAC: lw          $at, 0x0($s1)
    ctx->r1 = MEM_W(ctx->r17, 0X0);
    // 0x8007CCB0: lw          $t2, 0x4($s1)
    ctx->r10 = MEM_W(ctx->r17, 0X4);
    // 0x8007CCB4: lw          $t4, 0x4($s0)
    ctx->r12 = MEM_W(ctx->r16, 0X4);
    // 0x8007CCB8: sw          $at, 0x0($s3)
    MEM_W(0X0, ctx->r19) = ctx->r1;
    // 0x8007CCBC: lw          $at, 0x8($s1)
    ctx->r1 = MEM_W(ctx->r17, 0X8);
    // 0x8007CCC0: sw          $t2, 0x4($s3)
    MEM_W(0X4, ctx->r19) = ctx->r10;
    // 0x8007CCC4: lw          $t2, 0xC($s1)
    ctx->r10 = MEM_W(ctx->r17, 0XC);
    // 0x8007CCC8: sw          $at, 0x8($s3)
    MEM_W(0X8, ctx->r19) = ctx->r1;
    // 0x8007CCCC: lw          $at, 0x10($s1)
    ctx->r1 = MEM_W(ctx->r17, 0X10);
    // 0x8007CCD0: sw          $t4, 0x4($s1)
    MEM_W(0X4, ctx->r17) = ctx->r12;
    // 0x8007CCD4: lw          $t4, 0xC($s0)
    ctx->r12 = MEM_W(ctx->r16, 0XC);
    // 0x8007CCD8: sw          $at, 0x10($s3)
    MEM_W(0X10, ctx->r19) = ctx->r1;
    // 0x8007CCDC: lw          $at, 0x0($s0)
    ctx->r1 = MEM_W(ctx->r16, 0X0);
    // 0x8007CCE0: lw          $t6, 0x4($s3)
    ctx->r14 = MEM_W(ctx->r19, 0X4);
    // 0x8007CCE4: sw          $t2, 0xC($s3)
    MEM_W(0XC, ctx->r19) = ctx->r10;
    // 0x8007CCE8: sw          $at, 0x0($s1)
    MEM_W(0X0, ctx->r17) = ctx->r1;
    // 0x8007CCEC: lw          $at, 0x8($s0)
    ctx->r1 = MEM_W(ctx->r16, 0X8);
    // 0x8007CCF0: sw          $t2, 0xC($s0)
    MEM_W(0XC, ctx->r16) = ctx->r10;
    // 0x8007CCF4: sw          $t4, 0xC($s1)
    MEM_W(0XC, ctx->r17) = ctx->r12;
    // 0x8007CCF8: sw          $at, 0x8($s1)
    MEM_W(0X8, ctx->r17) = ctx->r1;
    // 0x8007CCFC: lw          $at, 0x10($s0)
    ctx->r1 = MEM_W(ctx->r16, 0X10);
    // 0x8007CD00: sw          $t6, 0x4($s0)
    MEM_W(0X4, ctx->r16) = ctx->r14;
    // 0x8007CD04: sw          $at, 0x10($s1)
    MEM_W(0X10, ctx->r17) = ctx->r1;
    // 0x8007CD08: lw          $at, 0x0($s3)
    ctx->r1 = MEM_W(ctx->r19, 0X0);
    // 0x8007CD0C: sw          $at, 0x0($s0)
    MEM_W(0X0, ctx->r16) = ctx->r1;
    // 0x8007CD10: lw          $at, 0x8($s3)
    ctx->r1 = MEM_W(ctx->r19, 0X8);
    // 0x8007CD14: sw          $at, 0x8($s0)
    MEM_W(0X8, ctx->r16) = ctx->r1;
    // 0x8007CD18: lw          $at, 0x10($s3)
    ctx->r1 = MEM_W(ctx->r19, 0X10);
    // 0x8007CD1C: bne         $s1, $fp, L_8007CD28
    if (ctx->r17 != ctx->r30) {
        // 0x8007CD20: sw          $at, 0x10($s0)
        MEM_W(0X10, ctx->r16) = ctx->r1;
            goto L_8007CD28;
    }
    // 0x8007CD20: sw          $at, 0x10($s0)
    MEM_W(0X10, ctx->r16) = ctx->r1;
    // 0x8007CD24: addiu       $s5, $zero, 0x1
    ctx->r21 = ADD32(0, 0X1);
L_8007CD28:
    // 0x8007CD28: addiu       $s0, $s0, 0x14
    ctx->r16 = ADD32(ctx->r16, 0X14);
L_8007CD2C:
    // 0x8007CD2C: bnel        $s0, $v0, L_8007CC9C
    if (ctx->r16 != ctx->r2) {
        // 0x8007CD30: lw          $t7, 0x0($s0)
        ctx->r15 = MEM_W(ctx->r16, 0X0);
            goto L_8007CC9C;
    }
    goto skip_7;
    // 0x8007CD30: lw          $t7, 0x0($s0)
    ctx->r15 = MEM_W(ctx->r16, 0X0);
    skip_7:
    // 0x8007CD34: addiu       $s1, $s1, 0x14
    ctx->r17 = ADD32(ctx->r17, 0X14);
    // 0x8007CD38: sltu        $at, $s1, $v1
    ctx->r1 = ctx->r17 < ctx->r3 ? 1 : 0;
    // 0x8007CD3C: bnel        $at, $zero, L_8007CC98
    if (ctx->r1 != 0) {
        // 0x8007CD40: addiu       $s0, $sp, 0xDC
        ctx->r16 = ADD32(ctx->r29, 0XDC);
            goto L_8007CC98;
    }
    goto skip_8;
    // 0x8007CD40: addiu       $s0, $sp, 0xDC
    ctx->r16 = ADD32(ctx->r29, 0XDC);
    skip_8:
    // 0x8007CD44: lw          $s0, 0x54($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X54);
    // 0x8007CD48: addiu       $s1, $sp, 0x118
    ctx->r17 = ADD32(ctx->r29, 0X118);
    // 0x8007CD4C: addiu       $s2, $sp, 0x154
    ctx->r18 = ADD32(ctx->r29, 0X154);
    // 0x8007CD50: addiu       $s0, $s0, 0x60
    ctx->r16 = ADD32(ctx->r16, 0X60);
L_8007CD54:
    // 0x8007CD54: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    // 0x8007CD58: jal         0x8007AF78
    // 0x8007CD5C: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    func_8007AF78(rdram, ctx);
        goto after_3;
    // 0x8007CD5C: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    after_3:
    // 0x8007CD60: addiu       $s1, $s1, 0x14
    ctx->r17 = ADD32(ctx->r17, 0X14);
    // 0x8007CD64: sltu        $at, $s1, $s2
    ctx->r1 = ctx->r17 < ctx->r18 ? 1 : 0;
    // 0x8007CD68: bne         $at, $zero, L_8007CD54
    if (ctx->r1 != 0) {
        // 0x8007CD6C: addiu       $s0, $s0, 0x6
        ctx->r16 = ADD32(ctx->r16, 0X6);
            goto L_8007CD54;
    }
    // 0x8007CD6C: addiu       $s0, $s0, 0x6
    ctx->r16 = ADD32(ctx->r16, 0X6);
    // 0x8007CD70: beq         $s5, $zero, L_8007CDDC
    if (ctx->r21 == 0) {
        // 0x8007CD74: or          $a3, $zero, $zero
        ctx->r7 = 0 | 0;
            goto L_8007CDDC;
    }
    // 0x8007CD74: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    // 0x8007CD78: lw          $t7, 0x16C($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X16C);
    // 0x8007CD7C: lui         $t9, 0x801B
    ctx->r25 = S32(0X801B << 16);
    // 0x8007CD80: lui         $t2, 0x801B
    ctx->r10 = S32(0X801B << 16);
    // 0x8007CD84: sll         $t8, $t7, 2
    ctx->r24 = S32(ctx->r15 << 2);
    // 0x8007CD88: subu        $t8, $t8, $t7
    ctx->r24 = SUB32(ctx->r24, ctx->r15);
    // 0x8007CD8C: sll         $t8, $t8, 1
    ctx->r24 = S32(ctx->r24 << 1);
    // 0x8007CD90: addiu       $t2, $t2, -0x13E8
    ctx->r10 = ADD32(ctx->r10, -0X13E8);
    // 0x8007CD94: addiu       $t9, $t9, -0x15E8
    ctx->r25 = ADD32(ctx->r25, -0X15E8);
    // 0x8007CD98: addu        $a1, $t8, $t9
    ctx->r5 = ADD32(ctx->r24, ctx->r25);
    // 0x8007CD9C: addu        $a2, $t8, $t2
    ctx->r6 = ADD32(ctx->r24, ctx->r10);
    // 0x8007CDA0: addiu       $t1, $zero, 0x2
    ctx->r9 = ADD32(0, 0X2);
    // 0x8007CDA4: addiu       $t0, $zero, 0x3
    ctx->r8 = ADD32(0, 0X3);
L_8007CDA8:
    // 0x8007CDA8: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    // 0x8007CDAC: or          $v0, $a1, $zero
    ctx->r2 = ctx->r5 | 0;
    // 0x8007CDB0: or          $v1, $a2, $zero
    ctx->r3 = ctx->r6 | 0;
L_8007CDB4:
    // 0x8007CDB4: lbu         $t3, 0x1A8($v1)
    ctx->r11 = MEM_BU(ctx->r3, 0X1A8);
    // 0x8007CDB8: addiu       $a0, $a0, 0x1
    ctx->r4 = ADD32(ctx->r4, 0X1);
    // 0x8007CDBC: addiu       $v0, $v0, 0x1
    ctx->r2 = ADD32(ctx->r2, 0X1);
    // 0x8007CDC0: addiu       $v1, $v1, 0x1
    ctx->r3 = ADD32(ctx->r3, 0X1);
    // 0x8007CDC4: bne         $a0, $t0, L_8007CDB4
    if (ctx->r4 != ctx->r8) {
        // 0x8007CDC8: sb          $t3, 0x1A7($v0)
        MEM_B(0X1A7, ctx->r2) = ctx->r11;
            goto L_8007CDB4;
    }
    // 0x8007CDC8: sb          $t3, 0x1A7($v0)
    MEM_B(0X1A7, ctx->r2) = ctx->r11;
    // 0x8007CDCC: addiu       $a3, $a3, 0x1
    ctx->r7 = ADD32(ctx->r7, 0X1);
    // 0x8007CDD0: addiu       $a1, $a1, 0x3
    ctx->r5 = ADD32(ctx->r5, 0X3);
    // 0x8007CDD4: bne         $a3, $t1, L_8007CDA8
    if (ctx->r7 != ctx->r9) {
        // 0x8007CDD8: addiu       $a2, $a2, 0x3
        ctx->r6 = ADD32(ctx->r6, 0X3);
            goto L_8007CDA8;
    }
    // 0x8007CDD8: addiu       $a2, $a2, 0x3
    ctx->r6 = ADD32(ctx->r6, 0X3);
L_8007CDDC:
    // 0x8007CDDC: lw          $t4, 0x16C($sp)
    ctx->r12 = MEM_W(ctx->r29, 0X16C);
    // 0x8007CDE0: lw          $t6, 0x54($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X54);
    // 0x8007CDE4: lw          $t9, 0x48($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X48);
    // 0x8007CDE8: addiu       $t5, $t4, 0x1
    ctx->r13 = ADD32(ctx->r12, 0X1);
    // 0x8007CDEC: slti        $at, $t5, 0x8
    ctx->r1 = SIGNED(ctx->r13) < 0X8 ? 1 : 0;
    // 0x8007CDF0: addiu       $t7, $t6, 0x18
    ctx->r15 = ADD32(ctx->r14, 0X18);
    // 0x8007CDF4: addiu       $t8, $t9, 0x18
    ctx->r24 = ADD32(ctx->r25, 0X18);
    // 0x8007CDF8: sw          $t8, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r24;
    // 0x8007CDFC: sw          $t7, 0x54($sp)
    MEM_W(0X54, ctx->r29) = ctx->r15;
    // 0x8007CE00: bne         $at, $zero, L_8007CBC4
    if (ctx->r1 != 0) {
        // 0x8007CE04: sw          $t5, 0x16C($sp)
        MEM_W(0X16C, ctx->r29) = ctx->r13;
            goto L_8007CBC4;
    }
    // 0x8007CE04: sw          $t5, 0x16C($sp)
    MEM_W(0X16C, ctx->r29) = ctx->r13;
    // 0x8007CE08: lui         $s0, 0x801B
    ctx->r16 = S32(0X801B << 16);
    // 0x8007CE0C: lui         $s1, 0x801B
    ctx->r17 = S32(0X801B << 16);
    // 0x8007CE10: lui         $s4, 0x801B
    ctx->r20 = S32(0X801B << 16);
    // 0x8007CE14: addiu       $s4, $s4, -0x12B6
    ctx->r20 = ADD32(ctx->r20, -0X12B6);
    // 0x8007CE18: addiu       $s1, $s1, -0x1376
    ctx->r17 = ADD32(ctx->r17, -0X1376);
    // 0x8007CE1C: addiu       $s0, $s0, -0x1576
    ctx->r16 = ADD32(ctx->r16, -0X1576);
    // 0x8007CE20: sw          $zero, 0x16C($sp)
    MEM_W(0X16C, ctx->r29) = 0;
    // 0x8007CE24: addiu       $s3, $sp, 0xDC
    ctx->r19 = ADD32(ctx->r29, 0XDC);
    // 0x8007CE28: addiu       $s2, $sp, 0x118
    ctx->r18 = ADD32(ctx->r29, 0X118);
L_8007CE2C:
    // 0x8007CE2C: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x8007CE30: jal         0x8007AFF4
    // 0x8007CE34: or          $a1, $s2, $zero
    ctx->r5 = ctx->r18 | 0;
    func_8007AFF4(rdram, ctx);
        goto after_4;
    // 0x8007CE34: or          $a1, $s2, $zero
    ctx->r5 = ctx->r18 | 0;
    after_4:
    // 0x8007CE38: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    // 0x8007CE3C: jal         0x8007AFF4
    // 0x8007CE40: or          $a1, $s3, $zero
    ctx->r5 = ctx->r19 | 0;
    func_8007AFF4(rdram, ctx);
        goto after_5;
    // 0x8007CE40: or          $a1, $s3, $zero
    ctx->r5 = ctx->r19 | 0;
    after_5:
    // 0x8007CE44: lw          $t2, 0xDC($sp)
    ctx->r10 = MEM_W(ctx->r29, 0XDC);
    // 0x8007CE48: lw          $t3, 0x118($sp)
    ctx->r11 = MEM_W(ctx->r29, 0X118);
    // 0x8007CE4C: or          $a0, $s2, $zero
    ctx->r4 = ctx->r18 | 0;
    // 0x8007CE50: slt         $at, $t2, $t3
    ctx->r1 = SIGNED(ctx->r10) < SIGNED(ctx->r11) ? 1 : 0;
    // 0x8007CE54: beq         $at, $zero, L_8007CE84
    if (ctx->r1 == 0) {
        // 0x8007CE58: nop
    
            goto L_8007CE84;
    }
    // 0x8007CE58: nop

    // 0x8007CE5C: lw          $at, 0x0($s3)
    ctx->r1 = MEM_W(ctx->r19, 0X0);
    // 0x8007CE60: lw          $t6, 0x4($s3)
    ctx->r14 = MEM_W(ctx->r19, 0X4);
    // 0x8007CE64: sw          $at, 0x0($s2)
    MEM_W(0X0, ctx->r18) = ctx->r1;
    // 0x8007CE68: lw          $at, 0x8($s3)
    ctx->r1 = MEM_W(ctx->r19, 0X8);
    // 0x8007CE6C: sw          $t6, 0x4($s2)
    MEM_W(0X4, ctx->r18) = ctx->r14;
    // 0x8007CE70: lw          $t6, 0xC($s3)
    ctx->r14 = MEM_W(ctx->r19, 0XC);
    // 0x8007CE74: sw          $at, 0x8($s2)
    MEM_W(0X8, ctx->r18) = ctx->r1;
    // 0x8007CE78: lw          $at, 0x10($s3)
    ctx->r1 = MEM_W(ctx->r19, 0X10);
    // 0x8007CE7C: sw          $t6, 0xC($s2)
    MEM_W(0XC, ctx->r18) = ctx->r14;
    // 0x8007CE80: sw          $at, 0x10($s2)
    MEM_W(0X10, ctx->r18) = ctx->r1;
L_8007CE84:
    // 0x8007CE84: jal         0x8007AF78
    // 0x8007CE88: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    func_8007AF78(rdram, ctx);
        goto after_6;
    // 0x8007CE88: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    after_6:
    // 0x8007CE8C: addiu       $s1, $s1, 0x18
    ctx->r17 = ADD32(ctx->r17, 0X18);
    // 0x8007CE90: sltu        $at, $s1, $s4
    ctx->r1 = ctx->r17 < ctx->r20 ? 1 : 0;
    // 0x8007CE94: bne         $at, $zero, L_8007CE2C
    if (ctx->r1 != 0) {
        // 0x8007CE98: addiu       $s0, $s0, 0x18
        ctx->r16 = ADD32(ctx->r16, 0X18);
            goto L_8007CE2C;
    }
    // 0x8007CE98: addiu       $s0, $s0, 0x18
    ctx->r16 = ADD32(ctx->r16, 0X18);
    // 0x8007CE9C: lui         $s0, 0x801B
    ctx->r16 = S32(0X801B << 16);
    // 0x8007CEA0: lui         $s1, 0x801B
    ctx->r17 = S32(0X801B << 16);
    // 0x8007CEA4: lui         $s4, 0x801B
    ctx->r20 = S32(0X801B << 16);
    // 0x8007CEA8: addiu       $s4, $s4, -0x11E8
    ctx->r20 = ADD32(ctx->r20, -0X11E8);
    // 0x8007CEAC: addiu       $s1, $s1, -0x1210
    ctx->r17 = ADD32(ctx->r17, -0X1210);
    // 0x8007CEB0: addiu       $s0, $s0, -0x1410
    ctx->r16 = ADD32(ctx->r16, -0X1410);
    // 0x8007CEB4: sw          $zero, 0x16C($sp)
    MEM_W(0X16C, ctx->r29) = 0;
L_8007CEB8:
    // 0x8007CEB8: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x8007CEBC: jal         0x8007B110
    // 0x8007CEC0: or          $a1, $s2, $zero
    ctx->r5 = ctx->r18 | 0;
    func_8007B110(rdram, ctx);
        goto after_7;
    // 0x8007CEC0: or          $a1, $s2, $zero
    ctx->r5 = ctx->r18 | 0;
    after_7:
    // 0x8007CEC4: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    // 0x8007CEC8: jal         0x8007B110
    // 0x8007CECC: or          $a1, $s3, $zero
    ctx->r5 = ctx->r19 | 0;
    func_8007B110(rdram, ctx);
        goto after_8;
    // 0x8007CECC: or          $a1, $s3, $zero
    ctx->r5 = ctx->r19 | 0;
    after_8:
    // 0x8007CED0: lw          $t7, 0xDC($sp)
    ctx->r15 = MEM_W(ctx->r29, 0XDC);
    // 0x8007CED4: lw          $t9, 0x118($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X118);
    // 0x8007CED8: or          $a0, $s2, $zero
    ctx->r4 = ctx->r18 | 0;
    // 0x8007CEDC: slt         $at, $t7, $t9
    ctx->r1 = SIGNED(ctx->r15) < SIGNED(ctx->r25) ? 1 : 0;
    // 0x8007CEE0: beq         $at, $zero, L_8007CF10
    if (ctx->r1 == 0) {
        // 0x8007CEE4: nop
    
            goto L_8007CF10;
    }
    // 0x8007CEE4: nop

    // 0x8007CEE8: lw          $at, 0x0($s3)
    ctx->r1 = MEM_W(ctx->r19, 0X0);
    // 0x8007CEEC: lw          $t5, 0x4($s3)
    ctx->r13 = MEM_W(ctx->r19, 0X4);
    // 0x8007CEF0: sw          $at, 0x0($s2)
    MEM_W(0X0, ctx->r18) = ctx->r1;
    // 0x8007CEF4: lw          $at, 0x8($s3)
    ctx->r1 = MEM_W(ctx->r19, 0X8);
    // 0x8007CEF8: sw          $t5, 0x4($s2)
    MEM_W(0X4, ctx->r18) = ctx->r13;
    // 0x8007CEFC: lw          $t5, 0xC($s3)
    ctx->r13 = MEM_W(ctx->r19, 0XC);
    // 0x8007CF00: sw          $at, 0x8($s2)
    MEM_W(0X8, ctx->r18) = ctx->r1;
    // 0x8007CF04: lw          $at, 0x10($s3)
    ctx->r1 = MEM_W(ctx->r19, 0X10);
    // 0x8007CF08: sw          $t5, 0xC($s2)
    MEM_W(0XC, ctx->r18) = ctx->r13;
    // 0x8007CF0C: sw          $at, 0x10($s2)
    MEM_W(0X10, ctx->r18) = ctx->r1;
L_8007CF10:
    // 0x8007CF10: jal         0x8007B09C
    // 0x8007CF14: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    func_8007B09C(rdram, ctx);
        goto after_9;
    // 0x8007CF14: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    after_9:
    // 0x8007CF18: addiu       $s1, $s1, 0x5
    ctx->r17 = ADD32(ctx->r17, 0X5);
    // 0x8007CF1C: sltu        $at, $s1, $s4
    ctx->r1 = ctx->r17 < ctx->r20 ? 1 : 0;
    // 0x8007CF20: bne         $at, $zero, L_8007CEB8
    if (ctx->r1 != 0) {
        // 0x8007CF24: addiu       $s0, $s0, 0x5
        ctx->r16 = ADD32(ctx->r16, 0X5);
            goto L_8007CEB8;
    }
    // 0x8007CF24: addiu       $s0, $s0, 0x5
    ctx->r16 = ADD32(ctx->r16, 0X5);
    // 0x8007CF28: lui         $v0, 0x801B
    ctx->r2 = S32(0X801B << 16);
    // 0x8007CF2C: addiu       $s5, $sp, 0x98
    ctx->r21 = ADD32(ctx->r29, 0X98);
    // 0x8007CF30: addiu       $v0, $v0, -0x13E8
    ctx->r2 = ADD32(ctx->r2, -0X13E8);
    // 0x8007CF34: lui         $s7, 0x801B
    ctx->r23 = S32(0X801B << 16);
    // 0x8007CF38: addiu       $s7, $s7, -0x15E8
    ctx->r23 = ADD32(ctx->r23, -0X15E8);
    // 0x8007CF3C: sw          $v0, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r2;
    // 0x8007CF40: or          $fp, $s5, $zero
    ctx->r30 = ctx->r21 | 0;
    // 0x8007CF44: or          $s6, $s5, $zero
    ctx->r22 = ctx->r21 | 0;
    // 0x8007CF48: sw          $zero, 0x16C($sp)
    MEM_W(0X16C, ctx->r29) = 0;
    // 0x8007CF4C: addiu       $s2, $sp, 0x58
    ctx->r18 = ADD32(ctx->r29, 0X58);
L_8007CF50:
    // 0x8007CF50: lw          $v0, 0x48($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X48);
    // 0x8007CF54: addiu       $s0, $s7, 0x120
    ctx->r16 = ADD32(ctx->r23, 0X120);
    // 0x8007CF58: addiu       $s1, $sp, 0x98
    ctx->r17 = ADD32(ctx->r29, 0X98);
    // 0x8007CF5C: addiu       $s3, $sp, 0x68
    ctx->r19 = ADD32(ctx->r29, 0X68);
    // 0x8007CF60: addiu       $s4, $v0, 0x120
    ctx->r20 = ADD32(ctx->r2, 0X120);
L_8007CF64:
    // 0x8007CF64: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x8007CF68: jal         0x8007B220
    // 0x8007CF6C: or          $a1, $s1, $zero
    ctx->r5 = ctx->r17 | 0;
    func_8007B220(rdram, ctx);
        goto after_10;
    // 0x8007CF6C: or          $a1, $s1, $zero
    ctx->r5 = ctx->r17 | 0;
    after_10:
    // 0x8007CF70: or          $a0, $s4, $zero
    ctx->r4 = ctx->r20 | 0;
    // 0x8007CF74: jal         0x8007B220
    // 0x8007CF78: or          $a1, $s3, $zero
    ctx->r5 = ctx->r19 | 0;
    func_8007B220(rdram, ctx);
        goto after_11;
    // 0x8007CF78: or          $a1, $s3, $zero
    ctx->r5 = ctx->r19 | 0;
    after_11:
    // 0x8007CF7C: addiu       $s3, $s3, 0x10
    ctx->r19 = ADD32(ctx->r19, 0X10);
    // 0x8007CF80: sltu        $at, $s3, $fp
    ctx->r1 = ctx->r19 < ctx->r30 ? 1 : 0;
    // 0x8007CF84: addiu       $s0, $s0, 0x5
    ctx->r16 = ADD32(ctx->r16, 0X5);
    // 0x8007CF88: addiu       $s1, $s1, 0x10
    ctx->r17 = ADD32(ctx->r17, 0X10);
    // 0x8007CF8C: bne         $at, $zero, L_8007CF64
    if (ctx->r1 != 0) {
        // 0x8007CF90: addiu       $s4, $s4, 0x5
        ctx->r20 = ADD32(ctx->r20, 0X5);
            goto L_8007CF64;
    }
    // 0x8007CF90: addiu       $s4, $s4, 0x5
    ctx->r20 = ADD32(ctx->r20, 0X5);
    // 0x8007CF94: addiu       $s1, $sp, 0x98
    ctx->r17 = ADD32(ctx->r29, 0X98);
    // 0x8007CF98: addiu       $s0, $sp, 0x68
    ctx->r16 = ADD32(ctx->r29, 0X68);
L_8007CF9C:
    // 0x8007CF9C: lw          $t3, 0x0($s1)
    ctx->r11 = MEM_W(ctx->r17, 0X0);
L_8007CFA0:
    // 0x8007CFA0: lw          $t4, 0x0($s0)
    ctx->r12 = MEM_W(ctx->r16, 0X0);
    // 0x8007CFA4: bnel        $t3, $t4, L_8007CFEC
    if (ctx->r11 != ctx->r12) {
        // 0x8007CFA8: addiu       $s0, $s0, 0x10
        ctx->r16 = ADD32(ctx->r16, 0X10);
            goto L_8007CFEC;
    }
    goto skip_9;
    // 0x8007CFA8: addiu       $s0, $s0, 0x10
    ctx->r16 = ADD32(ctx->r16, 0X10);
    skip_9:
    // 0x8007CFAC: lw          $t6, 0x4($s1)
    ctx->r14 = MEM_W(ctx->r17, 0X4);
    // 0x8007CFB0: lw          $t7, 0x4($s0)
    ctx->r15 = MEM_W(ctx->r16, 0X4);
    // 0x8007CFB4: bnel        $t6, $t7, L_8007CFEC
    if (ctx->r14 != ctx->r15) {
        // 0x8007CFB8: addiu       $s0, $s0, 0x10
        ctx->r16 = ADD32(ctx->r16, 0X10);
            goto L_8007CFEC;
    }
    goto skip_10;
    // 0x8007CFB8: addiu       $s0, $s0, 0x10
    ctx->r16 = ADD32(ctx->r16, 0X10);
    skip_10:
    // 0x8007CFBC: lw          $t9, 0x8($s1)
    ctx->r25 = MEM_W(ctx->r17, 0X8);
    // 0x8007CFC0: lw          $t8, 0x8($s0)
    ctx->r24 = MEM_W(ctx->r16, 0X8);
    // 0x8007CFC4: addiu       $a0, $s1, 0xC
    ctx->r4 = ADD32(ctx->r17, 0XC);
    // 0x8007CFC8: addiu       $a1, $s0, 0xC
    ctx->r5 = ADD32(ctx->r16, 0XC);
    // 0x8007CFCC: bnel        $t9, $t8, L_8007CFEC
    if (ctx->r25 != ctx->r24) {
        // 0x8007CFD0: addiu       $s0, $s0, 0x10
        ctx->r16 = ADD32(ctx->r16, 0X10);
            goto L_8007CFEC;
    }
    goto skip_11;
    // 0x8007CFD0: addiu       $s0, $s0, 0x10
    ctx->r16 = ADD32(ctx->r16, 0X10);
    skip_11:
    // 0x8007CFD4: jal         0x8006A1CC
    // 0x8007CFD8: addiu       $a2, $zero, 0x3
    ctx->r6 = ADD32(0, 0X3);
    Libc_strncmp(rdram, ctx);
        goto after_12;
    // 0x8007CFD8: addiu       $a2, $zero, 0x3
    ctx->r6 = ADD32(0, 0X3);
    after_12:
    // 0x8007CFDC: bnel        $v0, $zero, L_8007CFEC
    if (ctx->r2 != 0) {
        // 0x8007CFE0: addiu       $s0, $s0, 0x10
        ctx->r16 = ADD32(ctx->r16, 0X10);
            goto L_8007CFEC;
    }
    goto skip_12;
    // 0x8007CFE0: addiu       $s0, $s0, 0x10
    ctx->r16 = ADD32(ctx->r16, 0X10);
    skip_12:
    // 0x8007CFE4: sw          $zero, 0x0($s0)
    MEM_W(0X0, ctx->r16) = 0;
    // 0x8007CFE8: addiu       $s0, $s0, 0x10
    ctx->r16 = ADD32(ctx->r16, 0X10);
L_8007CFEC:
    // 0x8007CFEC: bnel        $s0, $s5, L_8007CFA0
    if (ctx->r16 != ctx->r21) {
        // 0x8007CFF0: lw          $t3, 0x0($s1)
        ctx->r11 = MEM_W(ctx->r17, 0X0);
            goto L_8007CFA0;
    }
    goto skip_13;
    // 0x8007CFF0: lw          $t3, 0x0($s1)
    ctx->r11 = MEM_W(ctx->r17, 0X0);
    skip_13:
    // 0x8007CFF4: addiu       $s1, $s1, 0x10
    ctx->r17 = ADD32(ctx->r17, 0X10);
    // 0x8007CFF8: addiu       $t5, $sp, 0xC8
    ctx->r13 = ADD32(ctx->r29, 0XC8);
    // 0x8007CFFC: sltu        $at, $s1, $t5
    ctx->r1 = ctx->r17 < ctx->r13 ? 1 : 0;
    // 0x8007D000: bnel        $at, $zero, L_8007CF9C
    if (ctx->r1 != 0) {
        // 0x8007D004: addiu       $s0, $sp, 0x68
        ctx->r16 = ADD32(ctx->r29, 0X68);
            goto L_8007CF9C;
    }
    goto skip_14;
    // 0x8007D004: addiu       $s0, $sp, 0x68
    ctx->r16 = ADD32(ctx->r29, 0X68);
    skip_14:
    // 0x8007D008: addiu       $s1, $sp, 0x98
    ctx->r17 = ADD32(ctx->r29, 0X98);
    // 0x8007D00C: addiu       $v0, $sp, 0xC8
    ctx->r2 = ADD32(ctx->r29, 0XC8);
    // 0x8007D010: addiu       $s0, $sp, 0x68
    ctx->r16 = ADD32(ctx->r29, 0X68);
L_8007D014:
    // 0x8007D014: lw          $t2, 0x0($s1)
    ctx->r10 = MEM_W(ctx->r17, 0X0);
L_8007D018:
    // 0x8007D018: lw          $t3, 0x0($s0)
    ctx->r11 = MEM_W(ctx->r16, 0X0);
    // 0x8007D01C: slt         $at, $t2, $t3
    ctx->r1 = SIGNED(ctx->r10) < SIGNED(ctx->r11) ? 1 : 0;
    // 0x8007D020: beql        $at, $zero, L_8007D088
    if (ctx->r1 == 0) {
        // 0x8007D024: addiu       $s0, $s0, 0x10
        ctx->r16 = ADD32(ctx->r16, 0X10);
            goto L_8007D088;
    }
    goto skip_15;
    // 0x8007D024: addiu       $s0, $s0, 0x10
    ctx->r16 = ADD32(ctx->r16, 0X10);
    skip_15:
    // 0x8007D028: lw          $at, 0x0($s1)
    ctx->r1 = MEM_W(ctx->r17, 0X0);
    // 0x8007D02C: lw          $t6, 0x4($s1)
    ctx->r14 = MEM_W(ctx->r17, 0X4);
    // 0x8007D030: lw          $t9, 0x4($s0)
    ctx->r25 = MEM_W(ctx->r16, 0X4);
    // 0x8007D034: sw          $at, 0x0($s2)
    MEM_W(0X0, ctx->r18) = ctx->r1;
    // 0x8007D038: lw          $at, 0x8($s1)
    ctx->r1 = MEM_W(ctx->r17, 0X8);
    // 0x8007D03C: sw          $t6, 0x4($s2)
    MEM_W(0X4, ctx->r18) = ctx->r14;
    // 0x8007D040: lw          $t6, 0xC($s1)
    ctx->r14 = MEM_W(ctx->r17, 0XC);
    // 0x8007D044: sw          $at, 0x8($s2)
    MEM_W(0X8, ctx->r18) = ctx->r1;
    // 0x8007D048: lw          $at, 0x0($s0)
    ctx->r1 = MEM_W(ctx->r16, 0X0);
    // 0x8007D04C: sw          $t9, 0x4($s1)
    MEM_W(0X4, ctx->r17) = ctx->r25;
    // 0x8007D050: lw          $t9, 0xC($s0)
    ctx->r25 = MEM_W(ctx->r16, 0XC);
    // 0x8007D054: sw          $at, 0x0($s1)
    MEM_W(0X0, ctx->r17) = ctx->r1;
    // 0x8007D058: lw          $at, 0x8($s0)
    ctx->r1 = MEM_W(ctx->r16, 0X8);
    // 0x8007D05C: lw          $t5, 0x4($s2)
    ctx->r13 = MEM_W(ctx->r18, 0X4);
    // 0x8007D060: sw          $t6, 0xC($s2)
    MEM_W(0XC, ctx->r18) = ctx->r14;
    // 0x8007D064: sw          $at, 0x8($s1)
    MEM_W(0X8, ctx->r17) = ctx->r1;
    // 0x8007D068: lw          $at, 0x0($s2)
    ctx->r1 = MEM_W(ctx->r18, 0X0);
    // 0x8007D06C: sw          $t6, 0xC($s0)
    MEM_W(0XC, ctx->r16) = ctx->r14;
    // 0x8007D070: sw          $t9, 0xC($s1)
    MEM_W(0XC, ctx->r17) = ctx->r25;
    // 0x8007D074: sw          $at, 0x0($s0)
    MEM_W(0X0, ctx->r16) = ctx->r1;
    // 0x8007D078: lw          $at, 0x8($s2)
    ctx->r1 = MEM_W(ctx->r18, 0X8);
    // 0x8007D07C: sw          $t5, 0x4($s0)
    MEM_W(0X4, ctx->r16) = ctx->r13;
    // 0x8007D080: sw          $at, 0x8($s0)
    MEM_W(0X8, ctx->r16) = ctx->r1;
    // 0x8007D084: addiu       $s0, $s0, 0x10
    ctx->r16 = ADD32(ctx->r16, 0X10);
L_8007D088:
    // 0x8007D088: bnel        $s0, $s6, L_8007D018
    if (ctx->r16 != ctx->r22) {
        // 0x8007D08C: lw          $t2, 0x0($s1)
        ctx->r10 = MEM_W(ctx->r17, 0X0);
            goto L_8007D018;
    }
    goto skip_16;
    // 0x8007D08C: lw          $t2, 0x0($s1)
    ctx->r10 = MEM_W(ctx->r17, 0X0);
    skip_16:
    // 0x8007D090: addiu       $s1, $s1, 0x10
    ctx->r17 = ADD32(ctx->r17, 0X10);
    // 0x8007D094: sltu        $at, $s1, $v0
    ctx->r1 = ctx->r17 < ctx->r2 ? 1 : 0;
    // 0x8007D098: bnel        $at, $zero, L_8007D014
    if (ctx->r1 != 0) {
        // 0x8007D09C: addiu       $s0, $sp, 0x68
        ctx->r16 = ADD32(ctx->r29, 0X68);
            goto L_8007D014;
    }
    goto skip_17;
    // 0x8007D09C: addiu       $s0, $sp, 0x68
    ctx->r16 = ADD32(ctx->r29, 0X68);
    skip_17:
    // 0x8007D0A0: addiu       $s0, $s7, 0x120
    ctx->r16 = ADD32(ctx->r23, 0X120);
    // 0x8007D0A4: addiu       $s1, $sp, 0x98
    ctx->r17 = ADD32(ctx->r29, 0X98);
L_8007D0A8:
    // 0x8007D0A8: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    // 0x8007D0AC: jal         0x8007B1AC
    // 0x8007D0B0: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    func_8007B1AC(rdram, ctx);
        goto after_13;
    // 0x8007D0B0: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    after_13:
    // 0x8007D0B4: addiu       $s1, $s1, 0x10
    ctx->r17 = ADD32(ctx->r17, 0X10);
    // 0x8007D0B8: addiu       $t2, $sp, 0xC8
    ctx->r10 = ADD32(ctx->r29, 0XC8);
    // 0x8007D0BC: bne         $s1, $t2, L_8007D0A8
    if (ctx->r17 != ctx->r10) {
        // 0x8007D0C0: addiu       $s0, $s0, 0x5
        ctx->r16 = ADD32(ctx->r16, 0X5);
            goto L_8007D0A8;
    }
    // 0x8007D0C0: addiu       $s0, $s0, 0x5
    ctx->r16 = ADD32(ctx->r16, 0X5);
    // 0x8007D0C4: lw          $t3, 0x48($sp)
    ctx->r11 = MEM_W(ctx->r29, 0X48);
    // 0x8007D0C8: lui         $t6, 0x801B
    ctx->r14 = S32(0X801B << 16);
    // 0x8007D0CC: addiu       $t6, $t6, -0x1361
    ctx->r14 = ADD32(ctx->r14, -0X1361);
    // 0x8007D0D0: addiu       $t4, $t3, 0xF
    ctx->r12 = ADD32(ctx->r11, 0XF);
    // 0x8007D0D4: sw          $t4, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r12;
    // 0x8007D0D8: bne         $t4, $t6, L_8007CF50
    if (ctx->r12 != ctx->r14) {
        // 0x8007D0DC: addiu       $s7, $s7, 0xF
        ctx->r23 = ADD32(ctx->r23, 0XF);
            goto L_8007CF50;
    }
    // 0x8007D0DC: addiu       $s7, $s7, 0xF
    ctx->r23 = ADD32(ctx->r23, 0XF);
    // 0x8007D0E0: lw          $ra, 0x3C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X3C);
    // 0x8007D0E4: lw          $s0, 0x18($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X18);
    // 0x8007D0E8: lw          $s1, 0x1C($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X1C);
    // 0x8007D0EC: lw          $s2, 0x20($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X20);
    // 0x8007D0F0: lw          $s3, 0x24($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X24);
    // 0x8007D0F4: lw          $s4, 0x28($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X28);
    // 0x8007D0F8: lw          $s5, 0x2C($sp)
    ctx->r21 = MEM_W(ctx->r29, 0X2C);
    // 0x8007D0FC: lw          $s6, 0x30($sp)
    ctx->r22 = MEM_W(ctx->r29, 0X30);
    // 0x8007D100: lw          $s7, 0x34($sp)
    ctx->r23 = MEM_W(ctx->r29, 0X34);
    // 0x8007D104: lw          $fp, 0x38($sp)
    ctx->r30 = MEM_W(ctx->r29, 0X38);
    // 0x8007D108: jr          $ra
    // 0x8007D10C: addiu       $sp, $sp, 0x170
    ctx->r29 = ADD32(ctx->r29, 0X170);
    return;
    // 0x8007D10C: addiu       $sp, $sp, 0x170
    ctx->r29 = ADD32(ctx->r29, 0X170);
;}
RECOMP_FUNC void Save_PfsIsPlug(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8007D110: addiu       $sp, $sp, -0x40
    ctx->r29 = ADD32(ctx->r29, -0X40);
    // 0x8007D114: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x8007D118: lui         $a0, 0x8015
    ctx->r4 = S32(0X8015 << 16);
    // 0x8007D11C: addiu       $a0, $a0, 0x40D0
    ctx->r4 = ADD32(ctx->r4, 0X40D0);
    // 0x8007D120: jal         0x800C85C0
    // 0x8007D124: addiu       $a1, $sp, 0x32
    ctx->r5 = ADD32(ctx->r29, 0X32);
    osPfsIsPlug_recomp(rdram, ctx);
        goto after_0;
    // 0x8007D124: addiu       $a1, $sp, 0x32
    ctx->r5 = ADD32(ctx->r29, 0X32);
    after_0:
    // 0x8007D128: lui         $a2, 0x8015
    ctx->r6 = S32(0X8015 << 16);
    // 0x8007D12C: lw          $a2, 0x4330($a2)
    ctx->r6 = MEM_W(ctx->r6, 0X4330);
    // 0x8007D130: lbu         $t8, 0x32($sp)
    ctx->r24 = MEM_BU(ctx->r29, 0X32);
    // 0x8007D134: addiu       $t6, $zero, 0x1
    ctx->r14 = ADD32(0, 0X1);
    // 0x8007D138: sllv        $t7, $t6, $a2
    ctx->r15 = S32(ctx->r14 << (ctx->r6 & 31));
    // 0x8007D13C: and         $t9, $t7, $t8
    ctx->r25 = ctx->r15 & ctx->r24;
    // 0x8007D140: bne         $t9, $zero, L_8007D158
    if (ctx->r25 != 0) {
        // 0x8007D144: addiu       $t0, $zero, 0x1
        ctx->r8 = ADD32(0, 0X1);
            goto L_8007D158;
    }
    // 0x8007D144: addiu       $t0, $zero, 0x1
    ctx->r8 = ADD32(0, 0X1);
    // 0x8007D148: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x8007D14C: sw          $zero, -0x7D9C($at)
    MEM_W(-0X7D9C, ctx->r1) = 0;
    // 0x8007D150: b           L_8007D1A8
    // 0x8007D154: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
        goto L_8007D1A8;
    // 0x8007D154: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
L_8007D158:
    // 0x8007D158: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x8007D15C: lui         $a0, 0x8015
    ctx->r4 = S32(0X8015 << 16);
    // 0x8007D160: lui         $a1, 0x801C
    ctx->r5 = S32(0X801C << 16);
    // 0x8007D164: sw          $t0, -0x7D9C($at)
    MEM_W(-0X7D9C, ctx->r1) = ctx->r8;
    // 0x8007D168: addiu       $a1, $a1, 0x3AD0
    ctx->r5 = ADD32(ctx->r5, 0X3AD0);
    // 0x8007D16C: jal         0x800C88F0
    // 0x8007D170: addiu       $a0, $a0, 0x40D0
    ctx->r4 = ADD32(ctx->r4, 0X40D0);
    osPfsInit_recomp(rdram, ctx);
        goto after_1;
    // 0x8007D170: addiu       $a0, $a0, 0x40D0
    ctx->r4 = ADD32(ctx->r4, 0X40D0);
    after_1:
    // 0x8007D174: sltiu       $at, $v0, 0xC
    ctx->r1 = ctx->r2 < 0XC ? 1 : 0;
    // 0x8007D178: beq         $at, $zero, L_8007D1A4
    if (ctx->r1 == 0) {
        // 0x8007D17C: sll         $t1, $v0, 2
        ctx->r9 = S32(ctx->r2 << 2);
            goto L_8007D1A4;
    }
    // 0x8007D17C: sll         $t1, $v0, 2
    ctx->r9 = S32(ctx->r2 << 2);
    // 0x8007D180: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x8007D184: addu        $at, $at, $t1
    gpr jr_addend_8007D18C = ctx->r9;
    ctx->r1 = ADD32(ctx->r1, ctx->r9);
    // 0x8007D188: lw          $t1, -0x5D78($at)
    ctx->r9 = ADD32(ctx->r1, -0X5D78);
    // 0x8007D18C: jr          $t1
    // 0x8007D190: nop

    switch (jr_addend_8007D18C >> 2) {
        case 0: goto L_8007D194; break;
        case 1: goto L_8007D19C; break;
        case 2: goto L_8007D1A4; break;
        case 3: goto L_8007D1A4; break;
        case 4: goto L_8007D1A4; break;
        case 5: goto L_8007D1A4; break;
        case 6: goto L_8007D1A4; break;
        case 7: goto L_8007D1A4; break;
        case 8: goto L_8007D1A4; break;
        case 9: goto L_8007D1A4; break;
        case 10: goto L_8007D1A4; break;
        case 11: goto L_8007D19C; break;
        default: switch_error(__func__, 0x8007D18C, 0x800EA288);
    }
    // 0x8007D190: nop

L_8007D194:
    // 0x8007D194: b           L_8007D1A8
    // 0x8007D198: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
        goto L_8007D1A8;
    // 0x8007D198: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_8007D19C:
    // 0x8007D19C: b           L_8007D1A8
    // 0x8007D1A0: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
        goto L_8007D1A8;
    // 0x8007D1A0: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
L_8007D1A4:
    // 0x8007D1A4: addiu       $v0, $zero, 0x2
    ctx->r2 = ADD32(0, 0X2);
L_8007D1A8:
    // 0x8007D1A8: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x8007D1AC: addiu       $sp, $sp, 0x40
    ctx->r29 = ADD32(ctx->r29, 0X40);
    // 0x8007D1B0: jr          $ra
    // 0x8007D1B4: nop

    return;
    // 0x8007D1B4: nop

;}
RECOMP_FUNC void Save_PfsFindFile(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8007D1B8: addiu       $sp, $sp, -0x28
    ctx->r29 = ADD32(ctx->r29, -0X28);
    // 0x8007D1BC: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x8007D1C0: jal         0x8007D110
    // 0x8007D1C4: nop

    Save_PfsIsPlug(rdram, ctx);
        goto after_0;
    // 0x8007D1C4: nop

    after_0:
    // 0x8007D1C8: beq         $v0, $zero, L_8007D1D8
    if (ctx->r2 == 0) {
        // 0x8007D1CC: lui         $a0, 0x801C
        ctx->r4 = S32(0X801C << 16);
            goto L_8007D1D8;
    }
    // 0x8007D1CC: lui         $a0, 0x801C
    ctx->r4 = S32(0X801C << 16);
    // 0x8007D1D0: b           L_8007D240
    // 0x8007D1D4: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
        goto L_8007D240;
    // 0x8007D1D4: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
L_8007D1D8:
    // 0x8007D1D8: lui         $t6, 0x800E
    ctx->r14 = S32(0X800E << 16);
    // 0x8007D1DC: addiu       $t6, $t6, -0x7D28
    ctx->r14 = ADD32(ctx->r14, -0X7D28);
    // 0x8007D1E0: lui         $a2, 0x4E57
    ctx->r6 = S32(0X4E57 << 16);
    // 0x8007D1E4: lui         $a3, 0x800E
    ctx->r7 = S32(0X800E << 16);
    // 0x8007D1E8: addiu       $t7, $sp, 0x20
    ctx->r15 = ADD32(ctx->r29, 0X20);
    // 0x8007D1EC: sw          $t7, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r15;
    // 0x8007D1F0: addiu       $a3, $a3, -0x7D18
    ctx->r7 = ADD32(ctx->r7, -0X7D18);
    // 0x8007D1F4: ori         $a2, $a2, 0x524A
    ctx->r6 = ctx->r6 | 0X524A;
    // 0x8007D1F8: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x8007D1FC: addiu       $a0, $a0, 0x3AD0
    ctx->r4 = ADD32(ctx->r4, 0X3AD0);
    // 0x8007D200: jal         0x800C8A70
    // 0x8007D204: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    osPfsFindFile_recomp(rdram, ctx);
        goto after_1;
    // 0x8007D204: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    after_1:
    // 0x8007D208: sltiu       $at, $v0, 0x6
    ctx->r1 = ctx->r2 < 0X6 ? 1 : 0;
    // 0x8007D20C: beq         $at, $zero, L_8007D238
    if (ctx->r1 == 0) {
        // 0x8007D210: sll         $t8, $v0, 2
        ctx->r24 = S32(ctx->r2 << 2);
            goto L_8007D238;
    }
    // 0x8007D210: sll         $t8, $v0, 2
    ctx->r24 = S32(ctx->r2 << 2);
    // 0x8007D214: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x8007D218: addu        $at, $at, $t8
    gpr jr_addend_8007D220 = ctx->r24;
    ctx->r1 = ADD32(ctx->r1, ctx->r24);
    // 0x8007D21C: lw          $t8, -0x5D48($at)
    ctx->r24 = ADD32(ctx->r1, -0X5D48);
    // 0x8007D220: jr          $t8
    // 0x8007D224: nop

    switch (jr_addend_8007D220 >> 2) {
        case 0: goto L_8007D228; break;
        case 1: goto L_8007D238; break;
        case 2: goto L_8007D238; break;
        case 3: goto L_8007D238; break;
        case 4: goto L_8007D238; break;
        case 5: goto L_8007D230; break;
        default: switch_error(__func__, 0x8007D220, 0x800EA2B8);
    }
    // 0x8007D224: nop

L_8007D228:
    // 0x8007D228: b           L_8007D23C
    // 0x8007D22C: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
        goto L_8007D23C;
    // 0x8007D22C: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_8007D230:
    // 0x8007D230: b           L_8007D23C
    // 0x8007D234: addiu       $v0, $zero, 0x4
    ctx->r2 = ADD32(0, 0X4);
        goto L_8007D23C;
    // 0x8007D234: addiu       $v0, $zero, 0x4
    ctx->r2 = ADD32(0, 0X4);
L_8007D238:
    // 0x8007D238: addiu       $v0, $zero, 0x2
    ctx->r2 = ADD32(0, 0X2);
L_8007D23C:
    // 0x8007D23C: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
L_8007D240:
    // 0x8007D240: addiu       $sp, $sp, 0x28
    ctx->r29 = ADD32(ctx->r29, 0X28);
    // 0x8007D244: jr          $ra
    // 0x8007D248: nop

    return;
    // 0x8007D248: nop

;}
RECOMP_FUNC void Save_PfsCheckFree(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8007D24C: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x8007D250: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x8007D254: jal         0x8007D110
    // 0x8007D258: nop

    Save_PfsIsPlug(rdram, ctx);
        goto after_0;
    // 0x8007D258: nop

    after_0:
    // 0x8007D25C: beq         $v0, $zero, L_8007D26C
    if (ctx->r2 == 0) {
        // 0x8007D260: lui         $a0, 0x801C
        ctx->r4 = S32(0X801C << 16);
            goto L_8007D26C;
    }
    // 0x8007D260: lui         $a0, 0x801C
    ctx->r4 = S32(0X801C << 16);
    // 0x8007D264: b           L_8007D2C8
    // 0x8007D268: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_8007D2C8;
    // 0x8007D268: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_8007D26C:
    // 0x8007D26C: addiu       $a0, $a0, 0x3AD0
    ctx->r4 = ADD32(ctx->r4, 0X3AD0);
    // 0x8007D270: jal         0x800C8C10
    // 0x8007D274: addiu       $a1, $sp, 0x18
    ctx->r5 = ADD32(ctx->r29, 0X18);
    osPfsFreeBlocks_recomp(rdram, ctx);
        goto after_1;
    // 0x8007D274: addiu       $a1, $sp, 0x18
    ctx->r5 = ADD32(ctx->r29, 0X18);
    after_1:
    // 0x8007D278: sltiu       $at, $v0, 0x6
    ctx->r1 = ctx->r2 < 0X6 ? 1 : 0;
    // 0x8007D27C: beq         $at, $zero, L_8007D2C0
    if (ctx->r1 == 0) {
        // 0x8007D280: sll         $t6, $v0, 2
        ctx->r14 = S32(ctx->r2 << 2);
            goto L_8007D2C0;
    }
    // 0x8007D280: sll         $t6, $v0, 2
    ctx->r14 = S32(ctx->r2 << 2);
    // 0x8007D284: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x8007D288: addu        $at, $at, $t6
    gpr jr_addend_8007D290 = ctx->r14;
    ctx->r1 = ADD32(ctx->r1, ctx->r14);
    // 0x8007D28C: lw          $t6, -0x5D30($at)
    ctx->r14 = ADD32(ctx->r1, -0X5D30);
    // 0x8007D290: jr          $t6
    // 0x8007D294: nop

    switch (jr_addend_8007D290 >> 2) {
        case 0: goto L_8007D298; break;
        case 1: goto L_8007D2C0; break;
        case 2: goto L_8007D2C0; break;
        case 3: goto L_8007D2C0; break;
        case 4: goto L_8007D2C0; break;
        case 5: goto L_8007D2B8; break;
        default: switch_error(__func__, 0x8007D290, 0x800EA2D0);
    }
    // 0x8007D294: nop

L_8007D298:
    // 0x8007D298: lw          $t7, 0x18($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X18);
    // 0x8007D29C: slti        $at, $t7, 0x200
    ctx->r1 = SIGNED(ctx->r15) < 0X200 ? 1 : 0;
    // 0x8007D2A0: bne         $at, $zero, L_8007D2B0
    if (ctx->r1 != 0) {
        // 0x8007D2A4: nop
    
            goto L_8007D2B0;
    }
    // 0x8007D2A4: nop

    // 0x8007D2A8: b           L_8007D2C4
    // 0x8007D2AC: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
        goto L_8007D2C4;
    // 0x8007D2AC: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_8007D2B0:
    // 0x8007D2B0: b           L_8007D2C4
    // 0x8007D2B4: addiu       $v0, $zero, 0x3
    ctx->r2 = ADD32(0, 0X3);
        goto L_8007D2C4;
    // 0x8007D2B4: addiu       $v0, $zero, 0x3
    ctx->r2 = ADD32(0, 0X3);
L_8007D2B8:
    // 0x8007D2B8: b           L_8007D2C4
    // 0x8007D2BC: addiu       $v0, $zero, 0x4
    ctx->r2 = ADD32(0, 0X4);
        goto L_8007D2C4;
    // 0x8007D2BC: addiu       $v0, $zero, 0x4
    ctx->r2 = ADD32(0, 0X4);
L_8007D2C0:
    // 0x8007D2C0: addiu       $v0, $zero, 0x2
    ctx->r2 = ADD32(0, 0X2);
L_8007D2C4:
    // 0x8007D2C4: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_8007D2C8:
    // 0x8007D2C8: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x8007D2CC: jr          $ra
    // 0x8007D2D0: nop

    return;
    // 0x8007D2D0: nop

;}
RECOMP_FUNC void func_8007D2D4(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8007D2D4: addiu       $sp, $sp, -0x48
    ctx->r29 = ADD32(ctx->r29, -0X48);
    // 0x8007D2D8: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x8007D2DC: sw          $a0, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r4;
    // 0x8007D2E0: jal         0x8007D110
    // 0x8007D2E4: sw          $zero, 0x34($sp)
    MEM_W(0X34, ctx->r29) = 0;
    Save_PfsIsPlug(rdram, ctx);
        goto after_0;
    // 0x8007D2E4: sw          $zero, 0x34($sp)
    MEM_W(0X34, ctx->r29) = 0;
    after_0:
    // 0x8007D2E8: beq         $v0, $zero, L_8007D2F8
    if (ctx->r2 == 0) {
        // 0x8007D2EC: lui         $a0, 0x801C
        ctx->r4 = S32(0X801C << 16);
            goto L_8007D2F8;
    }
    // 0x8007D2EC: lui         $a0, 0x801C
    ctx->r4 = S32(0X801C << 16);
    // 0x8007D2F0: b           L_8007D608
    // 0x8007D2F4: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
        goto L_8007D608;
    // 0x8007D2F4: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
L_8007D2F8:
    // 0x8007D2F8: lw          $v0, 0x48($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X48);
    // 0x8007D2FC: addiu       $a0, $a0, 0x3AD0
    ctx->r4 = ADD32(ctx->r4, 0X3AD0);
    // 0x8007D300: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x8007D304: slti        $at, $v0, 0x80
    ctx->r1 = SIGNED(ctx->r2) < 0X80 ? 1 : 0;
    // 0x8007D308: bne         $at, $zero, L_8007D31C
    if (ctx->r1 != 0) {
        // 0x8007D30C: lui         $a2, 0x4E57
        ctx->r6 = S32(0X4E57 << 16);
            goto L_8007D31C;
    }
    // 0x8007D30C: lui         $a2, 0x4E57
    ctx->r6 = S32(0X4E57 << 16);
    // 0x8007D310: addiu       $t6, $zero, 0x1
    ctx->r14 = ADD32(0, 0X1);
    // 0x8007D314: addiu       $v0, $v0, -0x80
    ctx->r2 = ADD32(ctx->r2, -0X80);
    // 0x8007D318: sw          $t6, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r14;
L_8007D31C:
    // 0x8007D31C: lui         $t7, 0x800E
    ctx->r15 = S32(0X800E << 16);
    // 0x8007D320: addiu       $t7, $t7, -0x7D28
    ctx->r15 = ADD32(ctx->r15, -0X7D28);
    // 0x8007D324: lui         $a3, 0x800E
    ctx->r7 = S32(0X800E << 16);
    // 0x8007D328: addiu       $t8, $sp, 0x30
    ctx->r24 = ADD32(ctx->r29, 0X30);
    // 0x8007D32C: sw          $t8, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r24;
    // 0x8007D330: addiu       $a3, $a3, -0x7D18
    ctx->r7 = ADD32(ctx->r7, -0X7D18);
    // 0x8007D334: sw          $t7, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r15;
    // 0x8007D338: ori         $a2, $a2, 0x524A
    ctx->r6 = ctx->r6 | 0X524A;
    // 0x8007D33C: jal         0x800C8A70
    // 0x8007D340: sw          $v0, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r2;
    osPfsFindFile_recomp(rdram, ctx);
        goto after_1;
    // 0x8007D340: sw          $v0, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r2;
    after_1:
    // 0x8007D344: bne         $v0, $zero, L_8007D600
    if (ctx->r2 != 0) {
        // 0x8007D348: lui         $a0, 0x801C
        ctx->r4 = S32(0X801C << 16);
            goto L_8007D600;
    }
    // 0x8007D348: lui         $a0, 0x801C
    ctx->r4 = S32(0X801C << 16);
    // 0x8007D34C: lui         $t0, 0x801B
    ctx->r8 = S32(0X801B << 16);
    // 0x8007D350: addiu       $t0, $t0, -0x13E8
    ctx->r8 = ADD32(ctx->r8, -0X13E8);
    // 0x8007D354: addiu       $t9, $zero, 0x200
    ctx->r25 = ADD32(0, 0X200);
    // 0x8007D358: sw          $t9, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r25;
    // 0x8007D35C: sw          $t0, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r8;
    // 0x8007D360: addiu       $a0, $a0, 0x3AD0
    ctx->r4 = ADD32(ctx->r4, 0X3AD0);
    // 0x8007D364: lw          $a1, 0x30($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X30);
    // 0x8007D368: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x8007D36C: jal         0x800C8EA0
    // 0x8007D370: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    osPfsReadWriteFile_recomp(rdram, ctx);
        goto after_2;
    // 0x8007D370: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_2:
    // 0x8007D374: sltiu       $at, $v0, 0x7
    ctx->r1 = ctx->r2 < 0X7 ? 1 : 0;
    // 0x8007D378: beq         $at, $zero, L_8007D604
    if (ctx->r1 == 0) {
        // 0x8007D37C: sll         $t1, $v0, 2
        ctx->r9 = S32(ctx->r2 << 2);
            goto L_8007D604;
    }
    // 0x8007D37C: sll         $t1, $v0, 2
    ctx->r9 = S32(ctx->r2 << 2);
    // 0x8007D380: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x8007D384: addu        $at, $at, $t1
    gpr jr_addend_8007D38C = ctx->r9;
    ctx->r1 = ADD32(ctx->r1, ctx->r9);
    // 0x8007D388: lw          $t1, -0x5D18($at)
    ctx->r9 = ADD32(ctx->r1, -0X5D18);
    // 0x8007D38C: jr          $t1
    // 0x8007D390: nop

    switch (jr_addend_8007D38C >> 2) {
        case 0: goto L_8007D394; break;
        case 1: goto L_8007D604; break;
        case 2: goto L_8007D5F8; break;
        case 3: goto L_8007D5F8; break;
        case 4: goto L_8007D5F8; break;
        case 5: goto L_8007D5F8; break;
        case 6: goto L_8007D5F8; break;
        default: switch_error(__func__, 0x8007D38C, 0x800EA2E8);
    }
    // 0x8007D390: nop

L_8007D394:
    // 0x8007D394: lui         $v1, 0x801B
    ctx->r3 = S32(0X801B << 16);
    // 0x8007D398: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x8007D39C: lui         $a0, 0x800E
    ctx->r4 = S32(0X800E << 16);
    // 0x8007D3A0: addiu       $a0, $a0, -0x7D96
    ctx->r4 = ADD32(ctx->r4, -0X7D96);
    // 0x8007D3A4: addiu       $v0, $v0, -0x7D98
    ctx->r2 = ADD32(ctx->r2, -0X7D98);
    // 0x8007D3A8: addiu       $v1, $v1, -0x13E8
    ctx->r3 = ADD32(ctx->r3, -0X13E8);
L_8007D3AC:
    // 0x8007D3AC: lbu         $t2, 0x0($v1)
    ctx->r10 = MEM_BU(ctx->r3, 0X0);
    // 0x8007D3B0: lbu         $t3, 0x0($v0)
    ctx->r11 = MEM_BU(ctx->r2, 0X0);
    // 0x8007D3B4: addiu       $v0, $v0, 0x1
    ctx->r2 = ADD32(ctx->r2, 0X1);
    // 0x8007D3B8: sltu        $at, $v0, $a0
    ctx->r1 = ctx->r2 < ctx->r4 ? 1 : 0;
    // 0x8007D3BC: beq         $t2, $t3, L_8007D3CC
    if (ctx->r10 == ctx->r11) {
        // 0x8007D3C0: nop
    
            goto L_8007D3CC;
    }
    // 0x8007D3C0: nop

    // 0x8007D3C4: b           L_8007D604
    // 0x8007D3C8: addiu       $v0, $zero, 0x6
    ctx->r2 = ADD32(0, 0X6);
        goto L_8007D604;
    // 0x8007D3C8: addiu       $v0, $zero, 0x6
    ctx->r2 = ADD32(0, 0X6);
L_8007D3CC:
    // 0x8007D3CC: bne         $at, $zero, L_8007D3AC
    if (ctx->r1 != 0) {
        // 0x8007D3D0: addiu       $v1, $v1, 0x1
        ctx->r3 = ADD32(ctx->r3, 0X1);
            goto L_8007D3AC;
    }
    // 0x8007D3D0: addiu       $v1, $v1, 0x1
    ctx->r3 = ADD32(ctx->r3, 0X1);
    // 0x8007D3D4: lui         $a0, 0x801B
    ctx->r4 = S32(0X801B << 16);
    // 0x8007D3D8: jal         0x8007BBF8
    // 0x8007D3DC: addiu       $a0, $a0, -0x13E8
    ctx->r4 = ADD32(ctx->r4, -0X13E8);
    Save_GenCheckSum(rdram, ctx);
        goto after_3;
    // 0x8007D3DC: addiu       $a0, $a0, -0x13E8
    ctx->r4 = ADD32(ctx->r4, -0X13E8);
    after_3:
    // 0x8007D3E0: lui         $t4, 0x801B
    ctx->r12 = S32(0X801B << 16);
    // 0x8007D3E4: lhu         $t4, -0x13E6($t4)
    ctx->r12 = MEM_HU(ctx->r12, -0X13E6);
    // 0x8007D3E8: beq         $v0, $t4, L_8007D3F8
    if (ctx->r2 == ctx->r12) {
        // 0x8007D3EC: nop
    
            goto L_8007D3F8;
    }
    // 0x8007D3EC: nop

    // 0x8007D3F0: b           L_8007D604
    // 0x8007D3F4: addiu       $v0, $zero, 0x6
    ctx->r2 = ADD32(0, 0X6);
        goto L_8007D604;
    // 0x8007D3F4: addiu       $v0, $zero, 0x6
    ctx->r2 = ADD32(0, 0X6);
L_8007D3F8:
    // 0x8007D3F8: jal         0x8007B930
    // 0x8007D3FC: nop

    func_8007B930(rdram, ctx);
        goto after_4;
    // 0x8007D3FC: nop

    after_4:
    // 0x8007D400: lw          $t5, 0x48($sp)
    ctx->r13 = MEM_W(ctx->r29, 0X48);
    // 0x8007D404: sltiu       $at, $t5, 0x6
    ctx->r1 = ctx->r13 < 0X6 ? 1 : 0;
    // 0x8007D408: beq         $at, $zero, L_8007D5F0
    if (ctx->r1 == 0) {
        // 0x8007D40C: sll         $t5, $t5, 2
        ctx->r13 = S32(ctx->r13 << 2);
            goto L_8007D5F0;
    }
    // 0x8007D40C: sll         $t5, $t5, 2
    ctx->r13 = S32(ctx->r13 << 2);
    // 0x8007D410: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x8007D414: addu        $at, $at, $t5
    gpr jr_addend_8007D41C = ctx->r13;
    ctx->r1 = ADD32(ctx->r1, ctx->r13);
    // 0x8007D418: lw          $t5, -0x5CFC($at)
    ctx->r13 = ADD32(ctx->r1, -0X5CFC);
    // 0x8007D41C: jr          $t5
    // 0x8007D420: nop

    switch (jr_addend_8007D41C >> 2) {
        case 0: goto L_8007D424; break;
        case 1: goto L_8007D488; break;
        case 2: goto L_8007D488; break;
        case 3: goto L_8007D488; break;
        case 4: goto L_8007D488; break;
        case 5: goto L_8007D550; break;
        default: switch_error(__func__, 0x8007D41C, 0x800EA304);
    }
    // 0x8007D420: nop

L_8007D424:
    // 0x8007D424: lui         $t7, 0x801B
    ctx->r15 = S32(0X801B << 16);
    // 0x8007D428: addiu       $t7, $t7, -0x13E8
    ctx->r15 = ADD32(ctx->r15, -0X13E8);
    // 0x8007D42C: lui         $t6, 0x801B
    ctx->r14 = S32(0X801B << 16);
    // 0x8007D430: addiu       $t6, $t6, -0x15E8
    ctx->r14 = ADD32(ctx->r14, -0X15E8);
    // 0x8007D434: addiu       $t0, $t7, 0x1F8
    ctx->r8 = ADD32(ctx->r15, 0X1F8);
L_8007D438:
    // 0x8007D438: lw          $at, 0x0($t7)
    ctx->r1 = MEM_W(ctx->r15, 0X0);
    // 0x8007D43C: addiu       $t7, $t7, 0xC
    ctx->r15 = ADD32(ctx->r15, 0XC);
    // 0x8007D440: addiu       $t6, $t6, 0xC
    ctx->r14 = ADD32(ctx->r14, 0XC);
    // 0x8007D444: sw          $at, -0xC($t6)
    MEM_W(-0XC, ctx->r14) = ctx->r1;
    // 0x8007D448: lw          $at, -0x8($t7)
    ctx->r1 = MEM_W(ctx->r15, -0X8);
    // 0x8007D44C: sw          $at, -0x8($t6)
    MEM_W(-0X8, ctx->r14) = ctx->r1;
    // 0x8007D450: lw          $at, -0x4($t7)
    ctx->r1 = MEM_W(ctx->r15, -0X4);
    // 0x8007D454: bne         $t7, $t0, L_8007D438
    if (ctx->r15 != ctx->r8) {
        // 0x8007D458: sw          $at, -0x4($t6)
        MEM_W(-0X4, ctx->r14) = ctx->r1;
            goto L_8007D438;
    }
    // 0x8007D458: sw          $at, -0x4($t6)
    MEM_W(-0X4, ctx->r14) = ctx->r1;
    // 0x8007D45C: lw          $at, 0x0($t7)
    ctx->r1 = MEM_W(ctx->r15, 0X0);
    // 0x8007D460: lw          $t0, 0x4($t7)
    ctx->r8 = MEM_W(ctx->r15, 0X4);
    // 0x8007D464: sw          $at, 0x0($t6)
    MEM_W(0X0, ctx->r14) = ctx->r1;
    // 0x8007D468: jal         0x8007B630
    // 0x8007D46C: sw          $t0, 0x4($t6)
    MEM_W(0X4, ctx->r14) = ctx->r8;
    func_8007B630(rdram, ctx);
        goto after_5;
    // 0x8007D46C: sw          $t0, 0x4($t6)
    MEM_W(0X4, ctx->r14) = ctx->r8;
    after_5:
    // 0x8007D470: jal         0x8007BD20
    // 0x8007D474: nop

    func_8007BD20(rdram, ctx);
        goto after_6;
    // 0x8007D474: nop

    after_6:
    // 0x8007D478: beq         $v0, $zero, L_8007D5F0
    if (ctx->r2 == 0) {
        // 0x8007D47C: nop
    
            goto L_8007D5F0;
    }
    // 0x8007D47C: nop

    // 0x8007D480: b           L_8007D604
    // 0x8007D484: addiu       $v0, $zero, 0x5
    ctx->r2 = ADD32(0, 0X5);
        goto L_8007D604;
    // 0x8007D484: addiu       $v0, $zero, 0x5
    ctx->r2 = ADD32(0, 0X5);
L_8007D488:
    // 0x8007D488: lw          $t1, 0x34($sp)
    ctx->r9 = MEM_W(ctx->r29, 0X34);
    // 0x8007D48C: lw          $a3, 0x48($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X48);
    // 0x8007D490: lui         $t3, 0x801B
    ctx->r11 = S32(0X801B << 16);
    // 0x8007D494: bne         $t1, $zero, L_8007D4D4
    if (ctx->r9 != 0) {
        // 0x8007D498: addiu       $a3, $a3, -0x1
        ctx->r7 = ADD32(ctx->r7, -0X1);
            goto L_8007D4D4;
    }
    // 0x8007D498: addiu       $a3, $a3, -0x1
    ctx->r7 = ADD32(ctx->r7, -0X1);
    // 0x8007D49C: sll         $v0, $a3, 2
    ctx->r2 = S32(ctx->r7 << 2);
    // 0x8007D4A0: addu        $v0, $v0, $a3
    ctx->r2 = ADD32(ctx->r2, ctx->r7);
    // 0x8007D4A4: sll         $v0, $v0, 1
    ctx->r2 = S32(ctx->r2 << 1);
    // 0x8007D4A8: lui         $t5, 0x801B
    ctx->r13 = S32(0X801B << 16);
    // 0x8007D4AC: addiu       $t5, $t5, -0x13E8
    ctx->r13 = ADD32(ctx->r13, -0X13E8);
    // 0x8007D4B0: addiu       $t2, $v0, 0x10
    ctx->r10 = ADD32(ctx->r2, 0X10);
    // 0x8007D4B4: addiu       $t4, $v0, 0x10
    ctx->r12 = ADD32(ctx->r2, 0X10);
    // 0x8007D4B8: addiu       $t3, $t3, -0x15E8
    ctx->r11 = ADD32(ctx->r11, -0X15E8);
    // 0x8007D4BC: addu        $a0, $t2, $t3
    ctx->r4 = ADD32(ctx->r10, ctx->r11);
    // 0x8007D4C0: addu        $a1, $t4, $t5
    ctx->r5 = ADD32(ctx->r12, ctx->r13);
    // 0x8007D4C4: addiu       $a2, $zero, 0xA
    ctx->r6 = ADD32(0, 0XA);
    // 0x8007D4C8: jal         0x8006A140
    // 0x8007D4CC: sw          $a3, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r7;
    Libc_strncpy(rdram, ctx);
        goto after_7;
    // 0x8007D4CC: sw          $a3, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r7;
    after_7:
    // 0x8007D4D0: lw          $a3, 0x44($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X44);
L_8007D4D4:
    // 0x8007D4D4: lw          $t9, 0x34($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X34);
    // 0x8007D4D8: sll         $t0, $a3, 2
    ctx->r8 = S32(ctx->r7 << 2);
    // 0x8007D4DC: subu        $t0, $t0, $a3
    ctx->r8 = SUB32(ctx->r8, ctx->r7);
    // 0x8007D4E0: sll         $t8, $t9, 2
    ctx->r24 = S32(ctx->r25 << 2);
    // 0x8007D4E4: subu        $t8, $t8, $t9
    ctx->r24 = SUB32(ctx->r24, ctx->r25);
    // 0x8007D4E8: sll         $t8, $t8, 2
    ctx->r24 = S32(ctx->r24 << 2);
    // 0x8007D4EC: lui         $t6, 0x801B
    ctx->r14 = S32(0X801B << 16);
    // 0x8007D4F0: sll         $t1, $a3, 2
    ctx->r9 = S32(ctx->r7 << 2);
    // 0x8007D4F4: lui         $t2, 0x801B
    ctx->r10 = S32(0X801B << 16);
    // 0x8007D4F8: addiu       $t2, $t2, -0x13E8
    ctx->r10 = ADD32(ctx->r10, -0X13E8);
    // 0x8007D4FC: subu        $t1, $t1, $a3
    ctx->r9 = SUB32(ctx->r9, ctx->r7);
    // 0x8007D500: addiu       $t6, $t6, -0x15E8
    ctx->r14 = ADD32(ctx->r14, -0X15E8);
    // 0x8007D504: addu        $t7, $t8, $t0
    ctx->r15 = ADD32(ctx->r24, ctx->r8);
    // 0x8007D508: addu        $v1, $t7, $t6
    ctx->r3 = ADD32(ctx->r15, ctx->r14);
    // 0x8007D50C: addu        $a0, $t1, $t2
    ctx->r4 = ADD32(ctx->r9, ctx->r10);
    // 0x8007D510: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    // 0x8007D514: addiu       $a1, $zero, 0x3
    ctx->r5 = ADD32(0, 0X3);
L_8007D518:
    // 0x8007D518: lb          $t3, 0x38($a0)
    ctx->r11 = MEM_B(ctx->r4, 0X38);
    // 0x8007D51C: addiu       $v0, $v0, 0x1
    ctx->r2 = ADD32(ctx->r2, 0X1);
    // 0x8007D520: addiu       $v1, $v1, 0x1
    ctx->r3 = ADD32(ctx->r3, 0X1);
    // 0x8007D524: addiu       $a0, $a0, 0x1
    ctx->r4 = ADD32(ctx->r4, 0X1);
    // 0x8007D528: bne         $v0, $a1, L_8007D518
    if (ctx->r2 != ctx->r5) {
        // 0x8007D52C: sb          $t3, 0x37($v1)
        MEM_B(0X37, ctx->r3) = ctx->r11;
            goto L_8007D518;
    }
    // 0x8007D52C: sb          $t3, 0x37($v1)
    MEM_B(0X37, ctx->r3) = ctx->r11;
    // 0x8007D530: jal         0x8007B630
    // 0x8007D534: nop

    func_8007B630(rdram, ctx);
        goto after_8;
    // 0x8007D534: nop

    after_8:
    // 0x8007D538: jal         0x8007C31C
    // 0x8007D53C: nop

    func_8007C31C(rdram, ctx);
        goto after_9;
    // 0x8007D53C: nop

    after_9:
    // 0x8007D540: beq         $v0, $zero, L_8007D5F0
    if (ctx->r2 == 0) {
        // 0x8007D544: nop
    
            goto L_8007D5F0;
    }
    // 0x8007D544: nop

    // 0x8007D548: b           L_8007D604
    // 0x8007D54C: addiu       $v0, $zero, 0x5
    ctx->r2 = ADD32(0, 0X5);
        goto L_8007D604;
    // 0x8007D54C: addiu       $v0, $zero, 0x5
    ctx->r2 = ADD32(0, 0X5);
L_8007D550:
    // 0x8007D550: jal         0x8007CB68
    // 0x8007D554: nop

    func_8007CB68(rdram, ctx);
        goto after_10;
    // 0x8007D554: nop

    after_10:
    // 0x8007D558: jal         0x8007B630
    // 0x8007D55C: nop

    func_8007B630(rdram, ctx);
        goto after_11;
    // 0x8007D55C: nop

    after_11:
    // 0x8007D560: jal         0x8007B31C
    // 0x8007D564: nop

    func_8007B31C(rdram, ctx);
        goto after_12;
    // 0x8007D564: nop

    after_12:
    // 0x8007D568: lui         $a0, 0x801B
    ctx->r4 = S32(0X801B << 16);
    // 0x8007D56C: jal         0x8007BBF8
    // 0x8007D570: addiu       $a0, $a0, -0x15E8
    ctx->r4 = ADD32(ctx->r4, -0X15E8);
    Save_GenCheckSum(rdram, ctx);
        goto after_13;
    // 0x8007D570: addiu       $a0, $a0, -0x15E8
    ctx->r4 = ADD32(ctx->r4, -0X15E8);
    after_13:
    // 0x8007D574: lui         $a2, 0x801B
    ctx->r6 = S32(0X801B << 16);
    // 0x8007D578: addiu       $a2, $a2, -0x15E8
    ctx->r6 = ADD32(ctx->r6, -0X15E8);
    // 0x8007D57C: sh          $v0, 0x2($a2)
    MEM_H(0X2, ctx->r6) = ctx->r2;
    // 0x8007D580: lui         $t4, 0x800E
    ctx->r12 = S32(0X800E << 16);
    // 0x8007D584: lw          $t4, -0x7DA0($t4)
    ctx->r12 = MEM_W(ctx->r12, -0X7DA0);
    // 0x8007D588: lui         $a0, 0x8015
    ctx->r4 = S32(0X8015 << 16);
    // 0x8007D58C: addiu       $a0, $a0, 0x40D0
    ctx->r4 = ADD32(ctx->r4, 0X40D0);
    // 0x8007D590: beq         $t4, $zero, L_8007D5E8
    if (ctx->r12 == 0) {
        // 0x8007D594: or          $a1, $zero, $zero
        ctx->r5 = 0 | 0;
            goto L_8007D5E8;
    }
    // 0x8007D594: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x8007D598: jal         0x800C8410
    // 0x8007D59C: addiu       $a3, $zero, 0x10
    ctx->r7 = ADD32(0, 0X10);
    osEepromLongWrite_recomp(rdram, ctx);
        goto after_14;
    // 0x8007D59C: addiu       $a3, $zero, 0x10
    ctx->r7 = ADD32(0, 0X10);
    after_14:
    // 0x8007D5A0: beq         $v0, $zero, L_8007D5B0
    if (ctx->r2 == 0) {
        // 0x8007D5A4: lui         $a2, 0x801B
        ctx->r6 = S32(0X801B << 16);
            goto L_8007D5B0;
    }
    // 0x8007D5A4: lui         $a2, 0x801B
    ctx->r6 = S32(0X801B << 16);
    // 0x8007D5A8: b           L_8007D604
    // 0x8007D5AC: addiu       $v0, $zero, 0x3
    ctx->r2 = ADD32(0, 0X3);
        goto L_8007D604;
    // 0x8007D5AC: addiu       $v0, $zero, 0x3
    ctx->r2 = ADD32(0, 0X3);
L_8007D5B0:
    // 0x8007D5B0: lui         $t5, 0x801B
    ctx->r13 = S32(0X801B << 16);
    // 0x8007D5B4: addiu       $a2, $a2, -0x1588
    ctx->r6 = ADD32(ctx->r6, -0X1588);
    // 0x8007D5B8: addiu       $t5, $t5, -0x15E8
    ctx->r13 = ADD32(ctx->r13, -0X15E8);
    // 0x8007D5BC: subu        $a1, $a2, $t5
    ctx->r5 = SUB32(ctx->r6, ctx->r13);
    // 0x8007D5C0: srl         $t9, $a1, 3
    ctx->r25 = S32(U32(ctx->r5) >> 3);
    // 0x8007D5C4: lui         $a0, 0x8015
    ctx->r4 = S32(0X8015 << 16);
    // 0x8007D5C8: addiu       $a0, $a0, 0x40D0
    ctx->r4 = ADD32(ctx->r4, 0X40D0);
    // 0x8007D5CC: andi        $a1, $t9, 0xFF
    ctx->r5 = ctx->r25 & 0XFF;
    // 0x8007D5D0: jal         0x800C8410
    // 0x8007D5D4: addiu       $a3, $zero, 0x1A0
    ctx->r7 = ADD32(0, 0X1A0);
    osEepromLongWrite_recomp(rdram, ctx);
        goto after_15;
    // 0x8007D5D4: addiu       $a3, $zero, 0x1A0
    ctx->r7 = ADD32(0, 0X1A0);
    after_15:
    // 0x8007D5D8: beq         $v0, $zero, L_8007D5F0
    if (ctx->r2 == 0) {
        // 0x8007D5DC: nop
    
            goto L_8007D5F0;
    }
    // 0x8007D5DC: nop

    // 0x8007D5E0: b           L_8007D604
    // 0x8007D5E4: addiu       $v0, $zero, 0x5
    ctx->r2 = ADD32(0, 0X5);
        goto L_8007D604;
    // 0x8007D5E4: addiu       $v0, $zero, 0x5
    ctx->r2 = ADD32(0, 0X5);
L_8007D5E8:
    // 0x8007D5E8: b           L_8007D604
    // 0x8007D5EC: addiu       $v0, $zero, 0x5
    ctx->r2 = ADD32(0, 0X5);
        goto L_8007D604;
    // 0x8007D5EC: addiu       $v0, $zero, 0x5
    ctx->r2 = ADD32(0, 0X5);
L_8007D5F0:
    // 0x8007D5F0: b           L_8007D604
    // 0x8007D5F4: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
        goto L_8007D604;
    // 0x8007D5F4: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_8007D5F8:
    // 0x8007D5F8: b           L_8007D604
    // 0x8007D5FC: addiu       $v0, $zero, 0x2
    ctx->r2 = ADD32(0, 0X2);
        goto L_8007D604;
    // 0x8007D5FC: addiu       $v0, $zero, 0x2
    ctx->r2 = ADD32(0, 0X2);
L_8007D600:
    // 0x8007D600: addiu       $v0, $zero, 0x4
    ctx->r2 = ADD32(0, 0X4);
L_8007D604:
    // 0x8007D604: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
L_8007D608:
    // 0x8007D608: addiu       $sp, $sp, 0x48
    ctx->r29 = ADD32(ctx->r29, 0X48);
    // 0x8007D60C: jr          $ra
    // 0x8007D610: nop

    return;
    // 0x8007D610: nop

;}
RECOMP_FUNC void func_8007D614(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8007D614: addiu       $sp, $sp, -0x88
    ctx->r29 = ADD32(ctx->r29, -0X88);
    // 0x8007D618: sw          $ra, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r31;
    // 0x8007D61C: sw          $s1, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r17;
    // 0x8007D620: or          $s1, $a0, $zero
    ctx->r17 = ctx->r4 | 0;
    // 0x8007D624: sw          $s2, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r18;
    // 0x8007D628: jal         0x8007D110
    // 0x8007D62C: sw          $s0, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r16;
    Save_PfsIsPlug(rdram, ctx);
        goto after_0;
    // 0x8007D62C: sw          $s0, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r16;
    after_0:
    // 0x8007D630: beq         $v0, $zero, L_8007D640
    if (ctx->r2 == 0) {
        // 0x8007D634: slti        $at, $s1, 0x80
        ctx->r1 = SIGNED(ctx->r17) < 0X80 ? 1 : 0;
            goto L_8007D640;
    }
    // 0x8007D634: slti        $at, $s1, 0x80
    ctx->r1 = SIGNED(ctx->r17) < 0X80 ? 1 : 0;
    // 0x8007D638: b           L_8007DB2C
    // 0x8007D63C: lw          $ra, 0x34($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X34);
        goto L_8007DB2C;
    // 0x8007D63C: lw          $ra, 0x34($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X34);
L_8007D640:
    // 0x8007D640: bne         $at, $zero, L_8007D64C
    if (ctx->r1 != 0) {
        // 0x8007D644: lui         $s2, 0x4E57
        ctx->r18 = S32(0X4E57 << 16);
            goto L_8007D64C;
    }
    // 0x8007D644: lui         $s2, 0x4E57
    ctx->r18 = S32(0X4E57 << 16);
    // 0x8007D648: addiu       $s1, $s1, -0x80
    ctx->r17 = ADD32(ctx->r17, -0X80);
L_8007D64C:
    // 0x8007D64C: lui         $t6, 0x800E
    ctx->r14 = S32(0X800E << 16);
    // 0x8007D650: ori         $s2, $s2, 0x524A
    ctx->r18 = ctx->r18 | 0X524A;
    // 0x8007D654: addiu       $t6, $t6, -0x7D28
    ctx->r14 = ADD32(ctx->r14, -0X7D28);
    // 0x8007D658: lui         $a0, 0x801C
    ctx->r4 = S32(0X801C << 16);
    // 0x8007D65C: lui         $a3, 0x800E
    ctx->r7 = S32(0X800E << 16);
    // 0x8007D660: addiu       $t7, $sp, 0x6C
    ctx->r15 = ADD32(ctx->r29, 0X6C);
    // 0x8007D664: sw          $t7, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r15;
    // 0x8007D668: addiu       $a3, $a3, -0x7D18
    ctx->r7 = ADD32(ctx->r7, -0X7D18);
    // 0x8007D66C: addiu       $a0, $a0, 0x3AD0
    ctx->r4 = ADD32(ctx->r4, 0X3AD0);
    // 0x8007D670: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x8007D674: or          $a2, $s2, $zero
    ctx->r6 = ctx->r18 | 0;
    // 0x8007D678: jal         0x800C8A70
    // 0x8007D67C: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    osPfsFindFile_recomp(rdram, ctx);
        goto after_1;
    // 0x8007D67C: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    after_1:
    // 0x8007D680: sltiu       $at, $v0, 0x6
    ctx->r1 = ctx->r2 < 0X6 ? 1 : 0;
    // 0x8007D684: beq         $at, $zero, L_8007D778
    if (ctx->r1 == 0) {
        // 0x8007D688: sll         $t8, $v0, 2
        ctx->r24 = S32(ctx->r2 << 2);
            goto L_8007D778;
    }
    // 0x8007D688: sll         $t8, $v0, 2
    ctx->r24 = S32(ctx->r2 << 2);
    // 0x8007D68C: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x8007D690: addu        $at, $at, $t8
    gpr jr_addend_8007D698 = ctx->r24;
    ctx->r1 = ADD32(ctx->r1, ctx->r24);
    // 0x8007D694: lw          $t8, -0x5CE4($at)
    ctx->r24 = ADD32(ctx->r1, -0X5CE4);
    // 0x8007D698: jr          $t8
    // 0x8007D69C: nop

    switch (jr_addend_8007D698 >> 2) {
        case 0: goto L_8007D6A0; break;
        case 1: goto L_8007D778; break;
        case 2: goto L_8007D778; break;
        case 3: goto L_8007D778; break;
        case 4: goto L_8007D778; break;
        case 5: goto L_8007D70C; break;
        default: switch_error(__func__, 0x8007D698, 0x800EA31C);
    }
    // 0x8007D69C: nop

L_8007D6A0:
    // 0x8007D6A0: or          $s0, $zero, $zero
    ctx->r16 = 0 | 0;
L_8007D6A4:
    // 0x8007D6A4: jal         0x8007B930
    // 0x8007D6A8: nop

    func_8007B930(rdram, ctx);
        goto after_2;
    // 0x8007D6A8: nop

    after_2:
    // 0x8007D6AC: beq         $s1, $zero, L_8007D7E0
    if (ctx->r17 == 0) {
        // 0x8007D6B0: nop
    
            goto L_8007D7E0;
    }
    // 0x8007D6B0: nop

    // 0x8007D6B4: bne         $s0, $zero, L_8007D7E0
    if (ctx->r16 != 0) {
        // 0x8007D6B8: lui         $a0, 0x801C
        ctx->r4 = S32(0X801C << 16);
            goto L_8007D7E0;
    }
    // 0x8007D6B8: lui         $a0, 0x801C
    ctx->r4 = S32(0X801C << 16);
    // 0x8007D6BC: lui         $t6, 0x801B
    ctx->r14 = S32(0X801B << 16);
    // 0x8007D6C0: addiu       $t6, $t6, -0x13E8
    ctx->r14 = ADD32(ctx->r14, -0X13E8);
    // 0x8007D6C4: addiu       $t9, $zero, 0x200
    ctx->r25 = ADD32(0, 0X200);
    // 0x8007D6C8: sw          $t9, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r25;
    // 0x8007D6CC: sw          $t6, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r14;
    // 0x8007D6D0: addiu       $a0, $a0, 0x3AD0
    ctx->r4 = ADD32(ctx->r4, 0X3AD0);
    // 0x8007D6D4: lw          $a1, 0x6C($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X6C);
    // 0x8007D6D8: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x8007D6DC: jal         0x800C8EA0
    // 0x8007D6E0: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    osPfsReadWriteFile_recomp(rdram, ctx);
        goto after_3;
    // 0x8007D6E0: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_3:
    // 0x8007D6E4: addiu       $t7, $v0, -0x2
    ctx->r15 = ADD32(ctx->r2, -0X2);
    // 0x8007D6E8: sltiu       $at, $t7, 0x5
    ctx->r1 = ctx->r15 < 0X5 ? 1 : 0;
    // 0x8007D6EC: beq         $at, $zero, L_8007D788
    if (ctx->r1 == 0) {
        // 0x8007D6F0: lui         $v1, 0x801B
        ctx->r3 = S32(0X801B << 16);
            goto L_8007D788;
    }
    // 0x8007D6F0: lui         $v1, 0x801B
    ctx->r3 = S32(0X801B << 16);
    // 0x8007D6F4: sll         $t7, $t7, 2
    ctx->r15 = S32(ctx->r15 << 2);
    // 0x8007D6F8: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x8007D6FC: addu        $at, $at, $t7
    gpr jr_addend_8007D704 = ctx->r15;
    ctx->r1 = ADD32(ctx->r1, ctx->r15);
    // 0x8007D700: lw          $t7, -0x5CCC($at)
    ctx->r15 = ADD32(ctx->r1, -0X5CCC);
    // 0x8007D704: jr          $t7
    // 0x8007D708: nop

    switch (jr_addend_8007D704 >> 2) {
        case 0: goto L_8007D780; break;
        case 1: goto L_8007D780; break;
        case 2: goto L_8007D780; break;
        case 3: goto L_8007D780; break;
        case 4: goto L_8007D780; break;
        default: switch_error(__func__, 0x8007D704, 0x800EA334);
    }
    // 0x8007D708: nop

L_8007D70C:
    // 0x8007D70C: lui         $t8, 0x800E
    ctx->r24 = S32(0X800E << 16);
    // 0x8007D710: addiu       $t8, $t8, -0x7D28
    ctx->r24 = ADD32(ctx->r24, -0X7D28);
    // 0x8007D714: lui         $a0, 0x801C
    ctx->r4 = S32(0X801C << 16);
    // 0x8007D718: lui         $a3, 0x800E
    ctx->r7 = S32(0X800E << 16);
    // 0x8007D71C: addiu       $t9, $zero, 0x200
    ctx->r25 = ADD32(0, 0X200);
    // 0x8007D720: addiu       $t6, $sp, 0x6C
    ctx->r14 = ADD32(ctx->r29, 0X6C);
    // 0x8007D724: addiu       $s0, $zero, 0x1
    ctx->r16 = ADD32(0, 0X1);
    // 0x8007D728: sw          $t6, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r14;
    // 0x8007D72C: sw          $t9, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r25;
    // 0x8007D730: addiu       $a3, $a3, -0x7D18
    ctx->r7 = ADD32(ctx->r7, -0X7D18);
    // 0x8007D734: addiu       $a0, $a0, 0x3AD0
    ctx->r4 = ADD32(ctx->r4, 0X3AD0);
    // 0x8007D738: sw          $t8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r24;
    // 0x8007D73C: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x8007D740: jal         0x800C9210
    // 0x8007D744: or          $a2, $s2, $zero
    ctx->r6 = ctx->r18 | 0;
    osPfsAllocateFile_recomp(rdram, ctx);
        goto after_4;
    // 0x8007D744: or          $a2, $s2, $zero
    ctx->r6 = ctx->r18 | 0;
    after_4:
    // 0x8007D748: sltiu       $at, $v0, 0x9
    ctx->r1 = ctx->r2 < 0X9 ? 1 : 0;
    // 0x8007D74C: beq         $at, $zero, L_8007D770
    if (ctx->r1 == 0) {
        // 0x8007D750: sll         $t7, $v0, 2
        ctx->r15 = S32(ctx->r2 << 2);
            goto L_8007D770;
    }
    // 0x8007D750: sll         $t7, $v0, 2
    ctx->r15 = S32(ctx->r2 << 2);
    // 0x8007D754: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x8007D758: addu        $at, $at, $t7
    gpr jr_addend_8007D760 = ctx->r15;
    ctx->r1 = ADD32(ctx->r1, ctx->r15);
    // 0x8007D75C: lw          $t7, -0x5CB8($at)
    ctx->r15 = ADD32(ctx->r1, -0X5CB8);
    // 0x8007D760: jr          $t7
    // 0x8007D764: nop

    switch (jr_addend_8007D760 >> 2) {
        case 0: goto L_8007D6A4; break;
        case 1: goto L_8007D770; break;
        case 2: goto L_8007D770; break;
        case 3: goto L_8007D770; break;
        case 4: goto L_8007D770; break;
        case 5: goto L_8007D770; break;
        case 6: goto L_8007D770; break;
        case 7: goto L_8007D770; break;
        case 8: goto L_8007D768; break;
        default: switch_error(__func__, 0x8007D760, 0x800EA348);
    }
    // 0x8007D764: nop

L_8007D768:
    // 0x8007D768: b           L_8007DB28
    // 0x8007D76C: addiu       $v0, $zero, 0x3
    ctx->r2 = ADD32(0, 0X3);
        goto L_8007DB28;
    // 0x8007D76C: addiu       $v0, $zero, 0x3
    ctx->r2 = ADD32(0, 0X3);
L_8007D770:
    // 0x8007D770: b           L_8007DB28
    // 0x8007D774: addiu       $v0, $zero, 0x2
    ctx->r2 = ADD32(0, 0X2);
        goto L_8007DB28;
    // 0x8007D774: addiu       $v0, $zero, 0x2
    ctx->r2 = ADD32(0, 0X2);
L_8007D778:
    // 0x8007D778: b           L_8007DB28
    // 0x8007D77C: addiu       $v0, $zero, 0x2
    ctx->r2 = ADD32(0, 0X2);
        goto L_8007DB28;
    // 0x8007D77C: addiu       $v0, $zero, 0x2
    ctx->r2 = ADD32(0, 0X2);
L_8007D780:
    // 0x8007D780: b           L_8007DB28
    // 0x8007D784: addiu       $v0, $zero, 0x2
    ctx->r2 = ADD32(0, 0X2);
        goto L_8007DB28;
    // 0x8007D784: addiu       $v0, $zero, 0x2
    ctx->r2 = ADD32(0, 0X2);
L_8007D788:
    // 0x8007D788: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x8007D78C: lui         $a0, 0x800E
    ctx->r4 = S32(0X800E << 16);
    // 0x8007D790: addiu       $a0, $a0, -0x7D96
    ctx->r4 = ADD32(ctx->r4, -0X7D96);
    // 0x8007D794: addiu       $v0, $v0, -0x7D98
    ctx->r2 = ADD32(ctx->r2, -0X7D98);
    // 0x8007D798: addiu       $v1, $v1, -0x13E8
    ctx->r3 = ADD32(ctx->r3, -0X13E8);
L_8007D79C:
    // 0x8007D79C: lbu         $t8, 0x0($v1)
    ctx->r24 = MEM_BU(ctx->r3, 0X0);
    // 0x8007D7A0: lbu         $t9, 0x0($v0)
    ctx->r25 = MEM_BU(ctx->r2, 0X0);
    // 0x8007D7A4: addiu       $v0, $v0, 0x1
    ctx->r2 = ADD32(ctx->r2, 0X1);
    // 0x8007D7A8: beq         $t8, $t9, L_8007D7B4
    if (ctx->r24 == ctx->r25) {
        // 0x8007D7AC: nop
    
            goto L_8007D7B4;
    }
    // 0x8007D7AC: nop

    // 0x8007D7B0: addiu       $s0, $zero, 0x1
    ctx->r16 = ADD32(0, 0X1);
L_8007D7B4:
    // 0x8007D7B4: bne         $v0, $a0, L_8007D79C
    if (ctx->r2 != ctx->r4) {
        // 0x8007D7B8: addiu       $v1, $v1, 0x1
        ctx->r3 = ADD32(ctx->r3, 0X1);
            goto L_8007D79C;
    }
    // 0x8007D7B8: addiu       $v1, $v1, 0x1
    ctx->r3 = ADD32(ctx->r3, 0X1);
    // 0x8007D7BC: lui         $a0, 0x801B
    ctx->r4 = S32(0X801B << 16);
    // 0x8007D7C0: jal         0x8007BBF8
    // 0x8007D7C4: addiu       $a0, $a0, -0x13E8
    ctx->r4 = ADD32(ctx->r4, -0X13E8);
    Save_GenCheckSum(rdram, ctx);
        goto after_5;
    // 0x8007D7C4: addiu       $a0, $a0, -0x13E8
    ctx->r4 = ADD32(ctx->r4, -0X13E8);
    after_5:
    // 0x8007D7C8: lui         $a3, 0x801B
    ctx->r7 = S32(0X801B << 16);
    // 0x8007D7CC: addiu       $a3, $a3, -0x13E8
    ctx->r7 = ADD32(ctx->r7, -0X13E8);
    // 0x8007D7D0: lhu         $t6, 0x2($a3)
    ctx->r14 = MEM_HU(ctx->r7, 0X2);
    // 0x8007D7D4: beq         $v0, $t6, L_8007D7E0
    if (ctx->r2 == ctx->r14) {
        // 0x8007D7D8: nop
    
            goto L_8007D7E0;
    }
    // 0x8007D7D8: nop

    // 0x8007D7DC: addiu       $s0, $zero, 0x1
    ctx->r16 = ADD32(0, 0X1);
L_8007D7E0:
    // 0x8007D7E0: lui         $a3, 0x801B
    ctx->r7 = S32(0X801B << 16);
    // 0x8007D7E4: beq         $s0, $zero, L_8007D7FC
    if (ctx->r16 == 0) {
        // 0x8007D7E8: addiu       $a3, $a3, -0x13E8
        ctx->r7 = ADD32(ctx->r7, -0X13E8);
            goto L_8007D7FC;
    }
    // 0x8007D7E8: addiu       $a3, $a3, -0x13E8
    ctx->r7 = ADD32(ctx->r7, -0X13E8);
    // 0x8007D7EC: jal         0x8007B370
    // 0x8007D7F0: or          $a0, $a3, $zero
    ctx->r4 = ctx->r7 | 0;
    func_8007B370(rdram, ctx);
        goto after_6;
    // 0x8007D7F0: or          $a0, $a3, $zero
    ctx->r4 = ctx->r7 | 0;
    after_6:
    // 0x8007D7F4: lui         $a3, 0x801B
    ctx->r7 = S32(0X801B << 16);
    // 0x8007D7F8: addiu       $a3, $a3, -0x13E8
    ctx->r7 = ADD32(ctx->r7, -0X13E8);
L_8007D7FC:
    // 0x8007D7FC: sltiu       $at, $s1, 0x6
    ctx->r1 = ctx->r17 < 0X6 ? 1 : 0;
    // 0x8007D800: beq         $at, $zero, L_8007DAC0
    if (ctx->r1 == 0) {
        // 0x8007D804: sll         $t7, $s1, 2
        ctx->r15 = S32(ctx->r17 << 2);
            goto L_8007DAC0;
    }
    // 0x8007D804: sll         $t7, $s1, 2
    ctx->r15 = S32(ctx->r17 << 2);
    // 0x8007D808: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x8007D80C: addu        $at, $at, $t7
    gpr jr_addend_8007D814 = ctx->r15;
    ctx->r1 = ADD32(ctx->r1, ctx->r15);
    // 0x8007D810: lw          $t7, -0x5C94($at)
    ctx->r15 = ADD32(ctx->r1, -0X5C94);
    // 0x8007D814: jr          $t7
    // 0x8007D818: nop

    switch (jr_addend_8007D814 >> 2) {
        case 0: goto L_8007D81C; break;
        case 1: goto L_8007D864; break;
        case 2: goto L_8007D864; break;
        case 3: goto L_8007D864; break;
        case 4: goto L_8007D864; break;
        case 5: goto L_8007D8F0; break;
        default: switch_error(__func__, 0x8007D814, 0x800EA36C);
    }
    // 0x8007D818: nop

L_8007D81C:
    // 0x8007D81C: lui         $t8, 0x801B
    ctx->r24 = S32(0X801B << 16);
    // 0x8007D820: addiu       $t8, $t8, -0x15E8
    ctx->r24 = ADD32(ctx->r24, -0X15E8);
    // 0x8007D824: addiu       $t7, $t8, 0x1F8
    ctx->r15 = ADD32(ctx->r24, 0X1F8);
    // 0x8007D828: or          $t6, $a3, $zero
    ctx->r14 = ctx->r7 | 0;
L_8007D82C:
    // 0x8007D82C: lw          $at, 0x0($t8)
    ctx->r1 = MEM_W(ctx->r24, 0X0);
    // 0x8007D830: addiu       $t8, $t8, 0xC
    ctx->r24 = ADD32(ctx->r24, 0XC);
    // 0x8007D834: addiu       $t6, $t6, 0xC
    ctx->r14 = ADD32(ctx->r14, 0XC);
    // 0x8007D838: sw          $at, -0xC($t6)
    MEM_W(-0XC, ctx->r14) = ctx->r1;
    // 0x8007D83C: lw          $at, -0x8($t8)
    ctx->r1 = MEM_W(ctx->r24, -0X8);
    // 0x8007D840: sw          $at, -0x8($t6)
    MEM_W(-0X8, ctx->r14) = ctx->r1;
    // 0x8007D844: lw          $at, -0x4($t8)
    ctx->r1 = MEM_W(ctx->r24, -0X4);
    // 0x8007D848: bne         $t8, $t7, L_8007D82C
    if (ctx->r24 != ctx->r15) {
        // 0x8007D84C: sw          $at, -0x4($t6)
        MEM_W(-0X4, ctx->r14) = ctx->r1;
            goto L_8007D82C;
    }
    // 0x8007D84C: sw          $at, -0x4($t6)
    MEM_W(-0X4, ctx->r14) = ctx->r1;
    // 0x8007D850: lw          $at, 0x0($t8)
    ctx->r1 = MEM_W(ctx->r24, 0X0);
    // 0x8007D854: sw          $at, 0x0($t6)
    MEM_W(0X0, ctx->r14) = ctx->r1;
    // 0x8007D858: lw          $t7, 0x4($t8)
    ctx->r15 = MEM_W(ctx->r24, 0X4);
    // 0x8007D85C: b           L_8007DAC0
    // 0x8007D860: sw          $t7, 0x4($t6)
    MEM_W(0X4, ctx->r14) = ctx->r15;
        goto L_8007DAC0;
    // 0x8007D860: sw          $t7, 0x4($t6)
    MEM_W(0X4, ctx->r14) = ctx->r15;
L_8007D864:
    // 0x8007D864: sll         $v0, $s1, 2
    ctx->r2 = S32(ctx->r17 << 2);
    // 0x8007D868: addu        $v0, $v0, $s1
    ctx->r2 = ADD32(ctx->r2, ctx->r17);
    // 0x8007D86C: sll         $v0, $v0, 1
    ctx->r2 = S32(ctx->r2 << 1);
    // 0x8007D870: lui         $t7, 0x801B
    ctx->r15 = S32(0X801B << 16);
    // 0x8007D874: addiu       $t0, $s1, -0x1
    ctx->r8 = ADD32(ctx->r17, -0X1);
    // 0x8007D878: addiu       $t7, $t7, -0x15E8
    ctx->r15 = ADD32(ctx->r15, -0X15E8);
    // 0x8007D87C: addu        $a0, $a3, $v0
    ctx->r4 = ADD32(ctx->r7, ctx->r2);
    // 0x8007D880: addiu       $t9, $v0, 0x6
    ctx->r25 = ADD32(ctx->r2, 0X6);
    // 0x8007D884: addu        $a1, $t9, $t7
    ctx->r5 = ADD32(ctx->r25, ctx->r15);
    // 0x8007D888: addiu       $a0, $a0, 0x6
    ctx->r4 = ADD32(ctx->r4, 0X6);
    // 0x8007D88C: sw          $t0, 0x84($sp)
    MEM_W(0X84, ctx->r29) = ctx->r8;
    // 0x8007D890: jal         0x8006A140
    // 0x8007D894: addiu       $a2, $zero, 0xA
    ctx->r6 = ADD32(0, 0XA);
    Libc_strncpy(rdram, ctx);
        goto after_7;
    // 0x8007D894: addiu       $a2, $zero, 0xA
    ctx->r6 = ADD32(0, 0XA);
    after_7:
    // 0x8007D898: lw          $t0, 0x84($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X84);
    // 0x8007D89C: lui         $t6, 0x801B
    ctx->r14 = S32(0X801B << 16);
    // 0x8007D8A0: lui         $t7, 0x801B
    ctx->r15 = S32(0X801B << 16);
    // 0x8007D8A4: sll         $t8, $t0, 2
    ctx->r24 = S32(ctx->r8 << 2);
    // 0x8007D8A8: sll         $t9, $t0, 2
    ctx->r25 = S32(ctx->r8 << 2);
    // 0x8007D8AC: addiu       $t7, $t7, -0x15E8
    ctx->r15 = ADD32(ctx->r15, -0X15E8);
    // 0x8007D8B0: addiu       $t6, $t6, -0x13E8
    ctx->r14 = ADD32(ctx->r14, -0X13E8);
    // 0x8007D8B4: subu        $t9, $t9, $t0
    ctx->r25 = SUB32(ctx->r25, ctx->r8);
    // 0x8007D8B8: subu        $t8, $t8, $t0
    ctx->r24 = SUB32(ctx->r24, ctx->r8);
    // 0x8007D8BC: addu        $v0, $t8, $t6
    ctx->r2 = ADD32(ctx->r24, ctx->r14);
    // 0x8007D8C0: addu        $v1, $t9, $t7
    ctx->r3 = ADD32(ctx->r25, ctx->r15);
    // 0x8007D8C4: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    // 0x8007D8C8: addiu       $t2, $zero, 0x3
    ctx->r10 = ADD32(0, 0X3);
L_8007D8CC:
    // 0x8007D8CC: lb          $t8, 0x38($v1)
    ctx->r24 = MEM_B(ctx->r3, 0X38);
    // 0x8007D8D0: addiu       $a3, $a3, 0x1
    ctx->r7 = ADD32(ctx->r7, 0X1);
    // 0x8007D8D4: addiu       $v0, $v0, 0x1
    ctx->r2 = ADD32(ctx->r2, 0X1);
    // 0x8007D8D8: addiu       $v1, $v1, 0x1
    ctx->r3 = ADD32(ctx->r3, 0X1);
    // 0x8007D8DC: bne         $a3, $t2, L_8007D8CC
    if (ctx->r7 != ctx->r10) {
        // 0x8007D8E0: sb          $t8, 0x37($v0)
        MEM_B(0X37, ctx->r2) = ctx->r24;
            goto L_8007D8CC;
    }
    // 0x8007D8E0: sb          $t8, 0x37($v0)
    MEM_B(0X37, ctx->r2) = ctx->r24;
    // 0x8007D8E4: lui         $a3, 0x801B
    ctx->r7 = S32(0X801B << 16);
    // 0x8007D8E8: b           L_8007DAC0
    // 0x8007D8EC: addiu       $a3, $a3, -0x13E8
    ctx->r7 = ADD32(ctx->r7, -0X13E8);
        goto L_8007DAC0;
    // 0x8007D8EC: addiu       $a3, $a3, -0x13E8
    ctx->r7 = ADD32(ctx->r7, -0X13E8);
L_8007D8F0:
    // 0x8007D8F0: lui         $t6, 0x801B
    ctx->r14 = S32(0X801B << 16);
    // 0x8007D8F4: lui         $t9, 0x801B
    ctx->r25 = S32(0X801B << 16);
    // 0x8007D8F8: addiu       $t2, $t9, -0x15E8
    ctx->r10 = ADD32(ctx->r25, -0X15E8);
    // 0x8007D8FC: addiu       $t5, $t6, -0x13E8
    ctx->r13 = ADD32(ctx->r14, -0X13E8);
    // 0x8007D900: or          $ra, $t5, $zero
    ctx->r31 = ctx->r13 | 0;
    // 0x8007D904: or          $s1, $t5, $zero
    ctx->r17 = ctx->r13 | 0;
    // 0x8007D908: or          $t3, $t5, $zero
    ctx->r11 = ctx->r13 | 0;
    // 0x8007D90C: or          $s0, $t2, $zero
    ctx->r16 = ctx->r10 | 0;
    // 0x8007D910: or          $s2, $t2, $zero
    ctx->r18 = ctx->r10 | 0;
    // 0x8007D914: or          $t4, $t2, $zero
    ctx->r12 = ctx->r10 | 0;
L_8007D918:
    // 0x8007D918: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    // 0x8007D91C: or          $a1, $ra, $zero
    ctx->r5 = ctx->r31 | 0;
    // 0x8007D920: or          $a2, $s0, $zero
    ctx->r6 = ctx->r16 | 0;
    // 0x8007D924: or          $t0, $ra, $zero
    ctx->r8 = ctx->r31 | 0;
    // 0x8007D928: or          $t1, $s0, $zero
    ctx->r9 = ctx->r16 | 0;
L_8007D92C:
    // 0x8007D92C: lbu         $t7, 0x60($t1)
    ctx->r15 = MEM_BU(ctx->r9, 0X60);
    // 0x8007D930: lbu         $t8, 0x61($t1)
    ctx->r24 = MEM_BU(ctx->r9, 0X61);
    // 0x8007D934: addiu       $a0, $zero, 0x2
    ctx->r4 = ADD32(0, 0X2);
    // 0x8007D938: addu        $v1, $a2, $a0
    ctx->r3 = ADD32(ctx->r6, ctx->r4);
    // 0x8007D93C: addu        $v0, $a1, $a0
    ctx->r2 = ADD32(ctx->r5, ctx->r4);
    // 0x8007D940: sb          $t7, 0x60($t0)
    MEM_B(0X60, ctx->r8) = ctx->r15;
    // 0x8007D944: sb          $t8, 0x61($t0)
    MEM_B(0X61, ctx->r8) = ctx->r24;
    // 0x8007D948: lbu         $t8, 0x63($v1)
    ctx->r24 = MEM_BU(ctx->r3, 0X63);
    // 0x8007D94C: lbu         $t7, 0x62($v1)
    ctx->r15 = MEM_BU(ctx->r3, 0X62);
    // 0x8007D950: lbu         $t9, 0x61($v1)
    ctx->r25 = MEM_BU(ctx->r3, 0X61);
    // 0x8007D954: lbu         $t6, 0x60($v1)
    ctx->r14 = MEM_BU(ctx->r3, 0X60);
    // 0x8007D958: addiu       $a3, $a3, 0x1
    ctx->r7 = ADD32(ctx->r7, 0X1);
    // 0x8007D95C: slti        $at, $a3, 0x4
    ctx->r1 = SIGNED(ctx->r7) < 0X4 ? 1 : 0;
    // 0x8007D960: addiu       $a1, $a1, 0x6
    ctx->r5 = ADD32(ctx->r5, 0X6);
    // 0x8007D964: addiu       $a2, $a2, 0x6
    ctx->r6 = ADD32(ctx->r6, 0X6);
    // 0x8007D968: addiu       $t0, $t0, 0x6
    ctx->r8 = ADD32(ctx->r8, 0X6);
    // 0x8007D96C: addiu       $t1, $t1, 0x6
    ctx->r9 = ADD32(ctx->r9, 0X6);
    // 0x8007D970: sb          $t8, 0x63($v0)
    MEM_B(0X63, ctx->r2) = ctx->r24;
    // 0x8007D974: sb          $t7, 0x62($v0)
    MEM_B(0X62, ctx->r2) = ctx->r15;
    // 0x8007D978: sb          $t9, 0x61($v0)
    MEM_B(0X61, ctx->r2) = ctx->r25;
    // 0x8007D97C: bne         $at, $zero, L_8007D92C
    if (ctx->r1 != 0) {
        // 0x8007D980: sb          $t6, 0x60($v0)
        MEM_B(0X60, ctx->r2) = ctx->r14;
            goto L_8007D92C;
    }
    // 0x8007D980: sb          $t6, 0x60($v0)
    MEM_B(0X60, ctx->r2) = ctx->r14;
    // 0x8007D984: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    // 0x8007D988: or          $a1, $s1, $zero
    ctx->r5 = ctx->r17 | 0;
    // 0x8007D98C: or          $a2, $s2, $zero
    ctx->r6 = ctx->r18 | 0;
L_8007D990:
    // 0x8007D990: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    // 0x8007D994: or          $v0, $a1, $zero
    ctx->r2 = ctx->r5 | 0;
    // 0x8007D998: or          $v1, $a2, $zero
    ctx->r3 = ctx->r6 | 0;
L_8007D99C:
    // 0x8007D99C: lbu         $t6, 0x1A8($v1)
    ctx->r14 = MEM_BU(ctx->r3, 0X1A8);
    // 0x8007D9A0: addiu       $a0, $a0, 0x1
    ctx->r4 = ADD32(ctx->r4, 0X1);
    // 0x8007D9A4: slti        $at, $a0, 0x3
    ctx->r1 = SIGNED(ctx->r4) < 0X3 ? 1 : 0;
    // 0x8007D9A8: addiu       $v0, $v0, 0x1
    ctx->r2 = ADD32(ctx->r2, 0X1);
    // 0x8007D9AC: addiu       $v1, $v1, 0x1
    ctx->r3 = ADD32(ctx->r3, 0X1);
    // 0x8007D9B0: bne         $at, $zero, L_8007D99C
    if (ctx->r1 != 0) {
        // 0x8007D9B4: sb          $t6, 0x1A7($v0)
        MEM_B(0X1A7, ctx->r2) = ctx->r14;
            goto L_8007D99C;
    }
    // 0x8007D9B4: sb          $t6, 0x1A7($v0)
    MEM_B(0X1A7, ctx->r2) = ctx->r14;
    // 0x8007D9B8: addiu       $a3, $a3, 0x1
    ctx->r7 = ADD32(ctx->r7, 0X1);
    // 0x8007D9BC: slti        $at, $a3, 0x2
    ctx->r1 = SIGNED(ctx->r7) < 0X2 ? 1 : 0;
    // 0x8007D9C0: addiu       $a1, $a1, 0x3
    ctx->r5 = ADD32(ctx->r5, 0X3);
    // 0x8007D9C4: bne         $at, $zero, L_8007D990
    if (ctx->r1 != 0) {
        // 0x8007D9C8: addiu       $a2, $a2, 0x3
        ctx->r6 = ADD32(ctx->r6, 0X3);
            goto L_8007D990;
    }
    // 0x8007D9C8: addiu       $a2, $a2, 0x3
    ctx->r6 = ADD32(ctx->r6, 0X3);
    // 0x8007D9CC: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    // 0x8007D9D0: lbu         $t9, 0x1D8($t2)
    ctx->r25 = MEM_BU(ctx->r10, 0X1D8);
    // 0x8007D9D4: addu        $v1, $t4, $a0
    ctx->r3 = ADD32(ctx->r12, ctx->r4);
    // 0x8007D9D8: lbu         $t7, 0x1D8($v1)
    ctx->r15 = MEM_BU(ctx->r3, 0X1D8);
    // 0x8007D9DC: addu        $v0, $t3, $a0
    ctx->r2 = ADD32(ctx->r11, ctx->r4);
    // 0x8007D9E0: sb          $t9, 0x1D8($t5)
    MEM_B(0X1D8, ctx->r13) = ctx->r25;
    // 0x8007D9E4: sb          $t7, 0x1D8($v0)
    MEM_B(0X1D8, ctx->r2) = ctx->r15;
    // 0x8007D9E8: lui         $t7, 0x801B
    ctx->r15 = S32(0X801B << 16);
    // 0x8007D9EC: lbu         $t9, 0x1DB($v1)
    ctx->r25 = MEM_BU(ctx->r3, 0X1DB);
    // 0x8007D9F0: lbu         $t8, 0x1D9($v1)
    ctx->r24 = MEM_BU(ctx->r3, 0X1D9);
    // 0x8007D9F4: lbu         $t6, 0x1DA($v1)
    ctx->r14 = MEM_BU(ctx->r3, 0X1DA);
    // 0x8007D9F8: addiu       $t7, $t7, -0x15C0
    ctx->r15 = ADD32(ctx->r15, -0X15C0);
    // 0x8007D9FC: addiu       $t2, $t2, 0x5
    ctx->r10 = ADD32(ctx->r10, 0X5);
    // 0x8007DA00: sltu        $at, $t2, $t7
    ctx->r1 = ctx->r10 < ctx->r15 ? 1 : 0;
    // 0x8007DA04: addiu       $t3, $t3, 0x5
    ctx->r11 = ADD32(ctx->r11, 0X5);
    // 0x8007DA08: addiu       $t4, $t4, 0x5
    ctx->r12 = ADD32(ctx->r12, 0X5);
    // 0x8007DA0C: addiu       $ra, $ra, 0x18
    ctx->r31 = ADD32(ctx->r31, 0X18);
    // 0x8007DA10: addiu       $s0, $s0, 0x18
    ctx->r16 = ADD32(ctx->r16, 0X18);
    // 0x8007DA14: addiu       $s1, $s1, 0x6
    ctx->r17 = ADD32(ctx->r17, 0X6);
    // 0x8007DA18: addiu       $s2, $s2, 0x6
    ctx->r18 = ADD32(ctx->r18, 0X6);
    // 0x8007DA1C: addiu       $t5, $t5, 0x5
    ctx->r13 = ADD32(ctx->r13, 0X5);
    // 0x8007DA20: sb          $t9, 0x1DB($v0)
    MEM_B(0X1DB, ctx->r2) = ctx->r25;
    // 0x8007DA24: sb          $t8, 0x1D9($v0)
    MEM_B(0X1D9, ctx->r2) = ctx->r24;
    // 0x8007DA28: bne         $at, $zero, L_8007D918
    if (ctx->r1 != 0) {
        // 0x8007DA2C: sb          $t6, 0x1DA($v0)
        MEM_B(0X1DA, ctx->r2) = ctx->r14;
            goto L_8007D918;
    }
    // 0x8007DA2C: sb          $t6, 0x1DA($v0)
    MEM_B(0X1DA, ctx->r2) = ctx->r14;
    // 0x8007DA30: lui         $t4, 0x801B
    ctx->r12 = S32(0X801B << 16);
    // 0x8007DA34: lui         $t3, 0x801B
    ctx->r11 = S32(0X801B << 16);
    // 0x8007DA38: lui         $t5, 0x801B
    ctx->r13 = S32(0X801B << 16);
    // 0x8007DA3C: addiu       $t5, $t5, -0x1561
    ctx->r13 = ADD32(ctx->r13, -0X1561);
    // 0x8007DA40: addiu       $t3, $t3, -0x15E8
    ctx->r11 = ADD32(ctx->r11, -0X15E8);
    // 0x8007DA44: addiu       $t4, $t4, -0x13E8
    ctx->r12 = ADD32(ctx->r12, -0X13E8);
    // 0x8007DA48: addiu       $t2, $zero, 0x3
    ctx->r10 = ADD32(0, 0X3);
L_8007DA4C:
    // 0x8007DA4C: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    // 0x8007DA50: or          $a1, $t4, $zero
    ctx->r5 = ctx->r12 | 0;
    // 0x8007DA54: or          $a2, $t3, $zero
    ctx->r6 = ctx->r11 | 0;
    // 0x8007DA58: or          $t0, $t4, $zero
    ctx->r8 = ctx->r12 | 0;
    // 0x8007DA5C: or          $t1, $t3, $zero
    ctx->r9 = ctx->r11 | 0;
L_8007DA60:
    // 0x8007DA60: lbu         $t8, 0x120($t1)
    ctx->r24 = MEM_BU(ctx->r9, 0X120);
    // 0x8007DA64: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    // 0x8007DA68: addu        $v1, $a2, $a0
    ctx->r3 = ADD32(ctx->r6, ctx->r4);
    // 0x8007DA6C: addu        $v0, $a1, $a0
    ctx->r2 = ADD32(ctx->r5, ctx->r4);
    // 0x8007DA70: sb          $t8, 0x120($t0)
    MEM_B(0X120, ctx->r8) = ctx->r24;
    // 0x8007DA74: lbu         $t8, 0x123($v1)
    ctx->r24 = MEM_BU(ctx->r3, 0X123);
    // 0x8007DA78: lbu         $t9, 0x121($v1)
    ctx->r25 = MEM_BU(ctx->r3, 0X121);
    // 0x8007DA7C: lbu         $t7, 0x122($v1)
    ctx->r15 = MEM_BU(ctx->r3, 0X122);
    // 0x8007DA80: lbu         $t6, 0x120($v1)
    ctx->r14 = MEM_BU(ctx->r3, 0X120);
    // 0x8007DA84: addiu       $a3, $a3, 0x1
    ctx->r7 = ADD32(ctx->r7, 0X1);
    // 0x8007DA88: addiu       $a1, $a1, 0x5
    ctx->r5 = ADD32(ctx->r5, 0X5);
    // 0x8007DA8C: addiu       $a2, $a2, 0x5
    ctx->r6 = ADD32(ctx->r6, 0X5);
    // 0x8007DA90: addiu       $t0, $t0, 0x5
    ctx->r8 = ADD32(ctx->r8, 0X5);
    // 0x8007DA94: addiu       $t1, $t1, 0x5
    ctx->r9 = ADD32(ctx->r9, 0X5);
    // 0x8007DA98: sb          $t8, 0x123($v0)
    MEM_B(0X123, ctx->r2) = ctx->r24;
    // 0x8007DA9C: sb          $t9, 0x121($v0)
    MEM_B(0X121, ctx->r2) = ctx->r25;
    // 0x8007DAA0: sb          $t7, 0x122($v0)
    MEM_B(0X122, ctx->r2) = ctx->r15;
    // 0x8007DAA4: bne         $a3, $t2, L_8007DA60
    if (ctx->r7 != ctx->r10) {
        // 0x8007DAA8: sb          $t6, 0x120($v0)
        MEM_B(0X120, ctx->r2) = ctx->r14;
            goto L_8007DA60;
    }
    // 0x8007DAA8: sb          $t6, 0x120($v0)
    MEM_B(0X120, ctx->r2) = ctx->r14;
    // 0x8007DAAC: addiu       $t3, $t3, 0xF
    ctx->r11 = ADD32(ctx->r11, 0XF);
    // 0x8007DAB0: bne         $t3, $t5, L_8007DA4C
    if (ctx->r11 != ctx->r13) {
        // 0x8007DAB4: addiu       $t4, $t4, 0xF
        ctx->r12 = ADD32(ctx->r12, 0XF);
            goto L_8007DA4C;
    }
    // 0x8007DAB4: addiu       $t4, $t4, 0xF
    ctx->r12 = ADD32(ctx->r12, 0XF);
    // 0x8007DAB8: lui         $a3, 0x801B
    ctx->r7 = S32(0X801B << 16);
    // 0x8007DABC: addiu       $a3, $a3, -0x13E8
    ctx->r7 = ADD32(ctx->r7, -0X13E8);
L_8007DAC0:
    // 0x8007DAC0: jal         0x8007BBF8
    // 0x8007DAC4: or          $a0, $a3, $zero
    ctx->r4 = ctx->r7 | 0;
    Save_GenCheckSum(rdram, ctx);
        goto after_8;
    // 0x8007DAC4: or          $a0, $a3, $zero
    ctx->r4 = ctx->r7 | 0;
    after_8:
    // 0x8007DAC8: lui         $t9, 0x801B
    ctx->r25 = S32(0X801B << 16);
    // 0x8007DACC: lui         $at, 0x801B
    ctx->r1 = S32(0X801B << 16);
    // 0x8007DAD0: addiu       $t9, $t9, -0x13E8
    ctx->r25 = ADD32(ctx->r25, -0X13E8);
    // 0x8007DAD4: lui         $a0, 0x801C
    ctx->r4 = S32(0X801C << 16);
    // 0x8007DAD8: addiu       $t6, $zero, 0x200
    ctx->r14 = ADD32(0, 0X200);
    // 0x8007DADC: sh          $v0, -0x13E6($at)
    MEM_H(-0X13E6, ctx->r1) = ctx->r2;
    // 0x8007DAE0: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x8007DAE4: addiu       $a0, $a0, 0x3AD0
    ctx->r4 = ADD32(ctx->r4, 0X3AD0);
    // 0x8007DAE8: sw          $t9, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r25;
    // 0x8007DAEC: lw          $a1, 0x6C($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X6C);
    // 0x8007DAF0: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    // 0x8007DAF4: jal         0x800C8EA0
    // 0x8007DAF8: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    osPfsReadWriteFile_recomp(rdram, ctx);
        goto after_9;
    // 0x8007DAF8: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_9:
    // 0x8007DAFC: sltiu       $at, $v0, 0x7
    ctx->r1 = ctx->r2 < 0X7 ? 1 : 0;
    // 0x8007DB00: beq         $at, $zero, L_8007DB24
    if (ctx->r1 == 0) {
        // 0x8007DB04: sll         $t7, $v0, 2
        ctx->r15 = S32(ctx->r2 << 2);
            goto L_8007DB24;
    }
    // 0x8007DB04: sll         $t7, $v0, 2
    ctx->r15 = S32(ctx->r2 << 2);
    // 0x8007DB08: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x8007DB0C: addu        $at, $at, $t7
    gpr jr_addend_8007DB14 = ctx->r15;
    ctx->r1 = ADD32(ctx->r1, ctx->r15);
    // 0x8007DB10: lw          $t7, -0x5C7C($at)
    ctx->r15 = ADD32(ctx->r1, -0X5C7C);
    // 0x8007DB14: jr          $t7
    // 0x8007DB18: nop

    switch (jr_addend_8007DB14 >> 2) {
        case 0: goto L_8007DB1C; break;
        case 1: goto L_8007DB24; break;
        case 2: goto L_8007DB24; break;
        case 3: goto L_8007DB24; break;
        case 4: goto L_8007DB24; break;
        case 5: goto L_8007DB24; break;
        case 6: goto L_8007DB24; break;
        default: switch_error(__func__, 0x8007DB14, 0x800EA384);
    }
    // 0x8007DB18: nop

L_8007DB1C:
    // 0x8007DB1C: b           L_8007DB28
    // 0x8007DB20: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
        goto L_8007DB28;
    // 0x8007DB20: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_8007DB24:
    // 0x8007DB24: addiu       $v0, $zero, 0x2
    ctx->r2 = ADD32(0, 0X2);
L_8007DB28:
    // 0x8007DB28: lw          $ra, 0x34($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X34);
L_8007DB2C:
    // 0x8007DB2C: lw          $s0, 0x28($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X28);
    // 0x8007DB30: lw          $s1, 0x2C($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X2C);
    // 0x8007DB34: lw          $s2, 0x30($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X30);
    // 0x8007DB38: jr          $ra
    // 0x8007DB3C: addiu       $sp, $sp, 0x88
    ctx->r29 = ADD32(ctx->r29, 0X88);
    return;
    // 0x8007DB3C: addiu       $sp, $sp, 0x88
    ctx->r29 = ADD32(ctx->r29, 0X88);
;}
RECOMP_FUNC void Save_PfsDeleteFile(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8007DB40: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x8007DB44: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x8007DB48: jal         0x8007D110
    // 0x8007DB4C: nop

    Save_PfsIsPlug(rdram, ctx);
        goto after_0;
    // 0x8007DB4C: nop

    after_0:
    // 0x8007DB50: beq         $v0, $zero, L_8007DB60
    if (ctx->r2 == 0) {
        // 0x8007DB54: lui         $a0, 0x801C
        ctx->r4 = S32(0X801C << 16);
            goto L_8007DB60;
    }
    // 0x8007DB54: lui         $a0, 0x801C
    ctx->r4 = S32(0X801C << 16);
    // 0x8007DB58: b           L_8007DBB4
    // 0x8007DB5C: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
        goto L_8007DBB4;
    // 0x8007DB5C: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
L_8007DB60:
    // 0x8007DB60: lui         $t6, 0x800E
    ctx->r14 = S32(0X800E << 16);
    // 0x8007DB64: addiu       $t6, $t6, -0x7D28
    ctx->r14 = ADD32(ctx->r14, -0X7D28);
    // 0x8007DB68: lui         $a2, 0x4E57
    ctx->r6 = S32(0X4E57 << 16);
    // 0x8007DB6C: lui         $a3, 0x800E
    ctx->r7 = S32(0X800E << 16);
    // 0x8007DB70: addiu       $a3, $a3, -0x7D18
    ctx->r7 = ADD32(ctx->r7, -0X7D18);
    // 0x8007DB74: ori         $a2, $a2, 0x524A
    ctx->r6 = ctx->r6 | 0X524A;
    // 0x8007DB78: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x8007DB7C: addiu       $a0, $a0, 0x3AD0
    ctx->r4 = ADD32(ctx->r4, 0X3AD0);
    // 0x8007DB80: jal         0x800C98B0
    // 0x8007DB84: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    osPfsDeleteFile_recomp(rdram, ctx);
        goto after_1;
    // 0x8007DB84: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    after_1:
    // 0x8007DB88: beq         $v0, $zero, L_8007DBA0
    if (ctx->r2 == 0) {
        // 0x8007DB8C: addiu       $at, $zero, 0x5
        ctx->r1 = ADD32(0, 0X5);
            goto L_8007DBA0;
    }
    // 0x8007DB8C: addiu       $at, $zero, 0x5
    ctx->r1 = ADD32(0, 0X5);
    // 0x8007DB90: beq         $v0, $at, L_8007DBA8
    if (ctx->r2 == ctx->r1) {
        // 0x8007DB94: nop
    
            goto L_8007DBA8;
    }
    // 0x8007DB94: nop

    // 0x8007DB98: b           L_8007DBB0
    // 0x8007DB9C: addiu       $v0, $zero, 0x2
    ctx->r2 = ADD32(0, 0X2);
        goto L_8007DBB0;
    // 0x8007DB9C: addiu       $v0, $zero, 0x2
    ctx->r2 = ADD32(0, 0X2);
L_8007DBA0:
    // 0x8007DBA0: b           L_8007DBB0
    // 0x8007DBA4: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
        goto L_8007DBB0;
    // 0x8007DBA4: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_8007DBA8:
    // 0x8007DBA8: b           L_8007DBB0
    // 0x8007DBAC: addiu       $v0, $zero, 0x4
    ctx->r2 = ADD32(0, 0X4);
        goto L_8007DBB0;
    // 0x8007DBAC: addiu       $v0, $zero, 0x4
    ctx->r2 = ADD32(0, 0X4);
L_8007DBB0:
    // 0x8007DBB0: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
L_8007DBB4:
    // 0x8007DBB4: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x8007DBB8: jr          $ra
    // 0x8007DBBC: nop

    return;
    // 0x8007DBBC: nop

;}
RECOMP_FUNC void func_8007DBC0(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8007DBC0: addiu       $sp, $sp, -0x50
    ctx->r29 = ADD32(ctx->r29, -0X50);
    // 0x8007DBC4: lui         $v1, 0x801C
    ctx->r3 = S32(0X801C << 16);
    // 0x8007DBC8: lw          $v1, -0x4EE0($v1)
    ctx->r3 = MEM_W(ctx->r3, -0X4EE0);
    // 0x8007DBCC: sw          $ra, 0x4C($sp)
    MEM_W(0X4C, ctx->r29) = ctx->r31;
    // 0x8007DBD0: sw          $s1, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r17;
    // 0x8007DBD4: sw          $s0, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r16;
    // 0x8007DBD8: sdc1        $f30, 0x38($sp)
    CHECK_FR(ctx, 30);
    SD(ctx->f30.u64, 0X38, ctx->r29);
    // 0x8007DBDC: sdc1        $f28, 0x30($sp)
    CHECK_FR(ctx, 28);
    SD(ctx->f28.u64, 0X30, ctx->r29);
    // 0x8007DBE0: sdc1        $f26, 0x28($sp)
    CHECK_FR(ctx, 26);
    SD(ctx->f26.u64, 0X28, ctx->r29);
    // 0x8007DBE4: sdc1        $f24, 0x20($sp)
    CHECK_FR(ctx, 24);
    SD(ctx->f24.u64, 0X20, ctx->r29);
    // 0x8007DBE8: sdc1        $f22, 0x18($sp)
    CHECK_FR(ctx, 22);
    SD(ctx->f22.u64, 0X18, ctx->r29);
    // 0x8007DBEC: blez        $v1, L_8007DD80
    if (SIGNED(ctx->r3) <= 0) {
        // 0x8007DBF0: sdc1        $f20, 0x10($sp)
        CHECK_FR(ctx, 20);
    SD(ctx->f20.u64, 0X10, ctx->r29);
            goto L_8007DD80;
    }
    // 0x8007DBF0: sdc1        $f20, 0x10($sp)
    CHECK_FR(ctx, 20);
    SD(ctx->f20.u64, 0X10, ctx->r29);
    // 0x8007DBF4: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x8007DBF8: ldc1        $f30, -0x5C60($at)
    CHECK_FR(ctx, 30);
    ctx->f30.u64 = LD(ctx->r1, -0X5C60);
    // 0x8007DBFC: lui         $at, 0x41F0
    ctx->r1 = S32(0X41F0 << 16);
    // 0x8007DC00: mtc1        $at, $f28
    ctx->f28.u32l = ctx->r1;
    // 0x8007DC04: lui         $at, 0x4220
    ctx->r1 = S32(0X4220 << 16);
    // 0x8007DC08: mtc1        $at, $f26
    ctx->f26.u32l = ctx->r1;
    // 0x8007DC0C: lui         $at, 0x4008
    ctx->r1 = S32(0X4008 << 16);
    // 0x8007DC10: mtc1        $at, $f25
    ctx->f_odd[(25 - 1) * 2] = ctx->r1;
    // 0x8007DC14: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x8007DC18: ldc1        $f22, -0x5C58($at)
    CHECK_FR(ctx, 22);
    ctx->f22.u64 = LD(ctx->r1, -0X5C58);
    // 0x8007DC1C: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x8007DC20: lui         $s0, 0x801B
    ctx->r16 = S32(0X801B << 16);
    // 0x8007DC24: mtc1        $zero, $f24
    ctx->f24.u32l = 0;
    // 0x8007DC28: addiu       $s0, $s0, -0x11E0
    ctx->r16 = ADD32(ctx->r16, -0X11E0);
    // 0x8007DC2C: ldc1        $f20, -0x5C50($at)
    CHECK_FR(ctx, 20);
    ctx->f20.u64 = LD(ctx->r1, -0X5C50);
    // 0x8007DC30: lw          $t6, 0x9C($s0)
    ctx->r14 = MEM_W(ctx->r16, 0X9C);
L_8007DC34:
    // 0x8007DC34: sll         $t8, $v1, 6
    ctx->r24 = S32(ctx->r3 << 6);
    // 0x8007DC38: addu        $t8, $t8, $v1
    ctx->r24 = ADD32(ctx->r24, ctx->r3);
    // 0x8007DC3C: bne         $t6, $zero, L_8007DC4C
    if (ctx->r14 != 0) {
        // 0x8007DC40: sll         $t8, $t8, 2
        ctx->r24 = S32(ctx->r24 << 2);
            goto L_8007DC4C;
    }
    // 0x8007DC40: sll         $t8, $t8, 2
    ctx->r24 = S32(ctx->r24 << 2);
    // 0x8007DC44: lw          $t7, 0xC4($s0)
    ctx->r15 = MEM_W(ctx->r16, 0XC4);
    // 0x8007DC48: bne         $t7, $zero, L_8007DC5C
    if (ctx->r15 != 0) {
        // 0x8007DC4C: lui         $t9, 0x801B
        ctx->r25 = S32(0X801B << 16);
            goto L_8007DC5C;
    }
L_8007DC4C:
    // 0x8007DC4C: lui         $t9, 0x801B
    ctx->r25 = S32(0X801B << 16);
    // 0x8007DC50: addiu       $t9, $t9, -0x11E0
    ctx->r25 = ADD32(ctx->r25, -0X11E0);
    // 0x8007DC54: b           L_8007DD70
    // 0x8007DC58: addu        $v0, $t8, $t9
    ctx->r2 = ADD32(ctx->r24, ctx->r25);
        goto L_8007DD70;
    // 0x8007DC58: addu        $v0, $t8, $t9
    ctx->r2 = ADD32(ctx->r24, ctx->r25);
L_8007DC5C:
    // 0x8007DC5C: lwc1        $f12, 0x0($s0)
    ctx->f12.u32l = MEM_W(ctx->r16, 0X0);
    // 0x8007DC60: lwc1        $f10, 0x24($s0)
    ctx->f10.u32l = MEM_W(ctx->r16, 0X24);
    // 0x8007DC64: lwc1        $f4, 0x3C($s0)
    ctx->f4.u32l = MEM_W(ctx->r16, 0X3C);
    // 0x8007DC68: lwc1        $f14, 0x8($s0)
    ctx->f14.u32l = MEM_W(ctx->r16, 0X8);
    // 0x8007DC6C: sub.s       $f16, $f10, $f12
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f16.fl = ctx->f10.fl - ctx->f12.fl;
    // 0x8007DC70: cvt.d.s     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f4.fl); 
    ctx->f6.d = CVT_D_S(ctx->f4.fl);
    // 0x8007DC74: cvt.d.s     $f18, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f16.fl); 
    ctx->f18.d = CVT_D_S(ctx->f16.fl);
    // 0x8007DC78: mul.d       $f8, $f6, $f20
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f6.d); NAN_CHECK(ctx->f20.d); 
    ctx->f8.d = MUL_D(ctx->f6.d, ctx->f20.d);
    // 0x8007DC7C: lwc1        $f16, 0x44($s0)
    ctx->f16.u32l = MEM_W(ctx->r16, 0X44);
    // 0x8007DC80: mul.d       $f4, $f22, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f22.d); NAN_CHECK(ctx->f18.d); 
    ctx->f4.d = MUL_D(ctx->f22.d, ctx->f18.d);
    // 0x8007DC84: cvt.d.s     $f18, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f16.fl); 
    ctx->f18.d = CVT_D_S(ctx->f16.fl);
    // 0x8007DC88: add.d       $f6, $f8, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f8.d); NAN_CHECK(ctx->f4.d); 
    ctx->f6.d = ctx->f8.d + ctx->f4.d;
    // 0x8007DC8C: lwc1        $f4, 0x28($s0)
    ctx->f4.u32l = MEM_W(ctx->r16, 0X28);
    // 0x8007DC90: mul.d       $f8, $f18, $f20
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f18.d); NAN_CHECK(ctx->f20.d); 
    ctx->f8.d = MUL_D(ctx->f18.d, ctx->f20.d);
    // 0x8007DC94: cvt.s.d     $f10, $f6
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f6.d); 
    ctx->f10.fl = CVT_S_D(ctx->f6.d);
    // 0x8007DC98: sub.s       $f6, $f4, $f14
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f6.fl = ctx->f4.fl - ctx->f14.fl;
    // 0x8007DC9C: swc1        $f10, 0x3C($s0)
    MEM_W(0X3C, ctx->r16) = ctx->f10.u32l;
    // 0x8007DCA0: cvt.d.s     $f10, $f6
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f6.fl); 
    ctx->f10.d = CVT_D_S(ctx->f6.fl);
    // 0x8007DCA4: lwc1        $f6, 0x40($s0)
    ctx->f6.u32l = MEM_W(ctx->r16, 0X40);
    // 0x8007DCA8: mul.d       $f16, $f22, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f22.d); NAN_CHECK(ctx->f10.d); 
    ctx->f16.d = MUL_D(ctx->f22.d, ctx->f10.d);
    // 0x8007DCAC: cvt.d.s     $f10, $f6
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f6.fl); 
    ctx->f10.d = CVT_D_S(ctx->f6.fl);
    // 0x8007DCB0: add.d       $f18, $f8, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f8.d); NAN_CHECK(ctx->f16.d); 
    ctx->f18.d = ctx->f8.d + ctx->f16.d;
    // 0x8007DCB4: mul.d       $f8, $f10, $f20
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f10.d); NAN_CHECK(ctx->f20.d); 
    ctx->f8.d = MUL_D(ctx->f10.d, ctx->f20.d);
    // 0x8007DCB8: cvt.s.d     $f4, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f18.d); 
    ctx->f4.fl = CVT_S_D(ctx->f18.d);
    // 0x8007DCBC: sub.d       $f16, $f8, $f24
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 24);
    NAN_CHECK(ctx->f8.d); NAN_CHECK(ctx->f24.d); 
    ctx->f16.d = ctx->f8.d - ctx->f24.d;
    // 0x8007DCC0: swc1        $f4, 0x44($s0)
    MEM_W(0X44, ctx->r16) = ctx->f4.u32l;
    // 0x8007DCC4: cvt.s.d     $f18, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f16.d); 
    ctx->f18.fl = CVT_S_D(ctx->f16.d);
    // 0x8007DCC8: jal         0x8004D30C
    // 0x8007DCCC: swc1        $f18, 0x40($s0)
    MEM_W(0X40, ctx->r16) = ctx->f18.u32l;
    func_8004D30C(rdram, ctx);
        goto after_0;
    // 0x8007DCCC: swc1        $f18, 0x40($s0)
    MEM_W(0X40, ctx->r16) = ctx->f18.u32l;
    after_0:
    // 0x8007DCD0: add.s       $f4, $f0, $f26
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 26);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f26.fl); 
    ctx->f4.fl = ctx->f0.fl + ctx->f26.fl;
    // 0x8007DCD4: lwc1        $f12, 0x4($s0)
    ctx->f12.u32l = MEM_W(ctx->r16, 0X4);
    // 0x8007DCD8: mtc1        $zero, $f6
    ctx->f6.u32l = 0;
    // 0x8007DCDC: sub.s       $f2, $f4, $f12
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f2.fl = ctx->f4.fl - ctx->f12.fl;
    // 0x8007DCE0: c.lt.s      $f6, $f2
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 2);
    c1cs = ctx->f6.fl < ctx->f2.fl;
    // 0x8007DCE4: nop

    // 0x8007DCE8: bc1fl       L_8007DD28
    if (!c1cs) {
        // 0x8007DCEC: lwc1        $f10, 0x0($s0)
        ctx->f10.u32l = MEM_W(ctx->r16, 0X0);
            goto L_8007DD28;
    }
    goto skip_0;
    // 0x8007DCEC: lwc1        $f10, 0x0($s0)
    ctx->f10.u32l = MEM_W(ctx->r16, 0X0);
    skip_0:
    // 0x8007DCF0: c.lt.s      $f28, $f2
    CHECK_FR(ctx, 28);
    CHECK_FR(ctx, 2);
    c1cs = ctx->f28.fl < ctx->f2.fl;
    // 0x8007DCF4: nop

    // 0x8007DCF8: bc1fl       L_8007DD08
    if (!c1cs) {
        // 0x8007DCFC: cvt.d.s     $f16, $f2
        CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f2.fl); 
    ctx->f16.d = CVT_D_S(ctx->f2.fl);
            goto L_8007DD08;
    }
    goto skip_1;
    // 0x8007DCFC: cvt.d.s     $f16, $f2
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f2.fl); 
    ctx->f16.d = CVT_D_S(ctx->f2.fl);
    skip_1:
    // 0x8007DD00: mov.s       $f2, $f28
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 28);
    ctx->f2.fl = ctx->f28.fl;
    // 0x8007DD04: cvt.d.s     $f16, $f2
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f2.fl); 
    ctx->f16.d = CVT_D_S(ctx->f2.fl);
L_8007DD08:
    // 0x8007DD08: lwc1        $f10, 0x40($s0)
    ctx->f10.u32l = MEM_W(ctx->r16, 0X40);
    // 0x8007DD0C: mul.d       $f18, $f30, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 30);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f30.d); NAN_CHECK(ctx->f16.d); 
    ctx->f18.d = MUL_D(ctx->f30.d, ctx->f16.d);
    // 0x8007DD10: lwc1        $f12, 0x4($s0)
    ctx->f12.u32l = MEM_W(ctx->r16, 0X4);
    // 0x8007DD14: cvt.d.s     $f8, $f10
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f10.fl); 
    ctx->f8.d = CVT_D_S(ctx->f10.fl);
    // 0x8007DD18: add.d       $f4, $f8, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f8.d); NAN_CHECK(ctx->f18.d); 
    ctx->f4.d = ctx->f8.d + ctx->f18.d;
    // 0x8007DD1C: cvt.s.d     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f4.d); 
    ctx->f6.fl = CVT_S_D(ctx->f4.d);
    // 0x8007DD20: swc1        $f6, 0x40($s0)
    MEM_W(0X40, ctx->r16) = ctx->f6.u32l;
    // 0x8007DD24: lwc1        $f10, 0x0($s0)
    ctx->f10.u32l = MEM_W(ctx->r16, 0X0);
L_8007DD28:
    // 0x8007DD28: lwc1        $f16, 0x3C($s0)
    ctx->f16.u32l = MEM_W(ctx->r16, 0X3C);
    // 0x8007DD2C: lwc1        $f18, 0x40($s0)
    ctx->f18.u32l = MEM_W(ctx->r16, 0X40);
    // 0x8007DD30: lwc1        $f6, 0x8($s0)
    ctx->f6.u32l = MEM_W(ctx->r16, 0X8);
    // 0x8007DD34: add.s       $f8, $f10, $f16
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f8.fl = ctx->f10.fl + ctx->f16.fl;
    // 0x8007DD38: lwc1        $f10, 0x44($s0)
    ctx->f10.u32l = MEM_W(ctx->r16, 0X44);
    // 0x8007DD3C: lui         $v1, 0x801C
    ctx->r3 = S32(0X801C << 16);
    // 0x8007DD40: add.s       $f4, $f12, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f4.fl = ctx->f12.fl + ctx->f18.fl;
    // 0x8007DD44: swc1        $f8, 0x0($s0)
    MEM_W(0X0, ctx->r16) = ctx->f8.u32l;
    // 0x8007DD48: lui         $t1, 0x801B
    ctx->r9 = S32(0X801B << 16);
    // 0x8007DD4C: add.s       $f16, $f6, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f16.fl = ctx->f6.fl + ctx->f10.fl;
    // 0x8007DD50: swc1        $f4, 0x4($s0)
    MEM_W(0X4, ctx->r16) = ctx->f4.u32l;
    // 0x8007DD54: addiu       $t1, $t1, -0x11E0
    ctx->r9 = ADD32(ctx->r9, -0X11E0);
    // 0x8007DD58: swc1        $f16, 0x8($s0)
    MEM_W(0X8, ctx->r16) = ctx->f16.u32l;
    // 0x8007DD5C: lw          $v1, -0x4EE0($v1)
    ctx->r3 = MEM_W(ctx->r3, -0X4EE0);
    // 0x8007DD60: sll         $t0, $v1, 6
    ctx->r8 = S32(ctx->r3 << 6);
    // 0x8007DD64: addu        $t0, $t0, $v1
    ctx->r8 = ADD32(ctx->r8, ctx->r3);
    // 0x8007DD68: sll         $t0, $t0, 2
    ctx->r8 = S32(ctx->r8 << 2);
    // 0x8007DD6C: addu        $v0, $t0, $t1
    ctx->r2 = ADD32(ctx->r8, ctx->r9);
L_8007DD70:
    // 0x8007DD70: addiu       $s0, $s0, 0x104
    ctx->r16 = ADD32(ctx->r16, 0X104);
    // 0x8007DD74: sltu        $at, $s0, $v0
    ctx->r1 = ctx->r16 < ctx->r2 ? 1 : 0;
    // 0x8007DD78: bnel        $at, $zero, L_8007DC34
    if (ctx->r1 != 0) {
        // 0x8007DD7C: lw          $t6, 0x9C($s0)
        ctx->r14 = MEM_W(ctx->r16, 0X9C);
            goto L_8007DC34;
    }
    goto skip_2;
    // 0x8007DD7C: lw          $t6, 0x9C($s0)
    ctx->r14 = MEM_W(ctx->r16, 0X9C);
    skip_2:
L_8007DD80:
    // 0x8007DD80: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x8007DD84: ldc1        $f20, -0x5C48($at)
    CHECK_FR(ctx, 20);
    ctx->f20.u64 = LD(ctx->r1, -0X5C48);
    // 0x8007DD88: lui         $v1, 0x801C
    ctx->r3 = S32(0X801C << 16);
    // 0x8007DD8C: lw          $v1, -0x5C0($v1)
    ctx->r3 = MEM_W(ctx->r3, -0X5C0);
    // 0x8007DD90: lui         $at, 0x41F0
    ctx->r1 = S32(0X41F0 << 16);
    // 0x8007DD94: mtc1        $at, $f28
    ctx->f28.u32l = ctx->r1;
    // 0x8007DD98: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x8007DD9C: blez        $v1, L_8007DF20
    if (SIGNED(ctx->r3) <= 0) {
        // 0x8007DDA0: ldc1        $f30, -0x5C40($at)
        CHECK_FR(ctx, 30);
    ctx->f30.u64 = LD(ctx->r1, -0X5C40);
            goto L_8007DF20;
    }
    // 0x8007DDA0: ldc1        $f30, -0x5C40($at)
    CHECK_FR(ctx, 30);
    ctx->f30.u64 = LD(ctx->r1, -0X5C40);
    // 0x8007DDA4: lui         $at, 0x4010
    ctx->r1 = S32(0X4010 << 16);
    // 0x8007DDA8: mtc1        $at, $f27
    ctx->f_odd[(27 - 1) * 2] = ctx->r1;
    // 0x8007DDAC: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x8007DDB0: ldc1        $f24, -0x5C38($at)
    CHECK_FR(ctx, 24);
    ctx->f24.u64 = LD(ctx->r1, -0X5C38);
    // 0x8007DDB4: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x8007DDB8: lui         $s0, 0x801C
    ctx->r16 = S32(0X801C << 16);
    // 0x8007DDBC: mtc1        $zero, $f26
    ctx->f26.u32l = 0;
    // 0x8007DDC0: addiu       $s0, $s0, -0x36C0
    ctx->r16 = ADD32(ctx->r16, -0X36C0);
    // 0x8007DDC4: ldc1        $f22, -0x5C30($at)
    CHECK_FR(ctx, 22);
    ctx->f22.u64 = LD(ctx->r1, -0X5C30);
    // 0x8007DDC8: addiu       $s1, $zero, 0x4
    ctx->r17 = ADD32(0, 0X4);
    // 0x8007DDCC: lw          $t2, 0x58($s0)
    ctx->r10 = MEM_W(ctx->r16, 0X58);
L_8007DDD0:
    // 0x8007DDD0: sll         $t3, $v1, 2
    ctx->r11 = S32(ctx->r3 << 2);
    // 0x8007DDD4: subu        $t3, $t3, $v1
    ctx->r11 = SUB32(ctx->r11, ctx->r3);
    // 0x8007DDD8: beq         $s1, $t2, L_8007DDF8
    if (ctx->r17 == ctx->r10) {
        // 0x8007DDDC: sll         $t3, $t3, 4
        ctx->r11 = S32(ctx->r11 << 4);
            goto L_8007DDF8;
    }
    // 0x8007DDDC: sll         $t3, $t3, 4
    ctx->r11 = S32(ctx->r11 << 4);
    // 0x8007DDE0: addu        $t3, $t3, $v1
    ctx->r11 = ADD32(ctx->r11, ctx->r3);
    // 0x8007DDE4: lui         $t4, 0x801C
    ctx->r12 = S32(0X801C << 16);
    // 0x8007DDE8: addiu       $t4, $t4, -0x36C0
    ctx->r12 = ADD32(ctx->r12, -0X36C0);
    // 0x8007DDEC: sll         $t3, $t3, 2
    ctx->r11 = S32(ctx->r11 << 2);
    // 0x8007DDF0: b           L_8007DF10
    // 0x8007DDF4: addu        $v0, $t3, $t4
    ctx->r2 = ADD32(ctx->r11, ctx->r12);
        goto L_8007DF10;
    // 0x8007DDF4: addu        $v0, $t3, $t4
    ctx->r2 = ADD32(ctx->r11, ctx->r12);
L_8007DDF8:
    // 0x8007DDF8: lwc1        $f12, 0x0($s0)
    ctx->f12.u32l = MEM_W(ctx->r16, 0X0);
    // 0x8007DDFC: lwc1        $f6, 0x24($s0)
    ctx->f6.u32l = MEM_W(ctx->r16, 0X24);
    // 0x8007DE00: lwc1        $f8, 0x18($s0)
    ctx->f8.u32l = MEM_W(ctx->r16, 0X18);
    // 0x8007DE04: lwc1        $f14, 0x8($s0)
    ctx->f14.u32l = MEM_W(ctx->r16, 0X8);
    // 0x8007DE08: sub.s       $f10, $f6, $f12
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f10.fl = ctx->f6.fl - ctx->f12.fl;
    // 0x8007DE0C: cvt.d.s     $f18, $f8
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f8.fl); 
    ctx->f18.d = CVT_D_S(ctx->f8.fl);
    // 0x8007DE10: cvt.d.s     $f16, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f10.fl); 
    ctx->f16.d = CVT_D_S(ctx->f10.fl);
    // 0x8007DE14: mul.d       $f4, $f18, $f20
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f18.d); NAN_CHECK(ctx->f20.d); 
    ctx->f4.d = MUL_D(ctx->f18.d, ctx->f20.d);
    // 0x8007DE18: lwc1        $f10, 0x20($s0)
    ctx->f10.u32l = MEM_W(ctx->r16, 0X20);
    // 0x8007DE1C: mul.d       $f8, $f22, $f16
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f22.d); NAN_CHECK(ctx->f16.d); 
    ctx->f8.d = MUL_D(ctx->f22.d, ctx->f16.d);
    // 0x8007DE20: cvt.d.s     $f16, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f10.fl); 
    ctx->f16.d = CVT_D_S(ctx->f10.fl);
    // 0x8007DE24: add.d       $f18, $f4, $f8
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f4.d); NAN_CHECK(ctx->f8.d); 
    ctx->f18.d = ctx->f4.d + ctx->f8.d;
    // 0x8007DE28: lwc1        $f8, 0x2C($s0)
    ctx->f8.u32l = MEM_W(ctx->r16, 0X2C);
    // 0x8007DE2C: mul.d       $f4, $f16, $f20
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f16.d); NAN_CHECK(ctx->f20.d); 
    ctx->f4.d = MUL_D(ctx->f16.d, ctx->f20.d);
    // 0x8007DE30: cvt.s.d     $f6, $f18
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f18.d); 
    ctx->f6.fl = CVT_S_D(ctx->f18.d);
    // 0x8007DE34: sub.s       $f18, $f8, $f14
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f18.fl = ctx->f8.fl - ctx->f14.fl;
    // 0x8007DE38: swc1        $f6, 0x18($s0)
    MEM_W(0X18, ctx->r16) = ctx->f6.u32l;
    // 0x8007DE3C: cvt.d.s     $f6, $f18
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f18.fl); 
    ctx->f6.d = CVT_D_S(ctx->f18.fl);
    // 0x8007DE40: lwc1        $f18, 0x1C($s0)
    ctx->f18.u32l = MEM_W(ctx->r16, 0X1C);
    // 0x8007DE44: mul.d       $f10, $f22, $f6
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f22.d); NAN_CHECK(ctx->f6.d); 
    ctx->f10.d = MUL_D(ctx->f22.d, ctx->f6.d);
    // 0x8007DE48: cvt.d.s     $f6, $f18
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f18.fl); 
    ctx->f6.d = CVT_D_S(ctx->f18.fl);
    // 0x8007DE4C: add.d       $f16, $f4, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f4.d); NAN_CHECK(ctx->f10.d); 
    ctx->f16.d = ctx->f4.d + ctx->f10.d;
    // 0x8007DE50: mul.d       $f4, $f6, $f24
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 24);
    NAN_CHECK(ctx->f6.d); NAN_CHECK(ctx->f24.d); 
    ctx->f4.d = MUL_D(ctx->f6.d, ctx->f24.d);
    // 0x8007DE54: cvt.s.d     $f8, $f16
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f16.d); 
    ctx->f8.fl = CVT_S_D(ctx->f16.d);
    // 0x8007DE58: sub.d       $f10, $f4, $f26
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 26);
    NAN_CHECK(ctx->f4.d); NAN_CHECK(ctx->f26.d); 
    ctx->f10.d = ctx->f4.d - ctx->f26.d;
    // 0x8007DE5C: swc1        $f8, 0x20($s0)
    MEM_W(0X20, ctx->r16) = ctx->f8.u32l;
    // 0x8007DE60: cvt.s.d     $f16, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f10.d); 
    ctx->f16.fl = CVT_S_D(ctx->f10.d);
    // 0x8007DE64: jal         0x8004D30C
    // 0x8007DE68: swc1        $f16, 0x1C($s0)
    MEM_W(0X1C, ctx->r16) = ctx->f16.u32l;
    func_8004D30C(rdram, ctx);
        goto after_1;
    // 0x8007DE68: swc1        $f16, 0x1C($s0)
    MEM_W(0X1C, ctx->r16) = ctx->f16.u32l;
    after_1:
    // 0x8007DE6C: lwc1        $f12, 0x4($s0)
    ctx->f12.u32l = MEM_W(ctx->r16, 0X4);
    // 0x8007DE70: mtc1        $zero, $f8
    ctx->f8.u32l = 0;
    // 0x8007DE74: sub.s       $f2, $f0, $f12
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f2.fl = ctx->f0.fl - ctx->f12.fl;
    // 0x8007DE78: c.lt.s      $f8, $f2
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 2);
    c1cs = ctx->f8.fl < ctx->f2.fl;
    // 0x8007DE7C: nop

    // 0x8007DE80: bc1fl       L_8007DEC0
    if (!c1cs) {
        // 0x8007DE84: lwc1        $f18, 0x0($s0)
        ctx->f18.u32l = MEM_W(ctx->r16, 0X0);
            goto L_8007DEC0;
    }
    goto skip_3;
    // 0x8007DE84: lwc1        $f18, 0x0($s0)
    ctx->f18.u32l = MEM_W(ctx->r16, 0X0);
    skip_3:
    // 0x8007DE88: c.lt.s      $f28, $f2
    CHECK_FR(ctx, 28);
    CHECK_FR(ctx, 2);
    c1cs = ctx->f28.fl < ctx->f2.fl;
    // 0x8007DE8C: nop

    // 0x8007DE90: bc1fl       L_8007DEA0
    if (!c1cs) {
        // 0x8007DE94: cvt.d.s     $f4, $f2
        CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f2.fl); 
    ctx->f4.d = CVT_D_S(ctx->f2.fl);
            goto L_8007DEA0;
    }
    goto skip_4;
    // 0x8007DE94: cvt.d.s     $f4, $f2
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f2.fl); 
    ctx->f4.d = CVT_D_S(ctx->f2.fl);
    skip_4:
    // 0x8007DE98: mov.s       $f2, $f28
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 28);
    ctx->f2.fl = ctx->f28.fl;
    // 0x8007DE9C: cvt.d.s     $f4, $f2
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f2.fl); 
    ctx->f4.d = CVT_D_S(ctx->f2.fl);
L_8007DEA0:
    // 0x8007DEA0: lwc1        $f18, 0x1C($s0)
    ctx->f18.u32l = MEM_W(ctx->r16, 0X1C);
    // 0x8007DEA4: mul.d       $f10, $f30, $f4
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 30);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f30.d); NAN_CHECK(ctx->f4.d); 
    ctx->f10.d = MUL_D(ctx->f30.d, ctx->f4.d);
    // 0x8007DEA8: lwc1        $f12, 0x4($s0)
    ctx->f12.u32l = MEM_W(ctx->r16, 0X4);
    // 0x8007DEAC: cvt.d.s     $f6, $f18
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f18.fl); 
    ctx->f6.d = CVT_D_S(ctx->f18.fl);
    // 0x8007DEB0: add.d       $f16, $f6, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f6.d); NAN_CHECK(ctx->f10.d); 
    ctx->f16.d = ctx->f6.d + ctx->f10.d;
    // 0x8007DEB4: cvt.s.d     $f8, $f16
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f16.d); 
    ctx->f8.fl = CVT_S_D(ctx->f16.d);
    // 0x8007DEB8: swc1        $f8, 0x1C($s0)
    MEM_W(0X1C, ctx->r16) = ctx->f8.u32l;
    // 0x8007DEBC: lwc1        $f18, 0x0($s0)
    ctx->f18.u32l = MEM_W(ctx->r16, 0X0);
L_8007DEC0:
    // 0x8007DEC0: lwc1        $f4, 0x18($s0)
    ctx->f4.u32l = MEM_W(ctx->r16, 0X18);
    // 0x8007DEC4: lwc1        $f10, 0x1C($s0)
    ctx->f10.u32l = MEM_W(ctx->r16, 0X1C);
    // 0x8007DEC8: lwc1        $f8, 0x8($s0)
    ctx->f8.u32l = MEM_W(ctx->r16, 0X8);
    // 0x8007DECC: add.s       $f6, $f18, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = ctx->f18.fl + ctx->f4.fl;
    // 0x8007DED0: lwc1        $f18, 0x20($s0)
    ctx->f18.u32l = MEM_W(ctx->r16, 0X20);
    // 0x8007DED4: lui         $v1, 0x801C
    ctx->r3 = S32(0X801C << 16);
    // 0x8007DED8: add.s       $f16, $f12, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f16.fl = ctx->f12.fl + ctx->f10.fl;
    // 0x8007DEDC: swc1        $f6, 0x0($s0)
    MEM_W(0X0, ctx->r16) = ctx->f6.u32l;
    // 0x8007DEE0: lui         $t6, 0x801C
    ctx->r14 = S32(0X801C << 16);
    // 0x8007DEE4: add.s       $f4, $f8, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f4.fl = ctx->f8.fl + ctx->f18.fl;
    // 0x8007DEE8: swc1        $f16, 0x4($s0)
    MEM_W(0X4, ctx->r16) = ctx->f16.u32l;
    // 0x8007DEEC: addiu       $t6, $t6, -0x36C0
    ctx->r14 = ADD32(ctx->r14, -0X36C0);
    // 0x8007DEF0: swc1        $f4, 0x8($s0)
    MEM_W(0X8, ctx->r16) = ctx->f4.u32l;
    // 0x8007DEF4: lw          $v1, -0x5C0($v1)
    ctx->r3 = MEM_W(ctx->r3, -0X5C0);
    // 0x8007DEF8: sll         $t5, $v1, 2
    ctx->r13 = S32(ctx->r3 << 2);
    // 0x8007DEFC: subu        $t5, $t5, $v1
    ctx->r13 = SUB32(ctx->r13, ctx->r3);
    // 0x8007DF00: sll         $t5, $t5, 4
    ctx->r13 = S32(ctx->r13 << 4);
    // 0x8007DF04: addu        $t5, $t5, $v1
    ctx->r13 = ADD32(ctx->r13, ctx->r3);
    // 0x8007DF08: sll         $t5, $t5, 2
    ctx->r13 = S32(ctx->r13 << 2);
    // 0x8007DF0C: addu        $v0, $t5, $t6
    ctx->r2 = ADD32(ctx->r13, ctx->r14);
L_8007DF10:
    // 0x8007DF10: addiu       $s0, $s0, 0xC4
    ctx->r16 = ADD32(ctx->r16, 0XC4);
    // 0x8007DF14: sltu        $at, $s0, $v0
    ctx->r1 = ctx->r16 < ctx->r2 ? 1 : 0;
    // 0x8007DF18: bnel        $at, $zero, L_8007DDD0
    if (ctx->r1 != 0) {
        // 0x8007DF1C: lw          $t2, 0x58($s0)
        ctx->r10 = MEM_W(ctx->r16, 0X58);
            goto L_8007DDD0;
    }
    goto skip_5;
    // 0x8007DF1C: lw          $t2, 0x58($s0)
    ctx->r10 = MEM_W(ctx->r16, 0X58);
    skip_5:
L_8007DF20:
    // 0x8007DF20: lw          $ra, 0x4C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X4C);
    // 0x8007DF24: ldc1        $f20, 0x10($sp)
    CHECK_FR(ctx, 20);
    ctx->f20.u64 = LD(ctx->r29, 0X10);
    // 0x8007DF28: ldc1        $f22, 0x18($sp)
    CHECK_FR(ctx, 22);
    ctx->f22.u64 = LD(ctx->r29, 0X18);
    // 0x8007DF2C: ldc1        $f24, 0x20($sp)
    CHECK_FR(ctx, 24);
    ctx->f24.u64 = LD(ctx->r29, 0X20);
    // 0x8007DF30: ldc1        $f26, 0x28($sp)
    CHECK_FR(ctx, 26);
    ctx->f26.u64 = LD(ctx->r29, 0X28);
    // 0x8007DF34: ldc1        $f28, 0x30($sp)
    CHECK_FR(ctx, 28);
    ctx->f28.u64 = LD(ctx->r29, 0X30);
    // 0x8007DF38: ldc1        $f30, 0x38($sp)
    CHECK_FR(ctx, 30);
    ctx->f30.u64 = LD(ctx->r29, 0X38);
    // 0x8007DF3C: lw          $s0, 0x44($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X44);
    // 0x8007DF40: lw          $s1, 0x48($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X48);
    // 0x8007DF44: jr          $ra
    // 0x8007DF48: addiu       $sp, $sp, 0x50
    ctx->r29 = ADD32(ctx->r29, 0X50);
    return;
    // 0x8007DF48: addiu       $sp, $sp, 0x50
    ctx->r29 = ADD32(ctx->r29, 0X50);
;}
RECOMP_FUNC void func_8007DF4C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8007DF4C: lui         $t6, 0x801C
    ctx->r14 = S32(0X801C << 16);
    // 0x8007DF50: lw          $t6, -0x4EE0($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X4EE0);
    // 0x8007DF54: addiu       $sp, $sp, -0x88
    ctx->r29 = ADD32(ctx->r29, -0X88);
    // 0x8007DF58: lui         $v1, 0x801B
    ctx->r3 = S32(0X801B << 16);
    // 0x8007DF5C: sll         $t7, $t6, 6
    ctx->r15 = S32(ctx->r14 << 6);
    // 0x8007DF60: addu        $t7, $t7, $t6
    ctx->r15 = ADD32(ctx->r15, ctx->r14);
    // 0x8007DF64: addiu       $v1, $v1, -0x11E0
    ctx->r3 = ADD32(ctx->r3, -0X11E0);
    // 0x8007DF68: sll         $t7, $t7, 2
    ctx->r15 = S32(ctx->r15 << 2);
    // 0x8007DF6C: addu        $v0, $v1, $t7
    ctx->r2 = ADD32(ctx->r3, ctx->r15);
    // 0x8007DF70: sdc1        $f24, 0x20($sp)
    CHECK_FR(ctx, 24);
    SD(ctx->f24.u64, 0X20, ctx->r29);
    // 0x8007DF74: sdc1        $f22, 0x18($sp)
    CHECK_FR(ctx, 22);
    SD(ctx->f22.u64, 0X18, ctx->r29);
    // 0x8007DF78: sdc1        $f20, 0x10($sp)
    CHECK_FR(ctx, 20);
    SD(ctx->f20.u64, 0X10, ctx->r29);
    // 0x8007DF7C: addiu       $v0, $v0, -0x104
    ctx->r2 = ADD32(ctx->r2, -0X104);
    // 0x8007DF80: mtc1        $a1, $f20
    ctx->f20.u32l = ctx->r5;
    // 0x8007DF84: mtc1        $a3, $f22
    ctx->f22.u32l = ctx->r7;
    // 0x8007DF88: mtc1        $a2, $f24
    ctx->f24.u32l = ctx->r6;
    // 0x8007DF8C: sltu        $at, $v0, $v1
    ctx->r1 = ctx->r2 < ctx->r3 ? 1 : 0;
    // 0x8007DF90: sw          $ra, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r31;
    // 0x8007DF94: sdc1        $f30, 0x38($sp)
    CHECK_FR(ctx, 30);
    SD(ctx->f30.u64, 0X38, ctx->r29);
    // 0x8007DF98: sdc1        $f28, 0x30($sp)
    CHECK_FR(ctx, 28);
    SD(ctx->f28.u64, 0X30, ctx->r29);
    // 0x8007DF9C: bne         $at, $zero, L_8007E8A4
    if (ctx->r1 != 0) {
        // 0x8007DFA0: sdc1        $f26, 0x28($sp)
        CHECK_FR(ctx, 26);
    SD(ctx->f26.u64, 0X28, ctx->r29);
            goto L_8007E8A4;
    }
    // 0x8007DFA0: sdc1        $f26, 0x28($sp)
    CHECK_FR(ctx, 26);
    SD(ctx->f26.u64, 0X28, ctx->r29);
    // 0x8007DFA4: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x8007DFA8: lwc1        $f26, -0x5C28($at)
    ctx->f26.u32l = MEM_W(ctx->r1, -0X5C28);
    // 0x8007DFAC: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x8007DFB0: lwc1        $f18, -0x5C24($at)
    ctx->f18.u32l = MEM_W(ctx->r1, -0X5C24);
    // 0x8007DFB4: addiu       $a1, $zero, 0x3
    ctx->r5 = ADD32(0, 0X3);
    // 0x8007DFB8: lw          $t8, 0x9C($v0)
    ctx->r24 = MEM_W(ctx->r2, 0X9C);
L_8007DFBC:
    // 0x8007DFBC: bnel        $t8, $zero, L_8007E1DC
    if (ctx->r24 != 0) {
        // 0x8007DFC0: lw          $t1, 0x98($v0)
        ctx->r9 = MEM_W(ctx->r2, 0X98);
            goto L_8007E1DC;
    }
    goto skip_0;
    // 0x8007DFC0: lw          $t1, 0x98($v0)
    ctx->r9 = MEM_W(ctx->r2, 0X98);
    skip_0:
    // 0x8007DFC4: lw          $t9, 0xC4($v0)
    ctx->r25 = MEM_W(ctx->r2, 0XC4);
    // 0x8007DFC8: beql        $t9, $zero, L_8007E898
    if (ctx->r25 == 0) {
        // 0x8007DFCC: addiu       $v0, $v0, -0x104
        ctx->r2 = ADD32(ctx->r2, -0X104);
            goto L_8007E898;
    }
    goto skip_1;
    // 0x8007DFCC: addiu       $v0, $v0, -0x104
    ctx->r2 = ADD32(ctx->r2, -0X104);
    skip_1:
    // 0x8007DFD0: lwc1        $f4, 0x0($v0)
    ctx->f4.u32l = MEM_W(ctx->r2, 0X0);
    // 0x8007DFD4: lwc1        $f6, 0x8($v0)
    ctx->f6.u32l = MEM_W(ctx->r2, 0X8);
    // 0x8007DFD8: sub.s       $f14, $f20, $f4
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f14.fl = ctx->f20.fl - ctx->f4.fl;
    // 0x8007DFDC: sub.s       $f16, $f22, $f6
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f16.fl = ctx->f22.fl - ctx->f6.fl;
    // 0x8007DFE0: mul.s       $f8, $f14, $f14
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f8.fl = MUL_S(ctx->f14.fl, ctx->f14.fl);
    // 0x8007DFE4: nop

    // 0x8007DFE8: mul.s       $f10, $f16, $f16
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f10.fl = MUL_S(ctx->f16.fl, ctx->f16.fl);
    // 0x8007DFEC: add.s       $f0, $f8, $f10
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f0.fl = ctx->f8.fl + ctx->f10.fl;
    // 0x8007DFF0: c.lt.s      $f18, $f0
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 0);
    c1cs = ctx->f18.fl < ctx->f0.fl;
    // 0x8007DFF4: nop

    // 0x8007DFF8: bc1t        L_8007E894
    if (c1cs) {
        // 0x8007DFFC: nop
    
            goto L_8007E894;
    }
    // 0x8007DFFC: nop

    // 0x8007E000: lwc1        $f4, 0x4($v0)
    ctx->f4.u32l = MEM_W(ctx->r2, 0X4);
    // 0x8007E004: sub.s       $f2, $f24, $f4
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f24.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f2.fl = ctx->f24.fl - ctx->f4.fl;
    // 0x8007E008: mul.s       $f6, $f2, $f2
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f6.fl = MUL_S(ctx->f2.fl, ctx->f2.fl);
    // 0x8007E00C: add.s       $f12, $f0, $f6
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f12.fl = ctx->f0.fl + ctx->f6.fl;
    // 0x8007E010: c.lt.s      $f12, $f18
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 18);
    c1cs = ctx->f12.fl < ctx->f18.fl;
    // 0x8007E014: nop

    // 0x8007E018: bc1fl       L_8007E898
    if (!c1cs) {
        // 0x8007E01C: addiu       $v0, $v0, -0x104
        ctx->r2 = ADD32(ctx->r2, -0X104);
            goto L_8007E898;
    }
    goto skip_2;
    // 0x8007E01C: addiu       $v0, $v0, -0x104
    ctx->r2 = ADD32(ctx->r2, -0X104);
    skip_2:
    // 0x8007E020: sw          $v0, 0x84($sp)
    MEM_W(0X84, ctx->r29) = ctx->r2;
    // 0x8007E024: sw          $a0, 0x88($sp)
    MEM_W(0X88, ctx->r29) = ctx->r4;
    // 0x8007E028: swc1        $f2, 0x7C($sp)
    MEM_W(0X7C, ctx->r29) = ctx->f2.u32l;
    // 0x8007E02C: swc1        $f14, 0x80($sp)
    MEM_W(0X80, ctx->r29) = ctx->f14.u32l;
    // 0x8007E030: jal         0x800C7010
    // 0x8007E034: swc1        $f16, 0x78($sp)
    MEM_W(0X78, ctx->r29) = ctx->f16.u32l;
    _nsqrtf(rdram, ctx);
        goto after_0;
    // 0x8007E034: swc1        $f16, 0x78($sp)
    MEM_W(0X78, ctx->r29) = ctx->f16.u32l;
    after_0:
    // 0x8007E038: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x8007E03C: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x8007E040: lwc1        $f14, 0x80($sp)
    ctx->f14.u32l = MEM_W(ctx->r29, 0X80);
    // 0x8007E044: lwc1        $f2, 0x7C($sp)
    ctx->f2.u32l = MEM_W(ctx->r29, 0X7C);
    // 0x8007E048: div.s       $f18, $f8, $f0
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f18.fl = DIV_S(ctx->f8.fl, ctx->f0.fl);
    // 0x8007E04C: lui         $at, 0x4278
    ctx->r1 = S32(0X4278 << 16);
    // 0x8007E050: mtc1        $at, $f10
    ctx->f10.u32l = ctx->r1;
    // 0x8007E054: lwc1        $f16, 0x78($sp)
    ctx->f16.u32l = MEM_W(ctx->r29, 0X78);
    // 0x8007E058: lui         $at, 0x800D
    ctx->r1 = S32(0X800D << 16);
    // 0x8007E05C: sub.s       $f20, $f10, $f0
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f20.fl = ctx->f10.fl - ctx->f0.fl;
    // 0x8007E060: lwc1        $f4, 0x49B8($at)
    ctx->f4.u32l = MEM_W(ctx->r1, 0X49B8);
    // 0x8007E064: lw          $v0, 0x84($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X84);
    // 0x8007E068: lw          $a0, 0x88($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X88);
    // 0x8007E06C: lwc1        $f6, 0x0($v0)
    ctx->f6.u32l = MEM_W(ctx->r2, 0X0);
    // 0x8007E070: lwc1        $f10, 0x4($v0)
    ctx->f10.u32l = MEM_W(ctx->r2, 0X4);
    // 0x8007E074: mul.s       $f14, $f14, $f18
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f14.fl = MUL_S(ctx->f14.fl, ctx->f18.fl);
    // 0x8007E078: nop

    // 0x8007E07C: mul.s       $f2, $f2, $f18
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f2.fl = MUL_S(ctx->f2.fl, ctx->f18.fl);
    // 0x8007E080: nop

    // 0x8007E084: mul.s       $f16, $f16, $f18
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f16.fl = MUL_S(ctx->f16.fl, ctx->f18.fl);
    // 0x8007E088: nop

    // 0x8007E08C: mul.s       $f12, $f20, $f4
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f12.fl = MUL_S(ctx->f20.fl, ctx->f4.fl);
    // 0x8007E090: sub.s       $f22, $f20, $f12
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f22.fl = ctx->f20.fl - ctx->f12.fl;
    // 0x8007E094: mul.s       $f24, $f22, $f14
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f24.fl = MUL_S(ctx->f22.fl, ctx->f14.fl);
    // 0x8007E098: sub.s       $f8, $f6, $f24
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 24);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f24.fl); 
    ctx->f8.fl = ctx->f6.fl - ctx->f24.fl;
    // 0x8007E09C: mul.s       $f26, $f22, $f2
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f26.fl = MUL_S(ctx->f22.fl, ctx->f2.fl);
    // 0x8007E0A0: swc1        $f8, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->f8.u32l;
    // 0x8007E0A4: mul.s       $f6, $f22, $f16
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f6.fl = MUL_S(ctx->f22.fl, ctx->f16.fl);
    // 0x8007E0A8: sub.s       $f4, $f10, $f26
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 26);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f26.fl); 
    ctx->f4.fl = ctx->f10.fl - ctx->f26.fl;
    // 0x8007E0AC: swc1        $f4, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->f4.u32l;
    // 0x8007E0B0: swc1        $f6, 0x5C($sp)
    MEM_W(0X5C, ctx->r29) = ctx->f6.u32l;
    // 0x8007E0B4: lwc1        $f10, 0x5C($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0X5C);
    // 0x8007E0B8: lwc1        $f8, 0x8($v0)
    ctx->f8.u32l = MEM_W(ctx->r2, 0X8);
    // 0x8007E0BC: lwc1        $f6, 0x3C($v0)
    ctx->f6.u32l = MEM_W(ctx->r2, 0X3C);
    // 0x8007E0C0: sub.s       $f4, $f8, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f4.fl = ctx->f8.fl - ctx->f10.fl;
    // 0x8007E0C4: lwc1        $f10, 0x40($v0)
    ctx->f10.u32l = MEM_W(ctx->r2, 0X40);
    // 0x8007E0C8: sub.s       $f8, $f6, $f24
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 24);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f24.fl); 
    ctx->f8.fl = ctx->f6.fl - ctx->f24.fl;
    // 0x8007E0CC: swc1        $f4, 0x8($v0)
    MEM_W(0X8, ctx->r2) = ctx->f4.u32l;
    // 0x8007E0D0: lwc1        $f6, 0x44($v0)
    ctx->f6.u32l = MEM_W(ctx->r2, 0X44);
    // 0x8007E0D4: sub.s       $f4, $f10, $f26
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 26);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f26.fl); 
    ctx->f4.fl = ctx->f10.fl - ctx->f26.fl;
    // 0x8007E0D8: swc1        $f8, 0x3C($v0)
    MEM_W(0X3C, ctx->r2) = ctx->f8.u32l;
    // 0x8007E0DC: swc1        $f4, 0x40($v0)
    MEM_W(0X40, ctx->r2) = ctx->f4.u32l;
    // 0x8007E0E0: lwc1        $f8, 0x5C($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X5C);
    // 0x8007E0E4: mul.s       $f4, $f12, $f14
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f4.fl = MUL_S(ctx->f12.fl, ctx->f14.fl);
    // 0x8007E0E8: sub.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = ctx->f6.fl - ctx->f8.fl;
    // 0x8007E0EC: mul.s       $f28, $f12, $f2
    CHECK_FR(ctx, 28);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f28.fl = MUL_S(ctx->f12.fl, ctx->f2.fl);
    // 0x8007E0F0: swc1        $f10, 0x44($v0)
    MEM_W(0X44, ctx->r2) = ctx->f10.u32l;
    // 0x8007E0F4: lw          $v1, 0x98($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X98);
    // 0x8007E0F8: swc1        $f4, 0x74($sp)
    MEM_W(0X74, ctx->r29) = ctx->f4.u32l;
    // 0x8007E0FC: mul.s       $f30, $f12, $f16
    CHECK_FR(ctx, 30);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f30.fl = MUL_S(ctx->f12.fl, ctx->f16.fl);
    // 0x8007E100: lwc1        $f22, 0xC($v1)
    ctx->f22.u32l = MEM_W(ctx->r3, 0XC);
    // 0x8007E104: neg.s       $f6, $f14
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f14.fl); 
    ctx->f6.fl = -ctx->f14.fl;
    // 0x8007E108: lwc1        $f24, 0x10($v1)
    ctx->f24.u32l = MEM_W(ctx->r3, 0X10);
    // 0x8007E10C: mul.s       $f8, $f6, $f22
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f8.fl = MUL_S(ctx->f6.fl, ctx->f22.fl);
    // 0x8007E110: lwc1        $f26, 0x14($v1)
    ctx->f26.u32l = MEM_W(ctx->r3, 0X14);
    // 0x8007E114: mul.s       $f10, $f2, $f24
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 24);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f24.fl); 
    ctx->f10.fl = MUL_S(ctx->f2.fl, ctx->f24.fl);
    // 0x8007E118: mfc1        $a3, $f30
    ctx->r7 = (int32_t)ctx->f30.u32l;
    // 0x8007E11C: mul.s       $f6, $f16, $f26
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 26);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f26.fl); 
    ctx->f6.fl = MUL_S(ctx->f16.fl, ctx->f26.fl);
    // 0x8007E120: sub.s       $f4, $f8, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f4.fl = ctx->f8.fl - ctx->f10.fl;
    // 0x8007E124: lwc1        $f8, 0xC38($a0)
    ctx->f8.u32l = MEM_W(ctx->r4, 0XC38);
    // 0x8007E128: sub.s       $f12, $f4, $f6
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f12.fl = ctx->f4.fl - ctx->f6.fl;
    // 0x8007E12C: c.lt.s      $f8, $f12
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 12);
    c1cs = ctx->f8.fl < ctx->f12.fl;
    // 0x8007E130: nop

    // 0x8007E134: bc1f        L_8007E158
    if (!c1cs) {
        // 0x8007E138: nop
    
            goto L_8007E158;
    }
    // 0x8007E138: nop

    // 0x8007E13C: swc1        $f12, 0xC38($a0)
    MEM_W(0XC38, ctx->r4) = ctx->f12.u32l;
    // 0x8007E140: swc1        $f14, 0x15B4($a0)
    MEM_W(0X15B4, ctx->r4) = ctx->f14.u32l;
    // 0x8007E144: swc1        $f2, 0x15B8($a0)
    MEM_W(0X15B8, ctx->r4) = ctx->f2.u32l;
    // 0x8007E148: swc1        $f16, 0x15BC($a0)
    MEM_W(0X15BC, ctx->r4) = ctx->f16.u32l;
    // 0x8007E14C: lwc1        $f26, 0x14($v1)
    ctx->f26.u32l = MEM_W(ctx->r3, 0X14);
    // 0x8007E150: lwc1        $f24, 0x10($v1)
    ctx->f24.u32l = MEM_W(ctx->r3, 0X10);
    // 0x8007E154: lwc1        $f22, 0xC($v1)
    ctx->f22.u32l = MEM_W(ctx->r3, 0XC);
L_8007E158:
    // 0x8007E158: lwc1        $f0, 0x74($sp)
    ctx->f0.u32l = MEM_W(ctx->r29, 0X74);
    // 0x8007E15C: add.s       $f4, $f24, $f28
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 28);
    NAN_CHECK(ctx->f24.fl); NAN_CHECK(ctx->f28.fl); 
    ctx->f4.fl = ctx->f24.fl + ctx->f28.fl;
    // 0x8007E160: lw          $v0, 0x9C($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X9C);
    // 0x8007E164: lw          $t0, 0xA0($sp)
    ctx->r8 = MEM_W(ctx->r29, 0XA0);
    // 0x8007E168: add.s       $f6, $f26, $f30
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 30);
    NAN_CHECK(ctx->f26.fl); NAN_CHECK(ctx->f30.fl); 
    ctx->f6.fl = ctx->f26.fl + ctx->f30.fl;
    // 0x8007E16C: swc1        $f4, 0x10($v1)
    MEM_W(0X10, ctx->r3) = ctx->f4.u32l;
    // 0x8007E170: mfc1        $a2, $f28
    ctx->r6 = (int32_t)ctx->f28.u32l;
    // 0x8007E174: add.s       $f10, $f22, $f0
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f10.fl = ctx->f22.fl + ctx->f0.fl;
    // 0x8007E178: swc1        $f6, 0x14($v1)
    MEM_W(0X14, ctx->r3) = ctx->f6.u32l;
    // 0x8007E17C: mfc1        $a1, $f0
    ctx->r5 = (int32_t)ctx->f0.u32l;
    // 0x8007E180: swc1        $f10, 0xC($v1)
    MEM_W(0XC, ctx->r3) = ctx->f10.u32l;
    // 0x8007E184: lwc1        $f8, 0xC($v0)
    ctx->f8.u32l = MEM_W(ctx->r2, 0XC);
    // 0x8007E188: lwc1        $f4, 0x10($v0)
    ctx->f4.u32l = MEM_W(ctx->r2, 0X10);
    // 0x8007E18C: add.s       $f10, $f8, $f0
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f10.fl = ctx->f8.fl + ctx->f0.fl;
    // 0x8007E190: lwc1        $f8, 0x14($v0)
    ctx->f8.u32l = MEM_W(ctx->r2, 0X14);
    // 0x8007E194: add.s       $f6, $f4, $f28
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 28);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f28.fl); 
    ctx->f6.fl = ctx->f4.fl + ctx->f28.fl;
    // 0x8007E198: swc1        $f10, 0xC($v0)
    MEM_W(0XC, ctx->r2) = ctx->f10.u32l;
    // 0x8007E19C: add.s       $f10, $f8, $f30
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 30);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f30.fl); 
    ctx->f10.fl = ctx->f8.fl + ctx->f30.fl;
    // 0x8007E1A0: swc1        $f6, 0x10($v0)
    MEM_W(0X10, ctx->r2) = ctx->f6.u32l;
    // 0x8007E1A4: swc1        $f10, 0x14($v0)
    MEM_W(0X14, ctx->r2) = ctx->f10.u32l;
    // 0x8007E1A8: lwc1        $f4, 0xC($t0)
    ctx->f4.u32l = MEM_W(ctx->r8, 0XC);
    // 0x8007E1AC: lwc1        $f8, 0x10($t0)
    ctx->f8.u32l = MEM_W(ctx->r8, 0X10);
    // 0x8007E1B0: add.s       $f6, $f4, $f0
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f6.fl = ctx->f4.fl + ctx->f0.fl;
    // 0x8007E1B4: lwc1        $f4, 0x14($t0)
    ctx->f4.u32l = MEM_W(ctx->r8, 0X14);
    // 0x8007E1B8: add.s       $f10, $f8, $f28
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 28);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f28.fl); 
    ctx->f10.fl = ctx->f8.fl + ctx->f28.fl;
    // 0x8007E1BC: swc1        $f6, 0xC($t0)
    MEM_W(0XC, ctx->r8) = ctx->f6.u32l;
    // 0x8007E1C0: add.s       $f6, $f4, $f30
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 30);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f30.fl); 
    ctx->f6.fl = ctx->f4.fl + ctx->f30.fl;
    // 0x8007E1C4: swc1        $f10, 0x10($t0)
    MEM_W(0X10, ctx->r8) = ctx->f10.u32l;
    // 0x8007E1C8: jal         0x8006243C
    // 0x8007E1CC: swc1        $f6, 0x14($t0)
    MEM_W(0X14, ctx->r8) = ctx->f6.u32l;
    func_8006243C(rdram, ctx);
        goto after_1;
    // 0x8007E1CC: swc1        $f6, 0x14($t0)
    MEM_W(0X14, ctx->r8) = ctx->f6.u32l;
    after_1:
    // 0x8007E1D0: b           L_8007E8A8
    // 0x8007E1D4: lw          $ra, 0x44($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X44);
        goto L_8007E8A8;
    // 0x8007E1D4: lw          $ra, 0x44($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X44);
    // 0x8007E1D8: lw          $t1, 0x98($v0)
    ctx->r9 = MEM_W(ctx->r2, 0X98);
L_8007E1DC:
    // 0x8007E1DC: bnel        $a1, $t1, L_8007E540
    if (ctx->r5 != ctx->r9) {
        // 0x8007E1E0: lwc1        $f8, 0xC($v0)
        ctx->f8.u32l = MEM_W(ctx->r2, 0XC);
            goto L_8007E540;
    }
    goto skip_3;
    // 0x8007E1E0: lwc1        $f8, 0xC($v0)
    ctx->f8.u32l = MEM_W(ctx->r2, 0XC);
    skip_3:
    // 0x8007E1E4: lwc1        $f8, 0xC($v0)
    ctx->f8.u32l = MEM_W(ctx->r2, 0XC);
    // 0x8007E1E8: lwc1        $f10, 0x14($v0)
    ctx->f10.u32l = MEM_W(ctx->r2, 0X14);
    // 0x8007E1EC: sub.s       $f14, $f20, $f8
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f14.fl = ctx->f20.fl - ctx->f8.fl;
    // 0x8007E1F0: sub.s       $f16, $f22, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f16.fl = ctx->f22.fl - ctx->f10.fl;
    // 0x8007E1F4: mul.s       $f4, $f14, $f14
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f4.fl = MUL_S(ctx->f14.fl, ctx->f14.fl);
    // 0x8007E1F8: nop

    // 0x8007E1FC: mul.s       $f6, $f16, $f16
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f6.fl = MUL_S(ctx->f16.fl, ctx->f16.fl);
    // 0x8007E200: add.s       $f0, $f4, $f6
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f0.fl = ctx->f4.fl + ctx->f6.fl;
    // 0x8007E204: c.lt.s      $f0, $f26
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 26);
    c1cs = ctx->f0.fl < ctx->f26.fl;
    // 0x8007E208: nop

    // 0x8007E20C: bc1f        L_8007E390
    if (!c1cs) {
        // 0x8007E210: nop
    
            goto L_8007E390;
    }
    // 0x8007E210: nop

    // 0x8007E214: lwc1        $f8, 0x10($v0)
    ctx->f8.u32l = MEM_W(ctx->r2, 0X10);
    // 0x8007E218: sub.s       $f2, $f24, $f8
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f24.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f2.fl = ctx->f24.fl - ctx->f8.fl;
    // 0x8007E21C: mul.s       $f10, $f2, $f2
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f10.fl = MUL_S(ctx->f2.fl, ctx->f2.fl);
    // 0x8007E220: add.s       $f12, $f0, $f10
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f12.fl = ctx->f0.fl + ctx->f10.fl;
    // 0x8007E224: c.lt.s      $f12, $f26
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 26);
    c1cs = ctx->f12.fl < ctx->f26.fl;
    // 0x8007E228: nop

    // 0x8007E22C: bc1fl       L_8007E394
    if (!c1cs) {
        // 0x8007E230: lwc1        $f10, 0x18($v0)
        ctx->f10.u32l = MEM_W(ctx->r2, 0X18);
            goto L_8007E394;
    }
    goto skip_4;
    // 0x8007E230: lwc1        $f10, 0x18($v0)
    ctx->f10.u32l = MEM_W(ctx->r2, 0X18);
    skip_4:
    // 0x8007E234: sw          $a0, 0x88($sp)
    MEM_W(0X88, ctx->r29) = ctx->r4;
    // 0x8007E238: swc1        $f2, 0x7C($sp)
    MEM_W(0X7C, ctx->r29) = ctx->f2.u32l;
    // 0x8007E23C: swc1        $f14, 0x80($sp)
    MEM_W(0X80, ctx->r29) = ctx->f14.u32l;
    // 0x8007E240: jal         0x800C7010
    // 0x8007E244: swc1        $f16, 0x78($sp)
    MEM_W(0X78, ctx->r29) = ctx->f16.u32l;
    _nsqrtf(rdram, ctx);
        goto after_2;
    // 0x8007E244: swc1        $f16, 0x78($sp)
    MEM_W(0X78, ctx->r29) = ctx->f16.u32l;
    after_2:
    // 0x8007E248: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x8007E24C: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x8007E250: lwc1        $f14, 0x80($sp)
    ctx->f14.u32l = MEM_W(ctx->r29, 0X80);
    // 0x8007E254: lui         $at, 0x42B8
    ctx->r1 = S32(0X42B8 << 16);
    // 0x8007E258: div.s       $f18, $f4, $f0
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f18.fl = DIV_S(ctx->f4.fl, ctx->f0.fl);
    // 0x8007E25C: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x8007E260: lwc1        $f2, 0x7C($sp)
    ctx->f2.u32l = MEM_W(ctx->r29, 0X7C);
    // 0x8007E264: lwc1        $f16, 0x78($sp)
    ctx->f16.u32l = MEM_W(ctx->r29, 0X78);
    // 0x8007E268: sub.s       $f20, $f6, $f0
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f20.fl = ctx->f6.fl - ctx->f0.fl;
    // 0x8007E26C: lw          $v1, 0x98($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X98);
    // 0x8007E270: lw          $a0, 0x88($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X88);
    // 0x8007E274: mul.s       $f14, $f14, $f18
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f14.fl = MUL_S(ctx->f14.fl, ctx->f18.fl);
    // 0x8007E278: nop

    // 0x8007E27C: mul.s       $f8, $f14, $f20
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f8.fl = MUL_S(ctx->f14.fl, ctx->f20.fl);
    // 0x8007E280: nop

    // 0x8007E284: mul.s       $f2, $f2, $f18
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f2.fl = MUL_S(ctx->f2.fl, ctx->f18.fl);
    // 0x8007E288: swc1        $f8, 0x50($sp)
    MEM_W(0X50, ctx->r29) = ctx->f8.u32l;
    // 0x8007E28C: lwc1        $f10, 0x50($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0X50);
    // 0x8007E290: neg.s       $f8, $f14
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f14.fl); 
    ctx->f8.fl = -ctx->f14.fl;
    // 0x8007E294: mul.s       $f4, $f2, $f20
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f4.fl = MUL_S(ctx->f2.fl, ctx->f20.fl);
    // 0x8007E298: swc1        $f10, 0x74($sp)
    MEM_W(0X74, ctx->r29) = ctx->f10.u32l;
    // 0x8007E29C: mul.s       $f16, $f16, $f18
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f16.fl = MUL_S(ctx->f16.fl, ctx->f18.fl);
    // 0x8007E2A0: swc1        $f4, 0x4C($sp)
    MEM_W(0X4C, ctx->r29) = ctx->f4.u32l;
    // 0x8007E2A4: lwc1        $f28, 0x4C($sp)
    ctx->f28.u32l = MEM_W(ctx->r29, 0X4C);
    // 0x8007E2A8: mul.s       $f6, $f16, $f20
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f6.fl = MUL_S(ctx->f16.fl, ctx->f20.fl);
    // 0x8007E2AC: swc1        $f6, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->f6.u32l;
    // 0x8007E2B0: lwc1        $f22, 0xC($v1)
    ctx->f22.u32l = MEM_W(ctx->r3, 0XC);
    // 0x8007E2B4: lwc1        $f24, 0x10($v1)
    ctx->f24.u32l = MEM_W(ctx->r3, 0X10);
    // 0x8007E2B8: lwc1        $f26, 0x14($v1)
    ctx->f26.u32l = MEM_W(ctx->r3, 0X14);
    // 0x8007E2BC: mul.s       $f4, $f8, $f22
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f4.fl = MUL_S(ctx->f8.fl, ctx->f22.fl);
    // 0x8007E2C0: lwc1        $f30, 0x48($sp)
    ctx->f30.u32l = MEM_W(ctx->r29, 0X48);
    // 0x8007E2C4: mul.s       $f6, $f2, $f24
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 24);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f24.fl); 
    ctx->f6.fl = MUL_S(ctx->f2.fl, ctx->f24.fl);
    // 0x8007E2C8: sub.s       $f8, $f4, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = ctx->f4.fl - ctx->f6.fl;
    // 0x8007E2CC: mul.s       $f4, $f16, $f26
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 26);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f26.fl); 
    ctx->f4.fl = MUL_S(ctx->f16.fl, ctx->f26.fl);
    // 0x8007E2D0: lwc1        $f6, 0xC3C($a0)
    ctx->f6.u32l = MEM_W(ctx->r4, 0XC3C);
    // 0x8007E2D4: sub.s       $f12, $f8, $f4
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f12.fl = ctx->f8.fl - ctx->f4.fl;
    // 0x8007E2D8: c.lt.s      $f6, $f12
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 12);
    c1cs = ctx->f6.fl < ctx->f12.fl;
    // 0x8007E2DC: nop

    // 0x8007E2E0: bc1f        L_8007E304
    if (!c1cs) {
        // 0x8007E2E4: nop
    
            goto L_8007E304;
    }
    // 0x8007E2E4: nop

    // 0x8007E2E8: swc1        $f12, 0xC3C($a0)
    MEM_W(0XC3C, ctx->r4) = ctx->f12.u32l;
    // 0x8007E2EC: swc1        $f14, 0x15B4($a0)
    MEM_W(0X15B4, ctx->r4) = ctx->f14.u32l;
    // 0x8007E2F0: swc1        $f2, 0x15B8($a0)
    MEM_W(0X15B8, ctx->r4) = ctx->f2.u32l;
    // 0x8007E2F4: swc1        $f16, 0x15BC($a0)
    MEM_W(0X15BC, ctx->r4) = ctx->f16.u32l;
    // 0x8007E2F8: lwc1        $f26, 0x14($v1)
    ctx->f26.u32l = MEM_W(ctx->r3, 0X14);
    // 0x8007E2FC: lwc1        $f24, 0x10($v1)
    ctx->f24.u32l = MEM_W(ctx->r3, 0X10);
    // 0x8007E300: lwc1        $f22, 0xC($v1)
    ctx->f22.u32l = MEM_W(ctx->r3, 0XC);
L_8007E304:
    // 0x8007E304: lwc1        $f0, 0x4C($sp)
    ctx->f0.u32l = MEM_W(ctx->r29, 0X4C);
    // 0x8007E308: lwc1        $f2, 0x48($sp)
    ctx->f2.u32l = MEM_W(ctx->r29, 0X48);
    // 0x8007E30C: lwc1        $f18, 0x50($sp)
    ctx->f18.u32l = MEM_W(ctx->r29, 0X50);
    // 0x8007E310: add.s       $f4, $f24, $f0
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f24.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f4.fl = ctx->f24.fl + ctx->f0.fl;
    // 0x8007E314: lw          $v0, 0x9C($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X9C);
    // 0x8007E318: lw          $t0, 0xA0($sp)
    ctx->r8 = MEM_W(ctx->r29, 0XA0);
    // 0x8007E31C: add.s       $f6, $f26, $f2
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f26.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f6.fl = ctx->f26.fl + ctx->f2.fl;
    // 0x8007E320: swc1        $f4, 0x10($v1)
    MEM_W(0X10, ctx->r3) = ctx->f4.u32l;
    // 0x8007E324: mfc1        $a2, $f28
    ctx->r6 = (int32_t)ctx->f28.u32l;
    // 0x8007E328: add.s       $f8, $f22, $f18
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f8.fl = ctx->f22.fl + ctx->f18.fl;
    // 0x8007E32C: swc1        $f6, 0x14($v1)
    MEM_W(0X14, ctx->r3) = ctx->f6.u32l;
    // 0x8007E330: mfc1        $a3, $f30
    ctx->r7 = (int32_t)ctx->f30.u32l;
    // 0x8007E334: swc1        $f8, 0xC($v1)
    MEM_W(0XC, ctx->r3) = ctx->f8.u32l;
    // 0x8007E338: lwc1        $f10, 0xC($v0)
    ctx->f10.u32l = MEM_W(ctx->r2, 0XC);
    // 0x8007E33C: lwc1        $f4, 0x10($v0)
    ctx->f4.u32l = MEM_W(ctx->r2, 0X10);
    // 0x8007E340: add.s       $f8, $f10, $f18
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f8.fl = ctx->f10.fl + ctx->f18.fl;
    // 0x8007E344: lwc1        $f10, 0x14($v0)
    ctx->f10.u32l = MEM_W(ctx->r2, 0X14);
    // 0x8007E348: add.s       $f6, $f4, $f0
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f6.fl = ctx->f4.fl + ctx->f0.fl;
    // 0x8007E34C: swc1        $f8, 0xC($v0)
    MEM_W(0XC, ctx->r2) = ctx->f8.u32l;
    // 0x8007E350: add.s       $f8, $f10, $f2
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f8.fl = ctx->f10.fl + ctx->f2.fl;
    // 0x8007E354: swc1        $f6, 0x10($v0)
    MEM_W(0X10, ctx->r2) = ctx->f6.u32l;
    // 0x8007E358: swc1        $f8, 0x14($v0)
    MEM_W(0X14, ctx->r2) = ctx->f8.u32l;
    // 0x8007E35C: lwc1        $f4, 0xC($t0)
    ctx->f4.u32l = MEM_W(ctx->r8, 0XC);
    // 0x8007E360: lwc1        $f10, 0x10($t0)
    ctx->f10.u32l = MEM_W(ctx->r8, 0X10);
    // 0x8007E364: add.s       $f6, $f4, $f18
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f6.fl = ctx->f4.fl + ctx->f18.fl;
    // 0x8007E368: lwc1        $f4, 0x14($t0)
    ctx->f4.u32l = MEM_W(ctx->r8, 0X14);
    // 0x8007E36C: add.s       $f8, $f10, $f28
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 28);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f28.fl); 
    ctx->f8.fl = ctx->f10.fl + ctx->f28.fl;
    // 0x8007E370: swc1        $f6, 0xC($t0)
    MEM_W(0XC, ctx->r8) = ctx->f6.u32l;
    // 0x8007E374: add.s       $f6, $f4, $f30
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 30);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f30.fl); 
    ctx->f6.fl = ctx->f4.fl + ctx->f30.fl;
    // 0x8007E378: swc1        $f8, 0x10($t0)
    MEM_W(0X10, ctx->r8) = ctx->f8.u32l;
    // 0x8007E37C: swc1        $f6, 0x14($t0)
    MEM_W(0X14, ctx->r8) = ctx->f6.u32l;
    // 0x8007E380: jal         0x8006243C
    // 0x8007E384: lw          $a1, 0x74($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X74);
    func_8006243C(rdram, ctx);
        goto after_3;
    // 0x8007E384: lw          $a1, 0x74($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X74);
    after_3:
    // 0x8007E388: b           L_8007E8A8
    // 0x8007E38C: lw          $ra, 0x44($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X44);
        goto L_8007E8A8;
    // 0x8007E38C: lw          $ra, 0x44($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X44);
L_8007E390:
    // 0x8007E390: lwc1        $f10, 0x18($v0)
    ctx->f10.u32l = MEM_W(ctx->r2, 0X18);
L_8007E394:
    // 0x8007E394: lwc1        $f8, 0x20($v0)
    ctx->f8.u32l = MEM_W(ctx->r2, 0X20);
    // 0x8007E398: sub.s       $f14, $f20, $f10
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f14.fl = ctx->f20.fl - ctx->f10.fl;
    // 0x8007E39C: sub.s       $f16, $f22, $f8
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f16.fl = ctx->f22.fl - ctx->f8.fl;
    // 0x8007E3A0: mul.s       $f4, $f14, $f14
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f4.fl = MUL_S(ctx->f14.fl, ctx->f14.fl);
    // 0x8007E3A4: nop

    // 0x8007E3A8: mul.s       $f6, $f16, $f16
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f6.fl = MUL_S(ctx->f16.fl, ctx->f16.fl);
    // 0x8007E3AC: add.s       $f0, $f4, $f6
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f0.fl = ctx->f4.fl + ctx->f6.fl;
    // 0x8007E3B0: c.lt.s      $f0, $f26
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 26);
    c1cs = ctx->f0.fl < ctx->f26.fl;
    // 0x8007E3B4: nop

    // 0x8007E3B8: bc1f        L_8007E894
    if (!c1cs) {
        // 0x8007E3BC: nop
    
            goto L_8007E894;
    }
    // 0x8007E3BC: nop

    // 0x8007E3C0: lwc1        $f10, 0x1C($v0)
    ctx->f10.u32l = MEM_W(ctx->r2, 0X1C);
    // 0x8007E3C4: sub.s       $f2, $f24, $f10
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f24.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f2.fl = ctx->f24.fl - ctx->f10.fl;
    // 0x8007E3C8: mul.s       $f8, $f2, $f2
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f8.fl = MUL_S(ctx->f2.fl, ctx->f2.fl);
    // 0x8007E3CC: add.s       $f12, $f0, $f8
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f12.fl = ctx->f0.fl + ctx->f8.fl;
    // 0x8007E3D0: c.lt.s      $f12, $f26
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 26);
    c1cs = ctx->f12.fl < ctx->f26.fl;
    // 0x8007E3D4: nop

    // 0x8007E3D8: bc1fl       L_8007E898
    if (!c1cs) {
        // 0x8007E3DC: addiu       $v0, $v0, -0x104
        ctx->r2 = ADD32(ctx->r2, -0X104);
            goto L_8007E898;
    }
    goto skip_5;
    // 0x8007E3DC: addiu       $v0, $v0, -0x104
    ctx->r2 = ADD32(ctx->r2, -0X104);
    skip_5:
    // 0x8007E3E0: sw          $a0, 0x88($sp)
    MEM_W(0X88, ctx->r29) = ctx->r4;
    // 0x8007E3E4: swc1        $f2, 0x7C($sp)
    MEM_W(0X7C, ctx->r29) = ctx->f2.u32l;
    // 0x8007E3E8: swc1        $f14, 0x80($sp)
    MEM_W(0X80, ctx->r29) = ctx->f14.u32l;
    // 0x8007E3EC: jal         0x800C7010
    // 0x8007E3F0: swc1        $f16, 0x78($sp)
    MEM_W(0X78, ctx->r29) = ctx->f16.u32l;
    _nsqrtf(rdram, ctx);
        goto after_4;
    // 0x8007E3F0: swc1        $f16, 0x78($sp)
    MEM_W(0X78, ctx->r29) = ctx->f16.u32l;
    after_4:
    // 0x8007E3F4: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x8007E3F8: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x8007E3FC: lwc1        $f14, 0x80($sp)
    ctx->f14.u32l = MEM_W(ctx->r29, 0X80);
    // 0x8007E400: lui         $at, 0x42B8
    ctx->r1 = S32(0X42B8 << 16);
    // 0x8007E404: div.s       $f18, $f4, $f0
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f18.fl = DIV_S(ctx->f4.fl, ctx->f0.fl);
    // 0x8007E408: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x8007E40C: lwc1        $f2, 0x7C($sp)
    ctx->f2.u32l = MEM_W(ctx->r29, 0X7C);
    // 0x8007E410: lwc1        $f16, 0x78($sp)
    ctx->f16.u32l = MEM_W(ctx->r29, 0X78);
    // 0x8007E414: sub.s       $f20, $f6, $f0
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f20.fl = ctx->f6.fl - ctx->f0.fl;
    // 0x8007E418: lw          $v1, 0x98($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X98);
    // 0x8007E41C: lw          $a0, 0x88($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X88);
    // 0x8007E420: mul.s       $f14, $f14, $f18
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f14.fl = MUL_S(ctx->f14.fl, ctx->f18.fl);
    // 0x8007E424: nop

    // 0x8007E428: mul.s       $f10, $f14, $f20
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f10.fl = MUL_S(ctx->f14.fl, ctx->f20.fl);
    // 0x8007E42C: nop

    // 0x8007E430: mul.s       $f2, $f2, $f18
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f2.fl = MUL_S(ctx->f2.fl, ctx->f18.fl);
    // 0x8007E434: swc1        $f10, 0x50($sp)
    MEM_W(0X50, ctx->r29) = ctx->f10.u32l;
    // 0x8007E438: lwc1        $f8, 0x50($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X50);
    // 0x8007E43C: neg.s       $f10, $f14
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f14.fl); 
    ctx->f10.fl = -ctx->f14.fl;
    // 0x8007E440: mul.s       $f4, $f2, $f20
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f4.fl = MUL_S(ctx->f2.fl, ctx->f20.fl);
    // 0x8007E444: swc1        $f8, 0x74($sp)
    MEM_W(0X74, ctx->r29) = ctx->f8.u32l;
    // 0x8007E448: mul.s       $f16, $f16, $f18
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f16.fl = MUL_S(ctx->f16.fl, ctx->f18.fl);
    // 0x8007E44C: swc1        $f4, 0x4C($sp)
    MEM_W(0X4C, ctx->r29) = ctx->f4.u32l;
    // 0x8007E450: lwc1        $f28, 0x4C($sp)
    ctx->f28.u32l = MEM_W(ctx->r29, 0X4C);
    // 0x8007E454: mul.s       $f6, $f16, $f20
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f6.fl = MUL_S(ctx->f16.fl, ctx->f20.fl);
    // 0x8007E458: swc1        $f6, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->f6.u32l;
    // 0x8007E45C: lwc1        $f22, 0xC($v1)
    ctx->f22.u32l = MEM_W(ctx->r3, 0XC);
    // 0x8007E460: lwc1        $f24, 0x10($v1)
    ctx->f24.u32l = MEM_W(ctx->r3, 0X10);
    // 0x8007E464: lwc1        $f26, 0x14($v1)
    ctx->f26.u32l = MEM_W(ctx->r3, 0X14);
    // 0x8007E468: mul.s       $f4, $f10, $f22
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f4.fl = MUL_S(ctx->f10.fl, ctx->f22.fl);
    // 0x8007E46C: lwc1        $f30, 0x48($sp)
    ctx->f30.u32l = MEM_W(ctx->r29, 0X48);
    // 0x8007E470: mul.s       $f6, $f2, $f24
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 24);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f24.fl); 
    ctx->f6.fl = MUL_S(ctx->f2.fl, ctx->f24.fl);
    // 0x8007E474: sub.s       $f10, $f4, $f6
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f10.fl = ctx->f4.fl - ctx->f6.fl;
    // 0x8007E478: mul.s       $f4, $f16, $f26
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 26);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f26.fl); 
    ctx->f4.fl = MUL_S(ctx->f16.fl, ctx->f26.fl);
    // 0x8007E47C: lwc1        $f6, 0xC3C($a0)
    ctx->f6.u32l = MEM_W(ctx->r4, 0XC3C);
    // 0x8007E480: sub.s       $f12, $f10, $f4
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f12.fl = ctx->f10.fl - ctx->f4.fl;
    // 0x8007E484: c.lt.s      $f6, $f12
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 12);
    c1cs = ctx->f6.fl < ctx->f12.fl;
    // 0x8007E488: nop

    // 0x8007E48C: bc1f        L_8007E4B0
    if (!c1cs) {
        // 0x8007E490: nop
    
            goto L_8007E4B0;
    }
    // 0x8007E490: nop

    // 0x8007E494: swc1        $f12, 0xC3C($a0)
    MEM_W(0XC3C, ctx->r4) = ctx->f12.u32l;
    // 0x8007E498: swc1        $f14, 0x15B4($a0)
    MEM_W(0X15B4, ctx->r4) = ctx->f14.u32l;
    // 0x8007E49C: swc1        $f2, 0x15B8($a0)
    MEM_W(0X15B8, ctx->r4) = ctx->f2.u32l;
    // 0x8007E4A0: swc1        $f16, 0x15BC($a0)
    MEM_W(0X15BC, ctx->r4) = ctx->f16.u32l;
    // 0x8007E4A4: lwc1        $f26, 0x14($v1)
    ctx->f26.u32l = MEM_W(ctx->r3, 0X14);
    // 0x8007E4A8: lwc1        $f24, 0x10($v1)
    ctx->f24.u32l = MEM_W(ctx->r3, 0X10);
    // 0x8007E4AC: lwc1        $f22, 0xC($v1)
    ctx->f22.u32l = MEM_W(ctx->r3, 0XC);
L_8007E4B0:
    // 0x8007E4B0: lwc1        $f0, 0x48($sp)
    ctx->f0.u32l = MEM_W(ctx->r29, 0X48);
    // 0x8007E4B4: lwc1        $f2, 0x4C($sp)
    ctx->f2.u32l = MEM_W(ctx->r29, 0X4C);
    // 0x8007E4B8: lwc1        $f18, 0x50($sp)
    ctx->f18.u32l = MEM_W(ctx->r29, 0X50);
    // 0x8007E4BC: add.s       $f6, $f26, $f0
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f26.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f6.fl = ctx->f26.fl + ctx->f0.fl;
    // 0x8007E4C0: lw          $v0, 0x9C($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X9C);
    // 0x8007E4C4: lw          $t0, 0xA0($sp)
    ctx->r8 = MEM_W(ctx->r29, 0XA0);
    // 0x8007E4C8: add.s       $f4, $f24, $f2
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f24.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f4.fl = ctx->f24.fl + ctx->f2.fl;
    // 0x8007E4CC: swc1        $f6, 0x14($v1)
    MEM_W(0X14, ctx->r3) = ctx->f6.u32l;
    // 0x8007E4D0: mfc1        $a2, $f28
    ctx->r6 = (int32_t)ctx->f28.u32l;
    // 0x8007E4D4: add.s       $f10, $f22, $f18
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f10.fl = ctx->f22.fl + ctx->f18.fl;
    // 0x8007E4D8: swc1        $f4, 0x10($v1)
    MEM_W(0X10, ctx->r3) = ctx->f4.u32l;
    // 0x8007E4DC: mfc1        $a3, $f30
    ctx->r7 = (int32_t)ctx->f30.u32l;
    // 0x8007E4E0: swc1        $f10, 0xC($v1)
    MEM_W(0XC, ctx->r3) = ctx->f10.u32l;
    // 0x8007E4E4: lwc1        $f8, 0xC($v0)
    ctx->f8.u32l = MEM_W(ctx->r2, 0XC);
    // 0x8007E4E8: lwc1        $f4, 0x10($v0)
    ctx->f4.u32l = MEM_W(ctx->r2, 0X10);
    // 0x8007E4EC: add.s       $f10, $f8, $f18
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f10.fl = ctx->f8.fl + ctx->f18.fl;
    // 0x8007E4F0: lwc1        $f8, 0x14($v0)
    ctx->f8.u32l = MEM_W(ctx->r2, 0X14);
    // 0x8007E4F4: add.s       $f6, $f4, $f2
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f6.fl = ctx->f4.fl + ctx->f2.fl;
    // 0x8007E4F8: swc1        $f10, 0xC($v0)
    MEM_W(0XC, ctx->r2) = ctx->f10.u32l;
    // 0x8007E4FC: add.s       $f10, $f8, $f0
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f10.fl = ctx->f8.fl + ctx->f0.fl;
    // 0x8007E500: swc1        $f6, 0x10($v0)
    MEM_W(0X10, ctx->r2) = ctx->f6.u32l;
    // 0x8007E504: swc1        $f10, 0x14($v0)
    MEM_W(0X14, ctx->r2) = ctx->f10.u32l;
    // 0x8007E508: lwc1        $f4, 0xC($t0)
    ctx->f4.u32l = MEM_W(ctx->r8, 0XC);
    // 0x8007E50C: lwc1        $f8, 0x10($t0)
    ctx->f8.u32l = MEM_W(ctx->r8, 0X10);
    // 0x8007E510: add.s       $f6, $f4, $f18
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f6.fl = ctx->f4.fl + ctx->f18.fl;
    // 0x8007E514: lwc1        $f4, 0x14($t0)
    ctx->f4.u32l = MEM_W(ctx->r8, 0X14);
    // 0x8007E518: add.s       $f10, $f8, $f28
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 28);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f28.fl); 
    ctx->f10.fl = ctx->f8.fl + ctx->f28.fl;
    // 0x8007E51C: swc1        $f6, 0xC($t0)
    MEM_W(0XC, ctx->r8) = ctx->f6.u32l;
    // 0x8007E520: add.s       $f6, $f4, $f30
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 30);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f30.fl); 
    ctx->f6.fl = ctx->f4.fl + ctx->f30.fl;
    // 0x8007E524: swc1        $f10, 0x10($t0)
    MEM_W(0X10, ctx->r8) = ctx->f10.u32l;
    // 0x8007E528: swc1        $f6, 0x14($t0)
    MEM_W(0X14, ctx->r8) = ctx->f6.u32l;
    // 0x8007E52C: jal         0x8006243C
    // 0x8007E530: lw          $a1, 0x74($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X74);
    func_8006243C(rdram, ctx);
        goto after_5;
    // 0x8007E530: lw          $a1, 0x74($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X74);
    after_5:
    // 0x8007E534: b           L_8007E8A8
    // 0x8007E538: lw          $ra, 0x44($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X44);
        goto L_8007E8A8;
    // 0x8007E538: lw          $ra, 0x44($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X44);
    // 0x8007E53C: lwc1        $f8, 0xC($v0)
    ctx->f8.u32l = MEM_W(ctx->r2, 0XC);
L_8007E540:
    // 0x8007E540: lwc1        $f10, 0x14($v0)
    ctx->f10.u32l = MEM_W(ctx->r2, 0X14);
    // 0x8007E544: sub.s       $f14, $f20, $f8
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f14.fl = ctx->f20.fl - ctx->f8.fl;
    // 0x8007E548: sub.s       $f16, $f22, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f16.fl = ctx->f22.fl - ctx->f10.fl;
    // 0x8007E54C: mul.s       $f4, $f14, $f14
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f4.fl = MUL_S(ctx->f14.fl, ctx->f14.fl);
    // 0x8007E550: nop

    // 0x8007E554: mul.s       $f6, $f16, $f16
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f6.fl = MUL_S(ctx->f16.fl, ctx->f16.fl);
    // 0x8007E558: add.s       $f0, $f4, $f6
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f0.fl = ctx->f4.fl + ctx->f6.fl;
    // 0x8007E55C: c.lt.s      $f0, $f18
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 18);
    c1cs = ctx->f0.fl < ctx->f18.fl;
    // 0x8007E560: nop

    // 0x8007E564: bc1f        L_8007E6E8
    if (!c1cs) {
        // 0x8007E568: nop
    
            goto L_8007E6E8;
    }
    // 0x8007E568: nop

    // 0x8007E56C: lwc1        $f8, 0x10($v0)
    ctx->f8.u32l = MEM_W(ctx->r2, 0X10);
    // 0x8007E570: sub.s       $f2, $f24, $f8
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f24.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f2.fl = ctx->f24.fl - ctx->f8.fl;
    // 0x8007E574: mul.s       $f10, $f2, $f2
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f10.fl = MUL_S(ctx->f2.fl, ctx->f2.fl);
    // 0x8007E578: add.s       $f12, $f0, $f10
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f12.fl = ctx->f0.fl + ctx->f10.fl;
    // 0x8007E57C: c.lt.s      $f12, $f18
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 18);
    c1cs = ctx->f12.fl < ctx->f18.fl;
    // 0x8007E580: nop

    // 0x8007E584: bc1fl       L_8007E6EC
    if (!c1cs) {
        // 0x8007E588: lwc1        $f10, 0x18($v0)
        ctx->f10.u32l = MEM_W(ctx->r2, 0X18);
            goto L_8007E6EC;
    }
    goto skip_6;
    // 0x8007E588: lwc1        $f10, 0x18($v0)
    ctx->f10.u32l = MEM_W(ctx->r2, 0X18);
    skip_6:
    // 0x8007E58C: sw          $a0, 0x88($sp)
    MEM_W(0X88, ctx->r29) = ctx->r4;
    // 0x8007E590: swc1        $f2, 0x7C($sp)
    MEM_W(0X7C, ctx->r29) = ctx->f2.u32l;
    // 0x8007E594: swc1        $f14, 0x80($sp)
    MEM_W(0X80, ctx->r29) = ctx->f14.u32l;
    // 0x8007E598: jal         0x800C7010
    // 0x8007E59C: swc1        $f16, 0x78($sp)
    MEM_W(0X78, ctx->r29) = ctx->f16.u32l;
    _nsqrtf(rdram, ctx);
        goto after_6;
    // 0x8007E59C: swc1        $f16, 0x78($sp)
    MEM_W(0X78, ctx->r29) = ctx->f16.u32l;
    after_6:
    // 0x8007E5A0: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x8007E5A4: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x8007E5A8: lwc1        $f14, 0x80($sp)
    ctx->f14.u32l = MEM_W(ctx->r29, 0X80);
    // 0x8007E5AC: lui         $at, 0x4278
    ctx->r1 = S32(0X4278 << 16);
    // 0x8007E5B0: div.s       $f18, $f4, $f0
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f18.fl = DIV_S(ctx->f4.fl, ctx->f0.fl);
    // 0x8007E5B4: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x8007E5B8: lwc1        $f2, 0x7C($sp)
    ctx->f2.u32l = MEM_W(ctx->r29, 0X7C);
    // 0x8007E5BC: lwc1        $f16, 0x78($sp)
    ctx->f16.u32l = MEM_W(ctx->r29, 0X78);
    // 0x8007E5C0: sub.s       $f20, $f6, $f0
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f20.fl = ctx->f6.fl - ctx->f0.fl;
    // 0x8007E5C4: lw          $v1, 0x98($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X98);
    // 0x8007E5C8: lw          $a0, 0x88($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X88);
    // 0x8007E5CC: mul.s       $f14, $f14, $f18
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f14.fl = MUL_S(ctx->f14.fl, ctx->f18.fl);
    // 0x8007E5D0: nop

    // 0x8007E5D4: mul.s       $f8, $f14, $f20
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f8.fl = MUL_S(ctx->f14.fl, ctx->f20.fl);
    // 0x8007E5D8: nop

    // 0x8007E5DC: mul.s       $f2, $f2, $f18
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f2.fl = MUL_S(ctx->f2.fl, ctx->f18.fl);
    // 0x8007E5E0: swc1        $f8, 0x50($sp)
    MEM_W(0X50, ctx->r29) = ctx->f8.u32l;
    // 0x8007E5E4: lwc1        $f10, 0x50($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0X50);
    // 0x8007E5E8: neg.s       $f8, $f14
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f14.fl); 
    ctx->f8.fl = -ctx->f14.fl;
    // 0x8007E5EC: mul.s       $f4, $f2, $f20
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f4.fl = MUL_S(ctx->f2.fl, ctx->f20.fl);
    // 0x8007E5F0: swc1        $f10, 0x74($sp)
    MEM_W(0X74, ctx->r29) = ctx->f10.u32l;
    // 0x8007E5F4: mul.s       $f16, $f16, $f18
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f16.fl = MUL_S(ctx->f16.fl, ctx->f18.fl);
    // 0x8007E5F8: swc1        $f4, 0x4C($sp)
    MEM_W(0X4C, ctx->r29) = ctx->f4.u32l;
    // 0x8007E5FC: lwc1        $f28, 0x4C($sp)
    ctx->f28.u32l = MEM_W(ctx->r29, 0X4C);
    // 0x8007E600: mul.s       $f6, $f16, $f20
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f6.fl = MUL_S(ctx->f16.fl, ctx->f20.fl);
    // 0x8007E604: swc1        $f6, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->f6.u32l;
    // 0x8007E608: lwc1        $f22, 0xC($v1)
    ctx->f22.u32l = MEM_W(ctx->r3, 0XC);
    // 0x8007E60C: lwc1        $f24, 0x10($v1)
    ctx->f24.u32l = MEM_W(ctx->r3, 0X10);
    // 0x8007E610: lwc1        $f26, 0x14($v1)
    ctx->f26.u32l = MEM_W(ctx->r3, 0X14);
    // 0x8007E614: mul.s       $f4, $f8, $f22
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f4.fl = MUL_S(ctx->f8.fl, ctx->f22.fl);
    // 0x8007E618: lwc1        $f30, 0x48($sp)
    ctx->f30.u32l = MEM_W(ctx->r29, 0X48);
    // 0x8007E61C: mul.s       $f6, $f2, $f24
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 24);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f24.fl); 
    ctx->f6.fl = MUL_S(ctx->f2.fl, ctx->f24.fl);
    // 0x8007E620: sub.s       $f8, $f4, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = ctx->f4.fl - ctx->f6.fl;
    // 0x8007E624: mul.s       $f4, $f16, $f26
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 26);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f26.fl); 
    ctx->f4.fl = MUL_S(ctx->f16.fl, ctx->f26.fl);
    // 0x8007E628: lwc1        $f6, 0xC3C($a0)
    ctx->f6.u32l = MEM_W(ctx->r4, 0XC3C);
    // 0x8007E62C: sub.s       $f12, $f8, $f4
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f12.fl = ctx->f8.fl - ctx->f4.fl;
    // 0x8007E630: c.lt.s      $f6, $f12
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 12);
    c1cs = ctx->f6.fl < ctx->f12.fl;
    // 0x8007E634: nop

    // 0x8007E638: bc1f        L_8007E65C
    if (!c1cs) {
        // 0x8007E63C: nop
    
            goto L_8007E65C;
    }
    // 0x8007E63C: nop

    // 0x8007E640: swc1        $f12, 0xC3C($a0)
    MEM_W(0XC3C, ctx->r4) = ctx->f12.u32l;
    // 0x8007E644: swc1        $f14, 0x15B4($a0)
    MEM_W(0X15B4, ctx->r4) = ctx->f14.u32l;
    // 0x8007E648: swc1        $f2, 0x15B8($a0)
    MEM_W(0X15B8, ctx->r4) = ctx->f2.u32l;
    // 0x8007E64C: swc1        $f16, 0x15BC($a0)
    MEM_W(0X15BC, ctx->r4) = ctx->f16.u32l;
    // 0x8007E650: lwc1        $f26, 0x14($v1)
    ctx->f26.u32l = MEM_W(ctx->r3, 0X14);
    // 0x8007E654: lwc1        $f24, 0x10($v1)
    ctx->f24.u32l = MEM_W(ctx->r3, 0X10);
    // 0x8007E658: lwc1        $f22, 0xC($v1)
    ctx->f22.u32l = MEM_W(ctx->r3, 0XC);
L_8007E65C:
    // 0x8007E65C: lwc1        $f0, 0x4C($sp)
    ctx->f0.u32l = MEM_W(ctx->r29, 0X4C);
    // 0x8007E660: lwc1        $f2, 0x48($sp)
    ctx->f2.u32l = MEM_W(ctx->r29, 0X48);
    // 0x8007E664: lwc1        $f18, 0x50($sp)
    ctx->f18.u32l = MEM_W(ctx->r29, 0X50);
    // 0x8007E668: add.s       $f4, $f24, $f0
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f24.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f4.fl = ctx->f24.fl + ctx->f0.fl;
    // 0x8007E66C: lw          $v0, 0x9C($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X9C);
    // 0x8007E670: lw          $t0, 0xA0($sp)
    ctx->r8 = MEM_W(ctx->r29, 0XA0);
    // 0x8007E674: add.s       $f6, $f26, $f2
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f26.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f6.fl = ctx->f26.fl + ctx->f2.fl;
    // 0x8007E678: swc1        $f4, 0x10($v1)
    MEM_W(0X10, ctx->r3) = ctx->f4.u32l;
    // 0x8007E67C: mfc1        $a2, $f28
    ctx->r6 = (int32_t)ctx->f28.u32l;
    // 0x8007E680: add.s       $f8, $f22, $f18
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f8.fl = ctx->f22.fl + ctx->f18.fl;
    // 0x8007E684: swc1        $f6, 0x14($v1)
    MEM_W(0X14, ctx->r3) = ctx->f6.u32l;
    // 0x8007E688: mfc1        $a3, $f30
    ctx->r7 = (int32_t)ctx->f30.u32l;
    // 0x8007E68C: swc1        $f8, 0xC($v1)
    MEM_W(0XC, ctx->r3) = ctx->f8.u32l;
    // 0x8007E690: lwc1        $f10, 0xC($v0)
    ctx->f10.u32l = MEM_W(ctx->r2, 0XC);
    // 0x8007E694: lwc1        $f4, 0x10($v0)
    ctx->f4.u32l = MEM_W(ctx->r2, 0X10);
    // 0x8007E698: add.s       $f8, $f10, $f18
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f8.fl = ctx->f10.fl + ctx->f18.fl;
    // 0x8007E69C: lwc1        $f10, 0x14($v0)
    ctx->f10.u32l = MEM_W(ctx->r2, 0X14);
    // 0x8007E6A0: add.s       $f6, $f4, $f0
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f6.fl = ctx->f4.fl + ctx->f0.fl;
    // 0x8007E6A4: swc1        $f8, 0xC($v0)
    MEM_W(0XC, ctx->r2) = ctx->f8.u32l;
    // 0x8007E6A8: add.s       $f8, $f10, $f2
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f8.fl = ctx->f10.fl + ctx->f2.fl;
    // 0x8007E6AC: swc1        $f6, 0x10($v0)
    MEM_W(0X10, ctx->r2) = ctx->f6.u32l;
    // 0x8007E6B0: swc1        $f8, 0x14($v0)
    MEM_W(0X14, ctx->r2) = ctx->f8.u32l;
    // 0x8007E6B4: lwc1        $f4, 0xC($t0)
    ctx->f4.u32l = MEM_W(ctx->r8, 0XC);
    // 0x8007E6B8: lwc1        $f10, 0x10($t0)
    ctx->f10.u32l = MEM_W(ctx->r8, 0X10);
    // 0x8007E6BC: add.s       $f6, $f4, $f18
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f6.fl = ctx->f4.fl + ctx->f18.fl;
    // 0x8007E6C0: lwc1        $f4, 0x14($t0)
    ctx->f4.u32l = MEM_W(ctx->r8, 0X14);
    // 0x8007E6C4: add.s       $f8, $f10, $f28
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 28);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f28.fl); 
    ctx->f8.fl = ctx->f10.fl + ctx->f28.fl;
    // 0x8007E6C8: swc1        $f6, 0xC($t0)
    MEM_W(0XC, ctx->r8) = ctx->f6.u32l;
    // 0x8007E6CC: add.s       $f6, $f4, $f30
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 30);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f30.fl); 
    ctx->f6.fl = ctx->f4.fl + ctx->f30.fl;
    // 0x8007E6D0: swc1        $f8, 0x10($t0)
    MEM_W(0X10, ctx->r8) = ctx->f8.u32l;
    // 0x8007E6D4: swc1        $f6, 0x14($t0)
    MEM_W(0X14, ctx->r8) = ctx->f6.u32l;
    // 0x8007E6D8: jal         0x8006243C
    // 0x8007E6DC: lw          $a1, 0x74($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X74);
    func_8006243C(rdram, ctx);
        goto after_7;
    // 0x8007E6DC: lw          $a1, 0x74($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X74);
    after_7:
    // 0x8007E6E0: b           L_8007E8A8
    // 0x8007E6E4: lw          $ra, 0x44($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X44);
        goto L_8007E8A8;
    // 0x8007E6E4: lw          $ra, 0x44($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X44);
L_8007E6E8:
    // 0x8007E6E8: lwc1        $f10, 0x18($v0)
    ctx->f10.u32l = MEM_W(ctx->r2, 0X18);
L_8007E6EC:
    // 0x8007E6EC: lwc1        $f8, 0x20($v0)
    ctx->f8.u32l = MEM_W(ctx->r2, 0X20);
    // 0x8007E6F0: sub.s       $f14, $f20, $f10
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f14.fl = ctx->f20.fl - ctx->f10.fl;
    // 0x8007E6F4: sub.s       $f16, $f22, $f8
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f16.fl = ctx->f22.fl - ctx->f8.fl;
    // 0x8007E6F8: mul.s       $f4, $f14, $f14
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f4.fl = MUL_S(ctx->f14.fl, ctx->f14.fl);
    // 0x8007E6FC: nop

    // 0x8007E700: mul.s       $f6, $f16, $f16
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f6.fl = MUL_S(ctx->f16.fl, ctx->f16.fl);
    // 0x8007E704: add.s       $f0, $f4, $f6
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f0.fl = ctx->f4.fl + ctx->f6.fl;
    // 0x8007E708: c.lt.s      $f0, $f18
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 18);
    c1cs = ctx->f0.fl < ctx->f18.fl;
    // 0x8007E70C: nop

    // 0x8007E710: bc1f        L_8007E894
    if (!c1cs) {
        // 0x8007E714: nop
    
            goto L_8007E894;
    }
    // 0x8007E714: nop

    // 0x8007E718: lwc1        $f10, 0x1C($v0)
    ctx->f10.u32l = MEM_W(ctx->r2, 0X1C);
    // 0x8007E71C: sub.s       $f2, $f24, $f10
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f24.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f2.fl = ctx->f24.fl - ctx->f10.fl;
    // 0x8007E720: mul.s       $f8, $f2, $f2
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f8.fl = MUL_S(ctx->f2.fl, ctx->f2.fl);
    // 0x8007E724: add.s       $f12, $f0, $f8
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f12.fl = ctx->f0.fl + ctx->f8.fl;
    // 0x8007E728: c.lt.s      $f12, $f18
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 18);
    c1cs = ctx->f12.fl < ctx->f18.fl;
    // 0x8007E72C: nop

    // 0x8007E730: bc1fl       L_8007E898
    if (!c1cs) {
        // 0x8007E734: addiu       $v0, $v0, -0x104
        ctx->r2 = ADD32(ctx->r2, -0X104);
            goto L_8007E898;
    }
    goto skip_7;
    // 0x8007E734: addiu       $v0, $v0, -0x104
    ctx->r2 = ADD32(ctx->r2, -0X104);
    skip_7:
    // 0x8007E738: sw          $a0, 0x88($sp)
    MEM_W(0X88, ctx->r29) = ctx->r4;
    // 0x8007E73C: swc1        $f2, 0x7C($sp)
    MEM_W(0X7C, ctx->r29) = ctx->f2.u32l;
    // 0x8007E740: swc1        $f14, 0x80($sp)
    MEM_W(0X80, ctx->r29) = ctx->f14.u32l;
    // 0x8007E744: jal         0x800C7010
    // 0x8007E748: swc1        $f16, 0x78($sp)
    MEM_W(0X78, ctx->r29) = ctx->f16.u32l;
    _nsqrtf(rdram, ctx);
        goto after_8;
    // 0x8007E748: swc1        $f16, 0x78($sp)
    MEM_W(0X78, ctx->r29) = ctx->f16.u32l;
    after_8:
    // 0x8007E74C: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x8007E750: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x8007E754: lwc1        $f14, 0x80($sp)
    ctx->f14.u32l = MEM_W(ctx->r29, 0X80);
    // 0x8007E758: lui         $at, 0x4278
    ctx->r1 = S32(0X4278 << 16);
    // 0x8007E75C: div.s       $f18, $f4, $f0
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f18.fl = DIV_S(ctx->f4.fl, ctx->f0.fl);
    // 0x8007E760: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x8007E764: lwc1        $f2, 0x7C($sp)
    ctx->f2.u32l = MEM_W(ctx->r29, 0X7C);
    // 0x8007E768: lwc1        $f16, 0x78($sp)
    ctx->f16.u32l = MEM_W(ctx->r29, 0X78);
    // 0x8007E76C: sub.s       $f20, $f6, $f0
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f20.fl = ctx->f6.fl - ctx->f0.fl;
    // 0x8007E770: lw          $v1, 0x98($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X98);
    // 0x8007E774: lw          $a0, 0x88($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X88);
    // 0x8007E778: mul.s       $f14, $f14, $f18
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f14.fl = MUL_S(ctx->f14.fl, ctx->f18.fl);
    // 0x8007E77C: nop

    // 0x8007E780: mul.s       $f10, $f14, $f20
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f10.fl = MUL_S(ctx->f14.fl, ctx->f20.fl);
    // 0x8007E784: nop

    // 0x8007E788: mul.s       $f2, $f2, $f18
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f2.fl = MUL_S(ctx->f2.fl, ctx->f18.fl);
    // 0x8007E78C: swc1        $f10, 0x50($sp)
    MEM_W(0X50, ctx->r29) = ctx->f10.u32l;
    // 0x8007E790: lwc1        $f8, 0x50($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X50);
    // 0x8007E794: neg.s       $f10, $f14
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f14.fl); 
    ctx->f10.fl = -ctx->f14.fl;
    // 0x8007E798: mul.s       $f4, $f2, $f20
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f4.fl = MUL_S(ctx->f2.fl, ctx->f20.fl);
    // 0x8007E79C: swc1        $f8, 0x74($sp)
    MEM_W(0X74, ctx->r29) = ctx->f8.u32l;
    // 0x8007E7A0: mul.s       $f16, $f16, $f18
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f16.fl = MUL_S(ctx->f16.fl, ctx->f18.fl);
    // 0x8007E7A4: swc1        $f4, 0x4C($sp)
    MEM_W(0X4C, ctx->r29) = ctx->f4.u32l;
    // 0x8007E7A8: lwc1        $f28, 0x4C($sp)
    ctx->f28.u32l = MEM_W(ctx->r29, 0X4C);
    // 0x8007E7AC: mul.s       $f6, $f16, $f20
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f6.fl = MUL_S(ctx->f16.fl, ctx->f20.fl);
    // 0x8007E7B0: swc1        $f6, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->f6.u32l;
    // 0x8007E7B4: lwc1        $f22, 0xC($v1)
    ctx->f22.u32l = MEM_W(ctx->r3, 0XC);
    // 0x8007E7B8: lwc1        $f24, 0x10($v1)
    ctx->f24.u32l = MEM_W(ctx->r3, 0X10);
    // 0x8007E7BC: lwc1        $f26, 0x14($v1)
    ctx->f26.u32l = MEM_W(ctx->r3, 0X14);
    // 0x8007E7C0: mul.s       $f4, $f10, $f22
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f4.fl = MUL_S(ctx->f10.fl, ctx->f22.fl);
    // 0x8007E7C4: lwc1        $f30, 0x48($sp)
    ctx->f30.u32l = MEM_W(ctx->r29, 0X48);
    // 0x8007E7C8: mul.s       $f6, $f2, $f24
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 24);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f24.fl); 
    ctx->f6.fl = MUL_S(ctx->f2.fl, ctx->f24.fl);
    // 0x8007E7CC: sub.s       $f10, $f4, $f6
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f10.fl = ctx->f4.fl - ctx->f6.fl;
    // 0x8007E7D0: mul.s       $f4, $f16, $f26
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 26);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f26.fl); 
    ctx->f4.fl = MUL_S(ctx->f16.fl, ctx->f26.fl);
    // 0x8007E7D4: lwc1        $f6, 0xC3C($a0)
    ctx->f6.u32l = MEM_W(ctx->r4, 0XC3C);
    // 0x8007E7D8: sub.s       $f12, $f10, $f4
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f12.fl = ctx->f10.fl - ctx->f4.fl;
    // 0x8007E7DC: c.lt.s      $f6, $f12
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 12);
    c1cs = ctx->f6.fl < ctx->f12.fl;
    // 0x8007E7E0: nop

    // 0x8007E7E4: bc1f        L_8007E808
    if (!c1cs) {
        // 0x8007E7E8: nop
    
            goto L_8007E808;
    }
    // 0x8007E7E8: nop

    // 0x8007E7EC: swc1        $f12, 0xC3C($a0)
    MEM_W(0XC3C, ctx->r4) = ctx->f12.u32l;
    // 0x8007E7F0: swc1        $f14, 0x15B4($a0)
    MEM_W(0X15B4, ctx->r4) = ctx->f14.u32l;
    // 0x8007E7F4: swc1        $f2, 0x15B8($a0)
    MEM_W(0X15B8, ctx->r4) = ctx->f2.u32l;
    // 0x8007E7F8: swc1        $f16, 0x15BC($a0)
    MEM_W(0X15BC, ctx->r4) = ctx->f16.u32l;
    // 0x8007E7FC: lwc1        $f26, 0x14($v1)
    ctx->f26.u32l = MEM_W(ctx->r3, 0X14);
    // 0x8007E800: lwc1        $f24, 0x10($v1)
    ctx->f24.u32l = MEM_W(ctx->r3, 0X10);
    // 0x8007E804: lwc1        $f22, 0xC($v1)
    ctx->f22.u32l = MEM_W(ctx->r3, 0XC);
L_8007E808:
    // 0x8007E808: lwc1        $f0, 0x48($sp)
    ctx->f0.u32l = MEM_W(ctx->r29, 0X48);
    // 0x8007E80C: lwc1        $f2, 0x4C($sp)
    ctx->f2.u32l = MEM_W(ctx->r29, 0X4C);
    // 0x8007E810: lwc1        $f18, 0x50($sp)
    ctx->f18.u32l = MEM_W(ctx->r29, 0X50);
    // 0x8007E814: add.s       $f6, $f26, $f0
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f26.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f6.fl = ctx->f26.fl + ctx->f0.fl;
    // 0x8007E818: lw          $v0, 0x9C($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X9C);
    // 0x8007E81C: lw          $t0, 0xA0($sp)
    ctx->r8 = MEM_W(ctx->r29, 0XA0);
    // 0x8007E820: add.s       $f4, $f24, $f2
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f24.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f4.fl = ctx->f24.fl + ctx->f2.fl;
    // 0x8007E824: swc1        $f6, 0x14($v1)
    MEM_W(0X14, ctx->r3) = ctx->f6.u32l;
    // 0x8007E828: mfc1        $a2, $f28
    ctx->r6 = (int32_t)ctx->f28.u32l;
    // 0x8007E82C: add.s       $f10, $f22, $f18
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f10.fl = ctx->f22.fl + ctx->f18.fl;
    // 0x8007E830: swc1        $f4, 0x10($v1)
    MEM_W(0X10, ctx->r3) = ctx->f4.u32l;
    // 0x8007E834: mfc1        $a3, $f30
    ctx->r7 = (int32_t)ctx->f30.u32l;
    // 0x8007E838: swc1        $f10, 0xC($v1)
    MEM_W(0XC, ctx->r3) = ctx->f10.u32l;
    // 0x8007E83C: lwc1        $f8, 0xC($v0)
    ctx->f8.u32l = MEM_W(ctx->r2, 0XC);
    // 0x8007E840: lwc1        $f4, 0x10($v0)
    ctx->f4.u32l = MEM_W(ctx->r2, 0X10);
    // 0x8007E844: add.s       $f10, $f8, $f18
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f10.fl = ctx->f8.fl + ctx->f18.fl;
    // 0x8007E848: lwc1        $f8, 0x14($v0)
    ctx->f8.u32l = MEM_W(ctx->r2, 0X14);
    // 0x8007E84C: add.s       $f6, $f4, $f2
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f6.fl = ctx->f4.fl + ctx->f2.fl;
    // 0x8007E850: swc1        $f10, 0xC($v0)
    MEM_W(0XC, ctx->r2) = ctx->f10.u32l;
    // 0x8007E854: add.s       $f10, $f8, $f0
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f10.fl = ctx->f8.fl + ctx->f0.fl;
    // 0x8007E858: swc1        $f6, 0x10($v0)
    MEM_W(0X10, ctx->r2) = ctx->f6.u32l;
    // 0x8007E85C: swc1        $f10, 0x14($v0)
    MEM_W(0X14, ctx->r2) = ctx->f10.u32l;
    // 0x8007E860: lwc1        $f4, 0xC($t0)
    ctx->f4.u32l = MEM_W(ctx->r8, 0XC);
    // 0x8007E864: lwc1        $f8, 0x10($t0)
    ctx->f8.u32l = MEM_W(ctx->r8, 0X10);
    // 0x8007E868: add.s       $f6, $f4, $f18
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f6.fl = ctx->f4.fl + ctx->f18.fl;
    // 0x8007E86C: lwc1        $f4, 0x14($t0)
    ctx->f4.u32l = MEM_W(ctx->r8, 0X14);
    // 0x8007E870: add.s       $f10, $f8, $f28
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 28);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f28.fl); 
    ctx->f10.fl = ctx->f8.fl + ctx->f28.fl;
    // 0x8007E874: swc1        $f6, 0xC($t0)
    MEM_W(0XC, ctx->r8) = ctx->f6.u32l;
    // 0x8007E878: add.s       $f6, $f4, $f30
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 30);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f30.fl); 
    ctx->f6.fl = ctx->f4.fl + ctx->f30.fl;
    // 0x8007E87C: swc1        $f10, 0x10($t0)
    MEM_W(0X10, ctx->r8) = ctx->f10.u32l;
    // 0x8007E880: swc1        $f6, 0x14($t0)
    MEM_W(0X14, ctx->r8) = ctx->f6.u32l;
    // 0x8007E884: jal         0x8006243C
    // 0x8007E888: lw          $a1, 0x74($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X74);
    func_8006243C(rdram, ctx);
        goto after_9;
    // 0x8007E888: lw          $a1, 0x74($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X74);
    after_9:
    // 0x8007E88C: b           L_8007E8A8
    // 0x8007E890: lw          $ra, 0x44($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X44);
        goto L_8007E8A8;
    // 0x8007E890: lw          $ra, 0x44($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X44);
L_8007E894:
    // 0x8007E894: addiu       $v0, $v0, -0x104
    ctx->r2 = ADD32(ctx->r2, -0X104);
L_8007E898:
    // 0x8007E898: sltu        $at, $v0, $v1
    ctx->r1 = ctx->r2 < ctx->r3 ? 1 : 0;
    // 0x8007E89C: beql        $at, $zero, L_8007DFBC
    if (ctx->r1 == 0) {
        // 0x8007E8A0: lw          $t8, 0x9C($v0)
        ctx->r24 = MEM_W(ctx->r2, 0X9C);
            goto L_8007DFBC;
    }
    goto skip_8;
    // 0x8007E8A0: lw          $t8, 0x9C($v0)
    ctx->r24 = MEM_W(ctx->r2, 0X9C);
    skip_8:
L_8007E8A4:
    // 0x8007E8A4: lw          $ra, 0x44($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X44);
L_8007E8A8:
    // 0x8007E8A8: ldc1        $f20, 0x10($sp)
    CHECK_FR(ctx, 20);
    ctx->f20.u64 = LD(ctx->r29, 0X10);
    // 0x8007E8AC: ldc1        $f22, 0x18($sp)
    CHECK_FR(ctx, 22);
    ctx->f22.u64 = LD(ctx->r29, 0X18);
    // 0x8007E8B0: ldc1        $f24, 0x20($sp)
    CHECK_FR(ctx, 24);
    ctx->f24.u64 = LD(ctx->r29, 0X20);
    // 0x8007E8B4: ldc1        $f26, 0x28($sp)
    CHECK_FR(ctx, 26);
    ctx->f26.u64 = LD(ctx->r29, 0X28);
    // 0x8007E8B8: ldc1        $f28, 0x30($sp)
    CHECK_FR(ctx, 28);
    ctx->f28.u64 = LD(ctx->r29, 0X30);
    // 0x8007E8BC: ldc1        $f30, 0x38($sp)
    CHECK_FR(ctx, 30);
    ctx->f30.u64 = LD(ctx->r29, 0X38);
    // 0x8007E8C0: jr          $ra
    // 0x8007E8C4: addiu       $sp, $sp, 0x88
    ctx->r29 = ADD32(ctx->r29, 0X88);
    return;
    // 0x8007E8C4: addiu       $sp, $sp, 0x88
    ctx->r29 = ADD32(ctx->r29, 0X88);
;}
RECOMP_FUNC void func_8007E8C8(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8007E8C8: addiu       $sp, $sp, -0x28
    ctx->r29 = ADD32(ctx->r29, -0X28);
    // 0x8007E8CC: sw          $ra, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r31;
    // 0x8007E8D0: lw          $a3, 0x1614($a0)
    ctx->r7 = MEM_W(ctx->r4, 0X1614);
    // 0x8007E8D4: lw          $a2, 0x1610($a0)
    ctx->r6 = MEM_W(ctx->r4, 0X1610);
    // 0x8007E8D8: lw          $a1, 0x160C($a0)
    ctx->r5 = MEM_W(ctx->r4, 0X160C);
    // 0x8007E8DC: addiu       $t6, $a0, 0x110
    ctx->r14 = ADD32(ctx->r4, 0X110);
    // 0x8007E8E0: addiu       $t7, $a0, 0x130
    ctx->r15 = ADD32(ctx->r4, 0X130);
    // 0x8007E8E4: addiu       $t8, $a0, 0xF0
    ctx->r24 = ADD32(ctx->r4, 0XF0);
    // 0x8007E8E8: sw          $t8, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r24;
    // 0x8007E8EC: sw          $t7, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r15;
    // 0x8007E8F0: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x8007E8F4: jal         0x8007DF4C
    // 0x8007E8F8: sw          $a0, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r4;
    func_8007DF4C(rdram, ctx);
        goto after_0;
    // 0x8007E8F8: sw          $a0, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r4;
    after_0:
    // 0x8007E8FC: lw          $a0, 0x28($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X28);
    // 0x8007E900: lw          $a1, 0x1654($a0)
    ctx->r5 = MEM_W(ctx->r4, 0X1654);
    // 0x8007E904: lw          $a2, 0x1658($a0)
    ctx->r6 = MEM_W(ctx->r4, 0X1658);
    // 0x8007E908: lw          $a3, 0x165C($a0)
    ctx->r7 = MEM_W(ctx->r4, 0X165C);
    // 0x8007E90C: addiu       $t9, $a0, 0x1F0
    ctx->r25 = ADD32(ctx->r4, 0X1F0);
    // 0x8007E910: addiu       $t0, $a0, 0x1D0
    ctx->r8 = ADD32(ctx->r4, 0X1D0);
    // 0x8007E914: addiu       $t1, $a0, 0x1B0
    ctx->r9 = ADD32(ctx->r4, 0X1B0);
    // 0x8007E918: sw          $t1, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r9;
    // 0x8007E91C: sw          $t0, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r8;
    // 0x8007E920: jal         0x8007DF4C
    // 0x8007E924: sw          $t9, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r25;
    func_8007DF4C(rdram, ctx);
        goto after_1;
    // 0x8007E924: sw          $t9, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r25;
    after_1:
    // 0x8007E928: lw          $ra, 0x24($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X24);
    // 0x8007E92C: addiu       $sp, $sp, 0x28
    ctx->r29 = ADD32(ctx->r29, 0X28);
    // 0x8007E930: jr          $ra
    // 0x8007E934: nop

    return;
    // 0x8007E934: nop

;}
RECOMP_FUNC void func_8007E938(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8007E938: lui         $t6, 0x801C
    ctx->r14 = S32(0X801C << 16);
    // 0x8007E93C: lw          $t6, -0x5C0($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X5C0);
    // 0x8007E940: addiu       $sp, $sp, -0x70
    ctx->r29 = ADD32(ctx->r29, -0X70);
    // 0x8007E944: lui         $v1, 0x801C
    ctx->r3 = S32(0X801C << 16);
    // 0x8007E948: sll         $t7, $t6, 2
    ctx->r15 = S32(ctx->r14 << 2);
    // 0x8007E94C: subu        $t7, $t7, $t6
    ctx->r15 = SUB32(ctx->r15, ctx->r14);
    // 0x8007E950: sll         $t7, $t7, 4
    ctx->r15 = S32(ctx->r15 << 4);
    // 0x8007E954: addu        $t7, $t7, $t6
    ctx->r15 = ADD32(ctx->r15, ctx->r14);
    // 0x8007E958: addiu       $v1, $v1, -0x36C0
    ctx->r3 = ADD32(ctx->r3, -0X36C0);
    // 0x8007E95C: sll         $t7, $t7, 2
    ctx->r15 = S32(ctx->r15 << 2);
    // 0x8007E960: addu        $v0, $v1, $t7
    ctx->r2 = ADD32(ctx->r3, ctx->r15);
    // 0x8007E964: sdc1        $f26, 0x38($sp)
    CHECK_FR(ctx, 26);
    SD(ctx->f26.u64, 0X38, ctx->r29);
    // 0x8007E968: sdc1        $f24, 0x30($sp)
    CHECK_FR(ctx, 24);
    SD(ctx->f24.u64, 0X30, ctx->r29);
    // 0x8007E96C: addiu       $v0, $v0, -0xC4
    ctx->r2 = ADD32(ctx->r2, -0XC4);
    // 0x8007E970: mtc1        $a3, $f24
    ctx->f24.u32l = ctx->r7;
    // 0x8007E974: mtc1        $a2, $f26
    ctx->f26.u32l = ctx->r6;
    // 0x8007E978: sw          $s0, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r16;
    // 0x8007E97C: mtc1        $a1, $f12
    ctx->f12.u32l = ctx->r5;
    // 0x8007E980: sltu        $at, $v0, $v1
    ctx->r1 = ctx->r2 < ctx->r3 ? 1 : 0;
    // 0x8007E984: or          $s0, $a0, $zero
    ctx->r16 = ctx->r4 | 0;
    // 0x8007E988: sw          $ra, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r31;
    // 0x8007E98C: sdc1        $f22, 0x28($sp)
    CHECK_FR(ctx, 22);
    SD(ctx->f22.u64, 0X28, ctx->r29);
    // 0x8007E990: bne         $at, $zero, L_8007EC9C
    if (ctx->r1 != 0) {
        // 0x8007E994: sdc1        $f20, 0x20($sp)
        CHECK_FR(ctx, 20);
    SD(ctx->f20.u64, 0X20, ctx->r29);
            goto L_8007EC9C;
    }
    // 0x8007E994: sdc1        $f20, 0x20($sp)
    CHECK_FR(ctx, 20);
    SD(ctx->f20.u64, 0X20, ctx->r29);
    // 0x8007E998: lui         $at, 0x4140
    ctx->r1 = S32(0X4140 << 16);
    // 0x8007E99C: mtc1        $at, $f14
    ctx->f14.u32l = ctx->r1;
    // 0x8007E9A0: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x8007E9A4: addiu       $a0, $zero, 0xA
    ctx->r4 = ADD32(0, 0XA);
    // 0x8007E9A8: lw          $t8, 0x4C($v0)
    ctx->r24 = MEM_W(ctx->r2, 0X4C);
L_8007E9AC:
    // 0x8007E9AC: bnel        $a0, $t8, L_8007E9CC
    if (ctx->r4 != ctx->r24) {
        // 0x8007E9B0: lw          $t1, 0x5C($v0)
        ctx->r9 = MEM_W(ctx->r2, 0X5C);
            goto L_8007E9CC;
    }
    goto skip_0;
    // 0x8007E9B0: lw          $t1, 0x5C($v0)
    ctx->r9 = MEM_W(ctx->r2, 0X5C);
    skip_0:
    // 0x8007E9B4: lw          $t9, 0xBC($v0)
    ctx->r25 = MEM_W(ctx->r2, 0XBC);
    // 0x8007E9B8: beql        $t9, $zero, L_8007E9D8
    if (ctx->r25 == 0) {
        // 0x8007E9BC: lwc1        $f4, 0x40($v0)
        ctx->f4.u32l = MEM_W(ctx->r2, 0X40);
            goto L_8007E9D8;
    }
    goto skip_1;
    // 0x8007E9BC: lwc1        $f4, 0x40($v0)
    ctx->f4.u32l = MEM_W(ctx->r2, 0X40);
    skip_1:
    // 0x8007E9C0: b           L_8007EC90
    // 0x8007E9C4: addiu       $v0, $v0, -0xC4
    ctx->r2 = ADD32(ctx->r2, -0XC4);
        goto L_8007EC90;
    // 0x8007E9C4: addiu       $v0, $v0, -0xC4
    ctx->r2 = ADD32(ctx->r2, -0XC4);
    // 0x8007E9C8: lw          $t1, 0x5C($v0)
    ctx->r9 = MEM_W(ctx->r2, 0X5C);
L_8007E9CC:
    // 0x8007E9CC: bnel        $a1, $t1, L_8007EC90
    if (ctx->r5 != ctx->r9) {
        // 0x8007E9D0: addiu       $v0, $v0, -0xC4
        ctx->r2 = ADD32(ctx->r2, -0XC4);
            goto L_8007EC90;
    }
    goto skip_2;
    // 0x8007E9D0: addiu       $v0, $v0, -0xC4
    ctx->r2 = ADD32(ctx->r2, -0XC4);
    skip_2:
    // 0x8007E9D4: lwc1        $f4, 0x40($v0)
    ctx->f4.u32l = MEM_W(ctx->r2, 0X40);
L_8007E9D8:
    // 0x8007E9D8: lwc1        $f6, 0x0($v0)
    ctx->f6.u32l = MEM_W(ctx->r2, 0X0);
    // 0x8007E9DC: lwc1        $f8, 0x8($v0)
    ctx->f8.u32l = MEM_W(ctx->r2, 0X8);
    // 0x8007E9E0: add.s       $f0, $f4, $f14
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f0.fl = ctx->f4.fl + ctx->f14.fl;
    // 0x8007E9E4: sub.s       $f18, $f12, $f6
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f18.fl = ctx->f12.fl - ctx->f6.fl;
    // 0x8007E9E8: mul.s       $f0, $f0, $f0
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f0.fl = MUL_S(ctx->f0.fl, ctx->f0.fl);
    // 0x8007E9EC: sub.s       $f22, $f24, $f8
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f24.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f22.fl = ctx->f24.fl - ctx->f8.fl;
    // 0x8007E9F0: mul.s       $f10, $f18, $f18
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f10.fl = MUL_S(ctx->f18.fl, ctx->f18.fl);
    // 0x8007E9F4: nop

    // 0x8007E9F8: mul.s       $f4, $f22, $f22
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f4.fl = MUL_S(ctx->f22.fl, ctx->f22.fl);
    // 0x8007E9FC: add.s       $f2, $f10, $f4
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f2.fl = ctx->f10.fl + ctx->f4.fl;
    // 0x8007EA00: c.lt.s      $f0, $f2
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    c1cs = ctx->f0.fl < ctx->f2.fl;
    // 0x8007EA04: nop

    // 0x8007EA08: bc1t        L_8007EC8C
    if (c1cs) {
        // 0x8007EA0C: nop
    
            goto L_8007EC8C;
    }
    // 0x8007EA0C: nop

    // 0x8007EA10: lwc1        $f6, 0x4($v0)
    ctx->f6.u32l = MEM_W(ctx->r2, 0X4);
    // 0x8007EA14: sub.s       $f16, $f26, $f6
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f26.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f16.fl = ctx->f26.fl - ctx->f6.fl;
    // 0x8007EA18: mul.s       $f8, $f16, $f16
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f8.fl = MUL_S(ctx->f16.fl, ctx->f16.fl);
    // 0x8007EA1C: add.s       $f20, $f2, $f8
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f20.fl = ctx->f2.fl + ctx->f8.fl;
    // 0x8007EA20: c.lt.s      $f20, $f0
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 0);
    c1cs = ctx->f20.fl < ctx->f0.fl;
    // 0x8007EA24: nop

    // 0x8007EA28: bc1fl       L_8007EC90
    if (!c1cs) {
        // 0x8007EA2C: addiu       $v0, $v0, -0xC4
        ctx->r2 = ADD32(ctx->r2, -0XC4);
            goto L_8007EC90;
    }
    goto skip_3;
    // 0x8007EA2C: addiu       $v0, $v0, -0xC4
    ctx->r2 = ADD32(ctx->r2, -0XC4);
    skip_3:
    // 0x8007EA30: mov.s       $f12, $f20
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 20);
    ctx->f12.fl = ctx->f20.fl;
    // 0x8007EA34: sw          $v0, 0x6C($sp)
    MEM_W(0X6C, ctx->r29) = ctx->r2;
    // 0x8007EA38: swc1        $f16, 0x64($sp)
    MEM_W(0X64, ctx->r29) = ctx->f16.u32l;
    // 0x8007EA3C: jal         0x800C7010
    // 0x8007EA40: swc1        $f18, 0x68($sp)
    MEM_W(0X68, ctx->r29) = ctx->f18.u32l;
    _nsqrtf(rdram, ctx);
        goto after_0;
    // 0x8007EA40: swc1        $f18, 0x68($sp)
    MEM_W(0X68, ctx->r29) = ctx->f18.u32l;
    after_0:
    // 0x8007EA44: lui         $at, 0x4140
    ctx->r1 = S32(0X4140 << 16);
    // 0x8007EA48: mtc1        $at, $f14
    ctx->f14.u32l = ctx->r1;
    // 0x8007EA4C: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x8007EA50: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x8007EA54: lwc1        $f18, 0x68($sp)
    ctx->f18.u32l = MEM_W(ctx->r29, 0X68);
    // 0x8007EA58: lw          $v0, 0x6C($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X6C);
    // 0x8007EA5C: div.s       $f12, $f6, $f0
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f12.fl = DIV_S(ctx->f6.fl, ctx->f0.fl);
    // 0x8007EA60: lwc1        $f16, 0x64($sp)
    ctx->f16.u32l = MEM_W(ctx->r29, 0X64);
    // 0x8007EA64: lwc1        $f10, 0x40($v0)
    ctx->f10.u32l = MEM_W(ctx->r2, 0X40);
    // 0x8007EA68: lw          $t2, 0x4C($v0)
    ctx->r10 = MEM_W(ctx->r2, 0X4C);
    // 0x8007EA6C: addiu       $a0, $zero, 0xA
    ctx->r4 = ADD32(0, 0XA);
    // 0x8007EA70: add.s       $f4, $f14, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f4.fl = ctx->f14.fl + ctx->f10.fl;
    // 0x8007EA74: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x8007EA78: addiu       $t3, $zero, 0x1
    ctx->r11 = ADD32(0, 0X1);
    // 0x8007EA7C: lui         $at, 0x800D
    ctx->r1 = S32(0X800D << 16);
    // 0x8007EA80: sub.s       $f2, $f4, $f0
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f2.fl = ctx->f4.fl - ctx->f0.fl;
    // 0x8007EA84: mul.s       $f18, $f18, $f12
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f18.fl = MUL_S(ctx->f18.fl, ctx->f12.fl);
    // 0x8007EA88: nop

    // 0x8007EA8C: mul.s       $f16, $f16, $f12
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f16.fl = MUL_S(ctx->f16.fl, ctx->f12.fl);
    // 0x8007EA90: nop

    // 0x8007EA94: mul.s       $f22, $f22, $f12
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f22.fl = MUL_S(ctx->f22.fl, ctx->f12.fl);
    // 0x8007EA98: bne         $a0, $t2, L_8007EAAC
    if (ctx->r4 != ctx->r10) {
        // 0x8007EA9C: nop
    
            goto L_8007EAAC;
    }
    // 0x8007EA9C: nop

    // 0x8007EAA0: sw          $t3, 0x16D8($s0)
    MEM_W(0X16D8, ctx->r16) = ctx->r11;
    // 0x8007EAA4: b           L_8007EB14
    // 0x8007EAA8: mov.s       $f20, $f2
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 2);
    ctx->f20.fl = ctx->f2.fl;
        goto L_8007EB14;
    // 0x8007EAA8: mov.s       $f20, $f2
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 2);
    ctx->f20.fl = ctx->f2.fl;
L_8007EAAC:
    // 0x8007EAAC: sw          $zero, 0x16D8($s0)
    MEM_W(0X16D8, ctx->r16) = 0;
    // 0x8007EAB0: lwc1        $f8, 0x49B8($at)
    ctx->f8.u32l = MEM_W(ctx->r1, 0X49B8);
    // 0x8007EAB4: lwc1        $f10, 0x0($v0)
    ctx->f10.u32l = MEM_W(ctx->r2, 0X0);
    // 0x8007EAB8: lwc1        $f6, 0x4($v0)
    ctx->f6.u32l = MEM_W(ctx->r2, 0X4);
    // 0x8007EABC: mul.s       $f20, $f2, $f8
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f20.fl = MUL_S(ctx->f2.fl, ctx->f8.fl);
    // 0x8007EAC0: sub.s       $f2, $f2, $f20
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f2.fl = ctx->f2.fl - ctx->f20.fl;
    // 0x8007EAC4: mul.s       $f0, $f2, $f18
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f0.fl = MUL_S(ctx->f2.fl, ctx->f18.fl);
    // 0x8007EAC8: nop

    // 0x8007EACC: mul.s       $f12, $f2, $f16
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f12.fl = MUL_S(ctx->f2.fl, ctx->f16.fl);
    // 0x8007EAD0: sub.s       $f4, $f10, $f0
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f4.fl = ctx->f10.fl - ctx->f0.fl;
    // 0x8007EAD4: mul.s       $f14, $f2, $f22
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f14.fl = MUL_S(ctx->f2.fl, ctx->f22.fl);
    // 0x8007EAD8: lwc1        $f10, 0x8($v0)
    ctx->f10.u32l = MEM_W(ctx->r2, 0X8);
    // 0x8007EADC: sub.s       $f8, $f6, $f12
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f8.fl = ctx->f6.fl - ctx->f12.fl;
    // 0x8007EAE0: lwc1        $f6, 0x18($v0)
    ctx->f6.u32l = MEM_W(ctx->r2, 0X18);
    // 0x8007EAE4: swc1        $f4, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->f4.u32l;
    // 0x8007EAE8: swc1        $f8, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->f8.u32l;
    // 0x8007EAEC: sub.s       $f4, $f10, $f14
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f4.fl = ctx->f10.fl - ctx->f14.fl;
    // 0x8007EAF0: lwc1        $f10, 0x1C($v0)
    ctx->f10.u32l = MEM_W(ctx->r2, 0X1C);
    // 0x8007EAF4: sub.s       $f8, $f6, $f0
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f8.fl = ctx->f6.fl - ctx->f0.fl;
    // 0x8007EAF8: lwc1        $f6, 0x20($v0)
    ctx->f6.u32l = MEM_W(ctx->r2, 0X20);
    // 0x8007EAFC: swc1        $f4, 0x8($v0)
    MEM_W(0X8, ctx->r2) = ctx->f4.u32l;
    // 0x8007EB00: sub.s       $f4, $f10, $f12
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f4.fl = ctx->f10.fl - ctx->f12.fl;
    // 0x8007EB04: swc1        $f8, 0x18($v0)
    MEM_W(0X18, ctx->r2) = ctx->f8.u32l;
    // 0x8007EB08: sub.s       $f8, $f6, $f14
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f8.fl = ctx->f6.fl - ctx->f14.fl;
    // 0x8007EB0C: swc1        $f4, 0x1C($v0)
    MEM_W(0X1C, ctx->r2) = ctx->f4.u32l;
    // 0x8007EB10: swc1        $f8, 0x20($v0)
    MEM_W(0X20, ctx->r2) = ctx->f8.u32l;
L_8007EB14:
    // 0x8007EB14: mul.s       $f24, $f20, $f18
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f24.fl = MUL_S(ctx->f20.fl, ctx->f18.fl);
    // 0x8007EB18: lw          $v1, 0x80($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X80);
    // 0x8007EB1C: neg.s       $f4, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f18.fl); 
    ctx->f4.fl = -ctx->f18.fl;
    // 0x8007EB20: mul.s       $f26, $f20, $f16
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f26.fl = MUL_S(ctx->f20.fl, ctx->f16.fl);
    // 0x8007EB24: nop

    // 0x8007EB28: mul.s       $f10, $f20, $f22
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f10.fl = MUL_S(ctx->f20.fl, ctx->f22.fl);
    // 0x8007EB2C: swc1        $f10, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->f10.u32l;
    // 0x8007EB30: lwc1        $f0, 0xC($v1)
    ctx->f0.u32l = MEM_W(ctx->r3, 0XC);
    // 0x8007EB34: lwc1        $f2, 0x10($v1)
    ctx->f2.u32l = MEM_W(ctx->r3, 0X10);
    // 0x8007EB38: lwc1        $f12, 0x14($v1)
    ctx->f12.u32l = MEM_W(ctx->r3, 0X14);
    // 0x8007EB3C: mul.s       $f6, $f4, $f0
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f6.fl = MUL_S(ctx->f4.fl, ctx->f0.fl);
    // 0x8007EB40: nop

    // 0x8007EB44: mul.s       $f8, $f16, $f2
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f8.fl = MUL_S(ctx->f16.fl, ctx->f2.fl);
    // 0x8007EB48: sub.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = ctx->f6.fl - ctx->f8.fl;
    // 0x8007EB4C: mul.s       $f4, $f22, $f12
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f4.fl = MUL_S(ctx->f22.fl, ctx->f12.fl);
    // 0x8007EB50: lwc1        $f6, 0xC50($s0)
    ctx->f6.u32l = MEM_W(ctx->r16, 0XC50);
    // 0x8007EB54: sub.s       $f20, $f10, $f4
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f20.fl = ctx->f10.fl - ctx->f4.fl;
    // 0x8007EB58: c.lt.s      $f6, $f20
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 20);
    c1cs = ctx->f6.fl < ctx->f20.fl;
    // 0x8007EB5C: nop

    // 0x8007EB60: bc1f        L_8007EC04
    if (!c1cs) {
        // 0x8007EB64: nop
    
            goto L_8007EC04;
    }
    // 0x8007EB64: nop

    // 0x8007EB68: lw          $t4, 0x4C($v0)
    ctx->r12 = MEM_W(ctx->r2, 0X4C);
    // 0x8007EB6C: lui         $at, 0x3F00
    ctx->r1 = S32(0X3F00 << 16);
    // 0x8007EB70: bnel        $a0, $t4, L_8007EBEC
    if (ctx->r4 != ctx->r12) {
        // 0x8007EB74: swc1        $f20, 0xC50($s0)
        MEM_W(0XC50, ctx->r16) = ctx->f20.u32l;
            goto L_8007EBEC;
    }
    goto skip_4;
    // 0x8007EB74: swc1        $f20, 0xC50($s0)
    MEM_W(0XC50, ctx->r16) = ctx->f20.u32l;
    skip_4:
    // 0x8007EB78: lwc1        $f8, 0x16A0($s0)
    ctx->f8.u32l = MEM_W(ctx->r16, 0X16A0);
    // 0x8007EB7C: mtc1        $at, $f10
    ctx->f10.u32l = ctx->r1;
    // 0x8007EB80: nop

    // 0x8007EB84: mul.s       $f4, $f8, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f4.fl = MUL_S(ctx->f8.fl, ctx->f10.fl);
    // 0x8007EB88: c.le.s      $f4, $f20
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 20);
    c1cs = ctx->f4.fl <= ctx->f20.fl;
    // 0x8007EB8C: nop

    // 0x8007EB90: bc1fl       L_8007EBEC
    if (!c1cs) {
        // 0x8007EB94: swc1        $f20, 0xC50($s0)
        MEM_W(0XC50, ctx->r16) = ctx->f20.u32l;
            goto L_8007EBEC;
    }
    goto skip_5;
    // 0x8007EB94: swc1        $f20, 0xC50($s0)
    MEM_W(0XC50, ctx->r16) = ctx->f20.u32l;
    skip_5:
    // 0x8007EB98: sw          $a1, 0x16D8($s0)
    MEM_W(0X16D8, ctx->r16) = ctx->r5;
    // 0x8007EB9C: lw          $t5, 0xBC($v0)
    ctx->r13 = MEM_W(ctx->r2, 0XBC);
    // 0x8007EBA0: addiu       $t6, $zero, 0x1
    ctx->r14 = ADD32(0, 0X1);
    // 0x8007EBA4: bnel        $t5, $zero, L_8007EBEC
    if (ctx->r13 != 0) {
        // 0x8007EBA8: swc1        $f20, 0xC50($s0)
        MEM_W(0XC50, ctx->r16) = ctx->f20.u32l;
            goto L_8007EBEC;
    }
    goto skip_6;
    // 0x8007EBA8: swc1        $f20, 0xC50($s0)
    MEM_W(0XC50, ctx->r16) = ctx->f20.u32l;
    skip_6:
    // 0x8007EBAC: sw          $t6, 0xBC($v0)
    MEM_W(0XBC, ctx->r2) = ctx->r14;
    // 0x8007EBB0: lwc1        $f6, 0x10($v1)
    ctx->f6.u32l = MEM_W(ctx->r3, 0X10);
    // 0x8007EBB4: lw          $a3, 0xC($v1)
    ctx->r7 = MEM_W(ctx->r3, 0XC);
    // 0x8007EBB8: lwc1        $f12, 0x0($v0)
    ctx->f12.u32l = MEM_W(ctx->r2, 0X0);
    // 0x8007EBBC: lwc1        $f14, 0x4($v0)
    ctx->f14.u32l = MEM_W(ctx->r2, 0X4);
    // 0x8007EBC0: lw          $a2, 0x8($v0)
    ctx->r6 = MEM_W(ctx->r2, 0X8);
    // 0x8007EBC4: swc1        $f6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f6.u32l;
    // 0x8007EBC8: lwc1        $f8, 0x14($v1)
    ctx->f8.u32l = MEM_W(ctx->r3, 0X14);
    // 0x8007EBCC: swc1        $f18, 0x68($sp)
    MEM_W(0X68, ctx->r29) = ctx->f18.u32l;
    // 0x8007EBD0: swc1        $f16, 0x64($sp)
    MEM_W(0X64, ctx->r29) = ctx->f16.u32l;
    // 0x8007EBD4: jal         0x800B490C
    // 0x8007EBD8: swc1        $f8, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->f8.u32l;
    func_800B490C(rdram, ctx);
        goto after_1;
    // 0x8007EBD8: swc1        $f8, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->f8.u32l;
    after_1:
    // 0x8007EBDC: lw          $v1, 0x80($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X80);
    // 0x8007EBE0: lwc1        $f16, 0x64($sp)
    ctx->f16.u32l = MEM_W(ctx->r29, 0X64);
    // 0x8007EBE4: lwc1        $f18, 0x68($sp)
    ctx->f18.u32l = MEM_W(ctx->r29, 0X68);
    // 0x8007EBE8: swc1        $f20, 0xC50($s0)
    MEM_W(0XC50, ctx->r16) = ctx->f20.u32l;
L_8007EBEC:
    // 0x8007EBEC: swc1        $f18, 0x15B4($s0)
    MEM_W(0X15B4, ctx->r16) = ctx->f18.u32l;
    // 0x8007EBF0: swc1        $f16, 0x15B8($s0)
    MEM_W(0X15B8, ctx->r16) = ctx->f16.u32l;
    // 0x8007EBF4: swc1        $f22, 0x15BC($s0)
    MEM_W(0X15BC, ctx->r16) = ctx->f22.u32l;
    // 0x8007EBF8: lwc1        $f12, 0x14($v1)
    ctx->f12.u32l = MEM_W(ctx->r3, 0X14);
    // 0x8007EBFC: lwc1        $f2, 0x10($v1)
    ctx->f2.u32l = MEM_W(ctx->r3, 0X10);
    // 0x8007EC00: lwc1        $f0, 0xC($v1)
    ctx->f0.u32l = MEM_W(ctx->r3, 0XC);
L_8007EC04:
    // 0x8007EC04: lwc1        $f14, 0x48($sp)
    ctx->f14.u32l = MEM_W(ctx->r29, 0X48);
    // 0x8007EC08: add.s       $f10, $f0, $f24
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 24);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f24.fl); 
    ctx->f10.fl = ctx->f0.fl + ctx->f24.fl;
    // 0x8007EC0C: lw          $v0, 0x84($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X84);
    // 0x8007EC10: lw          $t0, 0x88($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X88);
    // 0x8007EC14: add.s       $f4, $f2, $f26
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 26);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f26.fl); 
    ctx->f4.fl = ctx->f2.fl + ctx->f26.fl;
    // 0x8007EC18: swc1        $f10, 0xC($v1)
    MEM_W(0XC, ctx->r3) = ctx->f10.u32l;
    // 0x8007EC1C: mfc1        $a1, $f24
    ctx->r5 = (int32_t)ctx->f24.u32l;
    // 0x8007EC20: add.s       $f6, $f12, $f14
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f6.fl = ctx->f12.fl + ctx->f14.fl;
    // 0x8007EC24: swc1        $f4, 0x10($v1)
    MEM_W(0X10, ctx->r3) = ctx->f4.u32l;
    // 0x8007EC28: mfc1        $a2, $f26
    ctx->r6 = (int32_t)ctx->f26.u32l;
    // 0x8007EC2C: mfc1        $a3, $f14
    ctx->r7 = (int32_t)ctx->f14.u32l;
    // 0x8007EC30: swc1        $f6, 0x14($v1)
    MEM_W(0X14, ctx->r3) = ctx->f6.u32l;
    // 0x8007EC34: lwc1        $f8, 0xC($v0)
    ctx->f8.u32l = MEM_W(ctx->r2, 0XC);
    // 0x8007EC38: lwc1        $f4, 0x10($v0)
    ctx->f4.u32l = MEM_W(ctx->r2, 0X10);
    // 0x8007EC3C: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x8007EC40: add.s       $f10, $f8, $f24
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 24);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f24.fl); 
    ctx->f10.fl = ctx->f8.fl + ctx->f24.fl;
    // 0x8007EC44: lwc1        $f8, 0x14($v0)
    ctx->f8.u32l = MEM_W(ctx->r2, 0X14);
    // 0x8007EC48: add.s       $f6, $f4, $f26
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 26);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f26.fl); 
    ctx->f6.fl = ctx->f4.fl + ctx->f26.fl;
    // 0x8007EC4C: swc1        $f10, 0xC($v0)
    MEM_W(0XC, ctx->r2) = ctx->f10.u32l;
    // 0x8007EC50: add.s       $f10, $f8, $f14
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f10.fl = ctx->f8.fl + ctx->f14.fl;
    // 0x8007EC54: swc1        $f6, 0x10($v0)
    MEM_W(0X10, ctx->r2) = ctx->f6.u32l;
    // 0x8007EC58: swc1        $f10, 0x14($v0)
    MEM_W(0X14, ctx->r2) = ctx->f10.u32l;
    // 0x8007EC5C: lwc1        $f4, 0xC($t0)
    ctx->f4.u32l = MEM_W(ctx->r8, 0XC);
    // 0x8007EC60: lwc1        $f8, 0x10($t0)
    ctx->f8.u32l = MEM_W(ctx->r8, 0X10);
    // 0x8007EC64: add.s       $f6, $f4, $f24
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 24);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f24.fl); 
    ctx->f6.fl = ctx->f4.fl + ctx->f24.fl;
    // 0x8007EC68: lwc1        $f4, 0x14($t0)
    ctx->f4.u32l = MEM_W(ctx->r8, 0X14);
    // 0x8007EC6C: add.s       $f10, $f8, $f26
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 26);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f26.fl); 
    ctx->f10.fl = ctx->f8.fl + ctx->f26.fl;
    // 0x8007EC70: swc1        $f6, 0xC($t0)
    MEM_W(0XC, ctx->r8) = ctx->f6.u32l;
    // 0x8007EC74: add.s       $f6, $f4, $f14
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f6.fl = ctx->f4.fl + ctx->f14.fl;
    // 0x8007EC78: swc1        $f10, 0x10($t0)
    MEM_W(0X10, ctx->r8) = ctx->f10.u32l;
    // 0x8007EC7C: jal         0x8006243C
    // 0x8007EC80: swc1        $f6, 0x14($t0)
    MEM_W(0X14, ctx->r8) = ctx->f6.u32l;
    func_8006243C(rdram, ctx);
        goto after_2;
    // 0x8007EC80: swc1        $f6, 0x14($t0)
    MEM_W(0X14, ctx->r8) = ctx->f6.u32l;
    after_2:
    // 0x8007EC84: b           L_8007ECA0
    // 0x8007EC88: lw          $ra, 0x44($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X44);
        goto L_8007ECA0;
    // 0x8007EC88: lw          $ra, 0x44($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X44);
L_8007EC8C:
    // 0x8007EC8C: addiu       $v0, $v0, -0xC4
    ctx->r2 = ADD32(ctx->r2, -0XC4);
L_8007EC90:
    // 0x8007EC90: sltu        $at, $v0, $v1
    ctx->r1 = ctx->r2 < ctx->r3 ? 1 : 0;
    // 0x8007EC94: beql        $at, $zero, L_8007E9AC
    if (ctx->r1 == 0) {
        // 0x8007EC98: lw          $t8, 0x4C($v0)
        ctx->r24 = MEM_W(ctx->r2, 0X4C);
            goto L_8007E9AC;
    }
    goto skip_7;
    // 0x8007EC98: lw          $t8, 0x4C($v0)
    ctx->r24 = MEM_W(ctx->r2, 0X4C);
    skip_7:
L_8007EC9C:
    // 0x8007EC9C: lw          $ra, 0x44($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X44);
L_8007ECA0:
    // 0x8007ECA0: ldc1        $f20, 0x20($sp)
    CHECK_FR(ctx, 20);
    ctx->f20.u64 = LD(ctx->r29, 0X20);
    // 0x8007ECA4: ldc1        $f22, 0x28($sp)
    CHECK_FR(ctx, 22);
    ctx->f22.u64 = LD(ctx->r29, 0X28);
    // 0x8007ECA8: ldc1        $f24, 0x30($sp)
    CHECK_FR(ctx, 24);
    ctx->f24.u64 = LD(ctx->r29, 0X30);
    // 0x8007ECAC: ldc1        $f26, 0x38($sp)
    CHECK_FR(ctx, 26);
    ctx->f26.u64 = LD(ctx->r29, 0X38);
    // 0x8007ECB0: lw          $s0, 0x40($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X40);
    // 0x8007ECB4: jr          $ra
    // 0x8007ECB8: addiu       $sp, $sp, 0x70
    ctx->r29 = ADD32(ctx->r29, 0X70);
    return;
    // 0x8007ECB8: addiu       $sp, $sp, 0x70
    ctx->r29 = ADD32(ctx->r29, 0X70);
;}
RECOMP_FUNC void func_8007ECBC(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8007ECBC: addiu       $sp, $sp, -0x28
    ctx->r29 = ADD32(ctx->r29, -0X28);
    // 0x8007ECC0: sw          $ra, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r31;
    // 0x8007ECC4: lw          $a3, 0x1614($a0)
    ctx->r7 = MEM_W(ctx->r4, 0X1614);
    // 0x8007ECC8: lw          $a2, 0x1610($a0)
    ctx->r6 = MEM_W(ctx->r4, 0X1610);
    // 0x8007ECCC: lw          $a1, 0x160C($a0)
    ctx->r5 = MEM_W(ctx->r4, 0X160C);
    // 0x8007ECD0: addiu       $t6, $a0, 0x110
    ctx->r14 = ADD32(ctx->r4, 0X110);
    // 0x8007ECD4: addiu       $t7, $a0, 0x130
    ctx->r15 = ADD32(ctx->r4, 0X130);
    // 0x8007ECD8: addiu       $t8, $a0, 0xF0
    ctx->r24 = ADD32(ctx->r4, 0XF0);
    // 0x8007ECDC: sw          $t8, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r24;
    // 0x8007ECE0: sw          $t7, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r15;
    // 0x8007ECE4: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x8007ECE8: jal         0x8007E938
    // 0x8007ECEC: sw          $a0, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r4;
    func_8007E938(rdram, ctx);
        goto after_0;
    // 0x8007ECEC: sw          $a0, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r4;
    after_0:
    // 0x8007ECF0: lw          $a0, 0x28($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X28);
    // 0x8007ECF4: lw          $a1, 0x1654($a0)
    ctx->r5 = MEM_W(ctx->r4, 0X1654);
    // 0x8007ECF8: lw          $a2, 0x1658($a0)
    ctx->r6 = MEM_W(ctx->r4, 0X1658);
    // 0x8007ECFC: lw          $a3, 0x165C($a0)
    ctx->r7 = MEM_W(ctx->r4, 0X165C);
    // 0x8007ED00: addiu       $t9, $a0, 0x1F0
    ctx->r25 = ADD32(ctx->r4, 0X1F0);
    // 0x8007ED04: addiu       $t0, $a0, 0x1D0
    ctx->r8 = ADD32(ctx->r4, 0X1D0);
    // 0x8007ED08: addiu       $t1, $a0, 0x1B0
    ctx->r9 = ADD32(ctx->r4, 0X1B0);
    // 0x8007ED0C: sw          $t1, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r9;
    // 0x8007ED10: sw          $t0, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r8;
    // 0x8007ED14: jal         0x8007E938
    // 0x8007ED18: sw          $t9, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r25;
    func_8007E938(rdram, ctx);
        goto after_1;
    // 0x8007ED18: sw          $t9, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r25;
    after_1:
    // 0x8007ED1C: lw          $ra, 0x24($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X24);
    // 0x8007ED20: addiu       $sp, $sp, 0x28
    ctx->r29 = ADD32(ctx->r29, 0X28);
    // 0x8007ED24: jr          $ra
    // 0x8007ED28: nop

    return;
    // 0x8007ED28: nop

;}
RECOMP_FUNC void func_8007ED2C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8007ED2C: addiu       $sp, $sp, -0x78
    ctx->r29 = ADD32(ctx->r29, -0X78);
    // 0x8007ED30: sdc1        $f24, 0x28($sp)
    CHECK_FR(ctx, 24);
    SD(ctx->f24.u64, 0X28, ctx->r29);
    // 0x8007ED34: mtc1        $a3, $f24
    ctx->f24.u32l = ctx->r7;
    // 0x8007ED38: sw          $s0, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r16;
    // 0x8007ED3C: or          $s0, $a2, $zero
    ctx->r16 = ctx->r6 | 0;
    // 0x8007ED40: sw          $ra, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r31;
    // 0x8007ED44: sdc1        $f22, 0x20($sp)
    CHECK_FR(ctx, 22);
    SD(ctx->f22.u64, 0X20, ctx->r29);
    // 0x8007ED48: bltz        $a0, L_8007EF64
    if (SIGNED(ctx->r4) < 0) {
        // 0x8007ED4C: sdc1        $f20, 0x18($sp)
        CHECK_FR(ctx, 20);
    SD(ctx->f20.u64, 0X18, ctx->r29);
            goto L_8007EF64;
    }
    // 0x8007ED4C: sdc1        $f20, 0x18($sp)
    CHECK_FR(ctx, 20);
    SD(ctx->f20.u64, 0X18, ctx->r29);
    // 0x8007ED50: addu        $v1, $a1, $a0
    ctx->r3 = ADD32(ctx->r5, ctx->r4);
    // 0x8007ED54: lui         $a1, 0x801C
    ctx->r5 = S32(0X801C << 16);
    // 0x8007ED58: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x8007ED5C: lwc1        $f18, -0x5C20($at)
    ctx->f18.u32l = MEM_W(ctx->r1, -0X5C20);
    // 0x8007ED60: addiu       $a1, $a1, -0x4EC8
    ctx->r5 = ADD32(ctx->r5, -0X4EC8);
    // 0x8007ED64: lwc1        $f22, 0x88($sp)
    ctx->f22.u32l = MEM_W(ctx->r29, 0X88);
    // 0x8007ED68: lwc1        $f20, 0x8C($sp)
    ctx->f20.u32l = MEM_W(ctx->r29, 0X8C);
    // 0x8007ED6C: addiu       $a2, $zero, 0x18
    ctx->r6 = ADD32(0, 0X18);
L_8007ED70:
    // 0x8007ED70: lbu         $t6, 0x0($v1)
    ctx->r14 = MEM_BU(ctx->r3, 0X0);
    // 0x8007ED74: addiu       $a0, $a0, -0x1
    ctx->r4 = ADD32(ctx->r4, -0X1);
    // 0x8007ED78: multu       $t6, $a2
    result = U64(U32(ctx->r14)) * U64(U32(ctx->r6)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x8007ED7C: mflo        $t7
    ctx->r15 = lo;
    // 0x8007ED80: addu        $v0, $a1, $t7
    ctx->r2 = ADD32(ctx->r5, ctx->r15);
    // 0x8007ED84: lwc1        $f4, 0x0($v0)
    ctx->f4.u32l = MEM_W(ctx->r2, 0X0);
    // 0x8007ED88: lwc1        $f6, 0x8($v0)
    ctx->f6.u32l = MEM_W(ctx->r2, 0X8);
    // 0x8007ED8C: sub.s       $f2, $f24, $f4
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f24.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f2.fl = ctx->f24.fl - ctx->f4.fl;
    // 0x8007ED90: sub.s       $f14, $f20, $f6
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f14.fl = ctx->f20.fl - ctx->f6.fl;
    // 0x8007ED94: mul.s       $f8, $f2, $f2
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f8.fl = MUL_S(ctx->f2.fl, ctx->f2.fl);
    // 0x8007ED98: nop

    // 0x8007ED9C: mul.s       $f10, $f14, $f14
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f10.fl = MUL_S(ctx->f14.fl, ctx->f14.fl);
    // 0x8007EDA0: add.s       $f0, $f8, $f10
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f0.fl = ctx->f8.fl + ctx->f10.fl;
    // 0x8007EDA4: c.lt.s      $f18, $f0
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 0);
    c1cs = ctx->f18.fl < ctx->f0.fl;
    // 0x8007EDA8: nop

    // 0x8007EDAC: bc1t        L_8007EF5C
    if (c1cs) {
        // 0x8007EDB0: nop
    
            goto L_8007EF5C;
    }
    // 0x8007EDB0: nop

    // 0x8007EDB4: lwc1        $f4, 0x4($v0)
    ctx->f4.u32l = MEM_W(ctx->r2, 0X4);
    // 0x8007EDB8: sub.s       $f16, $f22, $f4
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f16.fl = ctx->f22.fl - ctx->f4.fl;
    // 0x8007EDBC: mul.s       $f6, $f16, $f16
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f6.fl = MUL_S(ctx->f16.fl, ctx->f16.fl);
    // 0x8007EDC0: add.s       $f12, $f0, $f6
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f12.fl = ctx->f0.fl + ctx->f6.fl;
    // 0x8007EDC4: c.lt.s      $f12, $f18
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 18);
    c1cs = ctx->f12.fl < ctx->f18.fl;
    // 0x8007EDC8: nop

    // 0x8007EDCC: bc1f        L_8007EF5C
    if (!c1cs) {
        // 0x8007EDD0: nop
    
            goto L_8007EF5C;
    }
    // 0x8007EDD0: nop

    // 0x8007EDD4: swc1        $f2, 0x70($sp)
    MEM_W(0X70, ctx->r29) = ctx->f2.u32l;
    // 0x8007EDD8: swc1        $f14, 0x68($sp)
    MEM_W(0X68, ctx->r29) = ctx->f14.u32l;
    // 0x8007EDDC: jal         0x800C7010
    // 0x8007EDE0: swc1        $f16, 0x6C($sp)
    MEM_W(0X6C, ctx->r29) = ctx->f16.u32l;
    _nsqrtf(rdram, ctx);
        goto after_0;
    // 0x8007EDE0: swc1        $f16, 0x6C($sp)
    MEM_W(0X6C, ctx->r29) = ctx->f16.u32l;
    after_0:
    // 0x8007EDE4: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x8007EDE8: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x8007EDEC: lwc1        $f2, 0x70($sp)
    ctx->f2.u32l = MEM_W(ctx->r29, 0X70);
    // 0x8007EDF0: lui         $at, 0x4214
    ctx->r1 = S32(0X4214 << 16);
    // 0x8007EDF4: div.s       $f20, $f8, $f0
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f20.fl = DIV_S(ctx->f8.fl, ctx->f0.fl);
    // 0x8007EDF8: mtc1        $at, $f10
    ctx->f10.u32l = ctx->r1;
    // 0x8007EDFC: lwc1        $f16, 0x6C($sp)
    ctx->f16.u32l = MEM_W(ctx->r29, 0X6C);
    // 0x8007EE00: lwc1        $f14, 0x68($sp)
    ctx->f14.u32l = MEM_W(ctx->r29, 0X68);
    // 0x8007EE04: sub.s       $f18, $f10, $f0
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f18.fl = ctx->f10.fl - ctx->f0.fl;
    // 0x8007EE08: lw          $v1, 0x90($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X90);
    // 0x8007EE0C: mul.s       $f2, $f2, $f20
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f2.fl = MUL_S(ctx->f2.fl, ctx->f20.fl);
    // 0x8007EE10: nop

    // 0x8007EE14: mul.s       $f22, $f2, $f18
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f22.fl = MUL_S(ctx->f2.fl, ctx->f18.fl);
    // 0x8007EE18: nop

    // 0x8007EE1C: mul.s       $f16, $f16, $f20
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f16.fl = MUL_S(ctx->f16.fl, ctx->f20.fl);
    // 0x8007EE20: swc1        $f22, 0x5C($sp)
    MEM_W(0X5C, ctx->r29) = ctx->f22.u32l;
    // 0x8007EE24: mul.s       $f24, $f16, $f18
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f24.fl = MUL_S(ctx->f16.fl, ctx->f18.fl);
    // 0x8007EE28: nop

    // 0x8007EE2C: mul.s       $f14, $f14, $f20
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f14.fl = MUL_S(ctx->f14.fl, ctx->f20.fl);
    // 0x8007EE30: swc1        $f24, 0x58($sp)
    MEM_W(0X58, ctx->r29) = ctx->f24.u32l;
    // 0x8007EE34: mul.s       $f4, $f14, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f4.fl = MUL_S(ctx->f14.fl, ctx->f18.fl);
    // 0x8007EE38: swc1        $f4, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->f4.u32l;
    // 0x8007EE3C: lwc1        $f6, 0x48($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X48);
    // 0x8007EE40: swc1        $f6, 0x54($sp)
    MEM_W(0X54, ctx->r29) = ctx->f6.u32l;
    // 0x8007EE44: lwc1        $f8, 0xC($v1)
    ctx->f8.u32l = MEM_W(ctx->r3, 0XC);
    // 0x8007EE48: neg.s       $f6, $f2
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f2.fl); 
    ctx->f6.fl = -ctx->f2.fl;
    // 0x8007EE4C: swc1        $f8, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->f8.u32l;
    // 0x8007EE50: lwc1        $f10, 0x10($v1)
    ctx->f10.u32l = MEM_W(ctx->r3, 0X10);
    // 0x8007EE54: lwc1        $f8, 0x44($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X44);
    // 0x8007EE58: swc1        $f10, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->f10.u32l;
    // 0x8007EE5C: lwc1        $f4, 0x14($v1)
    ctx->f4.u32l = MEM_W(ctx->r3, 0X14);
    // 0x8007EE60: mul.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = MUL_S(ctx->f6.fl, ctx->f8.fl);
    // 0x8007EE64: swc1        $f4, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->f4.u32l;
    // 0x8007EE68: lwc1        $f4, 0x40($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X40);
    // 0x8007EE6C: mul.s       $f6, $f16, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = MUL_S(ctx->f16.fl, ctx->f4.fl);
    // 0x8007EE70: lwc1        $f4, 0x3C($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X3C);
    // 0x8007EE74: sub.s       $f8, $f10, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = ctx->f10.fl - ctx->f6.fl;
    // 0x8007EE78: mul.s       $f10, $f14, $f4
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f10.fl = MUL_S(ctx->f14.fl, ctx->f4.fl);
    // 0x8007EE7C: lwc1        $f6, 0xC3C($s0)
    ctx->f6.u32l = MEM_W(ctx->r16, 0XC3C);
    // 0x8007EE80: sub.s       $f12, $f8, $f10
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f12.fl = ctx->f8.fl - ctx->f10.fl;
    // 0x8007EE84: c.lt.s      $f6, $f12
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 12);
    c1cs = ctx->f6.fl < ctx->f12.fl;
    // 0x8007EE88: nop

    // 0x8007EE8C: bc1f        L_8007EEBC
    if (!c1cs) {
        // 0x8007EE90: nop
    
            goto L_8007EEBC;
    }
    // 0x8007EE90: nop

    // 0x8007EE94: swc1        $f12, 0xC3C($s0)
    MEM_W(0XC3C, ctx->r16) = ctx->f12.u32l;
    // 0x8007EE98: swc1        $f2, 0x15B4($s0)
    MEM_W(0X15B4, ctx->r16) = ctx->f2.u32l;
    // 0x8007EE9C: swc1        $f16, 0x15B8($s0)
    MEM_W(0X15B8, ctx->r16) = ctx->f16.u32l;
    // 0x8007EEA0: swc1        $f14, 0x15BC($s0)
    MEM_W(0X15BC, ctx->r16) = ctx->f14.u32l;
    // 0x8007EEA4: lwc1        $f4, 0xC($v1)
    ctx->f4.u32l = MEM_W(ctx->r3, 0XC);
    // 0x8007EEA8: swc1        $f4, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->f4.u32l;
    // 0x8007EEAC: lwc1        $f8, 0x10($v1)
    ctx->f8.u32l = MEM_W(ctx->r3, 0X10);
    // 0x8007EEB0: swc1        $f8, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->f8.u32l;
    // 0x8007EEB4: lwc1        $f10, 0x14($v1)
    ctx->f10.u32l = MEM_W(ctx->r3, 0X14);
    // 0x8007EEB8: swc1        $f10, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->f10.u32l;
L_8007EEBC:
    // 0x8007EEBC: lwc1        $f6, 0x44($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X44);
    // 0x8007EEC0: lw          $v0, 0x94($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X94);
    // 0x8007EEC4: lw          $t0, 0x98($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X98);
    // 0x8007EEC8: add.s       $f4, $f6, $f22
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f4.fl = ctx->f6.fl + ctx->f22.fl;
    // 0x8007EECC: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x8007EED0: swc1        $f4, 0xC($v1)
    MEM_W(0XC, ctx->r3) = ctx->f4.u32l;
    // 0x8007EED4: lwc1        $f8, 0x40($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X40);
    // 0x8007EED8: add.s       $f10, $f8, $f24
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 24);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f24.fl); 
    ctx->f10.fl = ctx->f8.fl + ctx->f24.fl;
    // 0x8007EEDC: swc1        $f10, 0x10($v1)
    MEM_W(0X10, ctx->r3) = ctx->f10.u32l;
    // 0x8007EEE0: lwc1        $f4, 0x48($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X48);
    // 0x8007EEE4: lwc1        $f6, 0x3C($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X3C);
    // 0x8007EEE8: add.s       $f8, $f6, $f4
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f8.fl = ctx->f6.fl + ctx->f4.fl;
    // 0x8007EEEC: swc1        $f8, 0x14($v1)
    MEM_W(0X14, ctx->r3) = ctx->f8.u32l;
    // 0x8007EEF0: lwc1        $f10, 0xC($v0)
    ctx->f10.u32l = MEM_W(ctx->r2, 0XC);
    // 0x8007EEF4: lwc1        $f4, 0x10($v0)
    ctx->f4.u32l = MEM_W(ctx->r2, 0X10);
    // 0x8007EEF8: add.s       $f6, $f10, $f22
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f6.fl = ctx->f10.fl + ctx->f22.fl;
    // 0x8007EEFC: lwc1        $f10, 0x14($v0)
    ctx->f10.u32l = MEM_W(ctx->r2, 0X14);
    // 0x8007EF00: add.s       $f8, $f4, $f24
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 24);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f24.fl); 
    ctx->f8.fl = ctx->f4.fl + ctx->f24.fl;
    // 0x8007EF04: swc1        $f6, 0xC($v0)
    MEM_W(0XC, ctx->r2) = ctx->f6.u32l;
    // 0x8007EF08: swc1        $f8, 0x10($v0)
    MEM_W(0X10, ctx->r2) = ctx->f8.u32l;
    // 0x8007EF0C: lwc1        $f6, 0x48($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X48);
    // 0x8007EF10: add.s       $f4, $f10, $f6
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f4.fl = ctx->f10.fl + ctx->f6.fl;
    // 0x8007EF14: swc1        $f4, 0x14($v0)
    MEM_W(0X14, ctx->r2) = ctx->f4.u32l;
    // 0x8007EF18: lwc1        $f8, 0xC($t0)
    ctx->f8.u32l = MEM_W(ctx->r8, 0XC);
    // 0x8007EF1C: lwc1        $f6, 0x10($t0)
    ctx->f6.u32l = MEM_W(ctx->r8, 0X10);
    // 0x8007EF20: add.s       $f10, $f8, $f22
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f10.fl = ctx->f8.fl + ctx->f22.fl;
    // 0x8007EF24: swc1        $f10, 0xC($t0)
    MEM_W(0XC, ctx->r8) = ctx->f10.u32l;
    // 0x8007EF28: lwc1        $f4, 0x58($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X58);
    // 0x8007EF2C: lwc1        $f10, 0x14($t0)
    ctx->f10.u32l = MEM_W(ctx->r8, 0X14);
    // 0x8007EF30: add.s       $f8, $f6, $f4
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f8.fl = ctx->f6.fl + ctx->f4.fl;
    // 0x8007EF34: swc1        $f8, 0x10($t0)
    MEM_W(0X10, ctx->r8) = ctx->f8.u32l;
    // 0x8007EF38: lwc1        $f6, 0x54($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X54);
    // 0x8007EF3C: add.s       $f4, $f10, $f6
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f4.fl = ctx->f10.fl + ctx->f6.fl;
    // 0x8007EF40: swc1        $f4, 0x14($t0)
    MEM_W(0X14, ctx->r8) = ctx->f4.u32l;
    // 0x8007EF44: lw          $a3, 0x54($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X54);
    // 0x8007EF48: lw          $a2, 0x58($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X58);
    // 0x8007EF4C: jal         0x8006243C
    // 0x8007EF50: lw          $a1, 0x5C($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X5C);
    func_8006243C(rdram, ctx);
        goto after_1;
    // 0x8007EF50: lw          $a1, 0x5C($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X5C);
    after_1:
    // 0x8007EF54: b           L_8007EF68
    // 0x8007EF58: lw          $ra, 0x34($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X34);
        goto L_8007EF68;
    // 0x8007EF58: lw          $ra, 0x34($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X34);
L_8007EF5C:
    // 0x8007EF5C: bgez        $a0, L_8007ED70
    if (SIGNED(ctx->r4) >= 0) {
        // 0x8007EF60: addiu       $v1, $v1, -0x1
        ctx->r3 = ADD32(ctx->r3, -0X1);
            goto L_8007ED70;
    }
    // 0x8007EF60: addiu       $v1, $v1, -0x1
    ctx->r3 = ADD32(ctx->r3, -0X1);
L_8007EF64:
    // 0x8007EF64: lw          $ra, 0x34($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X34);
L_8007EF68:
    // 0x8007EF68: ldc1        $f20, 0x18($sp)
    CHECK_FR(ctx, 20);
    ctx->f20.u64 = LD(ctx->r29, 0X18);
    // 0x8007EF6C: ldc1        $f22, 0x20($sp)
    CHECK_FR(ctx, 22);
    ctx->f22.u64 = LD(ctx->r29, 0X20);
    // 0x8007EF70: ldc1        $f24, 0x28($sp)
    CHECK_FR(ctx, 24);
    ctx->f24.u64 = LD(ctx->r29, 0X28);
    // 0x8007EF74: lw          $s0, 0x30($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X30);
    // 0x8007EF78: jr          $ra
    // 0x8007EF7C: addiu       $sp, $sp, 0x78
    ctx->r29 = ADD32(ctx->r29, 0X78);
    return;
    // 0x8007EF7C: addiu       $sp, $sp, 0x78
    ctx->r29 = ADD32(ctx->r29, 0X78);
;}
RECOMP_FUNC void func_8007EF80(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8007EF80: addiu       $sp, $sp, -0x40
    ctx->r29 = ADD32(ctx->r29, -0X40);
    // 0x8007EF84: sw          $ra, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r31;
    // 0x8007EF88: sw          $s0, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r16;
    // 0x8007EF8C: or          $s0, $a0, $zero
    ctx->r16 = ctx->r4 | 0;
    // 0x8007EF90: lwc1        $f14, 0x4C($a0)
    ctx->f14.u32l = MEM_W(ctx->r4, 0X4C);
    // 0x8007EF94: lwc1        $f12, 0x44($a0)
    ctx->f12.u32l = MEM_W(ctx->r4, 0X44);
    // 0x8007EF98: jal         0x800741A4
    // 0x8007EF9C: addiu       $a2, $sp, 0x38
    ctx->r6 = ADD32(ctx->r29, 0X38);
    func_800741A4(rdram, ctx);
        goto after_0;
    // 0x8007EF9C: addiu       $a2, $sp, 0x38
    ctx->r6 = ADD32(ctx->r29, 0X38);
    after_0:
    // 0x8007EFA0: addiu       $a0, $v0, -0x1
    ctx->r4 = ADD32(ctx->r2, -0X1);
    // 0x8007EFA4: sw          $a0, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r4;
    // 0x8007EFA8: lwc1        $f4, 0x1610($s0)
    ctx->f4.u32l = MEM_W(ctx->r16, 0X1610);
    // 0x8007EFAC: lw          $a3, 0x160C($s0)
    ctx->r7 = MEM_W(ctx->r16, 0X160C);
    // 0x8007EFB0: addiu       $t6, $s0, 0x110
    ctx->r14 = ADD32(ctx->r16, 0X110);
    // 0x8007EFB4: swc1        $f4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f4.u32l;
    // 0x8007EFB8: lwc1        $f6, 0x1614($s0)
    ctx->f6.u32l = MEM_W(ctx->r16, 0X1614);
    // 0x8007EFBC: addiu       $t7, $s0, 0x130
    ctx->r15 = ADD32(ctx->r16, 0X130);
    // 0x8007EFC0: addiu       $t8, $s0, 0xF0
    ctx->r24 = ADD32(ctx->r16, 0XF0);
    // 0x8007EFC4: sw          $t8, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r24;
    // 0x8007EFC8: sw          $t7, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r15;
    // 0x8007EFCC: sw          $t6, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r14;
    // 0x8007EFD0: lw          $a1, 0x38($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X38);
    // 0x8007EFD4: or          $a2, $s0, $zero
    ctx->r6 = ctx->r16 | 0;
    // 0x8007EFD8: jal         0x8007ED2C
    // 0x8007EFDC: swc1        $f6, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->f6.u32l;
    func_8007ED2C(rdram, ctx);
        goto after_1;
    // 0x8007EFDC: swc1        $f6, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->f6.u32l;
    after_1:
    // 0x8007EFE0: lwc1        $f8, 0x1658($s0)
    ctx->f8.u32l = MEM_W(ctx->r16, 0X1658);
    // 0x8007EFE4: lw          $a3, 0x1654($s0)
    ctx->r7 = MEM_W(ctx->r16, 0X1654);
    // 0x8007EFE8: addiu       $t9, $s0, 0x1F0
    ctx->r25 = ADD32(ctx->r16, 0X1F0);
    // 0x8007EFEC: swc1        $f8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f8.u32l;
    // 0x8007EFF0: lwc1        $f10, 0x165C($s0)
    ctx->f10.u32l = MEM_W(ctx->r16, 0X165C);
    // 0x8007EFF4: addiu       $t0, $s0, 0x1D0
    ctx->r8 = ADD32(ctx->r16, 0X1D0);
    // 0x8007EFF8: addiu       $t1, $s0, 0x1B0
    ctx->r9 = ADD32(ctx->r16, 0X1B0);
    // 0x8007EFFC: sw          $t1, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r9;
    // 0x8007F000: sw          $t0, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r8;
    // 0x8007F004: sw          $t9, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r25;
    // 0x8007F008: lw          $a0, 0x3C($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X3C);
    // 0x8007F00C: lw          $a1, 0x38($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X38);
    // 0x8007F010: or          $a2, $s0, $zero
    ctx->r6 = ctx->r16 | 0;
    // 0x8007F014: jal         0x8007ED2C
    // 0x8007F018: swc1        $f10, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->f10.u32l;
    func_8007ED2C(rdram, ctx);
        goto after_2;
    // 0x8007F018: swc1        $f10, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->f10.u32l;
    after_2:
    // 0x8007F01C: lw          $ra, 0x34($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X34);
    // 0x8007F020: lw          $s0, 0x30($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X30);
    // 0x8007F024: addiu       $sp, $sp, 0x40
    ctx->r29 = ADD32(ctx->r29, 0X40);
    // 0x8007F028: jr          $ra
    // 0x8007F02C: nop

    return;
    // 0x8007F02C: nop

;}
RECOMP_FUNC void func_8007F030(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8007F030: addiu       $sp, $sp, -0x58
    ctx->r29 = ADD32(ctx->r29, -0X58);
    // 0x8007F034: sw          $s7, 0x54($sp)
    MEM_W(0X54, ctx->r29) = ctx->r23;
    // 0x8007F038: sw          $s6, 0x50($sp)
    MEM_W(0X50, ctx->r29) = ctx->r22;
    // 0x8007F03C: sw          $s5, 0x4C($sp)
    MEM_W(0X4C, ctx->r29) = ctx->r21;
    // 0x8007F040: sw          $s4, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r20;
    // 0x8007F044: sw          $s3, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r19;
    // 0x8007F048: sw          $s2, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r18;
    // 0x8007F04C: sw          $s1, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r17;
    // 0x8007F050: sw          $s0, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r16;
    // 0x8007F054: sdc1        $f30, 0x30($sp)
    CHECK_FR(ctx, 30);
    SD(ctx->f30.u64, 0X30, ctx->r29);
    // 0x8007F058: sdc1        $f28, 0x28($sp)
    CHECK_FR(ctx, 28);
    SD(ctx->f28.u64, 0X28, ctx->r29);
    // 0x8007F05C: sdc1        $f26, 0x20($sp)
    CHECK_FR(ctx, 26);
    SD(ctx->f26.u64, 0X20, ctx->r29);
    // 0x8007F060: sdc1        $f24, 0x18($sp)
    CHECK_FR(ctx, 24);
    SD(ctx->f24.u64, 0X18, ctx->r29);
    // 0x8007F064: sdc1        $f22, 0x10($sp)
    CHECK_FR(ctx, 22);
    SD(ctx->f22.u64, 0X10, ctx->r29);
    // 0x8007F068: sdc1        $f20, 0x8($sp)
    CHECK_FR(ctx, 20);
    SD(ctx->f20.u64, 0X8, ctx->r29);
    // 0x8007F06C: lw          $t6, 0x28($a1)
    ctx->r14 = MEM_W(ctx->r5, 0X28);
    // 0x8007F070: lw          $v0, 0x30($a1)
    ctx->r2 = MEM_W(ctx->r5, 0X30);
    // 0x8007F074: lui         $t5, 0x801C
    ctx->r13 = S32(0X801C << 16);
    // 0x8007F078: sll         $t7, $t6, 5
    ctx->r15 = S32(ctx->r14 << 5);
    // 0x8007F07C: addu        $v1, $v0, $t7
    ctx->r3 = ADD32(ctx->r2, ctx->r15);
    // 0x8007F080: sltu        $at, $v1, $v0
    ctx->r1 = ctx->r3 < ctx->r2 ? 1 : 0;
    // 0x8007F084: bne         $at, $zero, L_8007F408
    if (ctx->r1 != 0) {
        // 0x8007F088: or          $s0, $v0, $zero
        ctx->r16 = ctx->r2 | 0;
            goto L_8007F408;
    }
    // 0x8007F088: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
    // 0x8007F08C: lui         $at, 0x4180
    ctx->r1 = S32(0X4180 << 16);
    // 0x8007F090: lui         $t4, 0x801C
    ctx->r12 = S32(0X801C << 16);
    // 0x8007F094: lui         $t3, 0x801C
    ctx->r11 = S32(0X801C << 16);
    // 0x8007F098: lui         $t2, 0x801C
    ctx->r10 = S32(0X801C << 16);
    // 0x8007F09C: lui         $t1, 0x801C
    ctx->r9 = S32(0X801C << 16);
    // 0x8007F0A0: lui         $t0, 0x801C
    ctx->r8 = S32(0X801C << 16);
    // 0x8007F0A4: lui         $a3, 0x801C
    ctx->r7 = S32(0X801C << 16);
    // 0x8007F0A8: lui         $a2, 0x801C
    ctx->r6 = S32(0X801C << 16);
    // 0x8007F0AC: mtc1        $at, $f30
    ctx->f30.u32l = ctx->r1;
    // 0x8007F0B0: mtc1        $zero, $f28
    ctx->f28.u32l = 0;
    // 0x8007F0B4: addiu       $a2, $a2, 0x3B84
    ctx->r6 = ADD32(ctx->r6, 0X3B84);
    // 0x8007F0B8: addiu       $a3, $a3, 0x3B44
    ctx->r7 = ADD32(ctx->r7, 0X3B44);
    // 0x8007F0BC: addiu       $t0, $t0, 0x3B4C
    ctx->r8 = ADD32(ctx->r8, 0X3B4C);
    // 0x8007F0C0: addiu       $t1, $t1, 0x3B50
    ctx->r9 = ADD32(ctx->r9, 0X3B50);
    // 0x8007F0C4: addiu       $t2, $t2, 0x3B58
    ctx->r10 = ADD32(ctx->r10, 0X3B58);
    // 0x8007F0C8: addiu       $t3, $t3, 0x3B40
    ctx->r11 = ADD32(ctx->r11, 0X3B40);
    // 0x8007F0CC: addiu       $t4, $t4, 0x3B68
    ctx->r12 = ADD32(ctx->r12, 0X3B68);
    // 0x8007F0D0: addiu       $t5, $t5, 0x3B60
    ctx->r13 = ADD32(ctx->r13, 0X3B60);
    // 0x8007F0D4: lwc1        $f4, 0x0($v1)
    ctx->f4.u32l = MEM_W(ctx->r3, 0X0);
L_8007F0D8:
    // 0x8007F0D8: lw          $t6, 0x0($a3)
    ctx->r14 = MEM_W(ctx->r7, 0X0);
    // 0x8007F0DC: trunc.w.s   $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.u32l = TRUNC_W_S(ctx->f4.fl);
    // 0x8007F0E0: mfc1        $t9, $f6
    ctx->r25 = (int32_t)ctx->f6.u32l;
    // 0x8007F0E4: nop

    // 0x8007F0E8: subu        $s1, $t9, $t6
    ctx->r17 = SUB32(ctx->r25, ctx->r14);
    // 0x8007F0EC: bltzl       $s1, L_8007F3FC
    if (SIGNED(ctx->r17) < 0) {
        // 0x8007F0F0: addiu       $v1, $v1, -0x20
        ctx->r3 = ADD32(ctx->r3, -0X20);
            goto L_8007F3FC;
    }
    goto skip_0;
    // 0x8007F0F0: addiu       $v1, $v1, -0x20
    ctx->r3 = ADD32(ctx->r3, -0X20);
    skip_0:
    // 0x8007F0F4: lw          $t7, 0x0($t0)
    ctx->r15 = MEM_W(ctx->r8, 0X0);
    // 0x8007F0F8: slt         $at, $s1, $t7
    ctx->r1 = SIGNED(ctx->r17) < SIGNED(ctx->r15) ? 1 : 0;
    // 0x8007F0FC: beql        $at, $zero, L_8007F3FC
    if (ctx->r1 == 0) {
        // 0x8007F100: addiu       $v1, $v1, -0x20
        ctx->r3 = ADD32(ctx->r3, -0X20);
            goto L_8007F3FC;
    }
    goto skip_1;
    // 0x8007F100: addiu       $v1, $v1, -0x20
    ctx->r3 = ADD32(ctx->r3, -0X20);
    skip_1:
    // 0x8007F104: lwc1        $f8, 0x8($v1)
    ctx->f8.u32l = MEM_W(ctx->r3, 0X8);
    // 0x8007F108: lw          $t6, 0x0($t1)
    ctx->r14 = MEM_W(ctx->r9, 0X0);
    // 0x8007F10C: trunc.w.s   $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.u32l = TRUNC_W_S(ctx->f8.fl);
    // 0x8007F110: mfc1        $t9, $f10
    ctx->r25 = (int32_t)ctx->f10.u32l;
    // 0x8007F114: nop

    // 0x8007F118: subu        $s2, $t9, $t6
    ctx->r18 = SUB32(ctx->r25, ctx->r14);
    // 0x8007F11C: bltzl       $s2, L_8007F3FC
    if (SIGNED(ctx->r18) < 0) {
        // 0x8007F120: addiu       $v1, $v1, -0x20
        ctx->r3 = ADD32(ctx->r3, -0X20);
            goto L_8007F3FC;
    }
    goto skip_2;
    // 0x8007F120: addiu       $v1, $v1, -0x20
    ctx->r3 = ADD32(ctx->r3, -0X20);
    skip_2:
    // 0x8007F124: lw          $t7, 0x0($t2)
    ctx->r15 = MEM_W(ctx->r10, 0X0);
    // 0x8007F128: lui         $s4, 0x801C
    ctx->r20 = S32(0X801C << 16);
    // 0x8007F12C: lui         $s5, 0x801C
    ctx->r21 = S32(0X801C << 16);
    // 0x8007F130: slt         $at, $s2, $t7
    ctx->r1 = SIGNED(ctx->r18) < SIGNED(ctx->r15) ? 1 : 0;
    // 0x8007F134: beq         $at, $zero, L_8007F3F8
    if (ctx->r1 == 0) {
        // 0x8007F138: lui         $s6, 0x801C
        ctx->r22 = S32(0X801C << 16);
            goto L_8007F3F8;
    }
    // 0x8007F138: lui         $s6, 0x801C
    ctx->r22 = S32(0X801C << 16);
    // 0x8007F13C: lh          $t8, 0x0($t3)
    ctx->r24 = MEM_H(ctx->r11, 0X0);
    // 0x8007F140: lui         $s7, 0x801C
    ctx->r23 = S32(0X801C << 16);
    // 0x8007F144: lw          $s7, 0x3B80($s7)
    ctx->r23 = MEM_W(ctx->r23, 0X3B80);
    // 0x8007F148: lw          $s4, 0x3B7C($s4)
    ctx->r20 = MEM_W(ctx->r20, 0X3B7C);
    // 0x8007F14C: lw          $s5, 0x3B78($s5)
    ctx->r21 = MEM_W(ctx->r21, 0X3B78);
    // 0x8007F150: beq         $t8, $zero, L_8007F178
    if (ctx->r24 == 0) {
        // 0x8007F154: lw          $s6, 0x3B70($s6)
        ctx->r22 = MEM_W(ctx->r22, 0X3B70);
            goto L_8007F178;
    }
    // 0x8007F154: lw          $s6, 0x3B70($s6)
    ctx->r22 = MEM_W(ctx->r22, 0X3B70);
    // 0x8007F158: lw          $t6, 0x0($t4)
    ctx->r14 = MEM_W(ctx->r12, 0X0);
    // 0x8007F15C: srav        $t9, $s1, $s6
    ctx->r25 = S32(SIGNED(ctx->r17) >> (ctx->r22 & 31));
    // 0x8007F160: srav        $t8, $s2, $s5
    ctx->r24 = S32(SIGNED(ctx->r18) >> (ctx->r21 & 31));
    // 0x8007F164: sllv        $t7, $t9, $t6
    ctx->r15 = S32(ctx->r25 << (ctx->r14 & 31));
    // 0x8007F168: or          $t9, $t8, $t7
    ctx->r25 = ctx->r24 | ctx->r15;
    // 0x8007F16C: sll         $t6, $t9, 1
    ctx->r14 = S32(ctx->r25 << 1);
    // 0x8007F170: b           L_8007F194
    // 0x8007F174: addu        $s3, $s4, $t6
    ctx->r19 = ADD32(ctx->r20, ctx->r14);
        goto L_8007F194;
    // 0x8007F174: addu        $s3, $s4, $t6
    ctx->r19 = ADD32(ctx->r20, ctx->r14);
L_8007F178:
    // 0x8007F178: lw          $t7, 0x0($t5)
    ctx->r15 = MEM_W(ctx->r13, 0X0);
    // 0x8007F17C: srav        $t8, $s2, $s5
    ctx->r24 = S32(SIGNED(ctx->r18) >> (ctx->r21 & 31));
    // 0x8007F180: srav        $t6, $s1, $s6
    ctx->r14 = S32(SIGNED(ctx->r17) >> (ctx->r22 & 31));
    // 0x8007F184: sllv        $t9, $t8, $t7
    ctx->r25 = S32(ctx->r24 << (ctx->r15 & 31));
    // 0x8007F188: or          $t8, $t6, $t9
    ctx->r24 = ctx->r14 | ctx->r25;
    // 0x8007F18C: sll         $t7, $t8, 1
    ctx->r15 = S32(ctx->r24 << 1);
    // 0x8007F190: addu        $s3, $s4, $t7
    ctx->r19 = ADD32(ctx->r20, ctx->r15);
L_8007F194:
    // 0x8007F194: lhu         $t6, 0x0($s3)
    ctx->r14 = MEM_HU(ctx->r19, 0X0);
    // 0x8007F198: sll         $t9, $t6, 1
    ctx->r25 = S32(ctx->r14 << 1);
    // 0x8007F19C: addu        $s1, $t9, $s7
    ctx->r17 = ADD32(ctx->r25, ctx->r23);
    // 0x8007F1A0: lhu         $s2, 0x2($s1)
    ctx->r18 = MEM_HU(ctx->r17, 0X2);
    // 0x8007F1A4: addiu       $s1, $s1, 0x2
    ctx->r17 = ADD32(ctx->r17, 0X2);
    // 0x8007F1A8: beql        $s2, $zero, L_8007F3FC
    if (ctx->r18 == 0) {
        // 0x8007F1AC: addiu       $v1, $v1, -0x20
        ctx->r3 = ADD32(ctx->r3, -0X20);
            goto L_8007F3FC;
    }
    goto skip_3;
    // 0x8007F1AC: addiu       $v1, $v1, -0x20
    ctx->r3 = ADD32(ctx->r3, -0X20);
    skip_3:
    // 0x8007F1B0: lw          $t7, 0x0($a2)
    ctx->r15 = MEM_W(ctx->r6, 0X0);
L_8007F1B4:
    // 0x8007F1B4: addiu       $s2, $s2, -0x1
    ctx->r18 = ADD32(ctx->r18, -0X1);
    // 0x8007F1B8: sll         $t8, $s2, 6
    ctx->r24 = S32(ctx->r18 << 6);
    // 0x8007F1BC: addu        $s0, $t8, $t7
    ctx->r16 = ADD32(ctx->r24, ctx->r15);
    // 0x8007F1C0: lwc1        $f4, 0x0($s0)
    ctx->f4.u32l = MEM_W(ctx->r16, 0X0);
    // 0x8007F1C4: lwc1        $f6, 0x0($v1)
    ctx->f6.u32l = MEM_W(ctx->r3, 0X0);
    // 0x8007F1C8: lwc1        $f8, 0x4($s0)
    ctx->f8.u32l = MEM_W(ctx->r16, 0X4);
    // 0x8007F1CC: lwc1        $f10, 0x4($v1)
    ctx->f10.u32l = MEM_W(ctx->r3, 0X4);
    // 0x8007F1D0: sub.s       $f0, $f4, $f6
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f0.fl = ctx->f4.fl - ctx->f6.fl;
    // 0x8007F1D4: lwc1        $f6, 0x8($v1)
    ctx->f6.u32l = MEM_W(ctx->r3, 0X8);
    // 0x8007F1D8: lwc1        $f4, 0x8($s0)
    ctx->f4.u32l = MEM_W(ctx->r16, 0X8);
    // 0x8007F1DC: sub.s       $f2, $f8, $f10
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f2.fl = ctx->f8.fl - ctx->f10.fl;
    // 0x8007F1E0: lwc1        $f8, 0x18($s0)
    ctx->f8.u32l = MEM_W(ctx->r16, 0X18);
    // 0x8007F1E4: sub.s       $f12, $f4, $f6
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f12.fl = ctx->f4.fl - ctx->f6.fl;
    // 0x8007F1E8: mul.s       $f10, $f8, $f0
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f10.fl = MUL_S(ctx->f8.fl, ctx->f0.fl);
    // 0x8007F1EC: lwc1        $f4, 0x1C($s0)
    ctx->f4.u32l = MEM_W(ctx->r16, 0X1C);
    // 0x8007F1F0: mul.s       $f6, $f2, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = MUL_S(ctx->f2.fl, ctx->f4.fl);
    // 0x8007F1F4: lwc1        $f4, 0x20($s0)
    ctx->f4.u32l = MEM_W(ctx->r16, 0X20);
    // 0x8007F1F8: add.s       $f8, $f10, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = ctx->f10.fl + ctx->f6.fl;
    // 0x8007F1FC: mul.s       $f10, $f12, $f4
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f10.fl = MUL_S(ctx->f12.fl, ctx->f4.fl);
    // 0x8007F200: add.s       $f6, $f8, $f10
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f6.fl = ctx->f8.fl + ctx->f10.fl;
    // 0x8007F204: c.lt.s      $f6, $f28
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 28);
    c1cs = ctx->f6.fl < ctx->f28.fl;
    // 0x8007F208: nop

    // 0x8007F20C: bc1tl       L_8007F3E8
    if (c1cs) {
        // 0x8007F210: lhu         $s2, 0x2($s1)
        ctx->r18 = MEM_HU(ctx->r17, 0X2);
            goto L_8007F3E8;
    }
    goto skip_4;
    // 0x8007F210: lhu         $s2, 0x2($s1)
    ctx->r18 = MEM_HU(ctx->r17, 0X2);
    skip_4:
    // 0x8007F214: lwc1        $f4, 0x24($s0)
    ctx->f4.u32l = MEM_W(ctx->r16, 0X24);
    // 0x8007F218: lwc1        $f10, 0x28($s0)
    ctx->f10.u32l = MEM_W(ctx->r16, 0X28);
    // 0x8007F21C: mul.s       $f8, $f4, $f0
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f8.fl = MUL_S(ctx->f4.fl, ctx->f0.fl);
    // 0x8007F220: nop

    // 0x8007F224: mul.s       $f6, $f2, $f10
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f6.fl = MUL_S(ctx->f2.fl, ctx->f10.fl);
    // 0x8007F228: lwc1        $f10, 0x2C($s0)
    ctx->f10.u32l = MEM_W(ctx->r16, 0X2C);
    // 0x8007F22C: add.s       $f4, $f8, $f6
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f4.fl = ctx->f8.fl + ctx->f6.fl;
    // 0x8007F230: mul.s       $f8, $f12, $f10
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f8.fl = MUL_S(ctx->f12.fl, ctx->f10.fl);
    // 0x8007F234: add.s       $f6, $f4, $f8
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f6.fl = ctx->f4.fl + ctx->f8.fl;
    // 0x8007F238: c.lt.s      $f6, $f28
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 28);
    c1cs = ctx->f6.fl < ctx->f28.fl;
    // 0x8007F23C: nop

    // 0x8007F240: bc1t        L_8007F3E4
    if (c1cs) {
        // 0x8007F244: nop
    
            goto L_8007F3E4;
    }
    // 0x8007F244: nop

    // 0x8007F248: lwc1        $f10, 0x30($s0)
    ctx->f10.u32l = MEM_W(ctx->r16, 0X30);
    // 0x8007F24C: lwc1        $f8, 0x34($s0)
    ctx->f8.u32l = MEM_W(ctx->r16, 0X34);
    // 0x8007F250: mul.s       $f4, $f10, $f0
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f4.fl = MUL_S(ctx->f10.fl, ctx->f0.fl);
    // 0x8007F254: nop

    // 0x8007F258: mul.s       $f6, $f2, $f8
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f6.fl = MUL_S(ctx->f2.fl, ctx->f8.fl);
    // 0x8007F25C: lwc1        $f8, 0x38($s0)
    ctx->f8.u32l = MEM_W(ctx->r16, 0X38);
    // 0x8007F260: add.s       $f10, $f4, $f6
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f10.fl = ctx->f4.fl + ctx->f6.fl;
    // 0x8007F264: mul.s       $f4, $f12, $f8
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f4.fl = MUL_S(ctx->f12.fl, ctx->f8.fl);
    // 0x8007F268: add.s       $f14, $f10, $f4
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f14.fl = ctx->f10.fl + ctx->f4.fl;
    // 0x8007F26C: c.le.s      $f28, $f14
    CHECK_FR(ctx, 28);
    CHECK_FR(ctx, 14);
    c1cs = ctx->f28.fl <= ctx->f14.fl;
    // 0x8007F270: nop

    // 0x8007F274: bc1t        L_8007F3E4
    if (c1cs) {
        // 0x8007F278: nop
    
            goto L_8007F3E4;
    }
    // 0x8007F278: nop

    // 0x8007F27C: lwc1        $f6, 0x3C($s0)
    ctx->f6.u32l = MEM_W(ctx->r16, 0X3C);
    // 0x8007F280: c.lt.s      $f14, $f6
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 6);
    c1cs = ctx->f14.fl < ctx->f6.fl;
    // 0x8007F284: nop

    // 0x8007F288: bc1tl       L_8007F3E8
    if (c1cs) {
        // 0x8007F28C: lhu         $s2, 0x2($s1)
        ctx->r18 = MEM_HU(ctx->r17, 0X2);
            goto L_8007F3E8;
    }
    goto skip_5;
    // 0x8007F28C: lhu         $s2, 0x2($s1)
    ctx->r18 = MEM_HU(ctx->r17, 0X2);
    skip_5:
    // 0x8007F290: lwc1        $f16, 0xC($s0)
    ctx->f16.u32l = MEM_W(ctx->r16, 0XC);
    // 0x8007F294: lwc1        $f18, 0x10($s0)
    ctx->f18.u32l = MEM_W(ctx->r16, 0X10);
    // 0x8007F298: lwc1        $f20, 0x14($s0)
    ctx->f20.u32l = MEM_W(ctx->r16, 0X14);
    // 0x8007F29C: mul.s       $f8, $f16, $f0
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f8.fl = MUL_S(ctx->f16.fl, ctx->f0.fl);
    // 0x8007F2A0: nop

    // 0x8007F2A4: mul.s       $f10, $f2, $f18
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f10.fl = MUL_S(ctx->f2.fl, ctx->f18.fl);
    // 0x8007F2A8: add.s       $f4, $f8, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f4.fl = ctx->f8.fl + ctx->f10.fl;
    // 0x8007F2AC: mul.s       $f6, $f12, $f20
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f6.fl = MUL_S(ctx->f12.fl, ctx->f20.fl);
    // 0x8007F2B0: add.s       $f14, $f4, $f6
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f14.fl = ctx->f4.fl + ctx->f6.fl;
    // 0x8007F2B4: c.lt.s      $f14, $f28
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 28);
    c1cs = ctx->f14.fl < ctx->f28.fl;
    // 0x8007F2B8: nop

    // 0x8007F2BC: bc1t        L_8007F3E4
    if (c1cs) {
        // 0x8007F2C0: nop
    
            goto L_8007F3E4;
    }
    // 0x8007F2C0: nop

    // 0x8007F2C4: c.lt.s      $f30, $f14
    CHECK_FR(ctx, 30);
    CHECK_FR(ctx, 14);
    c1cs = ctx->f30.fl < ctx->f14.fl;
    // 0x8007F2C8: nop

    // 0x8007F2CC: bc1tl       L_8007F3E8
    if (c1cs) {
        // 0x8007F2D0: lhu         $s2, 0x2($s1)
        ctx->r18 = MEM_HU(ctx->r17, 0X2);
            goto L_8007F3E8;
    }
    goto skip_6;
    // 0x8007F2D0: lhu         $s2, 0x2($s1)
    ctx->r18 = MEM_HU(ctx->r17, 0X2);
    skip_6:
    // 0x8007F2D4: lwc1        $f22, 0xC($v1)
    ctx->f22.u32l = MEM_W(ctx->r3, 0XC);
    // 0x8007F2D8: lwc1        $f24, 0x10($v1)
    ctx->f24.u32l = MEM_W(ctx->r3, 0X10);
    // 0x8007F2DC: lwc1        $f26, 0x14($v1)
    ctx->f26.u32l = MEM_W(ctx->r3, 0X14);
    // 0x8007F2E0: neg.s       $f8, $f22
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f22.fl); 
    ctx->f8.fl = -ctx->f22.fl;
    // 0x8007F2E4: mul.s       $f10, $f8, $f16
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f10.fl = MUL_S(ctx->f8.fl, ctx->f16.fl);
    // 0x8007F2E8: nop

    // 0x8007F2EC: mul.s       $f4, $f24, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f24.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f4.fl = MUL_S(ctx->f24.fl, ctx->f18.fl);
    // 0x8007F2F0: sub.s       $f6, $f10, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = ctx->f10.fl - ctx->f4.fl;
    // 0x8007F2F4: mul.s       $f8, $f26, $f20
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f26.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f8.fl = MUL_S(ctx->f26.fl, ctx->f20.fl);
    // 0x8007F2F8: sub.s       $f12, $f6, $f8
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f12.fl = ctx->f6.fl - ctx->f8.fl;
    // 0x8007F2FC: c.le.s      $f12, $f28
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 28);
    c1cs = ctx->f12.fl <= ctx->f28.fl;
    // 0x8007F300: nop

    // 0x8007F304: bc1t        L_8007F3E4
    if (c1cs) {
        // 0x8007F308: nop
    
            goto L_8007F3E4;
    }
    // 0x8007F308: nop

    // 0x8007F30C: lwc1        $f10, 0xC4C($a0)
    ctx->f10.u32l = MEM_W(ctx->r4, 0XC4C);
    // 0x8007F310: c.lt.s      $f10, $f12
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 12);
    c1cs = ctx->f10.fl < ctx->f12.fl;
    // 0x8007F314: nop

    // 0x8007F318: bc1f        L_8007F34C
    if (!c1cs) {
        // 0x8007F31C: nop
    
            goto L_8007F34C;
    }
    // 0x8007F31C: nop

    // 0x8007F320: swc1        $f12, 0xC4C($a0)
    MEM_W(0XC4C, ctx->r4) = ctx->f12.u32l;
    // 0x8007F324: lwc1        $f4, 0xC($s0)
    ctx->f4.u32l = MEM_W(ctx->r16, 0XC);
    // 0x8007F328: swc1        $f4, 0x15B4($a0)
    MEM_W(0X15B4, ctx->r4) = ctx->f4.u32l;
    // 0x8007F32C: lwc1        $f6, 0x10($s0)
    ctx->f6.u32l = MEM_W(ctx->r16, 0X10);
    // 0x8007F330: swc1        $f6, 0x15B8($a0)
    MEM_W(0X15B8, ctx->r4) = ctx->f6.u32l;
    // 0x8007F334: lwc1        $f8, 0x14($s0)
    ctx->f8.u32l = MEM_W(ctx->r16, 0X14);
    // 0x8007F338: swc1        $f8, 0x15BC($a0)
    MEM_W(0X15BC, ctx->r4) = ctx->f8.u32l;
    // 0x8007F33C: lwc1        $f26, 0x14($v1)
    ctx->f26.u32l = MEM_W(ctx->r3, 0X14);
    // 0x8007F340: lwc1        $f24, 0x10($v1)
    ctx->f24.u32l = MEM_W(ctx->r3, 0X10);
    // 0x8007F344: lwc1        $f22, 0xC($v1)
    ctx->f22.u32l = MEM_W(ctx->r3, 0XC);
    // 0x8007F348: lwc1        $f16, 0xC($s0)
    ctx->f16.u32l = MEM_W(ctx->r16, 0XC);
L_8007F34C:
    // 0x8007F34C: mul.s       $f10, $f12, $f16
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f10.fl = MUL_S(ctx->f12.fl, ctx->f16.fl);
    // 0x8007F350: add.s       $f4, $f22, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f4.fl = ctx->f22.fl + ctx->f10.fl;
    // 0x8007F354: swc1        $f4, 0xC($v1)
    MEM_W(0XC, ctx->r3) = ctx->f4.u32l;
    // 0x8007F358: lwc1        $f6, 0x10($s0)
    ctx->f6.u32l = MEM_W(ctx->r16, 0X10);
    // 0x8007F35C: mul.s       $f8, $f12, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = MUL_S(ctx->f12.fl, ctx->f6.fl);
    // 0x8007F360: add.s       $f10, $f24, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f24.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = ctx->f24.fl + ctx->f8.fl;
    // 0x8007F364: swc1        $f10, 0x10($v1)
    MEM_W(0X10, ctx->r3) = ctx->f10.u32l;
    // 0x8007F368: lwc1        $f4, 0x14($s0)
    ctx->f4.u32l = MEM_W(ctx->r16, 0X14);
    // 0x8007F36C: mul.s       $f6, $f12, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = MUL_S(ctx->f12.fl, ctx->f4.fl);
    // 0x8007F370: add.s       $f8, $f26, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f26.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = ctx->f26.fl + ctx->f6.fl;
    // 0x8007F374: swc1        $f8, 0x14($v1)
    MEM_W(0X14, ctx->r3) = ctx->f8.u32l;
    // 0x8007F378: lwc1        $f10, 0xC($s0)
    ctx->f10.u32l = MEM_W(ctx->r16, 0XC);
    // 0x8007F37C: lwc1        $f4, 0x10($s0)
    ctx->f4.u32l = MEM_W(ctx->r16, 0X10);
    // 0x8007F380: lw          $v0, 0x30($a1)
    ctx->r2 = MEM_W(ctx->r5, 0X30);
    // 0x8007F384: mul.s       $f0, $f10, $f14
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f0.fl = MUL_S(ctx->f10.fl, ctx->f14.fl);
    // 0x8007F388: lwc1        $f6, 0x14($s0)
    ctx->f6.u32l = MEM_W(ctx->r16, 0X14);
    // 0x8007F38C: addiu       $t6, $v0, 0x180
    ctx->r14 = ADD32(ctx->r2, 0X180);
    // 0x8007F390: mul.s       $f2, $f4, $f14
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f2.fl = MUL_S(ctx->f4.fl, ctx->f14.fl);
    // 0x8007F394: sltu        $at, $v0, $t6
    ctx->r1 = ctx->r2 < ctx->r14 ? 1 : 0;
    // 0x8007F398: or          $s2, $v0, $zero
    ctx->r18 = ctx->r2 | 0;
    // 0x8007F39C: mul.s       $f12, $f6, $f14
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f12.fl = MUL_S(ctx->f6.fl, ctx->f14.fl);
    // 0x8007F3A0: beql        $at, $zero, L_8007F3E8
    if (ctx->r1 == 0) {
        // 0x8007F3A4: lhu         $s2, 0x2($s1)
        ctx->r18 = MEM_HU(ctx->r17, 0X2);
            goto L_8007F3E8;
    }
    goto skip_7;
    // 0x8007F3A4: lhu         $s2, 0x2($s1)
    ctx->r18 = MEM_HU(ctx->r17, 0X2);
    skip_7:
    // 0x8007F3A8: lwc1        $f8, 0x0($s2)
    ctx->f8.u32l = MEM_W(ctx->r18, 0X0);
L_8007F3AC:
    // 0x8007F3AC: lwc1        $f4, 0x4($s2)
    ctx->f4.u32l = MEM_W(ctx->r18, 0X4);
    // 0x8007F3B0: addiu       $s2, $s2, 0x20
    ctx->r18 = ADD32(ctx->r18, 0X20);
    // 0x8007F3B4: add.s       $f10, $f8, $f0
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f10.fl = ctx->f8.fl + ctx->f0.fl;
    // 0x8007F3B8: lwc1        $f8, -0x18($s2)
    ctx->f8.u32l = MEM_W(ctx->r18, -0X18);
    // 0x8007F3BC: add.s       $f6, $f4, $f2
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f6.fl = ctx->f4.fl + ctx->f2.fl;
    // 0x8007F3C0: swc1        $f10, -0x20($s2)
    MEM_W(-0X20, ctx->r18) = ctx->f10.u32l;
    // 0x8007F3C4: add.s       $f10, $f8, $f12
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f10.fl = ctx->f8.fl + ctx->f12.fl;
    // 0x8007F3C8: swc1        $f6, -0x1C($s2)
    MEM_W(-0X1C, ctx->r18) = ctx->f6.u32l;
    // 0x8007F3CC: swc1        $f10, -0x18($s2)
    MEM_W(-0X18, ctx->r18) = ctx->f10.u32l;
    // 0x8007F3D0: lw          $v0, 0x30($a1)
    ctx->r2 = MEM_W(ctx->r5, 0X30);
    // 0x8007F3D4: addiu       $t9, $v0, 0x180
    ctx->r25 = ADD32(ctx->r2, 0X180);
    // 0x8007F3D8: sltu        $at, $s2, $t9
    ctx->r1 = ctx->r18 < ctx->r25 ? 1 : 0;
    // 0x8007F3DC: bnel        $at, $zero, L_8007F3AC
    if (ctx->r1 != 0) {
        // 0x8007F3E0: lwc1        $f8, 0x0($s2)
        ctx->f8.u32l = MEM_W(ctx->r18, 0X0);
            goto L_8007F3AC;
    }
    goto skip_8;
    // 0x8007F3E0: lwc1        $f8, 0x0($s2)
    ctx->f8.u32l = MEM_W(ctx->r18, 0X0);
    skip_8:
L_8007F3E4:
    // 0x8007F3E4: lhu         $s2, 0x2($s1)
    ctx->r18 = MEM_HU(ctx->r17, 0X2);
L_8007F3E8:
    // 0x8007F3E8: addiu       $s1, $s1, 0x2
    ctx->r17 = ADD32(ctx->r17, 0X2);
    // 0x8007F3EC: bnel        $s2, $zero, L_8007F1B4
    if (ctx->r18 != 0) {
        // 0x8007F3F0: lw          $t7, 0x0($a2)
        ctx->r15 = MEM_W(ctx->r6, 0X0);
            goto L_8007F1B4;
    }
    goto skip_9;
    // 0x8007F3F0: lw          $t7, 0x0($a2)
    ctx->r15 = MEM_W(ctx->r6, 0X0);
    skip_9:
    // 0x8007F3F4: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
L_8007F3F8:
    // 0x8007F3F8: addiu       $v1, $v1, -0x20
    ctx->r3 = ADD32(ctx->r3, -0X20);
L_8007F3FC:
    // 0x8007F3FC: sltu        $at, $v1, $s0
    ctx->r1 = ctx->r3 < ctx->r16 ? 1 : 0;
    // 0x8007F400: beql        $at, $zero, L_8007F0D8
    if (ctx->r1 == 0) {
        // 0x8007F404: lwc1        $f4, 0x0($v1)
        ctx->f4.u32l = MEM_W(ctx->r3, 0X0);
            goto L_8007F0D8;
    }
    goto skip_10;
    // 0x8007F404: lwc1        $f4, 0x0($v1)
    ctx->f4.u32l = MEM_W(ctx->r3, 0X0);
    skip_10:
L_8007F408:
    // 0x8007F408: ldc1        $f20, 0x8($sp)
    CHECK_FR(ctx, 20);
    ctx->f20.u64 = LD(ctx->r29, 0X8);
    // 0x8007F40C: ldc1        $f22, 0x10($sp)
    CHECK_FR(ctx, 22);
    ctx->f22.u64 = LD(ctx->r29, 0X10);
    // 0x8007F410: ldc1        $f24, 0x18($sp)
    CHECK_FR(ctx, 24);
    ctx->f24.u64 = LD(ctx->r29, 0X18);
    // 0x8007F414: ldc1        $f26, 0x20($sp)
    CHECK_FR(ctx, 26);
    ctx->f26.u64 = LD(ctx->r29, 0X20);
    // 0x8007F418: ldc1        $f28, 0x28($sp)
    CHECK_FR(ctx, 28);
    ctx->f28.u64 = LD(ctx->r29, 0X28);
    // 0x8007F41C: ldc1        $f30, 0x30($sp)
    CHECK_FR(ctx, 30);
    ctx->f30.u64 = LD(ctx->r29, 0X30);
    // 0x8007F420: lw          $s0, 0x38($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X38);
    // 0x8007F424: lw          $s1, 0x3C($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X3C);
    // 0x8007F428: lw          $s2, 0x40($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X40);
    // 0x8007F42C: lw          $s3, 0x44($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X44);
    // 0x8007F430: lw          $s4, 0x48($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X48);
    // 0x8007F434: lw          $s5, 0x4C($sp)
    ctx->r21 = MEM_W(ctx->r29, 0X4C);
    // 0x8007F438: lw          $s6, 0x50($sp)
    ctx->r22 = MEM_W(ctx->r29, 0X50);
    // 0x8007F43C: lw          $s7, 0x54($sp)
    ctx->r23 = MEM_W(ctx->r29, 0X54);
    // 0x8007F440: jr          $ra
    // 0x8007F444: addiu       $sp, $sp, 0x58
    ctx->r29 = ADD32(ctx->r29, 0X58);
    return;
    // 0x8007F444: addiu       $sp, $sp, 0x58
    ctx->r29 = ADD32(ctx->r29, 0X58);
;}
RECOMP_FUNC void func_8007F448(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8007F448: trunc.w.s   $f4, $f12
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 12);
    ctx->f4.u32l = TRUNC_W_S(ctx->f12.fl);
    // 0x8007F44C: lui         $t8, 0x801C
    ctx->r24 = S32(0X801C << 16);
    // 0x8007F450: lw          $t8, 0x3B44($t8)
    ctx->r24 = MEM_W(ctx->r24, 0X3B44);
    // 0x8007F454: addiu       $sp, $sp, -0x28
    ctx->r29 = ADD32(ctx->r29, -0X28);
    // 0x8007F458: mfc1        $t7, $f4
    ctx->r15 = (int32_t)ctx->f4.u32l;
    // 0x8007F45C: sdc1        $f20, 0x8($sp)
    CHECK_FR(ctx, 20);
    SD(ctx->f20.u64, 0X8, ctx->r29);
    // 0x8007F460: mtc1        $a2, $f20
    ctx->f20.u32l = ctx->r6;
    // 0x8007F464: subu        $v0, $t7, $t8
    ctx->r2 = SUB32(ctx->r15, ctx->r24);
    // 0x8007F468: sdc1        $f26, 0x20($sp)
    CHECK_FR(ctx, 26);
    SD(ctx->f26.u64, 0X20, ctx->r29);
    // 0x8007F46C: sdc1        $f24, 0x18($sp)
    CHECK_FR(ctx, 24);
    SD(ctx->f24.u64, 0X18, ctx->r29);
    // 0x8007F470: bltz        $v0, L_8007F48C
    if (SIGNED(ctx->r2) < 0) {
        // 0x8007F474: sdc1        $f22, 0x10($sp)
        CHECK_FR(ctx, 22);
    SD(ctx->f22.u64, 0X10, ctx->r29);
            goto L_8007F48C;
    }
    // 0x8007F474: sdc1        $f22, 0x10($sp)
    CHECK_FR(ctx, 22);
    SD(ctx->f22.u64, 0X10, ctx->r29);
    // 0x8007F478: lui         $t9, 0x801C
    ctx->r25 = S32(0X801C << 16);
    // 0x8007F47C: lw          $t9, 0x3B4C($t9)
    ctx->r25 = MEM_W(ctx->r25, 0X3B4C);
    // 0x8007F480: slt         $at, $v0, $t9
    ctx->r1 = SIGNED(ctx->r2) < SIGNED(ctx->r25) ? 1 : 0;
    // 0x8007F484: bnel        $at, $zero, L_8007F49C
    if (ctx->r1 != 0) {
        // 0x8007F488: trunc.w.s   $f6, $f20
        CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 20);
    ctx->f6.u32l = TRUNC_W_S(ctx->f20.fl);
            goto L_8007F49C;
    }
    goto skip_0;
    // 0x8007F488: trunc.w.s   $f6, $f20
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 20);
    ctx->f6.u32l = TRUNC_W_S(ctx->f20.fl);
    skip_0:
L_8007F48C:
    // 0x8007F48C: mtc1        $zero, $f0
    ctx->f0.u32l = 0;
    // 0x8007F490: b           L_8007F6E4
    // 0x8007F494: ldc1        $f20, 0x8($sp)
    CHECK_FR(ctx, 20);
    ctx->f20.u64 = LD(ctx->r29, 0X8);
        goto L_8007F6E4;
    // 0x8007F494: ldc1        $f20, 0x8($sp)
    CHECK_FR(ctx, 20);
    ctx->f20.u64 = LD(ctx->r29, 0X8);
    // 0x8007F498: trunc.w.s   $f6, $f20
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 20);
    ctx->f6.u32l = TRUNC_W_S(ctx->f20.fl);
L_8007F49C:
    // 0x8007F49C: lui         $t2, 0x801C
    ctx->r10 = S32(0X801C << 16);
    // 0x8007F4A0: lw          $t2, 0x3B50($t2)
    ctx->r10 = MEM_W(ctx->r10, 0X3B50);
    // 0x8007F4A4: lui         $t3, 0x801C
    ctx->r11 = S32(0X801C << 16);
    // 0x8007F4A8: mfc1        $t1, $f6
    ctx->r9 = (int32_t)ctx->f6.u32l;
    // 0x8007F4AC: nop

    // 0x8007F4B0: subu        $v1, $t1, $t2
    ctx->r3 = SUB32(ctx->r9, ctx->r10);
    // 0x8007F4B4: bltzl       $v1, L_8007F4D4
    if (SIGNED(ctx->r3) < 0) {
        // 0x8007F4B8: mtc1        $zero, $f0
        ctx->f0.u32l = 0;
            goto L_8007F4D4;
    }
    goto skip_1;
    // 0x8007F4B8: mtc1        $zero, $f0
    ctx->f0.u32l = 0;
    skip_1:
    // 0x8007F4BC: lw          $t3, 0x3B58($t3)
    ctx->r11 = MEM_W(ctx->r11, 0X3B58);
    // 0x8007F4C0: lui         $t4, 0x801C
    ctx->r12 = S32(0X801C << 16);
    // 0x8007F4C4: slt         $at, $v1, $t3
    ctx->r1 = SIGNED(ctx->r3) < SIGNED(ctx->r11) ? 1 : 0;
    // 0x8007F4C8: bne         $at, $zero, L_8007F4DC
    if (ctx->r1 != 0) {
        // 0x8007F4CC: nop
    
            goto L_8007F4DC;
    }
    // 0x8007F4CC: nop

    // 0x8007F4D0: mtc1        $zero, $f0
    ctx->f0.u32l = 0;
L_8007F4D4:
    // 0x8007F4D4: b           L_8007F6E4
    // 0x8007F4D8: ldc1        $f20, 0x8($sp)
    CHECK_FR(ctx, 20);
    ctx->f20.u64 = LD(ctx->r29, 0X8);
        goto L_8007F6E4;
    // 0x8007F4D8: ldc1        $f20, 0x8($sp)
    CHECK_FR(ctx, 20);
    ctx->f20.u64 = LD(ctx->r29, 0X8);
L_8007F4DC:
    // 0x8007F4DC: lh          $t4, 0x3B40($t4)
    ctx->r12 = MEM_H(ctx->r12, 0X3B40);
    // 0x8007F4E0: lui         $t6, 0x801C
    ctx->r14 = S32(0X801C << 16);
    // 0x8007F4E4: lui         $t9, 0x801C
    ctx->r25 = S32(0X801C << 16);
    // 0x8007F4E8: beq         $t4, $zero, L_8007F52C
    if (ctx->r12 == 0) {
        // 0x8007F4EC: lui         $t3, 0x801C
        ctx->r11 = S32(0X801C << 16);
            goto L_8007F52C;
    }
    // 0x8007F4EC: lui         $t3, 0x801C
    ctx->r11 = S32(0X801C << 16);
    // 0x8007F4F0: lui         $t5, 0x801C
    ctx->r13 = S32(0X801C << 16);
    // 0x8007F4F4: lw          $t5, 0x3B70($t5)
    ctx->r13 = MEM_W(ctx->r13, 0X3B70);
    // 0x8007F4F8: lui         $t7, 0x801C
    ctx->r15 = S32(0X801C << 16);
    // 0x8007F4FC: lui         $t9, 0x801C
    ctx->r25 = S32(0X801C << 16);
    // 0x8007F500: lw          $t9, 0x3B78($t9)
    ctx->r25 = MEM_W(ctx->r25, 0X3B78);
    // 0x8007F504: lw          $t7, 0x3B68($t7)
    ctx->r15 = MEM_W(ctx->r15, 0X3B68);
    // 0x8007F508: srav        $t6, $v0, $t5
    ctx->r14 = S32(SIGNED(ctx->r2) >> (ctx->r13 & 31));
    // 0x8007F50C: lui         $t3, 0x801C
    ctx->r11 = S32(0X801C << 16);
    // 0x8007F510: srav        $t0, $v1, $t9
    ctx->r8 = S32(SIGNED(ctx->r3) >> (ctx->r25 & 31));
    // 0x8007F514: sllv        $t8, $t6, $t7
    ctx->r24 = S32(ctx->r14 << (ctx->r15 & 31));
    // 0x8007F518: lw          $t3, 0x3B7C($t3)
    ctx->r11 = MEM_W(ctx->r11, 0X3B7C);
    // 0x8007F51C: or          $t1, $t0, $t8
    ctx->r9 = ctx->r8 | ctx->r24;
    // 0x8007F520: sll         $t2, $t1, 1
    ctx->r10 = S32(ctx->r9 << 1);
    // 0x8007F524: b           L_8007F558
    // 0x8007F528: addu        $a0, $t3, $t2
    ctx->r4 = ADD32(ctx->r11, ctx->r10);
        goto L_8007F558;
    // 0x8007F528: addu        $a0, $t3, $t2
    ctx->r4 = ADD32(ctx->r11, ctx->r10);
L_8007F52C:
    // 0x8007F52C: lui         $t4, 0x801C
    ctx->r12 = S32(0X801C << 16);
    // 0x8007F530: lw          $t4, 0x3B78($t4)
    ctx->r12 = MEM_W(ctx->r12, 0X3B78);
    // 0x8007F534: lw          $t6, 0x3B60($t6)
    ctx->r14 = MEM_W(ctx->r14, 0X3B60);
    // 0x8007F538: lw          $t9, 0x3B70($t9)
    ctx->r25 = MEM_W(ctx->r25, 0X3B70);
    // 0x8007F53C: srav        $t5, $v1, $t4
    ctx->r13 = S32(SIGNED(ctx->r3) >> (ctx->r12 & 31));
    // 0x8007F540: lw          $t3, 0x3B7C($t3)
    ctx->r11 = MEM_W(ctx->r11, 0X3B7C);
    // 0x8007F544: sllv        $t7, $t5, $t6
    ctx->r15 = S32(ctx->r13 << (ctx->r14 & 31));
    // 0x8007F548: srav        $t0, $v0, $t9
    ctx->r8 = S32(SIGNED(ctx->r2) >> (ctx->r25 & 31));
    // 0x8007F54C: or          $t8, $t0, $t7
    ctx->r24 = ctx->r8 | ctx->r15;
    // 0x8007F550: sll         $t1, $t8, 1
    ctx->r9 = S32(ctx->r24 << 1);
    // 0x8007F554: addu        $a0, $t3, $t1
    ctx->r4 = ADD32(ctx->r11, ctx->r9);
L_8007F558:
    // 0x8007F558: lhu         $t2, 0x0($a0)
    ctx->r10 = MEM_HU(ctx->r4, 0X0);
    // 0x8007F55C: lui         $t5, 0x801C
    ctx->r13 = S32(0X801C << 16);
    // 0x8007F560: lw          $t5, 0x3B80($t5)
    ctx->r13 = MEM_W(ctx->r13, 0X3B80);
    // 0x8007F564: sll         $t4, $t2, 1
    ctx->r12 = S32(ctx->r10 << 1);
    // 0x8007F568: lui         $a1, 0x801C
    ctx->r5 = S32(0X801C << 16);
    // 0x8007F56C: addu        $v0, $t4, $t5
    ctx->r2 = ADD32(ctx->r12, ctx->r13);
    // 0x8007F570: lhu         $v1, 0x2($v0)
    ctx->r3 = MEM_HU(ctx->r2, 0X2);
    // 0x8007F574: addiu       $v0, $v0, 0x2
    ctx->r2 = ADD32(ctx->r2, 0X2);
    // 0x8007F578: lui         $at, 0x4180
    ctx->r1 = S32(0X4180 << 16);
    // 0x8007F57C: beql        $v1, $zero, L_8007F6DC
    if (ctx->r3 == 0) {
        // 0x8007F580: mtc1        $zero, $f0
        ctx->f0.u32l = 0;
            goto L_8007F6DC;
    }
    goto skip_2;
    // 0x8007F580: mtc1        $zero, $f0
    ctx->f0.u32l = 0;
    skip_2:
    // 0x8007F584: mtc1        $at, $f26
    ctx->f26.u32l = ctx->r1;
    // 0x8007F588: mtc1        $zero, $f24
    ctx->f24.u32l = 0;
    // 0x8007F58C: lw          $a1, 0x3B84($a1)
    ctx->r5 = MEM_W(ctx->r5, 0X3B84);
    // 0x8007F590: addiu       $v1, $v1, -0x1
    ctx->r3 = ADD32(ctx->r3, -0X1);
L_8007F594:
    // 0x8007F594: sll         $t6, $v1, 6
    ctx->r14 = S32(ctx->r3 << 6);
    // 0x8007F598: addu        $a0, $t6, $a1
    ctx->r4 = ADD32(ctx->r14, ctx->r5);
    // 0x8007F59C: lwc1        $f8, 0x0($a0)
    ctx->f8.u32l = MEM_W(ctx->r4, 0X0);
    // 0x8007F5A0: lwc1        $f10, 0x4($a0)
    ctx->f10.u32l = MEM_W(ctx->r4, 0X4);
    // 0x8007F5A4: lwc1        $f6, 0x18($a0)
    ctx->f6.u32l = MEM_W(ctx->r4, 0X18);
    // 0x8007F5A8: sub.s       $f0, $f8, $f12
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f0.fl = ctx->f8.fl - ctx->f12.fl;
    // 0x8007F5AC: lwc1        $f4, 0x8($a0)
    ctx->f4.u32l = MEM_W(ctx->r4, 0X8);
    // 0x8007F5B0: sub.s       $f2, $f10, $f14
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f2.fl = ctx->f10.fl - ctx->f14.fl;
    // 0x8007F5B4: mul.s       $f8, $f6, $f0
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f8.fl = MUL_S(ctx->f6.fl, ctx->f0.fl);
    // 0x8007F5B8: lwc1        $f10, 0x1C($a0)
    ctx->f10.u32l = MEM_W(ctx->r4, 0X1C);
    // 0x8007F5BC: sub.s       $f16, $f4, $f20
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f16.fl = ctx->f4.fl - ctx->f20.fl;
    // 0x8007F5C0: mul.s       $f4, $f2, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f4.fl = MUL_S(ctx->f2.fl, ctx->f10.fl);
    // 0x8007F5C4: lwc1        $f10, 0x20($a0)
    ctx->f10.u32l = MEM_W(ctx->r4, 0X20);
    // 0x8007F5C8: add.s       $f6, $f8, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = ctx->f8.fl + ctx->f4.fl;
    // 0x8007F5CC: mul.s       $f8, $f16, $f10
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f8.fl = MUL_S(ctx->f16.fl, ctx->f10.fl);
    // 0x8007F5D0: add.s       $f4, $f6, $f8
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f4.fl = ctx->f6.fl + ctx->f8.fl;
    // 0x8007F5D4: c.lt.s      $f4, $f24
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 24);
    c1cs = ctx->f4.fl < ctx->f24.fl;
    // 0x8007F5D8: nop

    // 0x8007F5DC: bc1tl       L_8007F6CC
    if (c1cs) {
        // 0x8007F5E0: lhu         $v1, 0x2($v0)
        ctx->r3 = MEM_HU(ctx->r2, 0X2);
            goto L_8007F6CC;
    }
    goto skip_3;
    // 0x8007F5E0: lhu         $v1, 0x2($v0)
    ctx->r3 = MEM_HU(ctx->r2, 0X2);
    skip_3:
    // 0x8007F5E4: lwc1        $f10, 0x24($a0)
    ctx->f10.u32l = MEM_W(ctx->r4, 0X24);
    // 0x8007F5E8: lwc1        $f8, 0x28($a0)
    ctx->f8.u32l = MEM_W(ctx->r4, 0X28);
    // 0x8007F5EC: mul.s       $f6, $f10, $f0
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f6.fl = MUL_S(ctx->f10.fl, ctx->f0.fl);
    // 0x8007F5F0: nop

    // 0x8007F5F4: mul.s       $f4, $f2, $f8
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f4.fl = MUL_S(ctx->f2.fl, ctx->f8.fl);
    // 0x8007F5F8: lwc1        $f8, 0x2C($a0)
    ctx->f8.u32l = MEM_W(ctx->r4, 0X2C);
    // 0x8007F5FC: add.s       $f10, $f6, $f4
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f10.fl = ctx->f6.fl + ctx->f4.fl;
    // 0x8007F600: mul.s       $f6, $f16, $f8
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f6.fl = MUL_S(ctx->f16.fl, ctx->f8.fl);
    // 0x8007F604: add.s       $f4, $f10, $f6
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f4.fl = ctx->f10.fl + ctx->f6.fl;
    // 0x8007F608: c.lt.s      $f4, $f24
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 24);
    c1cs = ctx->f4.fl < ctx->f24.fl;
    // 0x8007F60C: nop

    // 0x8007F610: bc1t        L_8007F6C8
    if (c1cs) {
        // 0x8007F614: nop
    
            goto L_8007F6C8;
    }
    // 0x8007F614: nop

    // 0x8007F618: lwc1        $f8, 0x30($a0)
    ctx->f8.u32l = MEM_W(ctx->r4, 0X30);
    // 0x8007F61C: lwc1        $f6, 0x34($a0)
    ctx->f6.u32l = MEM_W(ctx->r4, 0X34);
    // 0x8007F620: mul.s       $f10, $f8, $f0
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f10.fl = MUL_S(ctx->f8.fl, ctx->f0.fl);
    // 0x8007F624: nop

    // 0x8007F628: mul.s       $f4, $f2, $f6
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f4.fl = MUL_S(ctx->f2.fl, ctx->f6.fl);
    // 0x8007F62C: lwc1        $f6, 0x38($a0)
    ctx->f6.u32l = MEM_W(ctx->r4, 0X38);
    // 0x8007F630: add.s       $f8, $f10, $f4
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f8.fl = ctx->f10.fl + ctx->f4.fl;
    // 0x8007F634: mul.s       $f10, $f16, $f6
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f10.fl = MUL_S(ctx->f16.fl, ctx->f6.fl);
    // 0x8007F638: add.s       $f18, $f8, $f10
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f18.fl = ctx->f8.fl + ctx->f10.fl;
    // 0x8007F63C: c.le.s      $f24, $f18
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 18);
    c1cs = ctx->f24.fl <= ctx->f18.fl;
    // 0x8007F640: nop

    // 0x8007F644: bc1t        L_8007F6C8
    if (c1cs) {
        // 0x8007F648: nop
    
            goto L_8007F6C8;
    }
    // 0x8007F648: nop

    // 0x8007F64C: lwc1        $f4, 0x3C($a0)
    ctx->f4.u32l = MEM_W(ctx->r4, 0X3C);
    // 0x8007F650: c.lt.s      $f18, $f4
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 4);
    c1cs = ctx->f18.fl < ctx->f4.fl;
    // 0x8007F654: nop

    // 0x8007F658: bc1tl       L_8007F6CC
    if (c1cs) {
        // 0x8007F65C: lhu         $v1, 0x2($v0)
        ctx->r3 = MEM_HU(ctx->r2, 0X2);
            goto L_8007F6CC;
    }
    goto skip_4;
    // 0x8007F65C: lhu         $v1, 0x2($v0)
    ctx->r3 = MEM_HU(ctx->r2, 0X2);
    skip_4:
    // 0x8007F660: lwc1        $f22, 0xC($a0)
    ctx->f22.u32l = MEM_W(ctx->r4, 0XC);
    // 0x8007F664: lwc1        $f8, 0x10($a0)
    ctx->f8.u32l = MEM_W(ctx->r4, 0X10);
    // 0x8007F668: mul.s       $f6, $f22, $f0
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f6.fl = MUL_S(ctx->f22.fl, ctx->f0.fl);
    // 0x8007F66C: nop

    // 0x8007F670: mul.s       $f10, $f2, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = MUL_S(ctx->f2.fl, ctx->f8.fl);
    // 0x8007F674: lwc1        $f8, 0x14($a0)
    ctx->f8.u32l = MEM_W(ctx->r4, 0X14);
    // 0x8007F678: add.s       $f4, $f6, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f4.fl = ctx->f6.fl + ctx->f10.fl;
    // 0x8007F67C: mul.s       $f6, $f16, $f8
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f6.fl = MUL_S(ctx->f16.fl, ctx->f8.fl);
    // 0x8007F680: add.s       $f18, $f4, $f6
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f18.fl = ctx->f4.fl + ctx->f6.fl;
    // 0x8007F684: c.lt.s      $f18, $f24
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 24);
    c1cs = ctx->f18.fl < ctx->f24.fl;
    // 0x8007F688: nop

    // 0x8007F68C: bc1t        L_8007F6C8
    if (c1cs) {
        // 0x8007F690: nop
    
            goto L_8007F6C8;
    }
    // 0x8007F690: nop

    // 0x8007F694: c.lt.s      $f26, $f18
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 18);
    c1cs = ctx->f26.fl < ctx->f18.fl;
    // 0x8007F698: nop

    // 0x8007F69C: bc1tl       L_8007F6CC
    if (c1cs) {
        // 0x8007F6A0: lhu         $v1, 0x2($v0)
        ctx->r3 = MEM_HU(ctx->r2, 0X2);
            goto L_8007F6CC;
    }
    goto skip_5;
    // 0x8007F6A0: lhu         $v1, 0x2($v0)
    ctx->r3 = MEM_HU(ctx->r2, 0X2);
    skip_5:
    // 0x8007F6A4: swc1        $f22, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->f22.u32l;
    // 0x8007F6A8: lw          $t9, 0x38($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X38);
    // 0x8007F6AC: lwc1        $f10, 0x10($a0)
    ctx->f10.u32l = MEM_W(ctx->r4, 0X10);
    // 0x8007F6B0: mov.s       $f0, $f18
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 18);
    ctx->f0.fl = ctx->f18.fl;
    // 0x8007F6B4: swc1        $f10, 0x0($t9)
    MEM_W(0X0, ctx->r25) = ctx->f10.u32l;
    // 0x8007F6B8: lw          $t0, 0x3C($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X3C);
    // 0x8007F6BC: lwc1        $f8, 0x14($a0)
    ctx->f8.u32l = MEM_W(ctx->r4, 0X14);
    // 0x8007F6C0: b           L_8007F6E0
    // 0x8007F6C4: swc1        $f8, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->f8.u32l;
        goto L_8007F6E0;
    // 0x8007F6C4: swc1        $f8, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->f8.u32l;
L_8007F6C8:
    // 0x8007F6C8: lhu         $v1, 0x2($v0)
    ctx->r3 = MEM_HU(ctx->r2, 0X2);
L_8007F6CC:
    // 0x8007F6CC: addiu       $v0, $v0, 0x2
    ctx->r2 = ADD32(ctx->r2, 0X2);
    // 0x8007F6D0: bnel        $v1, $zero, L_8007F594
    if (ctx->r3 != 0) {
        // 0x8007F6D4: addiu       $v1, $v1, -0x1
        ctx->r3 = ADD32(ctx->r3, -0X1);
            goto L_8007F594;
    }
    goto skip_6;
    // 0x8007F6D4: addiu       $v1, $v1, -0x1
    ctx->r3 = ADD32(ctx->r3, -0X1);
    skip_6:
    // 0x8007F6D8: mtc1        $zero, $f0
    ctx->f0.u32l = 0;
L_8007F6DC:
    // 0x8007F6DC: nop

L_8007F6E0:
    // 0x8007F6E0: ldc1        $f20, 0x8($sp)
    CHECK_FR(ctx, 20);
    ctx->f20.u64 = LD(ctx->r29, 0X8);
L_8007F6E4:
    // 0x8007F6E4: ldc1        $f22, 0x10($sp)
    CHECK_FR(ctx, 22);
    ctx->f22.u64 = LD(ctx->r29, 0X10);
    // 0x8007F6E8: ldc1        $f24, 0x18($sp)
    CHECK_FR(ctx, 24);
    ctx->f24.u64 = LD(ctx->r29, 0X18);
    // 0x8007F6EC: ldc1        $f26, 0x20($sp)
    CHECK_FR(ctx, 26);
    ctx->f26.u64 = LD(ctx->r29, 0X20);
    // 0x8007F6F0: jr          $ra
    // 0x8007F6F4: addiu       $sp, $sp, 0x28
    ctx->r29 = ADD32(ctx->r29, 0X28);
    return;
    // 0x8007F6F4: addiu       $sp, $sp, 0x28
    ctx->r29 = ADD32(ctx->r29, 0X28);
    // 0x8007F6F8: nop

    // 0x8007F6FC: nop

;}
RECOMP_FUNC void func_8007F700(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8007F700: lui         $t6, 0x801C
    ctx->r14 = S32(0X801C << 16);
    // 0x8007F704: lw          $t6, 0x578($t6)
    ctx->r14 = MEM_W(ctx->r14, 0X578);
    // 0x8007F708: addiu       $sp, $sp, -0xA0
    ctx->r29 = ADD32(ctx->r29, -0XA0);
    // 0x8007F70C: lui         $a2, 0x801C
    ctx->r6 = S32(0X801C << 16);
    // 0x8007F710: addiu       $v1, $a2, -0x288
    ctx->r3 = ADD32(ctx->r6, -0X288);
    // 0x8007F714: sll         $t7, $t6, 6
    ctx->r15 = S32(ctx->r14 << 6);
    // 0x8007F718: addu        $v0, $v1, $t7
    ctx->r2 = ADD32(ctx->r3, ctx->r15);
    // 0x8007F71C: addiu       $v0, $v0, -0x40
    ctx->r2 = ADD32(ctx->r2, -0X40);
    // 0x8007F720: sltu        $at, $v0, $v1
    ctx->r1 = ctx->r2 < ctx->r3 ? 1 : 0;
    // 0x8007F724: sdc1        $f30, 0x30($sp)
    CHECK_FR(ctx, 30);
    SD(ctx->f30.u64, 0X30, ctx->r29);
    // 0x8007F728: sdc1        $f28, 0x28($sp)
    CHECK_FR(ctx, 28);
    SD(ctx->f28.u64, 0X28, ctx->r29);
    // 0x8007F72C: sdc1        $f26, 0x20($sp)
    CHECK_FR(ctx, 26);
    SD(ctx->f26.u64, 0X20, ctx->r29);
    // 0x8007F730: sdc1        $f24, 0x18($sp)
    CHECK_FR(ctx, 24);
    SD(ctx->f24.u64, 0X18, ctx->r29);
    // 0x8007F734: sdc1        $f22, 0x10($sp)
    CHECK_FR(ctx, 22);
    SD(ctx->f22.u64, 0X10, ctx->r29);
    // 0x8007F738: sdc1        $f20, 0x8($sp)
    CHECK_FR(ctx, 20);
    SD(ctx->f20.u64, 0X8, ctx->r29);
    // 0x8007F73C: bne         $at, $zero, L_8007FAC4
    if (ctx->r1 != 0) {
        // 0x8007F740: or          $a1, $a0, $zero
        ctx->r5 = ctx->r4 | 0;
            goto L_8007FAC4;
    }
    // 0x8007F740: or          $a1, $a0, $zero
    ctx->r5 = ctx->r4 | 0;
    // 0x8007F744: addiu       $t1, $a0, 0x90
    ctx->r9 = ADD32(ctx->r4, 0X90);
    // 0x8007F748: addiu       $t5, $zero, 0x1
    ctx->r13 = ADD32(0, 0X1);
    // 0x8007F74C: addiu       $t4, $zero, 0x160
    ctx->r12 = ADD32(0, 0X160);
    // 0x8007F750: addiu       $t3, $zero, 0x100
    ctx->r11 = ADD32(0, 0X100);
    // 0x8007F754: addiu       $t2, $zero, 0x20
    ctx->r10 = ADD32(0, 0X20);
    // 0x8007F758: lw          $a0, 0x28($a1)
    ctx->r4 = MEM_W(ctx->r5, 0X28);
L_8007F75C:
    // 0x8007F75C: sll         $a3, $a0, 5
    ctx->r7 = S32(ctx->r4 << 5);
    // 0x8007F760: addu        $t0, $a1, $a3
    ctx->r8 = ADD32(ctx->r5, ctx->r7);
    // 0x8007F764: addiu       $a2, $t0, 0x90
    ctx->r6 = ADD32(ctx->r8, 0X90);
    // 0x8007F768: sltu        $at, $a2, $t1
    ctx->r1 = ctx->r6 < ctx->r9 ? 1 : 0;
    // 0x8007F76C: bnel        $at, $zero, L_8007FAB8
    if (ctx->r1 != 0) {
        // 0x8007F770: addiu       $v0, $v0, -0x40
        ctx->r2 = ADD32(ctx->r2, -0X40);
            goto L_8007FAB8;
    }
    goto skip_0;
    // 0x8007F770: addiu       $v0, $v0, -0x40
    ctx->r2 = ADD32(ctx->r2, -0X40);
    skip_0:
L_8007F774:
    // 0x8007F774: lwc1        $f4, 0x0($v0)
    ctx->f4.u32l = MEM_W(ctx->r2, 0X0);
    // 0x8007F778: lwc1        $f6, 0x0($a2)
    ctx->f6.u32l = MEM_W(ctx->r6, 0X0);
    // 0x8007F77C: lwc1        $f8, 0x4($v0)
    ctx->f8.u32l = MEM_W(ctx->r2, 0X4);
    // 0x8007F780: lwc1        $f10, 0x4($a2)
    ctx->f10.u32l = MEM_W(ctx->r6, 0X4);
    // 0x8007F784: sub.s       $f2, $f4, $f6
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f2.fl = ctx->f4.fl - ctx->f6.fl;
    // 0x8007F788: lwc1        $f22, 0xC($v0)
    ctx->f22.u32l = MEM_W(ctx->r2, 0XC);
    // 0x8007F78C: lwc1        $f6, 0x8($a2)
    ctx->f6.u32l = MEM_W(ctx->r6, 0X8);
    // 0x8007F790: sub.s       $f0, $f8, $f10
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f0.fl = ctx->f8.fl - ctx->f10.fl;
    // 0x8007F794: mul.s       $f8, $f22, $f2
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f8.fl = MUL_S(ctx->f22.fl, ctx->f2.fl);
    // 0x8007F798: lwc1        $f4, 0x8($v0)
    ctx->f4.u32l = MEM_W(ctx->r2, 0X8);
    // 0x8007F79C: lwc1        $f24, 0x10($v0)
    ctx->f24.u32l = MEM_W(ctx->r2, 0X10);
    // 0x8007F7A0: lwc1        $f26, 0x14($v0)
    ctx->f26.u32l = MEM_W(ctx->r2, 0X14);
    // 0x8007F7A4: mul.s       $f10, $f0, $f24
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 24);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f24.fl); 
    ctx->f10.fl = MUL_S(ctx->f0.fl, ctx->f24.fl);
    // 0x8007F7A8: sub.s       $f12, $f4, $f6
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f12.fl = ctx->f4.fl - ctx->f6.fl;
    // 0x8007F7AC: mul.s       $f6, $f12, $f26
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 26);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f26.fl); 
    ctx->f6.fl = MUL_S(ctx->f12.fl, ctx->f26.fl);
    // 0x8007F7B0: add.s       $f4, $f8, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f4.fl = ctx->f8.fl + ctx->f10.fl;
    // 0x8007F7B4: mtc1        $zero, $f8
    ctx->f8.u32l = 0;
    // 0x8007F7B8: add.s       $f16, $f4, $f6
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f16.fl = ctx->f4.fl + ctx->f6.fl;
    // 0x8007F7BC: c.lt.s      $f16, $f8
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 8);
    c1cs = ctx->f16.fl < ctx->f8.fl;
    // 0x8007F7C0: nop

    // 0x8007F7C4: bc1tl       L_8007FAA8
    if (c1cs) {
        // 0x8007F7C8: addiu       $a2, $a2, -0x20
        ctx->r6 = ADD32(ctx->r6, -0X20);
            goto L_8007FAA8;
    }
    goto skip_1;
    // 0x8007F7C8: addiu       $a2, $a2, -0x20
    ctx->r6 = ADD32(ctx->r6, -0X20);
    skip_1:
    // 0x8007F7CC: lwc1        $f28, 0x30($v0)
    ctx->f28.u32l = MEM_W(ctx->r2, 0X30);
    // 0x8007F7D0: c.le.s      $f28, $f16
    CHECK_FR(ctx, 28);
    CHECK_FR(ctx, 16);
    c1cs = ctx->f28.fl <= ctx->f16.fl;
    // 0x8007F7D4: nop

    // 0x8007F7D8: bc1tl       L_8007FAA8
    if (c1cs) {
        // 0x8007F7DC: addiu       $a2, $a2, -0x20
        ctx->r6 = ADD32(ctx->r6, -0X20);
            goto L_8007FAA8;
    }
    goto skip_2;
    // 0x8007F7DC: addiu       $a2, $a2, -0x20
    ctx->r6 = ADD32(ctx->r6, -0X20);
    skip_2:
    // 0x8007F7E0: lwc1        $f30, 0x18($v0)
    ctx->f30.u32l = MEM_W(ctx->r2, 0X18);
    // 0x8007F7E4: lwc1        $f18, 0x1C($v0)
    ctx->f18.u32l = MEM_W(ctx->r2, 0X1C);
    // 0x8007F7E8: lwc1        $f20, 0x20($v0)
    ctx->f20.u32l = MEM_W(ctx->r2, 0X20);
    // 0x8007F7EC: mul.s       $f10, $f30, $f2
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 30);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f30.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f10.fl = MUL_S(ctx->f30.fl, ctx->f2.fl);
    // 0x8007F7F0: swc1        $f18, 0x54($sp)
    MEM_W(0X54, ctx->r29) = ctx->f18.u32l;
    // 0x8007F7F4: swc1        $f20, 0x50($sp)
    MEM_W(0X50, ctx->r29) = ctx->f20.u32l;
    // 0x8007F7F8: mul.s       $f4, $f0, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f4.fl = MUL_S(ctx->f0.fl, ctx->f18.fl);
    // 0x8007F7FC: add.s       $f6, $f10, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = ctx->f10.fl + ctx->f4.fl;
    // 0x8007F800: mul.s       $f8, $f12, $f20
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f8.fl = MUL_S(ctx->f12.fl, ctx->f20.fl);
    // 0x8007F804: mtc1        $zero, $f10
    ctx->f10.u32l = 0;
    // 0x8007F808: add.s       $f14, $f6, $f8
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f14.fl = ctx->f6.fl + ctx->f8.fl;
    // 0x8007F80C: c.lt.s      $f14, $f10
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 10);
    c1cs = ctx->f14.fl < ctx->f10.fl;
    // 0x8007F810: nop

    // 0x8007F814: bc1tl       L_8007FAA8
    if (c1cs) {
        // 0x8007F818: addiu       $a2, $a2, -0x20
        ctx->r6 = ADD32(ctx->r6, -0X20);
            goto L_8007FAA8;
    }
    goto skip_3;
    // 0x8007F818: addiu       $a2, $a2, -0x20
    ctx->r6 = ADD32(ctx->r6, -0X20);
    skip_3:
    // 0x8007F81C: lwc1        $f18, 0x34($v0)
    ctx->f18.u32l = MEM_W(ctx->r2, 0X34);
    // 0x8007F820: c.le.s      $f18, $f14
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 14);
    c1cs = ctx->f18.fl <= ctx->f14.fl;
    // 0x8007F824: swc1        $f18, 0x4C($sp)
    MEM_W(0X4C, ctx->r29) = ctx->f18.u32l;
    // 0x8007F828: bc1tl       L_8007FAA8
    if (c1cs) {
        // 0x8007F82C: addiu       $a2, $a2, -0x20
        ctx->r6 = ADD32(ctx->r6, -0X20);
            goto L_8007FAA8;
    }
    goto skip_4;
    // 0x8007F82C: addiu       $a2, $a2, -0x20
    ctx->r6 = ADD32(ctx->r6, -0X20);
    skip_4:
    // 0x8007F830: lwc1        $f4, 0x28($v0)
    ctx->f4.u32l = MEM_W(ctx->r2, 0X28);
    // 0x8007F834: lwc1        $f20, 0x24($v0)
    ctx->f20.u32l = MEM_W(ctx->r2, 0X24);
    // 0x8007F838: swc1        $f4, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->f4.u32l;
    // 0x8007F83C: mul.s       $f8, $f20, $f2
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f8.fl = MUL_S(ctx->f20.fl, ctx->f2.fl);
    // 0x8007F840: lwc1        $f10, 0x44($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0X44);
    // 0x8007F844: lwc1        $f6, 0x2C($v0)
    ctx->f6.u32l = MEM_W(ctx->r2, 0X2C);
    // 0x8007F848: swc1        $f20, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->f20.u32l;
    // 0x8007F84C: mul.s       $f4, $f0, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f4.fl = MUL_S(ctx->f0.fl, ctx->f10.fl);
    // 0x8007F850: swc1        $f6, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->f6.u32l;
    // 0x8007F854: lwc1        $f10, 0x40($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0X40);
    // 0x8007F858: add.s       $f6, $f8, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = ctx->f8.fl + ctx->f4.fl;
    // 0x8007F85C: mul.s       $f8, $f12, $f10
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f8.fl = MUL_S(ctx->f12.fl, ctx->f10.fl);
    // 0x8007F860: mtc1        $zero, $f4
    ctx->f4.u32l = 0;
    // 0x8007F864: add.s       $f18, $f6, $f8
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f18.fl = ctx->f6.fl + ctx->f8.fl;
    // 0x8007F868: c.lt.s      $f18, $f4
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 4);
    c1cs = ctx->f18.fl < ctx->f4.fl;
    // 0x8007F86C: nop

    // 0x8007F870: bc1tl       L_8007FAA8
    if (c1cs) {
        // 0x8007F874: addiu       $a2, $a2, -0x20
        ctx->r6 = ADD32(ctx->r6, -0X20);
            goto L_8007FAA8;
    }
    goto skip_5;
    // 0x8007F874: addiu       $a2, $a2, -0x20
    ctx->r6 = ADD32(ctx->r6, -0X20);
    skip_5:
    // 0x8007F878: lwc1        $f0, 0x38($v0)
    ctx->f0.u32l = MEM_W(ctx->r2, 0X38);
    // 0x8007F87C: lwc1        $f10, 0x4C($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0X4C);
    // 0x8007F880: c.le.s      $f0, $f18
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 18);
    c1cs = ctx->f0.fl <= ctx->f18.fl;
    // 0x8007F884: swc1        $f0, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->f0.u32l;
    // 0x8007F888: lwc1        $f6, 0x3C($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X3C);
    // 0x8007F88C: bc1tl       L_8007FAA8
    if (c1cs) {
        // 0x8007F890: addiu       $a2, $a2, -0x20
        ctx->r6 = ADD32(ctx->r6, -0X20);
            goto L_8007FAA8;
    }
    goto skip_6;
    // 0x8007F890: addiu       $a2, $a2, -0x20
    ctx->r6 = ADD32(ctx->r6, -0X20);
    skip_6:
    // 0x8007F894: sub.s       $f20, $f28, $f16
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 28);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f28.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f20.fl = ctx->f28.fl - ctx->f16.fl;
    // 0x8007F898: mtc1        $zero, $f8
    ctx->f8.u32l = 0;
    // 0x8007F89C: c.lt.s      $f20, $f16
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 16);
    c1cs = ctx->f20.fl < ctx->f16.fl;
    // 0x8007F8A0: nop

    // 0x8007F8A4: bc1fl       L_8007F8C4
    if (!c1cs) {
        // 0x8007F8A8: mov.s       $f2, $f22
        CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 22);
    ctx->f2.fl = ctx->f22.fl;
            goto L_8007F8C4;
    }
    goto skip_7;
    // 0x8007F8A8: mov.s       $f2, $f22
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 22);
    ctx->f2.fl = ctx->f22.fl;
    skip_7:
    // 0x8007F8AC: mov.s       $f16, $f20
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 20);
    ctx->f16.fl = ctx->f20.fl;
    // 0x8007F8B0: neg.s       $f2, $f22
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f22.fl); 
    ctx->f2.fl = -ctx->f22.fl;
    // 0x8007F8B4: neg.s       $f0, $f24
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 24);
    NAN_CHECK(ctx->f24.fl); 
    ctx->f0.fl = -ctx->f24.fl;
    // 0x8007F8B8: b           L_8007F8CC
    // 0x8007F8BC: neg.s       $f12, $f26
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 26);
    NAN_CHECK(ctx->f26.fl); 
    ctx->f12.fl = -ctx->f26.fl;
        goto L_8007F8CC;
    // 0x8007F8BC: neg.s       $f12, $f26
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 26);
    NAN_CHECK(ctx->f26.fl); 
    ctx->f12.fl = -ctx->f26.fl;
    // 0x8007F8C0: mov.s       $f2, $f22
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 22);
    ctx->f2.fl = ctx->f22.fl;
L_8007F8C4:
    // 0x8007F8C4: mov.s       $f0, $f24
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 24);
    ctx->f0.fl = ctx->f24.fl;
    // 0x8007F8C8: mov.s       $f12, $f26
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 26);
    ctx->f12.fl = ctx->f26.fl;
L_8007F8CC:
    // 0x8007F8CC: c.lt.s      $f14, $f16
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 16);
    c1cs = ctx->f14.fl < ctx->f16.fl;
    // 0x8007F8D0: sub.s       $f20, $f10, $f14
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f20.fl = ctx->f10.fl - ctx->f14.fl;
    // 0x8007F8D4: bc1fl       L_8007F8F0
    if (!c1cs) {
        // 0x8007F8D8: c.lt.s      $f20, $f16
        CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 16);
    c1cs = ctx->f20.fl < ctx->f16.fl;
            goto L_8007F8F0;
    }
    goto skip_8;
    // 0x8007F8D8: c.lt.s      $f20, $f16
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 16);
    c1cs = ctx->f20.fl < ctx->f16.fl;
    skip_8:
    // 0x8007F8DC: mov.s       $f16, $f14
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 14);
    ctx->f16.fl = ctx->f14.fl;
    // 0x8007F8E0: mov.s       $f2, $f30
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 30);
    ctx->f2.fl = ctx->f30.fl;
    // 0x8007F8E4: lwc1        $f0, 0x54($sp)
    ctx->f0.u32l = MEM_W(ctx->r29, 0X54);
    // 0x8007F8E8: lwc1        $f12, 0x50($sp)
    ctx->f12.u32l = MEM_W(ctx->r29, 0X50);
    // 0x8007F8EC: c.lt.s      $f20, $f16
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 16);
    c1cs = ctx->f20.fl < ctx->f16.fl;
L_8007F8F0:
    // 0x8007F8F0: sub.s       $f14, $f6, $f18
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f14.fl = ctx->f6.fl - ctx->f18.fl;
    // 0x8007F8F4: bc1fl       L_8007F918
    if (!c1cs) {
        // 0x8007F8F8: c.lt.s      $f18, $f16
        CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    c1cs = ctx->f18.fl < ctx->f16.fl;
            goto L_8007F918;
    }
    goto skip_9;
    // 0x8007F8F8: c.lt.s      $f18, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    c1cs = ctx->f18.fl < ctx->f16.fl;
    skip_9:
    // 0x8007F8FC: lwc1        $f0, 0x54($sp)
    ctx->f0.u32l = MEM_W(ctx->r29, 0X54);
    // 0x8007F900: lwc1        $f12, 0x50($sp)
    ctx->f12.u32l = MEM_W(ctx->r29, 0X50);
    // 0x8007F904: mov.s       $f16, $f20
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 20);
    ctx->f16.fl = ctx->f20.fl;
    // 0x8007F908: neg.s       $f2, $f30
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 30);
    NAN_CHECK(ctx->f30.fl); 
    ctx->f2.fl = -ctx->f30.fl;
    // 0x8007F90C: neg.s       $f0, $f0
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f0.fl); 
    ctx->f0.fl = -ctx->f0.fl;
    // 0x8007F910: neg.s       $f12, $f12
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f12.fl); 
    ctx->f12.fl = -ctx->f12.fl;
    // 0x8007F914: c.lt.s      $f18, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    c1cs = ctx->f18.fl < ctx->f16.fl;
L_8007F918:
    // 0x8007F918: nop

    // 0x8007F91C: bc1fl       L_8007F938
    if (!c1cs) {
        // 0x8007F920: c.lt.s      $f14, $f16
        CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 16);
    c1cs = ctx->f14.fl < ctx->f16.fl;
            goto L_8007F938;
    }
    goto skip_10;
    // 0x8007F920: c.lt.s      $f14, $f16
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 16);
    c1cs = ctx->f14.fl < ctx->f16.fl;
    skip_10:
    // 0x8007F924: mov.s       $f16, $f18
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 18);
    ctx->f16.fl = ctx->f18.fl;
    // 0x8007F928: lwc1        $f2, 0x48($sp)
    ctx->f2.u32l = MEM_W(ctx->r29, 0X48);
    // 0x8007F92C: lwc1        $f0, 0x44($sp)
    ctx->f0.u32l = MEM_W(ctx->r29, 0X44);
    // 0x8007F930: lwc1        $f12, 0x40($sp)
    ctx->f12.u32l = MEM_W(ctx->r29, 0X40);
    // 0x8007F934: c.lt.s      $f14, $f16
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 16);
    c1cs = ctx->f14.fl < ctx->f16.fl;
L_8007F938:
    // 0x8007F938: nop

    // 0x8007F93C: bc1fl       L_8007F964
    if (!c1cs) {
        // 0x8007F940: c.le.s      $f0, $f8
        CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 8);
    c1cs = ctx->f0.fl <= ctx->f8.fl;
            goto L_8007F964;
    }
    goto skip_11;
    // 0x8007F940: c.le.s      $f0, $f8
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 8);
    c1cs = ctx->f0.fl <= ctx->f8.fl;
    skip_11:
    // 0x8007F944: lwc1        $f2, 0x48($sp)
    ctx->f2.u32l = MEM_W(ctx->r29, 0X48);
    // 0x8007F948: lwc1        $f0, 0x44($sp)
    ctx->f0.u32l = MEM_W(ctx->r29, 0X44);
    // 0x8007F94C: lwc1        $f12, 0x40($sp)
    ctx->f12.u32l = MEM_W(ctx->r29, 0X40);
    // 0x8007F950: mov.s       $f16, $f14
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 14);
    ctx->f16.fl = ctx->f14.fl;
    // 0x8007F954: neg.s       $f2, $f2
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f2.fl); 
    ctx->f2.fl = -ctx->f2.fl;
    // 0x8007F958: neg.s       $f0, $f0
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f0.fl); 
    ctx->f0.fl = -ctx->f0.fl;
    // 0x8007F95C: neg.s       $f12, $f12
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f12.fl); 
    ctx->f12.fl = -ctx->f12.fl;
    // 0x8007F960: c.le.s      $f0, $f8
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 8);
    c1cs = ctx->f0.fl <= ctx->f8.fl;
L_8007F964:
    // 0x8007F964: nop

    // 0x8007F968: bc1fl       L_8007F98C
    if (!c1cs) {
        // 0x8007F96C: lwc1        $f10, 0xC($a2)
        ctx->f10.u32l = MEM_W(ctx->r6, 0XC);
            goto L_8007F98C;
    }
    goto skip_12;
    // 0x8007F96C: lwc1        $f10, 0xC($a2)
    ctx->f10.u32l = MEM_W(ctx->r6, 0XC);
    skip_12:
    // 0x8007F970: beql        $a3, $t2, L_8007FAA8
    if (ctx->r7 == ctx->r10) {
        // 0x8007F974: addiu       $a2, $a2, -0x20
        ctx->r6 = ADD32(ctx->r6, -0X20);
            goto L_8007FAA8;
    }
    goto skip_13;
    // 0x8007F974: addiu       $a2, $a2, -0x20
    ctx->r6 = ADD32(ctx->r6, -0X20);
    skip_13:
    // 0x8007F978: beql        $a3, $t3, L_8007FAA8
    if (ctx->r7 == ctx->r11) {
        // 0x8007F97C: addiu       $a2, $a2, -0x20
        ctx->r6 = ADD32(ctx->r6, -0X20);
            goto L_8007FAA8;
    }
    goto skip_14;
    // 0x8007F97C: addiu       $a2, $a2, -0x20
    ctx->r6 = ADD32(ctx->r6, -0X20);
    skip_14:
    // 0x8007F980: beql        $a3, $t4, L_8007FAA8
    if (ctx->r7 == ctx->r12) {
        // 0x8007F984: addiu       $a2, $a2, -0x20
        ctx->r6 = ADD32(ctx->r6, -0X20);
            goto L_8007FAA8;
    }
    goto skip_15;
    // 0x8007F984: addiu       $a2, $a2, -0x20
    ctx->r6 = ADD32(ctx->r6, -0X20);
    skip_15:
    // 0x8007F988: lwc1        $f10, 0xC($a2)
    ctx->f10.u32l = MEM_W(ctx->r6, 0XC);
L_8007F98C:
    // 0x8007F98C: neg.s       $f4, $f2
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f2.fl); 
    ctx->f4.fl = -ctx->f2.fl;
    // 0x8007F990: lwc1        $f8, 0x10($a2)
    ctx->f8.u32l = MEM_W(ctx->r6, 0X10);
    // 0x8007F994: mul.s       $f6, $f4, $f10
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f6.fl = MUL_S(ctx->f4.fl, ctx->f10.fl);
    // 0x8007F998: lw          $t8, 0x3C($v0)
    ctx->r24 = MEM_W(ctx->r2, 0X3C);
    // 0x8007F99C: or          $a0, $t1, $zero
    ctx->r4 = ctx->r9 | 0;
    // 0x8007F9A0: mul.s       $f4, $f0, $f8
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f4.fl = MUL_S(ctx->f0.fl, ctx->f8.fl);
    // 0x8007F9A4: lwc1        $f8, 0x14($a2)
    ctx->f8.u32l = MEM_W(ctx->r6, 0X14);
    // 0x8007F9A8: addiu       $t0, $a1, 0x210
    ctx->r8 = ADD32(ctx->r5, 0X210);
    // 0x8007F9AC: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x8007F9B0: sub.s       $f10, $f6, $f4
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f10.fl = ctx->f6.fl - ctx->f4.fl;
    // 0x8007F9B4: mul.s       $f6, $f12, $f8
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f6.fl = MUL_S(ctx->f12.fl, ctx->f8.fl);
    // 0x8007F9B8: beq         $t8, $zero, L_8007F9D4
    if (ctx->r24 == 0) {
        // 0x8007F9BC: sub.s       $f14, $f10, $f6
        CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f14.fl = ctx->f10.fl - ctx->f6.fl;
            goto L_8007F9D4;
    }
    // 0x8007F9BC: sub.s       $f14, $f10, $f6
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f14.fl = ctx->f10.fl - ctx->f6.fl;
    // 0x8007F9C0: sh          $t5, 0x15DE($a1)
    MEM_H(0X15DE, ctx->r5) = ctx->r13;
    // 0x8007F9C4: lwc1        $f4, -0x5C10($at)
    ctx->f4.u32l = MEM_W(ctx->r1, -0X5C10);
    // 0x8007F9C8: mul.s       $f18, $f4, $f14
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f18.fl = MUL_S(ctx->f4.fl, ctx->f14.fl);
    // 0x8007F9CC: b           L_8007F9DC
    // 0x8007F9D0: lwc1        $f8, 0xC48($a1)
    ctx->f8.u32l = MEM_W(ctx->r5, 0XC48);
        goto L_8007F9DC;
    // 0x8007F9D0: lwc1        $f8, 0xC48($a1)
    ctx->f8.u32l = MEM_W(ctx->r5, 0XC48);
L_8007F9D4:
    // 0x8007F9D4: mov.s       $f18, $f14
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 14);
    ctx->f18.fl = ctx->f14.fl;
    // 0x8007F9D8: lwc1        $f8, 0xC48($a1)
    ctx->f8.u32l = MEM_W(ctx->r5, 0XC48);
L_8007F9DC:
    // 0x8007F9DC: mul.s       $f6, $f14, $f2
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f6.fl = MUL_S(ctx->f14.fl, ctx->f2.fl);
    // 0x8007F9E0: c.lt.s      $f8, $f18
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 18);
    c1cs = ctx->f8.fl < ctx->f18.fl;
    // 0x8007F9E4: nop

    // 0x8007F9E8: bc1fl       L_8007FA04
    if (!c1cs) {
        // 0x8007F9EC: lwc1        $f10, 0xC($a2)
        ctx->f10.u32l = MEM_W(ctx->r6, 0XC);
            goto L_8007FA04;
    }
    goto skip_16;
    // 0x8007F9EC: lwc1        $f10, 0xC($a2)
    ctx->f10.u32l = MEM_W(ctx->r6, 0XC);
    skip_16:
    // 0x8007F9F0: swc1        $f18, 0xC48($a1)
    MEM_W(0XC48, ctx->r5) = ctx->f18.u32l;
    // 0x8007F9F4: swc1        $f2, 0x15B4($a1)
    MEM_W(0X15B4, ctx->r5) = ctx->f2.u32l;
    // 0x8007F9F8: swc1        $f0, 0x15B8($a1)
    MEM_W(0X15B8, ctx->r5) = ctx->f0.u32l;
    // 0x8007F9FC: swc1        $f12, 0x15BC($a1)
    MEM_W(0X15BC, ctx->r5) = ctx->f12.u32l;
    // 0x8007FA00: lwc1        $f10, 0xC($a2)
    ctx->f10.u32l = MEM_W(ctx->r6, 0XC);
L_8007FA04:
    // 0x8007FA04: lwc1        $f8, 0x10($a2)
    ctx->f8.u32l = MEM_W(ctx->r6, 0X10);
    // 0x8007FA08: sltu        $at, $t1, $t0
    ctx->r1 = ctx->r9 < ctx->r8 ? 1 : 0;
    // 0x8007FA0C: add.s       $f4, $f10, $f6
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f4.fl = ctx->f10.fl + ctx->f6.fl;
    // 0x8007FA10: mul.s       $f10, $f14, $f0
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f10.fl = MUL_S(ctx->f14.fl, ctx->f0.fl);
    // 0x8007FA14: swc1        $f4, 0xC($a2)
    MEM_W(0XC, ctx->r6) = ctx->f4.u32l;
    // 0x8007FA18: lwc1        $f4, 0x14($a2)
    ctx->f4.u32l = MEM_W(ctx->r6, 0X14);
    // 0x8007FA1C: add.s       $f6, $f8, $f10
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f6.fl = ctx->f8.fl + ctx->f10.fl;
    // 0x8007FA20: mul.s       $f8, $f14, $f12
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f8.fl = MUL_S(ctx->f14.fl, ctx->f12.fl);
    // 0x8007FA24: swc1        $f6, 0x10($a2)
    MEM_W(0X10, ctx->r6) = ctx->f6.u32l;
    // 0x8007FA28: mul.s       $f2, $f2, $f16
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f2.fl = MUL_S(ctx->f2.fl, ctx->f16.fl);
    // 0x8007FA2C: nop

    // 0x8007FA30: mul.s       $f0, $f0, $f16
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f0.fl = MUL_S(ctx->f0.fl, ctx->f16.fl);
    // 0x8007FA34: add.s       $f10, $f4, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = ctx->f4.fl + ctx->f8.fl;
    // 0x8007FA38: mul.s       $f12, $f12, $f16
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f12.fl = MUL_S(ctx->f12.fl, ctx->f16.fl);
    // 0x8007FA3C: beq         $at, $zero, L_8007FAA4
    if (ctx->r1 == 0) {
        // 0x8007FA40: swc1        $f10, 0x14($a2)
        MEM_W(0X14, ctx->r6) = ctx->f10.u32l;
            goto L_8007FAA4;
    }
    // 0x8007FA40: swc1        $f10, 0x14($a2)
    MEM_W(0X14, ctx->r6) = ctx->f10.u32l;
    // 0x8007FA44: addiu       $a0, $a0, 0x20
    ctx->r4 = ADD32(ctx->r4, 0X20);
    // 0x8007FA48: sltu        $at, $a0, $t0
    ctx->r1 = ctx->r4 < ctx->r8 ? 1 : 0;
    // 0x8007FA4C: beq         $at, $zero, L_8007FA84
    if (ctx->r1 == 0) {
        // 0x8007FA50: lwc1        $f30, -0x20($a0)
        ctx->f30.u32l = MEM_W(ctx->r4, -0X20);
            goto L_8007FA84;
    }
    // 0x8007FA50: lwc1        $f30, -0x20($a0)
    ctx->f30.u32l = MEM_W(ctx->r4, -0X20);
L_8007FA54:
    // 0x8007FA54: add.s       $f28, $f30, $f2
    CHECK_FR(ctx, 28);
    CHECK_FR(ctx, 30);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f30.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f28.fl = ctx->f30.fl + ctx->f2.fl;
    // 0x8007FA58: lwc1        $f26, -0x1C($a0)
    ctx->f26.u32l = MEM_W(ctx->r4, -0X1C);
    // 0x8007FA5C: lwc1        $f24, -0x18($a0)
    ctx->f24.u32l = MEM_W(ctx->r4, -0X18);
    // 0x8007FA60: lwc1        $f30, 0x0($a0)
    ctx->f30.u32l = MEM_W(ctx->r4, 0X0);
    // 0x8007FA64: add.s       $f26, $f26, $f0
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f26.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f26.fl = ctx->f26.fl + ctx->f0.fl;
    // 0x8007FA68: addiu       $a0, $a0, 0x20
    ctx->r4 = ADD32(ctx->r4, 0X20);
    // 0x8007FA6C: sltu        $at, $a0, $t0
    ctx->r1 = ctx->r4 < ctx->r8 ? 1 : 0;
    // 0x8007FA70: add.s       $f24, $f24, $f12
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f24.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f24.fl = ctx->f24.fl + ctx->f12.fl;
    // 0x8007FA74: swc1        $f28, -0x40($a0)
    MEM_W(-0X40, ctx->r4) = ctx->f28.u32l;
    // 0x8007FA78: swc1        $f26, -0x3C($a0)
    MEM_W(-0X3C, ctx->r4) = ctx->f26.u32l;
    // 0x8007FA7C: bne         $at, $zero, L_8007FA54
    if (ctx->r1 != 0) {
        // 0x8007FA80: swc1        $f24, -0x38($a0)
        MEM_W(-0X38, ctx->r4) = ctx->f24.u32l;
            goto L_8007FA54;
    }
    // 0x8007FA80: swc1        $f24, -0x38($a0)
    MEM_W(-0X38, ctx->r4) = ctx->f24.u32l;
L_8007FA84:
    // 0x8007FA84: lwc1        $f26, -0x1C($a0)
    ctx->f26.u32l = MEM_W(ctx->r4, -0X1C);
    // 0x8007FA88: lwc1        $f24, -0x18($a0)
    ctx->f24.u32l = MEM_W(ctx->r4, -0X18);
    // 0x8007FA8C: add.s       $f28, $f30, $f2
    CHECK_FR(ctx, 28);
    CHECK_FR(ctx, 30);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f30.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f28.fl = ctx->f30.fl + ctx->f2.fl;
    // 0x8007FA90: add.s       $f26, $f26, $f0
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f26.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f26.fl = ctx->f26.fl + ctx->f0.fl;
    // 0x8007FA94: swc1        $f28, -0x20($a0)
    MEM_W(-0X20, ctx->r4) = ctx->f28.u32l;
    // 0x8007FA98: add.s       $f24, $f24, $f12
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f24.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f24.fl = ctx->f24.fl + ctx->f12.fl;
    // 0x8007FA9C: swc1        $f26, -0x1C($a0)
    MEM_W(-0X1C, ctx->r4) = ctx->f26.u32l;
    // 0x8007FAA0: swc1        $f24, -0x18($a0)
    MEM_W(-0X18, ctx->r4) = ctx->f24.u32l;
L_8007FAA4:
    // 0x8007FAA4: addiu       $a2, $a2, -0x20
    ctx->r6 = ADD32(ctx->r6, -0X20);
L_8007FAA8:
    // 0x8007FAA8: sltu        $at, $a2, $t1
    ctx->r1 = ctx->r6 < ctx->r9 ? 1 : 0;
    // 0x8007FAAC: beq         $at, $zero, L_8007F774
    if (ctx->r1 == 0) {
        // 0x8007FAB0: addiu       $a3, $a3, -0x20
        ctx->r7 = ADD32(ctx->r7, -0X20);
            goto L_8007F774;
    }
    // 0x8007FAB0: addiu       $a3, $a3, -0x20
    ctx->r7 = ADD32(ctx->r7, -0X20);
    // 0x8007FAB4: addiu       $v0, $v0, -0x40
    ctx->r2 = ADD32(ctx->r2, -0X40);
L_8007FAB8:
    // 0x8007FAB8: sltu        $at, $v0, $v1
    ctx->r1 = ctx->r2 < ctx->r3 ? 1 : 0;
    // 0x8007FABC: beql        $at, $zero, L_8007F75C
    if (ctx->r1 == 0) {
        // 0x8007FAC0: lw          $a0, 0x28($a1)
        ctx->r4 = MEM_W(ctx->r5, 0X28);
            goto L_8007F75C;
    }
    goto skip_17;
    // 0x8007FAC0: lw          $a0, 0x28($a1)
    ctx->r4 = MEM_W(ctx->r5, 0X28);
    skip_17:
L_8007FAC4:
    // 0x8007FAC4: ldc1        $f20, 0x8($sp)
    CHECK_FR(ctx, 20);
    ctx->f20.u64 = LD(ctx->r29, 0X8);
    // 0x8007FAC8: ldc1        $f22, 0x10($sp)
    CHECK_FR(ctx, 22);
    ctx->f22.u64 = LD(ctx->r29, 0X10);
    // 0x8007FACC: ldc1        $f24, 0x18($sp)
    CHECK_FR(ctx, 24);
    ctx->f24.u64 = LD(ctx->r29, 0X18);
    // 0x8007FAD0: ldc1        $f26, 0x20($sp)
    CHECK_FR(ctx, 26);
    ctx->f26.u64 = LD(ctx->r29, 0X20);
    // 0x8007FAD4: ldc1        $f28, 0x28($sp)
    CHECK_FR(ctx, 28);
    ctx->f28.u64 = LD(ctx->r29, 0X28);
    // 0x8007FAD8: ldc1        $f30, 0x30($sp)
    CHECK_FR(ctx, 30);
    ctx->f30.u64 = LD(ctx->r29, 0X30);
    // 0x8007FADC: jr          $ra
    // 0x8007FAE0: addiu       $sp, $sp, 0xA0
    ctx->r29 = ADD32(ctx->r29, 0XA0);
    return;
    // 0x8007FAE0: addiu       $sp, $sp, 0xA0
    ctx->r29 = ADD32(ctx->r29, 0XA0);
;}
RECOMP_FUNC void func_8007FAE4(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8007FAE4: addiu       $sp, $sp, -0x88
    ctx->r29 = ADD32(ctx->r29, -0X88);
    // 0x8007FAE8: lui         $t6, 0x801C
    ctx->r14 = S32(0X801C << 16);
    // 0x8007FAEC: lw          $t6, 0x578($t6)
    ctx->r14 = MEM_W(ctx->r14, 0X578);
    // 0x8007FAF0: lui         $a0, 0x801C
    ctx->r4 = S32(0X801C << 16);
    // 0x8007FAF4: addiu       $v1, $a0, -0x288
    ctx->r3 = ADD32(ctx->r4, -0X288);
    // 0x8007FAF8: sll         $t7, $t6, 6
    ctx->r15 = S32(ctx->r14 << 6);
    // 0x8007FAFC: addu        $v0, $v1, $t7
    ctx->r2 = ADD32(ctx->r3, ctx->r15);
    // 0x8007FB00: addiu       $v0, $v0, -0x40
    ctx->r2 = ADD32(ctx->r2, -0X40);
    // 0x8007FB04: sltu        $at, $v0, $v1
    ctx->r1 = ctx->r2 < ctx->r3 ? 1 : 0;
    // 0x8007FB08: sdc1        $f30, 0x30($sp)
    CHECK_FR(ctx, 30);
    SD(ctx->f30.u64, 0X30, ctx->r29);
    // 0x8007FB0C: sdc1        $f28, 0x28($sp)
    CHECK_FR(ctx, 28);
    SD(ctx->f28.u64, 0X28, ctx->r29);
    // 0x8007FB10: sdc1        $f26, 0x20($sp)
    CHECK_FR(ctx, 26);
    SD(ctx->f26.u64, 0X20, ctx->r29);
    // 0x8007FB14: sdc1        $f24, 0x18($sp)
    CHECK_FR(ctx, 24);
    SD(ctx->f24.u64, 0X18, ctx->r29);
    // 0x8007FB18: sdc1        $f22, 0x10($sp)
    CHECK_FR(ctx, 22);
    SD(ctx->f22.u64, 0X10, ctx->r29);
    // 0x8007FB1C: sdc1        $f20, 0x8($sp)
    CHECK_FR(ctx, 20);
    SD(ctx->f20.u64, 0X8, ctx->r29);
    // 0x8007FB20: swc1        $f12, 0x88($sp)
    MEM_W(0X88, ctx->r29) = ctx->f12.u32l;
    // 0x8007FB24: swc1        $f14, 0x8C($sp)
    MEM_W(0X8C, ctx->r29) = ctx->f14.u32l;
    // 0x8007FB28: bne         $at, $zero, L_8007FD4C
    if (ctx->r1 != 0) {
        // 0x8007FB2C: sw          $a2, 0x90($sp)
        MEM_W(0X90, ctx->r29) = ctx->r6;
            goto L_8007FD4C;
    }
    // 0x8007FB2C: sw          $a2, 0x90($sp)
    MEM_W(0X90, ctx->r29) = ctx->r6;
    // 0x8007FB30: mtc1        $zero, $f18
    ctx->f18.u32l = 0;
    // 0x8007FB34: nop

    // 0x8007FB38: lwc1        $f4, 0x0($v0)
    ctx->f4.u32l = MEM_W(ctx->r2, 0X0);
L_8007FB3C:
    // 0x8007FB3C: lwc1        $f6, 0x88($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X88);
    // 0x8007FB40: lwc1        $f8, 0x4($v0)
    ctx->f8.u32l = MEM_W(ctx->r2, 0X4);
    // 0x8007FB44: lwc1        $f10, 0x8C($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0X8C);
    // 0x8007FB48: sub.s       $f2, $f4, $f6
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f2.fl = ctx->f4.fl - ctx->f6.fl;
    // 0x8007FB4C: lwc1        $f20, 0xC($v0)
    ctx->f20.u32l = MEM_W(ctx->r2, 0XC);
    // 0x8007FB50: lwc1        $f6, 0x90($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X90);
    // 0x8007FB54: sub.s       $f12, $f8, $f10
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f12.fl = ctx->f8.fl - ctx->f10.fl;
    // 0x8007FB58: mul.s       $f8, $f20, $f2
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f8.fl = MUL_S(ctx->f20.fl, ctx->f2.fl);
    // 0x8007FB5C: lwc1        $f4, 0x8($v0)
    ctx->f4.u32l = MEM_W(ctx->r2, 0X8);
    // 0x8007FB60: lwc1        $f22, 0x10($v0)
    ctx->f22.u32l = MEM_W(ctx->r2, 0X10);
    // 0x8007FB64: lwc1        $f24, 0x14($v0)
    ctx->f24.u32l = MEM_W(ctx->r2, 0X14);
    // 0x8007FB68: mul.s       $f10, $f12, $f22
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f10.fl = MUL_S(ctx->f12.fl, ctx->f22.fl);
    // 0x8007FB6C: sub.s       $f14, $f4, $f6
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f14.fl = ctx->f4.fl - ctx->f6.fl;
    // 0x8007FB70: mul.s       $f6, $f14, $f24
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 24);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f24.fl); 
    ctx->f6.fl = MUL_S(ctx->f14.fl, ctx->f24.fl);
    // 0x8007FB74: add.s       $f4, $f8, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f4.fl = ctx->f8.fl + ctx->f10.fl;
    // 0x8007FB78: add.s       $f26, $f4, $f6
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f26.fl = ctx->f4.fl + ctx->f6.fl;
    // 0x8007FB7C: c.lt.s      $f26, $f18
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 18);
    c1cs = ctx->f26.fl < ctx->f18.fl;
    // 0x8007FB80: nop

    // 0x8007FB84: bc1tl       L_8007FD40
    if (c1cs) {
        // 0x8007FB88: addiu       $v0, $v0, -0x40
        ctx->r2 = ADD32(ctx->r2, -0X40);
            goto L_8007FD40;
    }
    goto skip_0;
    // 0x8007FB88: addiu       $v0, $v0, -0x40
    ctx->r2 = ADD32(ctx->r2, -0X40);
    skip_0:
    // 0x8007FB8C: lwc1        $f28, 0x30($v0)
    ctx->f28.u32l = MEM_W(ctx->r2, 0X30);
    // 0x8007FB90: c.le.s      $f28, $f26
    CHECK_FR(ctx, 28);
    CHECK_FR(ctx, 26);
    c1cs = ctx->f28.fl <= ctx->f26.fl;
    // 0x8007FB94: nop

    // 0x8007FB98: bc1tl       L_8007FD40
    if (c1cs) {
        // 0x8007FB9C: addiu       $v0, $v0, -0x40
        ctx->r2 = ADD32(ctx->r2, -0X40);
            goto L_8007FD40;
    }
    goto skip_1;
    // 0x8007FB9C: addiu       $v0, $v0, -0x40
    ctx->r2 = ADD32(ctx->r2, -0X40);
    skip_1:
    // 0x8007FBA0: lwc1        $f16, 0x18($v0)
    ctx->f16.u32l = MEM_W(ctx->r2, 0X18);
    // 0x8007FBA4: lwc1        $f30, 0x1C($v0)
    ctx->f30.u32l = MEM_W(ctx->r2, 0X1C);
    // 0x8007FBA8: lwc1        $f8, 0x20($v0)
    ctx->f8.u32l = MEM_W(ctx->r2, 0X20);
    // 0x8007FBAC: mul.s       $f10, $f16, $f2
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f10.fl = MUL_S(ctx->f16.fl, ctx->f2.fl);
    // 0x8007FBB0: swc1        $f16, 0x54($sp)
    MEM_W(0X54, ctx->r29) = ctx->f16.u32l;
    // 0x8007FBB4: swc1        $f8, 0x4C($sp)
    MEM_W(0X4C, ctx->r29) = ctx->f8.u32l;
    // 0x8007FBB8: mul.s       $f4, $f12, $f30
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 30);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f30.fl); 
    ctx->f4.fl = MUL_S(ctx->f12.fl, ctx->f30.fl);
    // 0x8007FBBC: lwc1        $f8, 0x4C($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X4C);
    // 0x8007FBC0: swc1        $f30, 0x50($sp)
    MEM_W(0X50, ctx->r29) = ctx->f30.u32l;
    // 0x8007FBC4: add.s       $f6, $f10, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = ctx->f10.fl + ctx->f4.fl;
    // 0x8007FBC8: mul.s       $f10, $f14, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = MUL_S(ctx->f14.fl, ctx->f8.fl);
    // 0x8007FBCC: add.s       $f0, $f6, $f10
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f0.fl = ctx->f6.fl + ctx->f10.fl;
    // 0x8007FBD0: c.lt.s      $f0, $f18
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 18);
    c1cs = ctx->f0.fl < ctx->f18.fl;
    // 0x8007FBD4: nop

    // 0x8007FBD8: bc1tl       L_8007FD40
    if (c1cs) {
        // 0x8007FBDC: addiu       $v0, $v0, -0x40
        ctx->r2 = ADD32(ctx->r2, -0X40);
            goto L_8007FD40;
    }
    goto skip_2;
    // 0x8007FBDC: addiu       $v0, $v0, -0x40
    ctx->r2 = ADD32(ctx->r2, -0X40);
    skip_2:
    // 0x8007FBE0: lwc1        $f30, 0x34($v0)
    ctx->f30.u32l = MEM_W(ctx->r2, 0X34);
    // 0x8007FBE4: c.le.s      $f30, $f0
    CHECK_FR(ctx, 30);
    CHECK_FR(ctx, 0);
    c1cs = ctx->f30.fl <= ctx->f0.fl;
    // 0x8007FBE8: nop

    // 0x8007FBEC: bc1tl       L_8007FD40
    if (c1cs) {
        // 0x8007FBF0: addiu       $v0, $v0, -0x40
        ctx->r2 = ADD32(ctx->r2, -0X40);
            goto L_8007FD40;
    }
    goto skip_3;
    // 0x8007FBF0: addiu       $v0, $v0, -0x40
    ctx->r2 = ADD32(ctx->r2, -0X40);
    skip_3:
    // 0x8007FBF4: lwc1        $f4, 0x24($v0)
    ctx->f4.u32l = MEM_W(ctx->r2, 0X24);
    // 0x8007FBF8: swc1        $f4, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->f4.u32l;
    // 0x8007FBFC: lwc1        $f8, 0x28($v0)
    ctx->f8.u32l = MEM_W(ctx->r2, 0X28);
    // 0x8007FC00: lwc1        $f10, 0x44($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0X44);
    // 0x8007FC04: swc1        $f8, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->f8.u32l;
    // 0x8007FC08: lwc1        $f6, 0x2C($v0)
    ctx->f6.u32l = MEM_W(ctx->r2, 0X2C);
    // 0x8007FC0C: mul.s       $f4, $f10, $f2
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f4.fl = MUL_S(ctx->f10.fl, ctx->f2.fl);
    // 0x8007FC10: lwc1        $f8, 0x40($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X40);
    // 0x8007FC14: swc1        $f6, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->f6.u32l;
    // 0x8007FC18: mul.s       $f6, $f12, $f8
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f6.fl = MUL_S(ctx->f12.fl, ctx->f8.fl);
    // 0x8007FC1C: lwc1        $f8, 0x3C($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X3C);
    // 0x8007FC20: add.s       $f10, $f4, $f6
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f10.fl = ctx->f4.fl + ctx->f6.fl;
    // 0x8007FC24: mul.s       $f4, $f14, $f8
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f4.fl = MUL_S(ctx->f14.fl, ctx->f8.fl);
    // 0x8007FC28: add.s       $f16, $f10, $f4
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f16.fl = ctx->f10.fl + ctx->f4.fl;
    // 0x8007FC2C: c.lt.s      $f16, $f18
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 18);
    c1cs = ctx->f16.fl < ctx->f18.fl;
    // 0x8007FC30: nop

    // 0x8007FC34: bc1tl       L_8007FD40
    if (c1cs) {
        // 0x8007FC38: addiu       $v0, $v0, -0x40
        ctx->r2 = ADD32(ctx->r2, -0X40);
            goto L_8007FD40;
    }
    goto skip_4;
    // 0x8007FC38: addiu       $v0, $v0, -0x40
    ctx->r2 = ADD32(ctx->r2, -0X40);
    skip_4:
    // 0x8007FC3C: lwc1        $f2, 0x38($v0)
    ctx->f2.u32l = MEM_W(ctx->r2, 0X38);
    // 0x8007FC40: c.le.s      $f2, $f16
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 16);
    c1cs = ctx->f2.fl <= ctx->f16.fl;
    // 0x8007FC44: swc1        $f2, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->f2.u32l;
    // 0x8007FC48: bc1tl       L_8007FD40
    if (c1cs) {
        // 0x8007FC4C: addiu       $v0, $v0, -0x40
        ctx->r2 = ADD32(ctx->r2, -0X40);
            goto L_8007FD40;
    }
    goto skip_5;
    // 0x8007FC4C: addiu       $v0, $v0, -0x40
    ctx->r2 = ADD32(ctx->r2, -0X40);
    skip_5:
    // 0x8007FC50: sub.s       $f18, $f28, $f26
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 28);
    CHECK_FR(ctx, 26);
    NAN_CHECK(ctx->f28.fl); NAN_CHECK(ctx->f26.fl); 
    ctx->f18.fl = ctx->f28.fl - ctx->f26.fl;
    // 0x8007FC54: lwc1        $f6, 0x38($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X38);
    // 0x8007FC58: c.lt.s      $f18, $f26
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 26);
    c1cs = ctx->f18.fl < ctx->f26.fl;
    // 0x8007FC5C: nop

    // 0x8007FC60: bc1fl       L_8007FC80
    if (!c1cs) {
        // 0x8007FC64: mov.s       $f2, $f20
        CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 20);
    ctx->f2.fl = ctx->f20.fl;
            goto L_8007FC80;
    }
    goto skip_6;
    // 0x8007FC64: mov.s       $f2, $f20
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 20);
    ctx->f2.fl = ctx->f20.fl;
    skip_6:
    // 0x8007FC68: mov.s       $f26, $f18
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 18);
    ctx->f26.fl = ctx->f18.fl;
    // 0x8007FC6C: neg.s       $f2, $f20
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f20.fl); 
    ctx->f2.fl = -ctx->f20.fl;
    // 0x8007FC70: neg.s       $f12, $f22
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f22.fl); 
    ctx->f12.fl = -ctx->f22.fl;
    // 0x8007FC74: b           L_8007FC88
    // 0x8007FC78: neg.s       $f14, $f24
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 24);
    NAN_CHECK(ctx->f24.fl); 
    ctx->f14.fl = -ctx->f24.fl;
        goto L_8007FC88;
    // 0x8007FC78: neg.s       $f14, $f24
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 24);
    NAN_CHECK(ctx->f24.fl); 
    ctx->f14.fl = -ctx->f24.fl;
    // 0x8007FC7C: mov.s       $f2, $f20
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 20);
    ctx->f2.fl = ctx->f20.fl;
L_8007FC80:
    // 0x8007FC80: mov.s       $f12, $f22
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 22);
    ctx->f12.fl = ctx->f22.fl;
    // 0x8007FC84: mov.s       $f14, $f24
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 24);
    ctx->f14.fl = ctx->f24.fl;
L_8007FC88:
    // 0x8007FC88: c.lt.s      $f0, $f26
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 26);
    c1cs = ctx->f0.fl < ctx->f26.fl;
    // 0x8007FC8C: sub.s       $f18, $f30, $f0
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 30);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f30.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f18.fl = ctx->f30.fl - ctx->f0.fl;
    // 0x8007FC90: bc1fl       L_8007FCAC
    if (!c1cs) {
        // 0x8007FC94: c.lt.s      $f18, $f26
        CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 26);
    c1cs = ctx->f18.fl < ctx->f26.fl;
            goto L_8007FCAC;
    }
    goto skip_7;
    // 0x8007FC94: c.lt.s      $f18, $f26
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 26);
    c1cs = ctx->f18.fl < ctx->f26.fl;
    skip_7:
    // 0x8007FC98: mov.s       $f26, $f0
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 0);
    ctx->f26.fl = ctx->f0.fl;
    // 0x8007FC9C: lwc1        $f2, 0x54($sp)
    ctx->f2.u32l = MEM_W(ctx->r29, 0X54);
    // 0x8007FCA0: lwc1        $f12, 0x50($sp)
    ctx->f12.u32l = MEM_W(ctx->r29, 0X50);
    // 0x8007FCA4: lwc1        $f14, 0x4C($sp)
    ctx->f14.u32l = MEM_W(ctx->r29, 0X4C);
    // 0x8007FCA8: c.lt.s      $f18, $f26
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 26);
    c1cs = ctx->f18.fl < ctx->f26.fl;
L_8007FCAC:
    // 0x8007FCAC: sub.s       $f0, $f6, $f16
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f0.fl = ctx->f6.fl - ctx->f16.fl;
    // 0x8007FCB0: bc1fl       L_8007FCD8
    if (!c1cs) {
        // 0x8007FCB4: c.lt.s      $f16, $f26
        CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 26);
    c1cs = ctx->f16.fl < ctx->f26.fl;
            goto L_8007FCD8;
    }
    goto skip_8;
    // 0x8007FCB4: c.lt.s      $f16, $f26
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 26);
    c1cs = ctx->f16.fl < ctx->f26.fl;
    skip_8:
    // 0x8007FCB8: lwc1        $f2, 0x54($sp)
    ctx->f2.u32l = MEM_W(ctx->r29, 0X54);
    // 0x8007FCBC: lwc1        $f12, 0x50($sp)
    ctx->f12.u32l = MEM_W(ctx->r29, 0X50);
    // 0x8007FCC0: lwc1        $f14, 0x4C($sp)
    ctx->f14.u32l = MEM_W(ctx->r29, 0X4C);
    // 0x8007FCC4: mov.s       $f26, $f18
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 18);
    ctx->f26.fl = ctx->f18.fl;
    // 0x8007FCC8: neg.s       $f2, $f2
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f2.fl); 
    ctx->f2.fl = -ctx->f2.fl;
    // 0x8007FCCC: neg.s       $f12, $f12
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f12.fl); 
    ctx->f12.fl = -ctx->f12.fl;
    // 0x8007FCD0: neg.s       $f14, $f14
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f14.fl); 
    ctx->f14.fl = -ctx->f14.fl;
    // 0x8007FCD4: c.lt.s      $f16, $f26
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 26);
    c1cs = ctx->f16.fl < ctx->f26.fl;
L_8007FCD8:
    // 0x8007FCD8: nop

    // 0x8007FCDC: bc1fl       L_8007FCF8
    if (!c1cs) {
        // 0x8007FCE0: c.lt.s      $f0, $f26
        CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 26);
    c1cs = ctx->f0.fl < ctx->f26.fl;
            goto L_8007FCF8;
    }
    goto skip_9;
    // 0x8007FCE0: c.lt.s      $f0, $f26
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 26);
    c1cs = ctx->f0.fl < ctx->f26.fl;
    skip_9:
    // 0x8007FCE4: mov.s       $f26, $f16
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 16);
    ctx->f26.fl = ctx->f16.fl;
    // 0x8007FCE8: lwc1        $f2, 0x44($sp)
    ctx->f2.u32l = MEM_W(ctx->r29, 0X44);
    // 0x8007FCEC: lwc1        $f12, 0x40($sp)
    ctx->f12.u32l = MEM_W(ctx->r29, 0X40);
    // 0x8007FCF0: lwc1        $f14, 0x3C($sp)
    ctx->f14.u32l = MEM_W(ctx->r29, 0X3C);
    // 0x8007FCF4: c.lt.s      $f0, $f26
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 26);
    c1cs = ctx->f0.fl < ctx->f26.fl;
L_8007FCF8:
    // 0x8007FCF8: nop

    // 0x8007FCFC: bc1fl       L_8007FD24
    if (!c1cs) {
        // 0x8007FD00: swc1        $f2, 0x0($a3)
        MEM_W(0X0, ctx->r7) = ctx->f2.u32l;
            goto L_8007FD24;
    }
    goto skip_10;
    // 0x8007FD00: swc1        $f2, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->f2.u32l;
    skip_10:
    // 0x8007FD04: lwc1        $f2, 0x44($sp)
    ctx->f2.u32l = MEM_W(ctx->r29, 0X44);
    // 0x8007FD08: lwc1        $f12, 0x40($sp)
    ctx->f12.u32l = MEM_W(ctx->r29, 0X40);
    // 0x8007FD0C: lwc1        $f14, 0x3C($sp)
    ctx->f14.u32l = MEM_W(ctx->r29, 0X3C);
    // 0x8007FD10: mov.s       $f26, $f0
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 0);
    ctx->f26.fl = ctx->f0.fl;
    // 0x8007FD14: neg.s       $f2, $f2
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f2.fl); 
    ctx->f2.fl = -ctx->f2.fl;
    // 0x8007FD18: neg.s       $f12, $f12
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f12.fl); 
    ctx->f12.fl = -ctx->f12.fl;
    // 0x8007FD1C: neg.s       $f14, $f14
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f14.fl); 
    ctx->f14.fl = -ctx->f14.fl;
    // 0x8007FD20: swc1        $f2, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->f2.u32l;
L_8007FD24:
    // 0x8007FD24: lw          $t8, 0x98($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X98);
    // 0x8007FD28: mov.s       $f0, $f26
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 26);
    ctx->f0.fl = ctx->f26.fl;
    // 0x8007FD2C: swc1        $f12, 0x0($t8)
    MEM_W(0X0, ctx->r24) = ctx->f12.u32l;
    // 0x8007FD30: lw          $t9, 0x9C($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X9C);
    // 0x8007FD34: b           L_8007FD54
    // 0x8007FD38: swc1        $f14, 0x0($t9)
    MEM_W(0X0, ctx->r25) = ctx->f14.u32l;
        goto L_8007FD54;
    // 0x8007FD38: swc1        $f14, 0x0($t9)
    MEM_W(0X0, ctx->r25) = ctx->f14.u32l;
    // 0x8007FD3C: addiu       $v0, $v0, -0x40
    ctx->r2 = ADD32(ctx->r2, -0X40);
L_8007FD40:
    // 0x8007FD40: sltu        $at, $v0, $v1
    ctx->r1 = ctx->r2 < ctx->r3 ? 1 : 0;
    // 0x8007FD44: beql        $at, $zero, L_8007FB3C
    if (ctx->r1 == 0) {
        // 0x8007FD48: lwc1        $f4, 0x0($v0)
        ctx->f4.u32l = MEM_W(ctx->r2, 0X0);
            goto L_8007FB3C;
    }
    goto skip_11;
    // 0x8007FD48: lwc1        $f4, 0x0($v0)
    ctx->f4.u32l = MEM_W(ctx->r2, 0X0);
    skip_11:
L_8007FD4C:
    // 0x8007FD4C: mtc1        $zero, $f0
    ctx->f0.u32l = 0;
    // 0x8007FD50: nop

L_8007FD54:
    // 0x8007FD54: ldc1        $f20, 0x8($sp)
    CHECK_FR(ctx, 20);
    ctx->f20.u64 = LD(ctx->r29, 0X8);
    // 0x8007FD58: ldc1        $f22, 0x10($sp)
    CHECK_FR(ctx, 22);
    ctx->f22.u64 = LD(ctx->r29, 0X10);
    // 0x8007FD5C: ldc1        $f24, 0x18($sp)
    CHECK_FR(ctx, 24);
    ctx->f24.u64 = LD(ctx->r29, 0X18);
    // 0x8007FD60: ldc1        $f26, 0x20($sp)
    CHECK_FR(ctx, 26);
    ctx->f26.u64 = LD(ctx->r29, 0X20);
    // 0x8007FD64: ldc1        $f28, 0x28($sp)
    CHECK_FR(ctx, 28);
    ctx->f28.u64 = LD(ctx->r29, 0X28);
    // 0x8007FD68: ldc1        $f30, 0x30($sp)
    CHECK_FR(ctx, 30);
    ctx->f30.u64 = LD(ctx->r29, 0X30);
    // 0x8007FD6C: jr          $ra
    // 0x8007FD70: addiu       $sp, $sp, 0x88
    ctx->r29 = ADD32(ctx->r29, 0X88);
    return;
    // 0x8007FD70: addiu       $sp, $sp, 0x88
    ctx->r29 = ADD32(ctx->r29, 0X88);
    // 0x8007FD74: nop

    // 0x8007FD78: nop

    // 0x8007FD7C: nop

;}
RECOMP_FUNC void func_8007FD80(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8007FD80: addiu       $sp, $sp, -0x28
    ctx->r29 = ADD32(ctx->r29, -0X28);
    // 0x8007FD84: sw          $s3, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r19;
    // 0x8007FD88: sw          $s2, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r18;
    // 0x8007FD8C: sw          $s1, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r17;
    // 0x8007FD90: sw          $s0, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r16;
    // 0x8007FD94: lui         $s2, 0x801C
    ctx->r18 = S32(0X801C << 16);
    // 0x8007FD98: lui         $s3, 0x800E
    ctx->r19 = S32(0X800E << 16);
    // 0x8007FD9C: sw          $ra, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r31;
    // 0x8007FDA0: addiu       $s3, $s3, -0x69C0
    ctx->r19 = ADD32(ctx->r19, -0X69C0);
    // 0x8007FDA4: addiu       $s2, $s2, 0x3B90
    ctx->r18 = ADD32(ctx->r18, 0X3B90);
    // 0x8007FDA8: or          $s0, $zero, $zero
    ctx->r16 = 0 | 0;
    // 0x8007FDAC: addiu       $s1, $zero, 0x10
    ctx->r17 = ADD32(0, 0X10);
L_8007FDB0:
    // 0x8007FDB0: sll         $t7, $s0, 2
    ctx->r15 = S32(ctx->r16 << 2);
    // 0x8007FDB4: addu        $v0, $s3, $t7
    ctx->r2 = ADD32(ctx->r19, ctx->r15);
    // 0x8007FDB8: lh          $t8, 0x0($v0)
    ctx->r24 = MEM_H(ctx->r2, 0X0);
    // 0x8007FDBC: lh          $t9, 0x2($v0)
    ctx->r25 = MEM_H(ctx->r2, 0X2);
    // 0x8007FDC0: mtc1        $t8, $f4
    ctx->f4.u32l = ctx->r24;
    // 0x8007FDC4: mtc1        $t9, $f8
    ctx->f8.u32l = ctx->r25;
    // 0x8007FDC8: cvt.s.w     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
    // 0x8007FDCC: cvt.s.w     $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.fl = CVT_S_W(ctx->f8.u32l);
    // 0x8007FDD0: swc1        $f6, 0x0($s2)
    MEM_W(0X0, ctx->r18) = ctx->f6.u32l;
    // 0x8007FDD4: jal         0x80047E50
    // 0x8007FDD8: swc1        $f10, 0x4($s2)
    MEM_W(0X4, ctx->r18) = ctx->f10.u32l;
    SysUtils_Rand(rdram, ctx);
        goto after_0;
    // 0x8007FDD8: swc1        $f10, 0x4($s2)
    MEM_W(0X4, ctx->r18) = ctx->f10.u32l;
    after_0:
    // 0x8007FDDC: addiu       $s0, $s0, 0x1
    ctx->r16 = ADD32(ctx->r16, 0X1);
    // 0x8007FDE0: andi        $t3, $v0, 0xFFF
    ctx->r11 = ctx->r2 & 0XFFF;
    // 0x8007FDE4: addiu       $s2, $s2, 0xC
    ctx->r18 = ADD32(ctx->r18, 0XC);
    // 0x8007FDE8: bne         $s0, $s1, L_8007FDB0
    if (ctx->r16 != ctx->r17) {
        // 0x8007FDEC: sw          $t3, -0x4($s2)
        MEM_W(-0X4, ctx->r18) = ctx->r11;
            goto L_8007FDB0;
    }
    // 0x8007FDEC: sw          $t3, -0x4($s2)
    MEM_W(-0X4, ctx->r18) = ctx->r11;
    // 0x8007FDF0: lui         $t1, 0x8015
    ctx->r9 = S32(0X8015 << 16);
    // 0x8007FDF4: lui         $t2, 0x8013
    ctx->r10 = S32(0X8013 << 16);
    // 0x8007FDF8: addiu       $t2, $t2, 0x7ED0
    ctx->r10 = ADD32(ctx->r10, 0X7ED0);
    // 0x8007FDFC: addiu       $t1, $t1, 0xEB8
    ctx->r9 = ADD32(ctx->r9, 0XEB8);
    // 0x8007FE00: addiu       $t0, $zero, 0x7C0
    ctx->r8 = ADD32(0, 0X7C0);
    // 0x8007FE04: addiu       $a3, $zero, 0x3E0
    ctx->r7 = ADD32(0, 0X3E0);
    // 0x8007FE08: addiu       $a2, $zero, 0xFC0
    ctx->r6 = ADD32(0, 0XFC0);
    // 0x8007FE0C: addiu       $a1, $zero, 0x7E0
    ctx->r5 = ADD32(0, 0X7E0);
    // 0x8007FE10: or          $v0, $t1, $zero
    ctx->r2 = ctx->r9 | 0;
L_8007FE14:
    // 0x8007FE14: or          $s0, $zero, $zero
    ctx->r16 = 0 | 0;
L_8007FE18:
    // 0x8007FE18: sh          $a2, 0x78($v0)
    MEM_H(0X78, ctx->r2) = ctx->r6;
    // 0x8007FE1C: lh          $a0, 0x78($v0)
    ctx->r4 = MEM_H(ctx->r2, 0X78);
    // 0x8007FE20: sh          $t0, 0x7A($v0)
    MEM_H(0X7A, ctx->r2) = ctx->r8;
    // 0x8007FE24: sh          $zero, 0x2A($v0)
    MEM_H(0X2A, ctx->r2) = 0;
    // 0x8007FE28: sh          $a0, 0x48($v0)
    MEM_H(0X48, ctx->r2) = ctx->r4;
    // 0x8007FE2C: sh          $a0, 0x28($v0)
    MEM_H(0X28, ctx->r2) = ctx->r4;
    // 0x8007FE30: lh          $a0, 0x7A($v0)
    ctx->r4 = MEM_H(ctx->r2, 0X7A);
    // 0x8007FE34: lh          $v1, 0x2A($v0)
    ctx->r3 = MEM_H(ctx->r2, 0X2A);
    // 0x8007FE38: sh          $a2, 0xF8($v0)
    MEM_H(0XF8, ctx->r2) = ctx->r6;
    // 0x8007FE3C: sh          $a0, 0x6A($v0)
    MEM_H(0X6A, ctx->r2) = ctx->r4;
    // 0x8007FE40: sh          $a0, 0x5A($v0)
    MEM_H(0X5A, ctx->r2) = ctx->r4;
    // 0x8007FE44: lh          $a0, 0xF8($v0)
    ctx->r4 = MEM_H(ctx->r2, 0XF8);
    // 0x8007FE48: sh          $t0, 0xFA($v0)
    MEM_H(0XFA, ctx->r2) = ctx->r8;
    // 0x8007FE4C: sh          $zero, 0xAA($v0)
    MEM_H(0XAA, ctx->r2) = 0;
    // 0x8007FE50: sh          $a0, 0xC8($v0)
    MEM_H(0XC8, ctx->r2) = ctx->r4;
    // 0x8007FE54: sh          $a0, 0xA8($v0)
    MEM_H(0XA8, ctx->r2) = ctx->r4;
    // 0x8007FE58: lh          $a0, 0xFA($v0)
    ctx->r4 = MEM_H(ctx->r2, 0XFA);
    // 0x8007FE5C: sh          $v1, 0x1A($v0)
    MEM_H(0X1A, ctx->r2) = ctx->r3;
    // 0x8007FE60: sh          $v1, 0xA($v0)
    MEM_H(0XA, ctx->r2) = ctx->r3;
    // 0x8007FE64: sh          $v1, 0x58($v0)
    MEM_H(0X58, ctx->r2) = ctx->r3;
    // 0x8007FE68: sh          $v1, 0x38($v0)
    MEM_H(0X38, ctx->r2) = ctx->r3;
    // 0x8007FE6C: sh          $v1, 0x8($v0)
    MEM_H(0X8, ctx->r2) = ctx->r3;
    // 0x8007FE70: lh          $v1, 0xAA($v0)
    ctx->r3 = MEM_H(ctx->r2, 0XAA);
    // 0x8007FE74: sh          $a2, 0x178($v0)
    MEM_H(0X178, ctx->r2) = ctx->r6;
    // 0x8007FE78: sh          $a0, 0xEA($v0)
    MEM_H(0XEA, ctx->r2) = ctx->r4;
    // 0x8007FE7C: sh          $a0, 0xDA($v0)
    MEM_H(0XDA, ctx->r2) = ctx->r4;
    // 0x8007FE80: lh          $a0, 0x178($v0)
    ctx->r4 = MEM_H(ctx->r2, 0X178);
    // 0x8007FE84: sh          $zero, 0x12A($v0)
    MEM_H(0X12A, ctx->r2) = 0;
    // 0x8007FE88: sh          $v1, 0x9A($v0)
    MEM_H(0X9A, ctx->r2) = ctx->r3;
    // 0x8007FE8C: sh          $v1, 0x8A($v0)
    MEM_H(0X8A, ctx->r2) = ctx->r3;
    // 0x8007FE90: sh          $v1, 0xD8($v0)
    MEM_H(0XD8, ctx->r2) = ctx->r3;
    // 0x8007FE94: sh          $v1, 0xB8($v0)
    MEM_H(0XB8, ctx->r2) = ctx->r3;
    // 0x8007FE98: sh          $v1, 0x88($v0)
    MEM_H(0X88, ctx->r2) = ctx->r3;
    // 0x8007FE9C: lh          $v1, 0x12A($v0)
    ctx->r3 = MEM_H(ctx->r2, 0X12A);
    // 0x8007FEA0: sh          $t0, 0x17A($v0)
    MEM_H(0X17A, ctx->r2) = ctx->r8;
    // 0x8007FEA4: sh          $a0, 0x148($v0)
    MEM_H(0X148, ctx->r2) = ctx->r4;
    // 0x8007FEA8: sh          $a0, 0x128($v0)
    MEM_H(0X128, ctx->r2) = ctx->r4;
    // 0x8007FEAC: lh          $a0, 0x17A($v0)
    ctx->r4 = MEM_H(ctx->r2, 0X17A);
    // 0x8007FEB0: sh          $a2, 0x1F8($v0)
    MEM_H(0X1F8, ctx->r2) = ctx->r6;
    // 0x8007FEB4: sh          $zero, 0x1AA($v0)
    MEM_H(0X1AA, ctx->r2) = 0;
    // 0x8007FEB8: sh          $a0, 0x16A($v0)
    MEM_H(0X16A, ctx->r2) = ctx->r4;
    // 0x8007FEBC: sh          $a0, 0x15A($v0)
    MEM_H(0X15A, ctx->r2) = ctx->r4;
    // 0x8007FEC0: lh          $a0, 0x1F8($v0)
    ctx->r4 = MEM_H(ctx->r2, 0X1F8);
    // 0x8007FEC4: sh          $a1, 0x68($v0)
    MEM_H(0X68, ctx->r2) = ctx->r5;
    // 0x8007FEC8: sh          $v1, 0x11A($v0)
    MEM_H(0X11A, ctx->r2) = ctx->r3;
    // 0x8007FECC: sh          $v1, 0x10A($v0)
    MEM_H(0X10A, ctx->r2) = ctx->r3;
    // 0x8007FED0: sh          $v1, 0x158($v0)
    MEM_H(0X158, ctx->r2) = ctx->r3;
    // 0x8007FED4: sh          $v1, 0x138($v0)
    MEM_H(0X138, ctx->r2) = ctx->r3;
    // 0x8007FED8: sh          $v1, 0x108($v0)
    MEM_H(0X108, ctx->r2) = ctx->r3;
    // 0x8007FEDC: lh          $v1, 0x1AA($v0)
    ctx->r3 = MEM_H(ctx->r2, 0X1AA);
    // 0x8007FEE0: lh          $t4, 0x68($v0)
    ctx->r12 = MEM_H(ctx->r2, 0X68);
    // 0x8007FEE4: sh          $t0, 0x1FA($v0)
    MEM_H(0X1FA, ctx->r2) = ctx->r8;
    // 0x8007FEE8: sh          $a0, 0x1C8($v0)
    MEM_H(0X1C8, ctx->r2) = ctx->r4;
    // 0x8007FEEC: sh          $a0, 0x1A8($v0)
    MEM_H(0X1A8, ctx->r2) = ctx->r4;
    // 0x8007FEF0: lh          $a0, 0x1FA($v0)
    ctx->r4 = MEM_H(ctx->r2, 0X1FA);
    // 0x8007FEF4: sh          $a1, 0xE8($v0)
    MEM_H(0XE8, ctx->r2) = ctx->r5;
    // 0x8007FEF8: sh          $a3, 0xCA($v0)
    MEM_H(0XCA, ctx->r2) = ctx->r7;
    // 0x8007FEFC: sh          $a1, 0x168($v0)
    MEM_H(0X168, ctx->r2) = ctx->r5;
    // 0x8007FF00: sh          $a3, 0x14A($v0)
    MEM_H(0X14A, ctx->r2) = ctx->r7;
    // 0x8007FF04: sh          $a1, 0x1E8($v0)
    MEM_H(0X1E8, ctx->r2) = ctx->r5;
    // 0x8007FF08: sh          $a3, 0x1CA($v0)
    MEM_H(0X1CA, ctx->r2) = ctx->r7;
    // 0x8007FF0C: sh          $a3, 0x4A($v0)
    MEM_H(0X4A, ctx->r2) = ctx->r7;
    // 0x8007FF10: sh          $t4, 0x18($v0)
    MEM_H(0X18, ctx->r2) = ctx->r12;
    // 0x8007FF14: lh          $t4, 0x1CA($v0)
    ctx->r12 = MEM_H(ctx->r2, 0X1CA);
    // 0x8007FF18: lh          $t3, 0x1E8($v0)
    ctx->r11 = MEM_H(ctx->r2, 0X1E8);
    // 0x8007FF1C: lh          $t9, 0x14A($v0)
    ctx->r25 = MEM_H(ctx->r2, 0X14A);
    // 0x8007FF20: lh          $t8, 0x168($v0)
    ctx->r24 = MEM_H(ctx->r2, 0X168);
    // 0x8007FF24: lh          $t7, 0xCA($v0)
    ctx->r15 = MEM_H(ctx->r2, 0XCA);
    // 0x8007FF28: lh          $t6, 0xE8($v0)
    ctx->r14 = MEM_H(ctx->r2, 0XE8);
    // 0x8007FF2C: lh          $t5, 0x4A($v0)
    ctx->r13 = MEM_H(ctx->r2, 0X4A);
    // 0x8007FF30: addiu       $s0, $s0, 0x4
    ctx->r16 = ADD32(ctx->r16, 0X4);
    // 0x8007FF34: addiu       $v0, $v0, 0x200
    ctx->r2 = ADD32(ctx->r2, 0X200);
    // 0x8007FF38: sh          $v1, -0x66($v0)
    MEM_H(-0X66, ctx->r2) = ctx->r3;
    // 0x8007FF3C: sh          $v1, -0x76($v0)
    MEM_H(-0X76, ctx->r2) = ctx->r3;
    // 0x8007FF40: sh          $v1, -0x28($v0)
    MEM_H(-0X28, ctx->r2) = ctx->r3;
    // 0x8007FF44: sh          $v1, -0x48($v0)
    MEM_H(-0X48, ctx->r2) = ctx->r3;
    // 0x8007FF48: sh          $v1, -0x78($v0)
    MEM_H(-0X78, ctx->r2) = ctx->r3;
    // 0x8007FF4C: sh          $a0, -0x16($v0)
    MEM_H(-0X16, ctx->r2) = ctx->r4;
    // 0x8007FF50: sh          $a0, -0x26($v0)
    MEM_H(-0X26, ctx->r2) = ctx->r4;
    // 0x8007FF54: sh          $t4, -0x46($v0)
    MEM_H(-0X46, ctx->r2) = ctx->r12;
    // 0x8007FF58: sh          $t3, -0x68($v0)
    MEM_H(-0X68, ctx->r2) = ctx->r11;
    // 0x8007FF5C: sh          $t9, -0xC6($v0)
    MEM_H(-0XC6, ctx->r2) = ctx->r25;
    // 0x8007FF60: sh          $t8, -0xE8($v0)
    MEM_H(-0XE8, ctx->r2) = ctx->r24;
    // 0x8007FF64: sh          $t7, -0x146($v0)
    MEM_H(-0X146, ctx->r2) = ctx->r15;
    // 0x8007FF68: sh          $t6, -0x168($v0)
    MEM_H(-0X168, ctx->r2) = ctx->r14;
    // 0x8007FF6C: bne         $s0, $s1, L_8007FE18
    if (ctx->r16 != ctx->r17) {
        // 0x8007FF70: sh          $t5, -0x1C6($v0)
        MEM_H(-0X1C6, ctx->r2) = ctx->r13;
            goto L_8007FE18;
    }
    // 0x8007FF70: sh          $t5, -0x1C6($v0)
    MEM_H(-0X1C6, ctx->r2) = ctx->r13;
    // 0x8007FF74: lui         $at, 0xFFFE
    ctx->r1 = S32(0XFFFE << 16);
    // 0x8007FF78: ori         $at, $at, 0x7018
    ctx->r1 = ctx->r1 | 0X7018;
    // 0x8007FF7C: addu        $t1, $t1, $at
    ctx->r9 = ADD32(ctx->r9, ctx->r1);
    // 0x8007FF80: sltu        $at, $t1, $t2
    ctx->r1 = ctx->r9 < ctx->r10 ? 1 : 0;
    // 0x8007FF84: beql        $at, $zero, L_8007FE14
    if (ctx->r1 == 0) {
        // 0x8007FF88: or          $v0, $t1, $zero
        ctx->r2 = ctx->r9 | 0;
            goto L_8007FE14;
    }
    goto skip_0;
    // 0x8007FF88: or          $v0, $t1, $zero
    ctx->r2 = ctx->r9 | 0;
    skip_0:
    // 0x8007FF8C: lw          $ra, 0x24($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X24);
    // 0x8007FF90: lw          $s0, 0x14($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X14);
    // 0x8007FF94: lw          $s1, 0x18($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X18);
    // 0x8007FF98: lw          $s2, 0x1C($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X1C);
    // 0x8007FF9C: lw          $s3, 0x20($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X20);
    // 0x8007FFA0: jr          $ra
    // 0x8007FFA4: addiu       $sp, $sp, 0x28
    ctx->r29 = ADD32(ctx->r29, 0X28);
    return;
    // 0x8007FFA4: addiu       $sp, $sp, 0x28
    ctx->r29 = ADD32(ctx->r29, 0X28);
;}
RECOMP_FUNC void func_8007FFA8(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8007FFA8: addiu       $sp, $sp, -0x98
    ctx->r29 = ADD32(ctx->r29, -0X98);
    // 0x8007FFAC: lui         $t6, 0x800E
    ctx->r14 = S32(0X800E << 16);
    // 0x8007FFB0: lw          $t6, -0x7E90($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X7E90);
    // 0x8007FFB4: sw          $s1, 0x4C($sp)
    MEM_W(0X4C, ctx->r29) = ctx->r17;
    // 0x8007FFB8: addiu       $at, $zero, 0x5
    ctx->r1 = ADD32(0, 0X5);
    // 0x8007FFBC: or          $s1, $a0, $zero
    ctx->r17 = ctx->r4 | 0;
    // 0x8007FFC0: sw          $ra, 0x6C($sp)
    MEM_W(0X6C, ctx->r29) = ctx->r31;
    // 0x8007FFC4: sw          $fp, 0x68($sp)
    MEM_W(0X68, ctx->r29) = ctx->r30;
    // 0x8007FFC8: sw          $s7, 0x64($sp)
    MEM_W(0X64, ctx->r29) = ctx->r23;
    // 0x8007FFCC: sw          $s6, 0x60($sp)
    MEM_W(0X60, ctx->r29) = ctx->r22;
    // 0x8007FFD0: sw          $s5, 0x5C($sp)
    MEM_W(0X5C, ctx->r29) = ctx->r21;
    // 0x8007FFD4: sw          $s4, 0x58($sp)
    MEM_W(0X58, ctx->r29) = ctx->r20;
    // 0x8007FFD8: sw          $s3, 0x54($sp)
    MEM_W(0X54, ctx->r29) = ctx->r19;
    // 0x8007FFDC: sw          $s2, 0x50($sp)
    MEM_W(0X50, ctx->r29) = ctx->r18;
    // 0x8007FFE0: sw          $s0, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r16;
    // 0x8007FFE4: sdc1        $f30, 0x40($sp)
    CHECK_FR(ctx, 30);
    SD(ctx->f30.u64, 0X40, ctx->r29);
    // 0x8007FFE8: sdc1        $f28, 0x38($sp)
    CHECK_FR(ctx, 28);
    SD(ctx->f28.u64, 0X38, ctx->r29);
    // 0x8007FFEC: sdc1        $f26, 0x30($sp)
    CHECK_FR(ctx, 26);
    SD(ctx->f26.u64, 0X30, ctx->r29);
    // 0x8007FFF0: sdc1        $f24, 0x28($sp)
    CHECK_FR(ctx, 24);
    SD(ctx->f24.u64, 0X28, ctx->r29);
    // 0x8007FFF4: sdc1        $f22, 0x20($sp)
    CHECK_FR(ctx, 22);
    SD(ctx->f22.u64, 0X20, ctx->r29);
    // 0x8007FFF8: beq         $t6, $at, L_80080008
    if (ctx->r14 == ctx->r1) {
        // 0x8007FFFC: sdc1        $f20, 0x18($sp)
        CHECK_FR(ctx, 20);
    SD(ctx->f20.u64, 0X18, ctx->r29);
            goto L_80080008;
    }
    // 0x8007FFFC: sdc1        $f20, 0x18($sp)
    CHECK_FR(ctx, 20);
    SD(ctx->f20.u64, 0X18, ctx->r29);
    // 0x80080000: b           L_800803AC
    // 0x80080004: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
        goto L_800803AC;
    // 0x80080004: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
L_80080008:
    // 0x80080008: or          $v0, $s1, $zero
    ctx->r2 = ctx->r17 | 0;
    // 0x8008000C: addiu       $s1, $s1, 0x8
    ctx->r17 = ADD32(ctx->r17, 0X8);
    // 0x80080010: lui         $t8, 0xE01
    ctx->r24 = S32(0XE01 << 16);
    // 0x80080014: addiu       $t8, $t8, 0xF28
    ctx->r24 = ADD32(ctx->r24, 0XF28);
    // 0x80080018: lui         $t7, 0x600
    ctx->r15 = S32(0X600 << 16);
    // 0x8008001C: or          $v1, $s1, $zero
    ctx->r3 = ctx->r17 | 0;
    // 0x80080020: sw          $t7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r15;
    // 0x80080024: sw          $t8, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r24;
    // 0x80080028: lui         $t9, 0x102
    ctx->r25 = S32(0X102 << 16);
    // 0x8008002C: lui         $t0, 0x200
    ctx->r8 = S32(0X200 << 16);
    // 0x80080030: addiu       $t0, $t0, 0xA40
    ctx->r8 = ADD32(ctx->r8, 0XA40);
    // 0x80080034: ori         $t9, $t9, 0x40
    ctx->r25 = ctx->r25 | 0X40;
    // 0x80080038: lui         $s2, 0x801C
    ctx->r18 = S32(0X801C << 16);
    // 0x8008003C: lui         $fp, 0x801C
    ctx->r30 = S32(0X801C << 16);
    // 0x80080040: lui         $s7, 0x8015
    ctx->r23 = S32(0X8015 << 16);
    // 0x80080044: lui         $s4, 0x8019
    ctx->r20 = S32(0X8019 << 16);
    // 0x80080048: sw          $t9, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r25;
    // 0x8008004C: sw          $t0, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r8;
    // 0x80080050: addiu       $s1, $s1, 0x8
    ctx->r17 = ADD32(ctx->r17, 0X8);
    // 0x80080054: or          $s6, $zero, $zero
    ctx->r22 = 0 | 0;
    // 0x80080058: addiu       $s4, $s4, 0x2420
    ctx->r20 = ADD32(ctx->r20, 0X2420);
    // 0x8008005C: addiu       $s7, $s7, 0x4350
    ctx->r23 = ADD32(ctx->r23, 0X4350);
    // 0x80080060: addiu       $fp, $fp, 0x3C50
    ctx->r30 = ADD32(ctx->r30, 0X3C50);
    // 0x80080064: addiu       $s2, $s2, 0x3B90
    ctx->r18 = ADD32(ctx->r18, 0X3B90);
    // 0x80080068: lui         $s3, 0xBF00
    ctx->r19 = S32(0XBF00 << 16);
L_8008006C:
    // 0x8008006C: lwc1        $f16, 0x0($s2)
    ctx->f16.u32l = MEM_W(ctx->r18, 0X0);
    // 0x80080070: lwc1        $f4, 0x8($s4)
    ctx->f4.u32l = MEM_W(ctx->r20, 0X8);
    // 0x80080074: lwc1        $f6, 0x4($s2)
    ctx->f6.u32l = MEM_W(ctx->r18, 0X4);
    // 0x80080078: lwc1        $f8, 0xC($s4)
    ctx->f8.u32l = MEM_W(ctx->r20, 0XC);
    // 0x8008007C: sub.s       $f20, $f16, $f4
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f20.fl = ctx->f16.fl - ctx->f4.fl;
    // 0x80080080: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x80080084: sll         $v1, $s6, 4
    ctx->r3 = S32(ctx->r22 << 4);
    // 0x80080088: sub.s       $f22, $f6, $f8
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f22.fl = ctx->f6.fl - ctx->f8.fl;
    // 0x8008008C: mul.s       $f10, $f20, $f20
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f10.fl = MUL_S(ctx->f20.fl, ctx->f20.fl);
    // 0x80080090: lwc1        $f8, 0x10($s4)
    ctx->f8.u32l = MEM_W(ctx->r20, 0X10);
    // 0x80080094: lui         $t8, 0x8015
    ctx->r24 = S32(0X8015 << 16);
    // 0x80080098: mul.s       $f4, $f22, $f22
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f4.fl = MUL_S(ctx->f22.fl, ctx->f22.fl);
    // 0x8008009C: add.s       $f6, $f10, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = ctx->f10.fl + ctx->f4.fl;
    // 0x800800A0: c.le.s      $f8, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    c1cs = ctx->f8.fl <= ctx->f6.fl;
    // 0x800800A4: nop

    // 0x800800A8: bc1tl       L_8008039C
    if (c1cs) {
        // 0x800800AC: addiu       $s2, $s2, 0xC
        ctx->r18 = ADD32(ctx->r18, 0XC);
            goto L_8008039C;
    }
    goto skip_0;
    // 0x800800AC: addiu       $s2, $s2, 0xC
    ctx->r18 = ADD32(ctx->r18, 0XC);
    skip_0:
    // 0x800800B0: lw          $v0, 0x8($s2)
    ctx->r2 = MEM_W(ctx->r18, 0X8);
    // 0x800800B4: lwc1        $f18, -0x5C00($at)
    ctx->f18.u32l = MEM_W(ctx->r1, -0X5C00);
    // 0x800800B8: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x800800BC: addiu       $t1, $v0, 0x400
    ctx->r9 = ADD32(ctx->r2, 0X400);
    // 0x800800C0: andi        $t2, $t1, 0xFFF
    ctx->r10 = ctx->r9 & 0XFFF;
    // 0x800800C4: sll         $t3, $t2, 2
    ctx->r11 = S32(ctx->r10 << 2);
    // 0x800800C8: addu        $t4, $s7, $t3
    ctx->r12 = ADD32(ctx->r23, ctx->r11);
    // 0x800800CC: lwc1        $f20, 0x0($t4)
    ctx->f20.u32l = MEM_W(ctx->r12, 0X0);
    // 0x800800D0: andi        $t5, $v0, 0xFFF
    ctx->r13 = ctx->r2 & 0XFFF;
    // 0x800800D4: sll         $t6, $t5, 2
    ctx->r14 = S32(ctx->r13 << 2);
    // 0x800800D8: mul.s       $f0, $f18, $f20
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f0.fl = MUL_S(ctx->f18.fl, ctx->f20.fl);
    // 0x800800DC: addu        $t7, $s7, $t6
    ctx->r15 = ADD32(ctx->r23, ctx->r14);
    // 0x800800E0: lwc1        $f22, 0x0($t7)
    ctx->f22.u32l = MEM_W(ctx->r15, 0X0);
    // 0x800800E4: lwc1        $f10, -0x5BFC($at)
    ctx->f10.u32l = MEM_W(ctx->r1, -0X5BFC);
    // 0x800800E8: lw          $t8, 0x18B8($t8)
    ctx->r24 = MEM_W(ctx->r24, 0X18B8);
    // 0x800800EC: mul.s       $f2, $f18, $f22
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f2.fl = MUL_S(ctx->f18.fl, ctx->f22.fl);
    // 0x800800F0: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x800800F4: sub.s       $f24, $f16, $f0
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f24.fl = ctx->f16.fl - ctx->f0.fl;
    // 0x800800F8: lwc1        $f4, -0x5BF8($at)
    ctx->f4.u32l = MEM_W(ctx->r1, -0X5BF8);
    // 0x800800FC: lui         $at, 0x1
    ctx->r1 = S32(0X1 << 16);
    // 0x80080100: ori         $at, $at, 0x85E8
    ctx->r1 = ctx->r1 | 0X85E8;
    // 0x80080104: trunc.w.s   $f6, $f24
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 24);
    ctx->f6.u32l = TRUNC_W_S(ctx->f24.fl);
    // 0x80080108: addu        $s0, $t8, $v1
    ctx->r16 = ADD32(ctx->r24, ctx->r3);
    // 0x8008010C: swc1        $f0, 0x78($sp)
    MEM_W(0X78, ctx->r29) = ctx->f0.u32l;
    // 0x80080110: swc1        $f2, 0x74($sp)
    MEM_W(0X74, ctx->r29) = ctx->f2.u32l;
    // 0x80080114: mfc1        $t0, $f6
    ctx->r8 = (int32_t)ctx->f6.u32l;
    // 0x80080118: addu        $s0, $s0, $at
    ctx->r16 = ADD32(ctx->r16, ctx->r1);
    // 0x8008011C: mul.s       $f28, $f10, $f22
    CHECK_FR(ctx, 28);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f28.fl = MUL_S(ctx->f10.fl, ctx->f22.fl);
    // 0x80080120: sh          $t0, 0x30($s0)
    MEM_H(0X30, ctx->r16) = ctx->r8;
    // 0x80080124: lwc1        $f8, 0x4($s2)
    ctx->f8.u32l = MEM_W(ctx->r18, 0X4);
    // 0x80080128: lui         $t4, 0x300
    ctx->r12 = S32(0X300 << 16);
    // 0x8008012C: addiu       $t4, $t4, 0x0
    ctx->r12 = ADD32(ctx->r12, 0X0);
    // 0x80080130: sub.s       $f26, $f8, $f2
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f26.fl = ctx->f8.fl - ctx->f2.fl;
    // 0x80080134: addu        $t3, $v1, $at
    ctx->r11 = ADD32(ctx->r3, ctx->r1);
    // 0x80080138: mul.s       $f30, $f4, $f20
    CHECK_FR(ctx, 30);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f30.fl = MUL_S(ctx->f4.fl, ctx->f20.fl);
    // 0x8008013C: addu        $s5, $t3, $t4
    ctx->r21 = ADD32(ctx->r11, ctx->r12);
    // 0x80080140: mov.s       $f14, $f26
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 26);
    ctx->f14.fl = ctx->f26.fl;
    // 0x80080144: mov.s       $f12, $f24
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 24);
    ctx->f12.fl = ctx->f24.fl;
    // 0x80080148: trunc.w.s   $f10, $f26
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 26);
    ctx->f10.u32l = TRUNC_W_S(ctx->f26.fl);
    // 0x8008014C: mfc1        $t2, $f10
    ctx->r10 = (int32_t)ctx->f10.u32l;
    // 0x80080150: jal         0x8004D30C
    // 0x80080154: sh          $t2, 0x34($s0)
    MEM_H(0X34, ctx->r16) = ctx->r10;
    func_8004D30C(rdram, ctx);
        goto after_0;
    // 0x80080154: sh          $t2, 0x34($s0)
    MEM_H(0X34, ctx->r16) = ctx->r10;
    after_0:
    // 0x80080158: sub.s       $f12, $f24, $f28
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 28);
    NAN_CHECK(ctx->f24.fl); NAN_CHECK(ctx->f28.fl); 
    ctx->f12.fl = ctx->f24.fl - ctx->f28.fl;
    // 0x8008015C: sub.s       $f14, $f26, $f30
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 30);
    NAN_CHECK(ctx->f26.fl); NAN_CHECK(ctx->f30.fl); 
    ctx->f14.fl = ctx->f26.fl - ctx->f30.fl;
    // 0x80080160: trunc.w.s   $f4, $f0
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    ctx->f4.u32l = TRUNC_W_S(ctx->f0.fl);
    // 0x80080164: trunc.w.s   $f6, $f12
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 12);
    ctx->f6.u32l = TRUNC_W_S(ctx->f12.fl);
    // 0x80080168: mfc1        $t6, $f4
    ctx->r14 = (int32_t)ctx->f4.u32l;
    // 0x8008016C: trunc.w.s   $f8, $f14
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 14);
    ctx->f8.u32l = TRUNC_W_S(ctx->f14.fl);
    // 0x80080170: mfc1        $t8, $f6
    ctx->r24 = (int32_t)ctx->f6.u32l;
    // 0x80080174: sh          $t6, 0x32($s0)
    MEM_H(0X32, ctx->r16) = ctx->r14;
    // 0x80080178: mfc1        $t0, $f8
    ctx->r8 = (int32_t)ctx->f8.u32l;
    // 0x8008017C: sh          $t8, 0x0($s0)
    MEM_H(0X0, ctx->r16) = ctx->r24;
    // 0x80080180: jal         0x8004D30C
    // 0x80080184: sh          $t0, 0x4($s0)
    MEM_H(0X4, ctx->r16) = ctx->r8;
    func_8004D30C(rdram, ctx);
        goto after_1;
    // 0x80080184: sh          $t0, 0x4($s0)
    MEM_H(0X4, ctx->r16) = ctx->r8;
    after_1:
    // 0x80080188: add.s       $f12, $f24, $f28
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 28);
    NAN_CHECK(ctx->f24.fl); NAN_CHECK(ctx->f28.fl); 
    ctx->f12.fl = ctx->f24.fl + ctx->f28.fl;
    // 0x8008018C: add.s       $f14, $f26, $f30
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 30);
    NAN_CHECK(ctx->f26.fl); NAN_CHECK(ctx->f30.fl); 
    ctx->f14.fl = ctx->f26.fl + ctx->f30.fl;
    // 0x80080190: trunc.w.s   $f10, $f0
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 0);
    ctx->f10.u32l = TRUNC_W_S(ctx->f0.fl);
    // 0x80080194: trunc.w.s   $f4, $f12
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 12);
    ctx->f4.u32l = TRUNC_W_S(ctx->f12.fl);
    // 0x80080198: mfc1        $t2, $f10
    ctx->r10 = (int32_t)ctx->f10.u32l;
    // 0x8008019C: trunc.w.s   $f6, $f14
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 14);
    ctx->f6.u32l = TRUNC_W_S(ctx->f14.fl);
    // 0x800801A0: mfc1        $t4, $f4
    ctx->r12 = (int32_t)ctx->f4.u32l;
    // 0x800801A4: sh          $t2, 0x2($s0)
    MEM_H(0X2, ctx->r16) = ctx->r10;
    // 0x800801A8: mfc1        $t6, $f6
    ctx->r14 = (int32_t)ctx->f6.u32l;
    // 0x800801AC: sh          $t4, 0x50($s0)
    MEM_H(0X50, ctx->r16) = ctx->r12;
    // 0x800801B0: jal         0x8004D30C
    // 0x800801B4: sh          $t6, 0x54($s0)
    MEM_H(0X54, ctx->r16) = ctx->r14;
    func_8004D30C(rdram, ctx);
        goto after_2;
    // 0x800801B4: sh          $t6, 0x54($s0)
    MEM_H(0X54, ctx->r16) = ctx->r14;
    after_2:
    // 0x800801B8: trunc.w.s   $f8, $f0
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 0);
    ctx->f8.u32l = TRUNC_W_S(ctx->f0.fl);
    // 0x800801BC: mfc1        $t8, $f8
    ctx->r24 = (int32_t)ctx->f8.u32l;
    // 0x800801C0: nop

    // 0x800801C4: sh          $t8, 0x52($s0)
    MEM_H(0X52, ctx->r16) = ctx->r24;
    // 0x800801C8: lwc1        $f10, 0x0($s2)
    ctx->f10.u32l = MEM_W(ctx->r18, 0X0);
    // 0x800801CC: sub.s       $f12, $f10, $f28
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 28);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f28.fl); 
    ctx->f12.fl = ctx->f10.fl - ctx->f28.fl;
    // 0x800801D0: trunc.w.s   $f4, $f12
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 12);
    ctx->f4.u32l = TRUNC_W_S(ctx->f12.fl);
    // 0x800801D4: mfc1        $t0, $f4
    ctx->r8 = (int32_t)ctx->f4.u32l;
    // 0x800801D8: nop

    // 0x800801DC: sh          $t0, 0x10($s0)
    MEM_H(0X10, ctx->r16) = ctx->r8;
    // 0x800801E0: lwc1        $f6, 0x4($s2)
    ctx->f6.u32l = MEM_W(ctx->r18, 0X4);
    // 0x800801E4: sub.s       $f14, $f6, $f30
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 30);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f30.fl); 
    ctx->f14.fl = ctx->f6.fl - ctx->f30.fl;
    // 0x800801E8: trunc.w.s   $f8, $f14
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 14);
    ctx->f8.u32l = TRUNC_W_S(ctx->f14.fl);
    // 0x800801EC: mfc1        $t2, $f8
    ctx->r10 = (int32_t)ctx->f8.u32l;
    // 0x800801F0: jal         0x8004D30C
    // 0x800801F4: sh          $t2, 0x14($s0)
    MEM_H(0X14, ctx->r16) = ctx->r10;
    func_8004D30C(rdram, ctx);
        goto after_3;
    // 0x800801F4: sh          $t2, 0x14($s0)
    MEM_H(0X14, ctx->r16) = ctx->r10;
    after_3:
    // 0x800801F8: trunc.w.s   $f10, $f0
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 0);
    ctx->f10.u32l = TRUNC_W_S(ctx->f0.fl);
    // 0x800801FC: mfc1        $t4, $f10
    ctx->r12 = (int32_t)ctx->f10.u32l;
    // 0x80080200: nop

    // 0x80080204: sh          $t4, 0x12($s0)
    MEM_H(0X12, ctx->r16) = ctx->r12;
    // 0x80080208: lwc1        $f4, 0x0($s2)
    ctx->f4.u32l = MEM_W(ctx->r18, 0X0);
    // 0x8008020C: add.s       $f12, $f4, $f28
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 28);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f28.fl); 
    ctx->f12.fl = ctx->f4.fl + ctx->f28.fl;
    // 0x80080210: trunc.w.s   $f6, $f12
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 12);
    ctx->f6.u32l = TRUNC_W_S(ctx->f12.fl);
    // 0x80080214: mfc1        $t6, $f6
    ctx->r14 = (int32_t)ctx->f6.u32l;
    // 0x80080218: nop

    // 0x8008021C: sh          $t6, 0x60($s0)
    MEM_H(0X60, ctx->r16) = ctx->r14;
    // 0x80080220: lwc1        $f8, 0x4($s2)
    ctx->f8.u32l = MEM_W(ctx->r18, 0X4);
    // 0x80080224: add.s       $f14, $f8, $f30
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 30);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f30.fl); 
    ctx->f14.fl = ctx->f8.fl + ctx->f30.fl;
    // 0x80080228: trunc.w.s   $f10, $f14
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 14);
    ctx->f10.u32l = TRUNC_W_S(ctx->f14.fl);
    // 0x8008022C: mfc1        $t8, $f10
    ctx->r24 = (int32_t)ctx->f10.u32l;
    // 0x80080230: jal         0x8004D30C
    // 0x80080234: sh          $t8, 0x64($s0)
    MEM_H(0X64, ctx->r16) = ctx->r24;
    func_8004D30C(rdram, ctx);
        goto after_4;
    // 0x80080234: sh          $t8, 0x64($s0)
    MEM_H(0X64, ctx->r16) = ctx->r24;
    after_4:
    // 0x80080238: trunc.w.s   $f4, $f0
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    ctx->f4.u32l = TRUNC_W_S(ctx->f0.fl);
    // 0x8008023C: mfc1        $t0, $f4
    ctx->r8 = (int32_t)ctx->f4.u32l;
    // 0x80080240: nop

    // 0x80080244: sh          $t0, 0x62($s0)
    MEM_H(0X62, ctx->r16) = ctx->r8;
    // 0x80080248: lwc1        $f8, 0x78($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X78);
    // 0x8008024C: lwc1        $f6, 0x0($s2)
    ctx->f6.u32l = MEM_W(ctx->r18, 0X0);
    // 0x80080250: add.s       $f24, $f6, $f8
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f24.fl = ctx->f6.fl + ctx->f8.fl;
    // 0x80080254: trunc.w.s   $f10, $f24
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 24);
    ctx->f10.u32l = TRUNC_W_S(ctx->f24.fl);
    // 0x80080258: mov.s       $f12, $f24
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 24);
    ctx->f12.fl = ctx->f24.fl;
    // 0x8008025C: mfc1        $t2, $f10
    ctx->r10 = (int32_t)ctx->f10.u32l;
    // 0x80080260: nop

    // 0x80080264: sh          $t2, 0x40($s0)
    MEM_H(0X40, ctx->r16) = ctx->r10;
    // 0x80080268: lwc1        $f6, 0x74($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X74);
    // 0x8008026C: lwc1        $f4, 0x4($s2)
    ctx->f4.u32l = MEM_W(ctx->r18, 0X4);
    // 0x80080270: add.s       $f26, $f4, $f6
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f26.fl = ctx->f4.fl + ctx->f6.fl;
    // 0x80080274: trunc.w.s   $f8, $f26
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 26);
    ctx->f8.u32l = TRUNC_W_S(ctx->f26.fl);
    // 0x80080278: mov.s       $f14, $f26
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 26);
    ctx->f14.fl = ctx->f26.fl;
    // 0x8008027C: mfc1        $t4, $f8
    ctx->r12 = (int32_t)ctx->f8.u32l;
    // 0x80080280: jal         0x8004D30C
    // 0x80080284: sh          $t4, 0x44($s0)
    MEM_H(0X44, ctx->r16) = ctx->r12;
    func_8004D30C(rdram, ctx);
        goto after_5;
    // 0x80080284: sh          $t4, 0x44($s0)
    MEM_H(0X44, ctx->r16) = ctx->r12;
    after_5:
    // 0x80080288: sub.s       $f12, $f24, $f28
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 28);
    NAN_CHECK(ctx->f24.fl); NAN_CHECK(ctx->f28.fl); 
    ctx->f12.fl = ctx->f24.fl - ctx->f28.fl;
    // 0x8008028C: sub.s       $f14, $f26, $f30
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 30);
    NAN_CHECK(ctx->f26.fl); NAN_CHECK(ctx->f30.fl); 
    ctx->f14.fl = ctx->f26.fl - ctx->f30.fl;
    // 0x80080290: trunc.w.s   $f10, $f0
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 0);
    ctx->f10.u32l = TRUNC_W_S(ctx->f0.fl);
    // 0x80080294: trunc.w.s   $f4, $f12
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 12);
    ctx->f4.u32l = TRUNC_W_S(ctx->f12.fl);
    // 0x80080298: mfc1        $t6, $f10
    ctx->r14 = (int32_t)ctx->f10.u32l;
    // 0x8008029C: trunc.w.s   $f6, $f14
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 14);
    ctx->f6.u32l = TRUNC_W_S(ctx->f14.fl);
    // 0x800802A0: mfc1        $t8, $f4
    ctx->r24 = (int32_t)ctx->f4.u32l;
    // 0x800802A4: sh          $t6, 0x42($s0)
    MEM_H(0X42, ctx->r16) = ctx->r14;
    // 0x800802A8: mfc1        $t0, $f6
    ctx->r8 = (int32_t)ctx->f6.u32l;
    // 0x800802AC: sh          $t8, 0x20($s0)
    MEM_H(0X20, ctx->r16) = ctx->r24;
    // 0x800802B0: jal         0x8004D30C
    // 0x800802B4: sh          $t0, 0x24($s0)
    MEM_H(0X24, ctx->r16) = ctx->r8;
    func_8004D30C(rdram, ctx);
        goto after_6;
    // 0x800802B4: sh          $t0, 0x24($s0)
    MEM_H(0X24, ctx->r16) = ctx->r8;
    after_6:
    // 0x800802B8: add.s       $f12, $f24, $f28
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 28);
    NAN_CHECK(ctx->f24.fl); NAN_CHECK(ctx->f28.fl); 
    ctx->f12.fl = ctx->f24.fl + ctx->f28.fl;
    // 0x800802BC: add.s       $f14, $f26, $f30
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 30);
    NAN_CHECK(ctx->f26.fl); NAN_CHECK(ctx->f30.fl); 
    ctx->f14.fl = ctx->f26.fl + ctx->f30.fl;
    // 0x800802C0: trunc.w.s   $f8, $f0
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 0);
    ctx->f8.u32l = TRUNC_W_S(ctx->f0.fl);
    // 0x800802C4: trunc.w.s   $f10, $f12
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 12);
    ctx->f10.u32l = TRUNC_W_S(ctx->f12.fl);
    // 0x800802C8: mfc1        $t2, $f8
    ctx->r10 = (int32_t)ctx->f8.u32l;
    // 0x800802CC: trunc.w.s   $f4, $f14
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 14);
    ctx->f4.u32l = TRUNC_W_S(ctx->f14.fl);
    // 0x800802D0: mfc1        $t4, $f10
    ctx->r12 = (int32_t)ctx->f10.u32l;
    // 0x800802D4: sh          $t2, 0x22($s0)
    MEM_H(0X22, ctx->r16) = ctx->r10;
    // 0x800802D8: mfc1        $t6, $f4
    ctx->r14 = (int32_t)ctx->f4.u32l;
    // 0x800802DC: sh          $t4, 0x70($s0)
    MEM_H(0X70, ctx->r16) = ctx->r12;
    // 0x800802E0: jal         0x8004D30C
    // 0x800802E4: sh          $t6, 0x74($s0)
    MEM_H(0X74, ctx->r16) = ctx->r14;
    func_8004D30C(rdram, ctx);
        goto after_7;
    // 0x800802E4: sh          $t6, 0x74($s0)
    MEM_H(0X74, ctx->r16) = ctx->r14;
    after_7:
    // 0x800802E8: trunc.w.s   $f6, $f0
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 0);
    ctx->f6.u32l = TRUNC_W_S(ctx->f0.fl);
    // 0x800802EC: or          $v0, $s1, $zero
    ctx->r2 = ctx->r17 | 0;
    // 0x800802F0: addiu       $s1, $s1, 0x8
    ctx->r17 = ADD32(ctx->r17, 0X8);
    // 0x800802F4: lui         $t9, 0x400
    ctx->r25 = S32(0X400 << 16);
    // 0x800802F8: mfc1        $t8, $f6
    ctx->r24 = (int32_t)ctx->f6.u32l;
    // 0x800802FC: ori         $t9, $t9, 0x107F
    ctx->r25 = ctx->r25 | 0X107F;
    // 0x80080300: or          $v1, $s1, $zero
    ctx->r3 = ctx->r17 | 0;
    // 0x80080304: sh          $t8, 0x72($s0)
    MEM_H(0X72, ctx->r16) = ctx->r24;
    // 0x80080308: sw          $s5, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r21;
    // 0x8008030C: sw          $t9, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r25;
    // 0x80080310: addiu       $s1, $s1, 0x8
    ctx->r17 = ADD32(ctx->r17, 0X8);
    // 0x80080314: addiu       $t0, $zero, 0xF05
    ctx->r8 = ADD32(0, 0XF05);
    // 0x80080318: sw          $t0, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r8;
    // 0x8008031C: sw          $s3, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r19;
    // 0x80080320: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    // 0x80080324: addiu       $s1, $s1, 0x8
    ctx->r17 = ADD32(ctx->r17, 0X8);
    // 0x80080328: lui         $t1, 0x5
    ctx->r9 = S32(0X5 << 16);
    // 0x8008032C: ori         $t1, $t1, 0xF1E
    ctx->r9 = ctx->r9 | 0XF1E;
    // 0x80080330: or          $a1, $s1, $zero
    ctx->r5 = ctx->r17 | 0;
    // 0x80080334: sw          $t1, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r9;
    // 0x80080338: sw          $s3, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r19;
    // 0x8008033C: addiu       $s1, $s1, 0x8
    ctx->r17 = ADD32(ctx->r17, 0X8);
    // 0x80080340: lui         $t2, 0x1E
    ctx->r10 = S32(0X1E << 16);
    // 0x80080344: ori         $t2, $t2, 0xF19
    ctx->r10 = ctx->r10 | 0XF19;
    // 0x80080348: or          $a2, $s1, $zero
    ctx->r6 = ctx->r17 | 0;
    // 0x8008034C: sw          $t2, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r10;
    // 0x80080350: sw          $s3, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r19;
    // 0x80080354: addiu       $s1, $s1, 0x8
    ctx->r17 = ADD32(ctx->r17, 0X8);
    // 0x80080358: lui         $t3, 0x1E
    ctx->r11 = S32(0X1E << 16);
    // 0x8008035C: ori         $t3, $t3, 0x2314
    ctx->r11 = ctx->r11 | 0X2314;
    // 0x80080360: or          $v0, $s1, $zero
    ctx->r2 = ctx->r17 | 0;
    // 0x80080364: sw          $t3, 0x4($a2)
    MEM_W(0X4, ctx->r6) = ctx->r11;
    // 0x80080368: sw          $s3, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r19;
    // 0x8008036C: addiu       $s1, $s1, 0x8
    ctx->r17 = ADD32(ctx->r17, 0X8);
    // 0x80080370: lui         $t4, 0x1E
    ctx->r12 = S32(0X1E << 16);
    // 0x80080374: ori         $t4, $t4, 0x1405
    ctx->r12 = ctx->r12 | 0X1405;
    // 0x80080378: or          $v1, $s1, $zero
    ctx->r3 = ctx->r17 | 0;
    // 0x8008037C: sw          $t4, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r12;
    // 0x80080380: sw          $s3, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r19;
    // 0x80080384: lui         $t5, 0x5
    ctx->r13 = S32(0X5 << 16);
    // 0x80080388: ori         $t5, $t5, 0x140A
    ctx->r13 = ctx->r13 | 0X140A;
    // 0x8008038C: sw          $t5, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r13;
    // 0x80080390: sw          $s3, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r19;
    // 0x80080394: addiu       $s1, $s1, 0x8
    ctx->r17 = ADD32(ctx->r17, 0X8);
    // 0x80080398: addiu       $s2, $s2, 0xC
    ctx->r18 = ADD32(ctx->r18, 0XC);
L_8008039C:
    // 0x8008039C: sltu        $at, $s2, $fp
    ctx->r1 = ctx->r18 < ctx->r30 ? 1 : 0;
    // 0x800803A0: bne         $at, $zero, L_8008006C
    if (ctx->r1 != 0) {
        // 0x800803A4: addiu       $s6, $s6, 0x8
        ctx->r22 = ADD32(ctx->r22, 0X8);
            goto L_8008006C;
    }
    // 0x800803A4: addiu       $s6, $s6, 0x8
    ctx->r22 = ADD32(ctx->r22, 0X8);
    // 0x800803A8: or          $v0, $s1, $zero
    ctx->r2 = ctx->r17 | 0;
L_800803AC:
    // 0x800803AC: lw          $ra, 0x6C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X6C);
    // 0x800803B0: ldc1        $f20, 0x18($sp)
    CHECK_FR(ctx, 20);
    ctx->f20.u64 = LD(ctx->r29, 0X18);
    // 0x800803B4: ldc1        $f22, 0x20($sp)
    CHECK_FR(ctx, 22);
    ctx->f22.u64 = LD(ctx->r29, 0X20);
    // 0x800803B8: ldc1        $f24, 0x28($sp)
    CHECK_FR(ctx, 24);
    ctx->f24.u64 = LD(ctx->r29, 0X28);
    // 0x800803BC: ldc1        $f26, 0x30($sp)
    CHECK_FR(ctx, 26);
    ctx->f26.u64 = LD(ctx->r29, 0X30);
    // 0x800803C0: ldc1        $f28, 0x38($sp)
    CHECK_FR(ctx, 28);
    ctx->f28.u64 = LD(ctx->r29, 0X38);
    // 0x800803C4: ldc1        $f30, 0x40($sp)
    CHECK_FR(ctx, 30);
    ctx->f30.u64 = LD(ctx->r29, 0X40);
    // 0x800803C8: lw          $s0, 0x48($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X48);
    // 0x800803CC: lw          $s1, 0x4C($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X4C);
    // 0x800803D0: lw          $s2, 0x50($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X50);
    // 0x800803D4: lw          $s3, 0x54($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X54);
    // 0x800803D8: lw          $s4, 0x58($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X58);
    // 0x800803DC: lw          $s5, 0x5C($sp)
    ctx->r21 = MEM_W(ctx->r29, 0X5C);
    // 0x800803E0: lw          $s6, 0x60($sp)
    ctx->r22 = MEM_W(ctx->r29, 0X60);
    // 0x800803E4: lw          $s7, 0x64($sp)
    ctx->r23 = MEM_W(ctx->r29, 0X64);
    // 0x800803E8: lw          $fp, 0x68($sp)
    ctx->r30 = MEM_W(ctx->r29, 0X68);
    // 0x800803EC: jr          $ra
    // 0x800803F0: addiu       $sp, $sp, 0x98
    ctx->r29 = ADD32(ctx->r29, 0X98);
    return;
    // 0x800803F0: addiu       $sp, $sp, 0x98
    ctx->r29 = ADD32(ctx->r29, 0X98);
    // 0x800803F4: nop

    // 0x800803F8: nop

    // 0x800803FC: nop

;}
RECOMP_FUNC void func_80080400(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x80080400: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x80080404: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x80080408: jal         0x80085EEC
    // 0x8008040C: nop

    func_80085EEC(rdram, ctx);
        goto after_0;
    // 0x8008040C: nop

    after_0:
    // 0x80080410: lui         $t6, 0x801D
    ctx->r14 = S32(0X801D << 16);
    // 0x80080414: lw          $t6, -0x19B0($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X19B0);
    // 0x80080418: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x8008041C: bne         $t6, $at, L_80080434
    if (ctx->r14 != ctx->r1) {
        // 0x80080420: nop
    
            goto L_80080434;
    }
    // 0x80080420: nop

    // 0x80080424: jal         0x8008044C
    // 0x80080428: nop

    func_8008044C(rdram, ctx);
        goto after_1;
    // 0x80080428: nop

    after_1:
    // 0x8008042C: b           L_80080440
    // 0x80080430: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_80080440;
    // 0x80080430: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_80080434:
    // 0x80080434: jal         0x80080630
    // 0x80080438: nop

    func_80080630(rdram, ctx);
        goto after_2;
    // 0x80080438: nop

    after_2:
    // 0x8008043C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_80080440:
    // 0x80080440: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x80080444: jr          $ra
    // 0x80080448: nop

    return;
    // 0x80080448: nop

;}
RECOMP_FUNC void func_8008044C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8008044C: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x80080450: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x80080454: jal         0x80086DA8
    // 0x80080458: nop

    func_80086DA8(rdram, ctx);
        goto after_0;
    // 0x80080458: nop

    after_0:
    // 0x8008045C: jal         0x80087E70
    // 0x80080460: nop

    func_80087E70(rdram, ctx);
        goto after_1;
    // 0x80080460: nop

    after_1:
    // 0x80080464: jal         0x800861AC
    // 0x80080468: nop

    func_800861AC(rdram, ctx);
        goto after_2;
    // 0x80080468: nop

    after_2:
    // 0x8008046C: jal         0x80087E70
    // 0x80080470: nop

    func_80087E70(rdram, ctx);
        goto after_3;
    // 0x80080470: nop

    after_3:
    // 0x80080474: jal         0x800861AC
    // 0x80080478: nop

    func_800861AC(rdram, ctx);
        goto after_4;
    // 0x80080478: nop

    after_4:
    // 0x8008047C: jal         0x80087E70
    // 0x80080480: nop

    func_80087E70(rdram, ctx);
        goto after_5;
    // 0x80080480: nop

    after_5:
    // 0x80080484: jal         0x80088418
    // 0x80080488: nop

    func_80088418(rdram, ctx);
        goto after_6;
    // 0x80080488: nop

    after_6:
    // 0x8008048C: jal         0x80085510
    // 0x80080490: nop

    func_80085510(rdram, ctx);
        goto after_7;
    // 0x80080490: nop

    after_7:
    // 0x80080494: jal         0x80080864
    // 0x80080498: nop

    func_80080864(rdram, ctx);
        goto after_8;
    // 0x80080498: nop

    after_8:
    // 0x8008049C: jal         0x80080E34
    // 0x800804A0: nop

    func_80080E34(rdram, ctx);
        goto after_9;
    // 0x800804A0: nop

    after_9:
    // 0x800804A4: jal         0x80081048
    // 0x800804A8: nop

    func_80081048(rdram, ctx);
        goto after_10;
    // 0x800804A8: nop

    after_10:
    // 0x800804AC: jal         0x80087AE8
    // 0x800804B0: nop

    func_80087AE8(rdram, ctx);
        goto after_11;
    // 0x800804B0: nop

    after_11:
    // 0x800804B4: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800804B8: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800804BC: jr          $ra
    // 0x800804C0: nop

    return;
    // 0x800804C0: nop

;}
RECOMP_FUNC void func_800804C4(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800804C4: lui         $v1, 0x801C
    ctx->r3 = S32(0X801C << 16);
    // 0x800804C8: lw          $v1, 0x3C58($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X3C58);
    // 0x800804CC: addiu       $t0, $zero, 0x104
    ctx->r8 = ADD32(0, 0X104);
    // 0x800804D0: lui         $a2, 0x801C
    ctx->r6 = S32(0X801C << 16);
    // 0x800804D4: lw          $a0, 0x8($v1)
    ctx->r4 = MEM_W(ctx->r3, 0X8);
    // 0x800804D8: lw          $a2, 0x3C54($a2)
    ctx->r6 = MEM_W(ctx->r6, 0X3C54);
    // 0x800804DC: lui         $a1, 0x801C
    ctx->r5 = S32(0X801C << 16);
    // 0x800804E0: multu       $a0, $t0
    result = U64(U32(ctx->r4)) * U64(U32(ctx->r8)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x800804E4: lw          $a1, 0x3C50($a1)
    ctx->r5 = MEM_W(ctx->r5, 0X3C50);
    // 0x800804E8: mtc1        $zero, $f12
    ctx->f12.u32l = 0;
    // 0x800804EC: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x800804F0: lwc1        $f0, 0x4C($a1)
    ctx->f0.u32l = MEM_W(ctx->r5, 0X4C);
    // 0x800804F4: lwc1        $f2, 0x44($a1)
    ctx->f2.u32l = MEM_W(ctx->r5, 0X44);
    // 0x800804F8: sll         $t7, $v0, 6
    ctx->r15 = S32(ctx->r2 << 6);
    // 0x800804FC: addu        $t7, $t7, $v0
    ctx->r15 = ADD32(ctx->r15, ctx->r2);
    // 0x80080500: sll         $t7, $t7, 2
    ctx->r15 = S32(ctx->r15 << 2);
    // 0x80080504: addu        $t8, $a2, $t7
    ctx->r24 = ADD32(ctx->r6, ctx->r15);
    // 0x80080508: mflo        $t6
    ctx->r14 = lo;
    // 0x8008050C: addu        $a3, $a2, $t6
    ctx->r7 = ADD32(ctx->r6, ctx->r14);
    // 0x80080510: lwc1        $f4, 0x8($a3)
    ctx->f4.u32l = MEM_W(ctx->r7, 0X8);
    // 0x80080514: lwc1        $f18, 0x0($a3)
    ctx->f18.u32l = MEM_W(ctx->r7, 0X0);
    // 0x80080518: lwc1        $f8, 0x74($a3)
    ctx->f8.u32l = MEM_W(ctx->r7, 0X74);
    // 0x8008051C: sub.s       $f6, $f0, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = ctx->f0.fl - ctx->f4.fl;
    // 0x80080520: lwc1        $f16, 0x70($a3)
    ctx->f16.u32l = MEM_W(ctx->r7, 0X70);
    // 0x80080524: sub.s       $f4, $f2, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f4.fl = ctx->f2.fl - ctx->f18.fl;
    // 0x80080528: mul.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = MUL_S(ctx->f6.fl, ctx->f8.fl);
    // 0x8008052C: nop

    // 0x80080530: mul.s       $f6, $f16, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = MUL_S(ctx->f16.fl, ctx->f4.fl);
    // 0x80080534: add.s       $f8, $f10, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = ctx->f10.fl + ctx->f6.fl;
    // 0x80080538: c.lt.s      $f12, $f8
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 8);
    c1cs = ctx->f12.fl < ctx->f8.fl;
    // 0x8008053C: nop

    // 0x80080540: bc1f        L_80080588
    if (!c1cs) {
        // 0x80080544: nop
    
            goto L_80080588;
    }
    // 0x80080544: nop

    // 0x80080548: lw          $t4, 0x0($v1)
    ctx->r12 = MEM_W(ctx->r3, 0X0);
    // 0x8008054C: lw          $t9, 0x4($v1)
    ctx->r25 = MEM_W(ctx->r3, 0X4);
    // 0x80080550: lui         $at, 0x801C
    ctx->r1 = S32(0X801C << 16);
    // 0x80080554: sll         $t5, $t4, 3
    ctx->r13 = S32(ctx->r12 << 3);
    // 0x80080558: subu        $t5, $t5, $t4
    ctx->r13 = SUB32(ctx->r13, ctx->r12);
    // 0x8008055C: sll         $t1, $t9, 2
    ctx->r9 = S32(ctx->r25 << 2);
    // 0x80080560: addu        $t2, $t8, $t1
    ctx->r10 = ADD32(ctx->r24, ctx->r9);
    // 0x80080564: sll         $t5, $t5, 4
    ctx->r13 = S32(ctx->r13 << 4);
    // 0x80080568: lw          $t3, 0xCC($t2)
    ctx->r11 = MEM_W(ctx->r10, 0XCC);
    // 0x8008056C: subu        $t5, $t5, $t4
    ctx->r13 = SUB32(ctx->r13, ctx->r12);
    // 0x80080570: sll         $t5, $t5, 3
    ctx->r13 = S32(ctx->r13 << 3);
    // 0x80080574: addu        $at, $at, $t5
    ctx->r1 = ADD32(ctx->r1, ctx->r13);
    // 0x80080578: sw          $t3, 0x2948($at)
    MEM_W(0X2948, ctx->r1) = ctx->r11;
    // 0x8008057C: lwc1        $f2, 0x44($a1)
    ctx->f2.u32l = MEM_W(ctx->r5, 0X44);
    // 0x80080580: lwc1        $f0, 0x4C($a1)
    ctx->f0.u32l = MEM_W(ctx->r5, 0X4C);
    // 0x80080584: lw          $a0, 0x8($v1)
    ctx->r4 = MEM_W(ctx->r3, 0X8);
L_80080588:
    // 0x80080588: lw          $a1, 0x4($v1)
    ctx->r5 = MEM_W(ctx->r3, 0X4);
    // 0x8008058C: sll         $t7, $a0, 6
    ctx->r15 = S32(ctx->r4 << 6);
    // 0x80080590: addu        $t7, $t7, $a0
    ctx->r15 = ADD32(ctx->r15, ctx->r4);
    // 0x80080594: sll         $t7, $t7, 2
    ctx->r15 = S32(ctx->r15 << 2);
    // 0x80080598: addu        $t9, $a2, $t7
    ctx->r25 = ADD32(ctx->r6, ctx->r15);
    // 0x8008059C: sll         $t6, $a1, 2
    ctx->r14 = S32(ctx->r5 << 2);
    // 0x800805A0: addu        $t8, $t9, $t6
    ctx->r24 = ADD32(ctx->r25, ctx->r14);
    // 0x800805A4: lw          $v0, 0xF4($t8)
    ctx->r2 = MEM_W(ctx->r24, 0XF4);
    // 0x800805A8: multu       $v0, $t0
    result = U64(U32(ctx->r2)) * U64(U32(ctx->r8)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x800805AC: sll         $t2, $v0, 6
    ctx->r10 = S32(ctx->r2 << 6);
    // 0x800805B0: addu        $t2, $t2, $v0
    ctx->r10 = ADD32(ctx->r10, ctx->r2);
    // 0x800805B4: sll         $t2, $t2, 2
    ctx->r10 = S32(ctx->r10 << 2);
    // 0x800805B8: addu        $t4, $a2, $t2
    ctx->r12 = ADD32(ctx->r6, ctx->r10);
    // 0x800805BC: addu        $t3, $t4, $t6
    ctx->r11 = ADD32(ctx->r12, ctx->r14);
    // 0x800805C0: mflo        $t1
    ctx->r9 = lo;
    // 0x800805C4: addu        $a3, $a2, $t1
    ctx->r7 = ADD32(ctx->r6, ctx->r9);
    // 0x800805C8: lwc1        $f18, 0x8($a3)
    ctx->f18.u32l = MEM_W(ctx->r7, 0X8);
    // 0x800805CC: lwc1        $f8, 0x0($a3)
    ctx->f8.u32l = MEM_W(ctx->r7, 0X0);
    // 0x800805D0: lwc1        $f4, 0x74($a3)
    ctx->f4.u32l = MEM_W(ctx->r7, 0X74);
    // 0x800805D4: sub.s       $f16, $f0, $f18
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f16.fl = ctx->f0.fl - ctx->f18.fl;
    // 0x800805D8: lwc1        $f6, 0x70($a3)
    ctx->f6.u32l = MEM_W(ctx->r7, 0X70);
    // 0x800805DC: sub.s       $f18, $f2, $f8
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f18.fl = ctx->f2.fl - ctx->f8.fl;
    // 0x800805E0: mul.s       $f10, $f16, $f4
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f10.fl = MUL_S(ctx->f16.fl, ctx->f4.fl);
    // 0x800805E4: nop

    // 0x800805E8: mul.s       $f16, $f6, $f18
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f16.fl = MUL_S(ctx->f6.fl, ctx->f18.fl);
    // 0x800805EC: add.s       $f4, $f10, $f16
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f4.fl = ctx->f10.fl + ctx->f16.fl;
    // 0x800805F0: c.lt.s      $f4, $f12
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 12);
    c1cs = ctx->f4.fl < ctx->f12.fl;
    // 0x800805F4: nop

    // 0x800805F8: bc1f        L_80080628
    if (!c1cs) {
        // 0x800805FC: nop
    
            goto L_80080628;
    }
    // 0x800805FC: nop

    // 0x80080600: lw          $t6, 0x0($v1)
    ctx->r14 = MEM_W(ctx->r3, 0X0);
    // 0x80080604: lw          $t5, 0xF4($t3)
    ctx->r13 = MEM_W(ctx->r11, 0XF4);
    // 0x80080608: lui         $at, 0x801C
    ctx->r1 = S32(0X801C << 16);
    // 0x8008060C: sll         $t7, $t6, 3
    ctx->r15 = S32(ctx->r14 << 3);
    // 0x80080610: subu        $t7, $t7, $t6
    ctx->r15 = SUB32(ctx->r15, ctx->r14);
    // 0x80080614: sll         $t7, $t7, 4
    ctx->r15 = S32(ctx->r15 << 4);
    // 0x80080618: subu        $t7, $t7, $t6
    ctx->r15 = SUB32(ctx->r15, ctx->r14);
    // 0x8008061C: sll         $t7, $t7, 3
    ctx->r15 = S32(ctx->r15 << 3);
    // 0x80080620: addu        $at, $at, $t7
    ctx->r1 = ADD32(ctx->r1, ctx->r15);
    // 0x80080624: sw          $t5, 0x2948($at)
    MEM_W(0X2948, ctx->r1) = ctx->r13;
L_80080628:
    // 0x80080628: jr          $ra
    // 0x8008062C: nop

    return;
    // 0x8008062C: nop

;}
RECOMP_FUNC void func_80080630(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x80080630: lui         $v1, 0x801C
    ctx->r3 = S32(0X801C << 16);
    // 0x80080634: addiu       $v1, $v1, 0x3C50
    ctx->r3 = ADD32(ctx->r3, 0X3C50);
    // 0x80080638: lw          $t6, 0x0($v1)
    ctx->r14 = MEM_W(ctx->r3, 0X0);
    // 0x8008063C: lui         $t8, 0x801C
    ctx->r24 = S32(0X801C << 16);
    // 0x80080640: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x80080644: sb          $zero, 0xB52($t6)
    MEM_B(0XB52, ctx->r14) = 0;
    // 0x80080648: lw          $t7, 0x0($v1)
    ctx->r15 = MEM_W(ctx->r3, 0X0);
    // 0x8008064C: addiu       $sp, $sp, -0x8
    ctx->r29 = ADD32(ctx->r29, -0X8);
    // 0x80080650: lui         $t9, 0x8023
    ctx->r25 = S32(0X8023 << 16);
    // 0x80080654: sb          $zero, 0xB53($t7)
    MEM_B(0XB53, ctx->r15) = 0;
    // 0x80080658: lw          $t8, 0x3C58($t8)
    ctx->r24 = MEM_W(ctx->r24, 0X3C58);
    // 0x8008065C: lw          $v0, 0x5C($t8)
    ctx->r2 = MEM_W(ctx->r24, 0X5C);
    // 0x80080660: beq         $v0, $at, L_80080690
    if (ctx->r2 == ctx->r1) {
        // 0x80080664: nop
    
            goto L_80080690;
    }
    // 0x80080664: nop

    // 0x80080668: beq         $v0, $zero, L_800806C8
    if (ctx->r2 == 0) {
        // 0x8008066C: lui         $t6, 0x8023
        ctx->r14 = S32(0X8023 << 16);
            goto L_800806C8;
    }
    // 0x8008066C: lui         $t6, 0x8023
    ctx->r14 = S32(0X8023 << 16);
    // 0x80080670: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    // 0x80080674: beq         $v0, $a0, L_80080754
    if (ctx->r2 == ctx->r4) {
        // 0x80080678: lui         $t7, 0x8023
        ctx->r15 = S32(0X8023 << 16);
            goto L_80080754;
    }
    // 0x80080678: lui         $t7, 0x8023
    ctx->r15 = S32(0X8023 << 16);
    // 0x8008067C: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x80080680: beq         $v0, $a1, L_800807DC
    if (ctx->r2 == ctx->r5) {
        // 0x80080684: lui         $t6, 0x8023
        ctx->r14 = S32(0X8023 << 16);
            goto L_800807DC;
    }
    // 0x80080684: lui         $t6, 0x8023
    ctx->r14 = S32(0X8023 << 16);
    // 0x80080688: b           L_8008085C
    // 0x8008068C: nop

        goto L_8008085C;
    // 0x8008068C: nop

L_80080690:
    // 0x80080690: lw          $t9, -0x7570($t9)
    ctx->r25 = MEM_W(ctx->r25, -0X7570);
    // 0x80080694: slti        $at, $t9, 0x10
    ctx->r1 = SIGNED(ctx->r25) < 0X10 ? 1 : 0;
    // 0x80080698: beql        $at, $zero, L_800806B8
    if (ctx->r1 == 0) {
        // 0x8008069C: lw          $v0, 0x0($v1)
        ctx->r2 = MEM_W(ctx->r3, 0X0);
            goto L_800806B8;
    }
    goto skip_0;
    // 0x8008069C: lw          $v0, 0x0($v1)
    ctx->r2 = MEM_W(ctx->r3, 0X0);
    skip_0:
    // 0x800806A0: lw          $v0, 0x0($v1)
    ctx->r2 = MEM_W(ctx->r3, 0X0);
    // 0x800806A4: lhu         $t0, 0xB50($v0)
    ctx->r8 = MEM_HU(ctx->r2, 0XB50);
    // 0x800806A8: ori         $t1, $t0, 0xA000
    ctx->r9 = ctx->r8 | 0XA000;
    // 0x800806AC: b           L_8008085C
    // 0x800806B0: sh          $t1, 0xB50($v0)
    MEM_H(0XB50, ctx->r2) = ctx->r9;
        goto L_8008085C;
    // 0x800806B0: sh          $t1, 0xB50($v0)
    MEM_H(0XB50, ctx->r2) = ctx->r9;
    // 0x800806B4: lw          $v0, 0x0($v1)
    ctx->r2 = MEM_W(ctx->r3, 0X0);
L_800806B8:
    // 0x800806B8: lhu         $t2, 0xB50($v0)
    ctx->r10 = MEM_HU(ctx->r2, 0XB50);
    // 0x800806BC: andi        $t3, $t2, 0x5FFF
    ctx->r11 = ctx->r10 & 0X5FFF;
    // 0x800806C0: b           L_8008085C
    // 0x800806C4: sh          $t3, 0xB50($v0)
    MEM_H(0XB50, ctx->r2) = ctx->r11;
        goto L_8008085C;
    // 0x800806C4: sh          $t3, 0xB50($v0)
    MEM_H(0XB50, ctx->r2) = ctx->r11;
L_800806C8:
    // 0x800806C8: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x800806CC: lw          $v0, -0x4CC8($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X4CC8);
    // 0x800806D0: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    // 0x800806D4: addiu       $t4, $zero, 0x5
    ctx->r12 = ADD32(0, 0X5);
    // 0x800806D8: beq         $v0, $zero, L_800806FC
    if (ctx->r2 == 0) {
        // 0x800806DC: nop
    
            goto L_800806FC;
    }
    // 0x800806DC: nop

    // 0x800806E0: beq         $v0, $a0, L_80080704
    if (ctx->r2 == ctx->r4) {
        // 0x800806E4: addiu       $t5, $zero, 0x2
        ctx->r13 = ADD32(0, 0X2);
            goto L_80080704;
    }
    // 0x800806E4: addiu       $t5, $zero, 0x2
    ctx->r13 = ADD32(0, 0X2);
    // 0x800806E8: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x800806EC: beql        $v0, $a1, L_80080710
    if (ctx->r2 == ctx->r5) {
        // 0x800806F0: sw          $zero, 0x4($sp)
        MEM_W(0X4, ctx->r29) = 0;
            goto L_80080710;
    }
    goto skip_1;
    // 0x800806F0: sw          $zero, 0x4($sp)
    MEM_W(0X4, ctx->r29) = 0;
    skip_1:
    // 0x800806F4: b           L_80080714
    // 0x800806F8: lw          $t7, 0x4($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X4);
        goto L_80080714;
    // 0x800806F8: lw          $t7, 0x4($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X4);
L_800806FC:
    // 0x800806FC: b           L_80080710
    // 0x80080700: sw          $t4, 0x4($sp)
    MEM_W(0X4, ctx->r29) = ctx->r12;
        goto L_80080710;
    // 0x80080700: sw          $t4, 0x4($sp)
    MEM_W(0X4, ctx->r29) = ctx->r12;
L_80080704:
    // 0x80080704: b           L_80080710
    // 0x80080708: sw          $t5, 0x4($sp)
    MEM_W(0X4, ctx->r29) = ctx->r13;
        goto L_80080710;
    // 0x80080708: sw          $t5, 0x4($sp)
    MEM_W(0X4, ctx->r29) = ctx->r13;
    // 0x8008070C: sw          $zero, 0x4($sp)
    MEM_W(0X4, ctx->r29) = 0;
L_80080710:
    // 0x80080710: lw          $t7, 0x4($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X4);
L_80080714:
    // 0x80080714: lw          $t6, -0x7570($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X7570);
    // 0x80080718: addiu       $t8, $zero, 0xF
    ctx->r24 = ADD32(0, 0XF);
    // 0x8008071C: subu        $t9, $t8, $t7
    ctx->r25 = SUB32(ctx->r24, ctx->r15);
    // 0x80080720: slt         $at, $t9, $t6
    ctx->r1 = SIGNED(ctx->r25) < SIGNED(ctx->r14) ? 1 : 0;
    // 0x80080724: bnel        $at, $zero, L_80080744
    if (ctx->r1 != 0) {
        // 0x80080728: lw          $v0, 0x0($v1)
        ctx->r2 = MEM_W(ctx->r3, 0X0);
            goto L_80080744;
    }
    goto skip_2;
    // 0x80080728: lw          $v0, 0x0($v1)
    ctx->r2 = MEM_W(ctx->r3, 0X0);
    skip_2:
    // 0x8008072C: lw          $v0, 0x0($v1)
    ctx->r2 = MEM_W(ctx->r3, 0X0);
    // 0x80080730: lhu         $t0, 0xB50($v0)
    ctx->r8 = MEM_HU(ctx->r2, 0XB50);
    // 0x80080734: ori         $t1, $t0, 0xA000
    ctx->r9 = ctx->r8 | 0XA000;
    // 0x80080738: b           L_8008085C
    // 0x8008073C: sh          $t1, 0xB50($v0)
    MEM_H(0XB50, ctx->r2) = ctx->r9;
        goto L_8008085C;
    // 0x8008073C: sh          $t1, 0xB50($v0)
    MEM_H(0XB50, ctx->r2) = ctx->r9;
    // 0x80080740: lw          $v0, 0x0($v1)
    ctx->r2 = MEM_W(ctx->r3, 0X0);
L_80080744:
    // 0x80080744: lhu         $t2, 0xB50($v0)
    ctx->r10 = MEM_HU(ctx->r2, 0XB50);
    // 0x80080748: andi        $t3, $t2, 0x5FFF
    ctx->r11 = ctx->r10 & 0X5FFF;
    // 0x8008074C: b           L_8008085C
    // 0x80080750: sh          $t3, 0xB50($v0)
    MEM_H(0XB50, ctx->r2) = ctx->r11;
        goto L_8008085C;
    // 0x80080750: sh          $t3, 0xB50($v0)
    MEM_H(0XB50, ctx->r2) = ctx->r11;
L_80080754:
    // 0x80080754: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x80080758: lw          $v0, -0x4CC8($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X4CC8);
    // 0x8008075C: addiu       $t4, $zero, 0x5
    ctx->r12 = ADD32(0, 0X5);
    // 0x80080760: beq         $v0, $zero, L_80080784
    if (ctx->r2 == 0) {
        // 0x80080764: nop
    
            goto L_80080784;
    }
    // 0x80080764: nop

    // 0x80080768: beq         $v0, $a0, L_8008078C
    if (ctx->r2 == ctx->r4) {
        // 0x8008076C: addiu       $t5, $zero, 0x3
        ctx->r13 = ADD32(0, 0X3);
            goto L_8008078C;
    }
    // 0x8008076C: addiu       $t5, $zero, 0x3
    ctx->r13 = ADD32(0, 0X3);
    // 0x80080770: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x80080774: beq         $v0, $a1, L_80080794
    if (ctx->r2 == ctx->r5) {
        // 0x80080778: addiu       $t8, $zero, 0x2
        ctx->r24 = ADD32(0, 0X2);
            goto L_80080794;
    }
    // 0x80080778: addiu       $t8, $zero, 0x2
    ctx->r24 = ADD32(0, 0X2);
    // 0x8008077C: b           L_8008079C
    // 0x80080780: lw          $t6, 0x4($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X4);
        goto L_8008079C;
    // 0x80080780: lw          $t6, 0x4($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X4);
L_80080784:
    // 0x80080784: b           L_80080798
    // 0x80080788: sw          $t4, 0x4($sp)
    MEM_W(0X4, ctx->r29) = ctx->r12;
        goto L_80080798;
    // 0x80080788: sw          $t4, 0x4($sp)
    MEM_W(0X4, ctx->r29) = ctx->r12;
L_8008078C:
    // 0x8008078C: b           L_80080798
    // 0x80080790: sw          $t5, 0x4($sp)
    MEM_W(0X4, ctx->r29) = ctx->r13;
        goto L_80080798;
    // 0x80080790: sw          $t5, 0x4($sp)
    MEM_W(0X4, ctx->r29) = ctx->r13;
L_80080794:
    // 0x80080794: sw          $t8, 0x4($sp)
    MEM_W(0X4, ctx->r29) = ctx->r24;
L_80080798:
    // 0x80080798: lw          $t6, 0x4($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X4);
L_8008079C:
    // 0x8008079C: lw          $t7, -0x7570($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X7570);
    // 0x800807A0: addiu       $t9, $zero, 0xF
    ctx->r25 = ADD32(0, 0XF);
    // 0x800807A4: subu        $t0, $t9, $t6
    ctx->r8 = SUB32(ctx->r25, ctx->r14);
    // 0x800807A8: slt         $at, $t0, $t7
    ctx->r1 = SIGNED(ctx->r8) < SIGNED(ctx->r15) ? 1 : 0;
    // 0x800807AC: bnel        $at, $zero, L_800807CC
    if (ctx->r1 != 0) {
        // 0x800807B0: lw          $v0, 0x0($v1)
        ctx->r2 = MEM_W(ctx->r3, 0X0);
            goto L_800807CC;
    }
    goto skip_3;
    // 0x800807B0: lw          $v0, 0x0($v1)
    ctx->r2 = MEM_W(ctx->r3, 0X0);
    skip_3:
    // 0x800807B4: lw          $v0, 0x0($v1)
    ctx->r2 = MEM_W(ctx->r3, 0X0);
    // 0x800807B8: lhu         $t1, 0xB50($v0)
    ctx->r9 = MEM_HU(ctx->r2, 0XB50);
    // 0x800807BC: ori         $t2, $t1, 0xA000
    ctx->r10 = ctx->r9 | 0XA000;
    // 0x800807C0: b           L_8008085C
    // 0x800807C4: sh          $t2, 0xB50($v0)
    MEM_H(0XB50, ctx->r2) = ctx->r10;
        goto L_8008085C;
    // 0x800807C4: sh          $t2, 0xB50($v0)
    MEM_H(0XB50, ctx->r2) = ctx->r10;
    // 0x800807C8: lw          $v0, 0x0($v1)
    ctx->r2 = MEM_W(ctx->r3, 0X0);
L_800807CC:
    // 0x800807CC: lhu         $t3, 0xB50($v0)
    ctx->r11 = MEM_HU(ctx->r2, 0XB50);
    // 0x800807D0: andi        $t4, $t3, 0x5FFF
    ctx->r12 = ctx->r11 & 0X5FFF;
    // 0x800807D4: b           L_8008085C
    // 0x800807D8: sh          $t4, 0xB50($v0)
    MEM_H(0XB50, ctx->r2) = ctx->r12;
        goto L_8008085C;
    // 0x800807D8: sh          $t4, 0xB50($v0)
    MEM_H(0XB50, ctx->r2) = ctx->r12;
L_800807DC:
    // 0x800807DC: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x800807E0: lw          $v0, -0x4CC8($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X4CC8);
    // 0x800807E4: addiu       $t5, $zero, 0x5
    ctx->r13 = ADD32(0, 0X5);
    // 0x800807E8: beq         $v0, $zero, L_80080808
    if (ctx->r2 == 0) {
        // 0x800807EC: nop
    
            goto L_80080808;
    }
    // 0x800807EC: nop

    // 0x800807F0: beq         $v0, $a0, L_80080810
    if (ctx->r2 == ctx->r4) {
        // 0x800807F4: addiu       $t8, $zero, 0x4
        ctx->r24 = ADD32(0, 0X4);
            goto L_80080810;
    }
    // 0x800807F4: addiu       $t8, $zero, 0x4
    ctx->r24 = ADD32(0, 0X4);
    // 0x800807F8: beq         $v0, $a1, L_80080818
    if (ctx->r2 == ctx->r5) {
        // 0x800807FC: addiu       $t9, $zero, 0x4
        ctx->r25 = ADD32(0, 0X4);
            goto L_80080818;
    }
    // 0x800807FC: addiu       $t9, $zero, 0x4
    ctx->r25 = ADD32(0, 0X4);
    // 0x80080800: b           L_80080820
    // 0x80080804: lw          $t7, 0x4($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X4);
        goto L_80080820;
    // 0x80080804: lw          $t7, 0x4($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X4);
L_80080808:
    // 0x80080808: b           L_8008081C
    // 0x8008080C: sw          $t5, 0x4($sp)
    MEM_W(0X4, ctx->r29) = ctx->r13;
        goto L_8008081C;
    // 0x8008080C: sw          $t5, 0x4($sp)
    MEM_W(0X4, ctx->r29) = ctx->r13;
L_80080810:
    // 0x80080810: b           L_8008081C
    // 0x80080814: sw          $t8, 0x4($sp)
    MEM_W(0X4, ctx->r29) = ctx->r24;
        goto L_8008081C;
    // 0x80080814: sw          $t8, 0x4($sp)
    MEM_W(0X4, ctx->r29) = ctx->r24;
L_80080818:
    // 0x80080818: sw          $t9, 0x4($sp)
    MEM_W(0X4, ctx->r29) = ctx->r25;
L_8008081C:
    // 0x8008081C: lw          $t7, 0x4($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X4);
L_80080820:
    // 0x80080820: lw          $t6, -0x7570($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X7570);
    // 0x80080824: addiu       $t0, $zero, 0xF
    ctx->r8 = ADD32(0, 0XF);
    // 0x80080828: subu        $t1, $t0, $t7
    ctx->r9 = SUB32(ctx->r8, ctx->r15);
    // 0x8008082C: slt         $at, $t1, $t6
    ctx->r1 = SIGNED(ctx->r9) < SIGNED(ctx->r14) ? 1 : 0;
    // 0x80080830: bnel        $at, $zero, L_80080850
    if (ctx->r1 != 0) {
        // 0x80080834: lw          $v0, 0x0($v1)
        ctx->r2 = MEM_W(ctx->r3, 0X0);
            goto L_80080850;
    }
    goto skip_4;
    // 0x80080834: lw          $v0, 0x0($v1)
    ctx->r2 = MEM_W(ctx->r3, 0X0);
    skip_4:
    // 0x80080838: lw          $v0, 0x0($v1)
    ctx->r2 = MEM_W(ctx->r3, 0X0);
    // 0x8008083C: lhu         $t2, 0xB50($v0)
    ctx->r10 = MEM_HU(ctx->r2, 0XB50);
    // 0x80080840: ori         $t3, $t2, 0xA000
    ctx->r11 = ctx->r10 | 0XA000;
    // 0x80080844: b           L_8008085C
    // 0x80080848: sh          $t3, 0xB50($v0)
    MEM_H(0XB50, ctx->r2) = ctx->r11;
        goto L_8008085C;
    // 0x80080848: sh          $t3, 0xB50($v0)
    MEM_H(0XB50, ctx->r2) = ctx->r11;
    // 0x8008084C: lw          $v0, 0x0($v1)
    ctx->r2 = MEM_W(ctx->r3, 0X0);
L_80080850:
    // 0x80080850: lhu         $t4, 0xB50($v0)
    ctx->r12 = MEM_HU(ctx->r2, 0XB50);
    // 0x80080854: andi        $t5, $t4, 0x5FFF
    ctx->r13 = ctx->r12 & 0X5FFF;
    // 0x80080858: sh          $t5, 0xB50($v0)
    MEM_H(0XB50, ctx->r2) = ctx->r13;
L_8008085C:
    // 0x8008085C: jr          $ra
    // 0x80080860: addiu       $sp, $sp, 0x8
    ctx->r29 = ADD32(ctx->r29, 0X8);
    return;
    // 0x80080860: addiu       $sp, $sp, 0x8
    ctx->r29 = ADD32(ctx->r29, 0X8);
;}
