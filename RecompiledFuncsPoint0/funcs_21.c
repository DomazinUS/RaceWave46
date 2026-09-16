#include "recomp.h"
#include "funcs.h"

RECOMP_FUNC void func_i1_802C6B00(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C6B00: lui         $t6, 0x8023
    ctx->r14 = S32(0X8023 << 16);
    // 0x802C6B04: lh          $t6, -0x75EA($t6)
    ctx->r14 = MEM_H(ctx->r14, -0X75EA);
    // 0x802C6B08: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x802C6B0C: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x802C6B10: bne         $t6, $at, L_802C6B28
    if (ctx->r14 != ctx->r1) {
        // 0x802C6B14: sw          $ra, 0x14($sp)
        MEM_W(0X14, ctx->r29) = ctx->r31;
            goto L_802C6B28;
    }
    // 0x802C6B14: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x802C6B18: jal         0x800AD3C4
    // 0x802C6B1C: nop

    func_800AD3C4(rdram, ctx);
        goto after_0;
    // 0x802C6B1C: nop

    after_0:
    // 0x802C6B20: jal         0x801ECE50
    // 0x802C6B24: nop

    func_801ECE50(rdram, ctx);
        goto after_1;
    // 0x802C6B24: nop

    after_1:
L_802C6B28:
    // 0x802C6B28: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x802C6B2C: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x802C6B30: jr          $ra
    // 0x802C6B34: nop

    return;
    // 0x802C6B34: nop

;}
RECOMP_FUNC void func_i1_802C6B38(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C6B38: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x802C6B3C: lw          $v0, -0x54DC($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X54DC);
    // 0x802C6B40: addiu       $at, $zero, 0x2A
    ctx->r1 = ADD32(0, 0X2A);
    // 0x802C6B44: lui         $t6, 0x801D
    ctx->r14 = S32(0X801D << 16);
    // 0x802C6B48: bnel        $v0, $at, L_802C6B6C
    if (ctx->r2 != ctx->r1) {
        // 0x802C6B4C: addiu       $at, $zero, 0x29
        ctx->r1 = ADD32(0, 0X29);
            goto L_802C6B6C;
    }
    goto skip_0;
    // 0x802C6B4C: addiu       $at, $zero, 0x29
    ctx->r1 = ADD32(0, 0X29);
    skip_0:
    // 0x802C6B50: lh          $t6, -0x1910($t6)
    ctx->r14 = MEM_H(ctx->r14, -0X1910);
    // 0x802C6B54: addiu       $v1, $zero, 0x1
    ctx->r3 = ADD32(0, 0X1);
    // 0x802C6B58: bne         $v1, $t6, L_802C6BD0
    if (ctx->r3 != ctx->r14) {
        // 0x802C6B5C: nop
    
            goto L_802C6BD0;
    }
    // 0x802C6B5C: nop

    // 0x802C6B60: jr          $ra
    // 0x802C6B64: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    return;
    // 0x802C6B64: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x802C6B68: addiu       $at, $zero, 0x29
    ctx->r1 = ADD32(0, 0X29);
L_802C6B6C:
    // 0x802C6B6C: bne         $v0, $at, L_802C6BD0
    if (ctx->r2 != ctx->r1) {
        // 0x802C6B70: lui         $a1, 0x802D
        ctx->r5 = S32(0X802D << 16);
            goto L_802C6BD0;
    }
    // 0x802C6B70: lui         $a1, 0x802D
    ctx->r5 = S32(0X802D << 16);
    // 0x802C6B74: addiu       $a1, $a1, -0x695C
    ctx->r5 = ADD32(ctx->r5, -0X695C);
    // 0x802C6B78: lw          $v0, 0x0($a1)
    ctx->r2 = MEM_W(ctx->r5, 0X0);
    // 0x802C6B7C: addiu       $v1, $zero, 0x1
    ctx->r3 = ADD32(0, 0X1);
    // 0x802C6B80: lui         $t7, 0x801D
    ctx->r15 = S32(0X801D << 16);
    // 0x802C6B84: slti        $at, $v0, 0x1E
    ctx->r1 = SIGNED(ctx->r2) < 0X1E ? 1 : 0;
    // 0x802C6B88: beq         $at, $zero, L_802C6BAC
    if (ctx->r1 == 0) {
        // 0x802C6B8C: addiu       $t8, $v0, 0x1
        ctx->r24 = ADD32(ctx->r2, 0X1);
            goto L_802C6BAC;
    }
    // 0x802C6B8C: addiu       $t8, $v0, 0x1
    ctx->r24 = ADD32(ctx->r2, 0X1);
    // 0x802C6B90: lh          $t7, -0x1910($t7)
    ctx->r15 = MEM_H(ctx->r15, -0X1910);
    // 0x802C6B94: addiu       $v1, $zero, 0x1
    ctx->r3 = ADD32(0, 0X1);
    // 0x802C6B98: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x802C6B9C: bne         $v1, $t7, L_802C6BAC
    if (ctx->r3 != ctx->r15) {
        // 0x802C6BA0: sw          $v1, -0x7E84($at)
        MEM_W(-0X7E84, ctx->r1) = ctx->r3;
            goto L_802C6BAC;
    }
    // 0x802C6BA0: sw          $v1, -0x7E84($at)
    MEM_W(-0X7E84, ctx->r1) = ctx->r3;
    // 0x802C6BA4: b           L_802C6BB0
    // 0x802C6BA8: slti        $at, $t8, 0x3D
    ctx->r1 = SIGNED(ctx->r24) < 0X3D ? 1 : 0;
        goto L_802C6BB0;
    // 0x802C6BA8: slti        $at, $t8, 0x3D
    ctx->r1 = SIGNED(ctx->r24) < 0X3D ? 1 : 0;
L_802C6BAC:
    // 0x802C6BAC: slti        $at, $t8, 0x3D
    ctx->r1 = SIGNED(ctx->r24) < 0X3D ? 1 : 0;
L_802C6BB0:
    // 0x802C6BB0: bne         $at, $zero, L_802C6BD0
    if (ctx->r1 != 0) {
        // 0x802C6BB4: sw          $t8, 0x0($a1)
        MEM_W(0X0, ctx->r5) = ctx->r24;
            goto L_802C6BD0;
    }
    // 0x802C6BB4: sw          $t8, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r24;
    // 0x802C6BB8: lui         $v0, 0x802D
    ctx->r2 = S32(0X802D << 16);
    // 0x802C6BBC: addiu       $v0, $v0, -0x6960
    ctx->r2 = ADD32(ctx->r2, -0X6960);
    // 0x802C6BC0: lw          $t0, 0x0($v0)
    ctx->r8 = MEM_W(ctx->r2, 0X0);
    // 0x802C6BC4: bne         $t0, $zero, L_802C6BD0
    if (ctx->r8 != 0) {
        // 0x802C6BC8: nop
    
            goto L_802C6BD0;
    }
    // 0x802C6BC8: nop

    // 0x802C6BCC: sw          $v1, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r3;
L_802C6BD0:
    // 0x802C6BD0: jr          $ra
    // 0x802C6BD4: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    return;
    // 0x802C6BD4: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
;}
RECOMP_FUNC void func_i1_802C6BD8(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C6BD8: addiu       $sp, $sp, -0x58
    ctx->r29 = ADD32(ctx->r29, -0X58);
    // 0x802C6BDC: sw          $ra, 0x54($sp)
    MEM_W(0X54, ctx->r29) = ctx->r31;
    // 0x802C6BE0: sw          $s5, 0x50($sp)
    MEM_W(0X50, ctx->r29) = ctx->r21;
    // 0x802C6BE4: sw          $s4, 0x4C($sp)
    MEM_W(0X4C, ctx->r29) = ctx->r20;
    // 0x802C6BE8: sw          $s3, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r19;
    // 0x802C6BEC: sw          $s2, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r18;
    // 0x802C6BF0: sw          $s1, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r17;
    // 0x802C6BF4: sw          $s0, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r16;
    // 0x802C6BF8: lui         $t7, 0x107
    ctx->r15 = S32(0X107 << 16);
    // 0x802C6BFC: addiu       $t7, $t7, -0x9D8
    ctx->r15 = ADD32(ctx->r15, -0X9D8);
    // 0x802C6C00: lui         $t6, 0x600
    ctx->r14 = S32(0X600 << 16);
    // 0x802C6C04: sw          $t6, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r14;
    // 0x802C6C08: sw          $t7, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r15;
    // 0x802C6C0C: addiu       $s2, $a0, 0x8
    ctx->r18 = ADD32(ctx->r4, 0X8);
    // 0x802C6C10: addiu       $t8, $zero, 0x17C
    ctx->r24 = ADD32(0, 0X17C);
    // 0x802C6C14: addiu       $t9, $zero, 0x14
    ctx->r25 = ADD32(0, 0X14);
    // 0x802C6C18: sw          $t9, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r25;
    // 0x802C6C1C: sw          $t8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r24;
    // 0x802C6C20: or          $a0, $s2, $zero
    ctx->r4 = ctx->r18 | 0;
    // 0x802C6C24: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C6C28: addiu       $a2, $zero, 0x16
    ctx->r6 = ADD32(0, 0X16);
    // 0x802C6C2C: jal         0x80094338
    // 0x802C6C30: addiu       $a3, $zero, 0xC5
    ctx->r7 = ADD32(0, 0XC5);
    func_80094338(rdram, ctx);
        goto after_0;
    // 0x802C6C30: addiu       $a3, $zero, 0xC5
    ctx->r7 = ADD32(0, 0XC5);
    after_0:
    // 0x802C6C34: lui         $s0, 0x802D
    ctx->r16 = S32(0X802D << 16);
    // 0x802C6C38: addiu       $s0, $s0, -0x6958
    ctx->r16 = ADD32(ctx->r16, -0X6958);
    // 0x802C6C3C: lw          $t0, 0x0($s0)
    ctx->r8 = MEM_W(ctx->r16, 0X0);
    // 0x802C6C40: or          $s2, $v0, $zero
    ctx->r18 = ctx->r2 | 0;
    // 0x802C6C44: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C6C48: beq         $t0, $zero, L_802C6D78
    if (ctx->r8 == 0) {
        // 0x802C6C4C: or          $a1, $zero, $zero
        ctx->r5 = 0 | 0;
            goto L_802C6D78;
    }
    // 0x802C6C4C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C6C50: addiu       $t1, $zero, 0xFF
    ctx->r9 = ADD32(0, 0XFF);
    // 0x802C6C54: addiu       $t2, $zero, 0xFF
    ctx->r10 = ADD32(0, 0XFF);
    // 0x802C6C58: addiu       $t3, $zero, 0xFF
    ctx->r11 = ADD32(0, 0XFF);
    // 0x802C6C5C: addiu       $t4, $zero, 0xFF
    ctx->r12 = ADD32(0, 0XFF);
    // 0x802C6C60: addiu       $t5, $zero, 0xFF
    ctx->r13 = ADD32(0, 0XFF);
    // 0x802C6C64: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C6C68: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C6C6C: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C6C70: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C6C74: addiu       $t0, $zero, 0xFF
    ctx->r8 = ADD32(0, 0XFF);
    // 0x802C6C78: sw          $t0, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r8;
    // 0x802C6C7C: sw          $t9, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r25;
    // 0x802C6C80: sw          $t8, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r24;
    // 0x802C6C84: sw          $t7, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r15;
    // 0x802C6C88: sw          $t6, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r14;
    // 0x802C6C8C: sw          $t5, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r13;
    // 0x802C6C90: sw          $t4, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r12;
    // 0x802C6C94: sw          $t3, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r11;
    // 0x802C6C98: sw          $t2, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r10;
    // 0x802C6C9C: sw          $t1, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r9;
    // 0x802C6CA0: addiu       $a2, $zero, 0xFF
    ctx->r6 = ADD32(0, 0XFF);
    // 0x802C6CA4: jal         0x801E946C
    // 0x802C6CA8: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    func_801E946C(rdram, ctx);
        goto after_1;
    // 0x802C6CA8: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    after_1:
    // 0x802C6CAC: lui         $t2, 0xED08
    ctx->r10 = S32(0XED08 << 16);
    // 0x802C6CB0: addiu       $t2, $t2, -0x7FB0
    ctx->r10 = ADD32(ctx->r10, -0X7FB0);
    // 0x802C6CB4: lui         $t3, 0x63
    ctx->r11 = S32(0X63 << 16);
    // 0x802C6CB8: addiu       $t3, $t3, -0x7C98
    ctx->r11 = ADD32(ctx->r11, -0X7C98);
    // 0x802C6CBC: ori         $t2, $t2, 0x8050
    ctx->r10 = ctx->r10 | 0X8050;
    // 0x802C6CC0: sw          $t1, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r9;
    // 0x802C6CC4: sw          $zero, 0x4($v0)
    MEM_W(0X4, ctx->r2) = 0;
    // 0x802C6CC8: sw          $t2, 0x8($v0)
    MEM_W(0X8, ctx->r2) = ctx->r10;
    // 0x802C6CCC: sw          $t3, 0xC($v0)
    MEM_W(0XC, ctx->r2) = ctx->r11;
    // 0x802C6CD0: lw          $t4, 0x4($s0)
    ctx->r12 = MEM_W(ctx->r16, 0X4);
    // 0x802C6CD4: addiu       $s2, $v0, 0x10
    ctx->r18 = ADD32(ctx->r2, 0X10);
    // 0x802C6CD8: or          $s4, $s0, $zero
    ctx->r20 = ctx->r16 | 0;
    // 0x802C6CDC: blez        $t4, L_802C6D54
    if (SIGNED(ctx->r12) <= 0) {
        // 0x802C6CE0: or          $s1, $zero, $zero
        ctx->r17 = 0 | 0;
            goto L_802C6D54;
    }
    // 0x802C6CE0: or          $s1, $zero, $zero
    ctx->r17 = 0 | 0;
    // 0x802C6CE4: lui         $s0, 0x802D
    ctx->r16 = S32(0X802D << 16);
    // 0x802C6CE8: lui         $s5, 0x801D
    ctx->r21 = S32(0X801D << 16);
    // 0x802C6CEC: addiu       $s5, $s5, -0x19DC
    ctx->r21 = ADD32(ctx->r21, -0X19DC);
    // 0x802C6CF0: addiu       $s0, $s0, -0x6958
    ctx->r16 = ADD32(ctx->r16, -0X6958);
    // 0x802C6CF4: addiu       $s3, $zero, -0x1
    ctx->r19 = ADD32(0, -0X1);
    // 0x802C6CF8: lw          $a2, 0x18($s0)
    ctx->r6 = MEM_W(ctx->r16, 0X18);
L_802C6CFC:
    // 0x802C6CFC: or          $a0, $s2, $zero
    ctx->r4 = ctx->r18 | 0;
    // 0x802C6D00: addiu       $a1, $zero, 0x3
    ctx->r5 = ADD32(0, 0X3);
    // 0x802C6D04: beq         $s3, $a2, L_802C6D3C
    if (ctx->r19 == ctx->r6) {
        // 0x802C6D08: addiu       $t8, $zero, 0xC8
        ctx->r24 = ADD32(0, 0XC8);
            goto L_802C6D3C;
    }
    // 0x802C6D08: addiu       $t8, $zero, 0xC8
    ctx->r24 = ADD32(0, 0XC8);
    // 0x802C6D0C: lh          $t5, 0x0($s5)
    ctx->r13 = MEM_H(ctx->r21, 0X0);
    // 0x802C6D10: bnel        $s3, $t5, L_802C6D2C
    if (ctx->r19 != ctx->r13) {
        // 0x802C6D14: lw          $a3, 0xC($s0)
        ctx->r7 = MEM_W(ctx->r16, 0XC);
            goto L_802C6D2C;
    }
    goto skip_0;
    // 0x802C6D14: lw          $a3, 0xC($s0)
    ctx->r7 = MEM_W(ctx->r16, 0XC);
    skip_0:
    // 0x802C6D18: lw          $t6, 0xC($s0)
    ctx->r14 = MEM_W(ctx->r16, 0XC);
    // 0x802C6D1C: lw          $a2, 0x18($s0)
    ctx->r6 = MEM_W(ctx->r16, 0X18);
    // 0x802C6D20: addiu       $t7, $t6, -0x2
    ctx->r15 = ADD32(ctx->r14, -0X2);
    // 0x802C6D24: sw          $t7, 0xC($s0)
    MEM_W(0XC, ctx->r16) = ctx->r15;
    // 0x802C6D28: lw          $a3, 0xC($s0)
    ctx->r7 = MEM_W(ctx->r16, 0XC);
L_802C6D2C:
    // 0x802C6D2C: sw          $t8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r24;
    // 0x802C6D30: jal         0x801E3EE0
    // 0x802C6D34: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    func_801E3EE0(rdram, ctx);
        goto after_2;
    // 0x802C6D34: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    after_2:
    { extern void wr64_hud_park_draw(uint8_t*, uint32_t, uint32_t, uint32_t); wr64_hud_park_draw(rdram, (uint32_t)ctx->r17, (uint32_t)ctx->r18, (uint32_t)ctx->r2); }
    // 0x802C6D38: or          $s2, $v0, $zero
    ctx->r18 = ctx->r2 | 0;
L_802C6D3C:
    // 0x802C6D3C: lw          $t9, 0x4($s4)
    ctx->r25 = MEM_W(ctx->r20, 0X4);
    // 0x802C6D40: addiu       $s1, $s1, 0x1
    ctx->r17 = ADD32(ctx->r17, 0X1);
    // 0x802C6D44: addiu       $s0, $s0, 0x4
    ctx->r16 = ADD32(ctx->r16, 0X4);
    // 0x802C6D48: slt         $at, $s1, $t9
    ctx->r1 = SIGNED(ctx->r17) < SIGNED(ctx->r25) ? 1 : 0;
    // 0x802C6D4C: bnel        $at, $zero, L_802C6CFC
    if (ctx->r1 != 0) {
        // 0x802C6D50: lw          $a2, 0x18($s0)
        ctx->r6 = MEM_W(ctx->r16, 0X18);
            goto L_802C6CFC;
    }
    goto skip_1;
    // 0x802C6D50: lw          $a2, 0x18($s0)
    ctx->r6 = MEM_W(ctx->r16, 0X18);
    skip_1:
L_802C6D54:
    // 0x802C6D54: lui         $t1, 0x802D
    ctx->r9 = S32(0X802D << 16);
    // 0x802C6D58: lw          $t1, -0x6950($t1)
    ctx->r9 = MEM_W(ctx->r9, -0X6950);
    // 0x802C6D5C: lui         $t0, 0x802D
    ctx->r8 = S32(0X802D << 16);
    // 0x802C6D60: lw          $t0, -0x694C($t0)
    ctx->r8 = MEM_W(ctx->r8, -0X694C);
    // 0x802C6D64: negu        $t2, $t1
    ctx->r10 = SUB32(0, ctx->r9);
    // 0x802C6D68: slt         $at, $t0, $t2
    ctx->r1 = SIGNED(ctx->r8) < SIGNED(ctx->r10) ? 1 : 0;
    // 0x802C6D6C: beq         $at, $zero, L_802C6D78
    if (ctx->r1 == 0) {
        // 0x802C6D70: lui         $at, 0x802D
        ctx->r1 = S32(0X802D << 16);
            goto L_802C6D78;
    }
    // 0x802C6D70: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C6D74: sw          $zero, -0x6958($at)
    MEM_W(-0X6958, ctx->r1) = 0;
L_802C6D78:
    // 0x802C6D78: or          $v1, $s2, $zero
    ctx->r3 = ctx->r18 | 0;
    // 0x802C6D7C: addiu       $s2, $s2, 0x8
    ctx->r18 = ADD32(ctx->r18, 0X8);
    // 0x802C6D80: lui         $t3, 0xE700
    ctx->r11 = S32(0XE700 << 16);
    // 0x802C6D84: sw          $t3, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r11;
    // 0x802C6D88: sw          $zero, 0x4($v1)
    MEM_W(0X4, ctx->r3) = 0;
    // 0x802C6D8C: or          $a0, $s2, $zero
    ctx->r4 = ctx->r18 | 0;
    // 0x802C6D90: lui         $t5, 0x6A
    ctx->r13 = S32(0X6A << 16);
    // 0x802C6D94: addiu       $t5, $t5, -0x3C44
    ctx->r13 = ADD32(ctx->r13, -0X3C44);
    // 0x802C6D98: lui         $t4, 0xED00
    ctx->r12 = S32(0XED00 << 16);
    // 0x802C6D9C: sw          $t4, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r12;
    // 0x802C6DA0: sw          $t5, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r13;
    // 0x802C6DA4: lw          $ra, 0x54($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X54);
    // 0x802C6DA8: addiu       $v0, $s2, 0x8
    ctx->r2 = ADD32(ctx->r18, 0X8);
    // 0x802C6DAC: lw          $s2, 0x44($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X44);
    // 0x802C6DB0: lw          $s5, 0x50($sp)
    ctx->r21 = MEM_W(ctx->r29, 0X50);
    // 0x802C6DB4: lw          $s4, 0x4C($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X4C);
    // 0x802C6DB8: lw          $s3, 0x48($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X48);
    // 0x802C6DBC: lw          $s1, 0x40($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X40);
    // 0x802C6DC0: lw          $s0, 0x3C($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X3C);
    // 0x802C6DC4: jr          $ra
    // 0x802C6DC8: addiu       $sp, $sp, 0x58
    ctx->r29 = ADD32(ctx->r29, 0X58);
    return;
    // 0x802C6DC8: addiu       $sp, $sp, 0x58
    ctx->r29 = ADD32(ctx->r29, 0X58);
;}
RECOMP_FUNC void func_i1_802C6DCC(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C6DCC: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x802C6DD0: addiu       $v0, $v0, -0x54DC
    ctx->r2 = ADD32(ctx->r2, -0X54DC);
    // 0x802C6DD4: lw          $t6, 0x0($v0)
    ctx->r14 = MEM_W(ctx->r2, 0X0);
    // 0x802C6DD8: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C6DDC: addiu       $t7, $zero, 0x29
    ctx->r15 = ADD32(0, 0X29);
    // 0x802C6DE0: sw          $t6, -0x19CC($at)
    MEM_W(-0X19CC, ctx->r1) = ctx->r14;
    // 0x802C6DE4: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C6DE8: sw          $zero, -0x19D0($at)
    MEM_W(-0X19D0, ctx->r1) = 0;
    // 0x802C6DEC: addiu       $v1, $zero, 0x1
    ctx->r3 = ADD32(0, 0X1);
    // 0x802C6DF0: sw          $t7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r15;
    // 0x802C6DF4: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C6DF8: sw          $v1, -0x19C8($at)
    MEM_W(-0X19C8, ctx->r1) = ctx->r3;
    // 0x802C6DFC: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C6E00: sw          $v1, -0x19C4($at)
    MEM_W(-0X19C4, ctx->r1) = ctx->r3;
    // 0x802C6E04: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C6E08: sw          $zero, -0x19C0($at)
    MEM_W(-0X19C0, ctx->r1) = 0;
    // 0x802C6E0C: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C6E10: sw          $zero, -0x19BC($at)
    MEM_W(-0X19BC, ctx->r1) = 0;
    // 0x802C6E14: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x802C6E18: sw          $zero, -0x54E4($at)
    MEM_W(-0X54E4, ctx->r1) = 0;
    // 0x802C6E1C: lui         $at, 0x800D
    ctx->r1 = S32(0X800D << 16);
    // 0x802C6E20: addiu       $t8, $zero, 0x3
    ctx->r24 = ADD32(0, 0X3);
    // 0x802C6E24: sw          $t8, 0x461C($at)
    MEM_W(0X461C, ctx->r1) = ctx->r24;
    // 0x802C6E28: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C6E2C: sw          $zero, -0x695C($at)
    MEM_W(-0X695C, ctx->r1) = 0;
    // 0x802C6E30: lui         $t9, 0x801D
    ctx->r25 = S32(0X801D << 16);
    // 0x802C6E34: lw          $t9, -0x19F8($t9)
    ctx->r25 = MEM_W(ctx->r25, -0X19F8);
    // 0x802C6E38: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C6E3C: sw          $zero, -0x6960($at)
    MEM_W(-0X6960, ctx->r1) = 0;
    // 0x802C6E40: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x802C6E44: addiu       $at, $zero, 0x4
    ctx->r1 = ADD32(0, 0X4);
    // 0x802C6E48: bne         $t9, $at, L_802C6F00
    if (ctx->r25 != ctx->r1) {
        // 0x802C6E4C: sw          $ra, 0x14($sp)
        MEM_W(0X14, ctx->r29) = ctx->r31;
            goto L_802C6F00;
    }
    // 0x802C6E4C: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x802C6E50: lui         $t0, 0x801D
    ctx->r8 = S32(0X801D << 16);
    // 0x802C6E54: lui         $t1, 0x801C
    ctx->r9 = S32(0X801C << 16);
    // 0x802C6E58: lw          $t1, 0x293C($t1)
    ctx->r9 = MEM_W(ctx->r9, 0X293C);
    // 0x802C6E5C: lw          $t0, -0x18F8($t0)
    ctx->r8 = MEM_W(ctx->r8, -0X18F8);
    // 0x802C6E60: lui         $t2, 0x801D
    ctx->r10 = S32(0X801D << 16);
    // 0x802C6E64: lui         $t3, 0x801C
    ctx->r11 = S32(0X801C << 16);
    // 0x802C6E68: slt         $at, $t0, $t1
    ctx->r1 = SIGNED(ctx->r8) < SIGNED(ctx->r9) ? 1 : 0;
    // 0x802C6E6C: bne         $at, $zero, L_802C6E80
    if (ctx->r1 != 0) {
        // 0x802C6E70: lui         $t4, 0x801D
        ctx->r12 = S32(0X801D << 16);
            goto L_802C6E80;
    }
    // 0x802C6E70: lui         $t4, 0x801D
    ctx->r12 = S32(0X801D << 16);
    // 0x802C6E74: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C6E78: b           L_802C6E88
    // 0x802C6E7C: sh          $v1, -0x4C08($at)
    MEM_H(-0X4C08, ctx->r1) = ctx->r3;
        goto L_802C6E88;
    // 0x802C6E7C: sh          $v1, -0x4C08($at)
    MEM_H(-0X4C08, ctx->r1) = ctx->r3;
L_802C6E80:
    // 0x802C6E80: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C6E84: sh          $zero, -0x4C08($at)
    MEM_H(-0X4C08, ctx->r1) = 0;
L_802C6E88:
    // 0x802C6E88: lw          $t2, -0x18F4($t2)
    ctx->r10 = MEM_W(ctx->r10, -0X18F4);
    // 0x802C6E8C: lw          $t3, 0x2CB4($t3)
    ctx->r11 = MEM_W(ctx->r11, 0X2CB4);
    // 0x802C6E90: lui         $t5, 0x801C
    ctx->r13 = S32(0X801C << 16);
    // 0x802C6E94: lui         $t6, 0x801D
    ctx->r14 = S32(0X801D << 16);
    // 0x802C6E98: slt         $at, $t2, $t3
    ctx->r1 = SIGNED(ctx->r10) < SIGNED(ctx->r11) ? 1 : 0;
    // 0x802C6E9C: bne         $at, $zero, L_802C6EB0
    if (ctx->r1 != 0) {
        // 0x802C6EA0: lui         $t7, 0x801C
        ctx->r15 = S32(0X801C << 16);
            goto L_802C6EB0;
    }
    // 0x802C6EA0: lui         $t7, 0x801C
    ctx->r15 = S32(0X801C << 16);
    // 0x802C6EA4: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C6EA8: b           L_802C6EB8
    // 0x802C6EAC: sh          $v1, -0x4C06($at)
    MEM_H(-0X4C06, ctx->r1) = ctx->r3;
        goto L_802C6EB8;
    // 0x802C6EAC: sh          $v1, -0x4C06($at)
    MEM_H(-0X4C06, ctx->r1) = ctx->r3;
L_802C6EB0:
    // 0x802C6EB0: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C6EB4: sh          $zero, -0x4C06($at)
    MEM_H(-0X4C06, ctx->r1) = 0;
L_802C6EB8:
    // 0x802C6EB8: lw          $t4, -0x18F0($t4)
    ctx->r12 = MEM_W(ctx->r12, -0X18F0);
    // 0x802C6EBC: lw          $t5, 0x302C($t5)
    ctx->r13 = MEM_W(ctx->r13, 0X302C);
    // 0x802C6EC0: slt         $at, $t4, $t5
    ctx->r1 = SIGNED(ctx->r12) < SIGNED(ctx->r13) ? 1 : 0;
    // 0x802C6EC4: bne         $at, $zero, L_802C6ED4
    if (ctx->r1 != 0) {
        // 0x802C6EC8: lui         $at, 0x801D
        ctx->r1 = S32(0X801D << 16);
            goto L_802C6ED4;
    }
    // 0x802C6EC8: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C6ECC: b           L_802C6EDC
    // 0x802C6ED0: sh          $v1, -0x4C04($at)
    MEM_H(-0X4C04, ctx->r1) = ctx->r3;
        goto L_802C6EDC;
    // 0x802C6ED0: sh          $v1, -0x4C04($at)
    MEM_H(-0X4C04, ctx->r1) = ctx->r3;
L_802C6ED4:
    // 0x802C6ED4: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C6ED8: sh          $zero, -0x4C04($at)
    MEM_H(-0X4C04, ctx->r1) = 0;
L_802C6EDC:
    // 0x802C6EDC: lw          $t6, -0x18EC($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X18EC);
    // 0x802C6EE0: lw          $t7, 0x33A4($t7)
    ctx->r15 = MEM_W(ctx->r15, 0X33A4);
    // 0x802C6EE4: slt         $at, $t6, $t7
    ctx->r1 = SIGNED(ctx->r14) < SIGNED(ctx->r15) ? 1 : 0;
    // 0x802C6EE8: bne         $at, $zero, L_802C6EF8
    if (ctx->r1 != 0) {
        // 0x802C6EEC: lui         $at, 0x801D
        ctx->r1 = S32(0X801D << 16);
            goto L_802C6EF8;
    }
    // 0x802C6EEC: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C6EF0: b           L_802C6F00
    // 0x802C6EF4: sh          $v1, -0x4C02($at)
    MEM_H(-0X4C02, ctx->r1) = ctx->r3;
        goto L_802C6F00;
    // 0x802C6EF4: sh          $v1, -0x4C02($at)
    MEM_H(-0X4C02, ctx->r1) = ctx->r3;
L_802C6EF8:
    // 0x802C6EF8: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C6EFC: sh          $zero, -0x4C02($at)
    MEM_H(-0X4C02, ctx->r1) = 0;
L_802C6F00:
    // 0x802C6F00: lui         $t8, 0x800E
    ctx->r24 = S32(0X800E << 16);
    // 0x802C6F04: lw          $t8, -0x54D8($t8)
    ctx->r24 = MEM_W(ctx->r24, -0X54D8);
    // 0x802C6F08: lui         $t9, 0x802D
    ctx->r25 = S32(0X802D << 16);
    // 0x802C6F0C: bnel        $v1, $t8, L_802C6F40
    if (ctx->r3 != ctx->r24) {
        // 0x802C6F10: or          $a0, $zero, $zero
        ctx->r4 = 0 | 0;
            goto L_802C6F40;
    }
    goto skip_0;
    // 0x802C6F10: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    skip_0:
    // 0x802C6F14: lw          $t9, -0x6AF0($t9)
    ctx->r25 = MEM_W(ctx->r25, -0X6AF0);
    // 0x802C6F18: addiu       $t0, $zero, 0x78
    ctx->r8 = ADD32(0, 0X78);
    // 0x802C6F1C: or          $a0, $v1, $zero
    ctx->r4 = ctx->r3 | 0;
    // 0x802C6F20: beq         $t9, $zero, L_802C6F34
    if (ctx->r25 == 0) {
        // 0x802C6F24: addiu       $a1, $zero, 0x4
        ctx->r5 = ADD32(0, 0X4);
            goto L_802C6F34;
    }
    // 0x802C6F24: addiu       $a1, $zero, 0x4
    ctx->r5 = ADD32(0, 0X4);
    // 0x802C6F28: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C6F2C: b           L_802C6F3C
    // 0x802C6F30: sw          $t0, -0x6AF4($at)
    MEM_W(-0X6AF4, ctx->r1) = ctx->r8;
        goto L_802C6F3C;
    // 0x802C6F30: sw          $t0, -0x6AF4($at)
    MEM_W(-0X6AF4, ctx->r1) = ctx->r8;
L_802C6F34:
    // 0x802C6F34: jal         0x801E6FB0
    // 0x802C6F38: addiu       $a2, $zero, 0x78
    ctx->r6 = ADD32(0, 0X78);
    FadeTransition_SetProps(rdram, ctx);
        goto after_0;
    // 0x802C6F38: addiu       $a2, $zero, 0x78
    ctx->r6 = ADD32(0, 0X78);
    after_0:
L_802C6F3C:
    // 0x802C6F3C: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
L_802C6F40:
    // 0x802C6F40: jal         0x801E6A4C
    // 0x802C6F44: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_801E6A4C(rdram, ctx);
        goto after_1;
    // 0x802C6F44: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_1:
    // 0x802C6F48: lui         $t1, 0x800E
    ctx->r9 = S32(0X800E << 16);
    // 0x802C6F4C: lw          $t1, -0x54D8($t1)
    ctx->r9 = MEM_W(ctx->r9, -0X54D8);
    // 0x802C6F50: addiu       $v1, $zero, 0x1
    ctx->r3 = ADD32(0, 0X1);
    // 0x802C6F54: lui         $t2, 0x800D
    ctx->r10 = S32(0X800D << 16);
    // 0x802C6F58: bne         $v1, $t1, L_802C6FA8
    if (ctx->r3 != ctx->r9) {
        // 0x802C6F5C: nop
    
            goto L_802C6FA8;
    }
    // 0x802C6F5C: nop

    // 0x802C6F60: lw          $t2, 0x48DC($t2)
    ctx->r10 = MEM_W(ctx->r10, 0X48DC);
    // 0x802C6F64: lui         $v0, 0x801C
    ctx->r2 = S32(0X801C << 16);
    // 0x802C6F68: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C6F6C: sll         $t3, $t2, 3
    ctx->r11 = S32(ctx->r10 << 3);
    // 0x802C6F70: subu        $t3, $t3, $t2
    ctx->r11 = SUB32(ctx->r11, ctx->r10);
    // 0x802C6F74: sll         $t3, $t3, 4
    ctx->r11 = S32(ctx->r11 << 4);
    // 0x802C6F78: subu        $t3, $t3, $t2
    ctx->r11 = SUB32(ctx->r11, ctx->r10);
    // 0x802C6F7C: sll         $t3, $t3, 3
    ctx->r11 = S32(ctx->r11 << 3);
    // 0x802C6F80: addu        $v0, $v0, $t3
    ctx->r2 = ADD32(ctx->r2, ctx->r11);
    // 0x802C6F84: lw          $v0, 0x2C24($v0)
    ctx->r2 = MEM_W(ctx->r2, 0X2C24);
    // 0x802C6F88: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x802C6F8C: beq         $v1, $v0, L_802C6FA0
    if (ctx->r3 == ctx->r2) {
        // 0x802C6F90: nop
    
            goto L_802C6FA0;
    }
    // 0x802C6F90: nop

    // 0x802C6F94: bne         $v0, $at, L_802C6FA0
    if (ctx->r2 != ctx->r1) {
        // 0x802C6F98: nop
    
            goto L_802C6FA0;
    }
    // 0x802C6F98: nop

    // 0x802C6F9C: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
L_802C6FA0:
    // 0x802C6FA0: jal         0x801E6A4C
    // 0x802C6FA4: addiu       $a0, $zero, 0x4
    ctx->r4 = ADD32(0, 0X4);
    func_801E6A4C(rdram, ctx);
        goto after_2;
    // 0x802C6FA4: addiu       $a0, $zero, 0x4
    ctx->r4 = ADD32(0, 0X4);
    after_2:
L_802C6FA8:
    // 0x802C6FA8: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C6FAC: jal         0x800BFD34
    // 0x802C6FB0: sh          $zero, -0x19D6($at)
    MEM_H(-0X19D6, ctx->r1) = 0;
    func_800BFD34(rdram, ctx);
        goto after_3;
    // 0x802C6FB0: sh          $zero, -0x19D6($at)
    MEM_H(-0X19D6, ctx->r1) = 0;
    after_3:
    // 0x802C6FB4: jal         0x800BFD68
    // 0x802C6FB8: nop

    func_800BFD68(rdram, ctx);
        goto after_4;
    // 0x802C6FB8: nop

    after_4:
    // 0x802C6FBC: jal         0x800C1F60
    // 0x802C6FC0: addiu       $a0, $zero, 0x4
    ctx->r4 = ADD32(0, 0X4);
    func_800C1F60(rdram, ctx);
        goto after_5;
    // 0x802C6FC0: addiu       $a0, $zero, 0x4
    ctx->r4 = ADD32(0, 0X4);
    after_5:
    // 0x802C6FC4: addiu       $a0, $zero, 0x4
    ctx->r4 = ADD32(0, 0X4);
    // 0x802C6FC8: jal         0x800C21F4
    // 0x802C6FCC: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C21F4(rdram, ctx);
        goto after_6;
    // 0x802C6FCC: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_6:
    // 0x802C6FD0: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x802C6FD4: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x802C6FD8: jr          $ra
    // 0x802C6FDC: nop

    return;
    // 0x802C6FDC: nop

;}
RECOMP_FUNC void func_i1_802C6FE0(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C6FE0: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x802C6FE4: addiu       $v0, $v0, -0x54DC
    ctx->r2 = ADD32(ctx->r2, -0X54DC);
    // 0x802C6FE8: lw          $t6, 0x0($v0)
    ctx->r14 = MEM_W(ctx->r2, 0X0);
    // 0x802C6FEC: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C6FF0: addiu       $t7, $zero, 0x2A
    ctx->r15 = ADD32(0, 0X2A);
    // 0x802C6FF4: sw          $t6, -0x19CC($at)
    MEM_W(-0X19CC, ctx->r1) = ctx->r14;
    // 0x802C6FF8: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C6FFC: sw          $zero, -0x19D0($at)
    MEM_W(-0X19D0, ctx->r1) = 0;
    // 0x802C7000: addiu       $v1, $zero, 0x1
    ctx->r3 = ADD32(0, 0X1);
    // 0x802C7004: sw          $t7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r15;
    // 0x802C7008: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C700C: sw          $v1, -0x19C8($at)
    MEM_W(-0X19C8, ctx->r1) = ctx->r3;
    // 0x802C7010: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C7014: sw          $v1, -0x19C4($at)
    MEM_W(-0X19C4, ctx->r1) = ctx->r3;
    // 0x802C7018: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C701C: sw          $zero, -0x19C0($at)
    MEM_W(-0X19C0, ctx->r1) = 0;
    // 0x802C7020: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C7024: sw          $zero, -0x19BC($at)
    MEM_W(-0X19BC, ctx->r1) = 0;
    // 0x802C7028: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x802C702C: sw          $zero, -0x54E4($at)
    MEM_W(-0X54E4, ctx->r1) = 0;
    // 0x802C7030: lui         $t9, 0x801D
    ctx->r25 = S32(0X801D << 16);
    // 0x802C7034: lw          $t9, -0x19F8($t9)
    ctx->r25 = MEM_W(ctx->r25, -0X19F8);
    // 0x802C7038: lui         $at, 0x800D
    ctx->r1 = S32(0X800D << 16);
    // 0x802C703C: addiu       $t8, $zero, 0x3
    ctx->r24 = ADD32(0, 0X3);
    // 0x802C7040: sw          $t8, 0x461C($at)
    MEM_W(0X461C, ctx->r1) = ctx->r24;
    // 0x802C7044: addiu       $sp, $sp, -0x28
    ctx->r29 = ADD32(ctx->r29, -0X28);
    // 0x802C7048: addiu       $a0, $zero, 0x4
    ctx->r4 = ADD32(0, 0X4);
    // 0x802C704C: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C7050: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x802C7054: bne         $a0, $t9, L_802C710C
    if (ctx->r4 != ctx->r25) {
        // 0x802C7058: sw          $zero, -0x6B00($at)
        MEM_W(-0X6B00, ctx->r1) = 0;
            goto L_802C710C;
    }
    // 0x802C7058: sw          $zero, -0x6B00($at)
    MEM_W(-0X6B00, ctx->r1) = 0;
    // 0x802C705C: lui         $t0, 0x801D
    ctx->r8 = S32(0X801D << 16);
    // 0x802C7060: lui         $t1, 0x801C
    ctx->r9 = S32(0X801C << 16);
    // 0x802C7064: lw          $t1, 0x293C($t1)
    ctx->r9 = MEM_W(ctx->r9, 0X293C);
    // 0x802C7068: lw          $t0, -0x18F8($t0)
    ctx->r8 = MEM_W(ctx->r8, -0X18F8);
    // 0x802C706C: lui         $t2, 0x801D
    ctx->r10 = S32(0X801D << 16);
    // 0x802C7070: lui         $t3, 0x801C
    ctx->r11 = S32(0X801C << 16);
    // 0x802C7074: slt         $at, $t0, $t1
    ctx->r1 = SIGNED(ctx->r8) < SIGNED(ctx->r9) ? 1 : 0;
    // 0x802C7078: bne         $at, $zero, L_802C708C
    if (ctx->r1 != 0) {
        // 0x802C707C: lui         $t4, 0x801D
        ctx->r12 = S32(0X801D << 16);
            goto L_802C708C;
    }
    // 0x802C707C: lui         $t4, 0x801D
    ctx->r12 = S32(0X801D << 16);
    // 0x802C7080: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C7084: b           L_802C7094
    // 0x802C7088: sh          $v1, -0x4C08($at)
    MEM_H(-0X4C08, ctx->r1) = ctx->r3;
        goto L_802C7094;
    // 0x802C7088: sh          $v1, -0x4C08($at)
    MEM_H(-0X4C08, ctx->r1) = ctx->r3;
L_802C708C:
    // 0x802C708C: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C7090: sh          $zero, -0x4C08($at)
    MEM_H(-0X4C08, ctx->r1) = 0;
L_802C7094:
    // 0x802C7094: lw          $t2, -0x18F4($t2)
    ctx->r10 = MEM_W(ctx->r10, -0X18F4);
    // 0x802C7098: lw          $t3, 0x2CB4($t3)
    ctx->r11 = MEM_W(ctx->r11, 0X2CB4);
    // 0x802C709C: lui         $t5, 0x801C
    ctx->r13 = S32(0X801C << 16);
    // 0x802C70A0: lui         $t6, 0x801D
    ctx->r14 = S32(0X801D << 16);
    // 0x802C70A4: slt         $at, $t2, $t3
    ctx->r1 = SIGNED(ctx->r10) < SIGNED(ctx->r11) ? 1 : 0;
    // 0x802C70A8: bne         $at, $zero, L_802C70BC
    if (ctx->r1 != 0) {
        // 0x802C70AC: lui         $t7, 0x801C
        ctx->r15 = S32(0X801C << 16);
            goto L_802C70BC;
    }
    // 0x802C70AC: lui         $t7, 0x801C
    ctx->r15 = S32(0X801C << 16);
    // 0x802C70B0: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C70B4: b           L_802C70C4
    // 0x802C70B8: sh          $v1, -0x4C06($at)
    MEM_H(-0X4C06, ctx->r1) = ctx->r3;
        goto L_802C70C4;
    // 0x802C70B8: sh          $v1, -0x4C06($at)
    MEM_H(-0X4C06, ctx->r1) = ctx->r3;
L_802C70BC:
    // 0x802C70BC: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C70C0: sh          $zero, -0x4C06($at)
    MEM_H(-0X4C06, ctx->r1) = 0;
L_802C70C4:
    // 0x802C70C4: lw          $t4, -0x18F0($t4)
    ctx->r12 = MEM_W(ctx->r12, -0X18F0);
    // 0x802C70C8: lw          $t5, 0x302C($t5)
    ctx->r13 = MEM_W(ctx->r13, 0X302C);
    // 0x802C70CC: slt         $at, $t4, $t5
    ctx->r1 = SIGNED(ctx->r12) < SIGNED(ctx->r13) ? 1 : 0;
    // 0x802C70D0: bne         $at, $zero, L_802C70E0
    if (ctx->r1 != 0) {
        // 0x802C70D4: lui         $at, 0x801D
        ctx->r1 = S32(0X801D << 16);
            goto L_802C70E0;
    }
    // 0x802C70D4: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C70D8: b           L_802C70E8
    // 0x802C70DC: sh          $v1, -0x4C04($at)
    MEM_H(-0X4C04, ctx->r1) = ctx->r3;
        goto L_802C70E8;
    // 0x802C70DC: sh          $v1, -0x4C04($at)
    MEM_H(-0X4C04, ctx->r1) = ctx->r3;
L_802C70E0:
    // 0x802C70E0: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C70E4: sh          $zero, -0x4C04($at)
    MEM_H(-0X4C04, ctx->r1) = 0;
L_802C70E8:
    // 0x802C70E8: lw          $t6, -0x18EC($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X18EC);
    // 0x802C70EC: lw          $t7, 0x33A4($t7)
    ctx->r15 = MEM_W(ctx->r15, 0X33A4);
    // 0x802C70F0: slt         $at, $t6, $t7
    ctx->r1 = SIGNED(ctx->r14) < SIGNED(ctx->r15) ? 1 : 0;
    // 0x802C70F4: bne         $at, $zero, L_802C7104
    if (ctx->r1 != 0) {
        // 0x802C70F8: lui         $at, 0x801D
        ctx->r1 = S32(0X801D << 16);
            goto L_802C7104;
    }
    // 0x802C70F8: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C70FC: b           L_802C710C
    // 0x802C7100: sh          $v1, -0x4C02($at)
    MEM_H(-0X4C02, ctx->r1) = ctx->r3;
        goto L_802C710C;
    // 0x802C7100: sh          $v1, -0x4C02($at)
    MEM_H(-0X4C02, ctx->r1) = ctx->r3;
L_802C7104:
    // 0x802C7104: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C7108: sh          $zero, -0x4C02($at)
    MEM_H(-0X4C02, ctx->r1) = 0;
L_802C710C:
    // 0x802C710C: lui         $t8, 0x800E
    ctx->r24 = S32(0X800E << 16);
    // 0x802C7110: lw          $t8, -0x54D8($t8)
    ctx->r24 = MEM_W(ctx->r24, -0X54D8);
    // 0x802C7114: lui         $t9, 0x800D
    ctx->r25 = S32(0X800D << 16);
    // 0x802C7118: addiu       $a1, $zero, 0x4
    ctx->r5 = ADD32(0, 0X4);
    // 0x802C711C: bne         $v1, $t8, L_802C7228
    if (ctx->r3 != ctx->r24) {
        // 0x802C7120: addiu       $a2, $zero, 0x64
        ctx->r6 = ADD32(0, 0X64);
            goto L_802C7228;
    }
    // 0x802C7120: addiu       $a2, $zero, 0x64
    ctx->r6 = ADD32(0, 0X64);
    // 0x802C7124: lw          $t9, 0x48DC($t9)
    ctx->r25 = MEM_W(ctx->r25, 0X48DC);
    // 0x802C7128: lui         $v0, 0x8019
    ctx->r2 = S32(0X8019 << 16);
    // 0x802C712C: addiu       $t1, $zero, 0x82
    ctx->r9 = ADD32(0, 0X82);
    // 0x802C7130: sll         $t0, $t9, 2
    ctx->r8 = S32(ctx->r25 << 2);
    // 0x802C7134: subu        $t0, $t0, $t9
    ctx->r8 = SUB32(ctx->r8, ctx->r25);
    // 0x802C7138: sll         $t0, $t0, 3
    ctx->r8 = S32(ctx->r8 << 3);
    // 0x802C713C: subu        $t0, $t0, $t9
    ctx->r8 = SUB32(ctx->r8, ctx->r25);
    // 0x802C7140: sll         $t0, $t0, 3
    ctx->r8 = S32(ctx->r8 << 3);
    // 0x802C7144: addu        $t0, $t0, $t9
    ctx->r8 = ADD32(ctx->r8, ctx->r25);
    // 0x802C7148: sll         $t0, $t0, 2
    ctx->r8 = S32(ctx->r8 << 2);
    // 0x802C714C: subu        $t0, $t0, $t9
    ctx->r8 = SUB32(ctx->r8, ctx->r25);
    // 0x802C7150: sll         $t0, $t0, 3
    ctx->r8 = S32(ctx->r8 << 3);
    // 0x802C7154: addu        $v0, $v0, $t0
    ctx->r2 = ADD32(ctx->r2, ctx->r8);
    // 0x802C7158: lw          $v0, 0x3D58($v0)
    ctx->r2 = MEM_W(ctx->r2, 0X3D58);
    // 0x802C715C: bnel        $v0, $v1, L_802C7178
    if (ctx->r2 != ctx->r3) {
        // 0x802C7160: addiu       $at, $zero, 0x2
        ctx->r1 = ADD32(0, 0X2);
            goto L_802C7178;
    }
    goto skip_0;
    // 0x802C7160: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    skip_0:
    // 0x802C7164: lui         $v0, 0x802D
    ctx->r2 = S32(0X802D << 16);
    // 0x802C7168: addiu       $v0, $v0, -0x6AFC
    ctx->r2 = ADD32(ctx->r2, -0X6AFC);
    // 0x802C716C: b           L_802C71FC
    // 0x802C7170: sw          $t1, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r9;
        goto L_802C71FC;
    // 0x802C7170: sw          $t1, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r9;
    // 0x802C7174: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
L_802C7178:
    // 0x802C7178: bnel        $v0, $at, L_802C7198
    if (ctx->r2 != ctx->r1) {
        // 0x802C717C: addiu       $at, $zero, 0x3
        ctx->r1 = ADD32(0, 0X3);
            goto L_802C7198;
    }
    goto skip_1;
    // 0x802C717C: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    skip_1:
    // 0x802C7180: lui         $v0, 0x802D
    ctx->r2 = S32(0X802D << 16);
    // 0x802C7184: addiu       $v0, $v0, -0x6AFC
    ctx->r2 = ADD32(ctx->r2, -0X6AFC);
    // 0x802C7188: addiu       $t2, $zero, 0x8C
    ctx->r10 = ADD32(0, 0X8C);
    // 0x802C718C: b           L_802C71FC
    // 0x802C7190: sw          $t2, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r10;
        goto L_802C71FC;
    // 0x802C7190: sw          $t2, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r10;
    // 0x802C7194: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
L_802C7198:
    // 0x802C7198: bne         $v0, $at, L_802C71B4
    if (ctx->r2 != ctx->r1) {
        // 0x802C719C: nop
    
            goto L_802C71B4;
    }
    // 0x802C719C: nop

    // 0x802C71A0: lui         $v0, 0x802D
    ctx->r2 = S32(0X802D << 16);
    // 0x802C71A4: addiu       $v0, $v0, -0x6AFC
    ctx->r2 = ADD32(ctx->r2, -0X6AFC);
    // 0x802C71A8: addiu       $t3, $zero, 0x64
    ctx->r11 = ADD32(0, 0X64);
    // 0x802C71AC: b           L_802C71FC
    // 0x802C71B0: sw          $t3, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r11;
        goto L_802C71FC;
    // 0x802C71B0: sw          $t3, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r11;
L_802C71B4:
    // 0x802C71B4: bnel        $v0, $a0, L_802C71D4
    if (ctx->r2 != ctx->r4) {
        // 0x802C71B8: addiu       $at, $zero, 0x5
        ctx->r1 = ADD32(0, 0X5);
            goto L_802C71D4;
    }
    goto skip_2;
    // 0x802C71B8: addiu       $at, $zero, 0x5
    ctx->r1 = ADD32(0, 0X5);
    skip_2:
    // 0x802C71BC: lui         $v0, 0x802D
    ctx->r2 = S32(0X802D << 16);
    // 0x802C71C0: addiu       $v0, $v0, -0x6AFC
    ctx->r2 = ADD32(ctx->r2, -0X6AFC);
    // 0x802C71C4: addiu       $t4, $zero, 0x78
    ctx->r12 = ADD32(0, 0X78);
    // 0x802C71C8: b           L_802C71FC
    // 0x802C71CC: sw          $t4, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r12;
        goto L_802C71FC;
    // 0x802C71CC: sw          $t4, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r12;
    // 0x802C71D0: addiu       $at, $zero, 0x5
    ctx->r1 = ADD32(0, 0X5);
L_802C71D4:
    // 0x802C71D4: bne         $v0, $at, L_802C71EC
    if (ctx->r2 != ctx->r1) {
        // 0x802C71D8: lui         $v0, 0x802D
        ctx->r2 = S32(0X802D << 16);
            goto L_802C71EC;
    }
    // 0x802C71D8: lui         $v0, 0x802D
    ctx->r2 = S32(0X802D << 16);
    // 0x802C71DC: addiu       $v0, $v0, -0x6AFC
    ctx->r2 = ADD32(ctx->r2, -0X6AFC);
    // 0x802C71E0: addiu       $t5, $zero, 0x6E
    ctx->r13 = ADD32(0, 0X6E);
    // 0x802C71E4: b           L_802C71FC
    // 0x802C71E8: sw          $t5, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r13;
        goto L_802C71FC;
    // 0x802C71E8: sw          $t5, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r13;
L_802C71EC:
    // 0x802C71EC: lui         $v0, 0x802D
    ctx->r2 = S32(0X802D << 16);
    // 0x802C71F0: addiu       $v0, $v0, -0x6AFC
    ctx->r2 = ADD32(ctx->r2, -0X6AFC);
    // 0x802C71F4: addiu       $t6, $zero, 0x64
    ctx->r14 = ADD32(0, 0X64);
    // 0x802C71F8: sw          $t6, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r14;
L_802C71FC:
    // 0x802C71FC: lui         $t7, 0x801D
    ctx->r15 = S32(0X801D << 16);
    // 0x802C7200: lw          $t7, -0x19E0($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X19E0);
    // 0x802C7204: addiu       $at, $zero, 0xB
    ctx->r1 = ADD32(0, 0XB);
    // 0x802C7208: bne         $t7, $at, L_802C721C
    if (ctx->r15 != ctx->r1) {
        // 0x802C720C: or          $a0, $v1, $zero
        ctx->r4 = ctx->r3 | 0;
            goto L_802C721C;
    }
    // 0x802C720C: or          $a0, $v1, $zero
    ctx->r4 = ctx->r3 | 0;
    // 0x802C7210: addiu       $a1, $zero, 0x4
    ctx->r5 = ADD32(0, 0X4);
    // 0x802C7214: jal         0x801E6FB0
    // 0x802C7218: lw          $a2, 0x0($v0)
    ctx->r6 = MEM_W(ctx->r2, 0X0);
    FadeTransition_SetProps(rdram, ctx);
        goto after_0;
    // 0x802C7218: lw          $a2, 0x0($v0)
    ctx->r6 = MEM_W(ctx->r2, 0X0);
    after_0:
L_802C721C:
    // 0x802C721C: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C7220: b           L_802C7230
    // 0x802C7224: sw          $zero, -0x6AF8($at)
    MEM_W(-0X6AF8, ctx->r1) = 0;
        goto L_802C7230;
    // 0x802C7224: sw          $zero, -0x6AF8($at)
    MEM_W(-0X6AF8, ctx->r1) = 0;
L_802C7228:
    // 0x802C7228: jal         0x801E6FB0
    // 0x802C722C: or          $a0, $v1, $zero
    ctx->r4 = ctx->r3 | 0;
    FadeTransition_SetProps(rdram, ctx);
        goto after_1;
    // 0x802C722C: or          $a0, $v1, $zero
    ctx->r4 = ctx->r3 | 0;
    after_1:
L_802C7230:
    // 0x802C7230: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    // 0x802C7234: jal         0x801E6A4C
    // 0x802C7238: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_801E6A4C(rdram, ctx);
        goto after_2;
    // 0x802C7238: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_2:
    // 0x802C723C: lui         $t8, 0x800E
    ctx->r24 = S32(0X800E << 16);
    // 0x802C7240: lw          $t8, -0x54D8($t8)
    ctx->r24 = MEM_W(ctx->r24, -0X54D8);
    // 0x802C7244: addiu       $v1, $zero, 0x1
    ctx->r3 = ADD32(0, 0X1);
    // 0x802C7248: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    // 0x802C724C: bne         $v1, $t8, L_802C7260
    if (ctx->r3 != ctx->r24) {
        // 0x802C7250: nop
    
            goto L_802C7260;
    }
    // 0x802C7250: nop

    // 0x802C7254: jal         0x801E6A4C
    // 0x802C7258: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    func_801E6A4C(rdram, ctx);
        goto after_3;
    // 0x802C7258: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    after_3:
    // 0x802C725C: addiu       $v1, $zero, 0x1
    ctx->r3 = ADD32(0, 0X1);
L_802C7260:
    // 0x802C7260: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x802C7264: lw          $v0, -0x19F8($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X19F8);
    // 0x802C7268: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C726C: sh          $zero, -0x19D6($at)
    MEM_H(-0X19D6, ctx->r1) = 0;
    // 0x802C7270: beq         $v0, $zero, L_802C7290
    if (ctx->r2 == 0) {
        // 0x802C7274: lui         $t9, 0x801C
        ctx->r25 = S32(0X801C << 16);
            goto L_802C7290;
    }
    // 0x802C7274: lui         $t9, 0x801C
    ctx->r25 = S32(0X801C << 16);
    // 0x802C7278: beq         $v0, $v1, L_802C7334
    if (ctx->r2 == ctx->r3) {
        // 0x802C727C: addiu       $at, $zero, 0xB
        ctx->r1 = ADD32(0, 0XB);
            goto L_802C7334;
    }
    // 0x802C727C: addiu       $at, $zero, 0xB
    ctx->r1 = ADD32(0, 0XB);
    // 0x802C7280: beq         $v0, $at, L_802C7374
    if (ctx->r2 == ctx->r1) {
        // 0x802C7284: nop
    
            goto L_802C7374;
    }
    // 0x802C7284: nop

    // 0x802C7288: b           L_802C72C8
    // 0x802C728C: nop

        goto L_802C72C8;
    // 0x802C728C: nop

L_802C7290:
    // 0x802C7290: lw          $t9, 0x2650($t9)
    ctx->r25 = MEM_W(ctx->r25, 0X2650);
    // 0x802C7294: addiu       $a0, $zero, 0x6
    ctx->r4 = ADD32(0, 0X6);
    // 0x802C7298: bnel        $v1, $t9, L_802C72AC
    if (ctx->r3 != ctx->r25) {
        // 0x802C729C: addiu       $a1, $zero, 0x1
        ctx->r5 = ADD32(0, 0X1);
            goto L_802C72AC;
    }
    goto skip_3;
    // 0x802C729C: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    skip_3:
    // 0x802C72A0: b           L_802C72AC
    // 0x802C72A4: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
        goto L_802C72AC;
    // 0x802C72A4: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C72A8: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
L_802C72AC:
    // 0x802C72AC: jal         0x800C1F60
    // 0x802C72B0: sw          $a1, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r5;
    func_800C1F60(rdram, ctx);
        goto after_4;
    // 0x802C72B0: sw          $a1, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r5;
    after_4:
    // 0x802C72B4: lw          $a1, 0x18($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X18);
    // 0x802C72B8: jal         0x800C21F4
    // 0x802C72BC: addiu       $a0, $zero, 0x6
    ctx->r4 = ADD32(0, 0X6);
    func_800C21F4(rdram, ctx);
        goto after_5;
    // 0x802C72BC: addiu       $a0, $zero, 0x6
    ctx->r4 = ADD32(0, 0X6);
    after_5:
    // 0x802C72C0: b           L_802C7374
    // 0x802C72C4: nop

        goto L_802C7374;
    // 0x802C72C4: nop

L_802C72C8:
    // 0x802C72C8: jal         0x800C1F60
    // 0x802C72CC: addiu       $a0, $zero, 0x6
    ctx->r4 = ADD32(0, 0X6);
    func_800C1F60(rdram, ctx);
        goto after_6;
    // 0x802C72CC: addiu       $a0, $zero, 0x6
    ctx->r4 = ADD32(0, 0X6);
    after_6:
    // 0x802C72D0: lui         $t0, 0x800D
    ctx->r8 = S32(0X800D << 16);
    // 0x802C72D4: lw          $t0, 0x48DC($t0)
    ctx->r8 = MEM_W(ctx->r8, 0X48DC);
    // 0x802C72D8: lui         $v0, 0x801C
    ctx->r2 = S32(0X801C << 16);
    // 0x802C72DC: lui         $t2, 0x801D
    ctx->r10 = S32(0X801D << 16);
    // 0x802C72E0: sll         $t1, $t0, 3
    ctx->r9 = S32(ctx->r8 << 3);
    // 0x802C72E4: subu        $t1, $t1, $t0
    ctx->r9 = SUB32(ctx->r9, ctx->r8);
    // 0x802C72E8: sll         $t1, $t1, 4
    ctx->r9 = S32(ctx->r9 << 4);
    // 0x802C72EC: subu        $t1, $t1, $t0
    ctx->r9 = SUB32(ctx->r9, ctx->r8);
    // 0x802C72F0: sll         $t1, $t1, 3
    ctx->r9 = S32(ctx->r9 << 3);
    // 0x802C72F4: addu        $v0, $v0, $t1
    ctx->r2 = ADD32(ctx->r2, ctx->r9);
    // 0x802C72F8: lw          $v0, 0x293C($v0)
    ctx->r2 = MEM_W(ctx->r2, 0X293C);
    // 0x802C72FC: lw          $t2, -0x18FC($t2)
    ctx->r10 = MEM_W(ctx->r10, -0X18FC);
    // 0x802C7300: addiu       $a0, $zero, 0x6
    ctx->r4 = ADD32(0, 0X6);
    // 0x802C7304: addiu       $a1, $v0, 0x1
    ctx->r5 = ADD32(ctx->r2, 0X1);
    // 0x802C7308: slt         $at, $t2, $v0
    ctx->r1 = SIGNED(ctx->r10) < SIGNED(ctx->r2) ? 1 : 0;
    // 0x802C730C: bne         $at, $zero, L_802C7324
    if (ctx->r1 != 0) {
        // 0x802C7310: nop
    
            goto L_802C7324;
    }
    // 0x802C7310: nop

    // 0x802C7314: jal         0x800C21F4
    // 0x802C7318: addiu       $a0, $zero, 0x6
    ctx->r4 = ADD32(0, 0X6);
    func_800C21F4(rdram, ctx);
        goto after_7;
    // 0x802C7318: addiu       $a0, $zero, 0x6
    ctx->r4 = ADD32(0, 0X6);
    after_7:
    // 0x802C731C: b           L_802C7374
    // 0x802C7320: nop

        goto L_802C7374;
    // 0x802C7320: nop

L_802C7324:
    // 0x802C7324: jal         0x800C21F4
    // 0x802C7328: addiu       $a1, $zero, 0x5
    ctx->r5 = ADD32(0, 0X5);
    func_800C21F4(rdram, ctx);
        goto after_8;
    // 0x802C7328: addiu       $a1, $zero, 0x5
    ctx->r5 = ADD32(0, 0X5);
    after_8:
    // 0x802C732C: b           L_802C7374
    // 0x802C7330: nop

        goto L_802C7374;
    // 0x802C7330: nop

L_802C7334:
    // 0x802C7334: jal         0x800C1F60
    // 0x802C7338: addiu       $a0, $zero, 0x6
    ctx->r4 = ADD32(0, 0X6);
    func_800C1F60(rdram, ctx);
        goto after_9;
    // 0x802C7338: addiu       $a0, $zero, 0x6
    ctx->r4 = ADD32(0, 0X6);
    after_9:
    // 0x802C733C: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x802C7340: lh          $v0, -0x1910($v0)
    ctx->r2 = MEM_H(ctx->r2, -0X1910);
    // 0x802C7344: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x802C7348: addiu       $v1, $zero, 0x1
    ctx->r3 = ADD32(0, 0X1);
    // 0x802C734C: bne         $v0, $at, L_802C735C
    if (ctx->r2 != ctx->r1) {
        // 0x802C7350: nop
    
            goto L_802C735C;
    }
    // 0x802C7350: nop

    // 0x802C7354: b           L_802C736C
    // 0x802C7358: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
        goto L_802C736C;
    // 0x802C7358: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
L_802C735C:
    // 0x802C735C: bne         $v1, $v0, L_802C736C
    if (ctx->r3 != ctx->r2) {
        // 0x802C7360: addiu       $a1, $zero, 0x1
        ctx->r5 = ADD32(0, 0X1);
            goto L_802C736C;
    }
    // 0x802C7360: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C7364: b           L_802C736C
    // 0x802C7368: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
        goto L_802C736C;
    // 0x802C7368: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
L_802C736C:
    // 0x802C736C: jal         0x800C21F4
    // 0x802C7370: addiu       $a0, $zero, 0x6
    ctx->r4 = ADD32(0, 0X6);
    func_800C21F4(rdram, ctx);
        goto after_10;
    // 0x802C7370: addiu       $a0, $zero, 0x6
    ctx->r4 = ADD32(0, 0X6);
    after_10:
L_802C7374:
    // 0x802C7374: jal         0x800BFD34
    // 0x802C7378: nop

    func_800BFD34(rdram, ctx);
        goto after_11;
    // 0x802C7378: nop

    after_11:
    // 0x802C737C: jal         0x800BFD68
    // 0x802C7380: nop

    func_800BFD68(rdram, ctx);
        goto after_12;
    // 0x802C7380: nop

    after_12:
    // 0x802C7384: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x802C7388: addiu       $sp, $sp, 0x28
    ctx->r29 = ADD32(ctx->r29, 0X28);
    // 0x802C738C: jr          $ra
    // 0x802C7390: nop

    return;
    // 0x802C7390: nop

;}
RECOMP_FUNC void func_i1_802C7394(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C7394: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x802C7398: addiu       $v0, $v0, -0x54DC
    ctx->r2 = ADD32(ctx->r2, -0X54DC);
    // 0x802C739C: lw          $t6, 0x0($v0)
    ctx->r14 = MEM_W(ctx->r2, 0X0);
    // 0x802C73A0: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C73A4: addiu       $t7, $zero, 0x2C
    ctx->r15 = ADD32(0, 0X2C);
    // 0x802C73A8: sw          $t6, -0x19CC($at)
    MEM_W(-0X19CC, ctx->r1) = ctx->r14;
    // 0x802C73AC: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C73B0: sw          $zero, -0x19D0($at)
    MEM_W(-0X19D0, ctx->r1) = 0;
    // 0x802C73B4: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    // 0x802C73B8: sw          $t7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r15;
    // 0x802C73BC: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C73C0: sw          $a0, -0x19C8($at)
    MEM_W(-0X19C8, ctx->r1) = ctx->r4;
    // 0x802C73C4: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C73C8: sw          $a0, -0x19C4($at)
    MEM_W(-0X19C4, ctx->r1) = ctx->r4;
    // 0x802C73CC: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C73D0: sw          $zero, -0x19C0($at)
    MEM_W(-0X19C0, ctx->r1) = 0;
    // 0x802C73D4: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C73D8: sw          $zero, -0x19BC($at)
    MEM_W(-0X19BC, ctx->r1) = 0;
    // 0x802C73DC: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x802C73E0: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x802C73E4: sw          $zero, -0x54E4($at)
    MEM_W(-0X54E4, ctx->r1) = 0;
    // 0x802C73E8: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x802C73EC: lui         $at, 0x800D
    ctx->r1 = S32(0X800D << 16);
    // 0x802C73F0: addiu       $t8, $zero, 0x3
    ctx->r24 = ADD32(0, 0X3);
    // 0x802C73F4: sw          $t8, 0x461C($at)
    MEM_W(0X461C, ctx->r1) = ctx->r24;
    // 0x802C73F8: addiu       $a1, $zero, 0x4
    ctx->r5 = ADD32(0, 0X4);
    // 0x802C73FC: jal         0x801E6FB0
    // 0x802C7400: addiu       $a2, $zero, 0x64
    ctx->r6 = ADD32(0, 0X64);
    FadeTransition_SetProps(rdram, ctx);
        goto after_0;
    // 0x802C7400: addiu       $a2, $zero, 0x64
    ctx->r6 = ADD32(0, 0X64);
    after_0:
    // 0x802C7404: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    // 0x802C7408: jal         0x801E6A4C
    // 0x802C740C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_801E6A4C(rdram, ctx);
        goto after_1;
    // 0x802C740C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_1:
    // 0x802C7410: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C7414: sh          $zero, -0x19D6($at)
    MEM_H(-0X19D6, ctx->r1) = 0;
    // 0x802C7418: jal         0x800C1F60
    // 0x802C741C: addiu       $a0, $zero, 0x4
    ctx->r4 = ADD32(0, 0X4);
    func_800C1F60(rdram, ctx);
        goto after_2;
    // 0x802C741C: addiu       $a0, $zero, 0x4
    ctx->r4 = ADD32(0, 0X4);
    after_2:
    // 0x802C7420: addiu       $a0, $zero, 0x4
    ctx->r4 = ADD32(0, 0X4);
    // 0x802C7424: jal         0x800C21F4
    // 0x802C7428: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C21F4(rdram, ctx);
        goto after_3;
    // 0x802C7428: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_3:
    // 0x802C742C: jal         0x800BFD34
    // 0x802C7430: nop

    func_800BFD34(rdram, ctx);
        goto after_4;
    // 0x802C7430: nop

    after_4:
    // 0x802C7434: jal         0x800BFD68
    // 0x802C7438: nop

    func_800BFD68(rdram, ctx);
        goto after_5;
    // 0x802C7438: nop

    after_5:
    // 0x802C743C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x802C7440: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x802C7444: jr          $ra
    // 0x802C7448: nop

    return;
    // 0x802C7448: nop

;}
RECOMP_FUNC void func_i1_802C744C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C744C: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x802C7450: addiu       $v0, $v0, -0x54DC
    ctx->r2 = ADD32(ctx->r2, -0X54DC);
    // 0x802C7454: lw          $t6, 0x0($v0)
    ctx->r14 = MEM_W(ctx->r2, 0X0);
    // 0x802C7458: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C745C: addiu       $t7, $zero, 0x2B
    ctx->r15 = ADD32(0, 0X2B);
    // 0x802C7460: sw          $t6, -0x19CC($at)
    MEM_W(-0X19CC, ctx->r1) = ctx->r14;
    // 0x802C7464: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C7468: sw          $a0, -0x19D0($at)
    MEM_W(-0X19D0, ctx->r1) = ctx->r4;
    // 0x802C746C: addiu       $v1, $zero, 0x1
    ctx->r3 = ADD32(0, 0X1);
    // 0x802C7470: sw          $t7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r15;
    // 0x802C7474: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C7478: sw          $v1, -0x19C8($at)
    MEM_W(-0X19C8, ctx->r1) = ctx->r3;
    // 0x802C747C: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C7480: sw          $v1, -0x19C4($at)
    MEM_W(-0X19C4, ctx->r1) = ctx->r3;
    // 0x802C7484: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C7488: sw          $zero, -0x19C0($at)
    MEM_W(-0X19C0, ctx->r1) = 0;
    // 0x802C748C: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C7490: sw          $zero, -0x19BC($at)
    MEM_W(-0X19BC, ctx->r1) = 0;
    // 0x802C7494: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x802C7498: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x802C749C: sw          $zero, -0x54E4($at)
    MEM_W(-0X54E4, ctx->r1) = 0;
    // 0x802C74A0: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x802C74A4: lui         $at, 0x800D
    ctx->r1 = S32(0X800D << 16);
    // 0x802C74A8: addiu       $t8, $zero, 0x3
    ctx->r24 = ADD32(0, 0X3);
    // 0x802C74AC: sw          $t8, 0x461C($at)
    MEM_W(0X461C, ctx->r1) = ctx->r24;
    // 0x802C74B0: or          $a0, $v1, $zero
    ctx->r4 = ctx->r3 | 0;
    // 0x802C74B4: addiu       $a1, $zero, 0x4
    ctx->r5 = ADD32(0, 0X4);
    // 0x802C74B8: jal         0x801E6FB0
    // 0x802C74BC: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    FadeTransition_SetProps(rdram, ctx);
        goto after_0;
    // 0x802C74BC: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    after_0:
    // 0x802C74C0: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C74C4: jal         0x800BFD34
    // 0x802C74C8: sh          $zero, -0x19D6($at)
    MEM_H(-0X19D6, ctx->r1) = 0;
    func_800BFD34(rdram, ctx);
        goto after_1;
    // 0x802C74C8: sh          $zero, -0x19D6($at)
    MEM_H(-0X19D6, ctx->r1) = 0;
    after_1:
    // 0x802C74CC: jal         0x800BFD68
    // 0x802C74D0: nop

    func_800BFD68(rdram, ctx);
        goto after_2;
    // 0x802C74D0: nop

    after_2:
    // 0x802C74D4: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x802C74D8: lw          $v0, -0x19D0($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X19D0);
    // 0x802C74DC: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x802C74E0: bnel        $v0, $at, L_802C74FC
    if (ctx->r2 != ctx->r1) {
        // 0x802C74E4: addiu       $at, $zero, 0x1E
        ctx->r1 = ADD32(0, 0X1E);
            goto L_802C74FC;
    }
    goto skip_0;
    // 0x802C74E4: addiu       $at, $zero, 0x1E
    ctx->r1 = ADD32(0, 0X1E);
    skip_0:
    // 0x802C74E8: jal         0x800C1F60
    // 0x802C74EC: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    func_800C1F60(rdram, ctx);
        goto after_3;
    // 0x802C74EC: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    after_3:
    // 0x802C74F0: b           L_802C7564
    // 0x802C74F4: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_802C7564;
    // 0x802C74F4: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x802C74F8: addiu       $at, $zero, 0x1E
    ctx->r1 = ADD32(0, 0X1E);
L_802C74FC:
    // 0x802C74FC: bnel        $v0, $at, L_802C7518
    if (ctx->r2 != ctx->r1) {
        // 0x802C7500: addiu       $at, $zero, 0x28
        ctx->r1 = ADD32(0, 0X28);
            goto L_802C7518;
    }
    goto skip_1;
    // 0x802C7500: addiu       $at, $zero, 0x28
    ctx->r1 = ADD32(0, 0X28);
    skip_1:
    // 0x802C7504: jal         0x800C1F60
    // 0x802C7508: addiu       $a0, $zero, 0x2
    ctx->r4 = ADD32(0, 0X2);
    func_800C1F60(rdram, ctx);
        goto after_4;
    // 0x802C7508: addiu       $a0, $zero, 0x2
    ctx->r4 = ADD32(0, 0X2);
    after_4:
    // 0x802C750C: b           L_802C7564
    // 0x802C7510: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_802C7564;
    // 0x802C7510: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x802C7514: addiu       $at, $zero, 0x28
    ctx->r1 = ADD32(0, 0X28);
L_802C7518:
    // 0x802C7518: bnel        $v0, $at, L_802C7534
    if (ctx->r2 != ctx->r1) {
        // 0x802C751C: addiu       $at, $zero, 0xA
        ctx->r1 = ADD32(0, 0XA);
            goto L_802C7534;
    }
    goto skip_2;
    // 0x802C751C: addiu       $at, $zero, 0xA
    ctx->r1 = ADD32(0, 0XA);
    skip_2:
    // 0x802C7520: jal         0x800C1F60
    // 0x802C7524: addiu       $a0, $zero, 0x7
    ctx->r4 = ADD32(0, 0X7);
    func_800C1F60(rdram, ctx);
        goto after_5;
    // 0x802C7524: addiu       $a0, $zero, 0x7
    ctx->r4 = ADD32(0, 0X7);
    after_5:
    // 0x802C7528: b           L_802C7564
    // 0x802C752C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_802C7564;
    // 0x802C752C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x802C7530: addiu       $at, $zero, 0xA
    ctx->r1 = ADD32(0, 0XA);
L_802C7534:
    // 0x802C7534: bnel        $v0, $at, L_802C7550
    if (ctx->r2 != ctx->r1) {
        // 0x802C7538: addiu       $at, $zero, 0x14
        ctx->r1 = ADD32(0, 0X14);
            goto L_802C7550;
    }
    goto skip_3;
    // 0x802C7538: addiu       $at, $zero, 0x14
    ctx->r1 = ADD32(0, 0X14);
    skip_3:
    // 0x802C753C: jal         0x800C1F60
    // 0x802C7540: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    func_800C1F60(rdram, ctx);
        goto after_6;
    // 0x802C7540: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    after_6:
    // 0x802C7544: b           L_802C7564
    // 0x802C7548: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_802C7564;
    // 0x802C7548: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x802C754C: addiu       $at, $zero, 0x14
    ctx->r1 = ADD32(0, 0X14);
L_802C7550:
    // 0x802C7550: bnel        $v0, $at, L_802C7564
    if (ctx->r2 != ctx->r1) {
        // 0x802C7554: lw          $ra, 0x14($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X14);
            goto L_802C7564;
    }
    goto skip_4;
    // 0x802C7554: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    skip_4:
    // 0x802C7558: jal         0x800C1F60
    // 0x802C755C: addiu       $a0, $zero, 0xA
    ctx->r4 = ADD32(0, 0XA);
    func_800C1F60(rdram, ctx);
        goto after_7;
    // 0x802C755C: addiu       $a0, $zero, 0xA
    ctx->r4 = ADD32(0, 0XA);
    after_7:
    // 0x802C7560: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C7564:
    // 0x802C7564: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x802C7568: jr          $ra
    // 0x802C756C: nop

    return;
    // 0x802C756C: nop

;}
RECOMP_FUNC void func_i1_802C7570(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C7570: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x802C7574: addiu       $v0, $v0, -0x54DC
    ctx->r2 = ADD32(ctx->r2, -0X54DC);
    // 0x802C7578: lw          $t6, 0x0($v0)
    ctx->r14 = MEM_W(ctx->r2, 0X0);
    // 0x802C757C: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C7580: addiu       $t7, $zero, 0x2D
    ctx->r15 = ADD32(0, 0X2D);
    // 0x802C7584: sw          $t6, -0x19CC($at)
    MEM_W(-0X19CC, ctx->r1) = ctx->r14;
    // 0x802C7588: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C758C: sw          $a0, -0x19D0($at)
    MEM_W(-0X19D0, ctx->r1) = ctx->r4;
    // 0x802C7590: addiu       $v1, $zero, 0x1
    ctx->r3 = ADD32(0, 0X1);
    // 0x802C7594: sw          $t7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r15;
    // 0x802C7598: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C759C: sw          $v1, -0x19C8($at)
    MEM_W(-0X19C8, ctx->r1) = ctx->r3;
    // 0x802C75A0: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C75A4: sw          $v1, -0x19C4($at)
    MEM_W(-0X19C4, ctx->r1) = ctx->r3;
    // 0x802C75A8: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C75AC: sw          $zero, -0x19C0($at)
    MEM_W(-0X19C0, ctx->r1) = 0;
    // 0x802C75B0: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C75B4: sw          $zero, -0x19BC($at)
    MEM_W(-0X19BC, ctx->r1) = 0;
    // 0x802C75B8: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x802C75BC: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x802C75C0: sw          $zero, -0x54E4($at)
    MEM_W(-0X54E4, ctx->r1) = 0;
    // 0x802C75C4: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x802C75C8: lui         $at, 0x800D
    ctx->r1 = S32(0X800D << 16);
    // 0x802C75CC: addiu       $t8, $zero, 0x3
    ctx->r24 = ADD32(0, 0X3);
    // 0x802C75D0: sw          $t8, 0x461C($at)
    MEM_W(0X461C, ctx->r1) = ctx->r24;
    // 0x802C75D4: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    // 0x802C75D8: jal         0x801E6A4C
    // 0x802C75DC: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_801E6A4C(rdram, ctx);
        goto after_0;
    // 0x802C75DC: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_0:
    // 0x802C75E0: addiu       $t9, $zero, 0x1
    ctx->r25 = ADD32(0, 0X1);
    // 0x802C75E4: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x802C75E8: sw          $t9, -0x755C($at)
    MEM_W(-0X755C, ctx->r1) = ctx->r25;
    // 0x802C75EC: addiu       $a0, $zero, 0x3
    ctx->r4 = ADD32(0, 0X3);
    // 0x802C75F0: jal         0x800C21F4
    // 0x802C75F4: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C21F4(rdram, ctx);
        goto after_1;
    // 0x802C75F4: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_1:
    // 0x802C75F8: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x802C75FC: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x802C7600: jr          $ra
    // 0x802C7604: nop

    return;
    // 0x802C7604: nop

;}
RECOMP_FUNC void func_i1_802C7608(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C7608: lui         $t6, 0x801D
    ctx->r14 = S32(0X801D << 16);
    // 0x802C760C: lw          $t6, -0x19C4($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X19C4);
    // 0x802C7610: addiu       $sp, $sp, -0x1A8
    ctx->r29 = ADD32(ctx->r29, -0X1A8);
    // 0x802C7614: sw          $ra, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r31;
    // 0x802C7618: beq         $t6, $zero, L_802C783C
    if (ctx->r14 == 0) {
        // 0x802C761C: sw          $s0, 0x38($sp)
        MEM_W(0X38, ctx->r29) = ctx->r16;
            goto L_802C783C;
    }
    // 0x802C761C: sw          $s0, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r16;
    // 0x802C7620: lui         $a1, 0x801C
    ctx->r5 = S32(0X801C << 16);
    // 0x802C7624: lw          $a1, 0x2650($a1)
    ctx->r5 = MEM_W(ctx->r5, 0X2650);
    // 0x802C7628: lui         $t7, 0x800E
    ctx->r15 = S32(0X800E << 16);
    // 0x802C762C: beq         $a1, $zero, L_802C7718
    if (ctx->r5 == 0) {
        // 0x802C7630: nop
    
            goto L_802C7718;
    }
    // 0x802C7630: nop

    // 0x802C7634: lh          $t7, -0x5498($t7)
    ctx->r15 = MEM_H(ctx->r15, -0X5498);
    // 0x802C7638: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
    // 0x802C763C: lui         $t8, 0x800E
    ctx->r24 = S32(0X800E << 16);
    // 0x802C7640: beq         $t7, $zero, L_802C76A4
    if (ctx->r15 == 0) {
        // 0x802C7644: lui         $t2, 0x801C
        ctx->r10 = S32(0X801C << 16);
            goto L_802C76A4;
    }
    // 0x802C7644: lui         $t2, 0x801C
    ctx->r10 = S32(0X801C << 16);
    // 0x802C7648: lui         $t3, 0x800E
    ctx->r11 = S32(0X800E << 16);
    // 0x802C764C: lw          $t3, -0x5650($t3)
    ctx->r11 = MEM_W(ctx->r11, -0X5650);
    // 0x802C7650: lw          $t8, -0x7E90($t8)
    ctx->r24 = MEM_W(ctx->r24, -0X7E90);
    // 0x802C7654: lui         $t5, 0x801D
    ctx->r13 = S32(0X801D << 16);
    // 0x802C7658: sll         $t4, $t3, 3
    ctx->r12 = S32(ctx->r11 << 3);
    // 0x802C765C: sll         $t9, $t8, 2
    ctx->r25 = S32(ctx->r24 << 2);
    // 0x802C7660: subu        $t4, $t4, $t3
    ctx->r12 = SUB32(ctx->r12, ctx->r11);
    // 0x802C7664: addu        $t9, $t9, $t8
    ctx->r25 = ADD32(ctx->r25, ctx->r24);
    // 0x802C7668: sll         $t9, $t9, 2
    ctx->r25 = S32(ctx->r25 << 2);
    // 0x802C766C: sll         $t4, $t4, 1
    ctx->r12 = S32(ctx->r12 << 1);
    // 0x802C7670: addiu       $t5, $t5, -0x4D68
    ctx->r13 = ADD32(ctx->r13, -0X4D68);
    // 0x802C7674: addiu       $t2, $t2, 0x23B0
    ctx->r10 = ADD32(ctx->r10, 0X23B0);
    // 0x802C7678: addu        $a0, $t9, $t2
    ctx->r4 = ADD32(ctx->r25, ctx->r10);
    // 0x802C767C: addu        $v0, $t4, $t5
    ctx->r2 = ADD32(ctx->r12, ctx->r13);
    // 0x802C7680: addiu       $a1, $zero, 0x3
    ctx->r5 = ADD32(0, 0X3);
L_802C7684:
    // 0x802C7684: lb          $t6, 0x0($v0)
    ctx->r14 = MEM_B(ctx->r2, 0X0);
    // 0x802C7688: addiu       $v1, $v1, 0x1
    ctx->r3 = ADD32(ctx->r3, 0X1);
    // 0x802C768C: addiu       $a0, $a0, 0x1
    ctx->r4 = ADD32(ctx->r4, 0X1);
    // 0x802C7690: addiu       $v0, $v0, 0x1
    ctx->r2 = ADD32(ctx->r2, 0X1);
    // 0x802C7694: bne         $v1, $a1, L_802C7684
    if (ctx->r3 != ctx->r5) {
        // 0x802C7698: sb          $t6, 0xF($a0)
        MEM_B(0XF, ctx->r4) = ctx->r14;
            goto L_802C7684;
    }
    // 0x802C7698: sb          $t6, 0xF($a0)
    MEM_B(0XF, ctx->r4) = ctx->r14;
    // 0x802C769C: b           L_802C7718
    // 0x802C76A0: sb          $zero, 0x10($a0)
    MEM_B(0X10, ctx->r4) = 0;
        goto L_802C7718;
    // 0x802C76A0: sb          $zero, 0x10($a0)
    MEM_B(0X10, ctx->r4) = 0;
L_802C76A4:
    // 0x802C76A4: lui         $t2, 0x800E
    ctx->r10 = S32(0X800E << 16);
    // 0x802C76A8: lw          $t2, -0x7E90($t2)
    ctx->r10 = MEM_W(ctx->r10, -0X7E90);
    // 0x802C76AC: lui         $t7, 0x800E
    ctx->r15 = S32(0X800E << 16);
    // 0x802C76B0: lw          $t7, -0x5650($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X5650);
    // 0x802C76B4: sll         $t4, $a1, 2
    ctx->r12 = S32(ctx->r5 << 2);
    // 0x802C76B8: sll         $t3, $t2, 4
    ctx->r11 = S32(ctx->r10 << 4);
    // 0x802C76BC: addu        $t4, $t4, $a1
    ctx->r12 = ADD32(ctx->r12, ctx->r5);
    // 0x802C76C0: subu        $t3, $t3, $t2
    ctx->r11 = SUB32(ctx->r11, ctx->r10);
    // 0x802C76C4: sll         $t8, $t7, 3
    ctx->r24 = S32(ctx->r15 << 3);
    // 0x802C76C8: sll         $t3, $t3, 2
    ctx->r11 = S32(ctx->r11 << 2);
    // 0x802C76CC: sll         $t4, $t4, 2
    ctx->r12 = S32(ctx->r12 << 2);
    // 0x802C76D0: lui         $t9, 0x801D
    ctx->r25 = S32(0X801D << 16);
    // 0x802C76D4: lui         $t6, 0x801C
    ctx->r14 = S32(0X801C << 16);
    // 0x802C76D8: subu        $t8, $t8, $t7
    ctx->r24 = SUB32(ctx->r24, ctx->r15);
    // 0x802C76DC: sll         $t8, $t8, 1
    ctx->r24 = S32(ctx->r24 << 1);
    // 0x802C76E0: addiu       $t6, $t6, 0x1FF0
    ctx->r14 = ADD32(ctx->r14, 0X1FF0);
    // 0x802C76E4: addiu       $t9, $t9, -0x4D68
    ctx->r25 = ADD32(ctx->r25, -0X4D68);
    // 0x802C76E8: addu        $t5, $t3, $t4
    ctx->r13 = ADD32(ctx->r11, ctx->r12);
    // 0x802C76EC: addu        $a0, $t5, $t6
    ctx->r4 = ADD32(ctx->r13, ctx->r14);
    // 0x802C76F0: addu        $v0, $t8, $t9
    ctx->r2 = ADD32(ctx->r24, ctx->r25);
    // 0x802C76F4: addiu       $a1, $zero, 0x3
    ctx->r5 = ADD32(0, 0X3);
    // 0x802C76F8: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
L_802C76FC:
    // 0x802C76FC: lb          $t7, 0x0($v0)
    ctx->r15 = MEM_B(ctx->r2, 0X0);
    // 0x802C7700: addiu       $v1, $v1, 0x1
    ctx->r3 = ADD32(ctx->r3, 0X1);
    // 0x802C7704: addiu       $v0, $v0, 0x1
    ctx->r2 = ADD32(ctx->r2, 0X1);
    // 0x802C7708: addiu       $a0, $a0, 0x1
    ctx->r4 = ADD32(ctx->r4, 0X1);
    // 0x802C770C: bne         $v1, $a1, L_802C76FC
    if (ctx->r3 != ctx->r5) {
        // 0x802C7710: sb          $t7, -0x5($a0)
        MEM_B(-0X5, ctx->r4) = ctx->r15;
            goto L_802C76FC;
    }
    // 0x802C7710: sb          $t7, -0x5($a0)
    MEM_B(-0X5, ctx->r4) = ctx->r15;
    // 0x802C7714: sb          $zero, -0x4($a0)
    MEM_B(-0X4, ctx->r4) = 0;
L_802C7718:
    // 0x802C7718: lui         $t8, 0x801C
    ctx->r24 = S32(0X801C << 16);
    // 0x802C771C: lw          $t8, 0x2654($t8)
    ctx->r24 = MEM_W(ctx->r24, 0X2654);
    // 0x802C7720: addiu       $a1, $zero, 0x3
    ctx->r5 = ADD32(0, 0X3);
    // 0x802C7724: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
    // 0x802C7728: beq         $t8, $zero, L_802C7788
    if (ctx->r24 == 0) {
        // 0x802C772C: lui         $t9, 0x800E
        ctx->r25 = S32(0X800E << 16);
            goto L_802C7788;
    }
    // 0x802C772C: lui         $t9, 0x800E
    ctx->r25 = S32(0X800E << 16);
    // 0x802C7730: lui         $t4, 0x800E
    ctx->r12 = S32(0X800E << 16);
    // 0x802C7734: lw          $t4, -0x7E90($t4)
    ctx->r12 = MEM_W(ctx->r12, -0X7E90);
    // 0x802C7738: lw          $t9, -0x5650($t9)
    ctx->r25 = MEM_W(ctx->r25, -0X5650);
    // 0x802C773C: lui         $t3, 0x801D
    ctx->r11 = S32(0X801D << 16);
    // 0x802C7740: sll         $t5, $t4, 2
    ctx->r13 = S32(ctx->r12 << 2);
    // 0x802C7744: sll         $t2, $t9, 3
    ctx->r10 = S32(ctx->r25 << 3);
    // 0x802C7748: lui         $t6, 0x801C
    ctx->r14 = S32(0X801C << 16);
    // 0x802C774C: addu        $t5, $t5, $t4
    ctx->r13 = ADD32(ctx->r13, ctx->r12);
    // 0x802C7750: subu        $t2, $t2, $t9
    ctx->r10 = SUB32(ctx->r10, ctx->r25);
    // 0x802C7754: sll         $t2, $t2, 1
    ctx->r10 = S32(ctx->r10 << 1);
    // 0x802C7758: sll         $t5, $t5, 2
    ctx->r13 = S32(ctx->r13 << 2);
    // 0x802C775C: addiu       $t6, $t6, 0x22C0
    ctx->r14 = ADD32(ctx->r14, 0X22C0);
    // 0x802C7760: addiu       $t3, $t3, -0x4D68
    ctx->r11 = ADD32(ctx->r11, -0X4D68);
    // 0x802C7764: addu        $v0, $t2, $t3
    ctx->r2 = ADD32(ctx->r10, ctx->r11);
    // 0x802C7768: addu        $a0, $t5, $t6
    ctx->r4 = ADD32(ctx->r13, ctx->r14);
L_802C776C:
    // 0x802C776C: lb          $t7, 0x0($v0)
    ctx->r15 = MEM_B(ctx->r2, 0X0);
    // 0x802C7770: addiu       $v1, $v1, 0x1
    ctx->r3 = ADD32(ctx->r3, 0X1);
    // 0x802C7774: addiu       $v0, $v0, 0x1
    ctx->r2 = ADD32(ctx->r2, 0X1);
    // 0x802C7778: addiu       $a0, $a0, 0x1
    ctx->r4 = ADD32(ctx->r4, 0X1);
    // 0x802C777C: bne         $v1, $a1, L_802C776C
    if (ctx->r3 != ctx->r5) {
        // 0x802C7780: sb          $t7, 0xF($a0)
        MEM_B(0XF, ctx->r4) = ctx->r15;
            goto L_802C776C;
    }
    // 0x802C7780: sb          $t7, 0xF($a0)
    MEM_B(0XF, ctx->r4) = ctx->r15;
    // 0x802C7784: sb          $zero, 0x10($a0)
    MEM_B(0X10, ctx->r4) = 0;
L_802C7788:
    // 0x802C7788: jal         0x80077F5C
    // 0x802C778C: nop

    func_80077F5C(rdram, ctx);
        goto after_0;
    // 0x802C778C: nop

    after_0:
    // 0x802C7790: jal         0x80094ACC
    // 0x802C7794: nop

    func_80094ACC(rdram, ctx);
        goto after_1;
    // 0x802C7794: nop

    after_1:
    // 0x802C7798: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x802C779C: lw          $v0, -0x4CC8($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X4CC8);
    // 0x802C77A0: bnel        $v0, $zero, L_802C77C4
    if (ctx->r2 != 0) {
        // 0x802C77A4: addiu       $at, $zero, 0x1
        ctx->r1 = ADD32(0, 0X1);
            goto L_802C77C4;
    }
    goto skip_0;
    // 0x802C77A4: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    skip_0:
    // 0x802C77A8: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x802C77AC: addiu       $v0, $v0, -0x4D80
    ctx->r2 = ADD32(ctx->r2, -0X4D80);
    // 0x802C77B0: lb          $t8, 0x0($v0)
    ctx->r24 = MEM_B(ctx->r2, 0X0);
    // 0x802C77B4: ori         $t9, $t8, 0x1
    ctx->r25 = ctx->r24 | 0X1;
    // 0x802C77B8: b           L_802C783C
    // 0x802C77BC: sb          $t9, 0x0($v0)
    MEM_B(0X0, ctx->r2) = ctx->r25;
        goto L_802C783C;
    // 0x802C77BC: sb          $t9, 0x0($v0)
    MEM_B(0X0, ctx->r2) = ctx->r25;
    // 0x802C77C0: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
L_802C77C4:
    // 0x802C77C4: bnel        $v0, $at, L_802C77E8
    if (ctx->r2 != ctx->r1) {
        // 0x802C77C8: addiu       $at, $zero, 0x2
        ctx->r1 = ADD32(0, 0X2);
            goto L_802C77E8;
    }
    goto skip_1;
    // 0x802C77C8: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    skip_1:
    // 0x802C77CC: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x802C77D0: addiu       $v0, $v0, -0x4D80
    ctx->r2 = ADD32(ctx->r2, -0X4D80);
    // 0x802C77D4: lb          $t2, 0x0($v0)
    ctx->r10 = MEM_B(ctx->r2, 0X0);
    // 0x802C77D8: ori         $t3, $t2, 0x2
    ctx->r11 = ctx->r10 | 0X2;
    // 0x802C77DC: b           L_802C783C
    // 0x802C77E0: sb          $t3, 0x0($v0)
    MEM_B(0X0, ctx->r2) = ctx->r11;
        goto L_802C783C;
    // 0x802C77E0: sb          $t3, 0x0($v0)
    MEM_B(0X0, ctx->r2) = ctx->r11;
    // 0x802C77E4: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
L_802C77E8:
    // 0x802C77E8: bne         $v0, $at, L_802C783C
    if (ctx->r2 != ctx->r1) {
        // 0x802C77EC: lui         $v0, 0x801D
        ctx->r2 = S32(0X801D << 16);
            goto L_802C783C;
    }
    // 0x802C77EC: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x802C77F0: addiu       $v0, $v0, -0x4D80
    ctx->r2 = ADD32(ctx->r2, -0X4D80);
    // 0x802C77F4: lb          $t4, 0x0($v0)
    ctx->r12 = MEM_B(ctx->r2, 0X0);
    // 0x802C77F8: lui         $t6, 0x800D
    ctx->r14 = S32(0X800D << 16);
    // 0x802C77FC: lui         $t8, 0x801C
    ctx->r24 = S32(0X801C << 16);
    // 0x802C7800: ori         $t5, $t4, 0x4
    ctx->r13 = ctx->r12 | 0X4;
    // 0x802C7804: sb          $t5, 0x0($v0)
    MEM_B(0X0, ctx->r2) = ctx->r13;
    // 0x802C7808: lw          $t6, 0x48DC($t6)
    ctx->r14 = MEM_W(ctx->r14, 0X48DC);
    // 0x802C780C: sll         $t7, $t6, 3
    ctx->r15 = S32(ctx->r14 << 3);
    // 0x802C7810: subu        $t7, $t7, $t6
    ctx->r15 = SUB32(ctx->r15, ctx->r14);
    // 0x802C7814: sll         $t7, $t7, 4
    ctx->r15 = S32(ctx->r15 << 4);
    // 0x802C7818: subu        $t7, $t7, $t6
    ctx->r15 = SUB32(ctx->r15, ctx->r14);
    // 0x802C781C: sll         $t7, $t7, 3
    ctx->r15 = S32(ctx->r15 << 3);
    // 0x802C7820: addu        $t8, $t8, $t7
    ctx->r24 = ADD32(ctx->r24, ctx->r15);
    // 0x802C7824: lw          $t8, 0x2C70($t8)
    ctx->r24 = MEM_W(ctx->r24, 0X2C70);
    // 0x802C7828: bne         $t8, $zero, L_802C783C
    if (ctx->r24 != 0) {
        // 0x802C782C: nop
    
            goto L_802C783C;
    }
    // 0x802C782C: nop

    // 0x802C7830: lb          $t9, 0x0($v0)
    ctx->r25 = MEM_B(ctx->r2, 0X0);
    // 0x802C7834: ori         $t2, $t9, 0x8
    ctx->r10 = ctx->r25 | 0X8;
    // 0x802C7838: sb          $t2, 0x0($v0)
    MEM_B(0X0, ctx->r2) = ctx->r10;
L_802C783C:
    // 0x802C783C: lui         $t3, 0x802D
    ctx->r11 = S32(0X802D << 16);
    // 0x802C7840: lw          $t3, -0x6AE0($t3)
    ctx->r11 = MEM_W(ctx->r11, -0X6AE0);
    // 0x802C7844: sltiu       $at, $t3, 0x8
    ctx->r1 = ctx->r11 < 0X8 ? 1 : 0;
    // 0x802C7848: beq         $at, $zero, L_802C7AB8
    if (ctx->r1 == 0) {
        // 0x802C784C: sll         $t3, $t3, 2
        ctx->r11 = S32(ctx->r11 << 2);
            goto L_802C7AB8;
    }
    // 0x802C784C: sll         $t3, $t3, 2
    ctx->r11 = S32(ctx->r11 << 2);
    // 0x802C7850: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C7854: addu        $at, $at, $t3
    gpr jr_addend_802C785C = ctx->r11;
    ctx->r1 = ADD32(ctx->r1, ctx->r11);
    // 0x802C7858: lw          $t3, -0x69C8($at)
    ctx->r11 = ADD32(ctx->r1, -0X69C8);
    // 0x802C785C: jr          $t3
    // 0x802C7860: nop

    switch (jr_addend_802C785C >> 2) {
        case 0: goto L_802C7864; break;
        case 1: goto L_802C786C; break;
        case 2: goto L_802C789C; break;
        case 3: goto L_802C78A4; break;
        case 4: goto L_802C78D4; break;
        case 5: goto L_802C799C; break;
        case 6: goto L_802C7AB0; break;
        case 7: goto L_802C7AB0; break;
        default: switch_error(__func__, 0x802C785C, 0x802C9638);
    }
    // 0x802C7860: nop

L_802C7864:
    // 0x802C7864: b           L_802C7AB8
    // 0x802C7868: sw          $zero, 0x1A0($sp)
    MEM_W(0X1A0, ctx->r29) = 0;
        goto L_802C7AB8;
    // 0x802C7868: sw          $zero, 0x1A0($sp)
    MEM_W(0X1A0, ctx->r29) = 0;
L_802C786C:
    // 0x802C786C: lui         $t4, 0x802D
    ctx->r12 = S32(0X802D << 16);
    // 0x802C7870: lw          $t4, -0x6ADC($t4)
    ctx->r12 = MEM_W(ctx->r12, -0X6ADC);
    // 0x802C7874: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C7878: sw          $zero, 0x1A0($sp)
    MEM_W(0X1A0, ctx->r29) = 0;
    // 0x802C787C: addiu       $t5, $t4, -0x28
    ctx->r13 = ADD32(ctx->r12, -0X28);
    // 0x802C7880: sw          $t5, -0x6ADC($at)
    MEM_W(-0X6ADC, ctx->r1) = ctx->r13;
    // 0x802C7884: slti        $at, $t5, 0x14
    ctx->r1 = SIGNED(ctx->r13) < 0X14 ? 1 : 0;
    // 0x802C7888: beq         $at, $zero, L_802C7AB8
    if (ctx->r1 == 0) {
        // 0x802C788C: addiu       $t6, $zero, 0x14
        ctx->r14 = ADD32(0, 0X14);
            goto L_802C7AB8;
    }
    // 0x802C788C: addiu       $t6, $zero, 0x14
    ctx->r14 = ADD32(0, 0X14);
    // 0x802C7890: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C7894: b           L_802C7AB8
    // 0x802C7898: sw          $t6, -0x6ADC($at)
    MEM_W(-0X6ADC, ctx->r1) = ctx->r14;
        goto L_802C7AB8;
    // 0x802C7898: sw          $t6, -0x6ADC($at)
    MEM_W(-0X6ADC, ctx->r1) = ctx->r14;
L_802C789C:
    // 0x802C789C: b           L_802C7AB8
    // 0x802C78A0: sw          $zero, 0x1A0($sp)
    MEM_W(0X1A0, ctx->r29) = 0;
        goto L_802C7AB8;
    // 0x802C78A0: sw          $zero, 0x1A0($sp)
    MEM_W(0X1A0, ctx->r29) = 0;
L_802C78A4:
    // 0x802C78A4: lui         $t7, 0x802D
    ctx->r15 = S32(0X802D << 16);
    // 0x802C78A8: lw          $t7, -0x6ADC($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X6ADC);
    // 0x802C78AC: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C78B0: sw          $zero, 0x1A0($sp)
    MEM_W(0X1A0, ctx->r29) = 0;
    // 0x802C78B4: addiu       $t8, $t7, -0x28
    ctx->r24 = ADD32(ctx->r15, -0X28);
    // 0x802C78B8: sw          $t8, -0x6ADC($at)
    MEM_W(-0X6ADC, ctx->r1) = ctx->r24;
    // 0x802C78BC: slti        $at, $t8, -0x171
    ctx->r1 = SIGNED(ctx->r24) < -0X171 ? 1 : 0;
    // 0x802C78C0: beq         $at, $zero, L_802C7AB8
    if (ctx->r1 == 0) {
        // 0x802C78C4: addiu       $t9, $zero, -0x171
        ctx->r25 = ADD32(0, -0X171);
            goto L_802C7AB8;
    }
    // 0x802C78C4: addiu       $t9, $zero, -0x171
    ctx->r25 = ADD32(0, -0X171);
    // 0x802C78C8: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C78CC: b           L_802C7AB8
    // 0x802C78D0: sw          $t9, -0x6ADC($at)
    MEM_W(-0X6ADC, ctx->r1) = ctx->r25;
        goto L_802C7AB8;
    // 0x802C78D0: sw          $t9, -0x6ADC($at)
    MEM_W(-0X6ADC, ctx->r1) = ctx->r25;
L_802C78D4:
    // 0x802C78D4: lui         $v1, 0x802D
    ctx->r3 = S32(0X802D << 16);
    // 0x802C78D8: addiu       $v1, $v1, -0x6930
    ctx->r3 = ADD32(ctx->r3, -0X6930);
    // 0x802C78DC: lw          $t3, 0x0($v1)
    ctx->r11 = MEM_W(ctx->r3, 0X0);
    // 0x802C78E0: addiu       $t2, $zero, 0x1
    ctx->r10 = ADD32(0, 0X1);
    // 0x802C78E4: sw          $t2, 0x1A0($sp)
    MEM_W(0X1A0, ctx->r29) = ctx->r10;
    // 0x802C78E8: addiu       $t4, $t3, 0x1
    ctx->r12 = ADD32(ctx->r11, 0X1);
    // 0x802C78EC: slti        $at, $t4, 0xB
    ctx->r1 = SIGNED(ctx->r12) < 0XB ? 1 : 0;
    // 0x802C78F0: sw          $t4, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r12;
    // 0x802C78F4: bne         $at, $zero, L_802C7904
    if (ctx->r1 != 0) {
        // 0x802C78F8: or          $v0, $t4, $zero
        ctx->r2 = ctx->r12 | 0;
            goto L_802C7904;
    }
    // 0x802C78F8: or          $v0, $t4, $zero
    ctx->r2 = ctx->r12 | 0;
    // 0x802C78FC: addiu       $v0, $zero, 0xA
    ctx->r2 = ADD32(0, 0XA);
    // 0x802C7900: sw          $v0, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r2;
L_802C7904:
    // 0x802C7904: addiu       $a0, $zero, 0xA
    ctx->r4 = ADD32(0, 0XA);
    // 0x802C7908: sll         $t5, $v0, 2
    ctx->r13 = S32(ctx->r2 << 2);
    // 0x802C790C: addu        $t5, $t5, $v0
    ctx->r13 = ADD32(ctx->r13, ctx->r2);
    // 0x802C7910: sll         $t5, $t5, 2
    ctx->r13 = S32(ctx->r13 << 2);
    // 0x802C7914: addu        $t5, $t5, $v0
    ctx->r13 = ADD32(ctx->r13, ctx->r2);
    // 0x802C7918: sll         $t5, $t5, 2
    ctx->r13 = S32(ctx->r13 << 2);
    // 0x802C791C: addu        $t5, $t5, $v0
    ctx->r13 = ADD32(ctx->r13, ctx->r2);
    // 0x802C7920: sll         $t5, $t5, 1
    ctx->r13 = S32(ctx->r13 << 1);
    // 0x802C7924: div         $zero, $t5, $a0
    lo = S32(S64(S32(ctx->r13)) / S64(S32(ctx->r4))); hi = S32(S64(S32(ctx->r13)) % S64(S32(ctx->r4)));
    // 0x802C7928: mflo        $t6
    ctx->r14 = lo;
    // 0x802C792C: sll         $t7, $v0, 8
    ctx->r15 = S32(ctx->r2 << 8);
    // 0x802C7930: subu        $t7, $t7, $v0
    ctx->r15 = SUB32(ctx->r15, ctx->r2);
    // 0x802C7934: div         $zero, $t7, $a0
    lo = S32(S64(S32(ctx->r15)) / S64(S32(ctx->r4))); hi = S32(S64(S32(ctx->r15)) % S64(S32(ctx->r4)));
    // 0x802C7938: bne         $a0, $zero, L_802C7944
    if (ctx->r4 != 0) {
        // 0x802C793C: nop
    
            goto L_802C7944;
    }
    // 0x802C793C: nop

    // 0x802C7940: break       7
    do_break(2150398272);
L_802C7944:
    // 0x802C7944: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x802C7948: bne         $a0, $at, L_802C795C
    if (ctx->r4 != ctx->r1) {
        // 0x802C794C: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_802C795C;
    }
    // 0x802C794C: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x802C7950: bne         $t5, $at, L_802C795C
    if (ctx->r13 != ctx->r1) {
        // 0x802C7954: nop
    
            goto L_802C795C;
    }
    // 0x802C7954: nop

    // 0x802C7958: break       6
    do_break(2150398296);
L_802C795C:
    // 0x802C795C: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C7960: sw          $t6, -0x6AD4($at)
    MEM_W(-0X6AD4, ctx->r1) = ctx->r14;
    // 0x802C7964: bne         $a0, $zero, L_802C7970
    if (ctx->r4 != 0) {
        // 0x802C7968: nop
    
            goto L_802C7970;
    }
    // 0x802C7968: nop

    // 0x802C796C: break       7
    do_break(2150398316);
L_802C7970:
    // 0x802C7970: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x802C7974: bne         $a0, $at, L_802C7988
    if (ctx->r4 != ctx->r1) {
        // 0x802C7978: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_802C7988;
    }
    // 0x802C7978: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x802C797C: bne         $t7, $at, L_802C7988
    if (ctx->r15 != ctx->r1) {
        // 0x802C7980: nop
    
            goto L_802C7988;
    }
    // 0x802C7980: nop

    // 0x802C7984: break       6
    do_break(2150398340);
L_802C7988:
    // 0x802C7988: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C798C: mflo        $t8
    ctx->r24 = lo;
    // 0x802C7990: sw          $t8, -0x6AD8($at)
    MEM_W(-0X6AD8, ctx->r1) = ctx->r24;
    // 0x802C7994: b           L_802C7AB8
    // 0x802C7998: nop

        goto L_802C7AB8;
    // 0x802C7998: nop

L_802C799C:
    // 0x802C799C: lui         $v1, 0x802D
    ctx->r3 = S32(0X802D << 16);
    // 0x802C79A0: addiu       $v1, $v1, -0x6930
    ctx->r3 = ADD32(ctx->r3, -0X6930);
    // 0x802C79A4: lw          $t2, 0x0($v1)
    ctx->r10 = MEM_W(ctx->r3, 0X0);
    // 0x802C79A8: addiu       $t9, $zero, 0x1
    ctx->r25 = ADD32(0, 0X1);
    // 0x802C79AC: sw          $t9, 0x1A0($sp)
    MEM_W(0X1A0, ctx->r29) = ctx->r25;
    // 0x802C79B0: addiu       $t3, $t2, 0x1
    ctx->r11 = ADD32(ctx->r10, 0X1);
    // 0x802C79B4: slti        $at, $t3, 0x10
    ctx->r1 = SIGNED(ctx->r11) < 0X10 ? 1 : 0;
    // 0x802C79B8: bne         $at, $zero, L_802C79E8
    if (ctx->r1 != 0) {
        // 0x802C79BC: sw          $t3, 0x0($v1)
        MEM_W(0X0, ctx->r3) = ctx->r11;
            goto L_802C79E8;
    }
    // 0x802C79BC: sw          $t3, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r11;
    // 0x802C79C0: lui         $a2, 0x802D
    ctx->r6 = S32(0X802D << 16);
    // 0x802C79C4: addiu       $a2, $a2, -0x6AD0
    ctx->r6 = ADD32(ctx->r6, -0X6AD0);
    // 0x802C79C8: lw          $v0, 0x0($a2)
    ctx->r2 = MEM_W(ctx->r6, 0X0);
    // 0x802C79CC: sw          $zero, 0x0($v1)
    MEM_W(0X0, ctx->r3) = 0;
    // 0x802C79D0: addiu       $a0, $zero, 0x31
    ctx->r4 = ADD32(0, 0X31);
    // 0x802C79D4: blez        $v0, L_802C79E8
    if (SIGNED(ctx->r2) <= 0) {
        // 0x802C79D8: addiu       $t5, $v0, -0x1
        ctx->r13 = ADD32(ctx->r2, -0X1);
            goto L_802C79E8;
    }
    // 0x802C79D8: addiu       $t5, $v0, -0x1
    ctx->r13 = ADD32(ctx->r2, -0X1);
    // 0x802C79DC: sw          $t5, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r13;
    // 0x802C79E0: jal         0x800C37F4
    // 0x802C79E4: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_2;
    // 0x802C79E4: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_2:
L_802C79E8:
    // 0x802C79E8: lui         $v0, 0x802D
    ctx->r2 = S32(0X802D << 16);
    // 0x802C79EC: lw          $v0, -0x6AD0($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X6AD0);
    // 0x802C79F0: lui         $v1, 0x802D
    ctx->r3 = S32(0X802D << 16);
    // 0x802C79F4: bgtz        $v0, L_802C7A20
    if (SIGNED(ctx->r2) > 0) {
        // 0x802C79F8: addiu       $t6, $v0, -0x1
        ctx->r14 = ADD32(ctx->r2, -0X1);
            goto L_802C7A20;
    }
    // 0x802C79F8: addiu       $t6, $v0, -0x1
    ctx->r14 = ADD32(ctx->r2, -0X1);
    // 0x802C79FC: lw          $v1, -0x6ACC($v1)
    ctx->r3 = MEM_W(ctx->r3, -0X6ACC);
    // 0x802C7A00: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C7A04: addiu       $v1, $v1, -0x3C
    ctx->r3 = ADD32(ctx->r3, -0X3C);
    // 0x802C7A08: sw          $v1, -0x6ACC($at)
    MEM_W(-0X6ACC, ctx->r1) = ctx->r3;
    // 0x802C7A0C: slti        $at, $v1, 0x14
    ctx->r1 = SIGNED(ctx->r3) < 0X14 ? 1 : 0;
    // 0x802C7A10: beq         $at, $zero, L_802C7A20
    if (ctx->r1 == 0) {
        // 0x802C7A14: addiu       $v1, $zero, 0x14
        ctx->r3 = ADD32(0, 0X14);
            goto L_802C7A20;
    }
    // 0x802C7A14: addiu       $v1, $zero, 0x14
    ctx->r3 = ADD32(0, 0X14);
    // 0x802C7A18: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C7A1C: sw          $v1, -0x6ACC($at)
    MEM_W(-0X6ACC, ctx->r1) = ctx->r3;
L_802C7A20:
    // 0x802C7A20: bgtz        $t6, L_802C7A50
    if (SIGNED(ctx->r14) > 0) {
        // 0x802C7A24: addiu       $t7, $v0, -0x2
        ctx->r15 = ADD32(ctx->r2, -0X2);
            goto L_802C7A50;
    }
    // 0x802C7A24: addiu       $t7, $v0, -0x2
    ctx->r15 = ADD32(ctx->r2, -0X2);
    // 0x802C7A28: lui         $v1, 0x802D
    ctx->r3 = S32(0X802D << 16);
    // 0x802C7A2C: lw          $v1, -0x6AC8($v1)
    ctx->r3 = MEM_W(ctx->r3, -0X6AC8);
    // 0x802C7A30: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C7A34: addiu       $v1, $v1, -0x3C
    ctx->r3 = ADD32(ctx->r3, -0X3C);
    // 0x802C7A38: sw          $v1, -0x6AC8($at)
    MEM_W(-0X6AC8, ctx->r1) = ctx->r3;
    // 0x802C7A3C: slti        $at, $v1, 0x14
    ctx->r1 = SIGNED(ctx->r3) < 0X14 ? 1 : 0;
    // 0x802C7A40: beq         $at, $zero, L_802C7A50
    if (ctx->r1 == 0) {
        // 0x802C7A44: addiu       $v1, $zero, 0x14
        ctx->r3 = ADD32(0, 0X14);
            goto L_802C7A50;
    }
    // 0x802C7A44: addiu       $v1, $zero, 0x14
    ctx->r3 = ADD32(0, 0X14);
    // 0x802C7A48: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C7A4C: sw          $v1, -0x6AC8($at)
    MEM_W(-0X6AC8, ctx->r1) = ctx->r3;
L_802C7A50:
    // 0x802C7A50: bgtz        $t7, L_802C7A80
    if (SIGNED(ctx->r15) > 0) {
        // 0x802C7A54: addiu       $t8, $v0, -0x3
        ctx->r24 = ADD32(ctx->r2, -0X3);
            goto L_802C7A80;
    }
    // 0x802C7A54: addiu       $t8, $v0, -0x3
    ctx->r24 = ADD32(ctx->r2, -0X3);
    // 0x802C7A58: lui         $v1, 0x802D
    ctx->r3 = S32(0X802D << 16);
    // 0x802C7A5C: lw          $v1, -0x6AC4($v1)
    ctx->r3 = MEM_W(ctx->r3, -0X6AC4);
    // 0x802C7A60: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C7A64: addiu       $v1, $v1, -0x3C
    ctx->r3 = ADD32(ctx->r3, -0X3C);
    // 0x802C7A68: sw          $v1, -0x6AC4($at)
    MEM_W(-0X6AC4, ctx->r1) = ctx->r3;
    // 0x802C7A6C: slti        $at, $v1, 0x14
    ctx->r1 = SIGNED(ctx->r3) < 0X14 ? 1 : 0;
    // 0x802C7A70: beq         $at, $zero, L_802C7A80
    if (ctx->r1 == 0) {
        // 0x802C7A74: addiu       $v1, $zero, 0x14
        ctx->r3 = ADD32(0, 0X14);
            goto L_802C7A80;
    }
    // 0x802C7A74: addiu       $v1, $zero, 0x14
    ctx->r3 = ADD32(0, 0X14);
    // 0x802C7A78: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C7A7C: sw          $v1, -0x6AC4($at)
    MEM_W(-0X6AC4, ctx->r1) = ctx->r3;
L_802C7A80:
    // 0x802C7A80: bgtz        $t8, L_802C7AB8
    if (SIGNED(ctx->r24) > 0) {
        // 0x802C7A84: lui         $v0, 0x802D
        ctx->r2 = S32(0X802D << 16);
            goto L_802C7AB8;
    }
    // 0x802C7A84: lui         $v0, 0x802D
    ctx->r2 = S32(0X802D << 16);
    // 0x802C7A88: lw          $v0, -0x6AC0($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X6AC0);
    // 0x802C7A8C: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C7A90: addiu       $v0, $v0, -0x3C
    ctx->r2 = ADD32(ctx->r2, -0X3C);
    // 0x802C7A94: sw          $v0, -0x6AC0($at)
    MEM_W(-0X6AC0, ctx->r1) = ctx->r2;
    // 0x802C7A98: slti        $at, $v0, 0x14
    ctx->r1 = SIGNED(ctx->r2) < 0X14 ? 1 : 0;
    // 0x802C7A9C: beq         $at, $zero, L_802C7AB8
    if (ctx->r1 == 0) {
        // 0x802C7AA0: addiu       $v0, $zero, 0x14
        ctx->r2 = ADD32(0, 0X14);
            goto L_802C7AB8;
    }
    // 0x802C7AA0: addiu       $v0, $zero, 0x14
    ctx->r2 = ADD32(0, 0X14);
    // 0x802C7AA4: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C7AA8: b           L_802C7AB8
    // 0x802C7AAC: sw          $v0, -0x6AC0($at)
    MEM_W(-0X6AC0, ctx->r1) = ctx->r2;
        goto L_802C7AB8;
    // 0x802C7AAC: sw          $v0, -0x6AC0($at)
    MEM_W(-0X6AC0, ctx->r1) = ctx->r2;
L_802C7AB0:
    // 0x802C7AB0: addiu       $t9, $zero, 0x1
    ctx->r25 = ADD32(0, 0X1);
    // 0x802C7AB4: sw          $t9, 0x1A0($sp)
    MEM_W(0X1A0, ctx->r29) = ctx->r25;
L_802C7AB8:
    // 0x802C7AB8: lui         $t2, 0x802D
    ctx->r10 = S32(0X802D << 16);
    // 0x802C7ABC: lw          $t2, -0x6ADC($t2)
    ctx->r10 = MEM_W(ctx->r10, -0X6ADC);
    // 0x802C7AC0: addiu       $t3, $zero, 0x28
    ctx->r11 = ADD32(0, 0X28);
    // 0x802C7AC4: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C7AC8: subu        $t4, $t3, $t2
    ctx->r12 = SUB32(ctx->r11, ctx->r10);
    // 0x802C7ACC: sw          $t4, -0x692C($at)
    MEM_W(-0X692C, ctx->r1) = ctx->r12;
    // 0x802C7AD0: lui         $at, 0x4180
    ctx->r1 = S32(0X4180 << 16);
    // 0x802C7AD4: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x802C7AD8: lui         $s0, 0x801D
    ctx->r16 = S32(0X801D << 16);
    // 0x802C7ADC: mtc1        $zero, $f0
    ctx->f0.u32l = 0;
    // 0x802C7AE0: addiu       $s0, $s0, -0x1A08
    ctx->r16 = ADD32(ctx->r16, -0X1A08);
    // 0x802C7AE4: lui         $at, 0x4580
    ctx->r1 = S32(0X4580 << 16);
    // 0x802C7AE8: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x802C7AEC: lw          $a0, 0x0($s0)
    ctx->r4 = MEM_W(ctx->r16, 0X0);
    // 0x802C7AF0: lui         $a1, 0x802D
    ctx->r5 = S32(0X802D << 16);
    // 0x802C7AF4: addiu       $a1, $a1, -0x6928
    ctx->r5 = ADD32(ctx->r5, -0X6928);
    // 0x802C7AF8: lui         $a2, 0x4204
    ctx->r6 = S32(0X4204 << 16);
    // 0x802C7AFC: lui         $a3, 0x3F80
    ctx->r7 = S32(0X3F80 << 16);
    // 0x802C7B00: swc1        $f4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f4.u32l;
    // 0x802C7B04: swc1        $f0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->f0.u32l;
    // 0x802C7B08: swc1        $f0, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->f0.u32l;
    // 0x802C7B0C: addiu       $a0, $a0, 0xA40
    ctx->r4 = ADD32(ctx->r4, 0XA40);
    // 0x802C7B10: jal         0x800481E0
    // 0x802C7B14: swc1        $f6, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->f6.u32l;
    func_800481E0(rdram, ctx);
        goto after_3;
    // 0x802C7B14: swc1        $f6, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->f6.u32l;
    after_3:
    // 0x802C7B18: mtc1        $zero, $f0
    ctx->f0.u32l = 0;
    // 0x802C7B1C: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x802C7B20: mtc1        $at, $f2
    ctx->f2.u32l = ctx->r1;
    // 0x802C7B24: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C7B28: lwc1        $f8, -0x69A8($at)
    ctx->f8.u32l = MEM_W(ctx->r1, -0X69A8);
    // 0x802C7B2C: mfc1        $a1, $f0
    ctx->r5 = (int32_t)ctx->f0.u32l;
    // 0x802C7B30: mfc1        $a2, $f0
    ctx->r6 = (int32_t)ctx->f0.u32l;
    // 0x802C7B34: mfc1        $a3, $f2
    ctx->r7 = (int32_t)ctx->f2.u32l;
    // 0x802C7B38: addiu       $a0, $sp, 0x90
    ctx->r4 = ADD32(ctx->r29, 0X90);
    // 0x802C7B3C: swc1        $f0, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f0.u32l;
    // 0x802C7B40: swc1        $f0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->f0.u32l;
    // 0x802C7B44: swc1        $f0, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->f0.u32l;
    // 0x802C7B48: swc1        $f0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->f0.u32l;
    // 0x802C7B4C: swc1        $f0, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->f0.u32l;
    // 0x802C7B50: swc1        $f2, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->f2.u32l;
    // 0x802C7B54: jal         0x80048A88
    // 0x802C7B58: swc1        $f8, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->f8.u32l;
    func_80048A88(rdram, ctx);
        goto after_4;
    // 0x802C7B58: swc1        $f8, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->f8.u32l;
    after_4:
    // 0x802C7B5C: lui         $v0, 0x8015
    ctx->r2 = S32(0X8015 << 16);
    // 0x802C7B60: addiu       $v0, $v0, 0x4350
    ctx->r2 = ADD32(ctx->r2, 0X4350);
    // 0x802C7B64: lui         $at, 0x43FA
    ctx->r1 = S32(0X43FA << 16);
    // 0x802C7B68: mtc1        $at, $f14
    ctx->f14.u32l = ctx->r1;
    // 0x802C7B6C: lwc1        $f10, 0x1000($v0)
    ctx->f10.u32l = MEM_W(ctx->r2, 0X1000);
    // 0x802C7B70: lwc1        $f16, 0x0($v0)
    ctx->f16.u32l = MEM_W(ctx->r2, 0X0);
    // 0x802C7B74: mtc1        $zero, $f0
    ctx->f0.u32l = 0;
    // 0x802C7B78: mul.s       $f2, $f10, $f14
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f2.fl = MUL_S(ctx->f10.fl, ctx->f14.fl);
    // 0x802C7B7C: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x802C7B80: mtc1        $at, $f18
    ctx->f18.u32l = ctx->r1;
    // 0x802C7B84: mul.s       $f12, $f16, $f14
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f12.fl = MUL_S(ctx->f16.fl, ctx->f14.fl);
    // 0x802C7B88: addiu       $a0, $sp, 0x50
    ctx->r4 = ADD32(ctx->r29, 0X50);
    // 0x802C7B8C: addiu       $a1, $sp, 0x114
    ctx->r5 = ADD32(ctx->r29, 0X114);
    // 0x802C7B90: addiu       $a3, $zero, 0x0
    ctx->r7 = ADD32(0, 0X0);
    // 0x802C7B94: mfc1        $a2, $f2
    ctx->r6 = (int32_t)ctx->f2.u32l;
    // 0x802C7B98: swc1        $f0, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->f0.u32l;
    // 0x802C7B9C: swc1        $f0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->f0.u32l;
    // 0x802C7BA0: swc1        $f12, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f12.u32l;
    // 0x802C7BA4: swc1        $f0, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->f0.u32l;
    // 0x802C7BA8: swc1        $f0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->f0.u32l;
    // 0x802C7BAC: swc1        $f0, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->f0.u32l;
    // 0x802C7BB0: jal         0x800484C8
    // 0x802C7BB4: swc1        $f18, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->f18.u32l;
    func_800484C8(rdram, ctx);
        goto after_5;
    // 0x802C7BB4: swc1        $f18, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->f18.u32l;
    after_5:
    // 0x802C7BB8: addiu       $a0, $sp, 0x90
    ctx->r4 = ADD32(ctx->r29, 0X90);
    // 0x802C7BBC: jal         0x80047E78
    // 0x802C7BC0: addiu       $a1, $sp, 0x154
    ctx->r5 = ADD32(ctx->r29, 0X154);
    SysUtils_MtxToMtxF(rdram, ctx);
        goto after_6;
    // 0x802C7BC0: addiu       $a1, $sp, 0x154
    ctx->r5 = ADD32(ctx->r29, 0X154);
    after_6:
    // 0x802C7BC4: addiu       $a0, $sp, 0x114
    ctx->r4 = ADD32(ctx->r29, 0X114);
    // 0x802C7BC8: addiu       $a1, $sp, 0x154
    ctx->r5 = ADD32(ctx->r29, 0X154);
    // 0x802C7BCC: jal         0x80049EB8
    // 0x802C7BD0: addiu       $a2, $sp, 0xD4
    ctx->r6 = ADD32(ctx->r29, 0XD4);
    SysUtils_MatrixAffineMultiply(rdram, ctx);
        goto after_7;
    // 0x802C7BD0: addiu       $a2, $sp, 0xD4
    ctx->r6 = ADD32(ctx->r29, 0XD4);
    after_7:
    // 0x802C7BD4: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
    // 0x802C7BD8: or          $t0, $zero, $zero
    ctx->r8 = 0 | 0;
    // 0x802C7BDC: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x802C7BE0: addiu       $t1, $zero, 0x58
    ctx->r9 = ADD32(0, 0X58);
L_802C7BE4:
    // 0x802C7BE4: lw          $t5, 0x1A0($sp)
    ctx->r13 = MEM_W(ctx->r29, 0X1A0);
    // 0x802C7BE8: sll         $t6, $v1, 2
    ctx->r14 = S32(ctx->r3 << 2);
    // 0x802C7BEC: lui         $v0, 0x802D
    ctx->r2 = S32(0X802D << 16);
    // 0x802C7BF0: bne         $t5, $zero, L_802C7C18
    if (ctx->r13 != 0) {
        // 0x802C7BF4: addiu       $a0, $sp, 0xD4
        ctx->r4 = ADD32(ctx->r29, 0XD4);
            goto L_802C7C18;
    }
    // 0x802C7BF4: addiu       $a0, $sp, 0xD4
    ctx->r4 = ADD32(ctx->r29, 0XD4);
    // 0x802C7BF8: andi        $a3, $v1, 0x1
    ctx->r7 = ctx->r3 & 0X1;
    // 0x802C7BFC: beq         $a3, $zero, L_802C7C10
    if (ctx->r7 == 0) {
        // 0x802C7C00: lui         $v0, 0x802D
        ctx->r2 = S32(0X802D << 16);
            goto L_802C7C10;
    }
    // 0x802C7C00: lui         $v0, 0x802D
    ctx->r2 = S32(0X802D << 16);
    // 0x802C7C04: lui         $v0, 0x802D
    ctx->r2 = S32(0X802D << 16);
    // 0x802C7C08: b           L_802C7C24
    // 0x802C7C0C: lw          $v0, -0x692C($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X692C);
        goto L_802C7C24;
    // 0x802C7C0C: lw          $v0, -0x692C($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X692C);
L_802C7C10:
    // 0x802C7C10: b           L_802C7C24
    // 0x802C7C14: lw          $v0, -0x6ADC($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X6ADC);
        goto L_802C7C24;
    // 0x802C7C14: lw          $v0, -0x6ADC($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X6ADC);
L_802C7C18:
    // 0x802C7C18: addu        $v0, $v0, $t6
    ctx->r2 = ADD32(ctx->r2, ctx->r14);
    // 0x802C7C1C: lw          $v0, -0x6ACC($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X6ACC);
    // 0x802C7C20: andi        $a3, $v1, 0x1
    ctx->r7 = ctx->r3 & 0X1;
L_802C7C24:
    // 0x802C7C24: lw          $t7, 0x0($s0)
    ctx->r15 = MEM_W(ctx->r16, 0X0);
    // 0x802C7C28: sw          $v0, 0x19C($sp)
    MEM_W(0X19C, ctx->r29) = ctx->r2;
    // 0x802C7C2C: sw          $v1, 0x1A4($sp)
    MEM_W(0X1A4, ctx->r29) = ctx->r3;
    // 0x802C7C30: addu        $a1, $t7, $t0
    ctx->r5 = ADD32(ctx->r15, ctx->r8);
    // 0x802C7C34: addiu       $a1, $a1, 0xA80
    ctx->r5 = ADD32(ctx->r5, 0XA80);
    // 0x802C7C38: sw          $a2, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r6;
    // 0x802C7C3C: sw          $a3, 0x4C($sp)
    MEM_W(0X4C, ctx->r29) = ctx->r7;
    // 0x802C7C40: sw          $t0, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r8;
    // 0x802C7C44: jal         0x80047EE0
    // 0x802C7C48: sw          $t1, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r9;
    SysUtils_MtxFToMtx(rdram, ctx);
        goto after_8;
    // 0x802C7C48: sw          $t1, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r9;
    after_8:
    // 0x802C7C4C: lui         $t3, 0x802D
    ctx->r11 = S32(0X802D << 16);
    // 0x802C7C50: lw          $a2, 0x44($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X44);
    // 0x802C7C54: lw          $t8, 0x0($s0)
    ctx->r24 = MEM_W(ctx->r16, 0X0);
    // 0x802C7C58: addiu       $t3, $t3, -0x6AA0
    ctx->r11 = ADD32(ctx->r11, -0X6AA0);
    // 0x802C7C5C: lw          $at, 0x0($t3)
    ctx->r1 = MEM_W(ctx->r11, 0X0);
    // 0x802C7C60: lw          $v1, 0x1A4($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X1A4);
    // 0x802C7C64: lw          $a3, 0x4C($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X4C);
    // 0x802C7C68: lw          $t0, 0x48($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X48);
    // 0x802C7C6C: lw          $v0, 0x19C($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X19C);
    // 0x802C7C70: lw          $t1, 0x40($sp)
    ctx->r9 = MEM_W(ctx->r29, 0X40);
    // 0x802C7C74: addu        $t9, $t8, $a2
    ctx->r25 = ADD32(ctx->r24, ctx->r6);
    // 0x802C7C78: sw          $at, 0x1280($t9)
    MEM_W(0X1280, ctx->r25) = ctx->r1;
    // 0x802C7C7C: lw          $t5, 0x4($t3)
    ctx->r13 = MEM_W(ctx->r11, 0X4);
    // 0x802C7C80: addiu       $v1, $v1, 0x1
    ctx->r3 = ADD32(ctx->r3, 0X1);
    // 0x802C7C84: addiu       $t0, $t0, 0x40
    ctx->r8 = ADD32(ctx->r8, 0X40);
    // 0x802C7C88: sw          $t5, 0x1284($t9)
    MEM_W(0X1284, ctx->r25) = ctx->r13;
    // 0x802C7C8C: lw          $at, 0x8($t3)
    ctx->r1 = MEM_W(ctx->r11, 0X8);
    // 0x802C7C90: sw          $at, 0x1288($t9)
    MEM_W(0X1288, ctx->r25) = ctx->r1;
    // 0x802C7C94: lw          $t5, 0xC($t3)
    ctx->r13 = MEM_W(ctx->r11, 0XC);
    // 0x802C7C98: addiu       $at, $zero, 0x4
    ctx->r1 = ADD32(0, 0X4);
    // 0x802C7C9C: beq         $a3, $zero, L_802C7CBC
    if (ctx->r7 == 0) {
        // 0x802C7CA0: sw          $t5, 0x128C($t9)
        MEM_W(0X128C, ctx->r25) = ctx->r13;
            goto L_802C7CBC;
    }
    // 0x802C7CA0: sw          $t5, 0x128C($t9)
    MEM_W(0X128C, ctx->r25) = ctx->r13;
    // 0x802C7CA4: lw          $t8, 0x0($s0)
    ctx->r24 = MEM_W(ctx->r16, 0X0);
    // 0x802C7CA8: addiu       $t6, $v0, 0x42
    ctx->r14 = ADD32(ctx->r2, 0X42);
    // 0x802C7CAC: sll         $t7, $t6, 2
    ctx->r15 = S32(ctx->r14 << 2);
    // 0x802C7CB0: addu        $t4, $t8, $a2
    ctx->r12 = ADD32(ctx->r24, ctx->r6);
    // 0x802C7CB4: b           L_802C7CD0
    // 0x802C7CB8: sh          $t7, 0x1288($t4)
    MEM_H(0X1288, ctx->r12) = ctx->r15;
        goto L_802C7CD0;
    // 0x802C7CB8: sh          $t7, 0x1288($t4)
    MEM_H(0X1288, ctx->r12) = ctx->r15;
L_802C7CBC:
    // 0x802C7CBC: lw          $t3, 0x0($s0)
    ctx->r11 = MEM_W(ctx->r16, 0X0);
    // 0x802C7CC0: addiu       $t2, $v0, 0x42
    ctx->r10 = ADD32(ctx->r2, 0X42);
    // 0x802C7CC4: sll         $t9, $t2, 2
    ctx->r25 = S32(ctx->r10 << 2);
    // 0x802C7CC8: addu        $t5, $t3, $a2
    ctx->r13 = ADD32(ctx->r11, ctx->r6);
    // 0x802C7CCC: sh          $t9, 0x1288($t5)
    MEM_H(0X1288, ctx->r13) = ctx->r25;
L_802C7CD0:
    // 0x802C7CD0: lw          $t8, 0x0($s0)
    ctx->r24 = MEM_W(ctx->r16, 0X0);
    // 0x802C7CD4: sll         $t6, $t1, 2
    ctx->r14 = S32(ctx->r9 << 2);
    // 0x802C7CD8: addiu       $t1, $t1, 0x20
    ctx->r9 = ADD32(ctx->r9, 0X20);
    // 0x802C7CDC: addu        $t7, $t8, $a2
    ctx->r15 = ADD32(ctx->r24, ctx->r6);
    // 0x802C7CE0: addiu       $a2, $a2, 0x10
    ctx->r6 = ADD32(ctx->r6, 0X10);
    // 0x802C7CE4: bne         $v1, $at, L_802C7BE4
    if (ctx->r3 != ctx->r1) {
        // 0x802C7CE8: sh          $t6, 0x128A($t7)
        MEM_H(0X128A, ctx->r15) = ctx->r14;
            goto L_802C7BE4;
    }
    // 0x802C7CE8: sh          $t6, 0x128A($t7)
    MEM_H(0X128A, ctx->r15) = ctx->r14;
    // 0x802C7CEC: lw          $ra, 0x3C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X3C);
    // 0x802C7CF0: lw          $s0, 0x38($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X38);
    // 0x802C7CF4: addiu       $sp, $sp, 0x1A8
    ctx->r29 = ADD32(ctx->r29, 0X1A8);
    // 0x802C7CF8: jr          $ra
    // 0x802C7CFC: nop

    return;
    // 0x802C7CFC: nop

;}
RECOMP_FUNC void func_i1_802C7D00(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C7D00: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x802C7D04: addiu       $v0, $v0, -0x19C4
    ctx->r2 = ADD32(ctx->r2, -0X19C4);
    // 0x802C7D08: lw          $t6, 0x0($v0)
    ctx->r14 = MEM_W(ctx->r2, 0X0);
    // 0x802C7D0C: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x802C7D10: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x802C7D14: beq         $t6, $zero, L_802C7D20
    if (ctx->r14 == 0) {
        // 0x802C7D18: nop
    
            goto L_802C7D20;
    }
    // 0x802C7D18: nop

    // 0x802C7D1C: sw          $zero, 0x0($v0)
    MEM_W(0X0, ctx->r2) = 0;
L_802C7D20:
    // 0x802C7D20: jal         0x8009328C
    // 0x802C7D24: nop

    func_8009328C(rdram, ctx);
        goto after_0;
    // 0x802C7D24: nop

    after_0:
    // 0x802C7D28: jal         0x80093AFC
    // 0x802C7D2C: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    func_80093AFC(rdram, ctx);
        goto after_1;
    // 0x802C7D2C: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    after_1:
    // 0x802C7D30: lui         $t8, 0xFF10
    ctx->r24 = S32(0XFF10 << 16);
    // 0x802C7D34: lui         $t7, 0xE700
    ctx->r15 = S32(0XE700 << 16);
    // 0x802C7D38: ori         $t8, $t8, 0x1A7
    ctx->r24 = ctx->r24 | 0X1A7;
    // 0x802C7D3C: sw          $t7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r15;
    // 0x802C7D40: sw          $zero, 0x4($v0)
    MEM_W(0X4, ctx->r2) = 0;
    // 0x802C7D44: sw          $t8, 0x8($v0)
    MEM_W(0X8, ctx->r2) = ctx->r24;
    // 0x802C7D48: lui         $t9, 0x8015
    ctx->r25 = S32(0X8015 << 16);
    // 0x802C7D4C: lw          $t9, 0x1948($t9)
    ctx->r25 = MEM_W(ctx->r25, 0X1948);
    // 0x802C7D50: lui         $t1, 0x8015
    ctx->r9 = S32(0X8015 << 16);
    // 0x802C7D54: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x802C7D58: sll         $t0, $t9, 2
    ctx->r8 = S32(ctx->r25 << 2);
    // 0x802C7D5C: addu        $t1, $t1, $t0
    ctx->r9 = ADD32(ctx->r9, ctx->r8);
    // 0x802C7D60: lw          $t1, 0x42C0($t1)
    ctx->r9 = MEM_W(ctx->r9, 0X42C0);
    // 0x802C7D64: lui         $t3, 0xED02
    ctx->r11 = S32(0XED02 << 16);
    // 0x802C7D68: addiu       $t3, $t3, 0x50
    ctx->r11 = ADD32(ctx->r11, 0X50);
    // 0x802C7D6C: lui         $t4, 0x68
    ctx->r12 = S32(0X68 << 16);
    // 0x802C7D70: addiu       $t4, $t4, -0x3C94
    ctx->r12 = ADD32(ctx->r12, -0X3C94);
    // 0x802C7D74: addu        $t2, $t1, $at
    ctx->r10 = ADD32(ctx->r9, ctx->r1);
    // 0x802C7D78: sw          $t2, 0xC($v0)
    MEM_W(0XC, ctx->r2) = ctx->r10;
    { extern uint32_t wr64_experimental_viewport_borders(void); if (wr64_experimental_viewport_borders()) { ctx->r11 = 0xED000000U; ctx->r12 = 0x006A03C0U; } }
    // 0x802C7D7C: sw          $t3, 0x10($v0)
    MEM_W(0X10, ctx->r2) = ctx->r11;
    // 0x802C7D80: sw          $t4, 0x14($v0)
    MEM_W(0X14, ctx->r2) = ctx->r12;
    // 0x802C7D84: jal         0x802C7E48
    // 0x802C7D88: addiu       $a0, $v0, 0x18
    ctx->r4 = ADD32(ctx->r2, 0X18);
    func_i1_802C7E48(rdram, ctx);
        goto after_2;
    // 0x802C7D88: addiu       $a0, $v0, 0x18
    ctx->r4 = ADD32(ctx->r2, 0X18);
    after_2:
    // 0x802C7D8C: lui         $t5, 0x800E
    ctx->r13 = S32(0X800E << 16);
    // 0x802C7D90: lw          $t5, -0x54D8($t5)
    ctx->r13 = MEM_W(ctx->r13, -0X54D8);
    // 0x802C7D94: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x802C7D98: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C7D9C: bne         $t5, $at, L_802C7DB8
    if (ctx->r13 != ctx->r1) {
        // 0x802C7DA0: lui         $t6, 0x600
        ctx->r14 = S32(0X600 << 16);
            goto L_802C7DB8;
    }
    // 0x802C7DA0: lui         $t6, 0x600
    ctx->r14 = S32(0X600 << 16);
    // 0x802C7DA4: lui         $t7, 0x107
    ctx->r15 = S32(0X107 << 16);
    // 0x802C7DA8: addiu       $t7, $t7, -0xE98
    ctx->r15 = ADD32(ctx->r15, -0XE98);
    // 0x802C7DAC: sw          $t7, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r15;
    // 0x802C7DB0: addiu       $a0, $v0, 0x8
    ctx->r4 = ADD32(ctx->r2, 0X8);
    // 0x802C7DB4: sw          $t6, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r14;
L_802C7DB8:
    // 0x802C7DB8: jal         0x802C8E70
    // 0x802C7DBC: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    func_i1_802C8E70(rdram, ctx);
        goto after_3;
    // 0x802C7DBC: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    after_3:
    // 0x802C7DC0: lui         $t8, 0x8023
    ctx->r24 = S32(0X8023 << 16);
    // 0x802C7DC4: lh          $t8, -0x75EA($t8)
    ctx->r24 = MEM_H(ctx->r24, -0X75EA);
    // 0x802C7DC8: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x802C7DCC: bnel        $t8, $at, L_802C7E38
    if (ctx->r24 != ctx->r1) {
        // 0x802C7DD0: lw          $ra, 0x14($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X14);
            goto L_802C7E38;
    }
    goto skip_0;
    // 0x802C7DD0: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    skip_0:
    // 0x802C7DD4: jal         0x8007C494
    // 0x802C7DD8: nop

    func_8007C494(rdram, ctx);
        goto after_4;
    // 0x802C7DD8: nop

    after_4:
    // 0x802C7DDC: lui         $t9, 0x801C
    ctx->r25 = S32(0X801C << 16);
    // 0x802C7DE0: lw          $t9, 0x2650($t9)
    ctx->r25 = MEM_W(ctx->r25, 0X2650);
    // 0x802C7DE4: lui         $t0, 0x801C
    ctx->r8 = S32(0X801C << 16);
    // 0x802C7DE8: lui         $t1, 0x800E
    ctx->r9 = S32(0X800E << 16);
    // 0x802C7DEC: bne         $t9, $zero, L_802C7E00
    if (ctx->r25 != 0) {
        // 0x802C7DF0: nop
    
            goto L_802C7E00;
    }
    // 0x802C7DF0: nop

    // 0x802C7DF4: lw          $t0, 0x2654($t0)
    ctx->r8 = MEM_W(ctx->r8, 0X2654);
    // 0x802C7DF8: beq         $t0, $zero, L_802C7E2C
    if (ctx->r8 == 0) {
        // 0x802C7DFC: nop
    
            goto L_802C7E2C;
    }
    // 0x802C7DFC: nop

L_802C7E00:
    // 0x802C7E00: lh          $t1, -0x5498($t1)
    ctx->r9 = MEM_H(ctx->r9, -0X5498);
    // 0x802C7E04: lui         $a0, 0x800E
    ctx->r4 = S32(0X800E << 16);
    // 0x802C7E08: beq         $t1, $zero, L_802C7E24
    if (ctx->r9 == 0) {
        // 0x802C7E0C: nop
    
            goto L_802C7E24;
    }
    // 0x802C7E0C: nop

    // 0x802C7E10: lui         $a0, 0x800E
    ctx->r4 = S32(0X800E << 16);
    // 0x802C7E14: jal         0x8007C204
    // 0x802C7E18: lw          $a0, -0x7E90($a0)
    ctx->r4 = MEM_W(ctx->r4, -0X7E90);
    func_8007C204(rdram, ctx);
        goto after_5;
    // 0x802C7E18: lw          $a0, -0x7E90($a0)
    ctx->r4 = MEM_W(ctx->r4, -0X7E90);
    after_5:
    // 0x802C7E1C: b           L_802C7E2C
    // 0x802C7E20: nop

        goto L_802C7E2C;
    // 0x802C7E20: nop

L_802C7E24:
    // 0x802C7E24: jal         0x8007BEA4
    // 0x802C7E28: lw          $a0, -0x7E90($a0)
    ctx->r4 = MEM_W(ctx->r4, -0X7E90);
    func_8007BEA4(rdram, ctx);
        goto after_6;
    // 0x802C7E28: lw          $a0, -0x7E90($a0)
    ctx->r4 = MEM_W(ctx->r4, -0X7E90);
    after_6:
L_802C7E2C:
    // 0x802C7E2C: jal         0x801ECB98
    // 0x802C7E30: nop

    func_801ECB98(rdram, ctx);
        goto after_7;
    // 0x802C7E30: nop

    after_7:
    // 0x802C7E34: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C7E38:
    // 0x802C7E38: lw          $v0, 0x18($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X18);
    // 0x802C7E3C: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x802C7E40: jr          $ra
    // 0x802C7E44: nop

    return;
    // 0x802C7E44: nop

;}
RECOMP_FUNC void func_i1_802C7E48(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C7E48: addiu       $sp, $sp, -0x128
    ctx->r29 = ADD32(ctx->r29, -0X128);
    // 0x802C7E4C: lui         $t6, 0x802D
    ctx->r14 = S32(0X802D << 16);
    // 0x802C7E50: lw          $t6, -0x6AE0($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X6AE0);
    // 0x802C7E54: sw          $s6, 0x68($sp)
    MEM_W(0X68, ctx->r29) = ctx->r22;
    // 0x802C7E58: or          $s6, $a0, $zero
    ctx->r22 = ctx->r4 | 0;
    // 0x802C7E5C: sltiu       $at, $t6, 0x8
    ctx->r1 = ctx->r14 < 0X8 ? 1 : 0;
    // 0x802C7E60: sw          $ra, 0x74($sp)
    MEM_W(0X74, ctx->r29) = ctx->r31;
    // 0x802C7E64: sw          $fp, 0x70($sp)
    MEM_W(0X70, ctx->r29) = ctx->r30;
    // 0x802C7E68: sw          $s7, 0x6C($sp)
    MEM_W(0X6C, ctx->r29) = ctx->r23;
    // 0x802C7E6C: sw          $s5, 0x64($sp)
    MEM_W(0X64, ctx->r29) = ctx->r21;
    // 0x802C7E70: sw          $s4, 0x60($sp)
    MEM_W(0X60, ctx->r29) = ctx->r20;
    // 0x802C7E74: sw          $s3, 0x5C($sp)
    MEM_W(0X5C, ctx->r29) = ctx->r19;
    // 0x802C7E78: sw          $s2, 0x58($sp)
    MEM_W(0X58, ctx->r29) = ctx->r18;
    // 0x802C7E7C: sw          $s1, 0x54($sp)
    MEM_W(0X54, ctx->r29) = ctx->r17;
    // 0x802C7E80: beq         $at, $zero, L_802C7ED0
    if (ctx->r1 == 0) {
        // 0x802C7E84: sw          $s0, 0x50($sp)
        MEM_W(0X50, ctx->r29) = ctx->r16;
            goto L_802C7ED0;
    }
    // 0x802C7E84: sw          $s0, 0x50($sp)
    MEM_W(0X50, ctx->r29) = ctx->r16;
    // 0x802C7E88: sll         $t6, $t6, 2
    ctx->r14 = S32(ctx->r14 << 2);
    // 0x802C7E8C: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C7E90: addu        $at, $at, $t6
    gpr jr_addend_802C7E98 = ctx->r14;
    ctx->r1 = ADD32(ctx->r1, ctx->r14);
    // 0x802C7E94: lw          $t6, -0x69A4($at)
    ctx->r14 = ADD32(ctx->r1, -0X69A4);
    // 0x802C7E98: jr          $t6
    // 0x802C7E9C: nop

    switch (jr_addend_802C7E98 >> 2) {
        case 0: goto L_802C7EA0; break;
        case 1: goto L_802C7EA0; break;
        case 2: goto L_802C7EA0; break;
        case 3: goto L_802C7EA0; break;
        case 4: goto L_802C7EB8; break;
        case 5: goto L_802C7EB8; break;
        case 6: goto L_802C7EB8; break;
        case 7: goto L_802C7EB8; break;
        default: switch_error(__func__, 0x802C7E98, 0x802C965C);
    }
    // 0x802C7E9C: nop

L_802C7EA0:
    // 0x802C7EA0: addiu       $v1, $zero, 0x24
    ctx->r3 = ADD32(0, 0X24);
    // 0x802C7EA4: addiu       $t0, $zero, 0x127
    ctx->r8 = ADD32(0, 0X127);
    // 0x802C7EA8: sw          $zero, 0x11C($sp)
    MEM_W(0X11C, ctx->r29) = 0;
    // 0x802C7EAC: sw          $t0, 0x110($sp)
    MEM_W(0X110, ctx->r29) = ctx->r8;
    // 0x802C7EB0: b           L_802C7ED0
    // 0x802C7EB4: sw          $v1, 0x114($sp)
    MEM_W(0X114, ctx->r29) = ctx->r3;
        goto L_802C7ED0;
    // 0x802C7EB4: sw          $v1, 0x114($sp)
    MEM_W(0X114, ctx->r29) = ctx->r3;
L_802C7EB8:
    // 0x802C7EB8: addiu       $t7, $zero, 0x1
    ctx->r15 = ADD32(0, 0X1);
    // 0x802C7EBC: addiu       $v1, $zero, 0xD
    ctx->r3 = ADD32(0, 0XD);
    // 0x802C7EC0: addiu       $t0, $zero, 0x15C
    ctx->r8 = ADD32(0, 0X15C);
    // 0x802C7EC4: sw          $t7, 0x11C($sp)
    MEM_W(0X11C, ctx->r29) = ctx->r15;
    // 0x802C7EC8: sw          $t0, 0x110($sp)
    MEM_W(0X110, ctx->r29) = ctx->r8;
    // 0x802C7ECC: sw          $v1, 0x114($sp)
    MEM_W(0X114, ctx->r29) = ctx->r3;
L_802C7ED0:
    // 0x802C7ED0: lw          $t8, 0x11C($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X11C);
    // 0x802C7ED4: lw          $v1, 0x114($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X114);
    // 0x802C7ED8: lw          $t0, 0x110($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X110);
    // 0x802C7EDC: bne         $t8, $zero, L_802C7EEC
    if (ctx->r24 != 0) {
        // 0x802C7EE0: or          $v0, $s6, $zero
        ctx->r2 = ctx->r22 | 0;
            goto L_802C7EEC;
    }
    // 0x802C7EE0: or          $v0, $s6, $zero
    ctx->r2 = ctx->r22 | 0;
    // 0x802C7EE4: b           L_802C7EF0
    // 0x802C7EE8: or          $s3, $zero, $zero
    ctx->r19 = 0 | 0;
        goto L_802C7EF0;
    // 0x802C7EE8: or          $s3, $zero, $zero
    ctx->r19 = 0 | 0;
L_802C7EEC:
    // 0x802C7EEC: addiu       $s3, $zero, 0x2
    ctx->r19 = ADD32(0, 0X2);
L_802C7EF0:
    // 0x802C7EF0: lui         $t1, 0x107
    ctx->r9 = S32(0X107 << 16);
    // 0x802C7EF4: addiu       $t1, $t1, -0x9D8
    ctx->r9 = ADD32(ctx->r9, -0X9D8);
    // 0x802C7EF8: lui         $t9, 0x600
    ctx->r25 = S32(0X600 << 16);
    // 0x802C7EFC: sw          $t9, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r25;
    // 0x802C7F00: sw          $t1, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r9;
    // 0x802C7F04: lw          $t2, 0x11C($sp)
    ctx->r10 = MEM_W(ctx->r29, 0X11C);
    // 0x802C7F08: addiu       $s6, $s6, 0x8
    ctx->r22 = ADD32(ctx->r22, 0X8);
    // 0x802C7F0C: bne         $t2, $zero, L_802C8008
    if (ctx->r10 != 0) {
        // 0x802C7F10: lui         $t3, 0x802D
        ctx->r11 = S32(0X802D << 16);
            goto L_802C8008;
    }
    // 0x802C7F10: lui         $t3, 0x802D
    ctx->r11 = S32(0X802D << 16);
    // 0x802C7F14: lw          $t3, -0x6ADC($t3)
    ctx->r11 = MEM_W(ctx->r11, -0X6ADC);
    // 0x802C7F18: addiu       $t4, $zero, 0x18
    ctx->r12 = ADD32(0, 0X18);
    // 0x802C7F1C: sw          $t4, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r12;
    // 0x802C7F20: addu        $a2, $t3, $v1
    ctx->r6 = ADD32(ctx->r11, ctx->r3);
    // 0x802C7F24: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x802C7F28: or          $a0, $s6, $zero
    ctx->r4 = ctx->r22 | 0;
    // 0x802C7F2C: or          $a1, $s3, $zero
    ctx->r5 = ctx->r19 | 0;
    // 0x802C7F30: addiu       $a3, $zero, 0x19
    ctx->r7 = ADD32(0, 0X19);
    // 0x802C7F34: jal         0x80094338
    // 0x802C7F38: sw          $t0, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r8;
    func_80094338(rdram, ctx);
        goto after_0;
    // 0x802C7F38: sw          $t0, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r8;
    after_0:
    // 0x802C7F3C: lui         $a2, 0x802D
    ctx->r6 = S32(0X802D << 16);
    // 0x802C7F40: lw          $a2, -0x692C($a2)
    ctx->r6 = MEM_W(ctx->r6, -0X692C);
    // 0x802C7F44: addiu       $t5, $zero, 0x171
    ctx->r13 = ADD32(0, 0X171);
    // 0x802C7F48: addiu       $t6, $zero, 0x10
    ctx->r14 = ADD32(0, 0X10);
    // 0x802C7F4C: sw          $t6, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r14;
    // 0x802C7F50: sw          $t5, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r13;
    // 0x802C7F54: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C7F58: or          $a1, $s3, $zero
    ctx->r5 = ctx->r19 | 0;
    // 0x802C7F5C: addiu       $a3, $zero, 0x34
    ctx->r7 = ADD32(0, 0X34);
    // 0x802C7F60: jal         0x80094338
    // 0x802C7F64: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    func_80094338(rdram, ctx);
        goto after_1;
    // 0x802C7F64: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    after_1:
    // 0x802C7F68: lui         $a2, 0x802D
    ctx->r6 = S32(0X802D << 16);
    // 0x802C7F6C: lw          $a2, -0x6ADC($a2)
    ctx->r6 = MEM_W(ctx->r6, -0X6ADC);
    // 0x802C7F70: addiu       $t7, $zero, 0x171
    ctx->r15 = ADD32(0, 0X171);
    // 0x802C7F74: addiu       $t8, $zero, 0x10
    ctx->r24 = ADD32(0, 0X10);
    // 0x802C7F78: sw          $t8, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r24;
    // 0x802C7F7C: sw          $t7, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r15;
    // 0x802C7F80: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C7F84: or          $a1, $s3, $zero
    ctx->r5 = ctx->r19 | 0;
    // 0x802C7F88: addiu       $a3, $zero, 0xC7
    ctx->r7 = ADD32(0, 0XC7);
    // 0x802C7F8C: jal         0x80094338
    // 0x802C7F90: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    func_80094338(rdram, ctx);
        goto after_2;
    // 0x802C7F90: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    after_2:
    // 0x802C7F94: or          $s6, $v0, $zero
    ctx->r22 = ctx->r2 | 0;
    // 0x802C7F98: sw          $zero, 0x124($sp)
    MEM_W(0X124, ctx->r29) = 0;
    // 0x802C7F9C: addiu       $s0, $zero, 0x47
    ctx->r16 = ADD32(0, 0X47);
    // 0x802C7FA0: addiu       $s1, $zero, 0x4
    ctx->r17 = ADD32(0, 0X4);
L_802C7FA4:
    // 0x802C7FA4: lw          $t9, 0x124($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X124);
    // 0x802C7FA8: or          $a0, $s6, $zero
    ctx->r4 = ctx->r22 | 0;
    // 0x802C7FAC: or          $a1, $s3, $zero
    ctx->r5 = ctx->r19 | 0;
    // 0x802C7FB0: andi        $t1, $t9, 0x1
    ctx->r9 = ctx->r25 & 0X1;
    // 0x802C7FB4: beq         $t1, $zero, L_802C7FC8
    if (ctx->r9 == 0) {
        // 0x802C7FB8: or          $a3, $s0, $zero
        ctx->r7 = ctx->r16 | 0;
            goto L_802C7FC8;
    }
    // 0x802C7FB8: or          $a3, $s0, $zero
    ctx->r7 = ctx->r16 | 0;
    // 0x802C7FBC: lui         $s7, 0x802D
    ctx->r23 = S32(0X802D << 16);
    // 0x802C7FC0: b           L_802C7FD0
    // 0x802C7FC4: lw          $s7, -0x692C($s7)
    ctx->r23 = MEM_W(ctx->r23, -0X692C);
        goto L_802C7FD0;
    // 0x802C7FC4: lw          $s7, -0x692C($s7)
    ctx->r23 = MEM_W(ctx->r23, -0X692C);
L_802C7FC8:
    // 0x802C7FC8: lui         $s7, 0x802D
    ctx->r23 = S32(0X802D << 16);
    // 0x802C7FCC: lw          $s7, -0x6ADC($s7)
    ctx->r23 = MEM_W(ctx->r23, -0X6ADC);
L_802C7FD0:
    // 0x802C7FD0: addiu       $t2, $zero, 0x171
    ctx->r10 = ADD32(0, 0X171);
    // 0x802C7FD4: addiu       $t3, $zero, 0x1C
    ctx->r11 = ADD32(0, 0X1C);
    // 0x802C7FD8: sw          $t3, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r11;
    // 0x802C7FDC: sw          $t2, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r10;
    // 0x802C7FE0: jal         0x80094338
    // 0x802C7FE4: addiu       $a2, $s7, 0x8
    ctx->r6 = ADD32(ctx->r23, 0X8);
    func_80094338(rdram, ctx);
        goto after_3;
    // 0x802C7FE4: addiu       $a2, $s7, 0x8
    ctx->r6 = ADD32(ctx->r23, 0X8);
    after_3:
    // 0x802C7FE8: lw          $v1, 0x124($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X124);
    // 0x802C7FEC: addiu       $s0, $s0, 0x20
    ctx->r16 = ADD32(ctx->r16, 0X20);
    // 0x802C7FF0: or          $s6, $v0, $zero
    ctx->r22 = ctx->r2 | 0;
    // 0x802C7FF4: addiu       $v1, $v1, 0x1
    ctx->r3 = ADD32(ctx->r3, 0X1);
    // 0x802C7FF8: bne         $v1, $s1, L_802C7FA4
    if (ctx->r3 != ctx->r17) {
        // 0x802C7FFC: sw          $v1, 0x124($sp)
        MEM_W(0X124, ctx->r29) = ctx->r3;
            goto L_802C7FA4;
    }
    // 0x802C7FFC: sw          $v1, 0x124($sp)
    MEM_W(0X124, ctx->r29) = ctx->r3;
    // 0x802C8000: b           L_802C80E8
    // 0x802C8004: lw          $t6, 0x11C($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X11C);
        goto L_802C80E8;
    // 0x802C8004: lw          $t6, 0x11C($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X11C);
L_802C8008:
    // 0x802C8008: or          $v0, $s6, $zero
    ctx->r2 = ctx->r22 | 0;
    // 0x802C800C: lui         $t4, 0xFA00
    ctx->r12 = S32(0XFA00 << 16);
    // 0x802C8010: sw          $t4, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r12;
    // 0x802C8014: lui         $t5, 0x802D
    ctx->r13 = S32(0X802D << 16);
    // 0x802C8018: lw          $t5, -0x6AD4($t5)
    ctx->r13 = MEM_W(ctx->r13, -0X6AD4);
    // 0x802C801C: addiu       $at, $zero, -0x100
    ctx->r1 = ADD32(0, -0X100);
    // 0x802C8020: addiu       $t8, $zero, 0x18
    ctx->r24 = ADD32(0, 0X18);
    // 0x802C8024: andi        $t6, $t5, 0xFF
    ctx->r14 = ctx->r13 & 0XFF;
    // 0x802C8028: or          $t7, $t6, $at
    ctx->r15 = ctx->r14 | ctx->r1;
    // 0x802C802C: sw          $t7, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r15;
    // 0x802C8030: addiu       $a0, $s6, 0x8
    ctx->r4 = ADD32(ctx->r22, 0X8);
    // 0x802C8034: sw          $t8, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r24;
    // 0x802C8038: sw          $t0, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r8;
    // 0x802C803C: or          $a1, $s3, $zero
    ctx->r5 = ctx->r19 | 0;
    // 0x802C8040: addiu       $a2, $v1, 0x1C
    ctx->r6 = ADD32(ctx->r3, 0X1C);
    // 0x802C8044: jal         0x80094338
    // 0x802C8048: addiu       $a3, $zero, 0x19
    ctx->r7 = ADD32(0, 0X19);
    func_80094338(rdram, ctx);
        goto after_4;
    // 0x802C8048: addiu       $a3, $zero, 0x19
    ctx->r7 = ADD32(0, 0X19);
    after_4:
    // 0x802C804C: addiu       $t9, $zero, 0x171
    ctx->r25 = ADD32(0, 0X171);
    // 0x802C8050: addiu       $t1, $zero, 0x10
    ctx->r9 = ADD32(0, 0X10);
    // 0x802C8054: sw          $t1, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r9;
    // 0x802C8058: sw          $t9, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r25;
    // 0x802C805C: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C8060: or          $a1, $s3, $zero
    ctx->r5 = ctx->r19 | 0;
    // 0x802C8064: addiu       $a2, $zero, 0x1C
    ctx->r6 = ADD32(0, 0X1C);
    // 0x802C8068: jal         0x80094338
    // 0x802C806C: addiu       $a3, $zero, 0x34
    ctx->r7 = ADD32(0, 0X34);
    func_80094338(rdram, ctx);
        goto after_5;
    // 0x802C806C: addiu       $a3, $zero, 0x34
    ctx->r7 = ADD32(0, 0X34);
    after_5:
    // 0x802C8070: addiu       $t2, $zero, 0x171
    ctx->r10 = ADD32(0, 0X171);
    // 0x802C8074: addiu       $t3, $zero, 0x10
    ctx->r11 = ADD32(0, 0X10);
    // 0x802C8078: sw          $t3, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r11;
    // 0x802C807C: sw          $t2, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r10;
    // 0x802C8080: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C8084: or          $a1, $s3, $zero
    ctx->r5 = ctx->r19 | 0;
    // 0x802C8088: addiu       $a2, $zero, 0x1C
    ctx->r6 = ADD32(0, 0X1C);
    // 0x802C808C: jal         0x80094338
    // 0x802C8090: addiu       $a3, $zero, 0xC7
    ctx->r7 = ADD32(0, 0XC7);
    func_80094338(rdram, ctx);
        goto after_6;
    // 0x802C8090: addiu       $a3, $zero, 0xC7
    ctx->r7 = ADD32(0, 0XC7);
    after_6:
    // 0x802C8094: lui         $s1, 0x802D
    ctx->r17 = S32(0X802D << 16);
    // 0x802C8098: lui         $s2, 0x802D
    ctx->r18 = S32(0X802D << 16);
    // 0x802C809C: or          $s6, $v0, $zero
    ctx->r22 = ctx->r2 | 0;
    // 0x802C80A0: addiu       $s2, $s2, -0x6ABC
    ctx->r18 = ADD32(ctx->r18, -0X6ABC);
    // 0x802C80A4: addiu       $s1, $s1, -0x6ACC
    ctx->r17 = ADD32(ctx->r17, -0X6ACC);
    // 0x802C80A8: addiu       $s0, $zero, 0x47
    ctx->r16 = ADD32(0, 0X47);
L_802C80AC:
    // 0x802C80AC: lw          $a2, 0x0($s1)
    ctx->r6 = MEM_W(ctx->r17, 0X0);
    // 0x802C80B0: addiu       $t4, $zero, 0x171
    ctx->r12 = ADD32(0, 0X171);
    // 0x802C80B4: addiu       $t5, $zero, 0x1C
    ctx->r13 = ADD32(0, 0X1C);
    // 0x802C80B8: sw          $t5, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r13;
    // 0x802C80BC: sw          $t4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r12;
    // 0x802C80C0: or          $a0, $s6, $zero
    ctx->r4 = ctx->r22 | 0;
    // 0x802C80C4: or          $a1, $s3, $zero
    ctx->r5 = ctx->r19 | 0;
    // 0x802C80C8: or          $a3, $s0, $zero
    ctx->r7 = ctx->r16 | 0;
    // 0x802C80CC: jal         0x80094338
    // 0x802C80D0: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    func_80094338(rdram, ctx);
        goto after_7;
    // 0x802C80D0: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    after_7:
    // 0x802C80D4: addiu       $s1, $s1, 0x4
    ctx->r17 = ADD32(ctx->r17, 0X4);
    // 0x802C80D8: addiu       $s0, $s0, 0x20
    ctx->r16 = ADD32(ctx->r16, 0X20);
    // 0x802C80DC: bne         $s1, $s2, L_802C80AC
    if (ctx->r17 != ctx->r18) {
        // 0x802C80E0: or          $s6, $v0, $zero
        ctx->r22 = ctx->r2 | 0;
            goto L_802C80AC;
    }
    // 0x802C80E0: or          $s6, $v0, $zero
    ctx->r22 = ctx->r2 | 0;
    // 0x802C80E4: lw          $t6, 0x11C($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X11C);
L_802C80E8:
    // 0x802C80E8: sw          $zero, 0xF4($sp)
    MEM_W(0XF4, ctx->r29) = 0;
    // 0x802C80EC: or          $a0, $s6, $zero
    ctx->r4 = ctx->r22 | 0;
    // 0x802C80F0: bne         $t6, $zero, L_802C81B0
    if (ctx->r14 != 0) {
        // 0x802C80F4: addiu       $a1, $zero, 0xA
        ctx->r5 = ADD32(0, 0XA);
            goto L_802C81B0;
    }
    // 0x802C80F4: addiu       $a1, $zero, 0xA
    ctx->r5 = ADD32(0, 0XA);
    // 0x802C80F8: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C80FC: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C8100: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C8104: addiu       $t1, $zero, 0xFF
    ctx->r9 = ADD32(0, 0XFF);
    // 0x802C8108: addiu       $t2, $zero, 0xFF
    ctx->r10 = ADD32(0, 0XFF);
    // 0x802C810C: addiu       $t3, $zero, 0xFF
    ctx->r11 = ADD32(0, 0XFF);
    // 0x802C8110: addiu       $t4, $zero, 0xFF
    ctx->r12 = ADD32(0, 0XFF);
    // 0x802C8114: addiu       $t5, $zero, 0xFF
    ctx->r13 = ADD32(0, 0XFF);
    // 0x802C8118: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C811C: sw          $t6, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r14;
    // 0x802C8120: sw          $t5, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r13;
    // 0x802C8124: sw          $t4, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r12;
    // 0x802C8128: sw          $t3, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r11;
    // 0x802C812C: sw          $t2, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r10;
    // 0x802C8130: sw          $t1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r9;
    // 0x802C8134: sw          $t9, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r25;
    // 0x802C8138: sw          $t8, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r24;
    // 0x802C813C: sw          $t7, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r15;
    // 0x802C8140: sw          $t7, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r15;
    // 0x802C8144: or          $a0, $s6, $zero
    ctx->r4 = ctx->r22 | 0;
    // 0x802C8148: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C814C: addiu       $a2, $zero, 0xFF
    ctx->r6 = ADD32(0, 0XFF);
    // 0x802C8150: jal         0x801E946C
    // 0x802C8154: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    func_801E946C(rdram, ctx);
        goto after_8;
    // 0x802C8154: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    after_8:
    // 0x802C8158: lui         $a3, 0x802D
    ctx->r7 = S32(0X802D << 16);
    // 0x802C815C: lw          $a3, -0x6ADC($a3)
    ctx->r7 = MEM_W(ctx->r7, -0X6ADC);
    // 0x802C8160: addiu       $t8, $zero, 0x1C
    ctx->r24 = ADD32(0, 0X1C);
    // 0x802C8164: sw          $t8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r24;
    // 0x802C8168: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C816C: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C8170: addiu       $a2, $zero, 0x14
    ctx->r6 = ADD32(0, 0X14);
    // 0x802C8174: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    // 0x802C8178: jal         0x801E3EE0
    // 0x802C817C: addiu       $a3, $a3, 0x6A
    ctx->r7 = ADD32(ctx->r7, 0X6A);
    func_801E3EE0(rdram, ctx);
        goto after_9;
    // 0x802C817C: addiu       $a3, $a3, 0x6A
    ctx->r7 = ADD32(ctx->r7, 0X6A);
    after_9:
    // 0x802C8180: lui         $a3, 0x802D
    ctx->r7 = S32(0X802D << 16);
    // 0x802C8184: lw          $a3, -0x6ADC($a3)
    ctx->r7 = MEM_W(ctx->r7, -0X6ADC);
    // 0x802C8188: addiu       $t9, $zero, 0xCA
    ctx->r25 = ADD32(0, 0XCA);
    // 0x802C818C: sw          $t9, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r25;
    // 0x802C8190: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C8194: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C8198: addiu       $a2, $zero, 0x4F
    ctx->r6 = ADD32(0, 0X4F);
    // 0x802C819C: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    // 0x802C81A0: jal         0x801E3EE0
    // 0x802C81A4: addiu       $a3, $a3, 0x18
    ctx->r7 = ADD32(ctx->r7, 0X18);
    func_801E3EE0(rdram, ctx);
        goto after_10;
    // 0x802C81A4: addiu       $a3, $a3, 0x18
    ctx->r7 = ADD32(ctx->r7, 0X18);
    after_10:
    // 0x802C81A8: b           L_802C8250
    // 0x802C81AC: or          $s6, $v0, $zero
    ctx->r22 = ctx->r2 | 0;
        goto L_802C8250;
    // 0x802C81AC: or          $s6, $v0, $zero
    ctx->r22 = ctx->r2 | 0;
L_802C81B0:
    // 0x802C81B0: lui         $a2, 0x802D
    ctx->r6 = S32(0X802D << 16);
    // 0x802C81B4: addiu       $t1, $zero, 0xFF
    ctx->r9 = ADD32(0, 0XFF);
    // 0x802C81B8: addiu       $t2, $zero, 0xFF
    ctx->r10 = ADD32(0, 0XFF);
    // 0x802C81BC: addiu       $t3, $zero, 0xFF
    ctx->r11 = ADD32(0, 0XFF);
    // 0x802C81C0: addiu       $t4, $zero, 0xFF
    ctx->r12 = ADD32(0, 0XFF);
    // 0x802C81C4: addiu       $t5, $zero, 0xFF
    ctx->r13 = ADD32(0, 0XFF);
    // 0x802C81C8: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C81CC: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C81D0: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C81D4: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C81D8: sw          $t9, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r25;
    // 0x802C81DC: sw          $t8, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r24;
    // 0x802C81E0: sw          $t7, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r15;
    // 0x802C81E4: sw          $t6, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r14;
    // 0x802C81E8: sw          $t5, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r13;
    // 0x802C81EC: sw          $t4, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r12;
    // 0x802C81F0: sw          $t3, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r11;
    // 0x802C81F4: sw          $t2, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r10;
    // 0x802C81F8: sw          $t1, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r9;
    // 0x802C81FC: sw          $t1, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r9;
    // 0x802C8200: lbu         $a2, -0x6AD5($a2)
    ctx->r6 = MEM_BU(ctx->r6, -0X6AD5);
    // 0x802C8204: jal         0x801E946C
    // 0x802C8208: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    func_801E946C(rdram, ctx);
        goto after_11;
    // 0x802C8208: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    after_11:
    // 0x802C820C: addiu       $t2, $zero, 0x1C
    ctx->r10 = ADD32(0, 0X1C);
    // 0x802C8210: sw          $t2, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r10;
    // 0x802C8214: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C8218: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C821C: addiu       $a2, $zero, 0x15
    ctx->r6 = ADD32(0, 0X15);
    // 0x802C8220: addiu       $a3, $zero, 0x71
    ctx->r7 = ADD32(0, 0X71);
    // 0x802C8224: jal         0x801E3EE0
    // 0x802C8228: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    func_801E3EE0(rdram, ctx);
        goto after_12;
    // 0x802C8228: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    after_12:
    // 0x802C822C: addiu       $t3, $zero, 0xCA
    ctx->r11 = ADD32(0, 0XCA);
    // 0x802C8230: sw          $t3, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r11;
    // 0x802C8234: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C8238: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C823C: addiu       $a2, $zero, 0x6
    ctx->r6 = ADD32(0, 0X6);
    // 0x802C8240: addiu       $a3, $zero, 0x2C
    ctx->r7 = ADD32(0, 0X2C);
    // 0x802C8244: jal         0x801E3EE0
    // 0x802C8248: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    func_801E3EE0(rdram, ctx);
        goto after_13;
    // 0x802C8248: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    after_13:
    // 0x802C824C: or          $s6, $v0, $zero
    ctx->r22 = ctx->r2 | 0;
L_802C8250:
    // 0x802C8250: lw          $t4, 0x11C($sp)
    ctx->r12 = MEM_W(ctx->r29, 0X11C);
    // 0x802C8254: or          $a0, $s6, $zero
    ctx->r4 = ctx->r22 | 0;
    // 0x802C8258: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C825C: bne         $t4, $zero, L_802C8270
    if (ctx->r12 != 0) {
        // 0x802C8260: addiu       $a2, $zero, 0x1F
        ctx->r6 = ADD32(0, 0X1F);
            goto L_802C8270;
    }
    // 0x802C8260: addiu       $a2, $zero, 0x1F
    ctx->r6 = ADD32(0, 0X1F);
    // 0x802C8264: lui         $s0, 0x802D
    ctx->r16 = S32(0X802D << 16);
    // 0x802C8268: b           L_802C8274
    // 0x802C826C: lw          $s0, -0x692C($s0)
    ctx->r16 = MEM_W(ctx->r16, -0X692C);
        goto L_802C8274;
    // 0x802C826C: lw          $s0, -0x692C($s0)
    ctx->r16 = MEM_W(ctx->r16, -0X692C);
L_802C8270:
    // 0x802C8270: addiu       $s0, $zero, 0x14
    ctx->r16 = ADD32(0, 0X14);
L_802C8274:
    // 0x802C8274: addiu       $t5, $zero, 0x37
    ctx->r13 = ADD32(0, 0X37);
    // 0x802C8278: sw          $t5, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r13;
    // 0x802C827C: addiu       $a3, $s0, 0xD
    ctx->r7 = ADD32(ctx->r16, 0XD);
    // 0x802C8280: jal         0x801E3EE0
    // 0x802C8284: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    func_801E3EE0(rdram, ctx);
        goto after_14;
    // 0x802C8284: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    after_14:
    // 0x802C8288: addiu       $t6, $zero, 0x37
    ctx->r14 = ADD32(0, 0X37);
    // 0x802C828C: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x802C8290: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C8294: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C8298: addiu       $a2, $zero, 0x20
    ctx->r6 = ADD32(0, 0X20);
    // 0x802C829C: addiu       $a3, $s0, 0xA1
    ctx->r7 = ADD32(ctx->r16, 0XA1);
    // 0x802C82A0: jal         0x801E3EE0
    // 0x802C82A4: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    func_801E3EE0(rdram, ctx);
        goto after_15;
    // 0x802C82A4: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    after_15:
    // 0x802C82A8: addiu       $t7, $zero, 0x37
    ctx->r15 = ADD32(0, 0X37);
    // 0x802C82AC: sw          $t7, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r15;
    // 0x802C82B0: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C82B4: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C82B8: addiu       $a2, $zero, 0x3A
    ctx->r6 = ADD32(0, 0X3A);
    // 0x802C82BC: addiu       $a3, $s0, 0x13F
    ctx->r7 = ADD32(ctx->r16, 0X13F);
    // 0x802C82C0: jal         0x801E3EE0
    // 0x802C82C4: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    func_801E3EE0(rdram, ctx);
        goto after_16;
    // 0x802C82C4: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    after_16:
    // 0x802C82C8: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C82CC: sw          $t8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r24;
    // 0x802C82D0: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C82D4: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C82D8: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x802C82DC: jal         0x801E7E74
    // 0x802C82E0: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_801E7E74(rdram, ctx);
        goto after_17;
    // 0x802C82E0: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_17:
    // 0x802C82E4: or          $s6, $v0, $zero
    ctx->r22 = ctx->r2 | 0;
    // 0x802C82E8: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
    // 0x802C82EC: addiu       $s0, $zero, 0x4A
    ctx->r16 = ADD32(0, 0X4A);
    // 0x802C82F0: addiu       $s1, $zero, 0x5F
    ctx->r17 = ADD32(0, 0X5F);
L_802C82F4:
    // 0x802C82F4: lw          $t9, 0x11C($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X11C);
    // 0x802C82F8: sll         $t2, $v1, 2
    ctx->r10 = S32(ctx->r3 << 2);
    // 0x802C82FC: or          $a0, $s6, $zero
    ctx->r4 = ctx->r22 | 0;
    // 0x802C8300: bne         $t9, $zero, L_802C8328
    if (ctx->r25 != 0) {
        // 0x802C8304: or          $a2, $s0, $zero
        ctx->r6 = ctx->r16 | 0;
            goto L_802C8328;
    }
    // 0x802C8304: or          $a2, $s0, $zero
    ctx->r6 = ctx->r16 | 0;
    // 0x802C8308: andi        $t1, $v1, 0x1
    ctx->r9 = ctx->r3 & 0X1;
    // 0x802C830C: beq         $t1, $zero, L_802C8320
    if (ctx->r9 == 0) {
        // 0x802C8310: lui         $s7, 0x802D
        ctx->r23 = S32(0X802D << 16);
            goto L_802C8320;
    }
    // 0x802C8310: lui         $s7, 0x802D
    ctx->r23 = S32(0X802D << 16);
    // 0x802C8314: lui         $s7, 0x802D
    ctx->r23 = S32(0X802D << 16);
    // 0x802C8318: b           L_802C8334
    // 0x802C831C: lw          $s7, -0x692C($s7)
    ctx->r23 = MEM_W(ctx->r23, -0X692C);
        goto L_802C8334;
    // 0x802C831C: lw          $s7, -0x692C($s7)
    ctx->r23 = MEM_W(ctx->r23, -0X692C);
L_802C8320:
    // 0x802C8320: b           L_802C8334
    // 0x802C8324: lw          $s7, -0x6ADC($s7)
    ctx->r23 = MEM_W(ctx->r23, -0X6ADC);
        goto L_802C8334;
    // 0x802C8324: lw          $s7, -0x6ADC($s7)
    ctx->r23 = MEM_W(ctx->r23, -0X6ADC);
L_802C8328:
    // 0x802C8328: lui         $s7, 0x802D
    ctx->r23 = S32(0X802D << 16);
    // 0x802C832C: addu        $s7, $s7, $t2
    ctx->r23 = ADD32(ctx->r23, ctx->r10);
    // 0x802C8330: lw          $s7, -0x6ACC($s7)
    ctx->r23 = MEM_W(ctx->r23, -0X6ACC);
L_802C8334:
    // 0x802C8334: addiu       $a1, $s7, 0x2A
    ctx->r5 = ADD32(ctx->r23, 0X2A);
    // 0x802C8338: addiu       $a3, $s7, 0x56
    ctx->r7 = ADD32(ctx->r23, 0X56);
    // 0x802C833C: sw          $s1, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r17;
    // 0x802C8340: jal         0x801E7FD8
    // 0x802C8344: sw          $v1, 0x124($sp)
    MEM_W(0X124, ctx->r29) = ctx->r3;
    func_801E7FD8(rdram, ctx);
        goto after_18;
    // 0x802C8344: sw          $v1, 0x124($sp)
    MEM_W(0X124, ctx->r29) = ctx->r3;
    after_18:
    // 0x802C8348: lw          $v1, 0x124($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X124);
    // 0x802C834C: addiu       $s0, $s0, 0x20
    ctx->r16 = ADD32(ctx->r16, 0X20);
    // 0x802C8350: addiu       $s1, $s1, 0x20
    ctx->r17 = ADD32(ctx->r17, 0X20);
    // 0x802C8354: addiu       $v1, $v1, 0x1
    ctx->r3 = ADD32(ctx->r3, 0X1);
    // 0x802C8358: slti        $at, $v1, 0x4
    ctx->r1 = SIGNED(ctx->r3) < 0X4 ? 1 : 0;
    // 0x802C835C: sw          $v1, 0x124($sp)
    MEM_W(0X124, ctx->r29) = ctx->r3;
    // 0x802C8360: bne         $at, $zero, L_802C82F4
    if (ctx->r1 != 0) {
        // 0x802C8364: or          $s6, $v0, $zero
        ctx->r22 = ctx->r2 | 0;
            goto L_802C82F4;
    }
    // 0x802C8364: or          $s6, $v0, $zero
    ctx->r22 = ctx->r2 | 0;
    // 0x802C8368: addiu       $s6, $v0, 0x8
    ctx->r22 = ADD32(ctx->r2, 0X8);
    // 0x802C836C: lui         $t3, 0xE700
    ctx->r11 = S32(0XE700 << 16);
    // 0x802C8370: sw          $t3, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r11;
    // 0x802C8374: sw          $zero, 0x4($v0)
    MEM_W(0X4, ctx->r2) = 0;
    // 0x802C8378: or          $a0, $s6, $zero
    ctx->r4 = ctx->r22 | 0;
    // 0x802C837C: lui         $t4, 0xED02
    ctx->r12 = S32(0XED02 << 16);
    // 0x802C8380: addiu       $t4, $t4, 0x50
    ctx->r12 = ADD32(ctx->r12, 0X50);
    // 0x802C8384: lui         $t5, 0x68
    ctx->r13 = S32(0X68 << 16);
    // 0x802C8388: addiu       $t5, $t5, -0x3C94
    ctx->r13 = ADD32(ctx->r13, -0X3C94);
    { extern uint32_t wr64_experimental_viewport_borders(void); if (wr64_experimental_viewport_borders()) { ctx->r12 = 0xED000000U; ctx->r13 = 0x006A03C0U; } }
    // 0x802C838C: sw          $t4, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r12;
    // 0x802C8390: sw          $t5, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r13;
    // 0x802C8394: addiu       $t6, $zero, 0x1
    ctx->r14 = ADD32(0, 0X1);
    // 0x802C8398: addiu       $t7, $zero, 0x1
    ctx->r15 = ADD32(0, 0X1);
    // 0x802C839C: addiu       $t8, $zero, 0x1
    ctx->r24 = ADD32(0, 0X1);
    // 0x802C83A0: addiu       $t9, $zero, 0x4B
    ctx->r25 = ADD32(0, 0X4B);
    // 0x802C83A4: addiu       $s6, $s6, 0x8
    ctx->r22 = ADD32(ctx->r22, 0X8);
    // 0x802C83A8: sw          $t8, 0xF0($sp)
    MEM_W(0XF0, ctx->r29) = ctx->r24;
    // 0x802C83AC: sw          $t7, 0xE8($sp)
    MEM_W(0XE8, ctx->r29) = ctx->r15;
    // 0x802C83B0: sw          $t6, 0xEC($sp)
    MEM_W(0XEC, ctx->r29) = ctx->r14;
    // 0x802C83B4: sw          $t9, 0x84($sp)
    MEM_W(0X84, ctx->r29) = ctx->r25;
    // 0x802C83B8: sw          $zero, 0x94($sp)
    MEM_W(0X94, ctx->r29) = 0;
    // 0x802C83BC: sw          $zero, 0x124($sp)
    MEM_W(0X124, ctx->r29) = 0;
    // 0x802C83C0: addiu       $fp, $zero, 0x58
    ctx->r30 = ADD32(0, 0X58);
    // 0x802C83C4: addiu       $s5, $sp, 0xBC
    ctx->r21 = ADD32(ctx->r29, 0XBC);
L_802C83C8:
    // 0x802C83C8: lw          $t1, 0x11C($sp)
    ctx->r9 = MEM_W(ctx->r29, 0X11C);
    // 0x802C83CC: lw          $t4, 0x94($sp)
    ctx->r12 = MEM_W(ctx->r29, 0X94);
    // 0x802C83D0: lui         $s7, 0x802D
    ctx->r23 = S32(0X802D << 16);
    // 0x802C83D4: bne         $t1, $zero, L_802C8404
    if (ctx->r9 != 0) {
        // 0x802C83D8: lw          $t5, 0x11C($sp)
        ctx->r13 = MEM_W(ctx->r29, 0X11C);
            goto L_802C8404;
    }
    // 0x802C83D8: lw          $t5, 0x11C($sp)
    ctx->r13 = MEM_W(ctx->r29, 0X11C);
    // 0x802C83DC: lw          $t2, 0x124($sp)
    ctx->r10 = MEM_W(ctx->r29, 0X124);
    // 0x802C83E0: lui         $s7, 0x802D
    ctx->r23 = S32(0X802D << 16);
    // 0x802C83E4: andi        $t3, $t2, 0x1
    ctx->r11 = ctx->r10 & 0X1;
    // 0x802C83E8: beq         $t3, $zero, L_802C83FC
    if (ctx->r11 == 0) {
        // 0x802C83EC: nop
    
            goto L_802C83FC;
    }
    // 0x802C83EC: nop

    // 0x802C83F0: lui         $s7, 0x802D
    ctx->r23 = S32(0X802D << 16);
    // 0x802C83F4: b           L_802C840C
    // 0x802C83F8: lw          $s7, -0x692C($s7)
    ctx->r23 = MEM_W(ctx->r23, -0X692C);
        goto L_802C840C;
    // 0x802C83F8: lw          $s7, -0x692C($s7)
    ctx->r23 = MEM_W(ctx->r23, -0X692C);
L_802C83FC:
    // 0x802C83FC: b           L_802C840C
    // 0x802C8400: lw          $s7, -0x6ADC($s7)
    ctx->r23 = MEM_W(ctx->r23, -0X6ADC);
        goto L_802C840C;
    // 0x802C8400: lw          $s7, -0x6ADC($s7)
    ctx->r23 = MEM_W(ctx->r23, -0X6ADC);
L_802C8404:
    // 0x802C8404: addu        $s7, $s7, $t4
    ctx->r23 = ADD32(ctx->r23, ctx->r12);
    // 0x802C8408: lw          $s7, -0x6ACC($s7)
    ctx->r23 = MEM_W(ctx->r23, -0X6ACC);
L_802C840C:
    // 0x802C840C: bne         $t5, $zero, L_802C8580
    if (ctx->r13 != 0) {
        // 0x802C8410: lw          $t3, 0x94($sp)
        ctx->r11 = MEM_W(ctx->r29, 0X94);
            goto L_802C8580;
    }
    // 0x802C8410: lw          $t3, 0x94($sp)
    ctx->r11 = MEM_W(ctx->r29, 0X94);
    // 0x802C8414: lw          $t8, 0x124($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X124);
    // 0x802C8418: lw          $t6, 0x94($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X94);
    // 0x802C841C: lui         $t7, 0x801D
    ctx->r15 = S32(0X801D << 16);
    // 0x802C8420: addiu       $t7, $t7, -0x18E8
    ctx->r15 = ADD32(ctx->r15, -0X18E8);
    // 0x802C8424: beq         $t8, $zero, L_802C848C
    if (ctx->r24 == 0) {
        // 0x802C8428: addu        $s0, $t6, $t7
        ctx->r16 = ADD32(ctx->r14, ctx->r15);
            goto L_802C848C;
    }
    // 0x802C8428: addu        $s0, $t6, $t7
    ctx->r16 = ADD32(ctx->r14, ctx->r15);
    // 0x802C842C: lw          $t9, 0xE8($sp)
    ctx->r25 = MEM_W(ctx->r29, 0XE8);
    // 0x802C8430: lui         $t2, 0x801D
    ctx->r10 = S32(0X801D << 16);
    // 0x802C8434: lw          $t2, -0x4CCC($t2)
    ctx->r10 = MEM_W(ctx->r10, -0X4CCC);
    // 0x802C8438: addiu       $t1, $t9, 0x1
    ctx->r9 = ADD32(ctx->r25, 0X1);
    // 0x802C843C: lw          $t9, -0x4($s0)
    ctx->r25 = MEM_W(ctx->r16, -0X4);
    // 0x802C8440: lw          $t5, 0x0($s0)
    ctx->r13 = MEM_W(ctx->r16, 0X0);
    // 0x802C8444: lui         $t4, 0x801D
    ctx->r12 = S32(0X801D << 16);
    // 0x802C8448: addiu       $t4, $t4, -0x4CB0
    ctx->r12 = ADD32(ctx->r12, -0X4CB0);
    // 0x802C844C: sll         $t3, $t2, 4
    ctx->r11 = S32(ctx->r10 << 4);
    // 0x802C8450: addu        $v0, $t3, $t4
    ctx->r2 = ADD32(ctx->r11, ctx->r12);
    // 0x802C8454: sll         $t2, $t9, 2
    ctx->r10 = S32(ctx->r25 << 2);
    // 0x802C8458: sll         $t6, $t5, 2
    ctx->r14 = S32(ctx->r13 << 2);
    // 0x802C845C: addu        $t7, $v0, $t6
    ctx->r15 = ADD32(ctx->r2, ctx->r14);
    // 0x802C8460: addu        $t3, $v0, $t2
    ctx->r11 = ADD32(ctx->r2, ctx->r10);
    // 0x802C8464: lw          $t4, 0x0($t3)
    ctx->r12 = MEM_W(ctx->r11, 0X0);
    // 0x802C8468: lw          $t8, 0x0($t7)
    ctx->r24 = MEM_W(ctx->r15, 0X0);
    // 0x802C846C: sw          $t1, 0xE8($sp)
    MEM_W(0XE8, ctx->r29) = ctx->r9;
    // 0x802C8470: lw          $t5, 0xEC($sp)
    ctx->r13 = MEM_W(ctx->r29, 0XEC);
    // 0x802C8474: beql        $t8, $t4, L_802C848C
    if (ctx->r24 == ctx->r12) {
        // 0x802C8478: sw          $t5, 0xF0($sp)
        MEM_W(0XF0, ctx->r29) = ctx->r13;
            goto L_802C848C;
    }
    goto skip_0;
    // 0x802C8478: sw          $t5, 0xF0($sp)
    MEM_W(0XF0, ctx->r29) = ctx->r13;
    skip_0:
    // 0x802C847C: sw          $t1, 0xEC($sp)
    MEM_W(0XEC, ctx->r29) = ctx->r9;
    // 0x802C8480: b           L_802C848C
    // 0x802C8484: sw          $t1, 0xF0($sp)
    MEM_W(0XF0, ctx->r29) = ctx->r9;
        goto L_802C848C;
    // 0x802C8484: sw          $t1, 0xF0($sp)
    MEM_W(0XF0, ctx->r29) = ctx->r9;
    // 0x802C8488: sw          $t5, 0xF0($sp)
    MEM_W(0XF0, ctx->r29) = ctx->r13;
L_802C848C:
    // 0x802C848C: lw          $t6, 0x0($s0)
    ctx->r14 = MEM_W(ctx->r16, 0X0);
    // 0x802C8490: lui         $t9, 0x801C
    ctx->r25 = S32(0X801C << 16);
    // 0x802C8494: lui         $a1, 0x802D
    ctx->r5 = S32(0X802D << 16);
    // 0x802C8498: sll         $t7, $t6, 3
    ctx->r15 = S32(ctx->r14 << 3);
    // 0x802C849C: subu        $t7, $t7, $t6
    ctx->r15 = SUB32(ctx->r15, ctx->r14);
    // 0x802C84A0: sll         $t7, $t7, 4
    ctx->r15 = S32(ctx->r15 << 4);
    // 0x802C84A4: subu        $t7, $t7, $t6
    ctx->r15 = SUB32(ctx->r15, ctx->r14);
    // 0x802C84A8: sll         $t7, $t7, 3
    ctx->r15 = S32(ctx->r15 << 3);
    // 0x802C84AC: addu        $t9, $t9, $t7
    ctx->r25 = ADD32(ctx->r25, ctx->r15);
    // 0x802C84B0: lw          $t9, 0x2C24($t9)
    ctx->r25 = MEM_W(ctx->r25, 0X2C24);
    // 0x802C84B4: addiu       $t2, $zero, 0x6
    ctx->r10 = ADD32(0, 0X6);
    // 0x802C84B8: addiu       $a1, $a1, -0x6A78
    ctx->r5 = ADD32(ctx->r5, -0X6A78);
    // 0x802C84BC: beq         $t9, $zero, L_802C84E8
    if (ctx->r25 == 0) {
        // 0x802C84C0: addiu       $a0, $sp, 0xC8
        ctx->r4 = ADD32(ctx->r29, 0XC8);
            goto L_802C84E8;
    }
    // 0x802C84C0: addiu       $a0, $sp, 0xC8
    ctx->r4 = ADD32(ctx->r29, 0XC8);
    // 0x802C84C4: lui         $a1, 0x802D
    ctx->r5 = S32(0X802D << 16);
    // 0x802C84C8: lui         $a2, 0x802D
    ctx->r6 = S32(0X802D << 16);
    // 0x802C84CC: sw          $t2, 0xF4($sp)
    MEM_W(0XF4, ctx->r29) = ctx->r10;
    // 0x802C84D0: addiu       $a2, $a2, -0x6A7C
    ctx->r6 = ADD32(ctx->r6, -0X6A7C);
    // 0x802C84D4: addiu       $a1, $a1, -0x6A80
    ctx->r5 = ADD32(ctx->r5, -0X6A80);
    // 0x802C84D8: jal         0x800CA210
    // 0x802C84DC: addiu       $a0, $sp, 0xC8
    ctx->r4 = ADD32(ctx->r29, 0XC8);
    func_800CA210(rdram, ctx);
        goto after_19;
    // 0x802C84DC: addiu       $a0, $sp, 0xC8
    ctx->r4 = ADD32(ctx->r29, 0XC8);
    after_19:
    // 0x802C84E0: b           L_802C84F4
    // 0x802C84E4: lw          $v0, 0x0($s0)
    ctx->r2 = MEM_W(ctx->r16, 0X0);
        goto L_802C84F4;
    // 0x802C84E4: lw          $v0, 0x0($s0)
    ctx->r2 = MEM_W(ctx->r16, 0X0);
L_802C84E8:
    // 0x802C84E8: jal         0x800CA210
    // 0x802C84EC: lw          $a2, 0xE8($sp)
    ctx->r6 = MEM_W(ctx->r29, 0XE8);
    func_800CA210(rdram, ctx);
        goto after_20;
    // 0x802C84EC: lw          $a2, 0xE8($sp)
    ctx->r6 = MEM_W(ctx->r29, 0XE8);
    after_20:
    // 0x802C84F0: lw          $v0, 0x0($s0)
    ctx->r2 = MEM_W(ctx->r16, 0X0);
L_802C84F4:
    // 0x802C84F4: lui         $t3, 0x800E
    ctx->r11 = S32(0X800E << 16);
    // 0x802C84F8: lui         $t5, 0x801D
    ctx->r13 = S32(0X801D << 16);
    // 0x802C84FC: sll         $v1, $v0, 2
    ctx->r3 = S32(ctx->r2 << 2);
    // 0x802C8500: addu        $t3, $t3, $v1
    ctx->r11 = ADD32(ctx->r11, ctx->r3);
    // 0x802C8504: lw          $t3, -0x5650($t3)
    ctx->r11 = MEM_W(ctx->r11, -0X5650);
    // 0x802C8508: lw          $t5, -0x4CCC($t5)
    ctx->r13 = MEM_W(ctx->r13, -0X4CCC);
    // 0x802C850C: lui         $t9, 0x800D
    ctx->r25 = S32(0X800D << 16);
    // 0x802C8510: sll         $t8, $t3, 3
    ctx->r24 = S32(ctx->r11 << 3);
    // 0x802C8514: lw          $t9, 0x48DC($t9)
    ctx->r25 = MEM_W(ctx->r25, 0X48DC);
    // 0x802C8518: lui         $t4, 0x801D
    ctx->r12 = S32(0X801D << 16);
    // 0x802C851C: subu        $t8, $t8, $t3
    ctx->r24 = SUB32(ctx->r24, ctx->r11);
    // 0x802C8520: sll         $t6, $t5, 4
    ctx->r14 = S32(ctx->r13 << 4);
    // 0x802C8524: sll         $t8, $t8, 1
    ctx->r24 = S32(ctx->r24 << 1);
    // 0x802C8528: addiu       $t4, $t4, -0x4D68
    ctx->r12 = ADD32(ctx->r12, -0X4D68);
    // 0x802C852C: addu        $t7, $t6, $v1
    ctx->r15 = ADD32(ctx->r14, ctx->r3);
    // 0x802C8530: lui         $a2, 0x801D
    ctx->r6 = S32(0X801D << 16);
    // 0x802C8534: addu        $t1, $t8, $t4
    ctx->r9 = ADD32(ctx->r24, ctx->r12);
    // 0x802C8538: addu        $a2, $a2, $t7
    ctx->r6 = ADD32(ctx->r6, ctx->r15);
    // 0x802C853C: sw          $t1, 0xD4($sp)
    MEM_W(0XD4, ctx->r29) = ctx->r9;
    // 0x802C8540: beq         $t9, $v0, L_802C8558
    if (ctx->r25 == ctx->r2) {
        // 0x802C8544: lw          $a2, -0x4CB0($a2)
        ctx->r6 = MEM_W(ctx->r6, -0X4CB0);
            goto L_802C8558;
    }
    // 0x802C8544: lw          $a2, -0x4CB0($a2)
    ctx->r6 = MEM_W(ctx->r6, -0X4CB0);
    // 0x802C8548: or          $s3, $zero, $zero
    ctx->r19 = 0 | 0;
    // 0x802C854C: or          $s2, $zero, $zero
    ctx->r18 = 0 | 0;
    // 0x802C8550: b           L_802C867C
    // 0x802C8554: or          $s4, $zero, $zero
    ctx->r20 = 0 | 0;
        goto L_802C867C;
    // 0x802C8554: or          $s4, $zero, $zero
    ctx->r20 = 0 | 0;
L_802C8558:
    // 0x802C8558: lui         $t2, 0x801C
    ctx->r10 = S32(0X801C << 16);
    // 0x802C855C: lw          $t2, 0x2650($t2)
    ctx->r10 = MEM_W(ctx->r10, 0X2650);
    // 0x802C8560: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x802C8564: addiu       $s3, $zero, 0x6
    ctx->r19 = ADD32(0, 0X6);
    // 0x802C8568: beq         $t2, $at, L_802C8578
    if (ctx->r10 == ctx->r1) {
        // 0x802C856C: addiu       $s4, $zero, 0x6
        ctx->r20 = ADD32(0, 0X6);
            goto L_802C8578;
    }
    // 0x802C856C: addiu       $s4, $zero, 0x6
    ctx->r20 = ADD32(0, 0X6);
    // 0x802C8570: b           L_802C867C
    // 0x802C8574: addiu       $s2, $zero, 0x6
    ctx->r18 = ADD32(0, 0X6);
        goto L_802C867C;
    // 0x802C8574: addiu       $s2, $zero, 0x6
    ctx->r18 = ADD32(0, 0X6);
L_802C8578:
    // 0x802C8578: b           L_802C867C
    // 0x802C857C: addiu       $s2, $zero, 0x4
    ctx->r18 = ADD32(0, 0X4);
        goto L_802C867C;
    // 0x802C857C: addiu       $s2, $zero, 0x4
    ctx->r18 = ADD32(0, 0X4);
L_802C8580:
    // 0x802C8580: lw          $t4, 0x124($sp)
    ctx->r12 = MEM_W(ctx->r29, 0X124);
    // 0x802C8584: lui         $t8, 0x800E
    ctx->r24 = S32(0X800E << 16);
    // 0x802C8588: addiu       $t8, $t8, -0x5624
    ctx->r24 = ADD32(ctx->r24, -0X5624);
    // 0x802C858C: beq         $t4, $zero, L_802C85E4
    if (ctx->r12 == 0) {
        // 0x802C8590: addu        $s3, $t3, $t8
        ctx->r19 = ADD32(ctx->r11, ctx->r24);
            goto L_802C85E4;
    }
    // 0x802C8590: addu        $s3, $t3, $t8
    ctx->r19 = ADD32(ctx->r11, ctx->r24);
    // 0x802C8594: lw          $t6, 0x0($s3)
    ctx->r14 = MEM_W(ctx->r19, 0X0);
    // 0x802C8598: lw          $t3, -0x4($s3)
    ctx->r11 = MEM_W(ctx->r19, -0X4);
    // 0x802C859C: lw          $t1, 0xE8($sp)
    ctx->r9 = MEM_W(ctx->r29, 0XE8);
    // 0x802C85A0: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x802C85A4: addiu       $v0, $v0, -0x4CC0
    ctx->r2 = ADD32(ctx->r2, -0X4CC0);
    // 0x802C85A8: sll         $t7, $t6, 2
    ctx->r15 = S32(ctx->r14 << 2);
    // 0x802C85AC: sll         $t8, $t3, 2
    ctx->r24 = S32(ctx->r11 << 2);
    // 0x802C85B0: addu        $t4, $v0, $t8
    ctx->r12 = ADD32(ctx->r2, ctx->r24);
    // 0x802C85B4: addu        $t9, $v0, $t7
    ctx->r25 = ADD32(ctx->r2, ctx->r15);
    // 0x802C85B8: addiu       $t5, $t1, 0x1
    ctx->r13 = ADD32(ctx->r9, 0X1);
    // 0x802C85BC: lw          $t1, 0x0($t4)
    ctx->r9 = MEM_W(ctx->r12, 0X0);
    // 0x802C85C0: lw          $t2, 0x0($t9)
    ctx->r10 = MEM_W(ctx->r25, 0X0);
    // 0x802C85C4: sw          $t5, 0xE8($sp)
    MEM_W(0XE8, ctx->r29) = ctx->r13;
    // 0x802C85C8: lw          $t6, 0xEC($sp)
    ctx->r14 = MEM_W(ctx->r29, 0XEC);
    // 0x802C85CC: beql        $t2, $t1, L_802C85E4
    if (ctx->r10 == ctx->r9) {
        // 0x802C85D0: sw          $t6, 0xF0($sp)
        MEM_W(0XF0, ctx->r29) = ctx->r14;
            goto L_802C85E4;
    }
    goto skip_1;
    // 0x802C85D0: sw          $t6, 0xF0($sp)
    MEM_W(0XF0, ctx->r29) = ctx->r14;
    skip_1:
    // 0x802C85D4: sw          $t5, 0xEC($sp)
    MEM_W(0XEC, ctx->r29) = ctx->r13;
    // 0x802C85D8: b           L_802C85E4
    // 0x802C85DC: sw          $t5, 0xF0($sp)
    MEM_W(0XF0, ctx->r29) = ctx->r13;
        goto L_802C85E4;
    // 0x802C85DC: sw          $t5, 0xF0($sp)
    MEM_W(0XF0, ctx->r29) = ctx->r13;
    // 0x802C85E0: sw          $t6, 0xF0($sp)
    MEM_W(0XF0, ctx->r29) = ctx->r14;
L_802C85E4:
    // 0x802C85E4: lui         $a1, 0x802D
    ctx->r5 = S32(0X802D << 16);
    // 0x802C85E8: addiu       $a1, $a1, -0x6A74
    ctx->r5 = ADD32(ctx->r5, -0X6A74);
    // 0x802C85EC: addiu       $a0, $sp, 0xC8
    ctx->r4 = ADD32(ctx->r29, 0XC8);
    // 0x802C85F0: jal         0x800CA210
    // 0x802C85F4: lw          $a2, 0xF0($sp)
    ctx->r6 = MEM_W(ctx->r29, 0XF0);
    func_800CA210(rdram, ctx);
        goto after_21;
    // 0x802C85F4: lw          $a2, 0xF0($sp)
    ctx->r6 = MEM_W(ctx->r29, 0XF0);
    after_21:
    // 0x802C85F8: lw          $a0, 0x0($s3)
    ctx->r4 = MEM_W(ctx->r19, 0X0);
    // 0x802C85FC: lui         $t7, 0x800E
    ctx->r15 = S32(0X800E << 16);
    // 0x802C8600: lui         $a1, 0x800D
    ctx->r5 = S32(0X800D << 16);
    // 0x802C8604: sll         $v1, $a0, 2
    ctx->r3 = S32(ctx->r4 << 2);
    // 0x802C8608: addu        $t7, $t7, $v1
    ctx->r15 = ADD32(ctx->r15, ctx->r3);
    // 0x802C860C: lw          $t7, -0x5650($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X5650);
    // 0x802C8610: lw          $a1, 0x48DC($a1)
    ctx->r5 = MEM_W(ctx->r5, 0X48DC);
    // 0x802C8614: lui         $t3, 0x801D
    ctx->r11 = S32(0X801D << 16);
    // 0x802C8618: sll         $t9, $t7, 3
    ctx->r25 = S32(ctx->r15 << 3);
    // 0x802C861C: subu        $t9, $t9, $t7
    ctx->r25 = SUB32(ctx->r25, ctx->r15);
    // 0x802C8620: sll         $t9, $t9, 1
    ctx->r25 = S32(ctx->r25 << 1);
    // 0x802C8624: addiu       $t3, $t3, -0x4D68
    ctx->r11 = ADD32(ctx->r11, -0X4D68);
    // 0x802C8628: lui         $a2, 0x801D
    ctx->r6 = S32(0X801D << 16);
    // 0x802C862C: addu        $t8, $t9, $t3
    ctx->r24 = ADD32(ctx->r25, ctx->r11);
    // 0x802C8630: addu        $a2, $a2, $v1
    ctx->r6 = ADD32(ctx->r6, ctx->r3);
    // 0x802C8634: sw          $t8, 0xD4($sp)
    MEM_W(0XD4, ctx->r29) = ctx->r24;
    // 0x802C8638: beq         $a1, $a0, L_802C864C
    if (ctx->r5 == ctx->r4) {
        // 0x802C863C: lw          $a2, -0x4CC0($a2)
        ctx->r6 = MEM_W(ctx->r6, -0X4CC0);
            goto L_802C864C;
    }
    // 0x802C863C: lw          $a2, -0x4CC0($a2)
    ctx->r6 = MEM_W(ctx->r6, -0X4CC0);
    // 0x802C8640: or          $s3, $zero, $zero
    ctx->r19 = 0 | 0;
    // 0x802C8644: b           L_802C866C
    // 0x802C8648: or          $s2, $zero, $zero
    ctx->r18 = 0 | 0;
        goto L_802C866C;
    // 0x802C8648: or          $s2, $zero, $zero
    ctx->r18 = 0 | 0;
L_802C864C:
    // 0x802C864C: lui         $t4, 0x801C
    ctx->r12 = S32(0X801C << 16);
    // 0x802C8650: lw          $t4, 0x2650($t4)
    ctx->r12 = MEM_W(ctx->r12, 0X2650);
    // 0x802C8654: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x802C8658: addiu       $s3, $zero, 0x6
    ctx->r19 = ADD32(0, 0X6);
    // 0x802C865C: beq         $t4, $at, L_802C866C
    if (ctx->r12 == ctx->r1) {
        // 0x802C8660: addiu       $s2, $zero, 0x7
        ctx->r18 = ADD32(0, 0X7);
            goto L_802C866C;
    }
    // 0x802C8660: addiu       $s2, $zero, 0x7
    ctx->r18 = ADD32(0, 0X7);
    // 0x802C8664: b           L_802C866C
    // 0x802C8668: addiu       $s2, $zero, 0x6
    ctx->r18 = ADD32(0, 0X6);
        goto L_802C866C;
    // 0x802C8668: addiu       $s2, $zero, 0x6
    ctx->r18 = ADD32(0, 0X6);
L_802C866C:
    // 0x802C866C: beq         $a1, $a0, L_802C867C
    if (ctx->r5 == ctx->r4) {
        // 0x802C8670: addiu       $s4, $zero, 0x6
        ctx->r20 = ADD32(0, 0X6);
            goto L_802C867C;
    }
    // 0x802C8670: addiu       $s4, $zero, 0x6
    ctx->r20 = ADD32(0, 0X6);
    // 0x802C8674: b           L_802C867C
    // 0x802C8678: or          $s4, $zero, $zero
    ctx->r20 = 0 | 0;
        goto L_802C867C;
    // 0x802C8678: or          $s4, $zero, $zero
    ctx->r20 = 0 | 0;
L_802C867C:
    // 0x802C867C: lui         $a1, 0x802D
    ctx->r5 = S32(0X802D << 16);
    // 0x802C8680: addiu       $a1, $a1, -0x6A70
    ctx->r5 = ADD32(ctx->r5, -0X6A70);
    // 0x802C8684: or          $a0, $s5, $zero
    ctx->r4 = ctx->r21 | 0;
    // 0x802C8688: jal         0x800CA210
    // 0x802C868C: sw          $a2, 0x104($sp)
    MEM_W(0X104, ctx->r29) = ctx->r6;
    func_800CA210(rdram, ctx);
        goto after_22;
    // 0x802C868C: sw          $a2, 0x104($sp)
    MEM_W(0X104, ctx->r29) = ctx->r6;
    after_22:
    // 0x802C8690: addiu       $a0, $zero, 0xA
    ctx->r4 = ADD32(0, 0XA);
    // 0x802C8694: lw          $a2, 0x104($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X104);
    // 0x802C8698: lw          $t6, 0xF4($sp)
    ctx->r14 = MEM_W(ctx->r29, 0XF4);
    // 0x802C869C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C86A0: div         $zero, $a2, $a0
    lo = S32(S64(S32(ctx->r6)) / S64(S32(ctx->r4))); hi = S32(S64(S32(ctx->r6)) % S64(S32(ctx->r4)));
    // 0x802C86A4: mflo        $t2
    ctx->r10 = lo;
    // 0x802C86A8: addu        $a3, $s7, $t6
    ctx->r7 = ADD32(ctx->r23, ctx->r14);
    // 0x802C86AC: bne         $a0, $zero, L_802C86B8
    if (ctx->r4 != 0) {
        // 0x802C86B0: nop
    
            goto L_802C86B8;
    }
    // 0x802C86B0: nop

    // 0x802C86B4: break       7
    do_break(2150401716);
L_802C86B8:
    // 0x802C86B8: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x802C86BC: bne         $a0, $at, L_802C86D0
    if (ctx->r4 != ctx->r1) {
        // 0x802C86C0: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_802C86D0;
    }
    // 0x802C86C0: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x802C86C4: bne         $a2, $at, L_802C86D0
    if (ctx->r6 != ctx->r1) {
        // 0x802C86C8: nop
    
            goto L_802C86D0;
    }
    // 0x802C86C8: nop

    // 0x802C86CC: break       6
    do_break(2150401740);
L_802C86D0:
    // 0x802C86D0: div         $zero, $t2, $a0
    lo = S32(S64(S32(ctx->r10)) / S64(S32(ctx->r4))); hi = S32(S64(S32(ctx->r10)) % S64(S32(ctx->r4)));
    // 0x802C86D4: mfhi        $v1
    ctx->r3 = hi;
    // 0x802C86D8: addiu       $a2, $sp, 0xC8
    ctx->r6 = ADD32(ctx->r29, 0XC8);
    // 0x802C86DC: bne         $a0, $zero, L_802C86E8
    if (ctx->r4 != 0) {
        // 0x802C86E0: nop
    
            goto L_802C86E8;
    }
    // 0x802C86E0: nop

    // 0x802C86E4: break       7
    do_break(2150401764);
L_802C86E8:
    // 0x802C86E8: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x802C86EC: bne         $a0, $at, L_802C8700
    if (ctx->r4 != ctx->r1) {
        // 0x802C86F0: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_802C8700;
    }
    // 0x802C86F0: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x802C86F4: bne         $t2, $at, L_802C8700
    if (ctx->r10 != ctx->r1) {
        // 0x802C86F8: nop
    
            goto L_802C8700;
    }
    // 0x802C86F8: nop

    // 0x802C86FC: break       6
    do_break(2150401788);
L_802C8700:
    // 0x802C8700: or          $a0, $s6, $zero
    ctx->r4 = ctx->r22 | 0;
    // 0x802C8704: beq         $v1, $zero, L_802C8724
    if (ctx->r3 == 0) {
        // 0x802C8708: addiu       $a3, $a3, 0xD
        ctx->r7 = ADD32(ctx->r7, 0XD);
            goto L_802C8724;
    }
    // 0x802C8708: addiu       $a3, $a3, 0xD
    ctx->r7 = ADD32(ctx->r7, 0XD);
    // 0x802C870C: lui         $t1, 0x8022
    ctx->r9 = S32(0X8022 << 16);
    // 0x802C8710: addu        $t1, $t1, $v1
    ctx->r9 = ADD32(ctx->r9, ctx->r3);
    // 0x802C8714: lbu         $t1, 0x6D70($t1)
    ctx->r9 = MEM_BU(ctx->r9, 0X6D70);
    // 0x802C8718: addiu       $t5, $zero, 0x14C
    ctx->r13 = ADD32(0, 0X14C);
    // 0x802C871C: b           L_802C8728
    // 0x802C8720: subu        $s1, $t5, $t1
    ctx->r17 = SUB32(ctx->r13, ctx->r9);
        goto L_802C8728;
    // 0x802C8720: subu        $s1, $t5, $t1
    ctx->r17 = SUB32(ctx->r13, ctx->r9);
L_802C8724:
    // 0x802C8724: addiu       $s1, $zero, 0x14C
    ctx->r17 = ADD32(0, 0X14C);
L_802C8728:
    // 0x802C8728: lw          $t7, 0x84($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X84);
    // 0x802C872C: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C8730: addiu       $t3, $zero, 0xFF
    ctx->r11 = ADD32(0, 0XFF);
    // 0x802C8734: sw          $t7, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r15;
    // 0x802C8738: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C873C: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C8740: addiu       $t4, $zero, 0xFF
    ctx->r12 = ADD32(0, 0XFF);
    // 0x802C8744: addiu       $t2, $zero, 0xFF
    ctx->r10 = ADD32(0, 0XFF);
    // 0x802C8748: addiu       $t5, $zero, 0xFF
    ctx->r13 = ADD32(0, 0XFF);
    // 0x802C874C: addiu       $t1, $zero, 0xFF
    ctx->r9 = ADD32(0, 0XFF);
    // 0x802C8750: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C8754: sw          $t6, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r14;
    // 0x802C8758: sw          $t1, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r9;
    // 0x802C875C: sw          $t5, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r13;
    // 0x802C8760: sw          $t2, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r10;
    // 0x802C8764: sw          $t4, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r12;
    // 0x802C8768: sw          $t8, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r24;
    // 0x802C876C: sw          $t8, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r24;
    // 0x802C8770: sw          $t7, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r15;
    // 0x802C8774: sw          $t3, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r11;
    // 0x802C8778: sw          $t3, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r11;
    // 0x802C877C: sw          $t9, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r25;
    // 0x802C8780: sw          $t9, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r25;
    // 0x802C8784: jal         0x801E92FC
    // 0x802C8788: sw          $s3, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r19;
    func_801E92FC(rdram, ctx);
        goto after_23;
    // 0x802C8788: sw          $s3, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r19;
    after_23:
    // 0x802C878C: lw          $t4, 0x84($sp)
    ctx->r12 = MEM_W(ctx->r29, 0X84);
    // 0x802C8790: addiu       $s0, $s7, 0x5C
    ctx->r16 = ADD32(ctx->r23, 0X5C);
    // 0x802C8794: addiu       $t2, $zero, 0xFF
    ctx->r10 = ADD32(0, 0XFF);
    // 0x802C8798: sw          $t4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r12;
    // 0x802C879C: addiu       $t4, $zero, 0xFF
    ctx->r12 = ADD32(0, 0XFF);
    // 0x802C87A0: addiu       $t5, $zero, 0xFF
    ctx->r13 = ADD32(0, 0XFF);
    // 0x802C87A4: addiu       $t1, $zero, 0xFF
    ctx->r9 = ADD32(0, 0XFF);
    // 0x802C87A8: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C87AC: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C87B0: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C87B4: addiu       $t3, $zero, 0xFF
    ctx->r11 = ADD32(0, 0XFF);
    // 0x802C87B8: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C87BC: sw          $t8, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r24;
    // 0x802C87C0: sw          $t3, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r11;
    // 0x802C87C4: sw          $t9, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r25;
    // 0x802C87C8: sw          $t7, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r15;
    // 0x802C87CC: sw          $t6, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r14;
    // 0x802C87D0: sw          $t1, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r9;
    // 0x802C87D4: sw          $t1, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r9;
    // 0x802C87D8: sw          $t5, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r13;
    // 0x802C87DC: sw          $t5, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r13;
    // 0x802C87E0: sw          $t4, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r12;
    // 0x802C87E4: sw          $t2, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r10;
    // 0x802C87E8: sw          $t2, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r10;
    // 0x802C87EC: or          $a3, $s0, $zero
    ctx->r7 = ctx->r16 | 0;
    // 0x802C87F0: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C87F4: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C87F8: lw          $a2, 0xD4($sp)
    ctx->r6 = MEM_W(ctx->r29, 0XD4);
    // 0x802C87FC: jal         0x801E92FC
    // 0x802C8800: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    func_801E92FC(rdram, ctx);
        goto after_24;
    // 0x802C8800: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    after_24:
    // 0x802C8804: lw          $t6, 0x84($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X84);
    // 0x802C8808: addu        $a3, $s7, $s1
    ctx->r7 = ADD32(ctx->r23, ctx->r17);
    // 0x802C880C: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C8810: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x802C8814: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C8818: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C881C: addiu       $t3, $zero, 0xFF
    ctx->r11 = ADD32(0, 0XFF);
    // 0x802C8820: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C8824: addiu       $t4, $zero, 0xFF
    ctx->r12 = ADD32(0, 0XFF);
    // 0x802C8828: addiu       $t2, $zero, 0xFF
    ctx->r10 = ADD32(0, 0XFF);
    // 0x802C882C: addiu       $t5, $zero, 0xFF
    ctx->r13 = ADD32(0, 0XFF);
    // 0x802C8830: addiu       $t1, $zero, 0xFF
    ctx->r9 = ADD32(0, 0XFF);
    // 0x802C8834: sw          $t1, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r9;
    // 0x802C8838: sw          $t5, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r13;
    // 0x802C883C: sw          $t2, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r10;
    // 0x802C8840: sw          $t4, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r12;
    // 0x802C8844: sw          $t8, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r24;
    // 0x802C8848: sw          $t3, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r11;
    // 0x802C884C: sw          $t3, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r11;
    // 0x802C8850: sw          $t9, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r25;
    // 0x802C8854: sw          $t9, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r25;
    // 0x802C8858: sw          $t6, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r14;
    // 0x802C885C: sw          $t7, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r15;
    // 0x802C8860: sw          $t7, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r15;
    // 0x802C8864: addiu       $a3, $a3, 0x8
    ctx->r7 = ADD32(ctx->r7, 0X8);
    // 0x802C8868: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C886C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C8870: or          $a2, $s5, $zero
    ctx->r6 = ctx->r21 | 0;
    // 0x802C8874: jal         0x801E92FC
    // 0x802C8878: sw          $s4, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r20;
    func_801E92FC(rdram, ctx);
        goto after_25;
    // 0x802C8878: sw          $s4, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r20;
    after_25:
    // 0x802C887C: lw          $t8, 0x11C($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X11C);
    // 0x802C8880: or          $s6, $v0, $zero
    ctx->r22 = ctx->r2 | 0;
    // 0x802C8884: or          $a0, $s6, $zero
    ctx->r4 = ctx->r22 | 0;
    // 0x802C8888: bne         $t8, $zero, L_802C89C4
    if (ctx->r24 != 0) {
        // 0x802C888C: or          $a1, $s4, $zero
        ctx->r5 = ctx->r20 | 0;
            goto L_802C89C4;
    }
    // 0x802C888C: or          $a1, $s4, $zero
    ctx->r5 = ctx->r20 | 0;
    // 0x802C8890: lw          $t4, 0x94($sp)
    ctx->r12 = MEM_W(ctx->r29, 0X94);
    // 0x802C8894: lui         $t2, 0x801D
    ctx->r10 = S32(0X801D << 16);
    // 0x802C8898: lui         $t1, 0x801C
    ctx->r9 = S32(0X801C << 16);
    // 0x802C889C: addu        $t2, $t2, $t4
    ctx->r10 = ADD32(ctx->r10, ctx->r12);
    // 0x802C88A0: lw          $t2, -0x18E8($t2)
    ctx->r10 = MEM_W(ctx->r10, -0X18E8);
    // 0x802C88A4: addiu       $t1, $t1, 0x2938
    ctx->r9 = ADD32(ctx->r9, 0X2938);
    // 0x802C88A8: or          $a0, $s6, $zero
    ctx->r4 = ctx->r22 | 0;
    // 0x802C88AC: sll         $t5, $t2, 3
    ctx->r13 = S32(ctx->r10 << 3);
    // 0x802C88B0: subu        $t5, $t5, $t2
    ctx->r13 = SUB32(ctx->r13, ctx->r10);
    // 0x802C88B4: sll         $t5, $t5, 4
    ctx->r13 = S32(ctx->r13 << 4);
    // 0x802C88B8: subu        $t5, $t5, $t2
    ctx->r13 = SUB32(ctx->r13, ctx->r10);
    // 0x802C88BC: sll         $t5, $t5, 3
    ctx->r13 = S32(ctx->r13 << 3);
    // 0x802C88C0: addu        $v0, $t5, $t1
    ctx->r2 = ADD32(ctx->r13, ctx->r9);
    // 0x802C88C4: lw          $t6, 0x2EC($v0)
    ctx->r14 = MEM_W(ctx->r2, 0X2EC);
    // 0x802C88C8: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C88CC: or          $a3, $s0, $zero
    ctx->r7 = ctx->r16 | 0;
    // 0x802C88D0: beq         $t6, $zero, L_802C895C
    if (ctx->r14 == 0) {
        // 0x802C88D4: addiu       $t9, $zero, 0xFF
        ctx->r25 = ADD32(0, 0XFF);
            goto L_802C895C;
    }
    // 0x802C88D4: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C88D8: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C88DC: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C88E0: addiu       $t3, $zero, 0xFF
    ctx->r11 = ADD32(0, 0XFF);
    // 0x802C88E4: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C88E8: addiu       $t4, $zero, 0xFF
    ctx->r12 = ADD32(0, 0XFF);
    // 0x802C88EC: addiu       $t2, $zero, 0xFF
    ctx->r10 = ADD32(0, 0XFF);
    // 0x802C88F0: addiu       $t5, $zero, 0xFF
    ctx->r13 = ADD32(0, 0XFF);
    // 0x802C88F4: addiu       $t1, $zero, 0xFF
    ctx->r9 = ADD32(0, 0XFF);
    // 0x802C88F8: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C88FC: sw          $t6, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r14;
    // 0x802C8900: sw          $t1, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r9;
    // 0x802C8904: sw          $t5, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r13;
    // 0x802C8908: sw          $t2, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r10;
    // 0x802C890C: sw          $t4, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r12;
    // 0x802C8910: sw          $t8, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r24;
    // 0x802C8914: sw          $t3, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r11;
    // 0x802C8918: sw          $t9, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r25;
    // 0x802C891C: sw          $t7, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r15;
    // 0x802C8920: sw          $t7, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r15;
    // 0x802C8924: or          $a0, $s6, $zero
    ctx->r4 = ctx->r22 | 0;
    // 0x802C8928: or          $a1, $s3, $zero
    ctx->r5 = ctx->r19 | 0;
    // 0x802C892C: addiu       $a2, $zero, 0xFF
    ctx->r6 = ADD32(0, 0XFF);
    // 0x802C8930: jal         0x801E946C
    // 0x802C8934: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    func_801E946C(rdram, ctx);
        goto after_26;
    // 0x802C8934: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    after_26:
    // 0x802C8938: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C893C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C8940: addiu       $a2, $zero, 0x1B
    ctx->r6 = ADD32(0, 0X1B);
    // 0x802C8944: or          $a3, $s0, $zero
    ctx->r7 = ctx->r16 | 0;
    // 0x802C8948: sw          $fp, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r30;
    // 0x802C894C: jal         0x801E3EE0
    // 0x802C8950: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    func_801E3EE0(rdram, ctx);
        goto after_27;
    // 0x802C8950: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    after_27:
    // 0x802C8954: b           L_802C8B6C
    // 0x802C8958: or          $s6, $v0, $zero
    ctx->r22 = ctx->r2 | 0;
        goto L_802C8B6C;
    // 0x802C8958: or          $s6, $v0, $zero
    ctx->r22 = ctx->r2 | 0;
L_802C895C:
    // 0x802C895C: addiu       $t3, $zero, 0xFF
    ctx->r11 = ADD32(0, 0XFF);
    // 0x802C8960: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C8964: addiu       $t4, $zero, 0xFF
    ctx->r12 = ADD32(0, 0XFF);
    // 0x802C8968: addiu       $t2, $zero, 0xFF
    ctx->r10 = ADD32(0, 0XFF);
    // 0x802C896C: addiu       $t5, $zero, 0xFF
    ctx->r13 = ADD32(0, 0XFF);
    // 0x802C8970: addiu       $t1, $zero, 0xFF
    ctx->r9 = ADD32(0, 0XFF);
    // 0x802C8974: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C8978: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C897C: sw          $t7, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r15;
    // 0x802C8980: sw          $t6, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r14;
    // 0x802C8984: sw          $t1, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r9;
    // 0x802C8988: sw          $t5, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r13;
    // 0x802C898C: sw          $t2, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r10;
    // 0x802C8990: sw          $t4, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r12;
    // 0x802C8994: sw          $t8, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r24;
    // 0x802C8998: sw          $t3, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r11;
    // 0x802C899C: lw          $a2, 0x19C($v0)
    ctx->r6 = MEM_W(ctx->r2, 0X19C);
    // 0x802C89A0: sw          $fp, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r30;
    // 0x802C89A4: sw          $s2, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r18;
    // 0x802C89A8: sw          $t9, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r25;
    // 0x802C89AC: sw          $zero, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = 0;
    // 0x802C89B0: sw          $zero, 0x20($sp)
    MEM_W(0X20, ctx->r29) = 0;
    // 0x802C89B4: jal         0x801E8A84
    // 0x802C89B8: sw          $t9, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r25;
    func_801E8A84(rdram, ctx);
        goto after_28;
    // 0x802C89B8: sw          $t9, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r25;
    after_28:
    // 0x802C89BC: b           L_802C8B6C
    // 0x802C89C0: or          $s6, $v0, $zero
    ctx->r22 = ctx->r2 | 0;
        goto L_802C8B6C;
    // 0x802C89C0: or          $s6, $v0, $zero
    ctx->r22 = ctx->r2 | 0;
L_802C89C4:
    // 0x802C89C4: addiu       $t3, $zero, 0xFF
    ctx->r11 = ADD32(0, 0XFF);
    // 0x802C89C8: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C89CC: addiu       $t4, $zero, 0xFF
    ctx->r12 = ADD32(0, 0XFF);
    // 0x802C89D0: addiu       $t2, $zero, 0xFF
    ctx->r10 = ADD32(0, 0XFF);
    // 0x802C89D4: addiu       $t5, $zero, 0xFF
    ctx->r13 = ADD32(0, 0XFF);
    // 0x802C89D8: addiu       $t1, $zero, 0xFF
    ctx->r9 = ADD32(0, 0XFF);
    // 0x802C89DC: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C89E0: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C89E4: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C89E8: sw          $t9, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r25;
    // 0x802C89EC: sw          $t7, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r15;
    // 0x802C89F0: sw          $t6, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r14;
    // 0x802C89F4: sw          $t1, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r9;
    // 0x802C89F8: sw          $t5, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r13;
    // 0x802C89FC: sw          $t2, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r10;
    // 0x802C8A00: sw          $t4, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r12;
    // 0x802C8A04: sw          $t8, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r24;
    // 0x802C8A08: sw          $t3, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r11;
    // 0x802C8A0C: sw          $t3, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r11;
    // 0x802C8A10: addiu       $a2, $zero, 0xFF
    ctx->r6 = ADD32(0, 0XFF);
    // 0x802C8A14: jal         0x801E946C
    // 0x802C8A18: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    func_801E946C(rdram, ctx);
        goto after_29;
    // 0x802C8A18: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    after_29:
    // 0x802C8A1C: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C8A20: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C8A24: addiu       $a2, $zero, 0x18
    ctx->r6 = ADD32(0, 0X18);
    // 0x802C8A28: or          $a3, $s0, $zero
    ctx->r7 = ctx->r16 | 0;
    // 0x802C8A2C: sw          $fp, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r30;
    // 0x802C8A30: jal         0x801E3EE0
    // 0x802C8A34: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    func_801E3EE0(rdram, ctx);
        goto after_30;
    // 0x802C8A34: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    after_30:
    // 0x802C8A38: lui         $t8, 0x801D
    ctx->r24 = S32(0X801D << 16);
    // 0x802C8A3C: lw          $t8, -0x4CC8($t8)
    ctx->r24 = MEM_W(ctx->r24, -0X4CC8);
    // 0x802C8A40: or          $s6, $v0, $zero
    ctx->r22 = ctx->r2 | 0;
    // 0x802C8A44: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    // 0x802C8A48: bne         $t8, $zero, L_802C8A58
    if (ctx->r24 != 0) {
        // 0x802C8A4C: lui         $v1, 0x801D
        ctx->r3 = S32(0X801D << 16);
            goto L_802C8A58;
    }
    // 0x802C8A4C: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x802C8A50: b           L_802C8A58
    // 0x802C8A54: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
        goto L_802C8A58;
    // 0x802C8A54: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
L_802C8A58:
    // 0x802C8A58: lw          $v1, -0x4CCC($v1)
    ctx->r3 = MEM_W(ctx->r3, -0X4CCC);
    // 0x802C8A5C: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
    // 0x802C8A60: lw          $t4, 0x94($sp)
    ctx->r12 = MEM_W(ctx->r29, 0X94);
    // 0x802C8A64: slt         $at, $v1, $v0
    ctx->r1 = SIGNED(ctx->r3) < SIGNED(ctx->r2) ? 1 : 0;
    // 0x802C8A68: bne         $at, $zero, L_802C8B6C
    if (ctx->r1 != 0) {
        // 0x802C8A6C: lui         $t2, 0x800E
        ctx->r10 = S32(0X800E << 16);
            goto L_802C8B6C;
    }
    // 0x802C8A6C: lui         $t2, 0x800E
    ctx->r10 = S32(0X800E << 16);
    // 0x802C8A70: subu        $t6, $v0, $v0
    ctx->r14 = SUB32(ctx->r2, ctx->r2);
    // 0x802C8A74: sll         $t7, $t6, 2
    ctx->r15 = S32(ctx->r14 << 2);
    // 0x802C8A78: subu        $t7, $t7, $t6
    ctx->r15 = SUB32(ctx->r15, ctx->r14);
    // 0x802C8A7C: sll         $t7, $t7, 2
    ctx->r15 = S32(ctx->r15 << 2);
    // 0x802C8A80: lui         $t1, 0x801D
    ctx->r9 = S32(0X801D << 16);
    // 0x802C8A84: addiu       $t1, $t1, -0x4CB0
    ctx->r9 = ADD32(ctx->r9, -0X4CB0);
    // 0x802C8A88: addu        $s2, $s7, $t7
    ctx->r18 = ADD32(ctx->r23, ctx->r15);
    // 0x802C8A8C: addiu       $t2, $t2, -0x5624
    ctx->r10 = ADD32(ctx->r10, -0X5624);
    // 0x802C8A90: sll         $t5, $v0, 4
    ctx->r13 = S32(ctx->r2 << 4);
    // 0x802C8A94: addu        $s1, $t5, $t1
    ctx->r17 = ADD32(ctx->r13, ctx->r9);
    // 0x802C8A98: addu        $s3, $t4, $t2
    ctx->r19 = ADD32(ctx->r12, ctx->r10);
    // 0x802C8A9C: addiu       $s2, $s2, 0x84
    ctx->r18 = ADD32(ctx->r18, 0X84);
L_802C8AA0:
    // 0x802C8AA0: lw          $t9, 0x0($s3)
    ctx->r25 = MEM_W(ctx->r19, 0X0);
    // 0x802C8AA4: or          $a0, $s5, $zero
    ctx->r4 = ctx->r21 | 0;
    // 0x802C8AA8: lui         $a1, 0x802D
    ctx->r5 = S32(0X802D << 16);
    // 0x802C8AAC: sll         $t3, $t9, 2
    ctx->r11 = S32(ctx->r25 << 2);
    // 0x802C8AB0: addu        $t8, $s1, $t3
    ctx->r24 = ADD32(ctx->r17, ctx->r11);
    // 0x802C8AB4: beq         $s0, $v1, L_802C8AD4
    if (ctx->r16 == ctx->r3) {
        // 0x802C8AB8: lw          $a2, 0x0($t8)
        ctx->r6 = MEM_W(ctx->r24, 0X0);
            goto L_802C8AD4;
    }
    // 0x802C8AB8: lw          $a2, 0x0($t8)
    ctx->r6 = MEM_W(ctx->r24, 0X0);
    // 0x802C8ABC: lui         $a1, 0x802D
    ctx->r5 = S32(0X802D << 16);
    // 0x802C8AC0: addiu       $a1, $a1, -0x6A6C
    ctx->r5 = ADD32(ctx->r5, -0X6A6C);
    // 0x802C8AC4: jal         0x800CA210
    // 0x802C8AC8: or          $a0, $s5, $zero
    ctx->r4 = ctx->r21 | 0;
    func_800CA210(rdram, ctx);
        goto after_31;
    // 0x802C8AC8: or          $a0, $s5, $zero
    ctx->r4 = ctx->r21 | 0;
    after_31:
    // 0x802C8ACC: b           L_802C8AE0
    // 0x802C8AD0: addiu       $t4, $zero, 0xFF
    ctx->r12 = ADD32(0, 0XFF);
        goto L_802C8AE0;
    // 0x802C8AD0: addiu       $t4, $zero, 0xFF
    ctx->r12 = ADD32(0, 0XFF);
L_802C8AD4:
    // 0x802C8AD4: jal         0x800CA210
    // 0x802C8AD8: addiu       $a1, $a1, -0x6A68
    ctx->r5 = ADD32(ctx->r5, -0X6A68);
    func_800CA210(rdram, ctx);
        goto after_32;
    // 0x802C8AD8: addiu       $a1, $a1, -0x6A68
    ctx->r5 = ADD32(ctx->r5, -0X6A68);
    after_32:
    // 0x802C8ADC: addiu       $t4, $zero, 0xFF
    ctx->r12 = ADD32(0, 0XFF);
L_802C8AE0:
    // 0x802C8AE0: addiu       $t2, $zero, 0xFF
    ctx->r10 = ADD32(0, 0XFF);
    // 0x802C8AE4: addiu       $t5, $zero, 0xFF
    ctx->r13 = ADD32(0, 0XFF);
    // 0x802C8AE8: addiu       $t1, $zero, 0xFF
    ctx->r9 = ADD32(0, 0XFF);
    // 0x802C8AEC: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C8AF0: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C8AF4: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C8AF8: addiu       $t3, $zero, 0xFF
    ctx->r11 = ADD32(0, 0XFF);
    // 0x802C8AFC: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C8B00: sw          $t8, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r24;
    // 0x802C8B04: sw          $t3, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r11;
    // 0x802C8B08: sw          $t9, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r25;
    // 0x802C8B0C: sw          $t7, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r15;
    // 0x802C8B10: sw          $t6, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r14;
    // 0x802C8B14: sw          $t1, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r9;
    // 0x802C8B18: sw          $t5, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r13;
    // 0x802C8B1C: sw          $t5, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r13;
    // 0x802C8B20: sw          $t2, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r10;
    // 0x802C8B24: sw          $t2, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r10;
    // 0x802C8B28: sw          $t4, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r12;
    // 0x802C8B2C: sw          $t4, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r12;
    // 0x802C8B30: or          $a0, $s6, $zero
    ctx->r4 = ctx->r22 | 0;
    // 0x802C8B34: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C8B38: or          $a2, $s5, $zero
    ctx->r6 = ctx->r21 | 0;
    // 0x802C8B3C: or          $a3, $s2, $zero
    ctx->r7 = ctx->r18 | 0;
    // 0x802C8B40: sw          $fp, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r30;
    // 0x802C8B44: jal         0x801E92FC
    // 0x802C8B48: sw          $s4, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r20;
    func_801E92FC(rdram, ctx);
        goto after_33;
    // 0x802C8B48: sw          $s4, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r20;
    after_33:
    // 0x802C8B4C: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x802C8B50: lw          $v1, -0x4CCC($v1)
    ctx->r3 = MEM_W(ctx->r3, -0X4CCC);
    // 0x802C8B54: addiu       $s0, $s0, 0x1
    ctx->r16 = ADD32(ctx->r16, 0X1);
    // 0x802C8B58: addiu       $s1, $s1, 0x10
    ctx->r17 = ADD32(ctx->r17, 0X10);
    // 0x802C8B5C: slt         $at, $v1, $s0
    ctx->r1 = SIGNED(ctx->r3) < SIGNED(ctx->r16) ? 1 : 0;
    // 0x802C8B60: addiu       $s2, $s2, 0xC
    ctx->r18 = ADD32(ctx->r18, 0XC);
    // 0x802C8B64: beq         $at, $zero, L_802C8AA0
    if (ctx->r1 == 0) {
        // 0x802C8B68: or          $s6, $v0, $zero
        ctx->r22 = ctx->r2 | 0;
            goto L_802C8AA0;
    }
    // 0x802C8B68: or          $s6, $v0, $zero
    ctx->r22 = ctx->r2 | 0;
L_802C8B6C:
    // 0x802C8B6C: lw          $t1, 0x124($sp)
    ctx->r9 = MEM_W(ctx->r29, 0X124);
    // 0x802C8B70: lw          $t7, 0x94($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X94);
    // 0x802C8B74: lw          $t3, 0x84($sp)
    ctx->r11 = MEM_W(ctx->r29, 0X84);
    // 0x802C8B78: addiu       $t6, $t1, 0x1
    ctx->r14 = ADD32(ctx->r9, 0X1);
    // 0x802C8B7C: slti        $at, $t6, 0x4
    ctx->r1 = SIGNED(ctx->r14) < 0X4 ? 1 : 0;
    // 0x802C8B80: addiu       $t9, $t7, 0x4
    ctx->r25 = ADD32(ctx->r15, 0X4);
    // 0x802C8B84: addiu       $t8, $t3, 0x20
    ctx->r24 = ADD32(ctx->r11, 0X20);
    // 0x802C8B88: sw          $t8, 0x84($sp)
    MEM_W(0X84, ctx->r29) = ctx->r24;
    // 0x802C8B8C: sw          $t9, 0x94($sp)
    MEM_W(0X94, ctx->r29) = ctx->r25;
    // 0x802C8B90: sw          $t6, 0x124($sp)
    MEM_W(0X124, ctx->r29) = ctx->r14;
    // 0x802C8B94: bne         $at, $zero, L_802C83C8
    if (ctx->r1 != 0) {
        // 0x802C8B98: addiu       $fp, $fp, 0x20
        ctx->r30 = ADD32(ctx->r30, 0X20);
            goto L_802C83C8;
    }
    // 0x802C8B98: addiu       $fp, $fp, 0x20
    ctx->r30 = ADD32(ctx->r30, 0X20);
    // 0x802C8B9C: lw          $t4, 0x11C($sp)
    ctx->r12 = MEM_W(ctx->r29, 0X11C);
    // 0x802C8BA0: lui         $t9, 0x802D
    ctx->r25 = S32(0X802D << 16);
    // 0x802C8BA4: or          $a0, $s6, $zero
    ctx->r4 = ctx->r22 | 0;
    // 0x802C8BA8: bne         $t4, $zero, L_802C8C54
    if (ctx->r12 != 0) {
        // 0x802C8BAC: lui         $a2, 0x802D
        ctx->r6 = S32(0X802D << 16);
            goto L_802C8C54;
    }
    // 0x802C8BAC: lui         $a2, 0x802D
    ctx->r6 = S32(0X802D << 16);
    // 0x802C8BB0: addiu       $t2, $zero, 0xFF
    ctx->r10 = ADD32(0, 0XFF);
    // 0x802C8BB4: addiu       $t5, $zero, 0xFF
    ctx->r13 = ADD32(0, 0XFF);
    // 0x802C8BB8: addiu       $t1, $zero, 0xFF
    ctx->r9 = ADD32(0, 0XFF);
    // 0x802C8BBC: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C8BC0: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C8BC4: addiu       $t3, $zero, 0xFF
    ctx->r11 = ADD32(0, 0XFF);
    // 0x802C8BC8: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C8BCC: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C8BD0: addiu       $t4, $zero, 0xFF
    ctx->r12 = ADD32(0, 0XFF);
    // 0x802C8BD4: sw          $t4, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r12;
    // 0x802C8BD8: sw          $t6, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r14;
    // 0x802C8BDC: sw          $t8, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r24;
    // 0x802C8BE0: sw          $t3, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r11;
    // 0x802C8BE4: sw          $t9, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r25;
    // 0x802C8BE8: sw          $t7, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r15;
    // 0x802C8BEC: sw          $t1, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r9;
    // 0x802C8BF0: sw          $t5, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r13;
    // 0x802C8BF4: sw          $t2, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r10;
    // 0x802C8BF8: sw          $t2, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r10;
    // 0x802C8BFC: or          $a0, $s6, $zero
    ctx->r4 = ctx->r22 | 0;
    // 0x802C8C00: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C8C04: addiu       $a2, $zero, 0xFF
    ctx->r6 = ADD32(0, 0XFF);
    // 0x802C8C08: jal         0x801E946C
    // 0x802C8C0C: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    func_801E946C(rdram, ctx);
        goto after_34;
    // 0x802C8C0C: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    after_34:
    // 0x802C8C10: lui         $t5, 0x801D
    ctx->r13 = S32(0X801D << 16);
    // 0x802C8C14: lw          $t5, -0x18FC($t5)
    ctx->r13 = MEM_W(ctx->r13, -0X18FC);
    // 0x802C8C18: lui         $a3, 0x802D
    ctx->r7 = S32(0X802D << 16);
    // 0x802C8C1C: lw          $a3, -0x6ADC($a3)
    ctx->r7 = MEM_W(ctx->r7, -0X6ADC);
    // 0x802C8C20: lui         $a2, 0x802D
    ctx->r6 = S32(0X802D << 16);
    // 0x802C8C24: sll         $t1, $t5, 2
    ctx->r9 = S32(ctx->r13 << 2);
    // 0x802C8C28: addu        $a2, $a2, $t1
    ctx->r6 = ADD32(ctx->r6, ctx->r9);
    // 0x802C8C2C: addiu       $t7, $zero, 0xCA
    ctx->r15 = ADD32(0, 0XCA);
    // 0x802C8C30: sw          $t7, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r15;
    // 0x802C8C34: lw          $a2, -0x6ABC($a2)
    ctx->r6 = MEM_W(ctx->r6, -0X6ABC);
    // 0x802C8C38: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C8C3C: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C8C40: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    // 0x802C8C44: jal         0x801E3EE0
    // 0x802C8C48: addiu       $a3, $a3, 0x108
    ctx->r7 = ADD32(ctx->r7, 0X108);
    func_801E3EE0(rdram, ctx);
        goto after_35;
    // 0x802C8C48: addiu       $a3, $a3, 0x108
    ctx->r7 = ADD32(ctx->r7, 0X108);
    after_35:
    // 0x802C8C4C: b           L_802C8D08
    // 0x802C8C50: lui         $t7, 0xB400
    ctx->r15 = S32(0XB400 << 16);
        goto L_802C8D08;
    // 0x802C8C50: lui         $t7, 0xB400
    ctx->r15 = S32(0XB400 << 16);
L_802C8C54:
    // 0x802C8C54: lw          $t9, -0x6AA8($t9)
    ctx->r25 = MEM_W(ctx->r25, -0X6AA8);
    // 0x802C8C58: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    // 0x802C8C5C: addiu       $t3, $zero, 0xFF
    ctx->r11 = ADD32(0, 0XFF);
    // 0x802C8C60: bne         $t9, $zero, L_802C8C70
    if (ctx->r25 != 0) {
        // 0x802C8C64: addiu       $t8, $zero, 0xFF
        ctx->r24 = ADD32(0, 0XFF);
            goto L_802C8C70;
    }
    // 0x802C8C64: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C8C68: b           L_802C8C74
    // 0x802C8C6C: addiu       $s3, $zero, 0xA
    ctx->r19 = ADD32(0, 0XA);
        goto L_802C8C74;
    // 0x802C8C6C: addiu       $s3, $zero, 0xA
    ctx->r19 = ADD32(0, 0XA);
L_802C8C70:
    // 0x802C8C70: addiu       $s3, $zero, 0x6
    ctx->r19 = ADD32(0, 0X6);
L_802C8C74:
    // 0x802C8C74: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C8C78: addiu       $t4, $zero, 0xFF
    ctx->r12 = ADD32(0, 0XFF);
    // 0x802C8C7C: addiu       $t2, $zero, 0xFF
    ctx->r10 = ADD32(0, 0XFF);
    // 0x802C8C80: addiu       $t5, $zero, 0xFF
    ctx->r13 = ADD32(0, 0XFF);
    // 0x802C8C84: addiu       $t1, $zero, 0xFF
    ctx->r9 = ADD32(0, 0XFF);
    // 0x802C8C88: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C8C8C: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C8C90: sw          $t9, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r25;
    // 0x802C8C94: sw          $t7, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r15;
    // 0x802C8C98: sw          $t1, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r9;
    // 0x802C8C9C: sw          $t5, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r13;
    // 0x802C8CA0: sw          $t2, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r10;
    // 0x802C8CA4: sw          $t4, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r12;
    // 0x802C8CA8: sw          $t6, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r14;
    // 0x802C8CAC: or          $a1, $s3, $zero
    ctx->r5 = ctx->r19 | 0;
    // 0x802C8CB0: lbu         $a2, -0x6AD5($a2)
    ctx->r6 = MEM_BU(ctx->r6, -0X6AD5);
    // 0x802C8CB4: sw          $t3, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r11;
    // 0x802C8CB8: sw          $t8, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r24;
    // 0x802C8CBC: jal         0x801E946C
    // 0x802C8CC0: sw          $t3, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r11;
    func_801E946C(rdram, ctx);
        goto after_36;
    // 0x802C8CC0: sw          $t3, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r11;
    after_36:
    // 0x802C8CC4: lui         $t8, 0x801D
    ctx->r24 = S32(0X801D << 16);
    // 0x802C8CC8: lui         $t4, 0x801D
    ctx->r12 = S32(0X801D << 16);
    // 0x802C8CCC: lw          $t4, -0x4CCC($t4)
    ctx->r12 = MEM_W(ctx->r12, -0X4CCC);
    // 0x802C8CD0: lw          $t8, -0x4CC8($t8)
    ctx->r24 = MEM_W(ctx->r24, -0X4CC8);
    // 0x802C8CD4: lui         $a2, 0x800F
    ctx->r6 = S32(0X800F << 16);
    // 0x802C8CD8: sll         $t2, $t4, 1
    ctx->r10 = S32(ctx->r12 << 1);
    // 0x802C8CDC: sll         $t6, $t8, 4
    ctx->r14 = S32(ctx->r24 << 4);
    // 0x802C8CE0: addu        $t5, $t6, $t2
    ctx->r13 = ADD32(ctx->r14, ctx->r10);
    // 0x802C8CE4: addu        $a2, $a2, $t5
    ctx->r6 = ADD32(ctx->r6, ctx->r13);
    // 0x802C8CE8: addiu       $t1, $zero, 0xC9
    ctx->r9 = ADD32(0, 0XC9);
    // 0x802C8CEC: sw          $t1, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r9;
    // 0x802C8CF0: lh          $a2, -0x5444($a2)
    ctx->r6 = MEM_H(ctx->r6, -0X5444);
    // 0x802C8CF4: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C8CF8: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C8CFC: jal         0x801EB00C
    // 0x802C8D00: addiu       $a3, $zero, 0x16E
    ctx->r7 = ADD32(0, 0X16E);
    func_801EB00C(rdram, ctx);
        goto after_37;
    // 0x802C8D00: addiu       $a3, $zero, 0x16E
    ctx->r7 = ADD32(0, 0X16E);
    after_37:
    // 0x802C8D04: lui         $t7, 0xB400
    ctx->r15 = S32(0XB400 << 16);
L_802C8D08:
    // 0x802C8D08: sw          $t7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r15;
    // 0x802C8D0C: lui         $t9, 0x802D
    ctx->r25 = S32(0X802D << 16);
    // 0x802C8D10: lhu         $t9, -0x6928($t9)
    ctx->r25 = MEM_HU(ctx->r25, -0X6928);
    // 0x802C8D14: addiu       $s6, $v0, 0x8
    ctx->r22 = ADD32(ctx->r2, 0X8);
    // 0x802C8D18: or          $a0, $s6, $zero
    ctx->r4 = ctx->r22 | 0;
    // 0x802C8D1C: lui         $t3, 0x103
    ctx->r11 = S32(0X103 << 16);
    // 0x802C8D20: lui         $t8, 0x700
    ctx->r24 = S32(0X700 << 16);
    // 0x802C8D24: sw          $t9, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r25;
    // 0x802C8D28: addiu       $t8, $t8, 0xA40
    ctx->r24 = ADD32(ctx->r24, 0XA40);
    // 0x802C8D2C: ori         $t3, $t3, 0x40
    ctx->r11 = ctx->r11 | 0X40;
    // 0x802C8D30: addiu       $s6, $s6, 0x8
    ctx->r22 = ADD32(ctx->r22, 0X8);
    // 0x802C8D34: sw          $t3, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r11;
    // 0x802C8D38: sw          $t8, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r24;
    // 0x802C8D3C: or          $a1, $s6, $zero
    ctx->r5 = ctx->r22 | 0;
    // 0x802C8D40: lui         $t6, 0x107
    ctx->r14 = S32(0X107 << 16);
    // 0x802C8D44: addiu       $t6, $t6, -0xB78
    ctx->r14 = ADD32(ctx->r14, -0XB78);
    // 0x802C8D48: lui         $t4, 0x600
    ctx->r12 = S32(0X600 << 16);
    // 0x802C8D4C: sw          $t4, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r12;
    // 0x802C8D50: sw          $t6, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r14;
    // 0x802C8D54: lui         $s1, 0x700
    ctx->r17 = S32(0X700 << 16);
    // 0x802C8D58: lui         $s2, 0x700
    ctx->r18 = S32(0X700 << 16);
    // 0x802C8D5C: lui         $fp, 0x801D
    ctx->r30 = S32(0X801D << 16);
    // 0x802C8D60: lui         $s5, 0x800E
    ctx->r21 = S32(0X800E << 16);
    // 0x802C8D64: lui         $s4, 0x102
    ctx->r20 = S32(0X102 << 16);
    // 0x802C8D68: lui         $s3, 0x380
    ctx->r19 = S32(0X380 << 16);
    // 0x802C8D6C: addiu       $s6, $s6, 0x8
    ctx->r22 = ADD32(ctx->r22, 0X8);
    // 0x802C8D70: ori         $s3, $s3, 0x10
    ctx->r19 = ctx->r19 | 0X10;
    // 0x802C8D74: ori         $s4, $s4, 0x40
    ctx->r20 = ctx->r20 | 0X40;
    // 0x802C8D78: addiu       $s5, $s5, -0x5624
    ctx->r21 = ADD32(ctx->r21, -0X5624);
    // 0x802C8D7C: addiu       $fp, $fp, -0x1A08
    ctx->r30 = ADD32(ctx->r30, -0X1A08);
    // 0x802C8D80: addiu       $s2, $s2, 0xA80
    ctx->r18 = ADD32(ctx->r18, 0XA80);
    // 0x802C8D84: addiu       $s1, $s1, 0x1280
    ctx->r17 = ADD32(ctx->r17, 0X1280);
    // 0x802C8D88: sw          $zero, 0x94($sp)
    MEM_W(0X94, ctx->r29) = 0;
    // 0x802C8D8C: or          $s0, $zero, $zero
    ctx->r16 = 0 | 0;
    // 0x802C8D90: addiu       $s7, $zero, 0x2
    ctx->r23 = ADD32(0, 0X2);
L_802C8D94:
    // 0x802C8D94: or          $v0, $s6, $zero
    ctx->r2 = ctx->r22 | 0;
    // 0x802C8D98: lw          $t0, 0x94($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X94);
    // 0x802C8D9C: addiu       $s6, $s6, 0x8
    ctx->r22 = ADD32(ctx->r22, 0X8);
    // 0x802C8DA0: sw          $s1, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r17;
    // 0x802C8DA4: sw          $s3, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r19;
    // 0x802C8DA8: or          $v1, $s6, $zero
    ctx->r3 = ctx->r22 | 0;
    // 0x802C8DAC: sw          $s4, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r20;
    // 0x802C8DB0: sw          $s2, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r18;
    // 0x802C8DB4: lw          $t2, 0x11C($sp)
    ctx->r10 = MEM_W(ctx->r29, 0X11C);
    // 0x802C8DB8: addiu       $s6, $s6, 0x8
    ctx->r22 = ADD32(ctx->r22, 0X8);
    // 0x802C8DBC: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x802C8DC0: bne         $t2, $at, L_802C8DD4
    if (ctx->r10 != ctx->r1) {
        // 0x802C8DC4: or          $a0, $s6, $zero
        ctx->r4 = ctx->r22 | 0;
            goto L_802C8DD4;
    }
    // 0x802C8DC4: or          $a0, $s6, $zero
    ctx->r4 = ctx->r22 | 0;
    // 0x802C8DC8: addu        $t5, $s5, $t0
    ctx->r13 = ADD32(ctx->r21, ctx->r8);
    // 0x802C8DCC: b           L_802C8DE0
    // 0x802C8DD0: lw          $a1, 0x0($t5)
    ctx->r5 = MEM_W(ctx->r13, 0X0);
        goto L_802C8DE0;
    // 0x802C8DD0: lw          $a1, 0x0($t5)
    ctx->r5 = MEM_W(ctx->r13, 0X0);
L_802C8DD4:
    // 0x802C8DD4: lui         $a1, 0x801D
    ctx->r5 = S32(0X801D << 16);
    // 0x802C8DD8: addu        $a1, $a1, $t0
    ctx->r5 = ADD32(ctx->r5, ctx->r8);
    // 0x802C8DDC: lw          $a1, -0x18E8($a1)
    ctx->r5 = MEM_W(ctx->r5, -0X18E8);
L_802C8DE0:
    // 0x802C8DE0: bne         $a1, $s7, L_802C8DF0
    if (ctx->r5 != ctx->r23) {
        // 0x802C8DE4: or          $a2, $zero, $zero
        ctx->r6 = 0 | 0;
            goto L_802C8DF0;
    }
    // 0x802C8DE4: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x802C8DE8: b           L_802C8E00
    // 0x802C8DEC: addiu       $a1, $zero, 0x3
    ctx->r5 = ADD32(0, 0X3);
        goto L_802C8E00;
    // 0x802C8DEC: addiu       $a1, $zero, 0x3
    ctx->r5 = ADD32(0, 0X3);
L_802C8DF0:
    // 0x802C8DF0: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x802C8DF4: bnel        $a1, $at, L_802C8E04
    if (ctx->r5 != ctx->r1) {
        // 0x802C8DF8: lw          $t1, 0x0($fp)
        ctx->r9 = MEM_W(ctx->r30, 0X0);
            goto L_802C8E04;
    }
    goto skip_2;
    // 0x802C8DF8: lw          $t1, 0x0($fp)
    ctx->r9 = MEM_W(ctx->r30, 0X0);
    skip_2:
    // 0x802C8DFC: addiu       $a1, $zero, 0x5
    ctx->r5 = ADD32(0, 0X5);
L_802C8E00:
    // 0x802C8E00: lw          $t1, 0x0($fp)
    ctx->r9 = MEM_W(ctx->r30, 0X0);
L_802C8E04:
    // 0x802C8E04: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    // 0x802C8E08: sw          $t0, 0x94($sp)
    MEM_W(0X94, ctx->r29) = ctx->r8;
    // 0x802C8E0C: addu        $t7, $t1, $s0
    ctx->r15 = ADD32(ctx->r9, ctx->r16);
    // 0x802C8E10: addiu       $t9, $t7, 0xC80
    ctx->r25 = ADD32(ctx->r15, 0XC80);
    // 0x802C8E14: jal         0x801E4FE8
    // 0x802C8E18: sw          $t9, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r25;
    func_801E4FE8(rdram, ctx);
        goto after_38;
    // 0x802C8E18: sw          $t9, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r25;
    after_38:
    // 0x802C8E1C: lw          $t3, 0x94($sp)
    ctx->r11 = MEM_W(ctx->r29, 0X94);
    // 0x802C8E20: addiu       $s0, $s0, 0xC0
    ctx->r16 = ADD32(ctx->r16, 0XC0);
    // 0x802C8E24: addiu       $at, $zero, 0x300
    ctx->r1 = ADD32(0, 0X300);
    // 0x802C8E28: addiu       $t8, $t3, 0x4
    ctx->r24 = ADD32(ctx->r11, 0X4);
    // 0x802C8E2C: sw          $t8, 0x94($sp)
    MEM_W(0X94, ctx->r29) = ctx->r24;
    // 0x802C8E30: addiu       $s1, $s1, 0x10
    ctx->r17 = ADD32(ctx->r17, 0X10);
    // 0x802C8E34: addiu       $s2, $s2, 0x40
    ctx->r18 = ADD32(ctx->r18, 0X40);
    // 0x802C8E38: bne         $s0, $at, L_802C8D94
    if (ctx->r16 != ctx->r1) {
        // 0x802C8E3C: or          $s6, $v0, $zero
        ctx->r22 = ctx->r2 | 0;
            goto L_802C8D94;
    }
    // 0x802C8E3C: or          $s6, $v0, $zero
    ctx->r22 = ctx->r2 | 0;
    // 0x802C8E40: lw          $ra, 0x74($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X74);
    // 0x802C8E44: lw          $s0, 0x50($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X50);
    // 0x802C8E48: lw          $s1, 0x54($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X54);
    // 0x802C8E4C: lw          $s2, 0x58($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X58);
    // 0x802C8E50: lw          $s3, 0x5C($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X5C);
    // 0x802C8E54: lw          $s4, 0x60($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X60);
    // 0x802C8E58: lw          $s5, 0x64($sp)
    ctx->r21 = MEM_W(ctx->r29, 0X64);
    // 0x802C8E5C: lw          $s6, 0x68($sp)
    ctx->r22 = MEM_W(ctx->r29, 0X68);
    // 0x802C8E60: lw          $s7, 0x6C($sp)
    ctx->r23 = MEM_W(ctx->r29, 0X6C);
    // 0x802C8E64: lw          $fp, 0x70($sp)
    ctx->r30 = MEM_W(ctx->r29, 0X70);
    // 0x802C8E68: jr          $ra
    // 0x802C8E6C: addiu       $sp, $sp, 0x128
    ctx->r29 = ADD32(ctx->r29, 0X128);
    return;
    // 0x802C8E6C: addiu       $sp, $sp, 0x128
    ctx->r29 = ADD32(ctx->r29, 0X128);
;}
RECOMP_FUNC void func_i1_802C8E70(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C8E70: lui         $t0, 0x802D
    ctx->r8 = S32(0X802D << 16);
    // 0x802C8E74: addiu       $t0, $t0, -0x6AE0
    ctx->r8 = ADD32(ctx->r8, -0X6AE0);
    // 0x802C8E78: lw          $t6, 0x0($t0)
    ctx->r14 = MEM_W(ctx->r8, 0X0);
    // 0x802C8E7C: addiu       $sp, $sp, -0x28
    ctx->r29 = ADD32(ctx->r29, -0X28);
    // 0x802C8E80: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x802C8E84: sltiu       $at, $t6, 0x8
    ctx->r1 = ctx->r14 < 0X8 ? 1 : 0;
    // 0x802C8E88: beq         $at, $zero, L_802C9114
    if (ctx->r1 == 0) {
        // 0x802C8E8C: sw          $zero, 0x1C($sp)
        MEM_W(0X1C, ctx->r29) = 0;
            goto L_802C9114;
    }
    // 0x802C8E8C: sw          $zero, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = 0;
    // 0x802C8E90: sll         $t6, $t6, 2
    ctx->r14 = S32(ctx->r14 << 2);
    // 0x802C8E94: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C8E98: addu        $at, $at, $t6
    gpr jr_addend_802C8EA0 = ctx->r14;
    ctx->r1 = ADD32(ctx->r1, ctx->r14);
    // 0x802C8E9C: lw          $t6, -0x6984($at)
    ctx->r14 = ADD32(ctx->r1, -0X6984);
    // 0x802C8EA0: jr          $t6
    // 0x802C8EA4: nop

    switch (jr_addend_802C8EA0 >> 2) {
        case 0: goto L_802C8EA8; break;
        case 1: goto L_802C8EDC; break;
        case 2: goto L_802C8F04; break;
        case 3: goto L_802C8F78; break;
        case 4: goto L_802C8FA8; break;
        case 5: goto L_802C9000; break;
        case 6: goto L_802C9074; break;
        case 7: goto L_802C9114; break;
        default: switch_error(__func__, 0x802C8EA0, 0x802C967C);
    }
    // 0x802C8EA4: nop

L_802C8EA8:
    // 0x802C8EA8: lui         $a3, 0x802D
    ctx->r7 = S32(0X802D << 16);
    // 0x802C8EAC: addiu       $a3, $a3, -0x6930
    ctx->r7 = ADD32(ctx->r7, -0X6930);
    // 0x802C8EB0: lw          $t7, 0x0($a3)
    ctx->r15 = MEM_W(ctx->r7, 0X0);
    // 0x802C8EB4: addiu       $t1, $zero, 0x1
    ctx->r9 = ADD32(0, 0X1);
    // 0x802C8EB8: addiu       $t2, $zero, 0x1
    ctx->r10 = ADD32(0, 0X1);
    // 0x802C8EBC: addiu       $t8, $t7, 0x1
    ctx->r24 = ADD32(ctx->r15, 0X1);
    // 0x802C8EC0: slti        $at, $t8, 0x3C
    ctx->r1 = SIGNED(ctx->r24) < 0X3C ? 1 : 0;
    // 0x802C8EC4: bne         $at, $zero, L_802C9114
    if (ctx->r1 != 0) {
        // 0x802C8EC8: sw          $t8, 0x0($a3)
        MEM_W(0X0, ctx->r7) = ctx->r24;
            goto L_802C9114;
    }
    // 0x802C8EC8: sw          $t8, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r24;
    // 0x802C8ECC: sw          $t1, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r9;
    // 0x802C8ED0: sw          $zero, 0x0($a3)
    MEM_W(0X0, ctx->r7) = 0;
    // 0x802C8ED4: b           L_802C9114
    // 0x802C8ED8: sw          $t2, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r10;
        goto L_802C9114;
    // 0x802C8ED8: sw          $t2, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r10;
L_802C8EDC:
    // 0x802C8EDC: lui         $t3, 0x802D
    ctx->r11 = S32(0X802D << 16);
    // 0x802C8EE0: lw          $t3, -0x6ADC($t3)
    ctx->r11 = MEM_W(ctx->r11, -0X6ADC);
    // 0x802C8EE4: addiu       $v1, $zero, 0x14
    ctx->r3 = ADD32(0, 0X14);
    // 0x802C8EE8: lui         $a3, 0x802D
    ctx->r7 = S32(0X802D << 16);
    // 0x802C8EEC: bne         $v1, $t3, L_802C9114
    if (ctx->r3 != ctx->r11) {
        // 0x802C8EF0: addiu       $a3, $a3, -0x6930
        ctx->r7 = ADD32(ctx->r7, -0X6930);
            goto L_802C9114;
    }
    // 0x802C8EF0: addiu       $a3, $a3, -0x6930
    ctx->r7 = ADD32(ctx->r7, -0X6930);
    // 0x802C8EF4: addiu       $t4, $zero, 0x2
    ctx->r12 = ADD32(0, 0X2);
    // 0x802C8EF8: sw          $t4, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r12;
    // 0x802C8EFC: b           L_802C9114
    // 0x802C8F00: sw          $zero, 0x0($a3)
    MEM_W(0X0, ctx->r7) = 0;
        goto L_802C9114;
    // 0x802C8F00: sw          $zero, 0x0($a3)
    MEM_W(0X0, ctx->r7) = 0;
L_802C8F04:
    // 0x802C8F04: lui         $a3, 0x802D
    ctx->r7 = S32(0X802D << 16);
    // 0x802C8F08: addiu       $a3, $a3, -0x6930
    ctx->r7 = ADD32(ctx->r7, -0X6930);
    // 0x802C8F0C: lw          $v1, 0x0($a3)
    ctx->r3 = MEM_W(ctx->r7, 0X0);
    // 0x802C8F10: lui         $t6, 0x801D
    ctx->r14 = S32(0X801D << 16);
    // 0x802C8F14: slti        $at, $v1, 0x258
    ctx->r1 = SIGNED(ctx->r3) < 0X258 ? 1 : 0;
    // 0x802C8F18: beq         $at, $zero, L_802C8F28
    if (ctx->r1 == 0) {
        // 0x802C8F1C: addiu       $t5, $v1, 0x1
        ctx->r13 = ADD32(ctx->r3, 0X1);
            goto L_802C8F28;
    }
    // 0x802C8F1C: addiu       $t5, $v1, 0x1
    ctx->r13 = ADD32(ctx->r3, 0X1);
    // 0x802C8F20: sw          $t5, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r13;
    // 0x802C8F24: or          $v1, $t5, $zero
    ctx->r3 = ctx->r13 | 0;
L_802C8F28:
    // 0x802C8F28: slti        $at, $v1, 0x15
    ctx->r1 = SIGNED(ctx->r3) < 0X15 ? 1 : 0;
    // 0x802C8F2C: bnel        $at, $zero, L_802C9118
    if (ctx->r1 != 0) {
        // 0x802C8F30: lw          $t1, 0x1C($sp)
        ctx->r9 = MEM_W(ctx->r29, 0X1C);
            goto L_802C9118;
    }
    goto skip_0;
    // 0x802C8F30: lw          $t1, 0x1C($sp)
    ctx->r9 = MEM_W(ctx->r29, 0X1C);
    skip_0:
    // 0x802C8F34: lhu         $t6, -0x19A6($t6)
    ctx->r14 = MEM_HU(ctx->r14, -0X19A6);
    // 0x802C8F38: addiu       $t8, $zero, 0x3
    ctx->r24 = ADD32(0, 0X3);
    // 0x802C8F3C: addiu       $a0, $zero, 0x11
    ctx->r4 = ADD32(0, 0X11);
    // 0x802C8F40: andi        $t7, $t6, 0xB000
    ctx->r15 = ctx->r14 & 0XB000;
    // 0x802C8F44: beq         $t7, $zero, L_802C8F64
    if (ctx->r15 == 0) {
        // 0x802C8F48: slti        $at, $v1, 0x258
        ctx->r1 = SIGNED(ctx->r3) < 0X258 ? 1 : 0;
            goto L_802C8F64;
    }
    // 0x802C8F48: slti        $at, $v1, 0x258
    ctx->r1 = SIGNED(ctx->r3) < 0X258 ? 1 : 0;
    // 0x802C8F4C: sw          $t8, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r24;
    // 0x802C8F50: sw          $zero, 0x0($a3)
    MEM_W(0X0, ctx->r7) = 0;
    // 0x802C8F54: jal         0x800C37F4
    // 0x802C8F58: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_0;
    // 0x802C8F58: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_0:
    // 0x802C8F5C: b           L_802C9118
    // 0x802C8F60: lw          $t1, 0x1C($sp)
    ctx->r9 = MEM_W(ctx->r29, 0X1C);
        goto L_802C9118;
    // 0x802C8F60: lw          $t1, 0x1C($sp)
    ctx->r9 = MEM_W(ctx->r29, 0X1C);
L_802C8F64:
    // 0x802C8F64: bne         $at, $zero, L_802C9114
    if (ctx->r1 != 0) {
        // 0x802C8F68: addiu       $t9, $zero, 0x3
        ctx->r25 = ADD32(0, 0X3);
            goto L_802C9114;
    }
    // 0x802C8F68: addiu       $t9, $zero, 0x3
    ctx->r25 = ADD32(0, 0X3);
    // 0x802C8F6C: sw          $t9, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r25;
    // 0x802C8F70: b           L_802C9114
    // 0x802C8F74: sw          $zero, 0x0($a3)
    MEM_W(0X0, ctx->r7) = 0;
        goto L_802C9114;
    // 0x802C8F74: sw          $zero, 0x0($a3)
    MEM_W(0X0, ctx->r7) = 0;
L_802C8F78:
    // 0x802C8F78: lui         $t1, 0x802D
    ctx->r9 = S32(0X802D << 16);
    // 0x802C8F7C: lw          $t1, -0x6ADC($t1)
    ctx->r9 = MEM_W(ctx->r9, -0X6ADC);
    // 0x802C8F80: addiu       $at, $zero, -0x171
    ctx->r1 = ADD32(0, -0X171);
    // 0x802C8F84: lui         $a3, 0x802D
    ctx->r7 = S32(0X802D << 16);
    // 0x802C8F88: bne         $t1, $at, L_802C9114
    if (ctx->r9 != ctx->r1) {
        // 0x802C8F8C: addiu       $a3, $a3, -0x6930
        ctx->r7 = ADD32(ctx->r7, -0X6930);
            goto L_802C9114;
    }
    // 0x802C8F8C: addiu       $a3, $a3, -0x6930
    ctx->r7 = ADD32(ctx->r7, -0X6930);
    // 0x802C8F90: addiu       $t2, $zero, 0x4
    ctx->r10 = ADD32(0, 0X4);
    // 0x802C8F94: sw          $t2, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r10;
    // 0x802C8F98: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C8F9C: sw          $zero, -0x6AD4($at)
    MEM_W(-0X6AD4, ctx->r1) = 0;
    // 0x802C8FA0: b           L_802C9114
    // 0x802C8FA4: sw          $zero, 0x0($a3)
    MEM_W(0X0, ctx->r7) = 0;
        goto L_802C9114;
    // 0x802C8FA4: sw          $zero, 0x0($a3)
    MEM_W(0X0, ctx->r7) = 0;
L_802C8FA8:
    // 0x802C8FA8: lui         $a3, 0x802D
    ctx->r7 = S32(0X802D << 16);
    // 0x802C8FAC: addiu       $a3, $a3, -0x6930
    ctx->r7 = ADD32(ctx->r7, -0X6930);
    // 0x802C8FB0: lw          $t3, 0x0($a3)
    ctx->r11 = MEM_W(ctx->r7, 0X0);
    // 0x802C8FB4: addiu       $at, $zero, 0xA
    ctx->r1 = ADD32(0, 0XA);
    // 0x802C8FB8: addiu       $t4, $zero, 0x5
    ctx->r12 = ADD32(0, 0X5);
    // 0x802C8FBC: bne         $t3, $at, L_802C9114
    if (ctx->r11 != ctx->r1) {
        // 0x802C8FC0: addiu       $t5, $zero, 0xAA
        ctx->r13 = ADD32(0, 0XAA);
            goto L_802C9114;
    }
    // 0x802C8FC0: addiu       $t5, $zero, 0xAA
    ctx->r13 = ADD32(0, 0XAA);
    // 0x802C8FC4: sw          $t4, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r12;
    // 0x802C8FC8: sw          $zero, 0x0($a3)
    MEM_W(0X0, ctx->r7) = 0;
    // 0x802C8FCC: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C8FD0: sw          $t5, -0x6AD4($at)
    MEM_W(-0X6AD4, ctx->r1) = ctx->r13;
    // 0x802C8FD4: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C8FD8: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C8FDC: sw          $t6, -0x6AD8($at)
    MEM_W(-0X6AD8, ctx->r1) = ctx->r14;
    // 0x802C8FE0: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C8FE4: addiu       $t7, $zero, 0x3
    ctx->r15 = ADD32(0, 0X3);
    // 0x802C8FE8: sw          $t7, -0x6AD0($at)
    MEM_W(-0X6AD0, ctx->r1) = ctx->r15;
    // 0x802C8FEC: addiu       $a0, $zero, 0x31
    ctx->r4 = ADD32(0, 0X31);
    // 0x802C8FF0: jal         0x800C37F4
    // 0x802C8FF4: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_1;
    // 0x802C8FF4: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_1:
    // 0x802C8FF8: b           L_802C9118
    // 0x802C8FFC: lw          $t1, 0x1C($sp)
    ctx->r9 = MEM_W(ctx->r29, 0X1C);
        goto L_802C9118;
    // 0x802C8FFC: lw          $t1, 0x1C($sp)
    ctx->r9 = MEM_W(ctx->r29, 0X1C);
L_802C9000:
    // 0x802C9000: lui         $t8, 0x802D
    ctx->r24 = S32(0X802D << 16);
    // 0x802C9004: lw          $t8, -0x6ACC($t8)
    ctx->r24 = MEM_W(ctx->r24, -0X6ACC);
    // 0x802C9008: addiu       $v1, $zero, 0x14
    ctx->r3 = ADD32(0, 0X14);
    // 0x802C900C: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    // 0x802C9010: bne         $v1, $t8, L_802C901C
    if (ctx->r3 != ctx->r24) {
        // 0x802C9014: lui         $t9, 0x802D
        ctx->r25 = S32(0X802D << 16);
            goto L_802C901C;
    }
    // 0x802C9014: lui         $t9, 0x802D
    ctx->r25 = S32(0X802D << 16);
    // 0x802C9018: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
L_802C901C:
    // 0x802C901C: lw          $t9, -0x6AC8($t9)
    ctx->r25 = MEM_W(ctx->r25, -0X6AC8);
    // 0x802C9020: lui         $t1, 0x802D
    ctx->r9 = S32(0X802D << 16);
    // 0x802C9024: lui         $t2, 0x802D
    ctx->r10 = S32(0X802D << 16);
    // 0x802C9028: bne         $v1, $t9, L_802C9034
    if (ctx->r3 != ctx->r25) {
        // 0x802C902C: lui         $a3, 0x802D
        ctx->r7 = S32(0X802D << 16);
            goto L_802C9034;
    }
    // 0x802C902C: lui         $a3, 0x802D
    ctx->r7 = S32(0X802D << 16);
    // 0x802C9030: addiu       $v0, $v0, 0x1
    ctx->r2 = ADD32(ctx->r2, 0X1);
L_802C9034:
    // 0x802C9034: lw          $t1, -0x6AC4($t1)
    ctx->r9 = MEM_W(ctx->r9, -0X6AC4);
    // 0x802C9038: addiu       $a3, $a3, -0x6930
    ctx->r7 = ADD32(ctx->r7, -0X6930);
    // 0x802C903C: addiu       $t3, $zero, 0x6
    ctx->r11 = ADD32(0, 0X6);
    // 0x802C9040: bne         $v1, $t1, L_802C904C
    if (ctx->r3 != ctx->r9) {
        // 0x802C9044: nop
    
            goto L_802C904C;
    }
    // 0x802C9044: nop

    // 0x802C9048: addiu       $v0, $v0, 0x1
    ctx->r2 = ADD32(ctx->r2, 0X1);
L_802C904C:
    // 0x802C904C: lw          $t2, -0x6AC0($t2)
    ctx->r10 = MEM_W(ctx->r10, -0X6AC0);
    // 0x802C9050: bnel        $v1, $t2, L_802C9060
    if (ctx->r3 != ctx->r10) {
        // 0x802C9054: addiu       $v1, $zero, 0x4
        ctx->r3 = ADD32(0, 0X4);
            goto L_802C9060;
    }
    goto skip_1;
    // 0x802C9054: addiu       $v1, $zero, 0x4
    ctx->r3 = ADD32(0, 0X4);
    skip_1:
    // 0x802C9058: addiu       $v0, $v0, 0x1
    ctx->r2 = ADD32(ctx->r2, 0X1);
    // 0x802C905C: addiu       $v1, $zero, 0x4
    ctx->r3 = ADD32(0, 0X4);
L_802C9060:
    // 0x802C9060: bnel        $v1, $v0, L_802C9118
    if (ctx->r3 != ctx->r2) {
        // 0x802C9064: lw          $t1, 0x1C($sp)
        ctx->r9 = MEM_W(ctx->r29, 0X1C);
            goto L_802C9118;
    }
    goto skip_2;
    // 0x802C9064: lw          $t1, 0x1C($sp)
    ctx->r9 = MEM_W(ctx->r29, 0X1C);
    skip_2:
    // 0x802C9068: sw          $t3, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r11;
    // 0x802C906C: b           L_802C9114
    // 0x802C9070: sw          $zero, 0x0($a3)
    MEM_W(0X0, ctx->r7) = 0;
        goto L_802C9114;
    // 0x802C9070: sw          $zero, 0x0($a3)
    MEM_W(0X0, ctx->r7) = 0;
L_802C9074:
    // 0x802C9074: lui         $a3, 0x802D
    ctx->r7 = S32(0X802D << 16);
    // 0x802C9078: addiu       $a3, $a3, -0x6930
    ctx->r7 = ADD32(ctx->r7, -0X6930);
    // 0x802C907C: lw          $t4, 0x0($a3)
    ctx->r12 = MEM_W(ctx->r7, 0X0);
    // 0x802C9080: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    // 0x802C9084: lui         $t6, 0x801D
    ctx->r14 = S32(0X801D << 16);
    // 0x802C9088: addiu       $v1, $t4, 0x1
    ctx->r3 = ADD32(ctx->r12, 0X1);
    // 0x802C908C: slti        $at, $v1, 0x190
    ctx->r1 = SIGNED(ctx->r3) < 0X190 ? 1 : 0;
    // 0x802C9090: bne         $at, $zero, L_802C909C
    if (ctx->r1 != 0) {
        // 0x802C9094: sw          $v1, 0x0($a3)
        MEM_W(0X0, ctx->r7) = ctx->r3;
            goto L_802C909C;
    }
    // 0x802C9094: sw          $v1, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r3;
    // 0x802C9098: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
L_802C909C:
    // 0x802C909C: slti        $at, $v1, 0x28
    ctx->r1 = SIGNED(ctx->r3) < 0X28 ? 1 : 0;
    // 0x802C90A0: bne         $at, $zero, L_802C90E0
    if (ctx->r1 != 0) {
        // 0x802C90A4: nop
    
            goto L_802C90E0;
    }
    // 0x802C90A4: nop

    // 0x802C90A8: lhu         $t6, -0x19A6($t6)
    ctx->r14 = MEM_HU(ctx->r14, -0X19A6);
    // 0x802C90AC: addiu       $a0, $zero, 0x11
    ctx->r4 = ADD32(0, 0X11);
    // 0x802C90B0: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C90B4: andi        $t7, $t6, 0xB000
    ctx->r15 = ctx->r14 & 0XB000;
    // 0x802C90B8: beq         $t7, $zero, L_802C90E0
    if (ctx->r15 == 0) {
        // 0x802C90BC: nop
    
            goto L_802C90E0;
    }
    // 0x802C90BC: nop

    // 0x802C90C0: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
    // 0x802C90C4: jal         0x800C37F4
    // 0x802C90C8: sw          $v0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r2;
    func_800C37F4(rdram, ctx);
        goto after_2;
    // 0x802C90C8: sw          $v0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r2;
    after_2:
    // 0x802C90CC: lui         $a3, 0x802D
    ctx->r7 = S32(0X802D << 16);
    // 0x802C90D0: lui         $t0, 0x802D
    ctx->r8 = S32(0X802D << 16);
    // 0x802C90D4: addiu       $t0, $t0, -0x6AE0
    ctx->r8 = ADD32(ctx->r8, -0X6AE0);
    // 0x802C90D8: addiu       $a3, $a3, -0x6930
    ctx->r7 = ADD32(ctx->r7, -0X6930);
    // 0x802C90DC: lw          $v0, 0x20($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X20);
L_802C90E0:
    // 0x802C90E0: beq         $v0, $zero, L_802C9114
    if (ctx->r2 == 0) {
        // 0x802C90E4: addiu       $t8, $zero, 0x7
        ctx->r24 = ADD32(0, 0X7);
            goto L_802C9114;
    }
    // 0x802C90E4: addiu       $t8, $zero, 0x7
    ctx->r24 = ADD32(0, 0X7);
    // 0x802C90E8: sw          $t8, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r24;
    // 0x802C90EC: sw          $zero, 0x0($a3)
    MEM_W(0X0, ctx->r7) = 0;
    // 0x802C90F0: addiu       $t9, $zero, 0x1
    ctx->r25 = ADD32(0, 0X1);
    // 0x802C90F4: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C90F8: sw          $t9, -0x6AA8($at)
    MEM_W(-0X6AA8, ctx->r1) = ctx->r25;
    // 0x802C90FC: addiu       $a0, $zero, 0x3
    ctx->r4 = ADD32(0, 0X3);
    // 0x802C9100: addiu       $a1, $zero, 0x14
    ctx->r5 = ADD32(0, 0X14);
    // 0x802C9104: jal         0x801E6FB0
    // 0x802C9108: addiu       $a2, $zero, 0x14
    ctx->r6 = ADD32(0, 0X14);
    FadeTransition_SetProps(rdram, ctx);
        goto after_3;
    // 0x802C9108: addiu       $a2, $zero, 0x14
    ctx->r6 = ADD32(0, 0X14);
    after_3:
    // 0x802C910C: jal         0x800C1F60
    // 0x802C9110: addiu       $a0, $zero, 0xB
    ctx->r4 = ADD32(0, 0XB);
    func_800C1F60(rdram, ctx);
        goto after_4;
    // 0x802C9110: addiu       $a0, $zero, 0xB
    ctx->r4 = ADD32(0, 0XB);
    after_4:
L_802C9114:
    // 0x802C9114: lw          $t1, 0x1C($sp)
    ctx->r9 = MEM_W(ctx->r29, 0X1C);
L_802C9118:
    // 0x802C9118: addiu       $a0, $zero, 0x31
    ctx->r4 = ADD32(0, 0X31);
    // 0x802C911C: beql        $t1, $zero, L_802C9130
    if (ctx->r9 == 0) {
        // 0x802C9120: lw          $ra, 0x14($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X14);
            goto L_802C9130;
    }
    goto skip_3;
    // 0x802C9120: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    skip_3:
    // 0x802C9124: jal         0x800C37F4
    // 0x802C9128: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_5;
    // 0x802C9128: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_5:
    // 0x802C912C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C9130:
    // 0x802C9130: addiu       $sp, $sp, 0x28
    ctx->r29 = ADD32(ctx->r29, 0X28);
    // 0x802C9134: jr          $ra
    // 0x802C9138: nop

    return;
    // 0x802C9138: nop

;}
RECOMP_FUNC void func_802C913C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C913C: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x802C9140: addiu       $v0, $v0, -0x19C4
    ctx->r2 = ADD32(ctx->r2, -0X19C4);
    // 0x802C9144: lw          $t6, 0x0($v0)
    ctx->r14 = MEM_W(ctx->r2, 0X0);
    // 0x802C9148: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x802C914C: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x802C9150: beq         $t6, $zero, L_802C9184
    if (ctx->r14 == 0) {
        // 0x802C9154: or          $a3, $a0, $zero
        ctx->r7 = ctx->r4 | 0;
            goto L_802C9184;
    }
    // 0x802C9154: or          $a3, $a0, $zero
    ctx->r7 = ctx->r4 | 0;
    // 0x802C9158: sw          $zero, 0x0($v0)
    MEM_W(0X0, ctx->r2) = 0;
    // 0x802C915C: lui         $t7, 0x800E
    ctx->r15 = S32(0X800E << 16);
    // 0x802C9160: lw          $t7, -0x54DC($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X54DC);
    // 0x802C9164: addiu       $at, $zero, 0x7
    ctx->r1 = ADD32(0, 0X7);
    // 0x802C9168: lui         $a1, 0x802D
    ctx->r5 = S32(0X802D << 16);
    // 0x802C916C: bne         $t7, $at, L_802C9184
    if (ctx->r15 != ctx->r1) {
        // 0x802C9170: addiu       $a1, $a1, -0x6BC0
        ctx->r5 = ADD32(ctx->r5, -0X6BC0);
            goto L_802C9184;
    }
    // 0x802C9170: addiu       $a1, $a1, -0x6BC0
    ctx->r5 = ADD32(ctx->r5, -0X6BC0);
    // 0x802C9174: jal         0x80093C44
    // 0x802C9178: sw          $zero, 0x0($a1)
    MEM_W(0X0, ctx->r5) = 0;
    func_80093C44(rdram, ctx);
        goto after_0;
    // 0x802C9178: sw          $zero, 0x0($a1)
    MEM_W(0X0, ctx->r5) = 0;
    after_0:
    // 0x802C917C: b           L_802C9374
    // 0x802C9180: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_802C9374;
    // 0x802C9180: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C9184:
    // 0x802C9184: lui         $t8, 0x8023
    ctx->r24 = S32(0X8023 << 16);
    // 0x802C9188: lh          $t8, -0x75EA($t8)
    ctx->r24 = MEM_H(ctx->r24, -0X75EA);
    // 0x802C918C: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    // 0x802C9190: lui         $t9, 0x800E
    ctx->r25 = S32(0X800E << 16);
    // 0x802C9194: bne         $a2, $t8, L_802C91CC
    if (ctx->r6 != ctx->r24) {
        // 0x802C9198: nop
    
            goto L_802C91CC;
    }
    // 0x802C9198: nop

    // 0x802C919C: lw          $t9, -0x54DC($t9)
    ctx->r25 = MEM_W(ctx->r25, -0X54DC);
    // 0x802C91A0: addiu       $at, $zero, 0x7
    ctx->r1 = ADD32(0, 0X7);
    // 0x802C91A4: lui         $a0, 0x8019
    ctx->r4 = S32(0X8019 << 16);
    // 0x802C91A8: bne         $t9, $at, L_802C91CC
    if (ctx->r25 != ctx->r1) {
        // 0x802C91AC: addiu       $a0, $a0, 0x2610
        ctx->r4 = ADD32(ctx->r4, 0X2610);
            goto L_802C91CC;
    }
    // 0x802C91AC: addiu       $a0, $a0, 0x2610
    ctx->r4 = ADD32(ctx->r4, 0X2610);
    // 0x802C91B0: jal         0x800BFDD0
    // 0x802C91B4: sw          $a3, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r7;
    func_800BFDD0(rdram, ctx);
        goto after_1;
    // 0x802C91B4: sw          $a3, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r7;
    after_1:
    // 0x802C91B8: lui         $a0, 0x8019
    ctx->r4 = S32(0X8019 << 16);
    // 0x802C91BC: jal         0x800BFEF8
    // 0x802C91C0: addiu       $a0, $a0, 0x2630
    ctx->r4 = ADD32(ctx->r4, 0X2630);
    func_800BFEF8(rdram, ctx);
        goto after_2;
    // 0x802C91C0: addiu       $a0, $a0, 0x2630
    ctx->r4 = ADD32(ctx->r4, 0X2630);
    after_2:
    // 0x802C91C4: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    // 0x802C91C8: lw          $a3, 0x18($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X18);
L_802C91CC:
    // 0x802C91CC: lui         $a1, 0x802D
    ctx->r5 = S32(0X802D << 16);
    // 0x802C91D0: addiu       $a1, $a1, -0x6BC0
    ctx->r5 = ADD32(ctx->r5, -0X6BC0);
    // 0x802C91D4: lw          $v0, 0x0($a1)
    ctx->r2 = MEM_W(ctx->r5, 0X0);
    // 0x802C91D8: lui         $t1, 0x800E
    ctx->r9 = S32(0X800E << 16);
    // 0x802C91DC: or          $a0, $a3, $zero
    ctx->r4 = ctx->r7 | 0;
    // 0x802C91E0: bltz        $v0, L_802C926C
    if (SIGNED(ctx->r2) < 0) {
        // 0x802C91E4: addiu       $t0, $v0, 0x1
        ctx->r8 = ADD32(ctx->r2, 0X1);
            goto L_802C926C;
    }
    // 0x802C91E4: addiu       $t0, $v0, 0x1
    ctx->r8 = ADD32(ctx->r2, 0X1);
    // 0x802C91E8: sw          $t0, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r8;
    // 0x802C91EC: lw          $t1, -0x54D8($t1)
    ctx->r9 = MEM_W(ctx->r9, -0X54D8);
    // 0x802C91F0: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
    // 0x802C91F4: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x802C91F8: bne         $a2, $t1, L_802C9248
    if (ctx->r6 != ctx->r9) {
        // 0x802C91FC: addiu       $t5, $zero, -0x1
        ctx->r13 = ADD32(0, -0X1);
            goto L_802C9248;
    }
    // 0x802C91FC: addiu       $t5, $zero, -0x1
    ctx->r13 = ADD32(0, -0X1);
    // 0x802C9200: lw          $v0, -0x19E0($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X19E0);
    // 0x802C9204: addiu       $at, $zero, 0xB
    ctx->r1 = ADD32(0, 0XB);
    // 0x802C9208: beql        $v0, $at, L_802C921C
    if (ctx->r2 == ctx->r1) {
        // 0x802C920C: lw          $t2, 0x0($a1)
        ctx->r10 = MEM_W(ctx->r5, 0X0);
            goto L_802C921C;
    }
    goto skip_0;
    // 0x802C920C: lw          $t2, 0x0($a1)
    ctx->r10 = MEM_W(ctx->r5, 0X0);
    skip_0:
    // 0x802C9210: bnel        $v0, $zero, L_802C9234
    if (ctx->r2 != 0) {
        // 0x802C9214: lw          $t3, 0x0($a1)
        ctx->r11 = MEM_W(ctx->r5, 0X0);
            goto L_802C9234;
    }
    goto skip_1;
    // 0x802C9214: lw          $t3, 0x0($a1)
    ctx->r11 = MEM_W(ctx->r5, 0X0);
    skip_1:
    // 0x802C9218: lw          $t2, 0x0($a1)
    ctx->r10 = MEM_W(ctx->r5, 0X0);
L_802C921C:
    // 0x802C921C: slti        $at, $t2, 0xA
    ctx->r1 = SIGNED(ctx->r10) < 0XA ? 1 : 0;
    // 0x802C9220: bne         $at, $zero, L_802C925C
    if (ctx->r1 != 0) {
        // 0x802C9224: nop
    
            goto L_802C925C;
    }
    // 0x802C9224: nop

    // 0x802C9228: b           L_802C925C
    // 0x802C922C: or          $v1, $a2, $zero
    ctx->r3 = ctx->r6 | 0;
        goto L_802C925C;
    // 0x802C922C: or          $v1, $a2, $zero
    ctx->r3 = ctx->r6 | 0;
    // 0x802C9230: lw          $t3, 0x0($a1)
    ctx->r11 = MEM_W(ctx->r5, 0X0);
L_802C9234:
    // 0x802C9234: slti        $at, $t3, 0x32
    ctx->r1 = SIGNED(ctx->r11) < 0X32 ? 1 : 0;
    // 0x802C9238: bne         $at, $zero, L_802C925C
    if (ctx->r1 != 0) {
        // 0x802C923C: nop
    
            goto L_802C925C;
    }
    // 0x802C923C: nop

    // 0x802C9240: b           L_802C925C
    // 0x802C9244: or          $v1, $a2, $zero
    ctx->r3 = ctx->r6 | 0;
        goto L_802C925C;
    // 0x802C9244: or          $v1, $a2, $zero
    ctx->r3 = ctx->r6 | 0;
L_802C9248:
    // 0x802C9248: lw          $t4, 0x0($a1)
    ctx->r12 = MEM_W(ctx->r5, 0X0);
    // 0x802C924C: slti        $at, $t4, 0x2E
    ctx->r1 = SIGNED(ctx->r12) < 0X2E ? 1 : 0;
    // 0x802C9250: bne         $at, $zero, L_802C925C
    if (ctx->r1 != 0) {
        // 0x802C9254: nop
    
            goto L_802C925C;
    }
    // 0x802C9254: nop

    // 0x802C9258: or          $v1, $a2, $zero
    ctx->r3 = ctx->r6 | 0;
L_802C925C:
    // 0x802C925C: beq         $v1, $zero, L_802C926C
    if (ctx->r3 == 0) {
        // 0x802C9260: lui         $at, 0x801D
        ctx->r1 = S32(0X801D << 16);
            goto L_802C926C;
    }
    // 0x802C9260: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C9264: sw          $a2, -0x19B0($at)
    MEM_W(-0X19B0, ctx->r1) = ctx->r6;
    // 0x802C9268: sw          $t5, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r13;
L_802C926C:
    // 0x802C926C: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x802C9270: jal         0x8009328C
    // 0x802C9274: sw          $zero, -0x54D4($at)
    MEM_W(-0X54D4, ctx->r1) = 0;
    func_8009328C(rdram, ctx);
        goto after_3;
    // 0x802C9274: sw          $zero, -0x54D4($at)
    MEM_W(-0X54D4, ctx->r1) = 0;
    after_3:
    // 0x802C9278: lui         $t6, 0xE700
    ctx->r14 = S32(0XE700 << 16);
    // 0x802C927C: sw          $t6, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r14;
    // 0x802C9280: sw          $zero, 0x4($v0)
    MEM_W(0X4, ctx->r2) = 0;
    // 0x802C9284: lui         $t7, 0x800E
    ctx->r15 = S32(0X800E << 16);
    // 0x802C9288: lw          $t7, -0x54D8($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X54D8);
    // 0x802C928C: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    // 0x802C9290: addiu       $v1, $v0, 0x8
    ctx->r3 = ADD32(ctx->r2, 0X8);
    // 0x802C9294: bne         $a2, $t7, L_802C92C0
    if (ctx->r6 != ctx->r15) {
        // 0x802C9298: lui         $t2, 0x800E
        ctx->r10 = S32(0X800E << 16);
            goto L_802C92C0;
    }
    // 0x802C9298: lui         $t2, 0x800E
    ctx->r10 = S32(0X800E << 16);
    // 0x802C929C: addiu       $v1, $v0, 0x8
    ctx->r3 = ADD32(ctx->r2, 0X8);
    // 0x802C92A0: lui         $t8, 0xED02
    ctx->r24 = S32(0XED02 << 16);
    // 0x802C92A4: addiu       $t8, $t8, 0x50
    ctx->r24 = ADD32(ctx->r24, 0X50);
    // 0x802C92A8: lui         $t9, 0x68
    ctx->r25 = S32(0X68 << 16);
    // 0x802C92AC: addiu       $t9, $t9, -0x3C94
    ctx->r25 = ADD32(ctx->r25, -0X3C94);
    { extern uint32_t wr64_experimental_viewport_borders(void); if (wr64_experimental_viewport_borders()) { ctx->r24 = 0xED000000U; ctx->r25 = 0x006A03C0U; } }
    // 0x802C92B0: sw          $t8, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r24;
    // 0x802C92B4: sw          $t9, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r25;
    // 0x802C92B8: b           L_802C92DC
    // 0x802C92BC: addiu       $a3, $v1, 0x8
    ctx->r7 = ADD32(ctx->r3, 0X8);
        goto L_802C92DC;
    // 0x802C92BC: addiu       $a3, $v1, 0x8
    ctx->r7 = ADD32(ctx->r3, 0X8);
L_802C92C0:
    // 0x802C92C0: lui         $t0, 0xED02
    ctx->r8 = S32(0XED02 << 16);
    // 0x802C92C4: addiu       $t0, $t0, 0x30
    ctx->r8 = ADD32(ctx->r8, 0X30);
    // 0x802C92C8: lui         $t1, 0x68
    ctx->r9 = S32(0X68 << 16);
    // 0x802C92CC: addiu       $t1, $t1, -0x3C6C
    ctx->r9 = ADD32(ctx->r9, -0X3C6C);
    // 0x802C92D0: sw          $t0, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r8;
    // 0x802C92D4: sw          $t1, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r9;
    // 0x802C92D8: addiu       $a3, $v1, 0x8
    ctx->r7 = ADD32(ctx->r3, 0X8);
L_802C92DC:
    // 0x802C92DC: lw          $t2, -0x54DC($t2)
    ctx->r10 = MEM_W(ctx->r10, -0X54DC);
    // 0x802C92E0: addiu       $at, $zero, 0x7
    ctx->r1 = ADD32(0, 0X7);
    // 0x802C92E4: lui         $v1, 0x802D
    ctx->r3 = S32(0X802D << 16);
    // 0x802C92E8: bne         $t2, $at, L_802C9354
    if (ctx->r10 != ctx->r1) {
        // 0x802C92EC: lui         $t9, 0x8023
        ctx->r25 = S32(0X8023 << 16);
            goto L_802C9354;
    }
    // 0x802C92EC: lui         $t9, 0x8023
    ctx->r25 = S32(0X8023 << 16);
    // 0x802C92F0: addiu       $v1, $v1, -0x6A90
    ctx->r3 = ADD32(ctx->r3, -0X6A90);
    // 0x802C92F4: lw          $t3, 0x0($v1)
    ctx->r11 = MEM_W(ctx->r3, 0X0);
    // 0x802C92F8: lui         $t5, 0x801D
    ctx->r13 = S32(0X801D << 16);
    // 0x802C92FC: addiu       $at, $zero, 0xB
    ctx->r1 = ADD32(0, 0XB);
    // 0x802C9300: addiu       $t4, $t3, 0x1
    ctx->r12 = ADD32(ctx->r11, 0X1);
    // 0x802C9304: sw          $t4, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r12;
    // 0x802C9308: lw          $t5, -0x19E0($t5)
    ctx->r13 = MEM_W(ctx->r13, -0X19E0);
    // 0x802C930C: addiu       $v0, $zero, 0x320
    ctx->r2 = ADD32(0, 0X320);
    // 0x802C9310: lui         $t6, 0x801D
    ctx->r14 = S32(0X801D << 16);
    // 0x802C9314: bne         $t5, $at, L_802C9324
    if (ctx->r13 != ctx->r1) {
        // 0x802C9318: addiu       $a0, $zero, 0x2
        ctx->r4 = ADD32(0, 0X2);
            goto L_802C9324;
    }
    // 0x802C9318: addiu       $a0, $zero, 0x2
    ctx->r4 = ADD32(0, 0X2);
    // 0x802C931C: b           L_802C9324
    // 0x802C9320: addiu       $v0, $zero, 0x258
    ctx->r2 = ADD32(0, 0X258);
        goto L_802C9324;
    // 0x802C9320: addiu       $v0, $zero, 0x258
    ctx->r2 = ADD32(0, 0X258);
L_802C9324:
    // 0x802C9324: lhu         $t6, -0x19A6($t6)
    ctx->r14 = MEM_HU(ctx->r14, -0X19A6);
    // 0x802C9328: andi        $t7, $t6, 0xB000
    ctx->r15 = ctx->r14 & 0XB000;
    // 0x802C932C: bne         $t7, $zero, L_802C9344
    if (ctx->r15 != 0) {
        // 0x802C9330: nop
    
            goto L_802C9344;
    }
    // 0x802C9330: nop

    // 0x802C9334: lw          $t8, 0x0($v1)
    ctx->r24 = MEM_W(ctx->r3, 0X0);
    // 0x802C9338: slt         $at, $v0, $t8
    ctx->r1 = SIGNED(ctx->r2) < SIGNED(ctx->r24) ? 1 : 0;
    // 0x802C933C: beql        $at, $zero, L_802C9370
    if (ctx->r1 == 0) {
        // 0x802C9340: or          $v0, $a3, $zero
        ctx->r2 = ctx->r7 | 0;
            goto L_802C9370;
    }
    goto skip_2;
    // 0x802C9340: or          $v0, $a3, $zero
    ctx->r2 = ctx->r7 | 0;
    skip_2:
L_802C9344:
    // 0x802C9344: jal         0x802C9380
    // 0x802C9348: sw          $a3, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r7;
    func_i1_802C9380(rdram, ctx);
        goto after_4;
    // 0x802C9348: sw          $a3, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r7;
    after_4:
    // 0x802C934C: b           L_802C936C
    // 0x802C9350: lw          $a3, 0x18($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X18);
        goto L_802C936C;
    // 0x802C9350: lw          $a3, 0x18($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X18);
L_802C9354:
    // 0x802C9354: lh          $t9, -0x75EA($t9)
    ctx->r25 = MEM_H(ctx->r25, -0X75EA);
    // 0x802C9358: bnel        $a2, $t9, L_802C9370
    if (ctx->r6 != ctx->r25) {
        // 0x802C935C: or          $v0, $a3, $zero
        ctx->r2 = ctx->r7 | 0;
            goto L_802C9370;
    }
    goto skip_3;
    // 0x802C935C: or          $v0, $a3, $zero
    ctx->r2 = ctx->r7 | 0;
    skip_3:
    // 0x802C9360: jal         0x801EB180
    // 0x802C9364: sw          $a3, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r7;
    func_801EB180(rdram, ctx);
        goto after_5;
    // 0x802C9364: sw          $a3, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r7;
    after_5:
    // 0x802C9368: lw          $a3, 0x18($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X18);
L_802C936C:
    // 0x802C936C: or          $v0, $a3, $zero
    ctx->r2 = ctx->r7 | 0;
L_802C9370:
    // 0x802C9370: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C9374:
    // 0x802C9374: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x802C9378: jr          $ra
    // 0x802C937C: nop

    return;
    // 0x802C937C: nop

;}
RECOMP_FUNC void func_i1_802C9380(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C9380: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x802C9384: addiu       $v0, $v0, -0x54DC
    ctx->r2 = ADD32(ctx->r2, -0X54DC);
    // 0x802C9388: lw          $t6, 0x0($v0)
    ctx->r14 = MEM_W(ctx->r2, 0X0);
    // 0x802C938C: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C9390: addiu       $t7, $zero, 0x8
    ctx->r15 = ADD32(0, 0X8);
    // 0x802C9394: sw          $t6, -0x19CC($at)
    MEM_W(-0X19CC, ctx->r1) = ctx->r14;
    // 0x802C9398: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C939C: sw          $a0, -0x19D0($at)
    MEM_W(-0X19D0, ctx->r1) = ctx->r4;
    // 0x802C93A0: sw          $t7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r15;
    // 0x802C93A4: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C93A8: sw          $zero, -0x19C8($at)
    MEM_W(-0X19C8, ctx->r1) = 0;
    // 0x802C93AC: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C93B0: addiu       $t8, $zero, 0x1
    ctx->r24 = ADD32(0, 0X1);
    // 0x802C93B4: sw          $t8, -0x19C4($at)
    MEM_W(-0X19C4, ctx->r1) = ctx->r24;
    // 0x802C93B8: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C93BC: sw          $zero, -0x19C0($at)
    MEM_W(-0X19C0, ctx->r1) = 0;
    // 0x802C93C0: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C93C4: sw          $zero, -0x19BC($at)
    MEM_W(-0X19BC, ctx->r1) = 0;
    // 0x802C93C8: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x802C93CC: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x802C93D0: sw          $zero, -0x54E4($at)
    MEM_W(-0X54E4, ctx->r1) = 0;
    // 0x802C93D4: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x802C93D8: lui         $at, 0x800D
    ctx->r1 = S32(0X800D << 16);
    // 0x802C93DC: addiu       $t9, $zero, 0x3
    ctx->r25 = ADD32(0, 0X3);
    // 0x802C93E0: sw          $t9, 0x461C($at)
    MEM_W(0X461C, ctx->r1) = ctx->r25;
    // 0x802C93E4: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    // 0x802C93E8: addiu       $a1, $zero, 0x4
    ctx->r5 = ADD32(0, 0X4);
    // 0x802C93EC: jal         0x801E6FB0
    // 0x802C93F0: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    FadeTransition_SetProps(rdram, ctx);
        goto after_0;
    // 0x802C93F0: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    after_0:
    // 0x802C93F4: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    // 0x802C93F8: jal         0x801E6A4C
    // 0x802C93FC: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_801E6A4C(rdram, ctx);
        goto after_1;
    // 0x802C93FC: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_1:
    // 0x802C9400: jal         0x800BFD34
    // 0x802C9404: nop

    func_800BFD34(rdram, ctx);
        goto after_2;
    // 0x802C9404: nop

    after_2:
    // 0x802C9408: jal         0x800BFD68
    // 0x802C940C: nop

    func_800BFD68(rdram, ctx);
        goto after_3;
    // 0x802C940C: nop

    after_3:
    // 0x802C9410: lui         $t0, 0x801D
    ctx->r8 = S32(0X801D << 16);
    // 0x802C9414: lw          $t0, -0x19D0($t0)
    ctx->r8 = MEM_W(ctx->r8, -0X19D0);
    // 0x802C9418: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x802C941C: bnel        $t0, $at, L_802C9430
    if (ctx->r8 != ctx->r1) {
        // 0x802C9420: lw          $ra, 0x14($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X14);
            goto L_802C9430;
    }
    goto skip_0;
    // 0x802C9420: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    skip_0:
    // 0x802C9424: jal         0x800C1F60
    // 0x802C9428: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    func_800C1F60(rdram, ctx);
        goto after_4;
    // 0x802C9428: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    after_4:
    // 0x802C942C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C9430:
    // 0x802C9430: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x802C9434: jr          $ra
    // 0x802C9438: nop

    return;
    // 0x802C9438: nop

    // 0x802C943C: nop

;}
RECOMP_FUNC void func_i2_802C5800(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C5800: addiu       $sp, $sp, -0x1F8
    ctx->r29 = ADD32(ctx->r29, -0X1F8);
    // 0x802C5804: lui         $t6, 0x801D
    ctx->r14 = S32(0X801D << 16);
    // 0x802C5808: lw          $t6, -0x19C4($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X19C4);
    // 0x802C580C: sw          $ra, 0x84($sp)
    MEM_W(0X84, ctx->r29) = ctx->r31;
    // 0x802C5810: sw          $fp, 0x80($sp)
    MEM_W(0X80, ctx->r29) = ctx->r30;
    // 0x802C5814: sw          $s7, 0x7C($sp)
    MEM_W(0X7C, ctx->r29) = ctx->r23;
    // 0x802C5818: sw          $s6, 0x78($sp)
    MEM_W(0X78, ctx->r29) = ctx->r22;
    // 0x802C581C: sw          $s5, 0x74($sp)
    MEM_W(0X74, ctx->r29) = ctx->r21;
    // 0x802C5820: sw          $s4, 0x70($sp)
    MEM_W(0X70, ctx->r29) = ctx->r20;
    // 0x802C5824: sw          $s3, 0x6C($sp)
    MEM_W(0X6C, ctx->r29) = ctx->r19;
    // 0x802C5828: sw          $s2, 0x68($sp)
    MEM_W(0X68, ctx->r29) = ctx->r18;
    // 0x802C582C: sw          $s1, 0x64($sp)
    MEM_W(0X64, ctx->r29) = ctx->r17;
    // 0x802C5830: sw          $s0, 0x60($sp)
    MEM_W(0X60, ctx->r29) = ctx->r16;
    // 0x802C5834: sdc1        $f28, 0x58($sp)
    CHECK_FR(ctx, 28);
    SD(ctx->f28.u64, 0X58, ctx->r29);
    // 0x802C5838: sdc1        $f26, 0x50($sp)
    CHECK_FR(ctx, 26);
    SD(ctx->f26.u64, 0X50, ctx->r29);
    // 0x802C583C: sdc1        $f24, 0x48($sp)
    CHECK_FR(ctx, 24);
    SD(ctx->f24.u64, 0X48, ctx->r29);
    // 0x802C5840: sdc1        $f22, 0x40($sp)
    CHECK_FR(ctx, 22);
    SD(ctx->f22.u64, 0X40, ctx->r29);
    // 0x802C5844: beq         $t6, $zero, L_802C5868
    if (ctx->r14 == 0) {
        // 0x802C5848: sdc1        $f20, 0x38($sp)
        CHECK_FR(ctx, 20);
    SD(ctx->f20.u64, 0X38, ctx->r29);
            goto L_802C5868;
    }
    // 0x802C5848: sdc1        $f20, 0x38($sp)
    CHECK_FR(ctx, 20);
    SD(ctx->f20.u64, 0X38, ctx->r29);
    // 0x802C584C: lui         $t7, 0x800E
    ctx->r15 = S32(0X800E << 16);
    // 0x802C5850: lw          $t7, -0x54DC($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X54DC);
    // 0x802C5854: addiu       $at, $zero, 0xA
    ctx->r1 = ADD32(0, 0XA);
    // 0x802C5858: bnel        $t7, $at, L_802C586C
    if (ctx->r15 != ctx->r1) {
        // 0x802C585C: lui         $at, 0x3F80
        ctx->r1 = S32(0X3F80 << 16);
            goto L_802C586C;
    }
    goto skip_0;
    // 0x802C585C: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    skip_0:
    // 0x802C5860: jal         0x802C5AE4
    // 0x802C5864: nop

    func_i2_802C5AE4(rdram, ctx);
        goto after_0;
    // 0x802C5864: nop

    after_0:
L_802C5868:
    // 0x802C5868: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
L_802C586C:
    // 0x802C586C: mtc1        $at, $f28
    ctx->f28.u32l = ctx->r1;
    // 0x802C5870: lui         $at, 0x4180
    ctx->r1 = S32(0X4180 << 16);
    // 0x802C5874: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x802C5878: mtc1        $zero, $f26
    ctx->f26.u32l = 0;
    // 0x802C587C: lui         $at, 0x4580
    ctx->r1 = S32(0X4580 << 16);
    // 0x802C5880: lui         $a0, 0x801D
    ctx->r4 = S32(0X801D << 16);
    // 0x802C5884: lw          $a0, -0x1A08($a0)
    ctx->r4 = MEM_W(ctx->r4, -0X1A08);
    // 0x802C5888: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x802C588C: lui         $a1, 0x802D
    ctx->r5 = S32(0X802D << 16);
    // 0x802C5890: mfc1        $a3, $f28
    ctx->r7 = (int32_t)ctx->f28.u32l;
    // 0x802C5894: addiu       $a1, $a1, -0x73B0
    ctx->r5 = ADD32(ctx->r5, -0X73B0);
    // 0x802C5898: lui         $a2, 0x4204
    ctx->r6 = S32(0X4204 << 16);
    // 0x802C589C: swc1        $f4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f4.u32l;
    // 0x802C58A0: swc1        $f26, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->f26.u32l;
    // 0x802C58A4: swc1        $f26, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->f26.u32l;
    // 0x802C58A8: addiu       $a0, $a0, 0xA40
    ctx->r4 = ADD32(ctx->r4, 0XA40);
    // 0x802C58AC: jal         0x800481E0
    // 0x802C58B0: swc1        $f6, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->f6.u32l;
    func_800481E0(rdram, ctx);
        goto after_1;
    // 0x802C58B0: swc1        $f6, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->f6.u32l;
    after_1:
    // 0x802C58B4: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C58B8: lwc1        $f8, -0x7418($at)
    ctx->f8.u32l = MEM_W(ctx->r1, -0X7418);
    // 0x802C58BC: mfc1        $a1, $f26
    ctx->r5 = (int32_t)ctx->f26.u32l;
    // 0x802C58C0: mfc1        $a2, $f26
    ctx->r6 = (int32_t)ctx->f26.u32l;
    // 0x802C58C4: mfc1        $a3, $f28
    ctx->r7 = (int32_t)ctx->f28.u32l;
    // 0x802C58C8: addiu       $a0, $sp, 0xE0
    ctx->r4 = ADD32(ctx->r29, 0XE0);
    // 0x802C58CC: swc1        $f26, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f26.u32l;
    // 0x802C58D0: swc1        $f28, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->f28.u32l;
    // 0x802C58D4: swc1        $f26, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->f26.u32l;
    // 0x802C58D8: swc1        $f26, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->f26.u32l;
    // 0x802C58DC: swc1        $f26, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->f26.u32l;
    // 0x802C58E0: swc1        $f26, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->f26.u32l;
    // 0x802C58E4: jal         0x80048A88
    // 0x802C58E8: swc1        $f8, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->f8.u32l;
    func_80048A88(rdram, ctx);
        goto after_2;
    // 0x802C58E8: swc1        $f8, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->f8.u32l;
    after_2:
    // 0x802C58EC: lui         $at, 0x43FA
    ctx->r1 = S32(0X43FA << 16);
    // 0x802C58F0: lui         $s7, 0x801D
    ctx->r23 = S32(0X801D << 16);
    // 0x802C58F4: lui         $s2, 0x802D
    ctx->r18 = S32(0X802D << 16);
    // 0x802C58F8: lui         $s0, 0x8015
    ctx->r16 = S32(0X8015 << 16);
    // 0x802C58FC: mtc1        $at, $f20
    ctx->f20.u32l = ctx->r1;
    // 0x802C5900: addiu       $s0, $s0, 0x4350
    ctx->r16 = ADD32(ctx->r16, 0X4350);
    // 0x802C5904: addiu       $s2, $s2, -0x73A0
    ctx->r18 = ADD32(ctx->r18, -0X73A0);
    // 0x802C5908: addiu       $s7, $s7, -0x19F8
    ctx->r23 = ADD32(ctx->r23, -0X19F8);
    // 0x802C590C: or          $s1, $zero, $zero
    ctx->r17 = 0 | 0;
    // 0x802C5910: or          $s3, $zero, $zero
    ctx->r19 = 0 | 0;
    // 0x802C5914: lwc1        $f24, 0x1E4($sp)
    ctx->f24.u32l = MEM_W(ctx->r29, 0X1E4);
    // 0x802C5918: lwc1        $f22, 0x1E8($sp)
    ctx->f22.u32l = MEM_W(ctx->r29, 0X1E8);
    // 0x802C591C: addiu       $fp, $sp, 0xA0
    ctx->r30 = ADD32(ctx->r29, 0XA0);
    // 0x802C5920: addiu       $s6, $sp, 0x124
    ctx->r22 = ADD32(ctx->r29, 0X124);
    // 0x802C5924: addiu       $s5, $sp, 0x1A4
    ctx->r21 = ADD32(ctx->r29, 0X1A4);
    // 0x802C5928: addiu       $s4, $sp, 0x164
    ctx->r20 = ADD32(ctx->r29, 0X164);
L_802C592C:
    // 0x802C592C: lh          $a3, 0x4($s7)
    ctx->r7 = MEM_H(ctx->r23, 0X4);
    // 0x802C5930: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    // 0x802C5934: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C5938: blez        $a3, L_802C59E0
    if (SIGNED(ctx->r7) <= 0) {
        // 0x802C593C: lui         $a2, 0x800E
        ctx->r6 = S32(0X800E << 16);
            goto L_802C59E0;
    }
    // 0x802C593C: lui         $a2, 0x800E
    ctx->r6 = S32(0X800E << 16);
    // 0x802C5940: addiu       $a2, $a2, -0x5640
    ctx->r6 = ADD32(ctx->r6, -0X5640);
L_802C5944:
    // 0x802C5944: lw          $t8, 0x0($a2)
    ctx->r24 = MEM_W(ctx->r6, 0X0);
    // 0x802C5948: addiu       $a0, $a0, 0x1
    ctx->r4 = ADD32(ctx->r4, 0X1);
    // 0x802C594C: addiu       $a2, $a2, 0x4
    ctx->r6 = ADD32(ctx->r6, 0X4);
    // 0x802C5950: bne         $s1, $t8, L_802C595C
    if (ctx->r17 != ctx->r24) {
        // 0x802C5954: or          $v1, $zero, $zero
        ctx->r3 = 0 | 0;
            goto L_802C595C;
    }
    // 0x802C5954: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
    // 0x802C5958: addiu       $v1, $zero, 0x1
    ctx->r3 = ADD32(0, 0X1);
L_802C595C:
    // 0x802C595C: beq         $v1, $zero, L_802C59B8
    if (ctx->r3 == 0) {
        // 0x802C5960: slt         $at, $a0, $a3
        ctx->r1 = SIGNED(ctx->r4) < SIGNED(ctx->r7) ? 1 : 0;
            goto L_802C59B8;
    }
    // 0x802C5960: slt         $at, $a0, $a3
    ctx->r1 = SIGNED(ctx->r4) < SIGNED(ctx->r7) ? 1 : 0;
    // 0x802C5964: addu        $t9, $s2, $a1
    ctx->r25 = ADD32(ctx->r18, ctx->r5);
    // 0x802C5968: lw          $v0, 0x0($t9)
    ctx->r2 = MEM_W(ctx->r25, 0X0);
    // 0x802C596C: bgez        $v0, L_802C5980
    if (SIGNED(ctx->r2) >= 0) {
        // 0x802C5970: andi        $t0, $v0, 0xFFF
        ctx->r8 = ctx->r2 & 0XFFF;
            goto L_802C5980;
    }
    // 0x802C5970: andi        $t0, $v0, 0xFFF
    ctx->r8 = ctx->r2 & 0XFFF;
    // 0x802C5974: beq         $t0, $zero, L_802C5980
    if (ctx->r8 == 0) {
        // 0x802C5978: nop
    
            goto L_802C5980;
    }
    // 0x802C5978: nop

    // 0x802C597C: addiu       $t0, $t0, -0x1000
    ctx->r8 = ADD32(ctx->r8, -0X1000);
L_802C5980:
    // 0x802C5980: addiu       $t1, $t0, 0x400
    ctx->r9 = ADD32(ctx->r8, 0X400);
    // 0x802C5984: andi        $t2, $t1, 0xFFF
    ctx->r10 = ctx->r9 & 0XFFF;
    // 0x802C5988: sll         $t3, $t2, 2
    ctx->r11 = S32(ctx->r10 << 2);
    // 0x802C598C: addu        $t4, $s0, $t3
    ctx->r12 = ADD32(ctx->r16, ctx->r11);
    // 0x802C5990: lwc1        $f10, 0x0($t4)
    ctx->f10.u32l = MEM_W(ctx->r12, 0X0);
    // 0x802C5994: andi        $t5, $t0, 0xFFF
    ctx->r13 = ctx->r8 & 0XFFF;
    // 0x802C5998: sll         $t6, $t5, 2
    ctx->r14 = S32(ctx->r13 << 2);
    // 0x802C599C: addu        $t7, $s0, $t6
    ctx->r15 = ADD32(ctx->r16, ctx->r14);
    // 0x802C59A0: lwc1        $f16, 0x0($t7)
    ctx->f16.u32l = MEM_W(ctx->r15, 0X0);
    // 0x802C59A4: mul.s       $f22, $f10, $f20
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f22.fl = MUL_S(ctx->f10.fl, ctx->f20.fl);
    // 0x802C59A8: nop

    // 0x802C59AC: mul.s       $f24, $f16, $f20
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f24.fl = MUL_S(ctx->f16.fl, ctx->f20.fl);
    // 0x802C59B0: b           L_802C59D0
    // 0x802C59B4: nop

        goto L_802C59D0;
    // 0x802C59B4: nop

L_802C59B8:
    // 0x802C59B8: lwc1        $f18, 0x1800($s0)
    ctx->f18.u32l = MEM_W(ctx->r16, 0X1800);
    // 0x802C59BC: lwc1        $f4, 0x800($s0)
    ctx->f4.u32l = MEM_W(ctx->r16, 0X800);
    // 0x802C59C0: mul.s       $f22, $f18, $f20
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f22.fl = MUL_S(ctx->f18.fl, ctx->f20.fl);
    // 0x802C59C4: nop

    // 0x802C59C8: mul.s       $f24, $f4, $f20
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f24.fl = MUL_S(ctx->f4.fl, ctx->f20.fl);
    // 0x802C59CC: nop

L_802C59D0:
    // 0x802C59D0: bnel        $v1, $zero, L_802C59E4
    if (ctx->r3 != 0) {
        // 0x802C59D4: mfc1        $a2, $f22
        ctx->r6 = (int32_t)ctx->f22.u32l;
            goto L_802C59E4;
    }
    goto skip_1;
    // 0x802C59D4: mfc1        $a2, $f22
    ctx->r6 = (int32_t)ctx->f22.u32l;
    skip_1:
    // 0x802C59D8: bne         $at, $zero, L_802C5944
    if (ctx->r1 != 0) {
        // 0x802C59DC: addiu       $a1, $a1, 0x4
        ctx->r5 = ADD32(ctx->r5, 0X4);
            goto L_802C5944;
    }
    // 0x802C59DC: addiu       $a1, $a1, 0x4
    ctx->r5 = ADD32(ctx->r5, 0X4);
L_802C59E0:
    // 0x802C59E0: mfc1        $a2, $f22
    ctx->r6 = (int32_t)ctx->f22.u32l;
L_802C59E4:
    // 0x802C59E4: mfc1        $a3, $f20
    ctx->r7 = (int32_t)ctx->f20.u32l;
    // 0x802C59E8: or          $a0, $fp, $zero
    ctx->r4 = ctx->r30 | 0;
    // 0x802C59EC: or          $a1, $s4, $zero
    ctx->r5 = ctx->r20 | 0;
    // 0x802C59F0: swc1        $f24, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f24.u32l;
    // 0x802C59F4: swc1        $f26, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->f26.u32l;
    // 0x802C59F8: swc1        $f26, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->f26.u32l;
    // 0x802C59FC: swc1        $f26, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->f26.u32l;
    // 0x802C5A00: swc1        $f26, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->f26.u32l;
    // 0x802C5A04: swc1        $f28, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->f28.u32l;
    // 0x802C5A08: jal         0x800484C8
    // 0x802C5A0C: swc1        $f26, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->f26.u32l;
    func_800484C8(rdram, ctx);
        goto after_3;
    // 0x802C5A0C: swc1        $f26, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->f26.u32l;
    after_3:
    // 0x802C5A10: addiu       $a0, $sp, 0xE0
    ctx->r4 = ADD32(ctx->r29, 0XE0);
    // 0x802C5A14: jal         0x80047E78
    // 0x802C5A18: or          $a1, $s5, $zero
    ctx->r5 = ctx->r21 | 0;
    SysUtils_MtxToMtxF(rdram, ctx);
        goto after_4;
    // 0x802C5A18: or          $a1, $s5, $zero
    ctx->r5 = ctx->r21 | 0;
    after_4:
    // 0x802C5A1C: or          $a0, $s4, $zero
    ctx->r4 = ctx->r20 | 0;
    // 0x802C5A20: or          $a1, $s5, $zero
    ctx->r5 = ctx->r21 | 0;
    // 0x802C5A24: jal         0x80049EB8
    // 0x802C5A28: or          $a2, $s6, $zero
    ctx->r6 = ctx->r22 | 0;
    SysUtils_MatrixAffineMultiply(rdram, ctx);
        goto after_5;
    // 0x802C5A28: or          $a2, $s6, $zero
    ctx->r6 = ctx->r22 | 0;
    after_5:
    // 0x802C5A2C: lui         $t8, 0x801D
    ctx->r24 = S32(0X801D << 16);
    // 0x802C5A30: lw          $t8, -0x1A08($t8)
    ctx->r24 = MEM_W(ctx->r24, -0X1A08);
    // 0x802C5A34: or          $a0, $s6, $zero
    ctx->r4 = ctx->r22 | 0;
    // 0x802C5A38: addu        $a1, $t8, $s3
    ctx->r5 = ADD32(ctx->r24, ctx->r19);
    // 0x802C5A3C: jal         0x80047EE0
    // 0x802C5A40: addiu       $a1, $a1, 0xA80
    ctx->r5 = ADD32(ctx->r5, 0XA80);
    SysUtils_MtxFToMtx(rdram, ctx);
        goto after_6;
    // 0x802C5A40: addiu       $a1, $a1, 0xA80
    ctx->r5 = ADD32(ctx->r5, 0XA80);
    after_6:
    // 0x802C5A44: addiu       $s1, $s1, 0x1
    ctx->r17 = ADD32(ctx->r17, 0X1);
    // 0x802C5A48: slti        $at, $s1, 0x4
    ctx->r1 = SIGNED(ctx->r17) < 0X4 ? 1 : 0;
    // 0x802C5A4C: bne         $at, $zero, L_802C592C
    if (ctx->r1 != 0) {
        // 0x802C5A50: addiu       $s3, $s3, 0x40
        ctx->r19 = ADD32(ctx->r19, 0X40);
            goto L_802C592C;
    }
    // 0x802C5A50: addiu       $s3, $s3, 0x40
    ctx->r19 = ADD32(ctx->r19, 0X40);
    // 0x802C5A54: lh          $a3, 0x4($s7)
    ctx->r7 = MEM_H(ctx->r23, 0X4);
    // 0x802C5A58: swc1        $f24, 0x1E4($sp)
    MEM_W(0X1E4, ctx->r29) = ctx->f24.u32l;
    // 0x802C5A5C: swc1        $f22, 0x1E8($sp)
    MEM_W(0X1E8, ctx->r29) = ctx->f22.u32l;
    // 0x802C5A60: blez        $a3, L_802C5AA0
    if (SIGNED(ctx->r7) <= 0) {
        // 0x802C5A64: lui         $t9, 0x802D
        ctx->r25 = S32(0X802D << 16);
            goto L_802C5AA0;
    }
    // 0x802C5A64: lui         $t9, 0x802D
    ctx->r25 = S32(0X802D << 16);
    // 0x802C5A68: addiu       $v0, $t9, -0x73A0
    ctx->r2 = ADD32(ctx->r25, -0X73A0);
    // 0x802C5A6C: sll         $t0, $a3, 2
    ctx->r8 = S32(ctx->r7 << 2);
    // 0x802C5A70: addu        $a0, $t0, $v0
    ctx->r4 = ADD32(ctx->r8, ctx->r2);
    // 0x802C5A74: lw          $t1, 0x0($v0)
    ctx->r9 = MEM_W(ctx->r2, 0X0);
L_802C5A78:
    // 0x802C5A78: addiu       $t2, $t1, 0x30
    ctx->r10 = ADD32(ctx->r9, 0X30);
    // 0x802C5A7C: slti        $at, $t2, 0x1000
    ctx->r1 = SIGNED(ctx->r10) < 0X1000 ? 1 : 0;
    // 0x802C5A80: bne         $at, $zero, L_802C5A90
    if (ctx->r1 != 0) {
        // 0x802C5A84: sw          $t2, 0x0($v0)
        MEM_W(0X0, ctx->r2) = ctx->r10;
            goto L_802C5A90;
    }
    // 0x802C5A84: sw          $t2, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r10;
    // 0x802C5A88: addiu       $t3, $t2, -0x1000
    ctx->r11 = ADD32(ctx->r10, -0X1000);
    // 0x802C5A8C: sw          $t3, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r11;
L_802C5A90:
    // 0x802C5A90: addiu       $v0, $v0, 0x4
    ctx->r2 = ADD32(ctx->r2, 0X4);
    // 0x802C5A94: sltu        $at, $v0, $a0
    ctx->r1 = ctx->r2 < ctx->r4 ? 1 : 0;
    // 0x802C5A98: bnel        $at, $zero, L_802C5A78
    if (ctx->r1 != 0) {
        // 0x802C5A9C: lw          $t1, 0x0($v0)
        ctx->r9 = MEM_W(ctx->r2, 0X0);
            goto L_802C5A78;
    }
    goto skip_2;
    // 0x802C5A9C: lw          $t1, 0x0($v0)
    ctx->r9 = MEM_W(ctx->r2, 0X0);
    skip_2:
L_802C5AA0:
    // 0x802C5AA0: lw          $ra, 0x84($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X84);
    // 0x802C5AA4: ldc1        $f20, 0x38($sp)
    CHECK_FR(ctx, 20);
    ctx->f20.u64 = LD(ctx->r29, 0X38);
    // 0x802C5AA8: ldc1        $f22, 0x40($sp)
    CHECK_FR(ctx, 22);
    ctx->f22.u64 = LD(ctx->r29, 0X40);
    // 0x802C5AAC: ldc1        $f24, 0x48($sp)
    CHECK_FR(ctx, 24);
    ctx->f24.u64 = LD(ctx->r29, 0X48);
    // 0x802C5AB0: ldc1        $f26, 0x50($sp)
    CHECK_FR(ctx, 26);
    ctx->f26.u64 = LD(ctx->r29, 0X50);
    // 0x802C5AB4: ldc1        $f28, 0x58($sp)
    CHECK_FR(ctx, 28);
    ctx->f28.u64 = LD(ctx->r29, 0X58);
    // 0x802C5AB8: lw          $s0, 0x60($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X60);
    // 0x802C5ABC: lw          $s1, 0x64($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X64);
    // 0x802C5AC0: lw          $s2, 0x68($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X68);
    // 0x802C5AC4: lw          $s3, 0x6C($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X6C);
    // 0x802C5AC8: lw          $s4, 0x70($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X70);
    // 0x802C5ACC: lw          $s5, 0x74($sp)
    ctx->r21 = MEM_W(ctx->r29, 0X74);
    // 0x802C5AD0: lw          $s6, 0x78($sp)
    ctx->r22 = MEM_W(ctx->r29, 0X78);
    // 0x802C5AD4: lw          $s7, 0x7C($sp)
    ctx->r23 = MEM_W(ctx->r29, 0X7C);
    // 0x802C5AD8: lw          $fp, 0x80($sp)
    ctx->r30 = MEM_W(ctx->r29, 0X80);
    // 0x802C5ADC: jr          $ra
    // 0x802C5AE0: addiu       $sp, $sp, 0x1F8
    ctx->r29 = ADD32(ctx->r29, 0X1F8);
    return;
    // 0x802C5AE0: addiu       $sp, $sp, 0x1F8
    ctx->r29 = ADD32(ctx->r29, 0X1F8);
;}
RECOMP_FUNC void func_i2_802C5AE4(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C5AE4: lui         $v1, 0x802D
    ctx->r3 = S32(0X802D << 16);
    // 0x802C5AE8: lui         $a0, 0x802D
    ctx->r4 = S32(0X802D << 16);
    // 0x802C5AEC: lui         $a1, 0x801D
    ctx->r5 = S32(0X801D << 16);
    // 0x802C5AF0: addiu       $a1, $a1, -0x190C
    ctx->r5 = ADD32(ctx->r5, -0X190C);
    // 0x802C5AF4: addiu       $a0, $a0, -0x73A0
    ctx->r4 = ADD32(ctx->r4, -0X73A0);
    // 0x802C5AF8: addiu       $v1, $v1, -0x73A8
    ctx->r3 = ADD32(ctx->r3, -0X73A8);
    // 0x802C5AFC: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_802C5B00:
    // 0x802C5B00: sh          $v0, 0x0($a1)
    MEM_H(0X0, ctx->r5) = ctx->r2;
    // 0x802C5B04: addiu       $v0, $v0, 0x1
    ctx->r2 = ADD32(ctx->r2, 0X1);
    // 0x802C5B08: slti        $at, $v0, 0x2
    ctx->r1 = SIGNED(ctx->r2) < 0X2 ? 1 : 0;
    // 0x802C5B0C: addiu       $v1, $v1, 0x4
    ctx->r3 = ADD32(ctx->r3, 0X4);
    // 0x802C5B10: addiu       $a0, $a0, 0x4
    ctx->r4 = ADD32(ctx->r4, 0X4);
    // 0x802C5B14: addiu       $a1, $a1, 0x2
    ctx->r5 = ADD32(ctx->r5, 0X2);
    // 0x802C5B18: sw          $zero, -0x4($v1)
    MEM_W(-0X4, ctx->r3) = 0;
    // 0x802C5B1C: bne         $at, $zero, L_802C5B00
    if (ctx->r1 != 0) {
        // 0x802C5B20: sw          $zero, -0x4($a0)
        MEM_W(-0X4, ctx->r4) = 0;
            goto L_802C5B00;
    }
    // 0x802C5B20: sw          $zero, -0x4($a0)
    MEM_W(-0X4, ctx->r4) = 0;
    // 0x802C5B24: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C5B28: sh          $zero, -0x7390($at)
    MEM_H(-0X7390, ctx->r1) = 0;
    // 0x802C5B2C: sh          $zero, -0x738E($at)
    MEM_H(-0X738E, ctx->r1) = 0;
    // 0x802C5B30: sh          $zero, -0x738C($at)
    MEM_H(-0X738C, ctx->r1) = 0;
    // 0x802C5B34: sh          $zero, -0x738A($at)
    MEM_H(-0X738A, ctx->r1) = 0;
    // 0x802C5B38: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C5B3C: sh          $zero, -0x7398($at)
    MEM_H(-0X7398, ctx->r1) = 0;
    // 0x802C5B40: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C5B44: jr          $ra
    // 0x802C5B48: sh          $zero, -0x7396($at)
    MEM_H(-0X7396, ctx->r1) = 0;
    return;
    // 0x802C5B48: sh          $zero, -0x7396($at)
    MEM_H(-0X7396, ctx->r1) = 0;
;}
RECOMP_FUNC void func_i2_802C5B4C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C5B4C: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x802C5B50: addiu       $v0, $v0, -0x19C4
    ctx->r2 = ADD32(ctx->r2, -0X19C4);
    // 0x802C5B54: lw          $t6, 0x0($v0)
    ctx->r14 = MEM_W(ctx->r2, 0X0);
    // 0x802C5B58: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x802C5B5C: sw          $s0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r16;
    // 0x802C5B60: or          $s0, $a0, $zero
    ctx->r16 = ctx->r4 | 0;
    // 0x802C5B64: beq         $t6, $zero, L_802C5B94
    if (ctx->r14 == 0) {
        // 0x802C5B68: sw          $ra, 0x1C($sp)
        MEM_W(0X1C, ctx->r29) = ctx->r31;
            goto L_802C5B94;
    }
    // 0x802C5B68: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x802C5B6C: sw          $zero, 0x0($v0)
    MEM_W(0X0, ctx->r2) = 0;
    // 0x802C5B70: lui         $t7, 0x800E
    ctx->r15 = S32(0X800E << 16);
    // 0x802C5B74: lw          $t7, -0x54DC($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X54DC);
    // 0x802C5B78: addiu       $at, $zero, 0xA
    ctx->r1 = ADD32(0, 0XA);
    // 0x802C5B7C: bne         $t7, $at, L_802C5B94
    if (ctx->r15 != ctx->r1) {
        // 0x802C5B80: nop
    
            goto L_802C5B94;
    }
    // 0x802C5B80: nop

    // 0x802C5B84: jal         0x80093C44
    // 0x802C5B88: nop

    func_80093C44(rdram, ctx);
        goto after_0;
    // 0x802C5B88: nop

    after_0:
    // 0x802C5B8C: b           L_802C5E18
    // 0x802C5B90: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
        goto L_802C5E18;
    // 0x802C5B90: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
L_802C5B94:
    { extern void wr64_watercraft_preview_prepare(uint8_t*, uint32_t); wr64_watercraft_preview_prepare(rdram, (uint32_t)ctx->r16); }
    // 0x802C5B94: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x802C5B98: sw          $zero, -0x54D4($at)
    MEM_W(-0X54D4, ctx->r1) = 0;
    // 0x802C5B9C: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
    // 0x802C5BA0: addiu       $v1, $s0, 0x8
    ctx->r3 = ADD32(ctx->r16, 0X8);
    // 0x802C5BA4: lui         $t8, 0xE700
    ctx->r24 = S32(0XE700 << 16);
    // 0x802C5BA8: sw          $t8, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r24;
    // 0x802C5BAC: sw          $zero, 0x4($v0)
    MEM_W(0X4, ctx->r2) = 0;
    // 0x802C5BB0: lui         $t9, 0xED02
    ctx->r25 = S32(0XED02 << 16);
    // 0x802C5BB4: addiu       $t9, $t9, 0x50
    ctx->r25 = ADD32(ctx->r25, 0X50);
    // 0x802C5BB8: lui         $t0, 0x68
    ctx->r8 = S32(0X68 << 16);
    // 0x802C5BBC: addiu       $t0, $t0, -0x3C94
    ctx->r8 = ADD32(ctx->r8, -0X3C94);
    // 0x802C5BC0: addiu       $a1, $v1, 0x8
    ctx->r5 = ADD32(ctx->r3, 0X8);
    // 0x802C5BC4: lui         $t2, 0x107
    ctx->r10 = S32(0X107 << 16);
    { extern uint32_t wr64_experimental_viewport_borders(void); if (wr64_experimental_viewport_borders()) { ctx->r25 = 0xED000000U; ctx->r8 = 0x006A03C0U; } }
    // 0x802C5BC8: sw          $t9, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r25;
    // 0x802C5BCC: sw          $t0, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r8;
    // 0x802C5BD0: addiu       $t2, $t2, -0x510
    ctx->r10 = ADD32(ctx->r10, -0X510);
    // 0x802C5BD4: lui         $t1, 0x600
    ctx->r9 = S32(0X600 << 16);
    // 0x802C5BD8: sw          $t1, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r9;
    // 0x802C5BDC: sw          $t2, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r10;
    // 0x802C5BE0: jal         0x802C88DC
    // 0x802C5BE4: addiu       $a0, $a1, 0x8
    ctx->r4 = ADD32(ctx->r5, 0X8);
    func_i2_802C88DC(rdram, ctx);
        goto after_1;
    // 0x802C5BE4: addiu       $a0, $a1, 0x8
    ctx->r4 = ADD32(ctx->r5, 0X8);
    after_1:
    // 0x802C5BE8: lui         $t3, 0x103
    ctx->r11 = S32(0X103 << 16);
    // 0x802C5BEC: lui         $t4, 0x700
    ctx->r12 = S32(0X700 << 16);
    // 0x802C5BF0: lui         $t5, 0x102
    ctx->r13 = S32(0X102 << 16);
    // 0x802C5BF4: lui         $t6, 0x200
    ctx->r14 = S32(0X200 << 16);
    // 0x802C5BF8: lui         $t8, 0x107
    ctx->r24 = S32(0X107 << 16);
    // 0x802C5BFC: addiu       $t4, $t4, 0x0
    ctx->r12 = ADD32(ctx->r12, 0X0);
    // 0x802C5C00: ori         $t3, $t3, 0x40
    ctx->r11 = ctx->r11 | 0X40;
    // 0x802C5C04: addiu       $t6, $t6, 0xA40
    ctx->r14 = ADD32(ctx->r14, 0XA40);
    // 0x802C5C08: ori         $t5, $t5, 0x40
    ctx->r13 = ctx->r13 | 0X40;
    // 0x802C5C0C: addiu       $t8, $t8, -0x7F8
    ctx->r24 = ADD32(ctx->r24, -0X7F8);
    // 0x802C5C10: lui         $t7, 0x600
    ctx->r15 = S32(0X600 << 16);
    // 0x802C5C14: sw          $t3, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r11;
    // 0x802C5C18: sw          $t4, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r12;
    // 0x802C5C1C: sw          $t5, 0x8($v0)
    MEM_W(0X8, ctx->r2) = ctx->r13;
    // 0x802C5C20: sw          $t6, 0xC($v0)
    MEM_W(0XC, ctx->r2) = ctx->r14;
    // 0x802C5C24: sw          $t7, 0x10($v0)
    MEM_W(0X10, ctx->r2) = ctx->r15;
    // 0x802C5C28: sw          $t8, 0x14($v0)
    MEM_W(0X14, ctx->r2) = ctx->r24;
    // 0x802C5C2C: lui         $t9, 0x801D
    ctx->r25 = S32(0X801D << 16);
    // 0x802C5C30: lh          $t9, -0x19F4($t9)
    ctx->r25 = MEM_H(ctx->r25, -0X19F4);
    // 0x802C5C34: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x802C5C38: addiu       $s0, $v0, 0x18
    ctx->r16 = ADD32(ctx->r2, 0X18);
    // 0x802C5C3C: bne         $t9, $at, L_802C5C54
    if (ctx->r25 != ctx->r1) {
        // 0x802C5C40: lui         $t0, 0x802D
        ctx->r8 = S32(0X802D << 16);
            goto L_802C5C54;
    }
    // 0x802C5C40: lui         $t0, 0x802D
    ctx->r8 = S32(0X802D << 16);
    // 0x802C5C44: jal         0x8009328C
    // 0x802C5C48: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    func_8009328C(rdram, ctx);
        goto after_2;
    // 0x802C5C48: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_2:
    // 0x802C5C4C: b           L_802C5CA0
    // 0x802C5C50: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
        goto L_802C5CA0;
    // 0x802C5C50: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
L_802C5C54:
    // 0x802C5C54: lw          $t0, -0x73A8($t0)
    ctx->r8 = MEM_W(ctx->r8, -0X73A8);
    // 0x802C5C58: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x802C5C5C: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x802C5C60: bne         $t0, $zero, L_802C5C74
    if (ctx->r8 != 0) {
        // 0x802C5C64: nop
    
            goto L_802C5C74;
    }
    // 0x802C5C64: nop

    // 0x802C5C68: jal         0x800933C4
    // 0x802C5C6C: sw          $zero, -0x54D4($at)
    MEM_W(-0X54D4, ctx->r1) = 0;
    func_800933C4(rdram, ctx);
        goto after_3;
    // 0x802C5C6C: sw          $zero, -0x54D4($at)
    MEM_W(-0X54D4, ctx->r1) = 0;
    after_3:
    // 0x802C5C70: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
L_802C5C74:
    // 0x802C5C74: lui         $t1, 0x802D
    ctx->r9 = S32(0X802D << 16);
    // 0x802C5C78: lw          $t1, -0x73A4($t1)
    ctx->r9 = MEM_W(ctx->r9, -0X73A4);
    // 0x802C5C7C: addiu       $t2, $zero, 0x1
    ctx->r10 = ADD32(0, 0X1);
    // 0x802C5C80: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x802C5C84: bne         $t1, $zero, L_802C5C98
    if (ctx->r9 != 0) {
        // 0x802C5C88: or          $a0, $s0, $zero
        ctx->r4 = ctx->r16 | 0;
            goto L_802C5C98;
    }
    // 0x802C5C88: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x802C5C8C: jal         0x800933C4
    // 0x802C5C90: sw          $t2, -0x54D4($at)
    MEM_W(-0X54D4, ctx->r1) = ctx->r10;
    func_800933C4(rdram, ctx);
        goto after_4;
    // 0x802C5C90: sw          $t2, -0x54D4($at)
    MEM_W(-0X54D4, ctx->r1) = ctx->r10;
    after_4:
    // 0x802C5C94: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
L_802C5C98:
    // 0x802C5C98: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x802C5C9C: sw          $zero, -0x54D4($at)
    MEM_W(-0X54D4, ctx->r1) = 0;
L_802C5CA0:
    // 0x802C5CA0: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
    // 0x802C5CA4: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C5CA8: lui         $t3, 0xE700
    ctx->r11 = S32(0XE700 << 16);
    // 0x802C5CAC: sw          $t3, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r11;
    // 0x802C5CB0: sw          $zero, 0x4($v0)
    MEM_W(0X4, ctx->r2) = 0;
    // 0x802C5CB4: or          $v1, $s0, $zero
    ctx->r3 = ctx->r16 | 0;
    // 0x802C5CB8: lui         $t4, 0xED02
    ctx->r12 = S32(0XED02 << 16);
    // 0x802C5CBC: addiu       $t4, $t4, 0x50
    ctx->r12 = ADD32(ctx->r12, 0X50);
    // 0x802C5CC0: lui         $t5, 0x68
    ctx->r13 = S32(0X68 << 16);
    // 0x802C5CC4: addiu       $t5, $t5, -0x3C94
    ctx->r13 = ADD32(ctx->r13, -0X3C94);
    { extern uint32_t wr64_experimental_viewport_borders(void); if (wr64_experimental_viewport_borders()) { ctx->r12 = 0xED000000U; ctx->r13 = 0x006A03C0U; } }
    // 0x802C5CC8: sw          $t4, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r12;
    // 0x802C5CCC: sw          $t5, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r13;
    // 0x802C5CD0: lui         $t6, 0x801D
    ctx->r14 = S32(0X801D << 16);
    // 0x802C5CD4: lh          $t6, -0x19F4($t6)
    ctx->r14 = MEM_H(ctx->r14, -0X19F4);
    // 0x802C5CD8: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x802C5CDC: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C5CE0: bne         $t6, $at, L_802C5D0C
    if (ctx->r14 != ctx->r1) {
        // 0x802C5CE4: nop
    
            goto L_802C5D0C;
    }
    // 0x802C5CE4: nop

    // 0x802C5CE8: jal         0x802C6ADC
    // 0x802C5CEC: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    func_i2_802C6ADC(rdram, ctx);
        goto after_5;
    // 0x802C5CEC: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_5:
    // 0x802C5CF0: lui         $t8, 0x80C
    ctx->r24 = S32(0X80C << 16);
    // 0x802C5CF4: addiu       $t8, $t8, -0x1B00
    ctx->r24 = ADD32(ctx->r24, -0X1B00);
    // 0x802C5CF8: lui         $t7, 0x600
    ctx->r15 = S32(0X600 << 16);
    // 0x802C5CFC: sw          $t7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r15;
    // 0x802C5D00: sw          $t8, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r24;
    { extern uint32_t wr64_watercraft_preview_coverage(uint8_t*, uint32_t); ctx->r2 = S32(wr64_watercraft_preview_coverage(rdram, (uint32_t)ctx->r2)); }
    // 0x802C5D04: b           L_802C5D64
    // 0x802C5D08: addiu       $s0, $v0, 0x8
    ctx->r16 = ADD32(ctx->r2, 0X8);
        goto L_802C5D64;
    // 0x802C5D08: addiu       $s0, $v0, 0x8
    ctx->r16 = ADD32(ctx->r2, 0X8);
L_802C5D0C:
    // 0x802C5D0C: jal         0x802C7C50
    // 0x802C5D10: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    func_i2_802C7C50(rdram, ctx);
        goto after_6;
    // 0x802C5D10: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_6:
    // 0x802C5D14: lui         $a0, 0x802D
    ctx->r4 = S32(0X802D << 16);
    // 0x802C5D18: addiu       $a0, $a0, -0x73A8
    ctx->r4 = ADD32(ctx->r4, -0X73A8);
    // 0x802C5D1C: lw          $t9, 0x0($a0)
    ctx->r25 = MEM_W(ctx->r4, 0X0);
    // 0x802C5D20: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
    // 0x802C5D24: lui         $t0, 0x600
    ctx->r8 = S32(0X600 << 16);
    // 0x802C5D28: bne         $t9, $zero, L_802C5D40
    if (ctx->r25 != 0) {
        // 0x802C5D2C: lui         $t1, 0x80C
        ctx->r9 = S32(0X80C << 16);
            goto L_802C5D40;
    }
    // 0x802C5D2C: lui         $t1, 0x80C
    ctx->r9 = S32(0X80C << 16);
    // 0x802C5D30: addiu       $t1, $t1, -0x1B58
    ctx->r9 = ADD32(ctx->r9, -0X1B58);
    // 0x802C5D34: sw          $t1, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r9;
    // 0x802C5D38: addiu       $s0, $v0, 0x8
    ctx->r16 = ADD32(ctx->r2, 0X8);
    // 0x802C5D3C: sw          $t0, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r8;
L_802C5D40:
    { extern void wr64_two_player_preview_coverage(uint8_t*, recomp_context*, uint32_t); wr64_two_player_preview_coverage(rdram, ctx, 0); }
    // 0x802C5D40: lw          $t2, 0x4($a0)
    ctx->r10 = MEM_W(ctx->r4, 0X4);
    // 0x802C5D44: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
    // 0x802C5D48: lui         $t3, 0x600
    ctx->r11 = S32(0X600 << 16);
    // 0x802C5D4C: bne         $t2, $zero, L_802C5D64
    if (ctx->r10 != 0) {
        // 0x802C5D50: lui         $t4, 0x80C
        ctx->r12 = S32(0X80C << 16);
            goto L_802C5D64;
    }
    // 0x802C5D50: lui         $t4, 0x80C
    ctx->r12 = S32(0X80C << 16);
    // 0x802C5D54: addiu       $t4, $t4, -0x1B00
    ctx->r12 = ADD32(ctx->r12, -0X1B00);
    // 0x802C5D58: sw          $t4, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r12;
    // 0x802C5D5C: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C5D60: sw          $t3, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r11;
L_802C5D64:
    { extern void wr64_two_player_preview_coverage(uint8_t*, recomp_context*, uint32_t); wr64_two_player_preview_coverage(rdram, ctx, 1); }
    // 0x802C5D64: lui         $t5, 0x800E
    ctx->r13 = S32(0X800E << 16);
    // 0x802C5D68: lw          $t5, -0x54DC($t5)
    ctx->r13 = MEM_W(ctx->r13, -0X54DC);
    // 0x802C5D6C: addiu       $at, $zero, 0xA
    ctx->r1 = ADD32(0, 0XA);
    // 0x802C5D70: lui         $t8, 0x8023
    ctx->r24 = S32(0X8023 << 16);
    // 0x802C5D74: bne         $t5, $at, L_802C5DA4
    if (ctx->r13 != ctx->r1) {
        // 0x802C5D78: nop
    
            goto L_802C5DA4;
    }
    // 0x802C5D78: nop

    // 0x802C5D7C: jal         0x802C5E28
    // 0x802C5D80: nop

    func_i2_802C5E28(rdram, ctx);
        goto after_7;
    // 0x802C5D80: nop

    after_7:
    // 0x802C5D84: lui         $t6, 0x8023
    ctx->r14 = S32(0X8023 << 16);
    // 0x802C5D88: lh          $t6, -0x75EA($t6)
    ctx->r14 = MEM_H(ctx->r14, -0X75EA);
    // 0x802C5D8C: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x802C5D90: addiu       $t7, $zero, 0x1
    ctx->r15 = ADD32(0, 0X1);
    // 0x802C5D94: bne         $t6, $at, L_802C5E10
    if (ctx->r14 != ctx->r1) {
        // 0x802C5D98: lui         $at, 0x802D
        ctx->r1 = S32(0X802D << 16);
            goto L_802C5E10;
    }
    // 0x802C5D98: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C5D9C: b           L_802C5E10
    // 0x802C5DA0: sw          $t7, -0x7440($at)
    MEM_W(-0X7440, ctx->r1) = ctx->r15;
        goto L_802C5E10;
    // 0x802C5DA0: sw          $t7, -0x7440($at)
    MEM_W(-0X7440, ctx->r1) = ctx->r15;
L_802C5DA4:
    // 0x802C5DA4: lh          $t8, -0x75EA($t8)
    ctx->r24 = MEM_H(ctx->r24, -0X75EA);
    // 0x802C5DA8: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x802C5DAC: bnel        $t8, $at, L_802C5E14
    if (ctx->r24 != ctx->r1) {
        // 0x802C5DB0: or          $v0, $s0, $zero
        ctx->r2 = ctx->r16 | 0;
            goto L_802C5E14;
    }
    goto skip_0;
    // 0x802C5DB0: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
    skip_0:
    // 0x802C5DB4: jal         0x8007C31C
    // 0x802C5DB8: nop

    func_8007C31C(rdram, ctx);
        goto after_8;
    // 0x802C5DB8: nop

    after_8:
    // 0x802C5DBC: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x802C5DC0: lw          $v1, -0x19D0($v1)
    ctx->r3 = MEM_W(ctx->r3, -0X19D0);
    // 0x802C5DC4: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x802C5DC8: beq         $v1, $at, L_802C5DE8
    if (ctx->r3 == ctx->r1) {
        // 0x802C5DCC: addiu       $at, $zero, 0x14
        ctx->r1 = ADD32(0, 0X14);
            goto L_802C5DE8;
    }
    // 0x802C5DCC: addiu       $at, $zero, 0x14
    ctx->r1 = ADD32(0, 0X14);
    // 0x802C5DD0: beq         $v1, $at, L_802C5E08
    if (ctx->r3 == ctx->r1) {
        // 0x802C5DD4: addiu       $at, $zero, 0x1E
        ctx->r1 = ADD32(0, 0X1E);
            goto L_802C5E08;
    }
    // 0x802C5DD4: addiu       $at, $zero, 0x1E
    ctx->r1 = ADD32(0, 0X1E);
    // 0x802C5DD8: beq         $v1, $at, L_802C5DF8
    if (ctx->r3 == ctx->r1) {
        // 0x802C5DDC: nop
    
            goto L_802C5DF8;
    }
    // 0x802C5DDC: nop

    // 0x802C5DE0: b           L_802C5E14
    // 0x802C5DE4: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
        goto L_802C5E14;
    // 0x802C5DE4: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
L_802C5DE8:
    // 0x802C5DE8: jal         0x801EB180
    // 0x802C5DEC: nop

    func_801EB180(rdram, ctx);
        goto after_9;
    // 0x802C5DEC: nop

    after_9:
    // 0x802C5DF0: b           L_802C5E14
    // 0x802C5DF4: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
        goto L_802C5E14;
    // 0x802C5DF4: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
L_802C5DF8:
    // 0x802C5DF8: jal         0x801EB91C
    // 0x802C5DFC: nop

    func_801EB91C(rdram, ctx);
        goto after_10;
    // 0x802C5DFC: nop

    after_10:
    // 0x802C5E00: b           L_802C5E14
    // 0x802C5E04: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
        goto L_802C5E14;
    // 0x802C5E04: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
L_802C5E08:
    // 0x802C5E08: jal         0x801EBFE4
    // 0x802C5E0C: nop

    func_801EBFE4(rdram, ctx);
        goto after_11;
    // 0x802C5E0C: nop

    after_11:
L_802C5E10:
    // 0x802C5E10: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
L_802C5E14:
    { extern void wr64_watercraft_preview_finish(uint8_t*, uint32_t); wr64_watercraft_preview_finish(rdram, (uint32_t)ctx->r2); }
    // 0x802C5E14: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
L_802C5E18:
    // 0x802C5E18: lw          $s0, 0x18($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X18);
    // 0x802C5E1C: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x802C5E20: jr          $ra
    // 0x802C5E24: nop

    return;
    // 0x802C5E24: nop

;}
RECOMP_FUNC void func_i2_802C5E28(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C5E28: addiu       $sp, $sp, -0x58
    ctx->r29 = ADD32(ctx->r29, -0X58);
    // 0x802C5E2C: lui         $t0, 0x801D
    ctx->r8 = S32(0X801D << 16);
    // 0x802C5E30: lh          $t0, -0x19F4($t0)
    ctx->r8 = MEM_H(ctx->r8, -0X19F4);
    // 0x802C5E34: sw          $s0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r16;
    // 0x802C5E38: sw          $ra, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r31;
    // 0x802C5E3C: sw          $fp, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r30;
    // 0x802C5E40: sw          $s7, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r23;
    // 0x802C5E44: sw          $s6, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r22;
    // 0x802C5E48: sw          $s5, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r21;
    // 0x802C5E4C: sw          $s4, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r20;
    // 0x802C5E50: sw          $s3, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r19;
    // 0x802C5E54: sw          $s2, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r18;
    // 0x802C5E58: sw          $s1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r17;
    // 0x802C5E5C: blez        $t0, L_802C6734
    if (SIGNED(ctx->r8) <= 0) {
        // 0x802C5E60: or          $s0, $zero, $zero
        ctx->r16 = 0 | 0;
            goto L_802C6734;
    }
    // 0x802C5E60: or          $s0, $zero, $zero
    ctx->r16 = 0 | 0;
    // 0x802C5E64: lui         $s2, 0x802D
    ctx->r18 = S32(0X802D << 16);
    // 0x802C5E68: lui         $s7, 0x800E
    ctx->r23 = S32(0X800E << 16);
    // 0x802C5E6C: addiu       $s7, $s7, -0x5640
    ctx->r23 = ADD32(ctx->r23, -0X5640);
    // 0x802C5E70: addiu       $s2, $s2, -0x73A8
    ctx->r18 = ADD32(ctx->r18, -0X73A8);
    // 0x802C5E74: or          $s4, $zero, $zero
    ctx->r20 = 0 | 0;
    // 0x802C5E78: addiu       $fp, $zero, 0x4
    ctx->r30 = ADD32(0, 0X4);
    // 0x802C5E7C: addiu       $s3, $zero, 0x1
    ctx->r19 = ADD32(0, 0X1);
L_802C5E80:
    // 0x802C5E80: bne         $s0, $zero, L_802C5E9C
    if (ctx->r16 != 0) {
        // 0x802C5E84: lui         $t9, 0x801D
        ctx->r25 = S32(0X801D << 16);
            goto L_802C5E9C;
    }
    // 0x802C5E84: lui         $t9, 0x801D
    ctx->r25 = S32(0X801D << 16);
    // 0x802C5E88: lui         $t6, 0x800D
    ctx->r14 = S32(0X800D << 16);
    // 0x802C5E8C: lw          $t6, 0x48DC($t6)
    ctx->r14 = MEM_W(ctx->r14, 0X48DC);
    // 0x802C5E90: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    // 0x802C5E94: b           L_802C5EAC
    // 0x802C5E98: sw          $t6, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r14;
        goto L_802C5EAC;
    // 0x802C5E98: sw          $t6, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r14;
L_802C5E9C:
    // 0x802C5E9C: lui         $t7, 0x800D
    ctx->r15 = S32(0X800D << 16);
    // 0x802C5EA0: lw          $t7, 0x48E0($t7)
    ctx->r15 = MEM_W(ctx->r15, 0X48E0);
    // 0x802C5EA4: or          $v0, $s3, $zero
    ctx->r2 = ctx->r19 | 0;
    // 0x802C5EA8: sw          $t7, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r15;
L_802C5EAC:
    // 0x802C5EAC: sll         $t8, $v0, 3
    ctx->r24 = S32(ctx->r2 << 3);
    // 0x802C5EB0: subu        $t8, $t8, $v0
    ctx->r24 = SUB32(ctx->r24, ctx->r2);
    // 0x802C5EB4: sll         $t8, $t8, 2
    ctx->r24 = S32(ctx->r24 << 2);
    // 0x802C5EB8: addiu       $t9, $t9, -0x19A8
    ctx->r25 = ADD32(ctx->r25, -0X19A8);
    // 0x802C5EBC: addu        $s6, $t8, $t9
    ctx->r22 = ADD32(ctx->r24, ctx->r25);
    // 0x802C5EC0: lhu         $a0, 0x2($s6)
    ctx->r4 = MEM_HU(ctx->r22, 0X2);
    // 0x802C5EC4: lui         $t2, 0x802D
    ctx->r10 = S32(0X802D << 16);
    // 0x802C5EC8: andi        $t1, $a0, 0xB000
    ctx->r9 = ctx->r4 & 0XB000;
    // 0x802C5ECC: beq         $t1, $zero, L_802C60A4
    if (ctx->r9 == 0) {
        // 0x802C5ED0: andi        $t7, $a0, 0x4000
        ctx->r15 = ctx->r4 & 0X4000;
            goto L_802C60A4;
    }
    // 0x802C5ED0: andi        $t7, $a0, 0x4000
    ctx->r15 = ctx->r4 & 0X4000;
    // 0x802C5ED4: lw          $t2, -0x7440($t2)
    ctx->r10 = MEM_W(ctx->r10, -0X7440);
    // 0x802C5ED8: beq         $t2, $zero, L_802C60A4
    if (ctx->r10 == 0) {
        // 0x802C5EDC: nop
    
            goto L_802C60A4;
    }
    // 0x802C5EDC: nop

    // 0x802C5EE0: lw          $t3, 0x0($s2)
    ctx->r11 = MEM_W(ctx->r18, 0X0);
    // 0x802C5EE4: or          $a1, $s3, $zero
    ctx->r5 = ctx->r19 | 0;
    // 0x802C5EE8: sltiu       $at, $t3, 0x6
    ctx->r1 = ctx->r11 < 0X6 ? 1 : 0;
    // 0x802C5EEC: beq         $at, $zero, L_802C6050
    if (ctx->r1 == 0) {
        // 0x802C5EF0: sll         $t3, $t3, 2
        ctx->r11 = S32(ctx->r11 << 2);
            goto L_802C6050;
    }
    // 0x802C5EF0: sll         $t3, $t3, 2
    ctx->r11 = S32(ctx->r11 << 2);
    // 0x802C5EF4: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C5EF8: addu        $at, $at, $t3
    gpr jr_addend_802C5F00 = ctx->r11;
    ctx->r1 = ADD32(ctx->r1, ctx->r11);
    // 0x802C5EFC: lw          $t3, -0x7414($at)
    ctx->r11 = ADD32(ctx->r1, -0X7414);
    // 0x802C5F00: jr          $t3
    // 0x802C5F04: nop

    switch (jr_addend_802C5F00 >> 2) {
        case 0: goto L_802C5F08; break;
        case 1: goto L_802C5F90; break;
        case 2: goto L_802C5FF8; break;
        case 3: goto L_802C6004; break;
        case 4: goto L_802C600C; break;
        case 5: goto L_802C6040; break;
        default: switch_error(__func__, 0x802C5F00, 0x802C8BEC);
    }
    // 0x802C5F04: nop

L_802C5F08:
    // 0x802C5F08: sw          $s3, 0x0($s2)
    MEM_W(0X0, ctx->r18) = ctx->r19;
    // 0x802C5F0C: lui         $t6, 0x800E
    ctx->r14 = S32(0X800E << 16);
    // 0x802C5F10: lh          $t6, -0x549C($t6)
    ctx->r14 = MEM_H(ctx->r14, -0X549C);
    // 0x802C5F14: lui         $t5, 0x801D
    ctx->r13 = S32(0X801D << 16);
    // 0x802C5F18: addiu       $t5, $t5, -0x190C
    ctx->r13 = ADD32(ctx->r13, -0X190C);
    // 0x802C5F1C: sll         $t4, $s0, 1
    ctx->r12 = S32(ctx->r16 << 1);
    // 0x802C5F20: addu        $v0, $t4, $t5
    ctx->r2 = ADD32(ctx->r12, ctx->r13);
    // 0x802C5F24: beq         $t6, $zero, L_802C5F3C
    if (ctx->r14 == 0) {
        // 0x802C5F28: addu        $v1, $s7, $s4
        ctx->r3 = ADD32(ctx->r23, ctx->r20);
            goto L_802C5F3C;
    }
    // 0x802C5F28: addu        $v1, $s7, $s4
    ctx->r3 = ADD32(ctx->r23, ctx->r20);
    // 0x802C5F2C: andi        $t7, $a0, 0x2000
    ctx->r15 = ctx->r4 & 0X2000;
    // 0x802C5F30: beql        $t7, $zero, L_802C5F40
    if (ctx->r15 == 0) {
        // 0x802C5F34: lh          $t8, 0x0($v0)
        ctx->r24 = MEM_H(ctx->r2, 0X0);
            goto L_802C5F40;
    }
    goto skip_0;
    // 0x802C5F34: lh          $t8, 0x0($v0)
    ctx->r24 = MEM_H(ctx->r2, 0X0);
    skip_0:
    // 0x802C5F38: sh          $s3, 0x0($v0)
    MEM_H(0X0, ctx->r2) = ctx->r19;
L_802C5F3C:
    // 0x802C5F3C: lh          $t8, 0x0($v0)
    ctx->r24 = MEM_H(ctx->r2, 0X0);
L_802C5F40:
    // 0x802C5F40: beql        $t8, $zero, L_802C5F70
    if (ctx->r24 == 0) {
        // 0x802C5F44: lw          $t5, 0x0($v1)
        ctx->r13 = MEM_W(ctx->r3, 0X0);
            goto L_802C5F70;
    }
    goto skip_1;
    // 0x802C5F44: lw          $t5, 0x0($v1)
    ctx->r13 = MEM_W(ctx->r3, 0X0);
    skip_1:
    // 0x802C5F48: lw          $t9, 0x0($v1)
    ctx->r25 = MEM_W(ctx->r3, 0X0);
    // 0x802C5F4C: lui         $t2, 0x802D
    ctx->r10 = S32(0X802D << 16);
    // 0x802C5F50: addiu       $t2, $t2, -0x7390
    ctx->r10 = ADD32(ctx->r10, -0X7390);
    // 0x802C5F54: sll         $t1, $t9, 1
    ctx->r9 = S32(ctx->r25 << 1);
    // 0x802C5F58: addu        $v0, $t1, $t2
    ctx->r2 = ADD32(ctx->r9, ctx->r10);
    // 0x802C5F5C: lh          $t3, 0x0($v0)
    ctx->r11 = MEM_H(ctx->r2, 0X0);
    // 0x802C5F60: ori         $t4, $t3, 0x2
    ctx->r12 = ctx->r11 | 0X2;
    // 0x802C5F64: b           L_802C6050
    // 0x802C5F68: sh          $t4, 0x0($v0)
    MEM_H(0X0, ctx->r2) = ctx->r12;
        goto L_802C6050;
    // 0x802C5F68: sh          $t4, 0x0($v0)
    MEM_H(0X0, ctx->r2) = ctx->r12;
    // 0x802C5F6C: lw          $t5, 0x0($v1)
    ctx->r13 = MEM_W(ctx->r3, 0X0);
L_802C5F70:
    // 0x802C5F70: lui         $t7, 0x802D
    ctx->r15 = S32(0X802D << 16);
    // 0x802C5F74: addiu       $t7, $t7, -0x7390
    ctx->r15 = ADD32(ctx->r15, -0X7390);
    // 0x802C5F78: sll         $t6, $t5, 1
    ctx->r14 = S32(ctx->r13 << 1);
    // 0x802C5F7C: addu        $v0, $t6, $t7
    ctx->r2 = ADD32(ctx->r14, ctx->r15);
    // 0x802C5F80: lh          $t8, 0x0($v0)
    ctx->r24 = MEM_H(ctx->r2, 0X0);
    // 0x802C5F84: ori         $t9, $t8, 0x1
    ctx->r25 = ctx->r24 | 0X1;
    // 0x802C5F88: b           L_802C6050
    // 0x802C5F8C: sh          $t9, 0x0($v0)
    MEM_H(0X0, ctx->r2) = ctx->r25;
        goto L_802C6050;
    // 0x802C5F8C: sh          $t9, 0x0($v0)
    MEM_H(0X0, ctx->r2) = ctx->r25;
L_802C5F90:
    // 0x802C5F90: lui         $t1, 0x800E
    ctx->r9 = S32(0X800E << 16);
    // 0x802C5F94: addu        $t1, $t1, $s4
    ctx->r9 = ADD32(ctx->r9, ctx->r20);
    // 0x802C5F98: lw          $t1, -0x5638($t1)
    ctx->r9 = MEM_W(ctx->r9, -0X5638);
    // 0x802C5F9C: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x802C5FA0: addiu       $t3, $zero, 0x2
    ctx->r11 = ADD32(0, 0X2);
    // 0x802C5FA4: bne         $t1, $zero, L_802C5FE4
    if (ctx->r9 != 0) {
        // 0x802C5FA8: nop
    
            goto L_802C5FE4;
    }
    // 0x802C5FA8: nop

    // 0x802C5FAC: bne         $s0, $zero, L_802C5FBC
    if (ctx->r16 != 0) {
        // 0x802C5FB0: lw          $v0, -0x19F8($v0)
        ctx->r2 = MEM_W(ctx->r2, -0X19F8);
            goto L_802C5FBC;
    }
    // 0x802C5FB0: lw          $v0, -0x19F8($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X19F8);
    // 0x802C5FB4: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C5FB8: sw          $zero, -0x4CD4($at)
    MEM_W(-0X4CD4, ctx->r1) = 0;
L_802C5FBC:
    // 0x802C5FBC: beq         $v0, $zero, L_802C5FCC
    if (ctx->r2 == 0) {
        // 0x802C5FC0: addiu       $at, $zero, 0xB
        ctx->r1 = ADD32(0, 0XB);
            goto L_802C5FCC;
    }
    // 0x802C5FC0: addiu       $at, $zero, 0xB
    ctx->r1 = ADD32(0, 0XB);
    // 0x802C5FC4: bne         $v0, $at, L_802C5FDC
    if (ctx->r2 != ctx->r1) {
        // 0x802C5FC8: addiu       $t2, $zero, 0x5
        ctx->r10 = ADD32(0, 0X5);
            goto L_802C5FDC;
    }
    // 0x802C5FC8: addiu       $t2, $zero, 0x5
    ctx->r10 = ADD32(0, 0X5);
L_802C5FCC:
    // 0x802C5FCC: jal         0x802C6864
    // 0x802C5FD0: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    func_i2_802C6864(rdram, ctx);
        goto after_0;
    // 0x802C5FD0: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_0:
    // 0x802C5FD4: b           L_802C6050
    // 0x802C5FD8: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
        goto L_802C6050;
    // 0x802C5FD8: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
L_802C5FDC:
    // 0x802C5FDC: b           L_802C6050
    // 0x802C5FE0: sw          $t2, 0x0($s2)
    MEM_W(0X0, ctx->r18) = ctx->r10;
        goto L_802C6050;
    // 0x802C5FE0: sw          $t2, 0x0($s2)
    MEM_W(0X0, ctx->r18) = ctx->r10;
L_802C5FE4:
    // 0x802C5FE4: bne         $s0, $zero, L_802C5FF0
    if (ctx->r16 != 0) {
        // 0x802C5FE8: lui         $at, 0x801D
        ctx->r1 = S32(0X801D << 16);
            goto L_802C5FF0;
    }
    // 0x802C5FE8: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C5FEC: sw          $s3, -0x4CD4($at)
    MEM_W(-0X4CD4, ctx->r1) = ctx->r19;
L_802C5FF0:
    // 0x802C5FF0: b           L_802C6050
    // 0x802C5FF4: sw          $t3, 0x0($s2)
    MEM_W(0X0, ctx->r18) = ctx->r11;
        goto L_802C6050;
    // 0x802C5FF4: sw          $t3, 0x0($s2)
    MEM_W(0X0, ctx->r18) = ctx->r11;
L_802C5FF8:
    // 0x802C5FF8: addiu       $t4, $zero, 0x3
    ctx->r12 = ADD32(0, 0X3);
    // 0x802C5FFC: b           L_802C6050
    // 0x802C6000: sw          $t4, 0x0($s2)
    MEM_W(0X0, ctx->r18) = ctx->r12;
        goto L_802C6050;
    // 0x802C6000: sw          $t4, 0x0($s2)
    MEM_W(0X0, ctx->r18) = ctx->r12;
L_802C6004:
    // 0x802C6004: b           L_802C6050
    // 0x802C6008: sw          $fp, 0x0($s2)
    MEM_W(0X0, ctx->r18) = ctx->r30;
        goto L_802C6050;
    // 0x802C6008: sw          $fp, 0x0($s2)
    MEM_W(0X0, ctx->r18) = ctx->r30;
L_802C600C:
    // 0x802C600C: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x802C6010: lw          $v0, -0x19F8($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X19F8);
    // 0x802C6014: addiu       $at, $zero, 0xB
    ctx->r1 = ADD32(0, 0XB);
    // 0x802C6018: beq         $v0, $zero, L_802C6028
    if (ctx->r2 == 0) {
        // 0x802C601C: nop
    
            goto L_802C6028;
    }
    // 0x802C601C: nop

    // 0x802C6020: bne         $v0, $at, L_802C6038
    if (ctx->r2 != ctx->r1) {
        // 0x802C6024: addiu       $t5, $zero, 0x5
        ctx->r13 = ADD32(0, 0X5);
            goto L_802C6038;
    }
    // 0x802C6024: addiu       $t5, $zero, 0x5
    ctx->r13 = ADD32(0, 0X5);
L_802C6028:
    // 0x802C6028: jal         0x802C6864
    // 0x802C602C: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    func_i2_802C6864(rdram, ctx);
        goto after_1;
    // 0x802C602C: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_1:
    // 0x802C6030: b           L_802C6050
    // 0x802C6034: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
        goto L_802C6050;
    // 0x802C6034: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
L_802C6038:
    // 0x802C6038: b           L_802C6050
    // 0x802C603C: sw          $t5, 0x0($s2)
    MEM_W(0X0, ctx->r18) = ctx->r13;
        goto L_802C6050;
    // 0x802C603C: sw          $t5, 0x0($s2)
    MEM_W(0X0, ctx->r18) = ctx->r13;
L_802C6040:
    // 0x802C6040: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x802C6044: jal         0x802C6864
    // 0x802C6048: sw          $a1, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r5;
    func_i2_802C6864(rdram, ctx);
        goto after_2;
    // 0x802C6048: sw          $a1, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r5;
    after_2:
    // 0x802C604C: lw          $a1, 0x40($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X40);
L_802C6050:
    // 0x802C6050: beq         $a1, $zero, L_802C6690
    if (ctx->r5 == 0) {
        // 0x802C6054: lui         $t6, 0x8023
        ctx->r14 = S32(0X8023 << 16);
            goto L_802C6690;
    }
    // 0x802C6054: lui         $t6, 0x8023
    ctx->r14 = S32(0X8023 << 16);
    // 0x802C6058: lh          $t6, -0x75CE($t6)
    ctx->r14 = MEM_H(ctx->r14, -0X75CE);
    // 0x802C605C: addiu       $a0, $zero, 0x2A
    ctx->r4 = ADD32(0, 0X2A);
    // 0x802C6060: bne         $s3, $t6, L_802C6078
    if (ctx->r19 != ctx->r14) {
        // 0x802C6064: nop
    
            goto L_802C6078;
    }
    // 0x802C6064: nop

    // 0x802C6068: jal         0x800C37F4
    // 0x802C606C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_3;
    // 0x802C606C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_3:
    // 0x802C6070: b           L_802C6694
    // 0x802C6074: lw          $t1, 0x0($s2)
    ctx->r9 = MEM_W(ctx->r18, 0X0);
        goto L_802C6694;
    // 0x802C6074: lw          $t1, 0x0($s2)
    ctx->r9 = MEM_W(ctx->r18, 0X0);
L_802C6078:
    // 0x802C6078: bne         $a1, $s3, L_802C6094
    if (ctx->r5 != ctx->r19) {
        // 0x802C607C: addiu       $a0, $zero, 0x37
        ctx->r4 = ADD32(0, 0X37);
            goto L_802C6094;
    }
    // 0x802C607C: addiu       $a0, $zero, 0x37
    ctx->r4 = ADD32(0, 0X37);
    // 0x802C6080: addiu       $a0, $zero, 0x11
    ctx->r4 = ADD32(0, 0X11);
    // 0x802C6084: jal         0x800C37F4
    // 0x802C6088: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_4;
    // 0x802C6088: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_4:
    // 0x802C608C: b           L_802C6694
    // 0x802C6090: lw          $t1, 0x0($s2)
    ctx->r9 = MEM_W(ctx->r18, 0X0);
        goto L_802C6694;
    // 0x802C6090: lw          $t1, 0x0($s2)
    ctx->r9 = MEM_W(ctx->r18, 0X0);
L_802C6094:
    // 0x802C6094: jal         0x800C37F4
    // 0x802C6098: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_5;
    // 0x802C6098: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_5:
    // 0x802C609C: b           L_802C6694
    // 0x802C60A0: lw          $t1, 0x0($s2)
    ctx->r9 = MEM_W(ctx->r18, 0X0);
        goto L_802C6694;
    // 0x802C60A0: lw          $t1, 0x0($s2)
    ctx->r9 = MEM_W(ctx->r18, 0X0);
L_802C60A4:
    // 0x802C60A4: beq         $t7, $zero, L_802C61B0
    if (ctx->r15 == 0) {
        // 0x802C60A8: andi        $t6, $a0, 0xF
        ctx->r14 = ctx->r4 & 0XF;
            goto L_802C61B0;
    }
    // 0x802C60A8: andi        $t6, $a0, 0xF
    ctx->r14 = ctx->r4 & 0XF;
    // 0x802C60AC: lw          $t8, 0x0($s2)
    ctx->r24 = MEM_W(ctx->r18, 0X0);
    // 0x802C60B0: or          $a1, $s3, $zero
    ctx->r5 = ctx->r19 | 0;
    // 0x802C60B4: sltiu       $at, $t8, 0x6
    ctx->r1 = ctx->r24 < 0X6 ? 1 : 0;
    // 0x802C60B8: beq         $at, $zero, L_802C6194
    if (ctx->r1 == 0) {
        // 0x802C60BC: sll         $t8, $t8, 2
        ctx->r24 = S32(ctx->r24 << 2);
            goto L_802C6194;
    }
    // 0x802C60BC: sll         $t8, $t8, 2
    ctx->r24 = S32(ctx->r24 << 2);
    // 0x802C60C0: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C60C4: addu        $at, $at, $t8
    gpr jr_addend_802C60CC = ctx->r24;
    ctx->r1 = ADD32(ctx->r1, ctx->r24);
    // 0x802C60C8: lw          $t8, -0x73FC($at)
    ctx->r24 = ADD32(ctx->r1, -0X73FC);
    // 0x802C60CC: jr          $t8
    // 0x802C60D0: nop

    switch (jr_addend_802C60CC >> 2) {
        case 0: goto L_802C60D4; break;
        case 1: goto L_802C60E8; break;
        case 2: goto L_802C6174; break;
        case 3: goto L_802C617C; break;
        case 4: goto L_802C6188; break;
        case 5: goto L_802C6150; break;
        default: switch_error(__func__, 0x802C60CC, 0x802C8C04);
    }
    // 0x802C60D0: nop

L_802C60D4:
    // 0x802C60D4: addiu       $a0, $zero, 0x2
    ctx->r4 = ADD32(0, 0X2);
    // 0x802C60D8: jal         0x802C84EC
    // 0x802C60DC: sw          $a1, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r5;
    func_i2_802C84EC(rdram, ctx);
        goto after_6;
    // 0x802C60DC: sw          $a1, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r5;
    after_6:
    // 0x802C60E0: b           L_802C6198
    // 0x802C60E4: lw          $a1, 0x40($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X40);
        goto L_802C6198;
    // 0x802C60E4: lw          $a1, 0x40($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X40);
L_802C60E8:
    // 0x802C60E8: sll         $t9, $s0, 1
    ctx->r25 = S32(ctx->r16 << 1);
    // 0x802C60EC: lui         $t1, 0x801D
    ctx->r9 = S32(0X801D << 16);
    // 0x802C60F0: sw          $zero, 0x0($s2)
    MEM_W(0X0, ctx->r18) = 0;
    // 0x802C60F4: addu        $t1, $t1, $t9
    ctx->r9 = ADD32(ctx->r9, ctx->r25);
    // 0x802C60F8: lh          $t1, -0x190C($t1)
    ctx->r9 = MEM_H(ctx->r9, -0X190C);
    // 0x802C60FC: addu        $v1, $s7, $s4
    ctx->r3 = ADD32(ctx->r23, ctx->r20);
    // 0x802C6100: beql        $t1, $zero, L_802C6130
    if (ctx->r9 == 0) {
        // 0x802C6104: lw          $t7, 0x0($v1)
        ctx->r15 = MEM_W(ctx->r3, 0X0);
            goto L_802C6130;
    }
    goto skip_2;
    // 0x802C6104: lw          $t7, 0x0($v1)
    ctx->r15 = MEM_W(ctx->r3, 0X0);
    skip_2:
    // 0x802C6108: lw          $t2, 0x0($v1)
    ctx->r10 = MEM_W(ctx->r3, 0X0);
    // 0x802C610C: lui         $t4, 0x802D
    ctx->r12 = S32(0X802D << 16);
    // 0x802C6110: addiu       $t4, $t4, -0x7390
    ctx->r12 = ADD32(ctx->r12, -0X7390);
    // 0x802C6114: sll         $t3, $t2, 1
    ctx->r11 = S32(ctx->r10 << 1);
    // 0x802C6118: addu        $v0, $t3, $t4
    ctx->r2 = ADD32(ctx->r11, ctx->r12);
    // 0x802C611C: lh          $t5, 0x0($v0)
    ctx->r13 = MEM_H(ctx->r2, 0X0);
    // 0x802C6120: andi        $t6, $t5, 0xFFFD
    ctx->r14 = ctx->r13 & 0XFFFD;
    // 0x802C6124: b           L_802C6198
    // 0x802C6128: sh          $t6, 0x0($v0)
    MEM_H(0X0, ctx->r2) = ctx->r14;
        goto L_802C6198;
    // 0x802C6128: sh          $t6, 0x0($v0)
    MEM_H(0X0, ctx->r2) = ctx->r14;
    // 0x802C612C: lw          $t7, 0x0($v1)
    ctx->r15 = MEM_W(ctx->r3, 0X0);
L_802C6130:
    // 0x802C6130: lui         $t9, 0x802D
    ctx->r25 = S32(0X802D << 16);
    // 0x802C6134: addiu       $t9, $t9, -0x7390
    ctx->r25 = ADD32(ctx->r25, -0X7390);
    // 0x802C6138: sll         $t8, $t7, 1
    ctx->r24 = S32(ctx->r15 << 1);
    // 0x802C613C: addu        $v0, $t8, $t9
    ctx->r2 = ADD32(ctx->r24, ctx->r25);
    // 0x802C6140: lh          $t1, 0x0($v0)
    ctx->r9 = MEM_H(ctx->r2, 0X0);
    // 0x802C6144: andi        $t2, $t1, 0xFFFE
    ctx->r10 = ctx->r9 & 0XFFFE;
    // 0x802C6148: b           L_802C6198
    // 0x802C614C: sh          $t2, 0x0($v0)
    MEM_H(0X0, ctx->r2) = ctx->r10;
        goto L_802C6198;
    // 0x802C614C: sh          $t2, 0x0($v0)
    MEM_H(0X0, ctx->r2) = ctx->r10;
L_802C6150:
    // 0x802C6150: lui         $t3, 0x800E
    ctx->r11 = S32(0X800E << 16);
    // 0x802C6154: addu        $t3, $t3, $s4
    ctx->r11 = ADD32(ctx->r11, ctx->r20);
    // 0x802C6158: lw          $t3, -0x5638($t3)
    ctx->r11 = MEM_W(ctx->r11, -0X5638);
    // 0x802C615C: bne         $t3, $zero, L_802C616C
    if (ctx->r11 != 0) {
        // 0x802C6160: nop
    
            goto L_802C616C;
    }
    // 0x802C6160: nop

    // 0x802C6164: b           L_802C6198
    // 0x802C6168: sw          $s3, 0x0($s2)
    MEM_W(0X0, ctx->r18) = ctx->r19;
        goto L_802C6198;
    // 0x802C6168: sw          $s3, 0x0($s2)
    MEM_W(0X0, ctx->r18) = ctx->r19;
L_802C616C:
    // 0x802C616C: b           L_802C6198
    // 0x802C6170: sw          $fp, 0x0($s2)
    MEM_W(0X0, ctx->r18) = ctx->r30;
        goto L_802C6198;
    // 0x802C6170: sw          $fp, 0x0($s2)
    MEM_W(0X0, ctx->r18) = ctx->r30;
L_802C6174:
    // 0x802C6174: b           L_802C6198
    // 0x802C6178: sw          $s3, 0x0($s2)
    MEM_W(0X0, ctx->r18) = ctx->r19;
        goto L_802C6198;
    // 0x802C6178: sw          $s3, 0x0($s2)
    MEM_W(0X0, ctx->r18) = ctx->r19;
L_802C617C:
    // 0x802C617C: addiu       $t4, $zero, 0x2
    ctx->r12 = ADD32(0, 0X2);
    // 0x802C6180: b           L_802C6198
    // 0x802C6184: sw          $t4, 0x0($s2)
    MEM_W(0X0, ctx->r18) = ctx->r12;
        goto L_802C6198;
    // 0x802C6184: sw          $t4, 0x0($s2)
    MEM_W(0X0, ctx->r18) = ctx->r12;
L_802C6188:
    // 0x802C6188: addiu       $t5, $zero, 0x3
    ctx->r13 = ADD32(0, 0X3);
    // 0x802C618C: b           L_802C6198
    // 0x802C6190: sw          $t5, 0x0($s2)
    MEM_W(0X0, ctx->r18) = ctx->r13;
        goto L_802C6198;
    // 0x802C6190: sw          $t5, 0x0($s2)
    MEM_W(0X0, ctx->r18) = ctx->r13;
L_802C6194:
    // 0x802C6194: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
L_802C6198:
    // 0x802C6198: beq         $a1, $zero, L_802C6690
    if (ctx->r5 == 0) {
        // 0x802C619C: addiu       $a0, $zero, 0x16
        ctx->r4 = ADD32(0, 0X16);
            goto L_802C6690;
    }
    // 0x802C619C: addiu       $a0, $zero, 0x16
    ctx->r4 = ADD32(0, 0X16);
    // 0x802C61A0: jal         0x800C37F4
    // 0x802C61A4: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_7;
    // 0x802C61A4: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_7:
    // 0x802C61A8: b           L_802C6694
    // 0x802C61AC: lw          $t1, 0x0($s2)
    ctx->r9 = MEM_W(ctx->r18, 0X0);
        goto L_802C6694;
    // 0x802C61AC: lw          $t1, 0x0($s2)
    ctx->r9 = MEM_W(ctx->r18, 0X0);
L_802C61B0:
    // 0x802C61B0: beq         $t6, $zero, L_802C6298
    if (ctx->r14 == 0) {
        // 0x802C61B4: addiu       $v1, $zero, 0x1
        ctx->r3 = ADD32(0, 0X1);
            goto L_802C6298;
    }
    // 0x802C61B4: addiu       $v1, $zero, 0x1
    ctx->r3 = ADD32(0, 0X1);
    // 0x802C61B8: addu        $t7, $s7, $s4
    ctx->r15 = ADD32(ctx->r23, ctx->r20);
    // 0x802C61BC: lw          $t8, 0x0($t7)
    ctx->r24 = MEM_W(ctx->r15, 0X0);
    // 0x802C61C0: lw          $v0, 0x0($s2)
    ctx->r2 = MEM_W(ctx->r18, 0X0);
    // 0x802C61C4: lui         $v1, 0x802D
    ctx->r3 = S32(0X802D << 16);
    // 0x802C61C8: sll         $t9, $t8, 2
    ctx->r25 = S32(ctx->r24 << 2);
    // 0x802C61CC: addu        $v1, $v1, $t9
    ctx->r3 = ADD32(ctx->r3, ctx->r25);
    // 0x802C61D0: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x802C61D4: beq         $v0, $at, L_802C61F8
    if (ctx->r2 == ctx->r1) {
        // 0x802C61D8: lw          $v1, -0x7428($v1)
        ctx->r3 = MEM_W(ctx->r3, -0X7428);
            goto L_802C61F8;
    }
    // 0x802C61D8: lw          $v1, -0x7428($v1)
    ctx->r3 = MEM_W(ctx->r3, -0X7428);
    // 0x802C61DC: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x802C61E0: beq         $v0, $at, L_802C6230
    if (ctx->r2 == ctx->r1) {
        // 0x802C61E4: lui         $t4, 0x800E
        ctx->r12 = S32(0X800E << 16);
            goto L_802C6230;
    }
    // 0x802C61E4: lui         $t4, 0x800E
    ctx->r12 = S32(0X800E << 16);
    // 0x802C61E8: beq         $v0, $fp, L_802C6264
    if (ctx->r2 == ctx->r30) {
        // 0x802C61EC: lui         $t7, 0x800E
        ctx->r15 = S32(0X800E << 16);
            goto L_802C6264;
    }
    // 0x802C61EC: lui         $t7, 0x800E
    ctx->r15 = S32(0X800E << 16);
    // 0x802C61F0: b           L_802C6694
    // 0x802C61F4: lw          $t1, 0x0($s2)
    ctx->r9 = MEM_W(ctx->r18, 0X0);
        goto L_802C6694;
    // 0x802C61F4: lw          $t1, 0x0($s2)
    ctx->r9 = MEM_W(ctx->r18, 0X0);
L_802C61F8:
    // 0x802C61F8: sll         $v0, $v1, 3
    ctx->r2 = S32(ctx->r3 << 3);
    // 0x802C61FC: subu        $v0, $v0, $v1
    ctx->r2 = SUB32(ctx->r2, ctx->r3);
    // 0x802C6200: sll         $t2, $s0, 3
    ctx->r10 = S32(ctx->r16 << 3);
    // 0x802C6204: subu        $t2, $t2, $s0
    ctx->r10 = SUB32(ctx->r10, ctx->r16);
    // 0x802C6208: sll         $v0, $v0, 1
    ctx->r2 = S32(ctx->r2 << 1);
    // 0x802C620C: lui         $t1, 0x800E
    ctx->r9 = S32(0X800E << 16);
    // 0x802C6210: addu        $t1, $t1, $v0
    ctx->r9 = ADD32(ctx->r9, ctx->r2);
    // 0x802C6214: sll         $t2, $t2, 3
    ctx->r10 = S32(ctx->r10 << 3);
    // 0x802C6218: lb          $t1, -0x56A5($t1)
    ctx->r9 = MEM_B(ctx->r9, -0X56A5);
    // 0x802C621C: addu        $t3, $t2, $v0
    ctx->r11 = ADD32(ctx->r10, ctx->r2);
    // 0x802C6220: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C6224: addu        $at, $at, $t3
    ctx->r1 = ADD32(ctx->r1, ctx->r11);
    // 0x802C6228: b           L_802C6690
    // 0x802C622C: sb          $t1, -0x4D5D($at)
    MEM_B(-0X4D5D, ctx->r1) = ctx->r9;
        goto L_802C6690;
    // 0x802C622C: sb          $t1, -0x4D5D($at)
    MEM_B(-0X4D5D, ctx->r1) = ctx->r9;
L_802C6230:
    // 0x802C6230: sll         $v0, $v1, 3
    ctx->r2 = S32(ctx->r3 << 3);
    // 0x802C6234: subu        $v0, $v0, $v1
    ctx->r2 = SUB32(ctx->r2, ctx->r3);
    // 0x802C6238: sll         $t5, $s0, 3
    ctx->r13 = S32(ctx->r16 << 3);
    // 0x802C623C: subu        $t5, $t5, $s0
    ctx->r13 = SUB32(ctx->r13, ctx->r16);
    // 0x802C6240: sll         $v0, $v0, 1
    ctx->r2 = S32(ctx->r2 << 1);
    // 0x802C6244: addu        $t4, $t4, $v0
    ctx->r12 = ADD32(ctx->r12, ctx->r2);
    // 0x802C6248: sll         $t5, $t5, 3
    ctx->r13 = S32(ctx->r13 << 3);
    // 0x802C624C: lb          $t4, -0x56A4($t4)
    ctx->r12 = MEM_B(ctx->r12, -0X56A4);
    // 0x802C6250: addu        $t6, $t5, $v0
    ctx->r14 = ADD32(ctx->r13, ctx->r2);
    // 0x802C6254: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C6258: addu        $at, $at, $t6
    ctx->r1 = ADD32(ctx->r1, ctx->r14);
    // 0x802C625C: b           L_802C6690
    // 0x802C6260: sb          $t4, -0x4D5C($at)
    MEM_B(-0X4D5C, ctx->r1) = ctx->r12;
        goto L_802C6690;
    // 0x802C6260: sb          $t4, -0x4D5C($at)
    MEM_B(-0X4D5C, ctx->r1) = ctx->r12;
L_802C6264:
    // 0x802C6264: sll         $v0, $v1, 3
    ctx->r2 = S32(ctx->r3 << 3);
    // 0x802C6268: subu        $v0, $v0, $v1
    ctx->r2 = SUB32(ctx->r2, ctx->r3);
    // 0x802C626C: sll         $t8, $s0, 3
    ctx->r24 = S32(ctx->r16 << 3);
    // 0x802C6270: subu        $t8, $t8, $s0
    ctx->r24 = SUB32(ctx->r24, ctx->r16);
    // 0x802C6274: sll         $v0, $v0, 1
    ctx->r2 = S32(ctx->r2 << 1);
    // 0x802C6278: addu        $t7, $t7, $v0
    ctx->r15 = ADD32(ctx->r15, ctx->r2);
    // 0x802C627C: sll         $t8, $t8, 3
    ctx->r24 = S32(ctx->r24 << 3);
    // 0x802C6280: lb          $t7, -0x56A3($t7)
    ctx->r15 = MEM_B(ctx->r15, -0X56A3);
    // 0x802C6284: addu        $t9, $t8, $v0
    ctx->r25 = ADD32(ctx->r24, ctx->r2);
    // 0x802C6288: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C628C: addu        $at, $at, $t9
    ctx->r1 = ADD32(ctx->r1, ctx->r25);
    // 0x802C6290: b           L_802C6690
    // 0x802C6294: sb          $t7, -0x4D5B($at)
    MEM_B(-0X4D5B, ctx->r1) = ctx->r15;
        goto L_802C6690;
    // 0x802C6294: sb          $t7, -0x4D5B($at)
    MEM_B(-0X4D5B, ctx->r1) = ctx->r15;
L_802C6298:
    // 0x802C6298: lui         $t3, 0x800E
    ctx->r11 = S32(0X800E << 16);
    // 0x802C629C: lw          $t3, -0x54D8($t3)
    ctx->r11 = MEM_W(ctx->r11, -0X54D8);
    // 0x802C62A0: lui         $t2, 0x802D
    ctx->r10 = S32(0X802D << 16);
    // 0x802C62A4: lui         $t1, 0x802D
    ctx->r9 = S32(0X802D << 16);
    // 0x802C62A8: addiu       $t1, $t1, -0x7448
    ctx->r9 = ADD32(ctx->r9, -0X7448);
    // 0x802C62AC: addiu       $t2, $t2, -0x7450
    ctx->r10 = ADD32(ctx->r10, -0X7450);
    // 0x802C62B0: addu        $s1, $s4, $t2
    ctx->r17 = ADD32(ctx->r20, ctx->r10);
    // 0x802C62B4: addu        $s5, $s4, $t1
    ctx->r21 = ADD32(ctx->r20, ctx->r9);
    // 0x802C62B8: beq         $s3, $t3, L_802C62D4
    if (ctx->r19 == ctx->r11) {
        // 0x802C62BC: or          $a3, $zero, $zero
        ctx->r7 = 0 | 0;
            goto L_802C62D4;
    }
    // 0x802C62BC: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    // 0x802C62C0: lw          $t5, 0x0($s7)
    ctx->r13 = MEM_W(ctx->r23, 0X0);
    // 0x802C62C4: lw          $t4, 0x4($s7)
    ctx->r12 = MEM_W(ctx->r23, 0X4);
    // 0x802C62C8: bnel        $t5, $t4, L_802C62D8
    if (ctx->r13 != ctx->r12) {
        // 0x802C62CC: lw          $a2, 0x0($s2)
        ctx->r6 = MEM_W(ctx->r18, 0X0);
            goto L_802C62D8;
    }
    goto skip_3;
    // 0x802C62CC: lw          $a2, 0x0($s2)
    ctx->r6 = MEM_W(ctx->r18, 0X0);
    skip_3:
    // 0x802C62D0: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
L_802C62D4:
    // 0x802C62D4: lw          $a2, 0x0($s2)
    ctx->r6 = MEM_W(ctx->r18, 0X0);
L_802C62D8:
    // 0x802C62D8: lui         $t8, 0x801D
    ctx->r24 = S32(0X801D << 16);
    // 0x802C62DC: addiu       $t8, $t8, -0x190C
    ctx->r24 = ADD32(ctx->r24, -0X190C);
    // 0x802C62E0: bne         $a2, $zero, L_802C6390
    if (ctx->r6 != 0) {
        // 0x802C62E4: sll         $t6, $s0, 1
        ctx->r14 = S32(ctx->r16 << 1);
            goto L_802C6390;
    }
    // 0x802C62E4: sll         $t6, $s0, 1
    ctx->r14 = S32(ctx->r16 << 1);
    // 0x802C62E8: lui         $a1, 0x800E
    ctx->r5 = S32(0X800E << 16);
    // 0x802C62EC: lh          $a1, -0x54A0($a1)
    ctx->r5 = MEM_H(ctx->r5, -0X54A0);
    // 0x802C62F0: beq         $v1, $zero, L_802C6320
    if (ctx->r3 == 0) {
        // 0x802C62F4: addu        $v0, $t6, $t8
        ctx->r2 = ADD32(ctx->r14, ctx->r24);
            goto L_802C6320;
    }
    // 0x802C62F4: addu        $v0, $t6, $t8
    ctx->r2 = ADD32(ctx->r14, ctx->r24);
    // 0x802C62F8: lhu         $t7, 0x0($s6)
    ctx->r15 = MEM_HU(ctx->r22, 0X0);
    // 0x802C62FC: xori        $t2, $s0, 0x1
    ctx->r10 = ctx->r16 ^ 0X1;
    // 0x802C6300: andi        $t9, $t7, 0x800
    ctx->r25 = ctx->r15 & 0X800;
    // 0x802C6304: beq         $t9, $zero, L_802C6318
    if (ctx->r25 == 0) {
        // 0x802C6308: nop
    
            goto L_802C6318;
    }
    // 0x802C6308: nop

    // 0x802C630C: or          $a3, $s3, $zero
    ctx->r7 = ctx->r19 | 0;
    // 0x802C6310: b           L_802C635C
    // 0x802C6314: sh          $t2, 0x0($v0)
    MEM_H(0X0, ctx->r2) = ctx->r10;
        goto L_802C635C;
    // 0x802C6314: sh          $t2, 0x0($v0)
    MEM_H(0X0, ctx->r2) = ctx->r10;
L_802C6318:
    // 0x802C6318: b           L_802C635C
    // 0x802C631C: sh          $s0, 0x0($v0)
    MEM_H(0X0, ctx->r2) = ctx->r16;
        goto L_802C635C;
    // 0x802C631C: sh          $s0, 0x0($v0)
    MEM_H(0X0, ctx->r2) = ctx->r16;
L_802C6320:
    // 0x802C6320: addu        $t1, $s7, $s4
    ctx->r9 = ADD32(ctx->r23, ctx->r20);
    // 0x802C6324: lw          $t3, 0x0($t1)
    ctx->r11 = MEM_W(ctx->r9, 0X0);
    // 0x802C6328: lui         $v1, 0x802D
    ctx->r3 = S32(0X802D << 16);
    // 0x802C632C: sll         $t5, $t3, 1
    ctx->r13 = S32(ctx->r11 << 1);
    // 0x802C6330: addu        $v1, $v1, $t5
    ctx->r3 = ADD32(ctx->r3, ctx->r13);
    // 0x802C6334: lh          $v1, -0x7390($v1)
    ctx->r3 = MEM_H(ctx->r3, -0X7390);
    // 0x802C6338: bne         $v1, $zero, L_802C6348
    if (ctx->r3 != 0) {
        // 0x802C633C: andi        $t4, $v1, 0x1
        ctx->r12 = ctx->r3 & 0X1;
            goto L_802C6348;
    }
    // 0x802C633C: andi        $t4, $v1, 0x1
    ctx->r12 = ctx->r3 & 0X1;
    // 0x802C6340: b           L_802C635C
    // 0x802C6344: sh          $s0, 0x0($v0)
    MEM_H(0X0, ctx->r2) = ctx->r16;
        goto L_802C635C;
    // 0x802C6344: sh          $s0, 0x0($v0)
    MEM_H(0X0, ctx->r2) = ctx->r16;
L_802C6348:
    // 0x802C6348: beql        $t4, $zero, L_802C635C
    if (ctx->r12 == 0) {
        // 0x802C634C: sh          $zero, 0x0($v0)
        MEM_H(0X0, ctx->r2) = 0;
            goto L_802C635C;
    }
    goto skip_4;
    // 0x802C634C: sh          $zero, 0x0($v0)
    MEM_H(0X0, ctx->r2) = 0;
    skip_4:
    // 0x802C6350: b           L_802C635C
    // 0x802C6354: sh          $s3, 0x0($v0)
    MEM_H(0X0, ctx->r2) = ctx->r19;
        goto L_802C635C;
    // 0x802C6354: sh          $s3, 0x0($v0)
    MEM_H(0X0, ctx->r2) = ctx->r19;
    // 0x802C6358: sh          $zero, 0x0($v0)
    MEM_H(0X0, ctx->r2) = 0;
L_802C635C:
    // 0x802C635C: beql        $a1, $zero, L_802C6394
    if (ctx->r5 == 0) {
        // 0x802C6360: andi        $t7, $a0, 0x200
        ctx->r15 = ctx->r4 & 0X200;
            goto L_802C6394;
    }
    goto skip_5;
    // 0x802C6360: andi        $t7, $a0, 0x200
    ctx->r15 = ctx->r4 & 0X200;
    skip_5:
    // 0x802C6364: bnel        $s3, $t0, L_802C6394
    if (ctx->r19 != ctx->r8) {
        // 0x802C6368: andi        $t7, $a0, 0x200
        ctx->r15 = ctx->r4 & 0X200;
            goto L_802C6394;
    }
    goto skip_6;
    // 0x802C6368: andi        $t7, $a0, 0x200
    ctx->r15 = ctx->r4 & 0X200;
    skip_6:
    // 0x802C636C: lhu         $t6, 0x0($s6)
    ctx->r14 = MEM_HU(ctx->r22, 0X0);
    // 0x802C6370: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x802C6374: andi        $t8, $t6, 0x400
    ctx->r24 = ctx->r14 & 0X400;
    // 0x802C6378: beq         $t8, $zero, L_802C638C
    if (ctx->r24 == 0) {
        // 0x802C637C: nop
    
            goto L_802C638C;
    }
    // 0x802C637C: nop

    // 0x802C6380: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x802C6384: b           L_802C6390
    // 0x802C6388: sh          $s3, -0x549C($at)
    MEM_H(-0X549C, ctx->r1) = ctx->r19;
        goto L_802C6390;
    // 0x802C6388: sh          $s3, -0x549C($at)
    MEM_H(-0X549C, ctx->r1) = ctx->r19;
L_802C638C:
    // 0x802C638C: sh          $zero, -0x549C($at)
    MEM_H(-0X549C, ctx->r1) = 0;
L_802C6390:
    // 0x802C6390: andi        $t7, $a0, 0x200
    ctx->r15 = ctx->r4 & 0X200;
L_802C6394:
    // 0x802C6394: beq         $t7, $zero, L_802C6488
    if (ctx->r15 == 0) {
        // 0x802C6398: sw          $zero, 0x0($s1)
        MEM_W(0X0, ctx->r17) = 0;
            goto L_802C6488;
    }
    // 0x802C6398: sw          $zero, 0x0($s1)
    MEM_W(0X0, ctx->r17) = 0;
    // 0x802C639C: sltiu       $at, $a2, 0x5
    ctx->r1 = ctx->r6 < 0X5 ? 1 : 0;
    // 0x802C63A0: beq         $at, $zero, L_802C646C
    if (ctx->r1 == 0) {
        // 0x802C63A4: or          $a1, $s3, $zero
        ctx->r5 = ctx->r19 | 0;
            goto L_802C646C;
    }
    // 0x802C63A4: or          $a1, $s3, $zero
    ctx->r5 = ctx->r19 | 0;
    // 0x802C63A8: sll         $t9, $a2, 2
    ctx->r25 = S32(ctx->r6 << 2);
    // 0x802C63AC: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C63B0: addu        $at, $at, $t9
    gpr jr_addend_802C63B8 = ctx->r25;
    ctx->r1 = ADD32(ctx->r1, ctx->r25);
    // 0x802C63B4: lw          $t9, -0x73E4($at)
    ctx->r25 = ADD32(ctx->r1, -0X73E4);
    // 0x802C63B8: jr          $t9
    // 0x802C63BC: nop

    switch (jr_addend_802C63B8 >> 2) {
        case 0: goto L_802C63C0; break;
        case 1: goto L_802C6400; break;
        case 2: goto L_802C6424; break;
        case 3: goto L_802C643C; break;
        case 4: goto L_802C6454; break;
        default: switch_error(__func__, 0x802C63B8, 0x802C8C1C);
    }
    // 0x802C63BC: nop

L_802C63C0:
    // 0x802C63C0: beq         $a3, $zero, L_802C63D0
    if (ctx->r7 == 0) {
        // 0x802C63C4: addu        $v1, $s7, $s4
        ctx->r3 = ADD32(ctx->r23, ctx->r20);
            goto L_802C63D0;
    }
    // 0x802C63C4: addu        $v1, $s7, $s4
    ctx->r3 = ADD32(ctx->r23, ctx->r20);
    // 0x802C63C8: b           L_802C6470
    // 0x802C63CC: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
        goto L_802C6470;
    // 0x802C63CC: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
L_802C63D0:
    // 0x802C63D0: lw          $t2, 0x0($v1)
    ctx->r10 = MEM_W(ctx->r3, 0X0);
    // 0x802C63D4: lui         $t3, 0x802D
    ctx->r11 = S32(0X802D << 16);
    // 0x802C63D8: addiu       $t3, $t3, -0x73A0
    ctx->r11 = ADD32(ctx->r11, -0X73A0);
    // 0x802C63DC: addiu       $t1, $t2, -0x1
    ctx->r9 = ADD32(ctx->r10, -0X1);
    // 0x802C63E0: sw          $t1, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r9;
    // 0x802C63E4: bgez        $t1, L_802C63F4
    if (SIGNED(ctx->r9) >= 0) {
        // 0x802C63E8: addu        $v0, $s4, $t3
        ctx->r2 = ADD32(ctx->r20, ctx->r11);
            goto L_802C63F4;
    }
    // 0x802C63E8: addu        $v0, $s4, $t3
    ctx->r2 = ADD32(ctx->r20, ctx->r11);
    // 0x802C63EC: addiu       $t4, $zero, 0x3
    ctx->r12 = ADD32(0, 0X3);
    // 0x802C63F0: sw          $t4, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r12;
L_802C63F4:
    // 0x802C63F4: addiu       $t6, $zero, 0x200
    ctx->r14 = ADD32(0, 0X200);
    // 0x802C63F8: b           L_802C6470
    // 0x802C63FC: sw          $t6, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r14;
        goto L_802C6470;
    // 0x802C63FC: sw          $t6, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r14;
L_802C6400:
    // 0x802C6400: lui         $t8, 0x800E
    ctx->r24 = S32(0X800E << 16);
    // 0x802C6404: addiu       $t8, $t8, -0x5638
    ctx->r24 = ADD32(ctx->r24, -0X5638);
    // 0x802C6408: addu        $v0, $s4, $t8
    ctx->r2 = ADD32(ctx->r20, ctx->r24);
    // 0x802C640C: lw          $t7, 0x0($v0)
    ctx->r15 = MEM_W(ctx->r2, 0X0);
    // 0x802C6410: addiu       $t9, $t7, -0x1
    ctx->r25 = ADD32(ctx->r15, -0X1);
    // 0x802C6414: bgez        $t9, L_802C6470
    if (SIGNED(ctx->r25) >= 0) {
        // 0x802C6418: sw          $t9, 0x0($v0)
        MEM_W(0X0, ctx->r2) = ctx->r25;
            goto L_802C6470;
    }
    // 0x802C6418: sw          $t9, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r25;
    // 0x802C641C: b           L_802C6470
    // 0x802C6420: sw          $s3, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r19;
        goto L_802C6470;
    // 0x802C6420: sw          $s3, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r19;
L_802C6424:
    // 0x802C6424: sw          $s3, 0x0($s1)
    MEM_W(0X0, ctx->r17) = ctx->r19;
    // 0x802C6428: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x802C642C: jal         0x802C676C
    // 0x802C6430: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_i2_802C676C(rdram, ctx);
        goto after_8;
    // 0x802C6430: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_8:
    // 0x802C6434: b           L_802C6470
    // 0x802C6438: or          $a1, $v0, $zero
    ctx->r5 = ctx->r2 | 0;
        goto L_802C6470;
    // 0x802C6438: or          $a1, $v0, $zero
    ctx->r5 = ctx->r2 | 0;
L_802C643C:
    // 0x802C643C: sw          $s3, 0x0($s1)
    MEM_W(0X0, ctx->r17) = ctx->r19;
    // 0x802C6440: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x802C6444: jal         0x802C676C
    // 0x802C6448: or          $a1, $s3, $zero
    ctx->r5 = ctx->r19 | 0;
    func_i2_802C676C(rdram, ctx);
        goto after_9;
    // 0x802C6448: or          $a1, $s3, $zero
    ctx->r5 = ctx->r19 | 0;
    after_9:
    // 0x802C644C: b           L_802C6470
    // 0x802C6450: or          $a1, $v0, $zero
    ctx->r5 = ctx->r2 | 0;
        goto L_802C6470;
    // 0x802C6450: or          $a1, $v0, $zero
    ctx->r5 = ctx->r2 | 0;
L_802C6454:
    // 0x802C6454: sw          $s3, 0x0($s1)
    MEM_W(0X0, ctx->r17) = ctx->r19;
    // 0x802C6458: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x802C645C: jal         0x802C676C
    // 0x802C6460: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    func_i2_802C676C(rdram, ctx);
        goto after_10;
    // 0x802C6460: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    after_10:
    // 0x802C6464: b           L_802C6470
    // 0x802C6468: or          $a1, $v0, $zero
    ctx->r5 = ctx->r2 | 0;
        goto L_802C6470;
    // 0x802C6468: or          $a1, $v0, $zero
    ctx->r5 = ctx->r2 | 0;
L_802C646C:
    // 0x802C646C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
L_802C6470:
    // 0x802C6470: beq         $a1, $zero, L_802C6574
    if (ctx->r5 == 0) {
        // 0x802C6474: addiu       $a0, $zero, 0x10
        ctx->r4 = ADD32(0, 0X10);
            goto L_802C6574;
    }
    // 0x802C6474: addiu       $a0, $zero, 0x10
    ctx->r4 = ADD32(0, 0X10);
    // 0x802C6478: jal         0x800C37F4
    // 0x802C647C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_11;
    // 0x802C647C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_11:
    // 0x802C6480: b           L_802C6578
    // 0x802C6484: lw          $t5, 0x0($s1)
    ctx->r13 = MEM_W(ctx->r17, 0X0);
        goto L_802C6578;
    // 0x802C6484: lw          $t5, 0x0($s1)
    ctx->r13 = MEM_W(ctx->r17, 0X0);
L_802C6488:
    // 0x802C6488: andi        $t1, $a0, 0x100
    ctx->r9 = ctx->r4 & 0X100;
    // 0x802C648C: beq         $t1, $zero, L_802C6574
    if (ctx->r9 == 0) {
        // 0x802C6490: sltiu       $at, $a2, 0x5
        ctx->r1 = ctx->r6 < 0X5 ? 1 : 0;
            goto L_802C6574;
    }
    // 0x802C6490: sltiu       $at, $a2, 0x5
    ctx->r1 = ctx->r6 < 0X5 ? 1 : 0;
    // 0x802C6494: beq         $at, $zero, L_802C6560
    if (ctx->r1 == 0) {
        // 0x802C6498: or          $a1, $s3, $zero
        ctx->r5 = ctx->r19 | 0;
            goto L_802C6560;
    }
    // 0x802C6498: or          $a1, $s3, $zero
    ctx->r5 = ctx->r19 | 0;
    // 0x802C649C: sll         $t3, $a2, 2
    ctx->r11 = S32(ctx->r6 << 2);
    // 0x802C64A0: lui         $at, 0x802D
    ctx->r1 = S32(0X802D << 16);
    // 0x802C64A4: addu        $at, $at, $t3
    gpr jr_addend_802C64AC = ctx->r11;
    ctx->r1 = ADD32(ctx->r1, ctx->r11);
    // 0x802C64A8: lw          $t3, -0x73D0($at)
    ctx->r11 = ADD32(ctx->r1, -0X73D0);
    // 0x802C64AC: jr          $t3
    // 0x802C64B0: nop

    switch (jr_addend_802C64AC >> 2) {
        case 0: goto L_802C64B4; break;
        case 1: goto L_802C64F0; break;
        case 2: goto L_802C6518; break;
        case 3: goto L_802C6530; break;
        case 4: goto L_802C6548; break;
        default: switch_error(__func__, 0x802C64AC, 0x802C8C30);
    }
    // 0x802C64B0: nop

L_802C64B4:
    // 0x802C64B4: beq         $a3, $zero, L_802C64C4
    if (ctx->r7 == 0) {
        // 0x802C64B8: addu        $v1, $s7, $s4
        ctx->r3 = ADD32(ctx->r23, ctx->r20);
            goto L_802C64C4;
    }
    // 0x802C64B8: addu        $v1, $s7, $s4
    ctx->r3 = ADD32(ctx->r23, ctx->r20);
    // 0x802C64BC: b           L_802C6564
    // 0x802C64C0: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
        goto L_802C6564;
    // 0x802C64C0: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
L_802C64C4:
    // 0x802C64C4: lw          $t5, 0x0($v1)
    ctx->r13 = MEM_W(ctx->r3, 0X0);
    // 0x802C64C8: lui         $t6, 0x802D
    ctx->r14 = S32(0X802D << 16);
    // 0x802C64CC: addiu       $t6, $t6, -0x73A0
    ctx->r14 = ADD32(ctx->r14, -0X73A0);
    // 0x802C64D0: addiu       $t4, $t5, 0x1
    ctx->r12 = ADD32(ctx->r13, 0X1);
    // 0x802C64D4: sw          $t4, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r12;
    // 0x802C64D8: bne         $fp, $t4, L_802C64E4
    if (ctx->r30 != ctx->r12) {
        // 0x802C64DC: addu        $v0, $s4, $t6
        ctx->r2 = ADD32(ctx->r20, ctx->r14);
            goto L_802C64E4;
    }
    // 0x802C64DC: addu        $v0, $s4, $t6
    ctx->r2 = ADD32(ctx->r20, ctx->r14);
    // 0x802C64E0: sw          $zero, 0x0($v1)
    MEM_W(0X0, ctx->r3) = 0;
L_802C64E4:
    // 0x802C64E4: addiu       $t7, $zero, 0x200
    ctx->r15 = ADD32(0, 0X200);
    // 0x802C64E8: b           L_802C6564
    // 0x802C64EC: sw          $t7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r15;
        goto L_802C6564;
    // 0x802C64EC: sw          $t7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r15;
L_802C64F0:
    // 0x802C64F0: lui         $t9, 0x800E
    ctx->r25 = S32(0X800E << 16);
    // 0x802C64F4: addiu       $t9, $t9, -0x5638
    ctx->r25 = ADD32(ctx->r25, -0X5638);
    // 0x802C64F8: addu        $v0, $s4, $t9
    ctx->r2 = ADD32(ctx->r20, ctx->r25);
    // 0x802C64FC: lw          $t2, 0x0($v0)
    ctx->r10 = MEM_W(ctx->r2, 0X0);
    // 0x802C6500: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x802C6504: addiu       $t1, $t2, 0x1
    ctx->r9 = ADD32(ctx->r10, 0X1);
    // 0x802C6508: bne         $t1, $at, L_802C6564
    if (ctx->r9 != ctx->r1) {
        // 0x802C650C: sw          $t1, 0x0($v0)
        MEM_W(0X0, ctx->r2) = ctx->r9;
            goto L_802C6564;
    }
    // 0x802C650C: sw          $t1, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r9;
    // 0x802C6510: b           L_802C6564
    // 0x802C6514: sw          $zero, 0x0($v0)
    MEM_W(0X0, ctx->r2) = 0;
        goto L_802C6564;
    // 0x802C6514: sw          $zero, 0x0($v0)
    MEM_W(0X0, ctx->r2) = 0;
L_802C6518:
    // 0x802C6518: sw          $s3, 0x0($s1)
    MEM_W(0X0, ctx->r17) = ctx->r19;
    // 0x802C651C: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x802C6520: jal         0x802C67E4
    // 0x802C6524: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_i2_802C67E4(rdram, ctx);
        goto after_12;
    // 0x802C6524: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_12:
    // 0x802C6528: b           L_802C6564
    // 0x802C652C: or          $a1, $v0, $zero
    ctx->r5 = ctx->r2 | 0;
        goto L_802C6564;
    // 0x802C652C: or          $a1, $v0, $zero
    ctx->r5 = ctx->r2 | 0;
L_802C6530:
    // 0x802C6530: sw          $s3, 0x0($s1)
    MEM_W(0X0, ctx->r17) = ctx->r19;
    // 0x802C6534: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x802C6538: jal         0x802C67E4
    // 0x802C653C: or          $a1, $s3, $zero
    ctx->r5 = ctx->r19 | 0;
    func_i2_802C67E4(rdram, ctx);
        goto after_13;
    // 0x802C653C: or          $a1, $s3, $zero
    ctx->r5 = ctx->r19 | 0;
    after_13:
    // 0x802C6540: b           L_802C6564
    // 0x802C6544: or          $a1, $v0, $zero
    ctx->r5 = ctx->r2 | 0;
        goto L_802C6564;
    // 0x802C6544: or          $a1, $v0, $zero
    ctx->r5 = ctx->r2 | 0;
L_802C6548:
    // 0x802C6548: sw          $s3, 0x0($s1)
    MEM_W(0X0, ctx->r17) = ctx->r19;
    // 0x802C654C: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x802C6550: jal         0x802C67E4
    // 0x802C6554: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    func_i2_802C67E4(rdram, ctx);
        goto after_14;
    // 0x802C6554: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    after_14:
    // 0x802C6558: b           L_802C6564
    // 0x802C655C: or          $a1, $v0, $zero
    ctx->r5 = ctx->r2 | 0;
        goto L_802C6564;
    // 0x802C655C: or          $a1, $v0, $zero
    ctx->r5 = ctx->r2 | 0;
L_802C6560:
    // 0x802C6560: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
L_802C6564:
    // 0x802C6564: beq         $a1, $zero, L_802C6574
    if (ctx->r5 == 0) {
        // 0x802C6568: addiu       $a0, $zero, 0x10
        ctx->r4 = ADD32(0, 0X10);
            goto L_802C6574;
    }
    // 0x802C6568: addiu       $a0, $zero, 0x10
    ctx->r4 = ADD32(0, 0X10);
    // 0x802C656C: jal         0x800C37F4
    // 0x802C6570: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_15;
    // 0x802C6570: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_15:
L_802C6574:
    // 0x802C6574: lw          $t5, 0x0($s1)
    ctx->r13 = MEM_W(ctx->r17, 0X0);
L_802C6578:
    // 0x802C6578: beq         $t5, $zero, L_802C6588
    if (ctx->r13 == 0) {
        // 0x802C657C: addiu       $t4, $zero, -0x3
        ctx->r12 = ADD32(0, -0X3);
            goto L_802C6588;
    }
    // 0x802C657C: addiu       $t4, $zero, -0x3
    ctx->r12 = ADD32(0, -0X3);
    // 0x802C6580: b           L_802C6690
    // 0x802C6584: sw          $t4, 0x0($s5)
    MEM_W(0X0, ctx->r21) = ctx->r12;
        goto L_802C6690;
    // 0x802C6584: sw          $t4, 0x0($s5)
    MEM_W(0X0, ctx->r21) = ctx->r12;
L_802C6588:
    // 0x802C6588: lw          $t6, 0x0($s5)
    ctx->r14 = MEM_W(ctx->r21, 0X0);
    // 0x802C658C: addiu       $t8, $t6, 0x1
    ctx->r24 = ADD32(ctx->r14, 0X1);
    // 0x802C6590: slti        $at, $t8, 0x4
    ctx->r1 = SIGNED(ctx->r24) < 0X4 ? 1 : 0;
    // 0x802C6594: bne         $at, $zero, L_802C6690
    if (ctx->r1 != 0) {
        // 0x802C6598: sw          $t8, 0x0($s5)
        MEM_W(0X0, ctx->r21) = ctx->r24;
            goto L_802C6690;
    }
    // 0x802C6598: sw          $t8, 0x0($s5)
    MEM_W(0X0, ctx->r21) = ctx->r24;
    // 0x802C659C: lhu         $v0, 0x0($s6)
    ctx->r2 = MEM_HU(ctx->r22, 0X0);
    // 0x802C65A0: sw          $zero, 0x0($s5)
    MEM_W(0X0, ctx->r21) = 0;
    // 0x802C65A4: andi        $t9, $v0, 0x200
    ctx->r25 = ctx->r2 & 0X200;
    // 0x802C65A8: beq         $t9, $zero, L_802C6620
    if (ctx->r25 == 0) {
        // 0x802C65AC: andi        $t2, $v0, 0x100
        ctx->r10 = ctx->r2 & 0X100;
            goto L_802C6620;
    }
    // 0x802C65AC: andi        $t2, $v0, 0x100
    ctx->r10 = ctx->r2 & 0X100;
    // 0x802C65B0: lw          $v0, 0x0($s2)
    ctx->r2 = MEM_W(ctx->r18, 0X0);
    // 0x802C65B4: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x802C65B8: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x802C65BC: beq         $v0, $at, L_802C65DC
    if (ctx->r2 == ctx->r1) {
        // 0x802C65C0: addiu       $at, $zero, 0x3
        ctx->r1 = ADD32(0, 0X3);
            goto L_802C65DC;
    }
    // 0x802C65C0: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x802C65C4: beq         $v0, $at, L_802C65EC
    if (ctx->r2 == ctx->r1) {
        // 0x802C65C8: or          $a0, $s0, $zero
        ctx->r4 = ctx->r16 | 0;
            goto L_802C65EC;
    }
    // 0x802C65C8: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x802C65CC: beq         $v0, $fp, L_802C65FC
    if (ctx->r2 == ctx->r30) {
        // 0x802C65D0: or          $a0, $s0, $zero
        ctx->r4 = ctx->r16 | 0;
            goto L_802C65FC;
    }
    // 0x802C65D0: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x802C65D4: b           L_802C6608
    // 0x802C65D8: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
        goto L_802C6608;
    // 0x802C65D8: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
L_802C65DC:
    // 0x802C65DC: jal         0x802C676C
    // 0x802C65E0: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_i2_802C676C(rdram, ctx);
        goto after_16;
    // 0x802C65E0: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_16:
    // 0x802C65E4: b           L_802C6608
    // 0x802C65E8: or          $a1, $v0, $zero
    ctx->r5 = ctx->r2 | 0;
        goto L_802C6608;
    // 0x802C65E8: or          $a1, $v0, $zero
    ctx->r5 = ctx->r2 | 0;
L_802C65EC:
    // 0x802C65EC: jal         0x802C676C
    // 0x802C65F0: or          $a1, $s3, $zero
    ctx->r5 = ctx->r19 | 0;
    func_i2_802C676C(rdram, ctx);
        goto after_17;
    // 0x802C65F0: or          $a1, $s3, $zero
    ctx->r5 = ctx->r19 | 0;
    after_17:
    // 0x802C65F4: b           L_802C6608
    // 0x802C65F8: or          $a1, $v0, $zero
    ctx->r5 = ctx->r2 | 0;
        goto L_802C6608;
    // 0x802C65F8: or          $a1, $v0, $zero
    ctx->r5 = ctx->r2 | 0;
L_802C65FC:
    // 0x802C65FC: jal         0x802C676C
    // 0x802C6600: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    func_i2_802C676C(rdram, ctx);
        goto after_18;
    // 0x802C6600: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    after_18:
    // 0x802C6604: or          $a1, $v0, $zero
    ctx->r5 = ctx->r2 | 0;
L_802C6608:
    // 0x802C6608: beq         $a1, $zero, L_802C6690
    if (ctx->r5 == 0) {
        // 0x802C660C: addiu       $a0, $zero, 0x10
        ctx->r4 = ADD32(0, 0X10);
            goto L_802C6690;
    }
    // 0x802C660C: addiu       $a0, $zero, 0x10
    ctx->r4 = ADD32(0, 0X10);
    // 0x802C6610: jal         0x800C37F4
    // 0x802C6614: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_19;
    // 0x802C6614: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_19:
    // 0x802C6618: b           L_802C6694
    // 0x802C661C: lw          $t1, 0x0($s2)
    ctx->r9 = MEM_W(ctx->r18, 0X0);
        goto L_802C6694;
    // 0x802C661C: lw          $t1, 0x0($s2)
    ctx->r9 = MEM_W(ctx->r18, 0X0);
L_802C6620:
    // 0x802C6620: beql        $t2, $zero, L_802C6694
    if (ctx->r10 == 0) {
        // 0x802C6624: lw          $t1, 0x0($s2)
        ctx->r9 = MEM_W(ctx->r18, 0X0);
            goto L_802C6694;
    }
    goto skip_7;
    // 0x802C6624: lw          $t1, 0x0($s2)
    ctx->r9 = MEM_W(ctx->r18, 0X0);
    skip_7:
    // 0x802C6628: lw          $v0, 0x0($s2)
    ctx->r2 = MEM_W(ctx->r18, 0X0);
    // 0x802C662C: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x802C6630: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x802C6634: beq         $v0, $at, L_802C6654
    if (ctx->r2 == ctx->r1) {
        // 0x802C6638: addiu       $at, $zero, 0x3
        ctx->r1 = ADD32(0, 0X3);
            goto L_802C6654;
    }
    // 0x802C6638: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x802C663C: beq         $v0, $at, L_802C6664
    if (ctx->r2 == ctx->r1) {
        // 0x802C6640: or          $a0, $s0, $zero
        ctx->r4 = ctx->r16 | 0;
            goto L_802C6664;
    }
    // 0x802C6640: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x802C6644: beq         $v0, $fp, L_802C6674
    if (ctx->r2 == ctx->r30) {
        // 0x802C6648: or          $a0, $s0, $zero
        ctx->r4 = ctx->r16 | 0;
            goto L_802C6674;
    }
    // 0x802C6648: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x802C664C: b           L_802C6680
    // 0x802C6650: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
        goto L_802C6680;
    // 0x802C6650: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
L_802C6654:
    // 0x802C6654: jal         0x802C67E4
    // 0x802C6658: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_i2_802C67E4(rdram, ctx);
        goto after_20;
    // 0x802C6658: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_20:
    // 0x802C665C: b           L_802C6680
    // 0x802C6660: or          $a1, $v0, $zero
    ctx->r5 = ctx->r2 | 0;
        goto L_802C6680;
    // 0x802C6660: or          $a1, $v0, $zero
    ctx->r5 = ctx->r2 | 0;
L_802C6664:
    // 0x802C6664: jal         0x802C67E4
    // 0x802C6668: or          $a1, $s3, $zero
    ctx->r5 = ctx->r19 | 0;
    func_i2_802C67E4(rdram, ctx);
        goto after_21;
    // 0x802C6668: or          $a1, $s3, $zero
    ctx->r5 = ctx->r19 | 0;
    after_21:
    // 0x802C666C: b           L_802C6680
    // 0x802C6670: or          $a1, $v0, $zero
    ctx->r5 = ctx->r2 | 0;
        goto L_802C6680;
    // 0x802C6670: or          $a1, $v0, $zero
    ctx->r5 = ctx->r2 | 0;
L_802C6674:
    // 0x802C6674: jal         0x802C67E4
    // 0x802C6678: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    func_i2_802C67E4(rdram, ctx);
        goto after_22;
    // 0x802C6678: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    after_22:
    // 0x802C667C: or          $a1, $v0, $zero
    ctx->r5 = ctx->r2 | 0;
L_802C6680:
    // 0x802C6680: beq         $a1, $zero, L_802C6690
    if (ctx->r5 == 0) {
        // 0x802C6684: addiu       $a0, $zero, 0x10
        ctx->r4 = ADD32(0, 0X10);
            goto L_802C6690;
    }
    // 0x802C6684: addiu       $a0, $zero, 0x10
    ctx->r4 = ADD32(0, 0X10);
    // 0x802C6688: jal         0x800C37F4
    // 0x802C668C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_23;
    // 0x802C668C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_23:
L_802C6690:
    // 0x802C6690: lw          $t1, 0x0($s2)
    ctx->r9 = MEM_W(ctx->r18, 0X0);
L_802C6694:
    // 0x802C6694: lui         $t0, 0x801D
    ctx->r8 = S32(0X801D << 16);
    // 0x802C6698: addiu       $s0, $s0, 0x1
    ctx->r16 = ADD32(ctx->r16, 0X1);
    // 0x802C669C: bne         $t1, $zero, L_802C6724
    if (ctx->r9 != 0) {
        // 0x802C66A0: lh          $t0, -0x19F4($t0)
        ctx->r8 = MEM_H(ctx->r8, -0X19F4);
            goto L_802C6724;
    }
    // 0x802C66A0: lh          $t0, -0x19F4($t0)
    ctx->r8 = MEM_H(ctx->r8, -0X19F4);
    // 0x802C66A4: addu        $t6, $s7, $s4
    ctx->r14 = ADD32(ctx->r23, ctx->r20);
    // 0x802C66A8: lw          $t8, 0x0($t6)
    ctx->r24 = MEM_W(ctx->r14, 0X0);
    // 0x802C66AC: lw          $t3, 0x48($sp)
    ctx->r11 = MEM_W(ctx->r29, 0X48);
    // 0x802C66B0: lui         $a0, 0x802D
    ctx->r4 = S32(0X802D << 16);
    // 0x802C66B4: sll         $t7, $t8, 2
    ctx->r15 = S32(ctx->r24 << 2);
    // 0x802C66B8: sll         $t5, $t3, 2
    ctx->r13 = S32(ctx->r11 << 2);
    // 0x802C66BC: addu        $a0, $a0, $t7
    ctx->r4 = ADD32(ctx->r4, ctx->r15);
    // 0x802C66C0: subu        $t5, $t5, $t3
    ctx->r13 = SUB32(ctx->r13, ctx->r11);
    // 0x802C66C4: lw          $a0, -0x7428($a0)
    ctx->r4 = MEM_W(ctx->r4, -0X7428);
    // 0x802C66C8: sll         $t5, $t5, 3
    ctx->r13 = S32(ctx->r13 << 3);
    // 0x802C66CC: subu        $t5, $t5, $t3
    ctx->r13 = SUB32(ctx->r13, ctx->r11);
    // 0x802C66D0: sll         $t5, $t5, 3
    ctx->r13 = S32(ctx->r13 << 3);
    // 0x802C66D4: addu        $t5, $t5, $t3
    ctx->r13 = ADD32(ctx->r13, ctx->r11);
    // 0x802C66D8: sll         $t9, $a0, 3
    ctx->r25 = S32(ctx->r4 << 3);
    // 0x802C66DC: sll         $t5, $t5, 2
    ctx->r13 = S32(ctx->r13 << 2);
    // 0x802C66E0: lui         $t2, 0x800E
    ctx->r10 = S32(0X800E << 16);
    // 0x802C66E4: subu        $t9, $t9, $a0
    ctx->r25 = SUB32(ctx->r25, ctx->r4);
    // 0x802C66E8: lui         $t4, 0x8019
    ctx->r12 = S32(0X8019 << 16);
    // 0x802C66EC: sll         $t9, $t9, 1
    ctx->r25 = S32(ctx->r25 << 1);
    // 0x802C66F0: addiu       $t2, $t2, -0x56B0
    ctx->r10 = ADD32(ctx->r10, -0X56B0);
    // 0x802C66F4: subu        $t5, $t5, $t3
    ctx->r13 = SUB32(ctx->r13, ctx->r11);
    // 0x802C66F8: sll         $t5, $t5, 3
    ctx->r13 = S32(ctx->r13 << 3);
    // 0x802C66FC: addiu       $t4, $t4, 0x2690
    ctx->r12 = ADD32(ctx->r12, 0X2690);
    // 0x802C6700: addu        $v1, $t9, $t2
    ctx->r3 = ADD32(ctx->r25, ctx->r10);
    // 0x802C6704: addu        $v0, $t5, $t4
    ctx->r2 = ADD32(ctx->r13, ctx->r12);
    // 0x802C6708: lb          $t1, 0xB($v1)
    ctx->r9 = MEM_B(ctx->r3, 0XB);
    // 0x802C670C: lb          $t3, 0xC($v1)
    ctx->r11 = MEM_B(ctx->r3, 0XC);
    // 0x802C6710: lb          $t5, 0xD($v1)
    ctx->r13 = MEM_B(ctx->r3, 0XD);
    // 0x802C6714: sw          $a0, 0xB68($v0)
    MEM_W(0XB68, ctx->r2) = ctx->r4;
    // 0x802C6718: sw          $t1, 0xB6C($v0)
    MEM_W(0XB6C, ctx->r2) = ctx->r9;
    // 0x802C671C: sw          $t3, 0xB70($v0)
    MEM_W(0XB70, ctx->r2) = ctx->r11;
    // 0x802C6720: sw          $t5, 0xB74($v0)
    MEM_W(0XB74, ctx->r2) = ctx->r13;
L_802C6724:
    // 0x802C6724: slt         $at, $s0, $t0
    ctx->r1 = SIGNED(ctx->r16) < SIGNED(ctx->r8) ? 1 : 0;
    // 0x802C6728: addiu       $s4, $s4, 0x4
    ctx->r20 = ADD32(ctx->r20, 0X4);
    // 0x802C672C: bne         $at, $zero, L_802C5E80
    if (ctx->r1 != 0) {
        // 0x802C6730: addiu       $s2, $s2, 0x4
        ctx->r18 = ADD32(ctx->r18, 0X4);
            goto L_802C5E80;
    }
    // 0x802C6730: addiu       $s2, $s2, 0x4
    ctx->r18 = ADD32(ctx->r18, 0X4);
L_802C6734:
    // 0x802C6734: jal         0x80047E50
    // 0x802C6738: nop

    SysUtils_Rand(rdram, ctx);
        goto after_24;
    // 0x802C6738: nop

    after_24:
    // 0x802C673C: lw          $ra, 0x3C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X3C);
    // 0x802C6740: lw          $s0, 0x18($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X18);
    // 0x802C6744: lw          $s1, 0x1C($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X1C);
    // 0x802C6748: lw          $s2, 0x20($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X20);
    // 0x802C674C: lw          $s3, 0x24($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X24);
    // 0x802C6750: lw          $s4, 0x28($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X28);
    // 0x802C6754: lw          $s5, 0x2C($sp)
    ctx->r21 = MEM_W(ctx->r29, 0X2C);
    // 0x802C6758: lw          $s6, 0x30($sp)
    ctx->r22 = MEM_W(ctx->r29, 0X30);
    // 0x802C675C: lw          $s7, 0x34($sp)
    ctx->r23 = MEM_W(ctx->r29, 0X34);
    // 0x802C6760: lw          $fp, 0x38($sp)
    ctx->r30 = MEM_W(ctx->r29, 0X38);
    // 0x802C6764: jr          $ra
    // 0x802C6768: addiu       $sp, $sp, 0x58
    ctx->r29 = ADD32(ctx->r29, 0X58);
    return;
    // 0x802C6768: addiu       $sp, $sp, 0x58
    ctx->r29 = ADD32(ctx->r29, 0X58);
;}
RECOMP_FUNC void func_i2_802C676C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C676C: sll         $t6, $a0, 2
    ctx->r14 = S32(ctx->r4 << 2);
    // 0x802C6770: lui         $t7, 0x800E
    ctx->r15 = S32(0X800E << 16);
    // 0x802C6774: addu        $t7, $t7, $t6
    ctx->r15 = ADD32(ctx->r15, ctx->r14);
    // 0x802C6778: lw          $t7, -0x5640($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X5640);
    // 0x802C677C: lui         $v0, 0x802D
    ctx->r2 = S32(0X802D << 16);
    // 0x802C6780: sll         $t9, $a0, 3
    ctx->r25 = S32(ctx->r4 << 3);
    // 0x802C6784: sll         $t8, $t7, 2
    ctx->r24 = S32(ctx->r15 << 2);
    // 0x802C6788: addu        $v0, $v0, $t8
    ctx->r2 = ADD32(ctx->r2, ctx->r24);
    // 0x802C678C: lw          $v0, -0x7428($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X7428);
    // 0x802C6790: subu        $t9, $t9, $a0
    ctx->r25 = SUB32(ctx->r25, ctx->r4);
    // 0x802C6794: sll         $t9, $t9, 3
    ctx->r25 = S32(ctx->r25 << 3);
    // 0x802C6798: sll         $t0, $v0, 3
    ctx->r8 = S32(ctx->r2 << 3);
    // 0x802C679C: subu        $t0, $t0, $v0
    ctx->r8 = SUB32(ctx->r8, ctx->r2);
    // 0x802C67A0: sll         $t0, $t0, 1
    ctx->r8 = S32(ctx->r8 << 1);
    // 0x802C67A4: addu        $t1, $t9, $t0
    ctx->r9 = ADD32(ctx->r25, ctx->r8);
    // 0x802C67A8: lui         $t3, 0x801D
    ctx->r11 = S32(0X801D << 16);
    // 0x802C67AC: addiu       $t3, $t3, -0x4D68
    ctx->r11 = ADD32(ctx->r11, -0X4D68);
    // 0x802C67B0: addu        $t2, $t1, $a1
    ctx->r10 = ADD32(ctx->r9, ctx->r5);
    // 0x802C67B4: addu        $a2, $t2, $t3
    ctx->r6 = ADD32(ctx->r10, ctx->r11);
    // 0x802C67B8: lb          $t4, 0xB($a2)
    ctx->r12 = MEM_B(ctx->r6, 0XB);
    // 0x802C67BC: addiu       $v1, $zero, 0x1
    ctx->r3 = ADD32(0, 0X1);
    // 0x802C67C0: addiu       $t5, $t4, -0x1
    ctx->r13 = ADD32(ctx->r12, -0X1);
    // 0x802C67C4: sb          $t5, 0xB($a2)
    MEM_B(0XB, ctx->r6) = ctx->r13;
    // 0x802C67C8: lb          $t6, 0xB($a2)
    ctx->r14 = MEM_B(ctx->r6, 0XB);
    // 0x802C67CC: bgez        $t6, L_802C67DC
    if (SIGNED(ctx->r14) >= 0) {
        // 0x802C67D0: nop
    
            goto L_802C67DC;
    }
    // 0x802C67D0: nop

    // 0x802C67D4: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
    // 0x802C67D8: sb          $zero, 0xB($a2)
    MEM_B(0XB, ctx->r6) = 0;
L_802C67DC:
    // 0x802C67DC: jr          $ra
    // 0x802C67E0: or          $v0, $v1, $zero
    ctx->r2 = ctx->r3 | 0;
    return;
    // 0x802C67E0: or          $v0, $v1, $zero
    ctx->r2 = ctx->r3 | 0;
;}
RECOMP_FUNC void func_i2_802C67E4(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C67E4: sll         $t6, $a0, 2
    ctx->r14 = S32(ctx->r4 << 2);
    // 0x802C67E8: lui         $t7, 0x800E
    ctx->r15 = S32(0X800E << 16);
    // 0x802C67EC: addu        $t7, $t7, $t6
    ctx->r15 = ADD32(ctx->r15, ctx->r14);
    // 0x802C67F0: lw          $t7, -0x5640($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X5640);
    // 0x802C67F4: lui         $v0, 0x802D
    ctx->r2 = S32(0X802D << 16);
    // 0x802C67F8: sll         $t9, $a0, 3
    ctx->r25 = S32(ctx->r4 << 3);
    // 0x802C67FC: sll         $t8, $t7, 2
    ctx->r24 = S32(ctx->r15 << 2);
    // 0x802C6800: addu        $v0, $v0, $t8
    ctx->r2 = ADD32(ctx->r2, ctx->r24);
    // 0x802C6804: lw          $v0, -0x7428($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X7428);
    // 0x802C6808: subu        $t9, $t9, $a0
    ctx->r25 = SUB32(ctx->r25, ctx->r4);
    // 0x802C680C: sll         $t9, $t9, 3
    ctx->r25 = S32(ctx->r25 << 3);
    // 0x802C6810: sll         $t0, $v0, 3
    ctx->r8 = S32(ctx->r2 << 3);
    // 0x802C6814: subu        $t0, $t0, $v0
    ctx->r8 = SUB32(ctx->r8, ctx->r2);
    // 0x802C6818: sll         $t0, $t0, 1
    ctx->r8 = S32(ctx->r8 << 1);
    // 0x802C681C: addu        $t1, $t9, $t0
    ctx->r9 = ADD32(ctx->r25, ctx->r8);
    // 0x802C6820: lui         $t3, 0x801D
    ctx->r11 = S32(0X801D << 16);
    // 0x802C6824: addiu       $t3, $t3, -0x4D68
    ctx->r11 = ADD32(ctx->r11, -0X4D68);
    // 0x802C6828: addu        $t2, $t1, $a1
    ctx->r10 = ADD32(ctx->r9, ctx->r5);
    // 0x802C682C: addu        $a2, $t2, $t3
    ctx->r6 = ADD32(ctx->r10, ctx->r11);
    // 0x802C6830: lb          $t4, 0xB($a2)
    ctx->r12 = MEM_B(ctx->r6, 0XB);
    // 0x802C6834: addiu       $at, $zero, 0xC
    ctx->r1 = ADD32(0, 0XC);
    // 0x802C6838: addiu       $v1, $zero, 0x1
    ctx->r3 = ADD32(0, 0X1);
    // 0x802C683C: addiu       $t5, $t4, 0x1
    ctx->r13 = ADD32(ctx->r12, 0X1);
    // 0x802C6840: sb          $t5, 0xB($a2)
    MEM_B(0XB, ctx->r6) = ctx->r13;
    // 0x802C6844: lb          $t6, 0xB($a2)
    ctx->r14 = MEM_B(ctx->r6, 0XB);
    // 0x802C6848: addiu       $t7, $zero, 0xB
    ctx->r15 = ADD32(0, 0XB);
    // 0x802C684C: bne         $t6, $at, L_802C685C
    if (ctx->r14 != ctx->r1) {
        // 0x802C6850: nop
    
            goto L_802C685C;
    }
    // 0x802C6850: nop

    // 0x802C6854: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
    // 0x802C6858: sb          $t7, 0xB($a2)
    MEM_B(0XB, ctx->r6) = ctx->r15;
L_802C685C:
    // 0x802C685C: jr          $ra
    // 0x802C6860: or          $v0, $v1, $zero
    ctx->r2 = ctx->r3 | 0;
    return;
    // 0x802C6860: or          $v0, $v1, $zero
    ctx->r2 = ctx->r3 | 0;
;}
RECOMP_FUNC void func_i2_802C6864(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C6864: lui         $a2, 0x801D
    ctx->r6 = S32(0X801D << 16);
    // 0x802C6868: addiu       $a2, $a2, -0x19F8
    ctx->r6 = ADD32(ctx->r6, -0X19F8);
    // 0x802C686C: lh          $t6, 0x4($a2)
    ctx->r14 = MEM_H(ctx->r6, 0X4);
    // 0x802C6870: addiu       $sp, $sp, -0x48
    ctx->r29 = ADD32(ctx->r29, -0X48);
    // 0x802C6874: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x802C6878: addiu       $ra, $zero, 0x1
    ctx->r31 = ADD32(0, 0X1);
    // 0x802C687C: or          $a1, $a0, $zero
    ctx->r5 = ctx->r4 | 0;
    // 0x802C6880: bne         $ra, $t6, L_802C6890
    if (ctx->r31 != ctx->r14) {
        // 0x802C6884: or          $v0, $zero, $zero
        ctx->r2 = 0 | 0;
            goto L_802C6890;
    }
    // 0x802C6884: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    // 0x802C6888: b           L_802C68C4
    // 0x802C688C: or          $v0, $ra, $zero
    ctx->r2 = ctx->r31 | 0;
        goto L_802C68C4;
    // 0x802C688C: or          $v0, $ra, $zero
    ctx->r2 = ctx->r31 | 0;
L_802C6890:
    // 0x802C6890: lui         $v1, 0x802D
    ctx->r3 = S32(0X802D << 16);
    // 0x802C6894: addiu       $v1, $v1, -0x73A8
    ctx->r3 = ADD32(ctx->r3, -0X73A8);
    // 0x802C6898: sll         $t7, $a1, 2
    ctx->r15 = S32(ctx->r5 << 2);
    // 0x802C689C: addiu       $a0, $zero, 0x6
    ctx->r4 = ADD32(0, 0X6);
    // 0x802C68A0: addu        $t8, $v1, $t7
    ctx->r24 = ADD32(ctx->r3, ctx->r15);
    // 0x802C68A4: sw          $a0, 0x0($t8)
    MEM_W(0X0, ctx->r24) = ctx->r4;
    // 0x802C68A8: lw          $t9, 0x0($v1)
    ctx->r25 = MEM_W(ctx->r3, 0X0);
    // 0x802C68AC: bne         $a0, $t9, L_802C68C4
    if (ctx->r4 != ctx->r25) {
        // 0x802C68B0: nop
    
            goto L_802C68C4;
    }
    // 0x802C68B0: nop

    // 0x802C68B4: lw          $t6, 0x4($v1)
    ctx->r14 = MEM_W(ctx->r3, 0X4);
    // 0x802C68B8: bne         $a0, $t6, L_802C68C4
    if (ctx->r4 != ctx->r14) {
        // 0x802C68BC: nop
    
            goto L_802C68C4;
    }
    // 0x802C68BC: nop

    // 0x802C68C0: or          $v0, $ra, $zero
    ctx->r2 = ctx->r31 | 0;
L_802C68C4:
    // 0x802C68C4: beql        $v0, $zero, L_802C6AD0
    if (ctx->r2 == 0) {
        // 0x802C68C8: lw          $ra, 0x14($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X14);
            goto L_802C6AD0;
    }
    goto skip_0;
    // 0x802C68C8: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    skip_0:
    // 0x802C68CC: lw          $v0, 0x0($a2)
    ctx->r2 = MEM_W(ctx->r6, 0X0);
    // 0x802C68D0: lui         $v1, 0x800E
    ctx->r3 = S32(0X800E << 16);
    // 0x802C68D4: addiu       $v1, $v1, -0x5640
    ctx->r3 = ADD32(ctx->r3, -0X5640);
    // 0x802C68D8: beq         $v0, $zero, L_802C6A3C
    if (ctx->r2 == 0) {
        // 0x802C68DC: lui         $t1, 0x802D
        ctx->r9 = S32(0X802D << 16);
            goto L_802C6A3C;
    }
    // 0x802C68DC: lui         $t1, 0x802D
    ctx->r9 = S32(0X802D << 16);
    // 0x802C68E0: beq         $v0, $ra, L_802C6A74
    if (ctx->r2 == ctx->r31) {
        // 0x802C68E4: addiu       $t2, $zero, 0x4
        ctx->r10 = ADD32(0, 0X4);
            goto L_802C6A74;
    }
    // 0x802C68E4: addiu       $t2, $zero, 0x4
    ctx->r10 = ADD32(0, 0X4);
    // 0x802C68E8: beq         $v0, $t2, L_802C6904
    if (ctx->r2 == ctx->r10) {
        // 0x802C68EC: or          $a2, $zero, $zero
        ctx->r6 = 0 | 0;
            goto L_802C6904;
    }
    // 0x802C68EC: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x802C68F0: addiu       $at, $zero, 0xB
    ctx->r1 = ADD32(0, 0XB);
    // 0x802C68F4: beql        $v0, $at, L_802C6A40
    if (ctx->r2 == ctx->r1) {
        // 0x802C68F8: lw          $t8, 0x0($v1)
        ctx->r24 = MEM_W(ctx->r3, 0X0);
            goto L_802C6A40;
    }
    goto skip_1;
    // 0x802C68F8: lw          $t8, 0x0($v1)
    ctx->r24 = MEM_W(ctx->r3, 0X0);
    skip_1:
    // 0x802C68FC: b           L_802C6AC4
    // 0x802C6900: nop

        goto L_802C6AC4;
    // 0x802C6900: nop

L_802C6904:
    // 0x802C6904: addiu       $v0, $sp, 0x34
    ctx->r2 = ADD32(ctx->r29, 0X34);
    // 0x802C6908: addiu       $v1, $sp, 0x38
    ctx->r3 = ADD32(ctx->r29, 0X38);
L_802C690C:
    // 0x802C690C: addiu       $v0, $v0, 0x1
    ctx->r2 = ADD32(ctx->r2, 0X1);
    // 0x802C6910: sltu        $at, $v0, $v1
    ctx->r1 = ctx->r2 < ctx->r3 ? 1 : 0;
    // 0x802C6914: bne         $at, $zero, L_802C690C
    if (ctx->r1 != 0) {
        // 0x802C6918: sb          $zero, -0x1($v0)
        MEM_B(-0X1, ctx->r2) = 0;
            goto L_802C690C;
    }
    // 0x802C6918: sb          $zero, -0x1($v0)
    MEM_B(-0X1, ctx->r2) = 0;
    // 0x802C691C: lui         $v1, 0x800E
    ctx->r3 = S32(0X800E << 16);
    // 0x802C6920: addiu       $v1, $v1, -0x5640
    ctx->r3 = ADD32(ctx->r3, -0X5640);
    // 0x802C6924: lw          $t3, 0x0($v1)
    ctx->r11 = MEM_W(ctx->r3, 0X0);
    // 0x802C6928: lui         $t4, 0x800D
    ctx->r12 = S32(0X800D << 16);
    // 0x802C692C: lui         $a3, 0x800E
    ctx->r7 = S32(0X800E << 16);
    // 0x802C6930: addu        $t7, $sp, $t3
    ctx->r15 = ADD32(ctx->r29, ctx->r11);
    // 0x802C6934: sb          $ra, 0x34($t7)
    MEM_B(0X34, ctx->r15) = ctx->r31;
    // 0x802C6938: lui         $t1, 0x802D
    ctx->r9 = S32(0X802D << 16);
    // 0x802C693C: addiu       $t1, $t1, -0x7428
    ctx->r9 = ADD32(ctx->r9, -0X7428);
    // 0x802C6940: lw          $t4, 0x48DC($t4)
    ctx->r12 = MEM_W(ctx->r12, 0X48DC);
    // 0x802C6944: addiu       $a3, $a3, -0x5650
    ctx->r7 = ADD32(ctx->r7, -0X5650);
    // 0x802C6948: addiu       $t5, $zero, 0xC
    ctx->r13 = ADD32(0, 0XC);
L_802C694C:
    // 0x802C694C: beq         $a2, $t4, L_802C6A14
    if (ctx->r6 == ctx->r12) {
        // 0x802C6950: or          $v1, $zero, $zero
        ctx->r3 = 0 | 0;
            goto L_802C6A14;
    }
    // 0x802C6950: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
    // 0x802C6954: sll         $t8, $a2, 2
    ctx->r24 = S32(ctx->r6 << 2);
    // 0x802C6958: subu        $t8, $t8, $a2
    ctx->r24 = SUB32(ctx->r24, ctx->r6);
    // 0x802C695C: sll         $t8, $t8, 3
    ctx->r24 = S32(ctx->r24 << 3);
    // 0x802C6960: subu        $t8, $t8, $a2
    ctx->r24 = SUB32(ctx->r24, ctx->r6);
    // 0x802C6964: sll         $t8, $t8, 3
    ctx->r24 = S32(ctx->r24 << 3);
    // 0x802C6968: addu        $t8, $t8, $a2
    ctx->r24 = ADD32(ctx->r24, ctx->r6);
    // 0x802C696C: lui         $t6, 0x800E
    ctx->r14 = S32(0X800E << 16);
    // 0x802C6970: lw          $t6, -0x7E90($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X7E90);
    // 0x802C6974: sll         $t8, $t8, 2
    ctx->r24 = S32(ctx->r24 << 2);
    // 0x802C6978: subu        $t8, $t8, $a2
    ctx->r24 = SUB32(ctx->r24, ctx->r6);
    // 0x802C697C: lui         $t9, 0x8019
    ctx->r25 = S32(0X8019 << 16);
    // 0x802C6980: addiu       $t9, $t9, 0x2690
    ctx->r25 = ADD32(ctx->r25, 0X2690);
    // 0x802C6984: sll         $t8, $t8, 3
    ctx->r24 = S32(ctx->r24 << 3);
    // 0x802C6988: addu        $a1, $t8, $t9
    ctx->r5 = ADD32(ctx->r24, ctx->r25);
    // 0x802C698C: sll         $t7, $t6, 2
    ctx->r15 = S32(ctx->r14 << 2);
    // 0x802C6990: lui         $t8, 0x800E
    ctx->r24 = S32(0X800E << 16);
    // 0x802C6994: subu        $t7, $t7, $t6
    ctx->r15 = SUB32(ctx->r15, ctx->r14);
    // 0x802C6998: sll         $t7, $t7, 4
    ctx->r15 = S32(ctx->r15 << 4);
    // 0x802C699C: addiu       $t8, $t8, -0x695C
    ctx->r24 = ADD32(ctx->r24, -0X695C);
    // 0x802C69A0: addu        $t0, $t7, $t8
    ctx->r8 = ADD32(ctx->r15, ctx->r24);
    // 0x802C69A4: addiu       $v0, $sp, 0x34
    ctx->r2 = ADD32(ctx->r29, 0X34);
L_802C69A8:
    // 0x802C69A8: lb          $t9, 0x0($v0)
    ctx->r25 = MEM_B(ctx->r2, 0X0);
    // 0x802C69AC: bnel        $t9, $zero, L_802C69C0
    if (ctx->r25 != 0) {
        // 0x802C69B0: addiu       $v1, $v1, 0x1
        ctx->r3 = ADD32(ctx->r3, 0X1);
            goto L_802C69C0;
    }
    goto skip_2;
    // 0x802C69B0: addiu       $v1, $v1, 0x1
    ctx->r3 = ADD32(ctx->r3, 0X1);
    skip_2:
    // 0x802C69B4: b           L_802C69CC
    // 0x802C69B8: sb          $ra, 0x0($v0)
    MEM_B(0X0, ctx->r2) = ctx->r31;
        goto L_802C69CC;
    // 0x802C69B8: sb          $ra, 0x0($v0)
    MEM_B(0X0, ctx->r2) = ctx->r31;
    // 0x802C69BC: addiu       $v1, $v1, 0x1
    ctx->r3 = ADD32(ctx->r3, 0X1);
L_802C69C0:
    // 0x802C69C0: slti        $at, $v1, 0x4
    ctx->r1 = SIGNED(ctx->r3) < 0X4 ? 1 : 0;
    // 0x802C69C4: bne         $at, $zero, L_802C69A8
    if (ctx->r1 != 0) {
        // 0x802C69C8: addiu       $v0, $v0, 0x1
        ctx->r2 = ADD32(ctx->r2, 0X1);
            goto L_802C69A8;
    }
    // 0x802C69C8: addiu       $v0, $v0, 0x1
    ctx->r2 = ADD32(ctx->r2, 0X1);
L_802C69CC:
    // 0x802C69CC: bnel        $v1, $t2, L_802C69DC
    if (ctx->r3 != ctx->r10) {
        // 0x802C69D0: sll         $t6, $v1, 2
        ctx->r14 = S32(ctx->r3 << 2);
            goto L_802C69DC;
    }
    goto skip_3;
    // 0x802C69D0: sll         $t6, $v1, 2
    ctx->r14 = S32(ctx->r3 << 2);
    skip_3:
    // 0x802C69D4: addiu       $v1, $v1, -0x1
    ctx->r3 = ADD32(ctx->r3, -0X1);
    // 0x802C69D8: sll         $t6, $v1, 2
    ctx->r14 = S32(ctx->r3 << 2);
L_802C69DC:
    // 0x802C69DC: addu        $t7, $t1, $t6
    ctx->r15 = ADD32(ctx->r9, ctx->r14);
    // 0x802C69E0: lw          $v0, 0x0($t7)
    ctx->r2 = MEM_W(ctx->r15, 0X0);
    // 0x802C69E4: multu       $v0, $t5
    result = U64(U32(ctx->r2)) * U64(U32(ctx->r13)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x802C69E8: sw          $v0, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r2;
    // 0x802C69EC: sw          $v0, 0xB68($a1)
    MEM_W(0XB68, ctx->r5) = ctx->r2;
    // 0x802C69F0: mflo        $t8
    ctx->r24 = lo;
    // 0x802C69F4: addu        $a0, $t0, $t8
    ctx->r4 = ADD32(ctx->r8, ctx->r24);
    // 0x802C69F8: lw          $t9, 0x0($a0)
    ctx->r25 = MEM_W(ctx->r4, 0X0);
    // 0x802C69FC: lw          $t6, 0x4($a0)
    ctx->r14 = MEM_W(ctx->r4, 0X4);
    // 0x802C6A00: lw          $t7, 0x8($a0)
    ctx->r15 = MEM_W(ctx->r4, 0X8);
    // 0x802C6A04: sw          $t9, 0xB6C($a1)
    MEM_W(0XB6C, ctx->r5) = ctx->r25;
    // 0x802C6A08: sw          $t6, 0xB70($a1)
    MEM_W(0XB70, ctx->r5) = ctx->r14;
    // 0x802C6A0C: b           L_802C6A24
    // 0x802C6A10: sw          $t7, 0xB74($a1)
    MEM_W(0XB74, ctx->r5) = ctx->r15;
        goto L_802C6A24;
    // 0x802C6A10: sw          $t7, 0xB74($a1)
    MEM_W(0XB74, ctx->r5) = ctx->r15;
L_802C6A14:
    // 0x802C6A14: sll         $t8, $t3, 2
    ctx->r24 = S32(ctx->r11 << 2);
    // 0x802C6A18: addu        $t9, $t1, $t8
    ctx->r25 = ADD32(ctx->r9, ctx->r24);
    // 0x802C6A1C: lw          $t6, 0x0($t9)
    ctx->r14 = MEM_W(ctx->r25, 0X0);
    // 0x802C6A20: sw          $t6, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r14;
L_802C6A24:
    // 0x802C6A24: addiu       $a2, $a2, 0x1
    ctx->r6 = ADD32(ctx->r6, 0X1);
    // 0x802C6A28: bne         $a2, $t2, L_802C694C
    if (ctx->r6 != ctx->r10) {
        // 0x802C6A2C: addiu       $a3, $a3, 0x4
        ctx->r7 = ADD32(ctx->r7, 0X4);
            goto L_802C694C;
    }
    // 0x802C6A2C: addiu       $a3, $a3, 0x4
    ctx->r7 = ADD32(ctx->r7, 0X4);
    // 0x802C6A30: addiu       $t7, $zero, 0x1E
    ctx->r15 = ADD32(0, 0X1E);
    // 0x802C6A34: b           L_802C6AC4
    // 0x802C6A38: sw          $t7, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r15;
        goto L_802C6AC4;
    // 0x802C6A38: sw          $t7, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r15;
L_802C6A3C:
    // 0x802C6A3C: lw          $t8, 0x0($v1)
    ctx->r24 = MEM_W(ctx->r3, 0X0);
L_802C6A40:
    // 0x802C6A40: addiu       $t1, $t1, -0x7428
    ctx->r9 = ADD32(ctx->r9, -0X7428);
    // 0x802C6A44: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x802C6A48: sll         $t9, $t8, 2
    ctx->r25 = S32(ctx->r24 << 2);
    // 0x802C6A4C: addu        $t6, $t1, $t9
    ctx->r14 = ADD32(ctx->r9, ctx->r25);
    // 0x802C6A50: lw          $t7, 0x0($t6)
    ctx->r15 = MEM_W(ctx->r14, 0X0);
    // 0x802C6A54: addiu       $v0, $v0, -0x5650
    ctx->r2 = ADD32(ctx->r2, -0X5650);
    // 0x802C6A58: addiu       $t8, $zero, 0x14
    ctx->r24 = ADD32(0, 0X14);
    // 0x802C6A5C: sw          $zero, 0x4($v0)
    MEM_W(0X4, ctx->r2) = 0;
    // 0x802C6A60: sw          $zero, 0x8($v0)
    MEM_W(0X8, ctx->r2) = 0;
    // 0x802C6A64: sw          $zero, 0xC($v0)
    MEM_W(0XC, ctx->r2) = 0;
    // 0x802C6A68: sw          $t8, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r24;
    // 0x802C6A6C: b           L_802C6AC4
    // 0x802C6A70: sw          $t7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r15;
        goto L_802C6AC4;
    // 0x802C6A70: sw          $t7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r15;
L_802C6A74:
    // 0x802C6A74: lui         $v1, 0x800E
    ctx->r3 = S32(0X800E << 16);
    // 0x802C6A78: addiu       $v1, $v1, -0x5640
    ctx->r3 = ADD32(ctx->r3, -0X5640);
    // 0x802C6A7C: lw          $t9, 0x0($v1)
    ctx->r25 = MEM_W(ctx->r3, 0X0);
    // 0x802C6A80: lui         $t1, 0x802D
    ctx->r9 = S32(0X802D << 16);
    // 0x802C6A84: addiu       $t1, $t1, -0x7428
    ctx->r9 = ADD32(ctx->r9, -0X7428);
    // 0x802C6A88: sll         $t6, $t9, 2
    ctx->r14 = S32(ctx->r25 << 2);
    // 0x802C6A8C: lw          $t9, 0x4($v1)
    ctx->r25 = MEM_W(ctx->r3, 0X4);
    // 0x802C6A90: addu        $t7, $t1, $t6
    ctx->r15 = ADD32(ctx->r9, ctx->r14);
    // 0x802C6A94: lw          $t8, 0x0($t7)
    ctx->r24 = MEM_W(ctx->r15, 0X0);
    // 0x802C6A98: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x802C6A9C: addiu       $v0, $v0, -0x5650
    ctx->r2 = ADD32(ctx->r2, -0X5650);
    // 0x802C6AA0: sll         $t6, $t9, 2
    ctx->r14 = S32(ctx->r25 << 2);
    // 0x802C6AA4: addu        $t7, $t1, $t6
    ctx->r15 = ADD32(ctx->r9, ctx->r14);
    // 0x802C6AA8: sw          $t8, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r24;
    // 0x802C6AAC: lw          $t8, 0x0($t7)
    ctx->r24 = MEM_W(ctx->r15, 0X0);
    // 0x802C6AB0: addiu       $t9, $zero, 0x14
    ctx->r25 = ADD32(0, 0X14);
    // 0x802C6AB4: sw          $zero, 0x8($v0)
    MEM_W(0X8, ctx->r2) = 0;
    // 0x802C6AB8: sw          $zero, 0xC($v0)
    MEM_W(0XC, ctx->r2) = 0;
    // 0x802C6ABC: sw          $t9, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r25;
    // 0x802C6AC0: sw          $t8, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r24;
L_802C6AC4:
    // 0x802C6AC4: jal         0x802C84EC
    // 0x802C6AC8: lw          $a0, 0x38($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X38);
    func_i2_802C84EC(rdram, ctx);
        goto after_0;
    // 0x802C6AC8: lw          $a0, 0x38($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X38);
    after_0:
    // 0x802C6ACC: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C6AD0:
    // 0x802C6AD0: addiu       $sp, $sp, 0x48
    ctx->r29 = ADD32(ctx->r29, 0X48);
    // 0x802C6AD4: jr          $ra
    // 0x802C6AD8: nop

    return;
    // 0x802C6AD8: nop

;}
RECOMP_FUNC void func_i2_802C6ADC(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C6ADC: addiu       $sp, $sp, -0x28
    ctx->r29 = ADD32(ctx->r29, -0X28);
    // 0x802C6AE0: sw          $s0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r16;
    // 0x802C6AE4: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x802C6AE8: sw          $ra, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r31;
    // 0x802C6AEC: lui         $t6, 0x80C
    ctx->r14 = S32(0X80C << 16);
    // 0x802C6AF0: lui         $s0, 0x600
    ctx->r16 = S32(0X600 << 16);
    // 0x802C6AF4: addiu       $t6, $t6, -0x1DB8
    ctx->r14 = ADD32(ctx->r14, -0X1DB8);
    // 0x802C6AF8: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C6AFC: sw          $t6, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r14;
    // 0x802C6B00: sw          $s0, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r16;
    // 0x802C6B04: or          $v1, $a0, $zero
    ctx->r3 = ctx->r4 | 0;
    // 0x802C6B08: lui         $t7, 0x107
    ctx->r15 = S32(0X107 << 16);
    // 0x802C6B0C: addiu       $t7, $t7, -0x9D8
    ctx->r15 = ADD32(ctx->r15, -0X9D8);
    // 0x802C6B10: sw          $t7, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r15;
    // 0x802C6B14: sw          $s0, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r16;
    // 0x802C6B18: addiu       $t8, $zero, 0x170
    ctx->r24 = ADD32(0, 0X170);
    // 0x802C6B1C: addiu       $t9, $zero, 0x1E
    ctx->r25 = ADD32(0, 0X1E);
    // 0x802C6B20: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C6B24: sw          $t9, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r25;
    // 0x802C6B28: sw          $t8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r24;
    // 0x802C6B2C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C6B30: addiu       $a2, $zero, 0x1C
    ctx->r6 = ADD32(0, 0X1C);
    // 0x802C6B34: jal         0x80094338
    // 0x802C6B38: addiu       $a3, $zero, 0x16
    ctx->r7 = ADD32(0, 0X16);
    func_80094338(rdram, ctx);
        goto after_0;
    // 0x802C6B38: addiu       $a3, $zero, 0x16
    ctx->r7 = ADD32(0, 0X16);
    after_0:
    // 0x802C6B3C: addiu       $t5, $zero, 0x82
    ctx->r13 = ADD32(0, 0X82);
    // 0x802C6B40: addiu       $t6, $zero, 0xD
    ctx->r14 = ADD32(0, 0XD);
    // 0x802C6B44: sw          $t6, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r14;
    // 0x802C6B48: sw          $t5, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r13;
    // 0x802C6B4C: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C6B50: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C6B54: addiu       $a2, $zero, 0x1C
    ctx->r6 = ADD32(0, 0X1C);
    // 0x802C6B58: jal         0x80094338
    // 0x802C6B5C: addiu       $a3, $zero, 0x60
    ctx->r7 = ADD32(0, 0X60);
    func_80094338(rdram, ctx);
        goto after_1;
    // 0x802C6B5C: addiu       $a3, $zero, 0x60
    ctx->r7 = ADD32(0, 0X60);
    after_1:
    // 0x802C6B60: addiu       $t7, $zero, 0x3B
    ctx->r15 = ADD32(0, 0X3B);
    // 0x802C6B64: addiu       $t8, $zero, 0xD
    ctx->r24 = ADD32(0, 0XD);
    // 0x802C6B68: sw          $t8, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r24;
    // 0x802C6B6C: sw          $t7, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r15;
    // 0x802C6B70: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C6B74: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C6B78: addiu       $a2, $zero, 0x20
    ctx->r6 = ADD32(0, 0X20);
    // 0x802C6B7C: jal         0x80094338
    // 0x802C6B80: addiu       $a3, $zero, 0x6E
    ctx->r7 = ADD32(0, 0X6E);
    func_80094338(rdram, ctx);
        goto after_2;
    // 0x802C6B80: addiu       $a3, $zero, 0x6E
    ctx->r7 = ADD32(0, 0X6E);
    after_2:
    // 0x802C6B84: addiu       $t9, $zero, 0x3B
    ctx->r25 = ADD32(0, 0X3B);
    // 0x802C6B88: addiu       $t5, $zero, 0xD
    ctx->r13 = ADD32(0, 0XD);
    // 0x802C6B8C: sw          $t5, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r13;
    // 0x802C6B90: sw          $t9, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r25;
    // 0x802C6B94: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C6B98: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C6B9C: addiu       $a2, $zero, 0x5F
    ctx->r6 = ADD32(0, 0X5F);
    // 0x802C6BA0: jal         0x80094338
    // 0x802C6BA4: addiu       $a3, $zero, 0x6E
    ctx->r7 = ADD32(0, 0X6E);
    func_80094338(rdram, ctx);
        goto after_3;
    // 0x802C6BA4: addiu       $a3, $zero, 0x6E
    ctx->r7 = ADD32(0, 0X6E);
    after_3:
    // 0x802C6BA8: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C6BAC: addiu       $a1, $zero, 0x13
    ctx->r5 = ADD32(0, 0X13);
    // 0x802C6BB0: jal         0x802C86E4
    // 0x802C6BB4: addiu       $a2, $zero, 0x68
    ctx->r6 = ADD32(0, 0X68);
    func_i2_802C86E4(rdram, ctx);
        goto after_4;
    // 0x802C6BB4: addiu       $a2, $zero, 0x68
    ctx->r6 = ADD32(0, 0X68);
    after_4:
    // 0x802C6BB8: lui         $t6, 0x802D
    ctx->r14 = S32(0X802D << 16);
    // 0x802C6BBC: lw          $t6, -0x73A8($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X73A8);
    // 0x802C6BC0: addiu       $at, $zero, 0x5
    ctx->r1 = ADD32(0, 0X5);
    // 0x802C6BC4: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C6BC8: beq         $t6, $at, L_802C6BE4
    if (ctx->r14 == ctx->r1) {
        // 0x802C6BCC: lui         $a3, 0x802D
        ctx->r7 = S32(0X802D << 16);
            goto L_802C6BE4;
    }
    // 0x802C6BCC: lui         $a3, 0x802D
    ctx->r7 = S32(0X802D << 16);
    // 0x802C6BD0: lui         $t7, 0x80C
    ctx->r15 = S32(0X80C << 16);
    // 0x802C6BD4: addiu       $t7, $t7, -0x1D48
    ctx->r15 = ADD32(ctx->r15, -0X1D48);
    // 0x802C6BD8: sw          $t7, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r15;
    // 0x802C6BDC: addiu       $a0, $v0, 0x8
    ctx->r4 = ADD32(ctx->r2, 0X8);
    // 0x802C6BE0: sw          $s0, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r16;
L_802C6BE4:
    // 0x802C6BE4: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x802C6BE8: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C6BEC: lui         $t4, 0xE700
    ctx->r12 = S32(0XE700 << 16);
    // 0x802C6BF0: or          $v1, $a0, $zero
    ctx->r3 = ctx->r4 | 0;
    // 0x802C6BF4: sw          $t4, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r12;
    // 0x802C6BF8: sw          $zero, 0x4($v0)
    MEM_W(0X4, ctx->r2) = 0;
    // 0x802C6BFC: lui         $t8, 0xB900
    ctx->r24 = S32(0XB900 << 16);
    // 0x802C6C00: lui         $t9, 0x50
    ctx->r25 = S32(0X50 << 16);
    // 0x802C6C04: ori         $t9, $t9, 0x4240
    ctx->r25 = ctx->r25 | 0X4240;
    // 0x802C6C08: ori         $t8, $t8, 0x31D
    ctx->r24 = ctx->r24 | 0X31D;
    // 0x802C6C0C: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C6C10: sw          $t8, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r24;
    // 0x802C6C14: sw          $t9, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r25;
    // 0x802C6C18: or          $a1, $a0, $zero
    ctx->r5 = ctx->r4 | 0;
    // 0x802C6C1C: lui         $t5, 0xFC11
    ctx->r13 = S32(0XFC11 << 16);
    // 0x802C6C20: lui         $t6, 0xFF2F
    ctx->r14 = S32(0XFF2F << 16);
    // 0x802C6C24: ori         $t6, $t6, 0xFFFF
    ctx->r14 = ctx->r14 | 0XFFFF;
    // 0x802C6C28: ori         $t5, $t5, 0x9623
    ctx->r13 = ctx->r13 | 0X9623;
    // 0x802C6C2C: addiu       $a3, $a3, -0x7396
    ctx->r7 = ADD32(ctx->r7, -0X7396);
    // 0x802C6C30: sw          $t5, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r13;
    // 0x802C6C34: sw          $t6, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r14;
    // 0x802C6C38: lh          $a2, 0x0($a3)
    ctx->r6 = MEM_H(ctx->r7, 0X0);
    // 0x802C6C3C: lui         $t3, 0xF568
    ctx->r11 = S32(0XF568 << 16);
    // 0x802C6C40: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C6C44: bne         $a2, $zero, L_802C6D0C
    if (ctx->r6 != 0) {
        // 0x802C6C48: ori         $t3, $t3, 0x1000
        ctx->r11 = ctx->r11 | 0X1000;
            goto L_802C6D0C;
    }
    // 0x802C6C48: ori         $t3, $t3, 0x1000
    ctx->r11 = ctx->r11 | 0X1000;
    // 0x802C6C4C: lui         $v1, 0x802D
    ctx->r3 = S32(0X802D << 16);
    // 0x802C6C50: addiu       $v1, $v1, -0x7398
    ctx->r3 = ADD32(ctx->r3, -0X7398);
    // 0x802C6C54: lh          $v0, 0x0($v1)
    ctx->r2 = MEM_H(ctx->r3, 0X0);
    // 0x802C6C58: lui         $at, 0x4080
    ctx->r1 = S32(0X4080 << 16);
    // 0x802C6C5C: mtc1        $at, $f0
    ctx->f0.u32l = ctx->r1;
    // 0x802C6C60: mtc1        $v0, $f4
    ctx->f4.u32l = ctx->r2;
    // 0x802C6C64: lui         $at, 0x437F
    ctx->r1 = S32(0X437F << 16);
    // 0x802C6C68: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x802C6C6C: cvt.s.w     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
    // 0x802C6C70: addiu       $t0, $zero, 0x1
    ctx->r8 = ADD32(0, 0X1);
    // 0x802C6C74: lui         $at, 0x4F00
    ctx->r1 = S32(0X4F00 << 16);
    // 0x802C6C78: mul.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = MUL_S(ctx->f6.fl, ctx->f8.fl);
    // 0x802C6C7C: div.s       $f16, $f10, $f0
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f16.fl = DIV_S(ctx->f10.fl, ctx->f0.fl);
    // 0x802C6C80: cfc1        $t7, $FpcCsr
    ctx->r15 = get_cop1_cs();
    // 0x802C6C84: ctc1        $t0, $FpcCsr
    set_cop1_cs(ctx->r8);
    // 0x802C6C88: nop

    // 0x802C6C8C: cvt.w.s     $f18, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    ctx->f18.u32l = CVT_W_S(ctx->f16.fl);
    // 0x802C6C90: cfc1        $t0, $FpcCsr
    ctx->r8 = get_cop1_cs();
    // 0x802C6C94: nop

    // 0x802C6C98: andi        $t0, $t0, 0x78
    ctx->r8 = ctx->r8 & 0X78;
    // 0x802C6C9C: beql        $t0, $zero, L_802C6CF4
    if (ctx->r8 == 0) {
        // 0x802C6CA0: mfc1        $t0, $f18
        ctx->r8 = (int32_t)ctx->f18.u32l;
            goto L_802C6CF4;
    }
    goto skip_0;
    // 0x802C6CA0: mfc1        $t0, $f18
    ctx->r8 = (int32_t)ctx->f18.u32l;
    skip_0:
    // 0x802C6CA4: mtc1        $at, $f18
    ctx->f18.u32l = ctx->r1;
    // 0x802C6CA8: addiu       $t0, $zero, 0x1
    ctx->r8 = ADD32(0, 0X1);
    // 0x802C6CAC: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x802C6CB0: sub.s       $f18, $f16, $f18
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f18.fl = ctx->f16.fl - ctx->f18.fl;
    // 0x802C6CB4: ctc1        $t0, $FpcCsr
    set_cop1_cs(ctx->r8);
    // 0x802C6CB8: nop

    // 0x802C6CBC: cvt.w.s     $f18, $f18
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 18);
    ctx->f18.u32l = CVT_W_S(ctx->f18.fl);
    // 0x802C6CC0: cfc1        $t0, $FpcCsr
    ctx->r8 = get_cop1_cs();
    // 0x802C6CC4: nop

    // 0x802C6CC8: andi        $t0, $t0, 0x78
    ctx->r8 = ctx->r8 & 0X78;
    // 0x802C6CCC: bnel        $t0, $zero, L_802C6CE8
    if (ctx->r8 != 0) {
        // 0x802C6CD0: ctc1        $t7, $FpcCsr
        set_cop1_cs(ctx->r15);
            goto L_802C6CE8;
    }
    goto skip_1;
    // 0x802C6CD0: ctc1        $t7, $FpcCsr
    set_cop1_cs(ctx->r15);
    skip_1:
    // 0x802C6CD4: mfc1        $t0, $f18
    ctx->r8 = (int32_t)ctx->f18.u32l;
    // 0x802C6CD8: ctc1        $t7, $FpcCsr
    set_cop1_cs(ctx->r15);
    // 0x802C6CDC: b           L_802C6DC8
    // 0x802C6CE0: or          $t0, $t0, $at
    ctx->r8 = ctx->r8 | ctx->r1;
        goto L_802C6DC8;
    // 0x802C6CE0: or          $t0, $t0, $at
    ctx->r8 = ctx->r8 | ctx->r1;
    // 0x802C6CE4: ctc1        $t7, $FpcCsr
    set_cop1_cs(ctx->r15);
L_802C6CE8:
    // 0x802C6CE8: b           L_802C6DC8
    // 0x802C6CEC: addiu       $t0, $zero, -0x1
    ctx->r8 = ADD32(0, -0X1);
        goto L_802C6DC8;
    // 0x802C6CEC: addiu       $t0, $zero, -0x1
    ctx->r8 = ADD32(0, -0X1);
    // 0x802C6CF0: mfc1        $t0, $f18
    ctx->r8 = (int32_t)ctx->f18.u32l;
L_802C6CF4:
    // 0x802C6CF4: nop

    // 0x802C6CF8: bltzl       $t0, L_802C6CE8
    if (SIGNED(ctx->r8) < 0) {
        // 0x802C6CFC: ctc1        $t7, $FpcCsr
        set_cop1_cs(ctx->r15);
            goto L_802C6CE8;
    }
    goto skip_2;
    // 0x802C6CFC: ctc1        $t7, $FpcCsr
    set_cop1_cs(ctx->r15);
    skip_2:
    // 0x802C6D00: ctc1        $t7, $FpcCsr
    set_cop1_cs(ctx->r15);
    // 0x802C6D04: b           L_802C6DCC
    // 0x802C6D08: addiu       $t9, $v0, 0x1
    ctx->r25 = ADD32(ctx->r2, 0X1);
        goto L_802C6DCC;
    // 0x802C6D08: addiu       $t9, $v0, 0x1
    ctx->r25 = ADD32(ctx->r2, 0X1);
L_802C6D0C:
    // 0x802C6D0C: lui         $v1, 0x802D
    ctx->r3 = S32(0X802D << 16);
    // 0x802C6D10: addiu       $v1, $v1, -0x7398
    ctx->r3 = ADD32(ctx->r3, -0X7398);
    // 0x802C6D14: lh          $v0, 0x0($v1)
    ctx->r2 = MEM_H(ctx->r3, 0X0);
    // 0x802C6D18: lui         $at, 0x4080
    ctx->r1 = S32(0X4080 << 16);
    // 0x802C6D1C: mtc1        $at, $f0
    ctx->f0.u32l = ctx->r1;
    // 0x802C6D20: mtc1        $v0, $f4
    ctx->f4.u32l = ctx->r2;
    // 0x802C6D24: lui         $at, 0x437F
    ctx->r1 = S32(0X437F << 16);
    // 0x802C6D28: mtc1        $at, $f10
    ctx->f10.u32l = ctx->r1;
    // 0x802C6D2C: cvt.s.w     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
    // 0x802C6D30: addiu       $t0, $zero, 0x1
    ctx->r8 = ADD32(0, 0X1);
    // 0x802C6D34: lui         $at, 0x4F00
    ctx->r1 = S32(0X4F00 << 16);
    // 0x802C6D38: sub.s       $f8, $f0, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = ctx->f0.fl - ctx->f6.fl;
    // 0x802C6D3C: mul.s       $f16, $f8, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f16.fl = MUL_S(ctx->f8.fl, ctx->f10.fl);
    // 0x802C6D40: div.s       $f18, $f16, $f0
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f18.fl = DIV_S(ctx->f16.fl, ctx->f0.fl);
    // 0x802C6D44: cfc1        $t8, $FpcCsr
    ctx->r24 = get_cop1_cs();
    // 0x802C6D48: ctc1        $t0, $FpcCsr
    set_cop1_cs(ctx->r8);
    // 0x802C6D4C: nop

    // 0x802C6D50: cvt.w.s     $f4, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    ctx->f4.u32l = CVT_W_S(ctx->f18.fl);
    // 0x802C6D54: cfc1        $t0, $FpcCsr
    ctx->r8 = get_cop1_cs();
    // 0x802C6D58: nop

    // 0x802C6D5C: andi        $t0, $t0, 0x78
    ctx->r8 = ctx->r8 & 0X78;
    // 0x802C6D60: beql        $t0, $zero, L_802C6DB0
    if (ctx->r8 == 0) {
        // 0x802C6D64: mfc1        $t0, $f4
        ctx->r8 = (int32_t)ctx->f4.u32l;
            goto L_802C6DB0;
    }
    goto skip_3;
    // 0x802C6D64: mfc1        $t0, $f4
    ctx->r8 = (int32_t)ctx->f4.u32l;
    skip_3:
    // 0x802C6D68: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x802C6D6C: addiu       $t0, $zero, 0x1
    ctx->r8 = ADD32(0, 0X1);
    // 0x802C6D70: sub.s       $f4, $f18, $f4
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f4.fl = ctx->f18.fl - ctx->f4.fl;
    // 0x802C6D74: ctc1        $t0, $FpcCsr
    set_cop1_cs(ctx->r8);
    // 0x802C6D78: nop

    // 0x802C6D7C: cvt.w.s     $f4, $f4
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 4);
    ctx->f4.u32l = CVT_W_S(ctx->f4.fl);
    // 0x802C6D80: cfc1        $t0, $FpcCsr
    ctx->r8 = get_cop1_cs();
    // 0x802C6D84: nop

    // 0x802C6D88: andi        $t0, $t0, 0x78
    ctx->r8 = ctx->r8 & 0X78;
    // 0x802C6D8C: bne         $t0, $zero, L_802C6DA4
    if (ctx->r8 != 0) {
        // 0x802C6D90: nop
    
            goto L_802C6DA4;
    }
    // 0x802C6D90: nop

    // 0x802C6D94: mfc1        $t0, $f4
    ctx->r8 = (int32_t)ctx->f4.u32l;
    // 0x802C6D98: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x802C6D9C: b           L_802C6DBC
    // 0x802C6DA0: or          $t0, $t0, $at
    ctx->r8 = ctx->r8 | ctx->r1;
        goto L_802C6DBC;
    // 0x802C6DA0: or          $t0, $t0, $at
    ctx->r8 = ctx->r8 | ctx->r1;
L_802C6DA4:
    // 0x802C6DA4: b           L_802C6DBC
    // 0x802C6DA8: addiu       $t0, $zero, -0x1
    ctx->r8 = ADD32(0, -0X1);
        goto L_802C6DBC;
    // 0x802C6DA8: addiu       $t0, $zero, -0x1
    ctx->r8 = ADD32(0, -0X1);
    // 0x802C6DAC: mfc1        $t0, $f4
    ctx->r8 = (int32_t)ctx->f4.u32l;
L_802C6DB0:
    // 0x802C6DB0: nop

    // 0x802C6DB4: bltz        $t0, L_802C6DA4
    if (SIGNED(ctx->r8) < 0) {
        // 0x802C6DB8: nop
    
            goto L_802C6DA4;
    }
    // 0x802C6DB8: nop

L_802C6DBC:
    // 0x802C6DBC: ctc1        $t8, $FpcCsr
    set_cop1_cs(ctx->r24);
    // 0x802C6DC0: nop

    // 0x802C6DC4: nop

L_802C6DC8:
    // 0x802C6DC8: addiu       $t9, $v0, 0x1
    ctx->r25 = ADD32(ctx->r2, 0X1);
L_802C6DCC:
    // 0x802C6DCC: sh          $t9, 0x0($v1)
    MEM_H(0X0, ctx->r3) = ctx->r25;
    // 0x802C6DD0: lh          $t5, 0x0($v1)
    ctx->r13 = MEM_H(ctx->r3, 0X0);
    // 0x802C6DD4: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x802C6DD8: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C6DDC: slti        $at, $t5, 0x4
    ctx->r1 = SIGNED(ctx->r13) < 0X4 ? 1 : 0;
    // 0x802C6DE0: bne         $at, $zero, L_802C6DF4
    if (ctx->r1 != 0) {
        // 0x802C6DE4: lui         $t7, 0xFA00
        ctx->r15 = S32(0XFA00 << 16);
            goto L_802C6DF4;
    }
    // 0x802C6DE4: lui         $t7, 0xFA00
    ctx->r15 = S32(0XFA00 << 16);
    // 0x802C6DE8: xori        $t6, $a2, 0x1
    ctx->r14 = ctx->r6 ^ 0X1;
    // 0x802C6DEC: sh          $zero, 0x0($v1)
    MEM_H(0X0, ctx->r3) = 0;
    // 0x802C6DF0: sh          $t6, 0x0($a3)
    MEM_H(0X0, ctx->r7) = ctx->r14;
L_802C6DF4:
    // 0x802C6DF4: andi        $v1, $t0, 0xFF
    ctx->r3 = ctx->r8 & 0XFF;
    // 0x802C6DF8: sll         $t8, $v1, 24
    ctx->r24 = S32(ctx->r3 << 24);
    // 0x802C6DFC: lui         $at, 0xFF
    ctx->r1 = S32(0XFF << 16);
    // 0x802C6E00: or          $t9, $t8, $at
    ctx->r25 = ctx->r24 | ctx->r1;
    // 0x802C6E04: sll         $t5, $v1, 8
    ctx->r13 = S32(ctx->r3 << 8);
    // 0x802C6E08: or          $t6, $t9, $t5
    ctx->r14 = ctx->r25 | ctx->r13;
    // 0x802C6E0C: sw          $t7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r15;
    // 0x802C6E10: ori         $t7, $t6, 0xFF
    ctx->r15 = ctx->r14 | 0XFF;
    // 0x802C6E14: or          $a1, $a0, $zero
    ctx->r5 = ctx->r4 | 0;
    // 0x802C6E18: sw          $t7, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r15;
    // 0x802C6E1C: lui         $t9, 0x80B
    ctx->r25 = S32(0X80B << 16);
    // 0x802C6E20: lui         $t8, 0xFD68
    ctx->r24 = S32(0XFD68 << 16);
    // 0x802C6E24: ori         $t8, $t8, 0x3F
    ctx->r24 = ctx->r24 | 0X3F;
    // 0x802C6E28: addiu       $t9, $t9, 0x6590
    ctx->r25 = ADD32(ctx->r25, 0X6590);
    // 0x802C6E2C: sw          $t9, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r25;
    // 0x802C6E30: sw          $t8, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r24;
    // 0x802C6E34: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C6E38: or          $a2, $a0, $zero
    ctx->r6 = ctx->r4 | 0;
    // 0x802C6E3C: lui         $t5, 0x708
    ctx->r13 = S32(0X708 << 16);
    // 0x802C6E40: ori         $t5, $t5, 0x200
    ctx->r13 = ctx->r13 | 0X200;
    // 0x802C6E44: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C6E48: or          $a3, $a0, $zero
    ctx->r7 = ctx->r4 | 0;
    // 0x802C6E4C: sw          $t5, 0x4($a2)
    MEM_W(0X4, ctx->r6) = ctx->r13;
    // 0x802C6E50: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C6E54: sw          $t3, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r11;
    // 0x802C6E58: lui         $t6, 0xE600
    ctx->r14 = S32(0XE600 << 16);
    // 0x802C6E5C: sw          $t6, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r14;
    // 0x802C6E60: or          $t1, $a0, $zero
    ctx->r9 = ctx->r4 | 0;
    // 0x802C6E64: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C6E68: sw          $zero, 0x4($a3)
    MEM_W(0X4, ctx->r7) = 0;
    // 0x802C6E6C: lui         $t8, 0x70F
    ctx->r24 = S32(0X70F << 16);
    // 0x802C6E70: ori         $t8, $t8, 0xC08C
    ctx->r24 = ctx->r24 | 0XC08C;
    // 0x802C6E74: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x802C6E78: lui         $t7, 0xF400
    ctx->r15 = S32(0XF400 << 16);
    // 0x802C6E7C: sw          $t7, 0x0($t1)
    MEM_W(0X0, ctx->r9) = ctx->r15;
    // 0x802C6E80: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C6E84: sw          $t8, 0x4($t1)
    MEM_W(0X4, ctx->r9) = ctx->r24;
    // 0x802C6E88: or          $v1, $a0, $zero
    ctx->r3 = ctx->r4 | 0;
    // 0x802C6E8C: sw          $zero, 0x4($v0)
    MEM_W(0X4, ctx->r2) = 0;
    // 0x802C6E90: sw          $t4, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r12;
    // 0x802C6E94: lui         $t9, 0x8
    ctx->r25 = S32(0X8 << 16);
    // 0x802C6E98: ori         $t9, $t9, 0x200
    ctx->r25 = ctx->r25 | 0X200;
    // 0x802C6E9C: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C6EA0: or          $a1, $a0, $zero
    ctx->r5 = ctx->r4 | 0;
    // 0x802C6EA4: sw          $t9, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r25;
    // 0x802C6EA8: sw          $t3, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r11;
    // 0x802C6EAC: lui         $t6, 0xF
    ctx->r14 = S32(0XF << 16);
    // 0x802C6EB0: ori         $t6, $t6, 0xC08C
    ctx->r14 = ctx->r14 | 0XC08C;
    // 0x802C6EB4: lui         $t5, 0xF200
    ctx->r13 = S32(0XF200 << 16);
    // 0x802C6EB8: lui         $t2, 0x800E
    ctx->r10 = S32(0X800E << 16);
    // 0x802C6EBC: addiu       $t2, $t2, -0x5640
    ctx->r10 = ADD32(ctx->r10, -0X5640);
    // 0x802C6EC0: sw          $t5, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r13;
    // 0x802C6EC4: sw          $t6, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r14;
    // 0x802C6EC8: lw          $t7, 0x0($t2)
    ctx->r15 = MEM_W(ctx->r10, 0X0);
    // 0x802C6ECC: lui         $t0, 0x802D
    ctx->r8 = S32(0X802D << 16);
    // 0x802C6ED0: addiu       $t0, $t0, -0x7430
    ctx->r8 = ADD32(ctx->r8, -0X7430);
    // 0x802C6ED4: sll         $t8, $t7, 1
    ctx->r24 = S32(ctx->r15 << 1);
    // 0x802C6ED8: addu        $t9, $t0, $t8
    ctx->r25 = ADD32(ctx->r8, ctx->r24);
    // 0x802C6EDC: lh          $t5, 0x0($t9)
    ctx->r13 = MEM_H(ctx->r25, 0X0);
    // 0x802C6EE0: lui         $at, 0xE400
    ctx->r1 = S32(0XE400 << 16);
    // 0x802C6EE4: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C6EE8: addiu       $t6, $t5, 0x48
    ctx->r14 = ADD32(ctx->r13, 0X48);
    // 0x802C6EEC: sll         $t7, $t6, 2
    ctx->r15 = S32(ctx->r14 << 2);
    // 0x802C6EF0: andi        $t8, $t7, 0xFFF
    ctx->r24 = ctx->r15 & 0XFFF;
    // 0x802C6EF4: sll         $t9, $t8, 12
    ctx->r25 = S32(ctx->r24 << 12);
    // 0x802C6EF8: or          $t5, $t9, $at
    ctx->r13 = ctx->r25 | ctx->r1;
    // 0x802C6EFC: ori         $t6, $t5, 0x16C
    ctx->r14 = ctx->r13 | 0X16C;
    // 0x802C6F00: or          $a2, $a0, $zero
    ctx->r6 = ctx->r4 | 0;
    // 0x802C6F04: sw          $t6, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r14;
    // 0x802C6F08: lw          $t7, 0x0($t2)
    ctx->r15 = MEM_W(ctx->r10, 0X0);
    // 0x802C6F0C: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C6F10: or          $a3, $a0, $zero
    ctx->r7 = ctx->r4 | 0;
    // 0x802C6F14: sll         $t8, $t7, 1
    ctx->r24 = S32(ctx->r15 << 1);
    // 0x802C6F18: addu        $t9, $t0, $t8
    ctx->r25 = ADD32(ctx->r8, ctx->r24);
    // 0x802C6F1C: lh          $t5, 0x0($t9)
    ctx->r13 = MEM_H(ctx->r25, 0X0);
    // 0x802C6F20: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C6F24: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x802C6F28: addiu       $t6, $t5, 0x8
    ctx->r14 = ADD32(ctx->r13, 0X8);
    // 0x802C6F2C: sll         $t7, $t6, 2
    ctx->r15 = S32(ctx->r14 << 2);
    // 0x802C6F30: andi        $t8, $t7, 0xFFF
    ctx->r24 = ctx->r15 & 0XFFF;
    // 0x802C6F34: sll         $t9, $t8, 12
    ctx->r25 = S32(ctx->r24 << 12);
    // 0x802C6F38: ori         $t5, $t9, 0xDC
    ctx->r13 = ctx->r25 | 0XDC;
    // 0x802C6F3C: sw          $t5, 0x4($a2)
    MEM_W(0X4, ctx->r6) = ctx->r13;
    // 0x802C6F40: lui         $t8, 0x400
    ctx->r24 = S32(0X400 << 16);
    // 0x802C6F44: lui         $t6, 0xB300
    ctx->r14 = S32(0XB300 << 16);
    // 0x802C6F48: sw          $t6, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r14;
    // 0x802C6F4C: ori         $t8, $t8, 0x400
    ctx->r24 = ctx->r24 | 0X400;
    // 0x802C6F50: sw          $zero, 0x4($a3)
    MEM_W(0X4, ctx->r7) = 0;
    // 0x802C6F54: lui         $t7, 0xB200
    ctx->r15 = S32(0XB200 << 16);
    // 0x802C6F58: sw          $t7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r15;
    // 0x802C6F5C: sw          $t8, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r24;
    // 0x802C6F60: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C6F64: jal         0x802C70EC
    // 0x802C6F68: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_i2_802C70EC(rdram, ctx);
        goto after_5;
    // 0x802C6F68: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_5:
    // 0x802C6F6C: lui         $t9, 0xB400
    ctx->r25 = S32(0XB400 << 16);
    // 0x802C6F70: sw          $t9, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r25;
    // 0x802C6F74: lui         $t5, 0x802D
    ctx->r13 = S32(0X802D << 16);
    // 0x802C6F78: lhu         $t5, -0x73B0($t5)
    ctx->r13 = MEM_HU(ctx->r13, -0X73B0);
    // 0x802C6F7C: lui         $t6, 0x103
    ctx->r14 = S32(0X103 << 16);
    // 0x802C6F80: ori         $t6, $t6, 0x40
    ctx->r14 = ctx->r14 | 0X40;
    // 0x802C6F84: sw          $t6, 0x8($v0)
    MEM_W(0X8, ctx->r2) = ctx->r14;
    // 0x802C6F88: lui         $t7, 0x700
    ctx->r15 = S32(0X700 << 16);
    // 0x802C6F8C: sw          $t5, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r13;
    // 0x802C6F90: addiu       $t7, $t7, 0xA40
    ctx->r15 = ADD32(ctx->r15, 0XA40);
    // 0x802C6F94: lui         $t8, 0x107
    ctx->r24 = S32(0X107 << 16);
    // 0x802C6F98: lui         $t9, 0x80C
    ctx->r25 = S32(0X80C << 16);
    // 0x802C6F9C: lui         $t5, 0x102
    ctx->r13 = S32(0X102 << 16);
    // 0x802C6FA0: lui         $t6, 0x700
    ctx->r14 = S32(0X700 << 16);
    // 0x802C6FA4: sw          $t7, 0xC($v0)
    MEM_W(0XC, ctx->r2) = ctx->r15;
    // 0x802C6FA8: addiu       $t8, $t8, -0xB78
    ctx->r24 = ADD32(ctx->r24, -0XB78);
    // 0x802C6FAC: addiu       $t9, $t9, -0x1B98
    ctx->r25 = ADD32(ctx->r25, -0X1B98);
    // 0x802C6FB0: addiu       $t6, $t6, 0xA80
    ctx->r14 = ADD32(ctx->r14, 0XA80);
    // 0x802C6FB4: ori         $t5, $t5, 0x40
    ctx->r13 = ctx->r13 | 0X40;
    // 0x802C6FB8: sw          $t8, 0x14($v0)
    MEM_W(0X14, ctx->r2) = ctx->r24;
    // 0x802C6FBC: sw          $s0, 0x10($v0)
    MEM_W(0X10, ctx->r2) = ctx->r16;
    // 0x802C6FC0: sw          $t9, 0x1C($v0)
    MEM_W(0X1C, ctx->r2) = ctx->r25;
    // 0x802C6FC4: sw          $s0, 0x18($v0)
    MEM_W(0X18, ctx->r2) = ctx->r16;
    // 0x802C6FC8: sw          $t5, 0x20($v0)
    MEM_W(0X20, ctx->r2) = ctx->r13;
    // 0x802C6FCC: sw          $t6, 0x24($v0)
    MEM_W(0X24, ctx->r2) = ctx->r14;
    // 0x802C6FD0: lui         $t7, 0x801D
    ctx->r15 = S32(0X801D << 16);
    // 0x802C6FD4: lw          $t7, -0x1A08($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X1A08);
    // 0x802C6FD8: addiu       $a0, $v0, 0x28
    ctx->r4 = ADD32(ctx->r2, 0X28);
    // 0x802C6FDC: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C6FE0: addiu       $t8, $t7, 0xC80
    ctx->r24 = ADD32(ctx->r15, 0XC80);
    // 0x802C6FE4: sw          $t8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r24;
    // 0x802C6FE8: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x802C6FEC: jal         0x801E4FE8
    // 0x802C6FF0: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_801E4FE8(rdram, ctx);
        goto after_6;
    // 0x802C6FF0: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_6:
    // 0x802C6FF4: lui         $t9, 0x80C
    ctx->r25 = S32(0X80C << 16);
    // 0x802C6FF8: lui         $t5, 0x102
    ctx->r13 = S32(0X102 << 16);
    // 0x802C6FFC: lui         $t6, 0x700
    ctx->r14 = S32(0X700 << 16);
    // 0x802C7000: addiu       $t9, $t9, -0x1B88
    ctx->r25 = ADD32(ctx->r25, -0X1B88);
    // 0x802C7004: addiu       $t6, $t6, 0xAC0
    ctx->r14 = ADD32(ctx->r14, 0XAC0);
    // 0x802C7008: ori         $t5, $t5, 0x40
    ctx->r13 = ctx->r13 | 0X40;
    // 0x802C700C: sw          $t9, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r25;
    // 0x802C7010: sw          $s0, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r16;
    // 0x802C7014: sw          $t5, 0x8($v0)
    MEM_W(0X8, ctx->r2) = ctx->r13;
    // 0x802C7018: sw          $t6, 0xC($v0)
    MEM_W(0XC, ctx->r2) = ctx->r14;
    // 0x802C701C: lui         $t7, 0x801D
    ctx->r15 = S32(0X801D << 16);
    // 0x802C7020: lw          $t7, -0x1A08($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X1A08);
    // 0x802C7024: addiu       $a0, $v0, 0x10
    ctx->r4 = ADD32(ctx->r2, 0X10);
    // 0x802C7028: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C702C: addiu       $t8, $t7, 0xD40
    ctx->r24 = ADD32(ctx->r15, 0XD40);
    // 0x802C7030: sw          $t8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r24;
    // 0x802C7034: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x802C7038: jal         0x801E4FE8
    // 0x802C703C: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_801E4FE8(rdram, ctx);
        goto after_7;
    // 0x802C703C: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_7:
    // 0x802C7040: lui         $t9, 0x80C
    ctx->r25 = S32(0X80C << 16);
    // 0x802C7044: lui         $t5, 0x102
    ctx->r13 = S32(0X102 << 16);
    // 0x802C7048: lui         $t6, 0x700
    ctx->r14 = S32(0X700 << 16);
    // 0x802C704C: addiu       $t9, $t9, -0x1B78
    ctx->r25 = ADD32(ctx->r25, -0X1B78);
    // 0x802C7050: addiu       $t6, $t6, 0xB00
    ctx->r14 = ADD32(ctx->r14, 0XB00);
    // 0x802C7054: ori         $t5, $t5, 0x40
    ctx->r13 = ctx->r13 | 0X40;
    // 0x802C7058: sw          $t9, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r25;
    // 0x802C705C: sw          $s0, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r16;
    // 0x802C7060: sw          $t5, 0x8($v0)
    MEM_W(0X8, ctx->r2) = ctx->r13;
    // 0x802C7064: sw          $t6, 0xC($v0)
    MEM_W(0XC, ctx->r2) = ctx->r14;
    // 0x802C7068: lui         $t7, 0x801D
    ctx->r15 = S32(0X801D << 16);
    // 0x802C706C: lw          $t7, -0x1A08($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X1A08);
    // 0x802C7070: addiu       $a0, $v0, 0x10
    ctx->r4 = ADD32(ctx->r2, 0X10);
    // 0x802C7074: addiu       $a1, $zero, 0x3
    ctx->r5 = ADD32(0, 0X3);
    // 0x802C7078: addiu       $t8, $t7, 0xE00
    ctx->r24 = ADD32(ctx->r15, 0XE00);
    // 0x802C707C: sw          $t8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r24;
    // 0x802C7080: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x802C7084: jal         0x801E4FE8
    // 0x802C7088: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_801E4FE8(rdram, ctx);
        goto after_8;
    // 0x802C7088: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_8:
    // 0x802C708C: lui         $t9, 0x80C
    ctx->r25 = S32(0X80C << 16);
    // 0x802C7090: lui         $t5, 0x102
    ctx->r13 = S32(0X102 << 16);
    // 0x802C7094: lui         $t6, 0x700
    ctx->r14 = S32(0X700 << 16);
    // 0x802C7098: addiu       $t9, $t9, -0x1B68
    ctx->r25 = ADD32(ctx->r25, -0X1B68);
    // 0x802C709C: addiu       $t6, $t6, 0xB40
    ctx->r14 = ADD32(ctx->r14, 0XB40);
    // 0x802C70A0: ori         $t5, $t5, 0x40
    ctx->r13 = ctx->r13 | 0X40;
    // 0x802C70A4: sw          $t9, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r25;
    // 0x802C70A8: sw          $s0, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r16;
    // 0x802C70AC: sw          $t5, 0x8($v0)
    MEM_W(0X8, ctx->r2) = ctx->r13;
    // 0x802C70B0: sw          $t6, 0xC($v0)
    MEM_W(0XC, ctx->r2) = ctx->r14;
    // 0x802C70B4: lui         $t7, 0x801D
    ctx->r15 = S32(0X801D << 16);
    // 0x802C70B8: lw          $t7, -0x1A08($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X1A08);
    // 0x802C70BC: addiu       $a0, $v0, 0x10
    ctx->r4 = ADD32(ctx->r2, 0X10);
    // 0x802C70C0: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C70C4: addiu       $t8, $t7, 0xEC0
    ctx->r24 = ADD32(ctx->r15, 0XEC0);
    // 0x802C70C8: sw          $t8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r24;
    // 0x802C70CC: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x802C70D0: jal         0x801E4FE8
    // 0x802C70D4: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_801E4FE8(rdram, ctx);
        goto after_9;
    // 0x802C70D4: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_9:
    // 0x802C70D8: lw          $ra, 0x24($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X24);
    // 0x802C70DC: lw          $s0, 0x20($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X20);
    // 0x802C70E0: addiu       $sp, $sp, 0x28
    ctx->r29 = ADD32(ctx->r29, 0X28);
    // 0x802C70E4: jr          $ra
    // 0x802C70E8: nop

    return;
    // 0x802C70E8: nop

;}
RECOMP_FUNC void func_i2_802C70EC(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C70EC: addiu       $sp, $sp, -0xF8
    ctx->r29 = ADD32(ctx->r29, -0XF8);
    // 0x802C70F0: sw          $s0, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r16;
    // 0x802C70F4: or          $s0, $a0, $zero
    ctx->r16 = ctx->r4 | 0;
    // 0x802C70F8: bne         $a1, $zero, L_802C710C
    if (ctx->r5 != 0) {
        // 0x802C70FC: sw          $ra, 0x44($sp)
        MEM_W(0X44, ctx->r29) = ctx->r31;
            goto L_802C710C;
    }
    // 0x802C70FC: sw          $ra, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r31;
    // 0x802C7100: addiu       $t6, $zero, 0x13
    ctx->r14 = ADD32(0, 0X13);
    // 0x802C7104: b           L_802C7114
    // 0x802C7108: sw          $t6, 0xDC($sp)
    MEM_W(0XDC, ctx->r29) = ctx->r14;
        goto L_802C7114;
    // 0x802C7108: sw          $t6, 0xDC($sp)
    MEM_W(0XDC, ctx->r29) = ctx->r14;
L_802C710C:
    // 0x802C710C: addiu       $t7, $zero, 0x101
    ctx->r15 = ADD32(0, 0X101);
    // 0x802C7110: sw          $t7, 0xDC($sp)
    MEM_W(0XDC, ctx->r29) = ctx->r15;
L_802C7114:
    // 0x802C7114: lui         $t8, 0x800E
    ctx->r24 = S32(0X800E << 16);
    // 0x802C7118: addiu       $t8, $t8, -0x5638
    ctx->r24 = ADD32(ctx->r24, -0X5638);
    // 0x802C711C: sll         $v0, $a1, 2
    ctx->r2 = S32(ctx->r5 << 2);
    // 0x802C7120: addu        $t9, $v0, $t8
    ctx->r25 = ADD32(ctx->r2, ctx->r24);
    // 0x802C7124: sw          $t9, 0x58($sp)
    MEM_W(0X58, ctx->r29) = ctx->r25;
    // 0x802C7128: lw          $t5, 0x0($t9)
    ctx->r13 = MEM_W(ctx->r25, 0X0);
    // 0x802C712C: lui         $t6, 0x802D
    ctx->r14 = S32(0X802D << 16);
    // 0x802C7130: addiu       $t6, $t6, -0x73A8
    ctx->r14 = ADD32(ctx->r14, -0X73A8);
    // 0x802C7134: beq         $t5, $zero, L_802C7148
    if (ctx->r13 == 0) {
        // 0x802C7138: addu        $t7, $v0, $t6
        ctx->r15 = ADD32(ctx->r2, ctx->r14);
            goto L_802C7148;
    }
    // 0x802C7138: addu        $t7, $v0, $t6
    ctx->r15 = ADD32(ctx->r2, ctx->r14);
    // 0x802C713C: sw          $t7, 0x54($sp)
    MEM_W(0X54, ctx->r29) = ctx->r15;
    // 0x802C7140: lw          $v1, 0x0($t7)
    ctx->r3 = MEM_W(ctx->r15, 0X0);
    // 0x802C7144: bne         $v1, $zero, L_802C719C
    if (ctx->r3 != 0) {
        // 0x802C7148: lui         $t9, 0x800E
        ctx->r25 = S32(0X800E << 16);
            goto L_802C719C;
    }
L_802C7148:
    // 0x802C7148: lui         $t9, 0x800E
    ctx->r25 = S32(0X800E << 16);
    // 0x802C714C: addiu       $t9, $t9, -0x5640
    ctx->r25 = ADD32(ctx->r25, -0X5640);
    // 0x802C7150: addu        $t4, $v0, $t9
    ctx->r12 = ADD32(ctx->r2, ctx->r25);
    // 0x802C7154: sw          $t4, 0x4C($sp)
    MEM_W(0X4C, ctx->r29) = ctx->r12;
    // 0x802C7158: lw          $t6, 0x0($t4)
    ctx->r14 = MEM_W(ctx->r12, 0X0);
    // 0x802C715C: lui         $t8, 0x802D
    ctx->r24 = S32(0X802D << 16);
    // 0x802C7160: lui         $t5, 0x802D
    ctx->r13 = S32(0X802D << 16);
    // 0x802C7164: sll         $t7, $t6, 2
    ctx->r15 = S32(ctx->r14 << 2);
    // 0x802C7168: addu        $t8, $t8, $t7
    ctx->r24 = ADD32(ctx->r24, ctx->r15);
    // 0x802C716C: lw          $t8, -0x7428($t8)
    ctx->r24 = MEM_W(ctx->r24, -0X7428);
    // 0x802C7170: addiu       $t5, $t5, -0x73A8
    ctx->r13 = ADD32(ctx->r13, -0X73A8);
    // 0x802C7174: lui         $t4, 0x800E
    ctx->r12 = S32(0X800E << 16);
    // 0x802C7178: sll         $t9, $t8, 3
    ctx->r25 = S32(ctx->r24 << 3);
    // 0x802C717C: subu        $t9, $t9, $t8
    ctx->r25 = SUB32(ctx->r25, ctx->r24);
    // 0x802C7180: sll         $t9, $t9, 1
    ctx->r25 = S32(ctx->r25 << 1);
    // 0x802C7184: addiu       $t4, $t4, -0x56B0
    ctx->r12 = ADD32(ctx->r12, -0X56B0);
    // 0x802C7188: addu        $a0, $v0, $t5
    ctx->r4 = ADD32(ctx->r2, ctx->r13);
    // 0x802C718C: lw          $v1, 0x0($a0)
    ctx->r3 = MEM_W(ctx->r4, 0X0);
    // 0x802C7190: sw          $a0, 0x54($sp)
    MEM_W(0X54, ctx->r29) = ctx->r4;
    // 0x802C7194: b           L_802C71E8
    // 0x802C7198: addu        $t0, $t9, $t4
    ctx->r8 = ADD32(ctx->r25, ctx->r12);
        goto L_802C71E8;
    // 0x802C7198: addu        $t0, $t9, $t4
    ctx->r8 = ADD32(ctx->r25, ctx->r12);
L_802C719C:
    // 0x802C719C: lui         $t6, 0x800E
    ctx->r14 = S32(0X800E << 16);
    // 0x802C71A0: addiu       $t6, $t6, -0x5640
    ctx->r14 = ADD32(ctx->r14, -0X5640);
    // 0x802C71A4: addu        $a0, $v0, $t6
    ctx->r4 = ADD32(ctx->r2, ctx->r14);
    // 0x802C71A8: lw          $t8, 0x0($a0)
    ctx->r24 = MEM_W(ctx->r4, 0X0);
    // 0x802C71AC: lui         $t4, 0x802D
    ctx->r12 = S32(0X802D << 16);
    // 0x802C71B0: sll         $t7, $a1, 3
    ctx->r15 = S32(ctx->r5 << 3);
    // 0x802C71B4: sll         $t9, $t8, 2
    ctx->r25 = S32(ctx->r24 << 2);
    // 0x802C71B8: addu        $t4, $t4, $t9
    ctx->r12 = ADD32(ctx->r12, ctx->r25);
    // 0x802C71BC: lw          $t4, -0x7428($t4)
    ctx->r12 = MEM_W(ctx->r12, -0X7428);
    // 0x802C71C0: subu        $t7, $t7, $a1
    ctx->r15 = SUB32(ctx->r15, ctx->r5);
    // 0x802C71C4: sll         $t7, $t7, 3
    ctx->r15 = S32(ctx->r15 << 3);
    // 0x802C71C8: sll         $t5, $t4, 3
    ctx->r13 = S32(ctx->r12 << 3);
    // 0x802C71CC: subu        $t5, $t5, $t4
    ctx->r13 = SUB32(ctx->r13, ctx->r12);
    // 0x802C71D0: sll         $t5, $t5, 1
    ctx->r13 = S32(ctx->r13 << 1);
    // 0x802C71D4: lui         $t8, 0x801D
    ctx->r24 = S32(0X801D << 16);
    // 0x802C71D8: addiu       $t8, $t8, -0x4D68
    ctx->r24 = ADD32(ctx->r24, -0X4D68);
    // 0x802C71DC: addu        $t6, $t7, $t5
    ctx->r14 = ADD32(ctx->r15, ctx->r13);
    // 0x802C71E0: addu        $t0, $t6, $t8
    ctx->r8 = ADD32(ctx->r14, ctx->r24);
    // 0x802C71E4: sw          $a0, 0x4C($sp)
    MEM_W(0X4C, ctx->r29) = ctx->r4;
L_802C71E8:
    // 0x802C71E8: slti        $at, $v1, 0x2
    ctx->r1 = SIGNED(ctx->r3) < 0X2 ? 1 : 0;
    // 0x802C71EC: or          $t1, $zero, $zero
    ctx->r9 = 0 | 0;
    // 0x802C71F0: sw          $zero, 0xF0($sp)
    MEM_W(0XF0, ctx->r29) = 0;
    // 0x802C71F4: sw          $zero, 0xEC($sp)
    MEM_W(0XEC, ctx->r29) = 0;
    // 0x802C71F8: sw          $zero, 0xE8($sp)
    MEM_W(0XE8, ctx->r29) = 0;
    // 0x802C71FC: bne         $at, $zero, L_802C720C
    if (ctx->r1 != 0) {
        // 0x802C7200: sw          $zero, 0xE4($sp)
        MEM_W(0XE4, ctx->r29) = 0;
            goto L_802C720C;
    }
    // 0x802C7200: sw          $zero, 0xE4($sp)
    MEM_W(0XE4, ctx->r29) = 0;
    // 0x802C7204: addiu       $t9, $zero, 0x1
    ctx->r25 = ADD32(0, 0X1);
    // 0x802C7208: sw          $t9, 0xE8($sp)
    MEM_W(0XE8, ctx->r29) = ctx->r25;
L_802C720C:
    // 0x802C720C: blez        $v1, L_802C7224
    if (SIGNED(ctx->r3) <= 0) {
        // 0x802C7210: lui         $t7, 0x801D
        ctx->r15 = S32(0X801D << 16);
            goto L_802C7224;
    }
    // 0x802C7210: lui         $t7, 0x801D
    ctx->r15 = S32(0X801D << 16);
    // 0x802C7214: addiu       $at, $zero, 0x6
    ctx->r1 = ADD32(0, 0X6);
    // 0x802C7218: beq         $v1, $at, L_802C7224
    if (ctx->r3 == ctx->r1) {
        // 0x802C721C: addiu       $t4, $zero, 0x1
        ctx->r12 = ADD32(0, 0X1);
            goto L_802C7224;
    }
    // 0x802C721C: addiu       $t4, $zero, 0x1
    ctx->r12 = ADD32(0, 0X1);
    // 0x802C7220: sw          $t4, 0xE4($sp)
    MEM_W(0XE4, ctx->r29) = ctx->r12;
L_802C7224:
    // 0x802C7224: lh          $t7, -0x19F4($t7)
    ctx->r15 = MEM_H(ctx->r15, -0X19F4);
    // 0x802C7228: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x802C722C: bne         $t7, $at, L_802C725C
    if (ctx->r15 != ctx->r1) {
        // 0x802C7230: addiu       $at, $zero, 0x5
        ctx->r1 = ADD32(0, 0X5);
            goto L_802C725C;
    }
    // 0x802C7230: addiu       $at, $zero, 0x5
    ctx->r1 = ADD32(0, 0X5);
    // 0x802C7234: beq         $v1, $at, L_802C7240
    if (ctx->r3 == ctx->r1) {
        // 0x802C7238: addiu       $t5, $zero, 0x1
        ctx->r13 = ADD32(0, 0X1);
            goto L_802C7240;
    }
    // 0x802C7238: addiu       $t5, $zero, 0x1
    ctx->r13 = ADD32(0, 0X1);
    // 0x802C723C: addiu       $t1, $zero, 0x1
    ctx->r9 = ADD32(0, 0X1);
L_802C7240:
    // 0x802C7240: lw          $t8, 0xDC($sp)
    ctx->r24 = MEM_W(ctx->r29, 0XDC);
    // 0x802C7244: addiu       $t6, $zero, 0x1
    ctx->r14 = ADD32(0, 0X1);
    // 0x802C7248: sw          $t5, 0xF0($sp)
    MEM_W(0XF0, ctx->r29) = ctx->r13;
    // 0x802C724C: addiu       $t9, $t8, 0x109
    ctx->r25 = ADD32(ctx->r24, 0X109);
    // 0x802C7250: sw          $t6, 0xEC($sp)
    MEM_W(0XEC, ctx->r29) = ctx->r14;
    // 0x802C7254: b           L_802C7294
    // 0x802C7258: sw          $t9, 0xD8($sp)
    MEM_W(0XD8, ctx->r29) = ctx->r25;
        goto L_802C7294;
    // 0x802C7258: sw          $t9, 0xD8($sp)
    MEM_W(0XD8, ctx->r29) = ctx->r25;
L_802C725C:
    // 0x802C725C: blez        $v1, L_802C7270
    if (SIGNED(ctx->r3) <= 0) {
        // 0x802C7260: slti        $at, $v1, 0x5
        ctx->r1 = SIGNED(ctx->r3) < 0X5 ? 1 : 0;
            goto L_802C7270;
    }
    // 0x802C7260: slti        $at, $v1, 0x5
    ctx->r1 = SIGNED(ctx->r3) < 0X5 ? 1 : 0;
    // 0x802C7264: beq         $at, $zero, L_802C7270
    if (ctx->r1 == 0) {
        // 0x802C7268: nop
    
            goto L_802C7270;
    }
    // 0x802C7268: nop

    // 0x802C726C: addiu       $t1, $zero, 0x1
    ctx->r9 = ADD32(0, 0X1);
L_802C7270:
    // 0x802C7270: blez        $v1, L_802C727C
    if (SIGNED(ctx->r3) <= 0) {
        // 0x802C7274: addiu       $t4, $zero, 0x1
        ctx->r12 = ADD32(0, 0X1);
            goto L_802C727C;
    }
    // 0x802C7274: addiu       $t4, $zero, 0x1
    ctx->r12 = ADD32(0, 0X1);
    // 0x802C7278: sw          $t4, 0xF0($sp)
    MEM_W(0XF0, ctx->r29) = ctx->r12;
L_802C727C:
    // 0x802C727C: bne         $v1, $zero, L_802C7288
    if (ctx->r3 != 0) {
        // 0x802C7280: addiu       $t7, $zero, 0x1
        ctx->r15 = ADD32(0, 0X1);
            goto L_802C7288;
    }
    // 0x802C7280: addiu       $t7, $zero, 0x1
    ctx->r15 = ADD32(0, 0X1);
    // 0x802C7284: sw          $t7, 0xEC($sp)
    MEM_W(0XEC, ctx->r29) = ctx->r15;
L_802C7288:
    // 0x802C7288: lw          $t5, 0xDC($sp)
    ctx->r13 = MEM_W(ctx->r29, 0XDC);
    // 0x802C728C: addiu       $t6, $t5, 0x1B
    ctx->r14 = ADD32(ctx->r13, 0X1B);
    // 0x802C7290: sw          $t6, 0xD8($sp)
    MEM_W(0XD8, ctx->r29) = ctx->r14;
L_802C7294:
    // 0x802C7294: beq         $t1, $zero, L_802C7554
    if (ctx->r9 == 0) {
        // 0x802C7298: sw          $t1, 0xF4($sp)
        MEM_W(0XF4, ctx->r29) = ctx->r9;
            goto L_802C7554;
    }
    // 0x802C7298: sw          $t1, 0xF4($sp)
    MEM_W(0XF4, ctx->r29) = ctx->r9;
    // 0x802C729C: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
    // 0x802C72A0: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C72A4: lui         $t2, 0xE700
    ctx->r10 = S32(0XE700 << 16);
    // 0x802C72A8: or          $v1, $s0, $zero
    ctx->r3 = ctx->r16 | 0;
    // 0x802C72AC: sw          $t2, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r10;
    // 0x802C72B0: sw          $zero, 0x4($v0)
    MEM_W(0X4, ctx->r2) = 0;
    // 0x802C72B4: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C72B8: lui         $t8, 0xB900
    ctx->r24 = S32(0XB900 << 16);
    // 0x802C72BC: lui         $t9, 0xF0A
    ctx->r25 = S32(0XF0A << 16);
    // 0x802C72C0: ori         $t9, $t9, 0x4000
    ctx->r25 = ctx->r25 | 0X4000;
    // 0x802C72C4: ori         $t8, $t8, 0x31D
    ctx->r24 = ctx->r24 | 0X31D;
    // 0x802C72C8: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x802C72CC: sw          $t8, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r24;
    // 0x802C72D0: sw          $t9, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r25;
    // 0x802C72D4: lui         $t4, 0xFCFF
    ctx->r12 = S32(0XFCFF << 16);
    // 0x802C72D8: lui         $t7, 0xFFFC
    ctx->r15 = S32(0XFFFC << 16);
    // 0x802C72DC: ori         $t7, $t7, 0xF279
    ctx->r15 = ctx->r15 | 0XF279;
    // 0x802C72E0: ori         $t4, $t4, 0xFFFF
    ctx->r12 = ctx->r12 | 0XFFFF;
    // 0x802C72E4: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C72E8: sw          $t4, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r12;
    // 0x802C72EC: sw          $t7, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r15;
    // 0x802C72F0: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    // 0x802C72F4: lui         $t5, 0xFD10
    ctx->r13 = S32(0XFD10 << 16);
    // 0x802C72F8: ori         $t5, $t5, 0x8
    ctx->r13 = ctx->r13 | 0X8;
    // 0x802C72FC: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C7300: lui         $t6, 0x80B
    ctx->r14 = S32(0X80B << 16);
    // 0x802C7304: addiu       $t6, $t6, 0x6518
    ctx->r14 = ADD32(ctx->r14, 0X6518);
    // 0x802C7308: or          $a2, $s0, $zero
    ctx->r6 = ctx->r16 | 0;
    // 0x802C730C: sw          $t5, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r13;
    // 0x802C7310: lui         $t8, 0x708
    ctx->r24 = S32(0X708 << 16);
    // 0x802C7314: lui         $a3, 0xF510
    ctx->r7 = S32(0XF510 << 16);
    // 0x802C7318: ori         $t8, $t8, 0x200
    ctx->r24 = ctx->r24 | 0X200;
    // 0x802C731C: sw          $t6, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r14;
    // 0x802C7320: ori         $a3, $a3, 0x600
    ctx->r7 = ctx->r7 | 0X600;
    // 0x802C7324: sw          $t8, 0x4($a2)
    MEM_W(0X4, ctx->r6) = ctx->r24;
    // 0x802C7328: sw          $a3, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r7;
    // 0x802C732C: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C7330: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
    // 0x802C7334: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C7338: sw          $t1, 0xF4($sp)
    MEM_W(0XF4, ctx->r29) = ctx->r9;
    // 0x802C733C: or          $v1, $s0, $zero
    ctx->r3 = ctx->r16 | 0;
    // 0x802C7340: lui         $t9, 0xE600
    ctx->r25 = S32(0XE600 << 16);
    // 0x802C7344: sw          $t9, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r25;
    // 0x802C7348: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C734C: sw          $zero, 0x4($v0)
    MEM_W(0X4, ctx->r2) = 0;
    // 0x802C7350: lui         $t7, 0x702
    ctx->r15 = S32(0X702 << 16);
    // 0x802C7354: ori         $t7, $t7, 0x14
    ctx->r15 = ctx->r15 | 0X14;
    // 0x802C7358: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x802C735C: lui         $t4, 0xF400
    ctx->r12 = S32(0XF400 << 16);
    // 0x802C7360: sw          $t4, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r12;
    // 0x802C7364: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C7368: sw          $t7, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r15;
    // 0x802C736C: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    // 0x802C7370: sw          $zero, 0x4($a0)
    MEM_W(0X4, ctx->r4) = 0;
    // 0x802C7374: sw          $t2, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r10;
    // 0x802C7378: lui         $t5, 0x8
    ctx->r13 = S32(0X8 << 16);
    // 0x802C737C: ori         $t5, $t5, 0x200
    ctx->r13 = ctx->r13 | 0X200;
    // 0x802C7380: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C7384: or          $a2, $s0, $zero
    ctx->r6 = ctx->r16 | 0;
    // 0x802C7388: sw          $t5, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r13;
    // 0x802C738C: sw          $a3, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r7;
    // 0x802C7390: lui         $t8, 0x2
    ctx->r24 = S32(0X2 << 16);
    // 0x802C7394: ori         $t8, $t8, 0x14
    ctx->r24 = ctx->r24 | 0X14;
    // 0x802C7398: lui         $t6, 0xF200
    ctx->r14 = S32(0XF200 << 16);
    // 0x802C739C: sw          $t6, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r14;
    // 0x802C73A0: sw          $t8, 0x4($a2)
    MEM_W(0X4, ctx->r6) = ctx->r24;
    // 0x802C73A4: lb          $t9, 0xB($t0)
    ctx->r25 = MEM_B(ctx->r8, 0XB);
    // 0x802C73A8: addiu       $a1, $zero, 0xA
    ctx->r5 = ADD32(0, 0XA);
    // 0x802C73AC: lw          $t1, 0xDC($sp)
    ctx->r9 = MEM_W(ctx->r29, 0XDC);
    // 0x802C73B0: multu       $t9, $a1
    result = U64(U32(ctx->r25)) * U64(U32(ctx->r5)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x802C73B4: lui         $t2, 0xE400
    ctx->r10 = S32(0XE400 << 16);
    // 0x802C73B8: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C73BC: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
    // 0x802C73C0: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C73C4: or          $v1, $s0, $zero
    ctx->r3 = ctx->r16 | 0;
    // 0x802C73C8: lui         $t3, 0xB300
    ctx->r11 = S32(0XB300 << 16);
    // 0x802C73CC: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C73D0: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x802C73D4: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C73D8: mflo        $t4
    ctx->r12 = lo;
    // 0x802C73DC: addu        $t7, $t4, $t1
    ctx->r15 = ADD32(ctx->r12, ctx->r9);
    // 0x802C73E0: addiu       $t5, $t7, 0x17
    ctx->r13 = ADD32(ctx->r15, 0X17);
    // 0x802C73E4: sll         $t6, $t5, 2
    ctx->r14 = S32(ctx->r13 << 2);
    // 0x802C73E8: andi        $t8, $t6, 0xFFF
    ctx->r24 = ctx->r14 & 0XFFF;
    // 0x802C73EC: sll         $t9, $t8, 12
    ctx->r25 = S32(ctx->r24 << 12);
    // 0x802C73F0: or          $t4, $t9, $t2
    ctx->r12 = ctx->r25 | ctx->r10;
    // 0x802C73F4: ori         $t7, $t4, 0x264
    ctx->r15 = ctx->r12 | 0X264;
    // 0x802C73F8: sw          $t7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r15;
    // 0x802C73FC: lb          $t5, 0xB($t0)
    ctx->r13 = MEM_B(ctx->r8, 0XB);
    // 0x802C7400: or          $a2, $s0, $zero
    ctx->r6 = ctx->r16 | 0;
    // 0x802C7404: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C7408: multu       $t5, $a1
    result = U64(U32(ctx->r13)) * U64(U32(ctx->r5)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x802C740C: mflo        $t6
    ctx->r14 = lo;
    // 0x802C7410: addu        $t8, $t6, $t1
    ctx->r24 = ADD32(ctx->r14, ctx->r9);
    // 0x802C7414: addiu       $t9, $t8, 0xE
    ctx->r25 = ADD32(ctx->r24, 0XE);
    // 0x802C7418: sll         $t4, $t9, 2
    ctx->r12 = S32(ctx->r25 << 2);
    // 0x802C741C: andi        $t7, $t4, 0xFFF
    ctx->r15 = ctx->r12 & 0XFFF;
    // 0x802C7420: sll         $t5, $t7, 12
    ctx->r13 = S32(ctx->r15 << 12);
    // 0x802C7424: ori         $t6, $t5, 0x24C
    ctx->r14 = ctx->r13 | 0X24C;
    // 0x802C7428: sw          $t6, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r14;
    // 0x802C742C: sw          $zero, 0x4($v1)
    MEM_W(0X4, ctx->r3) = 0;
    // 0x802C7430: sw          $t3, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r11;
    // 0x802C7434: lui         $t9, 0x400
    ctx->r25 = S32(0X400 << 16);
    // 0x802C7438: ori         $t9, $t9, 0x400
    ctx->r25 = ctx->r25 | 0X400;
    // 0x802C743C: lui         $t8, 0xB200
    ctx->r24 = S32(0XB200 << 16);
    // 0x802C7440: sw          $t8, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r24;
    // 0x802C7444: sw          $t9, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r25;
    // 0x802C7448: lb          $t4, 0xC($t0)
    ctx->r12 = MEM_B(ctx->r8, 0XC);
    // 0x802C744C: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
    // 0x802C7450: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C7454: multu       $t4, $a1
    result = U64(U32(ctx->r12)) * U64(U32(ctx->r5)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x802C7458: or          $v1, $s0, $zero
    ctx->r3 = ctx->r16 | 0;
    // 0x802C745C: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C7460: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x802C7464: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C7468: or          $a3, $s0, $zero
    ctx->r7 = ctx->r16 | 0;
    // 0x802C746C: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C7470: mflo        $t7
    ctx->r15 = lo;
    // 0x802C7474: addu        $t5, $t7, $t1
    ctx->r13 = ADD32(ctx->r15, ctx->r9);
    // 0x802C7478: addiu       $t6, $t5, 0x17
    ctx->r14 = ADD32(ctx->r13, 0X17);
    // 0x802C747C: sll         $t8, $t6, 2
    ctx->r24 = S32(ctx->r14 << 2);
    // 0x802C7480: andi        $t9, $t8, 0xFFF
    ctx->r25 = ctx->r24 & 0XFFF;
    // 0x802C7484: sll         $t4, $t9, 12
    ctx->r12 = S32(ctx->r25 << 12);
    // 0x802C7488: or          $t7, $t4, $t2
    ctx->r15 = ctx->r12 | ctx->r10;
    // 0x802C748C: ori         $t5, $t7, 0x2D8
    ctx->r13 = ctx->r15 | 0X2D8;
    // 0x802C7490: sw          $t5, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r13;
    // 0x802C7494: lb          $t6, 0xC($t0)
    ctx->r14 = MEM_B(ctx->r8, 0XC);
    // 0x802C7498: multu       $t6, $a1
    result = U64(U32(ctx->r14)) * U64(U32(ctx->r5)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x802C749C: mflo        $t8
    ctx->r24 = lo;
    // 0x802C74A0: addu        $t9, $t8, $t1
    ctx->r25 = ADD32(ctx->r24, ctx->r9);
    // 0x802C74A4: addiu       $t4, $t9, 0xE
    ctx->r12 = ADD32(ctx->r25, 0XE);
    // 0x802C74A8: sll         $t7, $t4, 2
    ctx->r15 = S32(ctx->r12 << 2);
    // 0x802C74AC: andi        $t5, $t7, 0xFFF
    ctx->r13 = ctx->r15 & 0XFFF;
    // 0x802C74B0: sll         $t6, $t5, 12
    ctx->r14 = S32(ctx->r13 << 12);
    // 0x802C74B4: ori         $t8, $t6, 0x2C0
    ctx->r24 = ctx->r14 | 0X2C0;
    // 0x802C74B8: sw          $t8, 0x4($a2)
    MEM_W(0X4, ctx->r6) = ctx->r24;
    // 0x802C74BC: sw          $zero, 0x4($v0)
    MEM_W(0X4, ctx->r2) = 0;
    // 0x802C74C0: sw          $t3, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r11;
    // 0x802C74C4: lui         $t4, 0x400
    ctx->r12 = S32(0X400 << 16);
    // 0x802C74C8: ori         $t4, $t4, 0x400
    ctx->r12 = ctx->r12 | 0X400;
    // 0x802C74CC: lui         $t9, 0xB200
    ctx->r25 = S32(0XB200 << 16);
    // 0x802C74D0: sw          $t9, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r25;
    // 0x802C74D4: sw          $t4, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r12;
    // 0x802C74D8: lb          $t7, 0xD($t0)
    ctx->r15 = MEM_B(ctx->r8, 0XD);
    // 0x802C74DC: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
    // 0x802C74E0: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C74E4: multu       $t7, $a1
    result = U64(U32(ctx->r15)) * U64(U32(ctx->r5)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x802C74E8: mflo        $t5
    ctx->r13 = lo;
    // 0x802C74EC: addu        $t6, $t5, $t1
    ctx->r14 = ADD32(ctx->r13, ctx->r9);
    // 0x802C74F0: addiu       $t8, $t6, 0x17
    ctx->r24 = ADD32(ctx->r14, 0X17);
    // 0x802C74F4: sll         $t9, $t8, 2
    ctx->r25 = S32(ctx->r24 << 2);
    // 0x802C74F8: andi        $t4, $t9, 0xFFF
    ctx->r12 = ctx->r25 & 0XFFF;
    // 0x802C74FC: sll         $t7, $t4, 12
    ctx->r15 = S32(ctx->r12 << 12);
    // 0x802C7500: or          $t5, $t7, $t2
    ctx->r13 = ctx->r15 | ctx->r10;
    // 0x802C7504: ori         $t6, $t5, 0x34C
    ctx->r14 = ctx->r13 | 0X34C;
    // 0x802C7508: sw          $t6, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r14;
    // 0x802C750C: lb          $t8, 0xD($t0)
    ctx->r24 = MEM_B(ctx->r8, 0XD);
    // 0x802C7510: multu       $t8, $a1
    result = U64(U32(ctx->r24)) * U64(U32(ctx->r5)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x802C7514: mflo        $t9
    ctx->r25 = lo;
    // 0x802C7518: addu        $t4, $t9, $t1
    ctx->r12 = ADD32(ctx->r25, ctx->r9);
    // 0x802C751C: addiu       $t7, $t4, 0xE
    ctx->r15 = ADD32(ctx->r12, 0XE);
    // 0x802C7520: sll         $t5, $t7, 2
    ctx->r13 = S32(ctx->r15 << 2);
    // 0x802C7524: andi        $t6, $t5, 0xFFF
    ctx->r14 = ctx->r13 & 0XFFF;
    // 0x802C7528: sll         $t8, $t6, 12
    ctx->r24 = S32(ctx->r14 << 12);
    // 0x802C752C: ori         $t9, $t8, 0x334
    ctx->r25 = ctx->r24 | 0X334;
    // 0x802C7530: sw          $t9, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r25;
    // 0x802C7534: lui         $t4, 0xB300
    ctx->r12 = S32(0XB300 << 16);
    // 0x802C7538: sw          $t4, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r12;
    // 0x802C753C: sw          $zero, 0x4($a3)
    MEM_W(0X4, ctx->r7) = 0;
    // 0x802C7540: lui         $t5, 0x400
    ctx->r13 = S32(0X400 << 16);
    // 0x802C7544: ori         $t5, $t5, 0x400
    ctx->r13 = ctx->r13 | 0X400;
    // 0x802C7548: lui         $t7, 0xB200
    ctx->r15 = S32(0XB200 << 16);
    // 0x802C754C: sw          $t7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r15;
    // 0x802C7550: sw          $t5, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r13;
L_802C7554:
    // 0x802C7554: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C7558: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C755C: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C7560: addiu       $t4, $zero, 0xFF
    ctx->r12 = ADD32(0, 0XFF);
    // 0x802C7564: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C7568: addiu       $t5, $zero, 0xFF
    ctx->r13 = ADD32(0, 0XFF);
    // 0x802C756C: sw          $t5, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r13;
    // 0x802C7570: sw          $t7, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r15;
    // 0x802C7574: sw          $t4, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r12;
    // 0x802C7578: sw          $t4, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r12;
    // 0x802C757C: sw          $t9, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r25;
    // 0x802C7580: sw          $t9, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r25;
    // 0x802C7584: sw          $t8, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r24;
    // 0x802C7588: sw          $t8, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r24;
    // 0x802C758C: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x802C7590: sw          $t6, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r14;
    // 0x802C7594: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x802C7598: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C759C: addiu       $a2, $zero, 0xFF
    ctx->r6 = ADD32(0, 0XFF);
    // 0x802C75A0: jal         0x801E946C
    // 0x802C75A4: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    func_801E946C(rdram, ctx);
        goto after_0;
    // 0x802C75A4: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    after_0:
    // 0x802C75A8: lw          $t7, 0x4C($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X4C);
    // 0x802C75AC: lui         $t5, 0x800E
    ctx->r13 = S32(0X800E << 16);
    // 0x802C75B0: addiu       $t5, $t5, -0x5640
    ctx->r13 = ADD32(ctx->r13, -0X5640);
    // 0x802C75B4: bne         $t7, $t5, L_802C7620
    if (ctx->r15 != ctx->r13) {
        // 0x802C75B8: or          $s0, $v0, $zero
        ctx->r16 = ctx->r2 | 0;
            goto L_802C7620;
    }
    // 0x802C75B8: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
    // 0x802C75BC: addiu       $t6, $zero, 0x1C
    ctx->r14 = ADD32(0, 0X1C);
    // 0x802C75C0: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x802C75C4: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C75C8: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C75CC: addiu       $a2, $zero, 0x3
    ctx->r6 = ADD32(0, 0X3);
    // 0x802C75D0: addiu       $a3, $zero, 0x26
    ctx->r7 = ADD32(0, 0X26);
    // 0x802C75D4: jal         0x801E3EE0
    // 0x802C75D8: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    func_801E3EE0(rdram, ctx);
        goto after_1;
    // 0x802C75D8: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    after_1:
    // 0x802C75DC: addiu       $t8, $zero, 0x1A
    ctx->r24 = ADD32(0, 0X1A);
    // 0x802C75E0: sw          $t8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r24;
    // 0x802C75E4: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C75E8: addiu       $a1, $zero, 0x4
    ctx->r5 = ADD32(0, 0X4);
    // 0x802C75EC: addiu       $a2, $zero, 0xC
    ctx->r6 = ADD32(0, 0XC);
    // 0x802C75F0: addiu       $a3, $zero, 0x146
    ctx->r7 = ADD32(0, 0X146);
    // 0x802C75F4: jal         0x801E3EE0
    // 0x802C75F8: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    func_801E3EE0(rdram, ctx);
        goto after_2;
    // 0x802C75F8: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    after_2:
    // 0x802C75FC: addiu       $t9, $zero, 0x25
    ctx->r25 = ADD32(0, 0X25);
    // 0x802C7600: sw          $t9, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r25;
    // 0x802C7604: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C7608: addiu       $a1, $zero, 0x4
    ctx->r5 = ADD32(0, 0X4);
    // 0x802C760C: addiu       $a2, $zero, 0xD
    ctx->r6 = ADD32(0, 0XD);
    // 0x802C7610: addiu       $a3, $zero, 0x146
    ctx->r7 = ADD32(0, 0X146);
    // 0x802C7614: jal         0x801E3EE0
    // 0x802C7618: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    func_801E3EE0(rdram, ctx);
        goto after_3;
    // 0x802C7618: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    after_3:
    // 0x802C761C: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
L_802C7620:
    // 0x802C7620: lw          $t4, 0xF4($sp)
    ctx->r12 = MEM_W(ctx->r29, 0XF4);
    // 0x802C7624: lw          $t7, 0x54($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X54);
    // 0x802C7628: beql        $t4, $zero, L_802C77CC
    if (ctx->r12 == 0) {
        // 0x802C762C: lw          $t7, 0xEC($sp)
        ctx->r15 = MEM_W(ctx->r29, 0XEC);
            goto L_802C77CC;
    }
    goto skip_0;
    // 0x802C762C: lw          $t7, 0xEC($sp)
    ctx->r15 = MEM_W(ctx->r29, 0XEC);
    skip_0:
    // 0x802C7630: lw          $t5, 0x0($t7)
    ctx->r13 = MEM_W(ctx->r15, 0X0);
    // 0x802C7634: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x802C7638: lw          $t6, 0xE8($sp)
    ctx->r14 = MEM_W(ctx->r29, 0XE8);
    // 0x802C763C: bne         $t5, $at, L_802C764C
    if (ctx->r13 != ctx->r1) {
        // 0x802C7640: or          $a0, $s0, $zero
        ctx->r4 = ctx->r16 | 0;
            goto L_802C764C;
    }
    // 0x802C7640: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x802C7644: bnel        $t6, $zero, L_802C7674
    if (ctx->r14 != 0) {
        // 0x802C7648: lw          $a3, 0xDC($sp)
        ctx->r7 = MEM_W(ctx->r29, 0XDC);
            goto L_802C7674;
    }
    goto skip_1;
    // 0x802C7648: lw          $a3, 0xDC($sp)
    ctx->r7 = MEM_W(ctx->r29, 0XDC);
    skip_1:
L_802C764C:
    // 0x802C764C: lw          $a3, 0xDC($sp)
    ctx->r7 = MEM_W(ctx->r29, 0XDC);
    // 0x802C7650: addiu       $t8, $zero, 0x80
    ctx->r24 = ADD32(0, 0X80);
    // 0x802C7654: sw          $t8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r24;
    // 0x802C7658: addiu       $a1, $zero, 0x4
    ctx->r5 = ADD32(0, 0X4);
    // 0x802C765C: addiu       $a2, $zero, 0x9
    ctx->r6 = ADD32(0, 0X9);
    // 0x802C7660: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    // 0x802C7664: jal         0x801E3EE0
    // 0x802C7668: addiu       $a3, $a3, 0xD
    ctx->r7 = ADD32(ctx->r7, 0XD);
    func_801E3EE0(rdram, ctx);
        goto after_4;
    // 0x802C7668: addiu       $a3, $a3, 0xD
    ctx->r7 = ADD32(ctx->r7, 0XD);
    after_4:
    // 0x802C766C: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
    // 0x802C7670: lw          $a3, 0xDC($sp)
    ctx->r7 = MEM_W(ctx->r29, 0XDC);
L_802C7674:
    // 0x802C7674: addiu       $t9, $zero, 0x8A
    ctx->r25 = ADD32(0, 0X8A);
    // 0x802C7678: sw          $t9, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r25;
    // 0x802C767C: addiu       $a3, $a3, 0xD
    ctx->r7 = ADD32(ctx->r7, 0XD);
    // 0x802C7680: sw          $a3, 0x5C($sp)
    MEM_W(0X5C, ctx->r29) = ctx->r7;
    // 0x802C7684: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x802C7688: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C768C: addiu       $a2, $zero, 0x6
    ctx->r6 = ADD32(0, 0X6);
    // 0x802C7690: jal         0x801E3EE0
    // 0x802C7694: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    func_801E3EE0(rdram, ctx);
        goto after_5;
    // 0x802C7694: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    after_5:
    // 0x802C7698: lw          $a3, 0xDC($sp)
    ctx->r7 = MEM_W(ctx->r29, 0XDC);
    // 0x802C769C: addiu       $t4, $zero, 0x8A
    ctx->r12 = ADD32(0, 0X8A);
    // 0x802C76A0: sw          $t4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r12;
    // 0x802C76A4: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C76A8: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C76AC: addiu       $a2, $zero, 0x7
    ctx->r6 = ADD32(0, 0X7);
    // 0x802C76B0: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    // 0x802C76B4: jal         0x801E3EE0
    // 0x802C76B8: addiu       $a3, $a3, 0x62
    ctx->r7 = ADD32(ctx->r7, 0X62);
    func_801E3EE0(rdram, ctx);
        goto after_6;
    // 0x802C76B8: addiu       $a3, $a3, 0x62
    ctx->r7 = ADD32(ctx->r7, 0X62);
    after_6:
    // 0x802C76BC: lw          $t7, 0x54($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X54);
    // 0x802C76C0: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
    // 0x802C76C4: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x802C76C8: lw          $t5, 0x0($t7)
    ctx->r13 = MEM_W(ctx->r15, 0X0);
    // 0x802C76CC: lw          $t6, 0xE8($sp)
    ctx->r14 = MEM_W(ctx->r29, 0XE8);
    // 0x802C76D0: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x802C76D4: bne         $t5, $at, L_802C76E0
    if (ctx->r13 != ctx->r1) {
        // 0x802C76D8: addiu       $a1, $zero, 0x4
        ctx->r5 = ADD32(0, 0X4);
            goto L_802C76E0;
    }
    // 0x802C76D8: addiu       $a1, $zero, 0x4
    ctx->r5 = ADD32(0, 0X4);
    // 0x802C76DC: bne         $t6, $zero, L_802C76FC
    if (ctx->r14 != 0) {
        // 0x802C76E0: addiu       $t8, $zero, 0x9C
        ctx->r24 = ADD32(0, 0X9C);
            goto L_802C76FC;
    }
L_802C76E0:
    // 0x802C76E0: addiu       $t8, $zero, 0x9C
    ctx->r24 = ADD32(0, 0X9C);
    // 0x802C76E4: sw          $t8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r24;
    // 0x802C76E8: addiu       $a2, $zero, 0xB
    ctx->r6 = ADD32(0, 0XB);
    // 0x802C76EC: lw          $a3, 0x5C($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X5C);
    // 0x802C76F0: jal         0x801E3EE0
    // 0x802C76F4: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    func_801E3EE0(rdram, ctx);
        goto after_7;
    // 0x802C76F4: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    after_7:
    // 0x802C76F8: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
L_802C76FC:
    // 0x802C76FC: addiu       $t9, $zero, 0xA7
    ctx->r25 = ADD32(0, 0XA7);
    // 0x802C7700: sw          $t9, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r25;
    // 0x802C7704: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x802C7708: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C770C: addiu       $a2, $zero, 0x9
    ctx->r6 = ADD32(0, 0X9);
    // 0x802C7710: lw          $a3, 0x5C($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X5C);
    // 0x802C7714: jal         0x801E3EE0
    // 0x802C7718: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    func_801E3EE0(rdram, ctx);
        goto after_8;
    // 0x802C7718: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    after_8:
    // 0x802C771C: lw          $a3, 0xDC($sp)
    ctx->r7 = MEM_W(ctx->r29, 0XDC);
    // 0x802C7720: addiu       $t4, $zero, 0xA7
    ctx->r12 = ADD32(0, 0XA7);
    // 0x802C7724: sw          $t4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r12;
    // 0x802C7728: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C772C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C7730: addiu       $a2, $zero, 0xA
    ctx->r6 = ADD32(0, 0XA);
    // 0x802C7734: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    // 0x802C7738: jal         0x801E3EE0
    // 0x802C773C: addiu       $a3, $a3, 0x59
    ctx->r7 = ADD32(ctx->r7, 0X59);
    func_801E3EE0(rdram, ctx);
        goto after_9;
    // 0x802C773C: addiu       $a3, $a3, 0x59
    ctx->r7 = ADD32(ctx->r7, 0X59);
    after_9:
    // 0x802C7740: lw          $t7, 0x54($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X54);
    // 0x802C7744: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
    // 0x802C7748: addiu       $at, $zero, 0x4
    ctx->r1 = ADD32(0, 0X4);
    // 0x802C774C: lw          $t5, 0x0($t7)
    ctx->r13 = MEM_W(ctx->r15, 0X0);
    // 0x802C7750: lw          $t6, 0xE8($sp)
    ctx->r14 = MEM_W(ctx->r29, 0XE8);
    // 0x802C7754: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x802C7758: bne         $t5, $at, L_802C7764
    if (ctx->r13 != ctx->r1) {
        // 0x802C775C: addiu       $a1, $zero, 0x4
        ctx->r5 = ADD32(0, 0X4);
            goto L_802C7764;
    }
    // 0x802C775C: addiu       $a1, $zero, 0x4
    ctx->r5 = ADD32(0, 0X4);
    // 0x802C7760: bne         $t6, $zero, L_802C7780
    if (ctx->r14 != 0) {
        // 0x802C7764: addiu       $t8, $zero, 0xB9
        ctx->r24 = ADD32(0, 0XB9);
            goto L_802C7780;
    }
L_802C7764:
    // 0x802C7764: addiu       $t8, $zero, 0xB9
    ctx->r24 = ADD32(0, 0XB9);
    // 0x802C7768: sw          $t8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r24;
    // 0x802C776C: addiu       $a2, $zero, 0xA
    ctx->r6 = ADD32(0, 0XA);
    // 0x802C7770: lw          $a3, 0x5C($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X5C);
    // 0x802C7774: jal         0x801E3EE0
    // 0x802C7778: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    func_801E3EE0(rdram, ctx);
        goto after_10;
    // 0x802C7778: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    after_10:
    // 0x802C777C: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
L_802C7780:
    // 0x802C7780: addiu       $t9, $zero, 0xC4
    ctx->r25 = ADD32(0, 0XC4);
    // 0x802C7784: sw          $t9, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r25;
    // 0x802C7788: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x802C778C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C7790: addiu       $a2, $zero, 0xC
    ctx->r6 = ADD32(0, 0XC);
    // 0x802C7794: lw          $a3, 0x5C($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X5C);
    // 0x802C7798: jal         0x801E3EE0
    // 0x802C779C: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    func_801E3EE0(rdram, ctx);
        goto after_11;
    // 0x802C779C: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    after_11:
    // 0x802C77A0: lw          $a3, 0xDC($sp)
    ctx->r7 = MEM_W(ctx->r29, 0XDC);
    // 0x802C77A4: addiu       $t4, $zero, 0xC4
    ctx->r12 = ADD32(0, 0XC4);
    // 0x802C77A8: sw          $t4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r12;
    // 0x802C77AC: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C77B0: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C77B4: addiu       $a2, $zero, 0xB
    ctx->r6 = ADD32(0, 0XB);
    // 0x802C77B8: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    // 0x802C77BC: jal         0x801E3EE0
    // 0x802C77C0: addiu       $a3, $a3, 0x67
    ctx->r7 = ADD32(ctx->r7, 0X67);
    func_801E3EE0(rdram, ctx);
        goto after_12;
    // 0x802C77C0: addiu       $a3, $a3, 0x67
    ctx->r7 = ADD32(ctx->r7, 0X67);
    after_12:
    // 0x802C77C4: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
    // 0x802C77C8: lw          $t7, 0xEC($sp)
    ctx->r15 = MEM_W(ctx->r29, 0XEC);
L_802C77CC:
    // 0x802C77CC: lui         $t6, 0x800E
    ctx->r14 = S32(0X800E << 16);
    // 0x802C77D0: addiu       $t6, $t6, -0x5640
    ctx->r14 = ADD32(ctx->r14, -0X5640);
    // 0x802C77D4: beq         $t7, $zero, L_802C7878
    if (ctx->r15 == 0) {
        // 0x802C77D8: lw          $t5, 0x4C($sp)
        ctx->r13 = MEM_W(ctx->r29, 0X4C);
            goto L_802C7878;
    }
    // 0x802C77D8: lw          $t5, 0x4C($sp)
    ctx->r13 = MEM_W(ctx->r29, 0X4C);
    // 0x802C77DC: bne         $t5, $t6, L_802C7830
    if (ctx->r13 != ctx->r14) {
        // 0x802C77E0: or          $a0, $s0, $zero
        ctx->r4 = ctx->r16 | 0;
            goto L_802C7830;
    }
    // 0x802C77E0: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x802C77E4: lw          $t8, 0x0($t5)
    ctx->r24 = MEM_W(ctx->r13, 0X0);
    // 0x802C77E8: lui         $t4, 0x802D
    ctx->r12 = S32(0X802D << 16);
    // 0x802C77EC: lui         $t6, 0x801D
    ctx->r14 = S32(0X801D << 16);
    // 0x802C77F0: sll         $t9, $t8, 2
    ctx->r25 = S32(ctx->r24 << 2);
    // 0x802C77F4: addu        $t4, $t4, $t9
    ctx->r12 = ADD32(ctx->r12, ctx->r25);
    // 0x802C77F8: lw          $t4, -0x7428($t4)
    ctx->r12 = MEM_W(ctx->r12, -0X7428);
    // 0x802C77FC: addiu       $t6, $t6, -0x4D68
    ctx->r14 = ADD32(ctx->r14, -0X4D68);
    // 0x802C7800: addiu       $t5, $zero, 0xCB
    ctx->r13 = ADD32(0, 0XCB);
    // 0x802C7804: sll         $t7, $t4, 3
    ctx->r15 = S32(ctx->r12 << 3);
    // 0x802C7808: subu        $t7, $t7, $t4
    ctx->r15 = SUB32(ctx->r15, ctx->r12);
    // 0x802C780C: sll         $t7, $t7, 1
    ctx->r15 = S32(ctx->r15 << 1);
    // 0x802C7810: addu        $a2, $t7, $t6
    ctx->r6 = ADD32(ctx->r15, ctx->r14);
    // 0x802C7814: sw          $t5, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r13;
    // 0x802C7818: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x802C781C: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    { extern void wr64_watercraft_preview_name(uint8_t*, recomp_context*); wr64_watercraft_preview_name(rdram, ctx); }
    // 0x802C7820: jal         0x801E9858
    // 0x802C7824: lw          $a3, 0xD8($sp)
    ctx->r7 = MEM_W(ctx->r29, 0XD8);
    func_801E9858(rdram, ctx);
        goto after_13;
    // 0x802C7824: lw          $a3, 0xD8($sp)
    ctx->r7 = MEM_W(ctx->r29, 0XD8);
    after_13:
    // 0x802C7828: b           L_802C7878
    // 0x802C782C: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
        goto L_802C7878;
    // 0x802C782C: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
L_802C7830:
    // 0x802C7830: lw          $t8, 0x4C($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X4C);
    // 0x802C7834: lui         $t7, 0x802D
    ctx->r15 = S32(0X802D << 16);
    // 0x802C7838: lui         $t5, 0x800E
    ctx->r13 = S32(0X800E << 16);
    // 0x802C783C: lw          $t9, 0x0($t8)
    ctx->r25 = MEM_W(ctx->r24, 0X0);
    // 0x802C7840: addiu       $t8, $zero, 0xCB
    ctx->r24 = ADD32(0, 0XCB);
    // 0x802C7844: addiu       $t5, $t5, -0x56B0
    ctx->r13 = ADD32(ctx->r13, -0X56B0);
    // 0x802C7848: sll         $t4, $t9, 2
    ctx->r12 = S32(ctx->r25 << 2);
    // 0x802C784C: addu        $t7, $t7, $t4
    ctx->r15 = ADD32(ctx->r15, ctx->r12);
    // 0x802C7850: lw          $t7, -0x7428($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X7428);
    // 0x802C7854: sw          $t8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r24;
    // 0x802C7858: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C785C: sll         $t6, $t7, 3
    ctx->r14 = S32(ctx->r15 << 3);
    // 0x802C7860: subu        $t6, $t6, $t7
    ctx->r14 = SUB32(ctx->r14, ctx->r15);
    // 0x802C7864: sll         $t6, $t6, 1
    ctx->r14 = S32(ctx->r14 << 1);
    // 0x802C7868: addu        $a2, $t6, $t5
    ctx->r6 = ADD32(ctx->r14, ctx->r13);
    { extern void wr64_watercraft_preview_name(uint8_t*, recomp_context*); wr64_watercraft_preview_name(rdram, ctx); }
    // 0x802C786C: jal         0x801E9858
    // 0x802C7870: lw          $a3, 0xD8($sp)
    ctx->r7 = MEM_W(ctx->r29, 0XD8);
    func_801E9858(rdram, ctx);
        goto after_14;
    // 0x802C7870: lw          $a3, 0xD8($sp)
    ctx->r7 = MEM_W(ctx->r29, 0XD8);
    after_14:
    // 0x802C7874: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
L_802C7878:
    // 0x802C7878: lw          $t9, 0xF0($sp)
    ctx->r25 = MEM_W(ctx->r29, 0XF0);
    // 0x802C787C: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x802C7880: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C7884: beq         $t9, $zero, L_802C792C
    if (ctx->r25 == 0) {
        // 0x802C7888: addiu       $a2, $zero, 0x25
        ctx->r6 = ADD32(0, 0X25);
            goto L_802C792C;
    }
    // 0x802C7888: addiu       $a2, $zero, 0x25
    ctx->r6 = ADD32(0, 0X25);
    // 0x802C788C: lw          $a3, 0xDC($sp)
    ctx->r7 = MEM_W(ctx->r29, 0XDC);
    // 0x802C7890: addiu       $t4, $zero, 0x62
    ctx->r12 = ADD32(0, 0X62);
    // 0x802C7894: sw          $t4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r12;
    // 0x802C7898: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    // 0x802C789C: jal         0x801E3EE0
    // 0x802C78A0: addiu       $a3, $a3, 0xC
    ctx->r7 = ADD32(ctx->r7, 0XC);
    func_801E3EE0(rdram, ctx);
        goto after_15;
    // 0x802C78A0: addiu       $a3, $a3, 0xC
    ctx->r7 = ADD32(ctx->r7, 0XC);
    after_15:
    // 0x802C78A4: lw          $t7, 0x58($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X58);
    // 0x802C78A8: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
    // 0x802C78AC: lw          $t6, 0xE4($sp)
    ctx->r14 = MEM_W(ctx->r29, 0XE4);
    // 0x802C78B0: lw          $v1, 0x0($t7)
    ctx->r3 = MEM_W(ctx->r15, 0X0);
    // 0x802C78B4: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x802C78B8: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C78BC: bne         $v1, $zero, L_802C78CC
    if (ctx->r3 != 0) {
        // 0x802C78C0: addiu       $a2, $zero, 0x3
        ctx->r6 = ADD32(0, 0X3);
            goto L_802C78CC;
    }
    // 0x802C78C0: addiu       $a2, $zero, 0x3
    ctx->r6 = ADD32(0, 0X3);
    // 0x802C78C4: bnel        $t6, $zero, L_802C78F4
    if (ctx->r14 != 0) {
        // 0x802C78C8: addiu       $at, $zero, 0x1
        ctx->r1 = ADD32(0, 0X1);
            goto L_802C78F4;
    }
    goto skip_2;
    // 0x802C78C8: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    skip_2:
L_802C78CC:
    // 0x802C78CC: lw          $a3, 0xDC($sp)
    ctx->r7 = MEM_W(ctx->r29, 0XDC);
    // 0x802C78D0: addiu       $t5, $zero, 0x70
    ctx->r13 = ADD32(0, 0X70);
    // 0x802C78D4: sw          $t5, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r13;
    // 0x802C78D8: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    // 0x802C78DC: jal         0x801E3EE0
    // 0x802C78E0: addiu       $a3, $a3, 0x15
    ctx->r7 = ADD32(ctx->r7, 0X15);
    func_801E3EE0(rdram, ctx);
        goto after_16;
    // 0x802C78E0: addiu       $a3, $a3, 0x15
    ctx->r7 = ADD32(ctx->r7, 0X15);
    after_16:
    // 0x802C78E4: lw          $t8, 0x58($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X58);
    // 0x802C78E8: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
    // 0x802C78EC: lw          $v1, 0x0($t8)
    ctx->r3 = MEM_W(ctx->r24, 0X0);
    // 0x802C78F0: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
L_802C78F4:
    // 0x802C78F4: bne         $v1, $at, L_802C7904
    if (ctx->r3 != ctx->r1) {
        // 0x802C78F8: lw          $t9, 0xE4($sp)
        ctx->r25 = MEM_W(ctx->r29, 0XE4);
            goto L_802C7904;
    }
    // 0x802C78F8: lw          $t9, 0xE4($sp)
    ctx->r25 = MEM_W(ctx->r29, 0XE4);
    // 0x802C78FC: bnel        $t9, $zero, L_802C7930
    if (ctx->r25 != 0) {
        // 0x802C7900: lw          $t7, 0x54($sp)
        ctx->r15 = MEM_W(ctx->r29, 0X54);
            goto L_802C7930;
    }
    goto skip_3;
    // 0x802C7900: lw          $t7, 0x54($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X54);
    skip_3:
L_802C7904:
    // 0x802C7904: lw          $a3, 0xDC($sp)
    ctx->r7 = MEM_W(ctx->r29, 0XDC);
    // 0x802C7908: addiu       $t4, $zero, 0x70
    ctx->r12 = ADD32(0, 0X70);
    // 0x802C790C: sw          $t4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r12;
    // 0x802C7910: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x802C7914: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C7918: addiu       $a2, $zero, 0x26
    ctx->r6 = ADD32(0, 0X26);
    // 0x802C791C: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    // 0x802C7920: jal         0x801E3EE0
    // 0x802C7924: addiu       $a3, $a3, 0x54
    ctx->r7 = ADD32(ctx->r7, 0X54);
    func_801E3EE0(rdram, ctx);
        goto after_17;
    // 0x802C7924: addiu       $a3, $a3, 0x54
    ctx->r7 = ADD32(ctx->r7, 0X54);
    after_17:
    // 0x802C7928: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
L_802C792C:
    // 0x802C792C: lw          $t7, 0x54($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X54);
L_802C7930:
    // 0x802C7930: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x802C7934: addiu       $a2, $zero, 0x80
    ctx->r6 = ADD32(0, 0X80);
    // 0x802C7938: lw          $v1, 0x0($t7)
    ctx->r3 = MEM_W(ctx->r15, 0X0);
    // 0x802C793C: addiu       $a3, $zero, 0x80
    ctx->r7 = ADD32(0, 0X80);
    // 0x802C7940: addiu       $t6, $zero, 0x80
    ctx->r14 = ADD32(0, 0X80);
    // 0x802C7944: slti        $at, $v1, 0x5
    ctx->r1 = SIGNED(ctx->r3) < 0X5 ? 1 : 0;
    // 0x802C7948: bne         $at, $zero, L_802C7A88
    if (ctx->r1 != 0) {
        // 0x802C794C: addiu       $t5, $zero, 0xFF
        ctx->r13 = ADD32(0, 0XFF);
            goto L_802C7A88;
    }
    // 0x802C794C: addiu       $t5, $zero, 0xFF
    ctx->r13 = ADD32(0, 0XFF);
    // 0x802C7950: addiu       $at, $zero, 0x5
    ctx->r1 = ADD32(0, 0X5);
    // 0x802C7954: bne         $v1, $at, L_802C7964
    if (ctx->r3 != ctx->r1) {
        // 0x802C7958: addiu       $t8, $zero, 0xFF
        ctx->r24 = ADD32(0, 0XFF);
            goto L_802C7964;
    }
    // 0x802C7958: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C795C: b           L_802C7968
    // 0x802C7960: addiu       $a1, $zero, 0x6
    ctx->r5 = ADD32(0, 0X6);
        goto L_802C7968;
    // 0x802C7960: addiu       $a1, $zero, 0x6
    ctx->r5 = ADD32(0, 0X6);
L_802C7964:
    // 0x802C7964: addiu       $a1, $zero, 0x7
    ctx->r5 = ADD32(0, 0X7);
L_802C7968:
    // 0x802C7968: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x802C796C: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C7970: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C7974: addiu       $t4, $zero, 0xFF
    ctx->r12 = ADD32(0, 0XFF);
    // 0x802C7978: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C797C: sw          $t7, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r15;
    // 0x802C7980: sw          $t4, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r12;
    // 0x802C7984: sw          $t9, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r25;
    // 0x802C7988: sw          $t9, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r25;
    // 0x802C798C: sw          $t6, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r14;
    // 0x802C7990: sw          $t5, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r13;
    // 0x802C7994: sw          $t8, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r24;
    // 0x802C7998: sw          $t5, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r13;
    // 0x802C799C: jal         0x801E946C
    // 0x802C79A0: sw          $t8, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r24;
    func_801E946C(rdram, ctx);
        goto after_18;
    // 0x802C79A0: sw          $t8, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r24;
    after_18:
    // 0x802C79A4: lui         $t7, 0x80C
    ctx->r15 = S32(0X80C << 16);
    // 0x802C79A8: addiu       $t7, $t7, -0x4058
    ctx->r15 = ADD32(ctx->r15, -0X4058);
    // 0x802C79AC: lui         $t4, 0xFD68
    ctx->r12 = S32(0XFD68 << 16);
    // 0x802C79B0: lui         $t6, 0x708
    ctx->r14 = S32(0X708 << 16);
    // 0x802C79B4: lui         $t5, 0xE600
    ctx->r13 = S32(0XE600 << 16);
    // 0x802C79B8: lui         $v1, 0xF568
    ctx->r3 = S32(0XF568 << 16);
    // 0x802C79BC: sw          $t5, 0x10($v0)
    MEM_W(0X10, ctx->r2) = ctx->r13;
    // 0x802C79C0: ori         $t6, $t6, 0x200
    ctx->r14 = ctx->r14 | 0X200;
    // 0x802C79C4: ori         $t4, $t4, 0x57
    ctx->r12 = ctx->r12 | 0X57;
    // 0x802C79C8: sw          $t7, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r15;
    // 0x802C79CC: ori         $v1, $v1, 0x1600
    ctx->r3 = ctx->r3 | 0X1600;
    // 0x802C79D0: lui         $t7, 0x8
    ctx->r15 = S32(0X8 << 16);
    // 0x802C79D4: sw          $t4, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r12;
    // 0x802C79D8: sw          $t6, 0xC($v0)
    MEM_W(0XC, ctx->r2) = ctx->r14;
    // 0x802C79DC: lui         $t5, 0x15
    ctx->r13 = S32(0X15 << 16);
    // 0x802C79E0: lui         $t9, 0x715
    ctx->r25 = S32(0X715 << 16);
    // 0x802C79E4: ori         $t9, $t9, 0xC024
    ctx->r25 = ctx->r25 | 0XC024;
    // 0x802C79E8: ori         $t5, $t5, 0xC024
    ctx->r13 = ctx->r13 | 0XC024;
    // 0x802C79EC: lui         $t6, 0xF200
    ctx->r14 = S32(0XF200 << 16);
    // 0x802C79F0: lui         $t4, 0xE700
    ctx->r12 = S32(0XE700 << 16);
    // 0x802C79F4: ori         $t7, $t7, 0x200
    ctx->r15 = ctx->r15 | 0X200;
    // 0x802C79F8: lui         $t8, 0xF400
    ctx->r24 = S32(0XF400 << 16);
    // 0x802C79FC: sw          $t8, 0x18($v0)
    MEM_W(0X18, ctx->r2) = ctx->r24;
    // 0x802C7A00: sw          $t7, 0x2C($v0)
    MEM_W(0X2C, ctx->r2) = ctx->r15;
    // 0x802C7A04: sw          $t4, 0x20($v0)
    MEM_W(0X20, ctx->r2) = ctx->r12;
    // 0x802C7A08: sw          $t6, 0x30($v0)
    MEM_W(0X30, ctx->r2) = ctx->r14;
    // 0x802C7A0C: sw          $t5, 0x34($v0)
    MEM_W(0X34, ctx->r2) = ctx->r13;
    // 0x802C7A10: sw          $t9, 0x1C($v0)
    MEM_W(0X1C, ctx->r2) = ctx->r25;
    // 0x802C7A14: sw          $v1, 0x8($v0)
    MEM_W(0X8, ctx->r2) = ctx->r3;
    // 0x802C7A18: sw          $v1, 0x28($v0)
    MEM_W(0X28, ctx->r2) = ctx->r3;
    // 0x802C7A1C: sw          $zero, 0x14($v0)
    MEM_W(0X14, ctx->r2) = 0;
    // 0x802C7A20: sw          $zero, 0x24($v0)
    MEM_W(0X24, ctx->r2) = 0;
    // 0x802C7A24: lw          $t8, 0xDC($sp)
    ctx->r24 = MEM_W(ctx->r29, 0XDC);
    // 0x802C7A28: lui         $at, 0xE400
    ctx->r1 = S32(0XE400 << 16);
    // 0x802C7A2C: addiu       $s0, $v0, 0x50
    ctx->r16 = ADD32(ctx->r2, 0X50);
    // 0x802C7A30: addiu       $t9, $t8, 0x75
    ctx->r25 = ADD32(ctx->r24, 0X75);
    // 0x802C7A34: sll         $t4, $t9, 2
    ctx->r12 = S32(ctx->r25 << 2);
    // 0x802C7A38: andi        $t7, $t4, 0xFFF
    ctx->r15 = ctx->r12 & 0XFFF;
    // 0x802C7A3C: sll         $t6, $t7, 12
    ctx->r14 = S32(ctx->r15 << 12);
    // 0x802C7A40: or          $t5, $t6, $at
    ctx->r13 = ctx->r14 | ctx->r1;
    // 0x802C7A44: ori         $t8, $t5, 0x2B0
    ctx->r24 = ctx->r13 | 0X2B0;
    // 0x802C7A48: sw          $t8, 0x38($v0)
    MEM_W(0X38, ctx->r2) = ctx->r24;
    // 0x802C7A4C: lw          $t9, 0xDC($sp)
    ctx->r25 = MEM_W(ctx->r29, 0XDC);
    // 0x802C7A50: sw          $zero, 0x44($v0)
    MEM_W(0X44, ctx->r2) = 0;
    // 0x802C7A54: addiu       $t4, $t9, 0x1D
    ctx->r12 = ADD32(ctx->r25, 0X1D);
    // 0x802C7A58: sll         $t7, $t4, 2
    ctx->r15 = S32(ctx->r12 << 2);
    // 0x802C7A5C: andi        $t6, $t7, 0xFFF
    ctx->r14 = ctx->r15 & 0XFFF;
    // 0x802C7A60: sll         $t5, $t6, 12
    ctx->r13 = S32(ctx->r14 << 12);
    // 0x802C7A64: lui         $t7, 0x400
    ctx->r15 = S32(0X400 << 16);
    // 0x802C7A68: ori         $t7, $t7, 0x400
    ctx->r15 = ctx->r15 | 0X400;
    // 0x802C7A6C: ori         $t8, $t5, 0x288
    ctx->r24 = ctx->r13 | 0X288;
    // 0x802C7A70: lui         $t4, 0xB200
    ctx->r12 = S32(0XB200 << 16);
    // 0x802C7A74: lui         $t9, 0xB300
    ctx->r25 = S32(0XB300 << 16);
    // 0x802C7A78: sw          $t9, 0x40($v0)
    MEM_W(0X40, ctx->r2) = ctx->r25;
    // 0x802C7A7C: sw          $t4, 0x48($v0)
    MEM_W(0X48, ctx->r2) = ctx->r12;
    // 0x802C7A80: sw          $t8, 0x3C($v0)
    MEM_W(0X3C, ctx->r2) = ctx->r24;
    // 0x802C7A84: sw          $t7, 0x4C($v0)
    MEM_W(0X4C, ctx->r2) = ctx->r15;
L_802C7A88:
    // 0x802C7A88: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C7A8C: addiu       $t5, $zero, 0xFF
    ctx->r13 = ADD32(0, 0XFF);
    // 0x802C7A90: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C7A94: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C7A98: addiu       $t4, $zero, 0xFF
    ctx->r12 = ADD32(0, 0XFF);
    // 0x802C7A9C: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C7AA0: sw          $t7, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r15;
    // 0x802C7AA4: sw          $t4, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r12;
    // 0x802C7AA8: sw          $t9, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r25;
    // 0x802C7AAC: sw          $t9, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r25;
    // 0x802C7AB0: sw          $t8, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r24;
    // 0x802C7AB4: sw          $t8, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r24;
    // 0x802C7AB8: sw          $t5, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r13;
    // 0x802C7ABC: sw          $t5, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r13;
    // 0x802C7AC0: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x802C7AC4: sw          $t6, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r14;
    // 0x802C7AC8: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x802C7ACC: addiu       $a1, $zero, 0x6
    ctx->r5 = ADD32(0, 0X6);
    // 0x802C7AD0: addiu       $a2, $zero, 0xFF
    ctx->r6 = ADD32(0, 0XFF);
    // 0x802C7AD4: jal         0x801E946C
    // 0x802C7AD8: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    func_801E946C(rdram, ctx);
        goto after_19;
    // 0x802C7AD8: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    after_19:
    // 0x802C7ADC: lw          $t4, 0xF4($sp)
    ctx->r12 = MEM_W(ctx->r29, 0XF4);
    // 0x802C7AE0: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
    // 0x802C7AE4: lw          $t7, 0x54($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X54);
    // 0x802C7AE8: beql        $t4, $zero, L_802C7BB4
    if (ctx->r12 == 0) {
        // 0x802C7AEC: lw          $t8, 0xF0($sp)
        ctx->r24 = MEM_W(ctx->r29, 0XF0);
            goto L_802C7BB4;
    }
    goto skip_4;
    // 0x802C7AEC: lw          $t8, 0xF0($sp)
    ctx->r24 = MEM_W(ctx->r29, 0XF0);
    skip_4:
    // 0x802C7AF0: lw          $v1, 0x0($t7)
    ctx->r3 = MEM_W(ctx->r15, 0X0);
    // 0x802C7AF4: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x802C7AF8: lw          $t6, 0xE8($sp)
    ctx->r14 = MEM_W(ctx->r29, 0XE8);
    // 0x802C7AFC: bnel        $v1, $at, L_802C7B3C
    if (ctx->r3 != ctx->r1) {
        // 0x802C7B00: addiu       $at, $zero, 0x3
        ctx->r1 = ADD32(0, 0X3);
            goto L_802C7B3C;
    }
    goto skip_5;
    // 0x802C7B00: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    skip_5:
    // 0x802C7B04: beq         $t6, $zero, L_802C7B38
    if (ctx->r14 == 0) {
        // 0x802C7B08: or          $a0, $v0, $zero
        ctx->r4 = ctx->r2 | 0;
            goto L_802C7B38;
    }
    // 0x802C7B08: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C7B0C: lw          $a3, 0xDC($sp)
    ctx->r7 = MEM_W(ctx->r29, 0XDC);
    // 0x802C7B10: addiu       $t5, $zero, 0x80
    ctx->r13 = ADD32(0, 0X80);
    // 0x802C7B14: sw          $t5, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r13;
    // 0x802C7B18: addiu       $a1, $zero, 0x4
    ctx->r5 = ADD32(0, 0X4);
    // 0x802C7B1C: addiu       $a2, $zero, 0x9
    ctx->r6 = ADD32(0, 0X9);
    // 0x802C7B20: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    // 0x802C7B24: jal         0x801E3EE0
    // 0x802C7B28: addiu       $a3, $a3, 0xD
    ctx->r7 = ADD32(ctx->r7, 0XD);
    func_801E3EE0(rdram, ctx);
        goto after_20;
    // 0x802C7B28: addiu       $a3, $a3, 0xD
    ctx->r7 = ADD32(ctx->r7, 0XD);
    after_20:
    // 0x802C7B2C: lw          $t8, 0x54($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X54);
    // 0x802C7B30: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
    // 0x802C7B34: lw          $v1, 0x0($t8)
    ctx->r3 = MEM_W(ctx->r24, 0X0);
L_802C7B38:
    // 0x802C7B38: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
L_802C7B3C:
    // 0x802C7B3C: bne         $v1, $at, L_802C7B78
    if (ctx->r3 != ctx->r1) {
        // 0x802C7B40: lw          $t9, 0xE8($sp)
        ctx->r25 = MEM_W(ctx->r29, 0XE8);
            goto L_802C7B78;
    }
    // 0x802C7B40: lw          $t9, 0xE8($sp)
    ctx->r25 = MEM_W(ctx->r29, 0XE8);
    // 0x802C7B44: beq         $t9, $zero, L_802C7B78
    if (ctx->r25 == 0) {
        // 0x802C7B48: or          $a0, $s0, $zero
        ctx->r4 = ctx->r16 | 0;
            goto L_802C7B78;
    }
    // 0x802C7B48: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x802C7B4C: lw          $a3, 0xDC($sp)
    ctx->r7 = MEM_W(ctx->r29, 0XDC);
    // 0x802C7B50: addiu       $t4, $zero, 0x9C
    ctx->r12 = ADD32(0, 0X9C);
    // 0x802C7B54: sw          $t4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r12;
    // 0x802C7B58: addiu       $a1, $zero, 0x4
    ctx->r5 = ADD32(0, 0X4);
    // 0x802C7B5C: addiu       $a2, $zero, 0xB
    ctx->r6 = ADD32(0, 0XB);
    // 0x802C7B60: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    // 0x802C7B64: jal         0x801E3EE0
    // 0x802C7B68: addiu       $a3, $a3, 0xD
    ctx->r7 = ADD32(ctx->r7, 0XD);
    func_801E3EE0(rdram, ctx);
        goto after_21;
    // 0x802C7B68: addiu       $a3, $a3, 0xD
    ctx->r7 = ADD32(ctx->r7, 0XD);
    after_21:
    // 0x802C7B6C: lw          $t7, 0x54($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X54);
    // 0x802C7B70: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
    // 0x802C7B74: lw          $v1, 0x0($t7)
    ctx->r3 = MEM_W(ctx->r15, 0X0);
L_802C7B78:
    // 0x802C7B78: addiu       $at, $zero, 0x4
    ctx->r1 = ADD32(0, 0X4);
    // 0x802C7B7C: bne         $v1, $at, L_802C7BB0
    if (ctx->r3 != ctx->r1) {
        // 0x802C7B80: lw          $t6, 0xE8($sp)
        ctx->r14 = MEM_W(ctx->r29, 0XE8);
            goto L_802C7BB0;
    }
    // 0x802C7B80: lw          $t6, 0xE8($sp)
    ctx->r14 = MEM_W(ctx->r29, 0XE8);
    // 0x802C7B84: beq         $t6, $zero, L_802C7BB0
    if (ctx->r14 == 0) {
        // 0x802C7B88: or          $a0, $s0, $zero
        ctx->r4 = ctx->r16 | 0;
            goto L_802C7BB0;
    }
    // 0x802C7B88: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x802C7B8C: lw          $a3, 0xDC($sp)
    ctx->r7 = MEM_W(ctx->r29, 0XDC);
    // 0x802C7B90: addiu       $t5, $zero, 0xB9
    ctx->r13 = ADD32(0, 0XB9);
    // 0x802C7B94: sw          $t5, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r13;
    // 0x802C7B98: addiu       $a1, $zero, 0x4
    ctx->r5 = ADD32(0, 0X4);
    // 0x802C7B9C: addiu       $a2, $zero, 0xA
    ctx->r6 = ADD32(0, 0XA);
    // 0x802C7BA0: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    // 0x802C7BA4: jal         0x801E3EE0
    // 0x802C7BA8: addiu       $a3, $a3, 0xD
    ctx->r7 = ADD32(ctx->r7, 0XD);
    func_801E3EE0(rdram, ctx);
        goto after_22;
    // 0x802C7BA8: addiu       $a3, $a3, 0xD
    ctx->r7 = ADD32(ctx->r7, 0XD);
    after_22:
    // 0x802C7BAC: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
L_802C7BB0:
    // 0x802C7BB0: lw          $t8, 0xF0($sp)
    ctx->r24 = MEM_W(ctx->r29, 0XF0);
L_802C7BB4:
    // 0x802C7BB4: lw          $t9, 0x58($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X58);
    // 0x802C7BB8: beql        $t8, $zero, L_802C7C40
    if (ctx->r24 == 0) {
        // 0x802C7BBC: lw          $ra, 0x44($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X44);
            goto L_802C7C40;
    }
    goto skip_6;
    // 0x802C7BBC: lw          $ra, 0x44($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X44);
    skip_6:
    // 0x802C7BC0: lw          $v1, 0x0($t9)
    ctx->r3 = MEM_W(ctx->r25, 0X0);
    // 0x802C7BC4: lw          $t4, 0xE4($sp)
    ctx->r12 = MEM_W(ctx->r29, 0XE4);
    // 0x802C7BC8: bnel        $v1, $zero, L_802C7C08
    if (ctx->r3 != 0) {
        // 0x802C7BCC: addiu       $at, $zero, 0x1
        ctx->r1 = ADD32(0, 0X1);
            goto L_802C7C08;
    }
    goto skip_7;
    // 0x802C7BCC: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    skip_7:
    // 0x802C7BD0: beq         $t4, $zero, L_802C7C04
    if (ctx->r12 == 0) {
        // 0x802C7BD4: or          $a0, $s0, $zero
        ctx->r4 = ctx->r16 | 0;
            goto L_802C7C04;
    }
    // 0x802C7BD4: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x802C7BD8: lw          $a3, 0xDC($sp)
    ctx->r7 = MEM_W(ctx->r29, 0XDC);
    // 0x802C7BDC: addiu       $t7, $zero, 0x70
    ctx->r15 = ADD32(0, 0X70);
    // 0x802C7BE0: sw          $t7, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r15;
    // 0x802C7BE4: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C7BE8: addiu       $a2, $zero, 0x3
    ctx->r6 = ADD32(0, 0X3);
    // 0x802C7BEC: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    // 0x802C7BF0: jal         0x801E3EE0
    // 0x802C7BF4: addiu       $a3, $a3, 0x15
    ctx->r7 = ADD32(ctx->r7, 0X15);
    func_801E3EE0(rdram, ctx);
        goto after_23;
    // 0x802C7BF4: addiu       $a3, $a3, 0x15
    ctx->r7 = ADD32(ctx->r7, 0X15);
    after_23:
    // 0x802C7BF8: lw          $t6, 0x58($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X58);
    // 0x802C7BFC: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
    // 0x802C7C00: lw          $v1, 0x0($t6)
    ctx->r3 = MEM_W(ctx->r14, 0X0);
L_802C7C04:
    // 0x802C7C04: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
L_802C7C08:
    // 0x802C7C08: bne         $v1, $at, L_802C7C3C
    if (ctx->r3 != ctx->r1) {
        // 0x802C7C0C: lw          $t5, 0xE4($sp)
        ctx->r13 = MEM_W(ctx->r29, 0XE4);
            goto L_802C7C3C;
    }
    // 0x802C7C0C: lw          $t5, 0xE4($sp)
    ctx->r13 = MEM_W(ctx->r29, 0XE4);
    // 0x802C7C10: beq         $t5, $zero, L_802C7C3C
    if (ctx->r13 == 0) {
        // 0x802C7C14: or          $a0, $s0, $zero
        ctx->r4 = ctx->r16 | 0;
            goto L_802C7C3C;
    }
    // 0x802C7C14: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x802C7C18: lw          $a3, 0xDC($sp)
    ctx->r7 = MEM_W(ctx->r29, 0XDC);
    // 0x802C7C1C: addiu       $t8, $zero, 0x70
    ctx->r24 = ADD32(0, 0X70);
    // 0x802C7C20: sw          $t8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r24;
    // 0x802C7C24: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C7C28: addiu       $a2, $zero, 0x26
    ctx->r6 = ADD32(0, 0X26);
    // 0x802C7C2C: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    // 0x802C7C30: jal         0x801E3EE0
    // 0x802C7C34: addiu       $a3, $a3, 0x54
    ctx->r7 = ADD32(ctx->r7, 0X54);
    func_801E3EE0(rdram, ctx);
        goto after_24;
    // 0x802C7C34: addiu       $a3, $a3, 0x54
    ctx->r7 = ADD32(ctx->r7, 0X54);
    after_24:
    // 0x802C7C38: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
L_802C7C3C:
    // 0x802C7C3C: lw          $ra, 0x44($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X44);
L_802C7C40:
    // 0x802C7C40: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
    // 0x802C7C44: lw          $s0, 0x40($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X40);
    // 0x802C7C48: jr          $ra
    // 0x802C7C4C: addiu       $sp, $sp, 0xF8
    ctx->r29 = ADD32(ctx->r29, 0XF8);
    return;
    // 0x802C7C4C: addiu       $sp, $sp, 0xF8
    ctx->r29 = ADD32(ctx->r29, 0XF8);
;}
RECOMP_FUNC void func_i2_802C7C50(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C7C50: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x802C7C54: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x802C7C58: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x802C7C5C: lui         $t6, 0x80C
    ctx->r14 = S32(0X80C << 16);
    // 0x802C7C60: lui         $t0, 0x600
    ctx->r8 = S32(0X600 << 16);
    // 0x802C7C64: addiu       $t6, $t6, -0x1CA8
    ctx->r14 = ADD32(ctx->r14, -0X1CA8);
    // 0x802C7C68: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C7C6C: sw          $t6, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r14;
    // 0x802C7C70: sw          $t0, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r8;
    // 0x802C7C74: or          $v1, $a0, $zero
    ctx->r3 = ctx->r4 | 0;
    // 0x802C7C78: lui         $t7, 0x107
    ctx->r15 = S32(0X107 << 16);
    // 0x802C7C7C: addiu       $t7, $t7, -0x9D8
    ctx->r15 = ADD32(ctx->r15, -0X9D8);
    // 0x802C7C80: sw          $t7, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r15;
    // 0x802C7C84: sw          $t0, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r8;
    // 0x802C7C88: addiu       $t8, $zero, 0x170
    ctx->r24 = ADD32(0, 0X170);
    // 0x802C7C8C: addiu       $t9, $zero, 0x1E
    ctx->r25 = ADD32(0, 0X1E);
    // 0x802C7C90: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C7C94: sw          $t9, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r25;
    // 0x802C7C98: sw          $t8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r24;
    // 0x802C7C9C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C7CA0: addiu       $a2, $zero, 0x1C
    ctx->r6 = ADD32(0, 0X1C);
    // 0x802C7CA4: jal         0x80094338
    // 0x802C7CA8: addiu       $a3, $zero, 0x16
    ctx->r7 = ADD32(0, 0X16);
    func_80094338(rdram, ctx);
        goto after_0;
    // 0x802C7CA8: addiu       $a3, $zero, 0x16
    ctx->r7 = ADD32(0, 0X16);
    after_0:
    // 0x802C7CAC: lui         $t0, 0x802D
    ctx->r8 = S32(0X802D << 16);
    // 0x802C7CB0: addiu       $t0, $t0, -0x73A8
    ctx->r8 = ADD32(ctx->r8, -0X73A8);
    // 0x802C7CB4: lw          $t6, 0x0($t0)
    ctx->r14 = MEM_W(ctx->r8, 0X0);
    // 0x802C7CB8: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C7CBC: beq         $t6, $zero, L_802C7D34
    if (ctx->r14 == 0) {
        // 0x802C7CC0: addiu       $t7, $zero, 0x82
        ctx->r15 = ADD32(0, 0X82);
            goto L_802C7D34;
    }
    // 0x802C7CC0: addiu       $t7, $zero, 0x82
    ctx->r15 = ADD32(0, 0X82);
    // 0x802C7CC4: addiu       $t8, $zero, 0xD
    ctx->r24 = ADD32(0, 0XD);
    // 0x802C7CC8: sw          $t8, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r24;
    // 0x802C7CCC: sw          $t7, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r15;
    // 0x802C7CD0: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C7CD4: addiu       $a2, $zero, 0x1C
    ctx->r6 = ADD32(0, 0X1C);
    // 0x802C7CD8: jal         0x80094338
    // 0x802C7CDC: addiu       $a3, $zero, 0x60
    ctx->r7 = ADD32(0, 0X60);
    func_80094338(rdram, ctx);
        goto after_1;
    // 0x802C7CDC: addiu       $a3, $zero, 0x60
    ctx->r7 = ADD32(0, 0X60);
    after_1:
    // 0x802C7CE0: addiu       $t9, $zero, 0x3B
    ctx->r25 = ADD32(0, 0X3B);
    // 0x802C7CE4: addiu       $t6, $zero, 0xD
    ctx->r14 = ADD32(0, 0XD);
    // 0x802C7CE8: sw          $t6, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r14;
    // 0x802C7CEC: sw          $t9, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r25;
    // 0x802C7CF0: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C7CF4: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C7CF8: addiu       $a2, $zero, 0x20
    ctx->r6 = ADD32(0, 0X20);
    // 0x802C7CFC: jal         0x80094338
    // 0x802C7D00: addiu       $a3, $zero, 0x6E
    ctx->r7 = ADD32(0, 0X6E);
    func_80094338(rdram, ctx);
        goto after_2;
    // 0x802C7D00: addiu       $a3, $zero, 0x6E
    ctx->r7 = ADD32(0, 0X6E);
    after_2:
    // 0x802C7D04: addiu       $t7, $zero, 0x3B
    ctx->r15 = ADD32(0, 0X3B);
    // 0x802C7D08: addiu       $t8, $zero, 0xD
    ctx->r24 = ADD32(0, 0XD);
    // 0x802C7D0C: sw          $t8, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r24;
    // 0x802C7D10: sw          $t7, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r15;
    // 0x802C7D14: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C7D18: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C7D1C: addiu       $a2, $zero, 0x5F
    ctx->r6 = ADD32(0, 0X5F);
    // 0x802C7D20: jal         0x80094338
    // 0x802C7D24: addiu       $a3, $zero, 0x6E
    ctx->r7 = ADD32(0, 0X6E);
    func_80094338(rdram, ctx);
        goto after_3;
    // 0x802C7D24: addiu       $a3, $zero, 0x6E
    ctx->r7 = ADD32(0, 0X6E);
    after_3:
    // 0x802C7D28: lui         $t0, 0x802D
    ctx->r8 = S32(0X802D << 16);
    // 0x802C7D2C: addiu       $t0, $t0, -0x73A8
    ctx->r8 = ADD32(ctx->r8, -0X73A8);
    // 0x802C7D30: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
L_802C7D34:
    // 0x802C7D34: lw          $t9, 0x4($t0)
    ctx->r25 = MEM_W(ctx->r8, 0X4);
    // 0x802C7D38: beq         $t9, $zero, L_802C7DB0
    if (ctx->r25 == 0) {
        // 0x802C7D3C: addiu       $t6, $zero, 0x82
        ctx->r14 = ADD32(0, 0X82);
            goto L_802C7DB0;
    }
    // 0x802C7D3C: addiu       $t6, $zero, 0x82
    ctx->r14 = ADD32(0, 0X82);
    // 0x802C7D40: addiu       $t7, $zero, 0xD
    ctx->r15 = ADD32(0, 0XD);
    // 0x802C7D44: sw          $t7, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r15;
    // 0x802C7D48: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x802C7D4C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C7D50: addiu       $a2, $zero, 0x109
    ctx->r6 = ADD32(0, 0X109);
    // 0x802C7D54: jal         0x80094338
    // 0x802C7D58: addiu       $a3, $zero, 0x60
    ctx->r7 = ADD32(0, 0X60);
    func_80094338(rdram, ctx);
        goto after_4;
    // 0x802C7D58: addiu       $a3, $zero, 0x60
    ctx->r7 = ADD32(0, 0X60);
    after_4:
    // 0x802C7D5C: addiu       $t8, $zero, 0x3B
    ctx->r24 = ADD32(0, 0X3B);
    // 0x802C7D60: addiu       $t9, $zero, 0xD
    ctx->r25 = ADD32(0, 0XD);
    // 0x802C7D64: sw          $t9, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r25;
    // 0x802C7D68: sw          $t8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r24;
    // 0x802C7D6C: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C7D70: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C7D74: addiu       $a2, $zero, 0x10D
    ctx->r6 = ADD32(0, 0X10D);
    // 0x802C7D78: jal         0x80094338
    // 0x802C7D7C: addiu       $a3, $zero, 0x6E
    ctx->r7 = ADD32(0, 0X6E);
    func_80094338(rdram, ctx);
        goto after_5;
    // 0x802C7D7C: addiu       $a3, $zero, 0x6E
    ctx->r7 = ADD32(0, 0X6E);
    after_5:
    // 0x802C7D80: addiu       $t6, $zero, 0x3B
    ctx->r14 = ADD32(0, 0X3B);
    // 0x802C7D84: addiu       $t7, $zero, 0xD
    ctx->r15 = ADD32(0, 0XD);
    // 0x802C7D88: sw          $t7, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r15;
    // 0x802C7D8C: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x802C7D90: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C7D94: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C7D98: addiu       $a2, $zero, 0x14C
    ctx->r6 = ADD32(0, 0X14C);
    // 0x802C7D9C: jal         0x80094338
    // 0x802C7DA0: addiu       $a3, $zero, 0x6E
    ctx->r7 = ADD32(0, 0X6E);
    func_80094338(rdram, ctx);
        goto after_6;
    // 0x802C7DA0: addiu       $a3, $zero, 0x6E
    ctx->r7 = ADD32(0, 0X6E);
    after_6:
    // 0x802C7DA4: lui         $t0, 0x802D
    ctx->r8 = S32(0X802D << 16);
    // 0x802C7DA8: addiu       $t0, $t0, -0x73A8
    ctx->r8 = ADD32(ctx->r8, -0X73A8);
    // 0x802C7DAC: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
L_802C7DB0:
    // 0x802C7DB0: lw          $t8, 0x0($t0)
    ctx->r24 = MEM_W(ctx->r8, 0X0);
    // 0x802C7DB4: beq         $t8, $zero, L_802C7DD0
    if (ctx->r24 == 0) {
        // 0x802C7DB8: addiu       $a1, $zero, 0x13
        ctx->r5 = ADD32(0, 0X13);
            goto L_802C7DD0;
    }
    // 0x802C7DB8: addiu       $a1, $zero, 0x13
    ctx->r5 = ADD32(0, 0X13);
    // 0x802C7DBC: jal         0x802C86E4
    // 0x802C7DC0: addiu       $a2, $zero, 0x68
    ctx->r6 = ADD32(0, 0X68);
    func_i2_802C86E4(rdram, ctx);
        goto after_7;
    // 0x802C7DC0: addiu       $a2, $zero, 0x68
    ctx->r6 = ADD32(0, 0X68);
    after_7:
    // 0x802C7DC4: lui         $t0, 0x802D
    ctx->r8 = S32(0X802D << 16);
    // 0x802C7DC8: addiu       $t0, $t0, -0x73A8
    ctx->r8 = ADD32(ctx->r8, -0X73A8);
    // 0x802C7DCC: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
L_802C7DD0:
    // 0x802C7DD0: lw          $t9, 0x4($t0)
    ctx->r25 = MEM_W(ctx->r8, 0X4);
    // 0x802C7DD4: beq         $t9, $zero, L_802C7DF0
    if (ctx->r25 == 0) {
        // 0x802C7DD8: addiu       $a1, $zero, 0x101
        ctx->r5 = ADD32(0, 0X101);
            goto L_802C7DF0;
    }
    // 0x802C7DD8: addiu       $a1, $zero, 0x101
    ctx->r5 = ADD32(0, 0X101);
    // 0x802C7DDC: jal         0x802C86E4
    // 0x802C7DE0: addiu       $a2, $zero, 0x68
    ctx->r6 = ADD32(0, 0X68);
    func_i2_802C86E4(rdram, ctx);
        goto after_8;
    // 0x802C7DE0: addiu       $a2, $zero, 0x68
    ctx->r6 = ADD32(0, 0X68);
    after_8:
    // 0x802C7DE4: lui         $t0, 0x802D
    ctx->r8 = S32(0X802D << 16);
    // 0x802C7DE8: addiu       $t0, $t0, -0x73A8
    ctx->r8 = ADD32(ctx->r8, -0X73A8);
    // 0x802C7DEC: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
L_802C7DF0:
    // 0x802C7DF0: lw          $v1, 0x0($t0)
    ctx->r3 = MEM_W(ctx->r8, 0X0);
    // 0x802C7DF4: lui         $a3, 0x802D
    ctx->r7 = S32(0X802D << 16);
    // 0x802C7DF8: addiu       $a3, $a3, -0x7396
    ctx->r7 = ADD32(ctx->r7, -0X7396);
    // 0x802C7DFC: beq         $v1, $zero, L_802C7E24
    if (ctx->r3 == 0) {
        // 0x802C7E00: lui         $t4, 0xF568
        ctx->r12 = S32(0XF568 << 16);
            goto L_802C7E24;
    }
    // 0x802C7E00: lui         $t4, 0xF568
    ctx->r12 = S32(0XF568 << 16);
    // 0x802C7E04: slti        $at, $v1, 0x5
    ctx->r1 = SIGNED(ctx->r3) < 0X5 ? 1 : 0;
    // 0x802C7E08: beq         $at, $zero, L_802C7E24
    if (ctx->r1 == 0) {
        // 0x802C7E0C: lui         $t6, 0x600
        ctx->r14 = S32(0X600 << 16);
            goto L_802C7E24;
    }
    // 0x802C7E0C: lui         $t6, 0x600
    ctx->r14 = S32(0X600 << 16);
    // 0x802C7E10: lui         $t7, 0x80C
    ctx->r15 = S32(0X80C << 16);
    // 0x802C7E14: addiu       $t7, $t7, -0x1D48
    ctx->r15 = ADD32(ctx->r15, -0X1D48);
    // 0x802C7E18: sw          $t7, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r15;
    // 0x802C7E1C: addiu       $a0, $v0, 0x8
    ctx->r4 = ADD32(ctx->r2, 0X8);
    // 0x802C7E20: sw          $t6, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r14;
L_802C7E24:
    // 0x802C7E24: lw          $v0, 0x4($t0)
    ctx->r2 = MEM_W(ctx->r8, 0X4);
    // 0x802C7E28: lui         $t7, 0xB900
    ctx->r15 = S32(0XB900 << 16);
    // 0x802C7E2C: lui         $t6, 0xE700
    ctx->r14 = S32(0XE700 << 16);
    // 0x802C7E30: beq         $v0, $zero, L_802C7E5C
    if (ctx->r2 == 0) {
        // 0x802C7E34: ori         $t7, $t7, 0x31D
        ctx->r15 = ctx->r15 | 0X31D;
            goto L_802C7E5C;
    }
    // 0x802C7E34: ori         $t7, $t7, 0x31D
    ctx->r15 = ctx->r15 | 0X31D;
    // 0x802C7E38: slti        $at, $v0, 0x5
    ctx->r1 = SIGNED(ctx->r2) < 0X5 ? 1 : 0;
    // 0x802C7E3C: beq         $at, $zero, L_802C7E5C
    if (ctx->r1 == 0) {
        // 0x802C7E40: or          $v0, $a0, $zero
        ctx->r2 = ctx->r4 | 0;
            goto L_802C7E5C;
    }
    // 0x802C7E40: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x802C7E44: lui         $t9, 0x80C
    ctx->r25 = S32(0X80C << 16);
    // 0x802C7E48: addiu       $t9, $t9, -0x1C38
    ctx->r25 = ADD32(ctx->r25, -0X1C38);
    // 0x802C7E4C: lui         $t8, 0x600
    ctx->r24 = S32(0X600 << 16);
    // 0x802C7E50: sw          $t8, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r24;
    // 0x802C7E54: sw          $t9, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r25;
    // 0x802C7E58: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
L_802C7E5C:
    // 0x802C7E5C: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x802C7E60: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C7E64: sw          $t6, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r14;
    // 0x802C7E68: or          $v1, $a0, $zero
    ctx->r3 = ctx->r4 | 0;
    // 0x802C7E6C: sw          $zero, 0x4($v0)
    MEM_W(0X4, ctx->r2) = 0;
    // 0x802C7E70: lui         $t8, 0x50
    ctx->r24 = S32(0X50 << 16);
    // 0x802C7E74: ori         $t8, $t8, 0x4240
    ctx->r24 = ctx->r24 | 0X4240;
    // 0x802C7E78: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C7E7C: sw          $t8, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r24;
    // 0x802C7E80: sw          $t7, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r15;
    // 0x802C7E84: or          $a1, $a0, $zero
    ctx->r5 = ctx->r4 | 0;
    // 0x802C7E88: lui         $t6, 0xFF2F
    ctx->r14 = S32(0XFF2F << 16);
    // 0x802C7E8C: lui         $t9, 0xFC11
    ctx->r25 = S32(0XFC11 << 16);
    // 0x802C7E90: ori         $t9, $t9, 0x9623
    ctx->r25 = ctx->r25 | 0X9623;
    // 0x802C7E94: ori         $t6, $t6, 0xFFFF
    ctx->r14 = ctx->r14 | 0XFFFF;
    // 0x802C7E98: sw          $t6, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r14;
    // 0x802C7E9C: sw          $t9, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r25;
    // 0x802C7EA0: lh          $a2, 0x0($a3)
    ctx->r6 = MEM_H(ctx->r7, 0X0);
    // 0x802C7EA4: lui         $t0, 0x800E
    ctx->r8 = S32(0X800E << 16);
    // 0x802C7EA8: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C7EAC: bne         $a2, $zero, L_802C7F74
    if (ctx->r6 != 0) {
        // 0x802C7EB0: addiu       $t0, $t0, -0x5640
        ctx->r8 = ADD32(ctx->r8, -0X5640);
            goto L_802C7F74;
    }
    // 0x802C7EB0: addiu       $t0, $t0, -0x5640
    ctx->r8 = ADD32(ctx->r8, -0X5640);
    // 0x802C7EB4: lui         $v1, 0x802D
    ctx->r3 = S32(0X802D << 16);
    // 0x802C7EB8: addiu       $v1, $v1, -0x7398
    ctx->r3 = ADD32(ctx->r3, -0X7398);
    // 0x802C7EBC: lh          $v0, 0x0($v1)
    ctx->r2 = MEM_H(ctx->r3, 0X0);
    // 0x802C7EC0: lui         $at, 0x4080
    ctx->r1 = S32(0X4080 << 16);
    // 0x802C7EC4: mtc1        $at, $f0
    ctx->f0.u32l = ctx->r1;
    // 0x802C7EC8: mtc1        $v0, $f4
    ctx->f4.u32l = ctx->r2;
    // 0x802C7ECC: lui         $at, 0x437F
    ctx->r1 = S32(0X437F << 16);
    // 0x802C7ED0: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x802C7ED4: cvt.s.w     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
    // 0x802C7ED8: addiu       $t3, $zero, 0x1
    ctx->r11 = ADD32(0, 0X1);
    // 0x802C7EDC: lui         $at, 0x4F00
    ctx->r1 = S32(0X4F00 << 16);
    // 0x802C7EE0: mul.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = MUL_S(ctx->f6.fl, ctx->f8.fl);
    // 0x802C7EE4: div.s       $f16, $f10, $f0
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f16.fl = DIV_S(ctx->f10.fl, ctx->f0.fl);
    // 0x802C7EE8: cfc1        $t7, $FpcCsr
    ctx->r15 = get_cop1_cs();
    // 0x802C7EEC: ctc1        $t3, $FpcCsr
    set_cop1_cs(ctx->r11);
    // 0x802C7EF0: nop

    // 0x802C7EF4: cvt.w.s     $f18, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    ctx->f18.u32l = CVT_W_S(ctx->f16.fl);
    // 0x802C7EF8: cfc1        $t3, $FpcCsr
    ctx->r11 = get_cop1_cs();
    // 0x802C7EFC: nop

    // 0x802C7F00: andi        $t3, $t3, 0x78
    ctx->r11 = ctx->r11 & 0X78;
    // 0x802C7F04: beql        $t3, $zero, L_802C7F5C
    if (ctx->r11 == 0) {
        // 0x802C7F08: mfc1        $t3, $f18
        ctx->r11 = (int32_t)ctx->f18.u32l;
            goto L_802C7F5C;
    }
    goto skip_0;
    // 0x802C7F08: mfc1        $t3, $f18
    ctx->r11 = (int32_t)ctx->f18.u32l;
    skip_0:
    // 0x802C7F0C: mtc1        $at, $f18
    ctx->f18.u32l = ctx->r1;
    // 0x802C7F10: addiu       $t3, $zero, 0x1
    ctx->r11 = ADD32(0, 0X1);
    // 0x802C7F14: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x802C7F18: sub.s       $f18, $f16, $f18
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f18.fl = ctx->f16.fl - ctx->f18.fl;
    // 0x802C7F1C: ctc1        $t3, $FpcCsr
    set_cop1_cs(ctx->r11);
    // 0x802C7F20: nop

    // 0x802C7F24: cvt.w.s     $f18, $f18
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 18);
    ctx->f18.u32l = CVT_W_S(ctx->f18.fl);
    // 0x802C7F28: cfc1        $t3, $FpcCsr
    ctx->r11 = get_cop1_cs();
    // 0x802C7F2C: nop

    // 0x802C7F30: andi        $t3, $t3, 0x78
    ctx->r11 = ctx->r11 & 0X78;
    // 0x802C7F34: bnel        $t3, $zero, L_802C7F50
    if (ctx->r11 != 0) {
        // 0x802C7F38: ctc1        $t7, $FpcCsr
        set_cop1_cs(ctx->r15);
            goto L_802C7F50;
    }
    goto skip_1;
    // 0x802C7F38: ctc1        $t7, $FpcCsr
    set_cop1_cs(ctx->r15);
    skip_1:
    // 0x802C7F3C: mfc1        $t3, $f18
    ctx->r11 = (int32_t)ctx->f18.u32l;
    // 0x802C7F40: ctc1        $t7, $FpcCsr
    set_cop1_cs(ctx->r15);
    // 0x802C7F44: b           L_802C8030
    // 0x802C7F48: or          $t3, $t3, $at
    ctx->r11 = ctx->r11 | ctx->r1;
        goto L_802C8030;
    // 0x802C7F48: or          $t3, $t3, $at
    ctx->r11 = ctx->r11 | ctx->r1;
    // 0x802C7F4C: ctc1        $t7, $FpcCsr
    set_cop1_cs(ctx->r15);
L_802C7F50:
    // 0x802C7F50: b           L_802C8030
    // 0x802C7F54: addiu       $t3, $zero, -0x1
    ctx->r11 = ADD32(0, -0X1);
        goto L_802C8030;
    // 0x802C7F54: addiu       $t3, $zero, -0x1
    ctx->r11 = ADD32(0, -0X1);
    // 0x802C7F58: mfc1        $t3, $f18
    ctx->r11 = (int32_t)ctx->f18.u32l;
L_802C7F5C:
    // 0x802C7F5C: nop

    // 0x802C7F60: bltzl       $t3, L_802C7F50
    if (SIGNED(ctx->r11) < 0) {
        // 0x802C7F64: ctc1        $t7, $FpcCsr
        set_cop1_cs(ctx->r15);
            goto L_802C7F50;
    }
    goto skip_2;
    // 0x802C7F64: ctc1        $t7, $FpcCsr
    set_cop1_cs(ctx->r15);
    skip_2:
    // 0x802C7F68: ctc1        $t7, $FpcCsr
    set_cop1_cs(ctx->r15);
    // 0x802C7F6C: b           L_802C8034
    // 0x802C7F70: addiu       $t9, $v0, 0x1
    ctx->r25 = ADD32(ctx->r2, 0X1);
        goto L_802C8034;
    // 0x802C7F70: addiu       $t9, $v0, 0x1
    ctx->r25 = ADD32(ctx->r2, 0X1);
L_802C7F74:
    // 0x802C7F74: lui         $v1, 0x802D
    ctx->r3 = S32(0X802D << 16);
    // 0x802C7F78: addiu       $v1, $v1, -0x7398
    ctx->r3 = ADD32(ctx->r3, -0X7398);
    // 0x802C7F7C: lh          $v0, 0x0($v1)
    ctx->r2 = MEM_H(ctx->r3, 0X0);
    // 0x802C7F80: lui         $at, 0x4080
    ctx->r1 = S32(0X4080 << 16);
    // 0x802C7F84: mtc1        $at, $f0
    ctx->f0.u32l = ctx->r1;
    // 0x802C7F88: mtc1        $v0, $f4
    ctx->f4.u32l = ctx->r2;
    // 0x802C7F8C: lui         $at, 0x437F
    ctx->r1 = S32(0X437F << 16);
    // 0x802C7F90: mtc1        $at, $f10
    ctx->f10.u32l = ctx->r1;
    // 0x802C7F94: cvt.s.w     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
    // 0x802C7F98: addiu       $t3, $zero, 0x1
    ctx->r11 = ADD32(0, 0X1);
    // 0x802C7F9C: lui         $at, 0x4F00
    ctx->r1 = S32(0X4F00 << 16);
    // 0x802C7FA0: sub.s       $f8, $f0, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = ctx->f0.fl - ctx->f6.fl;
    // 0x802C7FA4: mul.s       $f16, $f8, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f16.fl = MUL_S(ctx->f8.fl, ctx->f10.fl);
    // 0x802C7FA8: div.s       $f18, $f16, $f0
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f18.fl = DIV_S(ctx->f16.fl, ctx->f0.fl);
    // 0x802C7FAC: cfc1        $t8, $FpcCsr
    ctx->r24 = get_cop1_cs();
    // 0x802C7FB0: ctc1        $t3, $FpcCsr
    set_cop1_cs(ctx->r11);
    // 0x802C7FB4: nop

    // 0x802C7FB8: cvt.w.s     $f4, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    ctx->f4.u32l = CVT_W_S(ctx->f18.fl);
    // 0x802C7FBC: cfc1        $t3, $FpcCsr
    ctx->r11 = get_cop1_cs();
    // 0x802C7FC0: nop

    // 0x802C7FC4: andi        $t3, $t3, 0x78
    ctx->r11 = ctx->r11 & 0X78;
    // 0x802C7FC8: beql        $t3, $zero, L_802C8018
    if (ctx->r11 == 0) {
        // 0x802C7FCC: mfc1        $t3, $f4
        ctx->r11 = (int32_t)ctx->f4.u32l;
            goto L_802C8018;
    }
    goto skip_3;
    // 0x802C7FCC: mfc1        $t3, $f4
    ctx->r11 = (int32_t)ctx->f4.u32l;
    skip_3:
    // 0x802C7FD0: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x802C7FD4: addiu       $t3, $zero, 0x1
    ctx->r11 = ADD32(0, 0X1);
    // 0x802C7FD8: sub.s       $f4, $f18, $f4
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f4.fl = ctx->f18.fl - ctx->f4.fl;
    // 0x802C7FDC: ctc1        $t3, $FpcCsr
    set_cop1_cs(ctx->r11);
    // 0x802C7FE0: nop

    // 0x802C7FE4: cvt.w.s     $f4, $f4
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 4);
    ctx->f4.u32l = CVT_W_S(ctx->f4.fl);
    // 0x802C7FE8: cfc1        $t3, $FpcCsr
    ctx->r11 = get_cop1_cs();
    // 0x802C7FEC: nop

    // 0x802C7FF0: andi        $t3, $t3, 0x78
    ctx->r11 = ctx->r11 & 0X78;
    // 0x802C7FF4: bne         $t3, $zero, L_802C800C
    if (ctx->r11 != 0) {
        // 0x802C7FF8: nop
    
            goto L_802C800C;
    }
    // 0x802C7FF8: nop

    // 0x802C7FFC: mfc1        $t3, $f4
    ctx->r11 = (int32_t)ctx->f4.u32l;
    // 0x802C8000: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x802C8004: b           L_802C8024
    // 0x802C8008: or          $t3, $t3, $at
    ctx->r11 = ctx->r11 | ctx->r1;
        goto L_802C8024;
    // 0x802C8008: or          $t3, $t3, $at
    ctx->r11 = ctx->r11 | ctx->r1;
L_802C800C:
    // 0x802C800C: b           L_802C8024
    // 0x802C8010: addiu       $t3, $zero, -0x1
    ctx->r11 = ADD32(0, -0X1);
        goto L_802C8024;
    // 0x802C8010: addiu       $t3, $zero, -0x1
    ctx->r11 = ADD32(0, -0X1);
    // 0x802C8014: mfc1        $t3, $f4
    ctx->r11 = (int32_t)ctx->f4.u32l;
L_802C8018:
    // 0x802C8018: nop

    // 0x802C801C: bltz        $t3, L_802C800C
    if (SIGNED(ctx->r11) < 0) {
        // 0x802C8020: nop
    
            goto L_802C800C;
    }
    // 0x802C8020: nop

L_802C8024:
    // 0x802C8024: ctc1        $t8, $FpcCsr
    set_cop1_cs(ctx->r24);
    // 0x802C8028: nop

    // 0x802C802C: nop

L_802C8030:
    // 0x802C8030: addiu       $t9, $v0, 0x1
    ctx->r25 = ADD32(ctx->r2, 0X1);
L_802C8034:
    // 0x802C8034: sh          $t9, 0x0($v1)
    MEM_H(0X0, ctx->r3) = ctx->r25;
    // 0x802C8038: lh          $t6, 0x0($v1)
    ctx->r14 = MEM_H(ctx->r3, 0X0);
    // 0x802C803C: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x802C8040: ori         $t4, $t4, 0x1000
    ctx->r12 = ctx->r12 | 0X1000;
    // 0x802C8044: slti        $at, $t6, 0x4
    ctx->r1 = SIGNED(ctx->r14) < 0X4 ? 1 : 0;
    // 0x802C8048: bne         $at, $zero, L_802C805C
    if (ctx->r1 != 0) {
        // 0x802C804C: addiu       $a0, $a0, 0x8
        ctx->r4 = ADD32(ctx->r4, 0X8);
            goto L_802C805C;
    }
    // 0x802C804C: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C8050: xori        $t7, $a2, 0x1
    ctx->r15 = ctx->r6 ^ 0X1;
    // 0x802C8054: sh          $zero, 0x0($v1)
    MEM_H(0X0, ctx->r3) = 0;
    // 0x802C8058: sh          $t7, 0x0($a3)
    MEM_H(0X0, ctx->r7) = ctx->r15;
L_802C805C:
    // 0x802C805C: lw          $t8, 0x0($t0)
    ctx->r24 = MEM_W(ctx->r8, 0X0);
    // 0x802C8060: lw          $t9, 0x4($t0)
    ctx->r25 = MEM_W(ctx->r8, 0X4);
    // 0x802C8064: andi        $a3, $t3, 0xFF
    ctx->r7 = ctx->r11 & 0XFF;
    // 0x802C8068: sll         $t1, $a3, 8
    ctx->r9 = S32(ctx->r7 << 8);
    // 0x802C806C: bne         $t8, $t9, L_802C807C
    if (ctx->r24 != ctx->r25) {
        // 0x802C8070: lui         $t6, 0xFA00
        ctx->r14 = S32(0XFA00 << 16);
            goto L_802C807C;
    }
    // 0x802C8070: lui         $t6, 0xFA00
    ctx->r14 = S32(0XFA00 << 16);
    // 0x802C8074: b           L_802C8080
    // 0x802C8078: addiu       $ra, $zero, 0x20
    ctx->r31 = ADD32(0, 0X20);
        goto L_802C8080;
    // 0x802C8078: addiu       $ra, $zero, 0x20
    ctx->r31 = ADD32(0, 0X20);
L_802C807C:
    // 0x802C807C: addiu       $ra, $zero, 0x40
    ctx->r31 = ADD32(0, 0X40);
L_802C8080:
    // 0x802C8080: sll         $t7, $a3, 16
    ctx->r15 = S32(ctx->r7 << 16);
    // 0x802C8084: lui         $at, 0xFF00
    ctx->r1 = S32(0XFF00 << 16);
    // 0x802C8088: or          $t8, $t7, $at
    ctx->r24 = ctx->r15 | ctx->r1;
    // 0x802C808C: or          $t9, $t8, $t1
    ctx->r25 = ctx->r24 | ctx->r9;
    // 0x802C8090: sw          $t6, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r14;
    // 0x802C8094: ori         $t6, $t9, 0xFF
    ctx->r14 = ctx->r25 | 0XFF;
    // 0x802C8098: sw          $t6, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r14;
    // 0x802C809C: or          $v1, $a0, $zero
    ctx->r3 = ctx->r4 | 0;
    // 0x802C80A0: lui         $t8, 0x80B
    ctx->r24 = S32(0X80B << 16);
    // 0x802C80A4: lui         $t7, 0xFD68
    ctx->r15 = S32(0XFD68 << 16);
    // 0x802C80A8: ori         $t7, $t7, 0x3F
    ctx->r15 = ctx->r15 | 0X3F;
    // 0x802C80AC: addiu       $t8, $t8, 0x6E98
    ctx->r24 = ADD32(ctx->r24, 0X6E98);
    // 0x802C80B0: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C80B4: or          $a1, $a0, $zero
    ctx->r5 = ctx->r4 | 0;
    // 0x802C80B8: sw          $t8, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r24;
    // 0x802C80BC: sw          $t7, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r15;
    // 0x802C80C0: lui         $t9, 0x708
    ctx->r25 = S32(0X708 << 16);
    // 0x802C80C4: ori         $t9, $t9, 0x200
    ctx->r25 = ctx->r25 | 0X200;
    // 0x802C80C8: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C80CC: or          $a2, $a0, $zero
    ctx->r6 = ctx->r4 | 0;
    // 0x802C80D0: sw          $t9, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r25;
    // 0x802C80D4: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C80D8: sw          $t4, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r12;
    // 0x802C80DC: or          $t2, $a0, $zero
    ctx->r10 = ctx->r4 | 0;
    // 0x802C80E0: lui         $t6, 0xE600
    ctx->r14 = S32(0XE600 << 16);
    // 0x802C80E4: sw          $t6, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r14;
    // 0x802C80E8: sw          $zero, 0x4($a2)
    MEM_W(0X4, ctx->r6) = 0;
    // 0x802C80EC: lui         $t8, 0x70F
    ctx->r24 = S32(0X70F << 16);
    // 0x802C80F0: ori         $t8, $t8, 0xC08C
    ctx->r24 = ctx->r24 | 0XC08C;
    // 0x802C80F4: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C80F8: lui         $t7, 0xF400
    ctx->r15 = S32(0XF400 << 16);
    // 0x802C80FC: sw          $t7, 0x0($t2)
    MEM_W(0X0, ctx->r10) = ctx->r15;
    // 0x802C8100: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x802C8104: sw          $t8, 0x4($t2)
    MEM_W(0X4, ctx->r10) = ctx->r24;
    // 0x802C8108: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C810C: or          $v1, $a0, $zero
    ctx->r3 = ctx->r4 | 0;
    // 0x802C8110: lui         $t9, 0xE700
    ctx->r25 = S32(0XE700 << 16);
    // 0x802C8114: sw          $t9, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r25;
    // 0x802C8118: sw          $zero, 0x4($v0)
    MEM_W(0X4, ctx->r2) = 0;
    // 0x802C811C: lui         $t6, 0x8
    ctx->r14 = S32(0X8 << 16);
    // 0x802C8120: ori         $t6, $t6, 0x200
    ctx->r14 = ctx->r14 | 0X200;
    // 0x802C8124: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C8128: or          $a1, $a0, $zero
    ctx->r5 = ctx->r4 | 0;
    // 0x802C812C: sw          $t6, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r14;
    // 0x802C8130: sw          $t4, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r12;
    // 0x802C8134: lui         $t8, 0xF
    ctx->r24 = S32(0XF << 16);
    // 0x802C8138: ori         $t8, $t8, 0xC08C
    ctx->r24 = ctx->r24 | 0XC08C;
    // 0x802C813C: lui         $t7, 0xF200
    ctx->r15 = S32(0XF200 << 16);
    // 0x802C8140: sw          $t7, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r15;
    // 0x802C8144: sw          $t8, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r24;
    // 0x802C8148: lw          $t9, 0x4($t0)
    ctx->r25 = MEM_W(ctx->r8, 0X4);
    // 0x802C814C: lui         $t5, 0x802D
    ctx->r13 = S32(0X802D << 16);
    // 0x802C8150: addiu       $t5, $t5, -0x7430
    ctx->r13 = ADD32(ctx->r13, -0X7430);
    // 0x802C8154: sll         $t6, $t9, 1
    ctx->r14 = S32(ctx->r25 << 1);
    // 0x802C8158: addu        $t7, $t5, $t6
    ctx->r15 = ADD32(ctx->r13, ctx->r14);
    // 0x802C815C: lh          $t8, 0x0($t7)
    ctx->r24 = MEM_H(ctx->r15, 0X0);
    // 0x802C8160: lui         $at, 0xE400
    ctx->r1 = S32(0XE400 << 16);
    // 0x802C8164: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C8168: addiu       $t9, $t8, 0x48
    ctx->r25 = ADD32(ctx->r24, 0X48);
    // 0x802C816C: sll         $t6, $t9, 2
    ctx->r14 = S32(ctx->r25 << 2);
    // 0x802C8170: andi        $t7, $t6, 0xFFF
    ctx->r15 = ctx->r14 & 0XFFF;
    // 0x802C8174: sll         $t8, $t7, 12
    ctx->r24 = S32(ctx->r15 << 12);
    // 0x802C8178: or          $t9, $t8, $at
    ctx->r25 = ctx->r24 | ctx->r1;
    // 0x802C817C: ori         $t6, $t9, 0x16C
    ctx->r14 = ctx->r25 | 0X16C;
    // 0x802C8180: or          $a2, $a0, $zero
    ctx->r6 = ctx->r4 | 0;
    // 0x802C8184: sw          $t6, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r14;
    // 0x802C8188: lw          $t7, 0x4($t0)
    ctx->r15 = MEM_W(ctx->r8, 0X4);
    // 0x802C818C: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C8190: or          $t3, $a0, $zero
    ctx->r11 = ctx->r4 | 0;
    // 0x802C8194: sll         $t8, $t7, 1
    ctx->r24 = S32(ctx->r15 << 1);
    // 0x802C8198: addu        $t9, $t5, $t8
    ctx->r25 = ADD32(ctx->r13, ctx->r24);
    // 0x802C819C: lh          $t6, 0x0($t9)
    ctx->r14 = MEM_H(ctx->r25, 0X0);
    // 0x802C81A0: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C81A4: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x802C81A8: addiu       $t7, $t6, 0x8
    ctx->r15 = ADD32(ctx->r14, 0X8);
    // 0x802C81AC: sll         $t8, $t7, 2
    ctx->r24 = S32(ctx->r15 << 2);
    // 0x802C81B0: andi        $t9, $t8, 0xFFF
    ctx->r25 = ctx->r24 & 0XFFF;
    // 0x802C81B4: sll         $t6, $t9, 12
    ctx->r14 = S32(ctx->r25 << 12);
    // 0x802C81B8: ori         $t7, $t6, 0xDC
    ctx->r15 = ctx->r14 | 0XDC;
    // 0x802C81BC: sw          $t7, 0x4($a2)
    MEM_W(0X4, ctx->r6) = ctx->r15;
    // 0x802C81C0: lui         $t2, 0xB300
    ctx->r10 = S32(0XB300 << 16);
    // 0x802C81C4: sw          $t2, 0x0($t3)
    MEM_W(0X0, ctx->r11) = ctx->r10;
    // 0x802C81C8: sw          $zero, 0x4($t3)
    MEM_W(0X4, ctx->r11) = 0;
    // 0x802C81CC: lui         $t9, 0x400
    ctx->r25 = S32(0X400 << 16);
    // 0x802C81D0: ori         $t9, $t9, 0x400
    ctx->r25 = ctx->r25 | 0X400;
    // 0x802C81D4: lui         $t8, 0xB200
    ctx->r24 = S32(0XB200 << 16);
    // 0x802C81D8: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C81DC: sw          $t8, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r24;
    // 0x802C81E0: sw          $t9, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r25;
    // 0x802C81E4: or          $v1, $a0, $zero
    ctx->r3 = ctx->r4 | 0;
    // 0x802C81E8: sll         $t7, $a3, 24
    ctx->r15 = S32(ctx->r7 << 24);
    // 0x802C81EC: lui         $at, 0xFF
    ctx->r1 = S32(0XFF << 16);
    // 0x802C81F0: or          $t8, $t7, $at
    ctx->r24 = ctx->r15 | ctx->r1;
    // 0x802C81F4: lui         $t6, 0xFA00
    ctx->r14 = S32(0XFA00 << 16);
    // 0x802C81F8: sw          $t6, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r14;
    // 0x802C81FC: or          $t9, $t8, $t1
    ctx->r25 = ctx->r24 | ctx->r9;
    // 0x802C8200: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C8204: ori         $t6, $t9, 0xFF
    ctx->r14 = ctx->r25 | 0XFF;
    // 0x802C8208: or          $a1, $a0, $zero
    ctx->r5 = ctx->r4 | 0;
    // 0x802C820C: sw          $t6, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r14;
    // 0x802C8210: lui         $t8, 0x80B
    ctx->r24 = S32(0X80B << 16);
    // 0x802C8214: lui         $t7, 0xFD68
    ctx->r15 = S32(0XFD68 << 16);
    // 0x802C8218: ori         $t7, $t7, 0x3F
    ctx->r15 = ctx->r15 | 0X3F;
    // 0x802C821C: addiu       $t8, $t8, 0x6590
    ctx->r24 = ADD32(ctx->r24, 0X6590);
    // 0x802C8220: sw          $t8, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r24;
    // 0x802C8224: sw          $t7, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r15;
    // 0x802C8228: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C822C: or          $a2, $a0, $zero
    ctx->r6 = ctx->r4 | 0;
    // 0x802C8230: lui         $t9, 0x708
    ctx->r25 = S32(0X708 << 16);
    // 0x802C8234: ori         $t9, $t9, 0x200
    ctx->r25 = ctx->r25 | 0X200;
    // 0x802C8238: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C823C: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x802C8240: sw          $t9, 0x4($a2)
    MEM_W(0X4, ctx->r6) = ctx->r25;
    // 0x802C8244: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C8248: sw          $t4, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r12;
    // 0x802C824C: or          $v1, $a0, $zero
    ctx->r3 = ctx->r4 | 0;
    // 0x802C8250: lui         $t6, 0xE600
    ctx->r14 = S32(0XE600 << 16);
    // 0x802C8254: sw          $t6, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r14;
    // 0x802C8258: sw          $zero, 0x4($v0)
    MEM_W(0X4, ctx->r2) = 0;
    // 0x802C825C: lui         $t8, 0x70F
    ctx->r24 = S32(0X70F << 16);
    // 0x802C8260: ori         $t8, $t8, 0xC08C
    ctx->r24 = ctx->r24 | 0XC08C;
    // 0x802C8264: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C8268: lui         $t7, 0xF400
    ctx->r15 = S32(0XF400 << 16);
    // 0x802C826C: sw          $t7, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r15;
    // 0x802C8270: or          $a1, $a0, $zero
    ctx->r5 = ctx->r4 | 0;
    // 0x802C8274: sw          $t8, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r24;
    // 0x802C8278: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C827C: or          $a2, $a0, $zero
    ctx->r6 = ctx->r4 | 0;
    // 0x802C8280: lui         $t9, 0xE700
    ctx->r25 = S32(0XE700 << 16);
    // 0x802C8284: sw          $t9, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r25;
    // 0x802C8288: sw          $zero, 0x4($a1)
    MEM_W(0X4, ctx->r5) = 0;
    // 0x802C828C: lui         $t6, 0x8
    ctx->r14 = S32(0X8 << 16);
    // 0x802C8290: ori         $t6, $t6, 0x200
    ctx->r14 = ctx->r14 | 0X200;
    // 0x802C8294: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C8298: or          $a3, $a0, $zero
    ctx->r7 = ctx->r4 | 0;
    // 0x802C829C: sw          $t6, 0x4($a2)
    MEM_W(0X4, ctx->r6) = ctx->r14;
    // 0x802C82A0: sw          $t4, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r12;
    // 0x802C82A4: lui         $t8, 0xF
    ctx->r24 = S32(0XF << 16);
    // 0x802C82A8: ori         $t8, $t8, 0xC08C
    ctx->r24 = ctx->r24 | 0XC08C;
    // 0x802C82AC: lui         $t7, 0xF200
    ctx->r15 = S32(0XF200 << 16);
    // 0x802C82B0: sw          $t7, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r15;
    // 0x802C82B4: sw          $t8, 0x4($a3)
    MEM_W(0X4, ctx->r7) = ctx->r24;
    // 0x802C82B8: lw          $t9, 0x0($t0)
    ctx->r25 = MEM_W(ctx->r8, 0X0);
    // 0x802C82BC: lui         $at, 0xE400
    ctx->r1 = S32(0XE400 << 16);
    // 0x802C82C0: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C82C4: sll         $t6, $t9, 1
    ctx->r14 = S32(ctx->r25 << 1);
    // 0x802C82C8: addu        $t7, $t5, $t6
    ctx->r15 = ADD32(ctx->r13, ctx->r14);
    // 0x802C82CC: lh          $t8, 0x0($t7)
    ctx->r24 = MEM_H(ctx->r15, 0X0);
    // 0x802C82D0: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x802C82D4: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C82D8: addu        $t9, $t8, $ra
    ctx->r25 = ADD32(ctx->r24, ctx->r31);
    // 0x802C82DC: addiu       $t6, $t9, 0x8
    ctx->r14 = ADD32(ctx->r25, 0X8);
    // 0x802C82E0: sll         $t7, $t6, 2
    ctx->r15 = S32(ctx->r14 << 2);
    // 0x802C82E4: andi        $t8, $t7, 0xFFF
    ctx->r24 = ctx->r15 & 0XFFF;
    // 0x802C82E8: sll         $t9, $t8, 12
    ctx->r25 = S32(ctx->r24 << 12);
    // 0x802C82EC: or          $t6, $t9, $at
    ctx->r14 = ctx->r25 | ctx->r1;
    // 0x802C82F0: ori         $t7, $t6, 0x16C
    ctx->r15 = ctx->r14 | 0X16C;
    // 0x802C82F4: sw          $t7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r15;
    // 0x802C82F8: lw          $t8, 0x0($t0)
    ctx->r24 = MEM_W(ctx->r8, 0X0);
    // 0x802C82FC: or          $v1, $a0, $zero
    ctx->r3 = ctx->r4 | 0;
    // 0x802C8300: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C8304: sll         $t9, $t8, 1
    ctx->r25 = S32(ctx->r24 << 1);
    // 0x802C8308: addu        $t6, $t5, $t9
    ctx->r14 = ADD32(ctx->r13, ctx->r25);
    // 0x802C830C: lh          $t7, 0x0($t6)
    ctx->r15 = MEM_H(ctx->r14, 0X0);
    // 0x802C8310: or          $a2, $a0, $zero
    ctx->r6 = ctx->r4 | 0;
    // 0x802C8314: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C8318: addiu       $t8, $t7, 0x8
    ctx->r24 = ADD32(ctx->r15, 0X8);
    // 0x802C831C: sll         $t9, $t8, 2
    ctx->r25 = S32(ctx->r24 << 2);
    // 0x802C8320: andi        $t6, $t9, 0xFFF
    ctx->r14 = ctx->r25 & 0XFFF;
    // 0x802C8324: sll         $t7, $t6, 12
    ctx->r15 = S32(ctx->r14 << 12);
    // 0x802C8328: ori         $t8, $t7, 0xDC
    ctx->r24 = ctx->r15 | 0XDC;
    // 0x802C832C: sw          $t8, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r24;
    // 0x802C8330: lui         $t6, 0x400
    ctx->r14 = S32(0X400 << 16);
    // 0x802C8334: ori         $t6, $t6, 0x400
    ctx->r14 = ctx->r14 | 0X400;
    // 0x802C8338: sw          $zero, 0x4($v1)
    MEM_W(0X4, ctx->r3) = 0;
    // 0x802C833C: sw          $t2, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r10;
    // 0x802C8340: lui         $t9, 0xB200
    ctx->r25 = S32(0XB200 << 16);
    // 0x802C8344: sw          $t9, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r25;
    // 0x802C8348: sw          $t6, 0x4($a2)
    MEM_W(0X4, ctx->r6) = ctx->r14;
    // 0x802C834C: jal         0x802C70EC
    // 0x802C8350: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_i2_802C70EC(rdram, ctx);
        goto after_9;
    // 0x802C8350: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_9:
    // 0x802C8354: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C8358: jal         0x802C70EC
    // 0x802C835C: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    func_i2_802C70EC(rdram, ctx);
        goto after_10;
    // 0x802C835C: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    after_10:
    // 0x802C8360: lui         $t7, 0xB400
    ctx->r15 = S32(0XB400 << 16);
    // 0x802C8364: sw          $t7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r15;
    // 0x802C8368: lui         $t8, 0x802D
    ctx->r24 = S32(0X802D << 16);
    // 0x802C836C: lhu         $t8, -0x73B0($t8)
    ctx->r24 = MEM_HU(ctx->r24, -0X73B0);
    // 0x802C8370: lui         $t9, 0x103
    ctx->r25 = S32(0X103 << 16);
    // 0x802C8374: lui         $t6, 0x700
    ctx->r14 = S32(0X700 << 16);
    // 0x802C8378: addiu       $t6, $t6, 0xA40
    ctx->r14 = ADD32(ctx->r14, 0XA40);
    // 0x802C837C: ori         $t9, $t9, 0x40
    ctx->r25 = ctx->r25 | 0X40;
    // 0x802C8380: sw          $t9, 0x8($v0)
    MEM_W(0X8, ctx->r2) = ctx->r25;
    // 0x802C8384: sw          $t6, 0xC($v0)
    MEM_W(0XC, ctx->r2) = ctx->r14;
    // 0x802C8388: lui         $t7, 0x107
    ctx->r15 = S32(0X107 << 16);
    // 0x802C838C: sw          $t8, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r24;
    // 0x802C8390: lui         $v1, 0x600
    ctx->r3 = S32(0X600 << 16);
    // 0x802C8394: addiu       $t7, $t7, -0xB78
    ctx->r15 = ADD32(ctx->r15, -0XB78);
    // 0x802C8398: lui         $t8, 0x80C
    ctx->r24 = S32(0X80C << 16);
    // 0x802C839C: lui         $t6, 0x700
    ctx->r14 = S32(0X700 << 16);
    // 0x802C83A0: lui         $t9, 0x102
    ctx->r25 = S32(0X102 << 16);
    // 0x802C83A4: sw          $t7, 0x14($v0)
    MEM_W(0X14, ctx->r2) = ctx->r15;
    // 0x802C83A8: addiu       $t8, $t8, -0x1B98
    ctx->r24 = ADD32(ctx->r24, -0X1B98);
    // 0x802C83AC: ori         $t9, $t9, 0x40
    ctx->r25 = ctx->r25 | 0X40;
    // 0x802C83B0: addiu       $t6, $t6, 0xA80
    ctx->r14 = ADD32(ctx->r14, 0XA80);
    // 0x802C83B4: sw          $v1, 0x10($v0)
    MEM_W(0X10, ctx->r2) = ctx->r3;
    // 0x802C83B8: sw          $t8, 0x1C($v0)
    MEM_W(0X1C, ctx->r2) = ctx->r24;
    // 0x802C83BC: sw          $v1, 0x18($v0)
    MEM_W(0X18, ctx->r2) = ctx->r3;
    // 0x802C83C0: sw          $t6, 0x24($v0)
    MEM_W(0X24, ctx->r2) = ctx->r14;
    // 0x802C83C4: sw          $t9, 0x20($v0)
    MEM_W(0X20, ctx->r2) = ctx->r25;
    // 0x802C83C8: lui         $t7, 0x801D
    ctx->r15 = S32(0X801D << 16);
    // 0x802C83CC: lw          $t7, -0x1A08($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X1A08);
    // 0x802C83D0: addiu       $a0, $v0, 0x28
    ctx->r4 = ADD32(ctx->r2, 0X28);
    // 0x802C83D4: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C83D8: addiu       $t8, $t7, 0xC80
    ctx->r24 = ADD32(ctx->r15, 0XC80);
    // 0x802C83DC: sw          $t8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r24;
    // 0x802C83E0: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x802C83E4: jal         0x801E4FE8
    // 0x802C83E8: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_801E4FE8(rdram, ctx);
        goto after_11;
    // 0x802C83E8: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_11:
    // 0x802C83EC: lui         $t9, 0x600
    ctx->r25 = S32(0X600 << 16);
    // 0x802C83F0: lui         $t6, 0x80C
    ctx->r14 = S32(0X80C << 16);
    // 0x802C83F4: lui         $t7, 0x102
    ctx->r15 = S32(0X102 << 16);
    // 0x802C83F8: lui         $t8, 0x700
    ctx->r24 = S32(0X700 << 16);
    // 0x802C83FC: addiu       $t6, $t6, -0x1B88
    ctx->r14 = ADD32(ctx->r14, -0X1B88);
    // 0x802C8400: sw          $t9, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r25;
    // 0x802C8404: addiu       $t8, $t8, 0xAC0
    ctx->r24 = ADD32(ctx->r24, 0XAC0);
    // 0x802C8408: ori         $t7, $t7, 0x40
    ctx->r15 = ctx->r15 | 0X40;
    // 0x802C840C: sw          $t6, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r14;
    // 0x802C8410: sw          $t7, 0x8($v0)
    MEM_W(0X8, ctx->r2) = ctx->r15;
    // 0x802C8414: sw          $t8, 0xC($v0)
    MEM_W(0XC, ctx->r2) = ctx->r24;
    // 0x802C8418: lui         $t9, 0x801D
    ctx->r25 = S32(0X801D << 16);
    // 0x802C841C: lw          $t9, -0x1A08($t9)
    ctx->r25 = MEM_W(ctx->r25, -0X1A08);
    // 0x802C8420: addiu       $a0, $v0, 0x10
    ctx->r4 = ADD32(ctx->r2, 0X10);
    // 0x802C8424: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C8428: addiu       $t6, $t9, 0xD40
    ctx->r14 = ADD32(ctx->r25, 0XD40);
    // 0x802C842C: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x802C8430: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x802C8434: jal         0x801E4FE8
    // 0x802C8438: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_801E4FE8(rdram, ctx);
        goto after_12;
    // 0x802C8438: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_12:
    // 0x802C843C: lui         $t7, 0x600
    ctx->r15 = S32(0X600 << 16);
    // 0x802C8440: lui         $t8, 0x80C
    ctx->r24 = S32(0X80C << 16);
    // 0x802C8444: lui         $t9, 0x102
    ctx->r25 = S32(0X102 << 16);
    // 0x802C8448: lui         $t6, 0x700
    ctx->r14 = S32(0X700 << 16);
    // 0x802C844C: addiu       $t8, $t8, -0x1B78
    ctx->r24 = ADD32(ctx->r24, -0X1B78);
    // 0x802C8450: sw          $t7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r15;
    // 0x802C8454: addiu       $t6, $t6, 0xB00
    ctx->r14 = ADD32(ctx->r14, 0XB00);
    // 0x802C8458: ori         $t9, $t9, 0x40
    ctx->r25 = ctx->r25 | 0X40;
    // 0x802C845C: sw          $t8, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r24;
    // 0x802C8460: sw          $t9, 0x8($v0)
    MEM_W(0X8, ctx->r2) = ctx->r25;
    // 0x802C8464: sw          $t6, 0xC($v0)
    MEM_W(0XC, ctx->r2) = ctx->r14;
    // 0x802C8468: lui         $t7, 0x801D
    ctx->r15 = S32(0X801D << 16);
    // 0x802C846C: lw          $t7, -0x1A08($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X1A08);
    // 0x802C8470: addiu       $a0, $v0, 0x10
    ctx->r4 = ADD32(ctx->r2, 0X10);
    // 0x802C8474: addiu       $a1, $zero, 0x3
    ctx->r5 = ADD32(0, 0X3);
    // 0x802C8478: addiu       $t8, $t7, 0xE00
    ctx->r24 = ADD32(ctx->r15, 0XE00);
    // 0x802C847C: sw          $t8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r24;
    // 0x802C8480: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x802C8484: jal         0x801E4FE8
    // 0x802C8488: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_801E4FE8(rdram, ctx);
        goto after_13;
    // 0x802C8488: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_13:
    // 0x802C848C: lui         $t9, 0x600
    ctx->r25 = S32(0X600 << 16);
    // 0x802C8490: lui         $t6, 0x80C
    ctx->r14 = S32(0X80C << 16);
    // 0x802C8494: lui         $t7, 0x102
    ctx->r15 = S32(0X102 << 16);
    // 0x802C8498: lui         $t8, 0x700
    ctx->r24 = S32(0X700 << 16);
    // 0x802C849C: addiu       $t6, $t6, -0x1B68
    ctx->r14 = ADD32(ctx->r14, -0X1B68);
    // 0x802C84A0: sw          $t9, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r25;
    // 0x802C84A4: addiu       $t8, $t8, 0xB40
    ctx->r24 = ADD32(ctx->r24, 0XB40);
    // 0x802C84A8: ori         $t7, $t7, 0x40
    ctx->r15 = ctx->r15 | 0X40;
    // 0x802C84AC: sw          $t6, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r14;
    // 0x802C84B0: sw          $t7, 0x8($v0)
    MEM_W(0X8, ctx->r2) = ctx->r15;
    // 0x802C84B4: sw          $t8, 0xC($v0)
    MEM_W(0XC, ctx->r2) = ctx->r24;
    // 0x802C84B8: lui         $t9, 0x801D
    ctx->r25 = S32(0X801D << 16);
    // 0x802C84BC: lw          $t9, -0x1A08($t9)
    ctx->r25 = MEM_W(ctx->r25, -0X1A08);
    // 0x802C84C0: addiu       $a0, $v0, 0x10
    ctx->r4 = ADD32(ctx->r2, 0X10);
    // 0x802C84C4: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C84C8: addiu       $t6, $t9, 0xEC0
    ctx->r14 = ADD32(ctx->r25, 0XEC0);
    // 0x802C84CC: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x802C84D0: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x802C84D4: jal         0x801E4FE8
    // 0x802C84D8: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_801E4FE8(rdram, ctx);
        goto after_14;
    // 0x802C84D8: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_14:
    // 0x802C84DC: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    // 0x802C84E0: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x802C84E4: jr          $ra
    // 0x802C84E8: nop

    return;
    // 0x802C84E8: nop

;}
RECOMP_FUNC void func_i2_802C84EC(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C84EC: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x802C84F0: addiu       $v0, $v0, -0x54DC
    ctx->r2 = ADD32(ctx->r2, -0X54DC);
    // 0x802C84F4: lw          $t6, 0x0($v0)
    ctx->r14 = MEM_W(ctx->r2, 0X0);
    // 0x802C84F8: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C84FC: addiu       $t7, $zero, 0xB
    ctx->r15 = ADD32(0, 0XB);
    // 0x802C8500: sw          $t6, -0x19CC($at)
    MEM_W(-0X19CC, ctx->r1) = ctx->r14;
    // 0x802C8504: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C8508: sw          $a0, -0x19D0($at)
    MEM_W(-0X19D0, ctx->r1) = ctx->r4;
    // 0x802C850C: sw          $t7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r15;
    // 0x802C8510: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C8514: addiu       $t8, $zero, 0x4
    ctx->r24 = ADD32(0, 0X4);
    // 0x802C8518: sw          $t8, -0x19C8($at)
    MEM_W(-0X19C8, ctx->r1) = ctx->r24;
    // 0x802C851C: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C8520: addiu       $t9, $zero, 0x1
    ctx->r25 = ADD32(0, 0X1);
    // 0x802C8524: sw          $t9, -0x19C4($at)
    MEM_W(-0X19C4, ctx->r1) = ctx->r25;
    // 0x802C8528: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C852C: sw          $zero, -0x19C0($at)
    MEM_W(-0X19C0, ctx->r1) = 0;
    // 0x802C8530: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C8534: sw          $zero, -0x19BC($at)
    MEM_W(-0X19BC, ctx->r1) = 0;
    // 0x802C8538: lui         $t2, 0x801D
    ctx->r10 = S32(0X801D << 16);
    // 0x802C853C: lh          $t2, -0x19F4($t2)
    ctx->r10 = MEM_H(ctx->r10, -0X19F4);
    // 0x802C8540: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x802C8544: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x802C8548: sw          $zero, -0x54E4($at)
    MEM_W(-0X54E4, ctx->r1) = 0;
    // 0x802C854C: lui         $at, 0x800D
    ctx->r1 = S32(0X800D << 16);
    // 0x802C8550: addiu       $t6, $zero, 0x3
    ctx->r14 = ADD32(0, 0X3);
    // 0x802C8554: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x802C8558: sw          $s1, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r17;
    // 0x802C855C: sw          $s0, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r16;
    // 0x802C8560: sw          $t6, 0x461C($at)
    MEM_W(0X461C, ctx->r1) = ctx->r14;
    // 0x802C8564: blez        $t2, L_802C8660
    if (SIGNED(ctx->r10) <= 0) {
        // 0x802C8568: or          $v1, $zero, $zero
        ctx->r3 = 0 | 0;
            goto L_802C8660;
    }
    // 0x802C8568: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
    // 0x802C856C: lui         $a3, 0x800E
    ctx->r7 = S32(0X800E << 16);
    // 0x802C8570: lui         $a2, 0x800E
    ctx->r6 = S32(0X800E << 16);
    // 0x802C8574: lui         $s1, 0x801D
    ctx->r17 = S32(0X801D << 16);
    // 0x802C8578: lui         $s0, 0x800D
    ctx->r16 = S32(0X800D << 16);
    // 0x802C857C: lui         $t5, 0x8019
    ctx->r13 = S32(0X8019 << 16);
    // 0x802C8580: lui         $t4, 0x800D
    ctx->r12 = S32(0X800D << 16);
    // 0x802C8584: lui         $t3, 0x800E
    ctx->r11 = S32(0X800E << 16);
    // 0x802C8588: lui         $t0, 0x802D
    ctx->r8 = S32(0X802D << 16);
    // 0x802C858C: addiu       $t0, $t0, -0x7428
    ctx->r8 = ADD32(ctx->r8, -0X7428);
    // 0x802C8590: addiu       $t3, $t3, -0x56B0
    ctx->r11 = ADD32(ctx->r11, -0X56B0);
    // 0x802C8594: addiu       $t4, $t4, 0x48DC
    ctx->r12 = ADD32(ctx->r12, 0X48DC);
    // 0x802C8598: addiu       $t5, $t5, 0x2690
    ctx->r13 = ADD32(ctx->r13, 0X2690);
    // 0x802C859C: addiu       $s0, $s0, 0x48E0
    ctx->r16 = ADD32(ctx->r16, 0X48E0);
    // 0x802C85A0: addiu       $s1, $s1, -0x4D68
    ctx->r17 = ADD32(ctx->r17, -0X4D68);
    // 0x802C85A4: addiu       $a2, $a2, -0x5640
    ctx->r6 = ADD32(ctx->r6, -0X5640);
    // 0x802C85A8: addiu       $a3, $a3, -0x5638
    ctx->r7 = ADD32(ctx->r7, -0X5638);
    // 0x802C85AC: addiu       $ra, $zero, 0x1718
    ctx->r31 = ADD32(0, 0X1718);
    // 0x802C85B0: addiu       $t1, $zero, 0xE
    ctx->r9 = ADD32(0, 0XE);
L_802C85B4:
    // 0x802C85B4: lw          $t7, 0x0($a3)
    ctx->r15 = MEM_W(ctx->r7, 0X0);
    // 0x802C85B8: sll         $t9, $v1, 3
    ctx->r25 = S32(ctx->r3 << 3);
    // 0x802C85BC: subu        $t9, $t9, $v1
    ctx->r25 = SUB32(ctx->r25, ctx->r3);
    // 0x802C85C0: bnel        $t7, $zero, L_802C85F0
    if (ctx->r15 != 0) {
        // 0x802C85C4: lw          $t7, 0x0($a2)
        ctx->r15 = MEM_W(ctx->r6, 0X0);
            goto L_802C85F0;
    }
    goto skip_0;
    // 0x802C85C4: lw          $t7, 0x0($a2)
    ctx->r15 = MEM_W(ctx->r6, 0X0);
    skip_0:
    // 0x802C85C8: lw          $t8, 0x0($a2)
    ctx->r24 = MEM_W(ctx->r6, 0X0);
    // 0x802C85CC: sll         $t9, $t8, 2
    ctx->r25 = S32(ctx->r24 << 2);
    // 0x802C85D0: addu        $t6, $t0, $t9
    ctx->r14 = ADD32(ctx->r8, ctx->r25);
    // 0x802C85D4: lw          $t7, 0x0($t6)
    ctx->r15 = MEM_W(ctx->r14, 0X0);
    // 0x802C85D8: multu       $t7, $t1
    result = U64(U32(ctx->r15)) * U64(U32(ctx->r9)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x802C85DC: mflo        $t8
    ctx->r24 = lo;
    // 0x802C85E0: addu        $a0, $t3, $t8
    ctx->r4 = ADD32(ctx->r11, ctx->r24);
    // 0x802C85E4: b           L_802C8614
    // 0x802C85E8: nop

        goto L_802C8614;
    // 0x802C85E8: nop

    // 0x802C85EC: lw          $t7, 0x0($a2)
    ctx->r15 = MEM_W(ctx->r6, 0X0);
L_802C85F0:
    // 0x802C85F0: sll         $t9, $t9, 3
    ctx->r25 = S32(ctx->r25 << 3);
    // 0x802C85F4: addu        $t6, $s1, $t9
    ctx->r14 = ADD32(ctx->r17, ctx->r25);
    // 0x802C85F8: sll         $t8, $t7, 2
    ctx->r24 = S32(ctx->r15 << 2);
    // 0x802C85FC: addu        $t9, $t0, $t8
    ctx->r25 = ADD32(ctx->r8, ctx->r24);
    // 0x802C8600: lw          $t7, 0x0($t9)
    ctx->r15 = MEM_W(ctx->r25, 0X0);
    // 0x802C8604: multu       $t7, $t1
    result = U64(U32(ctx->r15)) * U64(U32(ctx->r9)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x802C8608: mflo        $t8
    ctx->r24 = lo;
    // 0x802C860C: addu        $a0, $t6, $t8
    ctx->r4 = ADD32(ctx->r14, ctx->r24);
    // 0x802C8610: nop

L_802C8614:
    // 0x802C8614: bnel        $v1, $zero, L_802C8628
    if (ctx->r3 != 0) {
        // 0x802C8618: lw          $a1, 0x0($s0)
        ctx->r5 = MEM_W(ctx->r16, 0X0);
            goto L_802C8628;
    }
    goto skip_1;
    // 0x802C8618: lw          $a1, 0x0($s0)
    ctx->r5 = MEM_W(ctx->r16, 0X0);
    skip_1:
    // 0x802C861C: b           L_802C8628
    // 0x802C8620: lw          $a1, 0x0($t4)
    ctx->r5 = MEM_W(ctx->r12, 0X0);
        goto L_802C8628;
    // 0x802C8620: lw          $a1, 0x0($t4)
    ctx->r5 = MEM_W(ctx->r12, 0X0);
    // 0x802C8624: lw          $a1, 0x0($s0)
    ctx->r5 = MEM_W(ctx->r16, 0X0);
L_802C8628:
    // 0x802C8628: multu       $a1, $ra
    result = U64(U32(ctx->r5)) * U64(U32(ctx->r31)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x802C862C: lb          $t7, 0xB($a0)
    ctx->r15 = MEM_B(ctx->r4, 0XB);
    // 0x802C8630: addiu       $v1, $v1, 0x1
    ctx->r3 = ADD32(ctx->r3, 0X1);
    // 0x802C8634: slt         $at, $v1, $t2
    ctx->r1 = SIGNED(ctx->r3) < SIGNED(ctx->r10) ? 1 : 0;
    // 0x802C8638: addiu       $a3, $a3, 0x4
    ctx->r7 = ADD32(ctx->r7, 0X4);
    // 0x802C863C: addiu       $a2, $a2, 0x4
    ctx->r6 = ADD32(ctx->r6, 0X4);
    // 0x802C8640: mflo        $t9
    ctx->r25 = lo;
    // 0x802C8644: addu        $v0, $t5, $t9
    ctx->r2 = ADD32(ctx->r13, ctx->r25);
    // 0x802C8648: sw          $t7, 0xB6C($v0)
    MEM_W(0XB6C, ctx->r2) = ctx->r15;
    // 0x802C864C: lb          $t6, 0xC($a0)
    ctx->r14 = MEM_B(ctx->r4, 0XC);
    // 0x802C8650: sw          $t6, 0xB70($v0)
    MEM_W(0XB70, ctx->r2) = ctx->r14;
    // 0x802C8654: lb          $t8, 0xD($a0)
    ctx->r24 = MEM_B(ctx->r4, 0XD);
    // 0x802C8658: bne         $at, $zero, L_802C85B4
    if (ctx->r1 != 0) {
        // 0x802C865C: sw          $t8, 0xB74($v0)
        MEM_W(0XB74, ctx->r2) = ctx->r24;
            goto L_802C85B4;
    }
    // 0x802C865C: sw          $t8, 0xB74($v0)
    MEM_W(0XB74, ctx->r2) = ctx->r24;
L_802C8660:
    // 0x802C8660: lui         $t9, 0x801D
    ctx->r25 = S32(0X801D << 16);
    // 0x802C8664: lw          $t9, -0x19F8($t9)
    ctx->r25 = MEM_W(ctx->r25, -0X19F8);
    // 0x802C8668: addiu       $at, $zero, 0x4
    ctx->r1 = ADD32(0, 0X4);
    // 0x802C866C: lui         $t7, 0x801D
    ctx->r15 = S32(0X801D << 16);
    // 0x802C8670: bne         $t9, $at, L_802C869C
    if (ctx->r25 != ctx->r1) {
        // 0x802C8674: addiu       $a0, $zero, 0x1
        ctx->r4 = ADD32(0, 0X1);
            goto L_802C869C;
    }
    // 0x802C8674: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    // 0x802C8678: lw          $t7, -0x19D0($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X19D0);
    // 0x802C867C: addiu       $at, $zero, 0x1E
    ctx->r1 = ADD32(0, 0X1E);
    // 0x802C8680: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C8684: bne         $t7, $at, L_802C869C
    if (ctx->r15 != ctx->r1) {
        // 0x802C8688: or          $a2, $zero, $zero
        ctx->r6 = 0 | 0;
            goto L_802C869C;
    }
    // 0x802C8688: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x802C868C: jal         0x801E6FB0
    // 0x802C8690: addiu       $a0, $zero, 0x5
    ctx->r4 = ADD32(0, 0X5);
    FadeTransition_SetProps(rdram, ctx);
        goto after_0;
    // 0x802C8690: addiu       $a0, $zero, 0x5
    ctx->r4 = ADD32(0, 0X5);
    after_0:
    // 0x802C8694: b           L_802C86AC
    // 0x802C8698: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
        goto L_802C86AC;
    // 0x802C8698: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
L_802C869C:
    // 0x802C869C: addiu       $a1, $zero, 0x4
    ctx->r5 = ADD32(0, 0X4);
    // 0x802C86A0: jal         0x801E6FB0
    // 0x802C86A4: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    FadeTransition_SetProps(rdram, ctx);
        goto after_1;
    // 0x802C86A4: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    after_1:
    // 0x802C86A8: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
L_802C86AC:
    // 0x802C86AC: jal         0x801E6A4C
    // 0x802C86B0: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_801E6A4C(rdram, ctx);
        goto after_2;
    // 0x802C86B0: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_2:
    // 0x802C86B4: lui         $t6, 0x801D
    ctx->r14 = S32(0X801D << 16);
    // 0x802C86B8: lw          $t6, -0x19D0($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X19D0);
    // 0x802C86BC: addiu       $at, $zero, 0x1E
    ctx->r1 = ADD32(0, 0X1E);
    // 0x802C86C0: bnel        $t6, $at, L_802C86D4
    if (ctx->r14 != ctx->r1) {
        // 0x802C86C4: lw          $ra, 0x1C($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X1C);
            goto L_802C86D4;
    }
    goto skip_2;
    // 0x802C86C4: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    skip_2:
    // 0x802C86C8: jal         0x800C1F60
    // 0x802C86CC: addiu       $a0, $zero, 0x2
    ctx->r4 = ADD32(0, 0X2);
    func_800C1F60(rdram, ctx);
        goto after_3;
    // 0x802C86CC: addiu       $a0, $zero, 0x2
    ctx->r4 = ADD32(0, 0X2);
    after_3:
    // 0x802C86D0: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
L_802C86D4:
    // 0x802C86D4: lw          $s0, 0x14($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X14);
    // 0x802C86D8: lw          $s1, 0x18($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X18);
    // 0x802C86DC: jr          $ra
    // 0x802C86E0: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    return;
    // 0x802C86E0: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
;}
RECOMP_FUNC void func_i2_802C86E4(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C86E4: addiu       $sp, $sp, -0x30
    ctx->r29 = ADD32(ctx->r29, -0X30);
    // 0x802C86E8: sw          $s1, 0xC($sp)
    MEM_W(0XC, ctx->r29) = ctx->r17;
    // 0x802C86EC: addiu       $s1, $a1, 0x8A
    ctx->r17 = ADD32(ctx->r5, 0X8A);
    // 0x802C86F0: sll         $t6, $s1, 2
    ctx->r14 = S32(ctx->r17 << 2);
    // 0x802C86F4: sw          $s2, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r18;
    // 0x802C86F8: andi        $t7, $t6, 0xFFF
    ctx->r15 = ctx->r14 & 0XFFF;
    // 0x802C86FC: addiu       $s2, $a1, 0x8
    ctx->r18 = ADD32(ctx->r5, 0X8);
    // 0x802C8700: sw          $ra, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r31;
    // 0x802C8704: sw          $s6, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r22;
    // 0x802C8708: sw          $s5, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r21;
    // 0x802C870C: sw          $s4, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r20;
    // 0x802C8710: sw          $s0, 0x8($sp)
    MEM_W(0X8, ctx->r29) = ctx->r16;
    // 0x802C8714: sll         $t6, $s2, 2
    ctx->r14 = S32(ctx->r18 << 2);
    // 0x802C8718: sll         $t8, $t7, 12
    ctx->r24 = S32(ctx->r15 << 12);
    // 0x802C871C: sw          $fp, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r30;
    // 0x802C8720: sw          $s7, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r23;
    // 0x802C8724: sw          $s3, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r19;
    // 0x802C8728: andi        $t7, $t6, 0xFFF
    ctx->r15 = ctx->r14 & 0XFFF;
    // 0x802C872C: lui         $s0, 0xF510
    ctx->r16 = S32(0XF510 << 16);
    // 0x802C8730: lui         $s4, 0xFD10
    ctx->r20 = S32(0XFD10 << 16);
    // 0x802C8734: lui         $s5, 0x80B
    ctx->r21 = S32(0X80B << 16);
    // 0x802C8738: lui         $s6, 0x708
    ctx->r22 = S32(0X708 << 16);
    // 0x802C873C: lui         $ra, 0x720
    ctx->r31 = S32(0X720 << 16);
    // 0x802C8740: lui         $at, 0xE400
    ctx->r1 = S32(0XE400 << 16);
    // 0x802C8744: or          $s1, $t8, $at
    ctx->r17 = ctx->r24 | ctx->r1;
    // 0x802C8748: ori         $ra, $ra, 0x4000
    ctx->r31 = ctx->r31 | 0X4000;
    // 0x802C874C: ori         $s6, $s6, 0x200
    ctx->r22 = ctx->r22 | 0X200;
    // 0x802C8750: addiu       $s5, $s5, 0x8
    ctx->r21 = ADD32(ctx->r21, 0X8);
    // 0x802C8754: ori         $s4, $s4, 0x81
    ctx->r20 = ctx->r20 | 0X81;
    // 0x802C8758: ori         $s0, $s0, 0x4200
    ctx->r16 = ctx->r16 | 0X4200;
    // 0x802C875C: sll         $s2, $t7, 12
    ctx->r18 = S32(ctx->r15 << 12);
    // 0x802C8760: addiu       $s3, $zero, 0x5A
    ctx->r19 = ADD32(0, 0X5A);
    // 0x802C8764: lui         $s7, 0xE600
    ctx->r23 = S32(0XE600 << 16);
    // 0x802C8768: lui         $fp, 0xF400
    ctx->r30 = S32(0XF400 << 16);
    // 0x802C876C: or          $t4, $zero, $zero
    ctx->r12 = 0 | 0;
    // 0x802C8770: or          $t2, $zero, $zero
    ctx->r10 = 0 | 0;
    // 0x802C8774: or          $t3, $a2, $zero
    ctx->r11 = ctx->r6 | 0;
    // 0x802C8778: addiu       $t5, $a2, 0x14
    ctx->r13 = ADD32(ctx->r6, 0X14);
L_802C877C:
    // 0x802C877C: beq         $t2, $s3, L_802C878C
    if (ctx->r10 == ctx->r19) {
        // 0x802C8780: or          $v0, $a0, $zero
        ctx->r2 = ctx->r4 | 0;
            goto L_802C878C;
    }
    // 0x802C8780: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x802C8784: b           L_802C8790
    // 0x802C8788: addiu       $a3, $zero, 0xF
    ctx->r7 = ADD32(0, 0XF);
        goto L_802C8790;
    // 0x802C8788: addiu       $a3, $zero, 0xF
    ctx->r7 = ADD32(0, 0XF);
L_802C878C:
    // 0x802C878C: addiu       $a3, $zero, 0x2
    ctx->r7 = ADD32(0, 0X2);
L_802C8790:
    // 0x802C8790: sll         $t9, $t4, 1
    ctx->r25 = S32(ctx->r12 << 1);
    // 0x802C8794: addu        $t6, $s5, $t9
    ctx->r14 = ADD32(ctx->r21, ctx->r25);
    // 0x802C8798: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C879C: or          $v1, $a0, $zero
    ctx->r3 = ctx->r4 | 0;
    // 0x802C87A0: sw          $t6, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r14;
    // 0x802C87A4: sw          $s4, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r20;
    // 0x802C87A8: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C87AC: or          $a1, $a0, $zero
    ctx->r5 = ctx->r4 | 0;
    // 0x802C87B0: sw          $s6, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r22;
    // 0x802C87B4: sw          $s0, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r16;
    // 0x802C87B8: addiu       $t0, $a3, -0x1
    ctx->r8 = ADD32(ctx->r7, -0X1);
    // 0x802C87BC: sll         $t7, $t0, 2
    ctx->r15 = S32(ctx->r8 << 2);
    // 0x802C87C0: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C87C4: or          $a2, $a0, $zero
    ctx->r6 = ctx->r4 | 0;
    // 0x802C87C8: andi        $t0, $t7, 0xFFF
    ctx->r8 = ctx->r15 & 0XFFF;
    // 0x802C87CC: or          $t9, $t0, $ra
    ctx->r25 = ctx->r8 | ctx->r31;
    // 0x802C87D0: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C87D4: sw          $zero, 0x4($a1)
    MEM_W(0X4, ctx->r5) = 0;
    // 0x802C87D8: sw          $s7, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r23;
    // 0x802C87DC: sw          $t9, 0x4($a2)
    MEM_W(0X4, ctx->r6) = ctx->r25;
    // 0x802C87E0: or          $t1, $a0, $zero
    ctx->r9 = ctx->r4 | 0;
    // 0x802C87E4: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C87E8: sw          $fp, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r30;
    // 0x802C87EC: lui         $t6, 0xE700
    ctx->r14 = S32(0XE700 << 16);
    // 0x802C87F0: sw          $t6, 0x0($t1)
    MEM_W(0X0, ctx->r9) = ctx->r14;
    // 0x802C87F4: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x802C87F8: lui         $t7, 0x8
    ctx->r15 = S32(0X8 << 16);
    // 0x802C87FC: ori         $t7, $t7, 0x200
    ctx->r15 = ctx->r15 | 0X200;
    // 0x802C8800: sw          $zero, 0x4($t1)
    MEM_W(0X4, ctx->r9) = 0;
    // 0x802C8804: sw          $t7, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r15;
    // 0x802C8808: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C880C: lui         $at, 0x20
    ctx->r1 = S32(0X20 << 16);
    // 0x802C8810: ori         $at, $at, 0x4000
    ctx->r1 = ctx->r1 | 0X4000;
    // 0x802C8814: or          $v1, $a0, $zero
    ctx->r3 = ctx->r4 | 0;
    // 0x802C8818: sw          $s0, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r16;
    // 0x802C881C: lui         $t8, 0xF200
    ctx->r24 = S32(0XF200 << 16);
    // 0x802C8820: addu        $t6, $t3, $a3
    ctx->r14 = ADD32(ctx->r11, ctx->r7);
    // 0x802C8824: sw          $t8, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r24;
    // 0x802C8828: or          $t9, $t0, $at
    ctx->r25 = ctx->r8 | ctx->r1;
    // 0x802C882C: addiu       $t7, $t6, 0x14
    ctx->r15 = ADD32(ctx->r14, 0X14);
    // 0x802C8830: sw          $t9, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r25;
    // 0x802C8834: sll         $t8, $t7, 2
    ctx->r24 = S32(ctx->r15 << 2);
    // 0x802C8838: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C883C: andi        $t9, $t8, 0xFFF
    ctx->r25 = ctx->r24 & 0XFFF;
    // 0x802C8840: or          $t6, $s1, $t9
    ctx->r14 = ctx->r17 | ctx->r25;
    // 0x802C8844: or          $a1, $a0, $zero
    ctx->r5 = ctx->r4 | 0;
    // 0x802C8848: sll         $t7, $t5, 2
    ctx->r15 = S32(ctx->r13 << 2);
    // 0x802C884C: andi        $t8, $t7, 0xFFF
    ctx->r24 = ctx->r15 & 0XFFF;
    // 0x802C8850: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C8854: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x802C8858: or          $t9, $s2, $t8
    ctx->r25 = ctx->r18 | ctx->r24;
    // 0x802C885C: sw          $t6, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r14;
    // 0x802C8860: sw          $t9, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r25;
    // 0x802C8864: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C8868: or          $v1, $a0, $zero
    ctx->r3 = ctx->r4 | 0;
    // 0x802C886C: lui         $t6, 0xB300
    ctx->r14 = S32(0XB300 << 16);
    // 0x802C8870: lui         $t8, 0x400
    ctx->r24 = S32(0X400 << 16);
    // 0x802C8874: addiu       $at, $zero, 0x69
    ctx->r1 = ADD32(0, 0X69);
    // 0x802C8878: addiu       $t2, $t2, 0xF
    ctx->r10 = ADD32(ctx->r10, 0XF);
    // 0x802C887C: ori         $t8, $t8, 0x400
    ctx->r24 = ctx->r24 | 0X400;
    // 0x802C8880: sw          $t6, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r14;
    // 0x802C8884: sw          $zero, 0x4($v0)
    MEM_W(0X4, ctx->r2) = 0;
    // 0x802C8888: lui         $t7, 0xB200
    ctx->r15 = S32(0XB200 << 16);
    // 0x802C888C: addiu       $t5, $t5, 0xF
    ctx->r13 = ADD32(ctx->r13, 0XF);
    // 0x802C8890: addiu       $t3, $t3, 0xF
    ctx->r11 = ADD32(ctx->r11, 0XF);
    // 0x802C8894: addiu       $t4, $t4, 0x79E
    ctx->r12 = ADD32(ctx->r12, 0X79E);
    // 0x802C8898: sw          $t7, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r15;
    // 0x802C889C: sw          $t8, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r24;
    // 0x802C88A0: bne         $t2, $at, L_802C877C
    if (ctx->r10 != ctx->r1) {
        // 0x802C88A4: addiu       $a0, $a0, 0x8
        ctx->r4 = ADD32(ctx->r4, 0X8);
            goto L_802C877C;
    }
    // 0x802C88A4: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C88A8: lw          $ra, 0x2C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X2C);
    // 0x802C88AC: lw          $s0, 0x8($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X8);
    // 0x802C88B0: lw          $s1, 0xC($sp)
    ctx->r17 = MEM_W(ctx->r29, 0XC);
    // 0x802C88B4: lw          $s2, 0x10($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X10);
    // 0x802C88B8: lw          $s3, 0x14($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X14);
    // 0x802C88BC: lw          $s4, 0x18($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X18);
    // 0x802C88C0: lw          $s5, 0x1C($sp)
    ctx->r21 = MEM_W(ctx->r29, 0X1C);
    // 0x802C88C4: lw          $s6, 0x20($sp)
    ctx->r22 = MEM_W(ctx->r29, 0X20);
    // 0x802C88C8: lw          $s7, 0x24($sp)
    ctx->r23 = MEM_W(ctx->r29, 0X24);
    // 0x802C88CC: lw          $fp, 0x28($sp)
    ctx->r30 = MEM_W(ctx->r29, 0X28);
    // 0x802C88D0: addiu       $sp, $sp, 0x30
    ctx->r29 = ADD32(ctx->r29, 0X30);
    // 0x802C88D4: jr          $ra
    // 0x802C88D8: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    return;
    // 0x802C88D8: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
;}
RECOMP_FUNC void func_i2_802C88DC(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C88DC: addiu       $sp, $sp, -0x78
    ctx->r29 = ADD32(ctx->r29, -0X78);
    // 0x802C88E0: sw          $s3, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r19;
    // 0x802C88E4: sw          $ra, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r31;
    // 0x802C88E8: sw          $fp, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r30;
    // 0x802C88EC: sw          $s4, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r20;
    // 0x802C88F0: sw          $s2, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r18;
    // 0x802C88F4: sw          $s1, 0xC($sp)
    MEM_W(0XC, ctx->r29) = ctx->r17;
    // 0x802C88F8: sw          $s0, 0x8($sp)
    MEM_W(0X8, ctx->r29) = ctx->r16;
    // 0x802C88FC: lui         $s3, 0x400
    ctx->r19 = S32(0X400 << 16);
    // 0x802C8900: sw          $s7, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r23;
    // 0x802C8904: sw          $s6, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r22;
    // 0x802C8908: sw          $s5, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r21;
    // 0x802C890C: or          $a3, $a0, $zero
    ctx->r7 = ctx->r4 | 0;
    // 0x802C8910: ori         $s3, $s3, 0x400
    ctx->r19 = ctx->r19 | 0X400;
    // 0x802C8914: lui         $s0, 0xE400
    ctx->r16 = S32(0XE400 << 16);
    // 0x802C8918: lui         $s1, 0xB300
    ctx->r17 = S32(0XB300 << 16);
    // 0x802C891C: lui         $s2, 0xB200
    ctx->r18 = S32(0XB200 << 16);
    // 0x802C8920: addiu       $s4, $zero, 0x240
    ctx->r20 = ADD32(0, 0X240);
    // 0x802C8924: addiu       $fp, $zero, 0x120
    ctx->r30 = ADD32(0, 0X120);
    // 0x802C8928: or          $ra, $zero, $zero
    ctx->r31 = 0 | 0;
    // 0x802C892C: sw          $zero, 0x34($sp)
    MEM_W(0X34, ctx->r29) = 0;
L_802C8930:
    // 0x802C8930: addiu       $at, $zero, 0x5F
    ctx->r1 = ADD32(0, 0X5F);
    // 0x802C8934: bne         $ra, $at, L_802C8944
    if (ctx->r31 != ctx->r1) {
        // 0x802C8938: or          $v0, $a3, $zero
        ctx->r2 = ctx->r7 | 0;
            goto L_802C8944;
    }
    // 0x802C8938: or          $v0, $a3, $zero
    ctx->r2 = ctx->r7 | 0;
    // 0x802C893C: b           L_802C8948
    // 0x802C8940: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
        goto L_802C8948;
    // 0x802C8940: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
L_802C8944:
    // 0x802C8944: addiu       $a2, $zero, 0x5
    ctx->r6 = ADD32(0, 0X5);
L_802C8948:
    // 0x802C8948: lui         $t6, 0xFD10
    ctx->r14 = S32(0XFD10 << 16);
    // 0x802C894C: sw          $t6, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r14;
    // 0x802C8950: lw          $t7, 0x34($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X34);
    // 0x802C8954: lui         $t9, 0x80B
    ctx->r25 = S32(0X80B << 16);
    // 0x802C8958: addiu       $t9, $t9, 0x77A0
    ctx->r25 = ADD32(ctx->r25, 0X77A0);
    // 0x802C895C: sll         $t8, $t7, 1
    ctx->r24 = S32(ctx->r15 << 1);
    // 0x802C8960: addu        $t6, $t8, $t9
    ctx->r14 = ADD32(ctx->r24, ctx->r25);
    // 0x802C8964: addiu       $a3, $a3, 0x8
    ctx->r7 = ADD32(ctx->r7, 0X8);
    // 0x802C8968: or          $v1, $a3, $zero
    ctx->r3 = ctx->r7 | 0;
    // 0x802C896C: sw          $t6, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r14;
    // 0x802C8970: addiu       $a3, $a3, 0x8
    ctx->r7 = ADD32(ctx->r7, 0X8);
    // 0x802C8974: lui         $t8, 0x708
    ctx->r24 = S32(0X708 << 16);
    // 0x802C8978: sll         $a1, $a2, 2
    ctx->r5 = S32(ctx->r6 << 2);
    // 0x802C897C: subu        $a1, $a1, $a2
    ctx->r5 = SUB32(ctx->r5, ctx->r6);
    // 0x802C8980: ori         $t8, $t8, 0x200
    ctx->r24 = ctx->r24 | 0X200;
    // 0x802C8984: or          $a0, $a3, $zero
    ctx->r4 = ctx->r7 | 0;
    // 0x802C8988: lui         $t7, 0xF510
    ctx->r15 = S32(0XF510 << 16);
    // 0x802C898C: sw          $t7, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r15;
    // 0x802C8990: sw          $t8, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r24;
    // 0x802C8994: sll         $a1, $a1, 5
    ctx->r5 = S32(ctx->r5 << 5);
    // 0x802C8998: addiu       $a1, $a1, -0x1
    ctx->r5 = ADD32(ctx->r5, -0X1);
    // 0x802C899C: addiu       $a3, $a3, 0x8
    ctx->r7 = ADD32(ctx->r7, 0X8);
    // 0x802C89A0: lui         $t9, 0xE600
    ctx->r25 = S32(0XE600 << 16);
    // 0x802C89A4: sw          $t9, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r25;
    // 0x802C89A8: or          $t0, $a3, $zero
    ctx->r8 = ctx->r7 | 0;
    // 0x802C89AC: slti        $at, $a1, 0x7FF
    ctx->r1 = SIGNED(ctx->r5) < 0X7FF ? 1 : 0;
    // 0x802C89B0: sw          $zero, 0x4($a0)
    MEM_W(0X4, ctx->r4) = 0;
    // 0x802C89B4: lui         $t6, 0xF300
    ctx->r14 = S32(0XF300 << 16);
    // 0x802C89B8: sw          $t6, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r14;
    // 0x802C89BC: beq         $at, $zero, L_802C89CC
    if (ctx->r1 == 0) {
        // 0x802C89C0: addiu       $a3, $a3, 0x8
        ctx->r7 = ADD32(ctx->r7, 0X8);
            goto L_802C89CC;
    }
    // 0x802C89C0: addiu       $a3, $a3, 0x8
    ctx->r7 = ADD32(ctx->r7, 0X8);
    // 0x802C89C4: b           L_802C89D0
    // 0x802C89C8: or          $v1, $a1, $zero
    ctx->r3 = ctx->r5 | 0;
        goto L_802C89D0;
    // 0x802C89C8: or          $v1, $a1, $zero
    ctx->r3 = ctx->r5 | 0;
L_802C89CC:
    // 0x802C89CC: addiu       $v1, $zero, 0x7FF
    ctx->r3 = ADD32(0, 0X7FF);
L_802C89D0:
    // 0x802C89D0: andi        $t7, $v1, 0xFFF
    ctx->r15 = ctx->r3 & 0XFFF;
    // 0x802C89D4: sll         $t8, $t7, 12
    ctx->r24 = S32(ctx->r15 << 12);
    // 0x802C89D8: lui         $at, 0x700
    ctx->r1 = S32(0X700 << 16);
    // 0x802C89DC: or          $t9, $t8, $at
    ctx->r25 = ctx->r24 | ctx->r1;
    // 0x802C89E0: ori         $t6, $t9, 0x56
    ctx->r14 = ctx->r25 | 0X56;
    // 0x802C89E4: or          $v0, $a3, $zero
    ctx->r2 = ctx->r7 | 0;
    // 0x802C89E8: addiu       $a3, $a3, 0x8
    ctx->r7 = ADD32(ctx->r7, 0X8);
    // 0x802C89EC: sw          $t6, 0x4($t0)
    MEM_W(0X4, ctx->r8) = ctx->r14;
    // 0x802C89F0: lui         $t7, 0xE700
    ctx->r15 = S32(0XE700 << 16);
    // 0x802C89F4: sw          $t7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r15;
    // 0x802C89F8: or          $a0, $a3, $zero
    ctx->r4 = ctx->r7 | 0;
    // 0x802C89FC: sw          $zero, 0x4($v0)
    MEM_W(0X4, ctx->r2) = 0;
    // 0x802C8A00: lui         $t9, 0x8
    ctx->r25 = S32(0X8 << 16);
    // 0x802C8A04: lui         $t8, 0xF510
    ctx->r24 = S32(0XF510 << 16);
    // 0x802C8A08: ori         $t8, $t8, 0x3000
    ctx->r24 = ctx->r24 | 0X3000;
    // 0x802C8A0C: ori         $t9, $t9, 0x200
    ctx->r25 = ctx->r25 | 0X200;
    // 0x802C8A10: sw          $t9, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r25;
    // 0x802C8A14: sw          $t8, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r24;
    // 0x802C8A18: addiu       $a3, $a3, 0x8
    ctx->r7 = ADD32(ctx->r7, 0X8);
    // 0x802C8A1C: addiu       $t7, $a2, -0x1
    ctx->r15 = ADD32(ctx->r6, -0X1);
    // 0x802C8A20: sll         $t8, $t7, 2
    ctx->r24 = S32(ctx->r15 << 2);
    // 0x802C8A24: or          $a1, $a3, $zero
    ctx->r5 = ctx->r7 | 0;
    // 0x802C8A28: lui         $t6, 0xF200
    ctx->r14 = S32(0XF200 << 16);
    // 0x802C8A2C: lui         $at, 0x17
    ctx->r1 = S32(0X17 << 16);
    // 0x802C8A30: ori         $at, $at, 0xC000
    ctx->r1 = ctx->r1 | 0XC000;
    // 0x802C8A34: sw          $t6, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r14;
    // 0x802C8A38: andi        $t9, $t8, 0xFFF
    ctx->r25 = ctx->r24 & 0XFFF;
    // 0x802C8A3C: or          $t6, $t9, $at
    ctx->r14 = ctx->r25 | ctx->r1;
    // 0x802C8A40: sw          $t6, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r14;
    // 0x802C8A44: addiu       $a3, $a3, 0x8
    ctx->r7 = ADD32(ctx->r7, 0X8);
    // 0x802C8A48: or          $s6, $zero, $zero
    ctx->r22 = 0 | 0;
    // 0x802C8A4C: or          $s5, $ra, $zero
    ctx->r21 = ctx->r31 | 0;
    // 0x802C8A50: addu        $s7, $ra, $a2
    ctx->r23 = ADD32(ctx->r31, ctx->r6);
L_802C8A54:
    // 0x802C8A54: sll         $t3, $s5, 2
    ctx->r11 = S32(ctx->r21 << 2);
    // 0x802C8A58: sll         $t5, $t3, 10
    ctx->r13 = S32(ctx->r11 << 10);
    // 0x802C8A5C: sra         $t7, $t5, 7
    ctx->r15 = S32(SIGNED(ctx->r13) >> 7);
    // 0x802C8A60: or          $t5, $t7, $zero
    ctx->r13 = ctx->r15 | 0;
    // 0x802C8A64: or          $t2, $zero, $zero
    ctx->r10 = 0 | 0;
    // 0x802C8A68: addiu       $t1, $zero, 0x60
    ctx->r9 = ADD32(0, 0X60);
    // 0x802C8A6C: sll         $t4, $s7, 2
    ctx->r12 = S32(ctx->r23 << 2);
L_802C8A70:
    // 0x802C8A70: or          $t0, $a3, $zero
    ctx->r8 = ctx->r7 | 0;
    // 0x802C8A74: sll         $v0, $t1, 2
    ctx->r2 = S32(ctx->r9 << 2);
    // 0x802C8A78: blez        $v0, L_802C8A88
    if (SIGNED(ctx->r2) <= 0) {
        // 0x802C8A7C: addiu       $a3, $a3, 0x8
        ctx->r7 = ADD32(ctx->r7, 0X8);
            goto L_802C8A88;
    }
    // 0x802C8A7C: addiu       $a3, $a3, 0x8
    ctx->r7 = ADD32(ctx->r7, 0X8);
    // 0x802C8A80: b           L_802C8A8C
    // 0x802C8A84: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
        goto L_802C8A8C;
    // 0x802C8A84: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
L_802C8A88:
    // 0x802C8A88: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
L_802C8A8C:
    // 0x802C8A8C: blez        $t4, L_802C8A9C
    if (SIGNED(ctx->r12) <= 0) {
        // 0x802C8A90: andi        $t6, $a0, 0xFFF
        ctx->r14 = ctx->r4 & 0XFFF;
            goto L_802C8A9C;
    }
    // 0x802C8A90: andi        $t6, $a0, 0xFFF
    ctx->r14 = ctx->r4 & 0XFFF;
    // 0x802C8A94: b           L_802C8AA0
    // 0x802C8A98: or          $v1, $t4, $zero
    ctx->r3 = ctx->r12 | 0;
        goto L_802C8AA0;
    // 0x802C8A98: or          $v1, $t4, $zero
    ctx->r3 = ctx->r12 | 0;
L_802C8A9C:
    // 0x802C8A9C: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
L_802C8AA0:
    // 0x802C8AA0: andi        $t8, $v1, 0xFFF
    ctx->r24 = ctx->r3 & 0XFFF;
    // 0x802C8AA4: or          $t9, $t8, $s0
    ctx->r25 = ctx->r24 | ctx->r16;
    // 0x802C8AA8: sll         $t7, $t6, 12
    ctx->r15 = S32(ctx->r14 << 12);
    // 0x802C8AAC: or          $t8, $t9, $t7
    ctx->r24 = ctx->r25 | ctx->r15;
    // 0x802C8AB0: sll         $a1, $t2, 2
    ctx->r5 = S32(ctx->r10 << 2);
    // 0x802C8AB4: blez        $a1, L_802C8AC4
    if (SIGNED(ctx->r5) <= 0) {
        // 0x802C8AB8: sw          $t8, 0x0($t0)
        MEM_W(0X0, ctx->r8) = ctx->r24;
            goto L_802C8AC4;
    }
    // 0x802C8AB8: sw          $t8, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r24;
    // 0x802C8ABC: b           L_802C8AC8
    // 0x802C8AC0: or          $a0, $a1, $zero
    ctx->r4 = ctx->r5 | 0;
        goto L_802C8AC8;
    // 0x802C8AC0: or          $a0, $a1, $zero
    ctx->r4 = ctx->r5 | 0;
L_802C8AC4:
    // 0x802C8AC4: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
L_802C8AC8:
    // 0x802C8AC8: blez        $t3, L_802C8AD8
    if (SIGNED(ctx->r11) <= 0) {
        // 0x802C8ACC: andi        $t9, $a0, 0xFFF
        ctx->r25 = ctx->r4 & 0XFFF;
            goto L_802C8AD8;
    }
    // 0x802C8ACC: andi        $t9, $a0, 0xFFF
    ctx->r25 = ctx->r4 & 0XFFF;
    // 0x802C8AD0: b           L_802C8ADC
    // 0x802C8AD4: or          $v1, $t3, $zero
    ctx->r3 = ctx->r11 | 0;
        goto L_802C8ADC;
    // 0x802C8AD4: or          $v1, $t3, $zero
    ctx->r3 = ctx->r11 | 0;
L_802C8AD8:
    // 0x802C8AD8: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
L_802C8ADC:
    // 0x802C8ADC: andi        $t6, $v1, 0xFFF
    ctx->r14 = ctx->r3 & 0XFFF;
    // 0x802C8AE0: sll         $t7, $t9, 12
    ctx->r15 = S32(ctx->r25 << 12);
    // 0x802C8AE4: or          $t8, $t6, $t7
    ctx->r24 = ctx->r14 | ctx->r15;
    // 0x802C8AE8: sll         $v0, $a1, 10
    ctx->r2 = S32(ctx->r5 << 10);
    // 0x802C8AEC: sra         $t9, $v0, 7
    ctx->r25 = S32(SIGNED(ctx->r2) >> 7);
    // 0x802C8AF0: sw          $t8, 0x4($t0)
    MEM_W(0X4, ctx->r8) = ctx->r24;
    // 0x802C8AF4: or          $a2, $a3, $zero
    ctx->r6 = ctx->r7 | 0;
    // 0x802C8AF8: sw          $s1, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r17;
    // 0x802C8AFC: bgez        $t9, L_802C8B0C
    if (SIGNED(ctx->r25) >= 0) {
        // 0x802C8B00: addiu       $a3, $a3, 0x8
        ctx->r7 = ADD32(ctx->r7, 0X8);
            goto L_802C8B0C;
    }
    // 0x802C8B00: addiu       $a3, $a3, 0x8
    ctx->r7 = ADD32(ctx->r7, 0X8);
    // 0x802C8B04: b           L_802C8B10
    // 0x802C8B08: or          $a0, $t9, $zero
    ctx->r4 = ctx->r25 | 0;
        goto L_802C8B10;
    // 0x802C8B08: or          $a0, $t9, $zero
    ctx->r4 = ctx->r25 | 0;
L_802C8B0C:
    // 0x802C8B0C: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
L_802C8B10:
    // 0x802C8B10: bgez        $t5, L_802C8B20
    if (SIGNED(ctx->r13) >= 0) {
        // 0x802C8B14: negu        $t9, $a0
        ctx->r25 = SUB32(0, ctx->r4);
            goto L_802C8B20;
    }
    // 0x802C8B14: negu        $t9, $a0
    ctx->r25 = SUB32(0, ctx->r4);
    // 0x802C8B18: b           L_802C8B24
    // 0x802C8B1C: or          $v1, $t5, $zero
    ctx->r3 = ctx->r13 | 0;
        goto L_802C8B24;
    // 0x802C8B1C: or          $v1, $t5, $zero
    ctx->r3 = ctx->r13 | 0;
L_802C8B20:
    // 0x802C8B20: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
L_802C8B24:
    // 0x802C8B24: negu        $t6, $v1
    ctx->r14 = SUB32(0, ctx->r3);
    // 0x802C8B28: andi        $t7, $t6, 0xFFFF
    ctx->r15 = ctx->r14 & 0XFFFF;
    // 0x802C8B2C: sll         $t6, $t9, 16
    ctx->r14 = S32(ctx->r25 << 16);
    // 0x802C8B30: or          $t8, $t7, $t6
    ctx->r24 = ctx->r15 | ctx->r14;
    // 0x802C8B34: or          $v0, $a3, $zero
    ctx->r2 = ctx->r7 | 0;
    // 0x802C8B38: addiu       $t1, $t1, 0x60
    ctx->r9 = ADD32(ctx->r9, 0X60);
    // 0x802C8B3C: sw          $t8, 0x4($a2)
    MEM_W(0X4, ctx->r6) = ctx->r24;
    // 0x802C8B40: addiu       $t2, $t2, 0x60
    ctx->r10 = ADD32(ctx->r10, 0X60);
    // 0x802C8B44: sw          $s3, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r19;
    // 0x802C8B48: sw          $s2, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r18;
    // 0x802C8B4C: bne         $t1, $s4, L_802C8A70
    if (ctx->r9 != ctx->r20) {
        // 0x802C8B50: addiu       $a3, $a3, 0x8
        ctx->r7 = ADD32(ctx->r7, 0X8);
            goto L_802C8A70;
    }
    // 0x802C8B50: addiu       $a3, $a3, 0x8
    ctx->r7 = ADD32(ctx->r7, 0X8);
    // 0x802C8B54: addiu       $s6, $s6, 0x60
    ctx->r22 = ADD32(ctx->r22, 0X60);
    // 0x802C8B58: addiu       $s5, $s5, 0x60
    ctx->r21 = ADD32(ctx->r21, 0X60);
    // 0x802C8B5C: bne         $s6, $fp, L_802C8A54
    if (ctx->r22 != ctx->r30) {
        // 0x802C8B60: addiu       $s7, $s7, 0x60
        ctx->r23 = ADD32(ctx->r23, 0X60);
            goto L_802C8A54;
    }
    // 0x802C8B60: addiu       $s7, $s7, 0x60
    ctx->r23 = ADD32(ctx->r23, 0X60);
    // 0x802C8B64: lw          $t9, 0x34($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X34);
    // 0x802C8B68: addiu       $ra, $ra, 0x5
    ctx->r31 = ADD32(ctx->r31, 0X5);
    // 0x802C8B6C: addiu       $at, $zero, 0x64
    ctx->r1 = ADD32(0, 0X64);
    // 0x802C8B70: addiu       $t7, $t9, 0x1E0
    ctx->r15 = ADD32(ctx->r25, 0X1E0);
    // 0x802C8B74: bne         $ra, $at, L_802C8930
    if (ctx->r31 != ctx->r1) {
        // 0x802C8B78: sw          $t7, 0x34($sp)
        MEM_W(0X34, ctx->r29) = ctx->r15;
            goto L_802C8930;
    }
    // 0x802C8B78: sw          $t7, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r15;
    // 0x802C8B7C: lw          $ra, 0x2C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X2C);
    // 0x802C8B80: lw          $s0, 0x8($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X8);
    // 0x802C8B84: lw          $s1, 0xC($sp)
    ctx->r17 = MEM_W(ctx->r29, 0XC);
    // 0x802C8B88: lw          $s2, 0x10($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X10);
    // 0x802C8B8C: lw          $s3, 0x14($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X14);
    // 0x802C8B90: lw          $s4, 0x18($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X18);
    // 0x802C8B94: lw          $s5, 0x1C($sp)
    ctx->r21 = MEM_W(ctx->r29, 0X1C);
    // 0x802C8B98: lw          $s6, 0x20($sp)
    ctx->r22 = MEM_W(ctx->r29, 0X20);
    // 0x802C8B9C: lw          $s7, 0x24($sp)
    ctx->r23 = MEM_W(ctx->r29, 0X24);
    // 0x802C8BA0: lw          $fp, 0x28($sp)
    ctx->r30 = MEM_W(ctx->r29, 0X28);
    // 0x802C8BA4: addiu       $sp, $sp, 0x78
    ctx->r29 = ADD32(ctx->r29, 0X78);
    // 0x802C8BA8: jr          $ra
    // 0x802C8BAC: or          $v0, $a3, $zero
    ctx->r2 = ctx->r7 | 0;
    return;
    // 0x802C8BAC: or          $v0, $a3, $zero
    ctx->r2 = ctx->r7 | 0;
;}
RECOMP_FUNC void func_i3_802C5800(uint8_t* rdram, recomp_context* ctx) {
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
    // 0x802C5810: beq         $t6, $zero, L_802C5A9C
    if (ctx->r14 == 0) {
        // 0x802C5814: lui         $t7, 0x800E
        ctx->r15 = S32(0X800E << 16);
            goto L_802C5A9C;
    }
    // 0x802C5814: lui         $t7, 0x800E
    ctx->r15 = S32(0X800E << 16);
    // 0x802C5818: lw          $t7, -0x54DC($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X54DC);
    // 0x802C581C: addiu       $at, $zero, 0x1E
    ctx->r1 = ADD32(0, 0X1E);
    // 0x802C5820: lui         $a1, 0x801D
    ctx->r5 = S32(0X801D << 16);
    // 0x802C5824: bne         $t7, $at, L_802C5A9C
    if (ctx->r15 != ctx->r1) {
        // 0x802C5828: lui         $t1, 0x801D
        ctx->r9 = S32(0X801D << 16);
            goto L_802C5A9C;
    }
    // 0x802C5828: lui         $t1, 0x801D
    ctx->r9 = S32(0X801D << 16);
    // 0x802C582C: lw          $t1, -0x4CC8($t1)
    ctx->r9 = MEM_W(ctx->r9, -0X4CC8);
    // 0x802C5830: lui         $t9, 0x802C
    ctx->r25 = S32(0X802C << 16);
    // 0x802C5834: lw          $a1, -0x4CCC($a1)
    ctx->r5 = MEM_W(ctx->r5, -0X4CCC);
    // 0x802C5838: sll         $t8, $t1, 2
    ctx->r24 = S32(ctx->r9 << 2);
    // 0x802C583C: addu        $t9, $t9, $t8
    ctx->r25 = ADD32(ctx->r25, ctx->r24);
    // 0x802C5840: lw          $t9, 0x6FE4($t9)
    ctx->r25 = MEM_W(ctx->r25, 0X6FE4);
    // 0x802C5844: lui         $t3, 0x802C
    ctx->r11 = S32(0X802C << 16);
    // 0x802C5848: addiu       $t3, $t3, 0x7028
    ctx->r11 = ADD32(ctx->r11, 0X7028);
    // 0x802C584C: bne         $a1, $t9, L_802C58D0
    if (ctx->r5 != ctx->r25) {
        // 0x802C5850: addiu       $t4, $zero, 0x1
        ctx->r12 = ADD32(0, 0X1);
            goto L_802C58D0;
    }
    // 0x802C5850: addiu       $t4, $zero, 0x1
    ctx->r12 = ADD32(0, 0X1);
    // 0x802C5854: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x802C5858: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x802C585C: lui         $a0, 0x801D
    ctx->r4 = S32(0X801D << 16);
    // 0x802C5860: addiu       $a0, $a0, -0x4C30
    ctx->r4 = ADD32(ctx->r4, -0X4C30);
    // 0x802C5864: addiu       $v0, $v0, -0x4CB0
    ctx->r2 = ADD32(ctx->r2, -0X4CB0);
    // 0x802C5868: addiu       $v1, $v1, -0x4C30
    ctx->r3 = ADD32(ctx->r3, -0X4C30);
L_802C586C:
    // 0x802C586C: addiu       $v0, $v0, 0x10
    ctx->r2 = ADD32(ctx->r2, 0X10);
    // 0x802C5870: sltu        $at, $v0, $a0
    ctx->r1 = ctx->r2 < ctx->r4 ? 1 : 0;
    // 0x802C5874: addiu       $v1, $v1, 0x4
    ctx->r3 = ADD32(ctx->r3, 0X4);
    // 0x802C5878: sw          $zero, -0x10($v0)
    MEM_W(-0X10, ctx->r2) = 0;
    // 0x802C587C: sw          $zero, -0xC($v0)
    MEM_W(-0XC, ctx->r2) = 0;
    // 0x802C5880: sw          $zero, -0x8($v0)
    MEM_W(-0X8, ctx->r2) = 0;
    // 0x802C5884: sw          $zero, -0x4($v0)
    MEM_W(-0X4, ctx->r2) = 0;
    // 0x802C5888: bne         $at, $zero, L_802C586C
    if (ctx->r1 != 0) {
        // 0x802C588C: sw          $zero, -0x4($v1)
        MEM_W(-0X4, ctx->r3) = 0;
            goto L_802C586C;
    }
    // 0x802C588C: sw          $zero, -0x4($v1)
    MEM_W(-0X4, ctx->r3) = 0;
    // 0x802C5890: lui         $a2, 0x801D
    ctx->r6 = S32(0X801D << 16);
    // 0x802C5894: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x802C5898: addiu       $v0, $v0, -0x4CB0
    ctx->r2 = ADD32(ctx->r2, -0X4CB0);
    // 0x802C589C: addiu       $a2, $a2, -0x4CC0
    ctx->r6 = ADD32(ctx->r6, -0X4CC0);
L_802C58A0:
    // 0x802C58A0: addiu       $a2, $a2, 0x4
    ctx->r6 = ADD32(ctx->r6, 0X4);
    // 0x802C58A4: sltu        $at, $a2, $v0
    ctx->r1 = ctx->r6 < ctx->r2 ? 1 : 0;
    // 0x802C58A8: bne         $at, $zero, L_802C58A0
    if (ctx->r1 != 0) {
        // 0x802C58AC: sw          $zero, -0x4($a2)
        MEM_W(-0X4, ctx->r6) = 0;
            goto L_802C58A0;
    }
    // 0x802C58AC: sw          $zero, -0x4($a2)
    MEM_W(-0X4, ctx->r6) = 0;
    // 0x802C58B0: lui         $at, 0x801C
    ctx->r1 = S32(0X801C << 16);
    // 0x802C58B4: sw          $zero, 0x2C70($at)
    MEM_W(0X2C70, ctx->r1) = 0;
    // 0x802C58B8: lui         $at, 0x801C
    ctx->r1 = S32(0X801C << 16);
    // 0x802C58BC: sw          $zero, 0x2FE8($at)
    MEM_W(0X2FE8, ctx->r1) = 0;
    // 0x802C58C0: lui         $at, 0x801C
    ctx->r1 = S32(0X801C << 16);
    // 0x802C58C4: sw          $zero, 0x3360($at)
    MEM_W(0X3360, ctx->r1) = 0;
    // 0x802C58C8: lui         $at, 0x801C
    ctx->r1 = S32(0X801C << 16);
    // 0x802C58CC: sw          $zero, 0x36D8($at)
    MEM_W(0X36D8, ctx->r1) = 0;
L_802C58D0:
    // 0x802C58D0: sw          $t4, 0x0($t3)
    MEM_W(0X0, ctx->r11) = ctx->r12;
    // 0x802C58D4: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C58D8: bne         $t1, $zero, L_802C5908
    if (ctx->r9 != 0) {
        // 0x802C58DC: sw          $zero, 0x6F84($at)
        MEM_W(0X6F84, ctx->r1) = 0;
            goto L_802C5908;
    }
    // 0x802C58DC: sw          $zero, 0x6F84($at)
    MEM_W(0X6F84, ctx->r1) = 0;
    // 0x802C58E0: bne         $t4, $a1, L_802C58FC
    if (ctx->r12 != ctx->r5) {
        // 0x802C58E4: addiu       $t6, $zero, 0xB4
        ctx->r14 = ADD32(0, 0XB4);
            goto L_802C58FC;
    }
    // 0x802C58E4: addiu       $t6, $zero, 0xB4
    ctx->r14 = ADD32(0, 0XB4);
    // 0x802C58E8: sw          $zero, 0x0($t3)
    MEM_W(0X0, ctx->r11) = 0;
    // 0x802C58EC: addiu       $t5, $zero, 0xF0
    ctx->r13 = ADD32(0, 0XF0);
    // 0x802C58F0: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C58F4: b           L_802C592C
    // 0x802C58F8: sw          $t5, 0x702C($at)
    MEM_W(0X702C, ctx->r1) = ctx->r13;
        goto L_802C592C;
    // 0x802C58F8: sw          $t5, 0x702C($at)
    MEM_W(0X702C, ctx->r1) = ctx->r13;
L_802C58FC:
    // 0x802C58FC: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C5900: b           L_802C592C
    // 0x802C5904: sw          $t6, 0x702C($at)
    MEM_W(0X702C, ctx->r1) = ctx->r14;
        goto L_802C592C;
    // 0x802C5904: sw          $t6, 0x702C($at)
    MEM_W(0X702C, ctx->r1) = ctx->r14;
L_802C5908:
    // 0x802C5908: bne         $a1, $zero, L_802C5924
    if (ctx->r5 != 0) {
        // 0x802C590C: addiu       $t8, $zero, 0xB4
        ctx->r24 = ADD32(0, 0XB4);
            goto L_802C5924;
    }
    // 0x802C590C: addiu       $t8, $zero, 0xB4
    ctx->r24 = ADD32(0, 0XB4);
    // 0x802C5910: sw          $zero, 0x0($t3)
    MEM_W(0X0, ctx->r11) = 0;
    // 0x802C5914: addiu       $t7, $zero, 0xF0
    ctx->r15 = ADD32(0, 0XF0);
    // 0x802C5918: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C591C: b           L_802C592C
    // 0x802C5920: sw          $t7, 0x702C($at)
    MEM_W(0X702C, ctx->r1) = ctx->r15;
        goto L_802C592C;
    // 0x802C5920: sw          $t7, 0x702C($at)
    MEM_W(0X702C, ctx->r1) = ctx->r15;
L_802C5924:
    // 0x802C5924: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C5928: sw          $t8, 0x702C($at)
    MEM_W(0X702C, ctx->r1) = ctx->r24;
L_802C592C:
    // 0x802C592C: lui         $t9, 0x801D
    ctx->r25 = S32(0X801D << 16);
    // 0x802C5930: lw          $t9, -0x4CD0($t9)
    ctx->r25 = MEM_W(ctx->r25, -0X4CD0);
    // 0x802C5934: lui         $a2, 0x801D
    ctx->r6 = S32(0X801D << 16);
    // 0x802C5938: addiu       $a2, $a2, -0x4CC0
    ctx->r6 = ADD32(ctx->r6, -0X4CC0);
    // 0x802C593C: bne         $t9, $zero, L_802C59A4
    if (ctx->r25 != 0) {
        // 0x802C5940: lui         $a3, 0x801D
        ctx->r7 = S32(0X801D << 16);
            goto L_802C59A4;
    }
    // 0x802C5940: lui         $a3, 0x801D
    ctx->r7 = S32(0X801D << 16);
    // 0x802C5944: lui         $t1, 0x802C
    ctx->r9 = S32(0X802C << 16);
    // 0x802C5948: addiu       $t1, $t1, 0x7020
    ctx->r9 = ADD32(ctx->r9, 0X7020);
    // 0x802C594C: sw          $zero, 0x0($t1)
    MEM_W(0X0, ctx->r9) = 0;
    // 0x802C5950: addiu       $t5, $zero, 0x4
    ctx->r13 = ADD32(0, 0X4);
    // 0x802C5954: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C5958: sw          $t5, -0x18F8($at)
    MEM_W(-0X18F8, ctx->r1) = ctx->r13;
    // 0x802C595C: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C5960: addiu       $t6, $zero, 0x4
    ctx->r14 = ADD32(0, 0X4);
    // 0x802C5964: lui         $t9, 0x800D
    ctx->r25 = S32(0X800D << 16);
    // 0x802C5968: lw          $t9, 0x48DC($t9)
    ctx->r25 = MEM_W(ctx->r25, 0X48DC);
    // 0x802C596C: sw          $t6, -0x18F4($at)
    MEM_W(-0X18F4, ctx->r1) = ctx->r14;
    // 0x802C5970: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C5974: addiu       $t7, $zero, 0x4
    ctx->r15 = ADD32(0, 0X4);
    // 0x802C5978: sw          $t7, -0x18F0($at)
    MEM_W(-0X18F0, ctx->r1) = ctx->r15;
    // 0x802C597C: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C5980: addiu       $t8, $zero, 0x4
    ctx->r24 = ADD32(0, 0X4);
    // 0x802C5984: lui         $t6, 0x801D
    ctx->r14 = S32(0X801D << 16);
    // 0x802C5988: sll         $t5, $t9, 2
    ctx->r13 = S32(ctx->r25 << 2);
    // 0x802C598C: sw          $t8, -0x18EC($at)
    MEM_W(-0X18EC, ctx->r1) = ctx->r24;
    // 0x802C5990: addu        $t6, $t6, $t5
    ctx->r14 = ADD32(ctx->r14, ctx->r13);
    // 0x802C5994: lw          $t6, -0x18F8($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X18F8);
    // 0x802C5998: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C599C: b           L_802C5A3C
    // 0x802C59A0: sw          $t6, -0x18FC($at)
    MEM_W(-0X18FC, ctx->r1) = ctx->r14;
        goto L_802C5A3C;
    // 0x802C59A0: sw          $t6, -0x18FC($at)
    MEM_W(-0X18FC, ctx->r1) = ctx->r14;
L_802C59A4:
    // 0x802C59A4: sll         $t7, $t1, 4
    ctx->r15 = S32(ctx->r9 << 4);
    // 0x802C59A8: sll         $t8, $a1, 1
    ctx->r24 = S32(ctx->r5 << 1);
    // 0x802C59AC: addu        $t9, $t7, $t8
    ctx->r25 = ADD32(ctx->r15, ctx->r24);
    // 0x802C59B0: lui         $t0, 0x800F
    ctx->r8 = S32(0X800F << 16);
    // 0x802C59B4: addu        $t0, $t0, $t9
    ctx->r8 = ADD32(ctx->r8, ctx->r25);
    // 0x802C59B8: lui         $t1, 0x802C
    ctx->r9 = S32(0X802C << 16);
    // 0x802C59BC: lui         $t2, 0x801D
    ctx->r10 = S32(0X801D << 16);
    // 0x802C59C0: addiu       $t2, $t2, -0x18E8
    ctx->r10 = ADD32(ctx->r10, -0X18E8);
    // 0x802C59C4: addiu       $t1, $t1, 0x7020
    ctx->r9 = ADD32(ctx->r9, 0X7020);
    // 0x802C59C8: lh          $t0, -0x5444($t0)
    ctx->r8 = MEM_H(ctx->r8, -0X5444);
    // 0x802C59CC: addiu       $a1, $zero, 0x5
    ctx->r5 = ADD32(0, 0X5);
    // 0x802C59D0: addiu       $a3, $a3, -0x18F8
    ctx->r7 = ADD32(ctx->r7, -0X18F8);
L_802C59D4:
    // 0x802C59D4: lw          $t5, 0x0($a2)
    ctx->r13 = MEM_W(ctx->r6, 0X0);
    // 0x802C59D8: lui         $v0, 0x800F
    ctx->r2 = S32(0X800F << 16);
    // 0x802C59DC: addiu       $v0, $v0, -0x544E
    ctx->r2 = ADD32(ctx->r2, -0X544E);
    // 0x802C59E0: subu        $a0, $t0, $t5
    ctx->r4 = SUB32(ctx->r8, ctx->r13);
    // 0x802C59E4: sw          $a0, 0x0($t1)
    MEM_W(0X0, ctx->r9) = ctx->r4;
    // 0x802C59E8: or          $v1, $t4, $zero
    ctx->r3 = ctx->r12 | 0;
L_802C59EC:
    // 0x802C59EC: lh          $t7, 0x0($v0)
    ctx->r15 = MEM_H(ctx->r2, 0X0);
    // 0x802C59F0: slt         $at, $t7, $a0
    ctx->r1 = SIGNED(ctx->r15) < SIGNED(ctx->r4) ? 1 : 0;
    // 0x802C59F4: bnel        $at, $zero, L_802C5A0C
    if (ctx->r1 != 0) {
        // 0x802C59F8: addiu       $a3, $a3, 0x4
        ctx->r7 = ADD32(ctx->r7, 0X4);
            goto L_802C5A0C;
    }
    goto skip_0;
    // 0x802C59F8: addiu       $a3, $a3, 0x4
    ctx->r7 = ADD32(ctx->r7, 0X4);
    skip_0:
    // 0x802C59FC: addiu       $v1, $v1, 0x1
    ctx->r3 = ADD32(ctx->r3, 0X1);
    // 0x802C5A00: bne         $v1, $a1, L_802C59EC
    if (ctx->r3 != ctx->r5) {
        // 0x802C5A04: addiu       $v0, $v0, 0x2
        ctx->r2 = ADD32(ctx->r2, 0X2);
            goto L_802C59EC;
    }
    // 0x802C5A04: addiu       $v0, $v0, 0x2
    ctx->r2 = ADD32(ctx->r2, 0X2);
    // 0x802C5A08: addiu       $a3, $a3, 0x4
    ctx->r7 = ADD32(ctx->r7, 0X4);
L_802C5A0C:
    // 0x802C5A0C: addiu       $t8, $v1, -0x1
    ctx->r24 = ADD32(ctx->r3, -0X1);
    // 0x802C5A10: addiu       $a2, $a2, 0x4
    ctx->r6 = ADD32(ctx->r6, 0X4);
    // 0x802C5A14: bne         $a3, $t2, L_802C59D4
    if (ctx->r7 != ctx->r10) {
        // 0x802C5A18: sw          $t8, -0x4($a3)
        MEM_W(-0X4, ctx->r7) = ctx->r24;
            goto L_802C59D4;
    }
    // 0x802C5A18: sw          $t8, -0x4($a3)
    MEM_W(-0X4, ctx->r7) = ctx->r24;
    // 0x802C5A1C: lui         $t9, 0x800D
    ctx->r25 = S32(0X800D << 16);
    // 0x802C5A20: lw          $t9, 0x48DC($t9)
    ctx->r25 = MEM_W(ctx->r25, 0X48DC);
    // 0x802C5A24: lui         $t6, 0x801D
    ctx->r14 = S32(0X801D << 16);
    // 0x802C5A28: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C5A2C: sll         $t5, $t9, 2
    ctx->r13 = S32(ctx->r25 << 2);
    // 0x802C5A30: addu        $t6, $t6, $t5
    ctx->r14 = ADD32(ctx->r14, ctx->r13);
    // 0x802C5A34: lw          $t6, -0x18F8($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X18F8);
    // 0x802C5A38: sw          $t6, -0x18FC($at)
    MEM_W(-0X18FC, ctx->r1) = ctx->r14;
L_802C5A3C:
    // 0x802C5A3C: lui         $t7, 0x800E
    ctx->r15 = S32(0X800E << 16);
    // 0x802C5A40: lw          $t7, -0x7E90($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X7E90);
    // 0x802C5A44: lui         $a1, 0x800E
    ctx->r5 = S32(0X800E << 16);
    // 0x802C5A48: lui         $a0, 0x801A
    ctx->r4 = S32(0X801A << 16);
    // 0x802C5A4C: sll         $t8, $t7, 2
    ctx->r24 = S32(ctx->r15 << 2);
    // 0x802C5A50: addu        $a1, $a1, $t8
    ctx->r5 = ADD32(ctx->r5, ctx->r24);
    // 0x802C5A54: lw          $a1, -0x554C($a1)
    ctx->r5 = MEM_W(ctx->r5, -0X554C);
    // 0x802C5A58: jal         0x80069740
    // 0x802C5A5C: addiu       $a0, $a0, -0x7CF0
    ctx->r4 = ADD32(ctx->r4, -0X7CF0);
    func_80069740(rdram, ctx);
        goto after_0;
    // 0x802C5A5C: addiu       $a0, $a0, -0x7CF0
    ctx->r4 = ADD32(ctx->r4, -0X7CF0);
    after_0:
    // 0x802C5A60: lui         $a0, 0x801A
    ctx->r4 = S32(0X801A << 16);
    // 0x802C5A64: lui         $a1, 0x800F
    ctx->r5 = S32(0X800F << 16);
    // 0x802C5A68: addiu       $a1, $a1, -0x6550
    ctx->r5 = ADD32(ctx->r5, -0X6550);
    // 0x802C5A6C: jal         0x8006977C
    // 0x802C5A70: addiu       $a0, $a0, -0x7CB0
    ctx->r4 = ADD32(ctx->r4, -0X7CB0);
    func_8006977C(rdram, ctx);
        goto after_1;
    // 0x802C5A70: addiu       $a0, $a0, -0x7CB0
    ctx->r4 = ADD32(ctx->r4, -0X7CB0);
    after_1:
    // 0x802C5A74: lui         $t9, 0x800E
    ctx->r25 = S32(0X800E << 16);
    // 0x802C5A78: lh          $t9, -0x5498($t9)
    ctx->r25 = MEM_H(ctx->r25, -0X5498);
    // 0x802C5A7C: addiu       $t5, $zero, 0x2
    ctx->r13 = ADD32(0, 0X2);
    // 0x802C5A80: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C5A84: beq         $t9, $zero, L_802C5A98
    if (ctx->r25 == 0) {
        // 0x802C5A88: nop
    
            goto L_802C5A98;
    }
    // 0x802C5A88: nop

    // 0x802C5A8C: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C5A90: b           L_802C5A9C
    // 0x802C5A94: sw          $t5, 0x6F8C($at)
    MEM_W(0X6F8C, ctx->r1) = ctx->r13;
        goto L_802C5A9C;
    // 0x802C5A94: sw          $t5, 0x6F8C($at)
    MEM_W(0X6F8C, ctx->r1) = ctx->r13;
L_802C5A98:
    // 0x802C5A98: sw          $zero, 0x6F8C($at)
    MEM_W(0X6F8C, ctx->r1) = 0;
L_802C5A9C:
    // 0x802C5A9C: lui         $v0, 0x802C
    ctx->r2 = S32(0X802C << 16);
    // 0x802C5AA0: lw          $v0, 0x7028($v0)
    ctx->r2 = MEM_W(ctx->r2, 0X7028);
    // 0x802C5AA4: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x802C5AA8: beq         $v0, $zero, L_802C5AC0
    if (ctx->r2 == 0) {
        // 0x802C5AAC: nop
    
            goto L_802C5AC0;
    }
    // 0x802C5AAC: nop

    // 0x802C5AB0: beq         $v0, $at, L_802C5AD0
    if (ctx->r2 == ctx->r1) {
        // 0x802C5AB4: nop
    
            goto L_802C5AD0;
    }
    // 0x802C5AB4: nop

    // 0x802C5AB8: b           L_802C5ADC
    // 0x802C5ABC: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_802C5ADC;
    // 0x802C5ABC: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C5AC0:
    // 0x802C5AC0: jal         0x802C5AE8
    // 0x802C5AC4: nop

    func_i3_802C5AE8(rdram, ctx);
        goto after_2;
    // 0x802C5AC4: nop

    after_2:
    // 0x802C5AC8: b           L_802C5ADC
    // 0x802C5ACC: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_802C5ADC;
    // 0x802C5ACC: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C5AD0:
    // 0x802C5AD0: jal         0x802C5AF0
    // 0x802C5AD4: nop

    func_i3_802C5AF0(rdram, ctx);
        goto after_3;
    // 0x802C5AD4: nop

    after_3:
    // 0x802C5AD8: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C5ADC:
    // 0x802C5ADC: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x802C5AE0: jr          $ra
    // 0x802C5AE4: nop

    return;
    // 0x802C5AE4: nop

;}
RECOMP_FUNC void func_i3_802C5AE8(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C5AE8: jr          $ra
    // 0x802C5AEC: nop

    return;
    // 0x802C5AEC: nop

;}
RECOMP_FUNC void func_i3_802C5AF0(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C5AF0: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x802C5AF4: lw          $v0, -0x1A08($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X1A08);
    // 0x802C5AF8: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x802C5AFC: lui         $t6, 0x801A
    ctx->r14 = S32(0X801A << 16);
    // 0x802C5B00: lui         $t7, 0x801A
    ctx->r15 = S32(0X801A << 16);
    // 0x802C5B04: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x802C5B08: addiu       $t7, $t7, -0x7CB0
    ctx->r15 = ADD32(ctx->r15, -0X7CB0);
    // 0x802C5B0C: addiu       $t6, $t6, -0x7CF0
    ctx->r14 = ADD32(ctx->r14, -0X7CF0);
    // 0x802C5B10: lui         $a3, 0x802C
    ctx->r7 = S32(0X802C << 16);
    // 0x802C5B14: addiu       $a3, $a3, 0x7024
    ctx->r7 = ADD32(ctx->r7, 0X7024);
    // 0x802C5B18: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x802C5B1C: sw          $t7, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r15;
    // 0x802C5B20: addiu       $a0, $v0, 0xA80
    ctx->r4 = ADD32(ctx->r2, 0XA80);
    // 0x802C5B24: addiu       $a1, $v0, 0x1780
    ctx->r5 = ADD32(ctx->r2, 0X1780);
    // 0x802C5B28: jal         0x80069798
    // 0x802C5B2C: addiu       $a2, $v0, 0xA40
    ctx->r6 = ADD32(ctx->r2, 0XA40);
    func_80069798(rdram, ctx);
        goto after_0;
    // 0x802C5B2C: addiu       $a2, $v0, 0xA40
    ctx->r6 = ADD32(ctx->r2, 0XA40);
    after_0:
    // 0x802C5B30: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    // 0x802C5B34: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x802C5B38: jr          $ra
    // 0x802C5B3C: nop

    return;
    // 0x802C5B3C: nop

;}
RECOMP_FUNC void func_i3_802C5B40(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C5B40: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x802C5B44: addiu       $v0, $v0, -0x19C4
    ctx->r2 = ADD32(ctx->r2, -0X19C4);
    // 0x802C5B48: lw          $t6, 0x0($v0)
    ctx->r14 = MEM_W(ctx->r2, 0X0);
    // 0x802C5B4C: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x802C5B50: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x802C5B54: beq         $t6, $zero, L_802C5B80
    if (ctx->r14 == 0) {
        // 0x802C5B58: lui         $t7, 0x800E
        ctx->r15 = S32(0X800E << 16);
            goto L_802C5B80;
    }
    // 0x802C5B58: lui         $t7, 0x800E
    ctx->r15 = S32(0X800E << 16);
    // 0x802C5B5C: sw          $zero, 0x0($v0)
    MEM_W(0X0, ctx->r2) = 0;
    // 0x802C5B60: lw          $t7, -0x54DC($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X54DC);
    // 0x802C5B64: addiu       $at, $zero, 0x1E
    ctx->r1 = ADD32(0, 0X1E);
    // 0x802C5B68: bne         $t7, $at, L_802C5B80
    if (ctx->r15 != ctx->r1) {
        // 0x802C5B6C: nop
    
            goto L_802C5B80;
    }
    // 0x802C5B6C: nop

    // 0x802C5B70: jal         0x80093C44
    // 0x802C5B74: nop

    func_80093C44(rdram, ctx);
        goto after_0;
    // 0x802C5B74: nop

    after_0:
    // 0x802C5B78: b           L_802C5D48
    // 0x802C5B7C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_802C5D48;
    // 0x802C5B7C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C5B80:
    // 0x802C5B80: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x802C5B84: jal         0x8009328C
    // 0x802C5B88: sw          $zero, -0x54D4($at)
    MEM_W(-0X54D4, ctx->r1) = 0;
    func_8009328C(rdram, ctx);
        goto after_1;
    // 0x802C5B88: sw          $zero, -0x54D4($at)
    MEM_W(-0X54D4, ctx->r1) = 0;
    after_1:
    // 0x802C5B8C: lui         $t8, 0x8022
    ctx->r24 = S32(0X8022 << 16);
    // 0x802C5B90: lw          $t8, 0x3938($t8)
    ctx->r24 = MEM_W(ctx->r24, 0X3938);
    // 0x802C5B94: sw          $v0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r2;
    // 0x802C5B98: lui         $v1, 0x802C
    ctx->r3 = S32(0X802C << 16);
    // 0x802C5B9C: beql        $t8, $zero, L_802C5BE0
    if (ctx->r24 == 0) {
        // 0x802C5BA0: addiu       $t9, $v0, 0x8
        ctx->r25 = ADD32(ctx->r2, 0X8);
            goto L_802C5BE0;
    }
    goto skip_0;
    // 0x802C5BA0: addiu       $t9, $v0, 0x8
    ctx->r25 = ADD32(ctx->r2, 0X8);
    skip_0:
    // 0x802C5BA4: lw          $v1, 0x7028($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X7028);
    // 0x802C5BA8: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x802C5BAC: beq         $v1, $zero, L_802C5BC4
    if (ctx->r3 == 0) {
        // 0x802C5BB0: nop
    
            goto L_802C5BC4;
    }
    // 0x802C5BB0: nop

    // 0x802C5BB4: beq         $v1, $at, L_802C5BD4
    if (ctx->r3 == ctx->r1) {
        // 0x802C5BB8: nop
    
            goto L_802C5BD4;
    }
    // 0x802C5BB8: nop

    // 0x802C5BBC: b           L_802C5BE0
    // 0x802C5BC0: addiu       $t9, $v0, 0x8
    ctx->r25 = ADD32(ctx->r2, 0X8);
        goto L_802C5BE0;
    // 0x802C5BC0: addiu       $t9, $v0, 0x8
    ctx->r25 = ADD32(ctx->r2, 0X8);
L_802C5BC4:
    // 0x802C5BC4: jal         0x802C5D54
    // 0x802C5BC8: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
    func_i3_802C5D54(rdram, ctx);
        goto after_2;
    // 0x802C5BC8: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
    after_2:
    // 0x802C5BCC: b           L_802C5BE0
    // 0x802C5BD0: addiu       $t9, $v0, 0x8
    ctx->r25 = ADD32(ctx->r2, 0X8);
        goto L_802C5BE0;
    // 0x802C5BD0: addiu       $t9, $v0, 0x8
    ctx->r25 = ADD32(ctx->r2, 0X8);
L_802C5BD4:
    // 0x802C5BD4: jal         0x802C6344
    // 0x802C5BD8: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
    func_i3_802C6344(rdram, ctx);
        goto after_3;
    // 0x802C5BD8: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
    after_3:
    // 0x802C5BDC: addiu       $t9, $v0, 0x8
    ctx->r25 = ADD32(ctx->r2, 0X8);
L_802C5BE0:
    // 0x802C5BE0: sw          $t9, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r25;
    // 0x802C5BE4: lui         $t1, 0x107
    ctx->r9 = S32(0X107 << 16);
    // 0x802C5BE8: addiu       $t1, $t1, -0xE98
    ctx->r9 = ADD32(ctx->r9, -0XE98);
    // 0x802C5BEC: lui         $t0, 0x600
    ctx->r8 = S32(0X600 << 16);
    // 0x802C5BF0: sw          $t0, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r8;
    // 0x802C5BF4: sw          $t1, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r9;
    // 0x802C5BF8: lui         $t2, 0x800E
    ctx->r10 = S32(0X800E << 16);
    // 0x802C5BFC: lw          $t2, -0x54DC($t2)
    ctx->r10 = MEM_W(ctx->r10, -0X54DC);
    // 0x802C5C00: addiu       $at, $zero, 0x1E
    ctx->r1 = ADD32(0, 0X1E);
    // 0x802C5C04: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x802C5C08: bne         $t2, $at, L_802C5CAC
    if (ctx->r10 != ctx->r1) {
        // 0x802C5C0C: nop
    
            goto L_802C5CAC;
    }
    // 0x802C5C0C: nop

    // 0x802C5C10: lui         $v0, 0x802C
    ctx->r2 = S32(0X802C << 16);
    // 0x802C5C14: addiu       $v0, $v0, 0x6F88
    ctx->r2 = ADD32(ctx->r2, 0X6F88);
    // 0x802C5C18: lw          $t3, 0x0($v0)
    ctx->r11 = MEM_W(ctx->r2, 0X0);
    // 0x802C5C1C: lui         $t4, 0x801D
    ctx->r12 = S32(0X801D << 16);
    // 0x802C5C20: beq         $t3, $zero, L_802C5C38
    if (ctx->r11 == 0) {
        // 0x802C5C24: nop
    
            goto L_802C5C38;
    }
    // 0x802C5C24: nop

    // 0x802C5C28: jal         0x801EB91C
    // 0x802C5C2C: sw          $zero, 0x0($v0)
    MEM_W(0X0, ctx->r2) = 0;
    func_801EB91C(rdram, ctx);
        goto after_4;
    // 0x802C5C2C: sw          $zero, 0x0($v0)
    MEM_W(0X0, ctx->r2) = 0;
    after_4:
    // 0x802C5C30: b           L_802C5D00
    // 0x802C5C34: nop

        goto L_802C5D00;
    // 0x802C5C34: nop

L_802C5C38:
    // 0x802C5C38: lhu         $t4, -0x196E($t4)
    ctx->r12 = MEM_HU(ctx->r12, -0X196E);
    // 0x802C5C3C: lui         $t6, 0x802C
    ctx->r14 = S32(0X802C << 16);
    // 0x802C5C40: lui         $t7, 0x8022
    ctx->r15 = S32(0X8022 << 16);
    // 0x802C5C44: andi        $t5, $t4, 0xB000
    ctx->r13 = ctx->r12 & 0XB000;
    // 0x802C5C48: beq         $t5, $zero, L_802C5C6C
    if (ctx->r13 == 0) {
        // 0x802C5C4C: nop
    
            goto L_802C5C6C;
    }
    // 0x802C5C4C: nop

    // 0x802C5C50: lw          $t6, 0x6F84($t6)
    ctx->r14 = MEM_W(ctx->r14, 0X6F84);
    // 0x802C5C54: beq         $t6, $zero, L_802C5C9C
    if (ctx->r14 == 0) {
        // 0x802C5C58: nop
    
            goto L_802C5C9C;
    }
    // 0x802C5C58: nop

    // 0x802C5C5C: jal         0x802C6E9C
    // 0x802C5C60: nop

    func_i3_802C6E9C(rdram, ctx);
        goto after_5;
    // 0x802C5C60: nop

    after_5:
    // 0x802C5C64: b           L_802C5C9C
    // 0x802C5C68: nop

        goto L_802C5C9C;
    // 0x802C5C68: nop

L_802C5C6C:
    // 0x802C5C6C: lw          $t7, 0x3938($t7)
    ctx->r15 = MEM_W(ctx->r15, 0X3938);
    // 0x802C5C70: lui         $t8, 0x801D
    ctx->r24 = S32(0X801D << 16);
    // 0x802C5C74: lui         $t9, 0x802C
    ctx->r25 = S32(0X802C << 16);
    // 0x802C5C78: beq         $t7, $zero, L_802C5C9C
    if (ctx->r15 == 0) {
        // 0x802C5C7C: nop
    
            goto L_802C5C9C;
    }
    // 0x802C5C7C: nop

    // 0x802C5C80: lw          $t8, -0x19BC($t8)
    ctx->r24 = MEM_W(ctx->r24, -0X19BC);
    // 0x802C5C84: lw          $t9, 0x702C($t9)
    ctx->r25 = MEM_W(ctx->r25, 0X702C);
    // 0x802C5C88: slt         $at, $t8, $t9
    ctx->r1 = SIGNED(ctx->r24) < SIGNED(ctx->r25) ? 1 : 0;
    // 0x802C5C8C: bne         $at, $zero, L_802C5C9C
    if (ctx->r1 != 0) {
        // 0x802C5C90: nop
    
            goto L_802C5C9C;
    }
    // 0x802C5C90: nop

    // 0x802C5C94: jal         0x802C6E9C
    // 0x802C5C98: nop

    func_i3_802C6E9C(rdram, ctx);
        goto after_6;
    // 0x802C5C98: nop

    after_6:
L_802C5C9C:
    // 0x802C5C9C: jal         0x80047E50
    // 0x802C5CA0: nop

    SysUtils_Rand(rdram, ctx);
        goto after_7;
    // 0x802C5CA0: nop

    after_7:
    // 0x802C5CA4: b           L_802C5D00
    // 0x802C5CA8: nop

        goto L_802C5D00;
    // 0x802C5CA8: nop

L_802C5CAC:
    // 0x802C5CAC: lw          $v0, -0x19BC($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X19BC);
    // 0x802C5CB0: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C5CB4: bltz        $v0, L_802C5CC8
    if (SIGNED(ctx->r2) < 0) {
        // 0x802C5CB8: addiu       $t0, $v0, -0x1
        ctx->r8 = ADD32(ctx->r2, -0X1);
            goto L_802C5CC8;
    }
    // 0x802C5CB8: addiu       $t0, $v0, -0x1
    ctx->r8 = ADD32(ctx->r2, -0X1);
    // 0x802C5CBC: sw          $t0, -0x19BC($at)
    MEM_W(-0X19BC, ctx->r1) = ctx->r8;
    // 0x802C5CC0: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x802C5CC4: lw          $v0, -0x19BC($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X19BC);
L_802C5CC8:
    // 0x802C5CC8: bne         $v0, $zero, L_802C5CD8
    if (ctx->r2 != 0) {
        // 0x802C5CCC: nop
    
            goto L_802C5CD8;
    }
    // 0x802C5CCC: nop

    // 0x802C5CD0: jal         0x800C1F60
    // 0x802C5CD4: addiu       $a0, $zero, 0x7
    ctx->r4 = ADD32(0, 0X7);
    func_800C1F60(rdram, ctx);
        goto after_8;
    // 0x802C5CD4: addiu       $a0, $zero, 0x7
    ctx->r4 = ADD32(0, 0X7);
    after_8:
L_802C5CD8:
    // 0x802C5CD8: lui         $t1, 0x8023
    ctx->r9 = S32(0X8023 << 16);
    // 0x802C5CDC: lh          $t1, -0x75EA($t1)
    ctx->r9 = MEM_H(ctx->r9, -0X75EA);
    // 0x802C5CE0: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x802C5CE4: lui         $t2, 0x801D
    ctx->r10 = S32(0X801D << 16);
    // 0x802C5CE8: bne         $t1, $at, L_802C5D00
    if (ctx->r9 != ctx->r1) {
        // 0x802C5CEC: nop
    
            goto L_802C5D00;
    }
    // 0x802C5CEC: nop

    // 0x802C5CF0: lw          $t2, -0x4CD0($t2)
    ctx->r10 = MEM_W(ctx->r10, -0X4CD0);
    // 0x802C5CF4: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x802C5CF8: jal         0x8009345C
    // 0x802C5CFC: sw          $t2, -0x7E90($at)
    MEM_W(-0X7E90, ctx->r1) = ctx->r10;
    func_8009345C(rdram, ctx);
        goto after_9;
    // 0x802C5CFC: sw          $t2, -0x7E90($at)
    MEM_W(-0X7E90, ctx->r1) = ctx->r10;
    after_9:
L_802C5D00:
    // 0x802C5D00: lui         $t3, 0x801D
    ctx->r11 = S32(0X801D << 16);
    // 0x802C5D04: lw          $t3, -0x19C8($t3)
    ctx->r11 = MEM_W(ctx->r11, -0X19C8);
    // 0x802C5D08: addiu       $at, $zero, 0x8
    ctx->r1 = ADD32(0, 0X8);
    // 0x802C5D0C: beq         $t3, $at, L_802C5D1C
    if (ctx->r11 == ctx->r1) {
        // 0x802C5D10: nop
    
            goto L_802C5D1C;
    }
    // 0x802C5D10: nop

    // 0x802C5D14: jal         0x800AD3C4
    // 0x802C5D18: nop

    func_800AD3C4(rdram, ctx);
        goto after_10;
    // 0x802C5D18: nop

    after_10:
L_802C5D1C:
    // 0x802C5D1C: lui         $t4, 0x800E
    ctx->r12 = S32(0X800E << 16);
    // 0x802C5D20: lw          $t4, -0x54DC($t4)
    ctx->r12 = MEM_W(ctx->r12, -0X54DC);
    // 0x802C5D24: addiu       $at, $zero, 0x1E
    ctx->r1 = ADD32(0, 0X1E);
    // 0x802C5D28: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x802C5D2C: bne         $t4, $at, L_802C5D40
    if (ctx->r12 != ctx->r1) {
        // 0x802C5D30: addiu       $v0, $v0, -0x19BC
        ctx->r2 = ADD32(ctx->r2, -0X19BC);
            goto L_802C5D40;
    }
    // 0x802C5D30: addiu       $v0, $v0, -0x19BC
    ctx->r2 = ADD32(ctx->r2, -0X19BC);
    // 0x802C5D34: lw          $t5, 0x0($v0)
    ctx->r13 = MEM_W(ctx->r2, 0X0);
    // 0x802C5D38: addiu       $t6, $t5, 0x1
    ctx->r14 = ADD32(ctx->r13, 0X1);
    // 0x802C5D3C: sw          $t6, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r14;
L_802C5D40:
    // 0x802C5D40: lw          $v0, 0x18($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X18);
    // 0x802C5D44: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C5D48:
    // 0x802C5D48: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x802C5D4C: jr          $ra
    // 0x802C5D50: nop

    return;
    // 0x802C5D50: nop

;}
RECOMP_FUNC void func_i3_802C5D54(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C5D54: lui         $t2, 0x802C
    ctx->r10 = S32(0X802C << 16);
    // 0x802C5D58: addiu       $t2, $t2, 0x6F64
    ctx->r10 = ADD32(ctx->r10, 0X6F64);
    // 0x802C5D5C: lw          $v0, 0x0($t2)
    ctx->r2 = MEM_W(ctx->r10, 0X0);
    // 0x802C5D60: addiu       $sp, $sp, -0x40
    ctx->r29 = ADD32(ctx->r29, -0X40);
    // 0x802C5D64: sw          $ra, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r31;
    // 0x802C5D68: beq         $v0, $zero, L_802C5D94
    if (ctx->r2 == 0) {
        // 0x802C5D6C: sw          $a0, 0x40($sp)
        MEM_W(0X40, ctx->r29) = ctx->r4;
            goto L_802C5D94;
    }
    // 0x802C5D6C: sw          $a0, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r4;
    // 0x802C5D70: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C5D74: beq         $v0, $a1, L_802C5DF4
    if (ctx->r2 == ctx->r5) {
        // 0x802C5D78: addiu       $at, $zero, 0x2
        ctx->r1 = ADD32(0, 0X2);
            goto L_802C5DF4;
    }
    // 0x802C5D78: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x802C5D7C: beq         $v0, $at, L_802C5FEC
    if (ctx->r2 == ctx->r1) {
        // 0x802C5D80: addiu       $at, $zero, 0x3
        ctx->r1 = ADD32(0, 0X3);
            goto L_802C5FEC;
    }
    // 0x802C5D80: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x802C5D84: beq         $v0, $at, L_802C6058
    if (ctx->r2 == ctx->r1) {
        // 0x802C5D88: lui         $t3, 0x802C
        ctx->r11 = S32(0X802C << 16);
            goto L_802C6058;
    }
    // 0x802C5D88: lui         $t3, 0x802C
    ctx->r11 = S32(0X802C << 16);
    // 0x802C5D8C: b           L_802C615C
    // 0x802C5D90: addiu       $t3, $t3, 0x6F70
    ctx->r11 = ADD32(ctx->r11, 0X6F70);
        goto L_802C615C;
    // 0x802C5D90: addiu       $t3, $t3, 0x6F70
    ctx->r11 = ADD32(ctx->r11, 0X6F70);
L_802C5D94:
    // 0x802C5D94: lui         $v1, 0x802C
    ctx->r3 = S32(0X802C << 16);
    // 0x802C5D98: addiu       $v1, $v1, 0x6F68
    ctx->r3 = ADD32(ctx->r3, 0X6F68);
    // 0x802C5D9C: lw          $t6, 0x0($v1)
    ctx->r14 = MEM_W(ctx->r3, 0X0);
    // 0x802C5DA0: lui         $t0, 0x802C
    ctx->r8 = S32(0X802C << 16);
    // 0x802C5DA4: addiu       $t0, $t0, 0x6F7C
    ctx->r8 = ADD32(ctx->r8, 0X6F7C);
    // 0x802C5DA8: addiu       $t7, $t6, 0x1
    ctx->r15 = ADD32(ctx->r14, 0X1);
    // 0x802C5DAC: slti        $at, $t7, 0x5
    ctx->r1 = SIGNED(ctx->r15) < 0X5 ? 1 : 0;
    // 0x802C5DB0: bne         $at, $zero, L_802C5DD0
    if (ctx->r1 != 0) {
        // 0x802C5DB4: sw          $t7, 0x0($v1)
        MEM_W(0X0, ctx->r3) = ctx->r15;
            goto L_802C5DD0;
    }
    // 0x802C5DB4: sw          $t7, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r15;
    // 0x802C5DB8: lui         $a2, 0x802C
    ctx->r6 = S32(0X802C << 16);
    // 0x802C5DBC: addiu       $a2, $a2, 0x6F74
    ctx->r6 = ADD32(ctx->r6, 0X6F74);
    // 0x802C5DC0: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C5DC4: sw          $a1, 0x0($t2)
    MEM_W(0X0, ctx->r10) = ctx->r5;
    // 0x802C5DC8: sw          $zero, 0x0($a2)
    MEM_W(0X0, ctx->r6) = 0;
    // 0x802C5DCC: sw          $zero, 0x0($v1)
    MEM_W(0X0, ctx->r3) = 0;
L_802C5DD0:
    // 0x802C5DD0: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C5DD4: sw          $zero, 0x6F78($at)
    MEM_W(0X6F78, ctx->r1) = 0;
    // 0x802C5DD8: lui         $t3, 0x802C
    ctx->r11 = S32(0X802C << 16);
    // 0x802C5DDC: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C5DE0: addiu       $t3, $t3, 0x6F70
    ctx->r11 = ADD32(ctx->r11, 0X6F70);
    // 0x802C5DE4: sw          $zero, 0x6F6C($at)
    MEM_W(0X6F6C, ctx->r1) = 0;
    // 0x802C5DE8: sw          $zero, 0x0($t3)
    MEM_W(0X0, ctx->r11) = 0;
    // 0x802C5DEC: b           L_802C615C
    // 0x802C5DF0: sw          $zero, 0x0($t0)
    MEM_W(0X0, ctx->r8) = 0;
        goto L_802C615C;
    // 0x802C5DF0: sw          $zero, 0x0($t0)
    MEM_W(0X0, ctx->r8) = 0;
L_802C5DF4:
    // 0x802C5DF4: lui         $v1, 0x802C
    ctx->r3 = S32(0X802C << 16);
    // 0x802C5DF8: addiu       $v1, $v1, 0x6F68
    ctx->r3 = ADD32(ctx->r3, 0X6F68);
    // 0x802C5DFC: lw          $t5, 0x0($v1)
    ctx->r13 = MEM_W(ctx->r3, 0X0);
    // 0x802C5E00: addiu       $t6, $t5, 0x1
    ctx->r14 = ADD32(ctx->r13, 0X1);
    // 0x802C5E04: slti        $at, $t6, 0x14
    ctx->r1 = SIGNED(ctx->r14) < 0X14 ? 1 : 0;
    // 0x802C5E08: sw          $t6, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r14;
    // 0x802C5E0C: bne         $at, $zero, L_802C5E28
    if (ctx->r1 != 0) {
        // 0x802C5E10: or          $a0, $t6, $zero
        ctx->r4 = ctx->r14 | 0;
            goto L_802C5E28;
    }
    // 0x802C5E10: or          $a0, $t6, $zero
    ctx->r4 = ctx->r14 | 0;
    // 0x802C5E14: lui         $a2, 0x802C
    ctx->r6 = S32(0X802C << 16);
    // 0x802C5E18: addiu       $a2, $a2, 0x6F74
    ctx->r6 = ADD32(ctx->r6, 0X6F74);
    // 0x802C5E1C: lw          $t7, 0x0($a2)
    ctx->r15 = MEM_W(ctx->r6, 0X0);
    // 0x802C5E20: addiu       $t8, $t7, 0x1
    ctx->r24 = ADD32(ctx->r15, 0X1);
    // 0x802C5E24: sw          $t8, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r24;
L_802C5E28:
    // 0x802C5E28: lui         $a2, 0x802C
    ctx->r6 = S32(0X802C << 16);
    // 0x802C5E2C: slti        $at, $a0, 0xA
    ctx->r1 = SIGNED(ctx->r4) < 0XA ? 1 : 0;
    // 0x802C5E30: bne         $at, $zero, L_802C5E5C
    if (ctx->r1 != 0) {
        // 0x802C5E34: addiu       $a2, $a2, 0x6F74
        ctx->r6 = ADD32(ctx->r6, 0X6F74);
            goto L_802C5E5C;
    }
    // 0x802C5E34: addiu       $a2, $a2, 0x6F74
    ctx->r6 = ADD32(ctx->r6, 0X6F74);
    // 0x802C5E38: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    // 0x802C5E3C: lui         $t3, 0x802C
    ctx->r11 = S32(0X802C << 16);
    // 0x802C5E40: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C5E44: addiu       $t3, $t3, 0x6F70
    ctx->r11 = ADD32(ctx->r11, 0X6F70);
    // 0x802C5E48: addiu       $t1, $zero, 0xAA
    ctx->r9 = ADD32(0, 0XAA);
    // 0x802C5E4C: sw          $a3, 0x6F6C($at)
    MEM_W(0X6F6C, ctx->r1) = ctx->r7;
    // 0x802C5E50: sw          $t1, 0x0($t3)
    MEM_W(0X0, ctx->r11) = ctx->r9;
    // 0x802C5E54: b           L_802C5EF4
    // 0x802C5E58: addiu       $a1, $zero, 0xA
    ctx->r5 = ADD32(0, 0XA);
        goto L_802C5EF4;
    // 0x802C5E58: addiu       $a1, $zero, 0xA
    ctx->r5 = ADD32(0, 0XA);
L_802C5E5C:
    // 0x802C5E5C: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    // 0x802C5E60: multu       $a0, $a3
    result = U64(U32(ctx->r4)) * U64(U32(ctx->r7)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x802C5E64: addiu       $a1, $zero, 0xA
    ctx->r5 = ADD32(0, 0XA);
    // 0x802C5E68: addiu       $t1, $zero, 0xAA
    ctx->r9 = ADD32(0, 0XAA);
    // 0x802C5E6C: lui         $t3, 0x802C
    ctx->r11 = S32(0X802C << 16);
    // 0x802C5E70: addiu       $t3, $t3, 0x6F70
    ctx->r11 = ADD32(ctx->r11, 0X6F70);
    // 0x802C5E74: mflo        $t9
    ctx->r25 = lo;
    // 0x802C5E78: nop

    // 0x802C5E7C: nop

    // 0x802C5E80: div         $zero, $t9, $a1
    lo = S32(S64(S32(ctx->r25)) / S64(S32(ctx->r5))); hi = S32(S64(S32(ctx->r25)) % S64(S32(ctx->r5)));
    // 0x802C5E84: mflo        $t4
    ctx->r12 = lo;
    // 0x802C5E88: bne         $a1, $zero, L_802C5E94
    if (ctx->r5 != 0) {
        // 0x802C5E8C: nop
    
            goto L_802C5E94;
    }
    // 0x802C5E8C: nop

    // 0x802C5E90: break       7
    do_break(2150391440);
L_802C5E94:
    // 0x802C5E94: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x802C5E98: bne         $a1, $at, L_802C5EAC
    if (ctx->r5 != ctx->r1) {
        // 0x802C5E9C: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_802C5EAC;
    }
    // 0x802C5E9C: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x802C5EA0: bne         $t9, $at, L_802C5EAC
    if (ctx->r25 != ctx->r1) {
        // 0x802C5EA4: nop
    
            goto L_802C5EAC;
    }
    // 0x802C5EA4: nop

    // 0x802C5EA8: break       6
    do_break(2150391464);
L_802C5EAC:
    // 0x802C5EAC: multu       $a0, $t1
    result = U64(U32(ctx->r4)) * U64(U32(ctx->r9)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x802C5EB0: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C5EB4: sw          $t4, 0x6F6C($at)
    MEM_W(0X6F6C, ctx->r1) = ctx->r12;
    // 0x802C5EB8: mflo        $t5
    ctx->r13 = lo;
    // 0x802C5EBC: nop

    // 0x802C5EC0: nop

    // 0x802C5EC4: div         $zero, $t5, $a1
    lo = S32(S64(S32(ctx->r13)) / S64(S32(ctx->r5))); hi = S32(S64(S32(ctx->r13)) % S64(S32(ctx->r5)));
    // 0x802C5EC8: mflo        $t6
    ctx->r14 = lo;
    // 0x802C5ECC: sw          $t6, 0x0($t3)
    MEM_W(0X0, ctx->r11) = ctx->r14;
    // 0x802C5ED0: bne         $a1, $zero, L_802C5EDC
    if (ctx->r5 != 0) {
        // 0x802C5ED4: nop
    
            goto L_802C5EDC;
    }
    // 0x802C5ED4: nop

    // 0x802C5ED8: break       7
    do_break(2150391512);
L_802C5EDC:
    // 0x802C5EDC: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x802C5EE0: bne         $a1, $at, L_802C5EF4
    if (ctx->r5 != ctx->r1) {
        // 0x802C5EE4: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_802C5EF4;
    }
    // 0x802C5EE4: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x802C5EE8: bne         $t5, $at, L_802C5EF4
    if (ctx->r13 != ctx->r1) {
        // 0x802C5EEC: nop
    
            goto L_802C5EF4;
    }
    // 0x802C5EEC: nop

    // 0x802C5EF0: break       6
    do_break(2150391536);
L_802C5EF4:
    // 0x802C5EF4: lw          $v0, 0x0($a2)
    ctx->r2 = MEM_W(ctx->r6, 0X0);
    // 0x802C5EF8: slti        $at, $v0, 0xA
    ctx->r1 = SIGNED(ctx->r2) < 0XA ? 1 : 0;
    // 0x802C5EFC: bne         $at, $zero, L_802C5F20
    if (ctx->r1 != 0) {
        // 0x802C5F00: nop
    
            goto L_802C5F20;
    }
    // 0x802C5F00: nop

    // 0x802C5F04: lui         $a1, 0x802C
    ctx->r5 = S32(0X802C << 16);
    // 0x802C5F08: lui         $t0, 0x802C
    ctx->r8 = S32(0X802C << 16);
    // 0x802C5F0C: addiu       $t0, $t0, 0x6F7C
    ctx->r8 = ADD32(ctx->r8, 0X6F7C);
    // 0x802C5F10: addiu       $a1, $a1, 0x6F78
    ctx->r5 = ADD32(ctx->r5, 0X6F78);
    // 0x802C5F14: sw          $a3, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r7;
    // 0x802C5F18: b           L_802C5FB4
    // 0x802C5F1C: sw          $t1, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r9;
        goto L_802C5FB4;
    // 0x802C5F1C: sw          $t1, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r9;
L_802C5F20:
    // 0x802C5F20: multu       $v0, $a3
    result = U64(U32(ctx->r2)) * U64(U32(ctx->r7)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x802C5F24: lui         $t0, 0x802C
    ctx->r8 = S32(0X802C << 16);
    // 0x802C5F28: addiu       $t0, $t0, 0x6F7C
    ctx->r8 = ADD32(ctx->r8, 0X6F7C);
    // 0x802C5F2C: mflo        $t7
    ctx->r15 = lo;
    // 0x802C5F30: nop

    // 0x802C5F34: nop

    // 0x802C5F38: div         $zero, $t7, $a1
    lo = S32(S64(S32(ctx->r15)) / S64(S32(ctx->r5))); hi = S32(S64(S32(ctx->r15)) % S64(S32(ctx->r5)));
    // 0x802C5F3C: mflo        $t8
    ctx->r24 = lo;
    // 0x802C5F40: bne         $a1, $zero, L_802C5F4C
    if (ctx->r5 != 0) {
        // 0x802C5F44: nop
    
            goto L_802C5F4C;
    }
    // 0x802C5F44: nop

    // 0x802C5F48: break       7
    do_break(2150391624);
L_802C5F4C:
    // 0x802C5F4C: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x802C5F50: bne         $a1, $at, L_802C5F64
    if (ctx->r5 != ctx->r1) {
        // 0x802C5F54: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_802C5F64;
    }
    // 0x802C5F54: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x802C5F58: bne         $t7, $at, L_802C5F64
    if (ctx->r15 != ctx->r1) {
        // 0x802C5F5C: nop
    
            goto L_802C5F64;
    }
    // 0x802C5F5C: nop

    // 0x802C5F60: break       6
    do_break(2150391648);
L_802C5F64:
    // 0x802C5F64: multu       $v0, $t1
    result = U64(U32(ctx->r2)) * U64(U32(ctx->r9)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x802C5F68: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C5F6C: sw          $t8, 0x6F78($at)
    MEM_W(0X6F78, ctx->r1) = ctx->r24;
    // 0x802C5F70: mflo        $t9
    ctx->r25 = lo;
    // 0x802C5F74: nop

    // 0x802C5F78: nop

    // 0x802C5F7C: div         $zero, $t9, $a1
    lo = S32(S64(S32(ctx->r25)) / S64(S32(ctx->r5))); hi = S32(S64(S32(ctx->r25)) % S64(S32(ctx->r5)));
    // 0x802C5F80: mflo        $t4
    ctx->r12 = lo;
    // 0x802C5F84: sw          $t4, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r12;
    // 0x802C5F88: bne         $a1, $zero, L_802C5F94
    if (ctx->r5 != 0) {
        // 0x802C5F8C: nop
    
            goto L_802C5F94;
    }
    // 0x802C5F8C: nop

    // 0x802C5F90: break       7
    do_break(2150391696);
L_802C5F94:
    // 0x802C5F94: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x802C5F98: bne         $a1, $at, L_802C5FAC
    if (ctx->r5 != ctx->r1) {
        // 0x802C5F9C: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_802C5FAC;
    }
    // 0x802C5F9C: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x802C5FA0: bne         $t9, $at, L_802C5FAC
    if (ctx->r25 != ctx->r1) {
        // 0x802C5FA4: nop
    
            goto L_802C5FAC;
    }
    // 0x802C5FA4: nop

    // 0x802C5FA8: break       6
    do_break(2150391720);
L_802C5FAC:
    // 0x802C5FAC: lui         $a1, 0x802C
    ctx->r5 = S32(0X802C << 16);
    // 0x802C5FB0: addiu       $a1, $a1, 0x6F78
    ctx->r5 = ADD32(ctx->r5, 0X6F78);
L_802C5FB4:
    // 0x802C5FB4: slti        $at, $a0, 0xA
    ctx->r1 = SIGNED(ctx->r4) < 0XA ? 1 : 0;
    // 0x802C5FB8: bne         $at, $zero, L_802C615C
    if (ctx->r1 != 0) {
        // 0x802C5FBC: slti        $at, $v0, 0xA
        ctx->r1 = SIGNED(ctx->r2) < 0XA ? 1 : 0;
            goto L_802C615C;
    }
    // 0x802C5FBC: slti        $at, $v0, 0xA
    ctx->r1 = SIGNED(ctx->r2) < 0XA ? 1 : 0;
    // 0x802C5FC0: bne         $at, $zero, L_802C615C
    if (ctx->r1 != 0) {
        // 0x802C5FC4: addiu       $t5, $zero, 0x2
        ctx->r13 = ADD32(0, 0X2);
            goto L_802C615C;
    }
    // 0x802C5FC4: addiu       $t5, $zero, 0x2
    ctx->r13 = ADD32(0, 0X2);
    // 0x802C5FC8: sw          $t5, 0x0($t2)
    MEM_W(0X0, ctx->r10) = ctx->r13;
    // 0x802C5FCC: sw          $a3, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r7;
    // 0x802C5FD0: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C5FD4: sw          $a3, 0x6F6C($at)
    MEM_W(0X6F6C, ctx->r1) = ctx->r7;
    // 0x802C5FD8: sw          $t1, 0x0($t3)
    MEM_W(0X0, ctx->r11) = ctx->r9;
    // 0x802C5FDC: sw          $t1, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r9;
    // 0x802C5FE0: sw          $zero, 0x0($v1)
    MEM_W(0X0, ctx->r3) = 0;
    // 0x802C5FE4: b           L_802C615C
    // 0x802C5FE8: sw          $zero, 0x0($a2)
    MEM_W(0X0, ctx->r6) = 0;
        goto L_802C615C;
    // 0x802C5FE8: sw          $zero, 0x0($a2)
    MEM_W(0X0, ctx->r6) = 0;
L_802C5FEC:
    // 0x802C5FEC: lui         $v1, 0x802C
    ctx->r3 = S32(0X802C << 16);
    // 0x802C5FF0: addiu       $v1, $v1, 0x6F68
    ctx->r3 = ADD32(ctx->r3, 0X6F68);
    // 0x802C5FF4: lw          $t9, 0x0($v1)
    ctx->r25 = MEM_W(ctx->r3, 0X0);
    // 0x802C5FF8: lui         $v0, 0x802C
    ctx->r2 = S32(0X802C << 16);
    // 0x802C5FFC: addiu       $v0, $v0, 0x6F78
    ctx->r2 = ADD32(ctx->r2, 0X6F78);
    // 0x802C6000: addiu       $t4, $t9, 0x1
    ctx->r12 = ADD32(ctx->r25, 0X1);
    // 0x802C6004: slti        $at, $t4, 0x19
    ctx->r1 = SIGNED(ctx->r12) < 0X19 ? 1 : 0;
    // 0x802C6008: bne         $at, $zero, L_802C6028
    if (ctx->r1 != 0) {
        // 0x802C600C: sw          $t4, 0x0($v1)
        MEM_W(0X0, ctx->r3) = ctx->r12;
            goto L_802C6028;
    }
    // 0x802C600C: sw          $t4, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r12;
    // 0x802C6010: lui         $a2, 0x802C
    ctx->r6 = S32(0X802C << 16);
    // 0x802C6014: addiu       $a2, $a2, 0x6F74
    ctx->r6 = ADD32(ctx->r6, 0X6F74);
    // 0x802C6018: addiu       $t6, $zero, 0x3
    ctx->r14 = ADD32(0, 0X3);
    // 0x802C601C: sw          $t6, 0x0($t2)
    MEM_W(0X0, ctx->r10) = ctx->r14;
    // 0x802C6020: sw          $zero, 0x0($a2)
    MEM_W(0X0, ctx->r6) = 0;
    // 0x802C6024: sw          $zero, 0x0($v1)
    MEM_W(0X0, ctx->r3) = 0;
L_802C6028:
    // 0x802C6028: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    // 0x802C602C: lui         $t0, 0x802C
    ctx->r8 = S32(0X802C << 16);
    // 0x802C6030: lui         $t3, 0x802C
    ctx->r11 = S32(0X802C << 16);
    // 0x802C6034: sw          $a3, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r7;
    // 0x802C6038: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C603C: addiu       $t3, $t3, 0x6F70
    ctx->r11 = ADD32(ctx->r11, 0X6F70);
    // 0x802C6040: addiu       $t0, $t0, 0x6F7C
    ctx->r8 = ADD32(ctx->r8, 0X6F7C);
    // 0x802C6044: addiu       $t1, $zero, 0xAA
    ctx->r9 = ADD32(0, 0XAA);
    // 0x802C6048: sw          $a3, 0x6F6C($at)
    MEM_W(0X6F6C, ctx->r1) = ctx->r7;
    // 0x802C604C: sw          $t1, 0x0($t3)
    MEM_W(0X0, ctx->r11) = ctx->r9;
    // 0x802C6050: b           L_802C615C
    // 0x802C6054: sw          $t1, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r9;
        goto L_802C615C;
    // 0x802C6054: sw          $t1, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r9;
L_802C6058:
    // 0x802C6058: lui         $v1, 0x802C
    ctx->r3 = S32(0X802C << 16);
    // 0x802C605C: addiu       $v1, $v1, 0x6F68
    ctx->r3 = ADD32(ctx->r3, 0X6F68);
    // 0x802C6060: lw          $t4, 0x0($v1)
    ctx->r12 = MEM_W(ctx->r3, 0X0);
    // 0x802C6064: addiu       $t5, $t4, 0x1
    ctx->r13 = ADD32(ctx->r12, 0X1);
    // 0x802C6068: slti        $at, $t5, 0xA
    ctx->r1 = SIGNED(ctx->r13) < 0XA ? 1 : 0;
    // 0x802C606C: sw          $t5, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r13;
    // 0x802C6070: bne         $at, $zero, L_802C60A0
    if (ctx->r1 != 0) {
        // 0x802C6074: or          $a0, $t5, $zero
        ctx->r4 = ctx->r13 | 0;
            goto L_802C60A0;
    }
    // 0x802C6074: or          $a0, $t5, $zero
    ctx->r4 = ctx->r13 | 0;
    // 0x802C6078: sw          $zero, 0x0($t2)
    MEM_W(0X0, ctx->r10) = 0;
    // 0x802C607C: sw          $zero, 0x0($v1)
    MEM_W(0X0, ctx->r3) = 0;
    // 0x802C6080: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C6084: lui         $t3, 0x802C
    ctx->r11 = S32(0X802C << 16);
    // 0x802C6088: sw          $zero, 0x6F6C($at)
    MEM_W(0X6F6C, ctx->r1) = 0;
    // 0x802C608C: addiu       $t3, $t3, 0x6F70
    ctx->r11 = ADD32(ctx->r11, 0X6F70);
    // 0x802C6090: sw          $zero, 0x0($t3)
    MEM_W(0X0, ctx->r11) = 0;
    // 0x802C6094: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C6098: b           L_802C613C
    // 0x802C609C: sw          $a1, 0x7028($at)
    MEM_W(0X7028, ctx->r1) = ctx->r5;
        goto L_802C613C;
    // 0x802C609C: sw          $a1, 0x7028($at)
    MEM_W(0X7028, ctx->r1) = ctx->r5;
L_802C60A0:
    // 0x802C60A0: addiu       $a1, $zero, 0xA
    ctx->r5 = ADD32(0, 0XA);
    // 0x802C60A4: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    // 0x802C60A8: subu        $v0, $a1, $a0
    ctx->r2 = SUB32(ctx->r5, ctx->r4);
    // 0x802C60AC: multu       $v0, $a3
    result = U64(U32(ctx->r2)) * U64(U32(ctx->r7)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x802C60B0: addiu       $t1, $zero, 0xAA
    ctx->r9 = ADD32(0, 0XAA);
    // 0x802C60B4: lui         $t3, 0x802C
    ctx->r11 = S32(0X802C << 16);
    // 0x802C60B8: addiu       $t3, $t3, 0x6F70
    ctx->r11 = ADD32(ctx->r11, 0X6F70);
    // 0x802C60BC: mflo        $t6
    ctx->r14 = lo;
    // 0x802C60C0: nop

    // 0x802C60C4: nop

    // 0x802C60C8: div         $zero, $t6, $a1
    lo = S32(S64(S32(ctx->r14)) / S64(S32(ctx->r5))); hi = S32(S64(S32(ctx->r14)) % S64(S32(ctx->r5)));
    // 0x802C60CC: mflo        $t7
    ctx->r15 = lo;
    // 0x802C60D0: bne         $a1, $zero, L_802C60DC
    if (ctx->r5 != 0) {
        // 0x802C60D4: nop
    
            goto L_802C60DC;
    }
    // 0x802C60D4: nop

    // 0x802C60D8: break       7
    do_break(2150392024);
L_802C60DC:
    // 0x802C60DC: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x802C60E0: bne         $a1, $at, L_802C60F4
    if (ctx->r5 != ctx->r1) {
        // 0x802C60E4: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_802C60F4;
    }
    // 0x802C60E4: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x802C60E8: bne         $t6, $at, L_802C60F4
    if (ctx->r14 != ctx->r1) {
        // 0x802C60EC: nop
    
            goto L_802C60F4;
    }
    // 0x802C60EC: nop

    // 0x802C60F0: break       6
    do_break(2150392048);
L_802C60F4:
    // 0x802C60F4: multu       $v0, $t1
    result = U64(U32(ctx->r2)) * U64(U32(ctx->r9)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x802C60F8: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C60FC: sw          $t7, 0x6F6C($at)
    MEM_W(0X6F6C, ctx->r1) = ctx->r15;
    // 0x802C6100: mflo        $t8
    ctx->r24 = lo;
    // 0x802C6104: nop

    // 0x802C6108: nop

    // 0x802C610C: div         $zero, $t8, $a1
    lo = S32(S64(S32(ctx->r24)) / S64(S32(ctx->r5))); hi = S32(S64(S32(ctx->r24)) % S64(S32(ctx->r5)));
    // 0x802C6110: mflo        $t9
    ctx->r25 = lo;
    // 0x802C6114: sw          $t9, 0x0($t3)
    MEM_W(0X0, ctx->r11) = ctx->r25;
    // 0x802C6118: bne         $a1, $zero, L_802C6124
    if (ctx->r5 != 0) {
        // 0x802C611C: nop
    
            goto L_802C6124;
    }
    // 0x802C611C: nop

    // 0x802C6120: break       7
    do_break(2150392096);
L_802C6124:
    // 0x802C6124: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x802C6128: bne         $a1, $at, L_802C613C
    if (ctx->r5 != ctx->r1) {
        // 0x802C612C: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_802C613C;
    }
    // 0x802C612C: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x802C6130: bne         $t8, $at, L_802C613C
    if (ctx->r24 != ctx->r1) {
        // 0x802C6134: nop
    
            goto L_802C613C;
    }
    // 0x802C6134: nop

    // 0x802C6138: break       6
    do_break(2150392120);
L_802C613C:
    // 0x802C613C: lui         $t4, 0x802C
    ctx->r12 = S32(0X802C << 16);
    // 0x802C6140: lw          $t4, 0x6F6C($t4)
    ctx->r12 = MEM_W(ctx->r12, 0X6F6C);
    // 0x802C6144: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C6148: lui         $t0, 0x802C
    ctx->r8 = S32(0X802C << 16);
    // 0x802C614C: sw          $t4, 0x6F78($at)
    MEM_W(0X6F78, ctx->r1) = ctx->r12;
    // 0x802C6150: lw          $t5, 0x0($t3)
    ctx->r13 = MEM_W(ctx->r11, 0X0);
    // 0x802C6154: addiu       $t0, $t0, 0x6F7C
    ctx->r8 = ADD32(ctx->r8, 0X6F7C);
    // 0x802C6158: sw          $t5, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r13;
L_802C615C:
    // 0x802C615C: lw          $t6, 0x40($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X40);
    // 0x802C6160: lui         $t9, 0x107
    ctx->r25 = S32(0X107 << 16);
    // 0x802C6164: addiu       $t9, $t9, -0x9D8
    ctx->r25 = ADD32(ctx->r25, -0X9D8);
    // 0x802C6168: addiu       $t7, $t6, 0x8
    ctx->r15 = ADD32(ctx->r14, 0X8);
    // 0x802C616C: sw          $t7, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r15;
    // 0x802C6170: lui         $t8, 0x600
    ctx->r24 = S32(0X600 << 16);
    // 0x802C6174: sw          $t8, 0x0($t6)
    MEM_W(0X0, ctx->r14) = ctx->r24;
    // 0x802C6178: sw          $t9, 0x4($t6)
    MEM_W(0X4, ctx->r14) = ctx->r25;
    // 0x802C617C: lw          $t4, 0x40($sp)
    ctx->r12 = MEM_W(ctx->r29, 0X40);
    // 0x802C6180: lui         $t6, 0xFA00
    ctx->r14 = S32(0XFA00 << 16);
    // 0x802C6184: addiu       $at, $zero, -0x100
    ctx->r1 = ADD32(0, -0X100);
    // 0x802C6188: addiu       $t5, $t4, 0x8
    ctx->r13 = ADD32(ctx->r12, 0X8);
    // 0x802C618C: sw          $t5, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r13;
    // 0x802C6190: sw          $t6, 0x0($t4)
    MEM_W(0X0, ctx->r12) = ctx->r14;
    // 0x802C6194: lw          $t7, 0x0($t3)
    ctx->r15 = MEM_W(ctx->r11, 0X0);
    // 0x802C6198: addiu       $t5, $zero, 0x20
    ctx->r13 = ADD32(0, 0X20);
    // 0x802C619C: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C61A0: andi        $t8, $t7, 0xFF
    ctx->r24 = ctx->r15 & 0XFF;
    // 0x802C61A4: or          $t9, $t8, $at
    ctx->r25 = ctx->r24 | ctx->r1;
    // 0x802C61A8: sw          $t9, 0x4($t4)
    MEM_W(0X4, ctx->r12) = ctx->r25;
    // 0x802C61AC: addiu       $t4, $zero, 0x168
    ctx->r12 = ADD32(0, 0X168);
    // 0x802C61B0: sw          $t4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r12;
    // 0x802C61B4: sw          $t5, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r13;
    // 0x802C61B8: lw          $a0, 0x40($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X40);
    // 0x802C61BC: addiu       $a2, $zero, 0x20
    ctx->r6 = ADD32(0, 0X20);
    // 0x802C61C0: jal         0x80094338
    // 0x802C61C4: addiu       $a3, $zero, 0x4B
    ctx->r7 = ADD32(0, 0X4B);
    func_80094338(rdram, ctx);
        goto after_0;
    // 0x802C61C4: addiu       $a3, $zero, 0x4B
    ctx->r7 = ADD32(0, 0X4B);
    after_0:
    // 0x802C61C8: lui         $t0, 0x802C
    ctx->r8 = S32(0X802C << 16);
    // 0x802C61CC: lui         $t6, 0xFA00
    ctx->r14 = S32(0XFA00 << 16);
    // 0x802C61D0: addiu       $t0, $t0, 0x6F7C
    ctx->r8 = ADD32(ctx->r8, 0X6F7C);
    // 0x802C61D4: sw          $t6, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r14;
    // 0x802C61D8: lw          $t7, 0x0($t0)
    ctx->r15 = MEM_W(ctx->r8, 0X0);
    // 0x802C61DC: addiu       $at, $zero, -0x100
    ctx->r1 = ADD32(0, -0X100);
    // 0x802C61E0: addiu       $t4, $zero, 0x168
    ctx->r12 = ADD32(0, 0X168);
    // 0x802C61E4: andi        $t8, $t7, 0xFF
    ctx->r24 = ctx->r15 & 0XFF;
    // 0x802C61E8: or          $t9, $t8, $at
    ctx->r25 = ctx->r24 | ctx->r1;
    // 0x802C61EC: sw          $t9, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r25;
    // 0x802C61F0: addiu       $t5, $zero, 0x20
    ctx->r13 = ADD32(0, 0X20);
    // 0x802C61F4: sw          $t5, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r13;
    // 0x802C61F8: sw          $t4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r12;
    // 0x802C61FC: addiu       $a0, $v0, 0x8
    ctx->r4 = ADD32(ctx->r2, 0X8);
    // 0x802C6200: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C6204: addiu       $a2, $zero, 0x20
    ctx->r6 = ADD32(0, 0X20);
    // 0x802C6208: jal         0x80094338
    // 0x802C620C: addiu       $a3, $zero, 0x85
    ctx->r7 = ADD32(0, 0X85);
    func_80094338(rdram, ctx);
        goto after_1;
    // 0x802C620C: addiu       $a3, $zero, 0x85
    ctx->r7 = ADD32(0, 0X85);
    after_1:
    // 0x802C6210: lui         $a2, 0x802C
    ctx->r6 = S32(0X802C << 16);
    // 0x802C6214: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C6218: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C621C: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C6220: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C6224: addiu       $t4, $zero, 0xFF
    ctx->r12 = ADD32(0, 0XFF);
    // 0x802C6228: addiu       $t5, $zero, 0xFF
    ctx->r13 = ADD32(0, 0XFF);
    // 0x802C622C: sw          $t5, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r13;
    // 0x802C6230: sw          $t4, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r12;
    // 0x802C6234: sw          $t9, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r25;
    // 0x802C6238: sw          $t9, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r25;
    // 0x802C623C: sw          $t8, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r24;
    // 0x802C6240: sw          $t8, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r24;
    // 0x802C6244: sw          $t7, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r15;
    // 0x802C6248: sw          $t7, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r15;
    // 0x802C624C: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x802C6250: sw          $t6, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r14;
    // 0x802C6254: lbu         $a2, 0x6F6F($a2)
    ctx->r6 = MEM_BU(ctx->r6, 0X6F6F);
    // 0x802C6258: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C625C: addiu       $a1, $zero, 0xA
    ctx->r5 = ADD32(0, 0XA);
    // 0x802C6260: jal         0x801E946C
    // 0x802C6264: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    func_801E946C(rdram, ctx);
        goto after_2;
    // 0x802C6264: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    after_2:
    // 0x802C6268: addiu       $t4, $zero, 0x51
    ctx->r12 = ADD32(0, 0X51);
    // 0x802C626C: sw          $t4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r12;
    // 0x802C6270: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C6274: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C6278: addiu       $a2, $zero, 0x22
    ctx->r6 = ADD32(0, 0X22);
    // 0x802C627C: addiu       $a3, $zero, 0x7C
    ctx->r7 = ADD32(0, 0X7C);
    // 0x802C6280: jal         0x801E3EE0
    // 0x802C6284: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    func_801E3EE0(rdram, ctx);
        goto after_3;
    // 0x802C6284: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    after_3:
    // 0x802C6288: lui         $a2, 0x802C
    ctx->r6 = S32(0X802C << 16);
    // 0x802C628C: addiu       $t5, $zero, 0xFF
    ctx->r13 = ADD32(0, 0XFF);
    // 0x802C6290: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C6294: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C6298: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C629C: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C62A0: addiu       $t4, $zero, 0xFF
    ctx->r12 = ADD32(0, 0XFF);
    // 0x802C62A4: sw          $t4, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r12;
    // 0x802C62A8: sw          $t9, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r25;
    // 0x802C62AC: sw          $t8, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r24;
    // 0x802C62B0: sw          $t8, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r24;
    // 0x802C62B4: sw          $t7, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r15;
    // 0x802C62B8: sw          $t7, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r15;
    // 0x802C62BC: sw          $t6, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r14;
    // 0x802C62C0: sw          $t6, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r14;
    // 0x802C62C4: sw          $t5, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r13;
    // 0x802C62C8: sw          $t5, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r13;
    // 0x802C62CC: lbu         $a2, 0x6F7B($a2)
    ctx->r6 = MEM_BU(ctx->r6, 0X6F7B);
    // 0x802C62D0: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C62D4: addiu       $a1, $zero, 0xA
    ctx->r5 = ADD32(0, 0XA);
    // 0x802C62D8: jal         0x801E946C
    // 0x802C62DC: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    func_801E946C(rdram, ctx);
        goto after_4;
    // 0x802C62DC: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    after_4:
    // 0x802C62E0: lui         $t9, 0x800E
    ctx->r25 = S32(0X800E << 16);
    // 0x802C62E4: lh          $t9, -0x5498($t9)
    ctx->r25 = MEM_H(ctx->r25, -0X5498);
    // 0x802C62E8: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C62EC: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C62F0: beq         $t9, $zero, L_802C6304
    if (ctx->r25 == 0) {
        // 0x802C62F4: addiu       $t7, $zero, 0x8B
        ctx->r15 = ADD32(0, 0X8B);
            goto L_802C6304;
    }
    // 0x802C62F4: addiu       $t7, $zero, 0x8B
    ctx->r15 = ADD32(0, 0X8B);
    // 0x802C62F8: lui         $v0, 0x802C
    ctx->r2 = S32(0X802C << 16);
    // 0x802C62FC: b           L_802C631C
    // 0x802C6300: addiu       $v0, $v0, 0x6FCC
    ctx->r2 = ADD32(ctx->r2, 0X6FCC);
        goto L_802C631C;
    // 0x802C6300: addiu       $v0, $v0, 0x6FCC
    ctx->r2 = ADD32(ctx->r2, 0X6FCC);
L_802C6304:
    // 0x802C6304: lui         $t4, 0x801D
    ctx->r12 = S32(0X801D << 16);
    // 0x802C6308: lw          $t4, -0x4CC8($t4)
    ctx->r12 = MEM_W(ctx->r12, -0X4CC8);
    // 0x802C630C: lui         $t6, 0x802C
    ctx->r14 = S32(0X802C << 16);
    // 0x802C6310: addiu       $t6, $t6, 0x6FB4
    ctx->r14 = ADD32(ctx->r14, 0X6FB4);
    // 0x802C6314: sll         $t5, $t4, 3
    ctx->r13 = S32(ctx->r12 << 3);
    // 0x802C6318: addu        $v0, $t5, $t6
    ctx->r2 = ADD32(ctx->r13, ctx->r14);
L_802C631C:
    // 0x802C631C: lh          $a3, 0x0($v0)
    ctx->r7 = MEM_H(ctx->r2, 0X0);
    // 0x802C6320: lw          $a2, 0x4($v0)
    ctx->r6 = MEM_W(ctx->r2, 0X4);
    // 0x802C6324: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    // 0x802C6328: sw          $t7, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r15;
    // 0x802C632C: jal         0x801E3EE0
    // 0x802C6330: addiu       $a3, $a3, 0x66
    ctx->r7 = ADD32(ctx->r7, 0X66);
    func_801E3EE0(rdram, ctx);
        goto after_5;
    // 0x802C6330: addiu       $a3, $a3, 0x66
    ctx->r7 = ADD32(ctx->r7, 0X66);
    after_5:
    // 0x802C6334: lw          $ra, 0x3C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X3C);
    // 0x802C6338: addiu       $sp, $sp, 0x40
    ctx->r29 = ADD32(ctx->r29, 0X40);
    // 0x802C633C: jr          $ra
    // 0x802C6340: nop

    return;
    // 0x802C6340: nop

;}
RECOMP_FUNC void func_i3_802C6344(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    { extern void wr64_championship_preview_prepare(uint8_t*, uint32_t); wr64_championship_preview_prepare(rdram, (uint32_t)ctx->r4); }
    // 0x802C6344: lui         $t6, 0x801D
    ctx->r14 = S32(0X801D << 16);
    // 0x802C6348: lw          $t6, -0x4CC8($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X4CC8);
    // 0x802C634C: lui         $a1, 0x802C
    ctx->r5 = S32(0X802C << 16);
    // 0x802C6350: addiu       $a1, $a1, 0x6F64
    ctx->r5 = ADD32(ctx->r5, 0X6F64);
    // 0x802C6354: lui         $t8, 0x802C
    ctx->r24 = S32(0X802C << 16);
    // 0x802C6358: sll         $t7, $t6, 2
    ctx->r15 = S32(ctx->r14 << 2);
    // 0x802C635C: lw          $v0, 0x0($a1)
    ctx->r2 = MEM_W(ctx->r5, 0X0);
    // 0x802C6360: addu        $t8, $t8, $t7
    ctx->r24 = ADD32(ctx->r24, ctx->r15);
    // 0x802C6364: lw          $t8, 0x6FD4($t8)
    ctx->r24 = MEM_W(ctx->r24, 0X6FD4);
    // 0x802C6368: addiu       $sp, $sp, -0x68
    ctx->r29 = ADD32(ctx->r29, -0X68);
    // 0x802C636C: sw          $ra, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r31;
    // 0x802C6370: beq         $v0, $zero, L_802C638C
    if (ctx->r2 == 0) {
        // 0x802C6374: sw          $t8, 0x50($sp)
        MEM_W(0X50, ctx->r29) = ctx->r24;
            goto L_802C638C;
    }
    // 0x802C6374: sw          $t8, 0x50($sp)
    MEM_W(0X50, ctx->r29) = ctx->r24;
    // 0x802C6378: addiu       $t0, $zero, 0x1
    ctx->r8 = ADD32(0, 0X1);
    // 0x802C637C: beq         $v0, $t0, L_802C63C8
    if (ctx->r2 == ctx->r8) {
        // 0x802C6380: nop
    
            goto L_802C63C8;
    }
    // 0x802C6380: nop

    // 0x802C6384: b           L_802C646C
    // 0x802C6388: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
        goto L_802C646C;
    // 0x802C6388: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
L_802C638C:
    // 0x802C638C: lui         $v0, 0x802C
    ctx->r2 = S32(0X802C << 16);
    // 0x802C6390: addiu       $v0, $v0, 0x6F68
    ctx->r2 = ADD32(ctx->r2, 0X6F68);
    // 0x802C6394: lw          $t9, 0x0($v0)
    ctx->r25 = MEM_W(ctx->r2, 0X0);
    // 0x802C6398: addiu       $t8, $zero, 0x1
    ctx->r24 = ADD32(0, 0X1);
    // 0x802C639C: addiu       $t6, $t9, 0x1
    ctx->r14 = ADD32(ctx->r25, 0X1);
    // 0x802C63A0: slti        $at, $t6, 0x14
    ctx->r1 = SIGNED(ctx->r14) < 0X14 ? 1 : 0;
    // 0x802C63A4: bne         $at, $zero, L_802C63B4
    if (ctx->r1 != 0) {
        // 0x802C63A8: sw          $t6, 0x0($v0)
        MEM_W(0X0, ctx->r2) = ctx->r14;
            goto L_802C63B4;
    }
    // 0x802C63A8: sw          $t6, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r14;
    // 0x802C63AC: sw          $t8, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r24;
    // 0x802C63B0: sw          $zero, 0x0($v0)
    MEM_W(0X0, ctx->r2) = 0;
L_802C63B4:
    // 0x802C63B4: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C63B8: sw          $zero, 0x6F6C($at)
    MEM_W(0X6F6C, ctx->r1) = 0;
    // 0x802C63BC: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C63C0: b           L_802C6468
    // 0x802C63C4: sw          $zero, 0x6F70($at)
    MEM_W(0X6F70, ctx->r1) = 0;
        goto L_802C6468;
    // 0x802C63C4: sw          $zero, 0x6F70($at)
    MEM_W(0X6F70, ctx->r1) = 0;
L_802C63C8:
    // 0x802C63C8: lui         $v0, 0x802C
    ctx->r2 = S32(0X802C << 16);
    // 0x802C63CC: addiu       $v0, $v0, 0x6F68
    ctx->r2 = ADD32(ctx->r2, 0X6F68);
    // 0x802C63D0: lw          $t9, 0x0($v0)
    ctx->r25 = MEM_W(ctx->r2, 0X0);
    // 0x802C63D4: addiu       $t7, $zero, 0x2
    ctx->r15 = ADD32(0, 0X2);
    // 0x802C63D8: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C63DC: addiu       $v1, $t9, 0x1
    ctx->r3 = ADD32(ctx->r25, 0X1);
    // 0x802C63E0: slti        $at, $v1, 0x14
    ctx->r1 = SIGNED(ctx->r3) < 0X14 ? 1 : 0;
    // 0x802C63E4: bne         $at, $zero, L_802C641C
    if (ctx->r1 != 0) {
        // 0x802C63E8: sw          $v1, 0x0($v0)
        MEM_W(0X0, ctx->r2) = ctx->r3;
            goto L_802C641C;
    }
    // 0x802C63E8: sw          $v1, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r3;
    // 0x802C63EC: sw          $t7, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r15;
    // 0x802C63F0: sw          $zero, 0x0($v0)
    MEM_W(0X0, ctx->r2) = 0;
    // 0x802C63F4: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C63F8: sw          $t8, 0x6F6C($at)
    MEM_W(0X6F6C, ctx->r1) = ctx->r24;
    // 0x802C63FC: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C6400: addiu       $t9, $zero, 0xAA
    ctx->r25 = ADD32(0, 0XAA);
    // 0x802C6404: sw          $t9, 0x6F70($at)
    MEM_W(0X6F70, ctx->r1) = ctx->r25;
    // 0x802C6408: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C640C: sw          $t0, 0x6F80($at)
    MEM_W(0X6F80, ctx->r1) = ctx->r8;
    // 0x802C6410: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C6414: b           L_802C6468
    // 0x802C6418: sw          $t0, 0x6F84($at)
    MEM_W(0X6F84, ctx->r1) = ctx->r8;
        goto L_802C6468;
    // 0x802C6418: sw          $t0, 0x6F84($at)
    MEM_W(0X6F84, ctx->r1) = ctx->r8;
L_802C641C:
    // 0x802C641C: sll         $t6, $v1, 8
    ctx->r14 = S32(ctx->r3 << 8);
    // 0x802C6420: subu        $t6, $t6, $v1
    ctx->r14 = SUB32(ctx->r14, ctx->r3);
    // 0x802C6424: addiu       $at, $zero, 0x14
    ctx->r1 = ADD32(0, 0X14);
    // 0x802C6428: div         $zero, $t6, $at
    lo = S32(S64(S32(ctx->r14)) / S64(S32(ctx->r1))); hi = S32(S64(S32(ctx->r14)) % S64(S32(ctx->r1)));
    // 0x802C642C: sll         $t8, $v1, 2
    ctx->r24 = S32(ctx->r3 << 2);
    // 0x802C6430: addu        $t8, $t8, $v1
    ctx->r24 = ADD32(ctx->r24, ctx->r3);
    // 0x802C6434: sll         $t8, $t8, 2
    ctx->r24 = S32(ctx->r24 << 2);
    // 0x802C6438: mflo        $t7
    ctx->r15 = lo;
    // 0x802C643C: addu        $t8, $t8, $v1
    ctx->r24 = ADD32(ctx->r24, ctx->r3);
    // 0x802C6440: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C6444: sll         $t8, $t8, 2
    ctx->r24 = S32(ctx->r24 << 2);
    // 0x802C6448: sw          $t7, 0x6F6C($at)
    MEM_W(0X6F6C, ctx->r1) = ctx->r15;
    // 0x802C644C: addu        $t8, $t8, $v1
    ctx->r24 = ADD32(ctx->r24, ctx->r3);
    // 0x802C6450: sll         $t8, $t8, 1
    ctx->r24 = S32(ctx->r24 << 1);
    // 0x802C6454: addiu       $at, $zero, 0x14
    ctx->r1 = ADD32(0, 0X14);
    // 0x802C6458: div         $zero, $t8, $at
    lo = S32(S64(S32(ctx->r24)) / S64(S32(ctx->r1))); hi = S32(S64(S32(ctx->r24)) % S64(S32(ctx->r1)));
    // 0x802C645C: mflo        $t9
    ctx->r25 = lo;
    // 0x802C6460: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C6464: sw          $t9, 0x6F70($at)
    MEM_W(0X6F70, ctx->r1) = ctx->r25;
L_802C6468:
    // 0x802C6468: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
L_802C646C:
    // 0x802C646C: lui         $t7, 0x107
    ctx->r15 = S32(0X107 << 16);
    // 0x802C6470: addiu       $t7, $t7, -0x9D8
    ctx->r15 = ADD32(ctx->r15, -0X9D8);
    // 0x802C6474: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C6478: lui         $t6, 0x600
    ctx->r14 = S32(0X600 << 16);
    // 0x802C647C: sw          $t6, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r14;
    // 0x802C6480: sw          $t7, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r15;
    // 0x802C6484: or          $v1, $a0, $zero
    ctx->r3 = ctx->r4 | 0;
    // 0x802C6488: lui         $t8, 0xFA00
    ctx->r24 = S32(0XFA00 << 16);
    // 0x802C648C: sw          $t8, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r24;
    // 0x802C6490: lui         $t9, 0x802C
    ctx->r25 = S32(0X802C << 16);
    // 0x802C6494: lw          $t9, 0x6F70($t9)
    ctx->r25 = MEM_W(ctx->r25, 0X6F70);
    // 0x802C6498: addiu       $at, $zero, -0x100
    ctx->r1 = ADD32(0, -0X100);
    // 0x802C649C: addiu       $t8, $zero, 0x170
    ctx->r24 = ADD32(0, 0X170);
    // 0x802C64A0: andi        $t6, $t9, 0xFF
    ctx->r14 = ctx->r25 & 0XFF;
    // 0x802C64A4: or          $t7, $t6, $at
    ctx->r15 = ctx->r14 | ctx->r1;
    // 0x802C64A8: sw          $t7, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r15;
    // 0x802C64AC: addiu       $t9, $zero, 0x18
    ctx->r25 = ADD32(0, 0X18);
    // 0x802C64B0: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C64B4: sw          $t9, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r25;
    // 0x802C64B8: sw          $t8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r24;
    // 0x802C64BC: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C64C0: addiu       $a2, $zero, 0x1C
    ctx->r6 = ADD32(0, 0X1C);
    // 0x802C64C4: jal         0x80094338
    // 0x802C64C8: addiu       $a3, $zero, 0x1E
    ctx->r7 = ADD32(0, 0X1E);
    func_80094338(rdram, ctx);
        goto after_0;
    // 0x802C64C8: addiu       $a3, $zero, 0x1E
    ctx->r7 = ADD32(0, 0X1E);
    after_0:
    // 0x802C64CC: addiu       $t6, $zero, 0x69
    ctx->r14 = ADD32(0, 0X69);
    // 0x802C64D0: addiu       $t7, $zero, 0xC
    ctx->r15 = ADD32(0, 0XC);
    // 0x802C64D4: sw          $t7, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r15;
    // 0x802C64D8: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x802C64DC: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C64E0: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C64E4: addiu       $a2, $zero, 0x123
    ctx->r6 = ADD32(0, 0X123);
    // 0x802C64E8: jal         0x80094338
    // 0x802C64EC: addiu       $a3, $zero, 0x3C
    ctx->r7 = ADD32(0, 0X3C);
    func_80094338(rdram, ctx);
        goto after_1;
    // 0x802C64EC: addiu       $a3, $zero, 0x3C
    ctx->r7 = ADD32(0, 0X3C);
    after_1:
    // 0x802C64F0: addiu       $t8, $zero, 0x69
    ctx->r24 = ADD32(0, 0X69);
    // 0x802C64F4: addiu       $t9, $zero, 0xC
    ctx->r25 = ADD32(0, 0XC);
    // 0x802C64F8: sw          $t9, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r25;
    // 0x802C64FC: sw          $t8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r24;
    // 0x802C6500: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C6504: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C6508: addiu       $a2, $zero, 0x123
    ctx->r6 = ADD32(0, 0X123);
    // 0x802C650C: jal         0x80094338
    // 0x802C6510: addiu       $a3, $zero, 0x56
    ctx->r7 = ADD32(0, 0X56);
    func_80094338(rdram, ctx);
        goto after_2;
    // 0x802C6510: addiu       $a3, $zero, 0x56
    ctx->r7 = ADD32(0, 0X56);
    after_2:
    // 0x802C6514: addiu       $t6, $zero, 0x69
    ctx->r14 = ADD32(0, 0X69);
    // 0x802C6518: addiu       $t7, $zero, 0x16
    ctx->r15 = ADD32(0, 0X16);
    // 0x802C651C: sw          $t7, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r15;
    // 0x802C6520: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x802C6524: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C6528: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C652C: addiu       $a2, $zero, 0x123
    ctx->r6 = ADD32(0, 0X123);
    // 0x802C6530: jal         0x80094338
    // 0x802C6534: addiu       $a3, $zero, 0x63
    ctx->r7 = ADD32(0, 0X63);
    func_80094338(rdram, ctx);
        goto after_3;
    // 0x802C6534: addiu       $a3, $zero, 0x63
    ctx->r7 = ADD32(0, 0X63);
    after_3:
    // 0x802C6538: addiu       $t8, $zero, 0x69
    ctx->r24 = ADD32(0, 0X69);
    // 0x802C653C: addiu       $t9, $zero, 0xC
    ctx->r25 = ADD32(0, 0XC);
    // 0x802C6540: sw          $t9, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r25;
    // 0x802C6544: sw          $t8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r24;
    // 0x802C6548: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C654C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C6550: addiu       $a2, $zero, 0x123
    ctx->r6 = ADD32(0, 0X123);
    // 0x802C6554: jal         0x80094338
    // 0x802C6558: addiu       $a3, $zero, 0x86
    ctx->r7 = ADD32(0, 0X86);
    func_80094338(rdram, ctx);
        goto after_4;
    // 0x802C6558: addiu       $a3, $zero, 0x86
    ctx->r7 = ADD32(0, 0X86);
    after_4:
    // 0x802C655C: addiu       $t6, $zero, 0x69
    ctx->r14 = ADD32(0, 0X69);
    // 0x802C6560: addiu       $t7, $zero, 0x16
    ctx->r15 = ADD32(0, 0X16);
    // 0x802C6564: sw          $t7, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r15;
    // 0x802C6568: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x802C656C: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C6570: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C6574: addiu       $a2, $zero, 0x123
    ctx->r6 = ADD32(0, 0X123);
    // 0x802C6578: jal         0x80094338
    // 0x802C657C: addiu       $a3, $zero, 0x93
    ctx->r7 = ADD32(0, 0X93);
    func_80094338(rdram, ctx);
        goto after_5;
    // 0x802C657C: addiu       $a3, $zero, 0x93
    ctx->r7 = ADD32(0, 0X93);
    after_5:
    // 0x802C6580: addiu       $t8, $zero, 0x127
    ctx->r24 = ADD32(0, 0X127);
    // 0x802C6584: addiu       $t9, $zero, 0x22
    ctx->r25 = ADD32(0, 0X22);
    // 0x802C6588: sw          $t9, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r25;
    // 0x802C658C: sw          $t8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r24;
    // 0x802C6590: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C6594: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C6598: addiu       $a2, $zero, 0x1C
    ctx->r6 = ADD32(0, 0X1C);
    // 0x802C659C: jal         0x80094338
    // 0x802C65A0: addiu       $a3, $zero, 0xB0
    ctx->r7 = ADD32(0, 0XB0);
    func_80094338(rdram, ctx);
        goto after_6;
    // 0x802C65A0: addiu       $a3, $zero, 0xB0
    ctx->r7 = ADD32(0, 0XB0);
    after_6:
    // 0x802C65A4: addiu       $t6, $zero, 0x46
    ctx->r14 = ADD32(0, 0X46);
    // 0x802C65A8: addiu       $t7, $zero, 0x22
    ctx->r15 = ADD32(0, 0X22);
    // 0x802C65AC: sw          $t7, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r15;
    // 0x802C65B0: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x802C65B4: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C65B8: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C65BC: addiu       $a2, $zero, 0x146
    ctx->r6 = ADD32(0, 0X146);
    // 0x802C65C0: jal         0x80094338
    // 0x802C65C4: addiu       $a3, $zero, 0xB0
    ctx->r7 = ADD32(0, 0XB0);
    func_80094338(rdram, ctx);
        goto after_7;
    // 0x802C65C4: addiu       $a3, $zero, 0xB0
    ctx->r7 = ADD32(0, 0XB0);
    after_7:
    // 0x802C65C8: lui         $t9, 0x805
    ctx->r25 = S32(0X805 << 16);
    // 0x802C65CC: addiu       $t9, $t9, -0x1B20
    ctx->r25 = ADD32(ctx->r25, -0X1B20);
    // 0x802C65D0: lui         $t8, 0x600
    ctx->r24 = S32(0X600 << 16);
    // 0x802C65D4: sw          $t8, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r24;
    // 0x802C65D8: sw          $t9, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r25;
    // 0x802C65DC: lui         $t7, 0x802C
    ctx->r15 = S32(0X802C << 16);
    // 0x802C65E0: lw          $t7, 0x6F70($t7)
    ctx->r15 = MEM_W(ctx->r15, 0X6F70);
    // 0x802C65E4: addiu       $t6, $zero, 0xA7
    ctx->r14 = ADD32(0, 0XA7);
    // 0x802C65E8: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x802C65EC: sw          $zero, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = 0;
    // 0x802C65F0: sw          $zero, 0x18($sp)
    MEM_W(0X18, ctx->r29) = 0;
    // 0x802C65F4: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    // 0x802C65F8: addiu       $a0, $v0, 0x8
    ctx->r4 = ADD32(ctx->r2, 0X8);
    // 0x802C65FC: addiu       $a1, $zero, 0x1F
    ctx->r5 = ADD32(0, 0X1F);
    // 0x802C6600: addiu       $a2, $zero, 0x3F
    ctx->r6 = ADD32(0, 0X3F);
    // 0x802C6604: addiu       $a3, $zero, 0xB4
    ctx->r7 = ADD32(0, 0XB4);
    // 0x802C6608: jal         0x801E7C58
    // 0x802C660C: sw          $t7, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r15;
    func_801E7C58(rdram, ctx);
        goto after_8;
    // 0x802C660C: sw          $t7, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r15;
    after_8:
    // 0x802C6610: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C6614: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C6618: lui         $a2, 0x802C
    ctx->r6 = S32(0X802C << 16);
    // 0x802C661C: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C6620: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C6624: sw          $t7, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r15;
    // 0x802C6628: sw          $t7, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r15;
    // 0x802C662C: sw          $t6, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r14;
    // 0x802C6630: sw          $t6, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r14;
    // 0x802C6634: lbu         $a2, 0x6F6F($a2)
    ctx->r6 = MEM_BU(ctx->r6, 0X6F6F);
    // 0x802C6638: sw          $t9, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r25;
    // 0x802C663C: sw          $t9, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r25;
    // 0x802C6640: sw          $t9, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r25;
    // 0x802C6644: sw          $t8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r24;
    // 0x802C6648: sw          $t8, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r24;
    // 0x802C664C: sw          $t8, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r24;
    // 0x802C6650: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C6654: addiu       $a1, $zero, 0xA
    ctx->r5 = ADD32(0, 0XA);
    // 0x802C6658: jal         0x801E946C
    // 0x802C665C: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    func_801E946C(rdram, ctx);
        goto after_9;
    // 0x802C665C: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    after_9:
    // 0x802C6660: lui         $t6, 0x801D
    ctx->r14 = S32(0X801D << 16);
    // 0x802C6664: lw          $t6, -0x4CC8($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X4CC8);
    // 0x802C6668: lui         $a1, 0x801D
    ctx->r5 = S32(0X801D << 16);
    // 0x802C666C: lw          $a1, -0x4CCC($a1)
    ctx->r5 = MEM_W(ctx->r5, -0X4CCC);
    // 0x802C6670: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C6674: bne         $t6, $zero, L_802C6680
    if (ctx->r14 != 0) {
        // 0x802C6678: or          $t0, $a1, $zero
        ctx->r8 = ctx->r5 | 0;
            goto L_802C6680;
    }
    // 0x802C6678: or          $t0, $a1, $zero
    ctx->r8 = ctx->r5 | 0;
    // 0x802C667C: addiu       $t0, $t0, -0x1
    ctx->r8 = ADD32(ctx->r8, -0X1);
L_802C6680:
    // 0x802C6680: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x802C6684: lw          $v1, -0x4CD0($v1)
    ctx->r3 = MEM_W(ctx->r3, -0X4CD0);
    // 0x802C6688: bne         $v1, $zero, L_802C6698
    if (ctx->r3 != 0) {
        // 0x802C668C: addiu       $t7, $zero, -0x55
        ctx->r15 = ADD32(0, -0X55);
            goto L_802C6698;
    }
    // 0x802C668C: addiu       $t7, $zero, -0x55
    ctx->r15 = ADD32(0, -0X55);
    // 0x802C6690: b           L_802C66F0
    // 0x802C6694: sw          $t7, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r15;
        goto L_802C66F0;
    // 0x802C6694: sw          $t7, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r15;
L_802C6698:
    // 0x802C6698: bltz        $t0, L_802C66F0
    if (SIGNED(ctx->r8) < 0) {
        // 0x802C669C: lw          $t8, 0x50($sp)
        ctx->r24 = MEM_W(ctx->r29, 0X50);
            goto L_802C66F0;
    }
    // 0x802C669C: lw          $t8, 0x50($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X50);
    // 0x802C66A0: bne         $t8, $a1, L_802C66B8
    if (ctx->r24 != ctx->r5) {
        // 0x802C66A4: lui         $a2, 0x802C
        ctx->r6 = S32(0X802C << 16);
            goto L_802C66B8;
    }
    // 0x802C66A4: lui         $a2, 0x802C
    ctx->r6 = S32(0X802C << 16);
    // 0x802C66A8: addiu       $t9, $zero, 0x16
    ctx->r25 = ADD32(0, 0X16);
    // 0x802C66AC: addiu       $t0, $zero, 0x8
    ctx->r8 = ADD32(0, 0X8);
    // 0x802C66B0: b           L_802C66BC
    // 0x802C66B4: sw          $t9, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r25;
        goto L_802C66BC;
    // 0x802C66B4: sw          $t9, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r25;
L_802C66B8:
    // 0x802C66B8: sw          $zero, 0x48($sp)
    MEM_W(0X48, ctx->r29) = 0;
L_802C66BC:
    // 0x802C66BC: sll         $t6, $t0, 2
    ctx->r14 = S32(ctx->r8 << 2);
    // 0x802C66C0: addu        $a2, $a2, $t6
    ctx->r6 = ADD32(ctx->r6, ctx->r14);
    // 0x802C66C4: addiu       $t7, $zero, 0x25
    ctx->r15 = ADD32(0, 0X25);
    // 0x802C66C8: addiu       $t8, $zero, 0x1
    ctx->r24 = ADD32(0, 0X1);
    // 0x802C66CC: sw          $t8, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r24;
    // 0x802C66D0: sw          $t7, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r15;
    // 0x802C66D4: lw          $a2, 0x6F90($a2)
    ctx->r6 = MEM_W(ctx->r6, 0X6F90);
    // 0x802C66D8: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C66DC: jal         0x801E3EE0
    // 0x802C66E0: addiu       $a3, $zero, 0x25
    ctx->r7 = ADD32(0, 0X25);
    func_801E3EE0(rdram, ctx);
        goto after_10;
    // 0x802C66E0: addiu       $a3, $zero, 0x25
    ctx->r7 = ADD32(0, 0X25);
    after_10:
    // 0x802C66E4: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x802C66E8: lw          $v1, -0x4CD0($v1)
    ctx->r3 = MEM_W(ctx->r3, -0X4CD0);
    // 0x802C66EC: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
L_802C66F0:
    // 0x802C66F0: lw          $a3, 0x48($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X48);
    // 0x802C66F4: sll         $t9, $v1, 2
    ctx->r25 = S32(ctx->r3 << 2);
    // 0x802C66F8: lui         $a2, 0x800E
    ctx->r6 = S32(0X800E << 16);
    // 0x802C66FC: addu        $a2, $a2, $t9
    ctx->r6 = ADD32(ctx->r6, ctx->r25);
    // 0x802C6700: addiu       $t6, $zero, 0x21
    ctx->r14 = ADD32(0, 0X21);
    // 0x802C6704: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x802C6708: lw          $a2, -0x55CC($a2)
    ctx->r6 = MEM_W(ctx->r6, -0X55CC);
    // 0x802C670C: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C6710: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    // 0x802C6714: jal         0x801E3EE0
    // 0x802C6718: addiu       $a3, $a3, 0xCF
    ctx->r7 = ADD32(ctx->r7, 0XCF);
    func_801E3EE0(rdram, ctx);
        goto after_11;
    // 0x802C6718: addiu       $a3, $a3, 0xCF
    ctx->r7 = ADD32(ctx->r7, 0XCF);
    after_11:
    // 0x802C671C: addiu       $t7, $zero, 0x3E
    ctx->r15 = ADD32(0, 0X3E);
    // 0x802C6720: sw          $t7, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r15;
    // 0x802C6724: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C6728: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C672C: addiu       $a2, $zero, 0x16
    ctx->r6 = ADD32(0, 0X16);
    // 0x802C6730: addiu       $a3, $zero, 0x12B
    ctx->r7 = ADD32(0, 0X12B);
    // 0x802C6734: jal         0x801E3EE0
    // 0x802C6738: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    func_801E3EE0(rdram, ctx);
        goto after_12;
    // 0x802C6738: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    after_12:
    // 0x802C673C: addiu       $t8, $zero, 0x58
    ctx->r24 = ADD32(0, 0X58);
    // 0x802C6740: sw          $t8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r24;
    // 0x802C6744: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C6748: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C674C: addiu       $a2, $zero, 0xE
    ctx->r6 = ADD32(0, 0XE);
    // 0x802C6750: addiu       $a3, $zero, 0x13C
    ctx->r7 = ADD32(0, 0X13C);
    // 0x802C6754: jal         0x801E3EE0
    // 0x802C6758: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    func_801E3EE0(rdram, ctx);
        goto after_13;
    // 0x802C6758: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    after_13:
    // 0x802C675C: addiu       $t9, $zero, 0x88
    ctx->r25 = ADD32(0, 0X88);
    // 0x802C6760: sw          $t9, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r25;
    // 0x802C6764: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C6768: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C676C: addiu       $a2, $zero, 0xD
    ctx->r6 = ADD32(0, 0XD);
    // 0x802C6770: addiu       $a3, $zero, 0x13C
    ctx->r7 = ADD32(0, 0X13C);
    // 0x802C6774: jal         0x801E3EE0
    // 0x802C6778: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    func_801E3EE0(rdram, ctx);
        goto after_14;
    // 0x802C6778: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    after_14:
    // 0x802C677C: addiu       $t6, $zero, 0xB5
    ctx->r14 = ADD32(0, 0XB5);
    // 0x802C6780: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C6784: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x802C6788: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C678C: addiu       $a2, $zero, 0x6
    ctx->r6 = ADD32(0, 0X6);
    // 0x802C6790: addiu       $a3, $zero, 0x22
    ctx->r7 = ADD32(0, 0X22);
    // 0x802C6794: jal         0x801E3EE0
    // 0x802C6798: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    func_801E3EE0(rdram, ctx);
        goto after_15;
    // 0x802C6798: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    after_15:
    // 0x802C679C: addiu       $t7, $zero, 0xC2
    ctx->r15 = ADD32(0, 0XC2);
    // 0x802C67A0: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C67A4: sw          $t7, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r15;
    // 0x802C67A8: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C67AC: addiu       $a2, $zero, 0x7
    ctx->r6 = ADD32(0, 0X7);
    // 0x802C67B0: addiu       $a3, $zero, 0x22
    ctx->r7 = ADD32(0, 0X22);
    // 0x802C67B4: jal         0x801E3EE0
    // 0x802C67B8: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    func_801E3EE0(rdram, ctx);
        goto after_16;
    // 0x802C67B8: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    after_16:
    // 0x802C67BC: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x802C67C0: lw          $v1, -0x4CD0($v1)
    ctx->r3 = MEM_W(ctx->r3, -0X4CD0);
    // 0x802C67C4: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C67C8: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C67CC: bne         $v1, $zero, L_802C6814
    if (ctx->r3 != 0) {
        // 0x802C67D0: lui         $t6, 0x800E
        ctx->r14 = S32(0X800E << 16);
            goto L_802C6814;
    }
    // 0x802C67D0: lui         $t6, 0x800E
    ctx->r14 = S32(0X800E << 16);
    // 0x802C67D4: lui         $a2, 0x802C
    ctx->r6 = S32(0X802C << 16);
    // 0x802C67D8: addiu       $t8, $zero, 0x69
    ctx->r24 = ADD32(0, 0X69);
    // 0x802C67DC: sw          $t8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r24;
    // 0x802C67E0: addiu       $a2, $a2, 0x6FF0
    ctx->r6 = ADD32(ctx->r6, 0X6FF0);
    // 0x802C67E4: jal         0x801E9858
    // 0x802C67E8: addiu       $a3, $zero, 0x133
    ctx->r7 = ADD32(0, 0X133);
    func_801E9858(rdram, ctx);
        goto after_17;
    // 0x802C67E8: addiu       $a3, $zero, 0x133
    ctx->r7 = ADD32(0, 0X133);
    after_17:
    // 0x802C67EC: lui         $a2, 0x802C
    ctx->r6 = S32(0X802C << 16);
    // 0x802C67F0: addiu       $t9, $zero, 0x99
    ctx->r25 = ADD32(0, 0X99);
    // 0x802C67F4: sw          $t9, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r25;
    // 0x802C67F8: addiu       $a2, $a2, 0x6FFC
    ctx->r6 = ADD32(ctx->r6, 0X6FFC);
    // 0x802C67FC: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C6800: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C6804: jal         0x801E9858
    // 0x802C6808: addiu       $a3, $zero, 0x133
    ctx->r7 = ADD32(0, 0X133);
    func_801E9858(rdram, ctx);
        goto after_18;
    // 0x802C6808: addiu       $a3, $zero, 0x133
    ctx->r7 = ADD32(0, 0X133);
    after_18:
    // 0x802C680C: b           L_802C68D8
    // 0x802C6810: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
        goto L_802C68D8;
    // 0x802C6810: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
L_802C6814:
    // 0x802C6814: lh          $t6, -0x5498($t6)
    ctx->r14 = MEM_H(ctx->r14, -0X5498);
    // 0x802C6818: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C681C: lui         $a2, 0x801C
    ctx->r6 = S32(0X801C << 16);
    // 0x802C6820: beq         $t6, $zero, L_802C687C
    if (ctx->r14 == 0) {
        // 0x802C6824: addiu       $a3, $zero, 0x133
        ctx->r7 = ADD32(0, 0X133);
            goto L_802C687C;
    }
    // 0x802C6824: addiu       $a3, $zero, 0x133
    ctx->r7 = ADD32(0, 0X133);
    // 0x802C6828: sll         $t7, $v1, 2
    ctx->r15 = S32(ctx->r3 << 2);
    // 0x802C682C: addu        $t7, $t7, $v1
    ctx->r15 = ADD32(ctx->r15, ctx->r3);
    // 0x802C6830: sll         $t7, $t7, 2
    ctx->r15 = S32(ctx->r15 << 2);
    // 0x802C6834: lui         $a2, 0x801C
    ctx->r6 = S32(0X801C << 16);
    // 0x802C6838: addu        $a2, $a2, $t7
    ctx->r6 = ADD32(ctx->r6, ctx->r15);
    // 0x802C683C: addiu       $t8, $zero, 0x69
    ctx->r24 = ADD32(0, 0X69);
    // 0x802C6840: sw          $t8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r24;
    // 0x802C6844: lw          $a2, 0x23B0($a2)
    ctx->r6 = MEM_W(ctx->r6, 0X23B0);
    // 0x802C6848: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C684C: jal         0x801E8B24
    // 0x802C6850: addiu       $a3, $zero, 0x133
    ctx->r7 = ADD32(0, 0X133);
    func_801E8B24(rdram, ctx);
        goto after_19;
    // 0x802C6850: addiu       $a3, $zero, 0x133
    ctx->r7 = ADD32(0, 0X133);
    after_19:
    // 0x802C6854: lui         $a2, 0x802C
    ctx->r6 = S32(0X802C << 16);
    // 0x802C6858: addiu       $t9, $zero, 0x99
    ctx->r25 = ADD32(0, 0X99);
    // 0x802C685C: sw          $t9, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r25;
    // 0x802C6860: addiu       $a2, $a2, 0x7008
    ctx->r6 = ADD32(ctx->r6, 0X7008);
    // 0x802C6864: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C6868: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C686C: jal         0x801E9858
    // 0x802C6870: addiu       $a3, $zero, 0x133
    ctx->r7 = ADD32(0, 0X133);
    func_801E9858(rdram, ctx);
        goto after_20;
    // 0x802C6870: addiu       $a3, $zero, 0x133
    ctx->r7 = ADD32(0, 0X133);
    after_20:
    // 0x802C6874: b           L_802C68D8
    // 0x802C6878: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
        goto L_802C68D8;
    // 0x802C6878: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
L_802C687C:
    // 0x802C687C: sll         $t6, $v1, 4
    ctx->r14 = S32(ctx->r3 << 4);
    // 0x802C6880: subu        $t6, $t6, $v1
    ctx->r14 = SUB32(ctx->r14, ctx->r3);
    // 0x802C6884: sll         $t6, $t6, 2
    ctx->r14 = S32(ctx->r14 << 2);
    // 0x802C6888: addu        $a2, $a2, $t6
    ctx->r6 = ADD32(ctx->r6, ctx->r14);
    // 0x802C688C: addiu       $t7, $zero, 0x69
    ctx->r15 = ADD32(0, 0X69);
    // 0x802C6890: sw          $t7, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r15;
    // 0x802C6894: jal         0x801E8B24
    // 0x802C6898: lw          $a2, 0x1FF0($a2)
    ctx->r6 = MEM_W(ctx->r6, 0X1FF0);
    func_801E8B24(rdram, ctx);
        goto after_21;
    // 0x802C6898: lw          $a2, 0x1FF0($a2)
    ctx->r6 = MEM_W(ctx->r6, 0X1FF0);
    after_21:
    // 0x802C689C: lui         $t8, 0x801D
    ctx->r24 = S32(0X801D << 16);
    // 0x802C68A0: lw          $t8, -0x4CD0($t8)
    ctx->r24 = MEM_W(ctx->r24, -0X4CD0);
    // 0x802C68A4: lui         $a2, 0x801C
    ctx->r6 = S32(0X801C << 16);
    // 0x802C68A8: addiu       $t6, $zero, 0x99
    ctx->r14 = ADD32(0, 0X99);
    // 0x802C68AC: sll         $t9, $t8, 2
    ctx->r25 = S32(ctx->r24 << 2);
    // 0x802C68B0: addu        $t9, $t9, $t8
    ctx->r25 = ADD32(ctx->r25, ctx->r24);
    // 0x802C68B4: sll         $t9, $t9, 2
    ctx->r25 = S32(ctx->r25 << 2);
    // 0x802C68B8: addu        $a2, $a2, $t9
    ctx->r6 = ADD32(ctx->r6, ctx->r25);
    // 0x802C68BC: lw          $a2, 0x22C0($a2)
    ctx->r6 = MEM_W(ctx->r6, 0X22C0);
    // 0x802C68C0: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x802C68C4: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C68C8: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C68CC: jal         0x801E8B24
    // 0x802C68D0: addiu       $a3, $zero, 0x133
    ctx->r7 = ADD32(0, 0X133);
    func_801E8B24(rdram, ctx);
        goto after_22;
    // 0x802C68D0: addiu       $a3, $zero, 0x133
    ctx->r7 = ADD32(0, 0X133);
    after_22:
    // 0x802C68D4: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
L_802C68D8:
    // 0x802C68D8: lui         $t7, 0x800D
    ctx->r15 = S32(0X800D << 16);
    // 0x802C68DC: lw          $t7, 0x48DC($t7)
    ctx->r15 = MEM_W(ctx->r15, 0X48DC);
    // 0x802C68E0: lui         $a2, 0x801D
    ctx->r6 = S32(0X801D << 16);
    // 0x802C68E4: addiu       $t9, $zero, 0xC2
    ctx->r25 = ADD32(0, 0XC2);
    // 0x802C68E8: sll         $t8, $t7, 2
    ctx->r24 = S32(ctx->r15 << 2);
    // 0x802C68EC: addu        $a2, $a2, $t8
    ctx->r6 = ADD32(ctx->r6, ctx->r24);
    // 0x802C68F0: lw          $a2, -0x4CC0($a2)
    ctx->r6 = MEM_W(ctx->r6, -0X4CC0);
    // 0x802C68F4: sw          $t9, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r25;
    // 0x802C68F8: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C68FC: jal         0x801EB00C
    // 0x802C6900: addiu       $a3, $zero, 0x132
    ctx->r7 = ADD32(0, 0X132);
    func_801EB00C(rdram, ctx);
        goto after_23;
    // 0x802C6900: addiu       $a3, $zero, 0x132
    ctx->r7 = ADD32(0, 0X132);
    after_23:
    // 0x802C6904: lui         $t6, 0x802C
    ctx->r14 = S32(0X802C << 16);
    // 0x802C6908: lw          $t6, 0x6FE0($t6)
    ctx->r14 = MEM_W(ctx->r14, 0X6FE0);
    // 0x802C690C: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C6910: addiu       $a1, $zero, 0xA
    ctx->r5 = ADD32(0, 0XA);
    // 0x802C6914: beq         $t6, $zero, L_802C696C
    if (ctx->r14 == 0) {
        // 0x802C6918: lui         $a2, 0x802C
        ctx->r6 = S32(0X802C << 16);
            goto L_802C696C;
    }
    // 0x802C6918: lui         $a2, 0x802C
    ctx->r6 = S32(0X802C << 16);
    // 0x802C691C: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C6920: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C6924: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C6928: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C692C: sw          $t6, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r14;
    // 0x802C6930: sw          $t6, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r14;
    // 0x802C6934: sw          $t9, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r25;
    // 0x802C6938: sw          $t9, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r25;
    // 0x802C693C: sw          $t8, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r24;
    // 0x802C6940: sw          $t8, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r24;
    // 0x802C6944: sw          $t8, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r24;
    // 0x802C6948: sw          $t7, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r15;
    // 0x802C694C: sw          $t7, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r15;
    // 0x802C6950: sw          $t7, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r15;
    // 0x802C6954: addiu       $a1, $zero, 0x6
    ctx->r5 = ADD32(0, 0X6);
    // 0x802C6958: addiu       $a2, $zero, 0xFF
    ctx->r6 = ADD32(0, 0XFF);
    // 0x802C695C: jal         0x801E946C
    // 0x802C6960: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    func_801E946C(rdram, ctx);
        goto after_24;
    // 0x802C6960: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    after_24:
    // 0x802C6964: b           L_802C69B4
    // 0x802C6968: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
        goto L_802C69B4;
    // 0x802C6968: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
L_802C696C:
    // 0x802C696C: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C6970: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C6974: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C6978: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C697C: sw          $t8, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r24;
    // 0x802C6980: sw          $t8, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r24;
    // 0x802C6984: sw          $t7, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r15;
    // 0x802C6988: sw          $t7, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r15;
    // 0x802C698C: sw          $t6, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r14;
    // 0x802C6990: sw          $t6, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r14;
    // 0x802C6994: sw          $t6, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r14;
    // 0x802C6998: sw          $t9, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r25;
    // 0x802C699C: sw          $t9, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r25;
    // 0x802C69A0: sw          $t9, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r25;
    // 0x802C69A4: lbu         $a2, 0x6F6F($a2)
    ctx->r6 = MEM_BU(ctx->r6, 0X6F6F);
    // 0x802C69A8: jal         0x801E946C
    // 0x802C69AC: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    func_801E946C(rdram, ctx);
        goto after_25;
    // 0x802C69AC: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    after_25:
    // 0x802C69B0: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
L_802C69B4:
    // 0x802C69B4: lui         $t7, 0x801D
    ctx->r15 = S32(0X801D << 16);
    // 0x802C69B8: lui         $t9, 0x801D
    ctx->r25 = S32(0X801D << 16);
    // 0x802C69BC: lw          $t9, -0x4CCC($t9)
    ctx->r25 = MEM_W(ctx->r25, -0X4CCC);
    // 0x802C69C0: lw          $t7, -0x4CC8($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X4CC8);
    // 0x802C69C4: lui         $a2, 0x800F
    ctx->r6 = S32(0X800F << 16);
    // 0x802C69C8: sll         $t6, $t9, 1
    ctx->r14 = S32(ctx->r25 << 1);
    // 0x802C69CC: sll         $t8, $t7, 4
    ctx->r24 = S32(ctx->r15 << 4);
    // 0x802C69D0: addu        $t7, $t8, $t6
    ctx->r15 = ADD32(ctx->r24, ctx->r14);
    // 0x802C69D4: addu        $a2, $a2, $t7
    ctx->r6 = ADD32(ctx->r6, ctx->r15);
    // 0x802C69D8: addiu       $t9, $zero, 0xB5
    ctx->r25 = ADD32(0, 0XB5);
    // 0x802C69DC: sw          $t9, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r25;
    // 0x802C69E0: lh          $a2, -0x5444($a2)
    ctx->r6 = MEM_H(ctx->r6, -0X5444);
    // 0x802C69E4: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C69E8: jal         0x801EB00C
    // 0x802C69EC: addiu       $a3, $zero, 0x132
    ctx->r7 = ADD32(0, 0X132);
    func_801EB00C(rdram, ctx);
        goto after_26;
    // 0x802C69EC: addiu       $a3, $zero, 0x132
    ctx->r7 = ADD32(0, 0X132);
    after_26:
    // 0x802C69F0: lui         $t8, 0xFD70
    ctx->r24 = S32(0XFD70 << 16);
    // 0x802C69F4: sw          $t8, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r24;
    // 0x802C69F8: lui         $t6, 0x801D
    ctx->r14 = S32(0X801D << 16);
    // 0x802C69FC: lw          $t6, -0x18FC($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X18FC);
    // 0x802C6A00: lui         $t9, 0x802C
    ctx->r25 = S32(0X802C << 16);
    // 0x802C6A04: addiu       $a0, $v0, 0x8
    ctx->r4 = ADD32(ctx->r2, 0X8);
    // 0x802C6A08: sll         $t7, $t6, 2
    ctx->r15 = S32(ctx->r14 << 2);
    // 0x802C6A0C: addu        $t9, $t9, $t7
    ctx->r25 = ADD32(ctx->r25, ctx->r15);
    // 0x802C6A10: lw          $t9, 0x6F50($t9)
    ctx->r25 = MEM_W(ctx->r25, 0X6F50);
    // 0x802C6A14: or          $a1, $a0, $zero
    ctx->r5 = ctx->r4 | 0;
    // 0x802C6A18: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C6A1C: sw          $t9, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r25;
    // 0x802C6A20: lui         $t6, 0x708
    ctx->r14 = S32(0X708 << 16);
    // 0x802C6A24: lui         $t8, 0xF570
    ctx->r24 = S32(0XF570 << 16);
    // 0x802C6A28: sw          $t8, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r24;
    // 0x802C6A2C: ori         $t6, $t6, 0x200
    ctx->r14 = ctx->r14 | 0X200;
    // 0x802C6A30: or          $a2, $a0, $zero
    ctx->r6 = ctx->r4 | 0;
    // 0x802C6A34: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C6A38: sw          $t6, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r14;
    // 0x802C6A3C: or          $a3, $a0, $zero
    ctx->r7 = ctx->r4 | 0;
    // 0x802C6A40: lui         $t7, 0xE600
    ctx->r15 = S32(0XE600 << 16);
    // 0x802C6A44: sw          $t7, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r15;
    // 0x802C6A48: sw          $zero, 0x4($a2)
    MEM_W(0X4, ctx->r6) = 0;
    // 0x802C6A4C: lui         $t8, 0x72B
    ctx->r24 = S32(0X72B << 16);
    // 0x802C6A50: ori         $t8, $t8, 0xF100
    ctx->r24 = ctx->r24 | 0XF100;
    // 0x802C6A54: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C6A58: lui         $t9, 0xF300
    ctx->r25 = S32(0XF300 << 16);
    // 0x802C6A5C: sw          $t9, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r25;
    // 0x802C6A60: or          $t0, $a0, $zero
    ctx->r8 = ctx->r4 | 0;
    // 0x802C6A64: sw          $t8, 0x4($a3)
    MEM_W(0X4, ctx->r7) = ctx->r24;
    // 0x802C6A68: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C6A6C: lui         $ra, 0xE700
    ctx->r31 = S32(0XE700 << 16);
    // 0x802C6A70: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x802C6A74: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C6A78: sw          $ra, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r31;
    // 0x802C6A7C: sw          $zero, 0x4($t0)
    MEM_W(0X4, ctx->r8) = 0;
    // 0x802C6A80: lui         $t7, 0x8
    ctx->r15 = S32(0X8 << 16);
    // 0x802C6A84: lui         $t6, 0xF568
    ctx->r14 = S32(0XF568 << 16);
    // 0x802C6A88: ori         $t6, $t6, 0x1000
    ctx->r14 = ctx->r14 | 0X1000;
    // 0x802C6A8C: ori         $t7, $t7, 0x200
    ctx->r15 = ctx->r15 | 0X200;
    // 0x802C6A90: or          $v1, $a0, $zero
    ctx->r3 = ctx->r4 | 0;
    // 0x802C6A94: sw          $t7, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r15;
    // 0x802C6A98: sw          $t6, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r14;
    // 0x802C6A9C: lui         $t8, 0xF
    ctx->r24 = S32(0XF << 16);
    // 0x802C6AA0: ori         $t8, $t8, 0xC054
    ctx->r24 = ctx->r24 | 0XC054;
    // 0x802C6AA4: lui         $t9, 0xF200
    ctx->r25 = S32(0XF200 << 16);
    // 0x802C6AA8: sw          $t9, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r25;
    // 0x802C6AAC: sw          $t8, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r24;
    // 0x802C6AB0: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C6AB4: or          $a1, $a0, $zero
    ctx->r5 = ctx->r4 | 0;
    // 0x802C6AB8: lui         $t6, 0xE462
    ctx->r14 = S32(0XE462 << 16);
    // 0x802C6ABC: addiu       $t6, $t6, 0x4330
    ctx->r14 = ADD32(ctx->r14, 0X4330);
    // 0x802C6AC0: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C6AC4: lui         $t7, 0x52
    ctx->r15 = S32(0X52 << 16);
    // 0x802C6AC8: addiu       $t7, $t7, 0x42D8
    ctx->r15 = ADD32(ctx->r15, 0X42D8);
    // 0x802C6ACC: or          $a2, $a0, $zero
    ctx->r6 = ctx->r4 | 0;
    // 0x802C6AD0: sw          $t6, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r14;
    // 0x802C6AD4: sw          $t7, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r15;
    // 0x802C6AD8: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C6ADC: lui         $t9, 0xB300
    ctx->r25 = S32(0XB300 << 16);
    // 0x802C6AE0: sw          $t9, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r25;
    // 0x802C6AE4: or          $a3, $a0, $zero
    ctx->r7 = ctx->r4 | 0;
    // 0x802C6AE8: sw          $zero, 0x4($a2)
    MEM_W(0X4, ctx->r6) = 0;
    // 0x802C6AEC: lui         $t6, 0x400
    ctx->r14 = S32(0X400 << 16);
    // 0x802C6AF0: ori         $t6, $t6, 0x400
    ctx->r14 = ctx->r14 | 0X400;
    // 0x802C6AF4: lui         $t8, 0xB200
    ctx->r24 = S32(0XB200 << 16);
    // 0x802C6AF8: sw          $t8, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r24;
    // 0x802C6AFC: sw          $t6, 0x4($a3)
    MEM_W(0X4, ctx->r7) = ctx->r14;
    // 0x802C6B00: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x802C6B04: lw          $v0, -0x7E90($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X7E90);
    // 0x802C6B08: lui         $v1, 0x802C
    ctx->r3 = S32(0X802C << 16);
    // 0x802C6B0C: lw          $v1, 0x6F8C($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X6F8C);
    // 0x802C6B10: lui         $t7, 0x800E
    ctx->r15 = S32(0X800E << 16);
    // 0x802C6B14: addiu       $t7, $t7, -0x4A50
    ctx->r15 = ADD32(ctx->r15, -0X4A50);
    // 0x802C6B18: sll         $a1, $v0, 3
    ctx->r5 = S32(ctx->r2 << 3);
    // 0x802C6B1C: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C6B20: addu        $t5, $a1, $t7
    ctx->r13 = ADD32(ctx->r5, ctx->r15);
    // 0x802C6B24: bne         $v1, $zero, L_802C6BC0
    if (ctx->r3 != 0) {
        // 0x802C6B28: addiu       $t2, $zero, 0x1
        ctx->r10 = ADD32(0, 0X1);
            goto L_802C6BC0;
    }
    // 0x802C6B28: addiu       $t2, $zero, 0x1
    ctx->r10 = ADD32(0, 0X1);
    // 0x802C6B2C: lui         $t9, 0x800E
    ctx->r25 = S32(0X800E << 16);
    // 0x802C6B30: addiu       $t9, $t9, -0x4A08
    ctx->r25 = ADD32(ctx->r25, -0X4A08);
    // 0x802C6B34: bne         $v0, $zero, L_802C6B44
    if (ctx->r2 != 0) {
        // 0x802C6B38: addu        $t4, $a1, $t9
        ctx->r12 = ADD32(ctx->r5, ctx->r25);
            goto L_802C6B44;
    }
    // 0x802C6B38: addu        $t4, $a1, $t9
    ctx->r12 = ADD32(ctx->r5, ctx->r25);
    // 0x802C6B3C: b           L_802C6BB8
    // 0x802C6B40: or          $t2, $zero, $zero
    ctx->r10 = 0 | 0;
        goto L_802C6BB8;
    // 0x802C6B40: or          $t2, $zero, $zero
    ctx->r10 = 0 | 0;
L_802C6B44:
    // 0x802C6B44: addiu       $at, $zero, 0x5
    ctx->r1 = ADD32(0, 0X5);
    // 0x802C6B48: bnel        $v0, $at, L_802C6B8C
    if (ctx->r2 != ctx->r1) {
        // 0x802C6B4C: addiu       $at, $zero, 0x3
        ctx->r1 = ADD32(0, 0X3);
            goto L_802C6B8C;
    }
    goto skip_0;
    // 0x802C6B4C: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    skip_0:
    // 0x802C6B50: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x802C6B54: lw          $v0, -0x4CC8($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X4CC8);
    // 0x802C6B58: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x802C6B5C: lui         $t8, 0x800E
    ctx->r24 = S32(0X800E << 16);
    // 0x802C6B60: bne         $v0, $at, L_802C6B70
    if (ctx->r2 != ctx->r1) {
        // 0x802C6B64: addiu       $t8, $t8, -0x49C0
        ctx->r24 = ADD32(ctx->r24, -0X49C0);
            goto L_802C6B70;
    }
    // 0x802C6B64: addiu       $t8, $t8, -0x49C0
    ctx->r24 = ADD32(ctx->r24, -0X49C0);
    // 0x802C6B68: b           L_802C6BB8
    // 0x802C6B6C: addu        $t4, $a1, $t8
    ctx->r12 = ADD32(ctx->r5, ctx->r24);
        goto L_802C6BB8;
    // 0x802C6B6C: addu        $t4, $a1, $t8
    ctx->r12 = ADD32(ctx->r5, ctx->r24);
L_802C6B70:
    // 0x802C6B70: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x802C6B74: bne         $v0, $at, L_802C6BB8
    if (ctx->r2 != ctx->r1) {
        // 0x802C6B78: lui         $t6, 0x800E
        ctx->r14 = S32(0X800E << 16);
            goto L_802C6BB8;
    }
    // 0x802C6B78: lui         $t6, 0x800E
    ctx->r14 = S32(0X800E << 16);
    // 0x802C6B7C: addiu       $t6, $t6, -0x4978
    ctx->r14 = ADD32(ctx->r14, -0X4978);
    // 0x802C6B80: b           L_802C6BB8
    // 0x802C6B84: addu        $t4, $a1, $t6
    ctx->r12 = ADD32(ctx->r5, ctx->r14);
        goto L_802C6BB8;
    // 0x802C6B84: addu        $t4, $a1, $t6
    ctx->r12 = ADD32(ctx->r5, ctx->r14);
    // 0x802C6B88: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
L_802C6B8C:
    // 0x802C6B8C: bne         $v0, $at, L_802C6BB8
    if (ctx->r2 != ctx->r1) {
        // 0x802C6B90: lui         $v0, 0x801D
        ctx->r2 = S32(0X801D << 16);
            goto L_802C6BB8;
    }
    // 0x802C6B90: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x802C6B94: lw          $v0, -0x4CC8($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X4CC8);
    // 0x802C6B98: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x802C6B9C: lui         $t7, 0x800E
    ctx->r15 = S32(0X800E << 16);
    // 0x802C6BA0: beq         $v0, $at, L_802C6BB4
    if (ctx->r2 == ctx->r1) {
        // 0x802C6BA4: addiu       $t7, $t7, -0x49C0
        ctx->r15 = ADD32(ctx->r15, -0X49C0);
            goto L_802C6BB4;
    }
    // 0x802C6BA4: addiu       $t7, $t7, -0x49C0
    ctx->r15 = ADD32(ctx->r15, -0X49C0);
    // 0x802C6BA8: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x802C6BAC: bne         $v0, $at, L_802C6BB8
    if (ctx->r2 != ctx->r1) {
        // 0x802C6BB0: nop
    
            goto L_802C6BB8;
    }
    // 0x802C6BB0: nop

L_802C6BB4:
    // 0x802C6BB4: addu        $t4, $a1, $t7
    ctx->r12 = ADD32(ctx->r5, ctx->r15);
L_802C6BB8:
    // 0x802C6BB8: b           L_802C6BE4
    // 0x802C6BBC: sw          $t4, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r12;
        goto L_802C6BE4;
    // 0x802C6BBC: sw          $t4, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r12;
L_802C6BC0:
    // 0x802C6BC0: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x802C6BC4: bne         $v1, $at, L_802C6BE4
    if (ctx->r3 != ctx->r1) {
        // 0x802C6BC8: lui         $t9, 0x800E
        ctx->r25 = S32(0X800E << 16);
            goto L_802C6BE4;
    }
    // 0x802C6BC8: lui         $t9, 0x800E
    ctx->r25 = S32(0X800E << 16);
    // 0x802C6BCC: addiu       $t9, $t9, -0x48E8
    ctx->r25 = ADD32(ctx->r25, -0X48E8);
    // 0x802C6BD0: addu        $t4, $a1, $t9
    ctx->r12 = ADD32(ctx->r5, ctx->r25);
    // 0x802C6BD4: bne         $v0, $zero, L_802C6BE4
    if (ctx->r2 != 0) {
        // 0x802C6BD8: sw          $t4, 0x40($sp)
        MEM_W(0X40, ctx->r29) = ctx->r12;
            goto L_802C6BE4;
    }
    // 0x802C6BD8: sw          $t4, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r12;
    // 0x802C6BDC: or          $t2, $zero, $zero
    ctx->r10 = 0 | 0;
    // 0x802C6BE0: sw          $t4, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r12;
L_802C6BE4:
    // 0x802C6BE4: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x802C6BE8: lw          $t4, 0x40($sp)
    ctx->r12 = MEM_W(ctx->r29, 0X40);
    // 0x802C6BEC: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C6BF0: lui         $t8, 0x805
    ctx->r24 = S32(0X805 << 16);
    // 0x802C6BF4: lui         $t0, 0x600
    ctx->r8 = S32(0X600 << 16);
    // 0x802C6BF8: addiu       $t8, $t8, -0x1BE8
    ctx->r24 = ADD32(ctx->r24, -0X1BE8);
    // 0x802C6BFC: or          $v1, $a0, $zero
    ctx->r3 = ctx->r4 | 0;
    // 0x802C6C00: sw          $t8, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r24;
    // 0x802C6C04: sw          $t0, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r8;
    // 0x802C6C08: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C6C0C: lui         $t6, 0xFF10
    ctx->r14 = S32(0XFF10 << 16);
    // 0x802C6C10: sw          $zero, 0x4($v1)
    MEM_W(0X4, ctx->r3) = 0;
    // 0x802C6C14: sw          $ra, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r31;
    // 0x802C6C18: ori         $t6, $t6, 0x1A7
    ctx->r14 = ctx->r14 | 0X1A7;
    // 0x802C6C1C: or          $a1, $a0, $zero
    ctx->r5 = ctx->r4 | 0;
    // 0x802C6C20: sw          $t6, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r14;
    // 0x802C6C24: lui         $t7, 0x8015
    ctx->r15 = S32(0X8015 << 16);
    // 0x802C6C28: lw          $t7, 0x1948($t7)
    ctx->r15 = MEM_W(ctx->r15, 0X1948);
    // 0x802C6C2C: lui         $t8, 0x8015
    ctx->r24 = S32(0X8015 << 16);
    // 0x802C6C30: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x802C6C34: sll         $t9, $t7, 2
    ctx->r25 = S32(ctx->r15 << 2);
    // 0x802C6C38: addu        $t8, $t8, $t9
    ctx->r24 = ADD32(ctx->r24, ctx->r25);
    // 0x802C6C3C: lw          $t8, 0x42C0($t8)
    ctx->r24 = MEM_W(ctx->r24, 0X42C0);
    // 0x802C6C40: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C6C44: or          $a2, $a0, $zero
    ctx->r6 = ctx->r4 | 0;
    // 0x802C6C48: addu        $t6, $t8, $at
    ctx->r14 = ADD32(ctx->r24, ctx->r1);
    // 0x802C6C4C: sw          $t6, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r14;
    // 0x802C6C50: lui         $t7, 0xB400
    ctx->r15 = S32(0XB400 << 16);
    // 0x802C6C54: sw          $t7, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r15;
    // 0x802C6C58: lui         $t9, 0x802C
    ctx->r25 = S32(0X802C << 16);
    // 0x802C6C5C: lhu         $t9, 0x7024($t9)
    ctx->r25 = MEM_HU(ctx->r25, 0X7024);
    // 0x802C6C60: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C6C64: or          $a3, $a0, $zero
    ctx->r7 = ctx->r4 | 0;
    // 0x802C6C68: sw          $t9, 0x4($a2)
    MEM_W(0X4, ctx->r6) = ctx->r25;
    // 0x802C6C6C: lui         $t6, 0x700
    ctx->r14 = S32(0X700 << 16);
    // 0x802C6C70: lui         $t8, 0x103
    ctx->r24 = S32(0X103 << 16);
    // 0x802C6C74: ori         $t8, $t8, 0x40
    ctx->r24 = ctx->r24 | 0X40;
    // 0x802C6C78: addiu       $t6, $t6, 0xA40
    ctx->r14 = ADD32(ctx->r14, 0XA40);
    // 0x802C6C7C: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C6C80: lui         $t7, 0x102
    ctx->r15 = S32(0X102 << 16);
    // 0x802C6C84: sw          $t6, 0x4($a3)
    MEM_W(0X4, ctx->r7) = ctx->r14;
    // 0x802C6C88: sw          $t8, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r24;
    // 0x802C6C8C: ori         $t7, $t7, 0x40
    ctx->r15 = ctx->r15 | 0X40;
    // 0x802C6C90: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x802C6C94: sw          $t7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r15;
    // 0x802C6C98: lui         $t9, 0x801D
    ctx->r25 = S32(0X801D << 16);
    // 0x802C6C9C: lw          $t9, -0x1A08($t9)
    ctx->r25 = MEM_W(ctx->r25, -0X1A08);
    // 0x802C6CA0: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C6CA4: or          $v1, $a0, $zero
    ctx->r3 = ctx->r4 | 0;
    // 0x802C6CA8: addiu       $t8, $t9, 0xA80
    ctx->r24 = ADD32(ctx->r25, 0XA80);
    // 0x802C6CAC: sw          $t8, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r24;
    // 0x802C6CB0: lui         $t6, 0x380
    ctx->r14 = S32(0X380 << 16);
    // 0x802C6CB4: ori         $t6, $t6, 0x10
    ctx->r14 = ctx->r14 | 0X10;
    // 0x802C6CB8: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C6CBC: lui         $t7, 0x107
    ctx->r15 = S32(0X107 << 16);
    // 0x802C6CC0: addiu       $t7, $t7, -0x8D8
    ctx->r15 = ADD32(ctx->r15, -0X8D8);
    // 0x802C6CC4: sw          $t6, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r14;
    // 0x802C6CC8: or          $a1, $a0, $zero
    ctx->r5 = ctx->r4 | 0;
    // 0x802C6CCC: sw          $t7, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r15;
    // 0x802C6CD0: lui         $t9, 0x107
    ctx->r25 = S32(0X107 << 16);
    // 0x802C6CD4: addiu       $t9, $t9, -0x8B8
    ctx->r25 = ADD32(ctx->r25, -0X8B8);
    // 0x802C6CD8: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C6CDC: sw          $t9, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r25;
    // 0x802C6CE0: sw          $t0, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r8;
    // 0x802C6CE4: or          $a2, $a0, $zero
    ctx->r6 = ctx->r4 | 0;
    // 0x802C6CE8: lui         $t8, 0xFB00
    ctx->r24 = S32(0XFB00 << 16);
    // 0x802C6CEC: sw          $t8, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r24;
    // 0x802C6CF0: lui         $t6, 0x802C
    ctx->r14 = S32(0X802C << 16);
    // 0x802C6CF4: lw          $t6, 0x6F6C($t6)
    ctx->r14 = MEM_W(ctx->r14, 0X6F6C);
    // 0x802C6CF8: addiu       $at, $zero, -0x100
    ctx->r1 = ADD32(0, -0X100);
    // 0x802C6CFC: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C6D00: andi        $t7, $t6, 0xFF
    ctx->r15 = ctx->r14 & 0XFF;
    // 0x802C6D04: or          $t9, $t7, $at
    ctx->r25 = ctx->r15 | ctx->r1;
    // 0x802C6D08: sw          $t9, 0x4($a2)
    MEM_W(0X4, ctx->r6) = ctx->r25;
    // 0x802C6D0C: lui         $t6, 0x2D
    ctx->r14 = S32(0X2D << 16);
    // 0x802C6D10: or          $a3, $a0, $zero
    ctx->r7 = ctx->r4 | 0;
    // 0x802C6D14: lui         $t8, 0xED07
    ctx->r24 = S32(0XED07 << 16);
    // 0x802C6D18: ori         $t8, $t8, 0xC0FC
    ctx->r24 = ctx->r24 | 0XC0FC;
    // 0x802C6D1C: ori         $t6, $t6, 0x29C
    ctx->r14 = ctx->r14 | 0X29C;
    // 0x802C6D20: sw          $t6, 0x4($a3)
    MEM_W(0X4, ctx->r7) = ctx->r14;
    // 0x802C6D24: sw          $t8, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r24;
    // 0x802C6D28: lui         $t7, 0x802C
    ctx->r15 = S32(0X802C << 16);
    // 0x802C6D2C: lw          $t7, 0x6F80($t7)
    ctx->r15 = MEM_W(ctx->r15, 0X6F80);
    // 0x802C6D30: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C6D34: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x802C6D38: bne         $t7, $zero, L_802C6D5C
    if (ctx->r15 != 0) {
        // 0x802C6D3C: lui         $t3, 0xB700
        ctx->r11 = S32(0XB700 << 16);
            goto L_802C6D5C;
    }
    // 0x802C6D3C: lui         $t3, 0xB700
    ctx->r11 = S32(0XB700 << 16);
    // 0x802C6D40: lui         $t9, 0xB900
    ctx->r25 = S32(0XB900 << 16);
    // 0x802C6D44: lui         $t8, 0x50
    ctx->r24 = S32(0X50 << 16);
    // 0x802C6D48: ori         $t8, $t8, 0x41C8
    ctx->r24 = ctx->r24 | 0X41C8;
    // 0x802C6D4C: ori         $t9, $t9, 0x31D
    ctx->r25 = ctx->r25 | 0X31D;
    // 0x802C6D50: sw          $t9, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r25;
    // 0x802C6D54: sw          $t8, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r24;
    // 0x802C6D58: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
L_802C6D5C:
    // 0x802C6D5C: beq         $t2, $zero, L_802C6D98
    if (ctx->r10 == 0) {
        // 0x802C6D60: lui         $t0, 0x2
        ctx->r8 = S32(0X2 << 16);
            goto L_802C6D98;
    }
    // 0x802C6D60: lui         $t0, 0x2
    ctx->r8 = S32(0X2 << 16);
    // 0x802C6D64: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x802C6D68: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C6D6C: lui         $t6, 0xB600
    ctx->r14 = S32(0XB600 << 16);
    // 0x802C6D70: sw          $t6, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r14;
    // 0x802C6D74: sw          $t0, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r8;
    // 0x802C6D78: or          $v1, $a0, $zero
    ctx->r3 = ctx->r4 | 0;
    // 0x802C6D7C: lui         $t7, 0x600
    ctx->r15 = S32(0X600 << 16);
    // 0x802C6D80: sw          $t7, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r15;
    // 0x802C6D84: lw          $t9, 0x0($t4)
    ctx->r25 = MEM_W(ctx->r12, 0X0);
    // 0x802C6D88: lui         $t1, 0x5
    ctx->r9 = S32(0X5 << 16);
    // 0x802C6D8C: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C6D90: addu        $t8, $t9, $t1
    ctx->r24 = ADD32(ctx->r25, ctx->r9);
    // 0x802C6D94: sw          $t8, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r24;
L_802C6D98:
    // 0x802C6D98: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x802C6D9C: lui         $t0, 0x2
    ctx->r8 = S32(0X2 << 16);
    // 0x802C6DA0: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C6DA4: sw          $t0, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r8;
    // 0x802C6DA8: sw          $t3, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r11;
    // 0x802C6DAC: or          $v1, $a0, $zero
    ctx->r3 = ctx->r4 | 0;
    // 0x802C6DB0: lui         $t6, 0x600
    ctx->r14 = S32(0X600 << 16);
    // 0x802C6DB4: sw          $t6, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r14;
    // 0x802C6DB8: lw          $t7, 0x0($t5)
    ctx->r15 = MEM_W(ctx->r13, 0X0);
    // 0x802C6DBC: lui         $t1, 0x5
    ctx->r9 = S32(0X5 << 16);
    // 0x802C6DC0: lui         $t8, 0x802C
    ctx->r24 = S32(0X802C << 16);
    // 0x802C6DC4: addu        $t9, $t7, $t1
    ctx->r25 = ADD32(ctx->r15, ctx->r9);
    // 0x802C6DC8: sw          $t9, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r25;
    // 0x802C6DCC: lw          $t8, 0x6F80($t8)
    ctx->r24 = MEM_W(ctx->r24, 0X6F80);
    // 0x802C6DD0: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C6DD4: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x802C6DD8: beq         $t8, $zero, L_802C6E08
    if (ctx->r24 == 0) {
        // 0x802C6DDC: lui         $t6, 0xB900
        ctx->r14 = S32(0XB900 << 16);
            goto L_802C6E08;
    }
    // 0x802C6DDC: lui         $t6, 0xB900
    ctx->r14 = S32(0XB900 << 16);
    // 0x802C6DE0: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C6DE4: or          $v1, $a0, $zero
    ctx->r3 = ctx->r4 | 0;
    // 0x802C6DE8: sw          $ra, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r31;
    // 0x802C6DEC: sw          $zero, 0x4($v0)
    MEM_W(0X4, ctx->r2) = 0;
    // 0x802C6DF0: lui         $t7, 0x50
    ctx->r15 = S32(0X50 << 16);
    // 0x802C6DF4: ori         $t7, $t7, 0x41C8
    ctx->r15 = ctx->r15 | 0X41C8;
    // 0x802C6DF8: ori         $t6, $t6, 0x31D
    ctx->r14 = ctx->r14 | 0X31D;
    // 0x802C6DFC: sw          $t6, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r14;
    // 0x802C6E00: sw          $t7, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r15;
    // 0x802C6E04: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
L_802C6E08:
    // 0x802C6E08: beq         $t2, $zero, L_802C6E3C
    if (ctx->r10 == 0) {
        // 0x802C6E0C: or          $v0, $a0, $zero
        ctx->r2 = ctx->r4 | 0;
            goto L_802C6E3C;
    }
    // 0x802C6E0C: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x802C6E10: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C6E14: lui         $t9, 0xB600
    ctx->r25 = S32(0XB600 << 16);
    // 0x802C6E18: sw          $t9, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r25;
    // 0x802C6E1C: sw          $t0, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r8;
    // 0x802C6E20: or          $v1, $a0, $zero
    ctx->r3 = ctx->r4 | 0;
    // 0x802C6E24: lui         $t8, 0x600
    ctx->r24 = S32(0X600 << 16);
    // 0x802C6E28: sw          $t8, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r24;
    // 0x802C6E2C: lw          $t6, 0x4($t4)
    ctx->r14 = MEM_W(ctx->r12, 0X4);
    // 0x802C6E30: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C6E34: addu        $t7, $t6, $t1
    ctx->r15 = ADD32(ctx->r14, ctx->r9);
    // 0x802C6E38: sw          $t7, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r15;
L_802C6E3C:
    // 0x802C6E3C: addiu       $a1, $a0, 0x8
    ctx->r5 = ADD32(ctx->r4, 0X8);
    // 0x802C6E40: sw          $t3, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r11;
    // 0x802C6E44: sw          $t0, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r8;
    // 0x802C6E48: lui         $t9, 0x600
    ctx->r25 = S32(0X600 << 16);
    // 0x802C6E4C: sw          $t9, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r25;
    // 0x802C6E50: lw          $t8, 0x4($t5)
    ctx->r24 = MEM_W(ctx->r13, 0X4);
    // 0x802C6E54: addiu       $a2, $a1, 0x8
    ctx->r6 = ADD32(ctx->r5, 0X8);
    // 0x802C6E58: addiu       $a3, $a2, 0x8
    ctx->r7 = ADD32(ctx->r6, 0X8);
    // 0x802C6E5C: addu        $t6, $t8, $t1
    ctx->r14 = ADD32(ctx->r24, ctx->r9);
    // 0x802C6E60: sw          $t6, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r14;
    // 0x802C6E64: sw          $zero, 0x4($a2)
    MEM_W(0X4, ctx->r6) = 0;
    // 0x802C6E68: sw          $ra, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r31;
    // 0x802C6E6C: lui         $t9, 0x6A
    ctx->r25 = S32(0X6A << 16);
    // 0x802C6E70: addiu       $t9, $t9, -0x3C44
    ctx->r25 = ADD32(ctx->r25, -0X3C44);
    // 0x802C6E74: lui         $t7, 0xED00
    ctx->r15 = S32(0XED00 << 16);
    // 0x802C6E78: sw          $t7, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r15;
    // 0x802C6E7C: sw          $t9, 0x4($a3)
    MEM_W(0X4, ctx->r7) = ctx->r25;
    // 0x802C6E80: lw          $ra, 0x3C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X3C);
    // 0x802C6E84: addiu       $v0, $a3, 0x8
    ctx->r2 = ADD32(ctx->r7, 0X8);
    { extern uint32_t wr64_championship_preview_finish(uint8_t*, uint32_t); ctx->r2 = S32(wr64_championship_preview_finish(rdram, (uint32_t)ctx->r2)); }
    // 0x802C6E88: addiu       $sp, $sp, 0x68
    ctx->r29 = ADD32(ctx->r29, 0X68);
    // 0x802C6E8C: jr          $ra
    // 0x802C6E90: nop

    return;
    // 0x802C6E90: nop

    // 0x802C6E94: jr          $ra
    // 0x802C6E98: nop

    return;
    // 0x802C6E98: nop

;}
RECOMP_FUNC void func_i3_802C6E9C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C6E9C: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x802C6EA0: addiu       $v0, $v0, -0x54DC
    ctx->r2 = ADD32(ctx->r2, -0X54DC);
    // 0x802C6EA4: lw          $t6, 0x0($v0)
    ctx->r14 = MEM_W(ctx->r2, 0X0);
    // 0x802C6EA8: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C6EAC: addiu       $t7, $zero, 0x1F
    ctx->r15 = ADD32(0, 0X1F);
    // 0x802C6EB0: sw          $t6, -0x19CC($at)
    MEM_W(-0X19CC, ctx->r1) = ctx->r14;
    // 0x802C6EB4: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C6EB8: sw          $zero, -0x19D0($at)
    MEM_W(-0X19D0, ctx->r1) = 0;
    // 0x802C6EBC: sw          $t7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r15;
    // 0x802C6EC0: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C6EC4: addiu       $t8, $zero, 0x8
    ctx->r24 = ADD32(0, 0X8);
    // 0x802C6EC8: sw          $t8, -0x19C8($at)
    MEM_W(-0X19C8, ctx->r1) = ctx->r24;
    // 0x802C6ECC: addiu       $v1, $zero, 0x1
    ctx->r3 = ADD32(0, 0X1);
    // 0x802C6ED0: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C6ED4: sw          $v1, -0x19C4($at)
    MEM_W(-0X19C4, ctx->r1) = ctx->r3;
    // 0x802C6ED8: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C6EDC: sw          $zero, -0x19C0($at)
    MEM_W(-0X19C0, ctx->r1) = 0;
    // 0x802C6EE0: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C6EE4: addiu       $t9, $zero, 0x14
    ctx->r25 = ADD32(0, 0X14);
    // 0x802C6EE8: sw          $t9, -0x19BC($at)
    MEM_W(-0X19BC, ctx->r1) = ctx->r25;
    // 0x802C6EEC: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x802C6EF0: sw          $zero, -0x54E4($at)
    MEM_W(-0X54E4, ctx->r1) = 0;
    // 0x802C6EF4: lui         $at, 0x800D
    ctx->r1 = S32(0X800D << 16);
    // 0x802C6EF8: addiu       $t0, $zero, 0x3
    ctx->r8 = ADD32(0, 0X3);
    // 0x802C6EFC: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x802C6F00: sw          $t0, 0x461C($at)
    MEM_W(0X461C, ctx->r1) = ctx->r8;
    // 0x802C6F04: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x802C6F08: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C6F0C: sw          $v1, 0x6FE0($at)
    MEM_W(0X6FE0, ctx->r1) = ctx->r3;
    // 0x802C6F10: addiu       $a0, $zero, 0x5
    ctx->r4 = ADD32(0, 0X5);
    // 0x802C6F14: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C6F18: jal         0x801E6FB0
    // 0x802C6F1C: addiu       $a2, $zero, 0x14
    ctx->r6 = ADD32(0, 0X14);
    FadeTransition_SetProps(rdram, ctx);
        goto after_0;
    // 0x802C6F1C: addiu       $a2, $zero, 0x14
    ctx->r6 = ADD32(0, 0X14);
    after_0:
    // 0x802C6F20: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    // 0x802C6F24: jal         0x801E6A4C
    // 0x802C6F28: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_801E6A4C(rdram, ctx);
        goto after_1;
    // 0x802C6F28: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_1:
    // 0x802C6F2C: addiu       $a0, $zero, 0x3A
    ctx->r4 = ADD32(0, 0X3A);
    // 0x802C6F30: jal         0x800C37F4
    // 0x802C6F34: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_2;
    // 0x802C6F34: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_2:
    // 0x802C6F38: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x802C6F3C: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x802C6F40: jr          $ra
    // 0x802C6F44: nop

    return;
    // 0x802C6F44: nop

    // 0x802C6F48: nop

    // 0x802C6F4C: nop

;}
RECOMP_FUNC void func_i4_802C5800(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C5800: lui         $t6, 0x801D
    ctx->r14 = S32(0X801D << 16);
    // 0x802C5804: lw          $t6, -0x19C4($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X19C4);
    // 0x802C5808: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x802C580C: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
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
    // 0x802C581C: addiu       $at, $zero, 0x14
    ctx->r1 = ADD32(0, 0X14);
    // 0x802C5820: bne         $t7, $at, L_802C5830
    if (ctx->r15 != ctx->r1) {
        // 0x802C5824: nop
    
            goto L_802C5830;
    }
    // 0x802C5824: nop

    // 0x802C5828: jal         0x802C58F8
    // 0x802C582C: nop

    func_i4_802C58F8(rdram, ctx);
        goto after_0;
    // 0x802C582C: nop

    after_0:
L_802C5830:
    // 0x802C5830: lui         $v0, 0x802C
    ctx->r2 = S32(0X802C << 16);
    // 0x802C5834: addiu       $v0, $v0, 0x7530
    ctx->r2 = ADD32(ctx->r2, 0X7530);
    // 0x802C5838: lw          $t8, 0x0($v0)
    ctx->r24 = MEM_W(ctx->r2, 0X0);
    // 0x802C583C: lui         $t9, 0x800E
    ctx->r25 = S32(0X800E << 16);
    // 0x802C5840: beq         $t8, $zero, L_802C58B0
    if (ctx->r24 == 0) {
        // 0x802C5844: nop
    
            goto L_802C58B0;
    }
    // 0x802C5844: nop

    // 0x802C5848: sw          $zero, 0x0($v0)
    MEM_W(0X0, ctx->r2) = 0;
    // 0x802C584C: lw          $t9, -0x5630($t9)
    ctx->r25 = MEM_W(ctx->r25, -0X5630);
    // 0x802C5850: lui         $t1, 0x800E
    ctx->r9 = S32(0X800E << 16);
    // 0x802C5854: lui         $a1, 0x800E
    ctx->r5 = S32(0X800E << 16);
    // 0x802C5858: sll         $t0, $t9, 2
    ctx->r8 = S32(ctx->r25 << 2);
    // 0x802C585C: addu        $t1, $t1, $t0
    ctx->r9 = ADD32(ctx->r9, ctx->r8);
    // 0x802C5860: lw          $t1, -0x5528($t1)
    ctx->r9 = MEM_W(ctx->r9, -0X5528);
    // 0x802C5864: lui         $a0, 0x801A
    ctx->r4 = S32(0X801A << 16);
    // 0x802C5868: addiu       $a0, $a0, -0x7CF0
    ctx->r4 = ADD32(ctx->r4, -0X7CF0);
    // 0x802C586C: sll         $t2, $t1, 2
    ctx->r10 = S32(ctx->r9 << 2);
    // 0x802C5870: addu        $a1, $a1, $t2
    ctx->r5 = ADD32(ctx->r5, ctx->r10);
    // 0x802C5874: jal         0x80069740
    // 0x802C5878: lw          $a1, -0x554C($a1)
    ctx->r5 = MEM_W(ctx->r5, -0X554C);
    func_80069740(rdram, ctx);
        goto after_1;
    // 0x802C5878: lw          $a1, -0x554C($a1)
    ctx->r5 = MEM_W(ctx->r5, -0X554C);
    after_1:
    // 0x802C587C: lui         $t3, 0x800E
    ctx->r11 = S32(0X800E << 16);
    // 0x802C5880: lw          $t3, -0x5630($t3)
    ctx->r11 = MEM_W(ctx->r11, -0X5630);
    // 0x802C5884: lui         $t5, 0x800E
    ctx->r13 = S32(0X800E << 16);
    // 0x802C5888: lui         $a1, 0x802C
    ctx->r5 = S32(0X802C << 16);
    // 0x802C588C: sll         $t4, $t3, 2
    ctx->r12 = S32(ctx->r11 << 2);
    // 0x802C5890: addu        $t5, $t5, $t4
    ctx->r13 = ADD32(ctx->r13, ctx->r12);
    // 0x802C5894: lw          $t5, -0x5528($t5)
    ctx->r13 = MEM_W(ctx->r13, -0X5528);
    // 0x802C5898: lui         $a0, 0x801A
    ctx->r4 = S32(0X801A << 16);
    // 0x802C589C: addiu       $a0, $a0, -0x7CB0
    ctx->r4 = ADD32(ctx->r4, -0X7CB0);
    // 0x802C58A0: sll         $t6, $t5, 2
    ctx->r14 = S32(ctx->r13 << 2);
    // 0x802C58A4: addu        $a1, $a1, $t6
    ctx->r5 = ADD32(ctx->r5, ctx->r14);
    // 0x802C58A8: jal         0x8006977C
    // 0x802C58AC: lw          $a1, 0x760C($a1)
    ctx->r5 = MEM_W(ctx->r5, 0X760C);
    func_8006977C(rdram, ctx);
        goto after_2;
    // 0x802C58AC: lw          $a1, 0x760C($a1)
    ctx->r5 = MEM_W(ctx->r5, 0X760C);
    after_2:
L_802C58B0:
    // 0x802C58B0: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x802C58B4: lw          $v0, -0x1A08($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X1A08);
    // 0x802C58B8: lui         $t7, 0x801A
    ctx->r15 = S32(0X801A << 16);
    // 0x802C58BC: lui         $t8, 0x801A
    ctx->r24 = S32(0X801A << 16);
    // 0x802C58C0: addiu       $t8, $t8, -0x7CB0
    ctx->r24 = ADD32(ctx->r24, -0X7CB0);
    // 0x802C58C4: addiu       $t7, $t7, -0x7CF0
    ctx->r15 = ADD32(ctx->r15, -0X7CF0);
    // 0x802C58C8: lui         $a3, 0x802C
    ctx->r7 = S32(0X802C << 16);
    // 0x802C58CC: addiu       $a3, $a3, 0x76AC
    ctx->r7 = ADD32(ctx->r7, 0X76AC);
    // 0x802C58D0: sw          $t7, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r15;
    // 0x802C58D4: sw          $t8, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r24;
    // 0x802C58D8: addiu       $a0, $v0, 0xA80
    ctx->r4 = ADD32(ctx->r2, 0XA80);
    // 0x802C58DC: addiu       $a1, $v0, 0x1780
    ctx->r5 = ADD32(ctx->r2, 0X1780);
    // 0x802C58E0: jal         0x80069798
    // 0x802C58E4: addiu       $a2, $v0, 0xA40
    ctx->r6 = ADD32(ctx->r2, 0XA40);
    func_80069798(rdram, ctx);
        goto after_3;
    // 0x802C58E4: addiu       $a2, $v0, 0xA40
    ctx->r6 = ADD32(ctx->r2, 0XA40);
    after_3:
    // 0x802C58E8: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    // 0x802C58EC: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x802C58F0: jr          $ra
    // 0x802C58F4: nop

    return;
    // 0x802C58F4: nop

;}
RECOMP_FUNC void func_i4_802C58F8(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C58F8: lui         $a1, 0x801D
    ctx->r5 = S32(0X801D << 16);
    // 0x802C58FC: addiu       $a1, $a1, -0x19F8
    ctx->r5 = ADD32(ctx->r5, -0X19F8);
    // 0x802C5900: lw          $v1, 0x0($a1)
    ctx->r3 = MEM_W(ctx->r5, 0X0);
    // 0x802C5904: addiu       $sp, $sp, -0x10
    ctx->r29 = ADD32(ctx->r29, -0X10);
    // 0x802C5908: addiu       $at, $zero, 0xB
    ctx->r1 = ADD32(0, 0XB);
    // 0x802C590C: sw          $s1, 0xC($sp)
    MEM_W(0XC, ctx->r29) = ctx->r17;
    // 0x802C5910: bne         $v1, $at, L_802C5928
    if (ctx->r3 != ctx->r1) {
        // 0x802C5914: sw          $s0, 0x8($sp)
        MEM_W(0X8, ctx->r29) = ctx->r16;
            goto L_802C5928;
    }
    // 0x802C5914: sw          $s0, 0x8($sp)
    MEM_W(0X8, ctx->r29) = ctx->r16;
    // 0x802C5918: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
    // 0x802C591C: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C5920: b           L_802C5934
    // 0x802C5924: sw          $v0, 0x7534($at)
    MEM_W(0X7534, ctx->r1) = ctx->r2;
        goto L_802C5934;
    // 0x802C5924: sw          $v0, 0x7534($at)
    MEM_W(0X7534, ctx->r1) = ctx->r2;
L_802C5928:
    // 0x802C5928: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C592C: sw          $zero, 0x7534($at)
    MEM_W(0X7534, ctx->r1) = 0;
    // 0x802C5930: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
L_802C5934:
    // 0x802C5934: lh          $a0, 0x4($a1)
    ctx->r4 = MEM_H(ctx->r5, 0X4);
    // 0x802C5938: lui         $t1, 0x801D
    ctx->r9 = S32(0X801D << 16);
    // 0x802C593C: addiu       $t1, $t1, -0x4D78
    ctx->r9 = ADD32(ctx->r9, -0X4D78);
    // 0x802C5940: bne         $v0, $a0, L_802C59A4
    if (ctx->r2 != ctx->r4) {
        // 0x802C5944: or          $t0, $zero, $zero
        ctx->r8 = 0 | 0;
            goto L_802C59A4;
    }
    // 0x802C5944: or          $t0, $zero, $zero
    ctx->r8 = 0 | 0;
    // 0x802C5948: lui         $a1, 0x801D
    ctx->r5 = S32(0X801D << 16);
    // 0x802C594C: lb          $a1, -0x4D80($a1)
    ctx->r5 = MEM_B(ctx->r5, -0X4D80);
    // 0x802C5950: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C5954: sw          $zero, 0x76B0($at)
    MEM_W(0X76B0, ctx->r1) = 0;
    // 0x802C5958: andi        $t6, $a1, 0x8
    ctx->r14 = ctx->r5 & 0X8;
    // 0x802C595C: beq         $t6, $zero, L_802C5988
    if (ctx->r14 == 0) {
        // 0x802C5960: addiu       $s0, $zero, 0x3
        ctx->r16 = ADD32(0, 0X3);
            goto L_802C5988;
    }
    // 0x802C5960: addiu       $s0, $zero, 0x3
    ctx->r16 = ADD32(0, 0X3);
    // 0x802C5964: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C5968: sw          $v0, 0x76C8($at)
    MEM_W(0X76C8, ctx->r1) = ctx->r2;
    // 0x802C596C: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C5970: addiu       $t7, $zero, 0x4
    ctx->r15 = ADD32(0, 0X4);
    // 0x802C5974: sw          $t7, 0x76D0($at)
    MEM_W(0X76D0, ctx->r1) = ctx->r15;
    // 0x802C5978: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C597C: sw          $v0, 0x76C4($at)
    MEM_W(0X76C4, ctx->r1) = ctx->r2;
    // 0x802C5980: b           L_802C5A00
    // 0x802C5984: addiu       $s0, $zero, 0x3
    ctx->r16 = ADD32(0, 0X3);
        goto L_802C5A00;
    // 0x802C5984: addiu       $s0, $zero, 0x3
    ctx->r16 = ADD32(0, 0X3);
L_802C5988:
    // 0x802C5988: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C598C: sw          $zero, 0x76C8($at)
    MEM_W(0X76C8, ctx->r1) = 0;
    // 0x802C5990: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C5994: sw          $s0, 0x76D0($at)
    MEM_W(0X76D0, ctx->r1) = ctx->r16;
    // 0x802C5998: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C599C: b           L_802C5A00
    // 0x802C59A0: sw          $zero, 0x76C4($at)
    MEM_W(0X76C4, ctx->r1) = 0;
        goto L_802C5A00;
    // 0x802C59A0: sw          $zero, 0x76C4($at)
    MEM_W(0X76C4, ctx->r1) = 0;
L_802C59A4:
    // 0x802C59A4: lui         $a1, 0x801D
    ctx->r5 = S32(0X801D << 16);
    // 0x802C59A8: lb          $a1, -0x4D80($a1)
    ctx->r5 = MEM_B(ctx->r5, -0X4D80);
    // 0x802C59AC: addiu       $a2, $zero, 0x2
    ctx->r6 = ADD32(0, 0X2);
    // 0x802C59B0: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C59B4: andi        $t8, $a1, 0x8
    ctx->r24 = ctx->r5 & 0X8;
    // 0x802C59B8: beq         $t8, $zero, L_802C59E4
    if (ctx->r24 == 0) {
        // 0x802C59BC: sw          $a2, 0x76B0($at)
        MEM_W(0X76B0, ctx->r1) = ctx->r6;
            goto L_802C59E4;
    }
    // 0x802C59BC: sw          $a2, 0x76B0($at)
    MEM_W(0X76B0, ctx->r1) = ctx->r6;
    // 0x802C59C0: addiu       $s0, $zero, 0x3
    ctx->r16 = ADD32(0, 0X3);
    // 0x802C59C4: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C59C8: sw          $s0, 0x76C8($at)
    MEM_W(0X76C8, ctx->r1) = ctx->r16;
    // 0x802C59CC: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C59D0: addiu       $t9, $zero, 0x4
    ctx->r25 = ADD32(0, 0X4);
    // 0x802C59D4: sw          $t9, 0x76D0($at)
    MEM_W(0X76D0, ctx->r1) = ctx->r25;
    // 0x802C59D8: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C59DC: b           L_802C5A00
    // 0x802C59E0: sw          $v0, 0x76C4($at)
    MEM_W(0X76C4, ctx->r1) = ctx->r2;
        goto L_802C5A00;
    // 0x802C59E0: sw          $v0, 0x76C4($at)
    MEM_W(0X76C4, ctx->r1) = ctx->r2;
L_802C59E4:
    // 0x802C59E4: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C59E8: sw          $a2, 0x76C8($at)
    MEM_W(0X76C8, ctx->r1) = ctx->r6;
    // 0x802C59EC: addiu       $s0, $zero, 0x3
    ctx->r16 = ADD32(0, 0X3);
    // 0x802C59F0: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C59F4: sw          $s0, 0x76D0($at)
    MEM_W(0X76D0, ctx->r1) = ctx->r16;
    // 0x802C59F8: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C59FC: sw          $zero, 0x76C4($at)
    MEM_W(0X76C4, ctx->r1) = 0;
L_802C5A00:
    // 0x802C5A00: lui         $s1, 0x802C
    ctx->r17 = S32(0X802C << 16);
    // 0x802C5A04: addiu       $s1, $s1, 0x757C
    ctx->r17 = ADD32(ctx->r17, 0X757C);
    // 0x802C5A08: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
L_802C5A0C:
    // 0x802C5A0C: lw          $t2, 0x0($t1)
    ctx->r10 = MEM_W(ctx->r9, 0X0);
    // 0x802C5A10: addiu       $t1, $t1, 0x4
    ctx->r9 = ADD32(ctx->r9, 0X4);
    // 0x802C5A14: or          $t3, $zero, $zero
    ctx->r11 = 0 | 0;
    // 0x802C5A18: addiu       $t2, $t2, 0x1
    ctx->r10 = ADD32(ctx->r10, 0X1);
    // 0x802C5A1C: blez        $t2, L_802C5A64
    if (SIGNED(ctx->r10) <= 0) {
        // 0x802C5A20: sll         $t6, $a2, 4
        ctx->r14 = S32(ctx->r6 << 4);
            goto L_802C5A64;
    }
    // 0x802C5A20: sll         $t6, $a2, 4
    ctx->r14 = S32(ctx->r6 << 4);
    // 0x802C5A24: lui         $t7, 0x800F
    ctx->r15 = S32(0X800F << 16);
    // 0x802C5A28: addiu       $t7, $t7, -0x53EC
    ctx->r15 = ADD32(ctx->r15, -0X53EC);
    // 0x802C5A2C: addu        $t4, $t6, $t7
    ctx->r12 = ADD32(ctx->r14, ctx->r15);
    // 0x802C5A30: sll         $t5, $t2, 1
    ctx->r13 = S32(ctx->r10 << 1);
L_802C5A34:
    // 0x802C5A34: bne         $a2, $s0, L_802C5A44
    if (ctx->r6 != ctx->r16) {
        // 0x802C5A38: addiu       $t3, $t3, 0x2
        ctx->r11 = ADD32(ctx->r11, 0X2);
            goto L_802C5A44;
    }
    // 0x802C5A38: addiu       $t3, $t3, 0x2
    ctx->r11 = ADD32(ctx->r11, 0X2);
    // 0x802C5A3C: b           L_802C5A48
    // 0x802C5A40: lh          $a3, -0x10($t4)
    ctx->r7 = MEM_H(ctx->r12, -0X10);
        goto L_802C5A48;
    // 0x802C5A40: lh          $a3, -0x10($t4)
    ctx->r7 = MEM_H(ctx->r12, -0X10);
L_802C5A44:
    // 0x802C5A44: lh          $a3, 0x0($t4)
    ctx->r7 = MEM_H(ctx->r12, 0X0);
L_802C5A48:
    // 0x802C5A48: sll         $t8, $a3, 4
    ctx->r24 = S32(ctx->r7 << 4);
    // 0x802C5A4C: addu        $t9, $s1, $t8
    ctx->r25 = ADD32(ctx->r17, ctx->r24);
    // 0x802C5A50: slt         $at, $t3, $t5
    ctx->r1 = SIGNED(ctx->r11) < SIGNED(ctx->r13) ? 1 : 0;
    // 0x802C5A54: addu        $t6, $t9, $t0
    ctx->r14 = ADD32(ctx->r25, ctx->r8);
    // 0x802C5A58: addiu       $t4, $t4, 0x2
    ctx->r12 = ADD32(ctx->r12, 0X2);
    // 0x802C5A5C: bne         $at, $zero, L_802C5A34
    if (ctx->r1 != 0) {
        // 0x802C5A60: sw          $v0, 0x0($t6)
        MEM_W(0X0, ctx->r14) = ctx->r2;
            goto L_802C5A34;
    }
    // 0x802C5A60: sw          $v0, 0x0($t6)
    MEM_W(0X0, ctx->r14) = ctx->r2;
L_802C5A64:
    // 0x802C5A64: addiu       $a2, $a2, 0x1
    ctx->r6 = ADD32(ctx->r6, 0X1);
    // 0x802C5A68: slti        $at, $a2, 0x4
    ctx->r1 = SIGNED(ctx->r6) < 0X4 ? 1 : 0;
    // 0x802C5A6C: bne         $at, $zero, L_802C5A0C
    if (ctx->r1 != 0) {
        // 0x802C5A70: addiu       $t0, $t0, 0x4
        ctx->r8 = ADD32(ctx->r8, 0X4);
            goto L_802C5A0C;
    }
    // 0x802C5A70: addiu       $t0, $t0, 0x4
    ctx->r8 = ADD32(ctx->r8, 0X4);
    // 0x802C5A74: beq         $v1, $zero, L_802C5A80
    if (ctx->r3 == 0) {
        // 0x802C5A78: or          $a2, $zero, $zero
        ctx->r6 = 0 | 0;
            goto L_802C5A80;
    }
    // 0x802C5A78: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x802C5A7C: bne         $v0, $v1, L_802C5A9C
    if (ctx->r2 != ctx->r3) {
        // 0x802C5A80: andi        $t7, $a1, 0x1
        ctx->r15 = ctx->r5 & 0X1;
            goto L_802C5A9C;
    }
L_802C5A80:
    // 0x802C5A80: andi        $t7, $a1, 0x1
    ctx->r15 = ctx->r5 & 0X1;
    // 0x802C5A84: bne         $t7, $zero, L_802C5A90
    if (ctx->r15 != 0) {
        // 0x802C5A88: andi        $t8, $a1, 0x2
        ctx->r24 = ctx->r5 & 0X2;
            goto L_802C5A90;
    }
    // 0x802C5A88: andi        $t8, $a1, 0x2
    ctx->r24 = ctx->r5 & 0X2;
    // 0x802C5A8C: sw          $zero, 0x14($s1)
    MEM_W(0X14, ctx->r17) = 0;
L_802C5A90:
    // 0x802C5A90: bne         $t8, $zero, L_802C5A9C
    if (ctx->r24 != 0) {
        // 0x802C5A94: nop
    
            goto L_802C5A9C;
    }
    // 0x802C5A94: nop

    // 0x802C5A98: sw          $zero, 0x18($s1)
    MEM_W(0X18, ctx->r17) = 0;
L_802C5A9C:
    // 0x802C5A9C: lui         $t0, 0x802C
    ctx->r8 = S32(0X802C << 16);
    // 0x802C5AA0: lui         $t3, 0x802C
    ctx->r11 = S32(0X802C << 16);
    // 0x802C5AA4: addiu       $t3, $t3, 0x7558
    ctx->r11 = ADD32(ctx->r11, 0X7558);
    // 0x802C5AA8: addiu       $t0, $t0, 0x757C
    ctx->r8 = ADD32(ctx->r8, 0X757C);
    // 0x802C5AAC: addiu       $t5, $zero, 0x10
    ctx->r13 = ADD32(0, 0X10);
    // 0x802C5AB0: addiu       $t4, $zero, 0x9
    ctx->r12 = ADD32(0, 0X9);
L_802C5AB4:
    // 0x802C5AB4: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C5AB8: or          $t1, $zero, $zero
    ctx->r9 = 0 | 0;
    // 0x802C5ABC: or          $t2, $t0, $zero
    ctx->r10 = ctx->r8 | 0;
L_802C5AC0:
    // 0x802C5AC0: lw          $t9, 0x0($t2)
    ctx->r25 = MEM_W(ctx->r10, 0X0);
    // 0x802C5AC4: addiu       $t1, $t1, 0x4
    ctx->r9 = ADD32(ctx->r9, 0X4);
    // 0x802C5AC8: beq         $t9, $zero, L_802C5AD8
    if (ctx->r25 == 0) {
        // 0x802C5ACC: nop
    
            goto L_802C5AD8;
    }
    // 0x802C5ACC: nop

    // 0x802C5AD0: b           L_802C5AE0
    // 0x802C5AD4: or          $a1, $v0, $zero
    ctx->r5 = ctx->r2 | 0;
        goto L_802C5AE0;
    // 0x802C5AD4: or          $a1, $v0, $zero
    ctx->r5 = ctx->r2 | 0;
L_802C5AD8:
    // 0x802C5AD8: bne         $t1, $t5, L_802C5AC0
    if (ctx->r9 != ctx->r13) {
        // 0x802C5ADC: addiu       $t2, $t2, 0x4
        ctx->r10 = ADD32(ctx->r10, 0X4);
            goto L_802C5AC0;
    }
    // 0x802C5ADC: addiu       $t2, $t2, 0x4
    ctx->r10 = ADD32(ctx->r10, 0X4);
L_802C5AE0:
    // 0x802C5AE0: beq         $a1, $zero, L_802C5AF0
    if (ctx->r5 == 0) {
        // 0x802C5AE4: sll         $t6, $a2, 2
        ctx->r14 = S32(ctx->r6 << 2);
            goto L_802C5AF0;
    }
    // 0x802C5AE4: sll         $t6, $a2, 2
    ctx->r14 = S32(ctx->r6 << 2);
    // 0x802C5AE8: addu        $t7, $t3, $t6
    ctx->r15 = ADD32(ctx->r11, ctx->r14);
    // 0x802C5AEC: sw          $v0, 0x0($t7)
    MEM_W(0X0, ctx->r15) = ctx->r2;
L_802C5AF0:
    // 0x802C5AF0: addiu       $a2, $a2, 0x1
    ctx->r6 = ADD32(ctx->r6, 0X1);
    // 0x802C5AF4: bne         $a2, $t4, L_802C5AB4
    if (ctx->r6 != ctx->r12) {
        // 0x802C5AF8: addiu       $t0, $t0, 0x10
        ctx->r8 = ADD32(ctx->r8, 0X10);
            goto L_802C5AB4;
    }
    // 0x802C5AF8: addiu       $t0, $t0, 0x10
    ctx->r8 = ADD32(ctx->r8, 0X10);
    // 0x802C5AFC: beql        $v1, $zero, L_802C5B10
    if (ctx->r3 == 0) {
        // 0x802C5B00: sw          $zero, 0x0($t3)
        MEM_W(0X0, ctx->r11) = 0;
            goto L_802C5B10;
    }
    goto skip_0;
    // 0x802C5B00: sw          $zero, 0x0($t3)
    MEM_W(0X0, ctx->r11) = 0;
    skip_0:
    // 0x802C5B04: bne         $v0, $v1, L_802C5B10
    if (ctx->r2 != ctx->r3) {
        // 0x802C5B08: nop
    
            goto L_802C5B10;
    }
    // 0x802C5B08: nop

    // 0x802C5B0C: sw          $zero, 0x0($t3)
    MEM_W(0X0, ctx->r11) = 0;
L_802C5B10:
    // 0x802C5B10: bne         $v0, $a0, L_802C5B3C
    if (ctx->r2 != ctx->r4) {
        // 0x802C5B14: nop
    
            goto L_802C5B3C;
    }
    // 0x802C5B14: nop

    // 0x802C5B18: bne         $v1, $zero, L_802C5B2C
    if (ctx->r3 != 0) {
        // 0x802C5B1C: lui         $v1, 0x802C
        ctx->r3 = S32(0X802C << 16);
            goto L_802C5B2C;
    }
    // 0x802C5B1C: lui         $v1, 0x802C
    ctx->r3 = S32(0X802C << 16);
    // 0x802C5B20: addiu       $v1, $v1, 0x76A4
    ctx->r3 = ADD32(ctx->r3, 0X76A4);
    // 0x802C5B24: b           L_802C5B48
    // 0x802C5B28: sw          $v0, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r2;
        goto L_802C5B48;
    // 0x802C5B28: sw          $v0, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r2;
L_802C5B2C:
    // 0x802C5B2C: lui         $v1, 0x802C
    ctx->r3 = S32(0X802C << 16);
    // 0x802C5B30: addiu       $v1, $v1, 0x76A4
    ctx->r3 = ADD32(ctx->r3, 0X76A4);
    // 0x802C5B34: b           L_802C5B48
    // 0x802C5B38: sw          $zero, 0x0($v1)
    MEM_W(0X0, ctx->r3) = 0;
        goto L_802C5B48;
    // 0x802C5B38: sw          $zero, 0x0($v1)
    MEM_W(0X0, ctx->r3) = 0;
L_802C5B3C:
    // 0x802C5B3C: lui         $v1, 0x802C
    ctx->r3 = S32(0X802C << 16);
    // 0x802C5B40: addiu       $v1, $v1, 0x76A4
    ctx->r3 = ADD32(ctx->r3, 0X76A4);
    // 0x802C5B44: sw          $v0, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r2;
L_802C5B48:
    { extern void wr64_free_ride_course_menu(uint8_t*); wr64_free_ride_course_menu(rdram); }
    // 0x802C5B48: lui         $a0, 0x800E
    ctx->r4 = S32(0X800E << 16);
    // 0x802C5B4C: addiu       $a0, $a0, -0x5630
    ctx->r4 = ADD32(ctx->r4, -0X5630);
    // 0x802C5B50: lw          $t8, 0x0($a0)
    ctx->r24 = MEM_W(ctx->r4, 0X0);
    // 0x802C5B54: lw          $v0, 0x0($v1)
    ctx->r2 = MEM_W(ctx->r3, 0X0);
    // 0x802C5B58: slt         $at, $t8, $v0
    ctx->r1 = SIGNED(ctx->r24) < SIGNED(ctx->r2) ? 1 : 0;
    // 0x802C5B5C: beql        $at, $zero, L_802C5B6C
    if (ctx->r1 == 0) {
        // 0x802C5B60: lw          $s0, 0x8($sp)
        ctx->r16 = MEM_W(ctx->r29, 0X8);
            goto L_802C5B6C;
    }
    goto skip_1;
    // 0x802C5B60: lw          $s0, 0x8($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X8);
    skip_1:
    // 0x802C5B64: sw          $v0, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r2;
    // 0x802C5B68: lw          $s0, 0x8($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X8);
L_802C5B6C:
    // 0x802C5B6C: lw          $s1, 0xC($sp)
    ctx->r17 = MEM_W(ctx->r29, 0XC);
    // 0x802C5B70: jr          $ra
    // 0x802C5B74: addiu       $sp, $sp, 0x10
    ctx->r29 = ADD32(ctx->r29, 0X10);
    return;
    // 0x802C5B74: addiu       $sp, $sp, 0x10
    ctx->r29 = ADD32(ctx->r29, 0X10);
;}
RECOMP_FUNC void func_i4_802C5B78(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C5B78: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x802C5B7C: addiu       $v0, $v0, -0x19C4
    ctx->r2 = ADD32(ctx->r2, -0X19C4);
    // 0x802C5B80: lw          $t6, 0x0($v0)
    ctx->r14 = MEM_W(ctx->r2, 0X0);
    // 0x802C5B84: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x802C5B88: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x802C5B8C: beq         $t6, $zero, L_802C5BC4
    if (ctx->r14 == 0) {
        // 0x802C5B90: sw          $a0, 0x18($sp)
        MEM_W(0X18, ctx->r29) = ctx->r4;
            goto L_802C5BC4;
    }
    // 0x802C5B90: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    // 0x802C5B94: sw          $zero, 0x0($v0)
    MEM_W(0X0, ctx->r2) = 0;
    // 0x802C5B98: lui         $t7, 0x800E
    ctx->r15 = S32(0X800E << 16);
    // 0x802C5B9C: lw          $t7, -0x54DC($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X54DC);
    // 0x802C5BA0: addiu       $at, $zero, 0x14
    ctx->r1 = ADD32(0, 0X14);
    // 0x802C5BA4: bne         $t7, $at, L_802C5BC4
    if (ctx->r15 != ctx->r1) {
        // 0x802C5BA8: nop
    
            goto L_802C5BC4;
    }
    // 0x802C5BA8: nop

    // 0x802C5BAC: jal         0x800C6AD0
    // 0x802C5BB0: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    osViBlack_recomp(rdram, ctx);
        goto after_0;
    // 0x802C5BB0: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    after_0:
    // 0x802C5BB4: jal         0x80093C44
    // 0x802C5BB8: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
    func_80093C44(rdram, ctx);
        goto after_1;
    // 0x802C5BB8: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
    after_1:
    // 0x802C5BBC: b           L_802C5CD0
    // 0x802C5BC0: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_802C5CD0;
    // 0x802C5BC0: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C5BC4:
    // 0x802C5BC4: lui         $t8, 0x800E
    ctx->r24 = S32(0X800E << 16);
    // 0x802C5BC8: lw          $t8, -0x5630($t8)
    ctx->r24 = MEM_W(ctx->r24, -0X5630);
    // 0x802C5BCC: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C5BD0: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
    // 0x802C5BD4: sw          $t8, 0x76A8($at)
    MEM_W(0X76A8, ctx->r1) = ctx->r24;
    // 0x802C5BD8: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x802C5BDC: jal         0x8008FB74
    // 0x802C5BE0: sw          $zero, -0x54D4($at)
    MEM_W(-0X54D4, ctx->r1) = 0;
    func_8008FB74(rdram, ctx);
        goto after_2;
    // 0x802C5BE0: sw          $zero, -0x54D4($at)
    MEM_W(-0X54D4, ctx->r1) = 0;
    after_2:
    // 0x802C5BE4: lui         $a1, 0x800E
    ctx->r5 = S32(0X800E << 16);
    // 0x802C5BE8: lw          $a1, -0x7E90($a1)
    ctx->r5 = MEM_W(ctx->r5, -0X7E90);
    // 0x802C5BEC: jal         0x800949B8
    // 0x802C5BF0: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    func_800949B8(rdram, ctx);
        goto after_3;
    // 0x802C5BF0: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    after_3:
    // 0x802C5BF4: jal         0x80090F58
    // 0x802C5BF8: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    Draw_WaterEffects(rdram, ctx);
        goto after_4;
    // 0x802C5BF8: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    after_4:
    // 0x802C5BFC: jal         0x802C5CDC
    // 0x802C5C00: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    func_i4_802C5CDC(rdram, ctx);
        goto after_5;
    // 0x802C5C00: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    after_5:
    // 0x802C5C04: addiu       $t9, $v0, 0x8
    ctx->r25 = ADD32(ctx->r2, 0X8);
    // 0x802C5C08: sw          $t9, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r25;
    // 0x802C5C0C: lui         $t1, 0x107
    ctx->r9 = S32(0X107 << 16);
    // 0x802C5C10: addiu       $t1, $t1, -0xE98
    ctx->r9 = ADD32(ctx->r9, -0XE98);
    // 0x802C5C14: lui         $t0, 0x600
    ctx->r8 = S32(0X600 << 16);
    // 0x802C5C18: sw          $t0, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r8;
    // 0x802C5C1C: sw          $t1, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r9;
    // 0x802C5C20: lui         $t2, 0x800E
    ctx->r10 = S32(0X800E << 16);
    // 0x802C5C24: lw          $t2, -0x54DC($t2)
    ctx->r10 = MEM_W(ctx->r10, -0X54DC);
    // 0x802C5C28: addiu       $at, $zero, 0x14
    ctx->r1 = ADD32(0, 0X14);
    // 0x802C5C2C: lui         $t3, 0x8023
    ctx->r11 = S32(0X8023 << 16);
    // 0x802C5C30: bne         $t2, $at, L_802C5C48
    if (ctx->r10 != ctx->r1) {
        // 0x802C5C34: nop
    
            goto L_802C5C48;
    }
    // 0x802C5C34: nop

    // 0x802C5C38: jal         0x802C6BAC
    // 0x802C5C3C: nop

    func_i4_802C6BAC(rdram, ctx);
        goto after_6;
    // 0x802C5C3C: nop

    after_6:
    // 0x802C5C40: b           L_802C5CCC
    // 0x802C5C44: lw          $v0, 0x18($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X18);
        goto L_802C5CCC;
    // 0x802C5C44: lw          $v0, 0x18($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X18);
L_802C5C48:
    // 0x802C5C48: lh          $t3, -0x75EA($t3)
    ctx->r11 = MEM_H(ctx->r11, -0X75EA);
    // 0x802C5C4C: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x802C5C50: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x802C5C54: bnel        $t3, $at, L_802C5CCC
    if (ctx->r11 != ctx->r1) {
        // 0x802C5C58: lw          $v0, 0x18($sp)
        ctx->r2 = MEM_W(ctx->r29, 0X18);
            goto L_802C5CCC;
    }
    goto skip_0;
    // 0x802C5C58: lw          $v0, 0x18($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X18);
    skip_0:
    // 0x802C5C5C: lw          $v0, -0x19D0($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X19D0);
    // 0x802C5C60: addiu       $at, $zero, 0xA
    ctx->r1 = ADD32(0, 0XA);
    // 0x802C5C64: beq         $v0, $at, L_802C5CC0
    if (ctx->r2 == ctx->r1) {
        // 0x802C5C68: addiu       $at, $zero, 0x28
        ctx->r1 = ADD32(0, 0X28);
            goto L_802C5CC0;
    }
    // 0x802C5C68: addiu       $at, $zero, 0x28
    ctx->r1 = ADD32(0, 0X28);
    // 0x802C5C6C: bne         $v0, $at, L_802C5CC8
    if (ctx->r2 != ctx->r1) {
        // 0x802C5C70: lui         $t4, 0x800E
        ctx->r12 = S32(0X800E << 16);
            goto L_802C5CC8;
    }
    // 0x802C5C70: lui         $t4, 0x800E
    ctx->r12 = S32(0X800E << 16);
    // 0x802C5C74: lw          $t4, -0x5630($t4)
    ctx->r12 = MEM_W(ctx->r12, -0X5630);
    // 0x802C5C78: lui         $t6, 0x800E
    ctx->r14 = S32(0X800E << 16);
    // 0x802C5C7C: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x802C5C80: sll         $t5, $t4, 2
    ctx->r13 = S32(ctx->r12 << 2);
    // 0x802C5C84: addu        $t6, $t6, $t5
    ctx->r14 = ADD32(ctx->r14, ctx->r13);
    // 0x802C5C88: lw          $t6, -0x5528($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X5528);
    // 0x802C5C8C: addiu       $v0, $v0, -0x7E90
    ctx->r2 = ADD32(ctx->r2, -0X7E90);
    // 0x802C5C90: lui         $t7, 0x800E
    ctx->r15 = S32(0X800E << 16);
    // 0x802C5C94: sw          $t6, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r14;
    // 0x802C5C98: lw          $t7, -0x7DC0($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X7DC0);
    // 0x802C5C9C: lui         $t8, 0x801C
    ctx->r24 = S32(0X801C << 16);
    // 0x802C5CA0: beq         $t7, $zero, L_802C5CB0
    if (ctx->r15 == 0) {
        // 0x802C5CA4: nop
    
            goto L_802C5CB0;
    }
    // 0x802C5CA4: nop

    // 0x802C5CA8: lw          $t8, 0x3A10($t8)
    ctx->r24 = MEM_W(ctx->r24, 0X3A10);
    // 0x802C5CAC: sw          $t8, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r24;
L_802C5CB0:
    // 0x802C5CB0: jal         0x8009345C
    // 0x802C5CB4: nop

    func_8009345C(rdram, ctx);
        goto after_7;
    // 0x802C5CB4: nop

    after_7:
    // 0x802C5CB8: b           L_802C5CCC
    // 0x802C5CBC: lw          $v0, 0x18($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X18);
        goto L_802C5CCC;
    // 0x802C5CBC: lw          $v0, 0x18($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X18);
L_802C5CC0:
    // 0x802C5CC0: jal         0x801EBD28
    // 0x802C5CC4: nop

    func_801EBD28(rdram, ctx);
        goto after_8;
    // 0x802C5CC4: nop

    after_8:
L_802C5CC8:
    // 0x802C5CC8: lw          $v0, 0x18($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X18);
L_802C5CCC:
    // 0x802C5CCC: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C5CD0:
    // 0x802C5CD0: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x802C5CD4: jr          $ra
    // 0x802C5CD8: nop

    return;
    // 0x802C5CD8: nop

;}
RECOMP_FUNC void func_i4_802C5CDC(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    { extern void wr64_course_preview_prepare(uint8_t*, uint32_t); wr64_course_preview_prepare(rdram, (uint32_t)ctx->r4); }
    // 0x802C5CDC: addiu       $sp, $sp, -0xD8
    ctx->r29 = ADD32(ctx->r29, -0XD8);
    // 0x802C5CE0: sw          $s2, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r18;
    // 0x802C5CE4: sw          $s1, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r17;
    // 0x802C5CE8: sw          $ra, 0x54($sp)
    MEM_W(0X54, ctx->r29) = ctx->r31;
    // 0x802C5CEC: sw          $s4, 0x50($sp)
    MEM_W(0X50, ctx->r29) = ctx->r20;
    // 0x802C5CF0: sw          $s3, 0x4C($sp)
    MEM_W(0X4C, ctx->r29) = ctx->r19;
    // 0x802C5CF4: sw          $s0, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r16;
    // 0x802C5CF8: lui         $s1, 0x80A
    ctx->r17 = S32(0X80A << 16);
    // 0x802C5CFC: lui         $s2, 0x600
    ctx->r18 = S32(0X600 << 16);
    // 0x802C5D00: addiu       $s1, $s1, 0x6DB0
    ctx->r17 = ADD32(ctx->r17, 0X6DB0);
    // 0x802C5D04: sw          $s1, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r17;
    // 0x802C5D08: sw          $s2, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r18;
    // 0x802C5D0C: addiu       $v1, $a0, 0x8
    ctx->r3 = ADD32(ctx->r4, 0X8);
    // 0x802C5D10: lui         $t6, 0xF663
    ctx->r14 = S32(0XF663 << 16);
    // 0x802C5D14: addiu       $t6, $t6, -0x3D88
    ctx->r14 = ADD32(ctx->r14, -0X3D88);
    // 0x802C5D18: lui         $t7, 0x40
    ctx->r15 = S32(0X40 << 16);
    // 0x802C5D1C: addiu       $t7, $t7, -0x7F2C
    ctx->r15 = ADD32(ctx->r15, -0X7F2C);
    // 0x802C5D20: sw          $t6, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r14;
    // 0x802C5D24: sw          $t7, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r15;
    // 0x802C5D28: jal         0x802C6778
    // 0x802C5D2C: addiu       $a0, $v1, 0x8
    ctx->r4 = ADD32(ctx->r3, 0X8);
    func_i4_802C6778(rdram, ctx);
        goto after_0;
    // 0x802C5D2C: addiu       $a0, $v1, 0x8
    ctx->r4 = ADD32(ctx->r3, 0X8);
    after_0:
    // 0x802C5D30: lui         $t8, 0x802C
    ctx->r24 = S32(0X802C << 16);
    // 0x802C5D34: lw          $t8, 0x7540($t8)
    ctx->r24 = MEM_W(ctx->r24, 0X7540);
    // 0x802C5D38: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
    // 0x802C5D3C: lui         $a1, 0x802C
    ctx->r5 = S32(0X802C << 16);
    // 0x802C5D40: beq         $t8, $zero, L_802C5DD8
    if (ctx->r24 == 0) {
        // 0x802C5D44: addiu       $a3, $zero, 0x18
        ctx->r7 = ADD32(0, 0X18);
            goto L_802C5DD8;
    }
    // 0x802C5D44: addiu       $a3, $zero, 0x18
    ctx->r7 = ADD32(0, 0X18);
    // 0x802C5D48: sw          $s2, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r18;
    // 0x802C5D4C: sw          $s1, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r17;
    // 0x802C5D50: addiu       $a1, $a1, 0x76B4
    ctx->r5 = ADD32(ctx->r5, 0X76B4);
    // 0x802C5D54: lui         $t6, 0x802C
    ctx->r14 = S32(0X802C << 16);
    // 0x802C5D58: lw          $t6, 0x76BC($t6)
    ctx->r14 = MEM_W(ctx->r14, 0X76BC);
    // 0x802C5D5C: lw          $t9, 0x0($a1)
    ctx->r25 = MEM_W(ctx->r5, 0X0);
    // 0x802C5D60: lui         $a2, 0x802C
    ctx->r6 = S32(0X802C << 16);
    // 0x802C5D64: addiu       $a2, $a2, 0x76B8
    ctx->r6 = ADD32(ctx->r6, 0X76B8);
    // 0x802C5D68: addu        $t7, $t9, $t6
    ctx->r15 = ADD32(ctx->r25, ctx->r14);
    // 0x802C5D6C: addiu       $t8, $t7, 0x7
    ctx->r24 = ADD32(ctx->r15, 0X7);
    // 0x802C5D70: andi        $t9, $t8, 0x3FF
    ctx->r25 = ctx->r24 & 0X3FF;
    // 0x802C5D74: sll         $t6, $t9, 14
    ctx->r14 = S32(ctx->r25 << 14);
    // 0x802C5D78: lui         $t9, 0x802C
    ctx->r25 = S32(0X802C << 16);
    // 0x802C5D7C: lw          $t9, 0x76C0($t9)
    ctx->r25 = MEM_W(ctx->r25, 0X76C0);
    // 0x802C5D80: lw          $t8, 0x0($a2)
    ctx->r24 = MEM_W(ctx->r6, 0X0);
    // 0x802C5D84: lui         $at, 0xF600
    ctx->r1 = S32(0XF600 << 16);
    // 0x802C5D88: or          $t7, $t6, $at
    ctx->r15 = ctx->r14 | ctx->r1;
    // 0x802C5D8C: addu        $t6, $t8, $t9
    ctx->r14 = ADD32(ctx->r24, ctx->r25);
    // 0x802C5D90: addiu       $t8, $t6, 0x13
    ctx->r24 = ADD32(ctx->r14, 0X13);
    // 0x802C5D94: andi        $t9, $t8, 0x3FF
    ctx->r25 = ctx->r24 & 0X3FF;
    // 0x802C5D98: addiu       $s0, $v0, 0x8
    ctx->r16 = ADD32(ctx->r2, 0X8);
    // 0x802C5D9C: sll         $t6, $t9, 2
    ctx->r14 = S32(ctx->r25 << 2);
    // 0x802C5DA0: or          $t8, $t7, $t6
    ctx->r24 = ctx->r15 | ctx->r14;
    // 0x802C5DA4: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x802C5DA8: sw          $t8, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r24;
    // 0x802C5DAC: lw          $t9, 0x0($a1)
    ctx->r25 = MEM_W(ctx->r5, 0X0);
    // 0x802C5DB0: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C5DB4: addiu       $t7, $t9, 0x8
    ctx->r15 = ADD32(ctx->r25, 0X8);
    // 0x802C5DB8: lw          $t9, 0x0($a2)
    ctx->r25 = MEM_W(ctx->r6, 0X0);
    // 0x802C5DBC: andi        $t6, $t7, 0x3FF
    ctx->r14 = ctx->r15 & 0X3FF;
    // 0x802C5DC0: sll         $t8, $t6, 14
    ctx->r24 = S32(ctx->r14 << 14);
    // 0x802C5DC4: addiu       $t7, $t9, 0x14
    ctx->r15 = ADD32(ctx->r25, 0X14);
    // 0x802C5DC8: andi        $t6, $t7, 0x3FF
    ctx->r14 = ctx->r15 & 0X3FF;
    // 0x802C5DCC: sll         $t9, $t6, 2
    ctx->r25 = S32(ctx->r14 << 2);
    // 0x802C5DD0: or          $t7, $t8, $t9
    ctx->r15 = ctx->r24 | ctx->r25;
    // 0x802C5DD4: sw          $t7, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r15;
L_802C5DD8:
    { extern void wr64_course_preview_mask(uint8_t*, uint32_t); wr64_course_preview_mask(rdram, (uint32_t)ctx->r16 - 8); }
    // 0x802C5DD8: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
    // 0x802C5DDC: lui         $t6, 0x107
    ctx->r14 = S32(0X107 << 16);
    // 0x802C5DE0: addiu       $t6, $t6, -0x9D8
    ctx->r14 = ADD32(ctx->r14, -0X9D8);
    // 0x802C5DE4: sw          $t6, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r14;
    // 0x802C5DE8: sw          $s2, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r18;
    // 0x802C5DEC: addiu       $t8, $zero, 0x170
    ctx->r24 = ADD32(0, 0X170);
    // 0x802C5DF0: addiu       $t9, $zero, 0x18
    ctx->r25 = ADD32(0, 0X18);
    // 0x802C5DF4: addiu       $a0, $s0, 0x8
    ctx->r4 = ADD32(ctx->r16, 0X8);
    // 0x802C5DF8: sw          $t9, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r25;
    // 0x802C5DFC: sw          $t8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r24;
    // 0x802C5E00: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C5E04: jal         0x80094338
    // 0x802C5E08: addiu       $a2, $zero, 0x1C
    ctx->r6 = ADD32(0, 0X1C);
    func_80094338(rdram, ctx);
        goto after_1;
    // 0x802C5E08: addiu       $a2, $zero, 0x1C
    ctx->r6 = ADD32(0, 0X1C);
    after_1:
    // 0x802C5E0C: lui         $t7, 0x801D
    ctx->r15 = S32(0X801D << 16);
    // 0x802C5E10: lw          $t7, -0x19F8($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X19F8);
    // 0x802C5E14: addiu       $s4, $zero, 0xB
    ctx->r20 = ADD32(0, 0XB);
    // 0x802C5E18: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
    // 0x802C5E1C: bne         $s4, $t7, L_802C5E74
    if (ctx->r20 != ctx->r15) {
        // 0x802C5E20: or          $a0, $s0, $zero
        ctx->r4 = ctx->r16 | 0;
            goto L_802C5E74;
    }
    // 0x802C5E20: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x802C5E24: addiu       $t6, $zero, 0x65
    ctx->r14 = ADD32(0, 0X65);
    // 0x802C5E28: addiu       $t8, $zero, 0xA
    ctx->r24 = ADD32(0, 0XA);
    // 0x802C5E2C: sw          $t8, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r24;
    // 0x802C5E30: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x802C5E34: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C5E38: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C5E3C: addiu       $a2, $zero, 0x113
    ctx->r6 = ADD32(0, 0X113);
    { extern int32_t wr64_course_preview_x(int32_t); ctx->r6 = S32(wr64_course_preview_x((int32_t)ctx->r6)); }
    // 0x802C5E40: jal         0x80094338
    // 0x802C5E44: addiu       $a3, $zero, 0xB9
    ctx->r7 = ADD32(0, 0XB9);
    func_80094338(rdram, ctx);
        goto after_2;
    // 0x802C5E44: addiu       $a3, $zero, 0xB9
    ctx->r7 = ADD32(0, 0XB9);
    after_2:
    // 0x802C5E48: addiu       $t9, $zero, 0x65
    ctx->r25 = ADD32(0, 0X65);
    // 0x802C5E4C: addiu       $t7, $zero, 0x10
    ctx->r15 = ADD32(0, 0X10);
    // 0x802C5E50: sw          $t7, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r15;
    // 0x802C5E54: sw          $t9, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r25;
    // 0x802C5E58: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C5E5C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C5E60: addiu       $a2, $zero, 0x113
    ctx->r6 = ADD32(0, 0X113);
    { extern int32_t wr64_course_preview_x(int32_t); ctx->r6 = S32(wr64_course_preview_x((int32_t)ctx->r6)); }
    // 0x802C5E64: jal         0x80094338
    // 0x802C5E68: addiu       $a3, $zero, 0xC5
    ctx->r7 = ADD32(0, 0XC5);
    func_80094338(rdram, ctx);
        goto after_3;
    // 0x802C5E68: addiu       $a3, $zero, 0xC5
    ctx->r7 = ADD32(0, 0XC5);
    after_3:
    // 0x802C5E6C: b           L_802C5F04
    // 0x802C5E70: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
        goto L_802C5F04;
    // 0x802C5E70: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
L_802C5E74:
    // 0x802C5E74: addiu       $t6, $zero, 0x65
    ctx->r14 = ADD32(0, 0X65);
    // 0x802C5E78: addiu       $t8, $zero, 0xC
    ctx->r24 = ADD32(0, 0XC);
    // 0x802C5E7C: sw          $t8, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r24;
    // 0x802C5E80: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x802C5E84: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C5E88: addiu       $a2, $zero, 0x113
    ctx->r6 = ADD32(0, 0X113);
    { extern int32_t wr64_course_preview_x(int32_t); ctx->r6 = S32(wr64_course_preview_x((int32_t)ctx->r6)); }
    // 0x802C5E8C: jal         0x80094338
    // 0x802C5E90: addiu       $a3, $zero, 0xA1
    ctx->r7 = ADD32(0, 0XA1);
    func_80094338(rdram, ctx);
        goto after_4;
    // 0x802C5E90: addiu       $a3, $zero, 0xA1
    ctx->r7 = ADD32(0, 0XA1);
    after_4:
    // 0x802C5E94: addiu       $t9, $zero, 0x65
    ctx->r25 = ADD32(0, 0X65);
    // 0x802C5E98: addiu       $t7, $zero, 0xC
    ctx->r15 = ADD32(0, 0XC);
    // 0x802C5E9C: sw          $t7, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r15;
    // 0x802C5EA0: sw          $t9, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r25;
    // 0x802C5EA4: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C5EA8: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C5EAC: addiu       $a2, $zero, 0x113
    ctx->r6 = ADD32(0, 0X113);
    { extern int32_t wr64_course_preview_x(int32_t); ctx->r6 = S32(wr64_course_preview_x((int32_t)ctx->r6)); }
    // 0x802C5EB0: jal         0x80094338
    // 0x802C5EB4: addiu       $a3, $zero, 0xAE
    ctx->r7 = ADD32(0, 0XAE);
    func_80094338(rdram, ctx);
        goto after_5;
    // 0x802C5EB4: addiu       $a3, $zero, 0xAE
    ctx->r7 = ADD32(0, 0XAE);
    after_5:
    // 0x802C5EB8: addiu       $t6, $zero, 0x65
    ctx->r14 = ADD32(0, 0X65);
    // 0x802C5EBC: addiu       $t8, $zero, 0xC
    ctx->r24 = ADD32(0, 0XC);
    // 0x802C5EC0: sw          $t8, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r24;
    // 0x802C5EC4: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x802C5EC8: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C5ECC: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C5ED0: addiu       $a2, $zero, 0x113
    ctx->r6 = ADD32(0, 0X113);
    { extern int32_t wr64_course_preview_x(int32_t); ctx->r6 = S32(wr64_course_preview_x((int32_t)ctx->r6)); }
    // 0x802C5ED4: jal         0x80094338
    // 0x802C5ED8: addiu       $a3, $zero, 0xBC
    ctx->r7 = ADD32(0, 0XBC);
    func_80094338(rdram, ctx);
        goto after_6;
    // 0x802C5ED8: addiu       $a3, $zero, 0xBC
    ctx->r7 = ADD32(0, 0XBC);
    after_6:
    // 0x802C5EDC: addiu       $t9, $zero, 0x65
    ctx->r25 = ADD32(0, 0X65);
    // 0x802C5EE0: addiu       $t7, $zero, 0xC
    ctx->r15 = ADD32(0, 0XC);
    // 0x802C5EE4: sw          $t7, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r15;
    // 0x802C5EE8: sw          $t9, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r25;
    // 0x802C5EEC: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C5EF0: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C5EF4: addiu       $a2, $zero, 0x113
    ctx->r6 = ADD32(0, 0X113);
    { extern int32_t wr64_course_preview_x(int32_t); ctx->r6 = S32(wr64_course_preview_x((int32_t)ctx->r6)); }
    // 0x802C5EF8: jal         0x80094338
    // 0x802C5EFC: addiu       $a3, $zero, 0xC9
    ctx->r7 = ADD32(0, 0XC9);
    func_80094338(rdram, ctx);
        goto after_7;
    // 0x802C5EFC: addiu       $a3, $zero, 0xC9
    ctx->r7 = ADD32(0, 0XC9);
    after_7:
    // 0x802C5F00: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
L_802C5F04:
    // 0x802C5F04: addiu       $a3, $zero, 0x35
    ctx->r7 = ADD32(0, 0X35);
    // 0x802C5F08: addiu       $t6, $zero, 0x76
    ctx->r14 = ADD32(0, 0X76);
L_802C5F0C:
    // 0x802C5F0C: addiu       $t8, $zero, 0x10
    ctx->r24 = ADD32(0, 0X10);
    // 0x802C5F10: sw          $t8, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r24;
    // 0x802C5F14: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x802C5F18: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x802C5F1C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C5F20: addiu       $a2, $zero, 0x1C
    ctx->r6 = ADD32(0, 0X1C);
    // 0x802C5F24: jal         0x80094338
    // 0x802C5F28: sw          $a3, 0x58($sp)
    MEM_W(0X58, ctx->r29) = ctx->r7;
    func_80094338(rdram, ctx);
        goto after_8;
    // 0x802C5F28: sw          $a3, 0x58($sp)
    MEM_W(0X58, ctx->r29) = ctx->r7;
    after_8:
    // 0x802C5F2C: lw          $a3, 0x58($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X58);
    // 0x802C5F30: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
    // 0x802C5F34: addiu       $a3, $a3, 0x12
    ctx->r7 = ADD32(ctx->r7, 0X12);
    // 0x802C5F38: slti        $at, $a3, 0xD7
    ctx->r1 = SIGNED(ctx->r7) < 0XD7 ? 1 : 0;
    // 0x802C5F3C: bnel        $at, $zero, L_802C5F0C
    if (ctx->r1 != 0) {
        // 0x802C5F40: addiu       $t6, $zero, 0x76
        ctx->r14 = ADD32(0, 0X76);
            goto L_802C5F0C;
    }
    goto skip_0;
    // 0x802C5F40: addiu       $t6, $zero, 0x76
    ctx->r14 = ADD32(0, 0X76);
    skip_0:
    // 0x802C5F44: lui         $t9, 0x802C
    ctx->r25 = S32(0X802C << 16);
    // 0x802C5F48: lw          $t9, 0x7548($t9)
    ctx->r25 = MEM_W(ctx->r25, 0X7548);
    // 0x802C5F4C: lui         $v0, 0x802C
    ctx->r2 = S32(0X802C << 16);
    // 0x802C5F50: beql        $t9, $zero, L_802C6128
    if (ctx->r25 == 0) {
        // 0x802C5F54: addiu       $t6, $zero, 0xFF
        ctx->r14 = ADD32(0, 0XFF);
            goto L_802C6128;
    }
    goto skip_1;
    // 0x802C5F54: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    skip_1:
    // 0x802C5F58: lw          $v0, 0x76C8($v0)
    ctx->r2 = MEM_W(ctx->r2, 0X76C8);
    // 0x802C5F5C: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x802C5F60: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x802C5F64: beq         $v0, $zero, L_802C5F90
    if (ctx->r2 == 0) {
        // 0x802C5F68: addiu       $a1, $zero, 0x10A
        ctx->r5 = ADD32(0, 0X10A);
            goto L_802C5F90;
    }
    // 0x802C5F68: addiu       $a1, $zero, 0x10A
    ctx->r5 = ADD32(0, 0X10A);
    // 0x802C5F6C: beq         $v0, $at, L_802C5F90
    if (ctx->r2 == ctx->r1) {
        // 0x802C5F70: addiu       $at, $zero, 0x2
        ctx->r1 = ADD32(0, 0X2);
            goto L_802C5F90;
    }
    // 0x802C5F70: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x802C5F74: beq         $v0, $at, L_802C5FA0
    if (ctx->r2 == ctx->r1) {
        // 0x802C5F78: or          $a0, $s0, $zero
        ctx->r4 = ctx->r16 | 0;
            goto L_802C5FA0;
    }
    // 0x802C5F78: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x802C5F7C: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x802C5F80: beql        $v0, $at, L_802C5FA4
    if (ctx->r2 == ctx->r1) {
        // 0x802C5F84: addiu       $a1, $zero, 0x10A
        ctx->r5 = ADD32(0, 0X10A);
            goto L_802C5FA4;
    }
    goto skip_2;
    // 0x802C5F84: addiu       $a1, $zero, 0x10A
    ctx->r5 = ADD32(0, 0X10A);
    skip_2:
    // 0x802C5F88: b           L_802C6128
    // 0x802C5F8C: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
        goto L_802C6128;
    // 0x802C5F8C: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
L_802C5F90:
    { extern int32_t wr64_course_preview_x(int32_t); ctx->r5 = S32(wr64_course_preview_x((int32_t)ctx->r5)); }
    // 0x802C5F90: jal         0x802C69C4
    // 0x802C5F94: addiu       $a2, $zero, 0x49
    ctx->r6 = ADD32(0, 0X49);
    func_i4_802C69C4(rdram, ctx);
        goto after_9;
    // 0x802C5F94: addiu       $a2, $zero, 0x49
    ctx->r6 = ADD32(0, 0X49);
    after_9:
    // 0x802C5F98: b           L_802C6124
    // 0x802C5F9C: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
        goto L_802C6124;
    // 0x802C5F9C: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
L_802C5FA0:
    // 0x802C5FA0: addiu       $a1, $zero, 0x10A
    ctx->r5 = ADD32(0, 0X10A);
L_802C5FA4:
    { extern int32_t wr64_course_preview_x(int32_t); ctx->r5 = S32(wr64_course_preview_x((int32_t)ctx->r5)); }
    // 0x802C5FA4: jal         0x802C69C4
    // 0x802C5FA8: addiu       $a2, $zero, 0x37
    ctx->r6 = ADD32(0, 0X37);
    func_i4_802C69C4(rdram, ctx);
        goto after_10;
    // 0x802C5FA8: addiu       $a2, $zero, 0x37
    ctx->r6 = ADD32(0, 0X37);
    after_10:
    // 0x802C5FAC: lui         $s2, 0x708
    ctx->r18 = S32(0X708 << 16);
    // 0x802C5FB0: lui         $s1, 0x80A
    ctx->r17 = S32(0X80A << 16);
    // 0x802C5FB4: lui         $ra, 0xFD10
    ctx->r31 = S32(0XFD10 << 16);
    // 0x802C5FB8: lui         $t4, 0xF510
    ctx->r12 = S32(0XF510 << 16);
    // 0x802C5FBC: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
    // 0x802C5FC0: ori         $t4, $t4, 0x3C00
    ctx->r12 = ctx->r12 | 0X3C00;
    // 0x802C5FC4: ori         $ra, $ra, 0x75
    ctx->r31 = ctx->r31 | 0X75;
    // 0x802C5FC8: addiu       $s1, $s1, 0x3DD8
    ctx->r17 = ADD32(ctx->r17, 0X3DD8);
    // 0x802C5FCC: ori         $s2, $s2, 0x200
    ctx->r18 = ctx->r18 | 0X200;
    // 0x802C5FD0: or          $t2, $zero, $zero
    ctx->r10 = 0 | 0;
    // 0x802C5FD4: or          $t3, $zero, $zero
    ctx->r11 = 0 | 0;
    // 0x802C5FD8: addiu       $a3, $zero, 0x7C
    ctx->r7 = ADD32(0, 0X7C);
    // 0x802C5FDC: lui         $s3, 0xE600
    ctx->r19 = S32(0XE600 << 16);
    // 0x802C5FE0: addiu       $t5, $zero, 0x8D
    ctx->r13 = ADD32(0, 0X8D);
L_802C5FE4:
    // 0x802C5FE4: beq         $a3, $t5, L_802C5FF4
    if (ctx->r7 == ctx->r13) {
        // 0x802C5FE8: or          $v0, $s0, $zero
        ctx->r2 = ctx->r16 | 0;
            goto L_802C5FF4;
    }
    // 0x802C5FE8: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
    // 0x802C5FEC: b           L_802C5FF8
    // 0x802C5FF0: addiu       $a2, $zero, 0x11
    ctx->r6 = ADD32(0, 0X11);
        goto L_802C5FF8;
    // 0x802C5FF0: addiu       $a2, $zero, 0x11
    ctx->r6 = ADD32(0, 0X11);
L_802C5FF4:
    // 0x802C5FF4: addiu       $a2, $zero, 0x10
    ctx->r6 = ADD32(0, 0X10);
L_802C5FF8:
    // 0x802C5FF8: sll         $t7, $t2, 1
    ctx->r15 = S32(ctx->r10 << 1);
    // 0x802C5FFC: addu        $t6, $s1, $t7
    ctx->r14 = ADD32(ctx->r17, ctx->r15);
    // 0x802C6000: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C6004: or          $v1, $s0, $zero
    ctx->r3 = ctx->r16 | 0;
    // 0x802C6008: sw          $t6, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r14;
    // 0x802C600C: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C6010: sw          $ra, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r31;
    // 0x802C6014: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x802C6018: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C601C: sw          $s2, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r18;
    // 0x802C6020: sw          $t4, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r12;
    // 0x802C6024: addiu       $t0, $a2, -0x1
    ctx->r8 = ADD32(ctx->r6, -0X1);
    // 0x802C6028: sll         $t9, $t0, 2
    ctx->r25 = S32(ctx->r8 << 2);
    // 0x802C602C: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    // 0x802C6030: lui         $at, 0x71D
    ctx->r1 = S32(0X71D << 16);
    // 0x802C6034: ori         $at, $at, 0x4000
    ctx->r1 = ctx->r1 | 0X4000;
    // 0x802C6038: andi        $t0, $t9, 0xFFF
    ctx->r8 = ctx->r25 & 0XFFF;
    // 0x802C603C: sw          $zero, 0x4($a0)
    MEM_W(0X4, ctx->r4) = 0;
    // 0x802C6040: sw          $s3, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r19;
    // 0x802C6044: or          $t6, $t0, $at
    ctx->r14 = ctx->r8 | ctx->r1;
    // 0x802C6048: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C604C: lui         $t8, 0xF400
    ctx->r24 = S32(0XF400 << 16);
    // 0x802C6050: sw          $t8, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r24;
    // 0x802C6054: or          $t1, $s0, $zero
    ctx->r9 = ctx->r16 | 0;
    // 0x802C6058: sw          $t6, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r14;
    // 0x802C605C: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C6060: lui         $t8, 0xE700
    ctx->r24 = S32(0XE700 << 16);
    // 0x802C6064: sw          $t8, 0x0($t1)
    MEM_W(0X0, ctx->r9) = ctx->r24;
    // 0x802C6068: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
    // 0x802C606C: lui         $t9, 0x8
    ctx->r25 = S32(0X8 << 16);
    // 0x802C6070: ori         $t9, $t9, 0x200
    ctx->r25 = ctx->r25 | 0X200;
    // 0x802C6074: sw          $zero, 0x4($t1)
    MEM_W(0X4, ctx->r9) = 0;
    // 0x802C6078: lui         $at, 0x1D
    ctx->r1 = S32(0X1D << 16);
    // 0x802C607C: ori         $at, $at, 0x4000
    ctx->r1 = ctx->r1 | 0X4000;
    // 0x802C6080: sw          $t9, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r25;
    // 0x802C6084: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C6088: or          $v1, $s0, $zero
    ctx->r3 = ctx->r16 | 0;
    // 0x802C608C: or          $t6, $t0, $at
    ctx->r14 = ctx->r8 | ctx->r1;
    // 0x802C6090: sw          $t4, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r12;
    // 0x802C6094: lui         $t7, 0xF200
    ctx->r15 = S32(0XF200 << 16);
    // 0x802C6098: addu        $t8, $t3, $a2
    ctx->r24 = ADD32(ctx->r11, ctx->r6);
    // 0x802C609C: sw          $t7, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r15;
    // 0x802C60A0: addiu       $t9, $t8, 0x7C
    ctx->r25 = ADD32(ctx->r24, 0X7C);
    // 0x802C60A4: sw          $t6, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r14;
    // 0x802C60A8: sll         $t7, $t9, 2
    ctx->r15 = S32(ctx->r25 << 2);
    // 0x802C60AC: andi        $t6, $t7, 0xFFF
    ctx->r14 = ctx->r15 & 0XFFF;
    // 0x802C60B0: lui         $at, 0xE460
    ctx->r1 = S32(0XE460 << 16);
    // 0x802C60B4: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C60B8: or          $t8, $t6, $at
    ctx->r24 = ctx->r14 | ctx->r1;
    // 0x802C60BC: lui         $at, 0x42
    ctx->r1 = S32(0X42 << 16);
    // 0x802C60C0: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x802C60C4: sll         $t9, $a3, 2
    ctx->r25 = S32(ctx->r7 << 2);
    // 0x802C60C8: andi        $t7, $t9, 0xFFF
    ctx->r15 = ctx->r25 & 0XFFF;
    // 0x802C60CC: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C60D0: ori         $at, $at, 0x8000
    ctx->r1 = ctx->r1 | 0X8000;
    // 0x802C60D4: or          $t6, $t7, $at
    ctx->r14 = ctx->r15 | ctx->r1;
    // 0x802C60D8: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    { extern uint32_t wr64_course_preview_rect_x(uint32_t); ctx->r24 = S32(wr64_course_preview_rect_x((uint32_t)ctx->r24)); ctx->r14 = S32(wr64_course_preview_rect_x((uint32_t)ctx->r14)); }
    // 0x802C60DC: sw          $t8, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r24;
    // 0x802C60E0: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x802C60E4: sw          $t6, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r14;
    // 0x802C60E8: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
    // 0x802C60EC: lui         $t8, 0xB300
    ctx->r24 = S32(0XB300 << 16);
    // 0x802C60F0: lui         $t7, 0x400
    ctx->r15 = S32(0X400 << 16);
    // 0x802C60F4: addiu       $at, $zero, 0x9E
    ctx->r1 = ADD32(0, 0X9E);
    // 0x802C60F8: addiu       $a3, $a3, 0x11
    ctx->r7 = ADD32(ctx->r7, 0X11);
    // 0x802C60FC: ori         $t7, $t7, 0x400
    ctx->r15 = ctx->r15 | 0X400;
    // 0x802C6100: sw          $t8, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r24;
    // 0x802C6104: sw          $zero, 0x4($a1)
    MEM_W(0X4, ctx->r5) = 0;
    // 0x802C6108: lui         $t9, 0xB200
    ctx->r25 = S32(0XB200 << 16);
    // 0x802C610C: addiu       $t3, $t3, 0x11
    ctx->r11 = ADD32(ctx->r11, 0X11);
    // 0x802C6110: addiu       $t2, $t2, 0x7D6
    ctx->r10 = ADD32(ctx->r10, 0X7D6);
    // 0x802C6114: sw          $t9, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r25;
    // 0x802C6118: sw          $t7, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r15;
    // 0x802C611C: bne         $a3, $at, L_802C5FE4
    if (ctx->r7 != ctx->r1) {
        // 0x802C6120: addiu       $s0, $s0, 0x8
        ctx->r16 = ADD32(ctx->r16, 0X8);
            goto L_802C5FE4;
    }
    // 0x802C6120: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
L_802C6124:
    // 0x802C6124: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
L_802C6128:
    // 0x802C6128: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C612C: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C6130: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C6134: sw          $t7, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r15;
    // 0x802C6138: sw          $t7, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r15;
    // 0x802C613C: sw          $t9, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r25;
    // 0x802C6140: sw          $t9, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r25;
    // 0x802C6144: sw          $t8, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r24;
    // 0x802C6148: sw          $t8, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r24;
    // 0x802C614C: sw          $t8, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r24;
    // 0x802C6150: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x802C6154: sw          $t6, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r14;
    // 0x802C6158: sw          $t6, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r14;
    // 0x802C615C: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x802C6160: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C6164: addiu       $a2, $zero, 0xFF
    ctx->r6 = ADD32(0, 0XFF);
    // 0x802C6168: jal         0x801E946C
    // 0x802C616C: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    func_801E946C(rdram, ctx);
        goto after_11;
    // 0x802C616C: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    after_11:
    // 0x802C6170: addiu       $t9, $zero, 0x1B
    ctx->r25 = ADD32(0, 0X1B);
    // 0x802C6174: sw          $t9, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r25;
    // 0x802C6178: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C617C: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x802C6180: addiu       $a2, $zero, 0x4
    ctx->r6 = ADD32(0, 0X4);
    // 0x802C6184: addiu       $a3, $zero, 0x74
    ctx->r7 = ADD32(0, 0X74);
    // 0x802C6188: jal         0x801E3EE0
    // 0x802C618C: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    func_801E3EE0(rdram, ctx);
        goto after_12;
    // 0x802C618C: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    after_12:
    // 0x802C6190: lui         $t7, 0x801D
    ctx->r15 = S32(0X801D << 16);
    // 0x802C6194: lw          $t7, -0x19F8($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X19F8);
    // 0x802C6198: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
    // 0x802C619C: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C61A0: bne         $s4, $t7, L_802C6214
    if (ctx->r20 != ctx->r15) {
        // 0x802C61A4: or          $a1, $zero, $zero
        ctx->r5 = 0 | 0;
            goto L_802C6214;
    }
    // 0x802C61A4: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C61A8: addiu       $t6, $zero, 0xBA
    ctx->r14 = ADD32(0, 0XBA);
    // 0x802C61AC: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x802C61B0: addiu       $a2, $zero, 0x1E
    ctx->r6 = ADD32(0, 0X1E);
    // 0x802C61B4: addiu       $a3, $zero, 0x127
    ctx->r7 = ADD32(0, 0X127);
    { extern int32_t wr64_course_preview_x(int32_t); ctx->r7 = S32(wr64_course_preview_x((int32_t)ctx->r7)); }
    // 0x802C61B8: jal         0x801E3EE0
    // 0x802C61BC: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    func_801E3EE0(rdram, ctx);
        goto after_13;
    // 0x802C61BC: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    after_13:
    // 0x802C61C0: lui         $s4, 0x800E
    ctx->r20 = S32(0X800E << 16);
    // 0x802C61C4: addiu       $s4, $s4, -0x5630
    ctx->r20 = ADD32(ctx->r20, -0X5630);
    // 0x802C61C8: lw          $t8, 0x0($s4)
    ctx->r24 = MEM_W(ctx->r20, 0X0);
    // 0x802C61CC: lui         $t7, 0x800E
    ctx->r15 = S32(0X800E << 16);
    // 0x802C61D0: lui         $a2, 0x801C
    ctx->r6 = S32(0X801C << 16);
    // 0x802C61D4: sll         $t9, $t8, 2
    ctx->r25 = S32(ctx->r24 << 2);
    // 0x802C61D8: addu        $t7, $t7, $t9
    ctx->r15 = ADD32(ctx->r15, ctx->r25);
    // 0x802C61DC: lw          $t7, -0x5528($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X5528);
    // 0x802C61E0: addiu       $t8, $zero, 0xC8
    ctx->r24 = ADD32(0, 0XC8);
    // 0x802C61E4: sw          $t8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r24;
    // 0x802C61E8: sll         $t6, $t7, 2
    ctx->r14 = S32(ctx->r15 << 2);
    // 0x802C61EC: subu        $t6, $t6, $t7
    ctx->r14 = SUB32(ctx->r14, ctx->r15);
    // 0x802C61F0: sll         $t6, $t6, 4
    ctx->r14 = S32(ctx->r14 << 4);
    // 0x802C61F4: addu        $a2, $a2, $t6
    ctx->r6 = ADD32(ctx->r6, ctx->r14);
    // 0x802C61F8: lw          $a2, 0x26E8($a2)
    ctx->r6 = MEM_W(ctx->r6, 0X26E8);
    // 0x802C61FC: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C6200: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    { extern int32_t wr64_course_preview_x(int32_t); ctx->r7 = S32(wr64_course_preview_x(0)); }
    // 0x802C6204: jal         0x80094200
    // 0x802C6208: addiu       $a3, $a3, 0x127
    ctx->r7 = ADD32(ctx->r7, 0X127);
    func_80094200(rdram, ctx);
        goto after_14;
    // 0x802C6208: addiu       $a3, $a3, 0x127
    ctx->r7 = ADD32(ctx->r7, 0X127);
    after_14:
    // 0x802C620C: b           L_802C637C
    // 0x802C6210: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
        goto L_802C637C;
    // 0x802C6210: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
L_802C6214:
    // 0x802C6214: addiu       $t9, $zero, 0xA3
    ctx->r25 = ADD32(0, 0XA3);
    // 0x802C6218: sw          $t9, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r25;
    // 0x802C621C: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x802C6220: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C6224: addiu       $a2, $zero, 0xE
    ctx->r6 = ADD32(0, 0XE);
    // 0x802C6228: addiu       $a3, $zero, 0x12B
    ctx->r7 = ADD32(0, 0X12B);
    { extern int32_t wr64_course_preview_x(int32_t); ctx->r7 = S32(wr64_course_preview_x((int32_t)ctx->r7)); }
    // 0x802C622C: jal         0x801E3EE0
    // 0x802C6230: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    func_801E3EE0(rdram, ctx);
        goto after_15;
    // 0x802C6230: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    after_15:
    // 0x802C6234: addiu       $t7, $zero, 0xBE
    ctx->r15 = ADD32(0, 0XBE);
    // 0x802C6238: sw          $t7, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r15;
    // 0x802C623C: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C6240: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C6244: addiu       $a2, $zero, 0xD
    ctx->r6 = ADD32(0, 0XD);
    // 0x802C6248: addiu       $a3, $zero, 0x12D
    ctx->r7 = ADD32(0, 0X12D);
    { extern int32_t wr64_course_preview_x(int32_t); ctx->r7 = S32(wr64_course_preview_x((int32_t)ctx->r7)); }
    // 0x802C624C: jal         0x801E3EE0
    // 0x802C6250: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    func_801E3EE0(rdram, ctx);
        goto after_16;
    // 0x802C6250: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    after_16:
    // 0x802C6254: lui         $t6, 0x802C
    ctx->r14 = S32(0X802C << 16);
    // 0x802C6258: lw          $t6, 0x754C($t6)
    ctx->r14 = MEM_W(ctx->r14, 0X754C);
    // 0x802C625C: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x802C6260: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
    // 0x802C6264: bne         $t6, $at, L_802C62E8
    if (ctx->r14 != ctx->r1) {
        // 0x802C6268: lui         $t8, 0x802C
        ctx->r24 = S32(0X802C << 16);
            goto L_802C62E8;
    }
    // 0x802C6268: lui         $t8, 0x802C
    ctx->r24 = S32(0X802C << 16);
    // 0x802C626C: lw          $t8, 0x7548($t8)
    ctx->r24 = MEM_W(ctx->r24, 0X7548);
    // 0x802C6270: lui         $s4, 0x800E
    ctx->r20 = S32(0X800E << 16);
    // 0x802C6274: addiu       $s4, $s4, -0x5630
    ctx->r20 = ADD32(ctx->r20, -0X5630);
    // 0x802C6278: beq         $t8, $zero, L_802C62E8
    if (ctx->r24 == 0) {
        // 0x802C627C: or          $a0, $v0, $zero
        ctx->r4 = ctx->r2 | 0;
            goto L_802C62E8;
    }
    // 0x802C627C: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C6280: lw          $t9, 0x0($s4)
    ctx->r25 = MEM_W(ctx->r20, 0X0);
    // 0x802C6284: lui         $t6, 0x800E
    ctx->r14 = S32(0X800E << 16);
    // 0x802C6288: lui         $a2, 0x801C
    ctx->r6 = S32(0X801C << 16);
    // 0x802C628C: sll         $t7, $t9, 2
    ctx->r15 = S32(ctx->r25 << 2);
    // 0x802C6290: addu        $t6, $t6, $t7
    ctx->r14 = ADD32(ctx->r14, ctx->r15);
    // 0x802C6294: lw          $t6, -0x5528($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X5528);
    // 0x802C6298: addiu       $t9, $zero, 0xB0
    ctx->r25 = ADD32(0, 0XB0);
    // 0x802C629C: sw          $t9, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r25;
    // 0x802C62A0: sll         $t8, $t6, 2
    ctx->r24 = S32(ctx->r14 << 2);
    // 0x802C62A4: addu        $t8, $t8, $t6
    ctx->r24 = ADD32(ctx->r24, ctx->r14);
    // 0x802C62A8: sll         $t8, $t8, 2
    ctx->r24 = S32(ctx->r24 << 2);
    // 0x802C62AC: addu        $a2, $a2, $t8
    ctx->r6 = ADD32(ctx->r6, ctx->r24);
    // 0x802C62B0: lw          $a2, 0x23B0($a2)
    ctx->r6 = MEM_W(ctx->r6, 0X23B0);
    // 0x802C62B4: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    { extern int32_t wr64_course_preview_x(int32_t); ctx->r7 = S32(wr64_course_preview_x(0)); }
    // 0x802C62B8: jal         0x801E8B24
    // 0x802C62BC: addiu       $a3, $a3, 0x12B
    ctx->r7 = ADD32(ctx->r7, 0X12B);
    func_801E8B24(rdram, ctx);
        goto after_17;
    // 0x802C62BC: addiu       $a3, $a3, 0x12B
    ctx->r7 = ADD32(ctx->r7, 0X12B);
    after_17:
    // 0x802C62C0: lui         $a2, 0x802C
    ctx->r6 = S32(0X802C << 16);
    // 0x802C62C4: addiu       $t7, $zero, 0xCB
    ctx->r15 = ADD32(0, 0XCB);
    // 0x802C62C8: sw          $t7, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r15;
    // 0x802C62CC: addiu       $a2, $a2, 0x7690
    ctx->r6 = ADD32(ctx->r6, 0X7690);
    // 0x802C62D0: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C62D4: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    { extern int32_t wr64_course_preview_x(int32_t); ctx->r7 = S32(wr64_course_preview_x(0)); }
    // 0x802C62D8: jal         0x801E9858
    // 0x802C62DC: addiu       $a3, $a3, 0x12B
    ctx->r7 = ADD32(ctx->r7, 0X12B);
    func_801E9858(rdram, ctx);
        goto after_18;
    // 0x802C62DC: addiu       $a3, $a3, 0x12B
    ctx->r7 = ADD32(ctx->r7, 0X12B);
    after_18:
    // 0x802C62E0: b           L_802C637C
    // 0x802C62E4: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
        goto L_802C637C;
    // 0x802C62E4: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
L_802C62E8:
    // 0x802C62E8: lui         $s4, 0x800E
    ctx->r20 = S32(0X800E << 16);
    // 0x802C62EC: addiu       $s4, $s4, -0x5630
    ctx->r20 = ADD32(ctx->r20, -0X5630);
    // 0x802C62F0: lw          $t6, 0x0($s4)
    ctx->r14 = MEM_W(ctx->r20, 0X0);
    // 0x802C62F4: lui         $t9, 0x800E
    ctx->r25 = S32(0X800E << 16);
    // 0x802C62F8: lui         $a2, 0x801C
    ctx->r6 = S32(0X801C << 16);
    // 0x802C62FC: sll         $t8, $t6, 2
    ctx->r24 = S32(ctx->r14 << 2);
    // 0x802C6300: addu        $t9, $t9, $t8
    ctx->r25 = ADD32(ctx->r25, ctx->r24);
    // 0x802C6304: lw          $t9, -0x5528($t9)
    ctx->r25 = MEM_W(ctx->r25, -0X5528);
    // 0x802C6308: addiu       $t6, $zero, 0xB0
    ctx->r14 = ADD32(0, 0XB0);
    // 0x802C630C: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x802C6310: sll         $t7, $t9, 4
    ctx->r15 = S32(ctx->r25 << 4);
    // 0x802C6314: subu        $t7, $t7, $t9
    ctx->r15 = SUB32(ctx->r15, ctx->r25);
    // 0x802C6318: sll         $t7, $t7, 2
    ctx->r15 = S32(ctx->r15 << 2);
    // 0x802C631C: addu        $a2, $a2, $t7
    ctx->r6 = ADD32(ctx->r6, ctx->r15);
    // 0x802C6320: lw          $a2, 0x1FF0($a2)
    ctx->r6 = MEM_W(ctx->r6, 0X1FF0);
    // 0x802C6324: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x802C6328: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    { extern int32_t wr64_course_preview_x(int32_t); ctx->r7 = S32(wr64_course_preview_x(0)); }
    // 0x802C632C: jal         0x801E8B24
    // 0x802C6330: addiu       $a3, $a3, 0x12B
    ctx->r7 = ADD32(ctx->r7, 0X12B);
    func_801E8B24(rdram, ctx);
        goto after_19;
    // 0x802C6330: addiu       $a3, $a3, 0x12B
    ctx->r7 = ADD32(ctx->r7, 0X12B);
    after_19:
    // 0x802C6334: lw          $t8, 0x0($s4)
    ctx->r24 = MEM_W(ctx->r20, 0X0);
    // 0x802C6338: lui         $t7, 0x800E
    ctx->r15 = S32(0X800E << 16);
    // 0x802C633C: lui         $a2, 0x801C
    ctx->r6 = S32(0X801C << 16);
    // 0x802C6340: sll         $t9, $t8, 2
    ctx->r25 = S32(ctx->r24 << 2);
    // 0x802C6344: addu        $t7, $t7, $t9
    ctx->r15 = ADD32(ctx->r15, ctx->r25);
    // 0x802C6348: lw          $t7, -0x5528($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X5528);
    // 0x802C634C: addiu       $t8, $zero, 0xCB
    ctx->r24 = ADD32(0, 0XCB);
    // 0x802C6350: sw          $t8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r24;
    // 0x802C6354: sll         $t6, $t7, 2
    ctx->r14 = S32(ctx->r15 << 2);
    // 0x802C6358: addu        $t6, $t6, $t7
    ctx->r14 = ADD32(ctx->r14, ctx->r15);
    // 0x802C635C: sll         $t6, $t6, 2
    ctx->r14 = S32(ctx->r14 << 2);
    // 0x802C6360: addu        $a2, $a2, $t6
    ctx->r6 = ADD32(ctx->r6, ctx->r14);
    // 0x802C6364: lw          $a2, 0x22C0($a2)
    ctx->r6 = MEM_W(ctx->r6, 0X22C0);
    // 0x802C6368: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C636C: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    { extern int32_t wr64_course_preview_x(int32_t); ctx->r7 = S32(wr64_course_preview_x(0)); }
    // 0x802C6370: jal         0x801E8B24
    // 0x802C6374: addiu       $a3, $a3, 0x12B
    ctx->r7 = ADD32(ctx->r7, 0X12B);
    func_801E8B24(rdram, ctx);
        goto after_20;
    // 0x802C6374: addiu       $a3, $a3, 0x12B
    ctx->r7 = ADD32(ctx->r7, 0X12B);
    after_20:
    // 0x802C6378: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
L_802C637C:
    // 0x802C637C: lui         $s2, 0x800E
    ctx->r18 = S32(0X800E << 16);
    // 0x802C6380: addiu       $s2, $s2, -0x5528
    ctx->r18 = ADD32(ctx->r18, -0X5528);
    // 0x802C6384: or          $s1, $zero, $zero
    ctx->r17 = 0 | 0;
    // 0x802C6388: addiu       $s3, $zero, 0x38
    ctx->r19 = ADD32(0, 0X38);
L_802C638C:
    // 0x802C638C: lw          $t9, 0x0($s4)
    ctx->r25 = MEM_W(ctx->r20, 0X0);
    // 0x802C6390: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x802C6394: addiu       $a2, $zero, 0x80
    ctx->r6 = ADD32(0, 0X80);
    // 0x802C6398: bne         $s1, $t9, L_802C63A8
    if (ctx->r17 != ctx->r25) {
        // 0x802C639C: addiu       $a3, $zero, 0x80
        ctx->r7 = ADD32(0, 0X80);
            goto L_802C63A8;
    }
    // 0x802C639C: addiu       $a3, $zero, 0x80
    ctx->r7 = ADD32(0, 0X80);
    // 0x802C63A0: b           L_802C63D0
    // 0x802C63A4: addiu       $a1, $zero, 0x6
    ctx->r5 = ADD32(0, 0X6);
        goto L_802C63D0;
    // 0x802C63A4: addiu       $a1, $zero, 0x6
    ctx->r5 = ADD32(0, 0X6);
L_802C63A8:
    // 0x802C63A8: lw          $t7, 0x0($s2)
    ctx->r15 = MEM_W(ctx->r18, 0X0);
    // 0x802C63AC: lui         $t8, 0x802C
    ctx->r24 = S32(0X802C << 16);
    // 0x802C63B0: addiu       $a1, $zero, 0x7
    ctx->r5 = ADD32(0, 0X7);
    // 0x802C63B4: sll         $t6, $t7, 2
    ctx->r14 = S32(ctx->r15 << 2);
    // 0x802C63B8: addu        $t8, $t8, $t6
    ctx->r24 = ADD32(ctx->r24, ctx->r14);
    // 0x802C63BC: lw          $t8, 0x7558($t8)
    ctx->r24 = MEM_W(ctx->r24, 0X7558);
    // 0x802C63C0: beq         $t8, $zero, L_802C63D0
    if (ctx->r24 == 0) {
        // 0x802C63C4: nop
    
            goto L_802C63D0;
    }
    // 0x802C63C4: nop

    // 0x802C63C8: b           L_802C63D0
    // 0x802C63CC: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
        goto L_802C63D0;
    // 0x802C63CC: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
L_802C63D0:
    // 0x802C63D0: addiu       $t9, $zero, 0x80
    ctx->r25 = ADD32(0, 0X80);
    // 0x802C63D4: sw          $t9, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r25;
    // 0x802C63D8: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C63DC: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C63E0: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C63E4: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C63E8: sw          $t8, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r24;
    // 0x802C63EC: sw          $t8, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r24;
    // 0x802C63F0: sw          $t6, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r14;
    // 0x802C63F4: sw          $t6, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r14;
    // 0x802C63F8: sw          $t9, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r25;
    // 0x802C63FC: sw          $t9, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r25;
    // 0x802C6400: sw          $t7, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r15;
    // 0x802C6404: sw          $t7, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r15;
    // 0x802C6408: jal         0x801E946C
    // 0x802C640C: sw          $t7, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r15;
    func_801E946C(rdram, ctx);
        goto after_21;
    // 0x802C640C: sw          $t7, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r15;
    after_21:
    // 0x802C6410: lw          $v1, 0x0($s2)
    ctx->r3 = MEM_W(ctx->r18, 0X0);
    // 0x802C6414: lui         $a3, 0x802C
    ctx->r7 = S32(0X802C << 16);
    // 0x802C6418: lui         $a2, 0x800E
    ctx->r6 = S32(0X800E << 16);
    // 0x802C641C: sll         $t6, $v1, 2
    ctx->r14 = S32(ctx->r3 << 2);
    // 0x802C6420: addu        $a3, $a3, $t6
    ctx->r7 = ADD32(ctx->r7, ctx->r14);
    // 0x802C6424: lw          $a3, 0x7660($a3)
    ctx->r7 = MEM_W(ctx->r7, 0X7660);
    // 0x802C6428: addu        $a2, $a2, $t6
    ctx->r6 = ADD32(ctx->r6, ctx->r14);
    // 0x802C642C: lw          $a2, -0x55F0($a2)
    ctx->r6 = MEM_W(ctx->r6, -0X55F0);
    // 0x802C6430: or          $v1, $t6, $zero
    ctx->r3 = ctx->r14 | 0;
    // 0x802C6434: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C6438: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C643C: sw          $s3, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r19;
    // 0x802C6440: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    // 0x802C6444: jal         0x801E3EE0
    // 0x802C6448: addiu       $a3, $a3, 0x30
    ctx->r7 = ADD32(ctx->r7, 0X30);
    func_801E3EE0(rdram, ctx);
        goto after_22;
    // 0x802C6448: addiu       $a3, $a3, 0x30
    ctx->r7 = ADD32(ctx->r7, 0X30);
    after_22:
    // 0x802C644C: addiu       $s1, $s1, 0x1
    ctx->r17 = ADD32(ctx->r17, 0X1);
    // 0x802C6450: slti        $at, $s1, 0x9
    ctx->r1 = SIGNED(ctx->r17) < 0X9 ? 1 : 0;
    // 0x802C6454: addiu       $s2, $s2, 0x4
    ctx->r18 = ADD32(ctx->r18, 0X4);
    // 0x802C6458: addiu       $s3, $s3, 0x12
    ctx->r19 = ADD32(ctx->r19, 0X12);
    // 0x802C645C: bne         $at, $zero, L_802C638C
    if (ctx->r1 != 0) {
        // 0x802C6460: or          $s0, $v0, $zero
        ctx->r16 = ctx->r2 | 0;
            goto L_802C638C;
    }
    // 0x802C6460: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
    // 0x802C6464: lui         $t8, 0x802C
    ctx->r24 = S32(0X802C << 16);
    // 0x802C6468: lw          $t8, 0x7548($t8)
    ctx->r24 = MEM_W(ctx->r24, 0X7548);
    // 0x802C646C: lui         $t9, 0x801D
    ctx->r25 = S32(0X801D << 16);
    // 0x802C6470: beql        $t8, $zero, L_802C6758
    if (ctx->r24 == 0) {
        // 0x802C6474: lw          $ra, 0x54($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X54);
            goto L_802C6758;
    }
    goto skip_3;
    // 0x802C6474: lw          $ra, 0x54($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X54);
    skip_3:
    // 0x802C6478: lh          $t9, -0x19F4($t9)
    ctx->r25 = MEM_H(ctx->r25, -0X19F4);
    // 0x802C647C: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x802C6480: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    // 0x802C6484: bne         $t9, $at, L_802C64AC
    if (ctx->r25 != ctx->r1) {
        // 0x802C6488: lui         $t8, 0x802C
        ctx->r24 = S32(0X802C << 16);
            goto L_802C64AC;
    }
    // 0x802C6488: lui         $t8, 0x802C
    ctx->r24 = S32(0X802C << 16);
    // 0x802C648C: lui         $t7, 0x802C
    ctx->r15 = S32(0X802C << 16);
    // 0x802C6490: lw          $t7, 0x76C4($t7)
    ctx->r15 = MEM_W(ctx->r15, 0X76C4);
    // 0x802C6494: addiu       $t6, $zero, 0x41
    ctx->r14 = ADD32(0, 0X41);
    // 0x802C6498: beq         $t7, $zero, L_802C64A4
    if (ctx->r15 == 0) {
        // 0x802C649C: nop
    
            goto L_802C64A4;
    }
    // 0x802C649C: nop

    // 0x802C64A0: addiu       $v0, $zero, -0x6
    ctx->r2 = ADD32(0, -0X6);
L_802C64A4:
    // 0x802C64A4: b           L_802C65FC
    // 0x802C64A8: sw          $t6, 0xC8($sp)
    MEM_W(0XC8, ctx->r29) = ctx->r14;
        goto L_802C65FC;
    // 0x802C64A8: sw          $t6, 0xC8($sp)
    MEM_W(0XC8, ctx->r29) = ctx->r14;
L_802C64AC:
    // 0x802C64AC: lw          $t8, 0x76C4($t8)
    ctx->r24 = MEM_W(ctx->r24, 0X76C4);
    // 0x802C64B0: addiu       $t9, $zero, 0x2F
    ctx->r25 = ADD32(0, 0X2F);
    // 0x802C64B4: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x802C64B8: beq         $t8, $zero, L_802C64C4
    if (ctx->r24 == 0) {
        // 0x802C64BC: or          $a1, $zero, $zero
        ctx->r5 = 0 | 0;
            goto L_802C64C4;
    }
    // 0x802C64BC: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C64C0: addiu       $v0, $zero, -0x8
    ctx->r2 = ADD32(0, -0X8);
L_802C64C4:
    // 0x802C64C4: sw          $t9, 0xC8($sp)
    MEM_W(0XC8, ctx->r29) = ctx->r25;
    // 0x802C64C8: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C64CC: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C64D0: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C64D4: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C64D8: sw          $t8, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r24;
    // 0x802C64DC: sw          $t8, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r24;
    // 0x802C64E0: sw          $t9, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r25;
    // 0x802C64E4: sw          $t9, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r25;
    // 0x802C64E8: sw          $t6, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r14;
    // 0x802C64EC: sw          $t6, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r14;
    // 0x802C64F0: sw          $t6, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r14;
    // 0x802C64F4: sw          $t7, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r15;
    // 0x802C64F8: sw          $t7, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r15;
    // 0x802C64FC: sw          $t7, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r15;
    // 0x802C6500: addiu       $a2, $zero, 0xFF
    ctx->r6 = ADD32(0, 0XFF);
    // 0x802C6504: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    // 0x802C6508: jal         0x801E946C
    // 0x802C650C: sw          $v0, 0xCC($sp)
    MEM_W(0XCC, ctx->r29) = ctx->r2;
    func_801E946C(rdram, ctx);
        goto after_23;
    // 0x802C650C: sw          $v0, 0xCC($sp)
    MEM_W(0XCC, ctx->r29) = ctx->r2;
    after_23:
    // 0x802C6510: addiu       $t8, $zero, 0x80
    ctx->r24 = ADD32(0, 0X80);
    // 0x802C6514: sw          $t8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r24;
    // 0x802C6518: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C651C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C6520: addiu       $a2, $zero, 0x20
    ctx->r6 = ADD32(0, 0X20);
    // 0x802C6524: addiu       $a3, $zero, 0x12B
    ctx->r7 = ADD32(0, 0X12B);
    { extern int32_t wr64_course_preview_x(int32_t); ctx->r7 = S32(wr64_course_preview_x((int32_t)ctx->r7)); }
    // 0x802C6528: jal         0x801E3EE0
    // 0x802C652C: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    func_801E3EE0(rdram, ctx);
        goto after_24;
    // 0x802C652C: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    after_24:
    // 0x802C6530: lui         $s2, 0x802C
    ctx->r18 = S32(0X802C << 16);
    // 0x802C6534: lui         $s3, 0x802C
    ctx->r19 = S32(0X802C << 16);
    // 0x802C6538: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
    // 0x802C653C: addiu       $s3, $s3, 0x7554
    ctx->r19 = ADD32(ctx->r19, 0X7554);
    // 0x802C6540: addiu       $s2, $s2, 0x7650
    ctx->r18 = ADD32(ctx->r18, 0X7650);
    // 0x802C6544: or          $s1, $zero, $zero
    ctx->r17 = 0 | 0;
L_802C6548:
    // 0x802C6548: lw          $t9, 0x0($s3)
    ctx->r25 = MEM_W(ctx->r19, 0X0);
    // 0x802C654C: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x802C6550: addiu       $a2, $zero, 0xFF
    ctx->r6 = ADD32(0, 0XFF);
    // 0x802C6554: beq         $t9, $zero, L_802C657C
    if (ctx->r25 == 0) {
        // 0x802C6558: addiu       $a3, $zero, 0xFF
        ctx->r7 = ADD32(0, 0XFF);
            goto L_802C657C;
    }
    // 0x802C6558: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    // 0x802C655C: lui         $t7, 0x800E
    ctx->r15 = S32(0X800E << 16);
    // 0x802C6560: lw          $t7, -0x55FC($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X55FC);
    // 0x802C6564: bne         $s1, $t7, L_802C6574
    if (ctx->r17 != ctx->r15) {
        // 0x802C6568: nop
    
            goto L_802C6574;
    }
    // 0x802C6568: nop

    // 0x802C656C: b           L_802C6580
    // 0x802C6570: addiu       $a1, $zero, 0x6
    ctx->r5 = ADD32(0, 0X6);
        goto L_802C6580;
    // 0x802C6570: addiu       $a1, $zero, 0x6
    ctx->r5 = ADD32(0, 0X6);
L_802C6574:
    // 0x802C6574: b           L_802C6580
    // 0x802C6578: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
        goto L_802C6580;
    // 0x802C6578: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
L_802C657C:
    // 0x802C657C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
L_802C6580:
    // 0x802C6580: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C6584: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C6588: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C658C: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C6590: sw          $t7, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r15;
    // 0x802C6594: sw          $t7, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r15;
    // 0x802C6598: sw          $t9, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r25;
    // 0x802C659C: sw          $t9, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r25;
    // 0x802C65A0: sw          $t8, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r24;
    // 0x802C65A4: sw          $t8, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r24;
    // 0x802C65A8: sw          $t8, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r24;
    // 0x802C65AC: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x802C65B0: sw          $t6, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r14;
    // 0x802C65B4: jal         0x801E946C
    // 0x802C65B8: sw          $t6, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r14;
    func_801E946C(rdram, ctx);
        goto after_25;
    // 0x802C65B8: sw          $t6, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r14;
    after_25:
    // 0x802C65BC: lh          $a3, 0x0($s2)
    ctx->r7 = MEM_H(ctx->r18, 0X0);
    // 0x802C65C0: addiu       $t9, $zero, 0x8F
    ctx->r25 = ADD32(0, 0X8F);
    // 0x802C65C4: subu        $t7, $t9, $s1
    ctx->r15 = SUB32(ctx->r25, ctx->r17);
    // 0x802C65C8: lw          $a2, 0x4($s2)
    ctx->r6 = MEM_W(ctx->r18, 0X4);
    // 0x802C65CC: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    // 0x802C65D0: sw          $t7, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r15;
    // 0x802C65D4: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C65D8: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    { extern int32_t wr64_course_preview_x(int32_t); ctx->r7 = S32(wr64_course_preview_x((int32_t)ctx->r7)); }
    // 0x802C65DC: jal         0x801E3EE0
    // 0x802C65E0: addiu       $a3, $a3, 0x129
    ctx->r7 = ADD32(ctx->r7, 0X129);
    func_801E3EE0(rdram, ctx);
        goto after_26;
    // 0x802C65E0: addiu       $a3, $a3, 0x129
    ctx->r7 = ADD32(ctx->r7, 0X129);
    after_26:
    // 0x802C65E4: addiu       $s1, $s1, 0x1
    ctx->r17 = ADD32(ctx->r17, 0X1);
    // 0x802C65E8: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x802C65EC: addiu       $s2, $s2, 0x8
    ctx->r18 = ADD32(ctx->r18, 0X8);
    // 0x802C65F0: bne         $s1, $at, L_802C6548
    if (ctx->r17 != ctx->r1) {
        // 0x802C65F4: or          $s0, $v0, $zero
        ctx->r16 = ctx->r2 | 0;
            goto L_802C6548;
    }
    // 0x802C65F4: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
    // 0x802C65F8: lw          $v0, 0xCC($sp)
    ctx->r2 = MEM_W(ctx->r29, 0XCC);
L_802C65FC:
    // 0x802C65FC: lui         $t6, 0x802C
    ctx->r14 = S32(0X802C << 16);
    // 0x802C6600: lw          $t6, 0x76D0($t6)
    ctx->r14 = MEM_W(ctx->r14, 0X76D0);
    // 0x802C6604: lui         $s2, 0x802C
    ctx->r18 = S32(0X802C << 16);
    // 0x802C6608: addiu       $s2, $s2, 0x7630
    ctx->r18 = ADD32(ctx->r18, 0X7630);
    // 0x802C660C: blez        $t6, L_802C6754
    if (SIGNED(ctx->r14) <= 0) {
        // 0x802C6610: or          $s1, $zero, $zero
        ctx->r17 = 0 | 0;
            goto L_802C6754;
    }
    // 0x802C6610: or          $s1, $zero, $zero
    ctx->r17 = 0 | 0;
    // 0x802C6614: lw          $t8, 0xC8($sp)
    ctx->r24 = MEM_W(ctx->r29, 0XC8);
    // 0x802C6618: addu        $s3, $t8, $v0
    ctx->r19 = ADD32(ctx->r24, ctx->r2);
    // 0x802C661C: addiu       $s3, $s3, 0x14
    ctx->r19 = ADD32(ctx->r19, 0X14);
L_802C6620:
    // 0x802C6620: lui         $t9, 0x802C
    ctx->r25 = S32(0X802C << 16);
    // 0x802C6624: lw          $t9, 0x7550($t9)
    ctx->r25 = MEM_W(ctx->r25, 0X7550);
    // 0x802C6628: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x802C662C: addiu       $a2, $zero, 0x80
    ctx->r6 = ADD32(0, 0X80);
    // 0x802C6630: beq         $t9, $zero, L_802C6694
    if (ctx->r25 == 0) {
        // 0x802C6634: addiu       $a3, $zero, 0x80
        ctx->r7 = ADD32(0, 0X80);
            goto L_802C6694;
    }
    // 0x802C6634: addiu       $a3, $zero, 0x80
    ctx->r7 = ADD32(0, 0X80);
    // 0x802C6638: lui         $t7, 0x802C
    ctx->r15 = S32(0X802C << 16);
    // 0x802C663C: lw          $t7, 0x754C($t7)
    ctx->r15 = MEM_W(ctx->r15, 0X754C);
    // 0x802C6640: bnel        $s1, $t7, L_802C6654
    if (ctx->r17 != ctx->r15) {
        // 0x802C6644: lw          $t6, 0x0($s4)
        ctx->r14 = MEM_W(ctx->r20, 0X0);
            goto L_802C6654;
    }
    goto skip_4;
    // 0x802C6644: lw          $t6, 0x0($s4)
    ctx->r14 = MEM_W(ctx->r20, 0X0);
    skip_4:
    // 0x802C6648: b           L_802C66D4
    // 0x802C664C: addiu       $a1, $zero, 0x6
    ctx->r5 = ADD32(0, 0X6);
        goto L_802C66D4;
    // 0x802C664C: addiu       $a1, $zero, 0x6
    ctx->r5 = ADD32(0, 0X6);
    // 0x802C6650: lw          $t6, 0x0($s4)
    ctx->r14 = MEM_W(ctx->r20, 0X0);
L_802C6654:
    // 0x802C6654: lui         $t9, 0x800E
    ctx->r25 = S32(0X800E << 16);
    // 0x802C6658: sll         $t8, $t6, 2
    ctx->r24 = S32(ctx->r14 << 2);
    // 0x802C665C: addu        $t9, $t9, $t8
    ctx->r25 = ADD32(ctx->r25, ctx->r24);
    // 0x802C6660: lw          $t9, -0x5528($t9)
    ctx->r25 = MEM_W(ctx->r25, -0X5528);
    // 0x802C6664: sll         $t6, $s1, 2
    ctx->r14 = S32(ctx->r17 << 2);
    // 0x802C6668: sll         $t7, $t9, 4
    ctx->r15 = S32(ctx->r25 << 4);
    // 0x802C666C: addu        $t8, $t7, $t6
    ctx->r24 = ADD32(ctx->r15, ctx->r14);
    // 0x802C6670: lui         $t9, 0x802C
    ctx->r25 = S32(0X802C << 16);
    // 0x802C6674: addu        $t9, $t9, $t8
    ctx->r25 = ADD32(ctx->r25, ctx->r24);
    // 0x802C6678: lw          $t9, 0x757C($t9)
    ctx->r25 = MEM_W(ctx->r25, 0X757C);
    // 0x802C667C: bne         $t9, $zero, L_802C668C
    if (ctx->r25 != 0) {
        // 0x802C6680: nop
    
            goto L_802C668C;
    }
    // 0x802C6680: nop

    // 0x802C6684: b           L_802C66D4
    // 0x802C6688: addiu       $a1, $zero, 0x7
    ctx->r5 = ADD32(0, 0X7);
        goto L_802C66D4;
    // 0x802C6688: addiu       $a1, $zero, 0x7
    ctx->r5 = ADD32(0, 0X7);
L_802C668C:
    // 0x802C668C: b           L_802C66D4
    // 0x802C6690: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
        goto L_802C66D4;
    // 0x802C6690: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
L_802C6694:
    // 0x802C6694: lw          $t7, 0x0($s4)
    ctx->r15 = MEM_W(ctx->r20, 0X0);
    // 0x802C6698: lui         $t8, 0x800E
    ctx->r24 = S32(0X800E << 16);
    // 0x802C669C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C66A0: sll         $t6, $t7, 2
    ctx->r14 = S32(ctx->r15 << 2);
    // 0x802C66A4: addu        $t8, $t8, $t6
    ctx->r24 = ADD32(ctx->r24, ctx->r14);
    // 0x802C66A8: lw          $t8, -0x5528($t8)
    ctx->r24 = MEM_W(ctx->r24, -0X5528);
    // 0x802C66AC: sll         $t7, $s1, 2
    ctx->r15 = S32(ctx->r17 << 2);
    // 0x802C66B0: sll         $t9, $t8, 4
    ctx->r25 = S32(ctx->r24 << 4);
    // 0x802C66B4: addu        $t6, $t9, $t7
    ctx->r14 = ADD32(ctx->r25, ctx->r15);
    // 0x802C66B8: lui         $t8, 0x802C
    ctx->r24 = S32(0X802C << 16);
    // 0x802C66BC: addu        $t8, $t8, $t6
    ctx->r24 = ADD32(ctx->r24, ctx->r14);
    // 0x802C66C0: lw          $t8, 0x757C($t8)
    ctx->r24 = MEM_W(ctx->r24, 0X757C);
    // 0x802C66C4: bne         $t8, $zero, L_802C66D4
    if (ctx->r24 != 0) {
        // 0x802C66C8: nop
    
            goto L_802C66D4;
    }
    // 0x802C66C8: nop

    // 0x802C66CC: b           L_802C66D4
    // 0x802C66D0: addiu       $a1, $zero, 0x7
    ctx->r5 = ADD32(0, 0X7);
        goto L_802C66D4;
    // 0x802C66D0: addiu       $a1, $zero, 0x7
    ctx->r5 = ADD32(0, 0X7);
L_802C66D4:
    // 0x802C66D4: addiu       $t9, $zero, 0x80
    ctx->r25 = ADD32(0, 0X80);
    // 0x802C66D8: sw          $t9, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r25;
    // 0x802C66DC: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x802C66E0: addiu       $t9, $zero, 0xFF
    ctx->r25 = ADD32(0, 0XFF);
    // 0x802C66E4: addiu       $t6, $zero, 0xFF
    ctx->r14 = ADD32(0, 0XFF);
    // 0x802C66E8: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x802C66EC: sw          $t8, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r24;
    // 0x802C66F0: sw          $t8, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r24;
    // 0x802C66F4: sw          $t6, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r14;
    // 0x802C66F8: sw          $t6, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r14;
    // 0x802C66FC: sw          $t9, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r25;
    // 0x802C6700: sw          $t9, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r25;
    // 0x802C6704: sw          $t7, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r15;
    // 0x802C6708: sw          $t7, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r15;
    // 0x802C670C: jal         0x801E946C
    // 0x802C6710: sw          $t7, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r15;
    func_801E946C(rdram, ctx);
        goto after_27;
    // 0x802C6710: sw          $t7, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r15;
    after_27:
    // 0x802C6714: lh          $a3, 0x0($s2)
    ctx->r7 = MEM_H(ctx->r18, 0X0);
    // 0x802C6718: lw          $a2, 0x4($s2)
    ctx->r6 = MEM_W(ctx->r18, 0X4);
    // 0x802C671C: sw          $zero, 0x14($sp)
    MEM_W(0X14, ctx->r29) = 0;
    // 0x802C6720: sw          $s3, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r19;
    // 0x802C6724: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x802C6728: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    { extern int32_t wr64_course_preview_x(int32_t); ctx->r7 = S32(wr64_course_preview_x((int32_t)ctx->r7)); }
    // 0x802C672C: jal         0x801E3EE0
    // 0x802C6730: addiu       $a3, $a3, 0x12A
    ctx->r7 = ADD32(ctx->r7, 0X12A);
    func_801E3EE0(rdram, ctx);
        goto after_28;
    // 0x802C6730: addiu       $a3, $a3, 0x12A
    ctx->r7 = ADD32(ctx->r7, 0X12A);
    after_28:
    // 0x802C6734: lui         $t6, 0x802C
    ctx->r14 = S32(0X802C << 16);
    // 0x802C6738: lw          $t6, 0x76D0($t6)
    ctx->r14 = MEM_W(ctx->r14, 0X76D0);
    // 0x802C673C: addiu       $s1, $s1, 0x1
    ctx->r17 = ADD32(ctx->r17, 0X1);
    // 0x802C6740: addiu       $s3, $s3, 0xF
    ctx->r19 = ADD32(ctx->r19, 0XF);
    // 0x802C6744: slt         $at, $s1, $t6
    ctx->r1 = SIGNED(ctx->r17) < SIGNED(ctx->r14) ? 1 : 0;
    // 0x802C6748: addiu       $s2, $s2, 0x8
    ctx->r18 = ADD32(ctx->r18, 0X8);
    // 0x802C674C: bne         $at, $zero, L_802C6620
    if (ctx->r1 != 0) {
        // 0x802C6750: or          $s0, $v0, $zero
        ctx->r16 = ctx->r2 | 0;
            goto L_802C6620;
    }
    // 0x802C6750: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
L_802C6754:
    // 0x802C6754: lw          $ra, 0x54($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X54);
L_802C6758:
    { extern void wr64_course_preview_finish(uint8_t*, uint32_t); wr64_course_preview_finish(rdram, (uint32_t)ctx->r16); }
    // 0x802C6758: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
    // 0x802C675C: lw          $s0, 0x40($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X40);
    // 0x802C6760: lw          $s1, 0x44($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X44);
    // 0x802C6764: lw          $s2, 0x48($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X48);
    // 0x802C6768: lw          $s3, 0x4C($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X4C);
    // 0x802C676C: lw          $s4, 0x50($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X50);
    // 0x802C6770: jr          $ra
    // 0x802C6774: addiu       $sp, $sp, 0xD8
    ctx->r29 = ADD32(ctx->r29, 0XD8);
    return;
    // 0x802C6774: addiu       $sp, $sp, 0xD8
    ctx->r29 = ADD32(ctx->r29, 0XD8);
;}
RECOMP_FUNC void func_i4_802C6778(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    { extern void wr64_course_preview_map_begin(uint8_t*, uint32_t); wr64_course_preview_map_begin(rdram, (uint32_t)ctx->r4); }
    // 0x802C6778: lui         $t6, 0x800E
    ctx->r14 = S32(0X800E << 16);
    // 0x802C677C: lw          $t6, -0x5630($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X5630);
    // 0x802C6780: lui         $t8, 0x802C
    ctx->r24 = S32(0X802C << 16);
    // 0x802C6784: lw          $t8, 0x7534($t8)
    ctx->r24 = MEM_W(ctx->r24, 0X7534);
    // 0x802C6788: lui         $a2, 0x800E
    ctx->r6 = S32(0X800E << 16);
    // 0x802C678C: sll         $t7, $t6, 2
    ctx->r15 = S32(ctx->r14 << 2);
    // 0x802C6790: addu        $a2, $a2, $t7
    ctx->r6 = ADD32(ctx->r6, ctx->r15);
    // 0x802C6794: bne         $t8, $zero, L_802C67B0
    if (ctx->r24 != 0) {
        // 0x802C6798: lw          $a2, -0x5528($a2)
        ctx->r6 = MEM_W(ctx->r6, -0X5528);
            goto L_802C67B0;
    }
    // 0x802C6798: lw          $a2, -0x5528($a2)
    ctx->r6 = MEM_W(ctx->r6, -0X5528);
    // 0x802C679C: lui         $t9, 0x800E
    ctx->r25 = S32(0X800E << 16);
    // 0x802C67A0: addiu       $t9, $t9, -0x4A08
    ctx->r25 = ADD32(ctx->r25, -0X4A08);
    // 0x802C67A4: sll         $v0, $a2, 3
    ctx->r2 = S32(ctx->r6 << 3);
    // 0x802C67A8: b           L_802C67C0
    // 0x802C67AC: addu        $a3, $v0, $t9
    ctx->r7 = ADD32(ctx->r2, ctx->r25);
        goto L_802C67C0;
    // 0x802C67AC: addu        $a3, $v0, $t9
    ctx->r7 = ADD32(ctx->r2, ctx->r25);
L_802C67B0:
    // 0x802C67B0: lui         $t5, 0x800E
    ctx->r13 = S32(0X800E << 16);
    // 0x802C67B4: addiu       $t5, $t5, -0x4930
    ctx->r13 = ADD32(ctx->r13, -0X4930);
    // 0x802C67B8: sll         $v0, $a2, 3
    ctx->r2 = S32(ctx->r6 << 3);
    // 0x802C67BC: addu        $a3, $v0, $t5
    ctx->r7 = ADD32(ctx->r2, ctx->r13);
L_802C67C0:
    // 0x802C67C0: or          $v1, $a0, $zero
    ctx->r3 = ctx->r4 | 0;
    // 0x802C67C4: lui         $t6, 0x80A
    ctx->r14 = S32(0X80A << 16);
    // 0x802C67C8: lui         $a1, 0x600
    ctx->r5 = S32(0X600 << 16);
    // 0x802C67CC: addiu       $t6, $t6, 0x6E00
    ctx->r14 = ADD32(ctx->r14, 0X6E00);
    // 0x802C67D0: sw          $t6, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r14;
    // 0x802C67D4: sw          $a1, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r5;
    // 0x802C67D8: lui         $t0, 0xE700
    ctx->r8 = S32(0XE700 << 16);
    // 0x802C67DC: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C67E0: lui         $t7, 0xFF10
    ctx->r15 = S32(0XFF10 << 16);
    // 0x802C67E4: addiu       $t2, $a0, 0x8
    ctx->r10 = ADD32(ctx->r4, 0X8);
    // 0x802C67E8: sw          $t0, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r8;
    // 0x802C67EC: sw          $zero, 0x4($a0)
    MEM_W(0X4, ctx->r4) = 0;
    // 0x802C67F0: ori         $t7, $t7, 0x1A7
    ctx->r15 = ctx->r15 | 0X1A7;
    // 0x802C67F4: sw          $t7, 0x0($t2)
    MEM_W(0X0, ctx->r10) = ctx->r15;
    // 0x802C67F8: lui         $t8, 0x8015
    ctx->r24 = S32(0X8015 << 16);
    // 0x802C67FC: lw          $t8, 0x1948($t8)
    ctx->r24 = MEM_W(ctx->r24, 0X1948);
    // 0x802C6800: lui         $t5, 0x8015
    ctx->r13 = S32(0X8015 << 16);
    // 0x802C6804: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x802C6808: sll         $t9, $t8, 2
    ctx->r25 = S32(ctx->r24 << 2);
    // 0x802C680C: addu        $t5, $t5, $t9
    ctx->r13 = ADD32(ctx->r13, ctx->r25);
    // 0x802C6810: lw          $t5, 0x42C0($t5)
    ctx->r13 = MEM_W(ctx->r13, 0X42C0);
    // 0x802C6814: addiu       $t3, $t2, 0x8
    ctx->r11 = ADD32(ctx->r10, 0X8);
    // 0x802C6818: lui         $t7, 0xB400
    ctx->r15 = S32(0XB400 << 16);
    // 0x802C681C: addu        $t6, $t5, $at
    ctx->r14 = ADD32(ctx->r13, ctx->r1);
    // 0x802C6820: sw          $t6, 0x4($t2)
    MEM_W(0X4, ctx->r10) = ctx->r14;
    // 0x802C6824: sw          $t7, 0x0($t3)
    MEM_W(0X0, ctx->r11) = ctx->r15;
    // 0x802C6828: lui         $t8, 0x802C
    ctx->r24 = S32(0X802C << 16);
    // 0x802C682C: lhu         $t8, 0x76AC($t8)
    ctx->r24 = MEM_HU(ctx->r24, 0X76AC);
    // 0x802C6830: addiu       $t4, $t3, 0x8
    ctx->r12 = ADD32(ctx->r11, 0X8);
    // 0x802C6834: lui         $t5, 0x700
    ctx->r13 = S32(0X700 << 16);
    // 0x802C6838: lui         $t9, 0x103
    ctx->r25 = S32(0X103 << 16);
    // 0x802C683C: sw          $t8, 0x4($t3)
    MEM_W(0X4, ctx->r11) = ctx->r24;
    // 0x802C6840: ori         $t9, $t9, 0x40
    ctx->r25 = ctx->r25 | 0X40;
    // 0x802C6844: addiu       $t5, $t5, 0xA40
    ctx->r13 = ADD32(ctx->r13, 0XA40);
    // 0x802C6848: lui         $t6, 0x102
    ctx->r14 = S32(0X102 << 16);
    // 0x802C684C: sw          $t5, 0x4($t4)
    MEM_W(0X4, ctx->r12) = ctx->r13;
    // 0x802C6850: sw          $t9, 0x0($t4)
    MEM_W(0X0, ctx->r12) = ctx->r25;
    // 0x802C6854: addiu       $v1, $t4, 0x8
    ctx->r3 = ADD32(ctx->r12, 0X8);
    // 0x802C6858: ori         $t6, $t6, 0x40
    ctx->r14 = ctx->r14 | 0X40;
    // 0x802C685C: sw          $t6, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r14;
    // 0x802C6860: lui         $t7, 0x801D
    ctx->r15 = S32(0X801D << 16);
    // 0x802C6864: lw          $t7, -0x1A08($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X1A08);
    // 0x802C6868: addiu       $t1, $v1, 0x8
    ctx->r9 = ADD32(ctx->r3, 0X8);
    // 0x802C686C: lui         $t9, 0x380
    ctx->r25 = S32(0X380 << 16);
    // 0x802C6870: addiu       $t8, $t7, 0xA80
    ctx->r24 = ADD32(ctx->r15, 0XA80);
    // 0x802C6874: sw          $t8, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r24;
    // 0x802C6878: lui         $t5, 0x107
    ctx->r13 = S32(0X107 << 16);
    // 0x802C687C: addiu       $t5, $t5, -0x8C8
    ctx->r13 = ADD32(ctx->r13, -0X8C8);
    // 0x802C6880: ori         $t9, $t9, 0x10
    ctx->r25 = ctx->r25 | 0X10;
    // 0x802C6884: sw          $t9, 0x0($t1)
    MEM_W(0X0, ctx->r9) = ctx->r25;
    // 0x802C6888: sw          $t5, 0x4($t1)
    MEM_W(0X4, ctx->r9) = ctx->r13;
    // 0x802C688C: addiu       $a0, $t1, 0x8
    ctx->r4 = ADD32(ctx->r9, 0X8);
    // 0x802C6890: lui         $t6, 0x107
    ctx->r14 = S32(0X107 << 16);
    // 0x802C6894: addiu       $t6, $t6, -0x8B8
    ctx->r14 = ADD32(ctx->r14, -0X8B8);
    // 0x802C6898: sw          $t6, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r14;
    // 0x802C689C: addiu       $t3, $a0, 0x8
    ctx->r11 = ADD32(ctx->r4, 0X8);
    // 0x802C68A0: sw          $a1, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r5;
    // 0x802C68A4: addiu       $t4, $t3, 0x8
    ctx->r12 = ADD32(ctx->r11, 0X8);
    // 0x802C68A8: addiu       $t8, $zero, -0x1
    ctx->r24 = ADD32(0, -0X1);
    // 0x802C68AC: lui         $t7, 0xFB00
    ctx->r15 = S32(0XFB00 << 16);
    // 0x802C68B0: sw          $t7, 0x0($t3)
    MEM_W(0X0, ctx->r11) = ctx->r15;
    // 0x802C68B4: sw          $t8, 0x4($t3)
    MEM_W(0X4, ctx->r11) = ctx->r24;
    // 0x802C68B8: lui         $t5, 0x63
    ctx->r13 = S32(0X63 << 16);
    // 0x802C68BC: addiu       $t5, $t5, 0x27C
    ctx->r13 = ADD32(ctx->r13, 0X27C);
    // 0x802C68C0: lui         $t9, 0xED40
    ctx->r25 = S32(0XED40 << 16);
    // 0x802C68C4: addiu       $t9, $t9, -0x7F2C
    ctx->r25 = ADD32(ctx->r25, -0X7F2C);
    // 0x802C68C8: lui         $t6, 0x800E
    ctx->r14 = S32(0X800E << 16);
    // 0x802C68CC: sw          $t5, 0x4($t4)
    MEM_W(0X4, ctx->r12) = ctx->r13;
    // 0x802C68D0: sw          $t9, 0x0($t4)
    MEM_W(0X0, ctx->r12) = ctx->r25;
    // 0x802C68D4: addiu       $t2, $t4, 0x8
    ctx->r10 = ADD32(ctx->r12, 0X8);
    // 0x802C68D8: addiu       $t6, $t6, -0x4A50
    ctx->r14 = ADD32(ctx->r14, -0X4A50);
    // 0x802C68DC: addu        $t1, $v0, $t6
    ctx->r9 = ADD32(ctx->r2, ctx->r14);
    // 0x802C68E0: sw          $a1, 0x0($t2)
    MEM_W(0X0, ctx->r10) = ctx->r5;
    // 0x802C68E4: lw          $t7, 0x0($t1)
    ctx->r15 = MEM_W(ctx->r9, 0X0);
    // 0x802C68E8: sll         $v1, $a2, 15
    ctx->r3 = S32(ctx->r6 << 15);
    // 0x802C68EC: lui         $at, 0x1
    ctx->r1 = S32(0X1 << 16);
    // 0x802C68F0: addu        $v1, $v1, $at
    ctx->r3 = ADD32(ctx->r3, ctx->r1);
    // 0x802C68F4: addiu       $a0, $t2, 0x8
    ctx->r4 = ADD32(ctx->r10, 0X8);
    // 0x802C68F8: addu        $t8, $t7, $v1
    ctx->r24 = ADD32(ctx->r15, ctx->r3);
    // 0x802C68FC: sw          $t8, 0x4($t2)
    MEM_W(0X4, ctx->r10) = ctx->r24;
    // 0x802C6900: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x802C6904: lui         $t4, 0x2
    ctx->r12 = S32(0X2 << 16);
    // 0x802C6908: lui         $t9, 0xB600
    ctx->r25 = S32(0XB600 << 16);
    // 0x802C690C: sw          $t9, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r25;
    // 0x802C6910: sw          $t4, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r12;
    // 0x802C6914: addiu       $a2, $a0, 0x8
    ctx->r6 = ADD32(ctx->r4, 0X8);
    // 0x802C6918: sw          $a1, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r5;
    // 0x802C691C: lw          $t5, 0x0($a3)
    ctx->r13 = MEM_W(ctx->r7, 0X0);
    // 0x802C6920: addiu       $v0, $a2, 0x8
    ctx->r2 = ADD32(ctx->r6, 0X8);
    // 0x802C6924: addiu       $a0, $v0, 0x8
    ctx->r4 = ADD32(ctx->r2, 0X8);
    // 0x802C6928: addu        $t6, $t5, $v1
    ctx->r14 = ADD32(ctx->r13, ctx->r3);
    // 0x802C692C: sw          $t6, 0x4($a2)
    MEM_W(0X4, ctx->r6) = ctx->r14;
    // 0x802C6930: lui         $t7, 0xB700
    ctx->r15 = S32(0XB700 << 16);
    // 0x802C6934: sw          $t7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r15;
    // 0x802C6938: sw          $t4, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r12;
    // 0x802C693C: addiu       $t2, $a0, 0x8
    ctx->r10 = ADD32(ctx->r4, 0X8);
    // 0x802C6940: sw          $zero, 0x4($a0)
    MEM_W(0X4, ctx->r4) = 0;
    // 0x802C6944: sw          $t0, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r8;
    // 0x802C6948: lui         $t9, 0x50
    ctx->r25 = S32(0X50 << 16);
    // 0x802C694C: lui         $t8, 0xB900
    ctx->r24 = S32(0XB900 << 16);
    // 0x802C6950: ori         $t8, $t8, 0x31D
    ctx->r24 = ctx->r24 | 0X31D;
    // 0x802C6954: ori         $t9, $t9, 0x49D8
    ctx->r25 = ctx->r25 | 0X49D8;
    // 0x802C6958: sw          $t9, 0x4($t2)
    MEM_W(0X4, ctx->r10) = ctx->r25;
    // 0x802C695C: sw          $t8, 0x0($t2)
    MEM_W(0X0, ctx->r10) = ctx->r24;
    // 0x802C6960: addiu       $t3, $t2, 0x8
    ctx->r11 = ADD32(ctx->r10, 0X8);
    // 0x802C6964: sw          $a1, 0x0($t3)
    MEM_W(0X0, ctx->r11) = ctx->r5;
    // 0x802C6968: lw          $t5, 0x4($t1)
    ctx->r13 = MEM_W(ctx->r9, 0X4);
    // 0x802C696C: addiu       $v0, $t3, 0x8
    ctx->r2 = ADD32(ctx->r11, 0X8);
    // 0x802C6970: lui         $t7, 0xB600
    ctx->r15 = S32(0XB600 << 16);
    // 0x802C6974: addu        $t6, $t5, $v1
    ctx->r14 = ADD32(ctx->r13, ctx->r3);
    // 0x802C6978: sw          $t6, 0x4($t3)
    MEM_W(0X4, ctx->r11) = ctx->r14;
    // 0x802C697C: sw          $t4, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r12;
    // 0x802C6980: sw          $t7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r15;
    // 0x802C6984: addiu       $a2, $v0, 0x8
    ctx->r6 = ADD32(ctx->r2, 0X8);
    // 0x802C6988: sw          $a1, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r5;
    // 0x802C698C: lw          $t8, 0x4($a3)
    ctx->r24 = MEM_W(ctx->r7, 0X4);
    // 0x802C6990: addiu       $a0, $a2, 0x8
    ctx->r4 = ADD32(ctx->r6, 0X8);
    // 0x802C6994: addiu       $a1, $a0, 0x8
    ctx->r5 = ADD32(ctx->r4, 0X8);
    // 0x802C6998: addu        $t9, $t8, $v1
    ctx->r25 = ADD32(ctx->r24, ctx->r3);
    // 0x802C699C: sw          $t9, 0x4($a2)
    MEM_W(0X4, ctx->r6) = ctx->r25;
    // 0x802C69A0: lui         $t6, 0x6A
    ctx->r14 = S32(0X6A << 16);
    // 0x802C69A4: addiu       $t6, $t6, -0x3C44
    ctx->r14 = ADD32(ctx->r14, -0X3C44);
    // 0x802C69A8: sw          $zero, 0x4($a0)
    MEM_W(0X4, ctx->r4) = 0;
    // 0x802C69AC: sw          $t0, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r8;
    // 0x802C69B0: lui         $t5, 0xED00
    ctx->r13 = S32(0XED00 << 16);
    // 0x802C69B4: sw          $t5, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r13;
    // 0x802C69B8: sw          $t6, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r14;
    { extern uint32_t wr64_course_preview_map_end(uint8_t*, uint32_t); ctx->r5 = S32(wr64_course_preview_map_end(rdram, (uint32_t)ctx->r5 + 8) - 8); }
    // 0x802C69BC: jr          $ra
    // 0x802C69C0: addiu       $v0, $a1, 0x8
    ctx->r2 = ADD32(ctx->r5, 0X8);
    return;
    // 0x802C69C0: addiu       $v0, $a1, 0x8
    ctx->r2 = ADD32(ctx->r5, 0X8);
;}
RECOMP_FUNC void func_i4_802C69C4(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C69C4: addiu       $sp, $sp, -0x30
    ctx->r29 = ADD32(ctx->r29, -0X30);
    // 0x802C69C8: sw          $s0, 0x8($sp)
    MEM_W(0X8, ctx->r29) = ctx->r16;
    // 0x802C69CC: addiu       $s0, $a1, 0x76
    ctx->r16 = ADD32(ctx->r5, 0X76);
    // 0x802C69D0: sll         $t6, $s0, 2
    ctx->r14 = S32(ctx->r16 << 2);
    // 0x802C69D4: sw          $s1, 0xC($sp)
    MEM_W(0XC, ctx->r29) = ctx->r17;
    // 0x802C69D8: andi        $t7, $t6, 0xFFF
    ctx->r15 = ctx->r14 & 0XFFF;
    // 0x802C69DC: sw          $fp, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r30;
    // 0x802C69E0: sw          $s5, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r21;
    // 0x802C69E4: sw          $s4, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r20;
    // 0x802C69E8: sw          $s3, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r19;
    // 0x802C69EC: sll         $s1, $a1, 2
    ctx->r17 = S32(ctx->r5 << 2);
    // 0x802C69F0: sw          $ra, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r31;
    // 0x802C69F4: sw          $s7, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r23;
    // 0x802C69F8: sw          $s6, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r22;
    // 0x802C69FC: sw          $s2, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r18;
    // 0x802C6A00: andi        $t6, $s1, 0xFFF
    ctx->r14 = ctx->r17 & 0XFFF;
    // 0x802C6A04: lui         $s3, 0xFD10
    ctx->r19 = S32(0XFD10 << 16);
    // 0x802C6A08: lui         $s4, 0x80A
    ctx->r20 = S32(0X80A << 16);
    // 0x802C6A0C: lui         $s5, 0x708
    ctx->r21 = S32(0X708 << 16);
    // 0x802C6A10: lui         $fp, 0x71D
    ctx->r30 = S32(0X71D << 16);
    // 0x802C6A14: sll         $t8, $t7, 12
    ctx->r24 = S32(ctx->r15 << 12);
    // 0x802C6A18: lui         $at, 0xE400
    ctx->r1 = S32(0XE400 << 16);
    // 0x802C6A1C: lui         $t5, 0xF510
    ctx->r13 = S32(0XF510 << 16);
    // 0x802C6A20: ori         $t5, $t5, 0x3C00
    ctx->r13 = ctx->r13 | 0X3C00;
    // 0x802C6A24: or          $s0, $t8, $at
    ctx->r16 = ctx->r24 | ctx->r1;
    // 0x802C6A28: ori         $fp, $fp, 0x4000
    ctx->r30 = ctx->r30 | 0X4000;
    // 0x802C6A2C: ori         $s5, $s5, 0x200
    ctx->r21 = ctx->r21 | 0X200;
    // 0x802C6A30: addiu       $s4, $s4, 0x8
    ctx->r20 = ADD32(ctx->r20, 0X8);
    // 0x802C6A34: ori         $s3, $s3, 0x75
    ctx->r19 = ctx->r19 | 0X75;
    // 0x802C6A38: sll         $s1, $t6, 12
    ctx->r17 = S32(ctx->r14 << 12);
    // 0x802C6A3C: addiu       $s2, $zero, 0x40
    ctx->r18 = ADD32(0, 0X40);
    // 0x802C6A40: lui         $s6, 0xE600
    ctx->r22 = S32(0XE600 << 16);
    // 0x802C6A44: lui         $s7, 0xF400
    ctx->r23 = S32(0XF400 << 16);
    // 0x802C6A48: lui         $ra, 0xE700
    ctx->r31 = S32(0XE700 << 16);
    // 0x802C6A4C: or          $t4, $zero, $zero
    ctx->r12 = 0 | 0;
    // 0x802C6A50: or          $t2, $zero, $zero
    ctx->r10 = 0 | 0;
    // 0x802C6A54: or          $t3, $a2, $zero
    ctx->r11 = ctx->r6 | 0;
L_802C6A58:
    // 0x802C6A58: beq         $t2, $s2, L_802C6A68
    if (ctx->r10 == ctx->r18) {
        // 0x802C6A5C: or          $v0, $a0, $zero
        ctx->r2 = ctx->r4 | 0;
            goto L_802C6A68;
    }
    // 0x802C6A5C: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x802C6A60: b           L_802C6A6C
    // 0x802C6A64: addiu       $a3, $zero, 0x10
    ctx->r7 = ADD32(0, 0X10);
        goto L_802C6A6C;
    // 0x802C6A64: addiu       $a3, $zero, 0x10
    ctx->r7 = ADD32(0, 0X10);
L_802C6A68:
    // 0x802C6A68: addiu       $a3, $zero, 0x3
    ctx->r7 = ADD32(0, 0X3);
L_802C6A6C:
    // 0x802C6A6C: sll         $t8, $t4, 1
    ctx->r24 = S32(ctx->r12 << 1);
    // 0x802C6A70: addu        $t9, $s4, $t8
    ctx->r25 = ADD32(ctx->r20, ctx->r24);
    // 0x802C6A74: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C6A78: or          $v1, $a0, $zero
    ctx->r3 = ctx->r4 | 0;
    // 0x802C6A7C: sw          $t9, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r25;
    // 0x802C6A80: sw          $s3, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r19;
    // 0x802C6A84: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C6A88: or          $a1, $a0, $zero
    ctx->r5 = ctx->r4 | 0;
    // 0x802C6A8C: sw          $s5, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r21;
    // 0x802C6A90: sw          $t5, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r13;
    // 0x802C6A94: addiu       $t0, $a3, -0x1
    ctx->r8 = ADD32(ctx->r7, -0X1);
    // 0x802C6A98: sll         $t6, $t0, 2
    ctx->r14 = S32(ctx->r8 << 2);
    // 0x802C6A9C: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C6AA0: or          $a2, $a0, $zero
    ctx->r6 = ctx->r4 | 0;
    // 0x802C6AA4: andi        $t7, $t6, 0xFFF
    ctx->r15 = ctx->r14 & 0XFFF;
    // 0x802C6AA8: or          $t8, $t7, $fp
    ctx->r24 = ctx->r15 | ctx->r30;
    // 0x802C6AAC: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C6AB0: sw          $zero, 0x4($a1)
    MEM_W(0X4, ctx->r5) = 0;
    // 0x802C6AB4: sw          $s6, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r22;
    // 0x802C6AB8: sw          $t8, 0x4($a2)
    MEM_W(0X4, ctx->r6) = ctx->r24;
    // 0x802C6ABC: or          $t1, $a0, $zero
    ctx->r9 = ctx->r4 | 0;
    // 0x802C6AC0: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C6AC4: sw          $s7, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r23;
    // 0x802C6AC8: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x802C6ACC: lui         $t9, 0x8
    ctx->r25 = S32(0X8 << 16);
    // 0x802C6AD0: ori         $t9, $t9, 0x200
    ctx->r25 = ctx->r25 | 0X200;
    // 0x802C6AD4: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C6AD8: sw          $zero, 0x4($t1)
    MEM_W(0X4, ctx->r9) = 0;
    // 0x802C6ADC: sw          $ra, 0x0($t1)
    MEM_W(0X0, ctx->r9) = ctx->r31;
    // 0x802C6AE0: sw          $t9, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r25;
    // 0x802C6AE4: or          $v1, $a0, $zero
    ctx->r3 = ctx->r4 | 0;
    // 0x802C6AE8: lui         $at, 0x1D
    ctx->r1 = S32(0X1D << 16);
    // 0x802C6AEC: ori         $at, $at, 0x4000
    ctx->r1 = ctx->r1 | 0X4000;
    // 0x802C6AF0: sw          $t5, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r13;
    // 0x802C6AF4: lui         $t6, 0xF200
    ctx->r14 = S32(0XF200 << 16);
    // 0x802C6AF8: addu        $t8, $t3, $a3
    ctx->r24 = ADD32(ctx->r11, ctx->r7);
    // 0x802C6AFC: sw          $t6, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r14;
    // 0x802C6B00: or          $t7, $t7, $at
    ctx->r15 = ctx->r15 | ctx->r1;
    // 0x802C6B04: sll         $t9, $t8, 2
    ctx->r25 = S32(ctx->r24 << 2);
    // 0x802C6B08: sw          $t7, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r15;
    // 0x802C6B0C: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C6B10: andi        $t6, $t9, 0xFFF
    ctx->r14 = ctx->r25 & 0XFFF;
    // 0x802C6B14: or          $t7, $s0, $t6
    ctx->r15 = ctx->r16 | ctx->r14;
    // 0x802C6B18: or          $a1, $a0, $zero
    ctx->r5 = ctx->r4 | 0;
    // 0x802C6B1C: sll         $t8, $t3, 2
    ctx->r24 = S32(ctx->r11 << 2);
    // 0x802C6B20: andi        $t9, $t8, 0xFFF
    ctx->r25 = ctx->r24 & 0XFFF;
    // 0x802C6B24: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C6B28: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x802C6B2C: or          $t6, $s1, $t9
    ctx->r14 = ctx->r17 | ctx->r25;
    // 0x802C6B30: sw          $t7, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r15;
    // 0x802C6B34: sw          $t6, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r14;
    // 0x802C6B38: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C6B3C: or          $v1, $a0, $zero
    ctx->r3 = ctx->r4 | 0;
    // 0x802C6B40: lui         $t7, 0xB300
    ctx->r15 = S32(0XB300 << 16);
    // 0x802C6B44: lui         $t9, 0x400
    ctx->r25 = S32(0X400 << 16);
    // 0x802C6B48: addiu       $at, $zero, 0x50
    ctx->r1 = ADD32(0, 0X50);
    // 0x802C6B4C: addiu       $t2, $t2, 0x10
    ctx->r10 = ADD32(ctx->r10, 0X10);
    // 0x802C6B50: ori         $t9, $t9, 0x400
    ctx->r25 = ctx->r25 | 0X400;
    // 0x802C6B54: sw          $t7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r15;
    // 0x802C6B58: sw          $zero, 0x4($v0)
    MEM_W(0X4, ctx->r2) = 0;
    // 0x802C6B5C: lui         $t8, 0xB200
    ctx->r24 = S32(0XB200 << 16);
    // 0x802C6B60: addiu       $t3, $t3, 0x10
    ctx->r11 = ADD32(ctx->r11, 0X10);
    // 0x802C6B64: addiu       $t4, $t4, 0x760
    ctx->r12 = ADD32(ctx->r12, 0X760);
    // 0x802C6B68: sw          $t8, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r24;
    // 0x802C6B6C: sw          $t9, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r25;
    // 0x802C6B70: bne         $t2, $at, L_802C6A58
    if (ctx->r10 != ctx->r1) {
        // 0x802C6B74: addiu       $a0, $a0, 0x8
        ctx->r4 = ADD32(ctx->r4, 0X8);
            goto L_802C6A58;
    }
    // 0x802C6B74: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x802C6B78: lw          $ra, 0x2C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X2C);
    // 0x802C6B7C: lw          $s0, 0x8($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X8);
    // 0x802C6B80: lw          $s1, 0xC($sp)
    ctx->r17 = MEM_W(ctx->r29, 0XC);
    // 0x802C6B84: lw          $s2, 0x10($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X10);
    // 0x802C6B88: lw          $s3, 0x14($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X14);
    // 0x802C6B8C: lw          $s4, 0x18($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X18);
    // 0x802C6B90: lw          $s5, 0x1C($sp)
    ctx->r21 = MEM_W(ctx->r29, 0X1C);
    // 0x802C6B94: lw          $s6, 0x20($sp)
    ctx->r22 = MEM_W(ctx->r29, 0X20);
    // 0x802C6B98: lw          $s7, 0x24($sp)
    ctx->r23 = MEM_W(ctx->r29, 0X24);
    // 0x802C6B9C: lw          $fp, 0x28($sp)
    ctx->r30 = MEM_W(ctx->r29, 0X28);
    // 0x802C6BA0: addiu       $sp, $sp, 0x30
    ctx->r29 = ADD32(ctx->r29, 0X30);
    // 0x802C6BA4: jr          $ra
    // 0x802C6BA8: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    return;
    // 0x802C6BA8: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
;}
RECOMP_FUNC void func_i4_802C6BAC(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C6BAC: lui         $v0, 0x802C
    ctx->r2 = S32(0X802C << 16);
    // 0x802C6BB0: lw          $v0, 0x7538($v0)
    ctx->r2 = MEM_W(ctx->r2, 0X7538);
    // 0x802C6BB4: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x802C6BB8: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x802C6BBC: beq         $v0, $zero, L_802C6BE4
    if (ctx->r2 == 0) {
        // 0x802C6BC0: addiu       $at, $zero, 0x1
        ctx->r1 = ADD32(0, 0X1);
            goto L_802C6BE4;
    }
    // 0x802C6BC0: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x802C6BC4: beq         $v0, $at, L_802C6BF4
    if (ctx->r2 == ctx->r1) {
        // 0x802C6BC8: addiu       $at, $zero, 0x2
        ctx->r1 = ADD32(0, 0X2);
            goto L_802C6BF4;
    }
    // 0x802C6BC8: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x802C6BCC: beq         $v0, $at, L_802C6C04
    if (ctx->r2 == ctx->r1) {
        // 0x802C6BD0: addiu       $at, $zero, 0x3
        ctx->r1 = ADD32(0, 0X3);
            goto L_802C6C04;
    }
    // 0x802C6BD0: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x802C6BD4: beq         $v0, $at, L_802C6C14
    if (ctx->r2 == ctx->r1) {
        // 0x802C6BD8: nop
    
            goto L_802C6C14;
    }
    // 0x802C6BD8: nop

    // 0x802C6BDC: b           L_802C6C20
    // 0x802C6BE0: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_802C6C20;
    // 0x802C6BE0: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C6BE4:
    // 0x802C6BE4: jal         0x802C6C2C
    // 0x802C6BE8: nop

    func_i4_802C6C2C(rdram, ctx);
        goto after_0;
    // 0x802C6BE8: nop

    after_0:
    // 0x802C6BEC: b           L_802C6C20
    // 0x802C6BF0: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_802C6C20;
    // 0x802C6BF0: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C6BF4:
    // 0x802C6BF4: jal         0x802C6ED0
    // 0x802C6BF8: nop

    func_i4_802C6ED0(rdram, ctx);
        goto after_1;
    // 0x802C6BF8: nop

    after_1:
    // 0x802C6BFC: b           L_802C6C20
    // 0x802C6C00: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_802C6C20;
    // 0x802C6C00: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C6C04:
    // 0x802C6C04: jal         0x802C70C0
    // 0x802C6C08: nop

    func_i4_802C70C0(rdram, ctx);
        goto after_2;
    // 0x802C6C08: nop

    after_2:
    // 0x802C6C0C: b           L_802C6C20
    // 0x802C6C10: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_802C6C20;
    // 0x802C6C10: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C6C14:
    // 0x802C6C14: jal         0x802C7344
    // 0x802C6C18: nop

    func_i4_802C7344(rdram, ctx);
        goto after_3;
    // 0x802C6C18: nop

    after_3:
    // 0x802C6C1C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C6C20:
    // 0x802C6C20: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x802C6C24: jr          $ra
    // 0x802C6C28: nop

    return;
    // 0x802C6C28: nop

;}
RECOMP_FUNC void func_i4_802C6C2C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    { extern void wr64_free_ride_course_refresh(uint8_t*); wr64_free_ride_course_refresh(rdram); }
    // 0x802C6C2C: lui         $t6, 0x802C
    ctx->r14 = S32(0X802C << 16);
    // 0x802C6C30: lw          $t6, 0x76B0($t6)
    ctx->r14 = MEM_W(ctx->r14, 0X76B0);
    // 0x802C6C34: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x802C6C38: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x802C6C3C: sll         $t7, $t6, 3
    ctx->r15 = S32(ctx->r14 << 3);
    // 0x802C6C40: subu        $t7, $t7, $t6
    ctx->r15 = SUB32(ctx->r15, ctx->r14);
    // 0x802C6C44: sll         $t7, $t7, 2
    ctx->r15 = S32(ctx->r15 << 2);
    // 0x802C6C48: addu        $v0, $v0, $t7
    ctx->r2 = ADD32(ctx->r2, ctx->r15);
    // 0x802C6C4C: lhu         $v0, -0x19A6($v0)
    ctx->r2 = MEM_HU(ctx->r2, -0X19A6);
    // 0x802C6C50: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x802C6C54: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x802C6C58: andi        $t8, $v0, 0xB000
    ctx->r24 = ctx->r2 & 0XB000;
    // 0x802C6C5C: beq         $t8, $zero, L_802C6D30
    if (ctx->r24 == 0) {
        // 0x802C6C60: andi        $t7, $v0, 0x4000
        ctx->r15 = ctx->r2 & 0X4000;
            goto L_802C6D30;
    }
    // 0x802C6C60: andi        $t7, $v0, 0x4000
    ctx->r15 = ctx->r2 & 0X4000;
    // 0x802C6C64: lui         $t9, 0x801D
    ctx->r25 = S32(0X801D << 16);
    // 0x802C6C68: lw          $t9, -0x19F8($t9)
    ctx->r25 = MEM_W(ctx->r25, -0X19F8);
    // 0x802C6C6C: sw          $zero, -0x7DC0($at)
    MEM_W(-0X7DC0, ctx->r1) = 0;
    // 0x802C6C70: addiu       $at, $zero, 0xB
    ctx->r1 = ADD32(0, 0XB);
    { extern uint32_t wr64_free_ride_course_confirm(uint8_t*); if (wr64_free_ride_course_confirm(rdram)) ctx->r25 = 11; }
    // 0x802C6C74: bne         $t9, $at, L_802C6C98
    if (ctx->r25 != ctx->r1) {
        // 0x802C6C78: addiu       $a2, $zero, 0x1
        ctx->r6 = ADD32(0, 0X1);
            goto L_802C6C98;
    }
    // 0x802C6C78: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    // 0x802C6C7C: jal         0x802C7474
    // 0x802C6C80: addiu       $a0, $zero, 0x28
    ctx->r4 = ADD32(0, 0X28);
    func_i4_802C7474(rdram, ctx);
        goto after_0;
    // 0x802C6C80: addiu       $a0, $zero, 0x28
    ctx->r4 = ADD32(0, 0X28);
    after_0:
    // 0x802C6C84: addiu       $a0, $zero, 0x37
    ctx->r4 = ADD32(0, 0X37);
    // 0x802C6C88: jal         0x800C37F4
    // 0x802C6C8C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_1;
    // 0x802C6C8C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_1:
    // 0x802C6C90: b           L_802C6EB8
    // 0x802C6C94: nop

        goto L_802C6EB8;
    // 0x802C6C94: nop

L_802C6C98:
    // 0x802C6C98: lui         $t0, 0x800E
    ctx->r8 = S32(0X800E << 16);
    // 0x802C6C9C: lw          $t0, -0x5630($t0)
    ctx->r8 = MEM_W(ctx->r8, -0X5630);
    // 0x802C6CA0: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C6CA4: sw          $a2, 0x7538($at)
    MEM_W(0X7538, ctx->r1) = ctx->r6;
    // 0x802C6CA8: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C6CAC: sw          $zero, 0x753C($at)
    MEM_W(0X753C, ctx->r1) = 0;
    // 0x802C6CB0: lui         $t2, 0x800E
    ctx->r10 = S32(0X800E << 16);
    // 0x802C6CB4: sll         $t1, $t0, 2
    ctx->r9 = S32(ctx->r8 << 2);
    // 0x802C6CB8: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C6CBC: addu        $t2, $t2, $t1
    ctx->r10 = ADD32(ctx->r10, ctx->r9);
    // 0x802C6CC0: lw          $t2, -0x5528($t2)
    ctx->r10 = MEM_W(ctx->r10, -0X5528);
    // 0x802C6CC4: sw          $zero, 0x7540($at)
    MEM_W(0X7540, ctx->r1) = 0;
    // 0x802C6CC8: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C6CCC: sw          $a2, 0x7544($at)
    MEM_W(0X7544, ctx->r1) = ctx->r6;
    // 0x802C6CD0: lui         $t4, 0x802C
    ctx->r12 = S32(0X802C << 16);
    // 0x802C6CD4: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C6CD8: addiu       $t4, $t4, 0x757C
    ctx->r12 = ADD32(ctx->r12, 0X757C);
    // 0x802C6CDC: sll         $t3, $t2, 4
    ctx->r11 = S32(ctx->r10 << 4);
    // 0x802C6CE0: sw          $a2, 0x7550($at)
    MEM_W(0X7550, ctx->r1) = ctx->r6;
    // 0x802C6CE4: addu        $v0, $t3, $t4
    ctx->r2 = ADD32(ctx->r11, ctx->r12);
    // 0x802C6CE8: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
    // 0x802C6CEC: addiu       $a0, $zero, 0x4
    ctx->r4 = ADD32(0, 0X4);
L_802C6CF0:
    // 0x802C6CF0: lw          $t5, 0x0($v0)
    ctx->r13 = MEM_W(ctx->r2, 0X0);
    // 0x802C6CF4: bne         $t5, $zero, L_802C6D08
    if (ctx->r13 != 0) {
        // 0x802C6CF8: nop
    
            goto L_802C6D08;
    }
    // 0x802C6CF8: nop

    // 0x802C6CFC: addiu       $v1, $v1, 0x1
    ctx->r3 = ADD32(ctx->r3, 0X1);
    // 0x802C6D00: bne         $v1, $a0, L_802C6CF0
    if (ctx->r3 != ctx->r4) {
        // 0x802C6D04: addiu       $v0, $v0, 0x4
        ctx->r2 = ADD32(ctx->r2, 0X4);
            goto L_802C6CF0;
    }
    // 0x802C6D04: addiu       $v0, $v0, 0x4
    ctx->r2 = ADD32(ctx->r2, 0X4);
L_802C6D08:
    // 0x802C6D08: lui         $v0, 0x802C
    ctx->r2 = S32(0X802C << 16);
    // 0x802C6D0C: addiu       $v0, $v0, 0x754C
    ctx->r2 = ADD32(ctx->r2, 0X754C);
    // 0x802C6D10: sw          $v1, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r3;
    // 0x802C6D14: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C6D18: sw          $v1, 0x76CC($at)
    MEM_W(0X76CC, ctx->r1) = ctx->r3;
    // 0x802C6D1C: addiu       $a0, $zero, 0x11
    ctx->r4 = ADD32(0, 0X11);
    // 0x802C6D20: jal         0x800C37F4
    // 0x802C6D24: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_2;
    // 0x802C6D24: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_2:
    // 0x802C6D28: b           L_802C6EB8
    // 0x802C6D2C: nop

        goto L_802C6EB8;
    // 0x802C6D2C: nop

L_802C6D30:
    // 0x802C6D30: beq         $t7, $zero, L_802C6D54
    if (ctx->r15 == 0) {
        // 0x802C6D34: andi        $t8, $v0, 0x800
        ctx->r24 = ctx->r2 & 0X800;
            goto L_802C6D54;
    }
    // 0x802C6D34: andi        $t8, $v0, 0x800
    ctx->r24 = ctx->r2 & 0X800;
    // 0x802C6D38: jal         0x802C7474
    // 0x802C6D3C: addiu       $a0, $zero, 0xA
    ctx->r4 = ADD32(0, 0XA);
    func_i4_802C7474(rdram, ctx);
        goto after_3;
    // 0x802C6D3C: addiu       $a0, $zero, 0xA
    ctx->r4 = ADD32(0, 0XA);
    after_3:
    // 0x802C6D40: addiu       $a0, $zero, 0x16
    ctx->r4 = ADD32(0, 0X16);
    // 0x802C6D44: jal         0x800C37F4
    // 0x802C6D48: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_4;
    // 0x802C6D48: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_4:
    // 0x802C6D4C: b           L_802C6EB8
    // 0x802C6D50: nop

        goto L_802C6EB8;
    // 0x802C6D50: nop

L_802C6D54:
    // 0x802C6D54: beq         $t8, $zero, L_802C6E0C
    if (ctx->r24 == 0) {
        // 0x802C6D58: andi        $t9, $v0, 0x400
        ctx->r25 = ctx->r2 & 0X400;
            goto L_802C6E0C;
    }
    // 0x802C6D58: andi        $t9, $v0, 0x400
    ctx->r25 = ctx->r2 & 0X400;
    // 0x802C6D5C: lui         $v1, 0x800E
    ctx->r3 = S32(0X800E << 16);
    // 0x802C6D60: addiu       $v1, $v1, -0x5630
    ctx->r3 = ADD32(ctx->r3, -0X5630);
    // 0x802C6D64: lui         $a3, 0x802C
    ctx->r7 = S32(0X802C << 16);
    // 0x802C6D68: lw          $t9, 0x0($v1)
    ctx->r25 = MEM_W(ctx->r3, 0X0);
    // 0x802C6D6C: addiu       $a3, $a3, 0x76A4
    ctx->r7 = ADD32(ctx->r7, 0X76A4);
    // 0x802C6D70: lw          $a2, 0x0($a3)
    ctx->r6 = MEM_W(ctx->r7, 0X0);
    // 0x802C6D74: addiu       $v0, $t9, -0x1
    ctx->r2 = ADD32(ctx->r25, -0X1);
    // 0x802C6D78: sw          $v0, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r2;
    // 0x802C6D7C: slt         $at, $v0, $a2
    ctx->r1 = SIGNED(ctx->r2) < SIGNED(ctx->r6) ? 1 : 0;
    // 0x802C6D80: beq         $at, $zero, L_802C6D90
    if (ctx->r1 == 0) {
        // 0x802C6D84: addiu       $a3, $zero, 0x8
        ctx->r7 = ADD32(0, 0X8);
            goto L_802C6D90;
    }
    // 0x802C6D84: addiu       $a3, $zero, 0x8
    ctx->r7 = ADD32(0, 0X8);
    // 0x802C6D88: addiu       $v0, $zero, 0x8
    ctx->r2 = ADD32(0, 0X8);
    // 0x802C6D8C: sw          $v0, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r2;
L_802C6D90:
    // 0x802C6D90: lui         $a1, 0x800E
    ctx->r5 = S32(0X800E << 16);
    // 0x802C6D94: lui         $a0, 0x802C
    ctx->r4 = S32(0X802C << 16);
    // 0x802C6D98: addiu       $a0, $a0, 0x7558
    ctx->r4 = ADD32(ctx->r4, 0X7558);
    // 0x802C6D9C: addiu       $a1, $a1, -0x5528
    ctx->r5 = ADD32(ctx->r5, -0X5528);
L_802C6DA0:
    // 0x802C6DA0: sll         $t1, $v0, 2
    ctx->r9 = S32(ctx->r2 << 2);
    // 0x802C6DA4: addu        $t2, $a1, $t1
    ctx->r10 = ADD32(ctx->r5, ctx->r9);
    // 0x802C6DA8: lw          $t3, 0x0($t2)
    ctx->r11 = MEM_W(ctx->r10, 0X0);
    // 0x802C6DAC: addiu       $t7, $v0, -0x1
    ctx->r15 = ADD32(ctx->r2, -0X1);
    // 0x802C6DB0: slt         $at, $t7, $a2
    ctx->r1 = SIGNED(ctx->r15) < SIGNED(ctx->r6) ? 1 : 0;
    // 0x802C6DB4: sll         $t4, $t3, 2
    ctx->r12 = S32(ctx->r11 << 2);
    // 0x802C6DB8: addu        $t5, $a0, $t4
    ctx->r13 = ADD32(ctx->r4, ctx->r12);
    // 0x802C6DBC: lw          $t6, 0x0($t5)
    ctx->r14 = MEM_W(ctx->r13, 0X0);
    // 0x802C6DC0: bne         $t6, $zero, L_802C6DE0
    if (ctx->r14 != 0) {
        // 0x802C6DC4: nop
    
            goto L_802C6DE0;
    }
    // 0x802C6DC4: nop

    // 0x802C6DC8: sw          $t7, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r15;
    // 0x802C6DCC: beq         $at, $zero, L_802C6DA0
    if (ctx->r1 == 0) {
        // 0x802C6DD0: or          $v0, $t7, $zero
        ctx->r2 = ctx->r15 | 0;
            goto L_802C6DA0;
    }
    // 0x802C6DD0: or          $v0, $t7, $zero
    ctx->r2 = ctx->r15 | 0;
    // 0x802C6DD4: sw          $a3, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r7;
    // 0x802C6DD8: b           L_802C6DA0
    // 0x802C6DDC: or          $v0, $a3, $zero
    ctx->r2 = ctx->r7 | 0;
        goto L_802C6DA0;
    // 0x802C6DDC: or          $v0, $a3, $zero
    ctx->r2 = ctx->r7 | 0;
L_802C6DE0:
    // 0x802C6DE0: lui         $t8, 0x802C
    ctx->r24 = S32(0X802C << 16);
    // 0x802C6DE4: lw          $t8, 0x76A8($t8)
    ctx->r24 = MEM_W(ctx->r24, 0X76A8);
    // 0x802C6DE8: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    // 0x802C6DEC: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C6DF0: beq         $t8, $v0, L_802C6EB8
    if (ctx->r24 == ctx->r2) {
        // 0x802C6DF4: addiu       $a0, $zero, 0x10
        ctx->r4 = ADD32(0, 0X10);
            goto L_802C6EB8;
    }
    // 0x802C6DF4: addiu       $a0, $zero, 0x10
    ctx->r4 = ADD32(0, 0X10);
    // 0x802C6DF8: sw          $a2, 0x7530($at)
    MEM_W(0X7530, ctx->r1) = ctx->r6;
    // 0x802C6DFC: jal         0x800C37F4
    // 0x802C6E00: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_5;
    // 0x802C6E00: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_5:
    // 0x802C6E04: b           L_802C6EB8
    // 0x802C6E08: nop

        goto L_802C6EB8;
    // 0x802C6E08: nop

L_802C6E0C:
    // 0x802C6E0C: beq         $t9, $zero, L_802C6EB8
    if (ctx->r25 == 0) {
        // 0x802C6E10: lui         $v1, 0x800E
        ctx->r3 = S32(0X800E << 16);
            goto L_802C6EB8;
    }
    // 0x802C6E10: lui         $v1, 0x800E
    ctx->r3 = S32(0X800E << 16);
    // 0x802C6E14: addiu       $v1, $v1, -0x5630
    ctx->r3 = ADD32(ctx->r3, -0X5630);
    // 0x802C6E18: lw          $t0, 0x0($v1)
    ctx->r8 = MEM_W(ctx->r3, 0X0);
    // 0x802C6E1C: lui         $a1, 0x800E
    ctx->r5 = S32(0X800E << 16);
    // 0x802C6E20: addiu       $a1, $a1, -0x5528
    ctx->r5 = ADD32(ctx->r5, -0X5528);
    // 0x802C6E24: addiu       $v0, $t0, 0x1
    ctx->r2 = ADD32(ctx->r8, 0X1);
    // 0x802C6E28: slti        $at, $v0, 0x9
    ctx->r1 = SIGNED(ctx->r2) < 0X9 ? 1 : 0;
    // 0x802C6E2C: bne         $at, $zero, L_802C6E44
    if (ctx->r1 != 0) {
        // 0x802C6E30: sw          $v0, 0x0($v1)
        MEM_W(0X0, ctx->r3) = ctx->r2;
            goto L_802C6E44;
    }
    // 0x802C6E30: sw          $v0, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r2;
    // 0x802C6E34: lui         $a3, 0x802C
    ctx->r7 = S32(0X802C << 16);
    // 0x802C6E38: addiu       $a3, $a3, 0x76A4
    ctx->r7 = ADD32(ctx->r7, 0X76A4);
    // 0x802C6E3C: lw          $v0, 0x0($a3)
    ctx->r2 = MEM_W(ctx->r7, 0X0);
    // 0x802C6E40: sw          $v0, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r2;
L_802C6E44:
    // 0x802C6E44: lui         $a3, 0x802C
    ctx->r7 = S32(0X802C << 16);
    // 0x802C6E48: lui         $a0, 0x802C
    ctx->r4 = S32(0X802C << 16);
    // 0x802C6E4C: addiu       $a3, $a3, 0x76A4
    ctx->r7 = ADD32(ctx->r7, 0X76A4);
    // 0x802C6E50: addiu       $a0, $a0, 0x7558
    ctx->r4 = ADD32(ctx->r4, 0X7558);
L_802C6E54:
    // 0x802C6E54: sll         $t3, $v0, 2
    ctx->r11 = S32(ctx->r2 << 2);
    // 0x802C6E58: addu        $t4, $a1, $t3
    ctx->r12 = ADD32(ctx->r5, ctx->r11);
    // 0x802C6E5C: lw          $t5, 0x0($t4)
    ctx->r13 = MEM_W(ctx->r12, 0X0);
    // 0x802C6E60: addiu       $t9, $v0, 0x1
    ctx->r25 = ADD32(ctx->r2, 0X1);
    // 0x802C6E64: slti        $at, $t9, 0x9
    ctx->r1 = SIGNED(ctx->r25) < 0X9 ? 1 : 0;
    // 0x802C6E68: sll         $t6, $t5, 2
    ctx->r14 = S32(ctx->r13 << 2);
    // 0x802C6E6C: addu        $t7, $a0, $t6
    ctx->r15 = ADD32(ctx->r4, ctx->r14);
    // 0x802C6E70: lw          $t8, 0x0($t7)
    ctx->r24 = MEM_W(ctx->r15, 0X0);
    // 0x802C6E74: bne         $t8, $zero, L_802C6E94
    if (ctx->r24 != 0) {
        // 0x802C6E78: nop
    
            goto L_802C6E94;
    }
    // 0x802C6E78: nop

    // 0x802C6E7C: sw          $t9, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r25;
    // 0x802C6E80: bne         $at, $zero, L_802C6E54
    if (ctx->r1 != 0) {
        // 0x802C6E84: or          $v0, $t9, $zero
        ctx->r2 = ctx->r25 | 0;
            goto L_802C6E54;
    }
    // 0x802C6E84: or          $v0, $t9, $zero
    ctx->r2 = ctx->r25 | 0;
    // 0x802C6E88: lw          $v0, 0x0($a3)
    ctx->r2 = MEM_W(ctx->r7, 0X0);
    // 0x802C6E8C: b           L_802C6E54
    // 0x802C6E90: sw          $v0, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r2;
        goto L_802C6E54;
    // 0x802C6E90: sw          $v0, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r2;
L_802C6E94:
    // 0x802C6E94: lui         $t1, 0x802C
    ctx->r9 = S32(0X802C << 16);
    // 0x802C6E98: lw          $t1, 0x76A8($t1)
    ctx->r9 = MEM_W(ctx->r9, 0X76A8);
    // 0x802C6E9C: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    // 0x802C6EA0: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C6EA4: beq         $t1, $v0, L_802C6EB8
    if (ctx->r9 == ctx->r2) {
        // 0x802C6EA8: addiu       $a0, $zero, 0x10
        ctx->r4 = ADD32(0, 0X10);
            goto L_802C6EB8;
    }
    // 0x802C6EA8: addiu       $a0, $zero, 0x10
    ctx->r4 = ADD32(0, 0X10);
    // 0x802C6EAC: sw          $a2, 0x7530($at)
    MEM_W(0X7530, ctx->r1) = ctx->r6;
    // 0x802C6EB0: jal         0x800C37F4
    // 0x802C6EB4: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_6;
    // 0x802C6EB4: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_6:
L_802C6EB8:
    // 0x802C6EB8: jal         0x80047E50
    // 0x802C6EBC: nop

    SysUtils_Rand(rdram, ctx);
        goto after_7;
    // 0x802C6EBC: nop

    after_7:
    // 0x802C6EC0: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x802C6EC4: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x802C6EC8: jr          $ra
    // 0x802C6ECC: nop

    return;
    // 0x802C6ECC: nop

;}
RECOMP_FUNC void func_i4_802C6ED0(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C6ED0: lui         $v0, 0x802C
    ctx->r2 = S32(0X802C << 16);
    // 0x802C6ED4: lw          $v0, 0x7544($v0)
    ctx->r2 = MEM_W(ctx->r2, 0X7544);
    // 0x802C6ED8: addiu       $v1, $zero, 0x1
    ctx->r3 = ADD32(0, 0X1);
    // 0x802C6EDC: lui         $a0, 0x802C
    ctx->r4 = S32(0X802C << 16);
    // 0x802C6EE0: beq         $v0, $v1, L_802C6EFC
    if (ctx->r2 == ctx->r3) {
        // 0x802C6EE4: addiu       $a0, $a0, 0x753C
        ctx->r4 = ADD32(ctx->r4, 0X753C);
            goto L_802C6EFC;
    }
    // 0x802C6EE4: addiu       $a0, $a0, 0x753C
    ctx->r4 = ADD32(ctx->r4, 0X753C);
    // 0x802C6EE8: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x802C6EEC: beq         $v0, $at, L_802C6FE4
    if (ctx->r2 == ctx->r1) {
        // 0x802C6EF0: lui         $a0, 0x802C
        ctx->r4 = S32(0X802C << 16);
            goto L_802C6FE4;
    }
    // 0x802C6EF0: lui         $a0, 0x802C
    ctx->r4 = S32(0X802C << 16);
    // 0x802C6EF4: jr          $ra
    // 0x802C6EF8: nop

    return;
    // 0x802C6EF8: nop

L_802C6EFC:
    // 0x802C6EFC: lui         $at, 0x40A0
    ctx->r1 = S32(0X40A0 << 16);
    // 0x802C6F00: mtc1        $at, $f12
    ctx->f12.u32l = ctx->r1;
    // 0x802C6F04: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C6F08: sw          $v1, 0x7540($at)
    MEM_W(0X7540, ctx->r1) = ctx->r3;
    // 0x802C6F0C: lw          $v0, 0x0($a0)
    ctx->r2 = MEM_W(ctx->r4, 0X0);
    // 0x802C6F10: addiu       $t6, $zero, 0x5
    ctx->r14 = ADD32(0, 0X5);
    // 0x802C6F14: lui         $at, 0x428E
    ctx->r1 = S32(0X428E << 16);
    // 0x802C6F18: subu        $t7, $t6, $v0
    ctx->r15 = SUB32(ctx->r14, ctx->r2);
    // 0x802C6F1C: mtc1        $t7, $f4
    ctx->f4.u32l = ctx->r15;
    // 0x802C6F20: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
    // 0x802C6F24: mtc1        $v0, $f8
    ctx->f8.u32l = ctx->r2;
    // 0x802C6F28: cvt.s.w     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
    // 0x802C6F2C: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C6F30: addiu       $t8, $v0, 0x1
    ctx->r24 = ADD32(ctx->r2, 0X1);
    // 0x802C6F34: cvt.s.w     $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.fl = CVT_S_W(ctx->f8.u32l);
    // 0x802C6F38: div.s       $f0, $f6, $f12
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f0.fl = DIV_S(ctx->f6.fl, ctx->f12.fl);
    // 0x802C6F3C: div.s       $f2, $f10, $f12
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f2.fl = DIV_S(ctx->f10.fl, ctx->f12.fl);
    // 0x802C6F40: mul.s       $f18, $f16, $f0
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f18.fl = MUL_S(ctx->f16.fl, ctx->f0.fl);
    // 0x802C6F44: trunc.w.s   $f4, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    ctx->f4.u32l = TRUNC_W_S(ctx->f18.fl);
    // 0x802C6F48: mfc1        $t9, $f4
    ctx->r25 = (int32_t)ctx->f4.u32l;
    // 0x802C6F4C: nop

    // 0x802C6F50: addiu       $t0, $t9, 0xF6
    ctx->r8 = ADD32(ctx->r25, 0XF6);
    // 0x802C6F54: sw          $t0, 0x76B4($at)
    MEM_W(0X76B4, ctx->r1) = ctx->r8;
    // 0x802C6F58: lui         $at, 0x4254
    ctx->r1 = S32(0X4254 << 16);
    // 0x802C6F5C: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x802C6F60: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C6F64: addiu       $t0, $zero, 0x2
    ctx->r8 = ADD32(0, 0X2);
    // 0x802C6F68: mul.s       $f8, $f6, $f0
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f8.fl = MUL_S(ctx->f6.fl, ctx->f0.fl);
    // 0x802C6F6C: trunc.w.s   $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.u32l = TRUNC_W_S(ctx->f8.fl);
    // 0x802C6F70: mfc1        $t2, $f10
    ctx->r10 = (int32_t)ctx->f10.u32l;
    // 0x802C6F74: nop

    // 0x802C6F78: addiu       $t3, $t2, 0x21
    ctx->r11 = ADD32(ctx->r10, 0X21);
    // 0x802C6F7C: sw          $t3, 0x76B8($at)
    MEM_W(0X76B8, ctx->r1) = ctx->r11;
    // 0x802C6F80: lui         $at, 0x430E
    ctx->r1 = S32(0X430E << 16);
    // 0x802C6F84: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
    // 0x802C6F88: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C6F8C: mul.s       $f18, $f16, $f2
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f18.fl = MUL_S(ctx->f16.fl, ctx->f2.fl);
    // 0x802C6F90: trunc.w.s   $f4, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    ctx->f4.u32l = TRUNC_W_S(ctx->f18.fl);
    // 0x802C6F94: mfc1        $t5, $f4
    ctx->r13 = (int32_t)ctx->f4.u32l;
    // 0x802C6F98: nop

    // 0x802C6F9C: sw          $t5, 0x76BC($at)
    MEM_W(0X76BC, ctx->r1) = ctx->r13;
    // 0x802C6FA0: lui         $at, 0x42D4
    ctx->r1 = S32(0X42D4 << 16);
    // 0x802C6FA4: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x802C6FA8: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C6FAC: mul.s       $f8, $f6, $f2
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f8.fl = MUL_S(ctx->f6.fl, ctx->f2.fl);
    // 0x802C6FB0: trunc.w.s   $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.u32l = TRUNC_W_S(ctx->f8.fl);
    // 0x802C6FB4: mfc1        $t7, $f10
    ctx->r15 = (int32_t)ctx->f10.u32l;
    // 0x802C6FB8: nop

    // 0x802C6FBC: sw          $t7, 0x76C0($at)
    MEM_W(0X76C0, ctx->r1) = ctx->r15;
    // 0x802C6FC0: slti        $at, $t8, 0x6
    ctx->r1 = SIGNED(ctx->r24) < 0X6 ? 1 : 0;
    // 0x802C6FC4: bne         $at, $zero, L_802C70B8
    if (ctx->r1 != 0) {
        // 0x802C6FC8: sw          $t8, 0x0($a0)
        MEM_W(0X0, ctx->r4) = ctx->r24;
            goto L_802C70B8;
    }
    // 0x802C6FC8: sw          $t8, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r24;
    // 0x802C6FCC: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C6FD0: sw          $t0, 0x7538($at)
    MEM_W(0X7538, ctx->r1) = ctx->r8;
    // 0x802C6FD4: sw          $zero, 0x0($a0)
    MEM_W(0X0, ctx->r4) = 0;
    // 0x802C6FD8: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C6FDC: jr          $ra
    // 0x802C6FE0: sw          $v1, 0x7548($at)
    MEM_W(0X7548, ctx->r1) = ctx->r3;
    return;
    // 0x802C6FE0: sw          $v1, 0x7548($at)
    MEM_W(0X7548, ctx->r1) = ctx->r3;
L_802C6FE4:
    // 0x802C6FE4: addiu       $a0, $a0, 0x753C
    ctx->r4 = ADD32(ctx->r4, 0X753C);
    // 0x802C6FE8: lw          $v0, 0x0($a0)
    ctx->r2 = MEM_W(ctx->r4, 0X0);
    // 0x802C6FEC: lui         $at, 0x40A0
    ctx->r1 = S32(0X40A0 << 16);
    // 0x802C6FF0: mtc1        $at, $f12
    ctx->f12.u32l = ctx->r1;
    // 0x802C6FF4: mtc1        $v0, $f4
    ctx->f4.u32l = ctx->r2;
    // 0x802C6FF8: lui         $at, 0x428E
    ctx->r1 = S32(0X428E << 16);
    // 0x802C6FFC: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x802C7000: cvt.s.w     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
    // 0x802C7004: addiu       $t1, $zero, 0x5
    ctx->r9 = ADD32(0, 0X5);
    // 0x802C7008: subu        $t2, $t1, $v0
    ctx->r10 = SUB32(ctx->r9, ctx->r2);
    // 0x802C700C: mtc1        $t2, $f16
    ctx->f16.u32l = ctx->r10;
    // 0x802C7010: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C7014: addiu       $t3, $v0, 0x1
    ctx->r11 = ADD32(ctx->r2, 0X1);
    // 0x802C7018: div.s       $f2, $f6, $f12
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f2.fl = DIV_S(ctx->f6.fl, ctx->f12.fl);
    // 0x802C701C: cvt.s.w     $f18, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    ctx->f18.fl = CVT_S_W(ctx->f16.u32l);
    // 0x802C7020: div.s       $f0, $f18, $f12
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f0.fl = DIV_S(ctx->f18.fl, ctx->f12.fl);
    // 0x802C7024: mul.s       $f10, $f8, $f2
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f10.fl = MUL_S(ctx->f8.fl, ctx->f2.fl);
    // 0x802C7028: trunc.w.s   $f16, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    ctx->f16.u32l = TRUNC_W_S(ctx->f10.fl);
    // 0x802C702C: mfc1        $t4, $f16
    ctx->r12 = (int32_t)ctx->f16.u32l;
    // 0x802C7030: nop

    // 0x802C7034: addiu       $t5, $t4, 0xF6
    ctx->r13 = ADD32(ctx->r12, 0XF6);
    // 0x802C7038: sw          $t5, 0x76B4($at)
    MEM_W(0X76B4, ctx->r1) = ctx->r13;
    // 0x802C703C: lui         $at, 0x4254
    ctx->r1 = S32(0X4254 << 16);
    // 0x802C7040: mtc1        $at, $f18
    ctx->f18.u32l = ctx->r1;
    // 0x802C7044: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C7048: mul.s       $f4, $f18, $f2
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f4.fl = MUL_S(ctx->f18.fl, ctx->f2.fl);
    // 0x802C704C: trunc.w.s   $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.u32l = TRUNC_W_S(ctx->f4.fl);
    // 0x802C7050: mfc1        $t7, $f6
    ctx->r15 = (int32_t)ctx->f6.u32l;
    // 0x802C7054: nop

    // 0x802C7058: addiu       $t8, $t7, 0x21
    ctx->r24 = ADD32(ctx->r15, 0X21);
    // 0x802C705C: sw          $t8, 0x76B8($at)
    MEM_W(0X76B8, ctx->r1) = ctx->r24;
    // 0x802C7060: lui         $at, 0x430E
    ctx->r1 = S32(0X430E << 16);
    // 0x802C7064: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x802C7068: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C706C: mul.s       $f10, $f8, $f0
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f10.fl = MUL_S(ctx->f8.fl, ctx->f0.fl);
    // 0x802C7070: trunc.w.s   $f16, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    ctx->f16.u32l = TRUNC_W_S(ctx->f10.fl);
    // 0x802C7074: mfc1        $t0, $f16
    ctx->r8 = (int32_t)ctx->f16.u32l;
    // 0x802C7078: nop

    // 0x802C707C: sw          $t0, 0x76BC($at)
    MEM_W(0X76BC, ctx->r1) = ctx->r8;
    // 0x802C7080: lui         $at, 0x42D4
    ctx->r1 = S32(0X42D4 << 16);
    // 0x802C7084: mtc1        $at, $f18
    ctx->f18.u32l = ctx->r1;
    // 0x802C7088: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C708C: mul.s       $f4, $f18, $f0
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f4.fl = MUL_S(ctx->f18.fl, ctx->f0.fl);
    // 0x802C7090: trunc.w.s   $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.u32l = TRUNC_W_S(ctx->f4.fl);
    // 0x802C7094: mfc1        $t2, $f6
    ctx->r10 = (int32_t)ctx->f6.u32l;
    // 0x802C7098: nop

    // 0x802C709C: sw          $t2, 0x76C0($at)
    MEM_W(0X76C0, ctx->r1) = ctx->r10;
    // 0x802C70A0: slti        $at, $t3, 0x6
    ctx->r1 = SIGNED(ctx->r11) < 0X6 ? 1 : 0;
    // 0x802C70A4: bne         $at, $zero, L_802C70B8
    if (ctx->r1 != 0) {
        // 0x802C70A8: sw          $t3, 0x0($a0)
        MEM_W(0X0, ctx->r4) = ctx->r11;
            goto L_802C70B8;
    }
    // 0x802C70A8: sw          $t3, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r11;
    // 0x802C70AC: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C70B0: sw          $zero, 0x7538($at)
    MEM_W(0X7538, ctx->r1) = 0;
    // 0x802C70B4: sw          $zero, 0x0($a0)
    MEM_W(0X0, ctx->r4) = 0;
L_802C70B8:
    // 0x802C70B8: jr          $ra
    // 0x802C70BC: nop

    return;
    // 0x802C70BC: nop

;}
RECOMP_FUNC void func_i4_802C70C0(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C70C0: lui         $t6, 0x802C
    ctx->r14 = S32(0X802C << 16);
    // 0x802C70C4: lw          $t6, 0x76B0($t6)
    ctx->r14 = MEM_W(ctx->r14, 0X76B0);
    // 0x802C70C8: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x802C70CC: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x802C70D0: sll         $t7, $t6, 3
    ctx->r15 = S32(ctx->r14 << 3);
    // 0x802C70D4: subu        $t7, $t7, $t6
    ctx->r15 = SUB32(ctx->r15, ctx->r14);
    // 0x802C70D8: sll         $t7, $t7, 2
    ctx->r15 = S32(ctx->r15 << 2);
    // 0x802C70DC: addu        $v0, $v0, $t7
    ctx->r2 = ADD32(ctx->r2, ctx->r15);
    // 0x802C70E0: lhu         $v0, -0x19A6($v0)
    ctx->r2 = MEM_HU(ctx->r2, -0X19A6);
    // 0x802C70E4: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x802C70E8: lui         $v1, 0x802C
    ctx->r3 = S32(0X802C << 16);
    // 0x802C70EC: andi        $t8, $v0, 0xB000
    ctx->r24 = ctx->r2 & 0XB000;
    // 0x802C70F0: beq         $t8, $zero, L_802C718C
    if (ctx->r24 == 0) {
        // 0x802C70F4: andi        $t1, $v0, 0x4000
        ctx->r9 = ctx->r2 & 0X4000;
            goto L_802C718C;
    }
    // 0x802C70F4: andi        $t1, $v0, 0x4000
    ctx->r9 = ctx->r2 & 0X4000;
    // 0x802C70F8: addiu       $v1, $v1, 0x754C
    ctx->r3 = ADD32(ctx->r3, 0X754C);
    // 0x802C70FC: lw          $v0, 0x0($v1)
    ctx->r2 = MEM_W(ctx->r3, 0X0);
    // 0x802C7100: addiu       $a2, $zero, 0x3
    ctx->r6 = ADD32(0, 0X3);
    // 0x802C7104: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C7108: bne         $a2, $v0, L_802C712C
    if (ctx->r6 != ctx->r2) {
        // 0x802C710C: lui         $t0, 0x801D
        ctx->r8 = S32(0X801D << 16);
            goto L_802C712C;
    }
    // 0x802C710C: lui         $t0, 0x801D
    ctx->r8 = S32(0X801D << 16);
    // 0x802C7110: addiu       $t9, $zero, 0x2
    ctx->r25 = ADD32(0, 0X2);
    // 0x802C7114: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C7118: sw          $t9, -0x4CC8($at)
    MEM_W(-0X4CC8, ctx->r1) = ctx->r25;
    // 0x802C711C: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
    // 0x802C7120: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x802C7124: b           L_802C713C
    // 0x802C7128: sh          $v0, -0x5498($at)
    MEM_H(-0X5498, ctx->r1) = ctx->r2;
        goto L_802C713C;
    // 0x802C7128: sh          $v0, -0x5498($at)
    MEM_H(-0X5498, ctx->r1) = ctx->r2;
L_802C712C:
    // 0x802C712C: sw          $v0, -0x4CC8($at)
    MEM_W(-0X4CC8, ctx->r1) = ctx->r2;
    // 0x802C7130: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x802C7134: sh          $zero, -0x5498($at)
    MEM_H(-0X5498, ctx->r1) = 0;
    // 0x802C7138: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
L_802C713C:
    // 0x802C713C: lh          $t0, -0x19F4($t0)
    ctx->r8 = MEM_H(ctx->r8, -0X19F4);
    // 0x802C7140: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C7144: addiu       $a0, $zero, 0x11
    ctx->r4 = ADD32(0, 0X11);
    // 0x802C7148: bne         $v0, $t0, L_802C716C
    if (ctx->r2 != ctx->r8) {
        // 0x802C714C: or          $a1, $zero, $zero
        ctx->r5 = 0 | 0;
            goto L_802C716C;
    }
    // 0x802C714C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x802C7150: jal         0x802C7474
    // 0x802C7154: addiu       $a0, $zero, 0x28
    ctx->r4 = ADD32(0, 0X28);
    func_i4_802C7474(rdram, ctx);
        goto after_0;
    // 0x802C7154: addiu       $a0, $zero, 0x28
    ctx->r4 = ADD32(0, 0X28);
    after_0:
    // 0x802C7158: addiu       $a0, $zero, 0x37
    ctx->r4 = ADD32(0, 0X37);
    // 0x802C715C: jal         0x800C37F4
    // 0x802C7160: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_1;
    // 0x802C7160: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_1:
    // 0x802C7164: b           L_802C7338
    // 0x802C7168: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_802C7338;
    // 0x802C7168: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C716C:
    // 0x802C716C: sw          $v0, 0x7554($at)
    MEM_W(0X7554, ctx->r1) = ctx->r2;
    // 0x802C7170: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C7174: sw          $a2, 0x7538($at)
    MEM_W(0X7538, ctx->r1) = ctx->r6;
    // 0x802C7178: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C717C: jal         0x800C37F4
    // 0x802C7180: sw          $zero, 0x753C($at)
    MEM_W(0X753C, ctx->r1) = 0;
    func_800C37F4(rdram, ctx);
        goto after_2;
    // 0x802C7180: sw          $zero, 0x753C($at)
    MEM_W(0X753C, ctx->r1) = 0;
    after_2:
    // 0x802C7184: b           L_802C7338
    // 0x802C7188: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_802C7338;
    // 0x802C7188: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C718C:
    // 0x802C718C: beq         $t1, $zero, L_802C71D0
    if (ctx->r9 == 0) {
        // 0x802C7190: andi        $t3, $v0, 0x800
        ctx->r11 = ctx->r2 & 0X800;
            goto L_802C71D0;
    }
    // 0x802C7190: andi        $t3, $v0, 0x800
    ctx->r11 = ctx->r2 & 0X800;
    // 0x802C7194: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
    // 0x802C7198: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C719C: sw          $v0, 0x7538($at)
    MEM_W(0X7538, ctx->r1) = ctx->r2;
    // 0x802C71A0: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C71A4: sw          $zero, 0x753C($at)
    MEM_W(0X753C, ctx->r1) = 0;
    // 0x802C71A8: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C71AC: addiu       $t2, $zero, 0x2
    ctx->r10 = ADD32(0, 0X2);
    // 0x802C71B0: sw          $t2, 0x7544($at)
    MEM_W(0X7544, ctx->r1) = ctx->r10;
    // 0x802C71B4: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C71B8: sw          $zero, 0x7548($at)
    MEM_W(0X7548, ctx->r1) = 0;
    // 0x802C71BC: addiu       $a0, $zero, 0x16
    ctx->r4 = ADD32(0, 0X16);
    // 0x802C71C0: jal         0x800C37F4
    // 0x802C71C4: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_3;
    // 0x802C71C4: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_3:
    // 0x802C71C8: b           L_802C7338
    // 0x802C71CC: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_802C7338;
    // 0x802C71CC: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C71D0:
    // 0x802C71D0: beq         $t3, $zero, L_802C728C
    if (ctx->r11 == 0) {
        // 0x802C71D4: andi        $t9, $v0, 0x400
        ctx->r25 = ctx->r2 & 0X400;
            goto L_802C728C;
    }
    // 0x802C71D4: andi        $t9, $v0, 0x400
    ctx->r25 = ctx->r2 & 0X400;
    // 0x802C71D8: lui         $v1, 0x802C
    ctx->r3 = S32(0X802C << 16);
    // 0x802C71DC: addiu       $v1, $v1, 0x754C
    ctx->r3 = ADD32(ctx->r3, 0X754C);
    // 0x802C71E0: lui         $a2, 0x802C
    ctx->r6 = S32(0X802C << 16);
    // 0x802C71E4: lw          $t4, 0x0($v1)
    ctx->r12 = MEM_W(ctx->r3, 0X0);
    // 0x802C71E8: addiu       $a2, $a2, 0x76CC
    ctx->r6 = ADD32(ctx->r6, 0X76CC);
    // 0x802C71EC: lw          $a1, 0x0($a2)
    ctx->r5 = MEM_W(ctx->r6, 0X0);
    // 0x802C71F0: addiu       $v0, $t4, -0x1
    ctx->r2 = ADD32(ctx->r12, -0X1);
    // 0x802C71F4: sw          $v0, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r2;
    // 0x802C71F8: slt         $at, $v0, $a1
    ctx->r1 = SIGNED(ctx->r2) < SIGNED(ctx->r5) ? 1 : 0;
    // 0x802C71FC: beq         $at, $zero, L_802C7218
    if (ctx->r1 == 0) {
        // 0x802C7200: lui         $t8, 0x800E
        ctx->r24 = S32(0X800E << 16);
            goto L_802C7218;
    }
    // 0x802C7200: lui         $t8, 0x800E
    ctx->r24 = S32(0X800E << 16);
    // 0x802C7204: lui         $a2, 0x802C
    ctx->r6 = S32(0X802C << 16);
    // 0x802C7208: addiu       $a2, $a2, 0x76D0
    ctx->r6 = ADD32(ctx->r6, 0X76D0);
    // 0x802C720C: lw          $t6, 0x0($a2)
    ctx->r14 = MEM_W(ctx->r6, 0X0);
    // 0x802C7210: addiu       $v0, $t6, -0x1
    ctx->r2 = ADD32(ctx->r14, -0X1);
    // 0x802C7214: sw          $v0, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r2;
L_802C7218:
    // 0x802C7218: lw          $t8, -0x5630($t8)
    ctx->r24 = MEM_W(ctx->r24, -0X5630);
    // 0x802C721C: lui         $t0, 0x800E
    ctx->r8 = S32(0X800E << 16);
    // 0x802C7220: lui         $t2, 0x802C
    ctx->r10 = S32(0X802C << 16);
    // 0x802C7224: sll         $t9, $t8, 2
    ctx->r25 = S32(ctx->r24 << 2);
    // 0x802C7228: addu        $t0, $t0, $t9
    ctx->r8 = ADD32(ctx->r8, ctx->r25);
    // 0x802C722C: lw          $t0, -0x5528($t0)
    ctx->r8 = MEM_W(ctx->r8, -0X5528);
    // 0x802C7230: lui         $a2, 0x802C
    ctx->r6 = S32(0X802C << 16);
    // 0x802C7234: addiu       $t2, $t2, 0x757C
    ctx->r10 = ADD32(ctx->r10, 0X757C);
    // 0x802C7238: sll         $t1, $t0, 4
    ctx->r9 = S32(ctx->r8 << 4);
    // 0x802C723C: addiu       $a2, $a2, 0x76D0
    ctx->r6 = ADD32(ctx->r6, 0X76D0);
    // 0x802C7240: addu        $a0, $t1, $t2
    ctx->r4 = ADD32(ctx->r9, ctx->r10);
L_802C7244:
    // 0x802C7244: sll         $t3, $v0, 2
    ctx->r11 = S32(ctx->r2 << 2);
    // 0x802C7248: addu        $t4, $a0, $t3
    ctx->r12 = ADD32(ctx->r4, ctx->r11);
    // 0x802C724C: lw          $t5, 0x0($t4)
    ctx->r13 = MEM_W(ctx->r12, 0X0);
    // 0x802C7250: addiu       $t6, $v0, -0x1
    ctx->r14 = ADD32(ctx->r2, -0X1);
    // 0x802C7254: or          $v0, $t6, $zero
    ctx->r2 = ctx->r14 | 0;
    // 0x802C7258: bne         $t5, $zero, L_802C7278
    if (ctx->r13 != 0) {
        // 0x802C725C: slt         $at, $t6, $a1
        ctx->r1 = SIGNED(ctx->r14) < SIGNED(ctx->r5) ? 1 : 0;
            goto L_802C7278;
    }
    // 0x802C725C: slt         $at, $t6, $a1
    ctx->r1 = SIGNED(ctx->r14) < SIGNED(ctx->r5) ? 1 : 0;
    // 0x802C7260: beq         $at, $zero, L_802C7244
    if (ctx->r1 == 0) {
        // 0x802C7264: sw          $t6, 0x0($v1)
        MEM_W(0X0, ctx->r3) = ctx->r14;
            goto L_802C7244;
    }
    // 0x802C7264: sw          $t6, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r14;
    // 0x802C7268: lw          $t7, 0x0($a2)
    ctx->r15 = MEM_W(ctx->r6, 0X0);
    // 0x802C726C: addiu       $v0, $t7, -0x1
    ctx->r2 = ADD32(ctx->r15, -0X1);
    // 0x802C7270: b           L_802C7244
    // 0x802C7274: sw          $v0, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r2;
        goto L_802C7244;
    // 0x802C7274: sw          $v0, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r2;
L_802C7278:
    // 0x802C7278: addiu       $a0, $zero, 0x10
    ctx->r4 = ADD32(0, 0X10);
    // 0x802C727C: jal         0x800C37F4
    // 0x802C7280: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_4;
    // 0x802C7280: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_4:
    // 0x802C7284: b           L_802C7338
    // 0x802C7288: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_802C7338;
    // 0x802C7288: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C728C:
    // 0x802C728C: beq         $t9, $zero, L_802C7334
    if (ctx->r25 == 0) {
        // 0x802C7290: lui         $v1, 0x802C
        ctx->r3 = S32(0X802C << 16);
            goto L_802C7334;
    }
    // 0x802C7290: lui         $v1, 0x802C
    ctx->r3 = S32(0X802C << 16);
    // 0x802C7294: addiu       $v1, $v1, 0x754C
    ctx->r3 = ADD32(ctx->r3, 0X754C);
    // 0x802C7298: lui         $a2, 0x802C
    ctx->r6 = S32(0X802C << 16);
    // 0x802C729C: lw          $t0, 0x0($v1)
    ctx->r8 = MEM_W(ctx->r3, 0X0);
    // 0x802C72A0: addiu       $a2, $a2, 0x76D0
    ctx->r6 = ADD32(ctx->r6, 0X76D0);
    // 0x802C72A4: lw          $a1, 0x0($a2)
    ctx->r5 = MEM_W(ctx->r6, 0X0);
    // 0x802C72A8: addiu       $v0, $t0, 0x1
    ctx->r2 = ADD32(ctx->r8, 0X1);
    // 0x802C72AC: sw          $v0, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r2;
    // 0x802C72B0: slt         $at, $v0, $a1
    ctx->r1 = SIGNED(ctx->r2) < SIGNED(ctx->r5) ? 1 : 0;
    // 0x802C72B4: bne         $at, $zero, L_802C72CC
    if (ctx->r1 != 0) {
        // 0x802C72B8: lui         $t3, 0x800E
        ctx->r11 = S32(0X800E << 16);
            goto L_802C72CC;
    }
    // 0x802C72B8: lui         $t3, 0x800E
    ctx->r11 = S32(0X800E << 16);
    // 0x802C72BC: lui         $a2, 0x802C
    ctx->r6 = S32(0X802C << 16);
    // 0x802C72C0: addiu       $a2, $a2, 0x76CC
    ctx->r6 = ADD32(ctx->r6, 0X76CC);
    // 0x802C72C4: lw          $v0, 0x0($a2)
    ctx->r2 = MEM_W(ctx->r6, 0X0);
    // 0x802C72C8: sw          $v0, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r2;
L_802C72CC:
    // 0x802C72CC: lw          $t3, -0x5630($t3)
    ctx->r11 = MEM_W(ctx->r11, -0X5630);
    // 0x802C72D0: lui         $t5, 0x800E
    ctx->r13 = S32(0X800E << 16);
    // 0x802C72D4: lui         $t7, 0x802C
    ctx->r15 = S32(0X802C << 16);
    // 0x802C72D8: sll         $t4, $t3, 2
    ctx->r12 = S32(ctx->r11 << 2);
    // 0x802C72DC: addu        $t5, $t5, $t4
    ctx->r13 = ADD32(ctx->r13, ctx->r12);
    // 0x802C72E0: lw          $t5, -0x5528($t5)
    ctx->r13 = MEM_W(ctx->r13, -0X5528);
    // 0x802C72E4: lui         $a2, 0x802C
    ctx->r6 = S32(0X802C << 16);
    // 0x802C72E8: addiu       $t7, $t7, 0x757C
    ctx->r15 = ADD32(ctx->r15, 0X757C);
    // 0x802C72EC: sll         $t6, $t5, 4
    ctx->r14 = S32(ctx->r13 << 4);
    // 0x802C72F0: addiu       $a2, $a2, 0x76CC
    ctx->r6 = ADD32(ctx->r6, 0X76CC);
    // 0x802C72F4: addu        $a0, $t6, $t7
    ctx->r4 = ADD32(ctx->r14, ctx->r15);
L_802C72F8:
    // 0x802C72F8: sll         $t8, $v0, 2
    ctx->r24 = S32(ctx->r2 << 2);
    // 0x802C72FC: addu        $t9, $a0, $t8
    ctx->r25 = ADD32(ctx->r4, ctx->r24);
    // 0x802C7300: lw          $t0, 0x0($t9)
    ctx->r8 = MEM_W(ctx->r25, 0X0);
    // 0x802C7304: addiu       $t1, $v0, 0x1
    ctx->r9 = ADD32(ctx->r2, 0X1);
    // 0x802C7308: or          $v0, $t1, $zero
    ctx->r2 = ctx->r9 | 0;
    // 0x802C730C: bne         $t0, $zero, L_802C7328
    if (ctx->r8 != 0) {
        // 0x802C7310: slt         $at, $t1, $a1
        ctx->r1 = SIGNED(ctx->r9) < SIGNED(ctx->r5) ? 1 : 0;
            goto L_802C7328;
    }
    // 0x802C7310: slt         $at, $t1, $a1
    ctx->r1 = SIGNED(ctx->r9) < SIGNED(ctx->r5) ? 1 : 0;
    // 0x802C7314: bne         $at, $zero, L_802C72F8
    if (ctx->r1 != 0) {
        // 0x802C7318: sw          $t1, 0x0($v1)
        MEM_W(0X0, ctx->r3) = ctx->r9;
            goto L_802C72F8;
    }
    // 0x802C7318: sw          $t1, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r9;
    // 0x802C731C: lw          $v0, 0x0($a2)
    ctx->r2 = MEM_W(ctx->r6, 0X0);
    // 0x802C7320: b           L_802C72F8
    // 0x802C7324: sw          $v0, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r2;
        goto L_802C72F8;
    // 0x802C7324: sw          $v0, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r2;
L_802C7328:
    // 0x802C7328: addiu       $a0, $zero, 0x10
    ctx->r4 = ADD32(0, 0X10);
    // 0x802C732C: jal         0x800C37F4
    // 0x802C7330: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_5;
    // 0x802C7330: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_5:
L_802C7334:
    // 0x802C7334: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C7338:
    // 0x802C7338: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x802C733C: jr          $ra
    // 0x802C7340: nop

    return;
    // 0x802C7340: nop

;}
RECOMP_FUNC void func_i4_802C7344(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C7344: lui         $t6, 0x802C
    ctx->r14 = S32(0X802C << 16);
    // 0x802C7348: lw          $t6, 0x76B0($t6)
    ctx->r14 = MEM_W(ctx->r14, 0X76B0);
    // 0x802C734C: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x802C7350: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x802C7354: sll         $t7, $t6, 3
    ctx->r15 = S32(ctx->r14 << 3);
    // 0x802C7358: subu        $t7, $t7, $t6
    ctx->r15 = SUB32(ctx->r15, ctx->r14);
    // 0x802C735C: sll         $t7, $t7, 2
    ctx->r15 = S32(ctx->r15 << 2);
    // 0x802C7360: addu        $v0, $v0, $t7
    ctx->r2 = ADD32(ctx->r2, ctx->r15);
    // 0x802C7364: lhu         $v0, -0x19A6($v0)
    ctx->r2 = MEM_HU(ctx->r2, -0X19A6);
    // 0x802C7368: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x802C736C: andi        $t8, $v0, 0xB000
    ctx->r24 = ctx->r2 & 0XB000;
    // 0x802C7370: beq         $t8, $zero, L_802C73C0
    if (ctx->r24 == 0) {
        // 0x802C7374: andi        $t1, $v0, 0x4000
        ctx->r9 = ctx->r2 & 0X4000;
            goto L_802C73C0;
    }
    // 0x802C7374: andi        $t1, $v0, 0x4000
    ctx->r9 = ctx->r2 & 0X4000;
    // 0x802C7378: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x802C737C: addiu       $v0, $v0, -0x55FC
    ctx->r2 = ADD32(ctx->r2, -0X55FC);
    // 0x802C7380: lw          $t9, 0x0($v0)
    ctx->r25 = MEM_W(ctx->r2, 0X0);
    // 0x802C7384: addiu       $t0, $zero, 0x1
    ctx->r8 = ADD32(0, 0X1);
    // 0x802C7388: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C738C: bne         $t9, $zero, L_802C73A0
    if (ctx->r25 != 0) {
        // 0x802C7390: nop
    
            goto L_802C73A0;
    }
    // 0x802C7390: nop

    // 0x802C7394: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C7398: b           L_802C73A4
    // 0x802C739C: sw          $t0, -0x19E4($at)
    MEM_W(-0X19E4, ctx->r1) = ctx->r8;
        goto L_802C73A4;
    // 0x802C739C: sw          $t0, -0x19E4($at)
    MEM_W(-0X19E4, ctx->r1) = ctx->r8;
L_802C73A0:
    // 0x802C73A0: sw          $zero, -0x19E4($at)
    MEM_W(-0X19E4, ctx->r1) = 0;
L_802C73A4:
    // 0x802C73A4: jal         0x802C7474
    // 0x802C73A8: addiu       $a0, $zero, 0x28
    ctx->r4 = ADD32(0, 0X28);
    func_i4_802C7474(rdram, ctx);
        goto after_0;
    // 0x802C73A8: addiu       $a0, $zero, 0x28
    ctx->r4 = ADD32(0, 0X28);
    after_0:
    // 0x802C73AC: addiu       $a0, $zero, 0x37
    ctx->r4 = ADD32(0, 0X37);
    // 0x802C73B0: jal         0x800C37F4
    // 0x802C73B4: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_1;
    // 0x802C73B4: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_1:
    // 0x802C73B8: b           L_802C7468
    // 0x802C73BC: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_802C7468;
    // 0x802C73BC: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C73C0:
    // 0x802C73C0: beq         $t1, $zero, L_802C73F8
    if (ctx->r9 == 0) {
        // 0x802C73C4: andi        $t3, $v0, 0x200
        ctx->r11 = ctx->r2 & 0X200;
            goto L_802C73F8;
    }
    // 0x802C73C4: andi        $t3, $v0, 0x200
    ctx->r11 = ctx->r2 & 0X200;
    // 0x802C73C8: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C73CC: sw          $zero, 0x7554($at)
    MEM_W(0X7554, ctx->r1) = 0;
    // 0x802C73D0: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C73D4: addiu       $t2, $zero, 0x2
    ctx->r10 = ADD32(0, 0X2);
    // 0x802C73D8: sw          $t2, 0x7538($at)
    MEM_W(0X7538, ctx->r1) = ctx->r10;
    // 0x802C73DC: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C73E0: sw          $zero, 0x753C($at)
    MEM_W(0X753C, ctx->r1) = 0;
    // 0x802C73E4: addiu       $a0, $zero, 0x16
    ctx->r4 = ADD32(0, 0X16);
    // 0x802C73E8: jal         0x800C37F4
    // 0x802C73EC: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_2;
    // 0x802C73EC: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_2:
    // 0x802C73F0: b           L_802C7468
    // 0x802C73F4: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_802C7468;
    // 0x802C73F4: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C73F8:
    // 0x802C73F8: beq         $t3, $zero, L_802C7434
    if (ctx->r11 == 0) {
        // 0x802C73FC: andi        $t8, $v0, 0x100
        ctx->r24 = ctx->r2 & 0X100;
            goto L_802C7434;
    }
    // 0x802C73FC: andi        $t8, $v0, 0x100
    ctx->r24 = ctx->r2 & 0X100;
    // 0x802C7400: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x802C7404: addiu       $v0, $v0, -0x55FC
    ctx->r2 = ADD32(ctx->r2, -0X55FC);
    // 0x802C7408: lw          $t4, 0x0($v0)
    ctx->r12 = MEM_W(ctx->r2, 0X0);
    // 0x802C740C: addiu       $t7, $zero, 0x1
    ctx->r15 = ADD32(0, 0X1);
    // 0x802C7410: addiu       $a0, $zero, 0x10
    ctx->r4 = ADD32(0, 0X10);
    // 0x802C7414: addiu       $t5, $t4, -0x1
    ctx->r13 = ADD32(ctx->r12, -0X1);
    // 0x802C7418: bgez        $t5, L_802C7424
    if (SIGNED(ctx->r13) >= 0) {
        // 0x802C741C: sw          $t5, 0x0($v0)
        MEM_W(0X0, ctx->r2) = ctx->r13;
            goto L_802C7424;
    }
    // 0x802C741C: sw          $t5, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r13;
    // 0x802C7420: sw          $t7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r15;
L_802C7424:
    // 0x802C7424: jal         0x800C37F4
    // 0x802C7428: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_3;
    // 0x802C7428: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_3:
    // 0x802C742C: b           L_802C7468
    // 0x802C7430: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_802C7468;
    // 0x802C7430: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C7434:
    // 0x802C7434: beq         $t8, $zero, L_802C7464
    if (ctx->r24 == 0) {
        // 0x802C7438: lui         $v0, 0x800E
        ctx->r2 = S32(0X800E << 16);
            goto L_802C7464;
    }
    // 0x802C7438: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x802C743C: addiu       $v0, $v0, -0x55FC
    ctx->r2 = ADD32(ctx->r2, -0X55FC);
    // 0x802C7440: lw          $t9, 0x0($v0)
    ctx->r25 = MEM_W(ctx->r2, 0X0);
    // 0x802C7444: addiu       $a0, $zero, 0x10
    ctx->r4 = ADD32(0, 0X10);
    // 0x802C7448: addiu       $t0, $t9, 0x1
    ctx->r8 = ADD32(ctx->r25, 0X1);
    // 0x802C744C: slti        $at, $t0, 0x2
    ctx->r1 = SIGNED(ctx->r8) < 0X2 ? 1 : 0;
    // 0x802C7450: bne         $at, $zero, L_802C745C
    if (ctx->r1 != 0) {
        // 0x802C7454: sw          $t0, 0x0($v0)
        MEM_W(0X0, ctx->r2) = ctx->r8;
            goto L_802C745C;
    }
    // 0x802C7454: sw          $t0, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r8;
    // 0x802C7458: sw          $zero, 0x0($v0)
    MEM_W(0X0, ctx->r2) = 0;
L_802C745C:
    // 0x802C745C: jal         0x800C37F4
    // 0x802C7460: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_4;
    // 0x802C7460: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_4:
L_802C7464:
    // 0x802C7464: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C7468:
    // 0x802C7468: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x802C746C: jr          $ra
    // 0x802C7470: nop

    return;
    // 0x802C7470: nop

;}
RECOMP_FUNC void func_i4_802C7474(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C7474: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x802C7478: addiu       $v0, $v0, -0x54DC
    ctx->r2 = ADD32(ctx->r2, -0X54DC);
    // 0x802C747C: lw          $t6, 0x0($v0)
    ctx->r14 = MEM_W(ctx->r2, 0X0);
    // 0x802C7480: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C7484: addiu       $t7, $zero, 0x15
    ctx->r15 = ADD32(0, 0X15);
    // 0x802C7488: sw          $t6, -0x19CC($at)
    MEM_W(-0X19CC, ctx->r1) = ctx->r14;
    // 0x802C748C: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C7490: sw          $a0, -0x19D0($at)
    MEM_W(-0X19D0, ctx->r1) = ctx->r4;
    // 0x802C7494: sw          $t7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r15;
    // 0x802C7498: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C749C: addiu       $t8, $zero, 0x5
    ctx->r24 = ADD32(0, 0X5);
    // 0x802C74A0: sw          $t8, -0x19C8($at)
    MEM_W(-0X19C8, ctx->r1) = ctx->r24;
    // 0x802C74A4: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C74A8: addiu       $t9, $zero, 0x1
    ctx->r25 = ADD32(0, 0X1);
    // 0x802C74AC: sw          $t9, -0x19C4($at)
    MEM_W(-0X19C4, ctx->r1) = ctx->r25;
    // 0x802C74B0: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C74B4: sw          $zero, -0x19C0($at)
    MEM_W(-0X19C0, ctx->r1) = 0;
    // 0x802C74B8: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x802C74BC: sw          $zero, -0x19BC($at)
    MEM_W(-0X19BC, ctx->r1) = 0;
    // 0x802C74C0: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x802C74C4: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x802C74C8: sw          $zero, -0x54E4($at)
    MEM_W(-0X54E4, ctx->r1) = 0;
    // 0x802C74CC: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x802C74D0: lui         $at, 0x800D
    ctx->r1 = S32(0X800D << 16);
    // 0x802C74D4: addiu       $t0, $zero, 0x2
    ctx->r8 = ADD32(0, 0X2);
    // 0x802C74D8: sw          $t0, 0x461C($at)
    MEM_W(0X461C, ctx->r1) = ctx->r8;
    // 0x802C74DC: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    // 0x802C74E0: addiu       $a1, $zero, 0x4
    ctx->r5 = ADD32(0, 0X4);
    // 0x802C74E4: jal         0x801E6FB0
    // 0x802C74E8: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    FadeTransition_SetProps(rdram, ctx);
        goto after_0;
    // 0x802C74E8: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    after_0:
    // 0x802C74EC: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    // 0x802C74F0: jal         0x801E6A4C
    // 0x802C74F4: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_801E6A4C(rdram, ctx);
        goto after_1;
    // 0x802C74F4: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_1:
    // 0x802C74F8: lui         $t1, 0x801D
    ctx->r9 = S32(0X801D << 16);
    // 0x802C74FC: lw          $t1, -0x19D0($t1)
    ctx->r9 = MEM_W(ctx->r9, -0X19D0);
    // 0x802C7500: addiu       $at, $zero, 0x28
    ctx->r1 = ADD32(0, 0X28);
    // 0x802C7504: bnel        $t1, $at, L_802C7518
    if (ctx->r9 != ctx->r1) {
        // 0x802C7508: lw          $ra, 0x14($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X14);
            goto L_802C7518;
    }
    goto skip_0;
    // 0x802C7508: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    skip_0:
    // 0x802C750C: jal         0x800C1F60
    // 0x802C7510: addiu       $a0, $zero, 0x7
    ctx->r4 = ADD32(0, 0X7);
    func_800C1F60(rdram, ctx);
        goto after_2;
    // 0x802C7510: addiu       $a0, $zero, 0x7
    ctx->r4 = ADD32(0, 0X7);
    after_2:
    // 0x802C7514: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C7518:
    // 0x802C7518: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x802C751C: jr          $ra
    // 0x802C7520: nop

    return;
    // 0x802C7520: nop

    // 0x802C7524: nop

    // 0x802C7528: nop

    // 0x802C752C: nop

;}
RECOMP_FUNC void func_i5_802C5800(uint8_t* rdram, recomp_context* ctx) {
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
    // 0x802C5810: beq         $t6, $zero, L_802C5838
    if (ctx->r14 == 0) {
        // 0x802C5814: lui         $t7, 0x800E
        ctx->r15 = S32(0X800E << 16);
            goto L_802C5838;
    }
    // 0x802C5814: lui         $t7, 0x800E
    ctx->r15 = S32(0X800E << 16);
    // 0x802C5818: lw          $t7, -0x54DC($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X54DC);
    // 0x802C581C: addiu       $at, $zero, 0x34
    ctx->r1 = ADD32(0, 0X34);
    // 0x802C5820: bne         $t7, $at, L_802C5838
    if (ctx->r15 != ctx->r1) {
        // 0x802C5824: nop
    
            goto L_802C5838;
    }
    // 0x802C5824: nop

    // 0x802C5828: jal         0x80094ACC
    // 0x802C582C: nop

    func_80094ACC(rdram, ctx);
        goto after_0;
    // 0x802C582C: nop

    after_0:
    // 0x802C5830: jal         0x802C5A98
    // 0x802C5834: nop

    func_i5_802C5A98(rdram, ctx);
        goto after_1;
    // 0x802C5834: nop

    after_1:
L_802C5838:
    // 0x802C5838: jal         0x802C5850
    // 0x802C583C: nop

    func_i5_802C5850(rdram, ctx);
        goto after_2;
    // 0x802C583C: nop

    after_2:
    // 0x802C5840: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x802C5844: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x802C5848: jr          $ra
    // 0x802C584C: nop

    return;
    // 0x802C584C: nop

;}
RECOMP_FUNC void func_i5_802C5850(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C5850: addiu       $sp, $sp, -0x1C0
    ctx->r29 = ADD32(ctx->r29, -0X1C0);
    // 0x802C5854: sw          $s2, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r18;
    // 0x802C5858: lui         $t6, 0x802C
    ctx->r14 = S32(0X802C << 16);
    // 0x802C585C: lui         $at, 0x4180
    ctx->r1 = S32(0X4180 << 16);
    // 0x802C5860: lh          $t6, 0x7A00($t6)
    ctx->r14 = MEM_H(ctx->r14, 0X7A00);
    // 0x802C5864: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x802C5868: lui         $s2, 0x801D
    ctx->r18 = S32(0X801D << 16);
    // 0x802C586C: mtc1        $zero, $f0
    ctx->f0.u32l = 0;
    // 0x802C5870: addiu       $s2, $s2, -0x1A08
    ctx->r18 = ADD32(ctx->r18, -0X1A08);
    // 0x802C5874: sw          $fp, 0x58($sp)
    MEM_W(0X58, ctx->r29) = ctx->r30;
    // 0x802C5878: lui         $at, 0x4580
    ctx->r1 = S32(0X4580 << 16);
    // 0x802C587C: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x802C5880: lw          $a0, 0x0($s2)
    ctx->r4 = MEM_W(ctx->r18, 0X0);
    // 0x802C5884: lui         $fp, 0x802C
    ctx->r30 = S32(0X802C << 16);
    // 0x802C5888: addiu       $t7, $zero, 0x28
    ctx->r15 = ADD32(0, 0X28);
    // 0x802C588C: addiu       $fp, $fp, 0x7B04
    ctx->r30 = ADD32(ctx->r30, 0X7B04);
    // 0x802C5890: sw          $ra, 0x5C($sp)
    MEM_W(0X5C, ctx->r29) = ctx->r31;
    // 0x802C5894: lui         $a1, 0x802C
    ctx->r5 = S32(0X802C << 16);
    // 0x802C5898: subu        $t8, $t7, $t6
    ctx->r24 = SUB32(ctx->r15, ctx->r14);
    // 0x802C589C: sw          $s7, 0x54($sp)
    MEM_W(0X54, ctx->r29) = ctx->r23;
    // 0x802C58A0: sw          $s6, 0x50($sp)
    MEM_W(0X50, ctx->r29) = ctx->r22;
    // 0x802C58A4: sw          $s5, 0x4C($sp)
    MEM_W(0X4C, ctx->r29) = ctx->r21;
    // 0x802C58A8: sw          $s4, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r20;
    // 0x802C58AC: sw          $s3, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r19;
    // 0x802C58B0: sw          $s1, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r17;
    // 0x802C58B4: sw          $s0, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r16;
    // 0x802C58B8: sh          $t8, 0x0($fp)
    MEM_H(0X0, ctx->r30) = ctx->r24;
    // 0x802C58BC: addiu       $a1, $a1, 0x7B06
    ctx->r5 = ADD32(ctx->r5, 0X7B06);
    // 0x802C58C0: lui         $a2, 0x4204
    ctx->r6 = S32(0X4204 << 16);
    // 0x802C58C4: lui         $a3, 0x3F80
    ctx->r7 = S32(0X3F80 << 16);
    // 0x802C58C8: swc1        $f4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f4.u32l;
    // 0x802C58CC: swc1        $f0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->f0.u32l;
    // 0x802C58D0: swc1        $f0, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->f0.u32l;
    // 0x802C58D4: addiu       $a0, $a0, 0xA40
    ctx->r4 = ADD32(ctx->r4, 0XA40);
    // 0x802C58D8: jal         0x800481E0
    // 0x802C58DC: swc1        $f6, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->f6.u32l;
    func_800481E0(rdram, ctx);
        goto after_0;
    // 0x802C58DC: swc1        $f6, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->f6.u32l;
    after_0:
    // 0x802C58E0: mtc1        $zero, $f0
    ctx->f0.u32l = 0;
    // 0x802C58E4: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x802C58E8: mtc1        $at, $f2
    ctx->f2.u32l = ctx->r1;
    // 0x802C58EC: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C58F0: lwc1        $f8, 0x7A5C($at)
    ctx->f8.u32l = MEM_W(ctx->r1, 0X7A5C);
    // 0x802C58F4: addiu       $s0, $sp, 0xB0
    ctx->r16 = ADD32(ctx->r29, 0XB0);
    // 0x802C58F8: mfc1        $a1, $f0
    ctx->r5 = (int32_t)ctx->f0.u32l;
    // 0x802C58FC: mfc1        $a2, $f0
    ctx->r6 = (int32_t)ctx->f0.u32l;
    // 0x802C5900: mfc1        $a3, $f2
    ctx->r7 = (int32_t)ctx->f2.u32l;
    // 0x802C5904: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x802C5908: swc1        $f0, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f0.u32l;
    // 0x802C590C: swc1        $f0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->f0.u32l;
    // 0x802C5910: swc1        $f0, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->f0.u32l;
    // 0x802C5914: swc1        $f0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->f0.u32l;
    // 0x802C5918: swc1        $f0, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->f0.u32l;
    // 0x802C591C: swc1        $f2, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->f2.u32l;
    // 0x802C5920: jal         0x80048A88
    // 0x802C5924: swc1        $f8, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->f8.u32l;
    func_80048A88(rdram, ctx);
        goto after_1;
    // 0x802C5924: swc1        $f8, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->f8.u32l;
    after_1:
    // 0x802C5928: lui         $v0, 0x8015
    ctx->r2 = S32(0X8015 << 16);
    // 0x802C592C: addiu       $v0, $v0, 0x4350
    ctx->r2 = ADD32(ctx->r2, 0X4350);
    // 0x802C5930: lui         $at, 0x43FA
    ctx->r1 = S32(0X43FA << 16);
    // 0x802C5934: mtc1        $at, $f14
    ctx->f14.u32l = ctx->r1;
    // 0x802C5938: lwc1        $f10, 0x1000($v0)
    ctx->f10.u32l = MEM_W(ctx->r2, 0X1000);
    // 0x802C593C: lwc1        $f16, 0x0($v0)
    ctx->f16.u32l = MEM_W(ctx->r2, 0X0);
    // 0x802C5940: mtc1        $zero, $f0
    ctx->f0.u32l = 0;
    // 0x802C5944: mul.s       $f2, $f10, $f14
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f2.fl = MUL_S(ctx->f10.fl, ctx->f14.fl);
    // 0x802C5948: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x802C594C: mtc1        $at, $f18
    ctx->f18.u32l = ctx->r1;
    // 0x802C5950: mul.s       $f12, $f16, $f14
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f12.fl = MUL_S(ctx->f16.fl, ctx->f14.fl);
    // 0x802C5954: addiu       $s1, $sp, 0x134
    ctx->r17 = ADD32(ctx->r29, 0X134);
    // 0x802C5958: or          $a1, $s1, $zero
    ctx->r5 = ctx->r17 | 0;
    // 0x802C595C: addiu       $a0, $sp, 0x70
    ctx->r4 = ADD32(ctx->r29, 0X70);
    // 0x802C5960: mfc1        $a2, $f2
    ctx->r6 = (int32_t)ctx->f2.u32l;
    // 0x802C5964: addiu       $a3, $zero, 0x0
    ctx->r7 = ADD32(0, 0X0);
    // 0x802C5968: swc1        $f0, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->f0.u32l;
    // 0x802C596C: swc1        $f12, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f12.u32l;
    // 0x802C5970: swc1        $f0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->f0.u32l;
    // 0x802C5974: swc1        $f0, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->f0.u32l;
    // 0x802C5978: swc1        $f0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->f0.u32l;
    // 0x802C597C: swc1        $f0, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->f0.u32l;
    // 0x802C5980: jal         0x800484C8
    // 0x802C5984: swc1        $f18, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->f18.u32l;
    func_800484C8(rdram, ctx);
        goto after_2;
    // 0x802C5984: swc1        $f18, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->f18.u32l;
    after_2:
    // 0x802C5988: addiu       $s3, $sp, 0x174
    ctx->r19 = ADD32(ctx->r29, 0X174);
    // 0x802C598C: or          $a1, $s3, $zero
    ctx->r5 = ctx->r19 | 0;
    // 0x802C5990: jal         0x80047E78
    // 0x802C5994: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    SysUtils_MtxToMtxF(rdram, ctx);
        goto after_3;
    // 0x802C5994: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_3:
    // 0x802C5998: addiu       $s7, $sp, 0xF4
    ctx->r23 = ADD32(ctx->r29, 0XF4);
    // 0x802C599C: or          $a2, $s7, $zero
    ctx->r6 = ctx->r23 | 0;
    // 0x802C59A0: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    // 0x802C59A4: jal         0x80049EB8
    // 0x802C59A8: or          $a1, $s3, $zero
    ctx->r5 = ctx->r19 | 0;
    SysUtils_MatrixAffineMultiply(rdram, ctx);
        goto after_4;
    // 0x802C59A8: or          $a1, $s3, $zero
    ctx->r5 = ctx->r19 | 0;
    after_4:
    // 0x802C59AC: lui         $s5, 0x802C
    ctx->r21 = S32(0X802C << 16);
    // 0x802C59B0: addiu       $s5, $s5, 0x7A08
    ctx->r21 = ADD32(ctx->r21, 0X7A08);
    // 0x802C59B4: or          $s1, $zero, $zero
    ctx->r17 = 0 | 0;
    // 0x802C59B8: or          $s3, $zero, $zero
    ctx->r19 = 0 | 0;
    // 0x802C59BC: or          $s0, $zero, $zero
    ctx->r16 = 0 | 0;
    // 0x802C59C0: addiu       $s4, $zero, 0x58
    ctx->r20 = ADD32(0, 0X58);
    // 0x802C59C4: addiu       $s6, $zero, 0x4
    ctx->r22 = ADD32(0, 0X4);
L_802C59C8:
    // 0x802C59C8: lw          $t9, 0x0($s2)
    ctx->r25 = MEM_W(ctx->r18, 0X0);
    // 0x802C59CC: or          $a0, $s7, $zero
    ctx->r4 = ctx->r23 | 0;
    // 0x802C59D0: addu        $a1, $t9, $s3
    ctx->r5 = ADD32(ctx->r25, ctx->r19);
    // 0x802C59D4: jal         0x80047EE0
    // 0x802C59D8: addiu       $a1, $a1, 0xA80
    ctx->r5 = ADD32(ctx->r5, 0XA80);
    SysUtils_MtxFToMtx(rdram, ctx);
        goto after_5;
    // 0x802C59D8: addiu       $a1, $a1, 0xA80
    ctx->r5 = ADD32(ctx->r5, 0XA80);
    after_5:
    // 0x802C59DC: lw          $t0, 0x0($s2)
    ctx->r8 = MEM_W(ctx->r18, 0X0);
    // 0x802C59E0: lw          $at, 0x0($s5)
    ctx->r1 = MEM_W(ctx->r21, 0X0);
    // 0x802C59E4: andi        $t4, $s1, 0x1
    ctx->r12 = ctx->r17 & 0X1;
    // 0x802C59E8: addu        $t1, $t0, $s0
    ctx->r9 = ADD32(ctx->r8, ctx->r16);
    // 0x802C59EC: sw          $at, 0x1280($t1)
    MEM_W(0X1280, ctx->r9) = ctx->r1;
    // 0x802C59F0: lw          $t3, 0x4($s5)
    ctx->r11 = MEM_W(ctx->r21, 0X4);
    // 0x802C59F4: addiu       $s1, $s1, 0x1
    ctx->r17 = ADD32(ctx->r17, 0X1);
    // 0x802C59F8: addiu       $s3, $s3, 0x40
    ctx->r19 = ADD32(ctx->r19, 0X40);
    // 0x802C59FC: sw          $t3, 0x1284($t1)
    MEM_W(0X1284, ctx->r9) = ctx->r11;
    // 0x802C5A00: lw          $at, 0x8($s5)
    ctx->r1 = MEM_W(ctx->r21, 0X8);
    // 0x802C5A04: lui         $t0, 0x802C
    ctx->r8 = S32(0X802C << 16);
    // 0x802C5A08: sw          $at, 0x1288($t1)
    MEM_W(0X1288, ctx->r9) = ctx->r1;
    // 0x802C5A0C: lw          $t3, 0xC($s5)
    ctx->r11 = MEM_W(ctx->r21, 0XC);
    // 0x802C5A10: beq         $t4, $zero, L_802C5A34
    if (ctx->r12 == 0) {
        // 0x802C5A14: sw          $t3, 0x128C($t1)
        MEM_W(0X128C, ctx->r9) = ctx->r11;
            goto L_802C5A34;
    }
    // 0x802C5A14: sw          $t3, 0x128C($t1)
    MEM_W(0X128C, ctx->r9) = ctx->r11;
    // 0x802C5A18: lh          $t5, 0x0($fp)
    ctx->r13 = MEM_H(ctx->r30, 0X0);
    // 0x802C5A1C: lw          $t8, 0x0($s2)
    ctx->r24 = MEM_W(ctx->r18, 0X0);
    // 0x802C5A20: addiu       $t7, $t5, 0x42
    ctx->r15 = ADD32(ctx->r13, 0X42);
    // 0x802C5A24: sll         $t6, $t7, 2
    ctx->r14 = S32(ctx->r15 << 2);
    // 0x802C5A28: addu        $t9, $t8, $s0
    ctx->r25 = ADD32(ctx->r24, ctx->r16);
    // 0x802C5A2C: b           L_802C5A4C
    // 0x802C5A30: sh          $t6, 0x1288($t9)
    MEM_H(0X1288, ctx->r25) = ctx->r14;
        goto L_802C5A4C;
    // 0x802C5A30: sh          $t6, 0x1288($t9)
    MEM_H(0X1288, ctx->r25) = ctx->r14;
L_802C5A34:
    // 0x802C5A34: lh          $t0, 0x7A00($t0)
    ctx->r8 = MEM_H(ctx->r8, 0X7A00);
    // 0x802C5A38: lw          $t3, 0x0($s2)
    ctx->r11 = MEM_W(ctx->r18, 0X0);
    // 0x802C5A3C: addiu       $t2, $t0, 0x42
    ctx->r10 = ADD32(ctx->r8, 0X42);
    // 0x802C5A40: sll         $t1, $t2, 2
    ctx->r9 = S32(ctx->r10 << 2);
    // 0x802C5A44: addu        $t4, $t3, $s0
    ctx->r12 = ADD32(ctx->r11, ctx->r16);
    // 0x802C5A48: sh          $t1, 0x1288($t4)
    MEM_H(0X1288, ctx->r12) = ctx->r9;
L_802C5A4C:
    // 0x802C5A4C: lw          $t7, 0x0($s2)
    ctx->r15 = MEM_W(ctx->r18, 0X0);
    // 0x802C5A50: sll         $t5, $s4, 2
    ctx->r13 = S32(ctx->r20 << 2);
    // 0x802C5A54: addiu       $s4, $s4, 0x20
    ctx->r20 = ADD32(ctx->r20, 0X20);
    // 0x802C5A58: addu        $t8, $t7, $s0
    ctx->r24 = ADD32(ctx->r15, ctx->r16);
    // 0x802C5A5C: addiu       $s0, $s0, 0x10
    ctx->r16 = ADD32(ctx->r16, 0X10);
    // 0x802C5A60: bne         $s1, $s6, L_802C59C8
    if (ctx->r17 != ctx->r22) {
        // 0x802C5A64: sh          $t5, 0x128A($t8)
        MEM_H(0X128A, ctx->r24) = ctx->r13;
            goto L_802C59C8;
    }
    // 0x802C5A64: sh          $t5, 0x128A($t8)
    MEM_H(0X128A, ctx->r24) = ctx->r13;
    // 0x802C5A68: lw          $ra, 0x5C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X5C);
    // 0x802C5A6C: lw          $s0, 0x38($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X38);
    // 0x802C5A70: lw          $s1, 0x3C($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X3C);
    // 0x802C5A74: lw          $s2, 0x40($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X40);
    // 0x802C5A78: lw          $s3, 0x44($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X44);
    // 0x802C5A7C: lw          $s4, 0x48($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X48);
    // 0x802C5A80: lw          $s5, 0x4C($sp)
    ctx->r21 = MEM_W(ctx->r29, 0X4C);
    // 0x802C5A84: lw          $s6, 0x50($sp)
    ctx->r22 = MEM_W(ctx->r29, 0X50);
    // 0x802C5A88: lw          $s7, 0x54($sp)
    ctx->r23 = MEM_W(ctx->r29, 0X54);
    // 0x802C5A8C: lw          $fp, 0x58($sp)
    ctx->r30 = MEM_W(ctx->r29, 0X58);
    // 0x802C5A90: jr          $ra
    // 0x802C5A94: addiu       $sp, $sp, 0x1C0
    ctx->r29 = ADD32(ctx->r29, 0X1C0);
    return;
    // 0x802C5A94: addiu       $sp, $sp, 0x1C0
    ctx->r29 = ADD32(ctx->r29, 0X1C0);
;}
RECOMP_FUNC void func_i5_802C5A98(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C5A98: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x802C5A9C: lui         $a0, 0x801D
    ctx->r4 = S32(0X801D << 16);
    // 0x802C5AA0: lw          $v0, -0x4CC8($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X4CC8);
    // 0x802C5AA4: lw          $a0, -0x4CCC($a0)
    ctx->r4 = MEM_W(ctx->r4, -0X4CCC);
    // 0x802C5AA8: lui         $a2, 0x800D
    ctx->r6 = S32(0X800D << 16);
    // 0x802C5AAC: lw          $a2, 0x48DC($a2)
    ctx->r6 = MEM_W(ctx->r6, 0X48DC);
    // 0x802C5AB0: sll         $t7, $v0, 4
    ctx->r15 = S32(ctx->r2 << 4);
    // 0x802C5AB4: sll         $t8, $a0, 1
    ctx->r24 = S32(ctx->r4 << 1);
    // 0x802C5AB8: addu        $t9, $t7, $t8
    ctx->r25 = ADD32(ctx->r15, ctx->r24);
    // 0x802C5ABC: lui         $v1, 0x800F
    ctx->r3 = S32(0X800F << 16);
    // 0x802C5AC0: lui         $t1, 0x801D
    ctx->r9 = S32(0X801D << 16);
    // 0x802C5AC4: sll         $t0, $a2, 2
    ctx->r8 = S32(ctx->r6 << 2);
    // 0x802C5AC8: addu        $v1, $v1, $t9
    ctx->r3 = ADD32(ctx->r3, ctx->r25);
    // 0x802C5ACC: addu        $t1, $t1, $t0
    ctx->r9 = ADD32(ctx->r9, ctx->r8);
    // 0x802C5AD0: lh          $v1, -0x5444($v1)
    ctx->r3 = MEM_H(ctx->r3, -0X5444);
    // 0x802C5AD4: lw          $t1, -0x4CC0($t1)
    ctx->r9 = MEM_W(ctx->r9, -0X4CC0);
    // 0x802C5AD8: lui         $a1, 0x802C
    ctx->r5 = S32(0X802C << 16);
    // 0x802C5ADC: sll         $t6, $v0, 2
    ctx->r14 = S32(ctx->r2 << 2);
    // 0x802C5AE0: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x802C5AE4: addu        $a1, $a1, $t6
    ctx->r5 = ADD32(ctx->r5, ctx->r14);
    // 0x802C5AE8: slt         $at, $t1, $v1
    ctx->r1 = SIGNED(ctx->r9) < SIGNED(ctx->r3) ? 1 : 0;
    // 0x802C5AEC: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x802C5AF0: bne         $at, $zero, L_802C5BD4
    if (ctx->r1 != 0) {
        // 0x802C5AF4: lw          $a1, 0x7A2C($a1)
        ctx->r5 = MEM_W(ctx->r5, 0X7A2C);
            goto L_802C5BD4;
    }
    // 0x802C5AF4: lw          $a1, 0x7A2C($a1)
    ctx->r5 = MEM_W(ctx->r5, 0X7A2C);
    // 0x802C5AF8: slt         $at, $a0, $a1
    ctx->r1 = SIGNED(ctx->r4) < SIGNED(ctx->r5) ? 1 : 0;
    // 0x802C5AFC: bne         $at, $zero, L_802C5BB8
    if (ctx->r1 != 0) {
        // 0x802C5B00: addiu       $t4, $zero, 0x1E
        ctx->r12 = ADD32(0, 0X1E);
            goto L_802C5BB8;
    }
    // 0x802C5B00: addiu       $t4, $zero, 0x1E
    ctx->r12 = ADD32(0, 0X1E);
    // 0x802C5B04: bnel        $v0, $zero, L_802C5B28
    if (ctx->r2 != 0) {
        // 0x802C5B08: addiu       $at, $zero, 0x1
        ctx->r1 = ADD32(0, 0X1);
            goto L_802C5B28;
    }
    goto skip_0;
    // 0x802C5B08: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    skip_0:
    // 0x802C5B0C: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x802C5B10: addiu       $v0, $v0, -0x4D80
    ctx->r2 = ADD32(ctx->r2, -0X4D80);
    // 0x802C5B14: lb          $t2, 0x0($v0)
    ctx->r10 = MEM_B(ctx->r2, 0X0);
    // 0x802C5B18: ori         $t3, $t2, 0x1
    ctx->r11 = ctx->r10 | 0X1;
    // 0x802C5B1C: b           L_802C5B98
    // 0x802C5B20: sb          $t3, 0x0($v0)
    MEM_B(0X0, ctx->r2) = ctx->r11;
        goto L_802C5B98;
    // 0x802C5B20: sb          $t3, 0x0($v0)
    MEM_B(0X0, ctx->r2) = ctx->r11;
    // 0x802C5B24: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
L_802C5B28:
    // 0x802C5B28: bnel        $v0, $at, L_802C5B4C
    if (ctx->r2 != ctx->r1) {
        // 0x802C5B2C: addiu       $at, $zero, 0x2
        ctx->r1 = ADD32(0, 0X2);
            goto L_802C5B4C;
    }
    goto skip_1;
    // 0x802C5B2C: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    skip_1:
    // 0x802C5B30: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x802C5B34: addiu       $v0, $v0, -0x4D80
    ctx->r2 = ADD32(ctx->r2, -0X4D80);
    // 0x802C5B38: lb          $t4, 0x0($v0)
    ctx->r12 = MEM_B(ctx->r2, 0X0);
    // 0x802C5B3C: ori         $t5, $t4, 0x2
    ctx->r13 = ctx->r12 | 0X2;
    // 0x802C5B40: b           L_802C5B98
    // 0x802C5B44: sb          $t5, 0x0($v0)
    MEM_B(0X0, ctx->r2) = ctx->r13;
        goto L_802C5B98;
    // 0x802C5B44: sb          $t5, 0x0($v0)
    MEM_B(0X0, ctx->r2) = ctx->r13;
    // 0x802C5B48: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
L_802C5B4C:
    // 0x802C5B4C: bne         $v0, $at, L_802C5B98
    if (ctx->r2 != ctx->r1) {
        // 0x802C5B50: lui         $v0, 0x801D
        ctx->r2 = S32(0X801D << 16);
            goto L_802C5B98;
    }
    // 0x802C5B50: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x802C5B54: addiu       $v0, $v0, -0x4D80
    ctx->r2 = ADD32(ctx->r2, -0X4D80);
    // 0x802C5B58: sll         $t8, $a2, 3
    ctx->r24 = S32(ctx->r6 << 3);
    // 0x802C5B5C: lb          $t6, 0x0($v0)
    ctx->r14 = MEM_B(ctx->r2, 0X0);
    // 0x802C5B60: subu        $t8, $t8, $a2
    ctx->r24 = SUB32(ctx->r24, ctx->r6);
    // 0x802C5B64: sll         $t8, $t8, 4
    ctx->r24 = S32(ctx->r24 << 4);
    // 0x802C5B68: subu        $t8, $t8, $a2
    ctx->r24 = SUB32(ctx->r24, ctx->r6);
    // 0x802C5B6C: sll         $t8, $t8, 3
    ctx->r24 = S32(ctx->r24 << 3);
    // 0x802C5B70: lui         $t9, 0x801C
    ctx->r25 = S32(0X801C << 16);
    // 0x802C5B74: ori         $t7, $t6, 0x4
    ctx->r15 = ctx->r14 | 0X4;
    // 0x802C5B78: sb          $t7, 0x0($v0)
    MEM_B(0X0, ctx->r2) = ctx->r15;
    // 0x802C5B7C: addu        $t9, $t9, $t8
    ctx->r25 = ADD32(ctx->r25, ctx->r24);
    // 0x802C5B80: lw          $t9, 0x2C70($t9)
    ctx->r25 = MEM_W(ctx->r25, 0X2C70);
    // 0x802C5B84: bne         $t9, $zero, L_802C5B98
    if (ctx->r25 != 0) {
        // 0x802C5B88: nop
    
            goto L_802C5B98;
    }
    // 0x802C5B88: nop

    // 0x802C5B8C: lb          $t0, 0x0($v0)
    ctx->r8 = MEM_B(ctx->r2, 0X0);
    // 0x802C5B90: ori         $t1, $t0, 0x8
    ctx->r9 = ctx->r8 | 0X8;
    // 0x802C5B94: sb          $t1, 0x0($v0)
    MEM_B(0X0, ctx->r2) = ctx->r9;
L_802C5B98:
    // 0x802C5B98: lui         $v0, 0x802C
    ctx->r2 = S32(0X802C << 16);
    // 0x802C5B9C: addiu       $t2, $zero, 0x66
    ctx->r10 = ADD32(0, 0X66);
    // 0x802C5BA0: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C5BA4: addiu       $v0, $v0, 0x7B00
    ctx->r2 = ADD32(ctx->r2, 0X7B00);
    // 0x802C5BA8: sw          $t2, 0x7B08($at)
    MEM_W(0X7B08, ctx->r1) = ctx->r10;
    // 0x802C5BAC: addiu       $t3, $zero, 0x2
    ctx->r11 = ADD32(0, 0X2);
    // 0x802C5BB0: b           L_802C5BEC
    // 0x802C5BB4: sw          $t3, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r11;
        goto L_802C5BEC;
    // 0x802C5BB4: sw          $t3, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r11;
L_802C5BB8:
    // 0x802C5BB8: lui         $v0, 0x802C
    ctx->r2 = S32(0X802C << 16);
    // 0x802C5BBC: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C5BC0: addiu       $v0, $v0, 0x7B00
    ctx->r2 = ADD32(ctx->r2, 0X7B00);
    // 0x802C5BC4: sw          $t4, 0x7B08($at)
    MEM_W(0X7B08, ctx->r1) = ctx->r12;
    // 0x802C5BC8: addiu       $t5, $zero, 0x1
    ctx->r13 = ADD32(0, 0X1);
    // 0x802C5BCC: b           L_802C5BEC
    // 0x802C5BD0: sw          $t5, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r13;
        goto L_802C5BEC;
    // 0x802C5BD0: sw          $t5, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r13;
L_802C5BD4:
    // 0x802C5BD4: lui         $v0, 0x802C
    ctx->r2 = S32(0X802C << 16);
    // 0x802C5BD8: addiu       $t6, $zero, 0x5A
    ctx->r14 = ADD32(0, 0X5A);
    // 0x802C5BDC: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x802C5BE0: addiu       $v0, $v0, 0x7B00
    ctx->r2 = ADD32(ctx->r2, 0X7B00);
    // 0x802C5BE4: sw          $t6, 0x7B08($at)
    MEM_W(0X7B08, ctx->r1) = ctx->r14;
    // 0x802C5BE8: sw          $zero, 0x0($v0)
    MEM_W(0X0, ctx->r2) = 0;
L_802C5BEC:
    // 0x802C5BEC: lw          $t7, 0x0($v0)
    ctx->r15 = MEM_W(ctx->r2, 0X0);
    // 0x802C5BF0: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x802C5BF4: beq         $t7, $zero, L_802C5C04
    if (ctx->r15 == 0) {
        // 0x802C5BF8: nop
    
            goto L_802C5C04;
    }
    // 0x802C5BF8: nop

    // 0x802C5BFC: b           L_802C5C04
    // 0x802C5C00: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
        goto L_802C5C04;
    // 0x802C5C00: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
L_802C5C04:
    // 0x802C5C04: jal         0x800C21F4
    // 0x802C5C08: addiu       $a0, $zero, 0x3
    ctx->r4 = ADD32(0, 0X3);
    func_800C21F4(rdram, ctx);
        goto after_0;
    // 0x802C5C08: addiu       $a0, $zero, 0x3
    ctx->r4 = ADD32(0, 0X3);
    after_0:
    // 0x802C5C0C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x802C5C10: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x802C5C14: jr          $ra
    // 0x802C5C18: nop

    return;
    // 0x802C5C18: nop

;}
RECOMP_FUNC void func_i5_802C5C1C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x802C5C1C: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x802C5C20: addiu       $v0, $v0, -0x19C4
    ctx->r2 = ADD32(ctx->r2, -0X19C4);
    // 0x802C5C24: lw          $t6, 0x0($v0)
    ctx->r14 = MEM_W(ctx->r2, 0X0);
    // 0x802C5C28: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x802C5C2C: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x802C5C30: beq         $t6, $zero, L_802C5C68
    if (ctx->r14 == 0) {
        // 0x802C5C34: sw          $a0, 0x18($sp)
        MEM_W(0X18, ctx->r29) = ctx->r4;
            goto L_802C5C68;
    }
    // 0x802C5C34: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    // 0x802C5C38: sw          $zero, 0x0($v0)
    MEM_W(0X0, ctx->r2) = 0;
    // 0x802C5C3C: lui         $t7, 0x800E
    ctx->r15 = S32(0X800E << 16);
    // 0x802C5C40: lw          $t7, -0x54DC($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X54DC);
    // 0x802C5C44: addiu       $at, $zero, 0x34
    ctx->r1 = ADD32(0, 0X34);
    // 0x802C5C48: bne         $t7, $at, L_802C5C68
    if (ctx->r15 != ctx->r1) {
        // 0x802C5C4C: nop
    
            goto L_802C5C68;
    }
    // 0x802C5C4C: nop

    // 0x802C5C50: jal         0x800C6AD0
    // 0x802C5C54: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    osViBlack_recomp(rdram, ctx);
        goto after_0;
    // 0x802C5C54: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    after_0:
    // 0x802C5C58: jal         0x80093C44
    // 0x802C5C5C: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
    func_80093C44(rdram, ctx);
        goto after_1;
    // 0x802C5C5C: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
    after_1:
    // 0x802C5C60: b           L_802C5DB4
    // 0x802C5C64: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_802C5DB4;
    // 0x802C5C64: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C5C68:
    // 0x802C5C68: jal         0x80093F78
    // 0x802C5C6C: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
    func_80093F78(rdram, ctx);
        goto after_2;
    // 0x802C5C6C: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
    after_2:
    // 0x802C5C70: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x802C5C74: lui         $a1, 0x800E
    ctx->r5 = S32(0X800E << 16);
    // 0x802C5C78: sw          $zero, -0x54D4($at)
    MEM_W(-0X54D4, ctx->r1) = 0;
    // 0x802C5C7C: lw          $a1, -0x7E90($a1)
    ctx->r5 = MEM_W(ctx->r5, -0X7E90);
    // 0x802C5C80: jal         0x800949B8
    // 0x802C5C84: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    func_800949B8(rdram, ctx);
        goto after_3;
    // 0x802C5C84: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    after_3:
    // 0x802C5C88: jal         0x8008FB74
    // 0x802C5C8C: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    func_8008FB74(rdram, ctx);
        goto after_4;
    // 0x802C5C8C: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    after_4:
    // 0x802C5C90: jal         0x80090F58
    // 0x802C5C94: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    Draw_WaterEffects(rdram, ctx);
        goto after_5;
    // 0x802C5C94: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    after_5:
    // 0x802C5C98: jal         0x802C5DC0
    // 0x802C5C9C: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    func_i5_802C5DC0(rdram, ctx);
        goto after_6;
    // 0x802C5C9C: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    after_6:
    // 0x802C5CA0: lui         $t8, 0x800E
    ctx->r24 = S32(0X800E << 16);
    // 0x802C5CA4: lw          $t8, -0x54DC($t8)
    ctx->r24 = MEM_W(ctx->r24, -0X54DC);
    // 0x802C5CA8: addiu       $at, $zero, 0x34
    ctx->r1 = ADD32(0, 0X34);
    // 0x802C5CAC: sw          $v0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r2;
    // 0x802C5CB0: bne         $t8, $at, L_802C5CC8
    if (ctx->r24 != ctx->r1) {
        // 0x802C5CB4: lui         $t9, 0x8023
        ctx->r25 = S32(0X8023 << 16);
            goto L_802C5CC8;
    }
    // 0x802C5CB4: lui         $t9, 0x8023
    ctx->r25 = S32(0X8023 << 16);
    // 0x802C5CB8: jal         0x802C6CC4
    // 0x802C5CBC: nop

    func_i5_802C6CC4(rdram, ctx);
        goto after_7;
    // 0x802C5CBC: nop

    after_7:
    // 0x802C5CC0: b           L_802C5D90
    // 0x802C5CC4: nop

        goto L_802C5D90;
    // 0x802C5CC4: nop

L_802C5CC8:
    // 0x802C5CC8: lh          $t9, -0x75EA($t9)
    ctx->r25 = MEM_H(ctx->r25, -0X75EA);
    // 0x802C5CCC: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x802C5CD0: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x802C5CD4: bne         $t9, $at, L_802C5D90
    if (ctx->r25 != ctx->r1) {
        // 0x802C5CD8: nop
    
            goto L_802C5D90;
    }
    // 0x802C5CD8: nop

    // 0x802C5CDC: lw          $v0, -0x19D0($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X19D0);
    // 0x802C5CE0: addiu       $at, $zero, 0x66
    ctx->r1 = ADD32(0, 0X66);
    // 0x802C5CE4: bnel        $v0, $at, L_802C5D00
    if (ctx->r2 != ctx->r1) {
        // 0x802C5CE8: addiu       $at, $zero, 0x1E
        ctx->r1 = ADD32(0, 0X1E);
            goto L_802C5D00;
    }
    goto skip_0;
    // 0x802C5CE8: addiu       $at, $zero, 0x1E
    ctx->r1 = ADD32(0, 0X1E);
    skip_0:
    // 0x802C5CEC: jal         0x801ECB98
    // 0x802C5CF0: nop

    func_801ECB98(rdram, ctx);
        goto after_8;
    // 0x802C5CF0: nop

    after_8:
    // 0x802C5CF4: b           L_802C5D90
    // 0x802C5CF8: nop

        goto L_802C5D90;
    // 0x802C5CF8: nop

    // 0x802C5CFC: addiu       $at, $zero, 0x1E
    ctx->r1 = ADD32(0, 0X1E);
L_802C5D00:
    // 0x802C5D00: bne         $v0, $at, L_802C5D88
    if (ctx->r2 != ctx->r1) {
        // 0x802C5D04: lui         $a0, 0x801D
        ctx->r4 = S32(0X801D << 16);
            goto L_802C5D88;
    }
    // 0x802C5D04: lui         $a0, 0x801D
    ctx->r4 = S32(0X801D << 16);
    // 0x802C5D08: addiu       $a0, $a0, -0x4CCC
    ctx->r4 = ADD32(ctx->r4, -0X4CCC);
    // 0x802C5D0C: lw          $t0, 0x0($a0)
    ctx->r8 = MEM_W(ctx->r4, 0X0);
    // 0x802C5D10: lui         $t2, 0x800E
    ctx->r10 = S32(0X800E << 16);
    // 0x802C5D14: lui         $a1, 0x801D
    ctx->r5 = S32(0X801D << 16);
    // 0x802C5D18: addiu       $t1, $t0, 0x1
    ctx->r9 = ADD32(ctx->r8, 0X1);
    // 0x802C5D1C: sw          $t1, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r9;
    // 0x802C5D20: lh          $t2, -0x5498($t2)
    ctx->r10 = MEM_H(ctx->r10, -0X5498);
    // 0x802C5D24: lui         $t4, 0x801D
    ctx->r12 = S32(0X801D << 16);
    // 0x802C5D28: beq         $t2, $zero, L_802C5D50
    if (ctx->r10 == 0) {
        // 0x802C5D2C: nop
    
            goto L_802C5D50;
    }
    // 0x802C5D2C: nop

    // 0x802C5D30: lui         $a1, 0x801D
    ctx->r5 = S32(0X801D << 16);
    // 0x802C5D34: addiu       $a1, $a1, -0x4D78
    ctx->r5 = ADD32(ctx->r5, -0X4D78);
    // 0x802C5D38: lw          $t3, 0xC($a1)
    ctx->r11 = MEM_W(ctx->r5, 0XC);
    // 0x802C5D3C: slt         $at, $t3, $t1
    ctx->r1 = SIGNED(ctx->r11) < SIGNED(ctx->r9) ? 1 : 0;
    // 0x802C5D40: beq         $at, $zero, L_802C5D78
    if (ctx->r1 == 0) {
        // 0x802C5D44: nop
    
            goto L_802C5D78;
    }
    // 0x802C5D44: nop

    // 0x802C5D48: b           L_802C5D78
    // 0x802C5D4C: sw          $t1, 0xC($a1)
    MEM_W(0XC, ctx->r5) = ctx->r9;
        goto L_802C5D78;
    // 0x802C5D4C: sw          $t1, 0xC($a1)
    MEM_W(0XC, ctx->r5) = ctx->r9;
L_802C5D50:
    // 0x802C5D50: lw          $t4, -0x4CC8($t4)
    ctx->r12 = MEM_W(ctx->r12, -0X4CC8);
    // 0x802C5D54: addiu       $a1, $a1, -0x4D78
    ctx->r5 = ADD32(ctx->r5, -0X4D78);
    // 0x802C5D58: lw          $v0, 0x0($a0)
    ctx->r2 = MEM_W(ctx->r4, 0X0);
    // 0x802C5D5C: sll         $t5, $t4, 2
    ctx->r13 = S32(ctx->r12 << 2);
    // 0x802C5D60: addu        $v1, $a1, $t5
    ctx->r3 = ADD32(ctx->r5, ctx->r13);
    // 0x802C5D64: lw          $t6, 0x0($v1)
    ctx->r14 = MEM_W(ctx->r3, 0X0);
    // 0x802C5D68: slt         $at, $t6, $v0
    ctx->r1 = SIGNED(ctx->r14) < SIGNED(ctx->r2) ? 1 : 0;
    // 0x802C5D6C: beq         $at, $zero, L_802C5D78
    if (ctx->r1 == 0) {
        // 0x802C5D70: nop
    
            goto L_802C5D78;
    }
    // 0x802C5D70: nop

    // 0x802C5D74: sw          $v0, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r2;
L_802C5D78:
    // 0x802C5D78: jal         0x801EB91C
    // 0x802C5D7C: nop

    func_801EB91C(rdram, ctx);
        goto after_9;
    // 0x802C5D7C: nop

    after_9:
    // 0x802C5D80: b           L_802C5D90
    // 0x802C5D84: nop

        goto L_802C5D90;
    // 0x802C5D84: nop

L_802C5D88:
    // 0x802C5D88: jal         0x801EB180
    // 0x802C5D8C: nop

    func_801EB180(rdram, ctx);
        goto after_10;
    // 0x802C5D8C: nop

    after_10:
L_802C5D90:
    // 0x802C5D90: lui         $t7, 0x801D
    ctx->r15 = S32(0X801D << 16);
    // 0x802C5D94: lw          $t7, -0x19C8($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X19C8);
    // 0x802C5D98: addiu       $at, $zero, 0x9
    ctx->r1 = ADD32(0, 0X9);
    // 0x802C5D9C: beql        $t7, $at, L_802C5DB0
    if (ctx->r15 == ctx->r1) {
        // 0x802C5DA0: lw          $v0, 0x18($sp)
        ctx->r2 = MEM_W(ctx->r29, 0X18);
            goto L_802C5DB0;
    }
    goto skip_1;
    // 0x802C5DA0: lw          $v0, 0x18($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X18);
    skip_1:
    // 0x802C5DA4: jal         0x8007C494
    // 0x802C5DA8: nop

    func_8007C494(rdram, ctx);
        goto after_11;
    // 0x802C5DA8: nop

    after_11:
    // 0x802C5DAC: lw          $v0, 0x18($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X18);
L_802C5DB0:
    // 0x802C5DB0: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_802C5DB4:
    // 0x802C5DB4: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x802C5DB8: jr          $ra
    // 0x802C5DBC: nop

    return;
    // 0x802C5DBC: nop

;}
