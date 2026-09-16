#include "recomp.h"
#include "funcs.h"

RECOMP_FUNC void func_i11_802C5800(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C5800: addiu       $sp, $sp, -0xA8
    ctx->r29 = ADD32(ctx->r29, -0XA8);
    // 0x802C5804: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x802C5808: addiu       $v0, $v0, -0x19C4
    ctx->r2 = ADD32(ctx->r2, -0X19C4);
    // 0x802C580C: lw          $t6, 0x0($v0)
    ctx->r14 = MEM_W(ctx->r2, 0X0);
    // 0x802C5810: sw          $s2, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r18;
    // 0x802C5814: or          $s2, $a0, $zero
    ctx->r18 = ctx->r4 | 0;
    // 0x802C5818: sw          $ra, 0x64($sp)
    MEM_W(0X64, ctx->r29) = ctx->r31;
    // 0x802C581C: sw          $fp, 0x60($sp)
    MEM_W(0X60, ctx->r29) = ctx->r30;
    // 0x802C5820: sw          $s7, 0x5C($sp)
    MEM_W(0X5C, ctx->r29) = ctx->r23;
    // 0x802C5824: sw          $s6, 0x58($sp)
    MEM_W(0X58, ctx->r29) = ctx->r22;
    // 0x802C5828: sw          $s5, 0x54($sp)
    MEM_W(0X54, ctx->r29) = ctx->r21;
    // 0x802C582C: sw          $s4, 0x50($sp)
    MEM_W(0X50, ctx->r29) = ctx->r20;
    // 0x802C5830: sw          $s3, 0x4C($sp)
    MEM_W(0X4C, ctx->r29) = ctx->r19;
    // 0x802C5834: sw          $s1, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r17;
    // 0x802C5838: beq         $t6, $zero, L_802C5868
    if (ctx->r14 == 0) {
        // 0x802C583C: sw          $s0, 0x40($sp)
        MEM_W(0X40, ctx->r29) = ctx->r16;
            goto L_802C5868;
    }
    // 0x802C583C: sw          $s0, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r16;
    // 0x802C5840: sw          $zero, 0x0($v0)
    MEM_W(0X0, ctx->r2) = 0;
    // 0x802C5844: lui         $t7, 0x800E
    ctx->r15 = S32(0X800E << 16);
    // 0x802C5848: lw          $t7, -0x54DC($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X54DC);
    // 0x802C584C: addiu       $at, $zero, 0x48
    ctx->r1 = ADD32(0, 0X48);
    // 0x802C5850: bne         $t7, $at, L_802C5868
    if (ctx->r15 != ctx->r1) {
        // 0x802C5854: nop
    
            goto L_802C5868;
    }
    // 0x802C5854: nop

    // 0x802C5858: jal         0x80093C44
    // 0x802C585C: nop

    func_80093C44(rdram, ctx);
        goto after_0;
    // 0x802C585C: nop

    after_0:
    // 0x802C5860: b           L_802C5D1C
    // 0x802C5864: lw          $ra, 0x64($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X64);
        goto L_802C5D1C;
    // 0x802C5864: lw          $ra, 0x64($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X64);
L_802C5868:
    // 0x802C5868: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x802C586C: or          $v0, $s2, $zero
    ctx->r2 = ctx->r18 | 0;
    // 0x802C5870: sw          $zero, -0x54D4($at)
    MEM_W(-0X54D4, ctx->r1) = 0;
    // 0x802C5874: addiu       $s2, $s2, 0x8
    ctx->r18 = ADD32(ctx->r18, 0X8);
    // 0x802C5878: lui         $t8, 0x103
    ctx->r24 = S32(0X103 << 16);
    // 0x802C587C: lui         $t9, 0x700
    ctx->r25 = S32(0X700 << 16);
    // 0x802C5880: addiu       $t9, $t9, 0x0
    ctx->r25 = ADD32(ctx->r25, 0X0);
    // 0x802C5884: ori         $t8, $t8, 0x40
    ctx->r24 = ctx->r24 | 0X40;
    // 0x802C5888: or          $v1, $s2, $zero
    ctx->r3 = ctx->r18 | 0;
    // 0x802C588C: sw          $t8, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r24;
    // 0x802C5890: sw          $t9, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r25;
    // 0x802C5894: addiu       $s2, $s2, 0x8
    ctx->r18 = ADD32(ctx->r18, 0X8);
    // 0x802C5898: lui         $t0, 0x102
    ctx->r8 = S32(0X102 << 16);
    // 0x802C589C: lui         $t1, 0x200
    ctx->r9 = S32(0X200 << 16);
    // 0x802C58A0: addiu       $t1, $t1, 0xA40
    ctx->r9 = ADD32(ctx->r9, 0XA40);
    // 0x802C58A4: ori         $t0, $t0, 0x40
    ctx->r8 = ctx->r8 | 0X40;
    // 0x802C58A8: or          $a0, $s2, $zero
    ctx->r4 = ctx->r18 | 0;
    // 0x802C58AC: sw          $t0, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r8;
    // 0x802C58B0: sw          $t1, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r9;
    // 0x802C58B4: addiu       $s2, $s2, 0x8
    ctx->r18 = ADD32(ctx->r18, 0X8);
    // 0x802C58B8: lui         $t2, 0x107
    ctx->r10 = S32(0X107 << 16);
    // 0x802C58BC: lui         $a2, 0x600
    ctx->r6 = S32(0X600 << 16);
    // 0x802C58C0: addiu       $t2, $t2, -0xAB0
    ctx->r10 = ADD32(ctx->r10, -0XAB0);
    // 0x802C58C4: or          $a1, $s2, $zero
    ctx->r5 = ctx->r18 | 0;
    // 0x802C58C8: sw          $t2, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r10;
    // 0x802C58CC: sw          $a2, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r6;
    // 0x802C58D0: lui         $t3, 0x107
    ctx->r11 = S32(0X107 << 16);
    // 0x802C58D4: addiu       $t3, $t3, -0x9D8
    ctx->r11 = ADD32(ctx->r11, -0X9D8);
    // 0x802C58D8: sw          $t3, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r11;
    // 0x802C58DC: sw          $a2, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r6;
    // 0x802C58E0: addiu       $s2, $s2, 0x8
    ctx->r18 = ADD32(ctx->r18, 0X8);
    // 0x802C58E4: addiu       $s0, $zero, 0x64
    ctx->r16 = ADD32(0, 0X64);
L_802C58E8:
    // 0x802C58E8: addiu       $t4, $zero, 0x94
    ctx->r12 = ADD32(0, 0X94);
    // 0x802C58EC: addiu       $t5, $zero, 0x10
    ctx->r13 = ADD32(0, 0X10);
    // 0x802C58F0: sw          $t5, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r13;
    // 0x802C58F4: sw          $t4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r12;
    // 0x802C58F8: or          $a0, $s2, $zero
    ctx->r4 = ctx->r18 | 0;
    // 0x802C58FC: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C5900: addiu       $a2, $zero, 0x1C
    ctx->r6 = ADD32(0, 0X1C);
    // 0x802C5904: jal         0x80094338
    // 0x802C5908: or          $a3, $s0, $zero
    ctx->r7 = ctx->r16 | 0;
    func_80094338(rdram, ctx);
        goto after_1;
    // 0x802C5908: or          $a3, $s0, $zero
    ctx->r7 = ctx->r16 | 0;
    after_1:
    // 0x802C590C: addiu       $t6, $zero, 0x69
    ctx->r14 = ADD32(0, 0X69);
    // 0x802C5910: addiu       $t7, $zero, 0x10
    ctx->r15 = ADD32(0, 0X10);
    // 0x802C5914: sw          $t7, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r15;
    // 0x802C5918: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x802C591C: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C5920: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C5924: addiu       $a2, $zero, 0x11A
    ctx->r6 = ADD32(0, 0X11A);
    // 0x802C5928: jal         0x80094338
    // 0x802C592C: or          $a3, $s0, $zero
    ctx->r7 = ctx->r16 | 0;
    func_80094338(rdram, ctx);
        goto after_2;
    // 0x802C592C: or          $a3, $s0, $zero
    ctx->r7 = ctx->r16 | 0;
    after_2:
    // 0x802C5930: addiu       $s0, $s0, 0x15
    ctx->r16 = ADD32(ctx->r16, 0X15);
    // 0x802C5934: slti        $at, $s0, 0xA3
    ctx->r1 = SIGNED(ctx->r16) < 0XA3 ? 1 : 0;
    // 0x802C5938: bne         $at, $zero, L_802C58E8
    if (ctx->r1 != 0) {
        // 0x802C593C: or          $s2, $v0, $zero
        ctx->r18 = ctx->r2 | 0;
            goto L_802C58E8;
    }
    // 0x802C593C: or          $s2, $v0, $zero
    ctx->r18 = ctx->r2 | 0;
    // 0x802C5940: addiu       $t8, $zero, 0x6B
    ctx->r24 = ADD32(0, 0X6B);
    // 0x802C5944: addiu       $t9, $zero, 0x10
    ctx->r25 = ADD32(0, 0X10);
    // 0x802C5948: sw          $t9, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r25;
    // 0x802C594C: sw          $t8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r24;
    // 0x802C5950: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C5954: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C5958: addiu       $a2, $zero, 0x9E
    ctx->r6 = ADD32(0, 0X9E);
    // 0x802C595C: jal         0x80094338
    // 0x802C5960: addiu       $a3, $zero, 0xA3
    ctx->r7 = ADD32(0, 0XA3);
    func_80094338(rdram, ctx);
        goto after_3;
    // 0x802C5960: addiu       $a3, $zero, 0xA3
    ctx->r7 = ADD32(0, 0XA3);
    after_3:
    // 0x802C5964: addiu       $t0, $zero, 0xFF
    ctx->r8 = ADD32(0, 0XFF);
    // 0x802C5968: addiu       $t1, $zero, 0xFF
    ctx->r9 = ADD32(0, 0XFF);
    // 0x802C596C: addiu       $t2, $zero, 0xFF
    ctx->r10 = ADD32(0, 0XFF);
    // 0x802C5970: addiu       $t3, $zero, 0xFF
    ctx->r11 = ADD32(0, 0XFF);
    // 0x802C5974: addiu       $t4, $zero, 0xFF
    ctx->r12 = ADD32(0, 0XFF);
    // 0x802C5978: addiu       $t5, $zero, 0xFF
    ctx->r13 = ADD32(0, 0XFF);
    // 0x802C597C: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C5980: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C5984: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C5988: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C598C: sw          $t9, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r25;
    // 0x802C5990: sw          $t8, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r24;
    // 0x802C5994: sw          $t7, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r15;
    // 0x802C5998: sw          $t6, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r14;
    // 0x802C599C: sw          $t5, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r13;
    // 0x802C59A0: sw          $t4, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r12;
    // 0x802C59A4: sw          $t3, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r11;
    // 0x802C59A8: sw          $t2, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r10;
    // 0x802C59AC: sw          $t1, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r9;
    // 0x802C59B0: sw          $t0, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r8;
    // 0x802C59B4: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C59B8: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C59BC: addiu       $a2, $zero, 0xFF
    ctx->r6 = ADD32(0, 0XFF);
    // 0x802C59C0: jal         0x801E946C
    // 0x802C59C4: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    func_801E946C(rdram, ctx);
        goto after_4;
    // 0x802C59C4: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    after_4:
    // 0x802C59C8: addiu       $t0, $zero, 0x32
    ctx->r8 = ADD32(0, 0X32);
    // 0x802C59CC: sw          $t0, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r8;
    // 0x802C59D0: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C59D4: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C59D8: addiu       $a2, $zero, 0x13
    ctx->r6 = ADD32(0, 0X13);
    // 0x802C59DC: addiu       $a3, $zero, 0xAE
    ctx->r7 = ADD32(0, 0XAE);
    // 0x802C59E0: jal         0x801E3EE0
    // 0x802C59E4: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    func_801E3EE0(rdram, ctx);
        goto after_5;
    // 0x802C59E4: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    after_5:
    // 0x802C59E8: lui         $s4, 0x802C
    ctx->r20 = S32(0X802C << 16);
    // 0x802C59EC: lui         $s3, 0x800E
    ctx->r19 = S32(0X800E << 16);
    // 0x802C59F0: lui         $s7, 0x802C
    ctx->r23 = S32(0X802C << 16);
    // 0x802C59F4: or          $s2, $v0, $zero
    ctx->r18 = ctx->r2 | 0;
    // 0x802C59F8: addiu       $s7, $s7, 0x6150
    ctx->r23 = ADD32(ctx->r23, 0X6150);
    // 0x802C59FC: addiu       $s3, $s3, -0x5614
    ctx->r19 = ADD32(ctx->r19, -0X5614);
    // 0x802C5A00: addiu       $s4, $s4, 0x6160
    ctx->r20 = ADD32(ctx->r20, 0X6160);
    // 0x802C5A04: or          $s1, $zero, $zero
    ctx->r17 = 0 | 0;
    // 0x802C5A08: addiu       $s5, $zero, 0x67
    ctx->r21 = ADD32(0, 0X67);
    // 0x802C5A0C: addiu       $s6, $zero, 0x66
    ctx->r22 = ADD32(0, 0X66);
    // 0x802C5A10: lw          $fp, 0x9C($sp)
    ctx->r30 = MEM_W(ctx->r29, 0X9C);
L_802C5A14:
    // 0x802C5A14: lw          $t1, 0x0($s7)
    ctx->r9 = MEM_W(ctx->r23, 0X0);
    // 0x802C5A18: or          $a0, $s2, $zero
    ctx->r4 = ctx->r18 | 0;
    // 0x802C5A1C: addiu       $a2, $zero, 0xFF
    ctx->r6 = ADD32(0, 0XFF);
    // 0x802C5A20: bne         $s1, $t1, L_802C5A30
    if (ctx->r17 != ctx->r9) {
        // 0x802C5A24: addiu       $a3, $zero, 0xFF
        ctx->r7 = ADD32(0, 0XFF);
            goto L_802C5A30;
    }
    // 0x802C5A24: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    // 0x802C5A28: b           L_802C5A34
    // 0x802C5A2C: addiu       $a1, $zero, 0x6
    ctx->r5 = ADD32(0, 0X6);
        goto L_802C5A34;
    // 0x802C5A2C: addiu       $a1, $zero, 0x6
    ctx->r5 = ADD32(0, 0X6);
L_802C5A30:
    // 0x802C5A30: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
L_802C5A34:
    // 0x802C5A34: addiu       $t2, $zero, 0xFF
    ctx->r10 = ADD32(0, 0XFF);
    // 0x802C5A38: addiu       $t3, $zero, 0xFF
    ctx->r11 = ADD32(0, 0XFF);
    // 0x802C5A3C: addiu       $t4, $zero, 0xFF
    ctx->r12 = ADD32(0, 0XFF);
    // 0x802C5A40: addiu       $t5, $zero, 0xFF
    ctx->r13 = ADD32(0, 0XFF);
    // 0x802C5A44: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C5A48: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C5A4C: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C5A50: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C5A54: addiu       $t0, $zero, 0xFF
    ctx->r8 = ADD32(0, 0XFF);
    // 0x802C5A58: addiu       $t1, $zero, 0xFF
    ctx->r9 = ADD32(0, 0XFF);
    // 0x802C5A5C: sw          $t1, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r9;
    // 0x802C5A60: sw          $t0, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r8;
    // 0x802C5A64: sw          $t9, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r25;
    // 0x802C5A68: sw          $t8, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r24;
    // 0x802C5A6C: sw          $t7, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r15;
    // 0x802C5A70: sw          $t6, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r14;
    // 0x802C5A74: sw          $t5, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r13;
    // 0x802C5A78: sw          $t4, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r12;
    // 0x802C5A7C: sw          $t3, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r11;
    // 0x802C5A80: jal         0x801E946C
    // 0x802C5A84: sw          $t2, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r10;
    func_801E946C(rdram, ctx);
        goto after_6;
    // 0x802C5A84: sw          $t2, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r10;
    after_6:
    // 0x802C5A88: lh          $a3, 0x0($s4)
    ctx->r7 = MEM_H(ctx->r20, 0X0);
    // 0x802C5A8C: lw          $a2, 0x4($s4)
    ctx->r6 = MEM_W(ctx->r20, 0X4);
    // 0x802C5A90: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    // 0x802C5A94: sw          $s5, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r21;
    // 0x802C5A98: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C5A9C: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C5AA0: jal         0x801E3EE0
    // 0x802C5AA4: addiu       $a3, $a3, 0x26
    ctx->r7 = ADD32(ctx->r7, 0X26);
    func_801E3EE0(rdram, ctx);
        goto after_7;
    // 0x802C5AA4: addiu       $a3, $a3, 0x26
    ctx->r7 = ADD32(ctx->r7, 0X26);
    after_7:
    // 0x802C5AA8: lui         $a2, 0x802C
    ctx->r6 = S32(0X802C << 16);
    // 0x802C5AAC: addiu       $a2, $a2, 0x61B0
    ctx->r6 = ADD32(ctx->r6, 0X61B0);
    // 0x802C5AB0: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C5AB4: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C5AB8: addiu       $a3, $zero, 0x9E
    ctx->r7 = ADD32(0, 0X9E);
    // 0x802C5ABC: jal         0x801E9858
    // 0x802C5AC0: sw          $s6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r22;
    func_801E9858(rdram, ctx);
        goto after_8;
    // 0x802C5AC0: sw          $s6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r22;
    after_8:
    // 0x802C5AC4: lw          $t2, 0x0($s7)
    ctx->r10 = MEM_W(ctx->r23, 0X0);
    // 0x802C5AC8: or          $s2, $v0, $zero
    ctx->r18 = ctx->r2 | 0;
    // 0x802C5ACC: or          $a0, $s2, $zero
    ctx->r4 = ctx->r18 | 0;
    // 0x802C5AD0: bne         $s1, $t2, L_802C5B18
    if (ctx->r17 != ctx->r10) {
        // 0x802C5AD4: addiu       $a2, $zero, 0xFF
        ctx->r6 = ADD32(0, 0XFF);
            goto L_802C5B18;
    }
    // 0x802C5AD4: addiu       $a2, $zero, 0xFF
    ctx->r6 = ADD32(0, 0XFF);
    // 0x802C5AD8: sll         $t4, $s1, 2
    ctx->r12 = S32(ctx->r17 << 2);
    // 0x802C5ADC: lui         $t5, 0x802C
    ctx->r13 = S32(0X802C << 16);
    // 0x802C5AE0: addu        $t5, $t5, $t4
    ctx->r13 = ADD32(ctx->r13, ctx->r12);
    // 0x802C5AE4: lw          $t5, 0x6154($t5)
    ctx->r13 = MEM_W(ctx->r13, 0X6154);
    // 0x802C5AE8: lw          $t3, 0x0($s3)
    ctx->r11 = MEM_W(ctx->r19, 0X0);
    // 0x802C5AEC: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x802C5AF0: bne         $t3, $t5, L_802C5B00
    if (ctx->r11 != ctx->r13) {
        // 0x802C5AF4: nop
    
            goto L_802C5B00;
    }
    // 0x802C5AF4: nop

    // 0x802C5AF8: b           L_802C5B1C
    // 0x802C5AFC: addiu       $a1, $zero, 0x6
    ctx->r5 = ADD32(0, 0X6);
        goto L_802C5B1C;
    // 0x802C5AFC: addiu       $a1, $zero, 0x6
    ctx->r5 = ADD32(0, 0X6);
L_802C5B00:
    // 0x802C5B00: bne         $s1, $at, L_802C5B10
    if (ctx->r17 != ctx->r1) {
        // 0x802C5B04: nop
    
            goto L_802C5B10;
    }
    // 0x802C5B04: nop

    // 0x802C5B08: b           L_802C5B1C
    // 0x802C5B0C: addiu       $a1, $zero, 0x6
    ctx->r5 = ADD32(0, 0X6);
        goto L_802C5B1C;
    // 0x802C5B0C: addiu       $a1, $zero, 0x6
    ctx->r5 = ADD32(0, 0X6);
L_802C5B10:
    // 0x802C5B10: b           L_802C5B1C
    // 0x802C5B14: addiu       $a1, $zero, 0x4
    ctx->r5 = ADD32(0, 0X4);
        goto L_802C5B1C;
    // 0x802C5B14: addiu       $a1, $zero, 0x4
    ctx->r5 = ADD32(0, 0X4);
L_802C5B18:
    // 0x802C5B18: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
L_802C5B1C:
    // 0x802C5B1C: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C5B20: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C5B24: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C5B28: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C5B2C: addiu       $t0, $zero, 0xFF
    ctx->r8 = ADD32(0, 0XFF);
    // 0x802C5B30: addiu       $t1, $zero, 0xFF
    ctx->r9 = ADD32(0, 0XFF);
    // 0x802C5B34: addiu       $t2, $zero, 0xFF
    ctx->r10 = ADD32(0, 0XFF);
    // 0x802C5B38: addiu       $t4, $zero, 0xFF
    ctx->r12 = ADD32(0, 0XFF);
    // 0x802C5B3C: addiu       $t3, $zero, 0xFF
    ctx->r11 = ADD32(0, 0XFF);
    // 0x802C5B40: addiu       $t5, $zero, 0xFF
    ctx->r13 = ADD32(0, 0XFF);
    // 0x802C5B44: sw          $t5, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r13;
    // 0x802C5B48: sw          $t3, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r11;
    // 0x802C5B4C: sw          $t4, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r12;
    // 0x802C5B50: sw          $t2, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r10;
    // 0x802C5B54: sw          $t1, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r9;
    // 0x802C5B58: sw          $t0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r8;
    // 0x802C5B5C: sw          $t9, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r25;
    // 0x802C5B60: sw          $t8, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r24;
    // 0x802C5B64: sw          $t7, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r15;
    // 0x802C5B68: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x802C5B6C: jal         0x801E946C
    // 0x802C5B70: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    func_801E946C(rdram, ctx);
        goto after_9;
    // 0x802C5B70: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    after_9:
    // 0x802C5B74: bne         $s1, $zero, L_802C5B98
    if (ctx->r17 != 0) {
        // 0x802C5B78: or          $s2, $v0, $zero
        ctx->r18 = ctx->r2 | 0;
            goto L_802C5B98;
    }
    // 0x802C5B78: or          $s2, $v0, $zero
    ctx->r18 = ctx->r2 | 0;
    // 0x802C5B7C: lw          $t6, 0x0($s3)
    ctx->r14 = MEM_W(ctx->r19, 0X0);
    // 0x802C5B80: lui         $fp, 0x802C
    ctx->r30 = S32(0X802C << 16);
    // 0x802C5B84: or          $s0, $zero, $zero
    ctx->r16 = 0 | 0;
    // 0x802C5B88: sll         $t7, $t6, 2
    ctx->r15 = S32(ctx->r14 << 2);
    // 0x802C5B8C: addu        $fp, $fp, $t7
    ctx->r30 = ADD32(ctx->r30, ctx->r15);
    // 0x802C5B90: b           L_802C5BD4
    // 0x802C5B94: lw          $fp, 0x6178($fp)
    ctx->r30 = MEM_W(ctx->r30, 0X6178);
        goto L_802C5BD4;
    // 0x802C5B94: lw          $fp, 0x6178($fp)
    ctx->r30 = MEM_W(ctx->r30, 0X6178);
L_802C5B98:
    // 0x802C5B98: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x802C5B9C: bne         $s1, $at, L_802C5BC0
    if (ctx->r17 != ctx->r1) {
        // 0x802C5BA0: addiu       $s0, $zero, 0x1
        ctx->r16 = ADD32(0, 0X1);
            goto L_802C5BC0;
    }
    // 0x802C5BA0: addiu       $s0, $zero, 0x1
    ctx->r16 = ADD32(0, 0X1);
    // 0x802C5BA4: lw          $t8, 0x0($s3)
    ctx->r24 = MEM_W(ctx->r19, 0X0);
    // 0x802C5BA8: lui         $fp, 0x802C
    ctx->r30 = S32(0X802C << 16);
    // 0x802C5BAC: or          $s0, $zero, $zero
    ctx->r16 = 0 | 0;
    // 0x802C5BB0: sll         $t9, $t8, 2
    ctx->r25 = S32(ctx->r24 << 2);
    // 0x802C5BB4: addu        $fp, $fp, $t9
    ctx->r30 = ADD32(ctx->r30, ctx->r25);
    // 0x802C5BB8: b           L_802C5BD4
    // 0x802C5BBC: lw          $fp, 0x6184($fp)
    ctx->r30 = MEM_W(ctx->r30, 0X6184);
        goto L_802C5BD4;
    // 0x802C5BBC: lw          $fp, 0x6184($fp)
    ctx->r30 = MEM_W(ctx->r30, 0X6184);
L_802C5BC0:
    // 0x802C5BC0: lui         $a1, 0x802C
    ctx->r5 = S32(0X802C << 16);
    // 0x802C5BC4: addiu       $a1, $a1, 0x61B4
    ctx->r5 = ADD32(ctx->r5, 0X61B4);
    // 0x802C5BC8: addiu       $a0, $sp, 0x84
    ctx->r4 = ADD32(ctx->r29, 0X84);
    // 0x802C5BCC: jal         0x800CA210
    // 0x802C5BD0: lw          $a2, 0x0($s3)
    ctx->r6 = MEM_W(ctx->r19, 0X0);
    func_800CA210(rdram, ctx);
        goto after_10;
    // 0x802C5BD0: lw          $a2, 0x0($s3)
    ctx->r6 = MEM_W(ctx->r19, 0X0);
    after_10:
L_802C5BD4:
    // 0x802C5BD4: bne         $s0, $zero, L_802C5C00
    if (ctx->r16 != 0) {
        // 0x802C5BD8: or          $a0, $s2, $zero
        ctx->r4 = ctx->r18 | 0;
            goto L_802C5C00;
    }
    // 0x802C5BD8: or          $a0, $s2, $zero
    ctx->r4 = ctx->r18 | 0;
    // 0x802C5BDC: or          $a0, $s2, $zero
    ctx->r4 = ctx->r18 | 0;
    // 0x802C5BE0: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C5BE4: or          $a2, $fp, $zero
    ctx->r6 = ctx->r30 | 0;
    // 0x802C5BE8: addiu       $a3, $zero, 0x124
    ctx->r7 = ADD32(0, 0X124);
    // 0x802C5BEC: sw          $s5, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r21;
    // 0x802C5BF0: jal         0x801E3EE0
    // 0x802C5BF4: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    func_801E3EE0(rdram, ctx);
        goto after_11;
    // 0x802C5BF4: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    after_11:
    // 0x802C5BF8: b           L_802C5C18
    // 0x802C5BFC: or          $s2, $v0, $zero
    ctx->r18 = ctx->r2 | 0;
        goto L_802C5C18;
    // 0x802C5BFC: or          $s2, $v0, $zero
    ctx->r18 = ctx->r2 | 0;
L_802C5C00:
    // 0x802C5C00: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C5C04: addiu       $a2, $sp, 0x84
    ctx->r6 = ADD32(ctx->r29, 0X84);
    // 0x802C5C08: addiu       $a3, $zero, 0x124
    ctx->r7 = ADD32(0, 0X124);
    // 0x802C5C0C: jal         0x801E9858
    // 0x802C5C10: sw          $s6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r22;
    func_801E9858(rdram, ctx);
        goto after_12;
    // 0x802C5C10: sw          $s6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r22;
    after_12:
    // 0x802C5C14: or          $s2, $v0, $zero
    ctx->r18 = ctx->r2 | 0;
L_802C5C18:
    // 0x802C5C18: addiu       $s1, $s1, 0x1
    ctx->r17 = ADD32(ctx->r17, 0X1);
    // 0x802C5C1C: addiu       $v0, $zero, 0x3
    ctx->r2 = ADD32(0, 0X3);
    // 0x802C5C20: addiu       $s5, $s5, 0x15
    ctx->r21 = ADD32(ctx->r21, 0X15);
    // 0x802C5C24: addiu       $s6, $s6, 0x15
    ctx->r22 = ADD32(ctx->r22, 0X15);
    // 0x802C5C28: addiu       $s4, $s4, 0x8
    ctx->r20 = ADD32(ctx->r20, 0X8);
    // 0x802C5C2C: bne         $s1, $v0, L_802C5A14
    if (ctx->r17 != ctx->r2) {
        // 0x802C5C30: addiu       $s3, $s3, 0x4
        ctx->r19 = ADD32(ctx->r19, 0X4);
            goto L_802C5A14;
    }
    // 0x802C5C30: addiu       $s3, $s3, 0x4
    ctx->r19 = ADD32(ctx->r19, 0X4);
    // 0x802C5C34: lw          $t0, 0x0($s7)
    ctx->r8 = MEM_W(ctx->r23, 0X0);
    // 0x802C5C38: sw          $fp, 0x9C($sp)
    MEM_W(0X9C, ctx->r29) = ctx->r30;
    // 0x802C5C3C: or          $a0, $s2, $zero
    ctx->r4 = ctx->r18 | 0;
    // 0x802C5C40: bne         $v0, $t0, L_802C5C50
    if (ctx->r2 != ctx->r8) {
        // 0x802C5C44: addiu       $a2, $zero, 0xFF
        ctx->r6 = ADD32(0, 0XFF);
            goto L_802C5C50;
    }
    // 0x802C5C44: addiu       $a2, $zero, 0xFF
    ctx->r6 = ADD32(0, 0XFF);
    // 0x802C5C48: b           L_802C5C54
    // 0x802C5C4C: addiu       $a1, $zero, 0x6
    ctx->r5 = ADD32(0, 0X6);
        goto L_802C5C54;
    // 0x802C5C4C: addiu       $a1, $zero, 0x6
    ctx->r5 = ADD32(0, 0X6);
L_802C5C50:
    // 0x802C5C50: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
L_802C5C54:
    // 0x802C5C54: addiu       $t1, $zero, 0xFF
    ctx->r9 = ADD32(0, 0XFF);
    // 0x802C5C58: addiu       $t2, $zero, 0xFF
    ctx->r10 = ADD32(0, 0XFF);
    // 0x802C5C5C: addiu       $t4, $zero, 0xFF
    ctx->r12 = ADD32(0, 0XFF);
    // 0x802C5C60: addiu       $t3, $zero, 0xFF
    ctx->r11 = ADD32(0, 0XFF);
    // 0x802C5C64: addiu       $t5, $zero, 0xFF
    ctx->r13 = ADD32(0, 0XFF);
    // 0x802C5C68: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C5C6C: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C5C70: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C5C74: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C5C78: addiu       $t0, $zero, 0xFF
    ctx->r8 = ADD32(0, 0XFF);
    // 0x802C5C7C: sw          $t0, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r8;
    // 0x802C5C80: sw          $t9, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r25;
    // 0x802C5C84: sw          $t8, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r24;
    // 0x802C5C88: sw          $t7, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r15;
    // 0x802C5C8C: sw          $t6, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r14;
    // 0x802C5C90: sw          $t5, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r13;
    // 0x802C5C94: sw          $t3, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r11;
    // 0x802C5C98: sw          $t4, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r12;
    // 0x802C5C9C: sw          $t2, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r10;
    // 0x802C5CA0: sw          $t1, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r9;
    // 0x802C5CA4: jal         0x801E946C
    // 0x802C5CA8: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    func_801E946C(rdram, ctx);
        goto after_13;
    // 0x802C5CA8: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    after_13:
    // 0x802C5CAC: addiu       $t1, $zero, 0xA6
    ctx->r9 = ADD32(0, 0XA6);
    // 0x802C5CB0: sw          $t1, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r9;
    // 0x802C5CB4: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C5CB8: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C5CBC: addiu       $a2, $zero, 0x3F
    ctx->r6 = ADD32(0, 0X3F);
    // 0x802C5CC0: addiu       $a3, $zero, 0xC4
    ctx->r7 = ADD32(0, 0XC4);
    // 0x802C5CC4: jal         0x801E3EE0
    // 0x802C5CC8: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    func_801E3EE0(rdram, ctx);
        goto after_14;
    // 0x802C5CC8: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    after_14:
    // 0x802C5CCC: lui         $t2, 0x800E
    ctx->r10 = S32(0X800E << 16);
    // 0x802C5CD0: lw          $t2, -0x54DC($t2)
    ctx->r10 = MEM_W(ctx->r10, -0X54DC);
    // 0x802C5CD4: addiu       $at, $zero, 0x48
    ctx->r1 = ADD32(0, 0X48);
    // 0x802C5CD8: or          $s2, $v0, $zero
    ctx->r18 = ctx->r2 | 0;
    // 0x802C5CDC: bne         $t2, $at, L_802C5CF4
    if (ctx->r10 != ctx->r1) {
        // 0x802C5CE0: lui         $t4, 0x8023
        ctx->r12 = S32(0X8023 << 16);
            goto L_802C5CF4;
    }
    // 0x802C5CE0: lui         $t4, 0x8023
    ctx->r12 = S32(0X8023 << 16);
    // 0x802C5CE4: jal         0x802C5D48
    // 0x802C5CE8: nop

    func_i11_802C5D48(rdram, ctx);
        goto after_15;
    // 0x802C5CE8: nop

    after_15:
    // 0x802C5CEC: b           L_802C5D18
    // 0x802C5CF0: or          $v0, $s2, $zero
    ctx->r2 = ctx->r18 | 0;
        goto L_802C5D18;
    // 0x802C5CF0: or          $v0, $s2, $zero
    ctx->r2 = ctx->r18 | 0;
L_802C5CF4:
    // 0x802C5CF4: lh          $t4, -0x75EA($t4)
    ctx->r12 = MEM_H(ctx->r12, -0X75EA);
    // 0x802C5CF8: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x802C5CFC: bnel        $t4, $at, L_802C5D18
    if (ctx->r12 != ctx->r1) {
        // 0x802C5D00: or          $v0, $s2, $zero
        ctx->r2 = ctx->r18 | 0;
            goto L_802C5D18;
    }
    goto skip_0;
    // 0x802C5D00: or          $v0, $s2, $zero
    ctx->r2 = ctx->r18 | 0;
    skip_0:
    // 0x802C5D04: jal         0x801EC304
    // 0x802C5D08: nop

    func_801EC304(rdram, ctx);
        goto after_16;
    // 0x802C5D08: nop

    after_16:
    // 0x802C5D0C: jal         0x8007C494
    // 0x802C5D10: nop

    func_8007C494(rdram, ctx);
        goto after_17;
    // 0x802C5D10: nop

    after_17:
    // 0x802C5D14: or          $v0, $s2, $zero
    ctx->r2 = ctx->r18 | 0;
L_802C5D18:
    // 0x802C5D18: lw          $ra, 0x64($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X64);
L_802C5D1C:
    // 0x802C5D1C: lw          $s0, 0x40($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X40);
    // 0x802C5D20: lw          $s1, 0x44($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X44);
    // 0x802C5D24: lw          $s2, 0x48($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X48);
    // 0x802C5D28: lw          $s3, 0x4C($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X4C);
    // 0x802C5D2C: lw          $s4, 0x50($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X50);
    // 0x802C5D30: lw          $s5, 0x54($sp)
    ctx->r21 = MEM_W(ctx->r29, 0X54);
    // 0x802C5D34: lw          $s6, 0x58($sp)
    ctx->r22 = MEM_W(ctx->r29, 0X58);
    // 0x802C5D38: lw          $s7, 0x5C($sp)
    ctx->r23 = MEM_W(ctx->r29, 0X5C);
    // 0x802C5D3C: lw          $fp, 0x60($sp)
    ctx->r30 = MEM_W(ctx->r29, 0X60);
    // 0x802C5D40: jr          $ra
    // 0x802C5D44: addiu       $sp, $sp, 0xA8
    ctx->r29 = ADD32(ctx->r29, 0XA8);
    return;
    // 0x802C5D44: addiu       $sp, $sp, 0xA8
    ctx->r29 = ADD32(ctx->r29, 0XA8);
;}
RECOMP_FUNC void func_i11_802C5D48(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C5D48: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x802C5D4C: addiu       $v1, $v1, -0x19A8
    ctx->r3 = ADD32(ctx->r3, -0X19A8);
    // 0x802C5D50: lhu         $v0, 0x3A($v1)
    ctx->r2 = MEM_HU(ctx->r3, 0X3A);
    // 0x802C5D54: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x802C5D58: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x802C5D5C: andi        $t6, $v0, 0xB000
    ctx->r14 = ctx->r2 & 0XB000;
    // 0x802C5D60: beq         $t6, $zero, L_802C5DD8
    if (ctx->r14 == 0) {
        // 0x802C5D64: andi        $t1, $v0, 0x4000
        ctx->r9 = ctx->r2 & 0X4000;
            goto L_802C5DD8;
    }
    // 0x802C5D64: andi        $t1, $v0, 0x4000
    ctx->r9 = ctx->r2 & 0X4000;
    // 0x802C5D68: lui         $v0, 0x802C
    ctx->r2 = S32(0X802C << 16);
    // 0x802C5D6C: addiu       $v0, $v0, 0x6150
    ctx->r2 = ADD32(ctx->r2, 0X6150);
    // 0x802C5D70: lw          $v1, 0x0($v0)
    ctx->r3 = MEM_W(ctx->r2, 0X0);
    // 0x802C5D74: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x802C5D78: addiu       $t7, $zero, 0x1
    ctx->r15 = ADD32(0, 0X1);
    // 0x802C5D7C: bne         $v1, $at, L_802C5DA0
    if (ctx->r3 != ctx->r1) {
        // 0x802C5D80: sll         $t8, $v1, 2
        ctx->r24 = S32(ctx->r3 << 2);
            goto L_802C5DA0;
    }
    // 0x802C5D80: sll         $t8, $v1, 2
    ctx->r24 = S32(ctx->r3 << 2);
    // 0x802C5D84: lui         $a0, 0x800E
    ctx->r4 = S32(0X800E << 16);
    // 0x802C5D88: addu        $a0, $a0, $t8
    ctx->r4 = ADD32(ctx->r4, ctx->r24);
    // 0x802C5D8C: sw          $t7, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r15;
    // 0x802C5D90: jal         0x800C3050
    // 0x802C5D94: lw          $a0, -0x5614($a0)
    ctx->r4 = MEM_W(ctx->r4, -0X5614);
    func_800C3050(rdram, ctx);
        goto after_0;
    // 0x802C5D94: lw          $a0, -0x5614($a0)
    ctx->r4 = MEM_W(ctx->r4, -0X5614);
    after_0:
    // 0x802C5D98: b           L_802C5DBC
    // 0x802C5D9C: lw          $t0, 0x18($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X18);
        goto L_802C5DBC;
    // 0x802C5D9C: lw          $t0, 0x18($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X18);
L_802C5DA0:
    // 0x802C5DA0: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x802C5DA4: bne         $v1, $at, L_802C5DB8
    if (ctx->r3 != ctx->r1) {
        // 0x802C5DA8: addiu       $t9, $zero, 0x1
        ctx->r25 = ADD32(0, 0X1);
            goto L_802C5DB8;
    }
    // 0x802C5DA8: addiu       $t9, $zero, 0x1
    ctx->r25 = ADD32(0, 0X1);
    // 0x802C5DAC: sw          $t9, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r25;
    // 0x802C5DB0: jal         0x802C6098
    // 0x802C5DB4: addiu       $a0, $zero, 0x3C
    ctx->r4 = ADD32(0, 0X3C);
    func_i11_802C6098(rdram, ctx);
        goto after_1;
    // 0x802C5DB4: addiu       $a0, $zero, 0x3C
    ctx->r4 = ADD32(0, 0X3C);
    after_1:
L_802C5DB8:
    // 0x802C5DB8: lw          $t0, 0x18($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X18);
L_802C5DBC:
    // 0x802C5DBC: addiu       $a0, $zero, 0x11
    ctx->r4 = ADD32(0, 0X11);
    // 0x802C5DC0: beql        $t0, $zero, L_802C5F70
    if (ctx->r8 == 0) {
        // 0x802C5DC4: lw          $ra, 0x14($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X14);
            goto L_802C5F70;
    }
    goto skip_0;
    // 0x802C5DC4: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    skip_0:
    // 0x802C5DC8: jal         0x800C37F4
    // 0x802C5DCC: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_2;
    // 0x802C5DCC: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_2:
    // 0x802C5DD0: b           L_802C5F70
    // 0x802C5DD4: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_802C5F70;
    // 0x802C5DD4: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C5DD8:
    // 0x802C5DD8: beql        $t1, $zero, L_802C5E00
    if (ctx->r9 == 0) {
        // 0x802C5DDC: lhu         $v0, 0x2($v1)
        ctx->r2 = MEM_HU(ctx->r3, 0X2);
            goto L_802C5E00;
    }
    goto skip_1;
    // 0x802C5DDC: lhu         $v0, 0x2($v1)
    ctx->r2 = MEM_HU(ctx->r3, 0X2);
    skip_1:
    // 0x802C5DE0: jal         0x802C6098
    // 0x802C5DE4: addiu       $a0, $zero, 0x3C
    ctx->r4 = ADD32(0, 0X3C);
    func_i11_802C6098(rdram, ctx);
        goto after_3;
    // 0x802C5DE4: addiu       $a0, $zero, 0x3C
    ctx->r4 = ADD32(0, 0X3C);
    after_3:
    // 0x802C5DE8: addiu       $a0, $zero, 0x16
    ctx->r4 = ADD32(0, 0X16);
    // 0x802C5DEC: jal         0x800C37F4
    // 0x802C5DF0: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_4;
    // 0x802C5DF0: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_4:
    // 0x802C5DF4: b           L_802C5F70
    // 0x802C5DF8: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_802C5F70;
    // 0x802C5DF8: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x802C5DFC: lhu         $v0, 0x2($v1)
    ctx->r2 = MEM_HU(ctx->r3, 0X2);
L_802C5E00:
    // 0x802C5E00: addiu       $a0, $zero, 0x10
    ctx->r4 = ADD32(0, 0X10);
    // 0x802C5E04: andi        $t2, $v0, 0x800
    ctx->r10 = ctx->r2 & 0X800;
    // 0x802C5E08: beq         $t2, $zero, L_802C5E40
    if (ctx->r10 == 0) {
        // 0x802C5E0C: andi        $t7, $v0, 0x400
        ctx->r15 = ctx->r2 & 0X400;
            goto L_802C5E40;
    }
    // 0x802C5E0C: andi        $t7, $v0, 0x400
    ctx->r15 = ctx->r2 & 0X400;
    // 0x802C5E10: lui         $v0, 0x802C
    ctx->r2 = S32(0X802C << 16);
    // 0x802C5E14: addiu       $v0, $v0, 0x6150
    ctx->r2 = ADD32(ctx->r2, 0X6150);
    // 0x802C5E18: lw          $t3, 0x0($v0)
    ctx->r11 = MEM_W(ctx->r2, 0X0);
    // 0x802C5E1C: addiu       $t6, $zero, 0x3
    ctx->r14 = ADD32(0, 0X3);
    // 0x802C5E20: addiu       $t4, $t3, -0x1
    ctx->r12 = ADD32(ctx->r11, -0X1);
    // 0x802C5E24: bgez        $t4, L_802C5E30
    if (SIGNED(ctx->r12) >= 0) {
        // 0x802C5E28: sw          $t4, 0x0($v0)
        MEM_W(0X0, ctx->r2) = ctx->r12;
            goto L_802C5E30;
    }
    // 0x802C5E28: sw          $t4, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r12;
    // 0x802C5E2C: sw          $t6, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r14;
L_802C5E30:
    // 0x802C5E30: jal         0x800C37F4
    // 0x802C5E34: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_5;
    // 0x802C5E34: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_5:
    // 0x802C5E38: b           L_802C5F70
    // 0x802C5E3C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_802C5F70;
    // 0x802C5E3C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C5E40:
    // 0x802C5E40: beq         $t7, $zero, L_802C5E7C
    if (ctx->r15 == 0) {
        // 0x802C5E44: andi        $t1, $v0, 0x200
        ctx->r9 = ctx->r2 & 0X200;
            goto L_802C5E7C;
    }
    // 0x802C5E44: andi        $t1, $v0, 0x200
    ctx->r9 = ctx->r2 & 0X200;
    // 0x802C5E48: lui         $v0, 0x802C
    ctx->r2 = S32(0X802C << 16);
    // 0x802C5E4C: addiu       $v0, $v0, 0x6150
    ctx->r2 = ADD32(ctx->r2, 0X6150);
    // 0x802C5E50: lw          $t8, 0x0($v0)
    ctx->r24 = MEM_W(ctx->r2, 0X0);
    // 0x802C5E54: addiu       $a0, $zero, 0x10
    ctx->r4 = ADD32(0, 0X10);
    // 0x802C5E58: addiu       $t9, $t8, 0x1
    ctx->r25 = ADD32(ctx->r24, 0X1);
    // 0x802C5E5C: slti        $at, $t9, 0x4
    ctx->r1 = SIGNED(ctx->r25) < 0X4 ? 1 : 0;
    // 0x802C5E60: bne         $at, $zero, L_802C5E6C
    if (ctx->r1 != 0) {
        // 0x802C5E64: sw          $t9, 0x0($v0)
        MEM_W(0X0, ctx->r2) = ctx->r25;
            goto L_802C5E6C;
    }
    // 0x802C5E64: sw          $t9, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r25;
    // 0x802C5E68: sw          $zero, 0x0($v0)
    MEM_W(0X0, ctx->r2) = 0;
L_802C5E6C:
    // 0x802C5E6C: jal         0x800C37F4
    // 0x802C5E70: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_6;
    // 0x802C5E70: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_6:
    // 0x802C5E74: b           L_802C5F70
    // 0x802C5E78: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_802C5F70;
    // 0x802C5E78: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C5E7C:
    // 0x802C5E7C: beql        $t1, $zero, L_802C5EFC
    if (ctx->r9 == 0) {
        // 0x802C5E80: andi        $t1, $v0, 0x100
        ctx->r9 = ctx->r2 & 0X100;
            goto L_802C5EFC;
    }
    goto skip_2;
    // 0x802C5E80: andi        $t1, $v0, 0x100
    ctx->r9 = ctx->r2 & 0X100;
    skip_2:
    // 0x802C5E84: lui         $v0, 0x802C
    ctx->r2 = S32(0X802C << 16);
    // 0x802C5E88: addiu       $v0, $v0, 0x6150
    ctx->r2 = ADD32(ctx->r2, 0X6150);
    // 0x802C5E8C: lw          $v1, 0x0($v0)
    ctx->r3 = MEM_W(ctx->r2, 0X0);
    // 0x802C5E90: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x802C5E94: lui         $t3, 0x802C
    ctx->r11 = S32(0X802C << 16);
    // 0x802C5E98: beq         $v1, $at, L_802C5EE4
    if (ctx->r3 == ctx->r1) {
        // 0x802C5E9C: sll         $t2, $v1, 3
        ctx->r10 = S32(ctx->r3 << 3);
            goto L_802C5EE4;
    }
    // 0x802C5E9C: sll         $t2, $v1, 3
    ctx->r10 = S32(ctx->r3 << 3);
    // 0x802C5EA0: lui         $t5, 0x800E
    ctx->r13 = S32(0X800E << 16);
    // 0x802C5EA4: addiu       $t5, $t5, -0x5614
    ctx->r13 = ADD32(ctx->r13, -0X5614);
    // 0x802C5EA8: sll         $t4, $v1, 2
    ctx->r12 = S32(ctx->r3 << 2);
    // 0x802C5EAC: addu        $v0, $t4, $t5
    ctx->r2 = ADD32(ctx->r12, ctx->r13);
    // 0x802C5EB0: lw          $t6, 0x0($v0)
    ctx->r14 = MEM_W(ctx->r2, 0X0);
    // 0x802C5EB4: addiu       $t3, $t3, 0x618C
    ctx->r11 = ADD32(ctx->r11, 0X618C);
    // 0x802C5EB8: addu        $a0, $t2, $t3
    ctx->r4 = ADD32(ctx->r10, ctx->r11);
    // 0x802C5EBC: addiu       $t7, $t6, -0x1
    ctx->r15 = ADD32(ctx->r14, -0X1);
    // 0x802C5EC0: sw          $t7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r15;
    // 0x802C5EC4: lw          $t9, 0x0($a0)
    ctx->r25 = MEM_W(ctx->r4, 0X0);
    // 0x802C5EC8: slt         $at, $t7, $t9
    ctx->r1 = SIGNED(ctx->r15) < SIGNED(ctx->r25) ? 1 : 0;
    // 0x802C5ECC: beq         $at, $zero, L_802C5EDC
    if (ctx->r1 == 0) {
        // 0x802C5ED0: nop
    
            goto L_802C5EDC;
    }
    // 0x802C5ED0: nop

    // 0x802C5ED4: lw          $t0, 0x4($a0)
    ctx->r8 = MEM_W(ctx->r4, 0X4);
    // 0x802C5ED8: sw          $t0, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r8;
L_802C5EDC:
    // 0x802C5EDC: jal         0x802C5F7C
    // 0x802C5EE0: nop

    func_i11_802C5F7C(rdram, ctx);
        goto after_7;
    // 0x802C5EE0: nop

    after_7:
L_802C5EE4:
    // 0x802C5EE4: addiu       $a0, $zero, 0x10
    ctx->r4 = ADD32(0, 0X10);
    // 0x802C5EE8: jal         0x800C37F4
    // 0x802C5EEC: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_8;
    // 0x802C5EEC: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_8:
    // 0x802C5EF0: b           L_802C5F70
    // 0x802C5EF4: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_802C5F70;
    // 0x802C5EF4: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x802C5EF8: andi        $t1, $v0, 0x100
    ctx->r9 = ctx->r2 & 0X100;
L_802C5EFC:
    // 0x802C5EFC: beq         $t1, $zero, L_802C5F6C
    if (ctx->r9 == 0) {
        // 0x802C5F00: lui         $v0, 0x802C
        ctx->r2 = S32(0X802C << 16);
            goto L_802C5F6C;
    }
    // 0x802C5F00: lui         $v0, 0x802C
    ctx->r2 = S32(0X802C << 16);
    // 0x802C5F04: addiu       $v0, $v0, 0x6150
    ctx->r2 = ADD32(ctx->r2, 0X6150);
    // 0x802C5F08: lw          $v1, 0x0($v0)
    ctx->r3 = MEM_W(ctx->r2, 0X0);
    // 0x802C5F0C: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x802C5F10: lui         $t3, 0x802C
    ctx->r11 = S32(0X802C << 16);
    // 0x802C5F14: beq         $v1, $at, L_802C5F60
    if (ctx->r3 == ctx->r1) {
        // 0x802C5F18: sll         $t2, $v1, 3
        ctx->r10 = S32(ctx->r3 << 3);
            goto L_802C5F60;
    }
    // 0x802C5F18: sll         $t2, $v1, 3
    ctx->r10 = S32(ctx->r3 << 3);
    // 0x802C5F1C: lui         $t5, 0x800E
    ctx->r13 = S32(0X800E << 16);
    // 0x802C5F20: addiu       $t5, $t5, -0x5614
    ctx->r13 = ADD32(ctx->r13, -0X5614);
    // 0x802C5F24: sll         $t4, $v1, 2
    ctx->r12 = S32(ctx->r3 << 2);
    // 0x802C5F28: addu        $v0, $t4, $t5
    ctx->r2 = ADD32(ctx->r12, ctx->r13);
    // 0x802C5F2C: lw          $t6, 0x0($v0)
    ctx->r14 = MEM_W(ctx->r2, 0X0);
    // 0x802C5F30: addiu       $t3, $t3, 0x618C
    ctx->r11 = ADD32(ctx->r11, 0X618C);
    // 0x802C5F34: addu        $a0, $t2, $t3
    ctx->r4 = ADD32(ctx->r10, ctx->r11);
    // 0x802C5F38: addiu       $t7, $t6, 0x1
    ctx->r15 = ADD32(ctx->r14, 0X1);
    // 0x802C5F3C: sw          $t7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r15;
    // 0x802C5F40: lw          $t8, 0x4($a0)
    ctx->r24 = MEM_W(ctx->r4, 0X4);
    // 0x802C5F44: slt         $at, $t8, $t7
    ctx->r1 = SIGNED(ctx->r24) < SIGNED(ctx->r15) ? 1 : 0;
    // 0x802C5F48: beq         $at, $zero, L_802C5F58
    if (ctx->r1 == 0) {
        // 0x802C5F4C: nop
    
            goto L_802C5F58;
    }
    // 0x802C5F4C: nop

    // 0x802C5F50: lw          $t0, 0x0($a0)
    ctx->r8 = MEM_W(ctx->r4, 0X0);
    // 0x802C5F54: sw          $t0, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r8;
L_802C5F58:
    // 0x802C5F58: jal         0x802C5F7C
    // 0x802C5F5C: nop

    func_i11_802C5F7C(rdram, ctx);
        goto after_9;
    // 0x802C5F5C: nop

    after_9:
L_802C5F60:
    // 0x802C5F60: addiu       $a0, $zero, 0x10
    ctx->r4 = ADD32(0, 0X10);
    // 0x802C5F64: jal         0x800C37F4
    // 0x802C5F68: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_10;
    // 0x802C5F68: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_10:
L_802C5F6C:
    // 0x802C5F6C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C5F70:
    // 0x802C5F70: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x802C5F74: jr          $ra
    // 0x802C5F78: nop

    return;
    // 0x802C5F78: nop

;}
RECOMP_FUNC void func_i11_802C5F7C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C5F7C: lui         $v0, 0x802C
    ctx->r2 = S32(0X802C << 16);
    // 0x802C5F80: lw          $v0, 0x6150($v0)
    ctx->r2 = MEM_W(ctx->r2, 0X6150);
    // 0x802C5F84: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x802C5F88: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x802C5F8C: bne         $v0, $zero, L_802C6030
    if (ctx->r2 != 0) {
        // 0x802C5F90: addiu       $a0, $zero, 0x1
        ctx->r4 = ADD32(0, 0X1);
            goto L_802C6030;
    }
    // 0x802C5F90: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    // 0x802C5F94: sll         $t6, $v0, 2
    ctx->r14 = S32(ctx->r2 << 2);
    // 0x802C5F98: lui         $v1, 0x800E
    ctx->r3 = S32(0X800E << 16);
    // 0x802C5F9C: addu        $v1, $v1, $t6
    ctx->r3 = ADD32(ctx->r3, ctx->r14);
    // 0x802C5FA0: lw          $v1, -0x5614($v1)
    ctx->r3 = MEM_W(ctx->r3, -0X5614);
    // 0x802C5FA4: bnel        $v1, $zero, L_802C5FD0
    if (ctx->r3 != 0) {
        // 0x802C5FA8: addiu       $a0, $zero, 0x1
        ctx->r4 = ADD32(0, 0X1);
            goto L_802C5FD0;
    }
    goto skip_0;
    // 0x802C5FA8: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    skip_0:
    // 0x802C5FAC: jal         0x800C2FDC
    // 0x802C5FB0: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    func_800C2FDC(rdram, ctx);
        goto after_0;
    // 0x802C5FB0: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    after_0:
    // 0x802C5FB4: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x802C5FB8: addiu       $v0, $v0, -0x4D80
    ctx->r2 = ADD32(ctx->r2, -0X4D80);
    // 0x802C5FBC: lb          $t7, 0x0($v0)
    ctx->r15 = MEM_B(ctx->r2, 0X0);
    // 0x802C5FC0: andi        $t8, $t7, 0x3F
    ctx->r24 = ctx->r15 & 0X3F;
    // 0x802C5FC4: b           L_802C6088
    // 0x802C5FC8: sb          $t8, 0x0($v0)
    MEM_B(0X0, ctx->r2) = ctx->r24;
        goto L_802C6088;
    // 0x802C5FC8: sb          $t8, 0x0($v0)
    MEM_B(0X0, ctx->r2) = ctx->r24;
    // 0x802C5FCC: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
L_802C5FD0:
    // 0x802C5FD0: bne         $a0, $v1, L_802C6004
    if (ctx->r4 != ctx->r3) {
        // 0x802C5FD4: nop
    
            goto L_802C6004;
    }
    // 0x802C5FD4: nop

    // 0x802C5FD8: jal         0x800C2FDC
    // 0x802C5FDC: addiu       $a0, $zero, 0x3
    ctx->r4 = ADD32(0, 0X3);
    func_800C2FDC(rdram, ctx);
        goto after_1;
    // 0x802C5FDC: addiu       $a0, $zero, 0x3
    ctx->r4 = ADD32(0, 0X3);
    after_1:
    // 0x802C5FE0: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x802C5FE4: addiu       $v0, $v0, -0x4D80
    ctx->r2 = ADD32(ctx->r2, -0X4D80);
    // 0x802C5FE8: lb          $t9, 0x0($v0)
    ctx->r25 = MEM_B(ctx->r2, 0X0);
    // 0x802C5FEC: andi        $t0, $t9, 0x3F
    ctx->r8 = ctx->r25 & 0X3F;
    // 0x802C5FF0: sb          $t0, 0x0($v0)
    MEM_B(0X0, ctx->r2) = ctx->r8;
    // 0x802C5FF4: lb          $t1, 0x0($v0)
    ctx->r9 = MEM_B(ctx->r2, 0X0);
    // 0x802C5FF8: ori         $t2, $t1, 0x40
    ctx->r10 = ctx->r9 | 0X40;
    // 0x802C5FFC: b           L_802C6088
    // 0x802C6000: sb          $t2, 0x0($v0)
    MEM_B(0X0, ctx->r2) = ctx->r10;
        goto L_802C6088;
    // 0x802C6000: sb          $t2, 0x0($v0)
    MEM_B(0X0, ctx->r2) = ctx->r10;
L_802C6004:
    // 0x802C6004: jal         0x800C2FDC
    // 0x802C6008: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    func_800C2FDC(rdram, ctx);
        goto after_2;
    // 0x802C6008: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    after_2:
    // 0x802C600C: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x802C6010: addiu       $v0, $v0, -0x4D80
    ctx->r2 = ADD32(ctx->r2, -0X4D80);
    // 0x802C6014: lb          $t3, 0x0($v0)
    ctx->r11 = MEM_B(ctx->r2, 0X0);
    // 0x802C6018: andi        $t4, $t3, 0x3F
    ctx->r12 = ctx->r11 & 0X3F;
    // 0x802C601C: sb          $t4, 0x0($v0)
    MEM_B(0X0, ctx->r2) = ctx->r12;
    // 0x802C6020: lb          $t5, 0x0($v0)
    ctx->r13 = MEM_B(ctx->r2, 0X0);
    // 0x802C6024: ori         $t6, $t5, 0x80
    ctx->r14 = ctx->r13 | 0X80;
    // 0x802C6028: b           L_802C6088
    // 0x802C602C: sb          $t6, 0x0($v0)
    MEM_B(0X0, ctx->r2) = ctx->r14;
        goto L_802C6088;
    // 0x802C602C: sb          $t6, 0x0($v0)
    MEM_B(0X0, ctx->r2) = ctx->r14;
L_802C6030:
    // 0x802C6030: bne         $a0, $v0, L_802C6088
    if (ctx->r4 != ctx->r2) {
        // 0x802C6034: sll         $t7, $v0, 2
        ctx->r15 = S32(ctx->r2 << 2);
            goto L_802C6088;
    }
    // 0x802C6034: sll         $t7, $v0, 2
    ctx->r15 = S32(ctx->r2 << 2);
    // 0x802C6038: lui         $t8, 0x800E
    ctx->r24 = S32(0X800E << 16);
    // 0x802C603C: addu        $t8, $t8, $t7
    ctx->r24 = ADD32(ctx->r24, ctx->r15);
    // 0x802C6040: lw          $t8, -0x5614($t8)
    ctx->r24 = MEM_W(ctx->r24, -0X5614);
    // 0x802C6044: bne         $a0, $t8, L_802C606C
    if (ctx->r4 != ctx->r24) {
        // 0x802C6048: nop
    
            goto L_802C606C;
    }
    // 0x802C6048: nop

    // 0x802C604C: jal         0x800C3034
    // 0x802C6050: nop

    leoInitUnit_atten(rdram, ctx);
        goto after_3;
    // 0x802C6050: nop

    after_3:
    // 0x802C6054: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x802C6058: addiu       $v0, $v0, -0x4D80
    ctx->r2 = ADD32(ctx->r2, -0X4D80);
    // 0x802C605C: lb          $t9, 0x0($v0)
    ctx->r25 = MEM_B(ctx->r2, 0X0);
    // 0x802C6060: andi        $t0, $t9, 0xDF
    ctx->r8 = ctx->r25 & 0XDF;
    // 0x802C6064: b           L_802C6088
    // 0x802C6068: sb          $t0, 0x0($v0)
    MEM_B(0X0, ctx->r2) = ctx->r8;
        goto L_802C6088;
    // 0x802C6068: sb          $t0, 0x0($v0)
    MEM_B(0X0, ctx->r2) = ctx->r8;
L_802C606C:
    // 0x802C606C: jal         0x800C3044
    // 0x802C6070: nop

    myfree(rdram, ctx);
        goto after_4;
    // 0x802C6070: nop

    after_4:
    // 0x802C6074: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x802C6078: addiu       $v0, $v0, -0x4D80
    ctx->r2 = ADD32(ctx->r2, -0X4D80);
    // 0x802C607C: lb          $t1, 0x0($v0)
    ctx->r9 = MEM_B(ctx->r2, 0X0);
    // 0x802C6080: ori         $t2, $t1, 0x20
    ctx->r10 = ctx->r9 | 0X20;
    // 0x802C6084: sb          $t2, 0x0($v0)
    MEM_B(0X0, ctx->r2) = ctx->r10;
L_802C6088:
    // 0x802C6088: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x802C608C: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x802C6090: jr          $ra
    // 0x802C6094: nop

    return;
    // 0x802C6094: nop

;}
RECOMP_FUNC void func_i11_802C6098(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C6098: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x802C609C: addiu       $v0, $v0, -0x54DC
    ctx->r2 = ADD32(ctx->r2, -0X54DC);
    // 0x802C60A0: lw          $t6, 0x0($v0)
    ctx->r14 = MEM_W(ctx->r2, 0X0);
    // 0x802C60A4: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C60A8: addiu       $t7, $zero, 0x49
    ctx->r15 = ADD32(0, 0X49);
    // 0x802C60AC: sw          $t6, -0x19CC($at)
    MEM_W(-0X19CC, ctx->r1) = ctx->r14;
    // 0x802C60B0: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C60B4: sw          $a0, -0x19D0($at)
    MEM_W(-0X19D0, ctx->r1) = ctx->r4;
    // 0x802C60B8: sw          $t7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r15;
    // 0x802C60BC: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C60C0: addiu       $t8, $zero, 0x14
    ctx->r24 = ADD32(0, 0X14);
    // 0x802C60C4: sw          $t8, -0x19C8($at)
    MEM_W(-0X19C8, ctx->r1) = ctx->r24;
    // 0x802C60C8: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C60CC: addiu       $t9, $zero, 0x1
    ctx->r25 = ADD32(0, 0X1);
    // 0x802C60D0: sw          $t9, -0x19C4($at)
    MEM_W(-0X19C4, ctx->r1) = ctx->r25;
    // 0x802C60D4: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C60D8: sw          $zero, -0x19C0($at)
    MEM_W(-0X19C0, ctx->r1) = 0;
    // 0x802C60DC: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C60E0: sw          $zero, -0x19BC($at)
    MEM_W(-0X19BC, ctx->r1) = 0;
    // 0x802C60E4: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x802C60E8: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x802C60EC: sw          $zero, -0x54E4($at)
    MEM_W(-0X54E4, ctx->r1) = 0;
    // 0x802C60F0: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x802C60F4: lui         $at, 0x800D
    ctx->r1 = S32(0X800D << 16);
    // 0x802C60F8: addiu       $t0, $zero, 0x2
    ctx->r8 = ADD32(0, 0X2);
    // 0x802C60FC: sw          $t0, 0x461C($at)
    MEM_W(0X461C, ctx->r1) = ctx->r8;
    // 0x802C6100: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    // 0x802C6104: addiu       $a1, $zero, 0x4
    ctx->r5 = ADD32(0, 0X4);
    // 0x802C6108: jal         0x801E6FB0
    // 0x802C610C: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    FadeTransition_SetProps(rdram, ctx);
        goto after_0;
    // 0x802C610C: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    after_0:
    // 0x802C6110: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    // 0x802C6114: jal         0x801E6A4C
    // 0x802C6118: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_801E6A4C(rdram, ctx);
        goto after_1;
    // 0x802C6118: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_1:
    // 0x802C611C: lui         $t1, 0x801D
    ctx->r9 = S32(0X801D << 16);
    // 0x802C6120: lw          $t1, -0x19D0($t1)
    ctx->r9 = MEM_W(ctx->r9, -0X19D0);
    // 0x802C6124: addiu       $at, $zero, 0x3C
    ctx->r1 = ADD32(0, 0X3C);
    // 0x802C6128: bnel        $t1, $at, L_802C613C
    if (ctx->r9 != ctx->r1) {
        // 0x802C612C: lw          $ra, 0x14($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X14);
            goto L_802C613C;
    }
    goto skip_0;
    // 0x802C612C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    skip_0:
    // 0x802C6130: jal         0x800C1F60
    // 0x802C6134: addiu       $a0, $zero, 0x9
    ctx->r4 = ADD32(0, 0X9);
    func_800C1F60(rdram, ctx);
        goto after_2;
    // 0x802C6134: addiu       $a0, $zero, 0x9
    ctx->r4 = ADD32(0, 0X9);
    after_2:
    // 0x802C6138: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C613C:
    // 0x802C613C: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x802C6140: jr          $ra
    // 0x802C6144: nop

    return;
    // 0x802C6144: nop

    // 0x802C6148: nop

    // 0x802C614C: nop

;}
RECOMP_FUNC void func_i12_802C5800(uint8_t* rdram, recomp_context* ctx) {
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
    // 0x802C5814: beq         $t6, $zero, L_802C5840
    if (ctx->r14 == 0) {
        // 0x802C5818: lui         $t7, 0x800E
        ctx->r15 = S32(0X800E << 16);
            goto L_802C5840;
    }
    // 0x802C5818: lui         $t7, 0x800E
    ctx->r15 = S32(0X800E << 16);
    // 0x802C581C: sw          $zero, 0x0($v0)
    MEM_W(0X0, ctx->r2) = 0;
    // 0x802C5820: lw          $t7, -0x54DC($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X54DC);
    // 0x802C5824: addiu       $at, $zero, 0x46
    ctx->r1 = ADD32(0, 0X46);
    // 0x802C5828: bne         $t7, $at, L_802C5840
    if (ctx->r15 != ctx->r1) {
        // 0x802C582C: nop
    
            goto L_802C5840;
    }
    // 0x802C582C: nop

    // 0x802C5830: jal         0x80093C44
    // 0x802C5834: nop

    func_80093C44(rdram, ctx);
        goto after_0;
    // 0x802C5834: nop

    after_0:
    // 0x802C5838: b           L_802C5894
    // 0x802C583C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_802C5894;
    // 0x802C583C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C5840:
    // 0x802C5840: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x802C5844: jal         0x802C58A0
    // 0x802C5848: sw          $zero, -0x54D4($at)
    MEM_W(-0X54D4, ctx->r1) = 0;
    func_i12_802C58A0(rdram, ctx);
        goto after_1;
    // 0x802C5848: sw          $zero, -0x54D4($at)
    MEM_W(-0X54D4, ctx->r1) = 0;
    after_1:
    // 0x802C584C: lui         $t8, 0x800E
    ctx->r24 = S32(0X800E << 16);
    // 0x802C5850: lw          $t8, -0x54DC($t8)
    ctx->r24 = MEM_W(ctx->r24, -0X54DC);
    // 0x802C5854: addiu       $at, $zero, 0x46
    ctx->r1 = ADD32(0, 0X46);
    // 0x802C5858: sw          $v0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r2;
    // 0x802C585C: bne         $t8, $at, L_802C5874
    if (ctx->r24 != ctx->r1) {
        // 0x802C5860: lui         $t9, 0x8023
        ctx->r25 = S32(0X8023 << 16);
            goto L_802C5874;
    }
    // 0x802C5860: lui         $t9, 0x8023
    ctx->r25 = S32(0X8023 << 16);
    // 0x802C5864: jal         0x802C5F6C
    // 0x802C5868: nop

    func_i12_802C5F6C(rdram, ctx);
        goto after_2;
    // 0x802C5868: nop

    after_2:
    // 0x802C586C: b           L_802C5890
    // 0x802C5870: lw          $v0, 0x18($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X18);
        goto L_802C5890;
    // 0x802C5870: lw          $v0, 0x18($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X18);
L_802C5874:
    // 0x802C5874: lh          $t9, -0x75EA($t9)
    ctx->r25 = MEM_H(ctx->r25, -0X75EA);
    // 0x802C5878: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x802C587C: bnel        $t9, $at, L_802C5890
    if (ctx->r25 != ctx->r1) {
        // 0x802C5880: lw          $v0, 0x18($sp)
        ctx->r2 = MEM_W(ctx->r29, 0X18);
            goto L_802C5890;
    }
    goto skip_0;
    // 0x802C5880: lw          $v0, 0x18($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X18);
    skip_0:
    // 0x802C5884: jal         0x801EC304
    // 0x802C5888: nop

    func_801EC304(rdram, ctx);
        goto after_3;
    // 0x802C5888: nop

    after_3:
    // 0x802C588C: lw          $v0, 0x18($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X18);
L_802C5890:
    // 0x802C5890: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C5894:
    // 0x802C5894: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x802C5898: jr          $ra
    // 0x802C589C: nop

    return;
    // 0x802C589C: nop

;}
RECOMP_FUNC void func_i12_802C58A0(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C58A0: addiu       $sp, $sp, -0x68
    ctx->r29 = ADD32(ctx->r29, -0X68);
    // 0x802C58A4: sw          $s4, 0x50($sp)
    MEM_W(0X50, ctx->r29) = ctx->r20;
    // 0x802C58A8: sw          $s0, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r16;
    // 0x802C58AC: sw          $ra, 0x64($sp)
    MEM_W(0X64, ctx->r29) = ctx->r31;
    // 0x802C58B0: sw          $fp, 0x60($sp)
    MEM_W(0X60, ctx->r29) = ctx->r30;
    // 0x802C58B4: sw          $s7, 0x5C($sp)
    MEM_W(0X5C, ctx->r29) = ctx->r23;
    // 0x802C58B8: sw          $s6, 0x58($sp)
    MEM_W(0X58, ctx->r29) = ctx->r22;
    // 0x802C58BC: sw          $s5, 0x54($sp)
    MEM_W(0X54, ctx->r29) = ctx->r21;
    // 0x802C58C0: sw          $s3, 0x4C($sp)
    MEM_W(0X4C, ctx->r29) = ctx->r19;
    // 0x802C58C4: sw          $s2, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r18;
    // 0x802C58C8: sw          $s1, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r17;
    // 0x802C58CC: addiu       $s4, $a0, 0x8
    ctx->r20 = ADD32(ctx->r4, 0X8);
    // 0x802C58D0: lui         $t6, 0x103
    ctx->r14 = S32(0X103 << 16);
    // 0x802C58D4: lui         $t7, 0x700
    ctx->r15 = S32(0X700 << 16);
    // 0x802C58D8: addiu       $t7, $t7, 0x0
    ctx->r15 = ADD32(ctx->r15, 0X0);
    // 0x802C58DC: ori         $t6, $t6, 0x40
    ctx->r14 = ctx->r14 | 0X40;
    // 0x802C58E0: or          $v1, $s4, $zero
    ctx->r3 = ctx->r20 | 0;
    // 0x802C58E4: sw          $t6, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r14;
    // 0x802C58E8: sw          $t7, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r15;
    // 0x802C58EC: addiu       $s4, $s4, 0x8
    ctx->r20 = ADD32(ctx->r20, 0X8);
    // 0x802C58F0: lui         $t8, 0x102
    ctx->r24 = S32(0X102 << 16);
    // 0x802C58F4: lui         $t9, 0x200
    ctx->r25 = S32(0X200 << 16);
    // 0x802C58F8: addiu       $t9, $t9, 0xA40
    ctx->r25 = ADD32(ctx->r25, 0XA40);
    // 0x802C58FC: ori         $t8, $t8, 0x40
    ctx->r24 = ctx->r24 | 0X40;
    // 0x802C5900: or          $a1, $s4, $zero
    ctx->r5 = ctx->r20 | 0;
    // 0x802C5904: sw          $t8, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r24;
    // 0x802C5908: sw          $t9, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r25;
    // 0x802C590C: addiu       $s4, $s4, 0x8
    ctx->r20 = ADD32(ctx->r20, 0X8);
    // 0x802C5910: lui         $t0, 0x107
    ctx->r8 = S32(0X107 << 16);
    // 0x802C5914: lui         $a3, 0x600
    ctx->r7 = S32(0X600 << 16);
    // 0x802C5918: addiu       $t0, $t0, -0xAB0
    ctx->r8 = ADD32(ctx->r8, -0XAB0);
    // 0x802C591C: or          $a2, $s4, $zero
    ctx->r6 = ctx->r20 | 0;
    // 0x802C5920: sw          $t0, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r8;
    // 0x802C5924: sw          $a3, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r7;
    // 0x802C5928: lui         $t1, 0x107
    ctx->r9 = S32(0X107 << 16);
    // 0x802C592C: addiu       $t1, $t1, -0x9D8
    ctx->r9 = ADD32(ctx->r9, -0X9D8);
    // 0x802C5930: sw          $t1, 0x4($a2)
    MEM_W(0X4, ctx->r6) = ctx->r9;
    // 0x802C5934: sw          $a3, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r7;
    // 0x802C5938: addiu       $s4, $s4, 0x8
    ctx->r20 = ADD32(ctx->r20, 0X8);
    // 0x802C593C: addiu       $s0, $zero, 0x1C
    ctx->r16 = ADD32(0, 0X1C);
L_802C5940:
    // 0x802C5940: addiu       $t2, $zero, 0x56
    ctx->r10 = ADD32(0, 0X56);
    // 0x802C5944: addiu       $t3, $zero, 0x10
    ctx->r11 = ADD32(0, 0X10);
    // 0x802C5948: sw          $t3, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r11;
    // 0x802C594C: sw          $t2, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r10;
    // 0x802C5950: or          $a0, $s4, $zero
    ctx->r4 = ctx->r20 | 0;
    // 0x802C5954: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C5958: or          $a2, $s0, $zero
    ctx->r6 = ctx->r16 | 0;
    // 0x802C595C: jal         0x80094338
    // 0x802C5960: addiu       $a3, $zero, 0x3A
    ctx->r7 = ADD32(0, 0X3A);
    func_80094338(rdram, ctx);
        goto after_0;
    // 0x802C5960: addiu       $a3, $zero, 0x3A
    ctx->r7 = ADD32(0, 0X3A);
    after_0:
    // 0x802C5964: addiu       $s0, $s0, 0x8D
    ctx->r16 = ADD32(ctx->r16, 0X8D);
    // 0x802C5968: slti        $at, $s0, 0x195
    ctx->r1 = SIGNED(ctx->r16) < 0X195 ? 1 : 0;
    // 0x802C596C: bne         $at, $zero, L_802C5940
    if (ctx->r1 != 0) {
        // 0x802C5970: or          $s4, $v0, $zero
        ctx->r20 = ctx->r2 | 0;
            goto L_802C5940;
    }
    // 0x802C5970: or          $s4, $v0, $zero
    ctx->r20 = ctx->r2 | 0;
    // 0x802C5974: or          $s1, $zero, $zero
    ctx->r17 = 0 | 0;
    // 0x802C5978: addiu       $fp, $zero, 0xED
    ctx->r30 = ADD32(0, 0XED);
    // 0x802C597C: addiu       $s6, $zero, 0x5
    ctx->r22 = ADD32(0, 0X5);
L_802C5980:
    // 0x802C5980: div         $zero, $s1, $s6
    lo = S32(S64(S32(ctx->r17)) / S64(S32(ctx->r22))); hi = S32(S64(S32(ctx->r17)) % S64(S32(ctx->r22)));
    // 0x802C5984: mflo        $t4
    ctx->r12 = lo;
    // 0x802C5988: addiu       $t6, $zero, 0x83
    ctx->r14 = ADD32(0, 0X83);
    // 0x802C598C: addiu       $t7, $zero, 0x10
    ctx->r15 = ADD32(0, 0X10);
    // 0x802C5990: multu       $t4, $fp
    result = U64(U32(ctx->r12)) * U64(U32(ctx->r30)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x802C5994: sw          $t7, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r15;
    // 0x802C5998: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x802C599C: or          $a0, $s4, $zero
    ctx->r4 = ctx->r20 | 0;
    // 0x802C59A0: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C59A4: bne         $s6, $zero, L_802C59B0
    if (ctx->r22 != 0) {
        // 0x802C59A8: nop
    
            goto L_802C59B0;
    }
    // 0x802C59A8: nop

    // 0x802C59AC: break       7
    do_break(2150390188);
L_802C59B0:
    // 0x802C59B0: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x802C59B4: bne         $s6, $at, L_802C59C8
    if (ctx->r22 != ctx->r1) {
        // 0x802C59B8: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_802C59C8;
    }
    // 0x802C59B8: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x802C59BC: bne         $s1, $at, L_802C59C8
    if (ctx->r17 != ctx->r1) {
        // 0x802C59C0: nop
    
            goto L_802C59C8;
    }
    // 0x802C59C0: nop

    // 0x802C59C4: break       6
    do_break(2150390212);
L_802C59C8:
    // 0x802C59C8: mflo        $a2
    ctx->r6 = lo;
    // 0x802C59CC: addiu       $a2, $a2, 0x1C
    ctx->r6 = ADD32(ctx->r6, 0X1C);
    // 0x802C59D0: nop

    // 0x802C59D4: div         $zero, $s1, $s6
    lo = S32(S64(S32(ctx->r17)) / S64(S32(ctx->r22))); hi = S32(S64(S32(ctx->r17)) % S64(S32(ctx->r22)));
    // 0x802C59D8: mfhi        $a3
    ctx->r7 = hi;
    // 0x802C59DC: sll         $t5, $a3, 3
    ctx->r13 = S32(ctx->r7 << 3);
    // 0x802C59E0: addu        $t5, $t5, $a3
    ctx->r13 = ADD32(ctx->r13, ctx->r7);
    // 0x802C59E4: sll         $t5, $t5, 1
    ctx->r13 = S32(ctx->r13 << 1);
    // 0x802C59E8: bne         $s6, $zero, L_802C59F4
    if (ctx->r22 != 0) {
        // 0x802C59EC: nop
    
            goto L_802C59F4;
    }
    // 0x802C59EC: nop

    // 0x802C59F0: break       7
    do_break(2150390256);
L_802C59F4:
    // 0x802C59F4: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x802C59F8: bne         $s6, $at, L_802C5A0C
    if (ctx->r22 != ctx->r1) {
        // 0x802C59FC: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_802C5A0C;
    }
    // 0x802C59FC: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x802C5A00: bne         $s1, $at, L_802C5A0C
    if (ctx->r17 != ctx->r1) {
        // 0x802C5A04: nop
    
            goto L_802C5A0C;
    }
    // 0x802C5A04: nop

    // 0x802C5A08: break       6
    do_break(2150390280);
L_802C5A0C:
    // 0x802C5A0C: addiu       $a3, $t5, 0x55
    ctx->r7 = ADD32(ctx->r13, 0X55);
    // 0x802C5A10: jal         0x80094338
    // 0x802C5A14: nop

    func_80094338(rdram, ctx);
        goto after_1;
    // 0x802C5A14: nop

    after_1:
    // 0x802C5A18: addiu       $s1, $s1, 0x1
    ctx->r17 = ADD32(ctx->r17, 0X1);
    // 0x802C5A1C: slti        $at, $s1, 0x9
    ctx->r1 = SIGNED(ctx->r17) < 0X9 ? 1 : 0;
    // 0x802C5A20: bne         $at, $zero, L_802C5980
    if (ctx->r1 != 0) {
        // 0x802C5A24: or          $s4, $v0, $zero
        ctx->r20 = ctx->r2 | 0;
            goto L_802C5980;
    }
    // 0x802C5A24: or          $s4, $v0, $zero
    ctx->r20 = ctx->r2 | 0;
    // 0x802C5A28: addiu       $t8, $zero, 0x5A
    ctx->r24 = ADD32(0, 0X5A);
    // 0x802C5A2C: addiu       $t9, $zero, 0x10
    ctx->r25 = ADD32(0, 0X10);
    // 0x802C5A30: sw          $t9, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r25;
    // 0x802C5A34: sw          $t8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r24;
    // 0x802C5A38: or          $a0, $s4, $zero
    ctx->r4 = ctx->r20 | 0;
    // 0x802C5A3C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C5A40: addiu       $a2, $zero, 0x5C
    ctx->r6 = ADD32(0, 0X5C);
    // 0x802C5A44: jal         0x80094338
    // 0x802C5A48: addiu       $a3, $zero, 0xB5
    ctx->r7 = ADD32(0, 0XB5);
    func_80094338(rdram, ctx);
        goto after_2;
    // 0x802C5A48: addiu       $a3, $zero, 0xB5
    ctx->r7 = ADD32(0, 0XB5);
    after_2:
    // 0x802C5A4C: addiu       $t0, $zero, 0x5A
    ctx->r8 = ADD32(0, 0X5A);
    // 0x802C5A50: addiu       $t1, $zero, 0x10
    ctx->r9 = ADD32(0, 0X10);
    // 0x802C5A54: sw          $t1, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r9;
    // 0x802C5A58: sw          $t0, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r8;
    // 0x802C5A5C: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C5A60: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C5A64: addiu       $a2, $zero, 0xF2
    ctx->r6 = ADD32(0, 0XF2);
    // 0x802C5A68: jal         0x80094338
    // 0x802C5A6C: addiu       $a3, $zero, 0xB5
    ctx->r7 = ADD32(0, 0XB5);
    func_80094338(rdram, ctx);
        goto after_3;
    // 0x802C5A6C: addiu       $a3, $zero, 0xB5
    ctx->r7 = ADD32(0, 0XB5);
    after_3:
    // 0x802C5A70: addiu       $t2, $zero, 0xFF
    ctx->r10 = ADD32(0, 0XFF);
    // 0x802C5A74: addiu       $t3, $zero, 0xFF
    ctx->r11 = ADD32(0, 0XFF);
    // 0x802C5A78: addiu       $t4, $zero, 0xFF
    ctx->r12 = ADD32(0, 0XFF);
    // 0x802C5A7C: addiu       $t5, $zero, 0xFF
    ctx->r13 = ADD32(0, 0XFF);
    // 0x802C5A80: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C5A84: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C5A88: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C5A8C: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C5A90: addiu       $t0, $zero, 0xFF
    ctx->r8 = ADD32(0, 0XFF);
    // 0x802C5A94: addiu       $t1, $zero, 0xFF
    ctx->r9 = ADD32(0, 0XFF);
    // 0x802C5A98: sw          $t1, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r9;
    // 0x802C5A9C: sw          $t0, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r8;
    // 0x802C5AA0: sw          $t9, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r25;
    // 0x802C5AA4: sw          $t8, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r24;
    // 0x802C5AA8: sw          $t7, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r15;
    // 0x802C5AAC: sw          $t6, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r14;
    // 0x802C5AB0: sw          $t5, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r13;
    // 0x802C5AB4: sw          $t4, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r12;
    // 0x802C5AB8: sw          $t3, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r11;
    // 0x802C5ABC: sw          $t2, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r10;
    // 0x802C5AC0: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C5AC4: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C5AC8: addiu       $a2, $zero, 0xFF
    ctx->r6 = ADD32(0, 0XFF);
    // 0x802C5ACC: jal         0x801E946C
    // 0x802C5AD0: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    func_801E946C(rdram, ctx);
        goto after_4;
    // 0x802C5AD0: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    after_4:
    // 0x802C5AD4: addiu       $t2, $zero, 0x1D
    ctx->r10 = ADD32(0, 0X1D);
    // 0x802C5AD8: sw          $t2, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r10;
    // 0x802C5ADC: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C5AE0: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C5AE4: addiu       $a2, $zero, 0x11
    ctx->r6 = ADD32(0, 0X11);
    // 0x802C5AE8: addiu       $a3, $zero, 0x54
    ctx->r7 = ADD32(0, 0X54);
    // 0x802C5AEC: jal         0x801E3EE0
    // 0x802C5AF0: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    func_801E3EE0(rdram, ctx);
        goto after_5;
    // 0x802C5AF0: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    after_5:
    // 0x802C5AF4: addiu       $t3, $zero, 0xCE
    ctx->r11 = ADD32(0, 0XCE);
    // 0x802C5AF8: sw          $t3, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r11;
    // 0x802C5AFC: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C5B00: addiu       $a1, $zero, 0x4
    ctx->r5 = ADD32(0, 0X4);
    // 0x802C5B04: addiu       $a2, $zero, 0xC
    ctx->r6 = ADD32(0, 0XC);
    // 0x802C5B08: addiu       $a3, $zero, 0x8B
    ctx->r7 = ADD32(0, 0X8B);
    // 0x802C5B0C: jal         0x801E3EE0
    // 0x802C5B10: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    func_801E3EE0(rdram, ctx);
        goto after_6;
    // 0x802C5B10: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    after_6:
    // 0x802C5B14: addiu       $t4, $zero, 0xCE
    ctx->r12 = ADD32(0, 0XCE);
    // 0x802C5B18: sw          $t4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r12;
    // 0x802C5B1C: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C5B20: addiu       $a1, $zero, 0x4
    ctx->r5 = ADD32(0, 0X4);
    // 0x802C5B24: addiu       $a2, $zero, 0xD
    ctx->r6 = ADD32(0, 0XD);
    // 0x802C5B28: addiu       $a3, $zero, 0xDD
    ctx->r7 = ADD32(0, 0XDD);
    // 0x802C5B2C: jal         0x801E3EE0
    // 0x802C5B30: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    func_801E3EE0(rdram, ctx);
        goto after_7;
    // 0x802C5B30: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    after_7:
    // 0x802C5B34: lui         $s2, 0x802C
    ctx->r18 = S32(0X802C << 16);
    // 0x802C5B38: lui         $s3, 0x802C
    ctx->r19 = S32(0X802C << 16);
    // 0x802C5B3C: lui         $s5, 0x802C
    ctx->r21 = S32(0X802C << 16);
    // 0x802C5B40: or          $s4, $v0, $zero
    ctx->r20 = ctx->r2 | 0;
    // 0x802C5B44: addiu       $s5, $s5, 0x6460
    ctx->r21 = ADD32(ctx->r21, 0X6460);
    // 0x802C5B48: addiu       $s3, $s3, 0x6480
    ctx->r19 = ADD32(ctx->r19, 0X6480);
    // 0x802C5B4C: addiu       $s2, $s2, 0x646C
    ctx->r18 = ADD32(ctx->r18, 0X646C);
    // 0x802C5B50: or          $s1, $zero, $zero
    ctx->r17 = 0 | 0;
    // 0x802C5B54: or          $s0, $zero, $zero
    ctx->r16 = 0 | 0;
L_802C5B58:
    // 0x802C5B58: lw          $t5, 0x0($s5)
    ctx->r13 = MEM_W(ctx->r21, 0X0);
    // 0x802C5B5C: or          $a0, $s4, $zero
    ctx->r4 = ctx->r20 | 0;
    // 0x802C5B60: addiu       $a2, $zero, 0xFF
    ctx->r6 = ADD32(0, 0XFF);
    // 0x802C5B64: bne         $s1, $t5, L_802C5B74
    if (ctx->r17 != ctx->r13) {
        // 0x802C5B68: addiu       $a3, $zero, 0xFF
        ctx->r7 = ADD32(0, 0XFF);
            goto L_802C5B74;
    }
    // 0x802C5B68: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    // 0x802C5B6C: b           L_802C5B78
    // 0x802C5B70: addiu       $a1, $zero, 0x6
    ctx->r5 = ADD32(0, 0X6);
        goto L_802C5B78;
    // 0x802C5B70: addiu       $a1, $zero, 0x6
    ctx->r5 = ADD32(0, 0X6);
L_802C5B74:
    // 0x802C5B74: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
L_802C5B78:
    // 0x802C5B78: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C5B7C: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C5B80: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C5B84: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C5B88: addiu       $t0, $zero, 0xFF
    ctx->r8 = ADD32(0, 0XFF);
    // 0x802C5B8C: addiu       $t1, $zero, 0xFF
    ctx->r9 = ADD32(0, 0XFF);
    // 0x802C5B90: addiu       $t2, $zero, 0xFF
    ctx->r10 = ADD32(0, 0XFF);
    // 0x802C5B94: addiu       $t3, $zero, 0xFF
    ctx->r11 = ADD32(0, 0XFF);
    // 0x802C5B98: addiu       $t4, $zero, 0xFF
    ctx->r12 = ADD32(0, 0XFF);
    // 0x802C5B9C: addiu       $t5, $zero, 0xFF
    ctx->r13 = ADD32(0, 0XFF);
    // 0x802C5BA0: sw          $t5, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r13;
    // 0x802C5BA4: sw          $t4, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r12;
    // 0x802C5BA8: sw          $t3, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r11;
    // 0x802C5BAC: sw          $t2, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r10;
    // 0x802C5BB0: sw          $t1, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r9;
    // 0x802C5BB4: sw          $t0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r8;
    // 0x802C5BB8: sw          $t9, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r25;
    // 0x802C5BBC: sw          $t8, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r24;
    // 0x802C5BC0: sw          $t7, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r15;
    // 0x802C5BC4: jal         0x801E946C
    // 0x802C5BC8: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    func_801E946C(rdram, ctx);
        goto after_8;
    // 0x802C5BC8: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    after_8:
    // 0x802C5BCC: lw          $t6, 0x0($s3)
    ctx->r14 = MEM_W(ctx->r19, 0X0);
    // 0x802C5BD0: addiu       $t7, $zero, 0x3D
    ctx->r15 = ADD32(0, 0X3D);
    // 0x802C5BD4: sw          $t7, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r15;
    // 0x802C5BD8: addu        $a3, $t6, $s0
    ctx->r7 = ADD32(ctx->r14, ctx->r16);
    // 0x802C5BDC: addiu       $a3, $a3, 0x34
    ctx->r7 = ADD32(ctx->r7, 0X34);
    // 0x802C5BE0: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C5BE4: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C5BE8: lw          $a2, 0x0($s2)
    ctx->r6 = MEM_W(ctx->r18, 0X0);
    // 0x802C5BEC: jal         0x801E3EE0
    // 0x802C5BF0: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    func_801E3EE0(rdram, ctx);
        goto after_9;
    // 0x802C5BF0: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    after_9:
    // 0x802C5BF4: addiu       $s1, $s1, 0x1
    ctx->r17 = ADD32(ctx->r17, 0X1);
    // 0x802C5BF8: slti        $at, $s1, 0x3
    ctx->r1 = SIGNED(ctx->r17) < 0X3 ? 1 : 0;
    // 0x802C5BFC: addiu       $s0, $s0, 0x8D
    ctx->r16 = ADD32(ctx->r16, 0X8D);
    // 0x802C5C00: addiu       $s2, $s2, 0x4
    ctx->r18 = ADD32(ctx->r18, 0X4);
    // 0x802C5C04: addiu       $s3, $s3, 0x4
    ctx->r19 = ADD32(ctx->r19, 0X4);
    // 0x802C5C08: bne         $at, $zero, L_802C5B58
    if (ctx->r1 != 0) {
        // 0x802C5C0C: or          $s4, $v0, $zero
        ctx->r20 = ctx->r2 | 0;
            goto L_802C5B58;
    }
    // 0x802C5C0C: or          $s4, $v0, $zero
    ctx->r20 = ctx->r2 | 0;
    // 0x802C5C10: lui         $s0, 0x800E
    ctx->r16 = S32(0X800E << 16);
    // 0x802C5C14: lui         $s7, 0x801D
    ctx->r23 = S32(0X801D << 16);
    // 0x802C5C18: lui         $s3, 0x800E
    ctx->r19 = S32(0X800E << 16);
    // 0x802C5C1C: lui         $s2, 0x802C
    ctx->r18 = S32(0X802C << 16);
    // 0x802C5C20: addiu       $s2, $s2, 0x6464
    ctx->r18 = ADD32(ctx->r18, 0X6464);
    // 0x802C5C24: addiu       $s3, $s3, -0x55F0
    ctx->r19 = ADD32(ctx->r19, -0X55F0);
    // 0x802C5C28: addiu       $s7, $s7, -0x19C0
    ctx->r23 = ADD32(ctx->r23, -0X19C0);
    // 0x802C5C2C: addiu       $s0, $s0, -0x5528
    ctx->r16 = ADD32(ctx->r16, -0X5528);
    // 0x802C5C30: or          $s1, $zero, $zero
    ctx->r17 = 0 | 0;
L_802C5C34:
    // 0x802C5C34: lw          $t8, 0x0($s7)
    ctx->r24 = MEM_W(ctx->r23, 0X0);
    // 0x802C5C38: or          $a0, $s4, $zero
    ctx->r4 = ctx->r20 | 0;
    // 0x802C5C3C: addiu       $a2, $zero, 0x80
    ctx->r6 = ADD32(0, 0X80);
    // 0x802C5C40: bne         $t8, $zero, L_802C5C74
    if (ctx->r24 != 0) {
        // 0x802C5C44: addiu       $a3, $zero, 0x80
        ctx->r7 = ADD32(0, 0X80);
            goto L_802C5C74;
    }
    // 0x802C5C44: addiu       $a3, $zero, 0x80
    ctx->r7 = ADD32(0, 0X80);
    // 0x802C5C48: lw          $t9, 0x0($s5)
    ctx->r25 = MEM_W(ctx->r21, 0X0);
    // 0x802C5C4C: bne         $t9, $zero, L_802C5C6C
    if (ctx->r25 != 0) {
        // 0x802C5C50: nop
    
            goto L_802C5C6C;
    }
    // 0x802C5C50: nop

    // 0x802C5C54: bne         $s1, $zero, L_802C5C64
    if (ctx->r17 != 0) {
        // 0x802C5C58: nop
    
            goto L_802C5C64;
    }
    // 0x802C5C58: nop

    // 0x802C5C5C: b           L_802C5CC4
    // 0x802C5C60: addiu       $a1, $zero, 0x7
    ctx->r5 = ADD32(0, 0X7);
        goto L_802C5CC4;
    // 0x802C5C60: addiu       $a1, $zero, 0x7
    ctx->r5 = ADD32(0, 0X7);
L_802C5C64:
    // 0x802C5C64: b           L_802C5CC4
    // 0x802C5C68: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
        goto L_802C5CC4;
    // 0x802C5C68: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
L_802C5C6C:
    // 0x802C5C6C: b           L_802C5CC4
    // 0x802C5C70: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
        goto L_802C5CC4;
    // 0x802C5C70: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
L_802C5C74:
    // 0x802C5C74: lw          $t0, 0x0($s5)
    ctx->r8 = MEM_W(ctx->r21, 0X0);
    // 0x802C5C78: bnel        $t0, $zero, L_802C5CB0
    if (ctx->r8 != 0) {
        // 0x802C5C7C: lw          $t2, 0x0($s2)
        ctx->r10 = MEM_W(ctx->r18, 0X0);
            goto L_802C5CB0;
    }
    goto skip_0;
    // 0x802C5C7C: lw          $t2, 0x0($s2)
    ctx->r10 = MEM_W(ctx->r18, 0X0);
    skip_0:
    // 0x802C5C80: bnel        $s1, $zero, L_802C5C94
    if (ctx->r17 != 0) {
        // 0x802C5C84: lw          $t1, 0x0($s2)
        ctx->r9 = MEM_W(ctx->r18, 0X0);
            goto L_802C5C94;
    }
    goto skip_1;
    // 0x802C5C84: lw          $t1, 0x0($s2)
    ctx->r9 = MEM_W(ctx->r18, 0X0);
    skip_1:
    // 0x802C5C88: b           L_802C5CC4
    // 0x802C5C8C: addiu       $a1, $zero, 0x7
    ctx->r5 = ADD32(0, 0X7);
        goto L_802C5CC4;
    // 0x802C5C8C: addiu       $a1, $zero, 0x7
    ctx->r5 = ADD32(0, 0X7);
    // 0x802C5C90: lw          $t1, 0x0($s2)
    ctx->r9 = MEM_W(ctx->r18, 0X0);
L_802C5C94:
    // 0x802C5C94: bne         $s1, $t1, L_802C5CA4
    if (ctx->r17 != ctx->r9) {
        // 0x802C5C98: nop
    
            goto L_802C5CA4;
    }
    // 0x802C5C98: nop

    // 0x802C5C9C: b           L_802C5CC4
    // 0x802C5CA0: addiu       $a1, $zero, 0x6
    ctx->r5 = ADD32(0, 0X6);
        goto L_802C5CC4;
    // 0x802C5CA0: addiu       $a1, $zero, 0x6
    ctx->r5 = ADD32(0, 0X6);
L_802C5CA4:
    // 0x802C5CA4: b           L_802C5CC4
    // 0x802C5CA8: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
        goto L_802C5CC4;
    // 0x802C5CA8: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C5CAC: lw          $t2, 0x0($s2)
    ctx->r10 = MEM_W(ctx->r18, 0X0);
L_802C5CB0:
    // 0x802C5CB0: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C5CB4: bne         $s1, $t2, L_802C5CC4
    if (ctx->r17 != ctx->r10) {
        // 0x802C5CB8: nop
    
            goto L_802C5CC4;
    }
    // 0x802C5CB8: nop

    // 0x802C5CBC: b           L_802C5CC4
    // 0x802C5CC0: addiu       $a1, $zero, 0x6
    ctx->r5 = ADD32(0, 0X6);
        goto L_802C5CC4;
    // 0x802C5CC0: addiu       $a1, $zero, 0x6
    ctx->r5 = ADD32(0, 0X6);
L_802C5CC4:
    // 0x802C5CC4: addiu       $t3, $zero, 0x80
    ctx->r11 = ADD32(0, 0X80);
    // 0x802C5CC8: addiu       $t4, $zero, 0xFF
    ctx->r12 = ADD32(0, 0XFF);
    // 0x802C5CCC: addiu       $t5, $zero, 0xFF
    ctx->r13 = ADD32(0, 0XFF);
    // 0x802C5CD0: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C5CD4: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C5CD8: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C5CDC: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C5CE0: addiu       $t0, $zero, 0xFF
    ctx->r8 = ADD32(0, 0XFF);
    // 0x802C5CE4: addiu       $t1, $zero, 0xFF
    ctx->r9 = ADD32(0, 0XFF);
    // 0x802C5CE8: addiu       $t2, $zero, 0xFF
    ctx->r10 = ADD32(0, 0XFF);
    // 0x802C5CEC: sw          $t2, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r10;
    // 0x802C5CF0: sw          $t1, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r9;
    // 0x802C5CF4: sw          $t0, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r8;
    // 0x802C5CF8: sw          $t9, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r25;
    // 0x802C5CFC: sw          $t8, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r24;
    // 0x802C5D00: sw          $t7, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r15;
    // 0x802C5D04: sw          $t6, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r14;
    // 0x802C5D08: sw          $t5, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r13;
    // 0x802C5D0C: sw          $t4, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r12;
    // 0x802C5D10: jal         0x801E946C
    // 0x802C5D14: sw          $t3, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r11;
    func_801E946C(rdram, ctx);
        goto after_10;
    // 0x802C5D14: sw          $t3, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r11;
    after_10:
    // 0x802C5D18: div         $zero, $s1, $s6
    lo = S32(S64(S32(ctx->r17)) / S64(S32(ctx->r22))); hi = S32(S64(S32(ctx->r17)) % S64(S32(ctx->r22)));
    // 0x802C5D1C: mflo        $t6
    ctx->r14 = lo;
    // 0x802C5D20: lw          $v1, 0x0($s0)
    ctx->r3 = MEM_W(ctx->r16, 0X0);
    // 0x802C5D24: lui         $t5, 0x802C
    ctx->r13 = S32(0X802C << 16);
    // 0x802C5D28: multu       $t6, $fp
    result = U64(U32(ctx->r14)) * U64(U32(ctx->r30)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x802C5D2C: sll         $t3, $v1, 2
    ctx->r11 = S32(ctx->r3 << 2);
    // 0x802C5D30: addu        $t5, $t5, $t3
    ctx->r13 = ADD32(ctx->r13, ctx->r11);
    // 0x802C5D34: lw          $t5, 0x648C($t5)
    ctx->r13 = MEM_W(ctx->r13, 0X648C);
    // 0x802C5D38: addu        $t4, $s3, $t3
    ctx->r12 = ADD32(ctx->r19, ctx->r11);
    // 0x802C5D3C: lw          $a2, 0x0($t4)
    ctx->r6 = MEM_W(ctx->r12, 0X0);
    // 0x802C5D40: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    // 0x802C5D44: or          $v1, $t3, $zero
    ctx->r3 = ctx->r11 | 0;
    // 0x802C5D48: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C5D4C: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C5D50: mflo        $t7
    ctx->r15 = lo;
    // 0x802C5D54: addu        $a3, $t5, $t7
    ctx->r7 = ADD32(ctx->r13, ctx->r15);
    // 0x802C5D58: bne         $s6, $zero, L_802C5D64
    if (ctx->r22 != 0) {
        // 0x802C5D5C: nop
    
            goto L_802C5D64;
    }
    // 0x802C5D5C: nop

    // 0x802C5D60: break       7
    do_break(2150391136);
L_802C5D64:
    // 0x802C5D64: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x802C5D68: bne         $s6, $at, L_802C5D7C
    if (ctx->r22 != ctx->r1) {
        // 0x802C5D6C: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_802C5D7C;
    }
    // 0x802C5D6C: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x802C5D70: bne         $s1, $at, L_802C5D7C
    if (ctx->r17 != ctx->r1) {
        // 0x802C5D74: nop
    
            goto L_802C5D7C;
    }
    // 0x802C5D74: nop

    // 0x802C5D78: break       6
    do_break(2150391160);
L_802C5D7C:
    // 0x802C5D7C: div         $zero, $s1, $s6
    lo = S32(S64(S32(ctx->r17)) / S64(S32(ctx->r22))); hi = S32(S64(S32(ctx->r17)) % S64(S32(ctx->r22)));
    // 0x802C5D80: mfhi        $t8
    ctx->r24 = hi;
    // 0x802C5D84: sll         $t9, $t8, 3
    ctx->r25 = S32(ctx->r24 << 3);
    // 0x802C5D88: addu        $t9, $t9, $t8
    ctx->r25 = ADD32(ctx->r25, ctx->r24);
    // 0x802C5D8C: sll         $t9, $t9, 1
    ctx->r25 = S32(ctx->r25 << 1);
    // 0x802C5D90: addiu       $t0, $t9, 0x58
    ctx->r8 = ADD32(ctx->r25, 0X58);
    // 0x802C5D94: sw          $t0, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r8;
    // 0x802C5D98: addiu       $a3, $a3, 0x37
    ctx->r7 = ADD32(ctx->r7, 0X37);
    // 0x802C5D9C: bne         $s6, $zero, L_802C5DA8
    if (ctx->r22 != 0) {
        // 0x802C5DA0: nop
    
            goto L_802C5DA8;
    }
    // 0x802C5DA0: nop

    // 0x802C5DA4: break       7
    do_break(2150391204);
L_802C5DA8:
    // 0x802C5DA8: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x802C5DAC: bne         $s6, $at, L_802C5DC0
    if (ctx->r22 != ctx->r1) {
        // 0x802C5DB0: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_802C5DC0;
    }
    // 0x802C5DB0: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x802C5DB4: bne         $s1, $at, L_802C5DC0
    if (ctx->r17 != ctx->r1) {
        // 0x802C5DB8: nop
    
            goto L_802C5DC0;
    }
    // 0x802C5DB8: nop

    // 0x802C5DBC: break       6
    do_break(2150391228);
L_802C5DC0:
    // 0x802C5DC0: jal         0x801E3EE0
    // 0x802C5DC4: nop

    func_801E3EE0(rdram, ctx);
        goto after_11;
    // 0x802C5DC4: nop

    after_11:
    // 0x802C5DC8: addiu       $s1, $s1, 0x1
    ctx->r17 = ADD32(ctx->r17, 0X1);
    // 0x802C5DCC: slti        $at, $s1, 0x9
    ctx->r1 = SIGNED(ctx->r17) < 0X9 ? 1 : 0;
    // 0x802C5DD0: addiu       $s0, $s0, 0x4
    ctx->r16 = ADD32(ctx->r16, 0X4);
    // 0x802C5DD4: bne         $at, $zero, L_802C5C34
    if (ctx->r1 != 0) {
        // 0x802C5DD8: or          $s4, $v0, $zero
        ctx->r20 = ctx->r2 | 0;
            goto L_802C5C34;
    }
    // 0x802C5DD8: or          $s4, $v0, $zero
    ctx->r20 = ctx->r2 | 0;
    // 0x802C5DDC: lui         $s0, 0x802C
    ctx->r16 = S32(0X802C << 16);
    // 0x802C5DE0: lui         $s5, 0x802C
    ctx->r21 = S32(0X802C << 16);
    // 0x802C5DE4: addiu       $s5, $s5, 0x6468
    ctx->r21 = ADD32(ctx->r21, 0X6468);
    // 0x802C5DE8: addiu       $s0, $s0, 0x6478
    ctx->r16 = ADD32(ctx->r16, 0X6478);
    // 0x802C5DEC: or          $s1, $zero, $zero
    ctx->r17 = 0 | 0;
    // 0x802C5DF0: addiu       $s2, $zero, 0x6C
    ctx->r18 = ADD32(0, 0X6C);
    // 0x802C5DF4: addiu       $s3, $zero, 0x2
    ctx->r19 = ADD32(0, 0X2);
L_802C5DF8:
    // 0x802C5DF8: lw          $t1, 0x0($s7)
    ctx->r9 = MEM_W(ctx->r23, 0X0);
    // 0x802C5DFC: or          $a0, $s4, $zero
    ctx->r4 = ctx->r20 | 0;
    // 0x802C5E00: addiu       $a2, $zero, 0x80
    ctx->r6 = ADD32(0, 0X80);
    // 0x802C5E04: bne         $s3, $t1, L_802C5E28
    if (ctx->r19 != ctx->r9) {
        // 0x802C5E08: addiu       $a3, $zero, 0x80
        ctx->r7 = ADD32(0, 0X80);
            goto L_802C5E28;
    }
    // 0x802C5E08: addiu       $a3, $zero, 0x80
    ctx->r7 = ADD32(0, 0X80);
    // 0x802C5E0C: lw          $t2, 0x0($s5)
    ctx->r10 = MEM_W(ctx->r21, 0X0);
    // 0x802C5E10: bne         $s1, $t2, L_802C5E20
    if (ctx->r17 != ctx->r10) {
        // 0x802C5E14: nop
    
            goto L_802C5E20;
    }
    // 0x802C5E14: nop

    // 0x802C5E18: b           L_802C5E2C
    // 0x802C5E1C: addiu       $a1, $zero, 0x6
    ctx->r5 = ADD32(0, 0X6);
        goto L_802C5E2C;
    // 0x802C5E1C: addiu       $a1, $zero, 0x6
    ctx->r5 = ADD32(0, 0X6);
L_802C5E20:
    // 0x802C5E20: b           L_802C5E2C
    // 0x802C5E24: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
        goto L_802C5E2C;
    // 0x802C5E24: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
L_802C5E28:
    // 0x802C5E28: addiu       $a1, $zero, 0x7
    ctx->r5 = ADD32(0, 0X7);
L_802C5E2C:
    // 0x802C5E2C: addiu       $t3, $zero, 0x80
    ctx->r11 = ADD32(0, 0X80);
    // 0x802C5E30: addiu       $t4, $zero, 0xFF
    ctx->r12 = ADD32(0, 0XFF);
    // 0x802C5E34: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C5E38: addiu       $t5, $zero, 0xFF
    ctx->r13 = ADD32(0, 0XFF);
    // 0x802C5E3C: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C5E40: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C5E44: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C5E48: addiu       $t0, $zero, 0xFF
    ctx->r8 = ADD32(0, 0XFF);
    // 0x802C5E4C: addiu       $t1, $zero, 0xFF
    ctx->r9 = ADD32(0, 0XFF);
    // 0x802C5E50: addiu       $t2, $zero, 0xFF
    ctx->r10 = ADD32(0, 0XFF);
    // 0x802C5E54: sw          $t2, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r10;
    // 0x802C5E58: sw          $t1, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r9;
    // 0x802C5E5C: sw          $t0, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r8;
    // 0x802C5E60: sw          $t9, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r25;
    // 0x802C5E64: sw          $t8, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r24;
    // 0x802C5E68: sw          $t7, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r15;
    // 0x802C5E6C: sw          $t5, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r13;
    // 0x802C5E70: sw          $t6, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r14;
    // 0x802C5E74: sw          $t4, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r12;
    // 0x802C5E78: jal         0x801E946C
    // 0x802C5E7C: sw          $t3, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r11;
    func_801E946C(rdram, ctx);
        goto after_12;
    // 0x802C5E7C: sw          $t3, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r11;
    after_12:
    // 0x802C5E80: addiu       $t3, $zero, 0xB8
    ctx->r11 = ADD32(0, 0XB8);
    // 0x802C5E84: sw          $t3, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r11;
    // 0x802C5E88: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C5E8C: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C5E90: lw          $a2, 0x0($s0)
    ctx->r6 = MEM_W(ctx->r16, 0X0);
    // 0x802C5E94: or          $a3, $s2, $zero
    ctx->r7 = ctx->r18 | 0;
    // 0x802C5E98: jal         0x801E3EE0
    // 0x802C5E9C: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    func_801E3EE0(rdram, ctx);
        goto after_13;
    // 0x802C5E9C: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    after_13:
    // 0x802C5EA0: addiu       $s1, $s1, 0x1
    ctx->r17 = ADD32(ctx->r17, 0X1);
    // 0x802C5EA4: addiu       $s0, $s0, 0x4
    ctx->r16 = ADD32(ctx->r16, 0X4);
    // 0x802C5EA8: addiu       $s2, $s2, 0x95
    ctx->r18 = ADD32(ctx->r18, 0X95);
    // 0x802C5EAC: bne         $s1, $s3, L_802C5DF8
    if (ctx->r17 != ctx->r19) {
        // 0x802C5EB0: or          $s4, $v0, $zero
        ctx->r20 = ctx->r2 | 0;
            goto L_802C5DF8;
    }
    // 0x802C5EB0: or          $s4, $v0, $zero
    ctx->r20 = ctx->r2 | 0;
    // 0x802C5EB4: lw          $ra, 0x64($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X64);
    // 0x802C5EB8: lw          $s0, 0x40($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X40);
    // 0x802C5EBC: lw          $s1, 0x44($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X44);
    // 0x802C5EC0: lw          $s2, 0x48($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X48);
    // 0x802C5EC4: lw          $s3, 0x4C($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X4C);
    // 0x802C5EC8: lw          $s4, 0x50($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X50);
    // 0x802C5ECC: lw          $s5, 0x54($sp)
    ctx->r21 = MEM_W(ctx->r29, 0X54);
    // 0x802C5ED0: lw          $s6, 0x58($sp)
    ctx->r22 = MEM_W(ctx->r29, 0X58);
    // 0x802C5ED4: lw          $s7, 0x5C($sp)
    ctx->r23 = MEM_W(ctx->r29, 0X5C);
    // 0x802C5ED8: lw          $fp, 0x60($sp)
    ctx->r30 = MEM_W(ctx->r29, 0X60);
    // 0x802C5EDC: jr          $ra
    // 0x802C5EE0: addiu       $sp, $sp, 0x68
    ctx->r29 = ADD32(ctx->r29, 0X68);
    return;
    // 0x802C5EE0: addiu       $sp, $sp, 0x68
    ctx->r29 = ADD32(ctx->r29, 0X68);
;}
RECOMP_FUNC void func_i12_802C5EE4(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C5EE4: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x802C5EE8: addiu       $v0, $v0, -0x54DC
    ctx->r2 = ADD32(ctx->r2, -0X54DC);
    // 0x802C5EEC: lw          $t6, 0x0($v0)
    ctx->r14 = MEM_W(ctx->r2, 0X0);
    // 0x802C5EF0: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C5EF4: addiu       $t7, $zero, 0x47
    ctx->r15 = ADD32(0, 0X47);
    // 0x802C5EF8: sw          $t6, -0x19CC($at)
    MEM_W(-0X19CC, ctx->r1) = ctx->r14;
    // 0x802C5EFC: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C5F00: sw          $a0, -0x19D0($at)
    MEM_W(-0X19D0, ctx->r1) = ctx->r4;
    // 0x802C5F04: sw          $t7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r15;
    // 0x802C5F08: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C5F0C: addiu       $t8, $zero, 0x10
    ctx->r24 = ADD32(0, 0X10);
    // 0x802C5F10: sw          $t8, -0x19C8($at)
    MEM_W(-0X19C8, ctx->r1) = ctx->r24;
    // 0x802C5F14: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C5F18: addiu       $t9, $zero, 0x1
    ctx->r25 = ADD32(0, 0X1);
    // 0x802C5F1C: sw          $t9, -0x19C4($at)
    MEM_W(-0X19C4, ctx->r1) = ctx->r25;
    // 0x802C5F20: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C5F24: sw          $zero, -0x19C0($at)
    MEM_W(-0X19C0, ctx->r1) = 0;
    // 0x802C5F28: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C5F2C: sw          $zero, -0x19BC($at)
    MEM_W(-0X19BC, ctx->r1) = 0;
    // 0x802C5F30: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x802C5F34: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x802C5F38: sw          $zero, -0x54E4($at)
    MEM_W(-0X54E4, ctx->r1) = 0;
    // 0x802C5F3C: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x802C5F40: lui         $at, 0x800D
    ctx->r1 = S32(0X800D << 16);
    // 0x802C5F44: addiu       $t0, $zero, 0x2
    ctx->r8 = ADD32(0, 0X2);
    // 0x802C5F48: sw          $t0, 0x461C($at)
    MEM_W(0X461C, ctx->r1) = ctx->r8;
    // 0x802C5F4C: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    // 0x802C5F50: addiu       $a1, $zero, 0x4
    ctx->r5 = ADD32(0, 0X4);
    // 0x802C5F54: jal         0x801E6FB0
    // 0x802C5F58: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    FadeTransition_SetProps(rdram, ctx);
        goto after_0;
    // 0x802C5F58: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    after_0:
    // 0x802C5F5C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x802C5F60: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x802C5F64: jr          $ra
    // 0x802C5F68: nop

    return;
    // 0x802C5F68: nop

;}
RECOMP_FUNC void func_i12_802C5F6C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C5F6C: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x802C5F70: lhu         $v0, -0x19A6($v0)
    ctx->r2 = MEM_HU(ctx->r2, -0X19A6);
    // 0x802C5F74: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x802C5F78: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x802C5F7C: andi        $t6, $v0, 0xB000
    ctx->r14 = ctx->r2 & 0XB000;
    // 0x802C5F80: beq         $t6, $zero, L_802C6100
    if (ctx->r14 == 0) {
        // 0x802C5F84: or          $a2, $zero, $zero
        ctx->r6 = 0 | 0;
            goto L_802C6100;
    }
    // 0x802C5F84: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x802C5F88: lui         $a1, 0x801D
    ctx->r5 = S32(0X801D << 16);
    // 0x802C5F8C: addiu       $a1, $a1, -0x19C0
    ctx->r5 = ADD32(ctx->r5, -0X19C0);
    // 0x802C5F90: lw          $v0, 0x0($a1)
    ctx->r2 = MEM_W(ctx->r5, 0X0);
    // 0x802C5F94: lui         $a0, 0x802C
    ctx->r4 = S32(0X802C << 16);
    // 0x802C5F98: addiu       $a0, $a0, 0x6460
    ctx->r4 = ADD32(ctx->r4, 0X6460);
    // 0x802C5F9C: beq         $v0, $zero, L_802C5FC0
    if (ctx->r2 == 0) {
        // 0x802C5FA0: addiu       $a3, $zero, 0x1
        ctx->r7 = ADD32(0, 0X1);
            goto L_802C5FC0;
    }
    // 0x802C5FA0: addiu       $a3, $zero, 0x1
    ctx->r7 = ADD32(0, 0X1);
    // 0x802C5FA4: beq         $v0, $a3, L_802C601C
    if (ctx->r2 == ctx->r7) {
        // 0x802C5FA8: addiu       $t7, $zero, 0x2
        ctx->r15 = ADD32(0, 0X2);
            goto L_802C601C;
    }
    // 0x802C5FA8: addiu       $t7, $zero, 0x2
    ctx->r15 = ADD32(0, 0X2);
    // 0x802C5FAC: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x802C5FB0: beq         $v0, $at, L_802C6044
    if (ctx->r2 == ctx->r1) {
        // 0x802C5FB4: nop
    
            goto L_802C6044;
    }
    // 0x802C5FB4: nop

    // 0x802C5FB8: b           L_802C60CC
    // 0x802C5FBC: nop

        goto L_802C60CC;
    // 0x802C5FBC: nop

L_802C5FC0:
    // 0x802C5FC0: lw          $v0, 0x0($a0)
    ctx->r2 = MEM_W(ctx->r4, 0X0);
    // 0x802C5FC4: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x802C5FC8: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    // 0x802C5FCC: bne         $v0, $at, L_802C5FE8
    if (ctx->r2 != ctx->r1) {
        // 0x802C5FD0: addiu       $a0, $zero, 0x3C
        ctx->r4 = ADD32(0, 0X3C);
            goto L_802C5FE8;
    }
    // 0x802C5FD0: addiu       $a0, $zero, 0x3C
    ctx->r4 = ADD32(0, 0X3C);
    // 0x802C5FD4: jal         0x802C5EE4
    // 0x802C5FD8: sw          $a2, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r6;
    func_i12_802C5EE4(rdram, ctx);
        goto after_0;
    // 0x802C5FD8: sw          $a2, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r6;
    after_0:
    // 0x802C5FDC: lw          $a2, 0x1C($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X1C);
    // 0x802C5FE0: b           L_802C60CC
    // 0x802C5FE4: addiu       $a3, $zero, 0x1
    ctx->r7 = ADD32(0, 0X1);
        goto L_802C60CC;
    // 0x802C5FE4: addiu       $a3, $zero, 0x1
    ctx->r7 = ADD32(0, 0X1);
L_802C5FE8:
    // 0x802C5FE8: bne         $v0, $zero, L_802C6008
    if (ctx->r2 != 0) {
        // 0x802C5FEC: lui         $v1, 0x802C
        ctx->r3 = S32(0X802C << 16);
            goto L_802C6008;
    }
    // 0x802C5FEC: lui         $v1, 0x802C
    ctx->r3 = S32(0X802C << 16);
    // 0x802C5FF0: lui         $v1, 0x802C
    ctx->r3 = S32(0X802C << 16);
    // 0x802C5FF4: addiu       $v1, $v1, 0x6464
    ctx->r3 = ADD32(ctx->r3, 0X6464);
    // 0x802C5FF8: addiu       $a3, $zero, 0x1
    ctx->r7 = ADD32(0, 0X1);
    // 0x802C5FFC: sw          $a3, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r7;
    // 0x802C6000: b           L_802C60CC
    // 0x802C6004: sw          $a3, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r7;
        goto L_802C60CC;
    // 0x802C6004: sw          $a3, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r7;
L_802C6008:
    // 0x802C6008: addiu       $v1, $v1, 0x6464
    ctx->r3 = ADD32(ctx->r3, 0X6464);
    // 0x802C600C: addiu       $a3, $zero, 0x1
    ctx->r7 = ADD32(0, 0X1);
    // 0x802C6010: sw          $zero, 0x0($v1)
    MEM_W(0X0, ctx->r3) = 0;
    // 0x802C6014: b           L_802C60CC
    // 0x802C6018: sw          $a3, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r7;
        goto L_802C60CC;
    // 0x802C6018: sw          $a3, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r7;
L_802C601C:
    // 0x802C601C: lui         $v0, 0x802C
    ctx->r2 = S32(0X802C << 16);
    // 0x802C6020: addiu       $v0, $v0, 0x6468
    ctx->r2 = ADD32(ctx->r2, 0X6468);
    // 0x802C6024: sw          $t7, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r15;
    // 0x802C6028: sw          $a3, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r7;
    // 0x802C602C: addiu       $a0, $zero, 0x3
    ctx->r4 = ADD32(0, 0X3);
    // 0x802C6030: jal         0x800C3E6C
    // 0x802C6034: sw          $a2, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r6;
    func_800C3E6C(rdram, ctx);
        goto after_1;
    // 0x802C6034: sw          $a2, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r6;
    after_1:
    // 0x802C6038: lw          $a2, 0x1C($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X1C);
    // 0x802C603C: b           L_802C60CC
    // 0x802C6040: addiu       $a3, $zero, 0x1
    ctx->r7 = ADD32(0, 0X1);
        goto L_802C60CC;
    // 0x802C6040: addiu       $a3, $zero, 0x1
    ctx->r7 = ADD32(0, 0X1);
L_802C6044:
    // 0x802C6044: lui         $v0, 0x802C
    ctx->r2 = S32(0X802C << 16);
    // 0x802C6048: addiu       $v0, $v0, 0x6468
    ctx->r2 = ADD32(ctx->r2, 0X6468);
    // 0x802C604C: lw          $t8, 0x0($v0)
    ctx->r24 = MEM_W(ctx->r2, 0X0);
    // 0x802C6050: or          $a2, $a3, $zero
    ctx->r6 = ctx->r7 | 0;
    // 0x802C6054: sw          $a3, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r7;
    // 0x802C6058: bne         $t8, $zero, L_802C60CC
    if (ctx->r24 != 0) {
        // 0x802C605C: lui         $a0, 0x802C
        ctx->r4 = S32(0X802C << 16);
            goto L_802C60CC;
    }
    // 0x802C605C: lui         $a0, 0x802C
    ctx->r4 = S32(0X802C << 16);
    // 0x802C6060: addiu       $a0, $a0, 0x6460
    ctx->r4 = ADD32(ctx->r4, 0X6460);
    // 0x802C6064: lw          $t9, 0x0($a0)
    ctx->r25 = MEM_W(ctx->r4, 0X0);
    // 0x802C6068: lui         $v1, 0x802C
    ctx->r3 = S32(0X802C << 16);
    // 0x802C606C: addiu       $a2, $zero, 0x2
    ctx->r6 = ADD32(0, 0X2);
    // 0x802C6070: bne         $t9, $zero, L_802C60A8
    if (ctx->r25 != 0) {
        // 0x802C6074: addiu       $v1, $v1, 0x6464
        ctx->r3 = ADD32(ctx->r3, 0X6464);
            goto L_802C60A8;
    }
    // 0x802C6074: addiu       $v1, $v1, 0x6464
    ctx->r3 = ADD32(ctx->r3, 0X6464);
    // 0x802C6078: lui         $v1, 0x802C
    ctx->r3 = S32(0X802C << 16);
    // 0x802C607C: addiu       $v1, $v1, 0x6464
    ctx->r3 = ADD32(ctx->r3, 0X6464);
    // 0x802C6080: lw          $t0, 0x0($v1)
    ctx->r8 = MEM_W(ctx->r3, 0X0);
    // 0x802C6084: lui         $a0, 0x800E
    ctx->r4 = S32(0X800E << 16);
    // 0x802C6088: sw          $a2, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r6;
    // 0x802C608C: sll         $t1, $t0, 2
    ctx->r9 = S32(ctx->r8 << 2);
    // 0x802C6090: addu        $a0, $a0, $t1
    ctx->r4 = ADD32(ctx->r4, ctx->r9);
    // 0x802C6094: jal         0x8007C604
    // 0x802C6098: lw          $a0, -0x5528($a0)
    ctx->r4 = MEM_W(ctx->r4, -0X5528);
    func_8007C604(rdram, ctx);
        goto after_2;
    // 0x802C6098: lw          $a0, -0x5528($a0)
    ctx->r4 = MEM_W(ctx->r4, -0X5528);
    after_2:
    // 0x802C609C: lw          $a2, 0x1C($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X1C);
    // 0x802C60A0: b           L_802C60CC
    // 0x802C60A4: addiu       $a3, $zero, 0x1
    ctx->r7 = ADD32(0, 0X1);
        goto L_802C60CC;
    // 0x802C60A4: addiu       $a3, $zero, 0x1
    ctx->r7 = ADD32(0, 0X1);
L_802C60A8:
    // 0x802C60A8: lw          $t2, 0x0($v1)
    ctx->r10 = MEM_W(ctx->r3, 0X0);
    // 0x802C60AC: lui         $a0, 0x800E
    ctx->r4 = S32(0X800E << 16);
    // 0x802C60B0: sw          $a2, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r6;
    // 0x802C60B4: sll         $t3, $t2, 2
    ctx->r11 = S32(ctx->r10 << 2);
    // 0x802C60B8: addu        $a0, $a0, $t3
    ctx->r4 = ADD32(ctx->r4, ctx->r11);
    // 0x802C60BC: jal         0x8007C9D4
    // 0x802C60C0: lw          $a0, -0x5528($a0)
    ctx->r4 = MEM_W(ctx->r4, -0X5528);
    func_8007C9D4(rdram, ctx);
        goto after_3;
    // 0x802C60C0: lw          $a0, -0x5528($a0)
    ctx->r4 = MEM_W(ctx->r4, -0X5528);
    after_3:
    // 0x802C60C4: lw          $a2, 0x1C($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X1C);
    // 0x802C60C8: addiu       $a3, $zero, 0x1
    ctx->r7 = ADD32(0, 0X1);
L_802C60CC:
    // 0x802C60CC: bne         $a2, $a3, L_802C60E8
    if (ctx->r6 != ctx->r7) {
        // 0x802C60D0: addiu       $at, $zero, 0x2
        ctx->r1 = ADD32(0, 0X2);
            goto L_802C60E8;
    }
    // 0x802C60D0: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x802C60D4: addiu       $a0, $zero, 0x11
    ctx->r4 = ADD32(0, 0X11);
    // 0x802C60D8: jal         0x800C37F4
    // 0x802C60DC: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_4;
    // 0x802C60DC: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_4:
    // 0x802C60E0: b           L_802C6454
    // 0x802C60E4: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_802C6454;
    // 0x802C60E4: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C60E8:
    // 0x802C60E8: bne         $a2, $at, L_802C6450
    if (ctx->r6 != ctx->r1) {
        // 0x802C60EC: addiu       $a0, $zero, 0x37
        ctx->r4 = ADD32(0, 0X37);
            goto L_802C6450;
    }
    // 0x802C60EC: addiu       $a0, $zero, 0x37
    ctx->r4 = ADD32(0, 0X37);
    // 0x802C60F0: jal         0x800C37F4
    // 0x802C60F4: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_5;
    // 0x802C60F4: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_5:
    // 0x802C60F8: b           L_802C6454
    // 0x802C60FC: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_802C6454;
    // 0x802C60FC: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C6100:
    // 0x802C6100: andi        $t4, $v0, 0x4000
    ctx->r12 = ctx->r2 & 0X4000;
    // 0x802C6104: beq         $t4, $zero, L_802C6180
    if (ctx->r12 == 0) {
        // 0x802C6108: andi        $t5, $v0, 0x800
        ctx->r13 = ctx->r2 & 0X800;
            goto L_802C6180;
    }
    // 0x802C6108: andi        $t5, $v0, 0x800
    ctx->r13 = ctx->r2 & 0X800;
    // 0x802C610C: lui         $a1, 0x801D
    ctx->r5 = S32(0X801D << 16);
    // 0x802C6110: addiu       $a1, $a1, -0x19C0
    ctx->r5 = ADD32(ctx->r5, -0X19C0);
    // 0x802C6114: lw          $v0, 0x0($a1)
    ctx->r2 = MEM_W(ctx->r5, 0X0);
    // 0x802C6118: addiu       $a3, $zero, 0x1
    ctx->r7 = ADD32(0, 0X1);
    // 0x802C611C: addiu       $a0, $zero, 0x3C
    ctx->r4 = ADD32(0, 0X3C);
    // 0x802C6120: beql        $v0, $zero, L_802C6144
    if (ctx->r2 == 0) {
        // 0x802C6124: addiu       $a2, $zero, 0x1
        ctx->r6 = ADD32(0, 0X1);
            goto L_802C6144;
    }
    goto skip_0;
    // 0x802C6124: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    skip_0:
    // 0x802C6128: beq         $v0, $a3, L_802C6154
    if (ctx->r2 == ctx->r7) {
        // 0x802C612C: addiu       $at, $zero, 0x2
        ctx->r1 = ADD32(0, 0X2);
            goto L_802C6154;
    }
    // 0x802C612C: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x802C6130: beql        $v0, $at, L_802C6164
    if (ctx->r2 == ctx->r1) {
        // 0x802C6134: or          $a2, $a3, $zero
        ctx->r6 = ctx->r7 | 0;
            goto L_802C6164;
    }
    goto skip_1;
    // 0x802C6134: or          $a2, $a3, $zero
    ctx->r6 = ctx->r7 | 0;
    skip_1:
    // 0x802C6138: b           L_802C6168
    // 0x802C613C: nop

        goto L_802C6168;
    // 0x802C613C: nop

    // 0x802C6140: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
L_802C6144:
    // 0x802C6144: jal         0x802C5EE4
    // 0x802C6148: sw          $a2, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r6;
    func_i12_802C5EE4(rdram, ctx);
        goto after_6;
    // 0x802C6148: sw          $a2, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r6;
    after_6:
    // 0x802C614C: b           L_802C6168
    // 0x802C6150: lw          $a2, 0x1C($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X1C);
        goto L_802C6168;
    // 0x802C6150: lw          $a2, 0x1C($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X1C);
L_802C6154:
    // 0x802C6154: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    // 0x802C6158: b           L_802C6168
    // 0x802C615C: sw          $zero, 0x0($a1)
    MEM_W(0X0, ctx->r5) = 0;
        goto L_802C6168;
    // 0x802C615C: sw          $zero, 0x0($a1)
    MEM_W(0X0, ctx->r5) = 0;
    // 0x802C6160: or          $a2, $a3, $zero
    ctx->r6 = ctx->r7 | 0;
L_802C6164:
    // 0x802C6164: sw          $a3, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r7;
L_802C6168:
    // 0x802C6168: beq         $a2, $zero, L_802C6450
    if (ctx->r6 == 0) {
        // 0x802C616C: addiu       $a0, $zero, 0x16
        ctx->r4 = ADD32(0, 0X16);
            goto L_802C6450;
    }
    // 0x802C616C: addiu       $a0, $zero, 0x16
    ctx->r4 = ADD32(0, 0X16);
    // 0x802C6170: jal         0x800C37F4
    // 0x802C6174: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_7;
    // 0x802C6174: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_7:
    // 0x802C6178: b           L_802C6454
    // 0x802C617C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_802C6454;
    // 0x802C617C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C6180:
    // 0x802C6180: beq         $t5, $zero, L_802C6200
    if (ctx->r13 == 0) {
        // 0x802C6184: andi        $t4, $v0, 0x400
        ctx->r12 = ctx->r2 & 0X400;
            goto L_802C6200;
    }
    // 0x802C6184: andi        $t4, $v0, 0x400
    ctx->r12 = ctx->r2 & 0X400;
    // 0x802C6188: lui         $a1, 0x801D
    ctx->r5 = S32(0X801D << 16);
    // 0x802C618C: addiu       $a1, $a1, -0x19C0
    ctx->r5 = ADD32(ctx->r5, -0X19C0);
    // 0x802C6190: lw          $t6, 0x0($a1)
    ctx->r14 = MEM_W(ctx->r5, 0X0);
    // 0x802C6194: addiu       $a3, $zero, 0x1
    ctx->r7 = ADD32(0, 0X1);
    // 0x802C6198: lui         $v1, 0x802C
    ctx->r3 = S32(0X802C << 16);
    // 0x802C619C: bne         $a3, $t6, L_802C61E8
    if (ctx->r7 != ctx->r14) {
        // 0x802C61A0: addiu       $v1, $v1, 0x6464
        ctx->r3 = ADD32(ctx->r3, 0X6464);
            goto L_802C61E8;
    }
    // 0x802C61A0: addiu       $v1, $v1, 0x6464
    ctx->r3 = ADD32(ctx->r3, 0X6464);
    // 0x802C61A4: lui         $a0, 0x802C
    ctx->r4 = S32(0X802C << 16);
    // 0x802C61A8: lw          $t7, 0x0($v1)
    ctx->r15 = MEM_W(ctx->r3, 0X0);
    // 0x802C61AC: addiu       $a0, $a0, 0x6460
    ctx->r4 = ADD32(ctx->r4, 0X6460);
    // 0x802C61B0: lw          $t9, 0x0($a0)
    ctx->r25 = MEM_W(ctx->r4, 0X0);
    // 0x802C61B4: addiu       $t8, $t7, -0x1
    ctx->r24 = ADD32(ctx->r15, -0X1);
    // 0x802C61B8: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    // 0x802C61BC: bne         $t9, $zero, L_802C61D4
    if (ctx->r25 != 0) {
        // 0x802C61C0: sw          $t8, 0x0($v1)
        MEM_W(0X0, ctx->r3) = ctx->r24;
            goto L_802C61D4;
    }
    // 0x802C61C0: sw          $t8, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r24;
    // 0x802C61C4: bgtz        $t8, L_802C61E8
    if (SIGNED(ctx->r24) > 0) {
        // 0x802C61C8: addiu       $t1, $zero, 0x8
        ctx->r9 = ADD32(0, 0X8);
            goto L_802C61E8;
    }
    // 0x802C61C8: addiu       $t1, $zero, 0x8
    ctx->r9 = ADD32(0, 0X8);
    // 0x802C61CC: b           L_802C61E8
    // 0x802C61D0: sw          $t1, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r9;
        goto L_802C61E8;
    // 0x802C61D0: sw          $t1, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r9;
L_802C61D4:
    // 0x802C61D4: lw          $t2, 0x0($v1)
    ctx->r10 = MEM_W(ctx->r3, 0X0);
    // 0x802C61D8: addiu       $t3, $zero, 0x8
    ctx->r11 = ADD32(0, 0X8);
    // 0x802C61DC: bgez        $t2, L_802C61E8
    if (SIGNED(ctx->r10) >= 0) {
        // 0x802C61E0: nop
    
            goto L_802C61E8;
    }
    // 0x802C61E0: nop

    // 0x802C61E4: sw          $t3, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r11;
L_802C61E8:
    // 0x802C61E8: beq         $a2, $zero, L_802C6450
    if (ctx->r6 == 0) {
        // 0x802C61EC: addiu       $a0, $zero, 0x10
        ctx->r4 = ADD32(0, 0X10);
            goto L_802C6450;
    }
    // 0x802C61EC: addiu       $a0, $zero, 0x10
    ctx->r4 = ADD32(0, 0X10);
    // 0x802C61F0: jal         0x800C37F4
    // 0x802C61F4: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_8;
    // 0x802C61F4: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_8:
    // 0x802C61F8: b           L_802C6454
    // 0x802C61FC: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_802C6454;
    // 0x802C61FC: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C6200:
    // 0x802C6200: beq         $t4, $zero, L_802C6284
    if (ctx->r12 == 0) {
        // 0x802C6204: andi        $t1, $v0, 0x200
        ctx->r9 = ctx->r2 & 0X200;
            goto L_802C6284;
    }
    // 0x802C6204: andi        $t1, $v0, 0x200
    ctx->r9 = ctx->r2 & 0X200;
    // 0x802C6208: lui         $a1, 0x801D
    ctx->r5 = S32(0X801D << 16);
    // 0x802C620C: addiu       $a1, $a1, -0x19C0
    ctx->r5 = ADD32(ctx->r5, -0X19C0);
    // 0x802C6210: lw          $t5, 0x0($a1)
    ctx->r13 = MEM_W(ctx->r5, 0X0);
    // 0x802C6214: addiu       $a3, $zero, 0x1
    ctx->r7 = ADD32(0, 0X1);
    // 0x802C6218: lui         $v1, 0x802C
    ctx->r3 = S32(0X802C << 16);
    // 0x802C621C: bne         $a3, $t5, L_802C626C
    if (ctx->r7 != ctx->r13) {
        // 0x802C6220: addiu       $v1, $v1, 0x6464
        ctx->r3 = ADD32(ctx->r3, 0X6464);
            goto L_802C626C;
    }
    // 0x802C6220: addiu       $v1, $v1, 0x6464
    ctx->r3 = ADD32(ctx->r3, 0X6464);
    // 0x802C6224: lui         $a0, 0x802C
    ctx->r4 = S32(0X802C << 16);
    // 0x802C6228: lw          $t6, 0x0($v1)
    ctx->r14 = MEM_W(ctx->r3, 0X0);
    // 0x802C622C: addiu       $a0, $a0, 0x6460
    ctx->r4 = ADD32(ctx->r4, 0X6460);
    // 0x802C6230: lw          $t8, 0x0($a0)
    ctx->r24 = MEM_W(ctx->r4, 0X0);
    // 0x802C6234: addiu       $t7, $t6, 0x1
    ctx->r15 = ADD32(ctx->r14, 0X1);
    // 0x802C6238: or          $a2, $a3, $zero
    ctx->r6 = ctx->r7 | 0;
    // 0x802C623C: bne         $t8, $zero, L_802C6258
    if (ctx->r24 != 0) {
        // 0x802C6240: sw          $t7, 0x0($v1)
        MEM_W(0X0, ctx->r3) = ctx->r15;
            goto L_802C6258;
    }
    // 0x802C6240: sw          $t7, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r15;
    // 0x802C6244: slti        $at, $t7, 0x9
    ctx->r1 = SIGNED(ctx->r15) < 0X9 ? 1 : 0;
    // 0x802C6248: bne         $at, $zero, L_802C626C
    if (ctx->r1 != 0) {
        // 0x802C624C: nop
    
            goto L_802C626C;
    }
    // 0x802C624C: nop

    // 0x802C6250: b           L_802C626C
    // 0x802C6254: sw          $a3, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r7;
        goto L_802C626C;
    // 0x802C6254: sw          $a3, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r7;
L_802C6258:
    // 0x802C6258: lw          $t0, 0x0($v1)
    ctx->r8 = MEM_W(ctx->r3, 0X0);
    // 0x802C625C: slti        $at, $t0, 0x9
    ctx->r1 = SIGNED(ctx->r8) < 0X9 ? 1 : 0;
    // 0x802C6260: bne         $at, $zero, L_802C626C
    if (ctx->r1 != 0) {
        // 0x802C6264: nop
    
            goto L_802C626C;
    }
    // 0x802C6264: nop

    // 0x802C6268: sw          $zero, 0x0($v1)
    MEM_W(0X0, ctx->r3) = 0;
L_802C626C:
    // 0x802C626C: beq         $a2, $zero, L_802C6450
    if (ctx->r6 == 0) {
        // 0x802C6270: addiu       $a0, $zero, 0x10
        ctx->r4 = ADD32(0, 0X10);
            goto L_802C6450;
    }
    // 0x802C6270: addiu       $a0, $zero, 0x10
    ctx->r4 = ADD32(0, 0X10);
    // 0x802C6274: jal         0x800C37F4
    // 0x802C6278: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_9;
    // 0x802C6278: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_9:
    // 0x802C627C: b           L_802C6454
    // 0x802C6280: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_802C6454;
    // 0x802C6280: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C6284:
    // 0x802C6284: beq         $t1, $zero, L_802C636C
    if (ctx->r9 == 0) {
        // 0x802C6288: andi        $t3, $v0, 0x100
        ctx->r11 = ctx->r2 & 0X100;
            goto L_802C636C;
    }
    // 0x802C6288: andi        $t3, $v0, 0x100
    ctx->r11 = ctx->r2 & 0X100;
    // 0x802C628C: lui         $a1, 0x801D
    ctx->r5 = S32(0X801D << 16);
    // 0x802C6290: addiu       $a1, $a1, -0x19C0
    ctx->r5 = ADD32(ctx->r5, -0X19C0);
    // 0x802C6294: lw          $v0, 0x0($a1)
    ctx->r2 = MEM_W(ctx->r5, 0X0);
    // 0x802C6298: lui         $a0, 0x802C
    ctx->r4 = S32(0X802C << 16);
    // 0x802C629C: addiu       $a0, $a0, 0x6460
    ctx->r4 = ADD32(ctx->r4, 0X6460);
    // 0x802C62A0: beq         $v0, $zero, L_802C62C4
    if (ctx->r2 == 0) {
        // 0x802C62A4: addiu       $a3, $zero, 0x1
        ctx->r7 = ADD32(0, 0X1);
            goto L_802C62C4;
    }
    // 0x802C62A4: addiu       $a3, $zero, 0x1
    ctx->r7 = ADD32(0, 0X1);
    // 0x802C62A8: beq         $v0, $a3, L_802C62E4
    if (ctx->r2 == ctx->r7) {
        // 0x802C62AC: lui         $a0, 0x802C
        ctx->r4 = S32(0X802C << 16);
            goto L_802C62E4;
    }
    // 0x802C62AC: lui         $a0, 0x802C
    ctx->r4 = S32(0X802C << 16);
    // 0x802C62B0: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x802C62B4: beq         $v0, $at, L_802C6334
    if (ctx->r2 == ctx->r1) {
        // 0x802C62B8: nop
    
            goto L_802C6334;
    }
    // 0x802C62B8: nop

    // 0x802C62BC: b           L_802C6354
    // 0x802C62C0: nop

        goto L_802C6354;
    // 0x802C62C0: nop

L_802C62C4:
    // 0x802C62C4: lw          $t2, 0x0($a0)
    ctx->r10 = MEM_W(ctx->r4, 0X0);
    // 0x802C62C8: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    // 0x802C62CC: addiu       $t5, $zero, 0x2
    ctx->r13 = ADD32(0, 0X2);
    // 0x802C62D0: addiu       $t3, $t2, -0x1
    ctx->r11 = ADD32(ctx->r10, -0X1);
    // 0x802C62D4: bgez        $t3, L_802C6354
    if (SIGNED(ctx->r11) >= 0) {
        // 0x802C62D8: sw          $t3, 0x0($a0)
        MEM_W(0X0, ctx->r4) = ctx->r11;
            goto L_802C6354;
    }
    // 0x802C62D8: sw          $t3, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r11;
    // 0x802C62DC: b           L_802C6354
    // 0x802C62E0: sw          $t5, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r13;
        goto L_802C6354;
    // 0x802C62E0: sw          $t5, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r13;
L_802C62E4:
    // 0x802C62E4: addiu       $a0, $a0, 0x6460
    ctx->r4 = ADD32(ctx->r4, 0X6460);
    // 0x802C62E8: lw          $t6, 0x0($a0)
    ctx->r14 = MEM_W(ctx->r4, 0X0);
    // 0x802C62EC: lui         $v1, 0x802C
    ctx->r3 = S32(0X802C << 16);
    // 0x802C62F0: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    // 0x802C62F4: bne         $t6, $zero, L_802C6308
    if (ctx->r14 != 0) {
        // 0x802C62F8: addiu       $v1, $v1, 0x6464
        ctx->r3 = ADD32(ctx->r3, 0X6464);
            goto L_802C6308;
    }
    // 0x802C62F8: addiu       $v1, $v1, 0x6464
    ctx->r3 = ADD32(ctx->r3, 0X6464);
    // 0x802C62FC: lw          $t7, 0x0($v1)
    ctx->r15 = MEM_W(ctx->r3, 0X0);
    // 0x802C6300: addiu       $at, $zero, 0x5
    ctx->r1 = ADD32(0, 0X5);
    // 0x802C6304: beq         $t7, $at, L_802C6354
    if (ctx->r15 == ctx->r1) {
        // 0x802C6308: lui         $v1, 0x802C
        ctx->r3 = S32(0X802C << 16);
            goto L_802C6354;
    }
L_802C6308:
    // 0x802C6308: lui         $v1, 0x802C
    ctx->r3 = S32(0X802C << 16);
    // 0x802C630C: addiu       $v1, $v1, 0x6464
    ctx->r3 = ADD32(ctx->r3, 0X6464);
    // 0x802C6310: lw          $v0, 0x0($v1)
    ctx->r2 = MEM_W(ctx->r3, 0X0);
    // 0x802C6314: addiu       $at, $zero, 0x4
    ctx->r1 = ADD32(0, 0X4);
    // 0x802C6318: beq         $v0, $at, L_802C6354
    if (ctx->r2 == ctx->r1) {
        // 0x802C631C: addiu       $t8, $v0, -0x5
        ctx->r24 = ADD32(ctx->r2, -0X5);
            goto L_802C6354;
    }
    // 0x802C631C: addiu       $t8, $v0, -0x5
    ctx->r24 = ADD32(ctx->r2, -0X5);
    // 0x802C6320: bgez        $t8, L_802C6354
    if (SIGNED(ctx->r24) >= 0) {
        // 0x802C6324: sw          $t8, 0x0($v1)
        MEM_W(0X0, ctx->r3) = ctx->r24;
            goto L_802C6354;
    }
    // 0x802C6324: sw          $t8, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r24;
    // 0x802C6328: addiu       $t9, $t8, 0xA
    ctx->r25 = ADD32(ctx->r24, 0XA);
    // 0x802C632C: b           L_802C6354
    // 0x802C6330: sw          $t9, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r25;
        goto L_802C6354;
    // 0x802C6330: sw          $t9, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r25;
L_802C6334:
    // 0x802C6334: lui         $v0, 0x802C
    ctx->r2 = S32(0X802C << 16);
    // 0x802C6338: addiu       $v0, $v0, 0x6468
    ctx->r2 = ADD32(ctx->r2, 0X6468);
    // 0x802C633C: lw          $t0, 0x0($v0)
    ctx->r8 = MEM_W(ctx->r2, 0X0);
    // 0x802C6340: or          $a2, $a3, $zero
    ctx->r6 = ctx->r7 | 0;
    // 0x802C6344: addiu       $t1, $t0, -0x1
    ctx->r9 = ADD32(ctx->r8, -0X1);
    // 0x802C6348: bgez        $t1, L_802C6354
    if (SIGNED(ctx->r9) >= 0) {
        // 0x802C634C: sw          $t1, 0x0($v0)
        MEM_W(0X0, ctx->r2) = ctx->r9;
            goto L_802C6354;
    }
    // 0x802C634C: sw          $t1, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r9;
    // 0x802C6350: sw          $a3, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r7;
L_802C6354:
    // 0x802C6354: beq         $a2, $zero, L_802C6450
    if (ctx->r6 == 0) {
        // 0x802C6358: addiu       $a0, $zero, 0x10
        ctx->r4 = ADD32(0, 0X10);
            goto L_802C6450;
    }
    // 0x802C6358: addiu       $a0, $zero, 0x10
    ctx->r4 = ADD32(0, 0X10);
    // 0x802C635C: jal         0x800C37F4
    // 0x802C6360: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_10;
    // 0x802C6360: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_10:
    // 0x802C6364: b           L_802C6454
    // 0x802C6368: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_802C6454;
    // 0x802C6368: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C636C:
    // 0x802C636C: beq         $t3, $zero, L_802C6450
    if (ctx->r11 == 0) {
        // 0x802C6370: lui         $a1, 0x801D
        ctx->r5 = S32(0X801D << 16);
            goto L_802C6450;
    }
    // 0x802C6370: lui         $a1, 0x801D
    ctx->r5 = S32(0X801D << 16);
    // 0x802C6374: addiu       $a1, $a1, -0x19C0
    ctx->r5 = ADD32(ctx->r5, -0X19C0);
    // 0x802C6378: lw          $v0, 0x0($a1)
    ctx->r2 = MEM_W(ctx->r5, 0X0);
    // 0x802C637C: lui         $a0, 0x802C
    ctx->r4 = S32(0X802C << 16);
    // 0x802C6380: addiu       $a0, $a0, 0x6460
    ctx->r4 = ADD32(ctx->r4, 0X6460);
    // 0x802C6384: beq         $v0, $zero, L_802C63A8
    if (ctx->r2 == 0) {
        // 0x802C6388: addiu       $a3, $zero, 0x1
        ctx->r7 = ADD32(0, 0X1);
            goto L_802C63A8;
    }
    // 0x802C6388: addiu       $a3, $zero, 0x1
    ctx->r7 = ADD32(0, 0X1);
    // 0x802C638C: beq         $v0, $a3, L_802C63C8
    if (ctx->r2 == ctx->r7) {
        // 0x802C6390: lui         $a0, 0x802C
        ctx->r4 = S32(0X802C << 16);
            goto L_802C63C8;
    }
    // 0x802C6390: lui         $a0, 0x802C
    ctx->r4 = S32(0X802C << 16);
    // 0x802C6394: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x802C6398: beq         $v0, $at, L_802C641C
    if (ctx->r2 == ctx->r1) {
        // 0x802C639C: nop
    
            goto L_802C641C;
    }
    // 0x802C639C: nop

    // 0x802C63A0: b           L_802C6440
    // 0x802C63A4: nop

        goto L_802C6440;
    // 0x802C63A4: nop

L_802C63A8:
    // 0x802C63A8: lw          $t4, 0x0($a0)
    ctx->r12 = MEM_W(ctx->r4, 0X0);
    // 0x802C63AC: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x802C63B0: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    // 0x802C63B4: addiu       $t5, $t4, 0x1
    ctx->r13 = ADD32(ctx->r12, 0X1);
    // 0x802C63B8: bne         $t5, $at, L_802C6440
    if (ctx->r13 != ctx->r1) {
        // 0x802C63BC: sw          $t5, 0x0($a0)
        MEM_W(0X0, ctx->r4) = ctx->r13;
            goto L_802C6440;
    }
    // 0x802C63BC: sw          $t5, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r13;
    // 0x802C63C0: b           L_802C6440
    // 0x802C63C4: sw          $zero, 0x0($a0)
    MEM_W(0X0, ctx->r4) = 0;
        goto L_802C6440;
    // 0x802C63C4: sw          $zero, 0x0($a0)
    MEM_W(0X0, ctx->r4) = 0;
L_802C63C8:
    // 0x802C63C8: addiu       $a0, $a0, 0x6460
    ctx->r4 = ADD32(ctx->r4, 0X6460);
    // 0x802C63CC: lw          $t7, 0x0($a0)
    ctx->r15 = MEM_W(ctx->r4, 0X0);
    // 0x802C63D0: lui         $v1, 0x802C
    ctx->r3 = S32(0X802C << 16);
    // 0x802C63D4: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    // 0x802C63D8: bne         $t7, $zero, L_802C63EC
    if (ctx->r15 != 0) {
        // 0x802C63DC: addiu       $v1, $v1, 0x6464
        ctx->r3 = ADD32(ctx->r3, 0X6464);
            goto L_802C63EC;
    }
    // 0x802C63DC: addiu       $v1, $v1, 0x6464
    ctx->r3 = ADD32(ctx->r3, 0X6464);
    // 0x802C63E0: lw          $t8, 0x0($v1)
    ctx->r24 = MEM_W(ctx->r3, 0X0);
    // 0x802C63E4: addiu       $at, $zero, 0x5
    ctx->r1 = ADD32(0, 0X5);
    // 0x802C63E8: beq         $t8, $at, L_802C6440
    if (ctx->r24 == ctx->r1) {
        // 0x802C63EC: lui         $v1, 0x802C
        ctx->r3 = S32(0X802C << 16);
            goto L_802C6440;
    }
L_802C63EC:
    // 0x802C63EC: lui         $v1, 0x802C
    ctx->r3 = S32(0X802C << 16);
    // 0x802C63F0: addiu       $v1, $v1, 0x6464
    ctx->r3 = ADD32(ctx->r3, 0X6464);
    // 0x802C63F4: lw          $v0, 0x0($v1)
    ctx->r2 = MEM_W(ctx->r3, 0X0);
    // 0x802C63F8: addiu       $at, $zero, 0x4
    ctx->r1 = ADD32(0, 0X4);
    // 0x802C63FC: beq         $v0, $at, L_802C6440
    if (ctx->r2 == ctx->r1) {
        // 0x802C6400: addiu       $t9, $v0, 0x5
        ctx->r25 = ADD32(ctx->r2, 0X5);
            goto L_802C6440;
    }
    // 0x802C6400: addiu       $t9, $v0, 0x5
    ctx->r25 = ADD32(ctx->r2, 0X5);
    // 0x802C6404: slti        $at, $t9, 0x9
    ctx->r1 = SIGNED(ctx->r25) < 0X9 ? 1 : 0;
    // 0x802C6408: bne         $at, $zero, L_802C6440
    if (ctx->r1 != 0) {
        // 0x802C640C: sw          $t9, 0x0($v1)
        MEM_W(0X0, ctx->r3) = ctx->r25;
            goto L_802C6440;
    }
    // 0x802C640C: sw          $t9, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r25;
    // 0x802C6410: addiu       $t0, $t9, -0xA
    ctx->r8 = ADD32(ctx->r25, -0XA);
    // 0x802C6414: b           L_802C6440
    // 0x802C6418: sw          $t0, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r8;
        goto L_802C6440;
    // 0x802C6418: sw          $t0, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r8;
L_802C641C:
    // 0x802C641C: lui         $v0, 0x802C
    ctx->r2 = S32(0X802C << 16);
    // 0x802C6420: addiu       $v0, $v0, 0x6468
    ctx->r2 = ADD32(ctx->r2, 0X6468);
    // 0x802C6424: lw          $t1, 0x0($v0)
    ctx->r9 = MEM_W(ctx->r2, 0X0);
    // 0x802C6428: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    // 0x802C642C: addiu       $t2, $t1, 0x1
    ctx->r10 = ADD32(ctx->r9, 0X1);
    // 0x802C6430: slti        $at, $t2, 0x2
    ctx->r1 = SIGNED(ctx->r10) < 0X2 ? 1 : 0;
    // 0x802C6434: bne         $at, $zero, L_802C6440
    if (ctx->r1 != 0) {
        // 0x802C6438: sw          $t2, 0x0($v0)
        MEM_W(0X0, ctx->r2) = ctx->r10;
            goto L_802C6440;
    }
    // 0x802C6438: sw          $t2, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r10;
    // 0x802C643C: sw          $zero, 0x0($v0)
    MEM_W(0X0, ctx->r2) = 0;
L_802C6440:
    // 0x802C6440: beq         $a2, $zero, L_802C6450
    if (ctx->r6 == 0) {
        // 0x802C6444: addiu       $a0, $zero, 0x10
        ctx->r4 = ADD32(0, 0X10);
            goto L_802C6450;
    }
    // 0x802C6444: addiu       $a0, $zero, 0x10
    ctx->r4 = ADD32(0, 0X10);
    // 0x802C6448: jal         0x800C37F4
    // 0x802C644C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_11;
    // 0x802C644C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_11:
L_802C6450:
    // 0x802C6450: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C6454:
    // 0x802C6454: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x802C6458: jr          $ra
    // 0x802C645C: nop

    return;
    // 0x802C645C: nop

;}
RECOMP_FUNC void func_i13_802C5800(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C5800: addiu       $sp, $sp, -0x1D8
    ctx->r29 = ADD32(ctx->r29, -0X1D8);
    // 0x802C5804: lui         $a1, 0x802D
    ctx->r5 = S32(0X802D << 16);
    // 0x802C5808: addiu       $a1, $a1, -0x7278
    ctx->r5 = ADD32(ctx->r5, -0X7278);
    // 0x802C580C: lw          $v1, 0x0($a1)
    ctx->r3 = MEM_W(ctx->r5, 0X0);
    // 0x802C5810: sw          $ra, 0x74($sp)
    MEM_W(0X74, ctx->r29) = ctx->r31;
    // 0x802C5814: sw          $fp, 0x70($sp)
    MEM_W(0X70, ctx->r29) = ctx->r30;
    // 0x802C5818: sw          $s7, 0x6C($sp)
    MEM_W(0X6C, ctx->r29) = ctx->r23;
    // 0x802C581C: sw          $s6, 0x68($sp)
    MEM_W(0X68, ctx->r29) = ctx->r22;
    // 0x802C5820: sw          $s5, 0x64($sp)
    MEM_W(0X64, ctx->r29) = ctx->r21;
    // 0x802C5824: sw          $s4, 0x60($sp)
    MEM_W(0X60, ctx->r29) = ctx->r20;
    // 0x802C5828: sw          $s3, 0x5C($sp)
    MEM_W(0X5C, ctx->r29) = ctx->r19;
    // 0x802C582C: sw          $s2, 0x58($sp)
    MEM_W(0X58, ctx->r29) = ctx->r18;
    // 0x802C5830: sw          $s1, 0x54($sp)
    MEM_W(0X54, ctx->r29) = ctx->r17;
    // 0x802C5834: sw          $s0, 0x50($sp)
    MEM_W(0X50, ctx->r29) = ctx->r16;
    // 0x802C5838: sdc1        $f24, 0x48($sp)
    CHECK_FR(ctx, 24);
    SD(ctx->f24.u64, 0X48, ctx->r29);
    // 0x802C583C: sdc1        $f22, 0x40($sp)
    CHECK_FR(ctx, 22);
    SD(ctx->f22.u64, 0X40, ctx->r29);
    // 0x802C5840: bne         $v1, $zero, L_802C5904
    if (ctx->r3 != 0) {
        // 0x802C5844: sdc1        $f20, 0x38($sp)
        CHECK_FR(ctx, 20);
    SD(ctx->f20.u64, 0X38, ctx->r29);
            goto L_802C5904;
    }
    // 0x802C5844: sdc1        $f20, 0x38($sp)
    CHECK_FR(ctx, 20);
    SD(ctx->f20.u64, 0X38, ctx->r29);
    // 0x802C5848: lui         $a0, 0x802D
    ctx->r4 = S32(0X802D << 16);
    // 0x802C584C: addiu       $a0, $a0, -0x7274
    ctx->r4 = ADD32(ctx->r4, -0X7274);
    // 0x802C5850: lw          $v0, 0x0($a0)
    ctx->r2 = MEM_W(ctx->r4, 0X0);
    // 0x802C5854: lui         $at, 0x437F
    ctx->r1 = S32(0X437F << 16);
    // 0x802C5858: mtc1        $at, $f0
    ctx->f0.u32l = ctx->r1;
    // 0x802C585C: mtc1        $v0, $f4
    ctx->f4.u32l = ctx->r2;
    // 0x802C5860: lui         $at, 0x4080
    ctx->r1 = S32(0X4080 << 16);
    // 0x802C5864: mtc1        $at, $f2
    ctx->f2.u32l = ctx->r1;
    // 0x802C5868: cvt.s.w     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
    // 0x802C586C: addiu       $t7, $zero, 0x1
    ctx->r15 = ADD32(0, 0X1);
    // 0x802C5870: lui         $at, 0x4F00
    ctx->r1 = S32(0X4F00 << 16);
    // 0x802C5874: mul.s       $f8, $f6, $f0
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f8.fl = MUL_S(ctx->f6.fl, ctx->f0.fl);
    // 0x802C5878: div.s       $f10, $f8, $f2
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f10.fl = DIV_S(ctx->f8.fl, ctx->f2.fl);
    // 0x802C587C: cfc1        $t6, $FpcCsr
    ctx->r14 = get_cop1_cs();
    // 0x802C5880: ctc1        $t7, $FpcCsr
    set_cop1_cs(ctx->r15);
    // 0x802C5884: nop

    // 0x802C5888: cvt.w.s     $f16, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    ctx->f16.u32l = CVT_W_S(ctx->f10.fl);
    // 0x802C588C: cfc1        $t7, $FpcCsr
    ctx->r15 = get_cop1_cs();
    // 0x802C5890: nop

    // 0x802C5894: andi        $t7, $t7, 0x78
    ctx->r15 = ctx->r15 & 0X78;
    // 0x802C5898: beql        $t7, $zero, L_802C58E8
    if (ctx->r15 == 0) {
        // 0x802C589C: mfc1        $t7, $f16
        ctx->r15 = (int32_t)ctx->f16.u32l;
            goto L_802C58E8;
    }
    goto skip_0;
    // 0x802C589C: mfc1        $t7, $f16
    ctx->r15 = (int32_t)ctx->f16.u32l;
    skip_0:
    // 0x802C58A0: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
    // 0x802C58A4: addiu       $t7, $zero, 0x1
    ctx->r15 = ADD32(0, 0X1);
    // 0x802C58A8: sub.s       $f16, $f10, $f16
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f16.fl = ctx->f10.fl - ctx->f16.fl;
    // 0x802C58AC: ctc1        $t7, $FpcCsr
    set_cop1_cs(ctx->r15);
    // 0x802C58B0: nop

    // 0x802C58B4: cvt.w.s     $f16, $f16
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 16);
    ctx->f16.u32l = CVT_W_S(ctx->f16.fl);
    // 0x802C58B8: cfc1        $t7, $FpcCsr
    ctx->r15 = get_cop1_cs();
    // 0x802C58BC: nop

    // 0x802C58C0: andi        $t7, $t7, 0x78
    ctx->r15 = ctx->r15 & 0X78;
    // 0x802C58C4: bne         $t7, $zero, L_802C58DC
    if (ctx->r15 != 0) {
        // 0x802C58C8: nop
    
            goto L_802C58DC;
    }
    // 0x802C58C8: nop

    // 0x802C58CC: mfc1        $t7, $f16
    ctx->r15 = (int32_t)ctx->f16.u32l;
    // 0x802C58D0: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x802C58D4: b           L_802C58F4
    // 0x802C58D8: or          $t7, $t7, $at
    ctx->r15 = ctx->r15 | ctx->r1;
        goto L_802C58F4;
    // 0x802C58D8: or          $t7, $t7, $at
    ctx->r15 = ctx->r15 | ctx->r1;
L_802C58DC:
    // 0x802C58DC: b           L_802C58F4
    // 0x802C58E0: addiu       $t7, $zero, -0x1
    ctx->r15 = ADD32(0, -0X1);
        goto L_802C58F4;
    // 0x802C58E0: addiu       $t7, $zero, -0x1
    ctx->r15 = ADD32(0, -0X1);
    // 0x802C58E4: mfc1        $t7, $f16
    ctx->r15 = (int32_t)ctx->f16.u32l;
L_802C58E8:
    // 0x802C58E8: nop

    // 0x802C58EC: bltz        $t7, L_802C58DC
    if (SIGNED(ctx->r15) < 0) {
        // 0x802C58F0: nop
    
            goto L_802C58DC;
    }
    // 0x802C58F0: nop

L_802C58F4:
    // 0x802C58F4: ctc1        $t6, $FpcCsr
    set_cop1_cs(ctx->r14);
    // 0x802C58F8: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C58FC: b           L_802C59C0
    // 0x802C5900: sw          $t7, -0x7160($at)
    MEM_W(-0X7160, ctx->r1) = ctx->r15;
        goto L_802C59C0;
    // 0x802C5900: sw          $t7, -0x7160($at)
    MEM_W(-0X7160, ctx->r1) = ctx->r15;
L_802C5904:
    // 0x802C5904: lui         $a0, 0x802D
    ctx->r4 = S32(0X802D << 16);
    // 0x802C5908: addiu       $a0, $a0, -0x7274
    ctx->r4 = ADD32(ctx->r4, -0X7274);
    // 0x802C590C: lw          $v0, 0x0($a0)
    ctx->r2 = MEM_W(ctx->r4, 0X0);
    // 0x802C5910: lui         $at, 0x437F
    ctx->r1 = S32(0X437F << 16);
    // 0x802C5914: mtc1        $at, $f0
    ctx->f0.u32l = ctx->r1;
    // 0x802C5918: mtc1        $v0, $f18
    ctx->f18.u32l = ctx->r2;
    // 0x802C591C: lui         $at, 0x4080
    ctx->r1 = S32(0X4080 << 16);
    // 0x802C5920: mtc1        $at, $f2
    ctx->f2.u32l = ctx->r1;
    // 0x802C5924: cvt.s.w     $f4, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    ctx->f4.fl = CVT_S_W(ctx->f18.u32l);
    // 0x802C5928: addiu       $t9, $zero, 0x1
    ctx->r25 = ADD32(0, 0X1);
    // 0x802C592C: lui         $at, 0x4F00
    ctx->r1 = S32(0X4F00 << 16);
    // 0x802C5930: sub.s       $f6, $f2, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = ctx->f2.fl - ctx->f4.fl;
    // 0x802C5934: mul.s       $f8, $f6, $f0
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f8.fl = MUL_S(ctx->f6.fl, ctx->f0.fl);
    // 0x802C5938: div.s       $f10, $f8, $f2
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f10.fl = DIV_S(ctx->f8.fl, ctx->f2.fl);
    // 0x802C593C: cfc1        $t8, $FpcCsr
    ctx->r24 = get_cop1_cs();
    // 0x802C5940: ctc1        $t9, $FpcCsr
    set_cop1_cs(ctx->r25);
    // 0x802C5944: nop

    // 0x802C5948: cvt.w.s     $f16, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    ctx->f16.u32l = CVT_W_S(ctx->f10.fl);
    // 0x802C594C: cfc1        $t9, $FpcCsr
    ctx->r25 = get_cop1_cs();
    // 0x802C5950: nop

    // 0x802C5954: andi        $t9, $t9, 0x78
    ctx->r25 = ctx->r25 & 0X78;
    // 0x802C5958: beql        $t9, $zero, L_802C59A8
    if (ctx->r25 == 0) {
        // 0x802C595C: mfc1        $t9, $f16
        ctx->r25 = (int32_t)ctx->f16.u32l;
            goto L_802C59A8;
    }
    goto skip_1;
    // 0x802C595C: mfc1        $t9, $f16
    ctx->r25 = (int32_t)ctx->f16.u32l;
    skip_1:
    // 0x802C5960: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
    // 0x802C5964: addiu       $t9, $zero, 0x1
    ctx->r25 = ADD32(0, 0X1);
    // 0x802C5968: sub.s       $f16, $f10, $f16
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f16.fl = ctx->f10.fl - ctx->f16.fl;
    // 0x802C596C: ctc1        $t9, $FpcCsr
    set_cop1_cs(ctx->r25);
    // 0x802C5970: nop

    // 0x802C5974: cvt.w.s     $f16, $f16
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 16);
    ctx->f16.u32l = CVT_W_S(ctx->f16.fl);
    // 0x802C5978: cfc1        $t9, $FpcCsr
    ctx->r25 = get_cop1_cs();
    // 0x802C597C: nop

    // 0x802C5980: andi        $t9, $t9, 0x78
    ctx->r25 = ctx->r25 & 0X78;
    // 0x802C5984: bne         $t9, $zero, L_802C599C
    if (ctx->r25 != 0) {
        // 0x802C5988: nop
    
            goto L_802C599C;
    }
    // 0x802C5988: nop

    // 0x802C598C: mfc1        $t9, $f16
    ctx->r25 = (int32_t)ctx->f16.u32l;
    // 0x802C5990: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x802C5994: b           L_802C59B4
    // 0x802C5998: or          $t9, $t9, $at
    ctx->r25 = ctx->r25 | ctx->r1;
        goto L_802C59B4;
    // 0x802C5998: or          $t9, $t9, $at
    ctx->r25 = ctx->r25 | ctx->r1;
L_802C599C:
    // 0x802C599C: b           L_802C59B4
    // 0x802C59A0: addiu       $t9, $zero, -0x1
    ctx->r25 = ADD32(0, -0X1);
        goto L_802C59B4;
    // 0x802C59A0: addiu       $t9, $zero, -0x1
    ctx->r25 = ADD32(0, -0X1);
    // 0x802C59A4: mfc1        $t9, $f16
    ctx->r25 = (int32_t)ctx->f16.u32l;
L_802C59A8:
    // 0x802C59A8: nop

    // 0x802C59AC: bltz        $t9, L_802C599C
    if (SIGNED(ctx->r25) < 0) {
        // 0x802C59B0: nop
    
            goto L_802C599C;
    }
    // 0x802C59B0: nop

L_802C59B4:
    // 0x802C59B4: ctc1        $t8, $FpcCsr
    set_cop1_cs(ctx->r24);
    // 0x802C59B8: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C59BC: sw          $t9, -0x7160($at)
    MEM_W(-0X7160, ctx->r1) = ctx->r25;
L_802C59C0:
    // 0x802C59C0: addiu       $t0, $v0, 0x1
    ctx->r8 = ADD32(ctx->r2, 0X1);
    // 0x802C59C4: slti        $at, $t0, 0x4
    ctx->r1 = SIGNED(ctx->r8) < 0X4 ? 1 : 0;
    // 0x802C59C8: bne         $at, $zero, L_802C59DC
    if (ctx->r1 != 0) {
        // 0x802C59CC: sw          $t0, 0x0($a0)
        MEM_W(0X0, ctx->r4) = ctx->r8;
            goto L_802C59DC;
    }
    // 0x802C59CC: sw          $t0, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r8;
    // 0x802C59D0: xori        $t2, $v1, 0x1
    ctx->r10 = ctx->r3 ^ 0X1;
    // 0x802C59D4: sw          $zero, 0x0($a0)
    MEM_W(0X0, ctx->r4) = 0;
    // 0x802C59D8: sw          $t2, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r10;
L_802C59DC:
    // 0x802C59DC: lui         $a1, 0x802D
    ctx->r5 = S32(0X802D << 16);
    // 0x802C59E0: addiu       $a1, $a1, -0x7270
    ctx->r5 = ADD32(ctx->r5, -0X7270);
    // 0x802C59E4: lw          $a0, 0x0($a1)
    ctx->r4 = MEM_W(ctx->r5, 0X0);
    // 0x802C59E8: lui         $a2, 0x802D
    ctx->r6 = S32(0X802D << 16);
    // 0x802C59EC: addiu       $a2, $a2, -0x726C
    ctx->r6 = ADD32(ctx->r6, -0X726C);
    // 0x802C59F0: beq         $a0, $zero, L_802C5A30
    if (ctx->r4 == 0) {
        // 0x802C59F4: or          $v0, $a0, $zero
        ctx->r2 = ctx->r4 | 0;
            goto L_802C5A30;
    }
    // 0x802C59F4: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x802C59F8: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x802C59FC: beq         $v0, $at, L_802C5AE8
    if (ctx->r2 == ctx->r1) {
        // 0x802C5A00: lui         $a2, 0x802D
        ctx->r6 = S32(0X802D << 16);
            goto L_802C5AE8;
    }
    // 0x802C5A00: lui         $a2, 0x802D
    ctx->r6 = S32(0X802D << 16);
    // 0x802C5A04: addiu       $v1, $zero, 0x2
    ctx->r3 = ADD32(0, 0X2);
    // 0x802C5A08: beq         $v0, $v1, L_802C5BA8
    if (ctx->r2 == ctx->r3) {
        // 0x802C5A0C: lui         $a2, 0x802D
        ctx->r6 = S32(0X802D << 16);
            goto L_802C5BA8;
    }
    // 0x802C5A0C: lui         $a2, 0x802D
    ctx->r6 = S32(0X802D << 16);
    // 0x802C5A10: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x802C5A14: beq         $v0, $at, L_802C5C6C
    if (ctx->r2 == ctx->r1) {
        // 0x802C5A18: lui         $a2, 0x802D
        ctx->r6 = S32(0X802D << 16);
            goto L_802C5C6C;
    }
    // 0x802C5A18: lui         $a2, 0x802D
    ctx->r6 = S32(0X802D << 16);
    // 0x802C5A1C: lui         $v0, 0x802D
    ctx->r2 = S32(0X802D << 16);
    // 0x802C5A20: lui         $a2, 0x802D
    ctx->r6 = S32(0X802D << 16);
    // 0x802C5A24: addiu       $a2, $a2, -0x726C
    ctx->r6 = ADD32(ctx->r6, -0X726C);
    // 0x802C5A28: b           L_802C5D28
    // 0x802C5A2C: lw          $v0, -0x726C($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X726C);
        goto L_802C5D28;
    // 0x802C5A2C: lw          $v0, -0x726C($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X726C);
L_802C5A30:
    // 0x802C5A30: lw          $v0, 0x0($a2)
    ctx->r2 = MEM_W(ctx->r6, 0X0);
    // 0x802C5A34: lui         $at, 0x3F00
    ctx->r1 = S32(0X3F00 << 16);
    // 0x802C5A38: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x802C5A3C: mtc1        $v0, $f18
    ctx->f18.u32l = ctx->r2;
    // 0x802C5A40: addiu       $t4, $zero, 0x1
    ctx->r12 = ADD32(0, 0X1);
    // 0x802C5A44: lui         $at, 0x4F00
    ctx->r1 = S32(0X4F00 << 16);
    // 0x802C5A48: cvt.s.w     $f4, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    ctx->f4.fl = CVT_S_W(ctx->f18.u32l);
    // 0x802C5A4C: mul.s       $f6, $f4, $f0
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f6.fl = MUL_S(ctx->f4.fl, ctx->f0.fl);
    // 0x802C5A50: nop

    // 0x802C5A54: mul.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = MUL_S(ctx->f6.fl, ctx->f8.fl);
    // 0x802C5A58: cfc1        $t3, $FpcCsr
    ctx->r11 = get_cop1_cs();
    // 0x802C5A5C: ctc1        $t4, $FpcCsr
    set_cop1_cs(ctx->r12);
    // 0x802C5A60: nop

    // 0x802C5A64: cvt.w.s     $f16, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    ctx->f16.u32l = CVT_W_S(ctx->f10.fl);
    // 0x802C5A68: cfc1        $t4, $FpcCsr
    ctx->r12 = get_cop1_cs();
    // 0x802C5A6C: nop

    // 0x802C5A70: andi        $t4, $t4, 0x78
    ctx->r12 = ctx->r12 & 0X78;
    // 0x802C5A74: beq         $t4, $zero, L_802C5AC0
    if (ctx->r12 == 0) {
        // 0x802C5A78: nop
    
            goto L_802C5AC0;
    }
    // 0x802C5A78: nop

    // 0x802C5A7C: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
    // 0x802C5A80: addiu       $t4, $zero, 0x1
    ctx->r12 = ADD32(0, 0X1);
    // 0x802C5A84: sub.s       $f16, $f10, $f16
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f16.fl = ctx->f10.fl - ctx->f16.fl;
    // 0x802C5A88: ctc1        $t4, $FpcCsr
    set_cop1_cs(ctx->r12);
    // 0x802C5A8C: nop

    // 0x802C5A90: cvt.w.s     $f16, $f16
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 16);
    ctx->f16.u32l = CVT_W_S(ctx->f16.fl);
    // 0x802C5A94: cfc1        $t4, $FpcCsr
    ctx->r12 = get_cop1_cs();
    // 0x802C5A98: nop

    // 0x802C5A9C: andi        $t4, $t4, 0x78
    ctx->r12 = ctx->r12 & 0X78;
    // 0x802C5AA0: bne         $t4, $zero, L_802C5AB8
    if (ctx->r12 != 0) {
        // 0x802C5AA4: nop
    
            goto L_802C5AB8;
    }
    // 0x802C5AA4: nop

    // 0x802C5AA8: mfc1        $t4, $f16
    ctx->r12 = (int32_t)ctx->f16.u32l;
    // 0x802C5AAC: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x802C5AB0: b           L_802C5AD0
    // 0x802C5AB4: or          $t4, $t4, $at
    ctx->r12 = ctx->r12 | ctx->r1;
        goto L_802C5AD0;
    // 0x802C5AB4: or          $t4, $t4, $at
    ctx->r12 = ctx->r12 | ctx->r1;
L_802C5AB8:
    // 0x802C5AB8: b           L_802C5AD0
    // 0x802C5ABC: addiu       $t4, $zero, -0x1
    ctx->r12 = ADD32(0, -0X1);
        goto L_802C5AD0;
    // 0x802C5ABC: addiu       $t4, $zero, -0x1
    ctx->r12 = ADD32(0, -0X1);
L_802C5AC0:
    // 0x802C5AC0: mfc1        $t4, $f16
    ctx->r12 = (int32_t)ctx->f16.u32l;
    // 0x802C5AC4: nop

    // 0x802C5AC8: bltz        $t4, L_802C5AB8
    if (SIGNED(ctx->r12) < 0) {
        // 0x802C5ACC: nop
    
            goto L_802C5AB8;
    }
    // 0x802C5ACC: nop

L_802C5AD0:
    // 0x802C5AD0: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C5AD4: sw          $t4, -0x715C($at)
    MEM_W(-0X715C, ctx->r1) = ctx->r12;
    // 0x802C5AD8: ctc1        $t3, $FpcCsr
    set_cop1_cs(ctx->r11);
    // 0x802C5ADC: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C5AE0: b           L_802C5D28
    // 0x802C5AE4: sw          $zero, -0x7158($at)
    MEM_W(-0X7158, ctx->r1) = 0;
        goto L_802C5D28;
    // 0x802C5AE4: sw          $zero, -0x7158($at)
    MEM_W(-0X7158, ctx->r1) = 0;
L_802C5AE8:
    // 0x802C5AE8: addiu       $t5, $zero, 0xFF
    ctx->r13 = ADD32(0, 0XFF);
    // 0x802C5AEC: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C5AF0: addiu       $a2, $a2, -0x726C
    ctx->r6 = ADD32(ctx->r6, -0X726C);
    // 0x802C5AF4: sw          $t5, -0x715C($at)
    MEM_W(-0X715C, ctx->r1) = ctx->r13;
    // 0x802C5AF8: lw          $v0, 0x0($a2)
    ctx->r2 = MEM_W(ctx->r6, 0X0);
    // 0x802C5AFC: lui         $at, 0x3F00
    ctx->r1 = S32(0X3F00 << 16);
    // 0x802C5B00: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x802C5B04: mtc1        $v0, $f18
    ctx->f18.u32l = ctx->r2;
    // 0x802C5B08: addiu       $t7, $zero, 0x1
    ctx->r15 = ADD32(0, 0X1);
    // 0x802C5B0C: lui         $at, 0x4F00
    ctx->r1 = S32(0X4F00 << 16);
    // 0x802C5B10: cvt.s.w     $f4, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    ctx->f4.fl = CVT_S_W(ctx->f18.u32l);
    // 0x802C5B14: mul.s       $f6, $f4, $f0
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f6.fl = MUL_S(ctx->f4.fl, ctx->f0.fl);
    // 0x802C5B18: nop

    // 0x802C5B1C: mul.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = MUL_S(ctx->f6.fl, ctx->f8.fl);
    // 0x802C5B20: cfc1        $t6, $FpcCsr
    ctx->r14 = get_cop1_cs();
    // 0x802C5B24: ctc1        $t7, $FpcCsr
    set_cop1_cs(ctx->r15);
    // 0x802C5B28: nop

    // 0x802C5B2C: cvt.w.s     $f16, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    ctx->f16.u32l = CVT_W_S(ctx->f10.fl);
    // 0x802C5B30: cfc1        $t7, $FpcCsr
    ctx->r15 = get_cop1_cs();
    // 0x802C5B34: nop

    // 0x802C5B38: andi        $t7, $t7, 0x78
    ctx->r15 = ctx->r15 & 0X78;
    // 0x802C5B3C: beq         $t7, $zero, L_802C5B88
    if (ctx->r15 == 0) {
        // 0x802C5B40: nop
    
            goto L_802C5B88;
    }
    // 0x802C5B40: nop

    // 0x802C5B44: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
    // 0x802C5B48: addiu       $t7, $zero, 0x1
    ctx->r15 = ADD32(0, 0X1);
    // 0x802C5B4C: sub.s       $f16, $f10, $f16
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f16.fl = ctx->f10.fl - ctx->f16.fl;
    // 0x802C5B50: ctc1        $t7, $FpcCsr
    set_cop1_cs(ctx->r15);
    // 0x802C5B54: nop

    // 0x802C5B58: cvt.w.s     $f16, $f16
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 16);
    ctx->f16.u32l = CVT_W_S(ctx->f16.fl);
    // 0x802C5B5C: cfc1        $t7, $FpcCsr
    ctx->r15 = get_cop1_cs();
    // 0x802C5B60: nop

    // 0x802C5B64: andi        $t7, $t7, 0x78
    ctx->r15 = ctx->r15 & 0X78;
    // 0x802C5B68: bne         $t7, $zero, L_802C5B80
    if (ctx->r15 != 0) {
        // 0x802C5B6C: nop
    
            goto L_802C5B80;
    }
    // 0x802C5B6C: nop

    // 0x802C5B70: mfc1        $t7, $f16
    ctx->r15 = (int32_t)ctx->f16.u32l;
    // 0x802C5B74: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x802C5B78: b           L_802C5B98
    // 0x802C5B7C: or          $t7, $t7, $at
    ctx->r15 = ctx->r15 | ctx->r1;
        goto L_802C5B98;
    // 0x802C5B7C: or          $t7, $t7, $at
    ctx->r15 = ctx->r15 | ctx->r1;
L_802C5B80:
    // 0x802C5B80: b           L_802C5B98
    // 0x802C5B84: addiu       $t7, $zero, -0x1
    ctx->r15 = ADD32(0, -0X1);
        goto L_802C5B98;
    // 0x802C5B84: addiu       $t7, $zero, -0x1
    ctx->r15 = ADD32(0, -0X1);
L_802C5B88:
    // 0x802C5B88: mfc1        $t7, $f16
    ctx->r15 = (int32_t)ctx->f16.u32l;
    // 0x802C5B8C: nop

    // 0x802C5B90: bltz        $t7, L_802C5B80
    if (SIGNED(ctx->r15) < 0) {
        // 0x802C5B94: nop
    
            goto L_802C5B80;
    }
    // 0x802C5B94: nop

L_802C5B98:
    // 0x802C5B98: ctc1        $t6, $FpcCsr
    set_cop1_cs(ctx->r14);
    // 0x802C5B9C: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C5BA0: b           L_802C5D28
    // 0x802C5BA4: sw          $t7, -0x7158($at)
    MEM_W(-0X7158, ctx->r1) = ctx->r15;
        goto L_802C5D28;
    // 0x802C5BA4: sw          $t7, -0x7158($at)
    MEM_W(-0X7158, ctx->r1) = ctx->r15;
L_802C5BA8:
    // 0x802C5BA8: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C5BAC: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C5BB0: addiu       $a2, $a2, -0x726C
    ctx->r6 = ADD32(ctx->r6, -0X726C);
    // 0x802C5BB4: sw          $t8, -0x715C($at)
    MEM_W(-0X715C, ctx->r1) = ctx->r24;
    // 0x802C5BB8: lw          $v0, 0x0($a2)
    ctx->r2 = MEM_W(ctx->r6, 0X0);
    // 0x802C5BBC: lui         $at, 0x3F00
    ctx->r1 = S32(0X3F00 << 16);
    // 0x802C5BC0: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x802C5BC4: subu        $t9, $v1, $v0
    ctx->r25 = SUB32(ctx->r3, ctx->r2);
    // 0x802C5BC8: mtc1        $t9, $f18
    ctx->f18.u32l = ctx->r25;
    // 0x802C5BCC: addiu       $t1, $zero, 0x1
    ctx->r9 = ADD32(0, 0X1);
    // 0x802C5BD0: lui         $at, 0x4F00
    ctx->r1 = S32(0X4F00 << 16);
    // 0x802C5BD4: cvt.s.w     $f4, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    ctx->f4.fl = CVT_S_W(ctx->f18.u32l);
    // 0x802C5BD8: mul.s       $f6, $f4, $f0
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f6.fl = MUL_S(ctx->f4.fl, ctx->f0.fl);
    // 0x802C5BDC: nop

    // 0x802C5BE0: mul.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = MUL_S(ctx->f6.fl, ctx->f8.fl);
    // 0x802C5BE4: cfc1        $t0, $FpcCsr
    ctx->r8 = get_cop1_cs();
    // 0x802C5BE8: ctc1        $t1, $FpcCsr
    set_cop1_cs(ctx->r9);
    // 0x802C5BEC: nop

    // 0x802C5BF0: cvt.w.s     $f16, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    ctx->f16.u32l = CVT_W_S(ctx->f10.fl);
    // 0x802C5BF4: cfc1        $t1, $FpcCsr
    ctx->r9 = get_cop1_cs();
    // 0x802C5BF8: nop

    // 0x802C5BFC: andi        $t1, $t1, 0x78
    ctx->r9 = ctx->r9 & 0X78;
    // 0x802C5C00: beq         $t1, $zero, L_802C5C4C
    if (ctx->r9 == 0) {
        // 0x802C5C04: nop
    
            goto L_802C5C4C;
    }
    // 0x802C5C04: nop

    // 0x802C5C08: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
    // 0x802C5C0C: addiu       $t1, $zero, 0x1
    ctx->r9 = ADD32(0, 0X1);
    // 0x802C5C10: sub.s       $f16, $f10, $f16
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f16.fl = ctx->f10.fl - ctx->f16.fl;
    // 0x802C5C14: ctc1        $t1, $FpcCsr
    set_cop1_cs(ctx->r9);
    // 0x802C5C18: nop

    // 0x802C5C1C: cvt.w.s     $f16, $f16
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 16);
    ctx->f16.u32l = CVT_W_S(ctx->f16.fl);
    // 0x802C5C20: cfc1        $t1, $FpcCsr
    ctx->r9 = get_cop1_cs();
    // 0x802C5C24: nop

    // 0x802C5C28: andi        $t1, $t1, 0x78
    ctx->r9 = ctx->r9 & 0X78;
    // 0x802C5C2C: bne         $t1, $zero, L_802C5C44
    if (ctx->r9 != 0) {
        // 0x802C5C30: nop
    
            goto L_802C5C44;
    }
    // 0x802C5C30: nop

    // 0x802C5C34: mfc1        $t1, $f16
    ctx->r9 = (int32_t)ctx->f16.u32l;
    // 0x802C5C38: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x802C5C3C: b           L_802C5C5C
    // 0x802C5C40: or          $t1, $t1, $at
    ctx->r9 = ctx->r9 | ctx->r1;
        goto L_802C5C5C;
    // 0x802C5C40: or          $t1, $t1, $at
    ctx->r9 = ctx->r9 | ctx->r1;
L_802C5C44:
    // 0x802C5C44: b           L_802C5C5C
    // 0x802C5C48: addiu       $t1, $zero, -0x1
    ctx->r9 = ADD32(0, -0X1);
        goto L_802C5C5C;
    // 0x802C5C48: addiu       $t1, $zero, -0x1
    ctx->r9 = ADD32(0, -0X1);
L_802C5C4C:
    // 0x802C5C4C: mfc1        $t1, $f16
    ctx->r9 = (int32_t)ctx->f16.u32l;
    // 0x802C5C50: nop

    // 0x802C5C54: bltz        $t1, L_802C5C44
    if (SIGNED(ctx->r9) < 0) {
        // 0x802C5C58: nop
    
            goto L_802C5C44;
    }
    // 0x802C5C58: nop

L_802C5C5C:
    // 0x802C5C5C: ctc1        $t0, $FpcCsr
    set_cop1_cs(ctx->r8);
    // 0x802C5C60: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C5C64: b           L_802C5D28
    // 0x802C5C68: sw          $t1, -0x7158($at)
    MEM_W(-0X7158, ctx->r1) = ctx->r9;
        goto L_802C5D28;
    // 0x802C5C68: sw          $t1, -0x7158($at)
    MEM_W(-0X7158, ctx->r1) = ctx->r9;
L_802C5C6C:
    // 0x802C5C6C: addiu       $a2, $a2, -0x726C
    ctx->r6 = ADD32(ctx->r6, -0X726C);
    // 0x802C5C70: lw          $v0, 0x0($a2)
    ctx->r2 = MEM_W(ctx->r6, 0X0);
    // 0x802C5C74: lui         $at, 0x3F00
    ctx->r1 = S32(0X3F00 << 16);
    // 0x802C5C78: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x802C5C7C: subu        $t2, $v1, $v0
    ctx->r10 = SUB32(ctx->r3, ctx->r2);
    // 0x802C5C80: mtc1        $t2, $f18
    ctx->f18.u32l = ctx->r10;
    // 0x802C5C84: addiu       $t4, $zero, 0x1
    ctx->r12 = ADD32(0, 0X1);
    // 0x802C5C88: lui         $at, 0x4F00
    ctx->r1 = S32(0X4F00 << 16);
    // 0x802C5C8C: cvt.s.w     $f4, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    ctx->f4.fl = CVT_S_W(ctx->f18.u32l);
    // 0x802C5C90: mul.s       $f6, $f4, $f0
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f6.fl = MUL_S(ctx->f4.fl, ctx->f0.fl);
    // 0x802C5C94: nop

    // 0x802C5C98: mul.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = MUL_S(ctx->f6.fl, ctx->f8.fl);
    // 0x802C5C9C: cfc1        $t3, $FpcCsr
    ctx->r11 = get_cop1_cs();
    // 0x802C5CA0: ctc1        $t4, $FpcCsr
    set_cop1_cs(ctx->r12);
    // 0x802C5CA4: nop

    // 0x802C5CA8: cvt.w.s     $f16, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    ctx->f16.u32l = CVT_W_S(ctx->f10.fl);
    // 0x802C5CAC: cfc1        $t4, $FpcCsr
    ctx->r12 = get_cop1_cs();
    // 0x802C5CB0: nop

    // 0x802C5CB4: andi        $t4, $t4, 0x78
    ctx->r12 = ctx->r12 & 0X78;
    // 0x802C5CB8: beq         $t4, $zero, L_802C5D04
    if (ctx->r12 == 0) {
        // 0x802C5CBC: nop
    
            goto L_802C5D04;
    }
    // 0x802C5CBC: nop

    // 0x802C5CC0: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
    // 0x802C5CC4: addiu       $t4, $zero, 0x1
    ctx->r12 = ADD32(0, 0X1);
    // 0x802C5CC8: sub.s       $f16, $f10, $f16
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f16.fl = ctx->f10.fl - ctx->f16.fl;
    // 0x802C5CCC: ctc1        $t4, $FpcCsr
    set_cop1_cs(ctx->r12);
    // 0x802C5CD0: nop

    // 0x802C5CD4: cvt.w.s     $f16, $f16
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 16);
    ctx->f16.u32l = CVT_W_S(ctx->f16.fl);
    // 0x802C5CD8: cfc1        $t4, $FpcCsr
    ctx->r12 = get_cop1_cs();
    // 0x802C5CDC: nop

    // 0x802C5CE0: andi        $t4, $t4, 0x78
    ctx->r12 = ctx->r12 & 0X78;
    // 0x802C5CE4: bne         $t4, $zero, L_802C5CFC
    if (ctx->r12 != 0) {
        // 0x802C5CE8: nop
    
            goto L_802C5CFC;
    }
    // 0x802C5CE8: nop

    // 0x802C5CEC: mfc1        $t4, $f16
    ctx->r12 = (int32_t)ctx->f16.u32l;
    // 0x802C5CF0: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x802C5CF4: b           L_802C5D14
    // 0x802C5CF8: or          $t4, $t4, $at
    ctx->r12 = ctx->r12 | ctx->r1;
        goto L_802C5D14;
    // 0x802C5CF8: or          $t4, $t4, $at
    ctx->r12 = ctx->r12 | ctx->r1;
L_802C5CFC:
    // 0x802C5CFC: b           L_802C5D14
    // 0x802C5D00: addiu       $t4, $zero, -0x1
    ctx->r12 = ADD32(0, -0X1);
        goto L_802C5D14;
    // 0x802C5D00: addiu       $t4, $zero, -0x1
    ctx->r12 = ADD32(0, -0X1);
L_802C5D04:
    // 0x802C5D04: mfc1        $t4, $f16
    ctx->r12 = (int32_t)ctx->f16.u32l;
    // 0x802C5D08: nop

    // 0x802C5D0C: bltz        $t4, L_802C5CFC
    if (SIGNED(ctx->r12) < 0) {
        // 0x802C5D10: nop
    
            goto L_802C5CFC;
    }
    // 0x802C5D10: nop

L_802C5D14:
    // 0x802C5D14: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C5D18: sw          $t4, -0x715C($at)
    MEM_W(-0X715C, ctx->r1) = ctx->r12;
    // 0x802C5D1C: ctc1        $t3, $FpcCsr
    set_cop1_cs(ctx->r11);
    // 0x802C5D20: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C5D24: sw          $zero, -0x7158($at)
    MEM_W(-0X7158, ctx->r1) = 0;
L_802C5D28:
    // 0x802C5D28: addiu       $t5, $v0, 0x1
    ctx->r13 = ADD32(ctx->r2, 0X1);
    // 0x802C5D2C: slti        $at, $t5, 0x2
    ctx->r1 = SIGNED(ctx->r13) < 0X2 ? 1 : 0;
    // 0x802C5D30: bne         $at, $zero, L_802C5D50
    if (ctx->r1 != 0) {
        // 0x802C5D34: sw          $t5, 0x0($a2)
        MEM_W(0X0, ctx->r6) = ctx->r13;
            goto L_802C5D50;
    }
    // 0x802C5D34: sw          $t5, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r13;
    // 0x802C5D38: addiu       $t7, $a0, 0x1
    ctx->r15 = ADD32(ctx->r4, 0X1);
    // 0x802C5D3C: addiu       $at, $zero, 0x4
    ctx->r1 = ADD32(0, 0X4);
    // 0x802C5D40: sw          $zero, 0x0($a2)
    MEM_W(0X0, ctx->r6) = 0;
    // 0x802C5D44: bne         $t7, $at, L_802C5D50
    if (ctx->r15 != ctx->r1) {
        // 0x802C5D48: sw          $t7, 0x0($a1)
        MEM_W(0X0, ctx->r5) = ctx->r15;
            goto L_802C5D50;
    }
    // 0x802C5D48: sw          $t7, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r15;
    // 0x802C5D4C: sw          $zero, 0x0($a1)
    MEM_W(0X0, ctx->r5) = 0;
L_802C5D50:
    // 0x802C5D50: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x802C5D54: lw          $v0, -0x19C0($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X19C0);
    // 0x802C5D58: addiu       $at, $zero, 0x4
    ctx->r1 = ADD32(0, 0X4);
    // 0x802C5D5C: lui         $fp, 0x801D
    ctx->r30 = S32(0X801D << 16);
    // 0x802C5D60: beq         $v0, $at, L_802C5D80
    if (ctx->r2 == ctx->r1) {
        // 0x802C5D64: addiu       $fp, $fp, -0x1A08
        ctx->r30 = ADD32(ctx->r30, -0X1A08);
            goto L_802C5D80;
    }
    // 0x802C5D64: addiu       $fp, $fp, -0x1A08
    ctx->r30 = ADD32(ctx->r30, -0X1A08);
    // 0x802C5D68: addiu       $at, $zero, 0x7
    ctx->r1 = ADD32(0, 0X7);
    // 0x802C5D6C: beq         $v0, $at, L_802C5D80
    if (ctx->r2 == ctx->r1) {
        // 0x802C5D70: addiu       $at, $zero, 0xB
        ctx->r1 = ADD32(0, 0XB);
            goto L_802C5D80;
    }
    // 0x802C5D70: addiu       $at, $zero, 0xB
    ctx->r1 = ADD32(0, 0XB);
    // 0x802C5D74: beq         $v0, $at, L_802C5D80
    if (ctx->r2 == ctx->r1) {
        // 0x802C5D78: addiu       $at, $zero, 0x8
        ctx->r1 = ADD32(0, 0X8);
            goto L_802C5D80;
    }
    // 0x802C5D78: addiu       $at, $zero, 0x8
    ctx->r1 = ADD32(0, 0X8);
    // 0x802C5D7C: bne         $v0, $at, L_802C5F30
    if (ctx->r2 != ctx->r1) {
        // 0x802C5D80: lui         $at, 0x3F80
        ctx->r1 = S32(0X3F80 << 16);
            goto L_802C5F30;
    }
L_802C5D80:
    // 0x802C5D80: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x802C5D84: mtc1        $at, $f24
    ctx->f24.u32l = ctx->r1;
    // 0x802C5D88: lui         $at, 0x4180
    ctx->r1 = S32(0X4180 << 16);
    // 0x802C5D8C: mtc1        $at, $f18
    ctx->f18.u32l = ctx->r1;
    // 0x802C5D90: mtc1        $zero, $f22
    ctx->f22.u32l = 0;
    // 0x802C5D94: lui         $at, 0x4480
    ctx->r1 = S32(0X4480 << 16);
    // 0x802C5D98: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x802C5D9C: lw          $a0, 0x0($fp)
    ctx->r4 = MEM_W(ctx->r30, 0X0);
    // 0x802C5DA0: lui         $a1, 0x802D
    ctx->r5 = S32(0X802D << 16);
    // 0x802C5DA4: mfc1        $a3, $f24
    ctx->r7 = (int32_t)ctx->f24.u32l;
    // 0x802C5DA8: addiu       $a1, $a1, -0x7154
    ctx->r5 = ADD32(ctx->r5, -0X7154);
    // 0x802C5DAC: lui         $a2, 0x4204
    ctx->r6 = S32(0X4204 << 16);
    // 0x802C5DB0: swc1        $f18, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f18.u32l;
    // 0x802C5DB4: swc1        $f22, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->f22.u32l;
    // 0x802C5DB8: swc1        $f22, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->f22.u32l;
    // 0x802C5DBC: addiu       $a0, $a0, 0xA40
    ctx->r4 = ADD32(ctx->r4, 0XA40);
    // 0x802C5DC0: jal         0x800481E0
    // 0x802C5DC4: swc1        $f4, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->f4.u32l;
    func_800481E0(rdram, ctx);
        goto after_0;
    // 0x802C5DC4: swc1        $f4, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->f4.u32l;
    after_0:
    // 0x802C5DC8: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C5DCC: lwc1        $f6, -0x7210($at)
    ctx->f6.u32l = MEM_W(ctx->r1, -0X7210);
    // 0x802C5DD0: mfc1        $a1, $f22
    ctx->r5 = (int32_t)ctx->f22.u32l;
    // 0x802C5DD4: mfc1        $a2, $f22
    ctx->r6 = (int32_t)ctx->f22.u32l;
    // 0x802C5DD8: mfc1        $a3, $f24
    ctx->r7 = (int32_t)ctx->f24.u32l;
    // 0x802C5DDC: addiu       $a0, $sp, 0xC8
    ctx->r4 = ADD32(ctx->r29, 0XC8);
    // 0x802C5DE0: swc1        $f22, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f22.u32l;
    // 0x802C5DE4: swc1        $f24, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->f24.u32l;
    // 0x802C5DE8: swc1        $f22, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->f22.u32l;
    // 0x802C5DEC: swc1        $f22, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->f22.u32l;
    // 0x802C5DF0: swc1        $f22, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->f22.u32l;
    // 0x802C5DF4: swc1        $f22, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->f22.u32l;
    // 0x802C5DF8: jal         0x80048A88
    // 0x802C5DFC: swc1        $f6, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->f6.u32l;
    func_80048A88(rdram, ctx);
        goto after_1;
    // 0x802C5DFC: swc1        $f6, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->f6.u32l;
    after_1:
    // 0x802C5E00: lui         $at, 0x43FA
    ctx->r1 = S32(0X43FA << 16);
    // 0x802C5E04: lui         $s7, 0x802D
    ctx->r23 = S32(0X802D << 16);
    // 0x802C5E08: lui         $s6, 0x802D
    ctx->r22 = S32(0X802D << 16);
    // 0x802C5E0C: lui         $s1, 0x8015
    ctx->r17 = S32(0X8015 << 16);
    // 0x802C5E10: mtc1        $at, $f20
    ctx->f20.u32l = ctx->r1;
    // 0x802C5E14: addiu       $s1, $s1, 0x4350
    ctx->r17 = ADD32(ctx->r17, 0X4350);
    // 0x802C5E18: addiu       $s6, $s6, -0x7268
    ctx->r22 = ADD32(ctx->r22, -0X7268);
    // 0x802C5E1C: addiu       $s7, $s7, -0x72A4
    ctx->r23 = ADD32(ctx->r23, -0X72A4);
    // 0x802C5E20: or          $s0, $zero, $zero
    ctx->r16 = 0 | 0;
    // 0x802C5E24: or          $s2, $zero, $zero
    ctx->r18 = 0 | 0;
    // 0x802C5E28: addiu       $s5, $sp, 0x10C
    ctx->r21 = ADD32(ctx->r29, 0X10C);
    // 0x802C5E2C: addiu       $s4, $sp, 0x18C
    ctx->r20 = ADD32(ctx->r29, 0X18C);
    // 0x802C5E30: addiu       $s3, $sp, 0x14C
    ctx->r19 = ADD32(ctx->r29, 0X14C);
L_802C5E34:
    // 0x802C5E34: lw          $t9, 0x0($s7)
    ctx->r25 = MEM_W(ctx->r23, 0X0);
    // 0x802C5E38: mfc1        $a3, $f20
    ctx->r7 = (int32_t)ctx->f20.u32l;
    // 0x802C5E3C: addiu       $a0, $sp, 0x88
    ctx->r4 = ADD32(ctx->r29, 0X88);
    // 0x802C5E40: bne         $s0, $t9, L_802C5E98
    if (ctx->r16 != ctx->r25) {
        // 0x802C5E44: or          $a1, $s3, $zero
        ctx->r5 = ctx->r19 | 0;
            goto L_802C5E98;
    }
    // 0x802C5E44: or          $a1, $s3, $zero
    ctx->r5 = ctx->r19 | 0;
    // 0x802C5E48: lw          $v0, 0x0($s6)
    ctx->r2 = MEM_W(ctx->r22, 0X0);
    // 0x802C5E4C: bgez        $v0, L_802C5E60
    if (SIGNED(ctx->r2) >= 0) {
        // 0x802C5E50: andi        $t0, $v0, 0xFFF
        ctx->r8 = ctx->r2 & 0XFFF;
            goto L_802C5E60;
    }
    // 0x802C5E50: andi        $t0, $v0, 0xFFF
    ctx->r8 = ctx->r2 & 0XFFF;
    // 0x802C5E54: beq         $t0, $zero, L_802C5E60
    if (ctx->r8 == 0) {
        // 0x802C5E58: nop
    
            goto L_802C5E60;
    }
    // 0x802C5E58: nop

    // 0x802C5E5C: addiu       $t0, $t0, -0x1000
    ctx->r8 = ADD32(ctx->r8, -0X1000);
L_802C5E60:
    // 0x802C5E60: addiu       $t1, $t0, 0x400
    ctx->r9 = ADD32(ctx->r8, 0X400);
    // 0x802C5E64: andi        $t2, $t1, 0xFFF
    ctx->r10 = ctx->r9 & 0XFFF;
    // 0x802C5E68: sll         $t3, $t2, 2
    ctx->r11 = S32(ctx->r10 << 2);
    // 0x802C5E6C: addu        $t4, $s1, $t3
    ctx->r12 = ADD32(ctx->r17, ctx->r11);
    // 0x802C5E70: lwc1        $f8, 0x0($t4)
    ctx->f8.u32l = MEM_W(ctx->r12, 0X0);
    // 0x802C5E74: andi        $t5, $t0, 0xFFF
    ctx->r13 = ctx->r8 & 0XFFF;
    // 0x802C5E78: sll         $t6, $t5, 2
    ctx->r14 = S32(ctx->r13 << 2);
    // 0x802C5E7C: addu        $t7, $s1, $t6
    ctx->r15 = ADD32(ctx->r17, ctx->r14);
    // 0x802C5E80: lwc1        $f10, 0x0($t7)
    ctx->f10.u32l = MEM_W(ctx->r15, 0X0);
    // 0x802C5E84: mul.s       $f0, $f8, $f20
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f0.fl = MUL_S(ctx->f8.fl, ctx->f20.fl);
    // 0x802C5E88: nop

    // 0x802C5E8C: mul.s       $f2, $f10, $f20
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f2.fl = MUL_S(ctx->f10.fl, ctx->f20.fl);
    // 0x802C5E90: b           L_802C5EB0
    // 0x802C5E94: nop

        goto L_802C5EB0;
    // 0x802C5E94: nop

L_802C5E98:
    // 0x802C5E98: lwc1        $f16, 0x1800($s1)
    ctx->f16.u32l = MEM_W(ctx->r17, 0X1800);
    // 0x802C5E9C: lwc1        $f18, 0x800($s1)
    ctx->f18.u32l = MEM_W(ctx->r17, 0X800);
    // 0x802C5EA0: mul.s       $f0, $f16, $f20
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f0.fl = MUL_S(ctx->f16.fl, ctx->f20.fl);
    // 0x802C5EA4: nop

    // 0x802C5EA8: mul.s       $f2, $f18, $f20
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f2.fl = MUL_S(ctx->f18.fl, ctx->f20.fl);
    // 0x802C5EAC: nop

L_802C5EB0:
    // 0x802C5EB0: mfc1        $a2, $f0
    ctx->r6 = (int32_t)ctx->f0.u32l;
    // 0x802C5EB4: swc1        $f2, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f2.u32l;
    // 0x802C5EB8: swc1        $f22, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->f22.u32l;
    // 0x802C5EBC: swc1        $f22, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->f22.u32l;
    // 0x802C5EC0: swc1        $f22, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->f22.u32l;
    // 0x802C5EC4: swc1        $f22, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->f22.u32l;
    // 0x802C5EC8: swc1        $f24, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->f24.u32l;
    // 0x802C5ECC: jal         0x800484C8
    // 0x802C5ED0: swc1        $f22, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->f22.u32l;
    func_800484C8(rdram, ctx);
        goto after_2;
    // 0x802C5ED0: swc1        $f22, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->f22.u32l;
    after_2:
    // 0x802C5ED4: addiu       $a0, $sp, 0xC8
    ctx->r4 = ADD32(ctx->r29, 0XC8);
    // 0x802C5ED8: jal         0x80047E78
    // 0x802C5EDC: or          $a1, $s4, $zero
    ctx->r5 = ctx->r20 | 0;
    SysUtils_MtxToMtxF(rdram, ctx);
        goto after_3;
    // 0x802C5EDC: or          $a1, $s4, $zero
    ctx->r5 = ctx->r20 | 0;
    after_3:
    // 0x802C5EE0: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
    // 0x802C5EE4: or          $a1, $s4, $zero
    ctx->r5 = ctx->r20 | 0;
    // 0x802C5EE8: jal         0x80049EB8
    // 0x802C5EEC: or          $a2, $s5, $zero
    ctx->r6 = ctx->r21 | 0;
    SysUtils_MatrixAffineMultiply(rdram, ctx);
        goto after_4;
    // 0x802C5EEC: or          $a2, $s5, $zero
    ctx->r6 = ctx->r21 | 0;
    after_4:
    // 0x802C5EF0: lw          $t8, 0x0($fp)
    ctx->r24 = MEM_W(ctx->r30, 0X0);
    // 0x802C5EF4: or          $a0, $s5, $zero
    ctx->r4 = ctx->r21 | 0;
    // 0x802C5EF8: addu        $a1, $t8, $s2
    ctx->r5 = ADD32(ctx->r24, ctx->r18);
    // 0x802C5EFC: jal         0x80047EE0
    // 0x802C5F00: addiu       $a1, $a1, 0xA80
    ctx->r5 = ADD32(ctx->r5, 0XA80);
    SysUtils_MtxFToMtx(rdram, ctx);
        goto after_5;
    // 0x802C5F00: addiu       $a1, $a1, 0xA80
    ctx->r5 = ADD32(ctx->r5, 0XA80);
    after_5:
    // 0x802C5F04: addiu       $s0, $s0, 0x1
    ctx->r16 = ADD32(ctx->r16, 0X1);
    // 0x802C5F08: addiu       $at, $zero, 0x4
    ctx->r1 = ADD32(0, 0X4);
    // 0x802C5F0C: bne         $s0, $at, L_802C5E34
    if (ctx->r16 != ctx->r1) {
        // 0x802C5F10: addiu       $s2, $s2, 0x40
        ctx->r18 = ADD32(ctx->r18, 0X40);
            goto L_802C5E34;
    }
    // 0x802C5F10: addiu       $s2, $s2, 0x40
    ctx->r18 = ADD32(ctx->r18, 0X40);
    // 0x802C5F14: lw          $t9, 0x0($s6)
    ctx->r25 = MEM_W(ctx->r22, 0X0);
    // 0x802C5F18: addiu       $t0, $t9, 0x18
    ctx->r8 = ADD32(ctx->r25, 0X18);
    // 0x802C5F1C: slti        $at, $t0, 0x1000
    ctx->r1 = SIGNED(ctx->r8) < 0X1000 ? 1 : 0;
    // 0x802C5F20: bne         $at, $zero, L_802C5F30
    if (ctx->r1 != 0) {
        // 0x802C5F24: sw          $t0, 0x0($s6)
        MEM_W(0X0, ctx->r22) = ctx->r8;
            goto L_802C5F30;
    }
    // 0x802C5F24: sw          $t0, 0x0($s6)
    MEM_W(0X0, ctx->r22) = ctx->r8;
    // 0x802C5F28: addiu       $t1, $t0, -0x1000
    ctx->r9 = ADD32(ctx->r8, -0X1000);
    // 0x802C5F2C: sw          $t1, 0x0($s6)
    MEM_W(0X0, ctx->r22) = ctx->r9;
L_802C5F30:
    // 0x802C5F30: lw          $ra, 0x74($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X74);
    // 0x802C5F34: ldc1        $f20, 0x38($sp)
    CHECK_FR(ctx, 20);
    ctx->f20.u64 = LD(ctx->r29, 0X38);
    // 0x802C5F38: ldc1        $f22, 0x40($sp)
    CHECK_FR(ctx, 22);
    ctx->f22.u64 = LD(ctx->r29, 0X40);
    // 0x802C5F3C: ldc1        $f24, 0x48($sp)
    CHECK_FR(ctx, 24);
    ctx->f24.u64 = LD(ctx->r29, 0X48);
    // 0x802C5F40: lw          $s0, 0x50($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X50);
    // 0x802C5F44: lw          $s1, 0x54($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X54);
    // 0x802C5F48: lw          $s2, 0x58($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X58);
    // 0x802C5F4C: lw          $s3, 0x5C($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X5C);
    // 0x802C5F50: lw          $s4, 0x60($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X60);
    // 0x802C5F54: lw          $s5, 0x64($sp)
    ctx->r21 = MEM_W(ctx->r29, 0X64);
    // 0x802C5F58: lw          $s6, 0x68($sp)
    ctx->r22 = MEM_W(ctx->r29, 0X68);
    // 0x802C5F5C: lw          $s7, 0x6C($sp)
    ctx->r23 = MEM_W(ctx->r29, 0X6C);
    // 0x802C5F60: lw          $fp, 0x70($sp)
    ctx->r30 = MEM_W(ctx->r29, 0X70);
    // 0x802C5F64: jr          $ra
    // 0x802C5F68: addiu       $sp, $sp, 0x1D8
    ctx->r29 = ADD32(ctx->r29, 0X1D8);
    return;
    // 0x802C5F68: addiu       $sp, $sp, 0x1D8
    ctx->r29 = ADD32(ctx->r29, 0X1D8);
;}
RECOMP_FUNC void func_i13_802C5F6C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C5F6C: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x802C5F70: addiu       $v0, $v0, -0x19C4
    ctx->r2 = ADD32(ctx->r2, -0X19C4);
    // 0x802C5F74: lw          $t6, 0x0($v0)
    ctx->r14 = MEM_W(ctx->r2, 0X0);
    // 0x802C5F78: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x802C5F7C: sw          $s0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r16;
    // 0x802C5F80: or          $s0, $a0, $zero
    ctx->r16 = ctx->r4 | 0;
    // 0x802C5F84: beq         $t6, $zero, L_802C5FB4
    if (ctx->r14 == 0) {
        // 0x802C5F88: sw          $ra, 0x1C($sp)
        MEM_W(0X1C, ctx->r29) = ctx->r31;
            goto L_802C5FB4;
    }
    // 0x802C5F88: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x802C5F8C: sw          $zero, 0x0($v0)
    MEM_W(0X0, ctx->r2) = 0;
    // 0x802C5F90: lui         $t7, 0x800E
    ctx->r15 = S32(0X800E << 16);
    // 0x802C5F94: lw          $t7, -0x54DC($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X54DC);
    // 0x802C5F98: addiu       $at, $zero, 0x40
    ctx->r1 = ADD32(0, 0X40);
    // 0x802C5F9C: bne         $t7, $at, L_802C5FB4
    if (ctx->r15 != ctx->r1) {
        // 0x802C5FA0: nop
    
            goto L_802C5FB4;
    }
    // 0x802C5FA0: nop

    // 0x802C5FA4: jal         0x80093C44
    // 0x802C5FA8: nop

    func_80093C44(rdram, ctx);
        goto after_0;
    // 0x802C5FA8: nop

    after_0:
    // 0x802C5FAC: b           L_802C6058
    // 0x802C5FB0: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
        goto L_802C6058;
    // 0x802C5FB0: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
L_802C5FB4:
    // 0x802C5FB4: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x802C5FB8: sw          $zero, -0x54D4($at)
    MEM_W(-0X54D4, ctx->r1) = 0;
    // 0x802C5FBC: jal         0x802C711C
    // 0x802C5FC0: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    func_i13_802C711C(rdram, ctx);
        goto after_1;
    // 0x802C5FC0: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_1:
    // 0x802C5FC4: lui         $a0, 0x802D
    ctx->r4 = S32(0X802D << 16);
    // 0x802C5FC8: lw          $a0, -0x728C($a0)
    ctx->r4 = MEM_W(ctx->r4, -0X728C);
    // 0x802C5FCC: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
    // 0x802C5FD0: beq         $a0, $zero, L_802C5FE8
    if (ctx->r4 == 0) {
        // 0x802C5FD4: nop
    
            goto L_802C5FE8;
    }
    // 0x802C5FD4: nop

    // 0x802C5FD8: jal         0x802C81AC
    // 0x802C5FDC: nop

    func_i13_802C81AC(rdram, ctx);
        goto after_2;
    // 0x802C5FDC: nop

    after_2:
    // 0x802C5FE0: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C5FE4: sw          $zero, -0x728C($at)
    MEM_W(-0X728C, ctx->r1) = 0;
L_802C5FE8:
    // 0x802C5FE8: jal         0x802C832C
    // 0x802C5FEC: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    func_i13_802C832C(rdram, ctx);
        goto after_3;
    // 0x802C5FEC: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_3:
    // 0x802C5FF0: lui         $t8, 0x800E
    ctx->r24 = S32(0X800E << 16);
    // 0x802C5FF4: lw          $t8, -0x54DC($t8)
    ctx->r24 = MEM_W(ctx->r24, -0X54DC);
    // 0x802C5FF8: addiu       $at, $zero, 0x40
    ctx->r1 = ADD32(0, 0X40);
    // 0x802C5FFC: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
    // 0x802C6000: bne         $t8, $at, L_802C6038
    if (ctx->r24 != ctx->r1) {
        // 0x802C6004: lui         $t0, 0x8023
        ctx->r8 = S32(0X8023 << 16);
            goto L_802C6038;
    }
    // 0x802C6004: lui         $t0, 0x8023
    ctx->r8 = S32(0X8023 << 16);
    // 0x802C6008: lui         $t9, 0x802D
    ctx->r25 = S32(0X802D << 16);
    // 0x802C600C: lw          $t9, -0x7288($t9)
    ctx->r25 = MEM_W(ctx->r25, -0X7288);
    // 0x802C6010: bne         $t9, $zero, L_802C6028
    if (ctx->r25 != 0) {
        // 0x802C6014: nop
    
            goto L_802C6028;
    }
    // 0x802C6014: nop

    // 0x802C6018: jal         0x802C6068
    // 0x802C601C: nop

    func_i13_802C6068(rdram, ctx);
        goto after_4;
    // 0x802C601C: nop

    after_4:
    // 0x802C6020: b           L_802C6054
    // 0x802C6024: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
        goto L_802C6054;
    // 0x802C6024: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
L_802C6028:
    // 0x802C6028: jal         0x802C7060
    // 0x802C602C: nop

    func_i13_802C7060(rdram, ctx);
        goto after_5;
    // 0x802C602C: nop

    after_5:
    // 0x802C6030: b           L_802C6054
    // 0x802C6034: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
        goto L_802C6054;
    // 0x802C6034: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
L_802C6038:
    // 0x802C6038: lh          $t0, -0x75EA($t0)
    ctx->r8 = MEM_H(ctx->r8, -0X75EA);
    // 0x802C603C: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x802C6040: bnel        $t0, $at, L_802C6054
    if (ctx->r8 != ctx->r1) {
        // 0x802C6044: or          $v0, $s0, $zero
        ctx->r2 = ctx->r16 | 0;
            goto L_802C6054;
    }
    goto skip_0;
    // 0x802C6044: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
    skip_0:
    // 0x802C6048: jal         0x801EC304
    // 0x802C604C: nop

    func_801EC304(rdram, ctx);
        goto after_6;
    // 0x802C604C: nop

    after_6:
    // 0x802C6050: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
L_802C6054:
    // 0x802C6054: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
L_802C6058:
    // 0x802C6058: lw          $s0, 0x18($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X18);
    // 0x802C605C: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x802C6060: jr          $ra
    // 0x802C6064: nop

    return;
    // 0x802C6064: nop

;}
RECOMP_FUNC void func_i13_802C6068(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C6068: lui         $t6, 0x801D
    ctx->r14 = S32(0X801D << 16);
    // 0x802C606C: lw          $t6, -0x19C0($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X19C0);
    // 0x802C6070: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x802C6074: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x802C6078: sltiu       $at, $t6, 0xC
    ctx->r1 = ctx->r14 < 0XC ? 1 : 0;
    // 0x802C607C: beq         $at, $zero, L_802C6144
    if (ctx->r1 == 0) {
        // 0x802C6080: sll         $t6, $t6, 2
        ctx->r14 = S32(ctx->r14 << 2);
            goto L_802C6144;
    }
    // 0x802C6080: sll         $t6, $t6, 2
    ctx->r14 = S32(ctx->r14 << 2);
    // 0x802C6084: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C6088: addu        $at, $at, $t6
    gpr jr_addend_802C6090 = ctx->r14;
    ctx->r1 = ADD32(ctx->r1, ctx->r14);
    // 0x802C608C: lw          $t6, -0x720C($at)
    ctx->r14 = ADD32(ctx->r1, -0X720C);
    // 0x802C6090: jr          $t6
    // 0x802C6094: nop

    switch (jr_addend_802C6090 >> 2) {
        case 0: goto L_802C6098; break;
        case 1: goto L_802C60A8; break;
        case 2: goto L_802C60A8; break;
        case 3: goto L_802C60B8; break;
        case 4: goto L_802C60C8; break;
        case 5: goto L_802C60E8; break;
        case 6: goto L_802C60F8; break;
        case 7: goto L_802C6108; break;
        case 8: goto L_802C60D8; break;
        case 9: goto L_802C6138; break;
        case 10: goto L_802C6128; break;
        case 11: goto L_802C6118; break;
        default: switch_error(__func__, 0x802C6090, 0x802C8DF4);
    }
    // 0x802C6094: nop

L_802C6098:
    // 0x802C6098: jal         0x802C61E0
    // 0x802C609C: nop

    func_i13_802C61E0(rdram, ctx);
        goto after_0;
    // 0x802C609C: nop

    after_0:
    // 0x802C60A0: b           L_802C6144
    // 0x802C60A4: sw          $v0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r2;
        goto L_802C6144;
    // 0x802C60A4: sw          $v0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r2;
L_802C60A8:
    // 0x802C60A8: jal         0x802C62EC
    // 0x802C60AC: nop

    func_i13_802C62EC(rdram, ctx);
        goto after_1;
    // 0x802C60AC: nop

    after_1:
    // 0x802C60B0: b           L_802C6144
    // 0x802C60B4: sw          $v0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r2;
        goto L_802C6144;
    // 0x802C60B4: sw          $v0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r2;
L_802C60B8:
    // 0x802C60B8: jal         0x802C64AC
    // 0x802C60BC: nop

    func_i13_802C64AC(rdram, ctx);
        goto after_2;
    // 0x802C60BC: nop

    after_2:
    // 0x802C60C0: b           L_802C6144
    // 0x802C60C4: sw          $v0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r2;
        goto L_802C6144;
    // 0x802C60C4: sw          $v0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r2;
L_802C60C8:
    // 0x802C60C8: jal         0x802C65D4
    // 0x802C60CC: nop

    func_i13_802C65D4(rdram, ctx);
        goto after_3;
    // 0x802C60CC: nop

    after_3:
    // 0x802C60D0: b           L_802C6144
    // 0x802C60D4: sw          $v0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r2;
        goto L_802C6144;
    // 0x802C60D4: sw          $v0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r2;
L_802C60D8:
    // 0x802C60D8: jal         0x802C6700
    // 0x802C60DC: nop

    func_i13_802C6700(rdram, ctx);
        goto after_4;
    // 0x802C60DC: nop

    after_4:
    // 0x802C60E0: b           L_802C6144
    // 0x802C60E4: sw          $v0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r2;
        goto L_802C6144;
    // 0x802C60E4: sw          $v0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r2;
L_802C60E8:
    // 0x802C60E8: jal         0x802C69CC
    // 0x802C60EC: nop

    func_i13_802C69CC(rdram, ctx);
        goto after_5;
    // 0x802C60EC: nop

    after_5:
    // 0x802C60F0: b           L_802C6144
    // 0x802C60F4: sw          $v0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r2;
        goto L_802C6144;
    // 0x802C60F4: sw          $v0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r2;
L_802C60F8:
    // 0x802C60F8: jal         0x802C6ABC
    // 0x802C60FC: nop

    func_i13_802C6ABC(rdram, ctx);
        goto after_6;
    // 0x802C60FC: nop

    after_6:
    // 0x802C6100: b           L_802C6144
    // 0x802C6104: sw          $v0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r2;
        goto L_802C6144;
    // 0x802C6104: sw          $v0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r2;
L_802C6108:
    // 0x802C6108: jal         0x802C6BC4
    // 0x802C610C: nop

    func_i13_802C6BC4(rdram, ctx);
        goto after_7;
    // 0x802C610C: nop

    after_7:
    // 0x802C6110: b           L_802C6144
    // 0x802C6114: sw          $v0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r2;
        goto L_802C6144;
    // 0x802C6114: sw          $v0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r2;
L_802C6118:
    // 0x802C6118: jal         0x802C6CE4
    // 0x802C611C: nop

    func_i13_802C6CE4(rdram, ctx);
        goto after_8;
    // 0x802C611C: nop

    after_8:
    // 0x802C6120: b           L_802C6144
    // 0x802C6124: sw          $v0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r2;
        goto L_802C6144;
    // 0x802C6124: sw          $v0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r2;
L_802C6128:
    // 0x802C6128: jal         0x802C6E48
    // 0x802C612C: nop

    func_i13_802C6E48(rdram, ctx);
        goto after_9;
    // 0x802C612C: nop

    after_9:
    // 0x802C6130: b           L_802C6144
    // 0x802C6134: sw          $v0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r2;
        goto L_802C6144;
    // 0x802C6134: sw          $v0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r2;
L_802C6138:
    // 0x802C6138: jal         0x802C6F0C
    // 0x802C613C: nop

    func_i13_802C6F0C(rdram, ctx);
        goto after_10;
    // 0x802C613C: nop

    after_10:
    // 0x802C6140: sw          $v0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r2;
L_802C6144:
    // 0x802C6144: lw          $v1, 0x18($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X18);
    // 0x802C6148: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x802C614C: addiu       $a0, $zero, 0x11
    ctx->r4 = ADD32(0, 0X11);
    // 0x802C6150: bnel        $v1, $at, L_802C616C
    if (ctx->r3 != ctx->r1) {
        // 0x802C6154: addiu       $at, $zero, 0x2
        ctx->r1 = ADD32(0, 0X2);
            goto L_802C616C;
    }
    goto skip_0;
    // 0x802C6154: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    skip_0:
    // 0x802C6158: jal         0x800C37F4
    // 0x802C615C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_11;
    // 0x802C615C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_11:
    // 0x802C6160: b           L_802C61D4
    // 0x802C6164: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_802C61D4;
    // 0x802C6164: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x802C6168: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
L_802C616C:
    // 0x802C616C: bne         $v1, $at, L_802C6184
    if (ctx->r3 != ctx->r1) {
        // 0x802C6170: addiu       $a0, $zero, 0x16
        ctx->r4 = ADD32(0, 0X16);
            goto L_802C6184;
    }
    // 0x802C6170: addiu       $a0, $zero, 0x16
    ctx->r4 = ADD32(0, 0X16);
    // 0x802C6174: jal         0x800C37F4
    // 0x802C6178: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_12;
    // 0x802C6178: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_12:
    // 0x802C617C: b           L_802C61D4
    // 0x802C6180: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_802C61D4;
    // 0x802C6180: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C6184:
    // 0x802C6184: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x802C6188: bne         $v1, $at, L_802C61A0
    if (ctx->r3 != ctx->r1) {
        // 0x802C618C: addiu       $a0, $zero, 0x10
        ctx->r4 = ADD32(0, 0X10);
            goto L_802C61A0;
    }
    // 0x802C618C: addiu       $a0, $zero, 0x10
    ctx->r4 = ADD32(0, 0X10);
    // 0x802C6190: jal         0x800C37F4
    // 0x802C6194: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_13;
    // 0x802C6194: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_13:
    // 0x802C6198: b           L_802C61D4
    // 0x802C619C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_802C61D4;
    // 0x802C619C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C61A0:
    // 0x802C61A0: addiu       $at, $zero, 0x4
    ctx->r1 = ADD32(0, 0X4);
    // 0x802C61A4: bne         $v1, $at, L_802C61BC
    if (ctx->r3 != ctx->r1) {
        // 0x802C61A8: addiu       $a0, $zero, 0x10
        ctx->r4 = ADD32(0, 0X10);
            goto L_802C61BC;
    }
    // 0x802C61A8: addiu       $a0, $zero, 0x10
    ctx->r4 = ADD32(0, 0X10);
    // 0x802C61AC: jal         0x800C37F4
    // 0x802C61B0: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_14;
    // 0x802C61B0: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_14:
    // 0x802C61B4: b           L_802C61D4
    // 0x802C61B8: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_802C61D4;
    // 0x802C61B8: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C61BC:
    // 0x802C61BC: addiu       $at, $zero, 0x5
    ctx->r1 = ADD32(0, 0X5);
    // 0x802C61C0: bne         $v1, $at, L_802C61D0
    if (ctx->r3 != ctx->r1) {
        // 0x802C61C4: addiu       $a0, $zero, 0x37
        ctx->r4 = ADD32(0, 0X37);
            goto L_802C61D0;
    }
    // 0x802C61C4: addiu       $a0, $zero, 0x37
    ctx->r4 = ADD32(0, 0X37);
    // 0x802C61C8: jal         0x800C37F4
    // 0x802C61CC: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_15;
    // 0x802C61CC: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_15:
L_802C61D0:
    // 0x802C61D0: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C61D4:
    // 0x802C61D4: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x802C61D8: jr          $ra
    // 0x802C61DC: nop

    return;
    // 0x802C61DC: nop

;}
RECOMP_FUNC void func_i13_802C61E0(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C61E0: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x802C61E4: lhu         $v0, -0x19A6($v0)
    ctx->r2 = MEM_HU(ctx->r2, -0X19A6);
    // 0x802C61E8: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x802C61EC: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x802C61F0: andi        $t6, $v0, 0xB000
    ctx->r14 = ctx->r2 & 0XB000;
    // 0x802C61F4: beq         $t6, $zero, L_802C6260
    if (ctx->r14 == 0) {
        // 0x802C61F8: or          $v1, $zero, $zero
        ctx->r3 = 0 | 0;
            goto L_802C6260;
    }
    // 0x802C61F8: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
    // 0x802C61FC: lui         $v0, 0x802D
    ctx->r2 = S32(0X802D << 16);
    // 0x802C6200: addiu       $v0, $v0, -0x72B0
    ctx->r2 = ADD32(ctx->r2, -0X72B0);
    // 0x802C6204: lw          $v1, 0x0($v0)
    ctx->r3 = MEM_W(ctx->r2, 0X0);
    // 0x802C6208: addiu       $t7, $zero, 0x1
    ctx->r15 = ADD32(0, 0X1);
    // 0x802C620C: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x802C6210: bne         $v1, $zero, L_802C6230
    if (ctx->r3 != 0) {
        // 0x802C6214: nop
    
            goto L_802C6230;
    }
    // 0x802C6214: nop

    // 0x802C6218: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C621C: sw          $t7, -0x19C0($at)
    MEM_W(-0X19C0, ctx->r1) = ctx->r15;
    // 0x802C6220: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C6224: sw          $zero, -0x72AC($at)
    MEM_W(-0X72AC, ctx->r1) = 0;
    // 0x802C6228: b           L_802C62D8
    // 0x802C622C: addiu       $v1, $zero, 0x1
    ctx->r3 = ADD32(0, 0X1);
        goto L_802C62D8;
    // 0x802C622C: addiu       $v1, $zero, 0x1
    ctx->r3 = ADD32(0, 0X1);
L_802C6230:
    // 0x802C6230: bne         $v1, $at, L_802C6250
    if (ctx->r3 != ctx->r1) {
        // 0x802C6234: addiu       $t8, $zero, 0x2
        ctx->r24 = ADD32(0, 0X2);
            goto L_802C6250;
    }
    // 0x802C6234: addiu       $t8, $zero, 0x2
    ctx->r24 = ADD32(0, 0X2);
    // 0x802C6238: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C623C: sw          $t8, -0x19C0($at)
    MEM_W(-0X19C0, ctx->r1) = ctx->r24;
    // 0x802C6240: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C6244: sw          $zero, -0x72AC($at)
    MEM_W(-0X72AC, ctx->r1) = 0;
    // 0x802C6248: b           L_802C62D8
    // 0x802C624C: addiu       $v1, $zero, 0x1
    ctx->r3 = ADD32(0, 0X1);
        goto L_802C62D8;
    // 0x802C624C: addiu       $v1, $zero, 0x1
    ctx->r3 = ADD32(0, 0X1);
L_802C6250:
    // 0x802C6250: jal         0x802C8CBC
    // 0x802C6254: nop

    func_i13_802C8CBC(rdram, ctx);
        goto after_0;
    // 0x802C6254: nop

    after_0:
    // 0x802C6258: b           L_802C62D8
    // 0x802C625C: addiu       $v1, $zero, 0x1
    ctx->r3 = ADD32(0, 0X1);
        goto L_802C62D8;
    // 0x802C625C: addiu       $v1, $zero, 0x1
    ctx->r3 = ADD32(0, 0X1);
L_802C6260:
    // 0x802C6260: andi        $t9, $v0, 0x4000
    ctx->r25 = ctx->r2 & 0X4000;
    // 0x802C6264: beq         $t9, $zero, L_802C6280
    if (ctx->r25 == 0) {
        // 0x802C6268: andi        $t0, $v0, 0x200
        ctx->r8 = ctx->r2 & 0X200;
            goto L_802C6280;
    }
    // 0x802C6268: andi        $t0, $v0, 0x200
    ctx->r8 = ctx->r2 & 0X200;
    // 0x802C626C: addiu       $v1, $zero, 0x2
    ctx->r3 = ADD32(0, 0X2);
    // 0x802C6270: jal         0x802C8CBC
    // 0x802C6274: sw          $v1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r3;
    func_i13_802C8CBC(rdram, ctx);
        goto after_1;
    // 0x802C6274: sw          $v1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r3;
    after_1:
    // 0x802C6278: b           L_802C62D8
    // 0x802C627C: lw          $v1, 0x1C($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X1C);
        goto L_802C62D8;
    // 0x802C627C: lw          $v1, 0x1C($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X1C);
L_802C6280:
    // 0x802C6280: beq         $t0, $zero, L_802C62B0
    if (ctx->r8 == 0) {
        // 0x802C6284: andi        $t5, $v0, 0x100
        ctx->r13 = ctx->r2 & 0X100;
            goto L_802C62B0;
    }
    // 0x802C6284: andi        $t5, $v0, 0x100
    ctx->r13 = ctx->r2 & 0X100;
    // 0x802C6288: lui         $v0, 0x802D
    ctx->r2 = S32(0X802D << 16);
    // 0x802C628C: addiu       $v0, $v0, -0x72B0
    ctx->r2 = ADD32(ctx->r2, -0X72B0);
    // 0x802C6290: lw          $t1, 0x0($v0)
    ctx->r9 = MEM_W(ctx->r2, 0X0);
    // 0x802C6294: addiu       $v1, $zero, 0x3
    ctx->r3 = ADD32(0, 0X3);
    // 0x802C6298: addiu       $t4, $zero, 0x2
    ctx->r12 = ADD32(0, 0X2);
    // 0x802C629C: addiu       $t2, $t1, -0x1
    ctx->r10 = ADD32(ctx->r9, -0X1);
    // 0x802C62A0: bgez        $t2, L_802C62D8
    if (SIGNED(ctx->r10) >= 0) {
        // 0x802C62A4: sw          $t2, 0x0($v0)
        MEM_W(0X0, ctx->r2) = ctx->r10;
            goto L_802C62D8;
    }
    // 0x802C62A4: sw          $t2, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r10;
    // 0x802C62A8: b           L_802C62D8
    // 0x802C62AC: sw          $t4, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r12;
        goto L_802C62D8;
    // 0x802C62AC: sw          $t4, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r12;
L_802C62B0:
    // 0x802C62B0: beq         $t5, $zero, L_802C62D8
    if (ctx->r13 == 0) {
        // 0x802C62B4: lui         $v0, 0x802D
        ctx->r2 = S32(0X802D << 16);
            goto L_802C62D8;
    }
    // 0x802C62B4: lui         $v0, 0x802D
    ctx->r2 = S32(0X802D << 16);
    // 0x802C62B8: addiu       $v0, $v0, -0x72B0
    ctx->r2 = ADD32(ctx->r2, -0X72B0);
    // 0x802C62BC: lw          $t6, 0x0($v0)
    ctx->r14 = MEM_W(ctx->r2, 0X0);
    // 0x802C62C0: addiu       $v1, $zero, 0x4
    ctx->r3 = ADD32(0, 0X4);
    // 0x802C62C4: addiu       $t7, $t6, 0x1
    ctx->r15 = ADD32(ctx->r14, 0X1);
    // 0x802C62C8: slti        $at, $t7, 0x3
    ctx->r1 = SIGNED(ctx->r15) < 0X3 ? 1 : 0;
    // 0x802C62CC: bne         $at, $zero, L_802C62D8
    if (ctx->r1 != 0) {
        // 0x802C62D0: sw          $t7, 0x0($v0)
        MEM_W(0X0, ctx->r2) = ctx->r15;
            goto L_802C62D8;
    }
    // 0x802C62D0: sw          $t7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r15;
    // 0x802C62D4: sw          $zero, 0x0($v0)
    MEM_W(0X0, ctx->r2) = 0;
L_802C62D8:
    // 0x802C62D8: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x802C62DC: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x802C62E0: or          $v0, $v1, $zero
    ctx->r2 = ctx->r3 | 0;
    // 0x802C62E4: jr          $ra
    // 0x802C62E8: nop

    return;
    // 0x802C62E8: nop

;}
RECOMP_FUNC void func_i13_802C62EC(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C62EC: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x802C62F0: lhu         $v0, -0x19A6($v0)
    ctx->r2 = MEM_HU(ctx->r2, -0X19A6);
    // 0x802C62F4: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x802C62F8: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x802C62FC: andi        $t6, $v0, 0xB000
    ctx->r14 = ctx->r2 & 0XB000;
    // 0x802C6300: beq         $t6, $zero, L_802C6414
    if (ctx->r14 == 0) {
        // 0x802C6304: or          $a1, $zero, $zero
        ctx->r5 = 0 | 0;
            goto L_802C6414;
    }
    // 0x802C6304: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C6308: lui         $t7, 0x801D
    ctx->r15 = S32(0X801D << 16);
    // 0x802C630C: lw          $t7, -0x19C0($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X19C0);
    // 0x802C6310: addiu       $v1, $zero, 0x1
    ctx->r3 = ADD32(0, 0X1);
    // 0x802C6314: or          $a1, $v1, $zero
    ctx->r5 = ctx->r3 | 0;
    // 0x802C6318: bne         $v1, $t7, L_802C63B0
    if (ctx->r3 != ctx->r15) {
        // 0x802C631C: lui         $v0, 0x802D
        ctx->r2 = S32(0X802D << 16);
            goto L_802C63B0;
    }
    // 0x802C631C: lui         $v0, 0x802D
    ctx->r2 = S32(0X802D << 16);
    // 0x802C6320: lui         $v0, 0x802D
    ctx->r2 = S32(0X802D << 16);
    // 0x802C6324: addiu       $v0, $v0, -0x72AC
    ctx->r2 = ADD32(ctx->r2, -0X72AC);
    // 0x802C6328: lw          $t8, 0x0($v0)
    ctx->r24 = MEM_W(ctx->r2, 0X0);
    // 0x802C632C: bne         $t8, $zero, L_802C6354
    if (ctx->r24 != 0) {
        // 0x802C6330: nop
    
            goto L_802C6354;
    }
    // 0x802C6330: nop

    // 0x802C6334: jal         0x8007D1B8
    // 0x802C6338: sw          $a1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r5;
    Save_PfsFindFile(rdram, ctx);
        goto after_0;
    // 0x802C6338: sw          $a1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r5;
    after_0:
    // 0x802C633C: lui         $a0, 0x802D
    ctx->r4 = S32(0X802D << 16);
    // 0x802C6340: addiu       $a0, $a0, -0x728C
    ctx->r4 = ADD32(ctx->r4, -0X728C);
    // 0x802C6344: sw          $v0, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r2;
    // 0x802C6348: lw          $a1, 0x1C($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X1C);
    // 0x802C634C: b           L_802C6394
    // 0x802C6350: or          $v1, $v0, $zero
    ctx->r3 = ctx->r2 | 0;
        goto L_802C6394;
    // 0x802C6350: or          $v1, $v0, $zero
    ctx->r3 = ctx->r2 | 0;
L_802C6354:
    // 0x802C6354: jal         0x8007D1B8
    // 0x802C6358: sw          $a1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r5;
    Save_PfsFindFile(rdram, ctx);
        goto after_1;
    // 0x802C6358: sw          $a1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r5;
    after_1:
    // 0x802C635C: lui         $a0, 0x802D
    ctx->r4 = S32(0X802D << 16);
    // 0x802C6360: addiu       $a0, $a0, -0x728C
    ctx->r4 = ADD32(ctx->r4, -0X728C);
    // 0x802C6364: addiu       $at, $zero, 0x4
    ctx->r1 = ADD32(0, 0X4);
    // 0x802C6368: sw          $v0, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r2;
    // 0x802C636C: lw          $a1, 0x1C($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X1C);
    // 0x802C6370: bne         $v0, $at, L_802C6394
    if (ctx->r2 != ctx->r1) {
        // 0x802C6374: or          $v1, $v0, $zero
        ctx->r3 = ctx->r2 | 0;
            goto L_802C6394;
    }
    // 0x802C6374: or          $v1, $v0, $zero
    ctx->r3 = ctx->r2 | 0;
    // 0x802C6378: jal         0x8007D24C
    // 0x802C637C: sw          $a1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r5;
    Save_PfsCheckFree(rdram, ctx);
        goto after_2;
    // 0x802C637C: sw          $a1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r5;
    after_2:
    // 0x802C6380: lui         $a0, 0x802D
    ctx->r4 = S32(0X802D << 16);
    // 0x802C6384: addiu       $a0, $a0, -0x728C
    ctx->r4 = ADD32(ctx->r4, -0X728C);
    // 0x802C6388: sw          $v0, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r2;
    // 0x802C638C: lw          $a1, 0x1C($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X1C);
    // 0x802C6390: or          $v1, $v0, $zero
    ctx->r3 = ctx->r2 | 0;
L_802C6394:
    // 0x802C6394: bne         $v1, $zero, L_802C6498
    if (ctx->r3 != 0) {
        // 0x802C6398: addiu       $t9, $zero, 0x3
        ctx->r25 = ADD32(0, 0X3);
            goto L_802C6498;
    }
    // 0x802C6398: addiu       $t9, $zero, 0x3
    ctx->r25 = ADD32(0, 0X3);
    // 0x802C639C: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C63A0: sw          $t9, -0x19C0($at)
    MEM_W(-0X19C0, ctx->r1) = ctx->r25;
    // 0x802C63A4: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C63A8: b           L_802C6498
    // 0x802C63AC: sw          $zero, -0x72A8($at)
    MEM_W(-0X72A8, ctx->r1) = 0;
        goto L_802C6498;
    // 0x802C63AC: sw          $zero, -0x72A8($at)
    MEM_W(-0X72A8, ctx->r1) = 0;
L_802C63B0:
    // 0x802C63B0: addiu       $v0, $v0, -0x72AC
    ctx->r2 = ADD32(ctx->r2, -0X72AC);
    // 0x802C63B4: lw          $t0, 0x0($v0)
    ctx->r8 = MEM_W(ctx->r2, 0X0);
    // 0x802C63B8: bne         $v1, $t0, L_802C63DC
    if (ctx->r3 != ctx->r8) {
        // 0x802C63BC: nop
    
            goto L_802C63DC;
    }
    // 0x802C63BC: nop

    // 0x802C63C0: jal         0x8007D1B8
    // 0x802C63C4: sw          $a1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r5;
    Save_PfsFindFile(rdram, ctx);
        goto after_3;
    // 0x802C63C4: sw          $a1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r5;
    after_3:
    // 0x802C63C8: lui         $a0, 0x802D
    ctx->r4 = S32(0X802D << 16);
    // 0x802C63CC: addiu       $a0, $a0, -0x728C
    ctx->r4 = ADD32(ctx->r4, -0X728C);
    // 0x802C63D0: sw          $v0, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r2;
    // 0x802C63D4: addiu       $v1, $zero, 0x1
    ctx->r3 = ADD32(0, 0X1);
    // 0x802C63D8: lw          $a1, 0x1C($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X1C);
L_802C63DC:
    // 0x802C63DC: lui         $a0, 0x802D
    ctx->r4 = S32(0X802D << 16);
    // 0x802C63E0: addiu       $a0, $a0, -0x728C
    ctx->r4 = ADD32(ctx->r4, -0X728C);
    // 0x802C63E4: lw          $t1, 0x0($a0)
    ctx->r9 = MEM_W(ctx->r4, 0X0);
    // 0x802C63E8: addiu       $t2, $zero, 0x5
    ctx->r10 = ADD32(0, 0X5);
    // 0x802C63EC: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C63F0: bne         $t1, $zero, L_802C6498
    if (ctx->r9 != 0) {
        // 0x802C63F4: addiu       $a0, $zero, 0x3
        ctx->r4 = ADD32(0, 0X3);
            goto L_802C6498;
    }
    // 0x802C63F4: addiu       $a0, $zero, 0x3
    ctx->r4 = ADD32(0, 0X3);
    // 0x802C63F8: sw          $t2, -0x19C0($at)
    MEM_W(-0X19C0, ctx->r1) = ctx->r10;
    // 0x802C63FC: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C6400: sw          $v1, -0x7290($at)
    MEM_W(-0X7290, ctx->r1) = ctx->r3;
    // 0x802C6404: jal         0x800C3E6C
    // 0x802C6408: sw          $a1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r5;
    func_800C3E6C(rdram, ctx);
        goto after_4;
    // 0x802C6408: sw          $a1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r5;
    after_4:
    // 0x802C640C: b           L_802C6498
    // 0x802C6410: lw          $a1, 0x1C($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X1C);
        goto L_802C6498;
    // 0x802C6410: lw          $a1, 0x1C($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X1C);
L_802C6414:
    // 0x802C6414: andi        $t3, $v0, 0x4000
    ctx->r11 = ctx->r2 & 0X4000;
    // 0x802C6418: beq         $t3, $zero, L_802C6438
    if (ctx->r11 == 0) {
        // 0x802C641C: lui         $at, 0x801D
        ctx->r1 = S32(0X801D << 16);
            goto L_802C6438;
    }
    // 0x802C641C: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C6420: lui         $v0, 0x802D
    ctx->r2 = S32(0X802D << 16);
    // 0x802C6424: addiu       $v0, $v0, -0x72AC
    ctx->r2 = ADD32(ctx->r2, -0X72AC);
    // 0x802C6428: sw          $zero, -0x19C0($at)
    MEM_W(-0X19C0, ctx->r1) = 0;
    // 0x802C642C: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C6430: b           L_802C6498
    // 0x802C6434: sw          $zero, 0x0($v0)
    MEM_W(0X0, ctx->r2) = 0;
        goto L_802C6498;
    // 0x802C6434: sw          $zero, 0x0($v0)
    MEM_W(0X0, ctx->r2) = 0;
L_802C6438:
    // 0x802C6438: andi        $t4, $v0, 0x200
    ctx->r12 = ctx->r2 & 0X200;
    // 0x802C643C: beql        $t4, $zero, L_802C6470
    if (ctx->r12 == 0) {
        // 0x802C6440: andi        $t8, $v0, 0x100
        ctx->r24 = ctx->r2 & 0X100;
            goto L_802C6470;
    }
    goto skip_0;
    // 0x802C6440: andi        $t8, $v0, 0x100
    ctx->r24 = ctx->r2 & 0X100;
    skip_0:
    // 0x802C6444: lui         $v0, 0x802D
    ctx->r2 = S32(0X802D << 16);
    // 0x802C6448: addiu       $v0, $v0, -0x72AC
    ctx->r2 = ADD32(ctx->r2, -0X72AC);
    // 0x802C644C: lw          $t5, 0x0($v0)
    ctx->r13 = MEM_W(ctx->r2, 0X0);
    // 0x802C6450: addiu       $a1, $zero, 0x3
    ctx->r5 = ADD32(0, 0X3);
    // 0x802C6454: addiu       $v1, $zero, 0x1
    ctx->r3 = ADD32(0, 0X1);
    // 0x802C6458: addiu       $t6, $t5, -0x1
    ctx->r14 = ADD32(ctx->r13, -0X1);
    // 0x802C645C: bgez        $t6, L_802C6498
    if (SIGNED(ctx->r14) >= 0) {
        // 0x802C6460: sw          $t6, 0x0($v0)
        MEM_W(0X0, ctx->r2) = ctx->r14;
            goto L_802C6498;
    }
    // 0x802C6460: sw          $t6, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r14;
    // 0x802C6464: b           L_802C6498
    // 0x802C6468: sw          $v1, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r3;
        goto L_802C6498;
    // 0x802C6468: sw          $v1, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r3;
    // 0x802C646C: andi        $t8, $v0, 0x100
    ctx->r24 = ctx->r2 & 0X100;
L_802C6470:
    // 0x802C6470: beq         $t8, $zero, L_802C6498
    if (ctx->r24 == 0) {
        // 0x802C6474: lui         $v0, 0x802D
        ctx->r2 = S32(0X802D << 16);
            goto L_802C6498;
    }
    // 0x802C6474: lui         $v0, 0x802D
    ctx->r2 = S32(0X802D << 16);
    // 0x802C6478: addiu       $v0, $v0, -0x72AC
    ctx->r2 = ADD32(ctx->r2, -0X72AC);
    // 0x802C647C: lw          $t9, 0x0($v0)
    ctx->r25 = MEM_W(ctx->r2, 0X0);
    // 0x802C6480: addiu       $a1, $zero, 0x4
    ctx->r5 = ADD32(0, 0X4);
    // 0x802C6484: addiu       $t0, $t9, 0x1
    ctx->r8 = ADD32(ctx->r25, 0X1);
    // 0x802C6488: slti        $at, $t0, 0x2
    ctx->r1 = SIGNED(ctx->r8) < 0X2 ? 1 : 0;
    // 0x802C648C: bne         $at, $zero, L_802C6498
    if (ctx->r1 != 0) {
        // 0x802C6490: sw          $t0, 0x0($v0)
        MEM_W(0X0, ctx->r2) = ctx->r8;
            goto L_802C6498;
    }
    // 0x802C6490: sw          $t0, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r8;
    // 0x802C6494: sw          $zero, 0x0($v0)
    MEM_W(0X0, ctx->r2) = 0;
L_802C6498:
    // 0x802C6498: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x802C649C: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x802C64A0: or          $v0, $a1, $zero
    ctx->r2 = ctx->r5 | 0;
    // 0x802C64A4: jr          $ra
    // 0x802C64A8: nop

    return;
    // 0x802C64A8: nop

;}
RECOMP_FUNC void func_i13_802C64AC(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C64AC: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x802C64B0: lhu         $v0, -0x19A6($v0)
    ctx->r2 = MEM_HU(ctx->r2, -0X19A6);
    // 0x802C64B4: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x802C64B8: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x802C64BC: andi        $t6, $v0, 0xB000
    ctx->r14 = ctx->r2 & 0XB000;
    // 0x802C64C0: beq         $t6, $zero, L_802C6548
    if (ctx->r14 == 0) {
        // 0x802C64C4: or          $v1, $zero, $zero
        ctx->r3 = 0 | 0;
            goto L_802C6548;
    }
    // 0x802C64C4: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
    // 0x802C64C8: lui         $v0, 0x802D
    ctx->r2 = S32(0X802D << 16);
    // 0x802C64CC: addiu       $v0, $v0, -0x72A8
    ctx->r2 = ADD32(ctx->r2, -0X72A8);
    // 0x802C64D0: lw          $t7, 0x0($v0)
    ctx->r15 = MEM_W(ctx->r2, 0X0);
    // 0x802C64D4: addiu       $v1, $zero, 0x1
    ctx->r3 = ADD32(0, 0X1);
    // 0x802C64D8: addiu       $t0, $zero, 0x6
    ctx->r8 = ADD32(0, 0X6);
    // 0x802C64DC: bne         $t7, $zero, L_802C6508
    if (ctx->r15 != 0) {
        // 0x802C64E0: lui         $at, 0x801D
        ctx->r1 = S32(0X801D << 16);
            goto L_802C6508;
    }
    // 0x802C64E0: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C64E4: addiu       $t8, $zero, 0x4
    ctx->r24 = ADD32(0, 0X4);
    // 0x802C64E8: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C64EC: sw          $t8, -0x19C0($at)
    MEM_W(-0X19C0, ctx->r1) = ctx->r24;
    // 0x802C64F0: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C64F4: sw          $zero, -0x72A4($at)
    MEM_W(-0X72A4, ctx->r1) = 0;
    // 0x802C64F8: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C64FC: addiu       $t9, $zero, 0x200
    ctx->r25 = ADD32(0, 0X200);
    // 0x802C6500: b           L_802C65C0
    // 0x802C6504: sw          $t9, -0x7268($at)
    MEM_W(-0X7268, ctx->r1) = ctx->r25;
        goto L_802C65C0;
    // 0x802C6504: sw          $t9, -0x7268($at)
    MEM_W(-0X7268, ctx->r1) = ctx->r25;
L_802C6508:
    // 0x802C6508: lui         $t2, 0x802D
    ctx->r10 = S32(0X802D << 16);
    // 0x802C650C: lw          $t2, -0x72AC($t2)
    ctx->r10 = MEM_W(ctx->r10, -0X72AC);
    // 0x802C6510: sw          $t0, -0x19C0($at)
    MEM_W(-0X19C0, ctx->r1) = ctx->r8;
    // 0x802C6514: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C6518: addiu       $t1, $zero, 0x1
    ctx->r9 = ADD32(0, 0X1);
    // 0x802C651C: bne         $t2, $zero, L_802C6534
    if (ctx->r10 != 0) {
        // 0x802C6520: sw          $t1, -0x7290($at)
        MEM_W(-0X7290, ctx->r1) = ctx->r9;
            goto L_802C6534;
    }
    // 0x802C6520: sw          $t1, -0x7290($at)
    MEM_W(-0X7290, ctx->r1) = ctx->r9;
    // 0x802C6524: addiu       $a0, $zero, 0x2
    ctx->r4 = ADD32(0, 0X2);
    // 0x802C6528: jal         0x802C82A4
    // 0x802C652C: sw          $v1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r3;
    func_i13_802C82A4(rdram, ctx);
        goto after_0;
    // 0x802C652C: sw          $v1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r3;
    after_0:
    // 0x802C6530: lw          $v1, 0x1C($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X1C);
L_802C6534:
    // 0x802C6534: addiu       $a0, $zero, 0x3
    ctx->r4 = ADD32(0, 0X3);
    // 0x802C6538: jal         0x800C3E6C
    // 0x802C653C: sw          $v1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r3;
    func_800C3E6C(rdram, ctx);
        goto after_1;
    // 0x802C653C: sw          $v1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r3;
    after_1:
    // 0x802C6540: b           L_802C65C0
    // 0x802C6544: lw          $v1, 0x1C($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X1C);
        goto L_802C65C0;
    // 0x802C6544: lw          $v1, 0x1C($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X1C);
L_802C6548:
    // 0x802C6548: andi        $t3, $v0, 0x4000
    ctx->r11 = ctx->r2 & 0X4000;
    // 0x802C654C: beq         $t3, $zero, L_802C6568
    if (ctx->r11 == 0) {
        // 0x802C6550: andi        $t5, $v0, 0x200
        ctx->r13 = ctx->r2 & 0X200;
            goto L_802C6568;
    }
    // 0x802C6550: andi        $t5, $v0, 0x200
    ctx->r13 = ctx->r2 & 0X200;
    // 0x802C6554: addiu       $t4, $zero, 0x1
    ctx->r12 = ADD32(0, 0X1);
    // 0x802C6558: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C655C: addiu       $v1, $zero, 0x2
    ctx->r3 = ADD32(0, 0X2);
    // 0x802C6560: b           L_802C65C0
    // 0x802C6564: sw          $t4, -0x19C0($at)
    MEM_W(-0X19C0, ctx->r1) = ctx->r12;
        goto L_802C65C0;
    // 0x802C6564: sw          $t4, -0x19C0($at)
    MEM_W(-0X19C0, ctx->r1) = ctx->r12;
L_802C6568:
    // 0x802C6568: beq         $t5, $zero, L_802C6598
    if (ctx->r13 == 0) {
        // 0x802C656C: andi        $t0, $v0, 0x100
        ctx->r8 = ctx->r2 & 0X100;
            goto L_802C6598;
    }
    // 0x802C656C: andi        $t0, $v0, 0x100
    ctx->r8 = ctx->r2 & 0X100;
    // 0x802C6570: lui         $v0, 0x802D
    ctx->r2 = S32(0X802D << 16);
    // 0x802C6574: addiu       $v0, $v0, -0x72A8
    ctx->r2 = ADD32(ctx->r2, -0X72A8);
    // 0x802C6578: lw          $t6, 0x0($v0)
    ctx->r14 = MEM_W(ctx->r2, 0X0);
    // 0x802C657C: addiu       $v1, $zero, 0x3
    ctx->r3 = ADD32(0, 0X3);
    // 0x802C6580: addiu       $t9, $zero, 0x1
    ctx->r25 = ADD32(0, 0X1);
    // 0x802C6584: addiu       $t7, $t6, -0x1
    ctx->r15 = ADD32(ctx->r14, -0X1);
    // 0x802C6588: bgez        $t7, L_802C65C0
    if (SIGNED(ctx->r15) >= 0) {
        // 0x802C658C: sw          $t7, 0x0($v0)
        MEM_W(0X0, ctx->r2) = ctx->r15;
            goto L_802C65C0;
    }
    // 0x802C658C: sw          $t7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r15;
    // 0x802C6590: b           L_802C65C0
    // 0x802C6594: sw          $t9, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r25;
        goto L_802C65C0;
    // 0x802C6594: sw          $t9, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r25;
L_802C6598:
    // 0x802C6598: beq         $t0, $zero, L_802C65C0
    if (ctx->r8 == 0) {
        // 0x802C659C: lui         $v0, 0x802D
        ctx->r2 = S32(0X802D << 16);
            goto L_802C65C0;
    }
    // 0x802C659C: lui         $v0, 0x802D
    ctx->r2 = S32(0X802D << 16);
    // 0x802C65A0: addiu       $v0, $v0, -0x72A8
    ctx->r2 = ADD32(ctx->r2, -0X72A8);
    // 0x802C65A4: lw          $t1, 0x0($v0)
    ctx->r9 = MEM_W(ctx->r2, 0X0);
    // 0x802C65A8: addiu       $v1, $zero, 0x4
    ctx->r3 = ADD32(0, 0X4);
    // 0x802C65AC: addiu       $t2, $t1, 0x1
    ctx->r10 = ADD32(ctx->r9, 0X1);
    // 0x802C65B0: slti        $at, $t2, 0x2
    ctx->r1 = SIGNED(ctx->r10) < 0X2 ? 1 : 0;
    // 0x802C65B4: bne         $at, $zero, L_802C65C0
    if (ctx->r1 != 0) {
        // 0x802C65B8: sw          $t2, 0x0($v0)
        MEM_W(0X0, ctx->r2) = ctx->r10;
            goto L_802C65C0;
    }
    // 0x802C65B8: sw          $t2, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r10;
    // 0x802C65BC: sw          $zero, 0x0($v0)
    MEM_W(0X0, ctx->r2) = 0;
L_802C65C0:
    // 0x802C65C0: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x802C65C4: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x802C65C8: or          $v0, $v1, $zero
    ctx->r2 = ctx->r3 | 0;
    // 0x802C65CC: jr          $ra
    // 0x802C65D0: nop

    return;
    // 0x802C65D0: nop

;}
RECOMP_FUNC void func_i13_802C65D4(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C65D4: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x802C65D8: lhu         $v0, -0x19A6($v0)
    ctx->r2 = MEM_HU(ctx->r2, -0X19A6);
    // 0x802C65DC: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x802C65E0: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x802C65E4: andi        $t6, $v0, 0xB000
    ctx->r14 = ctx->r2 & 0XB000;
    // 0x802C65E8: beq         $t6, $zero, L_802C665C
    if (ctx->r14 == 0) {
        // 0x802C65EC: or          $v1, $zero, $zero
        ctx->r3 = 0 | 0;
            goto L_802C665C;
    }
    // 0x802C65EC: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
    // 0x802C65F0: lui         $t7, 0x802D
    ctx->r15 = S32(0X802D << 16);
    // 0x802C65F4: lw          $t7, -0x72AC($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X72AC);
    // 0x802C65F8: addiu       $v1, $zero, 0x1
    ctx->r3 = ADD32(0, 0X1);
    // 0x802C65FC: addiu       $t9, $zero, 0x7
    ctx->r25 = ADD32(0, 0X7);
    // 0x802C6600: bne         $t7, $zero, L_802C6638
    if (ctx->r15 != 0) {
        // 0x802C6604: lui         $at, 0x801D
        ctx->r1 = S32(0X801D << 16);
            goto L_802C6638;
    }
    // 0x802C6604: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C6608: addiu       $t8, $zero, 0x8
    ctx->r24 = ADD32(0, 0X8);
    // 0x802C660C: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C6610: sw          $t8, -0x19C0($at)
    MEM_W(-0X19C0, ctx->r1) = ctx->r24;
    // 0x802C6614: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C6618: sw          $zero, -0x723C($at)
    MEM_W(-0X723C, ctx->r1) = 0;
    // 0x802C661C: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C6620: sw          $zero, -0x7238($at)
    MEM_W(-0X7238, ctx->r1) = 0;
    // 0x802C6624: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C6628: sw          $zero, -0x7234($at)
    MEM_W(-0X7234, ctx->r1) = 0;
    // 0x802C662C: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C6630: b           L_802C66EC
    // 0x802C6634: sw          $zero, -0x7230($at)
    MEM_W(-0X7230, ctx->r1) = 0;
        goto L_802C66EC;
    // 0x802C6634: sw          $zero, -0x7230($at)
    MEM_W(-0X7230, ctx->r1) = 0;
L_802C6638:
    // 0x802C6638: sw          $t9, -0x19C0($at)
    MEM_W(-0X19C0, ctx->r1) = ctx->r25;
    // 0x802C663C: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C6640: addiu       $t0, $zero, 0x1
    ctx->r8 = ADD32(0, 0X1);
    // 0x802C6644: sw          $t0, -0x7290($at)
    MEM_W(-0X7290, ctx->r1) = ctx->r8;
    // 0x802C6648: addiu       $a0, $zero, 0x3
    ctx->r4 = ADD32(0, 0X3);
    // 0x802C664C: jal         0x800C3E6C
    // 0x802C6650: sw          $v1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r3;
    func_800C3E6C(rdram, ctx);
        goto after_0;
    // 0x802C6650: sw          $v1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r3;
    after_0:
    // 0x802C6654: b           L_802C66EC
    // 0x802C6658: lw          $v1, 0x1C($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X1C);
        goto L_802C66EC;
    // 0x802C6658: lw          $v1, 0x1C($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X1C);
L_802C665C:
    // 0x802C665C: andi        $t1, $v0, 0x4000
    ctx->r9 = ctx->r2 & 0X4000;
    // 0x802C6660: beq         $t1, $zero, L_802C667C
    if (ctx->r9 == 0) {
        // 0x802C6664: andi        $t3, $v0, 0x200
        ctx->r11 = ctx->r2 & 0X200;
            goto L_802C667C;
    }
    // 0x802C6664: andi        $t3, $v0, 0x200
    ctx->r11 = ctx->r2 & 0X200;
    // 0x802C6668: addiu       $t2, $zero, 0x3
    ctx->r10 = ADD32(0, 0X3);
    // 0x802C666C: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C6670: addiu       $v1, $zero, 0x2
    ctx->r3 = ADD32(0, 0X2);
    // 0x802C6674: b           L_802C66EC
    // 0x802C6678: sw          $t2, -0x19C0($at)
    MEM_W(-0X19C0, ctx->r1) = ctx->r10;
        goto L_802C66EC;
    // 0x802C6678: sw          $t2, -0x19C0($at)
    MEM_W(-0X19C0, ctx->r1) = ctx->r10;
L_802C667C:
    // 0x802C667C: beq         $t3, $zero, L_802C66B8
    if (ctx->r11 == 0) {
        // 0x802C6680: andi        $t9, $v0, 0x100
        ctx->r25 = ctx->r2 & 0X100;
            goto L_802C66B8;
    }
    // 0x802C6680: andi        $t9, $v0, 0x100
    ctx->r25 = ctx->r2 & 0X100;
    // 0x802C6684: lui         $v0, 0x802D
    ctx->r2 = S32(0X802D << 16);
    // 0x802C6688: addiu       $t4, $zero, 0x200
    ctx->r12 = ADD32(0, 0X200);
    // 0x802C668C: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C6690: addiu       $v0, $v0, -0x72A4
    ctx->r2 = ADD32(ctx->r2, -0X72A4);
    // 0x802C6694: sw          $t4, -0x7268($at)
    MEM_W(-0X7268, ctx->r1) = ctx->r12;
    // 0x802C6698: lw          $t5, 0x0($v0)
    ctx->r13 = MEM_W(ctx->r2, 0X0);
    // 0x802C669C: addiu       $v1, $zero, 0x3
    ctx->r3 = ADD32(0, 0X3);
    // 0x802C66A0: addiu       $t8, $zero, 0x3
    ctx->r24 = ADD32(0, 0X3);
    // 0x802C66A4: addiu       $t6, $t5, -0x1
    ctx->r14 = ADD32(ctx->r13, -0X1);
    // 0x802C66A8: bgez        $t6, L_802C66EC
    if (SIGNED(ctx->r14) >= 0) {
        // 0x802C66AC: sw          $t6, 0x0($v0)
        MEM_W(0X0, ctx->r2) = ctx->r14;
            goto L_802C66EC;
    }
    // 0x802C66AC: sw          $t6, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r14;
    // 0x802C66B0: b           L_802C66EC
    // 0x802C66B4: sw          $t8, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r24;
        goto L_802C66EC;
    // 0x802C66B4: sw          $t8, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r24;
L_802C66B8:
    // 0x802C66B8: beq         $t9, $zero, L_802C66EC
    if (ctx->r25 == 0) {
        // 0x802C66BC: lui         $v0, 0x802D
        ctx->r2 = S32(0X802D << 16);
            goto L_802C66EC;
    }
    // 0x802C66BC: lui         $v0, 0x802D
    ctx->r2 = S32(0X802D << 16);
    // 0x802C66C0: addiu       $t0, $zero, 0x200
    ctx->r8 = ADD32(0, 0X200);
    // 0x802C66C4: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C66C8: addiu       $v0, $v0, -0x72A4
    ctx->r2 = ADD32(ctx->r2, -0X72A4);
    // 0x802C66CC: sw          $t0, -0x7268($at)
    MEM_W(-0X7268, ctx->r1) = ctx->r8;
    // 0x802C66D0: lw          $t1, 0x0($v0)
    ctx->r9 = MEM_W(ctx->r2, 0X0);
    // 0x802C66D4: addiu       $v1, $zero, 0x4
    ctx->r3 = ADD32(0, 0X4);
    // 0x802C66D8: addiu       $t2, $t1, 0x1
    ctx->r10 = ADD32(ctx->r9, 0X1);
    // 0x802C66DC: slti        $at, $t2, 0x4
    ctx->r1 = SIGNED(ctx->r10) < 0X4 ? 1 : 0;
    // 0x802C66E0: bne         $at, $zero, L_802C66EC
    if (ctx->r1 != 0) {
        // 0x802C66E4: sw          $t2, 0x0($v0)
        MEM_W(0X0, ctx->r2) = ctx->r10;
            goto L_802C66EC;
    }
    // 0x802C66E4: sw          $t2, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r10;
    // 0x802C66E8: sw          $zero, 0x0($v0)
    MEM_W(0X0, ctx->r2) = 0;
L_802C66EC:
    // 0x802C66EC: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x802C66F0: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x802C66F4: or          $v0, $v1, $zero
    ctx->r2 = ctx->r3 | 0;
    // 0x802C66F8: jr          $ra
    // 0x802C66FC: nop

    return;
    // 0x802C66FC: nop

;}
RECOMP_FUNC void func_i13_802C6700(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C6700: lui         $a0, 0x802D
    ctx->r4 = S32(0X802D << 16);
    // 0x802C6704: addiu       $a0, $a0, -0x7230
    ctx->r4 = ADD32(ctx->r4, -0X7230);
    // 0x802C6708: lw          $v0, 0x0($a0)
    ctx->r2 = MEM_W(ctx->r4, 0X0);
    // 0x802C670C: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x802C6710: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x802C6714: beq         $v0, $zero, L_802C6738
    if (ctx->r2 == 0) {
        // 0x802C6718: or          $a2, $zero, $zero
        ctx->r6 = 0 | 0;
            goto L_802C6738;
    }
    // 0x802C6718: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x802C671C: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C6720: beq         $v0, $a1, L_802C6824
    if (ctx->r2 == ctx->r5) {
        // 0x802C6724: addiu       $at, $zero, 0x2
        ctx->r1 = ADD32(0, 0X2);
            goto L_802C6824;
    }
    // 0x802C6724: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x802C6728: beq         $v0, $at, L_802C68D4
    if (ctx->r2 == ctx->r1) {
        // 0x802C672C: lui         $v1, 0x802D
        ctx->r3 = S32(0X802D << 16);
            goto L_802C68D4;
    }
    // 0x802C672C: lui         $v1, 0x802D
    ctx->r3 = S32(0X802D << 16);
    // 0x802C6730: b           L_802C69BC
    // 0x802C6734: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_802C69BC;
    // 0x802C6734: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C6738:
    // 0x802C6738: lui         $at, 0x40A0
    ctx->r1 = S32(0X40A0 << 16);
    // 0x802C673C: mtc1        $at, $f12
    ctx->f12.u32l = ctx->r1;
    // 0x802C6740: lui         $v1, 0x802D
    ctx->r3 = S32(0X802D << 16);
    // 0x802C6744: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C6748: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C674C: addiu       $v1, $v1, -0x7234
    ctx->r3 = ADD32(ctx->r3, -0X7234);
    // 0x802C6750: sw          $a1, -0x7238($at)
    MEM_W(-0X7238, ctx->r1) = ctx->r5;
    // 0x802C6754: lw          $t6, 0x0($v1)
    ctx->r14 = MEM_W(ctx->r3, 0X0);
    // 0x802C6758: addiu       $t8, $zero, 0x5
    ctx->r24 = ADD32(0, 0X5);
    // 0x802C675C: lui         $at, 0x4335
    ctx->r1 = S32(0X4335 << 16);
    // 0x802C6760: addiu       $v0, $t6, 0x1
    ctx->r2 = ADD32(ctx->r14, 0X1);
    // 0x802C6764: subu        $t9, $t8, $v0
    ctx->r25 = SUB32(ctx->r24, ctx->r2);
    // 0x802C6768: mtc1        $t9, $f4
    ctx->f4.u32l = ctx->r25;
    // 0x802C676C: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
    // 0x802C6770: mtc1        $v0, $f8
    ctx->f8.u32l = ctx->r2;
    // 0x802C6774: cvt.s.w     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
    // 0x802C6778: sw          $v0, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r2;
    // 0x802C677C: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C6780: cvt.s.w     $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.fl = CVT_S_W(ctx->f8.u32l);
    // 0x802C6784: div.s       $f0, $f6, $f12
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f0.fl = DIV_S(ctx->f6.fl, ctx->f12.fl);
    // 0x802C6788: div.s       $f2, $f10, $f12
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f2.fl = DIV_S(ctx->f10.fl, ctx->f12.fl);
    // 0x802C678C: mul.s       $f18, $f16, $f0
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f18.fl = MUL_S(ctx->f16.fl, ctx->f0.fl);
    // 0x802C6790: trunc.w.s   $f4, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    ctx->f4.u32l = TRUNC_W_S(ctx->f18.fl);
    // 0x802C6794: mfc1        $t1, $f4
    ctx->r9 = (int32_t)ctx->f4.u32l;
    // 0x802C6798: nop

    // 0x802C679C: addiu       $t2, $t1, 0x1F
    ctx->r10 = ADD32(ctx->r9, 0X1F);
    // 0x802C67A0: sw          $t2, -0x7150($at)
    MEM_W(-0X7150, ctx->r1) = ctx->r10;
    // 0x802C67A4: lui         $at, 0x41A0
    ctx->r1 = S32(0X41A0 << 16);
    // 0x802C67A8: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x802C67AC: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C67B0: mul.s       $f8, $f6, $f0
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f8.fl = MUL_S(ctx->f6.fl, ctx->f0.fl);
    // 0x802C67B4: trunc.w.s   $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.u32l = TRUNC_W_S(ctx->f8.fl);
    // 0x802C67B8: mfc1        $t4, $f10
    ctx->r12 = (int32_t)ctx->f10.u32l;
    // 0x802C67BC: nop

    // 0x802C67C0: addiu       $t5, $t4, 0x89
    ctx->r13 = ADD32(ctx->r12, 0X89);
    // 0x802C67C4: sw          $t5, -0x714C($at)
    MEM_W(-0X714C, ctx->r1) = ctx->r13;
    // 0x802C67C8: lui         $at, 0x43B5
    ctx->r1 = S32(0X43B5 << 16);
    // 0x802C67CC: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
    // 0x802C67D0: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C67D4: mul.s       $f18, $f16, $f2
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f18.fl = MUL_S(ctx->f16.fl, ctx->f2.fl);
    // 0x802C67D8: trunc.w.s   $f4, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    ctx->f4.u32l = TRUNC_W_S(ctx->f18.fl);
    // 0x802C67DC: mfc1        $t7, $f4
    ctx->r15 = (int32_t)ctx->f4.u32l;
    // 0x802C67E0: nop

    // 0x802C67E4: sw          $t7, -0x7148($at)
    MEM_W(-0X7148, ctx->r1) = ctx->r15;
    // 0x802C67E8: lui         $at, 0x4220
    ctx->r1 = S32(0X4220 << 16);
    // 0x802C67EC: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x802C67F0: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C67F4: mul.s       $f8, $f6, $f2
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f8.fl = MUL_S(ctx->f6.fl, ctx->f2.fl);
    // 0x802C67F8: trunc.w.s   $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.u32l = TRUNC_W_S(ctx->f8.fl);
    // 0x802C67FC: mfc1        $t9, $f10
    ctx->r25 = (int32_t)ctx->f10.u32l;
    // 0x802C6800: nop

    // 0x802C6804: sw          $t9, -0x7144($at)
    MEM_W(-0X7144, ctx->r1) = ctx->r25;
    // 0x802C6808: slti        $at, $v0, 0x5
    ctx->r1 = SIGNED(ctx->r2) < 0X5 ? 1 : 0;
    // 0x802C680C: bnel        $at, $zero, L_802C69BC
    if (ctx->r1 != 0) {
        // 0x802C6810: lw          $ra, 0x14($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X14);
            goto L_802C69BC;
    }
    goto skip_0;
    // 0x802C6810: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    skip_0:
    // 0x802C6814: sw          $a1, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r5;
    // 0x802C6818: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C681C: b           L_802C69B8
    // 0x802C6820: sw          $a1, -0x722C($at)
    MEM_W(-0X722C, ctx->r1) = ctx->r5;
        goto L_802C69B8;
    // 0x802C6820: sw          $a1, -0x722C($at)
    MEM_W(-0X722C, ctx->r1) = ctx->r5;
L_802C6824:
    // 0x802C6824: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x802C6828: lhu         $v0, -0x19A6($v0)
    ctx->r2 = MEM_HU(ctx->r2, -0X19A6);
    // 0x802C682C: addiu       $t1, $zero, 0x7
    ctx->r9 = ADD32(0, 0X7);
    // 0x802C6830: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C6834: andi        $t0, $v0, 0xB000
    ctx->r8 = ctx->r2 & 0XB000;
    // 0x802C6838: beq         $t0, $zero, L_802C6860
    if (ctx->r8 == 0) {
        // 0x802C683C: andi        $t2, $v0, 0x4000
        ctx->r10 = ctx->r2 & 0X4000;
            goto L_802C6860;
    }
    // 0x802C683C: andi        $t2, $v0, 0x4000
    ctx->r10 = ctx->r2 & 0X4000;
    // 0x802C6840: sw          $t1, -0x19C0($at)
    MEM_W(-0X19C0, ctx->r1) = ctx->r9;
    // 0x802C6844: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C6848: sw          $a1, -0x7290($at)
    MEM_W(-0X7290, ctx->r1) = ctx->r5;
    // 0x802C684C: addiu       $a0, $zero, 0x3
    ctx->r4 = ADD32(0, 0X3);
    // 0x802C6850: jal         0x800C3E6C
    // 0x802C6854: sw          $a1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r5;
    func_800C3E6C(rdram, ctx);
        goto after_0;
    // 0x802C6854: sw          $a1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r5;
    after_0:
    // 0x802C6858: b           L_802C69B8
    // 0x802C685C: lw          $a2, 0x1C($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X1C);
        goto L_802C69B8;
    // 0x802C685C: lw          $a2, 0x1C($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X1C);
L_802C6860:
    // 0x802C6860: beq         $t2, $zero, L_802C6888
    if (ctx->r10 == 0) {
        // 0x802C6864: lui         $v1, 0x802D
        ctx->r3 = S32(0X802D << 16);
            goto L_802C6888;
    }
    // 0x802C6864: lui         $v1, 0x802D
    ctx->r3 = S32(0X802D << 16);
    // 0x802C6868: addiu       $v1, $v1, -0x7234
    ctx->r3 = ADD32(ctx->r3, -0X7234);
    // 0x802C686C: addiu       $t3, $zero, 0x2
    ctx->r11 = ADD32(0, 0X2);
    // 0x802C6870: sw          $t3, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r11;
    // 0x802C6874: sw          $zero, 0x0($v1)
    MEM_W(0X0, ctx->r3) = 0;
    // 0x802C6878: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C687C: addiu       $a2, $zero, 0x2
    ctx->r6 = ADD32(0, 0X2);
    // 0x802C6880: b           L_802C69B8
    // 0x802C6884: sw          $zero, -0x722C($at)
    MEM_W(-0X722C, ctx->r1) = 0;
        goto L_802C69B8;
    // 0x802C6884: sw          $zero, -0x722C($at)
    MEM_W(-0X722C, ctx->r1) = 0;
L_802C6888:
    // 0x802C6888: andi        $t4, $v0, 0x200
    ctx->r12 = ctx->r2 & 0X200;
    // 0x802C688C: beql        $t4, $zero, L_802C68B4
    if (ctx->r12 == 0) {
        // 0x802C6890: andi        $t7, $v0, 0x100
        ctx->r15 = ctx->r2 & 0X100;
            goto L_802C68B4;
    }
    goto skip_1;
    // 0x802C6890: andi        $t7, $v0, 0x100
    ctx->r15 = ctx->r2 & 0X100;
    skip_1:
    // 0x802C6894: lui         $v0, 0x802D
    ctx->r2 = S32(0X802D << 16);
    // 0x802C6898: addiu       $v0, $v0, -0x723C
    ctx->r2 = ADD32(ctx->r2, -0X723C);
    // 0x802C689C: lw          $t5, 0x0($v0)
    ctx->r13 = MEM_W(ctx->r2, 0X0);
    // 0x802C68A0: addiu       $a2, $zero, 0x3
    ctx->r6 = ADD32(0, 0X3);
    // 0x802C68A4: xori        $t6, $t5, 0x1
    ctx->r14 = ctx->r13 ^ 0X1;
    // 0x802C68A8: b           L_802C69B8
    // 0x802C68AC: sw          $t6, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r14;
        goto L_802C69B8;
    // 0x802C68AC: sw          $t6, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r14;
    // 0x802C68B0: andi        $t7, $v0, 0x100
    ctx->r15 = ctx->r2 & 0X100;
L_802C68B4:
    // 0x802C68B4: beq         $t7, $zero, L_802C69B8
    if (ctx->r15 == 0) {
        // 0x802C68B8: lui         $v0, 0x802D
        ctx->r2 = S32(0X802D << 16);
            goto L_802C69B8;
    }
    // 0x802C68B8: lui         $v0, 0x802D
    ctx->r2 = S32(0X802D << 16);
    // 0x802C68BC: addiu       $v0, $v0, -0x723C
    ctx->r2 = ADD32(ctx->r2, -0X723C);
    // 0x802C68C0: lw          $t8, 0x0($v0)
    ctx->r24 = MEM_W(ctx->r2, 0X0);
    // 0x802C68C4: addiu       $a2, $zero, 0x4
    ctx->r6 = ADD32(0, 0X4);
    // 0x802C68C8: xori        $t9, $t8, 0x1
    ctx->r25 = ctx->r24 ^ 0X1;
    // 0x802C68CC: b           L_802C69B8
    // 0x802C68D0: sw          $t9, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r25;
        goto L_802C69B8;
    // 0x802C68D0: sw          $t9, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r25;
L_802C68D4:
    // 0x802C68D4: lui         $at, 0x40A0
    ctx->r1 = S32(0X40A0 << 16);
    // 0x802C68D8: mtc1        $at, $f12
    ctx->f12.u32l = ctx->r1;
    // 0x802C68DC: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C68E0: addiu       $v1, $v1, -0x7234
    ctx->r3 = ADD32(ctx->r3, -0X7234);
    // 0x802C68E4: sw          $a1, -0x7238($at)
    MEM_W(-0X7238, ctx->r1) = ctx->r5;
    // 0x802C68E8: lw          $t0, 0x0($v1)
    ctx->r8 = MEM_W(ctx->r3, 0X0);
    // 0x802C68EC: lui         $at, 0x4335
    ctx->r1 = S32(0X4335 << 16);
    // 0x802C68F0: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x802C68F4: addiu       $v0, $t0, 0x1
    ctx->r2 = ADD32(ctx->r8, 0X1);
    // 0x802C68F8: mtc1        $v0, $f4
    ctx->f4.u32l = ctx->r2;
    // 0x802C68FC: addiu       $t2, $zero, 0x5
    ctx->r10 = ADD32(0, 0X5);
    // 0x802C6900: subu        $t3, $t2, $v0
    ctx->r11 = SUB32(ctx->r10, ctx->r2);
    // 0x802C6904: cvt.s.w     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
    // 0x802C6908: mtc1        $t3, $f16
    ctx->f16.u32l = ctx->r11;
    // 0x802C690C: sw          $v0, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r2;
    // 0x802C6910: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C6914: addiu       $t4, $zero, 0x4
    ctx->r12 = ADD32(0, 0X4);
    // 0x802C6918: cvt.s.w     $f18, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    ctx->f18.fl = CVT_S_W(ctx->f16.u32l);
    // 0x802C691C: div.s       $f0, $f6, $f12
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f0.fl = DIV_S(ctx->f6.fl, ctx->f12.fl);
    // 0x802C6920: div.s       $f2, $f18, $f12
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f2.fl = DIV_S(ctx->f18.fl, ctx->f12.fl);
    // 0x802C6924: mul.s       $f10, $f8, $f0
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f10.fl = MUL_S(ctx->f8.fl, ctx->f0.fl);
    // 0x802C6928: trunc.w.s   $f16, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    ctx->f16.u32l = TRUNC_W_S(ctx->f10.fl);
    // 0x802C692C: mfc1        $t5, $f16
    ctx->r13 = (int32_t)ctx->f16.u32l;
    // 0x802C6930: nop

    // 0x802C6934: addiu       $t6, $t5, 0x1F
    ctx->r14 = ADD32(ctx->r13, 0X1F);
    // 0x802C6938: sw          $t6, -0x7150($at)
    MEM_W(-0X7150, ctx->r1) = ctx->r14;
    // 0x802C693C: lui         $at, 0x41A0
    ctx->r1 = S32(0X41A0 << 16);
    // 0x802C6940: mtc1        $at, $f18
    ctx->f18.u32l = ctx->r1;
    // 0x802C6944: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C6948: mul.s       $f4, $f18, $f0
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f4.fl = MUL_S(ctx->f18.fl, ctx->f0.fl);
    // 0x802C694C: trunc.w.s   $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.u32l = TRUNC_W_S(ctx->f4.fl);
    // 0x802C6950: mfc1        $t8, $f6
    ctx->r24 = (int32_t)ctx->f6.u32l;
    // 0x802C6954: nop

    // 0x802C6958: addiu       $t9, $t8, 0x89
    ctx->r25 = ADD32(ctx->r24, 0X89);
    // 0x802C695C: sw          $t9, -0x714C($at)
    MEM_W(-0X714C, ctx->r1) = ctx->r25;
    // 0x802C6960: lui         $at, 0x43B5
    ctx->r1 = S32(0X43B5 << 16);
    // 0x802C6964: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x802C6968: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C696C: mul.s       $f10, $f8, $f2
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f10.fl = MUL_S(ctx->f8.fl, ctx->f2.fl);
    // 0x802C6970: trunc.w.s   $f16, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    ctx->f16.u32l = TRUNC_W_S(ctx->f10.fl);
    // 0x802C6974: mfc1        $t1, $f16
    ctx->r9 = (int32_t)ctx->f16.u32l;
    // 0x802C6978: nop

    // 0x802C697C: sw          $t1, -0x7148($at)
    MEM_W(-0X7148, ctx->r1) = ctx->r9;
    // 0x802C6980: lui         $at, 0x4220
    ctx->r1 = S32(0X4220 << 16);
    // 0x802C6984: mtc1        $at, $f18
    ctx->f18.u32l = ctx->r1;
    // 0x802C6988: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C698C: mul.s       $f4, $f18, $f2
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f4.fl = MUL_S(ctx->f18.fl, ctx->f2.fl);
    // 0x802C6990: trunc.w.s   $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.u32l = TRUNC_W_S(ctx->f4.fl);
    // 0x802C6994: mfc1        $t3, $f6
    ctx->r11 = (int32_t)ctx->f6.u32l;
    // 0x802C6998: nop

    // 0x802C699C: sw          $t3, -0x7144($at)
    MEM_W(-0X7144, ctx->r1) = ctx->r11;
    // 0x802C69A0: slti        $at, $v0, 0x5
    ctx->r1 = SIGNED(ctx->r2) < 0X5 ? 1 : 0;
    // 0x802C69A4: bnel        $at, $zero, L_802C69BC
    if (ctx->r1 != 0) {
        // 0x802C69A8: lw          $ra, 0x14($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X14);
            goto L_802C69BC;
    }
    goto skip_2;
    // 0x802C69A8: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    skip_2:
    // 0x802C69AC: sw          $zero, 0x0($a0)
    MEM_W(0X0, ctx->r4) = 0;
    // 0x802C69B0: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C69B4: sw          $t4, -0x19C0($at)
    MEM_W(-0X19C0, ctx->r1) = ctx->r12;
L_802C69B8:
    // 0x802C69B8: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C69BC:
    // 0x802C69BC: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x802C69C0: or          $v0, $a2, $zero
    ctx->r2 = ctx->r6 | 0;
    // 0x802C69C4: jr          $ra
    // 0x802C69C8: nop

    return;
    // 0x802C69C8: nop

;}
RECOMP_FUNC void func_i13_802C69CC(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C69CC: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x802C69D0: lhu         $v0, -0x19A6($v0)
    ctx->r2 = MEM_HU(ctx->r2, -0X19A6);
    // 0x802C69D4: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x802C69D8: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x802C69DC: andi        $t6, $v0, 0xB000
    ctx->r14 = ctx->r2 & 0XB000;
    // 0x802C69E0: beq         $t6, $zero, L_802C6A30
    if (ctx->r14 == 0) {
        // 0x802C69E4: or          $v1, $zero, $zero
        ctx->r3 = 0 | 0;
            goto L_802C6A30;
    }
    // 0x802C69E4: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
    // 0x802C69E8: lui         $v0, 0x802D
    ctx->r2 = S32(0X802D << 16);
    // 0x802C69EC: addiu       $v0, $v0, -0x7290
    ctx->r2 = ADD32(ctx->r2, -0X7290);
    // 0x802C69F0: lw          $t7, 0x0($v0)
    ctx->r15 = MEM_W(ctx->r2, 0X0);
    // 0x802C69F4: addiu       $v1, $zero, 0x1
    ctx->r3 = ADD32(0, 0X1);
    // 0x802C69F8: addiu       $t9, $zero, 0x2
    ctx->r25 = ADD32(0, 0X2);
    // 0x802C69FC: bne         $t7, $zero, L_802C6A28
    if (ctx->r15 != 0) {
        // 0x802C6A00: lui         $at, 0x801D
        ctx->r1 = S32(0X801D << 16);
            goto L_802C6A28;
    }
    // 0x802C6A00: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C6A04: addiu       $v1, $zero, 0x5
    ctx->r3 = ADD32(0, 0X5);
    // 0x802C6A08: addiu       $t8, $zero, 0x9
    ctx->r24 = ADD32(0, 0X9);
    // 0x802C6A0C: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C6A10: sw          $t8, -0x19C0($at)
    MEM_W(-0X19C0, ctx->r1) = ctx->r24;
    // 0x802C6A14: sw          $v1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r3;
    // 0x802C6A18: jal         0x802C82A4
    // 0x802C6A1C: addiu       $a0, $zero, 0x4
    ctx->r4 = ADD32(0, 0X4);
    func_i13_802C82A4(rdram, ctx);
        goto after_0;
    // 0x802C6A1C: addiu       $a0, $zero, 0x4
    ctx->r4 = ADD32(0, 0X4);
    after_0:
    // 0x802C6A20: b           L_802C6AA8
    // 0x802C6A24: lw          $v1, 0x1C($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X1C);
        goto L_802C6AA8;
    // 0x802C6A24: lw          $v1, 0x1C($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X1C);
L_802C6A28:
    // 0x802C6A28: b           L_802C6AA8
    // 0x802C6A2C: sw          $t9, -0x19C0($at)
    MEM_W(-0X19C0, ctx->r1) = ctx->r25;
        goto L_802C6AA8;
    // 0x802C6A2C: sw          $t9, -0x19C0($at)
    MEM_W(-0X19C0, ctx->r1) = ctx->r25;
L_802C6A30:
    // 0x802C6A30: andi        $t0, $v0, 0x4000
    ctx->r8 = ctx->r2 & 0X4000;
    // 0x802C6A34: beq         $t0, $zero, L_802C6A50
    if (ctx->r8 == 0) {
        // 0x802C6A38: andi        $t2, $v0, 0x200
        ctx->r10 = ctx->r2 & 0X200;
            goto L_802C6A50;
    }
    // 0x802C6A38: andi        $t2, $v0, 0x200
    ctx->r10 = ctx->r2 & 0X200;
    // 0x802C6A3C: addiu       $t1, $zero, 0x2
    ctx->r9 = ADD32(0, 0X2);
    // 0x802C6A40: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C6A44: addiu       $v1, $zero, 0x2
    ctx->r3 = ADD32(0, 0X2);
    // 0x802C6A48: b           L_802C6AA8
    // 0x802C6A4C: sw          $t1, -0x19C0($at)
    MEM_W(-0X19C0, ctx->r1) = ctx->r9;
        goto L_802C6AA8;
    // 0x802C6A4C: sw          $t1, -0x19C0($at)
    MEM_W(-0X19C0, ctx->r1) = ctx->r9;
L_802C6A50:
    // 0x802C6A50: beq         $t2, $zero, L_802C6A80
    if (ctx->r10 == 0) {
        // 0x802C6A54: andi        $t7, $v0, 0x100
        ctx->r15 = ctx->r2 & 0X100;
            goto L_802C6A80;
    }
    // 0x802C6A54: andi        $t7, $v0, 0x100
    ctx->r15 = ctx->r2 & 0X100;
    // 0x802C6A58: lui         $v0, 0x802D
    ctx->r2 = S32(0X802D << 16);
    // 0x802C6A5C: addiu       $v0, $v0, -0x7290
    ctx->r2 = ADD32(ctx->r2, -0X7290);
    // 0x802C6A60: lw          $t3, 0x0($v0)
    ctx->r11 = MEM_W(ctx->r2, 0X0);
    // 0x802C6A64: addiu       $v1, $zero, 0x3
    ctx->r3 = ADD32(0, 0X3);
    // 0x802C6A68: addiu       $t6, $zero, 0x1
    ctx->r14 = ADD32(0, 0X1);
    // 0x802C6A6C: addiu       $t4, $t3, -0x1
    ctx->r12 = ADD32(ctx->r11, -0X1);
    // 0x802C6A70: bgez        $t4, L_802C6AA8
    if (SIGNED(ctx->r12) >= 0) {
        // 0x802C6A74: sw          $t4, 0x0($v0)
        MEM_W(0X0, ctx->r2) = ctx->r12;
            goto L_802C6AA8;
    }
    // 0x802C6A74: sw          $t4, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r12;
    // 0x802C6A78: b           L_802C6AA8
    // 0x802C6A7C: sw          $t6, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r14;
        goto L_802C6AA8;
    // 0x802C6A7C: sw          $t6, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r14;
L_802C6A80:
    // 0x802C6A80: beq         $t7, $zero, L_802C6AA8
    if (ctx->r15 == 0) {
        // 0x802C6A84: lui         $v0, 0x802D
        ctx->r2 = S32(0X802D << 16);
            goto L_802C6AA8;
    }
    // 0x802C6A84: lui         $v0, 0x802D
    ctx->r2 = S32(0X802D << 16);
    // 0x802C6A88: addiu       $v0, $v0, -0x7290
    ctx->r2 = ADD32(ctx->r2, -0X7290);
    // 0x802C6A8C: lw          $t8, 0x0($v0)
    ctx->r24 = MEM_W(ctx->r2, 0X0);
    // 0x802C6A90: addiu       $v1, $zero, 0x4
    ctx->r3 = ADD32(0, 0X4);
    // 0x802C6A94: addiu       $t9, $t8, 0x1
    ctx->r25 = ADD32(ctx->r24, 0X1);
    // 0x802C6A98: slti        $at, $t9, 0x2
    ctx->r1 = SIGNED(ctx->r25) < 0X2 ? 1 : 0;
    // 0x802C6A9C: bne         $at, $zero, L_802C6AA8
    if (ctx->r1 != 0) {
        // 0x802C6AA0: sw          $t9, 0x0($v0)
        MEM_W(0X0, ctx->r2) = ctx->r25;
            goto L_802C6AA8;
    }
    // 0x802C6AA0: sw          $t9, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r25;
    // 0x802C6AA4: sw          $zero, 0x0($v0)
    MEM_W(0X0, ctx->r2) = 0;
L_802C6AA8:
    // 0x802C6AA8: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x802C6AAC: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x802C6AB0: or          $v0, $v1, $zero
    ctx->r2 = ctx->r3 | 0;
    // 0x802C6AB4: jr          $ra
    // 0x802C6AB8: nop

    return;
    // 0x802C6AB8: nop

;}
RECOMP_FUNC void func_i13_802C6ABC(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C6ABC: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x802C6AC0: lhu         $v0, -0x19A6($v0)
    ctx->r2 = MEM_HU(ctx->r2, -0X19A6);
    // 0x802C6AC4: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x802C6AC8: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C6ACC: andi        $t6, $v0, 0xB000
    ctx->r14 = ctx->r2 & 0XB000;
    // 0x802C6AD0: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x802C6AD4: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
    // 0x802C6AD8: beq         $t6, $zero, L_802C6B30
    if (ctx->r14 == 0) {
        // 0x802C6ADC: sw          $zero, -0x7280($at)
        MEM_W(-0X7280, ctx->r1) = 0;
            goto L_802C6B30;
    }
    // 0x802C6ADC: sw          $zero, -0x7280($at)
    MEM_W(-0X7280, ctx->r1) = 0;
    // 0x802C6AE0: lui         $v0, 0x802D
    ctx->r2 = S32(0X802D << 16);
    // 0x802C6AE4: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C6AE8: addiu       $v0, $v0, -0x7290
    ctx->r2 = ADD32(ctx->r2, -0X7290);
    // 0x802C6AEC: sw          $zero, -0x727C($at)
    MEM_W(-0X727C, ctx->r1) = 0;
    // 0x802C6AF0: lw          $t7, 0x0($v0)
    ctx->r15 = MEM_W(ctx->r2, 0X0);
    // 0x802C6AF4: addiu       $v1, $zero, 0x1
    ctx->r3 = ADD32(0, 0X1);
    // 0x802C6AF8: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C6AFC: bne         $t7, $zero, L_802C6B28
    if (ctx->r15 != 0) {
        // 0x802C6B00: addiu       $t9, $zero, 0x1
        ctx->r25 = ADD32(0, 0X1);
            goto L_802C6B28;
    }
    // 0x802C6B00: addiu       $t9, $zero, 0x1
    ctx->r25 = ADD32(0, 0X1);
    // 0x802C6B04: addiu       $v1, $zero, 0x5
    ctx->r3 = ADD32(0, 0X5);
    // 0x802C6B08: addiu       $t8, $zero, 0xA
    ctx->r24 = ADD32(0, 0XA);
    // 0x802C6B0C: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C6B10: sw          $t8, -0x19C0($at)
    MEM_W(-0X19C0, ctx->r1) = ctx->r24;
    // 0x802C6B14: sw          $v1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r3;
    // 0x802C6B18: jal         0x802C82A4
    // 0x802C6B1C: addiu       $a0, $zero, 0x3
    ctx->r4 = ADD32(0, 0X3);
    func_i13_802C82A4(rdram, ctx);
        goto after_0;
    // 0x802C6B1C: addiu       $a0, $zero, 0x3
    ctx->r4 = ADD32(0, 0X3);
    after_0:
    // 0x802C6B20: b           L_802C6BB0
    // 0x802C6B24: lw          $v1, 0x1C($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X1C);
        goto L_802C6BB0;
    // 0x802C6B24: lw          $v1, 0x1C($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X1C);
L_802C6B28:
    // 0x802C6B28: b           L_802C6BB0
    // 0x802C6B2C: sw          $t9, -0x19C0($at)
    MEM_W(-0X19C0, ctx->r1) = ctx->r25;
        goto L_802C6BB0;
    // 0x802C6B2C: sw          $t9, -0x19C0($at)
    MEM_W(-0X19C0, ctx->r1) = ctx->r25;
L_802C6B30:
    // 0x802C6B30: andi        $t0, $v0, 0x4000
    ctx->r8 = ctx->r2 & 0X4000;
    // 0x802C6B34: beq         $t0, $zero, L_802C6B58
    if (ctx->r8 == 0) {
        // 0x802C6B38: andi        $t2, $v0, 0x200
        ctx->r10 = ctx->r2 & 0X200;
            goto L_802C6B58;
    }
    // 0x802C6B38: andi        $t2, $v0, 0x200
    ctx->r10 = ctx->r2 & 0X200;
    // 0x802C6B3C: addiu       $t1, $zero, 0x3
    ctx->r9 = ADD32(0, 0X3);
    // 0x802C6B40: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C6B44: sw          $t1, -0x19C0($at)
    MEM_W(-0X19C0, ctx->r1) = ctx->r9;
    // 0x802C6B48: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C6B4C: addiu       $v1, $zero, 0x2
    ctx->r3 = ADD32(0, 0X2);
    // 0x802C6B50: b           L_802C6BB0
    // 0x802C6B54: sw          $zero, -0x727C($at)
    MEM_W(-0X727C, ctx->r1) = 0;
        goto L_802C6BB0;
    // 0x802C6B54: sw          $zero, -0x727C($at)
    MEM_W(-0X727C, ctx->r1) = 0;
L_802C6B58:
    // 0x802C6B58: beq         $t2, $zero, L_802C6B88
    if (ctx->r10 == 0) {
        // 0x802C6B5C: andi        $t7, $v0, 0x100
        ctx->r15 = ctx->r2 & 0X100;
            goto L_802C6B88;
    }
    // 0x802C6B5C: andi        $t7, $v0, 0x100
    ctx->r15 = ctx->r2 & 0X100;
    // 0x802C6B60: lui         $v0, 0x802D
    ctx->r2 = S32(0X802D << 16);
    // 0x802C6B64: addiu       $v0, $v0, -0x7290
    ctx->r2 = ADD32(ctx->r2, -0X7290);
    // 0x802C6B68: lw          $t3, 0x0($v0)
    ctx->r11 = MEM_W(ctx->r2, 0X0);
    // 0x802C6B6C: addiu       $v1, $zero, 0x3
    ctx->r3 = ADD32(0, 0X3);
    // 0x802C6B70: addiu       $t6, $zero, 0x1
    ctx->r14 = ADD32(0, 0X1);
    // 0x802C6B74: addiu       $t4, $t3, -0x1
    ctx->r12 = ADD32(ctx->r11, -0X1);
    // 0x802C6B78: bgez        $t4, L_802C6BB0
    if (SIGNED(ctx->r12) >= 0) {
        // 0x802C6B7C: sw          $t4, 0x0($v0)
        MEM_W(0X0, ctx->r2) = ctx->r12;
            goto L_802C6BB0;
    }
    // 0x802C6B7C: sw          $t4, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r12;
    // 0x802C6B80: b           L_802C6BB0
    // 0x802C6B84: sw          $t6, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r14;
        goto L_802C6BB0;
    // 0x802C6B84: sw          $t6, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r14;
L_802C6B88:
    // 0x802C6B88: beq         $t7, $zero, L_802C6BB0
    if (ctx->r15 == 0) {
        // 0x802C6B8C: lui         $v0, 0x802D
        ctx->r2 = S32(0X802D << 16);
            goto L_802C6BB0;
    }
    // 0x802C6B8C: lui         $v0, 0x802D
    ctx->r2 = S32(0X802D << 16);
    // 0x802C6B90: addiu       $v0, $v0, -0x7290
    ctx->r2 = ADD32(ctx->r2, -0X7290);
    // 0x802C6B94: lw          $t8, 0x0($v0)
    ctx->r24 = MEM_W(ctx->r2, 0X0);
    // 0x802C6B98: addiu       $v1, $zero, 0x4
    ctx->r3 = ADD32(0, 0X4);
    // 0x802C6B9C: addiu       $t9, $t8, 0x1
    ctx->r25 = ADD32(ctx->r24, 0X1);
    // 0x802C6BA0: slti        $at, $t9, 0x2
    ctx->r1 = SIGNED(ctx->r25) < 0X2 ? 1 : 0;
    // 0x802C6BA4: bne         $at, $zero, L_802C6BB0
    if (ctx->r1 != 0) {
        // 0x802C6BA8: sw          $t9, 0x0($v0)
        MEM_W(0X0, ctx->r2) = ctx->r25;
            goto L_802C6BB0;
    }
    // 0x802C6BA8: sw          $t9, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r25;
    // 0x802C6BAC: sw          $zero, 0x0($v0)
    MEM_W(0X0, ctx->r2) = 0;
L_802C6BB0:
    // 0x802C6BB0: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x802C6BB4: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x802C6BB8: or          $v0, $v1, $zero
    ctx->r2 = ctx->r3 | 0;
    // 0x802C6BBC: jr          $ra
    // 0x802C6BC0: nop

    return;
    // 0x802C6BC0: nop

;}
RECOMP_FUNC void func_i13_802C6BC4(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C6BC4: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x802C6BC8: lhu         $v0, -0x19A6($v0)
    ctx->r2 = MEM_HU(ctx->r2, -0X19A6);
    // 0x802C6BCC: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x802C6BD0: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x802C6BD4: andi        $t6, $v0, 0xB000
    ctx->r14 = ctx->r2 & 0XB000;
    // 0x802C6BD8: beq         $t6, $zero, L_802C6C40
    if (ctx->r14 == 0) {
        // 0x802C6BDC: or          $v1, $zero, $zero
        ctx->r3 = 0 | 0;
            goto L_802C6C40;
    }
    // 0x802C6BDC: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
    // 0x802C6BE0: lui         $v0, 0x802D
    ctx->r2 = S32(0X802D << 16);
    // 0x802C6BE4: addiu       $v0, $v0, -0x7290
    ctx->r2 = ADD32(ctx->r2, -0X7290);
    // 0x802C6BE8: lw          $t7, 0x0($v0)
    ctx->r15 = MEM_W(ctx->r2, 0X0);
    // 0x802C6BEC: addiu       $v1, $zero, 0x1
    ctx->r3 = ADD32(0, 0X1);
    // 0x802C6BF0: addiu       $t9, $zero, 0x4
    ctx->r25 = ADD32(0, 0X4);
    // 0x802C6BF4: bne         $t7, $zero, L_802C6C20
    if (ctx->r15 != 0) {
        // 0x802C6BF8: lui         $at, 0x801D
        ctx->r1 = S32(0X801D << 16);
            goto L_802C6C20;
    }
    // 0x802C6BF8: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C6BFC: addiu       $v1, $zero, 0x5
    ctx->r3 = ADD32(0, 0X5);
    // 0x802C6C00: addiu       $t8, $zero, 0xB
    ctx->r24 = ADD32(0, 0XB);
    // 0x802C6C04: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C6C08: sw          $t8, -0x19C0($at)
    MEM_W(-0X19C0, ctx->r1) = ctx->r24;
    // 0x802C6C0C: sw          $v1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r3;
    // 0x802C6C10: jal         0x802C82A4
    // 0x802C6C14: addiu       $a0, $zero, 0x3
    ctx->r4 = ADD32(0, 0X3);
    func_i13_802C82A4(rdram, ctx);
        goto after_0;
    // 0x802C6C14: addiu       $a0, $zero, 0x3
    ctx->r4 = ADD32(0, 0X3);
    after_0:
    // 0x802C6C18: b           L_802C6CD0
    // 0x802C6C1C: lw          $v1, 0x1C($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X1C);
        goto L_802C6CD0;
    // 0x802C6C1C: lw          $v1, 0x1C($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X1C);
L_802C6C20:
    // 0x802C6C20: sw          $t9, -0x19C0($at)
    MEM_W(-0X19C0, ctx->r1) = ctx->r25;
    // 0x802C6C24: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C6C28: sw          $zero, -0x7238($at)
    MEM_W(-0X7238, ctx->r1) = 0;
    // 0x802C6C2C: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C6C30: sw          $zero, -0x722C($at)
    MEM_W(-0X722C, ctx->r1) = 0;
    // 0x802C6C34: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C6C38: b           L_802C6CD0
    // 0x802C6C3C: sw          $zero, -0x7230($at)
    MEM_W(-0X7230, ctx->r1) = 0;
        goto L_802C6CD0;
    // 0x802C6C3C: sw          $zero, -0x7230($at)
    MEM_W(-0X7230, ctx->r1) = 0;
L_802C6C40:
    // 0x802C6C40: andi        $t0, $v0, 0x4000
    ctx->r8 = ctx->r2 & 0X4000;
    // 0x802C6C44: beq         $t0, $zero, L_802C6C78
    if (ctx->r8 == 0) {
        // 0x802C6C48: andi        $t2, $v0, 0x200
        ctx->r10 = ctx->r2 & 0X200;
            goto L_802C6C78;
    }
    // 0x802C6C48: andi        $t2, $v0, 0x200
    ctx->r10 = ctx->r2 & 0X200;
    // 0x802C6C4C: addiu       $t1, $zero, 0x4
    ctx->r9 = ADD32(0, 0X4);
    // 0x802C6C50: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C6C54: sw          $t1, -0x19C0($at)
    MEM_W(-0X19C0, ctx->r1) = ctx->r9;
    // 0x802C6C58: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C6C5C: sw          $zero, -0x7238($at)
    MEM_W(-0X7238, ctx->r1) = 0;
    // 0x802C6C60: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C6C64: sw          $zero, -0x722C($at)
    MEM_W(-0X722C, ctx->r1) = 0;
    // 0x802C6C68: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C6C6C: addiu       $v1, $zero, 0x2
    ctx->r3 = ADD32(0, 0X2);
    // 0x802C6C70: b           L_802C6CD0
    // 0x802C6C74: sw          $zero, -0x7230($at)
    MEM_W(-0X7230, ctx->r1) = 0;
        goto L_802C6CD0;
    // 0x802C6C74: sw          $zero, -0x7230($at)
    MEM_W(-0X7230, ctx->r1) = 0;
L_802C6C78:
    // 0x802C6C78: beq         $t2, $zero, L_802C6CA8
    if (ctx->r10 == 0) {
        // 0x802C6C7C: andi        $t7, $v0, 0x100
        ctx->r15 = ctx->r2 & 0X100;
            goto L_802C6CA8;
    }
    // 0x802C6C7C: andi        $t7, $v0, 0x100
    ctx->r15 = ctx->r2 & 0X100;
    // 0x802C6C80: lui         $v0, 0x802D
    ctx->r2 = S32(0X802D << 16);
    // 0x802C6C84: addiu       $v0, $v0, -0x7290
    ctx->r2 = ADD32(ctx->r2, -0X7290);
    // 0x802C6C88: lw          $t3, 0x0($v0)
    ctx->r11 = MEM_W(ctx->r2, 0X0);
    // 0x802C6C8C: addiu       $v1, $zero, 0x3
    ctx->r3 = ADD32(0, 0X3);
    // 0x802C6C90: addiu       $t6, $zero, 0x1
    ctx->r14 = ADD32(0, 0X1);
    // 0x802C6C94: addiu       $t4, $t3, -0x1
    ctx->r12 = ADD32(ctx->r11, -0X1);
    // 0x802C6C98: bgez        $t4, L_802C6CD0
    if (SIGNED(ctx->r12) >= 0) {
        // 0x802C6C9C: sw          $t4, 0x0($v0)
        MEM_W(0X0, ctx->r2) = ctx->r12;
            goto L_802C6CD0;
    }
    // 0x802C6C9C: sw          $t4, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r12;
    // 0x802C6CA0: b           L_802C6CD0
    // 0x802C6CA4: sw          $t6, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r14;
        goto L_802C6CD0;
    // 0x802C6CA4: sw          $t6, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r14;
L_802C6CA8:
    // 0x802C6CA8: beq         $t7, $zero, L_802C6CD0
    if (ctx->r15 == 0) {
        // 0x802C6CAC: lui         $v0, 0x802D
        ctx->r2 = S32(0X802D << 16);
            goto L_802C6CD0;
    }
    // 0x802C6CAC: lui         $v0, 0x802D
    ctx->r2 = S32(0X802D << 16);
    // 0x802C6CB0: addiu       $v0, $v0, -0x7290
    ctx->r2 = ADD32(ctx->r2, -0X7290);
    // 0x802C6CB4: lw          $t8, 0x0($v0)
    ctx->r24 = MEM_W(ctx->r2, 0X0);
    // 0x802C6CB8: addiu       $v1, $zero, 0x4
    ctx->r3 = ADD32(0, 0X4);
    // 0x802C6CBC: addiu       $t9, $t8, 0x1
    ctx->r25 = ADD32(ctx->r24, 0X1);
    // 0x802C6CC0: slti        $at, $t9, 0x2
    ctx->r1 = SIGNED(ctx->r25) < 0X2 ? 1 : 0;
    // 0x802C6CC4: bne         $at, $zero, L_802C6CD0
    if (ctx->r1 != 0) {
        // 0x802C6CC8: sw          $t9, 0x0($v0)
        MEM_W(0X0, ctx->r2) = ctx->r25;
            goto L_802C6CD0;
    }
    // 0x802C6CC8: sw          $t9, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r25;
    // 0x802C6CCC: sw          $zero, 0x0($v0)
    MEM_W(0X0, ctx->r2) = 0;
L_802C6CD0:
    // 0x802C6CD0: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x802C6CD4: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x802C6CD8: or          $v0, $v1, $zero
    ctx->r2 = ctx->r3 | 0;
    // 0x802C6CDC: jr          $ra
    // 0x802C6CE0: nop

    return;
    // 0x802C6CE0: nop

;}
RECOMP_FUNC void func_i13_802C6CE4(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C6CE4: lui         $v0, 0x802D
    ctx->r2 = S32(0X802D << 16);
    // 0x802C6CE8: addiu       $v0, $v0, -0x7280
    ctx->r2 = ADD32(ctx->r2, -0X7280);
    // 0x802C6CEC: lw          $t6, 0x0($v0)
    ctx->r14 = MEM_W(ctx->r2, 0X0);
    // 0x802C6CF0: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x802C6CF4: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x802C6CF8: bne         $t6, $zero, L_802C6D08
    if (ctx->r14 != 0) {
        // 0x802C6CFC: or          $a1, $zero, $zero
        ctx->r5 = 0 | 0;
            goto L_802C6D08;
    }
    // 0x802C6CFC: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C6D00: b           L_802C6E38
    // 0x802C6D04: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
        goto L_802C6E38;
    // 0x802C6D04: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_802C6D08:
    // 0x802C6D08: sw          $zero, 0x0($v0)
    MEM_W(0X0, ctx->r2) = 0;
    // 0x802C6D0C: lui         $t7, 0x802D
    ctx->r15 = S32(0X802D << 16);
    // 0x802C6D10: lw          $t7, -0x72AC($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X72AC);
    // 0x802C6D14: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C6D18: sw          $zero, -0x727C($at)
    MEM_W(-0X727C, ctx->r1) = 0;
    // 0x802C6D1C: bne         $t7, $zero, L_802C6DBC
    if (ctx->r15 != 0) {
        // 0x802C6D20: lui         $t6, 0x802D
        ctx->r14 = S32(0X802D << 16);
            goto L_802C6DBC;
    }
    // 0x802C6D20: lui         $t6, 0x802D
    ctx->r14 = S32(0X802D << 16);
    // 0x802C6D24: lui         $t8, 0x802D
    ctx->r24 = S32(0X802D << 16);
    // 0x802C6D28: lw          $t8, -0x72A4($t8)
    ctx->r24 = MEM_W(ctx->r24, -0X72A4);
    // 0x802C6D2C: lui         $t0, 0x802D
    ctx->r8 = S32(0X802D << 16);
    // 0x802C6D30: lui         $t2, 0x802D
    ctx->r10 = S32(0X802D << 16);
    // 0x802C6D34: sll         $t9, $t8, 2
    ctx->r25 = S32(ctx->r24 << 2);
    // 0x802C6D38: addu        $t0, $t0, $t9
    ctx->r8 = ADD32(ctx->r8, ctx->r25);
    // 0x802C6D3C: lw          $t0, -0x7220($t0)
    ctx->r8 = MEM_W(ctx->r8, -0X7220);
    // 0x802C6D40: lw          $t2, -0x723C($t2)
    ctx->r10 = MEM_W(ctx->r10, -0X723C);
    // 0x802C6D44: lui         $a0, 0x802D
    ctx->r4 = S32(0X802D << 16);
    // 0x802C6D48: sll         $t1, $t0, 2
    ctx->r9 = S32(ctx->r8 << 2);
    // 0x802C6D4C: addu        $a0, $a0, $t1
    ctx->r4 = ADD32(ctx->r4, ctx->r9);
    // 0x802C6D50: beq         $t2, $zero, L_802C6D5C
    if (ctx->r10 == 0) {
        // 0x802C6D54: lw          $a0, -0x72A0($a0)
        ctx->r4 = MEM_W(ctx->r4, -0X72A0);
            goto L_802C6D5C;
    }
    // 0x802C6D54: lw          $a0, -0x72A0($a0)
    ctx->r4 = MEM_W(ctx->r4, -0X72A0);
    // 0x802C6D58: addiu       $a0, $a0, 0x80
    ctx->r4 = ADD32(ctx->r4, 0X80);
L_802C6D5C:
    // 0x802C6D5C: jal         0x8007D2D4
    // 0x802C6D60: sw          $a1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r5;
    func_8007D2D4(rdram, ctx);
        goto after_0;
    // 0x802C6D60: sw          $a1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r5;
    after_0:
    // 0x802C6D64: lui         $v1, 0x802D
    ctx->r3 = S32(0X802D << 16);
    // 0x802C6D68: addiu       $v1, $v1, -0x728C
    ctx->r3 = ADD32(ctx->r3, -0X728C);
    // 0x802C6D6C: sw          $v0, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r2;
    // 0x802C6D70: bne         $v0, $zero, L_802C6D94
    if (ctx->r2 != 0) {
        // 0x802C6D74: lw          $a1, 0x1C($sp)
        ctx->r5 = MEM_W(ctx->r29, 0X1C);
            goto L_802C6D94;
    }
    // 0x802C6D74: lw          $a1, 0x1C($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X1C);
    // 0x802C6D78: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C6D7C: sw          $zero, -0x19C0($at)
    MEM_W(-0X19C0, ctx->r1) = 0;
    // 0x802C6D80: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C6D84: addiu       $t4, $zero, 0x3
    ctx->r12 = ADD32(0, 0X3);
    // 0x802C6D88: sw          $t4, -0x7284($at)
    MEM_W(-0X7284, ctx->r1) = ctx->r12;
    // 0x802C6D8C: b           L_802C6DA0
    // 0x802C6D90: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
        goto L_802C6DA0;
    // 0x802C6D90: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
L_802C6D94:
    // 0x802C6D94: addiu       $t5, $zero, 0x4
    ctx->r13 = ADD32(0, 0X4);
    // 0x802C6D98: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C6D9C: sw          $t5, -0x19C0($at)
    MEM_W(-0X19C0, ctx->r1) = ctx->r13;
L_802C6DA0:
    // 0x802C6DA0: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C6DA4: sw          $zero, -0x7238($at)
    MEM_W(-0X7238, ctx->r1) = 0;
    // 0x802C6DA8: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C6DAC: sw          $zero, -0x722C($at)
    MEM_W(-0X722C, ctx->r1) = 0;
    // 0x802C6DB0: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C6DB4: b           L_802C6E24
    // 0x802C6DB8: sw          $zero, -0x7230($at)
    MEM_W(-0X7230, ctx->r1) = 0;
        goto L_802C6E24;
    // 0x802C6DB8: sw          $zero, -0x7230($at)
    MEM_W(-0X7230, ctx->r1) = 0;
L_802C6DBC:
    // 0x802C6DBC: lw          $t6, -0x72A4($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X72A4);
    // 0x802C6DC0: lui         $t8, 0x802D
    ctx->r24 = S32(0X802D << 16);
    // 0x802C6DC4: lui         $a0, 0x802D
    ctx->r4 = S32(0X802D << 16);
    // 0x802C6DC8: sll         $t7, $t6, 2
    ctx->r15 = S32(ctx->r14 << 2);
    // 0x802C6DCC: addu        $t8, $t8, $t7
    ctx->r24 = ADD32(ctx->r24, ctx->r15);
    // 0x802C6DD0: lw          $t8, -0x7220($t8)
    ctx->r24 = MEM_W(ctx->r24, -0X7220);
    // 0x802C6DD4: sw          $a1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r5;
    // 0x802C6DD8: sll         $t9, $t8, 2
    ctx->r25 = S32(ctx->r24 << 2);
    // 0x802C6DDC: addu        $a0, $a0, $t9
    ctx->r4 = ADD32(ctx->r4, ctx->r25);
    // 0x802C6DE0: jal         0x8007D614
    // 0x802C6DE4: lw          $a0, -0x72A0($a0)
    ctx->r4 = MEM_W(ctx->r4, -0X72A0);
    func_8007D614(rdram, ctx);
        goto after_1;
    // 0x802C6DE4: lw          $a0, -0x72A0($a0)
    ctx->r4 = MEM_W(ctx->r4, -0X72A0);
    after_1:
    // 0x802C6DE8: lui         $v1, 0x802D
    ctx->r3 = S32(0X802D << 16);
    // 0x802C6DEC: addiu       $v1, $v1, -0x728C
    ctx->r3 = ADD32(ctx->r3, -0X728C);
    // 0x802C6DF0: sw          $v0, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r2;
    // 0x802C6DF4: bne         $v0, $zero, L_802C6E18
    if (ctx->r2 != 0) {
        // 0x802C6DF8: lw          $a1, 0x1C($sp)
        ctx->r5 = MEM_W(ctx->r29, 0X1C);
            goto L_802C6E18;
    }
    // 0x802C6DF8: lw          $a1, 0x1C($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X1C);
    // 0x802C6DFC: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C6E00: sw          $zero, -0x19C0($at)
    MEM_W(-0X19C0, ctx->r1) = 0;
    // 0x802C6E04: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C6E08: addiu       $t1, $zero, 0x3
    ctx->r9 = ADD32(0, 0X3);
    // 0x802C6E0C: sw          $t1, -0x7284($at)
    MEM_W(-0X7284, ctx->r1) = ctx->r9;
    // 0x802C6E10: b           L_802C6E24
    // 0x802C6E14: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
        goto L_802C6E24;
    // 0x802C6E14: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
L_802C6E18:
    // 0x802C6E18: addiu       $t2, $zero, 0x4
    ctx->r10 = ADD32(0, 0X4);
    // 0x802C6E1C: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C6E20: sw          $t2, -0x19C0($at)
    MEM_W(-0X19C0, ctx->r1) = ctx->r10;
L_802C6E24:
    // 0x802C6E24: beql        $a1, $zero, L_802C6E38
    if (ctx->r5 == 0) {
        // 0x802C6E28: or          $v0, $zero, $zero
        ctx->r2 = 0 | 0;
            goto L_802C6E38;
    }
    goto skip_0;
    // 0x802C6E28: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    skip_0:
    // 0x802C6E2C: jal         0x800C3E6C
    // 0x802C6E30: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    func_800C3E6C(rdram, ctx);
        goto after_2;
    // 0x802C6E30: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    after_2:
    // 0x802C6E34: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_802C6E38:
    // 0x802C6E38: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x802C6E3C: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x802C6E40: jr          $ra
    // 0x802C6E44: nop

    return;
    // 0x802C6E44: nop

;}
RECOMP_FUNC void func_i13_802C6E48(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C6E48: lui         $v0, 0x802D
    ctx->r2 = S32(0X802D << 16);
    // 0x802C6E4C: addiu       $v0, $v0, -0x7280
    ctx->r2 = ADD32(ctx->r2, -0X7280);
    // 0x802C6E50: lw          $t6, 0x0($v0)
    ctx->r14 = MEM_W(ctx->r2, 0X0);
    // 0x802C6E54: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x802C6E58: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x802C6E5C: bne         $t6, $zero, L_802C6E6C
    if (ctx->r14 != 0) {
        // 0x802C6E60: or          $v1, $zero, $zero
        ctx->r3 = 0 | 0;
            goto L_802C6E6C;
    }
    // 0x802C6E60: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
    // 0x802C6E64: b           L_802C6EFC
    // 0x802C6E68: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
        goto L_802C6EFC;
    // 0x802C6E68: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_802C6E6C:
    // 0x802C6E6C: sw          $zero, 0x0($v0)
    MEM_W(0X0, ctx->r2) = 0;
    // 0x802C6E70: lui         $t7, 0x802D
    ctx->r15 = S32(0X802D << 16);
    // 0x802C6E74: lw          $t7, -0x72AC($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X72AC);
    // 0x802C6E78: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C6E7C: sw          $zero, -0x727C($at)
    MEM_W(-0X727C, ctx->r1) = 0;
    // 0x802C6E80: bne         $t7, $zero, L_802C6EA4
    if (ctx->r15 != 0) {
        // 0x802C6E84: addiu       $a0, $zero, 0x5
        ctx->r4 = ADD32(0, 0X5);
            goto L_802C6EA4;
    }
    // 0x802C6E84: addiu       $a0, $zero, 0x5
    ctx->r4 = ADD32(0, 0X5);
    // 0x802C6E88: jal         0x8007D2D4
    // 0x802C6E8C: sw          $v1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r3;
    func_8007D2D4(rdram, ctx);
        goto after_0;
    // 0x802C6E8C: sw          $v1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r3;
    after_0:
    // 0x802C6E90: lui         $a0, 0x802D
    ctx->r4 = S32(0X802D << 16);
    // 0x802C6E94: addiu       $a0, $a0, -0x728C
    ctx->r4 = ADD32(ctx->r4, -0X728C);
    // 0x802C6E98: sw          $v0, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r2;
    // 0x802C6E9C: b           L_802C6EC0
    // 0x802C6EA0: lw          $v1, 0x1C($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X1C);
        goto L_802C6EC0;
    // 0x802C6EA0: lw          $v1, 0x1C($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X1C);
L_802C6EA4:
    // 0x802C6EA4: addiu       $a0, $zero, 0x5
    ctx->r4 = ADD32(0, 0X5);
    // 0x802C6EA8: jal         0x8007D614
    // 0x802C6EAC: sw          $v1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r3;
    func_8007D614(rdram, ctx);
        goto after_1;
    // 0x802C6EAC: sw          $v1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r3;
    after_1:
    // 0x802C6EB0: lui         $a0, 0x802D
    ctx->r4 = S32(0X802D << 16);
    // 0x802C6EB4: addiu       $a0, $a0, -0x728C
    ctx->r4 = ADD32(ctx->r4, -0X728C);
    // 0x802C6EB8: sw          $v0, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r2;
    // 0x802C6EBC: lw          $v1, 0x1C($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X1C);
L_802C6EC0:
    // 0x802C6EC0: lw          $t8, 0x0($a0)
    ctx->r24 = MEM_W(ctx->r4, 0X0);
    // 0x802C6EC4: addiu       $t9, $zero, 0x1
    ctx->r25 = ADD32(0, 0X1);
    // 0x802C6EC8: addiu       $t0, $zero, 0x3
    ctx->r8 = ADD32(0, 0X3);
    // 0x802C6ECC: bne         $t8, $zero, L_802C6EE4
    if (ctx->r24 != 0) {
        // 0x802C6ED0: lui         $at, 0x801D
        ctx->r1 = S32(0X801D << 16);
            goto L_802C6EE4;
    }
    // 0x802C6ED0: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C6ED4: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C6ED8: sw          $t9, -0x19C0($at)
    MEM_W(-0X19C0, ctx->r1) = ctx->r25;
    // 0x802C6EDC: b           L_802C6EE8
    // 0x802C6EE0: addiu       $v1, $zero, 0x1
    ctx->r3 = ADD32(0, 0X1);
        goto L_802C6EE8;
    // 0x802C6EE0: addiu       $v1, $zero, 0x1
    ctx->r3 = ADD32(0, 0X1);
L_802C6EE4:
    // 0x802C6EE4: sw          $t0, -0x19C0($at)
    MEM_W(-0X19C0, ctx->r1) = ctx->r8;
L_802C6EE8:
    // 0x802C6EE8: beql        $v1, $zero, L_802C6EFC
    if (ctx->r3 == 0) {
        // 0x802C6EEC: or          $v0, $zero, $zero
        ctx->r2 = 0 | 0;
            goto L_802C6EFC;
    }
    goto skip_0;
    // 0x802C6EEC: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    skip_0:
    // 0x802C6EF0: jal         0x800C3E6C
    // 0x802C6EF4: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    func_800C3E6C(rdram, ctx);
        goto after_2;
    // 0x802C6EF4: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    after_2:
    // 0x802C6EF8: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_802C6EFC:
    // 0x802C6EFC: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x802C6F00: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x802C6F04: jr          $ra
    // 0x802C6F08: nop

    return;
    // 0x802C6F08: nop

;}
RECOMP_FUNC void func_i13_802C6F0C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C6F0C: lui         $v0, 0x802D
    ctx->r2 = S32(0X802D << 16);
    // 0x802C6F10: addiu       $v0, $v0, -0x7280
    ctx->r2 = ADD32(ctx->r2, -0X7280);
    // 0x802C6F14: lw          $t6, 0x0($v0)
    ctx->r14 = MEM_W(ctx->r2, 0X0);
    // 0x802C6F18: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x802C6F1C: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x802C6F20: bne         $t6, $zero, L_802C6F30
    if (ctx->r14 != 0) {
        // 0x802C6F24: sw          $zero, 0x1C($sp)
        MEM_W(0X1C, ctx->r29) = 0;
            goto L_802C6F30;
    }
    // 0x802C6F24: sw          $zero, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = 0;
    // 0x802C6F28: b           L_802C7050
    // 0x802C6F2C: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
        goto L_802C7050;
    // 0x802C6F2C: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_802C6F30:
    // 0x802C6F30: sw          $zero, 0x0($v0)
    MEM_W(0X0, ctx->r2) = 0;
    // 0x802C6F34: lui         $t7, 0x802D
    ctx->r15 = S32(0X802D << 16);
    // 0x802C6F38: lw          $t7, -0x72AC($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X72AC);
    // 0x802C6F3C: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C6F40: sw          $zero, -0x727C($at)
    MEM_W(-0X727C, ctx->r1) = 0;
    // 0x802C6F44: bne         $t7, $zero, L_802C7010
    if (ctx->r15 != 0) {
        // 0x802C6F48: nop
    
            goto L_802C7010;
    }
    // 0x802C6F48: nop

    // 0x802C6F4C: jal         0x8007BDB8
    // 0x802C6F50: nop

    func_8007BDB8(rdram, ctx);
        goto after_0;
    // 0x802C6F50: nop

    after_0:
    // 0x802C6F54: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x802C6F58: lb          $v1, -0x4D80($v1)
    ctx->r3 = MEM_B(ctx->r3, -0X4D80);
    // 0x802C6F5C: addiu       $t8, $zero, 0x1
    ctx->r24 = ADD32(0, 0X1);
    // 0x802C6F60: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C6F64: andi        $t9, $v1, 0xC0
    ctx->r25 = ctx->r3 & 0XC0;
    // 0x802C6F68: sll         $t0, $t9, 24
    ctx->r8 = S32(ctx->r25 << 24);
    // 0x802C6F6C: sra         $v1, $t0, 24
    ctx->r3 = S32(SIGNED(ctx->r8) >> 24);
    // 0x802C6F70: andi        $t2, $v1, 0x40
    ctx->r10 = ctx->r3 & 0X40;
    // 0x802C6F74: sw          $t8, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r24;
    // 0x802C6F78: beq         $t2, $zero, L_802C6F9C
    if (ctx->r10 == 0) {
        // 0x802C6F7C: sw          $zero, -0x19C0($at)
        MEM_W(-0X19C0, ctx->r1) = 0;
            goto L_802C6F9C;
    }
    // 0x802C6F7C: sw          $zero, -0x19C0($at)
    MEM_W(-0X19C0, ctx->r1) = 0;
    // 0x802C6F80: addiu       $t3, $zero, 0x1
    ctx->r11 = ADD32(0, 0X1);
    // 0x802C6F84: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x802C6F88: sw          $t3, -0x5614($at)
    MEM_W(-0X5614, ctx->r1) = ctx->r11;
    // 0x802C6F8C: jal         0x800C3010
    // 0x802C6F90: addiu       $a0, $zero, 0x3
    ctx->r4 = ADD32(0, 0X3);
    func_800C3010(rdram, ctx);
        goto after_1;
    // 0x802C6F90: addiu       $a0, $zero, 0x3
    ctx->r4 = ADD32(0, 0X3);
    after_1:
    // 0x802C6F94: b           L_802C6FD0
    // 0x802C6F98: nop

        goto L_802C6FD0;
    // 0x802C6F98: nop

L_802C6F9C:
    // 0x802C6F9C: andi        $t4, $v1, 0x80
    ctx->r12 = ctx->r3 & 0X80;
    // 0x802C6FA0: beq         $t4, $zero, L_802C6FC4
    if (ctx->r12 == 0) {
        // 0x802C6FA4: lui         $at, 0x800E
        ctx->r1 = S32(0X800E << 16);
            goto L_802C6FC4;
    }
    // 0x802C6FA4: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x802C6FA8: addiu       $t5, $zero, 0x2
    ctx->r13 = ADD32(0, 0X2);
    // 0x802C6FAC: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x802C6FB0: sw          $t5, -0x5614($at)
    MEM_W(-0X5614, ctx->r1) = ctx->r13;
    // 0x802C6FB4: jal         0x800C3010
    // 0x802C6FB8: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    func_800C3010(rdram, ctx);
        goto after_2;
    // 0x802C6FB8: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    after_2:
    // 0x802C6FBC: b           L_802C6FD0
    // 0x802C6FC0: nop

        goto L_802C6FD0;
    // 0x802C6FC0: nop

L_802C6FC4:
    // 0x802C6FC4: sw          $zero, -0x5614($at)
    MEM_W(-0X5614, ctx->r1) = 0;
    // 0x802C6FC8: jal         0x800C3010
    // 0x802C6FCC: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    func_800C3010(rdram, ctx);
        goto after_3;
    // 0x802C6FCC: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    after_3:
L_802C6FD0:
    // 0x802C6FD0: lui         $t6, 0x801D
    ctx->r14 = S32(0X801D << 16);
    // 0x802C6FD4: lb          $t6, -0x4D80($t6)
    ctx->r14 = MEM_B(ctx->r14, -0X4D80);
    // 0x802C6FD8: addiu       $t8, $zero, 0x1
    ctx->r24 = ADD32(0, 0X1);
    // 0x802C6FDC: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x802C6FE0: andi        $t7, $t6, 0x20
    ctx->r15 = ctx->r14 & 0X20;
    // 0x802C6FE4: beq         $t7, $zero, L_802C7000
    if (ctx->r15 == 0) {
        // 0x802C6FE8: nop
    
            goto L_802C7000;
    }
    // 0x802C6FE8: nop

    // 0x802C6FEC: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x802C6FF0: jal         0x800C3044
    // 0x802C6FF4: sw          $zero, -0x5610($at)
    MEM_W(-0X5610, ctx->r1) = 0;
    myfree(rdram, ctx);
        goto after_4;
    // 0x802C6FF4: sw          $zero, -0x5610($at)
    MEM_W(-0X5610, ctx->r1) = 0;
    after_4:
    // 0x802C6FF8: b           L_802C703C
    // 0x802C6FFC: lw          $t1, 0x1C($sp)
    ctx->r9 = MEM_W(ctx->r29, 0X1C);
        goto L_802C703C;
    // 0x802C6FFC: lw          $t1, 0x1C($sp)
    ctx->r9 = MEM_W(ctx->r29, 0X1C);
L_802C7000:
    // 0x802C7000: jal         0x800C3034
    // 0x802C7004: sw          $t8, -0x5610($at)
    MEM_W(-0X5610, ctx->r1) = ctx->r24;
    leoInitUnit_atten(rdram, ctx);
        goto after_5;
    // 0x802C7004: sw          $t8, -0x5610($at)
    MEM_W(-0X5610, ctx->r1) = ctx->r24;
    after_5:
    // 0x802C7008: b           L_802C703C
    // 0x802C700C: lw          $t1, 0x1C($sp)
    ctx->r9 = MEM_W(ctx->r29, 0X1C);
        goto L_802C703C;
    // 0x802C700C: lw          $t1, 0x1C($sp)
    ctx->r9 = MEM_W(ctx->r29, 0X1C);
L_802C7010:
    // 0x802C7010: jal         0x8007DB40
    // 0x802C7014: nop

    Save_PfsDeleteFile(rdram, ctx);
        goto after_6;
    // 0x802C7014: nop

    after_6:
    // 0x802C7018: lui         $v1, 0x802D
    ctx->r3 = S32(0X802D << 16);
    // 0x802C701C: addiu       $v1, $v1, -0x728C
    ctx->r3 = ADD32(ctx->r3, -0X728C);
    // 0x802C7020: bne         $v0, $zero, L_802C7030
    if (ctx->r2 != 0) {
        // 0x802C7024: sw          $v0, 0x0($v1)
        MEM_W(0X0, ctx->r3) = ctx->r2;
            goto L_802C7030;
    }
    // 0x802C7024: sw          $v0, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r2;
    // 0x802C7028: addiu       $t0, $zero, 0x1
    ctx->r8 = ADD32(0, 0X1);
    // 0x802C702C: sw          $t0, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r8;
L_802C7030:
    // 0x802C7030: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C7034: sw          $zero, -0x19C0($at)
    MEM_W(-0X19C0, ctx->r1) = 0;
    // 0x802C7038: lw          $t1, 0x1C($sp)
    ctx->r9 = MEM_W(ctx->r29, 0X1C);
L_802C703C:
    // 0x802C703C: beql        $t1, $zero, L_802C7050
    if (ctx->r9 == 0) {
        // 0x802C7040: or          $v0, $zero, $zero
        ctx->r2 = 0 | 0;
            goto L_802C7050;
    }
    goto skip_0;
    // 0x802C7040: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    skip_0:
    // 0x802C7044: jal         0x800C3E6C
    // 0x802C7048: addiu       $a0, $zero, 0x2
    ctx->r4 = ADD32(0, 0X2);
    func_800C3E6C(rdram, ctx);
        goto after_7;
    // 0x802C7048: addiu       $a0, $zero, 0x2
    ctx->r4 = ADD32(0, 0X2);
    after_7:
    // 0x802C704C: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_802C7050:
    // 0x802C7050: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x802C7054: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x802C7058: jr          $ra
    // 0x802C705C: nop

    return;
    // 0x802C705C: nop

;}
RECOMP_FUNC void func_i13_802C7060(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C7060: lui         $v1, 0x802D
    ctx->r3 = S32(0X802D << 16);
    // 0x802C7064: addiu       $v1, $v1, -0x7288
    ctx->r3 = ADD32(ctx->r3, -0X7288);
    // 0x802C7068: lw          $v0, 0x0($v1)
    ctx->r2 = MEM_W(ctx->r3, 0X0);
    // 0x802C706C: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x802C7070: lui         $a0, 0x802D
    ctx->r4 = S32(0X802D << 16);
    // 0x802C7074: beq         $v0, $at, L_802C709C
    if (ctx->r2 == ctx->r1) {
        // 0x802C7078: addiu       $a0, $a0, -0x7168
        ctx->r4 = ADD32(ctx->r4, -0X7168);
            goto L_802C709C;
    }
    // 0x802C7078: addiu       $a0, $a0, -0x7168
    ctx->r4 = ADD32(ctx->r4, -0X7168);
    // 0x802C707C: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x802C7080: beq         $v0, $at, L_802C70BC
    if (ctx->r2 == ctx->r1) {
        // 0x802C7084: lui         $a0, 0x802D
        ctx->r4 = S32(0X802D << 16);
            goto L_802C70BC;
    }
    // 0x802C7084: lui         $a0, 0x802D
    ctx->r4 = S32(0X802D << 16);
    // 0x802C7088: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x802C708C: beq         $v0, $at, L_802C70E4
    if (ctx->r2 == ctx->r1) {
        // 0x802C7090: nop
    
            goto L_802C70E4;
    }
    // 0x802C7090: nop

    // 0x802C7094: jr          $ra
    // 0x802C7098: nop

    return;
    // 0x802C7098: nop

L_802C709C:
    // 0x802C709C: lw          $t6, 0x0($a0)
    ctx->r14 = MEM_W(ctx->r4, 0X0);
    // 0x802C70A0: addiu       $t7, $zero, 0x2
    ctx->r15 = ADD32(0, 0X2);
    // 0x802C70A4: slti        $at, $t6, 0x5
    ctx->r1 = SIGNED(ctx->r14) < 0X5 ? 1 : 0;
    // 0x802C70A8: bne         $at, $zero, L_802C7114
    if (ctx->r1 != 0) {
        // 0x802C70AC: nop
    
            goto L_802C7114;
    }
    // 0x802C70AC: nop

    // 0x802C70B0: sw          $t7, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r15;
    // 0x802C70B4: jr          $ra
    // 0x802C70B8: sw          $zero, 0x0($a0)
    MEM_W(0X0, ctx->r4) = 0;
    return;
    // 0x802C70B8: sw          $zero, 0x0($a0)
    MEM_W(0X0, ctx->r4) = 0;
L_802C70BC:
    // 0x802C70BC: addiu       $a0, $a0, -0x7168
    ctx->r4 = ADD32(ctx->r4, -0X7168);
    // 0x802C70C0: lw          $t8, 0x0($a0)
    ctx->r24 = MEM_W(ctx->r4, 0X0);
    // 0x802C70C4: addiu       $t1, $zero, 0x3
    ctx->r9 = ADD32(0, 0X3);
    // 0x802C70C8: addiu       $t9, $t8, 0x1
    ctx->r25 = ADD32(ctx->r24, 0X1);
    // 0x802C70CC: slti        $at, $t9, 0xA
    ctx->r1 = SIGNED(ctx->r25) < 0XA ? 1 : 0;
    // 0x802C70D0: bne         $at, $zero, L_802C7114
    if (ctx->r1 != 0) {
        // 0x802C70D4: sw          $t9, 0x0($a0)
        MEM_W(0X0, ctx->r4) = ctx->r25;
            goto L_802C7114;
    }
    // 0x802C70D4: sw          $t9, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r25;
    // 0x802C70D8: sw          $t1, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r9;
    // 0x802C70DC: jr          $ra
    // 0x802C70E0: sw          $zero, 0x0($a0)
    MEM_W(0X0, ctx->r4) = 0;
    return;
    // 0x802C70E0: sw          $zero, 0x0($a0)
    MEM_W(0X0, ctx->r4) = 0;
L_802C70E4:
    // 0x802C70E4: lui         $v0, 0x802D
    ctx->r2 = S32(0X802D << 16);
    // 0x802C70E8: addiu       $v0, $v0, -0x7240
    ctx->r2 = ADD32(ctx->r2, -0X7240);
    // 0x802C70EC: lw          $t2, 0x0($v0)
    ctx->r10 = MEM_W(ctx->r2, 0X0);
    // 0x802C70F0: lui         $a0, 0x802D
    ctx->r4 = S32(0X802D << 16);
    // 0x802C70F4: addiu       $a0, $a0, -0x7168
    ctx->r4 = ADD32(ctx->r4, -0X7168);
    // 0x802C70F8: addiu       $t3, $t2, 0x1
    ctx->r11 = ADD32(ctx->r10, 0X1);
    // 0x802C70FC: slti        $at, $t3, 0x5B
    ctx->r1 = SIGNED(ctx->r11) < 0X5B ? 1 : 0;
    // 0x802C7100: bne         $at, $zero, L_802C7114
    if (ctx->r1 != 0) {
        // 0x802C7104: sw          $t3, 0x0($v0)
        MEM_W(0X0, ctx->r2) = ctx->r11;
            goto L_802C7114;
    }
    // 0x802C7104: sw          $t3, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r11;
    // 0x802C7108: sw          $zero, 0x0($v1)
    MEM_W(0X0, ctx->r3) = 0;
    // 0x802C710C: sw          $zero, 0x0($a0)
    MEM_W(0X0, ctx->r4) = 0;
    // 0x802C7110: sw          $zero, 0x0($v0)
    MEM_W(0X0, ctx->r2) = 0;
L_802C7114:
    // 0x802C7114: jr          $ra
    // 0x802C7118: nop

    return;
    // 0x802C7118: nop

;}
RECOMP_FUNC void func_i13_802C711C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C711C: lui         $a1, 0x801D
    ctx->r5 = S32(0X801D << 16);
    // 0x802C7120: lw          $a1, -0x19C0($a1)
    ctx->r5 = MEM_W(ctx->r5, -0X19C0);
    // 0x802C7124: addiu       $sp, $sp, -0x150
    ctx->r29 = ADD32(ctx->r29, -0X150);
    // 0x802C7128: sw          $ra, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r31;
    // 0x802C712C: or          $t3, $zero, $zero
    ctx->r11 = 0 | 0;
    // 0x802C7130: or          $t2, $zero, $zero
    ctx->r10 = 0 | 0;
    // 0x802C7134: beq         $a1, $zero, L_802C7140
    if (ctx->r5 == 0) {
        // 0x802C7138: or          $t5, $zero, $zero
        ctx->r13 = 0 | 0;
            goto L_802C7140;
    }
    // 0x802C7138: or          $t5, $zero, $zero
    ctx->r13 = 0 | 0;
    // 0x802C713C: addiu       $t5, $zero, 0x1
    ctx->r13 = ADD32(0, 0X1);
L_802C7140:
    // 0x802C7140: sltiu       $at, $a1, 0xC
    ctx->r1 = ctx->r5 < 0XC ? 1 : 0;
    // 0x802C7144: beq         $at, $zero, L_802C7198
    if (ctx->r1 == 0) {
        // 0x802C7148: or          $t4, $zero, $zero
        ctx->r12 = 0 | 0;
            goto L_802C7198;
    }
    // 0x802C7148: or          $t4, $zero, $zero
    ctx->r12 = 0 | 0;
    // 0x802C714C: sll         $t6, $a1, 2
    ctx->r14 = S32(ctx->r5 << 2);
    // 0x802C7150: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C7154: addu        $at, $at, $t6
    gpr jr_addend_802C715C = ctx->r14;
    ctx->r1 = ADD32(ctx->r1, ctx->r14);
    // 0x802C7158: lw          $t6, -0x71DC($at)
    ctx->r14 = ADD32(ctx->r1, -0X71DC);
    // 0x802C715C: jr          $t6
    // 0x802C7160: nop

    switch (jr_addend_802C715C >> 2) {
        case 0: goto L_802C7198; break;
        case 1: goto L_802C7198; break;
        case 2: goto L_802C7198; break;
        case 3: goto L_802C7164; break;
        case 4: goto L_802C716C; break;
        case 5: goto L_802C7194; break;
        case 6: goto L_802C7178; break;
        case 7: goto L_802C7184; break;
        case 8: goto L_802C716C; break;
        case 9: goto L_802C7194; break;
        case 10: goto L_802C7178; break;
        case 11: goto L_802C7184; break;
        default: switch_error(__func__, 0x802C715C, 0x802C8E24);
    }
    // 0x802C7160: nop

L_802C7164:
    // 0x802C7164: b           L_802C7198
    // 0x802C7168: addiu       $t3, $zero, 0x1
    ctx->r11 = ADD32(0, 0X1);
        goto L_802C7198;
    // 0x802C7168: addiu       $t3, $zero, 0x1
    ctx->r11 = ADD32(0, 0X1);
L_802C716C:
    // 0x802C716C: addiu       $t3, $zero, 0x1
    ctx->r11 = ADD32(0, 0X1);
    // 0x802C7170: b           L_802C7198
    // 0x802C7174: addiu       $t2, $zero, 0x1
    ctx->r10 = ADD32(0, 0X1);
        goto L_802C7198;
    // 0x802C7174: addiu       $t2, $zero, 0x1
    ctx->r10 = ADD32(0, 0X1);
L_802C7178:
    // 0x802C7178: addiu       $t3, $zero, 0x1
    ctx->r11 = ADD32(0, 0X1);
    // 0x802C717C: b           L_802C7198
    // 0x802C7180: addiu       $t4, $zero, 0x1
    ctx->r12 = ADD32(0, 0X1);
        goto L_802C7198;
    // 0x802C7180: addiu       $t4, $zero, 0x1
    ctx->r12 = ADD32(0, 0X1);
L_802C7184:
    // 0x802C7184: addiu       $t3, $zero, 0x1
    ctx->r11 = ADD32(0, 0X1);
    // 0x802C7188: addiu       $t2, $zero, 0x1
    ctx->r10 = ADD32(0, 0X1);
    // 0x802C718C: b           L_802C7198
    // 0x802C7190: addiu       $t4, $zero, 0x1
    ctx->r12 = ADD32(0, 0X1);
        goto L_802C7198;
    // 0x802C7190: addiu       $t4, $zero, 0x1
    ctx->r12 = ADD32(0, 0X1);
L_802C7194:
    // 0x802C7194: addiu       $t4, $zero, 0x1
    ctx->r12 = ADD32(0, 0X1);
L_802C7198:
    // 0x802C7198: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x802C719C: lui         $t7, 0x103
    ctx->r15 = S32(0X103 << 16);
    // 0x802C71A0: ori         $t7, $t7, 0x40
    ctx->r15 = ctx->r15 | 0X40;
    // 0x802C71A4: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C71A8: lui         $t8, 0x700
    ctx->r24 = S32(0X700 << 16);
    // 0x802C71AC: addiu       $t8, $t8, 0x0
    ctx->r24 = ADD32(ctx->r24, 0X0);
    // 0x802C71B0: sw          $t7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r15;
    // 0x802C71B4: or          $a1, $a0, $zero
    ctx->r5 = ctx->r4 | 0;
    // 0x802C71B8: sw          $t8, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r24;
    // 0x802C71BC: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C71C0: lui         $t9, 0x102
    ctx->r25 = S32(0X102 << 16);
    // 0x802C71C4: lui         $t6, 0x200
    ctx->r14 = S32(0X200 << 16);
    // 0x802C71C8: addiu       $t6, $t6, 0xA40
    ctx->r14 = ADD32(ctx->r14, 0XA40);
    // 0x802C71CC: ori         $t9, $t9, 0x40
    ctx->r25 = ctx->r25 | 0X40;
    // 0x802C71D0: or          $a3, $a0, $zero
    ctx->r7 = ctx->r4 | 0;
    // 0x802C71D4: sw          $t9, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r25;
    // 0x802C71D8: sw          $t6, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r14;
    // 0x802C71DC: lui         $t7, 0x107
    ctx->r15 = S32(0X107 << 16);
    // 0x802C71E0: lui         $t1, 0x600
    ctx->r9 = S32(0X600 << 16);
    // 0x802C71E4: addiu       $t7, $t7, -0xAB0
    ctx->r15 = ADD32(ctx->r15, -0XAB0);
    // 0x802C71E8: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C71EC: sw          $t7, 0x4($a3)
    MEM_W(0X4, ctx->r7) = ctx->r15;
    // 0x802C71F0: sw          $t1, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r9;
    // 0x802C71F4: or          $t0, $a0, $zero
    ctx->r8 = ctx->r4 | 0;
    // 0x802C71F8: lui         $ra, 0x107
    ctx->r31 = S32(0X107 << 16);
    // 0x802C71FC: addiu       $ra, $ra, -0x9D8
    ctx->r31 = ADD32(ctx->r31, -0X9D8);
    // 0x802C7200: sw          $ra, 0x4($t0)
    MEM_W(0X4, ctx->r8) = ctx->r31;
    // 0x802C7204: sw          $t1, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r9;
    // 0x802C7208: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C720C: sw          $ra, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r31;
    // 0x802C7210: sb          $t5, 0x124($sp)
    MEM_B(0X124, ctx->r29) = ctx->r13;
    // 0x802C7214: sb          $t4, 0x123($sp)
    MEM_B(0X123, ctx->r29) = ctx->r12;
    // 0x802C7218: sb          $t3, 0x127($sp)
    MEM_B(0X127, ctx->r29) = ctx->r11;
    // 0x802C721C: sb          $t2, 0x126($sp)
    MEM_B(0X126, ctx->r29) = ctx->r10;
    // 0x802C7220: addiu       $a2, $zero, 0x1C
    ctx->r6 = ADD32(0, 0X1C);
    // 0x802C7224: addiu       $t8, $zero, 0x56
    ctx->r24 = ADD32(0, 0X56);
L_802C7228:
    // 0x802C7228: addiu       $t9, $zero, 0x10
    ctx->r25 = ADD32(0, 0X10);
    // 0x802C722C: sw          $t9, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r25;
    // 0x802C7230: sw          $t8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r24;
    // 0x802C7234: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C7238: addiu       $a3, $zero, 0x30
    ctx->r7 = ADD32(0, 0X30);
    // 0x802C723C: jal         0x80094338
    // 0x802C7240: sw          $a2, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r6;
    func_80094338(rdram, ctx);
        goto after_0;
    // 0x802C7240: sw          $a2, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r6;
    after_0:
    // 0x802C7244: lw          $a2, 0x44($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X44);
    // 0x802C7248: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C724C: addiu       $a2, $a2, 0x8D
    ctx->r6 = ADD32(ctx->r6, 0X8D);
    // 0x802C7250: slti        $at, $a2, 0x18F
    ctx->r1 = SIGNED(ctx->r6) < 0X18F ? 1 : 0;
    // 0x802C7254: bnel        $at, $zero, L_802C7228
    if (ctx->r1 != 0) {
        // 0x802C7258: addiu       $t8, $zero, 0x56
        ctx->r24 = ADD32(0, 0X56);
            goto L_802C7228;
    }
    goto skip_0;
    // 0x802C7258: addiu       $t8, $zero, 0x56
    ctx->r24 = ADD32(0, 0X56);
    skip_0:
    // 0x802C725C: addiu       $t6, $zero, 0x170
    ctx->r14 = ADD32(0, 0X170);
    // 0x802C7260: addiu       $t7, $zero, 0x28
    ctx->r15 = ADD32(0, 0X28);
    // 0x802C7264: sw          $t7, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r15;
    // 0x802C7268: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x802C726C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C7270: addiu       $a2, $zero, 0x1C
    ctx->r6 = ADD32(0, 0X1C);
    // 0x802C7274: jal         0x80094338
    // 0x802C7278: addiu       $a3, $zero, 0x44
    ctx->r7 = ADD32(0, 0X44);
    func_80094338(rdram, ctx);
        goto after_1;
    // 0x802C7278: addiu       $a3, $zero, 0x44
    ctx->r7 = ADD32(0, 0X44);
    after_1:
    // 0x802C727C: lb          $t8, 0x127($sp)
    ctx->r24 = MEM_B(ctx->r29, 0X127);
    // 0x802C7280: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C7284: beq         $t8, $zero, L_802C72D0
    if (ctx->r24 == 0) {
        // 0x802C7288: addiu       $t9, $zero, 0x64
        ctx->r25 = ADD32(0, 0X64);
            goto L_802C72D0;
    }
    // 0x802C7288: addiu       $t9, $zero, 0x64
    ctx->r25 = ADD32(0, 0X64);
    // 0x802C728C: addiu       $t6, $zero, 0x10
    ctx->r14 = ADD32(0, 0X10);
    // 0x802C7290: sw          $t6, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r14;
    // 0x802C7294: sw          $t9, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r25;
    // 0x802C7298: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C729C: addiu       $a2, $zero, 0x52
    ctx->r6 = ADD32(0, 0X52);
    // 0x802C72A0: jal         0x80094338
    // 0x802C72A4: addiu       $a3, $zero, 0x70
    ctx->r7 = ADD32(0, 0X70);
    func_80094338(rdram, ctx);
        goto after_2;
    // 0x802C72A4: addiu       $a3, $zero, 0x70
    ctx->r7 = ADD32(0, 0X70);
    after_2:
    // 0x802C72A8: addiu       $t7, $zero, 0x64
    ctx->r15 = ADD32(0, 0X64);
    // 0x802C72AC: addiu       $t8, $zero, 0x10
    ctx->r24 = ADD32(0, 0X10);
    // 0x802C72B0: sw          $t8, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r24;
    // 0x802C72B4: sw          $t7, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r15;
    // 0x802C72B8: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C72BC: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C72C0: addiu       $a2, $zero, 0xF2
    ctx->r6 = ADD32(0, 0XF2);
    // 0x802C72C4: jal         0x80094338
    // 0x802C72C8: addiu       $a3, $zero, 0x70
    ctx->r7 = ADD32(0, 0X70);
    func_80094338(rdram, ctx);
        goto after_3;
    // 0x802C72C8: addiu       $a3, $zero, 0x70
    ctx->r7 = ADD32(0, 0X70);
    after_3:
    // 0x802C72CC: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
L_802C72D0:
    // 0x802C72D0: lb          $t9, 0x126($sp)
    ctx->r25 = MEM_B(ctx->r29, 0X126);
    // 0x802C72D4: beq         $t9, $zero, L_802C72FC
    if (ctx->r25 == 0) {
        // 0x802C72D8: addiu       $t6, $zero, 0x170
        ctx->r14 = ADD32(0, 0X170);
            goto L_802C72FC;
    }
    // 0x802C72D8: addiu       $t6, $zero, 0x170
    ctx->r14 = ADD32(0, 0X170);
    // 0x802C72DC: addiu       $t7, $zero, 0x32
    ctx->r15 = ADD32(0, 0X32);
    // 0x802C72E0: sw          $t7, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r15;
    // 0x802C72E4: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x802C72E8: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C72EC: addiu       $a2, $zero, 0x1C
    ctx->r6 = ADD32(0, 0X1C);
    // 0x802C72F0: jal         0x80094338
    // 0x802C72F4: addiu       $a3, $zero, 0x84
    ctx->r7 = ADD32(0, 0X84);
    func_80094338(rdram, ctx);
        goto after_4;
    // 0x802C72F4: addiu       $a3, $zero, 0x84
    ctx->r7 = ADD32(0, 0X84);
    after_4:
    // 0x802C72F8: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
L_802C72FC:
    // 0x802C72FC: addiu       $a3, $zero, 0xBA
    ctx->r7 = ADD32(0, 0XBA);
    // 0x802C7300: addiu       $t9, $zero, 0x64
    ctx->r25 = ADD32(0, 0X64);
    // 0x802C7304: addiu       $t6, $zero, 0x10
    ctx->r14 = ADD32(0, 0X10);
    // 0x802C7308: sw          $a3, 0x148($sp)
    MEM_W(0X148, ctx->r29) = ctx->r7;
    // 0x802C730C: sw          $t6, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r14;
    // 0x802C7310: sw          $t9, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r25;
    // 0x802C7314: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C7318: jal         0x80094338
    // 0x802C731C: addiu       $a2, $zero, 0x52
    ctx->r6 = ADD32(0, 0X52);
    func_80094338(rdram, ctx);
        goto after_5;
    // 0x802C731C: addiu       $a2, $zero, 0x52
    ctx->r6 = ADD32(0, 0X52);
    after_5:
    // 0x802C7320: addiu       $t7, $zero, 0x64
    ctx->r15 = ADD32(0, 0X64);
    // 0x802C7324: addiu       $t8, $zero, 0x10
    ctx->r24 = ADD32(0, 0X10);
    // 0x802C7328: sw          $t8, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r24;
    // 0x802C732C: sw          $t7, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r15;
    // 0x802C7330: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C7334: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C7338: addiu       $a2, $zero, 0xF2
    ctx->r6 = ADD32(0, 0XF2);
    // 0x802C733C: jal         0x80094338
    // 0x802C7340: lw          $a3, 0x148($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X148);
    func_80094338(rdram, ctx);
        goto after_6;
    // 0x802C7340: lw          $a3, 0x148($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X148);
    after_6:
    // 0x802C7344: lb          $t9, 0x126($sp)
    ctx->r25 = MEM_B(ctx->r29, 0X126);
    // 0x802C7348: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C734C: beq         $t9, $zero, L_802C7368
    if (ctx->r25 == 0) {
        // 0x802C7350: lui         $t6, 0x807
        ctx->r14 = S32(0X807 << 16);
            goto L_802C7368;
    }
    // 0x802C7350: lui         $t6, 0x807
    ctx->r14 = S32(0X807 << 16);
    // 0x802C7354: lui         $t0, 0x600
    ctx->r8 = S32(0X600 << 16);
    // 0x802C7358: addiu       $t6, $t6, -0x2F8
    ctx->r14 = ADD32(ctx->r14, -0X2F8);
    // 0x802C735C: sw          $t6, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r14;
    // 0x802C7360: sw          $t0, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r8;
    // 0x802C7364: addiu       $a0, $v0, 0x8
    ctx->r4 = ADD32(ctx->r2, 0X8);
L_802C7368:
    // 0x802C7368: lb          $t7, 0x126($sp)
    ctx->r15 = MEM_B(ctx->r29, 0X126);
    // 0x802C736C: lui         $t0, 0x600
    ctx->r8 = S32(0X600 << 16);
    // 0x802C7370: beql        $t7, $zero, L_802C7548
    if (ctx->r15 == 0) {
        // 0x802C7374: or          $v0, $a0, $zero
        ctx->r2 = ctx->r4 | 0;
            goto L_802C7548;
    }
    goto skip_1;
    // 0x802C7374: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    skip_1:
    // 0x802C7378: jal         0x80093AFC
    // 0x802C737C: nop

    func_80093AFC(rdram, ctx);
        goto after_7;
    // 0x802C737C: nop

    after_7:
    // 0x802C7380: lui         $t9, 0xFF10
    ctx->r25 = S32(0XFF10 << 16);
    // 0x802C7384: lui         $t8, 0xE700
    ctx->r24 = S32(0XE700 << 16);
    // 0x802C7388: ori         $t9, $t9, 0x1A7
    ctx->r25 = ctx->r25 | 0X1A7;
    // 0x802C738C: sw          $t8, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r24;
    // 0x802C7390: sw          $zero, 0x4($v0)
    MEM_W(0X4, ctx->r2) = 0;
    // 0x802C7394: sw          $t9, 0x8($v0)
    MEM_W(0X8, ctx->r2) = ctx->r25;
    // 0x802C7398: lui         $t6, 0x8015
    ctx->r14 = S32(0X8015 << 16);
    // 0x802C739C: lw          $t6, 0x1948($t6)
    ctx->r14 = MEM_W(ctx->r14, 0X1948);
    // 0x802C73A0: lui         $t8, 0x8015
    ctx->r24 = S32(0X8015 << 16);
    // 0x802C73A4: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x802C73A8: sll         $t7, $t6, 2
    ctx->r15 = S32(ctx->r14 << 2);
    // 0x802C73AC: addu        $t8, $t8, $t7
    ctx->r24 = ADD32(ctx->r24, ctx->r15);
    // 0x802C73B0: lw          $t8, 0x42C0($t8)
    ctx->r24 = MEM_W(ctx->r24, 0X42C0);
    // 0x802C73B4: lui         $t6, 0xB400
    ctx->r14 = S32(0XB400 << 16);
    // 0x802C73B8: sw          $t6, 0x10($v0)
    MEM_W(0X10, ctx->r2) = ctx->r14;
    // 0x802C73BC: addu        $t9, $t8, $at
    ctx->r25 = ADD32(ctx->r24, ctx->r1);
    // 0x802C73C0: sw          $t9, 0xC($v0)
    MEM_W(0XC, ctx->r2) = ctx->r25;
    // 0x802C73C4: lui         $t7, 0x802D
    ctx->r15 = S32(0X802D << 16);
    // 0x802C73C8: lhu         $t7, -0x7154($t7)
    ctx->r15 = MEM_HU(ctx->r15, -0X7154);
    // 0x802C73CC: lui         $t9, 0x700
    ctx->r25 = S32(0X700 << 16);
    // 0x802C73D0: lui         $t8, 0x103
    ctx->r24 = S32(0X103 << 16);
    // 0x802C73D4: sw          $t7, 0x14($v0)
    MEM_W(0X14, ctx->r2) = ctx->r15;
    // 0x802C73D8: lui         $t7, 0x107
    ctx->r15 = S32(0X107 << 16);
    // 0x802C73DC: ori         $t8, $t8, 0x40
    ctx->r24 = ctx->r24 | 0X40;
    // 0x802C73E0: addiu       $t9, $t9, 0xA40
    ctx->r25 = ADD32(ctx->r25, 0XA40);
    // 0x802C73E4: addiu       $t7, $t7, -0xB78
    ctx->r15 = ADD32(ctx->r15, -0XB78);
    // 0x802C73E8: lui         $t6, 0x600
    ctx->r14 = S32(0X600 << 16);
    // 0x802C73EC: sw          $t9, 0x1C($v0)
    MEM_W(0X1C, ctx->r2) = ctx->r25;
    // 0x802C73F0: sw          $t8, 0x18($v0)
    MEM_W(0X18, ctx->r2) = ctx->r24;
    // 0x802C73F4: sw          $t6, 0x20($v0)
    MEM_W(0X20, ctx->r2) = ctx->r14;
    // 0x802C73F8: sw          $t7, 0x24($v0)
    MEM_W(0X24, ctx->r2) = ctx->r15;
    // 0x802C73FC: lui         $t8, 0x600
    ctx->r24 = S32(0X600 << 16);
    // 0x802C7400: lui         $t9, 0x807
    ctx->r25 = S32(0X807 << 16);
    // 0x802C7404: lui         $t7, 0x700
    ctx->r15 = S32(0X700 << 16);
    // 0x802C7408: lui         $t6, 0x102
    ctx->r14 = S32(0X102 << 16);
    // 0x802C740C: addiu       $t9, $t9, -0x230
    ctx->r25 = ADD32(ctx->r25, -0X230);
    // 0x802C7410: sw          $t8, 0x28($v0)
    MEM_W(0X28, ctx->r2) = ctx->r24;
    // 0x802C7414: ori         $t6, $t6, 0x40
    ctx->r14 = ctx->r14 | 0X40;
    // 0x802C7418: addiu       $t7, $t7, 0xA80
    ctx->r15 = ADD32(ctx->r15, 0XA80);
    // 0x802C741C: sw          $t9, 0x2C($v0)
    MEM_W(0X2C, ctx->r2) = ctx->r25;
    // 0x802C7420: sw          $t7, 0x34($v0)
    MEM_W(0X34, ctx->r2) = ctx->r15;
    // 0x802C7424: sw          $t6, 0x30($v0)
    MEM_W(0X30, ctx->r2) = ctx->r14;
    // 0x802C7428: lui         $t8, 0x801D
    ctx->r24 = S32(0X801D << 16);
    // 0x802C742C: lw          $t8, -0x1A08($t8)
    ctx->r24 = MEM_W(ctx->r24, -0X1A08);
    // 0x802C7430: addiu       $a0, $v0, 0x38
    ctx->r4 = ADD32(ctx->r2, 0X38);
    // 0x802C7434: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C7438: addiu       $t9, $t8, 0xC80
    ctx->r25 = ADD32(ctx->r24, 0XC80);
    // 0x802C743C: sw          $t9, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r25;
    // 0x802C7440: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x802C7444: jal         0x801E4FE8
    // 0x802C7448: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_801E4FE8(rdram, ctx);
        goto after_8;
    // 0x802C7448: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_8:
    // 0x802C744C: lui         $t6, 0x600
    ctx->r14 = S32(0X600 << 16);
    // 0x802C7450: lui         $t7, 0x807
    ctx->r15 = S32(0X807 << 16);
    // 0x802C7454: lui         $t8, 0x102
    ctx->r24 = S32(0X102 << 16);
    // 0x802C7458: lui         $t9, 0x700
    ctx->r25 = S32(0X700 << 16);
    // 0x802C745C: addiu       $t7, $t7, -0x220
    ctx->r15 = ADD32(ctx->r15, -0X220);
    // 0x802C7460: sw          $t6, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r14;
    // 0x802C7464: addiu       $t9, $t9, 0xAC0
    ctx->r25 = ADD32(ctx->r25, 0XAC0);
    // 0x802C7468: ori         $t8, $t8, 0x40
    ctx->r24 = ctx->r24 | 0X40;
    // 0x802C746C: sw          $t7, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r15;
    // 0x802C7470: sw          $t8, 0x8($v0)
    MEM_W(0X8, ctx->r2) = ctx->r24;
    // 0x802C7474: sw          $t9, 0xC($v0)
    MEM_W(0XC, ctx->r2) = ctx->r25;
    // 0x802C7478: lui         $t6, 0x801D
    ctx->r14 = S32(0X801D << 16);
    // 0x802C747C: lw          $t6, -0x1A08($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X1A08);
    // 0x802C7480: addiu       $a0, $v0, 0x10
    ctx->r4 = ADD32(ctx->r2, 0X10);
    // 0x802C7484: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C7488: addiu       $t7, $t6, 0xD40
    ctx->r15 = ADD32(ctx->r14, 0XD40);
    // 0x802C748C: sw          $t7, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r15;
    // 0x802C7490: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x802C7494: jal         0x801E4FE8
    // 0x802C7498: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_801E4FE8(rdram, ctx);
        goto after_9;
    // 0x802C7498: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_9:
    // 0x802C749C: lui         $t8, 0x600
    ctx->r24 = S32(0X600 << 16);
    // 0x802C74A0: lui         $t9, 0x807
    ctx->r25 = S32(0X807 << 16);
    // 0x802C74A4: lui         $t6, 0x102
    ctx->r14 = S32(0X102 << 16);
    // 0x802C74A8: lui         $t7, 0x700
    ctx->r15 = S32(0X700 << 16);
    // 0x802C74AC: addiu       $t9, $t9, -0x210
    ctx->r25 = ADD32(ctx->r25, -0X210);
    // 0x802C74B0: sw          $t8, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r24;
    // 0x802C74B4: addiu       $t7, $t7, 0xB00
    ctx->r15 = ADD32(ctx->r15, 0XB00);
    // 0x802C74B8: ori         $t6, $t6, 0x40
    ctx->r14 = ctx->r14 | 0X40;
    // 0x802C74BC: sw          $t9, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r25;
    // 0x802C74C0: sw          $t6, 0x8($v0)
    MEM_W(0X8, ctx->r2) = ctx->r14;
    // 0x802C74C4: sw          $t7, 0xC($v0)
    MEM_W(0XC, ctx->r2) = ctx->r15;
    // 0x802C74C8: lui         $t8, 0x801D
    ctx->r24 = S32(0X801D << 16);
    // 0x802C74CC: lw          $t8, -0x1A08($t8)
    ctx->r24 = MEM_W(ctx->r24, -0X1A08);
    // 0x802C74D0: addiu       $a0, $v0, 0x10
    ctx->r4 = ADD32(ctx->r2, 0X10);
    // 0x802C74D4: addiu       $a1, $zero, 0x3
    ctx->r5 = ADD32(0, 0X3);
    // 0x802C74D8: addiu       $t9, $t8, 0xE00
    ctx->r25 = ADD32(ctx->r24, 0XE00);
    // 0x802C74DC: sw          $t9, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r25;
    // 0x802C74E0: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x802C74E4: jal         0x801E4FE8
    // 0x802C74E8: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_801E4FE8(rdram, ctx);
        goto after_10;
    // 0x802C74E8: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_10:
    // 0x802C74EC: lui         $t6, 0x600
    ctx->r14 = S32(0X600 << 16);
    // 0x802C74F0: lui         $t7, 0x807
    ctx->r15 = S32(0X807 << 16);
    // 0x802C74F4: lui         $t8, 0x102
    ctx->r24 = S32(0X102 << 16);
    // 0x802C74F8: lui         $t9, 0x700
    ctx->r25 = S32(0X700 << 16);
    // 0x802C74FC: addiu       $t7, $t7, -0x200
    ctx->r15 = ADD32(ctx->r15, -0X200);
    // 0x802C7500: sw          $t6, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r14;
    // 0x802C7504: addiu       $t9, $t9, 0xB40
    ctx->r25 = ADD32(ctx->r25, 0XB40);
    // 0x802C7508: ori         $t8, $t8, 0x40
    ctx->r24 = ctx->r24 | 0X40;
    // 0x802C750C: sw          $t7, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r15;
    // 0x802C7510: sw          $t8, 0x8($v0)
    MEM_W(0X8, ctx->r2) = ctx->r24;
    // 0x802C7514: sw          $t9, 0xC($v0)
    MEM_W(0XC, ctx->r2) = ctx->r25;
    // 0x802C7518: lui         $t6, 0x801D
    ctx->r14 = S32(0X801D << 16);
    // 0x802C751C: lw          $t6, -0x1A08($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X1A08);
    // 0x802C7520: addiu       $a0, $v0, 0x10
    ctx->r4 = ADD32(ctx->r2, 0X10);
    // 0x802C7524: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C7528: addiu       $t7, $t6, 0xEC0
    ctx->r15 = ADD32(ctx->r14, 0XEC0);
    // 0x802C752C: sw          $t7, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r15;
    // 0x802C7530: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x802C7534: jal         0x801E4FE8
    // 0x802C7538: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_801E4FE8(rdram, ctx);
        goto after_11;
    // 0x802C7538: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_11:
    // 0x802C753C: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C7540: lui         $t0, 0x600
    ctx->r8 = S32(0X600 << 16);
    // 0x802C7544: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
L_802C7548:
    // 0x802C7548: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C754C: lui         $t8, 0x807
    ctx->r24 = S32(0X807 << 16);
    // 0x802C7550: addiu       $t8, $t8, -0x550
    ctx->r24 = ADD32(ctx->r24, -0X550);
    // 0x802C7554: or          $v1, $a0, $zero
    ctx->r3 = ctx->r4 | 0;
    // 0x802C7558: sw          $t8, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r24;
    // 0x802C755C: sw          $t0, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r8;
    // 0x802C7560: lui         $t9, 0x807
    ctx->r25 = S32(0X807 << 16);
    // 0x802C7564: addiu       $t9, $t9, -0x4D0
    ctx->r25 = ADD32(ctx->r25, -0X4D0);
    // 0x802C7568: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C756C: sw          $t9, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r25;
    // 0x802C7570: sw          $t0, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r8;
    // 0x802C7574: or          $a1, $a0, $zero
    ctx->r5 = ctx->r4 | 0;
    // 0x802C7578: lui         $t6, 0x807
    ctx->r14 = S32(0X807 << 16);
    // 0x802C757C: addiu       $t6, $t6, -0x478
    ctx->r14 = ADD32(ctx->r14, -0X478);
    // 0x802C7580: sw          $t6, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r14;
    // 0x802C7584: sw          $t0, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r8;
    // 0x802C7588: lb          $t7, 0x124($sp)
    ctx->r15 = MEM_B(ctx->r29, 0X124);
    // 0x802C758C: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C7590: beq         $t7, $zero, L_802C77B4
    if (ctx->r15 == 0) {
        // 0x802C7594: or          $v0, $a0, $zero
        ctx->r2 = ctx->r4 | 0;
            goto L_802C77B4;
    }
    // 0x802C7594: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x802C7598: lui         $t8, 0x807
    ctx->r24 = S32(0X807 << 16);
    // 0x802C759C: addiu       $t8, $t8, -0x420
    ctx->r24 = ADD32(ctx->r24, -0X420);
    // 0x802C75A0: sw          $t8, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r24;
    // 0x802C75A4: sw          $t0, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r8;
    // 0x802C75A8: lui         $t9, 0x802D
    ctx->r25 = S32(0X802D << 16);
    // 0x802C75AC: lw          $t9, -0x72B0($t9)
    ctx->r25 = MEM_W(ctx->r25, -0X72B0);
    // 0x802C75B0: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C75B4: lui         $t6, 0x802D
    ctx->r14 = S32(0X802D << 16);
    // 0x802C75B8: bne         $t9, $zero, L_802C7668
    if (ctx->r25 != 0) {
        // 0x802C75BC: lui         $a1, 0x801D
        ctx->r5 = S32(0X801D << 16);
            goto L_802C7668;
    }
    // 0x802C75BC: lui         $a1, 0x801D
    ctx->r5 = S32(0X801D << 16);
    // 0x802C75C0: lw          $t6, -0x72AC($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X72AC);
    // 0x802C75C4: lui         $t1, 0xFA00
    ctx->r9 = S32(0XFA00 << 16);
    // 0x802C75C8: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x802C75CC: bne         $t6, $zero, L_802C75F0
    if (ctx->r14 != 0) {
        // 0x802C75D0: lui         $at, 0xFF
        ctx->r1 = S32(0XFF << 16);
            goto L_802C75F0;
    }
    // 0x802C75D0: lui         $at, 0xFF
    ctx->r1 = S32(0XFF << 16);
    // 0x802C75D4: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x802C75D8: lui         $t7, 0x807
    ctx->r15 = S32(0X807 << 16);
    // 0x802C75DC: addiu       $t7, $t7, -0x3F8
    ctx->r15 = ADD32(ctx->r15, -0X3F8);
    // 0x802C75E0: sw          $t7, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r15;
    // 0x802C75E4: sw          $t0, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r8;
    // 0x802C75E8: b           L_802C7604
    // 0x802C75EC: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
        goto L_802C7604;
    // 0x802C75EC: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
L_802C75F0:
    // 0x802C75F0: lui         $t8, 0x807
    ctx->r24 = S32(0X807 << 16);
    // 0x802C75F4: addiu       $t8, $t8, -0x398
    ctx->r24 = ADD32(ctx->r24, -0X398);
    // 0x802C75F8: sw          $t8, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r24;
    // 0x802C75FC: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C7600: sw          $t0, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r8;
L_802C7604:
    // 0x802C7604: or          $v1, $a0, $zero
    ctx->r3 = ctx->r4 | 0;
    // 0x802C7608: sw          $t1, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r9;
    // 0x802C760C: lui         $v0, 0x802D
    ctx->r2 = S32(0X802D << 16);
    // 0x802C7610: lw          $v0, -0x7160($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X7160);
    // 0x802C7614: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C7618: or          $a1, $a0, $zero
    ctx->r5 = ctx->r4 | 0;
    // 0x802C761C: andi        $t9, $v0, 0xFF
    ctx->r25 = ctx->r2 & 0XFF;
    // 0x802C7620: sll         $t6, $t9, 24
    ctx->r14 = S32(ctx->r25 << 24);
    // 0x802C7624: or          $t7, $t6, $at
    ctx->r15 = ctx->r14 | ctx->r1;
    // 0x802C7628: sll         $t8, $t9, 8
    ctx->r24 = S32(ctx->r25 << 8);
    // 0x802C762C: or          $t9, $t7, $t8
    ctx->r25 = ctx->r15 | ctx->r24;
    // 0x802C7630: ori         $t6, $t9, 0xFF
    ctx->r14 = ctx->r25 | 0XFF;
    // 0x802C7634: sw          $t6, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r14;
    // 0x802C7638: lui         $t7, 0x807
    ctx->r15 = S32(0X807 << 16);
    // 0x802C763C: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C7640: addiu       $t7, $t7, -0x3B8
    ctx->r15 = ADD32(ctx->r15, -0X3B8);
    // 0x802C7644: or          $a2, $a0, $zero
    ctx->r6 = ctx->r4 | 0;
    // 0x802C7648: lui         $t8, 0x807
    ctx->r24 = S32(0X807 << 16);
    // 0x802C764C: sw          $t7, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r15;
    // 0x802C7650: sw          $t0, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r8;
    // 0x802C7654: addiu       $t8, $t8, -0x358
    ctx->r24 = ADD32(ctx->r24, -0X358);
    // 0x802C7658: sw          $t8, 0x4($a2)
    MEM_W(0X4, ctx->r6) = ctx->r24;
    // 0x802C765C: sw          $t0, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r8;
    // 0x802C7660: b           L_802C77B4
    // 0x802C7664: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
        goto L_802C77B4;
    // 0x802C7664: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
L_802C7668:
    // 0x802C7668: lui         $t9, 0x801D
    ctx->r25 = S32(0X801D << 16);
    // 0x802C766C: lw          $t9, -0x19C0($t9)
    ctx->r25 = MEM_W(ctx->r25, -0X19C0);
    // 0x802C7670: lui         $t6, 0x802D
    ctx->r14 = S32(0X802D << 16);
    // 0x802C7674: beql        $t9, $zero, L_802C76E0
    if (ctx->r25 == 0) {
        // 0x802C7678: or          $v0, $a0, $zero
        ctx->r2 = ctx->r4 | 0;
            goto L_802C76E0;
    }
    goto skip_2;
    // 0x802C7678: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    skip_2:
    // 0x802C767C: lw          $t6, -0x72AC($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X72AC);
    // 0x802C7680: lui         $t1, 0xFA00
    ctx->r9 = S32(0XFA00 << 16);
    // 0x802C7684: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x802C7688: bne         $t6, $zero, L_802C76CC
    if (ctx->r14 != 0) {
        // 0x802C768C: lui         $t9, 0x8080
        ctx->r25 = S32(0X8080 << 16);
            goto L_802C76CC;
    }
    // 0x802C768C: lui         $t9, 0x8080
    ctx->r25 = S32(0X8080 << 16);
    // 0x802C7690: lui         $t1, 0xFA00
    ctx->r9 = S32(0XFA00 << 16);
    // 0x802C7694: or          $v1, $a0, $zero
    ctx->r3 = ctx->r4 | 0;
    // 0x802C7698: sw          $t1, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r9;
    // 0x802C769C: lui         $v0, 0x802D
    ctx->r2 = S32(0X802D << 16);
    // 0x802C76A0: lw          $v0, -0x7160($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X7160);
    // 0x802C76A4: lui         $at, 0xFF
    ctx->r1 = S32(0XFF << 16);
    // 0x802C76A8: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C76AC: andi        $t7, $v0, 0xFF
    ctx->r15 = ctx->r2 & 0XFF;
    // 0x802C76B0: sll         $t8, $t7, 24
    ctx->r24 = S32(ctx->r15 << 24);
    // 0x802C76B4: or          $t9, $t8, $at
    ctx->r25 = ctx->r24 | ctx->r1;
    // 0x802C76B8: sll         $t6, $t7, 8
    ctx->r14 = S32(ctx->r15 << 8);
    // 0x802C76BC: or          $t7, $t9, $t6
    ctx->r15 = ctx->r25 | ctx->r14;
    // 0x802C76C0: ori         $t8, $t7, 0xFF
    ctx->r24 = ctx->r15 | 0XFF;
    // 0x802C76C4: b           L_802C76DC
    // 0x802C76C8: sw          $t8, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r24;
        goto L_802C76DC;
    // 0x802C76C8: sw          $t8, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r24;
L_802C76CC:
    // 0x802C76CC: ori         $t9, $t9, 0x80FF
    ctx->r25 = ctx->r25 | 0X80FF;
    // 0x802C76D0: sw          $t9, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r25;
    // 0x802C76D4: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C76D8: sw          $t1, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r9;
L_802C76DC:
    // 0x802C76DC: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
L_802C76E0:
    // 0x802C76E0: lui         $t6, 0x807
    ctx->r14 = S32(0X807 << 16);
    // 0x802C76E4: addiu       $t6, $t6, -0x3F8
    ctx->r14 = ADD32(ctx->r14, -0X3F8);
    // 0x802C76E8: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C76EC: sw          $t6, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r14;
    // 0x802C76F0: sw          $t0, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r8;
    // 0x802C76F4: or          $v1, $a0, $zero
    ctx->r3 = ctx->r4 | 0;
    // 0x802C76F8: lui         $t7, 0x807
    ctx->r15 = S32(0X807 << 16);
    // 0x802C76FC: addiu       $t7, $t7, -0x3B8
    ctx->r15 = ADD32(ctx->r15, -0X3B8);
    // 0x802C7700: sw          $t7, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r15;
    // 0x802C7704: sw          $t0, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r8;
    // 0x802C7708: lw          $a1, -0x19C0($a1)
    ctx->r5 = MEM_W(ctx->r5, -0X19C0);
    // 0x802C770C: lui         $t1, 0xFA00
    ctx->r9 = S32(0XFA00 << 16);
    // 0x802C7710: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C7714: beq         $a1, $zero, L_802C7784
    if (ctx->r5 == 0) {
        // 0x802C7718: lui         $t8, 0x802D
        ctx->r24 = S32(0X802D << 16);
            goto L_802C7784;
    }
    // 0x802C7718: lui         $t8, 0x802D
    ctx->r24 = S32(0X802D << 16);
    // 0x802C771C: lw          $t8, -0x72AC($t8)
    ctx->r24 = MEM_W(ctx->r24, -0X72AC);
    // 0x802C7720: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x802C7724: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x802C7728: bne         $t8, $at, L_802C7770
    if (ctx->r24 != ctx->r1) {
        // 0x802C772C: lui         $t7, 0x4040
        ctx->r15 = S32(0X4040 << 16);
            goto L_802C7770;
    }
    // 0x802C772C: lui         $t7, 0x4040
    ctx->r15 = S32(0X4040 << 16);
    // 0x802C7730: beq         $a1, $zero, L_802C7770
    if (ctx->r5 == 0) {
        // 0x802C7734: or          $v1, $a0, $zero
        ctx->r3 = ctx->r4 | 0;
            goto L_802C7770;
    }
    // 0x802C7734: or          $v1, $a0, $zero
    ctx->r3 = ctx->r4 | 0;
    // 0x802C7738: sw          $t1, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r9;
    // 0x802C773C: lui         $v0, 0x802D
    ctx->r2 = S32(0X802D << 16);
    // 0x802C7740: lw          $v0, -0x7160($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X7160);
    // 0x802C7744: lui         $at, 0xFF
    ctx->r1 = S32(0XFF << 16);
    // 0x802C7748: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C774C: andi        $t9, $v0, 0xFF
    ctx->r25 = ctx->r2 & 0XFF;
    // 0x802C7750: sll         $t6, $t9, 24
    ctx->r14 = S32(ctx->r25 << 24);
    // 0x802C7754: or          $t7, $t6, $at
    ctx->r15 = ctx->r14 | ctx->r1;
    // 0x802C7758: sll         $t8, $t9, 8
    ctx->r24 = S32(ctx->r25 << 8);
    // 0x802C775C: or          $t9, $t7, $t8
    ctx->r25 = ctx->r15 | ctx->r24;
    // 0x802C7760: ori         $t6, $t9, 0xFF
    ctx->r14 = ctx->r25 | 0XFF;
    // 0x802C7764: sw          $t6, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r14;
    // 0x802C7768: b           L_802C7784
    // 0x802C776C: lui         $t0, 0x600
    ctx->r8 = S32(0X600 << 16);
        goto L_802C7784;
    // 0x802C776C: lui         $t0, 0x600
    ctx->r8 = S32(0X600 << 16);
L_802C7770:
    // 0x802C7770: ori         $t7, $t7, 0x40FF
    ctx->r15 = ctx->r15 | 0X40FF;
    // 0x802C7774: sw          $t7, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r15;
    // 0x802C7778: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C777C: sw          $t1, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r9;
    // 0x802C7780: lui         $t0, 0x600
    ctx->r8 = S32(0X600 << 16);
L_802C7784:
    // 0x802C7784: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x802C7788: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C778C: lui         $t8, 0x807
    ctx->r24 = S32(0X807 << 16);
    // 0x802C7790: addiu       $t8, $t8, -0x398
    ctx->r24 = ADD32(ctx->r24, -0X398);
    // 0x802C7794: or          $v1, $a0, $zero
    ctx->r3 = ctx->r4 | 0;
    // 0x802C7798: sw          $t8, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r24;
    // 0x802C779C: sw          $t0, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r8;
    // 0x802C77A0: lui         $t9, 0x807
    ctx->r25 = S32(0X807 << 16);
    // 0x802C77A4: addiu       $t9, $t9, -0x358
    ctx->r25 = ADD32(ctx->r25, -0X358);
    // 0x802C77A8: sw          $t9, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r25;
    // 0x802C77AC: sw          $t0, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r8;
    // 0x802C77B0: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
L_802C77B4:
    // 0x802C77B4: lui         $t6, 0x801D
    ctx->r14 = S32(0X801D << 16);
    // 0x802C77B8: lw          $t6, -0x19C0($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X19C0);
    // 0x802C77BC: lui         $t1, 0xFA00
    ctx->r9 = S32(0XFA00 << 16);
    // 0x802C77C0: beq         $t6, $zero, L_802C7898
    if (ctx->r14 == 0) {
        // 0x802C77C4: or          $v0, $a0, $zero
        ctx->r2 = ctx->r4 | 0;
            goto L_802C7898;
    }
    // 0x802C77C4: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x802C77C8: lui         $t7, 0x807
    ctx->r15 = S32(0X807 << 16);
    // 0x802C77CC: addiu       $t7, $t7, -0x338
    ctx->r15 = ADD32(ctx->r15, -0X338);
    // 0x802C77D0: sw          $t7, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r15;
    // 0x802C77D4: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C77D8: sw          $t0, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r8;
    // 0x802C77DC: or          $v1, $a0, $zero
    ctx->r3 = ctx->r4 | 0;
    // 0x802C77E0: sw          $t1, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r9;
    // 0x802C77E4: lui         $t7, 0x802D
    ctx->r15 = S32(0X802D << 16);
    // 0x802C77E8: lui         $t8, 0x802D
    ctx->r24 = S32(0X802D << 16);
    // 0x802C77EC: lw          $t9, -0x715C($t8)
    ctx->r25 = MEM_W(ctx->r24, -0X715C);
    // 0x802C77F0: lw          $t7, -0x7158($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X7158);
    // 0x802C77F4: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C77F8: sll         $t6, $t9, 24
    ctx->r14 = S32(ctx->r25 << 24);
    // 0x802C77FC: andi        $t8, $t7, 0xFF
    ctx->r24 = ctx->r15 & 0XFF;
    // 0x802C7800: sll         $t9, $t8, 16
    ctx->r25 = S32(ctx->r24 << 16);
    // 0x802C7804: or          $t7, $t6, $t9
    ctx->r15 = ctx->r14 | ctx->r25;
    // 0x802C7808: ori         $t8, $t7, 0xFF
    ctx->r24 = ctx->r15 | 0XFF;
    // 0x802C780C: sw          $t8, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r24;
    // 0x802C7810: lui         $t6, 0x802D
    ctx->r14 = S32(0X802D << 16);
    // 0x802C7814: lw          $t6, -0x72AC($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X72AC);
    // 0x802C7818: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x802C781C: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C7820: bne         $t6, $zero, L_802C7830
    if (ctx->r14 != 0) {
        // 0x802C7824: lui         $at, 0xE400
        ctx->r1 = S32(0XE400 << 16);
            goto L_802C7830;
    }
    // 0x802C7824: lui         $at, 0xE400
    ctx->r1 = S32(0XE400 << 16);
    // 0x802C7828: b           L_802C7834
    // 0x802C782C: addiu       $a2, $zero, 0x18
    ctx->r6 = ADD32(0, 0X18);
        goto L_802C7834;
    // 0x802C782C: addiu       $a2, $zero, 0x18
    ctx->r6 = ADD32(0, 0X18);
L_802C7830:
    // 0x802C7830: addiu       $a2, $zero, 0x160
    ctx->r6 = ADD32(0, 0X160);
L_802C7834:
    // 0x802C7834: addiu       $t9, $a2, 0x28
    ctx->r25 = ADD32(ctx->r6, 0X28);
    // 0x802C7838: sll         $t7, $t9, 2
    ctx->r15 = S32(ctx->r25 << 2);
    // 0x802C783C: andi        $t8, $t7, 0xFFF
    ctx->r24 = ctx->r15 & 0XFFF;
    // 0x802C7840: sll         $t6, $t8, 12
    ctx->r14 = S32(ctx->r24 << 12);
    // 0x802C7844: or          $t9, $t6, $at
    ctx->r25 = ctx->r14 | ctx->r1;
    // 0x802C7848: ori         $t7, $t9, 0x1A0
    ctx->r15 = ctx->r25 | 0X1A0;
    // 0x802C784C: addiu       $t8, $a2, 0x8
    ctx->r24 = ADD32(ctx->r6, 0X8);
    // 0x802C7850: sll         $t6, $t8, 2
    ctx->r14 = S32(ctx->r24 << 2);
    // 0x802C7854: andi        $t9, $t6, 0xFFF
    ctx->r25 = ctx->r14 & 0XFFF;
    // 0x802C7858: sw          $t7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r15;
    // 0x802C785C: sll         $t7, $t9, 12
    ctx->r15 = S32(ctx->r25 << 12);
    // 0x802C7860: ori         $t8, $t7, 0x120
    ctx->r24 = ctx->r15 | 0X120;
    // 0x802C7864: or          $v1, $a0, $zero
    ctx->r3 = ctx->r4 | 0;
    // 0x802C7868: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C786C: sw          $t8, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r24;
    // 0x802C7870: or          $a1, $a0, $zero
    ctx->r5 = ctx->r4 | 0;
    // 0x802C7874: lui         $t6, 0xB300
    ctx->r14 = S32(0XB300 << 16);
    // 0x802C7878: sw          $t6, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r14;
    // 0x802C787C: sw          $zero, 0x4($v1)
    MEM_W(0X4, ctx->r3) = 0;
    // 0x802C7880: lui         $t7, 0x400
    ctx->r15 = S32(0X400 << 16);
    // 0x802C7884: ori         $t7, $t7, 0x400
    ctx->r15 = ctx->r15 | 0X400;
    // 0x802C7888: lui         $t9, 0xB200
    ctx->r25 = S32(0XB200 << 16);
    // 0x802C788C: sw          $t9, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r25;
    // 0x802C7890: sw          $t7, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r15;
    // 0x802C7894: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
L_802C7898:
    // 0x802C7898: lb          $t8, 0x126($sp)
    ctx->r24 = MEM_B(ctx->r29, 0X126);
    // 0x802C789C: beq         $t8, $zero, L_802C7A20
    if (ctx->r24 == 0) {
        // 0x802C78A0: or          $v1, $a0, $zero
        ctx->r3 = ctx->r4 | 0;
            goto L_802C7A20;
    }
    // 0x802C78A0: or          $v1, $a0, $zero
    ctx->r3 = ctx->r4 | 0;
    // 0x802C78A4: sw          $t1, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r9;
    // 0x802C78A8: lui         $v0, 0x802D
    ctx->r2 = S32(0X802D << 16);
    // 0x802C78AC: lw          $v0, -0x7160($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X7160);
    // 0x802C78B0: lui         $at, 0xFF
    ctx->r1 = S32(0XFF << 16);
    // 0x802C78B4: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C78B8: andi        $t6, $v0, 0xFF
    ctx->r14 = ctx->r2 & 0XFF;
    // 0x802C78BC: sll         $t9, $t6, 24
    ctx->r25 = S32(ctx->r14 << 24);
    // 0x802C78C0: or          $t7, $t9, $at
    ctx->r15 = ctx->r25 | ctx->r1;
    // 0x802C78C4: sll         $t8, $t6, 8
    ctx->r24 = S32(ctx->r14 << 8);
    // 0x802C78C8: or          $t6, $t7, $t8
    ctx->r14 = ctx->r15 | ctx->r24;
    // 0x802C78CC: ori         $t9, $t6, 0xFF
    ctx->r25 = ctx->r14 | 0XFF;
    // 0x802C78D0: or          $a1, $a0, $zero
    ctx->r5 = ctx->r4 | 0;
    // 0x802C78D4: sw          $t9, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r25;
    // 0x802C78D8: lui         $t8, 0x806
    ctx->r24 = S32(0X806 << 16);
    // 0x802C78DC: lui         $t7, 0xFD68
    ctx->r15 = S32(0XFD68 << 16);
    // 0x802C78E0: ori         $t7, $t7, 0x3E
    ctx->r15 = ctx->r15 | 0X3E;
    // 0x802C78E4: addiu       $t8, $t8, 0x1B10
    ctx->r24 = ADD32(ctx->r24, 0X1B10);
    // 0x802C78E8: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C78EC: or          $a2, $a0, $zero
    ctx->r6 = ctx->r4 | 0;
    // 0x802C78F0: sw          $t8, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r24;
    // 0x802C78F4: sw          $t7, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r15;
    // 0x802C78F8: lui         $t2, 0xF568
    ctx->r10 = S32(0XF568 << 16);
    // 0x802C78FC: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C7900: lui         $t6, 0x708
    ctx->r14 = S32(0X708 << 16);
    // 0x802C7904: ori         $t2, $t2, 0x1000
    ctx->r10 = ctx->r10 | 0X1000;
    // 0x802C7908: ori         $t6, $t6, 0x200
    ctx->r14 = ctx->r14 | 0X200;
    // 0x802C790C: or          $a3, $a0, $zero
    ctx->r7 = ctx->r4 | 0;
    // 0x802C7910: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C7914: sw          $t6, 0x4($a2)
    MEM_W(0X4, ctx->r6) = ctx->r14;
    // 0x802C7918: sw          $t2, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r10;
    // 0x802C791C: or          $t0, $a0, $zero
    ctx->r8 = ctx->r4 | 0;
    // 0x802C7920: lui         $t9, 0xE600
    ctx->r25 = S32(0XE600 << 16);
    // 0x802C7924: sw          $t9, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r25;
    // 0x802C7928: sw          $zero, 0x4($a3)
    MEM_W(0X4, ctx->r7) = 0;
    // 0x802C792C: lui         $t8, 0x70F
    ctx->r24 = S32(0X70F << 16);
    // 0x802C7930: ori         $t8, $t8, 0x809C
    ctx->r24 = ctx->r24 | 0X809C;
    // 0x802C7934: lui         $t7, 0xF400
    ctx->r15 = S32(0XF400 << 16);
    // 0x802C7938: sw          $t7, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r15;
    // 0x802C793C: sw          $t8, 0x4($t0)
    MEM_W(0X4, ctx->r8) = ctx->r24;
    // 0x802C7940: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C7944: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x802C7948: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C794C: or          $v1, $a0, $zero
    ctx->r3 = ctx->r4 | 0;
    // 0x802C7950: lui         $t6, 0xE700
    ctx->r14 = S32(0XE700 << 16);
    // 0x802C7954: sw          $t6, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r14;
    // 0x802C7958: sw          $zero, 0x4($v0)
    MEM_W(0X4, ctx->r2) = 0;
    // 0x802C795C: lui         $t9, 0x8
    ctx->r25 = S32(0X8 << 16);
    // 0x802C7960: ori         $t9, $t9, 0x200
    ctx->r25 = ctx->r25 | 0X200;
    // 0x802C7964: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C7968: or          $a1, $a0, $zero
    ctx->r5 = ctx->r4 | 0;
    // 0x802C796C: sw          $t9, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r25;
    // 0x802C7970: sw          $t2, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r10;
    // 0x802C7974: lui         $t8, 0xF
    ctx->r24 = S32(0XF << 16);
    // 0x802C7978: ori         $t8, $t8, 0x809C
    ctx->r24 = ctx->r24 | 0X809C;
    // 0x802C797C: lui         $t0, 0x802D
    ctx->r8 = S32(0X802D << 16);
    // 0x802C7980: lui         $t7, 0xF200
    ctx->r15 = S32(0XF200 << 16);
    // 0x802C7984: sw          $t7, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r15;
    // 0x802C7988: addiu       $t0, $t0, -0x72A4
    ctx->r8 = ADD32(ctx->r8, -0X72A4);
    // 0x802C798C: sw          $t8, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r24;
    // 0x802C7990: lw          $t6, 0x0($t0)
    ctx->r14 = MEM_W(ctx->r8, 0X0);
    // 0x802C7994: addiu       $t1, $zero, 0x63
    ctx->r9 = ADD32(0, 0X63);
    // 0x802C7998: lui         $at, 0xE400
    ctx->r1 = S32(0XE400 << 16);
    // 0x802C799C: multu       $t6, $t1
    result = U64(U32(ctx->r14)) * U64(U32(ctx->r9)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x802C79A0: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C79A4: or          $a2, $a0, $zero
    ctx->r6 = ctx->r4 | 0;
    // 0x802C79A8: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C79AC: or          $a3, $a0, $zero
    ctx->r7 = ctx->r4 | 0;
    // 0x802C79B0: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C79B4: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x802C79B8: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C79BC: mflo        $t9
    ctx->r25 = lo;
    // 0x802C79C0: addiu       $t7, $t9, 0x5E
    ctx->r15 = ADD32(ctx->r25, 0X5E);
    // 0x802C79C4: sll         $t8, $t7, 2
    ctx->r24 = S32(ctx->r15 << 2);
    // 0x802C79C8: andi        $t6, $t8, 0xFFF
    ctx->r14 = ctx->r24 & 0XFFF;
    // 0x802C79CC: sll         $t9, $t6, 12
    ctx->r25 = S32(ctx->r14 << 12);
    // 0x802C79D0: or          $t7, $t9, $at
    ctx->r15 = ctx->r25 | ctx->r1;
    // 0x802C79D4: ori         $t8, $t7, 0x2C4
    ctx->r24 = ctx->r15 | 0X2C4;
    // 0x802C79D8: sw          $t8, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r24;
    // 0x802C79DC: lw          $t6, 0x0($t0)
    ctx->r14 = MEM_W(ctx->r8, 0X0);
    // 0x802C79E0: multu       $t6, $t1
    result = U64(U32(ctx->r14)) * U64(U32(ctx->r9)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x802C79E4: mflo        $t9
    ctx->r25 = lo;
    // 0x802C79E8: addiu       $t7, $t9, 0x1F
    ctx->r15 = ADD32(ctx->r25, 0X1F);
    // 0x802C79EC: sll         $t8, $t7, 2
    ctx->r24 = S32(ctx->r15 << 2);
    // 0x802C79F0: andi        $t6, $t8, 0xFFF
    ctx->r14 = ctx->r24 & 0XFFF;
    // 0x802C79F4: sll         $t9, $t6, 12
    ctx->r25 = S32(ctx->r14 << 12);
    // 0x802C79F8: ori         $t7, $t9, 0x224
    ctx->r15 = ctx->r25 | 0X224;
    // 0x802C79FC: sw          $t7, 0x4($a2)
    MEM_W(0X4, ctx->r6) = ctx->r15;
    // 0x802C7A00: lui         $t8, 0xB300
    ctx->r24 = S32(0XB300 << 16);
    // 0x802C7A04: sw          $t8, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r24;
    // 0x802C7A08: sw          $zero, 0x4($a3)
    MEM_W(0X4, ctx->r7) = 0;
    // 0x802C7A0C: lui         $t9, 0x400
    ctx->r25 = S32(0X400 << 16);
    // 0x802C7A10: ori         $t9, $t9, 0x400
    ctx->r25 = ctx->r25 | 0X400;
    // 0x802C7A14: lui         $t6, 0xB200
    ctx->r14 = S32(0XB200 << 16);
    // 0x802C7A18: sw          $t6, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r14;
    // 0x802C7A1C: sw          $t9, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r25;
L_802C7A20:
    // 0x802C7A20: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C7A24: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C7A28: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C7A2C: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C7A30: sw          $t9, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r25;
    // 0x802C7A34: sw          $t9, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r25;
    // 0x802C7A38: sw          $t6, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r14;
    // 0x802C7A3C: sw          $t6, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r14;
    // 0x802C7A40: sw          $t8, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r24;
    // 0x802C7A44: sw          $t8, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r24;
    // 0x802C7A48: sw          $t8, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r24;
    // 0x802C7A4C: sw          $t7, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r15;
    // 0x802C7A50: sw          $t7, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r15;
    // 0x802C7A54: sw          $t7, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r15;
    // 0x802C7A58: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C7A5C: addiu       $a2, $zero, 0xFF
    ctx->r6 = ADD32(0, 0XFF);
    // 0x802C7A60: jal         0x801E946C
    // 0x802C7A64: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    func_801E946C(rdram, ctx);
        goto after_12;
    // 0x802C7A64: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    after_12:
    // 0x802C7A68: addiu       $t6, $zero, 0x16
    ctx->r14 = ADD32(0, 0X16);
    // 0x802C7A6C: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x802C7A70: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C7A74: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C7A78: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x802C7A7C: addiu       $a3, $zero, 0x76
    ctx->r7 = ADD32(0, 0X76);
    // 0x802C7A80: jal         0x801E3EE0
    // 0x802C7A84: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    func_801E3EE0(rdram, ctx);
        goto after_13;
    // 0x802C7A84: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    after_13:
    // 0x802C7A88: addiu       $t9, $zero, 0xCE
    ctx->r25 = ADD32(0, 0XCE);
    // 0x802C7A8C: sw          $t9, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r25;
    // 0x802C7A90: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C7A94: addiu       $a1, $zero, 0x4
    ctx->r5 = ADD32(0, 0X4);
    // 0x802C7A98: addiu       $a2, $zero, 0xC
    ctx->r6 = ADD32(0, 0XC);
    // 0x802C7A9C: addiu       $a3, $zero, 0x8B
    ctx->r7 = ADD32(0, 0X8B);
    // 0x802C7AA0: jal         0x801E3EE0
    // 0x802C7AA4: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    func_801E3EE0(rdram, ctx);
        goto after_14;
    // 0x802C7AA4: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    after_14:
    // 0x802C7AA8: addiu       $t7, $zero, 0xCE
    ctx->r15 = ADD32(0, 0XCE);
    // 0x802C7AAC: sw          $t7, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r15;
    // 0x802C7AB0: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C7AB4: addiu       $a1, $zero, 0x4
    ctx->r5 = ADD32(0, 0X4);
    // 0x802C7AB8: addiu       $a2, $zero, 0xD
    ctx->r6 = ADD32(0, 0XD);
    // 0x802C7ABC: addiu       $a3, $zero, 0xDD
    ctx->r7 = ADD32(0, 0XDD);
    // 0x802C7AC0: jal         0x801E3EE0
    // 0x802C7AC4: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    func_801E3EE0(rdram, ctx);
        goto after_15;
    // 0x802C7AC4: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    after_15:
    // 0x802C7AC8: lui         $v1, 0x802D
    ctx->r3 = S32(0X802D << 16);
    // 0x802C7ACC: lw          $v1, -0x72B0($v1)
    ctx->r3 = MEM_W(ctx->r3, -0X72B0);
    // 0x802C7AD0: lui         $t0, 0x802D
    ctx->r8 = S32(0X802D << 16);
    // 0x802C7AD4: lui         $a2, 0x802D
    ctx->r6 = S32(0X802D << 16);
    // 0x802C7AD8: sll         $t6, $v1, 2
    ctx->r14 = S32(ctx->r3 << 2);
    // 0x802C7ADC: addu        $t0, $t0, $t6
    ctx->r8 = ADD32(ctx->r8, ctx->r14);
    // 0x802C7AE0: lw          $t0, -0x724C($t0)
    ctx->r8 = MEM_W(ctx->r8, -0X724C);
    // 0x802C7AE4: sll         $t8, $v1, 3
    ctx->r24 = S32(ctx->r3 << 3);
    // 0x802C7AE8: addu        $a2, $a2, $t8
    ctx->r6 = ADD32(ctx->r6, ctx->r24);
    // 0x802C7AEC: addiu       $t9, $zero, 0x52
    ctx->r25 = ADD32(0, 0X52);
    // 0x802C7AF0: lw          $a2, -0x7260($a2)
    ctx->r6 = MEM_W(ctx->r6, -0X7260);
    // 0x802C7AF4: sw          $t9, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r25;
    // 0x802C7AF8: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C7AFC: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C7B00: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    // 0x802C7B04: jal         0x801E3EE0
    // 0x802C7B08: addiu       $a3, $t0, 0xBF
    ctx->r7 = ADD32(ctx->r8, 0XBF);
    func_801E3EE0(rdram, ctx);
        goto after_16;
    // 0x802C7B08: addiu       $a3, $t0, 0xBF
    ctx->r7 = ADD32(ctx->r8, 0XBF);
    after_16:
    // 0x802C7B0C: addiu       $t7, $zero, 0x5F
    ctx->r15 = ADD32(0, 0X5F);
    // 0x802C7B10: sw          $t7, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r15;
    // 0x802C7B14: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C7B18: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C7B1C: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x802C7B20: addiu       $a3, $zero, 0x43
    ctx->r7 = ADD32(0, 0X43);
    // 0x802C7B24: jal         0x801E3EE0
    // 0x802C7B28: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    func_801E3EE0(rdram, ctx);
        goto after_17;
    // 0x802C7B28: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    after_17:
    // 0x802C7B2C: addiu       $t8, $zero, 0x5F
    ctx->r24 = ADD32(0, 0X5F);
    // 0x802C7B30: sw          $t8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r24;
    // 0x802C7B34: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C7B38: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C7B3C: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    // 0x802C7B40: addiu       $a3, $zero, 0x109
    ctx->r7 = ADD32(0, 0X109);
    // 0x802C7B44: jal         0x801E3EE0
    // 0x802C7B48: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    func_801E3EE0(rdram, ctx);
        goto after_18;
    // 0x802C7B48: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    after_18:
    // 0x802C7B4C: lui         $t0, 0x802D
    ctx->r8 = S32(0X802D << 16);
    // 0x802C7B50: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C7B54: addiu       $t0, $t0, -0x7264
    ctx->r8 = ADD32(ctx->r8, -0X7264);
    // 0x802C7B58: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
    // 0x802C7B5C: or          $t1, $zero, $zero
    ctx->r9 = 0 | 0;
L_802C7B60:
    // 0x802C7B60: lui         $t6, 0x802D
    ctx->r14 = S32(0X802D << 16);
    // 0x802C7B64: lw          $t6, -0x72B0($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X72B0);
    // 0x802C7B68: addiu       $a2, $zero, 0xFF
    ctx->r6 = ADD32(0, 0XFF);
    // 0x802C7B6C: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    // 0x802C7B70: bne         $v1, $t6, L_802C7B80
    if (ctx->r3 != ctx->r14) {
        // 0x802C7B74: addiu       $t9, $zero, 0xFF
        ctx->r25 = ADD32(0, 0XFF);
            goto L_802C7B80;
    }
    // 0x802C7B74: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C7B78: b           L_802C7B84
    // 0x802C7B7C: addiu       $a1, $zero, 0x6
    ctx->r5 = ADD32(0, 0X6);
        goto L_802C7B84;
    // 0x802C7B7C: addiu       $a1, $zero, 0x6
    ctx->r5 = ADD32(0, 0X6);
L_802C7B80:
    // 0x802C7B80: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
L_802C7B84:
    // 0x802C7B84: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C7B88: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C7B8C: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C7B90: sw          $t6, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r14;
    // 0x802C7B94: sw          $t6, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r14;
    // 0x802C7B98: sw          $t8, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r24;
    // 0x802C7B9C: sw          $t8, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r24;
    // 0x802C7BA0: sw          $t7, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r15;
    // 0x802C7BA4: sw          $t7, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r15;
    // 0x802C7BA8: sw          $t7, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r15;
    // 0x802C7BAC: sw          $t9, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r25;
    // 0x802C7BB0: sw          $t9, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r25;
    // 0x802C7BB4: sw          $t9, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r25;
    // 0x802C7BB8: sw          $v1, 0x14C($sp)
    MEM_W(0X14C, ctx->r29) = ctx->r3;
    // 0x802C7BBC: sw          $t0, 0x11C($sp)
    MEM_W(0X11C, ctx->r29) = ctx->r8;
    // 0x802C7BC0: jal         0x801E946C
    // 0x802C7BC4: sw          $t1, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r9;
    func_801E946C(rdram, ctx);
        goto after_19;
    // 0x802C7BC4: sw          $t1, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r9;
    after_19:
    // 0x802C7BC8: lw          $t0, 0x11C($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X11C);
    // 0x802C7BCC: lw          $t1, 0x44($sp)
    ctx->r9 = MEM_W(ctx->r29, 0X44);
    // 0x802C7BD0: addiu       $t6, $zero, 0x33
    ctx->r14 = ADD32(0, 0X33);
    // 0x802C7BD4: lh          $t8, 0x0($t0)
    ctx->r24 = MEM_H(ctx->r8, 0X0);
    // 0x802C7BD8: lw          $a2, 0x4($t0)
    ctx->r6 = MEM_W(ctx->r8, 0X4);
    // 0x802C7BDC: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    // 0x802C7BE0: addu        $a3, $t1, $t8
    ctx->r7 = ADD32(ctx->r9, ctx->r24);
    // 0x802C7BE4: addiu       $a3, $a3, 0x35
    ctx->r7 = ADD32(ctx->r7, 0X35);
    // 0x802C7BE8: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x802C7BEC: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C7BF0: jal         0x801E3EE0
    // 0x802C7BF4: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    func_801E3EE0(rdram, ctx);
        goto after_20;
    // 0x802C7BF4: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    after_20:
    // 0x802C7BF8: lw          $v1, 0x14C($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X14C);
    // 0x802C7BFC: lw          $t0, 0x11C($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X11C);
    // 0x802C7C00: lw          $t1, 0x44($sp)
    ctx->r9 = MEM_W(ctx->r29, 0X44);
    // 0x802C7C04: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x802C7C08: addiu       $v1, $v1, 0x1
    ctx->r3 = ADD32(ctx->r3, 0X1);
    // 0x802C7C0C: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C7C10: addiu       $t0, $t0, 0x8
    ctx->r8 = ADD32(ctx->r8, 0X8);
    // 0x802C7C14: bne         $v1, $at, L_802C7B60
    if (ctx->r3 != ctx->r1) {
        // 0x802C7C18: addiu       $t1, $t1, 0x8D
        ctx->r9 = ADD32(ctx->r9, 0X8D);
            goto L_802C7B60;
    }
    // 0x802C7C18: addiu       $t1, $t1, 0x8D
    ctx->r9 = ADD32(ctx->r9, 0X8D);
    // 0x802C7C1C: lb          $t9, 0x127($sp)
    ctx->r25 = MEM_B(ctx->r29, 0X127);
    // 0x802C7C20: lui         $t7, 0x802D
    ctx->r15 = S32(0X802D << 16);
    // 0x802C7C24: addiu       $a2, $zero, 0xFF
    ctx->r6 = ADD32(0, 0XFF);
    // 0x802C7C28: beq         $t9, $zero, L_802C7D1C
    if (ctx->r25 == 0) {
        // 0x802C7C2C: addiu       $a3, $zero, 0xFF
        ctx->r7 = ADD32(0, 0XFF);
            goto L_802C7D1C;
    }
    // 0x802C7C2C: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    // 0x802C7C30: lw          $t7, -0x72A8($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X72A8);
    // 0x802C7C34: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C7C38: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C7C3C: bne         $t7, $zero, L_802C7C50
    if (ctx->r15 != 0) {
        // 0x802C7C40: addiu       $t9, $zero, 0xFF
        ctx->r25 = ADD32(0, 0XFF);
            goto L_802C7C50;
    }
    // 0x802C7C40: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C7C44: addiu       $a1, $zero, 0x6
    ctx->r5 = ADD32(0, 0X6);
    // 0x802C7C48: b           L_802C7C58
    // 0x802C7C4C: sw          $zero, 0x128($sp)
    MEM_W(0X128, ctx->r29) = 0;
        goto L_802C7C58;
    // 0x802C7C4C: sw          $zero, 0x128($sp)
    MEM_W(0X128, ctx->r29) = 0;
L_802C7C50:
    // 0x802C7C50: addiu       $t8, $zero, 0x6
    ctx->r24 = ADD32(0, 0X6);
    // 0x802C7C54: sw          $t8, 0x128($sp)
    MEM_W(0X128, ctx->r29) = ctx->r24;
L_802C7C58:
    // 0x802C7C58: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C7C5C: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C7C60: sw          $t8, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r24;
    // 0x802C7C64: sw          $t8, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r24;
    // 0x802C7C68: sw          $t7, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r15;
    // 0x802C7C6C: sw          $t7, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r15;
    // 0x802C7C70: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x802C7C74: sw          $t9, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r25;
    // 0x802C7C78: sw          $t6, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r14;
    // 0x802C7C7C: sw          $t9, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r25;
    // 0x802C7C80: sw          $t6, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r14;
    // 0x802C7C84: jal         0x801E946C
    // 0x802C7C88: sw          $t9, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r25;
    func_801E946C(rdram, ctx);
        goto after_21;
    // 0x802C7C88: sw          $t9, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r25;
    after_21:
    // 0x802C7C8C: addiu       $t7, $zero, 0x73
    ctx->r15 = ADD32(0, 0X73);
    // 0x802C7C90: sw          $t7, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r15;
    // 0x802C7C94: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C7C98: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C7C9C: addiu       $a2, $zero, 0x2
    ctx->r6 = ADD32(0, 0X2);
    // 0x802C7CA0: addiu       $a3, $zero, 0x5E
    ctx->r7 = ADD32(0, 0X5E);
    // 0x802C7CA4: jal         0x801E3EE0
    // 0x802C7CA8: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    func_801E3EE0(rdram, ctx);
        goto after_22;
    // 0x802C7CA8: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    after_22:
    // 0x802C7CAC: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C7CB0: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C7CB4: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C7CB8: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C7CBC: sw          $t7, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r15;
    // 0x802C7CC0: sw          $t7, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r15;
    // 0x802C7CC4: sw          $t9, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r25;
    // 0x802C7CC8: sw          $t9, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r25;
    // 0x802C7CCC: sw          $t6, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r14;
    // 0x802C7CD0: sw          $t6, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r14;
    // 0x802C7CD4: sw          $t6, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r14;
    // 0x802C7CD8: sw          $t8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r24;
    // 0x802C7CDC: sw          $t8, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r24;
    // 0x802C7CE0: sw          $t8, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r24;
    // 0x802C7CE4: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C7CE8: lw          $a1, 0x128($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X128);
    // 0x802C7CEC: addiu       $a2, $zero, 0xFF
    ctx->r6 = ADD32(0, 0XFF);
    // 0x802C7CF0: jal         0x801E946C
    // 0x802C7CF4: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    func_801E946C(rdram, ctx);
        goto after_23;
    // 0x802C7CF4: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    after_23:
    // 0x802C7CF8: addiu       $t9, $zero, 0x73
    ctx->r25 = ADD32(0, 0X73);
    // 0x802C7CFC: sw          $t9, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r25;
    // 0x802C7D00: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C7D04: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C7D08: addiu       $a2, $zero, 0x40
    ctx->r6 = ADD32(0, 0X40);
    // 0x802C7D0C: addiu       $a3, $zero, 0xF8
    ctx->r7 = ADD32(0, 0XF8);
    // 0x802C7D10: jal         0x801E3EE0
    // 0x802C7D14: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    func_801E3EE0(rdram, ctx);
        goto after_24;
    // 0x802C7D14: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    after_24:
    // 0x802C7D18: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
L_802C7D1C:
    // 0x802C7D1C: lb          $t7, 0x123($sp)
    ctx->r15 = MEM_B(ctx->r29, 0X123);
    // 0x802C7D20: addiu       $t9, $zero, 0x7
    ctx->r25 = ADD32(0, 0X7);
    // 0x802C7D24: addiu       $a2, $zero, 0x80
    ctx->r6 = ADD32(0, 0X80);
    // 0x802C7D28: beq         $t7, $zero, L_802C7D5C
    if (ctx->r15 == 0) {
        // 0x802C7D2C: addiu       $a3, $zero, 0x80
        ctx->r7 = ADD32(0, 0X80);
            goto L_802C7D5C;
    }
    // 0x802C7D2C: addiu       $a3, $zero, 0x80
    ctx->r7 = ADD32(0, 0X80);
    // 0x802C7D30: lui         $t8, 0x802D
    ctx->r24 = S32(0X802D << 16);
    // 0x802C7D34: lw          $t8, -0x7290($t8)
    ctx->r24 = MEM_W(ctx->r24, -0X7290);
    // 0x802C7D38: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C7D3C: addiu       $t6, $zero, 0x6
    ctx->r14 = ADD32(0, 0X6);
    // 0x802C7D40: bne         $t8, $zero, L_802C7D54
    if (ctx->r24 != 0) {
        // 0x802C7D44: nop
    
            goto L_802C7D54;
    }
    // 0x802C7D44: nop

    // 0x802C7D48: addiu       $a1, $zero, 0x6
    ctx->r5 = ADD32(0, 0X6);
    // 0x802C7D4C: b           L_802C7D64
    // 0x802C7D50: sw          $zero, 0x128($sp)
    MEM_W(0X128, ctx->r29) = 0;
        goto L_802C7D64;
    // 0x802C7D50: sw          $zero, 0x128($sp)
    MEM_W(0X128, ctx->r29) = 0;
L_802C7D54:
    // 0x802C7D54: b           L_802C7D64
    // 0x802C7D58: sw          $t6, 0x128($sp)
    MEM_W(0X128, ctx->r29) = ctx->r14;
        goto L_802C7D64;
    // 0x802C7D58: sw          $t6, 0x128($sp)
    MEM_W(0X128, ctx->r29) = ctx->r14;
L_802C7D5C:
    // 0x802C7D5C: sw          $t9, 0x128($sp)
    MEM_W(0X128, ctx->r29) = ctx->r25;
    // 0x802C7D60: addiu       $a1, $zero, 0x7
    ctx->r5 = ADD32(0, 0X7);
L_802C7D64:
    // 0x802C7D64: addiu       $t7, $zero, 0x80
    ctx->r15 = ADD32(0, 0X80);
    // 0x802C7D68: sw          $t7, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r15;
    // 0x802C7D6C: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C7D70: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C7D74: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C7D78: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C7D7C: sw          $t9, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r25;
    // 0x802C7D80: sw          $t9, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r25;
    // 0x802C7D84: sw          $t6, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r14;
    // 0x802C7D88: sw          $t6, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r14;
    // 0x802C7D8C: sw          $t7, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r15;
    // 0x802C7D90: sw          $t7, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r15;
    // 0x802C7D94: sw          $t8, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r24;
    // 0x802C7D98: sw          $t8, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r24;
    // 0x802C7D9C: jal         0x801E946C
    // 0x802C7DA0: sw          $t8, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r24;
    func_801E946C(rdram, ctx);
        goto after_25;
    // 0x802C7DA0: sw          $t8, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r24;
    after_25:
    // 0x802C7DA4: lw          $v1, 0x148($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X148);
    // 0x802C7DA8: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C7DAC: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C7DB0: addiu       $v1, $v1, 0x3
    ctx->r3 = ADD32(ctx->r3, 0X3);
    // 0x802C7DB4: sw          $v1, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r3;
    // 0x802C7DB8: sw          $v1, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r3;
    // 0x802C7DBC: addiu       $a2, $zero, 0x4
    ctx->r6 = ADD32(0, 0X4);
    // 0x802C7DC0: addiu       $a3, $zero, 0x66
    ctx->r7 = ADD32(0, 0X66);
    // 0x802C7DC4: jal         0x801E3EE0
    // 0x802C7DC8: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    func_801E3EE0(rdram, ctx);
        goto after_26;
    // 0x802C7DC8: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    after_26:
    // 0x802C7DCC: addiu       $t6, $zero, 0x80
    ctx->r14 = ADD32(0, 0X80);
    // 0x802C7DD0: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x802C7DD4: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C7DD8: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C7DDC: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C7DE0: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C7DE4: sw          $t8, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r24;
    // 0x802C7DE8: sw          $t8, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r24;
    // 0x802C7DEC: sw          $t7, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r15;
    // 0x802C7DF0: sw          $t7, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r15;
    // 0x802C7DF4: sw          $t6, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r14;
    // 0x802C7DF8: sw          $t6, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r14;
    // 0x802C7DFC: sw          $t9, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r25;
    // 0x802C7E00: sw          $t9, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r25;
    // 0x802C7E04: sw          $t9, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r25;
    // 0x802C7E08: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C7E0C: lw          $a1, 0x128($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X128);
    // 0x802C7E10: addiu       $a2, $zero, 0x80
    ctx->r6 = ADD32(0, 0X80);
    // 0x802C7E14: jal         0x801E946C
    // 0x802C7E18: addiu       $a3, $zero, 0x80
    ctx->r7 = ADD32(0, 0X80);
    func_801E946C(rdram, ctx);
        goto after_27;
    // 0x802C7E18: addiu       $a3, $zero, 0x80
    ctx->r7 = ADD32(0, 0X80);
    after_27:
    // 0x802C7E1C: lw          $t7, 0x44($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X44);
    // 0x802C7E20: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C7E24: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C7E28: addiu       $a2, $zero, 0x5
    ctx->r6 = ADD32(0, 0X5);
    // 0x802C7E2C: addiu       $a3, $zero, 0x109
    ctx->r7 = ADD32(0, 0X109);
    // 0x802C7E30: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    // 0x802C7E34: jal         0x801E3EE0
    // 0x802C7E38: sw          $t7, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r15;
    func_801E3EE0(rdram, ctx);
        goto after_28;
    // 0x802C7E38: sw          $t7, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r15;
    after_28:
    // 0x802C7E3C: lui         $t8, 0x802D
    ctx->r24 = S32(0X802D << 16);
    // 0x802C7E40: lw          $t8, -0x7238($t8)
    ctx->r24 = MEM_W(ctx->r24, -0X7238);
    // 0x802C7E44: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C7E48: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C7E4C: beq         $t8, $zero, L_802C7EA4
    if (ctx->r24 == 0) {
        // 0x802C7E50: or          $a2, $zero, $zero
        ctx->r6 = 0 | 0;
            goto L_802C7EA4;
    }
    // 0x802C7E50: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x802C7E54: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C7E58: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x802C7E5C: jal         0x801E7E74
    // 0x802C7E60: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_801E7E74(rdram, ctx);
        goto after_29;
    // 0x802C7E60: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_29:
    // 0x802C7E64: lui         $t0, 0x802D
    ctx->r8 = S32(0X802D << 16);
    // 0x802C7E68: lui         $t7, 0x802D
    ctx->r15 = S32(0X802D << 16);
    // 0x802C7E6C: lw          $t7, -0x7144($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X7144);
    // 0x802C7E70: lw          $t0, -0x714C($t0)
    ctx->r8 = MEM_W(ctx->r8, -0X714C);
    // 0x802C7E74: lui         $v1, 0x802D
    ctx->r3 = S32(0X802D << 16);
    // 0x802C7E78: lw          $v1, -0x7150($v1)
    ctx->r3 = MEM_W(ctx->r3, -0X7150);
    // 0x802C7E7C: lui         $t9, 0x802D
    ctx->r25 = S32(0X802D << 16);
    // 0x802C7E80: lw          $t9, -0x7148($t9)
    ctx->r25 = MEM_W(ctx->r25, -0X7148);
    // 0x802C7E84: addu        $t8, $t0, $t7
    ctx->r24 = ADD32(ctx->r8, ctx->r15);
    // 0x802C7E88: sw          $t8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r24;
    // 0x802C7E8C: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C7E90: or          $a2, $t0, $zero
    ctx->r6 = ctx->r8 | 0;
    // 0x802C7E94: or          $a1, $v1, $zero
    ctx->r5 = ctx->r3 | 0;
    // 0x802C7E98: jal         0x801E7FD8
    // 0x802C7E9C: addu        $a3, $v1, $t9
    ctx->r7 = ADD32(ctx->r3, ctx->r25);
    func_801E7FD8(rdram, ctx);
        goto after_30;
    // 0x802C7E9C: addu        $a3, $v1, $t9
    ctx->r7 = ADD32(ctx->r3, ctx->r25);
    after_30:
    // 0x802C7EA0: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
L_802C7EA4:
    // 0x802C7EA4: lui         $t6, 0x802D
    ctx->r14 = S32(0X802D << 16);
    // 0x802C7EA8: lw          $t6, -0x722C($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X722C);
    // 0x802C7EAC: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x802C7EB0: lui         $t9, 0x600
    ctx->r25 = S32(0X600 << 16);
    // 0x802C7EB4: beq         $t6, $zero, L_802C8008
    if (ctx->r14 == 0) {
        // 0x802C7EB8: or          $a1, $zero, $zero
        ctx->r5 = 0 | 0;
            goto L_802C8008;
    }
    // 0x802C7EB8: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C7EBC: sw          $t9, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r25;
    // 0x802C7EC0: lw          $t7, 0x40($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X40);
    // 0x802C7EC4: addiu       $t8, $zero, 0x64
    ctx->r24 = ADD32(0, 0X64);
    // 0x802C7EC8: addiu       $t6, $zero, 0x10
    ctx->r14 = ADD32(0, 0X10);
    // 0x802C7ECC: sw          $t7, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r15;
    // 0x802C7ED0: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C7ED4: sw          $t6, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r14;
    // 0x802C7ED8: sw          $t8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r24;
    // 0x802C7EDC: addiu       $a2, $zero, 0x52
    ctx->r6 = ADD32(0, 0X52);
    // 0x802C7EE0: jal         0x80094338
    // 0x802C7EE4: addiu       $a3, $zero, 0x93
    ctx->r7 = ADD32(0, 0X93);
    func_80094338(rdram, ctx);
        goto after_31;
    // 0x802C7EE4: addiu       $a3, $zero, 0x93
    ctx->r7 = ADD32(0, 0X93);
    after_31:
    // 0x802C7EE8: addiu       $t9, $zero, 0x64
    ctx->r25 = ADD32(0, 0X64);
    // 0x802C7EEC: addiu       $t7, $zero, 0x10
    ctx->r15 = ADD32(0, 0X10);
    // 0x802C7EF0: sw          $t7, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r15;
    // 0x802C7EF4: sw          $t9, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r25;
    // 0x802C7EF8: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C7EFC: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C7F00: addiu       $a2, $zero, 0xF2
    ctx->r6 = ADD32(0, 0XF2);
    // 0x802C7F04: jal         0x80094338
    // 0x802C7F08: addiu       $a3, $zero, 0x93
    ctx->r7 = ADD32(0, 0X93);
    func_80094338(rdram, ctx);
        goto after_32;
    // 0x802C7F08: addiu       $a3, $zero, 0x93
    ctx->r7 = ADD32(0, 0X93);
    after_32:
    // 0x802C7F0C: lui         $t8, 0x802D
    ctx->r24 = S32(0X802D << 16);
    // 0x802C7F10: lw          $t8, -0x723C($t8)
    ctx->r24 = MEM_W(ctx->r24, -0X723C);
    // 0x802C7F14: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C7F18: addiu       $a2, $zero, 0xFF
    ctx->r6 = ADD32(0, 0XFF);
    // 0x802C7F1C: bne         $t8, $zero, L_802C7F30
    if (ctx->r24 != 0) {
        // 0x802C7F20: addiu       $a3, $zero, 0xFF
        ctx->r7 = ADD32(0, 0XFF);
            goto L_802C7F30;
    }
    // 0x802C7F20: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    // 0x802C7F24: addiu       $a1, $zero, 0x6
    ctx->r5 = ADD32(0, 0X6);
    // 0x802C7F28: b           L_802C7F3C
    // 0x802C7F2C: sw          $zero, 0x130($sp)
    MEM_W(0X130, ctx->r29) = 0;
        goto L_802C7F3C;
    // 0x802C7F2C: sw          $zero, 0x130($sp)
    MEM_W(0X130, ctx->r29) = 0;
L_802C7F30:
    // 0x802C7F30: addiu       $t6, $zero, 0x6
    ctx->r14 = ADD32(0, 0X6);
    // 0x802C7F34: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C7F38: sw          $t6, 0x130($sp)
    MEM_W(0X130, ctx->r29) = ctx->r14;
L_802C7F3C:
    // 0x802C7F3C: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C7F40: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C7F44: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C7F48: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C7F4C: sw          $t6, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r14;
    // 0x802C7F50: sw          $t6, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r14;
    // 0x802C7F54: sw          $t8, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r24;
    // 0x802C7F58: sw          $t8, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r24;
    // 0x802C7F5C: sw          $t7, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r15;
    // 0x802C7F60: sw          $t7, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r15;
    // 0x802C7F64: sw          $t7, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r15;
    // 0x802C7F68: sw          $t9, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r25;
    // 0x802C7F6C: sw          $t9, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r25;
    // 0x802C7F70: jal         0x801E946C
    // 0x802C7F74: sw          $t9, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r25;
    func_801E946C(rdram, ctx);
        goto after_33;
    // 0x802C7F74: sw          $t9, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r25;
    after_33:
    // 0x802C7F78: addiu       $t8, $zero, 0x96
    ctx->r24 = ADD32(0, 0X96);
    // 0x802C7F7C: sw          $t8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r24;
    // 0x802C7F80: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C7F84: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C7F88: addiu       $a2, $zero, 0x26
    ctx->r6 = ADD32(0, 0X26);
    // 0x802C7F8C: addiu       $a3, $zero, 0x6E
    ctx->r7 = ADD32(0, 0X6E);
    // 0x802C7F90: jal         0x801E3EE0
    // 0x802C7F94: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    func_801E3EE0(rdram, ctx);
        goto after_34;
    // 0x802C7F94: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    after_34:
    // 0x802C7F98: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C7F9C: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C7FA0: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C7FA4: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C7FA8: sw          $t8, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r24;
    // 0x802C7FAC: sw          $t8, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r24;
    // 0x802C7FB0: sw          $t7, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r15;
    // 0x802C7FB4: sw          $t7, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r15;
    // 0x802C7FB8: sw          $t9, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r25;
    // 0x802C7FBC: sw          $t9, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r25;
    // 0x802C7FC0: sw          $t9, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r25;
    // 0x802C7FC4: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x802C7FC8: sw          $t6, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r14;
    // 0x802C7FCC: sw          $t6, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r14;
    // 0x802C7FD0: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C7FD4: lw          $a1, 0x130($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X130);
    // 0x802C7FD8: addiu       $a2, $zero, 0xFF
    ctx->r6 = ADD32(0, 0XFF);
    // 0x802C7FDC: jal         0x801E946C
    // 0x802C7FE0: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    func_801E946C(rdram, ctx);
        goto after_35;
    // 0x802C7FE0: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    after_35:
    // 0x802C7FE4: addiu       $t7, $zero, 0x96
    ctx->r15 = ADD32(0, 0X96);
    // 0x802C7FE8: sw          $t7, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r15;
    // 0x802C7FEC: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C7FF0: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C7FF4: addiu       $a2, $zero, 0x27
    ctx->r6 = ADD32(0, 0X27);
    // 0x802C7FF8: addiu       $a3, $zero, 0x10E
    ctx->r7 = ADD32(0, 0X10E);
    // 0x802C7FFC: jal         0x801E3EE0
    // 0x802C8000: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    func_801E3EE0(rdram, ctx);
        goto after_36;
    // 0x802C8000: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    after_36:
    // 0x802C8004: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
L_802C8008:
    // 0x802C8008: lui         $t0, 0x802D
    ctx->r8 = S32(0X802D << 16);
    // 0x802C800C: addiu       $t0, $t0, -0x727C
    ctx->r8 = ADD32(ctx->r8, -0X727C);
    // 0x802C8010: lw          $v0, 0x0($t0)
    ctx->r2 = MEM_W(ctx->r8, 0X0);
    // 0x802C8014: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x802C8018: lui         $v1, 0x802D
    ctx->r3 = S32(0X802D << 16);
    // 0x802C801C: beq         $v0, $at, L_802C8044
    if (ctx->r2 == ctx->r1) {
        // 0x802C8020: addiu       $v1, $v1, -0x7168
        ctx->r3 = ADD32(ctx->r3, -0X7168);
            goto L_802C8044;
    }
    // 0x802C8020: addiu       $v1, $v1, -0x7168
    ctx->r3 = ADD32(ctx->r3, -0X7168);
    // 0x802C8024: addiu       $at, $zero, 0x5
    ctx->r1 = ADD32(0, 0X5);
    // 0x802C8028: beq         $v0, $at, L_802C8100
    if (ctx->r2 == ctx->r1) {
        // 0x802C802C: or          $a1, $zero, $zero
        ctx->r5 = 0 | 0;
            goto L_802C8100;
    }
    // 0x802C802C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C8030: addiu       $at, $zero, 0x6
    ctx->r1 = ADD32(0, 0X6);
    // 0x802C8034: beql        $v0, $at, L_802C8104
    if (ctx->r2 == ctx->r1) {
        // 0x802C8038: addiu       $t7, $zero, 0xFF
        ctx->r15 = ADD32(0, 0XFF);
            goto L_802C8104;
    }
    goto skip_3;
    // 0x802C8038: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    skip_3:
    // 0x802C803C: b           L_802C819C
    // 0x802C8040: lw          $ra, 0x3C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X3C);
        goto L_802C819C;
    // 0x802C8040: lw          $ra, 0x3C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X3C);
L_802C8044:
    // 0x802C8044: lw          $t8, 0x0($v1)
    ctx->r24 = MEM_W(ctx->r3, 0X0);
    // 0x802C8048: addiu       $at, $zero, 0x5
    ctx->r1 = ADD32(0, 0X5);
    // 0x802C804C: addiu       $t7, $zero, 0x1C
    ctx->r15 = ADD32(0, 0X1C);
    // 0x802C8050: addiu       $t6, $t8, 0x1
    ctx->r14 = ADD32(ctx->r24, 0X1);
    // 0x802C8054: sll         $t1, $t6, 2
    ctx->r9 = S32(ctx->r14 << 2);
    // 0x802C8058: addu        $t1, $t1, $t6
    ctx->r9 = ADD32(ctx->r9, ctx->r14);
    // 0x802C805C: sll         $t1, $t1, 2
    ctx->r9 = S32(ctx->r9 << 2);
    // 0x802C8060: div         $zero, $t1, $at
    lo = S32(S64(S32(ctx->r9)) / S64(S32(ctx->r1))); hi = S32(S64(S32(ctx->r9)) % S64(S32(ctx->r1)));
    // 0x802C8064: mflo        $t1
    ctx->r9 = lo;
    // 0x802C8068: slti        $at, $t6, 0x5
    ctx->r1 = SIGNED(ctx->r14) < 0X5 ? 1 : 0;
    // 0x802C806C: bne         $at, $zero, L_802C8098
    if (ctx->r1 != 0) {
        // 0x802C8070: sw          $t6, 0x0($v1)
        MEM_W(0X0, ctx->r3) = ctx->r14;
            goto L_802C8098;
    }
    // 0x802C8070: sw          $t6, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r14;
    // 0x802C8074: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C8078: sw          $t7, -0x7170($at)
    MEM_W(-0X7170, ctx->r1) = ctx->r15;
    // 0x802C807C: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C8080: addiu       $t8, $zero, 0x44
    ctx->r24 = ADD32(0, 0X44);
    // 0x802C8084: sw          $t8, -0x716C($at)
    MEM_W(-0X716C, ctx->r1) = ctx->r24;
    // 0x802C8088: addiu       $t6, $zero, 0x5
    ctx->r14 = ADD32(0, 0X5);
    // 0x802C808C: sw          $t6, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r14;
    // 0x802C8090: b           L_802C80A8
    // 0x802C8094: sw          $zero, 0x0($v1)
    MEM_W(0X0, ctx->r3) = 0;
        goto L_802C80A8;
    // 0x802C8094: sw          $zero, 0x0($v1)
    MEM_W(0X0, ctx->r3) = 0;
L_802C8098:
    // 0x802C8098: addiu       $t9, $zero, 0x58
    ctx->r25 = ADD32(0, 0X58);
    // 0x802C809C: subu        $t7, $t9, $t1
    ctx->r15 = SUB32(ctx->r25, ctx->r9);
    // 0x802C80A0: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C80A4: sw          $t7, -0x716C($at)
    MEM_W(-0X716C, ctx->r1) = ctx->r15;
L_802C80A8:
    // 0x802C80A8: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C80AC: sw          $t8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r24;
    // 0x802C80B0: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C80B4: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x802C80B8: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    // 0x802C80BC: jal         0x801E7E74
    // 0x802C80C0: sw          $t1, 0x13C($sp)
    MEM_W(0X13C, ctx->r29) = ctx->r9;
    func_801E7E74(rdram, ctx);
        goto after_37;
    // 0x802C80C0: sw          $t1, 0x13C($sp)
    MEM_W(0X13C, ctx->r29) = ctx->r9;
    after_37:
    // 0x802C80C4: lw          $t1, 0x13C($sp)
    ctx->r9 = MEM_W(ctx->r29, 0X13C);
    // 0x802C80C8: lui         $t0, 0x802D
    ctx->r8 = S32(0X802D << 16);
    // 0x802C80CC: lw          $t0, -0x716C($t0)
    ctx->r8 = MEM_W(ctx->r8, -0X716C);
    // 0x802C80D0: lui         $v1, 0x802D
    ctx->r3 = S32(0X802D << 16);
    // 0x802C80D4: lw          $v1, -0x7170($v1)
    ctx->r3 = MEM_W(ctx->r3, -0X7170);
    // 0x802C80D8: sll         $t6, $t1, 1
    ctx->r14 = S32(ctx->r9 << 1);
    // 0x802C80DC: addu        $t9, $t6, $t0
    ctx->r25 = ADD32(ctx->r14, ctx->r8);
    // 0x802C80E0: sw          $t9, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r25;
    // 0x802C80E4: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C80E8: or          $a2, $t0, $zero
    ctx->r6 = ctx->r8 | 0;
    // 0x802C80EC: or          $a1, $v1, $zero
    ctx->r5 = ctx->r3 | 0;
    // 0x802C80F0: jal         0x801E7FD8
    // 0x802C80F4: addiu       $a3, $v1, 0x170
    ctx->r7 = ADD32(ctx->r3, 0X170);
    func_801E7FD8(rdram, ctx);
        goto after_38;
    // 0x802C80F4: addiu       $a3, $v1, 0x170
    ctx->r7 = ADD32(ctx->r3, 0X170);
    after_38:
    // 0x802C80F8: b           L_802C8198
    // 0x802C80FC: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
        goto L_802C8198;
    // 0x802C80FC: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
L_802C8100:
    // 0x802C8100: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
L_802C8104:
    // 0x802C8104: sw          $t7, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r15;
    // 0x802C8108: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x802C810C: jal         0x801E7E74
    // 0x802C8110: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_801E7E74(rdram, ctx);
        goto after_39;
    // 0x802C8110: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_39:
    // 0x802C8114: lui         $t0, 0x802D
    ctx->r8 = S32(0X802D << 16);
    // 0x802C8118: lw          $t0, -0x716C($t0)
    ctx->r8 = MEM_W(ctx->r8, -0X716C);
    // 0x802C811C: lui         $v1, 0x802D
    ctx->r3 = S32(0X802D << 16);
    // 0x802C8120: lw          $v1, -0x7170($v1)
    ctx->r3 = MEM_W(ctx->r3, -0X7170);
    // 0x802C8124: addiu       $t8, $t0, 0x28
    ctx->r24 = ADD32(ctx->r8, 0X28);
    // 0x802C8128: sw          $t8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r24;
    // 0x802C812C: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C8130: or          $a2, $t0, $zero
    ctx->r6 = ctx->r8 | 0;
    // 0x802C8134: or          $a1, $v1, $zero
    ctx->r5 = ctx->r3 | 0;
    // 0x802C8138: jal         0x801E7FD8
    // 0x802C813C: addiu       $a3, $v1, 0x170
    ctx->r7 = ADD32(ctx->r3, 0X170);
    func_801E7FD8(rdram, ctx);
        goto after_40;
    // 0x802C813C: addiu       $a3, $v1, 0x170
    ctx->r7 = ADD32(ctx->r3, 0X170);
    after_40:
    // 0x802C8140: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C8144: jal         0x802C8484
    // 0x802C8148: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    func_i13_802C8484(rdram, ctx);
        goto after_41;
    // 0x802C8148: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    after_41:
    // 0x802C814C: lui         $a1, 0x802D
    ctx->r5 = S32(0X802D << 16);
    // 0x802C8150: addiu       $a1, $a1, -0x727C
    ctx->r5 = ADD32(ctx->r5, -0X727C);
    // 0x802C8154: lw          $t6, 0x0($a1)
    ctx->r14 = MEM_W(ctx->r5, 0X0);
    // 0x802C8158: addiu       $at, $zero, 0x5
    ctx->r1 = ADD32(0, 0X5);
    // 0x802C815C: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C8160: bne         $t6, $at, L_802C8190
    if (ctx->r14 != ctx->r1) {
        // 0x802C8164: addiu       $t9, $zero, 0x1
        ctx->r25 = ADD32(0, 0X1);
            goto L_802C8190;
    }
    // 0x802C8164: addiu       $t9, $zero, 0x1
    ctx->r25 = ADD32(0, 0X1);
    // 0x802C8168: lui         $v1, 0x802D
    ctx->r3 = S32(0X802D << 16);
    // 0x802C816C: addiu       $v1, $v1, -0x7168
    ctx->r3 = ADD32(ctx->r3, -0X7168);
    // 0x802C8170: lw          $t9, 0x0($v1)
    ctx->r25 = MEM_W(ctx->r3, 0X0);
    // 0x802C8174: addiu       $t6, $zero, 0x6
    ctx->r14 = ADD32(0, 0X6);
    // 0x802C8178: addiu       $t7, $t9, 0x1
    ctx->r15 = ADD32(ctx->r25, 0X1);
    // 0x802C817C: slti        $at, $t7, 0x2
    ctx->r1 = SIGNED(ctx->r15) < 0X2 ? 1 : 0;
    // 0x802C8180: bne         $at, $zero, L_802C8198
    if (ctx->r1 != 0) {
        // 0x802C8184: sw          $t7, 0x0($v1)
        MEM_W(0X0, ctx->r3) = ctx->r15;
            goto L_802C8198;
    }
    // 0x802C8184: sw          $t7, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r15;
    // 0x802C8188: b           L_802C8198
    // 0x802C818C: sw          $t6, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r14;
        goto L_802C8198;
    // 0x802C818C: sw          $t6, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r14;
L_802C8190:
    // 0x802C8190: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C8194: sw          $t9, -0x7280($at)
    MEM_W(-0X7280, ctx->r1) = ctx->r25;
L_802C8198:
    // 0x802C8198: lw          $ra, 0x3C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X3C);
L_802C819C:
    // 0x802C819C: addiu       $sp, $sp, 0x150
    ctx->r29 = ADD32(ctx->r29, 0X150);
    // 0x802C81A0: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x802C81A4: jr          $ra
    // 0x802C81A8: nop

    return;
    // 0x802C81A8: nop

;}
RECOMP_FUNC void func_i13_802C81AC(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C81AC: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C81B0: sw          $zero, -0x727C($at)
    MEM_W(-0X727C, ctx->r1) = 0;
    // 0x802C81B4: addiu       $v1, $zero, 0x1
    ctx->r3 = ADD32(0, 0X1);
    // 0x802C81B8: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C81BC: sw          $v1, -0x7288($at)
    MEM_W(-0X7288, ctx->r1) = ctx->r3;
    // 0x802C81C0: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C81C4: addiu       $t6, $zero, 0x1C
    ctx->r14 = ADD32(0, 0X1C);
    // 0x802C81C8: sw          $t6, -0x7170($at)
    MEM_W(-0X7170, ctx->r1) = ctx->r14;
    // 0x802C81CC: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C81D0: addiu       $t7, $zero, 0x44
    ctx->r15 = ADD32(0, 0X44);
    // 0x802C81D4: sw          $t7, -0x716C($at)
    MEM_W(-0X716C, ctx->r1) = ctx->r15;
    // 0x802C81D8: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C81DC: sw          $zero, -0x7168($at)
    MEM_W(-0X7168, ctx->r1) = 0;
    // 0x802C81E0: addiu       $t8, $a0, -0x1
    ctx->r24 = ADD32(ctx->r4, -0X1);
    // 0x802C81E4: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x802C81E8: sltiu       $at, $t8, 0x6
    ctx->r1 = ctx->r24 < 0X6 ? 1 : 0;
    // 0x802C81EC: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x802C81F0: beq         $at, $zero, L_802C8284
    if (ctx->r1 == 0) {
        // 0x802C81F4: or          $v0, $zero, $zero
        ctx->r2 = 0 | 0;
            goto L_802C8284;
    }
    // 0x802C81F4: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    // 0x802C81F8: sll         $t8, $t8, 2
    ctx->r24 = S32(ctx->r24 << 2);
    // 0x802C81FC: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C8200: addu        $at, $at, $t8
    gpr jr_addend_802C8208 = ctx->r24;
    ctx->r1 = ADD32(ctx->r1, ctx->r24);
    // 0x802C8204: lw          $t8, -0x71AC($at)
    ctx->r24 = ADD32(ctx->r1, -0X71AC);
    // 0x802C8208: jr          $t8
    // 0x802C820C: nop

    switch (jr_addend_802C8208 >> 2) {
        case 0: goto L_802C8210; break;
        case 1: goto L_802C825C; break;
        case 2: goto L_802C8238; break;
        case 3: goto L_802C8248; break;
        case 4: goto L_802C825C; break;
        case 5: goto L_802C8224; break;
        default: switch_error(__func__, 0x802C8208, 0x802C8E54);
    }
    // 0x802C820C: nop

L_802C8210:
    // 0x802C8210: addiu       $t9, $zero, 0x4
    ctx->r25 = ADD32(0, 0X4);
    // 0x802C8214: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C8218: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
    // 0x802C821C: b           L_802C8284
    // 0x802C8220: sw          $t9, -0x7164($at)
    MEM_W(-0X7164, ctx->r1) = ctx->r25;
        goto L_802C8284;
    // 0x802C8220: sw          $t9, -0x7164($at)
    MEM_W(-0X7164, ctx->r1) = ctx->r25;
L_802C8224:
    // 0x802C8224: addiu       $t0, $zero, 0x6
    ctx->r8 = ADD32(0, 0X6);
    // 0x802C8228: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C822C: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
    // 0x802C8230: b           L_802C8284
    // 0x802C8234: sw          $t0, -0x7164($at)
    MEM_W(-0X7164, ctx->r1) = ctx->r8;
        goto L_802C8284;
    // 0x802C8234: sw          $t0, -0x7164($at)
    MEM_W(-0X7164, ctx->r1) = ctx->r8;
L_802C8238:
    // 0x802C8238: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C823C: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
    // 0x802C8240: b           L_802C8284
    // 0x802C8244: sw          $zero, -0x7164($at)
    MEM_W(-0X7164, ctx->r1) = 0;
        goto L_802C8284;
    // 0x802C8244: sw          $zero, -0x7164($at)
    MEM_W(-0X7164, ctx->r1) = 0;
L_802C8248:
    // 0x802C8248: addiu       $t1, $zero, 0x2
    ctx->r9 = ADD32(0, 0X2);
    // 0x802C824C: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C8250: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
    // 0x802C8254: b           L_802C8284
    // 0x802C8258: sw          $t1, -0x7164($at)
    MEM_W(-0X7164, ctx->r1) = ctx->r9;
        goto L_802C8284;
    // 0x802C8258: sw          $t1, -0x7164($at)
    MEM_W(-0X7164, ctx->r1) = ctx->r9;
L_802C825C:
    // 0x802C825C: lui         $t2, 0x802D
    ctx->r10 = S32(0X802D << 16);
    // 0x802C8260: lw          $t2, -0x72B0($t2)
    ctx->r10 = MEM_W(ctx->r10, -0X72B0);
    // 0x802C8264: or          $v0, $v1, $zero
    ctx->r2 = ctx->r3 | 0;
    // 0x802C8268: addiu       $t3, $zero, 0x3
    ctx->r11 = ADD32(0, 0X3);
    // 0x802C826C: bne         $t2, $zero, L_802C8280
    if (ctx->r10 != 0) {
        // 0x802C8270: lui         $at, 0x802D
        ctx->r1 = S32(0X802D << 16);
            goto L_802C8280;
    }
    // 0x802C8270: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C8274: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C8278: b           L_802C8284
    // 0x802C827C: sw          $v1, -0x7164($at)
    MEM_W(-0X7164, ctx->r1) = ctx->r3;
        goto L_802C8284;
    // 0x802C827C: sw          $v1, -0x7164($at)
    MEM_W(-0X7164, ctx->r1) = ctx->r3;
L_802C8280:
    // 0x802C8280: sw          $t3, -0x7164($at)
    MEM_W(-0X7164, ctx->r1) = ctx->r11;
L_802C8284:
    // 0x802C8284: beql        $v0, $zero, L_802C8298
    if (ctx->r2 == 0) {
        // 0x802C8288: lw          $ra, 0x14($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X14);
            goto L_802C8298;
    }
    goto skip_0;
    // 0x802C8288: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    skip_0:
    // 0x802C828C: jal         0x800C3E6C
    // 0x802C8290: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    func_800C3E6C(rdram, ctx);
        goto after_0;
    // 0x802C8290: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    after_0:
    // 0x802C8294: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C8298:
    // 0x802C8298: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x802C829C: jr          $ra
    // 0x802C82A0: nop

    return;
    // 0x802C82A0: nop

;}
RECOMP_FUNC void func_i13_802C82A4(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C82A4: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C82A8: sw          $zero, -0x7280($at)
    MEM_W(-0X7280, ctx->r1) = 0;
    // 0x802C82AC: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C82B0: addiu       $t6, $zero, 0x1
    ctx->r14 = ADD32(0, 0X1);
    // 0x802C82B4: sw          $t6, -0x727C($at)
    MEM_W(-0X727C, ctx->r1) = ctx->r14;
    // 0x802C82B8: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C82BC: addiu       $t7, $zero, 0x1C
    ctx->r15 = ADD32(0, 0X1C);
    // 0x802C82C0: sw          $t7, -0x7170($at)
    MEM_W(-0X7170, ctx->r1) = ctx->r15;
    // 0x802C82C4: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C82C8: addiu       $t8, $zero, 0x44
    ctx->r24 = ADD32(0, 0X44);
    // 0x802C82CC: sw          $t8, -0x716C($at)
    MEM_W(-0X716C, ctx->r1) = ctx->r24;
    // 0x802C82D0: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C82D4: sw          $zero, -0x7168($at)
    MEM_W(-0X7168, ctx->r1) = 0;
    // 0x802C82D8: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x802C82DC: beq         $a0, $at, L_802C8304
    if (ctx->r4 == ctx->r1) {
        // 0x802C82E0: addiu       $t9, $zero, 0x5
        ctx->r25 = ADD32(0, 0X5);
            goto L_802C8304;
    }
    // 0x802C82E0: addiu       $t9, $zero, 0x5
    ctx->r25 = ADD32(0, 0X5);
    // 0x802C82E4: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x802C82E8: beq         $a0, $at, L_802C8310
    if (ctx->r4 == ctx->r1) {
        // 0x802C82EC: addiu       $t0, $zero, 0x7
        ctx->r8 = ADD32(0, 0X7);
            goto L_802C8310;
    }
    // 0x802C82EC: addiu       $t0, $zero, 0x7
    ctx->r8 = ADD32(0, 0X7);
    // 0x802C82F0: addiu       $at, $zero, 0x4
    ctx->r1 = ADD32(0, 0X4);
    // 0x802C82F4: beq         $a0, $at, L_802C831C
    if (ctx->r4 == ctx->r1) {
        // 0x802C82F8: addiu       $t1, $zero, 0x8
        ctx->r9 = ADD32(0, 0X8);
            goto L_802C831C;
    }
    // 0x802C82F8: addiu       $t1, $zero, 0x8
    ctx->r9 = ADD32(0, 0X8);
    // 0x802C82FC: jr          $ra
    // 0x802C8300: nop

    return;
    // 0x802C8300: nop

L_802C8304:
    // 0x802C8304: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C8308: jr          $ra
    // 0x802C830C: sw          $t9, -0x7164($at)
    MEM_W(-0X7164, ctx->r1) = ctx->r25;
    return;
    // 0x802C830C: sw          $t9, -0x7164($at)
    MEM_W(-0X7164, ctx->r1) = ctx->r25;
L_802C8310:
    // 0x802C8310: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C8314: jr          $ra
    // 0x802C8318: sw          $t0, -0x7164($at)
    MEM_W(-0X7164, ctx->r1) = ctx->r8;
    return;
    // 0x802C8318: sw          $t0, -0x7164($at)
    MEM_W(-0X7164, ctx->r1) = ctx->r8;
L_802C831C:
    // 0x802C831C: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C8320: sw          $t1, -0x7164($at)
    MEM_W(-0X7164, ctx->r1) = ctx->r9;
    // 0x802C8324: jr          $ra
    // 0x802C8328: nop

    return;
    // 0x802C8328: nop

;}
RECOMP_FUNC void func_i13_802C832C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C832C: lui         $v0, 0x802D
    ctx->r2 = S32(0X802D << 16);
    // 0x802C8330: lw          $v0, -0x7288($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X7288);
    // 0x802C8334: addiu       $sp, $sp, -0x28
    ctx->r29 = ADD32(ctx->r29, -0X28);
    // 0x802C8338: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x802C833C: beq         $v0, $at, L_802C836C
    if (ctx->r2 == ctx->r1) {
        // 0x802C8340: sw          $ra, 0x1C($sp)
        MEM_W(0X1C, ctx->r29) = ctx->r31;
            goto L_802C836C;
    }
    // 0x802C8340: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x802C8344: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x802C8348: beq         $v0, $at, L_802C8420
    if (ctx->r2 == ctx->r1) {
        // 0x802C834C: or          $a1, $zero, $zero
        ctx->r5 = 0 | 0;
            goto L_802C8420;
    }
    // 0x802C834C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C8350: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x802C8354: beq         $v0, $at, L_802C8420
    if (ctx->r2 == ctx->r1) {
        // 0x802C8358: addiu       $at, $zero, 0x5
        ctx->r1 = ADD32(0, 0X5);
            goto L_802C8420;
    }
    // 0x802C8358: addiu       $at, $zero, 0x5
    ctx->r1 = ADD32(0, 0X5);
    // 0x802C835C: beql        $v0, $at, L_802C8424
    if (ctx->r2 == ctx->r1) {
        // 0x802C8360: addiu       $t8, $zero, 0xFF
        ctx->r24 = ADD32(0, 0XFF);
            goto L_802C8424;
    }
    goto skip_0;
    // 0x802C8360: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    skip_0:
    // 0x802C8364: b           L_802C8474
    // 0x802C8368: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
        goto L_802C8474;
    // 0x802C8368: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
L_802C836C:
    // 0x802C836C: lui         $v1, 0x802D
    ctx->r3 = S32(0X802D << 16);
    // 0x802C8370: addiu       $v1, $v1, -0x7168
    ctx->r3 = ADD32(ctx->r3, -0X7168);
    // 0x802C8374: lw          $t6, 0x0($v1)
    ctx->r14 = MEM_W(ctx->r3, 0X0);
    // 0x802C8378: addiu       $at, $zero, 0x5
    ctx->r1 = ADD32(0, 0X5);
    // 0x802C837C: addiu       $t3, $zero, 0x58
    ctx->r11 = ADD32(0, 0X58);
    // 0x802C8380: addiu       $t7, $t6, 0x1
    ctx->r15 = ADD32(ctx->r14, 0X1);
    // 0x802C8384: sll         $t1, $t7, 2
    ctx->r9 = S32(ctx->r15 << 2);
    // 0x802C8388: addu        $t1, $t1, $t7
    ctx->r9 = ADD32(ctx->r9, ctx->r15);
    // 0x802C838C: sll         $t1, $t1, 2
    ctx->r9 = S32(ctx->r9 << 2);
    // 0x802C8390: div         $zero, $t1, $at
    lo = S32(S64(S32(ctx->r9)) / S64(S32(ctx->r1))); hi = S32(S64(S32(ctx->r9)) % S64(S32(ctx->r1)));
    // 0x802C8394: mflo        $t1
    ctx->r9 = lo;
    // 0x802C8398: slti        $at, $t7, 0x5
    ctx->r1 = SIGNED(ctx->r15) < 0X5 ? 1 : 0;
    // 0x802C839C: bne         $at, $zero, L_802C83BC
    if (ctx->r1 != 0) {
        // 0x802C83A0: sw          $t7, 0x0($v1)
        MEM_W(0X0, ctx->r3) = ctx->r15;
            goto L_802C83BC;
    }
    // 0x802C83A0: sw          $t7, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r15;
    // 0x802C83A4: addiu       $t9, $zero, 0x1C
    ctx->r25 = ADD32(0, 0X1C);
    // 0x802C83A8: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C83AC: sw          $t9, -0x7170($at)
    MEM_W(-0X7170, ctx->r1) = ctx->r25;
    // 0x802C83B0: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C83B4: addiu       $t2, $zero, 0x44
    ctx->r10 = ADD32(0, 0X44);
    // 0x802C83B8: sw          $t2, -0x716C($at)
    MEM_W(-0X716C, ctx->r1) = ctx->r10;
L_802C83BC:
    // 0x802C83BC: subu        $t4, $t3, $t1
    ctx->r12 = SUB32(ctx->r11, ctx->r9);
    // 0x802C83C0: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C83C4: addiu       $t5, $zero, 0xFF
    ctx->r13 = ADD32(0, 0XFF);
    // 0x802C83C8: sw          $t4, -0x716C($at)
    MEM_W(-0X716C, ctx->r1) = ctx->r12;
    // 0x802C83CC: sw          $t5, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r13;
    // 0x802C83D0: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C83D4: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x802C83D8: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    // 0x802C83DC: jal         0x801E7E74
    // 0x802C83E0: sw          $t1, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r9;
    func_801E7E74(rdram, ctx);
        goto after_0;
    // 0x802C83E0: sw          $t1, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r9;
    after_0:
    // 0x802C83E4: lw          $t1, 0x24($sp)
    ctx->r9 = MEM_W(ctx->r29, 0X24);
    // 0x802C83E8: lui         $t0, 0x802D
    ctx->r8 = S32(0X802D << 16);
    // 0x802C83EC: lw          $t0, -0x716C($t0)
    ctx->r8 = MEM_W(ctx->r8, -0X716C);
    // 0x802C83F0: lui         $v1, 0x802D
    ctx->r3 = S32(0X802D << 16);
    // 0x802C83F4: lw          $v1, -0x7170($v1)
    ctx->r3 = MEM_W(ctx->r3, -0X7170);
    // 0x802C83F8: sll         $t6, $t1, 1
    ctx->r14 = S32(ctx->r9 << 1);
    // 0x802C83FC: addu        $t7, $t6, $t0
    ctx->r15 = ADD32(ctx->r14, ctx->r8);
    // 0x802C8400: sw          $t7, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r15;
    // 0x802C8404: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C8408: or          $a2, $t0, $zero
    ctx->r6 = ctx->r8 | 0;
    // 0x802C840C: or          $a1, $v1, $zero
    ctx->r5 = ctx->r3 | 0;
    // 0x802C8410: addiu       $a3, $v1, 0x170
    ctx->r7 = ADD32(ctx->r3, 0X170);
    // 0x802C8414: addiu       $a3, $v1, 0x108
    ctx->r7 = ADD32(ctx->r3, 0X108);
    // 0x802C8418: b           L_802C8470
    // 0x802C841C: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
        goto L_802C8470;
    // 0x802C841C: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
L_802C8420:
    // 0x802C8420: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
L_802C8424:
    // 0x802C8424: sw          $t8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r24;
    // 0x802C8428: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x802C842C: jal         0x801E7E74
    // 0x802C8430: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_801E7E74(rdram, ctx);
        goto after_1;
    // 0x802C8430: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_1:
    // 0x802C8434: lui         $t0, 0x802D
    ctx->r8 = S32(0X802D << 16);
    // 0x802C8438: lw          $t0, -0x716C($t0)
    ctx->r8 = MEM_W(ctx->r8, -0X716C);
    // 0x802C843C: lui         $v1, 0x802D
    ctx->r3 = S32(0X802D << 16);
    // 0x802C8440: lw          $v1, -0x7170($v1)
    ctx->r3 = MEM_W(ctx->r3, -0X7170);
    // 0x802C8444: addiu       $t9, $t0, 0x28
    ctx->r25 = ADD32(ctx->r8, 0X28);
    // 0x802C8448: sw          $t9, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r25;
    // 0x802C844C: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C8450: or          $a2, $t0, $zero
    ctx->r6 = ctx->r8 | 0;
    // 0x802C8454: or          $a1, $v1, $zero
    ctx->r5 = ctx->r3 | 0;
    // 0x802C8458: jal         0x801E7FD8
    // 0x802C845C: addiu       $a3, $v1, 0x170
    ctx->r7 = ADD32(ctx->r3, 0X170);
    func_801E7FD8(rdram, ctx);
        goto after_2;
    // 0x802C845C: addiu       $a3, $v1, 0x170
    ctx->r7 = ADD32(ctx->r3, 0X170);
    after_2:
    // 0x802C8460: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C8464: jal         0x802C8484
    // 0x802C8468: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_i13_802C8484(rdram, ctx);
        goto after_3;
    // 0x802C8468: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_3:
    // 0x802C846C: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
L_802C8470:
    // 0x802C8470: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
L_802C8474:
    // 0x802C8474: addiu       $sp, $sp, 0x28
    ctx->r29 = ADD32(ctx->r29, 0X28);
    // 0x802C8478: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x802C847C: jr          $ra
    // 0x802C8480: nop

    return;
    // 0x802C8480: nop

;}
RECOMP_FUNC void func_i13_802C8484(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C8484: addiu       $sp, $sp, -0x68
    ctx->r29 = ADD32(ctx->r29, -0X68);
    // 0x802C8488: sw          $s0, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r16;
    // 0x802C848C: or          $s0, $a0, $zero
    ctx->r16 = ctx->r4 | 0;
    // 0x802C8490: sw          $ra, 0x64($sp)
    MEM_W(0X64, ctx->r29) = ctx->r31;
    // 0x802C8494: sw          $fp, 0x60($sp)
    MEM_W(0X60, ctx->r29) = ctx->r30;
    // 0x802C8498: sw          $s7, 0x5C($sp)
    MEM_W(0X5C, ctx->r29) = ctx->r23;
    // 0x802C849C: sw          $s6, 0x58($sp)
    MEM_W(0X58, ctx->r29) = ctx->r22;
    // 0x802C84A0: sw          $s5, 0x54($sp)
    MEM_W(0X54, ctx->r29) = ctx->r21;
    // 0x802C84A4: sw          $s4, 0x50($sp)
    MEM_W(0X50, ctx->r29) = ctx->r20;
    // 0x802C84A8: sw          $s3, 0x4C($sp)
    MEM_W(0X4C, ctx->r29) = ctx->r19;
    // 0x802C84AC: sw          $s2, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r18;
    // 0x802C84B0: bne         $a1, $zero, L_802C8508
    if (ctx->r5 != 0) {
        // 0x802C84B4: sw          $s1, 0x44($sp)
        MEM_W(0X44, ctx->r29) = ctx->r17;
            goto L_802C8508;
    }
    // 0x802C84B4: sw          $s1, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r17;
    // 0x802C84B8: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C84BC: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C84C0: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C84C4: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C84C8: sw          $t9, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r25;
    // 0x802C84CC: sw          $t9, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r25;
    // 0x802C84D0: sw          $t8, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r24;
    // 0x802C84D4: sw          $t8, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r24;
    // 0x802C84D8: sw          $t7, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r15;
    // 0x802C84DC: sw          $t7, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r15;
    // 0x802C84E0: sw          $t7, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r15;
    // 0x802C84E4: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x802C84E8: sw          $t6, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r14;
    // 0x802C84EC: sw          $t6, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r14;
    // 0x802C84F0: addiu       $a1, $zero, 0x4
    ctx->r5 = ADD32(0, 0X4);
    // 0x802C84F4: addiu       $a2, $zero, 0xFF
    ctx->r6 = ADD32(0, 0XFF);
    // 0x802C84F8: jal         0x801E946C
    // 0x802C84FC: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    func_801E946C(rdram, ctx);
        goto after_0;
    // 0x802C84FC: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    after_0:
    // 0x802C8500: b           L_802C8558
    // 0x802C8504: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
        goto L_802C8558;
    // 0x802C8504: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
L_802C8508:
    // 0x802C8508: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C850C: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C8510: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C8514: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C8518: sw          $t7, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r15;
    // 0x802C851C: sw          $t7, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r15;
    // 0x802C8520: sw          $t6, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r14;
    // 0x802C8524: sw          $t6, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r14;
    // 0x802C8528: sw          $t9, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r25;
    // 0x802C852C: sw          $t9, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r25;
    // 0x802C8530: sw          $t9, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r25;
    // 0x802C8534: sw          $t8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r24;
    // 0x802C8538: sw          $t8, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r24;
    // 0x802C853C: sw          $t8, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r24;
    // 0x802C8540: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x802C8544: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C8548: addiu       $a2, $zero, 0xFF
    ctx->r6 = ADD32(0, 0XFF);
    // 0x802C854C: jal         0x801E946C
    // 0x802C8550: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    func_801E946C(rdram, ctx);
        goto after_1;
    // 0x802C8550: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    after_1:
    // 0x802C8554: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
L_802C8558:
    // 0x802C8558: lui         $t6, 0x802D
    ctx->r14 = S32(0X802D << 16);
    // 0x802C855C: lw          $t6, -0x7164($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X7164);
    // 0x802C8560: sltiu       $at, $t6, 0x9
    ctx->r1 = ctx->r14 < 0X9 ? 1 : 0;
    // 0x802C8564: beq         $at, $zero, L_802C8C88
    if (ctx->r1 == 0) {
        // 0x802C8568: sll         $t6, $t6, 2
        ctx->r14 = S32(ctx->r14 << 2);
            goto L_802C8C88;
    }
    // 0x802C8568: sll         $t6, $t6, 2
    ctx->r14 = S32(ctx->r14 << 2);
    // 0x802C856C: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C8570: addu        $at, $at, $t6
    gpr jr_addend_802C8578 = ctx->r14;
    ctx->r1 = ADD32(ctx->r1, ctx->r14);
    // 0x802C8574: lw          $t6, -0x7194($at)
    ctx->r14 = ADD32(ctx->r1, -0X7194);
    // 0x802C8578: jr          $t6
    // 0x802C857C: nop

    switch (jr_addend_802C8578 >> 2) {
        case 0: goto L_802C8580; break;
        case 1: goto L_802C86BC; break;
        case 2: goto L_802C8714; break;
        case 3: goto L_802C86E8; break;
        case 4: goto L_802C885C; break;
        case 5: goto L_802C89A4; break;
        case 6: goto L_802C8AEC; break;
        case 7: goto L_802C8C34; break;
        case 8: goto L_802C8C60; break;
        default: switch_error(__func__, 0x802C8578, 0x802C8E6C);
    }
    // 0x802C857C: nop

L_802C8580:
    // 0x802C8580: lui         $t0, 0x807
    ctx->r8 = S32(0X807 << 16);
    // 0x802C8584: lui         $fp, 0x73F
    ctx->r30 = S32(0X73F << 16);
    // 0x802C8588: lui         $s7, 0xFD68
    ctx->r23 = S32(0XFD68 << 16);
    // 0x802C858C: lui         $s6, 0x400
    ctx->r22 = S32(0X400 << 16);
    // 0x802C8590: lui         $s2, 0x8
    ctx->r18 = S32(0X8 << 16);
    // 0x802C8594: lui         $t4, 0x708
    ctx->r12 = S32(0X708 << 16);
    // 0x802C8598: lui         $t3, 0xF568
    ctx->r11 = S32(0XF568 << 16);
    // 0x802C859C: ori         $t3, $t3, 0x4000
    ctx->r11 = ctx->r11 | 0X4000;
    // 0x802C85A0: ori         $t4, $t4, 0x200
    ctx->r12 = ctx->r12 | 0X200;
    // 0x802C85A4: ori         $s2, $s2, 0x200
    ctx->r18 = ctx->r18 | 0X200;
    // 0x802C85A8: ori         $s6, $s6, 0x400
    ctx->r22 = ctx->r22 | 0X400;
    // 0x802C85AC: ori         $s7, $s7, 0xFF
    ctx->r23 = ctx->r23 | 0XFF;
    // 0x802C85B0: ori         $fp, $fp, 0xC038
    ctx->r30 = ctx->r30 | 0XC038;
    // 0x802C85B4: addiu       $t0, $t0, -0x5588
    ctx->r8 = ADD32(ctx->r8, -0X5588);
    // 0x802C85B8: addiu       $a3, $zero, 0x58
    ctx->r7 = ADD32(0, 0X58);
    // 0x802C85BC: addiu       $a2, $zero, 0x49
    ctx->r6 = ADD32(0, 0X49);
    // 0x802C85C0: lui         $s5, 0xB200
    ctx->r21 = S32(0XB200 << 16);
    // 0x802C85C4: lui         $s4, 0xB300
    ctx->r20 = S32(0XB300 << 16);
    // 0x802C85C8: lui         $s3, 0xF200
    ctx->r19 = S32(0XF200 << 16);
    // 0x802C85CC: lui         $s1, 0xE700
    ctx->r17 = S32(0XE700 << 16);
    // 0x802C85D0: lui         $ra, 0xF400
    ctx->r31 = S32(0XF400 << 16);
    // 0x802C85D4: lui         $t5, 0xE600
    ctx->r13 = S32(0XE600 << 16);
L_802C85D8:
    // 0x802C85D8: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
    // 0x802C85DC: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C85E0: or          $v1, $s0, $zero
    ctx->r3 = ctx->r16 | 0;
    // 0x802C85E4: sw          $s7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r23;
    // 0x802C85E8: sw          $t0, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r8;
    // 0x802C85EC: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C85F0: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x802C85F4: sw          $t4, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r12;
    // 0x802C85F8: sw          $t3, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r11;
    // 0x802C85FC: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C8600: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    // 0x802C8604: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C8608: sw          $zero, 0x4($a0)
    MEM_W(0X4, ctx->r4) = 0;
    // 0x802C860C: sw          $t5, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r13;
    // 0x802C8610: or          $t1, $s0, $zero
    ctx->r9 = ctx->r16 | 0;
    // 0x802C8614: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C8618: sw          $fp, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r30;
    // 0x802C861C: sw          $ra, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r31;
    // 0x802C8620: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
    // 0x802C8624: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C8628: sw          $zero, 0x4($t1)
    MEM_W(0X4, ctx->r9) = 0;
    // 0x802C862C: sw          $s1, 0x0($t1)
    MEM_W(0X0, ctx->r9) = ctx->r17;
    // 0x802C8630: or          $v1, $s0, $zero
    ctx->r3 = ctx->r16 | 0;
    // 0x802C8634: lui         $t7, 0x3F
    ctx->r15 = S32(0X3F << 16);
    // 0x802C8638: ori         $t7, $t7, 0xC038
    ctx->r15 = ctx->r15 | 0XC038;
    // 0x802C863C: sw          $s2, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r18;
    // 0x802C8640: sw          $t3, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r11;
    // 0x802C8644: sll         $t8, $a3, 2
    ctx->r24 = S32(ctx->r7 << 2);
    // 0x802C8648: sw          $t7, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r15;
    // 0x802C864C: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C8650: andi        $t9, $t8, 0xFFF
    ctx->r25 = ctx->r24 & 0XFFF;
    // 0x802C8654: lui         $at, 0xE455
    ctx->r1 = S32(0XE455 << 16);
    // 0x802C8658: or          $t6, $t9, $at
    ctx->r14 = ctx->r25 | ctx->r1;
    // 0x802C865C: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x802C8660: sll         $t7, $a2, 2
    ctx->r15 = S32(ctx->r6 << 2);
    // 0x802C8664: sw          $s3, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r19;
    // 0x802C8668: andi        $t8, $t7, 0xFFF
    ctx->r24 = ctx->r15 & 0XFFF;
    // 0x802C866C: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C8670: lui         $at, 0x15
    ctx->r1 = S32(0X15 << 16);
    // 0x802C8674: or          $t9, $t8, $at
    ctx->r25 = ctx->r24 | ctx->r1;
    // 0x802C8678: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    // 0x802C867C: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C8680: sw          $t9, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r25;
    // 0x802C8684: sw          $t6, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r14;
    // 0x802C8688: or          $t2, $s0, $zero
    ctx->r10 = ctx->r16 | 0;
    // 0x802C868C: addiu       $at, $zero, 0x67
    ctx->r1 = ADD32(0, 0X67);
    // 0x802C8690: addiu       $a2, $a2, 0xF
    ctx->r6 = ADD32(ctx->r6, 0XF);
    // 0x802C8694: sw          $zero, 0x4($a1)
    MEM_W(0X4, ctx->r5) = 0;
    // 0x802C8698: sw          $s4, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r20;
    // 0x802C869C: addiu       $a3, $a3, 0xF
    ctx->r7 = ADD32(ctx->r7, 0XF);
    // 0x802C86A0: addiu       $t0, $t0, 0xF00
    ctx->r8 = ADD32(ctx->r8, 0XF00);
    // 0x802C86A4: sw          $s6, 0x4($t2)
    MEM_W(0X4, ctx->r10) = ctx->r22;
    // 0x802C86A8: sw          $s5, 0x0($t2)
    MEM_W(0X0, ctx->r10) = ctx->r21;
    // 0x802C86AC: bne         $a2, $at, L_802C85D8
    if (ctx->r6 != ctx->r1) {
        // 0x802C86B0: addiu       $s0, $s0, 0x8
        ctx->r16 = ADD32(ctx->r16, 0X8);
            goto L_802C85D8;
    }
    // 0x802C86B0: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C86B4: b           L_802C8C8C
    // 0x802C86B8: lw          $ra, 0x64($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X64);
        goto L_802C8C8C;
    // 0x802C86B8: lw          $ra, 0x64($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X64);
L_802C86BC:
    // 0x802C86BC: addiu       $t6, $zero, 0x50
    ctx->r14 = ADD32(0, 0X50);
    // 0x802C86C0: addiu       $t7, $zero, 0x2
    ctx->r15 = ADD32(0, 0X2);
    // 0x802C86C4: sw          $t7, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r15;
    // 0x802C86C8: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x802C86CC: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x802C86D0: addiu       $a1, $zero, 0x3
    ctx->r5 = ADD32(0, 0X3);
    // 0x802C86D4: addiu       $a2, $zero, 0x7
    ctx->r6 = ADD32(0, 0X7);
    // 0x802C86D8: jal         0x801E3EE0
    // 0x802C86DC: addiu       $a3, $zero, 0x7C
    ctx->r7 = ADD32(0, 0X7C);
    func_801E3EE0(rdram, ctx);
        goto after_2;
    // 0x802C86DC: addiu       $a3, $zero, 0x7C
    ctx->r7 = ADD32(0, 0X7C);
    after_2:
    // 0x802C86E0: b           L_802C8C88
    // 0x802C86E4: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
        goto L_802C8C88;
    // 0x802C86E4: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
L_802C86E8:
    // 0x802C86E8: addiu       $t8, $zero, 0x50
    ctx->r24 = ADD32(0, 0X50);
    // 0x802C86EC: addiu       $t9, $zero, 0x2
    ctx->r25 = ADD32(0, 0X2);
    // 0x802C86F0: sw          $t9, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r25;
    // 0x802C86F4: sw          $t8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r24;
    // 0x802C86F8: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x802C86FC: addiu       $a1, $zero, 0x3
    ctx->r5 = ADD32(0, 0X3);
    // 0x802C8700: addiu       $a2, $zero, 0x9
    ctx->r6 = ADD32(0, 0X9);
    // 0x802C8704: jal         0x801E3EE0
    // 0x802C8708: addiu       $a3, $zero, 0x78
    ctx->r7 = ADD32(0, 0X78);
    func_801E3EE0(rdram, ctx);
        goto after_3;
    // 0x802C8708: addiu       $a3, $zero, 0x78
    ctx->r7 = ADD32(0, 0X78);
    after_3:
    // 0x802C870C: b           L_802C8C88
    // 0x802C8710: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
        goto L_802C8C88;
    // 0x802C8710: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
L_802C8714:
    // 0x802C8714: lui         $t0, 0x807
    ctx->r8 = S32(0X807 << 16);
    // 0x802C8718: lui         $fp, 0x72F
    ctx->r30 = S32(0X72F << 16);
    // 0x802C871C: lui         $s7, 0xFD68
    ctx->r23 = S32(0XFD68 << 16);
    // 0x802C8720: lui         $s6, 0x400
    ctx->r22 = S32(0X400 << 16);
    // 0x802C8724: lui         $s2, 0x8
    ctx->r18 = S32(0X8 << 16);
    // 0x802C8728: lui         $t4, 0x708
    ctx->r12 = S32(0X708 << 16);
    // 0x802C872C: lui         $t3, 0xF568
    ctx->r11 = S32(0XF568 << 16);
    // 0x802C8730: ori         $t3, $t3, 0x3000
    ctx->r11 = ctx->r11 | 0X3000;
    // 0x802C8734: ori         $t4, $t4, 0x200
    ctx->r12 = ctx->r12 | 0X200;
    // 0x802C8738: ori         $s2, $s2, 0x200
    ctx->r18 = ctx->r18 | 0X200;
    // 0x802C873C: ori         $s6, $s6, 0x400
    ctx->r22 = ctx->r22 | 0X400;
    // 0x802C8740: ori         $s7, $s7, 0xBF
    ctx->r23 = ctx->r23 | 0XBF;
    // 0x802C8744: ori         $fp, $fp, 0xC038
    ctx->r30 = ctx->r30 | 0XC038;
    // 0x802C8748: addiu       $t0, $t0, -0x3780
    ctx->r8 = ADD32(ctx->r8, -0X3780);
    // 0x802C874C: addiu       $a3, $zero, 0x58
    ctx->r7 = ADD32(0, 0X58);
    // 0x802C8750: addiu       $a2, $zero, 0x49
    ctx->r6 = ADD32(0, 0X49);
    // 0x802C8754: lui         $s5, 0xB200
    ctx->r21 = S32(0XB200 << 16);
    // 0x802C8758: lui         $s4, 0xB300
    ctx->r20 = S32(0XB300 << 16);
    // 0x802C875C: lui         $s3, 0xF200
    ctx->r19 = S32(0XF200 << 16);
    // 0x802C8760: lui         $s1, 0xE700
    ctx->r17 = S32(0XE700 << 16);
    // 0x802C8764: lui         $ra, 0xF400
    ctx->r31 = S32(0XF400 << 16);
    // 0x802C8768: lui         $t5, 0xE600
    ctx->r13 = S32(0XE600 << 16);
L_802C876C:
    // 0x802C876C: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
    // 0x802C8770: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C8774: or          $v1, $s0, $zero
    ctx->r3 = ctx->r16 | 0;
    // 0x802C8778: sw          $s7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r23;
    // 0x802C877C: sw          $t0, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r8;
    // 0x802C8780: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C8784: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x802C8788: sw          $t4, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r12;
    // 0x802C878C: sw          $t3, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r11;
    // 0x802C8790: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C8794: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    // 0x802C8798: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C879C: sw          $zero, 0x4($a0)
    MEM_W(0X4, ctx->r4) = 0;
    // 0x802C87A0: sw          $t5, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r13;
    // 0x802C87A4: or          $t1, $s0, $zero
    ctx->r9 = ctx->r16 | 0;
    // 0x802C87A8: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C87AC: sw          $fp, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r30;
    // 0x802C87B0: sw          $ra, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r31;
    // 0x802C87B4: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
    // 0x802C87B8: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C87BC: sw          $zero, 0x4($t1)
    MEM_W(0X4, ctx->r9) = 0;
    // 0x802C87C0: sw          $s1, 0x0($t1)
    MEM_W(0X0, ctx->r9) = ctx->r17;
    // 0x802C87C4: or          $v1, $s0, $zero
    ctx->r3 = ctx->r16 | 0;
    // 0x802C87C8: lui         $t6, 0x2F
    ctx->r14 = S32(0X2F << 16);
    // 0x802C87CC: sll         $t7, $a3, 2
    ctx->r15 = S32(ctx->r7 << 2);
    // 0x802C87D0: lui         $at, 0xE44D
    ctx->r1 = S32(0XE44D << 16);
    // 0x802C87D4: ori         $t6, $t6, 0xC038
    ctx->r14 = ctx->r14 | 0XC038;
    // 0x802C87D8: sw          $s2, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r18;
    // 0x802C87DC: sw          $t3, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r11;
    // 0x802C87E0: ori         $at, $at, 0xC000
    ctx->r1 = ctx->r1 | 0XC000;
    // 0x802C87E4: andi        $t8, $t7, 0xFFF
    ctx->r24 = ctx->r15 & 0XFFF;
    // 0x802C87E8: sw          $t6, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r14;
    // 0x802C87EC: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C87F0: or          $t9, $t8, $at
    ctx->r25 = ctx->r24 | ctx->r1;
    // 0x802C87F4: lui         $at, 0x1D
    ctx->r1 = S32(0X1D << 16);
    // 0x802C87F8: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x802C87FC: sll         $t6, $a2, 2
    ctx->r14 = S32(ctx->r6 << 2);
    // 0x802C8800: sw          $s3, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r19;
    // 0x802C8804: andi        $t7, $t6, 0xFFF
    ctx->r15 = ctx->r14 & 0XFFF;
    // 0x802C8808: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C880C: ori         $at, $at, 0xC000
    ctx->r1 = ctx->r1 | 0XC000;
    // 0x802C8810: or          $t8, $t7, $at
    ctx->r24 = ctx->r15 | ctx->r1;
    // 0x802C8814: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    // 0x802C8818: sw          $t9, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r25;
    // 0x802C881C: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C8820: sw          $t8, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r24;
    // 0x802C8824: lui         $t9, 0x807
    ctx->r25 = S32(0X807 << 16);
    // 0x802C8828: or          $t2, $s0, $zero
    ctx->r10 = ctx->r16 | 0;
    // 0x802C882C: addiu       $t9, $t9, -0x2100
    ctx->r25 = ADD32(ctx->r25, -0X2100);
    // 0x802C8830: addiu       $t0, $t0, 0xB40
    ctx->r8 = ADD32(ctx->r8, 0XB40);
    // 0x802C8834: sw          $zero, 0x4($a1)
    MEM_W(0X4, ctx->r5) = 0;
    // 0x802C8838: sw          $s4, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r20;
    // 0x802C883C: addiu       $a2, $a2, 0xF
    ctx->r6 = ADD32(ctx->r6, 0XF);
    // 0x802C8840: addiu       $a3, $a3, 0xF
    ctx->r7 = ADD32(ctx->r7, 0XF);
    // 0x802C8844: sw          $s6, 0x4($t2)
    MEM_W(0X4, ctx->r10) = ctx->r22;
    // 0x802C8848: sw          $s5, 0x0($t2)
    MEM_W(0X0, ctx->r10) = ctx->r21;
    // 0x802C884C: bne         $t0, $t9, L_802C876C
    if (ctx->r8 != ctx->r25) {
        // 0x802C8850: addiu       $s0, $s0, 0x8
        ctx->r16 = ADD32(ctx->r16, 0X8);
            goto L_802C876C;
    }
    // 0x802C8850: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C8854: b           L_802C8C8C
    // 0x802C8858: lw          $ra, 0x64($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X64);
        goto L_802C8C8C;
    // 0x802C8858: lw          $ra, 0x64($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X64);
L_802C885C:
    // 0x802C885C: lui         $t0, 0x807
    ctx->r8 = S32(0X807 << 16);
    // 0x802C8860: lui         $fp, 0x73B
    ctx->r30 = S32(0X73B << 16);
    // 0x802C8864: lui         $s7, 0xFD68
    ctx->r23 = S32(0XFD68 << 16);
    // 0x802C8868: lui         $s6, 0x400
    ctx->r22 = S32(0X400 << 16);
    // 0x802C886C: lui         $s2, 0x8
    ctx->r18 = S32(0X8 << 16);
    // 0x802C8870: lui         $t4, 0x708
    ctx->r12 = S32(0X708 << 16);
    // 0x802C8874: lui         $t3, 0xF568
    ctx->r11 = S32(0XF568 << 16);
    // 0x802C8878: ori         $t3, $t3, 0x3C00
    ctx->r11 = ctx->r11 | 0X3C00;
    // 0x802C887C: ori         $t4, $t4, 0x200
    ctx->r12 = ctx->r12 | 0X200;
    // 0x802C8880: ori         $s2, $s2, 0x200
    ctx->r18 = ctx->r18 | 0X200;
    // 0x802C8884: ori         $s6, $s6, 0x400
    ctx->r22 = ctx->r22 | 0X400;
    // 0x802C8888: ori         $s7, $s7, 0xEF
    ctx->r23 = ctx->r23 | 0XEF;
    // 0x802C888C: ori         $fp, $fp, 0xC038
    ctx->r30 = ctx->r30 | 0XC038;
    // 0x802C8890: addiu       $t0, $t0, -0x71B0
    ctx->r8 = ADD32(ctx->r8, -0X71B0);
    // 0x802C8894: addiu       $a3, $zero, 0x58
    ctx->r7 = ADD32(0, 0X58);
    // 0x802C8898: addiu       $a2, $zero, 0x49
    ctx->r6 = ADD32(0, 0X49);
    // 0x802C889C: lui         $s5, 0xB200
    ctx->r21 = S32(0XB200 << 16);
    // 0x802C88A0: lui         $s4, 0xB300
    ctx->r20 = S32(0XB300 << 16);
    // 0x802C88A4: lui         $s3, 0xF200
    ctx->r19 = S32(0XF200 << 16);
    // 0x802C88A8: lui         $s1, 0xE700
    ctx->r17 = S32(0XE700 << 16);
    // 0x802C88AC: lui         $ra, 0xF400
    ctx->r31 = S32(0XF400 << 16);
    // 0x802C88B0: lui         $t5, 0xE600
    ctx->r13 = S32(0XE600 << 16);
L_802C88B4:
    // 0x802C88B4: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
    // 0x802C88B8: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C88BC: or          $v1, $s0, $zero
    ctx->r3 = ctx->r16 | 0;
    // 0x802C88C0: sw          $s7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r23;
    // 0x802C88C4: sw          $t0, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r8;
    // 0x802C88C8: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C88CC: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x802C88D0: sw          $t4, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r12;
    // 0x802C88D4: sw          $t3, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r11;
    // 0x802C88D8: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C88DC: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    // 0x802C88E0: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C88E4: sw          $zero, 0x4($a0)
    MEM_W(0X4, ctx->r4) = 0;
    // 0x802C88E8: sw          $t5, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r13;
    // 0x802C88EC: or          $t1, $s0, $zero
    ctx->r9 = ctx->r16 | 0;
    // 0x802C88F0: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C88F4: sw          $fp, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r30;
    // 0x802C88F8: sw          $ra, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r31;
    // 0x802C88FC: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
    // 0x802C8900: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C8904: sw          $zero, 0x4($t1)
    MEM_W(0X4, ctx->r9) = 0;
    // 0x802C8908: sw          $s1, 0x0($t1)
    MEM_W(0X0, ctx->r9) = ctx->r17;
    // 0x802C890C: or          $v1, $s0, $zero
    ctx->r3 = ctx->r16 | 0;
    // 0x802C8910: lui         $t6, 0x3B
    ctx->r14 = S32(0X3B << 16);
    // 0x802C8914: sll         $t7, $a3, 2
    ctx->r15 = S32(ctx->r7 << 2);
    // 0x802C8918: lui         $at, 0xE447
    ctx->r1 = S32(0XE447 << 16);
    // 0x802C891C: ori         $t6, $t6, 0xC038
    ctx->r14 = ctx->r14 | 0XC038;
    // 0x802C8920: sw          $s2, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r18;
    // 0x802C8924: sw          $t3, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r11;
    // 0x802C8928: ori         $at, $at, 0x8000
    ctx->r1 = ctx->r1 | 0X8000;
    // 0x802C892C: lui         $at, 0xE454
    ctx->r1 = S32(0XE454 << 16);
    // 0x802C8930: sw          $t6, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r14;
    // 0x802C8934: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C8938: or          $t9, $t8, $at
    ctx->r25 = ctx->r24 | ctx->r1;
    // 0x802C893C: lui         $at, 0x18
    ctx->r1 = S32(0X18 << 16);
    // 0x802C8940: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x802C8944: sll         $t6, $a2, 2
    ctx->r14 = S32(ctx->r6 << 2);
    // 0x802C8948: sw          $s3, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r19;
    // 0x802C894C: andi        $t7, $t6, 0xFFF
    ctx->r15 = ctx->r14 & 0XFFF;
    // 0x802C8950: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C8954: ori         $at, $at, 0x8000
    ctx->r1 = ctx->r1 | 0X8000;
    // 0x802C8958: or          $t8, $t7, $at
    ctx->r24 = ctx->r15 | ctx->r1;
    // 0x802C895C: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    // 0x802C8960: sw          $t9, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r25;
    // 0x802C8964: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C8968: sw          $t8, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r24;
    // 0x802C896C: lui         $t9, 0x807
    ctx->r25 = S32(0X807 << 16);
    // 0x802C8970: or          $t2, $s0, $zero
    ctx->r10 = ctx->r16 | 0;
    // 0x802C8974: addiu       $t9, $t9, -0x5590
    ctx->r25 = ADD32(ctx->r25, -0X5590);
    // 0x802C8978: addiu       $t0, $t0, 0xE10
    ctx->r8 = ADD32(ctx->r8, 0XE10);
    // 0x802C897C: sw          $zero, 0x4($a1)
    MEM_W(0X4, ctx->r5) = 0;
    // 0x802C8980: sw          $s4, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r20;
    // 0x802C8984: addiu       $a2, $a2, 0xF
    ctx->r6 = ADD32(ctx->r6, 0XF);
    // 0x802C8988: addiu       $a3, $a3, 0xF
    ctx->r7 = ADD32(ctx->r7, 0XF);
    // 0x802C898C: sw          $s6, 0x4($t2)
    MEM_W(0X4, ctx->r10) = ctx->r22;
    // 0x802C8990: sw          $s5, 0x0($t2)
    MEM_W(0X0, ctx->r10) = ctx->r21;
    // 0x802C8994: bne         $t0, $t9, L_802C88B4
    if (ctx->r8 != ctx->r25) {
        // 0x802C8998: addiu       $s0, $s0, 0x8
        ctx->r16 = ADD32(ctx->r16, 0X8);
            goto L_802C88B4;
    }
    // 0x802C8998: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C899C: b           L_802C8C8C
    // 0x802C89A0: lw          $ra, 0x64($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X64);
        goto L_802C8C8C;
    // 0x802C89A0: lw          $ra, 0x64($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X64);
L_802C89A4:
    // 0x802C89A4: lui         $t0, 0x806
    ctx->r8 = S32(0X806 << 16);
    // 0x802C89A8: lui         $fp, 0x73F
    ctx->r30 = S32(0X73F << 16);
    // 0x802C89AC: lui         $s7, 0xFD68
    ctx->r23 = S32(0XFD68 << 16);
    // 0x802C89B0: lui         $s6, 0x400
    ctx->r22 = S32(0X400 << 16);
    // 0x802C89B4: lui         $s2, 0x8
    ctx->r18 = S32(0X8 << 16);
    // 0x802C89B8: lui         $t4, 0x708
    ctx->r12 = S32(0X708 << 16);
    // 0x802C89BC: lui         $t3, 0xF568
    ctx->r11 = S32(0XF568 << 16);
    // 0x802C89C0: ori         $t3, $t3, 0x4000
    ctx->r11 = ctx->r11 | 0X4000;
    // 0x802C89C4: ori         $t4, $t4, 0x200
    ctx->r12 = ctx->r12 | 0X200;
    // 0x802C89C8: ori         $s2, $s2, 0x200
    ctx->r18 = ctx->r18 | 0X200;
    // 0x802C89CC: ori         $s6, $s6, 0x400
    ctx->r22 = ctx->r22 | 0X400;
    // 0x802C89D0: ori         $s7, $s7, 0xFF
    ctx->r23 = ctx->r23 | 0XFF;
    // 0x802C89D4: ori         $fp, $fp, 0xC038
    ctx->r30 = ctx->r30 | 0XC038;
    // 0x802C89D8: addiu       $t0, $t0, 0x7048
    ctx->r8 = ADD32(ctx->r8, 0X7048);
    // 0x802C89DC: addiu       $a3, $zero, 0x58
    ctx->r7 = ADD32(0, 0X58);
    // 0x802C89E0: addiu       $a2, $zero, 0x49
    ctx->r6 = ADD32(0, 0X49);
    // 0x802C89E4: lui         $s5, 0xB200
    ctx->r21 = S32(0XB200 << 16);
    // 0x802C89E8: lui         $s4, 0xB300
    ctx->r20 = S32(0XB300 << 16);
    // 0x802C89EC: lui         $s3, 0xF200
    ctx->r19 = S32(0XF200 << 16);
    // 0x802C89F0: lui         $s1, 0xE700
    ctx->r17 = S32(0XE700 << 16);
    // 0x802C89F4: lui         $ra, 0xF400
    ctx->r31 = S32(0XF400 << 16);
    // 0x802C89F8: lui         $t5, 0xE600
    ctx->r13 = S32(0XE600 << 16);
L_802C89FC:
    // 0x802C89FC: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
    // 0x802C8A00: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C8A04: or          $v1, $s0, $zero
    ctx->r3 = ctx->r16 | 0;
    // 0x802C8A08: sw          $s7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r23;
    // 0x802C8A0C: sw          $t0, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r8;
    // 0x802C8A10: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C8A14: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x802C8A18: sw          $t4, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r12;
    // 0x802C8A1C: sw          $t3, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r11;
    // 0x802C8A20: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C8A24: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    // 0x802C8A28: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C8A2C: sw          $zero, 0x4($a0)
    MEM_W(0X4, ctx->r4) = 0;
    // 0x802C8A30: sw          $t5, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r13;
    // 0x802C8A34: or          $t1, $s0, $zero
    ctx->r9 = ctx->r16 | 0;
    // 0x802C8A38: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C8A3C: sw          $fp, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r30;
    // 0x802C8A40: sw          $ra, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r31;
    // 0x802C8A44: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
    // 0x802C8A48: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C8A4C: sw          $zero, 0x4($t1)
    MEM_W(0X4, ctx->r9) = 0;
    // 0x802C8A50: sw          $s1, 0x0($t1)
    MEM_W(0X0, ctx->r9) = ctx->r17;
    // 0x802C8A54: or          $v1, $s0, $zero
    ctx->r3 = ctx->r16 | 0;
    // 0x802C8A58: lui         $t6, 0x3F
    ctx->r14 = S32(0X3F << 16);
    // 0x802C8A5C: sll         $t7, $a3, 2
    ctx->r15 = S32(ctx->r7 << 2);
    // 0x802C8A60: lui         $at, 0xE455
    ctx->r1 = S32(0XE455 << 16);
    // 0x802C8A64: ori         $t6, $t6, 0xC038
    ctx->r14 = ctx->r14 | 0XC038;
    // 0x802C8A68: sw          $s2, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r18;
    // 0x802C8A6C: sw          $t3, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r11;
    // 0x802C8A70: ori         $at, $at, 0x4000
    ctx->r1 = ctx->r1 | 0X4000;
    // 0x802C8A74: andi        $t8, $t7, 0xFFF
    ctx->r24 = ctx->r15 & 0XFFF;
    // 0x802C8A78: sw          $t6, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r14;
    // 0x802C8A7C: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C8A80: or          $t9, $t8, $at
    ctx->r25 = ctx->r24 | ctx->r1;
    // 0x802C8A84: lui         $at, 0x15
    ctx->r1 = S32(0X15 << 16);
    // 0x802C8A88: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x802C8A8C: sll         $t6, $a2, 2
    ctx->r14 = S32(ctx->r6 << 2);
    // 0x802C8A90: sw          $s3, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r19;
    // 0x802C8A94: andi        $t7, $t6, 0xFFF
    ctx->r15 = ctx->r14 & 0XFFF;
    // 0x802C8A98: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C8A9C: ori         $at, $at, 0x4000
    ctx->r1 = ctx->r1 | 0X4000;
    // 0x802C8AA0: or          $t8, $t7, $at
    ctx->r24 = ctx->r15 | ctx->r1;
    // 0x802C8AA4: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    // 0x802C8AA8: sw          $t9, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r25;
    // 0x802C8AAC: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C8AB0: sw          $t8, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r24;
    // 0x802C8AB4: lui         $t9, 0x807
    ctx->r25 = S32(0X807 << 16);
    // 0x802C8AB8: or          $t2, $s0, $zero
    ctx->r10 = ctx->r16 | 0;
    // 0x802C8ABC: addiu       $t9, $t9, -0x71B8
    ctx->r25 = ADD32(ctx->r25, -0X71B8);
    // 0x802C8AC0: addiu       $t0, $t0, 0xF00
    ctx->r8 = ADD32(ctx->r8, 0XF00);
    // 0x802C8AC4: sw          $zero, 0x4($a1)
    MEM_W(0X4, ctx->r5) = 0;
    // 0x802C8AC8: sw          $s4, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r20;
    // 0x802C8ACC: addiu       $a2, $a2, 0xF
    ctx->r6 = ADD32(ctx->r6, 0XF);
    // 0x802C8AD0: addiu       $a3, $a3, 0xF
    ctx->r7 = ADD32(ctx->r7, 0XF);
    // 0x802C8AD4: sw          $s6, 0x4($t2)
    MEM_W(0X4, ctx->r10) = ctx->r22;
    // 0x802C8AD8: sw          $s5, 0x0($t2)
    MEM_W(0X0, ctx->r10) = ctx->r21;
    // 0x802C8ADC: bne         $t0, $t9, L_802C89FC
    if (ctx->r8 != ctx->r25) {
        // 0x802C8AE0: addiu       $s0, $s0, 0x8
        ctx->r16 = ADD32(ctx->r16, 0X8);
            goto L_802C89FC;
    }
    // 0x802C8AE0: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C8AE4: b           L_802C8C8C
    // 0x802C8AE8: lw          $ra, 0x64($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X64);
        goto L_802C8C8C;
    // 0x802C8AE8: lw          $ra, 0x64($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X64);
L_802C8AEC:
    // 0x802C8AEC: lui         $t0, 0x806
    ctx->r8 = S32(0X806 << 16);
    // 0x802C8AF0: lui         $fp, 0x737
    ctx->r30 = S32(0X737 << 16);
    // 0x802C8AF4: lui         $s7, 0xFD68
    ctx->r23 = S32(0XFD68 << 16);
    // 0x802C8AF8: lui         $s6, 0x400
    ctx->r22 = S32(0X400 << 16);
    // 0x802C8AFC: lui         $s2, 0x8
    ctx->r18 = S32(0X8 << 16);
    // 0x802C8B00: lui         $t4, 0x708
    ctx->r12 = S32(0X708 << 16);
    // 0x802C8B04: lui         $t3, 0xF568
    ctx->r11 = S32(0XF568 << 16);
    // 0x802C8B08: ori         $t3, $t3, 0x3800
    ctx->r11 = ctx->r11 | 0X3800;
    // 0x802C8B0C: ori         $t4, $t4, 0x200
    ctx->r12 = ctx->r12 | 0X200;
    // 0x802C8B10: ori         $s2, $s2, 0x200
    ctx->r18 = ctx->r18 | 0X200;
    // 0x802C8B14: ori         $s6, $s6, 0x400
    ctx->r22 = ctx->r22 | 0X400;
    // 0x802C8B18: ori         $s7, $s7, 0xDF
    ctx->r23 = ctx->r23 | 0XDF;
    // 0x802C8B1C: ori         $fp, $fp, 0xC038
    ctx->r30 = ctx->r30 | 0XC038;
    // 0x802C8B20: addiu       $t0, $t0, 0x5078
    ctx->r8 = ADD32(ctx->r8, 0X5078);
    // 0x802C8B24: addiu       $a3, $zero, 0x58
    ctx->r7 = ADD32(0, 0X58);
    // 0x802C8B28: addiu       $a2, $zero, 0x49
    ctx->r6 = ADD32(0, 0X49);
    // 0x802C8B2C: lui         $s5, 0xB200
    ctx->r21 = S32(0XB200 << 16);
    // 0x802C8B30: lui         $s4, 0xB300
    ctx->r20 = S32(0XB300 << 16);
    // 0x802C8B34: lui         $s3, 0xF200
    ctx->r19 = S32(0XF200 << 16);
    // 0x802C8B38: lui         $s1, 0xE700
    ctx->r17 = S32(0XE700 << 16);
    // 0x802C8B3C: lui         $ra, 0xF400
    ctx->r31 = S32(0XF400 << 16);
    // 0x802C8B40: lui         $t5, 0xE600
    ctx->r13 = S32(0XE600 << 16);
L_802C8B44:
    // 0x802C8B44: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
    // 0x802C8B48: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C8B4C: or          $v1, $s0, $zero
    ctx->r3 = ctx->r16 | 0;
    // 0x802C8B50: sw          $s7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r23;
    // 0x802C8B54: sw          $t0, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r8;
    // 0x802C8B58: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C8B5C: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x802C8B60: sw          $t4, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r12;
    // 0x802C8B64: sw          $t3, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r11;
    // 0x802C8B68: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C8B6C: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    // 0x802C8B70: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C8B74: sw          $zero, 0x4($a0)
    MEM_W(0X4, ctx->r4) = 0;
    // 0x802C8B78: sw          $t5, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r13;
    // 0x802C8B7C: or          $t1, $s0, $zero
    ctx->r9 = ctx->r16 | 0;
    // 0x802C8B80: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C8B84: sw          $fp, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r30;
    // 0x802C8B88: sw          $ra, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r31;
    // 0x802C8B8C: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
    // 0x802C8B90: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C8B94: sw          $zero, 0x4($t1)
    MEM_W(0X4, ctx->r9) = 0;
    // 0x802C8B98: sw          $s1, 0x0($t1)
    MEM_W(0X0, ctx->r9) = ctx->r17;
    // 0x802C8B9C: or          $v1, $s0, $zero
    ctx->r3 = ctx->r16 | 0;
    // 0x802C8BA0: lui         $t6, 0x37
    ctx->r14 = S32(0X37 << 16);
    // 0x802C8BA4: sll         $t7, $a3, 2
    ctx->r15 = S32(ctx->r7 << 2);
    // 0x802C8BA8: lui         $at, 0xE452
    ctx->r1 = S32(0XE452 << 16);
    // 0x802C8BAC: ori         $t6, $t6, 0xC038
    ctx->r14 = ctx->r14 | 0XC038;
    // 0x802C8BB0: sw          $s2, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r18;
    // 0x802C8BB4: sw          $t3, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r11;
    // 0x802C8BB8: ori         $at, $at, 0x4000
    ctx->r1 = ctx->r1 | 0X4000;
    // 0x802C8BBC: andi        $t8, $t7, 0xFFF
    ctx->r24 = ctx->r15 & 0XFFF;
    // 0x802C8BC0: sw          $t6, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r14;
    // 0x802C8BC4: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C8BC8: or          $t9, $t8, $at
    ctx->r25 = ctx->r24 | ctx->r1;
    // 0x802C8BCC: lui         $at, 0x1A
    ctx->r1 = S32(0X1A << 16);
    // 0x802C8BD0: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x802C8BD4: sll         $t6, $a2, 2
    ctx->r14 = S32(ctx->r6 << 2);
    // 0x802C8BD8: sw          $s3, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r19;
    // 0x802C8BDC: andi        $t7, $t6, 0xFFF
    ctx->r15 = ctx->r14 & 0XFFF;
    // 0x802C8BE0: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C8BE4: ori         $at, $at, 0x4000
    ctx->r1 = ctx->r1 | 0X4000;
    // 0x802C8BE8: or          $t8, $t7, $at
    ctx->r24 = ctx->r15 | ctx->r1;
    // 0x802C8BEC: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    // 0x802C8BF0: sw          $t9, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r25;
    // 0x802C8BF4: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C8BF8: sw          $t8, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r24;
    // 0x802C8BFC: lui         $t9, 0x806
    ctx->r25 = S32(0X806 << 16);
    // 0x802C8C00: or          $t2, $s0, $zero
    ctx->r10 = ctx->r16 | 0;
    // 0x802C8C04: addiu       $t9, $t9, 0x6AB8
    ctx->r25 = ADD32(ctx->r25, 0X6AB8);
    // 0x802C8C08: addiu       $t0, $t0, 0xD20
    ctx->r8 = ADD32(ctx->r8, 0XD20);
    // 0x802C8C0C: sw          $zero, 0x4($a1)
    MEM_W(0X4, ctx->r5) = 0;
    // 0x802C8C10: sw          $s4, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r20;
    // 0x802C8C14: addiu       $a2, $a2, 0xF
    ctx->r6 = ADD32(ctx->r6, 0XF);
    // 0x802C8C18: addiu       $a3, $a3, 0xF
    ctx->r7 = ADD32(ctx->r7, 0XF);
    // 0x802C8C1C: sw          $s6, 0x4($t2)
    MEM_W(0X4, ctx->r10) = ctx->r22;
    // 0x802C8C20: sw          $s5, 0x0($t2)
    MEM_W(0X0, ctx->r10) = ctx->r21;
    // 0x802C8C24: bne         $t0, $t9, L_802C8B44
    if (ctx->r8 != ctx->r25) {
        // 0x802C8C28: addiu       $s0, $s0, 0x8
        ctx->r16 = ADD32(ctx->r16, 0X8);
            goto L_802C8B44;
    }
    // 0x802C8C28: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C8C2C: b           L_802C8C8C
    // 0x802C8C30: lw          $ra, 0x64($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X64);
        goto L_802C8C8C;
    // 0x802C8C30: lw          $ra, 0x64($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X64);
L_802C8C34:
    // 0x802C8C34: addiu       $t6, $zero, 0x50
    ctx->r14 = ADD32(0, 0X50);
    // 0x802C8C38: addiu       $t7, $zero, 0x2
    ctx->r15 = ADD32(0, 0X2);
    // 0x802C8C3C: sw          $t7, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r15;
    // 0x802C8C40: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x802C8C44: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x802C8C48: addiu       $a1, $zero, 0x3
    ctx->r5 = ADD32(0, 0X3);
    // 0x802C8C4C: addiu       $a2, $zero, 0xF
    ctx->r6 = ADD32(0, 0XF);
    // 0x802C8C50: jal         0x801E3EE0
    // 0x802C8C54: addiu       $a3, $zero, 0xAB
    ctx->r7 = ADD32(0, 0XAB);
    func_801E3EE0(rdram, ctx);
        goto after_4;
    // 0x802C8C54: addiu       $a3, $zero, 0xAB
    ctx->r7 = ADD32(0, 0XAB);
    after_4:
    // 0x802C8C58: b           L_802C8C88
    // 0x802C8C5C: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
        goto L_802C8C88;
    // 0x802C8C5C: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
L_802C8C60:
    // 0x802C8C60: addiu       $t8, $zero, 0x50
    ctx->r24 = ADD32(0, 0X50);
    // 0x802C8C64: addiu       $t9, $zero, 0x2
    ctx->r25 = ADD32(0, 0X2);
    // 0x802C8C68: sw          $t9, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r25;
    // 0x802C8C6C: sw          $t8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r24;
    // 0x802C8C70: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x802C8C74: addiu       $a1, $zero, 0x3
    ctx->r5 = ADD32(0, 0X3);
    // 0x802C8C78: addiu       $a2, $zero, 0x10
    ctx->r6 = ADD32(0, 0X10);
    // 0x802C8C7C: jal         0x801E3EE0
    // 0x802C8C80: addiu       $a3, $zero, 0xAC
    ctx->r7 = ADD32(0, 0XAC);
    func_801E3EE0(rdram, ctx);
        goto after_5;
    // 0x802C8C80: addiu       $a3, $zero, 0xAC
    ctx->r7 = ADD32(0, 0XAC);
    after_5:
    // 0x802C8C84: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
L_802C8C88:
    // 0x802C8C88: lw          $ra, 0x64($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X64);
L_802C8C8C:
    // 0x802C8C8C: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
    // 0x802C8C90: lw          $s0, 0x40($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X40);
    // 0x802C8C94: lw          $s1, 0x44($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X44);
    // 0x802C8C98: lw          $s2, 0x48($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X48);
    // 0x802C8C9C: lw          $s3, 0x4C($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X4C);
    // 0x802C8CA0: lw          $s4, 0x50($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X50);
    // 0x802C8CA4: lw          $s5, 0x54($sp)
    ctx->r21 = MEM_W(ctx->r29, 0X54);
    // 0x802C8CA8: lw          $s6, 0x58($sp)
    ctx->r22 = MEM_W(ctx->r29, 0X58);
    // 0x802C8CAC: lw          $s7, 0x5C($sp)
    ctx->r23 = MEM_W(ctx->r29, 0X5C);
    // 0x802C8CB0: lw          $fp, 0x60($sp)
    ctx->r30 = MEM_W(ctx->r29, 0X60);
    // 0x802C8CB4: jr          $ra
    // 0x802C8CB8: addiu       $sp, $sp, 0x68
    ctx->r29 = ADD32(ctx->r29, 0X68);
    return;
    // 0x802C8CB8: addiu       $sp, $sp, 0x68
    ctx->r29 = ADD32(ctx->r29, 0X68);
;}
RECOMP_FUNC void func_i13_802C8CBC(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C8CBC: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x802C8CC0: addiu       $v0, $v0, -0x54DC
    ctx->r2 = ADD32(ctx->r2, -0X54DC);
    // 0x802C8CC4: lw          $t6, 0x0($v0)
    ctx->r14 = MEM_W(ctx->r2, 0X0);
    // 0x802C8CC8: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C8CCC: addiu       $t7, $zero, 0x41
    ctx->r15 = ADD32(0, 0X41);
    // 0x802C8CD0: sw          $t6, -0x19CC($at)
    MEM_W(-0X19CC, ctx->r1) = ctx->r14;
    // 0x802C8CD4: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C8CD8: sw          $zero, -0x19D0($at)
    MEM_W(-0X19D0, ctx->r1) = 0;
    // 0x802C8CDC: sw          $t7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r15;
    // 0x802C8CE0: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C8CE4: addiu       $t8, $zero, 0xB
    ctx->r24 = ADD32(0, 0XB);
    // 0x802C8CE8: sw          $t8, -0x19C8($at)
    MEM_W(-0X19C8, ctx->r1) = ctx->r24;
    // 0x802C8CEC: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C8CF0: addiu       $t9, $zero, 0x1
    ctx->r25 = ADD32(0, 0X1);
    // 0x802C8CF4: sw          $t9, -0x19C4($at)
    MEM_W(-0X19C4, ctx->r1) = ctx->r25;
    // 0x802C8CF8: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C8CFC: sw          $zero, -0x19C0($at)
    MEM_W(-0X19C0, ctx->r1) = 0;
    // 0x802C8D00: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C8D04: sw          $zero, -0x19BC($at)
    MEM_W(-0X19BC, ctx->r1) = 0;
    // 0x802C8D08: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x802C8D0C: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x802C8D10: sw          $zero, -0x54E4($at)
    MEM_W(-0X54E4, ctx->r1) = 0;
    // 0x802C8D14: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x802C8D18: lui         $at, 0x800D
    ctx->r1 = S32(0X800D << 16);
    // 0x802C8D1C: addiu       $t0, $zero, 0x2
    ctx->r8 = ADD32(0, 0X2);
    // 0x802C8D20: sw          $t0, 0x461C($at)
    MEM_W(0X461C, ctx->r1) = ctx->r8;
    // 0x802C8D24: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    // 0x802C8D28: addiu       $a1, $zero, 0x4
    ctx->r5 = ADD32(0, 0X4);
    // 0x802C8D2C: jal         0x801E6FB0
    // 0x802C8D30: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    FadeTransition_SetProps(rdram, ctx);
        goto after_0;
    // 0x802C8D30: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    after_0:
    // 0x802C8D34: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x802C8D38: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x802C8D3C: jr          $ra
    // 0x802C8D40: nop

    return;
    // 0x802C8D40: nop

    // 0x802C8D44: nop

    // 0x802C8D48: nop

    // 0x802C8D4C: nop

;}
RECOMP_FUNC void func_i14_802C5800(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C5800: lui         $t6, 0x801D
    ctx->r14 = S32(0X801D << 16);
    // 0x802C5804: lw          $t6, -0x19C4($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X19C4);
    // 0x802C5808: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x802C580C: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x802C5810: beq         $t6, $zero, L_802C5830
    if (ctx->r14 == 0) {
        // 0x802C5814: lui         $t7, 0x800E
        ctx->r15 = S32(0X800E << 16);
            goto L_802C5830;
    }
    // 0x802C5814: lui         $t7, 0x800E
    ctx->r15 = S32(0X800E << 16);
    // 0x802C5818: lw          $t7, -0x54DC($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X54DC);
    // 0x802C581C: addiu       $at, $zero, 0x50
    ctx->r1 = ADD32(0, 0X50);
    // 0x802C5820: bnel        $t7, $at, L_802C5834
    if (ctx->r15 != ctx->r1) {
        // 0x802C5824: lw          $ra, 0x14($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X14);
            goto L_802C5834;
    }
    goto skip_0;
    // 0x802C5824: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    skip_0:
    // 0x802C5828: jal         0x802C5840
    // 0x802C582C: nop

    func_i14_802C5840(rdram, ctx);
        goto after_0;
    // 0x802C582C: nop

    after_0:
L_802C5830:
    // 0x802C5830: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C5834:
    // 0x802C5834: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x802C5838: jr          $ra
    // 0x802C583C: nop

    return;
    // 0x802C583C: nop

;}
RECOMP_FUNC void func_i14_802C5840(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C5840: lui         $a2, 0x802C
    ctx->r6 = S32(0X802C << 16);
    // 0x802C5844: addiu       $a2, $a2, 0x61EC
    ctx->r6 = ADD32(ctx->r6, 0X61EC);
    // 0x802C5848: addiu       $a1, $zero, 0x4
    ctx->r5 = ADD32(0, 0X4);
    // 0x802C584C: sw          $a1, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r5;
    // 0x802C5850: lui         $a0, 0x801D
    ctx->r4 = S32(0X801D << 16);
    // 0x802C5854: lw          $a0, -0x19F8($a0)
    ctx->r4 = MEM_W(ctx->r4, -0X19F8);
    // 0x802C5858: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x802C585C: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x802C5860: bne         $a1, $a0, L_802C5884
    if (ctx->r5 != ctx->r4) {
        // 0x802C5864: or          $v1, $zero, $zero
        ctx->r3 = 0 | 0;
            goto L_802C5884;
    }
    // 0x802C5864: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
    // 0x802C5868: lui         $t6, 0x801D
    ctx->r14 = S32(0X801D << 16);
    // 0x802C586C: lw          $t6, -0x19CC($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X19CC);
    // 0x802C5870: addiu       $at, $zero, 0x43
    ctx->r1 = ADD32(0, 0X43);
    // 0x802C5874: bne         $t6, $at, L_802C58AC
    if (ctx->r14 != ctx->r1) {
        // 0x802C5878: nop
    
            goto L_802C58AC;
    }
    // 0x802C5878: nop

    // 0x802C587C: b           L_802C58AC
    // 0x802C5880: addiu       $v1, $zero, 0x1
    ctx->r3 = ADD32(0, 0X1);
        goto L_802C58AC;
    // 0x802C5880: addiu       $v1, $zero, 0x1
    ctx->r3 = ADD32(0, 0X1);
L_802C5884:
    // 0x802C5884: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x802C5888: lw          $v0, -0x19CC($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X19CC);
    // 0x802C588C: addiu       $at, $zero, 0x64
    ctx->r1 = ADD32(0, 0X64);
    // 0x802C5890: beq         $v0, $at, L_802C58AC
    if (ctx->r2 == ctx->r1) {
        // 0x802C5894: addiu       $at, $zero, 0x32
        ctx->r1 = ADD32(0, 0X32);
            goto L_802C58AC;
    }
    // 0x802C5894: addiu       $at, $zero, 0x32
    ctx->r1 = ADD32(0, 0X32);
    // 0x802C5898: beq         $v0, $at, L_802C58AC
    if (ctx->r2 == ctx->r1) {
        // 0x802C589C: addiu       $at, $zero, 0x39
        ctx->r1 = ADD32(0, 0X39);
            goto L_802C58AC;
    }
    // 0x802C589C: addiu       $at, $zero, 0x39
    ctx->r1 = ADD32(0, 0X39);
    // 0x802C58A0: beq         $v0, $at, L_802C58AC
    if (ctx->r2 == ctx->r1) {
        // 0x802C58A4: nop
    
            goto L_802C58AC;
    }
    // 0x802C58A4: nop

    // 0x802C58A8: addiu       $v1, $zero, 0x1
    ctx->r3 = ADD32(0, 0X1);
L_802C58AC:
    // 0x802C58AC: bne         $a1, $a0, L_802C58B8
    if (ctx->r5 != ctx->r4) {
        // 0x802C58B0: addiu       $t7, $zero, 0x2
        ctx->r15 = ADD32(0, 0X2);
            goto L_802C58B8;
    }
    // 0x802C58B0: addiu       $t7, $zero, 0x2
    ctx->r15 = ADD32(0, 0X2);
    // 0x802C58B4: sw          $t7, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r15;
L_802C58B8:
    // 0x802C58B8: beq         $v1, $zero, L_802C58E8
    if (ctx->r3 == 0) {
        // 0x802C58BC: lui         $v0, 0x802C
        ctx->r2 = S32(0X802C << 16);
            goto L_802C58E8;
    }
    // 0x802C58BC: lui         $v0, 0x802C
    ctx->r2 = S32(0X802C << 16);
    // 0x802C58C0: addiu       $t8, $zero, 0x1
    ctx->r24 = ADD32(0, 0X1);
    // 0x802C58C4: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C58C8: lui         $v0, 0x802C
    ctx->r2 = S32(0X802C << 16);
    // 0x802C58CC: sw          $t8, 0x61E0($at)
    MEM_W(0X61E0, ctx->r1) = ctx->r24;
    // 0x802C58D0: addiu       $v0, $v0, 0x61E8
    ctx->r2 = ADD32(ctx->r2, 0X61E8);
    // 0x802C58D4: addiu       $t9, $zero, 0x80
    ctx->r25 = ADD32(0, 0X80);
    // 0x802C58D8: sw          $t9, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r25;
    // 0x802C58DC: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C58E0: b           L_802C5914
    // 0x802C58E4: sw          $t9, 0x61E4($at)
    MEM_W(0X61E4, ctx->r1) = ctx->r25;
        goto L_802C5914;
    // 0x802C58E4: sw          $t9, 0x61E4($at)
    MEM_W(0X61E4, ctx->r1) = ctx->r25;
L_802C58E8:
    // 0x802C58E8: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C58EC: sw          $zero, 0x61E0($at)
    MEM_W(0X61E0, ctx->r1) = 0;
    // 0x802C58F0: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C58F4: addiu       $t1, $zero, 0x1A8
    ctx->r9 = ADD32(0, 0X1A8);
    // 0x802C58F8: addiu       $v0, $v0, 0x61E8
    ctx->r2 = ADD32(ctx->r2, 0X61E8);
    // 0x802C58FC: sw          $t1, 0x61E4($at)
    MEM_W(0X61E4, ctx->r1) = ctx->r9;
    // 0x802C5900: addiu       $t2, $zero, -0xA9
    ctx->r10 = ADD32(0, -0XA9);
    // 0x802C5904: sw          $t2, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r10;
    // 0x802C5908: addiu       $a0, $zero, 0x31
    ctx->r4 = ADD32(0, 0X31);
    // 0x802C590C: jal         0x800C37F4
    // 0x802C5910: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_0;
    // 0x802C5910: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_0:
L_802C5914:
    // 0x802C5914: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x802C5918: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x802C591C: jr          $ra
    // 0x802C5920: nop

    return;
    // 0x802C5920: nop

;}
RECOMP_FUNC void func_i14_802C5924(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C5924: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x802C5928: addiu       $v0, $v0, -0x19C4
    ctx->r2 = ADD32(ctx->r2, -0X19C4);
    // 0x802C592C: lw          $t6, 0x0($v0)
    ctx->r14 = MEM_W(ctx->r2, 0X0);
    // 0x802C5930: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x802C5934: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x802C5938: beq         $t6, $zero, L_802C59C4
    if (ctx->r14 == 0) {
        // 0x802C593C: sw          $a0, 0x18($sp)
        MEM_W(0X18, ctx->r29) = ctx->r4;
            goto L_802C59C4;
    }
    // 0x802C593C: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    // 0x802C5940: sw          $zero, 0x0($v0)
    MEM_W(0X0, ctx->r2) = 0;
    // 0x802C5944: lui         $t7, 0x800E
    ctx->r15 = S32(0X800E << 16);
    // 0x802C5948: lw          $t7, -0x54DC($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X54DC);
    // 0x802C594C: addiu       $at, $zero, 0x50
    ctx->r1 = ADD32(0, 0X50);
    // 0x802C5950: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x802C5954: bne         $t7, $at, L_802C59C4
    if (ctx->r15 != ctx->r1) {
        // 0x802C5958: nop
    
            goto L_802C59C4;
    }
    // 0x802C5958: nop

    // 0x802C595C: lw          $v1, -0x19CC($v1)
    ctx->r3 = MEM_W(ctx->r3, -0X19CC);
    // 0x802C5960: addiu       $at, $zero, 0x32
    ctx->r1 = ADD32(0, 0X32);
    // 0x802C5964: beq         $v1, $at, L_802C59C4
    if (ctx->r3 == ctx->r1) {
        // 0x802C5968: addiu       $at, $zero, 0x39
        ctx->r1 = ADD32(0, 0X39);
            goto L_802C59C4;
    }
    // 0x802C5968: addiu       $at, $zero, 0x39
    ctx->r1 = ADD32(0, 0X39);
    // 0x802C596C: beq         $v1, $at, L_802C59C4
    if (ctx->r3 == ctx->r1) {
        // 0x802C5970: addiu       $at, $zero, 0x64
        ctx->r1 = ADD32(0, 0X64);
            goto L_802C59C4;
    }
    // 0x802C5970: addiu       $at, $zero, 0x64
    ctx->r1 = ADD32(0, 0X64);
    // 0x802C5974: beq         $v1, $at, L_802C59C4
    if (ctx->r3 == ctx->r1) {
        // 0x802C5978: lui         $t8, 0x801D
        ctx->r24 = S32(0X801D << 16);
            goto L_802C59C4;
    }
    // 0x802C5978: lui         $t8, 0x801D
    ctx->r24 = S32(0X801D << 16);
    // 0x802C597C: lw          $t8, -0x19F8($t8)
    ctx->r24 = MEM_W(ctx->r24, -0X19F8);
    // 0x802C5980: addiu       $at, $zero, 0x4
    ctx->r1 = ADD32(0, 0X4);
    // 0x802C5984: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    // 0x802C5988: bne         $t8, $at, L_802C59A0
    if (ctx->r24 != ctx->r1) {
        // 0x802C598C: addiu       $at, $zero, 0x43
        ctx->r1 = ADD32(0, 0X43);
            goto L_802C59A0;
    }
    // 0x802C598C: addiu       $at, $zero, 0x43
    ctx->r1 = ADD32(0, 0X43);
    // 0x802C5990: bne         $v1, $at, L_802C59A4
    if (ctx->r3 != ctx->r1) {
        // 0x802C5994: nop
    
            goto L_802C59A4;
    }
    // 0x802C5994: nop

    // 0x802C5998: b           L_802C59A4
    // 0x802C599C: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
        goto L_802C59A4;
    // 0x802C599C: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
L_802C59A0:
    // 0x802C59A0: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
L_802C59A4:
    // 0x802C59A4: beq         $v0, $zero, L_802C59C4
    if (ctx->r2 == 0) {
        // 0x802C59A8: nop
    
            goto L_802C59C4;
    }
    // 0x802C59A8: nop

    // 0x802C59AC: jal         0x800C6AD0
    // 0x802C59B0: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    osViBlack_recomp(rdram, ctx);
        goto after_0;
    // 0x802C59B0: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    after_0:
    // 0x802C59B4: jal         0x80093C44
    // 0x802C59B8: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
    func_80093C44(rdram, ctx);
        goto after_1;
    // 0x802C59B8: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
    after_1:
    // 0x802C59BC: b           L_802C5B64
    // 0x802C59C0: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_802C5B64;
    // 0x802C59C0: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C59C4:
    // 0x802C59C4: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x802C59C8: sw          $zero, -0x54D4($at)
    MEM_W(-0X54D4, ctx->r1) = 0;
    // 0x802C59CC: jal         0x8008FB74
    // 0x802C59D0: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
    func_8008FB74(rdram, ctx);
        goto after_2;
    // 0x802C59D0: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
    after_2:
    // 0x802C59D4: lui         $a1, 0x800E
    ctx->r5 = S32(0X800E << 16);
    // 0x802C59D8: lw          $a1, -0x7E90($a1)
    ctx->r5 = MEM_W(ctx->r5, -0X7E90);
    // 0x802C59DC: jal         0x800949B8
    // 0x802C59E0: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    func_800949B8(rdram, ctx);
        goto after_3;
    // 0x802C59E0: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    after_3:
    // 0x802C59E4: jal         0x80090F58
    // 0x802C59E8: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    Draw_WaterEffects(rdram, ctx);
        goto after_4;
    // 0x802C59E8: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    after_4:
    // 0x802C59EC: jal         0x802C5B70
    // 0x802C59F0: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    func_i14_802C5B70(rdram, ctx);
        goto after_5;
    // 0x802C59F0: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    after_5:
    // 0x802C59F4: lui         $t9, 0x800E
    ctx->r25 = S32(0X800E << 16);
    // 0x802C59F8: lw          $t9, -0x54DC($t9)
    ctx->r25 = MEM_W(ctx->r25, -0X54DC);
    // 0x802C59FC: addiu       $at, $zero, 0x50
    ctx->r1 = ADD32(0, 0X50);
    // 0x802C5A00: sw          $v0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r2;
    // 0x802C5A04: bne         $t9, $at, L_802C5A1C
    if (ctx->r25 != ctx->r1) {
        // 0x802C5A08: lui         $t0, 0x8023
        ctx->r8 = S32(0X8023 << 16);
            goto L_802C5A1C;
    }
    // 0x802C5A08: lui         $t0, 0x8023
    ctx->r8 = S32(0X8023 << 16);
    // 0x802C5A0C: jal         0x802C5F60
    // 0x802C5A10: nop

    func_i14_802C5F60(rdram, ctx);
        goto after_6;
    // 0x802C5A10: nop

    after_6:
    // 0x802C5A14: b           L_802C5B60
    // 0x802C5A18: lw          $v0, 0x18($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X18);
        goto L_802C5B60;
    // 0x802C5A18: lw          $v0, 0x18($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X18);
L_802C5A1C:
    // 0x802C5A1C: lh          $t0, -0x75EA($t0)
    ctx->r8 = MEM_H(ctx->r8, -0X75EA);
    // 0x802C5A20: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x802C5A24: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x802C5A28: bnel        $t0, $at, L_802C5B60
    if (ctx->r8 != ctx->r1) {
        // 0x802C5A2C: lw          $v0, 0x18($sp)
        ctx->r2 = MEM_W(ctx->r29, 0X18);
            goto L_802C5B60;
    }
    goto skip_0;
    // 0x802C5A2C: lw          $v0, 0x18($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X18);
    skip_0:
    // 0x802C5A30: lw          $v0, -0x19F8($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X19F8);
    // 0x802C5A34: lui         $t1, 0x801C
    ctx->r9 = S32(0X801C << 16);
    // 0x802C5A38: addiu       $at, $zero, 0xB
    ctx->r1 = ADD32(0, 0XB);
    // 0x802C5A3C: bne         $v0, $zero, L_802C5A98
    if (ctx->r2 != 0) {
        // 0x802C5A40: nop
    
            goto L_802C5A98;
    }
    // 0x802C5A40: nop

    // 0x802C5A44: lw          $t1, 0x2650($t1)
    ctx->r9 = MEM_W(ctx->r9, 0X2650);
    // 0x802C5A48: lui         $t2, 0x801C
    ctx->r10 = S32(0X801C << 16);
    // 0x802C5A4C: lui         $t3, 0x800E
    ctx->r11 = S32(0X800E << 16);
    // 0x802C5A50: bne         $t1, $zero, L_802C5A64
    if (ctx->r9 != 0) {
        // 0x802C5A54: nop
    
            goto L_802C5A64;
    }
    // 0x802C5A54: nop

    // 0x802C5A58: lw          $t2, 0x2654($t2)
    ctx->r10 = MEM_W(ctx->r10, 0X2654);
    // 0x802C5A5C: beq         $t2, $zero, L_802C5AB8
    if (ctx->r10 == 0) {
        // 0x802C5A60: nop
    
            goto L_802C5AB8;
    }
    // 0x802C5A60: nop

L_802C5A64:
    // 0x802C5A64: lh          $t3, -0x5498($t3)
    ctx->r11 = MEM_H(ctx->r11, -0X5498);
    // 0x802C5A68: lui         $a0, 0x800E
    ctx->r4 = S32(0X800E << 16);
    // 0x802C5A6C: beq         $t3, $zero, L_802C5A88
    if (ctx->r11 == 0) {
        // 0x802C5A70: nop
    
            goto L_802C5A88;
    }
    // 0x802C5A70: nop

    // 0x802C5A74: lui         $a0, 0x800E
    ctx->r4 = S32(0X800E << 16);
    // 0x802C5A78: jal         0x8007C204
    // 0x802C5A7C: lw          $a0, -0x7E90($a0)
    ctx->r4 = MEM_W(ctx->r4, -0X7E90);
    func_8007C204(rdram, ctx);
        goto after_7;
    // 0x802C5A7C: lw          $a0, -0x7E90($a0)
    ctx->r4 = MEM_W(ctx->r4, -0X7E90);
    after_7:
    // 0x802C5A80: b           L_802C5AB8
    // 0x802C5A84: nop

        goto L_802C5AB8;
    // 0x802C5A84: nop

L_802C5A88:
    // 0x802C5A88: jal         0x8007BEA4
    // 0x802C5A8C: lw          $a0, -0x7E90($a0)
    ctx->r4 = MEM_W(ctx->r4, -0X7E90);
    func_8007BEA4(rdram, ctx);
        goto after_8;
    // 0x802C5A8C: lw          $a0, -0x7E90($a0)
    ctx->r4 = MEM_W(ctx->r4, -0X7E90);
    after_8:
    // 0x802C5A90: b           L_802C5AB8
    // 0x802C5A94: nop

        goto L_802C5AB8;
    // 0x802C5A94: nop

L_802C5A98:
    // 0x802C5A98: bne         $v0, $at, L_802C5AB8
    if (ctx->r2 != ctx->r1) {
        // 0x802C5A9C: lui         $t4, 0x801C
        ctx->r12 = S32(0X801C << 16);
            goto L_802C5AB8;
    }
    // 0x802C5A9C: lui         $t4, 0x801C
    ctx->r12 = S32(0X801C << 16);
    // 0x802C5AA0: lw          $t4, 0x2928($t4)
    ctx->r12 = MEM_W(ctx->r12, 0X2928);
    // 0x802C5AA4: lui         $a0, 0x800E
    ctx->r4 = S32(0X800E << 16);
    // 0x802C5AA8: beq         $t4, $zero, L_802C5AB8
    if (ctx->r12 == 0) {
        // 0x802C5AAC: nop
    
            goto L_802C5AB8;
    }
    // 0x802C5AAC: nop

    // 0x802C5AB0: jal         0x8007C0B8
    // 0x802C5AB4: lw          $a0, -0x7E90($a0)
    ctx->r4 = MEM_W(ctx->r4, -0X7E90);
    func_8007C0B8(rdram, ctx);
        goto after_9;
    // 0x802C5AB4: lw          $a0, -0x7E90($a0)
    ctx->r4 = MEM_W(ctx->r4, -0X7E90);
    after_9:
L_802C5AB8:
    // 0x802C5AB8: lui         $t5, 0x801D
    ctx->r13 = S32(0X801D << 16);
    // 0x802C5ABC: lw          $t5, -0x19D0($t5)
    ctx->r13 = MEM_W(ctx->r13, -0X19D0);
    // 0x802C5AC0: addiu       $t6, $t5, -0x2
    ctx->r14 = ADD32(ctx->r13, -0X2);
    // 0x802C5AC4: sltiu       $at, $t6, 0x27
    ctx->r1 = ctx->r14 < 0X27 ? 1 : 0;
    // 0x802C5AC8: beq         $at, $zero, L_802C5B5C
    if (ctx->r1 == 0) {
        // 0x802C5ACC: sll         $t6, $t6, 2
        ctx->r14 = S32(ctx->r14 << 2);
            goto L_802C5B5C;
    }
    // 0x802C5ACC: sll         $t6, $t6, 2
    ctx->r14 = S32(ctx->r14 << 2);
    // 0x802C5AD0: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C5AD4: addu        $at, $at, $t6
    gpr jr_addend_802C5ADC = ctx->r14;
    ctx->r1 = ADD32(ctx->r1, ctx->r14);
    // 0x802C5AD8: lw          $t6, 0x6140($at)
    ctx->r14 = ADD32(ctx->r1, 0X6140);
    // 0x802C5ADC: jr          $t6
    // 0x802C5AE0: nop

    switch (jr_addend_802C5ADC >> 2) {
        case 0: goto L_802C5B54; break;
        case 1: goto L_802C5B5C; break;
        case 2: goto L_802C5B5C; break;
        case 3: goto L_802C5B5C; break;
        case 4: goto L_802C5B5C; break;
        case 5: goto L_802C5B5C; break;
        case 6: goto L_802C5B5C; break;
        case 7: goto L_802C5B5C; break;
        case 8: goto L_802C5B34; break;
        case 9: goto L_802C5B5C; break;
        case 10: goto L_802C5B5C; break;
        case 11: goto L_802C5B5C; break;
        case 12: goto L_802C5B5C; break;
        case 13: goto L_802C5B5C; break;
        case 14: goto L_802C5B5C; break;
        case 15: goto L_802C5B5C; break;
        case 16: goto L_802C5B5C; break;
        case 17: goto L_802C5B5C; break;
        case 18: goto L_802C5B44; break;
        case 19: goto L_802C5B5C; break;
        case 20: goto L_802C5B5C; break;
        case 21: goto L_802C5B5C; break;
        case 22: goto L_802C5B5C; break;
        case 23: goto L_802C5B5C; break;
        case 24: goto L_802C5B5C; break;
        case 25: goto L_802C5B5C; break;
        case 26: goto L_802C5B5C; break;
        case 27: goto L_802C5B5C; break;
        case 28: goto L_802C5AE4; break;
        case 29: goto L_802C5B5C; break;
        case 30: goto L_802C5B5C; break;
        case 31: goto L_802C5B5C; break;
        case 32: goto L_802C5B5C; break;
        case 33: goto L_802C5B5C; break;
        case 34: goto L_802C5B5C; break;
        case 35: goto L_802C5B5C; break;
        case 36: goto L_802C5B5C; break;
        case 37: goto L_802C5B5C; break;
        case 38: goto L_802C5B24; break;
        default: switch_error(__func__, 0x802C5ADC, 0x802C6140);
    }
    // 0x802C5AE0: nop

L_802C5AE4:
    // 0x802C5AE4: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x802C5AE8: addiu       $t7, $zero, 0x1
    ctx->r15 = ADD32(0, 0X1);
    // 0x802C5AEC: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C5AF0: addiu       $v0, $v0, -0x4CCC
    ctx->r2 = ADD32(ctx->r2, -0X4CCC);
    // 0x802C5AF4: sw          $t7, -0x1908($at)
    MEM_W(-0X1908, ctx->r1) = ctx->r15;
    // 0x802C5AF8: sw          $zero, 0x0($v0)
    MEM_W(0X0, ctx->r2) = 0;
    // 0x802C5AFC: lui         $t8, 0x801D
    ctx->r24 = S32(0X801D << 16);
    // 0x802C5B00: lw          $t8, -0x4CC8($t8)
    ctx->r24 = MEM_W(ctx->r24, -0X4CC8);
    // 0x802C5B04: addiu       $t9, $zero, 0x1
    ctx->r25 = ADD32(0, 0X1);
    // 0x802C5B08: bne         $t8, $zero, L_802C5B14
    if (ctx->r24 != 0) {
        // 0x802C5B0C: nop
    
            goto L_802C5B14;
    }
    // 0x802C5B0C: nop

    // 0x802C5B10: sw          $t9, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r25;
L_802C5B14:
    // 0x802C5B14: jal         0x801EB91C
    // 0x802C5B18: nop

    func_801EB91C(rdram, ctx);
        goto after_10;
    // 0x802C5B18: nop

    after_10:
    // 0x802C5B1C: b           L_802C5B60
    // 0x802C5B20: lw          $v0, 0x18($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X18);
        goto L_802C5B60;
    // 0x802C5B20: lw          $v0, 0x18($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X18);
L_802C5B24:
    // 0x802C5B24: jal         0x8009345C
    // 0x802C5B28: nop

    func_8009345C(rdram, ctx);
        goto after_11;
    // 0x802C5B28: nop

    after_11:
    // 0x802C5B2C: b           L_802C5B60
    // 0x802C5B30: lw          $v0, 0x18($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X18);
        goto L_802C5B60;
    // 0x802C5B30: lw          $v0, 0x18($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X18);
L_802C5B34:
    // 0x802C5B34: jal         0x801EBD28
    // 0x802C5B38: nop

    func_801EBD28(rdram, ctx);
        goto after_12;
    // 0x802C5B38: nop

    after_12:
    // 0x802C5B3C: b           L_802C5B60
    // 0x802C5B40: lw          $v0, 0x18($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X18);
        goto L_802C5B60;
    // 0x802C5B40: lw          $v0, 0x18($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X18);
L_802C5B44:
    // 0x802C5B44: jal         0x801EBFE4
    // 0x802C5B48: nop

    func_801EBFE4(rdram, ctx);
        goto after_13;
    // 0x802C5B48: nop

    after_13:
    // 0x802C5B4C: b           L_802C5B60
    // 0x802C5B50: lw          $v0, 0x18($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X18);
        goto L_802C5B60;
    // 0x802C5B50: lw          $v0, 0x18($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X18);
L_802C5B54:
    // 0x802C5B54: jal         0x801EB180
    // 0x802C5B58: nop

    func_801EB180(rdram, ctx);
        goto after_14;
    // 0x802C5B58: nop

    after_14:
L_802C5B5C:
    // 0x802C5B5C: lw          $v0, 0x18($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X18);
L_802C5B60:
    // 0x802C5B60: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C5B64:
    // 0x802C5B64: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x802C5B68: jr          $ra
    // 0x802C5B6C: nop

    return;
    // 0x802C5B6C: nop

;}
RECOMP_FUNC void func_i14_802C5B70(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C5B70: addiu       $sp, $sp, -0x60
    ctx->r29 = ADD32(ctx->r29, -0X60);
    // 0x802C5B74: sw          $s5, 0x50($sp)
    MEM_W(0X50, ctx->r29) = ctx->r21;
    // 0x802C5B78: sw          $ra, 0x54($sp)
    MEM_W(0X54, ctx->r29) = ctx->r31;
    // 0x802C5B7C: sw          $s4, 0x4C($sp)
    MEM_W(0X4C, ctx->r29) = ctx->r20;
    // 0x802C5B80: sw          $s3, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r19;
    // 0x802C5B84: sw          $s2, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r18;
    // 0x802C5B88: sw          $s1, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r17;
    // 0x802C5B8C: sw          $s0, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r16;
    // 0x802C5B90: lui         $t7, 0x107
    ctx->r15 = S32(0X107 << 16);
    // 0x802C5B94: lui         $s5, 0x802C
    ctx->r21 = S32(0X802C << 16);
    // 0x802C5B98: addiu       $t7, $t7, -0x9D8
    ctx->r15 = ADD32(ctx->r15, -0X9D8);
    // 0x802C5B9C: lui         $t6, 0x600
    ctx->r14 = S32(0X600 << 16);
    // 0x802C5BA0: addiu       $s5, $s5, 0x61EC
    ctx->r21 = ADD32(ctx->r21, 0X61EC);
    // 0x802C5BA4: sw          $t6, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r14;
    // 0x802C5BA8: sw          $t7, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r15;
    // 0x802C5BAC: lw          $t8, 0x0($s5)
    ctx->r24 = MEM_W(ctx->r21, 0X0);
    // 0x802C5BB0: addiu       $s2, $a0, 0x8
    ctx->r18 = ADD32(ctx->r4, 0X8);
    // 0x802C5BB4: or          $s0, $zero, $zero
    ctx->r16 = 0 | 0;
    // 0x802C5BB8: blez        $t8, L_802C5C24
    if (SIGNED(ctx->r24) <= 0) {
        // 0x802C5BBC: addiu       $s1, $zero, 0x61
        ctx->r17 = ADD32(0, 0X61);
            goto L_802C5C24;
    }
    // 0x802C5BBC: addiu       $s1, $zero, 0x61
    ctx->r17 = ADD32(0, 0X61);
    // 0x802C5BC0: lui         $s4, 0x802C
    ctx->r20 = S32(0X802C << 16);
    // 0x802C5BC4: lui         $s3, 0x802C
    ctx->r19 = S32(0X802C << 16);
    // 0x802C5BC8: addiu       $s3, $s3, 0x61E4
    ctx->r19 = ADD32(ctx->r19, 0X61E4);
    // 0x802C5BCC: addiu       $s4, $s4, 0x61E8
    ctx->r20 = ADD32(ctx->r20, 0X61E8);
L_802C5BD0:
    // 0x802C5BD0: andi        $t9, $s0, 0x1
    ctx->r25 = ctx->r16 & 0X1;
    // 0x802C5BD4: beq         $t9, $zero, L_802C5BE4
    if (ctx->r25 == 0) {
        // 0x802C5BD8: or          $a0, $s2, $zero
        ctx->r4 = ctx->r18 | 0;
            goto L_802C5BE4;
    }
    // 0x802C5BD8: or          $a0, $s2, $zero
    ctx->r4 = ctx->r18 | 0;
    // 0x802C5BDC: b           L_802C5BE8
    // 0x802C5BE0: lw          $v1, 0x0($s3)
    ctx->r3 = MEM_W(ctx->r19, 0X0);
        goto L_802C5BE8;
    // 0x802C5BE0: lw          $v1, 0x0($s3)
    ctx->r3 = MEM_W(ctx->r19, 0X0);
L_802C5BE4:
    // 0x802C5BE4: lw          $v1, 0x0($s4)
    ctx->r3 = MEM_W(ctx->r20, 0X0);
L_802C5BE8:
    // 0x802C5BE8: addiu       $t0, $zero, 0xA9
    ctx->r8 = ADD32(0, 0XA9);
    // 0x802C5BEC: addiu       $t1, $zero, 0x10
    ctx->r9 = ADD32(0, 0X10);
    // 0x802C5BF0: sw          $t1, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r9;
    // 0x802C5BF4: sw          $t0, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r8;
    // 0x802C5BF8: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C5BFC: addiu       $a2, $v1, 0x8
    ctx->r6 = ADD32(ctx->r3, 0X8);
    // 0x802C5C00: jal         0x80094338
    // 0x802C5C04: or          $a3, $s1, $zero
    ctx->r7 = ctx->r17 | 0;
    func_80094338(rdram, ctx);
        goto after_0;
    // 0x802C5C04: or          $a3, $s1, $zero
    ctx->r7 = ctx->r17 | 0;
    after_0:
    // 0x802C5C08: lw          $t2, 0x0($s5)
    ctx->r10 = MEM_W(ctx->r21, 0X0);
    // 0x802C5C0C: addiu       $s0, $s0, 0x1
    ctx->r16 = ADD32(ctx->r16, 0X1);
    // 0x802C5C10: addiu       $s1, $s1, 0x12
    ctx->r17 = ADD32(ctx->r17, 0X12);
    // 0x802C5C14: slt         $at, $s0, $t2
    ctx->r1 = SIGNED(ctx->r16) < SIGNED(ctx->r10) ? 1 : 0;
    // 0x802C5C18: bne         $at, $zero, L_802C5BD0
    if (ctx->r1 != 0) {
        // 0x802C5C1C: or          $s2, $v0, $zero
        ctx->r18 = ctx->r2 | 0;
            goto L_802C5BD0;
    }
    // 0x802C5C1C: or          $s2, $v0, $zero
    ctx->r18 = ctx->r2 | 0;
    // 0x802C5C20: or          $s0, $zero, $zero
    ctx->r16 = 0 | 0;
L_802C5C24:
    // 0x802C5C24: lui         $s3, 0x802C
    ctx->r19 = S32(0X802C << 16);
    // 0x802C5C28: lui         $s4, 0x802C
    ctx->r20 = S32(0X802C << 16);
    // 0x802C5C2C: addiu       $t3, $zero, 0xFF
    ctx->r11 = ADD32(0, 0XFF);
    // 0x802C5C30: addiu       $t4, $zero, 0xFF
    ctx->r12 = ADD32(0, 0XFF);
    // 0x802C5C34: addiu       $t5, $zero, 0xFF
    ctx->r13 = ADD32(0, 0XFF);
    // 0x802C5C38: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C5C3C: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C5C40: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C5C44: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C5C48: addiu       $t0, $zero, 0xFF
    ctx->r8 = ADD32(0, 0XFF);
    // 0x802C5C4C: addiu       $t1, $zero, 0xFF
    ctx->r9 = ADD32(0, 0XFF);
    // 0x802C5C50: addiu       $t2, $zero, 0xFF
    ctx->r10 = ADD32(0, 0XFF);
    // 0x802C5C54: addiu       $s4, $s4, 0x61E8
    ctx->r20 = ADD32(ctx->r20, 0X61E8);
    // 0x802C5C58: addiu       $s3, $s3, 0x61E4
    ctx->r19 = ADD32(ctx->r19, 0X61E4);
    // 0x802C5C5C: sw          $t2, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r10;
    // 0x802C5C60: sw          $t1, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r9;
    // 0x802C5C64: sw          $t0, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r8;
    // 0x802C5C68: sw          $t9, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r25;
    // 0x802C5C6C: sw          $t8, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r24;
    // 0x802C5C70: sw          $t7, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r15;
    // 0x802C5C74: sw          $t6, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r14;
    // 0x802C5C78: sw          $t5, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r13;
    // 0x802C5C7C: sw          $t4, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r12;
    // 0x802C5C80: sw          $t3, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r11;
    // 0x802C5C84: or          $a0, $s2, $zero
    ctx->r4 = ctx->r18 | 0;
    // 0x802C5C88: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C5C8C: addiu       $a2, $zero, 0xFF
    ctx->r6 = ADD32(0, 0XFF);
    // 0x802C5C90: jal         0x801E946C
    // 0x802C5C94: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    func_801E946C(rdram, ctx);
        goto after_1;
    // 0x802C5C94: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    after_1:
    // 0x802C5C98: lui         $a0, 0x801D
    ctx->r4 = S32(0X801D << 16);
    // 0x802C5C9C: lw          $a0, -0x19F8($a0)
    ctx->r4 = MEM_W(ctx->r4, -0X19F8);
    // 0x802C5CA0: addiu       $at, $zero, 0x4
    ctx->r1 = ADD32(0, 0X4);
    // 0x802C5CA4: or          $s2, $v0, $zero
    ctx->r18 = ctx->r2 | 0;
    // 0x802C5CA8: bne         $a0, $at, L_802C5CBC
    if (ctx->r4 != ctx->r1) {
        // 0x802C5CAC: lui         $s1, 0x802C
        ctx->r17 = S32(0X802C << 16);
            goto L_802C5CBC;
    }
    // 0x802C5CAC: lui         $s1, 0x802C
    ctx->r17 = S32(0X802C << 16);
    // 0x802C5CB0: lui         $s1, 0x802C
    ctx->r17 = S32(0X802C << 16);
    // 0x802C5CB4: b           L_802C5CC0
    // 0x802C5CB8: addiu       $s1, $s1, 0x6114
    ctx->r17 = ADD32(ctx->r17, 0X6114);
        goto L_802C5CC0;
    // 0x802C5CB8: addiu       $s1, $s1, 0x6114
    ctx->r17 = ADD32(ctx->r17, 0X6114);
L_802C5CBC:
    // 0x802C5CBC: addiu       $s1, $s1, 0x60F4
    ctx->r17 = ADD32(ctx->r17, 0X60F4);
L_802C5CC0:
    // 0x802C5CC0: lw          $v1, 0x0($s5)
    ctx->r3 = MEM_W(ctx->r21, 0X0);
    // 0x802C5CC4: lui         $s5, 0x802C
    ctx->r21 = S32(0X802C << 16);
    // 0x802C5CC8: addiu       $s5, $s5, 0x60F0
    ctx->r21 = ADD32(ctx->r21, 0X60F0);
    // 0x802C5CCC: blez        $v1, L_802C5D48
    if (SIGNED(ctx->r3) <= 0) {
        // 0x802C5CD0: nop
    
            goto L_802C5D48;
    }
    // 0x802C5CD0: nop

L_802C5CD4:
    // 0x802C5CD4: lw          $t3, 0x0($s5)
    ctx->r11 = MEM_W(ctx->r21, 0X0);
    // 0x802C5CD8: sll         $v0, $s0, 3
    ctx->r2 = S32(ctx->r16 << 3);
    // 0x802C5CDC: addu        $v0, $v0, $s0
    ctx->r2 = ADD32(ctx->r2, ctx->r16);
    // 0x802C5CE0: beq         $s0, $t3, L_802C5D30
    if (ctx->r16 == ctx->r11) {
        // 0x802C5CE4: sll         $v0, $v0, 1
        ctx->r2 = S32(ctx->r2 << 1);
            goto L_802C5D30;
    }
    // 0x802C5CE4: sll         $v0, $v0, 1
    ctx->r2 = S32(ctx->r2 << 1);
    // 0x802C5CE8: andi        $t4, $s0, 0x1
    ctx->r12 = ctx->r16 & 0X1;
    // 0x802C5CEC: beq         $t4, $zero, L_802C5CFC
    if (ctx->r12 == 0) {
        // 0x802C5CF0: addiu       $v0, $v0, 0x64
        ctx->r2 = ADD32(ctx->r2, 0X64);
            goto L_802C5CFC;
    }
    // 0x802C5CF0: addiu       $v0, $v0, 0x64
    ctx->r2 = ADD32(ctx->r2, 0X64);
    // 0x802C5CF4: b           L_802C5D00
    // 0x802C5CF8: lw          $v1, 0x0($s3)
    ctx->r3 = MEM_W(ctx->r19, 0X0);
        goto L_802C5D00;
    // 0x802C5CF8: lw          $v1, 0x0($s3)
    ctx->r3 = MEM_W(ctx->r19, 0X0);
L_802C5CFC:
    // 0x802C5CFC: lw          $v1, 0x0($s4)
    ctx->r3 = MEM_W(ctx->r20, 0X0);
L_802C5D00:
    // 0x802C5D00: lh          $t5, 0x0($s1)
    ctx->r13 = MEM_H(ctx->r17, 0X0);
    // 0x802C5D04: lw          $a2, 0x4($s1)
    ctx->r6 = MEM_W(ctx->r17, 0X4);
    // 0x802C5D08: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    // 0x802C5D0C: addu        $a3, $v1, $t5
    ctx->r7 = ADD32(ctx->r3, ctx->r13);
    // 0x802C5D10: addiu       $a3, $a3, 0x3C
    ctx->r7 = ADD32(ctx->r7, 0X3C);
    // 0x802C5D14: sw          $v0, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r2;
    // 0x802C5D18: or          $a0, $s2, $zero
    ctx->r4 = ctx->r18 | 0;
    // 0x802C5D1C: jal         0x801E3EE0
    // 0x802C5D20: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    func_801E3EE0(rdram, ctx);
        goto after_2;
    // 0x802C5D20: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    after_2:
    // 0x802C5D24: lui         $v1, 0x802C
    ctx->r3 = S32(0X802C << 16);
    // 0x802C5D28: lw          $v1, 0x61EC($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X61EC);
    // 0x802C5D2C: or          $s2, $v0, $zero
    ctx->r18 = ctx->r2 | 0;
L_802C5D30:
    // 0x802C5D30: addiu       $s0, $s0, 0x1
    ctx->r16 = ADD32(ctx->r16, 0X1);
    // 0x802C5D34: slt         $at, $s0, $v1
    ctx->r1 = SIGNED(ctx->r16) < SIGNED(ctx->r3) ? 1 : 0;
    // 0x802C5D38: bne         $at, $zero, L_802C5CD4
    if (ctx->r1 != 0) {
        // 0x802C5D3C: addiu       $s1, $s1, 0x8
        ctx->r17 = ADD32(ctx->r17, 0X8);
            goto L_802C5CD4;
    }
    // 0x802C5D3C: addiu       $s1, $s1, 0x8
    ctx->r17 = ADD32(ctx->r17, 0X8);
    // 0x802C5D40: lui         $a0, 0x801D
    ctx->r4 = S32(0X801D << 16);
    // 0x802C5D44: lw          $a0, -0x19F8($a0)
    ctx->r4 = MEM_W(ctx->r4, -0X19F8);
L_802C5D48:
    // 0x802C5D48: lui         $s5, 0x802C
    ctx->r21 = S32(0X802C << 16);
    // 0x802C5D4C: addiu       $s5, $s5, 0x60F0
    ctx->r21 = ADD32(ctx->r21, 0X60F0);
    // 0x802C5D50: lw          $s0, 0x0($s5)
    ctx->r16 = MEM_W(ctx->r21, 0X0);
    // 0x802C5D54: andi        $t6, $s0, 0x1
    ctx->r14 = ctx->r16 & 0X1;
    // 0x802C5D58: beql        $t6, $zero, L_802C5D6C
    if (ctx->r14 == 0) {
        // 0x802C5D5C: lw          $v1, 0x0($s4)
        ctx->r3 = MEM_W(ctx->r20, 0X0);
            goto L_802C5D6C;
    }
    goto skip_0;
    // 0x802C5D5C: lw          $v1, 0x0($s4)
    ctx->r3 = MEM_W(ctx->r20, 0X0);
    skip_0:
    // 0x802C5D60: b           L_802C5D6C
    // 0x802C5D64: lw          $v1, 0x0($s3)
    ctx->r3 = MEM_W(ctx->r19, 0X0);
        goto L_802C5D6C;
    // 0x802C5D64: lw          $v1, 0x0($s3)
    ctx->r3 = MEM_W(ctx->r19, 0X0);
    // 0x802C5D68: lw          $v1, 0x0($s4)
    ctx->r3 = MEM_W(ctx->r20, 0X0);
L_802C5D6C:
    // 0x802C5D6C: addiu       $at, $zero, 0x4
    ctx->r1 = ADD32(0, 0X4);
    // 0x802C5D70: bne         $a0, $at, L_802C5D8C
    if (ctx->r4 != ctx->r1) {
        // 0x802C5D74: addiu       $a1, $zero, 0x6
        ctx->r5 = ADD32(0, 0X6);
            goto L_802C5D8C;
    }
    // 0x802C5D74: addiu       $a1, $zero, 0x6
    ctx->r5 = ADD32(0, 0X6);
    // 0x802C5D78: lui         $t8, 0x802C
    ctx->r24 = S32(0X802C << 16);
    // 0x802C5D7C: addiu       $t8, $t8, 0x6114
    ctx->r24 = ADD32(ctx->r24, 0X6114);
    // 0x802C5D80: sll         $t7, $s0, 3
    ctx->r15 = S32(ctx->r16 << 3);
    // 0x802C5D84: b           L_802C5D9C
    // 0x802C5D88: addu        $s1, $t7, $t8
    ctx->r17 = ADD32(ctx->r15, ctx->r24);
        goto L_802C5D9C;
    // 0x802C5D88: addu        $s1, $t7, $t8
    ctx->r17 = ADD32(ctx->r15, ctx->r24);
L_802C5D8C:
    // 0x802C5D8C: lui         $t0, 0x802C
    ctx->r8 = S32(0X802C << 16);
    // 0x802C5D90: addiu       $t0, $t0, 0x60F4
    ctx->r8 = ADD32(ctx->r8, 0X60F4);
    // 0x802C5D94: sll         $t9, $s0, 3
    ctx->r25 = S32(ctx->r16 << 3);
    // 0x802C5D98: addu        $s1, $t9, $t0
    ctx->r17 = ADD32(ctx->r25, ctx->r8);
L_802C5D9C:
    // 0x802C5D9C: addiu       $t1, $zero, 0xFF
    ctx->r9 = ADD32(0, 0XFF);
    // 0x802C5DA0: addiu       $t2, $zero, 0xFF
    ctx->r10 = ADD32(0, 0XFF);
    // 0x802C5DA4: addiu       $t3, $zero, 0xFF
    ctx->r11 = ADD32(0, 0XFF);
    // 0x802C5DA8: addiu       $t4, $zero, 0xFF
    ctx->r12 = ADD32(0, 0XFF);
    // 0x802C5DAC: addiu       $t5, $zero, 0xFF
    ctx->r13 = ADD32(0, 0XFF);
    // 0x802C5DB0: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C5DB4: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C5DB8: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C5DBC: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C5DC0: addiu       $t0, $zero, 0xFF
    ctx->r8 = ADD32(0, 0XFF);
    // 0x802C5DC4: sw          $t0, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r8;
    // 0x802C5DC8: sw          $t9, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r25;
    // 0x802C5DCC: sw          $t8, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r24;
    // 0x802C5DD0: sw          $t7, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r15;
    // 0x802C5DD4: sw          $t6, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r14;
    // 0x802C5DD8: sw          $t5, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r13;
    // 0x802C5DDC: sw          $t4, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r12;
    // 0x802C5DE0: sw          $t3, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r11;
    // 0x802C5DE4: sw          $t2, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r10;
    // 0x802C5DE8: sw          $t1, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r9;
    // 0x802C5DEC: or          $a0, $s2, $zero
    ctx->r4 = ctx->r18 | 0;
    // 0x802C5DF0: addiu       $a2, $zero, 0xFF
    ctx->r6 = ADD32(0, 0XFF);
    // 0x802C5DF4: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    // 0x802C5DF8: jal         0x801E946C
    // 0x802C5DFC: sw          $v1, 0x58($sp)
    MEM_W(0X58, ctx->r29) = ctx->r3;
    func_801E946C(rdram, ctx);
        goto after_3;
    // 0x802C5DFC: sw          $v1, 0x58($sp)
    MEM_W(0X58, ctx->r29) = ctx->r3;
    after_3:
    // 0x802C5E00: lw          $v1, 0x58($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X58);
    // 0x802C5E04: lh          $t1, 0x0($s1)
    ctx->r9 = MEM_H(ctx->r17, 0X0);
    // 0x802C5E08: sll         $t2, $s0, 3
    ctx->r10 = S32(ctx->r16 << 3);
    // 0x802C5E0C: addu        $t2, $t2, $s0
    ctx->r10 = ADD32(ctx->r10, ctx->r16);
    // 0x802C5E10: sll         $t2, $t2, 1
    ctx->r10 = S32(ctx->r10 << 1);
    // 0x802C5E14: addiu       $t3, $t2, 0x64
    ctx->r11 = ADD32(ctx->r10, 0X64);
    // 0x802C5E18: lw          $a2, 0x4($s1)
    ctx->r6 = MEM_W(ctx->r17, 0X4);
    // 0x802C5E1C: addu        $a3, $v1, $t1
    ctx->r7 = ADD32(ctx->r3, ctx->r9);
    // 0x802C5E20: addiu       $a3, $a3, 0x3C
    ctx->r7 = ADD32(ctx->r7, 0X3C);
    // 0x802C5E24: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    // 0x802C5E28: sw          $t3, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r11;
    // 0x802C5E2C: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C5E30: jal         0x801E3EE0
    // 0x802C5E34: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    func_801E3EE0(rdram, ctx);
        goto after_4;
    // 0x802C5E34: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    after_4:
    // 0x802C5E38: lw          $ra, 0x54($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X54);
    // 0x802C5E3C: lw          $s0, 0x3C($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X3C);
    // 0x802C5E40: lw          $s1, 0x40($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X40);
    // 0x802C5E44: lw          $s2, 0x44($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X44);
    // 0x802C5E48: lw          $s3, 0x48($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X48);
    // 0x802C5E4C: lw          $s4, 0x4C($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X4C);
    // 0x802C5E50: lw          $s5, 0x50($sp)
    ctx->r21 = MEM_W(ctx->r29, 0X50);
    // 0x802C5E54: jr          $ra
    // 0x802C5E58: addiu       $sp, $sp, 0x60
    ctx->r29 = ADD32(ctx->r29, 0X60);
    return;
    // 0x802C5E58: addiu       $sp, $sp, 0x60
    ctx->r29 = ADD32(ctx->r29, 0X60);
;}
RECOMP_FUNC void func_i14_802C5E5C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C5E5C: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x802C5E60: addiu       $v0, $v0, -0x54DC
    ctx->r2 = ADD32(ctx->r2, -0X54DC);
    // 0x802C5E64: lw          $t6, 0x0($v0)
    ctx->r14 = MEM_W(ctx->r2, 0X0);
    // 0x802C5E68: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C5E6C: addiu       $t7, $zero, 0x51
    ctx->r15 = ADD32(0, 0X51);
    // 0x802C5E70: sw          $t6, -0x19CC($at)
    MEM_W(-0X19CC, ctx->r1) = ctx->r14;
    // 0x802C5E74: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C5E78: sw          $a0, -0x19D0($at)
    MEM_W(-0X19D0, ctx->r1) = ctx->r4;
    // 0x802C5E7C: sw          $t7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r15;
    // 0x802C5E80: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C5E84: addiu       $t8, $zero, 0xD
    ctx->r24 = ADD32(0, 0XD);
    // 0x802C5E88: sw          $t8, -0x19C8($at)
    MEM_W(-0X19C8, ctx->r1) = ctx->r24;
    // 0x802C5E8C: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C5E90: addiu       $t9, $zero, 0x1
    ctx->r25 = ADD32(0, 0X1);
    // 0x802C5E94: sw          $t9, -0x19C4($at)
    MEM_W(-0X19C4, ctx->r1) = ctx->r25;
    // 0x802C5E98: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C5E9C: sw          $zero, -0x19C0($at)
    MEM_W(-0X19C0, ctx->r1) = 0;
    // 0x802C5EA0: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C5EA4: sw          $zero, -0x19BC($at)
    MEM_W(-0X19BC, ctx->r1) = 0;
    // 0x802C5EA8: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x802C5EAC: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x802C5EB0: sw          $zero, -0x54E4($at)
    MEM_W(-0X54E4, ctx->r1) = 0;
    // 0x802C5EB4: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x802C5EB8: lui         $at, 0x800D
    ctx->r1 = S32(0X800D << 16);
    // 0x802C5EBC: addiu       $t0, $zero, 0x2
    ctx->r8 = ADD32(0, 0X2);
    // 0x802C5EC0: sw          $t0, 0x461C($at)
    MEM_W(0X461C, ctx->r1) = ctx->r8;
    // 0x802C5EC4: addiu       $a0, $zero, 0x5
    ctx->r4 = ADD32(0, 0X5);
    // 0x802C5EC8: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C5ECC: jal         0x801E6FB0
    // 0x802C5ED0: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    FadeTransition_SetProps(rdram, ctx);
        goto after_0;
    // 0x802C5ED0: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    after_0:
    // 0x802C5ED4: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    // 0x802C5ED8: jal         0x801E6A4C
    // 0x802C5EDC: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_801E6A4C(rdram, ctx);
        goto after_1;
    // 0x802C5EDC: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_1:
    // 0x802C5EE0: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x802C5EE4: lw          $v0, -0x19D0($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X19D0);
    // 0x802C5EE8: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x802C5EEC: bnel        $v0, $at, L_802C5F08
    if (ctx->r2 != ctx->r1) {
        // 0x802C5EF0: addiu       $at, $zero, 0x14
        ctx->r1 = ADD32(0, 0X14);
            goto L_802C5F08;
    }
    goto skip_0;
    // 0x802C5EF0: addiu       $at, $zero, 0x14
    ctx->r1 = ADD32(0, 0X14);
    skip_0:
    // 0x802C5EF4: jal         0x800C1F60
    // 0x802C5EF8: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    func_800C1F60(rdram, ctx);
        goto after_2;
    // 0x802C5EF8: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    after_2:
    // 0x802C5EFC: b           L_802C5F54
    // 0x802C5F00: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_802C5F54;
    // 0x802C5F00: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x802C5F04: addiu       $at, $zero, 0x14
    ctx->r1 = ADD32(0, 0X14);
L_802C5F08:
    // 0x802C5F08: bnel        $v0, $at, L_802C5F24
    if (ctx->r2 != ctx->r1) {
        // 0x802C5F0C: addiu       $at, $zero, 0xA
        ctx->r1 = ADD32(0, 0XA);
            goto L_802C5F24;
    }
    goto skip_1;
    // 0x802C5F0C: addiu       $at, $zero, 0xA
    ctx->r1 = ADD32(0, 0XA);
    skip_1:
    // 0x802C5F10: jal         0x800C1F60
    // 0x802C5F14: addiu       $a0, $zero, 0xA
    ctx->r4 = ADD32(0, 0XA);
    func_800C1F60(rdram, ctx);
        goto after_3;
    // 0x802C5F14: addiu       $a0, $zero, 0xA
    ctx->r4 = ADD32(0, 0XA);
    after_3:
    // 0x802C5F18: b           L_802C5F54
    // 0x802C5F1C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_802C5F54;
    // 0x802C5F1C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x802C5F20: addiu       $at, $zero, 0xA
    ctx->r1 = ADD32(0, 0XA);
L_802C5F24:
    // 0x802C5F24: bnel        $v0, $at, L_802C5F40
    if (ctx->r2 != ctx->r1) {
        // 0x802C5F28: addiu       $at, $zero, 0x28
        ctx->r1 = ADD32(0, 0X28);
            goto L_802C5F40;
    }
    goto skip_2;
    // 0x802C5F28: addiu       $at, $zero, 0x28
    ctx->r1 = ADD32(0, 0X28);
    skip_2:
    // 0x802C5F2C: jal         0x800C1F60
    // 0x802C5F30: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    func_800C1F60(rdram, ctx);
        goto after_4;
    // 0x802C5F30: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    after_4:
    // 0x802C5F34: b           L_802C5F54
    // 0x802C5F38: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_802C5F54;
    // 0x802C5F38: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x802C5F3C: addiu       $at, $zero, 0x28
    ctx->r1 = ADD32(0, 0X28);
L_802C5F40:
    // 0x802C5F40: bnel        $v0, $at, L_802C5F54
    if (ctx->r2 != ctx->r1) {
        // 0x802C5F44: lw          $ra, 0x14($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X14);
            goto L_802C5F54;
    }
    goto skip_3;
    // 0x802C5F44: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    skip_3:
    // 0x802C5F48: jal         0x800C1F60
    // 0x802C5F4C: addiu       $a0, $zero, 0x7
    ctx->r4 = ADD32(0, 0X7);
    func_800C1F60(rdram, ctx);
        goto after_5;
    // 0x802C5F4C: addiu       $a0, $zero, 0x7
    ctx->r4 = ADD32(0, 0X7);
    after_5:
    // 0x802C5F50: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C5F54:
    // 0x802C5F54: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x802C5F58: jr          $ra
    // 0x802C5F5C: nop

    return;
    // 0x802C5F5C: nop

;}
RECOMP_FUNC void func_i14_802C5F60(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C5F60: lui         $a0, 0x802C
    ctx->r4 = S32(0X802C << 16);
    // 0x802C5F64: addiu       $a0, $a0, 0x61E0
    ctx->r4 = ADD32(ctx->r4, 0X61E0);
    // 0x802C5F68: lw          $t6, 0x0($a0)
    ctx->r14 = MEM_W(ctx->r4, 0X0);
    // 0x802C5F6C: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x802C5F70: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x802C5F74: bne         $t6, $zero, L_802C5FBC
    if (ctx->r14 != 0) {
        // 0x802C5F78: lui         $v0, 0x802C
        ctx->r2 = S32(0X802C << 16);
            goto L_802C5FBC;
    }
    // 0x802C5F78: lui         $v0, 0x802C
    ctx->r2 = S32(0X802C << 16);
    // 0x802C5F7C: lui         $v1, 0x802C
    ctx->r3 = S32(0X802C << 16);
    // 0x802C5F80: addiu       $v1, $v1, 0x61E4
    ctx->r3 = ADD32(ctx->r3, 0X61E4);
    // 0x802C5F84: lw          $t7, 0x0($v1)
    ctx->r15 = MEM_W(ctx->r3, 0X0);
    // 0x802C5F88: addiu       $t9, $zero, 0x1
    ctx->r25 = ADD32(0, 0X1);
    // 0x802C5F8C: addiu       $t1, $zero, 0x100
    ctx->r9 = ADD32(0, 0X100);
    // 0x802C5F90: addiu       $v0, $t7, -0x14
    ctx->r2 = ADD32(ctx->r15, -0X14);
    // 0x802C5F94: slti        $at, $v0, 0x80
    ctx->r1 = SIGNED(ctx->r2) < 0X80 ? 1 : 0;
    // 0x802C5F98: beq         $at, $zero, L_802C5FAC
    if (ctx->r1 == 0) {
        // 0x802C5F9C: sw          $v0, 0x0($v1)
        MEM_W(0X0, ctx->r3) = ctx->r2;
            goto L_802C5FAC;
    }
    // 0x802C5F9C: sw          $v0, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r2;
    // 0x802C5FA0: addiu       $v0, $zero, 0x80
    ctx->r2 = ADD32(0, 0X80);
    // 0x802C5FA4: sw          $t9, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r25;
    // 0x802C5FA8: sw          $v0, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r2;
L_802C5FAC:
    // 0x802C5FAC: subu        $t2, $t1, $v0
    ctx->r10 = SUB32(ctx->r9, ctx->r2);
    // 0x802C5FB0: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C5FB4: b           L_802C60D8
    // 0x802C5FB8: sw          $t2, 0x61E8($at)
    MEM_W(0X61E8, ctx->r1) = ctx->r10;
        goto L_802C60D8;
    // 0x802C5FB8: sw          $t2, 0x61E8($at)
    MEM_W(0X61E8, ctx->r1) = ctx->r10;
L_802C5FBC:
    // 0x802C5FBC: addiu       $v0, $v0, 0x613C
    ctx->r2 = ADD32(ctx->r2, 0X613C);
    // 0x802C5FC0: lw          $t3, 0x0($v0)
    ctx->r11 = MEM_W(ctx->r2, 0X0);
    // 0x802C5FC4: addiu       $t4, $zero, 0x1
    ctx->r12 = ADD32(0, 0X1);
    // 0x802C5FC8: bne         $t3, $zero, L_802C5FD8
    if (ctx->r11 != 0) {
        // 0x802C5FCC: nop
    
            goto L_802C5FD8;
    }
    // 0x802C5FCC: nop

    // 0x802C5FD0: jal         0x800C30F8
    // 0x802C5FD4: sw          $t4, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r12;
    func_800C30F8(rdram, ctx);
        goto after_0;
    // 0x802C5FD4: sw          $t4, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r12;
    after_0:
L_802C5FD8:
    // 0x802C5FD8: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x802C5FDC: lhu         $v0, -0x19A6($v0)
    ctx->r2 = MEM_HU(ctx->r2, -0X19A6);
    // 0x802C5FE0: lui         $t6, 0x801D
    ctx->r14 = S32(0X801D << 16);
    // 0x802C5FE4: andi        $t5, $v0, 0xB000
    ctx->r13 = ctx->r2 & 0XB000;
    // 0x802C5FE8: beq         $t5, $zero, L_802C6058
    if (ctx->r13 == 0) {
        // 0x802C5FEC: andi        $t1, $v0, 0x800
        ctx->r9 = ctx->r2 & 0X800;
            goto L_802C6058;
    }
    // 0x802C5FEC: andi        $t1, $v0, 0x800
    ctx->r9 = ctx->r2 & 0X800;
    // 0x802C5FF0: lw          $t6, -0x19F8($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X19F8);
    // 0x802C5FF4: addiu       $at, $zero, 0x4
    ctx->r1 = ADD32(0, 0X4);
    // 0x802C5FF8: lui         $v0, 0x802C
    ctx->r2 = S32(0X802C << 16);
    // 0x802C5FFC: bne         $t6, $at, L_802C602C
    if (ctx->r14 != ctx->r1) {
        // 0x802C6000: addiu       $v0, $v0, 0x60F0
        ctx->r2 = ADD32(ctx->r2, 0X60F0);
            goto L_802C602C;
    }
    // 0x802C6000: addiu       $v0, $v0, 0x60F0
    ctx->r2 = ADD32(ctx->r2, 0X60F0);
    // 0x802C6004: lui         $v0, 0x802C
    ctx->r2 = S32(0X802C << 16);
    // 0x802C6008: addiu       $v0, $v0, 0x60F0
    ctx->r2 = ADD32(ctx->r2, 0X60F0);
    // 0x802C600C: lw          $t7, 0x0($v0)
    ctx->r15 = MEM_W(ctx->r2, 0X0);
    // 0x802C6010: lui         $a0, 0x802C
    ctx->r4 = S32(0X802C << 16);
    // 0x802C6014: sll         $t8, $t7, 2
    ctx->r24 = S32(ctx->r15 << 2);
    // 0x802C6018: addu        $a0, $a0, $t8
    ctx->r4 = ADD32(ctx->r4, ctx->r24);
    // 0x802C601C: jal         0x802C5E5C
    // 0x802C6020: lw          $a0, 0x6134($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X6134);
    func_i14_802C5E5C(rdram, ctx);
        goto after_1;
    // 0x802C6020: lw          $a0, 0x6134($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X6134);
    after_1:
    // 0x802C6024: b           L_802C6048
    // 0x802C6028: addiu       $a0, $zero, 0x11
    ctx->r4 = ADD32(0, 0X11);
        goto L_802C6048;
    // 0x802C6028: addiu       $a0, $zero, 0x11
    ctx->r4 = ADD32(0, 0X11);
L_802C602C:
    // 0x802C602C: lw          $t9, 0x0($v0)
    ctx->r25 = MEM_W(ctx->r2, 0X0);
    // 0x802C6030: lui         $a0, 0x802C
    ctx->r4 = S32(0X802C << 16);
    // 0x802C6034: sll         $t0, $t9, 2
    ctx->r8 = S32(ctx->r25 << 2);
    // 0x802C6038: addu        $a0, $a0, $t0
    ctx->r4 = ADD32(ctx->r4, ctx->r8);
    // 0x802C603C: jal         0x802C5E5C
    // 0x802C6040: lw          $a0, 0x6124($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X6124);
    func_i14_802C5E5C(rdram, ctx);
        goto after_2;
    // 0x802C6040: lw          $a0, 0x6124($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X6124);
    after_2:
    // 0x802C6044: addiu       $a0, $zero, 0x11
    ctx->r4 = ADD32(0, 0X11);
L_802C6048:
    // 0x802C6048: jal         0x800C37F4
    // 0x802C604C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_3;
    // 0x802C604C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_3:
    // 0x802C6050: b           L_802C60DC
    // 0x802C6054: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_802C60DC;
    // 0x802C6054: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C6058:
    // 0x802C6058: beq         $t1, $zero, L_802C609C
    if (ctx->r9 == 0) {
        // 0x802C605C: andi        $t7, $v0, 0x400
        ctx->r15 = ctx->r2 & 0X400;
            goto L_802C609C;
    }
    // 0x802C605C: andi        $t7, $v0, 0x400
    ctx->r15 = ctx->r2 & 0X400;
    // 0x802C6060: lui         $v0, 0x802C
    ctx->r2 = S32(0X802C << 16);
    // 0x802C6064: addiu       $v0, $v0, 0x60F0
    ctx->r2 = ADD32(ctx->r2, 0X60F0);
    // 0x802C6068: lw          $t2, 0x0($v0)
    ctx->r10 = MEM_W(ctx->r2, 0X0);
    // 0x802C606C: lui         $t5, 0x802C
    ctx->r13 = S32(0X802C << 16);
    // 0x802C6070: addiu       $a0, $zero, 0x10
    ctx->r4 = ADD32(0, 0X10);
    // 0x802C6074: addiu       $t3, $t2, -0x1
    ctx->r11 = ADD32(ctx->r10, -0X1);
    // 0x802C6078: bgez        $t3, L_802C608C
    if (SIGNED(ctx->r11) >= 0) {
        // 0x802C607C: sw          $t3, 0x0($v0)
        MEM_W(0X0, ctx->r2) = ctx->r11;
            goto L_802C608C;
    }
    // 0x802C607C: sw          $t3, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r11;
    // 0x802C6080: lw          $t5, 0x61EC($t5)
    ctx->r13 = MEM_W(ctx->r13, 0X61EC);
    // 0x802C6084: addiu       $t6, $t5, -0x1
    ctx->r14 = ADD32(ctx->r13, -0X1);
    // 0x802C6088: sw          $t6, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r14;
L_802C608C:
    // 0x802C608C: jal         0x800C37F4
    // 0x802C6090: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_4;
    // 0x802C6090: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_4:
    // 0x802C6094: b           L_802C60DC
    // 0x802C6098: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_802C60DC;
    // 0x802C6098: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C609C:
    // 0x802C609C: beq         $t7, $zero, L_802C60D8
    if (ctx->r15 == 0) {
        // 0x802C60A0: lui         $v0, 0x802C
        ctx->r2 = S32(0X802C << 16);
            goto L_802C60D8;
    }
    // 0x802C60A0: lui         $v0, 0x802C
    ctx->r2 = S32(0X802C << 16);
    // 0x802C60A4: addiu       $v0, $v0, 0x60F0
    ctx->r2 = ADD32(ctx->r2, 0X60F0);
    // 0x802C60A8: lw          $t8, 0x0($v0)
    ctx->r24 = MEM_W(ctx->r2, 0X0);
    // 0x802C60AC: lui         $t1, 0x802C
    ctx->r9 = S32(0X802C << 16);
    // 0x802C60B0: addiu       $a0, $zero, 0x10
    ctx->r4 = ADD32(0, 0X10);
    // 0x802C60B4: addiu       $t9, $t8, 0x1
    ctx->r25 = ADD32(ctx->r24, 0X1);
    // 0x802C60B8: sw          $t9, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r25;
    // 0x802C60BC: lw          $t1, 0x61EC($t1)
    ctx->r9 = MEM_W(ctx->r9, 0X61EC);
    // 0x802C60C0: slt         $at, $t9, $t1
    ctx->r1 = SIGNED(ctx->r25) < SIGNED(ctx->r9) ? 1 : 0;
    // 0x802C60C4: bne         $at, $zero, L_802C60D0
    if (ctx->r1 != 0) {
        // 0x802C60C8: nop
    
            goto L_802C60D0;
    }
    // 0x802C60C8: nop

    // 0x802C60CC: sw          $zero, 0x0($v0)
    MEM_W(0X0, ctx->r2) = 0;
L_802C60D0:
    // 0x802C60D0: jal         0x800C37F4
    // 0x802C60D4: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_5;
    // 0x802C60D4: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_5:
L_802C60D8:
    // 0x802C60D8: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C60DC:
    // 0x802C60DC: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x802C60E0: jr          $ra
    // 0x802C60E4: nop

    return;
    // 0x802C60E4: nop

    // 0x802C60E8: nop

    // 0x802C60EC: nop

;}
RECOMP_FUNC void func_i15_802C5800(uint8_t* rdram, recomp_context* ctx) {
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
    // 0x802C5830: beq         $t6, $zero, L_802C58F0
    if (ctx->r14 == 0) {
        // 0x802C5834: sw          $s0, 0x38($sp)
        MEM_W(0X38, ctx->r29) = ctx->r16;
            goto L_802C58F0;
    }
    // 0x802C5834: sw          $s0, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r16;
    // 0x802C5838: lui         $t7, 0x800E
    ctx->r15 = S32(0X800E << 16);
    // 0x802C583C: lw          $t7, -0x54DC($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X54DC);
    // 0x802C5840: addiu       $at, $zero, 0x66
    ctx->r1 = ADD32(0, 0X66);
    // 0x802C5844: bne         $t7, $at, L_802C58F0
    if (ctx->r15 != ctx->r1) {
        // 0x802C5848: nop
    
            goto L_802C58F0;
    }
    // 0x802C5848: nop

    // 0x802C584C: jal         0x802C5CE8
    // 0x802C5850: nop

    func_i15_802C5CE8(rdram, ctx);
        goto after_0;
    // 0x802C5850: nop

    after_0:
    // 0x802C5854: lui         $t1, 0x802C
    ctx->r9 = S32(0X802C << 16);
    // 0x802C5858: lui         $t2, 0x802C
    ctx->r10 = S32(0X802C << 16);
    // 0x802C585C: addiu       $t2, $t2, 0x6E74
    ctx->r10 = ADD32(ctx->r10, 0X6E74);
    // 0x802C5860: addiu       $t1, $t1, 0x6E78
    ctx->r9 = ADD32(ctx->r9, 0X6E78);
    // 0x802C5864: sw          $zero, 0x0($t1)
    MEM_W(0X0, ctx->r9) = 0;
    // 0x802C5868: sw          $zero, 0x0($t2)
    MEM_W(0X0, ctx->r10) = 0;
    // 0x802C586C: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x802C5870: lw          $v0, -0x4CCC($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X4CCC);
    // 0x802C5874: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    // 0x802C5878: lui         $t9, 0x801D
    ctx->r25 = S32(0X801D << 16);
    // 0x802C587C: addiu       $v0, $v0, 0x1
    ctx->r2 = ADD32(ctx->r2, 0X1);
    // 0x802C5880: blez        $v0, L_802C58F0
    if (SIGNED(ctx->r2) <= 0) {
        // 0x802C5884: lui         $t5, 0x800F
        ctx->r13 = S32(0X800F << 16);
            goto L_802C58F0;
    }
    // 0x802C5884: lui         $t5, 0x800F
    ctx->r13 = S32(0X800F << 16);
    // 0x802C5888: lw          $t9, -0x4CC8($t9)
    ctx->r25 = MEM_W(ctx->r25, -0X4CC8);
    // 0x802C588C: addiu       $t5, $t5, -0x53EC
    ctx->r13 = ADD32(ctx->r13, -0X53EC);
    // 0x802C5890: lui         $a3, 0x801C
    ctx->r7 = S32(0X801C << 16);
    // 0x802C5894: lui         $a2, 0x801C
    ctx->r6 = S32(0X801C << 16);
    // 0x802C5898: sll         $t4, $t9, 4
    ctx->r12 = S32(ctx->r25 << 4);
    // 0x802C589C: addu        $a1, $t4, $t5
    ctx->r5 = ADD32(ctx->r12, ctx->r13);
    // 0x802C58A0: addiu       $a2, $a2, 0x2660
    ctx->r6 = ADD32(ctx->r6, 0X2660);
    // 0x802C58A4: addiu       $a3, $a3, 0x2690
    ctx->r7 = ADD32(ctx->r7, 0X2690);
    // 0x802C58A8: sll         $t0, $v0, 1
    ctx->r8 = S32(ctx->r2 << 1);
    // 0x802C58AC: addiu       $t3, $zero, 0x1
    ctx->r11 = ADD32(0, 0X1);
L_802C58B0:
    // 0x802C58B0: lh          $v0, 0x0($a1)
    ctx->r2 = MEM_H(ctx->r5, 0X0);
    // 0x802C58B4: addiu       $a0, $a0, 0x2
    ctx->r4 = ADD32(ctx->r4, 0X2);
    // 0x802C58B8: slt         $at, $a0, $t0
    ctx->r1 = SIGNED(ctx->r4) < SIGNED(ctx->r8) ? 1 : 0;
    // 0x802C58BC: sll         $v1, $v0, 2
    ctx->r3 = S32(ctx->r2 << 2);
    // 0x802C58C0: addu        $t6, $a2, $v1
    ctx->r14 = ADD32(ctx->r6, ctx->r3);
    // 0x802C58C4: lw          $t7, 0x0($t6)
    ctx->r15 = MEM_W(ctx->r14, 0X0);
    // 0x802C58C8: addu        $t8, $a3, $v1
    ctx->r24 = ADD32(ctx->r7, ctx->r3);
    // 0x802C58CC: beql        $t7, $zero, L_802C58DC
    if (ctx->r15 == 0) {
        // 0x802C58D0: lw          $t9, 0x0($t8)
        ctx->r25 = MEM_W(ctx->r24, 0X0);
            goto L_802C58DC;
    }
    goto skip_0;
    // 0x802C58D0: lw          $t9, 0x0($t8)
    ctx->r25 = MEM_W(ctx->r24, 0X0);
    skip_0:
    // 0x802C58D4: sw          $t3, 0x0($t2)
    MEM_W(0X0, ctx->r10) = ctx->r11;
    // 0x802C58D8: lw          $t9, 0x0($t8)
    ctx->r25 = MEM_W(ctx->r24, 0X0);
L_802C58DC:
    // 0x802C58DC: beq         $t9, $zero, L_802C58E8
    if (ctx->r25 == 0) {
        // 0x802C58E0: nop
    
            goto L_802C58E8;
    }
    // 0x802C58E0: nop

    // 0x802C58E4: sw          $t3, 0x0($t1)
    MEM_W(0X0, ctx->r9) = ctx->r11;
L_802C58E8:
    // 0x802C58E8: bne         $at, $zero, L_802C58B0
    if (ctx->r1 != 0) {
        // 0x802C58EC: addiu       $a1, $a1, 0x2
        ctx->r5 = ADD32(ctx->r5, 0X2);
            goto L_802C58B0;
    }
    // 0x802C58EC: addiu       $a1, $a1, 0x2
    ctx->r5 = ADD32(ctx->r5, 0X2);
L_802C58F0:
    // 0x802C58F0: lui         $s1, 0x802C
    ctx->r17 = S32(0X802C << 16);
    // 0x802C58F4: addiu       $s1, $s1, 0x6D6C
    ctx->r17 = ADD32(ctx->r17, 0X6D6C);
    // 0x802C58F8: lw          $t4, 0x0($s1)
    ctx->r12 = MEM_W(ctx->r17, 0X0);
    // 0x802C58FC: sw          $zero, 0x1D4($sp)
    MEM_W(0X1D4, ctx->r29) = 0;
    // 0x802C5900: lui         $s2, 0x802C
    ctx->r18 = S32(0X802C << 16);
    // 0x802C5904: addiu       $t5, $t4, -0x1
    ctx->r13 = ADD32(ctx->r12, -0X1);
    // 0x802C5908: bgez        $t5, L_802C5978
    if (SIGNED(ctx->r13) >= 0) {
        // 0x802C590C: sw          $t5, 0x0($s1)
        MEM_W(0X0, ctx->r17) = ctx->r13;
            goto L_802C5978;
    }
    // 0x802C590C: sw          $t5, 0x0($s1)
    MEM_W(0X0, ctx->r17) = ctx->r13;
    // 0x802C5910: addiu       $s2, $s2, 0x6D68
    ctx->r18 = ADD32(ctx->r18, 0X6D68);
    // 0x802C5914: lw          $s0, 0x0($s2)
    ctx->r16 = MEM_W(ctx->r18, 0X0);
    // 0x802C5918: addiu       $s3, $zero, -0x1
    ctx->r19 = ADD32(0, -0X1);
    // 0x802C591C: beql        $s3, $s0, L_802C597C
    if (ctx->r19 == ctx->r16) {
        // 0x802C5920: lui         $at, 0x4180
        ctx->r1 = S32(0X4180 << 16);
            goto L_802C597C;
    }
    goto skip_1;
    // 0x802C5920: lui         $at, 0x4180
    ctx->r1 = S32(0X4180 << 16);
    skip_1:
    // 0x802C5924: jal         0x802C5EE4
    // 0x802C5928: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    func_i15_802C5EE4(rdram, ctx);
        goto after_1;
    // 0x802C5928: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_1:
    // 0x802C592C: addiu       $t7, $zero, 0x28
    ctx->r15 = ADD32(0, 0X28);
    // 0x802C5930: sw          $t7, 0x0($s1)
    MEM_W(0X0, ctx->r17) = ctx->r15;
    // 0x802C5934: lui         $t8, 0x802C
    ctx->r24 = S32(0X802C << 16);
    // 0x802C5938: lw          $t8, 0x6E7C($t8)
    ctx->r24 = MEM_W(ctx->r24, 0X6E7C);
    // 0x802C593C: lw          $s0, 0x0($s2)
    ctx->r16 = MEM_W(ctx->r18, 0X0);
    // 0x802C5940: addiu       $t9, $zero, 0xA
    ctx->r25 = ADD32(0, 0XA);
    // 0x802C5944: addiu       $t4, $zero, 0x6E
    ctx->r12 = ADD32(0, 0X6E);
    // 0x802C5948: bnel        $t8, $s0, L_802C5960
    if (ctx->r24 != ctx->r16) {
        // 0x802C594C: addiu       $at, $zero, 0xA
        ctx->r1 = ADD32(0, 0XA);
            goto L_802C5960;
    }
    goto skip_2;
    // 0x802C594C: addiu       $at, $zero, 0xA
    ctx->r1 = ADD32(0, 0XA);
    skip_2:
    // 0x802C5950: sw          $t9, 0x0($s2)
    MEM_W(0X0, ctx->r18) = ctx->r25;
    // 0x802C5954: b           L_802C5978
    // 0x802C5958: sw          $t4, 0x0($s1)
    MEM_W(0X0, ctx->r17) = ctx->r12;
        goto L_802C5978;
    // 0x802C5958: sw          $t4, 0x0($s1)
    MEM_W(0X0, ctx->r17) = ctx->r12;
    // 0x802C595C: addiu       $at, $zero, 0xA
    ctx->r1 = ADD32(0, 0XA);
L_802C5960:
    // 0x802C5960: bnel        $s0, $at, L_802C5974
    if (ctx->r16 != ctx->r1) {
        // 0x802C5964: addiu       $t5, $s0, 0x1
        ctx->r13 = ADD32(ctx->r16, 0X1);
            goto L_802C5974;
    }
    goto skip_3;
    // 0x802C5964: addiu       $t5, $s0, 0x1
    ctx->r13 = ADD32(ctx->r16, 0X1);
    skip_3:
    // 0x802C5968: b           L_802C5978
    // 0x802C596C: sw          $s3, 0x0($s2)
    MEM_W(0X0, ctx->r18) = ctx->r19;
        goto L_802C5978;
    // 0x802C596C: sw          $s3, 0x0($s2)
    MEM_W(0X0, ctx->r18) = ctx->r19;
    // 0x802C5970: addiu       $t5, $s0, 0x1
    ctx->r13 = ADD32(ctx->r16, 0X1);
L_802C5974:
    // 0x802C5974: sw          $t5, 0x0($s2)
    MEM_W(0X0, ctx->r18) = ctx->r13;
L_802C5978:
    // 0x802C5978: lui         $at, 0x4180
    ctx->r1 = S32(0X4180 << 16);
L_802C597C:
    // 0x802C597C: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x802C5980: lui         $s3, 0x801D
    ctx->r19 = S32(0X801D << 16);
    // 0x802C5984: mtc1        $zero, $f0
    ctx->f0.u32l = 0;
    // 0x802C5988: addiu       $s3, $s3, -0x1A08
    ctx->r19 = ADD32(ctx->r19, -0X1A08);
    // 0x802C598C: lui         $at, 0x4580
    ctx->r1 = S32(0X4580 << 16);
    // 0x802C5990: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x802C5994: lw          $a0, 0x0($s3)
    ctx->r4 = MEM_W(ctx->r19, 0X0);
    // 0x802C5998: lui         $a1, 0x802C
    ctx->r5 = S32(0X802C << 16);
    // 0x802C599C: addiu       $a1, $a1, 0x6F40
    ctx->r5 = ADD32(ctx->r5, 0X6F40);
    // 0x802C59A0: lui         $a2, 0x4204
    ctx->r6 = S32(0X4204 << 16);
    // 0x802C59A4: lui         $a3, 0x3F80
    ctx->r7 = S32(0X3F80 << 16);
    // 0x802C59A8: swc1        $f4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f4.u32l;
    // 0x802C59AC: swc1        $f0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->f0.u32l;
    // 0x802C59B0: swc1        $f0, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->f0.u32l;
    // 0x802C59B4: addiu       $a0, $a0, 0xA40
    ctx->r4 = ADD32(ctx->r4, 0XA40);
    // 0x802C59B8: jal         0x800481E0
    // 0x802C59BC: swc1        $f6, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->f6.u32l;
    func_800481E0(rdram, ctx);
        goto after_2;
    // 0x802C59BC: swc1        $f6, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->f6.u32l;
    after_2:
    // 0x802C59C0: mtc1        $zero, $f0
    ctx->f0.u32l = 0;
    // 0x802C59C4: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x802C59C8: mtc1        $at, $f2
    ctx->f2.u32l = ctx->r1;
    // 0x802C59CC: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C59D0: lwc1        $f8, 0x6E34($at)
    ctx->f8.u32l = MEM_W(ctx->r1, 0X6E34);
    // 0x802C59D4: addiu       $s0, $sp, 0xB8
    ctx->r16 = ADD32(ctx->r29, 0XB8);
    // 0x802C59D8: mfc1        $a1, $f0
    ctx->r5 = (int32_t)ctx->f0.u32l;
    // 0x802C59DC: mfc1        $a2, $f0
    ctx->r6 = (int32_t)ctx->f0.u32l;
    // 0x802C59E0: mfc1        $a3, $f2
    ctx->r7 = (int32_t)ctx->f2.u32l;
    // 0x802C59E4: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x802C59E8: swc1        $f0, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f0.u32l;
    // 0x802C59EC: swc1        $f0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->f0.u32l;
    // 0x802C59F0: swc1        $f0, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->f0.u32l;
    // 0x802C59F4: swc1        $f0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->f0.u32l;
    // 0x802C59F8: swc1        $f0, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->f0.u32l;
    // 0x802C59FC: swc1        $f2, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->f2.u32l;
    // 0x802C5A00: jal         0x80048A88
    // 0x802C5A04: swc1        $f8, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->f8.u32l;
    func_80048A88(rdram, ctx);
        goto after_3;
    // 0x802C5A04: swc1        $f8, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->f8.u32l;
    after_3:
    // 0x802C5A08: lui         $v0, 0x8015
    ctx->r2 = S32(0X8015 << 16);
    // 0x802C5A0C: addiu       $v0, $v0, 0x4350
    ctx->r2 = ADD32(ctx->r2, 0X4350);
    // 0x802C5A10: lui         $at, 0x43FA
    ctx->r1 = S32(0X43FA << 16);
    // 0x802C5A14: mtc1        $at, $f14
    ctx->f14.u32l = ctx->r1;
    // 0x802C5A18: lwc1        $f10, 0x1000($v0)
    ctx->f10.u32l = MEM_W(ctx->r2, 0X1000);
    // 0x802C5A1C: lwc1        $f16, 0x0($v0)
    ctx->f16.u32l = MEM_W(ctx->r2, 0X0);
    // 0x802C5A20: mtc1        $zero, $f0
    ctx->f0.u32l = 0;
    // 0x802C5A24: mul.s       $f2, $f10, $f14
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f2.fl = MUL_S(ctx->f10.fl, ctx->f14.fl);
    // 0x802C5A28: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x802C5A2C: mtc1        $at, $f18
    ctx->f18.u32l = ctx->r1;
    // 0x802C5A30: mul.s       $f12, $f16, $f14
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f12.fl = MUL_S(ctx->f16.fl, ctx->f14.fl);
    // 0x802C5A34: addiu       $s1, $sp, 0x13C
    ctx->r17 = ADD32(ctx->r29, 0X13C);
    // 0x802C5A38: or          $a1, $s1, $zero
    ctx->r5 = ctx->r17 | 0;
    // 0x802C5A3C: addiu       $a0, $sp, 0x78
    ctx->r4 = ADD32(ctx->r29, 0X78);
    // 0x802C5A40: mfc1        $a2, $f2
    ctx->r6 = (int32_t)ctx->f2.u32l;
    // 0x802C5A44: addiu       $a3, $zero, 0x0
    ctx->r7 = ADD32(0, 0X0);
    // 0x802C5A48: swc1        $f0, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->f0.u32l;
    // 0x802C5A4C: swc1        $f12, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f12.u32l;
    // 0x802C5A50: swc1        $f0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->f0.u32l;
    // 0x802C5A54: swc1        $f0, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->f0.u32l;
    // 0x802C5A58: swc1        $f0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->f0.u32l;
    // 0x802C5A5C: swc1        $f0, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->f0.u32l;
    // 0x802C5A60: jal         0x800484C8
    // 0x802C5A64: swc1        $f18, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->f18.u32l;
    func_800484C8(rdram, ctx);
        goto after_4;
    // 0x802C5A64: swc1        $f18, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->f18.u32l;
    after_4:
    // 0x802C5A68: addiu       $s2, $sp, 0x17C
    ctx->r18 = ADD32(ctx->r29, 0X17C);
    // 0x802C5A6C: or          $a1, $s2, $zero
    ctx->r5 = ctx->r18 | 0;
    // 0x802C5A70: jal         0x80047E78
    // 0x802C5A74: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    SysUtils_MtxToMtxF(rdram, ctx);
        goto after_5;
    // 0x802C5A74: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_5:
    // 0x802C5A78: addiu       $s5, $sp, 0xFC
    ctx->r21 = ADD32(ctx->r29, 0XFC);
    // 0x802C5A7C: or          $a2, $s5, $zero
    ctx->r6 = ctx->r21 | 0;
    // 0x802C5A80: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    // 0x802C5A84: jal         0x80049EB8
    // 0x802C5A88: or          $a1, $s2, $zero
    ctx->r5 = ctx->r18 | 0;
    SysUtils_MatrixAffineMultiply(rdram, ctx);
        goto after_6;
    // 0x802C5A88: or          $a1, $s2, $zero
    ctx->r5 = ctx->r18 | 0;
    after_6:
    // 0x802C5A8C: lui         $s4, 0x802C
    ctx->r20 = S32(0X802C << 16);
    // 0x802C5A90: lui         $fp, 0x802C
    ctx->r30 = S32(0X802C << 16);
    // 0x802C5A94: lui         $s6, 0x802C
    ctx->r22 = S32(0X802C << 16);
    // 0x802C5A98: addiu       $s6, $s6, 0x6DE0
    ctx->r22 = ADD32(ctx->r22, 0X6DE0);
    // 0x802C5A9C: addiu       $fp, $fp, 0x6DDC
    ctx->r30 = ADD32(ctx->r30, 0X6DDC);
    // 0x802C5AA0: addiu       $s4, $s4, 0x6E80
    ctx->r20 = ADD32(ctx->r20, 0X6E80);
    // 0x802C5AA4: addiu       $s7, $zero, 0x80
    ctx->r23 = ADD32(0, 0X80);
    // 0x802C5AA8: addiu       $a0, $zero, 0xA
    ctx->r4 = ADD32(0, 0XA);
L_802C5AAC:
    // 0x802C5AAC: lw          $v1, 0x0($s4)
    ctx->r3 = MEM_W(ctx->r20, 0X0);
    // 0x802C5AB0: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x802C5AB4: beql        $v1, $zero, L_802C5CA8
    if (ctx->r3 == 0) {
        // 0x802C5AB8: lw          $t9, 0x1D4($sp)
        ctx->r25 = MEM_W(ctx->r29, 0X1D4);
            goto L_802C5CA8;
    }
    goto skip_4;
    // 0x802C5AB8: lw          $t9, 0x1D4($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X1D4);
    skip_4:
    // 0x802C5ABC: beq         $v1, $at, L_802C5AE4
    if (ctx->r3 == ctx->r1) {
        // 0x802C5AC0: or          $s0, $zero, $zero
        ctx->r16 = 0 | 0;
            goto L_802C5AE4;
    }
    // 0x802C5AC0: or          $s0, $zero, $zero
    ctx->r16 = 0 | 0;
    // 0x802C5AC4: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x802C5AC8: beq         $v1, $at, L_802C5B40
    if (ctx->r3 == ctx->r1) {
        // 0x802C5ACC: lui         $v0, 0x802C
        ctx->r2 = S32(0X802C << 16);
            goto L_802C5B40;
    }
    // 0x802C5ACC: lui         $v0, 0x802C
    ctx->r2 = S32(0X802C << 16);
    // 0x802C5AD0: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x802C5AD4: beql        $v1, $at, L_802C5C10
    if (ctx->r3 == ctx->r1) {
        // 0x802C5AD8: addiu       $s0, $zero, 0x1
        ctx->r16 = ADD32(0, 0X1);
            goto L_802C5C10;
    }
    goto skip_5;
    // 0x802C5AD8: addiu       $s0, $zero, 0x1
    ctx->r16 = ADD32(0, 0X1);
    skip_5:
    // 0x802C5ADC: b           L_802C5C10
    // 0x802C5AE0: nop

        goto L_802C5C10;
    // 0x802C5AE0: nop

L_802C5AE4:
    // 0x802C5AE4: lw          $t6, 0xC($s4)
    ctx->r14 = MEM_W(ctx->r20, 0XC);
    // 0x802C5AE8: lw          $v0, 0x4($s4)
    ctx->r2 = MEM_W(ctx->r20, 0X4);
    // 0x802C5AEC: addiu       $t7, $t6, -0x2
    ctx->r15 = ADD32(ctx->r14, -0X2);
    // 0x802C5AF0: bne         $a0, $v0, L_802C5B18
    if (ctx->r4 != ctx->r2) {
        // 0x802C5AF4: sw          $t7, 0xC($s4)
        MEM_W(0XC, ctx->r20) = ctx->r15;
            goto L_802C5B18;
    }
    // 0x802C5AF4: sw          $t7, 0xC($s4)
    MEM_W(0XC, ctx->r20) = ctx->r15;
    // 0x802C5AF8: slti        $at, $t7, 0x1A
    ctx->r1 = SIGNED(ctx->r15) < 0X1A ? 1 : 0;
    // 0x802C5AFC: beq         $at, $zero, L_802C5B30
    if (ctx->r1 == 0) {
        // 0x802C5B00: addiu       $t9, $zero, 0x2
        ctx->r25 = ADD32(0, 0X2);
            goto L_802C5B30;
    }
    // 0x802C5B00: addiu       $t9, $zero, 0x2
    ctx->r25 = ADD32(0, 0X2);
    // 0x802C5B04: addiu       $t4, $zero, 0x19
    ctx->r12 = ADD32(0, 0X19);
    // 0x802C5B08: sw          $t9, 0x0($s4)
    MEM_W(0X0, ctx->r20) = ctx->r25;
    // 0x802C5B0C: sw          $t4, 0xC($s4)
    MEM_W(0XC, ctx->r20) = ctx->r12;
    // 0x802C5B10: b           L_802C5B30
    // 0x802C5B14: lw          $v0, 0x4($s4)
    ctx->r2 = MEM_W(ctx->r20, 0X4);
        goto L_802C5B30;
    // 0x802C5B14: lw          $v0, 0x4($s4)
    ctx->r2 = MEM_W(ctx->r20, 0X4);
L_802C5B18:
    // 0x802C5B18: lw          $t5, 0xC($s4)
    ctx->r13 = MEM_W(ctx->r20, 0XC);
    // 0x802C5B1C: slti        $at, $t5, -0xC
    ctx->r1 = SIGNED(ctx->r13) < -0XC ? 1 : 0;
    { extern int32_t wr64_ending_panel_retire(uint8_t*, uint32_t, int32_t); ctx->r1 = S32(wr64_ending_panel_retire(rdram, (uint32_t)ctx->r20, (int32_t)ctx->r1)); }
    // 0x802C5B20: beq         $at, $zero, L_802C5B30
    if (ctx->r1 == 0) {
        // 0x802C5B24: nop
    
            goto L_802C5B30;
    }
    // 0x802C5B24: nop

    // 0x802C5B28: sw          $zero, 0x0($s4)
    MEM_W(0X0, ctx->r20) = 0;
    // 0x802C5B2C: lw          $v0, 0x4($s4)
    ctx->r2 = MEM_W(ctx->r20, 0X4);
L_802C5B30:
    // 0x802C5B30: bne         $a0, $v0, L_802C5C10
    if (ctx->r4 != ctx->r2) {
        // 0x802C5B34: nop
    
            goto L_802C5C10;
    }
    // 0x802C5B34: nop

    // 0x802C5B38: b           L_802C5C10
    // 0x802C5B3C: addiu       $s0, $zero, 0x1
    ctx->r16 = ADD32(0, 0X1);
        goto L_802C5C10;
    // 0x802C5B3C: addiu       $s0, $zero, 0x1
    ctx->r16 = ADD32(0, 0X1);
L_802C5B40:
    // 0x802C5B40: lw          $v0, 0x6DF0($v0)
    ctx->r2 = MEM_W(ctx->r2, 0X6DF0);
    // 0x802C5B44: addiu       $s0, $zero, 0x1
    ctx->r16 = ADD32(0, 0X1);
    // 0x802C5B48: slti        $at, $v0, 0x14
    ctx->r1 = SIGNED(ctx->r2) < 0X14 ? 1 : 0;
    // 0x802C5B4C: beq         $at, $zero, L_802C5B64
    if (ctx->r1 == 0) {
        // 0x802C5B50: addiu       $t6, $v0, 0x1
        ctx->r14 = ADD32(ctx->r2, 0X1);
            goto L_802C5B64;
    }
    // 0x802C5B50: addiu       $t6, $v0, 0x1
    ctx->r14 = ADD32(ctx->r2, 0X1);
    // 0x802C5B54: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C5B58: sw          $t6, 0x6DF0($at)
    MEM_W(0X6DF0, ctx->r1) = ctx->r14;
    // 0x802C5B5C: lui         $v0, 0x802C
    ctx->r2 = S32(0X802C << 16);
    // 0x802C5B60: lw          $v0, 0x6DF0($v0)
    ctx->r2 = MEM_W(ctx->r2, 0X6DF0);
L_802C5B64:
    // 0x802C5B64: slti        $at, $v0, 0xB
    ctx->r1 = SIGNED(ctx->r2) < 0XB ? 1 : 0;
    // 0x802C5B68: bne         $at, $zero, L_802C5C10
    if (ctx->r1 != 0) {
        // 0x802C5B6C: nop
    
            goto L_802C5C10;
    }
    // 0x802C5B6C: nop

    // 0x802C5B70: lw          $t7, 0x0($fp)
    ctx->r15 = MEM_W(ctx->r30, 0X0);
    // 0x802C5B74: addiu       $at, $zero, 0x14
    ctx->r1 = ADD32(0, 0X14);
    // 0x802C5B78: addiu       $t9, $zero, 0x3
    ctx->r25 = ADD32(0, 0X3);
    // 0x802C5B7C: addiu       $v0, $t7, 0x1
    ctx->r2 = ADD32(ctx->r15, 0X1);
    // 0x802C5B80: bne         $v0, $at, L_802C5BBC
    if (ctx->r2 != ctx->r1) {
        // 0x802C5B84: sw          $v0, 0x0($fp)
        MEM_W(0X0, ctx->r30) = ctx->r2;
            goto L_802C5BBC;
    }
    // 0x802C5B84: sw          $v0, 0x0($fp)
    MEM_W(0X0, ctx->r30) = ctx->r2;
    // 0x802C5B88: sw          $t9, 0x0($s4)
    MEM_W(0X0, ctx->r20) = ctx->r25;
    // 0x802C5B8C: addiu       $t4, $zero, 0xFF
    ctx->r12 = ADD32(0, 0XFF);
    // 0x802C5B90: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C5B94: sw          $t4, 0x6DD4($at)
    MEM_W(0X6DD4, ctx->r1) = ctx->r12;
    // 0x802C5B98: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C5B9C: addiu       $t5, $zero, 0xAA
    ctx->r13 = ADD32(0, 0XAA);
    // 0x802C5BA0: sw          $t5, 0x6DD8($at)
    MEM_W(0X6DD8, ctx->r1) = ctx->r13;
    // 0x802C5BA4: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C5BA8: addiu       $t6, $zero, 0x1
    ctx->r14 = ADD32(0, 0X1);
    // 0x802C5BAC: jal         0x800C489C
    // 0x802C5BB0: sw          $t6, 0x6DF4($at)
    MEM_W(0X6DF4, ctx->r1) = ctx->r14;
    func_800C489C(rdram, ctx);
        goto after_7;
    // 0x802C5BB0: sw          $t6, 0x6DF4($at)
    MEM_W(0X6DF4, ctx->r1) = ctx->r14;
    after_7:
    // 0x802C5BB4: b           L_802C5C10
    // 0x802C5BB8: addiu       $a0, $zero, 0xA
    ctx->r4 = ADD32(0, 0XA);
        goto L_802C5C10;
    // 0x802C5BB8: addiu       $a0, $zero, 0xA
    ctx->r4 = ADD32(0, 0XA);
L_802C5BBC:
    // 0x802C5BBC: sll         $t7, $v0, 2
    ctx->r15 = S32(ctx->r2 << 2);
    // 0x802C5BC0: addu        $t7, $t7, $v0
    ctx->r15 = ADD32(ctx->r15, ctx->r2);
    // 0x802C5BC4: sll         $t7, $t7, 2
    ctx->r15 = S32(ctx->r15 << 2);
    // 0x802C5BC8: addu        $t7, $t7, $v0
    ctx->r15 = ADD32(ctx->r15, ctx->r2);
    // 0x802C5BCC: sll         $t7, $t7, 2
    ctx->r15 = S32(ctx->r15 << 2);
    // 0x802C5BD0: addu        $t7, $t7, $v0
    ctx->r15 = ADD32(ctx->r15, ctx->r2);
    // 0x802C5BD4: sll         $t7, $t7, 1
    ctx->r15 = S32(ctx->r15 << 1);
    // 0x802C5BD8: addiu       $at, $zero, 0x14
    ctx->r1 = ADD32(0, 0X14);
    // 0x802C5BDC: div         $zero, $t7, $at
    lo = S32(S64(S32(ctx->r15)) / S64(S32(ctx->r1))); hi = S32(S64(S32(ctx->r15)) % S64(S32(ctx->r1)));
    // 0x802C5BE0: mflo        $t8
    ctx->r24 = lo;
    // 0x802C5BE4: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C5BE8: sw          $t8, 0x6DD8($at)
    MEM_W(0X6DD8, ctx->r1) = ctx->r24;
    // 0x802C5BEC: sll         $t9, $v0, 8
    ctx->r25 = S32(ctx->r2 << 8);
    // 0x802C5BF0: subu        $t9, $t9, $v0
    ctx->r25 = SUB32(ctx->r25, ctx->r2);
    // 0x802C5BF4: addiu       $at, $zero, 0x14
    ctx->r1 = ADD32(0, 0X14);
    // 0x802C5BF8: div         $zero, $t9, $at
    lo = S32(S64(S32(ctx->r25)) / S64(S32(ctx->r1))); hi = S32(S64(S32(ctx->r25)) % S64(S32(ctx->r1)));
    // 0x802C5BFC: mflo        $t4
    ctx->r12 = lo;
    // 0x802C5C00: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C5C04: b           L_802C5C10
    // 0x802C5C08: sw          $t4, 0x6DD4($at)
    MEM_W(0X6DD4, ctx->r1) = ctx->r12;
        goto L_802C5C10;
    // 0x802C5C08: sw          $t4, 0x6DD4($at)
    MEM_W(0X6DD4, ctx->r1) = ctx->r12;
    // 0x802C5C0C: addiu       $s0, $zero, 0x1
    ctx->r16 = ADD32(0, 0X1);
L_802C5C10:
    // 0x802C5C10: beq         $s0, $zero, L_802C5CA4
    if (ctx->r16 == 0) {
        // 0x802C5C14: or          $s2, $zero, $zero
        ctx->r18 = 0 | 0;
            goto L_802C5CA4;
    }
    // 0x802C5C14: or          $s2, $zero, $zero
    ctx->r18 = 0 | 0;
    // 0x802C5C18: or          $s0, $zero, $zero
    ctx->r16 = 0 | 0;
    // 0x802C5C1C: or          $s1, $zero, $zero
    ctx->r17 = 0 | 0;
L_802C5C20:
    // 0x802C5C20: lw          $t5, 0x0($s3)
    ctx->r13 = MEM_W(ctx->r19, 0X0);
    // 0x802C5C24: or          $a0, $s5, $zero
    ctx->r4 = ctx->r21 | 0;
    // 0x802C5C28: addu        $a1, $t5, $s2
    ctx->r5 = ADD32(ctx->r13, ctx->r18);
    // 0x802C5C2C: jal         0x80047EE0
    // 0x802C5C30: addiu       $a1, $a1, 0xA80
    ctx->r5 = ADD32(ctx->r5, 0XA80);
    SysUtils_MtxFToMtx(rdram, ctx);
        goto after_8;
    // 0x802C5C30: addiu       $a1, $a1, 0xA80
    ctx->r5 = ADD32(ctx->r5, 0XA80);
    after_8:
    // 0x802C5C34: lw          $t6, 0x0($s3)
    ctx->r14 = MEM_W(ctx->r19, 0X0);
    // 0x802C5C38: lw          $at, 0x0($s6)
    ctx->r1 = MEM_W(ctx->r22, 0X0);
    // 0x802C5C3C: addiu       $s2, $s2, 0x40
    ctx->r18 = ADD32(ctx->r18, 0X40);
    // 0x802C5C40: addu        $t7, $t6, $s0
    ctx->r15 = ADD32(ctx->r14, ctx->r16);
    // 0x802C5C44: sw          $at, 0x1280($t7)
    MEM_W(0X1280, ctx->r15) = ctx->r1;
    // 0x802C5C48: lw          $t9, 0x4($s6)
    ctx->r25 = MEM_W(ctx->r22, 0X4);
    // 0x802C5C4C: sw          $t9, 0x1284($t7)
    MEM_W(0X1284, ctx->r15) = ctx->r25;
    // 0x802C5C50: lw          $at, 0x8($s6)
    ctx->r1 = MEM_W(ctx->r22, 0X8);
    // 0x802C5C54: sw          $at, 0x1288($t7)
    MEM_W(0X1288, ctx->r15) = ctx->r1;
    // 0x802C5C58: lw          $t9, 0xC($s6)
    ctx->r25 = MEM_W(ctx->r22, 0XC);
    // 0x802C5C5C: sw          $t9, 0x128C($t7)
    MEM_W(0X128C, ctx->r15) = ctx->r25;
    // 0x802C5C60: lw          $t4, 0x8($s4)
    ctx->r12 = MEM_W(ctx->r20, 0X8);
    // 0x802C5C64: lw          $t8, 0x0($s3)
    ctx->r24 = MEM_W(ctx->r19, 0X0);
    // 0x802C5C68: addiu       $t5, $t4, 0x3A
    ctx->r13 = ADD32(ctx->r12, 0X3A);
    // 0x802C5C6C: sll         $t6, $t5, 2
    ctx->r14 = S32(ctx->r13 << 2);
    // 0x802C5C70: addu        $t7, $t8, $s0
    ctx->r15 = ADD32(ctx->r24, ctx->r16);
    // 0x802C5C74: sh          $t6, 0x1288($t7)
    MEM_H(0X1288, ctx->r15) = ctx->r14;
    // 0x802C5C78: lw          $t9, 0xC($s4)
    ctx->r25 = MEM_W(ctx->r20, 0XC);
    // 0x802C5C7C: lw          $t6, 0x0($s3)
    ctx->r14 = MEM_W(ctx->r19, 0X0);
    // 0x802C5C80: addu        $t4, $t9, $s1
    ctx->r12 = ADD32(ctx->r25, ctx->r17);
    // 0x802C5C84: addiu       $t5, $t4, 0x43
    ctx->r13 = ADD32(ctx->r12, 0X43);
    // 0x802C5C88: addiu       $s1, $s1, 0x20
    ctx->r17 = ADD32(ctx->r17, 0X20);
    // 0x802C5C8C: sll         $t8, $t5, 2
    ctx->r24 = S32(ctx->r13 << 2);
    // 0x802C5C90: addu        $t7, $t6, $s0
    ctx->r15 = ADD32(ctx->r14, ctx->r16);
    // 0x802C5C94: addiu       $s0, $s0, 0x10
    ctx->r16 = ADD32(ctx->r16, 0X10);
    // 0x802C5C98: bne         $s1, $s7, L_802C5C20
    if (ctx->r17 != ctx->r23) {
        // 0x802C5C9C: sh          $t8, 0x128A($t7)
        MEM_H(0X128A, ctx->r15) = ctx->r24;
            goto L_802C5C20;
    }
    // 0x802C5C9C: sh          $t8, 0x128A($t7)
    MEM_H(0X128A, ctx->r15) = ctx->r24;
    // 0x802C5CA0: addiu       $a0, $zero, 0xA
    ctx->r4 = ADD32(0, 0XA);
L_802C5CA4:
    // 0x802C5CA4: lw          $t9, 0x1D4($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X1D4);
L_802C5CA8:
    // 0x802C5CA8: addiu       $s4, $s4, 0x10
    ctx->r20 = ADD32(ctx->r20, 0X10);
    // 0x802C5CAC: addiu       $t4, $t9, 0x1
    ctx->r12 = ADD32(ctx->r25, 0X1);
    // 0x802C5CB0: bne         $t4, $a0, L_802C5AAC
    if (ctx->r12 != ctx->r4) {
        // 0x802C5CB4: sw          $t4, 0x1D4($sp)
        MEM_W(0X1D4, ctx->r29) = ctx->r12;
            goto L_802C5AAC;
    }
    // 0x802C5CB4: sw          $t4, 0x1D4($sp)
    MEM_W(0X1D4, ctx->r29) = ctx->r12;
    // 0x802C5CB8: lw          $ra, 0x5C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X5C);
    // 0x802C5CBC: lw          $s0, 0x38($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X38);
    // 0x802C5CC0: lw          $s1, 0x3C($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X3C);
    // 0x802C5CC4: lw          $s2, 0x40($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X40);
    // 0x802C5CC8: lw          $s3, 0x44($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X44);
    // 0x802C5CCC: lw          $s4, 0x48($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X48);
    // 0x802C5CD0: lw          $s5, 0x4C($sp)
    ctx->r21 = MEM_W(ctx->r29, 0X4C);
    // 0x802C5CD4: lw          $s6, 0x50($sp)
    ctx->r22 = MEM_W(ctx->r29, 0X50);
    // 0x802C5CD8: lw          $s7, 0x54($sp)
    ctx->r23 = MEM_W(ctx->r29, 0X54);
    // 0x802C5CDC: lw          $fp, 0x58($sp)
    ctx->r30 = MEM_W(ctx->r29, 0X58);
    // 0x802C5CE0: jr          $ra
    // 0x802C5CE4: addiu       $sp, $sp, 0x1D8
    ctx->r29 = ADD32(ctx->r29, 0X1D8);
    return;
    // 0x802C5CE4: addiu       $sp, $sp, 0x1D8
    ctx->r29 = ADD32(ctx->r29, 0X1D8);
;}
RECOMP_FUNC void func_i15_802C5CE8(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    { extern void wr64_ending_hud_spawn(void); wr64_ending_hud_spawn(); }
    // 0x802C5CE8: lui         $v1, 0x802C
    ctx->r3 = S32(0X802C << 16);
    // 0x802C5CEC: lui         $a0, 0x802C
    ctx->r4 = S32(0X802C << 16);
    // 0x802C5CF0: lui         $v0, 0x802C
    ctx->r2 = S32(0X802C << 16);
    // 0x802C5CF4: addiu       $v0, $v0, 0x6D8C
    ctx->r2 = ADD32(ctx->r2, 0X6D8C);
    // 0x802C5CF8: addiu       $a0, $a0, 0x6F20
    ctx->r4 = ADD32(ctx->r4, 0X6F20);
    // 0x802C5CFC: addiu       $v1, $v1, 0x6E80
    ctx->r3 = ADD32(ctx->r3, 0X6E80);
L_802C5D00:
    // 0x802C5D00: lw          $at, 0x0($v0)
    ctx->r1 = MEM_W(ctx->r2, 0X0);
    // 0x802C5D04: lw          $t8, 0x4($v0)
    ctx->r24 = MEM_W(ctx->r2, 0X4);
    // 0x802C5D08: addiu       $v1, $v1, 0x10
    ctx->r3 = ADD32(ctx->r3, 0X10);
    // 0x802C5D0C: sw          $at, -0x10($v1)
    MEM_W(-0X10, ctx->r3) = ctx->r1;
    // 0x802C5D10: lw          $at, 0x8($v0)
    ctx->r1 = MEM_W(ctx->r2, 0X8);
    // 0x802C5D14: sw          $t8, -0xC($v1)
    MEM_W(-0XC, ctx->r3) = ctx->r24;
    // 0x802C5D18: lw          $t8, 0xC($v0)
    ctx->r24 = MEM_W(ctx->r2, 0XC);
    // 0x802C5D1C: sw          $at, -0x8($v1)
    MEM_W(-0X8, ctx->r3) = ctx->r1;
    // 0x802C5D20: sltu        $at, $v1, $a0
    ctx->r1 = ctx->r3 < ctx->r4 ? 1 : 0;
    // 0x802C5D24: bne         $at, $zero, L_802C5D00
    if (ctx->r1 != 0) {
        // 0x802C5D28: sw          $t8, -0x4($v1)
        MEM_W(-0X4, ctx->r3) = ctx->r24;
            goto L_802C5D00;
    }
    // 0x802C5D28: sw          $t8, -0x4($v1)
    MEM_W(-0X4, ctx->r3) = ctx->r24;
    // 0x802C5D2C: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x802C5D30: lw          $v0, -0x4CC8($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X4CC8);
    // 0x802C5D34: lui         $t2, 0x802C
    ctx->r10 = S32(0X802C << 16);
    // 0x802C5D38: lui         $a0, 0x802C
    ctx->r4 = S32(0X802C << 16);
    // 0x802C5D3C: sll         $t9, $v0, 2
    ctx->r25 = S32(ctx->r2 << 2);
    // 0x802C5D40: addu        $t2, $t2, $t9
    ctx->r10 = ADD32(ctx->r10, ctx->r25);
    // 0x802C5D44: lw          $t2, 0x6D54($t2)
    ctx->r10 = MEM_W(ctx->r10, 0X6D54);
    // 0x802C5D48: addiu       $a0, $a0, 0x6E7C
    ctx->r4 = ADD32(ctx->r4, 0X6E7C);
    // 0x802C5D4C: lui         $t3, 0x800D
    ctx->r11 = S32(0X800D << 16);
    // 0x802C5D50: sw          $t2, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r10;
    // 0x802C5D54: lw          $t3, 0x48DC($t3)
    ctx->r11 = MEM_W(ctx->r11, 0X48DC);
    // 0x802C5D58: lui         $v1, 0x801C
    ctx->r3 = S32(0X801C << 16);
    // 0x802C5D5C: addiu       $a1, $zero, 0x3
    ctx->r5 = ADD32(0, 0X3);
    // 0x802C5D60: sll         $t4, $t3, 3
    ctx->r12 = S32(ctx->r11 << 3);
    // 0x802C5D64: subu        $t4, $t4, $t3
    ctx->r12 = SUB32(ctx->r12, ctx->r11);
    // 0x802C5D68: sll         $t4, $t4, 4
    ctx->r12 = S32(ctx->r12 << 4);
    // 0x802C5D6C: subu        $t4, $t4, $t3
    ctx->r12 = SUB32(ctx->r12, ctx->r11);
    // 0x802C5D70: sll         $t4, $t4, 3
    ctx->r12 = S32(ctx->r12 << 3);
    // 0x802C5D74: addu        $v1, $v1, $t4
    ctx->r3 = ADD32(ctx->r3, ctx->r12);
    // 0x802C5D78: lw          $v1, 0x2C70($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X2C70);
    // 0x802C5D7C: addiu       $t5, $zero, 0x6
    ctx->r13 = ADD32(0, 0X6);
    // 0x802C5D80: addiu       $t1, $zero, 0x4
    ctx->r9 = ADD32(0, 0X4);
    // 0x802C5D84: bne         $a1, $v1, L_802C5D9C
    if (ctx->r5 != ctx->r3) {
        // 0x802C5D88: addiu       $t0, $zero, 0x1
        ctx->r8 = ADD32(0, 0X1);
            goto L_802C5D9C;
    }
    // 0x802C5D88: addiu       $t0, $zero, 0x1
    ctx->r8 = ADD32(0, 0X1);
    // 0x802C5D8C: lui         $v1, 0x802C
    ctx->r3 = S32(0X802C << 16);
    // 0x802C5D90: addiu       $v1, $v1, 0x6F44
    ctx->r3 = ADD32(ctx->r3, 0X6F44);
    // 0x802C5D94: b           L_802C5E44
    // 0x802C5D98: sw          $t5, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r13;
        goto L_802C5E44;
    // 0x802C5D98: sw          $t5, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r13;
L_802C5D9C:
    // 0x802C5D9C: addiu       $a2, $zero, 0x2
    ctx->r6 = ADD32(0, 0X2);
    // 0x802C5DA0: bne         $a2, $v0, L_802C5DF8
    if (ctx->r6 != ctx->r2) {
        // 0x802C5DA4: nop
    
            goto L_802C5DF8;
    }
    // 0x802C5DA4: nop

    // 0x802C5DA8: bne         $v1, $zero, L_802C5DC4
    if (ctx->r3 != 0) {
        // 0x802C5DAC: addiu       $t1, $zero, 0x4
        ctx->r9 = ADD32(0, 0X4);
            goto L_802C5DC4;
    }
    // 0x802C5DAC: addiu       $t1, $zero, 0x4
    ctx->r9 = ADD32(0, 0X4);
    // 0x802C5DB0: lui         $v1, 0x802C
    ctx->r3 = S32(0X802C << 16);
    // 0x802C5DB4: addiu       $v1, $v1, 0x6F44
    ctx->r3 = ADD32(ctx->r3, 0X6F44);
    // 0x802C5DB8: sw          $a1, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r5;
    // 0x802C5DBC: b           L_802C5E44
    // 0x802C5DC0: addiu       $t0, $zero, 0x1
    ctx->r8 = ADD32(0, 0X1);
        goto L_802C5E44;
    // 0x802C5DC0: addiu       $t0, $zero, 0x1
    ctx->r8 = ADD32(0, 0X1);
L_802C5DC4:
    // 0x802C5DC4: addiu       $t0, $zero, 0x1
    ctx->r8 = ADD32(0, 0X1);
    // 0x802C5DC8: bne         $t0, $v1, L_802C5DE0
    if (ctx->r8 != ctx->r3) {
        // 0x802C5DCC: lui         $v1, 0x802C
        ctx->r3 = S32(0X802C << 16);
            goto L_802C5DE0;
    }
    // 0x802C5DCC: lui         $v1, 0x802C
    ctx->r3 = S32(0X802C << 16);
    // 0x802C5DD0: addiu       $v1, $v1, 0x6F44
    ctx->r3 = ADD32(ctx->r3, 0X6F44);
    // 0x802C5DD4: addiu       $t1, $zero, 0x4
    ctx->r9 = ADD32(0, 0X4);
    // 0x802C5DD8: b           L_802C5E44
    // 0x802C5DDC: sw          $t1, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r9;
        goto L_802C5E44;
    // 0x802C5DDC: sw          $t1, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r9;
L_802C5DE0:
    // 0x802C5DE0: lui         $v1, 0x802C
    ctx->r3 = S32(0X802C << 16);
    // 0x802C5DE4: addiu       $v1, $v1, 0x6F44
    ctx->r3 = ADD32(ctx->r3, 0X6F44);
    // 0x802C5DE8: addiu       $t7, $zero, 0x5
    ctx->r15 = ADD32(0, 0X5);
    // 0x802C5DEC: sw          $t7, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r15;
    // 0x802C5DF0: b           L_802C5E44
    // 0x802C5DF4: addiu       $t1, $zero, 0x4
    ctx->r9 = ADD32(0, 0X4);
        goto L_802C5E44;
    // 0x802C5DF4: addiu       $t1, $zero, 0x4
    ctx->r9 = ADD32(0, 0X4);
L_802C5DF8:
    // 0x802C5DF8: bnel        $v1, $zero, L_802C5E1C
    if (ctx->r3 != 0) {
        // 0x802C5DFC: addiu       $t0, $zero, 0x1
        ctx->r8 = ADD32(0, 0X1);
            goto L_802C5E1C;
    }
    goto skip_0;
    // 0x802C5DFC: addiu       $t0, $zero, 0x1
    ctx->r8 = ADD32(0, 0X1);
    skip_0:
    // 0x802C5E00: lui         $v1, 0x802C
    ctx->r3 = S32(0X802C << 16);
    // 0x802C5E04: addiu       $v1, $v1, 0x6F44
    ctx->r3 = ADD32(ctx->r3, 0X6F44);
    // 0x802C5E08: sw          $zero, 0x0($v1)
    MEM_W(0X0, ctx->r3) = 0;
    // 0x802C5E0C: addiu       $t1, $zero, 0x4
    ctx->r9 = ADD32(0, 0X4);
    // 0x802C5E10: b           L_802C5E44
    // 0x802C5E14: addiu       $t0, $zero, 0x1
    ctx->r8 = ADD32(0, 0X1);
        goto L_802C5E44;
    // 0x802C5E14: addiu       $t0, $zero, 0x1
    ctx->r8 = ADD32(0, 0X1);
    // 0x802C5E18: addiu       $t0, $zero, 0x1
    ctx->r8 = ADD32(0, 0X1);
L_802C5E1C:
    // 0x802C5E1C: bne         $t0, $v1, L_802C5E34
    if (ctx->r8 != ctx->r3) {
        // 0x802C5E20: lui         $v1, 0x802C
        ctx->r3 = S32(0X802C << 16);
            goto L_802C5E34;
    }
    // 0x802C5E20: lui         $v1, 0x802C
    ctx->r3 = S32(0X802C << 16);
    // 0x802C5E24: addiu       $v1, $v1, 0x6F44
    ctx->r3 = ADD32(ctx->r3, 0X6F44);
    // 0x802C5E28: sw          $t0, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r8;
    // 0x802C5E2C: b           L_802C5E44
    // 0x802C5E30: addiu       $t1, $zero, 0x4
    ctx->r9 = ADD32(0, 0X4);
        goto L_802C5E44;
    // 0x802C5E30: addiu       $t1, $zero, 0x4
    ctx->r9 = ADD32(0, 0X4);
L_802C5E34:
    // 0x802C5E34: lui         $v1, 0x802C
    ctx->r3 = S32(0X802C << 16);
    // 0x802C5E38: addiu       $v1, $v1, 0x6F44
    ctx->r3 = ADD32(ctx->r3, 0X6F44);
    // 0x802C5E3C: sw          $a2, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r6;
    // 0x802C5E40: addiu       $t1, $zero, 0x4
    ctx->r9 = ADD32(0, 0X4);
L_802C5E44:
    // 0x802C5E44: lw          $t6, 0x0($v1)
    ctx->r14 = MEM_W(ctx->r3, 0X0);
    // 0x802C5E48: lui         $t9, 0x802C
    ctx->r25 = S32(0X802C << 16);
    // 0x802C5E4C: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C5E50: sll         $t8, $t6, 2
    ctx->r24 = S32(ctx->r14 << 2);
    // 0x802C5E54: addu        $t9, $t9, $t8
    ctx->r25 = ADD32(ctx->r25, ctx->r24);
    // 0x802C5E58: lw          $t9, 0x6D70($t9)
    ctx->r25 = MEM_W(ctx->r25, 0X6D70);
    // 0x802C5E5C: bne         $v0, $zero, L_802C5E70
    if (ctx->r2 != 0) {
        // 0x802C5E60: sw          $t9, 0x6D6C($at)
        MEM_W(0X6D6C, ctx->r1) = ctx->r25;
            goto L_802C5E70;
    }
    // 0x802C5E60: sw          $t9, 0x6D6C($at)
    MEM_W(0X6D6C, ctx->r1) = ctx->r25;
    // 0x802C5E64: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C5E68: b           L_802C5E78
    // 0x802C5E6C: sw          $t0, 0x6D68($at)
    MEM_W(0X6D68, ctx->r1) = ctx->r8;
        goto L_802C5E78;
    // 0x802C5E6C: sw          $t0, 0x6D68($at)
    MEM_W(0X6D68, ctx->r1) = ctx->r8;
L_802C5E70:
    // 0x802C5E70: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C5E74: sw          $zero, 0x6D68($at)
    MEM_W(0X6D68, ctx->r1) = 0;
L_802C5E78:
    // 0x802C5E78: lw          $v1, 0x0($a0)
    ctx->r3 = MEM_W(ctx->r4, 0X0);
    // 0x802C5E7C: addiu       $v1, $v1, 0x1
    ctx->r3 = ADD32(ctx->r3, 0X1);
    // 0x802C5E80: blez        $v1, L_802C5ED8
    if (SIGNED(ctx->r3) <= 0) {
        // 0x802C5E84: lui         $t2, 0x802C
        ctx->r10 = S32(0X802C << 16);
            goto L_802C5ED8;
    }
    // 0x802C5E84: lui         $t2, 0x802C
    ctx->r10 = S32(0X802C << 16);
    // 0x802C5E88: addiu       $a2, $t2, 0x6F20
    ctx->r6 = ADD32(ctx->r10, 0X6F20);
    // 0x802C5E8C: lui         $a0, 0x801D
    ctx->r4 = S32(0X801D << 16);
    // 0x802C5E90: sll         $t3, $v1, 2
    ctx->r11 = S32(ctx->r3 << 2);
    // 0x802C5E94: addu        $a3, $t3, $a2
    ctx->r7 = ADD32(ctx->r11, ctx->r6);
    // 0x802C5E98: addiu       $a0, $a0, -0x4CB0
    ctx->r4 = ADD32(ctx->r4, -0X4CB0);
L_802C5E9C:
    // 0x802C5E9C: lui         $v1, 0x800F
    ctx->r3 = S32(0X800F << 16);
    // 0x802C5EA0: addiu       $v1, $v1, -0x5450
    ctx->r3 = ADD32(ctx->r3, -0X5450);
    // 0x802C5EA4: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    // 0x802C5EA8: lw          $a1, 0x0($a0)
    ctx->r5 = MEM_W(ctx->r4, 0X0);
L_802C5EAC:
    // 0x802C5EAC: lh          $t4, 0x0($v1)
    ctx->r12 = MEM_H(ctx->r3, 0X0);
    // 0x802C5EB0: beql        $t4, $a1, L_802C5EC8
    if (ctx->r12 == ctx->r5) {
        // 0x802C5EB4: addiu       $a2, $a2, 0x4
        ctx->r6 = ADD32(ctx->r6, 0X4);
            goto L_802C5EC8;
    }
    goto skip_1;
    // 0x802C5EB4: addiu       $a2, $a2, 0x4
    ctx->r6 = ADD32(ctx->r6, 0X4);
    skip_1:
    // 0x802C5EB8: addiu       $v0, $v0, 0x1
    ctx->r2 = ADD32(ctx->r2, 0X1);
    // 0x802C5EBC: bne         $v0, $t1, L_802C5EAC
    if (ctx->r2 != ctx->r9) {
        // 0x802C5EC0: addiu       $v1, $v1, 0x2
        ctx->r3 = ADD32(ctx->r3, 0X2);
            goto L_802C5EAC;
    }
    // 0x802C5EC0: addiu       $v1, $v1, 0x2
    ctx->r3 = ADD32(ctx->r3, 0X2);
    // 0x802C5EC4: addiu       $a2, $a2, 0x4
    ctx->r6 = ADD32(ctx->r6, 0X4);
L_802C5EC8:
    // 0x802C5EC8: sltu        $at, $a2, $a3
    ctx->r1 = ctx->r6 < ctx->r7 ? 1 : 0;
    // 0x802C5ECC: addiu       $a0, $a0, 0x10
    ctx->r4 = ADD32(ctx->r4, 0X10);
    // 0x802C5ED0: bne         $at, $zero, L_802C5E9C
    if (ctx->r1 != 0) {
        // 0x802C5ED4: sw          $v0, -0x4($a2)
        MEM_W(-0X4, ctx->r6) = ctx->r2;
            goto L_802C5E9C;
    }
    // 0x802C5ED4: sw          $v0, -0x4($a2)
    MEM_W(-0X4, ctx->r6) = ctx->r2;
L_802C5ED8:
    // 0x802C5ED8: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x802C5EDC: jr          $ra
    // 0x802C5EE0: sw          $t0, -0x55F8($at)
    MEM_W(-0X55F8, ctx->r1) = ctx->r8;
    return;
    // 0x802C5EE0: sw          $t0, -0x55F8($at)
    MEM_W(-0X55F8, ctx->r1) = ctx->r8;
;}
RECOMP_FUNC void func_i15_802C5EE4(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C5EE4: lui         $a1, 0x802C
    ctx->r5 = S32(0X802C << 16);
    // 0x802C5EE8: addiu       $a1, $a1, 0x6E80
    ctx->r5 = ADD32(ctx->r5, 0X6E80);
    // 0x802C5EEC: or          $v1, $a1, $zero
    ctx->r3 = ctx->r5 | 0;
    // 0x802C5EF0: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    // 0x802C5EF4: addiu       $a2, $zero, 0xA
    ctx->r6 = ADD32(0, 0XA);
L_802C5EF8:
    // 0x802C5EF8: lw          $t6, 0x0($v1)
    ctx->r14 = MEM_W(ctx->r3, 0X0);
    // 0x802C5EFC: beq         $t6, $zero, L_802C5F10
    if (ctx->r14 == 0) {
        // 0x802C5F00: nop
    
            goto L_802C5F10;
    }
    // 0x802C5F00: nop

    // 0x802C5F04: addiu       $v0, $v0, 0x1
    ctx->r2 = ADD32(ctx->r2, 0X1);
    // 0x802C5F08: bne         $v0, $a2, L_802C5EF8
    if (ctx->r2 != ctx->r6) {
        // 0x802C5F0C: addiu       $v1, $v1, 0x10
        ctx->r3 = ADD32(ctx->r3, 0X10);
            goto L_802C5EF8;
    }
    // 0x802C5F0C: addiu       $v1, $v1, 0x10
    ctx->r3 = ADD32(ctx->r3, 0X10);
L_802C5F10:
    // 0x802C5F10: beq         $v0, $a2, L_802C5F48
    if (ctx->r2 == ctx->r6) {
        // 0x802C5F14: sll         $t7, $v0, 4
        ctx->r15 = S32(ctx->r2 << 4);
            goto L_802C5F48;
    }
    // 0x802C5F14: sll         $t7, $v0, 4
    ctx->r15 = S32(ctx->r2 << 4);
    // 0x802C5F18: addu        $v1, $a1, $t7
    ctx->r3 = ADD32(ctx->r5, ctx->r15);
    // 0x802C5F1C: addiu       $t8, $zero, 0x1
    ctx->r24 = ADD32(0, 0X1);
    // 0x802C5F20: addiu       $t9, $zero, 0xEB
    ctx->r25 = ADD32(0, 0XEB);
    // 0x802C5F24: sw          $t8, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r24;
    // 0x802C5F28: sw          $a0, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r4;
    // 0x802C5F2C: beq         $a0, $a2, L_802C5F40
    if (ctx->r4 == ctx->r6) {
        // 0x802C5F30: sw          $t9, 0xC($v1)
        MEM_W(0XC, ctx->r3) = ctx->r25;
            goto L_802C5F40;
    }
    // 0x802C5F30: sw          $t9, 0xC($v1)
    MEM_W(0XC, ctx->r3) = ctx->r25;
    // 0x802C5F34: addiu       $t0, $zero, 0x20
    ctx->r8 = ADD32(0, 0X20);
    // 0x802C5F38: jr          $ra
    // 0x802C5F3C: sw          $t0, 0x8($v1)
    MEM_W(0X8, ctx->r3) = ctx->r8;
    return;
    // 0x802C5F3C: sw          $t0, 0x8($v1)
    MEM_W(0X8, ctx->r3) = ctx->r8;
L_802C5F40:
    // 0x802C5F40: addiu       $t1, $zero, 0x1C
    ctx->r9 = ADD32(0, 0X1C);
    // 0x802C5F44: sw          $t1, 0x8($v1)
    MEM_W(0X8, ctx->r3) = ctx->r9;
L_802C5F48:
    // 0x802C5F48: jr          $ra
    // 0x802C5F4C: nop

    return;
    // 0x802C5F4C: nop

;}
RECOMP_FUNC void func_i15_802C5F50(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C5F50: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x802C5F54: addiu       $v0, $v0, -0x19C4
    ctx->r2 = ADD32(ctx->r2, -0X19C4);
    // 0x802C5F58: lw          $t6, 0x0($v0)
    ctx->r14 = MEM_W(ctx->r2, 0X0);
    // 0x802C5F5C: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x802C5F60: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x802C5F64: beq         $t6, $zero, L_802C5F94
    if (ctx->r14 == 0) {
        // 0x802C5F68: lui         $t7, 0x800E
        ctx->r15 = S32(0X800E << 16);
            goto L_802C5F94;
    }
    // 0x802C5F68: lui         $t7, 0x800E
    ctx->r15 = S32(0X800E << 16);
    // 0x802C5F6C: sw          $zero, 0x0($v0)
    MEM_W(0X0, ctx->r2) = 0;
    // 0x802C5F70: lw          $t7, -0x54DC($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X54DC);
    // 0x802C5F74: addiu       $at, $zero, 0x66
    ctx->r1 = ADD32(0, 0X66);
    // 0x802C5F78: addiu       $a1, $zero, 0xFF
    ctx->r5 = ADD32(0, 0XFF);
    // 0x802C5F7C: bne         $t7, $at, L_802C5F94
    if (ctx->r15 != ctx->r1) {
        // 0x802C5F80: addiu       $a2, $zero, 0xFF
        ctx->r6 = ADD32(0, 0XFF);
            goto L_802C5F94;
    }
    // 0x802C5F80: addiu       $a2, $zero, 0xFF
    ctx->r6 = ADD32(0, 0XFF);
    // 0x802C5F84: jal         0x80093DBC
    // 0x802C5F88: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    func_80093DBC(rdram, ctx);
        goto after_0;
    // 0x802C5F88: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    after_0:
    // 0x802C5F8C: b           L_802C6020
    // 0x802C5F90: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_802C6020;
    // 0x802C5F90: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C5F94:
    // 0x802C5F94: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x802C5F98: jal         0x80091DBC
    // 0x802C5F9C: sw          $zero, -0x54D4($at)
    MEM_W(-0X54D4, ctx->r1) = 0;
    func_80091DBC(rdram, ctx);
        goto after_1;
    // 0x802C5F9C: sw          $zero, -0x54D4($at)
    MEM_W(-0X54D4, ctx->r1) = 0;
    after_1:
    // 0x802C5FA0: jal         0x8009328C
    // 0x802C5FA4: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    func_8009328C(rdram, ctx);
        goto after_2;
    // 0x802C5FA4: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    after_2:
    // 0x802C5FA8: jal         0x802C602C
    // 0x802C5FAC: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    func_i15_802C602C(rdram, ctx);
        goto after_3;
    // 0x802C5FAC: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    after_3:
    // 0x802C5FB0: lui         $t8, 0x800E
    ctx->r24 = S32(0X800E << 16);
    // 0x802C5FB4: lw          $t8, -0x54DC($t8)
    ctx->r24 = MEM_W(ctx->r24, -0X54DC);
    // 0x802C5FB8: addiu       $at, $zero, 0x66
    ctx->r1 = ADD32(0, 0X66);
    // 0x802C5FBC: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C5FC0: bne         $t8, $at, L_802C5FD8
    if (ctx->r24 != ctx->r1) {
        // 0x802C5FC4: lui         $t9, 0x8023
        ctx->r25 = S32(0X8023 << 16);
            goto L_802C5FD8;
    }
    // 0x802C5FC4: lui         $t9, 0x8023
    ctx->r25 = S32(0X8023 << 16);
    // 0x802C5FC8: jal         0x802C6C1C
    // 0x802C5FCC: sw          $v0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r2;
    func_i15_802C6C1C(rdram, ctx);
        goto after_4;
    // 0x802C5FCC: sw          $v0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r2;
    after_4:
    // 0x802C5FD0: b           L_802C6018
    // 0x802C5FD4: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
        goto L_802C6018;
    // 0x802C5FD4: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
L_802C5FD8:
    // 0x802C5FD8: lh          $t9, -0x75EA($t9)
    ctx->r25 = MEM_H(ctx->r25, -0X75EA);
    // 0x802C5FDC: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x802C5FE0: lui         $t0, 0x801D
    ctx->r8 = S32(0X801D << 16);
    // 0x802C5FE4: bnel        $t9, $at, L_802C601C
    if (ctx->r25 != ctx->r1) {
        // 0x802C5FE8: or          $v0, $a0, $zero
        ctx->r2 = ctx->r4 | 0;
            goto L_802C601C;
    }
    goto skip_0;
    // 0x802C5FE8: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    skip_0:
    // 0x802C5FEC: lw          $t0, -0x19D0($t0)
    ctx->r8 = MEM_W(ctx->r8, -0X19D0);
    // 0x802C5FF0: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x802C5FF4: bne         $t0, $at, L_802C600C
    if (ctx->r8 != ctx->r1) {
        // 0x802C5FF8: nop
    
            goto L_802C600C;
    }
    // 0x802C5FF8: nop

    // 0x802C5FFC: jal         0x801EB180
    // 0x802C6000: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    func_801EB180(rdram, ctx);
        goto after_5;
    // 0x802C6000: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    after_5:
    // 0x802C6004: b           L_802C6018
    // 0x802C6008: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
        goto L_802C6018;
    // 0x802C6008: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
L_802C600C:
    // 0x802C600C: jal         0x801EC9C8
    // 0x802C6010: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    func_801EC9C8(rdram, ctx);
        goto after_6;
    // 0x802C6010: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    after_6:
    // 0x802C6014: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
L_802C6018:
    // 0x802C6018: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
L_802C601C:
    // 0x802C601C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C6020:
    // 0x802C6020: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x802C6024: jr          $ra
    // 0x802C6028: nop

    return;
    // 0x802C6028: nop

;}
RECOMP_FUNC void func_i15_802C602C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    uint32_t wr64EndingHudBegin = 0;
    // 0x802C602C: addiu       $sp, $sp, -0x130
    ctx->r29 = ADD32(ctx->r29, -0X130);
    // 0x802C6030: sw          $s6, 0x68($sp)
    MEM_W(0X68, ctx->r29) = ctx->r22;
    // 0x802C6034: sw          $s5, 0x64($sp)
    MEM_W(0X64, ctx->r29) = ctx->r21;
    // 0x802C6038: sw          $s4, 0x60($sp)
    MEM_W(0X60, ctx->r29) = ctx->r20;
    // 0x802C603C: lui         $s6, 0x802C
    ctx->r22 = S32(0X802C << 16);
    // 0x802C6040: or          $s4, $a0, $zero
    ctx->r20 = ctx->r4 | 0;
    // 0x802C6044: sw          $ra, 0x74($sp)
    MEM_W(0X74, ctx->r29) = ctx->r31;
    // 0x802C6048: sw          $fp, 0x70($sp)
    MEM_W(0X70, ctx->r29) = ctx->r30;
    // 0x802C604C: sw          $s7, 0x6C($sp)
    MEM_W(0X6C, ctx->r29) = ctx->r23;
    // 0x802C6050: sw          $s3, 0x5C($sp)
    MEM_W(0X5C, ctx->r29) = ctx->r19;
    // 0x802C6054: sw          $s2, 0x58($sp)
    MEM_W(0X58, ctx->r29) = ctx->r18;
    // 0x802C6058: sw          $s1, 0x54($sp)
    MEM_W(0X54, ctx->r29) = ctx->r17;
    // 0x802C605C: sw          $s0, 0x50($sp)
    MEM_W(0X50, ctx->r29) = ctx->r16;
    // 0x802C6060: addiu       $s6, $s6, 0x6E80
    ctx->r22 = ADD32(ctx->r22, 0X6E80);
    // 0x802C6064: or          $s5, $zero, $zero
    ctx->r21 = 0 | 0;
L_802C6068:
    // 0x802C6068: lw          $t6, 0x0($s6)
    ctx->r14 = MEM_W(ctx->r22, 0X0);
    // 0x802C606C: beql        $t6, $zero, L_802C6BDC
    if (ctx->r14 == 0) {
        // 0x802C6070: addiu       $s5, $s5, 0x1
        ctx->r21 = ADD32(ctx->r21, 0X1);
            goto L_802C6BDC;
    }
    goto skip_0;
    // 0x802C6070: addiu       $s5, $s5, 0x1
    ctx->r21 = ADD32(ctx->r21, 0X1);
    skip_0:
    wr64EndingHudBegin = (uint32_t)ctx->r20;
    // 0x802C6074: lw          $t7, 0x4($s6)
    ctx->r15 = MEM_W(ctx->r22, 0X4);
    // 0x802C6078: sltiu       $at, $t7, 0xB
    ctx->r1 = ctx->r15 < 0XB ? 1 : 0;
    // 0x802C607C: beq         $at, $zero, L_802C6BD8
    if (ctx->r1 == 0) {
        // 0x802C6080: sll         $t7, $t7, 2
        ctx->r15 = S32(ctx->r15 << 2);
            goto L_802C6BD8;
    }
    // 0x802C6080: sll         $t7, $t7, 2
    ctx->r15 = S32(ctx->r15 << 2);
    // 0x802C6084: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C6088: addu        $at, $at, $t7
    gpr jr_addend_802C6090 = ctx->r15;
    ctx->r1 = ADD32(ctx->r1, ctx->r15);
    // 0x802C608C: lw          $t7, 0x6E38($at)
    ctx->r15 = ADD32(ctx->r1, 0X6E38);
    // 0x802C6090: jr          $t7
    // 0x802C6094: nop

    switch (jr_addend_802C6090 >> 2) {
        case 0: goto L_802C6098; break;
        case 1: goto L_802C6098; break;
        case 2: goto L_802C6098; break;
        case 3: goto L_802C6098; break;
        case 4: goto L_802C6098; break;
        case 5: goto L_802C6098; break;
        case 6: goto L_802C6098; break;
        case 7: goto L_802C6098; break;
        case 8: goto L_802C6098; break;
        case 9: goto L_802C6BD8; break;
        case 10: goto L_802C6378; break;
        default: switch_error(__func__, 0x802C6090, 0x802C6E38);
    }
    // 0x802C6094: nop

L_802C6098:
    // 0x802C6098: or          $v0, $s4, $zero
    ctx->r2 = ctx->r20 | 0;
    // 0x802C609C: lui         $t9, 0x107
    ctx->r25 = S32(0X107 << 16);
    // 0x802C60A0: addiu       $t9, $t9, -0x9D8
    ctx->r25 = ADD32(ctx->r25, -0X9D8);
    // 0x802C60A4: lui         $t8, 0x600
    ctx->r24 = S32(0X600 << 16);
    // 0x802C60A8: sw          $t8, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r24;
    // 0x802C60AC: sw          $t9, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r25;
    // 0x802C60B0: lw          $a3, 0xC($s6)
    ctx->r7 = MEM_W(ctx->r22, 0XC);
    // 0x802C60B4: lw          $a2, 0x8($s6)
    ctx->r6 = MEM_W(ctx->r22, 0X8);
    // 0x802C60B8: addiu       $t0, $zero, 0x168
    ctx->r8 = ADD32(0, 0X168);
    // 0x802C60BC: addiu       $t1, $zero, 0x20
    ctx->r9 = ADD32(0, 0X20);
    // 0x802C60C0: addiu       $a0, $s4, 0x8
    ctx->r4 = ADD32(ctx->r20, 0X8);
    // 0x802C60C4: sw          $t1, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r9;
    // 0x802C60C8: sw          $t0, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r8;
    // 0x802C60CC: jal         0x80094338
    // 0x802C60D0: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_80094338(rdram, ctx);
        goto after_0;
    // 0x802C60D0: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_0:
    // 0x802C60D4: addiu       $t2, $zero, 0xFF
    ctx->r10 = ADD32(0, 0XFF);
    // 0x802C60D8: addiu       $t3, $zero, 0xFF
    ctx->r11 = ADD32(0, 0XFF);
    // 0x802C60DC: addiu       $t4, $zero, 0xFF
    ctx->r12 = ADD32(0, 0XFF);
    // 0x802C60E0: addiu       $t5, $zero, 0xFF
    ctx->r13 = ADD32(0, 0XFF);
    // 0x802C60E4: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C60E8: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C60EC: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C60F0: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C60F4: addiu       $t0, $zero, 0xFF
    ctx->r8 = ADD32(0, 0XFF);
    // 0x802C60F8: addiu       $t1, $zero, 0xFF
    ctx->r9 = ADD32(0, 0XFF);
    // 0x802C60FC: sw          $t1, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r9;
    // 0x802C6100: sw          $t0, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r8;
    // 0x802C6104: sw          $t9, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r25;
    // 0x802C6108: sw          $t8, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r24;
    // 0x802C610C: sw          $t7, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r15;
    // 0x802C6110: sw          $t6, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r14;
    // 0x802C6114: sw          $t5, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r13;
    // 0x802C6118: sw          $t4, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r12;
    // 0x802C611C: sw          $t3, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r11;
    // 0x802C6120: sw          $t2, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r10;
    // 0x802C6124: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C6128: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C612C: addiu       $a2, $zero, 0xFF
    ctx->r6 = ADD32(0, 0XFF);
    // 0x802C6130: jal         0x801E946C
    // 0x802C6134: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    func_801E946C(rdram, ctx);
        goto after_1;
    // 0x802C6134: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    after_1:
    // 0x802C6138: lui         $t2, 0x801D
    ctx->r10 = S32(0X801D << 16);
    // 0x802C613C: lw          $t2, -0x4CC8($t2)
    ctx->r10 = MEM_W(ctx->r10, -0X4CC8);
    // 0x802C6140: lw          $a0, 0x4($s6)
    ctx->r4 = MEM_W(ctx->r22, 0X4);
    // 0x802C6144: or          $s4, $v0, $zero
    ctx->r20 = ctx->r2 | 0;
    // 0x802C6148: bne         $t2, $zero, L_802C6154
    if (ctx->r10 != 0) {
        // 0x802C614C: or          $v1, $a0, $zero
        ctx->r3 = ctx->r4 | 0;
            goto L_802C6154;
    }
    // 0x802C614C: or          $v1, $a0, $zero
    ctx->r3 = ctx->r4 | 0;
    // 0x802C6150: addiu       $v1, $v1, -0x1
    ctx->r3 = ADD32(ctx->r3, -0X1);
L_802C6154:
    // 0x802C6154: lui         $t3, 0x802C
    ctx->r11 = S32(0X802C << 16);
    // 0x802C6158: lw          $t3, 0x6E7C($t3)
    ctx->r11 = MEM_W(ctx->r11, 0X6E7C);
    // 0x802C615C: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C6160: lui         $a2, 0x802C
    ctx->r6 = S32(0X802C << 16);
    // 0x802C6164: bne         $t3, $a0, L_802C6170
    if (ctx->r11 != ctx->r4) {
        // 0x802C6168: addiu       $t7, $zero, 0x1
        ctx->r15 = ADD32(0, 0X1);
            goto L_802C6170;
    }
    // 0x802C6168: addiu       $t7, $zero, 0x1
    ctx->r15 = ADD32(0, 0X1);
    // 0x802C616C: addiu       $v1, $zero, 0x8
    ctx->r3 = ADD32(0, 0X8);
L_802C6170:
    // 0x802C6170: lw          $t5, 0xC($s6)
    ctx->r13 = MEM_W(ctx->r22, 0XC);
    // 0x802C6174: lw          $a3, 0x8($s6)
    ctx->r7 = MEM_W(ctx->r22, 0X8);
    // 0x802C6178: sll         $t4, $v1, 2
    ctx->r12 = S32(ctx->r3 << 2);
    // 0x802C617C: addu        $a2, $a2, $t4
    ctx->r6 = ADD32(ctx->r6, ctx->r12);
    // 0x802C6180: addiu       $t6, $t5, 0x4
    ctx->r14 = ADD32(ctx->r13, 0X4);
    // 0x802C6184: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x802C6188: lw          $a2, 0x6D9C($a2)
    ctx->r6 = MEM_W(ctx->r6, 0X6D9C);
    // 0x802C618C: sw          $t7, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r15;
    // 0x802C6190: or          $a0, $s4, $zero
    ctx->r4 = ctx->r20 | 0;
    // 0x802C6194: jal         0x801E3EE0
    // 0x802C6198: addiu       $a3, $a3, 0x18
    ctx->r7 = ADD32(ctx->r7, 0X18);
    func_801E3EE0(rdram, ctx);
        goto after_2;
    // 0x802C6198: addiu       $a3, $a3, 0x18
    ctx->r7 = ADD32(ctx->r7, 0X18);
    after_2:
    // 0x802C619C: lw          $t8, 0x4($s6)
    ctx->r24 = MEM_W(ctx->r22, 0X4);
    // 0x802C61A0: lui         $v1, 0x802C
    ctx->r3 = S32(0X802C << 16);
    // 0x802C61A4: lw          $t2, 0xC($s6)
    ctx->r10 = MEM_W(ctx->r22, 0XC);
    // 0x802C61A8: sll         $t9, $t8, 2
    ctx->r25 = S32(ctx->r24 << 2);
    // 0x802C61AC: addu        $v1, $v1, $t9
    ctx->r3 = ADD32(ctx->r3, ctx->r25);
    // 0x802C61B0: lw          $v1, 0x6F20($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X6F20);
    // 0x802C61B4: lui         $t1, 0x802C
    ctx->r9 = S32(0X802C << 16);
    // 0x802C61B8: lw          $a3, 0x8($s6)
    ctx->r7 = MEM_W(ctx->r22, 0X8);
    // 0x802C61BC: addiu       $t1, $t1, 0x6DC0
    ctx->r9 = ADD32(ctx->r9, 0X6DC0);
    // 0x802C61C0: sll         $t0, $v1, 2
    ctx->r8 = S32(ctx->r3 << 2);
    // 0x802C61C4: addu        $s0, $t0, $t1
    ctx->r16 = ADD32(ctx->r8, ctx->r9);
    // 0x802C61C8: addiu       $t3, $t2, 0x10
    ctx->r11 = ADD32(ctx->r10, 0X10);
    // 0x802C61CC: sw          $t3, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r11;
    // 0x802C61D0: lw          $a2, 0x0($s0)
    ctx->r6 = MEM_W(ctx->r16, 0X0);
    // 0x802C61D4: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    // 0x802C61D8: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C61DC: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C61E0: jal         0x801E3EE0
    // 0x802C61E4: addiu       $a3, $a3, 0x27
    ctx->r7 = ADD32(ctx->r7, 0X27);
    func_801E3EE0(rdram, ctx);
        goto after_3;
    // 0x802C61E4: addiu       $a3, $a3, 0x27
    ctx->r7 = ADD32(ctx->r7, 0X27);
    after_3:
    // 0x802C61E8: lui         $t4, 0x802C
    ctx->r12 = S32(0X802C << 16);
    // 0x802C61EC: addiu       $t4, $t4, 0x6DD0
    ctx->r12 = ADD32(ctx->r12, 0X6DD0);
    // 0x802C61F0: beq         $s0, $t4, L_802C6234
    if (ctx->r16 == ctx->r12) {
        // 0x802C61F4: or          $s4, $v0, $zero
        ctx->r20 = ctx->r2 | 0;
            goto L_802C6234;
    }
    // 0x802C61F4: or          $s4, $v0, $zero
    ctx->r20 = ctx->r2 | 0;
    // 0x802C61F8: lw          $t5, 0x4($s6)
    ctx->r13 = MEM_W(ctx->r22, 0X4);
    // 0x802C61FC: lw          $t7, 0xC($s6)
    ctx->r15 = MEM_W(ctx->r22, 0XC);
    // 0x802C6200: lw          $a3, 0x8($s6)
    ctx->r7 = MEM_W(ctx->r22, 0X8);
    // 0x802C6204: lui         $a2, 0x801D
    ctx->r6 = S32(0X801D << 16);
    // 0x802C6208: sll         $t6, $t5, 2
    ctx->r14 = S32(ctx->r13 << 2);
    // 0x802C620C: addu        $a2, $a2, $t6
    ctx->r6 = ADD32(ctx->r6, ctx->r14);
    // 0x802C6210: addiu       $t8, $t7, 0x10
    ctx->r24 = ADD32(ctx->r15, 0X10);
    // 0x802C6214: sw          $t8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r24;
    // 0x802C6218: lw          $a2, -0x4C30($a2)
    ctx->r6 = MEM_W(ctx->r6, -0X4C30);
    // 0x802C621C: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C6220: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C6224: jal         0x801E8B24
    // 0x802C6228: addiu       $a3, $a3, 0xFB
    ctx->r7 = ADD32(ctx->r7, 0XFB);
    func_801E8B24(rdram, ctx);
        goto after_4;
    // 0x802C6228: addiu       $a3, $a3, 0xFB
    ctx->r7 = ADD32(ctx->r7, 0XFB);
    after_4:
    // 0x802C622C: b           L_802C6260
    // 0x802C6230: or          $s4, $v0, $zero
    ctx->r20 = ctx->r2 | 0;
        goto L_802C6260;
    // 0x802C6230: or          $s4, $v0, $zero
    ctx->r20 = ctx->r2 | 0;
L_802C6234:
    // 0x802C6234: lw          $t9, 0xC($s6)
    ctx->r25 = MEM_W(ctx->r22, 0XC);
    // 0x802C6238: lw          $a3, 0x8($s6)
    ctx->r7 = MEM_W(ctx->r22, 0X8);
    // 0x802C623C: lui         $a2, 0x802C
    ctx->r6 = S32(0X802C << 16);
    // 0x802C6240: addiu       $t0, $t9, 0x10
    ctx->r8 = ADD32(ctx->r25, 0X10);
    // 0x802C6244: sw          $t0, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r8;
    // 0x802C6248: addiu       $a2, $a2, 0x6E20
    ctx->r6 = ADD32(ctx->r6, 0X6E20);
    // 0x802C624C: or          $a0, $s4, $zero
    ctx->r4 = ctx->r20 | 0;
    // 0x802C6250: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C6254: jal         0x801E9858
    // 0x802C6258: addiu       $a3, $a3, 0xFB
    ctx->r7 = ADD32(ctx->r7, 0XFB);
    func_801E9858(rdram, ctx);
        goto after_5;
    // 0x802C6258: addiu       $a3, $a3, 0xFB
    ctx->r7 = ADD32(ctx->r7, 0XFB);
    after_5:
    // 0x802C625C: or          $s4, $v0, $zero
    ctx->r20 = ctx->r2 | 0;
L_802C6260:
    // 0x802C6260: lui         $t1, 0x801D
    ctx->r9 = S32(0X801D << 16);
    // 0x802C6264: lw          $t1, -0x4CC8($t1)
    ctx->r9 = MEM_W(ctx->r9, -0X4CC8);
    // 0x802C6268: lw          $t3, 0x4($s6)
    ctx->r11 = MEM_W(ctx->r22, 0X4);
    // 0x802C626C: lui         $v0, 0x800F
    ctx->r2 = S32(0X800F << 16);
    // 0x802C6270: sll         $t2, $t1, 4
    ctx->r10 = S32(ctx->r9 << 4);
    // 0x802C6274: sll         $t4, $t3, 1
    ctx->r12 = S32(ctx->r11 << 1);
    // 0x802C6278: addu        $t5, $t2, $t4
    ctx->r13 = ADD32(ctx->r10, ctx->r12);
    // 0x802C627C: addu        $v0, $v0, $t5
    ctx->r2 = ADD32(ctx->r2, ctx->r13);
    // 0x802C6280: lh          $v0, -0x53EC($v0)
    ctx->r2 = MEM_H(ctx->r2, -0X53EC);
    // 0x802C6284: lui         $t6, 0x802C
    ctx->r14 = S32(0X802C << 16);
    // 0x802C6288: lw          $t7, 0x8($s6)
    ctx->r15 = MEM_W(ctx->r22, 0X8);
    // 0x802C628C: sll         $s0, $v0, 2
    ctx->r16 = S32(ctx->r2 << 2);
    // 0x802C6290: addu        $t6, $t6, $s0
    ctx->r14 = ADD32(ctx->r14, ctx->r16);
    // 0x802C6294: lw          $t6, 0x6DFC($t6)
    ctx->r14 = MEM_W(ctx->r14, 0X6DFC);
    // 0x802C6298: lw          $t8, 0xC($s6)
    ctx->r24 = MEM_W(ctx->r22, 0XC);
    // 0x802C629C: lui         $a2, 0x800E
    ctx->r6 = S32(0X800E << 16);
    // 0x802C62A0: addu        $a2, $a2, $s0
    ctx->r6 = ADD32(ctx->r6, ctx->r16);
    // 0x802C62A4: addu        $a3, $t6, $t7
    ctx->r7 = ADD32(ctx->r14, ctx->r15);
    // 0x802C62A8: addiu       $t9, $t8, 0x4
    ctx->r25 = ADD32(ctx->r24, 0X4);
    // 0x802C62AC: sw          $t9, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r25;
    // 0x802C62B0: addiu       $a3, $a3, 0xF1
    ctx->r7 = ADD32(ctx->r7, 0XF1);
    // 0x802C62B4: lw          $a2, -0x55F0($a2)
    ctx->r6 = MEM_W(ctx->r6, -0X55F0);
    // 0x802C62B8: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    // 0x802C62BC: or          $a0, $s4, $zero
    ctx->r4 = ctx->r20 | 0;
    // 0x802C62C0: jal         0x801E3EE0
    // 0x802C62C4: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    func_801E3EE0(rdram, ctx);
        goto after_6;
    // 0x802C62C4: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    after_6:
    // 0x802C62C8: lui         $t0, 0x801C
    ctx->r8 = S32(0X801C << 16);
    // 0x802C62CC: addu        $t0, $t0, $s0
    ctx->r8 = ADD32(ctx->r8, ctx->r16);
    // 0x802C62D0: lw          $t0, 0x2660($t0)
    ctx->r8 = MEM_W(ctx->r8, 0X2660);
    // 0x802C62D4: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x802C62D8: or          $s4, $v0, $zero
    ctx->r20 = ctx->r2 | 0;
    // 0x802C62DC: bne         $t0, $at, L_802C6BD8
    if (ctx->r8 != ctx->r1) {
        // 0x802C62E0: or          $a0, $v0, $zero
        ctx->r4 = ctx->r2 | 0;
            goto L_802C6BD8;
    }
    // 0x802C62E0: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C62E4: addiu       $t1, $zero, 0xFF
    ctx->r9 = ADD32(0, 0XFF);
    // 0x802C62E8: addiu       $t3, $zero, 0xFF
    ctx->r11 = ADD32(0, 0XFF);
    // 0x802C62EC: addiu       $t2, $zero, 0xFF
    ctx->r10 = ADD32(0, 0XFF);
    // 0x802C62F0: addiu       $t4, $zero, 0xFF
    ctx->r12 = ADD32(0, 0XFF);
    // 0x802C62F4: addiu       $t5, $zero, 0xFF
    ctx->r13 = ADD32(0, 0XFF);
    // 0x802C62F8: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C62FC: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C6300: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C6304: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C6308: addiu       $t0, $zero, 0xFF
    ctx->r8 = ADD32(0, 0XFF);
    // 0x802C630C: sw          $t0, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r8;
    // 0x802C6310: sw          $t9, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r25;
    // 0x802C6314: sw          $t8, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r24;
    // 0x802C6318: sw          $t7, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r15;
    // 0x802C631C: sw          $t6, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r14;
    // 0x802C6320: sw          $t5, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r13;
    // 0x802C6324: sw          $t4, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r12;
    // 0x802C6328: sw          $t2, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r10;
    // 0x802C632C: sw          $t3, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r11;
    // 0x802C6330: sw          $t1, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r9;
    // 0x802C6334: addiu       $a1, $zero, 0x4
    ctx->r5 = ADD32(0, 0X4);
    // 0x802C6338: addiu       $a2, $zero, 0xFF
    ctx->r6 = ADD32(0, 0XFF);
    // 0x802C633C: jal         0x801E946C
    // 0x802C6340: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    func_801E946C(rdram, ctx);
        goto after_7;
    // 0x802C6340: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    after_7:
    // 0x802C6344: lw          $t1, 0xC($s6)
    ctx->r9 = MEM_W(ctx->r22, 0XC);
    // 0x802C6348: lw          $a3, 0x8($s6)
    ctx->r7 = MEM_W(ctx->r22, 0X8);
    // 0x802C634C: addiu       $t2, $zero, 0x2
    ctx->r10 = ADD32(0, 0X2);
    // 0x802C6350: addiu       $t3, $t1, 0x10
    ctx->r11 = ADD32(ctx->r9, 0X10);
    // 0x802C6354: sw          $t3, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r11;
    // 0x802C6358: sw          $t2, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r10;
    // 0x802C635C: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C6360: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C6364: addiu       $a2, $zero, 0x62
    ctx->r6 = ADD32(0, 0X62);
    // 0x802C6368: jal         0x801E3EE0
    // 0x802C636C: addiu       $a3, $a3, 0xD5
    ctx->r7 = ADD32(ctx->r7, 0XD5);
    func_801E3EE0(rdram, ctx);
        goto after_8;
    // 0x802C636C: addiu       $a3, $a3, 0xD5
    ctx->r7 = ADD32(ctx->r7, 0XD5);
    after_8:
    // 0x802C6370: b           L_802C6BD8
    // 0x802C6374: or          $s4, $v0, $zero
    ctx->r20 = ctx->r2 | 0;
        goto L_802C6BD8;
    // 0x802C6374: or          $s4, $v0, $zero
    ctx->r20 = ctx->r2 | 0;
L_802C6378:
    // 0x802C6378: or          $v0, $s4, $zero
    ctx->r2 = ctx->r20 | 0;
    // 0x802C637C: lui         $t5, 0x107
    ctx->r13 = S32(0X107 << 16);
    // 0x802C6380: addiu       $t5, $t5, -0x9D8
    ctx->r13 = ADD32(ctx->r13, -0X9D8);
    // 0x802C6384: lui         $t4, 0x600
    ctx->r12 = S32(0X600 << 16);
    // 0x802C6388: sw          $t4, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r12;
    // 0x802C638C: sw          $t5, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r13;
    // 0x802C6390: lw          $a3, 0xC($s6)
    ctx->r7 = MEM_W(ctx->r22, 0XC);
    // 0x802C6394: lw          $a2, 0x8($s6)
    ctx->r6 = MEM_W(ctx->r22, 0X8);
    // 0x802C6398: lui         $t0, 0x700
    ctx->r8 = S32(0X700 << 16);
    // 0x802C639C: lui         $t1, 0x107
    ctx->r9 = S32(0X107 << 16);
    // 0x802C63A0: addiu       $t1, $t1, -0xB78
    ctx->r9 = ADD32(ctx->r9, -0XB78);
    // 0x802C63A4: addiu       $t0, $t0, 0xA40
    ctx->r8 = ADD32(ctx->r8, 0XA40);
    // 0x802C63A8: addiu       $t6, $zero, 0x171
    ctx->r14 = ADD32(0, 0X171);
    // 0x802C63AC: addiu       $t7, $zero, 0x17
    ctx->r15 = ADD32(0, 0X17);
    // 0x802C63B0: addiu       $t8, $zero, 0x1
    ctx->r24 = ADD32(0, 0X1);
    // 0x802C63B4: addiu       $t9, $zero, 0x1
    ctx->r25 = ADD32(0, 0X1);
    // 0x802C63B8: addiu       $a0, $s4, 0x8
    ctx->r4 = ADD32(ctx->r20, 0X8);
    // 0x802C63BC: sw          $t9, 0x11C($sp)
    MEM_W(0X11C, ctx->r29) = ctx->r25;
    // 0x802C63C0: sw          $t8, 0x110($sp)
    MEM_W(0X110, ctx->r29) = ctx->r24;
    // 0x802C63C4: sw          $t7, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r15;
    // 0x802C63C8: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x802C63CC: sw          $t0, 0x84($sp)
    MEM_W(0X84, ctx->r29) = ctx->r8;
    // 0x802C63D0: sw          $t1, 0x80($sp)
    MEM_W(0X80, ctx->r29) = ctx->r9;
    // 0x802C63D4: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C63D8: or          $s5, $zero, $zero
    ctx->r21 = 0 | 0;
    // 0x802C63DC: jal         0x80094338
    // 0x802C63E0: addiu       $fp, $zero, 0x1
    ctx->r30 = ADD32(0, 0X1);
    func_80094338(rdram, ctx);
        goto after_9;
    // 0x802C63E0: addiu       $fp, $zero, 0x1
    ctx->r30 = ADD32(0, 0X1);
    after_9:
    // 0x802C63E4: lw          $a3, 0xC($s6)
    ctx->r7 = MEM_W(ctx->r22, 0XC);
    // 0x802C63E8: lw          $a2, 0x8($s6)
    ctx->r6 = MEM_W(ctx->r22, 0X8);
    // 0x802C63EC: addiu       $t3, $zero, 0x171
    ctx->r11 = ADD32(0, 0X171);
    // 0x802C63F0: addiu       $t2, $zero, 0x10
    ctx->r10 = ADD32(0, 0X10);
    // 0x802C63F4: sw          $t2, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r10;
    // 0x802C63F8: sw          $t3, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r11;
    // 0x802C63FC: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C6400: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C6404: jal         0x80094338
    // 0x802C6408: addiu       $a3, $a3, 0x1B
    ctx->r7 = ADD32(ctx->r7, 0X1B);
    func_80094338(rdram, ctx);
        goto after_10;
    // 0x802C6408: addiu       $a3, $a3, 0x1B
    ctx->r7 = ADD32(ctx->r7, 0X1B);
    after_10:
    // 0x802C640C: or          $s4, $v0, $zero
    ctx->r20 = ctx->r2 | 0;
    // 0x802C6410: or          $s0, $zero, $zero
    ctx->r16 = 0 | 0;
L_802C6414:
    // 0x802C6414: lw          $t4, 0xC($s6)
    ctx->r12 = MEM_W(ctx->r22, 0XC);
    // 0x802C6418: lw          $a2, 0x8($s6)
    ctx->r6 = MEM_W(ctx->r22, 0X8);
    // 0x802C641C: addiu       $t5, $zero, 0x171
    ctx->r13 = ADD32(0, 0X171);
    // 0x802C6420: addiu       $t6, $zero, 0x1C
    ctx->r14 = ADD32(0, 0X1C);
    // 0x802C6424: addu        $a3, $t4, $s0
    ctx->r7 = ADD32(ctx->r12, ctx->r16);
    // 0x802C6428: addiu       $a3, $a3, 0x2E
    ctx->r7 = ADD32(ctx->r7, 0X2E);
    // 0x802C642C: sw          $t6, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r14;
    // 0x802C6430: sw          $t5, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r13;
    // 0x802C6434: or          $a0, $s4, $zero
    ctx->r4 = ctx->r20 | 0;
    // 0x802C6438: jal         0x80094338
    // 0x802C643C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_80094338(rdram, ctx);
        goto after_11;
    // 0x802C643C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_11:
    // 0x802C6440: addiu       $s0, $s0, 0x20
    ctx->r16 = ADD32(ctx->r16, 0X20);
    // 0x802C6444: slti        $at, $s0, 0x80
    ctx->r1 = SIGNED(ctx->r16) < 0X80 ? 1 : 0;
    // 0x802C6448: bne         $at, $zero, L_802C6414
    if (ctx->r1 != 0) {
        // 0x802C644C: or          $s4, $v0, $zero
        ctx->r20 = ctx->r2 | 0;
            goto L_802C6414;
    }
    // 0x802C644C: or          $s4, $v0, $zero
    ctx->r20 = ctx->r2 | 0;
    // 0x802C6450: lui         $t7, 0x800E
    ctx->r15 = S32(0X800E << 16);
    // 0x802C6454: lh          $t7, -0x5498($t7)
    ctx->r15 = MEM_H(ctx->r15, -0X5498);
    // 0x802C6458: lui         $t8, 0x801D
    ctx->r24 = S32(0X801D << 16);
    // 0x802C645C: bnel        $t7, $zero, L_802C6510
    if (ctx->r15 != 0) {
        // 0x802C6460: addiu       $t8, $zero, 0xFF
        ctx->r24 = ADD32(0, 0XFF);
            goto L_802C6510;
    }
    goto skip_1;
    // 0x802C6460: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    skip_1:
    // 0x802C6464: lw          $t8, -0x4CC8($t8)
    ctx->r24 = MEM_W(ctx->r24, -0X4CC8);
    // 0x802C6468: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x802C646C: lui         $t9, 0x800D
    ctx->r25 = S32(0X800D << 16);
    // 0x802C6470: bne         $t8, $at, L_802C64B4
    if (ctx->r24 != ctx->r1) {
        // 0x802C6474: addiu       $v0, $zero, 0x1
        ctx->r2 = ADD32(0, 0X1);
            goto L_802C64B4;
    }
    // 0x802C6474: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
    // 0x802C6478: lw          $t9, 0x48DC($t9)
    ctx->r25 = MEM_W(ctx->r25, 0X48DC);
    // 0x802C647C: lui         $t1, 0x801C
    ctx->r9 = S32(0X801C << 16);
    // 0x802C6480: sll         $t0, $t9, 3
    ctx->r8 = S32(ctx->r25 << 3);
    // 0x802C6484: subu        $t0, $t0, $t9
    ctx->r8 = SUB32(ctx->r8, ctx->r25);
    // 0x802C6488: sll         $t0, $t0, 4
    ctx->r8 = S32(ctx->r8 << 4);
    // 0x802C648C: subu        $t0, $t0, $t9
    ctx->r8 = SUB32(ctx->r8, ctx->r25);
    // 0x802C6490: sll         $t0, $t0, 3
    ctx->r8 = S32(ctx->r8 << 3);
    // 0x802C6494: addu        $t1, $t1, $t0
    ctx->r9 = ADD32(ctx->r9, ctx->r8);
    // 0x802C6498: lw          $t1, 0x2C70($t1)
    ctx->r9 = MEM_W(ctx->r9, 0X2C70);
    // 0x802C649C: bne         $t1, $zero, L_802C64AC
    if (ctx->r9 != 0) {
        // 0x802C64A0: nop
    
            goto L_802C64AC;
    }
    // 0x802C64A0: nop

    // 0x802C64A4: b           L_802C64B4
    // 0x802C64A8: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
        goto L_802C64B4;
    // 0x802C64A8: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
L_802C64AC:
    // 0x802C64AC: b           L_802C64B4
    // 0x802C64B0: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
        goto L_802C64B4;
    // 0x802C64B0: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_802C64B4:
    // 0x802C64B4: beq         $v0, $zero, L_802C650C
    if (ctx->r2 == 0) {
        // 0x802C64B8: addiu       $a0, $s4, 0x8
        ctx->r4 = ADD32(ctx->r20, 0X8);
            goto L_802C650C;
    }
    // 0x802C64B8: addiu       $a0, $s4, 0x8
    ctx->r4 = ADD32(ctx->r20, 0X8);
    // 0x802C64BC: or          $v0, $s4, $zero
    ctx->r2 = ctx->r20 | 0;
    // 0x802C64C0: lui         $t3, 0xFA00
    ctx->r11 = S32(0XFA00 << 16);
    // 0x802C64C4: sw          $t3, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r11;
    // 0x802C64C8: lui         $t2, 0x802C
    ctx->r10 = S32(0X802C << 16);
    // 0x802C64CC: lw          $t2, 0x6DD8($t2)
    ctx->r10 = MEM_W(ctx->r10, 0X6DD8);
    // 0x802C64D0: addiu       $at, $zero, -0x100
    ctx->r1 = ADD32(0, -0X100);
    // 0x802C64D4: addiu       $t6, $zero, 0xCC
    ctx->r14 = ADD32(0, 0XCC);
    // 0x802C64D8: andi        $t4, $t2, 0xFF
    ctx->r12 = ctx->r10 & 0XFF;
    // 0x802C64DC: or          $t5, $t4, $at
    ctx->r13 = ctx->r12 | ctx->r1;
    // 0x802C64E0: sw          $t5, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r13;
    // 0x802C64E4: lw          $a3, 0xC($s6)
    ctx->r7 = MEM_W(ctx->r22, 0XC);
    // 0x802C64E8: lw          $a2, 0x8($s6)
    ctx->r6 = MEM_W(ctx->r22, 0X8);
    // 0x802C64EC: addiu       $t7, $zero, 0x10
    ctx->r15 = ADD32(0, 0X10);
    // 0x802C64F0: sw          $t7, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r15;
    // 0x802C64F4: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x802C64F8: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C64FC: addiu       $a3, $a3, 0xAE
    ctx->r7 = ADD32(ctx->r7, 0XAE);
    // 0x802C6500: jal         0x80094338
    // 0x802C6504: addiu       $a2, $a2, 0x52
    ctx->r6 = ADD32(ctx->r6, 0X52);
    func_80094338(rdram, ctx);
        goto after_12;
    // 0x802C6504: addiu       $a2, $a2, 0x52
    ctx->r6 = ADD32(ctx->r6, 0X52);
    after_12:
    // 0x802C6508: or          $s4, $v0, $zero
    ctx->r20 = ctx->r2 | 0;
L_802C650C:
    // 0x802C650C: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
L_802C6510:
    // 0x802C6510: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C6514: addiu       $t0, $zero, 0xFF
    ctx->r8 = ADD32(0, 0XFF);
    // 0x802C6518: addiu       $t1, $zero, 0xFF
    ctx->r9 = ADD32(0, 0XFF);
    // 0x802C651C: addiu       $t3, $zero, 0xFF
    ctx->r11 = ADD32(0, 0XFF);
    // 0x802C6520: addiu       $t2, $zero, 0xFF
    ctx->r10 = ADD32(0, 0XFF);
    // 0x802C6524: addiu       $t4, $zero, 0xFF
    ctx->r12 = ADD32(0, 0XFF);
    // 0x802C6528: addiu       $t5, $zero, 0xFF
    ctx->r13 = ADD32(0, 0XFF);
    // 0x802C652C: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C6530: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C6534: sw          $t7, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r15;
    // 0x802C6538: sw          $t6, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r14;
    // 0x802C653C: sw          $t5, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r13;
    // 0x802C6540: sw          $t4, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r12;
    // 0x802C6544: sw          $t2, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r10;
    // 0x802C6548: sw          $t3, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r11;
    // 0x802C654C: sw          $t1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r9;
    // 0x802C6550: sw          $t0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r8;
    // 0x802C6554: sw          $t9, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r25;
    // 0x802C6558: sw          $t8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r24;
    // 0x802C655C: or          $a0, $s4, $zero
    ctx->r4 = ctx->r20 | 0;
    // 0x802C6560: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C6564: addiu       $a2, $zero, 0xFF
    ctx->r6 = ADD32(0, 0XFF);
    // 0x802C6568: jal         0x801E946C
    // 0x802C656C: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    func_801E946C(rdram, ctx);
        goto after_13;
    // 0x802C656C: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    after_13:
    // 0x802C6570: lw          $t8, 0xC($s6)
    ctx->r24 = MEM_W(ctx->r22, 0XC);
    // 0x802C6574: lw          $a3, 0x8($s6)
    ctx->r7 = MEM_W(ctx->r22, 0X8);
    // 0x802C6578: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    // 0x802C657C: addiu       $t9, $t8, 0x3
    ctx->r25 = ADD32(ctx->r24, 0X3);
    // 0x802C6580: sw          $t9, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r25;
    // 0x802C6584: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C6588: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C658C: addiu       $a2, $zero, 0x26
    ctx->r6 = ADD32(0, 0X26);
    // 0x802C6590: jal         0x801E3EE0
    // 0x802C6594: addiu       $a3, $a3, 0x40
    ctx->r7 = ADD32(ctx->r7, 0X40);
    func_801E3EE0(rdram, ctx);
        goto after_14;
    // 0x802C6594: addiu       $a3, $a3, 0x40
    ctx->r7 = ADD32(ctx->r7, 0X40);
    after_14:
    // 0x802C6598: lw          $t0, 0xC($s6)
    ctx->r8 = MEM_W(ctx->r22, 0XC);
    // 0x802C659C: lw          $a3, 0x8($s6)
    ctx->r7 = MEM_W(ctx->r22, 0X8);
    // 0x802C65A0: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    // 0x802C65A4: addiu       $t1, $t0, 0x1E
    ctx->r9 = ADD32(ctx->r8, 0X1E);
    // 0x802C65A8: sw          $t1, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r9;
    // 0x802C65AC: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C65B0: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C65B4: addiu       $a2, $zero, 0x1F
    ctx->r6 = ADD32(0, 0X1F);
    // 0x802C65B8: jal         0x801E3EE0
    // 0x802C65BC: addiu       $a3, $a3, 0x5
    ctx->r7 = ADD32(ctx->r7, 0X5);
    func_801E3EE0(rdram, ctx);
        goto after_15;
    // 0x802C65BC: addiu       $a3, $a3, 0x5
    ctx->r7 = ADD32(ctx->r7, 0X5);
    after_15:
    // 0x802C65C0: lw          $t3, 0xC($s6)
    ctx->r11 = MEM_W(ctx->r22, 0XC);
    // 0x802C65C4: lw          $a3, 0x8($s6)
    ctx->r7 = MEM_W(ctx->r22, 0X8);
    // 0x802C65C8: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    // 0x802C65CC: addiu       $t2, $t3, 0x1E
    ctx->r10 = ADD32(ctx->r11, 0X1E);
    // 0x802C65D0: sw          $t2, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r10;
    // 0x802C65D4: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C65D8: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C65DC: addiu       $a2, $zero, 0x20
    ctx->r6 = ADD32(0, 0X20);
    // 0x802C65E0: jal         0x801E3EE0
    // 0x802C65E4: addiu       $a3, $a3, 0x99
    ctx->r7 = ADD32(ctx->r7, 0X99);
    func_801E3EE0(rdram, ctx);
        goto after_16;
    // 0x802C65E4: addiu       $a3, $a3, 0x99
    ctx->r7 = ADD32(ctx->r7, 0X99);
    after_16:
    // 0x802C65E8: lw          $t4, 0xC($s6)
    ctx->r12 = MEM_W(ctx->r22, 0XC);
    // 0x802C65EC: lw          $a3, 0x8($s6)
    ctx->r7 = MEM_W(ctx->r22, 0X8);
    // 0x802C65F0: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    // 0x802C65F4: addiu       $t5, $t4, 0x1E
    ctx->r13 = ADD32(ctx->r12, 0X1E);
    // 0x802C65F8: sw          $t5, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r13;
    // 0x802C65FC: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C6600: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C6604: addiu       $a2, $zero, 0x3A
    ctx->r6 = ADD32(0, 0X3A);
    // 0x802C6608: jal         0x801E3EE0
    // 0x802C660C: addiu       $a3, $a3, 0x137
    ctx->r7 = ADD32(ctx->r7, 0X137);
    func_801E3EE0(rdram, ctx);
        goto after_17;
    // 0x802C660C: addiu       $a3, $a3, 0x137
    ctx->r7 = ADD32(ctx->r7, 0X137);
    after_17:
    // 0x802C6610: lui         $t6, 0x800E
    ctx->r14 = S32(0X800E << 16);
    // 0x802C6614: lh          $t6, -0x5498($t6)
    ctx->r14 = MEM_H(ctx->r14, -0X5498);
    // 0x802C6618: or          $s4, $v0, $zero
    ctx->r20 = ctx->r2 | 0;
    // 0x802C661C: lui         $t7, 0x801D
    ctx->r15 = S32(0X801D << 16);
    // 0x802C6620: bnel        $t6, $zero, L_802C6714
    if (ctx->r14 != 0) {
        // 0x802C6624: addiu       $t2, $zero, 0xFF
        ctx->r10 = ADD32(0, 0XFF);
            goto L_802C6714;
    }
    goto skip_2;
    // 0x802C6624: addiu       $t2, $zero, 0xFF
    ctx->r10 = ADD32(0, 0XFF);
    skip_2:
    // 0x802C6628: lw          $t7, -0x4CC8($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X4CC8);
    // 0x802C662C: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x802C6630: lui         $t8, 0x800D
    ctx->r24 = S32(0X800D << 16);
    // 0x802C6634: bne         $t7, $at, L_802C6678
    if (ctx->r15 != ctx->r1) {
        // 0x802C6638: addiu       $v0, $zero, 0x1
        ctx->r2 = ADD32(0, 0X1);
            goto L_802C6678;
    }
    // 0x802C6638: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
    // 0x802C663C: lw          $t8, 0x48DC($t8)
    ctx->r24 = MEM_W(ctx->r24, 0X48DC);
    // 0x802C6640: lui         $t0, 0x801C
    ctx->r8 = S32(0X801C << 16);
    // 0x802C6644: sll         $t9, $t8, 3
    ctx->r25 = S32(ctx->r24 << 3);
    // 0x802C6648: subu        $t9, $t9, $t8
    ctx->r25 = SUB32(ctx->r25, ctx->r24);
    // 0x802C664C: sll         $t9, $t9, 4
    ctx->r25 = S32(ctx->r25 << 4);
    // 0x802C6650: subu        $t9, $t9, $t8
    ctx->r25 = SUB32(ctx->r25, ctx->r24);
    // 0x802C6654: sll         $t9, $t9, 3
    ctx->r25 = S32(ctx->r25 << 3);
    // 0x802C6658: addu        $t0, $t0, $t9
    ctx->r8 = ADD32(ctx->r8, ctx->r25);
    // 0x802C665C: lw          $t0, 0x2C70($t0)
    ctx->r8 = MEM_W(ctx->r8, 0X2C70);
    // 0x802C6660: bne         $t0, $zero, L_802C6670
    if (ctx->r8 != 0) {
        // 0x802C6664: nop
    
            goto L_802C6670;
    }
    // 0x802C6664: nop

    // 0x802C6668: b           L_802C6678
    // 0x802C666C: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
        goto L_802C6678;
    // 0x802C666C: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
L_802C6670:
    // 0x802C6670: b           L_802C6678
    // 0x802C6674: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
        goto L_802C6678;
    // 0x802C6674: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_802C6678:
    // 0x802C6678: beq         $v0, $zero, L_802C6710
    if (ctx->r2 == 0) {
        // 0x802C667C: or          $a0, $s4, $zero
        ctx->r4 = ctx->r20 | 0;
            goto L_802C6710;
    }
    // 0x802C667C: or          $a0, $s4, $zero
    ctx->r4 = ctx->r20 | 0;
    // 0x802C6680: lui         $a2, 0x802C
    ctx->r6 = S32(0X802C << 16);
    // 0x802C6684: addiu       $t1, $zero, 0xFF
    ctx->r9 = ADD32(0, 0XFF);
    // 0x802C6688: addiu       $t3, $zero, 0xFF
    ctx->r11 = ADD32(0, 0XFF);
    // 0x802C668C: addiu       $t2, $zero, 0xFF
    ctx->r10 = ADD32(0, 0XFF);
    // 0x802C6690: addiu       $t4, $zero, 0xFF
    ctx->r12 = ADD32(0, 0XFF);
    // 0x802C6694: addiu       $t5, $zero, 0xFF
    ctx->r13 = ADD32(0, 0XFF);
    // 0x802C6698: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C669C: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C66A0: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C66A4: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C66A8: addiu       $t0, $zero, 0xFF
    ctx->r8 = ADD32(0, 0XFF);
    // 0x802C66AC: sw          $t0, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r8;
    // 0x802C66B0: sw          $t9, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r25;
    // 0x802C66B4: sw          $t8, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r24;
    // 0x802C66B8: sw          $t7, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r15;
    // 0x802C66BC: sw          $t6, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r14;
    // 0x802C66C0: sw          $t5, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r13;
    // 0x802C66C4: sw          $t4, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r12;
    // 0x802C66C8: sw          $t2, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r10;
    // 0x802C66CC: sw          $t3, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r11;
    // 0x802C66D0: sw          $t1, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r9;
    // 0x802C66D4: lbu         $a2, 0x6DD7($a2)
    ctx->r6 = MEM_BU(ctx->r6, 0X6DD7);
    // 0x802C66D8: addiu       $a1, $zero, 0xA
    ctx->r5 = ADD32(0, 0XA);
    // 0x802C66DC: jal         0x801E946C
    // 0x802C66E0: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    func_801E946C(rdram, ctx);
        goto after_18;
    // 0x802C66E0: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    after_18:
    // 0x802C66E4: lw          $t1, 0xC($s6)
    ctx->r9 = MEM_W(ctx->r22, 0XC);
    // 0x802C66E8: lw          $a3, 0x8($s6)
    ctx->r7 = MEM_W(ctx->r22, 0X8);
    // 0x802C66EC: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    // 0x802C66F0: addiu       $t3, $t1, 0xB1
    ctx->r11 = ADD32(ctx->r9, 0XB1);
    // 0x802C66F4: sw          $t3, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r11;
    // 0x802C66F8: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C66FC: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C6700: addiu       $a2, $zero, 0x63
    ctx->r6 = ADD32(0, 0X63);
    // 0x802C6704: jal         0x801E3EE0
    // 0x802C6708: addiu       $a3, $a3, 0x58
    ctx->r7 = ADD32(ctx->r7, 0X58);
    func_801E3EE0(rdram, ctx);
        goto after_19;
    // 0x802C6708: addiu       $a3, $a3, 0x58
    ctx->r7 = ADD32(ctx->r7, 0X58);
    after_19:
    // 0x802C670C: or          $s4, $v0, $zero
    ctx->r20 = ctx->r2 | 0;
L_802C6710:
    // 0x802C6710: addiu       $t2, $zero, 0xFF
    ctx->r10 = ADD32(0, 0XFF);
L_802C6714:
    // 0x802C6714: sw          $t2, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r10;
    // 0x802C6718: or          $a0, $s4, $zero
    ctx->r4 = ctx->r20 | 0;
    // 0x802C671C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C6720: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x802C6724: jal         0x801E7E74
    // 0x802C6728: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_801E7E74(rdram, ctx);
        goto after_20;
    // 0x802C6728: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_20:
    // 0x802C672C: or          $s4, $v0, $zero
    ctx->r20 = ctx->r2 | 0;
    // 0x802C6730: or          $s0, $zero, $zero
    ctx->r16 = 0 | 0;
L_802C6734:
    // 0x802C6734: lw          $t4, 0xC($s6)
    ctx->r12 = MEM_W(ctx->r22, 0XC);
    // 0x802C6738: lw          $v0, 0x8($s6)
    ctx->r2 = MEM_W(ctx->r22, 0X8);
    // 0x802C673C: or          $a0, $s4, $zero
    ctx->r4 = ctx->r20 | 0;
    // 0x802C6740: addu        $v1, $t4, $s0
    ctx->r3 = ADD32(ctx->r12, ctx->r16);
    // 0x802C6744: addiu       $t5, $v1, 0x46
    ctx->r13 = ADD32(ctx->r3, 0X46);
    // 0x802C6748: sw          $t5, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r13;
    // 0x802C674C: addiu       $a2, $v1, 0x31
    ctx->r6 = ADD32(ctx->r3, 0X31);
    // 0x802C6750: addiu       $a1, $v0, 0x22
    ctx->r5 = ADD32(ctx->r2, 0X22);
    // 0x802C6754: jal         0x801E7FD8
    // 0x802C6758: addiu       $a3, $v0, 0x4E
    ctx->r7 = ADD32(ctx->r2, 0X4E);
    func_801E7FD8(rdram, ctx);
        goto after_21;
    // 0x802C6758: addiu       $a3, $v0, 0x4E
    ctx->r7 = ADD32(ctx->r2, 0X4E);
    after_21:
    // 0x802C675C: addiu       $s0, $s0, 0x20
    ctx->r16 = ADD32(ctx->r16, 0X20);
    // 0x802C6760: slti        $at, $s0, 0x80
    ctx->r1 = SIGNED(ctx->r16) < 0X80 ? 1 : 0;
    // 0x802C6764: bne         $at, $zero, L_802C6734
    if (ctx->r1 != 0) {
        // 0x802C6768: or          $s4, $v0, $zero
        ctx->r20 = ctx->r2 | 0;
            goto L_802C6734;
    }
    // 0x802C6768: or          $s4, $v0, $zero
    ctx->r20 = ctx->r2 | 0;
    // 0x802C676C: addiu       $s4, $v0, 0x8
    ctx->r20 = ADD32(ctx->r2, 0X8);
    // 0x802C6770: lui         $t6, 0xE700
    ctx->r14 = S32(0XE700 << 16);
    // 0x802C6774: or          $a0, $s4, $zero
    ctx->r4 = ctx->r20 | 0;
    // 0x802C6778: sw          $t6, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r14;
    // 0x802C677C: sw          $zero, 0x4($v0)
    MEM_W(0X4, ctx->r2) = 0;
    // 0x802C6780: lui         $t7, 0xED02
    ctx->r15 = S32(0XED02 << 16);
    // 0x802C6784: addiu       $t7, $t7, 0x50
    ctx->r15 = ADD32(ctx->r15, 0X50);
    // 0x802C6788: lui         $t8, 0x68
    ctx->r24 = S32(0X68 << 16);
    // 0x802C678C: addiu       $t8, $t8, -0x3C94
    ctx->r24 = ADD32(ctx->r24, -0X3C94);
    // 0x802C6790: lui         $s3, 0x800E
    ctx->r19 = S32(0X800E << 16);
    { extern uint32_t wr64_experimental_viewport_borders(void); if (wr64_experimental_viewport_borders()) { ctx->r15 = 0xED000000U; ctx->r24 = 0x006A03C0U; } }
    // 0x802C6794: sw          $t7, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r15;
    // 0x802C6798: sw          $t8, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r24;
    // 0x802C679C: addiu       $s4, $s4, 0x8
    ctx->r20 = ADD32(ctx->r20, 0X8);
    // 0x802C67A0: addiu       $s3, $s3, -0x5624
    ctx->r19 = ADD32(ctx->r19, -0X5624);
    // 0x802C67A4: or          $s0, $zero, $zero
    ctx->r16 = 0 | 0;
L_802C67A8:
    // 0x802C67A8: lui         $t9, 0x800E
    ctx->r25 = S32(0X800E << 16);
    // 0x802C67AC: addiu       $t9, $t9, -0x5624
    ctx->r25 = ADD32(ctx->r25, -0X5624);
    // 0x802C67B0: beq         $s3, $t9, L_802C6800
    if (ctx->r19 == ctx->r25) {
        // 0x802C67B4: addiu       $a0, $sp, 0xE0
        ctx->r4 = ADD32(ctx->r29, 0XE0);
            goto L_802C6800;
    }
    // 0x802C67B4: addiu       $a0, $sp, 0xE0
    ctx->r4 = ADD32(ctx->r29, 0XE0);
    // 0x802C67B8: lw          $t0, 0x0($s3)
    ctx->r8 = MEM_W(ctx->r19, 0X0);
    // 0x802C67BC: lw          $t4, -0x4($s3)
    ctx->r12 = MEM_W(ctx->r19, -0X4);
    // 0x802C67C0: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x802C67C4: addiu       $v0, $v0, -0x4CC0
    ctx->r2 = ADD32(ctx->r2, -0X4CC0);
    // 0x802C67C8: sll         $t1, $t0, 2
    ctx->r9 = S32(ctx->r8 << 2);
    // 0x802C67CC: sll         $t5, $t4, 2
    ctx->r13 = S32(ctx->r12 << 2);
    // 0x802C67D0: addu        $t6, $v0, $t5
    ctx->r14 = ADD32(ctx->r2, ctx->r13);
    // 0x802C67D4: addu        $t3, $v0, $t1
    ctx->r11 = ADD32(ctx->r2, ctx->r9);
    // 0x802C67D8: lw          $t2, 0x0($t3)
    ctx->r10 = MEM_W(ctx->r11, 0X0);
    // 0x802C67DC: lw          $t7, 0x0($t6)
    ctx->r15 = MEM_W(ctx->r14, 0X0);
    // 0x802C67E0: addiu       $fp, $fp, 0x1
    ctx->r30 = ADD32(ctx->r30, 0X1);
    // 0x802C67E4: lw          $t8, 0x110($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X110);
    // 0x802C67E8: beql        $t2, $t7, L_802C6800
    if (ctx->r10 == ctx->r15) {
        // 0x802C67EC: sw          $t8, 0x11C($sp)
        MEM_W(0X11C, ctx->r29) = ctx->r24;
            goto L_802C6800;
    }
    goto skip_3;
    // 0x802C67EC: sw          $t8, 0x11C($sp)
    MEM_W(0X11C, ctx->r29) = ctx->r24;
    skip_3:
    // 0x802C67F0: sw          $fp, 0x110($sp)
    MEM_W(0X110, ctx->r29) = ctx->r30;
    // 0x802C67F4: b           L_802C6800
    // 0x802C67F8: sw          $fp, 0x11C($sp)
    MEM_W(0X11C, ctx->r29) = ctx->r30;
        goto L_802C6800;
    // 0x802C67F8: sw          $fp, 0x11C($sp)
    MEM_W(0X11C, ctx->r29) = ctx->r30;
    // 0x802C67FC: sw          $t8, 0x11C($sp)
    MEM_W(0X11C, ctx->r29) = ctx->r24;
L_802C6800:
    // 0x802C6800: lui         $a1, 0x802C
    ctx->r5 = S32(0X802C << 16);
    // 0x802C6804: addiu       $a1, $a1, 0x6E2C
    ctx->r5 = ADD32(ctx->r5, 0X6E2C);
    // 0x802C6808: jal         0x800CA210
    // 0x802C680C: lw          $a2, 0x11C($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X11C);
    func_800CA210(rdram, ctx);
        goto after_22;
    // 0x802C680C: lw          $a2, 0x11C($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X11C);
    after_22:
    // 0x802C6810: lw          $a0, 0x0($s3)
    ctx->r4 = MEM_W(ctx->r19, 0X0);
    // 0x802C6814: lui         $t9, 0x800E
    ctx->r25 = S32(0X800E << 16);
    // 0x802C6818: lui         $a1, 0x800D
    ctx->r5 = S32(0X800D << 16);
    // 0x802C681C: sll         $v1, $a0, 2
    ctx->r3 = S32(ctx->r4 << 2);
    // 0x802C6820: addu        $t9, $t9, $v1
    ctx->r25 = ADD32(ctx->r25, ctx->r3);
    // 0x802C6824: lw          $t9, -0x5650($t9)
    ctx->r25 = MEM_W(ctx->r25, -0X5650);
    // 0x802C6828: lw          $a1, 0x48DC($a1)
    ctx->r5 = MEM_W(ctx->r5, 0X48DC);
    // 0x802C682C: lui         $t1, 0x801D
    ctx->r9 = S32(0X801D << 16);
    // 0x802C6830: sll         $t0, $t9, 3
    ctx->r8 = S32(ctx->r25 << 3);
    // 0x802C6834: lui         $s1, 0x801D
    ctx->r17 = S32(0X801D << 16);
    // 0x802C6838: subu        $t0, $t0, $t9
    ctx->r8 = SUB32(ctx->r8, ctx->r25);
    // 0x802C683C: sll         $t0, $t0, 1
    ctx->r8 = S32(ctx->r8 << 1);
    // 0x802C6840: addiu       $t1, $t1, -0x4D68
    ctx->r9 = ADD32(ctx->r9, -0X4D68);
    // 0x802C6844: addu        $s1, $s1, $v1
    ctx->r17 = ADD32(ctx->r17, ctx->r3);
    // 0x802C6848: addu        $s7, $t0, $t1
    ctx->r23 = ADD32(ctx->r8, ctx->r9);
    // 0x802C684C: beq         $a1, $a0, L_802C685C
    if (ctx->r5 == ctx->r4) {
        // 0x802C6850: lw          $s1, -0x4CC0($s1)
        ctx->r17 = MEM_W(ctx->r17, -0X4CC0);
            goto L_802C685C;
    }
    // 0x802C6850: lw          $s1, -0x4CC0($s1)
    ctx->r17 = MEM_W(ctx->r17, -0X4CC0);
    // 0x802C6854: b           L_802C6860
    // 0x802C6858: or          $s5, $zero, $zero
    ctx->r21 = 0 | 0;
        goto L_802C6860;
    // 0x802C6858: or          $s5, $zero, $zero
    ctx->r21 = 0 | 0;
L_802C685C:
    // 0x802C685C: addiu       $s5, $zero, 0x6
    ctx->r21 = ADD32(0, 0X6);
L_802C6860:
    // 0x802C6860: beq         $a1, $a0, L_802C6870
    if (ctx->r5 == ctx->r4) {
        // 0x802C6864: or          $a2, $s1, $zero
        ctx->r6 = ctx->r17 | 0;
            goto L_802C6870;
    }
    // 0x802C6864: or          $a2, $s1, $zero
    ctx->r6 = ctx->r17 | 0;
    // 0x802C6868: b           L_802C6874
    // 0x802C686C: or          $s2, $zero, $zero
    ctx->r18 = 0 | 0;
        goto L_802C6874;
    // 0x802C686C: or          $s2, $zero, $zero
    ctx->r18 = 0 | 0;
L_802C6870:
    // 0x802C6870: addiu       $s2, $zero, 0x6
    ctx->r18 = ADD32(0, 0X6);
L_802C6874:
    // 0x802C6874: lui         $a1, 0x802C
    ctx->r5 = S32(0X802C << 16);
    // 0x802C6878: addiu       $a1, $a1, 0x6E30
    ctx->r5 = ADD32(ctx->r5, 0X6E30);
    // 0x802C687C: jal         0x800CA210
    // 0x802C6880: addiu       $a0, $sp, 0xD4
    ctx->r4 = ADD32(ctx->r29, 0XD4);
    func_800CA210(rdram, ctx);
        goto after_23;
    // 0x802C6880: addiu       $a0, $sp, 0xD4
    ctx->r4 = ADD32(ctx->r29, 0XD4);
    after_23:
    // 0x802C6884: addiu       $a0, $zero, 0xA
    ctx->r4 = ADD32(0, 0XA);
    // 0x802C6888: div         $zero, $s1, $a0
    lo = S32(S64(S32(ctx->r17)) / S64(S32(ctx->r4))); hi = S32(S64(S32(ctx->r17)) % S64(S32(ctx->r4)));
    // 0x802C688C: mflo        $t3
    ctx->r11 = lo;
    // 0x802C6890: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C6894: bne         $a0, $zero, L_802C68A0
    if (ctx->r4 != 0) {
        // 0x802C6898: nop
    
            goto L_802C68A0;
    }
    // 0x802C6898: nop

    // 0x802C689C: break       7
    do_break(2150394012);
L_802C68A0:
    // 0x802C68A0: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x802C68A4: bne         $a0, $at, L_802C68B8
    if (ctx->r4 != ctx->r1) {
        // 0x802C68A8: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_802C68B8;
    }
    // 0x802C68A8: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x802C68AC: bne         $s1, $at, L_802C68B8
    if (ctx->r17 != ctx->r1) {
        // 0x802C68B0: nop
    
            goto L_802C68B8;
    }
    // 0x802C68B0: nop

    // 0x802C68B4: break       6
    do_break(2150394036);
L_802C68B8:
    // 0x802C68B8: div         $zero, $t3, $a0
    lo = S32(S64(S32(ctx->r11)) / S64(S32(ctx->r4))); hi = S32(S64(S32(ctx->r11)) % S64(S32(ctx->r4)));
    // 0x802C68BC: mfhi        $v1
    ctx->r3 = hi;
    // 0x802C68C0: addiu       $a2, $sp, 0xE0
    ctx->r6 = ADD32(ctx->r29, 0XE0);
    // 0x802C68C4: bne         $a0, $zero, L_802C68D0
    if (ctx->r4 != 0) {
        // 0x802C68C8: nop
    
            goto L_802C68D0;
    }
    // 0x802C68C8: nop

    // 0x802C68CC: break       7
    do_break(2150394060);
L_802C68D0:
    // 0x802C68D0: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x802C68D4: bne         $a0, $at, L_802C68E8
    if (ctx->r4 != ctx->r1) {
        // 0x802C68D8: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_802C68E8;
    }
    // 0x802C68D8: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x802C68DC: bne         $t3, $at, L_802C68E8
    if (ctx->r11 != ctx->r1) {
        // 0x802C68E0: nop
    
            goto L_802C68E8;
    }
    // 0x802C68E0: nop

    // 0x802C68E4: break       6
    do_break(2150394084);
L_802C68E8:
    // 0x802C68E8: or          $a0, $s4, $zero
    ctx->r4 = ctx->r20 | 0;
    // 0x802C68EC: beq         $v1, $zero, L_802C690C
    if (ctx->r3 == 0) {
        // 0x802C68F0: addiu       $t8, $zero, 0xFF
        ctx->r24 = ADD32(0, 0XFF);
            goto L_802C690C;
    }
    // 0x802C68F0: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C68F4: lui         $t4, 0x8022
    ctx->r12 = S32(0X8022 << 16);
    // 0x802C68F8: addu        $t4, $t4, $v1
    ctx->r12 = ADD32(ctx->r12, ctx->r3);
    // 0x802C68FC: lbu         $t4, 0x6D70($t4)
    ctx->r12 = MEM_BU(ctx->r12, 0X6D70);
    // 0x802C6900: addiu       $t5, $zero, 0x14C
    ctx->r13 = ADD32(0, 0X14C);
    // 0x802C6904: b           L_802C6910
    // 0x802C6908: subu        $s1, $t5, $t4
    ctx->r17 = SUB32(ctx->r13, ctx->r12);
        goto L_802C6910;
    // 0x802C6908: subu        $s1, $t5, $t4
    ctx->r17 = SUB32(ctx->r13, ctx->r12);
L_802C690C:
    // 0x802C690C: addiu       $s1, $zero, 0x14C
    ctx->r17 = ADD32(0, 0X14C);
L_802C6910:
    // 0x802C6910: lw          $t6, 0xC($s6)
    ctx->r14 = MEM_W(ctx->r22, 0XC);
    // 0x802C6914: lw          $a3, 0x8($s6)
    ctx->r7 = MEM_W(ctx->r22, 0X8);
    // 0x802C6918: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C691C: addu        $t2, $t6, $s0
    ctx->r10 = ADD32(ctx->r14, ctx->r16);
    // 0x802C6920: addiu       $t7, $t2, 0x32
    ctx->r15 = ADD32(ctx->r10, 0X32);
    // 0x802C6924: sw          $t7, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r15;
    // 0x802C6928: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C692C: addiu       $t2, $zero, 0xFF
    ctx->r10 = ADD32(0, 0XFF);
    // 0x802C6930: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C6934: addiu       $t0, $zero, 0xFF
    ctx->r8 = ADD32(0, 0XFF);
    // 0x802C6938: addiu       $t1, $zero, 0xFF
    ctx->r9 = ADD32(0, 0XFF);
    // 0x802C693C: addiu       $t3, $zero, 0xFF
    ctx->r11 = ADD32(0, 0XFF);
    // 0x802C6940: addiu       $t5, $zero, 0xFF
    ctx->r13 = ADD32(0, 0XFF);
    // 0x802C6944: addiu       $t4, $zero, 0xFF
    ctx->r12 = ADD32(0, 0XFF);
    // 0x802C6948: sw          $t4, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r12;
    // 0x802C694C: sw          $t5, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r13;
    // 0x802C6950: sw          $t3, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r11;
    // 0x802C6954: sw          $t1, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r9;
    // 0x802C6958: sw          $t0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r8;
    // 0x802C695C: sw          $t6, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r14;
    // 0x802C6960: sw          $t2, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r10;
    // 0x802C6964: sw          $t7, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r15;
    // 0x802C6968: sw          $t9, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r25;
    // 0x802C696C: sw          $t9, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r25;
    // 0x802C6970: sw          $t8, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r24;
    // 0x802C6974: sw          $t8, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r24;
    // 0x802C6978: sw          $s5, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r21;
    // 0x802C697C: jal         0x801E92FC
    // 0x802C6980: addiu       $a3, $a3, 0x5
    ctx->r7 = ADD32(ctx->r7, 0X5);
    func_801E92FC(rdram, ctx);
        goto after_24;
    // 0x802C6980: addiu       $a3, $a3, 0x5
    ctx->r7 = ADD32(ctx->r7, 0X5);
    after_24:
    // 0x802C6984: lw          $t0, 0xC($s6)
    ctx->r8 = MEM_W(ctx->r22, 0XC);
    // 0x802C6988: lw          $a3, 0x8($s6)
    ctx->r7 = MEM_W(ctx->r22, 0X8);
    // 0x802C698C: addiu       $t5, $zero, 0xFF
    ctx->r13 = ADD32(0, 0XFF);
    // 0x802C6990: addu        $t1, $t0, $s0
    ctx->r9 = ADD32(ctx->r8, ctx->r16);
    // 0x802C6994: addiu       $t3, $t1, 0x36
    ctx->r11 = ADD32(ctx->r9, 0X36);
    // 0x802C6998: sw          $t3, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r11;
    // 0x802C699C: addiu       $t3, $zero, 0xFF
    ctx->r11 = ADD32(0, 0XFF);
    // 0x802C69A0: addiu       $t1, $zero, 0xFF
    ctx->r9 = ADD32(0, 0XFF);
    // 0x802C69A4: addiu       $t0, $zero, 0xFF
    ctx->r8 = ADD32(0, 0XFF);
    // 0x802C69A8: addiu       $t4, $zero, 0xFF
    ctx->r12 = ADD32(0, 0XFF);
    // 0x802C69AC: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C69B0: addiu       $t2, $zero, 0xFF
    ctx->r10 = ADD32(0, 0XFF);
    // 0x802C69B4: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C69B8: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C69BC: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C69C0: sw          $t9, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r25;
    // 0x802C69C4: sw          $t8, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r24;
    // 0x802C69C8: sw          $t7, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r15;
    // 0x802C69CC: sw          $t2, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r10;
    // 0x802C69D0: sw          $t6, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r14;
    // 0x802C69D4: sw          $t4, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r12;
    // 0x802C69D8: sw          $t4, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r12;
    // 0x802C69DC: sw          $t0, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r8;
    // 0x802C69E0: sw          $t1, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r9;
    // 0x802C69E4: sw          $t3, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r11;
    // 0x802C69E8: sw          $t5, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r13;
    // 0x802C69EC: sw          $t5, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r13;
    // 0x802C69F0: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    // 0x802C69F4: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C69F8: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C69FC: or          $a2, $s7, $zero
    ctx->r6 = ctx->r23 | 0;
    // 0x802C6A00: jal         0x801E92FC
    // 0x802C6A04: addiu       $a3, $a3, 0x54
    ctx->r7 = ADD32(ctx->r7, 0X54);
    func_801E92FC(rdram, ctx);
        goto after_25;
    // 0x802C6A04: addiu       $a3, $a3, 0x54
    ctx->r7 = ADD32(ctx->r7, 0X54);
    after_25:
    // 0x802C6A08: lw          $t6, 0x8($s6)
    ctx->r14 = MEM_W(ctx->r22, 0X8);
    // 0x802C6A0C: lw          $t2, 0xC($s6)
    ctx->r10 = MEM_W(ctx->r22, 0XC);
    // 0x802C6A10: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C6A14: addu        $a3, $t6, $s1
    ctx->r7 = ADD32(ctx->r14, ctx->r17);
    // 0x802C6A18: addu        $t7, $t2, $s0
    ctx->r15 = ADD32(ctx->r10, ctx->r16);
    // 0x802C6A1C: addiu       $t8, $t7, 0x32
    ctx->r24 = ADD32(ctx->r15, 0X32);
    // 0x802C6A20: sw          $t8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r24;
    // 0x802C6A24: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C6A28: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C6A2C: addiu       $t2, $zero, 0xFF
    ctx->r10 = ADD32(0, 0XFF);
    // 0x802C6A30: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C6A34: addiu       $t0, $zero, 0xFF
    ctx->r8 = ADD32(0, 0XFF);
    // 0x802C6A38: addiu       $t1, $zero, 0xFF
    ctx->r9 = ADD32(0, 0XFF);
    // 0x802C6A3C: addiu       $t3, $zero, 0xFF
    ctx->r11 = ADD32(0, 0XFF);
    // 0x802C6A40: addiu       $t5, $zero, 0xFF
    ctx->r13 = ADD32(0, 0XFF);
    // 0x802C6A44: addiu       $t4, $zero, 0xFF
    ctx->r12 = ADD32(0, 0XFF);
    // 0x802C6A48: sw          $t4, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r12;
    // 0x802C6A4C: sw          $t5, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r13;
    // 0x802C6A50: sw          $t3, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r11;
    // 0x802C6A54: sw          $t1, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r9;
    // 0x802C6A58: sw          $t0, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r8;
    // 0x802C6A5C: sw          $t0, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r8;
    // 0x802C6A60: sw          $t6, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r14;
    // 0x802C6A64: sw          $t2, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r10;
    // 0x802C6A68: sw          $t7, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r15;
    // 0x802C6A6C: sw          $t8, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r24;
    // 0x802C6A70: sw          $t9, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r25;
    // 0x802C6A74: sw          $t9, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r25;
    // 0x802C6A78: sw          $s2, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r18;
    // 0x802C6A7C: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C6A80: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C6A84: jal         0x801E92FC
    // 0x802C6A88: addiu       $a2, $sp, 0xD4
    ctx->r6 = ADD32(ctx->r29, 0XD4);
    func_801E92FC(rdram, ctx);
        goto after_26;
    // 0x802C6A88: addiu       $a2, $sp, 0xD4
    ctx->r6 = ADD32(ctx->r29, 0XD4);
    after_26:
    // 0x802C6A8C: lui         $t1, 0x800E
    ctx->r9 = S32(0X800E << 16);
    // 0x802C6A90: addiu       $t1, $t1, -0x5614
    ctx->r9 = ADD32(ctx->r9, -0X5614);
    // 0x802C6A94: addiu       $s3, $s3, 0x4
    ctx->r19 = ADD32(ctx->r19, 0X4);
    // 0x802C6A98: sltu        $at, $s3, $t1
    ctx->r1 = ctx->r19 < ctx->r9 ? 1 : 0;
    // 0x802C6A9C: addiu       $s0, $s0, 0x20
    ctx->r16 = ADD32(ctx->r16, 0X20);
    // 0x802C6AA0: bne         $at, $zero, L_802C67A8
    if (ctx->r1 != 0) {
        // 0x802C6AA4: or          $s4, $v0, $zero
        ctx->r20 = ctx->r2 | 0;
            goto L_802C67A8;
    }
    // 0x802C6AA4: or          $s4, $v0, $zero
    ctx->r20 = ctx->r2 | 0;
    // 0x802C6AA8: jal         0x80093AFC
    // 0x802C6AAC: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    func_80093AFC(rdram, ctx);
        goto after_27;
    // 0x802C6AAC: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    after_27:
    // 0x802C6AB0: lui         $t3, 0xFF10
    ctx->r11 = S32(0XFF10 << 16);
    // 0x802C6AB4: lui         $v1, 0xE700
    ctx->r3 = S32(0XE700 << 16);
    // 0x802C6AB8: ori         $t3, $t3, 0x1A7
    ctx->r11 = ctx->r11 | 0X1A7;
    // 0x802C6ABC: sw          $v1, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r3;
    // 0x802C6AC0: sw          $zero, 0x4($v0)
    MEM_W(0X4, ctx->r2) = 0;
    // 0x802C6AC4: sw          $t3, 0x8($v0)
    MEM_W(0X8, ctx->r2) = ctx->r11;
    // 0x802C6AC8: lui         $t5, 0x8015
    ctx->r13 = S32(0X8015 << 16);
    // 0x802C6ACC: lw          $t5, 0x1948($t5)
    ctx->r13 = MEM_W(ctx->r13, 0X1948);
    // 0x802C6AD0: lui         $t6, 0x8015
    ctx->r14 = S32(0X8015 << 16);
    // 0x802C6AD4: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x802C6AD8: sll         $t4, $t5, 2
    ctx->r12 = S32(ctx->r13 << 2);
    // 0x802C6ADC: addu        $t6, $t6, $t4
    ctx->r14 = ADD32(ctx->r14, ctx->r12);
    // 0x802C6AE0: lw          $t6, 0x42C0($t6)
    ctx->r14 = MEM_W(ctx->r14, 0X42C0);
    // 0x802C6AE4: lui         $t7, 0xB400
    ctx->r15 = S32(0XB400 << 16);
    // 0x802C6AE8: sw          $t7, 0x10($v0)
    MEM_W(0X10, ctx->r2) = ctx->r15;
    // 0x802C6AEC: addu        $t2, $t6, $at
    ctx->r10 = ADD32(ctx->r14, ctx->r1);
    // 0x802C6AF0: sw          $t2, 0xC($v0)
    MEM_W(0XC, ctx->r2) = ctx->r10;
    // 0x802C6AF4: lui         $t8, 0x802C
    ctx->r24 = S32(0X802C << 16);
    // 0x802C6AF8: lhu         $t8, 0x6F40($t8)
    ctx->r24 = MEM_HU(ctx->r24, 0X6F40);
    // 0x802C6AFC: lui         $t9, 0x103
    ctx->r25 = S32(0X103 << 16);
    // 0x802C6B00: ori         $t9, $t9, 0x40
    ctx->r25 = ctx->r25 | 0X40;
    // 0x802C6B04: sw          $t9, 0x18($v0)
    MEM_W(0X18, ctx->r2) = ctx->r25;
    // 0x802C6B08: sw          $t8, 0x14($v0)
    MEM_W(0X14, ctx->r2) = ctx->r24;
    // 0x802C6B0C: lw          $t0, 0x84($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X84);
    // 0x802C6B10: lui         $t1, 0x600
    ctx->r9 = S32(0X600 << 16);
    // 0x802C6B14: sw          $t1, 0x20($v0)
    MEM_W(0X20, ctx->r2) = ctx->r9;
    // 0x802C6B18: sw          $t0, 0x1C($v0)
    MEM_W(0X1C, ctx->r2) = ctx->r8;
    // 0x802C6B1C: lw          $t3, 0x80($sp)
    ctx->r11 = MEM_W(ctx->r29, 0X80);
    // 0x802C6B20: lui         $t5, 0xED02
    ctx->r13 = S32(0XED02 << 16);
    // 0x802C6B24: addiu       $t5, $t5, 0x50
    ctx->r13 = ADD32(ctx->r13, 0X50);
    // 0x802C6B28: lui         $t4, 0x68
    ctx->r12 = S32(0X68 << 16);
    // 0x802C6B2C: addiu       $t4, $t4, -0x3C94
    ctx->r12 = ADD32(ctx->r12, -0X3C94);
    // 0x802C6B30: lui         $s3, 0x800E
    ctx->r19 = S32(0X800E << 16);
    // 0x802C6B34: lui         $s0, 0x700
    ctx->r16 = S32(0X700 << 16);
    // 0x802C6B38: lui         $s1, 0x700
    ctx->r17 = S32(0X700 << 16);
    // 0x802C6B3C: sw          $zero, 0x2C($v0)
    MEM_W(0X2C, ctx->r2) = 0;
    // 0x802C6B40: sw          $v1, 0x28($v0)
    MEM_W(0X28, ctx->r2) = ctx->r3;
    { extern uint32_t wr64_experimental_viewport_borders(void); if (wr64_experimental_viewport_borders()) { ctx->r13 = 0xED000000U; ctx->r12 = 0x006A03C0U; } }
    // 0x802C6B44: sw          $t4, 0x34($v0)
    MEM_W(0X34, ctx->r2) = ctx->r12;
    // 0x802C6B48: sw          $t5, 0x30($v0)
    MEM_W(0X30, ctx->r2) = ctx->r13;
    // 0x802C6B4C: addiu       $s4, $v0, 0x38
    ctx->r20 = ADD32(ctx->r2, 0X38);
    // 0x802C6B50: addiu       $s1, $s1, 0xA80
    ctx->r17 = ADD32(ctx->r17, 0XA80);
    // 0x802C6B54: addiu       $s0, $s0, 0x1280
    ctx->r16 = ADD32(ctx->r16, 0X1280);
    // 0x802C6B58: addiu       $s3, $s3, -0x5624
    ctx->r19 = ADD32(ctx->r19, -0X5624);
    // 0x802C6B5C: or          $s5, $zero, $zero
    ctx->r21 = 0 | 0;
    // 0x802C6B60: or          $s2, $zero, $zero
    ctx->r18 = 0 | 0;
    // 0x802C6B64: sw          $t3, 0x24($v0)
    MEM_W(0X24, ctx->r2) = ctx->r11;
L_802C6B68:
    // 0x802C6B68: or          $v0, $s4, $zero
    ctx->r2 = ctx->r20 | 0;
    // 0x802C6B6C: lui         $t6, 0x380
    ctx->r14 = S32(0X380 << 16);
    // 0x802C6B70: ori         $t6, $t6, 0x10
    ctx->r14 = ctx->r14 | 0X10;
    // 0x802C6B74: sw          $t6, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r14;
    // 0x802C6B78: sw          $s0, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r16;
    // 0x802C6B7C: addiu       $v1, $s4, 0x8
    ctx->r3 = ADD32(ctx->r20, 0X8);
    // 0x802C6B80: lui         $t2, 0x102
    ctx->r10 = S32(0X102 << 16);
    // 0x802C6B84: ori         $t2, $t2, 0x40
    ctx->r10 = ctx->r10 | 0X40;
    // 0x802C6B88: sw          $t2, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r10;
    // 0x802C6B8C: sw          $s1, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r17;
    // 0x802C6B90: lui         $t7, 0x801D
    ctx->r15 = S32(0X801D << 16);
    // 0x802C6B94: lw          $t7, -0x1A08($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X1A08);
    // 0x802C6B98: addiu       $a0, $v1, 0x8
    ctx->r4 = ADD32(ctx->r3, 0X8);
    // 0x802C6B9C: lw          $a1, 0x0($s3)
    ctx->r5 = MEM_W(ctx->r19, 0X0);
    // 0x802C6BA0: addu        $t8, $t7, $s2
    ctx->r24 = ADD32(ctx->r15, ctx->r18);
    // 0x802C6BA4: addiu       $t9, $t8, 0xC80
    ctx->r25 = ADD32(ctx->r24, 0XC80);
    // 0x802C6BA8: sw          $t9, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r25;
    // 0x802C6BAC: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x802C6BB0: jal         0x801E4FE8
    // 0x802C6BB4: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_801E4FE8(rdram, ctx);
        goto after_28;
    // 0x802C6BB4: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_28:
    // 0x802C6BB8: addiu       $s5, $s5, 0x1
    ctx->r21 = ADD32(ctx->r21, 0X1);
    // 0x802C6BBC: addiu       $at, $zero, 0x4
    ctx->r1 = ADD32(0, 0X4);
    // 0x802C6BC0: addiu       $s3, $s3, 0x4
    ctx->r19 = ADD32(ctx->r19, 0X4);
    // 0x802C6BC4: addiu       $s0, $s0, 0x10
    ctx->r16 = ADD32(ctx->r16, 0X10);
    // 0x802C6BC8: addiu       $s1, $s1, 0x40
    ctx->r17 = ADD32(ctx->r17, 0X40);
    // 0x802C6BCC: addiu       $s2, $s2, 0xC0
    ctx->r18 = ADD32(ctx->r18, 0XC0);
    // 0x802C6BD0: bne         $s5, $at, L_802C6B68
    if (ctx->r21 != ctx->r1) {
        // 0x802C6BD4: or          $s4, $v0, $zero
        ctx->r20 = ctx->r2 | 0;
            goto L_802C6B68;
    }
    // 0x802C6BD4: or          $s4, $v0, $zero
    ctx->r20 = ctx->r2 | 0;
L_802C6BD8:
    { extern void wr64_ending_hud_draw(uint8_t*, uint32_t, uint32_t, uint32_t); wr64_ending_hud_draw(rdram, (uint32_t)ctx->r22, wr64EndingHudBegin, (uint32_t)ctx->r20); }
    // 0x802C6BD8: addiu       $s5, $s5, 0x1
    ctx->r21 = ADD32(ctx->r21, 0X1);
L_802C6BDC:
    // 0x802C6BDC: slti        $at, $s5, 0xA
    ctx->r1 = SIGNED(ctx->r21) < 0XA ? 1 : 0;
    // 0x802C6BE0: bne         $at, $zero, L_802C6068
    if (ctx->r1 != 0) {
        // 0x802C6BE4: addiu       $s6, $s6, 0x10
        ctx->r22 = ADD32(ctx->r22, 0X10);
            goto L_802C6068;
    }
    // 0x802C6BE4: addiu       $s6, $s6, 0x10
    ctx->r22 = ADD32(ctx->r22, 0X10);
    // 0x802C6BE8: lw          $ra, 0x74($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X74);
    // 0x802C6BEC: or          $v0, $s4, $zero
    ctx->r2 = ctx->r20 | 0;
    // 0x802C6BF0: lw          $s4, 0x60($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X60);
    // 0x802C6BF4: lw          $s0, 0x50($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X50);
    // 0x802C6BF8: lw          $s1, 0x54($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X54);
    // 0x802C6BFC: lw          $s2, 0x58($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X58);
    // 0x802C6C00: lw          $s3, 0x5C($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X5C);
    // 0x802C6C04: lw          $s5, 0x64($sp)
    ctx->r21 = MEM_W(ctx->r29, 0X64);
    // 0x802C6C08: lw          $s6, 0x68($sp)
    ctx->r22 = MEM_W(ctx->r29, 0X68);
    // 0x802C6C0C: lw          $s7, 0x6C($sp)
    ctx->r23 = MEM_W(ctx->r29, 0X6C);
    // 0x802C6C10: lw          $fp, 0x70($sp)
    ctx->r30 = MEM_W(ctx->r29, 0X70);
    // 0x802C6C14: jr          $ra
    // 0x802C6C18: addiu       $sp, $sp, 0x130
    ctx->r29 = ADD32(ctx->r29, 0X130);
    return;
    // 0x802C6C18: addiu       $sp, $sp, 0x130
    ctx->r29 = ADD32(ctx->r29, 0X130);
;}
RECOMP_FUNC void func_i15_802C6C1C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C6C1C: lui         $t6, 0x802C
    ctx->r14 = S32(0X802C << 16);
    // 0x802C6C20: lw          $t6, 0x6DF4($t6)
    ctx->r14 = MEM_W(ctx->r14, 0X6DF4);
    // 0x802C6C24: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x802C6C28: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x802C6C2C: beq         $t6, $zero, L_802C6C9C
    if (ctx->r14 == 0) {
        // 0x802C6C30: lui         $v0, 0x802C
        ctx->r2 = S32(0X802C << 16);
            goto L_802C6C9C;
    }
    // 0x802C6C30: lui         $v0, 0x802C
    ctx->r2 = S32(0X802C << 16);
    // 0x802C6C34: addiu       $v0, $v0, 0x6DF8
    ctx->r2 = ADD32(ctx->r2, 0X6DF8);
    // 0x802C6C38: lw          $t7, 0x0($v0)
    ctx->r15 = MEM_W(ctx->r2, 0X0);
    // 0x802C6C3C: lui         $t9, 0x801D
    ctx->r25 = S32(0X801D << 16);
    // 0x802C6C40: lui         $t2, 0x802C
    ctx->r10 = S32(0X802C << 16);
    // 0x802C6C44: addiu       $t8, $t7, 0x1
    ctx->r24 = ADD32(ctx->r15, 0X1);
    // 0x802C6C48: sw          $t8, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r24;
    // 0x802C6C4C: lhu         $t9, -0x19A6($t9)
    ctx->r25 = MEM_HU(ctx->r25, -0X19A6);
    // 0x802C6C50: slti        $at, $t8, 0x259
    ctx->r1 = SIGNED(ctx->r24) < 0X259 ? 1 : 0;
    // 0x802C6C54: andi        $t0, $t9, 0xB000
    ctx->r8 = ctx->r25 & 0XB000;
    // 0x802C6C58: bne         $t0, $zero, L_802C6C68
    if (ctx->r8 != 0) {
        // 0x802C6C5C: nop
    
            goto L_802C6C68;
    }
    // 0x802C6C5C: nop

    // 0x802C6C60: bnel        $at, $zero, L_802C6CA0
    if (ctx->r1 != 0) {
        // 0x802C6C64: lw          $ra, 0x14($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X14);
            goto L_802C6CA0;
    }
    goto skip_0;
    // 0x802C6C64: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    skip_0:
L_802C6C68:
    // 0x802C6C68: lw          $t2, 0x6E74($t2)
    ctx->r10 = MEM_W(ctx->r10, 0X6E74);
    // 0x802C6C6C: lui         $t3, 0x802C
    ctx->r11 = S32(0X802C << 16);
    // 0x802C6C70: bne         $t2, $zero, L_802C6C84
    if (ctx->r10 != 0) {
        // 0x802C6C74: nop
    
            goto L_802C6C84;
    }
    // 0x802C6C74: nop

    // 0x802C6C78: lw          $t3, 0x6E78($t3)
    ctx->r11 = MEM_W(ctx->r11, 0X6E78);
    // 0x802C6C7C: beq         $t3, $zero, L_802C6C94
    if (ctx->r11 == 0) {
        // 0x802C6C80: nop
    
            goto L_802C6C94;
    }
    // 0x802C6C80: nop

L_802C6C84:
    // 0x802C6C84: jal         0x802C6CAC
    // 0x802C6C88: addiu       $a0, $zero, 0x64
    ctx->r4 = ADD32(0, 0X64);
    func_i15_802C6CAC(rdram, ctx);
        goto after_0;
    // 0x802C6C88: addiu       $a0, $zero, 0x64
    ctx->r4 = ADD32(0, 0X64);
    after_0:
    // 0x802C6C8C: b           L_802C6CA0
    // 0x802C6C90: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_802C6CA0;
    // 0x802C6C90: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C6C94:
    // 0x802C6C94: jal         0x802C6CAC
    // 0x802C6C98: addiu       $a0, $zero, 0x2
    ctx->r4 = ADD32(0, 0X2);
    func_i15_802C6CAC(rdram, ctx);
        goto after_1;
    // 0x802C6C98: addiu       $a0, $zero, 0x2
    ctx->r4 = ADD32(0, 0X2);
    after_1:
L_802C6C9C:
    // 0x802C6C9C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C6CA0:
    // 0x802C6CA0: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x802C6CA4: jr          $ra
    // 0x802C6CA8: nop

    return;
    // 0x802C6CA8: nop

;}
RECOMP_FUNC void func_i15_802C6CAC(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C6CAC: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x802C6CB0: addiu       $v0, $v0, -0x54DC
    ctx->r2 = ADD32(ctx->r2, -0X54DC);
    // 0x802C6CB4: lw          $t6, 0x0($v0)
    ctx->r14 = MEM_W(ctx->r2, 0X0);
    // 0x802C6CB8: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C6CBC: addiu       $t7, $zero, 0x67
    ctx->r15 = ADD32(0, 0X67);
    // 0x802C6CC0: sw          $t6, -0x19CC($at)
    MEM_W(-0X19CC, ctx->r1) = ctx->r14;
    // 0x802C6CC4: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C6CC8: sw          $a0, -0x19D0($at)
    MEM_W(-0X19D0, ctx->r1) = ctx->r4;
    // 0x802C6CCC: sw          $t7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r15;
    // 0x802C6CD0: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C6CD4: addiu       $t8, $zero, 0x15
    ctx->r24 = ADD32(0, 0X15);
    // 0x802C6CD8: sw          $t8, -0x19C8($at)
    MEM_W(-0X19C8, ctx->r1) = ctx->r24;
    // 0x802C6CDC: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C6CE0: addiu       $t9, $zero, 0x1
    ctx->r25 = ADD32(0, 0X1);
    // 0x802C6CE4: sw          $t9, -0x19C4($at)
    MEM_W(-0X19C4, ctx->r1) = ctx->r25;
    // 0x802C6CE8: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C6CEC: sw          $zero, -0x19C0($at)
    MEM_W(-0X19C0, ctx->r1) = 0;
    // 0x802C6CF0: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C6CF4: sw          $zero, -0x19BC($at)
    MEM_W(-0X19BC, ctx->r1) = 0;
    // 0x802C6CF8: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x802C6CFC: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x802C6D00: sw          $zero, -0x54E4($at)
    MEM_W(-0X54E4, ctx->r1) = 0;
    // 0x802C6D04: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x802C6D08: lui         $at, 0x800D
    ctx->r1 = S32(0X800D << 16);
    // 0x802C6D0C: addiu       $t0, $zero, 0x3
    ctx->r8 = ADD32(0, 0X3);
    // 0x802C6D10: sw          $t0, 0x461C($at)
    MEM_W(0X461C, ctx->r1) = ctx->r8;
    // 0x802C6D14: addiu       $a0, $zero, 0x3
    ctx->r4 = ADD32(0, 0X3);
    // 0x802C6D18: addiu       $a1, $zero, 0x14
    ctx->r5 = ADD32(0, 0X14);
    // 0x802C6D1C: jal         0x801E6FB0
    // 0x802C6D20: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    FadeTransition_SetProps(rdram, ctx);
        goto after_0;
    // 0x802C6D20: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    after_0:
    // 0x802C6D24: lui         $t1, 0x801D
    ctx->r9 = S32(0X801D << 16);
    // 0x802C6D28: lw          $t1, -0x19D0($t1)
    ctx->r9 = MEM_W(ctx->r9, -0X19D0);
    // 0x802C6D2C: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x802C6D30: bnel        $t1, $at, L_802C6D44
    if (ctx->r9 != ctx->r1) {
        // 0x802C6D34: lw          $ra, 0x14($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X14);
            goto L_802C6D44;
    }
    goto skip_0;
    // 0x802C6D34: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    skip_0:
    // 0x802C6D38: jal         0x800C1F60
    // 0x802C6D3C: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    func_800C1F60(rdram, ctx);
        goto after_1;
    // 0x802C6D3C: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    after_1:
    // 0x802C6D40: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C6D44:
    // 0x802C6D44: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x802C6D48: jr          $ra
    // 0x802C6D4C: nop

    return;
    // 0x802C6D4C: nop

;}
