#include "recomp.h"
#include "funcs.h"

RECOMP_FUNC void func_801EC9C8(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801EC9C8: lui         $v1, 0x800E
    ctx->r3 = S32(0X800E << 16);
    // 0x801EC9CC: addiu       $v1, $v1, -0x54DC
    ctx->r3 = ADD32(ctx->r3, -0X54DC);
    // 0x801EC9D0: lw          $t6, 0x0($v1)
    ctx->r14 = MEM_W(ctx->r3, 0X0);
    // 0x801EC9D4: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EC9D8: addiu       $t7, $zero, 0x64
    ctx->r15 = ADD32(0, 0X64);
    // 0x801EC9DC: sw          $t6, -0x19CC($at)
    MEM_W(-0X19CC, ctx->r1) = ctx->r14;
    // 0x801EC9E0: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EC9E4: sw          $zero, -0x19D0($at)
    MEM_W(-0X19D0, ctx->r1) = 0;
    // 0x801EC9E8: sw          $t7, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r15;
    // 0x801EC9EC: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801EC9F0: addiu       $t8, $zero, 0x6
    ctx->r24 = ADD32(0, 0X6);
    // 0x801EC9F4: sw          $t8, -0x19C8($at)
    MEM_W(-0X19C8, ctx->r1) = ctx->r24;
    // 0x801EC9F8: addiu       $t0, $zero, 0x1
    ctx->r8 = ADD32(0, 0X1);
    // 0x801EC9FC: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801ECA00: sw          $t0, -0x19C4($at)
    MEM_W(-0X19C4, ctx->r1) = ctx->r8;
    // 0x801ECA04: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801ECA08: sw          $zero, -0x19C0($at)
    MEM_W(-0X19C0, ctx->r1) = 0;
    // 0x801ECA0C: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801ECA10: sw          $zero, -0x19BC($at)
    MEM_W(-0X19BC, ctx->r1) = 0;
    // 0x801ECA14: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x801ECA18: sw          $zero, -0x54E4($at)
    MEM_W(-0X54E4, ctx->r1) = 0;
    // 0x801ECA1C: lui         $at, 0x800D
    ctx->r1 = S32(0X800D << 16);
    // 0x801ECA20: addiu       $t9, $zero, 0x2
    ctx->r25 = ADD32(0, 0X2);
    // 0x801ECA24: sw          $t9, 0x461C($at)
    MEM_W(0X461C, ctx->r1) = ctx->r25;
    // 0x801ECA28: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x801ECA2C: sw          $t0, -0x54D8($at)
    MEM_W(-0X54D8, ctx->r1) = ctx->r8;
    // 0x801ECA30: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801ECA34: sw          $t0, -0x19B8($at)
    MEM_W(-0X19B8, ctx->r1) = ctx->r8;
    // 0x801ECA38: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x801ECA3C: lw          $v0, -0x19F8($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X19F8);
    // 0x801ECA40: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801ECA44: sw          $t0, -0x19B4($at)
    MEM_W(-0X19B4, ctx->r1) = ctx->r8;
    // 0x801ECA48: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x801ECA4C: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801ECA50: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x801ECA54: beq         $v0, $zero, L_801ECA64
    if (ctx->r2 == 0) {
        // 0x801ECA58: sw          $zero, -0x19B0($at)
        MEM_W(-0X19B0, ctx->r1) = 0;
            goto L_801ECA64;
    }
    // 0x801ECA58: sw          $zero, -0x19B0($at)
    MEM_W(-0X19B0, ctx->r1) = 0;
    // 0x801ECA5C: addiu       $at, $zero, 0xB
    ctx->r1 = ADD32(0, 0XB);
    // 0x801ECA60: bne         $v0, $at, L_801ECA80
    if (ctx->r2 != ctx->r1) {
        // 0x801ECA64: addiu       $t1, $zero, 0x3
        ctx->r9 = ADD32(0, 0X3);
            goto L_801ECA80;
    }
L_801ECA64:
    // 0x801ECA64: addiu       $t1, $zero, 0x3
    ctx->r9 = ADD32(0, 0X3);
    // 0x801ECA68: sw          $t1, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r9;
    // 0x801ECA6C: addiu       $a0, $zero, 0x2
    ctx->r4 = ADD32(0, 0X2);
    // 0x801ECA70: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x801ECA74: or          $a2, $t0, $zero
    ctx->r6 = ctx->r8 | 0;
    // 0x801ECA78: jal         0x80096960
    // 0x801ECA7C: addiu       $a3, $zero, 0x2
    ctx->r7 = ADD32(0, 0X2);
    func_80096960(rdram, ctx);
        goto after_0;
    // 0x801ECA7C: addiu       $a3, $zero, 0x2
    ctx->r7 = ADD32(0, 0X2);
    after_0:
L_801ECA80:
    // 0x801ECA80: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x801ECA84: lw          $v0, -0x19CC($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X19CC);
    // 0x801ECA88: addiu       $at, $zero, 0x67
    ctx->r1 = ADD32(0, 0X67);
    // 0x801ECA8C: addiu       $a0, $zero, 0x7
    ctx->r4 = ADD32(0, 0X7);
    // 0x801ECA90: bne         $v0, $at, L_801ECAA8
    if (ctx->r2 != ctx->r1) {
        // 0x801ECA94: addiu       $a1, $zero, 0x14
        ctx->r5 = ADD32(0, 0X14);
            goto L_801ECAA8;
    }
    // 0x801ECA94: addiu       $a1, $zero, 0x14
    ctx->r5 = ADD32(0, 0X14);
    // 0x801ECA98: jal         0x801E6FB0
    // 0x801ECA9C: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    FadeTransition_SetProps(rdram, ctx);
        goto after_1;
    // 0x801ECA9C: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    after_1:
    // 0x801ECAA0: b           L_801ECAC4
    // 0x801ECAA4: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
        goto L_801ECAC4;
    // 0x801ECAA4: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
L_801ECAA8:
    // 0x801ECAA8: addiu       $at, $zero, 0x2A
    ctx->r1 = ADD32(0, 0X2A);
    // 0x801ECAAC: bne         $v0, $at, L_801ECAC0
    if (ctx->r2 != ctx->r1) {
        // 0x801ECAB0: addiu       $a0, $zero, 0x4
        ctx->r4 = ADD32(0, 0X4);
            goto L_801ECAC0;
    }
    // 0x801ECAB0: addiu       $a0, $zero, 0x4
    ctx->r4 = ADD32(0, 0X4);
    // 0x801ECAB4: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x801ECAB8: jal         0x801E6FB0
    // 0x801ECABC: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    FadeTransition_SetProps(rdram, ctx);
        goto after_2;
    // 0x801ECABC: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    after_2:
L_801ECAC0:
    // 0x801ECAC0: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
L_801ECAC4:
    // 0x801ECAC4: jal         0x801E6A4C
    // 0x801ECAC8: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_801E6A4C(rdram, ctx);
        goto after_3;
    // 0x801ECAC8: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_3:
    // 0x801ECACC: addiu       $t2, $zero, 0x1
    ctx->r10 = ADD32(0, 0X1);
    // 0x801ECAD0: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801ECAD4: sw          $t2, 0x7C80($at)
    MEM_W(0X7C80, ctx->r1) = ctx->r10;
    // 0x801ECAD8: addiu       $a0, $zero, 0xC
    ctx->r4 = ADD32(0, 0XC);
    // 0x801ECADC: jal         0x800C21F4
    // 0x801ECAE0: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C21F4(rdram, ctx);
        goto after_4;
    // 0x801ECAE0: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_4:
    // 0x801ECAE4: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    // 0x801ECAE8: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x801ECAEC: jr          $ra
    // 0x801ECAF0: nop

    return;
    // 0x801ECAF0: nop

;}
RECOMP_FUNC void func_801ECAF4(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801ECAF4: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x801ECAF8: addiu       $v0, $v0, -0x54DC
    ctx->r2 = ADD32(ctx->r2, -0X54DC);
    // 0x801ECAFC: lw          $t6, 0x0($v0)
    ctx->r14 = MEM_W(ctx->r2, 0X0);
    // 0x801ECB00: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801ECB04: addiu       $t7, $zero, 0x5
    ctx->r15 = ADD32(0, 0X5);
    // 0x801ECB08: sw          $t6, -0x19CC($at)
    MEM_W(-0X19CC, ctx->r1) = ctx->r14;
    // 0x801ECB0C: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801ECB10: sw          $zero, -0x19D0($at)
    MEM_W(-0X19D0, ctx->r1) = 0;
    // 0x801ECB14: sw          $t7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r15;
    // 0x801ECB18: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801ECB1C: addiu       $t8, $zero, 0x13
    ctx->r24 = ADD32(0, 0X13);
    // 0x801ECB20: sw          $t8, -0x19C8($at)
    MEM_W(-0X19C8, ctx->r1) = ctx->r24;
    // 0x801ECB24: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801ECB28: addiu       $t9, $zero, 0x1
    ctx->r25 = ADD32(0, 0X1);
    // 0x801ECB2C: sw          $t9, -0x19C4($at)
    MEM_W(-0X19C4, ctx->r1) = ctx->r25;
    // 0x801ECB30: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801ECB34: sw          $zero, -0x19C0($at)
    MEM_W(-0X19C0, ctx->r1) = 0;
    // 0x801ECB38: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801ECB3C: sw          $zero, -0x19BC($at)
    MEM_W(-0X19BC, ctx->r1) = 0;
    // 0x801ECB40: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x801ECB44: addiu       $t0, $zero, 0x3
    ctx->r8 = ADD32(0, 0X3);
    // 0x801ECB48: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x801ECB4C: sw          $t0, -0x54E4($at)
    MEM_W(-0X54E4, ctx->r1) = ctx->r8;
    // 0x801ECB50: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x801ECB54: lui         $at, 0x800D
    ctx->r1 = S32(0X800D << 16);
    // 0x801ECB58: addiu       $t1, $zero, 0x2
    ctx->r9 = ADD32(0, 0X2);
    // 0x801ECB5C: sw          $t1, 0x461C($at)
    MEM_W(0X461C, ctx->r1) = ctx->r9;
    // 0x801ECB60: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    // 0x801ECB64: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x801ECB68: jal         0x801E6FB0
    // 0x801ECB6C: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    FadeTransition_SetProps(rdram, ctx);
        goto after_0;
    // 0x801ECB6C: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    after_0:
    // 0x801ECB70: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    // 0x801ECB74: jal         0x801E6A4C
    // 0x801ECB78: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_801E6A4C(rdram, ctx);
        goto after_1;
    // 0x801ECB78: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_1:
    // 0x801ECB7C: addiu       $a0, $zero, 0x8
    ctx->r4 = ADD32(0, 0X8);
    // 0x801ECB80: jal         0x800C21F4
    // 0x801ECB84: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C21F4(rdram, ctx);
        goto after_2;
    // 0x801ECB84: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_2:
    // 0x801ECB88: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x801ECB8C: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x801ECB90: jr          $ra
    // 0x801ECB94: nop

    return;
    // 0x801ECB94: nop

;}
RECOMP_FUNC void func_801ECB98(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801ECB98: lui         $a0, 0x800E
    ctx->r4 = S32(0X800E << 16);
    // 0x801ECB9C: addiu       $a0, $a0, -0x54DC
    ctx->r4 = ADD32(ctx->r4, -0X54DC);
    // 0x801ECBA0: lw          $t6, 0x0($a0)
    ctx->r14 = MEM_W(ctx->r4, 0X0);
    // 0x801ECBA4: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801ECBA8: addiu       $t7, $zero, 0x66
    ctx->r15 = ADD32(0, 0X66);
    // 0x801ECBAC: sw          $t6, -0x19CC($at)
    MEM_W(-0X19CC, ctx->r1) = ctx->r14;
    // 0x801ECBB0: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801ECBB4: sw          $zero, -0x19D0($at)
    MEM_W(-0X19D0, ctx->r1) = 0;
    // 0x801ECBB8: sw          $t7, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r15;
    // 0x801ECBBC: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801ECBC0: addiu       $t8, $zero, 0x15
    ctx->r24 = ADD32(0, 0X15);
    // 0x801ECBC4: sw          $t8, -0x19C8($at)
    MEM_W(-0X19C8, ctx->r1) = ctx->r24;
    // 0x801ECBC8: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
    // 0x801ECBCC: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801ECBD0: sw          $v0, -0x19C4($at)
    MEM_W(-0X19C4, ctx->r1) = ctx->r2;
    // 0x801ECBD4: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801ECBD8: sw          $zero, -0x19C0($at)
    MEM_W(-0X19C0, ctx->r1) = 0;
    // 0x801ECBDC: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801ECBE0: sw          $zero, -0x19BC($at)
    MEM_W(-0X19BC, ctx->r1) = 0;
    // 0x801ECBE4: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x801ECBE8: sw          $zero, -0x54E4($at)
    MEM_W(-0X54E4, ctx->r1) = 0;
    // 0x801ECBEC: addiu       $v1, $zero, 0x3
    ctx->r3 = ADD32(0, 0X3);
    // 0x801ECBF0: lui         $at, 0x800D
    ctx->r1 = S32(0X800D << 16);
    // 0x801ECBF4: sw          $v1, 0x461C($at)
    MEM_W(0X461C, ctx->r1) = ctx->r3;
    // 0x801ECBF8: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801ECBFC: sw          $zero, -0x19E0($at)
    MEM_W(-0X19E0, ctx->r1) = 0;
    // 0x801ECC00: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x801ECC04: sw          $v0, -0x54D8($at)
    MEM_W(-0X54D8, ctx->r1) = ctx->r2;
    // 0x801ECC08: lui         $at, 0x801A
    ctx->r1 = S32(0X801A << 16);
    // 0x801ECC0C: addiu       $t9, $zero, 0x4
    ctx->r25 = ADD32(0, 0X4);
    // 0x801ECC10: sw          $t9, -0x7D10($at)
    MEM_W(-0X7D10, ctx->r1) = ctx->r25;
    // 0x801ECC14: lui         $at, 0x800D
    ctx->r1 = S32(0X800D << 16);
    // 0x801ECC18: addiu       $t5, $zero, 0xA
    ctx->r13 = ADD32(0, 0XA);
    // 0x801ECC1C: sw          $t5, 0x49B0($at)
    MEM_W(0X49B0, ctx->r1) = ctx->r13;
    // 0x801ECC20: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x801ECC24: addiu       $t6, $zero, 0x5
    ctx->r14 = ADD32(0, 0X5);
    // 0x801ECC28: sw          $t6, -0x7E8C($at)
    MEM_W(-0X7E8C, ctx->r1) = ctx->r14;
    // 0x801ECC2C: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801ECC30: lui         $t4, 0x800E
    ctx->r12 = S32(0X800E << 16);
    // 0x801ECC34: sw          $v1, -0x18D8($at)
    MEM_W(-0X18D8, ctx->r1) = ctx->r3;
    // 0x801ECC38: addiu       $t4, $t4, -0x7E90
    ctx->r12 = ADD32(ctx->r12, -0X7E90);
    // 0x801ECC3C: addiu       $t7, $zero, 0x7
    ctx->r15 = ADD32(0, 0X7);
    // 0x801ECC40: sw          $t7, 0x0($t4)
    MEM_W(0X0, ctx->r12) = ctx->r15;
    // 0x801ECC44: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x801ECC48: sw          $v0, -0x7E88($at)
    MEM_W(-0X7E88, ctx->r1) = ctx->r2;
    // 0x801ECC4C: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801ECC50: addiu       $t8, $zero, 0x2
    ctx->r24 = ADD32(0, 0X2);
    // 0x801ECC54: lui         $t0, 0x800E
    ctx->r8 = S32(0X800E << 16);
    // 0x801ECC58: lw          $t0, -0x5650($t0)
    ctx->r8 = MEM_W(ctx->r8, -0X5650);
    // 0x801ECC5C: sw          $t8, -0x19B8($at)
    MEM_W(-0X19B8, ctx->r1) = ctx->r24;
    // 0x801ECC60: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801ECC64: sw          $zero, -0x19B4($at)
    MEM_W(-0X19B4, ctx->r1) = 0;
    // 0x801ECC68: addiu       $a3, $zero, 0xC
    ctx->r7 = ADD32(0, 0XC);
    // 0x801ECC6C: multu       $t0, $a3
    result = U64(U32(ctx->r8)) * U64(U32(ctx->r7)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x801ECC70: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801ECC74: sw          $v1, -0x19B0($at)
    MEM_W(-0X19B0, ctx->r1) = ctx->r3;
    // 0x801ECC78: lui         $at, 0x8019
    ctx->r1 = S32(0X8019 << 16);
    // 0x801ECC7C: sw          $t0, 0x31F8($at)
    MEM_W(0X31F8, ctx->r1) = ctx->r8;
    // 0x801ECC80: lw          $t9, 0x0($t4)
    ctx->r25 = MEM_W(ctx->r12, 0X0);
    // 0x801ECC84: lui         $t6, 0x800E
    ctx->r14 = S32(0X800E << 16);
    // 0x801ECC88: addiu       $t6, $t6, -0x695C
    ctx->r14 = ADD32(ctx->r14, -0X695C);
    // 0x801ECC8C: sll         $t5, $t9, 2
    ctx->r13 = S32(ctx->r25 << 2);
    // 0x801ECC90: subu        $t5, $t5, $t9
    ctx->r13 = SUB32(ctx->r13, ctx->r25);
    // 0x801ECC94: sll         $t5, $t5, 4
    ctx->r13 = S32(ctx->r13 << 4);
    // 0x801ECC98: mflo        $t7
    ctx->r15 = lo;
    // 0x801ECC9C: lui         $t1, 0x800E
    ctx->r9 = S32(0X800E << 16);
    // 0x801ECCA0: addu        $v0, $t5, $t6
    ctx->r2 = ADD32(ctx->r13, ctx->r14);
    // 0x801ECCA4: lw          $t1, -0x564C($t1)
    ctx->r9 = MEM_W(ctx->r9, -0X564C);
    // 0x801ECCA8: addu        $v1, $v0, $t7
    ctx->r3 = ADD32(ctx->r2, ctx->r15);
    // 0x801ECCAC: lw          $t8, 0x0($v1)
    ctx->r24 = MEM_W(ctx->r3, 0X0);
    // 0x801ECCB0: multu       $t1, $a3
    result = U64(U32(ctx->r9)) * U64(U32(ctx->r7)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x801ECCB4: lui         $at, 0x8019
    ctx->r1 = S32(0X8019 << 16);
    // 0x801ECCB8: sw          $t8, 0x31FC($at)
    MEM_W(0X31FC, ctx->r1) = ctx->r24;
    // 0x801ECCBC: lw          $t9, 0x4($v1)
    ctx->r25 = MEM_W(ctx->r3, 0X4);
    // 0x801ECCC0: lui         $at, 0x8019
    ctx->r1 = S32(0X8019 << 16);
    // 0x801ECCC4: lui         $t2, 0x800E
    ctx->r10 = S32(0X800E << 16);
    // 0x801ECCC8: sw          $t9, 0x3200($at)
    MEM_W(0X3200, ctx->r1) = ctx->r25;
    // 0x801ECCCC: lw          $t5, 0x8($v1)
    ctx->r13 = MEM_W(ctx->r3, 0X8);
    // 0x801ECCD0: lui         $at, 0x8019
    ctx->r1 = S32(0X8019 << 16);
    // 0x801ECCD4: lw          $t2, -0x5648($t2)
    ctx->r10 = MEM_W(ctx->r10, -0X5648);
    // 0x801ECCD8: sw          $t5, 0x3204($at)
    MEM_W(0X3204, ctx->r1) = ctx->r13;
    // 0x801ECCDC: mflo        $t6
    ctx->r14 = lo;
    // 0x801ECCE0: lui         $at, 0x8019
    ctx->r1 = S32(0X8019 << 16);
    // 0x801ECCE4: addu        $a0, $v0, $t6
    ctx->r4 = ADD32(ctx->r2, ctx->r14);
    // 0x801ECCE8: sw          $t1, 0x4910($at)
    MEM_W(0X4910, ctx->r1) = ctx->r9;
    // 0x801ECCEC: lw          $t7, 0x0($a0)
    ctx->r15 = MEM_W(ctx->r4, 0X0);
    // 0x801ECCF0: multu       $t2, $a3
    result = U64(U32(ctx->r10)) * U64(U32(ctx->r7)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x801ECCF4: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x801ECCF8: lui         $at, 0x8019
    ctx->r1 = S32(0X8019 << 16);
    // 0x801ECCFC: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x801ECD00: sw          $t7, 0x4914($at)
    MEM_W(0X4914, ctx->r1) = ctx->r15;
    // 0x801ECD04: lw          $t8, 0x4($a0)
    ctx->r24 = MEM_W(ctx->r4, 0X4);
    // 0x801ECD08: lui         $at, 0x8019
    ctx->r1 = S32(0X8019 << 16);
    // 0x801ECD0C: lui         $t3, 0x800E
    ctx->r11 = S32(0X800E << 16);
    // 0x801ECD10: sw          $t8, 0x4918($at)
    MEM_W(0X4918, ctx->r1) = ctx->r24;
    // 0x801ECD14: lw          $t9, 0x8($a0)
    ctx->r25 = MEM_W(ctx->r4, 0X8);
    // 0x801ECD18: lui         $at, 0x8019
    ctx->r1 = S32(0X8019 << 16);
    // 0x801ECD1C: mflo        $t5
    ctx->r13 = lo;
    // 0x801ECD20: sw          $t9, 0x491C($at)
    MEM_W(0X491C, ctx->r1) = ctx->r25;
    // 0x801ECD24: lui         $at, 0x8019
    ctx->r1 = S32(0X8019 << 16);
    // 0x801ECD28: lw          $t3, -0x5644($t3)
    ctx->r11 = MEM_W(ctx->r11, -0X5644);
    // 0x801ECD2C: addu        $a1, $v0, $t5
    ctx->r5 = ADD32(ctx->r2, ctx->r13);
    // 0x801ECD30: sw          $t2, 0x6028($at)
    MEM_W(0X6028, ctx->r1) = ctx->r10;
    // 0x801ECD34: lw          $t6, 0x0($a1)
    ctx->r14 = MEM_W(ctx->r5, 0X0);
    // 0x801ECD38: multu       $t3, $a3
    result = U64(U32(ctx->r11)) * U64(U32(ctx->r7)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x801ECD3C: lui         $at, 0x8019
    ctx->r1 = S32(0X8019 << 16);
    // 0x801ECD40: sw          $t6, 0x602C($at)
    MEM_W(0X602C, ctx->r1) = ctx->r14;
    // 0x801ECD44: lw          $t7, 0x4($a1)
    ctx->r15 = MEM_W(ctx->r5, 0X4);
    // 0x801ECD48: lui         $at, 0x8019
    ctx->r1 = S32(0X8019 << 16);
    // 0x801ECD4C: addiu       $a0, $zero, 0x2
    ctx->r4 = ADD32(0, 0X2);
    // 0x801ECD50: sw          $t7, 0x6030($at)
    MEM_W(0X6030, ctx->r1) = ctx->r15;
    // 0x801ECD54: lw          $t8, 0x8($a1)
    ctx->r24 = MEM_W(ctx->r5, 0X8);
    // 0x801ECD58: lui         $at, 0x8019
    ctx->r1 = S32(0X8019 << 16);
    // 0x801ECD5C: sw          $t8, 0x6034($at)
    MEM_W(0X6034, ctx->r1) = ctx->r24;
    // 0x801ECD60: lui         $at, 0x8019
    ctx->r1 = S32(0X8019 << 16);
    // 0x801ECD64: mflo        $t9
    ctx->r25 = lo;
    // 0x801ECD68: addu        $a2, $v0, $t9
    ctx->r6 = ADD32(ctx->r2, ctx->r25);
    // 0x801ECD6C: sw          $t3, 0x7740($at)
    MEM_W(0X7740, ctx->r1) = ctx->r11;
    // 0x801ECD70: lw          $t5, 0x0($a2)
    ctx->r13 = MEM_W(ctx->r6, 0X0);
    // 0x801ECD74: lui         $at, 0x8019
    ctx->r1 = S32(0X8019 << 16);
    // 0x801ECD78: lui         $t8, 0x800D
    ctx->r24 = S32(0X800D << 16);
    // 0x801ECD7C: sw          $t5, 0x7744($at)
    MEM_W(0X7744, ctx->r1) = ctx->r13;
    // 0x801ECD80: lw          $t6, 0x4($a2)
    ctx->r14 = MEM_W(ctx->r6, 0X4);
    // 0x801ECD84: lui         $at, 0x8019
    ctx->r1 = S32(0X8019 << 16);
    // 0x801ECD88: lw          $t8, 0x48DC($t8)
    ctx->r24 = MEM_W(ctx->r24, 0X48DC);
    // 0x801ECD8C: sw          $t6, 0x7748($at)
    MEM_W(0X7748, ctx->r1) = ctx->r14;
    // 0x801ECD90: lw          $t7, 0x8($a2)
    ctx->r15 = MEM_W(ctx->r6, 0X8);
    // 0x801ECD94: lui         $t6, 0x801D
    ctx->r14 = S32(0X801D << 16);
    // 0x801ECD98: lh          $t6, -0x190C($t6)
    ctx->r14 = MEM_H(ctx->r14, -0X190C);
    // 0x801ECD9C: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x801ECDA0: addiu       $v0, $v0, -0x5650
    ctx->r2 = ADD32(ctx->r2, -0X5650);
    // 0x801ECDA4: lui         $at, 0x8019
    ctx->r1 = S32(0X8019 << 16);
    // 0x801ECDA8: sll         $t9, $t8, 2
    ctx->r25 = S32(ctx->r24 << 2);
    // 0x801ECDAC: addu        $t5, $v0, $t9
    ctx->r13 = ADD32(ctx->r2, ctx->r25);
    // 0x801ECDB0: sw          $t7, 0x774C($at)
    MEM_W(0X774C, ctx->r1) = ctx->r15;
    // 0x801ECDB4: beq         $t6, $zero, L_801ECDC0
    if (ctx->r14 == 0) {
        // 0x801ECDB8: lw          $a1, 0x0($t5)
        ctx->r5 = MEM_W(ctx->r13, 0X0);
            goto L_801ECDC0;
    }
    // 0x801ECDB8: lw          $a1, 0x0($t5)
    ctx->r5 = MEM_W(ctx->r13, 0X0);
    // 0x801ECDBC: addiu       $a1, $a1, 0x4
    ctx->r5 = ADD32(ctx->r5, 0X4);
L_801ECDC0:
    // 0x801ECDC0: lw          $t7, 0xC($v0)
    ctx->r15 = MEM_W(ctx->r2, 0XC);
    // 0x801ECDC4: lw          $a2, 0x4($v0)
    ctx->r6 = MEM_W(ctx->r2, 0X4);
    // 0x801ECDC8: lw          $a3, 0x8($v0)
    ctx->r7 = MEM_W(ctx->r2, 0X8);
    // 0x801ECDCC: jal         0x80096960
    // 0x801ECDD0: sw          $t7, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r15;
    func_80096960(rdram, ctx);
        goto after_0;
    // 0x801ECDD0: sw          $t7, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r15;
    after_0:
    // 0x801ECDD4: lui         $a0, 0x806
    ctx->r4 = S32(0X806 << 16);
    // 0x801ECDD8: addiu       $a1, $zero, 0x3
    ctx->r5 = ADD32(0, 0X3);
    // 0x801ECDDC: jal         0x8009684C
    // 0x801ECDE0: addiu       $a2, $zero, -0x1
    ctx->r6 = ADD32(0, -0X1);
    func_8009684C(rdram, ctx);
        goto after_1;
    // 0x801ECDE0: addiu       $a2, $zero, -0x1
    ctx->r6 = ADD32(0, -0X1);
    after_1:
    // 0x801ECDE4: addiu       $a0, $zero, 0x7
    ctx->r4 = ADD32(0, 0X7);
    // 0x801ECDE8: addiu       $a1, $zero, 0xA
    ctx->r5 = ADD32(0, 0XA);
    // 0x801ECDEC: jal         0x801E6FB0
    // 0x801ECDF0: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    FadeTransition_SetProps(rdram, ctx);
        goto after_2;
    // 0x801ECDF0: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    after_2:
    // 0x801ECDF4: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    // 0x801ECDF8: jal         0x801E6A4C
    // 0x801ECDFC: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_801E6A4C(rdram, ctx);
        goto after_3;
    // 0x801ECDFC: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_3:
    // 0x801ECE00: lui         $t9, 0x800D
    ctx->r25 = S32(0X800D << 16);
    // 0x801ECE04: lw          $t9, 0x48DC($t9)
    ctx->r25 = MEM_W(ctx->r25, 0X48DC);
    // 0x801ECE08: lui         $a1, 0x801C
    ctx->r5 = S32(0X801C << 16);
    // 0x801ECE0C: addiu       $t8, $zero, 0x8
    ctx->r24 = ADD32(0, 0X8);
    // 0x801ECE10: sll         $t5, $t9, 3
    ctx->r13 = S32(ctx->r25 << 3);
    // 0x801ECE14: subu        $t5, $t5, $t9
    ctx->r13 = SUB32(ctx->r13, ctx->r25);
    // 0x801ECE18: sll         $t5, $t5, 4
    ctx->r13 = S32(ctx->r13 << 4);
    // 0x801ECE1C: subu        $t5, $t5, $t9
    ctx->r13 = SUB32(ctx->r13, ctx->r25);
    // 0x801ECE20: sll         $t5, $t5, 3
    ctx->r13 = S32(ctx->r13 << 3);
    // 0x801ECE24: addu        $a1, $a1, $t5
    ctx->r5 = ADD32(ctx->r5, ctx->r13);
    // 0x801ECE28: lw          $a1, 0x2C70($a1)
    ctx->r5 = MEM_W(ctx->r5, 0X2C70);
    // 0x801ECE2C: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801ECE30: sw          $t8, 0x7C80($at)
    MEM_W(0X7C80, ctx->r1) = ctx->r24;
    // 0x801ECE34: addiu       $a0, $zero, 0xB
    ctx->r4 = ADD32(0, 0XB);
    // 0x801ECE38: jal         0x800C21F4
    // 0x801ECE3C: addiu       $a1, $a1, 0x1
    ctx->r5 = ADD32(ctx->r5, 0X1);
    func_800C21F4(rdram, ctx);
        goto after_4;
    // 0x801ECE3C: addiu       $a1, $a1, 0x1
    ctx->r5 = ADD32(ctx->r5, 0X1);
    after_4:
    // 0x801ECE40: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    // 0x801ECE44: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x801ECE48: jr          $ra
    // 0x801ECE4C: nop

    return;
    // 0x801ECE4C: nop

;}
RECOMP_FUNC void func_801ECE50(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801ECE50: lui         $v1, 0x800E
    ctx->r3 = S32(0X800E << 16);
    // 0x801ECE54: addiu       $v1, $v1, -0x54DC
    ctx->r3 = ADD32(ctx->r3, -0X54DC);
    // 0x801ECE58: lw          $t6, 0x0($v1)
    ctx->r14 = MEM_W(ctx->r3, 0X0);
    // 0x801ECE5C: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801ECE60: addiu       $t7, $zero, 0x36
    ctx->r15 = ADD32(0, 0X36);
    // 0x801ECE64: sw          $t6, -0x19CC($at)
    MEM_W(-0X19CC, ctx->r1) = ctx->r14;
    // 0x801ECE68: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801ECE6C: sw          $zero, -0x19D0($at)
    MEM_W(-0X19D0, ctx->r1) = 0;
    // 0x801ECE70: sw          $t7, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r15;
    // 0x801ECE74: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801ECE78: addiu       $t8, $zero, 0x12
    ctx->r24 = ADD32(0, 0X12);
    // 0x801ECE7C: sw          $t8, -0x19C8($at)
    MEM_W(-0X19C8, ctx->r1) = ctx->r24;
    // 0x801ECE80: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
    // 0x801ECE84: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801ECE88: sw          $v0, -0x19C4($at)
    MEM_W(-0X19C4, ctx->r1) = ctx->r2;
    // 0x801ECE8C: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801ECE90: sw          $zero, -0x19C0($at)
    MEM_W(-0X19C0, ctx->r1) = 0;
    // 0x801ECE94: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801ECE98: sw          $zero, -0x19BC($at)
    MEM_W(-0X19BC, ctx->r1) = 0;
    // 0x801ECE9C: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x801ECEA0: sw          $zero, -0x54E4($at)
    MEM_W(-0X54E4, ctx->r1) = 0;
    // 0x801ECEA4: lui         $at, 0x800D
    ctx->r1 = S32(0X800D << 16);
    // 0x801ECEA8: addiu       $t9, $zero, 0x2
    ctx->r25 = ADD32(0, 0X2);
    // 0x801ECEAC: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x801ECEB0: sw          $t9, 0x461C($at)
    MEM_W(0X461C, ctx->r1) = ctx->r25;
    // 0x801ECEB4: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x801ECEB8: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x801ECEBC: sw          $v0, -0x54D8($at)
    MEM_W(-0X54D8, ctx->r1) = ctx->r2;
    // 0x801ECEC0: addiu       $a0, $zero, 0x4
    ctx->r4 = ADD32(0, 0X4);
    // 0x801ECEC4: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x801ECEC8: jal         0x801E6FB0
    // 0x801ECECC: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    FadeTransition_SetProps(rdram, ctx);
        goto after_0;
    // 0x801ECECC: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    after_0:
    // 0x801ECED0: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    // 0x801ECED4: jal         0x801E6A4C
    // 0x801ECED8: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_801E6A4C(rdram, ctx);
        goto after_1;
    // 0x801ECED8: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_1:
    // 0x801ECEDC: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
    // 0x801ECEE0: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801ECEE4: sw          $v0, -0x19B8($at)
    MEM_W(-0X19B8, ctx->r1) = ctx->r2;
    // 0x801ECEE8: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801ECEEC: sw          $v0, -0x19B4($at)
    MEM_W(-0X19B4, ctx->r1) = ctx->r2;
    // 0x801ECEF0: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801ECEF4: sw          $zero, -0x19B0($at)
    MEM_W(-0X19B0, ctx->r1) = 0;
    // 0x801ECEF8: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801ECEFC: sw          $v0, 0x7C80($at)
    MEM_W(0X7C80, ctx->r1) = ctx->r2;
    // 0x801ECF00: jal         0x800C6AD0
    // 0x801ECF04: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    osViBlack_recomp(rdram, ctx);
        goto after_2;
    // 0x801ECF04: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    after_2:
    // 0x801ECF08: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x801ECF0C: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x801ECF10: jr          $ra
    // 0x801ECF14: nop

    return;
    // 0x801ECF14: nop

;}
RECOMP_FUNC void func_801ECF18(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801ECF18: lui         $v1, 0x800E
    ctx->r3 = S32(0X800E << 16);
    // 0x801ECF1C: addiu       $v1, $v1, -0x54DC
    ctx->r3 = ADD32(ctx->r3, -0X54DC);
    // 0x801ECF20: lw          $t6, 0x0($v1)
    ctx->r14 = MEM_W(ctx->r3, 0X0);
    // 0x801ECF24: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801ECF28: addiu       $t7, $zero, 0x38
    ctx->r15 = ADD32(0, 0X38);
    // 0x801ECF2C: sw          $t6, -0x19CC($at)
    MEM_W(-0X19CC, ctx->r1) = ctx->r14;
    // 0x801ECF30: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801ECF34: sw          $zero, -0x19D0($at)
    MEM_W(-0X19D0, ctx->r1) = 0;
    // 0x801ECF38: sw          $t7, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r15;
    // 0x801ECF3C: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801ECF40: addiu       $t8, $zero, 0x16
    ctx->r24 = ADD32(0, 0X16);
    // 0x801ECF44: sw          $t8, -0x19C8($at)
    MEM_W(-0X19C8, ctx->r1) = ctx->r24;
    // 0x801ECF48: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    // 0x801ECF4C: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801ECF50: sw          $a2, -0x19C4($at)
    MEM_W(-0X19C4, ctx->r1) = ctx->r6;
    // 0x801ECF54: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801ECF58: sw          $zero, -0x19C0($at)
    MEM_W(-0X19C0, ctx->r1) = 0;
    // 0x801ECF5C: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801ECF60: sw          $zero, -0x19BC($at)
    MEM_W(-0X19BC, ctx->r1) = 0;
    // 0x801ECF64: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x801ECF68: sw          $zero, -0x54E4($at)
    MEM_W(-0X54E4, ctx->r1) = 0;
    // 0x801ECF6C: lui         $at, 0x800D
    ctx->r1 = S32(0X800D << 16);
    // 0x801ECF70: addiu       $t9, $zero, 0x2
    ctx->r25 = ADD32(0, 0X2);
    // 0x801ECF74: sw          $t9, 0x461C($at)
    MEM_W(0X461C, ctx->r1) = ctx->r25;
    // 0x801ECF78: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x801ECF7C: sw          $a2, -0x54D8($at)
    MEM_W(-0X54D8, ctx->r1) = ctx->r6;
    // 0x801ECF80: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801ECF84: sw          $a2, -0x19B8($at)
    MEM_W(-0X19B8, ctx->r1) = ctx->r6;
    // 0x801ECF88: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801ECF8C: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x801ECF90: sw          $a2, -0x19B4($at)
    MEM_W(-0X19B4, ctx->r1) = ctx->r6;
    // 0x801ECF94: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x801ECF98: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801ECF9C: addiu       $t0, $zero, 0x3
    ctx->r8 = ADD32(0, 0X3);
    // 0x801ECFA0: sw          $zero, -0x19B0($at)
    MEM_W(-0X19B0, ctx->r1) = 0;
    // 0x801ECFA4: sw          $t0, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r8;
    // 0x801ECFA8: addiu       $a0, $zero, 0x2
    ctx->r4 = ADD32(0, 0X2);
    // 0x801ECFAC: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x801ECFB0: jal         0x80096960
    // 0x801ECFB4: addiu       $a3, $zero, 0x2
    ctx->r7 = ADD32(0, 0X2);
    func_80096960(rdram, ctx);
        goto after_0;
    // 0x801ECFB4: addiu       $a3, $zero, 0x2
    ctx->r7 = ADD32(0, 0X2);
    after_0:
    // 0x801ECFB8: addiu       $a0, $zero, 0x4
    ctx->r4 = ADD32(0, 0X4);
    // 0x801ECFBC: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x801ECFC0: jal         0x801E6FB0
    // 0x801ECFC4: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    FadeTransition_SetProps(rdram, ctx);
        goto after_1;
    // 0x801ECFC4: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    after_1:
    // 0x801ECFC8: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    // 0x801ECFCC: jal         0x801E6A4C
    // 0x801ECFD0: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_801E6A4C(rdram, ctx);
        goto after_2;
    // 0x801ECFD0: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_2:
    // 0x801ECFD4: addiu       $t1, $zero, 0x1
    ctx->r9 = ADD32(0, 0X1);
    // 0x801ECFD8: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801ECFDC: sw          $t1, 0x7C80($at)
    MEM_W(0X7C80, ctx->r1) = ctx->r9;
    // 0x801ECFE0: addiu       $a0, $zero, 0x3
    ctx->r4 = ADD32(0, 0X3);
    // 0x801ECFE4: jal         0x800C21F4
    // 0x801ECFE8: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C21F4(rdram, ctx);
        goto after_3;
    // 0x801ECFE8: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_3:
    // 0x801ECFEC: jal         0x800C6AD0
    // 0x801ECFF0: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    osViBlack_recomp(rdram, ctx);
        goto after_4;
    // 0x801ECFF0: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    after_4:
    // 0x801ECFF4: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    // 0x801ECFF8: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x801ECFFC: jr          $ra
    // 0x801ED000: nop

    return;
    // 0x801ED000: nop

;}
RECOMP_FUNC void func_801ED004(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801ED004: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x801ED008: addiu       $v0, $v0, -0x54DC
    ctx->r2 = ADD32(ctx->r2, -0X54DC);
    // 0x801ED00C: lw          $t6, 0x0($v0)
    ctx->r14 = MEM_W(ctx->r2, 0X0);
    // 0x801ED010: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801ED014: addiu       $t7, $zero, 0x39
    ctx->r15 = ADD32(0, 0X39);
    // 0x801ED018: sw          $t6, -0x19CC($at)
    MEM_W(-0X19CC, ctx->r1) = ctx->r14;
    // 0x801ED01C: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801ED020: sw          $zero, -0x19D0($at)
    MEM_W(-0X19D0, ctx->r1) = 0;
    // 0x801ED024: sw          $t7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r15;
    // 0x801ED028: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801ED02C: addiu       $t8, $zero, 0x17
    ctx->r24 = ADD32(0, 0X17);
    // 0x801ED030: sw          $t8, -0x19C8($at)
    MEM_W(-0X19C8, ctx->r1) = ctx->r24;
    // 0x801ED034: addiu       $v1, $zero, 0x1
    ctx->r3 = ADD32(0, 0X1);
    // 0x801ED038: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801ED03C: sw          $v1, -0x19C4($at)
    MEM_W(-0X19C4, ctx->r1) = ctx->r3;
    // 0x801ED040: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801ED044: sw          $zero, -0x19C0($at)
    MEM_W(-0X19C0, ctx->r1) = 0;
    // 0x801ED048: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801ED04C: sw          $zero, -0x19BC($at)
    MEM_W(-0X19BC, ctx->r1) = 0;
    // 0x801ED050: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x801ED054: sw          $zero, -0x54E4($at)
    MEM_W(-0X54E4, ctx->r1) = 0;
    // 0x801ED058: lui         $at, 0x800D
    ctx->r1 = S32(0X800D << 16);
    // 0x801ED05C: addiu       $t9, $zero, 0x2
    ctx->r25 = ADD32(0, 0X2);
    // 0x801ED060: sw          $t9, 0x461C($at)
    MEM_W(0X461C, ctx->r1) = ctx->r25;
    // 0x801ED064: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x801ED068: sw          $v1, -0x54D8($at)
    MEM_W(-0X54D8, ctx->r1) = ctx->r3;
    // 0x801ED06C: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801ED070: sw          $v1, -0x19B8($at)
    MEM_W(-0X19B8, ctx->r1) = ctx->r3;
    // 0x801ED074: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801ED078: sw          $v1, -0x19B4($at)
    MEM_W(-0X19B4, ctx->r1) = ctx->r3;
    // 0x801ED07C: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801ED080: sw          $zero, -0x19B0($at)
    MEM_W(-0X19B0, ctx->r1) = 0;
    // 0x801ED084: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801ED088: jr          $ra
    // 0x801ED08C: sw          $v1, 0x7C80($at)
    MEM_W(0X7C80, ctx->r1) = ctx->r3;
    return;
    // 0x801ED08C: sw          $v1, 0x7C80($at)
    MEM_W(0X7C80, ctx->r1) = ctx->r3;
;}
RECOMP_FUNC void func_801ED090(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801ED090: lui         $at, 0xBF80
    ctx->r1 = S32(0XBF80 << 16);
    // 0x801ED094: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x801ED098: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x801ED09C: c.lt.s      $f12, $f4
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    c1cs = ctx->f12.fl < ctx->f4.fl;
    // 0x801ED0A0: nop

    // 0x801ED0A4: bc1tl       L_801ED0C8
    if (c1cs) {
        // 0x801ED0A8: mtc1        $zero, $f0
        ctx->f0.u32l = 0;
            goto L_801ED0C8;
    }
    goto skip_0;
    // 0x801ED0A8: mtc1        $zero, $f0
    ctx->f0.u32l = 0;
    skip_0:
    // 0x801ED0AC: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x801ED0B0: nop

    // 0x801ED0B4: c.lt.s      $f6, $f12
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 12);
    c1cs = ctx->f6.fl < ctx->f12.fl;
    // 0x801ED0B8: nop

    // 0x801ED0BC: bc1fl       L_801ED0D4
    if (!c1cs) {
        // 0x801ED0C0: mtc1        $zero, $f8
        ctx->f8.u32l = 0;
            goto L_801ED0D4;
    }
    goto skip_1;
    // 0x801ED0C0: mtc1        $zero, $f8
    ctx->f8.u32l = 0;
    skip_1:
    // 0x801ED0C4: mtc1        $zero, $f0
    ctx->f0.u32l = 0;
L_801ED0C8:
    // 0x801ED0C8: jr          $ra
    // 0x801ED0CC: nop

    return;
    // 0x801ED0CC: nop

    // 0x801ED0D0: mtc1        $zero, $f8
    ctx->f8.u32l = 0;
L_801ED0D4:
    // 0x801ED0D4: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801ED0D8: c.le.s      $f8, $f12
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 12);
    c1cs = ctx->f8.fl <= ctx->f12.fl;
    // 0x801ED0DC: nop

    // 0x801ED0E0: bc1f        L_801ED114
    if (!c1cs) {
        // 0x801ED0E4: nop
    
            goto L_801ED114;
    }
    // 0x801ED0E4: nop

    // 0x801ED0E8: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801ED0EC: lwc1        $f10, 0x7710($at)
    ctx->f10.u32l = MEM_W(ctx->r1, 0X7710);
    // 0x801ED0F0: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801ED0F4: mul.s       $f16, $f12, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f16.fl = MUL_S(ctx->f12.fl, ctx->f10.fl);
    // 0x801ED0F8: trunc.w.s   $f18, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    ctx->f18.u32l = TRUNC_W_S(ctx->f16.fl);
    // 0x801ED0FC: mfc1        $t7, $f18
    ctx->r15 = (int32_t)ctx->f18.u32l;
    // 0x801ED100: nop

    // 0x801ED104: sll         $t8, $t7, 2
    ctx->r24 = S32(ctx->r15 << 2);
    // 0x801ED108: addu        $at, $at, $t8
    ctx->r1 = ADD32(ctx->r1, ctx->r24);
    // 0x801ED10C: jr          $ra
    // 0x801ED110: lwc1        $f0, 0x6F08($at)
    ctx->f0.u32l = MEM_W(ctx->r1, 0X6F08);
    return;
    // 0x801ED110: lwc1        $f0, 0x6F08($at)
    ctx->f0.u32l = MEM_W(ctx->r1, 0X6F08);
L_801ED114:
    // 0x801ED114: lwc1        $f6, 0x7714($at)
    ctx->f6.u32l = MEM_W(ctx->r1, 0X7714);
    // 0x801ED118: neg.s       $f4, $f12
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f12.fl); 
    ctx->f4.fl = -ctx->f12.fl;
    // 0x801ED11C: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801ED120: mul.s       $f8, $f4, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = MUL_S(ctx->f4.fl, ctx->f6.fl);
    // 0x801ED124: trunc.w.s   $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.u32l = TRUNC_W_S(ctx->f8.fl);
    // 0x801ED128: mfc1        $t0, $f10
    ctx->r8 = (int32_t)ctx->f10.u32l;
    // 0x801ED12C: nop

    // 0x801ED130: sll         $t1, $t0, 2
    ctx->r9 = S32(ctx->r8 << 2);
    // 0x801ED134: addu        $at, $at, $t1
    ctx->r1 = ADD32(ctx->r1, ctx->r9);
    // 0x801ED138: lwc1        $f16, 0x6F08($at)
    ctx->f16.u32l = MEM_W(ctx->r1, 0X6F08);
    // 0x801ED13C: lui         $at, 0x4334
    ctx->r1 = S32(0X4334 << 16);
    // 0x801ED140: mtc1        $at, $f18
    ctx->f18.u32l = ctx->r1;
    // 0x801ED144: nop

    // 0x801ED148: sub.s       $f0, $f18, $f16
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f0.fl = ctx->f18.fl - ctx->f16.fl;
    // 0x801ED14C: jr          $ra
    // 0x801ED150: nop

    return;
    // 0x801ED150: nop

;}
RECOMP_FUNC void func_801ED154(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801ED154: mtc1        $zero, $f2
    ctx->f2.u32l = 0;
    // 0x801ED158: addiu       $sp, $sp, -0x28
    ctx->r29 = ADD32(ctx->r29, -0X28);
    // 0x801ED15C: sdc1        $f20, 0x10($sp)
    CHECK_FR(ctx, 20);
    SD(ctx->f20.u64, 0X10, ctx->r29);
    // 0x801ED160: c.eq.s      $f14, $f2
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 2);
    c1cs = ctx->f14.fl == ctx->f2.fl;
    // 0x801ED164: mov.s       $f20, $f12
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 12);
    ctx->f20.fl = ctx->f12.fl;
    // 0x801ED168: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x801ED16C: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    // 0x801ED170: bc1f        L_801ED190
    if (!c1cs) {
        // 0x801ED174: or          $v1, $zero, $zero
        ctx->r3 = 0 | 0;
            goto L_801ED190;
    }
    // 0x801ED174: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
    // 0x801ED178: c.eq.s      $f12, $f2
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 2);
    c1cs = ctx->f12.fl == ctx->f2.fl;
    // 0x801ED17C: nop

    // 0x801ED180: bc1fl       L_801ED194
    if (!c1cs) {
        // 0x801ED184: c.lt.s      $f14, $f2
        CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 2);
    c1cs = ctx->f14.fl < ctx->f2.fl;
            goto L_801ED194;
    }
    goto skip_0;
    // 0x801ED184: c.lt.s      $f14, $f2
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 2);
    c1cs = ctx->f14.fl < ctx->f2.fl;
    skip_0:
    // 0x801ED188: b           L_801ED2CC
    // 0x801ED18C: mov.s       $f0, $f2
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    ctx->f0.fl = ctx->f2.fl;
        goto L_801ED2CC;
    // 0x801ED18C: mov.s       $f0, $f2
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    ctx->f0.fl = ctx->f2.fl;
L_801ED190:
    // 0x801ED190: c.lt.s      $f14, $f2
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 2);
    c1cs = ctx->f14.fl < ctx->f2.fl;
L_801ED194:
    // 0x801ED194: nop

    // 0x801ED198: bc1fl       L_801ED1AC
    if (!c1cs) {
        // 0x801ED19C: c.lt.s      $f20, $f2
        CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 2);
    c1cs = ctx->f20.fl < ctx->f2.fl;
            goto L_801ED1AC;
    }
    goto skip_1;
    // 0x801ED19C: c.lt.s      $f20, $f2
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 2);
    c1cs = ctx->f20.fl < ctx->f2.fl;
    skip_1:
    // 0x801ED1A0: neg.s       $f14, $f14
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f14.fl); 
    ctx->f14.fl = -ctx->f14.fl;
    // 0x801ED1A4: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
    // 0x801ED1A8: c.lt.s      $f20, $f2
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 2);
    c1cs = ctx->f20.fl < ctx->f2.fl;
L_801ED1AC:
    // 0x801ED1AC: mul.s       $f4, $f14, $f14
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f4.fl = MUL_S(ctx->f14.fl, ctx->f14.fl);
    // 0x801ED1B0: bc1f        L_801ED1C0
    if (!c1cs) {
        // 0x801ED1B4: nop
    
            goto L_801ED1C0;
    }
    // 0x801ED1B4: nop

    // 0x801ED1B8: neg.s       $f20, $f20
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f20.fl); 
    ctx->f20.fl = -ctx->f20.fl;
    // 0x801ED1BC: addiu       $v1, $zero, 0x1
    ctx->r3 = ADD32(0, 0X1);
L_801ED1C0:
    // 0x801ED1C0: mul.s       $f6, $f20, $f20
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f6.fl = MUL_S(ctx->f20.fl, ctx->f20.fl);
    // 0x801ED1C4: sw          $v0, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r2;
    // 0x801ED1C8: sw          $v1, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r3;
    // 0x801ED1CC: swc1        $f14, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->f14.u32l;
    // 0x801ED1D0: jal         0x800C7010
    // 0x801ED1D4: add.s       $f12, $f4, $f6
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f12.fl = ctx->f4.fl + ctx->f6.fl;
    _nsqrtf(rdram, ctx);
        goto after_0;
    // 0x801ED1D4: add.s       $f12, $f4, $f6
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f12.fl = ctx->f4.fl + ctx->f6.fl;
    after_0:
    // 0x801ED1D8: lwc1        $f14, 0x2C($sp)
    ctx->f14.u32l = MEM_W(ctx->r29, 0X2C);
    // 0x801ED1DC: lw          $v0, 0x24($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X24);
    // 0x801ED1E0: lw          $v1, 0x20($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X20);
    // 0x801ED1E4: c.le.s      $f14, $f20
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 20);
    c1cs = ctx->f14.fl <= ctx->f20.fl;
    // 0x801ED1E8: nop

    // 0x801ED1EC: bc1fl       L_801ED228
    if (!c1cs) {
        // 0x801ED1F0: div.s       $f4, $f20, $f0
        CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f4.fl = DIV_S(ctx->f20.fl, ctx->f0.fl);
            goto L_801ED228;
    }
    goto skip_2;
    // 0x801ED1F0: div.s       $f4, $f20, $f0
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f4.fl = DIV_S(ctx->f20.fl, ctx->f0.fl);
    skip_2:
    // 0x801ED1F4: div.s       $f8, $f14, $f0
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f8.fl = DIV_S(ctx->f14.fl, ctx->f0.fl);
    // 0x801ED1F8: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801ED1FC: lwc1        $f10, 0x7718($at)
    ctx->f10.u32l = MEM_W(ctx->r1, 0X7718);
    // 0x801ED200: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801ED204: mul.s       $f16, $f8, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f16.fl = MUL_S(ctx->f8.fl, ctx->f10.fl);
    // 0x801ED208: trunc.w.s   $f18, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    ctx->f18.u32l = TRUNC_W_S(ctx->f16.fl);
    // 0x801ED20C: mfc1        $t7, $f18
    ctx->r15 = (int32_t)ctx->f18.u32l;
    // 0x801ED210: nop

    // 0x801ED214: sll         $t8, $t7, 2
    ctx->r24 = S32(ctx->r15 << 2);
    // 0x801ED218: addu        $at, $at, $t8
    ctx->r1 = ADD32(ctx->r1, ctx->r24);
    // 0x801ED21C: b           L_801ED260
    // 0x801ED220: lwc1        $f2, 0x6F08($at)
    ctx->f2.u32l = MEM_W(ctx->r1, 0X6F08);
        goto L_801ED260;
    // 0x801ED220: lwc1        $f2, 0x6F08($at)
    ctx->f2.u32l = MEM_W(ctx->r1, 0X6F08);
    // 0x801ED224: div.s       $f4, $f20, $f0
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f4.fl = DIV_S(ctx->f20.fl, ctx->f0.fl);
L_801ED228:
    // 0x801ED228: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801ED22C: lwc1        $f6, 0x771C($at)
    ctx->f6.u32l = MEM_W(ctx->r1, 0X771C);
    // 0x801ED230: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801ED234: mul.s       $f8, $f4, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = MUL_S(ctx->f4.fl, ctx->f6.fl);
    // 0x801ED238: trunc.w.s   $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.u32l = TRUNC_W_S(ctx->f8.fl);
    // 0x801ED23C: mfc1        $t0, $f10
    ctx->r8 = (int32_t)ctx->f10.u32l;
    // 0x801ED240: nop

    // 0x801ED244: sll         $t1, $t0, 2
    ctx->r9 = S32(ctx->r8 << 2);
    // 0x801ED248: addu        $at, $at, $t1
    ctx->r1 = ADD32(ctx->r1, ctx->r9);
    // 0x801ED24C: lwc1        $f16, 0x6F08($at)
    ctx->f16.u32l = MEM_W(ctx->r1, 0X6F08);
    // 0x801ED250: lui         $at, 0x42B4
    ctx->r1 = S32(0X42B4 << 16);
    // 0x801ED254: mtc1        $at, $f18
    ctx->f18.u32l = ctx->r1;
    // 0x801ED258: nop

    // 0x801ED25C: sub.s       $f2, $f18, $f16
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f2.fl = ctx->f18.fl - ctx->f16.fl;
L_801ED260:
    // 0x801ED260: beq         $v0, $zero, L_801ED284
    if (ctx->r2 == 0) {
        // 0x801ED264: nop
    
            goto L_801ED284;
    }
    // 0x801ED264: nop

    // 0x801ED268: bne         $v1, $zero, L_801ED284
    if (ctx->r3 != 0) {
        // 0x801ED26C: lui         $at, 0x8022
        ctx->r1 = S32(0X8022 << 16);
            goto L_801ED284;
    }
    // 0x801ED26C: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801ED270: ldc1        $f4, 0x7720($at)
    CHECK_FR(ctx, 4);
    ctx->f4.u64 = LD(ctx->r1, 0X7720);
    // 0x801ED274: cvt.d.s     $f6, $f2
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f2.fl); 
    ctx->f6.d = CVT_D_S(ctx->f2.fl);
    // 0x801ED278: sub.d       $f8, $f4, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.d); NAN_CHECK(ctx->f6.d); 
    ctx->f8.d = ctx->f4.d - ctx->f6.d;
    // 0x801ED27C: b           L_801ED2C8
    // 0x801ED280: cvt.s.d     $f2, $f8
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f8.d); 
    ctx->f2.fl = CVT_S_D(ctx->f8.d);
        goto L_801ED2C8;
    // 0x801ED280: cvt.s.d     $f2, $f8
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f8.d); 
    ctx->f2.fl = CVT_S_D(ctx->f8.d);
L_801ED284:
    // 0x801ED284: beq         $v0, $zero, L_801ED2A8
    if (ctx->r2 == 0) {
        // 0x801ED288: nop
    
            goto L_801ED2A8;
    }
    // 0x801ED288: nop

    // 0x801ED28C: beq         $v1, $zero, L_801ED2A8
    if (ctx->r3 == 0) {
        // 0x801ED290: lui         $at, 0x8022
        ctx->r1 = S32(0X8022 << 16);
            goto L_801ED2A8;
    }
    // 0x801ED290: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801ED294: ldc1        $f18, 0x7728($at)
    CHECK_FR(ctx, 18);
    ctx->f18.u64 = LD(ctx->r1, 0X7728);
    // 0x801ED298: cvt.d.s     $f10, $f2
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f2.fl); 
    ctx->f10.d = CVT_D_S(ctx->f2.fl);
    // 0x801ED29C: add.d       $f16, $f10, $f18
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f10.d); NAN_CHECK(ctx->f18.d); 
    ctx->f16.d = ctx->f10.d + ctx->f18.d;
    // 0x801ED2A0: b           L_801ED2C8
    // 0x801ED2A4: cvt.s.d     $f2, $f16
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f16.d); 
    ctx->f2.fl = CVT_S_D(ctx->f16.d);
        goto L_801ED2C8;
    // 0x801ED2A4: cvt.s.d     $f2, $f16
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f16.d); 
    ctx->f2.fl = CVT_S_D(ctx->f16.d);
L_801ED2A8:
    // 0x801ED2A8: bnel        $v0, $zero, L_801ED2CC
    if (ctx->r2 != 0) {
        // 0x801ED2AC: mov.s       $f0, $f2
        CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    ctx->f0.fl = ctx->f2.fl;
            goto L_801ED2CC;
    }
    goto skip_3;
    // 0x801ED2AC: mov.s       $f0, $f2
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    ctx->f0.fl = ctx->f2.fl;
    skip_3:
    // 0x801ED2B0: beq         $v1, $zero, L_801ED2C8
    if (ctx->r3 == 0) {
        // 0x801ED2B4: lui         $at, 0x8022
        ctx->r1 = S32(0X8022 << 16);
            goto L_801ED2C8;
    }
    // 0x801ED2B4: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801ED2B8: ldc1        $f4, 0x7730($at)
    CHECK_FR(ctx, 4);
    ctx->f4.u64 = LD(ctx->r1, 0X7730);
    // 0x801ED2BC: cvt.d.s     $f6, $f2
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f2.fl); 
    ctx->f6.d = CVT_D_S(ctx->f2.fl);
    // 0x801ED2C0: sub.d       $f8, $f4, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.d); NAN_CHECK(ctx->f6.d); 
    ctx->f8.d = ctx->f4.d - ctx->f6.d;
    // 0x801ED2C4: cvt.s.d     $f2, $f8
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f8.d); 
    ctx->f2.fl = CVT_S_D(ctx->f8.d);
L_801ED2C8:
    // 0x801ED2C8: mov.s       $f0, $f2
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    ctx->f0.fl = ctx->f2.fl;
L_801ED2CC:
    // 0x801ED2CC: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    // 0x801ED2D0: ldc1        $f20, 0x10($sp)
    CHECK_FR(ctx, 20);
    ctx->f20.u64 = LD(ctx->r29, 0X10);
    // 0x801ED2D4: addiu       $sp, $sp, 0x28
    ctx->r29 = ADD32(ctx->r29, 0X28);
    // 0x801ED2D8: jr          $ra
    // 0x801ED2DC: nop

    return;
    // 0x801ED2DC: nop

;}
RECOMP_FUNC void Math_srand(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801ED2E0: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x801ED2E4: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x801ED2E8: jal         0x800C58F0
    // 0x801ED2EC: nop

    osGetTime_recomp(rdram, ctx);
        goto after_0;
    // 0x801ED2EC: nop

    after_0:
    // 0x801ED2F0: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x801ED2F4: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801ED2F8: sh          $v1, 0x6F00($at)
    MEM_H(0X6F00, ctx->r1) = ctx->r3;
    // 0x801ED2FC: jr          $ra
    // 0x801ED300: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    return;
    // 0x801ED300: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
;}
RECOMP_FUNC void Math_Rand(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801ED304: lui         $a1, 0x8022
    ctx->r5 = S32(0X8022 << 16);
    // 0x801ED308: addiu       $a1, $a1, 0x6F00
    ctx->r5 = ADD32(ctx->r5, 0X6F00);
    // 0x801ED30C: lhu         $v1, 0x0($a1)
    ctx->r3 = MEM_HU(ctx->r5, 0X0);
    // 0x801ED310: sll         $t6, $v1, 2
    ctx->r14 = S32(ctx->r3 << 2);
    // 0x801ED314: addu        $t7, $t6, $v1
    ctx->r15 = ADD32(ctx->r14, ctx->r3);
    // 0x801ED318: addiu       $t8, $t7, 0x1
    ctx->r24 = ADD32(ctx->r15, 0X1);
    // 0x801ED31C: andi        $t9, $t8, 0xFFFF
    ctx->r25 = ctx->r24 & 0XFFFF;
    // 0x801ED320: multu       $t9, $a0
    result = U64(U32(ctx->r25)) * U64(U32(ctx->r4)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x801ED324: sh          $t8, 0x0($a1)
    MEM_H(0X0, ctx->r5) = ctx->r24;
    // 0x801ED328: mflo        $v0
    ctx->r2 = lo;
    // 0x801ED32C: sra         $t0, $v0, 16
    ctx->r8 = S32(SIGNED(ctx->r2) >> 16);
    // 0x801ED330: jr          $ra
    // 0x801ED334: or          $v0, $t0, $zero
    ctx->r2 = ctx->r8 | 0;
    return;
    // 0x801ED334: or          $v0, $t0, $zero
    ctx->r2 = ctx->r8 | 0;
;}
RECOMP_FUNC void Math_FloatRand(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801ED338: lui         $v1, 0x8022
    ctx->r3 = S32(0X8022 << 16);
    // 0x801ED33C: addiu       $v1, $v1, 0x6F00
    ctx->r3 = ADD32(ctx->r3, 0X6F00);
    // 0x801ED340: lhu         $v0, 0x0($v1)
    ctx->r2 = MEM_HU(ctx->r3, 0X0);
    // 0x801ED344: lui         $at, 0x4F80
    ctx->r1 = S32(0X4F80 << 16);
    // 0x801ED348: sll         $t6, $v0, 2
    ctx->r14 = S32(ctx->r2 << 2);
    // 0x801ED34C: addu        $t7, $t6, $v0
    ctx->r15 = ADD32(ctx->r14, ctx->r2);
    // 0x801ED350: addiu       $t8, $t7, 0x1
    ctx->r24 = ADD32(ctx->r15, 0X1);
    // 0x801ED354: andi        $t9, $t8, 0xFFFF
    ctx->r25 = ctx->r24 & 0XFFFF;
    // 0x801ED358: mtc1        $t9, $f4
    ctx->f4.u32l = ctx->r25;
    // 0x801ED35C: sh          $t8, 0x0($v1)
    MEM_H(0X0, ctx->r3) = ctx->r24;
    // 0x801ED360: bgez        $t9, L_801ED374
    if (SIGNED(ctx->r25) >= 0) {
        // 0x801ED364: cvt.s.w     $f6, $f4
        CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
            goto L_801ED374;
    }
    // 0x801ED364: cvt.s.w     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
    // 0x801ED368: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x801ED36C: nop

    // 0x801ED370: add.s       $f6, $f6, $f8
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f6.fl = ctx->f6.fl + ctx->f8.fl;
L_801ED374:
    // 0x801ED374: mul.s       $f10, $f6, $f12
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f10.fl = MUL_S(ctx->f6.fl, ctx->f12.fl);
    // 0x801ED378: lui         $at, 0x4780
    ctx->r1 = S32(0X4780 << 16);
    // 0x801ED37C: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
    // 0x801ED380: jr          $ra
    // 0x801ED384: div.s       $f0, $f10, $f16
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f0.fl = DIV_S(ctx->f10.fl, ctx->f16.fl);
    return;
    // 0x801ED384: div.s       $f0, $f10, $f16
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f0.fl = DIV_S(ctx->f10.fl, ctx->f16.fl);
;}
RECOMP_FUNC void func_801ED388(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801ED388: addiu       $v0, $zero, 0x168
    ctx->r2 = ADD32(0, 0X168);
    // 0x801ED38C: div         $zero, $a0, $v0
    lo = S32(S64(S32(ctx->r4)) / S64(S32(ctx->r2))); hi = S32(S64(S32(ctx->r4)) % S64(S32(ctx->r2)));
    // 0x801ED390: bne         $v0, $zero, L_801ED39C
    if (ctx->r2 != 0) {
        // 0x801ED394: nop
    
            goto L_801ED39C;
    }
    // 0x801ED394: nop

    // 0x801ED398: break       7
    do_break(2149503896);
L_801ED39C:
    // 0x801ED39C: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x801ED3A0: bne         $v0, $at, L_801ED3B4
    if (ctx->r2 != ctx->r1) {
        // 0x801ED3A4: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_801ED3B4;
    }
    // 0x801ED3A4: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x801ED3A8: bne         $a0, $at, L_801ED3B4
    if (ctx->r4 != ctx->r1) {
        // 0x801ED3AC: nop
    
            goto L_801ED3B4;
    }
    // 0x801ED3AC: nop

    // 0x801ED3B0: break       6
    do_break(2149503920);
L_801ED3B4:
    // 0x801ED3B4: mfhi        $a0
    ctx->r4 = hi;
    // 0x801ED3B8: addiu       $v1, $a0, 0x168
    ctx->r3 = ADD32(ctx->r4, 0X168);
    // 0x801ED3BC: bltz        $a0, L_801ED3CC
    if (SIGNED(ctx->r4) < 0) {
        // 0x801ED3C0: nop
    
            goto L_801ED3CC;
    }
    // 0x801ED3C0: nop

    // 0x801ED3C4: b           L_801ED3CC
    // 0x801ED3C8: or          $v1, $a0, $zero
    ctx->r3 = ctx->r4 | 0;
        goto L_801ED3CC;
    // 0x801ED3C8: or          $v1, $a0, $zero
    ctx->r3 = ctx->r4 | 0;
L_801ED3CC:
    // 0x801ED3CC: div         $zero, $a1, $v0
    lo = S32(S64(S32(ctx->r5)) / S64(S32(ctx->r2))); hi = S32(S64(S32(ctx->r5)) % S64(S32(ctx->r2)));
    // 0x801ED3D0: or          $a0, $v1, $zero
    ctx->r4 = ctx->r3 | 0;
    // 0x801ED3D4: bne         $v0, $zero, L_801ED3E0
    if (ctx->r2 != 0) {
        // 0x801ED3D8: nop
    
            goto L_801ED3E0;
    }
    // 0x801ED3D8: nop

    // 0x801ED3DC: break       7
    do_break(2149503964);
L_801ED3E0:
    // 0x801ED3E0: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x801ED3E4: bne         $v0, $at, L_801ED3F8
    if (ctx->r2 != ctx->r1) {
        // 0x801ED3E8: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_801ED3F8;
    }
    // 0x801ED3E8: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x801ED3EC: bne         $a1, $at, L_801ED3F8
    if (ctx->r5 != ctx->r1) {
        // 0x801ED3F0: nop
    
            goto L_801ED3F8;
    }
    // 0x801ED3F0: nop

    // 0x801ED3F4: break       6
    do_break(2149503988);
L_801ED3F8:
    // 0x801ED3F8: mfhi        $a1
    ctx->r5 = hi;
    // 0x801ED3FC: addiu       $v1, $a1, 0x168
    ctx->r3 = ADD32(ctx->r5, 0X168);
    // 0x801ED400: bltz        $a1, L_801ED410
    if (SIGNED(ctx->r5) < 0) {
        // 0x801ED404: nop
    
            goto L_801ED410;
    }
    // 0x801ED404: nop

    // 0x801ED408: b           L_801ED410
    // 0x801ED40C: or          $v1, $a1, $zero
    ctx->r3 = ctx->r5 | 0;
        goto L_801ED410;
    // 0x801ED40C: or          $v1, $a1, $zero
    ctx->r3 = ctx->r5 | 0;
L_801ED410:
    // 0x801ED410: subu        $a0, $a0, $v1
    ctx->r4 = SUB32(ctx->r4, ctx->r3);
    // 0x801ED414: bgezl       $a0, L_801ED424
    if (SIGNED(ctx->r4) >= 0) {
        // 0x801ED418: slti        $at, $a0, 0xB5
        ctx->r1 = SIGNED(ctx->r4) < 0XB5 ? 1 : 0;
            goto L_801ED424;
    }
    goto skip_0;
    // 0x801ED418: slti        $at, $a0, 0xB5
    ctx->r1 = SIGNED(ctx->r4) < 0XB5 ? 1 : 0;
    skip_0:
    // 0x801ED41C: negu        $a0, $a0
    ctx->r4 = SUB32(0, ctx->r4);
    // 0x801ED420: slti        $at, $a0, 0xB5
    ctx->r1 = SIGNED(ctx->r4) < 0XB5 ? 1 : 0;
L_801ED424:
    // 0x801ED424: beq         $at, $zero, L_801ED434
    if (ctx->r1 == 0) {
        // 0x801ED428: subu        $v1, $v0, $a0
        ctx->r3 = SUB32(ctx->r2, ctx->r4);
            goto L_801ED434;
    }
    // 0x801ED428: subu        $v1, $v0, $a0
    ctx->r3 = SUB32(ctx->r2, ctx->r4);
    // 0x801ED42C: jr          $ra
    // 0x801ED430: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    return;
    // 0x801ED430: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
L_801ED434:
    // 0x801ED434: jr          $ra
    // 0x801ED438: or          $v0, $v1, $zero
    ctx->r2 = ctx->r3 | 0;
    return;
    // 0x801ED438: or          $v0, $v1, $zero
    ctx->r2 = ctx->r3 | 0;
;}
RECOMP_FUNC void func_801ED43C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801ED43C: addiu       $v0, $zero, 0x168
    ctx->r2 = ADD32(0, 0X168);
    // 0x801ED440: div         $zero, $a0, $v0
    lo = S32(S64(S32(ctx->r4)) / S64(S32(ctx->r2))); hi = S32(S64(S32(ctx->r4)) % S64(S32(ctx->r2)));
    // 0x801ED444: bne         $v0, $zero, L_801ED450
    if (ctx->r2 != 0) {
        // 0x801ED448: nop
    
            goto L_801ED450;
    }
    // 0x801ED448: nop

    // 0x801ED44C: break       7
    do_break(2149504076);
L_801ED450:
    // 0x801ED450: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x801ED454: bne         $v0, $at, L_801ED468
    if (ctx->r2 != ctx->r1) {
        // 0x801ED458: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_801ED468;
    }
    // 0x801ED458: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x801ED45C: bne         $a0, $at, L_801ED468
    if (ctx->r4 != ctx->r1) {
        // 0x801ED460: nop
    
            goto L_801ED468;
    }
    // 0x801ED460: nop

    // 0x801ED464: break       6
    do_break(2149504100);
L_801ED468:
    // 0x801ED468: mfhi        $a0
    ctx->r4 = hi;
    // 0x801ED46C: addiu       $v1, $a0, 0x168
    ctx->r3 = ADD32(ctx->r4, 0X168);
    // 0x801ED470: bltz        $a0, L_801ED480
    if (SIGNED(ctx->r4) < 0) {
        // 0x801ED474: nop
    
            goto L_801ED480;
    }
    // 0x801ED474: nop

    // 0x801ED478: b           L_801ED480
    // 0x801ED47C: or          $v1, $a0, $zero
    ctx->r3 = ctx->r4 | 0;
        goto L_801ED480;
    // 0x801ED47C: or          $v1, $a0, $zero
    ctx->r3 = ctx->r4 | 0;
L_801ED480:
    // 0x801ED480: div         $zero, $a1, $v0
    lo = S32(S64(S32(ctx->r5)) / S64(S32(ctx->r2))); hi = S32(S64(S32(ctx->r5)) % S64(S32(ctx->r2)));
    // 0x801ED484: or          $a0, $v1, $zero
    ctx->r4 = ctx->r3 | 0;
    // 0x801ED488: bne         $v0, $zero, L_801ED494
    if (ctx->r2 != 0) {
        // 0x801ED48C: nop
    
            goto L_801ED494;
    }
    // 0x801ED48C: nop

    // 0x801ED490: break       7
    do_break(2149504144);
L_801ED494:
    // 0x801ED494: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x801ED498: bne         $v0, $at, L_801ED4AC
    if (ctx->r2 != ctx->r1) {
        // 0x801ED49C: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_801ED4AC;
    }
    // 0x801ED49C: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x801ED4A0: bne         $a1, $at, L_801ED4AC
    if (ctx->r5 != ctx->r1) {
        // 0x801ED4A4: nop
    
            goto L_801ED4AC;
    }
    // 0x801ED4A4: nop

    // 0x801ED4A8: break       6
    do_break(2149504168);
L_801ED4AC:
    // 0x801ED4AC: mfhi        $a1
    ctx->r5 = hi;
    // 0x801ED4B0: addiu       $v1, $a1, 0x168
    ctx->r3 = ADD32(ctx->r5, 0X168);
    // 0x801ED4B4: bltz        $a1, L_801ED4C4
    if (SIGNED(ctx->r5) < 0) {
        // 0x801ED4B8: nop
    
            goto L_801ED4C4;
    }
    // 0x801ED4B8: nop

    // 0x801ED4BC: b           L_801ED4C4
    // 0x801ED4C0: or          $v1, $a1, $zero
    ctx->r3 = ctx->r5 | 0;
        goto L_801ED4C4;
    // 0x801ED4C0: or          $v1, $a1, $zero
    ctx->r3 = ctx->r5 | 0;
L_801ED4C4:
    // 0x801ED4C4: subu        $a0, $a0, $v1
    ctx->r4 = SUB32(ctx->r4, ctx->r3);
    // 0x801ED4C8: bltz        $a0, L_801ED4D8
    if (SIGNED(ctx->r4) < 0) {
        // 0x801ED4CC: addiu       $v1, $a0, 0x168
        ctx->r3 = ADD32(ctx->r4, 0X168);
            goto L_801ED4D8;
    }
    // 0x801ED4CC: addiu       $v1, $a0, 0x168
    ctx->r3 = ADD32(ctx->r4, 0X168);
    // 0x801ED4D0: jr          $ra
    // 0x801ED4D4: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    return;
    // 0x801ED4D4: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
L_801ED4D8:
    // 0x801ED4D8: jr          $ra
    // 0x801ED4DC: or          $v0, $v1, $zero
    ctx->r2 = ctx->r3 | 0;
    return;
    // 0x801ED4DC: or          $v0, $v1, $zero
    ctx->r2 = ctx->r3 | 0;
;}
RECOMP_FUNC void func_801ED4E0(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801ED4E0: addiu       $v0, $zero, 0x168
    ctx->r2 = ADD32(0, 0X168);
    // 0x801ED4E4: div         $zero, $a0, $v0
    lo = S32(S64(S32(ctx->r4)) / S64(S32(ctx->r2))); hi = S32(S64(S32(ctx->r4)) % S64(S32(ctx->r2)));
    // 0x801ED4E8: bne         $v0, $zero, L_801ED4F4
    if (ctx->r2 != 0) {
        // 0x801ED4EC: nop
    
            goto L_801ED4F4;
    }
    // 0x801ED4EC: nop

    // 0x801ED4F0: break       7
    do_break(2149504240);
L_801ED4F4:
    // 0x801ED4F4: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x801ED4F8: bne         $v0, $at, L_801ED50C
    if (ctx->r2 != ctx->r1) {
        // 0x801ED4FC: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_801ED50C;
    }
    // 0x801ED4FC: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x801ED500: bne         $a0, $at, L_801ED50C
    if (ctx->r4 != ctx->r1) {
        // 0x801ED504: nop
    
            goto L_801ED50C;
    }
    // 0x801ED504: nop

    // 0x801ED508: break       6
    do_break(2149504264);
L_801ED50C:
    // 0x801ED50C: mfhi        $a0
    ctx->r4 = hi;
    // 0x801ED510: addiu       $v1, $a0, 0x168
    ctx->r3 = ADD32(ctx->r4, 0X168);
    // 0x801ED514: bltz        $a0, L_801ED524
    if (SIGNED(ctx->r4) < 0) {
        // 0x801ED518: nop
    
            goto L_801ED524;
    }
    // 0x801ED518: nop

    // 0x801ED51C: b           L_801ED524
    // 0x801ED520: or          $v1, $a0, $zero
    ctx->r3 = ctx->r4 | 0;
        goto L_801ED524;
    // 0x801ED520: or          $v1, $a0, $zero
    ctx->r3 = ctx->r4 | 0;
L_801ED524:
    // 0x801ED524: div         $zero, $a1, $v0
    lo = S32(S64(S32(ctx->r5)) / S64(S32(ctx->r2))); hi = S32(S64(S32(ctx->r5)) % S64(S32(ctx->r2)));
    // 0x801ED528: or          $a0, $v1, $zero
    ctx->r4 = ctx->r3 | 0;
    // 0x801ED52C: bne         $v0, $zero, L_801ED538
    if (ctx->r2 != 0) {
        // 0x801ED530: nop
    
            goto L_801ED538;
    }
    // 0x801ED530: nop

    // 0x801ED534: break       7
    do_break(2149504308);
L_801ED538:
    // 0x801ED538: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x801ED53C: bne         $v0, $at, L_801ED550
    if (ctx->r2 != ctx->r1) {
        // 0x801ED540: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_801ED550;
    }
    // 0x801ED540: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x801ED544: bne         $a1, $at, L_801ED550
    if (ctx->r5 != ctx->r1) {
        // 0x801ED548: nop
    
            goto L_801ED550;
    }
    // 0x801ED548: nop

    // 0x801ED54C: break       6
    do_break(2149504332);
L_801ED550:
    // 0x801ED550: mfhi        $a1
    ctx->r5 = hi;
    // 0x801ED554: addiu       $v1, $a1, 0x168
    ctx->r3 = ADD32(ctx->r5, 0X168);
    // 0x801ED558: bltz        $a1, L_801ED568
    if (SIGNED(ctx->r5) < 0) {
        // 0x801ED55C: nop
    
            goto L_801ED568;
    }
    // 0x801ED55C: nop

    // 0x801ED560: b           L_801ED568
    // 0x801ED564: or          $v1, $a1, $zero
    ctx->r3 = ctx->r5 | 0;
        goto L_801ED568;
    // 0x801ED564: or          $v1, $a1, $zero
    ctx->r3 = ctx->r5 | 0;
L_801ED568:
    // 0x801ED568: bnel        $a0, $v1, L_801ED57C
    if (ctx->r4 != ctx->r3) {
        // 0x801ED56C: subu        $a0, $a0, $v1
        ctx->r4 = SUB32(ctx->r4, ctx->r3);
            goto L_801ED57C;
    }
    goto skip_0;
    // 0x801ED56C: subu        $a0, $a0, $v1
    ctx->r4 = SUB32(ctx->r4, ctx->r3);
    skip_0:
    // 0x801ED570: jr          $ra
    // 0x801ED574: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    return;
    // 0x801ED574: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    // 0x801ED578: subu        $a0, $a0, $v1
    ctx->r4 = SUB32(ctx->r4, ctx->r3);
L_801ED57C:
    // 0x801ED57C: bgez        $a0, L_801ED588
    if (SIGNED(ctx->r4) >= 0) {
        // 0x801ED580: addiu       $v1, $zero, -0x1
        ctx->r3 = ADD32(0, -0X1);
            goto L_801ED588;
    }
    // 0x801ED580: addiu       $v1, $zero, -0x1
    ctx->r3 = ADD32(0, -0X1);
    // 0x801ED584: addiu       $a0, $a0, 0x168
    ctx->r4 = ADD32(ctx->r4, 0X168);
L_801ED588:
    // 0x801ED588: slti        $at, $a0, 0xB4
    ctx->r1 = SIGNED(ctx->r4) < 0XB4 ? 1 : 0;
    // 0x801ED58C: beq         $at, $zero, L_801ED59C
    if (ctx->r1 == 0) {
        // 0x801ED590: nop
    
            goto L_801ED59C;
    }
    // 0x801ED590: nop

    // 0x801ED594: b           L_801ED59C
    // 0x801ED598: addiu       $v1, $zero, 0x1
    ctx->r3 = ADD32(0, 0X1);
        goto L_801ED59C;
    // 0x801ED598: addiu       $v1, $zero, 0x1
    ctx->r3 = ADD32(0, 0X1);
L_801ED59C:
    // 0x801ED59C: or          $v0, $v1, $zero
    ctx->r2 = ctx->r3 | 0;
    // 0x801ED5A0: jr          $ra
    // 0x801ED5A4: nop

    return;
    // 0x801ED5A4: nop

;}
RECOMP_FUNC void func_801ED5A8(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801ED5A8: addiu       $at, $zero, 0x168
    ctx->r1 = ADD32(0, 0X168);
    // 0x801ED5AC: div         $zero, $a0, $at
    lo = S32(S64(S32(ctx->r4)) / S64(S32(ctx->r1))); hi = S32(S64(S32(ctx->r4)) % S64(S32(ctx->r1)));
    // 0x801ED5B0: mfhi        $t6
    ctx->r14 = hi;
    // 0x801ED5B4: or          $a0, $t6, $zero
    ctx->r4 = ctx->r14 | 0;
    // 0x801ED5B8: bltz        $t6, L_801ED5C8
    if (SIGNED(ctx->r14) < 0) {
        // 0x801ED5BC: addiu       $v0, $a0, 0x168
        ctx->r2 = ADD32(ctx->r4, 0X168);
            goto L_801ED5C8;
    }
    // 0x801ED5BC: addiu       $v0, $a0, 0x168
    ctx->r2 = ADD32(ctx->r4, 0X168);
    // 0x801ED5C0: b           L_801ED5C8
    // 0x801ED5C4: or          $v0, $t6, $zero
    ctx->r2 = ctx->r14 | 0;
        goto L_801ED5C8;
    // 0x801ED5C4: or          $v0, $t6, $zero
    ctx->r2 = ctx->r14 | 0;
L_801ED5C8:
    // 0x801ED5C8: slti        $at, $v0, 0x10F
    ctx->r1 = SIGNED(ctx->r2) < 0X10F ? 1 : 0;
    // 0x801ED5CC: bne         $at, $zero, L_801ED5E0
    if (ctx->r1 != 0) {
        // 0x801ED5D0: or          $a0, $v0, $zero
        ctx->r4 = ctx->r2 | 0;
            goto L_801ED5E0;
    }
    // 0x801ED5D0: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x801ED5D4: addiu       $a0, $v0, -0x168
    ctx->r4 = ADD32(ctx->r2, -0X168);
    // 0x801ED5D8: jr          $ra
    // 0x801ED5DC: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    return;
    // 0x801ED5DC: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
L_801ED5E0:
    // 0x801ED5E0: slti        $at, $v0, 0x5B
    ctx->r1 = SIGNED(ctx->r2) < 0X5B ? 1 : 0;
    // 0x801ED5E4: bne         $at, $zero, L_801ED5F0
    if (ctx->r1 != 0) {
        // 0x801ED5E8: addiu       $t7, $zero, 0xB4
        ctx->r15 = ADD32(0, 0XB4);
            goto L_801ED5F0;
    }
    // 0x801ED5E8: addiu       $t7, $zero, 0xB4
    ctx->r15 = ADD32(0, 0XB4);
    // 0x801ED5EC: subu        $a0, $t7, $v0
    ctx->r4 = SUB32(ctx->r15, ctx->r2);
L_801ED5F0:
    // 0x801ED5F0: jr          $ra
    // 0x801ED5F4: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    return;
    // 0x801ED5F4: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
;}
RECOMP_FUNC void func_801ED5F8(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801ED5F8: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x801ED5FC: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x801ED600: jal         0x801ED5A8
    // 0x801ED604: sw          $a1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r5;
    func_801ED5A8(rdram, ctx);
        goto after_0;
    // 0x801ED604: sw          $a1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r5;
    after_0:
    // 0x801ED608: lw          $a0, 0x1C($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X1C);
    // 0x801ED60C: jal         0x801ED5A8
    // 0x801ED610: sw          $v0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r2;
    func_801ED5A8(rdram, ctx);
        goto after_1;
    // 0x801ED610: sw          $v0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r2;
    after_1:
    // 0x801ED614: lw          $a2, 0x18($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X18);
    // 0x801ED618: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x801ED61C: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x801ED620: subu        $a2, $a2, $v0
    ctx->r6 = SUB32(ctx->r6, ctx->r2);
    // 0x801ED624: bltz        $a2, L_801ED634
    if (SIGNED(ctx->r6) < 0) {
        // 0x801ED628: negu        $v1, $a2
        ctx->r3 = SUB32(0, ctx->r6);
            goto L_801ED634;
    }
    // 0x801ED628: negu        $v1, $a2
    ctx->r3 = SUB32(0, ctx->r6);
    // 0x801ED62C: b           L_801ED634
    // 0x801ED630: or          $v1, $a2, $zero
    ctx->r3 = ctx->r6 | 0;
        goto L_801ED634;
    // 0x801ED630: or          $v1, $a2, $zero
    ctx->r3 = ctx->r6 | 0;
L_801ED634:
    // 0x801ED634: jr          $ra
    // 0x801ED638: or          $v0, $v1, $zero
    ctx->r2 = ctx->r3 | 0;
    return;
    // 0x801ED638: or          $v0, $v1, $zero
    ctx->r2 = ctx->r3 | 0;
;}
RECOMP_FUNC void func_801ED63C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801ED63C: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x801ED640: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x801ED644: jal         0x801ED5A8
    // 0x801ED648: sw          $a1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r5;
    func_801ED5A8(rdram, ctx);
        goto after_0;
    // 0x801ED648: sw          $a1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r5;
    after_0:
    // 0x801ED64C: lw          $a0, 0x1C($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X1C);
    // 0x801ED650: jal         0x801ED5A8
    // 0x801ED654: sw          $v0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r2;
    func_801ED5A8(rdram, ctx);
        goto after_1;
    // 0x801ED654: sw          $v0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r2;
    after_1:
    // 0x801ED658: lw          $a2, 0x18($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X18);
    // 0x801ED65C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x801ED660: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x801ED664: subu        $a2, $a2, $v0
    ctx->r6 = SUB32(ctx->r6, ctx->r2);
    // 0x801ED668: bne         $a2, $zero, L_801ED678
    if (ctx->r6 != 0) {
        // 0x801ED66C: nop
    
            goto L_801ED678;
    }
    // 0x801ED66C: nop

    // 0x801ED670: b           L_801ED68C
    // 0x801ED674: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
        goto L_801ED68C;
    // 0x801ED674: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
L_801ED678:
    // 0x801ED678: blez        $a2, L_801ED688
    if (SIGNED(ctx->r6) <= 0) {
        // 0x801ED67C: addiu       $v0, $zero, -0x1
        ctx->r2 = ADD32(0, -0X1);
            goto L_801ED688;
    }
    // 0x801ED67C: addiu       $v0, $zero, -0x1
    ctx->r2 = ADD32(0, -0X1);
    // 0x801ED680: b           L_801ED688
    // 0x801ED684: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
        goto L_801ED688;
    // 0x801ED684: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
L_801ED688:
    // 0x801ED688: or          $v1, $v0, $zero
    ctx->r3 = ctx->r2 | 0;
L_801ED68C:
    // 0x801ED68C: jr          $ra
    // 0x801ED690: or          $v0, $v1, $zero
    ctx->r2 = ctx->r3 | 0;
    return;
    // 0x801ED690: or          $v0, $v1, $zero
    ctx->r2 = ctx->r3 | 0;
;}
RECOMP_FUNC void func_801ED694(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801ED694: lui         $at, 0x43B4
    ctx->r1 = S32(0X43B4 << 16);
    // 0x801ED698: mtc1        $at, $f0
    ctx->f0.u32l = ctx->r1;
    // 0x801ED69C: mtc1        $zero, $f16
    ctx->f16.u32l = 0;
    // 0x801ED6A0: div.s       $f4, $f12, $f0
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f4.fl = DIV_S(ctx->f12.fl, ctx->f0.fl);
    // 0x801ED6A4: trunc.w.s   $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.u32l = TRUNC_W_S(ctx->f4.fl);
    // 0x801ED6A8: mfc1        $t7, $f6
    ctx->r15 = (int32_t)ctx->f6.u32l;
    // 0x801ED6AC: nop

    // 0x801ED6B0: sll         $t8, $t7, 2
    ctx->r24 = S32(ctx->r15 << 2);
    // 0x801ED6B4: subu        $t8, $t8, $t7
    ctx->r24 = SUB32(ctx->r24, ctx->r15);
    // 0x801ED6B8: sll         $t8, $t8, 2
    ctx->r24 = S32(ctx->r24 << 2);
    // 0x801ED6BC: subu        $t8, $t8, $t7
    ctx->r24 = SUB32(ctx->r24, ctx->r15);
    // 0x801ED6C0: sll         $t8, $t8, 2
    ctx->r24 = S32(ctx->r24 << 2);
    // 0x801ED6C4: addu        $t8, $t8, $t7
    ctx->r24 = ADD32(ctx->r24, ctx->r15);
    // 0x801ED6C8: sll         $t8, $t8, 3
    ctx->r24 = S32(ctx->r24 << 3);
    // 0x801ED6CC: mtc1        $t8, $f8
    ctx->f8.u32l = ctx->r24;
    // 0x801ED6D0: nop

    // 0x801ED6D4: cvt.s.w     $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.fl = CVT_S_W(ctx->f8.u32l);
    // 0x801ED6D8: sub.s       $f12, $f12, $f10
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f12.fl = ctx->f12.fl - ctx->f10.fl;
    // 0x801ED6DC: c.le.s      $f16, $f12
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 12);
    c1cs = ctx->f16.fl <= ctx->f12.fl;
    // 0x801ED6E0: nop

    // 0x801ED6E4: bc1fl       L_801ED6FC
    if (!c1cs) {
        // 0x801ED6E8: add.s       $f2, $f12, $f0
        CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f2.fl = ctx->f12.fl + ctx->f0.fl;
            goto L_801ED6FC;
    }
    goto skip_0;
    // 0x801ED6E8: add.s       $f2, $f12, $f0
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f2.fl = ctx->f12.fl + ctx->f0.fl;
    skip_0:
    // 0x801ED6EC: mov.s       $f2, $f12
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 12);
    ctx->f2.fl = ctx->f12.fl;
    // 0x801ED6F0: jr          $ra
    // 0x801ED6F4: mov.s       $f0, $f12
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 12);
    ctx->f0.fl = ctx->f12.fl;
    return;
    // 0x801ED6F4: mov.s       $f0, $f12
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 12);
    ctx->f0.fl = ctx->f12.fl;
    // 0x801ED6F8: add.s       $f2, $f12, $f0
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f2.fl = ctx->f12.fl + ctx->f0.fl;
L_801ED6FC:
    // 0x801ED6FC: jr          $ra
    // 0x801ED700: mov.s       $f0, $f2
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    ctx->f0.fl = ctx->f2.fl;
    return;
    // 0x801ED700: mov.s       $f0, $f2
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    ctx->f0.fl = ctx->f2.fl;
;}
RECOMP_FUNC void func_801ED704(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801ED704: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x801ED708: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x801ED70C: sdc1        $f20, 0x10($sp)
    CHECK_FR(ctx, 20);
    SD(ctx->f20.u64, 0X10, ctx->r29);
    // 0x801ED710: jal         0x801ED694
    // 0x801ED714: swc1        $f14, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->f14.u32l;
    func_801ED694(rdram, ctx);
        goto after_0;
    // 0x801ED714: swc1        $f14, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->f14.u32l;
    after_0:
    // 0x801ED718: mov.s       $f20, $f0
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 0);
    ctx->f20.fl = ctx->f0.fl;
    // 0x801ED71C: jal         0x801ED694
    // 0x801ED720: lwc1        $f12, 0x24($sp)
    ctx->f12.u32l = MEM_W(ctx->r29, 0X24);
    func_801ED694(rdram, ctx);
        goto after_1;
    // 0x801ED720: lwc1        $f12, 0x24($sp)
    ctx->f12.u32l = MEM_W(ctx->r29, 0X24);
    after_1:
    // 0x801ED724: sub.s       $f20, $f20, $f0
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f20.fl = ctx->f20.fl - ctx->f0.fl;
    // 0x801ED728: mtc1        $zero, $f4
    ctx->f4.u32l = 0;
    // 0x801ED72C: lui         $at, 0x4334
    ctx->r1 = S32(0X4334 << 16);
    // 0x801ED730: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x801ED734: c.le.s      $f4, $f20
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 20);
    c1cs = ctx->f4.fl <= ctx->f20.fl;
    // 0x801ED738: lui         $at, 0x43B4
    ctx->r1 = S32(0X43B4 << 16);
    // 0x801ED73C: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    // 0x801ED740: bc1tl       L_801ED750
    if (c1cs) {
        // 0x801ED744: c.le.s      $f20, $f6
        CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 6);
    c1cs = ctx->f20.fl <= ctx->f6.fl;
            goto L_801ED750;
    }
    goto skip_0;
    // 0x801ED744: c.le.s      $f20, $f6
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 6);
    c1cs = ctx->f20.fl <= ctx->f6.fl;
    skip_0:
    // 0x801ED748: neg.s       $f20, $f20
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f20.fl); 
    ctx->f20.fl = -ctx->f20.fl;
    // 0x801ED74C: c.le.s      $f20, $f6
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 6);
    c1cs = ctx->f20.fl <= ctx->f6.fl;
L_801ED750:
    // 0x801ED750: nop

    // 0x801ED754: bc1fl       L_801ED768
    if (!c1cs) {
        // 0x801ED758: mtc1        $at, $f8
        ctx->f8.u32l = ctx->r1;
            goto L_801ED768;
    }
    goto skip_1;
    // 0x801ED758: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    skip_1:
    // 0x801ED75C: b           L_801ED770
    // 0x801ED760: mov.s       $f2, $f20
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 20);
    ctx->f2.fl = ctx->f20.fl;
        goto L_801ED770;
    // 0x801ED760: mov.s       $f2, $f20
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 20);
    ctx->f2.fl = ctx->f20.fl;
    // 0x801ED764: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
L_801ED768:
    // 0x801ED768: nop

    // 0x801ED76C: sub.s       $f2, $f8, $f20
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f2.fl = ctx->f8.fl - ctx->f20.fl;
L_801ED770:
    // 0x801ED770: ldc1        $f20, 0x10($sp)
    CHECK_FR(ctx, 20);
    ctx->f20.u64 = LD(ctx->r29, 0X10);
    // 0x801ED774: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x801ED778: jr          $ra
    // 0x801ED77C: mov.s       $f0, $f2
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    ctx->f0.fl = ctx->f2.fl;
    return;
    // 0x801ED77C: mov.s       $f0, $f2
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    ctx->f0.fl = ctx->f2.fl;
;}
RECOMP_FUNC void func_801ED780(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801ED780: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x801ED784: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x801ED788: sdc1        $f20, 0x10($sp)
    CHECK_FR(ctx, 20);
    SD(ctx->f20.u64, 0X10, ctx->r29);
    // 0x801ED78C: jal         0x801ED694
    // 0x801ED790: swc1        $f14, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->f14.u32l;
    func_801ED694(rdram, ctx);
        goto after_0;
    // 0x801ED790: swc1        $f14, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->f14.u32l;
    after_0:
    // 0x801ED794: mov.s       $f20, $f0
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 0);
    ctx->f20.fl = ctx->f0.fl;
    // 0x801ED798: jal         0x801ED694
    // 0x801ED79C: lwc1        $f12, 0x24($sp)
    ctx->f12.u32l = MEM_W(ctx->r29, 0X24);
    func_801ED694(rdram, ctx);
        goto after_1;
    // 0x801ED79C: lwc1        $f12, 0x24($sp)
    ctx->f12.u32l = MEM_W(ctx->r29, 0X24);
    after_1:
    // 0x801ED7A0: sub.s       $f20, $f20, $f0
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f20.fl = ctx->f20.fl - ctx->f0.fl;
    // 0x801ED7A4: mtc1        $zero, $f4
    ctx->f4.u32l = 0;
    // 0x801ED7A8: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    // 0x801ED7AC: lui         $at, 0x43B4
    ctx->r1 = S32(0X43B4 << 16);
    // 0x801ED7B0: c.le.s      $f4, $f20
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 20);
    c1cs = ctx->f4.fl <= ctx->f20.fl;
    // 0x801ED7B4: nop

    // 0x801ED7B8: bc1fl       L_801ED7CC
    if (!c1cs) {
        // 0x801ED7BC: mtc1        $at, $f6
        ctx->f6.u32l = ctx->r1;
            goto L_801ED7CC;
    }
    goto skip_0;
    // 0x801ED7BC: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    skip_0:
    // 0x801ED7C0: b           L_801ED7D4
    // 0x801ED7C4: mov.s       $f2, $f20
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 20);
    ctx->f2.fl = ctx->f20.fl;
        goto L_801ED7D4;
    // 0x801ED7C4: mov.s       $f2, $f20
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 20);
    ctx->f2.fl = ctx->f20.fl;
    // 0x801ED7C8: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
L_801ED7CC:
    // 0x801ED7CC: nop

    // 0x801ED7D0: add.s       $f2, $f20, $f6
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f2.fl = ctx->f20.fl + ctx->f6.fl;
L_801ED7D4:
    // 0x801ED7D4: ldc1        $f20, 0x10($sp)
    CHECK_FR(ctx, 20);
    ctx->f20.u64 = LD(ctx->r29, 0X10);
    // 0x801ED7D8: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x801ED7DC: jr          $ra
    // 0x801ED7E0: mov.s       $f0, $f2
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    ctx->f0.fl = ctx->f2.fl;
    return;
    // 0x801ED7E0: mov.s       $f0, $f2
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    ctx->f0.fl = ctx->f2.fl;
;}
RECOMP_FUNC void func_801ED7E4(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801ED7E4: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x801ED7E8: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x801ED7EC: sdc1        $f20, 0x10($sp)
    CHECK_FR(ctx, 20);
    SD(ctx->f20.u64, 0X10, ctx->r29);
    // 0x801ED7F0: jal         0x801ED694
    // 0x801ED7F4: swc1        $f14, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->f14.u32l;
    func_801ED694(rdram, ctx);
        goto after_0;
    // 0x801ED7F4: swc1        $f14, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->f14.u32l;
    after_0:
    // 0x801ED7F8: mov.s       $f20, $f0
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 0);
    ctx->f20.fl = ctx->f0.fl;
    // 0x801ED7FC: jal         0x801ED694
    // 0x801ED800: lwc1        $f12, 0x24($sp)
    ctx->f12.u32l = MEM_W(ctx->r29, 0X24);
    func_801ED694(rdram, ctx);
        goto after_1;
    // 0x801ED800: lwc1        $f12, 0x24($sp)
    ctx->f12.u32l = MEM_W(ctx->r29, 0X24);
    after_1:
    // 0x801ED804: c.eq.s      $f20, $f0
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 0);
    c1cs = ctx->f20.fl == ctx->f0.fl;
    // 0x801ED808: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    // 0x801ED80C: bc1fl       L_801ED820
    if (!c1cs) {
        // 0x801ED810: sub.s       $f20, $f20, $f0
        CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f20.fl = ctx->f20.fl - ctx->f0.fl;
            goto L_801ED820;
    }
    goto skip_0;
    // 0x801ED810: sub.s       $f20, $f20, $f0
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f20.fl = ctx->f20.fl - ctx->f0.fl;
    skip_0:
    // 0x801ED814: b           L_801ED870
    // 0x801ED818: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
        goto L_801ED870;
    // 0x801ED818: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    // 0x801ED81C: sub.s       $f20, $f20, $f0
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f20.fl = ctx->f20.fl - ctx->f0.fl;
L_801ED820:
    // 0x801ED820: mtc1        $zero, $f4
    ctx->f4.u32l = 0;
    // 0x801ED824: lui         $at, 0x43B4
    ctx->r1 = S32(0X43B4 << 16);
    // 0x801ED828: addiu       $v1, $zero, -0x1
    ctx->r3 = ADD32(0, -0X1);
    // 0x801ED82C: c.le.s      $f4, $f20
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 20);
    c1cs = ctx->f4.fl <= ctx->f20.fl;
    // 0x801ED830: nop

    // 0x801ED834: bc1tl       L_801ED84C
    if (c1cs) {
        // 0x801ED838: lui         $at, 0x4334
        ctx->r1 = S32(0X4334 << 16);
            goto L_801ED84C;
    }
    goto skip_1;
    // 0x801ED838: lui         $at, 0x4334
    ctx->r1 = S32(0X4334 << 16);
    skip_1:
    // 0x801ED83C: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x801ED840: nop

    // 0x801ED844: add.s       $f20, $f20, $f6
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f20.fl = ctx->f20.fl + ctx->f6.fl;
    // 0x801ED848: lui         $at, 0x4334
    ctx->r1 = S32(0X4334 << 16);
L_801ED84C:
    // 0x801ED84C: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x801ED850: nop

    // 0x801ED854: c.lt.s      $f20, $f8
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 8);
    c1cs = ctx->f20.fl < ctx->f8.fl;
    // 0x801ED858: nop

    // 0x801ED85C: bc1f        L_801ED86C
    if (!c1cs) {
        // 0x801ED860: nop
    
            goto L_801ED86C;
    }
    // 0x801ED860: nop

    // 0x801ED864: b           L_801ED86C
    // 0x801ED868: addiu       $v1, $zero, 0x1
    ctx->r3 = ADD32(0, 0X1);
        goto L_801ED86C;
    // 0x801ED868: addiu       $v1, $zero, 0x1
    ctx->r3 = ADD32(0, 0X1);
L_801ED86C:
    // 0x801ED86C: or          $v0, $v1, $zero
    ctx->r2 = ctx->r3 | 0;
L_801ED870:
    // 0x801ED870: ldc1        $f20, 0x10($sp)
    CHECK_FR(ctx, 20);
    ctx->f20.u64 = LD(ctx->r29, 0X10);
    // 0x801ED874: jr          $ra
    // 0x801ED878: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    return;
    // 0x801ED878: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
;}
RECOMP_FUNC void func_801ED87C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801ED87C: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x801ED880: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x801ED884: jal         0x801ED694
    // 0x801ED888: nop

    func_801ED694(rdram, ctx);
        goto after_0;
    // 0x801ED888: nop

    after_0:
    // 0x801ED88C: lui         $at, 0x4387
    ctx->r1 = S32(0X4387 << 16);
    // 0x801ED890: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x801ED894: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x801ED898: mov.s       $f12, $f0
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 0);
    ctx->f12.fl = ctx->f0.fl;
    // 0x801ED89C: c.lt.s      $f4, $f0
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    c1cs = ctx->f4.fl < ctx->f0.fl;
    // 0x801ED8A0: lui         $at, 0x42B4
    ctx->r1 = S32(0X42B4 << 16);
    // 0x801ED8A4: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x801ED8A8: bc1fl       L_801ED8C4
    if (!c1cs) {
        // 0x801ED8AC: mtc1        $at, $f8
        ctx->f8.u32l = ctx->r1;
            goto L_801ED8C4;
    }
    goto skip_0;
    // 0x801ED8AC: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    skip_0:
    // 0x801ED8B0: lui         $at, 0x43B4
    ctx->r1 = S32(0X43B4 << 16);
    // 0x801ED8B4: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x801ED8B8: b           L_801ED8E4
    // 0x801ED8BC: sub.s       $f12, $f0, $f6
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f12.fl = ctx->f0.fl - ctx->f6.fl;
        goto L_801ED8E4;
    // 0x801ED8BC: sub.s       $f12, $f0, $f6
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f12.fl = ctx->f0.fl - ctx->f6.fl;
    // 0x801ED8C0: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
L_801ED8C4:
    // 0x801ED8C4: lui         $at, 0x4334
    ctx->r1 = S32(0X4334 << 16);
    // 0x801ED8C8: c.lt.s      $f8, $f0
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 0);
    c1cs = ctx->f8.fl < ctx->f0.fl;
    // 0x801ED8CC: nop

    // 0x801ED8D0: bc1f        L_801ED8E4
    if (!c1cs) {
        // 0x801ED8D4: nop
    
            goto L_801ED8E4;
    }
    // 0x801ED8D4: nop

    // 0x801ED8D8: mtc1        $at, $f10
    ctx->f10.u32l = ctx->r1;
    // 0x801ED8DC: nop

    // 0x801ED8E0: sub.s       $f12, $f10, $f0
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f12.fl = ctx->f10.fl - ctx->f0.fl;
L_801ED8E4:
    // 0x801ED8E4: jr          $ra
    // 0x801ED8E8: mov.s       $f0, $f12
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 12);
    ctx->f0.fl = ctx->f12.fl;
    return;
    // 0x801ED8E8: mov.s       $f0, $f12
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 12);
    ctx->f0.fl = ctx->f12.fl;
;}
RECOMP_FUNC void func_801ED8EC(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801ED8EC: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x801ED8F0: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x801ED8F4: sdc1        $f20, 0x10($sp)
    CHECK_FR(ctx, 20);
    SD(ctx->f20.u64, 0X10, ctx->r29);
    // 0x801ED8F8: jal         0x801ED87C
    // 0x801ED8FC: swc1        $f14, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->f14.u32l;
    func_801ED87C(rdram, ctx);
        goto after_0;
    // 0x801ED8FC: swc1        $f14, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->f14.u32l;
    after_0:
    // 0x801ED900: mov.s       $f20, $f0
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 0);
    ctx->f20.fl = ctx->f0.fl;
    // 0x801ED904: jal         0x801ED87C
    // 0x801ED908: lwc1        $f12, 0x24($sp)
    ctx->f12.u32l = MEM_W(ctx->r29, 0X24);
    func_801ED87C(rdram, ctx);
        goto after_1;
    // 0x801ED908: lwc1        $f12, 0x24($sp)
    ctx->f12.u32l = MEM_W(ctx->r29, 0X24);
    after_1:
    // 0x801ED90C: sub.s       $f20, $f20, $f0
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f20.fl = ctx->f20.fl - ctx->f0.fl;
    // 0x801ED910: mtc1        $zero, $f4
    ctx->f4.u32l = 0;
    // 0x801ED914: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    // 0x801ED918: c.le.s      $f4, $f20
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 20);
    c1cs = ctx->f4.fl <= ctx->f20.fl;
    // 0x801ED91C: nop

    // 0x801ED920: bc1fl       L_801ED934
    if (!c1cs) {
        // 0x801ED924: neg.s       $f2, $f20
        CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f20.fl); 
    ctx->f2.fl = -ctx->f20.fl;
            goto L_801ED934;
    }
    goto skip_0;
    // 0x801ED924: neg.s       $f2, $f20
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f20.fl); 
    ctx->f2.fl = -ctx->f20.fl;
    skip_0:
    // 0x801ED928: b           L_801ED934
    // 0x801ED92C: mov.s       $f2, $f20
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 20);
    ctx->f2.fl = ctx->f20.fl;
        goto L_801ED934;
    // 0x801ED92C: mov.s       $f2, $f20
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 20);
    ctx->f2.fl = ctx->f20.fl;
    // 0x801ED930: neg.s       $f2, $f20
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f20.fl); 
    ctx->f2.fl = -ctx->f20.fl;
L_801ED934:
    // 0x801ED934: ldc1        $f20, 0x10($sp)
    CHECK_FR(ctx, 20);
    ctx->f20.u64 = LD(ctx->r29, 0X10);
    // 0x801ED938: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x801ED93C: jr          $ra
    // 0x801ED940: mov.s       $f0, $f2
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    ctx->f0.fl = ctx->f2.fl;
    return;
    // 0x801ED940: mov.s       $f0, $f2
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    ctx->f0.fl = ctx->f2.fl;
;}
RECOMP_FUNC void func_801ED944(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801ED944: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x801ED948: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x801ED94C: sdc1        $f20, 0x10($sp)
    CHECK_FR(ctx, 20);
    SD(ctx->f20.u64, 0X10, ctx->r29);
    // 0x801ED950: jal         0x801ED87C
    // 0x801ED954: swc1        $f14, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->f14.u32l;
    func_801ED87C(rdram, ctx);
        goto after_0;
    // 0x801ED954: swc1        $f14, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->f14.u32l;
    after_0:
    // 0x801ED958: mov.s       $f20, $f0
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 0);
    ctx->f20.fl = ctx->f0.fl;
    // 0x801ED95C: jal         0x801ED87C
    // 0x801ED960: lwc1        $f12, 0x24($sp)
    ctx->f12.u32l = MEM_W(ctx->r29, 0X24);
    func_801ED87C(rdram, ctx);
        goto after_1;
    // 0x801ED960: lwc1        $f12, 0x24($sp)
    ctx->f12.u32l = MEM_W(ctx->r29, 0X24);
    after_1:
    // 0x801ED964: sub.s       $f20, $f20, $f0
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f20.fl = ctx->f20.fl - ctx->f0.fl;
    // 0x801ED968: mtc1        $zero, $f2
    ctx->f2.u32l = 0;
    // 0x801ED96C: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    // 0x801ED970: c.eq.s      $f20, $f2
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 2);
    c1cs = ctx->f20.fl == ctx->f2.fl;
    // 0x801ED974: nop

    // 0x801ED978: bc1fl       L_801ED98C
    if (!c1cs) {
        // 0x801ED97C: c.lt.s      $f2, $f20
        CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 20);
    c1cs = ctx->f2.fl < ctx->f20.fl;
            goto L_801ED98C;
    }
    goto skip_0;
    // 0x801ED97C: c.lt.s      $f2, $f20
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 20);
    c1cs = ctx->f2.fl < ctx->f20.fl;
    skip_0:
    // 0x801ED980: b           L_801ED9A4
    // 0x801ED984: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
        goto L_801ED9A4;
    // 0x801ED984: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
    // 0x801ED988: c.lt.s      $f2, $f20
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 20);
    c1cs = ctx->f2.fl < ctx->f20.fl;
L_801ED98C:
    // 0x801ED98C: addiu       $v0, $zero, -0x1
    ctx->r2 = ADD32(0, -0X1);
    // 0x801ED990: bc1f        L_801ED9A0
    if (!c1cs) {
        // 0x801ED994: nop
    
            goto L_801ED9A0;
    }
    // 0x801ED994: nop

    // 0x801ED998: b           L_801ED9A0
    // 0x801ED99C: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
        goto L_801ED9A0;
    // 0x801ED99C: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
L_801ED9A0:
    // 0x801ED9A0: or          $v1, $v0, $zero
    ctx->r3 = ctx->r2 | 0;
L_801ED9A4:
    // 0x801ED9A4: ldc1        $f20, 0x10($sp)
    CHECK_FR(ctx, 20);
    ctx->f20.u64 = LD(ctx->r29, 0X10);
    // 0x801ED9A8: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x801ED9AC: jr          $ra
    // 0x801ED9B0: or          $v0, $v1, $zero
    ctx->r2 = ctx->r3 | 0;
    return;
    // 0x801ED9B0: or          $v0, $v1, $zero
    ctx->r2 = ctx->r3 | 0;
;}
RECOMP_FUNC void func_801ED9B4(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801ED9B4: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x801ED9B8: swc1        $f12, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->f12.u32l;
    // 0x801ED9BC: lwc1        $f4, 0x20($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X20);
    // 0x801ED9C0: sw          $a2, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r6;
    // 0x801ED9C4: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x801ED9C8: mul.s       $f6, $f4, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = MUL_S(ctx->f4.fl, ctx->f4.fl);
    // 0x801ED9CC: lwc1        $f4, 0x28($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X28);
    // 0x801ED9D0: sw          $a3, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r7;
    // 0x801ED9D4: mul.s       $f8, $f14, $f14
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f8.fl = MUL_S(ctx->f14.fl, ctx->f14.fl);
    // 0x801ED9D8: swc1        $f14, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->f14.u32l;
    // 0x801ED9DC: add.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = ctx->f6.fl + ctx->f8.fl;
    // 0x801ED9E0: mul.s       $f6, $f4, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = MUL_S(ctx->f4.fl, ctx->f4.fl);
    // 0x801ED9E4: jal         0x800C7010
    // 0x801ED9E8: add.s       $f12, $f10, $f6
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f12.fl = ctx->f10.fl + ctx->f6.fl;
    _nsqrtf(rdram, ctx);
        goto after_0;
    // 0x801ED9E8: add.s       $f12, $f10, $f6
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f12.fl = ctx->f10.fl + ctx->f6.fl;
    after_0:
    // 0x801ED9EC: lwc1        $f18, 0x2C($sp)
    ctx->f18.u32l = MEM_W(ctx->r29, 0X2C);
    // 0x801ED9F0: lwc1        $f14, 0x30($sp)
    ctx->f14.u32l = MEM_W(ctx->r29, 0X30);
    // 0x801ED9F4: lwc1        $f16, 0x34($sp)
    ctx->f16.u32l = MEM_W(ctx->r29, 0X34);
    // 0x801ED9F8: mul.s       $f8, $f18, $f18
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f8.fl = MUL_S(ctx->f18.fl, ctx->f18.fl);
    // 0x801ED9FC: swc1        $f0, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->f0.u32l;
    // 0x801EDA00: mul.s       $f4, $f14, $f14
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f4.fl = MUL_S(ctx->f14.fl, ctx->f14.fl);
    // 0x801EDA04: add.s       $f10, $f8, $f4
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f10.fl = ctx->f8.fl + ctx->f4.fl;
    // 0x801EDA08: mul.s       $f6, $f16, $f16
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f6.fl = MUL_S(ctx->f16.fl, ctx->f16.fl);
    // 0x801EDA0C: jal         0x800C7010
    // 0x801EDA10: add.s       $f12, $f10, $f6
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f12.fl = ctx->f10.fl + ctx->f6.fl;
    _nsqrtf(rdram, ctx);
        goto after_1;
    // 0x801EDA10: add.s       $f12, $f10, $f6
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f12.fl = ctx->f10.fl + ctx->f6.fl;
    after_1:
    // 0x801EDA14: lwc1        $f2, 0x1C($sp)
    ctx->f2.u32l = MEM_W(ctx->r29, 0X1C);
    // 0x801EDA18: mtc1        $zero, $f14
    ctx->f14.u32l = 0;
    // 0x801EDA1C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x801EDA20: c.lt.s      $f14, $f2
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 2);
    c1cs = ctx->f14.fl < ctx->f2.fl;
    // 0x801EDA24: nop

    // 0x801EDA28: bc1fl       L_801EDA78
    if (!c1cs) {
        // 0x801EDA2C: mov.s       $f0, $f14
        CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 14);
    ctx->f0.fl = ctx->f14.fl;
            goto L_801EDA78;
    }
    goto skip_0;
    // 0x801EDA2C: mov.s       $f0, $f14
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 14);
    ctx->f0.fl = ctx->f14.fl;
    skip_0:
    // 0x801EDA30: c.lt.s      $f14, $f0
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 0);
    c1cs = ctx->f14.fl < ctx->f0.fl;
    // 0x801EDA34: lwc1        $f8, 0x20($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X20);
    // 0x801EDA38: lwc1        $f4, 0x2C($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X2C);
    // 0x801EDA3C: lwc1        $f6, 0x24($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X24);
    // 0x801EDA40: bc1fl       L_801EDA78
    if (!c1cs) {
        // 0x801EDA44: mov.s       $f0, $f14
        CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 14);
    ctx->f0.fl = ctx->f14.fl;
            goto L_801EDA78;
    }
    goto skip_1;
    // 0x801EDA44: mov.s       $f0, $f14
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 14);
    ctx->f0.fl = ctx->f14.fl;
    skip_1:
    // 0x801EDA48: mul.s       $f10, $f8, $f4
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f10.fl = MUL_S(ctx->f8.fl, ctx->f4.fl);
    // 0x801EDA4C: lwc1        $f8, 0x30($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X30);
    // 0x801EDA50: mul.s       $f4, $f6, $f8
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f4.fl = MUL_S(ctx->f6.fl, ctx->f8.fl);
    // 0x801EDA54: lwc1        $f8, 0x28($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X28);
    // 0x801EDA58: add.s       $f6, $f10, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = ctx->f10.fl + ctx->f4.fl;
    // 0x801EDA5C: lwc1        $f10, 0x34($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0X34);
    // 0x801EDA60: mul.s       $f4, $f8, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f4.fl = MUL_S(ctx->f8.fl, ctx->f10.fl);
    // 0x801EDA64: add.s       $f8, $f6, $f4
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f8.fl = ctx->f6.fl + ctx->f4.fl;
    // 0x801EDA68: div.s       $f10, $f8, $f2
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f10.fl = DIV_S(ctx->f8.fl, ctx->f2.fl);
    // 0x801EDA6C: b           L_801EDA78
    // 0x801EDA70: div.s       $f0, $f10, $f0
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f0.fl = DIV_S(ctx->f10.fl, ctx->f0.fl);
        goto L_801EDA78;
    // 0x801EDA70: div.s       $f0, $f10, $f0
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f0.fl = DIV_S(ctx->f10.fl, ctx->f0.fl);
    // 0x801EDA74: mov.s       $f0, $f14
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 14);
    ctx->f0.fl = ctx->f14.fl;
L_801EDA78:
    // 0x801EDA78: jr          $ra
    // 0x801EDA7C: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    return;
    // 0x801EDA7C: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
;}
RECOMP_FUNC void func_801EDA80(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801EDA80: sw          $a2, 0x8($sp)
    MEM_W(0X8, ctx->r29) = ctx->r6;
    // 0x801EDA84: lwc1        $f4, 0x8($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X8);
    // 0x801EDA88: lwc1        $f6, 0x10($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X10);
    // 0x801EDA8C: lwc1        $f10, 0x14($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0X14);
    // 0x801EDA90: lw          $t6, 0x18($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X18);
    // 0x801EDA94: mul.s       $f8, $f4, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = MUL_S(ctx->f4.fl, ctx->f6.fl);
    // 0x801EDA98: sw          $a3, 0xC($sp)
    MEM_W(0XC, ctx->r29) = ctx->r7;
    // 0x801EDA9C: mul.s       $f16, $f14, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f16.fl = MUL_S(ctx->f14.fl, ctx->f10.fl);
    // 0x801EDAA0: sub.s       $f18, $f16, $f8
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f18.fl = ctx->f16.fl - ctx->f8.fl;
    // 0x801EDAA4: swc1        $f18, 0x0($t6)
    MEM_W(0X0, ctx->r14) = ctx->f18.u32l;
    // 0x801EDAA8: lwc1        $f16, 0xC($sp)
    ctx->f16.u32l = MEM_W(ctx->r29, 0XC);
    // 0x801EDAAC: lw          $t7, 0x1C($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X1C);
    // 0x801EDAB0: mul.s       $f8, $f4, $f16
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f8.fl = MUL_S(ctx->f4.fl, ctx->f16.fl);
    // 0x801EDAB4: nop

    // 0x801EDAB8: mul.s       $f18, $f12, $f10
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f18.fl = MUL_S(ctx->f12.fl, ctx->f10.fl);
    // 0x801EDABC: sub.s       $f4, $f8, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f4.fl = ctx->f8.fl - ctx->f18.fl;
    // 0x801EDAC0: mul.s       $f10, $f12, $f6
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f10.fl = MUL_S(ctx->f12.fl, ctx->f6.fl);
    // 0x801EDAC4: nop

    // 0x801EDAC8: mul.s       $f8, $f14, $f16
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f8.fl = MUL_S(ctx->f14.fl, ctx->f16.fl);
    // 0x801EDACC: swc1        $f4, 0x0($t7)
    MEM_W(0X0, ctx->r15) = ctx->f4.u32l;
    // 0x801EDAD0: lw          $t8, 0x20($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X20);
    // 0x801EDAD4: sub.s       $f18, $f10, $f8
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f18.fl = ctx->f10.fl - ctx->f8.fl;
    // 0x801EDAD8: jr          $ra
    // 0x801EDADC: swc1        $f18, 0x0($t8)
    MEM_W(0X0, ctx->r24) = ctx->f18.u32l;
    return;
    // 0x801EDADC: swc1        $f18, 0x0($t8)
    MEM_W(0X0, ctx->r24) = ctx->f18.u32l;
;}
RECOMP_FUNC void func_801EDAE0(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801EDAE0: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x801EDAE4: sw          $a2, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r6;
    // 0x801EDAE8: lwc1        $f4, 0x20($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X20);
    // 0x801EDAEC: lwc1        $f6, 0x28($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X28);
    // 0x801EDAF0: lwc1        $f10, 0x2C($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0X2C);
    // 0x801EDAF4: lw          $a0, 0x30($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X30);
    // 0x801EDAF8: mul.s       $f8, $f4, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = MUL_S(ctx->f4.fl, ctx->f6.fl);
    // 0x801EDAFC: lw          $a1, 0x34($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X34);
    // 0x801EDB00: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x801EDB04: mul.s       $f18, $f14, $f10
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f18.fl = MUL_S(ctx->f14.fl, ctx->f10.fl);
    // 0x801EDB08: swc1        $f12, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->f12.u32l;
    // 0x801EDB0C: sw          $a3, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r7;
    // 0x801EDB10: sub.s       $f4, $f18, $f8
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f4.fl = ctx->f18.fl - ctx->f8.fl;
    // 0x801EDB14: swc1        $f4, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->f4.u32l;
    // 0x801EDB18: lwc1        $f10, 0x24($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0X24);
    // 0x801EDB1C: lwc1        $f6, 0x20($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X20);
    // 0x801EDB20: lwc1        $f8, 0x18($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X18);
    // 0x801EDB24: lwc1        $f4, 0x2C($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X2C);
    // 0x801EDB28: mul.s       $f18, $f6, $f10
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f18.fl = MUL_S(ctx->f6.fl, ctx->f10.fl);
    // 0x801EDB2C: nop

    // 0x801EDB30: mul.s       $f6, $f8, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = MUL_S(ctx->f8.fl, ctx->f4.fl);
    // 0x801EDB34: sub.s       $f10, $f18, $f6
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f10.fl = ctx->f18.fl - ctx->f6.fl;
    // 0x801EDB38: swc1        $f10, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->f10.u32l;
    // 0x801EDB3C: lwc1        $f4, 0x28($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X28);
    // 0x801EDB40: lwc1        $f8, 0x18($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X18);
    // 0x801EDB44: lwc1        $f6, 0x24($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X24);
    // 0x801EDB48: lw          $t6, 0x38($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X38);
    // 0x801EDB4C: mul.s       $f18, $f8, $f4
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f18.fl = MUL_S(ctx->f8.fl, ctx->f4.fl);
    // 0x801EDB50: nop

    // 0x801EDB54: mul.s       $f10, $f14, $f6
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f10.fl = MUL_S(ctx->f14.fl, ctx->f6.fl);
    // 0x801EDB58: sub.s       $f0, $f18, $f10
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f0.fl = ctx->f18.fl - ctx->f10.fl;
    // 0x801EDB5C: swc1        $f0, 0x0($t6)
    MEM_W(0X0, ctx->r14) = ctx->f0.u32l;
    // 0x801EDB60: lwc1        $f2, 0x0($a0)
    ctx->f2.u32l = MEM_W(ctx->r4, 0X0);
    // 0x801EDB64: lwc1        $f16, 0x0($a1)
    ctx->f16.u32l = MEM_W(ctx->r5, 0X0);
    // 0x801EDB68: mul.s       $f8, $f2, $f2
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f8.fl = MUL_S(ctx->f2.fl, ctx->f2.fl);
    // 0x801EDB6C: nop

    // 0x801EDB70: mul.s       $f4, $f16, $f16
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f4.fl = MUL_S(ctx->f16.fl, ctx->f16.fl);
    // 0x801EDB74: add.s       $f6, $f8, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = ctx->f8.fl + ctx->f4.fl;
    // 0x801EDB78: mul.s       $f18, $f0, $f0
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f18.fl = MUL_S(ctx->f0.fl, ctx->f0.fl);
    // 0x801EDB7C: jal         0x800C7010
    // 0x801EDB80: add.s       $f12, $f18, $f6
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f12.fl = ctx->f18.fl + ctx->f6.fl;
    _nsqrtf(rdram, ctx);
        goto after_0;
    // 0x801EDB80: add.s       $f12, $f18, $f6
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f12.fl = ctx->f18.fl + ctx->f6.fl;
    after_0:
    // 0x801EDB84: mtc1        $zero, $f10
    ctx->f10.u32l = 0;
    // 0x801EDB88: lw          $v0, 0x38($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X38);
    // 0x801EDB8C: lw          $a0, 0x30($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X30);
    // 0x801EDB90: c.lt.s      $f10, $f0
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 0);
    c1cs = ctx->f10.fl < ctx->f0.fl;
    // 0x801EDB94: lw          $a1, 0x34($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X34);
    // 0x801EDB98: bc1fl       L_801EDBC8
    if (!c1cs) {
        // 0x801EDB9C: lw          $ra, 0x14($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X14);
            goto L_801EDBC8;
    }
    goto skip_0;
    // 0x801EDB9C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    skip_0:
    // 0x801EDBA0: lwc1        $f8, 0x0($a0)
    ctx->f8.u32l = MEM_W(ctx->r4, 0X0);
    // 0x801EDBA4: div.s       $f4, $f8, $f0
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f4.fl = DIV_S(ctx->f8.fl, ctx->f0.fl);
    // 0x801EDBA8: swc1        $f4, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->f4.u32l;
    // 0x801EDBAC: lwc1        $f18, 0x0($a1)
    ctx->f18.u32l = MEM_W(ctx->r5, 0X0);
    // 0x801EDBB0: div.s       $f6, $f18, $f0
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f6.fl = DIV_S(ctx->f18.fl, ctx->f0.fl);
    // 0x801EDBB4: swc1        $f6, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->f6.u32l;
    // 0x801EDBB8: lwc1        $f10, 0x0($v0)
    ctx->f10.u32l = MEM_W(ctx->r2, 0X0);
    // 0x801EDBBC: div.s       $f8, $f10, $f0
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f8.fl = DIV_S(ctx->f10.fl, ctx->f0.fl);
    // 0x801EDBC0: swc1        $f8, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->f8.u32l;
    // 0x801EDBC4: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_801EDBC8:
    // 0x801EDBC8: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x801EDBCC: jr          $ra
    // 0x801EDBD0: nop

    return;
    // 0x801EDBD0: nop

;}
RECOMP_FUNC void func_801EDBD4(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801EDBD4: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x801EDBD8: swc1        $f12, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->f12.u32l;
    // 0x801EDBDC: lwc1        $f4, 0x18($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X18);
    // 0x801EDBE0: sw          $a2, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r6;
    // 0x801EDBE4: lwc1        $f16, 0x20($sp)
    ctx->f16.u32l = MEM_W(ctx->r29, 0X20);
    // 0x801EDBE8: mul.s       $f6, $f4, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = MUL_S(ctx->f4.fl, ctx->f4.fl);
    // 0x801EDBEC: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x801EDBF0: sw          $a3, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r7;
    // 0x801EDBF4: mul.s       $f8, $f14, $f14
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f8.fl = MUL_S(ctx->f14.fl, ctx->f14.fl);
    // 0x801EDBF8: swc1        $f14, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->f14.u32l;
    // 0x801EDBFC: mul.s       $f18, $f16, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f18.fl = MUL_S(ctx->f16.fl, ctx->f16.fl);
    // 0x801EDC00: add.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = ctx->f6.fl + ctx->f8.fl;
    // 0x801EDC04: jal         0x800C7010
    // 0x801EDC08: add.s       $f12, $f10, $f18
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f12.fl = ctx->f10.fl + ctx->f18.fl;
    _nsqrtf(rdram, ctx);
        goto after_0;
    // 0x801EDC08: add.s       $f12, $f10, $f18
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f12.fl = ctx->f10.fl + ctx->f18.fl;
    after_0:
    // 0x801EDC0C: mtc1        $zero, $f4
    ctx->f4.u32l = 0;
    // 0x801EDC10: lwc1        $f14, 0x1C($sp)
    ctx->f14.u32l = MEM_W(ctx->r29, 0X1C);
    // 0x801EDC14: lwc1        $f6, 0x18($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X18);
    // 0x801EDC18: c.lt.s      $f4, $f0
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    c1cs = ctx->f4.fl < ctx->f0.fl;
    // 0x801EDC1C: nop

    // 0x801EDC20: bc1fl       L_801EDC54
    if (!c1cs) {
        // 0x801EDC24: lw          $ra, 0x14($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X14);
            goto L_801EDC54;
    }
    goto skip_0;
    // 0x801EDC24: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    skip_0:
    // 0x801EDC28: div.s       $f8, $f6, $f0
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f8.fl = DIV_S(ctx->f6.fl, ctx->f0.fl);
    // 0x801EDC2C: lw          $t6, 0x24($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X24);
    // 0x801EDC30: div.s       $f16, $f14, $f0
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f16.fl = DIV_S(ctx->f14.fl, ctx->f0.fl);
    // 0x801EDC34: swc1        $f8, 0x0($t6)
    MEM_W(0X0, ctx->r14) = ctx->f8.u32l;
    // 0x801EDC38: lw          $t7, 0x28($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X28);
    // 0x801EDC3C: swc1        $f16, 0x0($t7)
    MEM_W(0X0, ctx->r15) = ctx->f16.u32l;
    // 0x801EDC40: lwc1        $f10, 0x20($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0X20);
    // 0x801EDC44: lw          $t8, 0x2C($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X2C);
    // 0x801EDC48: div.s       $f18, $f10, $f0
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f18.fl = DIV_S(ctx->f10.fl, ctx->f0.fl);
    // 0x801EDC4C: swc1        $f18, 0x0($t8)
    MEM_W(0X0, ctx->r24) = ctx->f18.u32l;
    // 0x801EDC50: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_801EDC54:
    // 0x801EDC54: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x801EDC58: jr          $ra
    // 0x801EDC5C: nop

    return;
    // 0x801EDC5C: nop

;}
RECOMP_FUNC void func_801EDC60(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801EDC60: sw          $a3, 0xC($sp)
    MEM_W(0XC, ctx->r29) = ctx->r7;
    // 0x801EDC64: mtc1        $a1, $f12
    ctx->f12.u32l = ctx->r5;
    // 0x801EDC68: lwc1        $f4, 0x0($a0)
    ctx->f4.u32l = MEM_W(ctx->r4, 0X0);
    // 0x801EDC6C: mtc1        $a2, $f14
    ctx->f14.u32l = ctx->r6;
    // 0x801EDC70: lwc1        $f8, 0x10($a0)
    ctx->f8.u32l = MEM_W(ctx->r4, 0X10);
    // 0x801EDC74: mul.s       $f6, $f4, $f12
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f6.fl = MUL_S(ctx->f4.fl, ctx->f12.fl);
    // 0x801EDC78: lwc1        $f4, 0xC($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0XC);
    // 0x801EDC7C: lwc1        $f18, 0x20($a0)
    ctx->f18.u32l = MEM_W(ctx->r4, 0X20);
    // 0x801EDC80: mul.s       $f10, $f8, $f14
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f10.fl = MUL_S(ctx->f8.fl, ctx->f14.fl);
    // 0x801EDC84: lw          $t6, 0x10($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X10);
    // 0x801EDC88: mul.s       $f8, $f18, $f4
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f8.fl = MUL_S(ctx->f18.fl, ctx->f4.fl);
    // 0x801EDC8C: add.s       $f16, $f6, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f16.fl = ctx->f6.fl + ctx->f10.fl;
    // 0x801EDC90: lwc1        $f10, 0x30($a0)
    ctx->f10.u32l = MEM_W(ctx->r4, 0X30);
    // 0x801EDC94: add.s       $f6, $f16, $f8
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f6.fl = ctx->f16.fl + ctx->f8.fl;
    // 0x801EDC98: add.s       $f18, $f10, $f6
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f18.fl = ctx->f10.fl + ctx->f6.fl;
    // 0x801EDC9C: swc1        $f18, 0x0($t6)
    MEM_W(0X0, ctx->r14) = ctx->f18.u32l;
    // 0x801EDCA0: lwc1        $f16, 0x4($a0)
    ctx->f16.u32l = MEM_W(ctx->r4, 0X4);
    // 0x801EDCA4: lwc1        $f10, 0x14($a0)
    ctx->f10.u32l = MEM_W(ctx->r4, 0X14);
    // 0x801EDCA8: lw          $t7, 0x14($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X14);
    // 0x801EDCAC: mul.s       $f8, $f16, $f12
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f8.fl = MUL_S(ctx->f16.fl, ctx->f12.fl);
    // 0x801EDCB0: lwc1        $f16, 0x24($a0)
    ctx->f16.u32l = MEM_W(ctx->r4, 0X24);
    // 0x801EDCB4: mul.s       $f6, $f10, $f14
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f6.fl = MUL_S(ctx->f10.fl, ctx->f14.fl);
    // 0x801EDCB8: add.s       $f18, $f8, $f6
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f18.fl = ctx->f8.fl + ctx->f6.fl;
    // 0x801EDCBC: mul.s       $f10, $f16, $f4
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f10.fl = MUL_S(ctx->f16.fl, ctx->f4.fl);
    // 0x801EDCC0: lwc1        $f6, 0x34($a0)
    ctx->f6.u32l = MEM_W(ctx->r4, 0X34);
    // 0x801EDCC4: add.s       $f8, $f18, $f10
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f8.fl = ctx->f18.fl + ctx->f10.fl;
    // 0x801EDCC8: add.s       $f16, $f6, $f8
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f16.fl = ctx->f6.fl + ctx->f8.fl;
    // 0x801EDCCC: swc1        $f16, 0x0($t7)
    MEM_W(0X0, ctx->r15) = ctx->f16.u32l;
    // 0x801EDCD0: lwc1        $f18, 0x8($a0)
    ctx->f18.u32l = MEM_W(ctx->r4, 0X8);
    // 0x801EDCD4: lwc1        $f6, 0x18($a0)
    ctx->f6.u32l = MEM_W(ctx->r4, 0X18);
    // 0x801EDCD8: lw          $t8, 0x18($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X18);
    // 0x801EDCDC: mul.s       $f10, $f18, $f12
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f10.fl = MUL_S(ctx->f18.fl, ctx->f12.fl);
    // 0x801EDCE0: lwc1        $f18, 0x28($a0)
    ctx->f18.u32l = MEM_W(ctx->r4, 0X28);
    // 0x801EDCE4: mul.s       $f8, $f6, $f14
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f8.fl = MUL_S(ctx->f6.fl, ctx->f14.fl);
    // 0x801EDCE8: add.s       $f16, $f10, $f8
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f16.fl = ctx->f10.fl + ctx->f8.fl;
    // 0x801EDCEC: mul.s       $f6, $f18, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = MUL_S(ctx->f18.fl, ctx->f4.fl);
    // 0x801EDCF0: lwc1        $f8, 0x38($a0)
    ctx->f8.u32l = MEM_W(ctx->r4, 0X38);
    // 0x801EDCF4: add.s       $f10, $f16, $f6
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f10.fl = ctx->f16.fl + ctx->f6.fl;
    // 0x801EDCF8: add.s       $f18, $f8, $f10
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f18.fl = ctx->f8.fl + ctx->f10.fl;
    // 0x801EDCFC: jr          $ra
    // 0x801EDD00: swc1        $f18, 0x0($t8)
    MEM_W(0X0, ctx->r24) = ctx->f18.u32l;
    return;
    // 0x801EDD00: swc1        $f18, 0x0($t8)
    MEM_W(0X0, ctx->r24) = ctx->f18.u32l;
;}
RECOMP_FUNC void func_801EDD04(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801EDD04: sw          $a2, 0x8($sp)
    MEM_W(0X8, ctx->r29) = ctx->r6;
    // 0x801EDD08: lwc1        $f6, 0x8($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X8);
    // 0x801EDD0C: lwc1        $f4, 0x10($a0)
    ctx->f4.u32l = MEM_W(ctx->r4, 0X10);
    // 0x801EDD10: mtc1        $a1, $f14
    ctx->f14.u32l = ctx->r5;
    // 0x801EDD14: lwc1        $f10, 0x0($a0)
    ctx->f10.u32l = MEM_W(ctx->r4, 0X0);
    // 0x801EDD18: mul.s       $f8, $f4, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = MUL_S(ctx->f4.fl, ctx->f6.fl);
    // 0x801EDD1C: mtc1        $a3, $f12
    ctx->f12.u32l = ctx->r7;
    // 0x801EDD20: lwc1        $f4, 0x20($a0)
    ctx->f4.u32l = MEM_W(ctx->r4, 0X20);
    // 0x801EDD24: mul.s       $f16, $f10, $f14
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f16.fl = MUL_S(ctx->f10.fl, ctx->f14.fl);
    // 0x801EDD28: lw          $t6, 0x10($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X10);
    // 0x801EDD2C: mul.s       $f10, $f4, $f12
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f10.fl = MUL_S(ctx->f4.fl, ctx->f12.fl);
    // 0x801EDD30: add.s       $f18, $f16, $f8
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f18.fl = ctx->f16.fl + ctx->f8.fl;
    // 0x801EDD34: add.s       $f16, $f10, $f18
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f16.fl = ctx->f10.fl + ctx->f18.fl;
    // 0x801EDD38: swc1        $f16, 0x0($t6)
    MEM_W(0X0, ctx->r14) = ctx->f16.u32l;
    // 0x801EDD3C: lwc1        $f8, 0x14($a0)
    ctx->f8.u32l = MEM_W(ctx->r4, 0X14);
    // 0x801EDD40: lwc1        $f10, 0x4($a0)
    ctx->f10.u32l = MEM_W(ctx->r4, 0X4);
    // 0x801EDD44: lw          $t7, 0x14($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X14);
    // 0x801EDD48: mul.s       $f4, $f8, $f6
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f4.fl = MUL_S(ctx->f8.fl, ctx->f6.fl);
    // 0x801EDD4C: lwc1        $f8, 0x24($a0)
    ctx->f8.u32l = MEM_W(ctx->r4, 0X24);
    // 0x801EDD50: mul.s       $f18, $f10, $f14
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f18.fl = MUL_S(ctx->f10.fl, ctx->f14.fl);
    // 0x801EDD54: add.s       $f16, $f18, $f4
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f16.fl = ctx->f18.fl + ctx->f4.fl;
    // 0x801EDD58: mul.s       $f10, $f8, $f12
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f10.fl = MUL_S(ctx->f8.fl, ctx->f12.fl);
    // 0x801EDD5C: add.s       $f18, $f10, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f18.fl = ctx->f10.fl + ctx->f16.fl;
    // 0x801EDD60: swc1        $f18, 0x0($t7)
    MEM_W(0X0, ctx->r15) = ctx->f18.u32l;
    // 0x801EDD64: lwc1        $f4, 0x18($a0)
    ctx->f4.u32l = MEM_W(ctx->r4, 0X18);
    // 0x801EDD68: lwc1        $f10, 0x8($a0)
    ctx->f10.u32l = MEM_W(ctx->r4, 0X8);
    // 0x801EDD6C: lw          $t8, 0x18($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X18);
    // 0x801EDD70: mul.s       $f8, $f4, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = MUL_S(ctx->f4.fl, ctx->f6.fl);
    // 0x801EDD74: lwc1        $f4, 0x28($a0)
    ctx->f4.u32l = MEM_W(ctx->r4, 0X28);
    // 0x801EDD78: mul.s       $f16, $f10, $f14
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f16.fl = MUL_S(ctx->f10.fl, ctx->f14.fl);
    // 0x801EDD7C: add.s       $f18, $f16, $f8
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f18.fl = ctx->f16.fl + ctx->f8.fl;
    // 0x801EDD80: mul.s       $f6, $f4, $f12
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f6.fl = MUL_S(ctx->f4.fl, ctx->f12.fl);
    // 0x801EDD84: add.s       $f10, $f6, $f18
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f10.fl = ctx->f6.fl + ctx->f18.fl;
    // 0x801EDD88: jr          $ra
    // 0x801EDD8C: swc1        $f10, 0x0($t8)
    MEM_W(0X0, ctx->r24) = ctx->f10.u32l;
    return;
    // 0x801EDD8C: swc1        $f10, 0x0($t8)
    MEM_W(0X0, ctx->r24) = ctx->f10.u32l;
;}
RECOMP_FUNC void _MtxF_to_Mtx(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801EDD90: lui         $at, 0x4780
    ctx->r1 = S32(0X4780 << 16);
    // 0x801EDD94: mtc1        $at, $f0
    ctx->f0.u32l = ctx->r1;
    // 0x801EDD98: lwc1        $f4, 0x3C($a0)
    ctx->f4.u32l = MEM_W(ctx->r4, 0X3C);
    // 0x801EDD9C: mul.s       $f6, $f4, $f0
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f6.fl = MUL_S(ctx->f4.fl, ctx->f0.fl);
    // 0x801EDDA0: trunc.w.s   $f8, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    ctx->f8.u32l = TRUNC_W_S(ctx->f6.fl);
    // 0x801EDDA4: mfc1        $t8, $f8
    ctx->r24 = (int32_t)ctx->f8.u32l;
    // 0x801EDDA8: nop

    // 0x801EDDAC: srl         $t7, $t8, 16
    ctx->r15 = S32(U32(ctx->r24) >> 16);
    // 0x801EDDB0: sh          $t7, 0x1E($a1)
    MEM_H(0X1E, ctx->r5) = ctx->r15;
    // 0x801EDDB4: sh          $t8, 0x3E($a1)
    MEM_H(0X3E, ctx->r5) = ctx->r24;
    // 0x801EDDB8: lwc1        $f10, 0x38($a0)
    ctx->f10.u32l = MEM_W(ctx->r4, 0X38);
    // 0x801EDDBC: mul.s       $f16, $f10, $f0
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f16.fl = MUL_S(ctx->f10.fl, ctx->f0.fl);
    // 0x801EDDC0: trunc.w.s   $f18, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    ctx->f18.u32l = TRUNC_W_S(ctx->f16.fl);
    // 0x801EDDC4: mfc1        $t1, $f18
    ctx->r9 = (int32_t)ctx->f18.u32l;
    // 0x801EDDC8: nop

    // 0x801EDDCC: srl         $t0, $t1, 16
    ctx->r8 = S32(U32(ctx->r9) >> 16);
    // 0x801EDDD0: sh          $t0, 0x1C($a1)
    MEM_H(0X1C, ctx->r5) = ctx->r8;
    // 0x801EDDD4: sh          $t1, 0x3C($a1)
    MEM_H(0X3C, ctx->r5) = ctx->r9;
    // 0x801EDDD8: lwc1        $f4, 0x34($a0)
    ctx->f4.u32l = MEM_W(ctx->r4, 0X34);
    // 0x801EDDDC: mul.s       $f6, $f4, $f0
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f6.fl = MUL_S(ctx->f4.fl, ctx->f0.fl);
    // 0x801EDDE0: trunc.w.s   $f8, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    ctx->f8.u32l = TRUNC_W_S(ctx->f6.fl);
    // 0x801EDDE4: mfc1        $t4, $f8
    ctx->r12 = (int32_t)ctx->f8.u32l;
    // 0x801EDDE8: nop

    // 0x801EDDEC: srl         $t3, $t4, 16
    ctx->r11 = S32(U32(ctx->r12) >> 16);
    // 0x801EDDF0: sh          $t3, 0x1A($a1)
    MEM_H(0X1A, ctx->r5) = ctx->r11;
    // 0x801EDDF4: sh          $t4, 0x3A($a1)
    MEM_H(0X3A, ctx->r5) = ctx->r12;
    // 0x801EDDF8: lwc1        $f10, 0x30($a0)
    ctx->f10.u32l = MEM_W(ctx->r4, 0X30);
    // 0x801EDDFC: mul.s       $f16, $f10, $f0
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f16.fl = MUL_S(ctx->f10.fl, ctx->f0.fl);
    // 0x801EDE00: trunc.w.s   $f18, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    ctx->f18.u32l = TRUNC_W_S(ctx->f16.fl);
    // 0x801EDE04: mfc1        $t7, $f18
    ctx->r15 = (int32_t)ctx->f18.u32l;
    // 0x801EDE08: nop

    // 0x801EDE0C: srl         $t6, $t7, 16
    ctx->r14 = S32(U32(ctx->r15) >> 16);
    // 0x801EDE10: sh          $t6, 0x18($a1)
    MEM_H(0X18, ctx->r5) = ctx->r14;
    // 0x801EDE14: sh          $t7, 0x38($a1)
    MEM_H(0X38, ctx->r5) = ctx->r15;
    // 0x801EDE18: lwc1        $f4, 0x2C($a0)
    ctx->f4.u32l = MEM_W(ctx->r4, 0X2C);
    // 0x801EDE1C: mul.s       $f6, $f4, $f0
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f6.fl = MUL_S(ctx->f4.fl, ctx->f0.fl);
    // 0x801EDE20: trunc.w.s   $f8, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    ctx->f8.u32l = TRUNC_W_S(ctx->f6.fl);
    // 0x801EDE24: mfc1        $t0, $f8
    ctx->r8 = (int32_t)ctx->f8.u32l;
    // 0x801EDE28: nop

    // 0x801EDE2C: srl         $t9, $t0, 16
    ctx->r25 = S32(U32(ctx->r8) >> 16);
    // 0x801EDE30: sh          $t9, 0x16($a1)
    MEM_H(0X16, ctx->r5) = ctx->r25;
    // 0x801EDE34: sh          $t0, 0x36($a1)
    MEM_H(0X36, ctx->r5) = ctx->r8;
    // 0x801EDE38: lwc1        $f10, 0x28($a0)
    ctx->f10.u32l = MEM_W(ctx->r4, 0X28);
    // 0x801EDE3C: mul.s       $f16, $f10, $f0
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f16.fl = MUL_S(ctx->f10.fl, ctx->f0.fl);
    // 0x801EDE40: trunc.w.s   $f18, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    ctx->f18.u32l = TRUNC_W_S(ctx->f16.fl);
    // 0x801EDE44: mfc1        $t3, $f18
    ctx->r11 = (int32_t)ctx->f18.u32l;
    // 0x801EDE48: nop

    // 0x801EDE4C: srl         $t2, $t3, 16
    ctx->r10 = S32(U32(ctx->r11) >> 16);
    // 0x801EDE50: sh          $t2, 0x14($a1)
    MEM_H(0X14, ctx->r5) = ctx->r10;
    // 0x801EDE54: sh          $t3, 0x34($a1)
    MEM_H(0X34, ctx->r5) = ctx->r11;
    // 0x801EDE58: lwc1        $f4, 0x24($a0)
    ctx->f4.u32l = MEM_W(ctx->r4, 0X24);
    // 0x801EDE5C: mul.s       $f6, $f4, $f0
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f6.fl = MUL_S(ctx->f4.fl, ctx->f0.fl);
    // 0x801EDE60: trunc.w.s   $f8, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    ctx->f8.u32l = TRUNC_W_S(ctx->f6.fl);
    // 0x801EDE64: mfc1        $t6, $f8
    ctx->r14 = (int32_t)ctx->f8.u32l;
    // 0x801EDE68: nop

    // 0x801EDE6C: srl         $t5, $t6, 16
    ctx->r13 = S32(U32(ctx->r14) >> 16);
    // 0x801EDE70: sh          $t5, 0x12($a1)
    MEM_H(0X12, ctx->r5) = ctx->r13;
    // 0x801EDE74: sh          $t6, 0x32($a1)
    MEM_H(0X32, ctx->r5) = ctx->r14;
    // 0x801EDE78: lwc1        $f10, 0x20($a0)
    ctx->f10.u32l = MEM_W(ctx->r4, 0X20);
    // 0x801EDE7C: mul.s       $f16, $f10, $f0
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f16.fl = MUL_S(ctx->f10.fl, ctx->f0.fl);
    // 0x801EDE80: trunc.w.s   $f18, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    ctx->f18.u32l = TRUNC_W_S(ctx->f16.fl);
    // 0x801EDE84: mfc1        $t9, $f18
    ctx->r25 = (int32_t)ctx->f18.u32l;
    // 0x801EDE88: nop

    // 0x801EDE8C: srl         $t8, $t9, 16
    ctx->r24 = S32(U32(ctx->r25) >> 16);
    // 0x801EDE90: sh          $t8, 0x10($a1)
    MEM_H(0X10, ctx->r5) = ctx->r24;
    // 0x801EDE94: sh          $t9, 0x30($a1)
    MEM_H(0X30, ctx->r5) = ctx->r25;
    // 0x801EDE98: lwc1        $f4, 0x1C($a0)
    ctx->f4.u32l = MEM_W(ctx->r4, 0X1C);
    // 0x801EDE9C: mul.s       $f6, $f4, $f0
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f6.fl = MUL_S(ctx->f4.fl, ctx->f0.fl);
    // 0x801EDEA0: trunc.w.s   $f8, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    ctx->f8.u32l = TRUNC_W_S(ctx->f6.fl);
    // 0x801EDEA4: mfc1        $t2, $f8
    ctx->r10 = (int32_t)ctx->f8.u32l;
    // 0x801EDEA8: nop

    // 0x801EDEAC: srl         $t1, $t2, 16
    ctx->r9 = S32(U32(ctx->r10) >> 16);
    // 0x801EDEB0: sh          $t1, 0xE($a1)
    MEM_H(0XE, ctx->r5) = ctx->r9;
    // 0x801EDEB4: sh          $t2, 0x2E($a1)
    MEM_H(0X2E, ctx->r5) = ctx->r10;
    // 0x801EDEB8: lwc1        $f10, 0x18($a0)
    ctx->f10.u32l = MEM_W(ctx->r4, 0X18);
    // 0x801EDEBC: mul.s       $f16, $f10, $f0
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f16.fl = MUL_S(ctx->f10.fl, ctx->f0.fl);
    // 0x801EDEC0: trunc.w.s   $f18, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    ctx->f18.u32l = TRUNC_W_S(ctx->f16.fl);
    // 0x801EDEC4: mfc1        $t5, $f18
    ctx->r13 = (int32_t)ctx->f18.u32l;
    // 0x801EDEC8: nop

    // 0x801EDECC: srl         $t4, $t5, 16
    ctx->r12 = S32(U32(ctx->r13) >> 16);
    // 0x801EDED0: sh          $t4, 0xC($a1)
    MEM_H(0XC, ctx->r5) = ctx->r12;
    // 0x801EDED4: sh          $t5, 0x2C($a1)
    MEM_H(0X2C, ctx->r5) = ctx->r13;
    // 0x801EDED8: lwc1        $f4, 0x14($a0)
    ctx->f4.u32l = MEM_W(ctx->r4, 0X14);
    // 0x801EDEDC: mul.s       $f6, $f4, $f0
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f6.fl = MUL_S(ctx->f4.fl, ctx->f0.fl);
    // 0x801EDEE0: trunc.w.s   $f8, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    ctx->f8.u32l = TRUNC_W_S(ctx->f6.fl);
    // 0x801EDEE4: mfc1        $t8, $f8
    ctx->r24 = (int32_t)ctx->f8.u32l;
    // 0x801EDEE8: nop

    // 0x801EDEEC: srl         $t7, $t8, 16
    ctx->r15 = S32(U32(ctx->r24) >> 16);
    // 0x801EDEF0: sh          $t7, 0xA($a1)
    MEM_H(0XA, ctx->r5) = ctx->r15;
    // 0x801EDEF4: sh          $t8, 0x2A($a1)
    MEM_H(0X2A, ctx->r5) = ctx->r24;
    // 0x801EDEF8: lwc1        $f10, 0x10($a0)
    ctx->f10.u32l = MEM_W(ctx->r4, 0X10);
    // 0x801EDEFC: mul.s       $f16, $f10, $f0
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f16.fl = MUL_S(ctx->f10.fl, ctx->f0.fl);
    // 0x801EDF00: trunc.w.s   $f18, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    ctx->f18.u32l = TRUNC_W_S(ctx->f16.fl);
    // 0x801EDF04: mfc1        $t1, $f18
    ctx->r9 = (int32_t)ctx->f18.u32l;
    // 0x801EDF08: nop

    // 0x801EDF0C: srl         $t0, $t1, 16
    ctx->r8 = S32(U32(ctx->r9) >> 16);
    // 0x801EDF10: sh          $t0, 0x8($a1)
    MEM_H(0X8, ctx->r5) = ctx->r8;
    // 0x801EDF14: sh          $t1, 0x28($a1)
    MEM_H(0X28, ctx->r5) = ctx->r9;
    // 0x801EDF18: lwc1        $f4, 0xC($a0)
    ctx->f4.u32l = MEM_W(ctx->r4, 0XC);
    // 0x801EDF1C: mul.s       $f6, $f4, $f0
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f6.fl = MUL_S(ctx->f4.fl, ctx->f0.fl);
    // 0x801EDF20: trunc.w.s   $f8, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    ctx->f8.u32l = TRUNC_W_S(ctx->f6.fl);
    // 0x801EDF24: mfc1        $t4, $f8
    ctx->r12 = (int32_t)ctx->f8.u32l;
    // 0x801EDF28: nop

    // 0x801EDF2C: srl         $t3, $t4, 16
    ctx->r11 = S32(U32(ctx->r12) >> 16);
    // 0x801EDF30: sh          $t3, 0x6($a1)
    MEM_H(0X6, ctx->r5) = ctx->r11;
    // 0x801EDF34: sh          $t4, 0x26($a1)
    MEM_H(0X26, ctx->r5) = ctx->r12;
    // 0x801EDF38: lwc1        $f10, 0x8($a0)
    ctx->f10.u32l = MEM_W(ctx->r4, 0X8);
    // 0x801EDF3C: mul.s       $f16, $f10, $f0
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f16.fl = MUL_S(ctx->f10.fl, ctx->f0.fl);
    // 0x801EDF40: trunc.w.s   $f18, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    ctx->f18.u32l = TRUNC_W_S(ctx->f16.fl);
    // 0x801EDF44: mfc1        $t7, $f18
    ctx->r15 = (int32_t)ctx->f18.u32l;
    // 0x801EDF48: nop

    // 0x801EDF4C: srl         $t6, $t7, 16
    ctx->r14 = S32(U32(ctx->r15) >> 16);
    // 0x801EDF50: sh          $t6, 0x4($a1)
    MEM_H(0X4, ctx->r5) = ctx->r14;
    // 0x801EDF54: sh          $t7, 0x24($a1)
    MEM_H(0X24, ctx->r5) = ctx->r15;
    // 0x801EDF58: lwc1        $f4, 0x4($a0)
    ctx->f4.u32l = MEM_W(ctx->r4, 0X4);
    // 0x801EDF5C: mul.s       $f6, $f4, $f0
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f6.fl = MUL_S(ctx->f4.fl, ctx->f0.fl);
    // 0x801EDF60: trunc.w.s   $f8, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    ctx->f8.u32l = TRUNC_W_S(ctx->f6.fl);
    // 0x801EDF64: mfc1        $t0, $f8
    ctx->r8 = (int32_t)ctx->f8.u32l;
    // 0x801EDF68: nop

    // 0x801EDF6C: srl         $t9, $t0, 16
    ctx->r25 = S32(U32(ctx->r8) >> 16);
    // 0x801EDF70: sh          $t9, 0x2($a1)
    MEM_H(0X2, ctx->r5) = ctx->r25;
    // 0x801EDF74: sh          $t0, 0x22($a1)
    MEM_H(0X22, ctx->r5) = ctx->r8;
    // 0x801EDF78: lwc1        $f10, 0x0($a0)
    ctx->f10.u32l = MEM_W(ctx->r4, 0X0);
    // 0x801EDF7C: mul.s       $f16, $f10, $f0
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f16.fl = MUL_S(ctx->f10.fl, ctx->f0.fl);
    // 0x801EDF80: trunc.w.s   $f18, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    ctx->f18.u32l = TRUNC_W_S(ctx->f16.fl);
    // 0x801EDF84: mfc1        $t3, $f18
    ctx->r11 = (int32_t)ctx->f18.u32l;
    // 0x801EDF88: nop

    // 0x801EDF8C: srl         $t2, $t3, 16
    ctx->r10 = S32(U32(ctx->r11) >> 16);
    // 0x801EDF90: sh          $t2, 0x0($a1)
    MEM_H(0X0, ctx->r5) = ctx->r10;
    // 0x801EDF94: jr          $ra
    // 0x801EDF98: sh          $t3, 0x20($a1)
    MEM_H(0X20, ctx->r5) = ctx->r11;
    return;
    // 0x801EDF98: sh          $t3, 0x20($a1)
    MEM_H(0X20, ctx->r5) = ctx->r11;
;}
RECOMP_FUNC void func_801EDF9C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801EDF9C: sw          $a3, 0xC($sp)
    MEM_W(0XC, ctx->r29) = ctx->r7;
    // 0x801EDFA0: mtc1        $zero, $f2
    ctx->f2.u32l = 0;
    // 0x801EDFA4: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x801EDFA8: mtc1        $at, $f0
    ctx->f0.u32l = ctx->r1;
    // 0x801EDFAC: mtc1        $a1, $f12
    ctx->f12.u32l = ctx->r5;
    // 0x801EDFB0: mtc1        $a2, $f14
    ctx->f14.u32l = ctx->r6;
    // 0x801EDFB4: swc1        $f2, 0x2C($a0)
    MEM_W(0X2C, ctx->r4) = ctx->f2.u32l;
    // 0x801EDFB8: swc1        $f2, 0x1C($a0)
    MEM_W(0X1C, ctx->r4) = ctx->f2.u32l;
    // 0x801EDFBC: swc1        $f2, 0xC($a0)
    MEM_W(0XC, ctx->r4) = ctx->f2.u32l;
    // 0x801EDFC0: swc1        $f2, 0x18($a0)
    MEM_W(0X18, ctx->r4) = ctx->f2.u32l;
    // 0x801EDFC4: swc1        $f2, 0x8($a0)
    MEM_W(0X8, ctx->r4) = ctx->f2.u32l;
    // 0x801EDFC8: swc1        $f2, 0x24($a0)
    MEM_W(0X24, ctx->r4) = ctx->f2.u32l;
    // 0x801EDFCC: swc1        $f2, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->f2.u32l;
    // 0x801EDFD0: swc1        $f2, 0x20($a0)
    MEM_W(0X20, ctx->r4) = ctx->f2.u32l;
    // 0x801EDFD4: swc1        $f2, 0x10($a0)
    MEM_W(0X10, ctx->r4) = ctx->f2.u32l;
    // 0x801EDFD8: swc1        $f0, 0x3C($a0)
    MEM_W(0X3C, ctx->r4) = ctx->f0.u32l;
    // 0x801EDFDC: swc1        $f0, 0x28($a0)
    MEM_W(0X28, ctx->r4) = ctx->f0.u32l;
    // 0x801EDFE0: swc1        $f0, 0x14($a0)
    MEM_W(0X14, ctx->r4) = ctx->f0.u32l;
    // 0x801EDFE4: swc1        $f0, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->f0.u32l;
    // 0x801EDFE8: swc1        $f12, 0x30($a0)
    MEM_W(0X30, ctx->r4) = ctx->f12.u32l;
    // 0x801EDFEC: swc1        $f14, 0x34($a0)
    MEM_W(0X34, ctx->r4) = ctx->f14.u32l;
    // 0x801EDFF0: lwc1        $f4, 0xC($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0XC);
    // 0x801EDFF4: jr          $ra
    // 0x801EDFF8: swc1        $f4, 0x38($a0)
    MEM_W(0X38, ctx->r4) = ctx->f4.u32l;
    return;
    // 0x801EDFF8: swc1        $f4, 0x38($a0)
    MEM_W(0X38, ctx->r4) = ctx->f4.u32l;
;}
RECOMP_FUNC void func_801EDFFC(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801EDFFC: mtc1        $a1, $f12
    ctx->f12.u32l = ctx->r5;
    // 0x801EE000: mtc1        $a2, $f14
    ctx->f14.u32l = ctx->r6;
    // 0x801EE004: addiu       $sp, $sp, -0x58
    ctx->r29 = ADD32(ctx->r29, -0X58);
    // 0x801EE008: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x801EE00C: sw          $a0, 0x58($sp)
    MEM_W(0X58, ctx->r29) = ctx->r4;
    // 0x801EE010: mfc1        $a1, $f12
    ctx->r5 = (int32_t)ctx->f12.u32l;
    // 0x801EE014: mfc1        $a2, $f14
    ctx->r6 = (int32_t)ctx->f14.u32l;
    // 0x801EE018: sw          $a3, 0x64($sp)
    MEM_W(0X64, ctx->r29) = ctx->r7;
    // 0x801EE01C: jal         0x801EDF9C
    // 0x801EE020: addiu       $a0, $sp, 0x18
    ctx->r4 = ADD32(ctx->r29, 0X18);
    func_801EDF9C(rdram, ctx);
        goto after_0;
    // 0x801EE020: addiu       $a0, $sp, 0x18
    ctx->r4 = ADD32(ctx->r29, 0X18);
    after_0:
    // 0x801EE024: addiu       $a0, $sp, 0x18
    ctx->r4 = ADD32(ctx->r29, 0X18);
    // 0x801EE028: jal         0x801EDD90
    // 0x801EE02C: lw          $a1, 0x58($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X58);
    _MtxF_to_Mtx(rdram, ctx);
        goto after_1;
    // 0x801EE02C: lw          $a1, 0x58($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X58);
    after_1:
    // 0x801EE030: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x801EE034: addiu       $sp, $sp, 0x58
    ctx->r29 = ADD32(ctx->r29, 0X58);
    // 0x801EE038: jr          $ra
    // 0x801EE03C: nop

    return;
    // 0x801EE03C: nop

;}
RECOMP_FUNC void func_801EE040(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801EE040: mtc1        $a2, $f14
    ctx->f14.u32l = ctx->r6;
    // 0x801EE044: addiu       $sp, $sp, -0x70
    ctx->r29 = ADD32(ctx->r29, -0X70);
    // 0x801EE048: sdc1        $f20, 0x10($sp)
    CHECK_FR(ctx, 20);
    SD(ctx->f20.u64, 0X10, ctx->r29);
    // 0x801EE04C: mul.s       $f2, $f14, $f14
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f2.fl = MUL_S(ctx->f14.fl, ctx->f14.fl);
    // 0x801EE050: mtc1        $a3, $f20
    ctx->f20.u32l = ctx->r7;
    // 0x801EE054: sdc1        $f22, 0x18($sp)
    CHECK_FR(ctx, 22);
    SD(ctx->f22.u64, 0X18, ctx->r29);
    // 0x801EE058: lwc1        $f22, 0x80($sp)
    ctx->f22.u32l = MEM_W(ctx->r29, 0X80);
    // 0x801EE05C: mul.s       $f18, $f20, $f20
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f18.fl = MUL_S(ctx->f20.fl, ctx->f20.fl);
    // 0x801EE060: sdc1        $f26, 0x28($sp)
    CHECK_FR(ctx, 26);
    SD(ctx->f26.u64, 0X28, ctx->r29);
    // 0x801EE064: sw          $ra, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r31;
    // 0x801EE068: mul.s       $f26, $f22, $f22
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f26.fl = MUL_S(ctx->f22.fl, ctx->f22.fl);
    // 0x801EE06C: sdc1        $f24, 0x20($sp)
    CHECK_FR(ctx, 24);
    SD(ctx->f24.u64, 0X20, ctx->r29);
    // 0x801EE070: sw          $a1, 0x74($sp)
    MEM_W(0X74, ctx->r29) = ctx->r5;
    // 0x801EE074: swc1        $f2, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->f2.u32l;
    // 0x801EE078: swc1        $f18, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->f18.u32l;
    // 0x801EE07C: add.s       $f4, $f2, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f4.fl = ctx->f2.fl + ctx->f18.fl;
    // 0x801EE080: sw          $a0, 0x70($sp)
    MEM_W(0X70, ctx->r29) = ctx->r4;
    // 0x801EE084: swc1        $f14, 0x78($sp)
    MEM_W(0X78, ctx->r29) = ctx->f14.u32l;
    // 0x801EE088: jal         0x800C7010
    // 0x801EE08C: add.s       $f12, $f4, $f26
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 26);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f26.fl); 
    ctx->f12.fl = ctx->f4.fl + ctx->f26.fl;
    _nsqrtf(rdram, ctx);
        goto after_0;
    // 0x801EE08C: add.s       $f12, $f4, $f26
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 26);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f26.fl); 
    ctx->f12.fl = ctx->f4.fl + ctx->f26.fl;
    after_0:
    // 0x801EE090: mtc1        $zero, $f6
    ctx->f6.u32l = 0;
    // 0x801EE094: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x801EE098: mtc1        $at, $f12
    ctx->f12.u32l = ctx->r1;
    // 0x801EE09C: c.lt.s      $f6, $f0
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 0);
    c1cs = ctx->f6.fl < ctx->f0.fl;
    // 0x801EE0A0: lw          $a0, 0x70($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X70);
    // 0x801EE0A4: lwc1        $f2, 0x40($sp)
    ctx->f2.u32l = MEM_W(ctx->r29, 0X40);
    // 0x801EE0A8: lwc1        $f14, 0x78($sp)
    ctx->f14.u32l = MEM_W(ctx->r29, 0X78);
    // 0x801EE0AC: bc1f        L_801EE0D4
    if (!c1cs) {
        // 0x801EE0B0: lwc1        $f18, 0x3C($sp)
        ctx->f18.u32l = MEM_W(ctx->r29, 0X3C);
            goto L_801EE0D4;
    }
    // 0x801EE0B0: lwc1        $f18, 0x3C($sp)
    ctx->f18.u32l = MEM_W(ctx->r29, 0X3C);
    // 0x801EE0B4: div.s       $f14, $f14, $f0
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f14.fl = DIV_S(ctx->f14.fl, ctx->f0.fl);
    // 0x801EE0B8: div.s       $f20, $f20, $f0
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f20.fl = DIV_S(ctx->f20.fl, ctx->f0.fl);
    // 0x801EE0BC: mul.s       $f2, $f14, $f14
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f2.fl = MUL_S(ctx->f14.fl, ctx->f14.fl);
    // 0x801EE0C0: div.s       $f22, $f22, $f0
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f22.fl = DIV_S(ctx->f22.fl, ctx->f0.fl);
    // 0x801EE0C4: mul.s       $f18, $f20, $f20
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f18.fl = MUL_S(ctx->f20.fl, ctx->f20.fl);
    // 0x801EE0C8: nop

    // 0x801EE0CC: mul.s       $f26, $f22, $f22
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f26.fl = MUL_S(ctx->f22.fl, ctx->f22.fl);
    // 0x801EE0D0: nop

L_801EE0D4:
    // 0x801EE0D4: lui         $at, 0x43B4
    ctx->r1 = S32(0X43B4 << 16);
    // 0x801EE0D8: mtc1        $at, $f10
    ctx->f10.u32l = ctx->r1;
    // 0x801EE0DC: lwc1        $f8, 0x74($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X74);
    // 0x801EE0E0: lui         $at, 0x4580
    ctx->r1 = S32(0X4580 << 16);
    // 0x801EE0E4: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x801EE0E8: div.s       $f4, $f8, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f4.fl = DIV_S(ctx->f8.fl, ctx->f10.fl);
    // 0x801EE0EC: lui         $v1, 0x8015
    ctx->r3 = S32(0X8015 << 16);
    // 0x801EE0F0: addiu       $v1, $v1, 0x4350
    ctx->r3 = ADD32(ctx->r3, 0X4350);
    // 0x801EE0F4: mtc1        $zero, $f0
    ctx->f0.u32l = 0;
    // 0x801EE0F8: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x801EE0FC: mul.s       $f8, $f4, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = MUL_S(ctx->f4.fl, ctx->f6.fl);
    // 0x801EE100: sub.s       $f6, $f12, $f2
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f6.fl = ctx->f12.fl - ctx->f2.fl;
    // 0x801EE104: trunc.w.s   $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.u32l = TRUNC_W_S(ctx->f8.fl);
    // 0x801EE108: mfc1        $v0, $f10
    ctx->r2 = (int32_t)ctx->f10.u32l;
    // 0x801EE10C: nop

    // 0x801EE110: addiu       $t0, $v0, 0x400
    ctx->r8 = ADD32(ctx->r2, 0X400);
    // 0x801EE114: andi        $t1, $t0, 0xFFF
    ctx->r9 = ctx->r8 & 0XFFF;
    // 0x801EE118: sll         $t2, $t1, 2
    ctx->r10 = S32(ctx->r9 << 2);
    // 0x801EE11C: addu        $t3, $v1, $t2
    ctx->r11 = ADD32(ctx->r3, ctx->r10);
    // 0x801EE120: lwc1        $f24, 0x0($t3)
    ctx->f24.u32l = MEM_W(ctx->r11, 0X0);
    // 0x801EE124: andi        $t7, $v0, 0xFFF
    ctx->r15 = ctx->r2 & 0XFFF;
    // 0x801EE128: sll         $t8, $t7, 2
    ctx->r24 = S32(ctx->r15 << 2);
    // 0x801EE12C: mul.s       $f8, $f6, $f24
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 24);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f24.fl); 
    ctx->f8.fl = MUL_S(ctx->f6.fl, ctx->f24.fl);
    // 0x801EE130: addu        $t9, $v1, $t8
    ctx->r25 = ADD32(ctx->r3, ctx->r24);
    // 0x801EE134: lwc1        $f4, 0x0($t9)
    ctx->f4.u32l = MEM_W(ctx->r25, 0X0);
    // 0x801EE138: swc1        $f4, 0x6C($sp)
    MEM_W(0X6C, ctx->r29) = ctx->f4.u32l;
    // 0x801EE13C: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x801EE140: add.s       $f10, $f8, $f2
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f10.fl = ctx->f8.fl + ctx->f2.fl;
    // 0x801EE144: mul.s       $f8, $f20, $f22
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f8.fl = MUL_S(ctx->f20.fl, ctx->f22.fl);
    // 0x801EE148: swc1        $f0, 0x30($a0)
    MEM_W(0X30, ctx->r4) = ctx->f0.u32l;
    // 0x801EE14C: sub.s       $f6, $f4, $f24
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 24);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f24.fl); 
    ctx->f6.fl = ctx->f4.fl - ctx->f24.fl;
    // 0x801EE150: swc1        $f0, 0x34($a0)
    MEM_W(0X34, ctx->r4) = ctx->f0.u32l;
    // 0x801EE154: swc1        $f0, 0x38($a0)
    MEM_W(0X38, ctx->r4) = ctx->f0.u32l;
    // 0x801EE158: swc1        $f0, 0xC($a0)
    MEM_W(0XC, ctx->r4) = ctx->f0.u32l;
    // 0x801EE15C: swc1        $f0, 0x1C($a0)
    MEM_W(0X1C, ctx->r4) = ctx->f0.u32l;
    // 0x801EE160: swc1        $f0, 0x2C($a0)
    MEM_W(0X2C, ctx->r4) = ctx->f0.u32l;
    // 0x801EE164: swc1        $f12, 0x3C($a0)
    MEM_W(0X3C, ctx->r4) = ctx->f12.u32l;
    // 0x801EE168: swc1        $f10, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->f10.u32l;
    // 0x801EE16C: mul.s       $f0, $f8, $f6
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f0.fl = MUL_S(ctx->f8.fl, ctx->f6.fl);
    // 0x801EE170: lwc1        $f10, 0x6C($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0X6C);
    // 0x801EE174: swc1        $f6, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->f6.u32l;
    // 0x801EE178: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x801EE17C: mul.s       $f12, $f14, $f10
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f12.fl = MUL_S(ctx->f14.fl, ctx->f10.fl);
    // 0x801EE180: sub.s       $f10, $f6, $f18
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f10.fl = ctx->f6.fl - ctx->f18.fl;
    // 0x801EE184: sub.s       $f4, $f0, $f12
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f4.fl = ctx->f0.fl - ctx->f12.fl;
    // 0x801EE188: add.s       $f8, $f12, $f0
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f8.fl = ctx->f12.fl + ctx->f0.fl;
    // 0x801EE18C: swc1        $f4, 0x24($a0)
    MEM_W(0X24, ctx->r4) = ctx->f4.u32l;
    // 0x801EE190: mul.s       $f4, $f10, $f24
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 24);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f24.fl); 
    ctx->f4.fl = MUL_S(ctx->f10.fl, ctx->f24.fl);
    // 0x801EE194: swc1        $f8, 0x18($a0)
    MEM_W(0X18, ctx->r4) = ctx->f8.u32l;
    // 0x801EE198: add.s       $f8, $f4, $f18
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f8.fl = ctx->f4.fl + ctx->f18.fl;
    // 0x801EE19C: swc1        $f8, 0x14($a0)
    MEM_W(0X14, ctx->r4) = ctx->f8.u32l;
    // 0x801EE1A0: lwc1        $f6, 0x6C($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X6C);
    // 0x801EE1A4: lwc1        $f4, 0x40($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X40);
    // 0x801EE1A8: mul.s       $f16, $f20, $f6
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f16.fl = MUL_S(ctx->f20.fl, ctx->f6.fl);
    // 0x801EE1AC: nop

    // 0x801EE1B0: mul.s       $f10, $f22, $f14
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f10.fl = MUL_S(ctx->f22.fl, ctx->f14.fl);
    // 0x801EE1B4: nop

    // 0x801EE1B8: mul.s       $f2, $f10, $f4
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f2.fl = MUL_S(ctx->f10.fl, ctx->f4.fl);
    // 0x801EE1BC: mtc1        $at, $f10
    ctx->f10.u32l = ctx->r1;
    // 0x801EE1C0: nop

    // 0x801EE1C4: sub.s       $f4, $f10, $f26
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 26);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f26.fl); 
    ctx->f4.fl = ctx->f10.fl - ctx->f26.fl;
    // 0x801EE1C8: add.s       $f8, $f16, $f2
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f8.fl = ctx->f16.fl + ctx->f2.fl;
    // 0x801EE1CC: sub.s       $f6, $f2, $f16
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f6.fl = ctx->f2.fl - ctx->f16.fl;
    // 0x801EE1D0: swc1        $f8, 0x20($a0)
    MEM_W(0X20, ctx->r4) = ctx->f8.u32l;
    // 0x801EE1D4: mul.s       $f8, $f4, $f24
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 24);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f24.fl); 
    ctx->f8.fl = MUL_S(ctx->f4.fl, ctx->f24.fl);
    // 0x801EE1D8: swc1        $f6, 0x8($a0)
    MEM_W(0X8, ctx->r4) = ctx->f6.u32l;
    // 0x801EE1DC: mul.s       $f10, $f14, $f20
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f10.fl = MUL_S(ctx->f14.fl, ctx->f20.fl);
    // 0x801EE1E0: add.s       $f6, $f8, $f26
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 26);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f26.fl); 
    ctx->f6.fl = ctx->f8.fl + ctx->f26.fl;
    // 0x801EE1E4: swc1        $f6, 0x28($a0)
    MEM_W(0X28, ctx->r4) = ctx->f6.u32l;
    // 0x801EE1E8: lwc1        $f4, 0x40($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X40);
    // 0x801EE1EC: lwc1        $f8, 0x6C($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X6C);
    // 0x801EE1F0: mul.s       $f0, $f10, $f4
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f0.fl = MUL_S(ctx->f10.fl, ctx->f4.fl);
    // 0x801EE1F4: nop

    // 0x801EE1F8: mul.s       $f2, $f22, $f8
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f2.fl = MUL_S(ctx->f22.fl, ctx->f8.fl);
    // 0x801EE1FC: sub.s       $f6, $f0, $f2
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f6.fl = ctx->f0.fl - ctx->f2.fl;
    // 0x801EE200: add.s       $f10, $f2, $f0
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f10.fl = ctx->f2.fl + ctx->f0.fl;
    // 0x801EE204: swc1        $f6, 0x10($a0)
    MEM_W(0X10, ctx->r4) = ctx->f6.u32l;
    // 0x801EE208: swc1        $f10, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->f10.u32l;
    // 0x801EE20C: lw          $ra, 0x34($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X34);
    // 0x801EE210: ldc1        $f26, 0x28($sp)
    CHECK_FR(ctx, 26);
    ctx->f26.u64 = LD(ctx->r29, 0X28);
    // 0x801EE214: ldc1        $f24, 0x20($sp)
    CHECK_FR(ctx, 24);
    ctx->f24.u64 = LD(ctx->r29, 0X20);
    // 0x801EE218: ldc1        $f22, 0x18($sp)
    CHECK_FR(ctx, 22);
    ctx->f22.u64 = LD(ctx->r29, 0X18);
    // 0x801EE21C: ldc1        $f20, 0x10($sp)
    CHECK_FR(ctx, 20);
    ctx->f20.u64 = LD(ctx->r29, 0X10);
    // 0x801EE220: jr          $ra
    // 0x801EE224: addiu       $sp, $sp, 0x70
    ctx->r29 = ADD32(ctx->r29, 0X70);
    return;
    // 0x801EE224: addiu       $sp, $sp, 0x70
    ctx->r29 = ADD32(ctx->r29, 0X70);
;}
RECOMP_FUNC void func_801EE228(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801EE228: addiu       $sp, $sp, -0x60
    ctx->r29 = ADD32(ctx->r29, -0X60);
    // 0x801EE22C: mtc1        $a1, $f12
    ctx->f12.u32l = ctx->r5;
    // 0x801EE230: mtc1        $a2, $f14
    ctx->f14.u32l = ctx->r6;
    // 0x801EE234: lwc1        $f4, 0x70($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X70);
    // 0x801EE238: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x801EE23C: sw          $a0, 0x60($sp)
    MEM_W(0X60, ctx->r29) = ctx->r4;
    // 0x801EE240: mfc1        $a1, $f12
    ctx->r5 = (int32_t)ctx->f12.u32l;
    // 0x801EE244: mfc1        $a2, $f14
    ctx->r6 = (int32_t)ctx->f14.u32l;
    // 0x801EE248: sw          $a3, 0x6C($sp)
    MEM_W(0X6C, ctx->r29) = ctx->r7;
    // 0x801EE24C: addiu       $a0, $sp, 0x20
    ctx->r4 = ADD32(ctx->r29, 0X20);
    // 0x801EE250: jal         0x801EE040
    // 0x801EE254: swc1        $f4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f4.u32l;
    func_801EE040(rdram, ctx);
        goto after_0;
    // 0x801EE254: swc1        $f4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f4.u32l;
    after_0:
    // 0x801EE258: addiu       $a0, $sp, 0x20
    ctx->r4 = ADD32(ctx->r29, 0X20);
    // 0x801EE25C: jal         0x801EDD90
    // 0x801EE260: lw          $a1, 0x60($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X60);
    _MtxF_to_Mtx(rdram, ctx);
        goto after_1;
    // 0x801EE260: lw          $a1, 0x60($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X60);
    after_1:
    // 0x801EE264: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    // 0x801EE268: addiu       $sp, $sp, 0x60
    ctx->r29 = ADD32(ctx->r29, 0X60);
    // 0x801EE26C: jr          $ra
    // 0x801EE270: nop

    return;
    // 0x801EE270: nop

;}
RECOMP_FUNC void func_801EE274(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801EE274: mtc1        $a2, $f14
    ctx->f14.u32l = ctx->r6;
    // 0x801EE278: addiu       $sp, $sp, -0x68
    ctx->r29 = ADD32(ctx->r29, -0X68);
    // 0x801EE27C: sdc1        $f20, 0x10($sp)
    CHECK_FR(ctx, 20);
    SD(ctx->f20.u64, 0X10, ctx->r29);
    // 0x801EE280: mul.s       $f16, $f14, $f14
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f16.fl = MUL_S(ctx->f14.fl, ctx->f14.fl);
    // 0x801EE284: mtc1        $a3, $f20
    ctx->f20.u32l = ctx->r7;
    // 0x801EE288: sdc1        $f22, 0x18($sp)
    CHECK_FR(ctx, 22);
    SD(ctx->f22.u64, 0X18, ctx->r29);
    // 0x801EE28C: lwc1        $f22, 0x78($sp)
    ctx->f22.u32l = MEM_W(ctx->r29, 0X78);
    // 0x801EE290: mul.s       $f18, $f20, $f20
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f18.fl = MUL_S(ctx->f20.fl, ctx->f20.fl);
    // 0x801EE294: sdc1        $f24, 0x20($sp)
    CHECK_FR(ctx, 24);
    SD(ctx->f24.u64, 0X20, ctx->r29);
    // 0x801EE298: sw          $ra, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r31;
    // 0x801EE29C: mul.s       $f24, $f22, $f22
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f24.fl = MUL_S(ctx->f22.fl, ctx->f22.fl);
    // 0x801EE2A0: sw          $a1, 0x6C($sp)
    MEM_W(0X6C, ctx->r29) = ctx->r5;
    // 0x801EE2A4: swc1        $f16, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->f16.u32l;
    // 0x801EE2A8: sw          $a0, 0x68($sp)
    MEM_W(0X68, ctx->r29) = ctx->r4;
    // 0x801EE2AC: swc1        $f18, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->f18.u32l;
    // 0x801EE2B0: add.s       $f4, $f16, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f4.fl = ctx->f16.fl + ctx->f18.fl;
    // 0x801EE2B4: swc1        $f14, 0x70($sp)
    MEM_W(0X70, ctx->r29) = ctx->f14.u32l;
    // 0x801EE2B8: jal         0x800C7010
    // 0x801EE2BC: add.s       $f12, $f4, $f24
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 24);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f24.fl); 
    ctx->f12.fl = ctx->f4.fl + ctx->f24.fl;
    _nsqrtf(rdram, ctx);
        goto after_0;
    // 0x801EE2BC: add.s       $f12, $f4, $f24
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 24);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f24.fl); 
    ctx->f12.fl = ctx->f4.fl + ctx->f24.fl;
    after_0:
    // 0x801EE2C0: mtc1        $zero, $f6
    ctx->f6.u32l = 0;
    // 0x801EE2C4: lw          $a0, 0x68($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X68);
    // 0x801EE2C8: lwc1        $f14, 0x70($sp)
    ctx->f14.u32l = MEM_W(ctx->r29, 0X70);
    // 0x801EE2CC: c.lt.s      $f6, $f0
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 0);
    c1cs = ctx->f6.fl < ctx->f0.fl;
    // 0x801EE2D0: lwc1        $f16, 0x44($sp)
    ctx->f16.u32l = MEM_W(ctx->r29, 0X44);
    // 0x801EE2D4: lwc1        $f18, 0x40($sp)
    ctx->f18.u32l = MEM_W(ctx->r29, 0X40);
    // 0x801EE2D8: lwc1        $f8, 0x6C($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X6C);
    // 0x801EE2DC: bc1f        L_801EE304
    if (!c1cs) {
        // 0x801EE2E0: lui         $at, 0x43B4
        ctx->r1 = S32(0X43B4 << 16);
            goto L_801EE304;
    }
    // 0x801EE2E0: lui         $at, 0x43B4
    ctx->r1 = S32(0X43B4 << 16);
    // 0x801EE2E4: div.s       $f14, $f14, $f0
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f14.fl = DIV_S(ctx->f14.fl, ctx->f0.fl);
    // 0x801EE2E8: div.s       $f20, $f20, $f0
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f20.fl = DIV_S(ctx->f20.fl, ctx->f0.fl);
    // 0x801EE2EC: mul.s       $f16, $f14, $f14
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f16.fl = MUL_S(ctx->f14.fl, ctx->f14.fl);
    // 0x801EE2F0: div.s       $f22, $f22, $f0
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f22.fl = DIV_S(ctx->f22.fl, ctx->f0.fl);
    // 0x801EE2F4: mul.s       $f18, $f20, $f20
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f18.fl = MUL_S(ctx->f20.fl, ctx->f20.fl);
    // 0x801EE2F8: nop

    // 0x801EE2FC: mul.s       $f24, $f22, $f22
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f24.fl = MUL_S(ctx->f22.fl, ctx->f22.fl);
    // 0x801EE300: nop

L_801EE304:
    // 0x801EE304: mtc1        $at, $f10
    ctx->f10.u32l = ctx->r1;
    // 0x801EE308: lui         $at, 0x4580
    ctx->r1 = S32(0X4580 << 16);
    // 0x801EE30C: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x801EE310: div.s       $f4, $f8, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f4.fl = DIV_S(ctx->f8.fl, ctx->f10.fl);
    // 0x801EE314: lui         $v1, 0x8015
    ctx->r3 = S32(0X8015 << 16);
    // 0x801EE318: addiu       $v1, $v1, 0x4350
    ctx->r3 = ADD32(ctx->r3, 0X4350);
    // 0x801EE31C: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x801EE320: mtc1        $zero, $f0
    ctx->f0.u32l = 0;
    // 0x801EE324: mul.s       $f8, $f4, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = MUL_S(ctx->f4.fl, ctx->f6.fl);
    // 0x801EE328: lwc1        $f6, 0x7C($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X7C);
    // 0x801EE32C: trunc.w.s   $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.u32l = TRUNC_W_S(ctx->f8.fl);
    // 0x801EE330: mfc1        $v0, $f10
    ctx->r2 = (int32_t)ctx->f10.u32l;
    // 0x801EE334: nop

    // 0x801EE338: andi        $t7, $v0, 0xFFF
    ctx->r15 = ctx->r2 & 0XFFF;
    // 0x801EE33C: sll         $t8, $t7, 2
    ctx->r24 = S32(ctx->r15 << 2);
    // 0x801EE340: addu        $t9, $v1, $t8
    ctx->r25 = ADD32(ctx->r3, ctx->r24);
    // 0x801EE344: addiu       $t0, $v0, 0x400
    ctx->r8 = ADD32(ctx->r2, 0X400);
    // 0x801EE348: lwc1        $f4, 0x0($t9)
    ctx->f4.u32l = MEM_W(ctx->r25, 0X0);
    // 0x801EE34C: andi        $t1, $t0, 0xFFF
    ctx->r9 = ctx->r8 & 0XFFF;
    // 0x801EE350: sll         $t2, $t1, 2
    ctx->r10 = S32(ctx->r9 << 2);
    // 0x801EE354: addu        $t3, $v1, $t2
    ctx->r11 = ADD32(ctx->r3, ctx->r10);
    // 0x801EE358: lwc1        $f12, 0x0($t3)
    ctx->f12.u32l = MEM_W(ctx->r11, 0X0);
    // 0x801EE35C: swc1        $f4, 0x64($sp)
    MEM_W(0X64, ctx->r29) = ctx->f4.u32l;
    // 0x801EE360: swc1        $f6, 0x30($a0)
    MEM_W(0X30, ctx->r4) = ctx->f6.u32l;
    // 0x801EE364: lwc1        $f8, 0x80($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X80);
    // 0x801EE368: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x801EE36C: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x801EE370: swc1        $f8, 0x34($a0)
    MEM_W(0X34, ctx->r4) = ctx->f8.u32l;
    // 0x801EE374: sub.s       $f8, $f6, $f16
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f8.fl = ctx->f6.fl - ctx->f16.fl;
    // 0x801EE378: lwc1        $f10, 0x84($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0X84);
    // 0x801EE37C: swc1        $f4, 0x3C($a0)
    MEM_W(0X3C, ctx->r4) = ctx->f4.u32l;
    // 0x801EE380: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x801EE384: swc1        $f10, 0x38($a0)
    MEM_W(0X38, ctx->r4) = ctx->f10.u32l;
    // 0x801EE388: mul.s       $f10, $f8, $f12
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f10.fl = MUL_S(ctx->f8.fl, ctx->f12.fl);
    // 0x801EE38C: sub.s       $f8, $f6, $f12
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f8.fl = ctx->f6.fl - ctx->f12.fl;
    // 0x801EE390: swc1        $f0, 0xC($a0)
    MEM_W(0XC, ctx->r4) = ctx->f0.u32l;
    // 0x801EE394: swc1        $f0, 0x1C($a0)
    MEM_W(0X1C, ctx->r4) = ctx->f0.u32l;
    // 0x801EE398: swc1        $f0, 0x2C($a0)
    MEM_W(0X2C, ctx->r4) = ctx->f0.u32l;
    // 0x801EE39C: add.s       $f4, $f10, $f16
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f4.fl = ctx->f10.fl + ctx->f16.fl;
    // 0x801EE3A0: mul.s       $f10, $f20, $f22
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f10.fl = MUL_S(ctx->f20.fl, ctx->f22.fl);
    // 0x801EE3A4: swc1        $f4, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->f4.u32l;
    // 0x801EE3A8: lwc1        $f4, 0x64($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X64);
    // 0x801EE3AC: swc1        $f8, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->f8.u32l;
    // 0x801EE3B0: mul.s       $f0, $f10, $f8
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f0.fl = MUL_S(ctx->f10.fl, ctx->f8.fl);
    // 0x801EE3B4: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x801EE3B8: mul.s       $f2, $f14, $f4
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f2.fl = MUL_S(ctx->f14.fl, ctx->f4.fl);
    // 0x801EE3BC: sub.s       $f4, $f8, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f4.fl = ctx->f8.fl - ctx->f18.fl;
    // 0x801EE3C0: sub.s       $f6, $f0, $f2
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f6.fl = ctx->f0.fl - ctx->f2.fl;
    // 0x801EE3C4: add.s       $f10, $f2, $f0
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f10.fl = ctx->f2.fl + ctx->f0.fl;
    // 0x801EE3C8: swc1        $f6, 0x24($a0)
    MEM_W(0X24, ctx->r4) = ctx->f6.u32l;
    // 0x801EE3CC: mul.s       $f6, $f4, $f12
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f6.fl = MUL_S(ctx->f4.fl, ctx->f12.fl);
    // 0x801EE3D0: swc1        $f10, 0x18($a0)
    MEM_W(0X18, ctx->r4) = ctx->f10.u32l;
    // 0x801EE3D4: add.s       $f10, $f6, $f18
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f10.fl = ctx->f6.fl + ctx->f18.fl;
    // 0x801EE3D8: swc1        $f10, 0x14($a0)
    MEM_W(0X14, ctx->r4) = ctx->f10.u32l;
    // 0x801EE3DC: lwc1        $f8, 0x64($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X64);
    // 0x801EE3E0: lwc1        $f10, 0x38($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0X38);
    // 0x801EE3E4: mul.s       $f4, $f20, $f8
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f4.fl = MUL_S(ctx->f20.fl, ctx->f8.fl);
    // 0x801EE3E8: nop

    // 0x801EE3EC: mul.s       $f6, $f22, $f14
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f6.fl = MUL_S(ctx->f22.fl, ctx->f14.fl);
    // 0x801EE3F0: swc1        $f4, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->f4.u32l;
    // 0x801EE3F4: lwc1        $f4, 0x30($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X30);
    // 0x801EE3F8: mul.s       $f8, $f6, $f10
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f8.fl = MUL_S(ctx->f6.fl, ctx->f10.fl);
    // 0x801EE3FC: add.s       $f6, $f4, $f8
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f6.fl = ctx->f4.fl + ctx->f8.fl;
    // 0x801EE400: swc1        $f8, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->f8.u32l;
    // 0x801EE404: swc1        $f6, 0x20($a0)
    MEM_W(0X20, ctx->r4) = ctx->f6.u32l;
    // 0x801EE408: lwc1        $f4, 0x30($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X30);
    // 0x801EE40C: lwc1        $f10, 0x34($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0X34);
    // 0x801EE410: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x801EE414: sub.s       $f8, $f10, $f4
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f8.fl = ctx->f10.fl - ctx->f4.fl;
    // 0x801EE418: sub.s       $f10, $f6, $f24
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 24);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f24.fl); 
    ctx->f10.fl = ctx->f6.fl - ctx->f24.fl;
    // 0x801EE41C: swc1        $f8, 0x8($a0)
    MEM_W(0X8, ctx->r4) = ctx->f8.u32l;
    // 0x801EE420: mul.s       $f4, $f10, $f12
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f4.fl = MUL_S(ctx->f10.fl, ctx->f12.fl);
    // 0x801EE424: add.s       $f8, $f4, $f24
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 24);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f24.fl); 
    ctx->f8.fl = ctx->f4.fl + ctx->f24.fl;
    // 0x801EE428: mul.s       $f6, $f14, $f20
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f6.fl = MUL_S(ctx->f14.fl, ctx->f20.fl);
    // 0x801EE42C: swc1        $f8, 0x28($a0)
    MEM_W(0X28, ctx->r4) = ctx->f8.u32l;
    // 0x801EE430: lwc1        $f10, 0x38($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0X38);
    // 0x801EE434: lwc1        $f4, 0x64($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X64);
    // 0x801EE438: mul.s       $f0, $f6, $f10
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f0.fl = MUL_S(ctx->f6.fl, ctx->f10.fl);
    // 0x801EE43C: nop

    // 0x801EE440: mul.s       $f2, $f22, $f4
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f2.fl = MUL_S(ctx->f22.fl, ctx->f4.fl);
    // 0x801EE444: sub.s       $f8, $f0, $f2
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f8.fl = ctx->f0.fl - ctx->f2.fl;
    // 0x801EE448: add.s       $f6, $f2, $f0
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f6.fl = ctx->f2.fl + ctx->f0.fl;
    // 0x801EE44C: swc1        $f8, 0x10($a0)
    MEM_W(0X10, ctx->r4) = ctx->f8.u32l;
    // 0x801EE450: swc1        $f6, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->f6.u32l;
    // 0x801EE454: lw          $ra, 0x2C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X2C);
    // 0x801EE458: ldc1        $f24, 0x20($sp)
    CHECK_FR(ctx, 24);
    ctx->f24.u64 = LD(ctx->r29, 0X20);
    // 0x801EE45C: ldc1        $f22, 0x18($sp)
    CHECK_FR(ctx, 22);
    ctx->f22.u64 = LD(ctx->r29, 0X18);
    // 0x801EE460: ldc1        $f20, 0x10($sp)
    CHECK_FR(ctx, 20);
    ctx->f20.u64 = LD(ctx->r29, 0X10);
    // 0x801EE464: jr          $ra
    // 0x801EE468: addiu       $sp, $sp, 0x68
    ctx->r29 = ADD32(ctx->r29, 0X68);
    return;
    // 0x801EE468: addiu       $sp, $sp, 0x68
    ctx->r29 = ADD32(ctx->r29, 0X68);
;}
RECOMP_FUNC void func_801EE46C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801EE46C: addiu       $sp, $sp, -0x68
    ctx->r29 = ADD32(ctx->r29, -0X68);
    // 0x801EE470: mtc1        $a1, $f12
    ctx->f12.u32l = ctx->r5;
    // 0x801EE474: mtc1        $a2, $f14
    ctx->f14.u32l = ctx->r6;
    // 0x801EE478: lwc1        $f4, 0x78($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X78);
    // 0x801EE47C: lwc1        $f6, 0x7C($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X7C);
    // 0x801EE480: lwc1        $f8, 0x80($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X80);
    // 0x801EE484: lwc1        $f10, 0x84($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0X84);
    // 0x801EE488: sw          $ra, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r31;
    // 0x801EE48C: sw          $a0, 0x68($sp)
    MEM_W(0X68, ctx->r29) = ctx->r4;
    // 0x801EE490: mfc1        $a1, $f12
    ctx->r5 = (int32_t)ctx->f12.u32l;
    // 0x801EE494: mfc1        $a2, $f14
    ctx->r6 = (int32_t)ctx->f14.u32l;
    // 0x801EE498: sw          $a3, 0x74($sp)
    MEM_W(0X74, ctx->r29) = ctx->r7;
    // 0x801EE49C: addiu       $a0, $sp, 0x28
    ctx->r4 = ADD32(ctx->r29, 0X28);
    // 0x801EE4A0: swc1        $f4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f4.u32l;
    // 0x801EE4A4: swc1        $f6, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->f6.u32l;
    // 0x801EE4A8: swc1        $f8, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->f8.u32l;
    // 0x801EE4AC: jal         0x801EE274
    // 0x801EE4B0: swc1        $f10, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->f10.u32l;
    func_801EE274(rdram, ctx);
        goto after_0;
    // 0x801EE4B0: swc1        $f10, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->f10.u32l;
    after_0:
    // 0x801EE4B4: addiu       $a0, $sp, 0x28
    ctx->r4 = ADD32(ctx->r29, 0X28);
    // 0x801EE4B8: jal         0x801EDD90
    // 0x801EE4BC: lw          $a1, 0x68($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X68);
    _MtxF_to_Mtx(rdram, ctx);
        goto after_1;
    // 0x801EE4BC: lw          $a1, 0x68($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X68);
    after_1:
    // 0x801EE4C0: lw          $ra, 0x24($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X24);
    // 0x801EE4C4: addiu       $sp, $sp, 0x68
    ctx->r29 = ADD32(ctx->r29, 0X68);
    // 0x801EE4C8: jr          $ra
    // 0x801EE4CC: nop

    return;
    // 0x801EE4CC: nop

;}
RECOMP_FUNC void func_801EE4D0(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801EE4D0: addiu       $sp, $sp, -0x28
    ctx->r29 = ADD32(ctx->r29, -0X28);
    // 0x801EE4D4: sw          $a1, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r5;
    // 0x801EE4D8: lui         $at, 0x43B4
    ctx->r1 = S32(0X43B4 << 16);
    // 0x801EE4DC: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x801EE4E0: lwc1        $f4, 0x2C($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X2C);
    // 0x801EE4E4: lui         $at, 0x4580
    ctx->r1 = S32(0X4580 << 16);
    // 0x801EE4E8: mtc1        $at, $f10
    ctx->f10.u32l = ctx->r1;
    // 0x801EE4EC: div.s       $f8, $f4, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = DIV_S(ctx->f4.fl, ctx->f6.fl);
    // 0x801EE4F0: sw          $a2, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r6;
    // 0x801EE4F4: lui         $at, 0x43B4
    ctx->r1 = S32(0X43B4 << 16);
    // 0x801EE4F8: sw          $a3, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r7;
    // 0x801EE4FC: lui         $a2, 0x8015
    ctx->r6 = S32(0X8015 << 16);
    // 0x801EE500: addiu       $a2, $a2, 0x4350
    ctx->r6 = ADD32(ctx->r6, 0X4350);
    // 0x801EE504: mul.s       $f4, $f8, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f4.fl = MUL_S(ctx->f8.fl, ctx->f10.fl);
    // 0x801EE508: mtc1        $at, $f10
    ctx->f10.u32l = ctx->r1;
    // 0x801EE50C: lwc1        $f8, 0x30($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X30);
    // 0x801EE510: lui         $at, 0x4580
    ctx->r1 = S32(0X4580 << 16);
    // 0x801EE514: trunc.w.s   $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.u32l = TRUNC_W_S(ctx->f4.fl);
    // 0x801EE518: div.s       $f4, $f8, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f4.fl = DIV_S(ctx->f8.fl, ctx->f10.fl);
    // 0x801EE51C: mfc1        $v0, $f6
    ctx->r2 = (int32_t)ctx->f6.u32l;
    // 0x801EE520: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x801EE524: lui         $at, 0x43B4
    ctx->r1 = S32(0X43B4 << 16);
    // 0x801EE528: andi        $t7, $v0, 0xFFF
    ctx->r15 = ctx->r2 & 0XFFF;
    // 0x801EE52C: sll         $t8, $t7, 2
    ctx->r24 = S32(ctx->r15 << 2);
    // 0x801EE530: addu        $t9, $a2, $t8
    ctx->r25 = ADD32(ctx->r6, ctx->r24);
    // 0x801EE534: lwc1        $f12, 0x0($t9)
    ctx->f12.u32l = MEM_W(ctx->r25, 0X0);
    // 0x801EE538: addiu       $t8, $v0, 0x400
    ctx->r24 = ADD32(ctx->r2, 0X400);
    // 0x801EE53C: andi        $t9, $t8, 0xFFF
    ctx->r25 = ctx->r24 & 0XFFF;
    // 0x801EE540: sll         $t0, $t9, 2
    ctx->r8 = S32(ctx->r25 << 2);
    // 0x801EE544: mul.s       $f8, $f4, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = MUL_S(ctx->f4.fl, ctx->f6.fl);
    // 0x801EE548: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x801EE54C: lwc1        $f4, 0x34($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X34);
    // 0x801EE550: lui         $at, 0x4580
    ctx->r1 = S32(0X4580 << 16);
    // 0x801EE554: trunc.w.s   $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.u32l = TRUNC_W_S(ctx->f8.fl);
    // 0x801EE558: div.s       $f8, $f4, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = DIV_S(ctx->f4.fl, ctx->f6.fl);
    // 0x801EE55C: mfc1        $v1, $f10
    ctx->r3 = (int32_t)ctx->f10.u32l;
    // 0x801EE560: mtc1        $at, $f10
    ctx->f10.u32l = ctx->r1;
    // 0x801EE564: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x801EE568: andi        $t1, $v1, 0xFFF
    ctx->r9 = ctx->r3 & 0XFFF;
    // 0x801EE56C: sll         $t2, $t1, 2
    ctx->r10 = S32(ctx->r9 << 2);
    // 0x801EE570: addu        $t3, $a2, $t2
    ctx->r11 = ADD32(ctx->r6, ctx->r10);
    // 0x801EE574: lwc1        $f18, 0x0($t3)
    ctx->f18.u32l = MEM_W(ctx->r11, 0X0);
    // 0x801EE578: addiu       $t2, $v1, 0x400
    ctx->r10 = ADD32(ctx->r3, 0X400);
    // 0x801EE57C: andi        $t3, $t2, 0xFFF
    ctx->r11 = ctx->r10 & 0XFFF;
    // 0x801EE580: sll         $t4, $t3, 2
    ctx->r12 = S32(ctx->r11 << 2);
    // 0x801EE584: addu        $t1, $a2, $t0
    ctx->r9 = ADD32(ctx->r6, ctx->r8);
    // 0x801EE588: lwc1        $f14, 0x0($t1)
    ctx->f14.u32l = MEM_W(ctx->r9, 0X0);
    // 0x801EE58C: mul.s       $f4, $f8, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f4.fl = MUL_S(ctx->f8.fl, ctx->f10.fl);
    // 0x801EE590: trunc.w.s   $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.u32l = TRUNC_W_S(ctx->f4.fl);
    // 0x801EE594: neg.s       $f4, $f14
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f14.fl); 
    ctx->f4.fl = -ctx->f14.fl;
    // 0x801EE598: mfc1        $a1, $f6
    ctx->r5 = (int32_t)ctx->f6.u32l;
    // 0x801EE59C: nop

    // 0x801EE5A0: andi        $t5, $a1, 0xFFF
    ctx->r13 = ctx->r5 & 0XFFF;
    // 0x801EE5A4: sll         $t6, $t5, 2
    ctx->r14 = S32(ctx->r13 << 2);
    // 0x801EE5A8: addu        $t7, $a2, $t6
    ctx->r15 = ADD32(ctx->r6, ctx->r14);
    // 0x801EE5AC: lwc1        $f0, 0x0($t7)
    ctx->f0.u32l = MEM_W(ctx->r15, 0X0);
    // 0x801EE5B0: addiu       $t6, $a1, 0x400
    ctx->r14 = ADD32(ctx->r5, 0X400);
    // 0x801EE5B4: andi        $t7, $t6, 0xFFF
    ctx->r15 = ctx->r14 & 0XFFF;
    // 0x801EE5B8: sll         $t8, $t7, 2
    ctx->r24 = S32(ctx->r15 << 2);
    // 0x801EE5BC: addu        $t5, $a2, $t4
    ctx->r13 = ADD32(ctx->r6, ctx->r12);
    // 0x801EE5C0: addu        $t9, $a2, $t8
    ctx->r25 = ADD32(ctx->r6, ctx->r24);
    // 0x801EE5C4: lwc1        $f16, 0x0($t5)
    ctx->f16.u32l = MEM_W(ctx->r13, 0X0);
    // 0x801EE5C8: lwc1        $f2, 0x0($t9)
    ctx->f2.u32l = MEM_W(ctx->r25, 0X0);
    // 0x801EE5CC: mul.s       $f8, $f16, $f2
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f8.fl = MUL_S(ctx->f16.fl, ctx->f2.fl);
    // 0x801EE5D0: nop

    // 0x801EE5D4: mul.s       $f10, $f12, $f18
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f10.fl = MUL_S(ctx->f12.fl, ctx->f18.fl);
    // 0x801EE5D8: nop

    // 0x801EE5DC: mul.s       $f6, $f4, $f0
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f6.fl = MUL_S(ctx->f4.fl, ctx->f0.fl);
    // 0x801EE5E0: swc1        $f8, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->f8.u32l;
    // 0x801EE5E4: swc1        $f10, 0x8($sp)
    MEM_W(0X8, ctx->r29) = ctx->f10.u32l;
    // 0x801EE5E8: lwc1        $f8, 0x8($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X8);
    // 0x801EE5EC: mul.s       $f10, $f8, $f2
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f10.fl = MUL_S(ctx->f8.fl, ctx->f2.fl);
    // 0x801EE5F0: add.s       $f4, $f6, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f4.fl = ctx->f6.fl + ctx->f10.fl;
    // 0x801EE5F4: mul.s       $f8, $f14, $f18
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f8.fl = MUL_S(ctx->f14.fl, ctx->f18.fl);
    // 0x801EE5F8: swc1        $f4, 0x10($a0)
    MEM_W(0X10, ctx->r4) = ctx->f4.u32l;
    // 0x801EE5FC: mul.s       $f6, $f12, $f0
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f6.fl = MUL_S(ctx->f12.fl, ctx->f0.fl);
    // 0x801EE600: swc1        $f8, 0x4($sp)
    MEM_W(0X4, ctx->r29) = ctx->f8.u32l;
    // 0x801EE604: lwc1        $f10, 0x4($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0X4);
    // 0x801EE608: mul.s       $f4, $f10, $f2
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f4.fl = MUL_S(ctx->f10.fl, ctx->f2.fl);
    // 0x801EE60C: add.s       $f8, $f6, $f4
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f8.fl = ctx->f6.fl + ctx->f4.fl;
    // 0x801EE610: mul.s       $f6, $f16, $f0
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f6.fl = MUL_S(ctx->f16.fl, ctx->f0.fl);
    // 0x801EE614: swc1        $f8, 0x20($a0)
    MEM_W(0X20, ctx->r4) = ctx->f8.u32l;
    // 0x801EE618: lwc1        $f10, 0x38($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0X38);
    // 0x801EE61C: mul.s       $f4, $f14, $f2
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f4.fl = MUL_S(ctx->f14.fl, ctx->f2.fl);
    // 0x801EE620: swc1        $f6, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->f6.u32l;
    // 0x801EE624: swc1        $f10, 0x30($a0)
    MEM_W(0X30, ctx->r4) = ctx->f10.u32l;
    // 0x801EE628: lwc1        $f8, 0x8($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X8);
    // 0x801EE62C: mul.s       $f10, $f8, $f0
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f10.fl = MUL_S(ctx->f8.fl, ctx->f0.fl);
    // 0x801EE630: neg.s       $f8, $f12
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f12.fl); 
    ctx->f8.fl = -ctx->f12.fl;
    // 0x801EE634: add.s       $f6, $f4, $f10
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f6.fl = ctx->f4.fl + ctx->f10.fl;
    // 0x801EE638: mul.s       $f4, $f8, $f2
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f4.fl = MUL_S(ctx->f8.fl, ctx->f2.fl);
    // 0x801EE63C: swc1        $f6, 0x14($a0)
    MEM_W(0X14, ctx->r4) = ctx->f6.u32l;
    // 0x801EE640: lwc1        $f10, 0x4($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0X4);
    // 0x801EE644: mul.s       $f6, $f10, $f0
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f6.fl = MUL_S(ctx->f10.fl, ctx->f0.fl);
    // 0x801EE648: mtc1        $zero, $f0
    ctx->f0.u32l = 0;
    // 0x801EE64C: add.s       $f8, $f4, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = ctx->f4.fl + ctx->f6.fl;
    // 0x801EE650: mul.s       $f6, $f12, $f16
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f6.fl = MUL_S(ctx->f12.fl, ctx->f16.fl);
    // 0x801EE654: neg.s       $f4, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f18.fl); 
    ctx->f4.fl = -ctx->f18.fl;
    // 0x801EE658: swc1        $f8, 0x24($a0)
    MEM_W(0X24, ctx->r4) = ctx->f8.u32l;
    // 0x801EE65C: mul.s       $f8, $f14, $f16
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f8.fl = MUL_S(ctx->f14.fl, ctx->f16.fl);
    // 0x801EE660: lwc1        $f10, 0x3C($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0X3C);
    // 0x801EE664: swc1        $f4, 0x8($a0)
    MEM_W(0X8, ctx->r4) = ctx->f4.u32l;
    // 0x801EE668: swc1        $f6, 0x18($a0)
    MEM_W(0X18, ctx->r4) = ctx->f6.u32l;
    // 0x801EE66C: swc1        $f10, 0x34($a0)
    MEM_W(0X34, ctx->r4) = ctx->f10.u32l;
    // 0x801EE670: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x801EE674: swc1        $f8, 0x28($a0)
    MEM_W(0X28, ctx->r4) = ctx->f8.u32l;
    // 0x801EE678: lwc1        $f10, 0x40($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0X40);
    // 0x801EE67C: addiu       $sp, $sp, 0x28
    ctx->r29 = ADD32(ctx->r29, 0X28);
    // 0x801EE680: swc1        $f0, 0xC($a0)
    MEM_W(0XC, ctx->r4) = ctx->f0.u32l;
    // 0x801EE684: swc1        $f0, 0x1C($a0)
    MEM_W(0X1C, ctx->r4) = ctx->f0.u32l;
    // 0x801EE688: swc1        $f0, 0x2C($a0)
    MEM_W(0X2C, ctx->r4) = ctx->f0.u32l;
    // 0x801EE68C: swc1        $f4, 0x3C($a0)
    MEM_W(0X3C, ctx->r4) = ctx->f4.u32l;
    // 0x801EE690: jr          $ra
    // 0x801EE694: swc1        $f10, 0x38($a0)
    MEM_W(0X38, ctx->r4) = ctx->f10.u32l;
    return;
    // 0x801EE694: swc1        $f10, 0x38($a0)
    MEM_W(0X38, ctx->r4) = ctx->f10.u32l;
;}
RECOMP_FUNC void func_801EE698(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801EE698: addiu       $sp, $sp, -0x68
    ctx->r29 = ADD32(ctx->r29, -0X68);
    // 0x801EE69C: mtc1        $a1, $f12
    ctx->f12.u32l = ctx->r5;
    // 0x801EE6A0: mtc1        $a2, $f14
    ctx->f14.u32l = ctx->r6;
    // 0x801EE6A4: lwc1        $f4, 0x78($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X78);
    // 0x801EE6A8: lwc1        $f6, 0x7C($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X7C);
    // 0x801EE6AC: lwc1        $f8, 0x80($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X80);
    // 0x801EE6B0: sw          $ra, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r31;
    // 0x801EE6B4: sw          $a0, 0x68($sp)
    MEM_W(0X68, ctx->r29) = ctx->r4;
    // 0x801EE6B8: mfc1        $a1, $f12
    ctx->r5 = (int32_t)ctx->f12.u32l;
    // 0x801EE6BC: mfc1        $a2, $f14
    ctx->r6 = (int32_t)ctx->f14.u32l;
    // 0x801EE6C0: sw          $a3, 0x74($sp)
    MEM_W(0X74, ctx->r29) = ctx->r7;
    // 0x801EE6C4: addiu       $a0, $sp, 0x28
    ctx->r4 = ADD32(ctx->r29, 0X28);
    // 0x801EE6C8: swc1        $f4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f4.u32l;
    // 0x801EE6CC: swc1        $f6, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->f6.u32l;
    // 0x801EE6D0: jal         0x801EE4D0
    // 0x801EE6D4: swc1        $f8, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->f8.u32l;
    func_801EE4D0(rdram, ctx);
        goto after_0;
    // 0x801EE6D4: swc1        $f8, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->f8.u32l;
    after_0:
    // 0x801EE6D8: addiu       $a0, $sp, 0x28
    ctx->r4 = ADD32(ctx->r29, 0X28);
    // 0x801EE6DC: jal         0x801EDD90
    // 0x801EE6E0: lw          $a1, 0x68($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X68);
    _MtxF_to_Mtx(rdram, ctx);
        goto after_1;
    // 0x801EE6E0: lw          $a1, 0x68($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X68);
    after_1:
    // 0x801EE6E4: lw          $ra, 0x24($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X24);
    // 0x801EE6E8: addiu       $sp, $sp, 0x68
    ctx->r29 = ADD32(ctx->r29, 0X68);
    // 0x801EE6EC: jr          $ra
    // 0x801EE6F0: nop

    return;
    // 0x801EE6F0: nop

;}
RECOMP_FUNC void func_801EE6F4(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801EE6F4: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x801EE6F8: sw          $a1, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r5;
    // 0x801EE6FC: lui         $at, 0x43B4
    ctx->r1 = S32(0X43B4 << 16);
    // 0x801EE700: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x801EE704: lwc1        $f4, 0x24($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X24);
    // 0x801EE708: lui         $at, 0x4580
    ctx->r1 = S32(0X4580 << 16);
    // 0x801EE70C: mtc1        $at, $f10
    ctx->f10.u32l = ctx->r1;
    // 0x801EE710: div.s       $f8, $f4, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = DIV_S(ctx->f4.fl, ctx->f6.fl);
    // 0x801EE714: sw          $a2, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r6;
    // 0x801EE718: lui         $at, 0x43B4
    ctx->r1 = S32(0X43B4 << 16);
    // 0x801EE71C: sw          $a3, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r7;
    // 0x801EE720: lui         $a2, 0x8015
    ctx->r6 = S32(0X8015 << 16);
    // 0x801EE724: addiu       $a2, $a2, 0x4350
    ctx->r6 = ADD32(ctx->r6, 0X4350);
    // 0x801EE728: mul.s       $f4, $f8, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f4.fl = MUL_S(ctx->f8.fl, ctx->f10.fl);
    // 0x801EE72C: mtc1        $at, $f10
    ctx->f10.u32l = ctx->r1;
    // 0x801EE730: lwc1        $f8, 0x28($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X28);
    // 0x801EE734: lui         $at, 0x4580
    ctx->r1 = S32(0X4580 << 16);
    // 0x801EE738: trunc.w.s   $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.u32l = TRUNC_W_S(ctx->f4.fl);
    // 0x801EE73C: div.s       $f4, $f8, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f4.fl = DIV_S(ctx->f8.fl, ctx->f10.fl);
    // 0x801EE740: mfc1        $v0, $f6
    ctx->r2 = (int32_t)ctx->f6.u32l;
    // 0x801EE744: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x801EE748: lui         $at, 0x43B4
    ctx->r1 = S32(0X43B4 << 16);
    // 0x801EE74C: andi        $t7, $v0, 0xFFF
    ctx->r15 = ctx->r2 & 0XFFF;
    // 0x801EE750: sll         $t8, $t7, 2
    ctx->r24 = S32(ctx->r15 << 2);
    // 0x801EE754: addu        $t9, $a2, $t8
    ctx->r25 = ADD32(ctx->r6, ctx->r24);
    // 0x801EE758: lwc1        $f18, 0x0($t9)
    ctx->f18.u32l = MEM_W(ctx->r25, 0X0);
    // 0x801EE75C: addiu       $t8, $v0, 0x400
    ctx->r24 = ADD32(ctx->r2, 0X400);
    // 0x801EE760: andi        $t9, $t8, 0xFFF
    ctx->r25 = ctx->r24 & 0XFFF;
    // 0x801EE764: sll         $t0, $t9, 2
    ctx->r8 = S32(ctx->r25 << 2);
    // 0x801EE768: mul.s       $f8, $f4, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = MUL_S(ctx->f4.fl, ctx->f6.fl);
    // 0x801EE76C: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x801EE770: lwc1        $f4, 0x2C($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X2C);
    // 0x801EE774: lui         $at, 0x4580
    ctx->r1 = S32(0X4580 << 16);
    // 0x801EE778: trunc.w.s   $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.u32l = TRUNC_W_S(ctx->f8.fl);
    // 0x801EE77C: div.s       $f8, $f4, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = DIV_S(ctx->f4.fl, ctx->f6.fl);
    // 0x801EE780: mfc1        $v1, $f10
    ctx->r3 = (int32_t)ctx->f10.u32l;
    // 0x801EE784: mtc1        $at, $f10
    ctx->f10.u32l = ctx->r1;
    // 0x801EE788: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x801EE78C: andi        $t1, $v1, 0xFFF
    ctx->r9 = ctx->r3 & 0XFFF;
    // 0x801EE790: sll         $t2, $t1, 2
    ctx->r10 = S32(ctx->r9 << 2);
    // 0x801EE794: addu        $t3, $a2, $t2
    ctx->r11 = ADD32(ctx->r6, ctx->r10);
    // 0x801EE798: lwc1        $f12, 0x0($t3)
    ctx->f12.u32l = MEM_W(ctx->r11, 0X0);
    // 0x801EE79C: addiu       $t2, $v1, 0x400
    ctx->r10 = ADD32(ctx->r3, 0X400);
    // 0x801EE7A0: andi        $t3, $t2, 0xFFF
    ctx->r11 = ctx->r10 & 0XFFF;
    // 0x801EE7A4: sll         $t4, $t3, 2
    ctx->r12 = S32(ctx->r11 << 2);
    // 0x801EE7A8: addu        $t1, $a2, $t0
    ctx->r9 = ADD32(ctx->r6, ctx->r8);
    // 0x801EE7AC: lwc1        $f14, 0x0($t1)
    ctx->f14.u32l = MEM_W(ctx->r9, 0X0);
    // 0x801EE7B0: mul.s       $f4, $f8, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f4.fl = MUL_S(ctx->f8.fl, ctx->f10.fl);
    // 0x801EE7B4: trunc.w.s   $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.u32l = TRUNC_W_S(ctx->f4.fl);
    // 0x801EE7B8: mul.s       $f8, $f18, $f12
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f8.fl = MUL_S(ctx->f18.fl, ctx->f12.fl);
    // 0x801EE7BC: mfc1        $a1, $f6
    ctx->r5 = (int32_t)ctx->f6.u32l;
    // 0x801EE7C0: nop

    // 0x801EE7C4: andi        $t5, $a1, 0xFFF
    ctx->r13 = ctx->r5 & 0XFFF;
    // 0x801EE7C8: sll         $t6, $t5, 2
    ctx->r14 = S32(ctx->r13 << 2);
    // 0x801EE7CC: addu        $t7, $a2, $t6
    ctx->r15 = ADD32(ctx->r6, ctx->r14);
    // 0x801EE7D0: lwc1        $f0, 0x0($t7)
    ctx->f0.u32l = MEM_W(ctx->r15, 0X0);
    // 0x801EE7D4: addiu       $t6, $a1, 0x400
    ctx->r14 = ADD32(ctx->r5, 0X400);
    // 0x801EE7D8: andi        $t7, $t6, 0xFFF
    ctx->r15 = ctx->r14 & 0XFFF;
    // 0x801EE7DC: sll         $t8, $t7, 2
    ctx->r24 = S32(ctx->r15 << 2);
    // 0x801EE7E0: addu        $t5, $a2, $t4
    ctx->r13 = ADD32(ctx->r6, ctx->r12);
    // 0x801EE7E4: addu        $t9, $a2, $t8
    ctx->r25 = ADD32(ctx->r6, ctx->r24);
    // 0x801EE7E8: lwc1        $f16, 0x0($t5)
    ctx->f16.u32l = MEM_W(ctx->r13, 0X0);
    // 0x801EE7EC: lwc1        $f2, 0x0($t9)
    ctx->f2.u32l = MEM_W(ctx->r25, 0X0);
    // 0x801EE7F0: swc1        $f8, 0x0($sp)
    MEM_W(0X0, ctx->r29) = ctx->f8.u32l;
    // 0x801EE7F4: lwc1        $f10, 0x0($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0X0);
    // 0x801EE7F8: mul.s       $f4, $f10, $f0
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f4.fl = MUL_S(ctx->f10.fl, ctx->f0.fl);
    // 0x801EE7FC: nop

    // 0x801EE800: mul.s       $f6, $f16, $f2
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f6.fl = MUL_S(ctx->f16.fl, ctx->f2.fl);
    // 0x801EE804: add.s       $f8, $f4, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = ctx->f4.fl + ctx->f6.fl;
    // 0x801EE808: swc1        $f8, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->f8.u32l;
    // 0x801EE80C: lwc1        $f10, 0x0($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0X0);
    // 0x801EE810: mul.s       $f4, $f10, $f2
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f4.fl = MUL_S(ctx->f10.fl, ctx->f2.fl);
    // 0x801EE814: nop

    // 0x801EE818: mul.s       $f6, $f16, $f0
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f6.fl = MUL_S(ctx->f16.fl, ctx->f0.fl);
    // 0x801EE81C: sub.s       $f8, $f4, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = ctx->f4.fl - ctx->f6.fl;
    // 0x801EE820: mul.s       $f10, $f14, $f12
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f10.fl = MUL_S(ctx->f14.fl, ctx->f12.fl);
    // 0x801EE824: nop

    // 0x801EE828: mul.s       $f6, $f14, $f0
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f6.fl = MUL_S(ctx->f14.fl, ctx->f0.fl);
    // 0x801EE82C: swc1        $f8, 0x10($a0)
    MEM_W(0X10, ctx->r4) = ctx->f8.u32l;
    // 0x801EE830: mul.s       $f8, $f14, $f2
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f8.fl = MUL_S(ctx->f14.fl, ctx->f2.fl);
    // 0x801EE834: swc1        $f10, 0x20($a0)
    MEM_W(0X20, ctx->r4) = ctx->f10.u32l;
    // 0x801EE838: lwc1        $f4, 0x30($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X30);
    // 0x801EE83C: neg.s       $f10, $f18
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f18.fl); 
    ctx->f10.fl = -ctx->f18.fl;
    // 0x801EE840: swc1        $f6, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->f6.u32l;
    // 0x801EE844: mul.s       $f6, $f18, $f16
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f6.fl = MUL_S(ctx->f18.fl, ctx->f16.fl);
    // 0x801EE848: swc1        $f10, 0x24($a0)
    MEM_W(0X24, ctx->r4) = ctx->f10.u32l;
    // 0x801EE84C: swc1        $f8, 0x14($a0)
    MEM_W(0X14, ctx->r4) = ctx->f8.u32l;
    // 0x801EE850: swc1        $f4, 0x30($a0)
    MEM_W(0X30, ctx->r4) = ctx->f4.u32l;
    // 0x801EE854: lwc1        $f4, 0x34($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X34);
    // 0x801EE858: swc1        $f4, 0x34($a0)
    MEM_W(0X34, ctx->r4) = ctx->f4.u32l;
    // 0x801EE85C: swc1        $f6, 0x0($sp)
    MEM_W(0X0, ctx->r29) = ctx->f6.u32l;
    // 0x801EE860: lwc1        $f8, 0x0($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X0);
    // 0x801EE864: mul.s       $f10, $f8, $f0
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f10.fl = MUL_S(ctx->f8.fl, ctx->f0.fl);
    // 0x801EE868: nop

    // 0x801EE86C: mul.s       $f4, $f12, $f2
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f4.fl = MUL_S(ctx->f12.fl, ctx->f2.fl);
    // 0x801EE870: sub.s       $f6, $f10, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = ctx->f10.fl - ctx->f4.fl;
    // 0x801EE874: swc1        $f6, 0x8($a0)
    MEM_W(0X8, ctx->r4) = ctx->f6.u32l;
    // 0x801EE878: lwc1        $f8, 0x0($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X0);
    // 0x801EE87C: mul.s       $f10, $f8, $f2
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f10.fl = MUL_S(ctx->f8.fl, ctx->f2.fl);
    // 0x801EE880: nop

    // 0x801EE884: mul.s       $f4, $f12, $f0
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f4.fl = MUL_S(ctx->f12.fl, ctx->f0.fl);
    // 0x801EE888: mtc1        $zero, $f0
    ctx->f0.u32l = 0;
    // 0x801EE88C: mul.s       $f8, $f14, $f16
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f8.fl = MUL_S(ctx->f14.fl, ctx->f16.fl);
    // 0x801EE890: add.s       $f6, $f10, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = ctx->f10.fl + ctx->f4.fl;
    // 0x801EE894: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x801EE898: swc1        $f8, 0x28($a0)
    MEM_W(0X28, ctx->r4) = ctx->f8.u32l;
    // 0x801EE89C: swc1        $f6, 0x18($a0)
    MEM_W(0X18, ctx->r4) = ctx->f6.u32l;
    // 0x801EE8A0: lwc1        $f10, 0x38($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0X38);
    // 0x801EE8A4: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x801EE8A8: swc1        $f0, 0xC($a0)
    MEM_W(0XC, ctx->r4) = ctx->f0.u32l;
    // 0x801EE8AC: swc1        $f0, 0x1C($a0)
    MEM_W(0X1C, ctx->r4) = ctx->f0.u32l;
    // 0x801EE8B0: swc1        $f0, 0x2C($a0)
    MEM_W(0X2C, ctx->r4) = ctx->f0.u32l;
    // 0x801EE8B4: swc1        $f4, 0x3C($a0)
    MEM_W(0X3C, ctx->r4) = ctx->f4.u32l;
    // 0x801EE8B8: jr          $ra
    // 0x801EE8BC: swc1        $f10, 0x38($a0)
    MEM_W(0X38, ctx->r4) = ctx->f10.u32l;
    return;
    // 0x801EE8BC: swc1        $f10, 0x38($a0)
    MEM_W(0X38, ctx->r4) = ctx->f10.u32l;
;}
RECOMP_FUNC void func_801EE8C0(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801EE8C0: addiu       $sp, $sp, -0x68
    ctx->r29 = ADD32(ctx->r29, -0X68);
    // 0x801EE8C4: mtc1        $a1, $f12
    ctx->f12.u32l = ctx->r5;
    // 0x801EE8C8: mtc1        $a2, $f14
    ctx->f14.u32l = ctx->r6;
    // 0x801EE8CC: lwc1        $f4, 0x78($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X78);
    // 0x801EE8D0: lwc1        $f6, 0x7C($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X7C);
    // 0x801EE8D4: lwc1        $f8, 0x80($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X80);
    // 0x801EE8D8: sw          $ra, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r31;
    // 0x801EE8DC: sw          $a0, 0x68($sp)
    MEM_W(0X68, ctx->r29) = ctx->r4;
    // 0x801EE8E0: mfc1        $a1, $f12
    ctx->r5 = (int32_t)ctx->f12.u32l;
    // 0x801EE8E4: mfc1        $a2, $f14
    ctx->r6 = (int32_t)ctx->f14.u32l;
    // 0x801EE8E8: sw          $a3, 0x74($sp)
    MEM_W(0X74, ctx->r29) = ctx->r7;
    // 0x801EE8EC: addiu       $a0, $sp, 0x28
    ctx->r4 = ADD32(ctx->r29, 0X28);
    // 0x801EE8F0: swc1        $f4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f4.u32l;
    // 0x801EE8F4: swc1        $f6, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->f6.u32l;
    // 0x801EE8F8: jal         0x801EE6F4
    // 0x801EE8FC: swc1        $f8, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->f8.u32l;
    func_801EE6F4(rdram, ctx);
        goto after_0;
    // 0x801EE8FC: swc1        $f8, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->f8.u32l;
    after_0:
    // 0x801EE900: addiu       $a0, $sp, 0x28
    ctx->r4 = ADD32(ctx->r29, 0X28);
    // 0x801EE904: jal         0x801EDD90
    // 0x801EE908: lw          $a1, 0x68($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X68);
    _MtxF_to_Mtx(rdram, ctx);
        goto after_1;
    // 0x801EE908: lw          $a1, 0x68($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X68);
    after_1:
    // 0x801EE90C: lw          $ra, 0x24($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X24);
    // 0x801EE910: addiu       $sp, $sp, 0x68
    ctx->r29 = ADD32(ctx->r29, 0X68);
    // 0x801EE914: jr          $ra
    // 0x801EE918: nop

    return;
    // 0x801EE918: nop

;}
RECOMP_FUNC void func_801EE91C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801EE91C: mtc1        $a1, $f12
    ctx->f12.u32l = ctx->r5;
    // 0x801EE920: mtc1        $a2, $f14
    ctx->f14.u32l = ctx->r6;
    // 0x801EE924: sw          $a3, 0xC($sp)
    MEM_W(0XC, ctx->r29) = ctx->r7;
    // 0x801EE928: swc1        $f12, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->f12.u32l;
    // 0x801EE92C: swc1        $f14, 0x14($a0)
    MEM_W(0X14, ctx->r4) = ctx->f14.u32l;
    // 0x801EE930: mtc1        $zero, $f0
    ctx->f0.u32l = 0;
    // 0x801EE934: lwc1        $f4, 0xC($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0XC);
    // 0x801EE938: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x801EE93C: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x801EE940: swc1        $f4, 0x28($a0)
    MEM_W(0X28, ctx->r4) = ctx->f4.u32l;
    // 0x801EE944: swc1        $f0, 0x10($a0)
    MEM_W(0X10, ctx->r4) = ctx->f0.u32l;
    // 0x801EE948: swc1        $f0, 0x20($a0)
    MEM_W(0X20, ctx->r4) = ctx->f0.u32l;
    // 0x801EE94C: swc1        $f0, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->f0.u32l;
    // 0x801EE950: swc1        $f0, 0x24($a0)
    MEM_W(0X24, ctx->r4) = ctx->f0.u32l;
    // 0x801EE954: swc1        $f0, 0x8($a0)
    MEM_W(0X8, ctx->r4) = ctx->f0.u32l;
    // 0x801EE958: swc1        $f0, 0x18($a0)
    MEM_W(0X18, ctx->r4) = ctx->f0.u32l;
    // 0x801EE95C: swc1        $f0, 0xC($a0)
    MEM_W(0XC, ctx->r4) = ctx->f0.u32l;
    // 0x801EE960: swc1        $f0, 0x1C($a0)
    MEM_W(0X1C, ctx->r4) = ctx->f0.u32l;
    // 0x801EE964: swc1        $f0, 0x2C($a0)
    MEM_W(0X2C, ctx->r4) = ctx->f0.u32l;
    // 0x801EE968: swc1        $f0, 0x30($a0)
    MEM_W(0X30, ctx->r4) = ctx->f0.u32l;
    // 0x801EE96C: swc1        $f0, 0x34($a0)
    MEM_W(0X34, ctx->r4) = ctx->f0.u32l;
    // 0x801EE970: swc1        $f0, 0x38($a0)
    MEM_W(0X38, ctx->r4) = ctx->f0.u32l;
    // 0x801EE974: jr          $ra
    // 0x801EE978: swc1        $f6, 0x3C($a0)
    MEM_W(0X3C, ctx->r4) = ctx->f6.u32l;
    return;
    // 0x801EE978: swc1        $f6, 0x3C($a0)
    MEM_W(0X3C, ctx->r4) = ctx->f6.u32l;
;}
RECOMP_FUNC void func_801EE97C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801EE97C: mtc1        $a1, $f12
    ctx->f12.u32l = ctx->r5;
    // 0x801EE980: mtc1        $a2, $f14
    ctx->f14.u32l = ctx->r6;
    // 0x801EE984: addiu       $sp, $sp, -0x58
    ctx->r29 = ADD32(ctx->r29, -0X58);
    // 0x801EE988: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x801EE98C: sw          $a0, 0x58($sp)
    MEM_W(0X58, ctx->r29) = ctx->r4;
    // 0x801EE990: mfc1        $a1, $f12
    ctx->r5 = (int32_t)ctx->f12.u32l;
    // 0x801EE994: mfc1        $a2, $f14
    ctx->r6 = (int32_t)ctx->f14.u32l;
    // 0x801EE998: sw          $a3, 0x64($sp)
    MEM_W(0X64, ctx->r29) = ctx->r7;
    // 0x801EE99C: jal         0x801EE91C
    // 0x801EE9A0: addiu       $a0, $sp, 0x18
    ctx->r4 = ADD32(ctx->r29, 0X18);
    func_801EE91C(rdram, ctx);
        goto after_0;
    // 0x801EE9A0: addiu       $a0, $sp, 0x18
    ctx->r4 = ADD32(ctx->r29, 0X18);
    after_0:
    // 0x801EE9A4: addiu       $a0, $sp, 0x18
    ctx->r4 = ADD32(ctx->r29, 0X18);
    // 0x801EE9A8: jal         0x801EDD90
    // 0x801EE9AC: lw          $a1, 0x58($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X58);
    _MtxF_to_Mtx(rdram, ctx);
        goto after_1;
    // 0x801EE9AC: lw          $a1, 0x58($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X58);
    after_1:
    // 0x801EE9B0: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x801EE9B4: addiu       $sp, $sp, 0x58
    ctx->r29 = ADD32(ctx->r29, 0X58);
    // 0x801EE9B8: jr          $ra
    // 0x801EE9BC: nop

    return;
    // 0x801EE9BC: nop

;}
RECOMP_FUNC void func_801EE9C0(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801EE9C0: lui         $a0, 0x8023
    ctx->r4 = S32(0X8023 << 16);
    // 0x801EE9C4: addiu       $a0, $a0, -0x72E0
    ctx->r4 = ADD32(ctx->r4, -0X72E0);
    // 0x801EE9C8: lw          $v1, 0x0($a0)
    ctx->r3 = MEM_W(ctx->r4, 0X0);
    // 0x801EE9CC: addiu       $t6, $zero, 0x2
    ctx->r14 = ADD32(0, 0X2);
    // 0x801EE9D0: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x801EE9D4: subu        $t7, $t6, $v1
    ctx->r15 = SUB32(ctx->r14, ctx->r3);
    // 0x801EE9D8: mtc1        $t7, $f4
    ctx->f4.u32l = ctx->r15;
    // 0x801EE9DC: mtc1        $at, $f14
    ctx->f14.u32l = ctx->r1;
    // 0x801EE9E0: lui         $at, 0x4000
    ctx->r1 = S32(0X4000 << 16);
    // 0x801EE9E4: cvt.s.w     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
    // 0x801EE9E8: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x801EE9EC: lui         $a1, 0x8023
    ctx->r5 = S32(0X8023 << 16);
    // 0x801EE9F0: addiu       $a1, $a1, -0x72E4
    ctx->r5 = ADD32(ctx->r5, -0X72E4);
    // 0x801EE9F4: lw          $v0, 0x0($a1)
    ctx->r2 = MEM_W(ctx->r5, 0X0);
    // 0x801EE9F8: addiu       $a2, $zero, 0xC
    ctx->r6 = ADD32(0, 0XC);
    // 0x801EE9FC: div.s       $f0, $f6, $f8
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f0.fl = DIV_S(ctx->f6.fl, ctx->f8.fl);
    // 0x801EEA00: multu       $v0, $a2
    result = U64(U32(ctx->r2)) * U64(U32(ctx->r6)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x801EEA04: lui         $t8, 0x8022
    ctx->r24 = S32(0X8022 << 16);
    // 0x801EEA08: addiu       $t8, $t8, 0x7888
    ctx->r24 = ADD32(ctx->r24, 0X7888);
    // 0x801EEA0C: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801EEA10: mflo        $a3
    ctx->r7 = lo;
    // 0x801EEA14: addu        $t0, $a3, $t8
    ctx->r8 = ADD32(ctx->r7, ctx->r24);
    // 0x801EEA18: lw          $t9, 0xC($t0)
    ctx->r25 = MEM_W(ctx->r8, 0XC);
    // 0x801EEA1C: lw          $t3, 0x0($t0)
    ctx->r11 = MEM_W(ctx->r8, 0X0);
    // 0x801EEA20: mtc1        $t9, $f10
    ctx->f10.u32l = ctx->r25;
    // 0x801EEA24: mtc1        $t3, $f4
    ctx->f4.u32l = ctx->r11;
    // 0x801EEA28: cvt.s.w     $f16, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    ctx->f16.fl = CVT_S_W(ctx->f10.u32l);
    // 0x801EEA2C: sub.s       $f2, $f14, $f0
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f2.fl = ctx->f14.fl - ctx->f0.fl;
    // 0x801EEA30: cvt.s.w     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
    // 0x801EEA34: mul.s       $f18, $f16, $f2
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f18.fl = MUL_S(ctx->f16.fl, ctx->f2.fl);
    // 0x801EEA38: nop

    // 0x801EEA3C: mul.s       $f8, $f6, $f0
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f8.fl = MUL_S(ctx->f6.fl, ctx->f0.fl);
    // 0x801EEA40: add.s       $f10, $f18, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = ctx->f18.fl + ctx->f8.fl;
    // 0x801EEA44: trunc.w.s   $f16, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    ctx->f16.u32l = TRUNC_W_S(ctx->f10.fl);
    // 0x801EEA48: mfc1        $t5, $f16
    ctx->r13 = (int32_t)ctx->f16.u32l;
    // 0x801EEA4C: nop

    // 0x801EEA50: sw          $t5, -0x7554($at)
    MEM_W(-0X7554, ctx->r1) = ctx->r13;
    // 0x801EEA54: lw          $t6, 0x10($t0)
    ctx->r14 = MEM_W(ctx->r8, 0X10);
    // 0x801EEA58: lw          $t7, 0x4($t0)
    ctx->r15 = MEM_W(ctx->r8, 0X4);
    // 0x801EEA5C: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801EEA60: mtc1        $t6, $f4
    ctx->f4.u32l = ctx->r14;
    // 0x801EEA64: mtc1        $t7, $f8
    ctx->f8.u32l = ctx->r15;
    // 0x801EEA68: lui         $t7, 0x8022
    ctx->r15 = S32(0X8022 << 16);
    // 0x801EEA6C: cvt.s.w     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
    // 0x801EEA70: addiu       $t7, $t7, 0x78C4
    ctx->r15 = ADD32(ctx->r15, 0X78C4);
    // 0x801EEA74: addu        $t1, $a3, $t7
    ctx->r9 = ADD32(ctx->r7, ctx->r15);
    // 0x801EEA78: or          $a3, $v0, $zero
    ctx->r7 = ctx->r2 | 0;
    // 0x801EEA7C: cvt.s.w     $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.fl = CVT_S_W(ctx->f8.u32l);
    // 0x801EEA80: mul.s       $f18, $f6, $f2
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f18.fl = MUL_S(ctx->f6.fl, ctx->f2.fl);
    // 0x801EEA84: nop

    // 0x801EEA88: mul.s       $f16, $f10, $f0
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f16.fl = MUL_S(ctx->f10.fl, ctx->f0.fl);
    // 0x801EEA8C: add.s       $f4, $f18, $f16
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f4.fl = ctx->f18.fl + ctx->f16.fl;
    // 0x801EEA90: trunc.w.s   $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.u32l = TRUNC_W_S(ctx->f4.fl);
    // 0x801EEA94: mfc1        $t9, $f6
    ctx->r25 = (int32_t)ctx->f6.u32l;
    // 0x801EEA98: nop

    // 0x801EEA9C: sw          $t9, -0x7550($at)
    MEM_W(-0X7550, ctx->r1) = ctx->r25;
    // 0x801EEAA0: lw          $t3, 0x14($t0)
    ctx->r11 = MEM_W(ctx->r8, 0X14);
    // 0x801EEAA4: lw          $t4, 0x8($t0)
    ctx->r12 = MEM_W(ctx->r8, 0X8);
    // 0x801EEAA8: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801EEAAC: mtc1        $t3, $f8
    ctx->f8.u32l = ctx->r11;
    // 0x801EEAB0: mtc1        $t4, $f16
    ctx->f16.u32l = ctx->r12;
    // 0x801EEAB4: cvt.s.w     $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.fl = CVT_S_W(ctx->f8.u32l);
    // 0x801EEAB8: cvt.s.w     $f4, $f16
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 16);
    ctx->f4.fl = CVT_S_W(ctx->f16.u32l);
    // 0x801EEABC: mul.s       $f18, $f10, $f2
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f18.fl = MUL_S(ctx->f10.fl, ctx->f2.fl);
    // 0x801EEAC0: nop

    // 0x801EEAC4: mul.s       $f6, $f4, $f0
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f6.fl = MUL_S(ctx->f4.fl, ctx->f0.fl);
    // 0x801EEAC8: add.s       $f8, $f18, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = ctx->f18.fl + ctx->f6.fl;
    // 0x801EEACC: trunc.w.s   $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.u32l = TRUNC_W_S(ctx->f8.fl);
    // 0x801EEAD0: mfc1        $t6, $f10
    ctx->r14 = (int32_t)ctx->f10.u32l;
    // 0x801EEAD4: nop

    // 0x801EEAD8: sw          $t6, -0x754C($at)
    MEM_W(-0X754C, ctx->r1) = ctx->r14;
    // 0x801EEADC: lw          $t8, 0xC($t1)
    ctx->r24 = MEM_W(ctx->r9, 0XC);
    // 0x801EEAE0: lw          $t9, 0x0($t1)
    ctx->r25 = MEM_W(ctx->r9, 0X0);
    // 0x801EEAE4: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801EEAE8: mtc1        $t8, $f16
    ctx->f16.u32l = ctx->r24;
    // 0x801EEAEC: mtc1        $t9, $f6
    ctx->f6.u32l = ctx->r25;
    // 0x801EEAF0: cvt.s.w     $f4, $f16
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 16);
    ctx->f4.fl = CVT_S_W(ctx->f16.u32l);
    // 0x801EEAF4: cvt.s.w     $f8, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    ctx->f8.fl = CVT_S_W(ctx->f6.u32l);
    // 0x801EEAF8: mul.s       $f18, $f4, $f2
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f18.fl = MUL_S(ctx->f4.fl, ctx->f2.fl);
    // 0x801EEAFC: nop

    // 0x801EEB00: mul.s       $f10, $f8, $f0
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f10.fl = MUL_S(ctx->f8.fl, ctx->f0.fl);
    // 0x801EEB04: add.s       $f16, $f18, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f16.fl = ctx->f18.fl + ctx->f10.fl;
    // 0x801EEB08: trunc.w.s   $f4, $f16
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 16);
    ctx->f4.u32l = TRUNC_W_S(ctx->f16.fl);
    // 0x801EEB0C: mfc1        $t4, $f4
    ctx->r12 = (int32_t)ctx->f4.u32l;
    // 0x801EEB10: nop

    // 0x801EEB14: sw          $t4, -0x7548($at)
    MEM_W(-0X7548, ctx->r1) = ctx->r12;
    // 0x801EEB18: lw          $t5, 0x10($t1)
    ctx->r13 = MEM_W(ctx->r9, 0X10);
    // 0x801EEB1C: lw          $t6, 0x4($t1)
    ctx->r14 = MEM_W(ctx->r9, 0X4);
    // 0x801EEB20: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801EEB24: mtc1        $t5, $f6
    ctx->f6.u32l = ctx->r13;
    // 0x801EEB28: mtc1        $t6, $f10
    ctx->f10.u32l = ctx->r14;
    // 0x801EEB2C: lui         $t6, 0x801C
    ctx->r14 = S32(0X801C << 16);
    // 0x801EEB30: cvt.s.w     $f8, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    ctx->f8.fl = CVT_S_W(ctx->f6.u32l);
    // 0x801EEB34: lw          $t6, 0x1FD8($t6)
    ctx->r14 = MEM_W(ctx->r14, 0X1FD8);
    // 0x801EEB38: cvt.s.w     $f16, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    ctx->f16.fl = CVT_S_W(ctx->f10.u32l);
    // 0x801EEB3C: mul.s       $f18, $f8, $f2
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f18.fl = MUL_S(ctx->f8.fl, ctx->f2.fl);
    // 0x801EEB40: nop

    // 0x801EEB44: mul.s       $f4, $f16, $f0
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f4.fl = MUL_S(ctx->f16.fl, ctx->f0.fl);
    // 0x801EEB48: add.s       $f6, $f18, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = ctx->f18.fl + ctx->f4.fl;
    // 0x801EEB4C: trunc.w.s   $f8, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    ctx->f8.u32l = TRUNC_W_S(ctx->f6.fl);
    // 0x801EEB50: mfc1        $t8, $f8
    ctx->r24 = (int32_t)ctx->f8.u32l;
    // 0x801EEB54: nop

    // 0x801EEB58: sw          $t8, -0x7544($at)
    MEM_W(-0X7544, ctx->r1) = ctx->r24;
    // 0x801EEB5C: lw          $t9, 0x14($t1)
    ctx->r25 = MEM_W(ctx->r9, 0X14);
    // 0x801EEB60: lw          $t3, 0x8($t1)
    ctx->r11 = MEM_W(ctx->r9, 0X8);
    // 0x801EEB64: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801EEB68: mtc1        $t9, $f10
    ctx->f10.u32l = ctx->r25;
    // 0x801EEB6C: mtc1        $t3, $f4
    ctx->f4.u32l = ctx->r11;
    // 0x801EEB70: cvt.s.w     $f16, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    ctx->f16.fl = CVT_S_W(ctx->f10.u32l);
    // 0x801EEB74: cvt.s.w     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
    // 0x801EEB78: mul.s       $f18, $f16, $f2
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f18.fl = MUL_S(ctx->f16.fl, ctx->f2.fl);
    // 0x801EEB7C: nop

    // 0x801EEB80: mul.s       $f8, $f6, $f0
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f8.fl = MUL_S(ctx->f6.fl, ctx->f0.fl);
    // 0x801EEB84: add.s       $f10, $f18, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = ctx->f18.fl + ctx->f8.fl;
    // 0x801EEB88: trunc.w.s   $f16, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    ctx->f16.u32l = TRUNC_W_S(ctx->f10.fl);
    // 0x801EEB8C: mfc1        $t5, $f16
    ctx->r13 = (int32_t)ctx->f16.u32l;
    // 0x801EEB90: beq         $t6, $zero, L_801EEBA8
    if (ctx->r14 == 0) {
        // 0x801EEB94: sw          $t5, -0x7540($at)
        MEM_W(-0X7540, ctx->r1) = ctx->r13;
            goto L_801EEBA8;
    }
    // 0x801EEB94: sw          $t5, -0x7540($at)
    MEM_W(-0X7540, ctx->r1) = ctx->r13;
    // 0x801EEB98: mtc1        $zero, $f2
    ctx->f2.u32l = 0;
    // 0x801EEB9C: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    // 0x801EEBA0: b           L_801EEBA8
    // 0x801EEBA4: mov.s       $f0, $f14
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 14);
    ctx->f0.fl = ctx->f14.fl;
        goto L_801EEBA8;
    // 0x801EEBA4: mov.s       $f0, $f14
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 14);
    ctx->f0.fl = ctx->f14.fl;
L_801EEBA8:
    // 0x801EEBA8: multu       $a3, $a2
    result = U64(U32(ctx->r7)) * U64(U32(ctx->r6)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x801EEBAC: lui         $t7, 0x8022
    ctx->r15 = S32(0X8022 << 16);
    // 0x801EEBB0: addiu       $t7, $t7, 0x7900
    ctx->r15 = ADD32(ctx->r15, 0X7900);
    // 0x801EEBB4: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801EEBB8: mflo        $t0
    ctx->r8 = lo;
    // 0x801EEBBC: addu        $t1, $t0, $t7
    ctx->r9 = ADD32(ctx->r8, ctx->r15);
    // 0x801EEBC0: lw          $t8, 0xC($t1)
    ctx->r24 = MEM_W(ctx->r9, 0XC);
    // 0x801EEBC4: lw          $t9, 0x0($t1)
    ctx->r25 = MEM_W(ctx->r9, 0X0);
    // 0x801EEBC8: mtc1        $t8, $f4
    ctx->f4.u32l = ctx->r24;
    // 0x801EEBCC: mtc1        $t9, $f8
    ctx->f8.u32l = ctx->r25;
    // 0x801EEBD0: cvt.s.w     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
    // 0x801EEBD4: cvt.s.w     $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.fl = CVT_S_W(ctx->f8.u32l);
    // 0x801EEBD8: mul.s       $f18, $f6, $f2
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f18.fl = MUL_S(ctx->f6.fl, ctx->f2.fl);
    // 0x801EEBDC: nop

    // 0x801EEBE0: mul.s       $f16, $f10, $f0
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f16.fl = MUL_S(ctx->f10.fl, ctx->f0.fl);
    // 0x801EEBE4: add.s       $f4, $f18, $f16
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f4.fl = ctx->f18.fl + ctx->f16.fl;
    // 0x801EEBE8: trunc.w.s   $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.u32l = TRUNC_W_S(ctx->f4.fl);
    // 0x801EEBEC: mfc1        $t4, $f6
    ctx->r12 = (int32_t)ctx->f6.u32l;
    // 0x801EEBF0: nop

    // 0x801EEBF4: sw          $t4, -0x753C($at)
    MEM_W(-0X753C, ctx->r1) = ctx->r12;
    // 0x801EEBF8: lw          $t5, 0x10($t1)
    ctx->r13 = MEM_W(ctx->r9, 0X10);
    // 0x801EEBFC: lw          $t6, 0x4($t1)
    ctx->r14 = MEM_W(ctx->r9, 0X4);
    // 0x801EEC00: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801EEC04: mtc1        $t5, $f8
    ctx->f8.u32l = ctx->r13;
    // 0x801EEC08: mtc1        $t6, $f16
    ctx->f16.u32l = ctx->r14;
    // 0x801EEC0C: lui         $t6, 0x8022
    ctx->r14 = S32(0X8022 << 16);
    // 0x801EEC10: cvt.s.w     $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.fl = CVT_S_W(ctx->f8.u32l);
    // 0x801EEC14: addiu       $t6, $t6, 0x793C
    ctx->r14 = ADD32(ctx->r14, 0X793C);
    // 0x801EEC18: addu        $t2, $t0, $t6
    ctx->r10 = ADD32(ctx->r8, ctx->r14);
    // 0x801EEC1C: addiu       $t6, $v1, 0x1
    ctx->r14 = ADD32(ctx->r3, 0X1);
    // 0x801EEC20: cvt.s.w     $f4, $f16
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 16);
    ctx->f4.fl = CVT_S_W(ctx->f16.u32l);
    // 0x801EEC24: mul.s       $f18, $f10, $f2
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f18.fl = MUL_S(ctx->f10.fl, ctx->f2.fl);
    // 0x801EEC28: nop

    // 0x801EEC2C: mul.s       $f6, $f4, $f0
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f6.fl = MUL_S(ctx->f4.fl, ctx->f0.fl);
    // 0x801EEC30: add.s       $f8, $f18, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = ctx->f18.fl + ctx->f6.fl;
    // 0x801EEC34: trunc.w.s   $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.u32l = TRUNC_W_S(ctx->f8.fl);
    // 0x801EEC38: mfc1        $t8, $f10
    ctx->r24 = (int32_t)ctx->f10.u32l;
    // 0x801EEC3C: nop

    // 0x801EEC40: sw          $t8, -0x7538($at)
    MEM_W(-0X7538, ctx->r1) = ctx->r24;
    // 0x801EEC44: lw          $t9, 0x14($t1)
    ctx->r25 = MEM_W(ctx->r9, 0X14);
    // 0x801EEC48: lw          $t3, 0x8($t1)
    ctx->r11 = MEM_W(ctx->r9, 0X8);
    // 0x801EEC4C: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801EEC50: mtc1        $t9, $f16
    ctx->f16.u32l = ctx->r25;
    // 0x801EEC54: mtc1        $t3, $f6
    ctx->f6.u32l = ctx->r11;
    // 0x801EEC58: cvt.s.w     $f4, $f16
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 16);
    ctx->f4.fl = CVT_S_W(ctx->f16.u32l);
    // 0x801EEC5C: cvt.s.w     $f8, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    ctx->f8.fl = CVT_S_W(ctx->f6.u32l);
    // 0x801EEC60: mul.s       $f18, $f4, $f2
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f18.fl = MUL_S(ctx->f4.fl, ctx->f2.fl);
    // 0x801EEC64: nop

    // 0x801EEC68: mul.s       $f10, $f8, $f0
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f10.fl = MUL_S(ctx->f8.fl, ctx->f0.fl);
    // 0x801EEC6C: add.s       $f16, $f18, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f16.fl = ctx->f18.fl + ctx->f10.fl;
    // 0x801EEC70: trunc.w.s   $f4, $f16
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 16);
    ctx->f4.u32l = TRUNC_W_S(ctx->f16.fl);
    // 0x801EEC74: mfc1        $t5, $f4
    ctx->r13 = (int32_t)ctx->f4.u32l;
    // 0x801EEC78: nop

    // 0x801EEC7C: sw          $t5, -0x7534($at)
    MEM_W(-0X7534, ctx->r1) = ctx->r13;
    // 0x801EEC80: lw          $t7, 0xC($t2)
    ctx->r15 = MEM_W(ctx->r10, 0XC);
    // 0x801EEC84: lw          $t8, 0x0($t2)
    ctx->r24 = MEM_W(ctx->r10, 0X0);
    // 0x801EEC88: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801EEC8C: mtc1        $t7, $f6
    ctx->f6.u32l = ctx->r15;
    // 0x801EEC90: mtc1        $t8, $f10
    ctx->f10.u32l = ctx->r24;
    // 0x801EEC94: cvt.s.w     $f8, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    ctx->f8.fl = CVT_S_W(ctx->f6.u32l);
    // 0x801EEC98: cvt.s.w     $f16, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    ctx->f16.fl = CVT_S_W(ctx->f10.u32l);
    // 0x801EEC9C: mul.s       $f18, $f8, $f2
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f18.fl = MUL_S(ctx->f8.fl, ctx->f2.fl);
    // 0x801EECA0: nop

    // 0x801EECA4: mul.s       $f4, $f16, $f0
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f4.fl = MUL_S(ctx->f16.fl, ctx->f0.fl);
    // 0x801EECA8: add.s       $f6, $f18, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = ctx->f18.fl + ctx->f4.fl;
    // 0x801EECAC: trunc.w.s   $f8, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    ctx->f8.u32l = TRUNC_W_S(ctx->f6.fl);
    // 0x801EECB0: mfc1        $t3, $f8
    ctx->r11 = (int32_t)ctx->f8.u32l;
    // 0x801EECB4: nop

    // 0x801EECB8: sw          $t3, -0x7530($at)
    MEM_W(-0X7530, ctx->r1) = ctx->r11;
    // 0x801EECBC: lw          $t4, 0x10($t2)
    ctx->r12 = MEM_W(ctx->r10, 0X10);
    // 0x801EECC0: lw          $t5, 0x4($t2)
    ctx->r13 = MEM_W(ctx->r10, 0X4);
    // 0x801EECC4: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801EECC8: mtc1        $t4, $f10
    ctx->f10.u32l = ctx->r12;
    // 0x801EECCC: mtc1        $t5, $f4
    ctx->f4.u32l = ctx->r13;
    // 0x801EECD0: lui         $t5, 0x801D
    ctx->r13 = S32(0X801D << 16);
    // 0x801EECD4: cvt.s.w     $f16, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    ctx->f16.fl = CVT_S_W(ctx->f10.u32l);
    // 0x801EECD8: lh          $t5, -0x19DC($t5)
    ctx->r13 = MEM_H(ctx->r13, -0X19DC);
    // 0x801EECDC: cvt.s.w     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
    // 0x801EECE0: mul.s       $f18, $f16, $f2
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f18.fl = MUL_S(ctx->f16.fl, ctx->f2.fl);
    // 0x801EECE4: nop

    // 0x801EECE8: mul.s       $f8, $f6, $f0
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f8.fl = MUL_S(ctx->f6.fl, ctx->f0.fl);
    // 0x801EECEC: add.s       $f10, $f18, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = ctx->f18.fl + ctx->f8.fl;
    // 0x801EECF0: trunc.w.s   $f16, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    ctx->f16.u32l = TRUNC_W_S(ctx->f10.fl);
    // 0x801EECF4: mfc1        $t7, $f16
    ctx->r15 = (int32_t)ctx->f16.u32l;
    // 0x801EECF8: nop

    // 0x801EECFC: sw          $t7, -0x752C($at)
    MEM_W(-0X752C, ctx->r1) = ctx->r15;
    // 0x801EED00: lw          $t8, 0x14($t2)
    ctx->r24 = MEM_W(ctx->r10, 0X14);
    // 0x801EED04: lw          $t9, 0x8($t2)
    ctx->r25 = MEM_W(ctx->r10, 0X8);
    // 0x801EED08: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801EED0C: mtc1        $t8, $f4
    ctx->f4.u32l = ctx->r24;
    // 0x801EED10: mtc1        $t9, $f8
    ctx->f8.u32l = ctx->r25;
    // 0x801EED14: cvt.s.w     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
    // 0x801EED18: cvt.s.w     $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.fl = CVT_S_W(ctx->f8.u32l);
    // 0x801EED1C: mul.s       $f18, $f6, $f2
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f18.fl = MUL_S(ctx->f6.fl, ctx->f2.fl);
    // 0x801EED20: nop

    // 0x801EED24: mul.s       $f16, $f10, $f0
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f16.fl = MUL_S(ctx->f10.fl, ctx->f0.fl);
    // 0x801EED28: add.s       $f4, $f18, $f16
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f4.fl = ctx->f18.fl + ctx->f16.fl;
    // 0x801EED2C: trunc.w.s   $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.u32l = TRUNC_W_S(ctx->f4.fl);
    // 0x801EED30: mfc1        $t4, $f6
    ctx->r12 = (int32_t)ctx->f6.u32l;
    // 0x801EED34: nop

    // 0x801EED38: sw          $t4, -0x7528($at)
    MEM_W(-0X7528, ctx->r1) = ctx->r12;
    // 0x801EED3C: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x801EED40: bne         $t5, $at, L_801EED68
    if (ctx->r13 != ctx->r1) {
        // 0x801EED44: nop
    
            goto L_801EED68;
    }
    // 0x801EED44: nop

    // 0x801EED48: slti        $at, $t6, 0x2
    ctx->r1 = SIGNED(ctx->r14) < 0X2 ? 1 : 0;
    // 0x801EED4C: bne         $at, $zero, L_801EED68
    if (ctx->r1 != 0) {
        // 0x801EED50: sw          $t6, 0x0($a0)
        MEM_W(0X0, ctx->r4) = ctx->r14;
            goto L_801EED68;
    }
    // 0x801EED50: sw          $t6, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r14;
    // 0x801EED54: addiu       $t8, $v0, 0x1
    ctx->r24 = ADD32(ctx->r2, 0X1);
    // 0x801EED58: sw          $t8, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r24;
    // 0x801EED5C: andi        $t3, $t8, 0x3
    ctx->r11 = ctx->r24 & 0X3;
    // 0x801EED60: sw          $zero, 0x0($a0)
    MEM_W(0X0, ctx->r4) = 0;
    // 0x801EED64: sw          $t3, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r11;
L_801EED68:
    // 0x801EED68: jr          $ra
    // 0x801EED6C: nop

    return;
    // 0x801EED6C: nop

;}
RECOMP_FUNC void func_801EED70(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801EED70: lui         $v0, 0x8022
    ctx->r2 = S32(0X8022 << 16);
    // 0x801EED74: addiu       $v0, $v0, 0x7998
    ctx->r2 = ADD32(ctx->r2, 0X7998);
    // 0x801EED78: lw          $t6, 0x0($v0)
    ctx->r14 = MEM_W(ctx->r2, 0X0);
    // 0x801EED7C: addiu       $sp, $sp, -0x40
    ctx->r29 = ADD32(ctx->r29, -0X40);
    // 0x801EED80: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x801EED84: sw          $s1, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r17;
    // 0x801EED88: beq         $t6, $zero, L_801EED94
    if (ctx->r14 == 0) {
        // 0x801EED8C: sw          $s0, 0x14($sp)
        MEM_W(0X14, ctx->r29) = ctx->r16;
            goto L_801EED94;
    }
    // 0x801EED8C: sw          $s0, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r16;
    // 0x801EED90: sw          $zero, 0x0($v0)
    MEM_W(0X0, ctx->r2) = 0;
L_801EED94:
    // 0x801EED94: jal         0x801EE9C0
    // 0x801EED98: nop

    func_801EE9C0(rdram, ctx);
        goto after_0;
    // 0x801EED98: nop

    after_0:
    // 0x801EED9C: lui         $v0, 0x8023
    ctx->r2 = S32(0X8023 << 16);
    // 0x801EEDA0: lui         $v1, 0x8023
    ctx->r3 = S32(0X8023 << 16);
    // 0x801EEDA4: addiu       $v1, $v1, -0x74B0
    ctx->r3 = ADD32(ctx->r3, -0X74B0);
    // 0x801EEDA8: addiu       $v0, $v0, -0x74AC
    ctx->r2 = ADD32(ctx->r2, -0X74AC);
    // 0x801EEDAC: sw          $zero, 0x0($v0)
    MEM_W(0X0, ctx->r2) = 0;
    // 0x801EEDB0: sw          $zero, 0x0($v1)
    MEM_W(0X0, ctx->r3) = 0;
    // 0x801EEDB4: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801EEDB8: lui         $a1, 0x8023
    ctx->r5 = S32(0X8023 << 16);
    // 0x801EEDBC: lui         $a2, 0x8023
    ctx->r6 = S32(0X8023 << 16);
    // 0x801EEDC0: mtc1        $zero, $f0
    ctx->f0.u32l = 0;
    // 0x801EEDC4: sw          $zero, -0x755C($at)
    MEM_W(-0X755C, ctx->r1) = 0;
    // 0x801EEDC8: addiu       $a2, $a2, -0x7328
    ctx->r6 = ADD32(ctx->r6, -0X7328);
    // 0x801EEDCC: addiu       $a1, $a1, -0x73D0
    ctx->r5 = ADD32(ctx->r5, -0X73D0);
    // 0x801EEDD0: addiu       $a0, $zero, 0x3
    ctx->r4 = ADD32(0, 0X3);
    // 0x801EEDD4: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
L_801EEDD8:
    // 0x801EEDD8: or          $v0, $a1, $zero
    ctx->r2 = ctx->r5 | 0;
L_801EEDDC:
    // 0x801EEDDC: addiu       $v1, $v1, 0x1
    ctx->r3 = ADD32(ctx->r3, 0X1);
    // 0x801EEDE0: addiu       $v0, $v0, 0x1C
    ctx->r2 = ADD32(ctx->r2, 0X1C);
    // 0x801EEDE4: sw          $zero, -0x8($v0)
    MEM_W(-0X8, ctx->r2) = 0;
    // 0x801EEDE8: sw          $zero, -0x4($v0)
    MEM_W(-0X4, ctx->r2) = 0;
    // 0x801EEDEC: swc1        $f0, -0x10($v0)
    MEM_W(-0X10, ctx->r2) = ctx->f0.u32l;
    // 0x801EEDF0: swc1        $f0, -0x14($v0)
    MEM_W(-0X14, ctx->r2) = ctx->f0.u32l;
    // 0x801EEDF4: swc1        $f0, -0x18($v0)
    MEM_W(-0X18, ctx->r2) = ctx->f0.u32l;
    // 0x801EEDF8: bne         $v1, $a0, L_801EEDDC
    if (ctx->r3 != ctx->r4) {
        // 0x801EEDFC: swc1        $f0, -0x1C($v0)
        MEM_W(-0X1C, ctx->r2) = ctx->f0.u32l;
            goto L_801EEDDC;
    }
    // 0x801EEDFC: swc1        $f0, -0x1C($v0)
    MEM_W(-0X1C, ctx->r2) = ctx->f0.u32l;
    // 0x801EEE00: addiu       $a1, $a1, 0x54
    ctx->r5 = ADD32(ctx->r5, 0X54);
    // 0x801EEE04: bnel        $a1, $a2, L_801EEDD8
    if (ctx->r5 != ctx->r6) {
        // 0x801EEE08: or          $v1, $zero, $zero
        ctx->r3 = 0 | 0;
            goto L_801EEDD8;
    }
    goto skip_0;
    // 0x801EEE08: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
    skip_0:
    // 0x801EEE0C: lui         $t5, 0x801A
    ctx->r13 = S32(0X801A << 16);
    // 0x801EEE10: lui         $ra, 0x801B
    ctx->r31 = S32(0X801B << 16);
    // 0x801EEE14: lui         $t3, 0x8022
    ctx->r11 = S32(0X8022 << 16);
    // 0x801EEE18: addiu       $t3, $t3, 0x7888
    ctx->r11 = ADD32(ctx->r11, 0X7888);
    // 0x801EEE1C: addiu       $ra, $ra, -0x16B8
    ctx->r31 = ADD32(ctx->r31, -0X16B8);
    // 0x801EEE20: addiu       $t5, $t5, -0x7C98
    ctx->r13 = ADD32(ctx->r13, -0X7C98);
    // 0x801EEE24: ori         $at, $zero, 0xB240
    ctx->r1 = 0 | 0XB240;
L_801EEE28:
    // 0x801EEE28: addu        $v1, $t5, $at
    ctx->r3 = ADD32(ctx->r13, ctx->r1);
    // 0x801EEE2C: ori         $at, $zero, 0xB1C0
    ctx->r1 = 0 | 0XB1C0;
    // 0x801EEE30: addu        $a2, $t5, $at
    ctx->r6 = ADD32(ctx->r13, ctx->r1);
    // 0x801EEE34: ori         $at, $zero, 0xB200
    ctx->r1 = 0 | 0XB200;
    // 0x801EEE38: addu        $t0, $t5, $at
    ctx->r8 = ADD32(ctx->r13, ctx->r1);
    // 0x801EEE3C: ori         $at, $zero, 0xB280
    ctx->r1 = 0 | 0XB280;
    // 0x801EEE40: lui         $a1, 0x8022
    ctx->r5 = S32(0X8022 << 16);
    // 0x801EEE44: lui         $a3, 0x8022
    ctx->r7 = S32(0X8022 << 16);
    // 0x801EEE48: lui         $t1, 0x8022
    ctx->r9 = S32(0X8022 << 16);
    // 0x801EEE4C: lui         $v0, 0x8022
    ctx->r2 = S32(0X8022 << 16);
    // 0x801EEE50: addiu       $v0, $v0, 0x7848
    ctx->r2 = ADD32(ctx->r2, 0X7848);
    // 0x801EEE54: addiu       $t1, $t1, 0x7808
    ctx->r9 = ADD32(ctx->r9, 0X7808);
    // 0x801EEE58: addiu       $a3, $a3, 0x77C8
    ctx->r7 = ADD32(ctx->r7, 0X77C8);
    // 0x801EEE5C: addiu       $a1, $a1, 0x7788
    ctx->r5 = ADD32(ctx->r5, 0X7788);
    // 0x801EEE60: addu        $t2, $t5, $at
    ctx->r10 = ADD32(ctx->r13, ctx->r1);
L_801EEE64:
    // 0x801EEE64: lw          $at, 0x0($a1)
    ctx->r1 = MEM_W(ctx->r5, 0X0);
    // 0x801EEE68: lw          $t6, 0x4($a1)
    ctx->r14 = MEM_W(ctx->r5, 0X4);
    // 0x801EEE6C: lw          $t8, 0x4($a3)
    ctx->r24 = MEM_W(ctx->r7, 0X4);
    // 0x801EEE70: sw          $at, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r1;
    // 0x801EEE74: lw          $at, 0x8($a1)
    ctx->r1 = MEM_W(ctx->r5, 0X8);
    // 0x801EEE78: sw          $t6, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r14;
    // 0x801EEE7C: lw          $t6, 0xC($a1)
    ctx->r14 = MEM_W(ctx->r5, 0XC);
    // 0x801EEE80: sw          $at, 0x8($v1)
    MEM_W(0X8, ctx->r3) = ctx->r1;
    // 0x801EEE84: lw          $at, 0x0($a3)
    ctx->r1 = MEM_W(ctx->r7, 0X0);
    // 0x801EEE88: sw          $t6, 0xC($v1)
    MEM_W(0XC, ctx->r3) = ctx->r14;
    // 0x801EEE8C: sw          $t8, 0x4($a2)
    MEM_W(0X4, ctx->r6) = ctx->r24;
    // 0x801EEE90: sw          $at, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r1;
    // 0x801EEE94: lw          $at, 0x8($a3)
    ctx->r1 = MEM_W(ctx->r7, 0X8);
    // 0x801EEE98: lw          $t8, 0xC($a3)
    ctx->r24 = MEM_W(ctx->r7, 0XC);
    // 0x801EEE9C: lw          $t6, 0x4($t1)
    ctx->r14 = MEM_W(ctx->r9, 0X4);
    // 0x801EEEA0: sw          $at, 0x8($a2)
    MEM_W(0X8, ctx->r6) = ctx->r1;
    // 0x801EEEA4: lw          $at, 0x0($t1)
    ctx->r1 = MEM_W(ctx->r9, 0X0);
    // 0x801EEEA8: sw          $t8, 0xC($a2)
    MEM_W(0XC, ctx->r6) = ctx->r24;
    // 0x801EEEAC: sw          $t6, 0x4($t0)
    MEM_W(0X4, ctx->r8) = ctx->r14;
    // 0x801EEEB0: sw          $at, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r1;
    // 0x801EEEB4: lw          $at, 0x8($t1)
    ctx->r1 = MEM_W(ctx->r9, 0X8);
    // 0x801EEEB8: lw          $t6, 0xC($t1)
    ctx->r14 = MEM_W(ctx->r9, 0XC);
    // 0x801EEEBC: lw          $t8, 0x4($v0)
    ctx->r24 = MEM_W(ctx->r2, 0X4);
    // 0x801EEEC0: sw          $at, 0x8($t0)
    MEM_W(0X8, ctx->r8) = ctx->r1;
    // 0x801EEEC4: lw          $at, 0x0($v0)
    ctx->r1 = MEM_W(ctx->r2, 0X0);
    // 0x801EEEC8: sw          $t6, 0xC($t0)
    MEM_W(0XC, ctx->r8) = ctx->r14;
    // 0x801EEECC: sw          $t8, 0x4($t2)
    MEM_W(0X4, ctx->r10) = ctx->r24;
    // 0x801EEED0: sw          $at, 0x0($t2)
    MEM_W(0X0, ctx->r10) = ctx->r1;
    // 0x801EEED4: lw          $at, 0x8($v0)
    ctx->r1 = MEM_W(ctx->r2, 0X8);
    // 0x801EEED8: lw          $t8, 0xC($v0)
    ctx->r24 = MEM_W(ctx->r2, 0XC);
    // 0x801EEEDC: addiu       $v0, $v0, 0x10
    ctx->r2 = ADD32(ctx->r2, 0X10);
    // 0x801EEEE0: sw          $at, 0x8($t2)
    MEM_W(0X8, ctx->r10) = ctx->r1;
    // 0x801EEEE4: sltu        $at, $v0, $t3
    ctx->r1 = ctx->r2 < ctx->r11 ? 1 : 0;
    // 0x801EEEE8: addiu       $v1, $v1, 0x10
    ctx->r3 = ADD32(ctx->r3, 0X10);
    // 0x801EEEEC: addiu       $a1, $a1, 0x10
    ctx->r5 = ADD32(ctx->r5, 0X10);
    // 0x801EEEF0: addiu       $a2, $a2, 0x10
    ctx->r6 = ADD32(ctx->r6, 0X10);
    // 0x801EEEF4: addiu       $a3, $a3, 0x10
    ctx->r7 = ADD32(ctx->r7, 0X10);
    // 0x801EEEF8: addiu       $t0, $t0, 0x10
    ctx->r8 = ADD32(ctx->r8, 0X10);
    // 0x801EEEFC: addiu       $t1, $t1, 0x10
    ctx->r9 = ADD32(ctx->r9, 0X10);
    // 0x801EEF00: addiu       $t2, $t2, 0x10
    ctx->r10 = ADD32(ctx->r10, 0X10);
    // 0x801EEF04: bne         $at, $zero, L_801EEE64
    if (ctx->r1 != 0) {
        // 0x801EEF08: sw          $t8, -0x4($t2)
        MEM_W(-0X4, ctx->r10) = ctx->r24;
            goto L_801EEE64;
    }
    // 0x801EEF08: sw          $t8, -0x4($t2)
    MEM_W(-0X4, ctx->r10) = ctx->r24;
    // 0x801EEF0C: ori         $at, $zero, 0xB2F0
    ctx->r1 = 0 | 0XB2F0;
    // 0x801EEF10: addu        $t5, $t5, $at
    ctx->r13 = ADD32(ctx->r13, ctx->r1);
    // 0x801EEF14: sltu        $at, $t5, $ra
    ctx->r1 = ctx->r13 < ctx->r31 ? 1 : 0;
    // 0x801EEF18: bnel        $at, $zero, L_801EEE28
    if (ctx->r1 != 0) {
        // 0x801EEF1C: ori         $at, $zero, 0xB240
        ctx->r1 = 0 | 0XB240;
            goto L_801EEE28;
    }
    goto skip_1;
    // 0x801EEF1C: ori         $at, $zero, 0xB240
    ctx->r1 = 0 | 0XB240;
    skip_1:
    // 0x801EEF20: lui         $a3, 0x800E
    ctx->r7 = S32(0X800E << 16);
    // 0x801EEF24: lw          $a3, -0x7E90($a3)
    ctx->r7 = MEM_W(ctx->r7, -0X7E90);
    // 0x801EEF28: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801EEF2C: sw          $zero, -0x72F8($at)
    MEM_W(-0X72F8, ctx->r1) = 0;
    // 0x801EEF30: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801EEF34: addiu       $t9, $zero, 0x3C
    ctx->r25 = ADD32(0, 0X3C);
    // 0x801EEF38: beq         $a3, $zero, L_801EEF58
    if (ctx->r7 == 0) {
        // 0x801EEF3C: sw          $t9, -0x7570($at)
        MEM_W(-0X7570, ctx->r1) = ctx->r25;
            goto L_801EEF58;
    }
    // 0x801EEF3C: sw          $t9, -0x7570($at)
    MEM_W(-0X7570, ctx->r1) = ctx->r25;
    // 0x801EEF40: lui         $s1, 0x801D
    ctx->r17 = S32(0X801D << 16);
    // 0x801EEF44: lw          $s1, -0x19E0($s1)
    ctx->r17 = MEM_W(ctx->r17, -0X19E0);
    // 0x801EEF48: addiu       $at, $zero, 0xB
    ctx->r1 = ADD32(0, 0XB);
    // 0x801EEF4C: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
    // 0x801EEF50: bne         $s1, $at, L_801EEF68
    if (ctx->r17 != ctx->r1) {
        // 0x801EEF54: nop
    
            goto L_801EEF68;
    }
    // 0x801EEF54: nop

L_801EEF58:
    // 0x801EEF58: lui         $s1, 0x801D
    ctx->r17 = S32(0X801D << 16);
    // 0x801EEF5C: lw          $s1, -0x19E0($s1)
    ctx->r17 = MEM_W(ctx->r17, -0X19E0);
    // 0x801EEF60: b           L_801EEF68
    // 0x801EEF64: addiu       $v1, $zero, 0x1
    ctx->r3 = ADD32(0, 0X1);
        goto L_801EEF68;
    // 0x801EEF64: addiu       $v1, $zero, 0x1
    ctx->r3 = ADD32(0, 0X1);
L_801EEF68:
    // 0x801EEF68: lui         $t3, 0x801A
    ctx->r11 = S32(0X801A << 16);
    // 0x801EEF6C: lw          $t3, -0x7D10($t3)
    ctx->r11 = MEM_W(ctx->r11, -0X7D10);
    // 0x801EEF70: lui         $a1, 0x8023
    ctx->r5 = S32(0X8023 << 16);
    // 0x801EEF74: lui         $s0, 0x800E
    ctx->r16 = S32(0X800E << 16);
    // 0x801EEF78: blez        $t3, L_801EEF9C
    if (SIGNED(ctx->r11) <= 0) {
        // 0x801EEF7C: addiu       $a1, $a1, -0x73D8
        ctx->r5 = ADD32(ctx->r5, -0X73D8);
            goto L_801EEF9C;
    }
    // 0x801EEF7C: addiu       $a1, $a1, -0x73D8
    ctx->r5 = ADD32(ctx->r5, -0X73D8);
    // 0x801EEF80: lui         $t6, 0x8023
    ctx->r14 = S32(0X8023 << 16);
    // 0x801EEF84: addiu       $v0, $t6, -0x74A8
    ctx->r2 = ADD32(ctx->r14, -0X74A8);
    // 0x801EEF88: addu        $a0, $t3, $v0
    ctx->r4 = ADD32(ctx->r11, ctx->r2);
L_801EEF8C:
    // 0x801EEF8C: addiu       $v0, $v0, 0x1
    ctx->r2 = ADD32(ctx->r2, 0X1);
    // 0x801EEF90: sltu        $at, $v0, $a0
    ctx->r1 = ctx->r2 < ctx->r4 ? 1 : 0;
    // 0x801EEF94: bne         $at, $zero, L_801EEF8C
    if (ctx->r1 != 0) {
        // 0x801EEF98: sb          $v1, -0x1($v0)
        MEM_B(-0X1, ctx->r2) = ctx->r3;
            goto L_801EEF8C;
    }
    // 0x801EEF98: sb          $v1, -0x1($v0)
    MEM_B(-0X1, ctx->r2) = ctx->r3;
L_801EEF9C:
    // 0x801EEF9C: lw          $s0, -0x54D8($s0)
    ctx->r16 = MEM_W(ctx->r16, -0X54D8);
    // 0x801EEFA0: addiu       $ra, $zero, 0x1
    ctx->r31 = ADD32(0, 0X1);
    // 0x801EEFA4: lui         $a2, 0x8023
    ctx->r6 = S32(0X8023 << 16);
    // 0x801EEFA8: bne         $ra, $s0, L_801EEFC4
    if (ctx->r31 != ctx->r16) {
        // 0x801EEFAC: addiu       $a2, $a2, -0x73D4
        ctx->r6 = ADD32(ctx->r6, -0X73D4);
            goto L_801EEFC4;
    }
    // 0x801EEFAC: addiu       $a2, $a2, -0x73D4
    ctx->r6 = ADD32(ctx->r6, -0X73D4);
    // 0x801EEFB0: lui         $v0, 0x8023
    ctx->r2 = S32(0X8023 << 16);
    // 0x801EEFB4: addiu       $v0, $v0, -0x72F0
    ctx->r2 = ADD32(ctx->r2, -0X72F0);
    // 0x801EEFB8: addiu       $t7, $zero, 0x64
    ctx->r15 = ADD32(0, 0X64);
    // 0x801EEFBC: b           L_801EEFD4
    // 0x801EEFC0: sw          $t7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r15;
        goto L_801EEFD4;
    // 0x801EEFC0: sw          $t7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r15;
L_801EEFC4:
    // 0x801EEFC4: lui         $v0, 0x8023
    ctx->r2 = S32(0X8023 << 16);
    // 0x801EEFC8: addiu       $v0, $v0, -0x72F0
    ctx->r2 = ADD32(ctx->r2, -0X72F0);
    // 0x801EEFCC: addiu       $t8, $zero, 0x32
    ctx->r24 = ADD32(0, 0X32);
    // 0x801EEFD0: sw          $t8, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r24;
L_801EEFD4:
    // 0x801EEFD4: beq         $s1, $zero, L_801EEFE4
    if (ctx->r17 == 0) {
        // 0x801EEFD8: lui         $t0, 0x8023
        ctx->r8 = S32(0X8023 << 16);
            goto L_801EEFE4;
    }
    // 0x801EEFD8: lui         $t0, 0x8023
    ctx->r8 = S32(0X8023 << 16);
    // 0x801EEFDC: addiu       $at, $zero, 0xB
    ctx->r1 = ADD32(0, 0XB);
    // 0x801EEFE0: bne         $s1, $at, L_801EEFF0
    if (ctx->r17 != ctx->r1) {
        // 0x801EEFE4: lui         $at, 0x8023
        ctx->r1 = S32(0X8023 << 16);
            goto L_801EEFF0;
    }
L_801EEFE4:
    // 0x801EEFE4: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801EEFE8: b           L_801EEFFC
    // 0x801EEFEC: sw          $zero, -0x72F4($at)
    MEM_W(-0X72F4, ctx->r1) = 0;
        goto L_801EEFFC;
    // 0x801EEFEC: sw          $zero, -0x72F4($at)
    MEM_W(-0X72F4, ctx->r1) = 0;
L_801EEFF0:
    // 0x801EEFF0: lw          $t9, 0x0($v0)
    ctx->r25 = MEM_W(ctx->r2, 0X0);
    // 0x801EEFF4: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801EEFF8: sw          $t9, -0x72F4($at)
    MEM_W(-0X72F4, ctx->r1) = ctx->r25;
L_801EEFFC:
    // 0x801EEFFC: addiu       $t0, $t0, -0x72E0
    ctx->r8 = ADD32(ctx->r8, -0X72E0);
    // 0x801EF000: sw          $zero, 0x0($t0)
    MEM_W(0X0, ctx->r8) = 0;
    // 0x801EF004: sw          $zero, 0x0($a1)
    MEM_W(0X0, ctx->r5) = 0;
    // 0x801EF008: sw          $zero, 0x0($a2)
    MEM_W(0X0, ctx->r6) = 0;
    // 0x801EF00C: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801EF010: sw          $zero, -0x72E4($at)
    MEM_W(-0X72E4, ctx->r1) = 0;
    // 0x801EF014: lui         $t1, 0x8023
    ctx->r9 = S32(0X8023 << 16);
    // 0x801EF018: lui         $t2, 0x8023
    ctx->r10 = S32(0X8023 << 16);
    // 0x801EF01C: lui         $t4, 0x8023
    ctx->r12 = S32(0X8023 << 16);
    // 0x801EF020: addiu       $t4, $t4, -0x7488
    ctx->r12 = ADD32(ctx->r12, -0X7488);
    // 0x801EF024: addiu       $t2, $t2, -0x7484
    ctx->r10 = ADD32(ctx->r10, -0X7484);
    // 0x801EF028: addiu       $t1, $t1, -0x7480
    ctx->r9 = ADD32(ctx->r9, -0X7480);
    // 0x801EF02C: sw          $zero, 0x0($t1)
    MEM_W(0X0, ctx->r9) = 0;
    // 0x801EF030: sw          $zero, 0x0($t2)
    MEM_W(0X0, ctx->r10) = 0;
    // 0x801EF034: sw          $zero, 0x0($t4)
    MEM_W(0X0, ctx->r12) = 0;
    // 0x801EF038: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801EF03C: lui         $a1, 0x8023
    ctx->r5 = S32(0X8023 << 16);
    // 0x801EF040: lui         $v1, 0x8023
    ctx->r3 = S32(0X8023 << 16);
    // 0x801EF044: lui         $a0, 0x8023
    ctx->r4 = S32(0X8023 << 16);
    // 0x801EF048: lui         $v0, 0x8023
    ctx->r2 = S32(0X8023 << 16);
    // 0x801EF04C: sw          $zero, -0x7568($at)
    MEM_W(-0X7568, ctx->r1) = 0;
    // 0x801EF050: addiu       $v0, $v0, -0x74A0
    ctx->r2 = ADD32(ctx->r2, -0X74A0);
    // 0x801EF054: addiu       $a0, $a0, -0x7498
    ctx->r4 = ADD32(ctx->r4, -0X7498);
    // 0x801EF058: addiu       $v1, $v1, -0x7490
    ctx->r3 = ADD32(ctx->r3, -0X7490);
    // 0x801EF05C: addiu       $a1, $a1, -0x7498
    ctx->r5 = ADD32(ctx->r5, -0X7498);
L_801EF060:
    // 0x801EF060: addiu       $v0, $v0, 0x4
    ctx->r2 = ADD32(ctx->r2, 0X4);
    // 0x801EF064: addiu       $v1, $v1, 0x4
    ctx->r3 = ADD32(ctx->r3, 0X4);
    // 0x801EF068: addiu       $a0, $a0, 0x4
    ctx->r4 = ADD32(ctx->r4, 0X4);
    // 0x801EF06C: sw          $zero, -0x4($v1)
    MEM_W(-0X4, ctx->r3) = 0;
    // 0x801EF070: sw          $zero, -0x4($a0)
    MEM_W(-0X4, ctx->r4) = 0;
    // 0x801EF074: bne         $v0, $a1, L_801EF060
    if (ctx->r2 != ctx->r5) {
        // 0x801EF078: sw          $zero, -0x4($v0)
        MEM_W(-0X4, ctx->r2) = 0;
            goto L_801EF060;
    }
    // 0x801EF078: sw          $zero, -0x4($v0)
    MEM_W(-0X4, ctx->r2) = 0;
    // 0x801EF07C: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801EF080: sw          $zero, -0x7560($at)
    MEM_W(-0X7560, ctx->r1) = 0;
    // 0x801EF084: blez        $s0, L_801EF288
    if (SIGNED(ctx->r16) <= 0) {
        // 0x801EF088: or          $a1, $zero, $zero
        ctx->r5 = 0 | 0;
            goto L_801EF288;
    }
    // 0x801EF088: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x801EF08C: sw          $a3, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r7;
    // 0x801EF090: lui         $t5, 0x800D
    ctx->r13 = S32(0X800D << 16);
    // 0x801EF094: lui         $t2, 0x800D
    ctx->r10 = S32(0X800D << 16);
    // 0x801EF098: lui         $t0, 0x8023
    ctx->r8 = S32(0X8023 << 16);
    // 0x801EF09C: lui         $a2, 0x801C
    ctx->r6 = S32(0X801C << 16);
    // 0x801EF0A0: addiu       $a2, $a2, 0x2938
    ctx->r6 = ADD32(ctx->r6, 0X2938);
    // 0x801EF0A4: addiu       $t0, $t0, -0x72D8
    ctx->r8 = ADD32(ctx->r8, -0X72D8);
    // 0x801EF0A8: addiu       $t2, $t2, 0x48DC
    ctx->r10 = ADD32(ctx->r10, 0X48DC);
    // 0x801EF0AC: addiu       $t5, $t5, 0x48E0
    ctx->r13 = ADD32(ctx->r13, 0X48E0);
    // 0x801EF0B0: addiu       $a3, $zero, 0x378
    ctx->r7 = ADD32(0, 0X378);
    // 0x801EF0B4: addiu       $t4, $zero, 0x18
    ctx->r12 = ADD32(0, 0X18);
    // 0x801EF0B8: addiu       $t1, $zero, 0x14
    ctx->r9 = ADD32(0, 0X14);
L_801EF0BC:
    // 0x801EF0BC: blez        $t3, L_801EF11C
    if (SIGNED(ctx->r11) <= 0) {
        // 0x801EF0C0: or          $a0, $zero, $zero
        ctx->r4 = 0 | 0;
            goto L_801EF11C;
    }
    // 0x801EF0C0: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    // 0x801EF0C4: sll         $t6, $t3, 3
    ctx->r14 = S32(ctx->r11 << 3);
    // 0x801EF0C8: subu        $t6, $t6, $t3
    ctx->r14 = SUB32(ctx->r14, ctx->r11);
    // 0x801EF0CC: sll         $t6, $t6, 4
    ctx->r14 = S32(ctx->r14 << 4);
    // 0x801EF0D0: sll         $t8, $a1, 2
    ctx->r24 = S32(ctx->r5 << 2);
    // 0x801EF0D4: addu        $t8, $t8, $a1
    ctx->r24 = ADD32(ctx->r24, ctx->r5);
    // 0x801EF0D8: subu        $t6, $t6, $t3
    ctx->r14 = SUB32(ctx->r14, ctx->r11);
    // 0x801EF0DC: lui         $t9, 0x801C
    ctx->r25 = S32(0X801C << 16);
    // 0x801EF0E0: addiu       $v1, $t9, 0x2938
    ctx->r3 = ADD32(ctx->r25, 0X2938);
    // 0x801EF0E4: sll         $t6, $t6, 3
    ctx->r14 = S32(ctx->r14 << 3);
    // 0x801EF0E8: sll         $t8, $t8, 4
    ctx->r24 = S32(ctx->r24 << 4);
    // 0x801EF0EC: addu        $v0, $t0, $t8
    ctx->r2 = ADD32(ctx->r8, ctx->r24);
    // 0x801EF0F0: addu        $a0, $t6, $v1
    ctx->r4 = ADD32(ctx->r14, ctx->r3);
    // 0x801EF0F4: lw          $t7, 0x4($v1)
    ctx->r15 = MEM_W(ctx->r3, 0X4);
L_801EF0F8:
    // 0x801EF0F8: addiu       $v1, $v1, 0x378
    ctx->r3 = ADD32(ctx->r3, 0X378);
    // 0x801EF0FC: sltu        $at, $v1, $a0
    ctx->r1 = ctx->r3 < ctx->r4 ? 1 : 0;
    // 0x801EF100: multu       $t7, $t4
    result = U64(U32(ctx->r15)) * U64(U32(ctx->r12)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x801EF104: addiu       $v0, $v0, 0x14
    ctx->r2 = ADD32(ctx->r2, 0X14);
    // 0x801EF108: mflo        $t8
    ctx->r24 = lo;
    // 0x801EF10C: sw          $t8, -0x8($v0)
    MEM_W(-0X8, ctx->r2) = ctx->r24;
    // 0x801EF110: bnel        $at, $zero, L_801EF0F8
    if (ctx->r1 != 0) {
        // 0x801EF114: lw          $t7, 0x4($v1)
        ctx->r15 = MEM_W(ctx->r3, 0X4);
            goto L_801EF0F8;
    }
    goto skip_2;
    // 0x801EF114: lw          $t7, 0x4($v1)
    ctx->r15 = MEM_W(ctx->r3, 0X4);
    skip_2:
    // 0x801EF118: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
L_801EF11C:
    // 0x801EF11C: blez        $t3, L_801EF238
    if (SIGNED(ctx->r11) <= 0) {
        // 0x801EF120: lui         $v1, 0x801C
        ctx->r3 = S32(0X801C << 16);
            goto L_801EF238;
    }
    // 0x801EF120: lui         $v1, 0x801C
    ctx->r3 = S32(0X801C << 16);
    // 0x801EF124: addiu       $v1, $v1, 0x2938
    ctx->r3 = ADD32(ctx->r3, 0X2938);
L_801EF128:
    // 0x801EF128: bne         $ra, $s0, L_801EF180
    if (ctx->r31 != ctx->r16) {
        // 0x801EF12C: nop
    
            goto L_801EF180;
    }
    // 0x801EF12C: nop

    // 0x801EF130: lw          $t6, 0x0($t2)
    ctx->r14 = MEM_W(ctx->r10, 0X0);
    // 0x801EF134: multu       $t6, $a3
    result = U64(U32(ctx->r14)) * U64(U32(ctx->r7)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x801EF138: lw          $t6, 0x4($v1)
    ctx->r14 = MEM_W(ctx->r3, 0X4);
    // 0x801EF13C: mflo        $t9
    ctx->r25 = lo;
    // 0x801EF140: addu        $t7, $a2, $t9
    ctx->r15 = ADD32(ctx->r6, ctx->r25);
    // 0x801EF144: lw          $t8, 0x4($t7)
    ctx->r24 = MEM_W(ctx->r15, 0X4);
    // 0x801EF148: slt         $at, $t8, $t6
    ctx->r1 = SIGNED(ctx->r24) < SIGNED(ctx->r14) ? 1 : 0;
    // 0x801EF14C: beql        $at, $zero, L_801EF228
    if (ctx->r1 == 0) {
        // 0x801EF150: addiu       $a0, $a0, 0x1
        ctx->r4 = ADD32(ctx->r4, 0X1);
            goto L_801EF228;
    }
    goto skip_3;
    // 0x801EF150: addiu       $a0, $a0, 0x1
    ctx->r4 = ADD32(ctx->r4, 0X1);
    skip_3:
    // 0x801EF154: multu       $a0, $t1
    result = U64(U32(ctx->r4)) * U64(U32(ctx->r9)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x801EF158: sll         $t9, $a1, 2
    ctx->r25 = S32(ctx->r5 << 2);
    // 0x801EF15C: addu        $t9, $t9, $a1
    ctx->r25 = ADD32(ctx->r25, ctx->r5);
    // 0x801EF160: sll         $t9, $t9, 4
    ctx->r25 = S32(ctx->r25 << 4);
    // 0x801EF164: addu        $t7, $t0, $t9
    ctx->r15 = ADD32(ctx->r8, ctx->r25);
    // 0x801EF168: mflo        $t8
    ctx->r24 = lo;
    // 0x801EF16C: addu        $v0, $t7, $t8
    ctx->r2 = ADD32(ctx->r15, ctx->r24);
    // 0x801EF170: lw          $t6, 0xC($v0)
    ctx->r14 = MEM_W(ctx->r2, 0XC);
    // 0x801EF174: addiu       $t9, $t6, 0x4
    ctx->r25 = ADD32(ctx->r14, 0X4);
    // 0x801EF178: b           L_801EF224
    // 0x801EF17C: sw          $t9, 0xC($v0)
    MEM_W(0XC, ctx->r2) = ctx->r25;
        goto L_801EF224;
    // 0x801EF17C: sw          $t9, 0xC($v0)
    MEM_W(0XC, ctx->r2) = ctx->r25;
L_801EF180:
    // 0x801EF180: bnel        $a1, $zero, L_801EF1DC
    if (ctx->r5 != 0) {
        // 0x801EF184: lw          $t6, 0x0($t5)
        ctx->r14 = MEM_W(ctx->r13, 0X0);
            goto L_801EF1DC;
    }
    goto skip_4;
    // 0x801EF184: lw          $t6, 0x0($t5)
    ctx->r14 = MEM_W(ctx->r13, 0X0);
    skip_4:
    // 0x801EF188: lw          $t7, 0x0($t2)
    ctx->r15 = MEM_W(ctx->r10, 0X0);
    // 0x801EF18C: multu       $t7, $a3
    result = U64(U32(ctx->r15)) * U64(U32(ctx->r7)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x801EF190: lw          $t7, 0x4($v1)
    ctx->r15 = MEM_W(ctx->r3, 0X4);
    // 0x801EF194: mflo        $t8
    ctx->r24 = lo;
    // 0x801EF198: addu        $t6, $a2, $t8
    ctx->r14 = ADD32(ctx->r6, ctx->r24);
    // 0x801EF19C: lw          $t9, 0x4($t6)
    ctx->r25 = MEM_W(ctx->r14, 0X4);
    // 0x801EF1A0: slt         $at, $t9, $t7
    ctx->r1 = SIGNED(ctx->r25) < SIGNED(ctx->r15) ? 1 : 0;
    // 0x801EF1A4: beql        $at, $zero, L_801EF228
    if (ctx->r1 == 0) {
        // 0x801EF1A8: addiu       $a0, $a0, 0x1
        ctx->r4 = ADD32(ctx->r4, 0X1);
            goto L_801EF228;
    }
    goto skip_5;
    // 0x801EF1A8: addiu       $a0, $a0, 0x1
    ctx->r4 = ADD32(ctx->r4, 0X1);
    skip_5:
    // 0x801EF1AC: multu       $a0, $t1
    result = U64(U32(ctx->r4)) * U64(U32(ctx->r9)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x801EF1B0: sll         $t8, $a1, 2
    ctx->r24 = S32(ctx->r5 << 2);
    // 0x801EF1B4: addu        $t8, $t8, $a1
    ctx->r24 = ADD32(ctx->r24, ctx->r5);
    // 0x801EF1B8: sll         $t8, $t8, 4
    ctx->r24 = S32(ctx->r24 << 4);
    // 0x801EF1BC: addu        $t6, $t0, $t8
    ctx->r14 = ADD32(ctx->r8, ctx->r24);
    // 0x801EF1C0: mflo        $t9
    ctx->r25 = lo;
    // 0x801EF1C4: addu        $v0, $t6, $t9
    ctx->r2 = ADD32(ctx->r14, ctx->r25);
    // 0x801EF1C8: lw          $t7, 0xC($v0)
    ctx->r15 = MEM_W(ctx->r2, 0XC);
    // 0x801EF1CC: addiu       $t8, $t7, 0x4
    ctx->r24 = ADD32(ctx->r15, 0X4);
    // 0x801EF1D0: b           L_801EF224
    // 0x801EF1D4: sw          $t8, 0xC($v0)
    MEM_W(0XC, ctx->r2) = ctx->r24;
        goto L_801EF224;
    // 0x801EF1D4: sw          $t8, 0xC($v0)
    MEM_W(0XC, ctx->r2) = ctx->r24;
    // 0x801EF1D8: lw          $t6, 0x0($t5)
    ctx->r14 = MEM_W(ctx->r13, 0X0);
L_801EF1DC:
    // 0x801EF1DC: multu       $t6, $a3
    result = U64(U32(ctx->r14)) * U64(U32(ctx->r7)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x801EF1E0: lw          $t6, 0x4($v1)
    ctx->r14 = MEM_W(ctx->r3, 0X4);
    // 0x801EF1E4: mflo        $t9
    ctx->r25 = lo;
    // 0x801EF1E8: addu        $t7, $a2, $t9
    ctx->r15 = ADD32(ctx->r6, ctx->r25);
    // 0x801EF1EC: lw          $t8, 0x4($t7)
    ctx->r24 = MEM_W(ctx->r15, 0X4);
    // 0x801EF1F0: slt         $at, $t8, $t6
    ctx->r1 = SIGNED(ctx->r24) < SIGNED(ctx->r14) ? 1 : 0;
    // 0x801EF1F4: beql        $at, $zero, L_801EF228
    if (ctx->r1 == 0) {
        // 0x801EF1F8: addiu       $a0, $a0, 0x1
        ctx->r4 = ADD32(ctx->r4, 0X1);
            goto L_801EF228;
    }
    goto skip_6;
    // 0x801EF1F8: addiu       $a0, $a0, 0x1
    ctx->r4 = ADD32(ctx->r4, 0X1);
    skip_6:
    // 0x801EF1FC: multu       $a0, $t1
    result = U64(U32(ctx->r4)) * U64(U32(ctx->r9)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x801EF200: sll         $t9, $a1, 2
    ctx->r25 = S32(ctx->r5 << 2);
    // 0x801EF204: addu        $t9, $t9, $a1
    ctx->r25 = ADD32(ctx->r25, ctx->r5);
    // 0x801EF208: sll         $t9, $t9, 4
    ctx->r25 = S32(ctx->r25 << 4);
    // 0x801EF20C: addu        $t7, $t0, $t9
    ctx->r15 = ADD32(ctx->r8, ctx->r25);
    // 0x801EF210: mflo        $t8
    ctx->r24 = lo;
    // 0x801EF214: addu        $v0, $t7, $t8
    ctx->r2 = ADD32(ctx->r15, ctx->r24);
    // 0x801EF218: lw          $t6, 0xC($v0)
    ctx->r14 = MEM_W(ctx->r2, 0XC);
    // 0x801EF21C: addiu       $t9, $t6, 0x4
    ctx->r25 = ADD32(ctx->r14, 0X4);
    // 0x801EF220: sw          $t9, 0xC($v0)
    MEM_W(0XC, ctx->r2) = ctx->r25;
L_801EF224:
    // 0x801EF224: addiu       $a0, $a0, 0x1
    ctx->r4 = ADD32(ctx->r4, 0X1);
L_801EF228:
    // 0x801EF228: slt         $at, $a0, $t3
    ctx->r1 = SIGNED(ctx->r4) < SIGNED(ctx->r11) ? 1 : 0;
    // 0x801EF22C: bne         $at, $zero, L_801EF128
    if (ctx->r1 != 0) {
        // 0x801EF230: addiu       $v1, $v1, 0x378
        ctx->r3 = ADD32(ctx->r3, 0X378);
            goto L_801EF128;
    }
    // 0x801EF230: addiu       $v1, $v1, 0x378
    ctx->r3 = ADD32(ctx->r3, 0X378);
    // 0x801EF234: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
L_801EF238:
    // 0x801EF238: blez        $t3, L_801EF270
    if (SIGNED(ctx->r11) <= 0) {
        // 0x801EF23C: sll         $t7, $a1, 2
        ctx->r15 = S32(ctx->r5 << 2);
            goto L_801EF270;
    }
    // 0x801EF23C: sll         $t7, $a1, 2
    ctx->r15 = S32(ctx->r5 << 2);
    // 0x801EF240: addu        $t7, $t7, $a1
    ctx->r15 = ADD32(ctx->r15, ctx->r5);
    // 0x801EF244: sll         $t7, $t7, 4
    ctx->r15 = S32(ctx->r15 << 4);
    // 0x801EF248: addu        $v0, $t0, $t7
    ctx->r2 = ADD32(ctx->r8, ctx->r15);
L_801EF24C:
    // 0x801EF24C: lw          $t8, 0xC($v0)
    ctx->r24 = MEM_W(ctx->r2, 0XC);
    // 0x801EF250: addiu       $a0, $a0, 0x1
    ctx->r4 = ADD32(ctx->r4, 0X1);
    // 0x801EF254: slt         $at, $a0, $t3
    ctx->r1 = SIGNED(ctx->r4) < SIGNED(ctx->r11) ? 1 : 0;
    // 0x801EF258: addiu       $v0, $v0, 0x14
    ctx->r2 = ADD32(ctx->r2, 0X14);
    // 0x801EF25C: sw          $zero, -0x4($v0)
    MEM_W(-0X4, ctx->r2) = 0;
    // 0x801EF260: sw          $zero, -0xC($v0)
    MEM_W(-0XC, ctx->r2) = 0;
    // 0x801EF264: sw          $zero, -0x14($v0)
    MEM_W(-0X14, ctx->r2) = 0;
    // 0x801EF268: bne         $at, $zero, L_801EF24C
    if (ctx->r1 != 0) {
        // 0x801EF26C: sw          $t8, -0x10($v0)
        MEM_W(-0X10, ctx->r2) = ctx->r24;
            goto L_801EF24C;
    }
    // 0x801EF26C: sw          $t8, -0x10($v0)
    MEM_W(-0X10, ctx->r2) = ctx->r24;
L_801EF270:
    // 0x801EF270: addiu       $a1, $a1, 0x1
    ctx->r5 = ADD32(ctx->r5, 0X1);
    // 0x801EF274: slt         $at, $a1, $s0
    ctx->r1 = SIGNED(ctx->r5) < SIGNED(ctx->r16) ? 1 : 0;
    // 0x801EF278: bne         $at, $zero, L_801EF0BC
    if (ctx->r1 != 0) {
        // 0x801EF27C: nop
    
            goto L_801EF0BC;
    }
    // 0x801EF27C: nop

    // 0x801EF280: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x801EF284: lw          $a3, 0x20($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X20);
L_801EF288:
    // 0x801EF288: lui         $v1, 0x8023
    ctx->r3 = S32(0X8023 << 16);
    // 0x801EF28C: lui         $a2, 0x8023
    ctx->r6 = S32(0X8023 << 16);
    // 0x801EF290: lui         $v0, 0x8023
    ctx->r2 = S32(0X8023 << 16);
    // 0x801EF294: lui         $a0, 0x8023
    ctx->r4 = S32(0X8023 << 16);
    // 0x801EF298: addiu       $a0, $a0, -0x7208
    ctx->r4 = ADD32(ctx->r4, -0X7208);
    // 0x801EF29C: addiu       $v0, $v0, -0x7218
    ctx->r2 = ADD32(ctx->r2, -0X7218);
    // 0x801EF2A0: addiu       $a2, $a2, -0x7238
    ctx->r6 = ADD32(ctx->r6, -0X7238);
    // 0x801EF2A4: addiu       $v1, $v1, -0x7228
    ctx->r3 = ADD32(ctx->r3, -0X7228);
L_801EF2A8:
    // 0x801EF2A8: addiu       $v0, $v0, 0x4
    ctx->r2 = ADD32(ctx->r2, 0X4);
    // 0x801EF2AC: sltu        $at, $v0, $a0
    ctx->r1 = ctx->r2 < ctx->r4 ? 1 : 0;
    // 0x801EF2B0: addiu       $v1, $v1, 0x4
    ctx->r3 = ADD32(ctx->r3, 0X4);
    // 0x801EF2B4: addiu       $a2, $a2, 0x4
    ctx->r6 = ADD32(ctx->r6, 0X4);
    // 0x801EF2B8: sw          $zero, -0x4($v1)
    MEM_W(-0X4, ctx->r3) = 0;
    // 0x801EF2BC: sw          $zero, -0x4($a2)
    MEM_W(-0X4, ctx->r6) = 0;
    // 0x801EF2C0: bne         $at, $zero, L_801EF2A8
    if (ctx->r1 != 0) {
        // 0x801EF2C4: sw          $ra, -0x4($v0)
        MEM_W(-0X4, ctx->r2) = ctx->r31;
            goto L_801EF2A8;
    }
    // 0x801EF2C4: sw          $ra, -0x4($v0)
    MEM_W(-0X4, ctx->r2) = ctx->r31;
    // 0x801EF2C8: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801EF2CC: sw          $zero, -0x7520($at)
    MEM_W(-0X7520, ctx->r1) = 0;
    // 0x801EF2D0: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801EF2D4: sw          $zero, -0x7504($at)
    MEM_W(-0X7504, ctx->r1) = 0;
    // 0x801EF2D8: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801EF2DC: sw          $zero, -0x74E8($at)
    MEM_W(-0X74E8, ctx->r1) = 0;
    // 0x801EF2E0: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801EF2E4: sw          $zero, -0x74CC($at)
    MEM_W(-0X74CC, ctx->r1) = 0;
    // 0x801EF2E8: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801EF2EC: sw          $zero, -0x756C($at)
    MEM_W(-0X756C, ctx->r1) = 0;
    // 0x801EF2F0: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801EF2F4: lui         $v0, 0x8023
    ctx->r2 = S32(0X8023 << 16);
    // 0x801EF2F8: sw          $zero, -0x7564($at)
    MEM_W(-0X7564, ctx->r1) = 0;
    // 0x801EF2FC: addiu       $v0, $v0, -0x7204
    ctx->r2 = ADD32(ctx->r2, -0X7204);
    // 0x801EF300: sw          $zero, 0x0($v0)
    MEM_W(0X0, ctx->r2) = 0;
    // 0x801EF304: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801EF308: blez        $s0, L_801EF364
    if (SIGNED(ctx->r16) <= 0) {
        // 0x801EF30C: sw          $zero, -0x7208($at)
        MEM_W(-0X7208, ctx->r1) = 0;
            goto L_801EF364;
    }
    // 0x801EF30C: sw          $zero, -0x7208($at)
    MEM_W(-0X7208, ctx->r1) = 0;
L_801EF310:
    // 0x801EF310: blez        $t3, L_801EF354
    if (SIGNED(ctx->r11) <= 0) {
        // 0x801EF314: or          $a0, $zero, $zero
        ctx->r4 = 0 | 0;
            goto L_801EF354;
    }
    // 0x801EF314: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    // 0x801EF318: sll         $t9, $a1, 2
    ctx->r25 = S32(ctx->r5 << 2);
    // 0x801EF31C: addu        $t9, $t9, $a1
    ctx->r25 = ADD32(ctx->r25, ctx->r5);
    // 0x801EF320: lui         $t7, 0x8023
    ctx->r15 = S32(0X8023 << 16);
    // 0x801EF324: addiu       $t7, $t7, -0x7478
    ctx->r15 = ADD32(ctx->r15, -0X7478);
    // 0x801EF328: sll         $t9, $t9, 4
    ctx->r25 = S32(ctx->r25 << 4);
    // 0x801EF32C: addu        $v0, $t9, $t7
    ctx->r2 = ADD32(ctx->r25, ctx->r15);
L_801EF330:
    // 0x801EF330: addiu       $a0, $a0, 0x1
    ctx->r4 = ADD32(ctx->r4, 0X1);
    // 0x801EF334: slt         $at, $a0, $t3
    ctx->r1 = SIGNED(ctx->r4) < SIGNED(ctx->r11) ? 1 : 0;
    // 0x801EF338: addiu       $v0, $v0, 0x14
    ctx->r2 = ADD32(ctx->r2, 0X14);
    // 0x801EF33C: sw          $zero, -0x8($v0)
    MEM_W(-0X8, ctx->r2) = 0;
    // 0x801EF340: sw          $zero, -0x4($v0)
    MEM_W(-0X4, ctx->r2) = 0;
    // 0x801EF344: swc1        $f0, -0xC($v0)
    MEM_W(-0XC, ctx->r2) = ctx->f0.u32l;
    // 0x801EF348: swc1        $f0, -0x10($v0)
    MEM_W(-0X10, ctx->r2) = ctx->f0.u32l;
    // 0x801EF34C: bne         $at, $zero, L_801EF330
    if (ctx->r1 != 0) {
        // 0x801EF350: swc1        $f0, -0x14($v0)
        MEM_W(-0X14, ctx->r2) = ctx->f0.u32l;
            goto L_801EF330;
    }
    // 0x801EF350: swc1        $f0, -0x14($v0)
    MEM_W(-0X14, ctx->r2) = ctx->f0.u32l;
L_801EF354:
    // 0x801EF354: addiu       $a1, $a1, 0x1
    ctx->r5 = ADD32(ctx->r5, 0X1);
    // 0x801EF358: slt         $at, $a1, $s0
    ctx->r1 = SIGNED(ctx->r5) < SIGNED(ctx->r16) ? 1 : 0;
    // 0x801EF35C: bne         $at, $zero, L_801EF310
    if (ctx->r1 != 0) {
        // 0x801EF360: nop
    
            goto L_801EF310;
    }
    // 0x801EF360: nop

L_801EF364:
    // 0x801EF364: addiu       $at, $zero, 0xB
    ctx->r1 = ADD32(0, 0XB);
    // 0x801EF368: beq         $s1, $at, L_801EF384
    if (ctx->r17 == ctx->r1) {
        // 0x801EF36C: lui         $v0, 0x8023
        ctx->r2 = S32(0X8023 << 16);
            goto L_801EF384;
    }
    // 0x801EF36C: lui         $v0, 0x8023
    ctx->r2 = S32(0X8023 << 16);
    // 0x801EF370: bne         $a3, $zero, L_801EF384
    if (ctx->r7 != 0) {
        // 0x801EF374: addiu       $t8, $zero, 0xDB
        ctx->r24 = ADD32(0, 0XDB);
            goto L_801EF384;
    }
    // 0x801EF374: addiu       $t8, $zero, 0xDB
    ctx->r24 = ADD32(0, 0XDB);
    // 0x801EF378: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801EF37C: b           L_801EF390
    // 0x801EF380: sw          $t8, -0x74A4($at)
    MEM_W(-0X74A4, ctx->r1) = ctx->r24;
        goto L_801EF390;
    // 0x801EF380: sw          $t8, -0x74A4($at)
    MEM_W(-0X74A4, ctx->r1) = ctx->r24;
L_801EF384:
    // 0x801EF384: addiu       $t6, $zero, 0x77
    ctx->r14 = ADD32(0, 0X77);
    // 0x801EF388: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801EF38C: sw          $t6, -0x74A4($at)
    MEM_W(-0X74A4, ctx->r1) = ctx->r14;
L_801EF390:
    // 0x801EF390: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801EF394: lui         $v1, 0x8023
    ctx->r3 = S32(0X8023 << 16);
    // 0x801EF398: sw          $zero, -0x7558($at)
    MEM_W(-0X7558, ctx->r1) = 0;
    // 0x801EF39C: addiu       $v1, $v1, -0x71F8
    ctx->r3 = ADD32(ctx->r3, -0X71F8);
    // 0x801EF3A0: addiu       $v0, $v0, -0x7200
    ctx->r2 = ADD32(ctx->r2, -0X7200);
L_801EF3A4:
    // 0x801EF3A4: addiu       $v0, $v0, 0x4
    ctx->r2 = ADD32(ctx->r2, 0X4);
    // 0x801EF3A8: bne         $v0, $v1, L_801EF3A4
    if (ctx->r2 != ctx->r3) {
        // 0x801EF3AC: sw          $zero, -0x4($v0)
        MEM_W(-0X4, ctx->r2) = 0;
            goto L_801EF3A4;
    }
    // 0x801EF3AC: sw          $zero, -0x4($v0)
    MEM_W(-0X4, ctx->r2) = 0;
    // 0x801EF3B0: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    // 0x801EF3B4: lw          $s0, 0x14($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X14);
    // 0x801EF3B8: lw          $s1, 0x18($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X18);
    // 0x801EF3BC: jr          $ra
    // 0x801EF3C0: addiu       $sp, $sp, 0x40
    ctx->r29 = ADD32(ctx->r29, 0X40);
    return;
    // 0x801EF3C0: addiu       $sp, $sp, 0x40
    ctx->r29 = ADD32(ctx->r29, 0X40);
;}
RECOMP_FUNC void func_801EF3C4(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801EF3C4: addiu       $sp, $sp, -0x80
    ctx->r29 = ADD32(ctx->r29, -0X80);
    // 0x801EF3C8: lui         $at, 0x4180
    ctx->r1 = S32(0X4180 << 16);
    // 0x801EF3CC: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x801EF3D0: sdc1        $f20, 0x30($sp)
    CHECK_FR(ctx, 20);
    SD(ctx->f20.u64, 0X30, ctx->r29);
    // 0x801EF3D4: mtc1        $zero, $f20
    ctx->f20.u32l = 0;
    // 0x801EF3D8: lui         $at, 0x4580
    ctx->r1 = S32(0X4580 << 16);
    // 0x801EF3DC: lui         $a0, 0x801B
    ctx->r4 = S32(0X801B << 16);
    // 0x801EF3E0: lw          $a0, -0x16B8($a0)
    ctx->r4 = MEM_W(ctx->r4, -0X16B8);
    // 0x801EF3E4: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x801EF3E8: sw          $ra, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r31;
    // 0x801EF3EC: lui         $a1, 0x8023
    ctx->r5 = S32(0X8023 << 16);
    // 0x801EF3F0: lui         $a3, 0x3FE2
    ctx->r7 = S32(0X3FE2 << 16);
    // 0x801EF3F4: addiu       $a3, $a3, 0x2222
    ctx->r7 = ADD32(ctx->r7, 0X2222);
    // 0x801EF3F8: addiu       $a1, $a1, -0x72DC
    ctx->r5 = ADD32(ctx->r5, -0X72DC);
    // 0x801EF3FC: lui         $a2, 0x41C0
    ctx->r6 = S32(0X41C0 << 16);
    // 0x801EF400: swc1        $f4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f4.u32l;
    // 0x801EF404: swc1        $f20, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->f20.u32l;
    // 0x801EF408: swc1        $f20, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->f20.u32l;
    // 0x801EF40C: addiu       $a0, $a0, 0x4080
    ctx->r4 = ADD32(ctx->r4, 0X4080);
    // 0x801EF410: jal         0x800481E0
    // 0x801EF414: swc1        $f6, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->f6.u32l;
    func_800481E0(rdram, ctx);
        goto after_0;
    // 0x801EF414: swc1        $f6, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->f6.u32l;
    after_0:
    // 0x801EF418: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801EF41C: lwc1        $f8, 0x7A24($at)
    ctx->f8.u32l = MEM_W(ctx->r1, 0X7A24);
    // 0x801EF420: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x801EF424: lui         $a0, 0x801B
    ctx->r4 = S32(0X801B << 16);
    // 0x801EF428: lw          $a0, -0x16B8($a0)
    ctx->r4 = MEM_W(ctx->r4, -0X16B8);
    // 0x801EF42C: mtc1        $at, $f10
    ctx->f10.u32l = ctx->r1;
    // 0x801EF430: mfc1        $a2, $f20
    ctx->r6 = (int32_t)ctx->f20.u32l;
    // 0x801EF434: addiu       $a1, $sp, 0x40
    ctx->r5 = ADD32(ctx->r29, 0X40);
    // 0x801EF438: lui         $a3, 0x4400
    ctx->r7 = S32(0X4400 << 16);
    // 0x801EF43C: swc1        $f20, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->f20.u32l;
    // 0x801EF440: swc1        $f20, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->f20.u32l;
    // 0x801EF444: swc1        $f20, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->f20.u32l;
    // 0x801EF448: swc1        $f20, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->f20.u32l;
    // 0x801EF44C: swc1        $f20, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->f20.u32l;
    // 0x801EF450: swc1        $f8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f8.u32l;
    // 0x801EF454: addiu       $a0, $a0, 0x40C0
    ctx->r4 = ADD32(ctx->r4, 0X40C0);
    // 0x801EF458: jal         0x800484C8
    // 0x801EF45C: swc1        $f10, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->f10.u32l;
    func_800484C8(rdram, ctx);
        goto after_1;
    // 0x801EF45C: swc1        $f10, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->f10.u32l;
    after_1:
    // 0x801EF460: lui         $at, 0x42F0
    ctx->r1 = S32(0X42F0 << 16);
    // 0x801EF464: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
    // 0x801EF468: lui         $at, 0xC480
    ctx->r1 = S32(0XC480 << 16);
    // 0x801EF46C: mtc1        $at, $f18
    ctx->f18.u32l = ctx->r1;
    // 0x801EF470: lui         $at, 0x4480
    ctx->r1 = S32(0X4480 << 16);
    // 0x801EF474: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x801EF478: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x801EF47C: lui         $a0, 0x801B
    ctx->r4 = S32(0X801B << 16);
    // 0x801EF480: lw          $a0, -0x16B8($a0)
    ctx->r4 = MEM_W(ctx->r4, -0X16B8);
    // 0x801EF484: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x801EF488: lui         $a1, 0xC320
    ctx->r5 = S32(0XC320 << 16);
    // 0x801EF48C: lui         $a2, 0x4320
    ctx->r6 = S32(0X4320 << 16);
    // 0x801EF490: lui         $a3, 0xC2F0
    ctx->r7 = S32(0XC2F0 << 16);
    // 0x801EF494: swc1        $f16, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f16.u32l;
    // 0x801EF498: swc1        $f18, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->f18.u32l;
    // 0x801EF49C: swc1        $f4, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->f4.u32l;
    // 0x801EF4A0: addiu       $a0, $a0, 0x4000
    ctx->r4 = ADD32(ctx->r4, 0X4000);
    // 0x801EF4A4: jal         0x800C74D4
    // 0x801EF4A8: swc1        $f6, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->f6.u32l;
    func_800C74D4(rdram, ctx);
        goto after_2;
    // 0x801EF4A8: swc1        $f6, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->f6.u32l;
    after_2:
    // 0x801EF4AC: lui         $at, 0xC480
    ctx->r1 = S32(0XC480 << 16);
    // 0x801EF4B0: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x801EF4B4: lui         $at, 0x4480
    ctx->r1 = S32(0X4480 << 16);
    // 0x801EF4B8: mtc1        $at, $f10
    ctx->f10.u32l = ctx->r1;
    // 0x801EF4BC: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x801EF4C0: lui         $a0, 0x801B
    ctx->r4 = S32(0X801B << 16);
    // 0x801EF4C4: lw          $a0, -0x16B8($a0)
    ctx->r4 = MEM_W(ctx->r4, -0X16B8);
    // 0x801EF4C8: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
    // 0x801EF4CC: mfc1        $a1, $f20
    ctx->r5 = (int32_t)ctx->f20.u32l;
    // 0x801EF4D0: lui         $a2, 0x43D4
    ctx->r6 = S32(0X43D4 << 16);
    // 0x801EF4D4: lui         $a3, 0x4370
    ctx->r7 = S32(0X4370 << 16);
    // 0x801EF4D8: swc1        $f20, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f20.u32l;
    // 0x801EF4DC: swc1        $f8, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->f8.u32l;
    // 0x801EF4E0: swc1        $f10, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->f10.u32l;
    // 0x801EF4E4: addiu       $a0, $a0, 0x4040
    ctx->r4 = ADD32(ctx->r4, 0X4040);
    // 0x801EF4E8: jal         0x800C74D4
    // 0x801EF4EC: swc1        $f16, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->f16.u32l;
    func_800C74D4(rdram, ctx);
        goto after_3;
    // 0x801EF4EC: swc1        $f16, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->f16.u32l;
    after_3:
    // 0x801EF4F0: lw          $ra, 0x3C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X3C);
    // 0x801EF4F4: ldc1        $f20, 0x30($sp)
    CHECK_FR(ctx, 20);
    ctx->f20.u64 = LD(ctx->r29, 0X30);
    // 0x801EF4F8: addiu       $sp, $sp, 0x80
    ctx->r29 = ADD32(ctx->r29, 0X80);
    // 0x801EF4FC: jr          $ra
    // 0x801EF500: nop

    return;
    // 0x801EF500: nop

;}
RECOMP_FUNC void func_801EF504(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801EF504: addiu       $sp, $sp, -0xB8
    ctx->r29 = ADD32(ctx->r29, -0XB8);
    // 0x801EF508: lui         $t6, 0x800E
    ctx->r14 = S32(0X800E << 16);
    // 0x801EF50C: lw          $t6, -0x54D8($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X54D8);
    // 0x801EF510: sw          $s7, 0x60($sp)
    MEM_W(0X60, ctx->r29) = ctx->r23;
    // 0x801EF514: sw          $ra, 0x64($sp)
    MEM_W(0X64, ctx->r29) = ctx->r31;
    // 0x801EF518: sw          $s6, 0x5C($sp)
    MEM_W(0X5C, ctx->r29) = ctx->r22;
    // 0x801EF51C: sw          $s5, 0x58($sp)
    MEM_W(0X58, ctx->r29) = ctx->r21;
    // 0x801EF520: sw          $s4, 0x54($sp)
    MEM_W(0X54, ctx->r29) = ctx->r20;
    // 0x801EF524: sw          $s3, 0x50($sp)
    MEM_W(0X50, ctx->r29) = ctx->r19;
    // 0x801EF528: sw          $s2, 0x4C($sp)
    MEM_W(0X4C, ctx->r29) = ctx->r18;
    // 0x801EF52C: sw          $s1, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r17;
    // 0x801EF530: sw          $s0, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r16;
    // 0x801EF534: sdc1        $f30, 0x38($sp)
    CHECK_FR(ctx, 30);
    SD(ctx->f30.u64, 0X38, ctx->r29);
    // 0x801EF538: sdc1        $f28, 0x30($sp)
    CHECK_FR(ctx, 28);
    SD(ctx->f28.u64, 0X30, ctx->r29);
    // 0x801EF53C: sdc1        $f26, 0x28($sp)
    CHECK_FR(ctx, 26);
    SD(ctx->f26.u64, 0X28, ctx->r29);
    // 0x801EF540: sdc1        $f24, 0x20($sp)
    CHECK_FR(ctx, 24);
    SD(ctx->f24.u64, 0X20, ctx->r29);
    // 0x801EF544: sdc1        $f22, 0x18($sp)
    CHECK_FR(ctx, 22);
    SD(ctx->f22.u64, 0X18, ctx->r29);
    // 0x801EF548: sdc1        $f20, 0x10($sp)
    CHECK_FR(ctx, 20);
    SD(ctx->f20.u64, 0X10, ctx->r29);
    // 0x801EF54C: blez        $t6, L_801EFF94
    if (SIGNED(ctx->r14) <= 0) {
        // 0x801EF550: or          $s7, $zero, $zero
        ctx->r23 = 0 | 0;
            goto L_801EFF94;
    }
    // 0x801EF550: or          $s7, $zero, $zero
    ctx->r23 = 0 | 0;
    // 0x801EF554: addiu       $s6, $zero, 0x8
    ctx->r22 = ADD32(0, 0X8);
L_801EF558:
    // 0x801EF558: bne         $s7, $zero, L_801EF5E4
    if (ctx->r23 != 0) {
        // 0x801EF55C: lui         $t4, 0x8022
        ctx->r12 = S32(0X8022 << 16);
            goto L_801EF5E4;
    }
    // 0x801EF55C: lui         $t4, 0x8022
    ctx->r12 = S32(0X8022 << 16);
    // 0x801EF560: lui         $v0, 0x800D
    ctx->r2 = S32(0X800D << 16);
    // 0x801EF564: lw          $v0, 0x48DC($v0)
    ctx->r2 = MEM_W(ctx->r2, 0X48DC);
    // 0x801EF568: lui         $t7, 0x8022
    ctx->r15 = S32(0X8022 << 16);
    // 0x801EF56C: lw          $t7, 0x3930($t7)
    ctx->r15 = MEM_W(ctx->r15, 0X3930);
    // 0x801EF570: sll         $t0, $v0, 2
    ctx->r8 = S32(ctx->r2 << 2);
    // 0x801EF574: subu        $t0, $t0, $v0
    ctx->r8 = SUB32(ctx->r8, ctx->r2);
    // 0x801EF578: sll         $t0, $t0, 3
    ctx->r8 = S32(ctx->r8 << 3);
    // 0x801EF57C: subu        $t0, $t0, $v0
    ctx->r8 = SUB32(ctx->r8, ctx->r2);
    // 0x801EF580: sll         $t0, $t0, 3
    ctx->r8 = S32(ctx->r8 << 3);
    // 0x801EF584: sll         $t2, $v0, 3
    ctx->r10 = S32(ctx->r2 << 3);
    // 0x801EF588: sll         $t8, $t7, 4
    ctx->r24 = S32(ctx->r15 << 4);
    // 0x801EF58C: addu        $t0, $t0, $v0
    ctx->r8 = ADD32(ctx->r8, ctx->r2);
    // 0x801EF590: subu        $t2, $t2, $v0
    ctx->r10 = SUB32(ctx->r10, ctx->r2);
    // 0x801EF594: addu        $t8, $t8, $t7
    ctx->r24 = ADD32(ctx->r24, ctx->r15);
    // 0x801EF598: sll         $t8, $t8, 2
    ctx->r24 = S32(ctx->r24 << 2);
    // 0x801EF59C: sll         $t0, $t0, 2
    ctx->r8 = S32(ctx->r8 << 2);
    // 0x801EF5A0: sll         $t2, $t2, 4
    ctx->r10 = S32(ctx->r10 << 4);
    // 0x801EF5A4: lui         $t9, 0x8022
    ctx->r25 = S32(0X8022 << 16);
    // 0x801EF5A8: lui         $t1, 0x8019
    ctx->r9 = S32(0X8019 << 16);
    // 0x801EF5AC: lui         $t3, 0x801C
    ctx->r11 = S32(0X801C << 16);
    // 0x801EF5B0: subu        $t0, $t0, $v0
    ctx->r8 = SUB32(ctx->r8, ctx->r2);
    // 0x801EF5B4: subu        $t2, $t2, $v0
    ctx->r10 = SUB32(ctx->r10, ctx->r2);
    // 0x801EF5B8: subu        $t8, $t8, $t7
    ctx->r24 = SUB32(ctx->r24, ctx->r15);
    // 0x801EF5BC: sll         $t8, $t8, 2
    ctx->r24 = S32(ctx->r24 << 2);
    // 0x801EF5C0: addiu       $t9, $t9, 0x7C80
    ctx->r25 = ADD32(ctx->r25, 0X7C80);
    // 0x801EF5C4: sll         $t0, $t0, 3
    ctx->r8 = S32(ctx->r8 << 3);
    // 0x801EF5C8: addiu       $t1, $t1, 0x2690
    ctx->r9 = ADD32(ctx->r9, 0X2690);
    // 0x801EF5CC: sll         $t2, $t2, 3
    ctx->r10 = S32(ctx->r10 << 3);
    // 0x801EF5D0: addiu       $t3, $t3, 0x2938
    ctx->r11 = ADD32(ctx->r11, 0X2938);
    // 0x801EF5D4: addu        $s1, $t8, $t9
    ctx->r17 = ADD32(ctx->r24, ctx->r25);
    // 0x801EF5D8: addu        $s5, $t0, $t1
    ctx->r21 = ADD32(ctx->r8, ctx->r9);
    // 0x801EF5DC: b           L_801EF660
    // 0x801EF5E0: addu        $s2, $t2, $t3
    ctx->r18 = ADD32(ctx->r10, ctx->r11);
        goto L_801EF660;
    // 0x801EF5E0: addu        $s2, $t2, $t3
    ctx->r18 = ADD32(ctx->r10, ctx->r11);
L_801EF5E4:
    // 0x801EF5E4: lui         $v0, 0x800D
    ctx->r2 = S32(0X800D << 16);
    // 0x801EF5E8: lw          $v0, 0x48E0($v0)
    ctx->r2 = MEM_W(ctx->r2, 0X48E0);
    // 0x801EF5EC: lw          $t4, 0x3934($t4)
    ctx->r12 = MEM_W(ctx->r12, 0X3934);
    // 0x801EF5F0: lui         $t6, 0x8022
    ctx->r14 = S32(0X8022 << 16);
    // 0x801EF5F4: sll         $t7, $v0, 2
    ctx->r15 = S32(ctx->r2 << 2);
    // 0x801EF5F8: subu        $t7, $t7, $v0
    ctx->r15 = SUB32(ctx->r15, ctx->r2);
    // 0x801EF5FC: sll         $t7, $t7, 3
    ctx->r15 = S32(ctx->r15 << 3);
    // 0x801EF600: subu        $t7, $t7, $v0
    ctx->r15 = SUB32(ctx->r15, ctx->r2);
    // 0x801EF604: sll         $t7, $t7, 3
    ctx->r15 = S32(ctx->r15 << 3);
    // 0x801EF608: sll         $t9, $v0, 3
    ctx->r25 = S32(ctx->r2 << 3);
    // 0x801EF60C: sll         $t5, $t4, 4
    ctx->r13 = S32(ctx->r12 << 4);
    // 0x801EF610: addu        $t7, $t7, $v0
    ctx->r15 = ADD32(ctx->r15, ctx->r2);
    // 0x801EF614: subu        $t9, $t9, $v0
    ctx->r25 = SUB32(ctx->r25, ctx->r2);
    // 0x801EF618: addu        $t5, $t5, $t4
    ctx->r13 = ADD32(ctx->r13, ctx->r12);
    // 0x801EF61C: sll         $t5, $t5, 2
    ctx->r13 = S32(ctx->r13 << 2);
    // 0x801EF620: sll         $t7, $t7, 2
    ctx->r15 = S32(ctx->r15 << 2);
    // 0x801EF624: sll         $t9, $t9, 4
    ctx->r25 = S32(ctx->r25 << 4);
    // 0x801EF628: lui         $t8, 0x8019
    ctx->r24 = S32(0X8019 << 16);
    // 0x801EF62C: lui         $t0, 0x801C
    ctx->r8 = S32(0X801C << 16);
    // 0x801EF630: subu        $t7, $t7, $v0
    ctx->r15 = SUB32(ctx->r15, ctx->r2);
    // 0x801EF634: subu        $t9, $t9, $v0
    ctx->r25 = SUB32(ctx->r25, ctx->r2);
    // 0x801EF638: subu        $t5, $t5, $t4
    ctx->r13 = SUB32(ctx->r13, ctx->r12);
    // 0x801EF63C: sll         $t5, $t5, 2
    ctx->r13 = S32(ctx->r13 << 2);
    // 0x801EF640: addiu       $t6, $t6, 0x7C80
    ctx->r14 = ADD32(ctx->r14, 0X7C80);
    // 0x801EF644: sll         $t7, $t7, 3
    ctx->r15 = S32(ctx->r15 << 3);
    // 0x801EF648: addiu       $t8, $t8, 0x2690
    ctx->r24 = ADD32(ctx->r24, 0X2690);
    // 0x801EF64C: sll         $t9, $t9, 3
    ctx->r25 = S32(ctx->r25 << 3);
    // 0x801EF650: addiu       $t0, $t0, 0x2938
    ctx->r8 = ADD32(ctx->r8, 0X2938);
    // 0x801EF654: addu        $s1, $t5, $t6
    ctx->r17 = ADD32(ctx->r13, ctx->r14);
    // 0x801EF658: addu        $s5, $t7, $t8
    ctx->r21 = ADD32(ctx->r15, ctx->r24);
    // 0x801EF65C: addu        $s2, $t9, $t0
    ctx->r18 = ADD32(ctx->r25, ctx->r8);
L_801EF660:
    // 0x801EF660: lwc1        $f26, 0x64($s1)
    ctx->f26.u32l = MEM_W(ctx->r17, 0X64);
    // 0x801EF664: lwc1        $f28, 0x6C($s1)
    ctx->f28.u32l = MEM_W(ctx->r17, 0X6C);
    // 0x801EF668: mul.s       $f4, $f26, $f26
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 26);
    NAN_CHECK(ctx->f26.fl); NAN_CHECK(ctx->f26.fl); 
    ctx->f4.fl = MUL_S(ctx->f26.fl, ctx->f26.fl);
    // 0x801EF66C: nop

    // 0x801EF670: mul.s       $f6, $f28, $f28
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 28);
    CHECK_FR(ctx, 28);
    NAN_CHECK(ctx->f28.fl); NAN_CHECK(ctx->f28.fl); 
    ctx->f6.fl = MUL_S(ctx->f28.fl, ctx->f28.fl);
    // 0x801EF674: jal         0x800C7010
    // 0x801EF678: add.s       $f12, $f4, $f6
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f12.fl = ctx->f4.fl + ctx->f6.fl;
    _nsqrtf(rdram, ctx);
        goto after_0;
    // 0x801EF678: add.s       $f12, $f4, $f6
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f12.fl = ctx->f4.fl + ctx->f6.fl;
    after_0:
    // 0x801EF67C: mtc1        $zero, $f8
    ctx->f8.u32l = 0;
    // 0x801EF680: nop

    // 0x801EF684: c.lt.s      $f8, $f0
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 0);
    c1cs = ctx->f8.fl < ctx->f0.fl;
    // 0x801EF688: nop

    // 0x801EF68C: bc1fl       L_801EF6A0
    if (!c1cs) {
        // 0x801EF690: lw          $t1, 0x2F0($s2)
        ctx->r9 = MEM_W(ctx->r18, 0X2F0);
            goto L_801EF6A0;
    }
    goto skip_0;
    // 0x801EF690: lw          $t1, 0x2F0($s2)
    ctx->r9 = MEM_W(ctx->r18, 0X2F0);
    skip_0:
    // 0x801EF694: div.s       $f26, $f26, $f0
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f26.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f26.fl = DIV_S(ctx->f26.fl, ctx->f0.fl);
    // 0x801EF698: div.s       $f28, $f28, $f0
    CHECK_FR(ctx, 28);
    CHECK_FR(ctx, 28);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f28.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f28.fl = DIV_S(ctx->f28.fl, ctx->f0.fl);
    // 0x801EF69C: lw          $t1, 0x2F0($s2)
    ctx->r9 = MEM_W(ctx->r18, 0X2F0);
L_801EF6A0:
    // 0x801EF6A0: beql        $t1, $zero, L_801EF6D4
    if (ctx->r9 == 0) {
        // 0x801EF6A4: lw          $a0, 0xC($s2)
        ctx->r4 = MEM_W(ctx->r18, 0XC);
            goto L_801EF6D4;
    }
    goto skip_1;
    // 0x801EF6A4: lw          $a0, 0xC($s2)
    ctx->r4 = MEM_W(ctx->r18, 0XC);
    skip_1:
    // 0x801EF6A8: lw          $v0, 0xC($s2)
    ctx->r2 = MEM_W(ctx->r18, 0XC);
    // 0x801EF6AC: lui         $t3, 0x801B
    ctx->r11 = S32(0X801B << 16);
    // 0x801EF6B0: addiu       $t3, $t3, -0x11E0
    ctx->r11 = ADD32(ctx->r11, -0X11E0);
    // 0x801EF6B4: sll         $t2, $v0, 6
    ctx->r10 = S32(ctx->r2 << 6);
    // 0x801EF6B8: addu        $t2, $t2, $v0
    ctx->r10 = ADD32(ctx->r10, ctx->r2);
    // 0x801EF6BC: sll         $t2, $t2, 2
    ctx->r10 = S32(ctx->r10 << 2);
    // 0x801EF6C0: addu        $s3, $t2, $t3
    ctx->r19 = ADD32(ctx->r10, ctx->r11);
    // 0x801EF6C4: lwc1        $f0, 0x0($s3)
    ctx->f0.u32l = MEM_W(ctx->r19, 0X0);
    // 0x801EF6C8: b           L_801EF7E4
    // 0x801EF6CC: lwc1        $f2, 0x8($s3)
    ctx->f2.u32l = MEM_W(ctx->r19, 0X8);
        goto L_801EF7E4;
    // 0x801EF6CC: lwc1        $f2, 0x8($s3)
    ctx->f2.u32l = MEM_W(ctx->r19, 0X8);
    // 0x801EF6D0: lw          $a0, 0xC($s2)
    ctx->r4 = MEM_W(ctx->r18, 0XC);
L_801EF6D4:
    // 0x801EF6D4: lw          $a1, 0x310($s2)
    ctx->r5 = MEM_W(ctx->r18, 0X310);
    // 0x801EF6D8: bnel        $a0, $a1, L_801EF76C
    if (ctx->r4 != ctx->r5) {
        // 0x801EF6DC: sll         $t9, $a1, 6
        ctx->r25 = S32(ctx->r5 << 6);
            goto L_801EF76C;
    }
    goto skip_2;
    // 0x801EF6DC: sll         $t9, $a1, 6
    ctx->r25 = S32(ctx->r5 << 6);
    skip_2:
    // 0x801EF6E0: lw          $t4, 0x0($s2)
    ctx->r12 = MEM_W(ctx->r18, 0X0);
    // 0x801EF6E4: lw          $t5, 0x320($s2)
    ctx->r13 = MEM_W(ctx->r18, 0X320);
    // 0x801EF6E8: sll         $t6, $a0, 6
    ctx->r14 = S32(ctx->r4 << 6);
    // 0x801EF6EC: addu        $t6, $t6, $a0
    ctx->r14 = ADD32(ctx->r14, ctx->r4);
    // 0x801EF6F0: bne         $t4, $t5, L_801EF768
    if (ctx->r12 != ctx->r13) {
        // 0x801EF6F4: sll         $t6, $t6, 2
        ctx->r14 = S32(ctx->r14 << 2);
            goto L_801EF768;
    }
    // 0x801EF6F4: sll         $t6, $t6, 2
    ctx->r14 = S32(ctx->r14 << 2);
    // 0x801EF6F8: lui         $t7, 0x801B
    ctx->r15 = S32(0X801B << 16);
    // 0x801EF6FC: addiu       $t7, $t7, -0x11E0
    ctx->r15 = ADD32(ctx->r15, -0X11E0);
    // 0x801EF700: addu        $s3, $t6, $t7
    ctx->r19 = ADD32(ctx->r14, ctx->r15);
    // 0x801EF704: lwc1        $f0, 0x0($s3)
    ctx->f0.u32l = MEM_W(ctx->r19, 0X0);
    // 0x801EF708: lwc1        $f10, 0x44($s5)
    ctx->f10.u32l = MEM_W(ctx->r21, 0X44);
    // 0x801EF70C: lwc1        $f2, 0x8($s3)
    ctx->f2.u32l = MEM_W(ctx->r19, 0X8);
    // 0x801EF710: lwc1        $f6, 0x4C($s5)
    ctx->f6.u32l = MEM_W(ctx->r21, 0X4C);
    // 0x801EF714: sub.s       $f16, $f10, $f0
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f16.fl = ctx->f10.fl - ctx->f0.fl;
    // 0x801EF718: lwc1        $f18, 0x70($s3)
    ctx->f18.u32l = MEM_W(ctx->r19, 0X70);
    // 0x801EF71C: lwc1        $f10, 0x74($s3)
    ctx->f10.u32l = MEM_W(ctx->r19, 0X74);
    // 0x801EF720: sub.s       $f8, $f6, $f2
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f8.fl = ctx->f6.fl - ctx->f2.fl;
    // 0x801EF724: mul.s       $f4, $f16, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f4.fl = MUL_S(ctx->f16.fl, ctx->f18.fl);
    // 0x801EF728: mtc1        $zero, $f18
    ctx->f18.u32l = 0;
    // 0x801EF72C: or          $v1, $s3, $zero
    ctx->r3 = ctx->r19 | 0;
    // 0x801EF730: mul.s       $f16, $f8, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f16.fl = MUL_S(ctx->f8.fl, ctx->f10.fl);
    // 0x801EF734: add.s       $f12, $f4, $f16
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f12.fl = ctx->f4.fl + ctx->f16.fl;
    // 0x801EF738: c.lt.s      $f18, $f12
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 12);
    c1cs = ctx->f18.fl < ctx->f12.fl;
    // 0x801EF73C: nop

    // 0x801EF740: bc1fl       L_801EF7E8
    if (!c1cs) {
        // 0x801EF744: lwc1        $f16, 0x4C($s1)
        ctx->f16.u32l = MEM_W(ctx->r17, 0X4C);
            goto L_801EF7E8;
    }
    goto skip_3;
    // 0x801EF744: lwc1        $f16, 0x4C($s1)
    ctx->f16.u32l = MEM_W(ctx->r17, 0X4C);
    skip_3:
    // 0x801EF748: lw          $v0, 0xA0($v1)
    ctx->r2 = MEM_W(ctx->r3, 0XA0);
    // 0x801EF74C: sll         $t8, $v0, 6
    ctx->r24 = S32(ctx->r2 << 6);
    // 0x801EF750: addu        $t8, $t8, $v0
    ctx->r24 = ADD32(ctx->r24, ctx->r2);
    // 0x801EF754: sll         $t8, $t8, 2
    ctx->r24 = S32(ctx->r24 << 2);
    // 0x801EF758: addu        $s3, $t8, $t7
    ctx->r19 = ADD32(ctx->r24, ctx->r15);
    // 0x801EF75C: lwc1        $f0, 0x0($s3)
    ctx->f0.u32l = MEM_W(ctx->r19, 0X0);
    // 0x801EF760: b           L_801EF7E4
    // 0x801EF764: lwc1        $f2, 0x8($s3)
    ctx->f2.u32l = MEM_W(ctx->r19, 0X8);
        goto L_801EF7E4;
    // 0x801EF764: lwc1        $f2, 0x8($s3)
    ctx->f2.u32l = MEM_W(ctx->r19, 0X8);
L_801EF768:
    // 0x801EF768: sll         $t9, $a1, 6
    ctx->r25 = S32(ctx->r5 << 6);
L_801EF76C:
    // 0x801EF76C: addu        $t9, $t9, $a1
    ctx->r25 = ADD32(ctx->r25, ctx->r5);
    // 0x801EF770: lui         $t0, 0x801B
    ctx->r8 = S32(0X801B << 16);
    // 0x801EF774: addiu       $t0, $t0, -0x11E0
    ctx->r8 = ADD32(ctx->r8, -0X11E0);
    // 0x801EF778: sll         $t9, $t9, 2
    ctx->r25 = S32(ctx->r25 << 2);
    // 0x801EF77C: addu        $s3, $t9, $t0
    ctx->r19 = ADD32(ctx->r25, ctx->r8);
    // 0x801EF780: lwc1        $f0, 0x0($s3)
    ctx->f0.u32l = MEM_W(ctx->r19, 0X0);
    // 0x801EF784: lwc1        $f6, 0x44($s5)
    ctx->f6.u32l = MEM_W(ctx->r21, 0X44);
    // 0x801EF788: lwc1        $f2, 0x8($s3)
    ctx->f2.u32l = MEM_W(ctx->r19, 0X8);
    // 0x801EF78C: lwc1        $f16, 0x4C($s5)
    ctx->f16.u32l = MEM_W(ctx->r21, 0X4C);
    // 0x801EF790: sub.s       $f8, $f6, $f0
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f8.fl = ctx->f6.fl - ctx->f0.fl;
    // 0x801EF794: lwc1        $f10, 0x70($s3)
    ctx->f10.u32l = MEM_W(ctx->r19, 0X70);
    // 0x801EF798: lwc1        $f6, 0x74($s3)
    ctx->f6.u32l = MEM_W(ctx->r19, 0X74);
    // 0x801EF79C: sub.s       $f18, $f16, $f2
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f18.fl = ctx->f16.fl - ctx->f2.fl;
    // 0x801EF7A0: mul.s       $f4, $f8, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f4.fl = MUL_S(ctx->f8.fl, ctx->f10.fl);
    // 0x801EF7A4: lui         $at, 0xC380
    ctx->r1 = S32(0XC380 << 16);
    // 0x801EF7A8: mtc1        $at, $f10
    ctx->f10.u32l = ctx->r1;
    // 0x801EF7AC: mul.s       $f8, $f18, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = MUL_S(ctx->f18.fl, ctx->f6.fl);
    // 0x801EF7B0: or          $v1, $s3, $zero
    ctx->r3 = ctx->r19 | 0;
    // 0x801EF7B4: add.s       $f12, $f4, $f8
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f12.fl = ctx->f4.fl + ctx->f8.fl;
    // 0x801EF7B8: c.lt.s      $f10, $f12
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 12);
    c1cs = ctx->f10.fl < ctx->f12.fl;
    // 0x801EF7BC: nop

    // 0x801EF7C0: bc1fl       L_801EF7E8
    if (!c1cs) {
        // 0x801EF7C4: lwc1        $f16, 0x4C($s1)
        ctx->f16.u32l = MEM_W(ctx->r17, 0X4C);
            goto L_801EF7E8;
    }
    goto skip_4;
    // 0x801EF7C4: lwc1        $f16, 0x4C($s1)
    ctx->f16.u32l = MEM_W(ctx->r17, 0X4C);
    skip_4:
    // 0x801EF7C8: lw          $v0, 0xA0($v1)
    ctx->r2 = MEM_W(ctx->r3, 0XA0);
    // 0x801EF7CC: sll         $t1, $v0, 6
    ctx->r9 = S32(ctx->r2 << 6);
    // 0x801EF7D0: addu        $t1, $t1, $v0
    ctx->r9 = ADD32(ctx->r9, ctx->r2);
    // 0x801EF7D4: sll         $t1, $t1, 2
    ctx->r9 = S32(ctx->r9 << 2);
    // 0x801EF7D8: addu        $s3, $t1, $t0
    ctx->r19 = ADD32(ctx->r9, ctx->r8);
    // 0x801EF7DC: lwc1        $f0, 0x0($s3)
    ctx->f0.u32l = MEM_W(ctx->r19, 0X0);
    // 0x801EF7E0: lwc1        $f2, 0x8($s3)
    ctx->f2.u32l = MEM_W(ctx->r19, 0X8);
L_801EF7E4:
    // 0x801EF7E4: lwc1        $f16, 0x4C($s1)
    ctx->f16.u32l = MEM_W(ctx->r17, 0X4C);
L_801EF7E8:
    // 0x801EF7E8: lwc1        $f18, 0x54($s1)
    ctx->f18.u32l = MEM_W(ctx->r17, 0X54);
    // 0x801EF7EC: sub.s       $f20, $f0, $f16
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f20.fl = ctx->f0.fl - ctx->f16.fl;
    // 0x801EF7F0: sub.s       $f22, $f2, $f18
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f22.fl = ctx->f2.fl - ctx->f18.fl;
    // 0x801EF7F4: mul.s       $f6, $f20, $f20
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f6.fl = MUL_S(ctx->f20.fl, ctx->f20.fl);
    // 0x801EF7F8: nop

    // 0x801EF7FC: mul.s       $f4, $f22, $f22
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f4.fl = MUL_S(ctx->f22.fl, ctx->f22.fl);
    // 0x801EF800: jal         0x800C7010
    // 0x801EF804: add.s       $f12, $f6, $f4
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f12.fl = ctx->f6.fl + ctx->f4.fl;
    _nsqrtf(rdram, ctx);
        goto after_1;
    // 0x801EF804: add.s       $f12, $f6, $f4
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f12.fl = ctx->f6.fl + ctx->f4.fl;
    after_1:
    // 0x801EF808: mtc1        $zero, $f8
    ctx->f8.u32l = 0;
    // 0x801EF80C: mov.s       $f14, $f0
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 0);
    ctx->f14.fl = ctx->f0.fl;
    // 0x801EF810: c.lt.s      $f8, $f0
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 0);
    c1cs = ctx->f8.fl < ctx->f0.fl;
    // 0x801EF814: nop

    // 0x801EF818: bc1fl       L_801EF82C
    if (!c1cs) {
        // 0x801EF81C: lw          $t2, 0x9C($s3)
        ctx->r10 = MEM_W(ctx->r19, 0X9C);
            goto L_801EF82C;
    }
    goto skip_5;
    // 0x801EF81C: lw          $t2, 0x9C($s3)
    ctx->r10 = MEM_W(ctx->r19, 0X9C);
    skip_5:
    // 0x801EF820: div.s       $f20, $f20, $f0
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f20.fl = DIV_S(ctx->f20.fl, ctx->f0.fl);
    // 0x801EF824: div.s       $f22, $f22, $f0
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f22.fl = DIV_S(ctx->f22.fl, ctx->f0.fl);
    // 0x801EF828: lw          $t2, 0x9C($s3)
    ctx->r10 = MEM_W(ctx->r19, 0X9C);
L_801EF82C:
    // 0x801EF82C: bnel        $t2, $zero, L_801EF8D8
    if (ctx->r10 != 0) {
        // 0x801EF830: or          $s4, $zero, $zero
        ctx->r20 = 0 | 0;
            goto L_801EF8D8;
    }
    goto skip_6;
    // 0x801EF830: or          $s4, $zero, $zero
    ctx->r20 = 0 | 0;
    skip_6:
    // 0x801EF834: lw          $t3, 0x2DC($s2)
    ctx->r11 = MEM_W(ctx->r18, 0X2DC);
    // 0x801EF838: bnel        $t3, $zero, L_801EF8D8
    if (ctx->r11 != 0) {
        // 0x801EF83C: or          $s4, $zero, $zero
        ctx->r20 = 0 | 0;
            goto L_801EF8D8;
    }
    goto skip_7;
    // 0x801EF83C: or          $s4, $zero, $zero
    ctx->r20 = 0 | 0;
    skip_7:
    // 0x801EF840: lwc1        $f0, 0x70($s3)
    ctx->f0.u32l = MEM_W(ctx->r19, 0X70);
    // 0x801EF844: lwc1        $f2, 0x74($s3)
    ctx->f2.u32l = MEM_W(ctx->r19, 0X74);
    // 0x801EF848: lw          $v0, 0x98($s3)
    ctx->r2 = MEM_W(ctx->r19, 0X98);
    // 0x801EF84C: mul.s       $f10, $f0, $f26
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 26);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f26.fl); 
    ctx->f10.fl = MUL_S(ctx->f0.fl, ctx->f26.fl);
    // 0x801EF850: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x801EF854: mul.s       $f16, $f2, $f28
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 28);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f28.fl); 
    ctx->f16.fl = MUL_S(ctx->f2.fl, ctx->f28.fl);
    // 0x801EF858: nop

    // 0x801EF85C: mul.s       $f18, $f0, $f22
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f18.fl = MUL_S(ctx->f0.fl, ctx->f22.fl);
    // 0x801EF860: nop

    // 0x801EF864: mul.s       $f6, $f2, $f20
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f6.fl = MUL_S(ctx->f2.fl, ctx->f20.fl);
    // 0x801EF868: add.s       $f30, $f10, $f16
    CHECK_FR(ctx, 30);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f30.fl = ctx->f10.fl + ctx->f16.fl;
    // 0x801EF86C: bne         $v0, $zero, L_801EF88C
    if (ctx->r2 != 0) {
        // 0x801EF870: sub.s       $f12, $f18, $f6
        CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f12.fl = ctx->f18.fl - ctx->f6.fl;
            goto L_801EF88C;
    }
    // 0x801EF870: sub.s       $f12, $f18, $f6
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f12.fl = ctx->f18.fl - ctx->f6.fl;
    // 0x801EF874: mtc1        $zero, $f4
    ctx->f4.u32l = 0;
    // 0x801EF878: nop

    // 0x801EF87C: c.lt.s      $f4, $f12
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 12);
    c1cs = ctx->f4.fl < ctx->f12.fl;
    // 0x801EF880: nop

    // 0x801EF884: bc1t        L_801EF8C4
    if (c1cs) {
        // 0x801EF888: nop
    
            goto L_801EF8C4;
    }
    // 0x801EF888: nop

L_801EF88C:
    // 0x801EF88C: bnel        $v0, $at, L_801EF8B0
    if (ctx->r2 != ctx->r1) {
        // 0x801EF890: mtc1        $zero, $f10
        ctx->f10.u32l = 0;
            goto L_801EF8B0;
    }
    goto skip_8;
    // 0x801EF890: mtc1        $zero, $f10
    ctx->f10.u32l = 0;
    skip_8:
    // 0x801EF894: mtc1        $zero, $f8
    ctx->f8.u32l = 0;
    // 0x801EF898: nop

    // 0x801EF89C: c.lt.s      $f12, $f8
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 8);
    c1cs = ctx->f12.fl < ctx->f8.fl;
    // 0x801EF8A0: nop

    // 0x801EF8A4: bc1t        L_801EF8C4
    if (c1cs) {
        // 0x801EF8A8: nop
    
            goto L_801EF8C4;
    }
    // 0x801EF8A8: nop

    // 0x801EF8AC: mtc1        $zero, $f10
    ctx->f10.u32l = 0;
L_801EF8B0:
    // 0x801EF8B0: nop

    // 0x801EF8B4: c.lt.s      $f30, $f10
    CHECK_FR(ctx, 30);
    CHECK_FR(ctx, 10);
    c1cs = ctx->f30.fl < ctx->f10.fl;
    // 0x801EF8B8: nop

    // 0x801EF8BC: bc1f        L_801EF8CC
    if (!c1cs) {
        // 0x801EF8C0: nop
    
            goto L_801EF8CC;
    }
    // 0x801EF8C0: nop

L_801EF8C4:
    // 0x801EF8C4: b           L_801EF8D8
    // 0x801EF8C8: or          $s4, $zero, $zero
    ctx->r20 = 0 | 0;
        goto L_801EF8D8;
    // 0x801EF8C8: or          $s4, $zero, $zero
    ctx->r20 = 0 | 0;
L_801EF8CC:
    // 0x801EF8CC: b           L_801EF8D8
    // 0x801EF8D0: addiu       $s4, $zero, 0x1
    ctx->r20 = ADD32(0, 0X1);
        goto L_801EF8D8;
    // 0x801EF8D0: addiu       $s4, $zero, 0x1
    ctx->r20 = ADD32(0, 0X1);
    // 0x801EF8D4: or          $s4, $zero, $zero
    ctx->r20 = 0 | 0;
L_801EF8D8:
    // 0x801EF8D8: mul.s       $f16, $f26, $f20
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f26.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f16.fl = MUL_S(ctx->f26.fl, ctx->f20.fl);
    // 0x801EF8DC: swc1        $f14, 0x68($sp)
    MEM_W(0X68, ctx->r29) = ctx->f14.u32l;
    // 0x801EF8E0: mul.s       $f18, $f28, $f22
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 28);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f28.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f18.fl = MUL_S(ctx->f28.fl, ctx->f22.fl);
    // 0x801EF8E4: add.s       $f24, $f16, $f18
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f24.fl = ctx->f16.fl + ctx->f18.fl;
    // 0x801EF8E8: mov.s       $f30, $f24
    CHECK_FR(ctx, 30);
    CHECK_FR(ctx, 24);
    ctx->f30.fl = ctx->f24.fl;
    // 0x801EF8EC: jal         0x801ED090
    // 0x801EF8F0: mov.s       $f12, $f24
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 24);
    ctx->f12.fl = ctx->f24.fl;
    func_801ED090(rdram, ctx);
        goto after_2;
    // 0x801EF8F0: mov.s       $f12, $f24
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 24);
    ctx->f12.fl = ctx->f24.fl;
    after_2:
    // 0x801EF8F4: mul.s       $f8, $f26, $f22
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f26.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f8.fl = MUL_S(ctx->f26.fl, ctx->f22.fl);
    // 0x801EF8F8: mtc1        $zero, $f4
    ctx->f4.u32l = 0;
    // 0x801EF8FC: lwc1        $f14, 0x68($sp)
    ctx->f14.u32l = MEM_W(ctx->r29, 0X68);
    // 0x801EF900: mul.s       $f10, $f28, $f20
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 28);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f28.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f10.fl = MUL_S(ctx->f28.fl, ctx->f20.fl);
    // 0x801EF904: trunc.w.s   $f6, $f0
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 0);
    ctx->f6.u32l = TRUNC_W_S(ctx->f0.fl);
    // 0x801EF908: sub.s       $f16, $f8, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f16.fl = ctx->f8.fl - ctx->f10.fl;
    // 0x801EF90C: mfc1        $t5, $f6
    ctx->r13 = (int32_t)ctx->f6.u32l;
    // 0x801EF910: c.lt.s      $f4, $f16
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 16);
    c1cs = ctx->f4.fl < ctx->f16.fl;
    // 0x801EF914: sw          $t5, 0x2D4($s2)
    MEM_W(0X2D4, ctx->r18) = ctx->r13;
    // 0x801EF918: bc1f        L_801EF928
    if (!c1cs) {
        // 0x801EF91C: addiu       $t8, $zero, 0x168
        ctx->r24 = ADD32(0, 0X168);
            goto L_801EF928;
    }
    // 0x801EF91C: addiu       $t8, $zero, 0x168
    ctx->r24 = ADD32(0, 0X168);
    // 0x801EF920: subu        $t7, $t8, $t5
    ctx->r15 = SUB32(ctx->r24, ctx->r13);
    // 0x801EF924: sw          $t7, 0x2D4($s2)
    MEM_W(0X2D4, ctx->r18) = ctx->r15;
L_801EF928:
    // 0x801EF928: lw          $a0, 0x2D4($s2)
    ctx->r4 = MEM_W(ctx->r18, 0X2D4);
    // 0x801EF92C: lw          $a1, 0x2D0($s2)
    ctx->r5 = MEM_W(ctx->r18, 0X2D0);
    // 0x801EF930: jal         0x801ED388
    // 0x801EF934: swc1        $f14, 0x68($sp)
    MEM_W(0X68, ctx->r29) = ctx->f14.u32l;
    func_801ED388(rdram, ctx);
        goto after_3;
    // 0x801EF934: swc1        $f14, 0x68($sp)
    MEM_W(0X68, ctx->r29) = ctx->f14.u32l;
    after_3:
    // 0x801EF938: lwc1        $f14, 0x68($sp)
    ctx->f14.u32l = MEM_W(ctx->r29, 0X68);
    // 0x801EF93C: bgez        $v0, L_801EF94C
    if (SIGNED(ctx->r2) >= 0) {
        // 0x801EF940: sra         $v1, $v0, 3
        ctx->r3 = S32(SIGNED(ctx->r2) >> 3);
            goto L_801EF94C;
    }
    // 0x801EF940: sra         $v1, $v0, 3
    ctx->r3 = S32(SIGNED(ctx->r2) >> 3);
    // 0x801EF944: addiu       $at, $v0, 0x7
    ctx->r1 = ADD32(ctx->r2, 0X7);
    // 0x801EF948: sra         $v1, $at, 3
    ctx->r3 = S32(SIGNED(ctx->r1) >> 3);
L_801EF94C:
    // 0x801EF94C: slti        $at, $v1, 0x2
    ctx->r1 = SIGNED(ctx->r3) < 0X2 ? 1 : 0;
    // 0x801EF950: beq         $at, $zero, L_801EF95C
    if (ctx->r1 == 0) {
        // 0x801EF954: or          $s0, $v1, $zero
        ctx->r16 = ctx->r3 | 0;
            goto L_801EF95C;
    }
    // 0x801EF954: or          $s0, $v1, $zero
    ctx->r16 = ctx->r3 | 0;
    // 0x801EF958: addiu       $s0, $zero, 0x2
    ctx->r16 = ADD32(0, 0X2);
L_801EF95C:
    // 0x801EF95C: slt         $at, $s0, $v0
    ctx->r1 = SIGNED(ctx->r16) < SIGNED(ctx->r2) ? 1 : 0;
    // 0x801EF960: bnel        $at, $zero, L_801EF978
    if (ctx->r1 != 0) {
        // 0x801EF964: lw          $a0, 0x2D4($s2)
        ctx->r4 = MEM_W(ctx->r18, 0X2D4);
            goto L_801EF978;
    }
    goto skip_9;
    // 0x801EF964: lw          $a0, 0x2D4($s2)
    ctx->r4 = MEM_W(ctx->r18, 0X2D4);
    skip_9:
    // 0x801EF968: lw          $t9, 0x2D4($s2)
    ctx->r25 = MEM_W(ctx->r18, 0X2D4);
    // 0x801EF96C: b           L_801EF99C
    // 0x801EF970: sw          $t9, 0x2D0($s2)
    MEM_W(0X2D0, ctx->r18) = ctx->r25;
        goto L_801EF99C;
    // 0x801EF970: sw          $t9, 0x2D0($s2)
    MEM_W(0X2D0, ctx->r18) = ctx->r25;
    // 0x801EF974: lw          $a0, 0x2D4($s2)
    ctx->r4 = MEM_W(ctx->r18, 0X2D4);
L_801EF978:
    // 0x801EF978: lw          $a1, 0x2D0($s2)
    ctx->r5 = MEM_W(ctx->r18, 0X2D0);
    // 0x801EF97C: jal         0x801ED4E0
    // 0x801EF980: swc1        $f14, 0x68($sp)
    MEM_W(0X68, ctx->r29) = ctx->f14.u32l;
    func_801ED4E0(rdram, ctx);
        goto after_4;
    // 0x801EF980: swc1        $f14, 0x68($sp)
    MEM_W(0X68, ctx->r29) = ctx->f14.u32l;
    after_4:
    // 0x801EF984: multu       $v0, $s0
    result = U64(U32(ctx->r2)) * U64(U32(ctx->r16)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x801EF988: lw          $t1, 0x2D0($s2)
    ctx->r9 = MEM_W(ctx->r18, 0X2D0);
    // 0x801EF98C: lwc1        $f14, 0x68($sp)
    ctx->f14.u32l = MEM_W(ctx->r29, 0X68);
    // 0x801EF990: mflo        $t0
    ctx->r8 = lo;
    // 0x801EF994: addu        $t2, $t1, $t0
    ctx->r10 = ADD32(ctx->r9, ctx->r8);
    // 0x801EF998: sw          $t2, 0x2D0($s2)
    MEM_W(0X2D0, ctx->r18) = ctx->r10;
L_801EF99C:
    // 0x801EF99C: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801EF9A0: lwc1        $f18, 0x7A28($at)
    ctx->f18.u32l = MEM_W(ctx->r1, 0X7A28);
    // 0x801EF9A4: c.lt.s      $f24, $f18
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 18);
    c1cs = ctx->f24.fl < ctx->f18.fl;
    // 0x801EF9A8: nop

    // 0x801EF9AC: bc1f        L_801EFAEC
    if (!c1cs) {
        // 0x801EF9B0: nop
    
            goto L_801EFAEC;
    }
    // 0x801EF9B0: nop

    // 0x801EF9B4: lw          $t3, 0x9C($s3)
    ctx->r11 = MEM_W(ctx->r19, 0X9C);
    // 0x801EF9B8: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x801EF9BC: bne         $t3, $at, L_801EFAEC
    if (ctx->r11 != ctx->r1) {
        // 0x801EF9C0: nop
    
            goto L_801EFAEC;
    }
    // 0x801EF9C0: nop

    // 0x801EF9C4: lwc1        $f6, 0xC($s3)
    ctx->f6.u32l = MEM_W(ctx->r19, 0XC);
    // 0x801EF9C8: lwc1        $f8, 0x4C($s1)
    ctx->f8.u32l = MEM_W(ctx->r17, 0X4C);
    // 0x801EF9CC: lwc1        $f10, 0x14($s3)
    ctx->f10.u32l = MEM_W(ctx->r19, 0X14);
    // 0x801EF9D0: lwc1        $f4, 0x54($s1)
    ctx->f4.u32l = MEM_W(ctx->r17, 0X54);
    // 0x801EF9D4: sub.s       $f20, $f6, $f8
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f20.fl = ctx->f6.fl - ctx->f8.fl;
    // 0x801EF9D8: sub.s       $f22, $f10, $f4
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f22.fl = ctx->f10.fl - ctx->f4.fl;
    // 0x801EF9DC: mul.s       $f16, $f20, $f20
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f16.fl = MUL_S(ctx->f20.fl, ctx->f20.fl);
    // 0x801EF9E0: nop

    // 0x801EF9E4: mul.s       $f18, $f22, $f22
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f18.fl = MUL_S(ctx->f22.fl, ctx->f22.fl);
    // 0x801EF9E8: jal         0x800C7010
    // 0x801EF9EC: add.s       $f12, $f16, $f18
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f12.fl = ctx->f16.fl + ctx->f18.fl;
    _nsqrtf(rdram, ctx);
        goto after_5;
    // 0x801EF9EC: add.s       $f12, $f16, $f18
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f12.fl = ctx->f16.fl + ctx->f18.fl;
    after_5:
    // 0x801EF9F0: mtc1        $zero, $f6
    ctx->f6.u32l = 0;
    // 0x801EF9F4: mov.s       $f14, $f0
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 0);
    ctx->f14.fl = ctx->f0.fl;
    // 0x801EF9F8: c.lt.s      $f6, $f0
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 0);
    c1cs = ctx->f6.fl < ctx->f0.fl;
    // 0x801EF9FC: nop

    // 0x801EFA00: bc1f        L_801EFA10
    if (!c1cs) {
        // 0x801EFA04: nop
    
            goto L_801EFA10;
    }
    // 0x801EFA04: nop

    // 0x801EFA08: div.s       $f20, $f20, $f0
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f20.fl = DIV_S(ctx->f20.fl, ctx->f0.fl);
    // 0x801EFA0C: div.s       $f22, $f22, $f0
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f22.fl = DIV_S(ctx->f22.fl, ctx->f0.fl);
L_801EFA10:
    // 0x801EFA10: mul.s       $f8, $f26, $f22
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f26.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f8.fl = MUL_S(ctx->f26.fl, ctx->f22.fl);
    // 0x801EFA14: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801EFA18: lwc1        $f18, 0x7A2C($at)
    ctx->f18.u32l = MEM_W(ctx->r1, 0X7A2C);
    // 0x801EFA1C: mul.s       $f10, $f28, $f20
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 28);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f28.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f10.fl = MUL_S(ctx->f28.fl, ctx->f20.fl);
    // 0x801EFA20: nop

    // 0x801EFA24: mul.s       $f4, $f26, $f20
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f26.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f4.fl = MUL_S(ctx->f26.fl, ctx->f20.fl);
    // 0x801EFA28: nop

    // 0x801EFA2C: mul.s       $f16, $f28, $f22
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 28);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f28.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f16.fl = MUL_S(ctx->f28.fl, ctx->f22.fl);
    // 0x801EFA30: sub.s       $f2, $f8, $f10
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f2.fl = ctx->f8.fl - ctx->f10.fl;
    // 0x801EFA34: add.s       $f30, $f4, $f16
    CHECK_FR(ctx, 30);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f30.fl = ctx->f4.fl + ctx->f16.fl;
    // 0x801EFA38: c.lt.s      $f30, $f18
    CHECK_FR(ctx, 30);
    CHECK_FR(ctx, 18);
    c1cs = ctx->f30.fl < ctx->f18.fl;
    // 0x801EFA3C: nop

    // 0x801EFA40: bc1f        L_801EFAEC
    if (!c1cs) {
        // 0x801EFA44: nop
    
            goto L_801EFAEC;
    }
    // 0x801EFA44: nop

    // 0x801EFA48: lwc1        $f6, 0x18($s3)
    ctx->f6.u32l = MEM_W(ctx->r19, 0X18);
    // 0x801EFA4C: lwc1        $f8, 0x4C($s1)
    ctx->f8.u32l = MEM_W(ctx->r17, 0X4C);
    // 0x801EFA50: lwc1        $f10, 0x20($s3)
    ctx->f10.u32l = MEM_W(ctx->r19, 0X20);
    // 0x801EFA54: lwc1        $f4, 0x54($s1)
    ctx->f4.u32l = MEM_W(ctx->r17, 0X54);
    // 0x801EFA58: sub.s       $f20, $f6, $f8
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f20.fl = ctx->f6.fl - ctx->f8.fl;
    // 0x801EFA5C: swc1        $f2, 0x80($sp)
    MEM_W(0X80, ctx->r29) = ctx->f2.u32l;
    // 0x801EFA60: sub.s       $f22, $f10, $f4
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f22.fl = ctx->f10.fl - ctx->f4.fl;
    // 0x801EFA64: mul.s       $f16, $f20, $f20
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f16.fl = MUL_S(ctx->f20.fl, ctx->f20.fl);
    // 0x801EFA68: nop

    // 0x801EFA6C: mul.s       $f18, $f22, $f22
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f18.fl = MUL_S(ctx->f22.fl, ctx->f22.fl);
    // 0x801EFA70: jal         0x800C7010
    // 0x801EFA74: add.s       $f12, $f16, $f18
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f12.fl = ctx->f16.fl + ctx->f18.fl;
    _nsqrtf(rdram, ctx);
        goto after_6;
    // 0x801EFA74: add.s       $f12, $f16, $f18
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f12.fl = ctx->f16.fl + ctx->f18.fl;
    after_6:
    // 0x801EFA78: mtc1        $zero, $f6
    ctx->f6.u32l = 0;
    // 0x801EFA7C: mtc1        $zero, $f8
    ctx->f8.u32l = 0;
    // 0x801EFA80: lwc1        $f2, 0x80($sp)
    ctx->f2.u32l = MEM_W(ctx->r29, 0X80);
    // 0x801EFA84: c.lt.s      $f6, $f0
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 0);
    c1cs = ctx->f6.fl < ctx->f0.fl;
    // 0x801EFA88: mov.s       $f14, $f0
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 0);
    ctx->f14.fl = ctx->f0.fl;
    // 0x801EFA8C: bc1fl       L_801EFAA0
    if (!c1cs) {
        // 0x801EFA90: c.lt.s      $f2, $f8
        CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 8);
    c1cs = ctx->f2.fl < ctx->f8.fl;
            goto L_801EFAA0;
    }
    goto skip_10;
    // 0x801EFA90: c.lt.s      $f2, $f8
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 8);
    c1cs = ctx->f2.fl < ctx->f8.fl;
    skip_10:
    // 0x801EFA94: div.s       $f20, $f20, $f0
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f20.fl = DIV_S(ctx->f20.fl, ctx->f0.fl);
    // 0x801EFA98: div.s       $f22, $f22, $f0
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f22.fl = DIV_S(ctx->f22.fl, ctx->f0.fl);
    // 0x801EFA9C: c.lt.s      $f2, $f8
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 8);
    c1cs = ctx->f2.fl < ctx->f8.fl;
L_801EFAA0:
    // 0x801EFAA0: nop

    // 0x801EFAA4: bc1f        L_801EFADC
    if (!c1cs) {
        // 0x801EFAA8: nop
    
            goto L_801EFADC;
    }
    // 0x801EFAA8: nop

    // 0x801EFAAC: mul.s       $f4, $f26, $f22
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f26.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f4.fl = MUL_S(ctx->f26.fl, ctx->f22.fl);
    // 0x801EFAB0: mtc1        $zero, $f10
    ctx->f10.u32l = 0;
    // 0x801EFAB4: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x801EFAB8: mul.s       $f16, $f28, $f20
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 28);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f28.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f16.fl = MUL_S(ctx->f28.fl, ctx->f20.fl);
    // 0x801EFABC: sub.s       $f18, $f4, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f18.fl = ctx->f4.fl - ctx->f16.fl;
    // 0x801EFAC0: c.lt.s      $f10, $f18
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 18);
    c1cs = ctx->f10.fl < ctx->f18.fl;
    // 0x801EFAC4: nop

    // 0x801EFAC8: bc1f        L_801EFADC
    if (!c1cs) {
        // 0x801EFACC: nop
    
            goto L_801EFADC;
    }
    // 0x801EFACC: nop

    // 0x801EFAD0: mtc1        $at, $f30
    ctx->f30.u32l = ctx->r1;
    // 0x801EFAD4: b           L_801EFAEC
    // 0x801EFAD8: nop

        goto L_801EFAEC;
    // 0x801EFAD8: nop

L_801EFADC:
    // 0x801EFADC: mul.s       $f6, $f26, $f20
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f26.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f6.fl = MUL_S(ctx->f26.fl, ctx->f20.fl);
    // 0x801EFAE0: nop

    // 0x801EFAE4: mul.s       $f8, $f28, $f22
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 28);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f28.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f8.fl = MUL_S(ctx->f28.fl, ctx->f22.fl);
    // 0x801EFAE8: add.s       $f30, $f6, $f8
    CHECK_FR(ctx, 30);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f30.fl = ctx->f6.fl + ctx->f8.fl;
L_801EFAEC:
    // 0x801EFAEC: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801EFAF0: lwc1        $f4, 0x7A30($at)
    ctx->f4.u32l = MEM_W(ctx->r1, 0X7A30);
    // 0x801EFAF4: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    // 0x801EFAF8: c.lt.s      $f30, $f4
    CHECK_FR(ctx, 30);
    CHECK_FR(ctx, 4);
    c1cs = ctx->f30.fl < ctx->f4.fl;
    // 0x801EFAFC: nop

    // 0x801EFB00: bc1f        L_801EFB0C
    if (!c1cs) {
        // 0x801EFB04: nop
    
            goto L_801EFB0C;
    }
    // 0x801EFB04: nop

    // 0x801EFB08: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
L_801EFB0C:
    // 0x801EFB0C: beq         $v0, $zero, L_801EFB40
    if (ctx->r2 == 0) {
        // 0x801EFB10: or          $v1, $v0, $zero
        ctx->r3 = ctx->r2 | 0;
            goto L_801EFB40;
    }
    // 0x801EFB10: or          $v1, $v0, $zero
    ctx->r3 = ctx->r2 | 0;
    // 0x801EFB14: lui         $at, 0x4500
    ctx->r1 = S32(0X4500 << 16);
    // 0x801EFB18: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
    // 0x801EFB1C: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    // 0x801EFB20: c.lt.s      $f16, $f14
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 14);
    c1cs = ctx->f16.fl < ctx->f14.fl;
    // 0x801EFB24: nop

    // 0x801EFB28: bc1f        L_801EFB34
    if (!c1cs) {
        // 0x801EFB2C: nop
    
            goto L_801EFB34;
    }
    // 0x801EFB2C: nop

    // 0x801EFB30: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
L_801EFB34:
    // 0x801EFB34: bne         $v0, $zero, L_801EFB40
    if (ctx->r2 != 0) {
        // 0x801EFB38: or          $v1, $v0, $zero
        ctx->r3 = ctx->r2 | 0;
            goto L_801EFB40;
    }
    // 0x801EFB38: or          $v1, $v0, $zero
    ctx->r3 = ctx->r2 | 0;
    // 0x801EFB3C: sltiu       $v1, $s4, 0x1
    ctx->r3 = ctx->r20 < 0X1 ? 1 : 0;
L_801EFB40:
    // 0x801EFB40: lw          $t4, 0x31C($s2)
    ctx->r12 = MEM_W(ctx->r18, 0X31C);
    // 0x801EFB44: or          $s4, $v1, $zero
    ctx->r20 = ctx->r3 | 0;
    // 0x801EFB48: beql        $t4, $zero, L_801EFB58
    if (ctx->r12 == 0) {
        // 0x801EFB4C: lwc1        $f12, 0x4C($s1)
        ctx->f12.u32l = MEM_W(ctx->r17, 0X4C);
            goto L_801EFB58;
    }
    goto skip_11;
    // 0x801EFB4C: lwc1        $f12, 0x4C($s1)
    ctx->f12.u32l = MEM_W(ctx->r17, 0X4C);
    skip_11:
    // 0x801EFB50: or          $s4, $zero, $zero
    ctx->r20 = 0 | 0;
    // 0x801EFB54: lwc1        $f12, 0x4C($s1)
    ctx->f12.u32l = MEM_W(ctx->r17, 0X4C);
L_801EFB58:
    // 0x801EFB58: jal         0x80074448
    // 0x801EFB5C: lwc1        $f14, 0x54($s1)
    ctx->f14.u32l = MEM_W(ctx->r17, 0X54);
    func_80074448(rdram, ctx);
        goto after_7;
    // 0x801EFB5C: lwc1        $f14, 0x54($s1)
    ctx->f14.u32l = MEM_W(ctx->r17, 0X54);
    after_7:
    // 0x801EFB60: beq         $v0, $zero, L_801EFB6C
    if (ctx->r2 == 0) {
        // 0x801EFB64: nop
    
            goto L_801EFB6C;
    }
    // 0x801EFB64: nop

    // 0x801EFB68: or          $s4, $zero, $zero
    ctx->r20 = 0 | 0;
L_801EFB6C:
    // 0x801EFB6C: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x801EFB70: lw          $v0, -0x19E0($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X19E0);
    // 0x801EFB74: addiu       $at, $zero, 0xB
    ctx->r1 = ADD32(0, 0XB);
    // 0x801EFB78: bne         $v0, $at, L_801EFCA8
    if (ctx->r2 != ctx->r1) {
        // 0x801EFB7C: lui         $v1, 0x801C
        ctx->r3 = S32(0X801C << 16);
            goto L_801EFCA8;
    }
    // 0x801EFB7C: lui         $v1, 0x801C
    ctx->r3 = S32(0X801C << 16);
    // 0x801EFB80: lw          $v1, -0x5C0($v1)
    ctx->r3 = MEM_W(ctx->r3, -0X5C0);
    // 0x801EFB84: lui         $s0, 0x801C
    ctx->r16 = S32(0X801C << 16);
    // 0x801EFB88: sw          $zero, 0x98($sp)
    MEM_W(0X98, ctx->r29) = 0;
    // 0x801EFB8C: blez        $v1, L_801EFC98
    if (SIGNED(ctx->r3) <= 0) {
        // 0x801EFB90: addiu       $s0, $s0, -0x36C0
        ctx->r16 = ADD32(ctx->r16, -0X36C0);
            goto L_801EFC98;
    }
    // 0x801EFB90: addiu       $s0, $s0, -0x36C0
    ctx->r16 = ADD32(ctx->r16, -0X36C0);
    // 0x801EFB94: lw          $t5, 0x4C($s0)
    ctx->r13 = MEM_W(ctx->r16, 0X4C);
L_801EFB98:
    // 0x801EFB98: sll         $t8, $v1, 2
    ctx->r24 = S32(ctx->r3 << 2);
    // 0x801EFB9C: subu        $t8, $t8, $v1
    ctx->r24 = SUB32(ctx->r24, ctx->r3);
    // 0x801EFBA0: beq         $s6, $t5, L_801EFBC0
    if (ctx->r22 == ctx->r13) {
        // 0x801EFBA4: sll         $t8, $t8, 4
        ctx->r24 = S32(ctx->r24 << 4);
            goto L_801EFBC0;
    }
    // 0x801EFBA4: sll         $t8, $t8, 4
    ctx->r24 = S32(ctx->r24 << 4);
    // 0x801EFBA8: addu        $t8, $t8, $v1
    ctx->r24 = ADD32(ctx->r24, ctx->r3);
    // 0x801EFBAC: lui         $t6, 0x801C
    ctx->r14 = S32(0X801C << 16);
    // 0x801EFBB0: addiu       $t6, $t6, -0x36C0
    ctx->r14 = ADD32(ctx->r14, -0X36C0);
    // 0x801EFBB4: sll         $t8, $t8, 2
    ctx->r24 = S32(ctx->r24 << 2);
    // 0x801EFBB8: b           L_801EFC80
    // 0x801EFBBC: addu        $v0, $t8, $t6
    ctx->r2 = ADD32(ctx->r24, ctx->r14);
        goto L_801EFC80;
    // 0x801EFBBC: addu        $v0, $t8, $t6
    ctx->r2 = ADD32(ctx->r24, ctx->r14);
L_801EFBC0:
    // 0x801EFBC0: lwc1        $f10, 0x0($s0)
    ctx->f10.u32l = MEM_W(ctx->r16, 0X0);
    // 0x801EFBC4: lwc1        $f18, 0x4C($s1)
    ctx->f18.u32l = MEM_W(ctx->r17, 0X4C);
    // 0x801EFBC8: lwc1        $f6, 0x8($s0)
    ctx->f6.u32l = MEM_W(ctx->r16, 0X8);
    // 0x801EFBCC: lwc1        $f8, 0x54($s1)
    ctx->f8.u32l = MEM_W(ctx->r17, 0X54);
    // 0x801EFBD0: sub.s       $f20, $f10, $f18
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f20.fl = ctx->f10.fl - ctx->f18.fl;
    // 0x801EFBD4: sub.s       $f22, $f6, $f8
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f22.fl = ctx->f6.fl - ctx->f8.fl;
    // 0x801EFBD8: mul.s       $f4, $f20, $f20
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f4.fl = MUL_S(ctx->f20.fl, ctx->f20.fl);
    // 0x801EFBDC: nop

    // 0x801EFBE0: mul.s       $f16, $f22, $f22
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f16.fl = MUL_S(ctx->f22.fl, ctx->f22.fl);
    // 0x801EFBE4: jal         0x800C7010
    // 0x801EFBE8: add.s       $f12, $f4, $f16
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f12.fl = ctx->f4.fl + ctx->f16.fl;
    _nsqrtf(rdram, ctx);
        goto after_8;
    // 0x801EFBE8: add.s       $f12, $f4, $f16
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f12.fl = ctx->f4.fl + ctx->f16.fl;
    after_8:
    // 0x801EFBEC: mtc1        $zero, $f10
    ctx->f10.u32l = 0;
    // 0x801EFBF0: lui         $v1, 0x801C
    ctx->r3 = S32(0X801C << 16);
    // 0x801EFBF4: c.lt.s      $f10, $f0
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 0);
    c1cs = ctx->f10.fl < ctx->f0.fl;
    // 0x801EFBF8: nop

    // 0x801EFBFC: bc1f        L_801EFC0C
    if (!c1cs) {
        // 0x801EFC00: nop
    
            goto L_801EFC0C;
    }
    // 0x801EFC00: nop

    // 0x801EFC04: div.s       $f20, $f20, $f0
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f20.fl = DIV_S(ctx->f20.fl, ctx->f0.fl);
    // 0x801EFC08: div.s       $f22, $f22, $f0
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f22.fl = DIV_S(ctx->f22.fl, ctx->f0.fl);
L_801EFC0C:
    // 0x801EFC0C: mul.s       $f18, $f26, $f20
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f26.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f18.fl = MUL_S(ctx->f26.fl, ctx->f20.fl);
    // 0x801EFC10: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801EFC14: lwc1        $f4, 0x7A34($at)
    ctx->f4.u32l = MEM_W(ctx->r1, 0X7A34);
    // 0x801EFC18: mul.s       $f6, $f28, $f22
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 28);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f28.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f6.fl = MUL_S(ctx->f28.fl, ctx->f22.fl);
    // 0x801EFC1C: lui         $at, 0x4580
    ctx->r1 = S32(0X4580 << 16);
    // 0x801EFC20: add.s       $f8, $f18, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = ctx->f18.fl + ctx->f6.fl;
    // 0x801EFC24: c.le.s      $f4, $f8
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    c1cs = ctx->f4.fl <= ctx->f8.fl;
    // 0x801EFC28: nop

    // 0x801EFC2C: bc1f        L_801EFC5C
    if (!c1cs) {
        // 0x801EFC30: nop
    
            goto L_801EFC5C;
    }
    // 0x801EFC30: nop

    // 0x801EFC34: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
    // 0x801EFC38: nop

    // 0x801EFC3C: c.lt.s      $f0, $f16
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 16);
    c1cs = ctx->f0.fl < ctx->f16.fl;
    // 0x801EFC40: nop

    // 0x801EFC44: bc1f        L_801EFC5C
    if (!c1cs) {
        // 0x801EFC48: addiu       $t7, $zero, 0x1
        ctx->r15 = ADD32(0, 0X1);
            goto L_801EFC5C;
    }
    // 0x801EFC48: addiu       $t7, $zero, 0x1
    ctx->r15 = ADD32(0, 0X1);
    // 0x801EFC4C: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x801EFC50: sw          $t7, 0x98($sp)
    MEM_W(0X98, ctx->r29) = ctx->r15;
    // 0x801EFC54: b           L_801EFC98
    // 0x801EFC58: lw          $v0, -0x19E0($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X19E0);
        goto L_801EFC98;
    // 0x801EFC58: lw          $v0, -0x19E0($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X19E0);
L_801EFC5C:
    // 0x801EFC5C: lw          $v1, -0x5C0($v1)
    ctx->r3 = MEM_W(ctx->r3, -0X5C0);
    // 0x801EFC60: lui         $t1, 0x801C
    ctx->r9 = S32(0X801C << 16);
    // 0x801EFC64: addiu       $t1, $t1, -0x36C0
    ctx->r9 = ADD32(ctx->r9, -0X36C0);
    // 0x801EFC68: sll         $t9, $v1, 2
    ctx->r25 = S32(ctx->r3 << 2);
    // 0x801EFC6C: subu        $t9, $t9, $v1
    ctx->r25 = SUB32(ctx->r25, ctx->r3);
    // 0x801EFC70: sll         $t9, $t9, 4
    ctx->r25 = S32(ctx->r25 << 4);
    // 0x801EFC74: addu        $t9, $t9, $v1
    ctx->r25 = ADD32(ctx->r25, ctx->r3);
    // 0x801EFC78: sll         $t9, $t9, 2
    ctx->r25 = S32(ctx->r25 << 2);
    // 0x801EFC7C: addu        $v0, $t9, $t1
    ctx->r2 = ADD32(ctx->r25, ctx->r9);
L_801EFC80:
    // 0x801EFC80: addiu       $s0, $s0, 0xC4
    ctx->r16 = ADD32(ctx->r16, 0XC4);
    // 0x801EFC84: sltu        $at, $s0, $v0
    ctx->r1 = ctx->r16 < ctx->r2 ? 1 : 0;
    // 0x801EFC88: bnel        $at, $zero, L_801EFB98
    if (ctx->r1 != 0) {
        // 0x801EFC8C: lw          $t5, 0x4C($s0)
        ctx->r13 = MEM_W(ctx->r16, 0X4C);
            goto L_801EFB98;
    }
    goto skip_12;
    // 0x801EFC8C: lw          $t5, 0x4C($s0)
    ctx->r13 = MEM_W(ctx->r16, 0X4C);
    skip_12:
    // 0x801EFC90: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x801EFC94: lw          $v0, -0x19E0($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X19E0);
L_801EFC98:
    // 0x801EFC98: lw          $t0, 0x98($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X98);
    // 0x801EFC9C: beql        $t0, $zero, L_801EFCAC
    if (ctx->r8 == 0) {
        // 0x801EFCA0: lw          $t2, 0x2F0($s2)
        ctx->r10 = MEM_W(ctx->r18, 0X2F0);
            goto L_801EFCAC;
    }
    goto skip_13;
    // 0x801EFCA0: lw          $t2, 0x2F0($s2)
    ctx->r10 = MEM_W(ctx->r18, 0X2F0);
    skip_13:
    // 0x801EFCA4: or          $s4, $zero, $zero
    ctx->r20 = 0 | 0;
L_801EFCA8:
    // 0x801EFCA8: lw          $t2, 0x2F0($s2)
    ctx->r10 = MEM_W(ctx->r18, 0X2F0);
L_801EFCAC:
    // 0x801EFCAC: bnel        $t2, $zero, L_801EFCD4
    if (ctx->r10 != 0) {
        // 0x801EFCB0: addiu       $s4, $zero, 0x1
        ctx->r20 = ADD32(0, 0X1);
            goto L_801EFCD4;
    }
    goto skip_14;
    // 0x801EFCB0: addiu       $s4, $zero, 0x1
    ctx->r20 = ADD32(0, 0X1);
    skip_14:
    // 0x801EFCB4: lw          $t3, 0x2E4($s2)
    ctx->r11 = MEM_W(ctx->r18, 0X2E4);
    // 0x801EFCB8: bnel        $t3, $zero, L_801EFCD4
    if (ctx->r11 != 0) {
        // 0x801EFCBC: addiu       $s4, $zero, 0x1
        ctx->r20 = ADD32(0, 0X1);
            goto L_801EFCD4;
    }
    goto skip_15;
    // 0x801EFCBC: addiu       $s4, $zero, 0x1
    ctx->r20 = ADD32(0, 0X1);
    skip_15:
    // 0x801EFCC0: lw          $t4, 0x328($s2)
    ctx->r12 = MEM_W(ctx->r18, 0X328);
    // 0x801EFCC4: slti        $at, $t4, 0x28
    ctx->r1 = SIGNED(ctx->r12) < 0X28 ? 1 : 0;
    // 0x801EFCC8: bnel        $at, $zero, L_801EFCD8
    if (ctx->r1 != 0) {
        // 0x801EFCCC: addiu       $at, $zero, 0xB
        ctx->r1 = ADD32(0, 0XB);
            goto L_801EFCD8;
    }
    goto skip_16;
    // 0x801EFCCC: addiu       $at, $zero, 0xB
    ctx->r1 = ADD32(0, 0XB);
    skip_16:
    // 0x801EFCD0: addiu       $s4, $zero, 0x1
    ctx->r20 = ADD32(0, 0X1);
L_801EFCD4:
    // 0x801EFCD4: addiu       $at, $zero, 0xB
    ctx->r1 = ADD32(0, 0XB);
L_801EFCD8:
    // 0x801EFCD8: beq         $v0, $at, L_801EFCF0
    if (ctx->r2 == ctx->r1) {
        // 0x801EFCDC: lui         $t5, 0x800E
        ctx->r13 = S32(0X800E << 16);
            goto L_801EFCF0;
    }
    // 0x801EFCDC: lui         $t5, 0x800E
    ctx->r13 = S32(0X800E << 16);
    // 0x801EFCE0: lw          $t5, -0x7E90($t5)
    ctx->r13 = MEM_W(ctx->r13, -0X7E90);
    // 0x801EFCE4: bne         $t5, $zero, L_801EFCF0
    if (ctx->r13 != 0) {
        // 0x801EFCE8: nop
    
            goto L_801EFCF0;
    }
    // 0x801EFCE8: nop

    // 0x801EFCEC: or          $s4, $zero, $zero
    ctx->r20 = 0 | 0;
L_801EFCF0:
    // 0x801EFCF0: beq         $s4, $zero, L_801EFD70
    if (ctx->r20 == 0) {
        // 0x801EFCF4: lui         $t8, 0x800E
        ctx->r24 = S32(0X800E << 16);
            goto L_801EFD70;
    }
    // 0x801EFCF4: lui         $t8, 0x800E
    ctx->r24 = S32(0X800E << 16);
    // 0x801EFCF8: lh          $t8, -0x5498($t8)
    ctx->r24 = MEM_H(ctx->r24, -0X5498);
    // 0x801EFCFC: lui         $t6, 0x800E
    ctx->r14 = S32(0X800E << 16);
    // 0x801EFD00: beq         $t8, $zero, L_801EFD70
    if (ctx->r24 == 0) {
        // 0x801EFD04: nop
    
            goto L_801EFD70;
    }
    // 0x801EFD04: nop

    // 0x801EFD08: lw          $t6, -0x7E90($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X7E90);
    // 0x801EFD0C: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x801EFD10: bne         $t6, $at, L_801EFD70
    if (ctx->r14 != ctx->r1) {
        // 0x801EFD14: nop
    
            goto L_801EFD70;
    }
    // 0x801EFD14: nop

    // 0x801EFD18: lw          $t7, 0x0($s2)
    ctx->r15 = MEM_W(ctx->r18, 0X0);
    // 0x801EFD1C: slti        $at, $t7, 0x2
    ctx->r1 = SIGNED(ctx->r15) < 0X2 ? 1 : 0;
    // 0x801EFD20: bne         $at, $zero, L_801EFD70
    if (ctx->r1 != 0) {
        // 0x801EFD24: lui         $at, 0x8022
        ctx->r1 = S32(0X8022 << 16);
            goto L_801EFD70;
    }
    // 0x801EFD24: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801EFD28: lwc1        $f18, 0x7A38($at)
    ctx->f18.u32l = MEM_W(ctx->r1, 0X7A38);
    // 0x801EFD2C: lwc1        $f10, 0x44($s5)
    ctx->f10.u32l = MEM_W(ctx->r21, 0X44);
    // 0x801EFD30: lui         $at, 0x452F
    ctx->r1 = S32(0X452F << 16);
    // 0x801EFD34: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x801EFD38: sub.s       $f20, $f10, $f18
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f20.fl = ctx->f10.fl - ctx->f18.fl;
    // 0x801EFD3C: lwc1        $f6, 0x4C($s5)
    ctx->f6.u32l = MEM_W(ctx->r21, 0X4C);
    // 0x801EFD40: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801EFD44: lwc1        $f18, 0x7A3C($at)
    ctx->f18.u32l = MEM_W(ctx->r1, 0X7A3C);
    // 0x801EFD48: sub.s       $f22, $f6, $f8
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f22.fl = ctx->f6.fl - ctx->f8.fl;
    // 0x801EFD4C: mul.s       $f4, $f20, $f20
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f4.fl = MUL_S(ctx->f20.fl, ctx->f20.fl);
    // 0x801EFD50: nop

    // 0x801EFD54: mul.s       $f16, $f22, $f22
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f16.fl = MUL_S(ctx->f22.fl, ctx->f22.fl);
    // 0x801EFD58: add.s       $f10, $f4, $f16
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f10.fl = ctx->f4.fl + ctx->f16.fl;
    // 0x801EFD5C: c.lt.s      $f10, $f18
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 18);
    c1cs = ctx->f10.fl < ctx->f18.fl;
    // 0x801EFD60: nop

    // 0x801EFD64: bc1f        L_801EFD70
    if (!c1cs) {
        // 0x801EFD68: nop
    
            goto L_801EFD70;
    }
    // 0x801EFD68: nop

    // 0x801EFD6C: or          $s4, $zero, $zero
    ctx->r20 = 0 | 0;
L_801EFD70:
    // 0x801EFD70: beq         $s4, $zero, L_801EFD9C
    if (ctx->r20 == 0) {
        // 0x801EFD74: or          $v0, $zero, $zero
        ctx->r2 = 0 | 0;
            goto L_801EFD9C;
    }
    // 0x801EFD74: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    // 0x801EFD78: lw          $v0, 0x2D8($s2)
    ctx->r2 = MEM_W(ctx->r18, 0X2D8);
    // 0x801EFD7C: lui         $at, 0x7FFF
    ctx->r1 = S32(0X7FFF << 16);
    // 0x801EFD80: ori         $at, $at, 0xFFFF
    ctx->r1 = ctx->r1 | 0XFFFF;
    // 0x801EFD84: slt         $at, $v0, $at
    ctx->r1 = SIGNED(ctx->r2) < SIGNED(ctx->r1) ? 1 : 0;
    // 0x801EFD88: beq         $at, $zero, L_801EFDA0
    if (ctx->r1 == 0) {
        // 0x801EFD8C: addiu       $t9, $v0, 0x1
        ctx->r25 = ADD32(ctx->r2, 0X1);
            goto L_801EFDA0;
    }
    // 0x801EFD8C: addiu       $t9, $v0, 0x1
    ctx->r25 = ADD32(ctx->r2, 0X1);
    // 0x801EFD90: sw          $t9, 0x2D8($s2)
    MEM_W(0X2D8, ctx->r18) = ctx->r25;
    // 0x801EFD94: b           L_801EFDA0
    // 0x801EFD98: or          $v0, $t9, $zero
    ctx->r2 = ctx->r25 | 0;
        goto L_801EFDA0;
    // 0x801EFD98: or          $v0, $t9, $zero
    ctx->r2 = ctx->r25 | 0;
L_801EFD9C:
    // 0x801EFD9C: sw          $zero, 0x2D8($s2)
    MEM_W(0X2D8, ctx->r18) = 0;
L_801EFDA0:
    // 0x801EFDA0: slti        $at, $v0, 0x8
    ctx->r1 = SIGNED(ctx->r2) < 0X8 ? 1 : 0;
    // 0x801EFDA4: beql        $at, $zero, L_801EFDC0
    if (ctx->r1 == 0) {
        // 0x801EFDA8: lw          $t1, 0x2E0($s2)
        ctx->r9 = MEM_W(ctx->r18, 0X2E0);
            goto L_801EFDC0;
    }
    goto skip_17;
    // 0x801EFDA8: lw          $t1, 0x2E0($s2)
    ctx->r9 = MEM_W(ctx->r18, 0X2E0);
    skip_17:
    // 0x801EFDAC: lw          $v0, 0x2E0($s2)
    ctx->r2 = MEM_W(ctx->r18, 0X2E0);
    // 0x801EFDB0: slti        $at, $v0, 0x2
    ctx->r1 = SIGNED(ctx->r2) < 0X2 ? 1 : 0;
    // 0x801EFDB4: bne         $at, $zero, L_801EFDF8
    if (ctx->r1 != 0) {
        // 0x801EFDB8: nop
    
            goto L_801EFDF8;
    }
    // 0x801EFDB8: nop

    // 0x801EFDBC: lw          $t1, 0x2E0($s2)
    ctx->r9 = MEM_W(ctx->r18, 0X2E0);
L_801EFDC0:
    // 0x801EFDC0: bnel        $t1, $zero, L_801EFDD0
    if (ctx->r9 != 0) {
        // 0x801EFDC4: lw          $v0, 0x2DC($s2)
        ctx->r2 = MEM_W(ctx->r18, 0X2DC);
            goto L_801EFDD0;
    }
    goto skip_18;
    // 0x801EFDC4: lw          $v0, 0x2DC($s2)
    ctx->r2 = MEM_W(ctx->r18, 0X2DC);
    skip_18:
    // 0x801EFDC8: sw          $s6, 0x2E0($s2)
    MEM_W(0X2E0, ctx->r18) = ctx->r22;
    // 0x801EFDCC: lw          $v0, 0x2DC($s2)
    ctx->r2 = MEM_W(ctx->r18, 0X2DC);
L_801EFDD0:
    // 0x801EFDD0: slti        $at, $v0, 0x4
    ctx->r1 = SIGNED(ctx->r2) < 0X4 ? 1 : 0;
    // 0x801EFDD4: beq         $at, $zero, L_801EFDE0
    if (ctx->r1 == 0) {
        // 0x801EFDD8: addiu       $t0, $v0, 0x1
        ctx->r8 = ADD32(ctx->r2, 0X1);
            goto L_801EFDE0;
    }
    // 0x801EFDD8: addiu       $t0, $v0, 0x1
    ctx->r8 = ADD32(ctx->r2, 0X1);
    // 0x801EFDDC: sw          $t0, 0x2DC($s2)
    MEM_W(0X2DC, ctx->r18) = ctx->r8;
L_801EFDE0:
    // 0x801EFDE0: lw          $v0, 0x2E0($s2)
    ctx->r2 = MEM_W(ctx->r18, 0X2E0);
    // 0x801EFDE4: slti        $at, $v0, 0x2
    ctx->r1 = SIGNED(ctx->r2) < 0X2 ? 1 : 0;
    // 0x801EFDE8: bne         $at, $zero, L_801EFE18
    if (ctx->r1 != 0) {
        // 0x801EFDEC: addiu       $t2, $v0, -0x1
        ctx->r10 = ADD32(ctx->r2, -0X1);
            goto L_801EFE18;
    }
    // 0x801EFDEC: addiu       $t2, $v0, -0x1
    ctx->r10 = ADD32(ctx->r2, -0X1);
    // 0x801EFDF0: b           L_801EFE18
    // 0x801EFDF4: sw          $t2, 0x2E0($s2)
    MEM_W(0X2E0, ctx->r18) = ctx->r10;
        goto L_801EFE18;
    // 0x801EFDF4: sw          $t2, 0x2E0($s2)
    MEM_W(0X2E0, ctx->r18) = ctx->r10;
L_801EFDF8:
    // 0x801EFDF8: bne         $v0, $zero, L_801EFE14
    if (ctx->r2 != 0) {
        // 0x801EFDFC: addiu       $t4, $v0, -0x1
        ctx->r12 = ADD32(ctx->r2, -0X1);
            goto L_801EFE14;
    }
    // 0x801EFDFC: addiu       $t4, $v0, -0x1
    ctx->r12 = ADD32(ctx->r2, -0X1);
    // 0x801EFE00: lw          $v0, 0x2DC($s2)
    ctx->r2 = MEM_W(ctx->r18, 0X2DC);
    // 0x801EFE04: blez        $v0, L_801EFE18
    if (SIGNED(ctx->r2) <= 0) {
        // 0x801EFE08: addiu       $t3, $v0, -0x1
        ctx->r11 = ADD32(ctx->r2, -0X1);
            goto L_801EFE18;
    }
    // 0x801EFE08: addiu       $t3, $v0, -0x1
    ctx->r11 = ADD32(ctx->r2, -0X1);
    // 0x801EFE0C: b           L_801EFE18
    // 0x801EFE10: sw          $t3, 0x2DC($s2)
    MEM_W(0X2DC, ctx->r18) = ctx->r11;
        goto L_801EFE18;
    // 0x801EFE10: sw          $t3, 0x2DC($s2)
    MEM_W(0X2DC, ctx->r18) = ctx->r11;
L_801EFE14:
    // 0x801EFE14: sw          $t4, 0x2E0($s2)
    MEM_W(0X2E0, ctx->r18) = ctx->r12;
L_801EFE18:
    // 0x801EFE18: lwc1        $f26, 0x6C($s5)
    ctx->f26.u32l = MEM_W(ctx->r21, 0X6C);
    // 0x801EFE1C: lwc1        $f28, 0x74($s5)
    ctx->f28.u32l = MEM_W(ctx->r21, 0X74);
    // 0x801EFE20: mul.s       $f6, $f26, $f26
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 26);
    NAN_CHECK(ctx->f26.fl); NAN_CHECK(ctx->f26.fl); 
    ctx->f6.fl = MUL_S(ctx->f26.fl, ctx->f26.fl);
    // 0x801EFE24: nop

    // 0x801EFE28: mul.s       $f8, $f28, $f28
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 28);
    CHECK_FR(ctx, 28);
    NAN_CHECK(ctx->f28.fl); NAN_CHECK(ctx->f28.fl); 
    ctx->f8.fl = MUL_S(ctx->f28.fl, ctx->f28.fl);
    // 0x801EFE2C: jal         0x800C7010
    // 0x801EFE30: add.s       $f12, $f6, $f8
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f12.fl = ctx->f6.fl + ctx->f8.fl;
    _nsqrtf(rdram, ctx);
        goto after_9;
    // 0x801EFE30: add.s       $f12, $f6, $f8
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f12.fl = ctx->f6.fl + ctx->f8.fl;
    after_9:
    // 0x801EFE34: mtc1        $zero, $f4
    ctx->f4.u32l = 0;
    // 0x801EFE38: nop

    // 0x801EFE3C: c.lt.s      $f4, $f0
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    c1cs = ctx->f4.fl < ctx->f0.fl;
    // 0x801EFE40: nop

    // 0x801EFE44: bc1fl       L_801EFE58
    if (!c1cs) {
        // 0x801EFE48: lwc1        $f16, 0x0($s3)
        ctx->f16.u32l = MEM_W(ctx->r19, 0X0);
            goto L_801EFE58;
    }
    goto skip_19;
    // 0x801EFE48: lwc1        $f16, 0x0($s3)
    ctx->f16.u32l = MEM_W(ctx->r19, 0X0);
    skip_19:
    // 0x801EFE4C: div.s       $f26, $f26, $f0
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f26.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f26.fl = DIV_S(ctx->f26.fl, ctx->f0.fl);
    // 0x801EFE50: div.s       $f28, $f28, $f0
    CHECK_FR(ctx, 28);
    CHECK_FR(ctx, 28);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f28.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f28.fl = DIV_S(ctx->f28.fl, ctx->f0.fl);
    // 0x801EFE54: lwc1        $f16, 0x0($s3)
    ctx->f16.u32l = MEM_W(ctx->r19, 0X0);
L_801EFE58:
    // 0x801EFE58: lwc1        $f10, 0x44($s5)
    ctx->f10.u32l = MEM_W(ctx->r21, 0X44);
    // 0x801EFE5C: lwc1        $f18, 0x8($s3)
    ctx->f18.u32l = MEM_W(ctx->r19, 0X8);
    // 0x801EFE60: lwc1        $f6, 0x4C($s5)
    ctx->f6.u32l = MEM_W(ctx->r21, 0X4C);
    // 0x801EFE64: sub.s       $f20, $f16, $f10
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f20.fl = ctx->f16.fl - ctx->f10.fl;
    // 0x801EFE68: sub.s       $f22, $f18, $f6
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f22.fl = ctx->f18.fl - ctx->f6.fl;
    // 0x801EFE6C: mul.s       $f8, $f20, $f20
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f8.fl = MUL_S(ctx->f20.fl, ctx->f20.fl);
    // 0x801EFE70: nop

    // 0x801EFE74: mul.s       $f4, $f22, $f22
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f4.fl = MUL_S(ctx->f22.fl, ctx->f22.fl);
    // 0x801EFE78: jal         0x800C7010
    // 0x801EFE7C: add.s       $f12, $f8, $f4
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f12.fl = ctx->f8.fl + ctx->f4.fl;
    _nsqrtf(rdram, ctx);
        goto after_10;
    // 0x801EFE7C: add.s       $f12, $f8, $f4
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f12.fl = ctx->f8.fl + ctx->f4.fl;
    after_10:
    // 0x801EFE80: mtc1        $zero, $f16
    ctx->f16.u32l = 0;
    // 0x801EFE84: nop

    // 0x801EFE88: c.lt.s      $f16, $f0
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 0);
    c1cs = ctx->f16.fl < ctx->f0.fl;
    // 0x801EFE8C: nop

    // 0x801EFE90: bc1f        L_801EFEA0
    if (!c1cs) {
        // 0x801EFE94: nop
    
            goto L_801EFEA0;
    }
    // 0x801EFE94: nop

    // 0x801EFE98: div.s       $f20, $f20, $f0
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f20.fl = DIV_S(ctx->f20.fl, ctx->f0.fl);
    // 0x801EFE9C: div.s       $f22, $f22, $f0
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f22.fl = DIV_S(ctx->f22.fl, ctx->f0.fl);
L_801EFEA0:
    // 0x801EFEA0: mul.s       $f10, $f26, $f20
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f26.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f10.fl = MUL_S(ctx->f26.fl, ctx->f20.fl);
    // 0x801EFEA4: nop

    // 0x801EFEA8: mul.s       $f18, $f28, $f22
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 28);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f28.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f18.fl = MUL_S(ctx->f28.fl, ctx->f22.fl);
    // 0x801EFEAC: jal         0x801ED090
    // 0x801EFEB0: add.s       $f12, $f10, $f18
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f12.fl = ctx->f10.fl + ctx->f18.fl;
    func_801ED090(rdram, ctx);
        goto after_11;
    // 0x801EFEB0: add.s       $f12, $f10, $f18
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f12.fl = ctx->f10.fl + ctx->f18.fl;
    after_11:
    // 0x801EFEB4: lui         $at, 0x42C8
    ctx->r1 = S32(0X42C8 << 16);
    // 0x801EFEB8: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x801EFEBC: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x801EFEC0: c.le.s      $f6, $f0
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 0);
    c1cs = ctx->f6.fl <= ctx->f0.fl;
    // 0x801EFEC4: nop

    // 0x801EFEC8: bc1fl       L_801EFF3C
    if (!c1cs) {
        // 0x801EFECC: sw          $zero, 0x328($s2)
        MEM_W(0X328, ctx->r18) = 0;
            goto L_801EFF3C;
    }
    goto skip_20;
    // 0x801EFECC: sw          $zero, 0x328($s2)
    MEM_W(0X328, ctx->r18) = 0;
    skip_20:
    // 0x801EFED0: lwc1        $f8, 0xB90($s5)
    ctx->f8.u32l = MEM_W(ctx->r21, 0XB90);
    // 0x801EFED4: lwc1        $f4, 0x7A40($at)
    ctx->f4.u32l = MEM_W(ctx->r1, 0X7A40);
    // 0x801EFED8: lui         $at, 0x4120
    ctx->r1 = S32(0X4120 << 16);
    // 0x801EFEDC: mtc1        $at, $f10
    ctx->f10.u32l = ctx->r1;
    // 0x801EFEE0: mul.s       $f16, $f8, $f4
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f16.fl = MUL_S(ctx->f8.fl, ctx->f4.fl);
    // 0x801EFEE4: c.le.s      $f10, $f16
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    c1cs = ctx->f10.fl <= ctx->f16.fl;
    // 0x801EFEE8: nop

    // 0x801EFEEC: bc1fl       L_801EFF3C
    if (!c1cs) {
        // 0x801EFEF0: sw          $zero, 0x328($s2)
        MEM_W(0X328, ctx->r18) = 0;
            goto L_801EFF3C;
    }
    goto skip_21;
    // 0x801EFEF0: sw          $zero, 0x328($s2)
    MEM_W(0X328, ctx->r18) = 0;
    skip_21:
    // 0x801EFEF4: lwc1        $f12, 0x44($s5)
    ctx->f12.u32l = MEM_W(ctx->r21, 0X44);
    // 0x801EFEF8: jal         0x80074448
    // 0x801EFEFC: lwc1        $f14, 0x4C($s5)
    ctx->f14.u32l = MEM_W(ctx->r21, 0X4C);
    func_80074448(rdram, ctx);
        goto after_12;
    // 0x801EFEFC: lwc1        $f14, 0x4C($s5)
    ctx->f14.u32l = MEM_W(ctx->r21, 0X4C);
    after_12:
    // 0x801EFF00: bne         $v0, $zero, L_801EFF38
    if (ctx->r2 != 0) {
        // 0x801EFF04: lui         $t5, 0x800E
        ctx->r13 = S32(0X800E << 16);
            goto L_801EFF38;
    }
    // 0x801EFF04: lui         $t5, 0x800E
    ctx->r13 = S32(0X800E << 16);
    // 0x801EFF08: lw          $t5, -0x7E90($t5)
    ctx->r13 = MEM_W(ctx->r13, -0X7E90);
    // 0x801EFF0C: beql        $t5, $zero, L_801EFF3C
    if (ctx->r13 == 0) {
        // 0x801EFF10: sw          $zero, 0x328($s2)
        MEM_W(0X328, ctx->r18) = 0;
            goto L_801EFF3C;
    }
    goto skip_22;
    // 0x801EFF10: sw          $zero, 0x328($s2)
    MEM_W(0X328, ctx->r18) = 0;
    skip_22:
    // 0x801EFF14: lw          $v0, 0x328($s2)
    ctx->r2 = MEM_W(ctx->r18, 0X328);
    // 0x801EFF18: lui         $at, 0x7FFF
    ctx->r1 = S32(0X7FFF << 16);
    // 0x801EFF1C: ori         $at, $at, 0xFFFF
    ctx->r1 = ctx->r1 | 0XFFFF;
    // 0x801EFF20: slt         $at, $v0, $at
    ctx->r1 = SIGNED(ctx->r2) < SIGNED(ctx->r1) ? 1 : 0;
    // 0x801EFF24: beq         $at, $zero, L_801EFF40
    if (ctx->r1 == 0) {
        // 0x801EFF28: addiu       $t8, $v0, 0x1
        ctx->r24 = ADD32(ctx->r2, 0X1);
            goto L_801EFF40;
    }
    // 0x801EFF28: addiu       $t8, $v0, 0x1
    ctx->r24 = ADD32(ctx->r2, 0X1);
    // 0x801EFF2C: sw          $t8, 0x328($s2)
    MEM_W(0X328, ctx->r18) = ctx->r24;
    // 0x801EFF30: b           L_801EFF40
    // 0x801EFF34: or          $v0, $t8, $zero
    ctx->r2 = ctx->r24 | 0;
        goto L_801EFF40;
    // 0x801EFF34: or          $v0, $t8, $zero
    ctx->r2 = ctx->r24 | 0;
L_801EFF38:
    // 0x801EFF38: sw          $zero, 0x328($s2)
    MEM_W(0X328, ctx->r18) = 0;
L_801EFF3C:
    // 0x801EFF3C: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_801EFF40:
    // 0x801EFF40: slti        $at, $v0, 0x28
    ctx->r1 = SIGNED(ctx->r2) < 0X28 ? 1 : 0;
    // 0x801EFF44: bne         $at, $zero, L_801EFF7C
    if (ctx->r1 != 0) {
        // 0x801EFF48: addiu       $at, $zero, 0x14
        ctx->r1 = ADD32(0, 0X14);
            goto L_801EFF7C;
    }
    // 0x801EFF48: addiu       $at, $zero, 0x14
    ctx->r1 = ADD32(0, 0X14);
    // 0x801EFF4C: div         $zero, $v0, $at
    lo = S32(S64(S32(ctx->r2)) / S64(S32(ctx->r1))); hi = S32(S64(S32(ctx->r2)) % S64(S32(ctx->r1)));
    // 0x801EFF50: mfhi        $t6
    ctx->r14 = hi;
    // 0x801EFF54: lui         $t7, 0x801D
    ctx->r15 = S32(0X801D << 16);
    // 0x801EFF58: bne         $t6, $zero, L_801EFF7C
    if (ctx->r14 != 0) {
        // 0x801EFF5C: nop
    
            goto L_801EFF7C;
    }
    // 0x801EFF5C: nop

    // 0x801EFF60: lw          $t7, -0x19B0($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X19B0);
    // 0x801EFF64: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x801EFF68: addiu       $a0, $zero, 0x35
    ctx->r4 = ADD32(0, 0X35);
    // 0x801EFF6C: bne         $t7, $at, L_801EFF7C
    if (ctx->r15 != ctx->r1) {
        // 0x801EFF70: nop
    
            goto L_801EFF7C;
    }
    // 0x801EFF70: nop

    // 0x801EFF74: jal         0x800C37F4
    // 0x801EFF78: or          $a1, $s7, $zero
    ctx->r5 = ctx->r23 | 0;
    func_800C37F4(rdram, ctx);
        goto after_13;
    // 0x801EFF78: or          $a1, $s7, $zero
    ctx->r5 = ctx->r23 | 0;
    after_13:
L_801EFF7C:
    // 0x801EFF7C: lui         $t9, 0x800E
    ctx->r25 = S32(0X800E << 16);
    // 0x801EFF80: lw          $t9, -0x54D8($t9)
    ctx->r25 = MEM_W(ctx->r25, -0X54D8);
    // 0x801EFF84: addiu       $s7, $s7, 0x1
    ctx->r23 = ADD32(ctx->r23, 0X1);
    // 0x801EFF88: slt         $at, $s7, $t9
    ctx->r1 = SIGNED(ctx->r23) < SIGNED(ctx->r25) ? 1 : 0;
    // 0x801EFF8C: bne         $at, $zero, L_801EF558
    if (ctx->r1 != 0) {
        // 0x801EFF90: nop
    
            goto L_801EF558;
    }
    // 0x801EFF90: nop

L_801EFF94:
    // 0x801EFF94: lw          $ra, 0x64($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X64);
    // 0x801EFF98: ldc1        $f20, 0x10($sp)
    CHECK_FR(ctx, 20);
    ctx->f20.u64 = LD(ctx->r29, 0X10);
    // 0x801EFF9C: ldc1        $f22, 0x18($sp)
    CHECK_FR(ctx, 22);
    ctx->f22.u64 = LD(ctx->r29, 0X18);
    // 0x801EFFA0: ldc1        $f24, 0x20($sp)
    CHECK_FR(ctx, 24);
    ctx->f24.u64 = LD(ctx->r29, 0X20);
    // 0x801EFFA4: ldc1        $f26, 0x28($sp)
    CHECK_FR(ctx, 26);
    ctx->f26.u64 = LD(ctx->r29, 0X28);
    // 0x801EFFA8: ldc1        $f28, 0x30($sp)
    CHECK_FR(ctx, 28);
    ctx->f28.u64 = LD(ctx->r29, 0X30);
    // 0x801EFFAC: ldc1        $f30, 0x38($sp)
    CHECK_FR(ctx, 30);
    ctx->f30.u64 = LD(ctx->r29, 0X38);
    // 0x801EFFB0: lw          $s0, 0x44($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X44);
    // 0x801EFFB4: lw          $s1, 0x48($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X48);
    // 0x801EFFB8: lw          $s2, 0x4C($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X4C);
    // 0x801EFFBC: lw          $s3, 0x50($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X50);
    // 0x801EFFC0: lw          $s4, 0x54($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X54);
    // 0x801EFFC4: lw          $s5, 0x58($sp)
    ctx->r21 = MEM_W(ctx->r29, 0X58);
    // 0x801EFFC8: lw          $s6, 0x5C($sp)
    ctx->r22 = MEM_W(ctx->r29, 0X5C);
    // 0x801EFFCC: lw          $s7, 0x60($sp)
    ctx->r23 = MEM_W(ctx->r29, 0X60);
    // 0x801EFFD0: jr          $ra
    // 0x801EFFD4: addiu       $sp, $sp, 0xB8
    ctx->r29 = ADD32(ctx->r29, 0XB8);
    return;
    // 0x801EFFD4: addiu       $sp, $sp, 0xB8
    ctx->r29 = ADD32(ctx->r29, 0XB8);
;}
RECOMP_FUNC void func_801EFFD8(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801EFFD8: addiu       $sp, $sp, -0x58
    ctx->r29 = ADD32(ctx->r29, -0X58);
    // 0x801EFFDC: sw          $ra, 0x54($sp)
    MEM_W(0X54, ctx->r29) = ctx->r31;
    // 0x801EFFE0: sw          $fp, 0x50($sp)
    MEM_W(0X50, ctx->r29) = ctx->r30;
    // 0x801EFFE4: sw          $s7, 0x4C($sp)
    MEM_W(0X4C, ctx->r29) = ctx->r23;
    // 0x801EFFE8: sw          $s6, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r22;
    // 0x801EFFEC: sw          $s5, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r21;
    // 0x801EFFF0: sw          $s4, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r20;
    // 0x801EFFF4: sw          $s3, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r19;
    // 0x801EFFF8: sw          $s2, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r18;
    // 0x801EFFFC: sw          $s1, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r17;
    // 0x801F0000: sw          $s0, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r16;
    // 0x801F0004: sdc1        $f22, 0x28($sp)
    CHECK_FR(ctx, 22);
    SD(ctx->f22.u64, 0X28, ctx->r29);
    // 0x801F0008: sdc1        $f20, 0x20($sp)
    CHECK_FR(ctx, 20);
    SD(ctx->f20.u64, 0X20, ctx->r29);
    // 0x801F000C: sw          $a0, 0x58($sp)
    MEM_W(0X58, ctx->r29) = ctx->r4;
    // 0x801F0010: lw          $s0, 0x0($a0)
    ctx->r16 = MEM_W(ctx->r4, 0X0);
    // 0x801F0014: lui         $t8, 0x101
    ctx->r24 = S32(0X101 << 16);
    // 0x801F0018: addiu       $t8, $t8, 0x4618
    ctx->r24 = ADD32(ctx->r24, 0X4618);
    // 0x801F001C: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
    // 0x801F0020: lui         $t7, 0x600
    ctx->r15 = S32(0X600 << 16);
    // 0x801F0024: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801F0028: sw          $t7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r15;
    // 0x801F002C: sw          $t8, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r24;
    // 0x801F0030: or          $v1, $s0, $zero
    ctx->r3 = ctx->r16 | 0;
    // 0x801F0034: lui         $t9, 0xB400
    ctx->r25 = S32(0XB400 << 16);
    // 0x801F0038: sw          $t9, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r25;
    // 0x801F003C: lui         $t3, 0x8023
    ctx->r11 = S32(0X8023 << 16);
    // 0x801F0040: lhu         $t3, -0x72DC($t3)
    ctx->r11 = MEM_HU(ctx->r11, -0X72DC);
    // 0x801F0044: lui         $a1, 0x800E
    ctx->r5 = S32(0X800E << 16);
    // 0x801F0048: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801F004C: sw          $t3, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r11;
    // 0x801F0050: lw          $a1, -0x54D8($a1)
    ctx->r5 = MEM_W(ctx->r5, -0X54D8);
    // 0x801F0054: or          $s2, $zero, $zero
    ctx->r18 = 0 | 0;
    // 0x801F0058: lui         $fp, 0xE700
    ctx->r30 = S32(0XE700 << 16);
    // 0x801F005C: blez        $a1, L_801F0304
    if (SIGNED(ctx->r5) <= 0) {
        // 0x801F0060: lui         $at, 0x3F80
        ctx->r1 = S32(0X3F80 << 16);
            goto L_801F0304;
    }
    // 0x801F0060: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x801F0064: lui         $s6, 0x801C
    ctx->r22 = S32(0X801C << 16);
    // 0x801F0068: lui         $s4, 0x380
    ctx->r20 = S32(0X380 << 16);
    // 0x801F006C: lui         $s3, 0x801B
    ctx->r19 = S32(0X801B << 16);
    // 0x801F0070: lui         $t1, 0xFCFF
    ctx->r9 = S32(0XFCFF << 16);
    // 0x801F0074: mtc1        $at, $f22
    ctx->f22.u32l = ctx->r1;
    // 0x801F0078: mtc1        $zero, $f20
    ctx->f20.u32l = 0;
    // 0x801F007C: ori         $t1, $t1, 0xFFFF
    ctx->r9 = ctx->r9 | 0XFFFF;
    // 0x801F0080: addiu       $s3, $s3, -0x16B0
    ctx->r19 = ADD32(ctx->r19, -0X16B0);
    // 0x801F0084: ori         $s4, $s4, 0x10
    ctx->r20 = ctx->r20 | 0X10;
    // 0x801F0088: addiu       $s6, $s6, 0x2938
    ctx->r22 = ADD32(ctx->r22, 0X2938);
    // 0x801F008C: addiu       $s7, $zero, 0x378
    ctx->r23 = ADD32(0, 0X378);
L_801F0090:
    // 0x801F0090: bne         $s2, $zero, L_801F00B4
    if (ctx->r18 != 0) {
        // 0x801F0094: lui         $t6, 0x800D
        ctx->r14 = S32(0X800D << 16);
            goto L_801F00B4;
    }
    // 0x801F0094: lui         $t6, 0x800D
    ctx->r14 = S32(0X800D << 16);
    // 0x801F0098: lui         $t4, 0x800D
    ctx->r12 = S32(0X800D << 16);
    // 0x801F009C: lw          $t4, 0x48DC($t4)
    ctx->r12 = MEM_W(ctx->r12, 0X48DC);
    // 0x801F00A0: multu       $t4, $s7
    result = U64(U32(ctx->r12)) * U64(U32(ctx->r23)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x801F00A4: mflo        $t5
    ctx->r13 = lo;
    // 0x801F00A8: addu        $t0, $s6, $t5
    ctx->r8 = ADD32(ctx->r22, ctx->r13);
    // 0x801F00AC: b           L_801F00CC
    // 0x801F00B0: lw          $s1, 0x2DC($t0)
    ctx->r17 = MEM_W(ctx->r8, 0X2DC);
        goto L_801F00CC;
    // 0x801F00B0: lw          $s1, 0x2DC($t0)
    ctx->r17 = MEM_W(ctx->r8, 0X2DC);
L_801F00B4:
    // 0x801F00B4: lw          $t6, 0x48E0($t6)
    ctx->r14 = MEM_W(ctx->r14, 0X48E0);
    // 0x801F00B8: multu       $t6, $s7
    result = U64(U32(ctx->r14)) * U64(U32(ctx->r23)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x801F00BC: mflo        $t7
    ctx->r15 = lo;
    // 0x801F00C0: addu        $t0, $s6, $t7
    ctx->r8 = ADD32(ctx->r22, ctx->r15);
    // 0x801F00C4: nop

    // 0x801F00C8: lw          $s1, 0x2DC($t0)
    ctx->r17 = MEM_W(ctx->r8, 0X2DC);
L_801F00CC:
    // 0x801F00CC: sll         $t8, $s1, 8
    ctx->r24 = S32(ctx->r17 << 8);
    // 0x801F00D0: subu        $t8, $t8, $s1
    ctx->r24 = SUB32(ctx->r24, ctx->r17);
    // 0x801F00D4: or          $s1, $t8, $zero
    ctx->r17 = ctx->r24 | 0;
    // 0x801F00D8: bgez        $s1, L_801F00E8
    if (SIGNED(ctx->r17) >= 0) {
        // 0x801F00DC: sra         $t9, $s1, 2
        ctx->r25 = S32(SIGNED(ctx->r17) >> 2);
            goto L_801F00E8;
    }
    // 0x801F00DC: sra         $t9, $s1, 2
    ctx->r25 = S32(SIGNED(ctx->r17) >> 2);
    // 0x801F00E0: addiu       $at, $s1, 0x3
    ctx->r1 = ADD32(ctx->r17, 0X3);
    // 0x801F00E4: sra         $t9, $at, 2
    ctx->r25 = S32(SIGNED(ctx->r1) >> 2);
L_801F00E8:
    // 0x801F00E8: blez        $t9, L_801F02F4
    if (SIGNED(ctx->r25) <= 0) {
        // 0x801F00EC: or          $s1, $t9, $zero
        ctx->r17 = ctx->r25 | 0;
            goto L_801F02F4;
    }
    // 0x801F00EC: or          $s1, $t9, $zero
    ctx->r17 = ctx->r25 | 0;
    // 0x801F00F0: lw          $t3, 0x2F4($t0)
    ctx->r11 = MEM_W(ctx->r8, 0X2F4);
    // 0x801F00F4: bnel        $t3, $zero, L_801F02F8
    if (ctx->r11 != 0) {
        // 0x801F00F8: addiu       $s2, $s2, 0x1
        ctx->r18 = ADD32(ctx->r18, 0X1);
            goto L_801F02F8;
    }
    goto skip_0;
    // 0x801F00F8: addiu       $s2, $s2, 0x1
    ctx->r18 = ADD32(ctx->r18, 0X1);
    skip_0:
    // 0x801F00FC: lw          $t4, 0x2EC($t0)
    ctx->r12 = MEM_W(ctx->r8, 0X2EC);
    // 0x801F0100: lui         $s5, 0x101
    ctx->r21 = S32(0X101 << 16);
    // 0x801F0104: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x801F0108: bnel        $t4, $zero, L_801F02F8
    if (ctx->r12 != 0) {
        // 0x801F010C: addiu       $s2, $s2, 0x1
        ctx->r18 = ADD32(ctx->r18, 0X1);
            goto L_801F02F8;
    }
    goto skip_1;
    // 0x801F010C: addiu       $s2, $s2, 0x1
    ctx->r18 = ADD32(ctx->r18, 0X1);
    skip_1:
    // 0x801F0110: bne         $a1, $at, L_801F0134
    if (ctx->r5 != ctx->r1) {
        // 0x801F0114: addiu       $s5, $s5, 0x528
        ctx->r21 = ADD32(ctx->r21, 0X528);
            goto L_801F0134;
    }
    // 0x801F0114: addiu       $s5, $s5, 0x528
    ctx->r21 = ADD32(ctx->r21, 0X528);
    // 0x801F0118: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
    // 0x801F011C: lui         $t5, 0x101
    ctx->r13 = S32(0X101 << 16);
    // 0x801F0120: addiu       $t5, $t5, 0x4460
    ctx->r13 = ADD32(ctx->r13, 0X4460);
    // 0x801F0124: sw          $t5, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r13;
    // 0x801F0128: sw          $s4, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r20;
    // 0x801F012C: b           L_801F016C
    // 0x801F0130: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
        goto L_801F016C;
    // 0x801F0130: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
L_801F0134:
    // 0x801F0134: bne         $s2, $zero, L_801F0158
    if (ctx->r18 != 0) {
        // 0x801F0138: or          $v0, $s0, $zero
        ctx->r2 = ctx->r16 | 0;
            goto L_801F0158;
    }
    // 0x801F0138: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
    // 0x801F013C: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
    // 0x801F0140: lui         $t6, 0x101
    ctx->r14 = S32(0X101 << 16);
    // 0x801F0144: addiu       $t6, $t6, 0x4470
    ctx->r14 = ADD32(ctx->r14, 0X4470);
    // 0x801F0148: sw          $t6, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r14;
    // 0x801F014C: sw          $s4, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r20;
    // 0x801F0150: b           L_801F016C
    // 0x801F0154: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
        goto L_801F016C;
    // 0x801F0154: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
L_801F0158:
    // 0x801F0158: lui         $t7, 0x101
    ctx->r15 = S32(0X101 << 16);
    // 0x801F015C: addiu       $t7, $t7, 0x4480
    ctx->r15 = ADD32(ctx->r15, 0X4480);
    // 0x801F0160: sw          $t7, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r15;
    // 0x801F0164: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801F0168: sw          $s4, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r20;
L_801F016C:
    // 0x801F016C: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
    // 0x801F0170: sw          $fp, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r30;
    // 0x801F0174: sw          $zero, 0x4($v0)
    MEM_W(0X4, ctx->r2) = 0;
    // 0x801F0178: lw          $v1, 0x328($t0)
    ctx->r3 = MEM_W(ctx->r8, 0X328);
    // 0x801F017C: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801F0180: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
    // 0x801F0184: slti        $at, $v1, 0x28
    ctx->r1 = SIGNED(ctx->r3) < 0X28 ? 1 : 0;
    // 0x801F0188: bne         $at, $zero, L_801F01BC
    if (ctx->r1 != 0) {
        // 0x801F018C: lui         $t3, 0xFFFE
        ctx->r11 = S32(0XFFFE << 16);
            goto L_801F01BC;
    }
    // 0x801F018C: lui         $t3, 0xFFFE
    ctx->r11 = S32(0XFFFE << 16);
    // 0x801F0190: addiu       $at, $zero, 0x14
    ctx->r1 = ADD32(0, 0X14);
    // 0x801F0194: div         $zero, $v1, $at
    lo = S32(S64(S32(ctx->r3)) / S64(S32(ctx->r1))); hi = S32(S64(S32(ctx->r3)) % S64(S32(ctx->r1)));
    // 0x801F0198: mfhi        $t8
    ctx->r24 = hi;
    // 0x801F019C: lui         $t9, 0xFFFD
    ctx->r25 = S32(0XFFFD << 16);
    // 0x801F01A0: bne         $t8, $zero, L_801F01BC
    if (ctx->r24 != 0) {
        // 0x801F01A4: ori         $t9, $t9, 0xF6FB
        ctx->r25 = ctx->r25 | 0XF6FB;
            goto L_801F01BC;
    }
    // 0x801F01A4: ori         $t9, $t9, 0xF6FB
    ctx->r25 = ctx->r25 | 0XF6FB;
    // 0x801F01A8: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
    // 0x801F01AC: sw          $t1, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r9;
    // 0x801F01B0: sw          $t9, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r25;
    // 0x801F01B4: b           L_801F01CC
    // 0x801F01B8: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
        goto L_801F01CC;
    // 0x801F01B8: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
L_801F01BC:
    // 0x801F01BC: ori         $t3, $t3, 0x773B
    ctx->r11 = ctx->r11 | 0X773B;
    // 0x801F01C0: sw          $t3, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r11;
    // 0x801F01C4: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801F01C8: sw          $t1, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r9;
L_801F01CC:
    // 0x801F01CC: lw          $t7, 0x2D0($t0)
    ctx->r15 = MEM_W(ctx->r8, 0X2D0);
    // 0x801F01D0: lw          $t5, 0x0($s3)
    ctx->r13 = MEM_W(ctx->r19, 0X0);
    // 0x801F01D4: lui         $t4, 0x801B
    ctx->r12 = S32(0X801B << 16);
    // 0x801F01D8: mtc1        $t7, $f4
    ctx->f4.u32l = ctx->r15;
    // 0x801F01DC: lw          $t4, -0x16B8($t4)
    ctx->r12 = MEM_W(ctx->r12, -0X16B8);
    // 0x801F01E0: sll         $t6, $t5, 6
    ctx->r14 = S32(ctx->r13 << 6);
    // 0x801F01E4: cvt.s.w     $f4, $f4
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 4);
    ctx->f4.fl = CVT_S_W(ctx->f4.u32l);
    // 0x801F01E8: mfc1        $a2, $f20
    ctx->r6 = (int32_t)ctx->f20.u32l;
    // 0x801F01EC: mfc1        $a3, $f22
    ctx->r7 = (int32_t)ctx->f22.u32l;
    // 0x801F01F0: addu        $a0, $t4, $t6
    ctx->r4 = ADD32(ctx->r12, ctx->r14);
    // 0x801F01F4: addiu       $a0, $a0, 0x4140
    ctx->r4 = ADD32(ctx->r4, 0X4140);
    // 0x801F01F8: swc1        $f20, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f20.u32l;
    // 0x801F01FC: mfc1        $a1, $f4
    ctx->r5 = (int32_t)ctx->f4.u32l;
    // 0x801F0200: jal         0x801EE228
    // 0x801F0204: nop

    func_801EE228(rdram, ctx);
        goto after_0;
    // 0x801F0204: nop

    after_0:
    // 0x801F0208: lui         $t8, 0x104
    ctx->r24 = S32(0X104 << 16);
    // 0x801F020C: ori         $t8, $t8, 0x40
    ctx->r24 = ctx->r24 | 0X40;
    // 0x801F0210: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
    // 0x801F0214: sw          $t8, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r24;
    // 0x801F0218: lw          $t9, 0x0($s3)
    ctx->r25 = MEM_W(ctx->r19, 0X0);
    // 0x801F021C: lui         $t4, 0x500
    ctx->r12 = S32(0X500 << 16);
    // 0x801F0220: addiu       $t4, $t4, 0x0
    ctx->r12 = ADD32(ctx->r12, 0X0);
    // 0x801F0224: sll         $t3, $t9, 6
    ctx->r11 = S32(ctx->r25 << 6);
    // 0x801F0228: addiu       $t5, $t3, 0x4140
    ctx->r13 = ADD32(ctx->r11, 0X4140);
    // 0x801F022C: addu        $t6, $t5, $t4
    ctx->r14 = ADD32(ctx->r13, ctx->r12);
    // 0x801F0230: sw          $t6, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r14;
    // 0x801F0234: lw          $t7, 0x0($s3)
    ctx->r15 = MEM_W(ctx->r19, 0X0);
    // 0x801F0238: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801F023C: or          $v1, $s0, $zero
    ctx->r3 = ctx->r16 | 0;
    // 0x801F0240: lui         $at, 0xFF96
    ctx->r1 = S32(0XFF96 << 16);
    // 0x801F0244: addiu       $t8, $t7, 0x1
    ctx->r24 = ADD32(ctx->r15, 0X1);
    // 0x801F0248: sw          $t8, 0x0($s3)
    MEM_W(0X0, ctx->r19) = ctx->r24;
    // 0x801F024C: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801F0250: ori         $at, $at, 0x9600
    ctx->r1 = ctx->r1 | 0X9600;
    // 0x801F0254: andi        $t3, $s1, 0xFF
    ctx->r11 = ctx->r17 & 0XFF;
    // 0x801F0258: or          $t5, $t3, $at
    ctx->r13 = ctx->r11 | ctx->r1;
    // 0x801F025C: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x801F0260: lui         $t1, 0xFCFF
    ctx->r9 = S32(0XFCFF << 16);
    // 0x801F0264: lui         $t2, 0xB900
    ctx->r10 = S32(0XB900 << 16);
    // 0x801F0268: sw          $zero, 0x4($v1)
    MEM_W(0X4, ctx->r3) = 0;
    // 0x801F026C: sw          $fp, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r30;
    // 0x801F0270: lui         $t9, 0xFA00
    ctx->r25 = S32(0XFA00 << 16);
    // 0x801F0274: slti        $at, $s1, 0xFF
    ctx->r1 = SIGNED(ctx->r17) < 0XFF ? 1 : 0;
    // 0x801F0278: ori         $t2, $t2, 0x31D
    ctx->r10 = ctx->r10 | 0X31D;
    // 0x801F027C: ori         $t1, $t1, 0xFFFF
    ctx->r9 = ctx->r9 | 0XFFFF;
    // 0x801F0280: sw          $t9, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r25;
    // 0x801F0284: sw          $t5, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r13;
    // 0x801F0288: beq         $at, $zero, L_801F02AC
    if (ctx->r1 == 0) {
        // 0x801F028C: addiu       $s0, $s0, 0x8
        ctx->r16 = ADD32(ctx->r16, 0X8);
            goto L_801F02AC;
    }
    // 0x801F028C: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801F0290: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
    // 0x801F0294: lui         $t4, 0x50
    ctx->r12 = S32(0X50 << 16);
    // 0x801F0298: ori         $t4, $t4, 0x41C8
    ctx->r12 = ctx->r12 | 0X41C8;
    // 0x801F029C: sw          $t4, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r12;
    // 0x801F02A0: sw          $t2, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r10;
    // 0x801F02A4: b           L_801F02C4
    // 0x801F02A8: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
        goto L_801F02C4;
    // 0x801F02A8: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
L_801F02AC:
    // 0x801F02AC: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
    // 0x801F02B0: lui         $t6, 0x55
    ctx->r14 = S32(0X55 << 16);
    // 0x801F02B4: ori         $t6, $t6, 0x2078
    ctx->r14 = ctx->r14 | 0X2078;
    // 0x801F02B8: sw          $t6, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r14;
    // 0x801F02BC: sw          $t2, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r10;
    // 0x801F02C0: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
L_801F02C4:
    // 0x801F02C4: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
    // 0x801F02C8: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801F02CC: lui         $t7, 0x600
    ctx->r15 = S32(0X600 << 16);
    // 0x801F02D0: sw          $t7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r15;
    // 0x801F02D4: sw          $s5, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r21;
    // 0x801F02D8: or          $v1, $s0, $zero
    ctx->r3 = ctx->r16 | 0;
    // 0x801F02DC: lui         $t8, 0xBD00
    ctx->r24 = S32(0XBD00 << 16);
    // 0x801F02E0: sw          $t8, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r24;
    // 0x801F02E4: sw          $zero, 0x4($v1)
    MEM_W(0X4, ctx->r3) = 0;
    // 0x801F02E8: lui         $a1, 0x800E
    ctx->r5 = S32(0X800E << 16);
    // 0x801F02EC: lw          $a1, -0x54D8($a1)
    ctx->r5 = MEM_W(ctx->r5, -0X54D8);
    // 0x801F02F0: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
L_801F02F4:
    // 0x801F02F4: addiu       $s2, $s2, 0x1
    ctx->r18 = ADD32(ctx->r18, 0X1);
L_801F02F8:
    // 0x801F02F8: slt         $at, $s2, $a1
    ctx->r1 = SIGNED(ctx->r18) < SIGNED(ctx->r5) ? 1 : 0;
    // 0x801F02FC: bne         $at, $zero, L_801F0090
    if (ctx->r1 != 0) {
        // 0x801F0300: nop
    
            goto L_801F0090;
    }
    // 0x801F0300: nop

L_801F0304:
    // 0x801F0304: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
    // 0x801F0308: lui         $s4, 0x380
    ctx->r20 = S32(0X380 << 16);
    // 0x801F030C: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801F0310: lui         $t9, 0x101
    ctx->r25 = S32(0X101 << 16);
    // 0x801F0314: ori         $s4, $s4, 0x10
    ctx->r20 = ctx->r20 | 0X10;
    // 0x801F0318: addiu       $t9, $t9, 0x4450
    ctx->r25 = ADD32(ctx->r25, 0X4450);
    // 0x801F031C: or          $v1, $s0, $zero
    ctx->r3 = ctx->r16 | 0;
    // 0x801F0320: sw          $t9, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r25;
    // 0x801F0324: sw          $s4, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r20;
    // 0x801F0328: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801F032C: lui         $t3, 0x103
    ctx->r11 = S32(0X103 << 16);
    // 0x801F0330: lui         $t5, 0x301
    ctx->r13 = S32(0X301 << 16);
    // 0x801F0334: addiu       $t5, $t5, -0x1FF8
    ctx->r13 = ADD32(ctx->r13, -0X1FF8);
    // 0x801F0338: ori         $t3, $t3, 0x40
    ctx->r11 = ctx->r11 | 0X40;
    // 0x801F033C: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x801F0340: sw          $t3, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r11;
    // 0x801F0344: sw          $t5, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r13;
    // 0x801F0348: lui         $t4, 0x101
    ctx->r12 = S32(0X101 << 16);
    // 0x801F034C: lui         $t6, 0x301
    ctx->r14 = S32(0X301 << 16);
    // 0x801F0350: addiu       $t6, $t6, -0x1F78
    ctx->r14 = ADD32(ctx->r14, -0X1F78);
    // 0x801F0354: ori         $t4, $t4, 0x40
    ctx->r12 = ctx->r12 | 0X40;
    // 0x801F0358: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801F035C: sw          $t4, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r12;
    // 0x801F0360: sw          $t6, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r14;
    // 0x801F0364: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    // 0x801F0368: lui         $t7, 0xB400
    ctx->r15 = S32(0XB400 << 16);
    // 0x801F036C: sw          $t7, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r15;
    // 0x801F0370: lui         $t8, 0x8022
    ctx->r24 = S32(0X8022 << 16);
    // 0x801F0374: lw          $t8, 0x3930($t8)
    ctx->r24 = MEM_W(ctx->r24, 0X3930);
    // 0x801F0378: lui         $t3, 0x8022
    ctx->r11 = S32(0X8022 << 16);
    // 0x801F037C: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x801F0380: sll         $t9, $t8, 4
    ctx->r25 = S32(ctx->r24 << 4);
    // 0x801F0384: addu        $t9, $t9, $t8
    ctx->r25 = ADD32(ctx->r25, ctx->r24);
    // 0x801F0388: sll         $t9, $t9, 2
    ctx->r25 = S32(ctx->r25 << 2);
    // 0x801F038C: subu        $t9, $t9, $t8
    ctx->r25 = SUB32(ctx->r25, ctx->r24);
    // 0x801F0390: sll         $t9, $t9, 2
    ctx->r25 = S32(ctx->r25 << 2);
    // 0x801F0394: addu        $t3, $t3, $t9
    ctx->r11 = ADD32(ctx->r11, ctx->r25);
    // 0x801F0398: lhu         $t3, 0x7D64($t3)
    ctx->r11 = MEM_HU(ctx->r11, 0X7D64);
    // 0x801F039C: sw          $t3, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r11;
    // 0x801F03A0: lw          $t5, 0x58($sp)
    ctx->r13 = MEM_W(ctx->r29, 0X58);
    // 0x801F03A4: sw          $s0, 0x0($t5)
    MEM_W(0X0, ctx->r13) = ctx->r16;
    // 0x801F03A8: lw          $ra, 0x54($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X54);
    // 0x801F03AC: lw          $fp, 0x50($sp)
    ctx->r30 = MEM_W(ctx->r29, 0X50);
    // 0x801F03B0: lw          $s7, 0x4C($sp)
    ctx->r23 = MEM_W(ctx->r29, 0X4C);
    // 0x801F03B4: lw          $s6, 0x48($sp)
    ctx->r22 = MEM_W(ctx->r29, 0X48);
    // 0x801F03B8: lw          $s5, 0x44($sp)
    ctx->r21 = MEM_W(ctx->r29, 0X44);
    // 0x801F03BC: lw          $s4, 0x40($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X40);
    // 0x801F03C0: lw          $s3, 0x3C($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X3C);
    // 0x801F03C4: lw          $s2, 0x38($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X38);
    // 0x801F03C8: lw          $s1, 0x34($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X34);
    // 0x801F03CC: lw          $s0, 0x30($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X30);
    // 0x801F03D0: ldc1        $f22, 0x28($sp)
    CHECK_FR(ctx, 22);
    ctx->f22.u64 = LD(ctx->r29, 0X28);
    // 0x801F03D4: ldc1        $f20, 0x20($sp)
    CHECK_FR(ctx, 20);
    ctx->f20.u64 = LD(ctx->r29, 0X20);
    // 0x801F03D8: jr          $ra
    // 0x801F03DC: addiu       $sp, $sp, 0x58
    ctx->r29 = ADD32(ctx->r29, 0X58);
    return;
    // 0x801F03DC: addiu       $sp, $sp, 0x58
    ctx->r29 = ADD32(ctx->r29, 0X58);
;}
RECOMP_FUNC void func_801F03E0(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801F03E0: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x801F03E4: lw          $v0, -0x19B0($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X19B0);
    // 0x801F03E8: addiu       $sp, $sp, -0x30
    ctx->r29 = ADD32(ctx->r29, -0X30);
    // 0x801F03EC: addiu       $t1, $zero, 0x1
    ctx->r9 = ADD32(0, 0X1);
    // 0x801F03F0: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x801F03F4: beq         $t1, $v0, L_801F0408
    if (ctx->r9 == ctx->r2) {
        // 0x801F03F8: sw          $s0, 0x18($sp)
        MEM_W(0X18, ctx->r29) = ctx->r16;
            goto L_801F0408;
    }
    // 0x801F03F8: sw          $s0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r16;
    // 0x801F03FC: addiu       $s0, $zero, 0x2
    ctx->r16 = ADD32(0, 0X2);
    // 0x801F0400: bne         $s0, $v0, L_801F0644
    if (ctx->r16 != ctx->r2) {
        // 0x801F0404: lui         $t6, 0x8023
        ctx->r14 = S32(0X8023 << 16);
            goto L_801F0644;
    }
    // 0x801F0404: lui         $t6, 0x8023
    ctx->r14 = S32(0X8023 << 16);
L_801F0408:
    // 0x801F0408: lui         $t6, 0x8023
    ctx->r14 = S32(0X8023 << 16);
    // 0x801F040C: lw          $t6, -0x72F8($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X72F8);
    // 0x801F0410: addiu       $s0, $zero, 0x2
    ctx->r16 = ADD32(0, 0X2);
    // 0x801F0414: bne         $t6, $zero, L_801F0444
    if (ctx->r14 != 0) {
        // 0x801F0418: nop
    
            goto L_801F0444;
    }
    // 0x801F0418: nop

    // 0x801F041C: lui         $v0, 0x8023
    ctx->r2 = S32(0X8023 << 16);
    // 0x801F0420: addiu       $v0, $v0, -0x72F4
    ctx->r2 = ADD32(ctx->r2, -0X72F4);
    // 0x801F0424: lw          $t7, 0x0($v0)
    ctx->r15 = MEM_W(ctx->r2, 0X0);
    // 0x801F0428: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801F042C: addiu       $t8, $t7, -0x3
    ctx->r24 = ADD32(ctx->r15, -0X3);
    // 0x801F0430: bgtz        $t8, L_801F068C
    if (SIGNED(ctx->r24) > 0) {
        // 0x801F0434: sw          $t8, 0x0($v0)
        MEM_W(0X0, ctx->r2) = ctx->r24;
            goto L_801F068C;
    }
    // 0x801F0434: sw          $t8, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r24;
    // 0x801F0438: sw          $zero, 0x0($v0)
    MEM_W(0X0, ctx->r2) = 0;
    // 0x801F043C: b           L_801F068C
    // 0x801F0440: sw          $t1, -0x72F8($at)
    MEM_W(-0X72F8, ctx->r1) = ctx->r9;
        goto L_801F068C;
    // 0x801F0440: sw          $t1, -0x72F8($at)
    MEM_W(-0X72F8, ctx->r1) = ctx->r9;
L_801F0444:
    // 0x801F0444: lui         $t6, 0x8023
    ctx->r14 = S32(0X8023 << 16);
    // 0x801F0448: lw          $t6, -0x7570($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X7570);
    // 0x801F044C: addiu       $at, $zero, 0xF
    ctx->r1 = ADD32(0, 0XF);
    // 0x801F0450: div         $zero, $t6, $at
    lo = S32(S64(S32(ctx->r14)) / S64(S32(ctx->r1))); hi = S32(S64(S32(ctx->r14)) % S64(S32(ctx->r1)));
    // 0x801F0454: mfhi        $t7
    ctx->r15 = hi;
    // 0x801F0458: sw          $t6, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r14;
    // 0x801F045C: bnel        $t7, $zero, L_801F04B4
    if (ctx->r15 != 0) {
        // 0x801F0460: lw          $a2, 0x20($sp)
        ctx->r6 = MEM_W(ctx->r29, 0X20);
            goto L_801F04B4;
    }
    goto skip_0;
    // 0x801F0460: lw          $a2, 0x20($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X20);
    skip_0:
    // 0x801F0464: beq         $s0, $v0, L_801F0498
    if (ctx->r16 == ctx->r2) {
        // 0x801F0468: addiu       $a0, $zero, 0x23
        ctx->r4 = ADD32(0, 0X23);
            goto L_801F0498;
    }
    // 0x801F0468: addiu       $a0, $zero, 0x23
    ctx->r4 = ADD32(0, 0X23);
    // 0x801F046C: addiu       $at, $zero, 0xF
    ctx->r1 = ADD32(0, 0XF);
    // 0x801F0470: div         $zero, $t6, $at
    lo = S32(S64(S32(ctx->r14)) / S64(S32(ctx->r1))); hi = S32(S64(S32(ctx->r14)) % S64(S32(ctx->r1)));
    // 0x801F0474: mflo        $a1
    ctx->r5 = lo;
    // 0x801F0478: addiu       $a1, $a1, -0x1
    ctx->r5 = ADD32(ctx->r5, -0X1);
    // 0x801F047C: jal         0x800C37F4
    // 0x801F0480: addiu       $a0, $zero, 0x22
    ctx->r4 = ADD32(0, 0X22);
    func_800C37F4(rdram, ctx);
        goto after_0;
    // 0x801F0480: addiu       $a0, $zero, 0x22
    ctx->r4 = ADD32(0, 0X22);
    after_0:
    // 0x801F0484: lui         $t8, 0x8023
    ctx->r24 = S32(0X8023 << 16);
    // 0x801F0488: lw          $t8, -0x7570($t8)
    ctx->r24 = MEM_W(ctx->r24, -0X7570);
    // 0x801F048C: addiu       $t1, $zero, 0x1
    ctx->r9 = ADD32(0, 0X1);
    // 0x801F0490: b           L_801F04B0
    // 0x801F0494: sw          $t8, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r24;
        goto L_801F04B0;
    // 0x801F0494: sw          $t8, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r24;
L_801F0498:
    // 0x801F0498: jal         0x800C37F4
    // 0x801F049C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_1;
    // 0x801F049C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_1:
    // 0x801F04A0: lui         $t9, 0x8023
    ctx->r25 = S32(0X8023 << 16);
    // 0x801F04A4: lw          $t9, -0x7570($t9)
    ctx->r25 = MEM_W(ctx->r25, -0X7570);
    // 0x801F04A8: addiu       $t1, $zero, 0x1
    ctx->r9 = ADD32(0, 0X1);
    // 0x801F04AC: sw          $t9, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r25;
L_801F04B0:
    // 0x801F04B0: lw          $a2, 0x20($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X20);
L_801F04B4:
    // 0x801F04B4: lui         $t2, 0x801A
    ctx->r10 = S32(0X801A << 16);
    // 0x801F04B8: addiu       $a2, $a2, -0xF
    ctx->r6 = ADD32(ctx->r6, -0XF);
    // 0x801F04BC: bgezl       $a2, L_801F04CC
    if (SIGNED(ctx->r6) >= 0) {
        // 0x801F04C0: slti        $at, $a2, 0xF
        ctx->r1 = SIGNED(ctx->r6) < 0XF ? 1 : 0;
            goto L_801F04CC;
    }
    goto skip_1;
    // 0x801F04C0: slti        $at, $a2, 0xF
    ctx->r1 = SIGNED(ctx->r6) < 0XF ? 1 : 0;
    skip_1:
    // 0x801F04C4: negu        $a2, $a2
    ctx->r6 = SUB32(0, ctx->r6);
    // 0x801F04C8: slti        $at, $a2, 0xF
    ctx->r1 = SIGNED(ctx->r6) < 0XF ? 1 : 0;
L_801F04CC:
    // 0x801F04CC: beql        $at, $zero, L_801F05F4
    if (ctx->r1 == 0) {
        // 0x801F04D0: lw          $t8, 0x20($sp)
        ctx->r24 = MEM_W(ctx->r29, 0X20);
            goto L_801F05F4;
    }
    goto skip_2;
    // 0x801F04D0: lw          $t8, 0x20($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X20);
    skip_2:
    // 0x801F04D4: lw          $t2, -0x7D10($t2)
    ctx->r10 = MEM_W(ctx->r10, -0X7D10);
    // 0x801F04D8: lui         $a3, 0x8019
    ctx->r7 = S32(0X8019 << 16);
    // 0x801F04DC: addiu       $a3, $a3, 0x2690
    ctx->r7 = ADD32(ctx->r7, 0X2690);
    // 0x801F04E0: blez        $t2, L_801F05F0
    if (SIGNED(ctx->r10) <= 0) {
        // 0x801F04E4: or          $v1, $zero, $zero
        ctx->r3 = 0 | 0;
            goto L_801F05F0;
    }
    // 0x801F04E4: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
    // 0x801F04E8: lui         $t3, 0x8023
    ctx->r11 = S32(0X8023 << 16);
    // 0x801F04EC: lui         $a0, 0x801C
    ctx->r4 = S32(0X801C << 16);
    // 0x801F04F0: addiu       $a0, $a0, 0x2938
    ctx->r4 = ADD32(ctx->r4, 0X2938);
    // 0x801F04F4: addiu       $t3, $t3, -0x74A8
    ctx->r11 = ADD32(ctx->r11, -0X74A8);
    // 0x801F04F8: addiu       $ra, $zero, 0x3
    ctx->r31 = ADD32(0, 0X3);
    // 0x801F04FC: addiu       $t5, $zero, 0x4
    ctx->r13 = ADD32(0, 0X4);
    // 0x801F0500: addiu       $t4, $zero, 0x5
    ctx->r12 = ADD32(0, 0X5);
    // 0x801F0504: addiu       $a1, $zero, 0x378
    ctx->r5 = ADD32(0, 0X378);
L_801F0508:
    // 0x801F0508: lhu         $t7, 0xB58($a3)
    ctx->r15 = MEM_HU(ctx->r7, 0XB58);
    // 0x801F050C: addu        $t0, $t3, $v1
    ctx->r8 = ADD32(ctx->r11, ctx->r3);
    // 0x801F0510: andi        $t6, $t7, 0xA000
    ctx->r14 = ctx->r15 & 0XA000;
    // 0x801F0514: beql        $t6, $zero, L_801F05E4
    if (ctx->r14 == 0) {
        // 0x801F0518: addiu       $v1, $v1, 0x1
        ctx->r3 = ADD32(ctx->r3, 0X1);
            goto L_801F05E4;
    }
    goto skip_3;
    // 0x801F0518: addiu       $v1, $v1, 0x1
    ctx->r3 = ADD32(ctx->r3, 0X1);
    skip_3:
    // 0x801F051C: lb          $t8, 0x0($t0)
    ctx->r24 = MEM_B(ctx->r8, 0X0);
    // 0x801F0520: bnel        $t8, $zero, L_801F05E4
    if (ctx->r24 != 0) {
        // 0x801F0524: addiu       $v1, $v1, 0x1
        ctx->r3 = ADD32(ctx->r3, 0X1);
            goto L_801F05E4;
    }
    goto skip_4;
    // 0x801F0524: addiu       $v1, $v1, 0x1
    ctx->r3 = ADD32(ctx->r3, 0X1);
    skip_4:
    // 0x801F0528: bgtz        $a2, L_801F0544
    if (SIGNED(ctx->r6) > 0) {
        // 0x801F052C: slti        $at, $a2, 0x2
        ctx->r1 = SIGNED(ctx->r6) < 0X2 ? 1 : 0;
            goto L_801F0544;
    }
    // 0x801F052C: slti        $at, $a2, 0x2
    ctx->r1 = SIGNED(ctx->r6) < 0X2 ? 1 : 0;
    // 0x801F0530: multu       $v1, $a1
    result = U64(U32(ctx->r3)) * U64(U32(ctx->r5)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x801F0534: mflo        $t9
    ctx->r25 = lo;
    // 0x801F0538: addu        $t7, $a0, $t9
    ctx->r15 = ADD32(ctx->r4, ctx->r25);
    // 0x801F053C: b           L_801F05BC
    // 0x801F0540: sw          $t4, 0x12C($t7)
    MEM_W(0X12C, ctx->r15) = ctx->r12;
        goto L_801F05BC;
    // 0x801F0540: sw          $t4, 0x12C($t7)
    MEM_W(0X12C, ctx->r15) = ctx->r12;
L_801F0544:
    // 0x801F0544: beql        $at, $zero, L_801F0564
    if (ctx->r1 == 0) {
        // 0x801F0548: slti        $at, $a2, 0x3
        ctx->r1 = SIGNED(ctx->r6) < 0X3 ? 1 : 0;
            goto L_801F0564;
    }
    goto skip_5;
    // 0x801F0548: slti        $at, $a2, 0x3
    ctx->r1 = SIGNED(ctx->r6) < 0X3 ? 1 : 0;
    skip_5:
    // 0x801F054C: multu       $v1, $a1
    result = U64(U32(ctx->r3)) * U64(U32(ctx->r5)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x801F0550: mflo        $t6
    ctx->r14 = lo;
    // 0x801F0554: addu        $t8, $a0, $t6
    ctx->r24 = ADD32(ctx->r4, ctx->r14);
    // 0x801F0558: b           L_801F05BC
    // 0x801F055C: sw          $t5, 0x12C($t8)
    MEM_W(0X12C, ctx->r24) = ctx->r13;
        goto L_801F05BC;
    // 0x801F055C: sw          $t5, 0x12C($t8)
    MEM_W(0X12C, ctx->r24) = ctx->r13;
    // 0x801F0560: slti        $at, $a2, 0x3
    ctx->r1 = SIGNED(ctx->r6) < 0X3 ? 1 : 0;
L_801F0564:
    // 0x801F0564: beql        $at, $zero, L_801F0584
    if (ctx->r1 == 0) {
        // 0x801F0568: slti        $at, $a2, 0x4
        ctx->r1 = SIGNED(ctx->r6) < 0X4 ? 1 : 0;
            goto L_801F0584;
    }
    goto skip_6;
    // 0x801F0568: slti        $at, $a2, 0x4
    ctx->r1 = SIGNED(ctx->r6) < 0X4 ? 1 : 0;
    skip_6:
    // 0x801F056C: multu       $v1, $a1
    result = U64(U32(ctx->r3)) * U64(U32(ctx->r5)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x801F0570: mflo        $t9
    ctx->r25 = lo;
    // 0x801F0574: addu        $t7, $a0, $t9
    ctx->r15 = ADD32(ctx->r4, ctx->r25);
    // 0x801F0578: b           L_801F05BC
    // 0x801F057C: sw          $ra, 0x12C($t7)
    MEM_W(0X12C, ctx->r15) = ctx->r31;
        goto L_801F05BC;
    // 0x801F057C: sw          $ra, 0x12C($t7)
    MEM_W(0X12C, ctx->r15) = ctx->r31;
    // 0x801F0580: slti        $at, $a2, 0x4
    ctx->r1 = SIGNED(ctx->r6) < 0X4 ? 1 : 0;
L_801F0584:
    // 0x801F0584: beql        $at, $zero, L_801F05A4
    if (ctx->r1 == 0) {
        // 0x801F0588: slti        $at, $a2, 0x5
        ctx->r1 = SIGNED(ctx->r6) < 0X5 ? 1 : 0;
            goto L_801F05A4;
    }
    goto skip_7;
    // 0x801F0588: slti        $at, $a2, 0x5
    ctx->r1 = SIGNED(ctx->r6) < 0X5 ? 1 : 0;
    skip_7:
    // 0x801F058C: multu       $v1, $a1
    result = U64(U32(ctx->r3)) * U64(U32(ctx->r5)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x801F0590: mflo        $t6
    ctx->r14 = lo;
    // 0x801F0594: addu        $t8, $a0, $t6
    ctx->r24 = ADD32(ctx->r4, ctx->r14);
    // 0x801F0598: b           L_801F05BC
    // 0x801F059C: sw          $s0, 0x12C($t8)
    MEM_W(0X12C, ctx->r24) = ctx->r16;
        goto L_801F05BC;
    // 0x801F059C: sw          $s0, 0x12C($t8)
    MEM_W(0X12C, ctx->r24) = ctx->r16;
    // 0x801F05A0: slti        $at, $a2, 0x5
    ctx->r1 = SIGNED(ctx->r6) < 0X5 ? 1 : 0;
L_801F05A4:
    // 0x801F05A4: beql        $at, $zero, L_801F05C0
    if (ctx->r1 == 0) {
        // 0x801F05A8: slti        $at, $a2, 0x5
        ctx->r1 = SIGNED(ctx->r6) < 0X5 ? 1 : 0;
            goto L_801F05C0;
    }
    goto skip_8;
    // 0x801F05A8: slti        $at, $a2, 0x5
    ctx->r1 = SIGNED(ctx->r6) < 0X5 ? 1 : 0;
    skip_8:
    // 0x801F05AC: multu       $v1, $a1
    result = U64(U32(ctx->r3)) * U64(U32(ctx->r5)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x801F05B0: mflo        $t9
    ctx->r25 = lo;
    // 0x801F05B4: addu        $t7, $a0, $t9
    ctx->r15 = ADD32(ctx->r4, ctx->r25);
    // 0x801F05B8: sw          $t1, 0x12C($t7)
    MEM_W(0X12C, ctx->r15) = ctx->r9;
L_801F05BC:
    // 0x801F05BC: slti        $at, $a2, 0x5
    ctx->r1 = SIGNED(ctx->r6) < 0X5 ? 1 : 0;
L_801F05C0:
    // 0x801F05C0: beql        $at, $zero, L_801F05E0
    if (ctx->r1 == 0) {
        // 0x801F05C4: sb          $t1, 0x0($t0)
        MEM_B(0X0, ctx->r8) = ctx->r9;
            goto L_801F05E0;
    }
    goto skip_9;
    // 0x801F05C4: sb          $t1, 0x0($t0)
    MEM_B(0X0, ctx->r8) = ctx->r9;
    skip_9:
    // 0x801F05C8: multu       $v1, $a1
    result = U64(U32(ctx->r3)) * U64(U32(ctx->r5)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x801F05CC: mflo        $t6
    ctx->r14 = lo;
    // 0x801F05D0: addu        $v0, $a0, $t6
    ctx->r2 = ADD32(ctx->r4, ctx->r14);
    // 0x801F05D4: sw          $t1, 0x314($v0)
    MEM_W(0X314, ctx->r2) = ctx->r9;
    // 0x801F05D8: sw          $t1, 0x28($v0)
    MEM_W(0X28, ctx->r2) = ctx->r9;
    // 0x801F05DC: sb          $t1, 0x0($t0)
    MEM_B(0X0, ctx->r8) = ctx->r9;
L_801F05E0:
    // 0x801F05E0: addiu       $v1, $v1, 0x1
    ctx->r3 = ADD32(ctx->r3, 0X1);
L_801F05E4:
    // 0x801F05E4: slt         $at, $v1, $t2
    ctx->r1 = SIGNED(ctx->r3) < SIGNED(ctx->r10) ? 1 : 0;
    // 0x801F05E8: bne         $at, $zero, L_801F0508
    if (ctx->r1 != 0) {
        // 0x801F05EC: addiu       $a3, $a3, 0x1718
        ctx->r7 = ADD32(ctx->r7, 0X1718);
            goto L_801F0508;
    }
    // 0x801F05EC: addiu       $a3, $a3, 0x1718
    ctx->r7 = ADD32(ctx->r7, 0X1718);
L_801F05F0:
    // 0x801F05F0: lw          $t8, 0x20($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X20);
L_801F05F4:
    // 0x801F05F4: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801F05F8: addiu       $ra, $zero, 0x3
    ctx->r31 = ADD32(0, 0X3);
    // 0x801F05FC: addiu       $t9, $t8, -0x1
    ctx->r25 = ADD32(ctx->r24, -0X1);
    // 0x801F0600: sw          $t9, -0x7570($at)
    MEM_W(-0X7570, ctx->r1) = ctx->r25;
    // 0x801F0604: addiu       $at, $zero, 0xF
    ctx->r1 = ADD32(0, 0XF);
    // 0x801F0608: bne         $t9, $at, L_801F0624
    if (ctx->r25 != ctx->r1) {
        // 0x801F060C: sw          $t9, 0x20($sp)
        MEM_W(0X20, ctx->r29) = ctx->r25;
            goto L_801F0624;
    }
    // 0x801F060C: sw          $t9, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r25;
    // 0x801F0610: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801F0614: sw          $s0, -0x19B0($at)
    MEM_W(-0X19B0, ctx->r1) = ctx->r16;
    // 0x801F0618: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x801F061C: b           L_801F068C
    // 0x801F0620: sw          $zero, -0x7E84($at)
    MEM_W(-0X7E84, ctx->r1) = 0;
        goto L_801F068C;
    // 0x801F0620: sw          $zero, -0x7E84($at)
    MEM_W(-0X7E84, ctx->r1) = 0;
L_801F0624:
    // 0x801F0624: lw          $t7, 0x20($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X20);
    // 0x801F0628: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x801F062C: bgtzl       $t7, L_801F0690
    if (SIGNED(ctx->r15) > 0) {
        // 0x801F0630: lw          $ra, 0x1C($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X1C);
            goto L_801F0690;
    }
    goto skip_10;
    // 0x801F0630: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    skip_10:
    // 0x801F0634: sw          $ra, -0x19B0($at)
    MEM_W(-0X19B0, ctx->r1) = ctx->r31;
    // 0x801F0638: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801F063C: b           L_801F068C
    // 0x801F0640: sw          $s0, -0x72F8($at)
    MEM_W(-0X72F8, ctx->r1) = ctx->r16;
        goto L_801F068C;
    // 0x801F0640: sw          $s0, -0x72F8($at)
    MEM_W(-0X72F8, ctx->r1) = ctx->r16;
L_801F0644:
    // 0x801F0644: lw          $t6, -0x72F8($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X72F8);
    // 0x801F0648: lui         $t8, 0x801D
    ctx->r24 = S32(0X801D << 16);
    // 0x801F064C: bnel        $s0, $t6, L_801F0690
    if (ctx->r16 != ctx->r14) {
        // 0x801F0650: lw          $ra, 0x1C($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X1C);
            goto L_801F0690;
    }
    goto skip_11;
    // 0x801F0650: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    skip_11:
    // 0x801F0654: lh          $t8, -0x19DC($t8)
    ctx->r24 = MEM_H(ctx->r24, -0X19DC);
    // 0x801F0658: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x801F065C: lui         $v0, 0x8023
    ctx->r2 = S32(0X8023 << 16);
    // 0x801F0660: bne         $t8, $at, L_801F068C
    if (ctx->r24 != ctx->r1) {
        // 0x801F0664: addiu       $v0, $v0, -0x72F4
        ctx->r2 = ADD32(ctx->r2, -0X72F4);
            goto L_801F068C;
    }
    // 0x801F0664: addiu       $v0, $v0, -0x72F4
    ctx->r2 = ADD32(ctx->r2, -0X72F4);
    // 0x801F0668: lw          $t9, 0x0($v0)
    ctx->r25 = MEM_W(ctx->r2, 0X0);
    // 0x801F066C: lui         $t8, 0x8023
    ctx->r24 = S32(0X8023 << 16);
    // 0x801F0670: addiu       $t7, $t9, 0x6
    ctx->r15 = ADD32(ctx->r25, 0X6);
    // 0x801F0674: sw          $t7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r15;
    // 0x801F0678: lw          $t8, -0x72F0($t8)
    ctx->r24 = MEM_W(ctx->r24, -0X72F0);
    // 0x801F067C: slt         $at, $t7, $t8
    ctx->r1 = SIGNED(ctx->r15) < SIGNED(ctx->r24) ? 1 : 0;
    // 0x801F0680: bne         $at, $zero, L_801F068C
    if (ctx->r1 != 0) {
        // 0x801F0684: lui         $at, 0x8023
        ctx->r1 = S32(0X8023 << 16);
            goto L_801F068C;
    }
    // 0x801F0684: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x801F0688: sw          $zero, -0x72F8($at)
    MEM_W(-0X72F8, ctx->r1) = 0;
L_801F068C:
    // 0x801F068C: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
L_801F0690:
    // 0x801F0690: lw          $s0, 0x18($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X18);
    // 0x801F0694: addiu       $sp, $sp, 0x30
    ctx->r29 = ADD32(ctx->r29, 0X30);
    // 0x801F0698: jr          $ra
    // 0x801F069C: nop

    return;
    // 0x801F069C: nop

;}
RECOMP_FUNC void func_801F06A0(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x801F06A0: lui         $v1, 0x8023
    ctx->r3 = S32(0X8023 << 16);
    // 0x801F06A4: lw          $v1, -0x7570($v1)
    ctx->r3 = MEM_W(ctx->r3, -0X7570);
    // 0x801F06A8: addiu       $at, $zero, 0xF
    ctx->r1 = ADD32(0, 0XF);
    // 0x801F06AC: addiu       $sp, $sp, -0x198
    ctx->r29 = ADD32(ctx->r29, -0X198);
    // 0x801F06B0: addiu       $v1, $v1, -0x1
    ctx->r3 = ADD32(ctx->r3, -0X1);
    // 0x801F06B4: div         $zero, $v1, $at
    lo = S32(S64(S32(ctx->r3)) / S64(S32(ctx->r1))); hi = S32(S64(S32(ctx->r3)) % S64(S32(ctx->r1)));
    // 0x801F06B8: sw          $ra, 0x5C($sp)
    MEM_W(0X5C, ctx->r29) = ctx->r31;
    // 0x801F06BC: sw          $fp, 0x58($sp)
    MEM_W(0X58, ctx->r29) = ctx->r30;
    // 0x801F06C0: sw          $s7, 0x54($sp)
    MEM_W(0X54, ctx->r29) = ctx->r23;
    // 0x801F06C4: sw          $s6, 0x50($sp)
    MEM_W(0X50, ctx->r29) = ctx->r22;
    // 0x801F06C8: sw          $s5, 0x4C($sp)
    MEM_W(0X4C, ctx->r29) = ctx->r21;
    // 0x801F06CC: sw          $s4, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r20;
    // 0x801F06D0: sw          $s3, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r19;
    // 0x801F06D4: sw          $s2, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r18;
    // 0x801F06D8: sw          $s1, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r17;
    // 0x801F06DC: sw          $s0, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r16;
    // 0x801F06E0: sw          $a0, 0x198($sp)
    MEM_W(0X198, ctx->r29) = ctx->r4;
    // 0x801F06E4: mflo        $v1
    ctx->r3 = lo;
    // 0x801F06E8: lw          $v0, 0x0($a0)
    ctx->r2 = MEM_W(ctx->r4, 0X0);
    // 0x801F06EC: bgez        $v1, L_801F06F8
    if (SIGNED(ctx->r3) >= 0) {
        // 0x801F06F0: lui         $s5, 0x8023
        ctx->r21 = S32(0X8023 << 16);
            goto L_801F06F8;
    }
    // 0x801F06F0: lui         $s5, 0x8023
    ctx->r21 = S32(0X8023 << 16);
    // 0x801F06F4: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
L_801F06F8:
    // 0x801F06F8: addiu       $s5, $s5, -0x72F8
    ctx->r21 = ADD32(ctx->r21, -0X72F8);
    // 0x801F06FC: lw          $t8, 0x0($s5)
    ctx->r24 = MEM_W(ctx->r21, 0X0);
    // 0x801F0700: lui         $s0, 0x801B
    ctx->r16 = S32(0X801B << 16);
    // 0x801F0704: addiu       $s0, $s0, -0x16B0
    ctx->r16 = ADD32(ctx->r16, -0X16B0);
    // 0x801F0708: bne         $t8, $zero, L_801F0714
    if (ctx->r24 != 0) {
        // 0x801F070C: lui         $s1, 0x801B
        ctx->r17 = S32(0X801B << 16);
            goto L_801F0714;
    }
    // 0x801F070C: lui         $s1, 0x801B
    ctx->r17 = S32(0X801B << 16);
    // 0x801F0710: addiu       $v1, $zero, 0x4
    ctx->r3 = ADD32(0, 0X4);
L_801F0714:
    // 0x801F0714: blez        $v1, L_801F073C
    if (SIGNED(ctx->r3) <= 0) {
        // 0x801F0718: addiu       $s1, $s1, -0x16B8
        ctx->r17 = ADD32(ctx->r17, -0X16B8);
            goto L_801F073C;
    }
    // 0x801F0718: addiu       $s1, $s1, -0x16B8
    ctx->r17 = ADD32(ctx->r17, -0X16B8);
    // 0x801F071C: slti        $at, $v1, 0x4
    ctx->r1 = SIGNED(ctx->r3) < 0X4 ? 1 : 0;
    // 0x801F0720: beq         $at, $zero, L_801F073C
    if (ctx->r1 == 0) {
        // 0x801F0724: lui         $a0, 0x101
        ctx->r4 = S32(0X101 << 16);
            goto L_801F073C;
    }
    // 0x801F0724: lui         $a0, 0x101
    ctx->r4 = S32(0X101 << 16);
    // 0x801F0728: addiu       $a0, $a0, 0x3BA8
    ctx->r4 = ADD32(ctx->r4, 0X3BA8);
    // 0x801F072C: lui         $a1, 0x101
    ctx->r5 = S32(0X101 << 16);
    // 0x801F0730: addiu       $a1, $a1, 0x33A8
    ctx->r5 = ADD32(ctx->r5, 0X33A8);
    // 0x801F0734: b           L_801F0750
    // 0x801F0738: sw          $a0, 0x188($sp)
    MEM_W(0X188, ctx->r29) = ctx->r4;
        goto L_801F0750;
    // 0x801F0738: sw          $a0, 0x188($sp)
    MEM_W(0X188, ctx->r29) = ctx->r4;
L_801F073C:
    // 0x801F073C: lui         $a1, 0x101
    ctx->r5 = S32(0X101 << 16);
    // 0x801F0740: addiu       $a1, $a1, 0x33A8
    ctx->r5 = ADD32(ctx->r5, 0X33A8);
    // 0x801F0744: lui         $a0, 0x101
    ctx->r4 = S32(0X101 << 16);
    // 0x801F0748: addiu       $a0, $a0, 0x3BA8
    ctx->r4 = ADD32(ctx->r4, 0X3BA8);
    // 0x801F074C: sw          $a1, 0x188($sp)
    MEM_W(0X188, ctx->r29) = ctx->r5;
L_801F0750:
    // 0x801F0750: blez        $v1, L_801F076C
    if (SIGNED(ctx->r3) <= 0) {
        // 0x801F0754: lui         $s3, 0x8023
        ctx->r19 = S32(0X8023 << 16);
            goto L_801F076C;
    }
    // 0x801F0754: lui         $s3, 0x8023
    ctx->r19 = S32(0X8023 << 16);
    // 0x801F0758: slti        $at, $v1, 0x3
    ctx->r1 = SIGNED(ctx->r3) < 0X3 ? 1 : 0;
    // 0x801F075C: beql        $at, $zero, L_801F0770
    if (ctx->r1 == 0) {
        // 0x801F0760: sw          $a1, 0x184($sp)
        MEM_W(0X184, ctx->r29) = ctx->r5;
            goto L_801F0770;
    }
    goto skip_0;
    // 0x801F0760: sw          $a1, 0x184($sp)
    MEM_W(0X184, ctx->r29) = ctx->r5;
    skip_0:
    // 0x801F0764: b           L_801F0770
    // 0x801F0768: sw          $a0, 0x184($sp)
    MEM_W(0X184, ctx->r29) = ctx->r4;
        goto L_801F0770;
    // 0x801F0768: sw          $a0, 0x184($sp)
    MEM_W(0X184, ctx->r29) = ctx->r4;
L_801F076C:
    // 0x801F076C: sw          $a1, 0x184($sp)
    MEM_W(0X184, ctx->r29) = ctx->r5;
L_801F0770:
    // 0x801F0770: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x801F0774: bne         $v1, $at, L_801F0784
    if (ctx->r3 != ctx->r1) {
        // 0x801F0778: addiu       $s3, $s3, -0x72DC
        ctx->r19 = ADD32(ctx->r19, -0X72DC);
            goto L_801F0784;
    }
    // 0x801F0778: addiu       $s3, $s3, -0x72DC
    ctx->r19 = ADD32(ctx->r19, -0X72DC);
    // 0x801F077C: b           L_801F0788
    // 0x801F0780: sw          $a0, 0x180($sp)
    MEM_W(0X180, ctx->r29) = ctx->r4;
        goto L_801F0788;
    // 0x801F0780: sw          $a0, 0x180($sp)
    MEM_W(0X180, ctx->r29) = ctx->r4;
L_801F0784:
    // 0x801F0784: sw          $a1, 0x180($sp)
    MEM_W(0X180, ctx->r29) = ctx->r5;
L_801F0788:
    // 0x801F0788: bne         $v1, $zero, L_801F07A0
    if (ctx->r3 != 0) {
        // 0x801F078C: lui         $s6, 0x600
        ctx->r22 = S32(0X600 << 16);
            goto L_801F07A0;
    }
    // 0x801F078C: lui         $s6, 0x600
    ctx->r22 = S32(0X600 << 16);
    // 0x801F0790: lui         $t9, 0x101
    ctx->r25 = S32(0X101 << 16);
    // 0x801F0794: addiu       $t9, $t9, 0x2BA8
    ctx->r25 = ADD32(ctx->r25, 0X2BA8);
    // 0x801F0798: b           L_801F07AC
    // 0x801F079C: sw          $t9, 0x17C($sp)
    MEM_W(0X17C, ctx->r29) = ctx->r25;
        goto L_801F07AC;
    // 0x801F079C: sw          $t9, 0x17C($sp)
    MEM_W(0X17C, ctx->r29) = ctx->r25;
L_801F07A0:
    // 0x801F07A0: lui         $t6, 0x101
    ctx->r14 = S32(0X101 << 16);
    // 0x801F07A4: addiu       $t6, $t6, 0x23A8
    ctx->r14 = ADD32(ctx->r14, 0X23A8);
    // 0x801F07A8: sw          $t6, 0x17C($sp)
    MEM_W(0X17C, ctx->r29) = ctx->r14;
L_801F07AC:
    // 0x801F07AC: or          $v1, $v0, $zero
    ctx->r3 = ctx->r2 | 0;
    // 0x801F07B0: lui         $t7, 0x101
    ctx->r15 = S32(0X101 << 16);
    // 0x801F07B4: addiu       $t7, $t7, 0x4658
    ctx->r15 = ADD32(ctx->r15, 0X4658);
    // 0x801F07B8: sw          $t7, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r15;
    // 0x801F07BC: sw          $s6, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r22;
    // 0x801F07C0: lw          $t9, 0x0($s0)
    ctx->r25 = MEM_W(ctx->r16, 0X0);
    // 0x801F07C4: lui         $at, 0x4180
    ctx->r1 = S32(0X4180 << 16);
    // 0x801F07C8: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x801F07CC: lw          $t8, 0x0($s1)
    ctx->r24 = MEM_W(ctx->r17, 0X0);
    // 0x801F07D0: mtc1        $zero, $f0
    ctx->f0.u32l = 0;
    // 0x801F07D4: lui         $at, 0x4480
    ctx->r1 = S32(0X4480 << 16);
    // 0x801F07D8: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x801F07DC: sll         $t6, $t9, 6
    ctx->r14 = S32(ctx->r25 << 6);
    // 0x801F07E0: addiu       $v0, $v0, 0x8
    ctx->r2 = ADD32(ctx->r2, 0X8);
    // 0x801F07E4: addu        $a0, $t8, $t6
    ctx->r4 = ADD32(ctx->r24, ctx->r14);
    // 0x801F07E8: addiu       $a0, $a0, 0x4140
    ctx->r4 = ADD32(ctx->r4, 0X4140);
    // 0x801F07EC: lui         $a3, 0x3FE2
    ctx->r7 = S32(0X3FE2 << 16);
    // 0x801F07F0: addiu       $a3, $a3, 0x2222
    ctx->r7 = ADD32(ctx->r7, 0X2222);
    // 0x801F07F4: sw          $v0, 0x178($sp)
    MEM_W(0X178, ctx->r29) = ctx->r2;
    // 0x801F07F8: or          $a1, $s3, $zero
    ctx->r5 = ctx->r19 | 0;
    // 0x801F07FC: lui         $a2, 0x42F0
    ctx->r6 = S32(0X42F0 << 16);
    // 0x801F0800: swc1        $f4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f4.u32l;
    // 0x801F0804: swc1        $f0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->f0.u32l;
    // 0x801F0808: swc1        $f0, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->f0.u32l;
    // 0x801F080C: jal         0x800481E0
    // 0x801F0810: swc1        $f6, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->f6.u32l;
    func_800481E0(rdram, ctx);
        goto after_0;
    // 0x801F0810: swc1        $f6, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->f6.u32l;
    after_0:
    // 0x801F0814: lw          $v1, 0x178($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X178);
    // 0x801F0818: lui         $t7, 0x103
    ctx->r15 = S32(0X103 << 16);
    // 0x801F081C: ori         $t7, $t7, 0x40
    ctx->r15 = ctx->r15 | 0X40;
    // 0x801F0820: sw          $t7, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r15;
    // 0x801F0824: lw          $t9, 0x0($s0)
    ctx->r25 = MEM_W(ctx->r16, 0X0);
    // 0x801F0828: lui         $s2, 0x500
    ctx->r18 = S32(0X500 << 16);
    // 0x801F082C: addiu       $s2, $s2, 0x0
    ctx->r18 = ADD32(ctx->r18, 0X0);
    // 0x801F0830: sll         $t8, $t9, 6
    ctx->r24 = S32(ctx->r25 << 6);
    // 0x801F0834: addu        $t6, $s2, $t8
    ctx->r14 = ADD32(ctx->r18, ctx->r24);
    // 0x801F0838: addiu       $t7, $t6, 0x4140
    ctx->r15 = ADD32(ctx->r14, 0X4140);
    // 0x801F083C: sw          $t7, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r15;
    // 0x801F0840: lw          $t9, 0x0($s0)
    ctx->r25 = MEM_W(ctx->r16, 0X0);
    // 0x801F0844: lui         $fp, 0x800E
    ctx->r30 = S32(0X800E << 16);
    // 0x801F0848: addiu       $fp, $fp, -0x54D8
    ctx->r30 = ADD32(ctx->r30, -0X54D8);
    // 0x801F084C: addiu       $t8, $t9, 0x1
    ctx->r24 = ADD32(ctx->r25, 0X1);
    // 0x801F0850: sw          $t8, 0x0($s0)
    MEM_W(0X0, ctx->r16) = ctx->r24;
    // 0x801F0854: sll         $t9, $t8, 6
    ctx->r25 = S32(ctx->r24 << 6);
    // 0x801F0858: lw          $t8, 0x0($fp)
    ctx->r24 = MEM_W(ctx->r30, 0X0);
    // 0x801F085C: addiu       $s7, $zero, 0x2
    ctx->r23 = ADD32(0, 0X2);
    // 0x801F0860: lui         $at, 0x41A0
    ctx->r1 = S32(0X41A0 << 16);
    // 0x801F0864: xor         $t7, $s7, $t8
    ctx->r15 = ctx->r23 ^ ctx->r24;
    // 0x801F0868: sltiu       $t7, $t7, 0x1
    ctx->r15 = ctx->r15 < 0X1 ? 1 : 0;
    // 0x801F086C: mtc1        $t7, $f8
    ctx->f8.u32l = ctx->r15;
    // 0x801F0870: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
    // 0x801F0874: mtc1        $zero, $f0
    ctx->f0.u32l = 0;
    // 0x801F0878: cvt.s.w     $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.fl = CVT_S_W(ctx->f8.u32l);
    // 0x801F087C: lui         $at, 0x4270
    ctx->r1 = S32(0X4270 << 16);
    // 0x801F0880: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x801F0884: lw          $t6, 0x0($s1)
    ctx->r14 = MEM_W(ctx->r17, 0X0);
    // 0x801F0888: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x801F088C: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x801F0890: mul.s       $f18, $f10, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f18.fl = MUL_S(ctx->f10.fl, ctx->f16.fl);
    // 0x801F0894: addiu       $v0, $v1, 0x8
    ctx->r2 = ADD32(ctx->r3, 0X8);
    // 0x801F0898: mfc1        $a2, $f0
    ctx->r6 = (int32_t)ctx->f0.u32l;
    // 0x801F089C: mfc1        $a3, $f0
    ctx->r7 = (int32_t)ctx->f0.u32l;
    // 0x801F08A0: addu        $a0, $t6, $t9
    ctx->r4 = ADD32(ctx->r14, ctx->r25);
    // 0x801F08A4: addiu       $a0, $a0, 0x4140
    ctx->r4 = ADD32(ctx->r4, 0X4140);
    // 0x801F08A8: sw          $v0, 0x178($sp)
    MEM_W(0X178, ctx->r29) = ctx->r2;
    // 0x801F08AC: add.s       $f6, $f18, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = ctx->f18.fl + ctx->f4.fl;
    // 0x801F08B0: addiu       $a1, $sp, 0x138
    ctx->r5 = ADD32(ctx->r29, 0X138);
    // 0x801F08B4: swc1        $f0, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->f0.u32l;
    // 0x801F08B8: swc1        $f0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->f0.u32l;
    // 0x801F08BC: swc1        $f6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f6.u32l;
    // 0x801F08C0: swc1        $f0, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->f0.u32l;
    // 0x801F08C4: swc1        $f0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->f0.u32l;
    // 0x801F08C8: swc1        $f0, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->f0.u32l;
    // 0x801F08CC: jal         0x800484C8
    // 0x801F08D0: swc1        $f8, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->f8.u32l;
    func_800484C8(rdram, ctx);
        goto after_1;
    // 0x801F08D0: swc1        $f8, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->f8.u32l;
    after_1:
    // 0x801F08D4: lw          $v1, 0x178($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X178);
    // 0x801F08D8: lui         $t6, 0x102
    ctx->r14 = S32(0X102 << 16);
    // 0x801F08DC: ori         $t6, $t6, 0x40
    ctx->r14 = ctx->r14 | 0X40;
    // 0x801F08E0: sw          $t6, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r14;
    // 0x801F08E4: lw          $t9, 0x0($s0)
    ctx->r25 = MEM_W(ctx->r16, 0X0);
    // 0x801F08E8: addiu       $t0, $v1, 0x8
    ctx->r8 = ADD32(ctx->r3, 0X8);
    // 0x801F08EC: lui         $s4, 0x8023
    ctx->r20 = S32(0X8023 << 16);
    // 0x801F08F0: sll         $t8, $t9, 6
    ctx->r24 = S32(ctx->r25 << 6);
    // 0x801F08F4: addu        $t7, $s2, $t8
    ctx->r15 = ADD32(ctx->r18, ctx->r24);
    // 0x801F08F8: addiu       $t6, $t7, 0x4140
    ctx->r14 = ADD32(ctx->r15, 0X4140);
    // 0x801F08FC: sw          $t6, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r14;
    // 0x801F0900: lw          $t9, 0x0($s0)
    ctx->r25 = MEM_W(ctx->r16, 0X0);
    // 0x801F0904: lui         $t7, 0xB400
    ctx->r15 = S32(0XB400 << 16);
    // 0x801F0908: addiu       $s4, $s4, -0x72F4
    ctx->r20 = ADD32(ctx->r20, -0X72F4);
    // 0x801F090C: addiu       $t8, $t9, 0x1
    ctx->r24 = ADD32(ctx->r25, 0X1);
    // 0x801F0910: sw          $t8, 0x0($s0)
    MEM_W(0X0, ctx->r16) = ctx->r24;
    // 0x801F0914: sw          $t7, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r15;
    // 0x801F0918: lhu         $t6, 0x0($s3)
    ctx->r14 = MEM_HU(ctx->r19, 0X0);
    // 0x801F091C: mtc1        $zero, $f0
    ctx->f0.u32l = 0;
    // 0x801F0920: addiu       $v0, $t0, 0x8
    ctx->r2 = ADD32(ctx->r8, 0X8);
    // 0x801F0924: sw          $t6, 0x4($t0)
    MEM_W(0X4, ctx->r8) = ctx->r14;
    // 0x801F0928: lw          $t6, 0x0($s4)
    ctx->r14 = MEM_W(ctx->r20, 0X0);
    // 0x801F092C: lw          $t8, 0x0($s0)
    ctx->r24 = MEM_W(ctx->r16, 0X0);
    // 0x801F0930: lw          $t9, 0x0($s1)
    ctx->r25 = MEM_W(ctx->r17, 0X0);
    // 0x801F0934: mtc1        $t6, $f10
    ctx->f10.u32l = ctx->r14;
    // 0x801F0938: sll         $t7, $t8, 6
    ctx->r15 = S32(ctx->r24 << 6);
    // 0x801F093C: mfc1        $a1, $f0
    ctx->r5 = (int32_t)ctx->f0.u32l;
    // 0x801F0940: cvt.s.w     $f10, $f10
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 10);
    ctx->f10.fl = CVT_S_W(ctx->f10.u32l);
    // 0x801F0944: mfc1        $a3, $f0
    ctx->r7 = (int32_t)ctx->f0.u32l;
    // 0x801F0948: addu        $a0, $t9, $t7
    ctx->r4 = ADD32(ctx->r25, ctx->r15);
    // 0x801F094C: addiu       $a0, $a0, 0x4140
    ctx->r4 = ADD32(ctx->r4, 0X4140);
    // 0x801F0950: sw          $v0, 0x178($sp)
    MEM_W(0X178, ctx->r29) = ctx->r2;
    // 0x801F0954: mfc1        $a2, $f10
    ctx->r6 = (int32_t)ctx->f10.u32l;
    // 0x801F0958: jal         0x801EDFFC
    // 0x801F095C: nop

    func_801EDFFC(rdram, ctx);
        goto after_2;
    // 0x801F095C: nop

    after_2:
    // 0x801F0960: lw          $v0, 0x178($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X178);
    // 0x801F0964: lui         $s3, 0x100
    ctx->r19 = S32(0X100 << 16);
    // 0x801F0968: ori         $s3, $s3, 0x40
    ctx->r19 = ctx->r19 | 0X40;
    // 0x801F096C: or          $v1, $v0, $zero
    ctx->r3 = ctx->r2 | 0;
    // 0x801F0970: sw          $s3, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r19;
    // 0x801F0974: lw          $t8, 0x0($s0)
    ctx->r24 = MEM_W(ctx->r16, 0X0);
    // 0x801F0978: lui         $at, 0x42C8
    ctx->r1 = S32(0X42C8 << 16);
    // 0x801F097C: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x801F0980: sll         $t9, $t8, 6
    ctx->r25 = S32(ctx->r24 << 6);
    // 0x801F0984: addu        $t7, $s2, $t9
    ctx->r15 = ADD32(ctx->r18, ctx->r25);
    // 0x801F0988: addiu       $t6, $t7, 0x4140
    ctx->r14 = ADD32(ctx->r15, 0X4140);
    // 0x801F098C: sw          $t6, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r14;
    // 0x801F0990: lw          $t7, 0x0($s4)
    ctx->r15 = MEM_W(ctx->r20, 0X0);
    // 0x801F0994: lui         $at, 0x42F0
    ctx->r1 = S32(0X42F0 << 16);
    // 0x801F0998: mtc1        $zero, $f0
    ctx->f0.u32l = 0;
    // 0x801F099C: mtc1        $t7, $f16
    ctx->f16.u32l = ctx->r15;
    // 0x801F09A0: lw          $t8, 0x0($s0)
    ctx->r24 = MEM_W(ctx->r16, 0X0);
    // 0x801F09A4: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x801F09A8: cvt.s.w     $f18, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    ctx->f18.fl = CVT_S_W(ctx->f16.u32l);
    // 0x801F09AC: lw          $t6, 0x0($s5)
    ctx->r14 = MEM_W(ctx->r21, 0X0);
    // 0x801F09B0: mfc1        $a2, $f0
    ctx->r6 = (int32_t)ctx->f0.u32l;
    // 0x801F09B4: addiu       $t9, $t8, 0x1
    ctx->r25 = ADD32(ctx->r24, 0X1);
    // 0x801F09B8: sw          $t9, 0x0($s0)
    MEM_W(0X0, ctx->r16) = ctx->r25;
    // 0x801F09BC: lui         $a3, 0x3F80
    ctx->r7 = S32(0X3F80 << 16);
    // 0x801F09C0: div.s       $f6, $f18, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = DIV_S(ctx->f18.fl, ctx->f4.fl);
    // 0x801F09C4: addiu       $v0, $v0, 0x8
    ctx->r2 = ADD32(ctx->r2, 0X8);
    // 0x801F09C8: mul.s       $f2, $f6, $f8
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f2.fl = MUL_S(ctx->f6.fl, ctx->f8.fl);
    // 0x801F09CC: bnel        $s7, $t6, L_801F09DC
    if (ctx->r23 != ctx->r14) {
        // 0x801F09D0: lw          $t9, 0x0($s0)
        ctx->r25 = MEM_W(ctx->r16, 0X0);
            goto L_801F09DC;
    }
    goto skip_1;
    // 0x801F09D0: lw          $t9, 0x0($s0)
    ctx->r25 = MEM_W(ctx->r16, 0X0);
    skip_1:
    // 0x801F09D4: neg.s       $f2, $f2
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f2.fl); 
    ctx->f2.fl = -ctx->f2.fl;
    // 0x801F09D8: lw          $t9, 0x0($s0)
    ctx->r25 = MEM_W(ctx->r16, 0X0);
L_801F09DC:
    // 0x801F09DC: lw          $t8, 0x0($s1)
    ctx->r24 = MEM_W(ctx->r17, 0X0);
    // 0x801F09E0: mfc1        $a1, $f2
    ctx->r5 = (int32_t)ctx->f2.u32l;
    // 0x801F09E4: sll         $t7, $t9, 6
    ctx->r15 = S32(ctx->r25 << 6);
    // 0x801F09E8: addu        $a0, $t8, $t7
    ctx->r4 = ADD32(ctx->r24, ctx->r15);
    // 0x801F09EC: addiu       $a0, $a0, 0x4140
    ctx->r4 = ADD32(ctx->r4, 0X4140);
    // 0x801F09F0: swc1        $f0, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f0.u32l;
    // 0x801F09F4: jal         0x801EE228
    // 0x801F09F8: sw          $v0, 0x178($sp)
    MEM_W(0X178, ctx->r29) = ctx->r2;
    func_801EE228(rdram, ctx);
        goto after_3;
    // 0x801F09F8: sw          $v0, 0x178($sp)
    MEM_W(0X178, ctx->r29) = ctx->r2;
    after_3:
    // 0x801F09FC: lw          $v0, 0x178($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X178);
    // 0x801F0A00: lui         $s7, 0x380
    ctx->r23 = S32(0X380 << 16);
    // 0x801F0A04: ori         $s7, $s7, 0x10
    ctx->r23 = ctx->r23 | 0X10;
    // 0x801F0A08: or          $v1, $v0, $zero
    ctx->r3 = ctx->r2 | 0;
    // 0x801F0A0C: sw          $s3, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r19;
    // 0x801F0A10: lw          $t6, 0x0($s0)
    ctx->r14 = MEM_W(ctx->r16, 0X0);
    // 0x801F0A14: or          $s5, $zero, $zero
    ctx->r21 = 0 | 0;
    // 0x801F0A18: addiu       $v0, $v0, 0x8
    ctx->r2 = ADD32(ctx->r2, 0X8);
    // 0x801F0A1C: sll         $t9, $t6, 6
    ctx->r25 = S32(ctx->r14 << 6);
    // 0x801F0A20: addu        $t8, $s2, $t9
    ctx->r24 = ADD32(ctx->r18, ctx->r25);
    // 0x801F0A24: addiu       $t7, $t8, 0x4140
    ctx->r15 = ADD32(ctx->r24, 0X4140);
    // 0x801F0A28: sw          $t7, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r15;
    // 0x801F0A2C: lw          $t6, 0x0($s0)
    ctx->r14 = MEM_W(ctx->r16, 0X0);
    // 0x801F0A30: lw          $a2, 0x0($fp)
    ctx->r6 = MEM_W(ctx->r30, 0X0);
    // 0x801F0A34: lui         $fp, 0x101
    ctx->r30 = S32(0X101 << 16);
    // 0x801F0A38: addiu       $t9, $t6, 0x1
    ctx->r25 = ADD32(ctx->r14, 0X1);
    // 0x801F0A3C: blez        $a2, L_801F0D6C
    if (SIGNED(ctx->r6) <= 0) {
        // 0x801F0A40: sw          $t9, 0x0($s0)
        MEM_W(0X0, ctx->r16) = ctx->r25;
            goto L_801F0D6C;
    }
    // 0x801F0A40: sw          $t9, 0x0($s0)
    MEM_W(0X0, ctx->r16) = ctx->r25;
    // 0x801F0A44: lui         $t8, 0x101
    ctx->r24 = S32(0X101 << 16);
    // 0x801F0A48: lui         $t7, 0x101
    ctx->r15 = S32(0X101 << 16);
    // 0x801F0A4C: lui         $t6, 0x101
    ctx->r14 = S32(0X101 << 16);
    // 0x801F0A50: addiu       $t6, $t6, 0x9F8
    ctx->r14 = ADD32(ctx->r14, 0X9F8);
    // 0x801F0A54: addiu       $t7, $t7, 0x998
    ctx->r15 = ADD32(ctx->r15, 0X998);
    // 0x801F0A58: addiu       $t8, $t8, 0x730
    ctx->r24 = ADD32(ctx->r24, 0X730);
    // 0x801F0A5C: lui         $s4, 0x7
    ctx->r20 = S32(0X7 << 16);
    // 0x801F0A60: lui         $s2, 0x8
    ctx->r18 = S32(0X8 << 16);
    // 0x801F0A64: lui         $s1, 0xF510
    ctx->r17 = S32(0XF510 << 16);
    // 0x801F0A68: lui         $ra, 0x73F
    ctx->r31 = S32(0X73F << 16);
    // 0x801F0A6C: lui         $t3, 0x708
    ctx->r11 = S32(0X708 << 16);
    // 0x801F0A70: ori         $t3, $t3, 0x200
    ctx->r11 = ctx->r11 | 0X200;
    // 0x801F0A74: ori         $ra, $ra, 0xF100
    ctx->r31 = ctx->r31 | 0XF100;
    // 0x801F0A78: ori         $s1, $s1, 0x1000
    ctx->r17 = ctx->r17 | 0X1000;
    // 0x801F0A7C: ori         $s2, $s2, 0x200
    ctx->r18 = ctx->r18 | 0X200;
    // 0x801F0A80: ori         $s4, $s4, 0xC07C
    ctx->r20 = ctx->r20 | 0XC07C;
    // 0x801F0A84: sw          $t8, 0x68($sp)
    MEM_W(0X68, ctx->r29) = ctx->r24;
    // 0x801F0A88: sw          $t7, 0x64($sp)
    MEM_W(0X64, ctx->r29) = ctx->r15;
    // 0x801F0A8C: sw          $t6, 0x60($sp)
    MEM_W(0X60, ctx->r29) = ctx->r14;
    // 0x801F0A90: addiu       $fp, $fp, 0x6C0
    ctx->r30 = ADD32(ctx->r30, 0X6C0);
    // 0x801F0A94: lui         $s3, 0xF200
    ctx->r19 = S32(0XF200 << 16);
    // 0x801F0A98: lui         $s0, 0xE700
    ctx->r16 = S32(0XE700 << 16);
    // 0x801F0A9C: lui         $t5, 0xF300
    ctx->r13 = S32(0XF300 << 16);
    // 0x801F0AA0: lui         $t4, 0xE600
    ctx->r12 = S32(0XE600 << 16);
    // 0x801F0AA4: lui         $t2, 0xF510
    ctx->r10 = S32(0XF510 << 16);
    // 0x801F0AA8: lui         $t1, 0xFD10
    ctx->r9 = S32(0XFD10 << 16);
    // 0x801F0AAC: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
L_801F0AB0:
    // 0x801F0AB0: bne         $a2, $at, L_801F0AD0
    if (ctx->r6 != ctx->r1) {
        // 0x801F0AB4: or          $v1, $v0, $zero
        ctx->r3 = ctx->r2 | 0;
            goto L_801F0AD0;
    }
    // 0x801F0AB4: or          $v1, $v0, $zero
    ctx->r3 = ctx->r2 | 0;
    // 0x801F0AB8: lui         $t9, 0x101
    ctx->r25 = S32(0X101 << 16);
    // 0x801F0ABC: addiu       $t9, $t9, 0x4490
    ctx->r25 = ADD32(ctx->r25, 0X4490);
    // 0x801F0AC0: sw          $t9, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r25;
    // 0x801F0AC4: addiu       $v0, $v0, 0x8
    ctx->r2 = ADD32(ctx->r2, 0X8);
    // 0x801F0AC8: b           L_801F0B38
    // 0x801F0ACC: sw          $s7, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r23;
        goto L_801F0B38;
    // 0x801F0ACC: sw          $s7, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r23;
L_801F0AD0:
    // 0x801F0AD0: bne         $s5, $zero, L_801F0AF4
    if (ctx->r21 != 0) {
        // 0x801F0AD4: or          $v1, $v0, $zero
        ctx->r3 = ctx->r2 | 0;
            goto L_801F0AF4;
    }
    // 0x801F0AD4: or          $v1, $v0, $zero
    ctx->r3 = ctx->r2 | 0;
    // 0x801F0AD8: or          $v1, $v0, $zero
    ctx->r3 = ctx->r2 | 0;
    // 0x801F0ADC: lui         $t8, 0x101
    ctx->r24 = S32(0X101 << 16);
    // 0x801F0AE0: addiu       $t8, $t8, 0x44A0
    ctx->r24 = ADD32(ctx->r24, 0X44A0);
    // 0x801F0AE4: sw          $t8, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r24;
    // 0x801F0AE8: sw          $s7, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r23;
    // 0x801F0AEC: b           L_801F0B38
    // 0x801F0AF0: addiu       $v0, $v0, 0x8
    ctx->r2 = ADD32(ctx->r2, 0X8);
        goto L_801F0B38;
    // 0x801F0AF0: addiu       $v0, $v0, 0x8
    ctx->r2 = ADD32(ctx->r2, 0X8);
L_801F0AF4:
    // 0x801F0AF4: addiu       $v0, $v0, 0x8
    ctx->r2 = ADD32(ctx->r2, 0X8);
    // 0x801F0AF8: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x801F0AFC: sw          $s0, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r16;
    // 0x801F0B00: sw          $zero, 0x4($v1)
    MEM_W(0X4, ctx->r3) = 0;
    // 0x801F0B04: addiu       $v0, $v0, 0x8
    ctx->r2 = ADD32(ctx->r2, 0X8);
    // 0x801F0B08: lui         $t7, 0xED02
    ctx->r15 = S32(0XED02 << 16);
    // 0x801F0B0C: addiu       $t7, $t7, 0x1E8
    ctx->r15 = ADD32(ctx->r15, 0X1E8);
    // 0x801F0B10: lui         $t6, 0x68
    ctx->r14 = S32(0X68 << 16);
    // 0x801F0B14: addiu       $t6, $t6, -0x3C6C
    ctx->r14 = ADD32(ctx->r14, -0X3C6C);
    // 0x801F0B18: or          $a1, $v0, $zero
    ctx->r5 = ctx->r2 | 0;
    // 0x801F0B1C: sw          $t7, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r15;
    // 0x801F0B20: sw          $t6, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r14;
    // 0x801F0B24: lui         $t9, 0x101
    ctx->r25 = S32(0X101 << 16);
    // 0x801F0B28: addiu       $t9, $t9, 0x44B0
    ctx->r25 = ADD32(ctx->r25, 0X44B0);
    // 0x801F0B2C: sw          $t9, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r25;
    // 0x801F0B30: sw          $s7, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r23;
    // 0x801F0B34: addiu       $v0, $v0, 0x8
    ctx->r2 = ADD32(ctx->r2, 0X8);
L_801F0B38:
    // 0x801F0B38: or          $v1, $v0, $zero
    ctx->r3 = ctx->r2 | 0;
    // 0x801F0B3C: sw          $t1, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r9;
    // 0x801F0B40: lw          $t8, 0x188($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X188);
    // 0x801F0B44: addiu       $v0, $v0, 0x8
    ctx->r2 = ADD32(ctx->r2, 0X8);
    // 0x801F0B48: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x801F0B4C: addiu       $v0, $v0, 0x8
    ctx->r2 = ADD32(ctx->r2, 0X8);
    // 0x801F0B50: sw          $t8, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r24;
    // 0x801F0B54: or          $a1, $v0, $zero
    ctx->r5 = ctx->r2 | 0;
    // 0x801F0B58: addiu       $v0, $v0, 0x8
    ctx->r2 = ADD32(ctx->r2, 0X8);
    // 0x801F0B5C: sw          $t3, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r11;
    // 0x801F0B60: sw          $t2, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r10;
    // 0x801F0B64: or          $a2, $v0, $zero
    ctx->r6 = ctx->r2 | 0;
    // 0x801F0B68: sw          $zero, 0x4($a1)
    MEM_W(0X4, ctx->r5) = 0;
    // 0x801F0B6C: sw          $t4, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r12;
    // 0x801F0B70: addiu       $v0, $v0, 0x8
    ctx->r2 = ADD32(ctx->r2, 0X8);
    // 0x801F0B74: or          $a3, $v0, $zero
    ctx->r7 = ctx->r2 | 0;
    // 0x801F0B78: sw          $ra, 0x4($a2)
    MEM_W(0X4, ctx->r6) = ctx->r31;
    // 0x801F0B7C: sw          $t5, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r13;
    // 0x801F0B80: addiu       $v0, $v0, 0x8
    ctx->r2 = ADD32(ctx->r2, 0X8);
    // 0x801F0B84: or          $v1, $v0, $zero
    ctx->r3 = ctx->r2 | 0;
    // 0x801F0B88: addiu       $v0, $v0, 0x8
    ctx->r2 = ADD32(ctx->r2, 0X8);
    // 0x801F0B8C: sw          $zero, 0x4($a3)
    MEM_W(0X4, ctx->r7) = 0;
    // 0x801F0B90: sw          $s0, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r16;
    // 0x801F0B94: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x801F0B98: addiu       $v0, $v0, 0x8
    ctx->r2 = ADD32(ctx->r2, 0X8);
    // 0x801F0B9C: sw          $s2, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r18;
    // 0x801F0BA0: sw          $s1, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r17;
    // 0x801F0BA4: or          $a1, $v0, $zero
    ctx->r5 = ctx->r2 | 0;
    // 0x801F0BA8: sw          $s4, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r20;
    // 0x801F0BAC: sw          $s3, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r19;
    // 0x801F0BB0: addiu       $v0, $v0, 0x8
    ctx->r2 = ADD32(ctx->r2, 0X8);
    // 0x801F0BB4: sw          $fp, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r30;
    // 0x801F0BB8: sw          $s6, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r22;
    // 0x801F0BBC: or          $a2, $v0, $zero
    ctx->r6 = ctx->r2 | 0;
    // 0x801F0BC0: sw          $t1, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r9;
    // 0x801F0BC4: lw          $t7, 0x184($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X184);
    // 0x801F0BC8: addiu       $v0, $v0, 0x8
    ctx->r2 = ADD32(ctx->r2, 0X8);
    // 0x801F0BCC: or          $t0, $v0, $zero
    ctx->r8 = ctx->r2 | 0;
    // 0x801F0BD0: addiu       $v0, $v0, 0x8
    ctx->r2 = ADD32(ctx->r2, 0X8);
    // 0x801F0BD4: sw          $t7, 0x4($a2)
    MEM_W(0X4, ctx->r6) = ctx->r15;
    // 0x801F0BD8: or          $v1, $v0, $zero
    ctx->r3 = ctx->r2 | 0;
    // 0x801F0BDC: sw          $t3, 0x4($t0)
    MEM_W(0X4, ctx->r8) = ctx->r11;
    // 0x801F0BE0: sw          $t2, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r10;
    // 0x801F0BE4: addiu       $v0, $v0, 0x8
    ctx->r2 = ADD32(ctx->r2, 0X8);
    // 0x801F0BE8: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x801F0BEC: sw          $zero, 0x4($v1)
    MEM_W(0X4, ctx->r3) = 0;
    // 0x801F0BF0: sw          $t4, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r12;
    // 0x801F0BF4: addiu       $v0, $v0, 0x8
    ctx->r2 = ADD32(ctx->r2, 0X8);
    // 0x801F0BF8: or          $a1, $v0, $zero
    ctx->r5 = ctx->r2 | 0;
    // 0x801F0BFC: addiu       $v0, $v0, 0x8
    ctx->r2 = ADD32(ctx->r2, 0X8);
    // 0x801F0C00: sw          $ra, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r31;
    // 0x801F0C04: sw          $t5, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r13;
    // 0x801F0C08: or          $a2, $v0, $zero
    ctx->r6 = ctx->r2 | 0;
    // 0x801F0C0C: addiu       $v0, $v0, 0x8
    ctx->r2 = ADD32(ctx->r2, 0X8);
    // 0x801F0C10: sw          $zero, 0x4($a1)
    MEM_W(0X4, ctx->r5) = 0;
    // 0x801F0C14: sw          $s0, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r16;
    // 0x801F0C18: or          $a3, $v0, $zero
    ctx->r7 = ctx->r2 | 0;
    // 0x801F0C1C: sw          $s2, 0x4($a2)
    MEM_W(0X4, ctx->r6) = ctx->r18;
    // 0x801F0C20: sw          $s1, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r17;
    // 0x801F0C24: addiu       $v0, $v0, 0x8
    ctx->r2 = ADD32(ctx->r2, 0X8);
    // 0x801F0C28: sw          $s4, 0x4($a3)
    MEM_W(0X4, ctx->r7) = ctx->r20;
    // 0x801F0C2C: sw          $s3, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r19;
    // 0x801F0C30: or          $v1, $v0, $zero
    ctx->r3 = ctx->r2 | 0;
    // 0x801F0C34: sw          $s6, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r22;
    // 0x801F0C38: lw          $t6, 0x68($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X68);
    // 0x801F0C3C: addiu       $v0, $v0, 0x8
    ctx->r2 = ADD32(ctx->r2, 0X8);
    // 0x801F0C40: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x801F0C44: sw          $t6, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r14;
    // 0x801F0C48: sw          $t1, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r9;
    // 0x801F0C4C: lw          $t9, 0x180($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X180);
    // 0x801F0C50: addiu       $v0, $v0, 0x8
    ctx->r2 = ADD32(ctx->r2, 0X8);
    // 0x801F0C54: or          $a1, $v0, $zero
    ctx->r5 = ctx->r2 | 0;
    // 0x801F0C58: addiu       $v0, $v0, 0x8
    ctx->r2 = ADD32(ctx->r2, 0X8);
    // 0x801F0C5C: sw          $t9, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r25;
    // 0x801F0C60: or          $a2, $v0, $zero
    ctx->r6 = ctx->r2 | 0;
    // 0x801F0C64: sw          $t3, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r11;
    // 0x801F0C68: sw          $t2, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r10;
    // 0x801F0C6C: addiu       $v0, $v0, 0x8
    ctx->r2 = ADD32(ctx->r2, 0X8);
    // 0x801F0C70: or          $t0, $v0, $zero
    ctx->r8 = ctx->r2 | 0;
    // 0x801F0C74: sw          $zero, 0x4($a2)
    MEM_W(0X4, ctx->r6) = 0;
    // 0x801F0C78: sw          $t4, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r12;
    // 0x801F0C7C: addiu       $v0, $v0, 0x8
    ctx->r2 = ADD32(ctx->r2, 0X8);
    // 0x801F0C80: or          $v1, $v0, $zero
    ctx->r3 = ctx->r2 | 0;
    // 0x801F0C84: addiu       $v0, $v0, 0x8
    ctx->r2 = ADD32(ctx->r2, 0X8);
    // 0x801F0C88: sw          $ra, 0x4($t0)
    MEM_W(0X4, ctx->r8) = ctx->r31;
    // 0x801F0C8C: sw          $t5, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r13;
    // 0x801F0C90: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x801F0C94: addiu       $v0, $v0, 0x8
    ctx->r2 = ADD32(ctx->r2, 0X8);
    // 0x801F0C98: sw          $zero, 0x4($v1)
    MEM_W(0X4, ctx->r3) = 0;
    // 0x801F0C9C: sw          $s0, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r16;
    // 0x801F0CA0: or          $a1, $v0, $zero
    ctx->r5 = ctx->r2 | 0;
    // 0x801F0CA4: sw          $s2, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r18;
    // 0x801F0CA8: sw          $s1, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r17;
    // 0x801F0CAC: addiu       $v0, $v0, 0x8
    ctx->r2 = ADD32(ctx->r2, 0X8);
    // 0x801F0CB0: sw          $s4, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r20;
    // 0x801F0CB4: sw          $s3, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r19;
    // 0x801F0CB8: or          $a2, $v0, $zero
    ctx->r6 = ctx->r2 | 0;
    // 0x801F0CBC: sw          $s6, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r22;
    // 0x801F0CC0: lw          $t8, 0x64($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X64);
    // 0x801F0CC4: addiu       $v0, $v0, 0x8
    ctx->r2 = ADD32(ctx->r2, 0X8);
    // 0x801F0CC8: or          $a3, $v0, $zero
    ctx->r7 = ctx->r2 | 0;
    // 0x801F0CCC: sw          $t8, 0x4($a2)
    MEM_W(0X4, ctx->r6) = ctx->r24;
    // 0x801F0CD0: sw          $t1, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r9;
    // 0x801F0CD4: lw          $t7, 0x17C($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X17C);
    // 0x801F0CD8: addiu       $v0, $v0, 0x8
    ctx->r2 = ADD32(ctx->r2, 0X8);
    // 0x801F0CDC: or          $v1, $v0, $zero
    ctx->r3 = ctx->r2 | 0;
    // 0x801F0CE0: addiu       $v0, $v0, 0x8
    ctx->r2 = ADD32(ctx->r2, 0X8);
    // 0x801F0CE4: sw          $t7, 0x4($a3)
    MEM_W(0X4, ctx->r7) = ctx->r15;
    // 0x801F0CE8: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x801F0CEC: addiu       $v0, $v0, 0x8
    ctx->r2 = ADD32(ctx->r2, 0X8);
    // 0x801F0CF0: sw          $t3, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r11;
    // 0x801F0CF4: sw          $t2, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r10;
    // 0x801F0CF8: or          $a1, $v0, $zero
    ctx->r5 = ctx->r2 | 0;
    // 0x801F0CFC: sw          $zero, 0x4($a0)
    MEM_W(0X4, ctx->r4) = 0;
    // 0x801F0D00: sw          $t4, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r12;
    // 0x801F0D04: addiu       $v0, $v0, 0x8
    ctx->r2 = ADD32(ctx->r2, 0X8);
    // 0x801F0D08: or          $a2, $v0, $zero
    ctx->r6 = ctx->r2 | 0;
    // 0x801F0D0C: sw          $ra, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r31;
    // 0x801F0D10: sw          $t5, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r13;
    // 0x801F0D14: addiu       $v0, $v0, 0x8
    ctx->r2 = ADD32(ctx->r2, 0X8);
    // 0x801F0D18: or          $v1, $v0, $zero
    ctx->r3 = ctx->r2 | 0;
    // 0x801F0D1C: addiu       $v0, $v0, 0x8
    ctx->r2 = ADD32(ctx->r2, 0X8);
    // 0x801F0D20: sw          $zero, 0x4($a2)
    MEM_W(0X4, ctx->r6) = 0;
    // 0x801F0D24: sw          $s0, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r16;
    // 0x801F0D28: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x801F0D2C: sw          $s2, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r18;
    // 0x801F0D30: sw          $s1, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r17;
    // 0x801F0D34: addiu       $v0, $v0, 0x8
    ctx->r2 = ADD32(ctx->r2, 0X8);
    // 0x801F0D38: sw          $s4, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r20;
    // 0x801F0D3C: sw          $s3, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r19;
    // 0x801F0D40: or          $a1, $v0, $zero
    ctx->r5 = ctx->r2 | 0;
    // 0x801F0D44: sw          $s6, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r22;
    // 0x801F0D48: lw          $t6, 0x60($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X60);
    // 0x801F0D4C: lui         $a2, 0x800E
    ctx->r6 = S32(0X800E << 16);
    // 0x801F0D50: addiu       $s5, $s5, 0x1
    ctx->r21 = ADD32(ctx->r21, 0X1);
    // 0x801F0D54: sw          $t6, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r14;
    // 0x801F0D58: lw          $a2, -0x54D8($a2)
    ctx->r6 = MEM_W(ctx->r6, -0X54D8);
    // 0x801F0D5C: addiu       $v0, $v0, 0x8
    ctx->r2 = ADD32(ctx->r2, 0X8);
    // 0x801F0D60: slt         $at, $s5, $a2
    ctx->r1 = SIGNED(ctx->r21) < SIGNED(ctx->r6) ? 1 : 0;
    // 0x801F0D64: bnel        $at, $zero, L_801F0AB0
    if (ctx->r1 != 0) {
        // 0x801F0D68: addiu       $at, $zero, 0x1
        ctx->r1 = ADD32(0, 0X1);
            goto L_801F0AB0;
    }
    goto skip_2;
    // 0x801F0D68: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    skip_2:
L_801F0D6C:
    // 0x801F0D6C: lui         $s7, 0x380
    ctx->r23 = S32(0X380 << 16);
    // 0x801F0D70: or          $v1, $v0, $zero
    ctx->r3 = ctx->r2 | 0;
    // 0x801F0D74: lui         $t9, 0x101
    ctx->r25 = S32(0X101 << 16);
    // 0x801F0D78: ori         $s7, $s7, 0x10
    ctx->r23 = ctx->r23 | 0X10;
    // 0x801F0D7C: addiu       $t9, $t9, 0x4450
    ctx->r25 = ADD32(ctx->r25, 0X4450);
    // 0x801F0D80: sw          $t9, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r25;
    // 0x801F0D84: sw          $s7, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r23;
    // 0x801F0D88: lui         $t8, 0x800E
    ctx->r24 = S32(0X800E << 16);
    // 0x801F0D8C: lw          $t8, -0x54D8($t8)
    ctx->r24 = MEM_W(ctx->r24, -0X54D8);
    // 0x801F0D90: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x801F0D94: lui         $s0, 0xE700
    ctx->r16 = S32(0XE700 << 16);
    // 0x801F0D98: bne         $t8, $at, L_801F0DD0
    if (ctx->r24 != ctx->r1) {
        // 0x801F0D9C: addiu       $v0, $v0, 0x8
        ctx->r2 = ADD32(ctx->r2, 0X8);
            goto L_801F0DD0;
    }
    // 0x801F0D9C: addiu       $v0, $v0, 0x8
    ctx->r2 = ADD32(ctx->r2, 0X8);
    // 0x801F0DA0: or          $v1, $v0, $zero
    ctx->r3 = ctx->r2 | 0;
    // 0x801F0DA4: addiu       $v0, $v0, 0x8
    ctx->r2 = ADD32(ctx->r2, 0X8);
    // 0x801F0DA8: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x801F0DAC: sw          $s0, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r16;
    // 0x801F0DB0: sw          $zero, 0x4($v1)
    MEM_W(0X4, ctx->r3) = 0;
    // 0x801F0DB4: lui         $t7, 0xED02
    ctx->r15 = S32(0XED02 << 16);
    // 0x801F0DB8: addiu       $t7, $t7, 0x30
    ctx->r15 = ADD32(ctx->r15, 0X30);
    // 0x801F0DBC: lui         $t6, 0x68
    ctx->r14 = S32(0X68 << 16);
    // 0x801F0DC0: addiu       $t6, $t6, -0x3C6C
    ctx->r14 = ADD32(ctx->r14, -0X3C6C);
    // 0x801F0DC4: sw          $t7, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r15;
    // 0x801F0DC8: sw          $t6, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r14;
    // 0x801F0DCC: addiu       $v0, $v0, 0x8
    ctx->r2 = ADD32(ctx->r2, 0X8);
L_801F0DD0:
    // 0x801F0DD0: or          $v1, $v0, $zero
    ctx->r3 = ctx->r2 | 0;
    // 0x801F0DD4: lui         $t9, 0x103
    ctx->r25 = S32(0X103 << 16);
    // 0x801F0DD8: lui         $t8, 0x301
    ctx->r24 = S32(0X301 << 16);
    // 0x801F0DDC: addiu       $t8, $t8, -0x1FF8
    ctx->r24 = ADD32(ctx->r24, -0X1FF8);
    // 0x801F0DE0: ori         $t9, $t9, 0x40
    ctx->r25 = ctx->r25 | 0X40;
    // 0x801F0DE4: sw          $t9, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r25;
    // 0x801F0DE8: sw          $t8, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r24;
    // 0x801F0DEC: addiu       $a0, $v0, 0x8
    ctx->r4 = ADD32(ctx->r2, 0X8);
    // 0x801F0DF0: lui         $t7, 0x101
    ctx->r15 = S32(0X101 << 16);
    // 0x801F0DF4: lui         $t6, 0x301
    ctx->r14 = S32(0X301 << 16);
    // 0x801F0DF8: addiu       $t6, $t6, -0x1F78
    ctx->r14 = ADD32(ctx->r14, -0X1F78);
    // 0x801F0DFC: ori         $t7, $t7, 0x40
    ctx->r15 = ctx->r15 | 0X40;
    // 0x801F0E00: sw          $t7, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r15;
    // 0x801F0E04: sw          $t6, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r14;
    // 0x801F0E08: addiu       $a1, $a0, 0x8
    ctx->r5 = ADD32(ctx->r4, 0X8);
    // 0x801F0E0C: lui         $t9, 0xB400
    ctx->r25 = S32(0XB400 << 16);
    // 0x801F0E10: sw          $t9, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r25;
    // 0x801F0E14: lui         $t8, 0x8022
    ctx->r24 = S32(0X8022 << 16);
    // 0x801F0E18: lw          $t8, 0x3930($t8)
    ctx->r24 = MEM_W(ctx->r24, 0X3930);
    // 0x801F0E1C: lui         $t6, 0x8022
    ctx->r14 = S32(0X8022 << 16);
    // 0x801F0E20: addiu       $v0, $a1, 0x8
    ctx->r2 = ADD32(ctx->r5, 0X8);
    // 0x801F0E24: sll         $t7, $t8, 4
    ctx->r15 = S32(ctx->r24 << 4);
    // 0x801F0E28: addu        $t7, $t7, $t8
    ctx->r15 = ADD32(ctx->r15, ctx->r24);
    // 0x801F0E2C: sll         $t7, $t7, 2
    ctx->r15 = S32(ctx->r15 << 2);
    // 0x801F0E30: subu        $t7, $t7, $t8
    ctx->r15 = SUB32(ctx->r15, ctx->r24);
    // 0x801F0E34: sll         $t7, $t7, 2
    ctx->r15 = S32(ctx->r15 << 2);
    // 0x801F0E38: addu        $t6, $t6, $t7
    ctx->r14 = ADD32(ctx->r14, ctx->r15);
    // 0x801F0E3C: lhu         $t6, 0x7D64($t6)
    ctx->r14 = MEM_HU(ctx->r14, 0X7D64);
    // 0x801F0E40: sw          $t6, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r14;
    // 0x801F0E44: lw          $t9, 0x198($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X198);
    // 0x801F0E48: sw          $v0, 0x0($t9)
    MEM_W(0X0, ctx->r25) = ctx->r2;
    // 0x801F0E4C: lw          $ra, 0x5C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X5C);
    // 0x801F0E50: lw          $fp, 0x58($sp)
    ctx->r30 = MEM_W(ctx->r29, 0X58);
    // 0x801F0E54: lw          $s7, 0x54($sp)
    ctx->r23 = MEM_W(ctx->r29, 0X54);
    // 0x801F0E58: lw          $s6, 0x50($sp)
    ctx->r22 = MEM_W(ctx->r29, 0X50);
    // 0x801F0E5C: lw          $s5, 0x4C($sp)
    ctx->r21 = MEM_W(ctx->r29, 0X4C);
    // 0x801F0E60: lw          $s4, 0x48($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X48);
    // 0x801F0E64: lw          $s3, 0x44($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X44);
    // 0x801F0E68: lw          $s2, 0x40($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X40);
    // 0x801F0E6C: lw          $s1, 0x3C($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X3C);
    // 0x801F0E70: lw          $s0, 0x38($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X38);
    // 0x801F0E74: jr          $ra
    // 0x801F0E78: addiu       $sp, $sp, 0x198
    ctx->r29 = ADD32(ctx->r29, 0X198);
    return;
    // 0x801F0E78: addiu       $sp, $sp, 0x198
    ctx->r29 = ADD32(ctx->r29, 0X198);
;}
