#include "recomp.h"
#include "funcs.h"

RECOMP_FUNC void func_i5_802C5DC0(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C5DC0: addiu       $sp, $sp, -0x120
    ctx->r29 = ADD32(ctx->r29, -0X120);
    // 0x802C5DC4: lui         $t6, 0x801D
    ctx->r14 = S32(0X801D << 16);
    // 0x802C5DC8: lw          $t6, -0x19C0($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X19C0);
    // 0x802C5DCC: sw          $s6, 0x68($sp)
    MEM_W(0X68, ctx->r29) = ctx->r22;
    // 0x802C5DD0: or          $s6, $a0, $zero
    ctx->r22 = ctx->r4 | 0;
    // 0x802C5DD4: addiu       $t7, $t6, -0x4
    ctx->r15 = ADD32(ctx->r14, -0X4);
    // 0x802C5DD8: sltiu       $at, $t7, 0x5
    ctx->r1 = ctx->r15 < 0X5 ? 1 : 0;
    // 0x802C5DDC: sw          $ra, 0x74($sp)
    MEM_W(0X74, ctx->r29) = ctx->r31;
    // 0x802C5DE0: sw          $fp, 0x70($sp)
    MEM_W(0X70, ctx->r29) = ctx->r30;
    // 0x802C5DE4: sw          $s7, 0x6C($sp)
    MEM_W(0X6C, ctx->r29) = ctx->r23;
    // 0x802C5DE8: sw          $s5, 0x64($sp)
    MEM_W(0X64, ctx->r29) = ctx->r21;
    // 0x802C5DEC: sw          $s4, 0x60($sp)
    MEM_W(0X60, ctx->r29) = ctx->r20;
    // 0x802C5DF0: sw          $s3, 0x5C($sp)
    MEM_W(0X5C, ctx->r29) = ctx->r19;
    // 0x802C5DF4: sw          $s2, 0x58($sp)
    MEM_W(0X58, ctx->r29) = ctx->r18;
    // 0x802C5DF8: sw          $s1, 0x54($sp)
    MEM_W(0X54, ctx->r29) = ctx->r17;
    // 0x802C5DFC: beq         $at, $zero, L_802C5E30
    if (ctx->r1 == 0) {
        // 0x802C5E00: sw          $s0, 0x50($sp)
        MEM_W(0X50, ctx->r29) = ctx->r16;
            goto L_802C5E30;
    }
    // 0x802C5E00: sw          $s0, 0x50($sp)
    MEM_W(0X50, ctx->r29) = ctx->r16;
    // 0x802C5E04: sll         $t7, $t7, 2
    ctx->r15 = S32(ctx->r15 << 2);
    // 0x802C5E08: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C5E0C: addu        $at, $at, $t7
    gpr jr_addend_802C5E14 = ctx->r15;
    ctx->r1 = ADD32(ctx->r1, ctx->r15);
    // 0x802C5E10: lw          $t7, 0x7A60($at)
    ctx->r15 = ADD32(ctx->r1, 0X7A60);
    // 0x802C5E14: jr          $t7
    // 0x802C5E18: nop

    switch (jr_addend_802C5E14 >> 2) {
        case 0: goto L_802C5E1C; break;
        case 1: goto L_802C5E1C; break;
        case 2: goto L_802C5E1C; break;
        case 3: goto L_802C5E1C; break;
        case 4: goto L_802C5E1C; break;
        default: switch_error(__func__, 0x802C5E14, 0x802C7A60);
    }
    // 0x802C5E18: nop

L_802C5E1C:
    // 0x802C5E1C: addiu       $t8, $zero, 0x1
    ctx->r24 = ADD32(0, 0X1);
    // 0x802C5E20: sw          $t8, 0x114($sp)
    MEM_W(0X114, ctx->r29) = ctx->r24;
    // 0x802C5E24: addiu       $v1, $zero, 0xD
    ctx->r3 = ADD32(0, 0XD);
    // 0x802C5E28: b           L_802C5E3C
    // 0x802C5E2C: addiu       $t0, $zero, 0x15C
    ctx->r8 = ADD32(0, 0X15C);
        goto L_802C5E3C;
    // 0x802C5E2C: addiu       $t0, $zero, 0x15C
    ctx->r8 = ADD32(0, 0X15C);
L_802C5E30:
    // 0x802C5E30: sw          $zero, 0x114($sp)
    MEM_W(0X114, ctx->r29) = 0;
    // 0x802C5E34: addiu       $v1, $zero, 0x24
    ctx->r3 = ADD32(0, 0X24);
    // 0x802C5E38: addiu       $t0, $zero, 0x127
    ctx->r8 = ADD32(0, 0X127);
L_802C5E3C:
    // 0x802C5E3C: lw          $t9, 0x114($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X114);
    // 0x802C5E40: or          $v0, $s6, $zero
    ctx->r2 = ctx->r22 | 0;
    // 0x802C5E44: addiu       $a0, $s6, 0x8
    ctx->r4 = ADD32(ctx->r22, 0X8);
    // 0x802C5E48: bne         $t9, $zero, L_802C5E58
    if (ctx->r25 != 0) {
        // 0x802C5E4C: lui         $t1, 0x600
        ctx->r9 = S32(0X600 << 16);
            goto L_802C5E58;
    }
    // 0x802C5E4C: lui         $t1, 0x600
    ctx->r9 = S32(0X600 << 16);
    // 0x802C5E50: b           L_802C5E5C
    // 0x802C5E54: or          $s1, $zero, $zero
    ctx->r17 = 0 | 0;
        goto L_802C5E5C;
    // 0x802C5E54: or          $s1, $zero, $zero
    ctx->r17 = 0 | 0;
L_802C5E58:
    // 0x802C5E58: addiu       $s1, $zero, 0x2
    ctx->r17 = ADD32(0, 0X2);
L_802C5E5C:
    // 0x802C5E5C: lui         $t2, 0x107
    ctx->r10 = S32(0X107 << 16);
    // 0x802C5E60: addiu       $t2, $t2, -0x9D8
    ctx->r10 = ADD32(ctx->r10, -0X9D8);
    // 0x802C5E64: sw          $t2, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r10;
    // 0x802C5E68: sw          $t1, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r9;
    // 0x802C5E6C: lui         $t3, 0x802C
    ctx->r11 = S32(0X802C << 16);
    // 0x802C5E70: lh          $t3, 0x7A00($t3)
    ctx->r11 = MEM_H(ctx->r11, 0X7A00);
    // 0x802C5E74: addiu       $t4, $zero, 0x18
    ctx->r12 = ADD32(0, 0X18);
    // 0x802C5E78: sw          $t4, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r12;
    // 0x802C5E7C: addu        $a2, $t3, $v1
    ctx->r6 = ADD32(ctx->r11, ctx->r3);
    // 0x802C5E80: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x802C5E84: sw          $t0, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r8;
    // 0x802C5E88: or          $a1, $s1, $zero
    ctx->r5 = ctx->r17 | 0;
    // 0x802C5E8C: jal         0x80094338
    // 0x802C5E90: addiu       $a3, $zero, 0x19
    ctx->r7 = ADD32(0, 0X19);
    func_80094338(rdram, ctx);
        goto after_0;
    // 0x802C5E90: addiu       $a3, $zero, 0x19
    ctx->r7 = ADD32(0, 0X19);
    after_0:
    // 0x802C5E94: lui         $a2, 0x802C
    ctx->r6 = S32(0X802C << 16);
    // 0x802C5E98: lh          $a2, 0x7B04($a2)
    ctx->r6 = MEM_H(ctx->r6, 0X7B04);
    // 0x802C5E9C: addiu       $t5, $zero, 0x171
    ctx->r13 = ADD32(0, 0X171);
    // 0x802C5EA0: addiu       $t6, $zero, 0x10
    ctx->r14 = ADD32(0, 0X10);
    // 0x802C5EA4: sw          $t6, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r14;
    // 0x802C5EA8: sw          $t5, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r13;
    // 0x802C5EAC: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C5EB0: or          $a1, $s1, $zero
    ctx->r5 = ctx->r17 | 0;
    // 0x802C5EB4: addiu       $a3, $zero, 0x34
    ctx->r7 = ADD32(0, 0X34);
    // 0x802C5EB8: jal         0x80094338
    // 0x802C5EBC: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    func_80094338(rdram, ctx);
        goto after_1;
    // 0x802C5EBC: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    after_1:
    // 0x802C5EC0: lui         $a2, 0x802C
    ctx->r6 = S32(0X802C << 16);
    // 0x802C5EC4: lh          $a2, 0x7A00($a2)
    ctx->r6 = MEM_H(ctx->r6, 0X7A00);
    // 0x802C5EC8: addiu       $t7, $zero, 0x171
    ctx->r15 = ADD32(0, 0X171);
    // 0x802C5ECC: addiu       $t8, $zero, 0x10
    ctx->r24 = ADD32(0, 0X10);
    // 0x802C5ED0: sw          $t8, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r24;
    // 0x802C5ED4: sw          $t7, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r15;
    // 0x802C5ED8: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C5EDC: or          $a1, $s1, $zero
    ctx->r5 = ctx->r17 | 0;
    // 0x802C5EE0: addiu       $a3, $zero, 0xC7
    ctx->r7 = ADD32(0, 0XC7);
    // 0x802C5EE4: jal         0x80094338
    // 0x802C5EE8: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    func_80094338(rdram, ctx);
        goto after_2;
    // 0x802C5EE8: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    after_2:
    // 0x802C5EEC: or          $s6, $v0, $zero
    ctx->r22 = ctx->r2 | 0;
    // 0x802C5EF0: sw          $zero, 0x11C($sp)
    MEM_W(0X11C, ctx->r29) = 0;
    // 0x802C5EF4: addiu       $s0, $zero, 0x47
    ctx->r16 = ADD32(0, 0X47);
L_802C5EF8:
    // 0x802C5EF8: lw          $t9, 0x11C($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X11C);
    // 0x802C5EFC: or          $a0, $s6, $zero
    ctx->r4 = ctx->r22 | 0;
    // 0x802C5F00: or          $a1, $s1, $zero
    ctx->r5 = ctx->r17 | 0;
    // 0x802C5F04: andi        $t1, $t9, 0x1
    ctx->r9 = ctx->r25 & 0X1;
    // 0x802C5F08: beq         $t1, $zero, L_802C5F1C
    if (ctx->r9 == 0) {
        // 0x802C5F0C: or          $a3, $s0, $zero
        ctx->r7 = ctx->r16 | 0;
            goto L_802C5F1C;
    }
    // 0x802C5F0C: or          $a3, $s0, $zero
    ctx->r7 = ctx->r16 | 0;
    // 0x802C5F10: lui         $s7, 0x802C
    ctx->r23 = S32(0X802C << 16);
    // 0x802C5F14: b           L_802C5F24
    // 0x802C5F18: lh          $s7, 0x7B04($s7)
    ctx->r23 = MEM_H(ctx->r23, 0X7B04);
        goto L_802C5F24;
    // 0x802C5F18: lh          $s7, 0x7B04($s7)
    ctx->r23 = MEM_H(ctx->r23, 0X7B04);
L_802C5F1C:
    // 0x802C5F1C: lui         $s7, 0x802C
    ctx->r23 = S32(0X802C << 16);
    // 0x802C5F20: lh          $s7, 0x7A00($s7)
    ctx->r23 = MEM_H(ctx->r23, 0X7A00);
L_802C5F24:
    // 0x802C5F24: addiu       $t2, $zero, 0x171
    ctx->r10 = ADD32(0, 0X171);
    // 0x802C5F28: addiu       $t3, $zero, 0x1C
    ctx->r11 = ADD32(0, 0X1C);
    // 0x802C5F2C: sw          $t3, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r11;
    // 0x802C5F30: sw          $t2, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r10;
    // 0x802C5F34: jal         0x80094338
    // 0x802C5F38: addiu       $a2, $s7, 0x8
    ctx->r6 = ADD32(ctx->r23, 0X8);
    func_80094338(rdram, ctx);
        goto after_3;
    // 0x802C5F38: addiu       $a2, $s7, 0x8
    ctx->r6 = ADD32(ctx->r23, 0X8);
    after_3:
    // 0x802C5F3C: lw          $v1, 0x11C($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X11C);
    // 0x802C5F40: addiu       $s0, $s0, 0x20
    ctx->r16 = ADD32(ctx->r16, 0X20);
    // 0x802C5F44: or          $s6, $v0, $zero
    ctx->r22 = ctx->r2 | 0;
    // 0x802C5F48: addiu       $v1, $v1, 0x1
    ctx->r3 = ADD32(ctx->r3, 0X1);
    // 0x802C5F4C: slti        $at, $v1, 0x4
    ctx->r1 = SIGNED(ctx->r3) < 0X4 ? 1 : 0;
    // 0x802C5F50: bne         $at, $zero, L_802C5EF8
    if (ctx->r1 != 0) {
        // 0x802C5F54: sw          $v1, 0x11C($sp)
        MEM_W(0X11C, ctx->r29) = ctx->r3;
            goto L_802C5EF8;
    }
    // 0x802C5F54: sw          $v1, 0x11C($sp)
    MEM_W(0X11C, ctx->r29) = ctx->r3;
    // 0x802C5F58: addiu       $t4, $zero, 0xFF
    ctx->r12 = ADD32(0, 0XFF);
    // 0x802C5F5C: addiu       $t5, $zero, 0xFF
    ctx->r13 = ADD32(0, 0XFF);
    // 0x802C5F60: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C5F64: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C5F68: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C5F6C: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C5F70: addiu       $t1, $zero, 0xFF
    ctx->r9 = ADD32(0, 0XFF);
    // 0x802C5F74: addiu       $t2, $zero, 0xFF
    ctx->r10 = ADD32(0, 0XFF);
    // 0x802C5F78: addiu       $t3, $zero, 0xFF
    ctx->r11 = ADD32(0, 0XFF);
    // 0x802C5F7C: sw          $zero, 0xE8($sp)
    MEM_W(0XE8, ctx->r29) = 0;
    // 0x802C5F80: sw          $t3, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r11;
    // 0x802C5F84: sw          $t2, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r10;
    // 0x802C5F88: sw          $t1, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r9;
    // 0x802C5F8C: sw          $t9, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r25;
    // 0x802C5F90: sw          $t8, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r24;
    // 0x802C5F94: sw          $t7, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r15;
    // 0x802C5F98: sw          $t6, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r14;
    // 0x802C5F9C: sw          $t5, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r13;
    // 0x802C5FA0: sw          $t4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r12;
    // 0x802C5FA4: sw          $t4, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r12;
    // 0x802C5FA8: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C5FAC: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C5FB0: addiu       $a2, $zero, 0xFF
    ctx->r6 = ADD32(0, 0XFF);
    // 0x802C5FB4: jal         0x801E946C
    // 0x802C5FB8: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    func_801E946C(rdram, ctx);
        goto after_4;
    // 0x802C5FB8: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    after_4:
    // 0x802C5FBC: lw          $t5, 0x114($sp)
    ctx->r13 = MEM_W(ctx->r29, 0X114);
    // 0x802C5FC0: or          $s6, $v0, $zero
    ctx->r22 = ctx->r2 | 0;
    // 0x802C5FC4: or          $a0, $s6, $zero
    ctx->r4 = ctx->r22 | 0;
    // 0x802C5FC8: bne         $t5, $zero, L_802C6028
    if (ctx->r13 != 0) {
        // 0x802C5FCC: addiu       $a1, $zero, 0x2
        ctx->r5 = ADD32(0, 0X2);
            goto L_802C6028;
    }
    // 0x802C5FCC: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C5FD0: lui         $a3, 0x802C
    ctx->r7 = S32(0X802C << 16);
    // 0x802C5FD4: lh          $a3, 0x7A00($a3)
    ctx->r7 = MEM_H(ctx->r7, 0X7A00);
    // 0x802C5FD8: addiu       $t6, $zero, 0x1C
    ctx->r14 = ADD32(0, 0X1C);
    // 0x802C5FDC: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x802C5FE0: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C5FE4: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C5FE8: addiu       $a2, $zero, 0x14
    ctx->r6 = ADD32(0, 0X14);
    // 0x802C5FEC: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    // 0x802C5FF0: jal         0x801E3EE0
    // 0x802C5FF4: addiu       $a3, $a3, 0x69
    ctx->r7 = ADD32(ctx->r7, 0X69);
    func_801E3EE0(rdram, ctx);
        goto after_5;
    // 0x802C5FF4: addiu       $a3, $a3, 0x69
    ctx->r7 = ADD32(ctx->r7, 0X69);
    after_5:
    // 0x802C5FF8: lui         $a3, 0x802C
    ctx->r7 = S32(0X802C << 16);
    // 0x802C5FFC: lh          $a3, 0x7A00($a3)
    ctx->r7 = MEM_H(ctx->r7, 0X7A00);
    // 0x802C6000: addiu       $t7, $zero, 0xCA
    ctx->r15 = ADD32(0, 0XCA);
    // 0x802C6004: sw          $t7, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r15;
    // 0x802C6008: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C600C: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C6010: addiu       $a2, $zero, 0x4F
    ctx->r6 = ADD32(0, 0X4F);
    // 0x802C6014: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    // 0x802C6018: jal         0x801E3EE0
    // 0x802C601C: addiu       $a3, $a3, 0x18
    ctx->r7 = ADD32(ctx->r7, 0X18);
    func_801E3EE0(rdram, ctx);
        goto after_6;
    // 0x802C601C: addiu       $a3, $a3, 0x18
    ctx->r7 = ADD32(ctx->r7, 0X18);
    after_6:
    // 0x802C6020: b           L_802C6074
    // 0x802C6024: or          $s6, $v0, $zero
    ctx->r22 = ctx->r2 | 0;
        goto L_802C6074;
    // 0x802C6024: or          $s6, $v0, $zero
    ctx->r22 = ctx->r2 | 0;
L_802C6028:
    // 0x802C6028: lui         $a3, 0x802C
    ctx->r7 = S32(0X802C << 16);
    // 0x802C602C: lh          $a3, 0x7A00($a3)
    ctx->r7 = MEM_H(ctx->r7, 0X7A00);
    // 0x802C6030: addiu       $t8, $zero, 0x1C
    ctx->r24 = ADD32(0, 0X1C);
    // 0x802C6034: sw          $t8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r24;
    // 0x802C6038: addiu       $a2, $zero, 0x15
    ctx->r6 = ADD32(0, 0X15);
    // 0x802C603C: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    // 0x802C6040: jal         0x801E3EE0
    // 0x802C6044: addiu       $a3, $a3, 0x5D
    ctx->r7 = ADD32(ctx->r7, 0X5D);
    func_801E3EE0(rdram, ctx);
        goto after_7;
    // 0x802C6044: addiu       $a3, $a3, 0x5D
    ctx->r7 = ADD32(ctx->r7, 0X5D);
    after_7:
    // 0x802C6048: lui         $a3, 0x802C
    ctx->r7 = S32(0X802C << 16);
    // 0x802C604C: lh          $a3, 0x7A00($a3)
    ctx->r7 = MEM_H(ctx->r7, 0X7A00);
    // 0x802C6050: addiu       $t9, $zero, 0xCA
    ctx->r25 = ADD32(0, 0XCA);
    // 0x802C6054: sw          $t9, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r25;
    // 0x802C6058: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C605C: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C6060: addiu       $a2, $zero, 0x6
    ctx->r6 = ADD32(0, 0X6);
    // 0x802C6064: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    // 0x802C6068: jal         0x801E3EE0
    // 0x802C606C: addiu       $a3, $a3, 0x18
    ctx->r7 = ADD32(ctx->r7, 0X18);
    func_801E3EE0(rdram, ctx);
        goto after_8;
    // 0x802C606C: addiu       $a3, $a3, 0x18
    ctx->r7 = ADD32(ctx->r7, 0X18);
    after_8:
    // 0x802C6070: or          $s6, $v0, $zero
    ctx->r22 = ctx->r2 | 0;
L_802C6074:
    // 0x802C6074: lui         $a3, 0x802C
    ctx->r7 = S32(0X802C << 16);
    // 0x802C6078: lh          $a3, 0x7B04($a3)
    ctx->r7 = MEM_H(ctx->r7, 0X7B04);
    // 0x802C607C: addiu       $t1, $zero, 0x37
    ctx->r9 = ADD32(0, 0X37);
    // 0x802C6080: sw          $t1, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r9;
    // 0x802C6084: or          $a0, $s6, $zero
    ctx->r4 = ctx->r22 | 0;
    // 0x802C6088: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C608C: addiu       $a2, $zero, 0x1F
    ctx->r6 = ADD32(0, 0X1F);
    // 0x802C6090: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    // 0x802C6094: jal         0x801E3EE0
    // 0x802C6098: addiu       $a3, $a3, 0xD
    ctx->r7 = ADD32(ctx->r7, 0XD);
    func_801E3EE0(rdram, ctx);
        goto after_9;
    // 0x802C6098: addiu       $a3, $a3, 0xD
    ctx->r7 = ADD32(ctx->r7, 0XD);
    after_9:
    // 0x802C609C: lui         $a3, 0x802C
    ctx->r7 = S32(0X802C << 16);
    // 0x802C60A0: lh          $a3, 0x7B04($a3)
    ctx->r7 = MEM_H(ctx->r7, 0X7B04);
    // 0x802C60A4: addiu       $t2, $zero, 0x37
    ctx->r10 = ADD32(0, 0X37);
    // 0x802C60A8: sw          $t2, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r10;
    // 0x802C60AC: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C60B0: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C60B4: addiu       $a2, $zero, 0x20
    ctx->r6 = ADD32(0, 0X20);
    // 0x802C60B8: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    // 0x802C60BC: jal         0x801E3EE0
    // 0x802C60C0: addiu       $a3, $a3, 0xA1
    ctx->r7 = ADD32(ctx->r7, 0XA1);
    func_801E3EE0(rdram, ctx);
        goto after_10;
    // 0x802C60C0: addiu       $a3, $a3, 0xA1
    ctx->r7 = ADD32(ctx->r7, 0XA1);
    after_10:
    // 0x802C60C4: lui         $a3, 0x802C
    ctx->r7 = S32(0X802C << 16);
    // 0x802C60C8: lh          $a3, 0x7B04($a3)
    ctx->r7 = MEM_H(ctx->r7, 0X7B04);
    // 0x802C60CC: addiu       $t3, $zero, 0x37
    ctx->r11 = ADD32(0, 0X37);
    // 0x802C60D0: sw          $t3, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r11;
    // 0x802C60D4: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C60D8: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C60DC: addiu       $a2, $zero, 0x3A
    ctx->r6 = ADD32(0, 0X3A);
    // 0x802C60E0: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    // 0x802C60E4: jal         0x801E3EE0
    // 0x802C60E8: addiu       $a3, $a3, 0x13F
    ctx->r7 = ADD32(ctx->r7, 0X13F);
    func_801E3EE0(rdram, ctx);
        goto after_11;
    // 0x802C60E8: addiu       $a3, $a3, 0x13F
    ctx->r7 = ADD32(ctx->r7, 0X13F);
    after_11:
    // 0x802C60EC: addiu       $t4, $zero, 0xFF
    ctx->r12 = ADD32(0, 0XFF);
    // 0x802C60F0: sw          $t4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r12;
    // 0x802C60F4: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C60F8: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C60FC: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x802C6100: jal         0x801E7E74
    // 0x802C6104: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_801E7E74(rdram, ctx);
        goto after_12;
    // 0x802C6104: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_12:
    // 0x802C6108: or          $s6, $v0, $zero
    ctx->r22 = ctx->r2 | 0;
    // 0x802C610C: sw          $zero, 0x11C($sp)
    MEM_W(0X11C, ctx->r29) = 0;
    // 0x802C6110: addiu       $s0, $zero, 0x4A
    ctx->r16 = ADD32(0, 0X4A);
    // 0x802C6114: addiu       $s1, $zero, 0x5F
    ctx->r17 = ADD32(0, 0X5F);
L_802C6118:
    // 0x802C6118: lw          $t5, 0x11C($sp)
    ctx->r13 = MEM_W(ctx->r29, 0X11C);
    // 0x802C611C: lui         $s7, 0x802C
    ctx->r23 = S32(0X802C << 16);
    // 0x802C6120: or          $a0, $s6, $zero
    ctx->r4 = ctx->r22 | 0;
    // 0x802C6124: andi        $t6, $t5, 0x1
    ctx->r14 = ctx->r13 & 0X1;
    // 0x802C6128: beq         $t6, $zero, L_802C613C
    if (ctx->r14 == 0) {
        // 0x802C612C: or          $a2, $s0, $zero
        ctx->r6 = ctx->r16 | 0;
            goto L_802C613C;
    }
    // 0x802C612C: or          $a2, $s0, $zero
    ctx->r6 = ctx->r16 | 0;
    // 0x802C6130: lui         $s7, 0x802C
    ctx->r23 = S32(0X802C << 16);
    // 0x802C6134: b           L_802C6140
    // 0x802C6138: lh          $s7, 0x7B04($s7)
    ctx->r23 = MEM_H(ctx->r23, 0X7B04);
        goto L_802C6140;
    // 0x802C6138: lh          $s7, 0x7B04($s7)
    ctx->r23 = MEM_H(ctx->r23, 0X7B04);
L_802C613C:
    // 0x802C613C: lh          $s7, 0x7A00($s7)
    ctx->r23 = MEM_H(ctx->r23, 0X7A00);
L_802C6140:
    // 0x802C6140: addiu       $a1, $s7, 0x2A
    ctx->r5 = ADD32(ctx->r23, 0X2A);
    // 0x802C6144: addiu       $a3, $s7, 0x56
    ctx->r7 = ADD32(ctx->r23, 0X56);
    // 0x802C6148: jal         0x801E7FD8
    // 0x802C614C: sw          $s1, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r17;
    func_801E7FD8(rdram, ctx);
        goto after_13;
    // 0x802C614C: sw          $s1, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r17;
    after_13:
    // 0x802C6150: lw          $v1, 0x11C($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X11C);
    // 0x802C6154: addiu       $s0, $s0, 0x20
    ctx->r16 = ADD32(ctx->r16, 0X20);
    // 0x802C6158: addiu       $s1, $s1, 0x20
    ctx->r17 = ADD32(ctx->r17, 0X20);
    // 0x802C615C: addiu       $v1, $v1, 0x1
    ctx->r3 = ADD32(ctx->r3, 0X1);
    // 0x802C6160: slti        $at, $v1, 0x4
    ctx->r1 = SIGNED(ctx->r3) < 0X4 ? 1 : 0;
    // 0x802C6164: sw          $v1, 0x11C($sp)
    MEM_W(0X11C, ctx->r29) = ctx->r3;
    // 0x802C6168: bne         $at, $zero, L_802C6118
    if (ctx->r1 != 0) {
        // 0x802C616C: or          $s6, $v0, $zero
        ctx->r22 = ctx->r2 | 0;
            goto L_802C6118;
    }
    // 0x802C616C: or          $s6, $v0, $zero
    ctx->r22 = ctx->r2 | 0;
    // 0x802C6170: addiu       $s6, $v0, 0x8
    ctx->r22 = ADD32(ctx->r2, 0X8);
    // 0x802C6174: lui         $t7, 0xE700
    ctx->r15 = S32(0XE700 << 16);
    // 0x802C6178: sw          $t7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r15;
    // 0x802C617C: sw          $zero, 0x4($v0)
    MEM_W(0X4, ctx->r2) = 0;
    // 0x802C6180: or          $a0, $s6, $zero
    ctx->r4 = ctx->r22 | 0;
    // 0x802C6184: lui         $t8, 0xED02
    ctx->r24 = S32(0XED02 << 16);
    // 0x802C6188: addiu       $t8, $t8, 0x50
    ctx->r24 = ADD32(ctx->r24, 0X50);
    // 0x802C618C: lui         $t9, 0x68
    ctx->r25 = S32(0X68 << 16);
    // 0x802C6190: addiu       $t9, $t9, -0x3C94
    ctx->r25 = ADD32(ctx->r25, -0X3C94);
    { extern uint32_t wr64_experimental_viewport_borders(void); if (wr64_experimental_viewport_borders()) { ctx->r24 = 0xED000000U; ctx->r25 = 0x006A03C0U; } }
    // 0x802C6194: sw          $t8, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r24;
    // 0x802C6198: sw          $t9, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r25;
    // 0x802C619C: addiu       $t1, $zero, 0x1
    ctx->r9 = ADD32(0, 0X1);
    // 0x802C61A0: addiu       $t2, $zero, 0x1
    ctx->r10 = ADD32(0, 0X1);
    // 0x802C61A4: addiu       $t3, $zero, 0x1
    ctx->r11 = ADD32(0, 0X1);
    // 0x802C61A8: addiu       $t4, $zero, 0x4B
    ctx->r12 = ADD32(0, 0X4B);
    // 0x802C61AC: addiu       $s6, $s6, 0x8
    ctx->r22 = ADD32(ctx->r22, 0X8);
    // 0x802C61B0: sw          $t3, 0xFC($sp)
    MEM_W(0XFC, ctx->r29) = ctx->r11;
    // 0x802C61B4: sw          $t2, 0x104($sp)
    MEM_W(0X104, ctx->r29) = ctx->r10;
    // 0x802C61B8: sw          $t1, 0x100($sp)
    MEM_W(0X100, ctx->r29) = ctx->r9;
    // 0x802C61BC: sw          $t4, 0x84($sp)
    MEM_W(0X84, ctx->r29) = ctx->r12;
    // 0x802C61C0: sw          $zero, 0x90($sp)
    MEM_W(0X90, ctx->r29) = 0;
    // 0x802C61C4: sw          $zero, 0x11C($sp)
    MEM_W(0X11C, ctx->r29) = 0;
    // 0x802C61C8: addiu       $fp, $zero, 0x58
    ctx->r30 = ADD32(0, 0X58);
    // 0x802C61CC: addiu       $s5, $sp, 0xB8
    ctx->r21 = ADD32(ctx->r29, 0XB8);
L_802C61D0:
    // 0x802C61D0: lw          $t5, 0x11C($sp)
    ctx->r13 = MEM_W(ctx->r29, 0X11C);
    // 0x802C61D4: lui         $s7, 0x802C
    ctx->r23 = S32(0X802C << 16);
    // 0x802C61D8: lw          $t7, 0x114($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X114);
    // 0x802C61DC: andi        $t6, $t5, 0x1
    ctx->r14 = ctx->r13 & 0X1;
    // 0x802C61E0: beq         $t6, $zero, L_802C61F4
    if (ctx->r14 == 0) {
        // 0x802C61E4: lw          $t5, 0x90($sp)
        ctx->r13 = MEM_W(ctx->r29, 0X90);
            goto L_802C61F4;
    }
    // 0x802C61E4: lw          $t5, 0x90($sp)
    ctx->r13 = MEM_W(ctx->r29, 0X90);
    // 0x802C61E8: lui         $s7, 0x802C
    ctx->r23 = S32(0X802C << 16);
    // 0x802C61EC: b           L_802C61F8
    // 0x802C61F0: lh          $s7, 0x7B04($s7)
    ctx->r23 = MEM_H(ctx->r23, 0X7B04);
        goto L_802C61F8;
    // 0x802C61F0: lh          $s7, 0x7B04($s7)
    ctx->r23 = MEM_H(ctx->r23, 0X7B04);
L_802C61F4:
    // 0x802C61F4: lh          $s7, 0x7A00($s7)
    ctx->r23 = MEM_H(ctx->r23, 0X7A00);
L_802C61F8:
    // 0x802C61F8: bne         $t7, $zero, L_802C636C
    if (ctx->r15 != 0) {
        // 0x802C61FC: lw          $t6, 0x11C($sp)
        ctx->r14 = MEM_W(ctx->r29, 0X11C);
            goto L_802C636C;
    }
    // 0x802C61FC: lw          $t6, 0x11C($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X11C);
    // 0x802C6200: lw          $t1, 0x11C($sp)
    ctx->r9 = MEM_W(ctx->r29, 0X11C);
    // 0x802C6204: lw          $t8, 0x90($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X90);
    // 0x802C6208: lui         $t9, 0x801D
    ctx->r25 = S32(0X801D << 16);
    // 0x802C620C: addiu       $t9, $t9, -0x18E8
    ctx->r25 = ADD32(ctx->r25, -0X18E8);
    // 0x802C6210: beq         $t1, $zero, L_802C6278
    if (ctx->r9 == 0) {
        // 0x802C6214: addu        $s0, $t8, $t9
        ctx->r16 = ADD32(ctx->r24, ctx->r25);
            goto L_802C6278;
    }
    // 0x802C6214: addu        $s0, $t8, $t9
    ctx->r16 = ADD32(ctx->r24, ctx->r25);
    // 0x802C6218: lw          $t2, 0x104($sp)
    ctx->r10 = MEM_W(ctx->r29, 0X104);
    // 0x802C621C: lui         $t4, 0x801D
    ctx->r12 = S32(0X801D << 16);
    // 0x802C6220: lw          $t4, -0x4CCC($t4)
    ctx->r12 = MEM_W(ctx->r12, -0X4CCC);
    // 0x802C6224: addiu       $t3, $t2, 0x1
    ctx->r11 = ADD32(ctx->r10, 0X1);
    // 0x802C6228: lw          $t2, -0x4($s0)
    ctx->r10 = MEM_W(ctx->r16, -0X4);
    // 0x802C622C: lw          $t7, 0x0($s0)
    ctx->r15 = MEM_W(ctx->r16, 0X0);
    // 0x802C6230: lui         $t6, 0x801D
    ctx->r14 = S32(0X801D << 16);
    // 0x802C6234: addiu       $t6, $t6, -0x4CB0
    ctx->r14 = ADD32(ctx->r14, -0X4CB0);
    // 0x802C6238: sll         $t5, $t4, 4
    ctx->r13 = S32(ctx->r12 << 4);
    // 0x802C623C: addu        $v0, $t5, $t6
    ctx->r2 = ADD32(ctx->r13, ctx->r14);
    // 0x802C6240: sll         $t4, $t2, 2
    ctx->r12 = S32(ctx->r10 << 2);
    // 0x802C6244: sll         $t8, $t7, 2
    ctx->r24 = S32(ctx->r15 << 2);
    // 0x802C6248: addu        $t9, $v0, $t8
    ctx->r25 = ADD32(ctx->r2, ctx->r24);
    // 0x802C624C: addu        $t5, $v0, $t4
    ctx->r13 = ADD32(ctx->r2, ctx->r12);
    // 0x802C6250: lw          $t6, 0x0($t5)
    ctx->r14 = MEM_W(ctx->r13, 0X0);
    // 0x802C6254: lw          $t1, 0x0($t9)
    ctx->r9 = MEM_W(ctx->r25, 0X0);
    // 0x802C6258: sw          $t3, 0x104($sp)
    MEM_W(0X104, ctx->r29) = ctx->r11;
    // 0x802C625C: lw          $t7, 0x100($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X100);
    // 0x802C6260: beql        $t1, $t6, L_802C6278
    if (ctx->r9 == ctx->r14) {
        // 0x802C6264: sw          $t7, 0xFC($sp)
        MEM_W(0XFC, ctx->r29) = ctx->r15;
            goto L_802C6278;
    }
    goto skip_0;
    // 0x802C6264: sw          $t7, 0xFC($sp)
    MEM_W(0XFC, ctx->r29) = ctx->r15;
    skip_0:
    // 0x802C6268: sw          $t3, 0x100($sp)
    MEM_W(0X100, ctx->r29) = ctx->r11;
    // 0x802C626C: b           L_802C6278
    // 0x802C6270: sw          $t3, 0xFC($sp)
    MEM_W(0XFC, ctx->r29) = ctx->r11;
        goto L_802C6278;
    // 0x802C6270: sw          $t3, 0xFC($sp)
    MEM_W(0XFC, ctx->r29) = ctx->r11;
    // 0x802C6274: sw          $t7, 0xFC($sp)
    MEM_W(0XFC, ctx->r29) = ctx->r15;
L_802C6278:
    // 0x802C6278: lw          $t8, 0x0($s0)
    ctx->r24 = MEM_W(ctx->r16, 0X0);
    // 0x802C627C: lui         $t2, 0x801C
    ctx->r10 = S32(0X801C << 16);
    // 0x802C6280: lui         $a1, 0x802C
    ctx->r5 = S32(0X802C << 16);
    // 0x802C6284: sll         $t9, $t8, 3
    ctx->r25 = S32(ctx->r24 << 3);
    // 0x802C6288: subu        $t9, $t9, $t8
    ctx->r25 = SUB32(ctx->r25, ctx->r24);
    // 0x802C628C: sll         $t9, $t9, 4
    ctx->r25 = S32(ctx->r25 << 4);
    // 0x802C6290: subu        $t9, $t9, $t8
    ctx->r25 = SUB32(ctx->r25, ctx->r24);
    // 0x802C6294: sll         $t9, $t9, 3
    ctx->r25 = S32(ctx->r25 << 3);
    // 0x802C6298: addu        $t2, $t2, $t9
    ctx->r10 = ADD32(ctx->r10, ctx->r25);
    // 0x802C629C: lw          $t2, 0x2C24($t2)
    ctx->r10 = MEM_W(ctx->r10, 0X2C24);
    // 0x802C62A0: addiu       $t4, $zero, 0x6
    ctx->r12 = ADD32(0, 0X6);
    // 0x802C62A4: addiu       $a1, $a1, 0x7A48
    ctx->r5 = ADD32(ctx->r5, 0X7A48);
    // 0x802C62A8: beq         $t2, $zero, L_802C62D4
    if (ctx->r10 == 0) {
        // 0x802C62AC: addiu       $a0, $sp, 0xC4
        ctx->r4 = ADD32(ctx->r29, 0XC4);
            goto L_802C62D4;
    }
    // 0x802C62AC: addiu       $a0, $sp, 0xC4
    ctx->r4 = ADD32(ctx->r29, 0XC4);
    // 0x802C62B0: lui         $a1, 0x802C
    ctx->r5 = S32(0X802C << 16);
    // 0x802C62B4: lui         $a2, 0x802C
    ctx->r6 = S32(0X802C << 16);
    // 0x802C62B8: sw          $t4, 0xE8($sp)
    MEM_W(0XE8, ctx->r29) = ctx->r12;
    // 0x802C62BC: addiu       $a2, $a2, 0x7A44
    ctx->r6 = ADD32(ctx->r6, 0X7A44);
    // 0x802C62C0: addiu       $a1, $a1, 0x7A40
    ctx->r5 = ADD32(ctx->r5, 0X7A40);
    // 0x802C62C4: jal         0x800CA210
    // 0x802C62C8: addiu       $a0, $sp, 0xC4
    ctx->r4 = ADD32(ctx->r29, 0XC4);
    func_800CA210(rdram, ctx);
        goto after_14;
    // 0x802C62C8: addiu       $a0, $sp, 0xC4
    ctx->r4 = ADD32(ctx->r29, 0XC4);
    after_14:
    // 0x802C62CC: b           L_802C62E0
    // 0x802C62D0: lw          $v0, 0x0($s0)
    ctx->r2 = MEM_W(ctx->r16, 0X0);
        goto L_802C62E0;
    // 0x802C62D0: lw          $v0, 0x0($s0)
    ctx->r2 = MEM_W(ctx->r16, 0X0);
L_802C62D4:
    // 0x802C62D4: jal         0x800CA210
    // 0x802C62D8: lw          $a2, 0x104($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X104);
    func_800CA210(rdram, ctx);
        goto after_15;
    // 0x802C62D8: lw          $a2, 0x104($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X104);
    after_15:
    // 0x802C62DC: lw          $v0, 0x0($s0)
    ctx->r2 = MEM_W(ctx->r16, 0X0);
L_802C62E0:
    // 0x802C62E0: lui         $t5, 0x800E
    ctx->r13 = S32(0X800E << 16);
    // 0x802C62E4: lui         $t7, 0x801D
    ctx->r15 = S32(0X801D << 16);
    // 0x802C62E8: sll         $v1, $v0, 2
    ctx->r3 = S32(ctx->r2 << 2);
    // 0x802C62EC: addu        $t5, $t5, $v1
    ctx->r13 = ADD32(ctx->r13, ctx->r3);
    // 0x802C62F0: lw          $t5, -0x5650($t5)
    ctx->r13 = MEM_W(ctx->r13, -0X5650);
    // 0x802C62F4: lw          $t7, -0x4CCC($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X4CCC);
    // 0x802C62F8: lui         $t2, 0x800D
    ctx->r10 = S32(0X800D << 16);
    // 0x802C62FC: sll         $t1, $t5, 3
    ctx->r9 = S32(ctx->r13 << 3);
    // 0x802C6300: lw          $t2, 0x48DC($t2)
    ctx->r10 = MEM_W(ctx->r10, 0X48DC);
    // 0x802C6304: lui         $t6, 0x801D
    ctx->r14 = S32(0X801D << 16);
    // 0x802C6308: subu        $t1, $t1, $t5
    ctx->r9 = SUB32(ctx->r9, ctx->r13);
    // 0x802C630C: sll         $t8, $t7, 4
    ctx->r24 = S32(ctx->r15 << 4);
    // 0x802C6310: sll         $t1, $t1, 1
    ctx->r9 = S32(ctx->r9 << 1);
    // 0x802C6314: addiu       $t6, $t6, -0x4D68
    ctx->r14 = ADD32(ctx->r14, -0X4D68);
    // 0x802C6318: addu        $t9, $t8, $v1
    ctx->r25 = ADD32(ctx->r24, ctx->r3);
    // 0x802C631C: lui         $a2, 0x801D
    ctx->r6 = S32(0X801D << 16);
    // 0x802C6320: addu        $t3, $t1, $t6
    ctx->r11 = ADD32(ctx->r9, ctx->r14);
    // 0x802C6324: addu        $a2, $a2, $t9
    ctx->r6 = ADD32(ctx->r6, ctx->r25);
    // 0x802C6328: sw          $t3, 0xD0($sp)
    MEM_W(0XD0, ctx->r29) = ctx->r11;
    // 0x802C632C: beq         $t2, $v0, L_802C6344
    if (ctx->r10 == ctx->r2) {
        // 0x802C6330: lw          $a2, -0x4CB0($a2)
        ctx->r6 = MEM_W(ctx->r6, -0X4CB0);
            goto L_802C6344;
    }
    // 0x802C6330: lw          $a2, -0x4CB0($a2)
    ctx->r6 = MEM_W(ctx->r6, -0X4CB0);
    // 0x802C6334: or          $s2, $zero, $zero
    ctx->r18 = 0 | 0;
    // 0x802C6338: or          $s3, $zero, $zero
    ctx->r19 = 0 | 0;
    // 0x802C633C: b           L_802C6498
    // 0x802C6340: or          $s4, $zero, $zero
    ctx->r20 = 0 | 0;
        goto L_802C6498;
    // 0x802C6340: or          $s4, $zero, $zero
    ctx->r20 = 0 | 0;
L_802C6344:
    // 0x802C6344: lui         $t4, 0x801C
    ctx->r12 = S32(0X801C << 16);
    // 0x802C6348: lw          $t4, 0x2650($t4)
    ctx->r12 = MEM_W(ctx->r12, 0X2650);
    // 0x802C634C: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x802C6350: addiu       $s2, $zero, 0x6
    ctx->r18 = ADD32(0, 0X6);
    // 0x802C6354: beq         $t4, $at, L_802C6364
    if (ctx->r12 == ctx->r1) {
        // 0x802C6358: addiu       $s4, $zero, 0x6
        ctx->r20 = ADD32(0, 0X6);
            goto L_802C6364;
    }
    // 0x802C6358: addiu       $s4, $zero, 0x6
    ctx->r20 = ADD32(0, 0X6);
    // 0x802C635C: b           L_802C6498
    // 0x802C6360: addiu       $s3, $zero, 0x6
    ctx->r19 = ADD32(0, 0X6);
        goto L_802C6498;
    // 0x802C6360: addiu       $s3, $zero, 0x6
    ctx->r19 = ADD32(0, 0X6);
L_802C6364:
    // 0x802C6364: b           L_802C6498
    // 0x802C6368: addiu       $s3, $zero, 0x4
    ctx->r19 = ADD32(0, 0X4);
        goto L_802C6498;
    // 0x802C6368: addiu       $s3, $zero, 0x4
    ctx->r19 = ADD32(0, 0X4);
L_802C636C:
    // 0x802C636C: lui         $t1, 0x800E
    ctx->r9 = S32(0X800E << 16);
    // 0x802C6370: addiu       $t1, $t1, -0x5624
    ctx->r9 = ADD32(ctx->r9, -0X5624);
    // 0x802C6374: beq         $t6, $zero, L_802C63CC
    if (ctx->r14 == 0) {
        // 0x802C6378: addu        $s3, $t5, $t1
        ctx->r19 = ADD32(ctx->r13, ctx->r9);
            goto L_802C63CC;
    }
    // 0x802C6378: addu        $s3, $t5, $t1
    ctx->r19 = ADD32(ctx->r13, ctx->r9);
    // 0x802C637C: lw          $t8, 0x0($s3)
    ctx->r24 = MEM_W(ctx->r19, 0X0);
    // 0x802C6380: lw          $t5, -0x4($s3)
    ctx->r13 = MEM_W(ctx->r19, -0X4);
    // 0x802C6384: lw          $t3, 0x104($sp)
    ctx->r11 = MEM_W(ctx->r29, 0X104);
    // 0x802C6388: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x802C638C: addiu       $v0, $v0, -0x4CC0
    ctx->r2 = ADD32(ctx->r2, -0X4CC0);
    // 0x802C6390: sll         $t9, $t8, 2
    ctx->r25 = S32(ctx->r24 << 2);
    // 0x802C6394: sll         $t1, $t5, 2
    ctx->r9 = S32(ctx->r13 << 2);
    // 0x802C6398: addu        $t6, $v0, $t1
    ctx->r14 = ADD32(ctx->r2, ctx->r9);
    // 0x802C639C: addu        $t2, $v0, $t9
    ctx->r10 = ADD32(ctx->r2, ctx->r25);
    // 0x802C63A0: addiu       $t7, $t3, 0x1
    ctx->r15 = ADD32(ctx->r11, 0X1);
    // 0x802C63A4: lw          $t3, 0x0($t6)
    ctx->r11 = MEM_W(ctx->r14, 0X0);
    // 0x802C63A8: lw          $t4, 0x0($t2)
    ctx->r12 = MEM_W(ctx->r10, 0X0);
    // 0x802C63AC: sw          $t7, 0x104($sp)
    MEM_W(0X104, ctx->r29) = ctx->r15;
    // 0x802C63B0: lw          $t8, 0x100($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X100);
    // 0x802C63B4: beql        $t4, $t3, L_802C63CC
    if (ctx->r12 == ctx->r11) {
        // 0x802C63B8: sw          $t8, 0xFC($sp)
        MEM_W(0XFC, ctx->r29) = ctx->r24;
            goto L_802C63CC;
    }
    goto skip_1;
    // 0x802C63B8: sw          $t8, 0xFC($sp)
    MEM_W(0XFC, ctx->r29) = ctx->r24;
    skip_1:
    // 0x802C63BC: sw          $t7, 0x100($sp)
    MEM_W(0X100, ctx->r29) = ctx->r15;
    // 0x802C63C0: b           L_802C63CC
    // 0x802C63C4: sw          $t7, 0xFC($sp)
    MEM_W(0XFC, ctx->r29) = ctx->r15;
        goto L_802C63CC;
    // 0x802C63C4: sw          $t7, 0xFC($sp)
    MEM_W(0XFC, ctx->r29) = ctx->r15;
    // 0x802C63C8: sw          $t8, 0xFC($sp)
    MEM_W(0XFC, ctx->r29) = ctx->r24;
L_802C63CC:
    // 0x802C63CC: lui         $a1, 0x802C
    ctx->r5 = S32(0X802C << 16);
    // 0x802C63D0: addiu       $a1, $a1, 0x7A4C
    ctx->r5 = ADD32(ctx->r5, 0X7A4C);
    // 0x802C63D4: addiu       $a0, $sp, 0xC4
    ctx->r4 = ADD32(ctx->r29, 0XC4);
    // 0x802C63D8: jal         0x800CA210
    // 0x802C63DC: lw          $a2, 0xFC($sp)
    ctx->r6 = MEM_W(ctx->r29, 0XFC);
    func_800CA210(rdram, ctx);
        goto after_16;
    // 0x802C63DC: lw          $a2, 0xFC($sp)
    ctx->r6 = MEM_W(ctx->r29, 0XFC);
    after_16:
    // 0x802C63E0: lw          $a0, 0x0($s3)
    ctx->r4 = MEM_W(ctx->r19, 0X0);
    // 0x802C63E4: lui         $t9, 0x800E
    ctx->r25 = S32(0X800E << 16);
    // 0x802C63E8: lui         $a1, 0x800D
    ctx->r5 = S32(0X800D << 16);
    // 0x802C63EC: sll         $v1, $a0, 2
    ctx->r3 = S32(ctx->r4 << 2);
    // 0x802C63F0: addu        $t9, $t9, $v1
    ctx->r25 = ADD32(ctx->r25, ctx->r3);
    // 0x802C63F4: lw          $t9, -0x5650($t9)
    ctx->r25 = MEM_W(ctx->r25, -0X5650);
    // 0x802C63F8: lw          $a1, 0x48DC($a1)
    ctx->r5 = MEM_W(ctx->r5, 0X48DC);
    // 0x802C63FC: lui         $t5, 0x801D
    ctx->r13 = S32(0X801D << 16);
    // 0x802C6400: sll         $t2, $t9, 3
    ctx->r10 = S32(ctx->r25 << 3);
    // 0x802C6404: subu        $t2, $t2, $t9
    ctx->r10 = SUB32(ctx->r10, ctx->r25);
    // 0x802C6408: sll         $t2, $t2, 1
    ctx->r10 = S32(ctx->r10 << 1);
    // 0x802C640C: addiu       $t5, $t5, -0x4D68
    ctx->r13 = ADD32(ctx->r13, -0X4D68);
    // 0x802C6410: lui         $a2, 0x801D
    ctx->r6 = S32(0X801D << 16);
    // 0x802C6414: addu        $t1, $t2, $t5
    ctx->r9 = ADD32(ctx->r10, ctx->r13);
    // 0x802C6418: addu        $a2, $a2, $v1
    ctx->r6 = ADD32(ctx->r6, ctx->r3);
    // 0x802C641C: sw          $t1, 0xD0($sp)
    MEM_W(0XD0, ctx->r29) = ctx->r9;
    // 0x802C6420: beq         $a1, $a0, L_802C6434
    if (ctx->r5 == ctx->r4) {
        // 0x802C6424: lw          $a2, -0x4CC0($a2)
        ctx->r6 = MEM_W(ctx->r6, -0X4CC0);
            goto L_802C6434;
    }
    // 0x802C6424: lw          $a2, -0x4CC0($a2)
    ctx->r6 = MEM_W(ctx->r6, -0X4CC0);
    // 0x802C6428: or          $s2, $zero, $zero
    ctx->r18 = 0 | 0;
    // 0x802C642C: b           L_802C6454
    // 0x802C6430: or          $s3, $zero, $zero
    ctx->r19 = 0 | 0;
        goto L_802C6454;
    // 0x802C6430: or          $s3, $zero, $zero
    ctx->r19 = 0 | 0;
L_802C6434:
    // 0x802C6434: lui         $t6, 0x801C
    ctx->r14 = S32(0X801C << 16);
    // 0x802C6438: lw          $t6, 0x2650($t6)
    ctx->r14 = MEM_W(ctx->r14, 0X2650);
    // 0x802C643C: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x802C6440: addiu       $s2, $zero, 0x6
    ctx->r18 = ADD32(0, 0X6);
    // 0x802C6444: beq         $t6, $at, L_802C6454
    if (ctx->r14 == ctx->r1) {
        // 0x802C6448: addiu       $s3, $zero, 0x7
        ctx->r19 = ADD32(0, 0X7);
            goto L_802C6454;
    }
    // 0x802C6448: addiu       $s3, $zero, 0x7
    ctx->r19 = ADD32(0, 0X7);
    // 0x802C644C: b           L_802C6454
    // 0x802C6450: addiu       $s3, $zero, 0x6
    ctx->r19 = ADD32(0, 0X6);
        goto L_802C6454;
    // 0x802C6450: addiu       $s3, $zero, 0x6
    ctx->r19 = ADD32(0, 0X6);
L_802C6454:
    // 0x802C6454: lui         $t4, 0x801D
    ctx->r12 = S32(0X801D << 16);
    // 0x802C6458: lw          $t4, -0x19C0($t4)
    ctx->r12 = MEM_W(ctx->r12, -0X19C0);
    // 0x802C645C: slti        $at, $t4, 0x6
    ctx->r1 = SIGNED(ctx->r12) < 0X6 ? 1 : 0;
    // 0x802C6460: beq         $at, $zero, L_802C6470
    if (ctx->r1 == 0) {
        // 0x802C6464: nop
    
            goto L_802C6470;
    }
    // 0x802C6464: nop

    // 0x802C6468: b           L_802C6498
    // 0x802C646C: or          $s4, $zero, $zero
    ctx->r20 = 0 | 0;
        goto L_802C6498;
    // 0x802C646C: or          $s4, $zero, $zero
    ctx->r20 = 0 | 0;
L_802C6470:
    // 0x802C6470: beq         $a1, $a0, L_802C6480
    if (ctx->r5 == ctx->r4) {
        // 0x802C6474: lui         $t3, 0x802C
        ctx->r11 = S32(0X802C << 16);
            goto L_802C6480;
    }
    // 0x802C6474: lui         $t3, 0x802C
    ctx->r11 = S32(0X802C << 16);
    // 0x802C6478: b           L_802C6498
    // 0x802C647C: or          $s4, $zero, $zero
    ctx->r20 = 0 | 0;
        goto L_802C6498;
    // 0x802C647C: or          $s4, $zero, $zero
    ctx->r20 = 0 | 0;
L_802C6480:
    // 0x802C6480: lw          $t3, 0x7B00($t3)
    ctx->r11 = MEM_W(ctx->r11, 0X7B00);
    // 0x802C6484: addiu       $s4, $zero, 0x4
    ctx->r20 = ADD32(0, 0X4);
    // 0x802C6488: beq         $t3, $zero, L_802C6498
    if (ctx->r11 == 0) {
        // 0x802C648C: nop
    
            goto L_802C6498;
    }
    // 0x802C648C: nop

    // 0x802C6490: b           L_802C6498
    // 0x802C6494: addiu       $s4, $zero, 0x6
    ctx->r20 = ADD32(0, 0X6);
        goto L_802C6498;
    // 0x802C6494: addiu       $s4, $zero, 0x6
    ctx->r20 = ADD32(0, 0X6);
L_802C6498:
    // 0x802C6498: lui         $a1, 0x802C
    ctx->r5 = S32(0X802C << 16);
    // 0x802C649C: addiu       $a1, $a1, 0x7A50
    ctx->r5 = ADD32(ctx->r5, 0X7A50);
    // 0x802C64A0: or          $a0, $s5, $zero
    ctx->r4 = ctx->r21 | 0;
    // 0x802C64A4: jal         0x800CA210
    // 0x802C64A8: sw          $a2, 0xF0($sp)
    MEM_W(0XF0, ctx->r29) = ctx->r6;
    func_800CA210(rdram, ctx);
        goto after_17;
    // 0x802C64A8: sw          $a2, 0xF0($sp)
    MEM_W(0XF0, ctx->r29) = ctx->r6;
    after_17:
    // 0x802C64AC: addiu       $a0, $zero, 0xA
    ctx->r4 = ADD32(0, 0XA);
    // 0x802C64B0: lw          $a2, 0xF0($sp)
    ctx->r6 = MEM_W(ctx->r29, 0XF0);
    // 0x802C64B4: lw          $t2, 0xE8($sp)
    ctx->r10 = MEM_W(ctx->r29, 0XE8);
    // 0x802C64B8: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C64BC: div         $zero, $a2, $a0
    lo = S32(S64(S32(ctx->r6)) / S64(S32(ctx->r4))); hi = S32(S64(S32(ctx->r6)) % S64(S32(ctx->r4)));
    // 0x802C64C0: mflo        $t7
    ctx->r15 = lo;
    // 0x802C64C4: addu        $a3, $s7, $t2
    ctx->r7 = ADD32(ctx->r23, ctx->r10);
    // 0x802C64C8: bne         $a0, $zero, L_802C64D4
    if (ctx->r4 != 0) {
        // 0x802C64CC: nop
    
            goto L_802C64D4;
    }
    // 0x802C64CC: nop

    // 0x802C64D0: break       7
    do_break(2150393040);
L_802C64D4:
    // 0x802C64D4: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x802C64D8: bne         $a0, $at, L_802C64EC
    if (ctx->r4 != ctx->r1) {
        // 0x802C64DC: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_802C64EC;
    }
    // 0x802C64DC: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x802C64E0: bne         $a2, $at, L_802C64EC
    if (ctx->r6 != ctx->r1) {
        // 0x802C64E4: nop
    
            goto L_802C64EC;
    }
    // 0x802C64E4: nop

    // 0x802C64E8: break       6
    do_break(2150393064);
L_802C64EC:
    // 0x802C64EC: div         $zero, $t7, $a0
    lo = S32(S64(S32(ctx->r15)) / S64(S32(ctx->r4))); hi = S32(S64(S32(ctx->r15)) % S64(S32(ctx->r4)));
    // 0x802C64F0: mfhi        $v1
    ctx->r3 = hi;
    // 0x802C64F4: addiu       $a2, $sp, 0xC4
    ctx->r6 = ADD32(ctx->r29, 0XC4);
    // 0x802C64F8: bne         $a0, $zero, L_802C6504
    if (ctx->r4 != 0) {
        // 0x802C64FC: nop
    
            goto L_802C6504;
    }
    // 0x802C64FC: nop

    // 0x802C6500: break       7
    do_break(2150393088);
L_802C6504:
    // 0x802C6504: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x802C6508: bne         $a0, $at, L_802C651C
    if (ctx->r4 != ctx->r1) {
        // 0x802C650C: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_802C651C;
    }
    // 0x802C650C: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x802C6510: bne         $t7, $at, L_802C651C
    if (ctx->r15 != ctx->r1) {
        // 0x802C6514: nop
    
            goto L_802C651C;
    }
    // 0x802C6514: nop

    // 0x802C6518: break       6
    do_break(2150393112);
L_802C651C:
    // 0x802C651C: or          $a0, $s6, $zero
    ctx->r4 = ctx->r22 | 0;
    // 0x802C6520: beq         $v1, $zero, L_802C6540
    if (ctx->r3 == 0) {
        // 0x802C6524: addiu       $a3, $a3, 0xD
        ctx->r7 = ADD32(ctx->r7, 0XD);
            goto L_802C6540;
    }
    // 0x802C6524: addiu       $a3, $a3, 0xD
    ctx->r7 = ADD32(ctx->r7, 0XD);
    // 0x802C6528: lui         $t8, 0x8022
    ctx->r24 = S32(0X8022 << 16);
    // 0x802C652C: addu        $t8, $t8, $v1
    ctx->r24 = ADD32(ctx->r24, ctx->r3);
    // 0x802C6530: lbu         $t8, 0x6D70($t8)
    ctx->r24 = MEM_BU(ctx->r24, 0X6D70);
    // 0x802C6534: addiu       $t9, $zero, 0x14C
    ctx->r25 = ADD32(0, 0X14C);
    // 0x802C6538: b           L_802C6544
    // 0x802C653C: subu        $s1, $t9, $t8
    ctx->r17 = SUB32(ctx->r25, ctx->r24);
        goto L_802C6544;
    // 0x802C653C: subu        $s1, $t9, $t8
    ctx->r17 = SUB32(ctx->r25, ctx->r24);
L_802C6540:
    // 0x802C6540: addiu       $s1, $zero, 0x14C
    ctx->r17 = ADD32(0, 0X14C);
L_802C6544:
    // 0x802C6544: lw          $t5, 0x84($sp)
    ctx->r13 = MEM_W(ctx->r29, 0X84);
    // 0x802C6548: addiu       $t1, $zero, 0xFF
    ctx->r9 = ADD32(0, 0XFF);
    // 0x802C654C: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C6550: sw          $t5, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r13;
    // 0x802C6554: addiu       $t5, $zero, 0xFF
    ctx->r13 = ADD32(0, 0XFF);
    // 0x802C6558: addiu       $t4, $zero, 0xFF
    ctx->r12 = ADD32(0, 0XFF);
    // 0x802C655C: addiu       $t3, $zero, 0xFF
    ctx->r11 = ADD32(0, 0XFF);
    // 0x802C6560: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C6564: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C6568: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C656C: addiu       $t2, $zero, 0xFF
    ctx->r10 = ADD32(0, 0XFF);
    // 0x802C6570: sw          $t2, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r10;
    // 0x802C6574: sw          $t8, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r24;
    // 0x802C6578: sw          $t9, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r25;
    // 0x802C657C: sw          $t7, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r15;
    // 0x802C6580: sw          $t3, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r11;
    // 0x802C6584: sw          $t4, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r12;
    // 0x802C6588: sw          $t4, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r12;
    // 0x802C658C: sw          $t5, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r13;
    // 0x802C6590: sw          $t6, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r14;
    // 0x802C6594: sw          $t6, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r14;
    // 0x802C6598: sw          $t1, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r9;
    // 0x802C659C: sw          $t1, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r9;
    // 0x802C65A0: jal         0x801E92FC
    // 0x802C65A4: sw          $s2, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r18;
    func_801E92FC(rdram, ctx);
        goto after_18;
    // 0x802C65A4: sw          $s2, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r18;
    after_18:
    // 0x802C65A8: lw          $t3, 0x84($sp)
    ctx->r11 = MEM_W(ctx->r29, 0X84);
    // 0x802C65AC: addiu       $s0, $s7, 0x5C
    ctx->r16 = ADD32(ctx->r23, 0X5C);
    // 0x802C65B0: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C65B4: sw          $t3, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r11;
    // 0x802C65B8: addiu       $t3, $zero, 0xFF
    ctx->r11 = ADD32(0, 0XFF);
    // 0x802C65BC: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C65C0: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C65C4: addiu       $t2, $zero, 0xFF
    ctx->r10 = ADD32(0, 0XFF);
    // 0x802C65C8: addiu       $t5, $zero, 0xFF
    ctx->r13 = ADD32(0, 0XFF);
    // 0x802C65CC: addiu       $t1, $zero, 0xFF
    ctx->r9 = ADD32(0, 0XFF);
    // 0x802C65D0: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C65D4: addiu       $t4, $zero, 0xFF
    ctx->r12 = ADD32(0, 0XFF);
    // 0x802C65D8: sw          $t4, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r12;
    // 0x802C65DC: sw          $t6, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r14;
    // 0x802C65E0: sw          $t1, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r9;
    // 0x802C65E4: sw          $t5, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r13;
    // 0x802C65E8: sw          $t2, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r10;
    // 0x802C65EC: sw          $t8, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r24;
    // 0x802C65F0: sw          $t8, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r24;
    // 0x802C65F4: sw          $t9, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r25;
    // 0x802C65F8: sw          $t9, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r25;
    // 0x802C65FC: sw          $t3, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r11;
    // 0x802C6600: sw          $t7, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r15;
    // 0x802C6604: sw          $t7, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r15;
    // 0x802C6608: or          $a3, $s0, $zero
    ctx->r7 = ctx->r16 | 0;
    // 0x802C660C: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C6610: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C6614: lw          $a2, 0xD0($sp)
    ctx->r6 = MEM_W(ctx->r29, 0XD0);
    // 0x802C6618: jal         0x801E92FC
    // 0x802C661C: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    func_801E92FC(rdram, ctx);
        goto after_19;
    // 0x802C661C: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    after_19:
    // 0x802C6620: lw          $t2, 0x84($sp)
    ctx->r10 = MEM_W(ctx->r29, 0X84);
    // 0x802C6624: addu        $a3, $s7, $s1
    ctx->r7 = ADD32(ctx->r23, ctx->r17);
    // 0x802C6628: addiu       $t5, $zero, 0xFF
    ctx->r13 = ADD32(0, 0XFF);
    // 0x802C662C: sw          $t2, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r10;
    // 0x802C6630: addiu       $t2, $zero, 0xFF
    ctx->r10 = ADD32(0, 0XFF);
    // 0x802C6634: addiu       $t1, $zero, 0xFF
    ctx->r9 = ADD32(0, 0XFF);
    // 0x802C6638: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C663C: addiu       $t4, $zero, 0xFF
    ctx->r12 = ADD32(0, 0XFF);
    // 0x802C6640: addiu       $t3, $zero, 0xFF
    ctx->r11 = ADD32(0, 0XFF);
    // 0x802C6644: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C6648: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C664C: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C6650: sw          $t8, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r24;
    // 0x802C6654: sw          $t9, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r25;
    // 0x802C6658: sw          $t7, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r15;
    // 0x802C665C: sw          $t3, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r11;
    // 0x802C6660: sw          $t4, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r12;
    // 0x802C6664: sw          $t6, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r14;
    // 0x802C6668: sw          $t6, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r14;
    // 0x802C666C: sw          $t1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r9;
    // 0x802C6670: sw          $t1, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r9;
    // 0x802C6674: sw          $t2, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r10;
    // 0x802C6678: sw          $t5, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r13;
    // 0x802C667C: sw          $t5, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r13;
    // 0x802C6680: addiu       $a3, $a3, 0x8
    ctx->r7 = ADD32(ctx->r7, 0X8);
    // 0x802C6684: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C6688: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C668C: or          $a2, $s5, $zero
    ctx->r6 = ctx->r21 | 0;
    // 0x802C6690: jal         0x801E92FC
    // 0x802C6694: sw          $s4, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r20;
    func_801E92FC(rdram, ctx);
        goto after_20;
    // 0x802C6694: sw          $s4, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r20;
    after_20:
    // 0x802C6698: lw          $t4, 0x114($sp)
    ctx->r12 = MEM_W(ctx->r29, 0X114);
    // 0x802C669C: or          $s6, $v0, $zero
    ctx->r22 = ctx->r2 | 0;
    // 0x802C66A0: or          $a0, $s6, $zero
    ctx->r4 = ctx->r22 | 0;
    // 0x802C66A4: bne         $t4, $zero, L_802C67E0
    if (ctx->r12 != 0) {
        // 0x802C66A8: or          $a1, $s4, $zero
        ctx->r5 = ctx->r20 | 0;
            goto L_802C67E0;
    }
    // 0x802C66A8: or          $a1, $s4, $zero
    ctx->r5 = ctx->r20 | 0;
    // 0x802C66AC: lw          $t3, 0x90($sp)
    ctx->r11 = MEM_W(ctx->r29, 0X90);
    // 0x802C66B0: lui         $t7, 0x801D
    ctx->r15 = S32(0X801D << 16);
    // 0x802C66B4: lui         $t8, 0x801C
    ctx->r24 = S32(0X801C << 16);
    // 0x802C66B8: addu        $t7, $t7, $t3
    ctx->r15 = ADD32(ctx->r15, ctx->r11);
    // 0x802C66BC: lw          $t7, -0x18E8($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X18E8);
    // 0x802C66C0: addiu       $t8, $t8, 0x2938
    ctx->r24 = ADD32(ctx->r24, 0X2938);
    // 0x802C66C4: or          $a0, $s6, $zero
    ctx->r4 = ctx->r22 | 0;
    // 0x802C66C8: sll         $t9, $t7, 3
    ctx->r25 = S32(ctx->r15 << 3);
    // 0x802C66CC: subu        $t9, $t9, $t7
    ctx->r25 = SUB32(ctx->r25, ctx->r15);
    // 0x802C66D0: sll         $t9, $t9, 4
    ctx->r25 = S32(ctx->r25 << 4);
    // 0x802C66D4: subu        $t9, $t9, $t7
    ctx->r25 = SUB32(ctx->r25, ctx->r15);
    // 0x802C66D8: sll         $t9, $t9, 3
    ctx->r25 = S32(ctx->r25 << 3);
    // 0x802C66DC: addu        $v0, $t9, $t8
    ctx->r2 = ADD32(ctx->r25, ctx->r24);
    // 0x802C66E0: lw          $t2, 0x2EC($v0)
    ctx->r10 = MEM_W(ctx->r2, 0X2EC);
    // 0x802C66E4: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C66E8: or          $a3, $s0, $zero
    ctx->r7 = ctx->r16 | 0;
    // 0x802C66EC: beq         $t2, $zero, L_802C6778
    if (ctx->r10 == 0) {
        // 0x802C66F0: addiu       $t1, $zero, 0xFF
        ctx->r9 = ADD32(0, 0XFF);
            goto L_802C6778;
    }
    // 0x802C66F0: addiu       $t1, $zero, 0xFF
    ctx->r9 = ADD32(0, 0XFF);
    // 0x802C66F4: addiu       $t5, $zero, 0xFF
    ctx->r13 = ADD32(0, 0XFF);
    // 0x802C66F8: addiu       $t1, $zero, 0xFF
    ctx->r9 = ADD32(0, 0XFF);
    // 0x802C66FC: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C6700: addiu       $t4, $zero, 0xFF
    ctx->r12 = ADD32(0, 0XFF);
    // 0x802C6704: addiu       $t3, $zero, 0xFF
    ctx->r11 = ADD32(0, 0XFF);
    // 0x802C6708: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C670C: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C6710: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C6714: addiu       $t2, $zero, 0xFF
    ctx->r10 = ADD32(0, 0XFF);
    // 0x802C6718: sw          $t2, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r10;
    // 0x802C671C: sw          $t8, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r24;
    // 0x802C6720: sw          $t9, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r25;
    // 0x802C6724: sw          $t7, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r15;
    // 0x802C6728: sw          $t3, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r11;
    // 0x802C672C: sw          $t4, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r12;
    // 0x802C6730: sw          $t6, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r14;
    // 0x802C6734: sw          $t1, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r9;
    // 0x802C6738: sw          $t5, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r13;
    // 0x802C673C: sw          $t5, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r13;
    // 0x802C6740: or          $a0, $s6, $zero
    ctx->r4 = ctx->r22 | 0;
    // 0x802C6744: or          $a1, $s2, $zero
    ctx->r5 = ctx->r18 | 0;
    // 0x802C6748: addiu       $a2, $zero, 0xFF
    ctx->r6 = ADD32(0, 0XFF);
    // 0x802C674C: jal         0x801E946C
    // 0x802C6750: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    func_801E946C(rdram, ctx);
        goto after_21;
    // 0x802C6750: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    after_21:
    // 0x802C6754: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C6758: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C675C: addiu       $a2, $zero, 0x1B
    ctx->r6 = ADD32(0, 0X1B);
    // 0x802C6760: or          $a3, $s0, $zero
    ctx->r7 = ctx->r16 | 0;
    // 0x802C6764: sw          $fp, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r30;
    // 0x802C6768: jal         0x801E3EE0
    // 0x802C676C: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    func_801E3EE0(rdram, ctx);
        goto after_22;
    // 0x802C676C: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    after_22:
    // 0x802C6770: b           L_802C6988
    // 0x802C6774: or          $s6, $v0, $zero
    ctx->r22 = ctx->r2 | 0;
        goto L_802C6988;
    // 0x802C6774: or          $s6, $v0, $zero
    ctx->r22 = ctx->r2 | 0;
L_802C6778:
    // 0x802C6778: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C677C: addiu       $t4, $zero, 0xFF
    ctx->r12 = ADD32(0, 0XFF);
    // 0x802C6780: addiu       $t3, $zero, 0xFF
    ctx->r11 = ADD32(0, 0XFF);
    // 0x802C6784: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C6788: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C678C: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C6790: addiu       $t2, $zero, 0xFF
    ctx->r10 = ADD32(0, 0XFF);
    // 0x802C6794: addiu       $t5, $zero, 0xFF
    ctx->r13 = ADD32(0, 0XFF);
    // 0x802C6798: sw          $t5, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r13;
    // 0x802C679C: sw          $t2, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r10;
    // 0x802C67A0: sw          $t8, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r24;
    // 0x802C67A4: sw          $t9, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r25;
    // 0x802C67A8: sw          $t7, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r15;
    // 0x802C67AC: sw          $t3, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r11;
    // 0x802C67B0: sw          $t4, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r12;
    // 0x802C67B4: sw          $t6, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r14;
    // 0x802C67B8: lw          $a2, 0x19C($v0)
    ctx->r6 = MEM_W(ctx->r2, 0X19C);
    // 0x802C67BC: sw          $fp, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r30;
    // 0x802C67C0: sw          $s3, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r19;
    // 0x802C67C4: sw          $t1, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r9;
    // 0x802C67C8: sw          $zero, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = 0;
    // 0x802C67CC: sw          $zero, 0x20($sp)
    MEM_W(0X20, ctx->r29) = 0;
    // 0x802C67D0: jal         0x801E8A84
    // 0x802C67D4: sw          $t1, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r9;
    func_801E8A84(rdram, ctx);
        goto after_23;
    // 0x802C67D4: sw          $t1, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r9;
    after_23:
    // 0x802C67D8: b           L_802C6988
    // 0x802C67DC: or          $s6, $v0, $zero
    ctx->r22 = ctx->r2 | 0;
        goto L_802C6988;
    // 0x802C67DC: or          $s6, $v0, $zero
    ctx->r22 = ctx->r2 | 0;
L_802C67E0:
    // 0x802C67E0: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C67E4: addiu       $t4, $zero, 0xFF
    ctx->r12 = ADD32(0, 0XFF);
    // 0x802C67E8: addiu       $t3, $zero, 0xFF
    ctx->r11 = ADD32(0, 0XFF);
    // 0x802C67EC: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C67F0: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C67F4: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C67F8: addiu       $t2, $zero, 0xFF
    ctx->r10 = ADD32(0, 0XFF);
    // 0x802C67FC: addiu       $t5, $zero, 0xFF
    ctx->r13 = ADD32(0, 0XFF);
    // 0x802C6800: addiu       $t1, $zero, 0xFF
    ctx->r9 = ADD32(0, 0XFF);
    // 0x802C6804: sw          $t1, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r9;
    // 0x802C6808: sw          $t5, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r13;
    // 0x802C680C: sw          $t2, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r10;
    // 0x802C6810: sw          $t8, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r24;
    // 0x802C6814: sw          $t9, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r25;
    // 0x802C6818: sw          $t7, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r15;
    // 0x802C681C: sw          $t3, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r11;
    // 0x802C6820: sw          $t4, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r12;
    // 0x802C6824: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x802C6828: sw          $t6, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r14;
    // 0x802C682C: addiu       $a2, $zero, 0xFF
    ctx->r6 = ADD32(0, 0XFF);
    // 0x802C6830: jal         0x801E946C
    // 0x802C6834: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    func_801E946C(rdram, ctx);
        goto after_24;
    // 0x802C6834: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    after_24:
    // 0x802C6838: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C683C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C6840: addiu       $a2, $zero, 0x18
    ctx->r6 = ADD32(0, 0X18);
    // 0x802C6844: or          $a3, $s0, $zero
    ctx->r7 = ctx->r16 | 0;
    // 0x802C6848: sw          $fp, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r30;
    // 0x802C684C: jal         0x801E3EE0
    // 0x802C6850: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    func_801E3EE0(rdram, ctx);
        goto after_25;
    // 0x802C6850: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    after_25:
    // 0x802C6854: lui         $t4, 0x801D
    ctx->r12 = S32(0X801D << 16);
    // 0x802C6858: lw          $t4, -0x4CC8($t4)
    ctx->r12 = MEM_W(ctx->r12, -0X4CC8);
    // 0x802C685C: or          $s6, $v0, $zero
    ctx->r22 = ctx->r2 | 0;
    // 0x802C6860: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    // 0x802C6864: bne         $t4, $zero, L_802C6874
    if (ctx->r12 != 0) {
        // 0x802C6868: lui         $v1, 0x801D
        ctx->r3 = S32(0X801D << 16);
            goto L_802C6874;
    }
    // 0x802C6868: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x802C686C: b           L_802C6874
    // 0x802C6870: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
        goto L_802C6874;
    // 0x802C6870: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
L_802C6874:
    // 0x802C6874: lw          $v1, -0x4CCC($v1)
    ctx->r3 = MEM_W(ctx->r3, -0X4CCC);
    // 0x802C6878: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
    // 0x802C687C: lw          $t3, 0x90($sp)
    ctx->r11 = MEM_W(ctx->r29, 0X90);
    // 0x802C6880: slt         $at, $v1, $v0
    ctx->r1 = SIGNED(ctx->r3) < SIGNED(ctx->r2) ? 1 : 0;
    // 0x802C6884: bne         $at, $zero, L_802C6988
    if (ctx->r1 != 0) {
        // 0x802C6888: lui         $t7, 0x800E
        ctx->r15 = S32(0X800E << 16);
            goto L_802C6988;
    }
    // 0x802C6888: lui         $t7, 0x800E
    ctx->r15 = S32(0X800E << 16);
    // 0x802C688C: subu        $t2, $v0, $v0
    ctx->r10 = SUB32(ctx->r2, ctx->r2);
    // 0x802C6890: sll         $t5, $t2, 2
    ctx->r13 = S32(ctx->r10 << 2);
    // 0x802C6894: subu        $t5, $t5, $t2
    ctx->r13 = SUB32(ctx->r13, ctx->r10);
    // 0x802C6898: sll         $t5, $t5, 2
    ctx->r13 = S32(ctx->r13 << 2);
    // 0x802C689C: lui         $t8, 0x801D
    ctx->r24 = S32(0X801D << 16);
    // 0x802C68A0: addiu       $t8, $t8, -0x4CB0
    ctx->r24 = ADD32(ctx->r24, -0X4CB0);
    // 0x802C68A4: addu        $s2, $s7, $t5
    ctx->r18 = ADD32(ctx->r23, ctx->r13);
    // 0x802C68A8: addiu       $t7, $t7, -0x5624
    ctx->r15 = ADD32(ctx->r15, -0X5624);
    // 0x802C68AC: sll         $t9, $v0, 4
    ctx->r25 = S32(ctx->r2 << 4);
    // 0x802C68B0: addu        $s1, $t9, $t8
    ctx->r17 = ADD32(ctx->r25, ctx->r24);
    // 0x802C68B4: addu        $s3, $t3, $t7
    ctx->r19 = ADD32(ctx->r11, ctx->r15);
    // 0x802C68B8: addiu       $s2, $s2, 0x84
    ctx->r18 = ADD32(ctx->r18, 0X84);
L_802C68BC:
    // 0x802C68BC: lw          $t1, 0x0($s3)
    ctx->r9 = MEM_W(ctx->r19, 0X0);
    // 0x802C68C0: or          $a0, $s5, $zero
    ctx->r4 = ctx->r21 | 0;
    // 0x802C68C4: lui         $a1, 0x802C
    ctx->r5 = S32(0X802C << 16);
    // 0x802C68C8: sll         $t6, $t1, 2
    ctx->r14 = S32(ctx->r9 << 2);
    // 0x802C68CC: addu        $t4, $s1, $t6
    ctx->r12 = ADD32(ctx->r17, ctx->r14);
    // 0x802C68D0: beq         $s0, $v1, L_802C68F0
    if (ctx->r16 == ctx->r3) {
        // 0x802C68D4: lw          $a2, 0x0($t4)
        ctx->r6 = MEM_W(ctx->r12, 0X0);
            goto L_802C68F0;
    }
    // 0x802C68D4: lw          $a2, 0x0($t4)
    ctx->r6 = MEM_W(ctx->r12, 0X0);
    // 0x802C68D8: lui         $a1, 0x802C
    ctx->r5 = S32(0X802C << 16);
    // 0x802C68DC: addiu       $a1, $a1, 0x7A54
    ctx->r5 = ADD32(ctx->r5, 0X7A54);
    // 0x802C68E0: jal         0x800CA210
    // 0x802C68E4: or          $a0, $s5, $zero
    ctx->r4 = ctx->r21 | 0;
    func_800CA210(rdram, ctx);
        goto after_26;
    // 0x802C68E4: or          $a0, $s5, $zero
    ctx->r4 = ctx->r21 | 0;
    after_26:
    // 0x802C68E8: b           L_802C68FC
    // 0x802C68EC: addiu       $t3, $zero, 0xFF
    ctx->r11 = ADD32(0, 0XFF);
        goto L_802C68FC;
    // 0x802C68EC: addiu       $t3, $zero, 0xFF
    ctx->r11 = ADD32(0, 0XFF);
L_802C68F0:
    // 0x802C68F0: jal         0x800CA210
    // 0x802C68F4: addiu       $a1, $a1, 0x7A58
    ctx->r5 = ADD32(ctx->r5, 0X7A58);
    func_800CA210(rdram, ctx);
        goto after_27;
    // 0x802C68F4: addiu       $a1, $a1, 0x7A58
    ctx->r5 = ADD32(ctx->r5, 0X7A58);
    after_27:
    // 0x802C68F8: addiu       $t3, $zero, 0xFF
    ctx->r11 = ADD32(0, 0XFF);
L_802C68FC:
    // 0x802C68FC: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C6900: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C6904: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C6908: addiu       $t2, $zero, 0xFF
    ctx->r10 = ADD32(0, 0XFF);
    // 0x802C690C: addiu       $t5, $zero, 0xFF
    ctx->r13 = ADD32(0, 0XFF);
    // 0x802C6910: addiu       $t1, $zero, 0xFF
    ctx->r9 = ADD32(0, 0XFF);
    // 0x802C6914: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C6918: addiu       $t4, $zero, 0xFF
    ctx->r12 = ADD32(0, 0XFF);
    // 0x802C691C: sw          $t4, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r12;
    // 0x802C6920: sw          $t6, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r14;
    // 0x802C6924: sw          $t1, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r9;
    // 0x802C6928: sw          $t5, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r13;
    // 0x802C692C: sw          $t2, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r10;
    // 0x802C6930: sw          $t8, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r24;
    // 0x802C6934: sw          $t9, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r25;
    // 0x802C6938: sw          $t9, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r25;
    // 0x802C693C: sw          $t7, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r15;
    // 0x802C6940: sw          $t7, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r15;
    // 0x802C6944: sw          $t3, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r11;
    // 0x802C6948: sw          $t3, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r11;
    // 0x802C694C: or          $a0, $s6, $zero
    ctx->r4 = ctx->r22 | 0;
    // 0x802C6950: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C6954: or          $a2, $s5, $zero
    ctx->r6 = ctx->r21 | 0;
    // 0x802C6958: or          $a3, $s2, $zero
    ctx->r7 = ctx->r18 | 0;
    // 0x802C695C: sw          $fp, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r30;
    // 0x802C6960: jal         0x801E92FC
    // 0x802C6964: sw          $s4, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r20;
    func_801E92FC(rdram, ctx);
        goto after_28;
    // 0x802C6964: sw          $s4, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r20;
    after_28:
    // 0x802C6968: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x802C696C: lw          $v1, -0x4CCC($v1)
    ctx->r3 = MEM_W(ctx->r3, -0X4CCC);
    // 0x802C6970: addiu       $s0, $s0, 0x1
    ctx->r16 = ADD32(ctx->r16, 0X1);
    // 0x802C6974: addiu       $s1, $s1, 0x10
    ctx->r17 = ADD32(ctx->r17, 0X10);
    // 0x802C6978: slt         $at, $v1, $s0
    ctx->r1 = SIGNED(ctx->r3) < SIGNED(ctx->r16) ? 1 : 0;
    // 0x802C697C: addiu       $s2, $s2, 0xC
    ctx->r18 = ADD32(ctx->r18, 0XC);
    // 0x802C6980: beq         $at, $zero, L_802C68BC
    if (ctx->r1 == 0) {
        // 0x802C6984: or          $s6, $v0, $zero
        ctx->r22 = ctx->r2 | 0;
            goto L_802C68BC;
    }
    // 0x802C6984: or          $s6, $v0, $zero
    ctx->r22 = ctx->r2 | 0;
L_802C6988:
    // 0x802C6988: lw          $t8, 0x11C($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X11C);
    // 0x802C698C: lw          $t5, 0x90($sp)
    ctx->r13 = MEM_W(ctx->r29, 0X90);
    // 0x802C6990: lw          $t6, 0x84($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X84);
    // 0x802C6994: addiu       $t2, $t8, 0x1
    ctx->r10 = ADD32(ctx->r24, 0X1);
    // 0x802C6998: slti        $at, $t2, 0x4
    ctx->r1 = SIGNED(ctx->r10) < 0X4 ? 1 : 0;
    // 0x802C699C: addiu       $t1, $t5, 0x4
    ctx->r9 = ADD32(ctx->r13, 0X4);
    // 0x802C69A0: addiu       $t4, $t6, 0x20
    ctx->r12 = ADD32(ctx->r14, 0X20);
    // 0x802C69A4: sw          $t4, 0x84($sp)
    MEM_W(0X84, ctx->r29) = ctx->r12;
    // 0x802C69A8: sw          $t1, 0x90($sp)
    MEM_W(0X90, ctx->r29) = ctx->r9;
    // 0x802C69AC: sw          $t2, 0x11C($sp)
    MEM_W(0X11C, ctx->r29) = ctx->r10;
    // 0x802C69B0: bne         $at, $zero, L_802C61D0
    if (ctx->r1 != 0) {
        // 0x802C69B4: addiu       $fp, $fp, 0x20
        ctx->r30 = ADD32(ctx->r30, 0X20);
            goto L_802C61D0;
    }
    // 0x802C69B4: addiu       $fp, $fp, 0x20
    ctx->r30 = ADD32(ctx->r30, 0X20);
    // 0x802C69B8: lw          $t3, 0x114($sp)
    ctx->r11 = MEM_W(ctx->r29, 0X114);
    // 0x802C69BC: lui         $t6, 0x801D
    ctx->r14 = S32(0X801D << 16);
    // 0x802C69C0: or          $a0, $s6, $zero
    ctx->r4 = ctx->r22 | 0;
    // 0x802C69C4: bne         $t3, $zero, L_802C6A88
    if (ctx->r11 != 0) {
        // 0x802C69C8: addiu       $a2, $zero, 0xFF
        ctx->r6 = ADD32(0, 0XFF);
            goto L_802C6A88;
    }
    // 0x802C69C8: addiu       $a2, $zero, 0xFF
    ctx->r6 = ADD32(0, 0XFF);
    // 0x802C69CC: lui         $t7, 0x802C
    ctx->r15 = S32(0X802C << 16);
    // 0x802C69D0: lw          $t7, 0x7B00($t7)
    ctx->r15 = MEM_W(ctx->r15, 0X7B00);
    // 0x802C69D4: or          $a0, $s6, $zero
    ctx->r4 = ctx->r22 | 0;
    // 0x802C69D8: addiu       $a2, $zero, 0xFF
    ctx->r6 = ADD32(0, 0XFF);
    // 0x802C69DC: beq         $t7, $zero, L_802C69EC
    if (ctx->r15 == 0) {
        // 0x802C69E0: addiu       $a3, $zero, 0xFF
        ctx->r7 = ADD32(0, 0XFF);
            goto L_802C69EC;
    }
    // 0x802C69E0: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    // 0x802C69E4: b           L_802C69F0
    // 0x802C69E8: or          $s2, $zero, $zero
    ctx->r18 = 0 | 0;
        goto L_802C69F0;
    // 0x802C69E8: or          $s2, $zero, $zero
    ctx->r18 = 0 | 0;
L_802C69EC:
    // 0x802C69EC: addiu       $s2, $zero, 0x4
    ctx->r18 = ADD32(0, 0X4);
L_802C69F0:
    // 0x802C69F0: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C69F4: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C69F8: addiu       $t5, $zero, 0xFF
    ctx->r13 = ADD32(0, 0XFF);
    // 0x802C69FC: addiu       $t1, $zero, 0xFF
    ctx->r9 = ADD32(0, 0XFF);
    // 0x802C6A00: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C6A04: addiu       $t4, $zero, 0xFF
    ctx->r12 = ADD32(0, 0XFF);
    // 0x802C6A08: addiu       $t2, $zero, 0xFF
    ctx->r10 = ADD32(0, 0XFF);
    // 0x802C6A0C: addiu       $t3, $zero, 0xFF
    ctx->r11 = ADD32(0, 0XFF);
    // 0x802C6A10: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C6A14: sw          $t7, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r15;
    // 0x802C6A18: sw          $t3, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r11;
    // 0x802C6A1C: sw          $t2, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r10;
    // 0x802C6A20: sw          $t4, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r12;
    // 0x802C6A24: sw          $t6, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r14;
    // 0x802C6A28: sw          $t1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r9;
    // 0x802C6A2C: sw          $t5, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r13;
    // 0x802C6A30: sw          $t8, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r24;
    // 0x802C6A34: sw          $t9, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r25;
    // 0x802C6A38: sw          $t9, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r25;
    // 0x802C6A3C: jal         0x801E946C
    // 0x802C6A40: or          $a1, $s2, $zero
    ctx->r5 = ctx->r18 | 0;
    func_801E946C(rdram, ctx);
        goto after_29;
    // 0x802C6A40: or          $a1, $s2, $zero
    ctx->r5 = ctx->r18 | 0;
    after_29:
    // 0x802C6A44: lui         $t8, 0x801D
    ctx->r24 = S32(0X801D << 16);
    // 0x802C6A48: lw          $t8, -0x18FC($t8)
    ctx->r24 = MEM_W(ctx->r24, -0X18FC);
    // 0x802C6A4C: lui         $a3, 0x802C
    ctx->r7 = S32(0X802C << 16);
    // 0x802C6A50: lh          $a3, 0x7A00($a3)
    ctx->r7 = MEM_H(ctx->r7, 0X7A00);
    // 0x802C6A54: lui         $a2, 0x802C
    ctx->r6 = S32(0X802C << 16);
    // 0x802C6A58: sll         $t5, $t8, 2
    ctx->r13 = S32(ctx->r24 << 2);
    // 0x802C6A5C: addu        $a2, $a2, $t5
    ctx->r6 = ADD32(ctx->r6, ctx->r13);
    // 0x802C6A60: addiu       $t1, $zero, 0xCA
    ctx->r9 = ADD32(0, 0XCA);
    // 0x802C6A64: sw          $t1, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r9;
    // 0x802C6A68: lw          $a2, 0x7A18($a2)
    ctx->r6 = MEM_W(ctx->r6, 0X7A18);
    // 0x802C6A6C: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C6A70: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C6A74: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    // 0x802C6A78: jal         0x801E3EE0
    // 0x802C6A7C: addiu       $a3, $a3, 0x108
    ctx->r7 = ADD32(ctx->r7, 0X108);
    func_801E3EE0(rdram, ctx);
        goto after_30;
    // 0x802C6A7C: addiu       $a3, $a3, 0x108
    ctx->r7 = ADD32(ctx->r7, 0X108);
    after_30:
    // 0x802C6A80: b           L_802C6B5C
    // 0x802C6A84: lui         $t6, 0xB400
    ctx->r14 = S32(0XB400 << 16);
        goto L_802C6B5C;
    // 0x802C6A84: lui         $t6, 0xB400
    ctx->r14 = S32(0XB400 << 16);
L_802C6A88:
    // 0x802C6A88: lw          $t6, -0x19C0($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X19C0);
    // 0x802C6A8C: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    // 0x802C6A90: addiu       $t2, $zero, 0xFF
    ctx->r10 = ADD32(0, 0XFF);
    // 0x802C6A94: slti        $at, $t6, 0x6
    ctx->r1 = SIGNED(ctx->r14) < 0X6 ? 1 : 0;
    // 0x802C6A98: beq         $at, $zero, L_802C6AA8
    if (ctx->r1 == 0) {
        // 0x802C6A9C: addiu       $t3, $zero, 0xFF
        ctx->r11 = ADD32(0, 0XFF);
            goto L_802C6AA8;
    }
    // 0x802C6A9C: addiu       $t3, $zero, 0xFF
    ctx->r11 = ADD32(0, 0XFF);
    // 0x802C6AA0: b           L_802C6AC4
    // 0x802C6AA4: or          $s2, $zero, $zero
    ctx->r18 = 0 | 0;
        goto L_802C6AC4;
    // 0x802C6AA4: or          $s2, $zero, $zero
    ctx->r18 = 0 | 0;
L_802C6AA8:
    // 0x802C6AA8: lui         $t4, 0x802C
    ctx->r12 = S32(0X802C << 16);
    // 0x802C6AAC: lw          $t4, 0x7B00($t4)
    ctx->r12 = MEM_W(ctx->r12, 0X7B00);
    // 0x802C6AB0: addiu       $s2, $zero, 0x4
    ctx->r18 = ADD32(0, 0X4);
    // 0x802C6AB4: beq         $t4, $zero, L_802C6AC4
    if (ctx->r12 == 0) {
        // 0x802C6AB8: nop
    
            goto L_802C6AC4;
    }
    // 0x802C6AB8: nop

    // 0x802C6ABC: b           L_802C6AC4
    // 0x802C6AC0: addiu       $s2, $zero, 0x6
    ctx->r18 = ADD32(0, 0X6);
        goto L_802C6AC4;
    // 0x802C6AC0: addiu       $s2, $zero, 0x6
    ctx->r18 = ADD32(0, 0X6);
L_802C6AC4:
    // 0x802C6AC4: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C6AC8: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C6ACC: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C6AD0: addiu       $t5, $zero, 0xFF
    ctx->r13 = ADD32(0, 0XFF);
    // 0x802C6AD4: addiu       $t1, $zero, 0xFF
    ctx->r9 = ADD32(0, 0XFF);
    // 0x802C6AD8: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C6ADC: addiu       $t4, $zero, 0xFF
    ctx->r12 = ADD32(0, 0XFF);
    // 0x802C6AE0: sw          $t4, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r12;
    // 0x802C6AE4: sw          $t6, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r14;
    // 0x802C6AE8: sw          $t1, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r9;
    // 0x802C6AEC: sw          $t5, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r13;
    // 0x802C6AF0: sw          $t8, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r24;
    // 0x802C6AF4: sw          $t9, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r25;
    // 0x802C6AF8: sw          $t7, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r15;
    // 0x802C6AFC: or          $a1, $s2, $zero
    ctx->r5 = ctx->r18 | 0;
    // 0x802C6B00: sw          $t2, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r10;
    // 0x802C6B04: sw          $t3, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r11;
    // 0x802C6B08: jal         0x801E946C
    // 0x802C6B0C: sw          $t2, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r10;
    func_801E946C(rdram, ctx);
        goto after_31;
    // 0x802C6B0C: sw          $t2, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r10;
    after_31:
    // 0x802C6B10: lui         $t3, 0x801D
    ctx->r11 = S32(0X801D << 16);
    // 0x802C6B14: lui         $t9, 0x801D
    ctx->r25 = S32(0X801D << 16);
    // 0x802C6B18: lw          $t9, -0x4CCC($t9)
    ctx->r25 = MEM_W(ctx->r25, -0X4CCC);
    // 0x802C6B1C: lw          $t3, -0x4CC8($t3)
    ctx->r11 = MEM_W(ctx->r11, -0X4CC8);
    // 0x802C6B20: lui         $a3, 0x802C
    ctx->r7 = S32(0X802C << 16);
    // 0x802C6B24: sll         $t8, $t9, 1
    ctx->r24 = S32(ctx->r25 << 1);
    // 0x802C6B28: sll         $t7, $t3, 4
    ctx->r15 = S32(ctx->r11 << 4);
    // 0x802C6B2C: lh          $a3, 0x7A00($a3)
    ctx->r7 = MEM_H(ctx->r7, 0X7A00);
    // 0x802C6B30: addu        $t5, $t7, $t8
    ctx->r13 = ADD32(ctx->r15, ctx->r24);
    // 0x802C6B34: lui         $a2, 0x800F
    ctx->r6 = S32(0X800F << 16);
    // 0x802C6B38: addu        $a2, $a2, $t5
    ctx->r6 = ADD32(ctx->r6, ctx->r13);
    // 0x802C6B3C: addiu       $t1, $zero, 0xC9
    ctx->r9 = ADD32(0, 0XC9);
    // 0x802C6B40: sw          $t1, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r9;
    // 0x802C6B44: lh          $a2, -0x5444($a2)
    ctx->r6 = MEM_H(ctx->r6, -0X5444);
    // 0x802C6B48: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C6B4C: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C6B50: jal         0x801EB00C
    // 0x802C6B54: addiu       $a3, $a3, 0x15A
    ctx->r7 = ADD32(ctx->r7, 0X15A);
    func_801EB00C(rdram, ctx);
        goto after_32;
    // 0x802C6B54: addiu       $a3, $a3, 0x15A
    ctx->r7 = ADD32(ctx->r7, 0X15A);
    after_32:
    // 0x802C6B58: lui         $t6, 0xB400
    ctx->r14 = S32(0XB400 << 16);
L_802C6B5C:
    // 0x802C6B5C: sw          $t6, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r14;
    // 0x802C6B60: lui         $t4, 0x802C
    ctx->r12 = S32(0X802C << 16);
    // 0x802C6B64: lhu         $t4, 0x7B06($t4)
    ctx->r12 = MEM_HU(ctx->r12, 0X7B06);
    // 0x802C6B68: addiu       $s6, $v0, 0x8
    ctx->r22 = ADD32(ctx->r2, 0X8);
    // 0x802C6B6C: or          $a0, $s6, $zero
    ctx->r4 = ctx->r22 | 0;
    // 0x802C6B70: lui         $t2, 0x103
    ctx->r10 = S32(0X103 << 16);
    // 0x802C6B74: lui         $t3, 0x700
    ctx->r11 = S32(0X700 << 16);
    // 0x802C6B78: sw          $t4, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r12;
    // 0x802C6B7C: addiu       $t3, $t3, 0xA40
    ctx->r11 = ADD32(ctx->r11, 0XA40);
    // 0x802C6B80: ori         $t2, $t2, 0x40
    ctx->r10 = ctx->r10 | 0X40;
    // 0x802C6B84: addiu       $s6, $s6, 0x8
    ctx->r22 = ADD32(ctx->r22, 0X8);
    // 0x802C6B88: sw          $t2, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r10;
    // 0x802C6B8C: sw          $t3, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r11;
    // 0x802C6B90: or          $a1, $s6, $zero
    ctx->r5 = ctx->r22 | 0;
    // 0x802C6B94: lui         $t7, 0x107
    ctx->r15 = S32(0X107 << 16);
    // 0x802C6B98: addiu       $t7, $t7, -0xB78
    ctx->r15 = ADD32(ctx->r15, -0XB78);
    // 0x802C6B9C: lui         $t9, 0x600
    ctx->r25 = S32(0X600 << 16);
    // 0x802C6BA0: sw          $t9, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r25;
    // 0x802C6BA4: sw          $t7, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r15;
    // 0x802C6BA8: lui         $s1, 0x700
    ctx->r17 = S32(0X700 << 16);
    // 0x802C6BAC: lui         $s2, 0x700
    ctx->r18 = S32(0X700 << 16);
    // 0x802C6BB0: lui         $s7, 0x801D
    ctx->r23 = S32(0X801D << 16);
    // 0x802C6BB4: lui         $s5, 0x800E
    ctx->r21 = S32(0X800E << 16);
    // 0x802C6BB8: lui         $s4, 0x102
    ctx->r20 = S32(0X102 << 16);
    // 0x802C6BBC: lui         $s3, 0x380
    ctx->r19 = S32(0X380 << 16);
    // 0x802C6BC0: addiu       $s6, $s6, 0x8
    ctx->r22 = ADD32(ctx->r22, 0X8);
    // 0x802C6BC4: ori         $s3, $s3, 0x10
    ctx->r19 = ctx->r19 | 0X10;
    // 0x802C6BC8: ori         $s4, $s4, 0x40
    ctx->r20 = ctx->r20 | 0X40;
    // 0x802C6BCC: addiu       $s5, $s5, -0x5624
    ctx->r21 = ADD32(ctx->r21, -0X5624);
    // 0x802C6BD0: addiu       $s7, $s7, -0x1A08
    ctx->r23 = ADD32(ctx->r23, -0X1A08);
    // 0x802C6BD4: addiu       $s2, $s2, 0xA80
    ctx->r18 = ADD32(ctx->r18, 0XA80);
    // 0x802C6BD8: addiu       $s1, $s1, 0x1280
    ctx->r17 = ADD32(ctx->r17, 0X1280);
    // 0x802C6BDC: sw          $zero, 0x90($sp)
    MEM_W(0X90, ctx->r29) = 0;
    // 0x802C6BE0: or          $s0, $zero, $zero
    ctx->r16 = 0 | 0;
    // 0x802C6BE4: addiu       $fp, $zero, 0x300
    ctx->r30 = ADD32(0, 0X300);
L_802C6BE8:
    // 0x802C6BE8: or          $v0, $s6, $zero
    ctx->r2 = ctx->r22 | 0;
    // 0x802C6BEC: addiu       $s6, $s6, 0x8
    ctx->r22 = ADD32(ctx->r22, 0X8);
    // 0x802C6BF0: sw          $s3, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r19;
    // 0x802C6BF4: sw          $s1, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r17;
    // 0x802C6BF8: or          $v1, $s6, $zero
    ctx->r3 = ctx->r22 | 0;
    // 0x802C6BFC: sw          $s4, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r20;
    // 0x802C6C00: sw          $s2, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r18;
    // 0x802C6C04: lw          $t8, 0x114($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X114);
    // 0x802C6C08: addiu       $s6, $s6, 0x8
    ctx->r22 = ADD32(ctx->r22, 0X8);
    // 0x802C6C0C: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x802C6C10: bne         $t8, $at, L_802C6C38
    if (ctx->r24 != ctx->r1) {
        // 0x802C6C14: or          $a0, $s6, $zero
        ctx->r4 = ctx->r22 | 0;
            goto L_802C6C38;
    }
    // 0x802C6C14: or          $a0, $s6, $zero
    ctx->r4 = ctx->r22 | 0;
    // 0x802C6C18: lw          $t5, 0x90($sp)
    ctx->r13 = MEM_W(ctx->r29, 0X90);
    // 0x802C6C1C: lui         $a1, 0x800E
    ctx->r5 = S32(0X800E << 16);
    // 0x802C6C20: addu        $t1, $s5, $t5
    ctx->r9 = ADD32(ctx->r21, ctx->r13);
    // 0x802C6C24: lw          $t6, 0x0($t1)
    ctx->r14 = MEM_W(ctx->r9, 0X0);
    // 0x802C6C28: sll         $t4, $t6, 2
    ctx->r12 = S32(ctx->r14 << 2);
    // 0x802C6C2C: addu        $a1, $a1, $t4
    ctx->r5 = ADD32(ctx->r5, ctx->r12);
    // 0x802C6C30: b           L_802C6C58
    // 0x802C6C34: lw          $a1, -0x5650($a1)
    ctx->r5 = MEM_W(ctx->r5, -0X5650);
        goto L_802C6C58;
    // 0x802C6C34: lw          $a1, -0x5650($a1)
    ctx->r5 = MEM_W(ctx->r5, -0X5650);
L_802C6C38:
    // 0x802C6C38: lw          $t2, 0x90($sp)
    ctx->r10 = MEM_W(ctx->r29, 0X90);
    // 0x802C6C3C: lui         $t3, 0x801D
    ctx->r11 = S32(0X801D << 16);
    // 0x802C6C40: lui         $a1, 0x800E
    ctx->r5 = S32(0X800E << 16);
    // 0x802C6C44: addu        $t3, $t3, $t2
    ctx->r11 = ADD32(ctx->r11, ctx->r10);
    // 0x802C6C48: lw          $t3, -0x18E8($t3)
    ctx->r11 = MEM_W(ctx->r11, -0X18E8);
    // 0x802C6C4C: sll         $t9, $t3, 2
    ctx->r25 = S32(ctx->r11 << 2);
    // 0x802C6C50: addu        $a1, $a1, $t9
    ctx->r5 = ADD32(ctx->r5, ctx->r25);
    // 0x802C6C54: lw          $a1, -0x5650($a1)
    ctx->r5 = MEM_W(ctx->r5, -0X5650);
L_802C6C58:
    // 0x802C6C58: lw          $t7, 0x0($s7)
    ctx->r15 = MEM_W(ctx->r23, 0X0);
    // 0x802C6C5C: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x802C6C60: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    // 0x802C6C64: addu        $t8, $t7, $s0
    ctx->r24 = ADD32(ctx->r15, ctx->r16);
    // 0x802C6C68: addiu       $t5, $t8, 0xC80
    ctx->r13 = ADD32(ctx->r24, 0XC80);
    // 0x802C6C6C: jal         0x801E4FE8
    // 0x802C6C70: sw          $t5, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r13;
    func_801E4FE8(rdram, ctx);
        goto after_33;
    // 0x802C6C70: sw          $t5, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r13;
    after_33:
    // 0x802C6C74: lw          $t1, 0x90($sp)
    ctx->r9 = MEM_W(ctx->r29, 0X90);
    // 0x802C6C78: addiu       $s0, $s0, 0xC0
    ctx->r16 = ADD32(ctx->r16, 0XC0);
    // 0x802C6C7C: addiu       $s1, $s1, 0x10
    ctx->r17 = ADD32(ctx->r17, 0X10);
    // 0x802C6C80: addiu       $t6, $t1, 0x4
    ctx->r14 = ADD32(ctx->r9, 0X4);
    // 0x802C6C84: sw          $t6, 0x90($sp)
    MEM_W(0X90, ctx->r29) = ctx->r14;
    // 0x802C6C88: addiu       $s2, $s2, 0x40
    ctx->r18 = ADD32(ctx->r18, 0X40);
    // 0x802C6C8C: bne         $s0, $fp, L_802C6BE8
    if (ctx->r16 != ctx->r30) {
        // 0x802C6C90: or          $s6, $v0, $zero
        ctx->r22 = ctx->r2 | 0;
            goto L_802C6BE8;
    }
    // 0x802C6C90: or          $s6, $v0, $zero
    ctx->r22 = ctx->r2 | 0;
    // 0x802C6C94: lw          $ra, 0x74($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X74);
    // 0x802C6C98: lw          $s0, 0x50($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X50);
    // 0x802C6C9C: lw          $s1, 0x54($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X54);
    // 0x802C6CA0: lw          $s2, 0x58($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X58);
    // 0x802C6CA4: lw          $s3, 0x5C($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X5C);
    // 0x802C6CA8: lw          $s4, 0x60($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X60);
    // 0x802C6CAC: lw          $s5, 0x64($sp)
    ctx->r21 = MEM_W(ctx->r29, 0X64);
    // 0x802C6CB0: lw          $s6, 0x68($sp)
    ctx->r22 = MEM_W(ctx->r29, 0X68);
    // 0x802C6CB4: lw          $s7, 0x6C($sp)
    ctx->r23 = MEM_W(ctx->r29, 0X6C);
    // 0x802C6CB8: lw          $fp, 0x70($sp)
    ctx->r30 = MEM_W(ctx->r29, 0X70);
    // 0x802C6CBC: jr          $ra
    // 0x802C6CC0: addiu       $sp, $sp, 0x120
    ctx->r29 = ADD32(ctx->r29, 0X120);
    return;
    // 0x802C6CC0: addiu       $sp, $sp, 0x120
    ctx->r29 = ADD32(ctx->r29, 0X120);
;}
RECOMP_FUNC void func_i5_802C6CC4(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C6CC4: lui         $a2, 0x801D
    ctx->r6 = S32(0X801D << 16);
    // 0x802C6CC8: addiu       $a2, $a2, -0x19C0
    ctx->r6 = ADD32(ctx->r6, -0X19C0);
    // 0x802C6CCC: lw          $t6, 0x0($a2)
    ctx->r14 = MEM_W(ctx->r6, 0X0);
    // 0x802C6CD0: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x802C6CD4: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x802C6CD8: sltiu       $at, $t6, 0x8
    ctx->r1 = ctx->r14 < 0X8 ? 1 : 0;
    // 0x802C6CDC: beq         $at, $zero, L_802C6F5C
    if (ctx->r1 == 0) {
        // 0x802C6CE0: sw          $zero, 0x1C($sp)
        MEM_W(0X1C, ctx->r29) = 0;
            goto L_802C6F5C;
    }
    // 0x802C6CE0: sw          $zero, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = 0;
    // 0x802C6CE4: sll         $t6, $t6, 2
    ctx->r14 = S32(ctx->r14 << 2);
    // 0x802C6CE8: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C6CEC: addu        $at, $at, $t6
    gpr jr_addend_802C6CF4 = ctx->r14;
    ctx->r1 = ADD32(ctx->r1, ctx->r14);
    // 0x802C6CF0: lw          $t6, 0x7A74($at)
    ctx->r14 = ADD32(ctx->r1, 0X7A74);
    // 0x802C6CF4: jr          $t6
    // 0x802C6CF8: nop

    switch (jr_addend_802C6CF4 >> 2) {
        case 0: goto L_802C6CFC; break;
        case 1: goto L_802C6D1C; break;
        case 2: goto L_802C6D60; break;
        case 3: goto L_802C6DB4; break;
        case 4: goto L_802C6DF4; break;
        case 5: goto L_802C6E38; break;
        case 6: goto L_802C6ED0; break;
        case 7: goto L_802C6F2C; break;
        default: switch_error(__func__, 0x802C6CF4, 0x802C7A74);
    }
    // 0x802C6CF8: nop

L_802C6CFC:
    // 0x802C6CFC: lui         $t7, 0x8023
    ctx->r15 = S32(0X8023 << 16);
    // 0x802C6D00: lh          $t7, -0x75EA($t7)
    ctx->r15 = MEM_H(ctx->r15, -0X75EA);
    // 0x802C6D04: addiu       $v1, $zero, 0x1
    ctx->r3 = ADD32(0, 0X1);
    // 0x802C6D08: bnel        $v1, $t7, L_802C6F60
    if (ctx->r3 != ctx->r15) {
        // 0x802C6D0C: lw          $t3, 0x1C($sp)
        ctx->r11 = MEM_W(ctx->r29, 0X1C);
            goto L_802C6F60;
    }
    goto skip_0;
    // 0x802C6D0C: lw          $t3, 0x1C($sp)
    ctx->r11 = MEM_W(ctx->r29, 0X1C);
    skip_0:
    // 0x802C6D10: sw          $v1, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r3;
    // 0x802C6D14: b           L_802C6F5C
    // 0x802C6D18: sw          $v1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r3;
        goto L_802C6F5C;
    // 0x802C6D18: sw          $v1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r3;
L_802C6D1C:
    // 0x802C6D1C: lui         $v0, 0x802C
    ctx->r2 = S32(0X802C << 16);
    // 0x802C6D20: addiu       $v0, $v0, 0x7A00
    ctx->r2 = ADD32(ctx->r2, 0X7A00);
    // 0x802C6D24: lh          $t8, 0x0($v0)
    ctx->r24 = MEM_H(ctx->r2, 0X0);
    // 0x802C6D28: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x802C6D2C: addiu       $v1, $v1, -0x19BC
    ctx->r3 = ADD32(ctx->r3, -0X19BC);
    // 0x802C6D30: addiu       $t9, $t8, -0x14
    ctx->r25 = ADD32(ctx->r24, -0X14);
    // 0x802C6D34: sh          $t9, 0x0($v0)
    MEM_H(0X0, ctx->r2) = ctx->r25;
    // 0x802C6D38: lh          $t0, 0x0($v0)
    ctx->r8 = MEM_H(ctx->r2, 0X0);
    // 0x802C6D3C: addiu       $t1, $zero, 0x2
    ctx->r9 = ADD32(0, 0X2);
    // 0x802C6D40: addiu       $t2, $zero, 0x14
    ctx->r10 = ADD32(0, 0X14);
    // 0x802C6D44: slti        $at, $t0, 0x14
    ctx->r1 = SIGNED(ctx->r8) < 0X14 ? 1 : 0;
    // 0x802C6D48: beql        $at, $zero, L_802C6F60
    if (ctx->r1 == 0) {
        // 0x802C6D4C: lw          $t3, 0x1C($sp)
        ctx->r11 = MEM_W(ctx->r29, 0X1C);
            goto L_802C6F60;
    }
    goto skip_1;
    // 0x802C6D4C: lw          $t3, 0x1C($sp)
    ctx->r11 = MEM_W(ctx->r29, 0X1C);
    skip_1:
    // 0x802C6D50: sw          $t1, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r9;
    // 0x802C6D54: sh          $t2, 0x0($v0)
    MEM_H(0X0, ctx->r2) = ctx->r10;
    // 0x802C6D58: b           L_802C6F5C
    // 0x802C6D5C: sw          $zero, 0x0($v1)
    MEM_W(0X0, ctx->r3) = 0;
        goto L_802C6F5C;
    // 0x802C6D5C: sw          $zero, 0x0($v1)
    MEM_W(0X0, ctx->r3) = 0;
L_802C6D60:
    // 0x802C6D60: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x802C6D64: addiu       $v1, $v1, -0x19BC
    ctx->r3 = ADD32(ctx->r3, -0X19BC);
    // 0x802C6D68: lw          $v0, 0x0($v1)
    ctx->r2 = MEM_W(ctx->r3, 0X0);
    // 0x802C6D6C: lui         $t4, 0x801D
    ctx->r12 = S32(0X801D << 16);
    // 0x802C6D70: slti        $at, $v0, 0x3C
    ctx->r1 = SIGNED(ctx->r2) < 0X3C ? 1 : 0;
    // 0x802C6D74: beq         $at, $zero, L_802C6D84
    if (ctx->r1 == 0) {
        // 0x802C6D78: addiu       $t3, $v0, 0x1
        ctx->r11 = ADD32(ctx->r2, 0X1);
            goto L_802C6D84;
    }
    // 0x802C6D78: addiu       $t3, $v0, 0x1
    ctx->r11 = ADD32(ctx->r2, 0X1);
    // 0x802C6D7C: sw          $t3, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r11;
    // 0x802C6D80: or          $v0, $t3, $zero
    ctx->r2 = ctx->r11 | 0;
L_802C6D84:
    // 0x802C6D84: slti        $at, $v0, 0x1F
    ctx->r1 = SIGNED(ctx->r2) < 0X1F ? 1 : 0;
    // 0x802C6D88: bnel        $at, $zero, L_802C6F60
    if (ctx->r1 != 0) {
        // 0x802C6D8C: lw          $t3, 0x1C($sp)
        ctx->r11 = MEM_W(ctx->r29, 0X1C);
            goto L_802C6F60;
    }
    goto skip_2;
    // 0x802C6D8C: lw          $t3, 0x1C($sp)
    ctx->r11 = MEM_W(ctx->r29, 0X1C);
    skip_2:
    // 0x802C6D90: lhu         $t4, -0x19A6($t4)
    ctx->r12 = MEM_HU(ctx->r12, -0X19A6);
    // 0x802C6D94: addiu       $t6, $zero, 0x3
    ctx->r14 = ADD32(0, 0X3);
    // 0x802C6D98: addiu       $t7, $zero, 0x1
    ctx->r15 = ADD32(0, 0X1);
    // 0x802C6D9C: andi        $t5, $t4, 0xB000
    ctx->r13 = ctx->r12 & 0XB000;
    // 0x802C6DA0: beql        $t5, $zero, L_802C6F60
    if (ctx->r13 == 0) {
        // 0x802C6DA4: lw          $t3, 0x1C($sp)
        ctx->r11 = MEM_W(ctx->r29, 0X1C);
            goto L_802C6F60;
    }
    goto skip_3;
    // 0x802C6DA4: lw          $t3, 0x1C($sp)
    ctx->r11 = MEM_W(ctx->r29, 0X1C);
    skip_3:
    // 0x802C6DA8: sw          $t6, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r14;
    // 0x802C6DAC: b           L_802C6F5C
    // 0x802C6DB0: sw          $t7, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r15;
        goto L_802C6F5C;
    // 0x802C6DB0: sw          $t7, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r15;
L_802C6DB4:
    // 0x802C6DB4: lui         $v0, 0x802C
    ctx->r2 = S32(0X802C << 16);
    // 0x802C6DB8: addiu       $v0, $v0, 0x7A00
    ctx->r2 = ADD32(ctx->r2, 0X7A00);
    // 0x802C6DBC: lh          $t8, 0x0($v0)
    ctx->r24 = MEM_H(ctx->r2, 0X0);
    // 0x802C6DC0: addiu       $t1, $zero, 0x4
    ctx->r9 = ADD32(0, 0X4);
    // 0x802C6DC4: addiu       $t2, $zero, -0x171
    ctx->r10 = ADD32(0, -0X171);
    // 0x802C6DC8: addiu       $t9, $t8, -0x14
    ctx->r25 = ADD32(ctx->r24, -0X14);
    // 0x802C6DCC: sh          $t9, 0x0($v0)
    MEM_H(0X0, ctx->r2) = ctx->r25;
    // 0x802C6DD0: lh          $t0, 0x0($v0)
    ctx->r8 = MEM_H(ctx->r2, 0X0);
    // 0x802C6DD4: addiu       $t3, $zero, 0x1
    ctx->r11 = ADD32(0, 0X1);
    // 0x802C6DD8: slti        $at, $t0, -0x171
    ctx->r1 = SIGNED(ctx->r8) < -0X171 ? 1 : 0;
    // 0x802C6DDC: beql        $at, $zero, L_802C6F60
    if (ctx->r1 == 0) {
        // 0x802C6DE0: lw          $t3, 0x1C($sp)
        ctx->r11 = MEM_W(ctx->r29, 0X1C);
            goto L_802C6F60;
    }
    goto skip_4;
    // 0x802C6DE0: lw          $t3, 0x1C($sp)
    ctx->r11 = MEM_W(ctx->r29, 0X1C);
    skip_4:
    // 0x802C6DE4: sw          $t1, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r9;
    // 0x802C6DE8: sh          $t2, 0x0($v0)
    MEM_H(0X0, ctx->r2) = ctx->r10;
    // 0x802C6DEC: b           L_802C6F5C
    // 0x802C6DF0: sw          $t3, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r11;
        goto L_802C6F5C;
    // 0x802C6DF0: sw          $t3, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r11;
L_802C6DF4:
    // 0x802C6DF4: lui         $v0, 0x802C
    ctx->r2 = S32(0X802C << 16);
    // 0x802C6DF8: addiu       $v0, $v0, 0x7A00
    ctx->r2 = ADD32(ctx->r2, 0X7A00);
    // 0x802C6DFC: lh          $t4, 0x0($v0)
    ctx->r12 = MEM_H(ctx->r2, 0X0);
    // 0x802C6E00: lui         $v1, 0x802C
    ctx->r3 = S32(0X802C << 16);
    // 0x802C6E04: addiu       $v1, $v1, 0x7B0C
    ctx->r3 = ADD32(ctx->r3, 0X7B0C);
    // 0x802C6E08: addiu       $t5, $t4, 0x14
    ctx->r13 = ADD32(ctx->r12, 0X14);
    // 0x802C6E0C: sh          $t5, 0x0($v0)
    MEM_H(0X0, ctx->r2) = ctx->r13;
    // 0x802C6E10: lh          $t6, 0x0($v0)
    ctx->r14 = MEM_H(ctx->r2, 0X0);
    // 0x802C6E14: addiu       $t7, $zero, 0x5
    ctx->r15 = ADD32(0, 0X5);
    // 0x802C6E18: addiu       $t8, $zero, 0x14
    ctx->r24 = ADD32(0, 0X14);
    // 0x802C6E1C: slti        $at, $t6, 0x15
    ctx->r1 = SIGNED(ctx->r14) < 0X15 ? 1 : 0;
    // 0x802C6E20: bnel        $at, $zero, L_802C6F60
    if (ctx->r1 != 0) {
        // 0x802C6E24: lw          $t3, 0x1C($sp)
        ctx->r11 = MEM_W(ctx->r29, 0X1C);
            goto L_802C6F60;
    }
    goto skip_5;
    // 0x802C6E24: lw          $t3, 0x1C($sp)
    ctx->r11 = MEM_W(ctx->r29, 0X1C);
    skip_5:
    // 0x802C6E28: sw          $t7, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r15;
    // 0x802C6E2C: sh          $t8, 0x0($v0)
    MEM_H(0X0, ctx->r2) = ctx->r24;
    // 0x802C6E30: b           L_802C6F5C
    // 0x802C6E34: sw          $zero, 0x0($v1)
    MEM_W(0X0, ctx->r3) = 0;
        goto L_802C6F5C;
    // 0x802C6E34: sw          $zero, 0x0($v1)
    MEM_W(0X0, ctx->r3) = 0;
L_802C6E38:
    // 0x802C6E38: lui         $v1, 0x802C
    ctx->r3 = S32(0X802C << 16);
    // 0x802C6E3C: addiu       $v1, $v1, 0x7B0C
    ctx->r3 = ADD32(ctx->r3, 0X7B0C);
    // 0x802C6E40: lw          $v0, 0x0($v1)
    ctx->r2 = MEM_W(ctx->r3, 0X0);
    // 0x802C6E44: lui         $t0, 0x802C
    ctx->r8 = S32(0X802C << 16);
    // 0x802C6E48: slti        $at, $v0, 0x10
    ctx->r1 = SIGNED(ctx->r2) < 0X10 ? 1 : 0;
    // 0x802C6E4C: beq         $at, $zero, L_802C6E5C
    if (ctx->r1 == 0) {
        // 0x802C6E50: addiu       $t9, $v0, 0x1
        ctx->r25 = ADD32(ctx->r2, 0X1);
            goto L_802C6E5C;
    }
    // 0x802C6E50: addiu       $t9, $v0, 0x1
    ctx->r25 = ADD32(ctx->r2, 0X1);
    // 0x802C6E54: sw          $t9, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r25;
    // 0x802C6E58: or          $v0, $t9, $zero
    ctx->r2 = ctx->r25 | 0;
L_802C6E5C:
    // 0x802C6E5C: addiu       $at, $zero, 0x6
    ctx->r1 = ADD32(0, 0X6);
    // 0x802C6E60: bnel        $v0, $at, L_802C6E94
    if (ctx->r2 != ctx->r1) {
        // 0x802C6E64: slti        $at, $v0, 0x6
        ctx->r1 = SIGNED(ctx->r2) < 0X6 ? 1 : 0;
            goto L_802C6E94;
    }
    goto skip_6;
    // 0x802C6E64: slti        $at, $v0, 0x6
    ctx->r1 = SIGNED(ctx->r2) < 0X6 ? 1 : 0;
    skip_6:
    // 0x802C6E68: lw          $t0, 0x7B00($t0)
    ctx->r8 = MEM_W(ctx->r8, 0X7B00);
    // 0x802C6E6C: addiu       $v1, $zero, 0x1
    ctx->r3 = ADD32(0, 0X1);
    // 0x802C6E70: bnel        $v1, $t0, L_802C6E94
    if (ctx->r3 != ctx->r8) {
        // 0x802C6E74: slti        $at, $v0, 0x6
        ctx->r1 = SIGNED(ctx->r2) < 0X6 ? 1 : 0;
            goto L_802C6E94;
    }
    goto skip_7;
    // 0x802C6E74: slti        $at, $v0, 0x6
    ctx->r1 = SIGNED(ctx->r2) < 0X6 ? 1 : 0;
    skip_7:
    // 0x802C6E78: jal         0x800C3E4C
    // 0x802C6E7C: nop

    func_800C3E4C(rdram, ctx);
        goto after_0;
    // 0x802C6E7C: nop

    after_0:
    // 0x802C6E80: lui         $a2, 0x801D
    ctx->r6 = S32(0X801D << 16);
    // 0x802C6E84: lui         $v0, 0x802C
    ctx->r2 = S32(0X802C << 16);
    // 0x802C6E88: lw          $v0, 0x7B0C($v0)
    ctx->r2 = MEM_W(ctx->r2, 0X7B0C);
    // 0x802C6E8C: addiu       $a2, $a2, -0x19C0
    ctx->r6 = ADD32(ctx->r6, -0X19C0);
    // 0x802C6E90: slti        $at, $v0, 0x6
    ctx->r1 = SIGNED(ctx->r2) < 0X6 ? 1 : 0;
L_802C6E94:
    // 0x802C6E94: bne         $at, $zero, L_802C6F5C
    if (ctx->r1 != 0) {
        // 0x802C6E98: lui         $t1, 0x801D
        ctx->r9 = S32(0X801D << 16);
            goto L_802C6F5C;
    }
    // 0x802C6E98: lui         $t1, 0x801D
    ctx->r9 = S32(0X801D << 16);
    // 0x802C6E9C: lhu         $t1, -0x19A6($t1)
    ctx->r9 = MEM_HU(ctx->r9, -0X19A6);
    // 0x802C6EA0: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x802C6EA4: addiu       $v1, $v1, -0x19BC
    ctx->r3 = ADD32(ctx->r3, -0X19BC);
    // 0x802C6EA8: andi        $t2, $t1, 0xB000
    ctx->r10 = ctx->r9 & 0XB000;
    // 0x802C6EAC: beq         $t2, $zero, L_802C6F5C
    if (ctx->r10 == 0) {
        // 0x802C6EB0: addiu       $t3, $zero, 0x6
        ctx->r11 = ADD32(0, 0X6);
            goto L_802C6F5C;
    }
    // 0x802C6EB0: addiu       $t3, $zero, 0x6
    ctx->r11 = ADD32(0, 0X6);
    // 0x802C6EB4: sw          $t3, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r11;
    // 0x802C6EB8: sw          $zero, 0x0($v1)
    MEM_W(0X0, ctx->r3) = 0;
    // 0x802C6EBC: addiu       $a0, $zero, 0x11
    ctx->r4 = ADD32(0, 0X11);
    // 0x802C6EC0: jal         0x800C37F4
    // 0x802C6EC4: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_1;
    // 0x802C6EC4: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_1:
    // 0x802C6EC8: b           L_802C6F60
    // 0x802C6ECC: lw          $t3, 0x1C($sp)
    ctx->r11 = MEM_W(ctx->r29, 0X1C);
        goto L_802C6F60;
    // 0x802C6ECC: lw          $t3, 0x1C($sp)
    ctx->r11 = MEM_W(ctx->r29, 0X1C);
L_802C6ED0:
    // 0x802C6ED0: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x802C6ED4: addiu       $v1, $v1, -0x19BC
    ctx->r3 = ADD32(ctx->r3, -0X19BC);
    // 0x802C6ED8: lw          $t4, 0x0($v1)
    ctx->r12 = MEM_W(ctx->r3, 0X0);
    // 0x802C6EDC: lui         $a0, 0x802C
    ctx->r4 = S32(0X802C << 16);
    // 0x802C6EE0: addiu       $t5, $t4, 0x1
    ctx->r13 = ADD32(ctx->r12, 0X1);
    // 0x802C6EE4: slti        $at, $t5, 0x1E
    ctx->r1 = SIGNED(ctx->r13) < 0X1E ? 1 : 0;
    // 0x802C6EE8: bne         $at, $zero, L_802C6F5C
    if (ctx->r1 != 0) {
        // 0x802C6EEC: sw          $t5, 0x0($v1)
        MEM_W(0X0, ctx->r3) = ctx->r13;
            goto L_802C6F5C;
    }
    // 0x802C6EEC: sw          $t5, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r13;
    // 0x802C6EF0: lw          $a0, 0x7B08($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X7B08);
    // 0x802C6EF4: addiu       $at, $zero, 0x5A
    ctx->r1 = ADD32(0, 0X5A);
    // 0x802C6EF8: addiu       $t7, $zero, 0x7
    ctx->r15 = ADD32(0, 0X7);
    // 0x802C6EFC: beq         $a0, $at, L_802C6F14
    if (ctx->r4 == ctx->r1) {
        // 0x802C6F00: addiu       $t8, $zero, 0x1
        ctx->r24 = ADD32(0, 0X1);
            goto L_802C6F14;
    }
    // 0x802C6F00: addiu       $t8, $zero, 0x1
    ctx->r24 = ADD32(0, 0X1);
    // 0x802C6F04: jal         0x802C6F84
    // 0x802C6F08: nop

    func_i5_802C6F84(rdram, ctx);
        goto after_2;
    // 0x802C6F08: nop

    after_2:
    // 0x802C6F0C: b           L_802C6F60
    // 0x802C6F10: lw          $t3, 0x1C($sp)
    ctx->r11 = MEM_W(ctx->r29, 0X1C);
        goto L_802C6F60;
    // 0x802C6F10: lw          $t3, 0x1C($sp)
    ctx->r11 = MEM_W(ctx->r29, 0X1C);
L_802C6F14:
    // 0x802C6F14: sw          $t7, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r15;
    // 0x802C6F18: sw          $t8, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r24;
    // 0x802C6F1C: jal         0x800C1F60
    // 0x802C6F20: addiu       $a0, $zero, 0x5
    ctx->r4 = ADD32(0, 0X5);
    func_800C1F60(rdram, ctx);
        goto after_3;
    // 0x802C6F20: addiu       $a0, $zero, 0x5
    ctx->r4 = ADD32(0, 0X5);
    after_3:
    // 0x802C6F24: b           L_802C6F60
    // 0x802C6F28: lw          $t3, 0x1C($sp)
    ctx->r11 = MEM_W(ctx->r29, 0X1C);
        goto L_802C6F60;
    // 0x802C6F28: lw          $t3, 0x1C($sp)
    ctx->r11 = MEM_W(ctx->r29, 0X1C);
L_802C6F2C:
    // 0x802C6F2C: lui         $v0, 0x802C
    ctx->r2 = S32(0X802C << 16);
    // 0x802C6F30: addiu       $v0, $v0, 0x7A00
    ctx->r2 = ADD32(ctx->r2, 0X7A00);
    // 0x802C6F34: lh          $t9, 0x0($v0)
    ctx->r25 = MEM_H(ctx->r2, 0X0);
    // 0x802C6F38: addiu       $t2, $zero, 0x140
    ctx->r10 = ADD32(0, 0X140);
    // 0x802C6F3C: addiu       $t0, $t9, 0x14
    ctx->r8 = ADD32(ctx->r25, 0X14);
    // 0x802C6F40: sh          $t0, 0x0($v0)
    MEM_H(0X0, ctx->r2) = ctx->r8;
    // 0x802C6F44: lh          $t1, 0x0($v0)
    ctx->r9 = MEM_H(ctx->r2, 0X0);
    // 0x802C6F48: slti        $at, $t1, 0x141
    ctx->r1 = SIGNED(ctx->r9) < 0X141 ? 1 : 0;
    // 0x802C6F4C: bnel        $at, $zero, L_802C6F60
    if (ctx->r1 != 0) {
        // 0x802C6F50: lw          $t3, 0x1C($sp)
        ctx->r11 = MEM_W(ctx->r29, 0X1C);
            goto L_802C6F60;
    }
    goto skip_8;
    // 0x802C6F50: lw          $t3, 0x1C($sp)
    ctx->r11 = MEM_W(ctx->r29, 0X1C);
    skip_8:
    // 0x802C6F54: jal         0x801EC944
    // 0x802C6F58: sh          $t2, 0x0($v0)
    MEM_H(0X0, ctx->r2) = ctx->r10;
    func_801EC944(rdram, ctx);
        goto after_4;
    // 0x802C6F58: sh          $t2, 0x0($v0)
    MEM_H(0X0, ctx->r2) = ctx->r10;
    after_4:
L_802C6F5C:
    // 0x802C6F5C: lw          $t3, 0x1C($sp)
    ctx->r11 = MEM_W(ctx->r29, 0X1C);
L_802C6F60:
    // 0x802C6F60: addiu       $a0, $zero, 0x31
    ctx->r4 = ADD32(0, 0X31);
    // 0x802C6F64: beql        $t3, $zero, L_802C6F78
    if (ctx->r11 == 0) {
        // 0x802C6F68: lw          $ra, 0x14($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X14);
            goto L_802C6F78;
    }
    goto skip_9;
    // 0x802C6F68: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    skip_9:
    // 0x802C6F6C: jal         0x800C37F4
    // 0x802C6F70: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_5;
    // 0x802C6F70: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_5:
    // 0x802C6F74: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C6F78:
    // 0x802C6F78: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x802C6F7C: jr          $ra
    // 0x802C6F80: nop

    return;
    // 0x802C6F80: nop

;}
RECOMP_FUNC void func_i5_802C6F84(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C6F84: lui         $v1, 0x800E
    ctx->r3 = S32(0X800E << 16);
    // 0x802C6F88: addiu       $v1, $v1, -0x54DC
    ctx->r3 = ADD32(ctx->r3, -0X54DC);
    // 0x802C6F8C: lw          $t6, 0x0($v1)
    ctx->r14 = MEM_W(ctx->r3, 0X0);
    // 0x802C6F90: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C6F94: lui         $a3, 0x801D
    ctx->r7 = S32(0X801D << 16);
    // 0x802C6F98: sw          $t6, -0x19CC($at)
    MEM_W(-0X19CC, ctx->r1) = ctx->r14;
    // 0x802C6F9C: addiu       $a3, $a3, -0x19D0
    ctx->r7 = ADD32(ctx->r7, -0X19D0);
    // 0x802C6FA0: addiu       $t7, $zero, 0x35
    ctx->r15 = ADD32(0, 0X35);
    // 0x802C6FA4: sw          $a0, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r4;
    // 0x802C6FA8: sw          $t7, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r15;
    // 0x802C6FAC: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C6FB0: addiu       $t8, $zero, 0x9
    ctx->r24 = ADD32(0, 0X9);
    // 0x802C6FB4: sw          $t8, -0x19C8($at)
    MEM_W(-0X19C8, ctx->r1) = ctx->r24;
    // 0x802C6FB8: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C6FBC: addiu       $t9, $zero, 0x1
    ctx->r25 = ADD32(0, 0X1);
    // 0x802C6FC0: sw          $t9, -0x19C4($at)
    MEM_W(-0X19C4, ctx->r1) = ctx->r25;
    // 0x802C6FC4: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C6FC8: sw          $zero, -0x19BC($at)
    MEM_W(-0X19BC, ctx->r1) = 0;
    // 0x802C6FCC: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x802C6FD0: sw          $zero, -0x54E4($at)
    MEM_W(-0X54E4, ctx->r1) = 0;
    // 0x802C6FD4: lui         $at, 0x800D
    ctx->r1 = S32(0X800D << 16);
    // 0x802C6FD8: addiu       $t0, $zero, 0x2
    ctx->r8 = ADD32(0, 0X2);
    // 0x802C6FDC: sw          $t0, 0x461C($at)
    MEM_W(0X461C, ctx->r1) = ctx->r8;
    // 0x802C6FE0: lw          $v0, 0x0($a3)
    ctx->r2 = MEM_W(ctx->r7, 0X0);
    // 0x802C6FE4: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x802C6FE8: addiu       $at, $zero, 0x66
    ctx->r1 = ADD32(0, 0X66);
    // 0x802C6FEC: bne         $v0, $at, L_802C700C
    if (ctx->r2 != ctx->r1) {
        // 0x802C6FF0: sw          $ra, 0x14($sp)
        MEM_W(0X14, ctx->r29) = ctx->r31;
            goto L_802C700C;
    }
    // 0x802C6FF0: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x802C6FF4: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    // 0x802C6FF8: addiu       $a1, $zero, 0x4
    ctx->r5 = ADD32(0, 0X4);
    // 0x802C6FFC: jal         0x801E6FB0
    // 0x802C7000: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    FadeTransition_SetProps(rdram, ctx);
        goto after_0;
    // 0x802C7000: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    after_0:
    // 0x802C7004: b           L_802C703C
    // 0x802C7008: nop

        goto L_802C703C;
    // 0x802C7008: nop

L_802C700C:
    // 0x802C700C: addiu       $at, $zero, 0x1E
    ctx->r1 = ADD32(0, 0X1E);
    // 0x802C7010: bne         $v0, $at, L_802C7030
    if (ctx->r2 != ctx->r1) {
        // 0x802C7014: addiu       $a0, $zero, 0x5
        ctx->r4 = ADD32(0, 0X5);
            goto L_802C7030;
    }
    // 0x802C7014: addiu       $a0, $zero, 0x5
    ctx->r4 = ADD32(0, 0X5);
    // 0x802C7018: addiu       $a0, $zero, 0x5
    ctx->r4 = ADD32(0, 0X5);
    // 0x802C701C: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C7020: jal         0x801E6FB0
    // 0x802C7024: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    FadeTransition_SetProps(rdram, ctx);
        goto after_1;
    // 0x802C7024: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    after_1:
    // 0x802C7028: b           L_802C703C
    // 0x802C702C: nop

        goto L_802C703C;
    // 0x802C702C: nop

L_802C7030:
    // 0x802C7030: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C7034: jal         0x801E6FB0
    // 0x802C7038: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    FadeTransition_SetProps(rdram, ctx);
        goto after_2;
    // 0x802C7038: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    after_2:
L_802C703C:
    // 0x802C703C: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x802C7040: lw          $v0, -0x19D0($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X19D0);
    // 0x802C7044: addiu       $at, $zero, 0x66
    ctx->r1 = ADD32(0, 0X66);
    // 0x802C7048: bnel        $v0, $at, L_802C7064
    if (ctx->r2 != ctx->r1) {
        // 0x802C704C: addiu       $at, $zero, 0x1E
        ctx->r1 = ADD32(0, 0X1E);
            goto L_802C7064;
    }
    goto skip_0;
    // 0x802C704C: addiu       $at, $zero, 0x1E
    ctx->r1 = ADD32(0, 0X1E);
    skip_0:
    // 0x802C7050: jal         0x800C1F60
    // 0x802C7054: addiu       $a0, $zero, 0xB
    ctx->r4 = ADD32(0, 0XB);
    func_800C1F60(rdram, ctx);
        goto after_3;
    // 0x802C7054: addiu       $a0, $zero, 0xB
    ctx->r4 = ADD32(0, 0XB);
    after_3:
    // 0x802C7058: b           L_802C7078
    // 0x802C705C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_802C7078;
    // 0x802C705C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x802C7060: addiu       $at, $zero, 0x1E
    ctx->r1 = ADD32(0, 0X1E);
L_802C7064:
    // 0x802C7064: bnel        $v0, $at, L_802C7078
    if (ctx->r2 != ctx->r1) {
        // 0x802C7068: lw          $ra, 0x14($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X14);
            goto L_802C7078;
    }
    goto skip_1;
    // 0x802C7068: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    skip_1:
    // 0x802C706C: jal         0x800C1F60
    // 0x802C7070: addiu       $a0, $zero, 0x2
    ctx->r4 = ADD32(0, 0X2);
    func_800C1F60(rdram, ctx);
        goto after_4;
    // 0x802C7070: addiu       $a0, $zero, 0x2
    ctx->r4 = ADD32(0, 0X2);
    after_4:
    // 0x802C7074: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C7078:
    // 0x802C7078: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x802C707C: jr          $ra
    // 0x802C7080: nop

    return;
    // 0x802C7080: nop

    // 0x802C7084: nop

    // 0x802C7088: nop

    // 0x802C708C: nop

;}
RECOMP_FUNC void func_i5_802C7090(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C7090: addiu       $sp, $sp, -0x98
    ctx->r29 = ADD32(ctx->r29, -0X98);
    // 0x802C7094: lui         $t6, 0x801D
    ctx->r14 = S32(0X801D << 16);
    // 0x802C7098: lw          $t6, -0x19C4($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X19C4);
    // 0x802C709C: sw          $ra, 0x6C($sp)
    MEM_W(0X6C, ctx->r29) = ctx->r31;
    // 0x802C70A0: sw          $s5, 0x68($sp)
    MEM_W(0X68, ctx->r29) = ctx->r21;
    // 0x802C70A4: sw          $s4, 0x64($sp)
    MEM_W(0X64, ctx->r29) = ctx->r20;
    // 0x802C70A8: sw          $s3, 0x60($sp)
    MEM_W(0X60, ctx->r29) = ctx->r19;
    // 0x802C70AC: sw          $s2, 0x5C($sp)
    MEM_W(0X5C, ctx->r29) = ctx->r18;
    // 0x802C70B0: sw          $s1, 0x58($sp)
    MEM_W(0X58, ctx->r29) = ctx->r17;
    // 0x802C70B4: sw          $s0, 0x54($sp)
    MEM_W(0X54, ctx->r29) = ctx->r16;
    // 0x802C70B8: sdc1        $f26, 0x48($sp)
    CHECK_FR(ctx, 26);
    SD(ctx->f26.u64, 0X48, ctx->r29);
    // 0x802C70BC: sdc1        $f24, 0x40($sp)
    CHECK_FR(ctx, 24);
    SD(ctx->f24.u64, 0X40, ctx->r29);
    // 0x802C70C0: sdc1        $f22, 0x38($sp)
    CHECK_FR(ctx, 22);
    SD(ctx->f22.u64, 0X38, ctx->r29);
    // 0x802C70C4: beq         $t6, $zero, L_802C729C
    if (ctx->r14 == 0) {
        // 0x802C70C8: sdc1        $f20, 0x30($sp)
        CHECK_FR(ctx, 20);
    SD(ctx->f20.u64, 0X30, ctx->r29);
            goto L_802C729C;
    }
    // 0x802C70C8: sdc1        $f20, 0x30($sp)
    CHECK_FR(ctx, 20);
    SD(ctx->f20.u64, 0X30, ctx->r29);
    // 0x802C70CC: lui         $t7, 0x800E
    ctx->r15 = S32(0X800E << 16);
    // 0x802C70D0: lw          $t7, -0x54DC($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X54DC);
    // 0x802C70D4: addiu       $at, $zero, 0x5A
    ctx->r1 = ADD32(0, 0X5A);
    // 0x802C70D8: lui         $t8, 0x800D
    ctx->r24 = S32(0X800D << 16);
    // 0x802C70DC: bne         $t7, $at, L_802C729C
    if (ctx->r15 != ctx->r1) {
        // 0x802C70E0: lui         $t4, 0x801D
        ctx->r12 = S32(0X801D << 16);
            goto L_802C729C;
    }
    // 0x802C70E0: lui         $t4, 0x801D
    ctx->r12 = S32(0X801D << 16);
    // 0x802C70E4: lw          $t8, 0x48DC($t8)
    ctx->r24 = MEM_W(ctx->r24, 0X48DC);
    // 0x802C70E8: lui         $t5, 0x801D
    ctx->r13 = S32(0X801D << 16);
    // 0x802C70EC: lui         $t7, 0x801D
    ctx->r15 = S32(0X801D << 16);
    // 0x802C70F0: sll         $t9, $t8, 2
    ctx->r25 = S32(ctx->r24 << 2);
    // 0x802C70F4: addu        $t4, $t4, $t9
    ctx->r12 = ADD32(ctx->r12, ctx->r25);
    // 0x802C70F8: lw          $t4, -0x4CC0($t4)
    ctx->r12 = MEM_W(ctx->r12, -0X4CC0);
    // 0x802C70FC: lw          $t7, -0x4CCC($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X4CCC);
    // 0x802C7100: lw          $t5, -0x4CC8($t5)
    ctx->r13 = MEM_W(ctx->r13, -0X4CC8);
    // 0x802C7104: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C7108: sw          $t4, 0x7B30($at)
    MEM_W(0X7B30, ctx->r1) = ctx->r12;
    // 0x802C710C: sll         $t8, $t7, 1
    ctx->r24 = S32(ctx->r15 << 1);
    // 0x802C7110: sll         $t6, $t5, 4
    ctx->r14 = S32(ctx->r13 << 4);
    // 0x802C7114: addu        $t9, $t6, $t8
    ctx->r25 = ADD32(ctx->r14, ctx->r24);
    // 0x802C7118: lui         $t4, 0x800F
    ctx->r12 = S32(0X800F << 16);
    // 0x802C711C: addu        $t4, $t4, $t9
    ctx->r12 = ADD32(ctx->r12, ctx->r25);
    // 0x802C7120: lh          $t4, -0x5444($t4)
    ctx->r12 = MEM_H(ctx->r12, -0X5444);
    // 0x802C7124: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C7128: lui         $s3, 0x802C
    ctx->r19 = S32(0X802C << 16);
    // 0x802C712C: lui         $s5, 0x802C
    ctx->r21 = S32(0X802C << 16);
    // 0x802C7130: lui         $s4, 0x802C
    ctx->r20 = S32(0X802C << 16);
    // 0x802C7134: addiu       $s4, $s4, 0x7B80
    ctx->r20 = ADD32(ctx->r20, 0X7B80);
    // 0x802C7138: addiu       $s5, $s5, 0x7B40
    ctx->r21 = ADD32(ctx->r21, 0X7B40);
    // 0x802C713C: addiu       $s3, $s3, 0x7B38
    ctx->r19 = ADD32(ctx->r19, 0X7B38);
    // 0x802C7140: sw          $t4, 0x7B34($at)
    MEM_W(0X7B34, ctx->r1) = ctx->r12;
L_802C7144:
    // 0x802C7144: lui         $t5, 0x802C
    ctx->r13 = S32(0X802C << 16);
    // 0x802C7148: addiu       $t5, $t5, 0x7B80
    ctx->r13 = ADD32(ctx->r13, 0X7B80);
    // 0x802C714C: bne         $s4, $t5, L_802C7168
    if (ctx->r20 != ctx->r13) {
        // 0x802C7150: lui         $a0, 0x80B
        ctx->r4 = S32(0X80B << 16);
            goto L_802C7168;
    }
    // 0x802C7150: lui         $a0, 0x80B
    ctx->r4 = S32(0X80B << 16);
    // 0x802C7154: lui         $a0, 0x80B
    ctx->r4 = S32(0X80B << 16);
    // 0x802C7158: jal         0x80094088
    // 0x802C715C: addiu       $a0, $a0, 0xE28
    ctx->r4 = ADD32(ctx->r4, 0XE28);
    SegmentedToVirtual(rdram, ctx);
        goto after_0;
    // 0x802C715C: addiu       $a0, $a0, 0xE28
    ctx->r4 = ADD32(ctx->r4, 0XE28);
    after_0:
    // 0x802C7160: b           L_802C7174
    // 0x802C7164: sw          $v0, 0x0($s3)
    MEM_W(0X0, ctx->r19) = ctx->r2;
        goto L_802C7174;
    // 0x802C7164: sw          $v0, 0x0($s3)
    MEM_W(0X0, ctx->r19) = ctx->r2;
L_802C7168:
    // 0x802C7168: jal         0x80094088
    // 0x802C716C: addiu       $a0, $a0, 0x1550
    ctx->r4 = ADD32(ctx->r4, 0X1550);
    SegmentedToVirtual(rdram, ctx);
        goto after_1;
    // 0x802C716C: addiu       $a0, $a0, 0x1550
    ctx->r4 = ADD32(ctx->r4, 0X1550);
    after_1:
    // 0x802C7170: sw          $v0, 0x0($s3)
    MEM_W(0X0, ctx->r19) = ctx->r2;
L_802C7174:
    // 0x802C7174: or          $s1, $zero, $zero
    ctx->r17 = 0 | 0;
    // 0x802C7178: or          $s2, $zero, $zero
    ctx->r18 = 0 | 0;
    // 0x802C717C: or          $s0, $s5, $zero
    ctx->r16 = ctx->r21 | 0;
L_802C7180:
    // 0x802C7180: lw          $t7, 0x0($s3)
    ctx->r15 = MEM_W(ctx->r19, 0X0);
    // 0x802C7184: addu        $t6, $t7, $s2
    ctx->r14 = ADD32(ctx->r15, ctx->r18);
    // 0x802C7188: jal         0x80094088
    // 0x802C718C: lw          $a0, 0x8($t6)
    ctx->r4 = MEM_W(ctx->r14, 0X8);
    SegmentedToVirtual(rdram, ctx);
        goto after_2;
    // 0x802C718C: lw          $a0, 0x8($t6)
    ctx->r4 = MEM_W(ctx->r14, 0X8);
    after_2:
    // 0x802C7190: addiu       $s1, $s1, 0x1
    ctx->r17 = ADD32(ctx->r17, 0X1);
    // 0x802C7194: slti        $at, $s1, 0x8
    ctx->r1 = SIGNED(ctx->r17) < 0X8 ? 1 : 0;
    // 0x802C7198: addiu       $s2, $s2, 0x4
    ctx->r18 = ADD32(ctx->r18, 0X4);
    // 0x802C719C: addiu       $s0, $s0, 0x4
    ctx->r16 = ADD32(ctx->r16, 0X4);
    // 0x802C71A0: bne         $at, $zero, L_802C7180
    if (ctx->r1 != 0) {
        // 0x802C71A4: sw          $v0, -0x4($s0)
        MEM_W(-0X4, ctx->r16) = ctx->r2;
            goto L_802C7180;
    }
    // 0x802C71A4: sw          $v0, -0x4($s0)
    MEM_W(-0X4, ctx->r16) = ctx->r2;
    // 0x802C71A8: lw          $t8, 0x0($s3)
    ctx->r24 = MEM_W(ctx->r19, 0X0);
    // 0x802C71AC: jal         0x80094088
    // 0x802C71B0: lw          $a0, 0x4($t8)
    ctx->r4 = MEM_W(ctx->r24, 0X4);
    SegmentedToVirtual(rdram, ctx);
        goto after_3;
    // 0x802C71B0: lw          $a0, 0x4($t8)
    ctx->r4 = MEM_W(ctx->r24, 0X4);
    after_3:
    // 0x802C71B4: lui         $t9, 0x802C
    ctx->r25 = S32(0X802C << 16);
    // 0x802C71B8: addiu       $t9, $t9, 0x7B88
    ctx->r25 = ADD32(ctx->r25, 0X7B88);
    // 0x802C71BC: addiu       $s4, $s4, 0x4
    ctx->r20 = ADD32(ctx->r20, 0X4);
    // 0x802C71C0: sltu        $at, $s4, $t9
    ctx->r1 = ctx->r20 < ctx->r25 ? 1 : 0;
    // 0x802C71C4: addiu       $s3, $s3, 0x4
    ctx->r19 = ADD32(ctx->r19, 0X4);
    // 0x802C71C8: addiu       $s5, $s5, 0x20
    ctx->r21 = ADD32(ctx->r21, 0X20);
    // 0x802C71CC: bne         $at, $zero, L_802C7144
    if (ctx->r1 != 0) {
        // 0x802C71D0: sw          $v0, -0x4($s4)
        MEM_W(-0X4, ctx->r20) = ctx->r2;
            goto L_802C7144;
    }
    // 0x802C71D0: sw          $v0, -0x4($s4)
    MEM_W(-0X4, ctx->r20) = ctx->r2;
    // 0x802C71D4: lui         $t0, 0x802C
    ctx->r8 = S32(0X802C << 16);
    // 0x802C71D8: lui         $t3, 0x802C
    ctx->r11 = S32(0X802C << 16);
    // 0x802C71DC: addiu       $t3, $t3, 0x7B8C
    ctx->r11 = ADD32(ctx->r11, 0X7B8C);
    // 0x802C71E0: addiu       $t0, $t0, 0x7B90
    ctx->r8 = ADD32(ctx->r8, 0X7B90);
    // 0x802C71E4: sw          $zero, 0x0($t0)
    MEM_W(0X0, ctx->r8) = 0;
    // 0x802C71E8: sw          $zero, 0x0($t3)
    MEM_W(0X0, ctx->r11) = 0;
    // 0x802C71EC: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x802C71F0: lw          $v0, -0x4CCC($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X4CCC);
    // 0x802C71F4: mtc1        $zero, $f26
    ctx->f26.u32l = 0;
    // 0x802C71F8: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    // 0x802C71FC: addiu       $v0, $v0, 0x1
    ctx->r2 = ADD32(ctx->r2, 0X1);
    // 0x802C7200: blez        $v0, L_802C7274
    if (SIGNED(ctx->r2) <= 0) {
        // 0x802C7204: lui         $t5, 0x801D
        ctx->r13 = S32(0X801D << 16);
            goto L_802C7274;
    }
    // 0x802C7204: lui         $t5, 0x801D
    ctx->r13 = S32(0X801D << 16);
    // 0x802C7208: lw          $t5, -0x4CC8($t5)
    ctx->r13 = MEM_W(ctx->r13, -0X4CC8);
    // 0x802C720C: lui         $t6, 0x800F
    ctx->r14 = S32(0X800F << 16);
    // 0x802C7210: addiu       $t6, $t6, -0x53EC
    ctx->r14 = ADD32(ctx->r14, -0X53EC);
    // 0x802C7214: lui         $t2, 0x801C
    ctx->r10 = S32(0X801C << 16);
    // 0x802C7218: lui         $t1, 0x801C
    ctx->r9 = S32(0X801C << 16);
    // 0x802C721C: sll         $t7, $t5, 4
    ctx->r15 = S32(ctx->r13 << 4);
    // 0x802C7220: addu        $a1, $t7, $t6
    ctx->r5 = ADD32(ctx->r15, ctx->r14);
    // 0x802C7224: addiu       $t1, $t1, 0x2660
    ctx->r9 = ADD32(ctx->r9, 0X2660);
    // 0x802C7228: addiu       $t2, $t2, 0x2690
    ctx->r10 = ADD32(ctx->r10, 0X2690);
    // 0x802C722C: sll         $a3, $v0, 1
    ctx->r7 = S32(ctx->r2 << 1);
    // 0x802C7230: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
L_802C7234:
    // 0x802C7234: lh          $v0, 0x0($a1)
    ctx->r2 = MEM_H(ctx->r5, 0X0);
    // 0x802C7238: addiu       $a0, $a0, 0x2
    ctx->r4 = ADD32(ctx->r4, 0X2);
    // 0x802C723C: slt         $at, $a0, $a3
    ctx->r1 = SIGNED(ctx->r4) < SIGNED(ctx->r7) ? 1 : 0;
    // 0x802C7240: sll         $v1, $v0, 2
    ctx->r3 = S32(ctx->r2 << 2);
    // 0x802C7244: addu        $t8, $t1, $v1
    ctx->r24 = ADD32(ctx->r9, ctx->r3);
    // 0x802C7248: lw          $t9, 0x0($t8)
    ctx->r25 = MEM_W(ctx->r24, 0X0);
    // 0x802C724C: addu        $t4, $t2, $v1
    ctx->r12 = ADD32(ctx->r10, ctx->r3);
    // 0x802C7250: beql        $t9, $zero, L_802C7260
    if (ctx->r25 == 0) {
        // 0x802C7254: lw          $t5, 0x0($t4)
        ctx->r13 = MEM_W(ctx->r12, 0X0);
            goto L_802C7260;
    }
    goto skip_0;
    // 0x802C7254: lw          $t5, 0x0($t4)
    ctx->r13 = MEM_W(ctx->r12, 0X0);
    skip_0:
    // 0x802C7258: sw          $a2, 0x0($t3)
    MEM_W(0X0, ctx->r11) = ctx->r6;
    // 0x802C725C: lw          $t5, 0x0($t4)
    ctx->r13 = MEM_W(ctx->r12, 0X0);
L_802C7260:
    // 0x802C7260: beq         $t5, $zero, L_802C726C
    if (ctx->r13 == 0) {
        // 0x802C7264: nop
    
            goto L_802C726C;
    }
    // 0x802C7264: nop

    // 0x802C7268: sw          $a2, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r6;
L_802C726C:
    // 0x802C726C: bne         $at, $zero, L_802C7234
    if (ctx->r1 != 0) {
        // 0x802C7270: addiu       $a1, $a1, 0x2
        ctx->r5 = ADD32(ctx->r5, 0X2);
            goto L_802C7234;
    }
    // 0x802C7270: addiu       $a1, $a1, 0x2
    ctx->r5 = ADD32(ctx->r5, 0X2);
L_802C7274:
    // 0x802C7274: lui         $v0, 0x802C
    ctx->r2 = S32(0X802C << 16);
    // 0x802C7278: lui         $v1, 0x802C
    ctx->r3 = S32(0X802C << 16);
    // 0x802C727C: addiu       $v1, $v1, 0x7B30
    ctx->r3 = ADD32(ctx->r3, 0X7B30);
    // 0x802C7280: addiu       $v0, $v0, 0x7B10
    ctx->r2 = ADD32(ctx->r2, 0X7B10);
L_802C7284:
    // 0x802C7284: addiu       $v0, $v0, 0x10
    ctx->r2 = ADD32(ctx->r2, 0X10);
    // 0x802C7288: swc1        $f26, -0x10($v0)
    MEM_W(-0X10, ctx->r2) = ctx->f26.u32l;
    // 0x802C728C: swc1        $f26, -0xC($v0)
    MEM_W(-0XC, ctx->r2) = ctx->f26.u32l;
    // 0x802C7290: swc1        $f26, -0x8($v0)
    MEM_W(-0X8, ctx->r2) = ctx->f26.u32l;
    // 0x802C7294: bne         $v0, $v1, L_802C7284
    if (ctx->r2 != ctx->r3) {
        // 0x802C7298: swc1        $f26, -0x4($v0)
        MEM_W(-0X4, ctx->r2) = ctx->f26.u32l;
            goto L_802C7284;
    }
    // 0x802C7298: swc1        $f26, -0x4($v0)
    MEM_W(-0X4, ctx->r2) = ctx->f26.u32l;
L_802C729C:
    // 0x802C729C: lui         $v0, 0x802C
    ctx->r2 = S32(0X802C << 16);
    // 0x802C72A0: lw          $v0, 0x7AC8($v0)
    ctx->r2 = MEM_W(ctx->r2, 0X7AC8);
    // 0x802C72A4: mtc1        $zero, $f26
    ctx->f26.u32l = 0;
    // 0x802C72A8: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x802C72AC: beq         $v0, $at, L_802C72C8
    if (ctx->r2 == ctx->r1) {
        // 0x802C72B0: or          $s2, $zero, $zero
        ctx->r18 = 0 | 0;
            goto L_802C72C8;
    }
    // 0x802C72B0: or          $s2, $zero, $zero
    ctx->r18 = 0 | 0;
    // 0x802C72B4: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x802C72B8: beql        $v0, $at, L_802C72CC
    if (ctx->r2 == ctx->r1) {
        // 0x802C72BC: or          $v0, $zero, $zero
        ctx->r2 = 0 | 0;
            goto L_802C72CC;
    }
    goto skip_1;
    // 0x802C72BC: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    skip_1:
    // 0x802C72C0: b           L_802C72CC
    // 0x802C72C4: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
        goto L_802C72CC;
    // 0x802C72C4: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
L_802C72C8:
    // 0x802C72C8: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_802C72CC:
    // 0x802C72CC: lui         $t6, 0x802C
    ctx->r14 = S32(0X802C << 16);
    // 0x802C72D0: lui         $t9, 0x802C
    ctx->r25 = S32(0X802C << 16);
    // 0x802C72D4: lui         $at, 0x4120
    ctx->r1 = S32(0X4120 << 16);
    // 0x802C72D8: addiu       $t9, $t9, 0x7B80
    ctx->r25 = ADD32(ctx->r25, 0X7B80);
    // 0x802C72DC: addiu       $t6, $t6, 0x7B40
    ctx->r14 = ADD32(ctx->r14, 0X7B40);
    // 0x802C72E0: sll         $t7, $v0, 5
    ctx->r15 = S32(ctx->r2 << 5);
    // 0x802C72E4: sll         $t8, $v0, 2
    ctx->r24 = S32(ctx->r2 << 2);
    // 0x802C72E8: lui         $s1, 0x802C
    ctx->r17 = S32(0X802C << 16);
    // 0x802C72EC: mtc1        $at, $f24
    ctx->f24.u32l = ctx->r1;
    // 0x802C72F0: addiu       $s1, $s1, 0x7AA0
    ctx->r17 = ADD32(ctx->r17, 0X7AA0);
    // 0x802C72F4: addu        $s5, $t8, $t9
    ctx->r21 = ADD32(ctx->r24, ctx->r25);
    // 0x802C72F8: addu        $s4, $t7, $t6
    ctx->r20 = ADD32(ctx->r15, ctx->r14);
    // 0x802C72FC: or          $s3, $zero, $zero
    ctx->r19 = 0 | 0;
L_802C7300:
    // 0x802C7300: lw          $a0, 0x0($s1)
    ctx->r4 = MEM_W(ctx->r17, 0X0);
    // 0x802C7304: lw          $v0, 0x0($s4)
    ctx->r2 = MEM_W(ctx->r20, 0X0);
    // 0x802C7308: lw          $s0, 0x0($s5)
    ctx->r16 = MEM_W(ctx->r21, 0X0);
    // 0x802C730C: sll         $t4, $a0, 1
    ctx->r12 = S32(ctx->r4 << 1);
    // 0x802C7310: addu        $v0, $v0, $t4
    ctx->r2 = ADD32(ctx->r2, ctx->r12);
    // 0x802C7314: lh          $v1, 0x0($v0)
    ctx->r3 = MEM_H(ctx->r2, 0X0);
    // 0x802C7318: lui         $t9, 0x802C
    ctx->r25 = S32(0X802C << 16);
    // 0x802C731C: addiu       $t9, $t9, 0x7B10
    ctx->r25 = ADD32(ctx->r25, 0X7B10);
    // 0x802C7320: sll         $t5, $v1, 2
    ctx->r13 = S32(ctx->r3 << 2);
    // 0x802C7324: subu        $t5, $t5, $v1
    ctx->r13 = SUB32(ctx->r13, ctx->r3);
    // 0x802C7328: sll         $t5, $t5, 2
    ctx->r13 = S32(ctx->r13 << 2);
    // 0x802C732C: addu        $s0, $s0, $t5
    ctx->r16 = ADD32(ctx->r16, ctx->r13);
    // 0x802C7330: lh          $t6, 0x2($s0)
    ctx->r14 = MEM_H(ctx->r16, 0X2);
    // 0x802C7334: lh          $t7, 0x0($s0)
    ctx->r15 = MEM_H(ctx->r16, 0X0);
    // 0x802C7338: lh          $t8, 0x4($s0)
    ctx->r24 = MEM_H(ctx->r16, 0X4);
    // 0x802C733C: mtc1        $t6, $f8
    ctx->f8.u32l = ctx->r14;
    // 0x802C7340: mtc1        $t7, $f4
    ctx->f4.u32l = ctx->r15;
    // 0x802C7344: mtc1        $t8, $f16
    ctx->f16.u32l = ctx->r24;
    // 0x802C7348: cvt.s.w     $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.fl = CVT_S_W(ctx->f8.u32l);
    // 0x802C734C: addu        $v0, $s2, $t9
    ctx->r2 = ADD32(ctx->r18, ctx->r25);
    // 0x802C7350: cvt.s.w     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
    // 0x802C7354: div.s       $f0, $f10, $f24
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 24);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f24.fl); 
    ctx->f0.fl = DIV_S(ctx->f10.fl, ctx->f24.fl);
    // 0x802C7358: cvt.s.w     $f18, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    ctx->f18.fl = CVT_S_W(ctx->f16.u32l);
    // 0x802C735C: div.s       $f20, $f6, $f24
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 24);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f24.fl); 
    ctx->f20.fl = DIV_S(ctx->f6.fl, ctx->f24.fl);
    // 0x802C7360: c.le.s      $f26, $f0
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 0);
    c1cs = ctx->f26.fl <= ctx->f0.fl;
    // 0x802C7364: nop

    // 0x802C7368: bc1f        L_802C73B0
    if (!c1cs) {
        // 0x802C736C: div.s       $f22, $f18, $f24
        CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 24);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f24.fl); 
    ctx->f22.fl = DIV_S(ctx->f18.fl, ctx->f24.fl);
            goto L_802C73B0;
    }
    // 0x802C736C: div.s       $f22, $f18, $f24
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 24);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f24.fl); 
    ctx->f22.fl = DIV_S(ctx->f18.fl, ctx->f24.fl);
    // 0x802C7370: mtc1        $zero, $f4
    ctx->f4.u32l = 0;
    // 0x802C7374: lwc1        $f6, 0x0($v0)
    ctx->f6.u32l = MEM_W(ctx->r2, 0X0);
    // 0x802C7378: c.eq.s      $f4, $f6
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    c1cs = ctx->f4.fl == ctx->f6.fl;
    // 0x802C737C: nop

    // 0x802C7380: bc1fl       L_802C73B4
    if (!c1cs) {
        // 0x802C7384: lb          $t8, 0x9($s0)
        ctx->r24 = MEM_B(ctx->r16, 0X9);
            goto L_802C73B4;
    }
    goto skip_2;
    // 0x802C7384: lb          $t8, 0x9($s0)
    ctx->r24 = MEM_B(ctx->r16, 0X9);
    skip_2:
    // 0x802C7388: blez        $a0, L_802C73B0
    if (SIGNED(ctx->r4) <= 0) {
        // 0x802C738C: lui         $at, 0x3F80
        ctx->r1 = S32(0X3F80 << 16);
            goto L_802C73B0;
    }
    // 0x802C738C: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x802C7390: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x802C7394: mov.s       $f12, $f20
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 20);
    ctx->f12.fl = ctx->f20.fl;
    // 0x802C7398: mov.s       $f14, $f22
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 22);
    ctx->f14.fl = ctx->f22.fl;
    // 0x802C739C: addiu       $a2, $zero, 0x32
    ctx->r6 = ADD32(0, 0X32);
    // 0x802C73A0: swc1        $f0, 0x74($sp)
    MEM_W(0X74, ctx->r29) = ctx->f0.u32l;
    // 0x802C73A4: jal         0x8004EFB4
    // 0x802C73A8: swc1        $f8, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->f8.u32l;
    func_8004EFB4(rdram, ctx);
        goto after_4;
    // 0x802C73A8: swc1        $f8, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->f8.u32l;
    after_4:
    // 0x802C73AC: lwc1        $f0, 0x74($sp)
    ctx->f0.u32l = MEM_W(ctx->r29, 0X74);
L_802C73B0:
    // 0x802C73B0: lb          $t8, 0x9($s0)
    ctx->r24 = MEM_B(ctx->r16, 0X9);
L_802C73B4:
    // 0x802C73B4: lb          $t5, 0x6($s0)
    ctx->r13 = MEM_B(ctx->r16, 0X6);
    // 0x802C73B8: lb          $t7, 0x7($s0)
    ctx->r15 = MEM_B(ctx->r16, 0X7);
    // 0x802C73BC: mtc1        $t8, $f4
    ctx->f4.u32l = ctx->r24;
    // 0x802C73C0: mtc1        $t5, $f10
    ctx->f10.u32l = ctx->r13;
    // 0x802C73C4: lb          $t6, 0x8($s0)
    ctx->r14 = MEM_B(ctx->r16, 0X8);
    // 0x802C73C8: cvt.s.w     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
    // 0x802C73CC: mtc1        $t7, $f16
    ctx->f16.u32l = ctx->r15;
    // 0x802C73D0: lui         $t4, 0x801D
    ctx->r12 = S32(0X801D << 16);
    // 0x802C73D4: lw          $t4, -0x1A08($t4)
    ctx->r12 = MEM_W(ctx->r12, -0X1A08);
    // 0x802C73D8: mtc1        $t6, $f18
    ctx->f18.u32l = ctx->r14;
    // 0x802C73DC: cvt.s.w     $f10, $f10
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 10);
    ctx->f10.fl = CVT_S_W(ctx->f10.u32l);
    // 0x802C73E0: swc1        $f6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f6.u32l;
    // 0x802C73E4: lb          $t9, 0xA($s0)
    ctx->r25 = MEM_B(ctx->r16, 0XA);
    // 0x802C73E8: addu        $a0, $t4, $s3
    ctx->r4 = ADD32(ctx->r12, ctx->r19);
    // 0x802C73EC: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C73F0: mtc1        $t9, $f8
    ctx->f8.u32l = ctx->r25;
    // 0x802C73F4: mfc1        $a1, $f10
    ctx->r5 = (int32_t)ctx->f10.u32l;
    // 0x802C73F8: cvt.s.w     $f16, $f16
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 16);
    ctx->f16.fl = CVT_S_W(ctx->f16.u32l);
    // 0x802C73FC: lwc1        $f4, 0x7AE0($at)
    ctx->f4.u32l = MEM_W(ctx->r1, 0X7AE0);
    // 0x802C7400: addiu       $a0, $a0, 0x1380
    ctx->r4 = ADD32(ctx->r4, 0X1380);
    // 0x802C7404: cvt.s.w     $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.fl = CVT_S_W(ctx->f8.u32l);
    // 0x802C7408: mfc1        $a2, $f16
    ctx->r6 = (int32_t)ctx->f16.u32l;
    // 0x802C740C: cvt.s.w     $f18, $f18
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 18);
    ctx->f18.fl = CVT_S_W(ctx->f18.u32l);
    // 0x802C7410: swc1        $f10, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->f10.u32l;
    // 0x802C7414: lb          $t4, 0xB($s0)
    ctx->r12 = MEM_B(ctx->r16, 0XB);
    // 0x802C7418: swc1        $f22, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->f22.u32l;
    // 0x802C741C: swc1        $f0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->f0.u32l;
    // 0x802C7420: mtc1        $t4, $f16
    ctx->f16.u32l = ctx->r12;
    // 0x802C7424: mfc1        $a3, $f18
    ctx->r7 = (int32_t)ctx->f18.u32l;
    // 0x802C7428: swc1        $f20, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->f20.u32l;
    // 0x802C742C: cvt.s.w     $f18, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    ctx->f18.fl = CVT_S_W(ctx->f16.u32l);
    // 0x802C7430: swc1        $f4, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->f4.u32l;
    // 0x802C7434: jal         0x801E4C60
    // 0x802C7438: swc1        $f18, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->f18.u32l;
    func_801E4C60(rdram, ctx);
        goto after_5;
    // 0x802C7438: swc1        $f18, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->f18.u32l;
    after_5:
    // 0x802C743C: addiu       $s3, $s3, 0x40
    ctx->r19 = ADD32(ctx->r19, 0X40);
    // 0x802C7440: addiu       $at, $zero, 0x200
    ctx->r1 = ADD32(0, 0X200);
    // 0x802C7444: addiu       $s2, $s2, 0x4
    ctx->r18 = ADD32(ctx->r18, 0X4);
    // 0x802C7448: bne         $s3, $at, L_802C7300
    if (ctx->r19 != ctx->r1) {
        // 0x802C744C: addiu       $s4, $s4, 0x4
        ctx->r20 = ADD32(ctx->r20, 0X4);
            goto L_802C7300;
    }
    // 0x802C744C: addiu       $s4, $s4, 0x4
    ctx->r20 = ADD32(ctx->r20, 0X4);
    // 0x802C7450: lw          $ra, 0x6C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X6C);
    // 0x802C7454: ldc1        $f20, 0x30($sp)
    CHECK_FR(ctx, 20);
    ctx->f20.u64 = LD(ctx->r29, 0X30);
    // 0x802C7458: ldc1        $f22, 0x38($sp)
    CHECK_FR(ctx, 22);
    ctx->f22.u64 = LD(ctx->r29, 0X38);
    // 0x802C745C: ldc1        $f24, 0x40($sp)
    CHECK_FR(ctx, 24);
    ctx->f24.u64 = LD(ctx->r29, 0X40);
    // 0x802C7460: ldc1        $f26, 0x48($sp)
    CHECK_FR(ctx, 26);
    ctx->f26.u64 = LD(ctx->r29, 0X48);
    // 0x802C7464: lw          $s0, 0x54($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X54);
    // 0x802C7468: lw          $s1, 0x58($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X58);
    // 0x802C746C: lw          $s2, 0x5C($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X5C);
    // 0x802C7470: lw          $s3, 0x60($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X60);
    // 0x802C7474: lw          $s4, 0x64($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X64);
    // 0x802C7478: lw          $s5, 0x68($sp)
    ctx->r21 = MEM_W(ctx->r29, 0X68);
    // 0x802C747C: jr          $ra
    // 0x802C7480: addiu       $sp, $sp, 0x98
    ctx->r29 = ADD32(ctx->r29, 0X98);
    return;
    // 0x802C7480: addiu       $sp, $sp, 0x98
    ctx->r29 = ADD32(ctx->r29, 0X98);
;}
RECOMP_FUNC void func_i5_802C7484(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C7484: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x802C7488: addiu       $v0, $v0, -0x19C4
    ctx->r2 = ADD32(ctx->r2, -0X19C4);
    // 0x802C748C: lw          $t6, 0x0($v0)
    ctx->r14 = MEM_W(ctx->r2, 0X0);
    // 0x802C7490: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x802C7494: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x802C7498: beq         $t6, $zero, L_802C74A4
    if (ctx->r14 == 0) {
        // 0x802C749C: nop
    
            goto L_802C74A4;
    }
    // 0x802C749C: nop

    // 0x802C74A0: sw          $zero, 0x0($v0)
    MEM_W(0X0, ctx->r2) = 0;
L_802C74A4:
    // 0x802C74A4: jal         0x80093F78
    // 0x802C74A8: nop

    func_80093F78(rdram, ctx);
        goto after_0;
    // 0x802C74A8: nop

    after_0:
    // 0x802C74AC: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x802C74B0: lui         $a1, 0x800E
    ctx->r5 = S32(0X800E << 16);
    // 0x802C74B4: sw          $zero, -0x54D4($at)
    MEM_W(-0X54D4, ctx->r1) = 0;
    // 0x802C74B8: lw          $a1, -0x7E90($a1)
    ctx->r5 = MEM_W(ctx->r5, -0X7E90);
    // 0x802C74BC: jal         0x800949B8
    // 0x802C74C0: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    func_800949B8(rdram, ctx);
        goto after_1;
    // 0x802C74C0: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    after_1:
    // 0x802C74C4: jal         0x8008FB74
    // 0x802C74C8: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    func_8008FB74(rdram, ctx);
        goto after_2;
    // 0x802C74C8: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    after_2:
    // 0x802C74CC: lui         $v1, 0x802C
    ctx->r3 = S32(0X802C << 16);
    // 0x802C74D0: lw          $v1, 0x7AC8($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X7AC8);
    // 0x802C74D4: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x802C74D8: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C74DC: beq         $v1, $at, L_802C74F4
    if (ctx->r3 == ctx->r1) {
        // 0x802C74E0: addiu       $at, $zero, 0x3
        ctx->r1 = ADD32(0, 0X3);
            goto L_802C74F4;
    }
    // 0x802C74E0: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x802C74E4: beq         $v1, $at, L_802C74F4
    if (ctx->r3 == ctx->r1) {
        // 0x802C74E8: addiu       $at, $zero, 0x4
        ctx->r1 = ADD32(0, 0X4);
            goto L_802C74F4;
    }
    // 0x802C74E8: addiu       $at, $zero, 0x4
    ctx->r1 = ADD32(0, 0X4);
    // 0x802C74EC: bnel        $v1, $at, L_802C7504
    if (ctx->r3 != ctx->r1) {
        // 0x802C74F0: or          $v0, $a0, $zero
        ctx->r2 = ctx->r4 | 0;
            goto L_802C7504;
    }
    goto skip_0;
    // 0x802C74F0: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    skip_0:
L_802C74F4:
    // 0x802C74F4: jal         0x802C7594
    // 0x802C74F8: nop

    func_i5_802C7594(rdram, ctx);
        goto after_3;
    // 0x802C74F8: nop

    after_3:
    // 0x802C74FC: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C7500: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
L_802C7504:
    // 0x802C7504: lui         $t7, 0x102
    ctx->r15 = S32(0X102 << 16);
    // 0x802C7508: lui         $t8, 0x8012
    ctx->r24 = S32(0X8012 << 16);
    // 0x802C750C: addiu       $t8, $t8, -0x7E0
    ctx->r24 = ADD32(ctx->r24, -0X7E0);
    // 0x802C7510: ori         $t7, $t7, 0x40
    ctx->r15 = ctx->r15 | 0X40;
    // 0x802C7514: sw          $t7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r15;
    // 0x802C7518: sw          $t8, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r24;
    // 0x802C751C: lui         $a1, 0x800E
    ctx->r5 = S32(0X800E << 16);
    // 0x802C7520: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C7524: jal         0x80094A44
    // 0x802C7528: lw          $a1, -0x7E90($a1)
    ctx->r5 = MEM_W(ctx->r5, -0X7E90);
    func_80094A44(rdram, ctx);
        goto after_4;
    // 0x802C7528: lw          $a1, -0x7E90($a1)
    ctx->r5 = MEM_W(ctx->r5, -0X7E90);
    after_4:
    // 0x802C752C: jal         0x80090F58
    // 0x802C7530: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    Draw_WaterEffects(rdram, ctx);
        goto after_5;
    // 0x802C7530: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    after_5:
    // 0x802C7534: jal         0x802C7698
    // 0x802C7538: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    func_i5_802C7698(rdram, ctx);
        goto after_6;
    // 0x802C7538: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    after_6:
    // 0x802C753C: lui         $t9, 0x800E
    ctx->r25 = S32(0X800E << 16);
    // 0x802C7540: lw          $t9, -0x54DC($t9)
    ctx->r25 = MEM_W(ctx->r25, -0X54DC);
    // 0x802C7544: addiu       $at, $zero, 0x5A
    ctx->r1 = ADD32(0, 0X5A);
    // 0x802C7548: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C754C: bne         $t9, $at, L_802C7564
    if (ctx->r25 != ctx->r1) {
        // 0x802C7550: lui         $t0, 0x8023
        ctx->r8 = S32(0X8023 << 16);
            goto L_802C7564;
    }
    // 0x802C7550: lui         $t0, 0x8023
    ctx->r8 = S32(0X8023 << 16);
    // 0x802C7554: jal         0x802C781C
    // 0x802C7558: sw          $v0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r2;
    func_i5_802C781C(rdram, ctx);
        goto after_7;
    // 0x802C7558: sw          $v0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r2;
    after_7:
    // 0x802C755C: b           L_802C7580
    // 0x802C7560: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
        goto L_802C7580;
    // 0x802C7560: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
L_802C7564:
    // 0x802C7564: lh          $t0, -0x75EA($t0)
    ctx->r8 = MEM_H(ctx->r8, -0X75EA);
    // 0x802C7568: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x802C756C: bnel        $t0, $at, L_802C7584
    if (ctx->r8 != ctx->r1) {
        // 0x802C7570: lw          $ra, 0x14($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X14);
            goto L_802C7584;
    }
    goto skip_1;
    // 0x802C7570: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    skip_1:
    // 0x802C7574: jal         0x801EB180
    // 0x802C7578: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    func_801EB180(rdram, ctx);
        goto after_8;
    // 0x802C7578: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    after_8:
    // 0x802C757C: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
L_802C7580:
    // 0x802C7580: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C7584:
    // 0x802C7584: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x802C7588: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x802C758C: jr          $ra
    // 0x802C7590: nop

    return;
    // 0x802C7590: nop

;}
RECOMP_FUNC void func_i5_802C7594(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C7594: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x802C7598: lui         $t6, 0x107
    ctx->r14 = S32(0X107 << 16);
    // 0x802C759C: lui         $t2, 0x600
    ctx->r10 = S32(0X600 << 16);
    // 0x802C75A0: addiu       $t6, $t6, -0x940
    ctx->r14 = ADD32(ctx->r14, -0X940);
    // 0x802C75A4: lui         $a1, 0x700
    ctx->r5 = S32(0X700 << 16);
    // 0x802C75A8: lui         $a2, 0x802C
    ctx->r6 = S32(0X802C << 16);
    // 0x802C75AC: lui         $a3, 0x700
    ctx->r7 = S32(0X700 << 16);
    // 0x802C75B0: lui         $t0, 0x700
    ctx->r8 = S32(0X700 << 16);
    // 0x802C75B4: lui         $t1, 0x700
    ctx->r9 = S32(0X700 << 16);
    // 0x802C75B8: lui         $t4, 0x700
    ctx->r12 = S32(0X700 << 16);
    // 0x802C75BC: lui         $t3, 0x102
    ctx->r11 = S32(0X102 << 16);
    // 0x802C75C0: sw          $t6, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r14;
    // 0x802C75C4: sw          $t2, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r10;
    // 0x802C75C8: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C75CC: ori         $t3, $t3, 0x40
    ctx->r11 = ctx->r11 | 0X40;
    // 0x802C75D0: addiu       $t4, $t4, 0x1640
    ctx->r12 = ADD32(ctx->r12, 0X1640);
    // 0x802C75D4: addiu       $t1, $t1, 0x1440
    ctx->r9 = ADD32(ctx->r9, 0X1440);
    // 0x802C75D8: addiu       $t0, $t0, 0x1400
    ctx->r8 = ADD32(ctx->r8, 0X1400);
    // 0x802C75DC: addiu       $a3, $a3, 0x13C0
    ctx->r7 = ADD32(ctx->r7, 0X13C0);
    // 0x802C75E0: addiu       $a2, $a2, 0x7AA8
    ctx->r6 = ADD32(ctx->r6, 0X7AA8);
    // 0x802C75E4: addiu       $a1, $a1, 0x1380
    ctx->r5 = ADD32(ctx->r5, 0X1380);
L_802C75E8:
    // 0x802C75E8: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x802C75EC: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C75F0: sw          $t3, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r11;
    // 0x802C75F4: sw          $a1, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r5;
    // 0x802C75F8: or          $v1, $a0, $zero
    ctx->r3 = ctx->r4 | 0;
    // 0x802C75FC: sw          $t2, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r10;
    // 0x802C7600: lw          $t7, 0x0($a2)
    ctx->r15 = MEM_W(ctx->r6, 0X0);
    // 0x802C7604: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C7608: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x802C760C: sw          $t7, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r15;
    // 0x802C7610: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C7614: or          $v1, $a0, $zero
    ctx->r3 = ctx->r4 | 0;
    // 0x802C7618: sw          $a3, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r7;
    // 0x802C761C: sw          $t3, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r11;
    // 0x802C7620: sw          $t2, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r10;
    // 0x802C7624: lw          $t8, 0x4($a2)
    ctx->r24 = MEM_W(ctx->r6, 0X4);
    // 0x802C7628: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C762C: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x802C7630: sw          $t8, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r24;
    // 0x802C7634: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C7638: or          $v1, $a0, $zero
    ctx->r3 = ctx->r4 | 0;
    // 0x802C763C: sw          $t0, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r8;
    // 0x802C7640: sw          $t3, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r11;
    // 0x802C7644: sw          $t2, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r10;
    // 0x802C7648: lw          $t9, 0x8($a2)
    ctx->r25 = MEM_W(ctx->r6, 0X8);
    // 0x802C764C: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C7650: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x802C7654: sw          $t9, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r25;
    // 0x802C7658: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C765C: or          $v1, $a0, $zero
    ctx->r3 = ctx->r4 | 0;
    // 0x802C7660: sw          $t1, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r9;
    // 0x802C7664: sw          $t3, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r11;
    // 0x802C7668: sw          $t2, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r10;
    // 0x802C766C: lw          $t5, 0xC($a2)
    ctx->r13 = MEM_W(ctx->r6, 0XC);
    // 0x802C7670: addiu       $t1, $t1, 0x100
    ctx->r9 = ADD32(ctx->r9, 0X100);
    // 0x802C7674: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C7678: addiu       $t0, $t0, 0x100
    ctx->r8 = ADD32(ctx->r8, 0X100);
    // 0x802C767C: addiu       $a3, $a3, 0x100
    ctx->r7 = ADD32(ctx->r7, 0X100);
    // 0x802C7680: addiu       $a1, $a1, 0x100
    ctx->r5 = ADD32(ctx->r5, 0X100);
    // 0x802C7684: addiu       $a2, $a2, 0x10
    ctx->r6 = ADD32(ctx->r6, 0X10);
    // 0x802C7688: bne         $t1, $t4, L_802C75E8
    if (ctx->r9 != ctx->r12) {
        // 0x802C768C: sw          $t5, 0x4($v1)
        MEM_W(0X4, ctx->r3) = ctx->r13;
            goto L_802C75E8;
    }
    // 0x802C768C: sw          $t5, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r13;
    // 0x802C7690: jr          $ra
    // 0x802C7694: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    return;
    // 0x802C7694: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
;}
RECOMP_FUNC void func_i5_802C7698(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C7698: addiu       $sp, $sp, -0x40
    ctx->r29 = ADD32(ctx->r29, -0X40);
    // 0x802C769C: sw          $ra, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r31;
    // 0x802C76A0: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x802C76A4: lui         $t7, 0x107
    ctx->r15 = S32(0X107 << 16);
    // 0x802C76A8: addiu       $t7, $t7, -0x9D8
    ctx->r15 = ADD32(ctx->r15, -0X9D8);
    // 0x802C76AC: lui         $t6, 0x600
    ctx->r14 = S32(0X600 << 16);
    // 0x802C76B0: sw          $t6, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r14;
    // 0x802C76B4: sw          $t7, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r15;
    // 0x802C76B8: lui         $a2, 0x802C
    ctx->r6 = S32(0X802C << 16);
    // 0x802C76BC: addiu       $t8, $zero, 0xD0
    ctx->r24 = ADD32(0, 0XD0);
    // 0x802C76C0: addiu       $t9, $zero, 0xF
    ctx->r25 = ADD32(0, 0XF);
    // 0x802C76C4: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C76C8: sw          $t9, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r25;
    // 0x802C76CC: sw          $t8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r24;
    // 0x802C76D0: lw          $a2, 0x7ACC($a2)
    ctx->r6 = MEM_W(ctx->r6, 0X7ACC);
    // 0x802C76D4: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    ctx->r6 = ADD32(ctx->r6, 52);
    // 0x802C76D8: jal         0x80094338
    // 0x802C76DC: addiu       $a3, $zero, 0x91
    ctx->r7 = ADD32(0, 0X91);
    func_80094338(rdram, ctx);
        goto after_0;
    // 0x802C76DC: addiu       $a3, $zero, 0x91
    ctx->r7 = ADD32(0, 0X91);
    after_0:
    // 0x802C76E0: lui         $a2, 0x802C
    ctx->r6 = S32(0X802C << 16);
    // 0x802C76E4: addiu       $t0, $zero, 0xD0
    ctx->r8 = ADD32(0, 0XD0);
    // 0x802C76E8: addiu       $t1, $zero, 0xF
    ctx->r9 = ADD32(0, 0XF);
    // 0x802C76EC: sw          $t1, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r9;
    // 0x802C76F0: sw          $t0, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r8;
    // 0x802C76F4: lw          $a2, 0x7AD0($a2)
    ctx->r6 = MEM_W(ctx->r6, 0X7AD0);
    // 0x802C76F8: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C76FC: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    ctx->r6 = ADD32(ctx->r6, 52);
    // 0x802C7700: jal         0x80094338
    // 0x802C7704: addiu       $a3, $zero, 0xA6
    ctx->r7 = ADD32(0, 0XA6);
    func_80094338(rdram, ctx);
        goto after_1;
    // 0x802C7704: addiu       $a3, $zero, 0xA6
    ctx->r7 = ADD32(0, 0XA6);
    after_1:
    // 0x802C7708: addiu       $t2, $zero, 0xFF
    ctx->r10 = ADD32(0, 0XFF);
    // 0x802C770C: addiu       $t3, $zero, 0xFF
    ctx->r11 = ADD32(0, 0XFF);
    // 0x802C7710: addiu       $t4, $zero, 0xFF
    ctx->r12 = ADD32(0, 0XFF);
    // 0x802C7714: addiu       $t5, $zero, 0xFF
    ctx->r13 = ADD32(0, 0XFF);
    // 0x802C7718: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C771C: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C7720: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C7724: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C7728: addiu       $t0, $zero, 0xFF
    ctx->r8 = ADD32(0, 0XFF);
    // 0x802C772C: addiu       $t1, $zero, 0xFF
    ctx->r9 = ADD32(0, 0XFF);
    // 0x802C7730: sw          $t1, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r9;
    // 0x802C7734: sw          $t0, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r8;
    // 0x802C7738: sw          $t9, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r25;
    // 0x802C773C: sw          $t8, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r24;
    // 0x802C7740: sw          $t7, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r15;
    // 0x802C7744: sw          $t6, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r14;
    // 0x802C7748: sw          $t5, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r13;
    // 0x802C774C: sw          $t4, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r12;
    // 0x802C7750: sw          $t3, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r11;
    // 0x802C7754: sw          $t2, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r10;
    // 0x802C7758: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C775C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C7760: addiu       $a2, $zero, 0xFF
    ctx->r6 = ADD32(0, 0XFF);
    // 0x802C7764: jal         0x801E946C
    // 0x802C7768: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    func_801E946C(rdram, ctx);
        goto after_2;
    // 0x802C7768: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    after_2:
    // 0x802C776C: lui         $a3, 0x802C
    ctx->r7 = S32(0X802C << 16);
    // 0x802C7770: lw          $a3, 0x7ACC($a3)
    ctx->r7 = MEM_W(ctx->r7, 0X7ACC);
    // 0x802C7774: addiu       $t2, $zero, 0x93
    ctx->r10 = ADD32(0, 0X93);
    // 0x802C7778: sw          $t2, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r10;
    // 0x802C777C: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C7780: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C7784: addiu       $a2, $zero, 0x6
    ctx->r6 = ADD32(0, 0X6);
    // 0x802C7788: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    ctx->r7 = ADD32(ctx->r7, 52);
    // 0x802C778C: jal         0x801E3EE0
    // 0x802C7790: addiu       $a3, $a3, 0xA
    ctx->r7 = ADD32(ctx->r7, 0XA);
    func_801E3EE0(rdram, ctx);
        goto after_3;
    // 0x802C7790: addiu       $a3, $a3, 0xA
    ctx->r7 = ADD32(ctx->r7, 0XA);
    after_3:
    // 0x802C7794: lui         $a3, 0x802C
    ctx->r7 = S32(0X802C << 16);
    // 0x802C7798: lw          $a3, 0x7AD0($a3)
    ctx->r7 = MEM_W(ctx->r7, 0X7AD0);
    // 0x802C779C: addiu       $t3, $zero, 0xA8
    ctx->r11 = ADD32(0, 0XA8);
    // 0x802C77A0: sw          $t3, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r11;
    // 0x802C77A4: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C77A8: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C77AC: addiu       $a2, $zero, 0x7
    ctx->r6 = ADD32(0, 0X7);
    // 0x802C77B0: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    ctx->r7 = ADD32(ctx->r7, 52);
    // 0x802C77B4: jal         0x801E3EE0
    // 0x802C77B8: addiu       $a3, $a3, 0xA
    ctx->r7 = ADD32(ctx->r7, 0XA);
    func_801E3EE0(rdram, ctx);
        goto after_4;
    // 0x802C77B8: addiu       $a3, $a3, 0xA
    ctx->r7 = ADD32(ctx->r7, 0XA);
    after_4:
    // 0x802C77BC: lui         $a3, 0x802C
    ctx->r7 = S32(0X802C << 16);
    // 0x802C77C0: lw          $a3, 0x7ACC($a3)
    ctx->r7 = MEM_W(ctx->r7, 0X7ACC);
    // 0x802C77C4: lui         $a2, 0x802C
    ctx->r6 = S32(0X802C << 16);
    // 0x802C77C8: addiu       $t4, $zero, 0x93
    ctx->r12 = ADD32(0, 0X93);
    // 0x802C77CC: sw          $t4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r12;
    // 0x802C77D0: lw          $a2, 0x7B34($a2)
    ctx->r6 = MEM_W(ctx->r6, 0X7B34);
    // 0x802C77D4: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C77D8: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    ctx->r7 = ADD32(ctx->r7, 52);
    // 0x802C77DC: jal         0x801EB00C
    // 0x802C77E0: addiu       $a3, $a3, 0xBA
    ctx->r7 = ADD32(ctx->r7, 0XBA);
    func_801EB00C(rdram, ctx);
        goto after_5;
    // 0x802C77E0: addiu       $a3, $a3, 0xBA
    ctx->r7 = ADD32(ctx->r7, 0XBA);
    after_5:
    // 0x802C77E4: lui         $a3, 0x802C
    ctx->r7 = S32(0X802C << 16);
    // 0x802C77E8: lw          $a3, 0x7AD0($a3)
    ctx->r7 = MEM_W(ctx->r7, 0X7AD0);
    // 0x802C77EC: lui         $a2, 0x802C
    ctx->r6 = S32(0X802C << 16);
    // 0x802C77F0: addiu       $t5, $zero, 0xA8
    ctx->r13 = ADD32(0, 0XA8);
    // 0x802C77F4: sw          $t5, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r13;
    // 0x802C77F8: lw          $a2, 0x7B30($a2)
    ctx->r6 = MEM_W(ctx->r6, 0X7B30);
    // 0x802C77FC: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C7800: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    ctx->r7 = ADD32(ctx->r7, 52);
    // 0x802C7804: jal         0x801EB00C
    // 0x802C7808: addiu       $a3, $a3, 0xBA
    ctx->r7 = ADD32(ctx->r7, 0XBA);
    func_801EB00C(rdram, ctx);
        goto after_6;
    // 0x802C7808: addiu       $a3, $a3, 0xBA
    ctx->r7 = ADD32(ctx->r7, 0XBA);
    after_6:
    // 0x802C780C: lw          $ra, 0x3C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X3C);
    // 0x802C7810: addiu       $sp, $sp, 0x40
    ctx->r29 = ADD32(ctx->r29, 0X40);
    // 0x802C7814: jr          $ra
    // 0x802C7818: nop

    return;
    // 0x802C7818: nop

;}
RECOMP_FUNC void func_i5_802C781C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C781C: lui         $a0, 0x802C
    ctx->r4 = S32(0X802C << 16);
    // 0x802C7820: addiu       $a0, $a0, 0x7AC8
    ctx->r4 = ADD32(ctx->r4, 0X7AC8);
    // 0x802C7824: lw          $t6, 0x0($a0)
    ctx->r14 = MEM_W(ctx->r4, 0X0);
    // 0x802C7828: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x802C782C: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x802C7830: sltiu       $at, $t6, 0x5
    ctx->r1 = ctx->r14 < 0X5 ? 1 : 0;
    // 0x802C7834: beq         $at, $zero, L_802C79CC
    if (ctx->r1 == 0) {
        // 0x802C7838: sll         $t6, $t6, 2
        ctx->r14 = S32(ctx->r14 << 2);
            goto L_802C79CC;
    }
    // 0x802C7838: sll         $t6, $t6, 2
    ctx->r14 = S32(ctx->r14 << 2);
    // 0x802C783C: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C7840: addu        $at, $at, $t6
    gpr jr_addend_802C7848 = ctx->r14;
    ctx->r1 = ADD32(ctx->r1, ctx->r14);
    // 0x802C7844: lw          $t6, 0x7AE4($at)
    ctx->r14 = ADD32(ctx->r1, 0X7AE4);
    // 0x802C7848: jr          $t6
    // 0x802C784C: nop

    switch (jr_addend_802C7848 >> 2) {
        case 0: goto L_802C7850; break;
        case 1: goto L_802C7880; break;
        case 2: goto L_802C788C; break;
        case 3: goto L_802C78C8; break;
        case 4: goto L_802C78FC; break;
        default: switch_error(__func__, 0x802C7848, 0x802C7AE4);
    }
    // 0x802C784C: nop

L_802C7850:
    // 0x802C7850: lui         $a1, 0x802C
    ctx->r5 = S32(0X802C << 16);
    // 0x802C7854: addiu       $a1, $a1, 0x7ACC
    ctx->r5 = ADD32(ctx->r5, 0X7ACC);
    // 0x802C7858: lw          $t7, 0x0($a1)
    ctx->r15 = MEM_W(ctx->r5, 0X0);
    // 0x802C785C: addiu       $t0, $zero, 0x1
    ctx->r8 = ADD32(0, 0X1);
    // 0x802C7860: addiu       $t1, $zero, 0x38
    ctx->r9 = ADD32(0, 0X38);
    // 0x802C7864: addiu       $t8, $t7, -0x1E
    ctx->r24 = ADD32(ctx->r15, -0X1E);
    // 0x802C7868: slti        $at, $t8, 0x38
    ctx->r1 = SIGNED(ctx->r24) < 0X38 ? 1 : 0;
    // 0x802C786C: beq         $at, $zero, L_802C79CC
    if (ctx->r1 == 0) {
        // 0x802C7870: sw          $t8, 0x0($a1)
        MEM_W(0X0, ctx->r5) = ctx->r24;
            goto L_802C79CC;
    }
    // 0x802C7870: sw          $t8, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r24;
    // 0x802C7874: sw          $t0, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r8;
    // 0x802C7878: b           L_802C79CC
    // 0x802C787C: sw          $t1, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r9;
        goto L_802C79CC;
    // 0x802C787C: sw          $t1, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r9;
L_802C7880:
    // 0x802C7880: addiu       $t2, $zero, 0x2
    ctx->r10 = ADD32(0, 0X2);
    // 0x802C7884: b           L_802C79CC
    // 0x802C7888: sw          $t2, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r10;
        goto L_802C79CC;
    // 0x802C7888: sw          $t2, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r10;
L_802C788C:
    // 0x802C788C: lui         $v1, 0x802C
    ctx->r3 = S32(0X802C << 16);
    // 0x802C7890: addiu       $v1, $v1, 0x7AA0
    ctx->r3 = ADD32(ctx->r3, 0X7AA0);
    // 0x802C7894: lw          $t3, 0x0($v1)
    ctx->r11 = MEM_W(ctx->r3, 0X0);
    // 0x802C7898: lui         $t5, 0x802C
    ctx->r13 = S32(0X802C << 16);
    // 0x802C789C: addiu       $t8, $zero, 0x3
    ctx->r24 = ADD32(0, 0X3);
    // 0x802C78A0: addiu       $t4, $t3, 0x1
    ctx->r12 = ADD32(ctx->r11, 0X1);
    // 0x802C78A4: sw          $t4, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r12;
    // 0x802C78A8: lw          $t5, 0x7B38($t5)
    ctx->r13 = MEM_W(ctx->r13, 0X7B38);
    // 0x802C78AC: addiu       $t7, $t4, -0x1
    ctx->r15 = ADD32(ctx->r12, -0X1);
    // 0x802C78B0: lh          $t6, 0x0($t5)
    ctx->r14 = MEM_H(ctx->r13, 0X0);
    // 0x802C78B4: bne         $t4, $t6, L_802C79CC
    if (ctx->r12 != ctx->r14) {
        // 0x802C78B8: nop
    
            goto L_802C79CC;
    }
    // 0x802C78B8: nop

    // 0x802C78BC: sw          $t7, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r15;
    // 0x802C78C0: b           L_802C79CC
    // 0x802C78C4: sw          $t8, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r24;
        goto L_802C79CC;
    // 0x802C78C4: sw          $t8, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r24;
L_802C78C8:
    // 0x802C78C8: lui         $t9, 0x801D
    ctx->r25 = S32(0X801D << 16);
    // 0x802C78CC: lhu         $t9, -0x19A6($t9)
    ctx->r25 = MEM_HU(ctx->r25, -0X19A6);
    // 0x802C78D0: lui         $v0, 0x802C
    ctx->r2 = S32(0X802C << 16);
    // 0x802C78D4: addiu       $v0, $v0, 0x7B88
    ctx->r2 = ADD32(ctx->r2, 0X7B88);
    // 0x802C78D8: andi        $t0, $t9, 0xB000
    ctx->r8 = ctx->r25 & 0XB000;
    // 0x802C78DC: beq         $t0, $zero, L_802C79CC
    if (ctx->r8 == 0) {
        // 0x802C78E0: lui         $v1, 0x802C
        ctx->r3 = S32(0X802C << 16);
            goto L_802C79CC;
    }
    // 0x802C78E0: lui         $v1, 0x802C
    ctx->r3 = S32(0X802C << 16);
    // 0x802C78E4: addiu       $v1, $v1, 0x7AA0
    ctx->r3 = ADD32(ctx->r3, 0X7AA0);
    // 0x802C78E8: addiu       $t1, $zero, 0x4
    ctx->r9 = ADD32(0, 0X4);
    // 0x802C78EC: sw          $t1, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r9;
    // 0x802C78F0: sw          $zero, 0x0($v1)
    MEM_W(0X0, ctx->r3) = 0;
    // 0x802C78F4: b           L_802C79CC
    // 0x802C78F8: sw          $zero, 0x0($v0)
    MEM_W(0X0, ctx->r2) = 0;
        goto L_802C79CC;
    // 0x802C78F8: sw          $zero, 0x0($v0)
    MEM_W(0X0, ctx->r2) = 0;
L_802C78FC:
    // 0x802C78FC: lui         $a1, 0x802C
    ctx->r5 = S32(0X802C << 16);
    // 0x802C7900: addiu       $a1, $a1, 0x7ACC
    ctx->r5 = ADD32(ctx->r5, 0X7ACC);
    // 0x802C7904: lw          $t2, 0x0($a1)
    ctx->r10 = MEM_W(ctx->r5, 0X0);
    // 0x802C7908: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    // 0x802C790C: lui         $v1, 0x802C
    ctx->r3 = S32(0X802C << 16);
    // 0x802C7910: addiu       $t3, $t2, -0x1E
    ctx->r11 = ADD32(ctx->r10, -0X1E);
    // 0x802C7914: slti        $at, $t3, -0xD0
    ctx->r1 = SIGNED(ctx->r11) < -0XD0 ? 1 : 0;
    // 0x802C7918: beq         $at, $zero, L_802C792C
    if (ctx->r1 == 0) {
        // 0x802C791C: sw          $t3, 0x0($a1)
        MEM_W(0X0, ctx->r5) = ctx->r11;
            goto L_802C792C;
    }
    // 0x802C791C: sw          $t3, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r11;
    // 0x802C7920: addiu       $t5, $zero, -0xD0
    ctx->r13 = ADD32(0, -0XD0);
    // 0x802C7924: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    // 0x802C7928: sw          $t5, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r13;
L_802C792C:
    // 0x802C792C: addiu       $v1, $v1, 0x7AA0
    ctx->r3 = ADD32(ctx->r3, 0X7AA0);
    // 0x802C7930: lw          $t6, 0x0($v1)
    ctx->r14 = MEM_W(ctx->r3, 0X0);
    // 0x802C7934: lui         $t8, 0x802C
    ctx->r24 = S32(0X802C << 16);
    // 0x802C7938: lui         $v0, 0x802C
    ctx->r2 = S32(0X802C << 16);
    // 0x802C793C: addiu       $t7, $t6, 0x1
    ctx->r15 = ADD32(ctx->r14, 0X1);
    // 0x802C7940: sw          $t7, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r15;
    // 0x802C7944: lw          $t8, 0x7B3C($t8)
    ctx->r24 = MEM_W(ctx->r24, 0X7B3C);
    // 0x802C7948: addiu       $t0, $t7, -0x1
    ctx->r8 = ADD32(ctx->r15, -0X1);
    // 0x802C794C: addiu       $v0, $v0, 0x7B88
    ctx->r2 = ADD32(ctx->r2, 0X7B88);
    // 0x802C7950: lh          $t9, 0x0($t8)
    ctx->r25 = MEM_H(ctx->r24, 0X0);
    // 0x802C7954: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x802C7958: lui         $t4, 0x802C
    ctx->r12 = S32(0X802C << 16);
    // 0x802C795C: bne         $t7, $t9, L_802C796C
    if (ctx->r15 != ctx->r25) {
        // 0x802C7960: nop
    
            goto L_802C796C;
    }
    // 0x802C7960: nop

    // 0x802C7964: addiu       $a0, $a0, 0x1
    ctx->r4 = ADD32(ctx->r4, 0X1);
    // 0x802C7968: sw          $t0, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r8;
L_802C796C:
    // 0x802C796C: bne         $a0, $at, L_802C7980
    if (ctx->r4 != ctx->r1) {
        // 0x802C7970: nop
    
            goto L_802C7980;
    }
    // 0x802C7970: nop

    // 0x802C7974: lw          $t1, 0x0($v0)
    ctx->r9 = MEM_W(ctx->r2, 0X0);
    // 0x802C7978: addiu       $t2, $t1, 0x1
    ctx->r10 = ADD32(ctx->r9, 0X1);
    // 0x802C797C: sw          $t2, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r10;
L_802C7980:
    // 0x802C7980: lui         $v0, 0x802C
    ctx->r2 = S32(0X802C << 16);
    // 0x802C7984: addiu       $v0, $v0, 0x7B88
    ctx->r2 = ADD32(ctx->r2, 0X7B88);
    // 0x802C7988: lw          $t3, 0x0($v0)
    ctx->r11 = MEM_W(ctx->r2, 0X0);
    // 0x802C798C: slti        $at, $t3, 0x4
    ctx->r1 = SIGNED(ctx->r11) < 0X4 ? 1 : 0;
    // 0x802C7990: bne         $at, $zero, L_802C79CC
    if (ctx->r1 != 0) {
        // 0x802C7994: nop
    
            goto L_802C79CC;
    }
    // 0x802C7994: nop

    // 0x802C7998: lw          $t4, 0x7B8C($t4)
    ctx->r12 = MEM_W(ctx->r12, 0X7B8C);
    // 0x802C799C: lui         $t5, 0x802C
    ctx->r13 = S32(0X802C << 16);
    // 0x802C79A0: bne         $t4, $zero, L_802C79B4
    if (ctx->r12 != 0) {
        // 0x802C79A4: nop
    
            goto L_802C79B4;
    }
    // 0x802C79A4: nop

    // 0x802C79A8: lw          $t5, 0x7B90($t5)
    ctx->r13 = MEM_W(ctx->r13, 0X7B90);
    // 0x802C79AC: beq         $t5, $zero, L_802C79C4
    if (ctx->r13 == 0) {
        // 0x802C79B0: nop
    
            goto L_802C79C4;
    }
    // 0x802C79B0: nop

L_802C79B4:
    // 0x802C79B4: jal         0x801EC9C8
    // 0x802C79B8: nop

    func_801EC9C8(rdram, ctx);
        goto after_0;
    // 0x802C79B8: nop

    after_0:
    // 0x802C79BC: b           L_802C79CC
    // 0x802C79C0: nop

        goto L_802C79CC;
    // 0x802C79C0: nop

L_802C79C4:
    // 0x802C79C4: jal         0x801EC830
    // 0x802C79C8: nop

    func_801EC830(rdram, ctx);
        goto after_1;
    // 0x802C79C8: nop

    after_1:
L_802C79CC:
    // 0x802C79CC: lui         $a1, 0x802C
    ctx->r5 = S32(0X802C << 16);
    // 0x802C79D0: addiu       $a1, $a1, 0x7ACC
    ctx->r5 = ADD32(ctx->r5, 0X7ACC);
    // 0x802C79D4: lw          $t6, 0x0($a1)
    ctx->r14 = MEM_W(ctx->r5, 0X0);
    // 0x802C79D8: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x802C79DC: addiu       $t7, $zero, 0x70
    ctx->r15 = ADD32(0, 0X70);
    // 0x802C79E0: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C79E4: subu        $t8, $t7, $t6
    ctx->r24 = SUB32(ctx->r15, ctx->r14);
    // 0x802C79E8: sw          $t8, 0x7AD0($at)
    MEM_W(0X7AD0, ctx->r1) = ctx->r24;
    // 0x802C79EC: jr          $ra
    // 0x802C79F0: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    return;
    // 0x802C79F0: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
;}
RECOMP_FUNC void func_i5_802C79F4(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C79F4: jr          $ra
    // 0x802C79F8: nop

    return;
    // 0x802C79F8: nop

    // 0x802C79FC: nop

;}
RECOMP_FUNC void func_i6_802C5800(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C5800: addiu       $sp, $sp, -0x1B8
    ctx->r29 = ADD32(ctx->r29, -0X1B8);
    // 0x802C5804: lui         $t6, 0x801D
    ctx->r14 = S32(0X801D << 16);
    // 0x802C5808: lw          $t6, -0x19C4($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X19C4);
    // 0x802C580C: sw          $ra, 0x5C($sp)
    MEM_W(0X5C, ctx->r29) = ctx->r31;
    // 0x802C5810: sw          $fp, 0x58($sp)
    MEM_W(0X58, ctx->r29) = ctx->r30;
    // 0x802C5814: sw          $s7, 0x54($sp)
    MEM_W(0X54, ctx->r29) = ctx->r23;
    // 0x802C5818: sw          $s6, 0x50($sp)
    MEM_W(0X50, ctx->r29) = ctx->r22;
    // 0x802C581C: sw          $s5, 0x4C($sp)
    MEM_W(0X4C, ctx->r29) = ctx->r21;
    // 0x802C5820: sw          $s4, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r20;
    // 0x802C5824: sw          $s3, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r19;
    // 0x802C5828: sw          $s2, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r18;
    // 0x802C582C: sw          $s1, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r17;
    // 0x802C5830: beq         $t6, $zero, L_802C58A8
    if (ctx->r14 == 0) {
        // 0x802C5834: sw          $s0, 0x38($sp)
        MEM_W(0X38, ctx->r29) = ctx->r16;
            goto L_802C58A8;
    }
    // 0x802C5834: sw          $s0, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r16;
    // 0x802C5838: lui         $t7, 0x800E
    ctx->r15 = S32(0X800E << 16);
    // 0x802C583C: lw          $t7, -0x54DC($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X54DC);
    // 0x802C5840: addiu       $at, $zero, 0x32
    ctx->r1 = ADD32(0, 0X32);
    // 0x802C5844: lui         $t8, 0x801D
    ctx->r24 = S32(0X801D << 16);
    // 0x802C5848: bnel        $t7, $at, L_802C58AC
    if (ctx->r15 != ctx->r1) {
        // 0x802C584C: lui         $at, 0x4180
        ctx->r1 = S32(0X4180 << 16);
            goto L_802C58AC;
    }
    goto skip_0;
    // 0x802C584C: lui         $at, 0x4180
    ctx->r1 = S32(0X4180 << 16);
    skip_0:
    // 0x802C5850: lw          $t8, -0x19CC($t8)
    ctx->r24 = MEM_W(ctx->r24, -0X19CC);
    // 0x802C5854: addiu       $at, $zero, 0x64
    ctx->r1 = ADD32(0, 0X64);
    // 0x802C5858: addiu       $v0, $zero, 0x14
    ctx->r2 = ADD32(0, 0X14);
    // 0x802C585C: bne         $t8, $at, L_802C588C
    if (ctx->r24 != ctx->r1) {
        // 0x802C5860: lui         $fp, 0x802C
        ctx->r30 = S32(0X802C << 16);
            goto L_802C588C;
    }
    // 0x802C5860: lui         $fp, 0x802C
    ctx->r30 = S32(0X802C << 16);
    // 0x802C5864: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C5868: sw          $zero, 0x6D30($at)
    MEM_W(0X6D30, ctx->r1) = 0;
    // 0x802C586C: lui         $fp, 0x802C
    ctx->r30 = S32(0X802C << 16);
    // 0x802C5870: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C5874: addiu       $t9, $zero, 0x1A8
    ctx->r25 = ADD32(0, 0X1A8);
    // 0x802C5878: addiu       $fp, $fp, 0x6D38
    ctx->r30 = ADD32(ctx->r30, 0X6D38);
    // 0x802C587C: sw          $t9, 0x6D34($at)
    MEM_W(0X6D34, ctx->r1) = ctx->r25;
    // 0x802C5880: addiu       $t0, $zero, -0x170
    ctx->r8 = ADD32(0, -0X170);
    // 0x802C5884: b           L_802C58A8
    // 0x802C5888: sw          $t0, 0x0($fp)
    MEM_W(0X0, ctx->r30) = ctx->r8;
        goto L_802C58A8;
    // 0x802C5888: sw          $t0, 0x0($fp)
    MEM_W(0X0, ctx->r30) = ctx->r8;
L_802C588C:
    // 0x802C588C: addiu       $t1, $zero, 0x2
    ctx->r9 = ADD32(0, 0X2);
    // 0x802C5890: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C5894: sw          $t1, 0x6D30($at)
    MEM_W(0X6D30, ctx->r1) = ctx->r9;
    // 0x802C5898: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C589C: addiu       $fp, $fp, 0x6D38
    ctx->r30 = ADD32(ctx->r30, 0X6D38);
    // 0x802C58A0: sw          $v0, 0x6D34($at)
    MEM_W(0X6D34, ctx->r1) = ctx->r2;
    // 0x802C58A4: sw          $v0, 0x0($fp)
    MEM_W(0X0, ctx->r30) = ctx->r2;
L_802C58A8:
    // 0x802C58A8: lui         $at, 0x4180
    ctx->r1 = S32(0X4180 << 16);
L_802C58AC:
    // 0x802C58AC: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x802C58B0: lui         $s4, 0x801D
    ctx->r20 = S32(0X801D << 16);
    // 0x802C58B4: mtc1        $zero, $f0
    ctx->f0.u32l = 0;
    // 0x802C58B8: addiu       $s4, $s4, -0x1A08
    ctx->r20 = ADD32(ctx->r20, -0X1A08);
    // 0x802C58BC: lui         $at, 0x4580
    ctx->r1 = S32(0X4580 << 16);
    // 0x802C58C0: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x802C58C4: lw          $a0, 0x0($s4)
    ctx->r4 = MEM_W(ctx->r20, 0X0);
    // 0x802C58C8: lui         $fp, 0x802C
    ctx->r30 = S32(0X802C << 16);
    // 0x802C58CC: lui         $a1, 0x802C
    ctx->r5 = S32(0X802C << 16);
    // 0x802C58D0: addiu       $fp, $fp, 0x6D38
    ctx->r30 = ADD32(ctx->r30, 0X6D38);
    // 0x802C58D4: addiu       $a1, $a1, 0x6D40
    ctx->r5 = ADD32(ctx->r5, 0X6D40);
    // 0x802C58D8: lui         $a2, 0x4204
    ctx->r6 = S32(0X4204 << 16);
    // 0x802C58DC: lui         $a3, 0x3F80
    ctx->r7 = S32(0X3F80 << 16);
    // 0x802C58E0: swc1        $f4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f4.u32l;
    // 0x802C58E4: swc1        $f0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->f0.u32l;
    // 0x802C58E8: swc1        $f0, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->f0.u32l;
    // 0x802C58EC: addiu       $a0, $a0, 0xA40
    ctx->r4 = ADD32(ctx->r4, 0XA40);
    // 0x802C58F0: jal         0x800481E0
    // 0x802C58F4: swc1        $f6, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->f6.u32l;
    func_800481E0(rdram, ctx);
        goto after_0;
    // 0x802C58F4: swc1        $f6, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->f6.u32l;
    after_0:
    // 0x802C58F8: mtc1        $zero, $f0
    ctx->f0.u32l = 0;
    // 0x802C58FC: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x802C5900: mtc1        $at, $f2
    ctx->f2.u32l = ctx->r1;
    // 0x802C5904: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C5908: lwc1        $f8, 0x6D14($at)
    ctx->f8.u32l = MEM_W(ctx->r1, 0X6D14);
    // 0x802C590C: addiu       $s0, $sp, 0xB0
    ctx->r16 = ADD32(ctx->r29, 0XB0);
    // 0x802C5910: mfc1        $a1, $f0
    ctx->r5 = (int32_t)ctx->f0.u32l;
    // 0x802C5914: mfc1        $a2, $f0
    ctx->r6 = (int32_t)ctx->f0.u32l;
    // 0x802C5918: mfc1        $a3, $f2
    ctx->r7 = (int32_t)ctx->f2.u32l;
    // 0x802C591C: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x802C5920: swc1        $f0, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f0.u32l;
    // 0x802C5924: swc1        $f0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->f0.u32l;
    // 0x802C5928: swc1        $f0, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->f0.u32l;
    // 0x802C592C: swc1        $f0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->f0.u32l;
    // 0x802C5930: swc1        $f0, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->f0.u32l;
    // 0x802C5934: swc1        $f2, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->f2.u32l;
    // 0x802C5938: jal         0x80048A88
    // 0x802C593C: swc1        $f8, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->f8.u32l;
    func_80048A88(rdram, ctx);
        goto after_1;
    // 0x802C593C: swc1        $f8, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->f8.u32l;
    after_1:
    // 0x802C5940: mtc1        $zero, $f0
    ctx->f0.u32l = 0;
    // 0x802C5944: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x802C5948: mtc1        $at, $f10
    ctx->f10.u32l = ctx->r1;
    // 0x802C594C: addiu       $s1, $sp, 0x130
    ctx->r17 = ADD32(ctx->r29, 0X130);
    // 0x802C5950: mfc1        $a3, $f0
    ctx->r7 = (int32_t)ctx->f0.u32l;
    // 0x802C5954: or          $a1, $s1, $zero
    ctx->r5 = ctx->r17 | 0;
    // 0x802C5958: addiu       $a0, $sp, 0x70
    ctx->r4 = ADD32(ctx->r29, 0X70);
    // 0x802C595C: lui         $a2, 0x43FA
    ctx->r6 = S32(0X43FA << 16);
    // 0x802C5960: swc1        $f0, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f0.u32l;
    // 0x802C5964: swc1        $f0, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->f0.u32l;
    // 0x802C5968: swc1        $f0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->f0.u32l;
    // 0x802C596C: swc1        $f0, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->f0.u32l;
    // 0x802C5970: swc1        $f0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->f0.u32l;
    // 0x802C5974: swc1        $f0, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->f0.u32l;
    // 0x802C5978: jal         0x800484C8
    // 0x802C597C: swc1        $f10, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->f10.u32l;
    func_800484C8(rdram, ctx);
        goto after_2;
    // 0x802C597C: swc1        $f10, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->f10.u32l;
    after_2:
    // 0x802C5980: addiu       $s2, $sp, 0x170
    ctx->r18 = ADD32(ctx->r29, 0X170);
    // 0x802C5984: or          $a1, $s2, $zero
    ctx->r5 = ctx->r18 | 0;
    // 0x802C5988: jal         0x80047E78
    // 0x802C598C: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    SysUtils_MtxToMtxF(rdram, ctx);
        goto after_3;
    // 0x802C598C: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_3:
    // 0x802C5990: addiu       $s6, $sp, 0xF0
    ctx->r22 = ADD32(ctx->r29, 0XF0);
    // 0x802C5994: or          $a2, $s6, $zero
    ctx->r6 = ctx->r22 | 0;
    // 0x802C5998: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    // 0x802C599C: jal         0x80049EB8
    // 0x802C59A0: or          $a1, $s2, $zero
    ctx->r5 = ctx->r18 | 0;
    SysUtils_MatrixAffineMultiply(rdram, ctx);
        goto after_4;
    // 0x802C59A0: or          $a1, $s2, $zero
    ctx->r5 = ctx->r18 | 0;
    after_4:
    // 0x802C59A4: lui         $s7, 0x802C
    ctx->r23 = S32(0X802C << 16);
    // 0x802C59A8: addiu       $s7, $s7, 0x6C70
    ctx->r23 = ADD32(ctx->r23, 0X6C70);
    // 0x802C59AC: or          $s0, $zero, $zero
    ctx->r16 = 0 | 0;
    // 0x802C59B0: or          $s5, $zero, $zero
    ctx->r21 = 0 | 0;
    // 0x802C59B4: or          $s1, $zero, $zero
    ctx->r17 = 0 | 0;
    // 0x802C59B8: addiu       $s3, $zero, 0x66
    ctx->r19 = ADD32(0, 0X66);
L_802C59BC:
    // 0x802C59BC: andi        $t2, $s0, 0x1
    ctx->r10 = ctx->r16 & 0X1;
    // 0x802C59C0: beq         $t2, $zero, L_802C59D0
    if (ctx->r10 == 0) {
        // 0x802C59C4: lui         $s2, 0x802C
        ctx->r18 = S32(0X802C << 16);
            goto L_802C59D0;
    }
    // 0x802C59C4: lui         $s2, 0x802C
    ctx->r18 = S32(0X802C << 16);
    // 0x802C59C8: b           L_802C59D4
    // 0x802C59CC: lw          $s2, 0x0($fp)
    ctx->r18 = MEM_W(ctx->r30, 0X0);
        goto L_802C59D4;
    // 0x802C59CC: lw          $s2, 0x0($fp)
    ctx->r18 = MEM_W(ctx->r30, 0X0);
L_802C59D0:
    // 0x802C59D0: lw          $s2, 0x6D34($s2)
    ctx->r18 = MEM_W(ctx->r18, 0X6D34);
L_802C59D4:
    // 0x802C59D4: lw          $t3, 0x0($s4)
    ctx->r11 = MEM_W(ctx->r20, 0X0);
    // 0x802C59D8: or          $a0, $s6, $zero
    ctx->r4 = ctx->r22 | 0;
    // 0x802C59DC: addu        $a1, $t3, $s5
    ctx->r5 = ADD32(ctx->r11, ctx->r21);
    // 0x802C59E0: jal         0x80047EE0
    // 0x802C59E4: addiu       $a1, $a1, 0xA80
    ctx->r5 = ADD32(ctx->r5, 0XA80);
    SysUtils_MtxFToMtx(rdram, ctx);
        goto after_5;
    // 0x802C59E4: addiu       $a1, $a1, 0xA80
    ctx->r5 = ADD32(ctx->r5, 0XA80);
    after_5:
    // 0x802C59E8: lw          $t4, 0x0($s4)
    ctx->r12 = MEM_W(ctx->r20, 0X0);
    // 0x802C59EC: lw          $at, 0x0($s7)
    ctx->r1 = MEM_W(ctx->r23, 0X0);
    // 0x802C59F0: addiu       $t8, $s2, 0x38
    ctx->r24 = ADD32(ctx->r18, 0X38);
    // 0x802C59F4: addu        $t5, $t4, $s1
    ctx->r13 = ADD32(ctx->r12, ctx->r17);
    // 0x802C59F8: sw          $at, 0x1280($t5)
    MEM_W(0X1280, ctx->r13) = ctx->r1;
    // 0x802C59FC: lw          $t7, 0x4($s7)
    ctx->r15 = MEM_W(ctx->r23, 0X4);
    // 0x802C5A00: sll         $t9, $t8, 2
    ctx->r25 = S32(ctx->r24 << 2);
    // 0x802C5A04: addiu       $s0, $s0, 0x1
    ctx->r16 = ADD32(ctx->r16, 0X1);
    // 0x802C5A08: sw          $t7, 0x1284($t5)
    MEM_W(0X1284, ctx->r13) = ctx->r15;
    // 0x802C5A0C: lw          $at, 0x8($s7)
    ctx->r1 = MEM_W(ctx->r23, 0X8);
    // 0x802C5A10: sll         $t2, $s3, 2
    ctx->r10 = S32(ctx->r19 << 2);
    // 0x802C5A14: addiu       $s3, $s3, 0x12
    ctx->r19 = ADD32(ctx->r19, 0X12);
    // 0x802C5A18: sw          $at, 0x1288($t5)
    MEM_W(0X1288, ctx->r13) = ctx->r1;
    // 0x802C5A1C: lw          $t7, 0xC($s7)
    ctx->r15 = MEM_W(ctx->r23, 0XC);
    // 0x802C5A20: slti        $at, $s0, 0x3
    ctx->r1 = SIGNED(ctx->r16) < 0X3 ? 1 : 0;
    // 0x802C5A24: addiu       $s5, $s5, 0x40
    ctx->r21 = ADD32(ctx->r21, 0X40);
    // 0x802C5A28: sw          $t7, 0x128C($t5)
    MEM_W(0X128C, ctx->r13) = ctx->r15;
    // 0x802C5A2C: lw          $t0, 0x0($s4)
    ctx->r8 = MEM_W(ctx->r20, 0X0);
    // 0x802C5A30: addu        $t1, $t0, $s1
    ctx->r9 = ADD32(ctx->r8, ctx->r17);
    // 0x802C5A34: sh          $t9, 0x1288($t1)
    MEM_H(0X1288, ctx->r9) = ctx->r25;
    // 0x802C5A38: lw          $t3, 0x0($s4)
    ctx->r11 = MEM_W(ctx->r20, 0X0);
    // 0x802C5A3C: addu        $t4, $t3, $s1
    ctx->r12 = ADD32(ctx->r11, ctx->r17);
    // 0x802C5A40: addiu       $s1, $s1, 0x10
    ctx->r17 = ADD32(ctx->r17, 0X10);
    // 0x802C5A44: bne         $at, $zero, L_802C59BC
    if (ctx->r1 != 0) {
        // 0x802C5A48: sh          $t2, 0x128A($t4)
        MEM_H(0X128A, ctx->r12) = ctx->r10;
            goto L_802C59BC;
    }
    // 0x802C5A48: sh          $t2, 0x128A($t4)
    MEM_H(0X128A, ctx->r12) = ctx->r10;
    // 0x802C5A4C: lui         $v0, 0x801C
    ctx->r2 = S32(0X801C << 16);
    // 0x802C5A50: lw          $v0, 0x2650($v0)
    ctx->r2 = MEM_W(ctx->r2, 0X2650);
    // 0x802C5A54: bne         $v0, $zero, L_802C5AD0
    if (ctx->r2 != 0) {
        // 0x802C5A58: nop
    
            goto L_802C5AD0;
    }
    // 0x802C5A58: nop

    // 0x802C5A5C: lw          $t6, 0x0($s4)
    ctx->r14 = MEM_W(ctx->r20, 0X0);
    // 0x802C5A60: or          $a0, $s6, $zero
    ctx->r4 = ctx->r22 | 0;
    // 0x802C5A64: addu        $a1, $t6, $s5
    ctx->r5 = ADD32(ctx->r14, ctx->r21);
    // 0x802C5A68: jal         0x80047EE0
    // 0x802C5A6C: addiu       $a1, $a1, 0xA80
    ctx->r5 = ADD32(ctx->r5, 0XA80);
    SysUtils_MtxFToMtx(rdram, ctx);
        goto after_6;
    // 0x802C5A6C: addiu       $a1, $a1, 0xA80
    ctx->r5 = ADD32(ctx->r5, 0XA80);
    after_6:
    // 0x802C5A70: lw          $t5, 0x0($s4)
    ctx->r13 = MEM_W(ctx->r20, 0X0);
    // 0x802C5A74: lw          $at, 0x0($s7)
    ctx->r1 = MEM_W(ctx->r23, 0X0);
    // 0x802C5A78: addiu       $t6, $zero, 0x2A8
    ctx->r14 = ADD32(0, 0X2A8);
    // 0x802C5A7C: addu        $t7, $t5, $s1
    ctx->r15 = ADD32(ctx->r13, ctx->r17);
    // 0x802C5A80: sw          $at, 0x1280($t7)
    MEM_W(0X1280, ctx->r15) = ctx->r1;
    // 0x802C5A84: lw          $t0, 0x4($s7)
    ctx->r8 = MEM_W(ctx->r23, 0X4);
    // 0x802C5A88: lui         $v0, 0x801C
    ctx->r2 = S32(0X801C << 16);
    // 0x802C5A8C: addiu       $s5, $s5, 0x40
    ctx->r21 = ADD32(ctx->r21, 0X40);
    // 0x802C5A90: sw          $t0, 0x1284($t7)
    MEM_W(0X1284, ctx->r15) = ctx->r8;
    // 0x802C5A94: lw          $at, 0x8($s7)
    ctx->r1 = MEM_W(ctx->r23, 0X8);
    // 0x802C5A98: sw          $at, 0x1288($t7)
    MEM_W(0X1288, ctx->r15) = ctx->r1;
    // 0x802C5A9C: lw          $t0, 0xC($s7)
    ctx->r8 = MEM_W(ctx->r23, 0XC);
    // 0x802C5AA0: sw          $t0, 0x128C($t7)
    MEM_W(0X128C, ctx->r15) = ctx->r8;
    // 0x802C5AA4: lw          $t9, 0x0($fp)
    ctx->r25 = MEM_W(ctx->r30, 0X0);
    // 0x802C5AA8: lw          $t2, 0x0($s4)
    ctx->r10 = MEM_W(ctx->r20, 0X0);
    // 0x802C5AAC: addiu       $t1, $t9, 0x38
    ctx->r9 = ADD32(ctx->r25, 0X38);
    // 0x802C5AB0: sll         $t3, $t1, 2
    ctx->r11 = S32(ctx->r9 << 2);
    // 0x802C5AB4: addu        $t4, $t2, $s1
    ctx->r12 = ADD32(ctx->r10, ctx->r17);
    // 0x802C5AB8: sh          $t3, 0x1288($t4)
    MEM_H(0X1288, ctx->r12) = ctx->r11;
    // 0x802C5ABC: lw          $t5, 0x0($s4)
    ctx->r13 = MEM_W(ctx->r20, 0X0);
    // 0x802C5AC0: addu        $t8, $t5, $s1
    ctx->r24 = ADD32(ctx->r13, ctx->r17);
    // 0x802C5AC4: sh          $t6, 0x128A($t8)
    MEM_H(0X128A, ctx->r24) = ctx->r14;
    // 0x802C5AC8: lw          $v0, 0x2650($v0)
    ctx->r2 = MEM_W(ctx->r2, 0X2650);
    // 0x802C5ACC: addiu       $s1, $s1, 0x10
    ctx->r17 = ADD32(ctx->r17, 0X10);
L_802C5AD0:
    // 0x802C5AD0: bne         $v0, $zero, L_802C5AE0
    if (ctx->r2 != 0) {
        // 0x802C5AD4: lui         $s2, 0x802C
        ctx->r18 = S32(0X802C << 16);
            goto L_802C5AE0;
    }
    // 0x802C5AD4: lui         $s2, 0x802C
    ctx->r18 = S32(0X802C << 16);
    // 0x802C5AD8: b           L_802C5AE4
    // 0x802C5ADC: lw          $s2, 0x6D34($s2)
    ctx->r18 = MEM_W(ctx->r18, 0X6D34);
        goto L_802C5AE4;
    // 0x802C5ADC: lw          $s2, 0x6D34($s2)
    ctx->r18 = MEM_W(ctx->r18, 0X6D34);
L_802C5AE0:
    // 0x802C5AE0: lw          $s2, 0x0($fp)
    ctx->r18 = MEM_W(ctx->r30, 0X0);
L_802C5AE4:
    // 0x802C5AE4: lw          $t7, 0x0($s4)
    ctx->r15 = MEM_W(ctx->r20, 0X0);
    // 0x802C5AE8: or          $a0, $s6, $zero
    ctx->r4 = ctx->r22 | 0;
    // 0x802C5AEC: addu        $a1, $t7, $s5
    ctx->r5 = ADD32(ctx->r15, ctx->r21);
    // 0x802C5AF0: jal         0x80047EE0
    // 0x802C5AF4: addiu       $a1, $a1, 0xA80
    ctx->r5 = ADD32(ctx->r5, 0XA80);
    SysUtils_MtxFToMtx(rdram, ctx);
        goto after_7;
    // 0x802C5AF4: addiu       $a1, $a1, 0xA80
    ctx->r5 = ADD32(ctx->r5, 0XA80);
    after_7:
    // 0x802C5AF8: lw          $t0, 0x0($s4)
    ctx->r8 = MEM_W(ctx->r20, 0X0);
    // 0x802C5AFC: lw          $at, 0x0($s7)
    ctx->r1 = MEM_W(ctx->r23, 0X0);
    // 0x802C5B00: addiu       $t3, $s2, 0x38
    ctx->r11 = ADD32(ctx->r18, 0X38);
    // 0x802C5B04: addu        $t9, $t0, $s1
    ctx->r25 = ADD32(ctx->r8, ctx->r17);
    // 0x802C5B08: sw          $at, 0x1280($t9)
    MEM_W(0X1280, ctx->r25) = ctx->r1;
    // 0x802C5B0C: lw          $t2, 0x4($s7)
    ctx->r10 = MEM_W(ctx->r23, 0X4);
    // 0x802C5B10: sll         $t4, $t3, 2
    ctx->r12 = S32(ctx->r11 << 2);
    // 0x802C5B14: addiu       $t8, $zero, 0x338
    ctx->r24 = ADD32(0, 0X338);
    // 0x802C5B18: sw          $t2, 0x1284($t9)
    MEM_W(0X1284, ctx->r25) = ctx->r10;
    // 0x802C5B1C: lw          $at, 0x8($s7)
    ctx->r1 = MEM_W(ctx->r23, 0X8);
    // 0x802C5B20: sw          $at, 0x1288($t9)
    MEM_W(0X1288, ctx->r25) = ctx->r1;
    // 0x802C5B24: lw          $t2, 0xC($s7)
    ctx->r10 = MEM_W(ctx->r23, 0XC);
    // 0x802C5B28: sw          $t2, 0x128C($t9)
    MEM_W(0X128C, ctx->r25) = ctx->r10;
    // 0x802C5B2C: lw          $t5, 0x0($s4)
    ctx->r13 = MEM_W(ctx->r20, 0X0);
    // 0x802C5B30: addu        $t6, $t5, $s1
    ctx->r14 = ADD32(ctx->r13, ctx->r17);
    // 0x802C5B34: sh          $t4, 0x1288($t6)
    MEM_H(0X1288, ctx->r14) = ctx->r12;
    // 0x802C5B38: lw          $t7, 0x0($s4)
    ctx->r15 = MEM_W(ctx->r20, 0X0);
    // 0x802C5B3C: addu        $t0, $t7, $s1
    ctx->r8 = ADD32(ctx->r15, ctx->r17);
    // 0x802C5B40: sh          $t8, 0x128A($t0)
    MEM_H(0X128A, ctx->r8) = ctx->r24;
    // 0x802C5B44: lw          $ra, 0x5C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X5C);
    // 0x802C5B48: lw          $fp, 0x58($sp)
    ctx->r30 = MEM_W(ctx->r29, 0X58);
    // 0x802C5B4C: lw          $s7, 0x54($sp)
    ctx->r23 = MEM_W(ctx->r29, 0X54);
    // 0x802C5B50: lw          $s6, 0x50($sp)
    ctx->r22 = MEM_W(ctx->r29, 0X50);
    // 0x802C5B54: lw          $s5, 0x4C($sp)
    ctx->r21 = MEM_W(ctx->r29, 0X4C);
    // 0x802C5B58: lw          $s4, 0x48($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X48);
    // 0x802C5B5C: lw          $s3, 0x44($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X44);
    // 0x802C5B60: lw          $s2, 0x40($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X40);
    // 0x802C5B64: lw          $s1, 0x3C($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X3C);
    // 0x802C5B68: lw          $s0, 0x38($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X38);
    // 0x802C5B6C: jr          $ra
    // 0x802C5B70: addiu       $sp, $sp, 0x1B8
    ctx->r29 = ADD32(ctx->r29, 0X1B8);
    return;
    // 0x802C5B70: addiu       $sp, $sp, 0x1B8
    ctx->r29 = ADD32(ctx->r29, 0X1B8);
;}
RECOMP_FUNC void func_i6_802C5B74(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C5B74: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x802C5B78: addiu       $v0, $v0, -0x19C4
    ctx->r2 = ADD32(ctx->r2, -0X19C4);
    // 0x802C5B7C: lw          $t6, 0x0($v0)
    ctx->r14 = MEM_W(ctx->r2, 0X0);
    // 0x802C5B80: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x802C5B84: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x802C5B88: beq         $t6, $zero, L_802C5BC8
    if (ctx->r14 == 0) {
        // 0x802C5B8C: lui         $t7, 0x800E
        ctx->r15 = S32(0X800E << 16);
            goto L_802C5BC8;
    }
    // 0x802C5B8C: lui         $t7, 0x800E
    ctx->r15 = S32(0X800E << 16);
    // 0x802C5B90: sw          $zero, 0x0($v0)
    MEM_W(0X0, ctx->r2) = 0;
    // 0x802C5B94: lw          $t7, -0x54DC($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X54DC);
    // 0x802C5B98: addiu       $at, $zero, 0x32
    ctx->r1 = ADD32(0, 0X32);
    // 0x802C5B9C: lui         $t8, 0x801D
    ctx->r24 = S32(0X801D << 16);
    // 0x802C5BA0: bne         $t7, $at, L_802C5BC8
    if (ctx->r15 != ctx->r1) {
        // 0x802C5BA4: nop
    
            goto L_802C5BC8;
    }
    // 0x802C5BA4: nop

    // 0x802C5BA8: lw          $t8, -0x19CC($t8)
    ctx->r24 = MEM_W(ctx->r24, -0X19CC);
    // 0x802C5BAC: addiu       $at, $zero, 0x64
    ctx->r1 = ADD32(0, 0X64);
    // 0x802C5BB0: beq         $t8, $at, L_802C5BC8
    if (ctx->r24 == ctx->r1) {
        // 0x802C5BB4: nop
    
            goto L_802C5BC8;
    }
    // 0x802C5BB4: nop

    // 0x802C5BB8: jal         0x80093C44
    // 0x802C5BBC: nop

    func_80093C44(rdram, ctx);
        goto after_0;
    // 0x802C5BBC: nop

    after_0:
    // 0x802C5BC0: b           L_802C5C20
    // 0x802C5BC4: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_802C5C20;
    // 0x802C5BC4: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C5BC8:
    // 0x802C5BC8: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x802C5BCC: jal         0x8008FB74
    // 0x802C5BD0: sw          $zero, -0x54D4($at)
    MEM_W(-0X54D4, ctx->r1) = 0;
    func_8008FB74(rdram, ctx);
        goto after_1;
    // 0x802C5BD0: sw          $zero, -0x54D4($at)
    MEM_W(-0X54D4, ctx->r1) = 0;
    after_1:
    // 0x802C5BD4: lui         $a1, 0x800E
    ctx->r5 = S32(0X800E << 16);
    // 0x802C5BD8: lw          $a1, -0x7E90($a1)
    ctx->r5 = MEM_W(ctx->r5, -0X7E90);
    // 0x802C5BDC: jal         0x800949B8
    // 0x802C5BE0: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    func_800949B8(rdram, ctx);
        goto after_2;
    // 0x802C5BE0: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    after_2:
    // 0x802C5BE4: jal         0x80090F58
    // 0x802C5BE8: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    Draw_WaterEffects(rdram, ctx);
        goto after_3;
    // 0x802C5BE8: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    after_3:
    // 0x802C5BEC: jal         0x802C5C2C
    // 0x802C5BF0: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    func_i6_802C5C2C(rdram, ctx);
        goto after_4;
    // 0x802C5BF0: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    after_4:
    // 0x802C5BF4: lui         $t9, 0x800E
    ctx->r25 = S32(0X800E << 16);
    // 0x802C5BF8: lw          $t9, -0x54DC($t9)
    ctx->r25 = MEM_W(ctx->r25, -0X54DC);
    // 0x802C5BFC: addiu       $at, $zero, 0x32
    ctx->r1 = ADD32(0, 0X32);
    // 0x802C5C00: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C5C04: bnel        $t9, $at, L_802C5C1C
    if (ctx->r25 != ctx->r1) {
        // 0x802C5C08: or          $v0, $a0, $zero
        ctx->r2 = ctx->r4 | 0;
            goto L_802C5C1C;
    }
    goto skip_0;
    // 0x802C5C08: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    skip_0:
    // 0x802C5C0C: jal         0x802C6B34
    // 0x802C5C10: sw          $v0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r2;
    func_i6_802C6B34(rdram, ctx);
        goto after_5;
    // 0x802C5C10: sw          $v0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r2;
    after_5:
    // 0x802C5C14: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
    // 0x802C5C18: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
L_802C5C1C:
    // 0x802C5C1C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C5C20:
    // 0x802C5C20: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x802C5C24: jr          $ra
    // 0x802C5C28: nop

    return;
    // 0x802C5C28: nop

;}
RECOMP_FUNC void func_i6_802C5C2C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C5C2C: addiu       $sp, $sp, -0xC0
    ctx->r29 = ADD32(ctx->r29, -0XC0);
    // 0x802C5C30: sw          $s5, 0x54($sp)
    MEM_W(0X54, ctx->r29) = ctx->r21;
    // 0x802C5C34: sw          $ra, 0x64($sp)
    MEM_W(0X64, ctx->r29) = ctx->r31;
    // 0x802C5C38: sw          $fp, 0x60($sp)
    MEM_W(0X60, ctx->r29) = ctx->r30;
    // 0x802C5C3C: sw          $s7, 0x5C($sp)
    MEM_W(0X5C, ctx->r29) = ctx->r23;
    // 0x802C5C40: sw          $s6, 0x58($sp)
    MEM_W(0X58, ctx->r29) = ctx->r22;
    // 0x802C5C44: sw          $s4, 0x50($sp)
    MEM_W(0X50, ctx->r29) = ctx->r20;
    // 0x802C5C48: sw          $s3, 0x4C($sp)
    MEM_W(0X4C, ctx->r29) = ctx->r19;
    // 0x802C5C4C: sw          $s2, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r18;
    // 0x802C5C50: sw          $s1, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r17;
    // 0x802C5C54: sw          $s0, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r16;
    // 0x802C5C58: lui         $t6, 0x107
    ctx->r14 = S32(0X107 << 16);
    // 0x802C5C5C: lui         $s5, 0x600
    ctx->r21 = S32(0X600 << 16);
    // 0x802C5C60: addiu       $t6, $t6, -0x9D8
    ctx->r14 = ADD32(ctx->r14, -0X9D8);
    // 0x802C5C64: sw          $t6, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r14;
    // 0x802C5C68: sw          $s5, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r21;
    // 0x802C5C6C: lui         $a2, 0x802C
    ctx->r6 = S32(0X802C << 16);
    // 0x802C5C70: lw          $a2, 0x6D34($a2)
    ctx->r6 = MEM_W(ctx->r6, 0X6D34);
    // 0x802C5C74: addiu       $s3, $a0, 0x8
    ctx->r19 = ADD32(ctx->r4, 0X8);
    // 0x802C5C78: addiu       $t7, $zero, 0x170
    ctx->r15 = ADD32(0, 0X170);
    // 0x802C5C7C: addiu       $t8, $zero, 0x18
    ctx->r24 = ADD32(0, 0X18);
    // 0x802C5C80: sw          $t8, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r24;
    // 0x802C5C84: sw          $t7, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r15;
    // 0x802C5C88: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
    // 0x802C5C8C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C5C90: addiu       $a3, $zero, 0x1E
    ctx->r7 = ADD32(0, 0X1E);
    // 0x802C5C94: jal         0x80094338
    // 0x802C5C98: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    func_80094338(rdram, ctx);
        goto after_0;
    // 0x802C5C98: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    after_0:
    // 0x802C5C9C: lui         $a2, 0x802C
    ctx->r6 = S32(0X802C << 16);
    // 0x802C5CA0: lw          $a2, 0x6D38($a2)
    ctx->r6 = MEM_W(ctx->r6, 0X6D38);
    // 0x802C5CA4: addiu       $t9, $zero, 0x170
    ctx->r25 = ADD32(0, 0X170);
    // 0x802C5CA8: addiu       $t0, $zero, 0x10
    ctx->r8 = ADD32(0, 0X10);
    // 0x802C5CAC: sw          $t0, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r8;
    // 0x802C5CB0: sw          $t9, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r25;
    // 0x802C5CB4: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C5CB8: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C5CBC: addiu       $a3, $zero, 0x44
    ctx->r7 = ADD32(0, 0X44);
    // 0x802C5CC0: jal         0x80094338
    // 0x802C5CC4: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    func_80094338(rdram, ctx);
        goto after_1;
    // 0x802C5CC4: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    after_1:
    // 0x802C5CC8: or          $s3, $v0, $zero
    ctx->r19 = ctx->r2 | 0;
    // 0x802C5CCC: or          $s1, $zero, $zero
    ctx->r17 = 0 | 0;
    // 0x802C5CD0: addiu       $s2, $zero, 0x5A
    ctx->r18 = ADD32(0, 0X5A);
L_802C5CD4:
    // 0x802C5CD4: andi        $t1, $s1, 0x1
    ctx->r9 = ctx->r17 & 0X1;
    // 0x802C5CD8: beq         $t1, $zero, L_802C5CEC
    if (ctx->r9 == 0) {
        // 0x802C5CDC: or          $a0, $s3, $zero
        ctx->r4 = ctx->r19 | 0;
            goto L_802C5CEC;
    }
    // 0x802C5CDC: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
    // 0x802C5CE0: lui         $s0, 0x802C
    ctx->r16 = S32(0X802C << 16);
    // 0x802C5CE4: b           L_802C5CF4
    // 0x802C5CE8: lw          $s0, 0x6D38($s0)
    ctx->r16 = MEM_W(ctx->r16, 0X6D38);
        goto L_802C5CF4;
    // 0x802C5CE8: lw          $s0, 0x6D38($s0)
    ctx->r16 = MEM_W(ctx->r16, 0X6D38);
L_802C5CEC:
    // 0x802C5CEC: lui         $s0, 0x802C
    ctx->r16 = S32(0X802C << 16);
    // 0x802C5CF0: lw          $s0, 0x6D34($s0)
    ctx->r16 = MEM_W(ctx->r16, 0X6D34);
L_802C5CF4:
    // 0x802C5CF4: addiu       $t2, $zero, 0x170
    ctx->r10 = ADD32(0, 0X170);
    // 0x802C5CF8: addiu       $t3, $zero, 0x10
    ctx->r11 = ADD32(0, 0X10);
    // 0x802C5CFC: sw          $t3, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r11;
    // 0x802C5D00: sw          $t2, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r10;
    // 0x802C5D04: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C5D08: addiu       $a2, $s0, 0x8
    ctx->r6 = ADD32(ctx->r16, 0X8);
    // 0x802C5D0C: jal         0x80094338
    // 0x802C5D10: or          $a3, $s2, $zero
    ctx->r7 = ctx->r18 | 0;
    func_80094338(rdram, ctx);
        goto after_2;
    // 0x802C5D10: or          $a3, $s2, $zero
    ctx->r7 = ctx->r18 | 0;
    after_2:
    // 0x802C5D14: addiu       $s1, $s1, 0x1
    ctx->r17 = ADD32(ctx->r17, 0X1);
    // 0x802C5D18: slti        $at, $s1, 0x3
    ctx->r1 = SIGNED(ctx->r17) < 0X3 ? 1 : 0;
    // 0x802C5D1C: addiu       $s2, $s2, 0x12
    ctx->r18 = ADD32(ctx->r18, 0X12);
    // 0x802C5D20: bne         $at, $zero, L_802C5CD4
    if (ctx->r1 != 0) {
        // 0x802C5D24: or          $s3, $v0, $zero
        ctx->r19 = ctx->r2 | 0;
            goto L_802C5CD4;
    }
    // 0x802C5D24: or          $s3, $v0, $zero
    ctx->r19 = ctx->r2 | 0;
    // 0x802C5D28: lui         $v1, 0x801C
    ctx->r3 = S32(0X801C << 16);
    // 0x802C5D2C: lw          $v1, 0x2650($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X2650);
    // 0x802C5D30: bne         $v1, $zero, L_802C5D98
    if (ctx->r3 != 0) {
        // 0x802C5D34: lui         $a2, 0x802C
        ctx->r6 = S32(0X802C << 16);
            goto L_802C5D98;
    }
    // 0x802C5D34: lui         $a2, 0x802C
    ctx->r6 = S32(0X802C << 16);
    // 0x802C5D38: lw          $a2, 0x6D38($a2)
    ctx->r6 = MEM_W(ctx->r6, 0X6D38);
    // 0x802C5D3C: addiu       $t4, $zero, 0x170
    ctx->r12 = ADD32(0, 0X170);
    // 0x802C5D40: addiu       $t5, $zero, 0xA
    ctx->r13 = ADD32(0, 0XA);
    // 0x802C5D44: sw          $t5, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r13;
    // 0x802C5D48: sw          $t4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r12;
    // 0x802C5D4C: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C5D50: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C5D54: addiu       $a3, $zero, 0x93
    ctx->r7 = ADD32(0, 0X93);
    // 0x802C5D58: jal         0x80094338
    // 0x802C5D5C: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    func_80094338(rdram, ctx);
        goto after_3;
    // 0x802C5D5C: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    after_3:
    // 0x802C5D60: lui         $a2, 0x802C
    ctx->r6 = S32(0X802C << 16);
    // 0x802C5D64: lw          $a2, 0x6D38($a2)
    ctx->r6 = MEM_W(ctx->r6, 0X6D38);
    // 0x802C5D68: addiu       $t6, $zero, 0x170
    ctx->r14 = ADD32(0, 0X170);
    // 0x802C5D6C: addiu       $t7, $zero, 0x10
    ctx->r15 = ADD32(0, 0X10);
    // 0x802C5D70: sw          $t7, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r15;
    // 0x802C5D74: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x802C5D78: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C5D7C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C5D80: addiu       $a3, $zero, 0x9E
    ctx->r7 = ADD32(0, 0X9E);
    // 0x802C5D84: jal         0x80094338
    // 0x802C5D88: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    func_80094338(rdram, ctx);
        goto after_4;
    // 0x802C5D88: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    after_4:
    // 0x802C5D8C: lui         $v1, 0x801C
    ctx->r3 = S32(0X801C << 16);
    // 0x802C5D90: lw          $v1, 0x2650($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X2650);
    // 0x802C5D94: or          $s3, $v0, $zero
    ctx->r19 = ctx->r2 | 0;
L_802C5D98:
    // 0x802C5D98: bne         $v1, $zero, L_802C5DB0
    if (ctx->r3 != 0) {
        // 0x802C5D9C: or          $a0, $s3, $zero
        ctx->r4 = ctx->r19 | 0;
            goto L_802C5DB0;
    }
    // 0x802C5D9C: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
    // 0x802C5DA0: lui         $t8, 0x802C
    ctx->r24 = S32(0X802C << 16);
    // 0x802C5DA4: lw          $t8, 0x6D34($t8)
    ctx->r24 = MEM_W(ctx->r24, 0X6D34);
    // 0x802C5DA8: b           L_802C5DBC
    // 0x802C5DAC: sw          $t8, 0xB4($sp)
    MEM_W(0XB4, ctx->r29) = ctx->r24;
        goto L_802C5DBC;
    // 0x802C5DAC: sw          $t8, 0xB4($sp)
    MEM_W(0XB4, ctx->r29) = ctx->r24;
L_802C5DB0:
    // 0x802C5DB0: lui         $t9, 0x802C
    ctx->r25 = S32(0X802C << 16);
    // 0x802C5DB4: lw          $t9, 0x6D38($t9)
    ctx->r25 = MEM_W(ctx->r25, 0X6D38);
    // 0x802C5DB8: sw          $t9, 0xB4($sp)
    MEM_W(0XB4, ctx->r29) = ctx->r25;
L_802C5DBC:
    // 0x802C5DBC: lw          $s0, 0xB4($sp)
    ctx->r16 = MEM_W(ctx->r29, 0XB4);
    // 0x802C5DC0: addiu       $t0, $zero, 0x170
    ctx->r8 = ADD32(0, 0X170);
    // 0x802C5DC4: addiu       $t1, $zero, 0xA
    ctx->r9 = ADD32(0, 0XA);
    // 0x802C5DC8: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C5DCC: or          $a2, $s0, $zero
    ctx->r6 = ctx->r16 | 0;
    // 0x802C5DD0: sw          $t1, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r9;
    // 0x802C5DD4: sw          $t0, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r8;
    // 0x802C5DD8: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C5DDC: jal         0x80094338
    // 0x802C5DE0: addiu       $a3, $zero, 0xB7
    ctx->r7 = ADD32(0, 0XB7);
    func_80094338(rdram, ctx);
        goto after_5;
    // 0x802C5DE0: addiu       $a3, $zero, 0xB7
    ctx->r7 = ADD32(0, 0XB7);
    after_5:
    // 0x802C5DE4: addiu       $t2, $zero, 0x170
    ctx->r10 = ADD32(0, 0X170);
    // 0x802C5DE8: addiu       $t3, $zero, 0x10
    ctx->r11 = ADD32(0, 0X10);
    // 0x802C5DEC: sw          $t3, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r11;
    // 0x802C5DF0: sw          $t2, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r10;
    // 0x802C5DF4: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C5DF8: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C5DFC: or          $a2, $s0, $zero
    ctx->r6 = ctx->r16 | 0;
    // 0x802C5E00: jal         0x80094338
    // 0x802C5E04: addiu       $a3, $zero, 0xC2
    ctx->r7 = ADD32(0, 0XC2);
    func_80094338(rdram, ctx);
        goto after_6;
    // 0x802C5E04: addiu       $a3, $zero, 0xC2
    ctx->r7 = ADD32(0, 0XC2);
    after_6:
    // 0x802C5E08: addiu       $t4, $zero, 0xFF
    ctx->r12 = ADD32(0, 0XFF);
    // 0x802C5E0C: sw          $t4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r12;
    // 0x802C5E10: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C5E14: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C5E18: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x802C5E1C: jal         0x801E7E74
    // 0x802C5E20: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_801E7E74(rdram, ctx);
        goto after_7;
    // 0x802C5E20: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_7:
    // 0x802C5E24: or          $s3, $v0, $zero
    ctx->r19 = ctx->r2 | 0;
    // 0x802C5E28: or          $s1, $zero, $zero
    ctx->r17 = 0 | 0;
    // 0x802C5E2C: addiu       $s4, $zero, 0x5C
    ctx->r20 = ADD32(0, 0X5C);
    // 0x802C5E30: addiu       $s2, $zero, 0x68
    ctx->r18 = ADD32(0, 0X68);
L_802C5E34:
    // 0x802C5E34: andi        $t5, $s1, 0x1
    ctx->r13 = ctx->r17 & 0X1;
    // 0x802C5E38: beq         $t5, $zero, L_802C5E4C
    if (ctx->r13 == 0) {
        // 0x802C5E3C: or          $a0, $s3, $zero
        ctx->r4 = ctx->r19 | 0;
            goto L_802C5E4C;
    }
    // 0x802C5E3C: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
    // 0x802C5E40: lui         $s0, 0x802C
    ctx->r16 = S32(0X802C << 16);
    // 0x802C5E44: b           L_802C5E54
    // 0x802C5E48: lw          $s0, 0x6D38($s0)
    ctx->r16 = MEM_W(ctx->r16, 0X6D38);
        goto L_802C5E54;
    // 0x802C5E48: lw          $s0, 0x6D38($s0)
    ctx->r16 = MEM_W(ctx->r16, 0X6D38);
L_802C5E4C:
    // 0x802C5E4C: lui         $s0, 0x802C
    ctx->r16 = S32(0X802C << 16);
    // 0x802C5E50: lw          $s0, 0x6D34($s0)
    ctx->r16 = MEM_W(ctx->r16, 0X6D34);
L_802C5E54:
    // 0x802C5E54: addiu       $a1, $s0, 0x28
    ctx->r5 = ADD32(ctx->r16, 0X28);
    // 0x802C5E58: or          $a2, $s4, $zero
    ctx->r6 = ctx->r20 | 0;
    // 0x802C5E5C: addiu       $a3, $s0, 0x42
    ctx->r7 = ADD32(ctx->r16, 0X42);
    // 0x802C5E60: jal         0x801E7FD8
    // 0x802C5E64: sw          $s2, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r18;
    func_801E7FD8(rdram, ctx);
        goto after_8;
    // 0x802C5E64: sw          $s2, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r18;
    after_8:
    // 0x802C5E68: addiu       $s1, $s1, 0x1
    ctx->r17 = ADD32(ctx->r17, 0X1);
    // 0x802C5E6C: slti        $at, $s1, 0x3
    ctx->r1 = SIGNED(ctx->r17) < 0X3 ? 1 : 0;
    // 0x802C5E70: addiu       $s4, $s4, 0x12
    ctx->r20 = ADD32(ctx->r20, 0X12);
    // 0x802C5E74: addiu       $s2, $s2, 0x12
    ctx->r18 = ADD32(ctx->r18, 0X12);
    // 0x802C5E78: bne         $at, $zero, L_802C5E34
    if (ctx->r1 != 0) {
        // 0x802C5E7C: or          $s3, $v0, $zero
        ctx->r19 = ctx->r2 | 0;
            goto L_802C5E34;
    }
    // 0x802C5E7C: or          $s3, $v0, $zero
    ctx->r19 = ctx->r2 | 0;
    // 0x802C5E80: lui         $t6, 0x801C
    ctx->r14 = S32(0X801C << 16);
    // 0x802C5E84: lw          $t6, 0x2650($t6)
    ctx->r14 = MEM_W(ctx->r14, 0X2650);
    // 0x802C5E88: bne         $t6, $zero, L_802C5EB4
    if (ctx->r14 != 0) {
        // 0x802C5E8C: or          $a0, $v0, $zero
        ctx->r4 = ctx->r2 | 0;
            goto L_802C5EB4;
    }
    // 0x802C5E8C: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C5E90: lui         $v0, 0x802C
    ctx->r2 = S32(0X802C << 16);
    // 0x802C5E94: lw          $v0, 0x6D38($v0)
    ctx->r2 = MEM_W(ctx->r2, 0X6D38);
    // 0x802C5E98: addiu       $t7, $zero, 0xAC
    ctx->r15 = ADD32(0, 0XAC);
    // 0x802C5E9C: sw          $t7, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r15;
    // 0x802C5EA0: addiu       $a2, $zero, 0xA0
    ctx->r6 = ADD32(0, 0XA0);
    // 0x802C5EA4: addiu       $a1, $v0, 0x28
    ctx->r5 = ADD32(ctx->r2, 0X28);
    // 0x802C5EA8: jal         0x801E7FD8
    // 0x802C5EAC: addiu       $a3, $v0, 0x42
    ctx->r7 = ADD32(ctx->r2, 0X42);
    func_801E7FD8(rdram, ctx);
        goto after_9;
    // 0x802C5EAC: addiu       $a3, $v0, 0x42
    ctx->r7 = ADD32(ctx->r2, 0X42);
    after_9:
    // 0x802C5EB0: or          $s3, $v0, $zero
    ctx->r19 = ctx->r2 | 0;
L_802C5EB4:
    // 0x802C5EB4: lw          $v0, 0xB4($sp)
    ctx->r2 = MEM_W(ctx->r29, 0XB4);
    // 0x802C5EB8: addiu       $t8, $zero, 0xD0
    ctx->r24 = ADD32(0, 0XD0);
    // 0x802C5EBC: sw          $t8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r24;
    // 0x802C5EC0: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
    // 0x802C5EC4: addiu       $a2, $zero, 0xC4
    ctx->r6 = ADD32(0, 0XC4);
    // 0x802C5EC8: addiu       $a1, $v0, 0x28
    ctx->r5 = ADD32(ctx->r2, 0X28);
    // 0x802C5ECC: jal         0x801E7FD8
    // 0x802C5ED0: addiu       $a3, $v0, 0x42
    ctx->r7 = ADD32(ctx->r2, 0X42);
    func_801E7FD8(rdram, ctx);
        goto after_10;
    // 0x802C5ED0: addiu       $a3, $v0, 0x42
    ctx->r7 = ADD32(ctx->r2, 0X42);
    after_10:
    // 0x802C5ED4: lui         $t0, 0xED02
    ctx->r8 = S32(0XED02 << 16);
    // 0x802C5ED8: addiu       $t0, $t0, 0x50
    ctx->r8 = ADD32(ctx->r8, 0X50);
    // 0x802C5EDC: lui         $t1, 0x68
    ctx->r9 = S32(0X68 << 16);
    // 0x802C5EE0: addiu       $t1, $t1, -0x3C94
    ctx->r9 = ADD32(ctx->r9, -0X3C94);
    // 0x802C5EE4: lui         $t9, 0xE700
    ctx->r25 = S32(0XE700 << 16);
    // 0x802C5EE8: lui         $t2, 0xB400
    ctx->r10 = S32(0XB400 << 16);
    // 0x802C5EEC: sw          $t9, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r25;
    // 0x802C5EF0: sw          $zero, 0x4($v0)
    MEM_W(0X4, ctx->r2) = 0;
    { extern uint32_t wr64_experimental_viewport_borders(void); if (wr64_experimental_viewport_borders()) { ctx->r8 = 0xED000000U; ctx->r9 = 0x006A03C0U; } }
    // 0x802C5EF4: sw          $t0, 0x8($v0)
    MEM_W(0X8, ctx->r2) = ctx->r8;
    // 0x802C5EF8: sw          $t1, 0xC($v0)
    MEM_W(0XC, ctx->r2) = ctx->r9;
    // 0x802C5EFC: sw          $t2, 0x10($v0)
    MEM_W(0X10, ctx->r2) = ctx->r10;
    // 0x802C5F00: lui         $t3, 0x802C
    ctx->r11 = S32(0X802C << 16);
    // 0x802C5F04: lhu         $t3, 0x6D40($t3)
    ctx->r11 = MEM_HU(ctx->r11, 0X6D40);
    // 0x802C5F08: lui         $t4, 0x103
    ctx->r12 = S32(0X103 << 16);
    // 0x802C5F0C: lui         $t5, 0x700
    ctx->r13 = S32(0X700 << 16);
    // 0x802C5F10: sw          $s5, 0x20($v0)
    MEM_W(0X20, ctx->r2) = ctx->r21;
    // 0x802C5F14: lui         $t6, 0x107
    ctx->r14 = S32(0X107 << 16);
    // 0x802C5F18: addiu       $t5, $t5, 0xA40
    ctx->r13 = ADD32(ctx->r13, 0XA40);
    // 0x802C5F1C: ori         $t4, $t4, 0x40
    ctx->r12 = ctx->r12 | 0X40;
    // 0x802C5F20: addiu       $t6, $t6, -0xB78
    ctx->r14 = ADD32(ctx->r14, -0XB78);
    // 0x802C5F24: lui         $s5, 0x380
    ctx->r21 = S32(0X380 << 16);
    // 0x802C5F28: lui         $s0, 0x700
    ctx->r16 = S32(0X700 << 16);
    // 0x802C5F2C: lui         $s4, 0x700
    ctx->r20 = S32(0X700 << 16);
    // 0x802C5F30: lui         $fp, 0x800E
    ctx->r30 = S32(0X800E << 16);
    // 0x802C5F34: lui         $s7, 0x800E
    ctx->r23 = S32(0X800E << 16);
    // 0x802C5F38: lui         $s6, 0x102
    ctx->r22 = S32(0X102 << 16);
    // 0x802C5F3C: sw          $t4, 0x18($v0)
    MEM_W(0X18, ctx->r2) = ctx->r12;
    // 0x802C5F40: sw          $t5, 0x1C($v0)
    MEM_W(0X1C, ctx->r2) = ctx->r13;
    // 0x802C5F44: sw          $t6, 0x24($v0)
    MEM_W(0X24, ctx->r2) = ctx->r14;
    // 0x802C5F48: addiu       $s3, $v0, 0x28
    ctx->r19 = ADD32(ctx->r2, 0X28);
    // 0x802C5F4C: ori         $s6, $s6, 0x40
    ctx->r22 = ctx->r22 | 0X40;
    // 0x802C5F50: addiu       $s7, $s7, -0x5498
    ctx->r23 = ADD32(ctx->r23, -0X5498);
    // 0x802C5F54: addiu       $fp, $fp, -0x7E90
    ctx->r30 = ADD32(ctx->r30, -0X7E90);
    // 0x802C5F58: addiu       $s4, $s4, 0xA80
    ctx->r20 = ADD32(ctx->r20, 0XA80);
    // 0x802C5F5C: addiu       $s0, $s0, 0x1280
    ctx->r16 = ADD32(ctx->r16, 0X1280);
    // 0x802C5F60: ori         $s5, $s5, 0x10
    ctx->r21 = ctx->r21 | 0X10;
    // 0x802C5F64: or          $s1, $zero, $zero
    ctx->r17 = 0 | 0;
    // 0x802C5F68: sw          $t3, 0x14($v0)
    MEM_W(0X14, ctx->r2) = ctx->r11;
L_802C5F6C:
    // 0x802C5F6C: lh          $t7, 0x0($s7)
    ctx->r15 = MEM_H(ctx->r23, 0X0);
    // 0x802C5F70: or          $v0, $s3, $zero
    ctx->r2 = ctx->r19 | 0;
    // 0x802C5F74: addiu       $s3, $s3, 0x8
    ctx->r19 = ADD32(ctx->r19, 0X8);
    // 0x802C5F78: beq         $t7, $zero, L_802C5FA0
    if (ctx->r15 == 0) {
        // 0x802C5F7C: or          $v1, $s3, $zero
        ctx->r3 = ctx->r19 | 0;
            goto L_802C5FA0;
    }
    // 0x802C5F7C: or          $v1, $s3, $zero
    ctx->r3 = ctx->r19 | 0;
    // 0x802C5F80: lw          $t8, 0x0($fp)
    ctx->r24 = MEM_W(ctx->r30, 0X0);
    // 0x802C5F84: lui         $t0, 0x801C
    ctx->r8 = S32(0X801C << 16);
    // 0x802C5F88: addiu       $t0, $t0, 0x23B0
    ctx->r8 = ADD32(ctx->r8, 0X23B0);
    // 0x802C5F8C: sll         $t9, $t8, 2
    ctx->r25 = S32(ctx->r24 << 2);
    // 0x802C5F90: addu        $t9, $t9, $t8
    ctx->r25 = ADD32(ctx->r25, ctx->r24);
    // 0x802C5F94: sll         $t9, $t9, 2
    ctx->r25 = S32(ctx->r25 << 2);
    // 0x802C5F98: b           L_802C5FCC
    // 0x802C5F9C: addu        $s2, $t9, $t0
    ctx->r18 = ADD32(ctx->r25, ctx->r8);
        goto L_802C5FCC;
    // 0x802C5F9C: addu        $s2, $t9, $t0
    ctx->r18 = ADD32(ctx->r25, ctx->r8);
L_802C5FA0:
    // 0x802C5FA0: lw          $t1, 0x0($fp)
    ctx->r9 = MEM_W(ctx->r30, 0X0);
    // 0x802C5FA4: sll         $t3, $s1, 2
    ctx->r11 = S32(ctx->r17 << 2);
    // 0x802C5FA8: addu        $t3, $t3, $s1
    ctx->r11 = ADD32(ctx->r11, ctx->r17);
    // 0x802C5FAC: sll         $t2, $t1, 4
    ctx->r10 = S32(ctx->r9 << 4);
    // 0x802C5FB0: subu        $t2, $t2, $t1
    ctx->r10 = SUB32(ctx->r10, ctx->r9);
    // 0x802C5FB4: sll         $t2, $t2, 2
    ctx->r10 = S32(ctx->r10 << 2);
    // 0x802C5FB8: sll         $t3, $t3, 2
    ctx->r11 = S32(ctx->r11 << 2);
    // 0x802C5FBC: lui         $t5, 0x801C
    ctx->r13 = S32(0X801C << 16);
    // 0x802C5FC0: addiu       $t5, $t5, 0x1FF0
    ctx->r13 = ADD32(ctx->r13, 0X1FF0);
    // 0x802C5FC4: addu        $t4, $t2, $t3
    ctx->r12 = ADD32(ctx->r10, ctx->r11);
    // 0x802C5FC8: addu        $s2, $t4, $t5
    ctx->r18 = ADD32(ctx->r12, ctx->r13);
L_802C5FCC:
    // 0x802C5FCC: sw          $s5, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r21;
    // 0x802C5FD0: sw          $s0, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r16;
    // 0x802C5FD4: sw          $s4, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r20;
    // 0x802C5FD8: sw          $s6, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r22;
    // 0x802C5FDC: lh          $t6, 0x0($s7)
    ctx->r14 = MEM_H(ctx->r23, 0X0);
    // 0x802C5FE0: addiu       $s3, $s3, 0x8
    ctx->r19 = ADD32(ctx->r19, 0X8);
    // 0x802C5FE4: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
    // 0x802C5FE8: beq         $t6, $zero, L_802C6030
    if (ctx->r14 == 0) {
        // 0x802C5FEC: or          $a2, $zero, $zero
        ctx->r6 = 0 | 0;
            goto L_802C6030;
    }
    // 0x802C5FEC: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x802C5FF0: bne         $s1, $zero, L_802C6060
    if (ctx->r17 != 0) {
        // 0x802C5FF4: or          $a0, $s3, $zero
        ctx->r4 = ctx->r19 | 0;
            goto L_802C6060;
    }
    // 0x802C5FF4: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
    // 0x802C5FF8: lui         $t7, 0x801D
    ctx->r15 = S32(0X801D << 16);
    // 0x802C5FFC: lw          $t7, -0x1A08($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X1A08);
    // 0x802C6000: sll         $t8, $s1, 2
    ctx->r24 = S32(ctx->r17 << 2);
    // 0x802C6004: subu        $t8, $t8, $s1
    ctx->r24 = SUB32(ctx->r24, ctx->r17);
    // 0x802C6008: sll         $t8, $t8, 6
    ctx->r24 = S32(ctx->r24 << 6);
    // 0x802C600C: addu        $t9, $t7, $t8
    ctx->r25 = ADD32(ctx->r15, ctx->r24);
    // 0x802C6010: addiu       $t0, $t9, 0xC80
    ctx->r8 = ADD32(ctx->r25, 0XC80);
    // 0x802C6014: lw          $a1, 0x4($s2)
    ctx->r5 = MEM_W(ctx->r18, 0X4);
    // 0x802C6018: sw          $t0, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r8;
    // 0x802C601C: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x802C6020: jal         0x801E4FE8
    // 0x802C6024: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_801E4FE8(rdram, ctx);
        goto after_11;
    // 0x802C6024: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_11:
    // 0x802C6028: b           L_802C6060
    // 0x802C602C: or          $s3, $v0, $zero
    ctx->r19 = ctx->r2 | 0;
        goto L_802C6060;
    // 0x802C602C: or          $s3, $v0, $zero
    ctx->r19 = ctx->r2 | 0;
L_802C6030:
    // 0x802C6030: lui         $t1, 0x801D
    ctx->r9 = S32(0X801D << 16);
    // 0x802C6034: lw          $t1, -0x1A08($t1)
    ctx->r9 = MEM_W(ctx->r9, -0X1A08);
    // 0x802C6038: sll         $t2, $s1, 2
    ctx->r10 = S32(ctx->r17 << 2);
    // 0x802C603C: subu        $t2, $t2, $s1
    ctx->r10 = SUB32(ctx->r10, ctx->r17);
    // 0x802C6040: sll         $t2, $t2, 6
    ctx->r10 = S32(ctx->r10 << 6);
    // 0x802C6044: addu        $t3, $t1, $t2
    ctx->r11 = ADD32(ctx->r9, ctx->r10);
    // 0x802C6048: addiu       $t4, $t3, 0xC80
    ctx->r12 = ADD32(ctx->r11, 0XC80);
    // 0x802C604C: lw          $a1, 0x4($s2)
    ctx->r5 = MEM_W(ctx->r18, 0X4);
    // 0x802C6050: sw          $t4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r12;
    // 0x802C6054: jal         0x801E4FE8
    // 0x802C6058: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_801E4FE8(rdram, ctx);
        goto after_12;
    // 0x802C6058: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_12:
    // 0x802C605C: or          $s3, $v0, $zero
    ctx->r19 = ctx->r2 | 0;
L_802C6060:
    // 0x802C6060: addiu       $s1, $s1, 0x1
    ctx->r17 = ADD32(ctx->r17, 0X1);
    // 0x802C6064: slti        $at, $s1, 0x3
    ctx->r1 = SIGNED(ctx->r17) < 0X3 ? 1 : 0;
    // 0x802C6068: addiu       $s0, $s0, 0x10
    ctx->r16 = ADD32(ctx->r16, 0X10);
    // 0x802C606C: bne         $at, $zero, L_802C5F6C
    if (ctx->r1 != 0) {
        // 0x802C6070: addiu       $s4, $s4, 0x40
        ctx->r20 = ADD32(ctx->r20, 0X40);
            goto L_802C5F6C;
    }
    // 0x802C6070: addiu       $s4, $s4, 0x40
    ctx->r20 = ADD32(ctx->r20, 0X40);
    // 0x802C6074: lui         $t5, 0x801C
    ctx->r13 = S32(0X801C << 16);
    // 0x802C6078: lw          $t5, 0x2650($t5)
    ctx->r13 = MEM_W(ctx->r13, 0X2650);
    // 0x802C607C: bne         $t5, $zero, L_802C60F0
    if (ctx->r13 != 0) {
        // 0x802C6080: or          $v0, $s3, $zero
        ctx->r2 = ctx->r19 | 0;
            goto L_802C60F0;
    }
    // 0x802C6080: or          $v0, $s3, $zero
    ctx->r2 = ctx->r19 | 0;
    // 0x802C6084: sw          $s5, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r21;
    // 0x802C6088: sw          $s0, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r16;
    // 0x802C608C: addiu       $v1, $s3, 0x8
    ctx->r3 = ADD32(ctx->r19, 0X8);
    // 0x802C6090: sw          $s6, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r22;
    // 0x802C6094: sw          $s4, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r20;
    // 0x802C6098: lui         $t6, 0x800D
    ctx->r14 = S32(0X800D << 16);
    // 0x802C609C: lui         $t8, 0x801D
    ctx->r24 = S32(0X801D << 16);
    // 0x802C60A0: lw          $t8, -0x1A08($t8)
    ctx->r24 = MEM_W(ctx->r24, -0X1A08);
    // 0x802C60A4: lw          $t6, 0x48DC($t6)
    ctx->r14 = MEM_W(ctx->r14, 0X48DC);
    // 0x802C60A8: sll         $t9, $s1, 2
    ctx->r25 = S32(ctx->r17 << 2);
    // 0x802C60AC: subu        $t9, $t9, $s1
    ctx->r25 = SUB32(ctx->r25, ctx->r17);
    // 0x802C60B0: sll         $t9, $t9, 6
    ctx->r25 = S32(ctx->r25 << 6);
    // 0x802C60B4: lui         $a1, 0x800E
    ctx->r5 = S32(0X800E << 16);
    // 0x802C60B8: addu        $t0, $t8, $t9
    ctx->r8 = ADD32(ctx->r24, ctx->r25);
    // 0x802C60BC: sll         $t7, $t6, 2
    ctx->r15 = S32(ctx->r14 << 2);
    // 0x802C60C0: addu        $a1, $a1, $t7
    ctx->r5 = ADD32(ctx->r5, ctx->r15);
    // 0x802C60C4: addiu       $t1, $t0, 0xC80
    ctx->r9 = ADD32(ctx->r8, 0XC80);
    // 0x802C60C8: addiu       $a0, $v1, 0x8
    ctx->r4 = ADD32(ctx->r3, 0X8);
    // 0x802C60CC: sw          $t1, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r9;
    // 0x802C60D0: lw          $a1, -0x5650($a1)
    ctx->r5 = MEM_W(ctx->r5, -0X5650);
    // 0x802C60D4: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x802C60D8: jal         0x801E4FE8
    // 0x802C60DC: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_801E4FE8(rdram, ctx);
        goto after_13;
    // 0x802C60DC: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_13:
    // 0x802C60E0: or          $s3, $v0, $zero
    ctx->r19 = ctx->r2 | 0;
    // 0x802C60E4: addiu       $s1, $s1, 0x1
    ctx->r17 = ADD32(ctx->r17, 0X1);
    // 0x802C60E8: addiu       $s0, $s0, 0x10
    ctx->r16 = ADD32(ctx->r16, 0X10);
    // 0x802C60EC: addiu       $s4, $s4, 0x40
    ctx->r20 = ADD32(ctx->r20, 0X40);
L_802C60F0:
    // 0x802C60F0: lh          $t2, 0x0($s7)
    ctx->r10 = MEM_H(ctx->r23, 0X0);
    // 0x802C60F4: bnel        $t2, $zero, L_802C616C
    if (ctx->r10 != 0) {
        // 0x802C60F8: addiu       $t0, $zero, 0xFF
        ctx->r8 = ADD32(0, 0XFF);
            goto L_802C616C;
    }
    goto skip_0;
    // 0x802C60F8: addiu       $t0, $zero, 0xFF
    ctx->r8 = ADD32(0, 0XFF);
    skip_0:
    // 0x802C60FC: lw          $t3, 0x0($fp)
    ctx->r11 = MEM_W(ctx->r30, 0X0);
    // 0x802C6100: or          $v0, $s3, $zero
    ctx->r2 = ctx->r19 | 0;
    // 0x802C6104: sw          $s5, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r21;
    // 0x802C6108: sw          $s0, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r16;
    // 0x802C610C: addiu       $v1, $s3, 0x8
    ctx->r3 = ADD32(ctx->r19, 0X8);
    // 0x802C6110: sw          $s6, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r22;
    // 0x802C6114: sw          $s4, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r20;
    // 0x802C6118: lui         $t6, 0x801D
    ctx->r14 = S32(0X801D << 16);
    // 0x802C611C: lw          $t6, -0x1A08($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X1A08);
    // 0x802C6120: sll         $t7, $s1, 2
    ctx->r15 = S32(ctx->r17 << 2);
    // 0x802C6124: sll         $t4, $t3, 2
    ctx->r12 = S32(ctx->r11 << 2);
    // 0x802C6128: lui         $t5, 0x801C
    ctx->r13 = S32(0X801C << 16);
    // 0x802C612C: subu        $t7, $t7, $s1
    ctx->r15 = SUB32(ctx->r15, ctx->r17);
    // 0x802C6130: addu        $t4, $t4, $t3
    ctx->r12 = ADD32(ctx->r12, ctx->r11);
    // 0x802C6134: sll         $t4, $t4, 2
    ctx->r12 = S32(ctx->r12 << 2);
    // 0x802C6138: addiu       $t5, $t5, 0x22C0
    ctx->r13 = ADD32(ctx->r13, 0X22C0);
    // 0x802C613C: sll         $t7, $t7, 6
    ctx->r15 = S32(ctx->r15 << 6);
    // 0x802C6140: addu        $s2, $t4, $t5
    ctx->r18 = ADD32(ctx->r12, ctx->r13);
    // 0x802C6144: addu        $t8, $t6, $t7
    ctx->r24 = ADD32(ctx->r14, ctx->r15);
    // 0x802C6148: addiu       $t9, $t8, 0xC80
    ctx->r25 = ADD32(ctx->r24, 0XC80);
    // 0x802C614C: lw          $a1, 0x4($s2)
    ctx->r5 = MEM_W(ctx->r18, 0X4);
    // 0x802C6150: addiu       $a0, $v1, 0x8
    ctx->r4 = ADD32(ctx->r3, 0X8);
    // 0x802C6154: sw          $t9, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r25;
    // 0x802C6158: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x802C615C: jal         0x801E4FE8
    // 0x802C6160: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_801E4FE8(rdram, ctx);
        goto after_14;
    // 0x802C6160: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_14:
    // 0x802C6164: or          $s3, $v0, $zero
    ctx->r19 = ctx->r2 | 0;
    // 0x802C6168: addiu       $t0, $zero, 0xFF
    ctx->r8 = ADD32(0, 0XFF);
L_802C616C:
    // 0x802C616C: addiu       $t1, $zero, 0xFF
    ctx->r9 = ADD32(0, 0XFF);
    // 0x802C6170: addiu       $t2, $zero, 0xFF
    ctx->r10 = ADD32(0, 0XFF);
    // 0x802C6174: addiu       $t3, $zero, 0xFF
    ctx->r11 = ADD32(0, 0XFF);
    // 0x802C6178: addiu       $t4, $zero, 0xFF
    ctx->r12 = ADD32(0, 0XFF);
    // 0x802C617C: addiu       $t5, $zero, 0xFF
    ctx->r13 = ADD32(0, 0XFF);
    // 0x802C6180: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C6184: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C6188: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C618C: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C6190: sw          $t9, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r25;
    // 0x802C6194: sw          $t8, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r24;
    // 0x802C6198: sw          $t7, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r15;
    // 0x802C619C: sw          $t6, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r14;
    // 0x802C61A0: sw          $t5, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r13;
    // 0x802C61A4: sw          $t4, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r12;
    // 0x802C61A8: sw          $t3, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r11;
    // 0x802C61AC: sw          $t2, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r10;
    // 0x802C61B0: sw          $t1, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r9;
    // 0x802C61B4: sw          $t0, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r8;
    // 0x802C61B8: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
    // 0x802C61BC: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C61C0: addiu       $a2, $zero, 0xFF
    ctx->r6 = ADD32(0, 0XFF);
    // 0x802C61C4: jal         0x801E946C
    // 0x802C61C8: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    func_801E946C(rdram, ctx);
        goto after_15;
    // 0x802C61C8: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    after_15:
    // 0x802C61CC: lw          $v1, 0x0($fp)
    ctx->r3 = MEM_W(ctx->r30, 0X0);
    // 0x802C61D0: lui         $t1, 0x802C
    ctx->r9 = S32(0X802C << 16);
    // 0x802C61D4: lui         $t2, 0x802C
    ctx->r10 = S32(0X802C << 16);
    // 0x802C61D8: sll         $t0, $v1, 2
    ctx->r8 = S32(ctx->r3 << 2);
    // 0x802C61DC: addu        $t1, $t1, $t0
    ctx->r9 = ADD32(ctx->r9, ctx->r8);
    // 0x802C61E0: lw          $t1, 0x6C8C($t1)
    ctx->r9 = MEM_W(ctx->r9, 0X6C8C);
    // 0x802C61E4: lw          $t2, 0x6D34($t2)
    ctx->r10 = MEM_W(ctx->r10, 0X6D34);
    // 0x802C61E8: lui         $a2, 0x800E
    ctx->r6 = S32(0X800E << 16);
    // 0x802C61EC: addu        $a2, $a2, $t0
    ctx->r6 = ADD32(ctx->r6, ctx->r8);
    // 0x802C61F0: addiu       $t3, $zero, 0x21
    ctx->r11 = ADD32(0, 0X21);
    // 0x802C61F4: addu        $a3, $t1, $t2
    ctx->r7 = ADD32(ctx->r9, ctx->r10);
    // 0x802C61F8: addiu       $a3, $a3, 0x6C
    ctx->r7 = ADD32(ctx->r7, 0X6C);
    // 0x802C61FC: sw          $t3, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r11;
    // 0x802C6200: lw          $a2, -0x55CC($a2)
    ctx->r6 = MEM_W(ctx->r6, -0X55CC);
    // 0x802C6204: or          $v1, $t0, $zero
    ctx->r3 = ctx->r8 | 0;
    // 0x802C6208: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C620C: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C6210: jal         0x801E3EE0
    // 0x802C6214: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    func_801E3EE0(rdram, ctx);
        goto after_16;
    // 0x802C6214: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    after_16:
    // 0x802C6218: lui         $a3, 0x802C
    ctx->r7 = S32(0X802C << 16);
    // 0x802C621C: lw          $a3, 0x6D38($a3)
    ctx->r7 = MEM_W(ctx->r7, 0X6D38);
    // 0x802C6220: addiu       $t4, $zero, 0x47
    ctx->r12 = ADD32(0, 0X47);
    // 0x802C6224: sw          $t4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r12;
    // 0x802C6228: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C622C: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C6230: addiu       $a2, $zero, 0x1F
    ctx->r6 = ADD32(0, 0X1F);
    // 0x802C6234: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    // 0x802C6238: jal         0x801E3EE0
    // 0x802C623C: addiu       $a3, $a3, 0x17
    ctx->r7 = ADD32(ctx->r7, 0X17);
    func_801E3EE0(rdram, ctx);
        goto after_17;
    // 0x802C623C: addiu       $a3, $a3, 0x17
    ctx->r7 = ADD32(ctx->r7, 0X17);
    after_17:
    // 0x802C6240: lui         $a3, 0x802C
    ctx->r7 = S32(0X802C << 16);
    // 0x802C6244: lw          $a3, 0x6D38($a3)
    ctx->r7 = MEM_W(ctx->r7, 0X6D38);
    // 0x802C6248: addiu       $t5, $zero, 0x47
    ctx->r13 = ADD32(0, 0X47);
    // 0x802C624C: sw          $t5, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r13;
    // 0x802C6250: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C6254: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C6258: addiu       $a2, $zero, 0x11
    ctx->r6 = ADD32(0, 0X11);
    // 0x802C625C: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    // 0x802C6260: jal         0x801E3EE0
    // 0x802C6264: addiu       $a3, $a3, 0x4B
    ctx->r7 = ADD32(ctx->r7, 0X4B);
    func_801E3EE0(rdram, ctx);
        goto after_18;
    // 0x802C6264: addiu       $a3, $a3, 0x4B
    ctx->r7 = ADD32(ctx->r7, 0X4B);
    after_18:
    // 0x802C6268: lui         $a3, 0x802C
    ctx->r7 = S32(0X802C << 16);
    // 0x802C626C: lw          $a3, 0x6D38($a3)
    ctx->r7 = MEM_W(ctx->r7, 0X6D38);
    // 0x802C6270: addiu       $t6, $zero, 0x47
    ctx->r14 = ADD32(0, 0X47);
    // 0x802C6274: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x802C6278: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C627C: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C6280: addiu       $a2, $zero, 0x20
    ctx->r6 = ADD32(0, 0X20);
    // 0x802C6284: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    // 0x802C6288: jal         0x801E3EE0
    // 0x802C628C: addiu       $a3, $a3, 0xEF
    ctx->r7 = ADD32(ctx->r7, 0XEF);
    func_801E3EE0(rdram, ctx);
        goto after_19;
    // 0x802C628C: addiu       $a3, $a3, 0xEF
    ctx->r7 = ADD32(ctx->r7, 0XEF);
    after_19:
    // 0x802C6290: lui         $a3, 0x802C
    ctx->r7 = S32(0X802C << 16);
    // 0x802C6294: lw          $a3, 0x6D38($a3)
    ctx->r7 = MEM_W(ctx->r7, 0X6D38);
    // 0x802C6298: addiu       $t7, $zero, 0x47
    ctx->r15 = ADD32(0, 0X47);
    // 0x802C629C: sw          $t7, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r15;
    // 0x802C62A0: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C62A4: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C62A8: addiu       $a2, $zero, 0x3
    ctx->r6 = ADD32(0, 0X3);
    // 0x802C62AC: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    // 0x802C62B0: jal         0x801E3EE0
    // 0x802C62B4: addiu       $a3, $a3, 0x142
    ctx->r7 = ADD32(ctx->r7, 0X142);
    func_801E3EE0(rdram, ctx);
        goto after_20;
    // 0x802C62B4: addiu       $a3, $a3, 0x142
    ctx->r7 = ADD32(ctx->r7, 0X142);
    after_20:
    // 0x802C62B8: lui         $t8, 0x801C
    ctx->r24 = S32(0X801C << 16);
    // 0x802C62BC: lw          $t8, 0x2650($t8)
    ctx->r24 = MEM_W(ctx->r24, 0X2650);
    // 0x802C62C0: or          $s3, $v0, $zero
    ctx->r19 = ctx->r2 | 0;
    // 0x802C62C4: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C62C8: bne         $t8, $zero, L_802C62F4
    if (ctx->r24 != 0) {
        // 0x802C62CC: or          $a1, $zero, $zero
        ctx->r5 = 0 | 0;
            goto L_802C62F4;
    }
    // 0x802C62CC: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C62D0: lui         $a3, 0x802C
    ctx->r7 = S32(0X802C << 16);
    // 0x802C62D4: lw          $a3, 0x6D38($a3)
    ctx->r7 = MEM_W(ctx->r7, 0X6D38);
    // 0x802C62D8: addiu       $t9, $zero, 0x94
    ctx->r25 = ADD32(0, 0X94);
    // 0x802C62DC: sw          $t9, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r25;
    // 0x802C62E0: addiu       $a2, $zero, 0x19
    ctx->r6 = ADD32(0, 0X19);
    // 0x802C62E4: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    // 0x802C62E8: jal         0x801E3EE0
    // 0x802C62EC: addiu       $a3, $a3, 0x12
    ctx->r7 = ADD32(ctx->r7, 0X12);
    func_801E3EE0(rdram, ctx);
        goto after_21;
    // 0x802C62EC: addiu       $a3, $a3, 0x12
    ctx->r7 = ADD32(ctx->r7, 0X12);
    after_21:
    // 0x802C62F0: or          $s3, $v0, $zero
    ctx->r19 = ctx->r2 | 0;
L_802C62F4:
    // 0x802C62F4: lw          $a3, 0xB4($sp)
    ctx->r7 = MEM_W(ctx->r29, 0XB4);
    // 0x802C62F8: addiu       $t0, $zero, 0xB8
    ctx->r8 = ADD32(0, 0XB8);
    // 0x802C62FC: sw          $t0, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r8;
    // 0x802C6300: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
    // 0x802C6304: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C6308: addiu       $a2, $zero, 0xD
    ctx->r6 = ADD32(0, 0XD);
    // 0x802C630C: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    // 0x802C6310: jal         0x801E3EE0
    // 0x802C6314: addiu       $a3, $a3, 0x12
    ctx->r7 = ADD32(ctx->r7, 0X12);
    func_801E3EE0(rdram, ctx);
        goto after_22;
    // 0x802C6314: addiu       $a3, $a3, 0x12
    ctx->r7 = ADD32(ctx->r7, 0X12);
    after_22:
    // 0x802C6318: lui         $t1, 0x8022
    ctx->r9 = S32(0X8022 << 16);
    // 0x802C631C: addiu       $t1, $t1, 0x6E44
    ctx->r9 = ADD32(ctx->r9, 0X6E44);
    // 0x802C6320: or          $s3, $v0, $zero
    ctx->r19 = ctx->r2 | 0;
    // 0x802C6324: sw          $t1, 0x6C($sp)
    MEM_W(0X6C, ctx->r29) = ctx->r9;
    // 0x802C6328: or          $s1, $zero, $zero
    ctx->r17 = 0 | 0;
    // 0x802C632C: addiu       $s4, $zero, 0x5C
    ctx->r20 = ADD32(0, 0X5C);
    // 0x802C6330: addiu       $s6, $zero, 0x5D
    ctx->r22 = ADD32(0, 0X5D);
    // 0x802C6334: addiu       $s5, $sp, 0xA8
    ctx->r21 = ADD32(ctx->r29, 0XA8);
L_802C6338:
    // 0x802C6338: lh          $t2, 0x0($s7)
    ctx->r10 = MEM_H(ctx->r23, 0X0);
    // 0x802C633C: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
    // 0x802C6340: addiu       $a2, $zero, 0x80
    ctx->r6 = ADD32(0, 0X80);
    // 0x802C6344: beq         $t2, $zero, L_802C6378
    if (ctx->r10 == 0) {
        // 0x802C6348: addiu       $a3, $zero, 0x80
        ctx->r7 = ADD32(0, 0X80);
            goto L_802C6378;
    }
    // 0x802C6348: addiu       $a3, $zero, 0x80
    ctx->r7 = ADD32(0, 0X80);
    // 0x802C634C: bne         $s1, $zero, L_802C6370
    if (ctx->r17 != 0) {
        // 0x802C6350: lui         $t3, 0x801C
        ctx->r11 = S32(0X801C << 16);
            goto L_802C6370;
    }
    // 0x802C6350: lui         $t3, 0x801C
    ctx->r11 = S32(0X801C << 16);
    // 0x802C6354: lw          $t3, 0x2650($t3)
    ctx->r11 = MEM_W(ctx->r11, 0X2650);
    // 0x802C6358: beq         $t3, $zero, L_802C6368
    if (ctx->r11 == 0) {
        // 0x802C635C: nop
    
            goto L_802C6368;
    }
    // 0x802C635C: nop

    // 0x802C6360: b           L_802C63CC
    // 0x802C6364: addiu       $a1, $zero, 0x4
    ctx->r5 = ADD32(0, 0X4);
        goto L_802C63CC;
    // 0x802C6364: addiu       $a1, $zero, 0x4
    ctx->r5 = ADD32(0, 0X4);
L_802C6368:
    // 0x802C6368: b           L_802C63CC
    // 0x802C636C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
        goto L_802C63CC;
    // 0x802C636C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
L_802C6370:
    // 0x802C6370: b           L_802C63CC
    // 0x802C6374: addiu       $a1, $zero, 0x7
    ctx->r5 = ADD32(0, 0X7);
        goto L_802C63CC;
    // 0x802C6374: addiu       $a1, $zero, 0x7
    ctx->r5 = ADD32(0, 0X7);
L_802C6378:
    // 0x802C6378: lui         $v1, 0x801C
    ctx->r3 = S32(0X801C << 16);
    // 0x802C637C: lw          $v1, 0x2650($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X2650);
    // 0x802C6380: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x802C6384: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C6388: beq         $v1, $zero, L_802C63CC
    if (ctx->r3 == 0) {
        // 0x802C638C: nop
    
            goto L_802C63CC;
    }
    // 0x802C638C: nop

    // 0x802C6390: bne         $v1, $at, L_802C63B4
    if (ctx->r3 != ctx->r1) {
        // 0x802C6394: addiu       $t5, $s1, 0x1
        ctx->r13 = ADD32(ctx->r17, 0X1);
            goto L_802C63B4;
    }
    // 0x802C6394: addiu       $t5, $s1, 0x1
    ctx->r13 = ADD32(ctx->r17, 0X1);
    // 0x802C6398: addiu       $t4, $s1, 0x1
    ctx->r12 = ADD32(ctx->r17, 0X1);
    // 0x802C639C: bne         $t4, $v1, L_802C63AC
    if (ctx->r12 != ctx->r3) {
        // 0x802C63A0: nop
    
            goto L_802C63AC;
    }
    // 0x802C63A0: nop

    // 0x802C63A4: b           L_802C63CC
    // 0x802C63A8: addiu       $a1, $zero, 0x4
    ctx->r5 = ADD32(0, 0X4);
        goto L_802C63CC;
    // 0x802C63A8: addiu       $a1, $zero, 0x4
    ctx->r5 = ADD32(0, 0X4);
L_802C63AC:
    // 0x802C63AC: b           L_802C63CC
    // 0x802C63B0: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
        goto L_802C63CC;
    // 0x802C63B0: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
L_802C63B4:
    // 0x802C63B4: bne         $t5, $v1, L_802C63C4
    if (ctx->r13 != ctx->r3) {
        // 0x802C63B8: nop
    
            goto L_802C63C4;
    }
    // 0x802C63B8: nop

    // 0x802C63BC: b           L_802C63CC
    // 0x802C63C0: addiu       $a1, $zero, 0x6
    ctx->r5 = ADD32(0, 0X6);
        goto L_802C63CC;
    // 0x802C63C0: addiu       $a1, $zero, 0x6
    ctx->r5 = ADD32(0, 0X6);
L_802C63C4:
    // 0x802C63C4: b           L_802C63CC
    // 0x802C63C8: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
        goto L_802C63CC;
    // 0x802C63C8: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
L_802C63CC:
    // 0x802C63CC: addiu       $t6, $zero, 0x80
    ctx->r14 = ADD32(0, 0X80);
    // 0x802C63D0: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C63D4: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C63D8: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C63DC: addiu       $t0, $zero, 0xFF
    ctx->r8 = ADD32(0, 0XFF);
    // 0x802C63E0: addiu       $t1, $zero, 0xFF
    ctx->r9 = ADD32(0, 0XFF);
    // 0x802C63E4: addiu       $t2, $zero, 0xFF
    ctx->r10 = ADD32(0, 0XFF);
    // 0x802C63E8: addiu       $t3, $zero, 0xFF
    ctx->r11 = ADD32(0, 0XFF);
    // 0x802C63EC: addiu       $t4, $zero, 0xFF
    ctx->r12 = ADD32(0, 0XFF);
    // 0x802C63F0: addiu       $t5, $zero, 0xFF
    ctx->r13 = ADD32(0, 0XFF);
    // 0x802C63F4: sw          $t5, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r13;
    // 0x802C63F8: sw          $t4, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r12;
    // 0x802C63FC: sw          $t3, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r11;
    // 0x802C6400: sw          $t2, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r10;
    // 0x802C6404: sw          $t1, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r9;
    // 0x802C6408: sw          $t0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r8;
    // 0x802C640C: sw          $t9, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r25;
    // 0x802C6410: sw          $t8, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r24;
    // 0x802C6414: sw          $t7, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r15;
    // 0x802C6418: jal         0x801E946C
    // 0x802C641C: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    func_801E946C(rdram, ctx);
        goto after_23;
    // 0x802C641C: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    after_23:
    // 0x802C6420: lh          $t6, 0x0($s7)
    ctx->r14 = MEM_H(ctx->r23, 0X0);
    // 0x802C6424: or          $s3, $v0, $zero
    ctx->r19 = ctx->r2 | 0;
    // 0x802C6428: andi        $t5, $s1, 0x1
    ctx->r13 = ctx->r17 & 0X1;
    // 0x802C642C: beq         $t6, $zero, L_802C6454
    if (ctx->r14 == 0) {
        // 0x802C6430: or          $a0, $s5, $zero
        ctx->r4 = ctx->r21 | 0;
            goto L_802C6454;
    }
    // 0x802C6430: or          $a0, $s5, $zero
    ctx->r4 = ctx->r21 | 0;
    // 0x802C6434: lw          $t7, 0x0($fp)
    ctx->r15 = MEM_W(ctx->r30, 0X0);
    // 0x802C6438: lui         $t9, 0x801C
    ctx->r25 = S32(0X801C << 16);
    // 0x802C643C: addiu       $t9, $t9, 0x23B0
    ctx->r25 = ADD32(ctx->r25, 0X23B0);
    // 0x802C6440: sll         $t8, $t7, 2
    ctx->r24 = S32(ctx->r15 << 2);
    // 0x802C6444: addu        $t8, $t8, $t7
    ctx->r24 = ADD32(ctx->r24, ctx->r15);
    // 0x802C6448: sll         $t8, $t8, 2
    ctx->r24 = S32(ctx->r24 << 2);
    // 0x802C644C: b           L_802C6480
    // 0x802C6450: addu        $s2, $t8, $t9
    ctx->r18 = ADD32(ctx->r24, ctx->r25);
        goto L_802C6480;
    // 0x802C6450: addu        $s2, $t8, $t9
    ctx->r18 = ADD32(ctx->r24, ctx->r25);
L_802C6454:
    // 0x802C6454: lw          $t0, 0x0($fp)
    ctx->r8 = MEM_W(ctx->r30, 0X0);
    // 0x802C6458: sll         $t2, $s1, 2
    ctx->r10 = S32(ctx->r17 << 2);
    // 0x802C645C: addu        $t2, $t2, $s1
    ctx->r10 = ADD32(ctx->r10, ctx->r17);
    // 0x802C6460: sll         $t1, $t0, 4
    ctx->r9 = S32(ctx->r8 << 4);
    // 0x802C6464: subu        $t1, $t1, $t0
    ctx->r9 = SUB32(ctx->r9, ctx->r8);
    // 0x802C6468: sll         $t1, $t1, 2
    ctx->r9 = S32(ctx->r9 << 2);
    // 0x802C646C: sll         $t2, $t2, 2
    ctx->r10 = S32(ctx->r10 << 2);
    // 0x802C6470: lui         $t4, 0x801C
    ctx->r12 = S32(0X801C << 16);
    // 0x802C6474: addiu       $t4, $t4, 0x1FF0
    ctx->r12 = ADD32(ctx->r12, 0X1FF0);
    // 0x802C6478: addu        $t3, $t1, $t2
    ctx->r11 = ADD32(ctx->r9, ctx->r10);
    // 0x802C647C: addu        $s2, $t3, $t4
    ctx->r18 = ADD32(ctx->r11, ctx->r12);
L_802C6480:
    // 0x802C6480: beq         $t5, $zero, L_802C6494
    if (ctx->r13 == 0) {
        // 0x802C6484: lui         $a1, 0x802C
        ctx->r5 = S32(0X802C << 16);
            goto L_802C6494;
    }
    // 0x802C6484: lui         $a1, 0x802C
    ctx->r5 = S32(0X802C << 16);
    // 0x802C6488: lui         $s0, 0x802C
    ctx->r16 = S32(0X802C << 16);
    // 0x802C648C: b           L_802C649C
    // 0x802C6490: lw          $s0, 0x6D38($s0)
    ctx->r16 = MEM_W(ctx->r16, 0X6D38);
        goto L_802C649C;
    // 0x802C6490: lw          $s0, 0x6D38($s0)
    ctx->r16 = MEM_W(ctx->r16, 0X6D38);
L_802C6494:
    // 0x802C6494: lui         $s0, 0x802C
    ctx->r16 = S32(0X802C << 16);
    // 0x802C6498: lw          $s0, 0x6D34($s0)
    ctx->r16 = MEM_W(ctx->r16, 0X6D34);
L_802C649C:
    // 0x802C649C: addiu       $a2, $s1, 0x1
    ctx->r6 = ADD32(ctx->r17, 0X1);
    // 0x802C64A0: sw          $a2, 0x74($sp)
    MEM_W(0X74, ctx->r29) = ctx->r6;
    // 0x802C64A4: jal         0x800CA210
    // 0x802C64A8: addiu       $a1, $a1, 0x6CB0
    ctx->r5 = ADD32(ctx->r5, 0X6CB0);
    func_800CA210(rdram, ctx);
        goto after_24;
    // 0x802C64A8: addiu       $a1, $a1, 0x6CB0
    ctx->r5 = ADD32(ctx->r5, 0X6CB0);
    after_24:
    // 0x802C64AC: lw          $t6, 0x6C($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X6C);
    // 0x802C64B0: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
    // 0x802C64B4: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C64B8: lb          $t7, 0x1($t6)
    ctx->r15 = MEM_B(ctx->r14, 0X1);
    // 0x802C64BC: sw          $s4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r20;
    // 0x802C64C0: or          $a2, $s5, $zero
    ctx->r6 = ctx->r21 | 0;
    // 0x802C64C4: addu        $a3, $t7, $s0
    ctx->r7 = ADD32(ctx->r15, ctx->r16);
    // 0x802C64C8: jal         0x801E9858
    // 0x802C64CC: addiu       $a3, $a3, 0x11
    ctx->r7 = ADD32(ctx->r7, 0X11);
    func_801E9858(rdram, ctx);
        goto after_25;
    // 0x802C64CC: addiu       $a3, $a3, 0x11
    ctx->r7 = ADD32(ctx->r7, 0X11);
    after_25:
    // 0x802C64D0: lh          $t8, 0x0($s7)
    ctx->r24 = MEM_H(ctx->r23, 0X0);
    // 0x802C64D4: or          $s3, $v0, $zero
    ctx->r19 = ctx->r2 | 0;
    // 0x802C64D8: beql        $t8, $zero, L_802C65D8
    if (ctx->r24 == 0) {
        // 0x802C64DC: lw          $t0, 0x8($s2)
        ctx->r8 = MEM_W(ctx->r18, 0X8);
            goto L_802C65D8;
    }
    goto skip_1;
    // 0x802C64DC: lw          $t0, 0x8($s2)
    ctx->r8 = MEM_W(ctx->r18, 0X8);
    skip_1:
    // 0x802C64E0: bne         $s1, $zero, L_802C6578
    if (ctx->r17 != 0) {
        // 0x802C64E4: or          $a0, $s3, $zero
        ctx->r4 = ctx->r19 | 0;
            goto L_802C6578;
    }
    // 0x802C64E4: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
    // 0x802C64E8: lw          $t9, 0x8($s2)
    ctx->r25 = MEM_W(ctx->r18, 0X8);
    // 0x802C64EC: lui         $a1, 0x802C
    ctx->r5 = S32(0X802C << 16);
    // 0x802C64F0: addiu       $a1, $a1, 0x6CBC
    ctx->r5 = ADD32(ctx->r5, 0X6CBC);
    // 0x802C64F4: bne         $t9, $zero, L_802C651C
    if (ctx->r25 != 0) {
        // 0x802C64F8: or          $a0, $s5, $zero
        ctx->r4 = ctx->r21 | 0;
            goto L_802C651C;
    }
    // 0x802C64F8: or          $a0, $s5, $zero
    ctx->r4 = ctx->r21 | 0;
    // 0x802C64FC: lui         $a1, 0x802C
    ctx->r5 = S32(0X802C << 16);
    // 0x802C6500: lui         $a2, 0x802C
    ctx->r6 = S32(0X802C << 16);
    // 0x802C6504: addiu       $a2, $a2, 0x6CB8
    ctx->r6 = ADD32(ctx->r6, 0X6CB8);
    // 0x802C6508: addiu       $a1, $a1, 0x6CB4
    ctx->r5 = ADD32(ctx->r5, 0X6CB4);
    // 0x802C650C: jal         0x800CA210
    // 0x802C6510: or          $a0, $s5, $zero
    ctx->r4 = ctx->r21 | 0;
    func_800CA210(rdram, ctx);
        goto after_26;
    // 0x802C6510: or          $a0, $s5, $zero
    ctx->r4 = ctx->r21 | 0;
    after_26:
    // 0x802C6514: b           L_802C652C
    // 0x802C6518: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
        goto L_802C652C;
    // 0x802C6518: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
L_802C651C:
    // 0x802C651C: lui         $a2, 0x802C
    ctx->r6 = S32(0X802C << 16);
    // 0x802C6520: jal         0x800CA210
    // 0x802C6524: addiu       $a2, $a2, 0x6CC0
    ctx->r6 = ADD32(ctx->r6, 0X6CC0);
    func_800CA210(rdram, ctx);
        goto after_27;
    // 0x802C6524: addiu       $a2, $a2, 0x6CC0
    ctx->r6 = ADD32(ctx->r6, 0X6CC0);
    after_27:
    // 0x802C6528: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
L_802C652C:
    // 0x802C652C: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C6530: or          $a2, $s5, $zero
    ctx->r6 = ctx->r21 | 0;
    // 0x802C6534: addiu       $a3, $s0, 0x3B
    ctx->r7 = ADD32(ctx->r16, 0X3B);
    // 0x802C6538: jal         0x801E9858
    // 0x802C653C: sw          $s4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r20;
    func_801E9858(rdram, ctx);
        goto after_28;
    // 0x802C653C: sw          $s4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r20;
    after_28:
    // 0x802C6540: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C6544: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C6548: addiu       $a2, $s2, 0x10
    ctx->r6 = ADD32(ctx->r18, 0X10);
    // 0x802C654C: addiu       $a3, $s0, 0xEF
    ctx->r7 = ADD32(ctx->r16, 0XEF);
    // 0x802C6550: jal         0x801E9858
    // 0x802C6554: sw          $s4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r20;
    func_801E9858(rdram, ctx);
        goto after_29;
    // 0x802C6554: sw          $s4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r20;
    after_29:
    // 0x802C6558: lw          $a2, 0x0($s2)
    ctx->r6 = MEM_W(ctx->r18, 0X0);
    // 0x802C655C: sw          $s4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r20;
    // 0x802C6560: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C6564: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C6568: jal         0x801E8B24
    // 0x802C656C: addiu       $a3, $s0, 0x12E
    ctx->r7 = ADD32(ctx->r16, 0X12E);
    func_801E8B24(rdram, ctx);
        goto after_30;
    // 0x802C656C: addiu       $a3, $s0, 0x12E
    ctx->r7 = ADD32(ctx->r16, 0X12E);
    after_30:
    // 0x802C6570: b           L_802C65B0
    // 0x802C6574: or          $s3, $v0, $zero
    ctx->r19 = ctx->r2 | 0;
        goto L_802C65B0;
    // 0x802C6574: or          $s3, $v0, $zero
    ctx->r19 = ctx->r2 | 0;
L_802C6578:
    // 0x802C6578: lui         $a2, 0x802C
    ctx->r6 = S32(0X802C << 16);
    // 0x802C657C: addiu       $a2, $a2, 0x6CC4
    ctx->r6 = ADD32(ctx->r6, 0X6CC4);
    // 0x802C6580: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C6584: addiu       $a3, $s0, 0xEF
    ctx->r7 = ADD32(ctx->r16, 0XEF);
    // 0x802C6588: jal         0x801E9858
    // 0x802C658C: sw          $s4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r20;
    func_801E9858(rdram, ctx);
        goto after_31;
    // 0x802C658C: sw          $s4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r20;
    after_31:
    // 0x802C6590: lui         $a2, 0x802C
    ctx->r6 = S32(0X802C << 16);
    // 0x802C6594: addiu       $a2, $a2, 0x6CC8
    ctx->r6 = ADD32(ctx->r6, 0X6CC8);
    // 0x802C6598: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C659C: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C65A0: addiu       $a3, $s0, 0x12E
    ctx->r7 = ADD32(ctx->r16, 0X12E);
    // 0x802C65A4: jal         0x801E9858
    // 0x802C65A8: sw          $s4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r20;
    func_801E9858(rdram, ctx);
        goto after_32;
    // 0x802C65A8: sw          $s4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r20;
    after_32:
    // 0x802C65AC: or          $s3, $v0, $zero
    ctx->r19 = ctx->r2 | 0;
L_802C65B0:
    // 0x802C65B0: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
    // 0x802C65B4: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C65B8: addiu       $a2, $zero, 0x24
    ctx->r6 = ADD32(0, 0X24);
    // 0x802C65BC: addiu       $a3, $s0, 0x4B
    ctx->r7 = ADD32(ctx->r16, 0X4B);
    // 0x802C65C0: sw          $s6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r22;
    // 0x802C65C4: jal         0x801E3EE0
    // 0x802C65C8: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    func_801E3EE0(rdram, ctx);
        goto after_33;
    // 0x802C65C8: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    after_33:
    // 0x802C65CC: b           L_802C668C
    // 0x802C65D0: or          $s3, $v0, $zero
    ctx->r19 = ctx->r2 | 0;
        goto L_802C668C;
    // 0x802C65D0: or          $s3, $v0, $zero
    ctx->r19 = ctx->r2 | 0;
    // 0x802C65D4: lw          $t0, 0x8($s2)
    ctx->r8 = MEM_W(ctx->r18, 0X8);
L_802C65D8:
    // 0x802C65D8: lui         $a1, 0x802C
    ctx->r5 = S32(0X802C << 16);
    // 0x802C65DC: addiu       $a1, $a1, 0x6CDC
    ctx->r5 = ADD32(ctx->r5, 0X6CDC);
    // 0x802C65E0: bne         $t0, $zero, L_802C6608
    if (ctx->r8 != 0) {
        // 0x802C65E4: or          $a0, $s5, $zero
        ctx->r4 = ctx->r21 | 0;
            goto L_802C6608;
    }
    // 0x802C65E4: or          $a0, $s5, $zero
    ctx->r4 = ctx->r21 | 0;
    // 0x802C65E8: lui         $a1, 0x802C
    ctx->r5 = S32(0X802C << 16);
    // 0x802C65EC: lui         $a2, 0x802C
    ctx->r6 = S32(0X802C << 16);
    // 0x802C65F0: addiu       $a2, $a2, 0x6CD8
    ctx->r6 = ADD32(ctx->r6, 0X6CD8);
    // 0x802C65F4: addiu       $a1, $a1, 0x6CD4
    ctx->r5 = ADD32(ctx->r5, 0X6CD4);
    // 0x802C65F8: jal         0x800CA210
    // 0x802C65FC: or          $a0, $s5, $zero
    ctx->r4 = ctx->r21 | 0;
    func_800CA210(rdram, ctx);
        goto after_34;
    // 0x802C65FC: or          $a0, $s5, $zero
    ctx->r4 = ctx->r21 | 0;
    after_34:
    // 0x802C6600: b           L_802C6618
    // 0x802C6604: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
        goto L_802C6618;
    // 0x802C6604: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
L_802C6608:
    // 0x802C6608: lui         $a2, 0x802C
    ctx->r6 = S32(0X802C << 16);
    // 0x802C660C: jal         0x800CA210
    // 0x802C6610: addiu       $a2, $a2, 0x6CE0
    ctx->r6 = ADD32(ctx->r6, 0X6CE0);
    func_800CA210(rdram, ctx);
        goto after_35;
    // 0x802C6610: addiu       $a2, $a2, 0x6CE0
    ctx->r6 = ADD32(ctx->r6, 0X6CE0);
    after_35:
    // 0x802C6614: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
L_802C6618:
    // 0x802C6618: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C661C: or          $a2, $s5, $zero
    ctx->r6 = ctx->r21 | 0;
    // 0x802C6620: addiu       $a3, $s0, 0x3B
    ctx->r7 = ADD32(ctx->r16, 0X3B);
    // 0x802C6624: jal         0x801E9858
    // 0x802C6628: sw          $s4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r20;
    func_801E9858(rdram, ctx);
        goto after_36;
    // 0x802C6628: sw          $s4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r20;
    after_36:
    // 0x802C662C: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C6630: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C6634: addiu       $a2, $s2, 0x10
    ctx->r6 = ADD32(ctx->r18, 0X10);
    // 0x802C6638: addiu       $a3, $s0, 0xEF
    ctx->r7 = ADD32(ctx->r16, 0XEF);
    // 0x802C663C: jal         0x801E9858
    // 0x802C6640: sw          $s4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r20;
    func_801E9858(rdram, ctx);
        goto after_37;
    // 0x802C6640: sw          $s4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r20;
    after_37:
    // 0x802C6644: lw          $a2, 0x0($s2)
    ctx->r6 = MEM_W(ctx->r18, 0X0);
    // 0x802C6648: sw          $s4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r20;
    // 0x802C664C: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C6650: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C6654: jal         0x801E8B24
    // 0x802C6658: addiu       $a3, $s0, 0x12E
    ctx->r7 = ADD32(ctx->r16, 0X12E);
    func_801E8B24(rdram, ctx);
        goto after_38;
    // 0x802C6658: addiu       $a3, $s0, 0x12E
    ctx->r7 = ADD32(ctx->r16, 0X12E);
    after_38:
    // 0x802C665C: lw          $t1, 0xC($s2)
    ctx->r9 = MEM_W(ctx->r18, 0XC);
    // 0x802C6660: lui         $a2, 0x802C
    ctx->r6 = S32(0X802C << 16);
    // 0x802C6664: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    // 0x802C6668: sll         $t2, $t1, 2
    ctx->r10 = S32(ctx->r9 << 2);
    // 0x802C666C: addu        $a2, $a2, $t2
    ctx->r6 = ADD32(ctx->r6, ctx->r10);
    // 0x802C6670: lw          $a2, 0x6C80($a2)
    ctx->r6 = MEM_W(ctx->r6, 0X6C80);
    // 0x802C6674: sw          $s6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r22;
    // 0x802C6678: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C667C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C6680: jal         0x801E3EE0
    // 0x802C6684: addiu       $a3, $s0, 0x4B
    ctx->r7 = ADD32(ctx->r16, 0X4B);
    func_801E3EE0(rdram, ctx);
        goto after_39;
    // 0x802C6684: addiu       $a3, $s0, 0x4B
    ctx->r7 = ADD32(ctx->r16, 0X4B);
    after_39:
    // 0x802C6688: or          $s3, $v0, $zero
    ctx->r19 = ctx->r2 | 0;
L_802C668C:
    // 0x802C668C: lw          $t3, 0x6C($sp)
    ctx->r11 = MEM_W(ctx->r29, 0X6C);
    // 0x802C6690: lw          $s1, 0x74($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X74);
    // 0x802C6694: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x802C6698: addiu       $t4, $t3, 0x1
    ctx->r12 = ADD32(ctx->r11, 0X1);
    // 0x802C669C: sw          $t4, 0x6C($sp)
    MEM_W(0X6C, ctx->r29) = ctx->r12;
    // 0x802C66A0: addiu       $s4, $s4, 0x12
    ctx->r20 = ADD32(ctx->r20, 0X12);
    // 0x802C66A4: bne         $s1, $at, L_802C6338
    if (ctx->r17 != ctx->r1) {
        // 0x802C66A8: addiu       $s6, $s6, 0x12
        ctx->r22 = ADD32(ctx->r22, 0X12);
            goto L_802C6338;
    }
    // 0x802C66A8: addiu       $s6, $s6, 0x12
    ctx->r22 = ADD32(ctx->r22, 0X12);
    // 0x802C66AC: lui         $t5, 0x801C
    ctx->r13 = S32(0X801C << 16);
    // 0x802C66B0: lw          $t5, 0x2650($t5)
    ctx->r13 = MEM_W(ctx->r13, 0X2650);
    // 0x802C66B4: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
    // 0x802C66B8: addiu       $a1, $zero, 0x6
    ctx->r5 = ADD32(0, 0X6);
    // 0x802C66BC: bne         $t5, $zero, L_802C684C
    if (ctx->r13 != 0) {
        // 0x802C66C0: addiu       $a2, $zero, 0xFF
        ctx->r6 = ADD32(0, 0XFF);
            goto L_802C684C;
    }
    // 0x802C66C0: addiu       $a2, $zero, 0xFF
    ctx->r6 = ADD32(0, 0XFF);
    // 0x802C66C4: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C66C8: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C66CC: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C66D0: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C66D4: addiu       $t0, $zero, 0xFF
    ctx->r8 = ADD32(0, 0XFF);
    // 0x802C66D8: addiu       $t1, $zero, 0xFF
    ctx->r9 = ADD32(0, 0XFF);
    // 0x802C66DC: addiu       $t2, $zero, 0xFF
    ctx->r10 = ADD32(0, 0XFF);
    // 0x802C66E0: addiu       $t3, $zero, 0xFF
    ctx->r11 = ADD32(0, 0XFF);
    // 0x802C66E4: addiu       $t4, $zero, 0xFF
    ctx->r12 = ADD32(0, 0XFF);
    // 0x802C66E8: addiu       $t5, $zero, 0xFF
    ctx->r13 = ADD32(0, 0XFF);
    // 0x802C66EC: sw          $t5, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r13;
    // 0x802C66F0: sw          $t4, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r12;
    // 0x802C66F4: sw          $t3, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r11;
    // 0x802C66F8: sw          $t2, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r10;
    // 0x802C66FC: sw          $t1, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r9;
    // 0x802C6700: sw          $t0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r8;
    // 0x802C6704: sw          $t9, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r25;
    // 0x802C6708: sw          $t8, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r24;
    // 0x802C670C: sw          $t7, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r15;
    // 0x802C6710: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x802C6714: jal         0x801E946C
    // 0x802C6718: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    func_801E946C(rdram, ctx);
        goto after_40;
    // 0x802C6718: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    after_40:
    // 0x802C671C: lui         $t6, 0x801D
    ctx->r14 = S32(0X801D << 16);
    // 0x802C6720: lw          $t6, -0x4CD4($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X4CD4);
    // 0x802C6724: or          $s3, $v0, $zero
    ctx->r19 = ctx->r2 | 0;
    // 0x802C6728: or          $a0, $s5, $zero
    ctx->r4 = ctx->r21 | 0;
    // 0x802C672C: bne         $t6, $zero, L_802C6754
    if (ctx->r14 != 0) {
        // 0x802C6730: lui         $a1, 0x802C
        ctx->r5 = S32(0X802C << 16);
            goto L_802C6754;
    }
    // 0x802C6730: lui         $a1, 0x802C
    ctx->r5 = S32(0X802C << 16);
    // 0x802C6734: lui         $a1, 0x802C
    ctx->r5 = S32(0X802C << 16);
    // 0x802C6738: lui         $a2, 0x802C
    ctx->r6 = S32(0X802C << 16);
    // 0x802C673C: addiu       $a2, $a2, 0x6CE8
    ctx->r6 = ADD32(ctx->r6, 0X6CE8);
    // 0x802C6740: addiu       $a1, $a1, 0x6CE4
    ctx->r5 = ADD32(ctx->r5, 0X6CE4);
    // 0x802C6744: jal         0x800CA210
    // 0x802C6748: or          $a0, $s5, $zero
    ctx->r4 = ctx->r21 | 0;
    func_800CA210(rdram, ctx);
        goto after_41;
    // 0x802C6748: or          $a0, $s5, $zero
    ctx->r4 = ctx->r21 | 0;
    after_41:
    // 0x802C674C: b           L_802C6764
    // 0x802C6750: nop

        goto L_802C6764;
    // 0x802C6750: nop

L_802C6754:
    // 0x802C6754: lui         $a2, 0x802C
    ctx->r6 = S32(0X802C << 16);
    // 0x802C6758: addiu       $a2, $a2, 0x6CF0
    ctx->r6 = ADD32(ctx->r6, 0X6CF0);
    // 0x802C675C: jal         0x800CA210
    // 0x802C6760: addiu       $a1, $a1, 0x6CEC
    ctx->r5 = ADD32(ctx->r5, 0X6CEC);
    func_800CA210(rdram, ctx);
        goto after_42;
    // 0x802C6760: addiu       $a1, $a1, 0x6CEC
    ctx->r5 = ADD32(ctx->r5, 0X6CEC);
    after_42:
L_802C6764:
    // 0x802C6764: lui         $a3, 0x802C
    ctx->r7 = S32(0X802C << 16);
    // 0x802C6768: lw          $a3, 0x6D38($a3)
    ctx->r7 = MEM_W(ctx->r7, 0X6D38);
    // 0x802C676C: addiu       $t7, $zero, 0xA0
    ctx->r15 = ADD32(0, 0XA0);
    // 0x802C6770: sw          $t7, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r15;
    // 0x802C6774: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
    // 0x802C6778: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C677C: or          $a2, $s5, $zero
    ctx->r6 = ctx->r21 | 0;
    // 0x802C6780: jal         0x801E9858
    // 0x802C6784: addiu       $a3, $a3, 0x3B
    ctx->r7 = ADD32(ctx->r7, 0X3B);
    func_801E9858(rdram, ctx);
        goto after_43;
    // 0x802C6784: addiu       $a3, $a3, 0x3B
    ctx->r7 = ADD32(ctx->r7, 0X3B);
    after_43:
    // 0x802C6788: lui         $t8, 0x800D
    ctx->r24 = S32(0X800D << 16);
    // 0x802C678C: lw          $t8, 0x48DC($t8)
    ctx->r24 = MEM_W(ctx->r24, 0X48DC);
    // 0x802C6790: lui         $a3, 0x802C
    ctx->r7 = S32(0X802C << 16);
    // 0x802C6794: lw          $a3, 0x6D38($a3)
    ctx->r7 = MEM_W(ctx->r7, 0X6D38);
    // 0x802C6798: sll         $t9, $t8, 3
    ctx->r25 = S32(ctx->r24 << 3);
    // 0x802C679C: subu        $t9, $t9, $t8
    ctx->r25 = SUB32(ctx->r25, ctx->r24);
    // 0x802C67A0: sll         $t9, $t9, 4
    ctx->r25 = S32(ctx->r25 << 4);
    // 0x802C67A4: subu        $t9, $t9, $t8
    ctx->r25 = SUB32(ctx->r25, ctx->r24);
    // 0x802C67A8: sll         $t9, $t9, 3
    ctx->r25 = S32(ctx->r25 << 3);
    // 0x802C67AC: lui         $a2, 0x801C
    ctx->r6 = S32(0X801C << 16);
    // 0x802C67B0: addu        $a2, $a2, $t9
    ctx->r6 = ADD32(ctx->r6, ctx->r25);
    // 0x802C67B4: addiu       $t0, $zero, 0xA0
    ctx->r8 = ADD32(0, 0XA0);
    // 0x802C67B8: sw          $t0, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r8;
    // 0x802C67BC: lw          $a2, 0x2AD4($a2)
    ctx->r6 = MEM_W(ctx->r6, 0X2AD4);
    // 0x802C67C0: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C67C4: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C67C8: jal         0x801E8B24
    // 0x802C67CC: addiu       $a3, $a3, 0x12E
    ctx->r7 = ADD32(ctx->r7, 0X12E);
    func_801E8B24(rdram, ctx);
        goto after_44;
    // 0x802C67CC: addiu       $a3, $a3, 0x12E
    ctx->r7 = ADD32(ctx->r7, 0X12E);
    after_44:
    // 0x802C67D0: lh          $t1, 0x0($s7)
    ctx->r9 = MEM_H(ctx->r23, 0X0);
    // 0x802C67D4: or          $s3, $v0, $zero
    ctx->r19 = ctx->r2 | 0;
    // 0x802C67D8: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
    // 0x802C67DC: beq         $t1, $zero, L_802C6814
    if (ctx->r9 == 0) {
        // 0x802C67E0: or          $a1, $zero, $zero
        ctx->r5 = 0 | 0;
            goto L_802C6814;
    }
    // 0x802C67E0: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C67E4: lui         $a3, 0x802C
    ctx->r7 = S32(0X802C << 16);
    // 0x802C67E8: lw          $a3, 0x6D38($a3)
    ctx->r7 = MEM_W(ctx->r7, 0X6D38);
    // 0x802C67EC: addiu       $t2, $zero, 0xA0
    ctx->r10 = ADD32(0, 0XA0);
    // 0x802C67F0: sw          $t2, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r10;
    // 0x802C67F4: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C67F8: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C67FC: addiu       $a2, $zero, 0x24
    ctx->r6 = ADD32(0, 0X24);
    // 0x802C6800: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    // 0x802C6804: jal         0x801E3EE0
    // 0x802C6808: addiu       $a3, $a3, 0x4B
    ctx->r7 = ADD32(ctx->r7, 0X4B);
    func_801E3EE0(rdram, ctx);
        goto after_45;
    // 0x802C6808: addiu       $a3, $a3, 0x4B
    ctx->r7 = ADD32(ctx->r7, 0X4B);
    after_45:
    // 0x802C680C: b           L_802C684C
    // 0x802C6810: or          $s3, $v0, $zero
    ctx->r19 = ctx->r2 | 0;
        goto L_802C684C;
    // 0x802C6810: or          $s3, $v0, $zero
    ctx->r19 = ctx->r2 | 0;
L_802C6814:
    // 0x802C6814: lui         $t3, 0x801D
    ctx->r11 = S32(0X801D << 16);
    // 0x802C6818: lw          $t3, -0x4CC8($t3)
    ctx->r11 = MEM_W(ctx->r11, -0X4CC8);
    // 0x802C681C: lui         $a3, 0x802C
    ctx->r7 = S32(0X802C << 16);
    // 0x802C6820: lw          $a3, 0x6D38($a3)
    ctx->r7 = MEM_W(ctx->r7, 0X6D38);
    // 0x802C6824: lui         $a2, 0x802C
    ctx->r6 = S32(0X802C << 16);
    // 0x802C6828: sll         $t4, $t3, 2
    ctx->r12 = S32(ctx->r11 << 2);
    // 0x802C682C: addu        $a2, $a2, $t4
    ctx->r6 = ADD32(ctx->r6, ctx->r12);
    // 0x802C6830: addiu       $t5, $zero, 0xA1
    ctx->r13 = ADD32(0, 0XA1);
    // 0x802C6834: sw          $t5, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r13;
    // 0x802C6838: lw          $a2, 0x6C80($a2)
    ctx->r6 = MEM_W(ctx->r6, 0X6C80);
    // 0x802C683C: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    // 0x802C6840: jal         0x801E3EE0
    // 0x802C6844: addiu       $a3, $a3, 0x4B
    ctx->r7 = ADD32(ctx->r7, 0X4B);
    func_801E3EE0(rdram, ctx);
        goto after_46;
    // 0x802C6844: addiu       $a3, $a3, 0x4B
    ctx->r7 = ADD32(ctx->r7, 0X4B);
    after_46:
    // 0x802C6848: or          $s3, $v0, $zero
    ctx->r19 = ctx->r2 | 0;
L_802C684C:
    // 0x802C684C: lh          $t6, 0x0($s7)
    ctx->r14 = MEM_H(ctx->r23, 0X0);
    // 0x802C6850: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
    // 0x802C6854: addiu       $a1, $zero, 0x7
    ctx->r5 = ADD32(0, 0X7);
    // 0x802C6858: beq         $t6, $zero, L_802C6930
    if (ctx->r14 == 0) {
        // 0x802C685C: lui         $t0, 0x801C
        ctx->r8 = S32(0X801C << 16);
            goto L_802C6930;
    }
    // 0x802C685C: lui         $t0, 0x801C
    ctx->r8 = S32(0X801C << 16);
    // 0x802C6860: addiu       $t7, $zero, 0x80
    ctx->r15 = ADD32(0, 0X80);
    // 0x802C6864: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C6868: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C686C: addiu       $t0, $zero, 0xFF
    ctx->r8 = ADD32(0, 0XFF);
    // 0x802C6870: addiu       $t1, $zero, 0xFF
    ctx->r9 = ADD32(0, 0XFF);
    // 0x802C6874: addiu       $t2, $zero, 0xFF
    ctx->r10 = ADD32(0, 0XFF);
    // 0x802C6878: addiu       $t3, $zero, 0xFF
    ctx->r11 = ADD32(0, 0XFF);
    // 0x802C687C: addiu       $t4, $zero, 0xFF
    ctx->r12 = ADD32(0, 0XFF);
    // 0x802C6880: addiu       $t5, $zero, 0xFF
    ctx->r13 = ADD32(0, 0XFF);
    // 0x802C6884: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C6888: sw          $t6, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r14;
    // 0x802C688C: sw          $t5, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r13;
    // 0x802C6890: sw          $t4, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r12;
    // 0x802C6894: sw          $t3, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r11;
    // 0x802C6898: sw          $t2, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r10;
    // 0x802C689C: sw          $t1, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r9;
    // 0x802C68A0: sw          $t0, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r8;
    // 0x802C68A4: sw          $t9, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r25;
    // 0x802C68A8: sw          $t8, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r24;
    // 0x802C68AC: sw          $t7, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r15;
    // 0x802C68B0: addiu       $a2, $zero, 0x80
    ctx->r6 = ADD32(0, 0X80);
    // 0x802C68B4: jal         0x801E946C
    // 0x802C68B8: addiu       $a3, $zero, 0x80
    ctx->r7 = ADD32(0, 0X80);
    func_801E946C(rdram, ctx);
        goto after_47;
    // 0x802C68B8: addiu       $a3, $zero, 0x80
    ctx->r7 = ADD32(0, 0X80);
    after_47:
    // 0x802C68BC: lw          $a3, 0xB4($sp)
    ctx->r7 = MEM_W(ctx->r29, 0XB4);
    // 0x802C68C0: lui         $a2, 0x802C
    ctx->r6 = S32(0X802C << 16);
    // 0x802C68C4: addiu       $t7, $zero, 0xC4
    ctx->r15 = ADD32(0, 0XC4);
    // 0x802C68C8: sw          $t7, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r15;
    // 0x802C68CC: addiu       $a2, $a2, 0x6CF4
    ctx->r6 = ADD32(ctx->r6, 0X6CF4);
    // 0x802C68D0: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C68D4: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C68D8: jal         0x801E9858
    // 0x802C68DC: addiu       $a3, $a3, 0xEF
    ctx->r7 = ADD32(ctx->r7, 0XEF);
    func_801E9858(rdram, ctx);
        goto after_48;
    // 0x802C68DC: addiu       $a3, $a3, 0xEF
    ctx->r7 = ADD32(ctx->r7, 0XEF);
    after_48:
    // 0x802C68E0: lw          $a3, 0xB4($sp)
    ctx->r7 = MEM_W(ctx->r29, 0XB4);
    // 0x802C68E4: lui         $a2, 0x802C
    ctx->r6 = S32(0X802C << 16);
    // 0x802C68E8: addiu       $t8, $zero, 0xC4
    ctx->r24 = ADD32(0, 0XC4);
    // 0x802C68EC: sw          $t8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r24;
    // 0x802C68F0: addiu       $a2, $a2, 0x6CF8
    ctx->r6 = ADD32(ctx->r6, 0X6CF8);
    // 0x802C68F4: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C68F8: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C68FC: jal         0x801E9858
    // 0x802C6900: addiu       $a3, $a3, 0x12E
    ctx->r7 = ADD32(ctx->r7, 0X12E);
    func_801E9858(rdram, ctx);
        goto after_49;
    // 0x802C6900: addiu       $a3, $a3, 0x12E
    ctx->r7 = ADD32(ctx->r7, 0X12E);
    after_49:
    // 0x802C6904: lw          $a3, 0xB4($sp)
    ctx->r7 = MEM_W(ctx->r29, 0XB4);
    // 0x802C6908: addiu       $t9, $zero, 0xC5
    ctx->r25 = ADD32(0, 0XC5);
    // 0x802C690C: sw          $t9, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r25;
    // 0x802C6910: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C6914: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C6918: addiu       $a2, $zero, 0x24
    ctx->r6 = ADD32(0, 0X24);
    // 0x802C691C: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    // 0x802C6920: jal         0x801E3EE0
    // 0x802C6924: addiu       $a3, $a3, 0x4B
    ctx->r7 = ADD32(ctx->r7, 0X4B);
    func_801E3EE0(rdram, ctx);
        goto after_50;
    // 0x802C6924: addiu       $a3, $a3, 0x4B
    ctx->r7 = ADD32(ctx->r7, 0X4B);
    after_50:
    // 0x802C6928: b           L_802C6B00
    // 0x802C692C: or          $s3, $v0, $zero
    ctx->r19 = ctx->r2 | 0;
        goto L_802C6B00;
    // 0x802C692C: or          $s3, $v0, $zero
    ctx->r19 = ctx->r2 | 0;
L_802C6930:
    // 0x802C6930: lw          $t0, 0x2654($t0)
    ctx->r8 = MEM_W(ctx->r8, 0X2654);
    // 0x802C6934: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
    // 0x802C6938: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C693C: beq         $t0, $zero, L_802C69B0
    if (ctx->r8 == 0) {
        // 0x802C6940: addiu       $a2, $zero, 0xFF
        ctx->r6 = ADD32(0, 0XFF);
            goto L_802C69B0;
    }
    // 0x802C6940: addiu       $a2, $zero, 0xFF
    ctx->r6 = ADD32(0, 0XFF);
    // 0x802C6944: addiu       $t1, $zero, 0xFF
    ctx->r9 = ADD32(0, 0XFF);
    // 0x802C6948: addiu       $t2, $zero, 0xFF
    ctx->r10 = ADD32(0, 0XFF);
    // 0x802C694C: addiu       $t3, $zero, 0xFF
    ctx->r11 = ADD32(0, 0XFF);
    // 0x802C6950: addiu       $t4, $zero, 0xFF
    ctx->r12 = ADD32(0, 0XFF);
    // 0x802C6954: addiu       $t5, $zero, 0xFF
    ctx->r13 = ADD32(0, 0XFF);
    // 0x802C6958: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C695C: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C6960: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C6964: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C6968: addiu       $t0, $zero, 0xFF
    ctx->r8 = ADD32(0, 0XFF);
    // 0x802C696C: sw          $t0, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r8;
    // 0x802C6970: sw          $t9, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r25;
    // 0x802C6974: sw          $t8, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r24;
    // 0x802C6978: sw          $t7, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r15;
    // 0x802C697C: sw          $t6, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r14;
    // 0x802C6980: sw          $t5, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r13;
    // 0x802C6984: sw          $t4, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r12;
    // 0x802C6988: sw          $t3, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r11;
    // 0x802C698C: sw          $t2, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r10;
    // 0x802C6990: sw          $t1, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r9;
    // 0x802C6994: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
    // 0x802C6998: addiu       $a1, $zero, 0x4
    ctx->r5 = ADD32(0, 0X4);
    // 0x802C699C: addiu       $a2, $zero, 0xFF
    ctx->r6 = ADD32(0, 0XFF);
    // 0x802C69A0: jal         0x801E946C
    // 0x802C69A4: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    func_801E946C(rdram, ctx);
        goto after_51;
    // 0x802C69A4: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    after_51:
    // 0x802C69A8: b           L_802C6A0C
    // 0x802C69AC: or          $s3, $v0, $zero
    ctx->r19 = ctx->r2 | 0;
        goto L_802C6A0C;
    // 0x802C69AC: or          $s3, $v0, $zero
    ctx->r19 = ctx->r2 | 0;
L_802C69B0:
    // 0x802C69B0: addiu       $t1, $zero, 0xFF
    ctx->r9 = ADD32(0, 0XFF);
    // 0x802C69B4: addiu       $t2, $zero, 0xFF
    ctx->r10 = ADD32(0, 0XFF);
    // 0x802C69B8: addiu       $t3, $zero, 0xFF
    ctx->r11 = ADD32(0, 0XFF);
    // 0x802C69BC: addiu       $t4, $zero, 0xFF
    ctx->r12 = ADD32(0, 0XFF);
    // 0x802C69C0: addiu       $t5, $zero, 0xFF
    ctx->r13 = ADD32(0, 0XFF);
    // 0x802C69C4: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C69C8: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C69CC: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C69D0: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C69D4: addiu       $t0, $zero, 0xFF
    ctx->r8 = ADD32(0, 0XFF);
    // 0x802C69D8: sw          $t0, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r8;
    // 0x802C69DC: sw          $t9, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r25;
    // 0x802C69E0: sw          $t8, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r24;
    // 0x802C69E4: sw          $t7, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r15;
    // 0x802C69E8: sw          $t6, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r14;
    // 0x802C69EC: sw          $t5, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r13;
    // 0x802C69F0: sw          $t4, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r12;
    // 0x802C69F4: sw          $t3, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r11;
    // 0x802C69F8: sw          $t2, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r10;
    // 0x802C69FC: sw          $t1, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r9;
    // 0x802C6A00: jal         0x801E946C
    // 0x802C6A04: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    func_801E946C(rdram, ctx);
        goto after_52;
    // 0x802C6A04: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    after_52:
    // 0x802C6A08: or          $s3, $v0, $zero
    ctx->r19 = ctx->r2 | 0;
L_802C6A0C:
    // 0x802C6A0C: lw          $t1, 0x0($fp)
    ctx->r9 = MEM_W(ctx->r30, 0X0);
    // 0x802C6A10: lui         $t3, 0x801C
    ctx->r11 = S32(0X801C << 16);
    // 0x802C6A14: addiu       $t3, $t3, 0x22C0
    ctx->r11 = ADD32(ctx->r11, 0X22C0);
    // 0x802C6A18: sll         $t2, $t1, 2
    ctx->r10 = S32(ctx->r9 << 2);
    // 0x802C6A1C: addu        $t2, $t2, $t1
    ctx->r10 = ADD32(ctx->r10, ctx->r9);
    // 0x802C6A20: sll         $t2, $t2, 2
    ctx->r10 = S32(ctx->r10 << 2);
    // 0x802C6A24: addu        $s2, $t2, $t3
    ctx->r18 = ADD32(ctx->r10, ctx->r11);
    // 0x802C6A28: lw          $t4, 0x8($s2)
    ctx->r12 = MEM_W(ctx->r18, 0X8);
    // 0x802C6A2C: lui         $a1, 0x802C
    ctx->r5 = S32(0X802C << 16);
    // 0x802C6A30: addiu       $a1, $a1, 0x6D0C
    ctx->r5 = ADD32(ctx->r5, 0X6D0C);
    // 0x802C6A34: bne         $t4, $zero, L_802C6A5C
    if (ctx->r12 != 0) {
        // 0x802C6A38: or          $a0, $s5, $zero
        ctx->r4 = ctx->r21 | 0;
            goto L_802C6A5C;
    }
    // 0x802C6A38: or          $a0, $s5, $zero
    ctx->r4 = ctx->r21 | 0;
    // 0x802C6A3C: lui         $a1, 0x802C
    ctx->r5 = S32(0X802C << 16);
    // 0x802C6A40: lui         $a2, 0x802C
    ctx->r6 = S32(0X802C << 16);
    // 0x802C6A44: addiu       $a2, $a2, 0x6D08
    ctx->r6 = ADD32(ctx->r6, 0X6D08);
    // 0x802C6A48: addiu       $a1, $a1, 0x6D04
    ctx->r5 = ADD32(ctx->r5, 0X6D04);
    // 0x802C6A4C: jal         0x800CA210
    // 0x802C6A50: or          $a0, $s5, $zero
    ctx->r4 = ctx->r21 | 0;
    func_800CA210(rdram, ctx);
        goto after_53;
    // 0x802C6A50: or          $a0, $s5, $zero
    ctx->r4 = ctx->r21 | 0;
    after_53:
    // 0x802C6A54: b           L_802C6A6C
    // 0x802C6A58: lw          $a3, 0xB4($sp)
    ctx->r7 = MEM_W(ctx->r29, 0XB4);
        goto L_802C6A6C;
    // 0x802C6A58: lw          $a3, 0xB4($sp)
    ctx->r7 = MEM_W(ctx->r29, 0XB4);
L_802C6A5C:
    // 0x802C6A5C: lui         $a2, 0x802C
    ctx->r6 = S32(0X802C << 16);
    // 0x802C6A60: jal         0x800CA210
    // 0x802C6A64: addiu       $a2, $a2, 0x6D10
    ctx->r6 = ADD32(ctx->r6, 0X6D10);
    func_800CA210(rdram, ctx);
        goto after_54;
    // 0x802C6A64: addiu       $a2, $a2, 0x6D10
    ctx->r6 = ADD32(ctx->r6, 0X6D10);
    after_54:
    // 0x802C6A68: lw          $a3, 0xB4($sp)
    ctx->r7 = MEM_W(ctx->r29, 0XB4);
L_802C6A6C:
    // 0x802C6A6C: addiu       $t5, $zero, 0xC4
    ctx->r13 = ADD32(0, 0XC4);
    // 0x802C6A70: sw          $t5, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r13;
    // 0x802C6A74: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
    // 0x802C6A78: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C6A7C: or          $a2, $s5, $zero
    ctx->r6 = ctx->r21 | 0;
    // 0x802C6A80: jal         0x801E9858
    // 0x802C6A84: addiu       $a3, $a3, 0x3B
    ctx->r7 = ADD32(ctx->r7, 0X3B);
    func_801E9858(rdram, ctx);
        goto after_55;
    // 0x802C6A84: addiu       $a3, $a3, 0x3B
    ctx->r7 = ADD32(ctx->r7, 0X3B);
    after_55:
    // 0x802C6A88: lw          $a3, 0xB4($sp)
    ctx->r7 = MEM_W(ctx->r29, 0XB4);
    // 0x802C6A8C: addiu       $t6, $zero, 0xC4
    ctx->r14 = ADD32(0, 0XC4);
    // 0x802C6A90: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x802C6A94: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C6A98: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C6A9C: addiu       $a2, $s2, 0x10
    ctx->r6 = ADD32(ctx->r18, 0X10);
    // 0x802C6AA0: jal         0x801E9858
    // 0x802C6AA4: addiu       $a3, $a3, 0xEF
    ctx->r7 = ADD32(ctx->r7, 0XEF);
    func_801E9858(rdram, ctx);
        goto after_56;
    // 0x802C6AA4: addiu       $a3, $a3, 0xEF
    ctx->r7 = ADD32(ctx->r7, 0XEF);
    after_56:
    // 0x802C6AA8: lw          $a3, 0xB4($sp)
    ctx->r7 = MEM_W(ctx->r29, 0XB4);
    // 0x802C6AAC: lw          $a2, 0x0($s2)
    ctx->r6 = MEM_W(ctx->r18, 0X0);
    // 0x802C6AB0: addiu       $t7, $zero, 0xC4
    ctx->r15 = ADD32(0, 0XC4);
    // 0x802C6AB4: sw          $t7, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r15;
    // 0x802C6AB8: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C6ABC: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C6AC0: jal         0x801E8B24
    // 0x802C6AC4: addiu       $a3, $a3, 0x12E
    ctx->r7 = ADD32(ctx->r7, 0X12E);
    func_801E8B24(rdram, ctx);
        goto after_57;
    // 0x802C6AC4: addiu       $a3, $a3, 0x12E
    ctx->r7 = ADD32(ctx->r7, 0X12E);
    after_57:
    // 0x802C6AC8: lw          $t8, 0xC($s2)
    ctx->r24 = MEM_W(ctx->r18, 0XC);
    // 0x802C6ACC: lw          $a3, 0xB4($sp)
    ctx->r7 = MEM_W(ctx->r29, 0XB4);
    // 0x802C6AD0: lui         $a2, 0x802C
    ctx->r6 = S32(0X802C << 16);
    // 0x802C6AD4: sll         $t9, $t8, 2
    ctx->r25 = S32(ctx->r24 << 2);
    // 0x802C6AD8: addu        $a2, $a2, $t9
    ctx->r6 = ADD32(ctx->r6, ctx->r25);
    // 0x802C6ADC: addiu       $t0, $zero, 0xC5
    ctx->r8 = ADD32(0, 0XC5);
    // 0x802C6AE0: sw          $t0, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r8;
    // 0x802C6AE4: lw          $a2, 0x6C80($a2)
    ctx->r6 = MEM_W(ctx->r6, 0X6C80);
    // 0x802C6AE8: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    // 0x802C6AEC: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C6AF0: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C6AF4: jal         0x801E3EE0
    // 0x802C6AF8: addiu       $a3, $a3, 0x4B
    ctx->r7 = ADD32(ctx->r7, 0X4B);
    func_801E3EE0(rdram, ctx);
        goto after_58;
    // 0x802C6AF8: addiu       $a3, $a3, 0x4B
    ctx->r7 = ADD32(ctx->r7, 0X4B);
    after_58:
    // 0x802C6AFC: or          $s3, $v0, $zero
    ctx->r19 = ctx->r2 | 0;
L_802C6B00:
    // 0x802C6B00: lw          $ra, 0x64($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X64);
    // 0x802C6B04: or          $v0, $s3, $zero
    ctx->r2 = ctx->r19 | 0;
    // 0x802C6B08: lw          $s3, 0x4C($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X4C);
    // 0x802C6B0C: lw          $s0, 0x40($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X40);
    // 0x802C6B10: lw          $s1, 0x44($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X44);
    // 0x802C6B14: lw          $s2, 0x48($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X48);
    // 0x802C6B18: lw          $s4, 0x50($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X50);
    // 0x802C6B1C: lw          $s5, 0x54($sp)
    ctx->r21 = MEM_W(ctx->r29, 0X54);
    // 0x802C6B20: lw          $s6, 0x58($sp)
    ctx->r22 = MEM_W(ctx->r29, 0X58);
    // 0x802C6B24: lw          $s7, 0x5C($sp)
    ctx->r23 = MEM_W(ctx->r29, 0X5C);
    // 0x802C6B28: lw          $fp, 0x60($sp)
    ctx->r30 = MEM_W(ctx->r29, 0X60);
    // 0x802C6B2C: jr          $ra
    // 0x802C6B30: addiu       $sp, $sp, 0xC0
    ctx->r29 = ADD32(ctx->r29, 0XC0);
    return;
    // 0x802C6B30: addiu       $sp, $sp, 0xC0
    ctx->r29 = ADD32(ctx->r29, 0XC0);
;}
RECOMP_FUNC void func_i6_802C6B34(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C6B34: lui         $a0, 0x802C
    ctx->r4 = S32(0X802C << 16);
    // 0x802C6B38: addiu       $a0, $a0, 0x6D30
    ctx->r4 = ADD32(ctx->r4, 0X6D30);
    // 0x802C6B3C: lw          $t6, 0x0($a0)
    ctx->r14 = MEM_W(ctx->r4, 0X0);
    // 0x802C6B40: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x802C6B44: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x802C6B48: sltiu       $at, $t6, 0x5
    ctx->r1 = ctx->r14 < 0X5 ? 1 : 0;
    // 0x802C6B4C: beq         $at, $zero, L_802C6C50
    if (ctx->r1 == 0) {
        // 0x802C6B50: or          $a2, $zero, $zero
        ctx->r6 = 0 | 0;
            goto L_802C6C50;
    }
    // 0x802C6B50: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x802C6B54: sll         $t6, $t6, 2
    ctx->r14 = S32(ctx->r14 << 2);
    // 0x802C6B58: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C6B5C: addu        $at, $at, $t6
    gpr jr_addend_802C6B64 = ctx->r14;
    ctx->r1 = ADD32(ctx->r1, ctx->r14);
    // 0x802C6B60: lw          $t6, 0x6D18($at)
    ctx->r14 = ADD32(ctx->r1, 0X6D18);
    // 0x802C6B64: jr          $t6
    // 0x802C6B68: nop

    switch (jr_addend_802C6B64 >> 2) {
        case 0: goto L_802C6B6C; break;
        case 1: goto L_802C6B78; break;
        case 2: goto L_802C6BB8; break;
        case 3: goto L_802C6BDC; break;
        case 4: goto L_802C6C28; break;
        default: switch_error(__func__, 0x802C6B64, 0x802C6D18);
    }
    // 0x802C6B68: nop

L_802C6B6C:
    // 0x802C6B6C: addiu       $t7, $zero, 0x1
    ctx->r15 = ADD32(0, 0X1);
    // 0x802C6B70: b           L_802C6C50
    // 0x802C6B74: sw          $t7, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r15;
        goto L_802C6C50;
    // 0x802C6B74: sw          $t7, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r15;
L_802C6B78:
    // 0x802C6B78: lui         $v0, 0x802C
    ctx->r2 = S32(0X802C << 16);
    // 0x802C6B7C: addiu       $v0, $v0, 0x6D34
    ctx->r2 = ADD32(ctx->r2, 0X6D34);
    // 0x802C6B80: lw          $t8, 0x0($v0)
    ctx->r24 = MEM_W(ctx->r2, 0X0);
    // 0x802C6B84: addiu       $t0, $zero, 0x2
    ctx->r8 = ADD32(0, 0X2);
    // 0x802C6B88: addiu       $t2, $zero, 0x28
    ctx->r10 = ADD32(0, 0X28);
    // 0x802C6B8C: addiu       $v1, $t8, -0x14
    ctx->r3 = ADD32(ctx->r24, -0X14);
    // 0x802C6B90: slti        $at, $v1, 0x14
    ctx->r1 = SIGNED(ctx->r3) < 0X14 ? 1 : 0;
    // 0x802C6B94: beq         $at, $zero, L_802C6BA8
    if (ctx->r1 == 0) {
        // 0x802C6B98: sw          $v1, 0x0($v0)
        MEM_W(0X0, ctx->r2) = ctx->r3;
            goto L_802C6BA8;
    }
    // 0x802C6B98: sw          $v1, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r3;
    // 0x802C6B9C: addiu       $v1, $zero, 0x14
    ctx->r3 = ADD32(0, 0X14);
    // 0x802C6BA0: sw          $t0, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r8;
    // 0x802C6BA4: sw          $v1, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r3;
L_802C6BA8:
    // 0x802C6BA8: subu        $t3, $t2, $v1
    ctx->r11 = SUB32(ctx->r10, ctx->r3);
    // 0x802C6BAC: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C6BB0: b           L_802C6C50
    // 0x802C6BB4: sw          $t3, 0x6D38($at)
    MEM_W(0X6D38, ctx->r1) = ctx->r11;
        goto L_802C6C50;
    // 0x802C6BB4: sw          $t3, 0x6D38($at)
    MEM_W(0X6D38, ctx->r1) = ctx->r11;
L_802C6BB8:
    // 0x802C6BB8: lui         $t4, 0x801D
    ctx->r12 = S32(0X801D << 16);
    // 0x802C6BBC: lhu         $t4, -0x196E($t4)
    ctx->r12 = MEM_HU(ctx->r12, -0X196E);
    // 0x802C6BC0: addiu       $t6, $zero, 0x3
    ctx->r14 = ADD32(0, 0X3);
    // 0x802C6BC4: andi        $t5, $t4, 0xB000
    ctx->r13 = ctx->r12 & 0XB000;
    // 0x802C6BC8: beq         $t5, $zero, L_802C6C50
    if (ctx->r13 == 0) {
        // 0x802C6BCC: nop
    
            goto L_802C6C50;
    }
    // 0x802C6BCC: nop

    // 0x802C6BD0: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    // 0x802C6BD4: b           L_802C6C50
    // 0x802C6BD8: sw          $t6, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r14;
        goto L_802C6C50;
    // 0x802C6BD8: sw          $t6, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r14;
L_802C6BDC:
    // 0x802C6BDC: lui         $v0, 0x802C
    ctx->r2 = S32(0X802C << 16);
    // 0x802C6BE0: addiu       $v0, $v0, 0x6D34
    ctx->r2 = ADD32(ctx->r2, 0X6D34);
    // 0x802C6BE4: lw          $t7, 0x0($v0)
    ctx->r15 = MEM_W(ctx->r2, 0X0);
    // 0x802C6BE8: lui         $a1, 0x802C
    ctx->r5 = S32(0X802C << 16);
    // 0x802C6BEC: addiu       $t1, $zero, 0x28
    ctx->r9 = ADD32(0, 0X28);
    // 0x802C6BF0: addiu       $v1, $t7, -0x14
    ctx->r3 = ADD32(ctx->r15, -0X14);
    // 0x802C6BF4: slti        $at, $v1, -0x170
    ctx->r1 = SIGNED(ctx->r3) < -0X170 ? 1 : 0;
    // 0x802C6BF8: beq         $at, $zero, L_802C6C18
    if (ctx->r1 == 0) {
        // 0x802C6BFC: sw          $v1, 0x0($v0)
        MEM_W(0X0, ctx->r2) = ctx->r3;
            goto L_802C6C18;
    }
    // 0x802C6BFC: sw          $v1, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r3;
    // 0x802C6C00: addiu       $a1, $a1, 0x6D3C
    ctx->r5 = ADD32(ctx->r5, 0X6D3C);
    // 0x802C6C04: addiu       $t9, $zero, 0x4
    ctx->r25 = ADD32(0, 0X4);
    // 0x802C6C08: addiu       $v1, $zero, -0x170
    ctx->r3 = ADD32(0, -0X170);
    // 0x802C6C0C: sw          $t9, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r25;
    // 0x802C6C10: sw          $v1, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r3;
    // 0x802C6C14: sw          $zero, 0x0($a1)
    MEM_W(0X0, ctx->r5) = 0;
L_802C6C18:
    // 0x802C6C18: subu        $t2, $t1, $v1
    ctx->r10 = SUB32(ctx->r9, ctx->r3);
    // 0x802C6C1C: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C6C20: b           L_802C6C50
    // 0x802C6C24: sw          $t2, 0x6D38($at)
    MEM_W(0X6D38, ctx->r1) = ctx->r10;
        goto L_802C6C50;
    // 0x802C6C24: sw          $t2, 0x6D38($at)
    MEM_W(0X6D38, ctx->r1) = ctx->r10;
L_802C6C28:
    // 0x802C6C28: lui         $a1, 0x802C
    ctx->r5 = S32(0X802C << 16);
    // 0x802C6C2C: addiu       $a1, $a1, 0x6D3C
    ctx->r5 = ADD32(ctx->r5, 0X6D3C);
    // 0x802C6C30: lw          $t3, 0x0($a1)
    ctx->r11 = MEM_W(ctx->r5, 0X0);
    // 0x802C6C34: addiu       $t4, $t3, 0x1
    ctx->r12 = ADD32(ctx->r11, 0X1);
    // 0x802C6C38: slti        $at, $t4, 0x3
    ctx->r1 = SIGNED(ctx->r12) < 0X3 ? 1 : 0;
    // 0x802C6C3C: bne         $at, $zero, L_802C6C50
    if (ctx->r1 != 0) {
        // 0x802C6C40: sw          $t4, 0x0($a1)
        MEM_W(0X0, ctx->r5) = ctx->r12;
            goto L_802C6C50;
    }
    // 0x802C6C40: sw          $t4, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r12;
    // 0x802C6C44: jal         0x801EC830
    // 0x802C6C48: sw          $a2, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r6;
    func_801EC830(rdram, ctx);
        goto after_0;
    // 0x802C6C48: sw          $a2, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r6;
    after_0:
    // 0x802C6C4C: lw          $a2, 0x1C($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X1C);
L_802C6C50:
    // 0x802C6C50: beq         $a2, $zero, L_802C6C60
    if (ctx->r6 == 0) {
        // 0x802C6C54: addiu       $a0, $zero, 0x31
        ctx->r4 = ADD32(0, 0X31);
            goto L_802C6C60;
    }
    // 0x802C6C54: addiu       $a0, $zero, 0x31
    ctx->r4 = ADD32(0, 0X31);
    // 0x802C6C58: jal         0x800C37F4
    // 0x802C6C5C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_1;
    // 0x802C6C5C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_1:
L_802C6C60:
    // 0x802C6C60: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x802C6C64: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x802C6C68: jr          $ra
    // 0x802C6C6C: nop

    return;
    // 0x802C6C6C: nop

;}
RECOMP_FUNC void func_1C3780_802C5800(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C5800: lui         $t6, 0x801D
    ctx->r14 = S32(0X801D << 16);
    // 0x802C5804: lw          $t6, -0x19C4($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X19C4);
    // 0x802C5808: addiu       $v0, $zero, 0x14
    ctx->r2 = ADD32(0, 0X14);
    // 0x802C580C: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C5810: beq         $t6, $zero, L_802C5834
    if (ctx->r14 == 0) {
        // 0x802C5814: addiu       $t7, $zero, 0x2
        ctx->r15 = ADD32(0, 0X2);
            goto L_802C5834;
    }
    // 0x802C5814: addiu       $t7, $zero, 0x2
    ctx->r15 = ADD32(0, 0X2);
    // 0x802C5818: sw          $zero, 0x5D84($at)
    MEM_W(0X5D84, ctx->r1) = 0;
    // 0x802C581C: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C5820: sw          $t7, 0x5D80($at)
    MEM_W(0X5D80, ctx->r1) = ctx->r15;
    // 0x802C5824: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C5828: sw          $v0, 0x5D88($at)
    MEM_W(0X5D88, ctx->r1) = ctx->r2;
    // 0x802C582C: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C5830: sw          $v0, 0x5D8C($at)
    MEM_W(0X5D8C, ctx->r1) = ctx->r2;
L_802C5834:
    // 0x802C5834: jr          $ra
    // 0x802C5838: nop

    return;
    // 0x802C5838: nop

;}
RECOMP_FUNC void func_1C3780_802C583C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C583C: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x802C5840: addiu       $v0, $v0, -0x19C4
    ctx->r2 = ADD32(ctx->r2, -0X19C4);
    // 0x802C5844: lw          $t6, 0x0($v0)
    ctx->r14 = MEM_W(ctx->r2, 0X0);
    // 0x802C5848: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x802C584C: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x802C5850: beq         $t6, $zero, L_802C588C
    if (ctx->r14 == 0) {
        // 0x802C5854: or          $a1, $a0, $zero
        ctx->r5 = ctx->r4 | 0;
            goto L_802C588C;
    }
    // 0x802C5854: or          $a1, $a0, $zero
    ctx->r5 = ctx->r4 | 0;
    // 0x802C5858: sw          $zero, 0x0($v0)
    MEM_W(0X0, ctx->r2) = 0;
    // 0x802C585C: lui         $t7, 0x800E
    ctx->r15 = S32(0X800E << 16);
    // 0x802C5860: lw          $t7, -0x54DC($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X54DC);
    // 0x802C5864: addiu       $at, $zero, 0x38
    ctx->r1 = ADD32(0, 0X38);
    // 0x802C5868: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    // 0x802C586C: bne         $t7, $at, L_802C588C
    if (ctx->r15 != ctx->r1) {
        // 0x802C5870: nop
    
            goto L_802C588C;
    }
    // 0x802C5870: nop

    // 0x802C5874: jal         0x800C6AD0
    // 0x802C5878: sw          $a1, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r5;
    osViBlack_recomp(rdram, ctx);
        goto after_0;
    // 0x802C5878: sw          $a1, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r5;
    after_0:
    // 0x802C587C: jal         0x80093C44
    // 0x802C5880: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
    func_80093C44(rdram, ctx);
        goto after_1;
    // 0x802C5880: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
    after_1:
    // 0x802C5884: b           L_802C58E8
    // 0x802C5888: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_802C58E8;
    // 0x802C5888: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C588C:
    // 0x802C588C: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x802C5890: sw          $zero, -0x54D4($at)
    MEM_W(-0X54D4, ctx->r1) = 0;
    // 0x802C5894: jal         0x8008FB74
    // 0x802C5898: or          $a0, $a1, $zero
    ctx->r4 = ctx->r5 | 0;
    func_8008FB74(rdram, ctx);
        goto after_2;
    // 0x802C5898: or          $a0, $a1, $zero
    ctx->r4 = ctx->r5 | 0;
    after_2:
    // 0x802C589C: lui         $a1, 0x800E
    ctx->r5 = S32(0X800E << 16);
    // 0x802C58A0: lw          $a1, -0x7E90($a1)
    ctx->r5 = MEM_W(ctx->r5, -0X7E90);
    // 0x802C58A4: jal         0x800949B8
    // 0x802C58A8: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    func_800949B8(rdram, ctx);
        goto after_3;
    // 0x802C58A8: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    after_3:
    // 0x802C58AC: jal         0x80090F58
    // 0x802C58B0: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    Draw_WaterEffects(rdram, ctx);
        goto after_4;
    // 0x802C58B0: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    after_4:
    // 0x802C58B4: jal         0x802C58F4
    // 0x802C58B8: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    func_1C3780_802C58F4(rdram, ctx);
        goto after_5;
    // 0x802C58B8: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    after_5:
    // 0x802C58BC: lui         $t8, 0x800E
    ctx->r24 = S32(0X800E << 16);
    // 0x802C58C0: lw          $t8, -0x54DC($t8)
    ctx->r24 = MEM_W(ctx->r24, -0X54DC);
    // 0x802C58C4: addiu       $at, $zero, 0x38
    ctx->r1 = ADD32(0, 0X38);
    // 0x802C58C8: or          $a1, $v0, $zero
    ctx->r5 = ctx->r2 | 0;
    // 0x802C58CC: bnel        $t8, $at, L_802C58E4
    if (ctx->r24 != ctx->r1) {
        // 0x802C58D0: or          $v0, $a1, $zero
        ctx->r2 = ctx->r5 | 0;
            goto L_802C58E4;
    }
    goto skip_0;
    // 0x802C58D0: or          $v0, $a1, $zero
    ctx->r2 = ctx->r5 | 0;
    skip_0:
    // 0x802C58D4: jal         0x802C5BD8
    // 0x802C58D8: sw          $v0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r2;
    func_1C3780_802C5BD8(rdram, ctx);
        goto after_6;
    // 0x802C58D8: sw          $v0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r2;
    after_6:
    // 0x802C58DC: lw          $a1, 0x18($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X18);
    // 0x802C58E0: or          $v0, $a1, $zero
    ctx->r2 = ctx->r5 | 0;
L_802C58E4:
    // 0x802C58E4: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C58E8:
    // 0x802C58E8: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x802C58EC: jr          $ra
    // 0x802C58F0: nop

    return;
    // 0x802C58F0: nop

;}
RECOMP_FUNC void func_1C3780_802C58F4(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C58F4: addiu       $sp, $sp, -0x48
    ctx->r29 = ADD32(ctx->r29, -0X48);
    // 0x802C58F8: sw          $s1, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r17;
    // 0x802C58FC: sw          $ra, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r31;
    // 0x802C5900: sw          $s0, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r16;
    // 0x802C5904: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x802C5908: lui         $t7, 0x107
    ctx->r15 = S32(0X107 << 16);
    // 0x802C590C: lui         $s1, 0x802C
    ctx->r17 = S32(0X802C << 16);
    // 0x802C5910: addiu       $t7, $t7, -0x9D8
    ctx->r15 = ADD32(ctx->r15, -0X9D8);
    // 0x802C5914: lui         $t6, 0x600
    ctx->r14 = S32(0X600 << 16);
    // 0x802C5918: addiu       $s1, $s1, 0x5D88
    ctx->r17 = ADD32(ctx->r17, 0X5D88);
    // 0x802C591C: sw          $t6, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r14;
    // 0x802C5920: sw          $t7, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r15;
    // 0x802C5924: lw          $a2, 0x0($s1)
    ctx->r6 = MEM_W(ctx->r17, 0X0);
    // 0x802C5928: addiu       $t8, $zero, 0x170
    ctx->r24 = ADD32(0, 0X170);
    // 0x802C592C: addiu       $t9, $zero, 0x18
    ctx->r25 = ADD32(0, 0X18);
    // 0x802C5930: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C5934: sw          $t9, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r25;
    // 0x802C5938: sw          $t8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r24;
    // 0x802C593C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C5940: addiu       $a3, $zero, 0x1E
    ctx->r7 = ADD32(0, 0X1E);
    // 0x802C5944: jal         0x80094338
    // 0x802C5948: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    func_80094338(rdram, ctx);
        goto after_0;
    // 0x802C5948: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    after_0:
    // 0x802C594C: lui         $s0, 0x802C
    ctx->r16 = S32(0X802C << 16);
    // 0x802C5950: addiu       $s0, $s0, 0x5D8C
    ctx->r16 = ADD32(ctx->r16, 0X5D8C);
    // 0x802C5954: lw          $a2, 0x0($s0)
    ctx->r6 = MEM_W(ctx->r16, 0X0);
    // 0x802C5958: addiu       $t0, $zero, 0x170
    ctx->r8 = ADD32(0, 0X170);
    // 0x802C595C: addiu       $t1, $zero, 0x10
    ctx->r9 = ADD32(0, 0X10);
    // 0x802C5960: sw          $t1, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r9;
    // 0x802C5964: sw          $t0, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r8;
    // 0x802C5968: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C596C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C5970: addiu       $a3, $zero, 0x50
    ctx->r7 = ADD32(0, 0X50);
    // 0x802C5974: jal         0x80094338
    // 0x802C5978: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    func_80094338(rdram, ctx);
        goto after_1;
    // 0x802C5978: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    after_1:
    // 0x802C597C: lw          $a2, 0x0($s0)
    ctx->r6 = MEM_W(ctx->r16, 0X0);
    // 0x802C5980: addiu       $t2, $zero, 0x170
    ctx->r10 = ADD32(0, 0X170);
    // 0x802C5984: addiu       $t3, $zero, 0x18
    ctx->r11 = ADD32(0, 0X18);
    // 0x802C5988: sw          $t3, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r11;
    // 0x802C598C: sw          $t2, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r10;
    // 0x802C5990: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C5994: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C5998: addiu       $a3, $zero, 0x62
    ctx->r7 = ADD32(0, 0X62);
    // 0x802C599C: jal         0x80094338
    // 0x802C59A0: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    func_80094338(rdram, ctx);
        goto after_2;
    // 0x802C59A0: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    after_2:
    // 0x802C59A4: lw          $a2, 0x0($s1)
    ctx->r6 = MEM_W(ctx->r17, 0X0);
    // 0x802C59A8: addiu       $t4, $zero, 0x170
    ctx->r12 = ADD32(0, 0X170);
    // 0x802C59AC: addiu       $t5, $zero, 0x18
    ctx->r13 = ADD32(0, 0X18);
    // 0x802C59B0: sw          $t5, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r13;
    // 0x802C59B4: sw          $t4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r12;
    // 0x802C59B8: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C59BC: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C59C0: addiu       $a3, $zero, 0x8C
    ctx->r7 = ADD32(0, 0X8C);
    // 0x802C59C4: jal         0x80094338
    // 0x802C59C8: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    func_80094338(rdram, ctx);
        goto after_3;
    // 0x802C59C8: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    after_3:
    // 0x802C59CC: lw          $a2, 0x0($s1)
    ctx->r6 = MEM_W(ctx->r17, 0X0);
    // 0x802C59D0: addiu       $t6, $zero, 0x170
    ctx->r14 = ADD32(0, 0X170);
    // 0x802C59D4: addiu       $t7, $zero, 0x18
    ctx->r15 = ADD32(0, 0X18);
    // 0x802C59D8: sw          $t7, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r15;
    // 0x802C59DC: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x802C59E0: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C59E4: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C59E8: addiu       $a3, $zero, 0xA5
    ctx->r7 = ADD32(0, 0XA5);
    // 0x802C59EC: jal         0x80094338
    // 0x802C59F0: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    func_80094338(rdram, ctx);
        goto after_4;
    // 0x802C59F0: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    after_4:
    // 0x802C59F4: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C59F8: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C59FC: addiu       $t0, $zero, 0xFF
    ctx->r8 = ADD32(0, 0XFF);
    // 0x802C5A00: addiu       $t1, $zero, 0xFF
    ctx->r9 = ADD32(0, 0XFF);
    // 0x802C5A04: addiu       $t2, $zero, 0xFF
    ctx->r10 = ADD32(0, 0XFF);
    // 0x802C5A08: addiu       $t3, $zero, 0xFF
    ctx->r11 = ADD32(0, 0XFF);
    // 0x802C5A0C: addiu       $t4, $zero, 0xFF
    ctx->r12 = ADD32(0, 0XFF);
    // 0x802C5A10: addiu       $t5, $zero, 0xFF
    ctx->r13 = ADD32(0, 0XFF);
    // 0x802C5A14: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C5A18: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C5A1C: sw          $t7, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r15;
    // 0x802C5A20: sw          $t6, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r14;
    // 0x802C5A24: sw          $t5, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r13;
    // 0x802C5A28: sw          $t4, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r12;
    // 0x802C5A2C: sw          $t3, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r11;
    // 0x802C5A30: sw          $t2, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r10;
    // 0x802C5A34: sw          $t1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r9;
    // 0x802C5A38: sw          $t0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r8;
    // 0x802C5A3C: sw          $t9, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r25;
    // 0x802C5A40: sw          $t8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r24;
    // 0x802C5A44: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C5A48: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C5A4C: addiu       $a2, $zero, 0xFF
    ctx->r6 = ADD32(0, 0XFF);
    // 0x802C5A50: jal         0x801E946C
    // 0x802C5A54: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    func_801E946C(rdram, ctx);
        goto after_5;
    // 0x802C5A54: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    after_5:
    // 0x802C5A58: lui         $v1, 0x800E
    ctx->r3 = S32(0X800E << 16);
    // 0x802C5A5C: lw          $v1, -0x7E90($v1)
    ctx->r3 = MEM_W(ctx->r3, -0X7E90);
    // 0x802C5A60: lui         $t9, 0x802C
    ctx->r25 = S32(0X802C << 16);
    // 0x802C5A64: lw          $t0, 0x0($s1)
    ctx->r8 = MEM_W(ctx->r17, 0X0);
    // 0x802C5A68: sll         $t8, $v1, 2
    ctx->r24 = S32(ctx->r3 << 2);
    // 0x802C5A6C: addu        $t9, $t9, $t8
    ctx->r25 = ADD32(ctx->r25, ctx->r24);
    // 0x802C5A70: lw          $t9, 0x5D30($t9)
    ctx->r25 = MEM_W(ctx->r25, 0X5D30);
    // 0x802C5A74: lui         $a2, 0x800E
    ctx->r6 = S32(0X800E << 16);
    // 0x802C5A78: addu        $a2, $a2, $t8
    ctx->r6 = ADD32(ctx->r6, ctx->r24);
    // 0x802C5A7C: addiu       $t1, $zero, 0x21
    ctx->r9 = ADD32(0, 0X21);
    // 0x802C5A80: addu        $a3, $t9, $t0
    ctx->r7 = ADD32(ctx->r25, ctx->r8);
    // 0x802C5A84: addiu       $a3, $a3, 0x6C
    ctx->r7 = ADD32(ctx->r7, 0X6C);
    // 0x802C5A88: sw          $t1, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r9;
    // 0x802C5A8C: lw          $a2, -0x55CC($a2)
    ctx->r6 = MEM_W(ctx->r6, -0X55CC);
    // 0x802C5A90: or          $v1, $t8, $zero
    ctx->r3 = ctx->r24 | 0;
    // 0x802C5A94: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C5A98: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C5A9C: jal         0x801E3EE0
    // 0x802C5AA0: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    func_801E3EE0(rdram, ctx);
        goto after_6;
    // 0x802C5AA0: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    after_6:
    // 0x802C5AA4: lw          $a3, 0x0($s1)
    ctx->r7 = MEM_W(ctx->r17, 0X0);
    // 0x802C5AA8: addiu       $t2, $zero, 0x90
    ctx->r10 = ADD32(0, 0X90);
    // 0x802C5AAC: sw          $t2, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r10;
    // 0x802C5AB0: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C5AB4: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C5AB8: addiu       $a2, $zero, 0x1C
    ctx->r6 = ADD32(0, 0X1C);
    // 0x802C5ABC: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    // 0x802C5AC0: jal         0x801E3EE0
    // 0x802C5AC4: addiu       $a3, $a3, 0x98
    ctx->r7 = ADD32(ctx->r7, 0X98);
    func_801E3EE0(rdram, ctx);
        goto after_7;
    // 0x802C5AC4: addiu       $a3, $a3, 0x98
    ctx->r7 = ADD32(ctx->r7, 0X98);
    after_7:
    // 0x802C5AC8: lw          $a3, 0x0($s0)
    ctx->r7 = MEM_W(ctx->r16, 0X0);
    // 0x802C5ACC: addiu       $t3, $zero, 0x53
    ctx->r11 = ADD32(0, 0X53);
    // 0x802C5AD0: sw          $t3, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r11;
    // 0x802C5AD4: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C5AD8: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C5ADC: addiu       $a2, $zero, 0x3
    ctx->r6 = ADD32(0, 0X3);
    // 0x802C5AE0: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    // 0x802C5AE4: jal         0x801E3EE0
    // 0x802C5AE8: addiu       $a3, $a3, 0x1C
    ctx->r7 = ADD32(ctx->r7, 0X1C);
    func_801E3EE0(rdram, ctx);
        goto after_8;
    // 0x802C5AE8: addiu       $a3, $a3, 0x1C
    ctx->r7 = ADD32(ctx->r7, 0X1C);
    after_8:
    // 0x802C5AEC: lw          $a3, 0x0($s0)
    ctx->r7 = MEM_W(ctx->r16, 0X0);
    // 0x802C5AF0: addiu       $t4, $zero, 0x53
    ctx->r12 = ADD32(0, 0X53);
    // 0x802C5AF4: sw          $t4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r12;
    // 0x802C5AF8: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C5AFC: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C5B00: addiu       $a2, $zero, 0x3D
    ctx->r6 = ADD32(0, 0X3D);
    // 0x802C5B04: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    // 0x802C5B08: jal         0x801E3EE0
    // 0x802C5B0C: addiu       $a3, $a3, 0xA5
    ctx->r7 = ADD32(ctx->r7, 0XA5);
    func_801E3EE0(rdram, ctx);
        goto after_9;
    // 0x802C5B0C: addiu       $a3, $a3, 0xA5
    ctx->r7 = ADD32(ctx->r7, 0XA5);
    after_9:
    // 0x802C5B10: lw          $a3, 0x0($s0)
    ctx->r7 = MEM_W(ctx->r16, 0X0);
    // 0x802C5B14: addiu       $t5, $zero, 0x53
    ctx->r13 = ADD32(0, 0X53);
    // 0x802C5B18: sw          $t5, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r13;
    // 0x802C5B1C: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C5B20: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C5B24: addiu       $a2, $zero, 0x3C
    ctx->r6 = ADD32(0, 0X3C);
    // 0x802C5B28: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    // 0x802C5B2C: jal         0x801E3EE0
    // 0x802C5B30: addiu       $a3, $a3, 0x141
    ctx->r7 = ADD32(ctx->r7, 0X141);
    func_801E3EE0(rdram, ctx);
        goto after_10;
    // 0x802C5B30: addiu       $a3, $a3, 0x141
    ctx->r7 = ADD32(ctx->r7, 0X141);
    after_10:
    // 0x802C5B34: lw          $a3, 0x0($s0)
    ctx->r7 = MEM_W(ctx->r16, 0X0);
    // 0x802C5B38: lui         $a2, 0x801C
    ctx->r6 = S32(0X801C << 16);
    // 0x802C5B3C: addiu       $t6, $zero, 0x69
    ctx->r14 = ADD32(0, 0X69);
    // 0x802C5B40: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x802C5B44: lw          $a2, 0x26D4($a2)
    ctx->r6 = MEM_W(ctx->r6, 0X26D4);
    // 0x802C5B48: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C5B4C: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C5B50: jal         0x80094200
    // 0x802C5B54: addiu       $a3, $a3, 0x10
    ctx->r7 = ADD32(ctx->r7, 0X10);
    func_80094200(rdram, ctx);
        goto after_11;
    // 0x802C5B54: addiu       $a3, $a3, 0x10
    ctx->r7 = ADD32(ctx->r7, 0X10);
    after_11:
    // 0x802C5B58: lw          $a3, 0x0($s0)
    ctx->r7 = MEM_W(ctx->r16, 0X0);
    // 0x802C5B5C: lui         $a2, 0x801C
    ctx->r6 = S32(0X801C << 16);
    // 0x802C5B60: addiu       $t7, $zero, 0x69
    ctx->r15 = ADD32(0, 0X69);
    // 0x802C5B64: sw          $t7, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r15;
    // 0x802C5B68: lw          $a2, 0x26DC($a2)
    ctx->r6 = MEM_W(ctx->r6, 0X26DC);
    // 0x802C5B6C: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C5B70: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C5B74: jal         0x80094200
    // 0x802C5B78: addiu       $a3, $a3, 0xA5
    ctx->r7 = ADD32(ctx->r7, 0XA5);
    func_80094200(rdram, ctx);
        goto after_12;
    // 0x802C5B78: addiu       $a3, $a3, 0xA5
    ctx->r7 = ADD32(ctx->r7, 0XA5);
    after_12:
    // 0x802C5B7C: lw          $a3, 0x0($s0)
    ctx->r7 = MEM_W(ctx->r16, 0X0);
    // 0x802C5B80: lui         $a2, 0x801C
    ctx->r6 = S32(0X801C << 16);
    // 0x802C5B84: addiu       $t8, $zero, 0x69
    ctx->r24 = ADD32(0, 0X69);
    // 0x802C5B88: sw          $t8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r24;
    // 0x802C5B8C: lw          $a2, 0x26D8($a2)
    ctx->r6 = MEM_W(ctx->r6, 0X26D8);
    // 0x802C5B90: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C5B94: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C5B98: jal         0x80094200
    // 0x802C5B9C: addiu       $a3, $a3, 0x135
    ctx->r7 = ADD32(ctx->r7, 0X135);
    func_80094200(rdram, ctx);
        goto after_13;
    // 0x802C5B9C: addiu       $a3, $a3, 0x135
    ctx->r7 = ADD32(ctx->r7, 0X135);
    after_13:
    // 0x802C5BA0: lw          $a3, 0x0($s1)
    ctx->r7 = MEM_W(ctx->r17, 0X0);
    // 0x802C5BA4: lui         $a2, 0x801C
    ctx->r6 = S32(0X801C << 16);
    // 0x802C5BA8: addiu       $t9, $zero, 0xA7
    ctx->r25 = ADD32(0, 0XA7);
    // 0x802C5BAC: sw          $t9, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r25;
    // 0x802C5BB0: lw          $a2, 0x26D0($a2)
    ctx->r6 = MEM_W(ctx->r6, 0X26D0);
    // 0x802C5BB4: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C5BB8: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C5BBC: jal         0x80094200
    // 0x802C5BC0: addiu       $a3, $a3, 0x90
    ctx->r7 = ADD32(ctx->r7, 0X90);
    func_80094200(rdram, ctx);
        goto after_14;
    // 0x802C5BC0: addiu       $a3, $a3, 0x90
    ctx->r7 = ADD32(ctx->r7, 0X90);
    after_14:
    // 0x802C5BC4: lw          $ra, 0x44($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X44);
    // 0x802C5BC8: lw          $s0, 0x3C($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X3C);
    // 0x802C5BCC: lw          $s1, 0x40($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X40);
    // 0x802C5BD0: jr          $ra
    // 0x802C5BD4: addiu       $sp, $sp, 0x48
    ctx->r29 = ADD32(ctx->r29, 0X48);
    return;
    // 0x802C5BD4: addiu       $sp, $sp, 0x48
    ctx->r29 = ADD32(ctx->r29, 0X48);
;}
RECOMP_FUNC void func_1C3780_802C5BD8(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C5BD8: lui         $v1, 0x802C
    ctx->r3 = S32(0X802C << 16);
    // 0x802C5BDC: addiu       $v1, $v1, 0x5D80
    ctx->r3 = ADD32(ctx->r3, 0X5D80);
    // 0x802C5BE0: lw          $t6, 0x0($v1)
    ctx->r14 = MEM_W(ctx->r3, 0X0);
    // 0x802C5BE4: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x802C5BE8: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x802C5BEC: sltiu       $at, $t6, 0x8
    ctx->r1 = ctx->r14 < 0X8 ? 1 : 0;
    // 0x802C5BF0: beq         $at, $zero, L_802C5CF0
    if (ctx->r1 == 0) {
        // 0x802C5BF4: or          $a1, $zero, $zero
        ctx->r5 = 0 | 0;
            goto L_802C5CF0;
    }
    // 0x802C5BF4: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C5BF8: sll         $t6, $t6, 2
    ctx->r14 = S32(ctx->r14 << 2);
    // 0x802C5BFC: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C5C00: addu        $at, $at, $t6
    gpr jr_addend_802C5C08 = ctx->r14;
    ctx->r1 = ADD32(ctx->r1, ctx->r14);
    // 0x802C5C04: lw          $t6, 0x5D60($at)
    ctx->r14 = ADD32(ctx->r1, 0X5D60);
    // 0x802C5C08: jr          $t6
    // 0x802C5C0C: nop

    switch (jr_addend_802C5C08 >> 2) {
        case 0: goto L_802C5C10; break;
        case 1: goto L_802C5C1C; break;
        case 2: goto L_802C5C4C; break;
        case 3: goto L_802C5C6C; break;
        case 4: goto L_802C5CF0; break;
        case 5: goto L_802C5CF0; break;
        case 6: goto L_802C5CF0; break;
        case 7: goto L_802C5CA8; break;
        default: switch_error(__func__, 0x802C5C08, 0x802C5D60);
    }
    // 0x802C5C0C: nop

L_802C5C10:
    // 0x802C5C10: addiu       $t7, $zero, 0x1
    ctx->r15 = ADD32(0, 0X1);
    // 0x802C5C14: b           L_802C5CF0
    // 0x802C5C18: sw          $t7, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r15;
        goto L_802C5CF0;
    // 0x802C5C18: sw          $t7, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r15;
L_802C5C1C:
    // 0x802C5C1C: lui         $v0, 0x802C
    ctx->r2 = S32(0X802C << 16);
    // 0x802C5C20: addiu       $v0, $v0, 0x5D88
    ctx->r2 = ADD32(ctx->r2, 0X5D88);
    // 0x802C5C24: lw          $t8, 0x0($v0)
    ctx->r24 = MEM_W(ctx->r2, 0X0);
    // 0x802C5C28: addiu       $t1, $zero, 0x2
    ctx->r9 = ADD32(0, 0X2);
    // 0x802C5C2C: addiu       $t2, $zero, 0x14
    ctx->r10 = ADD32(0, 0X14);
    // 0x802C5C30: addiu       $t9, $t8, 0x14
    ctx->r25 = ADD32(ctx->r24, 0X14);
    // 0x802C5C34: slti        $at, $t9, 0x14
    ctx->r1 = SIGNED(ctx->r25) < 0X14 ? 1 : 0;
    // 0x802C5C38: bne         $at, $zero, L_802C5CF0
    if (ctx->r1 != 0) {
        // 0x802C5C3C: sw          $t9, 0x0($v0)
        MEM_W(0X0, ctx->r2) = ctx->r25;
            goto L_802C5CF0;
    }
    // 0x802C5C3C: sw          $t9, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r25;
    // 0x802C5C40: sw          $t1, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r9;
    // 0x802C5C44: b           L_802C5CF0
    // 0x802C5C48: sw          $t2, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r10;
        goto L_802C5CF0;
    // 0x802C5C48: sw          $t2, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r10;
L_802C5C4C:
    // 0x802C5C4C: lui         $t3, 0x801D
    ctx->r11 = S32(0X801D << 16);
    // 0x802C5C50: lhu         $t3, -0x19A6($t3)
    ctx->r11 = MEM_HU(ctx->r11, -0X19A6);
    // 0x802C5C54: andi        $t4, $t3, 0xB000
    ctx->r12 = ctx->r11 & 0XB000;
    // 0x802C5C58: beq         $t4, $zero, L_802C5CF0
    if (ctx->r12 == 0) {
        // 0x802C5C5C: addiu       $t5, $zero, 0x3
        ctx->r13 = ADD32(0, 0X3);
            goto L_802C5CF0;
    }
    // 0x802C5C5C: addiu       $t5, $zero, 0x3
    ctx->r13 = ADD32(0, 0X3);
    // 0x802C5C60: sw          $t5, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r13;
    // 0x802C5C64: b           L_802C5CF0
    // 0x802C5C68: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
        goto L_802C5CF0;
    // 0x802C5C68: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
L_802C5C6C:
    // 0x802C5C6C: lui         $v0, 0x802C
    ctx->r2 = S32(0X802C << 16);
    // 0x802C5C70: addiu       $v0, $v0, 0x5D88
    ctx->r2 = ADD32(ctx->r2, 0X5D88);
    // 0x802C5C74: lw          $t6, 0x0($v0)
    ctx->r14 = MEM_W(ctx->r2, 0X0);
    // 0x802C5C78: lui         $a0, 0x802C
    ctx->r4 = S32(0X802C << 16);
    // 0x802C5C7C: addiu       $a0, $a0, 0x5D84
    ctx->r4 = ADD32(ctx->r4, 0X5D84);
    // 0x802C5C80: addiu       $t7, $t6, 0x14
    ctx->r15 = ADD32(ctx->r14, 0X14);
    // 0x802C5C84: slti        $at, $t7, 0x1A8
    ctx->r1 = SIGNED(ctx->r15) < 0X1A8 ? 1 : 0;
    // 0x802C5C88: bne         $at, $zero, L_802C5CF0
    if (ctx->r1 != 0) {
        // 0x802C5C8C: sw          $t7, 0x0($v0)
        MEM_W(0X0, ctx->r2) = ctx->r15;
            goto L_802C5CF0;
    }
    // 0x802C5C8C: sw          $t7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r15;
    // 0x802C5C90: addiu       $t9, $zero, 0x7
    ctx->r25 = ADD32(0, 0X7);
    // 0x802C5C94: addiu       $t0, $zero, 0x1A8
    ctx->r8 = ADD32(0, 0X1A8);
    // 0x802C5C98: sw          $t9, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r25;
    // 0x802C5C9C: sw          $t0, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r8;
    // 0x802C5CA0: b           L_802C5CF0
    // 0x802C5CA4: sw          $zero, 0x0($a0)
    MEM_W(0X0, ctx->r4) = 0;
        goto L_802C5CF0;
    // 0x802C5CA4: sw          $zero, 0x0($a0)
    MEM_W(0X0, ctx->r4) = 0;
L_802C5CA8:
    // 0x802C5CA8: lui         $a0, 0x802C
    ctx->r4 = S32(0X802C << 16);
    // 0x802C5CAC: addiu       $a0, $a0, 0x5D84
    ctx->r4 = ADD32(ctx->r4, 0X5D84);
    // 0x802C5CB0: lw          $t1, 0x0($a0)
    ctx->r9 = MEM_W(ctx->r4, 0X0);
    // 0x802C5CB4: addiu       $t2, $t1, 0x1
    ctx->r10 = ADD32(ctx->r9, 0X1);
    // 0x802C5CB8: slti        $at, $t2, 0x3
    ctx->r1 = SIGNED(ctx->r10) < 0X3 ? 1 : 0;
    // 0x802C5CBC: bne         $at, $zero, L_802C5CF0
    if (ctx->r1 != 0) {
        // 0x802C5CC0: sw          $t2, 0x0($a0)
        MEM_W(0X0, ctx->r4) = ctx->r10;
            goto L_802C5CF0;
    }
    // 0x802C5CC0: sw          $t2, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r10;
    // 0x802C5CC4: lui         $t4, 0x801C
    ctx->r12 = S32(0X801C << 16);
    // 0x802C5CC8: lw          $t4, 0x2928($t4)
    ctx->r12 = MEM_W(ctx->r12, 0X2928);
    // 0x802C5CCC: beq         $t4, $zero, L_802C5CE4
    if (ctx->r12 == 0) {
        // 0x802C5CD0: nop
    
            goto L_802C5CE4;
    }
    // 0x802C5CD0: nop

    // 0x802C5CD4: jal         0x801EC9C8
    // 0x802C5CD8: sw          $a1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r5;
    func_801EC9C8(rdram, ctx);
        goto after_0;
    // 0x802C5CD8: sw          $a1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r5;
    after_0:
    // 0x802C5CDC: b           L_802C5CF0
    // 0x802C5CE0: lw          $a1, 0x1C($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X1C);
        goto L_802C5CF0;
    // 0x802C5CE0: lw          $a1, 0x1C($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X1C);
L_802C5CE4:
    // 0x802C5CE4: jal         0x801ED004
    // 0x802C5CE8: sw          $a1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r5;
    func_801ED004(rdram, ctx);
        goto after_1;
    // 0x802C5CE8: sw          $a1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r5;
    after_1:
    // 0x802C5CEC: lw          $a1, 0x1C($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X1C);
L_802C5CF0:
    // 0x802C5CF0: lui         $v0, 0x802C
    ctx->r2 = S32(0X802C << 16);
    // 0x802C5CF4: beq         $a1, $zero, L_802C5D10
    if (ctx->r5 == 0) {
        // 0x802C5CF8: addiu       $v0, $v0, 0x5D88
        ctx->r2 = ADD32(ctx->r2, 0X5D88);
            goto L_802C5D10;
    }
    // 0x802C5CF8: addiu       $v0, $v0, 0x5D88
    ctx->r2 = ADD32(ctx->r2, 0X5D88);
    // 0x802C5CFC: addiu       $a0, $zero, 0x31
    ctx->r4 = ADD32(0, 0X31);
    // 0x802C5D00: jal         0x800C37F4
    // 0x802C5D04: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_2;
    // 0x802C5D04: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_2:
    // 0x802C5D08: lui         $v0, 0x802C
    ctx->r2 = S32(0X802C << 16);
    // 0x802C5D0C: addiu       $v0, $v0, 0x5D88
    ctx->r2 = ADD32(ctx->r2, 0X5D88);
L_802C5D10:
    // 0x802C5D10: lw          $t5, 0x0($v0)
    ctx->r13 = MEM_W(ctx->r2, 0X0);
    // 0x802C5D14: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x802C5D18: addiu       $t6, $zero, 0x28
    ctx->r14 = ADD32(0, 0X28);
    // 0x802C5D1C: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C5D20: subu        $t7, $t6, $t5
    ctx->r15 = SUB32(ctx->r14, ctx->r13);
    // 0x802C5D24: sw          $t7, 0x5D8C($at)
    MEM_W(0X5D8C, ctx->r1) = ctx->r15;
    // 0x802C5D28: jr          $ra
    // 0x802C5D2C: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    return;
    // 0x802C5D2C: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
;}
RECOMP_FUNC void func_1C3D00_802C5800(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C5800: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x802C5804: addiu       $v0, $v0, -0x19C4
    ctx->r2 = ADD32(ctx->r2, -0X19C4);
    // 0x802C5808: lw          $t6, 0x0($v0)
    ctx->r14 = MEM_W(ctx->r2, 0X0);
    // 0x802C580C: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x802C5810: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x802C5814: beq         $t6, $zero, L_802C5850
    if (ctx->r14 == 0) {
        // 0x802C5818: sw          $a0, 0x18($sp)
        MEM_W(0X18, ctx->r29) = ctx->r4;
            goto L_802C5850;
    }
    // 0x802C5818: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    // 0x802C581C: sw          $zero, 0x0($v0)
    MEM_W(0X0, ctx->r2) = 0;
    // 0x802C5820: lui         $t7, 0x800E
    ctx->r15 = S32(0X800E << 16);
    // 0x802C5824: lw          $t7, -0x54DC($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X54DC);
    // 0x802C5828: addiu       $at, $zero, 0x36
    ctx->r1 = ADD32(0, 0X36);
    // 0x802C582C: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    // 0x802C5830: bne         $t7, $at, L_802C5850
    if (ctx->r15 != ctx->r1) {
        // 0x802C5834: lui         $at, 0x802C
        ctx->r1 = S32(0X802C << 16);
            goto L_802C5850;
    }
    // 0x802C5834: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C5838: jal         0x800C6AD0
    // 0x802C583C: sw          $zero, 0x5EF0($at)
    MEM_W(0X5EF0, ctx->r1) = 0;
    osViBlack_recomp(rdram, ctx);
        goto after_0;
    // 0x802C583C: sw          $zero, 0x5EF0($at)
    MEM_W(0X5EF0, ctx->r1) = 0;
    after_0:
    // 0x802C5840: jal         0x80093C44
    // 0x802C5844: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
    func_80093C44(rdram, ctx);
        goto after_1;
    // 0x802C5844: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
    after_1:
    // 0x802C5848: b           L_802C58D0
    // 0x802C584C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_802C58D0;
    // 0x802C584C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C5850:
    // 0x802C5850: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x802C5854: sw          $zero, -0x54D4($at)
    MEM_W(-0X54D4, ctx->r1) = 0;
    // 0x802C5858: jal         0x8008FB74
    // 0x802C585C: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
    func_8008FB74(rdram, ctx);
        goto after_2;
    // 0x802C585C: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
    after_2:
    // 0x802C5860: lui         $a1, 0x800E
    ctx->r5 = S32(0X800E << 16);
    // 0x802C5864: lw          $a1, -0x7E90($a1)
    ctx->r5 = MEM_W(ctx->r5, -0X7E90);
    // 0x802C5868: jal         0x800949B8
    // 0x802C586C: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    func_800949B8(rdram, ctx);
        goto after_3;
    // 0x802C586C: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    after_3:
    // 0x802C5870: jal         0x80090F58
    // 0x802C5874: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    Draw_WaterEffects(rdram, ctx);
        goto after_4;
    // 0x802C5874: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    after_4:
    // 0x802C5878: jal         0x802C58DC
    // 0x802C587C: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    func_1C3D00_802C58DC(rdram, ctx);
        goto after_5;
    // 0x802C587C: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    after_5:
    // 0x802C5880: lui         $t8, 0x800E
    ctx->r24 = S32(0X800E << 16);
    // 0x802C5884: lw          $t8, -0x54DC($t8)
    ctx->r24 = MEM_W(ctx->r24, -0X54DC);
    // 0x802C5888: addiu       $at, $zero, 0x36
    ctx->r1 = ADD32(0, 0X36);
    // 0x802C588C: sw          $v0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r2;
    // 0x802C5890: bne         $t8, $at, L_802C58C0
    if (ctx->r24 != ctx->r1) {
        // 0x802C5894: lui         $t9, 0x8023
        ctx->r25 = S32(0X8023 << 16);
            goto L_802C58C0;
    }
    // 0x802C5894: lui         $t9, 0x8023
    ctx->r25 = S32(0X8023 << 16);
    // 0x802C5898: lh          $t9, -0x75EA($t9)
    ctx->r25 = MEM_H(ctx->r25, -0X75EA);
    // 0x802C589C: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x802C58A0: bne         $t9, $at, L_802C58B0
    if (ctx->r25 != ctx->r1) {
        // 0x802C58A4: nop
    
            goto L_802C58B0;
    }
    // 0x802C58A4: nop

    // 0x802C58A8: jal         0x800C30F8
    // 0x802C58AC: nop

    func_800C30F8(rdram, ctx);
        goto after_6;
    // 0x802C58AC: nop

    after_6:
L_802C58B0:
    // 0x802C58B0: jal         0x802C5D44
    // 0x802C58B4: nop

    func_1C3D00_802C5D44(rdram, ctx);
        goto after_7;
    // 0x802C58B4: nop

    after_7:
    // 0x802C58B8: b           L_802C58CC
    // 0x802C58BC: lw          $v0, 0x18($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X18);
        goto L_802C58CC;
    // 0x802C58BC: lw          $v0, 0x18($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X18);
L_802C58C0:
    // 0x802C58C0: jal         0x802C5E10
    // 0x802C58C4: nop

    func_1C3D00_802C5E10(rdram, ctx);
        goto after_8;
    // 0x802C58C4: nop

    after_8:
    // 0x802C58C8: lw          $v0, 0x18($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X18);
L_802C58CC:
    // 0x802C58CC: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C58D0:
    // 0x802C58D0: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x802C58D4: jr          $ra
    // 0x802C58D8: nop

    return;
    // 0x802C58D8: nop

;}
RECOMP_FUNC void func_1C3D00_802C58DC(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C58DC: addiu       $sp, $sp, -0x88
    ctx->r29 = ADD32(ctx->r29, -0X88);
    // 0x802C58E0: sw          $ra, 0x54($sp)
    MEM_W(0X54, ctx->r29) = ctx->r31;
    // 0x802C58E4: sw          $s5, 0x50($sp)
    MEM_W(0X50, ctx->r29) = ctx->r21;
    // 0x802C58E8: sw          $s4, 0x4C($sp)
    MEM_W(0X4C, ctx->r29) = ctx->r20;
    // 0x802C58EC: sw          $s3, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r19;
    // 0x802C58F0: sw          $s2, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r18;
    // 0x802C58F4: sw          $s1, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r17;
    // 0x802C58F8: sw          $s0, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r16;
    // 0x802C58FC: lui         $t7, 0x107
    ctx->r15 = S32(0X107 << 16);
    // 0x802C5900: addiu       $t7, $t7, -0x9D8
    ctx->r15 = ADD32(ctx->r15, -0X9D8);
    // 0x802C5904: lui         $t6, 0x600
    ctx->r14 = S32(0X600 << 16);
    // 0x802C5908: sw          $t6, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r14;
    // 0x802C590C: sw          $t7, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r15;
    // 0x802C5910: addiu       $s2, $a0, 0x8
    ctx->r18 = ADD32(ctx->r4, 0X8);
    // 0x802C5914: addiu       $t8, $zero, 0xD6
    ctx->r24 = ADD32(0, 0XD6);
    // 0x802C5918: addiu       $t9, $zero, 0x1A
    ctx->r25 = ADD32(0, 0X1A);
    // 0x802C591C: sw          $t9, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r25;
    // 0x802C5920: sw          $t8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r24;
    // 0x802C5924: or          $a0, $s2, $zero
    ctx->r4 = ctx->r18 | 0;
    // 0x802C5928: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C592C: addiu       $a2, $zero, 0x69
    ctx->r6 = ADD32(0, 0X69);
    // 0x802C5930: jal         0x80094338
    // 0x802C5934: addiu       $a3, $zero, 0x26
    ctx->r7 = ADD32(0, 0X26);
    func_80094338(rdram, ctx);
        goto after_0;
    // 0x802C5934: addiu       $a3, $zero, 0x26
    ctx->r7 = ADD32(0, 0X26);
    after_0:
    // 0x802C5938: addiu       $t0, $zero, 0xAE
    ctx->r8 = ADD32(0, 0XAE);
    // 0x802C593C: addiu       $t1, $zero, 0x10
    ctx->r9 = ADD32(0, 0X10);
    // 0x802C5940: sw          $t1, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r9;
    // 0x802C5944: sw          $t0, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r8;
    // 0x802C5948: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C594C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C5950: addiu       $a2, $zero, 0x7D
    ctx->r6 = ADD32(0, 0X7D);
    // 0x802C5954: jal         0x80094338
    // 0x802C5958: addiu       $a3, $zero, 0x49
    ctx->r7 = ADD32(0, 0X49);
    func_80094338(rdram, ctx);
        goto after_1;
    // 0x802C5958: addiu       $a3, $zero, 0x49
    ctx->r7 = ADD32(0, 0X49);
    after_1:
    // 0x802C595C: addiu       $t2, $zero, 0xAE
    ctx->r10 = ADD32(0, 0XAE);
    // 0x802C5960: addiu       $t3, $zero, 0x19
    ctx->r11 = ADD32(0, 0X19);
    // 0x802C5964: sw          $t3, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r11;
    // 0x802C5968: sw          $t2, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r10;
    // 0x802C596C: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C5970: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C5974: addiu       $a2, $zero, 0x7D
    ctx->r6 = ADD32(0, 0X7D);
    // 0x802C5978: jal         0x80094338
    // 0x802C597C: addiu       $a3, $zero, 0x5A
    ctx->r7 = ADD32(0, 0X5A);
    func_80094338(rdram, ctx);
        goto after_2;
    // 0x802C597C: addiu       $a3, $zero, 0x5A
    ctx->r7 = ADD32(0, 0X5A);
    after_2:
    // 0x802C5980: or          $s2, $v0, $zero
    ctx->r18 = ctx->r2 | 0;
    // 0x802C5984: addiu       $s0, $zero, 0x8C
    ctx->r16 = ADD32(0, 0X8C);
L_802C5988:
    // 0x802C5988: addiu       $t4, $zero, 0xAE
    ctx->r12 = ADD32(0, 0XAE);
    // 0x802C598C: addiu       $t5, $zero, 0x10
    ctx->r13 = ADD32(0, 0X10);
    // 0x802C5990: sw          $t5, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r13;
    // 0x802C5994: sw          $t4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r12;
    // 0x802C5998: or          $a0, $s2, $zero
    ctx->r4 = ctx->r18 | 0;
    // 0x802C599C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C59A0: addiu       $a2, $zero, 0x7D
    ctx->r6 = ADD32(0, 0X7D);
    // 0x802C59A4: jal         0x80094338
    // 0x802C59A8: or          $a3, $s0, $zero
    ctx->r7 = ctx->r16 | 0;
    func_80094338(rdram, ctx);
        goto after_3;
    // 0x802C59A8: or          $a3, $s0, $zero
    ctx->r7 = ctx->r16 | 0;
    after_3:
    // 0x802C59AC: addiu       $s0, $s0, 0x12
    ctx->r16 = ADD32(ctx->r16, 0X12);
    // 0x802C59B0: slti        $at, $s0, 0xD4
    ctx->r1 = SIGNED(ctx->r16) < 0XD4 ? 1 : 0;
    // 0x802C59B4: bne         $at, $zero, L_802C5988
    if (ctx->r1 != 0) {
        // 0x802C59B8: or          $s2, $v0, $zero
        ctx->r18 = ctx->r2 | 0;
            goto L_802C5988;
    }
    // 0x802C59B8: or          $s2, $v0, $zero
    ctx->r18 = ctx->r2 | 0;
    // 0x802C59BC: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C59C0: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C59C4: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C59C8: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C59CC: addiu       $t0, $zero, 0xFF
    ctx->r8 = ADD32(0, 0XFF);
    // 0x802C59D0: addiu       $t1, $zero, 0xFF
    ctx->r9 = ADD32(0, 0XFF);
    // 0x802C59D4: addiu       $t2, $zero, 0xFF
    ctx->r10 = ADD32(0, 0XFF);
    // 0x802C59D8: addiu       $t3, $zero, 0xFF
    ctx->r11 = ADD32(0, 0XFF);
    // 0x802C59DC: addiu       $t4, $zero, 0xFF
    ctx->r12 = ADD32(0, 0XFF);
    // 0x802C59E0: addiu       $t5, $zero, 0xFF
    ctx->r13 = ADD32(0, 0XFF);
    // 0x802C59E4: sw          $t5, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r13;
    // 0x802C59E8: sw          $t4, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r12;
    // 0x802C59EC: sw          $t3, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r11;
    // 0x802C59F0: sw          $t2, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r10;
    // 0x802C59F4: sw          $t1, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r9;
    // 0x802C59F8: sw          $t0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r8;
    // 0x802C59FC: sw          $t9, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r25;
    // 0x802C5A00: sw          $t8, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r24;
    // 0x802C5A04: sw          $t7, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r15;
    // 0x802C5A08: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x802C5A0C: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C5A10: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C5A14: addiu       $a2, $zero, 0xFF
    ctx->r6 = ADD32(0, 0XFF);
    // 0x802C5A18: jal         0x801E946C
    // 0x802C5A1C: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    func_801E946C(rdram, ctx);
        goto after_4;
    // 0x802C5A1C: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    after_4:
    // 0x802C5A20: addiu       $t6, $zero, 0x2A
    ctx->r14 = ADD32(0, 0X2A);
    // 0x802C5A24: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x802C5A28: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C5A2C: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C5A30: addiu       $a2, $zero, 0x12
    ctx->r6 = ADD32(0, 0X12);
    // 0x802C5A34: addiu       $a3, $zero, 0x7A
    ctx->r7 = ADD32(0, 0X7A);
    // 0x802C5A38: jal         0x801E3EE0
    // 0x802C5A3C: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    func_801E3EE0(rdram, ctx);
        goto after_5;
    // 0x802C5A3C: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    after_5:
    // 0x802C5A40: lui         $a2, 0x802C
    ctx->r6 = S32(0X802C << 16);
    // 0x802C5A44: addiu       $t7, $zero, 0x4B
    ctx->r15 = ADD32(0, 0X4B);
    // 0x802C5A48: sw          $t7, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r15;
    // 0x802C5A4C: addiu       $a2, $a2, 0x5EE0
    ctx->r6 = ADD32(ctx->r6, 0X5EE0);
    // 0x802C5A50: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C5A54: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C5A58: jal         0x801E9858
    // 0x802C5A5C: addiu       $a3, $zero, 0x97
    ctx->r7 = ADD32(0, 0X97);
    func_801E9858(rdram, ctx);
        goto after_6;
    // 0x802C5A5C: addiu       $a3, $zero, 0x97
    ctx->r7 = ADD32(0, 0X97);
    after_6:
    // 0x802C5A60: lui         $a2, 0x802C
    ctx->r6 = S32(0X802C << 16);
    // 0x802C5A64: addiu       $t8, $zero, 0x4B
    ctx->r24 = ADD32(0, 0X4B);
    // 0x802C5A68: sw          $t8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r24;
    // 0x802C5A6C: addiu       $a2, $a2, 0x5EE4
    ctx->r6 = ADD32(ctx->r6, 0X5EE4);
    // 0x802C5A70: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C5A74: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C5A78: jal         0x801E9858
    // 0x802C5A7C: addiu       $a3, $zero, 0xFE
    ctx->r7 = ADD32(0, 0XFE);
    func_801E9858(rdram, ctx);
        goto after_7;
    // 0x802C5A7C: addiu       $a3, $zero, 0xFE
    ctx->r7 = ADD32(0, 0XFE);
    after_7:
    // 0x802C5A80: lui         $a2, 0x802C
    ctx->r6 = S32(0X802C << 16);
    // 0x802C5A84: addiu       $t9, $zero, 0x5F
    ctx->r25 = ADD32(0, 0X5F);
    // 0x802C5A88: sw          $t9, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r25;
    // 0x802C5A8C: addiu       $a2, $a2, 0x5EE8
    ctx->r6 = ADD32(ctx->r6, 0X5EE8);
    // 0x802C5A90: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C5A94: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C5A98: jal         0x801E9858
    // 0x802C5A9C: addiu       $a3, $zero, 0xCD
    ctx->r7 = ADD32(0, 0XCD);
    func_801E9858(rdram, ctx);
        goto after_8;
    // 0x802C5A9C: addiu       $a3, $zero, 0xCD
    ctx->r7 = ADD32(0, 0XCD);
    after_8:
    // 0x802C5AA0: addiu       $t0, $zero, 0x4D
    ctx->r8 = ADD32(0, 0X4D);
    // 0x802C5AA4: sw          $t0, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r8;
    // 0x802C5AA8: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C5AAC: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C5AB0: addiu       $a2, $zero, 0x15
    ctx->r6 = ADD32(0, 0X15);
    // 0x802C5AB4: addiu       $a3, $zero, 0xC4
    ctx->r7 = ADD32(0, 0XC4);
    // 0x802C5AB8: jal         0x801E3EE0
    // 0x802C5ABC: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    func_801E3EE0(rdram, ctx);
        goto after_9;
    // 0x802C5ABC: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    after_9:
    // 0x802C5AC0: lui         $s0, 0x801D
    ctx->r16 = S32(0X801D << 16);
    // 0x802C5AC4: addiu       $s0, $s0, -0x4C10
    ctx->r16 = ADD32(ctx->r16, -0X4C10);
    // 0x802C5AC8: addiu       $t1, $zero, 0x5C
    ctx->r9 = ADD32(0, 0X5C);
    // 0x802C5ACC: sw          $t1, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r9;
    // 0x802C5AD0: lw          $a2, 0x0($s0)
    ctx->r6 = MEM_W(ctx->r16, 0X0);
    // 0x802C5AD4: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C5AD8: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C5ADC: jal         0x801EB00C
    // 0x802C5AE0: addiu       $a3, $zero, 0x97
    ctx->r7 = ADD32(0, 0X97);
    func_801EB00C(rdram, ctx);
        goto after_10;
    // 0x802C5AE0: addiu       $a3, $zero, 0x97
    ctx->r7 = ADD32(0, 0X97);
    after_10:
    // 0x802C5AE4: addiu       $s1, $sp, 0x60
    ctx->r17 = ADD32(ctx->r29, 0X60);
    // 0x802C5AE8: lui         $a1, 0x802C
    ctx->r5 = S32(0X802C << 16);
    // 0x802C5AEC: or          $s2, $v0, $zero
    ctx->r18 = ctx->r2 | 0;
    // 0x802C5AF0: addiu       $a1, $a1, 0x5EEC
    ctx->r5 = ADD32(ctx->r5, 0X5EEC);
    // 0x802C5AF4: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    // 0x802C5AF8: jal         0x800CA210
    // 0x802C5AFC: lw          $a2, 0x4($s0)
    ctx->r6 = MEM_W(ctx->r16, 0X4);
    func_800CA210(rdram, ctx);
        goto after_11;
    // 0x802C5AFC: lw          $a2, 0x4($s0)
    ctx->r6 = MEM_W(ctx->r16, 0X4);
    after_11:
    // 0x802C5B00: addiu       $t2, $zero, 0x5C
    ctx->r10 = ADD32(0, 0X5C);
    // 0x802C5B04: sw          $t2, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r10;
    // 0x802C5B08: or          $a0, $s2, $zero
    ctx->r4 = ctx->r18 | 0;
    // 0x802C5B0C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C5B10: or          $a2, $s1, $zero
    ctx->r6 = ctx->r17 | 0;
    // 0x802C5B14: jal         0x801E9858
    // 0x802C5B18: addiu       $a3, $zero, 0xF5
    ctx->r7 = ADD32(0, 0XF5);
    func_801E9858(rdram, ctx);
        goto after_12;
    // 0x802C5B18: addiu       $a3, $zero, 0xF5
    ctx->r7 = ADD32(0, 0XF5);
    after_12:
    // 0x802C5B1C: lui         $s0, 0x802C
    ctx->r16 = S32(0X802C << 16);
    // 0x802C5B20: lui         $s4, 0x802C
    ctx->r20 = S32(0X802C << 16);
    // 0x802C5B24: or          $s2, $v0, $zero
    ctx->r18 = ctx->r2 | 0;
    // 0x802C5B28: addiu       $s4, $s4, 0x5EF0
    ctx->r20 = ADD32(ctx->r20, 0X5EF0);
    // 0x802C5B2C: addiu       $s0, $s0, 0x5EB0
    ctx->r16 = ADD32(ctx->r16, 0X5EB0);
    // 0x802C5B30: or          $s1, $zero, $zero
    ctx->r17 = 0 | 0;
    // 0x802C5B34: addiu       $s5, $zero, 0x12
    ctx->r21 = ADD32(0, 0X12);
    // 0x802C5B38: addiu       $s3, $zero, 0x4
    ctx->r19 = ADD32(0, 0X4);
L_802C5B3C:
    // 0x802C5B3C: lw          $t3, 0x0($s4)
    ctx->r11 = MEM_W(ctx->r20, 0X0);
    // 0x802C5B40: beql        $s1, $t3, L_802C5B7C
    if (ctx->r17 == ctx->r11) {
        // 0x802C5B44: addiu       $s1, $s1, 0x1
        ctx->r17 = ADD32(ctx->r17, 0X1);
            goto L_802C5B7C;
    }
    goto skip_0;
    // 0x802C5B44: addiu       $s1, $s1, 0x1
    ctx->r17 = ADD32(ctx->r17, 0X1);
    skip_0:
    // 0x802C5B48: multu       $s1, $s5
    result = U64(U32(ctx->r17)) * U64(U32(ctx->r21)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x802C5B4C: lh          $a3, 0x0($s0)
    ctx->r7 = MEM_H(ctx->r16, 0X0);
    // 0x802C5B50: lw          $a2, 0x4($s0)
    ctx->r6 = MEM_W(ctx->r16, 0X4);
    // 0x802C5B54: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    // 0x802C5B58: or          $a0, $s2, $zero
    ctx->r4 = ctx->r18 | 0;
    // 0x802C5B5C: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C5B60: addiu       $a3, $a3, 0xBE
    ctx->r7 = ADD32(ctx->r7, 0XBE);
    // 0x802C5B64: mflo        $t4
    ctx->r12 = lo;
    // 0x802C5B68: addiu       $t5, $t4, 0x8F
    ctx->r13 = ADD32(ctx->r12, 0X8F);
    // 0x802C5B6C: jal         0x801E3EE0
    // 0x802C5B70: sw          $t5, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r13;
    func_801E3EE0(rdram, ctx);
        goto after_13;
    // 0x802C5B70: sw          $t5, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r13;
    after_13:
    // 0x802C5B74: or          $s2, $v0, $zero
    ctx->r18 = ctx->r2 | 0;
    // 0x802C5B78: addiu       $s1, $s1, 0x1
    ctx->r17 = ADD32(ctx->r17, 0X1);
L_802C5B7C:
    // 0x802C5B7C: bne         $s1, $s3, L_802C5B3C
    if (ctx->r17 != ctx->r19) {
        // 0x802C5B80: addiu       $s0, $s0, 0x8
        ctx->r16 = ADD32(ctx->r16, 0X8);
            goto L_802C5B3C;
    }
    // 0x802C5B80: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C5B84: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C5B88: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C5B8C: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C5B90: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C5B94: addiu       $t0, $zero, 0xFF
    ctx->r8 = ADD32(0, 0XFF);
    // 0x802C5B98: addiu       $t1, $zero, 0xFF
    ctx->r9 = ADD32(0, 0XFF);
    // 0x802C5B9C: addiu       $t2, $zero, 0xFF
    ctx->r10 = ADD32(0, 0XFF);
    // 0x802C5BA0: addiu       $t3, $zero, 0xFF
    ctx->r11 = ADD32(0, 0XFF);
    // 0x802C5BA4: addiu       $t4, $zero, 0xFF
    ctx->r12 = ADD32(0, 0XFF);
    // 0x802C5BA8: addiu       $t5, $zero, 0xFF
    ctx->r13 = ADD32(0, 0XFF);
    // 0x802C5BAC: sw          $t5, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r13;
    // 0x802C5BB0: sw          $t4, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r12;
    // 0x802C5BB4: sw          $t3, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r11;
    // 0x802C5BB8: sw          $t2, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r10;
    // 0x802C5BBC: sw          $t1, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r9;
    // 0x802C5BC0: sw          $t0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r8;
    // 0x802C5BC4: sw          $t9, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r25;
    // 0x802C5BC8: sw          $t8, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r24;
    // 0x802C5BCC: sw          $t7, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r15;
    // 0x802C5BD0: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x802C5BD4: or          $a0, $s2, $zero
    ctx->r4 = ctx->r18 | 0;
    // 0x802C5BD8: addiu       $a1, $zero, 0x6
    ctx->r5 = ADD32(0, 0X6);
    // 0x802C5BDC: addiu       $a2, $zero, 0xFF
    ctx->r6 = ADD32(0, 0XFF);
    // 0x802C5BE0: jal         0x801E946C
    // 0x802C5BE4: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    func_801E946C(rdram, ctx);
        goto after_14;
    // 0x802C5BE4: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    after_14:
    // 0x802C5BE8: lw          $v1, 0x0($s4)
    ctx->r3 = MEM_W(ctx->r20, 0X0);
    // 0x802C5BEC: lui         $t7, 0x802C
    ctx->r15 = S32(0X802C << 16);
    // 0x802C5BF0: addiu       $t7, $t7, 0x5EB0
    ctx->r15 = ADD32(ctx->r15, 0X5EB0);
    // 0x802C5BF4: multu       $v1, $s5
    result = U64(U32(ctx->r3)) * U64(U32(ctx->r21)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x802C5BF8: sll         $t6, $v1, 3
    ctx->r14 = S32(ctx->r3 << 3);
    // 0x802C5BFC: addu        $s0, $t6, $t7
    ctx->r16 = ADD32(ctx->r14, ctx->r15);
    // 0x802C5C00: lh          $a3, 0x0($s0)
    ctx->r7 = MEM_H(ctx->r16, 0X0);
    // 0x802C5C04: lw          $a2, 0x4($s0)
    ctx->r6 = MEM_W(ctx->r16, 0X4);
    // 0x802C5C08: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    // 0x802C5C0C: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C5C10: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C5C14: addiu       $a3, $a3, 0xBE
    ctx->r7 = ADD32(ctx->r7, 0XBE);
    // 0x802C5C18: mflo        $t8
    ctx->r24 = lo;
    // 0x802C5C1C: addiu       $t9, $t8, 0x8F
    ctx->r25 = ADD32(ctx->r24, 0X8F);
    // 0x802C5C20: jal         0x801E3EE0
    // 0x802C5C24: sw          $t9, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r25;
    func_801E3EE0(rdram, ctx);
        goto after_15;
    // 0x802C5C24: sw          $t9, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r25;
    after_15:
    // 0x802C5C28: lw          $ra, 0x54($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X54);
    // 0x802C5C2C: lw          $s0, 0x3C($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X3C);
    // 0x802C5C30: lw          $s1, 0x40($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X40);
    // 0x802C5C34: lw          $s2, 0x44($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X44);
    // 0x802C5C38: lw          $s3, 0x48($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X48);
    // 0x802C5C3C: lw          $s4, 0x4C($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X4C);
    // 0x802C5C40: lw          $s5, 0x50($sp)
    ctx->r21 = MEM_W(ctx->r29, 0X50);
    // 0x802C5C44: jr          $ra
    // 0x802C5C48: addiu       $sp, $sp, 0x88
    ctx->r29 = ADD32(ctx->r29, 0X88);
    return;
    // 0x802C5C48: addiu       $sp, $sp, 0x88
    ctx->r29 = ADD32(ctx->r29, 0X88);
;}
RECOMP_FUNC void func_1C3D00_802C5C4C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C5C4C: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x802C5C50: addiu       $v0, $v0, -0x54DC
    ctx->r2 = ADD32(ctx->r2, -0X54DC);
    // 0x802C5C54: lw          $t6, 0x0($v0)
    ctx->r14 = MEM_W(ctx->r2, 0X0);
    // 0x802C5C58: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C5C5C: addiu       $t7, $zero, 0x37
    ctx->r15 = ADD32(0, 0X37);
    // 0x802C5C60: sw          $t6, -0x19CC($at)
    MEM_W(-0X19CC, ctx->r1) = ctx->r14;
    // 0x802C5C64: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C5C68: sw          $a0, -0x19D0($at)
    MEM_W(-0X19D0, ctx->r1) = ctx->r4;
    // 0x802C5C6C: sw          $t7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r15;
    // 0x802C5C70: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C5C74: addiu       $t8, $zero, 0x12
    ctx->r24 = ADD32(0, 0X12);
    // 0x802C5C78: sw          $t8, -0x19C8($at)
    MEM_W(-0X19C8, ctx->r1) = ctx->r24;
    // 0x802C5C7C: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C5C80: addiu       $t9, $zero, 0x1
    ctx->r25 = ADD32(0, 0X1);
    // 0x802C5C84: sw          $t9, -0x19C4($at)
    MEM_W(-0X19C4, ctx->r1) = ctx->r25;
    // 0x802C5C88: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C5C8C: sw          $zero, -0x19C0($at)
    MEM_W(-0X19C0, ctx->r1) = 0;
    // 0x802C5C90: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C5C94: sw          $zero, -0x19BC($at)
    MEM_W(-0X19BC, ctx->r1) = 0;
    // 0x802C5C98: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x802C5C9C: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x802C5CA0: sw          $zero, -0x54E4($at)
    MEM_W(-0X54E4, ctx->r1) = 0;
    // 0x802C5CA4: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x802C5CA8: lui         $at, 0x800D
    ctx->r1 = S32(0X800D << 16);
    // 0x802C5CAC: addiu       $t0, $zero, 0x2
    ctx->r8 = ADD32(0, 0X2);
    // 0x802C5CB0: sw          $t0, 0x461C($at)
    MEM_W(0X461C, ctx->r1) = ctx->r8;
    // 0x802C5CB4: addiu       $a0, $zero, 0x5
    ctx->r4 = ADD32(0, 0X5);
    // 0x802C5CB8: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C5CBC: jal         0x801E6FB0
    // 0x802C5CC0: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    FadeTransition_SetProps(rdram, ctx);
        goto after_0;
    // 0x802C5CC0: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    after_0:
    // 0x802C5CC4: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x802C5CC8: lw          $v0, -0x19D0($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X19D0);
    // 0x802C5CCC: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x802C5CD0: bnel        $v0, $at, L_802C5CEC
    if (ctx->r2 != ctx->r1) {
        // 0x802C5CD4: addiu       $at, $zero, 0xA
        ctx->r1 = ADD32(0, 0XA);
            goto L_802C5CEC;
    }
    goto skip_0;
    // 0x802C5CD4: addiu       $at, $zero, 0xA
    ctx->r1 = ADD32(0, 0XA);
    skip_0:
    // 0x802C5CD8: jal         0x800C1F60
    // 0x802C5CDC: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    func_800C1F60(rdram, ctx);
        goto after_1;
    // 0x802C5CDC: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    after_1:
    // 0x802C5CE0: b           L_802C5D38
    // 0x802C5CE4: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_802C5D38;
    // 0x802C5CE4: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x802C5CE8: addiu       $at, $zero, 0xA
    ctx->r1 = ADD32(0, 0XA);
L_802C5CEC:
    // 0x802C5CEC: bnel        $v0, $at, L_802C5D08
    if (ctx->r2 != ctx->r1) {
        // 0x802C5CF0: addiu       $at, $zero, 0x14
        ctx->r1 = ADD32(0, 0X14);
            goto L_802C5D08;
    }
    goto skip_1;
    // 0x802C5CF0: addiu       $at, $zero, 0x14
    ctx->r1 = ADD32(0, 0X14);
    skip_1:
    // 0x802C5CF4: jal         0x800C1F60
    // 0x802C5CF8: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    func_800C1F60(rdram, ctx);
        goto after_2;
    // 0x802C5CF8: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    after_2:
    // 0x802C5CFC: b           L_802C5D38
    // 0x802C5D00: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_802C5D38;
    // 0x802C5D00: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x802C5D04: addiu       $at, $zero, 0x14
    ctx->r1 = ADD32(0, 0X14);
L_802C5D08:
    // 0x802C5D08: bnel        $v0, $at, L_802C5D24
    if (ctx->r2 != ctx->r1) {
        // 0x802C5D0C: addiu       $at, $zero, 0x28
        ctx->r1 = ADD32(0, 0X28);
            goto L_802C5D24;
    }
    goto skip_2;
    // 0x802C5D0C: addiu       $at, $zero, 0x28
    ctx->r1 = ADD32(0, 0X28);
    skip_2:
    // 0x802C5D10: jal         0x800C1F60
    // 0x802C5D14: addiu       $a0, $zero, 0xA
    ctx->r4 = ADD32(0, 0XA);
    func_800C1F60(rdram, ctx);
        goto after_3;
    // 0x802C5D14: addiu       $a0, $zero, 0xA
    ctx->r4 = ADD32(0, 0XA);
    after_3:
    // 0x802C5D18: b           L_802C5D38
    // 0x802C5D1C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_802C5D38;
    // 0x802C5D1C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x802C5D20: addiu       $at, $zero, 0x28
    ctx->r1 = ADD32(0, 0X28);
L_802C5D24:
    // 0x802C5D24: bnel        $v0, $at, L_802C5D38
    if (ctx->r2 != ctx->r1) {
        // 0x802C5D28: lw          $ra, 0x14($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X14);
            goto L_802C5D38;
    }
    goto skip_3;
    // 0x802C5D28: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    skip_3:
    // 0x802C5D2C: jal         0x800C1F60
    // 0x802C5D30: addiu       $a0, $zero, 0x7
    ctx->r4 = ADD32(0, 0X7);
    func_800C1F60(rdram, ctx);
        goto after_4;
    // 0x802C5D30: addiu       $a0, $zero, 0x7
    ctx->r4 = ADD32(0, 0X7);
    after_4:
    // 0x802C5D34: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C5D38:
    // 0x802C5D38: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x802C5D3C: jr          $ra
    // 0x802C5D40: nop

    return;
    // 0x802C5D40: nop

;}
RECOMP_FUNC void func_1C3D00_802C5D44(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C5D44: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x802C5D48: lhu         $v0, -0x196E($v0)
    ctx->r2 = MEM_HU(ctx->r2, -0X196E);
    // 0x802C5D4C: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x802C5D50: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x802C5D54: andi        $t6, $v0, 0xB000
    ctx->r14 = ctx->r2 & 0XB000;
    // 0x802C5D58: beq         $t6, $zero, L_802C5D94
    if (ctx->r14 == 0) {
        // 0x802C5D5C: andi        $t9, $v0, 0x800
        ctx->r25 = ctx->r2 & 0X800;
            goto L_802C5D94;
    }
    // 0x802C5D5C: andi        $t9, $v0, 0x800
    ctx->r25 = ctx->r2 & 0X800;
    // 0x802C5D60: lui         $v0, 0x802C
    ctx->r2 = S32(0X802C << 16);
    // 0x802C5D64: addiu       $v0, $v0, 0x5EF0
    ctx->r2 = ADD32(ctx->r2, 0X5EF0);
    // 0x802C5D68: lw          $t7, 0x0($v0)
    ctx->r15 = MEM_W(ctx->r2, 0X0);
    // 0x802C5D6C: lui         $a0, 0x802C
    ctx->r4 = S32(0X802C << 16);
    // 0x802C5D70: sll         $t8, $t7, 2
    ctx->r24 = S32(ctx->r15 << 2);
    // 0x802C5D74: addu        $a0, $a0, $t8
    ctx->r4 = ADD32(ctx->r4, ctx->r24);
    // 0x802C5D78: jal         0x802C5C4C
    // 0x802C5D7C: lw          $a0, 0x5ED0($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X5ED0);
    func_1C3D00_802C5C4C(rdram, ctx);
        goto after_0;
    // 0x802C5D7C: lw          $a0, 0x5ED0($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X5ED0);
    after_0:
    // 0x802C5D80: addiu       $a0, $zero, 0x11
    ctx->r4 = ADD32(0, 0X11);
    // 0x802C5D84: jal         0x800C37F4
    // 0x802C5D88: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_1;
    // 0x802C5D88: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_1:
    // 0x802C5D8C: b           L_802C5E04
    // 0x802C5D90: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_802C5E04;
    // 0x802C5D90: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C5D94:
    // 0x802C5D94: beq         $t9, $zero, L_802C5DD0
    if (ctx->r25 == 0) {
        // 0x802C5D98: andi        $t4, $v0, 0x400
        ctx->r12 = ctx->r2 & 0X400;
            goto L_802C5DD0;
    }
    // 0x802C5D98: andi        $t4, $v0, 0x400
    ctx->r12 = ctx->r2 & 0X400;
    // 0x802C5D9C: lui         $v0, 0x802C
    ctx->r2 = S32(0X802C << 16);
    // 0x802C5DA0: addiu       $v0, $v0, 0x5EF0
    ctx->r2 = ADD32(ctx->r2, 0X5EF0);
    // 0x802C5DA4: lw          $t0, 0x0($v0)
    ctx->r8 = MEM_W(ctx->r2, 0X0);
    // 0x802C5DA8: addiu       $t3, $zero, 0x3
    ctx->r11 = ADD32(0, 0X3);
    // 0x802C5DAC: addiu       $a0, $zero, 0x10
    ctx->r4 = ADD32(0, 0X10);
    // 0x802C5DB0: addiu       $t1, $t0, -0x1
    ctx->r9 = ADD32(ctx->r8, -0X1);
    // 0x802C5DB4: bgez        $t1, L_802C5DC0
    if (SIGNED(ctx->r9) >= 0) {
        // 0x802C5DB8: sw          $t1, 0x0($v0)
        MEM_W(0X0, ctx->r2) = ctx->r9;
            goto L_802C5DC0;
    }
    // 0x802C5DB8: sw          $t1, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r9;
    // 0x802C5DBC: sw          $t3, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r11;
L_802C5DC0:
    // 0x802C5DC0: jal         0x800C37F4
    // 0x802C5DC4: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_2;
    // 0x802C5DC4: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_2:
    // 0x802C5DC8: b           L_802C5E04
    // 0x802C5DCC: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_802C5E04;
    // 0x802C5DCC: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C5DD0:
    // 0x802C5DD0: beq         $t4, $zero, L_802C5E00
    if (ctx->r12 == 0) {
        // 0x802C5DD4: lui         $v0, 0x802C
        ctx->r2 = S32(0X802C << 16);
            goto L_802C5E00;
    }
    // 0x802C5DD4: lui         $v0, 0x802C
    ctx->r2 = S32(0X802C << 16);
    // 0x802C5DD8: addiu       $v0, $v0, 0x5EF0
    ctx->r2 = ADD32(ctx->r2, 0X5EF0);
    // 0x802C5DDC: lw          $t5, 0x0($v0)
    ctx->r13 = MEM_W(ctx->r2, 0X0);
    // 0x802C5DE0: addiu       $at, $zero, 0x4
    ctx->r1 = ADD32(0, 0X4);
    // 0x802C5DE4: addiu       $a0, $zero, 0x10
    ctx->r4 = ADD32(0, 0X10);
    // 0x802C5DE8: addiu       $t6, $t5, 0x1
    ctx->r14 = ADD32(ctx->r13, 0X1);
    // 0x802C5DEC: bne         $t6, $at, L_802C5DF8
    if (ctx->r14 != ctx->r1) {
        // 0x802C5DF0: sw          $t6, 0x0($v0)
        MEM_W(0X0, ctx->r2) = ctx->r14;
            goto L_802C5DF8;
    }
    // 0x802C5DF0: sw          $t6, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r14;
    // 0x802C5DF4: sw          $zero, 0x0($v0)
    MEM_W(0X0, ctx->r2) = 0;
L_802C5DF8:
    // 0x802C5DF8: jal         0x800C37F4
    // 0x802C5DFC: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_3;
    // 0x802C5DFC: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_3:
L_802C5E00:
    // 0x802C5E00: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C5E04:
    // 0x802C5E04: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x802C5E08: jr          $ra
    // 0x802C5E0C: nop

    return;
    // 0x802C5E0C: nop

;}
RECOMP_FUNC void func_1C3D00_802C5E10(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C5E10: lui         $t6, 0x8023
    ctx->r14 = S32(0X8023 << 16);
    // 0x802C5E14: lh          $t6, -0x75EA($t6)
    ctx->r14 = MEM_H(ctx->r14, -0X75EA);
    // 0x802C5E18: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x802C5E1C: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x802C5E20: bne         $t6, $at, L_802C5E94
    if (ctx->r14 != ctx->r1) {
        // 0x802C5E24: sw          $ra, 0x14($sp)
        MEM_W(0X14, ctx->r29) = ctx->r31;
            goto L_802C5E94;
    }
    // 0x802C5E24: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x802C5E28: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x802C5E2C: lw          $v0, -0x19D0($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X19D0);
    // 0x802C5E30: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x802C5E34: beq         $v0, $at, L_802C5E5C
    if (ctx->r2 == ctx->r1) {
        // 0x802C5E38: addiu       $at, $zero, 0xA
        ctx->r1 = ADD32(0, 0XA);
            goto L_802C5E5C;
    }
    // 0x802C5E38: addiu       $at, $zero, 0xA
    ctx->r1 = ADD32(0, 0XA);
    // 0x802C5E3C: beq         $v0, $at, L_802C5E7C
    if (ctx->r2 == ctx->r1) {
        // 0x802C5E40: addiu       $at, $zero, 0x14
        ctx->r1 = ADD32(0, 0X14);
            goto L_802C5E7C;
    }
    // 0x802C5E40: addiu       $at, $zero, 0x14
    ctx->r1 = ADD32(0, 0X14);
    // 0x802C5E44: beq         $v0, $at, L_802C5E8C
    if (ctx->r2 == ctx->r1) {
        // 0x802C5E48: addiu       $at, $zero, 0x28
        ctx->r1 = ADD32(0, 0X28);
            goto L_802C5E8C;
    }
    // 0x802C5E48: addiu       $at, $zero, 0x28
    ctx->r1 = ADD32(0, 0X28);
    // 0x802C5E4C: beq         $v0, $at, L_802C5E6C
    if (ctx->r2 == ctx->r1) {
        // 0x802C5E50: nop
    
            goto L_802C5E6C;
    }
    // 0x802C5E50: nop

    // 0x802C5E54: b           L_802C5E98
    // 0x802C5E58: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_802C5E98;
    // 0x802C5E58: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C5E5C:
    // 0x802C5E5C: jal         0x801EB180
    // 0x802C5E60: nop

    func_801EB180(rdram, ctx);
        goto after_0;
    // 0x802C5E60: nop

    after_0:
    // 0x802C5E64: b           L_802C5E98
    // 0x802C5E68: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_802C5E98;
    // 0x802C5E68: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C5E6C:
    // 0x802C5E6C: jal         0x8009345C
    // 0x802C5E70: nop

    func_8009345C(rdram, ctx);
        goto after_1;
    // 0x802C5E70: nop

    after_1:
    // 0x802C5E74: b           L_802C5E98
    // 0x802C5E78: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_802C5E98;
    // 0x802C5E78: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C5E7C:
    // 0x802C5E7C: jal         0x801EBD28
    // 0x802C5E80: nop

    func_801EBD28(rdram, ctx);
        goto after_2;
    // 0x802C5E80: nop

    after_2:
    // 0x802C5E84: b           L_802C5E98
    // 0x802C5E88: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_802C5E98;
    // 0x802C5E88: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C5E8C:
    // 0x802C5E8C: jal         0x801EBFE4
    // 0x802C5E90: nop

    func_801EBFE4(rdram, ctx);
        goto after_3;
    // 0x802C5E90: nop

    after_3:
L_802C5E94:
    // 0x802C5E94: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C5E98:
    // 0x802C5E98: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x802C5E9C: jr          $ra
    // 0x802C5EA0: nop

    return;
    // 0x802C5EA0: nop

    // 0x802C5EA4: nop

    // 0x802C5EA8: nop

    // 0x802C5EAC: nop

;}
RECOMP_FUNC void func_i7_802C5800(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C5800: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x802C5804: addiu       $v0, $v0, -0x19C4
    ctx->r2 = ADD32(ctx->r2, -0X19C4);
    // 0x802C5808: lw          $t6, 0x0($v0)
    ctx->r14 = MEM_W(ctx->r2, 0X0);
    // 0x802C580C: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x802C5810: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x802C5814: beq         $t6, $zero, L_802C585C
    if (ctx->r14 == 0) {
        // 0x802C5818: lui         $t7, 0x800E
        ctx->r15 = S32(0X800E << 16);
            goto L_802C585C;
    }
    // 0x802C5818: lui         $t7, 0x800E
    ctx->r15 = S32(0X800E << 16);
    // 0x802C581C: sw          $zero, 0x0($v0)
    MEM_W(0X0, ctx->r2) = 0;
    // 0x802C5820: lw          $t7, -0x54DC($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X54DC);
    // 0x802C5824: addiu       $at, $zero, 0x3C
    ctx->r1 = ADD32(0, 0X3C);
    // 0x802C5828: lui         $t8, 0x801D
    ctx->r24 = S32(0X801D << 16);
    // 0x802C582C: bne         $t7, $at, L_802C585C
    if (ctx->r15 != ctx->r1) {
        // 0x802C5830: nop
    
            goto L_802C585C;
    }
    // 0x802C5830: nop

    // 0x802C5834: lw          $t8, -0x19CC($t8)
    ctx->r24 = MEM_W(ctx->r24, -0X19CC);
    // 0x802C5838: addiu       $at, $zero, 0x4
    ctx->r1 = ADD32(0, 0X4);
    // 0x802C583C: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x802C5840: bne         $t8, $at, L_802C584C
    if (ctx->r24 != ctx->r1) {
        // 0x802C5844: addiu       $v0, $v0, -0x562C
        ctx->r2 = ADD32(ctx->r2, -0X562C);
            goto L_802C584C;
    }
    // 0x802C5844: addiu       $v0, $v0, -0x562C
    ctx->r2 = ADD32(ctx->r2, -0X562C);
    // 0x802C5848: sw          $zero, 0x0($v0)
    MEM_W(0X0, ctx->r2) = 0;
L_802C584C:
    // 0x802C584C: jal         0x80093C44
    // 0x802C5850: nop

    func_80093C44(rdram, ctx);
        goto after_0;
    // 0x802C5850: nop

    after_0:
    // 0x802C5854: b           L_802C5A0C
    // 0x802C5858: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_802C5A0C;
    // 0x802C5858: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C585C:
    // 0x802C585C: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x802C5860: jal         0x802C5A18
    // 0x802C5864: sw          $zero, -0x54D4($at)
    MEM_W(-0X54D4, ctx->r1) = 0;
    func_i7_802C5A18(rdram, ctx);
        goto after_1;
    // 0x802C5864: sw          $zero, -0x54D4($at)
    MEM_W(-0X54D4, ctx->r1) = 0;
    after_1:
    // 0x802C5868: lui         $t9, 0x800E
    ctx->r25 = S32(0X800E << 16);
    // 0x802C586C: lw          $t9, -0x54DC($t9)
    ctx->r25 = MEM_W(ctx->r25, -0X54DC);
    // 0x802C5870: addiu       $at, $zero, 0x3C
    ctx->r1 = ADD32(0, 0X3C);
    // 0x802C5874: sw          $v0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r2;
    // 0x802C5878: bne         $t9, $at, L_802C5960
    if (ctx->r25 != ctx->r1) {
        // 0x802C587C: lui         $t3, 0x8023
        ctx->r11 = S32(0X8023 << 16);
            goto L_802C5960;
    }
    // 0x802C587C: lui         $t3, 0x8023
    ctx->r11 = S32(0X8023 << 16);
    // 0x802C5880: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x802C5884: lhu         $v0, -0x19A6($v0)
    ctx->r2 = MEM_HU(ctx->r2, -0X19A6);
    // 0x802C5888: andi        $t0, $v0, 0xB000
    ctx->r8 = ctx->r2 & 0XB000;
    // 0x802C588C: beq         $t0, $zero, L_802C58C8
    if (ctx->r8 == 0) {
        // 0x802C5890: andi        $t3, $v0, 0x4000
        ctx->r11 = ctx->r2 & 0X4000;
            goto L_802C58C8;
    }
    // 0x802C5890: andi        $t3, $v0, 0x4000
    ctx->r11 = ctx->r2 & 0X4000;
    // 0x802C5894: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x802C5898: addiu       $v0, $v0, -0x562C
    ctx->r2 = ADD32(ctx->r2, -0X562C);
    // 0x802C589C: lw          $t1, 0x0($v0)
    ctx->r9 = MEM_W(ctx->r2, 0X0);
    // 0x802C58A0: lui         $a0, 0x802C
    ctx->r4 = S32(0X802C << 16);
    // 0x802C58A4: sll         $t2, $t1, 2
    ctx->r10 = S32(ctx->r9 << 2);
    // 0x802C58A8: addu        $a0, $a0, $t2
    ctx->r4 = ADD32(ctx->r4, ctx->r10);
    // 0x802C58AC: jal         0x802C5C94
    // 0x802C58B0: lw          $a0, 0x5D20($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X5D20);
    func_i7_802C5C94(rdram, ctx);
        goto after_2;
    // 0x802C58B0: lw          $a0, 0x5D20($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X5D20);
    after_2:
    // 0x802C58B4: addiu       $a0, $zero, 0x11
    ctx->r4 = ADD32(0, 0X11);
    // 0x802C58B8: jal         0x800C37F4
    // 0x802C58BC: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_3;
    // 0x802C58BC: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_3:
    // 0x802C58C0: b           L_802C5A08
    // 0x802C58C4: lw          $v0, 0x18($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X18);
        goto L_802C5A08;
    // 0x802C58C4: lw          $v0, 0x18($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X18);
L_802C58C8:
    // 0x802C58C8: beq         $t3, $zero, L_802C58EC
    if (ctx->r11 == 0) {
        // 0x802C58CC: andi        $t4, $v0, 0x800
        ctx->r12 = ctx->r2 & 0X800;
            goto L_802C58EC;
    }
    // 0x802C58CC: andi        $t4, $v0, 0x800
    ctx->r12 = ctx->r2 & 0X800;
    // 0x802C58D0: jal         0x802C5C94
    // 0x802C58D4: addiu       $a0, $zero, 0x2
    ctx->r4 = ADD32(0, 0X2);
    func_i7_802C5C94(rdram, ctx);
        goto after_4;
    // 0x802C58D4: addiu       $a0, $zero, 0x2
    ctx->r4 = ADD32(0, 0X2);
    after_4:
    // 0x802C58D8: addiu       $a0, $zero, 0x16
    ctx->r4 = ADD32(0, 0X16);
    // 0x802C58DC: jal         0x800C37F4
    // 0x802C58E0: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_5;
    // 0x802C58E0: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_5:
    // 0x802C58E4: b           L_802C5A08
    // 0x802C58E8: lw          $v0, 0x18($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X18);
        goto L_802C5A08;
    // 0x802C58E8: lw          $v0, 0x18($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X18);
L_802C58EC:
    // 0x802C58EC: beq         $t4, $zero, L_802C5928
    if (ctx->r12 == 0) {
        // 0x802C58F0: andi        $t9, $v0, 0x400
        ctx->r25 = ctx->r2 & 0X400;
            goto L_802C5928;
    }
    // 0x802C58F0: andi        $t9, $v0, 0x400
    ctx->r25 = ctx->r2 & 0X400;
    // 0x802C58F4: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x802C58F8: addiu       $v0, $v0, -0x562C
    ctx->r2 = ADD32(ctx->r2, -0X562C);
    // 0x802C58FC: lw          $t5, 0x0($v0)
    ctx->r13 = MEM_W(ctx->r2, 0X0);
    // 0x802C5900: addiu       $t8, $zero, 0x6
    ctx->r24 = ADD32(0, 0X6);
    // 0x802C5904: addiu       $a0, $zero, 0x10
    ctx->r4 = ADD32(0, 0X10);
    // 0x802C5908: addiu       $t6, $t5, -0x1
    ctx->r14 = ADD32(ctx->r13, -0X1);
    // 0x802C590C: bgez        $t6, L_802C5918
    if (SIGNED(ctx->r14) >= 0) {
        // 0x802C5910: sw          $t6, 0x0($v0)
        MEM_W(0X0, ctx->r2) = ctx->r14;
            goto L_802C5918;
    }
    // 0x802C5910: sw          $t6, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r14;
    // 0x802C5914: sw          $t8, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r24;
L_802C5918:
    // 0x802C5918: jal         0x800C37F4
    // 0x802C591C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_6;
    // 0x802C591C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_6:
    // 0x802C5920: b           L_802C5A08
    // 0x802C5924: lw          $v0, 0x18($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X18);
        goto L_802C5A08;
    // 0x802C5924: lw          $v0, 0x18($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X18);
L_802C5928:
    // 0x802C5928: beq         $t9, $zero, L_802C5A04
    if (ctx->r25 == 0) {
        // 0x802C592C: lui         $v0, 0x800E
        ctx->r2 = S32(0X800E << 16);
            goto L_802C5A04;
    }
    // 0x802C592C: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x802C5930: addiu       $v0, $v0, -0x562C
    ctx->r2 = ADD32(ctx->r2, -0X562C);
    // 0x802C5934: lw          $t0, 0x0($v0)
    ctx->r8 = MEM_W(ctx->r2, 0X0);
    // 0x802C5938: addiu       $at, $zero, 0x7
    ctx->r1 = ADD32(0, 0X7);
    // 0x802C593C: addiu       $a0, $zero, 0x10
    ctx->r4 = ADD32(0, 0X10);
    // 0x802C5940: addiu       $t1, $t0, 0x1
    ctx->r9 = ADD32(ctx->r8, 0X1);
    // 0x802C5944: bne         $t1, $at, L_802C5950
    if (ctx->r9 != ctx->r1) {
        // 0x802C5948: sw          $t1, 0x0($v0)
        MEM_W(0X0, ctx->r2) = ctx->r9;
            goto L_802C5950;
    }
    // 0x802C5948: sw          $t1, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r9;
    // 0x802C594C: sw          $zero, 0x0($v0)
    MEM_W(0X0, ctx->r2) = 0;
L_802C5950:
    // 0x802C5950: jal         0x800C37F4
    // 0x802C5954: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_7;
    // 0x802C5954: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_7:
    // 0x802C5958: b           L_802C5A08
    // 0x802C595C: lw          $v0, 0x18($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X18);
        goto L_802C5A08;
    // 0x802C595C: lw          $v0, 0x18($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X18);
L_802C5960:
    // 0x802C5960: lh          $t3, -0x75EA($t3)
    ctx->r11 = MEM_H(ctx->r11, -0X75EA);
    // 0x802C5964: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x802C5968: lui         $t4, 0x801D
    ctx->r12 = S32(0X801D << 16);
    // 0x802C596C: bnel        $t3, $at, L_802C5A08
    if (ctx->r11 != ctx->r1) {
        // 0x802C5970: lw          $v0, 0x18($sp)
        ctx->r2 = MEM_W(ctx->r29, 0X18);
            goto L_802C5A08;
    }
    goto skip_0;
    // 0x802C5970: lw          $v0, 0x18($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X18);
    skip_0:
    // 0x802C5974: lw          $t4, -0x19D0($t4)
    ctx->r12 = MEM_W(ctx->r12, -0X19D0);
    // 0x802C5978: addiu       $t5, $t4, -0x3E
    ctx->r13 = ADD32(ctx->r12, -0X3E);
    // 0x802C597C: sltiu       $at, $t5, 0xB
    ctx->r1 = ctx->r13 < 0XB ? 1 : 0;
    // 0x802C5980: beq         $at, $zero, L_802C59FC
    if (ctx->r1 == 0) {
        // 0x802C5984: sll         $t5, $t5, 2
        ctx->r13 = S32(ctx->r13 << 2);
            goto L_802C59FC;
    }
    // 0x802C5984: sll         $t5, $t5, 2
    ctx->r13 = S32(ctx->r13 << 2);
    // 0x802C5988: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C598C: addu        $at, $at, $t5
    gpr jr_addend_802C5994 = ctx->r13;
    ctx->r1 = ADD32(ctx->r1, ctx->r13);
    // 0x802C5990: lw          $t5, 0x5D80($at)
    ctx->r13 = ADD32(ctx->r1, 0X5D80);
    // 0x802C5994: jr          $t5
    // 0x802C5998: nop

    switch (jr_addend_802C5994 >> 2) {
        case 0: goto L_802C599C; break;
        case 1: goto L_802C59FC; break;
        case 2: goto L_802C59DC; break;
        case 3: goto L_802C59FC; break;
        case 4: goto L_802C59AC; break;
        case 5: goto L_802C59FC; break;
        case 6: goto L_802C59BC; break;
        case 7: goto L_802C59FC; break;
        case 8: goto L_802C59CC; break;
        case 9: goto L_802C59FC; break;
        case 10: goto L_802C59EC; break;
        default: switch_error(__func__, 0x802C5994, 0x802C5D80);
    }
    // 0x802C5998: nop

L_802C599C:
    // 0x802C599C: jal         0x801EC3AC
    // 0x802C59A0: nop

    func_801EC3AC(rdram, ctx);
        goto after_8;
    // 0x802C59A0: nop

    after_8:
    // 0x802C59A4: b           L_802C5A08
    // 0x802C59A8: lw          $v0, 0x18($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X18);
        goto L_802C5A08;
    // 0x802C59A8: lw          $v0, 0x18($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X18);
L_802C59AC:
    // 0x802C59AC: jal         0x801EC500
    // 0x802C59B0: nop

    func_801EC500(rdram, ctx);
        goto after_9;
    // 0x802C59B0: nop

    after_9:
    // 0x802C59B4: b           L_802C5A08
    // 0x802C59B8: lw          $v0, 0x18($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X18);
        goto L_802C5A08;
    // 0x802C59B8: lw          $v0, 0x18($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X18);
L_802C59BC:
    // 0x802C59BC: jal         0x801EC5B4
    // 0x802C59C0: nop

    func_801EC5B4(rdram, ctx);
        goto after_10;
    // 0x802C59C0: nop

    after_10:
    // 0x802C59C4: b           L_802C5A08
    // 0x802C59C8: lw          $v0, 0x18($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X18);
        goto L_802C5A08;
    // 0x802C59C8: lw          $v0, 0x18($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X18);
L_802C59CC:
    // 0x802C59CC: jal         0x801EC6EC
    // 0x802C59D0: nop

    func_801EC6EC(rdram, ctx);
        goto after_11;
    // 0x802C59D0: nop

    after_11:
    // 0x802C59D4: b           L_802C5A08
    // 0x802C59D8: lw          $v0, 0x18($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X18);
        goto L_802C5A08;
    // 0x802C59D8: lw          $v0, 0x18($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X18);
L_802C59DC:
    // 0x802C59DC: jal         0x801EC780
    // 0x802C59E0: nop

    func_801EC780(rdram, ctx);
        goto after_12;
    // 0x802C59E0: nop

    after_12:
    // 0x802C59E4: b           L_802C5A08
    // 0x802C59E8: lw          $v0, 0x18($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X18);
        goto L_802C5A08;
    // 0x802C59E8: lw          $v0, 0x18($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X18);
L_802C59EC:
    // 0x802C59EC: jal         0x801EC650
    // 0x802C59F0: nop

    func_801EC650(rdram, ctx);
        goto after_13;
    // 0x802C59F0: nop

    after_13:
    // 0x802C59F4: b           L_802C5A08
    // 0x802C59F8: lw          $v0, 0x18($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X18);
        goto L_802C5A08;
    // 0x802C59F8: lw          $v0, 0x18($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X18);
L_802C59FC:
    // 0x802C59FC: jal         0x801EB180
    // 0x802C5A00: nop

    func_801EB180(rdram, ctx);
        goto after_14;
    // 0x802C5A00: nop

    after_14:
L_802C5A04:
    // 0x802C5A04: lw          $v0, 0x18($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X18);
L_802C5A08:
    // 0x802C5A08: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C5A0C:
    // 0x802C5A0C: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x802C5A10: jr          $ra
    // 0x802C5A14: nop

    return;
    // 0x802C5A14: nop

;}
RECOMP_FUNC void func_i7_802C5A18(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C5A18: addiu       $sp, $sp, -0x58
    ctx->r29 = ADD32(ctx->r29, -0X58);
    // 0x802C5A1C: sw          $s2, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r18;
    // 0x802C5A20: sw          $s0, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r16;
    // 0x802C5A24: sw          $ra, 0x54($sp)
    MEM_W(0X54, ctx->r29) = ctx->r31;
    // 0x802C5A28: sw          $s4, 0x50($sp)
    MEM_W(0X50, ctx->r29) = ctx->r20;
    // 0x802C5A2C: sw          $s3, 0x4C($sp)
    MEM_W(0X4C, ctx->r29) = ctx->r19;
    // 0x802C5A30: sw          $s1, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r17;
    // 0x802C5A34: addiu       $s2, $a0, 0x8
    ctx->r18 = ADD32(ctx->r4, 0X8);
    // 0x802C5A38: lui         $t6, 0x103
    ctx->r14 = S32(0X103 << 16);
    // 0x802C5A3C: lui         $t7, 0x700
    ctx->r15 = S32(0X700 << 16);
    // 0x802C5A40: addiu       $t7, $t7, 0x0
    ctx->r15 = ADD32(ctx->r15, 0X0);
    // 0x802C5A44: ori         $t6, $t6, 0x40
    ctx->r14 = ctx->r14 | 0X40;
    // 0x802C5A48: or          $v1, $s2, $zero
    ctx->r3 = ctx->r18 | 0;
    // 0x802C5A4C: sw          $t6, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r14;
    // 0x802C5A50: sw          $t7, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r15;
    // 0x802C5A54: addiu       $s2, $s2, 0x8
    ctx->r18 = ADD32(ctx->r18, 0X8);
    // 0x802C5A58: lui         $t8, 0x102
    ctx->r24 = S32(0X102 << 16);
    // 0x802C5A5C: lui         $t9, 0x200
    ctx->r25 = S32(0X200 << 16);
    // 0x802C5A60: addiu       $t9, $t9, 0xA40
    ctx->r25 = ADD32(ctx->r25, 0XA40);
    // 0x802C5A64: ori         $t8, $t8, 0x40
    ctx->r24 = ctx->r24 | 0X40;
    // 0x802C5A68: or          $a1, $s2, $zero
    ctx->r5 = ctx->r18 | 0;
    // 0x802C5A6C: sw          $t8, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r24;
    // 0x802C5A70: sw          $t9, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r25;
    // 0x802C5A74: addiu       $s2, $s2, 0x8
    ctx->r18 = ADD32(ctx->r18, 0X8);
    // 0x802C5A78: lui         $t0, 0x107
    ctx->r8 = S32(0X107 << 16);
    // 0x802C5A7C: lui         $a3, 0x600
    ctx->r7 = S32(0X600 << 16);
    // 0x802C5A80: addiu       $t0, $t0, -0xAB0
    ctx->r8 = ADD32(ctx->r8, -0XAB0);
    // 0x802C5A84: or          $a2, $s2, $zero
    ctx->r6 = ctx->r18 | 0;
    // 0x802C5A88: sw          $t0, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r8;
    // 0x802C5A8C: sw          $a3, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r7;
    // 0x802C5A90: lui         $t1, 0x107
    ctx->r9 = S32(0X107 << 16);
    // 0x802C5A94: addiu       $t1, $t1, -0x9D8
    ctx->r9 = ADD32(ctx->r9, -0X9D8);
    // 0x802C5A98: sw          $t1, 0x4($a2)
    MEM_W(0X4, ctx->r6) = ctx->r9;
    // 0x802C5A9C: sw          $a3, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r7;
    // 0x802C5AA0: addiu       $s2, $s2, 0x8
    ctx->r18 = ADD32(ctx->r18, 0X8);
    // 0x802C5AA4: addiu       $s0, $zero, 0x49
    ctx->r16 = ADD32(0, 0X49);
L_802C5AA8:
    // 0x802C5AA8: addiu       $t2, $zero, 0xCC
    ctx->r10 = ADD32(0, 0XCC);
    // 0x802C5AAC: addiu       $t3, $zero, 0x10
    ctx->r11 = ADD32(0, 0X10);
    // 0x802C5AB0: sw          $t3, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r11;
    // 0x802C5AB4: sw          $t2, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r10;
    // 0x802C5AB8: or          $a0, $s2, $zero
    ctx->r4 = ctx->r18 | 0;
    // 0x802C5ABC: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C5AC0: addiu       $a2, $zero, 0x6E
    ctx->r6 = ADD32(0, 0X6E);
    // 0x802C5AC4: jal         0x80094338
    // 0x802C5AC8: or          $a3, $s0, $zero
    ctx->r7 = ctx->r16 | 0;
    func_80094338(rdram, ctx);
        goto after_0;
    // 0x802C5AC8: or          $a3, $s0, $zero
    ctx->r7 = ctx->r16 | 0;
    after_0:
    // 0x802C5ACC: addiu       $s0, $s0, 0x13
    ctx->r16 = ADD32(ctx->r16, 0X13);
    // 0x802C5AD0: slti        $at, $s0, 0xCE
    ctx->r1 = SIGNED(ctx->r16) < 0XCE ? 1 : 0;
    // 0x802C5AD4: bne         $at, $zero, L_802C5AA8
    if (ctx->r1 != 0) {
        // 0x802C5AD8: or          $s2, $v0, $zero
        ctx->r18 = ctx->r2 | 0;
            goto L_802C5AA8;
    }
    // 0x802C5AD8: or          $s2, $v0, $zero
    ctx->r18 = ctx->r2 | 0;
    // 0x802C5ADC: addiu       $t4, $zero, 0xFF
    ctx->r12 = ADD32(0, 0XFF);
    // 0x802C5AE0: addiu       $t5, $zero, 0xFF
    ctx->r13 = ADD32(0, 0XFF);
    // 0x802C5AE4: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C5AE8: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C5AEC: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C5AF0: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C5AF4: addiu       $t0, $zero, 0xFF
    ctx->r8 = ADD32(0, 0XFF);
    // 0x802C5AF8: addiu       $t1, $zero, 0xFF
    ctx->r9 = ADD32(0, 0XFF);
    // 0x802C5AFC: addiu       $t2, $zero, 0xFF
    ctx->r10 = ADD32(0, 0XFF);
    // 0x802C5B00: addiu       $t3, $zero, 0xFF
    ctx->r11 = ADD32(0, 0XFF);
    // 0x802C5B04: sw          $t3, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r11;
    // 0x802C5B08: sw          $t2, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r10;
    // 0x802C5B0C: sw          $t1, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r9;
    // 0x802C5B10: sw          $t0, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r8;
    // 0x802C5B14: sw          $t9, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r25;
    // 0x802C5B18: sw          $t8, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r24;
    // 0x802C5B1C: sw          $t7, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r15;
    // 0x802C5B20: sw          $t6, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r14;
    // 0x802C5B24: sw          $t5, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r13;
    // 0x802C5B28: sw          $t4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r12;
    // 0x802C5B2C: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C5B30: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C5B34: addiu       $a2, $zero, 0xFF
    ctx->r6 = ADD32(0, 0XFF);
    // 0x802C5B38: jal         0x801E946C
    // 0x802C5B3C: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    func_801E946C(rdram, ctx);
        goto after_1;
    // 0x802C5B3C: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    after_1:
    // 0x802C5B40: addiu       $t4, $zero, 0x22
    ctx->r12 = ADD32(0, 0X22);
    // 0x802C5B44: sw          $t4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r12;
    // 0x802C5B48: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C5B4C: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C5B50: addiu       $a2, $zero, 0x5
    ctx->r6 = ADD32(0, 0X5);
    // 0x802C5B54: addiu       $a3, $zero, 0x9F
    ctx->r7 = ADD32(0, 0X9F);
    // 0x802C5B58: jal         0x801E3EE0
    // 0x802C5B5C: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    func_801E3EE0(rdram, ctx);
        goto after_2;
    // 0x802C5B5C: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    after_2:
    // 0x802C5B60: lui         $s0, 0x802C
    ctx->r16 = S32(0X802C << 16);
    // 0x802C5B64: lui         $s3, 0x800E
    ctx->r19 = S32(0X800E << 16);
    // 0x802C5B68: or          $s2, $v0, $zero
    ctx->r18 = ctx->r2 | 0;
    // 0x802C5B6C: addiu       $s3, $s3, -0x562C
    ctx->r19 = ADD32(ctx->r19, -0X562C);
    // 0x802C5B70: addiu       $s0, $s0, 0x5D3C
    ctx->r16 = ADD32(ctx->r16, 0X5D3C);
    // 0x802C5B74: or          $s1, $zero, $zero
    ctx->r17 = 0 | 0;
    // 0x802C5B78: addiu       $s4, $zero, 0x7
    ctx->r20 = ADD32(0, 0X7);
L_802C5B7C:
    // 0x802C5B7C: lw          $t5, 0x0($s3)
    ctx->r13 = MEM_W(ctx->r19, 0X0);
    // 0x802C5B80: sll         $v0, $s1, 2
    ctx->r2 = S32(ctx->r17 << 2);
    // 0x802C5B84: addu        $v0, $v0, $s1
    ctx->r2 = ADD32(ctx->r2, ctx->r17);
    // 0x802C5B88: beq         $s1, $t5, L_802C5BBC
    if (ctx->r17 == ctx->r13) {
        // 0x802C5B8C: sll         $v0, $v0, 2
        ctx->r2 = S32(ctx->r2 << 2);
            goto L_802C5BBC;
    }
    // 0x802C5B8C: sll         $v0, $v0, 2
    ctx->r2 = S32(ctx->r2 << 2);
    // 0x802C5B90: lh          $a3, 0x0($s0)
    ctx->r7 = MEM_H(ctx->r16, 0X0);
    // 0x802C5B94: subu        $v0, $v0, $s1
    ctx->r2 = SUB32(ctx->r2, ctx->r17);
    // 0x802C5B98: addiu       $v0, $v0, 0x4C
    ctx->r2 = ADD32(ctx->r2, 0X4C);
    // 0x802C5B9C: lw          $a2, 0x4($s0)
    ctx->r6 = MEM_W(ctx->r16, 0X4);
    // 0x802C5BA0: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    // 0x802C5BA4: sw          $v0, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r2;
    // 0x802C5BA8: or          $a0, $s2, $zero
    ctx->r4 = ctx->r18 | 0;
    // 0x802C5BAC: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C5BB0: jal         0x801E3EE0
    // 0x802C5BB4: addiu       $a3, $a3, 0xA1
    ctx->r7 = ADD32(ctx->r7, 0XA1);
    func_801E3EE0(rdram, ctx);
        goto after_3;
    // 0x802C5BB4: addiu       $a3, $a3, 0xA1
    ctx->r7 = ADD32(ctx->r7, 0XA1);
    after_3:
    // 0x802C5BB8: or          $s2, $v0, $zero
    ctx->r18 = ctx->r2 | 0;
L_802C5BBC:
    // 0x802C5BBC: addiu       $s1, $s1, 0x1
    ctx->r17 = ADD32(ctx->r17, 0X1);
    // 0x802C5BC0: bne         $s1, $s4, L_802C5B7C
    if (ctx->r17 != ctx->r20) {
        // 0x802C5BC4: addiu       $s0, $s0, 0x8
        ctx->r16 = ADD32(ctx->r16, 0X8);
            goto L_802C5B7C;
    }
    // 0x802C5BC4: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C5BC8: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C5BCC: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C5BD0: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C5BD4: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C5BD8: addiu       $t0, $zero, 0xFF
    ctx->r8 = ADD32(0, 0XFF);
    // 0x802C5BDC: addiu       $t1, $zero, 0xFF
    ctx->r9 = ADD32(0, 0XFF);
    // 0x802C5BE0: addiu       $t2, $zero, 0xFF
    ctx->r10 = ADD32(0, 0XFF);
    // 0x802C5BE4: addiu       $t3, $zero, 0xFF
    ctx->r11 = ADD32(0, 0XFF);
    // 0x802C5BE8: addiu       $t4, $zero, 0xFF
    ctx->r12 = ADD32(0, 0XFF);
    // 0x802C5BEC: addiu       $t5, $zero, 0xFF
    ctx->r13 = ADD32(0, 0XFF);
    // 0x802C5BF0: sw          $t5, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r13;
    // 0x802C5BF4: sw          $t4, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r12;
    // 0x802C5BF8: sw          $t3, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r11;
    // 0x802C5BFC: sw          $t2, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r10;
    // 0x802C5C00: sw          $t1, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r9;
    // 0x802C5C04: sw          $t0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r8;
    // 0x802C5C08: sw          $t9, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r25;
    // 0x802C5C0C: sw          $t8, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r24;
    // 0x802C5C10: sw          $t7, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r15;
    // 0x802C5C14: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x802C5C18: or          $a0, $s2, $zero
    ctx->r4 = ctx->r18 | 0;
    // 0x802C5C1C: addiu       $a1, $zero, 0x6
    ctx->r5 = ADD32(0, 0X6);
    // 0x802C5C20: addiu       $a2, $zero, 0xFF
    ctx->r6 = ADD32(0, 0XFF);
    // 0x802C5C24: jal         0x801E946C
    // 0x802C5C28: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    func_801E946C(rdram, ctx);
        goto after_4;
    // 0x802C5C28: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    after_4:
    // 0x802C5C2C: lw          $v1, 0x0($s3)
    ctx->r3 = MEM_W(ctx->r19, 0X0);
    // 0x802C5C30: lui         $t7, 0x802C
    ctx->r15 = S32(0X802C << 16);
    // 0x802C5C34: addiu       $t7, $t7, 0x5D3C
    ctx->r15 = ADD32(ctx->r15, 0X5D3C);
    // 0x802C5C38: sll         $t8, $v1, 2
    ctx->r24 = S32(ctx->r3 << 2);
    // 0x802C5C3C: sll         $t6, $v1, 3
    ctx->r14 = S32(ctx->r3 << 3);
    // 0x802C5C40: addu        $t8, $t8, $v1
    ctx->r24 = ADD32(ctx->r24, ctx->r3);
    // 0x802C5C44: addu        $s0, $t6, $t7
    ctx->r16 = ADD32(ctx->r14, ctx->r15);
    // 0x802C5C48: sll         $t8, $t8, 2
    ctx->r24 = S32(ctx->r24 << 2);
    // 0x802C5C4C: lh          $a3, 0x0($s0)
    ctx->r7 = MEM_H(ctx->r16, 0X0);
    // 0x802C5C50: subu        $t8, $t8, $v1
    ctx->r24 = SUB32(ctx->r24, ctx->r3);
    // 0x802C5C54: addiu       $t9, $t8, 0x4C
    ctx->r25 = ADD32(ctx->r24, 0X4C);
    // 0x802C5C58: lw          $a2, 0x4($s0)
    ctx->r6 = MEM_W(ctx->r16, 0X4);
    // 0x802C5C5C: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    // 0x802C5C60: sw          $t9, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r25;
    // 0x802C5C64: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C5C68: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C5C6C: jal         0x801E3EE0
    // 0x802C5C70: addiu       $a3, $a3, 0xA1
    ctx->r7 = ADD32(ctx->r7, 0XA1);
    func_801E3EE0(rdram, ctx);
        goto after_5;
    // 0x802C5C70: addiu       $a3, $a3, 0xA1
    ctx->r7 = ADD32(ctx->r7, 0XA1);
    after_5:
    // 0x802C5C74: lw          $ra, 0x54($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X54);
    // 0x802C5C78: lw          $s0, 0x40($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X40);
    // 0x802C5C7C: lw          $s1, 0x44($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X44);
    // 0x802C5C80: lw          $s2, 0x48($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X48);
    // 0x802C5C84: lw          $s3, 0x4C($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X4C);
    // 0x802C5C88: lw          $s4, 0x50($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X50);
    // 0x802C5C8C: jr          $ra
    // 0x802C5C90: addiu       $sp, $sp, 0x58
    ctx->r29 = ADD32(ctx->r29, 0X58);
    return;
    // 0x802C5C90: addiu       $sp, $sp, 0x58
    ctx->r29 = ADD32(ctx->r29, 0X58);
;}
RECOMP_FUNC void func_i7_802C5C94(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C5C94: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x802C5C98: addiu       $v0, $v0, -0x54DC
    ctx->r2 = ADD32(ctx->r2, -0X54DC);
    // 0x802C5C9C: lw          $t6, 0x0($v0)
    ctx->r14 = MEM_W(ctx->r2, 0X0);
    // 0x802C5CA0: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C5CA4: addiu       $t7, $zero, 0x3D
    ctx->r15 = ADD32(0, 0X3D);
    // 0x802C5CA8: sw          $t6, -0x19CC($at)
    MEM_W(-0X19CC, ctx->r1) = ctx->r14;
    // 0x802C5CAC: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C5CB0: sw          $a0, -0x19D0($at)
    MEM_W(-0X19D0, ctx->r1) = ctx->r4;
    // 0x802C5CB4: sw          $t7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r15;
    // 0x802C5CB8: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C5CBC: addiu       $t8, $zero, 0x7
    ctx->r24 = ADD32(0, 0X7);
    // 0x802C5CC0: sw          $t8, -0x19C8($at)
    MEM_W(-0X19C8, ctx->r1) = ctx->r24;
    // 0x802C5CC4: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C5CC8: addiu       $t9, $zero, 0x1
    ctx->r25 = ADD32(0, 0X1);
    // 0x802C5CCC: sw          $t9, -0x19C4($at)
    MEM_W(-0X19C4, ctx->r1) = ctx->r25;
    // 0x802C5CD0: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C5CD4: sw          $zero, -0x19C0($at)
    MEM_W(-0X19C0, ctx->r1) = 0;
    // 0x802C5CD8: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C5CDC: sw          $zero, -0x19BC($at)
    MEM_W(-0X19BC, ctx->r1) = 0;
    // 0x802C5CE0: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x802C5CE4: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x802C5CE8: sw          $zero, -0x54E4($at)
    MEM_W(-0X54E4, ctx->r1) = 0;
    // 0x802C5CEC: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x802C5CF0: lui         $at, 0x800D
    ctx->r1 = S32(0X800D << 16);
    // 0x802C5CF4: addiu       $t0, $zero, 0x2
    ctx->r8 = ADD32(0, 0X2);
    // 0x802C5CF8: sw          $t0, 0x461C($at)
    MEM_W(0X461C, ctx->r1) = ctx->r8;
    // 0x802C5CFC: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    // 0x802C5D00: addiu       $a1, $zero, 0x4
    ctx->r5 = ADD32(0, 0X4);
    // 0x802C5D04: jal         0x801E6FB0
    // 0x802C5D08: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    FadeTransition_SetProps(rdram, ctx);
        goto after_0;
    // 0x802C5D08: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    after_0:
    // 0x802C5D0C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x802C5D10: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x802C5D14: jr          $ra
    // 0x802C5D18: nop

    return;
    // 0x802C5D18: nop

    // 0x802C5D1C: nop

;}
RECOMP_FUNC void func_i8_802C5800(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C5800: addiu       $sp, $sp, -0x1D8
    ctx->r29 = ADD32(ctx->r29, -0X1D8);
    // 0x802C5804: lui         $t6, 0x801D
    ctx->r14 = S32(0X801D << 16);
    // 0x802C5808: lw          $t6, -0x19C4($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X19C4);
    // 0x802C580C: sw          $ra, 0x74($sp)
    MEM_W(0X74, ctx->r29) = ctx->r31;
    // 0x802C5810: sw          $fp, 0x70($sp)
    MEM_W(0X70, ctx->r29) = ctx->r30;
    // 0x802C5814: sw          $s7, 0x6C($sp)
    MEM_W(0X6C, ctx->r29) = ctx->r23;
    // 0x802C5818: sw          $s6, 0x68($sp)
    MEM_W(0X68, ctx->r29) = ctx->r22;
    // 0x802C581C: sw          $s5, 0x64($sp)
    MEM_W(0X64, ctx->r29) = ctx->r21;
    // 0x802C5820: sw          $s4, 0x60($sp)
    MEM_W(0X60, ctx->r29) = ctx->r20;
    // 0x802C5824: sw          $s3, 0x5C($sp)
    MEM_W(0X5C, ctx->r29) = ctx->r19;
    // 0x802C5828: sw          $s2, 0x58($sp)
    MEM_W(0X58, ctx->r29) = ctx->r18;
    // 0x802C582C: sw          $s1, 0x54($sp)
    MEM_W(0X54, ctx->r29) = ctx->r17;
    // 0x802C5830: sw          $s0, 0x50($sp)
    MEM_W(0X50, ctx->r29) = ctx->r16;
    // 0x802C5834: sdc1        $f24, 0x48($sp)
    CHECK_FR(ctx, 24);
    SD(ctx->f24.u64, 0X48, ctx->r29);
    // 0x802C5838: sdc1        $f22, 0x40($sp)
    CHECK_FR(ctx, 22);
    SD(ctx->f22.u64, 0X40, ctx->r29);
    // 0x802C583C: beq         $t6, $zero, L_802C585C
    if (ctx->r14 == 0) {
        // 0x802C5840: sdc1        $f20, 0x38($sp)
        CHECK_FR(ctx, 20);
    SD(ctx->f20.u64, 0X38, ctx->r29);
            goto L_802C585C;
    }
    // 0x802C5840: sdc1        $f20, 0x38($sp)
    CHECK_FR(ctx, 20);
    SD(ctx->f20.u64, 0X38, ctx->r29);
    // 0x802C5844: lui         $t7, 0x800E
    ctx->r15 = S32(0X800E << 16);
    // 0x802C5848: lw          $t7, -0x54DC($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X54DC);
    // 0x802C584C: addiu       $at, $zero, 0x3E
    ctx->r1 = ADD32(0, 0X3E);
    // 0x802C5850: bne         $t7, $at, L_802C585C
    if (ctx->r15 != ctx->r1) {
        // 0x802C5854: lui         $at, 0x801D
        ctx->r1 = S32(0X801D << 16);
            goto L_802C585C;
    }
    // 0x802C5854: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C5858: sw          $zero, -0x19C0($at)
    MEM_W(-0X19C0, ctx->r1) = 0;
L_802C585C:
    // 0x802C585C: lui         $t8, 0x801D
    ctx->r24 = S32(0X801D << 16);
    // 0x802C5860: lw          $t8, -0x19C0($t8)
    ctx->r24 = MEM_W(ctx->r24, -0X19C0);
    // 0x802C5864: lui         $t9, 0x802C
    ctx->r25 = S32(0X802C << 16);
    // 0x802C5868: bne         $t8, $zero, L_802C5930
    if (ctx->r24 != 0) {
        // 0x802C586C: nop
    
            goto L_802C5930;
    }
    // 0x802C586C: nop

    // 0x802C5870: lw          $t9, 0x7040($t9)
    ctx->r25 = MEM_W(ctx->r25, 0X7040);
    // 0x802C5874: lui         $s0, 0x802C
    ctx->r16 = S32(0X802C << 16);
    // 0x802C5878: addiu       $s0, $s0, 0x74F8
    ctx->r16 = ADD32(ctx->r16, 0X74F8);
    // 0x802C587C: sll         $t0, $t9, 2
    ctx->r8 = S32(ctx->r25 << 2);
    // 0x802C5880: addu        $t1, $s0, $t0
    ctx->r9 = ADD32(ctx->r16, ctx->r8);
    // 0x802C5884: lw          $t2, 0x0($t1)
    ctx->r10 = MEM_W(ctx->r9, 0X0);
    // 0x802C5888: addiu       $s1, $zero, 0xE
    ctx->r17 = ADD32(0, 0XE);
    // 0x802C588C: lui         $t4, 0x801D
    ctx->r12 = S32(0X801D << 16);
    // 0x802C5890: multu       $t2, $s1
    result = U64(U32(ctx->r10)) * U64(U32(ctx->r17)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x802C5894: addiu       $t4, $t4, -0x4D68
    ctx->r12 = ADD32(ctx->r12, -0X4D68);
    // 0x802C5898: lui         $a1, 0x802C
    ctx->r5 = S32(0X802C << 16);
    // 0x802C589C: addiu       $a1, $a1, 0x7548
    ctx->r5 = ADD32(ctx->r5, 0X7548);
    // 0x802C58A0: addiu       $a2, $zero, 0xB
    ctx->r6 = ADD32(0, 0XB);
    // 0x802C58A4: mflo        $t3
    ctx->r11 = lo;
    // 0x802C58A8: addu        $a0, $t3, $t4
    ctx->r4 = ADD32(ctx->r11, ctx->r12);
    // 0x802C58AC: jal         0x802C6FD4
    // 0x802C58B0: nop

    func_i8_802C6FD4(rdram, ctx);
        goto after_0;
    // 0x802C58B0: nop

    after_0:
    // 0x802C58B4: lui         $t8, 0x802C
    ctx->r24 = S32(0X802C << 16);
    // 0x802C58B8: lw          $t8, 0x7040($t8)
    ctx->r24 = MEM_W(ctx->r24, 0X7040);
    // 0x802C58BC: lui         $t5, 0x800D
    ctx->r13 = S32(0X800D << 16);
    // 0x802C58C0: lw          $t5, 0x48DC($t5)
    ctx->r13 = MEM_W(ctx->r13, 0X48DC);
    // 0x802C58C4: sll         $t9, $t8, 2
    ctx->r25 = S32(ctx->r24 << 2);
    // 0x802C58C8: addu        $t0, $s0, $t9
    ctx->r8 = ADD32(ctx->r16, ctx->r25);
    // 0x802C58CC: lw          $a0, 0x0($t0)
    ctx->r4 = MEM_W(ctx->r8, 0X0);
    // 0x802C58D0: sll         $t6, $t5, 2
    ctx->r14 = S32(ctx->r13 << 2);
    // 0x802C58D4: subu        $t6, $t6, $t5
    ctx->r14 = SUB32(ctx->r14, ctx->r13);
    // 0x802C58D8: multu       $a0, $s1
    result = U64(U32(ctx->r4)) * U64(U32(ctx->r17)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x802C58DC: sll         $t6, $t6, 3
    ctx->r14 = S32(ctx->r14 << 3);
    // 0x802C58E0: subu        $t6, $t6, $t5
    ctx->r14 = SUB32(ctx->r14, ctx->r13);
    // 0x802C58E4: sll         $t6, $t6, 3
    ctx->r14 = S32(ctx->r14 << 3);
    // 0x802C58E8: lui         $t2, 0x800E
    ctx->r10 = S32(0X800E << 16);
    // 0x802C58EC: addu        $t6, $t6, $t5
    ctx->r14 = ADD32(ctx->r14, ctx->r13);
    // 0x802C58F0: sll         $t6, $t6, 2
    ctx->r14 = S32(ctx->r14 << 2);
    // 0x802C58F4: addiu       $t2, $t2, -0x56B0
    ctx->r10 = ADD32(ctx->r10, -0X56B0);
    // 0x802C58F8: lui         $t7, 0x8019
    ctx->r15 = S32(0X8019 << 16);
    // 0x802C58FC: subu        $t6, $t6, $t5
    ctx->r14 = SUB32(ctx->r14, ctx->r13);
    // 0x802C5900: mflo        $t1
    ctx->r9 = lo;
    // 0x802C5904: addu        $v1, $t1, $t2
    ctx->r3 = ADD32(ctx->r9, ctx->r10);
    // 0x802C5908: sll         $t6, $t6, 3
    ctx->r14 = S32(ctx->r14 << 3);
    // 0x802C590C: addiu       $t7, $t7, 0x2690
    ctx->r15 = ADD32(ctx->r15, 0X2690);
    // 0x802C5910: addu        $v0, $t6, $t7
    ctx->r2 = ADD32(ctx->r14, ctx->r15);
    // 0x802C5914: lb          $t3, 0xB($v1)
    ctx->r11 = MEM_B(ctx->r3, 0XB);
    // 0x802C5918: lb          $t4, 0xC($v1)
    ctx->r12 = MEM_B(ctx->r3, 0XC);
    // 0x802C591C: lb          $t5, 0xD($v1)
    ctx->r13 = MEM_B(ctx->r3, 0XD);
    // 0x802C5920: sw          $a0, 0xB68($v0)
    MEM_W(0XB68, ctx->r2) = ctx->r4;
    // 0x802C5924: sw          $t3, 0xB6C($v0)
    MEM_W(0XB6C, ctx->r2) = ctx->r11;
    // 0x802C5928: sw          $t4, 0xB70($v0)
    MEM_W(0XB70, ctx->r2) = ctx->r12;
    // 0x802C592C: sw          $t5, 0xB74($v0)
    MEM_W(0XB74, ctx->r2) = ctx->r13;
L_802C5930:
    // 0x802C5930: lui         $a1, 0x802C
    ctx->r5 = S32(0X802C << 16);
    // 0x802C5934: addiu       $a1, $a1, 0x7044
    ctx->r5 = ADD32(ctx->r5, 0X7044);
    // 0x802C5938: lw          $v1, 0x0($a1)
    ctx->r3 = MEM_W(ctx->r5, 0X0);
    // 0x802C593C: lui         $s5, 0x802C
    ctx->r21 = S32(0X802C << 16);
    // 0x802C5940: addiu       $s5, $s5, 0x7564
    ctx->r21 = ADD32(ctx->r21, 0X7564);
    // 0x802C5944: bne         $v1, $zero, L_802C5A08
    if (ctx->r3 != 0) {
        // 0x802C5948: lui         $s2, 0x802C
        ctx->r18 = S32(0X802C << 16);
            goto L_802C5A08;
    }
    // 0x802C5948: lui         $s2, 0x802C
    ctx->r18 = S32(0X802C << 16);
    // 0x802C594C: lui         $a0, 0x802C
    ctx->r4 = S32(0X802C << 16);
    // 0x802C5950: addiu       $a0, $a0, 0x7048
    ctx->r4 = ADD32(ctx->r4, 0X7048);
    // 0x802C5954: lw          $v0, 0x0($a0)
    ctx->r2 = MEM_W(ctx->r4, 0X0);
    // 0x802C5958: lui         $at, 0x4080
    ctx->r1 = S32(0X4080 << 16);
    // 0x802C595C: mtc1        $at, $f0
    ctx->f0.u32l = ctx->r1;
    // 0x802C5960: mtc1        $v0, $f4
    ctx->f4.u32l = ctx->r2;
    // 0x802C5964: lui         $at, 0x437F
    ctx->r1 = S32(0X437F << 16);
    // 0x802C5968: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x802C596C: cvt.s.w     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
    // 0x802C5970: addiu       $t7, $zero, 0x1
    ctx->r15 = ADD32(0, 0X1);
    // 0x802C5974: lui         $at, 0x4F00
    ctx->r1 = S32(0X4F00 << 16);
    // 0x802C5978: mul.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = MUL_S(ctx->f6.fl, ctx->f8.fl);
    // 0x802C597C: div.s       $f16, $f10, $f0
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f16.fl = DIV_S(ctx->f10.fl, ctx->f0.fl);
    // 0x802C5980: cfc1        $t6, $FpcCsr
    ctx->r14 = get_cop1_cs();
    // 0x802C5984: ctc1        $t7, $FpcCsr
    set_cop1_cs(ctx->r15);
    // 0x802C5988: nop

    // 0x802C598C: cvt.w.s     $f18, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    ctx->f18.u32l = CVT_W_S(ctx->f16.fl);
    // 0x802C5990: cfc1        $t7, $FpcCsr
    ctx->r15 = get_cop1_cs();
    // 0x802C5994: nop

    // 0x802C5998: andi        $t7, $t7, 0x78
    ctx->r15 = ctx->r15 & 0X78;
    // 0x802C599C: beql        $t7, $zero, L_802C59EC
    if (ctx->r15 == 0) {
        // 0x802C59A0: mfc1        $t7, $f18
        ctx->r15 = (int32_t)ctx->f18.u32l;
            goto L_802C59EC;
    }
    goto skip_0;
    // 0x802C59A0: mfc1        $t7, $f18
    ctx->r15 = (int32_t)ctx->f18.u32l;
    skip_0:
    // 0x802C59A4: mtc1        $at, $f18
    ctx->f18.u32l = ctx->r1;
    // 0x802C59A8: addiu       $t7, $zero, 0x1
    ctx->r15 = ADD32(0, 0X1);
    // 0x802C59AC: sub.s       $f18, $f16, $f18
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f18.fl = ctx->f16.fl - ctx->f18.fl;
    // 0x802C59B0: ctc1        $t7, $FpcCsr
    set_cop1_cs(ctx->r15);
    // 0x802C59B4: nop

    // 0x802C59B8: cvt.w.s     $f18, $f18
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 18);
    ctx->f18.u32l = CVT_W_S(ctx->f18.fl);
    // 0x802C59BC: cfc1        $t7, $FpcCsr
    ctx->r15 = get_cop1_cs();
    // 0x802C59C0: nop

    // 0x802C59C4: andi        $t7, $t7, 0x78
    ctx->r15 = ctx->r15 & 0X78;
    // 0x802C59C8: bne         $t7, $zero, L_802C59E0
    if (ctx->r15 != 0) {
        // 0x802C59CC: nop
    
            goto L_802C59E0;
    }
    // 0x802C59CC: nop

    // 0x802C59D0: mfc1        $t7, $f18
    ctx->r15 = (int32_t)ctx->f18.u32l;
    // 0x802C59D4: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x802C59D8: b           L_802C59F8
    // 0x802C59DC: or          $t7, $t7, $at
    ctx->r15 = ctx->r15 | ctx->r1;
        goto L_802C59F8;
    // 0x802C59DC: or          $t7, $t7, $at
    ctx->r15 = ctx->r15 | ctx->r1;
L_802C59E0:
    // 0x802C59E0: b           L_802C59F8
    // 0x802C59E4: addiu       $t7, $zero, -0x1
    ctx->r15 = ADD32(0, -0X1);
        goto L_802C59F8;
    // 0x802C59E4: addiu       $t7, $zero, -0x1
    ctx->r15 = ADD32(0, -0X1);
    // 0x802C59E8: mfc1        $t7, $f18
    ctx->r15 = (int32_t)ctx->f18.u32l;
L_802C59EC:
    // 0x802C59EC: nop

    // 0x802C59F0: bltz        $t7, L_802C59E0
    if (SIGNED(ctx->r15) < 0) {
        // 0x802C59F4: nop
    
            goto L_802C59E0;
    }
    // 0x802C59F4: nop

L_802C59F8:
    // 0x802C59F8: ctc1        $t6, $FpcCsr
    set_cop1_cs(ctx->r14);
    // 0x802C59FC: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C5A00: b           L_802C5AC4
    // 0x802C5A04: sw          $t7, 0x7534($at)
    MEM_W(0X7534, ctx->r1) = ctx->r15;
        goto L_802C5AC4;
    // 0x802C5A04: sw          $t7, 0x7534($at)
    MEM_W(0X7534, ctx->r1) = ctx->r15;
L_802C5A08:
    // 0x802C5A08: lui         $a0, 0x802C
    ctx->r4 = S32(0X802C << 16);
    // 0x802C5A0C: addiu       $a0, $a0, 0x7048
    ctx->r4 = ADD32(ctx->r4, 0X7048);
    // 0x802C5A10: lw          $v0, 0x0($a0)
    ctx->r2 = MEM_W(ctx->r4, 0X0);
    // 0x802C5A14: lui         $at, 0x4080
    ctx->r1 = S32(0X4080 << 16);
    // 0x802C5A18: mtc1        $at, $f0
    ctx->f0.u32l = ctx->r1;
    // 0x802C5A1C: mtc1        $v0, $f4
    ctx->f4.u32l = ctx->r2;
    // 0x802C5A20: lui         $at, 0x437F
    ctx->r1 = S32(0X437F << 16);
    // 0x802C5A24: mtc1        $at, $f10
    ctx->f10.u32l = ctx->r1;
    // 0x802C5A28: cvt.s.w     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
    // 0x802C5A2C: addiu       $t9, $zero, 0x1
    ctx->r25 = ADD32(0, 0X1);
    // 0x802C5A30: lui         $at, 0x4F00
    ctx->r1 = S32(0X4F00 << 16);
    // 0x802C5A34: sub.s       $f8, $f0, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = ctx->f0.fl - ctx->f6.fl;
    // 0x802C5A38: mul.s       $f16, $f8, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f16.fl = MUL_S(ctx->f8.fl, ctx->f10.fl);
    // 0x802C5A3C: div.s       $f18, $f16, $f0
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f18.fl = DIV_S(ctx->f16.fl, ctx->f0.fl);
    // 0x802C5A40: cfc1        $t8, $FpcCsr
    ctx->r24 = get_cop1_cs();
    // 0x802C5A44: ctc1        $t9, $FpcCsr
    set_cop1_cs(ctx->r25);
    // 0x802C5A48: nop

    // 0x802C5A4C: cvt.w.s     $f4, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    ctx->f4.u32l = CVT_W_S(ctx->f18.fl);
    // 0x802C5A50: cfc1        $t9, $FpcCsr
    ctx->r25 = get_cop1_cs();
    // 0x802C5A54: nop

    // 0x802C5A58: andi        $t9, $t9, 0x78
    ctx->r25 = ctx->r25 & 0X78;
    // 0x802C5A5C: beql        $t9, $zero, L_802C5AAC
    if (ctx->r25 == 0) {
        // 0x802C5A60: mfc1        $t9, $f4
        ctx->r25 = (int32_t)ctx->f4.u32l;
            goto L_802C5AAC;
    }
    goto skip_1;
    // 0x802C5A60: mfc1        $t9, $f4
    ctx->r25 = (int32_t)ctx->f4.u32l;
    skip_1:
    // 0x802C5A64: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x802C5A68: addiu       $t9, $zero, 0x1
    ctx->r25 = ADD32(0, 0X1);
    // 0x802C5A6C: sub.s       $f4, $f18, $f4
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f4.fl = ctx->f18.fl - ctx->f4.fl;
    // 0x802C5A70: ctc1        $t9, $FpcCsr
    set_cop1_cs(ctx->r25);
    // 0x802C5A74: nop

    // 0x802C5A78: cvt.w.s     $f4, $f4
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 4);
    ctx->f4.u32l = CVT_W_S(ctx->f4.fl);
    // 0x802C5A7C: cfc1        $t9, $FpcCsr
    ctx->r25 = get_cop1_cs();
    // 0x802C5A80: nop

    // 0x802C5A84: andi        $t9, $t9, 0x78
    ctx->r25 = ctx->r25 & 0X78;
    // 0x802C5A88: bne         $t9, $zero, L_802C5AA0
    if (ctx->r25 != 0) {
        // 0x802C5A8C: nop
    
            goto L_802C5AA0;
    }
    // 0x802C5A8C: nop

    // 0x802C5A90: mfc1        $t9, $f4
    ctx->r25 = (int32_t)ctx->f4.u32l;
    // 0x802C5A94: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x802C5A98: b           L_802C5AB8
    // 0x802C5A9C: or          $t9, $t9, $at
    ctx->r25 = ctx->r25 | ctx->r1;
        goto L_802C5AB8;
    // 0x802C5A9C: or          $t9, $t9, $at
    ctx->r25 = ctx->r25 | ctx->r1;
L_802C5AA0:
    // 0x802C5AA0: b           L_802C5AB8
    // 0x802C5AA4: addiu       $t9, $zero, -0x1
    ctx->r25 = ADD32(0, -0X1);
        goto L_802C5AB8;
    // 0x802C5AA4: addiu       $t9, $zero, -0x1
    ctx->r25 = ADD32(0, -0X1);
    // 0x802C5AA8: mfc1        $t9, $f4
    ctx->r25 = (int32_t)ctx->f4.u32l;
L_802C5AAC:
    // 0x802C5AAC: nop

    // 0x802C5AB0: bltz        $t9, L_802C5AA0
    if (SIGNED(ctx->r25) < 0) {
        // 0x802C5AB4: nop
    
            goto L_802C5AA0;
    }
    // 0x802C5AB4: nop

L_802C5AB8:
    // 0x802C5AB8: ctc1        $t8, $FpcCsr
    set_cop1_cs(ctx->r24);
    // 0x802C5ABC: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C5AC0: sw          $t9, 0x7534($at)
    MEM_W(0X7534, ctx->r1) = ctx->r25;
L_802C5AC4:
    // 0x802C5AC4: addiu       $t0, $v0, 0x1
    ctx->r8 = ADD32(ctx->r2, 0X1);
    // 0x802C5AC8: slti        $at, $t0, 0x4
    ctx->r1 = SIGNED(ctx->r8) < 0X4 ? 1 : 0;
    // 0x802C5ACC: bne         $at, $zero, L_802C5AE0
    if (ctx->r1 != 0) {
        // 0x802C5AD0: sw          $t0, 0x0($a0)
        MEM_W(0X0, ctx->r4) = ctx->r8;
            goto L_802C5AE0;
    }
    // 0x802C5AD0: sw          $t0, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r8;
    // 0x802C5AD4: xori        $t2, $v1, 0x1
    ctx->r10 = ctx->r3 ^ 0X1;
    // 0x802C5AD8: sw          $zero, 0x0($a0)
    MEM_W(0X0, ctx->r4) = 0;
    // 0x802C5ADC: sw          $t2, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r10;
L_802C5AE0:
    // 0x802C5AE0: lw          $t3, 0x0($s5)
    ctx->r11 = MEM_W(ctx->r21, 0X0);
    // 0x802C5AE4: addiu       $s2, $s2, 0x7568
    ctx->r18 = ADD32(ctx->r18, 0X7568);
    // 0x802C5AE8: sw          $zero, 0x0($s2)
    MEM_W(0X0, ctx->r18) = 0;
    // 0x802C5AEC: blez        $t3, L_802C5B4C
    if (SIGNED(ctx->r11) <= 0) {
        // 0x802C5AF0: or          $s1, $zero, $zero
        ctx->r17 = 0 | 0;
            goto L_802C5B4C;
    }
    // 0x802C5AF0: or          $s1, $zero, $zero
    ctx->r17 = 0 | 0;
    // 0x802C5AF4: lui         $s0, 0x802C
    ctx->r16 = S32(0X802C << 16);
    // 0x802C5AF8: lui         $s4, 0x8022
    ctx->r20 = S32(0X8022 << 16);
    // 0x802C5AFC: addiu       $s4, $s4, 0x6DC4
    ctx->r20 = ADD32(ctx->r20, 0X6DC4);
    // 0x802C5B00: addiu       $s0, $s0, 0x7548
    ctx->r16 = ADD32(ctx->r16, 0X7548);
    // 0x802C5B04: addiu       $s3, $zero, 0xFF
    ctx->r19 = ADD32(0, 0XFF);
L_802C5B08:
    // 0x802C5B08: addiu       $a0, $zero, 0x2
    ctx->r4 = ADD32(0, 0X2);
    // 0x802C5B0C: jal         0x801E9B04
    // 0x802C5B10: lb          $a1, 0x0($s0)
    ctx->r5 = MEM_B(ctx->r16, 0X0);
    func_801E9B04(rdram, ctx);
        goto after_1;
    // 0x802C5B10: lb          $a1, 0x0($s0)
    ctx->r5 = MEM_B(ctx->r16, 0X0);
    after_1:
    // 0x802C5B14: bne         $v0, $s3, L_802C5B24
    if (ctx->r2 != ctx->r19) {
        // 0x802C5B18: addiu       $s1, $s1, 0x1
        ctx->r17 = ADD32(ctx->r17, 0X1);
            goto L_802C5B24;
    }
    // 0x802C5B18: addiu       $s1, $s1, 0x1
    ctx->r17 = ADD32(ctx->r17, 0X1);
    // 0x802C5B1C: b           L_802C5B2C
    // 0x802C5B20: addiu       $v1, $zero, 0xC
    ctx->r3 = ADD32(0, 0XC);
        goto L_802C5B2C;
    // 0x802C5B20: addiu       $v1, $zero, 0xC
    ctx->r3 = ADD32(0, 0XC);
L_802C5B24:
    // 0x802C5B24: addu        $t4, $s4, $v0
    ctx->r12 = ADD32(ctx->r20, ctx->r2);
    // 0x802C5B28: lbu         $v1, 0x0($t4)
    ctx->r3 = MEM_BU(ctx->r12, 0X0);
L_802C5B2C:
    // 0x802C5B2C: lw          $t7, 0x0($s5)
    ctx->r15 = MEM_W(ctx->r21, 0X0);
    // 0x802C5B30: lw          $t5, 0x0($s2)
    ctx->r13 = MEM_W(ctx->r18, 0X0);
    // 0x802C5B34: addiu       $s0, $s0, 0x1
    ctx->r16 = ADD32(ctx->r16, 0X1);
    // 0x802C5B38: slt         $at, $s1, $t7
    ctx->r1 = SIGNED(ctx->r17) < SIGNED(ctx->r15) ? 1 : 0;
    // 0x802C5B3C: addu        $t6, $t5, $v1
    ctx->r14 = ADD32(ctx->r13, ctx->r3);
    // 0x802C5B40: bne         $at, $zero, L_802C5B08
    if (ctx->r1 != 0) {
        // 0x802C5B44: sw          $t6, 0x0($s2)
        MEM_W(0X0, ctx->r18) = ctx->r14;
            goto L_802C5B08;
    }
    // 0x802C5B44: sw          $t6, 0x0($s2)
    MEM_W(0X0, ctx->r18) = ctx->r14;
    // 0x802C5B48: or          $s1, $zero, $zero
    ctx->r17 = 0 | 0;
L_802C5B4C:
    // 0x802C5B4C: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x802C5B50: mtc1        $at, $f24
    ctx->f24.u32l = ctx->r1;
    // 0x802C5B54: lui         $at, 0x4180
    ctx->r1 = S32(0X4180 << 16);
    // 0x802C5B58: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x802C5B5C: mtc1        $zero, $f22
    ctx->f22.u32l = 0;
    // 0x802C5B60: lui         $at, 0x4580
    ctx->r1 = S32(0X4580 << 16);
    // 0x802C5B64: lui         $a0, 0x801D
    ctx->r4 = S32(0X801D << 16);
    // 0x802C5B68: lw          $a0, -0x1A08($a0)
    ctx->r4 = MEM_W(ctx->r4, -0X1A08);
    // 0x802C5B6C: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x802C5B70: lui         $a1, 0x802C
    ctx->r5 = S32(0X802C << 16);
    // 0x802C5B74: mfc1        $a3, $f24
    ctx->r7 = (int32_t)ctx->f24.u32l;
    // 0x802C5B78: addiu       $a1, $a1, 0x7530
    ctx->r5 = ADD32(ctx->r5, 0X7530);
    // 0x802C5B7C: lui         $a2, 0x4204
    ctx->r6 = S32(0X4204 << 16);
    // 0x802C5B80: swc1        $f6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f6.u32l;
    // 0x802C5B84: swc1        $f22, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->f22.u32l;
    // 0x802C5B88: swc1        $f22, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->f22.u32l;
    // 0x802C5B8C: addiu       $a0, $a0, 0xA40
    ctx->r4 = ADD32(ctx->r4, 0XA40);
    // 0x802C5B90: jal         0x800481E0
    // 0x802C5B94: swc1        $f8, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->f8.u32l;
    func_800481E0(rdram, ctx);
        goto after_2;
    // 0x802C5B94: swc1        $f8, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->f8.u32l;
    after_2:
    // 0x802C5B98: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C5B9C: lwc1        $f10, 0x750C($at)
    ctx->f10.u32l = MEM_W(ctx->r1, 0X750C);
    // 0x802C5BA0: mfc1        $a1, $f22
    ctx->r5 = (int32_t)ctx->f22.u32l;
    // 0x802C5BA4: mfc1        $a2, $f22
    ctx->r6 = (int32_t)ctx->f22.u32l;
    // 0x802C5BA8: mfc1        $a3, $f24
    ctx->r7 = (int32_t)ctx->f24.u32l;
    // 0x802C5BAC: addiu       $a0, $sp, 0xC0
    ctx->r4 = ADD32(ctx->r29, 0XC0);
    // 0x802C5BB0: swc1        $f22, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f22.u32l;
    // 0x802C5BB4: swc1        $f24, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->f24.u32l;
    // 0x802C5BB8: swc1        $f22, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->f22.u32l;
    // 0x802C5BBC: swc1        $f22, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->f22.u32l;
    // 0x802C5BC0: swc1        $f22, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->f22.u32l;
    // 0x802C5BC4: swc1        $f22, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->f22.u32l;
    // 0x802C5BC8: jal         0x80048A88
    // 0x802C5BCC: swc1        $f10, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->f10.u32l;
    func_80048A88(rdram, ctx);
        goto after_3;
    // 0x802C5BCC: swc1        $f10, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->f10.u32l;
    after_3:
    // 0x802C5BD0: lui         $at, 0x43FA
    ctx->r1 = S32(0X43FA << 16);
    // 0x802C5BD4: lui         $s6, 0x802C
    ctx->r22 = S32(0X802C << 16);
    // 0x802C5BD8: lui         $s0, 0x8015
    ctx->r16 = S32(0X8015 << 16);
    // 0x802C5BDC: mtc1        $at, $f20
    ctx->f20.u32l = ctx->r1;
    // 0x802C5BE0: addiu       $s0, $s0, 0x4350
    ctx->r16 = ADD32(ctx->r16, 0X4350);
    // 0x802C5BE4: addiu       $s6, $s6, 0x7050
    ctx->r22 = ADD32(ctx->r22, 0X7050);
    // 0x802C5BE8: or          $s2, $zero, $zero
    ctx->r18 = 0 | 0;
    // 0x802C5BEC: addiu       $fp, $zero, 0x4
    ctx->r30 = ADD32(0, 0X4);
    // 0x802C5BF0: addiu       $s7, $sp, 0x80
    ctx->r23 = ADD32(ctx->r29, 0X80);
    // 0x802C5BF4: addiu       $s5, $sp, 0x104
    ctx->r21 = ADD32(ctx->r29, 0X104);
    // 0x802C5BF8: addiu       $s4, $sp, 0x184
    ctx->r20 = ADD32(ctx->r29, 0X184);
    // 0x802C5BFC: addiu       $s3, $sp, 0x144
    ctx->r19 = ADD32(ctx->r29, 0X144);
L_802C5C00:
    // 0x802C5C00: lui         $t8, 0x802C
    ctx->r24 = S32(0X802C << 16);
    // 0x802C5C04: lw          $t8, 0x7040($t8)
    ctx->r24 = MEM_W(ctx->r24, 0X7040);
    // 0x802C5C08: mfc1        $a3, $f20
    ctx->r7 = (int32_t)ctx->f20.u32l;
    // 0x802C5C0C: or          $a0, $s7, $zero
    ctx->r4 = ctx->r23 | 0;
    // 0x802C5C10: bne         $s1, $t8, L_802C5C68
    if (ctx->r17 != ctx->r24) {
        // 0x802C5C14: or          $a1, $s3, $zero
        ctx->r5 = ctx->r19 | 0;
            goto L_802C5C68;
    }
    // 0x802C5C14: or          $a1, $s3, $zero
    ctx->r5 = ctx->r19 | 0;
    // 0x802C5C18: lw          $v0, 0x0($s6)
    ctx->r2 = MEM_W(ctx->r22, 0X0);
    // 0x802C5C1C: bgez        $v0, L_802C5C30
    if (SIGNED(ctx->r2) >= 0) {
        // 0x802C5C20: andi        $t9, $v0, 0xFFF
        ctx->r25 = ctx->r2 & 0XFFF;
            goto L_802C5C30;
    }
    // 0x802C5C20: andi        $t9, $v0, 0xFFF
    ctx->r25 = ctx->r2 & 0XFFF;
    // 0x802C5C24: beq         $t9, $zero, L_802C5C30
    if (ctx->r25 == 0) {
        // 0x802C5C28: nop
    
            goto L_802C5C30;
    }
    // 0x802C5C28: nop

    // 0x802C5C2C: addiu       $t9, $t9, -0x1000
    ctx->r25 = ADD32(ctx->r25, -0X1000);
L_802C5C30:
    // 0x802C5C30: addiu       $t0, $t9, 0x400
    ctx->r8 = ADD32(ctx->r25, 0X400);
    // 0x802C5C34: andi        $t1, $t0, 0xFFF
    ctx->r9 = ctx->r8 & 0XFFF;
    // 0x802C5C38: sll         $t2, $t1, 2
    ctx->r10 = S32(ctx->r9 << 2);
    // 0x802C5C3C: addu        $t3, $s0, $t2
    ctx->r11 = ADD32(ctx->r16, ctx->r10);
    // 0x802C5C40: lwc1        $f16, 0x0($t3)
    ctx->f16.u32l = MEM_W(ctx->r11, 0X0);
    // 0x802C5C44: andi        $t4, $t9, 0xFFF
    ctx->r12 = ctx->r25 & 0XFFF;
    // 0x802C5C48: sll         $t5, $t4, 2
    ctx->r13 = S32(ctx->r12 << 2);
    // 0x802C5C4C: addu        $t6, $s0, $t5
    ctx->r14 = ADD32(ctx->r16, ctx->r13);
    // 0x802C5C50: lwc1        $f18, 0x0($t6)
    ctx->f18.u32l = MEM_W(ctx->r14, 0X0);
    // 0x802C5C54: mul.s       $f0, $f16, $f20
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f0.fl = MUL_S(ctx->f16.fl, ctx->f20.fl);
    // 0x802C5C58: nop

    // 0x802C5C5C: mul.s       $f2, $f18, $f20
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f2.fl = MUL_S(ctx->f18.fl, ctx->f20.fl);
    // 0x802C5C60: b           L_802C5C80
    // 0x802C5C64: nop

        goto L_802C5C80;
    // 0x802C5C64: nop

L_802C5C68:
    // 0x802C5C68: lwc1        $f4, 0x1800($s0)
    ctx->f4.u32l = MEM_W(ctx->r16, 0X1800);
    // 0x802C5C6C: lwc1        $f6, 0x800($s0)
    ctx->f6.u32l = MEM_W(ctx->r16, 0X800);
    // 0x802C5C70: mul.s       $f0, $f4, $f20
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f0.fl = MUL_S(ctx->f4.fl, ctx->f20.fl);
    // 0x802C5C74: nop

    // 0x802C5C78: mul.s       $f2, $f6, $f20
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f2.fl = MUL_S(ctx->f6.fl, ctx->f20.fl);
    // 0x802C5C7C: nop

L_802C5C80:
    // 0x802C5C80: mfc1        $a2, $f0
    ctx->r6 = (int32_t)ctx->f0.u32l;
    // 0x802C5C84: swc1        $f2, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f2.u32l;
    // 0x802C5C88: swc1        $f22, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->f22.u32l;
    // 0x802C5C8C: swc1        $f22, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->f22.u32l;
    // 0x802C5C90: swc1        $f22, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->f22.u32l;
    // 0x802C5C94: swc1        $f22, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->f22.u32l;
    // 0x802C5C98: swc1        $f24, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->f24.u32l;
    // 0x802C5C9C: jal         0x800484C8
    // 0x802C5CA0: swc1        $f22, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->f22.u32l;
    func_800484C8(rdram, ctx);
        goto after_4;
    // 0x802C5CA0: swc1        $f22, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->f22.u32l;
    after_4:
    // 0x802C5CA4: addiu       $a0, $sp, 0xC0
    ctx->r4 = ADD32(ctx->r29, 0XC0);
    // 0x802C5CA8: jal         0x80047E78
    // 0x802C5CAC: or          $a1, $s4, $zero
    ctx->r5 = ctx->r20 | 0;
    SysUtils_MtxToMtxF(rdram, ctx);
        goto after_5;
    // 0x802C5CAC: or          $a1, $s4, $zero
    ctx->r5 = ctx->r20 | 0;
    after_5:
    // 0x802C5CB0: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
    // 0x802C5CB4: or          $a1, $s4, $zero
    ctx->r5 = ctx->r20 | 0;
    // 0x802C5CB8: jal         0x80049EB8
    // 0x802C5CBC: or          $a2, $s5, $zero
    ctx->r6 = ctx->r21 | 0;
    SysUtils_MatrixAffineMultiply(rdram, ctx);
        goto after_6;
    // 0x802C5CBC: or          $a2, $s5, $zero
    ctx->r6 = ctx->r21 | 0;
    after_6:
    // 0x802C5CC0: lui         $t7, 0x801D
    ctx->r15 = S32(0X801D << 16);
    // 0x802C5CC4: lw          $t7, -0x1A08($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X1A08);
    // 0x802C5CC8: or          $a0, $s5, $zero
    ctx->r4 = ctx->r21 | 0;
    // 0x802C5CCC: addu        $a1, $t7, $s2
    ctx->r5 = ADD32(ctx->r15, ctx->r18);
    // 0x802C5CD0: jal         0x80047EE0
    // 0x802C5CD4: addiu       $a1, $a1, 0xA80
    ctx->r5 = ADD32(ctx->r5, 0XA80);
    SysUtils_MtxFToMtx(rdram, ctx);
        goto after_7;
    // 0x802C5CD4: addiu       $a1, $a1, 0xA80
    ctx->r5 = ADD32(ctx->r5, 0XA80);
    after_7:
    // 0x802C5CD8: addiu       $s1, $s1, 0x1
    ctx->r17 = ADD32(ctx->r17, 0X1);
    // 0x802C5CDC: bne         $s1, $fp, L_802C5C00
    if (ctx->r17 != ctx->r30) {
        // 0x802C5CE0: addiu       $s2, $s2, 0x40
        ctx->r18 = ADD32(ctx->r18, 0X40);
            goto L_802C5C00;
    }
    // 0x802C5CE0: addiu       $s2, $s2, 0x40
    ctx->r18 = ADD32(ctx->r18, 0X40);
    // 0x802C5CE4: lw          $t8, 0x0($s6)
    ctx->r24 = MEM_W(ctx->r22, 0X0);
    // 0x802C5CE8: addiu       $t9, $t8, 0x30
    ctx->r25 = ADD32(ctx->r24, 0X30);
    // 0x802C5CEC: slti        $at, $t9, 0x1000
    ctx->r1 = SIGNED(ctx->r25) < 0X1000 ? 1 : 0;
    // 0x802C5CF0: bne         $at, $zero, L_802C5D00
    if (ctx->r1 != 0) {
        // 0x802C5CF4: sw          $t9, 0x0($s6)
        MEM_W(0X0, ctx->r22) = ctx->r25;
            goto L_802C5D00;
    }
    // 0x802C5CF4: sw          $t9, 0x0($s6)
    MEM_W(0X0, ctx->r22) = ctx->r25;
    // 0x802C5CF8: addiu       $t0, $t9, -0x1000
    ctx->r8 = ADD32(ctx->r25, -0X1000);
    // 0x802C5CFC: sw          $t0, 0x0($s6)
    MEM_W(0X0, ctx->r22) = ctx->r8;
L_802C5D00:
    // 0x802C5D00: lw          $ra, 0x74($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X74);
    // 0x802C5D04: ldc1        $f20, 0x38($sp)
    CHECK_FR(ctx, 20);
    ctx->f20.u64 = LD(ctx->r29, 0X38);
    // 0x802C5D08: ldc1        $f22, 0x40($sp)
    CHECK_FR(ctx, 22);
    ctx->f22.u64 = LD(ctx->r29, 0X40);
    // 0x802C5D0C: ldc1        $f24, 0x48($sp)
    CHECK_FR(ctx, 24);
    ctx->f24.u64 = LD(ctx->r29, 0X48);
    // 0x802C5D10: lw          $s0, 0x50($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X50);
    // 0x802C5D14: lw          $s1, 0x54($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X54);
    // 0x802C5D18: lw          $s2, 0x58($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X58);
    // 0x802C5D1C: lw          $s3, 0x5C($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X5C);
    // 0x802C5D20: lw          $s4, 0x60($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X60);
    // 0x802C5D24: lw          $s5, 0x64($sp)
    ctx->r21 = MEM_W(ctx->r29, 0X64);
    // 0x802C5D28: lw          $s6, 0x68($sp)
    ctx->r22 = MEM_W(ctx->r29, 0X68);
    // 0x802C5D2C: lw          $s7, 0x6C($sp)
    ctx->r23 = MEM_W(ctx->r29, 0X6C);
    // 0x802C5D30: lw          $fp, 0x70($sp)
    ctx->r30 = MEM_W(ctx->r29, 0X70);
    // 0x802C5D34: jr          $ra
    // 0x802C5D38: addiu       $sp, $sp, 0x1D8
    ctx->r29 = ADD32(ctx->r29, 0X1D8);
    return;
    // 0x802C5D38: addiu       $sp, $sp, 0x1D8
    ctx->r29 = ADD32(ctx->r29, 0X1D8);
;}
RECOMP_FUNC void func_i8_802C5D3C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C5D3C: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x802C5D40: addiu       $v0, $v0, -0x19C4
    ctx->r2 = ADD32(ctx->r2, -0X19C4);
    // 0x802C5D44: lw          $t6, 0x0($v0)
    ctx->r14 = MEM_W(ctx->r2, 0X0);
    // 0x802C5D48: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x802C5D4C: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x802C5D50: beq         $t6, $zero, L_802C5D7C
    if (ctx->r14 == 0) {
        // 0x802C5D54: lui         $t7, 0x800E
        ctx->r15 = S32(0X800E << 16);
            goto L_802C5D7C;
    }
    // 0x802C5D54: lui         $t7, 0x800E
    ctx->r15 = S32(0X800E << 16);
    // 0x802C5D58: sw          $zero, 0x0($v0)
    MEM_W(0X0, ctx->r2) = 0;
    // 0x802C5D5C: lw          $t7, -0x54DC($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X54DC);
    // 0x802C5D60: addiu       $at, $zero, 0x3E
    ctx->r1 = ADD32(0, 0X3E);
    // 0x802C5D64: bne         $t7, $at, L_802C5D7C
    if (ctx->r15 != ctx->r1) {
        // 0x802C5D68: nop
    
            goto L_802C5D7C;
    }
    // 0x802C5D68: nop

    // 0x802C5D6C: jal         0x80093C44
    // 0x802C5D70: nop

    func_80093C44(rdram, ctx);
        goto after_0;
    // 0x802C5D70: nop

    after_0:
    // 0x802C5D74: b           L_802C5EAC
    // 0x802C5D78: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_802C5EAC;
    // 0x802C5D78: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C5D7C:
    { extern void wr64_change_name_preview_prepare(uint8_t*, uint32_t); wr64_change_name_preview_prepare(rdram, (uint32_t)ctx->r4); }
    // 0x802C5D7C: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x802C5D80: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x802C5D84: sw          $zero, -0x54D4($at)
    MEM_W(-0X54D4, ctx->r1) = 0;
    // 0x802C5D88: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C5D8C: lui         $t8, 0xE700
    ctx->r24 = S32(0XE700 << 16);
    // 0x802C5D90: or          $v1, $a0, $zero
    ctx->r3 = ctx->r4 | 0;
    // 0x802C5D94: sw          $t8, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r24;
    // 0x802C5D98: sw          $zero, 0x4($v0)
    MEM_W(0X4, ctx->r2) = 0;
    // 0x802C5D9C: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C5DA0: lui         $t9, 0xED02
    ctx->r25 = S32(0XED02 << 16);
    // 0x802C5DA4: addiu       $t9, $t9, 0x50
    ctx->r25 = ADD32(ctx->r25, 0X50);
    // 0x802C5DA8: lui         $t0, 0x68
    ctx->r8 = S32(0X68 << 16);
    // 0x802C5DAC: addiu       $t0, $t0, -0x3C94
    ctx->r8 = ADD32(ctx->r8, -0X3C94);
    // 0x802C5DB0: or          $a1, $a0, $zero
    ctx->r5 = ctx->r4 | 0;
    { extern uint32_t wr64_experimental_viewport_borders(void); if (wr64_experimental_viewport_borders()) { ctx->r25 = 0xED000000U; ctx->r8 = 0x006A03C0U; } }
    // 0x802C5DB4: sw          $t9, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r25;
    // 0x802C5DB8: sw          $t0, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r8;
    // 0x802C5DBC: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C5DC0: lui         $t1, 0x103
    ctx->r9 = S32(0X103 << 16);
    // 0x802C5DC4: lui         $t2, 0x700
    ctx->r10 = S32(0X700 << 16);
    // 0x802C5DC8: addiu       $t2, $t2, 0x0
    ctx->r10 = ADD32(ctx->r10, 0X0);
    // 0x802C5DCC: ori         $t1, $t1, 0x40
    ctx->r9 = ctx->r9 | 0X40;
    // 0x802C5DD0: or          $a2, $a0, $zero
    ctx->r6 = ctx->r4 | 0;
    // 0x802C5DD4: sw          $t1, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r9;
    // 0x802C5DD8: sw          $t2, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r10;
    // 0x802C5DDC: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C5DE0: lui         $t3, 0x102
    ctx->r11 = S32(0X102 << 16);
    // 0x802C5DE4: lui         $t4, 0x200
    ctx->r12 = S32(0X200 << 16);
    // 0x802C5DE8: addiu       $t4, $t4, 0xA40
    ctx->r12 = ADD32(ctx->r12, 0XA40);
    // 0x802C5DEC: ori         $t3, $t3, 0x40
    ctx->r11 = ctx->r11 | 0X40;
    // 0x802C5DF0: or          $a3, $a0, $zero
    ctx->r7 = ctx->r4 | 0;
    // 0x802C5DF4: lui         $t6, 0x107
    ctx->r14 = S32(0X107 << 16);
    // 0x802C5DF8: sw          $t3, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r11;
    // 0x802C5DFC: sw          $t4, 0x4($a2)
    MEM_W(0X4, ctx->r6) = ctx->r12;
    // 0x802C5E00: addiu       $t6, $t6, -0xAB0
    ctx->r14 = ADD32(ctx->r14, -0XAB0);
    // 0x802C5E04: lui         $t5, 0x600
    ctx->r13 = S32(0X600 << 16);
    // 0x802C5E08: sw          $t5, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r13;
    // 0x802C5E0C: sw          $t6, 0x4($a3)
    MEM_W(0X4, ctx->r7) = ctx->r14;
    // 0x802C5E10: jal         0x8009328C
    // 0x802C5E14: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    func_8009328C(rdram, ctx);
        goto after_1;
    // 0x802C5E14: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    after_1:
    // 0x802C5E18: lui         $t7, 0xE700
    ctx->r15 = S32(0XE700 << 16);
    // 0x802C5E1C: lui         $t8, 0xED02
    ctx->r24 = S32(0XED02 << 16);
    // 0x802C5E20: addiu       $t8, $t8, 0x50
    ctx->r24 = ADD32(ctx->r24, 0X50);
    // 0x802C5E24: lui         $t9, 0x68
    ctx->r25 = S32(0X68 << 16);
    // 0x802C5E28: addiu       $t9, $t9, -0x3C94
    ctx->r25 = ADD32(ctx->r25, -0X3C94);
    // 0x802C5E2C: sw          $t7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r15;
    // 0x802C5E30: sw          $zero, 0x4($v0)
    MEM_W(0X4, ctx->r2) = 0;
    { extern uint32_t wr64_experimental_viewport_borders(void); if (wr64_experimental_viewport_borders()) { ctx->r24 = 0xED000000U; ctx->r25 = 0x006A03C0U; } }
    // 0x802C5E34: sw          $t8, 0x8($v0)
    MEM_W(0X8, ctx->r2) = ctx->r24;
    // 0x802C5E38: sw          $t9, 0xC($v0)
    MEM_W(0XC, ctx->r2) = ctx->r25;
    // 0x802C5E3C: jal         0x802C63E4
    // 0x802C5E40: addiu       $a0, $v0, 0x10
    ctx->r4 = ADD32(ctx->r2, 0X10);
    func_i8_802C63E4(rdram, ctx);
        goto after_2;
    // 0x802C5E40: addiu       $a0, $v0, 0x10
    ctx->r4 = ADD32(ctx->r2, 0X10);
    after_2:
    // 0x802C5E44: lui         $t1, 0x806
    ctx->r9 = S32(0X806 << 16);
    // 0x802C5E48: addiu       $t1, $t1, 0x2290
    ctx->r9 = ADD32(ctx->r9, 0X2290);
    // 0x802C5E4C: lui         $t0, 0x600
    ctx->r8 = S32(0X600 << 16);
    // 0x802C5E50: sw          $t0, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r8;
    // 0x802C5E54: sw          $t1, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r9;
    { extern uint32_t wr64_watercraft_preview_coverage(uint8_t*, uint32_t); ctx->r2 = S32(wr64_watercraft_preview_coverage(rdram, (uint32_t)ctx->r2)); }
    // 0x802C5E58: lui         $t2, 0x800E
    ctx->r10 = S32(0X800E << 16);
    // 0x802C5E5C: lw          $t2, -0x54DC($t2)
    ctx->r10 = MEM_W(ctx->r10, -0X54DC);
    // 0x802C5E60: addiu       $at, $zero, 0x3E
    ctx->r1 = ADD32(0, 0X3E);
    // 0x802C5E64: addiu       $a0, $v0, 0x8
    ctx->r4 = ADD32(ctx->r2, 0X8);
    // 0x802C5E68: bne         $t2, $at, L_802C5E80
    if (ctx->r10 != ctx->r1) {
        // 0x802C5E6C: lui         $t3, 0x8023
        ctx->r11 = S32(0X8023 << 16);
            goto L_802C5E80;
    }
    // 0x802C5E6C: lui         $t3, 0x8023
    ctx->r11 = S32(0X8023 << 16);
    // 0x802C5E70: jal         0x802C5EB8
    // 0x802C5E74: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    func_i8_802C5EB8(rdram, ctx);
        goto after_3;
    // 0x802C5E74: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    after_3:
    // 0x802C5E78: b           L_802C5EA4
    // 0x802C5E7C: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
        goto L_802C5EA4;
    // 0x802C5E7C: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
L_802C5E80:
    // 0x802C5E80: lh          $t3, -0x75EA($t3)
    ctx->r11 = MEM_H(ctx->r11, -0X75EA);
    // 0x802C5E84: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x802C5E88: bnel        $t3, $at, L_802C5EA8
    if (ctx->r11 != ctx->r1) {
        // 0x802C5E8C: or          $v0, $a0, $zero
        ctx->r2 = ctx->r4 | 0;
            goto L_802C5EA8;
    }
    goto skip_0;
    // 0x802C5E8C: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    skip_0:
    // 0x802C5E90: jal         0x8007C31C
    // 0x802C5E94: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    func_8007C31C(rdram, ctx);
        goto after_4;
    // 0x802C5E94: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    after_4:
    // 0x802C5E98: jal         0x801EC304
    // 0x802C5E9C: nop

    func_801EC304(rdram, ctx);
        goto after_5;
    // 0x802C5E9C: nop

    after_5:
    // 0x802C5EA0: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
L_802C5EA4:
    // 0x802C5EA4: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
L_802C5EA8:
    // 0x802C5EA8: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C5EAC:
    { extern void wr64_watercraft_preview_finish(uint8_t*, uint32_t); wr64_watercraft_preview_finish(rdram, (uint32_t)ctx->r2); }
    // 0x802C5EAC: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x802C5EB0: jr          $ra
    // 0x802C5EB4: nop

    return;
    // 0x802C5EB4: nop

;}
RECOMP_FUNC void func_i8_802C5EB8(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C5EB8: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x802C5EBC: lhu         $v1, -0x19A6($v1)
    ctx->r3 = MEM_HU(ctx->r3, -0X19A6);
    // 0x802C5EC0: addiu       $sp, $sp, -0x28
    ctx->r29 = ADD32(ctx->r29, -0X28);
    // 0x802C5EC4: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x802C5EC8: andi        $t6, $v1, 0xB000
    ctx->r14 = ctx->r3 & 0XB000;
    // 0x802C5ECC: beq         $t6, $zero, L_802C5F98
    if (ctx->r14 == 0) {
        // 0x802C5ED0: or          $t2, $zero, $zero
        ctx->r10 = 0 | 0;
            goto L_802C5F98;
    }
    // 0x802C5ED0: or          $t2, $zero, $zero
    ctx->r10 = 0 | 0;
    // 0x802C5ED4: lui         $a1, 0x801D
    ctx->r5 = S32(0X801D << 16);
    // 0x802C5ED8: addiu       $a1, $a1, -0x19C0
    ctx->r5 = ADD32(ctx->r5, -0X19C0);
    // 0x802C5EDC: lw          $v0, 0x0($a1)
    ctx->r2 = MEM_W(ctx->r5, 0X0);
    // 0x802C5EE0: lui         $a0, 0x802C
    ctx->r4 = S32(0X802C << 16);
    // 0x802C5EE4: addiu       $a0, $a0, 0x7538
    ctx->r4 = ADD32(ctx->r4, 0X7538);
    // 0x802C5EE8: beq         $v0, $zero, L_802C5F04
    if (ctx->r2 == 0) {
        // 0x802C5EEC: addiu       $t7, $zero, 0x1
        ctx->r15 = ADD32(0, 0X1);
            goto L_802C5F04;
    }
    // 0x802C5EEC: addiu       $t7, $zero, 0x1
    ctx->r15 = ADD32(0, 0X1);
    // 0x802C5EF0: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x802C5EF4: beq         $v0, $at, L_802C5F2C
    if (ctx->r2 == ctx->r1) {
        // 0x802C5EF8: andi        $t9, $v1, 0xA000
        ctx->r25 = ctx->r3 & 0XA000;
            goto L_802C5F2C;
    }
    // 0x802C5EF8: andi        $t9, $v1, 0xA000
    ctx->r25 = ctx->r3 & 0XA000;
    // 0x802C5EFC: b           L_802C5F80
    // 0x802C5F00: nop

        goto L_802C5F80;
    // 0x802C5F00: nop

L_802C5F04:
    // 0x802C5F04: lui         $v0, 0x802C
    ctx->r2 = S32(0X802C << 16);
    // 0x802C5F08: addiu       $v0, $v0, 0x753C
    ctx->r2 = ADD32(ctx->r2, 0X753C);
    // 0x802C5F0C: addiu       $t2, $zero, 0x1
    ctx->r10 = ADD32(0, 0X1);
    // 0x802C5F10: sw          $t7, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r15;
    // 0x802C5F14: sw          $zero, 0x0($v0)
    MEM_W(0X0, ctx->r2) = 0;
    // 0x802C5F18: sw          $zero, 0x0($a0)
    MEM_W(0X0, ctx->r4) = 0;
    // 0x802C5F1C: jal         0x802C6D58
    // 0x802C5F20: sw          $t2, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r10;
    func_i8_802C6D58(rdram, ctx);
        goto after_0;
    // 0x802C5F20: sw          $t2, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r10;
    after_0:
    // 0x802C5F24: b           L_802C5F80
    // 0x802C5F28: lw          $t2, 0x1C($sp)
    ctx->r10 = MEM_W(ctx->r29, 0X1C);
        goto L_802C5F80;
    // 0x802C5F28: lw          $t2, 0x1C($sp)
    ctx->r10 = MEM_W(ctx->r29, 0X1C);
L_802C5F2C:
    // 0x802C5F2C: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C5F30: addiu       $t2, $zero, 0x1
    ctx->r10 = ADD32(0, 0X1);
    // 0x802C5F34: beq         $t9, $zero, L_802C5F4C
    if (ctx->r25 == 0) {
        // 0x802C5F38: sw          $zero, 0x756C($at)
        MEM_W(0X756C, ctx->r1) = 0;
            goto L_802C5F4C;
    }
    // 0x802C5F38: sw          $zero, 0x756C($at)
    MEM_W(0X756C, ctx->r1) = 0;
    // 0x802C5F3C: jal         0x802C6ADC
    // 0x802C5F40: sw          $t2, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r10;
    func_i8_802C6ADC(rdram, ctx);
        goto after_1;
    // 0x802C5F40: sw          $t2, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r10;
    after_1:
    // 0x802C5F44: b           L_802C5F64
    // 0x802C5F48: lw          $t2, 0x1C($sp)
    ctx->r10 = MEM_W(ctx->r29, 0X1C);
        goto L_802C5F64;
    // 0x802C5F48: lw          $t2, 0x1C($sp)
    ctx->r10 = MEM_W(ctx->r29, 0X1C);
L_802C5F4C:
    // 0x802C5F4C: andi        $t4, $v1, 0x1000
    ctx->r12 = ctx->r3 & 0X1000;
    // 0x802C5F50: beq         $t4, $zero, L_802C5F64
    if (ctx->r12 == 0) {
        // 0x802C5F54: nop
    
            goto L_802C5F64;
    }
    // 0x802C5F54: nop

    // 0x802C5F58: jal         0x802C6E00
    // 0x802C5F5C: sw          $t2, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r10;
    func_i8_802C6E00(rdram, ctx);
        goto after_2;
    // 0x802C5F5C: sw          $t2, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r10;
    after_2:
    // 0x802C5F60: lw          $t2, 0x1C($sp)
    ctx->r10 = MEM_W(ctx->r29, 0X1C);
L_802C5F64:
    // 0x802C5F64: lui         $t5, 0x802C
    ctx->r13 = S32(0X802C << 16);
    // 0x802C5F68: lw          $t5, 0x756C($t5)
    ctx->r13 = MEM_W(ctx->r13, 0X756C);
    // 0x802C5F6C: beq         $t5, $zero, L_802C5F80
    if (ctx->r13 == 0) {
        // 0x802C5F70: nop
    
            goto L_802C5F80;
    }
    // 0x802C5F70: nop

    // 0x802C5F74: jal         0x802C6F4C
    // 0x802C5F78: sw          $t2, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r10;
    func_i8_802C6F4C(rdram, ctx);
        goto after_3;
    // 0x802C5F78: sw          $t2, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r10;
    after_3:
    // 0x802C5F7C: lw          $t2, 0x1C($sp)
    ctx->r10 = MEM_W(ctx->r29, 0X1C);
L_802C5F80:
    // 0x802C5F80: beq         $t2, $zero, L_802C63D4
    if (ctx->r10 == 0) {
        // 0x802C5F84: addiu       $a0, $zero, 0x11
        ctx->r4 = ADD32(0, 0X11);
            goto L_802C63D4;
    }
    // 0x802C5F84: addiu       $a0, $zero, 0x11
    ctx->r4 = ADD32(0, 0X11);
    // 0x802C5F88: jal         0x800C37F4
    // 0x802C5F8C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_4;
    // 0x802C5F8C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_4:
    // 0x802C5F90: b           L_802C63D8
    // 0x802C5F94: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_802C63D8;
    // 0x802C5F94: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C5F98:
    // 0x802C5F98: andi        $t6, $v1, 0x4000
    ctx->r14 = ctx->r3 & 0X4000;
    // 0x802C5F9C: beq         $t6, $zero, L_802C6008
    if (ctx->r14 == 0) {
        // 0x802C5FA0: andi        $t7, $v1, 0x800
        ctx->r15 = ctx->r3 & 0X800;
            goto L_802C6008;
    }
    // 0x802C5FA0: andi        $t7, $v1, 0x800
    ctx->r15 = ctx->r3 & 0X800;
    // 0x802C5FA4: lui         $a1, 0x801D
    ctx->r5 = S32(0X801D << 16);
    // 0x802C5FA8: addiu       $a1, $a1, -0x19C0
    ctx->r5 = ADD32(ctx->r5, -0X19C0);
    // 0x802C5FAC: lw          $v0, 0x0($a1)
    ctx->r2 = MEM_W(ctx->r5, 0X0);
    // 0x802C5FB0: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x802C5FB4: beql        $v0, $zero, L_802C5FD0
    if (ctx->r2 == 0) {
        // 0x802C5FB8: addiu       $t2, $zero, 0x1
        ctx->r10 = ADD32(0, 0X1);
            goto L_802C5FD0;
    }
    goto skip_0;
    // 0x802C5FB8: addiu       $t2, $zero, 0x1
    ctx->r10 = ADD32(0, 0X1);
    skip_0:
    // 0x802C5FBC: beql        $v0, $at, L_802C5FE4
    if (ctx->r2 == ctx->r1) {
        // 0x802C5FC0: addiu       $t2, $zero, 0x1
        ctx->r10 = ADD32(0, 0X1);
            goto L_802C5FE4;
    }
    goto skip_1;
    // 0x802C5FC0: addiu       $t2, $zero, 0x1
    ctx->r10 = ADD32(0, 0X1);
    skip_1:
    // 0x802C5FC4: b           L_802C5FF0
    // 0x802C5FC8: nop

        goto L_802C5FF0;
    // 0x802C5FC8: nop

    // 0x802C5FCC: addiu       $t2, $zero, 0x1
    ctx->r10 = ADD32(0, 0X1);
L_802C5FD0:
    // 0x802C5FD0: jal         0x802C6F4C
    // 0x802C5FD4: sw          $t2, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r10;
    func_i8_802C6F4C(rdram, ctx);
        goto after_5;
    // 0x802C5FD4: sw          $t2, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r10;
    after_5:
    // 0x802C5FD8: b           L_802C5FF0
    // 0x802C5FDC: lw          $t2, 0x1C($sp)
    ctx->r10 = MEM_W(ctx->r29, 0X1C);
        goto L_802C5FF0;
    // 0x802C5FDC: lw          $t2, 0x1C($sp)
    ctx->r10 = MEM_W(ctx->r29, 0X1C);
    // 0x802C5FE0: addiu       $t2, $zero, 0x1
    ctx->r10 = ADD32(0, 0X1);
L_802C5FE4:
    // 0x802C5FE4: jal         0x802C6DA8
    // 0x802C5FE8: sw          $t2, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r10;
    func_i8_802C6DA8(rdram, ctx);
        goto after_6;
    // 0x802C5FE8: sw          $t2, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r10;
    after_6:
    // 0x802C5FEC: lw          $t2, 0x1C($sp)
    ctx->r10 = MEM_W(ctx->r29, 0X1C);
L_802C5FF0:
    // 0x802C5FF0: beq         $t2, $zero, L_802C63D4
    if (ctx->r10 == 0) {
        // 0x802C5FF4: addiu       $a0, $zero, 0x16
        ctx->r4 = ADD32(0, 0X16);
            goto L_802C63D4;
    }
    // 0x802C5FF4: addiu       $a0, $zero, 0x16
    ctx->r4 = ADD32(0, 0X16);
    // 0x802C5FF8: jal         0x800C37F4
    // 0x802C5FFC: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_7;
    // 0x802C5FFC: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_7:
    // 0x802C6000: b           L_802C63D8
    // 0x802C6004: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_802C63D8;
    // 0x802C6004: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C6008:
    // 0x802C6008: beq         $t7, $zero, L_802C60F0
    if (ctx->r15 == 0) {
        // 0x802C600C: andi        $t4, $v1, 0x400
        ctx->r12 = ctx->r3 & 0X400;
            goto L_802C60F0;
    }
    // 0x802C600C: andi        $t4, $v1, 0x400
    ctx->r12 = ctx->r3 & 0X400;
    // 0x802C6010: lui         $a1, 0x801D
    ctx->r5 = S32(0X801D << 16);
    // 0x802C6014: addiu       $a1, $a1, -0x19C0
    ctx->r5 = ADD32(ctx->r5, -0X19C0);
    // 0x802C6018: lw          $t8, 0x0($a1)
    ctx->r24 = MEM_W(ctx->r5, 0X0);
    // 0x802C601C: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x802C6020: lui         $v0, 0x802C
    ctx->r2 = S32(0X802C << 16);
    // 0x802C6024: bne         $t8, $at, L_802C60D8
    if (ctx->r24 != ctx->r1) {
        // 0x802C6028: addiu       $v0, $v0, 0x753C
        ctx->r2 = ADD32(ctx->r2, 0X753C);
            goto L_802C60D8;
    }
    // 0x802C6028: addiu       $v0, $v0, 0x753C
    ctx->r2 = ADD32(ctx->r2, 0X753C);
    // 0x802C602C: lw          $t0, 0x0($v0)
    ctx->r8 = MEM_W(ctx->r2, 0X0);
    // 0x802C6030: lui         $t3, 0x802C
    ctx->r11 = S32(0X802C << 16);
    // 0x802C6034: addiu       $t3, $t3, 0x7540
    ctx->r11 = ADD32(ctx->r11, 0X7540);
    // 0x802C6038: addiu       $t9, $t0, -0x1
    ctx->r25 = ADD32(ctx->r8, -0X1);
    // 0x802C603C: sw          $t0, 0x0($t3)
    MEM_W(0X0, ctx->r11) = ctx->r8;
    // 0x802C6040: addiu       $t2, $zero, 0x1
    ctx->r10 = ADD32(0, 0X1);
    // 0x802C6044: sw          $t9, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r25;
    // 0x802C6048: bgez        $t9, L_802C6058
    if (SIGNED(ctx->r25) >= 0) {
        // 0x802C604C: or          $t0, $t9, $zero
        ctx->r8 = ctx->r25 | 0;
            goto L_802C6058;
    }
    // 0x802C604C: or          $t0, $t9, $zero
    ctx->r8 = ctx->r25 | 0;
    // 0x802C6050: addiu       $t0, $zero, 0x5
    ctx->r8 = ADD32(0, 0X5);
    // 0x802C6054: sw          $t0, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r8;
L_802C6058:
    // 0x802C6058: sll         $a3, $t0, 3
    ctx->r7 = S32(ctx->r8 << 3);
    // 0x802C605C: lui         $a1, 0x802C
    ctx->r5 = S32(0X802C << 16);
    // 0x802C6060: lui         $a0, 0x802C
    ctx->r4 = S32(0X802C << 16);
    // 0x802C6064: addiu       $a0, $a0, 0x7538
    ctx->r4 = ADD32(ctx->r4, 0X7538);
    // 0x802C6068: addiu       $a1, $a1, 0x7054
    ctx->r5 = ADD32(ctx->r5, 0X7054);
    // 0x802C606C: subu        $a3, $a3, $t0
    ctx->r7 = SUB32(ctx->r7, ctx->r8);
    // 0x802C6070: addiu       $a2, $zero, 0x1C
    ctx->r6 = ADD32(0, 0X1C);
L_802C6074:
    // 0x802C6074: lw          $v1, 0x0($a0)
    ctx->r3 = MEM_W(ctx->r4, 0X0);
    // 0x802C6078: addu        $v0, $a3, $v1
    ctx->r2 = ADD32(ctx->r7, ctx->r3);
    // 0x802C607C: multu       $v0, $a2
    result = U64(U32(ctx->r2)) * U64(U32(ctx->r6)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x802C6080: addiu       $t8, $v1, -0x1
    ctx->r24 = ADD32(ctx->r3, -0X1);
    // 0x802C6084: mflo        $t4
    ctx->r12 = lo;
    // 0x802C6088: addu        $t5, $a1, $t4
    ctx->r13 = ADD32(ctx->r5, ctx->r12);
    // 0x802C608C: lbu         $t6, 0x0($t5)
    ctx->r14 = MEM_BU(ctx->r13, 0X0);
    // 0x802C6090: andi        $t7, $t6, 0x1
    ctx->r15 = ctx->r14 & 0X1;
    // 0x802C6094: bnel        $t7, $zero, L_802C60A8
    if (ctx->r15 != 0) {
        // 0x802C6098: lw          $t9, 0x0($t3)
        ctx->r25 = MEM_W(ctx->r11, 0X0);
            goto L_802C60A8;
    }
    goto skip_2;
    // 0x802C6098: lw          $t9, 0x0($t3)
    ctx->r25 = MEM_W(ctx->r11, 0X0);
    skip_2:
    // 0x802C609C: b           L_802C6074
    // 0x802C60A0: sw          $t8, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r24;
        goto L_802C6074;
    // 0x802C60A0: sw          $t8, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r24;
    // 0x802C60A4: lw          $t9, 0x0($t3)
    ctx->r25 = MEM_W(ctx->r11, 0X0);
L_802C60A8:
    // 0x802C60A8: addiu       $at, $zero, 0x4
    ctx->r1 = ADD32(0, 0X4);
    // 0x802C60AC: bne         $t9, $at, L_802C60D8
    if (ctx->r25 != ctx->r1) {
        // 0x802C60B0: addiu       $at, $zero, 0x3
        ctx->r1 = ADD32(0, 0X3);
            goto L_802C60D8;
    }
    // 0x802C60B0: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x802C60B4: bne         $t0, $at, L_802C60D8
    if (ctx->r8 != ctx->r1) {
        // 0x802C60B8: lui         $a2, 0x802C
        ctx->r6 = S32(0X802C << 16);
            goto L_802C60D8;
    }
    // 0x802C60B8: lui         $a2, 0x802C
    ctx->r6 = S32(0X802C << 16);
    // 0x802C60BC: addiu       $a2, $a2, 0x704C
    ctx->r6 = ADD32(ctx->r6, 0X704C);
    // 0x802C60C0: lw          $v0, 0x0($a2)
    ctx->r2 = MEM_W(ctx->r6, 0X0);
    // 0x802C60C4: addiu       $a1, $zero, -0x1
    ctx->r5 = ADD32(0, -0X1);
    // 0x802C60C8: beq         $a1, $v0, L_802C60D8
    if (ctx->r5 == ctx->r2) {
        // 0x802C60CC: nop
    
            goto L_802C60D8;
    }
    // 0x802C60CC: nop

    // 0x802C60D0: sw          $v0, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r2;
    // 0x802C60D4: sw          $a1, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r5;
L_802C60D8:
    // 0x802C60D8: beq         $t2, $zero, L_802C63D4
    if (ctx->r10 == 0) {
        // 0x802C60DC: addiu       $a0, $zero, 0x10
        ctx->r4 = ADD32(0, 0X10);
            goto L_802C63D4;
    }
    // 0x802C60DC: addiu       $a0, $zero, 0x10
    ctx->r4 = ADD32(0, 0X10);
    // 0x802C60E0: jal         0x800C37F4
    // 0x802C60E4: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_8;
    // 0x802C60E4: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_8:
    // 0x802C60E8: b           L_802C63D8
    // 0x802C60EC: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_802C63D8;
    // 0x802C60EC: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C60F0:
    // 0x802C60F0: beq         $t4, $zero, L_802C61F0
    if (ctx->r12 == 0) {
        // 0x802C60F4: andi        $t9, $v1, 0x200
        ctx->r25 = ctx->r3 & 0X200;
            goto L_802C61F0;
    }
    // 0x802C60F4: andi        $t9, $v1, 0x200
    ctx->r25 = ctx->r3 & 0X200;
    // 0x802C60F8: lui         $a1, 0x801D
    ctx->r5 = S32(0X801D << 16);
    // 0x802C60FC: addiu       $a1, $a1, -0x19C0
    ctx->r5 = ADD32(ctx->r5, -0X19C0);
    // 0x802C6100: lw          $t5, 0x0($a1)
    ctx->r13 = MEM_W(ctx->r5, 0X0);
    // 0x802C6104: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x802C6108: lui         $v0, 0x802C
    ctx->r2 = S32(0X802C << 16);
    // 0x802C610C: bne         $t5, $at, L_802C61D8
    if (ctx->r13 != ctx->r1) {
        // 0x802C6110: addiu       $v0, $v0, 0x753C
        ctx->r2 = ADD32(ctx->r2, 0X753C);
            goto L_802C61D8;
    }
    // 0x802C6110: addiu       $v0, $v0, 0x753C
    ctx->r2 = ADD32(ctx->r2, 0X753C);
    // 0x802C6114: lw          $t0, 0x0($v0)
    ctx->r8 = MEM_W(ctx->r2, 0X0);
    // 0x802C6118: lui         $t3, 0x802C
    ctx->r11 = S32(0X802C << 16);
    // 0x802C611C: addiu       $t3, $t3, 0x7540
    ctx->r11 = ADD32(ctx->r11, 0X7540);
    // 0x802C6120: addiu       $t6, $t0, 0x1
    ctx->r14 = ADD32(ctx->r8, 0X1);
    // 0x802C6124: slti        $at, $t6, 0x6
    ctx->r1 = SIGNED(ctx->r14) < 0X6 ? 1 : 0;
    // 0x802C6128: sw          $t0, 0x0($t3)
    MEM_W(0X0, ctx->r11) = ctx->r8;
    // 0x802C612C: addiu       $t2, $zero, 0x1
    ctx->r10 = ADD32(0, 0X1);
    // 0x802C6130: sw          $t6, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r14;
    // 0x802C6134: bne         $at, $zero, L_802C6144
    if (ctx->r1 != 0) {
        // 0x802C6138: or          $t0, $t6, $zero
        ctx->r8 = ctx->r14 | 0;
            goto L_802C6144;
    }
    // 0x802C6138: or          $t0, $t6, $zero
    ctx->r8 = ctx->r14 | 0;
    // 0x802C613C: sw          $zero, 0x0($v0)
    MEM_W(0X0, ctx->r2) = 0;
    // 0x802C6140: or          $t0, $zero, $zero
    ctx->r8 = 0 | 0;
L_802C6144:
    // 0x802C6144: lw          $t7, 0x0($t3)
    ctx->r15 = MEM_W(ctx->r11, 0X0);
    // 0x802C6148: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x802C614C: sll         $a3, $t0, 3
    ctx->r7 = S32(ctx->r8 << 3);
    // 0x802C6150: bne         $t7, $at, L_802C6178
    if (ctx->r15 != ctx->r1) {
        // 0x802C6154: subu        $a3, $a3, $t0
        ctx->r7 = SUB32(ctx->r7, ctx->r8);
            goto L_802C6178;
    }
    // 0x802C6154: subu        $a3, $a3, $t0
    ctx->r7 = SUB32(ctx->r7, ctx->r8);
    // 0x802C6158: addiu       $at, $zero, 0x4
    ctx->r1 = ADD32(0, 0X4);
    // 0x802C615C: bne         $t0, $at, L_802C6178
    if (ctx->r8 != ctx->r1) {
        // 0x802C6160: lui         $a0, 0x802C
        ctx->r4 = S32(0X802C << 16);
            goto L_802C6178;
    }
    // 0x802C6160: lui         $a0, 0x802C
    ctx->r4 = S32(0X802C << 16);
    // 0x802C6164: addiu       $a0, $a0, 0x7538
    ctx->r4 = ADD32(ctx->r4, 0X7538);
    // 0x802C6168: lw          $t8, 0x0($a0)
    ctx->r24 = MEM_W(ctx->r4, 0X0);
    // 0x802C616C: lui         $a2, 0x802C
    ctx->r6 = S32(0X802C << 16);
    // 0x802C6170: addiu       $a2, $a2, 0x704C
    ctx->r6 = ADD32(ctx->r6, 0X704C);
    // 0x802C6174: sw          $t8, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r24;
L_802C6178:
    // 0x802C6178: lui         $a0, 0x802C
    ctx->r4 = S32(0X802C << 16);
    // 0x802C617C: addiu       $a0, $a0, 0x7538
    ctx->r4 = ADD32(ctx->r4, 0X7538);
    // 0x802C6180: lui         $a1, 0x802C
    ctx->r5 = S32(0X802C << 16);
    // 0x802C6184: addiu       $a1, $a1, 0x7054
    ctx->r5 = ADD32(ctx->r5, 0X7054);
    // 0x802C6188: lw          $v1, 0x0($a0)
    ctx->r3 = MEM_W(ctx->r4, 0X0);
    // 0x802C618C: addiu       $t1, $zero, 0x5
    ctx->r9 = ADD32(0, 0X5);
    // 0x802C6190: addiu       $a2, $zero, 0x1C
    ctx->r6 = ADD32(0, 0X1C);
L_802C6194:
    // 0x802C6194: addu        $v0, $a3, $v1
    ctx->r2 = ADD32(ctx->r7, ctx->r3);
    // 0x802C6198: multu       $v0, $a2
    result = U64(U32(ctx->r2)) * U64(U32(ctx->r6)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x802C619C: addiu       $t7, $v1, 0x1
    ctx->r15 = ADD32(ctx->r3, 0X1);
    // 0x802C61A0: addiu       $t8, $v1, -0x1
    ctx->r24 = ADD32(ctx->r3, -0X1);
    // 0x802C61A4: mflo        $t9
    ctx->r25 = lo;
    // 0x802C61A8: addu        $t4, $a1, $t9
    ctx->r12 = ADD32(ctx->r5, ctx->r25);
    // 0x802C61AC: lbu         $t5, 0x0($t4)
    ctx->r13 = MEM_BU(ctx->r12, 0X0);
    // 0x802C61B0: andi        $t6, $t5, 0x1
    ctx->r14 = ctx->r13 & 0X1;
    // 0x802C61B4: bne         $t6, $zero, L_802C61D8
    if (ctx->r14 != 0) {
        // 0x802C61B8: nop
    
            goto L_802C61D8;
    }
    // 0x802C61B8: nop

    // 0x802C61BC: bnel        $t1, $t0, L_802C61D0
    if (ctx->r9 != ctx->r8) {
        // 0x802C61C0: sw          $t8, 0x0($a0)
        MEM_W(0X0, ctx->r4) = ctx->r24;
            goto L_802C61D0;
    }
    goto skip_3;
    // 0x802C61C0: sw          $t8, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r24;
    skip_3:
    // 0x802C61C4: b           L_802C61D0
    // 0x802C61C8: sw          $t7, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r15;
        goto L_802C61D0;
    // 0x802C61C8: sw          $t7, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r15;
    // 0x802C61CC: sw          $t8, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r24;
L_802C61D0:
    // 0x802C61D0: b           L_802C6194
    // 0x802C61D4: lw          $v1, 0x0($a0)
    ctx->r3 = MEM_W(ctx->r4, 0X0);
        goto L_802C6194;
    // 0x802C61D4: lw          $v1, 0x0($a0)
    ctx->r3 = MEM_W(ctx->r4, 0X0);
L_802C61D8:
    // 0x802C61D8: beq         $t2, $zero, L_802C63D4
    if (ctx->r10 == 0) {
        // 0x802C61DC: addiu       $a0, $zero, 0x10
        ctx->r4 = ADD32(0, 0X10);
            goto L_802C63D4;
    }
    // 0x802C61DC: addiu       $a0, $zero, 0x10
    ctx->r4 = ADD32(0, 0X10);
    // 0x802C61E0: jal         0x800C37F4
    // 0x802C61E4: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_9;
    // 0x802C61E4: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_9:
    // 0x802C61E8: b           L_802C63D8
    // 0x802C61EC: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_802C63D8;
    // 0x802C61EC: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C61F0:
    // 0x802C61F0: beq         $t9, $zero, L_802C62E4
    if (ctx->r25 == 0) {
        // 0x802C61F4: lui         $a1, 0x801D
        ctx->r5 = S32(0X801D << 16);
            goto L_802C62E4;
    }
    // 0x802C61F4: lui         $a1, 0x801D
    ctx->r5 = S32(0X801D << 16);
    // 0x802C61F8: addiu       $a1, $a1, -0x19C0
    ctx->r5 = ADD32(ctx->r5, -0X19C0);
    // 0x802C61FC: lw          $v0, 0x0($a1)
    ctx->r2 = MEM_W(ctx->r5, 0X0);
    // 0x802C6200: addiu       $t8, $zero, 0x200
    ctx->r24 = ADD32(0, 0X200);
    // 0x802C6204: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C6208: beq         $v0, $zero, L_802C6224
    if (ctx->r2 == 0) {
        // 0x802C620C: nop
    
            goto L_802C6224;
    }
    // 0x802C620C: nop

    // 0x802C6210: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x802C6214: beq         $v0, $at, L_802C6250
    if (ctx->r2 == ctx->r1) {
        // 0x802C6218: addiu       $a1, $zero, -0x1
        ctx->r5 = ADD32(0, -0X1);
            goto L_802C6250;
    }
    // 0x802C6218: addiu       $a1, $zero, -0x1
    ctx->r5 = ADD32(0, -0X1);
    // 0x802C621C: b           L_802C62CC
    // 0x802C6220: nop

        goto L_802C62CC;
    // 0x802C6220: nop

L_802C6224:
    // 0x802C6224: lui         $v0, 0x802C
    ctx->r2 = S32(0X802C << 16);
    // 0x802C6228: addiu       $v0, $v0, 0x7040
    ctx->r2 = ADD32(ctx->r2, 0X7040);
    // 0x802C622C: lw          $t4, 0x0($v0)
    ctx->r12 = MEM_W(ctx->r2, 0X0);
    // 0x802C6230: addiu       $t2, $zero, 0x1
    ctx->r10 = ADD32(0, 0X1);
    // 0x802C6234: addiu       $t7, $zero, 0x3
    ctx->r15 = ADD32(0, 0X3);
    // 0x802C6238: addiu       $t5, $t4, -0x1
    ctx->r13 = ADD32(ctx->r12, -0X1);
    // 0x802C623C: bgez        $t5, L_802C6248
    if (SIGNED(ctx->r13) >= 0) {
        // 0x802C6240: sw          $t5, 0x0($v0)
        MEM_W(0X0, ctx->r2) = ctx->r13;
            goto L_802C6248;
    }
    // 0x802C6240: sw          $t5, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r13;
    // 0x802C6244: sw          $t7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r15;
L_802C6248:
    // 0x802C6248: b           L_802C62CC
    // 0x802C624C: sw          $t8, 0x7050($at)
    MEM_W(0X7050, ctx->r1) = ctx->r24;
        goto L_802C62CC;
    // 0x802C624C: sw          $t8, 0x7050($at)
    MEM_W(0X7050, ctx->r1) = ctx->r24;
L_802C6250:
    // 0x802C6250: lui         $a2, 0x802C
    ctx->r6 = S32(0X802C << 16);
    // 0x802C6254: addiu       $a2, $a2, 0x704C
    ctx->r6 = ADD32(ctx->r6, 0X704C);
    // 0x802C6258: sw          $a1, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r5;
    // 0x802C625C: lui         $a3, 0x802C
    ctx->r7 = S32(0X802C << 16);
    // 0x802C6260: lw          $a3, 0x753C($a3)
    ctx->r7 = MEM_W(ctx->r7, 0X753C);
    // 0x802C6264: lui         $a1, 0x802C
    ctx->r5 = S32(0X802C << 16);
    // 0x802C6268: lui         $v1, 0x802C
    ctx->r3 = S32(0X802C << 16);
    // 0x802C626C: sll         $t9, $a3, 3
    ctx->r25 = S32(ctx->r7 << 3);
    // 0x802C6270: lui         $a0, 0x802C
    ctx->r4 = S32(0X802C << 16);
    // 0x802C6274: subu        $t9, $t9, $a3
    ctx->r25 = SUB32(ctx->r25, ctx->r7);
    // 0x802C6278: addiu       $t2, $zero, 0x1
    ctx->r10 = ADD32(0, 0X1);
    // 0x802C627C: or          $a3, $t9, $zero
    ctx->r7 = ctx->r25 | 0;
    // 0x802C6280: addiu       $a0, $a0, 0x7538
    ctx->r4 = ADD32(ctx->r4, 0X7538);
    // 0x802C6284: lw          $v1, 0x7538($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X7538);
    // 0x802C6288: addiu       $a1, $a1, 0x7054
    ctx->r5 = ADD32(ctx->r5, 0X7054);
    // 0x802C628C: addiu       $a2, $zero, 0x1C
    ctx->r6 = ADD32(0, 0X1C);
    // 0x802C6290: addiu       $t0, $zero, 0x6
    ctx->r8 = ADD32(0, 0X6);
    // 0x802C6294: addiu       $t4, $v1, -0x1
    ctx->r12 = ADD32(ctx->r3, -0X1);
L_802C6298:
    // 0x802C6298: sw          $t4, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r12;
    // 0x802C629C: bgez        $t4, L_802C62AC
    if (SIGNED(ctx->r12) >= 0) {
        // 0x802C62A0: or          $v1, $t4, $zero
        ctx->r3 = ctx->r12 | 0;
            goto L_802C62AC;
    }
    // 0x802C62A0: or          $v1, $t4, $zero
    ctx->r3 = ctx->r12 | 0;
    // 0x802C62A4: sw          $t0, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r8;
    // 0x802C62A8: or          $v1, $t0, $zero
    ctx->r3 = ctx->r8 | 0;
L_802C62AC:
    // 0x802C62AC: addu        $v0, $a3, $v1
    ctx->r2 = ADD32(ctx->r7, ctx->r3);
    // 0x802C62B0: multu       $v0, $a2
    result = U64(U32(ctx->r2)) * U64(U32(ctx->r6)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x802C62B4: mflo        $t5
    ctx->r13 = lo;
    // 0x802C62B8: addu        $t6, $a1, $t5
    ctx->r14 = ADD32(ctx->r5, ctx->r13);
    // 0x802C62BC: lbu         $t7, 0x0($t6)
    ctx->r15 = MEM_BU(ctx->r14, 0X0);
    // 0x802C62C0: andi        $t8, $t7, 0x1
    ctx->r24 = ctx->r15 & 0X1;
    // 0x802C62C4: beql        $t8, $zero, L_802C6298
    if (ctx->r24 == 0) {
        // 0x802C62C8: addiu       $t4, $v1, -0x1
        ctx->r12 = ADD32(ctx->r3, -0X1);
            goto L_802C6298;
    }
    goto skip_4;
    // 0x802C62C8: addiu       $t4, $v1, -0x1
    ctx->r12 = ADD32(ctx->r3, -0X1);
    skip_4:
L_802C62CC:
    // 0x802C62CC: beq         $t2, $zero, L_802C63D4
    if (ctx->r10 == 0) {
        // 0x802C62D0: addiu       $a0, $zero, 0x10
        ctx->r4 = ADD32(0, 0X10);
            goto L_802C63D4;
    }
    // 0x802C62D0: addiu       $a0, $zero, 0x10
    ctx->r4 = ADD32(0, 0X10);
    // 0x802C62D4: jal         0x800C37F4
    // 0x802C62D8: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_10;
    // 0x802C62D8: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_10:
    // 0x802C62DC: b           L_802C63D8
    // 0x802C62E0: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_802C63D8;
    // 0x802C62E0: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C62E4:
    // 0x802C62E4: andi        $t9, $v1, 0x100
    ctx->r25 = ctx->r3 & 0X100;
    // 0x802C62E8: beq         $t9, $zero, L_802C63D4
    if (ctx->r25 == 0) {
        // 0x802C62EC: lui         $a1, 0x801D
        ctx->r5 = S32(0X801D << 16);
            goto L_802C63D4;
    }
    // 0x802C62EC: lui         $a1, 0x801D
    ctx->r5 = S32(0X801D << 16);
    // 0x802C62F0: addiu       $a1, $a1, -0x19C0
    ctx->r5 = ADD32(ctx->r5, -0X19C0);
    // 0x802C62F4: lw          $v0, 0x0($a1)
    ctx->r2 = MEM_W(ctx->r5, 0X0);
    // 0x802C62F8: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x802C62FC: addiu       $t7, $zero, 0x200
    ctx->r15 = ADD32(0, 0X200);
    // 0x802C6300: beq         $v0, $zero, L_802C6318
    if (ctx->r2 == 0) {
        // 0x802C6304: nop
    
            goto L_802C6318;
    }
    // 0x802C6304: nop

    // 0x802C6308: beq         $v0, $at, L_802C6348
    if (ctx->r2 == ctx->r1) {
        // 0x802C630C: addiu       $a1, $zero, -0x1
        ctx->r5 = ADD32(0, -0X1);
            goto L_802C6348;
    }
    // 0x802C630C: addiu       $a1, $zero, -0x1
    ctx->r5 = ADD32(0, -0X1);
    // 0x802C6310: b           L_802C63C4
    // 0x802C6314: nop

        goto L_802C63C4;
    // 0x802C6314: nop

L_802C6318:
    // 0x802C6318: lui         $v0, 0x802C
    ctx->r2 = S32(0X802C << 16);
    // 0x802C631C: addiu       $v0, $v0, 0x7040
    ctx->r2 = ADD32(ctx->r2, 0X7040);
    // 0x802C6320: lw          $t4, 0x0($v0)
    ctx->r12 = MEM_W(ctx->r2, 0X0);
    // 0x802C6324: addiu       $t2, $zero, 0x1
    ctx->r10 = ADD32(0, 0X1);
    // 0x802C6328: addiu       $t5, $t4, 0x1
    ctx->r13 = ADD32(ctx->r12, 0X1);
    // 0x802C632C: slti        $at, $t5, 0x4
    ctx->r1 = SIGNED(ctx->r13) < 0X4 ? 1 : 0;
    // 0x802C6330: bne         $at, $zero, L_802C633C
    if (ctx->r1 != 0) {
        // 0x802C6334: sw          $t5, 0x0($v0)
        MEM_W(0X0, ctx->r2) = ctx->r13;
            goto L_802C633C;
    }
    // 0x802C6334: sw          $t5, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r13;
    // 0x802C6338: sw          $zero, 0x0($v0)
    MEM_W(0X0, ctx->r2) = 0;
L_802C633C:
    // 0x802C633C: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C6340: b           L_802C63C4
    // 0x802C6344: sw          $t7, 0x7050($at)
    MEM_W(0X7050, ctx->r1) = ctx->r15;
        goto L_802C63C4;
    // 0x802C6344: sw          $t7, 0x7050($at)
    MEM_W(0X7050, ctx->r1) = ctx->r15;
L_802C6348:
    // 0x802C6348: lui         $a2, 0x802C
    ctx->r6 = S32(0X802C << 16);
    // 0x802C634C: addiu       $a2, $a2, 0x704C
    ctx->r6 = ADD32(ctx->r6, 0X704C);
    // 0x802C6350: sw          $a1, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r5;
    // 0x802C6354: lui         $a3, 0x802C
    ctx->r7 = S32(0X802C << 16);
    // 0x802C6358: lw          $a3, 0x753C($a3)
    ctx->r7 = MEM_W(ctx->r7, 0X753C);
    // 0x802C635C: lui         $a1, 0x802C
    ctx->r5 = S32(0X802C << 16);
    // 0x802C6360: lui         $v1, 0x802C
    ctx->r3 = S32(0X802C << 16);
    // 0x802C6364: sll         $t8, $a3, 3
    ctx->r24 = S32(ctx->r7 << 3);
    // 0x802C6368: lui         $a0, 0x802C
    ctx->r4 = S32(0X802C << 16);
    // 0x802C636C: subu        $t8, $t8, $a3
    ctx->r24 = SUB32(ctx->r24, ctx->r7);
    // 0x802C6370: addiu       $t2, $zero, 0x1
    ctx->r10 = ADD32(0, 0X1);
    // 0x802C6374: or          $a3, $t8, $zero
    ctx->r7 = ctx->r24 | 0;
    // 0x802C6378: addiu       $a0, $a0, 0x7538
    ctx->r4 = ADD32(ctx->r4, 0X7538);
    // 0x802C637C: lw          $v1, 0x7538($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X7538);
    // 0x802C6380: addiu       $a1, $a1, 0x7054
    ctx->r5 = ADD32(ctx->r5, 0X7054);
    // 0x802C6384: addiu       $a2, $zero, 0x1C
    ctx->r6 = ADD32(0, 0X1C);
    // 0x802C6388: addiu       $t9, $v1, 0x1
    ctx->r25 = ADD32(ctx->r3, 0X1);
L_802C638C:
    // 0x802C638C: slti        $at, $t9, 0x7
    ctx->r1 = SIGNED(ctx->r25) < 0X7 ? 1 : 0;
    // 0x802C6390: sw          $t9, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r25;
    // 0x802C6394: bne         $at, $zero, L_802C63A4
    if (ctx->r1 != 0) {
        // 0x802C6398: or          $v1, $t9, $zero
        ctx->r3 = ctx->r25 | 0;
            goto L_802C63A4;
    }
    // 0x802C6398: or          $v1, $t9, $zero
    ctx->r3 = ctx->r25 | 0;
    // 0x802C639C: sw          $zero, 0x0($a0)
    MEM_W(0X0, ctx->r4) = 0;
    // 0x802C63A0: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
L_802C63A4:
    // 0x802C63A4: addu        $v0, $a3, $v1
    ctx->r2 = ADD32(ctx->r7, ctx->r3);
    // 0x802C63A8: multu       $v0, $a2
    result = U64(U32(ctx->r2)) * U64(U32(ctx->r6)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x802C63AC: mflo        $t4
    ctx->r12 = lo;
    // 0x802C63B0: addu        $t5, $a1, $t4
    ctx->r13 = ADD32(ctx->r5, ctx->r12);
    // 0x802C63B4: lbu         $t6, 0x0($t5)
    ctx->r14 = MEM_BU(ctx->r13, 0X0);
    // 0x802C63B8: andi        $t7, $t6, 0x1
    ctx->r15 = ctx->r14 & 0X1;
    // 0x802C63BC: beql        $t7, $zero, L_802C638C
    if (ctx->r15 == 0) {
        // 0x802C63C0: addiu       $t9, $v1, 0x1
        ctx->r25 = ADD32(ctx->r3, 0X1);
            goto L_802C638C;
    }
    goto skip_5;
    // 0x802C63C0: addiu       $t9, $v1, 0x1
    ctx->r25 = ADD32(ctx->r3, 0X1);
    skip_5:
L_802C63C4:
    // 0x802C63C4: beq         $t2, $zero, L_802C63D4
    if (ctx->r10 == 0) {
        // 0x802C63C8: addiu       $a0, $zero, 0x10
        ctx->r4 = ADD32(0, 0X10);
            goto L_802C63D4;
    }
    // 0x802C63C8: addiu       $a0, $zero, 0x10
    ctx->r4 = ADD32(0, 0X10);
    // 0x802C63CC: jal         0x800C37F4
    // 0x802C63D0: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_11;
    // 0x802C63D0: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_11:
L_802C63D4:
    // 0x802C63D4: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C63D8:
    // 0x802C63D8: addiu       $sp, $sp, 0x28
    ctx->r29 = ADD32(ctx->r29, 0X28);
    // 0x802C63DC: jr          $ra
    // 0x802C63E0: nop

    return;
    // 0x802C63E0: nop

;}
RECOMP_FUNC void func_i8_802C63E4(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C63E4: addiu       $sp, $sp, -0x58
    ctx->r29 = ADD32(ctx->r29, -0X58);
    // 0x802C63E8: sw          $s0, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r16;
    // 0x802C63EC: sw          $ra, 0x54($sp)
    MEM_W(0X54, ctx->r29) = ctx->r31;
    // 0x802C63F0: sw          $s4, 0x50($sp)
    MEM_W(0X50, ctx->r29) = ctx->r20;
    // 0x802C63F4: sw          $s3, 0x4C($sp)
    MEM_W(0X4C, ctx->r29) = ctx->r19;
    // 0x802C63F8: sw          $s2, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r18;
    // 0x802C63FC: sw          $s1, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r17;
    // 0x802C6400: lui         $t6, 0x806
    ctx->r14 = S32(0X806 << 16);
    // 0x802C6404: lui         $s0, 0x600
    ctx->r16 = S32(0X600 << 16);
    // 0x802C6408: addiu       $t6, $t6, 0x1E50
    ctx->r14 = ADD32(ctx->r14, 0X1E50);
    // 0x802C640C: sw          $t6, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r14;
    // 0x802C6410: sw          $s0, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r16;
    // 0x802C6414: addiu       $v1, $a0, 0x8
    ctx->r3 = ADD32(ctx->r4, 0X8);
    // 0x802C6418: lui         $t7, 0x107
    ctx->r15 = S32(0X107 << 16);
    // 0x802C641C: addiu       $t7, $t7, -0x9D8
    ctx->r15 = ADD32(ctx->r15, -0X9D8);
    // 0x802C6420: sw          $t7, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r15;
    // 0x802C6424: sw          $s0, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r16;
    // 0x802C6428: addiu       $t8, $zero, 0x171
    ctx->r24 = ADD32(0, 0X171);
    // 0x802C642C: addiu       $t9, $zero, 0x17
    ctx->r25 = ADD32(0, 0X17);
    // 0x802C6430: addiu       $a0, $v1, 0x8
    ctx->r4 = ADD32(ctx->r3, 0X8);
    // 0x802C6434: sw          $t9, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r25;
    // 0x802C6438: sw          $t8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r24;
    // 0x802C643C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C6440: addiu       $a2, $zero, 0x1B
    ctx->r6 = ADD32(0, 0X1B);
    // 0x802C6444: jal         0x80094338
    // 0x802C6448: addiu       $a3, $zero, 0x16
    ctx->r7 = ADD32(0, 0X16);
    func_80094338(rdram, ctx);
        goto after_0;
    // 0x802C6448: addiu       $a3, $zero, 0x16
    ctx->r7 = ADD32(0, 0X16);
    after_0:
    // 0x802C644C: addiu       $t1, $zero, 0x82
    ctx->r9 = ADD32(0, 0X82);
    // 0x802C6450: addiu       $t2, $zero, 0x10
    ctx->r10 = ADD32(0, 0X10);
    // 0x802C6454: sw          $t2, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r10;
    // 0x802C6458: sw          $t1, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r9;
    // 0x802C645C: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C6460: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C6464: addiu       $a2, $zero, 0x1B
    ctx->r6 = ADD32(0, 0X1B);
    // 0x802C6468: jal         0x80094338
    // 0x802C646C: addiu       $a3, $zero, 0x60
    ctx->r7 = ADD32(0, 0X60);
    func_80094338(rdram, ctx);
        goto after_1;
    // 0x802C646C: addiu       $a3, $zero, 0x60
    ctx->r7 = ADD32(0, 0X60);
    after_1:
    // 0x802C6470: addiu       $t3, $zero, 0x43
    ctx->r11 = ADD32(0, 0X43);
    // 0x802C6474: addiu       $t4, $zero, 0xE
    ctx->r12 = ADD32(0, 0XE);
    // 0x802C6478: sw          $t4, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r12;
    // 0x802C647C: sw          $t3, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r11;
    // 0x802C6480: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C6484: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C6488: addiu       $a2, $zero, 0x21
    ctx->r6 = ADD32(0, 0X21);
    // 0x802C648C: jal         0x80094338
    // 0x802C6490: addiu       $a3, $zero, 0xB0
    ctx->r7 = ADD32(0, 0XB0);
    func_80094338(rdram, ctx);
        goto after_2;
    // 0x802C6490: addiu       $a3, $zero, 0xB0
    ctx->r7 = ADD32(0, 0XB0);
    after_2:
    // 0x802C6494: addiu       $t5, $zero, 0x32
    ctx->r13 = ADD32(0, 0X32);
    // 0x802C6498: addiu       $t6, $zero, 0xE
    ctx->r14 = ADD32(0, 0XE);
    // 0x802C649C: sw          $t6, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r14;
    // 0x802C64A0: sw          $t5, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r13;
    // 0x802C64A4: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C64A8: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C64AC: addiu       $a2, $zero, 0x65
    ctx->r6 = ADD32(0, 0X65);
    // 0x802C64B0: jal         0x80094338
    // 0x802C64B4: addiu       $a3, $zero, 0xB0
    ctx->r7 = ADD32(0, 0XB0);
    func_80094338(rdram, ctx);
        goto after_3;
    // 0x802C64B4: addiu       $a3, $zero, 0xB0
    ctx->r7 = ADD32(0, 0XB0);
    after_3:
    // 0x802C64B8: addiu       $t7, $zero, 0x43
    ctx->r15 = ADD32(0, 0X43);
    // 0x802C64BC: addiu       $t8, $zero, 0xE
    ctx->r24 = ADD32(0, 0XE);
    // 0x802C64C0: sw          $t8, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r24;
    // 0x802C64C4: sw          $t7, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r15;
    // 0x802C64C8: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C64CC: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C64D0: addiu       $a2, $zero, 0x21
    ctx->r6 = ADD32(0, 0X21);
    // 0x802C64D4: jal         0x80094338
    // 0x802C64D8: addiu       $a3, $zero, 0xC0
    ctx->r7 = ADD32(0, 0XC0);
    func_80094338(rdram, ctx);
        goto after_4;
    // 0x802C64D8: addiu       $a3, $zero, 0xC0
    ctx->r7 = ADD32(0, 0XC0);
    after_4:
    // 0x802C64DC: addiu       $t9, $zero, 0x21
    ctx->r25 = ADD32(0, 0X21);
    // 0x802C64E0: addiu       $t1, $zero, 0xE
    ctx->r9 = ADD32(0, 0XE);
    // 0x802C64E4: sw          $t1, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r9;
    // 0x802C64E8: sw          $t9, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r25;
    // 0x802C64EC: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C64F0: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C64F4: addiu       $a2, $zero, 0x76
    ctx->r6 = ADD32(0, 0X76);
    // 0x802C64F8: jal         0x80094338
    // 0x802C64FC: addiu       $a3, $zero, 0xC0
    ctx->r7 = ADD32(0, 0XC0);
    func_80094338(rdram, ctx);
        goto after_5;
    // 0x802C64FC: addiu       $a3, $zero, 0xC0
    ctx->r7 = ADD32(0, 0XC0);
    after_5:
    // 0x802C6500: lui         $t2, 0x806
    ctx->r10 = S32(0X806 << 16);
    // 0x802C6504: addiu       $t2, $t2, 0x1FB0
    ctx->r10 = ADD32(ctx->r10, 0X1FB0);
    // 0x802C6508: lui         $t3, 0xB400
    ctx->r11 = S32(0XB400 << 16);
    // 0x802C650C: sw          $t2, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r10;
    // 0x802C6510: sw          $s0, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r16;
    // 0x802C6514: sw          $t3, 0x8($v0)
    MEM_W(0X8, ctx->r2) = ctx->r11;
    // 0x802C6518: lui         $t4, 0x802C
    ctx->r12 = S32(0X802C << 16);
    // 0x802C651C: lhu         $t4, 0x7530($t4)
    ctx->r12 = MEM_HU(ctx->r12, 0X7530);
    // 0x802C6520: lui         $s1, 0x102
    ctx->r17 = S32(0X102 << 16);
    // 0x802C6524: lui         $t5, 0x103
    ctx->r13 = S32(0X103 << 16);
    // 0x802C6528: lui         $t6, 0x700
    ctx->r14 = S32(0X700 << 16);
    // 0x802C652C: lui         $t7, 0x107
    ctx->r15 = S32(0X107 << 16);
    // 0x802C6530: lui         $t8, 0x806
    ctx->r24 = S32(0X806 << 16);
    // 0x802C6534: lui         $t9, 0x700
    ctx->r25 = S32(0X700 << 16);
    // 0x802C6538: ori         $s1, $s1, 0x40
    ctx->r17 = ctx->r17 | 0X40;
    // 0x802C653C: lui         $s2, 0x801D
    ctx->r18 = S32(0X801D << 16);
    // 0x802C6540: addiu       $t6, $t6, 0xA40
    ctx->r14 = ADD32(ctx->r14, 0XA40);
    // 0x802C6544: ori         $t5, $t5, 0x40
    ctx->r13 = ctx->r13 | 0X40;
    // 0x802C6548: addiu       $t7, $t7, -0xB78
    ctx->r15 = ADD32(ctx->r15, -0XB78);
    // 0x802C654C: addiu       $t8, $t8, 0x1F70
    ctx->r24 = ADD32(ctx->r24, 0X1F70);
    // 0x802C6550: addiu       $t9, $t9, 0xA80
    ctx->r25 = ADD32(ctx->r25, 0XA80);
    // 0x802C6554: addiu       $s2, $s2, -0x1A08
    ctx->r18 = ADD32(ctx->r18, -0X1A08);
    // 0x802C6558: sw          $t5, 0x10($v0)
    MEM_W(0X10, ctx->r2) = ctx->r13;
    // 0x802C655C: sw          $t6, 0x14($v0)
    MEM_W(0X14, ctx->r2) = ctx->r14;
    // 0x802C6560: sw          $t7, 0x1C($v0)
    MEM_W(0X1C, ctx->r2) = ctx->r15;
    // 0x802C6564: sw          $s0, 0x18($v0)
    MEM_W(0X18, ctx->r2) = ctx->r16;
    // 0x802C6568: sw          $t8, 0x24($v0)
    MEM_W(0X24, ctx->r2) = ctx->r24;
    // 0x802C656C: sw          $s0, 0x20($v0)
    MEM_W(0X20, ctx->r2) = ctx->r16;
    // 0x802C6570: sw          $t9, 0x2C($v0)
    MEM_W(0X2C, ctx->r2) = ctx->r25;
    // 0x802C6574: sw          $s1, 0x28($v0)
    MEM_W(0X28, ctx->r2) = ctx->r17;
    // 0x802C6578: sw          $t4, 0xC($v0)
    MEM_W(0XC, ctx->r2) = ctx->r12;
    // 0x802C657C: lw          $t1, 0x0($s2)
    ctx->r9 = MEM_W(ctx->r18, 0X0);
    // 0x802C6580: addiu       $a0, $v0, 0x30
    ctx->r4 = ADD32(ctx->r2, 0X30);
    // 0x802C6584: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C6588: addiu       $t2, $t1, 0xC80
    ctx->r10 = ADD32(ctx->r9, 0XC80);
    // 0x802C658C: sw          $t2, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r10;
    // 0x802C6590: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x802C6594: jal         0x801E4FE8
    // 0x802C6598: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_801E4FE8(rdram, ctx);
        goto after_6;
    // 0x802C6598: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_6:
    // 0x802C659C: lui         $t3, 0x806
    ctx->r11 = S32(0X806 << 16);
    // 0x802C65A0: lui         $t4, 0x700
    ctx->r12 = S32(0X700 << 16);
    // 0x802C65A4: addiu       $t3, $t3, 0x1F80
    ctx->r11 = ADD32(ctx->r11, 0X1F80);
    // 0x802C65A8: addiu       $t4, $t4, 0xAC0
    ctx->r12 = ADD32(ctx->r12, 0XAC0);
    // 0x802C65AC: sw          $t3, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r11;
    // 0x802C65B0: sw          $s0, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r16;
    // 0x802C65B4: sw          $t4, 0xC($v0)
    MEM_W(0XC, ctx->r2) = ctx->r12;
    // 0x802C65B8: sw          $s1, 0x8($v0)
    MEM_W(0X8, ctx->r2) = ctx->r17;
    // 0x802C65BC: lw          $t5, 0x0($s2)
    ctx->r13 = MEM_W(ctx->r18, 0X0);
    // 0x802C65C0: addiu       $a0, $v0, 0x10
    ctx->r4 = ADD32(ctx->r2, 0X10);
    // 0x802C65C4: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C65C8: addiu       $t6, $t5, 0xD40
    ctx->r14 = ADD32(ctx->r13, 0XD40);
    // 0x802C65CC: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x802C65D0: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x802C65D4: jal         0x801E4FE8
    // 0x802C65D8: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_801E4FE8(rdram, ctx);
        goto after_7;
    // 0x802C65D8: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_7:
    // 0x802C65DC: lui         $t7, 0x806
    ctx->r15 = S32(0X806 << 16);
    // 0x802C65E0: lui         $t8, 0x700
    ctx->r24 = S32(0X700 << 16);
    // 0x802C65E4: addiu       $t7, $t7, 0x1F90
    ctx->r15 = ADD32(ctx->r15, 0X1F90);
    // 0x802C65E8: addiu       $t8, $t8, 0xB00
    ctx->r24 = ADD32(ctx->r24, 0XB00);
    // 0x802C65EC: sw          $t7, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r15;
    // 0x802C65F0: sw          $s0, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r16;
    // 0x802C65F4: sw          $t8, 0xC($v0)
    MEM_W(0XC, ctx->r2) = ctx->r24;
    // 0x802C65F8: sw          $s1, 0x8($v0)
    MEM_W(0X8, ctx->r2) = ctx->r17;
    // 0x802C65FC: lw          $t9, 0x0($s2)
    ctx->r25 = MEM_W(ctx->r18, 0X0);
    // 0x802C6600: addiu       $a0, $v0, 0x10
    ctx->r4 = ADD32(ctx->r2, 0X10);
    // 0x802C6604: addiu       $a1, $zero, 0x3
    ctx->r5 = ADD32(0, 0X3);
    // 0x802C6608: addiu       $t1, $t9, 0xE00
    ctx->r9 = ADD32(ctx->r25, 0XE00);
    // 0x802C660C: sw          $t1, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r9;
    // 0x802C6610: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x802C6614: jal         0x801E4FE8
    // 0x802C6618: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_801E4FE8(rdram, ctx);
        goto after_8;
    // 0x802C6618: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_8:
    // 0x802C661C: lui         $t2, 0x806
    ctx->r10 = S32(0X806 << 16);
    // 0x802C6620: lui         $t3, 0x700
    ctx->r11 = S32(0X700 << 16);
    // 0x802C6624: addiu       $t2, $t2, 0x1FA0
    ctx->r10 = ADD32(ctx->r10, 0X1FA0);
    // 0x802C6628: addiu       $t3, $t3, 0xB40
    ctx->r11 = ADD32(ctx->r11, 0XB40);
    // 0x802C662C: sw          $t2, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r10;
    // 0x802C6630: sw          $s0, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r16;
    // 0x802C6634: sw          $t3, 0xC($v0)
    MEM_W(0XC, ctx->r2) = ctx->r11;
    // 0x802C6638: sw          $s1, 0x8($v0)
    MEM_W(0X8, ctx->r2) = ctx->r17;
    // 0x802C663C: lw          $t4, 0x0($s2)
    ctx->r12 = MEM_W(ctx->r18, 0X0);
    // 0x802C6640: addiu       $a0, $v0, 0x10
    ctx->r4 = ADD32(ctx->r2, 0X10);
    // 0x802C6644: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C6648: addiu       $t5, $t4, 0xEC0
    ctx->r13 = ADD32(ctx->r12, 0XEC0);
    // 0x802C664C: sw          $t5, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r13;
    // 0x802C6650: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x802C6654: jal         0x801E4FE8
    // 0x802C6658: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_801E4FE8(rdram, ctx);
        goto after_9;
    // 0x802C6658: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_9:
    // 0x802C665C: lui         $t6, 0x806
    ctx->r14 = S32(0X806 << 16);
    // 0x802C6660: addiu       $t6, $t6, 0x1EC0
    ctx->r14 = ADD32(ctx->r14, 0X1EC0);
    // 0x802C6664: lui         $t7, 0xFA00
    ctx->r15 = S32(0XFA00 << 16);
    // 0x802C6668: sw          $t6, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r14;
    // 0x802C666C: sw          $s0, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r16;
    // 0x802C6670: sw          $t7, 0x8($v0)
    MEM_W(0X8, ctx->r2) = ctx->r15;
    // 0x802C6674: lui         $v1, 0x802C
    ctx->r3 = S32(0X802C << 16);
    // 0x802C6678: lw          $v1, 0x7534($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X7534);
    // 0x802C667C: lui         $at, 0xFF
    ctx->r1 = S32(0XFF << 16);
    // 0x802C6680: lui         $s1, 0x802C
    ctx->r17 = S32(0X802C << 16);
    // 0x802C6684: andi        $t8, $v1, 0xFF
    ctx->r24 = ctx->r3 & 0XFF;
    // 0x802C6688: sll         $t9, $t8, 24
    ctx->r25 = S32(ctx->r24 << 24);
    // 0x802C668C: or          $t1, $t9, $at
    ctx->r9 = ctx->r25 | ctx->r1;
    // 0x802C6690: sll         $t2, $t8, 8
    ctx->r10 = S32(ctx->r24 << 8);
    // 0x802C6694: or          $t3, $t1, $t2
    ctx->r11 = ctx->r9 | ctx->r10;
    // 0x802C6698: ori         $t4, $t3, 0xFF
    ctx->r12 = ctx->r11 | 0XFF;
    // 0x802C669C: addiu       $s1, $s1, 0x7040
    ctx->r17 = ADD32(ctx->r17, 0X7040);
    // 0x802C66A0: sw          $t4, 0xC($v0)
    MEM_W(0XC, ctx->r2) = ctx->r12;
    // 0x802C66A4: lw          $t5, 0x0($s1)
    ctx->r13 = MEM_W(ctx->r17, 0X0);
    // 0x802C66A8: lui         $t0, 0x802C
    ctx->r8 = S32(0X802C << 16);
    // 0x802C66AC: addiu       $t0, $t0, 0x74F0
    ctx->r8 = ADD32(ctx->r8, 0X74F0);
    // 0x802C66B0: sll         $t6, $t5, 1
    ctx->r14 = S32(ctx->r13 << 1);
    // 0x802C66B4: addu        $t7, $t0, $t6
    ctx->r15 = ADD32(ctx->r8, ctx->r14);
    // 0x802C66B8: lh          $t8, 0x0($t7)
    ctx->r24 = MEM_H(ctx->r15, 0X0);
    // 0x802C66BC: lui         $at, 0xE400
    ctx->r1 = S32(0XE400 << 16);
    // 0x802C66C0: addiu       $a0, $v0, 0x28
    ctx->r4 = ADD32(ctx->r2, 0X28);
    // 0x802C66C4: addiu       $t9, $t8, 0x47
    ctx->r25 = ADD32(ctx->r24, 0X47);
    // 0x802C66C8: sll         $t1, $t9, 2
    ctx->r9 = S32(ctx->r25 << 2);
    // 0x802C66CC: andi        $t2, $t1, 0xFFF
    ctx->r10 = ctx->r9 & 0XFFF;
    // 0x802C66D0: sll         $t3, $t2, 12
    ctx->r11 = S32(ctx->r10 << 12);
    // 0x802C66D4: or          $t4, $t3, $at
    ctx->r12 = ctx->r11 | ctx->r1;
    // 0x802C66D8: ori         $t5, $t4, 0x160
    ctx->r13 = ctx->r12 | 0X160;
    // 0x802C66DC: sw          $t5, 0x10($v0)
    MEM_W(0X10, ctx->r2) = ctx->r13;
    // 0x802C66E0: lw          $t6, 0x0($s1)
    ctx->r14 = MEM_W(ctx->r17, 0X0);
    // 0x802C66E4: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C66E8: addiu       $a2, $zero, 0xFF
    ctx->r6 = ADD32(0, 0XFF);
    // 0x802C66EC: sll         $t7, $t6, 1
    ctx->r15 = S32(ctx->r14 << 1);
    // 0x802C66F0: addu        $t8, $t0, $t7
    ctx->r24 = ADD32(ctx->r8, ctx->r15);
    // 0x802C66F4: lh          $t9, 0x0($t8)
    ctx->r25 = MEM_H(ctx->r24, 0X0);
    // 0x802C66F8: lui         $t8, 0x400
    ctx->r24 = S32(0X400 << 16);
    // 0x802C66FC: ori         $t8, $t8, 0x400
    ctx->r24 = ctx->r24 | 0X400;
    // 0x802C6700: addiu       $t1, $t9, 0x8
    ctx->r9 = ADD32(ctx->r25, 0X8);
    // 0x802C6704: sll         $t2, $t1, 2
    ctx->r10 = S32(ctx->r9 << 2);
    // 0x802C6708: andi        $t3, $t2, 0xFFF
    ctx->r11 = ctx->r10 & 0XFFF;
    // 0x802C670C: sll         $t4, $t3, 12
    ctx->r12 = S32(ctx->r11 << 12);
    // 0x802C6710: ori         $t5, $t4, 0xC0
    ctx->r13 = ctx->r12 | 0XC0;
    // 0x802C6714: lui         $t7, 0xB200
    ctx->r15 = S32(0XB200 << 16);
    // 0x802C6718: lui         $t6, 0xB300
    ctx->r14 = S32(0XB300 << 16);
    // 0x802C671C: sw          $t6, 0x18($v0)
    MEM_W(0X18, ctx->r2) = ctx->r14;
    // 0x802C6720: sw          $t7, 0x20($v0)
    MEM_W(0X20, ctx->r2) = ctx->r15;
    // 0x802C6724: sw          $t5, 0x14($v0)
    MEM_W(0X14, ctx->r2) = ctx->r13;
    // 0x802C6728: sw          $t8, 0x24($v0)
    MEM_W(0X24, ctx->r2) = ctx->r24;
    // 0x802C672C: sw          $zero, 0x1C($v0)
    MEM_W(0X1C, ctx->r2) = 0;
    // 0x802C6730: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C6734: addiu       $t5, $zero, 0xFF
    ctx->r13 = ADD32(0, 0XFF);
    // 0x802C6738: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C673C: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C6740: addiu       $t4, $zero, 0xFF
    ctx->r12 = ADD32(0, 0XFF);
    // 0x802C6744: addiu       $t3, $zero, 0xFF
    ctx->r11 = ADD32(0, 0XFF);
    // 0x802C6748: addiu       $t2, $zero, 0xFF
    ctx->r10 = ADD32(0, 0XFF);
    // 0x802C674C: addiu       $t1, $zero, 0xFF
    ctx->r9 = ADD32(0, 0XFF);
    // 0x802C6750: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C6754: sw          $t9, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r25;
    // 0x802C6758: sw          $t9, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r25;
    // 0x802C675C: sw          $t1, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r9;
    // 0x802C6760: sw          $t2, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r10;
    // 0x802C6764: sw          $t3, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r11;
    // 0x802C6768: sw          $t4, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r12;
    // 0x802C676C: sw          $t6, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r14;
    // 0x802C6770: sw          $t7, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r15;
    // 0x802C6774: sw          $t5, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r13;
    // 0x802C6778: sw          $t8, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r24;
    // 0x802C677C: jal         0x801E946C
    // 0x802C6780: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    func_801E946C(rdram, ctx);
        goto after_10;
    // 0x802C6780: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    after_10:
    // 0x802C6784: addiu       $t1, $zero, 0x18
    ctx->r9 = ADD32(0, 0X18);
    // 0x802C6788: sw          $t1, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r9;
    // 0x802C678C: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C6790: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C6794: addiu       $a2, $zero, 0x6
    ctx->r6 = ADD32(0, 0X6);
    // 0x802C6798: addiu       $a3, $zero, 0x77
    ctx->r7 = ADD32(0, 0X77);
    // 0x802C679C: jal         0x801E3EE0
    // 0x802C67A0: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    func_801E3EE0(rdram, ctx);
        goto after_11;
    // 0x802C67A0: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    after_11:
    // 0x802C67A4: lw          $t2, 0x0($s1)
    ctx->r10 = MEM_W(ctx->r17, 0X0);
    // 0x802C67A8: lui         $t4, 0x802C
    ctx->r12 = S32(0X802C << 16);
    // 0x802C67AC: lui         $t6, 0x801D
    ctx->r14 = S32(0X801D << 16);
    // 0x802C67B0: sll         $t3, $t2, 2
    ctx->r11 = S32(ctx->r10 << 2);
    // 0x802C67B4: addu        $t4, $t4, $t3
    ctx->r12 = ADD32(ctx->r12, ctx->r11);
    // 0x802C67B8: lw          $t4, 0x74F8($t4)
    ctx->r12 = MEM_W(ctx->r12, 0X74F8);
    // 0x802C67BC: addiu       $t6, $t6, -0x4D68
    ctx->r14 = ADD32(ctx->r14, -0X4D68);
    // 0x802C67C0: addiu       $t7, $zero, 0xCB
    ctx->r15 = ADD32(0, 0XCB);
    // 0x802C67C4: sll         $t5, $t4, 3
    ctx->r13 = S32(ctx->r12 << 3);
    // 0x802C67C8: subu        $t5, $t5, $t4
    ctx->r13 = SUB32(ctx->r13, ctx->r12);
    // 0x802C67CC: sll         $t5, $t5, 1
    ctx->r13 = S32(ctx->r13 << 1);
    // 0x802C67D0: addu        $a2, $t5, $t6
    ctx->r6 = ADD32(ctx->r13, ctx->r14);
    // 0x802C67D4: sw          $t7, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r15;
    // 0x802C67D8: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C67DC: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    { extern void wr64_change_name_preview_name(uint8_t*, recomp_context*); wr64_change_name_preview_name(rdram, ctx); }
    // 0x802C67E0: jal         0x801E9858
    // 0x802C67E4: addiu       $a3, $a3, 0x11C
    ctx->r7 = ADD32(ctx->r7, 0X11C);
    func_801E9858(rdram, ctx);
        goto after_12;
    // 0x802C67E4: addiu       $a3, $a3, 0x11C
    ctx->r7 = ADD32(ctx->r7, 0X11C);
    after_12:
    // 0x802C67E8: lui         $a2, 0x802C
    ctx->r6 = S32(0X802C << 16);
    // 0x802C67EC: addiu       $t8, $zero, 0x62
    ctx->r24 = ADD32(0, 0X62);
    // 0x802C67F0: sw          $t8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r24;
    // 0x802C67F4: addiu       $a2, $a2, 0x7548
    ctx->r6 = ADD32(ctx->r6, 0X7548);
    // 0x802C67F8: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C67FC: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C6800: jal         0x801E9858
    // 0x802C6804: addiu       $a3, $zero, 0x1F
    ctx->r7 = ADD32(0, 0X1F);
    func_801E9858(rdram, ctx);
        goto after_13;
    // 0x802C6804: addiu       $a3, $zero, 0x1F
    ctx->r7 = ADD32(0, 0X1F);
    after_13:
    // 0x802C6808: lui         $s0, 0x802C
    ctx->r16 = S32(0X802C << 16);
    // 0x802C680C: or          $s2, $v0, $zero
    ctx->r18 = ctx->r2 | 0;
    // 0x802C6810: addiu       $s0, $s0, 0x7054
    ctx->r16 = ADD32(ctx->r16, 0X7054);
    // 0x802C6814: or          $s1, $zero, $zero
    ctx->r17 = 0 | 0;
    // 0x802C6818: addiu       $s4, $zero, 0x1
    ctx->r20 = ADD32(0, 0X1);
    // 0x802C681C: addiu       $s3, $zero, 0x7
    ctx->r19 = ADD32(0, 0X7);
L_802C6820:
    // 0x802C6820: lbu         $v0, 0x0($s0)
    ctx->r2 = MEM_BU(ctx->r16, 0X0);
    // 0x802C6824: lui         $t1, 0x801D
    ctx->r9 = S32(0X801D << 16);
    // 0x802C6828: andi        $t9, $v0, 0x2
    ctx->r25 = ctx->r2 & 0X2;
    // 0x802C682C: beql        $t9, $zero, L_802C6914
    if (ctx->r25 == 0) {
        // 0x802C6830: addiu       $s1, $s1, 0x1
        ctx->r17 = ADD32(ctx->r17, 0X1);
            goto L_802C6914;
    }
    goto skip_0;
    // 0x802C6830: addiu       $s1, $s1, 0x1
    ctx->r17 = ADD32(ctx->r17, 0X1);
    skip_0:
    // 0x802C6834: lw          $t1, -0x19C0($t1)
    ctx->r9 = MEM_W(ctx->r9, -0X19C0);
    // 0x802C6838: andi        $t5, $v0, 0x8
    ctx->r13 = ctx->r2 & 0X8;
    // 0x802C683C: bne         $s4, $t1, L_802C6868
    if (ctx->r20 != ctx->r9) {
        // 0x802C6840: nop
    
            goto L_802C6868;
    }
    // 0x802C6840: nop

    // 0x802C6844: lui         $t2, 0x802C
    ctx->r10 = S32(0X802C << 16);
    // 0x802C6848: lw          $t2, 0x753C($t2)
    ctx->r10 = MEM_W(ctx->r10, 0X753C);
    // 0x802C684C: lui         $t4, 0x802C
    ctx->r12 = S32(0X802C << 16);
    // 0x802C6850: lw          $t4, 0x7538($t4)
    ctx->r12 = MEM_W(ctx->r12, 0X7538);
    // 0x802C6854: multu       $t2, $s3
    result = U64(U32(ctx->r10)) * U64(U32(ctx->r19)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x802C6858: mflo        $t3
    ctx->r11 = lo;
    // 0x802C685C: addu        $v1, $t3, $t4
    ctx->r3 = ADD32(ctx->r11, ctx->r12);
    // 0x802C6860: beql        $s1, $v1, L_802C6914
    if (ctx->r17 == ctx->r3) {
        // 0x802C6864: addiu       $s1, $s1, 0x1
        ctx->r17 = ADD32(ctx->r17, 0X1);
            goto L_802C6914;
    }
    goto skip_1;
    // 0x802C6864: addiu       $s1, $s1, 0x1
    ctx->r17 = ADD32(ctx->r17, 0X1);
    skip_1:
L_802C6868:
    // 0x802C6868: beq         $t5, $zero, L_802C687C
    if (ctx->r13 == 0) {
        // 0x802C686C: andi        $t3, $v0, 0x4
        ctx->r11 = ctx->r2 & 0X4;
            goto L_802C687C;
    }
    // 0x802C686C: andi        $t3, $v0, 0x4
    ctx->r11 = ctx->r2 & 0X4;
    // 0x802C6870: lh          $a3, 0x4($s0)
    ctx->r7 = MEM_H(ctx->r16, 0X4);
    // 0x802C6874: b           L_802C68D4
    // 0x802C6878: lh          $t0, 0x6($s0)
    ctx->r8 = MEM_H(ctx->r16, 0X6);
        goto L_802C68D4;
    // 0x802C6878: lh          $t0, 0x6($s0)
    ctx->r8 = MEM_H(ctx->r16, 0X6);
L_802C687C:
    // 0x802C687C: div         $zero, $s1, $s3
    lo = S32(S64(S32(ctx->r17)) / S64(S32(ctx->r19))); hi = S32(S64(S32(ctx->r17)) % S64(S32(ctx->r19)));
    // 0x802C6880: lh          $t6, 0x4($s0)
    ctx->r14 = MEM_H(ctx->r16, 0X4);
    // 0x802C6884: lh          $t9, 0x6($s0)
    ctx->r25 = MEM_H(ctx->r16, 0X6);
    // 0x802C6888: mfhi        $t7
    ctx->r15 = hi;
    // 0x802C688C: mflo        $t1
    ctx->r9 = lo;
    // 0x802C6890: sll         $t8, $t7, 4
    ctx->r24 = S32(ctx->r15 << 4);
    // 0x802C6894: sll         $t2, $t1, 4
    ctx->r10 = S32(ctx->r9 << 4);
    // 0x802C6898: addu        $t8, $t8, $t7
    ctx->r24 = ADD32(ctx->r24, ctx->r15);
    // 0x802C689C: subu        $t2, $t2, $t1
    ctx->r10 = SUB32(ctx->r10, ctx->r9);
    // 0x802C68A0: addu        $a3, $t6, $t8
    ctx->r7 = ADD32(ctx->r14, ctx->r24);
    // 0x802C68A4: addu        $t0, $t9, $t2
    ctx->r8 = ADD32(ctx->r25, ctx->r10);
    // 0x802C68A8: addiu       $a3, $a3, 0x21
    ctx->r7 = ADD32(ctx->r7, 0X21);
    // 0x802C68AC: bne         $s3, $zero, L_802C68B8
    if (ctx->r19 != 0) {
        // 0x802C68B0: nop
    
            goto L_802C68B8;
    }
    // 0x802C68B0: nop

    // 0x802C68B4: break       7
    do_break(2150394036);
L_802C68B8:
    // 0x802C68B8: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x802C68BC: bne         $s3, $at, L_802C68D0
    if (ctx->r19 != ctx->r1) {
        // 0x802C68C0: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_802C68D0;
    }
    // 0x802C68C0: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x802C68C4: bne         $s1, $at, L_802C68D0
    if (ctx->r17 != ctx->r1) {
        // 0x802C68C8: nop
    
            goto L_802C68D0;
    }
    // 0x802C68C8: nop

    // 0x802C68CC: break       6
    do_break(2150394060);
L_802C68D0:
    // 0x802C68D0: addiu       $t0, $t0, 0x74
    ctx->r8 = ADD32(ctx->r8, 0X74);
L_802C68D4:
    // 0x802C68D4: beq         $t3, $zero, L_802C68FC
    if (ctx->r11 == 0) {
        // 0x802C68D8: or          $a0, $s2, $zero
        ctx->r4 = ctx->r18 | 0;
            goto L_802C68FC;
    }
    // 0x802C68D8: or          $a0, $s2, $zero
    ctx->r4 = ctx->r18 | 0;
    // 0x802C68DC: lw          $a2, 0x18($s0)
    ctx->r6 = MEM_W(ctx->r16, 0X18);
    // 0x802C68E0: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    // 0x802C68E4: sw          $t0, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r8;
    // 0x802C68E8: or          $a0, $s2, $zero
    ctx->r4 = ctx->r18 | 0;
    // 0x802C68EC: jal         0x801E3EE0
    // 0x802C68F0: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_801E3EE0(rdram, ctx);
        goto after_14;
    // 0x802C68F0: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_14:
    // 0x802C68F4: b           L_802C6910
    // 0x802C68F8: or          $s2, $v0, $zero
    ctx->r18 = ctx->r2 | 0;
        goto L_802C6910;
    // 0x802C68F8: or          $s2, $v0, $zero
    ctx->r18 = ctx->r2 | 0;
L_802C68FC:
    // 0x802C68FC: lhu         $a1, 0x2($s0)
    ctx->r5 = MEM_HU(ctx->r16, 0X2);
    // 0x802C6900: sw          $t0, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r8;
    // 0x802C6904: jal         0x801E9858
    // 0x802C6908: addiu       $a2, $s0, 0xC
    ctx->r6 = ADD32(ctx->r16, 0XC);
    func_801E9858(rdram, ctx);
        goto after_15;
    // 0x802C6908: addiu       $a2, $s0, 0xC
    ctx->r6 = ADD32(ctx->r16, 0XC);
    after_15:
    // 0x802C690C: or          $s2, $v0, $zero
    ctx->r18 = ctx->r2 | 0;
L_802C6910:
    // 0x802C6910: addiu       $s1, $s1, 0x1
    ctx->r17 = ADD32(ctx->r17, 0X1);
L_802C6914:
    // 0x802C6914: addiu       $at, $zero, 0x2A
    ctx->r1 = ADD32(0, 0X2A);
    // 0x802C6918: bne         $s1, $at, L_802C6820
    if (ctx->r17 != ctx->r1) {
        // 0x802C691C: addiu       $s0, $s0, 0x1C
        ctx->r16 = ADD32(ctx->r16, 0X1C);
            goto L_802C6820;
    }
    // 0x802C691C: addiu       $s0, $s0, 0x1C
    ctx->r16 = ADD32(ctx->r16, 0X1C);
    // 0x802C6920: addiu       $t4, $zero, 0xFF
    ctx->r12 = ADD32(0, 0XFF);
    // 0x802C6924: addiu       $t5, $zero, 0xFF
    ctx->r13 = ADD32(0, 0XFF);
    // 0x802C6928: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C692C: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C6930: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C6934: addiu       $t1, $zero, 0xFF
    ctx->r9 = ADD32(0, 0XFF);
    // 0x802C6938: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C693C: addiu       $t2, $zero, 0xFF
    ctx->r10 = ADD32(0, 0XFF);
    // 0x802C6940: addiu       $t3, $zero, 0xFF
    ctx->r11 = ADD32(0, 0XFF);
    // 0x802C6944: sw          $t3, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r11;
    // 0x802C6948: sw          $t2, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r10;
    // 0x802C694C: sw          $t9, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r25;
    // 0x802C6950: sw          $t1, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r9;
    // 0x802C6954: sw          $t8, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r24;
    // 0x802C6958: sw          $t6, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r14;
    // 0x802C695C: sw          $t7, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r15;
    // 0x802C6960: sw          $t5, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r13;
    // 0x802C6964: sw          $t4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r12;
    // 0x802C6968: sw          $t4, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r12;
    // 0x802C696C: or          $a0, $s2, $zero
    ctx->r4 = ctx->r18 | 0;
    // 0x802C6970: addiu       $a1, $zero, 0x6
    ctx->r5 = ADD32(0, 0X6);
    // 0x802C6974: addiu       $a2, $zero, 0xFF
    ctx->r6 = ADD32(0, 0XFF);
    // 0x802C6978: jal         0x801E946C
    // 0x802C697C: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    func_801E946C(rdram, ctx);
        goto after_16;
    // 0x802C697C: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    after_16:
    // 0x802C6980: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x802C6984: lw          $v1, -0x19C0($v1)
    ctx->r3 = MEM_W(ctx->r3, -0X19C0);
    // 0x802C6988: or          $s2, $v0, $zero
    ctx->r18 = ctx->r2 | 0;
    // 0x802C698C: lui         $t5, 0x802C
    ctx->r13 = S32(0X802C << 16);
    // 0x802C6990: bne         $s4, $v1, L_802C6A88
    if (ctx->r20 != ctx->r3) {
        // 0x802C6994: nop
    
            goto L_802C6A88;
    }
    // 0x802C6994: nop

    // 0x802C6998: lw          $t5, 0x753C($t5)
    ctx->r13 = MEM_W(ctx->r13, 0X753C);
    // 0x802C699C: lui         $t6, 0x802C
    ctx->r14 = S32(0X802C << 16);
    // 0x802C69A0: lw          $t6, 0x7538($t6)
    ctx->r14 = MEM_W(ctx->r14, 0X7538);
    // 0x802C69A4: multu       $t5, $s3
    result = U64(U32(ctx->r13)) * U64(U32(ctx->r19)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x802C69A8: lui         $t1, 0x802C
    ctx->r9 = S32(0X802C << 16);
    // 0x802C69AC: addiu       $t1, $t1, 0x7054
    ctx->r9 = ADD32(ctx->r9, 0X7054);
    // 0x802C69B0: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C69B4: mflo        $t7
    ctx->r15 = lo;
    // 0x802C69B8: addu        $v1, $t7, $t6
    ctx->r3 = ADD32(ctx->r15, ctx->r14);
    // 0x802C69BC: sll         $t8, $v1, 3
    ctx->r24 = S32(ctx->r3 << 3);
    // 0x802C69C0: subu        $t8, $t8, $v1
    ctx->r24 = SUB32(ctx->r24, ctx->r3);
    // 0x802C69C4: sll         $t8, $t8, 2
    ctx->r24 = S32(ctx->r24 << 2);
    // 0x802C69C8: addu        $v0, $t8, $t1
    ctx->r2 = ADD32(ctx->r24, ctx->r9);
    // 0x802C69CC: lbu         $a0, 0x0($v0)
    ctx->r4 = MEM_BU(ctx->r2, 0X0);
    // 0x802C69D0: addiu       $a2, $v0, 0xC
    ctx->r6 = ADD32(ctx->r2, 0XC);
    // 0x802C69D4: andi        $t9, $a0, 0x8
    ctx->r25 = ctx->r4 & 0X8;
    // 0x802C69D8: beq         $t9, $zero, L_802C69EC
    if (ctx->r25 == 0) {
        // 0x802C69DC: andi        $t8, $a0, 0x4
        ctx->r24 = ctx->r4 & 0X4;
            goto L_802C69EC;
    }
    // 0x802C69DC: andi        $t8, $a0, 0x4
    ctx->r24 = ctx->r4 & 0X4;
    // 0x802C69E0: lh          $a3, 0x4($v0)
    ctx->r7 = MEM_H(ctx->r2, 0X4);
    // 0x802C69E4: b           L_802C6A44
    // 0x802C69E8: lh          $t0, 0x6($v0)
    ctx->r8 = MEM_H(ctx->r2, 0X6);
        goto L_802C6A44;
    // 0x802C69E8: lh          $t0, 0x6($v0)
    ctx->r8 = MEM_H(ctx->r2, 0X6);
L_802C69EC:
    // 0x802C69EC: div         $zero, $v1, $s3
    lo = S32(S64(S32(ctx->r3)) / S64(S32(ctx->r19))); hi = S32(S64(S32(ctx->r3)) % S64(S32(ctx->r19)));
    // 0x802C69F0: lh          $t2, 0x4($v0)
    ctx->r10 = MEM_H(ctx->r2, 0X4);
    // 0x802C69F4: lh          $t5, 0x6($v0)
    ctx->r13 = MEM_H(ctx->r2, 0X6);
    // 0x802C69F8: mfhi        $t3
    ctx->r11 = hi;
    // 0x802C69FC: mflo        $t7
    ctx->r15 = lo;
    // 0x802C6A00: sll         $t4, $t3, 4
    ctx->r12 = S32(ctx->r11 << 4);
    // 0x802C6A04: sll         $t6, $t7, 4
    ctx->r14 = S32(ctx->r15 << 4);
    // 0x802C6A08: addu        $t4, $t4, $t3
    ctx->r12 = ADD32(ctx->r12, ctx->r11);
    // 0x802C6A0C: subu        $t6, $t6, $t7
    ctx->r14 = SUB32(ctx->r14, ctx->r15);
    // 0x802C6A10: addu        $a3, $t2, $t4
    ctx->r7 = ADD32(ctx->r10, ctx->r12);
    // 0x802C6A14: addu        $t0, $t5, $t6
    ctx->r8 = ADD32(ctx->r13, ctx->r14);
    // 0x802C6A18: addiu       $a3, $a3, 0x21
    ctx->r7 = ADD32(ctx->r7, 0X21);
    // 0x802C6A1C: bne         $s3, $zero, L_802C6A28
    if (ctx->r19 != 0) {
        // 0x802C6A20: nop
    
            goto L_802C6A28;
    }
    // 0x802C6A20: nop

    // 0x802C6A24: break       7
    do_break(2150394404);
L_802C6A28:
    // 0x802C6A28: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x802C6A2C: bne         $s3, $at, L_802C6A40
    if (ctx->r19 != ctx->r1) {
        // 0x802C6A30: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_802C6A40;
    }
    // 0x802C6A30: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x802C6A34: bne         $v1, $at, L_802C6A40
    if (ctx->r3 != ctx->r1) {
        // 0x802C6A38: nop
    
            goto L_802C6A40;
    }
    // 0x802C6A38: nop

    // 0x802C6A3C: break       6
    do_break(2150394428);
L_802C6A40:
    // 0x802C6A40: addiu       $t0, $t0, 0x74
    ctx->r8 = ADD32(ctx->r8, 0X74);
L_802C6A44:
    // 0x802C6A44: beq         $t8, $zero, L_802C6A70
    if (ctx->r24 == 0) {
        // 0x802C6A48: or          $a0, $s2, $zero
        ctx->r4 = ctx->r18 | 0;
            goto L_802C6A70;
    }
    // 0x802C6A48: or          $a0, $s2, $zero
    ctx->r4 = ctx->r18 | 0;
    // 0x802C6A4C: or          $a0, $s2, $zero
    ctx->r4 = ctx->r18 | 0;
    // 0x802C6A50: lw          $a2, 0x18($v0)
    ctx->r6 = MEM_W(ctx->r2, 0X18);
    // 0x802C6A54: sw          $t0, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r8;
    // 0x802C6A58: jal         0x801E3EE0
    // 0x802C6A5C: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    func_801E3EE0(rdram, ctx);
        goto after_17;
    // 0x802C6A5C: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    after_17:
    // 0x802C6A60: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x802C6A64: lw          $v1, -0x19C0($v1)
    ctx->r3 = MEM_W(ctx->r3, -0X19C0);
    // 0x802C6A68: b           L_802C6A88
    // 0x802C6A6C: or          $s2, $v0, $zero
    ctx->r18 = ctx->r2 | 0;
        goto L_802C6A88;
    // 0x802C6A6C: or          $s2, $v0, $zero
    ctx->r18 = ctx->r2 | 0;
L_802C6A70:
    // 0x802C6A70: lhu         $a1, 0x2($v0)
    ctx->r5 = MEM_HU(ctx->r2, 0X2);
    // 0x802C6A74: jal         0x801E9858
    // 0x802C6A78: sw          $t0, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r8;
    func_801E9858(rdram, ctx);
        goto after_18;
    // 0x802C6A78: sw          $t0, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r8;
    after_18:
    // 0x802C6A7C: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x802C6A80: lw          $v1, -0x19C0($v1)
    ctx->r3 = MEM_W(ctx->r3, -0X19C0);
    // 0x802C6A84: or          $s2, $v0, $zero
    ctx->r18 = ctx->r2 | 0;
L_802C6A88:
    // 0x802C6A88: bne         $s4, $v1, L_802C6AB8
    if (ctx->r20 != ctx->r3) {
        // 0x802C6A8C: or          $a0, $s2, $zero
        ctx->r4 = ctx->r18 | 0;
            goto L_802C6AB8;
    }
    // 0x802C6A8C: or          $a0, $s2, $zero
    ctx->r4 = ctx->r18 | 0;
    // 0x802C6A90: lui         $a3, 0x802C
    ctx->r7 = S32(0X802C << 16);
    // 0x802C6A94: lw          $a3, 0x7568($a3)
    ctx->r7 = MEM_W(ctx->r7, 0X7568);
    // 0x802C6A98: lui         $a2, 0x802C
    ctx->r6 = S32(0X802C << 16);
    // 0x802C6A9C: addiu       $t1, $zero, 0x62
    ctx->r9 = ADD32(0, 0X62);
    // 0x802C6AA0: sw          $t1, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r9;
    // 0x802C6AA4: addiu       $a2, $a2, 0x7508
    ctx->r6 = ADD32(ctx->r6, 0X7508);
    // 0x802C6AA8: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C6AAC: jal         0x801E9858
    // 0x802C6AB0: addiu       $a3, $a3, 0x1F
    ctx->r7 = ADD32(ctx->r7, 0X1F);
    func_801E9858(rdram, ctx);
        goto after_19;
    // 0x802C6AB0: addiu       $a3, $a3, 0x1F
    ctx->r7 = ADD32(ctx->r7, 0X1F);
    after_19:
    // 0x802C6AB4: or          $s2, $v0, $zero
    ctx->r18 = ctx->r2 | 0;
L_802C6AB8:
    // 0x802C6AB8: lw          $ra, 0x54($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X54);
    // 0x802C6ABC: or          $v0, $s2, $zero
    ctx->r2 = ctx->r18 | 0;
    // 0x802C6AC0: lw          $s2, 0x48($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X48);
    // 0x802C6AC4: lw          $s0, 0x40($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X40);
    // 0x802C6AC8: lw          $s1, 0x44($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X44);
    // 0x802C6ACC: lw          $s3, 0x4C($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X4C);
    // 0x802C6AD0: lw          $s4, 0x50($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X50);
    // 0x802C6AD4: jr          $ra
    // 0x802C6AD8: addiu       $sp, $sp, 0x58
    ctx->r29 = ADD32(ctx->r29, 0X58);
    return;
    // 0x802C6AD8: addiu       $sp, $sp, 0x58
    ctx->r29 = ADD32(ctx->r29, 0X58);
;}
RECOMP_FUNC void func_i8_802C6ADC(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C6ADC: lui         $t6, 0x802C
    ctx->r14 = S32(0X802C << 16);
    // 0x802C6AE0: lw          $t6, 0x753C($t6)
    ctx->r14 = MEM_W(ctx->r14, 0X753C);
    // 0x802C6AE4: lui         $t8, 0x802C
    ctx->r24 = S32(0X802C << 16);
    // 0x802C6AE8: lw          $t8, 0x7538($t8)
    ctx->r24 = MEM_W(ctx->r24, 0X7538);
    // 0x802C6AEC: sll         $t7, $t6, 3
    ctx->r15 = S32(ctx->r14 << 3);
    // 0x802C6AF0: subu        $t7, $t7, $t6
    ctx->r15 = SUB32(ctx->r15, ctx->r14);
    // 0x802C6AF4: addu        $v0, $t7, $t8
    ctx->r2 = ADD32(ctx->r15, ctx->r24);
    // 0x802C6AF8: sll         $t9, $v0, 3
    ctx->r25 = S32(ctx->r2 << 3);
    // 0x802C6AFC: subu        $t9, $t9, $v0
    ctx->r25 = SUB32(ctx->r25, ctx->r2);
    // 0x802C6B00: lui         $t0, 0x802C
    ctx->r8 = S32(0X802C << 16);
    // 0x802C6B04: addiu       $t0, $t0, 0x7054
    ctx->r8 = ADD32(ctx->r8, 0X7054);
    // 0x802C6B08: sll         $t9, $t9, 2
    ctx->r25 = S32(ctx->r25 << 2);
    // 0x802C6B0C: addu        $a3, $t9, $t0
    ctx->r7 = ADD32(ctx->r25, ctx->r8);
    // 0x802C6B10: lbu         $t1, 0x1($a3)
    ctx->r9 = MEM_BU(ctx->r7, 0X1);
    // 0x802C6B14: addiu       $sp, $sp, -0x38
    ctx->r29 = ADD32(ctx->r29, -0X38);
    // 0x802C6B18: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x802C6B1C: sltiu       $at, $t1, 0x8
    ctx->r1 = ctx->r9 < 0X8 ? 1 : 0;
    // 0x802C6B20: beq         $at, $zero, L_802C6D48
    if (ctx->r1 == 0) {
        // 0x802C6B24: sll         $t1, $t1, 2
        ctx->r9 = S32(ctx->r9 << 2);
            goto L_802C6D48;
    }
    // 0x802C6B24: sll         $t1, $t1, 2
    ctx->r9 = S32(ctx->r9 << 2);
    // 0x802C6B28: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C6B2C: addu        $at, $at, $t1
    gpr jr_addend_802C6B34 = ctx->r9;
    ctx->r1 = ADD32(ctx->r1, ctx->r9);
    // 0x802C6B30: lw          $t1, 0x7510($at)
    ctx->r9 = ADD32(ctx->r1, 0X7510);
    // 0x802C6B34: jr          $t1
    // 0x802C6B38: nop

    switch (jr_addend_802C6B34 >> 2) {
        case 0: goto L_802C6B3C; break;
        case 1: goto L_802C6C94; break;
        case 2: goto L_802C6CA4; break;
        case 3: goto L_802C6B3C; break;
        case 4: goto L_802C6CE8; break;
        case 5: goto L_802C6CB4; break;
        case 6: goto L_802C6D04; break;
        case 7: goto L_802C6D40; break;
        default: switch_error(__func__, 0x802C6B34, 0x802C7510);
    }
    // 0x802C6B38: nop

L_802C6B3C:
    // 0x802C6B3C: addiu       $v1, $zero, 0x1
    ctx->r3 = ADD32(0, 0X1);
    // 0x802C6B40: lui         $a0, 0x802C
    ctx->r4 = S32(0X802C << 16);
    // 0x802C6B44: addiu       $a0, $a0, 0x7548
    ctx->r4 = ADD32(ctx->r4, 0X7548);
    // 0x802C6B48: sw          $v1, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r3;
    // 0x802C6B4C: jal         0x800941D0
    // 0x802C6B50: sw          $a3, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r7;
    Strlen2(rdram, ctx);
        goto after_0;
    // 0x802C6B50: sw          $a3, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r7;
    after_0:
    // 0x802C6B54: slti        $at, $v0, 0xA
    ctx->r1 = SIGNED(ctx->r2) < 0XA ? 1 : 0;
    // 0x802C6B58: lw          $v1, 0x30($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X30);
    // 0x802C6B5C: bne         $at, $zero, L_802C6B6C
    if (ctx->r1 != 0) {
        // 0x802C6B60: lw          $a3, 0x1C($sp)
        ctx->r7 = MEM_W(ctx->r29, 0X1C);
            goto L_802C6B6C;
    }
    // 0x802C6B60: lw          $a3, 0x1C($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X1C);
    // 0x802C6B64: b           L_802C6B98
    // 0x802C6B68: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
        goto L_802C6B98;
    // 0x802C6B68: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
L_802C6B6C:
    // 0x802C6B6C: lui         $a0, 0x802C
    ctx->r4 = S32(0X802C << 16);
    // 0x802C6B70: addiu       $a0, $a0, 0x7548
    ctx->r4 = ADD32(ctx->r4, 0X7548);
    // 0x802C6B74: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C6B78: sw          $v1, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r3;
    // 0x802C6B7C: jal         0x802C6EB8
    // 0x802C6B80: sw          $a3, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r7;
    func_i8_802C6EB8(rdram, ctx);
        goto after_1;
    // 0x802C6B80: sw          $a3, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r7;
    after_1:
    // 0x802C6B84: slti        $at, $v0, 0x77
    ctx->r1 = SIGNED(ctx->r2) < 0X77 ? 1 : 0;
    // 0x802C6B88: lw          $v1, 0x30($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X30);
    // 0x802C6B8C: bne         $at, $zero, L_802C6B98
    if (ctx->r1 != 0) {
        // 0x802C6B90: lw          $a3, 0x1C($sp)
        ctx->r7 = MEM_W(ctx->r29, 0X1C);
            goto L_802C6B98;
    }
    // 0x802C6B90: lw          $a3, 0x1C($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X1C);
    // 0x802C6B94: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
L_802C6B98:
    // 0x802C6B98: beq         $v1, $zero, L_802C6D48
    if (ctx->r3 == 0) {
        // 0x802C6B9C: lui         $a0, 0x802C
        ctx->r4 = S32(0X802C << 16);
            goto L_802C6D48;
    }
    // 0x802C6B9C: lui         $a0, 0x802C
    ctx->r4 = S32(0X802C << 16);
    // 0x802C6BA0: lui         $a1, 0x802C
    ctx->r5 = S32(0X802C << 16);
    // 0x802C6BA4: addiu       $a1, $a1, 0x7558
    ctx->r5 = ADD32(ctx->r5, 0X7558);
    // 0x802C6BA8: addiu       $a0, $a0, 0x7548
    ctx->r4 = ADD32(ctx->r4, 0X7548);
    // 0x802C6BAC: addiu       $a2, $zero, 0xB
    ctx->r6 = ADD32(0, 0XB);
    // 0x802C6BB0: jal         0x802C6FD4
    // 0x802C6BB4: sw          $a3, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r7;
    func_i8_802C6FD4(rdram, ctx);
        goto after_2;
    // 0x802C6BB4: sw          $a3, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r7;
    after_2:
    // 0x802C6BB8: lui         $a2, 0x802C
    ctx->r6 = S32(0X802C << 16);
    // 0x802C6BBC: addiu       $a2, $a2, 0x7564
    ctx->r6 = ADD32(ctx->r6, 0X7564);
    // 0x802C6BC0: lw          $a1, 0x0($a2)
    ctx->r5 = MEM_W(ctx->r6, 0X0);
    // 0x802C6BC4: lui         $t2, 0x802C
    ctx->r10 = S32(0X802C << 16);
    // 0x802C6BC8: lw          $a3, 0x1C($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X1C);
    // 0x802C6BCC: addiu       $a0, $a1, 0x1
    ctx->r4 = ADD32(ctx->r5, 0X1);
    // 0x802C6BD0: slti        $at, $a0, 0xB
    ctx->r1 = SIGNED(ctx->r4) < 0XB ? 1 : 0;
    // 0x802C6BD4: beq         $at, $zero, L_802C6C0C
    if (ctx->r1 == 0) {
        // 0x802C6BD8: addiu       $t2, $t2, 0x7548
        ctx->r10 = ADD32(ctx->r10, 0X7548);
            goto L_802C6C0C;
    }
    // 0x802C6BD8: addiu       $t2, $t2, 0x7548
    ctx->r10 = ADD32(ctx->r10, 0X7548);
    // 0x802C6BDC: lui         $t3, 0x802C
    ctx->r11 = S32(0X802C << 16);
    // 0x802C6BE0: addiu       $t3, $t3, 0x7558
    ctx->r11 = ADD32(ctx->r11, 0X7558);
    // 0x802C6BE4: addu        $v0, $a0, $t3
    ctx->r2 = ADD32(ctx->r4, ctx->r11);
    // 0x802C6BE8: addu        $v1, $a0, $t2
    ctx->r3 = ADD32(ctx->r4, ctx->r10);
    // 0x802C6BEC: lui         $a0, 0x802C
    ctx->r4 = S32(0X802C << 16);
    // 0x802C6BF0: addiu       $a0, $a0, 0x7563
    ctx->r4 = ADD32(ctx->r4, 0X7563);
L_802C6BF4:
    // 0x802C6BF4: lb          $t4, -0x1($v0)
    ctx->r12 = MEM_B(ctx->r2, -0X1);
    // 0x802C6BF8: addiu       $v0, $v0, 0x1
    ctx->r2 = ADD32(ctx->r2, 0X1);
    // 0x802C6BFC: sltu        $at, $v0, $a0
    ctx->r1 = ctx->r2 < ctx->r4 ? 1 : 0;
    // 0x802C6C00: addiu       $v1, $v1, 0x1
    ctx->r3 = ADD32(ctx->r3, 0X1);
    // 0x802C6C04: bne         $at, $zero, L_802C6BF4
    if (ctx->r1 != 0) {
        // 0x802C6C08: sb          $t4, -0x1($v1)
        MEM_B(-0X1, ctx->r3) = ctx->r12;
            goto L_802C6BF4;
    }
    // 0x802C6C08: sb          $t4, -0x1($v1)
    MEM_B(-0X1, ctx->r3) = ctx->r12;
L_802C6C0C:
    // 0x802C6C0C: lbu         $t5, 0x1($a3)
    ctx->r13 = MEM_BU(ctx->r7, 0X1);
    // 0x802C6C10: lui         $a0, 0x802C
    ctx->r4 = S32(0X802C << 16);
    // 0x802C6C14: addiu       $a0, $a0, 0x7548
    ctx->r4 = ADD32(ctx->r4, 0X7548);
    // 0x802C6C18: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x802C6C1C: bne         $t5, $at, L_802C6C30
    if (ctx->r13 != ctx->r1) {
        // 0x802C6C20: addu        $v0, $a0, $a1
        ctx->r2 = ADD32(ctx->r4, ctx->r5);
            goto L_802C6C30;
    }
    // 0x802C6C20: addu        $v0, $a0, $a1
    ctx->r2 = ADD32(ctx->r4, ctx->r5);
    // 0x802C6C24: addiu       $t6, $zero, 0x20
    ctx->r14 = ADD32(0, 0X20);
    // 0x802C6C28: b           L_802C6C38
    // 0x802C6C2C: sb          $t6, 0x0($v0)
    MEM_B(0X0, ctx->r2) = ctx->r14;
        goto L_802C6C38;
    // 0x802C6C2C: sb          $t6, 0x0($v0)
    MEM_B(0X0, ctx->r2) = ctx->r14;
L_802C6C30:
    // 0x802C6C30: lb          $t7, 0xC($a3)
    ctx->r15 = MEM_B(ctx->r7, 0XC);
    // 0x802C6C34: sb          $t7, 0x0($v0)
    MEM_B(0X0, ctx->r2) = ctx->r15;
L_802C6C38:
    // 0x802C6C38: jal         0x802C6EB8
    // 0x802C6C3C: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    func_i8_802C6EB8(rdram, ctx);
        goto after_3;
    // 0x802C6C3C: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    after_3:
    // 0x802C6C40: lui         $a2, 0x802C
    ctx->r6 = S32(0X802C << 16);
    // 0x802C6C44: slti        $at, $v0, 0x7C
    ctx->r1 = SIGNED(ctx->r2) < 0X7C ? 1 : 0;
    // 0x802C6C48: bne         $at, $zero, L_802C6C70
    if (ctx->r1 != 0) {
        // 0x802C6C4C: addiu       $a2, $a2, 0x7564
        ctx->r6 = ADD32(ctx->r6, 0X7564);
            goto L_802C6C70;
    }
    // 0x802C6C4C: addiu       $a2, $a2, 0x7564
    ctx->r6 = ADD32(ctx->r6, 0X7564);
    // 0x802C6C50: lui         $a0, 0x802C
    ctx->r4 = S32(0X802C << 16);
    // 0x802C6C54: lui         $a1, 0x802C
    ctx->r5 = S32(0X802C << 16);
    // 0x802C6C58: addiu       $a1, $a1, 0x7548
    ctx->r5 = ADD32(ctx->r5, 0X7548);
    // 0x802C6C5C: addiu       $a0, $a0, 0x7558
    ctx->r4 = ADD32(ctx->r4, 0X7558);
    // 0x802C6C60: jal         0x802C6FD4
    // 0x802C6C64: addiu       $a2, $zero, 0xB
    ctx->r6 = ADD32(0, 0XB);
    func_i8_802C6FD4(rdram, ctx);
        goto after_4;
    // 0x802C6C64: addiu       $a2, $zero, 0xB
    ctx->r6 = ADD32(0, 0XB);
    after_4:
    // 0x802C6C68: b           L_802C6D4C
    // 0x802C6C6C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_802C6D4C;
    // 0x802C6C6C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C6C70:
    // 0x802C6C70: lw          $a1, 0x0($a2)
    ctx->r5 = MEM_W(ctx->r6, 0X0);
    // 0x802C6C74: lui         $t8, 0x802C
    ctx->r24 = S32(0X802C << 16);
    // 0x802C6C78: addu        $t8, $t8, $a1
    ctx->r24 = ADD32(ctx->r24, ctx->r5);
    // 0x802C6C7C: lb          $t8, 0x7558($t8)
    ctx->r24 = MEM_B(ctx->r24, 0X7558);
    // 0x802C6C80: addiu       $t9, $a1, 0x1
    ctx->r25 = ADD32(ctx->r5, 0X1);
    // 0x802C6C84: bnel        $t8, $zero, L_802C6D4C
    if (ctx->r24 != 0) {
        // 0x802C6C88: lw          $ra, 0x14($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X14);
            goto L_802C6D4C;
    }
    goto skip_0;
    // 0x802C6C88: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    skip_0:
    // 0x802C6C8C: b           L_802C6D48
    // 0x802C6C90: sw          $t9, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r25;
        goto L_802C6D48;
    // 0x802C6C90: sw          $t9, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r25;
L_802C6C94:
    // 0x802C6C94: jal         0x802C6D58
    // 0x802C6C98: nop

    func_i8_802C6D58(rdram, ctx);
        goto after_5;
    // 0x802C6C98: nop

    after_5:
    // 0x802C6C9C: b           L_802C6D4C
    // 0x802C6CA0: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_802C6D4C;
    // 0x802C6CA0: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C6CA4:
    // 0x802C6CA4: jal         0x802C6DA8
    // 0x802C6CA8: nop

    func_i8_802C6DA8(rdram, ctx);
        goto after_6;
    // 0x802C6CA8: nop

    after_6:
    // 0x802C6CAC: b           L_802C6D4C
    // 0x802C6CB0: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_802C6D4C;
    // 0x802C6CB0: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C6CB4:
    // 0x802C6CB4: lui         $a2, 0x802C
    ctx->r6 = S32(0X802C << 16);
    // 0x802C6CB8: addiu       $a2, $a2, 0x7564
    ctx->r6 = ADD32(ctx->r6, 0X7564);
    // 0x802C6CBC: lw          $a1, 0x0($a2)
    ctx->r5 = MEM_W(ctx->r6, 0X0);
    // 0x802C6CC0: lui         $t0, 0x802C
    ctx->r8 = S32(0X802C << 16);
    // 0x802C6CC4: addu        $t0, $t0, $a1
    ctx->r8 = ADD32(ctx->r8, ctx->r5);
    // 0x802C6CC8: lb          $t0, 0x7548($t0)
    ctx->r8 = MEM_B(ctx->r8, 0X7548);
    // 0x802C6CCC: slti        $at, $a1, 0xA
    ctx->r1 = SIGNED(ctx->r5) < 0XA ? 1 : 0;
    // 0x802C6CD0: beql        $t0, $zero, L_802C6D4C
    if (ctx->r8 == 0) {
        // 0x802C6CD4: lw          $ra, 0x14($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X14);
            goto L_802C6D4C;
    }
    goto skip_1;
    // 0x802C6CD4: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    skip_1:
    // 0x802C6CD8: beq         $at, $zero, L_802C6D48
    if (ctx->r1 == 0) {
        // 0x802C6CDC: addiu       $t1, $a1, 0x1
        ctx->r9 = ADD32(ctx->r5, 0X1);
            goto L_802C6D48;
    }
    // 0x802C6CDC: addiu       $t1, $a1, 0x1
    ctx->r9 = ADD32(ctx->r5, 0X1);
    // 0x802C6CE0: b           L_802C6D48
    // 0x802C6CE4: sw          $t1, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r9;
        goto L_802C6D48;
    // 0x802C6CE4: sw          $t1, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r9;
L_802C6CE8:
    // 0x802C6CE8: lui         $a2, 0x802C
    ctx->r6 = S32(0X802C << 16);
    // 0x802C6CEC: addiu       $a2, $a2, 0x7564
    ctx->r6 = ADD32(ctx->r6, 0X7564);
    // 0x802C6CF0: lw          $a1, 0x0($a2)
    ctx->r5 = MEM_W(ctx->r6, 0X0);
    // 0x802C6CF4: blez        $a1, L_802C6D48
    if (SIGNED(ctx->r5) <= 0) {
        // 0x802C6CF8: addiu       $t2, $a1, -0x1
        ctx->r10 = ADD32(ctx->r5, -0X1);
            goto L_802C6D48;
    }
    // 0x802C6CF8: addiu       $t2, $a1, -0x1
    ctx->r10 = ADD32(ctx->r5, -0X1);
    // 0x802C6CFC: b           L_802C6D48
    // 0x802C6D00: sw          $t2, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r10;
        goto L_802C6D48;
    // 0x802C6D00: sw          $t2, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r10;
L_802C6D04:
    // 0x802C6D04: lui         $t3, 0x802C
    ctx->r11 = S32(0X802C << 16);
    // 0x802C6D08: lw          $t3, 0x7040($t3)
    ctx->r11 = MEM_W(ctx->r11, 0X7040);
    // 0x802C6D0C: lui         $t5, 0x802C
    ctx->r13 = S32(0X802C << 16);
    // 0x802C6D10: lui         $t7, 0x800E
    ctx->r15 = S32(0X800E << 16);
    // 0x802C6D14: sll         $t4, $t3, 2
    ctx->r12 = S32(ctx->r11 << 2);
    // 0x802C6D18: addu        $t5, $t5, $t4
    ctx->r13 = ADD32(ctx->r13, ctx->r12);
    // 0x802C6D1C: lw          $t5, 0x74F8($t5)
    ctx->r13 = MEM_W(ctx->r13, 0X74F8);
    // 0x802C6D20: addiu       $t7, $t7, -0x56B0
    ctx->r15 = ADD32(ctx->r15, -0X56B0);
    // 0x802C6D24: sll         $t6, $t5, 3
    ctx->r14 = S32(ctx->r13 << 3);
    // 0x802C6D28: subu        $t6, $t6, $t5
    ctx->r14 = SUB32(ctx->r14, ctx->r13);
    // 0x802C6D2C: sll         $t6, $t6, 1
    ctx->r14 = S32(ctx->r14 << 1);
    // 0x802C6D30: jal         0x802C6E68
    // 0x802C6D34: addu        $a0, $t6, $t7
    ctx->r4 = ADD32(ctx->r14, ctx->r15);
    func_i8_802C6E68(rdram, ctx);
        goto after_7;
    // 0x802C6D34: addu        $a0, $t6, $t7
    ctx->r4 = ADD32(ctx->r14, ctx->r15);
    after_7:
    // 0x802C6D38: b           L_802C6D4C
    // 0x802C6D3C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_802C6D4C;
    // 0x802C6D3C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C6D40:
    // 0x802C6D40: jal         0x802C6E00
    // 0x802C6D44: nop

    func_i8_802C6E00(rdram, ctx);
        goto after_8;
    // 0x802C6D44: nop

    after_8:
L_802C6D48:
    // 0x802C6D48: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C6D4C:
    // 0x802C6D4C: addiu       $sp, $sp, 0x38
    ctx->r29 = ADD32(ctx->r29, 0X38);
    // 0x802C6D50: jr          $ra
    // 0x802C6D54: nop

    return;
    // 0x802C6D54: nop

;}
RECOMP_FUNC void func_i8_802C6D58(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C6D58: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C6D5C: sw          $zero, 0x7564($at)
    MEM_W(0X7564, ctx->r1) = 0;
    // 0x802C6D60: lui         $v1, 0x802C
    ctx->r3 = S32(0X802C << 16);
    // 0x802C6D64: addiu       $v1, $v1, 0x7549
    ctx->r3 = ADD32(ctx->r3, 0X7549);
    // 0x802C6D68: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C6D6C: sb          $zero, 0x7548($at)
    MEM_B(0X7548, ctx->r1) = 0;
    // 0x802C6D70: sb          $zero, 0x1($v1)
    MEM_B(0X1, ctx->r3) = 0;
    // 0x802C6D74: sb          $zero, 0x0($v1)
    MEM_B(0X0, ctx->r3) = 0;
    // 0x802C6D78: addiu       $v1, $v1, 0x2
    ctx->r3 = ADD32(ctx->r3, 0X2);
    // 0x802C6D7C: addiu       $v0, $zero, 0x3
    ctx->r2 = ADD32(0, 0X3);
    // 0x802C6D80: addiu       $a0, $zero, 0xB
    ctx->r4 = ADD32(0, 0XB);
L_802C6D84:
    // 0x802C6D84: addiu       $v0, $v0, 0x4
    ctx->r2 = ADD32(ctx->r2, 0X4);
    // 0x802C6D88: sb          $zero, 0x0($v1)
    MEM_B(0X0, ctx->r3) = 0;
    // 0x802C6D8C: sb          $zero, 0x1($v1)
    MEM_B(0X1, ctx->r3) = 0;
    // 0x802C6D90: sb          $zero, 0x2($v1)
    MEM_B(0X2, ctx->r3) = 0;
    // 0x802C6D94: sb          $zero, 0x3($v1)
    MEM_B(0X3, ctx->r3) = 0;
    // 0x802C6D98: bne         $v0, $a0, L_802C6D84
    if (ctx->r2 != ctx->r4) {
        // 0x802C6D9C: addiu       $v1, $v1, 0x4
        ctx->r3 = ADD32(ctx->r3, 0X4);
            goto L_802C6D84;
    }
    // 0x802C6D9C: addiu       $v1, $v1, 0x4
    ctx->r3 = ADD32(ctx->r3, 0X4);
    // 0x802C6DA0: jr          $ra
    // 0x802C6DA4: nop

    return;
    // 0x802C6DA4: nop

;}
RECOMP_FUNC void func_i8_802C6DA8(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C6DA8: lui         $a2, 0x802C
    ctx->r6 = S32(0X802C << 16);
    // 0x802C6DAC: addiu       $a2, $a2, 0x7564
    ctx->r6 = ADD32(ctx->r6, 0X7564);
    // 0x802C6DB0: lw          $v0, 0x0($a2)
    ctx->r2 = MEM_W(ctx->r6, 0X0);
    // 0x802C6DB4: lui         $a3, 0x802C
    ctx->r7 = S32(0X802C << 16);
    // 0x802C6DB8: addiu       $a3, $a3, 0x7548
    ctx->r7 = ADD32(ctx->r7, 0X7548);
    // 0x802C6DBC: blez        $v0, L_802C6DF8
    if (SIGNED(ctx->r2) <= 0) {
        // 0x802C6DC0: addu        $v1, $a3, $v0
        ctx->r3 = ADD32(ctx->r7, ctx->r2);
            goto L_802C6DF8;
    }
    // 0x802C6DC0: addu        $v1, $a3, $v0
    ctx->r3 = ADD32(ctx->r7, ctx->r2);
    // 0x802C6DC4: addiu       $t6, $v0, -0x1
    ctx->r14 = ADD32(ctx->r2, -0X1);
    // 0x802C6DC8: sw          $t6, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r14;
    // 0x802C6DCC: lb          $a1, 0x0($v1)
    ctx->r5 = MEM_B(ctx->r3, 0X0);
    // 0x802C6DD0: addu        $a0, $a3, $t6
    ctx->r4 = ADD32(ctx->r7, ctx->r14);
    // 0x802C6DD4: beql        $a1, $zero, L_802C6DF8
    if (ctx->r5 == 0) {
        // 0x802C6DD8: sb          $zero, 0x0($a0)
        MEM_B(0X0, ctx->r4) = 0;
            goto L_802C6DF8;
    }
    goto skip_0;
    // 0x802C6DD8: sb          $zero, 0x0($a0)
    MEM_B(0X0, ctx->r4) = 0;
    skip_0:
    // 0x802C6DDC: sb          $a1, 0x0($a0)
    MEM_B(0X0, ctx->r4) = ctx->r5;
L_802C6DE0:
    // 0x802C6DE0: lb          $a1, 0x1($v1)
    ctx->r5 = MEM_B(ctx->r3, 0X1);
    // 0x802C6DE4: addiu       $a0, $a0, 0x1
    ctx->r4 = ADD32(ctx->r4, 0X1);
    // 0x802C6DE8: addiu       $v1, $v1, 0x1
    ctx->r3 = ADD32(ctx->r3, 0X1);
    // 0x802C6DEC: bnel        $a1, $zero, L_802C6DE0
    if (ctx->r5 != 0) {
        // 0x802C6DF0: sb          $a1, 0x0($a0)
        MEM_B(0X0, ctx->r4) = ctx->r5;
            goto L_802C6DE0;
    }
    goto skip_1;
    // 0x802C6DF0: sb          $a1, 0x0($a0)
    MEM_B(0X0, ctx->r4) = ctx->r5;
    skip_1:
    // 0x802C6DF4: sb          $zero, 0x0($a0)
    MEM_B(0X0, ctx->r4) = 0;
L_802C6DF8:
    // 0x802C6DF8: jr          $ra
    // 0x802C6DFC: nop

    return;
    // 0x802C6DFC: nop

;}
RECOMP_FUNC void func_i8_802C6E00(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C6E00: lui         $a0, 0x802C
    ctx->r4 = S32(0X802C << 16);
    // 0x802C6E04: addiu       $a0, $a0, 0x7548
    ctx->r4 = ADD32(ctx->r4, 0X7548);
    // 0x802C6E08: lb          $t6, 0x0($a0)
    ctx->r14 = MEM_B(ctx->r4, 0X0);
    // 0x802C6E0C: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x802C6E10: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x802C6E14: beq         $t6, $zero, L_802C6E50
    if (ctx->r14 == 0) {
        // 0x802C6E18: lui         $t7, 0x802C
        ctx->r15 = S32(0X802C << 16);
            goto L_802C6E50;
    }
    // 0x802C6E18: lui         $t7, 0x802C
    ctx->r15 = S32(0X802C << 16);
    // 0x802C6E1C: lw          $t7, 0x7040($t7)
    ctx->r15 = MEM_W(ctx->r15, 0X7040);
    // 0x802C6E20: lui         $t9, 0x802C
    ctx->r25 = S32(0X802C << 16);
    // 0x802C6E24: lui         $t1, 0x801D
    ctx->r9 = S32(0X801D << 16);
    // 0x802C6E28: sll         $t8, $t7, 2
    ctx->r24 = S32(ctx->r15 << 2);
    // 0x802C6E2C: addu        $t9, $t9, $t8
    ctx->r25 = ADD32(ctx->r25, ctx->r24);
    // 0x802C6E30: lw          $t9, 0x74F8($t9)
    ctx->r25 = MEM_W(ctx->r25, 0X74F8);
    // 0x802C6E34: addiu       $t1, $t1, -0x4D68
    ctx->r9 = ADD32(ctx->r9, -0X4D68);
    // 0x802C6E38: addiu       $a2, $zero, 0xB
    ctx->r6 = ADD32(0, 0XB);
    // 0x802C6E3C: sll         $t0, $t9, 3
    ctx->r8 = S32(ctx->r25 << 3);
    // 0x802C6E40: subu        $t0, $t0, $t9
    ctx->r8 = SUB32(ctx->r8, ctx->r25);
    // 0x802C6E44: sll         $t0, $t0, 1
    ctx->r8 = S32(ctx->r8 << 1);
    // 0x802C6E48: jal         0x802C6FD4
    // 0x802C6E4C: addu        $a1, $t0, $t1
    ctx->r5 = ADD32(ctx->r8, ctx->r9);
    func_i8_802C6FD4(rdram, ctx);
        goto after_0;
    // 0x802C6E4C: addu        $a1, $t0, $t1
    ctx->r5 = ADD32(ctx->r8, ctx->r9);
    after_0:
L_802C6E50:
    // 0x802C6E50: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x802C6E54: addiu       $t2, $zero, 0x1
    ctx->r10 = ADD32(0, 0X1);
    // 0x802C6E58: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C6E5C: sw          $t2, 0x756C($at)
    MEM_W(0X756C, ctx->r1) = ctx->r10;
    // 0x802C6E60: jr          $ra
    // 0x802C6E64: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    return;
    // 0x802C6E64: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
;}
RECOMP_FUNC void func_i8_802C6E68(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C6E68: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x802C6E6C: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x802C6E70: lui         $a1, 0x802C
    ctx->r5 = S32(0X802C << 16);
    // 0x802C6E74: addiu       $a1, $a1, 0x7548
    ctx->r5 = ADD32(ctx->r5, 0X7548);
    // 0x802C6E78: jal         0x802C6FD4
    // 0x802C6E7C: addiu       $a2, $zero, 0xB
    ctx->r6 = ADD32(0, 0XB);
    func_i8_802C6FD4(rdram, ctx);
        goto after_0;
    // 0x802C6E7C: addiu       $a2, $zero, 0xB
    ctx->r6 = ADD32(0, 0XB);
    after_0:
    // 0x802C6E80: lui         $a0, 0x802C
    ctx->r4 = S32(0X802C << 16);
    // 0x802C6E84: jal         0x800941D0
    // 0x802C6E88: addiu       $a0, $a0, 0x7548
    ctx->r4 = ADD32(ctx->r4, 0X7548);
    Strlen2(rdram, ctx);
        goto after_1;
    // 0x802C6E88: addiu       $a0, $a0, 0x7548
    ctx->r4 = ADD32(ctx->r4, 0X7548);
    after_1:
    // 0x802C6E8C: lui         $v1, 0x802C
    ctx->r3 = S32(0X802C << 16);
    // 0x802C6E90: addiu       $v1, $v1, 0x7564
    ctx->r3 = ADD32(ctx->r3, 0X7564);
    // 0x802C6E94: slti        $at, $v0, 0x9
    ctx->r1 = SIGNED(ctx->r2) < 0X9 ? 1 : 0;
    // 0x802C6E98: bne         $at, $zero, L_802C6EA8
    if (ctx->r1 != 0) {
        // 0x802C6E9C: sw          $v0, 0x0($v1)
        MEM_W(0X0, ctx->r3) = ctx->r2;
            goto L_802C6EA8;
    }
    // 0x802C6E9C: sw          $v0, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r2;
    // 0x802C6EA0: addiu       $t7, $zero, 0x9
    ctx->r15 = ADD32(0, 0X9);
    // 0x802C6EA4: sw          $t7, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r15;
L_802C6EA8:
    // 0x802C6EA8: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x802C6EAC: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x802C6EB0: jr          $ra
    // 0x802C6EB4: nop

    return;
    // 0x802C6EB4: nop

;}
RECOMP_FUNC void func_i8_802C6EB8(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C6EB8: addiu       $sp, $sp, -0x30
    ctx->r29 = ADD32(ctx->r29, -0X30);
    // 0x802C6EBC: sw          $ra, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r31;
    // 0x802C6EC0: sw          $s4, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r20;
    // 0x802C6EC4: sw          $s3, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r19;
    // 0x802C6EC8: sw          $s2, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r18;
    // 0x802C6ECC: sw          $s1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r17;
    // 0x802C6ED0: sw          $s0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r16;
    // 0x802C6ED4: lb          $t6, 0x0($a0)
    ctx->r14 = MEM_B(ctx->r4, 0X0);
    // 0x802C6ED8: or          $s4, $a1, $zero
    ctx->r20 = ctx->r5 | 0;
    // 0x802C6EDC: or          $s1, $zero, $zero
    ctx->r17 = 0 | 0;
    // 0x802C6EE0: beq         $t6, $zero, L_802C6F28
    if (ctx->r14 == 0) {
        // 0x802C6EE4: or          $s0, $a0, $zero
        ctx->r16 = ctx->r4 | 0;
            goto L_802C6F28;
    }
    // 0x802C6EE4: or          $s0, $a0, $zero
    ctx->r16 = ctx->r4 | 0;
    // 0x802C6EE8: lui         $s3, 0x8022
    ctx->r19 = S32(0X8022 << 16);
    // 0x802C6EEC: addiu       $s3, $s3, 0x6DC4
    ctx->r19 = ADD32(ctx->r19, 0X6DC4);
    // 0x802C6EF0: lb          $a1, 0x0($a0)
    ctx->r5 = MEM_B(ctx->r4, 0X0);
    // 0x802C6EF4: addiu       $s2, $zero, 0xFF
    ctx->r18 = ADD32(0, 0XFF);
L_802C6EF8:
    // 0x802C6EF8: jal         0x801E9B04
    // 0x802C6EFC: or          $a0, $s4, $zero
    ctx->r4 = ctx->r20 | 0;
    func_801E9B04(rdram, ctx);
        goto after_0;
    // 0x802C6EFC: or          $a0, $s4, $zero
    ctx->r4 = ctx->r20 | 0;
    after_0:
    // 0x802C6F00: bne         $v0, $s2, L_802C6F10
    if (ctx->r2 != ctx->r18) {
        // 0x802C6F04: addu        $t7, $s3, $v0
        ctx->r15 = ADD32(ctx->r19, ctx->r2);
            goto L_802C6F10;
    }
    // 0x802C6F04: addu        $t7, $s3, $v0
    ctx->r15 = ADD32(ctx->r19, ctx->r2);
    // 0x802C6F08: b           L_802C6F14
    // 0x802C6F0C: addiu       $v1, $zero, 0xC
    ctx->r3 = ADD32(0, 0XC);
        goto L_802C6F14;
    // 0x802C6F0C: addiu       $v1, $zero, 0xC
    ctx->r3 = ADD32(0, 0XC);
L_802C6F10:
    // 0x802C6F10: lbu         $v1, 0x0($t7)
    ctx->r3 = MEM_BU(ctx->r15, 0X0);
L_802C6F14:
    // 0x802C6F14: lb          $a1, 0x1($s0)
    ctx->r5 = MEM_B(ctx->r16, 0X1);
    // 0x802C6F18: addu        $s1, $s1, $v1
    ctx->r17 = ADD32(ctx->r17, ctx->r3);
    // 0x802C6F1C: addiu       $s0, $s0, 0x1
    ctx->r16 = ADD32(ctx->r16, 0X1);
    // 0x802C6F20: bne         $a1, $zero, L_802C6EF8
    if (ctx->r5 != 0) {
        // 0x802C6F24: nop
    
            goto L_802C6EF8;
    }
    // 0x802C6F24: nop

L_802C6F28:
    // 0x802C6F28: lw          $ra, 0x2C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X2C);
    // 0x802C6F2C: or          $v0, $s1, $zero
    ctx->r2 = ctx->r17 | 0;
    // 0x802C6F30: lw          $s1, 0x1C($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X1C);
    // 0x802C6F34: lw          $s0, 0x18($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X18);
    // 0x802C6F38: lw          $s2, 0x20($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X20);
    // 0x802C6F3C: lw          $s3, 0x24($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X24);
    // 0x802C6F40: lw          $s4, 0x28($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X28);
    // 0x802C6F44: jr          $ra
    // 0x802C6F48: addiu       $sp, $sp, 0x30
    ctx->r29 = ADD32(ctx->r29, 0X30);
    return;
    // 0x802C6F48: addiu       $sp, $sp, 0x30
    ctx->r29 = ADD32(ctx->r29, 0X30);
;}
RECOMP_FUNC void func_i8_802C6F4C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C6F4C: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x802C6F50: addiu       $v0, $v0, -0x54DC
    ctx->r2 = ADD32(ctx->r2, -0X54DC);
    // 0x802C6F54: lw          $t6, 0x0($v0)
    ctx->r14 = MEM_W(ctx->r2, 0X0);
    // 0x802C6F58: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C6F5C: addiu       $t7, $zero, 0x3F
    ctx->r15 = ADD32(0, 0X3F);
    // 0x802C6F60: sw          $t6, -0x19CC($at)
    MEM_W(-0X19CC, ctx->r1) = ctx->r14;
    // 0x802C6F64: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C6F68: sw          $zero, -0x19D0($at)
    MEM_W(-0X19D0, ctx->r1) = 0;
    // 0x802C6F6C: sw          $t7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r15;
    // 0x802C6F70: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C6F74: addiu       $t8, $zero, 0xA
    ctx->r24 = ADD32(0, 0XA);
    // 0x802C6F78: sw          $t8, -0x19C8($at)
    MEM_W(-0X19C8, ctx->r1) = ctx->r24;
    // 0x802C6F7C: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C6F80: addiu       $t9, $zero, 0x1
    ctx->r25 = ADD32(0, 0X1);
    // 0x802C6F84: sw          $t9, -0x19C4($at)
    MEM_W(-0X19C4, ctx->r1) = ctx->r25;
    // 0x802C6F88: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C6F8C: sw          $zero, -0x19C0($at)
    MEM_W(-0X19C0, ctx->r1) = 0;
    // 0x802C6F90: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C6F94: sw          $zero, -0x19BC($at)
    MEM_W(-0X19BC, ctx->r1) = 0;
    // 0x802C6F98: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x802C6F9C: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x802C6FA0: sw          $zero, -0x54E4($at)
    MEM_W(-0X54E4, ctx->r1) = 0;
    // 0x802C6FA4: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x802C6FA8: lui         $at, 0x800D
    ctx->r1 = S32(0X800D << 16);
    // 0x802C6FAC: addiu       $t0, $zero, 0x3
    ctx->r8 = ADD32(0, 0X3);
    // 0x802C6FB0: sw          $t0, 0x461C($at)
    MEM_W(0X461C, ctx->r1) = ctx->r8;
    // 0x802C6FB4: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    // 0x802C6FB8: addiu       $a1, $zero, 0x4
    ctx->r5 = ADD32(0, 0X4);
    // 0x802C6FBC: jal         0x801E6FB0
    // 0x802C6FC0: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    FadeTransition_SetProps(rdram, ctx);
        goto after_0;
    // 0x802C6FC0: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    after_0:
    // 0x802C6FC4: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x802C6FC8: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x802C6FCC: jr          $ra
    // 0x802C6FD0: nop

    return;
    // 0x802C6FD0: nop

;}
RECOMP_FUNC void func_i8_802C6FD4(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C6FD4: blez        $a2, L_802C7038
    if (SIGNED(ctx->r6) <= 0) {
        // 0x802C6FD8: or          $v0, $zero, $zero
        ctx->r2 = 0 | 0;
            goto L_802C7038;
    }
    // 0x802C6FD8: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    // 0x802C6FDC: andi        $a3, $a2, 0x3
    ctx->r7 = ctx->r6 & 0X3;
    // 0x802C6FE0: beq         $a3, $zero, L_802C7008
    if (ctx->r7 == 0) {
        // 0x802C6FE4: or          $v1, $a3, $zero
        ctx->r3 = ctx->r7 | 0;
            goto L_802C7008;
    }
    // 0x802C6FE4: or          $v1, $a3, $zero
    ctx->r3 = ctx->r7 | 0;
L_802C6FE8:
    // 0x802C6FE8: lb          $t6, 0x0($a0)
    ctx->r14 = MEM_B(ctx->r4, 0X0);
    // 0x802C6FEC: addiu       $v0, $v0, 0x1
    ctx->r2 = ADD32(ctx->r2, 0X1);
    // 0x802C6FF0: addiu       $a1, $a1, 0x1
    ctx->r5 = ADD32(ctx->r5, 0X1);
    // 0x802C6FF4: addiu       $a0, $a0, 0x1
    ctx->r4 = ADD32(ctx->r4, 0X1);
    // 0x802C6FF8: bne         $v1, $v0, L_802C6FE8
    if (ctx->r3 != ctx->r2) {
        // 0x802C6FFC: sb          $t6, -0x1($a1)
        MEM_B(-0X1, ctx->r5) = ctx->r14;
            goto L_802C6FE8;
    }
    // 0x802C6FFC: sb          $t6, -0x1($a1)
    MEM_B(-0X1, ctx->r5) = ctx->r14;
    // 0x802C7000: beq         $v0, $a2, L_802C7038
    if (ctx->r2 == ctx->r6) {
        // 0x802C7004: nop
    
            goto L_802C7038;
    }
    // 0x802C7004: nop

L_802C7008:
    // 0x802C7008: lb          $t7, 0x0($a0)
    ctx->r15 = MEM_B(ctx->r4, 0X0);
    // 0x802C700C: addiu       $v0, $v0, 0x4
    ctx->r2 = ADD32(ctx->r2, 0X4);
    // 0x802C7010: addiu       $a1, $a1, 0x4
    ctx->r5 = ADD32(ctx->r5, 0X4);
    // 0x802C7014: sb          $t7, -0x4($a1)
    MEM_B(-0X4, ctx->r5) = ctx->r15;
    // 0x802C7018: lb          $t8, 0x1($a0)
    ctx->r24 = MEM_B(ctx->r4, 0X1);
    // 0x802C701C: addiu       $a0, $a0, 0x4
    ctx->r4 = ADD32(ctx->r4, 0X4);
    // 0x802C7020: sb          $t8, -0x3($a1)
    MEM_B(-0X3, ctx->r5) = ctx->r24;
    // 0x802C7024: lb          $t9, -0x2($a0)
    ctx->r25 = MEM_B(ctx->r4, -0X2);
    // 0x802C7028: sb          $t9, -0x2($a1)
    MEM_B(-0X2, ctx->r5) = ctx->r25;
    // 0x802C702C: lb          $t0, -0x1($a0)
    ctx->r8 = MEM_B(ctx->r4, -0X1);
    // 0x802C7030: bne         $v0, $a2, L_802C7008
    if (ctx->r2 != ctx->r6) {
        // 0x802C7034: sb          $t0, -0x1($a1)
        MEM_B(-0X1, ctx->r5) = ctx->r8;
            goto L_802C7008;
    }
    // 0x802C7034: sb          $t0, -0x1($a1)
    MEM_B(-0X1, ctx->r5) = ctx->r8;
L_802C7038:
    // 0x802C7038: jr          $ra
    // 0x802C703C: nop

    return;
    // 0x802C703C: nop

;}
RECOMP_FUNC void func_i9_802C5800(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C5800: addiu       $sp, $sp, -0x1D8
    ctx->r29 = ADD32(ctx->r29, -0X1D8);
    // 0x802C5804: lui         $t6, 0x801D
    ctx->r14 = S32(0X801D << 16);
    // 0x802C5808: lw          $t6, -0x19C4($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X19C4);
    // 0x802C580C: sw          $ra, 0x5C($sp)
    MEM_W(0X5C, ctx->r29) = ctx->r31;
    // 0x802C5810: sw          $fp, 0x58($sp)
    MEM_W(0X58, ctx->r29) = ctx->r30;
    // 0x802C5814: sw          $s7, 0x54($sp)
    MEM_W(0X54, ctx->r29) = ctx->r23;
    // 0x802C5818: sw          $s6, 0x50($sp)
    MEM_W(0X50, ctx->r29) = ctx->r22;
    // 0x802C581C: sw          $s5, 0x4C($sp)
    MEM_W(0X4C, ctx->r29) = ctx->r21;
    // 0x802C5820: sw          $s4, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r20;
    // 0x802C5824: sw          $s3, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r19;
    // 0x802C5828: sw          $s2, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r18;
    // 0x802C582C: sw          $s1, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r17;
    // 0x802C5830: beq         $t6, $zero, L_802C5908
    if (ctx->r14 == 0) {
        // 0x802C5834: sw          $s0, 0x38($sp)
        MEM_W(0X38, ctx->r29) = ctx->r16;
            goto L_802C5908;
    }
    // 0x802C5834: sw          $s0, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r16;
    // 0x802C5838: lui         $t7, 0x800E
    ctx->r15 = S32(0X800E << 16);
    // 0x802C583C: lw          $t7, -0x54DC($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X54DC);
    // 0x802C5840: addiu       $at, $zero, 0x42
    ctx->r1 = ADD32(0, 0X42);
    // 0x802C5844: lui         $t8, 0x801D
    ctx->r24 = S32(0X801D << 16);
    // 0x802C5848: bne         $t7, $at, L_802C5908
    if (ctx->r15 != ctx->r1) {
        // 0x802C584C: lui         $t2, 0x801D
        ctx->r10 = S32(0X801D << 16);
            goto L_802C5908;
    }
    // 0x802C584C: lui         $t2, 0x801D
    ctx->r10 = S32(0X801D << 16);
    // 0x802C5850: lb          $t8, -0x4D80($t8)
    ctx->r24 = MEM_B(ctx->r24, -0X4D80);
    // 0x802C5854: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
    // 0x802C5858: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C585C: andi        $t9, $t8, 0x8
    ctx->r25 = ctx->r24 & 0X8;
    // 0x802C5860: beq         $t9, $zero, L_802C586C
    if (ctx->r25 == 0) {
        // 0x802C5864: addiu       $v1, $zero, 0x140
        ctx->r3 = ADD32(0, 0X140);
            goto L_802C586C;
    }
    // 0x802C5864: addiu       $v1, $zero, 0x140
    ctx->r3 = ADD32(0, 0X140);
    // 0x802C5868: sw          $v0, -0x7E4C($at)
    MEM_W(-0X7E4C, ctx->r1) = ctx->r2;
L_802C586C:
    // 0x802C586C: lw          $t2, -0x19CC($t2)
    ctx->r10 = MEM_W(ctx->r10, -0X19CC);
    // 0x802C5870: addiu       $at, $zero, 0x65
    ctx->r1 = ADD32(0, 0X65);
    // 0x802C5874: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
    // 0x802C5878: bne         $t2, $at, L_802C5908
    if (ctx->r10 != ctx->r1) {
        // 0x802C587C: lui         $a0, 0x802D
        ctx->r4 = S32(0X802D << 16);
            goto L_802C5908;
    }
    // 0x802C587C: lui         $a0, 0x802D
    ctx->r4 = S32(0X802D << 16);
    // 0x802C5880: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C5884: sw          $v0, -0x7E5C($at)
    MEM_W(-0X7E5C, ctx->r1) = ctx->r2;
    // 0x802C5888: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C588C: sw          $v0, -0x7F40($at)
    MEM_W(-0X7F40, ctx->r1) = ctx->r2;
    // 0x802C5890: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C5894: sw          $zero, -0x7F3C($at)
    MEM_W(-0X7F3C, ctx->r1) = 0;
    // 0x802C5898: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C589C: addiu       $a0, $a0, -0x7F1C
    ctx->r4 = ADD32(ctx->r4, -0X7F1C);
    // 0x802C58A0: sw          $v0, -0x7F38($at)
    MEM_W(-0X7F38, ctx->r1) = ctx->r2;
    // 0x802C58A4: sw          $zero, 0x0($a0)
    MEM_W(0X0, ctx->r4) = 0;
    // 0x802C58A8: sw          $zero, 0x4($a0)
    MEM_W(0X4, ctx->r4) = 0;
    // 0x802C58AC: sw          $v0, 0x8($a0)
    MEM_W(0X8, ctx->r4) = ctx->r2;
    // 0x802C58B0: sw          $v0, 0xC($a0)
    MEM_W(0XC, ctx->r4) = ctx->r2;
    // 0x802C58B4: sw          $v1, 0x10($a0)
    MEM_W(0X10, ctx->r4) = ctx->r3;
    // 0x802C58B8: sw          $zero, 0x14($a0)
    MEM_W(0X14, ctx->r4) = 0;
    // 0x802C58BC: sw          $v0, 0x18($a0)
    MEM_W(0X18, ctx->r4) = ctx->r2;
    // 0x802C58C0: sw          $v0, 0x1C($a0)
    MEM_W(0X1C, ctx->r4) = ctx->r2;
    // 0x802C58C4: lui         $t3, 0x800E
    ctx->r11 = S32(0X800E << 16);
    // 0x802C58C8: lh          $t3, -0x5498($t3)
    ctx->r11 = MEM_H(ctx->r11, -0X5498);
    // 0x802C58CC: lui         $a1, 0x802D
    ctx->r5 = S32(0X802D << 16);
    // 0x802C58D0: addiu       $t4, $zero, 0x3
    ctx->r12 = ADD32(0, 0X3);
    // 0x802C58D4: beq         $t3, $zero, L_802C58E8
    if (ctx->r11 == 0) {
        // 0x802C58D8: addiu       $a1, $a1, -0x7EFC
        ctx->r5 = ADD32(ctx->r5, -0X7EFC);
            goto L_802C58E8;
    }
    // 0x802C58D8: addiu       $a1, $a1, -0x7EFC
    ctx->r5 = ADD32(ctx->r5, -0X7EFC);
    // 0x802C58DC: addiu       $t5, $zero, 0x3
    ctx->r13 = ADD32(0, 0X3);
    // 0x802C58E0: sw          $t4, 0xC($a0)
    MEM_W(0XC, ctx->r4) = ctx->r12;
    // 0x802C58E4: sw          $t5, 0x1C($a0)
    MEM_W(0X1C, ctx->r4) = ctx->r13;
L_802C58E8:
    // 0x802C58E8: sw          $zero, 0x0($a1)
    MEM_W(0X0, ctx->r5) = 0;
    // 0x802C58EC: sw          $zero, 0x4($a1)
    MEM_W(0X4, ctx->r5) = 0;
    // 0x802C58F0: sw          $v0, 0x8($a1)
    MEM_W(0X8, ctx->r5) = ctx->r2;
    // 0x802C58F4: sw          $v0, 0xC($a1)
    MEM_W(0XC, ctx->r5) = ctx->r2;
    // 0x802C58F8: sw          $v1, 0x10($a1)
    MEM_W(0X10, ctx->r5) = ctx->r3;
    // 0x802C58FC: sw          $zero, 0x14($a1)
    MEM_W(0X14, ctx->r5) = 0;
    // 0x802C5900: sw          $v0, 0x18($a1)
    MEM_W(0X18, ctx->r5) = ctx->r2;
    // 0x802C5904: sw          $zero, 0x1C($a1)
    MEM_W(0X1C, ctx->r5) = 0;
L_802C5908:
    // 0x802C5908: lui         $a2, 0x802D
    ctx->r6 = S32(0X802D << 16);
    // 0x802C590C: addiu       $a2, $a2, -0x7F24
    ctx->r6 = ADD32(ctx->r6, -0X7F24);
    // 0x802C5910: lw          $v1, 0x0($a2)
    ctx->r3 = MEM_W(ctx->r6, 0X0);
    // 0x802C5914: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
    // 0x802C5918: lui         $a0, 0x802D
    ctx->r4 = S32(0X802D << 16);
    // 0x802C591C: lui         $a1, 0x802D
    ctx->r5 = S32(0X802D << 16);
    // 0x802C5920: addiu       $a1, $a1, -0x7EFC
    ctx->r5 = ADD32(ctx->r5, -0X7EFC);
    // 0x802C5924: addiu       $a0, $a0, -0x7F1C
    ctx->r4 = ADD32(ctx->r4, -0X7F1C);
    // 0x802C5928: beq         $v1, $zero, L_802C5A80
    if (ctx->r3 == 0) {
        // 0x802C592C: or          $t1, $v0, $zero
        ctx->r9 = ctx->r2 | 0;
            goto L_802C5A80;
    }
    // 0x802C592C: or          $t1, $v0, $zero
    ctx->r9 = ctx->r2 | 0;
    // 0x802C5930: bne         $v0, $v1, L_802C5954
    if (ctx->r2 != ctx->r3) {
        // 0x802C5934: addiu       $t1, $zero, 0x2
        ctx->r9 = ADD32(0, 0X2);
            goto L_802C5954;
    }
    // 0x802C5934: addiu       $t1, $zero, 0x2
    ctx->r9 = ADD32(0, 0X2);
    // 0x802C5938: lui         $t0, 0x802D
    ctx->r8 = S32(0X802D << 16);
    // 0x802C593C: addiu       $t0, $t0, -0x7F34
    ctx->r8 = ADD32(ctx->r8, -0X7F34);
    // 0x802C5940: lw          $t6, 0x0($t0)
    ctx->r14 = MEM_W(ctx->r8, 0X0);
    // 0x802C5944: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    // 0x802C5948: addiu       $t7, $t6, 0x1E
    ctx->r15 = ADD32(ctx->r14, 0X1E);
    // 0x802C594C: b           L_802C59CC
    // 0x802C5950: sw          $t7, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r15;
        goto L_802C59CC;
    // 0x802C5950: sw          $t7, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r15;
L_802C5954:
    // 0x802C5954: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x802C5958: bne         $v1, $at, L_802C5980
    if (ctx->r3 != ctx->r1) {
        // 0x802C595C: lui         $t8, 0x802D
        ctx->r24 = S32(0X802D << 16);
            goto L_802C5980;
    }
    // 0x802C595C: lui         $t8, 0x802D
    ctx->r24 = S32(0X802D << 16);
    // 0x802C5960: lw          $t8, -0x7F34($t8)
    ctx->r24 = MEM_W(ctx->r24, -0X7F34);
    // 0x802C5964: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C5968: lui         $t0, 0x802D
    ctx->r8 = S32(0X802D << 16);
    // 0x802C596C: addiu       $t9, $t8, -0x1E
    ctx->r25 = ADD32(ctx->r24, -0X1E);
    // 0x802C5970: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    // 0x802C5974: sw          $t9, -0x7F34($at)
    MEM_W(-0X7F34, ctx->r1) = ctx->r25;
    // 0x802C5978: b           L_802C59CC
    // 0x802C597C: addiu       $t0, $t0, -0x7F34
    ctx->r8 = ADD32(ctx->r8, -0X7F34);
        goto L_802C59CC;
    // 0x802C597C: addiu       $t0, $t0, -0x7F34
    ctx->r8 = ADD32(ctx->r8, -0X7F34);
L_802C5980:
    // 0x802C5980: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x802C5984: bne         $v1, $at, L_802C59B0
    if (ctx->r3 != ctx->r1) {
        // 0x802C5988: addiu       $v0, $zero, 0x1
        ctx->r2 = ADD32(0, 0X1);
            goto L_802C59B0;
    }
    // 0x802C5988: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
    // 0x802C598C: lui         $t2, 0x802D
    ctx->r10 = S32(0X802D << 16);
    // 0x802C5990: lw          $t2, -0x7F30($t2)
    ctx->r10 = MEM_W(ctx->r10, -0X7F30);
    // 0x802C5994: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C5998: lui         $t0, 0x802D
    ctx->r8 = S32(0X802D << 16);
    // 0x802C599C: addiu       $t3, $t2, -0x1E
    ctx->r11 = ADD32(ctx->r10, -0X1E);
    // 0x802C59A0: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
    // 0x802C59A4: sw          $t3, -0x7F30($at)
    MEM_W(-0X7F30, ctx->r1) = ctx->r11;
    // 0x802C59A8: b           L_802C59CC
    // 0x802C59AC: addiu       $t0, $t0, -0x7F34
    ctx->r8 = ADD32(ctx->r8, -0X7F34);
        goto L_802C59CC;
    // 0x802C59AC: addiu       $t0, $t0, -0x7F34
    ctx->r8 = ADD32(ctx->r8, -0X7F34);
L_802C59B0:
    // 0x802C59B0: lui         $t4, 0x802D
    ctx->r12 = S32(0X802D << 16);
    // 0x802C59B4: lw          $t4, -0x7F30($t4)
    ctx->r12 = MEM_W(ctx->r12, -0X7F30);
    // 0x802C59B8: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C59BC: lui         $t0, 0x802D
    ctx->r8 = S32(0X802D << 16);
    // 0x802C59C0: addiu       $t5, $t4, 0x1E
    ctx->r13 = ADD32(ctx->r12, 0X1E);
    // 0x802C59C4: sw          $t5, -0x7F30($at)
    MEM_W(-0X7F30, ctx->r1) = ctx->r13;
    // 0x802C59C8: addiu       $t0, $t0, -0x7F34
    ctx->r8 = ADD32(ctx->r8, -0X7F34);
L_802C59CC:
    // 0x802C59CC: bne         $v0, $zero, L_802C59F4
    if (ctx->r2 != 0) {
        // 0x802C59D0: or          $v1, $zero, $zero
        ctx->r3 = 0 | 0;
            goto L_802C59F4;
    }
    // 0x802C59D0: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
    // 0x802C59D4: lw          $v0, 0x0($t0)
    ctx->r2 = MEM_W(ctx->r8, 0X0);
    // 0x802C59D8: slti        $at, $v0, -0x1A7
    ctx->r1 = SIGNED(ctx->r2) < -0X1A7 ? 1 : 0;
    // 0x802C59DC: bne         $at, $zero, L_802C59EC
    if (ctx->r1 != 0) {
        // 0x802C59E0: slti        $at, $v0, 0x1A8
        ctx->r1 = SIGNED(ctx->r2) < 0X1A8 ? 1 : 0;
            goto L_802C59EC;
    }
    // 0x802C59E0: slti        $at, $v0, 0x1A8
    ctx->r1 = SIGNED(ctx->r2) < 0X1A8 ? 1 : 0;
    // 0x802C59E4: bne         $at, $zero, L_802C5A14
    if (ctx->r1 != 0) {
        // 0x802C59E8: nop
    
            goto L_802C5A14;
    }
    // 0x802C59E8: nop

L_802C59EC:
    // 0x802C59EC: b           L_802C5A14
    // 0x802C59F0: addiu       $v1, $zero, 0x1
    ctx->r3 = ADD32(0, 0X1);
        goto L_802C5A14;
    // 0x802C59F0: addiu       $v1, $zero, 0x1
    ctx->r3 = ADD32(0, 0X1);
L_802C59F4:
    // 0x802C59F4: lui         $v0, 0x802D
    ctx->r2 = S32(0X802D << 16);
    // 0x802C59F8: lw          $v0, -0x7F30($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X7F30);
    // 0x802C59FC: slti        $at, $v0, -0xEF
    ctx->r1 = SIGNED(ctx->r2) < -0XEF ? 1 : 0;
    // 0x802C5A00: bne         $at, $zero, L_802C5A10
    if (ctx->r1 != 0) {
        // 0x802C5A04: slti        $at, $v0, 0xF0
        ctx->r1 = SIGNED(ctx->r2) < 0XF0 ? 1 : 0;
            goto L_802C5A10;
    }
    // 0x802C5A04: slti        $at, $v0, 0xF0
    ctx->r1 = SIGNED(ctx->r2) < 0XF0 ? 1 : 0;
    // 0x802C5A08: bne         $at, $zero, L_802C5A14
    if (ctx->r1 != 0) {
        // 0x802C5A0C: nop
    
            goto L_802C5A14;
    }
    // 0x802C5A0C: nop

L_802C5A10:
    // 0x802C5A10: addiu       $v1, $zero, 0x1
    ctx->r3 = ADD32(0, 0X1);
L_802C5A14:
    // 0x802C5A14: beq         $v1, $zero, L_802C5A3C
    if (ctx->r3 == 0) {
        // 0x802C5A18: lui         $v0, 0x802D
        ctx->r2 = S32(0X802D << 16);
            goto L_802C5A3C;
    }
    // 0x802C5A18: lui         $v0, 0x802D
    ctx->r2 = S32(0X802D << 16);
    // 0x802C5A1C: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C5A20: sw          $zero, -0x7F30($at)
    MEM_W(-0X7F30, ctx->r1) = 0;
    // 0x802C5A24: lw          $t6, 0x18($a0)
    ctx->r14 = MEM_W(ctx->r4, 0X18);
    // 0x802C5A28: lw          $t7, 0x1C($a0)
    ctx->r15 = MEM_W(ctx->r4, 0X1C);
    // 0x802C5A2C: sw          $zero, 0x0($t0)
    MEM_W(0X0, ctx->r8) = 0;
    // 0x802C5A30: sw          $zero, 0x0($a2)
    MEM_W(0X0, ctx->r6) = 0;
    // 0x802C5A34: sw          $t6, 0x8($a0)
    MEM_W(0X8, ctx->r4) = ctx->r14;
    // 0x802C5A38: sw          $t7, 0xC($a0)
    MEM_W(0XC, ctx->r4) = ctx->r15;
L_802C5A3C:
    // 0x802C5A3C: addiu       $v0, $v0, -0x7F20
    ctx->r2 = ADD32(ctx->r2, -0X7F20);
    // 0x802C5A40: lw          $t8, 0x0($v0)
    ctx->r24 = MEM_W(ctx->r2, 0X0);
    // 0x802C5A44: beql        $t8, $zero, L_802C5A84
    if (ctx->r24 == 0) {
        // 0x802C5A48: lui         $at, 0x4180
        ctx->r1 = S32(0X4180 << 16);
            goto L_802C5A84;
    }
    goto skip_0;
    // 0x802C5A48: lui         $at, 0x4180
    ctx->r1 = S32(0X4180 << 16);
    skip_0:
    // 0x802C5A4C: lw          $t9, 0x0($t0)
    ctx->r25 = MEM_W(ctx->r8, 0X0);
    // 0x802C5A50: lui         $t2, 0x802D
    ctx->r10 = S32(0X802D << 16);
    // 0x802C5A54: lw          $t2, -0x7F30($t2)
    ctx->r10 = MEM_W(ctx->r10, -0X7F30);
    // 0x802C5A58: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C5A5C: sw          $t9, -0x7F2C($at)
    MEM_W(-0X7F2C, ctx->r1) = ctx->r25;
    // 0x802C5A60: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C5A64: sw          $t2, -0x7F28($at)
    MEM_W(-0X7F28, ctx->r1) = ctx->r10;
    // 0x802C5A68: lw          $t3, 0x0($a2)
    ctx->r11 = MEM_W(ctx->r6, 0X0);
    // 0x802C5A6C: lw          $t4, 0x8($a0)
    ctx->r12 = MEM_W(ctx->r4, 0X8);
    // 0x802C5A70: lw          $t5, 0x18($a0)
    ctx->r13 = MEM_W(ctx->r4, 0X18);
    // 0x802C5A74: sw          $t3, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r11;
    // 0x802C5A78: sw          $t4, 0x8($a1)
    MEM_W(0X8, ctx->r5) = ctx->r12;
    // 0x802C5A7C: sw          $t5, 0x18($a1)
    MEM_W(0X18, ctx->r5) = ctx->r13;
L_802C5A80:
    // 0x802C5A80: lui         $at, 0x4180
    ctx->r1 = S32(0X4180 << 16);
L_802C5A84:
    // 0x802C5A84: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x802C5A88: lui         $s3, 0x801D
    ctx->r19 = S32(0X801D << 16);
    // 0x802C5A8C: mtc1        $zero, $f0
    ctx->f0.u32l = 0;
    // 0x802C5A90: addiu       $s3, $s3, -0x1A08
    ctx->r19 = ADD32(ctx->r19, -0X1A08);
    // 0x802C5A94: lui         $at, 0x4580
    ctx->r1 = S32(0X4580 << 16);
    // 0x802C5A98: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x802C5A9C: lw          $a0, 0x0($s3)
    ctx->r4 = MEM_W(ctx->r19, 0X0);
    // 0x802C5AA0: lui         $a1, 0x802D
    ctx->r5 = S32(0X802D << 16);
    // 0x802C5AA4: addiu       $a1, $a1, -0x7D80
    ctx->r5 = ADD32(ctx->r5, -0X7D80);
    // 0x802C5AA8: lui         $a2, 0x4204
    ctx->r6 = S32(0X4204 << 16);
    // 0x802C5AAC: lui         $a3, 0x3F80
    ctx->r7 = S32(0X3F80 << 16);
    // 0x802C5AB0: sw          $t1, 0x1C0($sp)
    MEM_W(0X1C0, ctx->r29) = ctx->r9;
    // 0x802C5AB4: swc1        $f4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f4.u32l;
    // 0x802C5AB8: swc1        $f0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->f0.u32l;
    // 0x802C5ABC: swc1        $f0, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->f0.u32l;
    // 0x802C5AC0: addiu       $a0, $a0, 0xA40
    ctx->r4 = ADD32(ctx->r4, 0XA40);
    // 0x802C5AC4: jal         0x800481E0
    // 0x802C5AC8: swc1        $f6, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->f6.u32l;
    func_800481E0(rdram, ctx);
        goto after_0;
    // 0x802C5AC8: swc1        $f6, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->f6.u32l;
    after_0:
    // 0x802C5ACC: mtc1        $zero, $f0
    ctx->f0.u32l = 0;
    // 0x802C5AD0: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x802C5AD4: mtc1        $at, $f2
    ctx->f2.u32l = ctx->r1;
    // 0x802C5AD8: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C5ADC: lwc1        $f8, -0x7DE4($at)
    ctx->f8.u32l = MEM_W(ctx->r1, -0X7DE4);
    // 0x802C5AE0: addiu       $s0, $sp, 0xB8
    ctx->r16 = ADD32(ctx->r29, 0XB8);
    // 0x802C5AE4: mfc1        $a1, $f0
    ctx->r5 = (int32_t)ctx->f0.u32l;
    // 0x802C5AE8: mfc1        $a2, $f0
    ctx->r6 = (int32_t)ctx->f0.u32l;
    // 0x802C5AEC: mfc1        $a3, $f2
    ctx->r7 = (int32_t)ctx->f2.u32l;
    // 0x802C5AF0: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x802C5AF4: swc1        $f0, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f0.u32l;
    // 0x802C5AF8: swc1        $f0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->f0.u32l;
    // 0x802C5AFC: swc1        $f0, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->f0.u32l;
    // 0x802C5B00: swc1        $f0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->f0.u32l;
    // 0x802C5B04: swc1        $f0, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->f0.u32l;
    // 0x802C5B08: swc1        $f2, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->f2.u32l;
    // 0x802C5B0C: jal         0x80048A88
    // 0x802C5B10: swc1        $f8, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->f8.u32l;
    func_80048A88(rdram, ctx);
        goto after_1;
    // 0x802C5B10: swc1        $f8, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->f8.u32l;
    after_1:
    // 0x802C5B14: mtc1        $zero, $f0
    ctx->f0.u32l = 0;
    // 0x802C5B18: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x802C5B1C: mtc1        $at, $f10
    ctx->f10.u32l = ctx->r1;
    // 0x802C5B20: addiu       $s1, $sp, 0x138
    ctx->r17 = ADD32(ctx->r29, 0X138);
    // 0x802C5B24: mfc1        $a3, $f0
    ctx->r7 = (int32_t)ctx->f0.u32l;
    // 0x802C5B28: or          $a1, $s1, $zero
    ctx->r5 = ctx->r17 | 0;
    // 0x802C5B2C: addiu       $a0, $sp, 0x78
    ctx->r4 = ADD32(ctx->r29, 0X78);
    // 0x802C5B30: lui         $a2, 0x43FA
    ctx->r6 = S32(0X43FA << 16);
    // 0x802C5B34: swc1        $f0, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f0.u32l;
    // 0x802C5B38: swc1        $f0, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->f0.u32l;
    // 0x802C5B3C: swc1        $f0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->f0.u32l;
    // 0x802C5B40: swc1        $f0, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->f0.u32l;
    // 0x802C5B44: swc1        $f0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->f0.u32l;
    // 0x802C5B48: swc1        $f0, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->f0.u32l;
    // 0x802C5B4C: jal         0x800484C8
    // 0x802C5B50: swc1        $f10, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->f10.u32l;
    func_800484C8(rdram, ctx);
        goto after_2;
    // 0x802C5B50: swc1        $f10, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->f10.u32l;
    after_2:
    // 0x802C5B54: addiu       $s2, $sp, 0x178
    ctx->r18 = ADD32(ctx->r29, 0X178);
    // 0x802C5B58: or          $a1, $s2, $zero
    ctx->r5 = ctx->r18 | 0;
    // 0x802C5B5C: jal         0x80047E78
    // 0x802C5B60: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    SysUtils_MtxToMtxF(rdram, ctx);
        goto after_3;
    // 0x802C5B60: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_3:
    // 0x802C5B64: addiu       $s7, $sp, 0xF8
    ctx->r23 = ADD32(ctx->r29, 0XF8);
    // 0x802C5B68: or          $a2, $s7, $zero
    ctx->r6 = ctx->r23 | 0;
    // 0x802C5B6C: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    // 0x802C5B70: jal         0x80049EB8
    // 0x802C5B74: or          $a1, $s2, $zero
    ctx->r5 = ctx->r18 | 0;
    SysUtils_MatrixAffineMultiply(rdram, ctx);
        goto after_4;
    // 0x802C5B74: or          $a1, $s2, $zero
    ctx->r5 = ctx->r18 | 0;
    after_4:
    // 0x802C5B78: lw          $t6, 0x1C0($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X1C0);
    // 0x802C5B7C: sw          $zero, 0x1D0($sp)
    MEM_W(0X1D0, ctx->r29) = 0;
    // 0x802C5B80: blez        $t6, L_802C5CF4
    if (SIGNED(ctx->r14) <= 0) {
        // 0x802C5B84: lui         $a2, 0x802D
        ctx->r6 = S32(0X802D << 16);
            goto L_802C5CF4;
    }
    // 0x802C5B84: lui         $a2, 0x802D
    ctx->r6 = S32(0X802D << 16);
    // 0x802C5B88: addiu       $a2, $a2, -0x7F1C
    ctx->r6 = ADD32(ctx->r6, -0X7F1C);
    // 0x802C5B8C: lui         $fp, 0x802D
    ctx->r30 = S32(0X802D << 16);
    // 0x802C5B90: addiu       $fp, $fp, -0x7ED8
    ctx->r30 = ADD32(ctx->r30, -0X7ED8);
    // 0x802C5B94: sw          $a2, 0x70($sp)
    MEM_W(0X70, ctx->r29) = ctx->r6;
    // 0x802C5B98: or          $s5, $zero, $zero
    ctx->r21 = 0 | 0;
L_802C5B9C:
    // 0x802C5B9C: lw          $a2, 0x70($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X70);
    // 0x802C5BA0: lui         $t7, 0x802D
    ctx->r15 = S32(0X802D << 16);
    // 0x802C5BA4: lw          $t7, -0x7F34($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X7F34);
    // 0x802C5BA8: lw          $v0, 0x0($a2)
    ctx->r2 = MEM_W(ctx->r6, 0X0);
    // 0x802C5BAC: lui         $t8, 0x802D
    ctx->r24 = S32(0X802D << 16);
    // 0x802C5BB0: lw          $t8, -0x7F30($t8)
    ctx->r24 = MEM_W(ctx->r24, -0X7F30);
    // 0x802C5BB4: addu        $v1, $v0, $t7
    ctx->r3 = ADD32(ctx->r2, ctx->r15);
    // 0x802C5BB8: addiu       $s6, $v1, 0x4C
    ctx->r22 = ADD32(ctx->r3, 0X4C);
    // 0x802C5BBC: addu        $a3, $v0, $t8
    ctx->r7 = ADD32(ctx->r2, ctx->r24);
    // 0x802C5BC0: sll         $t9, $s6, 2
    ctx->r25 = S32(ctx->r22 << 2);
    // 0x802C5BC4: sw          $s5, 0x1CC($sp)
    MEM_W(0X1CC, ctx->r29) = ctx->r21;
    // 0x802C5BC8: or          $s6, $t9, $zero
    ctx->r22 = ctx->r25 | 0;
    // 0x802C5BCC: addiu       $s2, $a3, 0x8A
    ctx->r18 = ADD32(ctx->r7, 0X8A);
    // 0x802C5BD0: sw          $a3, 0x1C4($sp)
    MEM_W(0X1C4, ctx->r29) = ctx->r7;
    // 0x802C5BD4: or          $s4, $zero, $zero
    ctx->r20 = 0 | 0;
    // 0x802C5BD8: or          $s1, $zero, $zero
    ctx->r17 = 0 | 0;
    // 0x802C5BDC: sll         $s0, $s5, 4
    ctx->r16 = S32(ctx->r21 << 4);
L_802C5BE0:
    // 0x802C5BE0: lw          $t2, 0x0($s3)
    ctx->r10 = MEM_W(ctx->r19, 0X0);
    // 0x802C5BE4: sll         $t3, $s5, 6
    ctx->r11 = S32(ctx->r21 << 6);
    // 0x802C5BE8: or          $a0, $s7, $zero
    ctx->r4 = ctx->r23 | 0;
    // 0x802C5BEC: addu        $t4, $t2, $t3
    ctx->r12 = ADD32(ctx->r10, ctx->r11);
    // 0x802C5BF0: addu        $a1, $t4, $s1
    ctx->r5 = ADD32(ctx->r12, ctx->r17);
    // 0x802C5BF4: jal         0x80047EE0
    // 0x802C5BF8: addiu       $a1, $a1, 0xA80
    ctx->r5 = ADD32(ctx->r5, 0XA80);
    SysUtils_MtxFToMtx(rdram, ctx);
        goto after_5;
    // 0x802C5BF8: addiu       $a1, $a1, 0xA80
    ctx->r5 = ADD32(ctx->r5, 0XA80);
    after_5:
    // 0x802C5BFC: lw          $t5, 0x0($s3)
    ctx->r13 = MEM_W(ctx->r19, 0X0);
    // 0x802C5C00: lw          $at, 0x0($fp)
    ctx->r1 = MEM_W(ctx->r30, 0X0);
    // 0x802C5C04: addiu       $s4, $s4, 0x1
    ctx->r20 = ADD32(ctx->r20, 0X1);
    // 0x802C5C08: addu        $t6, $t5, $s0
    ctx->r14 = ADD32(ctx->r13, ctx->r16);
    // 0x802C5C0C: sw          $at, 0x1280($t6)
    MEM_W(0X1280, ctx->r14) = ctx->r1;
    // 0x802C5C10: lw          $t9, 0x4($fp)
    ctx->r25 = MEM_W(ctx->r30, 0X4);
    // 0x802C5C14: sll         $t4, $s2, 2
    ctx->r12 = S32(ctx->r18 << 2);
    // 0x802C5C18: addiu       $s2, $s2, 0x12
    ctx->r18 = ADD32(ctx->r18, 0X12);
    // 0x802C5C1C: sw          $t9, 0x1284($t6)
    MEM_W(0X1284, ctx->r14) = ctx->r25;
    // 0x802C5C20: lw          $at, 0x8($fp)
    ctx->r1 = MEM_W(ctx->r30, 0X8);
    // 0x802C5C24: addiu       $s1, $s1, 0x40
    ctx->r17 = ADD32(ctx->r17, 0X40);
    // 0x802C5C28: sw          $at, 0x1288($t6)
    MEM_W(0X1288, ctx->r14) = ctx->r1;
    // 0x802C5C2C: lw          $t9, 0xC($fp)
    ctx->r25 = MEM_W(ctx->r30, 0XC);
    // 0x802C5C30: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x802C5C34: sw          $t9, 0x128C($t6)
    MEM_W(0X128C, ctx->r14) = ctx->r25;
    // 0x802C5C38: lw          $t2, 0x0($s3)
    ctx->r10 = MEM_W(ctx->r19, 0X0);
    // 0x802C5C3C: addu        $t3, $t2, $s0
    ctx->r11 = ADD32(ctx->r10, ctx->r16);
    // 0x802C5C40: sh          $s6, 0x1288($t3)
    MEM_H(0X1288, ctx->r11) = ctx->r22;
    // 0x802C5C44: lw          $t5, 0x0($s3)
    ctx->r13 = MEM_W(ctx->r19, 0X0);
    // 0x802C5C48: addu        $t8, $t5, $s0
    ctx->r24 = ADD32(ctx->r13, ctx->r16);
    // 0x802C5C4C: addiu       $s0, $s0, 0x10
    ctx->r16 = ADD32(ctx->r16, 0X10);
    // 0x802C5C50: bne         $s4, $at, L_802C5BE0
    if (ctx->r20 != ctx->r1) {
        // 0x802C5C54: sh          $t4, 0x128A($t8)
        MEM_H(0X128A, ctx->r24) = ctx->r12;
            goto L_802C5BE0;
    }
    // 0x802C5C54: sh          $t4, 0x128A($t8)
    MEM_H(0X128A, ctx->r24) = ctx->r12;
    // 0x802C5C58: lw          $t7, 0x0($s3)
    ctx->r15 = MEM_W(ctx->r19, 0X0);
    // 0x802C5C5C: sll         $t6, $s5, 6
    ctx->r14 = S32(ctx->r21 << 6);
    // 0x802C5C60: or          $a0, $s7, $zero
    ctx->r4 = ctx->r23 | 0;
    // 0x802C5C64: addu        $t9, $t7, $t6
    ctx->r25 = ADD32(ctx->r15, ctx->r14);
    // 0x802C5C68: addu        $a1, $t9, $s1
    ctx->r5 = ADD32(ctx->r25, ctx->r17);
    // 0x802C5C6C: jal         0x80047EE0
    // 0x802C5C70: addiu       $a1, $a1, 0xA80
    ctx->r5 = ADD32(ctx->r5, 0XA80);
    SysUtils_MtxFToMtx(rdram, ctx);
        goto after_6;
    // 0x802C5C70: addiu       $a1, $a1, 0xA80
    ctx->r5 = ADD32(ctx->r5, 0XA80);
    after_6:
    // 0x802C5C74: lw          $t2, 0x1CC($sp)
    ctx->r10 = MEM_W(ctx->r29, 0X1CC);
    // 0x802C5C78: lw          $t5, 0x0($s3)
    ctx->r13 = MEM_W(ctx->r19, 0X0);
    // 0x802C5C7C: lw          $at, 0x0($fp)
    ctx->r1 = MEM_W(ctx->r30, 0X0);
    // 0x802C5C80: addu        $v0, $t2, $s4
    ctx->r2 = ADD32(ctx->r10, ctx->r20);
    // 0x802C5C84: sll         $t3, $v0, 4
    ctx->r11 = S32(ctx->r2 << 4);
    // 0x802C5C88: addu        $t4, $t5, $t3
    ctx->r12 = ADD32(ctx->r13, ctx->r11);
    // 0x802C5C8C: sw          $at, 0x1280($t4)
    MEM_W(0X1280, ctx->r12) = ctx->r1;
    // 0x802C5C90: lw          $t7, 0x4($fp)
    ctx->r15 = MEM_W(ctx->r30, 0X4);
    // 0x802C5C94: or          $v0, $t3, $zero
    ctx->r2 = ctx->r11 | 0;
    // 0x802C5C98: addiu       $s5, $s5, 0x4
    ctx->r21 = ADD32(ctx->r21, 0X4);
    // 0x802C5C9C: sw          $t7, 0x1284($t4)
    MEM_W(0X1284, ctx->r12) = ctx->r15;
    // 0x802C5CA0: lw          $at, 0x8($fp)
    ctx->r1 = MEM_W(ctx->r30, 0X8);
    // 0x802C5CA4: sw          $at, 0x1288($t4)
    MEM_W(0X1288, ctx->r12) = ctx->r1;
    // 0x802C5CA8: lw          $t7, 0xC($fp)
    ctx->r15 = MEM_W(ctx->r30, 0XC);
    // 0x802C5CAC: sw          $t7, 0x128C($t4)
    MEM_W(0X128C, ctx->r12) = ctx->r15;
    // 0x802C5CB0: lw          $t6, 0x0($s3)
    ctx->r14 = MEM_W(ctx->r19, 0X0);
    // 0x802C5CB4: addu        $t9, $t6, $t3
    ctx->r25 = ADD32(ctx->r14, ctx->r11);
    // 0x802C5CB8: sh          $s6, 0x1288($t9)
    MEM_H(0X1288, ctx->r25) = ctx->r22;
    // 0x802C5CBC: lw          $t2, 0x1C4($sp)
    ctx->r10 = MEM_W(ctx->r29, 0X1C4);
    // 0x802C5CC0: lw          $t8, 0x0($s3)
    ctx->r24 = MEM_W(ctx->r19, 0X0);
    // 0x802C5CC4: addiu       $t3, $t2, 0xCE
    ctx->r11 = ADD32(ctx->r10, 0XCE);
    // 0x802C5CC8: sll         $t5, $t3, 2
    ctx->r13 = S32(ctx->r11 << 2);
    // 0x802C5CCC: addu        $t4, $t8, $v0
    ctx->r12 = ADD32(ctx->r24, ctx->r2);
    // 0x802C5CD0: sh          $t5, 0x128A($t4)
    MEM_H(0X128A, ctx->r12) = ctx->r13;
    // 0x802C5CD4: lw          $t9, 0x70($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X70);
    // 0x802C5CD8: lw          $t7, 0x1D0($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X1D0);
    // 0x802C5CDC: lw          $t3, 0x1C0($sp)
    ctx->r11 = MEM_W(ctx->r29, 0X1C0);
    // 0x802C5CE0: addiu       $t2, $t9, 0x10
    ctx->r10 = ADD32(ctx->r25, 0X10);
    // 0x802C5CE4: addiu       $t6, $t7, 0x1
    ctx->r14 = ADD32(ctx->r15, 0X1);
    // 0x802C5CE8: sw          $t6, 0x1D0($sp)
    MEM_W(0X1D0, ctx->r29) = ctx->r14;
    // 0x802C5CEC: bne         $t6, $t3, L_802C5B9C
    if (ctx->r14 != ctx->r11) {
        // 0x802C5CF0: sw          $t2, 0x70($sp)
        MEM_W(0X70, ctx->r29) = ctx->r10;
            goto L_802C5B9C;
    }
    // 0x802C5CF0: sw          $t2, 0x70($sp)
    MEM_W(0X70, ctx->r29) = ctx->r10;
L_802C5CF4:
    // 0x802C5CF4: lw          $ra, 0x5C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X5C);
    // 0x802C5CF8: lw          $s0, 0x38($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X38);
    // 0x802C5CFC: lw          $s1, 0x3C($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X3C);
    // 0x802C5D00: lw          $s2, 0x40($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X40);
    // 0x802C5D04: lw          $s3, 0x44($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X44);
    // 0x802C5D08: lw          $s4, 0x48($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X48);
    // 0x802C5D0C: lw          $s5, 0x4C($sp)
    ctx->r21 = MEM_W(ctx->r29, 0X4C);
    // 0x802C5D10: lw          $s6, 0x50($sp)
    ctx->r22 = MEM_W(ctx->r29, 0X50);
    // 0x802C5D14: lw          $s7, 0x54($sp)
    ctx->r23 = MEM_W(ctx->r29, 0X54);
    // 0x802C5D18: lw          $fp, 0x58($sp)
    ctx->r30 = MEM_W(ctx->r29, 0X58);
    // 0x802C5D1C: jr          $ra
    // 0x802C5D20: addiu       $sp, $sp, 0x1D8
    ctx->r29 = ADD32(ctx->r29, 0X1D8);
    return;
    // 0x802C5D20: addiu       $sp, $sp, 0x1D8
    ctx->r29 = ADD32(ctx->r29, 0X1D8);
;}
RECOMP_FUNC void func_i9_802C5D24(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C5D24: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x802C5D28: addiu       $v0, $v0, -0x19C4
    ctx->r2 = ADD32(ctx->r2, -0X19C4);
    // 0x802C5D2C: lw          $t6, 0x0($v0)
    ctx->r14 = MEM_W(ctx->r2, 0X0);
    // 0x802C5D30: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x802C5D34: sw          $s0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r16;
    // 0x802C5D38: or          $s0, $a0, $zero
    ctx->r16 = ctx->r4 | 0;
    // 0x802C5D3C: beq         $t6, $zero, L_802C5D6C
    if (ctx->r14 == 0) {
        // 0x802C5D40: sw          $ra, 0x1C($sp)
        MEM_W(0X1C, ctx->r29) = ctx->r31;
            goto L_802C5D6C;
    }
    // 0x802C5D40: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x802C5D44: sw          $zero, 0x0($v0)
    MEM_W(0X0, ctx->r2) = 0;
    // 0x802C5D48: lui         $t7, 0x800E
    ctx->r15 = S32(0X800E << 16);
    // 0x802C5D4C: lw          $t7, -0x54DC($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X54DC);
    // 0x802C5D50: addiu       $at, $zero, 0x42
    ctx->r1 = ADD32(0, 0X42);
    // 0x802C5D54: bne         $t7, $at, L_802C5D6C
    if (ctx->r15 != ctx->r1) {
        // 0x802C5D58: nop
    
            goto L_802C5D6C;
    }
    // 0x802C5D58: nop

    // 0x802C5D5C: jal         0x80093C44
    // 0x802C5D60: nop

    func_80093C44(rdram, ctx);
        goto after_0;
    // 0x802C5D60: nop

    after_0:
    // 0x802C5D64: b           L_802C5E4C
    // 0x802C5D68: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
        goto L_802C5E4C;
    // 0x802C5D68: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
L_802C5D6C:
    // 0x802C5D6C: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x802C5D70: sw          $zero, -0x54D4($at)
    MEM_W(-0X54D4, ctx->r1) = 0;
    // 0x802C5D74: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
    // 0x802C5D78: addiu       $v1, $s0, 0x8
    ctx->r3 = ADD32(ctx->r16, 0X8);
    // 0x802C5D7C: lui         $t8, 0xE700
    ctx->r24 = S32(0XE700 << 16);
    // 0x802C5D80: lui         $t9, 0xED02
    ctx->r25 = S32(0XED02 << 16);
    // 0x802C5D84: addiu       $t9, $t9, 0x50
    ctx->r25 = ADD32(ctx->r25, 0X50);
    // 0x802C5D88: lui         $t0, 0x68
    ctx->r8 = S32(0X68 << 16);
    // 0x802C5D8C: addiu       $t0, $t0, -0x3C94
    ctx->r8 = ADD32(ctx->r8, -0X3C94);
    // 0x802C5D90: sw          $t8, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r24;
    // 0x802C5D94: sw          $zero, 0x4($v0)
    MEM_W(0X4, ctx->r2) = 0;
    { extern uint32_t wr64_experimental_viewport_borders(void); if (wr64_experimental_viewport_borders()) { ctx->r25 = 0xED000000U; ctx->r8 = 0x006A03C0U; } }
    // 0x802C5D98: sw          $t9, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r25;
    // 0x802C5D9C: sw          $t0, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r8;
    // 0x802C5DA0: jal         0x802C6750
    // 0x802C5DA4: addiu       $a0, $v1, 0x8
    ctx->r4 = ADD32(ctx->r3, 0X8);
    func_i9_802C6750(rdram, ctx);
        goto after_1;
    // 0x802C5DA4: addiu       $a0, $v1, 0x8
    ctx->r4 = ADD32(ctx->r3, 0X8);
    after_1:
    // 0x802C5DA8: lui         $t1, 0x800E
    ctx->r9 = S32(0X800E << 16);
    // 0x802C5DAC: lw          $t1, -0x54DC($t1)
    ctx->r9 = MEM_W(ctx->r9, -0X54DC);
    // 0x802C5DB0: addiu       $at, $zero, 0x42
    ctx->r1 = ADD32(0, 0X42);
    // 0x802C5DB4: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
    // 0x802C5DB8: bne         $t1, $at, L_802C5DE0
    if (ctx->r9 != ctx->r1) {
        // 0x802C5DBC: lui         $t3, 0x8023
        ctx->r11 = S32(0X8023 << 16);
            goto L_802C5DE0;
    }
    // 0x802C5DBC: lui         $t3, 0x8023
    ctx->r11 = S32(0X8023 << 16);
    // 0x802C5DC0: lui         $t2, 0x802D
    ctx->r10 = S32(0X802D << 16);
    // 0x802C5DC4: lw          $t2, -0x7F24($t2)
    ctx->r10 = MEM_W(ctx->r10, -0X7F24);
    // 0x802C5DC8: bnel        $t2, $zero, L_802C5E48
    if (ctx->r10 != 0) {
        // 0x802C5DCC: or          $v0, $s0, $zero
        ctx->r2 = ctx->r16 | 0;
            goto L_802C5E48;
    }
    goto skip_0;
    // 0x802C5DCC: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
    skip_0:
    // 0x802C5DD0: jal         0x802C5E5C
    // 0x802C5DD4: nop

    func_i9_802C5E5C(rdram, ctx);
        goto after_2;
    // 0x802C5DD4: nop

    after_2:
    // 0x802C5DD8: b           L_802C5E48
    // 0x802C5DDC: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
        goto L_802C5E48;
    // 0x802C5DDC: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
L_802C5DE0:
    // 0x802C5DE0: lh          $t3, -0x75EA($t3)
    ctx->r11 = MEM_H(ctx->r11, -0X75EA);
    // 0x802C5DE4: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x802C5DE8: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x802C5DEC: bnel        $t3, $at, L_802C5E48
    if (ctx->r11 != ctx->r1) {
        // 0x802C5DF0: or          $v0, $s0, $zero
        ctx->r2 = ctx->r16 | 0;
            goto L_802C5E48;
    }
    goto skip_1;
    // 0x802C5DF0: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
    skip_1:
    // 0x802C5DF4: lw          $v0, -0x19D0($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X19D0);
    // 0x802C5DF8: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x802C5DFC: beq         $v0, $at, L_802C5E2C
    if (ctx->r2 == ctx->r1) {
        // 0x802C5E00: addiu       $at, $zero, 0x3C
        ctx->r1 = ADD32(0, 0X3C);
            goto L_802C5E2C;
    }
    // 0x802C5E00: addiu       $at, $zero, 0x3C
    ctx->r1 = ADD32(0, 0X3C);
    // 0x802C5E04: beq         $v0, $at, L_802C5E1C
    if (ctx->r2 == ctx->r1) {
        // 0x802C5E08: addiu       $at, $zero, 0x50
        ctx->r1 = ADD32(0, 0X50);
            goto L_802C5E1C;
    }
    // 0x802C5E08: addiu       $at, $zero, 0x50
    ctx->r1 = ADD32(0, 0X50);
    // 0x802C5E0C: beq         $v0, $at, L_802C5E3C
    if (ctx->r2 == ctx->r1) {
        // 0x802C5E10: nop
    
            goto L_802C5E3C;
    }
    // 0x802C5E10: nop

    // 0x802C5E14: b           L_802C5E48
    // 0x802C5E18: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
        goto L_802C5E48;
    // 0x802C5E18: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
L_802C5E1C:
    // 0x802C5E1C: jal         0x801EC304
    // 0x802C5E20: nop

    func_801EC304(rdram, ctx);
        goto after_3;
    // 0x802C5E20: nop

    after_3:
    // 0x802C5E24: b           L_802C5E48
    // 0x802C5E28: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
        goto L_802C5E48;
    // 0x802C5E28: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
L_802C5E2C:
    // 0x802C5E2C: jal         0x801EB180
    // 0x802C5E30: nop

    func_801EB180(rdram, ctx);
        goto after_4;
    // 0x802C5E30: nop

    after_4:
    // 0x802C5E34: b           L_802C5E48
    // 0x802C5E38: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
        goto L_802C5E48;
    // 0x802C5E38: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
L_802C5E3C:
    // 0x802C5E3C: jal         0x801EC830
    // 0x802C5E40: nop

    func_801EC830(rdram, ctx);
        goto after_5;
    // 0x802C5E40: nop

    after_5:
    // 0x802C5E44: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
L_802C5E48:
    // 0x802C5E48: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
L_802C5E4C:
    // 0x802C5E4C: lw          $s0, 0x18($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X18);
    // 0x802C5E50: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x802C5E54: jr          $ra
    // 0x802C5E58: nop

    return;
    // 0x802C5E58: nop

;}
RECOMP_FUNC void func_i9_802C5E5C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C5E5C: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x802C5E60: lhu         $v0, -0x19A6($v0)
    ctx->r2 = MEM_HU(ctx->r2, -0X19A6);
    // 0x802C5E64: addiu       $sp, $sp, -0x28
    ctx->r29 = ADD32(ctx->r29, -0X28);
    // 0x802C5E68: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x802C5E6C: andi        $t6, $v0, 0xB000
    ctx->r14 = ctx->r2 & 0XB000;
    // 0x802C5E70: beq         $t6, $zero, L_802C600C
    if (ctx->r14 == 0) {
        // 0x802C5E74: sw          $zero, 0x24($sp)
        MEM_W(0X24, ctx->r29) = 0;
            goto L_802C600C;
    }
    // 0x802C5E74: sw          $zero, 0x24($sp)
    MEM_W(0X24, ctx->r29) = 0;
    // 0x802C5E78: lui         $t2, 0x802D
    ctx->r10 = S32(0X802D << 16);
    // 0x802C5E7C: addiu       $t2, $t2, -0x7F1C
    ctx->r10 = ADD32(ctx->r10, -0X7F1C);
    // 0x802C5E80: lw          $t7, 0x8($t2)
    ctx->r15 = MEM_W(ctx->r10, 0X8);
    // 0x802C5E84: addiu       $at, $zero, 0xA
    ctx->r1 = ADD32(0, 0XA);
    // 0x802C5E88: lui         $v1, 0x802D
    ctx->r3 = S32(0X802D << 16);
    // 0x802C5E8C: bne         $t7, $at, L_802C5FB4
    if (ctx->r15 != ctx->r1) {
        // 0x802C5E90: addiu       $v1, $v1, -0x7E5C
        ctx->r3 = ADD32(ctx->r3, -0X7E5C);
            goto L_802C5FB4;
    }
    // 0x802C5E90: addiu       $v1, $v1, -0x7E5C
    ctx->r3 = ADD32(ctx->r3, -0X7E5C);
    // 0x802C5E94: lui         $a0, 0x802D
    ctx->r4 = S32(0X802D << 16);
    // 0x802C5E98: addiu       $a0, $a0, -0x7F40
    ctx->r4 = ADD32(ctx->r4, -0X7F40);
    // 0x802C5E9C: lw          $v0, 0x0($a0)
    ctx->r2 = MEM_W(ctx->r4, 0X0);
    // 0x802C5EA0: lui         $v1, 0x802D
    ctx->r3 = S32(0X802D << 16);
    // 0x802C5EA4: addiu       $v1, $v1, -0x7F3C
    ctx->r3 = ADD32(ctx->r3, -0X7F3C);
    // 0x802C5EA8: beq         $v0, $zero, L_802C5EC0
    if (ctx->r2 == 0) {
        // 0x802C5EAC: addiu       $t1, $zero, 0x1
        ctx->r9 = ADD32(0, 0X1);
            goto L_802C5EC0;
    }
    // 0x802C5EAC: addiu       $t1, $zero, 0x1
    ctx->r9 = ADD32(0, 0X1);
    // 0x802C5EB0: beq         $v0, $t1, L_802C5F14
    if (ctx->r2 == ctx->r9) {
        // 0x802C5EB4: lui         $v1, 0x802D
        ctx->r3 = S32(0X802D << 16);
            goto L_802C5F14;
    }
    // 0x802C5EB4: lui         $v1, 0x802D
    ctx->r3 = S32(0X802D << 16);
    // 0x802C5EB8: b           L_802C5FF4
    // 0x802C5EBC: lw          $t4, 0x24($sp)
    ctx->r12 = MEM_W(ctx->r29, 0X24);
        goto L_802C5FF4;
    // 0x802C5EBC: lw          $t4, 0x24($sp)
    ctx->r12 = MEM_W(ctx->r29, 0X24);
L_802C5EC0:
    // 0x802C5EC0: lw          $v0, 0x0($v1)
    ctx->r2 = MEM_W(ctx->r3, 0X0);
    // 0x802C5EC4: addiu       $t8, $zero, 0x1
    ctx->r24 = ADD32(0, 0X1);
    // 0x802C5EC8: sw          $t8, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r24;
    // 0x802C5ECC: bne         $v0, $zero, L_802C5EE8
    if (ctx->r2 != 0) {
        // 0x802C5ED0: lui         $t0, 0x802D
        ctx->r8 = S32(0X802D << 16);
            goto L_802C5EE8;
    }
    // 0x802C5ED0: lui         $t0, 0x802D
    ctx->r8 = S32(0X802D << 16);
    // 0x802C5ED4: addiu       $t0, $t0, -0x7F38
    ctx->r8 = ADD32(ctx->r8, -0X7F38);
    // 0x802C5ED8: addiu       $t1, $zero, 0x1
    ctx->r9 = ADD32(0, 0X1);
    // 0x802C5EDC: sw          $t1, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r9;
    // 0x802C5EE0: b           L_802C5FF0
    // 0x802C5EE4: sw          $t1, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r9;
        goto L_802C5FF0;
    // 0x802C5EE4: sw          $t1, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r9;
L_802C5EE8:
    // 0x802C5EE8: addiu       $t1, $zero, 0x1
    ctx->r9 = ADD32(0, 0X1);
    // 0x802C5EEC: bne         $t1, $v0, L_802C5F04
    if (ctx->r9 != ctx->r2) {
        // 0x802C5EF0: lui         $t0, 0x802D
        ctx->r8 = S32(0X802D << 16);
            goto L_802C5F04;
    }
    // 0x802C5EF0: lui         $t0, 0x802D
    ctx->r8 = S32(0X802D << 16);
    // 0x802C5EF4: addiu       $t0, $t0, -0x7F38
    ctx->r8 = ADD32(ctx->r8, -0X7F38);
    // 0x802C5EF8: sw          $zero, 0x0($t0)
    MEM_W(0X0, ctx->r8) = 0;
    // 0x802C5EFC: b           L_802C5FF0
    // 0x802C5F00: sw          $t1, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r9;
        goto L_802C5FF0;
    // 0x802C5F00: sw          $t1, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r9;
L_802C5F04:
    // 0x802C5F04: jal         0x802C802C
    // 0x802C5F08: addiu       $a0, $zero, 0x3C
    ctx->r4 = ADD32(0, 0X3C);
    func_i9_802C802C(rdram, ctx);
        goto after_0;
    // 0x802C5F08: addiu       $a0, $zero, 0x3C
    ctx->r4 = ADD32(0, 0X3C);
    after_0:
    // 0x802C5F0C: b           L_802C5FF4
    // 0x802C5F10: lw          $t4, 0x24($sp)
    ctx->r12 = MEM_W(ctx->r29, 0X24);
        goto L_802C5FF4;
    // 0x802C5F10: lw          $t4, 0x24($sp)
    ctx->r12 = MEM_W(ctx->r29, 0X24);
L_802C5F14:
    // 0x802C5F14: lui         $t0, 0x802D
    ctx->r8 = S32(0X802D << 16);
    // 0x802C5F18: addiu       $t3, $zero, 0x2
    ctx->r11 = ADD32(0, 0X2);
    // 0x802C5F1C: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C5F20: addiu       $t0, $t0, -0x7F38
    ctx->r8 = ADD32(ctx->r8, -0X7F38);
    // 0x802C5F24: sw          $t3, -0x7F24($at)
    MEM_W(-0X7F24, ctx->r1) = ctx->r11;
    // 0x802C5F28: lw          $t4, 0x0($t0)
    ctx->r12 = MEM_W(ctx->r8, 0X0);
    // 0x802C5F2C: addiu       $v1, $v1, -0x7F3C
    ctx->r3 = ADD32(ctx->r3, -0X7F3C);
    // 0x802C5F30: lw          $t6, 0x0($v1)
    ctx->r14 = MEM_W(ctx->r3, 0X0);
    // 0x802C5F34: lui         $a3, 0x800E
    ctx->r7 = S32(0X800E << 16);
    // 0x802C5F38: sll         $t5, $t4, 2
    ctx->r13 = S32(ctx->r12 << 2);
    // 0x802C5F3C: addiu       $t9, $zero, 0x1
    ctx->r25 = ADD32(0, 0X1);
    // 0x802C5F40: addu        $a3, $a3, $t5
    ctx->r7 = ADD32(ctx->r7, ctx->r13);
    // 0x802C5F44: sw          $t9, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r25;
    // 0x802C5F48: bne         $t6, $zero, L_802C5F58
    if (ctx->r14 != 0) {
        // 0x802C5F4C: lw          $a3, -0x5528($a3)
        ctx->r7 = MEM_W(ctx->r7, -0X5528);
            goto L_802C5F58;
    }
    // 0x802C5F4C: lw          $a3, -0x5528($a3)
    ctx->r7 = MEM_W(ctx->r7, -0X5528);
    // 0x802C5F50: b           L_802C5F5C
    // 0x802C5F54: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
        goto L_802C5F5C;
    // 0x802C5F54: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
L_802C5F58:
    // 0x802C5F58: addiu       $v0, $zero, 0x2
    ctx->r2 = ADD32(0, 0X2);
L_802C5F5C:
    // 0x802C5F5C: lui         $a0, 0x802D
    ctx->r4 = S32(0X802D << 16);
    // 0x802C5F60: addiu       $a0, $a0, -0x7F0C
    ctx->r4 = ADD32(ctx->r4, -0X7F0C);
    // 0x802C5F64: addiu       $a1, $zero, 0x1A8
    ctx->r5 = ADD32(0, 0X1A8);
    // 0x802C5F68: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x802C5F6C: sw          $v0, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r2;
    // 0x802C5F70: jal         0x802C7194
    // 0x802C5F74: sw          $a3, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r7;
    func_i9_802C7194(rdram, ctx);
        goto after_1;
    // 0x802C5F74: sw          $a3, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r7;
    after_1:
    // 0x802C5F78: addiu       $t7, $zero, 0x2
    ctx->r15 = ADD32(0, 0X2);
    // 0x802C5F7C: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C5F80: lui         $a0, 0x802D
    ctx->r4 = S32(0X802D << 16);
    // 0x802C5F84: lw          $a3, 0x20($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X20);
    // 0x802C5F88: sw          $t7, -0x7F20($at)
    MEM_W(-0X7F20, ctx->r1) = ctx->r15;
    // 0x802C5F8C: addiu       $a0, $a0, -0x7EEC
    ctx->r4 = ADD32(ctx->r4, -0X7EEC);
    // 0x802C5F90: addiu       $a1, $zero, 0x1A8
    ctx->r5 = ADD32(0, 0X1A8);
    // 0x802C5F94: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x802C5F98: jal         0x802C7194
    // 0x802C5F9C: sw          $zero, 0x10($sp)
    MEM_W(0X10, ctx->r29) = 0;
    func_i9_802C7194(rdram, ctx);
        goto after_2;
    // 0x802C5F9C: sw          $zero, 0x10($sp)
    MEM_W(0X10, ctx->r29) = 0;
    after_2:
    // 0x802C5FA0: addiu       $a0, $zero, 0x2A
    ctx->r4 = ADD32(0, 0X2A);
    // 0x802C5FA4: jal         0x800C37F4
    // 0x802C5FA8: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_3;
    // 0x802C5FA8: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_3:
    // 0x802C5FAC: b           L_802C5FF4
    // 0x802C5FB0: lw          $t4, 0x24($sp)
    ctx->r12 = MEM_W(ctx->r29, 0X24);
        goto L_802C5FF4;
    // 0x802C5FB0: lw          $t4, 0x24($sp)
    ctx->r12 = MEM_W(ctx->r29, 0X24);
L_802C5FB4:
    // 0x802C5FB4: lw          $t8, 0x0($v1)
    ctx->r24 = MEM_W(ctx->r3, 0X0);
    // 0x802C5FB8: lui         $t3, 0x800E
    ctx->r11 = S32(0X800E << 16);
    // 0x802C5FBC: beql        $t8, $zero, L_802C5FF4
    if (ctx->r24 == 0) {
        // 0x802C5FC0: lw          $t4, 0x24($sp)
        ctx->r12 = MEM_W(ctx->r29, 0X24);
            goto L_802C5FF4;
    }
    goto skip_0;
    // 0x802C5FC0: lw          $t4, 0x24($sp)
    ctx->r12 = MEM_W(ctx->r29, 0X24);
    skip_0:
    // 0x802C5FC4: lw          $t3, -0x55F8($t3)
    ctx->r11 = MEM_W(ctx->r11, -0X55F8);
    // 0x802C5FC8: addiu       $t9, $zero, 0x1
    ctx->r25 = ADD32(0, 0X1);
    // 0x802C5FCC: sw          $t9, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r25;
    // 0x802C5FD0: beq         $t3, $zero, L_802C5FE8
    if (ctx->r11 == 0) {
        // 0x802C5FD4: nop
    
            goto L_802C5FE8;
    }
    // 0x802C5FD4: nop

    // 0x802C5FD8: jal         0x802C802C
    // 0x802C5FDC: addiu       $a0, $zero, 0x2
    ctx->r4 = ADD32(0, 0X2);
    func_i9_802C802C(rdram, ctx);
        goto after_4;
    // 0x802C5FDC: addiu       $a0, $zero, 0x2
    ctx->r4 = ADD32(0, 0X2);
    after_4:
    // 0x802C5FE0: b           L_802C5FF4
    // 0x802C5FE4: lw          $t4, 0x24($sp)
    ctx->r12 = MEM_W(ctx->r29, 0X24);
        goto L_802C5FF4;
    // 0x802C5FE4: lw          $t4, 0x24($sp)
    ctx->r12 = MEM_W(ctx->r29, 0X24);
L_802C5FE8:
    // 0x802C5FE8: jal         0x802C802C
    // 0x802C5FEC: addiu       $a0, $zero, 0x50
    ctx->r4 = ADD32(0, 0X50);
    func_i9_802C802C(rdram, ctx);
        goto after_5;
    // 0x802C5FEC: addiu       $a0, $zero, 0x50
    ctx->r4 = ADD32(0, 0X50);
    after_5:
L_802C5FF0:
    // 0x802C5FF0: lw          $t4, 0x24($sp)
    ctx->r12 = MEM_W(ctx->r29, 0X24);
L_802C5FF4:
    // 0x802C5FF4: beq         $t4, $zero, L_802C6740
    if (ctx->r12 == 0) {
        // 0x802C5FF8: addiu       $a0, $zero, 0x11
        ctx->r4 = ADD32(0, 0X11);
            goto L_802C6740;
    }
    // 0x802C5FF8: addiu       $a0, $zero, 0x11
    ctx->r4 = ADD32(0, 0X11);
    // 0x802C5FFC: jal         0x800C37F4
    // 0x802C6000: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_6;
    // 0x802C6000: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_6:
    // 0x802C6004: b           L_802C6744
    // 0x802C6008: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
        goto L_802C6744;
    // 0x802C6008: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
L_802C600C:
    // 0x802C600C: andi        $t5, $v0, 0x4000
    ctx->r13 = ctx->r2 & 0X4000;
    // 0x802C6010: beq         $t5, $zero, L_802C6118
    if (ctx->r13 == 0) {
        // 0x802C6014: lui         $v1, 0x802D
        ctx->r3 = S32(0X802D << 16);
            goto L_802C6118;
    }
    // 0x802C6014: lui         $v1, 0x802D
    ctx->r3 = S32(0X802D << 16);
    // 0x802C6018: addiu       $v1, $v1, -0x7E5C
    ctx->r3 = ADD32(ctx->r3, -0X7E5C);
    // 0x802C601C: lw          $t6, 0x0($v1)
    ctx->r14 = MEM_W(ctx->r3, 0X0);
    // 0x802C6020: lui         $t2, 0x802D
    ctx->r10 = S32(0X802D << 16);
    // 0x802C6024: addiu       $t2, $t2, -0x7F1C
    ctx->r10 = ADD32(ctx->r10, -0X7F1C);
    // 0x802C6028: bne         $t6, $zero, L_802C6118
    if (ctx->r14 != 0) {
        // 0x802C602C: nop
    
            goto L_802C6118;
    }
    // 0x802C602C: nop

    // 0x802C6030: lw          $t7, 0x8($t2)
    ctx->r15 = MEM_W(ctx->r10, 0X8);
    // 0x802C6034: addiu       $at, $zero, 0xA
    ctx->r1 = ADD32(0, 0XA);
    // 0x802C6038: lui         $a0, 0x802D
    ctx->r4 = S32(0X802D << 16);
    // 0x802C603C: bne         $t7, $at, L_802C6084
    if (ctx->r15 != ctx->r1) {
        // 0x802C6040: addiu       $a0, $a0, -0x7F0C
        ctx->r4 = ADD32(ctx->r4, -0X7F0C);
            goto L_802C6084;
    }
    // 0x802C6040: addiu       $a0, $a0, -0x7F0C
    ctx->r4 = ADD32(ctx->r4, -0X7F0C);
    // 0x802C6044: lui         $a0, 0x802D
    ctx->r4 = S32(0X802D << 16);
    // 0x802C6048: addiu       $a0, $a0, -0x7F40
    ctx->r4 = ADD32(ctx->r4, -0X7F40);
    // 0x802C604C: lw          $v0, 0x0($a0)
    ctx->r2 = MEM_W(ctx->r4, 0X0);
    // 0x802C6050: addiu       $t1, $zero, 0x1
    ctx->r9 = ADD32(0, 0X1);
    // 0x802C6054: beq         $v0, $zero, L_802C606C
    if (ctx->r2 == 0) {
        // 0x802C6058: nop
    
            goto L_802C606C;
    }
    // 0x802C6058: nop

    // 0x802C605C: beq         $v0, $t1, L_802C607C
    if (ctx->r2 == ctx->r9) {
        // 0x802C6060: nop
    
            goto L_802C607C;
    }
    // 0x802C6060: nop

    // 0x802C6064: b           L_802C6108
    // 0x802C6068: addiu       $a0, $zero, 0x16
    ctx->r4 = ADD32(0, 0X16);
        goto L_802C6108;
    // 0x802C6068: addiu       $a0, $zero, 0x16
    ctx->r4 = ADD32(0, 0X16);
L_802C606C:
    // 0x802C606C: jal         0x802C802C
    // 0x802C6070: addiu       $a0, $zero, 0x3C
    ctx->r4 = ADD32(0, 0X3C);
    func_i9_802C802C(rdram, ctx);
        goto after_7;
    // 0x802C6070: addiu       $a0, $zero, 0x3C
    ctx->r4 = ADD32(0, 0X3C);
    after_7:
    // 0x802C6074: b           L_802C6108
    // 0x802C6078: addiu       $a0, $zero, 0x16
    ctx->r4 = ADD32(0, 0X16);
        goto L_802C6108;
    // 0x802C6078: addiu       $a0, $zero, 0x16
    ctx->r4 = ADD32(0, 0X16);
L_802C607C:
    // 0x802C607C: b           L_802C6104
    // 0x802C6080: sw          $zero, 0x0($a0)
    MEM_W(0X0, ctx->r4) = 0;
        goto L_802C6104;
    // 0x802C6080: sw          $zero, 0x0($a0)
    MEM_W(0X0, ctx->r4) = 0;
L_802C6084:
    // 0x802C6084: lw          $v1, 0xC($t2)
    ctx->r3 = MEM_W(ctx->r10, 0XC);
    // 0x802C6088: addiu       $t1, $zero, 0x1
    ctx->r9 = ADD32(0, 0X1);
    // 0x802C608C: addiu       $a1, $zero, -0x1A8
    ctx->r5 = ADD32(0, -0X1A8);
    // 0x802C6090: beq         $t1, $v1, L_802C60A0
    if (ctx->r9 == ctx->r3) {
        // 0x802C6094: or          $a2, $zero, $zero
        ctx->r6 = 0 | 0;
            goto L_802C60A0;
    }
    // 0x802C6094: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x802C6098: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x802C609C: bne         $v1, $at, L_802C60B0
    if (ctx->r3 != ctx->r1) {
        // 0x802C60A0: lui         $v1, 0x802D
        ctx->r3 = S32(0X802D << 16);
            goto L_802C60B0;
    }
L_802C60A0:
    // 0x802C60A0: lui         $v1, 0x802D
    ctx->r3 = S32(0X802D << 16);
    // 0x802C60A4: addiu       $v1, $v1, -0x7F3C
    ctx->r3 = ADD32(ctx->r3, -0X7F3C);
    // 0x802C60A8: b           L_802C60BC
    // 0x802C60AC: sw          $zero, 0x0($v1)
    MEM_W(0X0, ctx->r3) = 0;
        goto L_802C60BC;
    // 0x802C60AC: sw          $zero, 0x0($v1)
    MEM_W(0X0, ctx->r3) = 0;
L_802C60B0:
    // 0x802C60B0: lui         $v1, 0x802D
    ctx->r3 = S32(0X802D << 16);
    // 0x802C60B4: addiu       $v1, $v1, -0x7F3C
    ctx->r3 = ADD32(ctx->r3, -0X7F3C);
    // 0x802C60B8: sw          $t1, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r9;
L_802C60BC:
    // 0x802C60BC: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C60C0: sw          $t1, -0x7F24($at)
    MEM_W(-0X7F24, ctx->r1) = ctx->r9;
    // 0x802C60C4: addiu       $a3, $zero, 0xA
    ctx->r7 = ADD32(0, 0XA);
    // 0x802C60C8: jal         0x802C7194
    // 0x802C60CC: sw          $zero, 0x10($sp)
    MEM_W(0X10, ctx->r29) = 0;
    func_i9_802C7194(rdram, ctx);
        goto after_8;
    // 0x802C60CC: sw          $zero, 0x10($sp)
    MEM_W(0X10, ctx->r29) = 0;
    after_8:
    // 0x802C60D0: addiu       $t1, $zero, 0x1
    ctx->r9 = ADD32(0, 0X1);
    // 0x802C60D4: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C60D8: lui         $a0, 0x802D
    ctx->r4 = S32(0X802D << 16);
    // 0x802C60DC: sw          $t1, -0x7F20($at)
    MEM_W(-0X7F20, ctx->r1) = ctx->r9;
    // 0x802C60E0: addiu       $a0, $a0, -0x7EEC
    ctx->r4 = ADD32(ctx->r4, -0X7EEC);
    // 0x802C60E4: addiu       $a1, $zero, -0x140
    ctx->r5 = ADD32(0, -0X140);
    // 0x802C60E8: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x802C60EC: addiu       $a3, $zero, 0xA
    ctx->r7 = ADD32(0, 0XA);
    // 0x802C60F0: jal         0x802C7194
    // 0x802C60F4: sw          $zero, 0x10($sp)
    MEM_W(0X10, ctx->r29) = 0;
    func_i9_802C7194(rdram, ctx);
        goto after_9;
    // 0x802C60F4: sw          $zero, 0x10($sp)
    MEM_W(0X10, ctx->r29) = 0;
    after_9:
    // 0x802C60F8: addiu       $a0, $zero, 0x2A
    ctx->r4 = ADD32(0, 0X2A);
    // 0x802C60FC: jal         0x800C37F4
    // 0x802C6100: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_10;
    // 0x802C6100: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_10:
L_802C6104:
    // 0x802C6104: addiu       $a0, $zero, 0x16
    ctx->r4 = ADD32(0, 0X16);
L_802C6108:
    // 0x802C6108: jal         0x800C37F4
    // 0x802C610C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_11;
    // 0x802C610C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_11:
    // 0x802C6110: b           L_802C6744
    // 0x802C6114: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
        goto L_802C6744;
    // 0x802C6114: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
L_802C6118:
    // 0x802C6118: lui         $v1, 0x802D
    ctx->r3 = S32(0X802D << 16);
    // 0x802C611C: andi        $t8, $v0, 0x800
    ctx->r24 = ctx->r2 & 0X800;
    // 0x802C6120: beq         $t8, $zero, L_802C6278
    if (ctx->r24 == 0) {
        // 0x802C6124: addiu       $v1, $v1, -0x7E5C
        ctx->r3 = ADD32(ctx->r3, -0X7E5C);
            goto L_802C6278;
    }
    // 0x802C6124: addiu       $v1, $v1, -0x7E5C
    ctx->r3 = ADD32(ctx->r3, -0X7E5C);
    // 0x802C6128: lui         $t2, 0x802D
    ctx->r10 = S32(0X802D << 16);
    // 0x802C612C: addiu       $t2, $t2, -0x7F1C
    ctx->r10 = ADD32(ctx->r10, -0X7F1C);
    // 0x802C6130: lw          $t9, 0x8($t2)
    ctx->r25 = MEM_W(ctx->r10, 0X8);
    // 0x802C6134: addiu       $at, $zero, 0xA
    ctx->r1 = ADD32(0, 0XA);
    // 0x802C6138: lui         $t0, 0x802D
    ctx->r8 = S32(0X802D << 16);
    // 0x802C613C: bne         $t9, $at, L_802C61AC
    if (ctx->r25 != ctx->r1) {
        // 0x802C6140: addiu       $t0, $t0, -0x7F38
        ctx->r8 = ADD32(ctx->r8, -0X7F38);
            goto L_802C61AC;
    }
    // 0x802C6140: addiu       $t0, $t0, -0x7F38
    ctx->r8 = ADD32(ctx->r8, -0X7F38);
    // 0x802C6144: lui         $a0, 0x802D
    ctx->r4 = S32(0X802D << 16);
    // 0x802C6148: addiu       $a0, $a0, -0x7F40
    ctx->r4 = ADD32(ctx->r4, -0X7F40);
    // 0x802C614C: lw          $t3, 0x0($a0)
    ctx->r11 = MEM_W(ctx->r4, 0X0);
    // 0x802C6150: addiu       $t1, $zero, 0x1
    ctx->r9 = ADD32(0, 0X1);
    // 0x802C6154: lui         $v1, 0x802D
    ctx->r3 = S32(0X802D << 16);
    // 0x802C6158: bne         $t1, $t3, L_802C6258
    if (ctx->r9 != ctx->r11) {
        // 0x802C615C: addiu       $v1, $v1, -0x7F3C
        ctx->r3 = ADD32(ctx->r3, -0X7F3C);
            goto L_802C6258;
    }
    // 0x802C615C: addiu       $v1, $v1, -0x7F3C
    ctx->r3 = ADD32(ctx->r3, -0X7F3C);
    // 0x802C6160: lui         $t0, 0x802D
    ctx->r8 = S32(0X802D << 16);
    // 0x802C6164: addiu       $t0, $t0, -0x7F38
    ctx->r8 = ADD32(ctx->r8, -0X7F38);
    // 0x802C6168: lw          $t5, 0x0($t0)
    ctx->r13 = MEM_W(ctx->r8, 0X0);
    // 0x802C616C: lw          $t7, 0x0($v1)
    ctx->r15 = MEM_W(ctx->r3, 0X0);
    // 0x802C6170: addiu       $t4, $zero, 0x1
    ctx->r12 = ADD32(0, 0X1);
    // 0x802C6174: addiu       $t6, $t5, -0x1
    ctx->r14 = ADD32(ctx->r13, -0X1);
    // 0x802C6178: sw          $t4, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r12;
    // 0x802C617C: bne         $t7, $zero, L_802C618C
    if (ctx->r15 != 0) {
        // 0x802C6180: sw          $t6, 0x0($t0)
        MEM_W(0X0, ctx->r8) = ctx->r14;
            goto L_802C618C;
    }
    // 0x802C6180: sw          $t6, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r14;
    // 0x802C6184: b           L_802C6190
    // 0x802C6188: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
        goto L_802C6190;
    // 0x802C6188: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
L_802C618C:
    // 0x802C618C: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_802C6190:
    // 0x802C6190: lw          $t8, 0x0($t0)
    ctx->r24 = MEM_W(ctx->r8, 0X0);
    // 0x802C6194: addiu       $t9, $zero, 0x8
    ctx->r25 = ADD32(0, 0X8);
    // 0x802C6198: slt         $at, $t8, $v0
    ctx->r1 = SIGNED(ctx->r24) < SIGNED(ctx->r2) ? 1 : 0;
    // 0x802C619C: beql        $at, $zero, L_802C625C
    if (ctx->r1 == 0) {
        // 0x802C61A0: lw          $t3, 0x24($sp)
        ctx->r11 = MEM_W(ctx->r29, 0X24);
            goto L_802C625C;
    }
    goto skip_1;
    // 0x802C61A0: lw          $t3, 0x24($sp)
    ctx->r11 = MEM_W(ctx->r29, 0X24);
    skip_1:
    // 0x802C61A4: b           L_802C6258
    // 0x802C61A8: sw          $t9, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r25;
        goto L_802C6258;
    // 0x802C61A8: sw          $t9, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r25;
L_802C61AC:
    // 0x802C61AC: lw          $t3, 0x0($t0)
    ctx->r11 = MEM_W(ctx->r8, 0X0);
    // 0x802C61B0: lw          $v1, 0xC($t2)
    ctx->r3 = MEM_W(ctx->r10, 0XC);
    // 0x802C61B4: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x802C61B8: addiu       $t4, $t3, -0x1
    ctx->r12 = ADD32(ctx->r11, -0X1);
    // 0x802C61BC: bne         $v1, $at, L_802C61D8
    if (ctx->r3 != ctx->r1) {
        // 0x802C61C0: sw          $t4, 0x0($t0)
        MEM_W(0X0, ctx->r8) = ctx->r12;
            goto L_802C61D8;
    }
    // 0x802C61C0: sw          $t4, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r12;
    // 0x802C61C4: bgez        $t4, L_802C61EC
    if (SIGNED(ctx->r12) >= 0) {
        // 0x802C61C8: or          $v0, $t4, $zero
        ctx->r2 = ctx->r12 | 0;
            goto L_802C61EC;
    }
    // 0x802C61C8: or          $v0, $t4, $zero
    ctx->r2 = ctx->r12 | 0;
    // 0x802C61CC: addiu       $v0, $zero, 0x8
    ctx->r2 = ADD32(0, 0X8);
    // 0x802C61D0: b           L_802C61EC
    // 0x802C61D4: sw          $v0, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r2;
        goto L_802C61EC;
    // 0x802C61D4: sw          $v0, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r2;
L_802C61D8:
    // 0x802C61D8: lw          $v0, 0x0($t0)
    ctx->r2 = MEM_W(ctx->r8, 0X0);
    // 0x802C61DC: bgtzl       $v0, L_802C61F0
    if (SIGNED(ctx->r2) > 0) {
        // 0x802C61E0: sll         $t7, $v0, 2
        ctx->r15 = S32(ctx->r2 << 2);
            goto L_802C61F0;
    }
    goto skip_2;
    // 0x802C61E0: sll         $t7, $v0, 2
    ctx->r15 = S32(ctx->r2 << 2);
    skip_2:
    // 0x802C61E4: addiu       $v0, $zero, 0x8
    ctx->r2 = ADD32(0, 0X8);
    // 0x802C61E8: sw          $v0, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r2;
L_802C61EC:
    // 0x802C61EC: sll         $t7, $v0, 2
    ctx->r15 = S32(ctx->r2 << 2);
L_802C61F0:
    // 0x802C61F0: lui         $a3, 0x800E
    ctx->r7 = S32(0X800E << 16);
    // 0x802C61F4: addu        $a3, $a3, $t7
    ctx->r7 = ADD32(ctx->r7, ctx->r15);
    // 0x802C61F8: lw          $a3, -0x5528($a3)
    ctx->r7 = MEM_W(ctx->r7, -0X5528);
    // 0x802C61FC: addiu       $t8, $zero, 0x4
    ctx->r24 = ADD32(0, 0X4);
    // 0x802C6200: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C6204: lui         $a0, 0x802D
    ctx->r4 = S32(0X802D << 16);
    // 0x802C6208: sw          $t8, -0x7F24($at)
    MEM_W(-0X7F24, ctx->r1) = ctx->r24;
    // 0x802C620C: addiu       $a0, $a0, -0x7F0C
    ctx->r4 = ADD32(ctx->r4, -0X7F0C);
    // 0x802C6210: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C6214: addiu       $a2, $zero, -0xF0
    ctx->r6 = ADD32(0, -0XF0);
    // 0x802C6218: sw          $v1, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r3;
    // 0x802C621C: jal         0x802C7194
    // 0x802C6220: sw          $a3, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r7;
    func_i9_802C7194(rdram, ctx);
        goto after_12;
    // 0x802C6220: sw          $a3, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r7;
    after_12:
    // 0x802C6224: addiu       $t9, $zero, 0x4
    ctx->r25 = ADD32(0, 0X4);
    // 0x802C6228: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C622C: lui         $a0, 0x802D
    ctx->r4 = S32(0X802D << 16);
    // 0x802C6230: lw          $a3, 0x20($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X20);
    // 0x802C6234: sw          $t9, -0x7F20($at)
    MEM_W(-0X7F20, ctx->r1) = ctx->r25;
    // 0x802C6238: addiu       $a0, $a0, -0x7EEC
    ctx->r4 = ADD32(ctx->r4, -0X7EEC);
    // 0x802C623C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C6240: addiu       $a2, $zero, -0xF0
    ctx->r6 = ADD32(0, -0XF0);
    // 0x802C6244: jal         0x802C7194
    // 0x802C6248: sw          $zero, 0x10($sp)
    MEM_W(0X10, ctx->r29) = 0;
    func_i9_802C7194(rdram, ctx);
        goto after_13;
    // 0x802C6248: sw          $zero, 0x10($sp)
    MEM_W(0X10, ctx->r29) = 0;
    after_13:
    // 0x802C624C: addiu       $a0, $zero, 0x2A
    ctx->r4 = ADD32(0, 0X2A);
    // 0x802C6250: jal         0x800C37F4
    // 0x802C6254: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_14;
    // 0x802C6254: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_14:
L_802C6258:
    // 0x802C6258: lw          $t3, 0x24($sp)
    ctx->r11 = MEM_W(ctx->r29, 0X24);
L_802C625C:
    // 0x802C625C: addiu       $a0, $zero, 0x10
    ctx->r4 = ADD32(0, 0X10);
    // 0x802C6260: beql        $t3, $zero, L_802C6744
    if (ctx->r11 == 0) {
        // 0x802C6264: lw          $ra, 0x1C($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X1C);
            goto L_802C6744;
    }
    goto skip_3;
    // 0x802C6264: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    skip_3:
    // 0x802C6268: jal         0x800C37F4
    // 0x802C626C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_15;
    // 0x802C626C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_15:
    // 0x802C6270: b           L_802C6744
    // 0x802C6274: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
        goto L_802C6744;
    // 0x802C6274: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
L_802C6278:
    // 0x802C6278: andi        $t4, $v0, 0x400
    ctx->r12 = ctx->r2 & 0X400;
    // 0x802C627C: beq         $t4, $zero, L_802C63CC
    if (ctx->r12 == 0) {
        // 0x802C6280: andi        $t6, $v0, 0x200
        ctx->r14 = ctx->r2 & 0X200;
            goto L_802C63CC;
    }
    // 0x802C6280: andi        $t6, $v0, 0x200
    ctx->r14 = ctx->r2 & 0X200;
    // 0x802C6284: lui         $t2, 0x802D
    ctx->r10 = S32(0X802D << 16);
    // 0x802C6288: addiu       $t2, $t2, -0x7F1C
    ctx->r10 = ADD32(ctx->r10, -0X7F1C);
    // 0x802C628C: lw          $t5, 0x8($t2)
    ctx->r13 = MEM_W(ctx->r10, 0X8);
    // 0x802C6290: addiu       $at, $zero, 0xA
    ctx->r1 = ADD32(0, 0XA);
    // 0x802C6294: lui         $t0, 0x802D
    ctx->r8 = S32(0X802D << 16);
    // 0x802C6298: bne         $t5, $at, L_802C6304
    if (ctx->r13 != ctx->r1) {
        // 0x802C629C: addiu       $t0, $t0, -0x7F38
        ctx->r8 = ADD32(ctx->r8, -0X7F38);
            goto L_802C6304;
    }
    // 0x802C629C: addiu       $t0, $t0, -0x7F38
    ctx->r8 = ADD32(ctx->r8, -0X7F38);
    // 0x802C62A0: lui         $a0, 0x802D
    ctx->r4 = S32(0X802D << 16);
    // 0x802C62A4: addiu       $a0, $a0, -0x7F40
    ctx->r4 = ADD32(ctx->r4, -0X7F40);
    // 0x802C62A8: lw          $t6, 0x0($a0)
    ctx->r14 = MEM_W(ctx->r4, 0X0);
    // 0x802C62AC: addiu       $t1, $zero, 0x1
    ctx->r9 = ADD32(0, 0X1);
    // 0x802C62B0: lui         $v1, 0x802D
    ctx->r3 = S32(0X802D << 16);
    // 0x802C62B4: bne         $t1, $t6, L_802C63AC
    if (ctx->r9 != ctx->r14) {
        // 0x802C62B8: addiu       $v1, $v1, -0x7F3C
        ctx->r3 = ADD32(ctx->r3, -0X7F3C);
            goto L_802C63AC;
    }
    // 0x802C62B8: addiu       $v1, $v1, -0x7F3C
    ctx->r3 = ADD32(ctx->r3, -0X7F3C);
    // 0x802C62BC: lui         $t0, 0x802D
    ctx->r8 = S32(0X802D << 16);
    // 0x802C62C0: addiu       $t0, $t0, -0x7F38
    ctx->r8 = ADD32(ctx->r8, -0X7F38);
    // 0x802C62C4: lw          $t8, 0x0($t0)
    ctx->r24 = MEM_W(ctx->r8, 0X0);
    // 0x802C62C8: lw          $t3, 0x0($v1)
    ctx->r11 = MEM_W(ctx->r3, 0X0);
    // 0x802C62CC: addiu       $t7, $zero, 0x1
    ctx->r15 = ADD32(0, 0X1);
    // 0x802C62D0: addiu       $t9, $t8, 0x1
    ctx->r25 = ADD32(ctx->r24, 0X1);
    // 0x802C62D4: sw          $t7, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r15;
    // 0x802C62D8: bne         $t3, $zero, L_802C62E8
    if (ctx->r11 != 0) {
        // 0x802C62DC: sw          $t9, 0x0($t0)
        MEM_W(0X0, ctx->r8) = ctx->r25;
            goto L_802C62E8;
    }
    // 0x802C62DC: sw          $t9, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r25;
    // 0x802C62E0: b           L_802C62EC
    // 0x802C62E4: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
        goto L_802C62EC;
    // 0x802C62E4: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
L_802C62E8:
    // 0x802C62E8: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_802C62EC:
    // 0x802C62EC: lw          $t4, 0x0($t0)
    ctx->r12 = MEM_W(ctx->r8, 0X0);
    // 0x802C62F0: slti        $at, $t4, 0x9
    ctx->r1 = SIGNED(ctx->r12) < 0X9 ? 1 : 0;
    // 0x802C62F4: bnel        $at, $zero, L_802C63B0
    if (ctx->r1 != 0) {
        // 0x802C62F8: lw          $t5, 0x24($sp)
        ctx->r13 = MEM_W(ctx->r29, 0X24);
            goto L_802C63B0;
    }
    goto skip_4;
    // 0x802C62F8: lw          $t5, 0x24($sp)
    ctx->r13 = MEM_W(ctx->r29, 0X24);
    skip_4:
    // 0x802C62FC: b           L_802C63AC
    // 0x802C6300: sw          $v0, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r2;
        goto L_802C63AC;
    // 0x802C6300: sw          $v0, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r2;
L_802C6304:
    // 0x802C6304: lw          $t5, 0x0($t0)
    ctx->r13 = MEM_W(ctx->r8, 0X0);
    // 0x802C6308: lui         $a3, 0x800E
    ctx->r7 = S32(0X800E << 16);
    // 0x802C630C: addiu       $t9, $zero, 0x3
    ctx->r25 = ADD32(0, 0X3);
    // 0x802C6310: addiu       $v0, $t5, 0x1
    ctx->r2 = ADD32(ctx->r13, 0X1);
    // 0x802C6314: slti        $at, $v0, 0x9
    ctx->r1 = SIGNED(ctx->r2) < 0X9 ? 1 : 0;
    // 0x802C6318: bne         $at, $zero, L_802C6344
    if (ctx->r1 != 0) {
        // 0x802C631C: sw          $v0, 0x0($t0)
        MEM_W(0X0, ctx->r8) = ctx->r2;
            goto L_802C6344;
    }
    // 0x802C631C: sw          $v0, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r2;
    // 0x802C6320: lw          $t7, 0xC($t2)
    ctx->r15 = MEM_W(ctx->r10, 0XC);
    // 0x802C6324: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x802C6328: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
    // 0x802C632C: bnel        $t7, $at, L_802C6344
    if (ctx->r15 != ctx->r1) {
        // 0x802C6330: sw          $v0, 0x0($t0)
        MEM_W(0X0, ctx->r8) = ctx->r2;
            goto L_802C6344;
    }
    goto skip_5;
    // 0x802C6330: sw          $v0, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r2;
    skip_5:
    // 0x802C6334: sw          $zero, 0x0($t0)
    MEM_W(0X0, ctx->r8) = 0;
    // 0x802C6338: b           L_802C6344
    // 0x802C633C: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
        goto L_802C6344;
    // 0x802C633C: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    // 0x802C6340: sw          $v0, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r2;
L_802C6344:
    // 0x802C6344: sll         $t8, $v0, 2
    ctx->r24 = S32(ctx->r2 << 2);
    // 0x802C6348: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C634C: addu        $a3, $a3, $t8
    ctx->r7 = ADD32(ctx->r7, ctx->r24);
    // 0x802C6350: sw          $t9, -0x7F24($at)
    MEM_W(-0X7F24, ctx->r1) = ctx->r25;
    // 0x802C6354: lw          $a3, -0x5528($a3)
    ctx->r7 = MEM_W(ctx->r7, -0X5528);
    // 0x802C6358: lw          $t3, 0xC($t2)
    ctx->r11 = MEM_W(ctx->r10, 0XC);
    // 0x802C635C: lui         $a0, 0x802D
    ctx->r4 = S32(0X802D << 16);
    // 0x802C6360: addiu       $a0, $a0, -0x7F0C
    ctx->r4 = ADD32(ctx->r4, -0X7F0C);
    // 0x802C6364: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C6368: addiu       $a2, $zero, 0xF0
    ctx->r6 = ADD32(0, 0XF0);
    // 0x802C636C: sw          $a3, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r7;
    // 0x802C6370: jal         0x802C7194
    // 0x802C6374: sw          $t3, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r11;
    func_i9_802C7194(rdram, ctx);
        goto after_16;
    // 0x802C6374: sw          $t3, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r11;
    after_16:
    // 0x802C6378: addiu       $t4, $zero, 0x3
    ctx->r12 = ADD32(0, 0X3);
    // 0x802C637C: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C6380: lui         $a0, 0x802D
    ctx->r4 = S32(0X802D << 16);
    // 0x802C6384: lw          $a3, 0x20($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X20);
    // 0x802C6388: sw          $t4, -0x7F20($at)
    MEM_W(-0X7F20, ctx->r1) = ctx->r12;
    // 0x802C638C: addiu       $a0, $a0, -0x7EEC
    ctx->r4 = ADD32(ctx->r4, -0X7EEC);
    // 0x802C6390: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C6394: addiu       $a2, $zero, 0xF0
    ctx->r6 = ADD32(0, 0XF0);
    // 0x802C6398: jal         0x802C7194
    // 0x802C639C: sw          $zero, 0x10($sp)
    MEM_W(0X10, ctx->r29) = 0;
    func_i9_802C7194(rdram, ctx);
        goto after_17;
    // 0x802C639C: sw          $zero, 0x10($sp)
    MEM_W(0X10, ctx->r29) = 0;
    after_17:
    // 0x802C63A0: addiu       $a0, $zero, 0x2A
    ctx->r4 = ADD32(0, 0X2A);
    // 0x802C63A4: jal         0x800C37F4
    // 0x802C63A8: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_18;
    // 0x802C63A8: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_18:
L_802C63AC:
    // 0x802C63AC: lw          $t5, 0x24($sp)
    ctx->r13 = MEM_W(ctx->r29, 0X24);
L_802C63B0:
    // 0x802C63B0: addiu       $a0, $zero, 0x10
    ctx->r4 = ADD32(0, 0X10);
    // 0x802C63B4: beql        $t5, $zero, L_802C6744
    if (ctx->r13 == 0) {
        // 0x802C63B8: lw          $ra, 0x1C($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X1C);
            goto L_802C6744;
    }
    goto skip_6;
    // 0x802C63B8: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    skip_6:
    // 0x802C63BC: jal         0x800C37F4
    // 0x802C63C0: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_19;
    // 0x802C63C0: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_19:
    // 0x802C63C4: b           L_802C6744
    // 0x802C63C8: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
        goto L_802C6744;
    // 0x802C63C8: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
L_802C63CC:
    // 0x802C63CC: beq         $t6, $zero, L_802C658C
    if (ctx->r14 == 0) {
        // 0x802C63D0: andi        $t3, $v0, 0x100
        ctx->r11 = ctx->r2 & 0X100;
            goto L_802C658C;
    }
    // 0x802C63D0: andi        $t3, $v0, 0x100
    ctx->r11 = ctx->r2 & 0X100;
    // 0x802C63D4: lw          $t7, 0x0($v1)
    ctx->r15 = MEM_W(ctx->r3, 0X0);
    // 0x802C63D8: lui         $t2, 0x802D
    ctx->r10 = S32(0X802D << 16);
    // 0x802C63DC: addiu       $t2, $t2, -0x7F1C
    ctx->r10 = ADD32(ctx->r10, -0X7F1C);
    // 0x802C63E0: bne         $t7, $zero, L_802C658C
    if (ctx->r15 != 0) {
        // 0x802C63E4: nop
    
            goto L_802C658C;
    }
    // 0x802C63E4: nop

    // 0x802C63E8: lw          $v0, 0x8($t2)
    ctx->r2 = MEM_W(ctx->r10, 0X8);
    // 0x802C63EC: addiu       $at, $zero, 0xA
    ctx->r1 = ADD32(0, 0XA);
    // 0x802C63F0: beql        $v0, $zero, L_802C6570
    if (ctx->r2 == 0) {
        // 0x802C63F4: lw          $t9, 0x24($sp)
        ctx->r25 = MEM_W(ctx->r29, 0X24);
            goto L_802C6570;
    }
    goto skip_7;
    // 0x802C63F4: lw          $t9, 0x24($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X24);
    skip_7:
    // 0x802C63F8: bne         $v0, $at, L_802C649C
    if (ctx->r2 != ctx->r1) {
        // 0x802C63FC: lui         $a0, 0x802D
        ctx->r4 = S32(0X802D << 16);
            goto L_802C649C;
    }
    // 0x802C63FC: lui         $a0, 0x802D
    ctx->r4 = S32(0X802D << 16);
    // 0x802C6400: addiu       $a0, $a0, -0x7F40
    ctx->r4 = ADD32(ctx->r4, -0X7F40);
    // 0x802C6404: lw          $v0, 0x0($a0)
    ctx->r2 = MEM_W(ctx->r4, 0X0);
    // 0x802C6408: addiu       $t8, $zero, 0x1
    ctx->r24 = ADD32(0, 0X1);
    // 0x802C640C: sw          $t8, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r24;
    // 0x802C6410: beq         $v0, $zero, L_802C642C
    if (ctx->r2 == 0) {
        // 0x802C6414: lui         $v1, 0x802D
        ctx->r3 = S32(0X802D << 16);
            goto L_802C642C;
    }
    // 0x802C6414: lui         $v1, 0x802D
    ctx->r3 = S32(0X802D << 16);
    // 0x802C6418: addiu       $t1, $zero, 0x1
    ctx->r9 = ADD32(0, 0X1);
    // 0x802C641C: beq         $v0, $t1, L_802C644C
    if (ctx->r2 == ctx->r9) {
        // 0x802C6420: lui         $v1, 0x802D
        ctx->r3 = S32(0X802D << 16);
            goto L_802C644C;
    }
    // 0x802C6420: lui         $v1, 0x802D
    ctx->r3 = S32(0X802D << 16);
    // 0x802C6424: b           L_802C6570
    // 0x802C6428: lw          $t9, 0x24($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X24);
        goto L_802C6570;
    // 0x802C6428: lw          $t9, 0x24($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X24);
L_802C642C:
    // 0x802C642C: addiu       $v1, $v1, -0x7F3C
    ctx->r3 = ADD32(ctx->r3, -0X7F3C);
    // 0x802C6430: lw          $t9, 0x0($v1)
    ctx->r25 = MEM_W(ctx->r3, 0X0);
    // 0x802C6434: addiu       $t5, $zero, 0x2
    ctx->r13 = ADD32(0, 0X2);
    // 0x802C6438: addiu       $t3, $t9, -0x1
    ctx->r11 = ADD32(ctx->r25, -0X1);
    // 0x802C643C: bgez        $t3, L_802C656C
    if (SIGNED(ctx->r11) >= 0) {
        // 0x802C6440: sw          $t3, 0x0($v1)
        MEM_W(0X0, ctx->r3) = ctx->r11;
            goto L_802C656C;
    }
    // 0x802C6440: sw          $t3, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r11;
    // 0x802C6444: b           L_802C656C
    // 0x802C6448: sw          $t5, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r13;
        goto L_802C656C;
    // 0x802C6448: sw          $t5, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r13;
L_802C644C:
    // 0x802C644C: addiu       $v1, $v1, -0x7F3C
    ctx->r3 = ADD32(ctx->r3, -0X7F3C);
    // 0x802C6450: lw          $t6, 0x0($v1)
    ctx->r14 = MEM_W(ctx->r3, 0X0);
    // 0x802C6454: lui         $t0, 0x802D
    ctx->r8 = S32(0X802D << 16);
    // 0x802C6458: addiu       $t0, $t0, -0x7F38
    ctx->r8 = ADD32(ctx->r8, -0X7F38);
    // 0x802C645C: bne         $t6, $zero, L_802C6470
    if (ctx->r14 != 0) {
        // 0x802C6460: nop
    
            goto L_802C6470;
    }
    // 0x802C6460: nop

    // 0x802C6464: lw          $t7, 0x0($t0)
    ctx->r15 = MEM_W(ctx->r8, 0X0);
    // 0x802C6468: addiu       $at, $zero, 0x5
    ctx->r1 = ADD32(0, 0X5);
    // 0x802C646C: beq         $t7, $at, L_802C656C
    if (ctx->r15 == ctx->r1) {
        // 0x802C6470: lui         $t0, 0x802D
        ctx->r8 = S32(0X802D << 16);
            goto L_802C656C;
    }
L_802C6470:
    // 0x802C6470: lui         $t0, 0x802D
    ctx->r8 = S32(0X802D << 16);
    // 0x802C6474: addiu       $t0, $t0, -0x7F38
    ctx->r8 = ADD32(ctx->r8, -0X7F38);
    // 0x802C6478: lw          $v0, 0x0($t0)
    ctx->r2 = MEM_W(ctx->r8, 0X0);
    // 0x802C647C: addiu       $at, $zero, 0x4
    ctx->r1 = ADD32(0, 0X4);
    // 0x802C6480: beq         $v0, $at, L_802C656C
    if (ctx->r2 == ctx->r1) {
        // 0x802C6484: addiu       $t8, $v0, -0x5
        ctx->r24 = ADD32(ctx->r2, -0X5);
            goto L_802C656C;
    }
    // 0x802C6484: addiu       $t8, $v0, -0x5
    ctx->r24 = ADD32(ctx->r2, -0X5);
    // 0x802C6488: bgez        $t8, L_802C656C
    if (SIGNED(ctx->r24) >= 0) {
        // 0x802C648C: sw          $t8, 0x0($t0)
        MEM_W(0X0, ctx->r8) = ctx->r24;
            goto L_802C656C;
    }
    // 0x802C648C: sw          $t8, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r24;
    // 0x802C6490: addiu       $t9, $t8, 0xA
    ctx->r25 = ADD32(ctx->r24, 0XA);
    // 0x802C6494: b           L_802C656C
    // 0x802C6498: sw          $t9, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r25;
        goto L_802C656C;
    // 0x802C6498: sw          $t9, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r25;
L_802C649C:
    // 0x802C649C: lw          $v1, 0xC($t2)
    ctx->r3 = MEM_W(ctx->r10, 0XC);
    // 0x802C64A0: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x802C64A4: lui         $t0, 0x802D
    ctx->r8 = S32(0X802D << 16);
    // 0x802C64A8: bne         $v1, $at, L_802C6510
    if (ctx->r3 != ctx->r1) {
        // 0x802C64AC: addiu       $t1, $zero, 0x1
        ctx->r9 = ADD32(0, 0X1);
            goto L_802C6510;
    }
    // 0x802C64AC: addiu       $t1, $zero, 0x1
    ctx->r9 = ADD32(0, 0X1);
    // 0x802C64B0: addiu       $t1, $zero, 0x1
    ctx->r9 = ADD32(0, 0X1);
    // 0x802C64B4: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C64B8: bne         $t1, $v1, L_802C64C8
    if (ctx->r9 != ctx->r3) {
        // 0x802C64BC: sw          $t1, -0x7F24($at)
        MEM_W(-0X7F24, ctx->r1) = ctx->r9;
            goto L_802C64C8;
    }
    // 0x802C64BC: sw          $t1, -0x7F24($at)
    MEM_W(-0X7F24, ctx->r1) = ctx->r9;
    // 0x802C64C0: b           L_802C64CC
    // 0x802C64C4: addiu       $v0, $zero, 0x2
    ctx->r2 = ADD32(0, 0X2);
        goto L_802C64CC;
    // 0x802C64C4: addiu       $v0, $zero, 0x2
    ctx->r2 = ADD32(0, 0X2);
L_802C64C8:
    // 0x802C64C8: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
L_802C64CC:
    // 0x802C64CC: addiu       $t0, $t0, -0x7F38
    ctx->r8 = ADD32(ctx->r8, -0X7F38);
    // 0x802C64D0: lw          $t3, 0x0($t0)
    ctx->r11 = MEM_W(ctx->r8, 0X0);
    // 0x802C64D4: lui         $a3, 0x800E
    ctx->r7 = S32(0X800E << 16);
    // 0x802C64D8: lui         $a0, 0x802D
    ctx->r4 = S32(0X802D << 16);
    // 0x802C64DC: sll         $t4, $t3, 2
    ctx->r12 = S32(ctx->r11 << 2);
    // 0x802C64E0: addu        $a3, $a3, $t4
    ctx->r7 = ADD32(ctx->r7, ctx->r12);
    // 0x802C64E4: lw          $a3, -0x5528($a3)
    ctx->r7 = MEM_W(ctx->r7, -0X5528);
    // 0x802C64E8: addiu       $a0, $a0, -0x7F0C
    ctx->r4 = ADD32(ctx->r4, -0X7F0C);
    // 0x802C64EC: addiu       $a1, $zero, -0x1A8
    ctx->r5 = ADD32(0, -0X1A8);
    // 0x802C64F0: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x802C64F4: jal         0x802C7194
    // 0x802C64F8: sw          $v0, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r2;
    func_i9_802C7194(rdram, ctx);
        goto after_20;
    // 0x802C64F8: sw          $v0, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r2;
    after_20:
    // 0x802C64FC: addiu       $a0, $zero, 0x2A
    ctx->r4 = ADD32(0, 0X2A);
    // 0x802C6500: jal         0x800C37F4
    // 0x802C6504: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_21;
    // 0x802C6504: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_21:
    // 0x802C6508: b           L_802C6570
    // 0x802C650C: lw          $t9, 0x24($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X24);
        goto L_802C6570;
    // 0x802C650C: lw          $t9, 0x24($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X24);
L_802C6510:
    // 0x802C6510: bne         $t1, $v1, L_802C656C
    if (ctx->r9 != ctx->r3) {
        // 0x802C6514: lui         $t5, 0x802D
        ctx->r13 = S32(0X802D << 16);
            goto L_802C656C;
    }
    // 0x802C6514: lui         $t5, 0x802D
    ctx->r13 = S32(0X802D << 16);
    // 0x802C6518: lw          $t5, -0x7E4C($t5)
    ctx->r13 = MEM_W(ctx->r13, -0X7E4C);
    // 0x802C651C: lui         $t0, 0x802D
    ctx->r8 = S32(0X802D << 16);
    // 0x802C6520: addiu       $t0, $t0, -0x7F38
    ctx->r8 = ADD32(ctx->r8, -0X7F38);
    // 0x802C6524: beq         $t5, $zero, L_802C656C
    if (ctx->r13 == 0) {
        // 0x802C6528: lui         $at, 0x802D
        ctx->r1 = S32(0X802D << 16);
            goto L_802C656C;
    }
    // 0x802C6528: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C652C: sw          $t1, -0x7F24($at)
    MEM_W(-0X7F24, ctx->r1) = ctx->r9;
    // 0x802C6530: lw          $t6, 0x0($t0)
    ctx->r14 = MEM_W(ctx->r8, 0X0);
    // 0x802C6534: lui         $a3, 0x800E
    ctx->r7 = S32(0X800E << 16);
    // 0x802C6538: lui         $a0, 0x802D
    ctx->r4 = S32(0X802D << 16);
    // 0x802C653C: sll         $t7, $t6, 2
    ctx->r15 = S32(ctx->r14 << 2);
    // 0x802C6540: addu        $a3, $a3, $t7
    ctx->r7 = ADD32(ctx->r7, ctx->r15);
    // 0x802C6544: addiu       $t8, $zero, 0x3
    ctx->r24 = ADD32(0, 0X3);
    // 0x802C6548: sw          $t8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r24;
    // 0x802C654C: lw          $a3, -0x5528($a3)
    ctx->r7 = MEM_W(ctx->r7, -0X5528);
    // 0x802C6550: addiu       $a0, $a0, -0x7F0C
    ctx->r4 = ADD32(ctx->r4, -0X7F0C);
    // 0x802C6554: addiu       $a1, $zero, -0x140
    ctx->r5 = ADD32(0, -0X140);
    // 0x802C6558: jal         0x802C7194
    // 0x802C655C: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    func_i9_802C7194(rdram, ctx);
        goto after_22;
    // 0x802C655C: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    after_22:
    // 0x802C6560: addiu       $a0, $zero, 0x2A
    ctx->r4 = ADD32(0, 0X2A);
    // 0x802C6564: jal         0x800C37F4
    // 0x802C6568: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_23;
    // 0x802C6568: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_23:
L_802C656C:
    // 0x802C656C: lw          $t9, 0x24($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X24);
L_802C6570:
    // 0x802C6570: addiu       $a0, $zero, 0x10
    ctx->r4 = ADD32(0, 0X10);
    // 0x802C6574: beql        $t9, $zero, L_802C6744
    if (ctx->r25 == 0) {
        // 0x802C6578: lw          $ra, 0x1C($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X1C);
            goto L_802C6744;
    }
    goto skip_8;
    // 0x802C6578: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    skip_8:
    // 0x802C657C: jal         0x800C37F4
    // 0x802C6580: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_24;
    // 0x802C6580: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_24:
    // 0x802C6584: b           L_802C6744
    // 0x802C6588: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
        goto L_802C6744;
    // 0x802C6588: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
L_802C658C:
    // 0x802C658C: beql        $t3, $zero, L_802C6744
    if (ctx->r11 == 0) {
        // 0x802C6590: lw          $ra, 0x1C($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X1C);
            goto L_802C6744;
    }
    goto skip_9;
    // 0x802C6590: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    skip_9:
    // 0x802C6594: lw          $t4, 0x0($v1)
    ctx->r12 = MEM_W(ctx->r3, 0X0);
    // 0x802C6598: lui         $t2, 0x802D
    ctx->r10 = S32(0X802D << 16);
    // 0x802C659C: addiu       $t2, $t2, -0x7F1C
    ctx->r10 = ADD32(ctx->r10, -0X7F1C);
    // 0x802C65A0: bnel        $t4, $zero, L_802C6744
    if (ctx->r12 != 0) {
        // 0x802C65A4: lw          $ra, 0x1C($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X1C);
            goto L_802C6744;
    }
    goto skip_10;
    // 0x802C65A4: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    skip_10:
    // 0x802C65A8: lw          $v0, 0x8($t2)
    ctx->r2 = MEM_W(ctx->r10, 0X8);
    // 0x802C65AC: addiu       $at, $zero, 0xA
    ctx->r1 = ADD32(0, 0XA);
    // 0x802C65B0: beql        $v0, $zero, L_802C672C
    if (ctx->r2 == 0) {
        // 0x802C65B4: lw          $t6, 0x24($sp)
        ctx->r14 = MEM_W(ctx->r29, 0X24);
            goto L_802C672C;
    }
    goto skip_11;
    // 0x802C65B4: lw          $t6, 0x24($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X24);
    skip_11:
    // 0x802C65B8: bne         $v0, $at, L_802C6660
    if (ctx->r2 != ctx->r1) {
        // 0x802C65BC: lui         $a0, 0x802D
        ctx->r4 = S32(0X802D << 16);
            goto L_802C6660;
    }
    // 0x802C65BC: lui         $a0, 0x802D
    ctx->r4 = S32(0X802D << 16);
    // 0x802C65C0: addiu       $a0, $a0, -0x7F40
    ctx->r4 = ADD32(ctx->r4, -0X7F40);
    // 0x802C65C4: lw          $v0, 0x0($a0)
    ctx->r2 = MEM_W(ctx->r4, 0X0);
    // 0x802C65C8: addiu       $t5, $zero, 0x1
    ctx->r13 = ADD32(0, 0X1);
    // 0x802C65CC: sw          $t5, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r13;
    // 0x802C65D0: beq         $v0, $zero, L_802C65EC
    if (ctx->r2 == 0) {
        // 0x802C65D4: lui         $v1, 0x802D
        ctx->r3 = S32(0X802D << 16);
            goto L_802C65EC;
    }
    // 0x802C65D4: lui         $v1, 0x802D
    ctx->r3 = S32(0X802D << 16);
    // 0x802C65D8: addiu       $t1, $zero, 0x1
    ctx->r9 = ADD32(0, 0X1);
    // 0x802C65DC: beq         $v0, $t1, L_802C660C
    if (ctx->r2 == ctx->r9) {
        // 0x802C65E0: lui         $v1, 0x802D
        ctx->r3 = S32(0X802D << 16);
            goto L_802C660C;
    }
    // 0x802C65E0: lui         $v1, 0x802D
    ctx->r3 = S32(0X802D << 16);
    // 0x802C65E4: b           L_802C672C
    // 0x802C65E8: lw          $t6, 0x24($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X24);
        goto L_802C672C;
    // 0x802C65E8: lw          $t6, 0x24($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X24);
L_802C65EC:
    // 0x802C65EC: addiu       $v1, $v1, -0x7F3C
    ctx->r3 = ADD32(ctx->r3, -0X7F3C);
    // 0x802C65F0: lw          $t6, 0x0($v1)
    ctx->r14 = MEM_W(ctx->r3, 0X0);
    // 0x802C65F4: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x802C65F8: addiu       $t7, $t6, 0x1
    ctx->r15 = ADD32(ctx->r14, 0X1);
    // 0x802C65FC: bne         $t7, $at, L_802C6728
    if (ctx->r15 != ctx->r1) {
        // 0x802C6600: sw          $t7, 0x0($v1)
        MEM_W(0X0, ctx->r3) = ctx->r15;
            goto L_802C6728;
    }
    // 0x802C6600: sw          $t7, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r15;
    // 0x802C6604: b           L_802C6728
    // 0x802C6608: sw          $zero, 0x0($v1)
    MEM_W(0X0, ctx->r3) = 0;
        goto L_802C6728;
    // 0x802C6608: sw          $zero, 0x0($v1)
    MEM_W(0X0, ctx->r3) = 0;
L_802C660C:
    // 0x802C660C: addiu       $v1, $v1, -0x7F3C
    ctx->r3 = ADD32(ctx->r3, -0X7F3C);
    // 0x802C6610: lw          $t9, 0x0($v1)
    ctx->r25 = MEM_W(ctx->r3, 0X0);
    // 0x802C6614: lui         $t0, 0x802D
    ctx->r8 = S32(0X802D << 16);
    // 0x802C6618: addiu       $t0, $t0, -0x7F38
    ctx->r8 = ADD32(ctx->r8, -0X7F38);
    // 0x802C661C: bne         $t9, $zero, L_802C6630
    if (ctx->r25 != 0) {
        // 0x802C6620: nop
    
            goto L_802C6630;
    }
    // 0x802C6620: nop

    // 0x802C6624: lw          $t3, 0x0($t0)
    ctx->r11 = MEM_W(ctx->r8, 0X0);
    // 0x802C6628: addiu       $at, $zero, 0x5
    ctx->r1 = ADD32(0, 0X5);
    // 0x802C662C: beq         $t3, $at, L_802C6728
    if (ctx->r11 == ctx->r1) {
        // 0x802C6630: lui         $t0, 0x802D
        ctx->r8 = S32(0X802D << 16);
            goto L_802C6728;
    }
L_802C6630:
    // 0x802C6630: lui         $t0, 0x802D
    ctx->r8 = S32(0X802D << 16);
    // 0x802C6634: addiu       $t0, $t0, -0x7F38
    ctx->r8 = ADD32(ctx->r8, -0X7F38);
    // 0x802C6638: lw          $v0, 0x0($t0)
    ctx->r2 = MEM_W(ctx->r8, 0X0);
    // 0x802C663C: addiu       $at, $zero, 0x4
    ctx->r1 = ADD32(0, 0X4);
    // 0x802C6640: beq         $v0, $at, L_802C6728
    if (ctx->r2 == ctx->r1) {
        // 0x802C6644: addiu       $t4, $v0, 0x5
        ctx->r12 = ADD32(ctx->r2, 0X5);
            goto L_802C6728;
    }
    // 0x802C6644: addiu       $t4, $v0, 0x5
    ctx->r12 = ADD32(ctx->r2, 0X5);
    // 0x802C6648: slti        $at, $t4, 0x9
    ctx->r1 = SIGNED(ctx->r12) < 0X9 ? 1 : 0;
    // 0x802C664C: bne         $at, $zero, L_802C6728
    if (ctx->r1 != 0) {
        // 0x802C6650: sw          $t4, 0x0($t0)
        MEM_W(0X0, ctx->r8) = ctx->r12;
            goto L_802C6728;
    }
    // 0x802C6650: sw          $t4, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r12;
    // 0x802C6654: addiu       $t5, $t4, -0xA
    ctx->r13 = ADD32(ctx->r12, -0XA);
    // 0x802C6658: b           L_802C6728
    // 0x802C665C: sw          $t5, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r13;
        goto L_802C6728;
    // 0x802C665C: sw          $t5, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r13;
L_802C6660:
    // 0x802C6660: lw          $v1, 0xC($t2)
    ctx->r3 = MEM_W(ctx->r10, 0XC);
    // 0x802C6664: addiu       $t1, $zero, 0x1
    ctx->r9 = ADD32(0, 0X1);
    // 0x802C6668: addiu       $t6, $zero, 0x2
    ctx->r14 = ADD32(0, 0X2);
    // 0x802C666C: bne         $t1, $v1, L_802C66D4
    if (ctx->r9 != ctx->r3) {
        // 0x802C6670: addiu       $at, $zero, 0x3
        ctx->r1 = ADD32(0, 0X3);
            goto L_802C66D4;
    }
    // 0x802C6670: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x802C6674: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C6678: bne         $t1, $v1, L_802C6688
    if (ctx->r9 != ctx->r3) {
        // 0x802C667C: sw          $t6, -0x7F24($at)
        MEM_W(-0X7F24, ctx->r1) = ctx->r14;
            goto L_802C6688;
    }
    // 0x802C667C: sw          $t6, -0x7F24($at)
    MEM_W(-0X7F24, ctx->r1) = ctx->r14;
    // 0x802C6680: b           L_802C668C
    // 0x802C6684: addiu       $v0, $zero, 0x2
    ctx->r2 = ADD32(0, 0X2);
        goto L_802C668C;
    // 0x802C6684: addiu       $v0, $zero, 0x2
    ctx->r2 = ADD32(0, 0X2);
L_802C6688:
    // 0x802C6688: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
L_802C668C:
    // 0x802C668C: lui         $t0, 0x802D
    ctx->r8 = S32(0X802D << 16);
    // 0x802C6690: addiu       $t0, $t0, -0x7F38
    ctx->r8 = ADD32(ctx->r8, -0X7F38);
    // 0x802C6694: lw          $t7, 0x0($t0)
    ctx->r15 = MEM_W(ctx->r8, 0X0);
    // 0x802C6698: lui         $a3, 0x800E
    ctx->r7 = S32(0X800E << 16);
    // 0x802C669C: lui         $a0, 0x802D
    ctx->r4 = S32(0X802D << 16);
    // 0x802C66A0: sll         $t8, $t7, 2
    ctx->r24 = S32(ctx->r15 << 2);
    // 0x802C66A4: addu        $a3, $a3, $t8
    ctx->r7 = ADD32(ctx->r7, ctx->r24);
    // 0x802C66A8: lw          $a3, -0x5528($a3)
    ctx->r7 = MEM_W(ctx->r7, -0X5528);
    // 0x802C66AC: addiu       $a0, $a0, -0x7F0C
    ctx->r4 = ADD32(ctx->r4, -0X7F0C);
    // 0x802C66B0: addiu       $a1, $zero, 0x1A8
    ctx->r5 = ADD32(0, 0X1A8);
    // 0x802C66B4: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x802C66B8: jal         0x802C7194
    // 0x802C66BC: sw          $v0, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r2;
    func_i9_802C7194(rdram, ctx);
        goto after_25;
    // 0x802C66BC: sw          $v0, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r2;
    after_25:
    // 0x802C66C0: addiu       $a0, $zero, 0x2A
    ctx->r4 = ADD32(0, 0X2A);
    // 0x802C66C4: jal         0x800C37F4
    // 0x802C66C8: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_26;
    // 0x802C66C8: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_26:
    // 0x802C66CC: b           L_802C672C
    // 0x802C66D0: lw          $t6, 0x24($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X24);
        goto L_802C672C;
    // 0x802C66D0: lw          $t6, 0x24($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X24);
L_802C66D4:
    // 0x802C66D4: bne         $v1, $at, L_802C6728
    if (ctx->r3 != ctx->r1) {
        // 0x802C66D8: lui         $t0, 0x802D
        ctx->r8 = S32(0X802D << 16);
            goto L_802C6728;
    }
    // 0x802C66D8: lui         $t0, 0x802D
    ctx->r8 = S32(0X802D << 16);
    // 0x802C66DC: addiu       $t9, $zero, 0x2
    ctx->r25 = ADD32(0, 0X2);
    // 0x802C66E0: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C66E4: addiu       $t0, $t0, -0x7F38
    ctx->r8 = ADD32(ctx->r8, -0X7F38);
    // 0x802C66E8: sw          $t9, -0x7F24($at)
    MEM_W(-0X7F24, ctx->r1) = ctx->r25;
    // 0x802C66EC: lw          $t3, 0x0($t0)
    ctx->r11 = MEM_W(ctx->r8, 0X0);
    // 0x802C66F0: lui         $a3, 0x800E
    ctx->r7 = S32(0X800E << 16);
    // 0x802C66F4: lui         $a0, 0x802D
    ctx->r4 = S32(0X802D << 16);
    // 0x802C66F8: sll         $t4, $t3, 2
    ctx->r12 = S32(ctx->r11 << 2);
    // 0x802C66FC: addu        $a3, $a3, $t4
    ctx->r7 = ADD32(ctx->r7, ctx->r12);
    // 0x802C6700: addiu       $t5, $zero, 0x1
    ctx->r13 = ADD32(0, 0X1);
    // 0x802C6704: sw          $t5, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r13;
    // 0x802C6708: lw          $a3, -0x5528($a3)
    ctx->r7 = MEM_W(ctx->r7, -0X5528);
    // 0x802C670C: addiu       $a0, $a0, -0x7F0C
    ctx->r4 = ADD32(ctx->r4, -0X7F0C);
    // 0x802C6710: addiu       $a1, $zero, 0x140
    ctx->r5 = ADD32(0, 0X140);
    // 0x802C6714: jal         0x802C7194
    // 0x802C6718: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    func_i9_802C7194(rdram, ctx);
        goto after_27;
    // 0x802C6718: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    after_27:
    // 0x802C671C: addiu       $a0, $zero, 0x2A
    ctx->r4 = ADD32(0, 0X2A);
    // 0x802C6720: jal         0x800C37F4
    // 0x802C6724: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_28;
    // 0x802C6724: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_28:
L_802C6728:
    // 0x802C6728: lw          $t6, 0x24($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X24);
L_802C672C:
    // 0x802C672C: addiu       $a0, $zero, 0x10
    ctx->r4 = ADD32(0, 0X10);
    // 0x802C6730: beql        $t6, $zero, L_802C6744
    if (ctx->r14 == 0) {
        // 0x802C6734: lw          $ra, 0x1C($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X1C);
            goto L_802C6744;
    }
    goto skip_12;
    // 0x802C6734: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    skip_12:
    // 0x802C6738: jal         0x800C37F4
    // 0x802C673C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_29;
    // 0x802C673C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_29:
L_802C6740:
    // 0x802C6740: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
L_802C6744:
    // 0x802C6744: addiu       $sp, $sp, 0x28
    ctx->r29 = ADD32(ctx->r29, 0X28);
    // 0x802C6748: jr          $ra
    // 0x802C674C: nop

    return;
    // 0x802C674C: nop

;}
RECOMP_FUNC void func_i9_802C6750(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C6750: addiu       $sp, $sp, -0x70
    ctx->r29 = ADD32(ctx->r29, -0X70);
    // 0x802C6754: lui         $t6, 0x802D
    ctx->r14 = S32(0X802D << 16);
    // 0x802C6758: lw          $t6, -0x7F24($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X7F24);
    // 0x802C675C: sw          $s0, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r16;
    // 0x802C6760: or          $s0, $a0, $zero
    ctx->r16 = ctx->r4 | 0;
    // 0x802C6764: sw          $ra, 0x64($sp)
    MEM_W(0X64, ctx->r29) = ctx->r31;
    // 0x802C6768: sw          $fp, 0x60($sp)
    MEM_W(0X60, ctx->r29) = ctx->r30;
    // 0x802C676C: sw          $s7, 0x5C($sp)
    MEM_W(0X5C, ctx->r29) = ctx->r23;
    // 0x802C6770: sw          $s6, 0x58($sp)
    MEM_W(0X58, ctx->r29) = ctx->r22;
    // 0x802C6774: sw          $s5, 0x54($sp)
    MEM_W(0X54, ctx->r29) = ctx->r21;
    // 0x802C6778: sw          $s4, 0x50($sp)
    MEM_W(0X50, ctx->r29) = ctx->r20;
    // 0x802C677C: sw          $s3, 0x4C($sp)
    MEM_W(0X4C, ctx->r29) = ctx->r19;
    // 0x802C6780: sw          $s2, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r18;
    // 0x802C6784: bne         $t6, $zero, L_802C6798
    if (ctx->r14 != 0) {
        // 0x802C6788: sw          $s1, 0x44($sp)
        MEM_W(0X44, ctx->r29) = ctx->r17;
            goto L_802C6798;
    }
    // 0x802C6788: sw          $s1, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r17;
    // 0x802C678C: addiu       $t7, $zero, 0x1
    ctx->r15 = ADD32(0, 0X1);
    // 0x802C6790: b           L_802C67A0
    // 0x802C6794: sw          $t7, 0x68($sp)
    MEM_W(0X68, ctx->r29) = ctx->r15;
        goto L_802C67A0;
    // 0x802C6794: sw          $t7, 0x68($sp)
    MEM_W(0X68, ctx->r29) = ctx->r15;
L_802C6798:
    // 0x802C6798: addiu       $t8, $zero, 0x2
    ctx->r24 = ADD32(0, 0X2);
    // 0x802C679C: sw          $t8, 0x68($sp)
    MEM_W(0X68, ctx->r29) = ctx->r24;
L_802C67A0:
    // 0x802C67A0: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
    // 0x802C67A4: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C67A8: lui         $t9, 0x103
    ctx->r25 = S32(0X103 << 16);
    // 0x802C67AC: lui         $t3, 0x700
    ctx->r11 = S32(0X700 << 16);
    // 0x802C67B0: addiu       $t3, $t3, 0x0
    ctx->r11 = ADD32(ctx->r11, 0X0);
    // 0x802C67B4: ori         $t9, $t9, 0x40
    ctx->r25 = ctx->r25 | 0X40;
    // 0x802C67B8: or          $v1, $s0, $zero
    ctx->r3 = ctx->r16 | 0;
    // 0x802C67BC: sw          $t9, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r25;
    // 0x802C67C0: sw          $t3, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r11;
    // 0x802C67C4: lui         $t4, 0x102
    ctx->r12 = S32(0X102 << 16);
    // 0x802C67C8: lui         $t5, 0x200
    ctx->r13 = S32(0X200 << 16);
    // 0x802C67CC: addiu       $t5, $t5, 0xA40
    ctx->r13 = ADD32(ctx->r13, 0XA40);
    // 0x802C67D0: ori         $t4, $t4, 0x40
    ctx->r12 = ctx->r12 | 0X40;
    // 0x802C67D4: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C67D8: sw          $t4, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r12;
    // 0x802C67DC: sw          $t5, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r13;
    // 0x802C67E0: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x802C67E4: lui         $t7, 0x107
    ctx->r15 = S32(0X107 << 16);
    // 0x802C67E8: addiu       $t7, $t7, -0xAB0
    ctx->r15 = ADD32(ctx->r15, -0XAB0);
    // 0x802C67EC: lui         $t6, 0x600
    ctx->r14 = S32(0X600 << 16);
    // 0x802C67F0: sw          $t6, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r14;
    // 0x802C67F4: sw          $t7, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r15;
    // 0x802C67F8: lw          $t8, 0x68($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X68);
    // 0x802C67FC: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C6800: or          $s6, $zero, $zero
    ctx->r22 = 0 | 0;
    // 0x802C6804: blez        $t8, L_802C6C94
    if (SIGNED(ctx->r24) <= 0) {
        // 0x802C6808: lui         $s4, 0x802D
        ctx->r20 = S32(0X802D << 16);
            goto L_802C6C94;
    }
    // 0x802C6808: lui         $s4, 0x802D
    ctx->r20 = S32(0X802D << 16);
    // 0x802C680C: lui         $s5, 0x802D
    ctx->r21 = S32(0X802D << 16);
    // 0x802C6810: addiu       $s5, $s5, -0x7F1C
    ctx->r21 = ADD32(ctx->r21, -0X7F1C);
    // 0x802C6814: addiu       $s4, $s4, -0x7EFC
    ctx->r20 = ADD32(ctx->r20, -0X7EFC);
    // 0x802C6818: lui         $fp, 0xB300
    ctx->r30 = S32(0XB300 << 16);
    // 0x802C681C: lui         $s7, 0xE400
    ctx->r23 = S32(0XE400 << 16);
L_802C6820:
    // 0x802C6820: lw          $t6, 0x8($s4)
    ctx->r14 = MEM_W(ctx->r20, 0X8);
    // 0x802C6824: lui         $t3, 0x802D
    ctx->r11 = S32(0X802D << 16);
    // 0x802C6828: lui         $t5, 0x802D
    ctx->r13 = S32(0X802D << 16);
    // 0x802C682C: lw          $t3, -0x7F2C($t3)
    ctx->r11 = MEM_W(ctx->r11, -0X7F2C);
    // 0x802C6830: lw          $t9, 0x0($s4)
    ctx->r25 = MEM_W(ctx->r20, 0X0);
    // 0x802C6834: lw          $t5, -0x7F28($t5)
    ctx->r13 = MEM_W(ctx->r13, -0X7F28);
    // 0x802C6838: lw          $t4, 0x4($s4)
    ctx->r12 = MEM_W(ctx->r20, 0X4);
    // 0x802C683C: sltiu       $at, $t6, 0xB
    ctx->r1 = ctx->r14 < 0XB ? 1 : 0;
    // 0x802C6840: addu        $s2, $t9, $t3
    ctx->r18 = ADD32(ctx->r25, ctx->r11);
    // 0x802C6844: beq         $at, $zero, L_802C6C0C
    if (ctx->r1 == 0) {
        // 0x802C6848: addu        $s3, $t4, $t5
        ctx->r19 = ADD32(ctx->r12, ctx->r13);
            goto L_802C6C0C;
    }
    // 0x802C6848: addu        $s3, $t4, $t5
    ctx->r19 = ADD32(ctx->r12, ctx->r13);
    // 0x802C684C: sll         $t6, $t6, 2
    ctx->r14 = S32(ctx->r14 << 2);
    // 0x802C6850: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C6854: addu        $at, $at, $t6
    gpr jr_addend_802C685C = ctx->r14;
    ctx->r1 = ADD32(ctx->r1, ctx->r14);
    // 0x802C6858: lw          $t6, -0x7DE0($at)
    ctx->r14 = ADD32(ctx->r1, -0X7DE0);
    // 0x802C685C: jr          $t6
    // 0x802C6860: nop

    switch (jr_addend_802C685C >> 2) {
        case 0: goto L_802C6864; break;
        case 1: goto L_802C6864; break;
        case 2: goto L_802C6864; break;
        case 3: goto L_802C6864; break;
        case 4: goto L_802C6864; break;
        case 5: goto L_802C6864; break;
        case 6: goto L_802C6864; break;
        case 7: goto L_802C6864; break;
        case 8: goto L_802C6864; break;
        case 9: goto L_802C6C0C; break;
        case 10: goto L_802C6C0C; break;
        default: switch_error(__func__, 0x802C685C, 0x802C8220);
    }
    // 0x802C6860: nop

L_802C6864:
    // 0x802C6864: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
    // 0x802C6868: lui         $t8, 0x107
    ctx->r24 = S32(0X107 << 16);
    // 0x802C686C: addiu       $t8, $t8, -0x9D8
    ctx->r24 = ADD32(ctx->r24, -0X9D8);
    // 0x802C6870: lui         $t7, 0x600
    ctx->r15 = S32(0X600 << 16);
    // 0x802C6874: sw          $t7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r15;
    // 0x802C6878: sw          $t8, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r24;
    // 0x802C687C: addiu       $t9, $zero, 0x170
    ctx->r25 = ADD32(0, 0X170);
    // 0x802C6880: addiu       $t3, $zero, 0x18
    ctx->r11 = ADD32(0, 0X18);
    // 0x802C6884: lui         $s1, 0x806
    ctx->r17 = S32(0X806 << 16);
    // 0x802C6888: addiu       $a0, $s0, 0x8
    ctx->r4 = ADD32(ctx->r16, 0X8);
    // 0x802C688C: addiu       $s1, $s1, 0x8
    ctx->r17 = ADD32(ctx->r17, 0X8);
    // 0x802C6890: sw          $t3, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r11;
    // 0x802C6894: sw          $t9, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r25;
    // 0x802C6898: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C689C: addiu       $a2, $s2, 0x1C
    ctx->r6 = ADD32(ctx->r18, 0X1C);
    // 0x802C68A0: jal         0x80094338
    // 0x802C68A4: addiu       $a3, $s3, 0x1E
    ctx->r7 = ADD32(ctx->r19, 0X1E);
    func_80094338(rdram, ctx);
        goto after_0;
    // 0x802C68A4: addiu       $a3, $s3, 0x1E
    ctx->r7 = ADD32(ctx->r19, 0X1E);
    after_0:
    // 0x802C68A8: addiu       $t4, $zero, 0xFF
    ctx->r12 = ADD32(0, 0XFF);
    // 0x802C68AC: addiu       $t5, $zero, 0xFF
    ctx->r13 = ADD32(0, 0XFF);
    // 0x802C68B0: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C68B4: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C68B8: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C68BC: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C68C0: addiu       $t3, $zero, 0xFF
    ctx->r11 = ADD32(0, 0XFF);
    // 0x802C68C4: sw          $t3, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r11;
    // 0x802C68C8: sw          $t9, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r25;
    // 0x802C68CC: sw          $t8, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r24;
    // 0x802C68D0: sw          $t7, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r15;
    // 0x802C68D4: sw          $t6, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r14;
    // 0x802C68D8: sw          $t6, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r14;
    // 0x802C68DC: sw          $t5, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r13;
    // 0x802C68E0: sw          $t5, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r13;
    // 0x802C68E4: sw          $t4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r12;
    // 0x802C68E8: sw          $t4, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r12;
    // 0x802C68EC: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C68F0: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C68F4: addiu       $a2, $zero, 0xFF
    ctx->r6 = ADD32(0, 0XFF);
    // 0x802C68F8: jal         0x801E946C
    // 0x802C68FC: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    func_801E946C(rdram, ctx);
        goto after_1;
    // 0x802C68FC: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    after_1:
    // 0x802C6900: lw          $v1, 0x8($s4)
    ctx->r3 = MEM_W(ctx->r20, 0X8);
    // 0x802C6904: lui         $t8, 0x802D
    ctx->r24 = S32(0X802D << 16);
    // 0x802C6908: lui         $a2, 0x800E
    ctx->r6 = S32(0X800E << 16);
    // 0x802C690C: sll         $t7, $v1, 2
    ctx->r15 = S32(ctx->r3 << 2);
    // 0x802C6910: addu        $t8, $t8, $t7
    ctx->r24 = ADD32(ctx->r24, ctx->r15);
    // 0x802C6914: lw          $t8, -0x7E8C($t8)
    ctx->r24 = MEM_W(ctx->r24, -0X7E8C);
    // 0x802C6918: addu        $a2, $a2, $t7
    ctx->r6 = ADD32(ctx->r6, ctx->r15);
    // 0x802C691C: addiu       $t9, $s3, 0x21
    ctx->r25 = ADD32(ctx->r19, 0X21);
    // 0x802C6920: addu        $a3, $t8, $s2
    ctx->r7 = ADD32(ctx->r24, ctx->r18);
    // 0x802C6924: addiu       $a3, $a3, 0x80
    ctx->r7 = ADD32(ctx->r7, 0X80);
    // 0x802C6928: sw          $t9, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r25;
    // 0x802C692C: lw          $a2, -0x55CC($a2)
    ctx->r6 = MEM_W(ctx->r6, -0X55CC);
    // 0x802C6930: or          $v1, $t7, $zero
    ctx->r3 = ctx->r15 | 0;
    // 0x802C6934: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C6938: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C693C: jal         0x801E3EE0
    // 0x802C6940: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    func_801E3EE0(rdram, ctx);
        goto after_2;
    // 0x802C6940: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    after_2:
    // 0x802C6944: lui         $t3, 0xFD70
    ctx->r11 = S32(0XFD70 << 16);
    // 0x802C6948: lui         $t4, 0xF570
    ctx->r12 = S32(0XF570 << 16);
    // 0x802C694C: lui         $t5, 0x708
    ctx->r13 = S32(0X708 << 16);
    // 0x802C6950: lui         $t6, 0xE600
    ctx->r14 = S32(0XE600 << 16);
    // 0x802C6954: sw          $t6, 0x10($v0)
    MEM_W(0X10, ctx->r2) = ctx->r14;
    // 0x802C6958: ori         $t5, $t5, 0x200
    ctx->r13 = ctx->r13 | 0X200;
    // 0x802C695C: sw          $t4, 0x8($v0)
    MEM_W(0X8, ctx->r2) = ctx->r12;
    // 0x802C6960: sw          $t3, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r11;
    // 0x802C6964: lui         $t3, 0xF568
    ctx->r11 = S32(0XF568 << 16);
    // 0x802C6968: lui         $t4, 0x8
    ctx->r12 = S32(0X8 << 16);
    // 0x802C696C: sw          $t5, 0xC($v0)
    MEM_W(0XC, ctx->r2) = ctx->r13;
    // 0x802C6970: lui         $t6, 0x1
    ctx->r14 = S32(0X1 << 16);
    // 0x802C6974: lui         $t8, 0x701
    ctx->r24 = S32(0X701 << 16);
    // 0x802C6978: ori         $t8, $t8, 0xF800
    ctx->r24 = ctx->r24 | 0XF800;
    // 0x802C697C: ori         $t6, $t6, 0xC01C
    ctx->r14 = ctx->r14 | 0XC01C;
    // 0x802C6980: lui         $t5, 0xF200
    ctx->r13 = S32(0XF200 << 16);
    // 0x802C6984: ori         $t4, $t4, 0x200
    ctx->r12 = ctx->r12 | 0X200;
    // 0x802C6988: ori         $t3, $t3, 0x200
    ctx->r11 = ctx->r11 | 0X200;
    // 0x802C698C: lui         $t7, 0xF300
    ctx->r15 = S32(0XF300 << 16);
    // 0x802C6990: lui         $t9, 0xE700
    ctx->r25 = S32(0XE700 << 16);
    // 0x802C6994: sw          $t9, 0x20($v0)
    MEM_W(0X20, ctx->r2) = ctx->r25;
    // 0x802C6998: sw          $t7, 0x18($v0)
    MEM_W(0X18, ctx->r2) = ctx->r15;
    // 0x802C699C: sw          $t3, 0x28($v0)
    MEM_W(0X28, ctx->r2) = ctx->r11;
    // 0x802C69A0: sw          $t4, 0x2C($v0)
    MEM_W(0X2C, ctx->r2) = ctx->r12;
    // 0x802C69A4: sw          $t5, 0x30($v0)
    MEM_W(0X30, ctx->r2) = ctx->r13;
    // 0x802C69A8: sw          $t6, 0x34($v0)
    MEM_W(0X34, ctx->r2) = ctx->r14;
    // 0x802C69AC: sw          $t8, 0x1C($v0)
    MEM_W(0X1C, ctx->r2) = ctx->r24;
    // 0x802C69B0: sw          $s1, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r17;
    // 0x802C69B4: sw          $zero, 0x14($v0)
    MEM_W(0X14, ctx->r2) = 0;
    // 0x802C69B8: sw          $zero, 0x24($v0)
    MEM_W(0X24, ctx->r2) = 0;
    // 0x802C69BC: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C69C0: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C69C4: addiu       $t5, $zero, 0xFF
    ctx->r13 = ADD32(0, 0XFF);
    // 0x802C69C8: addiu       $t4, $zero, 0xFF
    ctx->r12 = ADD32(0, 0XFF);
    // 0x802C69CC: addiu       $t3, $zero, 0xFF
    ctx->r11 = ADD32(0, 0XFF);
    // 0x802C69D0: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C69D4: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C69D8: sw          $t9, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r25;
    // 0x802C69DC: sw          $t9, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r25;
    // 0x802C69E0: sw          $t7, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r15;
    // 0x802C69E4: sw          $t7, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r15;
    // 0x802C69E8: sw          $t3, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r11;
    // 0x802C69EC: sw          $t4, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r12;
    // 0x802C69F0: sw          $t5, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r13;
    // 0x802C69F4: sw          $t6, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r14;
    // 0x802C69F8: sw          $t8, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r24;
    // 0x802C69FC: sw          $t8, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r24;
    // 0x802C6A00: addiu       $a0, $v0, 0x38
    ctx->r4 = ADD32(ctx->r2, 0X38);
    // 0x802C6A04: addiu       $a1, $zero, 0x6
    ctx->r5 = ADD32(0, 0X6);
    // 0x802C6A08: addiu       $a2, $zero, 0xFF
    ctx->r6 = ADD32(0, 0XFF);
    // 0x802C6A0C: jal         0x801E946C
    // 0x802C6A10: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    func_801E946C(rdram, ctx);
        goto after_3;
    // 0x802C6A10: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    after_3:
    // 0x802C6A14: addiu       $t1, $s2, 0xD4
    ctx->r9 = ADD32(ctx->r18, 0XD4);
    // 0x802C6A18: sll         $t3, $t1, 2
    ctx->r11 = S32(ctx->r9 << 2);
    // 0x802C6A1C: blez        $t3, L_802C6A2C
    if (SIGNED(ctx->r11) <= 0) {
        // 0x802C6A20: or          $t1, $t3, $zero
        ctx->r9 = ctx->r11 | 0;
            goto L_802C6A2C;
    }
    // 0x802C6A20: or          $t1, $t3, $zero
    ctx->r9 = ctx->r11 | 0;
    // 0x802C6A24: b           L_802C6A30
    // 0x802C6A28: or          $a1, $t3, $zero
    ctx->r5 = ctx->r11 | 0;
        goto L_802C6A30;
    // 0x802C6A28: or          $a1, $t3, $zero
    ctx->r5 = ctx->r11 | 0;
L_802C6A2C:
    // 0x802C6A2C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
L_802C6A30:
    // 0x802C6A30: addiu       $v1, $s3, 0x1D
    ctx->r3 = ADD32(ctx->r19, 0X1D);
    // 0x802C6A34: sll         $t4, $v1, 2
    ctx->r12 = S32(ctx->r3 << 2);
    // 0x802C6A38: blez        $t4, L_802C6A48
    if (SIGNED(ctx->r12) <= 0) {
        // 0x802C6A3C: andi        $t7, $a1, 0xFFF
        ctx->r15 = ctx->r5 & 0XFFF;
            goto L_802C6A48;
    }
    // 0x802C6A3C: andi        $t7, $a1, 0xFFF
    ctx->r15 = ctx->r5 & 0XFFF;
    // 0x802C6A40: b           L_802C6A4C
    // 0x802C6A44: or          $a0, $t4, $zero
    ctx->r4 = ctx->r12 | 0;
        goto L_802C6A4C;
    // 0x802C6A44: or          $a0, $t4, $zero
    ctx->r4 = ctx->r12 | 0;
L_802C6A48:
    // 0x802C6A48: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
L_802C6A4C:
    // 0x802C6A4C: andi        $t5, $a0, 0xFFF
    ctx->r13 = ctx->r4 & 0XFFF;
    // 0x802C6A50: or          $t6, $t5, $s7
    ctx->r14 = ctx->r13 | ctx->r23;
    // 0x802C6A54: sll         $t8, $t7, 12
    ctx->r24 = S32(ctx->r15 << 12);
    // 0x802C6A58: addiu       $a2, $s2, 0xCC
    ctx->r6 = ADD32(ctx->r18, 0XCC);
    // 0x802C6A5C: sll         $t3, $a2, 2
    ctx->r11 = S32(ctx->r6 << 2);
    // 0x802C6A60: or          $t9, $t6, $t8
    ctx->r25 = ctx->r14 | ctx->r24;
    // 0x802C6A64: sw          $t9, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r25;
    // 0x802C6A68: blez        $t3, L_802C6A78
    if (SIGNED(ctx->r11) <= 0) {
        // 0x802C6A6C: or          $a2, $t3, $zero
        ctx->r6 = ctx->r11 | 0;
            goto L_802C6A78;
    }
    // 0x802C6A6C: or          $a2, $t3, $zero
    ctx->r6 = ctx->r11 | 0;
    // 0x802C6A70: b           L_802C6A7C
    // 0x802C6A74: or          $a1, $t3, $zero
    ctx->r5 = ctx->r11 | 0;
        goto L_802C6A7C;
    // 0x802C6A74: or          $a1, $t3, $zero
    ctx->r5 = ctx->r11 | 0;
L_802C6A78:
    // 0x802C6A78: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
L_802C6A7C:
    // 0x802C6A7C: addiu       $a3, $s3, 0x15
    ctx->r7 = ADD32(ctx->r19, 0X15);
    // 0x802C6A80: sll         $v1, $a3, 2
    ctx->r3 = S32(ctx->r7 << 2);
    // 0x802C6A84: blez        $v1, L_802C6A94
    if (SIGNED(ctx->r3) <= 0) {
        // 0x802C6A88: andi        $t5, $a1, 0xFFF
        ctx->r13 = ctx->r5 & 0XFFF;
            goto L_802C6A94;
    }
    // 0x802C6A88: andi        $t5, $a1, 0xFFF
    ctx->r13 = ctx->r5 & 0XFFF;
    // 0x802C6A8C: b           L_802C6A98
    // 0x802C6A90: or          $a0, $v1, $zero
    ctx->r4 = ctx->r3 | 0;
        goto L_802C6A98;
    // 0x802C6A90: or          $a0, $v1, $zero
    ctx->r4 = ctx->r3 | 0;
L_802C6A94:
    // 0x802C6A94: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
L_802C6A98:
    // 0x802C6A98: andi        $t4, $a0, 0xFFF
    ctx->r12 = ctx->r4 & 0XFFF;
    // 0x802C6A9C: sll         $t7, $t5, 12
    ctx->r15 = S32(ctx->r13 << 12);
    // 0x802C6AA0: or          $t6, $t4, $t7
    ctx->r14 = ctx->r12 | ctx->r15;
    // 0x802C6AA4: sll         $t2, $a2, 10
    ctx->r10 = S32(ctx->r6 << 10);
    // 0x802C6AA8: sra         $t8, $t2, 7
    ctx->r24 = S32(SIGNED(ctx->r10) >> 7);
    // 0x802C6AAC: sw          $t6, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r14;
    // 0x802C6AB0: addiu       $t0, $v0, 0x8
    ctx->r8 = ADD32(ctx->r2, 0X8);
    // 0x802C6AB4: addiu       $s0, $t0, 0x8
    ctx->r16 = ADD32(ctx->r8, 0X8);
    // 0x802C6AB8: sw          $fp, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r30;
    // 0x802C6ABC: bgez        $t8, L_802C6ACC
    if (SIGNED(ctx->r24) >= 0) {
        // 0x802C6AC0: or          $t2, $t8, $zero
        ctx->r10 = ctx->r24 | 0;
            goto L_802C6ACC;
    }
    // 0x802C6AC0: or          $t2, $t8, $zero
    ctx->r10 = ctx->r24 | 0;
    // 0x802C6AC4: b           L_802C6AD0
    // 0x802C6AC8: or          $a1, $t8, $zero
    ctx->r5 = ctx->r24 | 0;
        goto L_802C6AD0;
    // 0x802C6AC8: or          $a1, $t8, $zero
    ctx->r5 = ctx->r24 | 0;
L_802C6ACC:
    // 0x802C6ACC: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
L_802C6AD0:
    // 0x802C6AD0: sra         $v0, $a3, 7
    ctx->r2 = S32(SIGNED(ctx->r7) >> 7);
    // 0x802C6AD4: bgez        $v0, L_802C6AE4
    if (SIGNED(ctx->r2) >= 0) {
        // 0x802C6AD8: addiu       $t9, $zero, 0xE0
        ctx->r25 = ADD32(0, 0XE0);
            goto L_802C6AE4;
    }
    // 0x802C6AD8: addiu       $t9, $zero, 0xE0
    ctx->r25 = ADD32(0, 0XE0);
    // 0x802C6ADC: b           L_802C6AE8
    // 0x802C6AE0: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
        goto L_802C6AE8;
    // 0x802C6AE0: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
L_802C6AE4:
    // 0x802C6AE4: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
L_802C6AE8:
    // 0x802C6AE8: subu        $t3, $t9, $a0
    ctx->r11 = SUB32(ctx->r25, ctx->r4);
    // 0x802C6AEC: andi        $t5, $t3, 0xFFFF
    ctx->r13 = ctx->r11 & 0XFFFF;
    // 0x802C6AF0: negu        $t7, $a1
    ctx->r15 = SUB32(0, ctx->r5);
    // 0x802C6AF4: sll         $t6, $t7, 16
    ctx->r14 = S32(ctx->r15 << 16);
    // 0x802C6AF8: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
    // 0x802C6AFC: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C6B00: or          $t8, $t5, $t6
    ctx->r24 = ctx->r13 | ctx->r14;
    // 0x802C6B04: lui         $t3, 0x400
    ctx->r11 = S32(0X400 << 16);
    // 0x802C6B08: ori         $t3, $t3, 0xFC00
    ctx->r11 = ctx->r11 | 0XFC00;
    // 0x802C6B0C: sw          $t8, 0x4($t0)
    MEM_W(0X4, ctx->r8) = ctx->r24;
    // 0x802C6B10: lui         $t9, 0xB200
    ctx->r25 = S32(0XB200 << 16);
    // 0x802C6B14: or          $a3, $s0, $zero
    ctx->r7 = ctx->r16 | 0;
    // 0x802C6B18: sw          $t9, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r25;
    // 0x802C6B1C: sw          $t3, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r11;
    // 0x802C6B20: blez        $t1, L_802C6B30
    if (SIGNED(ctx->r9) <= 0) {
        // 0x802C6B24: addiu       $s0, $s0, 0x8
        ctx->r16 = ADD32(ctx->r16, 0X8);
            goto L_802C6B30;
    }
    // 0x802C6B24: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C6B28: b           L_802C6B34
    // 0x802C6B2C: or          $a1, $t1, $zero
    ctx->r5 = ctx->r9 | 0;
        goto L_802C6B34;
    // 0x802C6B2C: or          $a1, $t1, $zero
    ctx->r5 = ctx->r9 | 0;
L_802C6B30:
    // 0x802C6B30: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
L_802C6B34:
    // 0x802C6B34: addiu       $v0, $s3, 0xDB
    ctx->r2 = ADD32(ctx->r19, 0XDB);
    // 0x802C6B38: sll         $t4, $v0, 2
    ctx->r12 = S32(ctx->r2 << 2);
    // 0x802C6B3C: blez        $t4, L_802C6B4C
    if (SIGNED(ctx->r12) <= 0) {
        // 0x802C6B40: andi        $t6, $a1, 0xFFF
        ctx->r14 = ctx->r5 & 0XFFF;
            goto L_802C6B4C;
    }
    // 0x802C6B40: andi        $t6, $a1, 0xFFF
    ctx->r14 = ctx->r5 & 0XFFF;
    // 0x802C6B44: b           L_802C6B50
    // 0x802C6B48: or          $a0, $t4, $zero
    ctx->r4 = ctx->r12 | 0;
        goto L_802C6B50;
    // 0x802C6B48: or          $a0, $t4, $zero
    ctx->r4 = ctx->r12 | 0;
L_802C6B4C:
    // 0x802C6B4C: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
L_802C6B50:
    // 0x802C6B50: andi        $t7, $a0, 0xFFF
    ctx->r15 = ctx->r4 & 0XFFF;
    // 0x802C6B54: or          $t5, $t7, $s7
    ctx->r13 = ctx->r15 | ctx->r23;
    // 0x802C6B58: sll         $t8, $t6, 12
    ctx->r24 = S32(ctx->r14 << 12);
    // 0x802C6B5C: or          $t9, $t5, $t8
    ctx->r25 = ctx->r13 | ctx->r24;
    // 0x802C6B60: blez        $a2, L_802C6B70
    if (SIGNED(ctx->r6) <= 0) {
        // 0x802C6B64: sw          $t9, 0x0($a3)
        MEM_W(0X0, ctx->r7) = ctx->r25;
            goto L_802C6B70;
    }
    // 0x802C6B64: sw          $t9, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r25;
    // 0x802C6B68: b           L_802C6B74
    // 0x802C6B6C: or          $a1, $a2, $zero
    ctx->r5 = ctx->r6 | 0;
        goto L_802C6B74;
    // 0x802C6B6C: or          $a1, $a2, $zero
    ctx->r5 = ctx->r6 | 0;
L_802C6B70:
    // 0x802C6B70: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
L_802C6B74:
    // 0x802C6B74: addiu       $v1, $s3, 0xD3
    ctx->r3 = ADD32(ctx->r19, 0XD3);
    // 0x802C6B78: sll         $t3, $v1, 2
    ctx->r11 = S32(ctx->r3 << 2);
    // 0x802C6B7C: blez        $t3, L_802C6B8C
    if (SIGNED(ctx->r11) <= 0) {
        // 0x802C6B80: or          $v1, $t3, $zero
        ctx->r3 = ctx->r11 | 0;
            goto L_802C6B8C;
    }
    // 0x802C6B80: or          $v1, $t3, $zero
    ctx->r3 = ctx->r11 | 0;
    // 0x802C6B84: b           L_802C6B90
    // 0x802C6B88: or          $a0, $t3, $zero
    ctx->r4 = ctx->r11 | 0;
        goto L_802C6B90;
    // 0x802C6B88: or          $a0, $t3, $zero
    ctx->r4 = ctx->r11 | 0;
L_802C6B8C:
    // 0x802C6B8C: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
L_802C6B90:
    // 0x802C6B90: andi        $t7, $a1, 0xFFF
    ctx->r15 = ctx->r5 & 0XFFF;
    // 0x802C6B94: sll         $t6, $t7, 12
    ctx->r14 = S32(ctx->r15 << 12);
    // 0x802C6B98: andi        $t4, $a0, 0xFFF
    ctx->r12 = ctx->r4 & 0XFFF;
    // 0x802C6B9C: or          $t5, $t4, $t6
    ctx->r13 = ctx->r12 | ctx->r14;
    // 0x802C6BA0: sw          $t5, 0x4($a3)
    MEM_W(0X4, ctx->r7) = ctx->r13;
    // 0x802C6BA4: or          $a2, $s0, $zero
    ctx->r6 = ctx->r16 | 0;
    // 0x802C6BA8: sw          $fp, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r30;
    // 0x802C6BAC: bgez        $t2, L_802C6BBC
    if (SIGNED(ctx->r10) >= 0) {
        // 0x802C6BB0: addiu       $s0, $s0, 0x8
        ctx->r16 = ADD32(ctx->r16, 0X8);
            goto L_802C6BBC;
    }
    // 0x802C6BB0: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C6BB4: b           L_802C6BC0
    // 0x802C6BB8: or          $a1, $t2, $zero
    ctx->r5 = ctx->r10 | 0;
        goto L_802C6BC0;
    // 0x802C6BB8: or          $a1, $t2, $zero
    ctx->r5 = ctx->r10 | 0;
L_802C6BBC:
    // 0x802C6BBC: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
L_802C6BC0:
    // 0x802C6BC0: sll         $v0, $v1, 10
    ctx->r2 = S32(ctx->r3 << 10);
    // 0x802C6BC4: sra         $t8, $v0, 7
    ctx->r24 = S32(SIGNED(ctx->r2) >> 7);
    // 0x802C6BC8: bgez        $t8, L_802C6BD8
    if (SIGNED(ctx->r24) >= 0) {
        // 0x802C6BCC: negu        $t4, $a1
        ctx->r12 = SUB32(0, ctx->r5);
            goto L_802C6BD8;
    }
    // 0x802C6BCC: negu        $t4, $a1
    ctx->r12 = SUB32(0, ctx->r5);
    // 0x802C6BD0: b           L_802C6BDC
    // 0x802C6BD4: or          $a0, $t8, $zero
    ctx->r4 = ctx->r24 | 0;
        goto L_802C6BDC;
    // 0x802C6BD4: or          $a0, $t8, $zero
    ctx->r4 = ctx->r24 | 0;
L_802C6BD8:
    // 0x802C6BD8: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
L_802C6BDC:
    // 0x802C6BDC: negu        $t9, $a0
    ctx->r25 = SUB32(0, ctx->r4);
    // 0x802C6BE0: andi        $t3, $t9, 0xFFFF
    ctx->r11 = ctx->r25 & 0XFFFF;
    // 0x802C6BE4: sll         $t6, $t4, 16
    ctx->r14 = S32(ctx->r12 << 16);
    // 0x802C6BE8: or          $t5, $t3, $t6
    ctx->r13 = ctx->r11 | ctx->r14;
    // 0x802C6BEC: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
    // 0x802C6BF0: sw          $t5, 0x4($a2)
    MEM_W(0X4, ctx->r6) = ctx->r13;
    // 0x802C6BF4: lui         $t9, 0x400
    ctx->r25 = S32(0X400 << 16);
    // 0x802C6BF8: ori         $t9, $t9, 0x400
    ctx->r25 = ctx->r25 | 0X400;
    // 0x802C6BFC: lui         $t8, 0xB200
    ctx->r24 = S32(0XB200 << 16);
    // 0x802C6C00: sw          $t8, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r24;
    // 0x802C6C04: sw          $t9, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r25;
    // 0x802C6C08: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
L_802C6C0C:
    // 0x802C6C0C: lw          $a2, 0x8($s5)
    ctx->r6 = MEM_W(ctx->r21, 0X8);
    // 0x802C6C10: lui         $t4, 0x802D
    ctx->r12 = S32(0X802D << 16);
    // 0x802C6C14: lui         $t6, 0x802D
    ctx->r14 = S32(0X802D << 16);
    // 0x802C6C18: lw          $t4, -0x7F34($t4)
    ctx->r12 = MEM_W(ctx->r12, -0X7F34);
    // 0x802C6C1C: lw          $t7, 0x0($s5)
    ctx->r15 = MEM_W(ctx->r21, 0X0);
    // 0x802C6C20: lw          $t6, -0x7F30($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X7F30);
    // 0x802C6C24: lw          $t3, 0x4($s5)
    ctx->r11 = MEM_W(ctx->r21, 0X4);
    // 0x802C6C28: sltiu       $at, $a2, 0xB
    ctx->r1 = ctx->r6 < 0XB ? 1 : 0;
    // 0x802C6C2C: addu        $s2, $t7, $t4
    ctx->r18 = ADD32(ctx->r15, ctx->r12);
    // 0x802C6C30: beq         $at, $zero, L_802C6C80
    if (ctx->r1 == 0) {
        // 0x802C6C34: addu        $s3, $t3, $t6
        ctx->r19 = ADD32(ctx->r11, ctx->r14);
            goto L_802C6C80;
    }
    // 0x802C6C34: addu        $s3, $t3, $t6
    ctx->r19 = ADD32(ctx->r11, ctx->r14);
    // 0x802C6C38: sll         $t5, $a2, 2
    ctx->r13 = S32(ctx->r6 << 2);
    // 0x802C6C3C: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C6C40: addu        $at, $at, $t5
    gpr jr_addend_802C6C48 = ctx->r13;
    ctx->r1 = ADD32(ctx->r1, ctx->r13);
    // 0x802C6C44: lw          $t5, -0x7DB4($at)
    ctx->r13 = ADD32(ctx->r1, -0X7DB4);
    // 0x802C6C48: jr          $t5
    // 0x802C6C4C: nop

    switch (jr_addend_802C6C48 >> 2) {
        case 0: goto L_802C6C64; break;
        case 1: goto L_802C6C64; break;
        case 2: goto L_802C6C64; break;
        case 3: goto L_802C6C64; break;
        case 4: goto L_802C6C64; break;
        case 5: goto L_802C6C64; break;
        case 6: goto L_802C6C64; break;
        case 7: goto L_802C6C64; break;
        case 8: goto L_802C6C64; break;
        case 9: goto L_802C6C80; break;
        case 10: goto L_802C6C50; break;
        default: switch_error(__func__, 0x802C6C48, 0x802C824C);
    }
    // 0x802C6C4C: nop

L_802C6C50:
    // 0x802C6C50: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x802C6C54: jal         0x802C6CC8
    // 0x802C6C58: or          $a1, $s2, $zero
    ctx->r5 = ctx->r18 | 0;
    func_i9_802C6CC8(rdram, ctx);
        goto after_4;
    // 0x802C6C58: or          $a1, $s2, $zero
    ctx->r5 = ctx->r18 | 0;
    after_4:
    // 0x802C6C5C: b           L_802C6C80
    // 0x802C6C60: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
        goto L_802C6C80;
    // 0x802C6C60: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
L_802C6C64:
    // 0x802C6C64: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x802C6C68: or          $a1, $s6, $zero
    ctx->r5 = ctx->r22 | 0;
    // 0x802C6C6C: lw          $a3, 0xC($s5)
    ctx->r7 = MEM_W(ctx->r21, 0XC);
    // 0x802C6C70: sw          $s2, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r18;
    // 0x802C6C74: jal         0x802C71AC
    // 0x802C6C78: sw          $s3, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r19;
    func_i9_802C71AC(rdram, ctx);
        goto after_5;
    // 0x802C6C78: sw          $s3, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r19;
    after_5:
    // 0x802C6C7C: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
L_802C6C80:
    // 0x802C6C80: lw          $t8, 0x68($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X68);
    // 0x802C6C84: addiu       $s6, $s6, 0x1
    ctx->r22 = ADD32(ctx->r22, 0X1);
    // 0x802C6C88: addiu       $s4, $s4, 0x10
    ctx->r20 = ADD32(ctx->r20, 0X10);
    // 0x802C6C8C: bne         $s6, $t8, L_802C6820
    if (ctx->r22 != ctx->r24) {
        // 0x802C6C90: addiu       $s5, $s5, 0x10
        ctx->r21 = ADD32(ctx->r21, 0X10);
            goto L_802C6820;
    }
    // 0x802C6C90: addiu       $s5, $s5, 0x10
    ctx->r21 = ADD32(ctx->r21, 0X10);
L_802C6C94:
    // 0x802C6C94: lw          $ra, 0x64($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X64);
    // 0x802C6C98: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
    // 0x802C6C9C: lw          $s0, 0x40($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X40);
    // 0x802C6CA0: lw          $s1, 0x44($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X44);
    // 0x802C6CA4: lw          $s2, 0x48($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X48);
    // 0x802C6CA8: lw          $s3, 0x4C($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X4C);
    // 0x802C6CAC: lw          $s4, 0x50($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X50);
    // 0x802C6CB0: lw          $s5, 0x54($sp)
    ctx->r21 = MEM_W(ctx->r29, 0X54);
    // 0x802C6CB4: lw          $s6, 0x58($sp)
    ctx->r22 = MEM_W(ctx->r29, 0X58);
    // 0x802C6CB8: lw          $s7, 0x5C($sp)
    ctx->r23 = MEM_W(ctx->r29, 0X5C);
    // 0x802C6CBC: lw          $fp, 0x60($sp)
    ctx->r30 = MEM_W(ctx->r29, 0X60);
    // 0x802C6CC0: jr          $ra
    // 0x802C6CC4: addiu       $sp, $sp, 0x70
    ctx->r29 = ADD32(ctx->r29, 0X70);
    return;
    // 0x802C6CC4: addiu       $sp, $sp, 0x70
    ctx->r29 = ADD32(ctx->r29, 0X70);
;}
RECOMP_FUNC void func_i9_802C6CC8(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C6CC8: addiu       $sp, $sp, -0x68
    ctx->r29 = ADD32(ctx->r29, -0X68);
    // 0x802C6CCC: sw          $fp, 0x60($sp)
    MEM_W(0X60, ctx->r29) = ctx->r30;
    // 0x802C6CD0: sw          $s7, 0x5C($sp)
    MEM_W(0X5C, ctx->r29) = ctx->r23;
    // 0x802C6CD4: sw          $s6, 0x58($sp)
    MEM_W(0X58, ctx->r29) = ctx->r22;
    // 0x802C6CD8: sw          $s4, 0x50($sp)
    MEM_W(0X50, ctx->r29) = ctx->r20;
    // 0x802C6CDC: sw          $s0, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r16;
    // 0x802C6CE0: sw          $ra, 0x64($sp)
    MEM_W(0X64, ctx->r29) = ctx->r31;
    // 0x802C6CE4: sw          $s5, 0x54($sp)
    MEM_W(0X54, ctx->r29) = ctx->r21;
    // 0x802C6CE8: sw          $s3, 0x4C($sp)
    MEM_W(0X4C, ctx->r29) = ctx->r19;
    // 0x802C6CEC: sw          $s2, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r18;
    // 0x802C6CF0: sw          $s1, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r17;
    // 0x802C6CF4: lui         $t7, 0x107
    ctx->r15 = S32(0X107 << 16);
    // 0x802C6CF8: addiu       $t7, $t7, -0x9D8
    ctx->r15 = ADD32(ctx->r15, -0X9D8);
    // 0x802C6CFC: lui         $t6, 0x600
    ctx->r14 = S32(0X600 << 16);
    // 0x802C6D00: or          $s7, $a1, $zero
    ctx->r23 = ctx->r5 | 0;
    // 0x802C6D04: sw          $t6, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r14;
    // 0x802C6D08: sw          $t7, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r15;
    // 0x802C6D0C: addiu       $s4, $a0, 0x8
    ctx->r20 = ADD32(ctx->r4, 0X8);
    // 0x802C6D10: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x802C6D14: or          $s0, $zero, $zero
    ctx->r16 = 0 | 0;
    // 0x802C6D18: addiu       $s6, $zero, 0x5
    ctx->r22 = ADD32(0, 0X5);
    // 0x802C6D1C: addiu       $fp, $zero, 0xED
    ctx->r30 = ADD32(0, 0XED);
L_802C6D20:
    // 0x802C6D20: div         $zero, $s0, $s6
    lo = S32(S64(S32(ctx->r16)) / S64(S32(ctx->r22))); hi = S32(S64(S32(ctx->r16)) % S64(S32(ctx->r22)));
    // 0x802C6D24: mflo        $t8
    ctx->r24 = lo;
    // 0x802C6D28: addiu       $t1, $zero, 0x83
    ctx->r9 = ADD32(0, 0X83);
    // 0x802C6D2C: addiu       $t2, $zero, 0x10
    ctx->r10 = ADD32(0, 0X10);
    // 0x802C6D30: multu       $t8, $fp
    result = U64(U32(ctx->r24)) * U64(U32(ctx->r30)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x802C6D34: sw          $t2, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r10;
    // 0x802C6D38: sw          $t1, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r9;
    // 0x802C6D3C: or          $a0, $s4, $zero
    ctx->r4 = ctx->r20 | 0;
    // 0x802C6D40: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C6D44: bne         $s6, $zero, L_802C6D50
    if (ctx->r22 != 0) {
        // 0x802C6D48: nop
    
            goto L_802C6D50;
    }
    // 0x802C6D48: nop

    // 0x802C6D4C: break       7
    do_break(2150395212);
L_802C6D50:
    // 0x802C6D50: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x802C6D54: bne         $s6, $at, L_802C6D68
    if (ctx->r22 != ctx->r1) {
        // 0x802C6D58: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_802C6D68;
    }
    // 0x802C6D58: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x802C6D5C: bne         $s0, $at, L_802C6D68
    if (ctx->r16 != ctx->r1) {
        // 0x802C6D60: nop
    
            goto L_802C6D68;
    }
    // 0x802C6D60: nop

    // 0x802C6D64: break       6
    do_break(2150395236);
L_802C6D68:
    // 0x802C6D68: mflo        $t9
    ctx->r25 = lo;
    // 0x802C6D6C: addu        $a2, $s7, $t9
    ctx->r6 = ADD32(ctx->r23, ctx->r25);
    // 0x802C6D70: addiu       $a2, $a2, 0x1C
    ctx->r6 = ADD32(ctx->r6, 0X1C);
    // 0x802C6D74: div         $zero, $s0, $s6
    lo = S32(S64(S32(ctx->r16)) / S64(S32(ctx->r22))); hi = S32(S64(S32(ctx->r16)) % S64(S32(ctx->r22)));
    // 0x802C6D78: mfhi        $a3
    ctx->r7 = hi;
    // 0x802C6D7C: sll         $t0, $a3, 3
    ctx->r8 = S32(ctx->r7 << 3);
    // 0x802C6D80: addu        $t0, $t0, $a3
    ctx->r8 = ADD32(ctx->r8, ctx->r7);
    // 0x802C6D84: sll         $t0, $t0, 1
    ctx->r8 = S32(ctx->r8 << 1);
    // 0x802C6D88: bne         $s6, $zero, L_802C6D94
    if (ctx->r22 != 0) {
        // 0x802C6D8C: nop
    
            goto L_802C6D94;
    }
    // 0x802C6D8C: nop

    // 0x802C6D90: break       7
    do_break(2150395280);
L_802C6D94:
    // 0x802C6D94: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x802C6D98: bne         $s6, $at, L_802C6DAC
    if (ctx->r22 != ctx->r1) {
        // 0x802C6D9C: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_802C6DAC;
    }
    // 0x802C6D9C: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x802C6DA0: bne         $s0, $at, L_802C6DAC
    if (ctx->r16 != ctx->r1) {
        // 0x802C6DA4: nop
    
            goto L_802C6DAC;
    }
    // 0x802C6DA4: nop

    // 0x802C6DA8: break       6
    do_break(2150395304);
L_802C6DAC:
    // 0x802C6DAC: addiu       $a3, $t0, 0x5F
    ctx->r7 = ADD32(ctx->r8, 0X5F);
    // 0x802C6DB0: jal         0x80094338
    // 0x802C6DB4: nop

    func_80094338(rdram, ctx);
        goto after_0;
    // 0x802C6DB4: nop

    after_0:
    // 0x802C6DB8: addiu       $s0, $s0, 0x1
    ctx->r16 = ADD32(ctx->r16, 0X1);
    // 0x802C6DBC: slti        $at, $s0, 0x9
    ctx->r1 = SIGNED(ctx->r16) < 0X9 ? 1 : 0;
    // 0x802C6DC0: bne         $at, $zero, L_802C6D20
    if (ctx->r1 != 0) {
        // 0x802C6DC4: or          $s4, $v0, $zero
        ctx->r20 = ctx->r2 | 0;
            goto L_802C6D20;
    }
    // 0x802C6DC4: or          $s4, $v0, $zero
    ctx->r20 = ctx->r2 | 0;
    // 0x802C6DC8: addiu       $t3, $zero, 0x57
    ctx->r11 = ADD32(0, 0X57);
    // 0x802C6DCC: addiu       $t4, $zero, 0x10
    ctx->r12 = ADD32(0, 0X10);
    // 0x802C6DD0: sw          $t4, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r12;
    // 0x802C6DD4: sw          $t3, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r11;
    // 0x802C6DD8: or          $a0, $s4, $zero
    ctx->r4 = ctx->r20 | 0;
    // 0x802C6DDC: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C6DE0: addiu       $a2, $s7, 0x1C
    ctx->r6 = ADD32(ctx->r23, 0X1C);
    // 0x802C6DE4: jal         0x80094338
    // 0x802C6DE8: addiu       $a3, $zero, 0x44
    ctx->r7 = ADD32(0, 0X44);
    func_80094338(rdram, ctx);
        goto after_1;
    // 0x802C6DE8: addiu       $a3, $zero, 0x44
    ctx->r7 = ADD32(0, 0X44);
    after_1:
    // 0x802C6DEC: addiu       $t5, $zero, 0x57
    ctx->r13 = ADD32(0, 0X57);
    // 0x802C6DF0: addiu       $t6, $zero, 0x10
    ctx->r14 = ADD32(0, 0X10);
    // 0x802C6DF4: sw          $t6, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r14;
    // 0x802C6DF8: sw          $t5, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r13;
    // 0x802C6DFC: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C6E00: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C6E04: addiu       $a2, $s7, 0xA9
    ctx->r6 = ADD32(ctx->r23, 0XA9);
    // 0x802C6E08: jal         0x80094338
    // 0x802C6E0C: addiu       $a3, $zero, 0x44
    ctx->r7 = ADD32(0, 0X44);
    func_80094338(rdram, ctx);
        goto after_2;
    // 0x802C6E0C: addiu       $a3, $zero, 0x44
    ctx->r7 = ADD32(0, 0X44);
    after_2:
    // 0x802C6E10: addiu       $t7, $zero, 0x57
    ctx->r15 = ADD32(0, 0X57);
    // 0x802C6E14: addiu       $t8, $zero, 0x10
    ctx->r24 = ADD32(0, 0X10);
    // 0x802C6E18: sw          $t8, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r24;
    // 0x802C6E1C: sw          $t7, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r15;
    // 0x802C6E20: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C6E24: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C6E28: addiu       $a2, $s7, 0x136
    ctx->r6 = ADD32(ctx->r23, 0X136);
    // 0x802C6E2C: jal         0x80094338
    // 0x802C6E30: addiu       $a3, $zero, 0x44
    ctx->r7 = ADD32(0, 0X44);
    func_80094338(rdram, ctx);
        goto after_3;
    // 0x802C6E30: addiu       $a3, $zero, 0x44
    ctx->r7 = ADD32(0, 0X44);
    after_3:
    // 0x802C6E34: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C6E38: addiu       $t0, $zero, 0xFF
    ctx->r8 = ADD32(0, 0XFF);
    // 0x802C6E3C: addiu       $t1, $zero, 0xFF
    ctx->r9 = ADD32(0, 0XFF);
    // 0x802C6E40: addiu       $t2, $zero, 0xFF
    ctx->r10 = ADD32(0, 0XFF);
    // 0x802C6E44: addiu       $t3, $zero, 0xFF
    ctx->r11 = ADD32(0, 0XFF);
    // 0x802C6E48: addiu       $t4, $zero, 0xFF
    ctx->r12 = ADD32(0, 0XFF);
    // 0x802C6E4C: addiu       $t5, $zero, 0xFF
    ctx->r13 = ADD32(0, 0XFF);
    // 0x802C6E50: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C6E54: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C6E58: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C6E5C: sw          $t8, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r24;
    // 0x802C6E60: sw          $t7, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r15;
    // 0x802C6E64: sw          $t6, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r14;
    // 0x802C6E68: sw          $t5, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r13;
    // 0x802C6E6C: sw          $t4, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r12;
    // 0x802C6E70: sw          $t3, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r11;
    // 0x802C6E74: sw          $t2, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r10;
    // 0x802C6E78: sw          $t1, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r9;
    // 0x802C6E7C: sw          $t0, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r8;
    // 0x802C6E80: sw          $t9, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r25;
    // 0x802C6E84: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C6E88: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C6E8C: addiu       $a2, $zero, 0xFF
    ctx->r6 = ADD32(0, 0XFF);
    // 0x802C6E90: jal         0x801E946C
    // 0x802C6E94: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    func_801E946C(rdram, ctx);
        goto after_4;
    // 0x802C6E94: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    after_4:
    // 0x802C6E98: addiu       $t9, $zero, 0x1D
    ctx->r25 = ADD32(0, 0X1D);
    // 0x802C6E9C: sw          $t9, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r25;
    // 0x802C6EA0: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C6EA4: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C6EA8: addiu       $a2, $zero, 0x7
    ctx->r6 = ADD32(0, 0X7);
    // 0x802C6EAC: addiu       $a3, $s7, 0x80
    ctx->r7 = ADD32(ctx->r23, 0X80);
    // 0x802C6EB0: jal         0x801E3EE0
    // 0x802C6EB4: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    func_801E3EE0(rdram, ctx);
        goto after_5;
    // 0x802C6EB4: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    after_5:
    // 0x802C6EB8: lui         $s1, 0x802D
    ctx->r17 = S32(0X802D << 16);
    // 0x802C6EBC: lui         $s2, 0x802D
    ctx->r18 = S32(0X802D << 16);
    // 0x802C6EC0: lui         $s5, 0x802D
    ctx->r21 = S32(0X802D << 16);
    // 0x802C6EC4: or          $s4, $v0, $zero
    ctx->r20 = ctx->r2 | 0;
    // 0x802C6EC8: addiu       $s5, $s5, -0x7F3C
    ctx->r21 = ADD32(ctx->r21, -0X7F3C);
    // 0x802C6ECC: addiu       $s2, $s2, -0x7EBC
    ctx->r18 = ADD32(ctx->r18, -0X7EBC);
    // 0x802C6ED0: addiu       $s1, $s1, -0x7EC8
    ctx->r17 = ADD32(ctx->r17, -0X7EC8);
    // 0x802C6ED4: or          $s0, $zero, $zero
    ctx->r16 = 0 | 0;
    // 0x802C6ED8: or          $s3, $zero, $zero
    ctx->r19 = 0 | 0;
L_802C6EDC:
    // 0x802C6EDC: lw          $t0, 0x0($s5)
    ctx->r8 = MEM_W(ctx->r21, 0X0);
    // 0x802C6EE0: or          $a0, $s4, $zero
    ctx->r4 = ctx->r20 | 0;
    // 0x802C6EE4: addiu       $a2, $zero, 0xFF
    ctx->r6 = ADD32(0, 0XFF);
    // 0x802C6EE8: bne         $s0, $t0, L_802C6EF8
    if (ctx->r16 != ctx->r8) {
        // 0x802C6EEC: addiu       $a3, $zero, 0xFF
        ctx->r7 = ADD32(0, 0XFF);
            goto L_802C6EF8;
    }
    // 0x802C6EEC: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    // 0x802C6EF0: b           L_802C6EFC
    // 0x802C6EF4: addiu       $a1, $zero, 0x6
    ctx->r5 = ADD32(0, 0X6);
        goto L_802C6EFC;
    // 0x802C6EF4: addiu       $a1, $zero, 0x6
    ctx->r5 = ADD32(0, 0X6);
L_802C6EF8:
    // 0x802C6EF8: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
L_802C6EFC:
    // 0x802C6EFC: addiu       $t1, $zero, 0xFF
    ctx->r9 = ADD32(0, 0XFF);
    // 0x802C6F00: addiu       $t2, $zero, 0xFF
    ctx->r10 = ADD32(0, 0XFF);
    // 0x802C6F04: addiu       $t3, $zero, 0xFF
    ctx->r11 = ADD32(0, 0XFF);
    // 0x802C6F08: addiu       $t4, $zero, 0xFF
    ctx->r12 = ADD32(0, 0XFF);
    // 0x802C6F0C: addiu       $t5, $zero, 0xFF
    ctx->r13 = ADD32(0, 0XFF);
    // 0x802C6F10: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C6F14: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C6F18: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C6F1C: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C6F20: addiu       $t0, $zero, 0xFF
    ctx->r8 = ADD32(0, 0XFF);
    // 0x802C6F24: sw          $t0, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r8;
    // 0x802C6F28: sw          $t9, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r25;
    // 0x802C6F2C: sw          $t8, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r24;
    // 0x802C6F30: sw          $t7, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r15;
    // 0x802C6F34: sw          $t6, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r14;
    // 0x802C6F38: sw          $t5, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r13;
    // 0x802C6F3C: sw          $t4, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r12;
    // 0x802C6F40: sw          $t3, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r11;
    // 0x802C6F44: sw          $t2, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r10;
    // 0x802C6F48: jal         0x801E946C
    // 0x802C6F4C: sw          $t1, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r9;
    func_801E946C(rdram, ctx);
        goto after_6;
    // 0x802C6F4C: sw          $t1, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r9;
    after_6:
    // 0x802C6F50: lw          $t1, 0x0($s2)
    ctx->r9 = MEM_W(ctx->r18, 0X0);
    // 0x802C6F54: addiu       $t3, $zero, 0x47
    ctx->r11 = ADD32(0, 0X47);
    // 0x802C6F58: sw          $t3, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r11;
    // 0x802C6F5C: addu        $t2, $t1, $s7
    ctx->r10 = ADD32(ctx->r9, ctx->r23);
    // 0x802C6F60: addu        $a3, $t2, $s3
    ctx->r7 = ADD32(ctx->r10, ctx->r19);
    // 0x802C6F64: addiu       $a3, $a3, 0x34
    ctx->r7 = ADD32(ctx->r7, 0X34);
    // 0x802C6F68: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C6F6C: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C6F70: lw          $a2, 0x0($s1)
    ctx->r6 = MEM_W(ctx->r17, 0X0);
    // 0x802C6F74: jal         0x801E3EE0
    // 0x802C6F78: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    func_801E3EE0(rdram, ctx);
        goto after_7;
    // 0x802C6F78: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    after_7:
    // 0x802C6F7C: addiu       $s0, $s0, 0x1
    ctx->r16 = ADD32(ctx->r16, 0X1);
    // 0x802C6F80: slti        $at, $s0, 0x3
    ctx->r1 = SIGNED(ctx->r16) < 0X3 ? 1 : 0;
    // 0x802C6F84: addiu       $s1, $s1, 0x4
    ctx->r17 = ADD32(ctx->r17, 0X4);
    // 0x802C6F88: addiu       $s2, $s2, 0x4
    ctx->r18 = ADD32(ctx->r18, 0X4);
    // 0x802C6F8C: addiu       $s3, $s3, 0x8D
    ctx->r19 = ADD32(ctx->r19, 0X8D);
    // 0x802C6F90: bne         $at, $zero, L_802C6EDC
    if (ctx->r1 != 0) {
        // 0x802C6F94: or          $s4, $v0, $zero
        ctx->r20 = ctx->r2 | 0;
            goto L_802C6EDC;
    }
    // 0x802C6F94: or          $s4, $v0, $zero
    ctx->r20 = ctx->r2 | 0;
    // 0x802C6F98: lui         $s1, 0x800E
    ctx->r17 = S32(0X800E << 16);
    // 0x802C6F9C: lui         $s3, 0x802D
    ctx->r19 = S32(0X802D << 16);
    // 0x802C6FA0: lui         $s2, 0x802D
    ctx->r18 = S32(0X802D << 16);
    // 0x802C6FA4: addiu       $s2, $s2, -0x7F38
    ctx->r18 = ADD32(ctx->r18, -0X7F38);
    // 0x802C6FA8: addiu       $s3, $s3, -0x7F40
    ctx->r19 = ADD32(ctx->r19, -0X7F40);
    // 0x802C6FAC: addiu       $s1, $s1, -0x5528
    ctx->r17 = ADD32(ctx->r17, -0X5528);
    // 0x802C6FB0: or          $s0, $zero, $zero
    ctx->r16 = 0 | 0;
L_802C6FB4:
    // 0x802C6FB4: lw          $t4, 0x0($s3)
    ctx->r12 = MEM_W(ctx->r19, 0X0);
    // 0x802C6FB8: or          $a0, $s4, $zero
    ctx->r4 = ctx->r20 | 0;
    // 0x802C6FBC: addiu       $a2, $zero, 0x80
    ctx->r6 = ADD32(0, 0X80);
    // 0x802C6FC0: bne         $t4, $zero, L_802C6FF4
    if (ctx->r12 != 0) {
        // 0x802C6FC4: addiu       $a3, $zero, 0x80
        ctx->r7 = ADD32(0, 0X80);
            goto L_802C6FF4;
    }
    // 0x802C6FC4: addiu       $a3, $zero, 0x80
    ctx->r7 = ADD32(0, 0X80);
    // 0x802C6FC8: lw          $t5, 0x0($s5)
    ctx->r13 = MEM_W(ctx->r21, 0X0);
    // 0x802C6FCC: bne         $t5, $zero, L_802C6FEC
    if (ctx->r13 != 0) {
        // 0x802C6FD0: nop
    
            goto L_802C6FEC;
    }
    // 0x802C6FD0: nop

    // 0x802C6FD4: bne         $s0, $zero, L_802C6FE4
    if (ctx->r16 != 0) {
        // 0x802C6FD8: nop
    
            goto L_802C6FE4;
    }
    // 0x802C6FD8: nop

    // 0x802C6FDC: b           L_802C7044
    // 0x802C6FE0: addiu       $a1, $zero, 0x7
    ctx->r5 = ADD32(0, 0X7);
        goto L_802C7044;
    // 0x802C6FE0: addiu       $a1, $zero, 0x7
    ctx->r5 = ADD32(0, 0X7);
L_802C6FE4:
    // 0x802C6FE4: b           L_802C7044
    // 0x802C6FE8: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
        goto L_802C7044;
    // 0x802C6FE8: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
L_802C6FEC:
    // 0x802C6FEC: b           L_802C7044
    // 0x802C6FF0: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
        goto L_802C7044;
    // 0x802C6FF0: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
L_802C6FF4:
    // 0x802C6FF4: lw          $t6, 0x0($s5)
    ctx->r14 = MEM_W(ctx->r21, 0X0);
    // 0x802C6FF8: bnel        $t6, $zero, L_802C7030
    if (ctx->r14 != 0) {
        // 0x802C6FFC: lw          $t8, 0x0($s2)
        ctx->r24 = MEM_W(ctx->r18, 0X0);
            goto L_802C7030;
    }
    goto skip_0;
    // 0x802C6FFC: lw          $t8, 0x0($s2)
    ctx->r24 = MEM_W(ctx->r18, 0X0);
    skip_0:
    // 0x802C7000: bnel        $s0, $zero, L_802C7014
    if (ctx->r16 != 0) {
        // 0x802C7004: lw          $t7, 0x0($s2)
        ctx->r15 = MEM_W(ctx->r18, 0X0);
            goto L_802C7014;
    }
    goto skip_1;
    // 0x802C7004: lw          $t7, 0x0($s2)
    ctx->r15 = MEM_W(ctx->r18, 0X0);
    skip_1:
    // 0x802C7008: b           L_802C7044
    // 0x802C700C: addiu       $a1, $zero, 0x7
    ctx->r5 = ADD32(0, 0X7);
        goto L_802C7044;
    // 0x802C700C: addiu       $a1, $zero, 0x7
    ctx->r5 = ADD32(0, 0X7);
    // 0x802C7010: lw          $t7, 0x0($s2)
    ctx->r15 = MEM_W(ctx->r18, 0X0);
L_802C7014:
    // 0x802C7014: bne         $s0, $t7, L_802C7024
    if (ctx->r16 != ctx->r15) {
        // 0x802C7018: nop
    
            goto L_802C7024;
    }
    // 0x802C7018: nop

    // 0x802C701C: b           L_802C7044
    // 0x802C7020: addiu       $a1, $zero, 0x6
    ctx->r5 = ADD32(0, 0X6);
        goto L_802C7044;
    // 0x802C7020: addiu       $a1, $zero, 0x6
    ctx->r5 = ADD32(0, 0X6);
L_802C7024:
    // 0x802C7024: b           L_802C7044
    // 0x802C7028: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
        goto L_802C7044;
    // 0x802C7028: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C702C: lw          $t8, 0x0($s2)
    ctx->r24 = MEM_W(ctx->r18, 0X0);
L_802C7030:
    // 0x802C7030: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C7034: bne         $s0, $t8, L_802C7044
    if (ctx->r16 != ctx->r24) {
        // 0x802C7038: nop
    
            goto L_802C7044;
    }
    // 0x802C7038: nop

    // 0x802C703C: b           L_802C7044
    // 0x802C7040: addiu       $a1, $zero, 0x6
    ctx->r5 = ADD32(0, 0X6);
        goto L_802C7044;
    // 0x802C7040: addiu       $a1, $zero, 0x6
    ctx->r5 = ADD32(0, 0X6);
L_802C7044:
    // 0x802C7044: addiu       $t9, $zero, 0x80
    ctx->r25 = ADD32(0, 0X80);
    // 0x802C7048: addiu       $t0, $zero, 0xFF
    ctx->r8 = ADD32(0, 0XFF);
    // 0x802C704C: addiu       $t1, $zero, 0xFF
    ctx->r9 = ADD32(0, 0XFF);
    // 0x802C7050: addiu       $t2, $zero, 0xFF
    ctx->r10 = ADD32(0, 0XFF);
    // 0x802C7054: addiu       $t3, $zero, 0xFF
    ctx->r11 = ADD32(0, 0XFF);
    // 0x802C7058: addiu       $t4, $zero, 0xFF
    ctx->r12 = ADD32(0, 0XFF);
    // 0x802C705C: addiu       $t5, $zero, 0xFF
    ctx->r13 = ADD32(0, 0XFF);
    // 0x802C7060: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C7064: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C7068: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C706C: sw          $t8, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r24;
    // 0x802C7070: sw          $t7, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r15;
    // 0x802C7074: sw          $t6, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r14;
    // 0x802C7078: sw          $t5, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r13;
    // 0x802C707C: sw          $t4, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r12;
    // 0x802C7080: sw          $t3, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r11;
    // 0x802C7084: sw          $t2, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r10;
    // 0x802C7088: sw          $t1, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r9;
    // 0x802C708C: sw          $t0, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r8;
    // 0x802C7090: jal         0x801E946C
    // 0x802C7094: sw          $t9, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r25;
    func_801E946C(rdram, ctx);
        goto after_8;
    // 0x802C7094: sw          $t9, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r25;
    after_8:
    // 0x802C7098: div         $zero, $s0, $s6
    lo = S32(S64(S32(ctx->r16)) / S64(S32(ctx->r22))); hi = S32(S64(S32(ctx->r16)) % S64(S32(ctx->r22)));
    // 0x802C709C: mflo        $t2
    ctx->r10 = lo;
    // 0x802C70A0: lw          $v1, 0x0($s1)
    ctx->r3 = MEM_W(ctx->r17, 0X0);
    // 0x802C70A4: lui         $t0, 0x802D
    ctx->r8 = S32(0X802D << 16);
    // 0x802C70A8: multu       $t2, $fp
    result = U64(U32(ctx->r10)) * U64(U32(ctx->r30)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x802C70AC: sll         $t9, $v1, 2
    ctx->r25 = S32(ctx->r3 << 2);
    // 0x802C70B0: addu        $t0, $t0, $t9
    ctx->r8 = ADD32(ctx->r8, ctx->r25);
    // 0x802C70B4: lw          $t0, -0x7EB0($t0)
    ctx->r8 = MEM_W(ctx->r8, -0X7EB0);
    // 0x802C70B8: lui         $a2, 0x800E
    ctx->r6 = S32(0X800E << 16);
    // 0x802C70BC: addu        $a2, $a2, $t9
    ctx->r6 = ADD32(ctx->r6, ctx->r25);
    // 0x802C70C0: addu        $t1, $t0, $s7
    ctx->r9 = ADD32(ctx->r8, ctx->r23);
    // 0x802C70C4: lw          $a2, -0x55F0($a2)
    ctx->r6 = MEM_W(ctx->r6, -0X55F0);
    // 0x802C70C8: or          $v1, $t9, $zero
    ctx->r3 = ctx->r25 | 0;
    // 0x802C70CC: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C70D0: mflo        $t3
    ctx->r11 = lo;
    // 0x802C70D4: addu        $a3, $t1, $t3
    ctx->r7 = ADD32(ctx->r9, ctx->r11);
    // 0x802C70D8: addiu       $a3, $a3, 0x37
    ctx->r7 = ADD32(ctx->r7, 0X37);
    // 0x802C70DC: div         $zero, $s0, $s6
    lo = S32(S64(S32(ctx->r16)) / S64(S32(ctx->r22))); hi = S32(S64(S32(ctx->r16)) % S64(S32(ctx->r22)));
    // 0x802C70E0: mfhi        $t4
    ctx->r12 = hi;
    // 0x802C70E4: sll         $t5, $t4, 3
    ctx->r13 = S32(ctx->r12 << 3);
    // 0x802C70E8: addu        $t5, $t5, $t4
    ctx->r13 = ADD32(ctx->r13, ctx->r12);
    // 0x802C70EC: sll         $t5, $t5, 1
    ctx->r13 = S32(ctx->r13 << 1);
    // 0x802C70F0: addiu       $t6, $t5, 0x62
    ctx->r14 = ADD32(ctx->r13, 0X62);
    // 0x802C70F4: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x802C70F8: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C70FC: bne         $s6, $zero, L_802C7108
    if (ctx->r22 != 0) {
        // 0x802C7100: nop
    
            goto L_802C7108;
    }
    // 0x802C7100: nop

    // 0x802C7104: break       7
    do_break(2150396164);
L_802C7108:
    // 0x802C7108: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x802C710C: bne         $s6, $at, L_802C7120
    if (ctx->r22 != ctx->r1) {
        // 0x802C7110: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_802C7120;
    }
    // 0x802C7110: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x802C7114: bne         $s0, $at, L_802C7120
    if (ctx->r16 != ctx->r1) {
        // 0x802C7118: nop
    
            goto L_802C7120;
    }
    // 0x802C7118: nop

    // 0x802C711C: break       6
    do_break(2150396188);
L_802C7120:
    // 0x802C7120: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    // 0x802C7124: bne         $s6, $zero, L_802C7130
    if (ctx->r22 != 0) {
        // 0x802C7128: nop
    
            goto L_802C7130;
    }
    // 0x802C7128: nop

    // 0x802C712C: break       7
    do_break(2150396204);
L_802C7130:
    // 0x802C7130: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x802C7134: bne         $s6, $at, L_802C7148
    if (ctx->r22 != ctx->r1) {
        // 0x802C7138: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_802C7148;
    }
    // 0x802C7138: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x802C713C: bne         $s0, $at, L_802C7148
    if (ctx->r16 != ctx->r1) {
        // 0x802C7140: nop
    
            goto L_802C7148;
    }
    // 0x802C7140: nop

    // 0x802C7144: break       6
    do_break(2150396228);
L_802C7148:
    // 0x802C7148: jal         0x801E3EE0
    // 0x802C714C: nop

    func_801E3EE0(rdram, ctx);
        goto after_9;
    // 0x802C714C: nop

    after_9:
    // 0x802C7150: addiu       $s0, $s0, 0x1
    ctx->r16 = ADD32(ctx->r16, 0X1);
    // 0x802C7154: addiu       $at, $zero, 0x9
    ctx->r1 = ADD32(0, 0X9);
    // 0x802C7158: addiu       $s1, $s1, 0x4
    ctx->r17 = ADD32(ctx->r17, 0X4);
    // 0x802C715C: bne         $s0, $at, L_802C6FB4
    if (ctx->r16 != ctx->r1) {
        // 0x802C7160: or          $s4, $v0, $zero
        ctx->r20 = ctx->r2 | 0;
            goto L_802C6FB4;
    }
    // 0x802C7160: or          $s4, $v0, $zero
    ctx->r20 = ctx->r2 | 0;
    // 0x802C7164: lw          $ra, 0x64($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X64);
    // 0x802C7168: lw          $s0, 0x40($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X40);
    // 0x802C716C: lw          $s1, 0x44($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X44);
    // 0x802C7170: lw          $s2, 0x48($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X48);
    // 0x802C7174: lw          $s3, 0x4C($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X4C);
    // 0x802C7178: lw          $s4, 0x50($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X50);
    // 0x802C717C: lw          $s5, 0x54($sp)
    ctx->r21 = MEM_W(ctx->r29, 0X54);
    // 0x802C7180: lw          $s6, 0x58($sp)
    ctx->r22 = MEM_W(ctx->r29, 0X58);
    // 0x802C7184: lw          $s7, 0x5C($sp)
    ctx->r23 = MEM_W(ctx->r29, 0X5C);
    // 0x802C7188: lw          $fp, 0x60($sp)
    ctx->r30 = MEM_W(ctx->r29, 0X60);
    // 0x802C718C: jr          $ra
    // 0x802C7190: addiu       $sp, $sp, 0x68
    ctx->r29 = ADD32(ctx->r29, 0X68);
    return;
    // 0x802C7190: addiu       $sp, $sp, 0x68
    ctx->r29 = ADD32(ctx->r29, 0X68);
;}
RECOMP_FUNC void func_i9_802C7194(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C7194: sw          $a1, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r5;
    // 0x802C7198: sw          $a2, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r6;
    // 0x802C719C: sw          $a3, 0x8($a0)
    MEM_W(0X8, ctx->r4) = ctx->r7;
    // 0x802C71A0: lw          $t6, 0x10($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X10);
    // 0x802C71A4: jr          $ra
    // 0x802C71A8: sw          $t6, 0xC($a0)
    MEM_W(0XC, ctx->r4) = ctx->r14;
    return;
    // 0x802C71A8: sw          $t6, 0xC($a0)
    MEM_W(0XC, ctx->r4) = ctx->r14;
;}
RECOMP_FUNC void func_i9_802C71AC(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C71AC: addiu       $sp, $sp, -0xE8
    ctx->r29 = ADD32(ctx->r29, -0XE8);
    // 0x802C71B0: sw          $s7, 0x5C($sp)
    MEM_W(0X5C, ctx->r29) = ctx->r23;
    // 0x802C71B4: sw          $s6, 0x58($sp)
    MEM_W(0X58, ctx->r29) = ctx->r22;
    // 0x802C71B8: lw          $s7, 0xF8($sp)
    ctx->r23 = MEM_W(ctx->r29, 0XF8);
    // 0x802C71BC: sw          $ra, 0x64($sp)
    MEM_W(0X64, ctx->r29) = ctx->r31;
    // 0x802C71C0: sw          $fp, 0x60($sp)
    MEM_W(0X60, ctx->r29) = ctx->r30;
    // 0x802C71C4: sw          $s5, 0x54($sp)
    MEM_W(0X54, ctx->r29) = ctx->r21;
    // 0x802C71C8: sw          $s4, 0x50($sp)
    MEM_W(0X50, ctx->r29) = ctx->r20;
    // 0x802C71CC: sw          $s3, 0x4C($sp)
    MEM_W(0X4C, ctx->r29) = ctx->r19;
    // 0x802C71D0: sw          $s2, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r18;
    // 0x802C71D4: sw          $s1, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r17;
    // 0x802C71D8: sw          $s0, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r16;
    // 0x802C71DC: sw          $a2, 0xF0($sp)
    MEM_W(0XF0, ctx->r29) = ctx->r6;
    // 0x802C71E0: lui         $t6, 0x107
    ctx->r14 = S32(0X107 << 16);
    // 0x802C71E4: lui         $s6, 0x600
    ctx->r22 = S32(0X600 << 16);
    // 0x802C71E8: addiu       $t6, $t6, -0x9D8
    ctx->r14 = ADD32(ctx->r14, -0X9D8);
    // 0x802C71EC: sw          $t6, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r14;
    // 0x802C71F0: sw          $s6, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r22;
    // 0x802C71F4: or          $fp, $a3, $zero
    ctx->r30 = ctx->r7 | 0;
    // 0x802C71F8: lw          $a3, 0xFC($sp)
    ctx->r7 = MEM_W(ctx->r29, 0XFC);
    // 0x802C71FC: or          $s5, $a1, $zero
    ctx->r21 = ctx->r5 | 0;
    // 0x802C7200: addiu       $s1, $a0, 0x8
    ctx->r17 = ADD32(ctx->r4, 0X8);
    // 0x802C7204: addiu       $t7, $zero, 0x15C
    ctx->r15 = ADD32(0, 0X15C);
    // 0x802C7208: addiu       $t8, $zero, 0x18
    ctx->r24 = ADD32(0, 0X18);
    // 0x802C720C: addiu       $a2, $s7, 0x26
    ctx->r6 = ADD32(ctx->r23, 0X26);
    // 0x802C7210: sw          $a2, 0x88($sp)
    MEM_W(0X88, ctx->r29) = ctx->r6;
    // 0x802C7214: sw          $t8, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r24;
    // 0x802C7218: sw          $t7, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r15;
    // 0x802C721C: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    // 0x802C7220: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C7224: jal         0x80094338
    // 0x802C7228: addiu       $a3, $a3, 0x46
    ctx->r7 = ADD32(ctx->r7, 0X46);
    func_80094338(rdram, ctx);
        goto after_0;
    // 0x802C7228: addiu       $a3, $a3, 0x46
    ctx->r7 = ADD32(ctx->r7, 0X46);
    after_0:
    // 0x802C722C: lw          $a3, 0xFC($sp)
    ctx->r7 = MEM_W(ctx->r29, 0XFC);
    // 0x802C7230: addiu       $s0, $s7, 0x1C
    ctx->r16 = ADD32(ctx->r23, 0X1C);
    // 0x802C7234: addiu       $t9, $zero, 0x170
    ctx->r25 = ADD32(0, 0X170);
    // 0x802C7238: addiu       $t3, $zero, 0x10
    ctx->r11 = ADD32(0, 0X10);
    // 0x802C723C: sw          $t3, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r11;
    // 0x802C7240: sw          $t9, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r25;
    // 0x802C7244: or          $a2, $s0, $zero
    ctx->r6 = ctx->r16 | 0;
    // 0x802C7248: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C724C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C7250: jal         0x80094338
    // 0x802C7254: addiu       $a3, $a3, 0x68
    ctx->r7 = ADD32(ctx->r7, 0X68);
    func_80094338(rdram, ctx);
        goto after_1;
    // 0x802C7254: addiu       $a3, $a3, 0x68
    ctx->r7 = ADD32(ctx->r7, 0X68);
    after_1:
    // 0x802C7258: lw          $a3, 0xFC($sp)
    ctx->r7 = MEM_W(ctx->r29, 0XFC);
    // 0x802C725C: or          $s1, $v0, $zero
    ctx->r17 = ctx->r2 | 0;
    // 0x802C7260: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
    // 0x802C7264: addiu       $a3, $a3, 0x7E
    ctx->r7 = ADD32(ctx->r7, 0X7E);
L_802C7268:
    // 0x802C7268: addiu       $t4, $zero, 0x170
    ctx->r12 = ADD32(0, 0X170);
    // 0x802C726C: addiu       $t5, $zero, 0x10
    ctx->r13 = ADD32(0, 0X10);
    // 0x802C7270: sw          $t5, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r13;
    // 0x802C7274: sw          $t4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r12;
    // 0x802C7278: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    // 0x802C727C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C7280: or          $a2, $s0, $zero
    ctx->r6 = ctx->r16 | 0;
    // 0x802C7284: sw          $v1, 0x80($sp)
    MEM_W(0X80, ctx->r29) = ctx->r3;
    // 0x802C7288: jal         0x80094338
    // 0x802C728C: sw          $a3, 0x7C($sp)
    MEM_W(0X7C, ctx->r29) = ctx->r7;
    func_80094338(rdram, ctx);
        goto after_2;
    // 0x802C728C: sw          $a3, 0x7C($sp)
    MEM_W(0X7C, ctx->r29) = ctx->r7;
    after_2:
    // 0x802C7290: lw          $v1, 0x80($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X80);
    // 0x802C7294: lw          $a3, 0x7C($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X7C);
    // 0x802C7298: or          $s1, $v0, $zero
    ctx->r17 = ctx->r2 | 0;
    // 0x802C729C: addiu       $v1, $v1, 0x12
    ctx->r3 = ADD32(ctx->r3, 0X12);
    // 0x802C72A0: slti        $at, $v1, 0x36
    ctx->r1 = SIGNED(ctx->r3) < 0X36 ? 1 : 0;
    // 0x802C72A4: bne         $at, $zero, L_802C7268
    if (ctx->r1 != 0) {
        // 0x802C72A8: addiu       $a3, $a3, 0x12
        ctx->r7 = ADD32(ctx->r7, 0X12);
            goto L_802C7268;
    }
    // 0x802C72A8: addiu       $a3, $a3, 0x12
    ctx->r7 = ADD32(ctx->r7, 0X12);
    // 0x802C72AC: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x802C72B0: beq         $fp, $at, L_802C72C0
    if (ctx->r30 == ctx->r1) {
        // 0x802C72B4: addiu       $at, $zero, 0x3
        ctx->r1 = ADD32(0, 0X3);
            goto L_802C72C0;
    }
    // 0x802C72B4: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x802C72B8: bnel        $fp, $at, L_802C7318
    if (ctx->r30 != ctx->r1) {
        // 0x802C72BC: addiu       $t3, $zero, 0xFF
        ctx->r11 = ADD32(0, 0XFF);
            goto L_802C7318;
    }
    goto skip_0;
    // 0x802C72BC: addiu       $t3, $zero, 0xFF
    ctx->r11 = ADD32(0, 0XFF);
    skip_0:
L_802C72C0:
    // 0x802C72C0: lw          $a3, 0xFC($sp)
    ctx->r7 = MEM_W(ctx->r29, 0XFC);
    // 0x802C72C4: addiu       $t6, $zero, 0x170
    ctx->r14 = ADD32(0, 0X170);
    // 0x802C72C8: addiu       $t7, $zero, 0xA
    ctx->r15 = ADD32(0, 0XA);
    // 0x802C72CC: sw          $t7, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r15;
    // 0x802C72D0: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x802C72D4: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    // 0x802C72D8: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C72DC: or          $a2, $s0, $zero
    ctx->r6 = ctx->r16 | 0;
    // 0x802C72E0: jal         0x80094338
    // 0x802C72E4: addiu       $a3, $a3, 0xB7
    ctx->r7 = ADD32(ctx->r7, 0XB7);
    func_80094338(rdram, ctx);
        goto after_3;
    // 0x802C72E4: addiu       $a3, $a3, 0xB7
    ctx->r7 = ADD32(ctx->r7, 0XB7);
    after_3:
    // 0x802C72E8: lw          $a3, 0xFC($sp)
    ctx->r7 = MEM_W(ctx->r29, 0XFC);
    // 0x802C72EC: addiu       $t8, $zero, 0x170
    ctx->r24 = ADD32(0, 0X170);
    // 0x802C72F0: addiu       $t9, $zero, 0x10
    ctx->r25 = ADD32(0, 0X10);
    // 0x802C72F4: sw          $t9, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r25;
    // 0x802C72F8: sw          $t8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r24;
    // 0x802C72FC: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C7300: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C7304: or          $a2, $s0, $zero
    ctx->r6 = ctx->r16 | 0;
    // 0x802C7308: jal         0x80094338
    // 0x802C730C: addiu       $a3, $a3, 0xC2
    ctx->r7 = ADD32(ctx->r7, 0XC2);
    func_80094338(rdram, ctx);
        goto after_4;
    // 0x802C730C: addiu       $a3, $a3, 0xC2
    ctx->r7 = ADD32(ctx->r7, 0XC2);
    after_4:
    // 0x802C7310: or          $s1, $v0, $zero
    ctx->r17 = ctx->r2 | 0;
    // 0x802C7314: addiu       $t3, $zero, 0xFF
    ctx->r11 = ADD32(0, 0XFF);
L_802C7318:
    // 0x802C7318: sw          $t3, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r11;
    // 0x802C731C: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    // 0x802C7320: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C7324: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x802C7328: jal         0x801E7E74
    // 0x802C732C: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_801E7E74(rdram, ctx);
        goto after_5;
    // 0x802C732C: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_5:
    // 0x802C7330: lw          $a0, 0xFC($sp)
    ctx->r4 = MEM_W(ctx->r29, 0XFC);
    // 0x802C7334: or          $s1, $v0, $zero
    ctx->r17 = ctx->r2 | 0;
    // 0x802C7338: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
    // 0x802C733C: addiu       $s0, $s7, 0x3C
    ctx->r16 = ADD32(ctx->r23, 0X3C);
    // 0x802C7340: addiu       $s2, $s7, 0x56
    ctx->r18 = ADD32(ctx->r23, 0X56);
    // 0x802C7344: addiu       $s3, $a0, 0x80
    ctx->r19 = ADD32(ctx->r4, 0X80);
    // 0x802C7348: addiu       $t0, $a0, 0x8C
    ctx->r8 = ADD32(ctx->r4, 0X8C);
L_802C734C:
    // 0x802C734C: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    // 0x802C7350: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    // 0x802C7354: or          $a2, $s3, $zero
    ctx->r6 = ctx->r19 | 0;
    // 0x802C7358: or          $a3, $s2, $zero
    ctx->r7 = ctx->r18 | 0;
    // 0x802C735C: sw          $t0, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r8;
    // 0x802C7360: sw          $v1, 0x80($sp)
    MEM_W(0X80, ctx->r29) = ctx->r3;
    // 0x802C7364: jal         0x801E7FD8
    // 0x802C7368: sw          $t0, 0x70($sp)
    MEM_W(0X70, ctx->r29) = ctx->r8;
    func_801E7FD8(rdram, ctx);
        goto after_6;
    // 0x802C7368: sw          $t0, 0x70($sp)
    MEM_W(0X70, ctx->r29) = ctx->r8;
    after_6:
    // 0x802C736C: lw          $v1, 0x80($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X80);
    // 0x802C7370: lw          $t0, 0x70($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X70);
    // 0x802C7374: addiu       $s3, $s3, 0x12
    ctx->r19 = ADD32(ctx->r19, 0X12);
    // 0x802C7378: addiu       $v1, $v1, 0x12
    ctx->r3 = ADD32(ctx->r3, 0X12);
    // 0x802C737C: slti        $at, $v1, 0x36
    ctx->r1 = SIGNED(ctx->r3) < 0X36 ? 1 : 0;
    // 0x802C7380: or          $s1, $v0, $zero
    ctx->r17 = ctx->r2 | 0;
    // 0x802C7384: bne         $at, $zero, L_802C734C
    if (ctx->r1 != 0) {
        // 0x802C7388: addiu       $t0, $t0, 0x12
        ctx->r8 = ADD32(ctx->r8, 0X12);
            goto L_802C734C;
    }
    // 0x802C7388: addiu       $t0, $t0, 0x12
    ctx->r8 = ADD32(ctx->r8, 0X12);
    // 0x802C738C: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x802C7390: beq         $fp, $at, L_802C73A0
    if (ctx->r30 == ctx->r1) {
        // 0x802C7394: addiu       $at, $zero, 0x3
        ctx->r1 = ADD32(0, 0X3);
            goto L_802C73A0;
    }
    // 0x802C7394: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x802C7398: bnel        $fp, $at, L_802C73C4
    if (ctx->r30 != ctx->r1) {
        // 0x802C739C: addiu       $s1, $v0, 0x8
        ctx->r17 = ADD32(ctx->r2, 0X8);
            goto L_802C73C4;
    }
    goto skip_1;
    // 0x802C739C: addiu       $s1, $v0, 0x8
    ctx->r17 = ADD32(ctx->r2, 0X8);
    skip_1:
L_802C73A0:
    // 0x802C73A0: lw          $t4, 0xFC($sp)
    ctx->r12 = MEM_W(ctx->r29, 0XFC);
    // 0x802C73A4: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    // 0x802C73A8: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    // 0x802C73AC: addiu       $t5, $t4, 0xD0
    ctx->r13 = ADD32(ctx->r12, 0XD0);
    // 0x802C73B0: sw          $t5, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r13;
    // 0x802C73B4: or          $a3, $s2, $zero
    ctx->r7 = ctx->r18 | 0;
    // 0x802C73B8: jal         0x801E7FD8
    // 0x802C73BC: addiu       $a2, $t4, 0xC4
    ctx->r6 = ADD32(ctx->r12, 0XC4);
    func_801E7FD8(rdram, ctx);
        goto after_7;
    // 0x802C73BC: addiu       $a2, $t4, 0xC4
    ctx->r6 = ADD32(ctx->r12, 0XC4);
    after_7:
    // 0x802C73C0: addiu       $s1, $v0, 0x8
    ctx->r17 = ADD32(ctx->r2, 0X8);
L_802C73C4:
    // 0x802C73C4: lui         $t6, 0xE700
    ctx->r14 = S32(0XE700 << 16);
    // 0x802C73C8: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    // 0x802C73CC: sw          $t6, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r14;
    // 0x802C73D0: sw          $zero, 0x4($v0)
    MEM_W(0X4, ctx->r2) = 0;
    // 0x802C73D4: lui         $t7, 0xED02
    ctx->r15 = S32(0XED02 << 16);
    // 0x802C73D8: addiu       $t7, $t7, 0x50
    ctx->r15 = ADD32(ctx->r15, 0X50);
    // 0x802C73DC: lui         $t8, 0x68
    ctx->r24 = S32(0X68 << 16);
    // 0x802C73E0: addiu       $t8, $t8, -0x3C94
    ctx->r24 = ADD32(ctx->r24, -0X3C94);
    // 0x802C73E4: addiu       $s1, $s1, 0x8
    ctx->r17 = ADD32(ctx->r17, 0X8);
    { extern uint32_t wr64_experimental_viewport_borders(void); if (wr64_experimental_viewport_borders()) { ctx->r15 = 0xED000000U; ctx->r24 = 0x006A03C0U; } }
    // 0x802C73E8: sw          $t7, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r15;
    // 0x802C73EC: sw          $t8, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r24;
    // 0x802C73F0: or          $a1, $s1, $zero
    ctx->r5 = ctx->r17 | 0;
    // 0x802C73F4: lui         $t9, 0xB400
    ctx->r25 = S32(0XB400 << 16);
    // 0x802C73F8: sw          $t9, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r25;
    // 0x802C73FC: lui         $t3, 0x802D
    ctx->r11 = S32(0X802D << 16);
    // 0x802C7400: lhu         $t3, -0x7D80($t3)
    ctx->r11 = MEM_HU(ctx->r11, -0X7D80);
    // 0x802C7404: addiu       $s1, $s1, 0x8
    ctx->r17 = ADD32(ctx->r17, 0X8);
    // 0x802C7408: or          $a2, $s1, $zero
    ctx->r6 = ctx->r17 | 0;
    // 0x802C740C: addiu       $s1, $s1, 0x8
    ctx->r17 = ADD32(ctx->r17, 0X8);
    // 0x802C7410: lui         $t4, 0x103
    ctx->r12 = S32(0X103 << 16);
    // 0x802C7414: lui         $t5, 0x700
    ctx->r13 = S32(0X700 << 16);
    // 0x802C7418: sw          $t3, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r11;
    // 0x802C741C: addiu       $t5, $t5, 0xA40
    ctx->r13 = ADD32(ctx->r13, 0XA40);
    // 0x802C7420: ori         $t4, $t4, 0x40
    ctx->r12 = ctx->r12 | 0X40;
    // 0x802C7424: or          $a3, $s1, $zero
    ctx->r7 = ctx->r17 | 0;
    // 0x802C7428: lui         $t6, 0x107
    ctx->r14 = S32(0X107 << 16);
    // 0x802C742C: sw          $t4, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r12;
    // 0x802C7430: sw          $t5, 0x4($a2)
    MEM_W(0X4, ctx->r6) = ctx->r13;
    // 0x802C7434: addiu       $t6, $t6, -0xB78
    ctx->r14 = ADD32(ctx->r14, -0XB78);
    // 0x802C7438: sw          $t6, 0x4($a3)
    MEM_W(0X4, ctx->r7) = ctx->r14;
    // 0x802C743C: sw          $s6, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r22;
    // 0x802C7440: bne         $s5, $zero, L_802C7450
    if (ctx->r21 != 0) {
        // 0x802C7444: addiu       $s1, $s1, 0x8
        ctx->r17 = ADD32(ctx->r17, 0X8);
            goto L_802C7450;
    }
    // 0x802C7444: addiu       $s1, $s1, 0x8
    ctx->r17 = ADD32(ctx->r17, 0X8);
    // 0x802C7448: b           L_802C7454
    // 0x802C744C: or          $s6, $zero, $zero
    ctx->r22 = 0 | 0;
        goto L_802C7454;
    // 0x802C744C: or          $s6, $zero, $zero
    ctx->r22 = 0 | 0;
L_802C7450:
    // 0x802C7450: addiu       $s6, $zero, 0x4
    ctx->r22 = ADD32(0, 0X4);
L_802C7454:
    // 0x802C7454: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x802C7458: bnel        $fp, $at, L_802C746C
    if (ctx->r30 != ctx->r1) {
        // 0x802C745C: addiu       $s0, $zero, 0x3
        ctx->r16 = ADD32(0, 0X3);
            goto L_802C746C;
    }
    goto skip_2;
    // 0x802C745C: addiu       $s0, $zero, 0x3
    ctx->r16 = ADD32(0, 0X3);
    skip_2:
    // 0x802C7460: b           L_802C746C
    // 0x802C7464: addiu       $s0, $zero, 0x1
    ctx->r16 = ADD32(0, 0X1);
        goto L_802C746C;
    // 0x802C7464: addiu       $s0, $zero, 0x1
    ctx->r16 = ADD32(0, 0X1);
    // 0x802C7468: addiu       $s0, $zero, 0x3
    ctx->r16 = ADD32(0, 0X3);
L_802C746C:
    // 0x802C746C: blez        $s0, L_802C75A4
    if (SIGNED(ctx->r16) <= 0) {
        // 0x802C7470: or          $s4, $zero, $zero
        ctx->r20 = 0 | 0;
            goto L_802C75A4;
    }
    // 0x802C7470: or          $s4, $zero, $zero
    ctx->r20 = 0 | 0;
    // 0x802C7474: lui         $t9, 0x700
    ctx->r25 = S32(0X700 << 16);
    // 0x802C7478: addiu       $t9, $t9, 0x0
    ctx->r25 = ADD32(ctx->r25, 0X0);
    // 0x802C747C: sll         $t7, $s6, 4
    ctx->r15 = S32(ctx->r22 << 4);
    // 0x802C7480: sll         $t3, $s6, 6
    ctx->r11 = S32(ctx->r22 << 6);
    // 0x802C7484: sll         $t2, $s6, 2
    ctx->r10 = S32(ctx->r22 << 2);
    // 0x802C7488: subu        $t2, $t2, $s6
    ctx->r10 = SUB32(ctx->r10, ctx->r22);
    // 0x802C748C: addiu       $t4, $t3, 0xA80
    ctx->r12 = ADD32(ctx->r11, 0XA80);
    // 0x802C7490: addiu       $t8, $t7, 0x1280
    ctx->r24 = ADD32(ctx->r15, 0X1280);
    // 0x802C7494: lui         $s5, 0x801D
    ctx->r21 = S32(0X801D << 16);
    // 0x802C7498: lui         $s3, 0x102
    ctx->r19 = S32(0X102 << 16);
    // 0x802C749C: lui         $s2, 0x380
    ctx->r18 = S32(0X380 << 16);
    // 0x802C74A0: ori         $s2, $s2, 0x10
    ctx->r18 = ctx->r18 | 0X10;
    // 0x802C74A4: ori         $s3, $s3, 0x40
    ctx->r19 = ctx->r19 | 0X40;
    // 0x802C74A8: addiu       $s5, $s5, -0x1A08
    ctx->r21 = ADD32(ctx->r21, -0X1A08);
    // 0x802C74AC: addu        $t0, $t8, $t9
    ctx->r8 = ADD32(ctx->r24, ctx->r25);
    // 0x802C74B0: addu        $t1, $t4, $t9
    ctx->r9 = ADD32(ctx->r12, ctx->r25);
    // 0x802C74B4: sll         $t2, $t2, 6
    ctx->r10 = S32(ctx->r10 << 6);
L_802C74B8:
    // 0x802C74B8: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x802C74BC: bne         $fp, $at, L_802C74F4
    if (ctx->r30 != ctx->r1) {
        // 0x802C74C0: or          $v0, $s1, $zero
        ctx->r2 = ctx->r17 | 0;
            goto L_802C74F4;
    }
    // 0x802C74C0: or          $v0, $s1, $zero
    ctx->r2 = ctx->r17 | 0;
    // 0x802C74C4: lw          $t5, 0xF0($sp)
    ctx->r13 = MEM_W(ctx->r29, 0XF0);
    // 0x802C74C8: sll         $t7, $s4, 2
    ctx->r15 = S32(ctx->r20 << 2);
    // 0x802C74CC: addu        $t7, $t7, $s4
    ctx->r15 = ADD32(ctx->r15, ctx->r20);
    // 0x802C74D0: sll         $t6, $t5, 4
    ctx->r14 = S32(ctx->r13 << 4);
    // 0x802C74D4: subu        $t6, $t6, $t5
    ctx->r14 = SUB32(ctx->r14, ctx->r13);
    // 0x802C74D8: sll         $t6, $t6, 2
    ctx->r14 = S32(ctx->r14 << 2);
    // 0x802C74DC: sll         $t7, $t7, 2
    ctx->r15 = S32(ctx->r15 << 2);
    // 0x802C74E0: addu        $t8, $t6, $t7
    ctx->r24 = ADD32(ctx->r14, ctx->r15);
    // 0x802C74E4: lui         $a1, 0x801C
    ctx->r5 = S32(0X801C << 16);
    // 0x802C74E8: addu        $a1, $a1, $t8
    ctx->r5 = ADD32(ctx->r5, ctx->r24);
    // 0x802C74EC: b           L_802C7540
    // 0x802C74F0: lw          $a1, 0x1FF4($a1)
    ctx->r5 = MEM_W(ctx->r5, 0X1FF4);
        goto L_802C7540;
    // 0x802C74F0: lw          $a1, 0x1FF4($a1)
    ctx->r5 = MEM_W(ctx->r5, 0X1FF4);
L_802C74F4:
    // 0x802C74F4: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x802C74F8: bne         $fp, $at, L_802C7520
    if (ctx->r30 != ctx->r1) {
        // 0x802C74FC: lw          $t9, 0xF0($sp)
        ctx->r25 = MEM_W(ctx->r29, 0XF0);
            goto L_802C7520;
    }
    // 0x802C74FC: lw          $t9, 0xF0($sp)
    ctx->r25 = MEM_W(ctx->r29, 0XF0);
    // 0x802C7500: lw          $t3, 0xF0($sp)
    ctx->r11 = MEM_W(ctx->r29, 0XF0);
    // 0x802C7504: lui         $a1, 0x801C
    ctx->r5 = S32(0X801C << 16);
    // 0x802C7508: sll         $t4, $t3, 2
    ctx->r12 = S32(ctx->r11 << 2);
    // 0x802C750C: addu        $t4, $t4, $t3
    ctx->r12 = ADD32(ctx->r12, ctx->r11);
    // 0x802C7510: sll         $t4, $t4, 2
    ctx->r12 = S32(ctx->r12 << 2);
    // 0x802C7514: addu        $a1, $a1, $t4
    ctx->r5 = ADD32(ctx->r5, ctx->r12);
    // 0x802C7518: b           L_802C7540
    // 0x802C751C: lw          $a1, 0x23B4($a1)
    ctx->r5 = MEM_W(ctx->r5, 0X23B4);
        goto L_802C7540;
    // 0x802C751C: lw          $a1, 0x23B4($a1)
    ctx->r5 = MEM_W(ctx->r5, 0X23B4);
L_802C7520:
    // 0x802C7520: sll         $t5, $t9, 2
    ctx->r13 = S32(ctx->r25 << 2);
    // 0x802C7524: subu        $t5, $t5, $t9
    ctx->r13 = SUB32(ctx->r13, ctx->r25);
    // 0x802C7528: sll         $t5, $t5, 4
    ctx->r13 = S32(ctx->r13 << 4);
    // 0x802C752C: sll         $t6, $s4, 4
    ctx->r14 = S32(ctx->r20 << 4);
    // 0x802C7530: addu        $t7, $t5, $t6
    ctx->r15 = ADD32(ctx->r13, ctx->r14);
    // 0x802C7534: lui         $a1, 0x801C
    ctx->r5 = S32(0X801C << 16);
    // 0x802C7538: addu        $a1, $a1, $t7
    ctx->r5 = ADD32(ctx->r5, ctx->r15);
    // 0x802C753C: lw          $a1, 0x26EC($a1)
    ctx->r5 = MEM_W(ctx->r5, 0X26EC);
L_802C7540:
    // 0x802C7540: addiu       $v1, $s1, 0x8
    ctx->r3 = ADD32(ctx->r17, 0X8);
    // 0x802C7544: sw          $s2, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r18;
    // 0x802C7548: sw          $t0, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r8;
    // 0x802C754C: sw          $t1, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r9;
    // 0x802C7550: sw          $s3, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r19;
    // 0x802C7554: lw          $t8, 0x0($s5)
    ctx->r24 = MEM_W(ctx->r21, 0X0);
    // 0x802C7558: addiu       $a0, $v1, 0x8
    ctx->r4 = ADD32(ctx->r3, 0X8);
    // 0x802C755C: sw          $t2, 0x78($sp)
    MEM_W(0X78, ctx->r29) = ctx->r10;
    // 0x802C7560: addu        $t3, $t8, $t2
    ctx->r11 = ADD32(ctx->r24, ctx->r10);
    // 0x802C7564: addiu       $t4, $t3, 0xC80
    ctx->r12 = ADD32(ctx->r11, 0XC80);
    // 0x802C7568: sw          $t4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r12;
    // 0x802C756C: sw          $t1, 0x7C($sp)
    MEM_W(0X7C, ctx->r29) = ctx->r9;
    // 0x802C7570: sw          $t0, 0x80($sp)
    MEM_W(0X80, ctx->r29) = ctx->r8;
    // 0x802C7574: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x802C7578: jal         0x801E4FE8
    // 0x802C757C: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_801E4FE8(rdram, ctx);
        goto after_8;
    // 0x802C757C: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_8:
    // 0x802C7580: lw          $t0, 0x80($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X80);
    // 0x802C7584: lw          $t1, 0x7C($sp)
    ctx->r9 = MEM_W(ctx->r29, 0X7C);
    // 0x802C7588: lw          $t2, 0x78($sp)
    ctx->r10 = MEM_W(ctx->r29, 0X78);
    // 0x802C758C: addiu       $s4, $s4, 0x1
    ctx->r20 = ADD32(ctx->r20, 0X1);
    // 0x802C7590: or          $s1, $v0, $zero
    ctx->r17 = ctx->r2 | 0;
    // 0x802C7594: addiu       $t0, $t0, 0x10
    ctx->r8 = ADD32(ctx->r8, 0X10);
    // 0x802C7598: addiu       $t1, $t1, 0x40
    ctx->r9 = ADD32(ctx->r9, 0X40);
    // 0x802C759C: bne         $s4, $s0, L_802C74B8
    if (ctx->r20 != ctx->r16) {
        // 0x802C75A0: addiu       $t2, $t2, 0xC0
        ctx->r10 = ADD32(ctx->r10, 0XC0);
            goto L_802C74B8;
    }
    // 0x802C75A0: addiu       $t2, $t2, 0xC0
    ctx->r10 = ADD32(ctx->r10, 0XC0);
L_802C75A4:
    // 0x802C75A4: lui         $s2, 0x380
    ctx->r18 = S32(0X380 << 16);
    // 0x802C75A8: lui         $s3, 0x102
    ctx->r19 = S32(0X102 << 16);
    // 0x802C75AC: lui         $s5, 0x801D
    ctx->r21 = S32(0X801D << 16);
    // 0x802C75B0: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x802C75B4: addiu       $s5, $s5, -0x1A08
    ctx->r21 = ADD32(ctx->r21, -0X1A08);
    // 0x802C75B8: ori         $s3, $s3, 0x40
    ctx->r19 = ctx->r19 | 0X40;
    // 0x802C75BC: bne         $fp, $at, L_802C7648
    if (ctx->r30 != ctx->r1) {
        // 0x802C75C0: ori         $s2, $s2, 0x10
        ctx->r18 = ctx->r18 | 0X10;
            goto L_802C7648;
    }
    // 0x802C75C0: ori         $s2, $s2, 0x10
    ctx->r18 = ctx->r18 | 0X10;
    // 0x802C75C4: lui         $t1, 0x700
    ctx->r9 = S32(0X700 << 16);
    // 0x802C75C8: addu        $v0, $s6, $s4
    ctx->r2 = ADD32(ctx->r22, ctx->r20);
    // 0x802C75CC: addiu       $t1, $t1, 0x0
    ctx->r9 = ADD32(ctx->r9, 0X0);
    // 0x802C75D0: sll         $t9, $v0, 4
    ctx->r25 = S32(ctx->r2 << 4);
    // 0x802C75D4: addu        $t5, $t1, $t9
    ctx->r13 = ADD32(ctx->r9, ctx->r25);
    // 0x802C75D8: addiu       $t6, $t5, 0x1280
    ctx->r14 = ADD32(ctx->r13, 0X1280);
    // 0x802C75DC: sll         $t7, $v0, 6
    ctx->r15 = S32(ctx->r2 << 6);
    // 0x802C75E0: sw          $t6, 0x4($s1)
    MEM_W(0X4, ctx->r17) = ctx->r14;
    // 0x802C75E4: addiu       $t0, $s1, 0x8
    ctx->r8 = ADD32(ctx->r17, 0X8);
    // 0x802C75E8: sw          $s2, 0x0($s1)
    MEM_W(0X0, ctx->r17) = ctx->r18;
    // 0x802C75EC: addu        $t8, $t1, $t7
    ctx->r24 = ADD32(ctx->r9, ctx->r15);
    // 0x802C75F0: addiu       $t3, $t8, 0xA80
    ctx->r11 = ADD32(ctx->r24, 0XA80);
    // 0x802C75F4: sw          $t3, 0x4($t0)
    MEM_W(0X4, ctx->r8) = ctx->r11;
    // 0x802C75F8: sw          $s3, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r19;
    // 0x802C75FC: lw          $t4, 0xF0($sp)
    ctx->r12 = MEM_W(ctx->r29, 0XF0);
    // 0x802C7600: lw          $t5, 0x0($s5)
    ctx->r13 = MEM_W(ctx->r21, 0X0);
    // 0x802C7604: sll         $t6, $v0, 2
    ctx->r14 = S32(ctx->r2 << 2);
    // 0x802C7608: subu        $t6, $t6, $v0
    ctx->r14 = SUB32(ctx->r14, ctx->r2);
    // 0x802C760C: sll         $t9, $t4, 2
    ctx->r25 = S32(ctx->r12 << 2);
    // 0x802C7610: sll         $t6, $t6, 6
    ctx->r14 = S32(ctx->r14 << 6);
    // 0x802C7614: addu        $t9, $t9, $t4
    ctx->r25 = ADD32(ctx->r25, ctx->r12);
    // 0x802C7618: sll         $t9, $t9, 2
    ctx->r25 = S32(ctx->r25 << 2);
    // 0x802C761C: lui         $a1, 0x801C
    ctx->r5 = S32(0X801C << 16);
    // 0x802C7620: addu        $t7, $t5, $t6
    ctx->r15 = ADD32(ctx->r13, ctx->r14);
    // 0x802C7624: addiu       $t8, $t7, 0xC80
    ctx->r24 = ADD32(ctx->r15, 0XC80);
    // 0x802C7628: addu        $a1, $a1, $t9
    ctx->r5 = ADD32(ctx->r5, ctx->r25);
    // 0x802C762C: addiu       $a0, $t0, 0x8
    ctx->r4 = ADD32(ctx->r8, 0X8);
    // 0x802C7630: lw          $a1, 0x22C4($a1)
    ctx->r5 = MEM_W(ctx->r5, 0X22C4);
    // 0x802C7634: sw          $t8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r24;
    // 0x802C7638: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x802C763C: jal         0x801E4FE8
    // 0x802C7640: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_801E4FE8(rdram, ctx);
        goto after_9;
    // 0x802C7640: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_9:
    // 0x802C7644: or          $s1, $v0, $zero
    ctx->r17 = ctx->r2 | 0;
L_802C7648:
    // 0x802C7648: addiu       $t3, $zero, 0xFF
    ctx->r11 = ADD32(0, 0XFF);
    // 0x802C764C: addiu       $t4, $zero, 0xFF
    ctx->r12 = ADD32(0, 0XFF);
    // 0x802C7650: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C7654: addiu       $t5, $zero, 0xFF
    ctx->r13 = ADD32(0, 0XFF);
    // 0x802C7658: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C765C: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C7660: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C7664: sw          $t8, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r24;
    // 0x802C7668: sw          $t7, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r15;
    // 0x802C766C: sw          $t6, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r14;
    // 0x802C7670: sw          $t5, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r13;
    // 0x802C7674: sw          $t9, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r25;
    // 0x802C7678: sw          $t9, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r25;
    // 0x802C767C: sw          $t4, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r12;
    // 0x802C7680: sw          $t4, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r12;
    // 0x802C7684: sw          $t3, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r11;
    // 0x802C7688: sw          $t3, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r11;
    // 0x802C768C: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    // 0x802C7690: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C7694: addiu       $a2, $zero, 0xFF
    ctx->r6 = ADD32(0, 0XFF);
    // 0x802C7698: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    // 0x802C769C: jal         0x801E946C
    // 0x802C76A0: or          $s4, $zero, $zero
    ctx->r20 = 0 | 0;
    func_801E946C(rdram, ctx);
        goto after_10;
    // 0x802C76A0: or          $s4, $zero, $zero
    ctx->r20 = 0 | 0;
    after_10:
    // 0x802C76A4: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x802C76A8: bne         $fp, $at, L_802C76E0
    if (ctx->r30 != ctx->r1) {
        // 0x802C76AC: or          $s1, $v0, $zero
        ctx->r17 = ctx->r2 | 0;
            goto L_802C76E0;
    }
    // 0x802C76AC: or          $s1, $v0, $zero
    ctx->r17 = ctx->r2 | 0;
    // 0x802C76B0: lw          $t5, 0xFC($sp)
    ctx->r13 = MEM_W(ctx->r29, 0XFC);
    // 0x802C76B4: addiu       $t7, $zero, 0x2
    ctx->r15 = ADD32(0, 0X2);
    // 0x802C76B8: sw          $t7, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r15;
    // 0x802C76BC: addiu       $t6, $t5, 0x4A
    ctx->r14 = ADD32(ctx->r13, 0X4A);
    // 0x802C76C0: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x802C76C4: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C76C8: addiu       $a1, $zero, 0x3
    ctx->r5 = ADD32(0, 0X3);
    // 0x802C76CC: addiu       $a2, $zero, 0x5
    ctx->r6 = ADD32(0, 0X5);
    // 0x802C76D0: jal         0x801E3EE0
    // 0x802C76D4: addiu       $a3, $s7, 0x71
    ctx->r7 = ADD32(ctx->r23, 0X71);
    func_801E3EE0(rdram, ctx);
        goto after_11;
    // 0x802C76D4: addiu       $a3, $s7, 0x71
    ctx->r7 = ADD32(ctx->r23, 0X71);
    after_11:
    // 0x802C76D8: b           L_802C7744
    // 0x802C76DC: or          $s1, $v0, $zero
    ctx->r17 = ctx->r2 | 0;
        goto L_802C7744;
    // 0x802C76DC: or          $s1, $v0, $zero
    ctx->r17 = ctx->r2 | 0;
L_802C76E0:
    // 0x802C76E0: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x802C76E4: bne         $fp, $at, L_802C771C
    if (ctx->r30 != ctx->r1) {
        // 0x802C76E8: or          $a0, $s1, $zero
        ctx->r4 = ctx->r17 | 0;
            goto L_802C771C;
    }
    // 0x802C76E8: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    // 0x802C76EC: lw          $t8, 0xFC($sp)
    ctx->r24 = MEM_W(ctx->r29, 0XFC);
    // 0x802C76F0: addiu       $t4, $zero, 0x2
    ctx->r12 = ADD32(0, 0X2);
    // 0x802C76F4: sw          $t4, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r12;
    // 0x802C76F8: addiu       $t3, $t8, 0x4A
    ctx->r11 = ADD32(ctx->r24, 0X4A);
    // 0x802C76FC: sw          $t3, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r11;
    // 0x802C7700: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    // 0x802C7704: addiu       $a1, $zero, 0x3
    ctx->r5 = ADD32(0, 0X3);
    // 0x802C7708: addiu       $a2, $zero, 0x20
    ctx->r6 = ADD32(0, 0X20);
    // 0x802C770C: jal         0x801E3EE0
    // 0x802C7710: addiu       $a3, $s7, 0x67
    ctx->r7 = ADD32(ctx->r23, 0X67);
    func_801E3EE0(rdram, ctx);
        goto after_12;
    // 0x802C7710: addiu       $a3, $s7, 0x67
    ctx->r7 = ADD32(ctx->r23, 0X67);
    after_12:
    // 0x802C7714: b           L_802C7744
    // 0x802C7718: or          $s1, $v0, $zero
    ctx->r17 = ctx->r2 | 0;
        goto L_802C7744;
    // 0x802C7718: or          $s1, $v0, $zero
    ctx->r17 = ctx->r2 | 0;
L_802C771C:
    // 0x802C771C: lw          $t9, 0xFC($sp)
    ctx->r25 = MEM_W(ctx->r29, 0XFC);
    // 0x802C7720: addiu       $t6, $zero, 0x2
    ctx->r14 = ADD32(0, 0X2);
    // 0x802C7724: sw          $t6, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r14;
    // 0x802C7728: addiu       $t5, $t9, 0x4A
    ctx->r13 = ADD32(ctx->r25, 0X4A);
    // 0x802C772C: sw          $t5, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r13;
    // 0x802C7730: addiu       $a1, $zero, 0x3
    ctx->r5 = ADD32(0, 0X3);
    // 0x802C7734: addiu       $a2, $zero, 0x4
    ctx->r6 = ADD32(0, 0X4);
    // 0x802C7738: jal         0x801E3EE0
    // 0x802C773C: addiu       $a3, $s7, 0x67
    ctx->r7 = ADD32(ctx->r23, 0X67);
    func_801E3EE0(rdram, ctx);
        goto after_13;
    // 0x802C773C: addiu       $a3, $s7, 0x67
    ctx->r7 = ADD32(ctx->r23, 0X67);
    after_13:
    // 0x802C7740: or          $s1, $v0, $zero
    ctx->r17 = ctx->r2 | 0;
L_802C7744:
    // 0x802C7744: lw          $s0, 0xFC($sp)
    ctx->r16 = MEM_W(ctx->r29, 0XFC);
    // 0x802C7748: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    // 0x802C774C: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C7750: addiu       $s0, $s0, 0x6B
    ctx->r16 = ADD32(ctx->r16, 0X6B);
    // 0x802C7754: sw          $s0, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r16;
    // 0x802C7758: addiu       $a2, $zero, 0x1F
    ctx->r6 = ADD32(0, 0X1F);
    // 0x802C775C: addiu       $a3, $s7, 0x2B
    ctx->r7 = ADD32(ctx->r23, 0X2B);
    // 0x802C7760: jal         0x801E3EE0
    // 0x802C7764: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    func_801E3EE0(rdram, ctx);
        goto after_14;
    // 0x802C7764: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    after_14:
    // 0x802C7768: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x802C776C: beq         $fp, $at, L_802C7780
    if (ctx->r30 == ctx->r1) {
        // 0x802C7770: or          $s1, $v0, $zero
        ctx->r17 = ctx->r2 | 0;
            goto L_802C7780;
    }
    // 0x802C7770: or          $s1, $v0, $zero
    ctx->r17 = ctx->r2 | 0;
    // 0x802C7774: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x802C7778: bne         $fp, $at, L_802C77E8
    if (ctx->r30 != ctx->r1) {
        // 0x802C777C: addiu       $s2, $zero, 0x3E
        ctx->r18 = ADD32(0, 0X3E);
            goto L_802C77E8;
    }
    // 0x802C777C: addiu       $s2, $zero, 0x3E
    ctx->r18 = ADD32(0, 0X3E);
L_802C7780:
    // 0x802C7780: addiu       $s2, $zero, 0x3
    ctx->r18 = ADD32(0, 0X3);
    // 0x802C7784: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    // 0x802C7788: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C778C: addiu       $a2, $zero, 0x11
    ctx->r6 = ADD32(0, 0X11);
    // 0x802C7790: addiu       $a3, $s7, 0x5F
    ctx->r7 = ADD32(ctx->r23, 0X5F);
    // 0x802C7794: sw          $s0, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r16;
    // 0x802C7798: jal         0x801E3EE0
    // 0x802C779C: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    func_801E3EE0(rdram, ctx);
        goto after_15;
    // 0x802C779C: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    after_15:
    // 0x802C77A0: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C77A4: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C77A8: addiu       $a2, $zero, 0x20
    ctx->r6 = ADD32(0, 0X20);
    // 0x802C77AC: addiu       $a3, $s7, 0x108
    ctx->r7 = ADD32(ctx->r23, 0X108);
    // 0x802C77B0: sw          $s0, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r16;
    // 0x802C77B4: jal         0x801E3EE0
    // 0x802C77B8: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    func_801E3EE0(rdram, ctx);
        goto after_16;
    // 0x802C77B8: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    after_16:
    // 0x802C77BC: lw          $t7, 0xFC($sp)
    ctx->r15 = MEM_W(ctx->r29, 0XFC);
    // 0x802C77C0: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C77C4: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C77C8: addiu       $t8, $t7, 0xB8
    ctx->r24 = ADD32(ctx->r15, 0XB8);
    // 0x802C77CC: sw          $t8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r24;
    // 0x802C77D0: addiu       $a2, $zero, 0xD
    ctx->r6 = ADD32(0, 0XD);
    // 0x802C77D4: lw          $a3, 0x88($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X88);
    // 0x802C77D8: jal         0x801E3EE0
    // 0x802C77DC: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    func_801E3EE0(rdram, ctx);
        goto after_17;
    // 0x802C77DC: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    after_17:
    // 0x802C77E0: b           L_802C7808
    // 0x802C77E4: or          $s1, $v0, $zero
    ctx->r17 = ctx->r2 | 0;
        goto L_802C7808;
    // 0x802C77E4: or          $s1, $v0, $zero
    ctx->r17 = ctx->r2 | 0;
L_802C77E8:
    // 0x802C77E8: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    // 0x802C77EC: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C77F0: addiu       $a2, $zero, 0x20
    ctx->r6 = ADD32(0, 0X20);
    // 0x802C77F4: addiu       $a3, $s7, 0xBF
    ctx->r7 = ADD32(ctx->r23, 0XBF);
    // 0x802C77F8: sw          $s0, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r16;
    // 0x802C77FC: jal         0x801E3EE0
    // 0x802C7800: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    func_801E3EE0(rdram, ctx);
        goto after_18;
    // 0x802C7800: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    after_18:
    // 0x802C7804: or          $s1, $v0, $zero
    ctx->r17 = ctx->r2 | 0;
L_802C7808:
    // 0x802C7808: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    // 0x802C780C: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C7810: or          $a2, $s2, $zero
    ctx->r6 = ctx->r18 | 0;
    // 0x802C7814: addiu       $a3, $s7, 0x156
    ctx->r7 = ADD32(ctx->r23, 0X156);
    // 0x802C7818: sw          $s0, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r16;
    // 0x802C781C: jal         0x801E3EE0
    // 0x802C7820: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    func_801E3EE0(rdram, ctx);
        goto after_19;
    // 0x802C7820: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    after_19:
    // 0x802C7824: lw          $t3, 0xFC($sp)
    ctx->r11 = MEM_W(ctx->r29, 0XFC);
    // 0x802C7828: or          $s1, $v0, $zero
    ctx->r17 = ctx->r2 | 0;
    // 0x802C782C: addiu       $v0, $zero, 0x3
    ctx->r2 = ADD32(0, 0X3);
    // 0x802C7830: addiu       $s6, $sp, 0xB4
    ctx->r22 = ADD32(ctx->r29, 0XB4);
    // 0x802C7834: sw          $t3, 0x84($sp)
    MEM_W(0X84, ctx->r29) = ctx->r11;
    // 0x802C7838: addiu       $s3, $t3, 0x80
    ctx->r19 = ADD32(ctx->r11, 0X80);
L_802C783C:
    // 0x802C783C: lui         $t4, 0x802D
    ctx->r12 = S32(0X802D << 16);
    // 0x802C7840: lw          $t4, -0x7E5C($t4)
    ctx->r12 = MEM_W(ctx->r12, -0X7E5C);
    // 0x802C7844: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    // 0x802C7848: addiu       $a2, $zero, 0x80
    ctx->r6 = ADD32(0, 0X80);
    // 0x802C784C: beq         $t4, $zero, L_802C78A4
    if (ctx->r12 == 0) {
        // 0x802C7850: addiu       $a3, $zero, 0x80
        ctx->r7 = ADD32(0, 0X80);
            goto L_802C78A4;
    }
    // 0x802C7850: addiu       $a3, $zero, 0x80
    ctx->r7 = ADD32(0, 0X80);
    // 0x802C7854: lw          $t5, 0xF0($sp)
    ctx->r13 = MEM_W(ctx->r29, 0XF0);
    // 0x802C7858: lui         $t7, 0x801C
    ctx->r15 = S32(0X801C << 16);
    // 0x802C785C: addiu       $t9, $s4, 0x1
    ctx->r25 = ADD32(ctx->r20, 0X1);
    // 0x802C7860: sll         $t6, $t5, 2
    ctx->r14 = S32(ctx->r13 << 2);
    // 0x802C7864: addu        $t7, $t7, $t6
    ctx->r15 = ADD32(ctx->r15, ctx->r14);
    // 0x802C7868: lw          $t7, 0x2660($t7)
    ctx->r15 = MEM_W(ctx->r15, 0X2660);
    // 0x802C786C: bne         $t9, $t7, L_802C787C
    if (ctx->r25 != ctx->r15) {
        // 0x802C7870: nop
    
            goto L_802C787C;
    }
    // 0x802C7870: nop

    // 0x802C7874: b           L_802C78C4
    // 0x802C7878: addiu       $a1, $zero, 0x6
    ctx->r5 = ADD32(0, 0X6);
        goto L_802C78C4;
    // 0x802C7878: addiu       $a1, $zero, 0x6
    ctx->r5 = ADD32(0, 0X6);
L_802C787C:
    // 0x802C787C: bne         $fp, $v0, L_802C789C
    if (ctx->r30 != ctx->r2) {
        // 0x802C7880: nop
    
            goto L_802C789C;
    }
    // 0x802C7880: nop

    // 0x802C7884: bne         $s4, $zero, L_802C7894
    if (ctx->r20 != 0) {
        // 0x802C7888: nop
    
            goto L_802C7894;
    }
    // 0x802C7888: nop

    // 0x802C788C: b           L_802C78C4
    // 0x802C7890: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
        goto L_802C78C4;
    // 0x802C7890: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
L_802C7894:
    // 0x802C7894: b           L_802C78C4
    // 0x802C7898: addiu       $a1, $zero, 0x7
    ctx->r5 = ADD32(0, 0X7);
        goto L_802C78C4;
    // 0x802C7898: addiu       $a1, $zero, 0x7
    ctx->r5 = ADD32(0, 0X7);
L_802C789C:
    // 0x802C789C: b           L_802C78C4
    // 0x802C78A0: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
        goto L_802C78C4;
    // 0x802C78A0: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
L_802C78A4:
    // 0x802C78A4: bne         $fp, $v0, L_802C78C4
    if (ctx->r30 != ctx->r2) {
        // 0x802C78A8: or          $a1, $zero, $zero
        ctx->r5 = 0 | 0;
            goto L_802C78C4;
    }
    // 0x802C78A8: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C78AC: bne         $s4, $zero, L_802C78BC
    if (ctx->r20 != 0) {
        // 0x802C78B0: nop
    
            goto L_802C78BC;
    }
    // 0x802C78B0: nop

    // 0x802C78B4: b           L_802C78C4
    // 0x802C78B8: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
        goto L_802C78C4;
    // 0x802C78B8: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
L_802C78BC:
    // 0x802C78BC: b           L_802C78C4
    // 0x802C78C0: addiu       $a1, $zero, 0x7
    ctx->r5 = ADD32(0, 0X7);
        goto L_802C78C4;
    // 0x802C78C0: addiu       $a1, $zero, 0x7
    ctx->r5 = ADD32(0, 0X7);
L_802C78C4:
    // 0x802C78C4: addiu       $t8, $zero, 0x80
    ctx->r24 = ADD32(0, 0X80);
    // 0x802C78C8: sw          $t8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r24;
    // 0x802C78CC: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C78D0: addiu       $t3, $zero, 0xFF
    ctx->r11 = ADD32(0, 0XFF);
    // 0x802C78D4: addiu       $t4, $zero, 0xFF
    ctx->r12 = ADD32(0, 0XFF);
    // 0x802C78D8: addiu       $t5, $zero, 0xFF
    ctx->r13 = ADD32(0, 0XFF);
    // 0x802C78DC: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C78E0: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C78E4: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C78E8: sw          $t7, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r15;
    // 0x802C78EC: sw          $t9, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r25;
    // 0x802C78F0: sw          $t6, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r14;
    // 0x802C78F4: sw          $t5, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r13;
    // 0x802C78F8: sw          $t4, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r12;
    // 0x802C78FC: sw          $t4, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r12;
    // 0x802C7900: sw          $t3, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r11;
    // 0x802C7904: sw          $t3, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r11;
    // 0x802C7908: jal         0x801E946C
    // 0x802C790C: sw          $t8, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r24;
    func_801E946C(rdram, ctx);
        goto after_20;
    // 0x802C790C: sw          $t8, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r24;
    after_20:
    // 0x802C7910: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x802C7914: bne         $fp, $at, L_802C79D8
    if (ctx->r30 != ctx->r1) {
        // 0x802C7918: or          $s1, $v0, $zero
        ctx->r17 = ctx->r2 | 0;
            goto L_802C79D8;
    }
    // 0x802C7918: or          $s1, $v0, $zero
    ctx->r17 = ctx->r2 | 0;
    // 0x802C791C: lw          $t5, 0xF0($sp)
    ctx->r13 = MEM_W(ctx->r29, 0XF0);
    // 0x802C7920: sll         $t9, $s4, 2
    ctx->r25 = S32(ctx->r20 << 2);
    // 0x802C7924: addu        $t9, $t9, $s4
    ctx->r25 = ADD32(ctx->r25, ctx->r20);
    // 0x802C7928: sll         $t6, $t5, 4
    ctx->r14 = S32(ctx->r13 << 4);
    // 0x802C792C: subu        $t6, $t6, $t5
    ctx->r14 = SUB32(ctx->r14, ctx->r13);
    // 0x802C7930: sll         $t6, $t6, 2
    ctx->r14 = S32(ctx->r14 << 2);
    // 0x802C7934: sll         $t9, $t9, 2
    ctx->r25 = S32(ctx->r25 << 2);
    // 0x802C7938: lui         $t8, 0x801C
    ctx->r24 = S32(0X801C << 16);
    // 0x802C793C: lw          $t4, 0x84($sp)
    ctx->r12 = MEM_W(ctx->r29, 0X84);
    // 0x802C7940: addiu       $t8, $t8, 0x1FF0
    ctx->r24 = ADD32(ctx->r24, 0X1FF0);
    // 0x802C7944: addu        $t7, $t6, $t9
    ctx->r15 = ADD32(ctx->r14, ctx->r25);
    // 0x802C7948: addu        $v1, $t7, $t8
    ctx->r3 = ADD32(ctx->r15, ctx->r24);
    // 0x802C794C: lw          $t3, 0x8($v1)
    ctx->r11 = MEM_W(ctx->r3, 0X8);
    // 0x802C7950: addiu       $t5, $t4, 0x81
    ctx->r13 = ADD32(ctx->r12, 0X81);
    // 0x802C7954: sw          $t5, 0x70($sp)
    MEM_W(0X70, ctx->r29) = ctx->r13;
    // 0x802C7958: lw          $a2, 0x0($v1)
    ctx->r6 = MEM_W(ctx->r3, 0X0);
    // 0x802C795C: addiu       $s0, $v1, 0x10
    ctx->r16 = ADD32(ctx->r3, 0X10);
    // 0x802C7960: sw          $v1, 0x88($sp)
    MEM_W(0X88, ctx->r29) = ctx->r3;
    // 0x802C7964: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C7968: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C796C: addiu       $a3, $s7, 0x13F
    ctx->r7 = ADD32(ctx->r23, 0X13F);
    // 0x802C7970: sw          $s3, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r19;
    // 0x802C7974: addiu       $s5, $s7, 0x5F
    ctx->r21 = ADD32(ctx->r23, 0X5F);
    // 0x802C7978: addiu       $s2, $s7, 0x108
    ctx->r18 = ADD32(ctx->r23, 0X108);
    // 0x802C797C: jal         0x801E8B24
    // 0x802C7980: sw          $t3, 0xD8($sp)
    MEM_W(0XD8, ctx->r29) = ctx->r11;
    func_801E8B24(rdram, ctx);
        goto after_21;
    // 0x802C7980: sw          $t3, 0xD8($sp)
    MEM_W(0XD8, ctx->r29) = ctx->r11;
    after_21:
    // 0x802C7984: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C7988: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C798C: or          $a2, $s0, $zero
    ctx->r6 = ctx->r16 | 0;
    // 0x802C7990: or          $a3, $s2, $zero
    ctx->r7 = ctx->r18 | 0;
    // 0x802C7994: jal         0x801E9858
    // 0x802C7998: sw          $s3, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r19;
    func_801E9858(rdram, ctx);
        goto after_22;
    // 0x802C7998: sw          $s3, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r19;
    after_22:
    // 0x802C799C: lw          $v1, 0x88($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X88);
    // 0x802C79A0: lw          $t7, 0x70($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X70);
    // 0x802C79A4: lui         $a2, 0x802D
    ctx->r6 = S32(0X802D << 16);
    // 0x802C79A8: lw          $t6, 0xC($v1)
    ctx->r14 = MEM_W(ctx->r3, 0XC);
    // 0x802C79AC: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C79B0: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C79B4: sll         $t9, $t6, 2
    ctx->r25 = S32(ctx->r14 << 2);
    // 0x802C79B8: addu        $a2, $a2, $t9
    ctx->r6 = ADD32(ctx->r6, ctx->r25);
    // 0x802C79BC: lw          $a2, -0x7E68($a2)
    ctx->r6 = MEM_W(ctx->r6, -0X7E68);
    // 0x802C79C0: or          $a3, $s5, $zero
    ctx->r7 = ctx->r21 | 0;
    // 0x802C79C4: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    // 0x802C79C8: jal         0x801E3EE0
    // 0x802C79CC: sw          $t7, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r15;
    func_801E3EE0(rdram, ctx);
        goto after_23;
    // 0x802C79CC: sw          $t7, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r15;
    after_23:
    // 0x802C79D0: b           L_802C7B30
    // 0x802C79D4: or          $s1, $v0, $zero
    ctx->r17 = ctx->r2 | 0;
        goto L_802C7B30;
    // 0x802C79D4: or          $s1, $v0, $zero
    ctx->r17 = ctx->r2 | 0;
L_802C79D8:
    // 0x802C79D8: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x802C79DC: bne         $fp, $at, L_802C7AC8
    if (ctx->r30 != ctx->r1) {
        // 0x802C79E0: lw          $t3, 0xF0($sp)
        ctx->r11 = MEM_W(ctx->r29, 0XF0);
            goto L_802C7AC8;
    }
    // 0x802C79E0: lw          $t3, 0xF0($sp)
    ctx->r11 = MEM_W(ctx->r29, 0XF0);
    // 0x802C79E4: lw          $t8, 0xF0($sp)
    ctx->r24 = MEM_W(ctx->r29, 0XF0);
    // 0x802C79E8: lui         $t4, 0x801C
    ctx->r12 = S32(0X801C << 16);
    // 0x802C79EC: lw          $t9, 0x84($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X84);
    // 0x802C79F0: sll         $t3, $t8, 2
    ctx->r11 = S32(ctx->r24 << 2);
    // 0x802C79F4: addu        $t3, $t3, $t8
    ctx->r11 = ADD32(ctx->r11, ctx->r24);
    // 0x802C79F8: sll         $t3, $t3, 2
    ctx->r11 = S32(ctx->r11 << 2);
    // 0x802C79FC: addiu       $t4, $t4, 0x23B0
    ctx->r12 = ADD32(ctx->r12, 0X23B0);
    // 0x802C7A00: addu        $v0, $t3, $t4
    ctx->r2 = ADD32(ctx->r11, ctx->r12);
    // 0x802C7A04: lw          $t5, 0x8($v0)
    ctx->r13 = MEM_W(ctx->r2, 0X8);
    // 0x802C7A08: addiu       $t6, $s7, 0x13F
    ctx->r14 = ADD32(ctx->r23, 0X13F);
    // 0x802C7A0C: addiu       $t7, $t9, 0x81
    ctx->r15 = ADD32(ctx->r25, 0X81);
    // 0x802C7A10: sw          $t7, 0x70($sp)
    MEM_W(0X70, ctx->r29) = ctx->r15;
    // 0x802C7A14: sw          $t6, 0x74($sp)
    MEM_W(0X74, ctx->r29) = ctx->r14;
    // 0x802C7A18: addiu       $s5, $s7, 0x5F
    ctx->r21 = ADD32(ctx->r23, 0X5F);
    // 0x802C7A1C: addiu       $s2, $s7, 0x108
    ctx->r18 = ADD32(ctx->r23, 0X108);
    // 0x802C7A20: bne         $s4, $zero, L_802C7A64
    if (ctx->r20 != 0) {
        // 0x802C7A24: sw          $t5, 0xD8($sp)
        MEM_W(0XD8, ctx->r29) = ctx->r13;
            goto L_802C7A64;
    }
    // 0x802C7A24: sw          $t5, 0xD8($sp)
    MEM_W(0XD8, ctx->r29) = ctx->r13;
    // 0x802C7A28: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    // 0x802C7A2C: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C7A30: lw          $a2, 0x0($v0)
    ctx->r6 = MEM_W(ctx->r2, 0X0);
    // 0x802C7A34: or          $a3, $t6, $zero
    ctx->r7 = ctx->r14 | 0;
    // 0x802C7A38: sw          $s3, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r19;
    // 0x802C7A3C: jal         0x801E8B24
    // 0x802C7A40: addiu       $s0, $v0, 0x10
    ctx->r16 = ADD32(ctx->r2, 0X10);
    func_801E8B24(rdram, ctx);
        goto after_24;
    // 0x802C7A40: addiu       $s0, $v0, 0x10
    ctx->r16 = ADD32(ctx->r2, 0X10);
    after_24:
    // 0x802C7A44: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C7A48: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C7A4C: or          $a2, $s0, $zero
    ctx->r6 = ctx->r16 | 0;
    // 0x802C7A50: or          $a3, $s2, $zero
    ctx->r7 = ctx->r18 | 0;
    // 0x802C7A54: jal         0x801E9858
    // 0x802C7A58: sw          $s3, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r19;
    func_801E9858(rdram, ctx);
        goto after_25;
    // 0x802C7A58: sw          $s3, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r19;
    after_25:
    // 0x802C7A5C: b           L_802C7AA0
    // 0x802C7A60: or          $s1, $v0, $zero
    ctx->r17 = ctx->r2 | 0;
        goto L_802C7AA0;
    // 0x802C7A60: or          $s1, $v0, $zero
    ctx->r17 = ctx->r2 | 0;
L_802C7A64:
    // 0x802C7A64: lui         $a2, 0x802D
    ctx->r6 = S32(0X802D << 16);
    // 0x802C7A68: addiu       $a2, $a2, -0x7E40
    ctx->r6 = ADD32(ctx->r6, -0X7E40);
    // 0x802C7A6C: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    // 0x802C7A70: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C7A74: lw          $a3, 0x74($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X74);
    // 0x802C7A78: jal         0x801E9858
    // 0x802C7A7C: sw          $s3, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r19;
    func_801E9858(rdram, ctx);
        goto after_26;
    // 0x802C7A7C: sw          $s3, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r19;
    after_26:
    // 0x802C7A80: lui         $a2, 0x802D
    ctx->r6 = S32(0X802D << 16);
    // 0x802C7A84: addiu       $a2, $a2, -0x7E34
    ctx->r6 = ADD32(ctx->r6, -0X7E34);
    // 0x802C7A88: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C7A8C: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C7A90: or          $a3, $s2, $zero
    ctx->r7 = ctx->r18 | 0;
    // 0x802C7A94: jal         0x801E9858
    // 0x802C7A98: sw          $s3, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r19;
    func_801E9858(rdram, ctx);
        goto after_27;
    // 0x802C7A98: sw          $s3, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r19;
    after_27:
    // 0x802C7A9C: or          $s1, $v0, $zero
    ctx->r17 = ctx->r2 | 0;
L_802C7AA0:
    // 0x802C7AA0: lw          $t8, 0x70($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X70);
    // 0x802C7AA4: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    // 0x802C7AA8: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C7AAC: addiu       $a2, $zero, 0x24
    ctx->r6 = ADD32(0, 0X24);
    // 0x802C7AB0: or          $a3, $s5, $zero
    ctx->r7 = ctx->r21 | 0;
    // 0x802C7AB4: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    // 0x802C7AB8: jal         0x801E3EE0
    // 0x802C7ABC: sw          $t8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r24;
    func_801E3EE0(rdram, ctx);
        goto after_28;
    // 0x802C7ABC: sw          $t8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r24;
    after_28:
    // 0x802C7AC0: b           L_802C7B30
    // 0x802C7AC4: or          $s1, $v0, $zero
    ctx->r17 = ctx->r2 | 0;
        goto L_802C7B30;
    // 0x802C7AC4: or          $s1, $v0, $zero
    ctx->r17 = ctx->r2 | 0;
L_802C7AC8:
    // 0x802C7AC8: sll         $t4, $t3, 2
    ctx->r12 = S32(ctx->r11 << 2);
    // 0x802C7ACC: subu        $t4, $t4, $t3
    ctx->r12 = SUB32(ctx->r12, ctx->r11);
    // 0x802C7AD0: sll         $t4, $t4, 4
    ctx->r12 = S32(ctx->r12 << 4);
    // 0x802C7AD4: sll         $t5, $s4, 4
    ctx->r13 = S32(ctx->r20 << 4);
    // 0x802C7AD8: lui         $t9, 0x801C
    ctx->r25 = S32(0X801C << 16);
    // 0x802C7ADC: addiu       $t9, $t9, 0x26E8
    ctx->r25 = ADD32(ctx->r25, 0X26E8);
    // 0x802C7AE0: addu        $t6, $t4, $t5
    ctx->r14 = ADD32(ctx->r12, ctx->r13);
    // 0x802C7AE4: addu        $v0, $t6, $t9
    ctx->r2 = ADD32(ctx->r14, ctx->r25);
    // 0x802C7AE8: lw          $t7, 0x8($v0)
    ctx->r15 = MEM_W(ctx->r2, 0X8);
    // 0x802C7AEC: addiu       $t8, $v0, 0xC
    ctx->r24 = ADD32(ctx->r2, 0XC);
    // 0x802C7AF0: sw          $t8, 0x7C($sp)
    MEM_W(0X7C, ctx->r29) = ctx->r24;
    // 0x802C7AF4: lw          $a2, 0x0($v0)
    ctx->r6 = MEM_W(ctx->r2, 0X0);
    // 0x802C7AF8: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    // 0x802C7AFC: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C7B00: addiu       $a3, $s7, 0x14C
    ctx->r7 = ADD32(ctx->r23, 0X14C);
    // 0x802C7B04: sw          $s3, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r19;
    // 0x802C7B08: addiu       $s0, $s7, 0xBF
    ctx->r16 = ADD32(ctx->r23, 0XBF);
    // 0x802C7B0C: jal         0x80094200
    // 0x802C7B10: sw          $t7, 0xD8($sp)
    MEM_W(0XD8, ctx->r29) = ctx->r15;
    func_80094200(rdram, ctx);
        goto after_29;
    // 0x802C7B10: sw          $t7, 0xD8($sp)
    MEM_W(0XD8, ctx->r29) = ctx->r15;
    after_29:
    // 0x802C7B14: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C7B18: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C7B1C: lw          $a2, 0x7C($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X7C);
    // 0x802C7B20: or          $a3, $s0, $zero
    ctx->r7 = ctx->r16 | 0;
    // 0x802C7B24: jal         0x801E9858
    // 0x802C7B28: sw          $s3, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r19;
    func_801E9858(rdram, ctx);
        goto after_30;
    // 0x802C7B28: sw          $s3, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r19;
    after_30:
    // 0x802C7B2C: or          $s1, $v0, $zero
    ctx->r17 = ctx->r2 | 0;
L_802C7B30:
    // 0x802C7B30: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x802C7B34: bne         $fp, $at, L_802C7B80
    if (ctx->r30 != ctx->r1) {
        // 0x802C7B38: or          $a0, $s6, $zero
        ctx->r4 = ctx->r22 | 0;
            goto L_802C7B80;
    }
    // 0x802C7B38: or          $a0, $s6, $zero
    ctx->r4 = ctx->r22 | 0;
    // 0x802C7B3C: bne         $s4, $zero, L_802C7B64
    if (ctx->r20 != 0) {
        // 0x802C7B40: or          $a0, $s6, $zero
        ctx->r4 = ctx->r22 | 0;
            goto L_802C7B64;
    }
    // 0x802C7B40: or          $a0, $s6, $zero
    ctx->r4 = ctx->r22 | 0;
    // 0x802C7B44: lui         $a1, 0x802D
    ctx->r5 = S32(0X802D << 16);
    // 0x802C7B48: addiu       $s0, $s4, 0x1
    ctx->r16 = ADD32(ctx->r20, 0X1);
    // 0x802C7B4C: or          $a2, $s0, $zero
    ctx->r6 = ctx->r16 | 0;
    // 0x802C7B50: addiu       $a1, $a1, -0x7E30
    ctx->r5 = ADD32(ctx->r5, -0X7E30);
    // 0x802C7B54: jal         0x800CA210
    // 0x802C7B58: or          $a0, $s6, $zero
    ctx->r4 = ctx->r22 | 0;
    func_800CA210(rdram, ctx);
        goto after_31;
    // 0x802C7B58: or          $a0, $s6, $zero
    ctx->r4 = ctx->r22 | 0;
    after_31:
    // 0x802C7B5C: b           L_802C7B98
    // 0x802C7B60: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
        goto L_802C7B98;
    // 0x802C7B60: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
L_802C7B64:
    // 0x802C7B64: lui         $a1, 0x802D
    ctx->r5 = S32(0X802D << 16);
    // 0x802C7B68: addiu       $s0, $s4, 0x1
    ctx->r16 = ADD32(ctx->r20, 0X1);
    // 0x802C7B6C: or          $a2, $s0, $zero
    ctx->r6 = ctx->r16 | 0;
    // 0x802C7B70: jal         0x800CA210
    // 0x802C7B74: addiu       $a1, $a1, -0x7E2C
    ctx->r5 = ADD32(ctx->r5, -0X7E2C);
    func_800CA210(rdram, ctx);
        goto after_32;
    // 0x802C7B74: addiu       $a1, $a1, -0x7E2C
    ctx->r5 = ADD32(ctx->r5, -0X7E2C);
    after_32:
    // 0x802C7B78: b           L_802C7B98
    // 0x802C7B7C: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
        goto L_802C7B98;
    // 0x802C7B7C: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
L_802C7B80:
    // 0x802C7B80: lui         $a1, 0x802D
    ctx->r5 = S32(0X802D << 16);
    // 0x802C7B84: addiu       $s0, $s4, 0x1
    ctx->r16 = ADD32(ctx->r20, 0X1);
    // 0x802C7B88: or          $a2, $s0, $zero
    ctx->r6 = ctx->r16 | 0;
    // 0x802C7B8C: jal         0x800CA210
    // 0x802C7B90: addiu       $a1, $a1, -0x7E28
    ctx->r5 = ADD32(ctx->r5, -0X7E28);
    func_800CA210(rdram, ctx);
        goto after_33;
    // 0x802C7B90: addiu       $a1, $a1, -0x7E28
    ctx->r5 = ADD32(ctx->r5, -0X7E28);
    after_33:
    // 0x802C7B94: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
L_802C7B98:
    // 0x802C7B98: beq         $fp, $at, L_802C7BBC
    if (ctx->r30 == ctx->r1) {
        // 0x802C7B9C: or          $a0, $s1, $zero
        ctx->r4 = ctx->r17 | 0;
            goto L_802C7BBC;
    }
    // 0x802C7B9C: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    // 0x802C7BA0: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x802C7BA4: bne         $s4, $at, L_802C7BB4
    if (ctx->r20 != ctx->r1) {
        // 0x802C7BA8: nop
    
            goto L_802C7BB4;
    }
    // 0x802C7BA8: nop

    // 0x802C7BAC: b           L_802C7BC0
    // 0x802C7BB0: addiu       $v0, $zero, -0x1
    ctx->r2 = ADD32(0, -0X1);
        goto L_802C7BC0;
    // 0x802C7BB0: addiu       $v0, $zero, -0x1
    ctx->r2 = ADD32(0, -0X1);
L_802C7BB4:
    // 0x802C7BB4: b           L_802C7BC0
    // 0x802C7BB8: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
        goto L_802C7BC0;
    // 0x802C7BB8: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_802C7BBC:
    // 0x802C7BBC: addiu       $v0, $zero, 0x2
    ctx->r2 = ADD32(0, 0X2);
L_802C7BC0:
    // 0x802C7BC0: addu        $a3, $s7, $v0
    ctx->r7 = ADD32(ctx->r23, ctx->r2);
    // 0x802C7BC4: addiu       $a3, $a3, 0x25
    ctx->r7 = ADD32(ctx->r7, 0X25);
    // 0x802C7BC8: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C7BCC: or          $a2, $s6, $zero
    ctx->r6 = ctx->r22 | 0;
    // 0x802C7BD0: jal         0x801E9858
    // 0x802C7BD4: sw          $s3, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r19;
    func_801E9858(rdram, ctx);
        goto after_34;
    // 0x802C7BD4: sw          $s3, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r19;
    after_34:
    // 0x802C7BD8: lw          $t3, 0xD8($sp)
    ctx->r11 = MEM_W(ctx->r29, 0XD8);
    // 0x802C7BDC: or          $s1, $v0, $zero
    ctx->r17 = ctx->r2 | 0;
    // 0x802C7BE0: or          $a0, $s6, $zero
    ctx->r4 = ctx->r22 | 0;
    // 0x802C7BE4: bne         $t3, $zero, L_802C7C0C
    if (ctx->r11 != 0) {
        // 0x802C7BE8: lui         $a1, 0x802D
        ctx->r5 = S32(0X802D << 16);
            goto L_802C7C0C;
    }
    // 0x802C7BE8: lui         $a1, 0x802D
    ctx->r5 = S32(0X802D << 16);
    // 0x802C7BEC: lui         $a1, 0x802D
    ctx->r5 = S32(0X802D << 16);
    // 0x802C7BF0: lui         $a2, 0x802D
    ctx->r6 = S32(0X802D << 16);
    // 0x802C7BF4: addiu       $a2, $a2, -0x7E20
    ctx->r6 = ADD32(ctx->r6, -0X7E20);
    // 0x802C7BF8: addiu       $a1, $a1, -0x7E24
    ctx->r5 = ADD32(ctx->r5, -0X7E24);
    // 0x802C7BFC: jal         0x800CA210
    // 0x802C7C00: or          $a0, $s6, $zero
    ctx->r4 = ctx->r22 | 0;
    func_800CA210(rdram, ctx);
        goto after_35;
    // 0x802C7C00: or          $a0, $s6, $zero
    ctx->r4 = ctx->r22 | 0;
    after_35:
    // 0x802C7C04: b           L_802C7C20
    // 0x802C7C08: addiu       $v0, $zero, 0x3
    ctx->r2 = ADD32(0, 0X3);
        goto L_802C7C20;
    // 0x802C7C08: addiu       $v0, $zero, 0x3
    ctx->r2 = ADD32(0, 0X3);
L_802C7C0C:
    // 0x802C7C0C: lui         $a2, 0x802D
    ctx->r6 = S32(0X802D << 16);
    // 0x802C7C10: addiu       $a2, $a2, -0x7E18
    ctx->r6 = ADD32(ctx->r6, -0X7E18);
    // 0x802C7C14: jal         0x800CA210
    // 0x802C7C18: addiu       $a1, $a1, -0x7E1C
    ctx->r5 = ADD32(ctx->r5, -0X7E1C);
    func_800CA210(rdram, ctx);
        goto after_36;
    // 0x802C7C18: addiu       $a1, $a1, -0x7E1C
    ctx->r5 = ADD32(ctx->r5, -0X7E1C);
    after_36:
    // 0x802C7C1C: addiu       $v0, $zero, 0x3
    ctx->r2 = ADD32(0, 0X3);
L_802C7C20:
    // 0x802C7C20: bne         $fp, $v0, L_802C7C2C
    if (ctx->r30 != ctx->r2) {
        // 0x802C7C24: or          $a0, $s1, $zero
        ctx->r4 = ctx->r17 | 0;
            goto L_802C7C2C;
    }
    // 0x802C7C24: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    // 0x802C7C28: bne         $s4, $zero, L_802C7C48
    if (ctx->r20 != 0) {
        // 0x802C7C2C: addiu       $a1, $zero, 0x1
        ctx->r5 = ADD32(0, 0X1);
            goto L_802C7C48;
    }
L_802C7C2C:
    // 0x802C7C2C: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C7C30: or          $a2, $s6, $zero
    ctx->r6 = ctx->r22 | 0;
    // 0x802C7C34: addiu       $a3, $s7, 0x4F
    ctx->r7 = ADD32(ctx->r23, 0X4F);
    // 0x802C7C38: jal         0x801E9858
    // 0x802C7C3C: sw          $s3, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r19;
    func_801E9858(rdram, ctx);
        goto after_37;
    // 0x802C7C3C: sw          $s3, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r19;
    after_37:
    // 0x802C7C40: or          $s1, $v0, $zero
    ctx->r17 = ctx->r2 | 0;
    // 0x802C7C44: addiu       $v0, $zero, 0x3
    ctx->r2 = ADD32(0, 0X3);
L_802C7C48:
    // 0x802C7C48: lw          $t4, 0x84($sp)
    ctx->r12 = MEM_W(ctx->r29, 0X84);
    // 0x802C7C4C: or          $s4, $s0, $zero
    ctx->r20 = ctx->r16 | 0;
    // 0x802C7C50: addiu       $s3, $s3, 0x12
    ctx->r19 = ADD32(ctx->r19, 0X12);
    // 0x802C7C54: addiu       $t5, $t4, 0x12
    ctx->r13 = ADD32(ctx->r12, 0X12);
    // 0x802C7C58: bne         $s0, $v0, L_802C783C
    if (ctx->r16 != ctx->r2) {
        // 0x802C7C5C: sw          $t5, 0x84($sp)
        MEM_W(0X84, ctx->r29) = ctx->r13;
            goto L_802C783C;
    }
    // 0x802C7C5C: sw          $t5, 0x84($sp)
    MEM_W(0X84, ctx->r29) = ctx->r13;
    // 0x802C7C60: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x802C7C64: bne         $fp, $at, L_802C7DE8
    if (ctx->r30 != ctx->r1) {
        // 0x802C7C68: lw          $s0, 0xFC($sp)
        ctx->r16 = MEM_W(ctx->r29, 0XFC);
            goto L_802C7DE8;
    }
    // 0x802C7C68: lw          $s0, 0xFC($sp)
    ctx->r16 = MEM_W(ctx->r29, 0XFC);
    // 0x802C7C6C: lw          $t6, 0xF0($sp)
    ctx->r14 = MEM_W(ctx->r29, 0XF0);
    // 0x802C7C70: lui         $t3, 0x802D
    ctx->r11 = S32(0X802D << 16);
    // 0x802C7C74: lw          $t3, -0x7E5C($t3)
    ctx->r11 = MEM_W(ctx->r11, -0X7E5C);
    // 0x802C7C78: sll         $t9, $t6, 2
    ctx->r25 = S32(ctx->r14 << 2);
    // 0x802C7C7C: lui         $t7, 0x801C
    ctx->r15 = S32(0X801C << 16);
    // 0x802C7C80: addu        $t9, $t9, $t6
    ctx->r25 = ADD32(ctx->r25, ctx->r14);
    // 0x802C7C84: sll         $t9, $t9, 2
    ctx->r25 = S32(ctx->r25 << 2);
    // 0x802C7C88: addiu       $t7, $t7, 0x22C0
    ctx->r15 = ADD32(ctx->r15, 0X22C0);
    // 0x802C7C8C: addiu       $t8, $s7, 0x13F
    ctx->r24 = ADD32(ctx->r23, 0X13F);
    // 0x802C7C90: sw          $t8, 0x74($sp)
    MEM_W(0X74, ctx->r29) = ctx->r24;
    // 0x802C7C94: addu        $s3, $t9, $t7
    ctx->r19 = ADD32(ctx->r25, ctx->r15);
    // 0x802C7C98: addiu       $s0, $s0, 0xC4
    ctx->r16 = ADD32(ctx->r16, 0XC4);
    // 0x802C7C9C: addiu       $s5, $s7, 0x5F
    ctx->r21 = ADD32(ctx->r23, 0X5F);
    // 0x802C7CA0: addiu       $s2, $s7, 0x108
    ctx->r18 = ADD32(ctx->r23, 0X108);
    // 0x802C7CA4: beq         $t3, $zero, L_802C7D24
    if (ctx->r11 == 0) {
        // 0x802C7CA8: addiu       $s4, $s7, 0x4F
        ctx->r20 = ADD32(ctx->r23, 0X4F);
            goto L_802C7D24;
    }
    // 0x802C7CA8: addiu       $s4, $s7, 0x4F
    ctx->r20 = ADD32(ctx->r23, 0X4F);
    // 0x802C7CAC: sll         $t4, $t6, 2
    ctx->r12 = S32(ctx->r14 << 2);
    // 0x802C7CB0: lui         $t5, 0x801C
    ctx->r13 = S32(0X801C << 16);
    // 0x802C7CB4: addu        $t5, $t5, $t4
    ctx->r13 = ADD32(ctx->r13, ctx->r12);
    // 0x802C7CB8: lw          $t5, 0x2690($t5)
    ctx->r13 = MEM_W(ctx->r13, 0X2690);
    // 0x802C7CBC: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    // 0x802C7CC0: addiu       $a2, $zero, 0xFF
    ctx->r6 = ADD32(0, 0XFF);
    // 0x802C7CC4: beq         $t5, $zero, L_802C7CD4
    if (ctx->r13 == 0) {
        // 0x802C7CC8: addiu       $a3, $zero, 0xFF
        ctx->r7 = ADD32(0, 0XFF);
            goto L_802C7CD4;
    }
    // 0x802C7CC8: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    // 0x802C7CCC: b           L_802C7CD8
    // 0x802C7CD0: addiu       $a1, $zero, 0x6
    ctx->r5 = ADD32(0, 0X6);
        goto L_802C7CD8;
    // 0x802C7CD0: addiu       $a1, $zero, 0x6
    ctx->r5 = ADD32(0, 0X6);
L_802C7CD4:
    // 0x802C7CD4: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
L_802C7CD8:
    // 0x802C7CD8: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C7CDC: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C7CE0: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C7CE4: addiu       $t3, $zero, 0xFF
    ctx->r11 = ADD32(0, 0XFF);
    // 0x802C7CE8: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C7CEC: addiu       $t4, $zero, 0xFF
    ctx->r12 = ADD32(0, 0XFF);
    // 0x802C7CF0: addiu       $t5, $zero, 0xFF
    ctx->r13 = ADD32(0, 0XFF);
    // 0x802C7CF4: sw          $t5, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r13;
    // 0x802C7CF8: sw          $t4, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r12;
    // 0x802C7CFC: sw          $t6, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r14;
    // 0x802C7D00: sw          $t3, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r11;
    // 0x802C7D04: sw          $t8, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r24;
    // 0x802C7D08: sw          $t8, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r24;
    // 0x802C7D0C: sw          $t7, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r15;
    // 0x802C7D10: sw          $t7, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r15;
    // 0x802C7D14: sw          $t9, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r25;
    // 0x802C7D18: jal         0x801E946C
    // 0x802C7D1C: sw          $t9, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r25;
    func_801E946C(rdram, ctx);
        goto after_38;
    // 0x802C7D1C: sw          $t9, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r25;
    after_38:
    // 0x802C7D20: or          $s1, $v0, $zero
    ctx->r17 = ctx->r2 | 0;
L_802C7D24:
    // 0x802C7D24: lw          $t3, 0x8($s3)
    ctx->r11 = MEM_W(ctx->r19, 0X8);
    // 0x802C7D28: lui         $a1, 0x802D
    ctx->r5 = S32(0X802D << 16);
    // 0x802C7D2C: addiu       $a1, $a1, -0x7E0C
    ctx->r5 = ADD32(ctx->r5, -0X7E0C);
    // 0x802C7D30: bne         $t3, $zero, L_802C7D58
    if (ctx->r11 != 0) {
        // 0x802C7D34: or          $a0, $s6, $zero
        ctx->r4 = ctx->r22 | 0;
            goto L_802C7D58;
    }
    // 0x802C7D34: or          $a0, $s6, $zero
    ctx->r4 = ctx->r22 | 0;
    // 0x802C7D38: lui         $a1, 0x802D
    ctx->r5 = S32(0X802D << 16);
    // 0x802C7D3C: lui         $a2, 0x802D
    ctx->r6 = S32(0X802D << 16);
    // 0x802C7D40: addiu       $a2, $a2, -0x7E10
    ctx->r6 = ADD32(ctx->r6, -0X7E10);
    // 0x802C7D44: addiu       $a1, $a1, -0x7E14
    ctx->r5 = ADD32(ctx->r5, -0X7E14);
    // 0x802C7D48: jal         0x800CA210
    // 0x802C7D4C: or          $a0, $s6, $zero
    ctx->r4 = ctx->r22 | 0;
    func_800CA210(rdram, ctx);
        goto after_39;
    // 0x802C7D4C: or          $a0, $s6, $zero
    ctx->r4 = ctx->r22 | 0;
    after_39:
    // 0x802C7D50: b           L_802C7D68
    // 0x802C7D54: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
        goto L_802C7D68;
    // 0x802C7D54: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
L_802C7D58:
    // 0x802C7D58: lui         $a2, 0x802D
    ctx->r6 = S32(0X802D << 16);
    // 0x802C7D5C: jal         0x800CA210
    // 0x802C7D60: addiu       $a2, $a2, -0x7E08
    ctx->r6 = ADD32(ctx->r6, -0X7E08);
    func_800CA210(rdram, ctx);
        goto after_40;
    // 0x802C7D60: addiu       $a2, $a2, -0x7E08
    ctx->r6 = ADD32(ctx->r6, -0X7E08);
    after_40:
    // 0x802C7D64: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
L_802C7D68:
    // 0x802C7D68: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C7D6C: or          $a2, $s6, $zero
    ctx->r6 = ctx->r22 | 0;
    // 0x802C7D70: or          $a3, $s4, $zero
    ctx->r7 = ctx->r20 | 0;
    // 0x802C7D74: jal         0x801E9858
    // 0x802C7D78: sw          $s0, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r16;
    func_801E9858(rdram, ctx);
        goto after_41;
    // 0x802C7D78: sw          $s0, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r16;
    after_41:
    // 0x802C7D7C: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C7D80: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C7D84: addiu       $a2, $s3, 0x10
    ctx->r6 = ADD32(ctx->r19, 0X10);
    // 0x802C7D88: or          $a3, $s2, $zero
    ctx->r7 = ctx->r18 | 0;
    // 0x802C7D8C: jal         0x801E9858
    // 0x802C7D90: sw          $s0, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r16;
    func_801E9858(rdram, ctx);
        goto after_42;
    // 0x802C7D90: sw          $s0, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r16;
    after_42:
    // 0x802C7D94: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C7D98: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C7D9C: lw          $a2, 0x0($s3)
    ctx->r6 = MEM_W(ctx->r19, 0X0);
    // 0x802C7DA0: lw          $a3, 0x74($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X74);
    // 0x802C7DA4: jal         0x801E8B24
    // 0x802C7DA8: sw          $s0, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r16;
    func_801E8B24(rdram, ctx);
        goto after_43;
    // 0x802C7DA8: sw          $s0, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r16;
    after_43:
    // 0x802C7DAC: lw          $t6, 0xC($s3)
    ctx->r14 = MEM_W(ctx->r19, 0XC);
    // 0x802C7DB0: lw          $t5, 0xFC($sp)
    ctx->r13 = MEM_W(ctx->r29, 0XFC);
    // 0x802C7DB4: lui         $a2, 0x802D
    ctx->r6 = S32(0X802D << 16);
    // 0x802C7DB8: sll         $t4, $t6, 2
    ctx->r12 = S32(ctx->r14 << 2);
    // 0x802C7DBC: addu        $a2, $a2, $t4
    ctx->r6 = ADD32(ctx->r6, ctx->r12);
    // 0x802C7DC0: addiu       $t9, $t5, 0xC5
    ctx->r25 = ADD32(ctx->r13, 0XC5);
    // 0x802C7DC4: sw          $t9, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r25;
    // 0x802C7DC8: lw          $a2, -0x7E68($a2)
    ctx->r6 = MEM_W(ctx->r6, -0X7E68);
    // 0x802C7DCC: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C7DD0: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C7DD4: or          $a3, $s5, $zero
    ctx->r7 = ctx->r21 | 0;
    // 0x802C7DD8: jal         0x801E3EE0
    // 0x802C7DDC: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    func_801E3EE0(rdram, ctx);
        goto after_44;
    // 0x802C7DDC: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    after_44:
    // 0x802C7DE0: b           L_802C7EC4
    // 0x802C7DE4: or          $s1, $v0, $zero
    ctx->r17 = ctx->r2 | 0;
        goto L_802C7EC4;
    // 0x802C7DE4: or          $s1, $v0, $zero
    ctx->r17 = ctx->r2 | 0;
L_802C7DE8:
    // 0x802C7DE8: bne         $fp, $v0, L_802C7EC4
    if (ctx->r30 != ctx->r2) {
        // 0x802C7DEC: or          $a0, $s1, $zero
        ctx->r4 = ctx->r17 | 0;
            goto L_802C7EC4;
    }
    // 0x802C7DEC: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    // 0x802C7DF0: addiu       $t7, $zero, 0x80
    ctx->r15 = ADD32(0, 0X80);
    // 0x802C7DF4: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C7DF8: lw          $s0, 0xFC($sp)
    ctx->r16 = MEM_W(ctx->r29, 0XFC);
    // 0x802C7DFC: sw          $t6, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r14;
    // 0x802C7E00: sw          $t7, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r15;
    // 0x802C7E04: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C7E08: addiu       $t6, $s7, 0xD7
    ctx->r14 = ADD32(ctx->r23, 0XD7);
    // 0x802C7E0C: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C7E10: addiu       $t3, $zero, 0xFF
    ctx->r11 = ADD32(0, 0XFF);
    // 0x802C7E14: addiu       $t4, $zero, 0xFF
    ctx->r12 = ADD32(0, 0XFF);
    // 0x802C7E18: addiu       $t5, $zero, 0xFF
    ctx->r13 = ADD32(0, 0XFF);
    // 0x802C7E1C: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C7E20: sw          $t9, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r25;
    // 0x802C7E24: sw          $t5, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r13;
    // 0x802C7E28: sw          $t4, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r12;
    // 0x802C7E2C: sw          $t3, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r11;
    // 0x802C7E30: sw          $t3, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r11;
    // 0x802C7E34: sw          $t8, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r24;
    // 0x802C7E38: sw          $t8, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r24;
    // 0x802C7E3C: sw          $t6, 0x74($sp)
    MEM_W(0X74, ctx->r29) = ctx->r14;
    // 0x802C7E40: sw          $t7, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r15;
    // 0x802C7E44: addiu       $a1, $zero, 0x7
    ctx->r5 = ADD32(0, 0X7);
    // 0x802C7E48: addiu       $a2, $zero, 0x80
    ctx->r6 = ADD32(0, 0X80);
    // 0x802C7E4C: addiu       $a3, $zero, 0x80
    ctx->r7 = ADD32(0, 0X80);
    // 0x802C7E50: addiu       $s5, $s7, 0x5F
    ctx->r21 = ADD32(ctx->r23, 0X5F);
    // 0x802C7E54: jal         0x801E946C
    // 0x802C7E58: addiu       $s0, $s0, 0xC4
    ctx->r16 = ADD32(ctx->r16, 0XC4);
    func_801E946C(rdram, ctx);
        goto after_45;
    // 0x802C7E58: addiu       $s0, $s0, 0xC4
    ctx->r16 = ADD32(ctx->r16, 0XC4);
    after_45:
    // 0x802C7E5C: lw          $t4, 0xFC($sp)
    ctx->r12 = MEM_W(ctx->r29, 0XFC);
    // 0x802C7E60: lui         $a2, 0x802D
    ctx->r6 = S32(0X802D << 16);
    // 0x802C7E64: addiu       $a2, $a2, -0x7E04
    ctx->r6 = ADD32(ctx->r6, -0X7E04);
    // 0x802C7E68: addiu       $t5, $t4, 0x12E
    ctx->r13 = ADD32(ctx->r12, 0X12E);
    // 0x802C7E6C: sw          $t5, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r13;
    // 0x802C7E70: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C7E74: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C7E78: jal         0x801E9858
    // 0x802C7E7C: addiu       $a3, $s7, 0x9B
    ctx->r7 = ADD32(ctx->r23, 0X9B);
    func_801E9858(rdram, ctx);
        goto after_46;
    // 0x802C7E7C: addiu       $a3, $s7, 0x9B
    ctx->r7 = ADD32(ctx->r23, 0X9B);
    after_46:
    // 0x802C7E80: lui         $a2, 0x802D
    ctx->r6 = S32(0X802D << 16);
    // 0x802C7E84: addiu       $a2, $a2, -0x7E00
    ctx->r6 = ADD32(ctx->r6, -0X7E00);
    // 0x802C7E88: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C7E8C: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C7E90: lw          $a3, 0x74($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X74);
    // 0x802C7E94: jal         0x801E9858
    // 0x802C7E98: sw          $s0, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r16;
    func_801E9858(rdram, ctx);
        goto after_47;
    // 0x802C7E98: sw          $s0, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r16;
    after_47:
    // 0x802C7E9C: lw          $t9, 0xFC($sp)
    ctx->r25 = MEM_W(ctx->r29, 0XFC);
    // 0x802C7EA0: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C7EA4: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C7EA8: addiu       $t7, $t9, 0xC5
    ctx->r15 = ADD32(ctx->r25, 0XC5);
    // 0x802C7EAC: sw          $t7, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r15;
    // 0x802C7EB0: addiu       $a2, $zero, 0x24
    ctx->r6 = ADD32(0, 0X24);
    // 0x802C7EB4: or          $a3, $s5, $zero
    ctx->r7 = ctx->r21 | 0;
    // 0x802C7EB8: jal         0x801E3EE0
    // 0x802C7EBC: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    func_801E3EE0(rdram, ctx);
        goto after_48;
    // 0x802C7EBC: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    after_48:
    // 0x802C7EC0: or          $s1, $v0, $zero
    ctx->r17 = ctx->r2 | 0;
L_802C7EC4:
    // 0x802C7EC4: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C7EC8: addiu       $t3, $zero, 0xFF
    ctx->r11 = ADD32(0, 0XFF);
    // 0x802C7ECC: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C7ED0: addiu       $t4, $zero, 0xFF
    ctx->r12 = ADD32(0, 0XFF);
    // 0x802C7ED4: addiu       $t5, $zero, 0xFF
    ctx->r13 = ADD32(0, 0XFF);
    // 0x802C7ED8: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C7EDC: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C7EE0: sw          $t7, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r15;
    // 0x802C7EE4: sw          $t9, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r25;
    // 0x802C7EE8: sw          $t5, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r13;
    // 0x802C7EEC: sw          $t4, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r12;
    // 0x802C7EF0: sw          $t6, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r14;
    // 0x802C7EF4: sw          $t6, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r14;
    // 0x802C7EF8: sw          $t3, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r11;
    // 0x802C7EFC: sw          $t3, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r11;
    // 0x802C7F00: sw          $t8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r24;
    // 0x802C7F04: sw          $t8, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r24;
    // 0x802C7F08: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    // 0x802C7F0C: addiu       $a1, $zero, 0x6
    ctx->r5 = ADD32(0, 0X6);
    // 0x802C7F10: addiu       $a2, $zero, 0xFF
    ctx->r6 = ADD32(0, 0XFF);
    // 0x802C7F14: jal         0x801E946C
    // 0x802C7F18: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    func_801E946C(rdram, ctx);
        goto after_49;
    // 0x802C7F18: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    after_49:
    // 0x802C7F1C: lw          $t4, 0xF0($sp)
    ctx->r12 = MEM_W(ctx->r29, 0XF0);
    // 0x802C7F20: or          $s1, $v0, $zero
    ctx->r17 = ctx->r2 | 0;
    // 0x802C7F24: lui         $t5, 0x802D
    ctx->r13 = S32(0X802D << 16);
    // 0x802C7F28: beql        $t4, $zero, L_802C7FFC
    if (ctx->r12 == 0) {
        // 0x802C7F2C: lw          $ra, 0x64($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X64);
            goto L_802C7FFC;
    }
    goto skip_3;
    // 0x802C7F2C: lw          $ra, 0x64($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X64);
    skip_3:
    // 0x802C7F30: lw          $t5, -0x7E5C($t5)
    ctx->r13 = MEM_W(ctx->r13, -0X7E5C);
    // 0x802C7F34: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x802C7F38: bnel        $t5, $zero, L_802C7FFC
    if (ctx->r13 != 0) {
        // 0x802C7F3C: lw          $ra, 0x64($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X64);
            goto L_802C7FFC;
    }
    goto skip_4;
    // 0x802C7F3C: lw          $ra, 0x64($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X64);
    skip_4:
    // 0x802C7F40: bne         $fp, $at, L_802C7F9C
    if (ctx->r30 != ctx->r1) {
        // 0x802C7F44: or          $a0, $v0, $zero
        ctx->r4 = ctx->r2 | 0;
            goto L_802C7F9C;
    }
    // 0x802C7F44: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C7F48: lw          $s0, 0xFC($sp)
    ctx->r16 = MEM_W(ctx->r29, 0XFC);
    // 0x802C7F4C: lui         $a2, 0x802D
    ctx->r6 = S32(0X802D << 16);
    // 0x802C7F50: addiu       $a2, $a2, -0x7DF4
    ctx->r6 = ADD32(ctx->r6, -0X7DF4);
    // 0x802C7F54: addiu       $s0, $s0, 0x4E
    ctx->r16 = ADD32(ctx->r16, 0X4E);
    // 0x802C7F58: sw          $s0, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r16;
    // 0x802C7F5C: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C7F60: jal         0x801E9858
    // 0x802C7F64: addiu       $a3, $s7, 0x18A
    ctx->r7 = ADD32(ctx->r23, 0X18A);
    func_801E9858(rdram, ctx);
        goto after_50;
    // 0x802C7F64: addiu       $a3, $s7, 0x18A
    ctx->r7 = ADD32(ctx->r23, 0X18A);
    after_50:
    // 0x802C7F68: lui         $t9, 0x802D
    ctx->r25 = S32(0X802D << 16);
    // 0x802C7F6C: lw          $t9, -0x7E4C($t9)
    ctx->r25 = MEM_W(ctx->r25, -0X7E4C);
    // 0x802C7F70: or          $s1, $v0, $zero
    ctx->r17 = ctx->r2 | 0;
    // 0x802C7F74: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C7F78: beq         $t9, $zero, L_802C7FF8
    if (ctx->r25 == 0) {
        // 0x802C7F7C: addiu       $a1, $zero, 0x2
        ctx->r5 = ADD32(0, 0X2);
            goto L_802C7FF8;
    }
    // 0x802C7F7C: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C7F80: lui         $a2, 0x802D
    ctx->r6 = S32(0X802D << 16);
    // 0x802C7F84: addiu       $a2, $a2, -0x7DF0
    ctx->r6 = ADD32(ctx->r6, -0X7DF0);
    // 0x802C7F88: addiu       $a3, $s7, 0x16
    ctx->r7 = ADD32(ctx->r23, 0X16);
    // 0x802C7F8C: jal         0x801E9858
    // 0x802C7F90: sw          $s0, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r16;
    func_801E9858(rdram, ctx);
        goto after_51;
    // 0x802C7F90: sw          $s0, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r16;
    after_51:
    // 0x802C7F94: b           L_802C7FF8
    // 0x802C7F98: or          $s1, $v0, $zero
    ctx->r17 = ctx->r2 | 0;
        goto L_802C7FF8;
    // 0x802C7F98: or          $s1, $v0, $zero
    ctx->r17 = ctx->r2 | 0;
L_802C7F9C:
    // 0x802C7F9C: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x802C7FA0: bne         $fp, $at, L_802C7FD4
    if (ctx->r30 != ctx->r1) {
        // 0x802C7FA4: or          $a0, $s1, $zero
        ctx->r4 = ctx->r17 | 0;
            goto L_802C7FD4;
    }
    // 0x802C7FA4: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    // 0x802C7FA8: lw          $t7, 0xFC($sp)
    ctx->r15 = MEM_W(ctx->r29, 0XFC);
    // 0x802C7FAC: lui         $a2, 0x802D
    ctx->r6 = S32(0X802D << 16);
    // 0x802C7FB0: addiu       $a2, $a2, -0x7DEC
    ctx->r6 = ADD32(ctx->r6, -0X7DEC);
    // 0x802C7FB4: addiu       $t8, $t7, 0x4E
    ctx->r24 = ADD32(ctx->r15, 0X4E);
    // 0x802C7FB8: sw          $t8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r24;
    // 0x802C7FBC: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    // 0x802C7FC0: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C7FC4: jal         0x801E9858
    // 0x802C7FC8: addiu       $a3, $s7, 0x122
    ctx->r7 = ADD32(ctx->r23, 0X122);
    func_801E9858(rdram, ctx);
        goto after_52;
    // 0x802C7FC8: addiu       $a3, $s7, 0x122
    ctx->r7 = ADD32(ctx->r23, 0X122);
    after_52:
    // 0x802C7FCC: b           L_802C7FF8
    // 0x802C7FD0: or          $s1, $v0, $zero
    ctx->r17 = ctx->r2 | 0;
        goto L_802C7FF8;
    // 0x802C7FD0: or          $s1, $v0, $zero
    ctx->r17 = ctx->r2 | 0;
L_802C7FD4:
    // 0x802C7FD4: lw          $t3, 0xFC($sp)
    ctx->r11 = MEM_W(ctx->r29, 0XFC);
    // 0x802C7FD8: lui         $a2, 0x802D
    ctx->r6 = S32(0X802D << 16);
    // 0x802C7FDC: addiu       $a2, $a2, -0x7DE8
    ctx->r6 = ADD32(ctx->r6, -0X7DE8);
    // 0x802C7FE0: addiu       $t6, $t3, 0x4E
    ctx->r14 = ADD32(ctx->r11, 0X4E);
    // 0x802C7FE4: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x802C7FE8: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C7FEC: jal         0x801E9858
    // 0x802C7FF0: addiu       $a3, $s7, 0x16
    ctx->r7 = ADD32(ctx->r23, 0X16);
    func_801E9858(rdram, ctx);
        goto after_53;
    // 0x802C7FF0: addiu       $a3, $s7, 0x16
    ctx->r7 = ADD32(ctx->r23, 0X16);
    after_53:
    // 0x802C7FF4: or          $s1, $v0, $zero
    ctx->r17 = ctx->r2 | 0;
L_802C7FF8:
    // 0x802C7FF8: lw          $ra, 0x64($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X64);
L_802C7FFC:
    // 0x802C7FFC: or          $v0, $s1, $zero
    ctx->r2 = ctx->r17 | 0;
    // 0x802C8000: lw          $s1, 0x44($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X44);
    // 0x802C8004: lw          $s0, 0x40($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X40);
    // 0x802C8008: lw          $s2, 0x48($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X48);
    // 0x802C800C: lw          $s3, 0x4C($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X4C);
    // 0x802C8010: lw          $s4, 0x50($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X50);
    // 0x802C8014: lw          $s5, 0x54($sp)
    ctx->r21 = MEM_W(ctx->r29, 0X54);
    // 0x802C8018: lw          $s6, 0x58($sp)
    ctx->r22 = MEM_W(ctx->r29, 0X58);
    // 0x802C801C: lw          $s7, 0x5C($sp)
    ctx->r23 = MEM_W(ctx->r29, 0X5C);
    // 0x802C8020: lw          $fp, 0x60($sp)
    ctx->r30 = MEM_W(ctx->r29, 0X60);
    // 0x802C8024: jr          $ra
    // 0x802C8028: addiu       $sp, $sp, 0xE8
    ctx->r29 = ADD32(ctx->r29, 0XE8);
    return;
    // 0x802C8028: addiu       $sp, $sp, 0xE8
    ctx->r29 = ADD32(ctx->r29, 0XE8);
;}
RECOMP_FUNC void func_i9_802C802C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C802C: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x802C8030: addiu       $v0, $v0, -0x54DC
    ctx->r2 = ADD32(ctx->r2, -0X54DC);
    // 0x802C8034: lw          $t6, 0x0($v0)
    ctx->r14 = MEM_W(ctx->r2, 0X0);
    // 0x802C8038: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C803C: addiu       $t7, $zero, 0x43
    ctx->r15 = ADD32(0, 0X43);
    // 0x802C8040: sw          $t6, -0x19CC($at)
    MEM_W(-0X19CC, ctx->r1) = ctx->r14;
    // 0x802C8044: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C8048: sw          $a0, -0x19D0($at)
    MEM_W(-0X19D0, ctx->r1) = ctx->r4;
    // 0x802C804C: sw          $t7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r15;
    // 0x802C8050: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C8054: addiu       $t8, $zero, 0xC
    ctx->r24 = ADD32(0, 0XC);
    // 0x802C8058: sw          $t8, -0x19C8($at)
    MEM_W(-0X19C8, ctx->r1) = ctx->r24;
    // 0x802C805C: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C8060: addiu       $t9, $zero, 0x1
    ctx->r25 = ADD32(0, 0X1);
    // 0x802C8064: sw          $t9, -0x19C4($at)
    MEM_W(-0X19C4, ctx->r1) = ctx->r25;
    // 0x802C8068: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C806C: sw          $zero, -0x19C0($at)
    MEM_W(-0X19C0, ctx->r1) = 0;
    // 0x802C8070: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C8074: sw          $zero, -0x19BC($at)
    MEM_W(-0X19BC, ctx->r1) = 0;
    // 0x802C8078: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x802C807C: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x802C8080: sw          $zero, -0x54E4($at)
    MEM_W(-0X54E4, ctx->r1) = 0;
    // 0x802C8084: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x802C8088: lui         $at, 0x800D
    ctx->r1 = S32(0X800D << 16);
    // 0x802C808C: addiu       $t0, $zero, 0x2
    ctx->r8 = ADD32(0, 0X2);
    // 0x802C8090: sw          $t0, 0x461C($at)
    MEM_W(0X461C, ctx->r1) = ctx->r8;
    // 0x802C8094: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    // 0x802C8098: addiu       $a1, $zero, 0x4
    ctx->r5 = ADD32(0, 0X4);
    // 0x802C809C: jal         0x801E6FB0
    // 0x802C80A0: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    FadeTransition_SetProps(rdram, ctx);
        goto after_0;
    // 0x802C80A0: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    after_0:
    // 0x802C80A4: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x802C80A8: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x802C80AC: jr          $ra
    // 0x802C80B0: nop

    return;
    // 0x802C80B0: nop

    // 0x802C80B4: nop

    // 0x802C80B8: nop

    // 0x802C80BC: nop

;}
RECOMP_FUNC void func_i10_802C5800(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C5800: lui         $t6, 0x801D
    ctx->r14 = S32(0X801D << 16);
    // 0x802C5804: lw          $t6, -0x19C4($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X19C4);
    // 0x802C5808: lui         $t7, 0x800E
    ctx->r15 = S32(0X800E << 16);
    // 0x802C580C: beq         $t6, $zero, L_802C5960
    if (ctx->r14 == 0) {
        // 0x802C5810: nop
    
            goto L_802C5960;
    }
    // 0x802C5810: nop

    // 0x802C5814: lw          $t7, -0x54DC($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X54DC);
    // 0x802C5818: addiu       $at, $zero, 0x44
    ctx->r1 = ADD32(0, 0X44);
    // 0x802C581C: lui         $v1, 0x802C
    ctx->r3 = S32(0X802C << 16);
    // 0x802C5820: bne         $t7, $at, L_802C5960
    if (ctx->r15 != ctx->r1) {
        // 0x802C5824: addiu       $v1, $v1, 0x6B40
        ctx->r3 = ADD32(ctx->r3, 0X6B40);
            goto L_802C5960;
    }
    // 0x802C5824: addiu       $v1, $v1, 0x6B40
    ctx->r3 = ADD32(ctx->r3, 0X6B40);
    // 0x802C5828: lui         $v0, 0x802C
    ctx->r2 = S32(0X802C << 16);
    // 0x802C582C: addiu       $v0, $v0, 0x6B58
    ctx->r2 = ADD32(ctx->r2, 0X6B58);
L_802C5830:
    // 0x802C5830: addiu       $v1, $v1, 0x4
    ctx->r3 = ADD32(ctx->r3, 0X4);
    // 0x802C5834: sltu        $at, $v1, $v0
    ctx->r1 = ctx->r3 < ctx->r2 ? 1 : 0;
    // 0x802C5838: bne         $at, $zero, L_802C5830
    if (ctx->r1 != 0) {
        // 0x802C583C: sw          $zero, -0x4($v1)
        MEM_W(-0X4, ctx->r3) = 0;
            goto L_802C5830;
    }
    // 0x802C583C: sw          $zero, -0x4($v1)
    MEM_W(-0X4, ctx->r3) = 0;
    // 0x802C5840: lui         $a0, 0x802C
    ctx->r4 = S32(0X802C << 16);
    // 0x802C5844: addiu       $a0, $a0, 0x6B40
    ctx->r4 = ADD32(ctx->r4, 0X6B40);
    // 0x802C5848: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C584C: sw          $a1, 0x10($a0)
    MEM_W(0X10, ctx->r4) = ctx->r5;
    // 0x802C5850: sw          $a1, 0xC($a0)
    MEM_W(0XC, ctx->r4) = ctx->r5;
    // 0x802C5854: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x802C5858: lb          $v0, -0x4D80($v0)
    ctx->r2 = MEM_B(ctx->r2, -0X4D80);
    // 0x802C585C: or          $t8, $a1, $zero
    ctx->r24 = ctx->r5 | 0;
    // 0x802C5860: lui         $v1, 0x802C
    ctx->r3 = S32(0X802C << 16);
    // 0x802C5864: andi        $t9, $v0, 0x1
    ctx->r25 = ctx->r2 & 0X1;
    // 0x802C5868: beq         $t9, $zero, L_802C5874
    if (ctx->r25 == 0) {
        // 0x802C586C: andi        $t0, $v0, 0x2
        ctx->r8 = ctx->r2 & 0X2;
            goto L_802C5874;
    }
    // 0x802C586C: andi        $t0, $v0, 0x2
    ctx->r8 = ctx->r2 & 0X2;
    // 0x802C5870: sw          $a1, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r5;
L_802C5874:
    // 0x802C5874: beq         $t0, $zero, L_802C5880
    if (ctx->r8 == 0) {
        // 0x802C5878: andi        $t1, $v0, 0x4
        ctx->r9 = ctx->r2 & 0X4;
            goto L_802C5880;
    }
    // 0x802C5878: andi        $t1, $v0, 0x4
    ctx->r9 = ctx->r2 & 0X4;
    // 0x802C587C: sw          $a1, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r5;
L_802C5880:
    // 0x802C5880: beq         $t1, $zero, L_802C588C
    if (ctx->r9 == 0) {
        // 0x802C5884: or          $v0, $zero, $zero
        ctx->r2 = 0 | 0;
            goto L_802C588C;
    }
    // 0x802C5884: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    // 0x802C5888: sw          $a1, 0x8($a0)
    MEM_W(0X8, ctx->r4) = ctx->r5;
L_802C588C:
    // 0x802C588C: addiu       $v1, $v1, 0x6B40
    ctx->r3 = ADD32(ctx->r3, 0X6B40);
L_802C5890:
    // 0x802C5890: lw          $t2, 0x0($v1)
    ctx->r10 = MEM_W(ctx->r3, 0X0);
    // 0x802C5894: bnel        $t2, $zero, L_802C58B0
    if (ctx->r10 != 0) {
        // 0x802C5898: addiu       $v1, $zero, 0x3
        ctx->r3 = ADD32(0, 0X3);
            goto L_802C58B0;
    }
    goto skip_0;
    // 0x802C5898: addiu       $v1, $zero, 0x3
    ctx->r3 = ADD32(0, 0X3);
    skip_0:
    // 0x802C589C: addiu       $v0, $v0, 0x1
    ctx->r2 = ADD32(ctx->r2, 0X1);
    // 0x802C58A0: slti        $at, $v0, 0x5
    ctx->r1 = SIGNED(ctx->r2) < 0X5 ? 1 : 0;
    // 0x802C58A4: bne         $at, $zero, L_802C5890
    if (ctx->r1 != 0) {
        // 0x802C58A8: addiu       $v1, $v1, 0x4
        ctx->r3 = ADD32(ctx->r3, 0X4);
            goto L_802C5890;
    }
    // 0x802C58A8: addiu       $v1, $v1, 0x4
    ctx->r3 = ADD32(ctx->r3, 0X4);
    // 0x802C58AC: addiu       $v1, $zero, 0x3
    ctx->r3 = ADD32(0, 0X3);
L_802C58B0:
    // 0x802C58B0: bne         $v0, $v1, L_802C58CC
    if (ctx->r2 != ctx->r3) {
        // 0x802C58B4: nop
    
            goto L_802C58CC;
    }
    // 0x802C58B4: nop

    // 0x802C58B8: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C58BC: sw          $a1, 0x6B30($at)
    MEM_W(0X6B30, ctx->r1) = ctx->r5;
    // 0x802C58C0: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C58C4: b           L_802C5910
    // 0x802C58C8: sw          $a1, 0x6B34($at)
    MEM_W(0X6B34, ctx->r1) = ctx->r5;
        goto L_802C5910;
    // 0x802C58C8: sw          $a1, 0x6B34($at)
    MEM_W(0X6B34, ctx->r1) = ctx->r5;
L_802C58CC:
    // 0x802C58CC: div         $zero, $v0, $v1
    lo = S32(S64(S32(ctx->r2)) / S64(S32(ctx->r3))); hi = S32(S64(S32(ctx->r2)) % S64(S32(ctx->r3)));
    // 0x802C58D0: bne         $v1, $zero, L_802C58DC
    if (ctx->r3 != 0) {
        // 0x802C58D4: nop
    
            goto L_802C58DC;
    }
    // 0x802C58D4: nop

    // 0x802C58D8: break       7
    do_break(2150389976);
L_802C58DC:
    // 0x802C58DC: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x802C58E0: bne         $v1, $at, L_802C58F4
    if (ctx->r3 != ctx->r1) {
        // 0x802C58E4: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_802C58F4;
    }
    // 0x802C58E4: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x802C58E8: bne         $v0, $at, L_802C58F4
    if (ctx->r2 != ctx->r1) {
        // 0x802C58EC: nop
    
            goto L_802C58F4;
    }
    // 0x802C58EC: nop

    // 0x802C58F0: break       6
    do_break(2150390000);
L_802C58F4:
    // 0x802C58F4: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C58F8: mfhi        $t3
    ctx->r11 = hi;
    // 0x802C58FC: sw          $t3, 0x6B30($at)
    MEM_W(0X6B30, ctx->r1) = ctx->r11;
    // 0x802C5900: mflo        $t4
    ctx->r12 = lo;
    // 0x802C5904: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C5908: sw          $t4, 0x6B34($at)
    MEM_W(0X6B34, ctx->r1) = ctx->r12;
    // 0x802C590C: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_802C5910:
    // 0x802C5910: lui         $v0, 0x802C
    ctx->r2 = S32(0X802C << 16);
    // 0x802C5914: addiu       $v0, $v0, 0x6B14
    ctx->r2 = ADD32(ctx->r2, 0X6B14);
    // 0x802C5918: lui         $v1, 0x802C
    ctx->r3 = S32(0X802C << 16);
    // 0x802C591C: lui         $a1, 0x802C
    ctx->r5 = S32(0X802C << 16);
    // 0x802C5920: sw          $zero, 0x0($v0)
    MEM_W(0X0, ctx->r2) = 0;
    // 0x802C5924: addiu       $a1, $a1, 0x6B4C
    ctx->r5 = ADD32(ctx->r5, 0X6B4C);
    // 0x802C5928: addiu       $v1, $v1, 0x6B40
    ctx->r3 = ADD32(ctx->r3, 0X6B40);
    // 0x802C592C: lw          $t5, 0x0($v1)
    ctx->r13 = MEM_W(ctx->r3, 0X0);
L_802C5930:
    // 0x802C5930: addiu       $v1, $v1, 0x4
    ctx->r3 = ADD32(ctx->r3, 0X4);
    // 0x802C5934: beq         $t5, $zero, L_802C5948
    if (ctx->r13 == 0) {
        // 0x802C5938: nop
    
            goto L_802C5948;
    }
    // 0x802C5938: nop

    // 0x802C593C: lw          $t6, 0x0($v0)
    ctx->r14 = MEM_W(ctx->r2, 0X0);
    // 0x802C5940: addiu       $t7, $t6, 0x1
    ctx->r15 = ADD32(ctx->r14, 0X1);
    // 0x802C5944: sw          $t7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r15;
L_802C5948:
    // 0x802C5948: bnel        $v1, $a1, L_802C5930
    if (ctx->r3 != ctx->r5) {
        // 0x802C594C: lw          $t5, 0x0($v1)
        ctx->r13 = MEM_W(ctx->r3, 0X0);
            goto L_802C5930;
    }
    goto skip_1;
    // 0x802C594C: lw          $t5, 0x0($v1)
    ctx->r13 = MEM_W(ctx->r3, 0X0);
    skip_1:
    // 0x802C5950: lw          $t8, 0x0($v0)
    ctx->r24 = MEM_W(ctx->r2, 0X0);
    // 0x802C5954: bne         $t8, $zero, L_802C5960
    if (ctx->r24 != 0) {
        // 0x802C5958: nop
    
            goto L_802C5960;
    }
    // 0x802C5958: nop

    // 0x802C595C: sw          $zero, 0xC($a0)
    MEM_W(0XC, ctx->r4) = 0;
L_802C5960:
    // 0x802C5960: jr          $ra
    // 0x802C5964: nop

    return;
    // 0x802C5964: nop

;}
RECOMP_FUNC void func_i10_802C5968(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C5968: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x802C596C: addiu       $v0, $v0, -0x19C4
    ctx->r2 = ADD32(ctx->r2, -0X19C4);
    // 0x802C5970: lw          $t6, 0x0($v0)
    ctx->r14 = MEM_W(ctx->r2, 0X0);
    // 0x802C5974: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x802C5978: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x802C597C: beq         $t6, $zero, L_802C59A8
    if (ctx->r14 == 0) {
        // 0x802C5980: lui         $t7, 0x800E
        ctx->r15 = S32(0X800E << 16);
            goto L_802C59A8;
    }
    // 0x802C5980: lui         $t7, 0x800E
    ctx->r15 = S32(0X800E << 16);
    // 0x802C5984: sw          $zero, 0x0($v0)
    MEM_W(0X0, ctx->r2) = 0;
    // 0x802C5988: lw          $t7, -0x54DC($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X54DC);
    // 0x802C598C: addiu       $at, $zero, 0x44
    ctx->r1 = ADD32(0, 0X44);
    // 0x802C5990: bne         $t7, $at, L_802C59A8
    if (ctx->r15 != ctx->r1) {
        // 0x802C5994: nop
    
            goto L_802C59A8;
    }
    // 0x802C5994: nop

    // 0x802C5998: jal         0x80093C44
    // 0x802C599C: nop

    func_80093C44(rdram, ctx);
        goto after_0;
    // 0x802C599C: nop

    after_0:
    // 0x802C59A0: b           L_802C5A04
    // 0x802C59A4: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_802C5A04;
    // 0x802C59A4: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C59A8:
    // 0x802C59A8: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x802C59AC: jal         0x802C6200
    // 0x802C59B0: sw          $zero, -0x54D4($at)
    MEM_W(-0X54D4, ctx->r1) = 0;
    func_i10_802C6200(rdram, ctx);
        goto after_1;
    // 0x802C59B0: sw          $zero, -0x54D4($at)
    MEM_W(-0X54D4, ctx->r1) = 0;
    after_1:
    // 0x802C59B4: lui         $t8, 0x800E
    ctx->r24 = S32(0X800E << 16);
    // 0x802C59B8: lw          $t8, -0x54DC($t8)
    ctx->r24 = MEM_W(ctx->r24, -0X54DC);
    // 0x802C59BC: addiu       $at, $zero, 0x44
    ctx->r1 = ADD32(0, 0X44);
    // 0x802C59C0: sw          $v0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r2;
    // 0x802C59C4: bne         $t8, $at, L_802C59DC
    if (ctx->r24 != ctx->r1) {
        // 0x802C59C8: lui         $t9, 0x8023
        ctx->r25 = S32(0X8023 << 16);
            goto L_802C59DC;
    }
    // 0x802C59C8: lui         $t9, 0x8023
    ctx->r25 = S32(0X8023 << 16);
    // 0x802C59CC: jal         0x802C5A10
    // 0x802C59D0: nop

    func_i10_802C5A10(rdram, ctx);
        goto after_2;
    // 0x802C59D0: nop

    after_2:
    // 0x802C59D4: b           L_802C5A00
    // 0x802C59D8: lw          $v0, 0x18($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X18);
        goto L_802C5A00;
    // 0x802C59D8: lw          $v0, 0x18($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X18);
L_802C59DC:
    // 0x802C59DC: lh          $t9, -0x75EA($t9)
    ctx->r25 = MEM_H(ctx->r25, -0X75EA);
    // 0x802C59E0: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x802C59E4: bnel        $t9, $at, L_802C5A00
    if (ctx->r25 != ctx->r1) {
        // 0x802C59E8: lw          $v0, 0x18($sp)
        ctx->r2 = MEM_W(ctx->r29, 0X18);
            goto L_802C5A00;
    }
    goto skip_0;
    // 0x802C59E8: lw          $v0, 0x18($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X18);
    skip_0:
    // 0x802C59EC: jal         0x8007C50C
    // 0x802C59F0: nop

    func_8007C50C(rdram, ctx);
        goto after_3;
    // 0x802C59F0: nop

    after_3:
    // 0x802C59F4: jal         0x801EC304
    // 0x802C59F8: nop

    func_801EC304(rdram, ctx);
        goto after_4;
    // 0x802C59F8: nop

    after_4:
    // 0x802C59FC: lw          $v0, 0x18($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X18);
L_802C5A00:
    // 0x802C5A00: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C5A04:
    // 0x802C5A04: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x802C5A08: jr          $ra
    // 0x802C5A0C: nop

    return;
    // 0x802C5A0C: nop

;}
RECOMP_FUNC void func_i10_802C5A10(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C5A10: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x802C5A14: addiu       $v1, $v1, -0x19A8
    ctx->r3 = ADD32(ctx->r3, -0X19A8);
    // 0x802C5A18: lhu         $v0, 0x3A($v1)
    ctx->r2 = MEM_HU(ctx->r3, 0X3A);
    // 0x802C5A1C: addiu       $sp, $sp, -0x28
    ctx->r29 = ADD32(ctx->r29, -0X28);
    // 0x802C5A20: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x802C5A24: andi        $t6, $v0, 0xB000
    ctx->r14 = ctx->r2 & 0XB000;
    // 0x802C5A28: beq         $t6, $zero, L_802C5B68
    if (ctx->r14 == 0) {
        // 0x802C5A2C: or          $t4, $zero, $zero
        ctx->r12 = 0 | 0;
            goto L_802C5B68;
    }
    // 0x802C5A2C: or          $t4, $zero, $zero
    ctx->r12 = 0 | 0;
    // 0x802C5A30: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x802C5A34: addiu       $v1, $v1, -0x19C0
    ctx->r3 = ADD32(ctx->r3, -0X19C0);
    // 0x802C5A38: lw          $v0, 0x0($v1)
    ctx->r2 = MEM_W(ctx->r3, 0X0);
    // 0x802C5A3C: lui         $a1, 0x802C
    ctx->r5 = S32(0X802C << 16);
    // 0x802C5A40: addiu       $a1, $a1, 0x6B34
    ctx->r5 = ADD32(ctx->r5, 0X6B34);
    // 0x802C5A44: beq         $v0, $zero, L_802C5A74
    if (ctx->r2 == 0) {
        // 0x802C5A48: addiu       $t1, $zero, 0x1
        ctx->r9 = ADD32(0, 0X1);
            goto L_802C5A74;
    }
    // 0x802C5A48: addiu       $t1, $zero, 0x1
    ctx->r9 = ADD32(0, 0X1);
    // 0x802C5A4C: beq         $v0, $t1, L_802C5B20
    if (ctx->r2 == ctx->r9) {
        // 0x802C5A50: addiu       $t3, $zero, 0x2
        ctx->r11 = ADD32(0, 0X2);
            goto L_802C5B20;
    }
    // 0x802C5A50: addiu       $t3, $zero, 0x2
    ctx->r11 = ADD32(0, 0X2);
    // 0x802C5A54: addiu       $t3, $zero, 0x2
    ctx->r11 = ADD32(0, 0X2);
    // 0x802C5A58: beq         $v0, $t3, L_802C5B34
    if (ctx->r2 == ctx->r11) {
        // 0x802C5A5C: addiu       $a3, $zero, 0x3
        ctx->r7 = ADD32(0, 0X3);
            goto L_802C5B34;
    }
    // 0x802C5A5C: addiu       $a3, $zero, 0x3
    ctx->r7 = ADD32(0, 0X3);
    // 0x802C5A60: addiu       $a3, $zero, 0x3
    ctx->r7 = ADD32(0, 0X3);
    // 0x802C5A64: beql        $v0, $a3, L_802C5B4C
    if (ctx->r2 == ctx->r7) {
        // 0x802C5A68: addiu       $t4, $zero, 0x1
        ctx->r12 = ADD32(0, 0X1);
            goto L_802C5B4C;
    }
    goto skip_0;
    // 0x802C5A68: addiu       $t4, $zero, 0x1
    ctx->r12 = ADD32(0, 0X1);
    skip_0:
    // 0x802C5A6C: b           L_802C5B50
    // 0x802C5A70: nop

        goto L_802C5B50;
    // 0x802C5A70: nop

L_802C5A74:
    // 0x802C5A74: lw          $t7, 0x0($a1)
    ctx->r15 = MEM_W(ctx->r5, 0X0);
    // 0x802C5A78: addiu       $a3, $zero, 0x3
    ctx->r7 = ADD32(0, 0X3);
    // 0x802C5A7C: lui         $t0, 0x802C
    ctx->r8 = S32(0X802C << 16);
    // 0x802C5A80: multu       $t7, $a3
    result = U64(U32(ctx->r15)) * U64(U32(ctx->r7)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x802C5A84: addiu       $t0, $t0, 0x6B30
    ctx->r8 = ADD32(ctx->r8, 0X6B30);
    // 0x802C5A88: lw          $t9, 0x0($t0)
    ctx->r25 = MEM_W(ctx->r8, 0X0);
    // 0x802C5A8C: addiu       $at, $zero, 0x4
    ctx->r1 = ADD32(0, 0X4);
    // 0x802C5A90: addiu       $t4, $zero, 0x1
    ctx->r12 = ADD32(0, 0X1);
    // 0x802C5A94: addiu       $a0, $zero, 0x3C
    ctx->r4 = ADD32(0, 0X3C);
    // 0x802C5A98: mflo        $t8
    ctx->r24 = lo;
    // 0x802C5A9C: addu        $v0, $t8, $t9
    ctx->r2 = ADD32(ctx->r24, ctx->r25);
    // 0x802C5AA0: bne         $v0, $at, L_802C5AB8
    if (ctx->r2 != ctx->r1) {
        // 0x802C5AA4: nop
    
            goto L_802C5AB8;
    }
    // 0x802C5AA4: nop

    // 0x802C5AA8: jal         0x802C6A00
    // 0x802C5AAC: sw          $t4, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r12;
    func_i10_802C6A00(rdram, ctx);
        goto after_0;
    // 0x802C5AAC: sw          $t4, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r12;
    after_0:
    // 0x802C5AB0: b           L_802C5B50
    // 0x802C5AB4: lw          $t4, 0x1C($sp)
    ctx->r12 = MEM_W(ctx->r29, 0X1C);
        goto L_802C5B50;
    // 0x802C5AB4: lw          $t4, 0x1C($sp)
    ctx->r12 = MEM_W(ctx->r29, 0X1C);
L_802C5AB8:
    // 0x802C5AB8: bne         $v0, $a3, L_802C5B10
    if (ctx->r2 != ctx->r7) {
        // 0x802C5ABC: addiu       $t1, $zero, 0x1
        ctx->r9 = ADD32(0, 0X1);
            goto L_802C5B10;
    }
    // 0x802C5ABC: addiu       $t1, $zero, 0x1
    ctx->r9 = ADD32(0, 0X1);
    // 0x802C5AC0: lui         $a2, 0x801D
    ctx->r6 = S32(0X801D << 16);
    // 0x802C5AC4: lui         $a1, 0x800E
    ctx->r5 = S32(0X800E << 16);
    // 0x802C5AC8: lui         $t0, 0x800E
    ctx->r8 = S32(0X800E << 16);
    // 0x802C5ACC: addiu       $t0, $t0, -0x5654
    ctx->r8 = ADD32(ctx->r8, -0X5654);
    // 0x802C5AD0: addiu       $a1, $a1, -0x5678
    ctx->r5 = ADD32(ctx->r5, -0X5678);
    // 0x802C5AD4: addiu       $a2, $a2, -0x4CF8
    ctx->r6 = ADD32(ctx->r6, -0X4CF8);
L_802C5AD8:
    // 0x802C5AD8: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    // 0x802C5ADC: or          $v1, $a2, $zero
    ctx->r3 = ctx->r6 | 0;
    // 0x802C5AE0: or          $a0, $a1, $zero
    ctx->r4 = ctx->r5 | 0;
L_802C5AE4:
    // 0x802C5AE4: lw          $t6, 0x0($a0)
    ctx->r14 = MEM_W(ctx->r4, 0X0);
    // 0x802C5AE8: addiu       $v0, $v0, 0x1
    ctx->r2 = ADD32(ctx->r2, 0X1);
    // 0x802C5AEC: addiu       $v1, $v1, 0x4
    ctx->r3 = ADD32(ctx->r3, 0X4);
    // 0x802C5AF0: addiu       $a0, $a0, 0x4
    ctx->r4 = ADD32(ctx->r4, 0X4);
    // 0x802C5AF4: bne         $v0, $a3, L_802C5AE4
    if (ctx->r2 != ctx->r7) {
        // 0x802C5AF8: sw          $t6, -0x4($v1)
        MEM_W(-0X4, ctx->r3) = ctx->r14;
            goto L_802C5AE4;
    }
    // 0x802C5AF8: sw          $t6, -0x4($v1)
    MEM_W(-0X4, ctx->r3) = ctx->r14;
    // 0x802C5AFC: addiu       $a1, $a1, 0xC
    ctx->r5 = ADD32(ctx->r5, 0XC);
    // 0x802C5B00: bne         $a1, $t0, L_802C5AD8
    if (ctx->r5 != ctx->r8) {
        // 0x802C5B04: addiu       $a2, $a2, 0xC
        ctx->r6 = ADD32(ctx->r6, 0XC);
            goto L_802C5AD8;
    }
    // 0x802C5B04: addiu       $a2, $a2, 0xC
    ctx->r6 = ADD32(ctx->r6, 0XC);
    // 0x802C5B08: b           L_802C5B50
    // 0x802C5B0C: nop

        goto L_802C5B50;
    // 0x802C5B0C: nop

L_802C5B10:
    // 0x802C5B10: sw          $t1, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r9;
    // 0x802C5B14: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C5B18: b           L_802C5B50
    // 0x802C5B1C: sw          $zero, 0x6B38($at)
    MEM_W(0X6B38, ctx->r1) = 0;
        goto L_802C5B50;
    // 0x802C5B1C: sw          $zero, 0x6B38($at)
    MEM_W(0X6B38, ctx->r1) = 0;
L_802C5B20:
    // 0x802C5B20: sw          $t3, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r11;
    // 0x802C5B24: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C5B28: or          $t4, $t1, $zero
    ctx->r12 = ctx->r9 | 0;
    // 0x802C5B2C: b           L_802C5B50
    // 0x802C5B30: sw          $t1, 0x6B38($at)
    MEM_W(0X6B38, ctx->r1) = ctx->r9;
        goto L_802C5B50;
    // 0x802C5B30: sw          $t1, 0x6B38($at)
    MEM_W(0X6B38, ctx->r1) = ctx->r9;
L_802C5B34:
    // 0x802C5B34: sw          $a3, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r7;
    // 0x802C5B38: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C5B3C: addiu       $t4, $zero, 0x1
    ctx->r12 = ADD32(0, 0X1);
    // 0x802C5B40: b           L_802C5B50
    // 0x802C5B44: sw          $t3, 0x6B38($at)
    MEM_W(0X6B38, ctx->r1) = ctx->r11;
        goto L_802C5B50;
    // 0x802C5B44: sw          $t3, 0x6B38($at)
    MEM_W(0X6B38, ctx->r1) = ctx->r11;
    // 0x802C5B48: addiu       $t4, $zero, 0x1
    ctx->r12 = ADD32(0, 0X1);
L_802C5B4C:
    // 0x802C5B4C: sw          $zero, 0x0($v1)
    MEM_W(0X0, ctx->r3) = 0;
L_802C5B50:
    // 0x802C5B50: beq         $t4, $zero, L_802C61F0
    if (ctx->r12 == 0) {
        // 0x802C5B54: addiu       $a0, $zero, 0x11
        ctx->r4 = ADD32(0, 0X11);
            goto L_802C61F0;
    }
    // 0x802C5B54: addiu       $a0, $zero, 0x11
    ctx->r4 = ADD32(0, 0X11);
    // 0x802C5B58: jal         0x800C37F4
    // 0x802C5B5C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_1;
    // 0x802C5B5C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_1:
    // 0x802C5B60: b           L_802C61F4
    // 0x802C5B64: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_802C61F4;
    // 0x802C5B64: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C5B68:
    // 0x802C5B68: andi        $t7, $v0, 0x4000
    ctx->r15 = ctx->r2 & 0X4000;
    // 0x802C5B6C: beql        $t7, $zero, L_802C5C14
    if (ctx->r15 == 0) {
        // 0x802C5B70: lhu         $v0, 0x2($v1)
        ctx->r2 = MEM_HU(ctx->r3, 0X2);
            goto L_802C5C14;
    }
    goto skip_1;
    // 0x802C5B70: lhu         $v0, 0x2($v1)
    ctx->r2 = MEM_HU(ctx->r3, 0X2);
    skip_1:
    // 0x802C5B74: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x802C5B78: addiu       $v1, $v1, -0x19C0
    ctx->r3 = ADD32(ctx->r3, -0X19C0);
    // 0x802C5B7C: lw          $v0, 0x0($v1)
    ctx->r2 = MEM_W(ctx->r3, 0X0);
    // 0x802C5B80: addiu       $t1, $zero, 0x1
    ctx->r9 = ADD32(0, 0X1);
    // 0x802C5B84: addiu       $a0, $zero, 0x3C
    ctx->r4 = ADD32(0, 0X3C);
    // 0x802C5B88: beql        $v0, $zero, L_802C5BBC
    if (ctx->r2 == 0) {
        // 0x802C5B8C: addiu       $t4, $zero, 0x1
        ctx->r12 = ADD32(0, 0X1);
            goto L_802C5BBC;
    }
    goto skip_2;
    // 0x802C5B8C: addiu       $t4, $zero, 0x1
    ctx->r12 = ADD32(0, 0X1);
    skip_2:
    // 0x802C5B90: beq         $v0, $t1, L_802C5BCC
    if (ctx->r2 == ctx->r9) {
        // 0x802C5B94: lui         $at, 0x802C
        ctx->r1 = S32(0X802C << 16);
            goto L_802C5BCC;
    }
    // 0x802C5B94: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C5B98: addiu       $t3, $zero, 0x2
    ctx->r11 = ADD32(0, 0X2);
    // 0x802C5B9C: beq         $v0, $t3, L_802C5BDC
    if (ctx->r2 == ctx->r11) {
        // 0x802C5BA0: lui         $at, 0x802C
        ctx->r1 = S32(0X802C << 16);
            goto L_802C5BDC;
    }
    // 0x802C5BA0: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C5BA4: addiu       $a3, $zero, 0x3
    ctx->r7 = ADD32(0, 0X3);
    // 0x802C5BA8: beq         $v0, $a3, L_802C5BEC
    if (ctx->r2 == ctx->r7) {
        // 0x802C5BAC: lui         $at, 0x802C
        ctx->r1 = S32(0X802C << 16);
            goto L_802C5BEC;
    }
    // 0x802C5BAC: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C5BB0: b           L_802C5BF8
    // 0x802C5BB4: nop

        goto L_802C5BF8;
    // 0x802C5BB4: nop

    // 0x802C5BB8: addiu       $t4, $zero, 0x1
    ctx->r12 = ADD32(0, 0X1);
L_802C5BBC:
    // 0x802C5BBC: jal         0x802C6A00
    // 0x802C5BC0: sw          $t4, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r12;
    func_i10_802C6A00(rdram, ctx);
        goto after_2;
    // 0x802C5BC0: sw          $t4, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r12;
    after_2:
    // 0x802C5BC4: b           L_802C5BF8
    // 0x802C5BC8: lw          $t4, 0x1C($sp)
    ctx->r12 = MEM_W(ctx->r29, 0X1C);
        goto L_802C5BF8;
    // 0x802C5BC8: lw          $t4, 0x1C($sp)
    ctx->r12 = MEM_W(ctx->r29, 0X1C);
L_802C5BCC:
    // 0x802C5BCC: sw          $zero, 0x0($v1)
    MEM_W(0X0, ctx->r3) = 0;
    // 0x802C5BD0: addiu       $t4, $zero, 0x1
    ctx->r12 = ADD32(0, 0X1);
    // 0x802C5BD4: b           L_802C5BF8
    // 0x802C5BD8: sw          $zero, 0x6B38($at)
    MEM_W(0X6B38, ctx->r1) = 0;
        goto L_802C5BF8;
    // 0x802C5BD8: sw          $zero, 0x6B38($at)
    MEM_W(0X6B38, ctx->r1) = 0;
L_802C5BDC:
    // 0x802C5BDC: sw          $t1, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r9;
    // 0x802C5BE0: or          $t4, $t1, $zero
    ctx->r12 = ctx->r9 | 0;
    // 0x802C5BE4: b           L_802C5BF8
    // 0x802C5BE8: sw          $zero, 0x6B38($at)
    MEM_W(0X6B38, ctx->r1) = 0;
        goto L_802C5BF8;
    // 0x802C5BE8: sw          $zero, 0x6B38($at)
    MEM_W(0X6B38, ctx->r1) = 0;
L_802C5BEC:
    // 0x802C5BEC: sw          $t3, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r11;
    // 0x802C5BF0: or          $t4, $t1, $zero
    ctx->r12 = ctx->r9 | 0;
    // 0x802C5BF4: sw          $t1, 0x6B38($at)
    MEM_W(0X6B38, ctx->r1) = ctx->r9;
L_802C5BF8:
    // 0x802C5BF8: beq         $t4, $zero, L_802C61F0
    if (ctx->r12 == 0) {
        // 0x802C5BFC: addiu       $a0, $zero, 0x16
        ctx->r4 = ADD32(0, 0X16);
            goto L_802C61F0;
    }
    // 0x802C5BFC: addiu       $a0, $zero, 0x16
    ctx->r4 = ADD32(0, 0X16);
    // 0x802C5C00: jal         0x800C37F4
    // 0x802C5C04: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_3;
    // 0x802C5C04: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_3:
    // 0x802C5C08: b           L_802C61F4
    // 0x802C5C0C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_802C61F4;
    // 0x802C5C0C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x802C5C10: lhu         $v0, 0x2($v1)
    ctx->r2 = MEM_HU(ctx->r3, 0X2);
L_802C5C14:
    // 0x802C5C14: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x802C5C18: addiu       $v1, $v1, -0x19C0
    ctx->r3 = ADD32(ctx->r3, -0X19C0);
    // 0x802C5C1C: andi        $t8, $v0, 0x800
    ctx->r24 = ctx->r2 & 0X800;
    // 0x802C5C20: beq         $t8, $zero, L_802C5D60
    if (ctx->r24 == 0) {
        // 0x802C5C24: andi        $t9, $v0, 0x400
        ctx->r25 = ctx->r2 & 0X400;
            goto L_802C5D60;
    }
    // 0x802C5C24: andi        $t9, $v0, 0x400
    ctx->r25 = ctx->r2 & 0X400;
    // 0x802C5C28: lw          $t9, 0x0($v1)
    ctx->r25 = MEM_W(ctx->r3, 0X0);
    // 0x802C5C2C: lui         $a1, 0x802C
    ctx->r5 = S32(0X802C << 16);
    // 0x802C5C30: addiu       $a1, $a1, 0x6B34
    ctx->r5 = ADD32(ctx->r5, 0X6B34);
    // 0x802C5C34: bne         $t9, $zero, L_802C5D48
    if (ctx->r25 != 0) {
        // 0x802C5C38: lui         $t2, 0x802C
        ctx->r10 = S32(0X802C << 16);
            goto L_802C5D48;
    }
    // 0x802C5C38: lui         $t2, 0x802C
    ctx->r10 = S32(0X802C << 16);
    // 0x802C5C3C: lw          $a0, 0x0($a1)
    ctx->r4 = MEM_W(ctx->r5, 0X0);
    // 0x802C5C40: addiu       $t1, $zero, 0x1
    ctx->r9 = ADD32(0, 0X1);
    // 0x802C5C44: or          $t4, $t1, $zero
    ctx->r12 = ctx->r9 | 0;
    // 0x802C5C48: bne         $t1, $a0, L_802C5C70
    if (ctx->r9 != ctx->r4) {
        // 0x802C5C4C: addiu       $t7, $a0, -0x1
        ctx->r15 = ADD32(ctx->r4, -0X1);
            goto L_802C5C70;
    }
    // 0x802C5C4C: addiu       $t7, $a0, -0x1
    ctx->r15 = ADD32(ctx->r4, -0X1);
    // 0x802C5C50: lui         $t5, 0x802C
    ctx->r13 = S32(0X802C << 16);
    // 0x802C5C54: addiu       $t5, $t5, 0x6B10
    ctx->r13 = ADD32(ctx->r13, 0X6B10);
    // 0x802C5C58: lw          $v0, 0x0($t5)
    ctx->r2 = MEM_W(ctx->r13, 0X0);
    // 0x802C5C5C: addiu       $v1, $zero, -0x1
    ctx->r3 = ADD32(0, -0X1);
    // 0x802C5C60: lui         $t0, 0x802C
    ctx->r8 = S32(0X802C << 16);
    // 0x802C5C64: beq         $v1, $v0, L_802C5C70
    if (ctx->r3 == ctx->r2) {
        // 0x802C5C68: addiu       $t0, $t0, 0x6B30
        ctx->r8 = ADD32(ctx->r8, 0X6B30);
            goto L_802C5C70;
    }
    // 0x802C5C68: addiu       $t0, $t0, 0x6B30
    ctx->r8 = ADD32(ctx->r8, 0X6B30);
    // 0x802C5C6C: sw          $v0, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r2;
L_802C5C70:
    // 0x802C5C70: lw          $t2, 0x6B14($t2)
    ctx->r10 = MEM_W(ctx->r10, 0X6B14);
    // 0x802C5C74: lui         $t0, 0x802C
    ctx->r8 = S32(0X802C << 16);
    // 0x802C5C78: lui         $t5, 0x802C
    ctx->r13 = S32(0X802C << 16);
    // 0x802C5C7C: addiu       $t5, $t5, 0x6B10
    ctx->r13 = ADD32(ctx->r13, 0X6B10);
    // 0x802C5C80: bne         $t1, $t2, L_802C5C98
    if (ctx->r9 != ctx->r10) {
        // 0x802C5C84: addiu       $t0, $t0, 0x6B30
        ctx->r8 = ADD32(ctx->r8, 0X6B30);
            goto L_802C5C98;
    }
    // 0x802C5C84: addiu       $t0, $t0, 0x6B30
    ctx->r8 = ADD32(ctx->r8, 0X6B30);
    // 0x802C5C88: bne         $t1, $a0, L_802C5C98
    if (ctx->r9 != ctx->r4) {
        // 0x802C5C8C: addiu       $a3, $zero, 0x3
        ctx->r7 = ADD32(0, 0X3);
            goto L_802C5C98;
    }
    // 0x802C5C8C: addiu       $a3, $zero, 0x3
    ctx->r7 = ADD32(0, 0X3);
    // 0x802C5C90: b           L_802C5CC0
    // 0x802C5C94: sw          $zero, 0x0($t0)
    MEM_W(0X0, ctx->r8) = 0;
        goto L_802C5CC0;
    // 0x802C5C94: sw          $zero, 0x0($t0)
    MEM_W(0X0, ctx->r8) = 0;
L_802C5C98:
    // 0x802C5C98: addiu       $a3, $zero, 0x3
    ctx->r7 = ADD32(0, 0X3);
    // 0x802C5C9C: bnel        $a3, $t2, L_802C5CC4
    if (ctx->r7 != ctx->r10) {
        // 0x802C5CA0: addiu       $t3, $zero, 0x2
        ctx->r11 = ADD32(0, 0X2);
            goto L_802C5CC4;
    }
    goto skip_3;
    // 0x802C5CA0: addiu       $t3, $zero, 0x2
    ctx->r11 = ADD32(0, 0X2);
    skip_3:
    // 0x802C5CA4: bnel        $a0, $zero, L_802C5CC4
    if (ctx->r4 != 0) {
        // 0x802C5CA8: addiu       $t3, $zero, 0x2
        ctx->r11 = ADD32(0, 0X2);
            goto L_802C5CC4;
    }
    goto skip_4;
    // 0x802C5CA8: addiu       $t3, $zero, 0x2
    ctx->r11 = ADD32(0, 0X2);
    skip_4:
    // 0x802C5CAC: lw          $t6, 0x0($t0)
    ctx->r14 = MEM_W(ctx->r8, 0X0);
    // 0x802C5CB0: addiu       $t3, $zero, 0x2
    ctx->r11 = ADD32(0, 0X2);
    // 0x802C5CB4: bnel        $t3, $t6, L_802C5CC4
    if (ctx->r11 != ctx->r14) {
        // 0x802C5CB8: addiu       $t3, $zero, 0x2
        ctx->r11 = ADD32(0, 0X2);
            goto L_802C5CC4;
    }
    goto skip_5;
    // 0x802C5CB8: addiu       $t3, $zero, 0x2
    ctx->r11 = ADD32(0, 0X2);
    skip_5:
    // 0x802C5CBC: sw          $t1, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r9;
L_802C5CC0:
    // 0x802C5CC0: addiu       $t3, $zero, 0x2
    ctx->r11 = ADD32(0, 0X2);
L_802C5CC4:
    // 0x802C5CC4: sw          $t7, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r15;
    // 0x802C5CC8: or          $a0, $t7, $zero
    ctx->r4 = ctx->r15 | 0;
    // 0x802C5CCC: bgez        $t7, L_802C5CDC
    if (SIGNED(ctx->r15) >= 0) {
        // 0x802C5CD0: lw          $v1, 0x0($t0)
        ctx->r3 = MEM_W(ctx->r8, 0X0);
            goto L_802C5CDC;
    }
    // 0x802C5CD0: lw          $v1, 0x0($t0)
    ctx->r3 = MEM_W(ctx->r8, 0X0);
    // 0x802C5CD4: sw          $t1, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r9;
    // 0x802C5CD8: or          $a0, $t1, $zero
    ctx->r4 = ctx->r9 | 0;
L_802C5CDC:
    // 0x802C5CDC: lui         $a2, 0x802C
    ctx->r6 = S32(0X802C << 16);
    // 0x802C5CE0: addiu       $a2, $a2, 0x6B40
    ctx->r6 = ADD32(ctx->r6, 0X6B40);
L_802C5CE4:
    // 0x802C5CE4: multu       $a0, $a3
    result = U64(U32(ctx->r4)) * U64(U32(ctx->r7)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x802C5CE8: mflo        $t8
    ctx->r24 = lo;
    // 0x802C5CEC: addu        $v0, $t8, $v1
    ctx->r2 = ADD32(ctx->r24, ctx->r3);
    // 0x802C5CF0: sll         $t9, $v0, 2
    ctx->r25 = S32(ctx->r2 << 2);
    // 0x802C5CF4: addu        $t6, $a2, $t9
    ctx->r14 = ADD32(ctx->r6, ctx->r25);
    // 0x802C5CF8: lw          $t7, 0x0($t6)
    ctx->r15 = MEM_W(ctx->r14, 0X0);
    // 0x802C5CFC: addiu       $t8, $a0, -0x1
    ctx->r24 = ADD32(ctx->r4, -0X1);
    // 0x802C5D00: bne         $t7, $zero, L_802C5D20
    if (ctx->r15 != 0) {
        // 0x802C5D04: nop
    
            goto L_802C5D20;
    }
    // 0x802C5D04: nop

    // 0x802C5D08: sw          $t8, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r24;
    // 0x802C5D0C: bgez        $t8, L_802C5CE4
    if (SIGNED(ctx->r24) >= 0) {
        // 0x802C5D10: or          $a0, $t8, $zero
        ctx->r4 = ctx->r24 | 0;
            goto L_802C5CE4;
    }
    // 0x802C5D10: or          $a0, $t8, $zero
    ctx->r4 = ctx->r24 | 0;
    // 0x802C5D14: sw          $t1, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r9;
    // 0x802C5D18: b           L_802C5CE4
    // 0x802C5D1C: or          $a0, $t1, $zero
    ctx->r4 = ctx->r9 | 0;
        goto L_802C5CE4;
    // 0x802C5D1C: or          $a0, $t1, $zero
    ctx->r4 = ctx->r9 | 0;
L_802C5D20:
    // 0x802C5D20: bne         $t1, $a0, L_802C5D48
    if (ctx->r9 != ctx->r4) {
        // 0x802C5D24: nop
    
            goto L_802C5D48;
    }
    // 0x802C5D24: nop

    // 0x802C5D28: bne         $a3, $t2, L_802C5D34
    if (ctx->r7 != ctx->r10) {
        // 0x802C5D2C: nop
    
            goto L_802C5D34;
    }
    // 0x802C5D2C: nop

    // 0x802C5D30: sw          $v1, 0x0($t5)
    MEM_W(0X0, ctx->r13) = ctx->r3;
L_802C5D34:
    // 0x802C5D34: bne         $a3, $t2, L_802C5D48
    if (ctx->r7 != ctx->r10) {
        // 0x802C5D38: nop
    
            goto L_802C5D48;
    }
    // 0x802C5D38: nop

    // 0x802C5D3C: bne         $t3, $v1, L_802C5D48
    if (ctx->r11 != ctx->r3) {
        // 0x802C5D40: nop
    
            goto L_802C5D48;
    }
    // 0x802C5D40: nop

    // 0x802C5D44: sw          $t1, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r9;
L_802C5D48:
    // 0x802C5D48: beq         $t4, $zero, L_802C61F0
    if (ctx->r12 == 0) {
        // 0x802C5D4C: addiu       $a0, $zero, 0x10
        ctx->r4 = ADD32(0, 0X10);
            goto L_802C61F0;
    }
    // 0x802C5D4C: addiu       $a0, $zero, 0x10
    ctx->r4 = ADD32(0, 0X10);
    // 0x802C5D50: jal         0x800C37F4
    // 0x802C5D54: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_4;
    // 0x802C5D54: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_4:
    // 0x802C5D58: b           L_802C61F4
    // 0x802C5D5C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_802C61F4;
    // 0x802C5D5C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C5D60:
    // 0x802C5D60: beq         $t9, $zero, L_802C5EB4
    if (ctx->r25 == 0) {
        // 0x802C5D64: andi        $t6, $v0, 0x200
        ctx->r14 = ctx->r2 & 0X200;
            goto L_802C5EB4;
    }
    // 0x802C5D64: andi        $t6, $v0, 0x200
    ctx->r14 = ctx->r2 & 0X200;
    // 0x802C5D68: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x802C5D6C: addiu       $v1, $v1, -0x19C0
    ctx->r3 = ADD32(ctx->r3, -0X19C0);
    // 0x802C5D70: lw          $t6, 0x0($v1)
    ctx->r14 = MEM_W(ctx->r3, 0X0);
    // 0x802C5D74: lui         $a1, 0x802C
    ctx->r5 = S32(0X802C << 16);
    // 0x802C5D78: addiu       $a1, $a1, 0x6B34
    ctx->r5 = ADD32(ctx->r5, 0X6B34);
    // 0x802C5D7C: bne         $t6, $zero, L_802C5E9C
    if (ctx->r14 != 0) {
        // 0x802C5D80: lui         $t2, 0x802C
        ctx->r10 = S32(0X802C << 16);
            goto L_802C5E9C;
    }
    // 0x802C5D80: lui         $t2, 0x802C
    ctx->r10 = S32(0X802C << 16);
    // 0x802C5D84: lw          $a0, 0x0($a1)
    ctx->r4 = MEM_W(ctx->r5, 0X0);
    // 0x802C5D88: addiu       $t1, $zero, 0x1
    ctx->r9 = ADD32(0, 0X1);
    // 0x802C5D8C: or          $t4, $t1, $zero
    ctx->r12 = ctx->r9 | 0;
    // 0x802C5D90: bne         $t1, $a0, L_802C5DBC
    if (ctx->r9 != ctx->r4) {
        // 0x802C5D94: addiu       $t8, $a0, 0x1
        ctx->r24 = ADD32(ctx->r4, 0X1);
            goto L_802C5DBC;
    }
    // 0x802C5D94: addiu       $t8, $a0, 0x1
    ctx->r24 = ADD32(ctx->r4, 0X1);
    // 0x802C5D98: lui         $t5, 0x802C
    ctx->r13 = S32(0X802C << 16);
    // 0x802C5D9C: addiu       $t5, $t5, 0x6B10
    ctx->r13 = ADD32(ctx->r13, 0X6B10);
    // 0x802C5DA0: lw          $v0, 0x0($t5)
    ctx->r2 = MEM_W(ctx->r13, 0X0);
    // 0x802C5DA4: addiu       $v1, $zero, -0x1
    ctx->r3 = ADD32(0, -0X1);
    // 0x802C5DA8: lui         $t0, 0x802C
    ctx->r8 = S32(0X802C << 16);
    // 0x802C5DAC: beq         $v1, $v0, L_802C5DBC
    if (ctx->r3 == ctx->r2) {
        // 0x802C5DB0: addiu       $t0, $t0, 0x6B30
        ctx->r8 = ADD32(ctx->r8, 0X6B30);
            goto L_802C5DBC;
    }
    // 0x802C5DB0: addiu       $t0, $t0, 0x6B30
    ctx->r8 = ADD32(ctx->r8, 0X6B30);
    // 0x802C5DB4: sw          $v0, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r2;
    // 0x802C5DB8: sw          $v1, 0x0($t5)
    MEM_W(0X0, ctx->r13) = ctx->r3;
L_802C5DBC:
    // 0x802C5DBC: lw          $t2, 0x6B14($t2)
    ctx->r10 = MEM_W(ctx->r10, 0X6B14);
    // 0x802C5DC0: lui         $t0, 0x802C
    ctx->r8 = S32(0X802C << 16);
    // 0x802C5DC4: lui         $t5, 0x802C
    ctx->r13 = S32(0X802C << 16);
    // 0x802C5DC8: addiu       $t5, $t5, 0x6B10
    ctx->r13 = ADD32(ctx->r13, 0X6B10);
    // 0x802C5DCC: bne         $t1, $t2, L_802C5DE4
    if (ctx->r9 != ctx->r10) {
        // 0x802C5DD0: addiu       $t0, $t0, 0x6B30
        ctx->r8 = ADD32(ctx->r8, 0X6B30);
            goto L_802C5DE4;
    }
    // 0x802C5DD0: addiu       $t0, $t0, 0x6B30
    ctx->r8 = ADD32(ctx->r8, 0X6B30);
    // 0x802C5DD4: bne         $t1, $a0, L_802C5DE4
    if (ctx->r9 != ctx->r4) {
        // 0x802C5DD8: addiu       $a3, $zero, 0x3
        ctx->r7 = ADD32(0, 0X3);
            goto L_802C5DE4;
    }
    // 0x802C5DD8: addiu       $a3, $zero, 0x3
    ctx->r7 = ADD32(0, 0X3);
    // 0x802C5DDC: b           L_802C5E0C
    // 0x802C5DE0: sw          $zero, 0x0($t0)
    MEM_W(0X0, ctx->r8) = 0;
        goto L_802C5E0C;
    // 0x802C5DE0: sw          $zero, 0x0($t0)
    MEM_W(0X0, ctx->r8) = 0;
L_802C5DE4:
    // 0x802C5DE4: addiu       $a3, $zero, 0x3
    ctx->r7 = ADD32(0, 0X3);
    // 0x802C5DE8: bnel        $a3, $t2, L_802C5E10
    if (ctx->r7 != ctx->r10) {
        // 0x802C5DEC: slti        $at, $t8, 0x2
        ctx->r1 = SIGNED(ctx->r24) < 0X2 ? 1 : 0;
            goto L_802C5E10;
    }
    goto skip_6;
    // 0x802C5DEC: slti        $at, $t8, 0x2
    ctx->r1 = SIGNED(ctx->r24) < 0X2 ? 1 : 0;
    skip_6:
    // 0x802C5DF0: bnel        $a0, $zero, L_802C5E10
    if (ctx->r4 != 0) {
        // 0x802C5DF4: slti        $at, $t8, 0x2
        ctx->r1 = SIGNED(ctx->r24) < 0X2 ? 1 : 0;
            goto L_802C5E10;
    }
    goto skip_7;
    // 0x802C5DF4: slti        $at, $t8, 0x2
    ctx->r1 = SIGNED(ctx->r24) < 0X2 ? 1 : 0;
    skip_7:
    // 0x802C5DF8: lw          $t7, 0x0($t0)
    ctx->r15 = MEM_W(ctx->r8, 0X0);
    // 0x802C5DFC: addiu       $t3, $zero, 0x2
    ctx->r11 = ADD32(0, 0X2);
    // 0x802C5E00: bnel        $t3, $t7, L_802C5E10
    if (ctx->r11 != ctx->r15) {
        // 0x802C5E04: slti        $at, $t8, 0x2
        ctx->r1 = SIGNED(ctx->r24) < 0X2 ? 1 : 0;
            goto L_802C5E10;
    }
    goto skip_8;
    // 0x802C5E04: slti        $at, $t8, 0x2
    ctx->r1 = SIGNED(ctx->r24) < 0X2 ? 1 : 0;
    skip_8:
    // 0x802C5E08: sw          $t1, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r9;
L_802C5E0C:
    // 0x802C5E0C: slti        $at, $t8, 0x2
    ctx->r1 = SIGNED(ctx->r24) < 0X2 ? 1 : 0;
L_802C5E10:
    // 0x802C5E10: addiu       $t3, $zero, 0x2
    ctx->r11 = ADD32(0, 0X2);
    // 0x802C5E14: sw          $t8, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r24;
    // 0x802C5E18: or          $a0, $t8, $zero
    ctx->r4 = ctx->r24 | 0;
    // 0x802C5E1C: bne         $at, $zero, L_802C5E2C
    if (ctx->r1 != 0) {
        // 0x802C5E20: lw          $v1, 0x0($t0)
        ctx->r3 = MEM_W(ctx->r8, 0X0);
            goto L_802C5E2C;
    }
    // 0x802C5E20: lw          $v1, 0x0($t0)
    ctx->r3 = MEM_W(ctx->r8, 0X0);
    // 0x802C5E24: sw          $zero, 0x0($a1)
    MEM_W(0X0, ctx->r5) = 0;
    // 0x802C5E28: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
L_802C5E2C:
    // 0x802C5E2C: lui         $a2, 0x802C
    ctx->r6 = S32(0X802C << 16);
    // 0x802C5E30: addiu       $a2, $a2, 0x6B40
    ctx->r6 = ADD32(ctx->r6, 0X6B40);
L_802C5E34:
    // 0x802C5E34: multu       $a0, $a3
    result = U64(U32(ctx->r4)) * U64(U32(ctx->r7)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x802C5E38: mflo        $t9
    ctx->r25 = lo;
    // 0x802C5E3C: addu        $v0, $t9, $v1
    ctx->r2 = ADD32(ctx->r25, ctx->r3);
    // 0x802C5E40: sll         $t6, $v0, 2
    ctx->r14 = S32(ctx->r2 << 2);
    // 0x802C5E44: addu        $t7, $a2, $t6
    ctx->r15 = ADD32(ctx->r6, ctx->r14);
    // 0x802C5E48: lw          $t8, 0x0($t7)
    ctx->r24 = MEM_W(ctx->r15, 0X0);
    // 0x802C5E4C: addiu       $t9, $a0, 0x1
    ctx->r25 = ADD32(ctx->r4, 0X1);
    // 0x802C5E50: slti        $at, $t9, 0x2
    ctx->r1 = SIGNED(ctx->r25) < 0X2 ? 1 : 0;
    // 0x802C5E54: bne         $t8, $zero, L_802C5E74
    if (ctx->r24 != 0) {
        // 0x802C5E58: nop
    
            goto L_802C5E74;
    }
    // 0x802C5E58: nop

    // 0x802C5E5C: sw          $t9, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r25;
    // 0x802C5E60: bne         $at, $zero, L_802C5E34
    if (ctx->r1 != 0) {
        // 0x802C5E64: or          $a0, $t9, $zero
        ctx->r4 = ctx->r25 | 0;
            goto L_802C5E34;
    }
    // 0x802C5E64: or          $a0, $t9, $zero
    ctx->r4 = ctx->r25 | 0;
    // 0x802C5E68: sw          $zero, 0x0($a1)
    MEM_W(0X0, ctx->r5) = 0;
    // 0x802C5E6C: b           L_802C5E34
    // 0x802C5E70: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
        goto L_802C5E34;
    // 0x802C5E70: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
L_802C5E74:
    // 0x802C5E74: bne         $t1, $a0, L_802C5E9C
    if (ctx->r9 != ctx->r4) {
        // 0x802C5E78: nop
    
            goto L_802C5E9C;
    }
    // 0x802C5E78: nop

    // 0x802C5E7C: bne         $a3, $t2, L_802C5E88
    if (ctx->r7 != ctx->r10) {
        // 0x802C5E80: nop
    
            goto L_802C5E88;
    }
    // 0x802C5E80: nop

    // 0x802C5E84: sw          $v1, 0x0($t5)
    MEM_W(0X0, ctx->r13) = ctx->r3;
L_802C5E88:
    // 0x802C5E88: bne         $a3, $t2, L_802C5E9C
    if (ctx->r7 != ctx->r10) {
        // 0x802C5E8C: nop
    
            goto L_802C5E9C;
    }
    // 0x802C5E8C: nop

    // 0x802C5E90: bne         $t3, $v1, L_802C5E9C
    if (ctx->r11 != ctx->r3) {
        // 0x802C5E94: nop
    
            goto L_802C5E9C;
    }
    // 0x802C5E94: nop

    // 0x802C5E98: sw          $t1, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r9;
L_802C5E9C:
    // 0x802C5E9C: beq         $t4, $zero, L_802C61F0
    if (ctx->r12 == 0) {
        // 0x802C5EA0: addiu       $a0, $zero, 0x10
        ctx->r4 = ADD32(0, 0X10);
            goto L_802C61F0;
    }
    // 0x802C5EA0: addiu       $a0, $zero, 0x10
    ctx->r4 = ADD32(0, 0X10);
    // 0x802C5EA4: jal         0x800C37F4
    // 0x802C5EA8: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_5;
    // 0x802C5EA8: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_5:
    // 0x802C5EAC: b           L_802C61F4
    // 0x802C5EB0: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_802C61F4;
    // 0x802C5EB0: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C5EB4:
    // 0x802C5EB4: beq         $t6, $zero, L_802C604C
    if (ctx->r14 == 0) {
        // 0x802C5EB8: andi        $t8, $v0, 0x100
        ctx->r24 = ctx->r2 & 0X100;
            goto L_802C604C;
    }
    // 0x802C5EB8: andi        $t8, $v0, 0x100
    ctx->r24 = ctx->r2 & 0X100;
    // 0x802C5EBC: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x802C5EC0: addiu       $v1, $v1, -0x19C0
    ctx->r3 = ADD32(ctx->r3, -0X19C0);
    // 0x802C5EC4: lw          $v0, 0x0($v1)
    ctx->r2 = MEM_W(ctx->r3, 0X0);
    // 0x802C5EC8: lui         $t0, 0x802C
    ctx->r8 = S32(0X802C << 16);
    // 0x802C5ECC: addiu       $t0, $t0, 0x6B30
    ctx->r8 = ADD32(ctx->r8, 0X6B30);
    // 0x802C5ED0: beq         $v0, $zero, L_802C5EFC
    if (ctx->r2 == 0) {
        // 0x802C5ED4: addiu       $t1, $zero, 0x1
        ctx->r9 = ADD32(0, 0X1);
            goto L_802C5EFC;
    }
    // 0x802C5ED4: addiu       $t1, $zero, 0x1
    ctx->r9 = ADD32(0, 0X1);
    // 0x802C5ED8: addiu       $t1, $zero, 0x1
    ctx->r9 = ADD32(0, 0X1);
    // 0x802C5EDC: beq         $v0, $t1, L_802C5FAC
    if (ctx->r2 == ctx->r9) {
        // 0x802C5EE0: addiu       $t3, $zero, 0x2
        ctx->r11 = ADD32(0, 0X2);
            goto L_802C5FAC;
    }
    // 0x802C5EE0: addiu       $t3, $zero, 0x2
    ctx->r11 = ADD32(0, 0X2);
    // 0x802C5EE4: beq         $v0, $t3, L_802C5FAC
    if (ctx->r2 == ctx->r11) {
        // 0x802C5EE8: addiu       $a3, $zero, 0x3
        ctx->r7 = ADD32(0, 0X3);
            goto L_802C5FAC;
    }
    // 0x802C5EE8: addiu       $a3, $zero, 0x3
    ctx->r7 = ADD32(0, 0X3);
    // 0x802C5EEC: beq         $v0, $a3, L_802C5FB0
    if (ctx->r2 == ctx->r7) {
        // 0x802C5EF0: nop
    
            goto L_802C5FB0;
    }
    // 0x802C5EF0: nop

    // 0x802C5EF4: b           L_802C6034
    // 0x802C5EF8: nop

        goto L_802C6034;
    // 0x802C5EF8: nop

L_802C5EFC:
    // 0x802C5EFC: lw          $t7, 0x0($t0)
    ctx->r15 = MEM_W(ctx->r8, 0X0);
    // 0x802C5F00: addiu       $t4, $zero, 0x1
    ctx->r12 = ADD32(0, 0X1);
    // 0x802C5F04: addiu       $t3, $zero, 0x2
    ctx->r11 = ADD32(0, 0X2);
    // 0x802C5F08: addiu       $v1, $t7, -0x1
    ctx->r3 = ADD32(ctx->r15, -0X1);
    // 0x802C5F0C: bgez        $v1, L_802C5F3C
    if (SIGNED(ctx->r3) >= 0) {
        // 0x802C5F10: sw          $v1, 0x0($t0)
        MEM_W(0X0, ctx->r8) = ctx->r3;
            goto L_802C5F3C;
    }
    // 0x802C5F10: sw          $v1, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r3;
    // 0x802C5F14: lui         $a1, 0x802C
    ctx->r5 = S32(0X802C << 16);
    // 0x802C5F18: addiu       $a1, $a1, 0x6B34
    ctx->r5 = ADD32(ctx->r5, 0X6B34);
    // 0x802C5F1C: lw          $t9, 0x0($a1)
    ctx->r25 = MEM_W(ctx->r5, 0X0);
    // 0x802C5F20: addiu       $v1, $zero, 0x1
    ctx->r3 = ADD32(0, 0X1);
    // 0x802C5F24: bnel        $t9, $zero, L_802C5F3C
    if (ctx->r25 != 0) {
        // 0x802C5F28: sw          $v1, 0x0($t0)
        MEM_W(0X0, ctx->r8) = ctx->r3;
            goto L_802C5F3C;
    }
    goto skip_9;
    // 0x802C5F28: sw          $v1, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r3;
    skip_9:
    // 0x802C5F2C: addiu       $v1, $zero, 0x2
    ctx->r3 = ADD32(0, 0X2);
    // 0x802C5F30: b           L_802C5F3C
    // 0x802C5F34: sw          $v1, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r3;
        goto L_802C5F3C;
    // 0x802C5F34: sw          $v1, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r3;
    // 0x802C5F38: sw          $v1, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r3;
L_802C5F3C:
    // 0x802C5F3C: lui         $a0, 0x802C
    ctx->r4 = S32(0X802C << 16);
    // 0x802C5F40: lw          $a0, 0x6B34($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X6B34);
    // 0x802C5F44: lui         $a2, 0x802C
    ctx->r6 = S32(0X802C << 16);
    // 0x802C5F48: addiu       $a2, $a2, 0x6B40
    ctx->r6 = ADD32(ctx->r6, 0X6B40);
    // 0x802C5F4C: sll         $a1, $a0, 2
    ctx->r5 = S32(ctx->r4 << 2);
    // 0x802C5F50: subu        $a1, $a1, $a0
    ctx->r5 = SUB32(ctx->r5, ctx->r4);
L_802C5F54:
    // 0x802C5F54: addu        $v0, $a1, $v1
    ctx->r2 = ADD32(ctx->r5, ctx->r3);
    // 0x802C5F58: sll         $t6, $v0, 2
    ctx->r14 = S32(ctx->r2 << 2);
    // 0x802C5F5C: addu        $t7, $a2, $t6
    ctx->r15 = ADD32(ctx->r6, ctx->r14);
    // 0x802C5F60: lw          $t8, 0x0($t7)
    ctx->r24 = MEM_W(ctx->r15, 0X0);
    // 0x802C5F64: lui         $t5, 0x802C
    ctx->r13 = S32(0X802C << 16);
    // 0x802C5F68: addiu       $t5, $t5, 0x6B10
    ctx->r13 = ADD32(ctx->r13, 0X6B10);
    // 0x802C5F6C: beql        $t8, $zero, L_802C5F84
    if (ctx->r24 == 0) {
        // 0x802C5F70: addiu       $t9, $v1, -0x1
        ctx->r25 = ADD32(ctx->r3, -0X1);
            goto L_802C5F84;
    }
    goto skip_10;
    // 0x802C5F70: addiu       $t9, $v1, -0x1
    ctx->r25 = ADD32(ctx->r3, -0X1);
    skip_10:
    // 0x802C5F74: addiu       $v1, $zero, -0x1
    ctx->r3 = ADD32(0, -0X1);
    // 0x802C5F78: b           L_802C6034
    // 0x802C5F7C: sw          $v1, 0x0($t5)
    MEM_W(0X0, ctx->r13) = ctx->r3;
        goto L_802C6034;
    // 0x802C5F7C: sw          $v1, 0x0($t5)
    MEM_W(0X0, ctx->r13) = ctx->r3;
    // 0x802C5F80: addiu       $t9, $v1, -0x1
    ctx->r25 = ADD32(ctx->r3, -0X1);
L_802C5F84:
    // 0x802C5F84: sw          $t9, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r25;
    // 0x802C5F88: bgez        $t9, L_802C5F54
    if (SIGNED(ctx->r25) >= 0) {
        // 0x802C5F8C: or          $v1, $t9, $zero
        ctx->r3 = ctx->r25 | 0;
            goto L_802C5F54;
    }
    // 0x802C5F8C: or          $v1, $t9, $zero
    ctx->r3 = ctx->r25 | 0;
    // 0x802C5F90: bne         $a0, $zero, L_802C5FA4
    if (ctx->r4 != 0) {
        // 0x802C5F94: or          $v1, $t1, $zero
        ctx->r3 = ctx->r9 | 0;
            goto L_802C5FA4;
    }
    // 0x802C5F94: or          $v1, $t1, $zero
    ctx->r3 = ctx->r9 | 0;
    // 0x802C5F98: sw          $t3, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r11;
    // 0x802C5F9C: b           L_802C5F54
    // 0x802C5FA0: or          $v1, $t3, $zero
    ctx->r3 = ctx->r11 | 0;
        goto L_802C5F54;
    // 0x802C5FA0: or          $v1, $t3, $zero
    ctx->r3 = ctx->r11 | 0;
L_802C5FA4:
    // 0x802C5FA4: b           L_802C5F54
    // 0x802C5FA8: sw          $t1, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r9;
        goto L_802C5F54;
    // 0x802C5FA8: sw          $t1, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r9;
L_802C5FAC:
    // 0x802C5FAC: addiu       $a3, $zero, 0x3
    ctx->r7 = ADD32(0, 0X3);
L_802C5FB0:
    // 0x802C5FB0: lui         $a1, 0x802C
    ctx->r5 = S32(0X802C << 16);
    // 0x802C5FB4: addiu       $a1, $a1, 0x6B34
    ctx->r5 = ADD32(ctx->r5, 0X6B34);
    // 0x802C5FB8: lw          $t6, 0x0($a1)
    ctx->r14 = MEM_W(ctx->r5, 0X0);
    // 0x802C5FBC: lui         $t0, 0x802C
    ctx->r8 = S32(0X802C << 16);
    // 0x802C5FC0: addiu       $t0, $t0, 0x6B30
    ctx->r8 = ADD32(ctx->r8, 0X6B30);
    // 0x802C5FC4: multu       $t6, $a3
    result = U64(U32(ctx->r14)) * U64(U32(ctx->r7)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x802C5FC8: lw          $t8, 0x0($t0)
    ctx->r24 = MEM_W(ctx->r8, 0X0);
    // 0x802C5FCC: lui         $a2, 0x802C
    ctx->r6 = S32(0X802C << 16);
    // 0x802C5FD0: lw          $a2, 0x6B38($a2)
    ctx->r6 = MEM_W(ctx->r6, 0X6B38);
    // 0x802C5FD4: lui         $t6, 0x802C
    ctx->r14 = S32(0X802C << 16);
    // 0x802C5FD8: addiu       $t6, $t6, 0x6AF8
    ctx->r14 = ADD32(ctx->r14, 0X6AF8);
    // 0x802C5FDC: sll         $t9, $a2, 3
    ctx->r25 = S32(ctx->r6 << 3);
    // 0x802C5FE0: addu        $a0, $t9, $t6
    ctx->r4 = ADD32(ctx->r25, ctx->r14);
    // 0x802C5FE4: lui         $t6, 0x801D
    ctx->r14 = S32(0X801D << 16);
    // 0x802C5FE8: addiu       $t6, $t6, -0x4CF8
    ctx->r14 = ADD32(ctx->r14, -0X4CF8);
    // 0x802C5FEC: mflo        $t7
    ctx->r15 = lo;
    // 0x802C5FF0: addu        $v0, $t7, $t8
    ctx->r2 = ADD32(ctx->r15, ctx->r24);
    // 0x802C5FF4: sll         $t7, $v0, 2
    ctx->r15 = S32(ctx->r2 << 2);
    // 0x802C5FF8: subu        $t7, $t7, $v0
    ctx->r15 = SUB32(ctx->r15, ctx->r2);
    // 0x802C5FFC: sll         $t7, $t7, 2
    ctx->r15 = S32(ctx->r15 << 2);
    // 0x802C6000: sll         $t8, $a2, 2
    ctx->r24 = S32(ctx->r6 << 2);
    // 0x802C6004: addu        $t9, $t7, $t8
    ctx->r25 = ADD32(ctx->r15, ctx->r24);
    // 0x802C6008: addu        $v1, $t9, $t6
    ctx->r3 = ADD32(ctx->r25, ctx->r14);
    // 0x802C600C: lw          $t7, 0x0($v1)
    ctx->r15 = MEM_W(ctx->r3, 0X0);
    // 0x802C6010: addiu       $t4, $zero, 0x1
    ctx->r12 = ADD32(0, 0X1);
    // 0x802C6014: addiu       $t8, $t7, -0x1
    ctx->r24 = ADD32(ctx->r15, -0X1);
    // 0x802C6018: sw          $t8, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r24;
    // 0x802C601C: lw          $t6, 0x0($a0)
    ctx->r14 = MEM_W(ctx->r4, 0X0);
    // 0x802C6020: slt         $at, $t8, $t6
    ctx->r1 = SIGNED(ctx->r24) < SIGNED(ctx->r14) ? 1 : 0;
    // 0x802C6024: beq         $at, $zero, L_802C6034
    if (ctx->r1 == 0) {
        // 0x802C6028: nop
    
            goto L_802C6034;
    }
    // 0x802C6028: nop

    // 0x802C602C: lw          $t7, 0x4($a0)
    ctx->r15 = MEM_W(ctx->r4, 0X4);
    // 0x802C6030: sw          $t7, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r15;
L_802C6034:
    // 0x802C6034: beq         $t4, $zero, L_802C61F0
    if (ctx->r12 == 0) {
        // 0x802C6038: addiu       $a0, $zero, 0x10
        ctx->r4 = ADD32(0, 0X10);
            goto L_802C61F0;
    }
    // 0x802C6038: addiu       $a0, $zero, 0x10
    ctx->r4 = ADD32(0, 0X10);
    // 0x802C603C: jal         0x800C37F4
    // 0x802C6040: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_6;
    // 0x802C6040: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_6:
    // 0x802C6044: b           L_802C61F4
    // 0x802C6048: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_802C61F4;
    // 0x802C6048: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C604C:
    // 0x802C604C: beq         $t8, $zero, L_802C61F0
    if (ctx->r24 == 0) {
        // 0x802C6050: lui         $v1, 0x801D
        ctx->r3 = S32(0X801D << 16);
            goto L_802C61F0;
    }
    // 0x802C6050: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x802C6054: addiu       $v1, $v1, -0x19C0
    ctx->r3 = ADD32(ctx->r3, -0X19C0);
    // 0x802C6058: lw          $v0, 0x0($v1)
    ctx->r2 = MEM_W(ctx->r3, 0X0);
    // 0x802C605C: lui         $a1, 0x802C
    ctx->r5 = S32(0X802C << 16);
    // 0x802C6060: addiu       $a1, $a1, 0x6B34
    ctx->r5 = ADD32(ctx->r5, 0X6B34);
    // 0x802C6064: beq         $v0, $zero, L_802C6090
    if (ctx->r2 == 0) {
        // 0x802C6068: lui         $t0, 0x802C
        ctx->r8 = S32(0X802C << 16);
            goto L_802C6090;
    }
    // 0x802C6068: lui         $t0, 0x802C
    ctx->r8 = S32(0X802C << 16);
    // 0x802C606C: addiu       $t1, $zero, 0x1
    ctx->r9 = ADD32(0, 0X1);
    // 0x802C6070: beq         $v0, $t1, L_802C6158
    if (ctx->r2 == ctx->r9) {
        // 0x802C6074: addiu       $t3, $zero, 0x2
        ctx->r11 = ADD32(0, 0X2);
            goto L_802C6158;
    }
    // 0x802C6074: addiu       $t3, $zero, 0x2
    ctx->r11 = ADD32(0, 0X2);
    // 0x802C6078: beq         $v0, $t3, L_802C6158
    if (ctx->r2 == ctx->r11) {
        // 0x802C607C: addiu       $a3, $zero, 0x3
        ctx->r7 = ADD32(0, 0X3);
            goto L_802C6158;
    }
    // 0x802C607C: addiu       $a3, $zero, 0x3
    ctx->r7 = ADD32(0, 0X3);
    // 0x802C6080: beq         $v0, $a3, L_802C615C
    if (ctx->r2 == ctx->r7) {
        // 0x802C6084: nop
    
            goto L_802C615C;
    }
    // 0x802C6084: nop

    // 0x802C6088: b           L_802C61E0
    // 0x802C608C: nop

        goto L_802C61E0;
    // 0x802C608C: nop

L_802C6090:
    // 0x802C6090: addiu       $t0, $t0, 0x6B30
    ctx->r8 = ADD32(ctx->r8, 0X6B30);
    // 0x802C6094: lw          $t9, 0x0($t0)
    ctx->r25 = MEM_W(ctx->r8, 0X0);
    // 0x802C6098: lw          $a0, 0x0($a1)
    ctx->r4 = MEM_W(ctx->r5, 0X0);
    // 0x802C609C: addiu       $t4, $zero, 0x1
    ctx->r12 = ADD32(0, 0X1);
    // 0x802C60A0: addiu       $t6, $t9, 0x1
    ctx->r14 = ADD32(ctx->r25, 0X1);
    // 0x802C60A4: bne         $a0, $zero, L_802C60C4
    if (ctx->r4 != 0) {
        // 0x802C60A8: sw          $t6, 0x0($t0)
        MEM_W(0X0, ctx->r8) = ctx->r14;
            goto L_802C60C4;
    }
    // 0x802C60A8: sw          $t6, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r14;
    // 0x802C60AC: slti        $at, $t6, 0x3
    ctx->r1 = SIGNED(ctx->r14) < 0X3 ? 1 : 0;
    // 0x802C60B0: bne         $at, $zero, L_802C60DC
    if (ctx->r1 != 0) {
        // 0x802C60B4: or          $v1, $t6, $zero
        ctx->r3 = ctx->r14 | 0;
            goto L_802C60DC;
    }
    // 0x802C60B4: or          $v1, $t6, $zero
    ctx->r3 = ctx->r14 | 0;
    // 0x802C60B8: sw          $zero, 0x0($t0)
    MEM_W(0X0, ctx->r8) = 0;
    // 0x802C60BC: b           L_802C60DC
    // 0x802C60C0: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
        goto L_802C60DC;
    // 0x802C60C0: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
L_802C60C4:
    // 0x802C60C4: lw          $v1, 0x0($t0)
    ctx->r3 = MEM_W(ctx->r8, 0X0);
    // 0x802C60C8: slti        $at, $v1, 0x2
    ctx->r1 = SIGNED(ctx->r3) < 0X2 ? 1 : 0;
    // 0x802C60CC: bnel        $at, $zero, L_802C60E0
    if (ctx->r1 != 0) {
        // 0x802C60D0: sll         $a1, $a0, 2
        ctx->r5 = S32(ctx->r4 << 2);
            goto L_802C60E0;
    }
    goto skip_11;
    // 0x802C60D0: sll         $a1, $a0, 2
    ctx->r5 = S32(ctx->r4 << 2);
    skip_11:
    // 0x802C60D4: sw          $zero, 0x0($t0)
    MEM_W(0X0, ctx->r8) = 0;
    // 0x802C60D8: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
L_802C60DC:
    // 0x802C60DC: sll         $a1, $a0, 2
    ctx->r5 = S32(ctx->r4 << 2);
L_802C60E0:
    // 0x802C60E0: lui         $a2, 0x802C
    ctx->r6 = S32(0X802C << 16);
    // 0x802C60E4: addiu       $a2, $a2, 0x6B40
    ctx->r6 = ADD32(ctx->r6, 0X6B40);
    // 0x802C60E8: subu        $a1, $a1, $a0
    ctx->r5 = SUB32(ctx->r5, ctx->r4);
L_802C60EC:
    // 0x802C60EC: addu        $v0, $a1, $v1
    ctx->r2 = ADD32(ctx->r5, ctx->r3);
L_802C60F0:
    // 0x802C60F0: sll         $t7, $v0, 2
    ctx->r15 = S32(ctx->r2 << 2);
    // 0x802C60F4: addu        $t8, $a2, $t7
    ctx->r24 = ADD32(ctx->r6, ctx->r15);
    // 0x802C60F8: lw          $t9, 0x0($t8)
    ctx->r25 = MEM_W(ctx->r24, 0X0);
    // 0x802C60FC: lui         $t5, 0x802C
    ctx->r13 = S32(0X802C << 16);
    // 0x802C6100: addiu       $t5, $t5, 0x6B10
    ctx->r13 = ADD32(ctx->r13, 0X6B10);
    // 0x802C6104: beql        $t9, $zero, L_802C611C
    if (ctx->r25 == 0) {
        // 0x802C6108: addiu       $t6, $v1, 0x1
        ctx->r14 = ADD32(ctx->r3, 0X1);
            goto L_802C611C;
    }
    goto skip_12;
    // 0x802C6108: addiu       $t6, $v1, 0x1
    ctx->r14 = ADD32(ctx->r3, 0X1);
    skip_12:
    // 0x802C610C: addiu       $v1, $zero, -0x1
    ctx->r3 = ADD32(0, -0X1);
    // 0x802C6110: b           L_802C61E0
    // 0x802C6114: sw          $v1, 0x0($t5)
    MEM_W(0X0, ctx->r13) = ctx->r3;
        goto L_802C61E0;
    // 0x802C6114: sw          $v1, 0x0($t5)
    MEM_W(0X0, ctx->r13) = ctx->r3;
    // 0x802C6118: addiu       $t6, $v1, 0x1
    ctx->r14 = ADD32(ctx->r3, 0X1);
L_802C611C:
    // 0x802C611C: bne         $a0, $zero, L_802C613C
    if (ctx->r4 != 0) {
        // 0x802C6120: sw          $t6, 0x0($t0)
        MEM_W(0X0, ctx->r8) = ctx->r14;
            goto L_802C613C;
    }
    // 0x802C6120: sw          $t6, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r14;
    // 0x802C6124: slti        $at, $t6, 0x3
    ctx->r1 = SIGNED(ctx->r14) < 0X3 ? 1 : 0;
    // 0x802C6128: bne         $at, $zero, L_802C60EC
    if (ctx->r1 != 0) {
        // 0x802C612C: or          $v1, $t6, $zero
        ctx->r3 = ctx->r14 | 0;
            goto L_802C60EC;
    }
    // 0x802C612C: or          $v1, $t6, $zero
    ctx->r3 = ctx->r14 | 0;
    // 0x802C6130: sw          $zero, 0x0($t0)
    MEM_W(0X0, ctx->r8) = 0;
    // 0x802C6134: b           L_802C60EC
    // 0x802C6138: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
        goto L_802C60EC;
    // 0x802C6138: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
L_802C613C:
    // 0x802C613C: lw          $v1, 0x0($t0)
    ctx->r3 = MEM_W(ctx->r8, 0X0);
    // 0x802C6140: slti        $at, $v1, 0x2
    ctx->r1 = SIGNED(ctx->r3) < 0X2 ? 1 : 0;
    // 0x802C6144: bnel        $at, $zero, L_802C60F0
    if (ctx->r1 != 0) {
        // 0x802C6148: addu        $v0, $a1, $v1
        ctx->r2 = ADD32(ctx->r5, ctx->r3);
            goto L_802C60F0;
    }
    goto skip_13;
    // 0x802C6148: addu        $v0, $a1, $v1
    ctx->r2 = ADD32(ctx->r5, ctx->r3);
    skip_13:
    // 0x802C614C: sw          $zero, 0x0($t0)
    MEM_W(0X0, ctx->r8) = 0;
    // 0x802C6150: b           L_802C60EC
    // 0x802C6154: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
        goto L_802C60EC;
    // 0x802C6154: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
L_802C6158:
    // 0x802C6158: addiu       $a3, $zero, 0x3
    ctx->r7 = ADD32(0, 0X3);
L_802C615C:
    // 0x802C615C: lui         $a1, 0x802C
    ctx->r5 = S32(0X802C << 16);
    // 0x802C6160: addiu       $a1, $a1, 0x6B34
    ctx->r5 = ADD32(ctx->r5, 0X6B34);
    // 0x802C6164: lw          $t7, 0x0($a1)
    ctx->r15 = MEM_W(ctx->r5, 0X0);
    // 0x802C6168: lui         $t0, 0x802C
    ctx->r8 = S32(0X802C << 16);
    // 0x802C616C: addiu       $t0, $t0, 0x6B30
    ctx->r8 = ADD32(ctx->r8, 0X6B30);
    // 0x802C6170: multu       $t7, $a3
    result = U64(U32(ctx->r15)) * U64(U32(ctx->r7)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x802C6174: lw          $t9, 0x0($t0)
    ctx->r25 = MEM_W(ctx->r8, 0X0);
    // 0x802C6178: lui         $a2, 0x802C
    ctx->r6 = S32(0X802C << 16);
    // 0x802C617C: lw          $a2, 0x6B38($a2)
    ctx->r6 = MEM_W(ctx->r6, 0X6B38);
    // 0x802C6180: lui         $t7, 0x802C
    ctx->r15 = S32(0X802C << 16);
    // 0x802C6184: addiu       $t7, $t7, 0x6AF8
    ctx->r15 = ADD32(ctx->r15, 0X6AF8);
    // 0x802C6188: sll         $t6, $a2, 3
    ctx->r14 = S32(ctx->r6 << 3);
    // 0x802C618C: addu        $a0, $t6, $t7
    ctx->r4 = ADD32(ctx->r14, ctx->r15);
    // 0x802C6190: lui         $t7, 0x801D
    ctx->r15 = S32(0X801D << 16);
    // 0x802C6194: addiu       $t7, $t7, -0x4CF8
    ctx->r15 = ADD32(ctx->r15, -0X4CF8);
    // 0x802C6198: mflo        $t8
    ctx->r24 = lo;
    // 0x802C619C: addu        $v0, $t8, $t9
    ctx->r2 = ADD32(ctx->r24, ctx->r25);
    // 0x802C61A0: sll         $t8, $v0, 2
    ctx->r24 = S32(ctx->r2 << 2);
    // 0x802C61A4: subu        $t8, $t8, $v0
    ctx->r24 = SUB32(ctx->r24, ctx->r2);
    // 0x802C61A8: sll         $t8, $t8, 2
    ctx->r24 = S32(ctx->r24 << 2);
    // 0x802C61AC: sll         $t9, $a2, 2
    ctx->r25 = S32(ctx->r6 << 2);
    // 0x802C61B0: addu        $t6, $t8, $t9
    ctx->r14 = ADD32(ctx->r24, ctx->r25);
    // 0x802C61B4: addu        $v1, $t6, $t7
    ctx->r3 = ADD32(ctx->r14, ctx->r15);
    // 0x802C61B8: lw          $t8, 0x0($v1)
    ctx->r24 = MEM_W(ctx->r3, 0X0);
    // 0x802C61BC: addiu       $t4, $zero, 0x1
    ctx->r12 = ADD32(0, 0X1);
    // 0x802C61C0: addiu       $t9, $t8, 0x1
    ctx->r25 = ADD32(ctx->r24, 0X1);
    // 0x802C61C4: sw          $t9, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r25;
    // 0x802C61C8: lw          $t6, 0x4($a0)
    ctx->r14 = MEM_W(ctx->r4, 0X4);
    // 0x802C61CC: slt         $at, $t6, $t9
    ctx->r1 = SIGNED(ctx->r14) < SIGNED(ctx->r25) ? 1 : 0;
    // 0x802C61D0: beq         $at, $zero, L_802C61E0
    if (ctx->r1 == 0) {
        // 0x802C61D4: nop
    
            goto L_802C61E0;
    }
    // 0x802C61D4: nop

    // 0x802C61D8: lw          $t8, 0x0($a0)
    ctx->r24 = MEM_W(ctx->r4, 0X0);
    // 0x802C61DC: sw          $t8, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r24;
L_802C61E0:
    // 0x802C61E0: beq         $t4, $zero, L_802C61F0
    if (ctx->r12 == 0) {
        // 0x802C61E4: addiu       $a0, $zero, 0x10
        ctx->r4 = ADD32(0, 0X10);
            goto L_802C61F0;
    }
    // 0x802C61E4: addiu       $a0, $zero, 0x10
    ctx->r4 = ADD32(0, 0X10);
    // 0x802C61E8: jal         0x800C37F4
    // 0x802C61EC: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_7;
    // 0x802C61EC: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_7:
L_802C61F0:
    // 0x802C61F0: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C61F4:
    // 0x802C61F4: addiu       $sp, $sp, 0x28
    ctx->r29 = ADD32(ctx->r29, 0X28);
    // 0x802C61F8: jr          $ra
    // 0x802C61FC: nop

    return;
    // 0x802C61FC: nop

;}
RECOMP_FUNC void func_i10_802C6200(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C6200: addiu       $sp, $sp, -0xD0
    ctx->r29 = ADD32(ctx->r29, -0XD0);
    // 0x802C6204: sw          $s2, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r18;
    // 0x802C6208: sw          $ra, 0x64($sp)
    MEM_W(0X64, ctx->r29) = ctx->r31;
    // 0x802C620C: sw          $fp, 0x60($sp)
    MEM_W(0X60, ctx->r29) = ctx->r30;
    // 0x802C6210: sw          $s7, 0x5C($sp)
    MEM_W(0X5C, ctx->r29) = ctx->r23;
    // 0x802C6214: sw          $s6, 0x58($sp)
    MEM_W(0X58, ctx->r29) = ctx->r22;
    // 0x802C6218: sw          $s5, 0x54($sp)
    MEM_W(0X54, ctx->r29) = ctx->r21;
    // 0x802C621C: sw          $s4, 0x50($sp)
    MEM_W(0X50, ctx->r29) = ctx->r20;
    // 0x802C6220: sw          $s3, 0x4C($sp)
    MEM_W(0X4C, ctx->r29) = ctx->r19;
    // 0x802C6224: sw          $s1, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r17;
    // 0x802C6228: sw          $s0, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r16;
    // 0x802C622C: addiu       $s2, $a0, 0x8
    ctx->r18 = ADD32(ctx->r4, 0X8);
    // 0x802C6230: lui         $t6, 0x103
    ctx->r14 = S32(0X103 << 16);
    // 0x802C6234: lui         $t7, 0x700
    ctx->r15 = S32(0X700 << 16);
    // 0x802C6238: addiu       $t7, $t7, 0x0
    ctx->r15 = ADD32(ctx->r15, 0X0);
    // 0x802C623C: ori         $t6, $t6, 0x40
    ctx->r14 = ctx->r14 | 0X40;
    // 0x802C6240: or          $v1, $s2, $zero
    ctx->r3 = ctx->r18 | 0;
    // 0x802C6244: sw          $t6, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r14;
    // 0x802C6248: sw          $t7, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r15;
    // 0x802C624C: addiu       $s2, $s2, 0x8
    ctx->r18 = ADD32(ctx->r18, 0X8);
    // 0x802C6250: lui         $t8, 0x102
    ctx->r24 = S32(0X102 << 16);
    // 0x802C6254: lui         $t9, 0x200
    ctx->r25 = S32(0X200 << 16);
    // 0x802C6258: addiu       $t9, $t9, 0xA40
    ctx->r25 = ADD32(ctx->r25, 0XA40);
    // 0x802C625C: ori         $t8, $t8, 0x40
    ctx->r24 = ctx->r24 | 0X40;
    // 0x802C6260: or          $a1, $s2, $zero
    ctx->r5 = ctx->r18 | 0;
    // 0x802C6264: sw          $t8, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r24;
    // 0x802C6268: sw          $t9, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r25;
    // 0x802C626C: addiu       $s2, $s2, 0x8
    ctx->r18 = ADD32(ctx->r18, 0X8);
    // 0x802C6270: lui         $t1, 0x107
    ctx->r9 = S32(0X107 << 16);
    // 0x802C6274: lui         $t0, 0x600
    ctx->r8 = S32(0X600 << 16);
    // 0x802C6278: addiu       $t1, $t1, -0xAB0
    ctx->r9 = ADD32(ctx->r9, -0XAB0);
    // 0x802C627C: or          $a3, $s2, $zero
    ctx->r7 = ctx->r18 | 0;
    // 0x802C6280: sw          $t1, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r9;
    // 0x802C6284: sw          $t0, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r8;
    // 0x802C6288: lui         $t2, 0x107
    ctx->r10 = S32(0X107 << 16);
    // 0x802C628C: addiu       $t2, $t2, -0x9D8
    ctx->r10 = ADD32(ctx->r10, -0X9D8);
    // 0x802C6290: sw          $t2, 0x4($a3)
    MEM_W(0X4, ctx->r7) = ctx->r10;
    // 0x802C6294: sw          $t0, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r8;
    // 0x802C6298: addiu       $s2, $s2, 0x8
    ctx->r18 = ADD32(ctx->r18, 0X8);
    // 0x802C629C: addiu       $a2, $zero, 0x1C
    ctx->r6 = ADD32(0, 0X1C);
    // 0x802C62A0: addiu       $t3, $zero, 0x56
    ctx->r11 = ADD32(0, 0X56);
L_802C62A4:
    // 0x802C62A4: addiu       $t4, $zero, 0x10
    ctx->r12 = ADD32(0, 0X10);
    // 0x802C62A8: sw          $t4, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r12;
    // 0x802C62AC: sw          $t3, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r11;
    // 0x802C62B0: or          $a0, $s2, $zero
    ctx->r4 = ctx->r18 | 0;
    // 0x802C62B4: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C62B8: addiu       $a3, $zero, 0x45
    ctx->r7 = ADD32(0, 0X45);
    // 0x802C62BC: jal         0x80094338
    // 0x802C62C0: sw          $a2, 0x80($sp)
    MEM_W(0X80, ctx->r29) = ctx->r6;
    func_80094338(rdram, ctx);
        goto after_0;
    // 0x802C62C0: sw          $a2, 0x80($sp)
    MEM_W(0X80, ctx->r29) = ctx->r6;
    after_0:
    // 0x802C62C4: lw          $a2, 0x80($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X80);
    // 0x802C62C8: or          $s2, $v0, $zero
    ctx->r18 = ctx->r2 | 0;
    // 0x802C62CC: addiu       $a2, $a2, 0x8D
    ctx->r6 = ADD32(ctx->r6, 0X8D);
    // 0x802C62D0: slti        $at, $a2, 0x18F
    ctx->r1 = SIGNED(ctx->r6) < 0X18F ? 1 : 0;
    // 0x802C62D4: bnel        $at, $zero, L_802C62A4
    if (ctx->r1 != 0) {
        // 0x802C62D8: addiu       $t3, $zero, 0x56
        ctx->r11 = ADD32(0, 0X56);
            goto L_802C62A4;
    }
    goto skip_0;
    // 0x802C62D8: addiu       $t3, $zero, 0x56
    ctx->r11 = ADD32(0, 0X56);
    skip_0:
    // 0x802C62DC: addiu       $t5, $zero, 0x56
    ctx->r13 = ADD32(0, 0X56);
    // 0x802C62E0: addiu       $t6, $zero, 0x10
    ctx->r14 = ADD32(0, 0X10);
    // 0x802C62E4: sw          $t6, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r14;
    // 0x802C62E8: sw          $t5, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r13;
    // 0x802C62EC: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C62F0: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C62F4: addiu       $a2, $zero, 0xF2
    ctx->r6 = ADD32(0, 0XF2);
    // 0x802C62F8: jal         0x80094338
    // 0x802C62FC: addiu       $a3, $zero, 0x5A
    ctx->r7 = ADD32(0, 0X5A);
    func_80094338(rdram, ctx);
        goto after_1;
    // 0x802C62FC: addiu       $a3, $zero, 0x5A
    ctx->r7 = ADD32(0, 0X5A);
    after_1:
    // 0x802C6300: addiu       $t7, $zero, 0x56
    ctx->r15 = ADD32(0, 0X56);
    // 0x802C6304: addiu       $t8, $zero, 0x10
    ctx->r24 = ADD32(0, 0X10);
    // 0x802C6308: sw          $t8, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r24;
    // 0x802C630C: sw          $t7, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r15;
    // 0x802C6310: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C6314: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C6318: addiu       $a2, $zero, 0x60
    ctx->r6 = ADD32(0, 0X60);
    // 0x802C631C: jal         0x80094338
    // 0x802C6320: addiu       $a3, $zero, 0x5A
    ctx->r7 = ADD32(0, 0X5A);
    func_80094338(rdram, ctx);
        goto after_2;
    // 0x802C6320: addiu       $a3, $zero, 0x5A
    ctx->r7 = ADD32(0, 0X5A);
    after_2:
    // 0x802C6324: or          $s2, $v0, $zero
    ctx->r18 = ctx->r2 | 0;
    // 0x802C6328: addiu       $s1, $zero, 0x7D
    ctx->r17 = ADD32(0, 0X7D);
    // 0x802C632C: addiu       $s0, $zero, 0x7C
    ctx->r16 = ADD32(0, 0X7C);
L_802C6330:
    // 0x802C6330: addiu       $t9, $zero, 0x9C
    ctx->r25 = ADD32(0, 0X9C);
    // 0x802C6334: addiu       $t1, $zero, 0x10
    ctx->r9 = ADD32(0, 0X10);
    // 0x802C6338: sw          $t1, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r9;
    // 0x802C633C: sw          $t9, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r25;
    // 0x802C6340: or          $a0, $s2, $zero
    ctx->r4 = ctx->r18 | 0;
    // 0x802C6344: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C6348: addiu       $a2, $zero, 0x1C
    ctx->r6 = ADD32(0, 0X1C);
    // 0x802C634C: jal         0x80094338
    // 0x802C6350: or          $a3, $s1, $zero
    ctx->r7 = ctx->r17 | 0;
    func_80094338(rdram, ctx);
        goto after_3;
    // 0x802C6350: or          $a3, $s1, $zero
    ctx->r7 = ctx->r17 | 0;
    after_3:
    // 0x802C6354: addiu       $t2, $zero, 0x69
    ctx->r10 = ADD32(0, 0X69);
    // 0x802C6358: addiu       $t3, $zero, 0x10
    ctx->r11 = ADD32(0, 0X10);
    // 0x802C635C: sw          $t3, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r11;
    // 0x802C6360: sw          $t2, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r10;
    // 0x802C6364: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C6368: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C636C: addiu       $a2, $zero, 0x123
    ctx->r6 = ADD32(0, 0X123);
    // 0x802C6370: jal         0x80094338
    // 0x802C6374: or          $a3, $s0, $zero
    ctx->r7 = ctx->r16 | 0;
    func_80094338(rdram, ctx);
        goto after_4;
    // 0x802C6374: or          $a3, $s0, $zero
    ctx->r7 = ctx->r16 | 0;
    after_4:
    // 0x802C6378: addiu       $s0, $s0, 0x14
    ctx->r16 = ADD32(ctx->r16, 0X14);
    // 0x802C637C: slti        $at, $s0, 0xB8
    ctx->r1 = SIGNED(ctx->r16) < 0XB8 ? 1 : 0;
    // 0x802C6380: addiu       $s1, $s1, 0x14
    ctx->r17 = ADD32(ctx->r17, 0X14);
    // 0x802C6384: bne         $at, $zero, L_802C6330
    if (ctx->r1 != 0) {
        // 0x802C6388: or          $s2, $v0, $zero
        ctx->r18 = ctx->r2 | 0;
            goto L_802C6330;
    }
    // 0x802C6388: or          $s2, $v0, $zero
    ctx->r18 = ctx->r2 | 0;
    // 0x802C638C: addiu       $t4, $zero, 0xFF
    ctx->r12 = ADD32(0, 0XFF);
    // 0x802C6390: addiu       $t5, $zero, 0xFF
    ctx->r13 = ADD32(0, 0XFF);
    // 0x802C6394: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C6398: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C639C: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C63A0: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C63A4: addiu       $t1, $zero, 0xFF
    ctx->r9 = ADD32(0, 0XFF);
    // 0x802C63A8: addiu       $t2, $zero, 0xFF
    ctx->r10 = ADD32(0, 0XFF);
    // 0x802C63AC: addiu       $t3, $zero, 0xFF
    ctx->r11 = ADD32(0, 0XFF);
    // 0x802C63B0: sw          $t3, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r11;
    // 0x802C63B4: sw          $t2, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r10;
    // 0x802C63B8: sw          $t1, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r9;
    // 0x802C63BC: sw          $t9, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r25;
    // 0x802C63C0: sw          $t8, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r24;
    // 0x802C63C4: sw          $t7, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r15;
    // 0x802C63C8: sw          $t6, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r14;
    // 0x802C63CC: sw          $t5, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r13;
    // 0x802C63D0: sw          $t4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r12;
    // 0x802C63D4: sw          $t4, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r12;
    // 0x802C63D8: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C63DC: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C63E0: addiu       $a2, $zero, 0xFF
    ctx->r6 = ADD32(0, 0XFF);
    // 0x802C63E4: jal         0x801E946C
    // 0x802C63E8: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    func_801E946C(rdram, ctx);
        goto after_5;
    // 0x802C63E8: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    after_5:
    // 0x802C63EC: addiu       $t5, $zero, 0x27
    ctx->r13 = ADD32(0, 0X27);
    // 0x802C63F0: sw          $t5, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r13;
    // 0x802C63F4: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C63F8: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C63FC: addiu       $a2, $zero, 0x10
    ctx->r6 = ADD32(0, 0X10);
    // 0x802C6400: addiu       $a3, $zero, 0x5A
    ctx->r7 = ADD32(0, 0X5A);
    // 0x802C6404: jal         0x801E3EE0
    // 0x802C6408: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    func_801E3EE0(rdram, ctx);
        goto after_6;
    // 0x802C6408: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    after_6:
    // 0x802C640C: lui         $t6, 0x802C
    ctx->r14 = S32(0X802C << 16);
    // 0x802C6410: lw          $t6, 0x6B34($t6)
    ctx->r14 = MEM_W(ctx->r14, 0X6B34);
    // 0x802C6414: lui         $t8, 0x802C
    ctx->r24 = S32(0X802C << 16);
    // 0x802C6418: lw          $t8, 0x6B30($t8)
    ctx->r24 = MEM_W(ctx->r24, 0X6B30);
    // 0x802C641C: sll         $t7, $t6, 2
    ctx->r15 = S32(ctx->r14 << 2);
    // 0x802C6420: subu        $t7, $t7, $t6
    ctx->r15 = SUB32(ctx->r15, ctx->r14);
    // 0x802C6424: lui         $s1, 0x802C
    ctx->r17 = S32(0X802C << 16);
    // 0x802C6428: lui         $s6, 0x802C
    ctx->r22 = S32(0X802C << 16);
    // 0x802C642C: addu        $t9, $t7, $t8
    ctx->r25 = ADD32(ctx->r15, ctx->r24);
    // 0x802C6430: or          $s2, $v0, $zero
    ctx->r18 = ctx->r2 | 0;
    // 0x802C6434: sw          $t9, 0xB0($sp)
    MEM_W(0XB0, ctx->r29) = ctx->r25;
    // 0x802C6438: addiu       $s6, $s6, 0x6B40
    ctx->r22 = ADD32(ctx->r22, 0X6B40);
    // 0x802C643C: addiu       $s1, $s1, 0x6AA0
    ctx->r17 = ADD32(ctx->r17, 0X6AA0);
    // 0x802C6440: or          $s3, $zero, $zero
    ctx->r19 = 0 | 0;
    // 0x802C6444: addiu       $s5, $zero, 0x95
    ctx->r21 = ADD32(0, 0X95);
    // 0x802C6448: addiu       $s4, $zero, 0x4
    ctx->r20 = ADD32(0, 0X4);
L_802C644C:
    // 0x802C644C: lw          $t1, 0xB0($sp)
    ctx->r9 = MEM_W(ctx->r29, 0XB0);
    // 0x802C6450: or          $a0, $s2, $zero
    ctx->r4 = ctx->r18 | 0;
    // 0x802C6454: addiu       $a2, $zero, 0x80
    ctx->r6 = ADD32(0, 0X80);
    // 0x802C6458: bne         $s3, $t1, L_802C6468
    if (ctx->r19 != ctx->r9) {
        // 0x802C645C: addiu       $a3, $zero, 0x80
        ctx->r7 = ADD32(0, 0X80);
            goto L_802C6468;
    }
    // 0x802C645C: addiu       $a3, $zero, 0x80
    ctx->r7 = ADD32(0, 0X80);
    // 0x802C6460: b           L_802C6488
    // 0x802C6464: addiu       $s0, $zero, 0x6
    ctx->r16 = ADD32(0, 0X6);
        goto L_802C6488;
    // 0x802C6464: addiu       $s0, $zero, 0x6
    ctx->r16 = ADD32(0, 0X6);
L_802C6468:
    // 0x802C6468: sll         $t2, $s3, 2
    ctx->r10 = S32(ctx->r19 << 2);
    // 0x802C646C: addu        $t3, $s6, $t2
    ctx->r11 = ADD32(ctx->r22, ctx->r10);
    // 0x802C6470: lw          $t4, 0x0($t3)
    ctx->r12 = MEM_W(ctx->r11, 0X0);
    // 0x802C6474: or          $s0, $zero, $zero
    ctx->r16 = 0 | 0;
    // 0x802C6478: bne         $t4, $zero, L_802C6488
    if (ctx->r12 != 0) {
        // 0x802C647C: nop
    
            goto L_802C6488;
    }
    // 0x802C647C: nop

    // 0x802C6480: b           L_802C6488
    // 0x802C6484: addiu       $s0, $zero, 0x7
    ctx->r16 = ADD32(0, 0X7);
        goto L_802C6488;
    // 0x802C6484: addiu       $s0, $zero, 0x7
    ctx->r16 = ADD32(0, 0X7);
L_802C6488:
    // 0x802C6488: addiu       $t5, $zero, 0x80
    ctx->r13 = ADD32(0, 0X80);
    // 0x802C648C: sw          $t5, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r13;
    // 0x802C6490: addiu       $t5, $zero, 0xFF
    ctx->r13 = ADD32(0, 0XFF);
    // 0x802C6494: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C6498: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C649C: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C64A0: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C64A4: addiu       $t1, $zero, 0xFF
    ctx->r9 = ADD32(0, 0XFF);
    // 0x802C64A8: addiu       $t2, $zero, 0xFF
    ctx->r10 = ADD32(0, 0XFF);
    // 0x802C64AC: addiu       $t3, $zero, 0xFF
    ctx->r11 = ADD32(0, 0XFF);
    // 0x802C64B0: addiu       $t4, $zero, 0xFF
    ctx->r12 = ADD32(0, 0XFF);
    // 0x802C64B4: sw          $t4, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r12;
    // 0x802C64B8: sw          $t3, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r11;
    // 0x802C64BC: sw          $t2, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r10;
    // 0x802C64C0: sw          $t1, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r9;
    // 0x802C64C4: sw          $t9, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r25;
    // 0x802C64C8: sw          $t8, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r24;
    // 0x802C64CC: sw          $t7, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r15;
    // 0x802C64D0: sw          $t6, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r14;
    // 0x802C64D4: sw          $t5, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r13;
    // 0x802C64D8: jal         0x801E946C
    // 0x802C64DC: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    func_801E946C(rdram, ctx);
        goto after_7;
    // 0x802C64DC: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    after_7:
    // 0x802C64E0: bne         $s3, $s4, L_802C6510
    if (ctx->r19 != ctx->r20) {
        // 0x802C64E4: or          $s2, $v0, $zero
        ctx->r18 = ctx->r2 | 0;
            goto L_802C6510;
    }
    // 0x802C64E4: or          $s2, $v0, $zero
    ctx->r18 = ctx->r2 | 0;
    // 0x802C64E8: lw          $a2, 0x4($s1)
    ctx->r6 = MEM_W(ctx->r17, 0X4);
    // 0x802C64EC: addiu       $t6, $zero, 0x5D
    ctx->r14 = ADD32(0, 0X5D);
    // 0x802C64F0: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x802C64F4: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    // 0x802C64F8: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C64FC: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C6500: jal         0x801E3EE0
    // 0x802C6504: addiu       $a3, $zero, 0x10F
    ctx->r7 = ADD32(0, 0X10F);
    func_801E3EE0(rdram, ctx);
        goto after_8;
    // 0x802C6504: addiu       $a3, $zero, 0x10F
    ctx->r7 = ADD32(0, 0X10F);
    after_8:
    // 0x802C6508: b           L_802C6574
    // 0x802C650C: or          $s2, $v0, $zero
    ctx->r18 = ctx->r2 | 0;
        goto L_802C6574;
    // 0x802C650C: or          $s2, $v0, $zero
    ctx->r18 = ctx->r2 | 0;
L_802C6510:
    // 0x802C6510: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x802C6514: bne         $s3, $at, L_802C6540
    if (ctx->r19 != ctx->r1) {
        // 0x802C6518: or          $a0, $s2, $zero
        ctx->r4 = ctx->r18 | 0;
            goto L_802C6540;
    }
    // 0x802C6518: or          $a0, $s2, $zero
    ctx->r4 = ctx->r18 | 0;
    // 0x802C651C: lw          $a2, 0x4($s1)
    ctx->r6 = MEM_W(ctx->r17, 0X4);
    // 0x802C6520: addiu       $t7, $zero, 0x5D
    ctx->r15 = ADD32(0, 0X5D);
    // 0x802C6524: sw          $t7, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r15;
    // 0x802C6528: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    // 0x802C652C: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C6530: jal         0x801E3EE0
    // 0x802C6534: addiu       $a3, $zero, 0x6A
    ctx->r7 = ADD32(0, 0X6A);
    func_801E3EE0(rdram, ctx);
        goto after_9;
    // 0x802C6534: addiu       $a3, $zero, 0x6A
    ctx->r7 = ADD32(0, 0X6A);
    after_9:
    // 0x802C6538: b           L_802C6574
    // 0x802C653C: or          $s2, $v0, $zero
    ctx->r18 = ctx->r2 | 0;
        goto L_802C6574;
    // 0x802C653C: or          $s2, $v0, $zero
    ctx->r18 = ctx->r2 | 0;
L_802C6540:
    // 0x802C6540: multu       $s3, $s5
    result = U64(U32(ctx->r19)) * U64(U32(ctx->r21)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x802C6544: lh          $t9, 0x0($s1)
    ctx->r25 = MEM_H(ctx->r17, 0X0);
    // 0x802C6548: lw          $a2, 0x4($s1)
    ctx->r6 = MEM_W(ctx->r17, 0X4);
    // 0x802C654C: addiu       $t1, $zero, 0x48
    ctx->r9 = ADD32(0, 0X48);
    // 0x802C6550: sw          $t1, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r9;
    // 0x802C6554: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    // 0x802C6558: or          $a0, $s2, $zero
    ctx->r4 = ctx->r18 | 0;
    // 0x802C655C: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C6560: mflo        $t8
    ctx->r24 = lo;
    // 0x802C6564: addu        $a3, $t8, $t9
    ctx->r7 = ADD32(ctx->r24, ctx->r25);
    // 0x802C6568: jal         0x801E3EE0
    // 0x802C656C: addiu       $a3, $a3, 0x2C
    ctx->r7 = ADD32(ctx->r7, 0X2C);
    func_801E3EE0(rdram, ctx);
        goto after_10;
    // 0x802C656C: addiu       $a3, $a3, 0x2C
    ctx->r7 = ADD32(ctx->r7, 0X2C);
    after_10:
    // 0x802C6570: or          $s2, $v0, $zero
    ctx->r18 = ctx->r2 | 0;
L_802C6574:
    // 0x802C6574: addiu       $s3, $s3, 0x1
    ctx->r19 = ADD32(ctx->r19, 0X1);
    // 0x802C6578: slti        $at, $s3, 0x5
    ctx->r1 = SIGNED(ctx->r19) < 0X5 ? 1 : 0;
    // 0x802C657C: bne         $at, $zero, L_802C644C
    if (ctx->r1 != 0) {
        // 0x802C6580: addiu       $s1, $s1, 0x8
        ctx->r17 = ADD32(ctx->r17, 0X8);
            goto L_802C644C;
    }
    // 0x802C6580: addiu       $s1, $s1, 0x8
    ctx->r17 = ADD32(ctx->r17, 0X8);
    // 0x802C6584: lw          $v0, 0xB0($sp)
    ctx->r2 = MEM_W(ctx->r29, 0XB0);
    // 0x802C6588: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x802C658C: beql        $v0, $s4, L_802C69D0
    if (ctx->r2 == ctx->r20) {
        // 0x802C6590: lw          $ra, 0x64($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X64);
            goto L_802C69D0;
    }
    goto skip_1;
    // 0x802C6590: lw          $ra, 0x64($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X64);
    skip_1:
    // 0x802C6594: beq         $v0, $at, L_802C69CC
    if (ctx->r2 == ctx->r1) {
        // 0x802C6598: sll         $t2, $v0, 2
        ctx->r10 = S32(ctx->r2 << 2);
            goto L_802C69CC;
    }
    // 0x802C6598: sll         $t2, $v0, 2
    ctx->r10 = S32(ctx->r2 << 2);
    // 0x802C659C: subu        $t2, $t2, $v0
    ctx->r10 = SUB32(ctx->r10, ctx->r2);
    // 0x802C65A0: lui         $t4, 0x801D
    ctx->r12 = S32(0X801D << 16);
    // 0x802C65A4: addiu       $t4, $t4, -0x4CF8
    ctx->r12 = ADD32(ctx->r12, -0X4CF8);
    // 0x802C65A8: sll         $t2, $t2, 2
    ctx->r10 = S32(ctx->r10 << 2);
    // 0x802C65AC: addu        $s5, $t2, $t4
    ctx->r21 = ADD32(ctx->r10, ctx->r12);
    // 0x802C65B0: lui         $fp, 0x802C
    ctx->r30 = S32(0X802C << 16);
    // 0x802C65B4: addiu       $t6, $zero, 0x80
    ctx->r14 = ADD32(0, 0X80);
    // 0x802C65B8: sw          $s5, 0x78($sp)
    MEM_W(0X78, ctx->r29) = ctx->r21;
    // 0x802C65BC: sw          $t2, 0x7C($sp)
    MEM_W(0X7C, ctx->r29) = ctx->r10;
    // 0x802C65C0: sw          $t6, 0x6C($sp)
    MEM_W(0X6C, ctx->r29) = ctx->r14;
    // 0x802C65C4: addiu       $fp, $fp, 0x6AC8
    ctx->r30 = ADD32(ctx->r30, 0X6AC8);
    // 0x802C65C8: or          $s3, $zero, $zero
    ctx->r19 = 0 | 0;
    // 0x802C65CC: or          $s7, $zero, $zero
    ctx->r23 = 0 | 0;
    // 0x802C65D0: addiu       $s6, $zero, 0x7F
    ctx->r22 = ADD32(0, 0X7F);
    // 0x802C65D4: addiu       $s4, $zero, -0x1
    ctx->r20 = ADD32(0, -0X1);
L_802C65D8:
    // 0x802C65D8: lui         $t7, 0x801D
    ctx->r15 = S32(0X801D << 16);
    // 0x802C65DC: lw          $t7, -0x19C0($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X19C0);
    // 0x802C65E0: or          $a0, $s2, $zero
    ctx->r4 = ctx->r18 | 0;
    // 0x802C65E4: addiu       $a2, $zero, 0x80
    ctx->r6 = ADD32(0, 0X80);
    // 0x802C65E8: beq         $t7, $zero, L_802C6624
    if (ctx->r15 == 0) {
        // 0x802C65EC: addiu       $a3, $zero, 0x80
        ctx->r7 = ADD32(0, 0X80);
            goto L_802C6624;
    }
    // 0x802C65EC: addiu       $a3, $zero, 0x80
    ctx->r7 = ADD32(0, 0X80);
    // 0x802C65F0: lui         $t8, 0x802C
    ctx->r24 = S32(0X802C << 16);
    // 0x802C65F4: lw          $t8, 0x6B38($t8)
    ctx->r24 = MEM_W(ctx->r24, 0X6B38);
    // 0x802C65F8: bnel        $s3, $t8, L_802C660C
    if (ctx->r19 != ctx->r24) {
        // 0x802C65FC: lw          $t9, 0x0($s5)
        ctx->r25 = MEM_W(ctx->r21, 0X0);
            goto L_802C660C;
    }
    goto skip_2;
    // 0x802C65FC: lw          $t9, 0x0($s5)
    ctx->r25 = MEM_W(ctx->r21, 0X0);
    skip_2:
    // 0x802C6600: b           L_802C663C
    // 0x802C6604: addiu       $s0, $zero, 0x6
    ctx->r16 = ADD32(0, 0X6);
        goto L_802C663C;
    // 0x802C6604: addiu       $s0, $zero, 0x6
    ctx->r16 = ADD32(0, 0X6);
    // 0x802C6608: lw          $t9, 0x0($s5)
    ctx->r25 = MEM_W(ctx->r21, 0X0);
L_802C660C:
    // 0x802C660C: bne         $s4, $t9, L_802C661C
    if (ctx->r20 != ctx->r25) {
        // 0x802C6610: nop
    
            goto L_802C661C;
    }
    // 0x802C6610: nop

    // 0x802C6614: b           L_802C663C
    // 0x802C6618: addiu       $s0, $zero, 0x7
    ctx->r16 = ADD32(0, 0X7);
        goto L_802C663C;
    // 0x802C6618: addiu       $s0, $zero, 0x7
    ctx->r16 = ADD32(0, 0X7);
L_802C661C:
    // 0x802C661C: b           L_802C663C
    // 0x802C6620: or          $s0, $zero, $zero
    ctx->r16 = 0 | 0;
        goto L_802C663C;
    // 0x802C6620: or          $s0, $zero, $zero
    ctx->r16 = 0 | 0;
L_802C6624:
    // 0x802C6624: lw          $t1, 0x0($s5)
    ctx->r9 = MEM_W(ctx->r21, 0X0);
    // 0x802C6628: or          $s0, $zero, $zero
    ctx->r16 = 0 | 0;
    // 0x802C662C: bne         $s4, $t1, L_802C663C
    if (ctx->r20 != ctx->r9) {
        // 0x802C6630: nop
    
            goto L_802C663C;
    }
    // 0x802C6630: nop

    // 0x802C6634: b           L_802C663C
    // 0x802C6638: addiu       $s0, $zero, 0x7
    ctx->r16 = ADD32(0, 0X7);
        goto L_802C663C;
    // 0x802C6638: addiu       $s0, $zero, 0x7
    ctx->r16 = ADD32(0, 0X7);
L_802C663C:
    // 0x802C663C: addiu       $t2, $zero, 0x80
    ctx->r10 = ADD32(0, 0X80);
    // 0x802C6640: sw          $t2, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r10;
    // 0x802C6644: addiu       $t2, $zero, 0xFF
    ctx->r10 = ADD32(0, 0XFF);
    // 0x802C6648: addiu       $t3, $zero, 0xFF
    ctx->r11 = ADD32(0, 0XFF);
    // 0x802C664C: addiu       $t4, $zero, 0xFF
    ctx->r12 = ADD32(0, 0XFF);
    // 0x802C6650: addiu       $t5, $zero, 0xFF
    ctx->r13 = ADD32(0, 0XFF);
    // 0x802C6654: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C6658: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C665C: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C6660: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C6664: addiu       $t1, $zero, 0xFF
    ctx->r9 = ADD32(0, 0XFF);
    // 0x802C6668: sw          $t1, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r9;
    // 0x802C666C: sw          $t9, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r25;
    // 0x802C6670: sw          $t8, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r24;
    // 0x802C6674: sw          $t7, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r15;
    // 0x802C6678: sw          $t6, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r14;
    // 0x802C667C: sw          $t5, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r13;
    // 0x802C6680: sw          $t4, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r12;
    // 0x802C6684: sw          $t3, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r11;
    // 0x802C6688: sw          $t2, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r10;
    // 0x802C668C: jal         0x801E946C
    // 0x802C6690: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    func_801E946C(rdram, ctx);
        goto after_11;
    // 0x802C6690: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    after_11:
    // 0x802C6694: lw          $t3, 0x6C($sp)
    ctx->r11 = MEM_W(ctx->r29, 0X6C);
    // 0x802C6698: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C669C: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C66A0: lw          $a2, 0x0($fp)
    ctx->r6 = MEM_W(ctx->r30, 0X0);
    // 0x802C66A4: addiu       $a3, $zero, 0x29
    ctx->r7 = ADD32(0, 0X29);
    // 0x802C66A8: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    // 0x802C66AC: jal         0x801E3EE0
    // 0x802C66B0: sw          $t3, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r11;
    func_801E3EE0(rdram, ctx);
        goto after_12;
    // 0x802C66B0: sw          $t3, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r11;
    after_12:
    // 0x802C66B4: lui         $a2, 0x802C
    ctx->r6 = S32(0X802C << 16);
    // 0x802C66B8: addiu       $a2, $a2, 0x6B20
    ctx->r6 = ADD32(ctx->r6, 0X6B20);
    // 0x802C66BC: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C66C0: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C66C4: addiu       $a3, $zero, 0xA7
    ctx->r7 = ADD32(0, 0XA7);
    // 0x802C66C8: jal         0x801E9858
    // 0x802C66CC: sw          $s6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r22;
    func_801E9858(rdram, ctx);
        goto after_13;
    // 0x802C66CC: sw          $s6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r22;
    after_13:
    // 0x802C66D0: lui         $t4, 0x801D
    ctx->r12 = S32(0X801D << 16);
    // 0x802C66D4: lw          $t4, -0x19C0($t4)
    ctx->r12 = MEM_W(ctx->r12, -0X19C0);
    // 0x802C66D8: or          $s2, $v0, $zero
    ctx->r18 = ctx->r2 | 0;
    // 0x802C66DC: lui         $t5, 0x802C
    ctx->r13 = S32(0X802C << 16);
    // 0x802C66E0: beq         $t4, $zero, L_802C6748
    if (ctx->r12 == 0) {
        // 0x802C66E4: addiu       $at, $zero, 0x1
        ctx->r1 = ADD32(0, 0X1);
            goto L_802C6748;
    }
    // 0x802C66E4: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x802C66E8: lw          $t5, 0x6B38($t5)
    ctx->r13 = MEM_W(ctx->r13, 0X6B38);
    // 0x802C66EC: lw          $t6, 0xB0($sp)
    ctx->r14 = MEM_W(ctx->r29, 0XB0);
    // 0x802C66F0: lui         $t9, 0x800E
    ctx->r25 = S32(0X800E << 16);
    // 0x802C66F4: bne         $s3, $t5, L_802C672C
    if (ctx->r19 != ctx->r13) {
        // 0x802C66F8: sll         $t7, $t6, 2
        ctx->r15 = S32(ctx->r14 << 2);
            goto L_802C672C;
    }
    // 0x802C66F8: sll         $t7, $t6, 2
    ctx->r15 = S32(ctx->r14 << 2);
    // 0x802C66FC: subu        $t7, $t7, $t6
    ctx->r15 = SUB32(ctx->r15, ctx->r14);
    // 0x802C6700: sll         $t7, $t7, 2
    ctx->r15 = S32(ctx->r15 << 2);
    // 0x802C6704: addu        $t8, $t7, $s7
    ctx->r24 = ADD32(ctx->r15, ctx->r23);
    // 0x802C6708: addu        $t9, $t9, $t8
    ctx->r25 = ADD32(ctx->r25, ctx->r24);
    // 0x802C670C: lw          $t9, -0x5678($t9)
    ctx->r25 = MEM_W(ctx->r25, -0X5678);
    // 0x802C6710: lw          $v0, 0x0($s5)
    ctx->r2 = MEM_W(ctx->r21, 0X0);
    // 0x802C6714: bne         $v0, $t9, L_802C6724
    if (ctx->r2 != ctx->r25) {
        // 0x802C6718: nop
    
            goto L_802C6724;
    }
    // 0x802C6718: nop

    // 0x802C671C: b           L_802C6760
    // 0x802C6720: addiu       $s0, $zero, 0x6
    ctx->r16 = ADD32(0, 0X6);
        goto L_802C6760;
    // 0x802C6720: addiu       $s0, $zero, 0x6
    ctx->r16 = ADD32(0, 0X6);
L_802C6724:
    // 0x802C6724: b           L_802C6760
    // 0x802C6728: addiu       $s0, $zero, 0x4
    ctx->r16 = ADD32(0, 0X4);
        goto L_802C6760;
    // 0x802C6728: addiu       $s0, $zero, 0x4
    ctx->r16 = ADD32(0, 0X4);
L_802C672C:
    // 0x802C672C: lw          $v0, 0x0($s5)
    ctx->r2 = MEM_W(ctx->r21, 0X0);
    // 0x802C6730: bne         $s4, $v0, L_802C6740
    if (ctx->r20 != ctx->r2) {
        // 0x802C6734: nop
    
            goto L_802C6740;
    }
    // 0x802C6734: nop

    // 0x802C6738: b           L_802C6760
    // 0x802C673C: addiu       $s0, $zero, 0x7
    ctx->r16 = ADD32(0, 0X7);
        goto L_802C6760;
    // 0x802C673C: addiu       $s0, $zero, 0x7
    ctx->r16 = ADD32(0, 0X7);
L_802C6740:
    // 0x802C6740: b           L_802C6760
    // 0x802C6744: or          $s0, $zero, $zero
    ctx->r16 = 0 | 0;
        goto L_802C6760;
    // 0x802C6744: or          $s0, $zero, $zero
    ctx->r16 = 0 | 0;
L_802C6748:
    // 0x802C6748: lw          $v0, 0x0($s5)
    ctx->r2 = MEM_W(ctx->r21, 0X0);
    // 0x802C674C: or          $s0, $zero, $zero
    ctx->r16 = 0 | 0;
    // 0x802C6750: bne         $s4, $v0, L_802C6760
    if (ctx->r20 != ctx->r2) {
        // 0x802C6754: nop
    
            goto L_802C6760;
    }
    // 0x802C6754: nop

    // 0x802C6758: b           L_802C6760
    // 0x802C675C: addiu       $s0, $zero, 0x7
    ctx->r16 = ADD32(0, 0X7);
        goto L_802C6760;
    // 0x802C675C: addiu       $s0, $zero, 0x7
    ctx->r16 = ADD32(0, 0X7);
L_802C6760:
    // 0x802C6760: bne         $s3, $zero, L_802C6790
    if (ctx->r19 != 0) {
        // 0x802C6764: lui         $t2, 0x802C
        ctx->r10 = S32(0X802C << 16);
            goto L_802C6790;
    }
    // 0x802C6764: lui         $t2, 0x802C
    ctx->r10 = S32(0X802C << 16);
    // 0x802C6768: bne         $s4, $v0, L_802C6778
    if (ctx->r20 != ctx->r2) {
        // 0x802C676C: or          $s1, $zero, $zero
        ctx->r17 = 0 | 0;
            goto L_802C6778;
    }
    // 0x802C676C: or          $s1, $zero, $zero
    ctx->r17 = 0 | 0;
    // 0x802C6770: b           L_802C677C
    // 0x802C6774: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
        goto L_802C677C;
    // 0x802C6774: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
L_802C6778:
    // 0x802C6778: or          $a2, $v0, $zero
    ctx->r6 = ctx->r2 | 0;
L_802C677C:
    // 0x802C677C: sll         $t1, $a2, 2
    ctx->r9 = S32(ctx->r6 << 2);
    // 0x802C6780: addu        $t2, $t2, $t1
    ctx->r10 = ADD32(ctx->r10, ctx->r9);
    // 0x802C6784: lw          $t2, 0x6AD4($t2)
    ctx->r10 = MEM_W(ctx->r10, 0X6AD4);
    // 0x802C6788: b           L_802C681C
    // 0x802C678C: sw          $t2, 0xB8($sp)
    MEM_W(0XB8, ctx->r29) = ctx->r10;
        goto L_802C681C;
    // 0x802C678C: sw          $t2, 0xB8($sp)
    MEM_W(0XB8, ctx->r29) = ctx->r10;
L_802C6790:
    // 0x802C6790: bne         $s3, $at, L_802C67C0
    if (ctx->r19 != ctx->r1) {
        // 0x802C6794: addiu       $a0, $sp, 0x94
        ctx->r4 = ADD32(ctx->r29, 0X94);
            goto L_802C67C0;
    }
    // 0x802C6794: addiu       $a0, $sp, 0x94
    ctx->r4 = ADD32(ctx->r29, 0X94);
    // 0x802C6798: bne         $s4, $v0, L_802C67A8
    if (ctx->r20 != ctx->r2) {
        // 0x802C679C: addiu       $s1, $zero, 0x1
        ctx->r17 = ADD32(0, 0X1);
            goto L_802C67A8;
    }
    // 0x802C679C: addiu       $s1, $zero, 0x1
    ctx->r17 = ADD32(0, 0X1);
    // 0x802C67A0: b           L_802C67AC
    // 0x802C67A4: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
        goto L_802C67AC;
    // 0x802C67A4: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
L_802C67A8:
    // 0x802C67A8: or          $a2, $v0, $zero
    ctx->r6 = ctx->r2 | 0;
L_802C67AC:
    // 0x802C67AC: lui         $a1, 0x802C
    ctx->r5 = S32(0X802C << 16);
    // 0x802C67B0: jal         0x800CA210
    // 0x802C67B4: addiu       $a1, $a1, 0x6B24
    ctx->r5 = ADD32(ctx->r5, 0X6B24);
    func_800CA210(rdram, ctx);
        goto after_14;
    // 0x802C67B4: addiu       $a1, $a1, 0x6B24
    ctx->r5 = ADD32(ctx->r5, 0X6B24);
    after_14:
    // 0x802C67B8: b           L_802C6820
    // 0x802C67BC: addiu       $t5, $zero, 0x80
    ctx->r13 = ADD32(0, 0X80);
        goto L_802C6820;
    // 0x802C67BC: addiu       $t5, $zero, 0x80
    ctx->r13 = ADD32(0, 0X80);
L_802C67C0:
    // 0x802C67C0: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x802C67C4: bne         $s3, $at, L_802C67F8
    if (ctx->r19 != ctx->r1) {
        // 0x802C67C8: lui         $t4, 0x802C
        ctx->r12 = S32(0X802C << 16);
            goto L_802C67F8;
    }
    // 0x802C67C8: lui         $t4, 0x802C
    ctx->r12 = S32(0X802C << 16);
    // 0x802C67CC: bne         $s4, $v0, L_802C67DC
    if (ctx->r20 != ctx->r2) {
        // 0x802C67D0: addiu       $s1, $zero, 0x1
        ctx->r17 = ADD32(0, 0X1);
            goto L_802C67DC;
    }
    // 0x802C67D0: addiu       $s1, $zero, 0x1
    ctx->r17 = ADD32(0, 0X1);
    // 0x802C67D4: b           L_802C67E0
    // 0x802C67D8: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
        goto L_802C67E0;
    // 0x802C67D8: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
L_802C67DC:
    // 0x802C67DC: or          $a2, $v0, $zero
    ctx->r6 = ctx->r2 | 0;
L_802C67E0:
    // 0x802C67E0: lui         $a1, 0x802C
    ctx->r5 = S32(0X802C << 16);
    // 0x802C67E4: addiu       $a1, $a1, 0x6B28
    ctx->r5 = ADD32(ctx->r5, 0X6B28);
    // 0x802C67E8: jal         0x800CA210
    // 0x802C67EC: addiu       $a0, $sp, 0x94
    ctx->r4 = ADD32(ctx->r29, 0X94);
    func_800CA210(rdram, ctx);
        goto after_15;
    // 0x802C67EC: addiu       $a0, $sp, 0x94
    ctx->r4 = ADD32(ctx->r29, 0X94);
    after_15:
    // 0x802C67F0: b           L_802C6820
    // 0x802C67F4: addiu       $t5, $zero, 0x80
    ctx->r13 = ADD32(0, 0X80);
        goto L_802C6820;
    // 0x802C67F4: addiu       $t5, $zero, 0x80
    ctx->r13 = ADD32(0, 0X80);
L_802C67F8:
    // 0x802C67F8: bne         $s4, $v0, L_802C6808
    if (ctx->r20 != ctx->r2) {
        // 0x802C67FC: or          $s1, $zero, $zero
        ctx->r17 = 0 | 0;
            goto L_802C6808;
    }
    // 0x802C67FC: or          $s1, $zero, $zero
    ctx->r17 = 0 | 0;
    // 0x802C6800: b           L_802C680C
    // 0x802C6804: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
        goto L_802C680C;
    // 0x802C6804: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
L_802C6808:
    // 0x802C6808: or          $a2, $v0, $zero
    ctx->r6 = ctx->r2 | 0;
L_802C680C:
    // 0x802C680C: sll         $t3, $a2, 2
    ctx->r11 = S32(ctx->r6 << 2);
    // 0x802C6810: addu        $t4, $t4, $t3
    ctx->r12 = ADD32(ctx->r12, ctx->r11);
    // 0x802C6814: lw          $t4, 0x6AE4($t4)
    ctx->r12 = MEM_W(ctx->r12, 0X6AE4);
    // 0x802C6818: sw          $t4, 0xB8($sp)
    MEM_W(0XB8, ctx->r29) = ctx->r12;
L_802C681C:
    // 0x802C681C: addiu       $t5, $zero, 0x80
    ctx->r13 = ADD32(0, 0X80);
L_802C6820:
    // 0x802C6820: sw          $t5, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r13;
    // 0x802C6824: addiu       $t5, $zero, 0xFF
    ctx->r13 = ADD32(0, 0XFF);
    // 0x802C6828: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C682C: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C6830: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C6834: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C6838: addiu       $t1, $zero, 0xFF
    ctx->r9 = ADD32(0, 0XFF);
    // 0x802C683C: addiu       $t2, $zero, 0xFF
    ctx->r10 = ADD32(0, 0XFF);
    // 0x802C6840: addiu       $t3, $zero, 0xFF
    ctx->r11 = ADD32(0, 0XFF);
    // 0x802C6844: addiu       $t4, $zero, 0xFF
    ctx->r12 = ADD32(0, 0XFF);
    // 0x802C6848: sw          $t4, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r12;
    // 0x802C684C: sw          $t3, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r11;
    // 0x802C6850: sw          $t2, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r10;
    // 0x802C6854: sw          $t1, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r9;
    // 0x802C6858: sw          $t9, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r25;
    // 0x802C685C: sw          $t8, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r24;
    // 0x802C6860: sw          $t7, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r15;
    // 0x802C6864: sw          $t6, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r14;
    // 0x802C6868: sw          $t5, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r13;
    // 0x802C686C: or          $a0, $s2, $zero
    ctx->r4 = ctx->r18 | 0;
    // 0x802C6870: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    // 0x802C6874: addiu       $a2, $zero, 0x80
    ctx->r6 = ADD32(0, 0X80);
    // 0x802C6878: jal         0x801E946C
    // 0x802C687C: addiu       $a3, $zero, 0x80
    ctx->r7 = ADD32(0, 0X80);
    func_801E946C(rdram, ctx);
        goto after_16;
    // 0x802C687C: addiu       $a3, $zero, 0x80
    ctx->r7 = ADD32(0, 0X80);
    after_16:
    // 0x802C6880: bne         $s1, $zero, L_802C68AC
    if (ctx->r17 != 0) {
        // 0x802C6884: or          $s2, $v0, $zero
        ctx->r18 = ctx->r2 | 0;
            goto L_802C68AC;
    }
    // 0x802C6884: or          $s2, $v0, $zero
    ctx->r18 = ctx->r2 | 0;
    // 0x802C6888: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C688C: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C6890: lw          $a2, 0xB8($sp)
    ctx->r6 = MEM_W(ctx->r29, 0XB8);
    // 0x802C6894: addiu       $a3, $zero, 0x12E
    ctx->r7 = ADD32(0, 0X12E);
    // 0x802C6898: sw          $s6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r22;
    // 0x802C689C: jal         0x801E3EE0
    // 0x802C68A0: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    func_801E3EE0(rdram, ctx);
        goto after_17;
    // 0x802C68A0: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    after_17:
    // 0x802C68A4: b           L_802C68C8
    // 0x802C68A8: or          $s2, $v0, $zero
    ctx->r18 = ctx->r2 | 0;
        goto L_802C68C8;
    // 0x802C68A8: or          $s2, $v0, $zero
    ctx->r18 = ctx->r2 | 0;
L_802C68AC:
    // 0x802C68AC: or          $a0, $s2, $zero
    ctx->r4 = ctx->r18 | 0;
    // 0x802C68B0: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C68B4: addiu       $a2, $sp, 0x94
    ctx->r6 = ADD32(ctx->r29, 0X94);
    // 0x802C68B8: addiu       $a3, $zero, 0x12E
    ctx->r7 = ADD32(0, 0X12E);
    // 0x802C68BC: jal         0x801E9858
    // 0x802C68C0: sw          $s6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r22;
    func_801E9858(rdram, ctx);
        goto after_18;
    // 0x802C68C0: sw          $s6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r22;
    after_18:
    // 0x802C68C4: or          $s2, $v0, $zero
    ctx->r18 = ctx->r2 | 0;
L_802C68C8:
    // 0x802C68C8: lw          $t6, 0x6C($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X6C);
    // 0x802C68CC: addiu       $s3, $s3, 0x1
    ctx->r19 = ADD32(ctx->r19, 0X1);
    // 0x802C68D0: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x802C68D4: addiu       $t7, $t6, 0x14
    ctx->r15 = ADD32(ctx->r14, 0X14);
    // 0x802C68D8: sw          $t7, 0x6C($sp)
    MEM_W(0X6C, ctx->r29) = ctx->r15;
    // 0x802C68DC: addiu       $s7, $s7, 0x4
    ctx->r23 = ADD32(ctx->r23, 0X4);
    // 0x802C68E0: addiu       $fp, $fp, 0x4
    ctx->r30 = ADD32(ctx->r30, 0X4);
    // 0x802C68E4: addiu       $s6, $s6, 0x14
    ctx->r22 = ADD32(ctx->r22, 0X14);
    // 0x802C68E8: bne         $s3, $at, L_802C65D8
    if (ctx->r19 != ctx->r1) {
        // 0x802C68EC: addiu       $s5, $s5, 0x4
        ctx->r21 = ADD32(ctx->r21, 0X4);
            goto L_802C65D8;
    }
    // 0x802C68EC: addiu       $s5, $s5, 0x4
    ctx->r21 = ADD32(ctx->r21, 0X4);
    // 0x802C68F0: lw          $t8, 0x78($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X78);
    // 0x802C68F4: lui         $t9, 0x801D
    ctx->r25 = S32(0X801D << 16);
    // 0x802C68F8: addiu       $t9, $t9, -0x4CC8
    ctx->r25 = ADD32(ctx->r25, -0X4CC8);
    // 0x802C68FC: beq         $t8, $t9, L_802C6924
    if (ctx->r24 == ctx->r25) {
        // 0x802C6900: or          $v0, $zero, $zero
        ctx->r2 = 0 | 0;
            goto L_802C6924;
    }
    // 0x802C6900: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    // 0x802C6904: lw          $t2, 0x7C($sp)
    ctx->r10 = MEM_W(ctx->r29, 0X7C);
    // 0x802C6908: lui         $t3, 0x800E
    ctx->r11 = S32(0X800E << 16);
    // 0x802C690C: lw          $t1, 0x0($t8)
    ctx->r9 = MEM_W(ctx->r24, 0X0);
    // 0x802C6910: addu        $t3, $t3, $t2
    ctx->r11 = ADD32(ctx->r11, ctx->r10);
    // 0x802C6914: lw          $t3, -0x5678($t3)
    ctx->r11 = MEM_W(ctx->r11, -0X5678);
    // 0x802C6918: beq         $t1, $t3, L_802C6924
    if (ctx->r9 == ctx->r11) {
        // 0x802C691C: nop
    
            goto L_802C6924;
    }
    // 0x802C691C: nop

    // 0x802C6920: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
L_802C6924:
    // 0x802C6924: beq         $v0, $zero, L_802C69CC
    if (ctx->r2 == 0) {
        // 0x802C6928: or          $a0, $s2, $zero
        ctx->r4 = ctx->r18 | 0;
            goto L_802C69CC;
    }
    // 0x802C6928: or          $a0, $s2, $zero
    ctx->r4 = ctx->r18 | 0;
    // 0x802C692C: addiu       $t4, $zero, 0xFF
    ctx->r12 = ADD32(0, 0XFF);
    // 0x802C6930: addiu       $t5, $zero, 0xFF
    ctx->r13 = ADD32(0, 0XFF);
    // 0x802C6934: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C6938: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C693C: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C6940: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C6944: addiu       $t2, $zero, 0xFF
    ctx->r10 = ADD32(0, 0XFF);
    // 0x802C6948: addiu       $t1, $zero, 0xFF
    ctx->r9 = ADD32(0, 0XFF);
    // 0x802C694C: addiu       $t3, $zero, 0xFF
    ctx->r11 = ADD32(0, 0XFF);
    // 0x802C6950: sw          $t3, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r11;
    // 0x802C6954: sw          $t1, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r9;
    // 0x802C6958: sw          $t2, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r10;
    // 0x802C695C: sw          $t8, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r24;
    // 0x802C6960: sw          $t9, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r25;
    // 0x802C6964: sw          $t7, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r15;
    // 0x802C6968: sw          $t6, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r14;
    // 0x802C696C: sw          $t5, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r13;
    // 0x802C6970: sw          $t4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r12;
    // 0x802C6974: sw          $t4, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r12;
    // 0x802C6978: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C697C: addiu       $a2, $zero, 0xFF
    ctx->r6 = ADD32(0, 0XFF);
    // 0x802C6980: jal         0x801E946C
    // 0x802C6984: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    func_801E946C(rdram, ctx);
        goto after_19;
    // 0x802C6984: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    after_19:
    // 0x802C6988: addiu       $t5, $zero, 0xCA
    ctx->r13 = ADD32(0, 0XCA);
    // 0x802C698C: sw          $t5, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r13;
    // 0x802C6990: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C6994: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C6998: addiu       $a2, $zero, 0x41
    ctx->r6 = ADD32(0, 0X41);
    // 0x802C699C: addiu       $a3, $zero, 0x50
    ctx->r7 = ADD32(0, 0X50);
    // 0x802C69A0: jal         0x801E3EE0
    // 0x802C69A4: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    func_801E3EE0(rdram, ctx);
        goto after_20;
    // 0x802C69A4: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    after_20:
    // 0x802C69A8: addiu       $t6, $zero, 0xCA
    ctx->r14 = ADD32(0, 0XCA);
    // 0x802C69AC: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x802C69B0: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C69B4: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C69B8: addiu       $a2, $zero, 0x44
    ctx->r6 = ADD32(0, 0X44);
    // 0x802C69BC: addiu       $a3, $zero, 0x96
    ctx->r7 = ADD32(0, 0X96);
    // 0x802C69C0: jal         0x801E3EE0
    // 0x802C69C4: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    func_801E3EE0(rdram, ctx);
        goto after_21;
    // 0x802C69C4: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    after_21:
    // 0x802C69C8: or          $s2, $v0, $zero
    ctx->r18 = ctx->r2 | 0;
L_802C69CC:
    // 0x802C69CC: lw          $ra, 0x64($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X64);
L_802C69D0:
    // 0x802C69D0: or          $v0, $s2, $zero
    ctx->r2 = ctx->r18 | 0;
    // 0x802C69D4: lw          $s2, 0x48($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X48);
    // 0x802C69D8: lw          $s0, 0x40($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X40);
    // 0x802C69DC: lw          $s1, 0x44($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X44);
    // 0x802C69E0: lw          $s3, 0x4C($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X4C);
    // 0x802C69E4: lw          $s4, 0x50($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X50);
    // 0x802C69E8: lw          $s5, 0x54($sp)
    ctx->r21 = MEM_W(ctx->r29, 0X54);
    // 0x802C69EC: lw          $s6, 0x58($sp)
    ctx->r22 = MEM_W(ctx->r29, 0X58);
    // 0x802C69F0: lw          $s7, 0x5C($sp)
    ctx->r23 = MEM_W(ctx->r29, 0X5C);
    // 0x802C69F4: lw          $fp, 0x60($sp)
    ctx->r30 = MEM_W(ctx->r29, 0X60);
    // 0x802C69F8: jr          $ra
    // 0x802C69FC: addiu       $sp, $sp, 0xD0
    ctx->r29 = ADD32(ctx->r29, 0XD0);
    return;
    // 0x802C69FC: addiu       $sp, $sp, 0xD0
    ctx->r29 = ADD32(ctx->r29, 0XD0);
;}
RECOMP_FUNC void func_i10_802C6A00(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C6A00: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x802C6A04: addiu       $v0, $v0, -0x54DC
    ctx->r2 = ADD32(ctx->r2, -0X54DC);
    // 0x802C6A08: lw          $t6, 0x0($v0)
    ctx->r14 = MEM_W(ctx->r2, 0X0);
    // 0x802C6A0C: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C6A10: addiu       $t7, $zero, 0x45
    ctx->r15 = ADD32(0, 0X45);
    // 0x802C6A14: sw          $t6, -0x19CC($at)
    MEM_W(-0X19CC, ctx->r1) = ctx->r14;
    // 0x802C6A18: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C6A1C: sw          $a0, -0x19D0($at)
    MEM_W(-0X19D0, ctx->r1) = ctx->r4;
    // 0x802C6A20: sw          $t7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r15;
    // 0x802C6A24: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C6A28: addiu       $t8, $zero, 0xE
    ctx->r24 = ADD32(0, 0XE);
    // 0x802C6A2C: sw          $t8, -0x19C8($at)
    MEM_W(-0X19C8, ctx->r1) = ctx->r24;
    // 0x802C6A30: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C6A34: addiu       $t9, $zero, 0x1
    ctx->r25 = ADD32(0, 0X1);
    // 0x802C6A38: sw          $t9, -0x19C4($at)
    MEM_W(-0X19C4, ctx->r1) = ctx->r25;
    // 0x802C6A3C: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C6A40: sw          $zero, -0x19C0($at)
    MEM_W(-0X19C0, ctx->r1) = 0;
    // 0x802C6A44: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C6A48: sw          $zero, -0x19BC($at)
    MEM_W(-0X19BC, ctx->r1) = 0;
    // 0x802C6A4C: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x802C6A50: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x802C6A54: sw          $zero, -0x54E4($at)
    MEM_W(-0X54E4, ctx->r1) = 0;
    // 0x802C6A58: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x802C6A5C: lui         $at, 0x800D
    ctx->r1 = S32(0X800D << 16);
    // 0x802C6A60: addiu       $t0, $zero, 0x2
    ctx->r8 = ADD32(0, 0X2);
    // 0x802C6A64: sw          $t0, 0x461C($at)
    MEM_W(0X461C, ctx->r1) = ctx->r8;
    // 0x802C6A68: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    // 0x802C6A6C: addiu       $a1, $zero, 0x4
    ctx->r5 = ADD32(0, 0X4);
    // 0x802C6A70: jal         0x801E6FB0
    // 0x802C6A74: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    FadeTransition_SetProps(rdram, ctx);
        goto after_0;
    // 0x802C6A74: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    after_0:
    // 0x802C6A78: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    // 0x802C6A7C: jal         0x801E6A4C
    // 0x802C6A80: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_801E6A4C(rdram, ctx);
        goto after_1;
    // 0x802C6A80: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_1:
    // 0x802C6A84: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x802C6A88: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x802C6A8C: jr          $ra
    // 0x802C6A90: nop

    return;
    // 0x802C6A90: nop

    // 0x802C6A94: nop

    // 0x802C6A98: nop

    // 0x802C6A9C: nop

;}
