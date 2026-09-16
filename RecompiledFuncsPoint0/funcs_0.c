#include "recomp.h"
#include "funcs.h"

RECOMP_FUNC void recomp_entrypoint(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x80046800: lui         $t0, 0x800F
    ctx->r8 = S32(0X800F << 16);
    // 0x80046804: lui         $t1, 0xE
    ctx->r9 = S32(0XE << 16);
    // 0x80046808: addiu       $t0, $t0, -0x1230
    ctx->r8 = ADD32(ctx->r8, -0X1230);
    // 0x8004680C: ori         $t1, $t1, 0xC1D0
    ctx->r9 = ctx->r9 | 0XC1D0;
L_80046810:
    // 0x80046810: addi        $t1, $t1, -0x8
    ctx->r9 = ADD32(ctx->r9, -0X8);
    // 0x80046814: sw          $zero, 0x0($t0)
    MEM_W(0X0, ctx->r8) = 0;
    // 0x80046818: sw          $zero, 0x4($t0)
    MEM_W(0X4, ctx->r8) = 0;
    // 0x8004681C: bne         $t1, $zero, L_80046810
    if (ctx->r9 != 0) {
        // 0x80046820: addi        $t0, $t0, 0x8
        ctx->r8 = ADD32(ctx->r8, 0X8);
            goto L_80046810;
    }
    // 0x80046820: addi        $t0, $t0, 0x8
    ctx->r8 = ADD32(ctx->r8, 0X8);
    // 0x80046824: lui         $t2, 0x8004
    ctx->r10 = S32(0X8004 << 16);
    // 0x80046828: lui         $sp, 0x8015
    ctx->r29 = S32(0X8015 << 16);
    // 0x8004682C: addiu       $t2, $t2, 0x7AA4
    ctx->r10 = ADD32(ctx->r10, 0X7AA4);
    // 0x80046830: jr          $t2
    // 0x80046834: addiu       $sp, $sp, 0x1BE0
    ctx->r29 = ADD32(ctx->r29, 0X1BE0);
    LOOKUP_FUNC(ctx->r10)(rdram, ctx);
    return;
    // 0x80046834: addiu       $sp, $sp, 0x1BE0
    ctx->r29 = ADD32(ctx->r29, 0X1BE0);
    // 0x80046838: nop

    // 0x8004683C: nop

    // 0x80046840: nop

    // 0x80046844: nop

    // 0x80046848: nop

    // 0x8004684C: nop

;}
RECOMP_FUNC void func_80046850(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x80046850: lui         $v1, 0x8015
    ctx->r3 = S32(0X8015 << 16);
    // 0x80046854: lui         $a0, 0x8015
    ctx->r4 = S32(0X8015 << 16);
    // 0x80046858: lui         $a1, 0x8015
    ctx->r5 = S32(0X8015 << 16);
    // 0x8004685C: addiu       $a1, $a1, 0x1950
    ctx->r5 = ADD32(ctx->r5, 0X1950);
    // 0x80046860: addiu       $a0, $a0, 0x1948
    ctx->r4 = ADD32(ctx->r4, 0X1948);
    // 0x80046864: addiu       $v1, $v1, 0x194C
    ctx->r3 = ADD32(ctx->r3, 0X194C);
    // 0x80046868: lw          $v0, 0x0($v1)
    ctx->r2 = MEM_W(ctx->r3, 0X0);
    // 0x8004686C: lw          $t6, 0x0($a0)
    ctx->r14 = MEM_W(ctx->r4, 0X0);
    // 0x80046870: lw          $t7, 0x0($a1)
    ctx->r15 = MEM_W(ctx->r5, 0X0);
    // 0x80046874: lui         $t8, 0x800E
    ctx->r24 = S32(0X800E << 16);
    // 0x80046878: sw          $v0, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r2;
    // 0x8004687C: sw          $t6, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r14;
    // 0x80046880: sw          $t7, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r15;
    // 0x80046884: lw          $t8, -0x54E4($t8)
    ctx->r24 = MEM_W(ctx->r24, -0X54E4);
    // 0x80046888: lui         $v0, 0x800D
    ctx->r2 = S32(0X800D << 16);
    // 0x8004688C: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x80046890: bne         $t8, $at, L_800468A4
    if (ctx->r24 != ctx->r1) {
        // 0x80046894: addiu       $v0, $v0, 0x45D8
        ctx->r2 = ADD32(ctx->r2, 0X45D8);
            goto L_800468A4;
    }
    // 0x80046894: addiu       $v0, $v0, 0x45D8
    ctx->r2 = ADD32(ctx->r2, 0X45D8);
    // 0x80046898: lw          $t9, 0x0($v0)
    ctx->r25 = MEM_W(ctx->r2, 0X0);
    // 0x8004689C: xori        $t0, $t9, 0x1
    ctx->r8 = ctx->r25 ^ 0X1;
    // 0x800468A0: sw          $t0, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r8;
L_800468A4:
    // 0x800468A4: jr          $ra
    // 0x800468A8: nop

    return;
    // 0x800468A8: nop

;}
RECOMP_FUNC void func_800468AC(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800468AC: lui         $v1, 0x8015
    ctx->r3 = S32(0X8015 << 16);
    // 0x800468B0: lui         $a0, 0x8015
    ctx->r4 = S32(0X8015 << 16);
    // 0x800468B4: lui         $a1, 0x8015
    ctx->r5 = S32(0X8015 << 16);
    // 0x800468B8: addiu       $a1, $a1, 0x194C
    ctx->r5 = ADD32(ctx->r5, 0X194C);
    // 0x800468BC: addiu       $a0, $a0, 0x1948
    ctx->r4 = ADD32(ctx->r4, 0X1948);
    // 0x800468C0: addiu       $v1, $v1, 0x1950
    ctx->r3 = ADD32(ctx->r3, 0X1950);
    // 0x800468C4: lw          $v0, 0x0($v1)
    ctx->r2 = MEM_W(ctx->r3, 0X0);
    // 0x800468C8: lw          $t6, 0x0($a0)
    ctx->r14 = MEM_W(ctx->r4, 0X0);
    // 0x800468CC: lw          $t7, 0x0($a1)
    ctx->r15 = MEM_W(ctx->r5, 0X0);
    // 0x800468D0: sw          $v0, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r2;
    // 0x800468D4: sw          $t6, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r14;
    // 0x800468D8: jr          $ra
    // 0x800468DC: sw          $t7, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r15;
    return;
    // 0x800468DC: sw          $t7, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r15;
;}
RECOMP_FUNC void func_800468E0(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800468E0: addiu       $sp, $sp, -0x38
    ctx->r29 = ADD32(ctx->r29, -0X38);
    // 0x800468E4: sw          $s1, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r17;
    // 0x800468E8: lui         $s1, 0x8015
    ctx->r17 = S32(0X8015 << 16);
    // 0x800468EC: addiu       $s1, $s1, 0x1944
    ctx->r17 = ADD32(ctx->r17, 0X1944);
    // 0x800468F0: sw          $s0, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r16;
    // 0x800468F4: lw          $s0, 0x0($s1)
    ctx->r16 = MEM_W(ctx->r17, 0X0);
    // 0x800468F8: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x800468FC: lui         $t7, 0xBC00
    ctx->r15 = S32(0XBC00 << 16);
    // 0x80046900: addiu       $t6, $s0, 0x8
    ctx->r14 = ADD32(ctx->r16, 0X8);
    // 0x80046904: sw          $t6, 0x0($s1)
    MEM_W(0X0, ctx->r17) = ctx->r14;
    // 0x80046908: ori         $t7, $t7, 0x6
    ctx->r15 = ctx->r15 | 0X6;
    // 0x8004690C: sw          $t7, 0x0($s0)
    MEM_W(0X0, ctx->r16) = ctx->r15;
    // 0x80046910: sw          $zero, 0x4($s0)
    MEM_W(0X4, ctx->r16) = 0;
    // 0x80046914: lw          $s0, 0x0($s1)
    ctx->r16 = MEM_W(ctx->r17, 0X0);
    // 0x80046918: lui         $t9, 0xBC00
    ctx->r25 = S32(0XBC00 << 16);
    // 0x8004691C: ori         $t9, $t9, 0x406
    ctx->r25 = ctx->r25 | 0X406;
    // 0x80046920: addiu       $t8, $s0, 0x8
    ctx->r24 = ADD32(ctx->r16, 0X8);
    // 0x80046924: sw          $t8, 0x0($s1)
    MEM_W(0X0, ctx->r17) = ctx->r24;
    // 0x80046928: lui         $t0, 0x8015
    ctx->r8 = S32(0X8015 << 16);
    // 0x8004692C: sw          $t9, 0x0($s0)
    MEM_W(0X0, ctx->r16) = ctx->r25;
    // 0x80046930: lw          $t0, 0x1984($t0)
    ctx->r8 = MEM_W(ctx->r8, 0X1984);
    // 0x80046934: lui         $t2, 0xBC00
    ctx->r10 = S32(0XBC00 << 16);
    // 0x80046938: ori         $t2, $t2, 0x806
    ctx->r10 = ctx->r10 | 0X806;
    // 0x8004693C: sw          $t0, 0x4($s0)
    MEM_W(0X4, ctx->r16) = ctx->r8;
    // 0x80046940: lw          $s0, 0x0($s1)
    ctx->r16 = MEM_W(ctx->r17, 0X0);
    // 0x80046944: lui         $a0, 0x8012
    ctx->r4 = S32(0X8012 << 16);
    // 0x80046948: addiu       $a0, $a0, -0x1220
    ctx->r4 = ADD32(ctx->r4, -0X1220);
    // 0x8004694C: addiu       $t1, $s0, 0x8
    ctx->r9 = ADD32(ctx->r16, 0X8);
    // 0x80046950: sw          $t1, 0x0($s1)
    MEM_W(0X0, ctx->r17) = ctx->r9;
    // 0x80046954: sw          $t2, 0x0($s0)
    MEM_W(0X0, ctx->r16) = ctx->r10;
    // 0x80046958: jal         0x800C5720
    // 0x8004695C: sw          $s0, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r16;
    osVirtualToPhysical_recomp(rdram, ctx);
        goto after_0;
    // 0x8004695C: sw          $s0, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r16;
    after_0:
    // 0x80046960: lw          $a1, 0x2C($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X2C);
    // 0x80046964: lui         $t4, 0xBC00
    ctx->r12 = S32(0XBC00 << 16);
    // 0x80046968: ori         $t4, $t4, 0xC06
    ctx->r12 = ctx->r12 | 0XC06;
    // 0x8004696C: sw          $v0, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r2;
    // 0x80046970: lw          $s0, 0x0($s1)
    ctx->r16 = MEM_W(ctx->r17, 0X0);
    // 0x80046974: lui         $a0, 0x8015
    ctx->r4 = S32(0X8015 << 16);
    // 0x80046978: addiu       $t3, $s0, 0x8
    ctx->r11 = ADD32(ctx->r16, 0X8);
    // 0x8004697C: sw          $t3, 0x0($s1)
    MEM_W(0X0, ctx->r17) = ctx->r11;
    // 0x80046980: sw          $t4, 0x0($s0)
    MEM_W(0X0, ctx->r16) = ctx->r12;
    // 0x80046984: lw          $a0, 0x18B8($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X18B8);
    // 0x80046988: jal         0x800C5720
    // 0x8004698C: sw          $s0, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r16;
    osVirtualToPhysical_recomp(rdram, ctx);
        goto after_1;
    // 0x8004698C: sw          $s0, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r16;
    after_1:
    // 0x80046990: lw          $v1, 0x28($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X28);
    // 0x80046994: lui         $t6, 0xBC00
    ctx->r14 = S32(0XBC00 << 16);
    // 0x80046998: ori         $t6, $t6, 0x1C06
    ctx->r14 = ctx->r14 | 0X1C06;
    // 0x8004699C: sw          $v0, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r2;
    // 0x800469A0: lw          $s0, 0x0($s1)
    ctx->r16 = MEM_W(ctx->r17, 0X0);
    // 0x800469A4: lui         $a0, 0x801D
    ctx->r4 = S32(0X801D << 16);
    // 0x800469A8: addiu       $t5, $s0, 0x8
    ctx->r13 = ADD32(ctx->r16, 0X8);
    // 0x800469AC: sw          $t5, 0x0($s1)
    MEM_W(0X0, ctx->r17) = ctx->r13;
    // 0x800469B0: sw          $t6, 0x0($s0)
    MEM_W(0X0, ctx->r16) = ctx->r14;
    // 0x800469B4: lw          $a0, -0x1A08($a0)
    ctx->r4 = MEM_W(ctx->r4, -0X1A08);
    // 0x800469B8: jal         0x800C5720
    // 0x800469BC: sw          $s0, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r16;
    osVirtualToPhysical_recomp(rdram, ctx);
        goto after_2;
    // 0x800469BC: sw          $s0, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r16;
    after_2:
    // 0x800469C0: lw          $a2, 0x24($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X24);
    // 0x800469C4: lui         $t8, 0xBC00
    ctx->r24 = S32(0XBC00 << 16);
    // 0x800469C8: ori         $t8, $t8, 0x2006
    ctx->r24 = ctx->r24 | 0X2006;
    // 0x800469CC: sw          $v0, 0x4($a2)
    MEM_W(0X4, ctx->r6) = ctx->r2;
    // 0x800469D0: lw          $s0, 0x0($s1)
    ctx->r16 = MEM_W(ctx->r17, 0X0);
    // 0x800469D4: lui         $t9, 0x800D
    ctx->r25 = S32(0X800D << 16);
    // 0x800469D8: lui         $t1, 0xBC00
    ctx->r9 = S32(0XBC00 << 16);
    // 0x800469DC: addiu       $t7, $s0, 0x8
    ctx->r15 = ADD32(ctx->r16, 0X8);
    // 0x800469E0: sw          $t7, 0x0($s1)
    MEM_W(0X0, ctx->r17) = ctx->r15;
    // 0x800469E4: sw          $t8, 0x0($s0)
    MEM_W(0X0, ctx->r16) = ctx->r24;
    // 0x800469E8: lw          $t9, 0x45F0($t9)
    ctx->r25 = MEM_W(ctx->r25, 0X45F0);
    // 0x800469EC: ori         $t1, $t1, 0x3406
    ctx->r9 = ctx->r9 | 0X3406;
    // 0x800469F0: lui         $t2, 0x800D
    ctx->r10 = S32(0X800D << 16);
    // 0x800469F4: sw          $t9, 0x4($s0)
    MEM_W(0X4, ctx->r16) = ctx->r25;
    // 0x800469F8: lw          $s0, 0x0($s1)
    ctx->r16 = MEM_W(ctx->r17, 0X0);
    // 0x800469FC: lui         $t4, 0xBC00
    ctx->r12 = S32(0XBC00 << 16);
    // 0x80046A00: ori         $t4, $t4, 0x3806
    ctx->r12 = ctx->r12 | 0X3806;
    // 0x80046A04: addiu       $t0, $s0, 0x8
    ctx->r8 = ADD32(ctx->r16, 0X8);
    // 0x80046A08: sw          $t0, 0x0($s1)
    MEM_W(0X0, ctx->r17) = ctx->r8;
    // 0x80046A0C: sw          $t1, 0x0($s0)
    MEM_W(0X0, ctx->r16) = ctx->r9;
    // 0x80046A10: lw          $t2, 0x45E4($t2)
    ctx->r10 = MEM_W(ctx->r10, 0X45E4);
    // 0x80046A14: lui         $t5, 0x800D
    ctx->r13 = S32(0X800D << 16);
    // 0x80046A18: lui         $t6, 0x800E
    ctx->r14 = S32(0X800E << 16);
    // 0x80046A1C: sw          $t2, 0x4($s0)
    MEM_W(0X4, ctx->r16) = ctx->r10;
    // 0x80046A20: lw          $s0, 0x0($s1)
    ctx->r16 = MEM_W(ctx->r17, 0X0);
    // 0x80046A24: addiu       $a3, $zero, 0x2
    ctx->r7 = ADD32(0, 0X2);
    // 0x80046A28: lui         $t8, 0x600
    ctx->r24 = S32(0X600 << 16);
    // 0x80046A2C: addiu       $t3, $s0, 0x8
    ctx->r11 = ADD32(ctx->r16, 0X8);
    // 0x80046A30: sw          $t3, 0x0($s1)
    MEM_W(0X0, ctx->r17) = ctx->r11;
    // 0x80046A34: sw          $t4, 0x0($s0)
    MEM_W(0X0, ctx->r16) = ctx->r12;
    // 0x80046A38: lw          $t5, 0x45E8($t5)
    ctx->r13 = MEM_W(ctx->r13, 0X45E8);
    // 0x80046A3C: lui         $t1, 0x600
    ctx->r9 = S32(0X600 << 16);
    // 0x80046A40: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x80046A44: sw          $t5, 0x4($s0)
    MEM_W(0X4, ctx->r16) = ctx->r13;
    // 0x80046A48: lw          $t6, -0x54D8($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X54D8);
    // 0x80046A4C: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x80046A50: bnel        $a3, $t6, L_80046A7C
    if (ctx->r7 != ctx->r14) {
        // 0x80046A54: lw          $s0, 0x0($s1)
        ctx->r16 = MEM_W(ctx->r17, 0X0);
            goto L_80046A7C;
    }
    goto skip_0;
    // 0x80046A54: lw          $s0, 0x0($s1)
    ctx->r16 = MEM_W(ctx->r17, 0X0);
    skip_0:
    // 0x80046A58: lw          $s0, 0x0($s1)
    ctx->r16 = MEM_W(ctx->r17, 0X0);
    // 0x80046A5C: lui         $t9, 0x100
    ctx->r25 = S32(0X100 << 16);
    // 0x80046A60: addiu       $t9, $t9, 0x98
    ctx->r25 = ADD32(ctx->r25, 0X98);
    // 0x80046A64: addiu       $t7, $s0, 0x8
    ctx->r15 = ADD32(ctx->r16, 0X8);
    // 0x80046A68: sw          $t7, 0x0($s1)
    MEM_W(0X0, ctx->r17) = ctx->r15;
    // 0x80046A6C: sw          $t9, 0x4($s0)
    MEM_W(0X4, ctx->r16) = ctx->r25;
    // 0x80046A70: b           L_80046A94
    // 0x80046A74: sw          $t8, 0x0($s0)
    MEM_W(0X0, ctx->r16) = ctx->r24;
        goto L_80046A94;
    // 0x80046A74: sw          $t8, 0x0($s0)
    MEM_W(0X0, ctx->r16) = ctx->r24;
    // 0x80046A78: lw          $s0, 0x0($s1)
    ctx->r16 = MEM_W(ctx->r17, 0X0);
L_80046A7C:
    // 0x80046A7C: lui         $t2, 0x100
    ctx->r10 = S32(0X100 << 16);
    // 0x80046A80: addiu       $t2, $t2, 0x0
    ctx->r10 = ADD32(ctx->r10, 0X0);
    // 0x80046A84: addiu       $t0, $s0, 0x8
    ctx->r8 = ADD32(ctx->r16, 0X8);
    // 0x80046A88: sw          $t0, 0x0($s1)
    MEM_W(0X0, ctx->r17) = ctx->r8;
    // 0x80046A8C: sw          $t2, 0x4($s0)
    MEM_W(0X4, ctx->r16) = ctx->r10;
    // 0x80046A90: sw          $t1, 0x0($s0)
    MEM_W(0X0, ctx->r16) = ctx->r9;
L_80046A94:
    // 0x80046A94: lw          $v0, -0x54E4($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X54E4);
    // 0x80046A98: beql        $v0, $zero, L_80046AC4
    if (ctx->r2 == 0) {
        // 0x80046A9C: lw          $s0, 0x0($s1)
        ctx->r16 = MEM_W(ctx->r17, 0X0);
            goto L_80046AC4;
    }
    goto skip_1;
    // 0x80046A9C: lw          $s0, 0x0($s1)
    ctx->r16 = MEM_W(ctx->r17, 0X0);
    skip_1:
    // 0x80046AA0: beql        $v0, $at, L_80046B20
    if (ctx->r2 == ctx->r1) {
        // 0x80046AA4: lw          $s0, 0x0($s1)
        ctx->r16 = MEM_W(ctx->r17, 0X0);
            goto L_80046B20;
    }
    goto skip_2;
    // 0x80046AA4: lw          $s0, 0x0($s1)
    ctx->r16 = MEM_W(ctx->r17, 0X0);
    skip_2:
    // 0x80046AA8: beq         $v0, $a3, L_80046B1C
    if (ctx->r2 == ctx->r7) {
        // 0x80046AAC: addiu       $at, $zero, 0x3
        ctx->r1 = ADD32(0, 0X3);
            goto L_80046B1C;
    }
    // 0x80046AAC: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x80046AB0: beql        $v0, $at, L_80046B90
    if (ctx->r2 == ctx->r1) {
        // 0x80046AB4: lw          $s0, 0x0($s1)
        ctx->r16 = MEM_W(ctx->r17, 0X0);
            goto L_80046B90;
    }
    goto skip_3;
    // 0x80046AB4: lw          $s0, 0x0($s1)
    ctx->r16 = MEM_W(ctx->r17, 0X0);
    skip_3:
    // 0x80046AB8: b           L_80046BE4
    // 0x80046ABC: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
        goto L_80046BE4;
    // 0x80046ABC: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    // 0x80046AC0: lw          $s0, 0x0($s1)
    ctx->r16 = MEM_W(ctx->r17, 0X0);
L_80046AC4:
    // 0x80046AC4: lui         $t4, 0xE700
    ctx->r12 = S32(0XE700 << 16);
    // 0x80046AC8: lui         $t6, 0xFF10
    ctx->r14 = S32(0XFF10 << 16);
    // 0x80046ACC: addiu       $t3, $s0, 0x8
    ctx->r11 = ADD32(ctx->r16, 0X8);
    // 0x80046AD0: sw          $t3, 0x0($s1)
    MEM_W(0X0, ctx->r17) = ctx->r11;
    // 0x80046AD4: sw          $zero, 0x4($s0)
    MEM_W(0X4, ctx->r16) = 0;
    // 0x80046AD8: sw          $t4, 0x0($s0)
    MEM_W(0X0, ctx->r16) = ctx->r12;
    // 0x80046ADC: lw          $s0, 0x0($s1)
    ctx->r16 = MEM_W(ctx->r17, 0X0);
    // 0x80046AE0: ori         $t6, $t6, 0x1A7
    ctx->r14 = ctx->r14 | 0X1A7;
    // 0x80046AE4: lui         $t7, 0x8015
    ctx->r15 = S32(0X8015 << 16);
    // 0x80046AE8: addiu       $t5, $s0, 0x8
    ctx->r13 = ADD32(ctx->r16, 0X8);
    // 0x80046AEC: sw          $t5, 0x0($s1)
    MEM_W(0X0, ctx->r17) = ctx->r13;
    // 0x80046AF0: sw          $t6, 0x0($s0)
    MEM_W(0X0, ctx->r16) = ctx->r14;
    // 0x80046AF4: lw          $t7, 0x1948($t7)
    ctx->r15 = MEM_W(ctx->r15, 0X1948);
    // 0x80046AF8: lui         $a2, 0x8015
    ctx->r6 = S32(0X8015 << 16);
    // 0x80046AFC: addiu       $a2, $a2, 0x42C0
    ctx->r6 = ADD32(ctx->r6, 0X42C0);
    // 0x80046B00: sll         $t8, $t7, 2
    ctx->r24 = S32(ctx->r15 << 2);
    // 0x80046B04: addu        $t9, $a2, $t8
    ctx->r25 = ADD32(ctx->r6, ctx->r24);
    // 0x80046B08: lw          $t0, 0x0($t9)
    ctx->r8 = MEM_W(ctx->r25, 0X0);
    // 0x80046B0C: lui         $a1, 0x8000
    ctx->r5 = S32(0X8000 << 16);
    // 0x80046B10: addu        $t1, $t0, $a1
    ctx->r9 = ADD32(ctx->r8, ctx->r5);
    // 0x80046B14: b           L_80046BE0
    // 0x80046B18: sw          $t1, 0x4($s0)
    MEM_W(0X4, ctx->r16) = ctx->r9;
        goto L_80046BE0;
    // 0x80046B18: sw          $t1, 0x4($s0)
    MEM_W(0X4, ctx->r16) = ctx->r9;
L_80046B1C:
    // 0x80046B1C: lw          $s0, 0x0($s1)
    ctx->r16 = MEM_W(ctx->r17, 0X0);
L_80046B20:
    // 0x80046B20: lui         $t3, 0xBC00
    ctx->r11 = S32(0XBC00 << 16);
    // 0x80046B24: lui         $a2, 0x8015
    ctx->r6 = S32(0X8015 << 16);
    // 0x80046B28: addiu       $t2, $s0, 0x8
    ctx->r10 = ADD32(ctx->r16, 0X8);
    // 0x80046B2C: sw          $t2, 0x0($s1)
    MEM_W(0X0, ctx->r17) = ctx->r10;
    // 0x80046B30: ori         $t3, $t3, 0x1006
    ctx->r11 = ctx->r11 | 0X1006;
    // 0x80046B34: addiu       $a2, $a2, 0x42C0
    ctx->r6 = ADD32(ctx->r6, 0X42C0);
    // 0x80046B38: sw          $t3, 0x0($s0)
    MEM_W(0X0, ctx->r16) = ctx->r11;
    // 0x80046B3C: lw          $t4, 0xC($a2)
    ctx->r12 = MEM_W(ctx->r6, 0XC);
    // 0x80046B40: lui         $a1, 0x8000
    ctx->r5 = S32(0X8000 << 16);
    // 0x80046B44: lui         $t7, 0xE700
    ctx->r15 = S32(0XE700 << 16);
    // 0x80046B48: addu        $t5, $t4, $a1
    ctx->r13 = ADD32(ctx->r12, ctx->r5);
    // 0x80046B4C: sw          $t5, 0x4($s0)
    MEM_W(0X4, ctx->r16) = ctx->r13;
    // 0x80046B50: lw          $s0, 0x0($s1)
    ctx->r16 = MEM_W(ctx->r17, 0X0);
    // 0x80046B54: lui         $t9, 0xFF10
    ctx->r25 = S32(0XFF10 << 16);
    // 0x80046B58: ori         $t9, $t9, 0x13F
    ctx->r25 = ctx->r25 | 0X13F;
    // 0x80046B5C: addiu       $t6, $s0, 0x8
    ctx->r14 = ADD32(ctx->r16, 0X8);
    // 0x80046B60: sw          $t6, 0x0($s1)
    MEM_W(0X0, ctx->r17) = ctx->r14;
    // 0x80046B64: sw          $zero, 0x4($s0)
    MEM_W(0X4, ctx->r16) = 0;
    // 0x80046B68: sw          $t7, 0x0($s0)
    MEM_W(0X0, ctx->r16) = ctx->r15;
    // 0x80046B6C: lw          $s0, 0x0($s1)
    ctx->r16 = MEM_W(ctx->r17, 0X0);
    // 0x80046B70: addiu       $t8, $s0, 0x8
    ctx->r24 = ADD32(ctx->r16, 0X8);
    // 0x80046B74: sw          $t8, 0x0($s1)
    MEM_W(0X0, ctx->r17) = ctx->r24;
    // 0x80046B78: sw          $t9, 0x0($s0)
    MEM_W(0X0, ctx->r16) = ctx->r25;
    // 0x80046B7C: lw          $t0, 0xC($a2)
    ctx->r8 = MEM_W(ctx->r6, 0XC);
    // 0x80046B80: addu        $t1, $t0, $a1
    ctx->r9 = ADD32(ctx->r8, ctx->r5);
    // 0x80046B84: b           L_80046BE0
    // 0x80046B88: sw          $t1, 0x4($s0)
    MEM_W(0X4, ctx->r16) = ctx->r9;
        goto L_80046BE0;
    // 0x80046B88: sw          $t1, 0x4($s0)
    MEM_W(0X4, ctx->r16) = ctx->r9;
    // 0x80046B8C: lw          $s0, 0x0($s1)
    ctx->r16 = MEM_W(ctx->r17, 0X0);
L_80046B90:
    // 0x80046B90: lui         $t3, 0xE700
    ctx->r11 = S32(0XE700 << 16);
    // 0x80046B94: lui         $t5, 0xFF10
    ctx->r13 = S32(0XFF10 << 16);
    // 0x80046B98: addiu       $t2, $s0, 0x8
    ctx->r10 = ADD32(ctx->r16, 0X8);
    // 0x80046B9C: sw          $t2, 0x0($s1)
    MEM_W(0X0, ctx->r17) = ctx->r10;
    // 0x80046BA0: sw          $zero, 0x4($s0)
    MEM_W(0X4, ctx->r16) = 0;
    // 0x80046BA4: sw          $t3, 0x0($s0)
    MEM_W(0X0, ctx->r16) = ctx->r11;
    // 0x80046BA8: lw          $s0, 0x0($s1)
    ctx->r16 = MEM_W(ctx->r17, 0X0);
    // 0x80046BAC: ori         $t5, $t5, 0x27F
    ctx->r13 = ctx->r13 | 0X27F;
    // 0x80046BB0: lui         $t6, 0x800D
    ctx->r14 = S32(0X800D << 16);
    // 0x80046BB4: addiu       $t4, $s0, 0x8
    ctx->r12 = ADD32(ctx->r16, 0X8);
    // 0x80046BB8: sw          $t4, 0x0($s1)
    MEM_W(0X0, ctx->r17) = ctx->r12;
    // 0x80046BBC: sw          $t5, 0x0($s0)
    MEM_W(0X0, ctx->r16) = ctx->r13;
    // 0x80046BC0: lw          $t6, 0x45D8($t6)
    ctx->r14 = MEM_W(ctx->r14, 0X45D8);
    // 0x80046BC4: lui         $t8, 0x800D
    ctx->r24 = S32(0X800D << 16);
    // 0x80046BC8: lui         $a1, 0x8000
    ctx->r5 = S32(0X8000 << 16);
    // 0x80046BCC: sll         $t7, $t6, 2
    ctx->r15 = S32(ctx->r14 << 2);
    // 0x80046BD0: addu        $t8, $t8, $t7
    ctx->r24 = ADD32(ctx->r24, ctx->r15);
    // 0x80046BD4: lw          $t8, 0x45DC($t8)
    ctx->r24 = MEM_W(ctx->r24, 0X45DC);
    // 0x80046BD8: addu        $t9, $t8, $a1
    ctx->r25 = ADD32(ctx->r24, ctx->r5);
    // 0x80046BDC: sw          $t9, 0x4($s0)
    MEM_W(0X4, ctx->r16) = ctx->r25;
L_80046BE0:
    // 0x80046BE0: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
L_80046BE4:
    // 0x80046BE4: lw          $s0, 0x14($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X14);
    // 0x80046BE8: lw          $s1, 0x18($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X18);
    // 0x80046BEC: jr          $ra
    // 0x80046BF0: addiu       $sp, $sp, 0x38
    ctx->r29 = ADD32(ctx->r29, 0X38);
    return;
    // 0x80046BF0: addiu       $sp, $sp, 0x38
    ctx->r29 = ADD32(ctx->r29, 0X38);
;}
RECOMP_FUNC void SysMain_GfxFullSync(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x80046BF4: lui         $a1, 0x8015
    ctx->r5 = S32(0X8015 << 16);
    // 0x80046BF8: addiu       $a1, $a1, 0x1944
    ctx->r5 = ADD32(ctx->r5, 0X1944);
    // 0x80046BFC: lw          $v1, 0x0($a1)
    ctx->r3 = MEM_W(ctx->r5, 0X0);
    // 0x80046C00: lui         $t7, 0xE900
    ctx->r15 = S32(0XE900 << 16);
    // 0x80046C04: lui         $t9, 0xB800
    ctx->r25 = S32(0XB800 << 16);
    // 0x80046C08: addiu       $t6, $v1, 0x8
    ctx->r14 = ADD32(ctx->r3, 0X8);
    // 0x80046C0C: sw          $t6, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r14;
    // 0x80046C10: sw          $zero, 0x4($v1)
    MEM_W(0X4, ctx->r3) = 0;
    // 0x80046C14: sw          $t7, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r15;
    // 0x80046C18: lw          $v1, 0x0($a1)
    ctx->r3 = MEM_W(ctx->r5, 0X0);
    // 0x80046C1C: addiu       $t8, $v1, 0x8
    ctx->r24 = ADD32(ctx->r3, 0X8);
    // 0x80046C20: sw          $t8, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r24;
    // 0x80046C24: sw          $zero, 0x4($v1)
    MEM_W(0X4, ctx->r3) = 0;
    // 0x80046C28: jr          $ra
    // 0x80046C2C: sw          $t9, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r25;
    return;
    // 0x80046C2C: sw          $t9, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r25;
;}
RECOMP_FUNC void SysMain_CreateGfxTask(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x80046C30: lui         $v0, 0x800F
    ctx->r2 = S32(0X800F << 16);
    // 0x80046C34: addiu       $v0, $v0, -0x1230
    ctx->r2 = ADD32(ctx->r2, -0X1230);
    // 0x80046C38: lui         $v1, 0x800D
    ctx->r3 = S32(0X800D << 16);
    // 0x80046C3C: addiu       $t6, $zero, 0x1
    ctx->r14 = ADD32(0, 0X1);
    // 0x80046C40: lui         $t7, 0x800D
    ctx->r15 = S32(0X800D << 16);
    // 0x80046C44: addiu       $v0, $v0, 0xF
    ctx->r2 = ADD32(ctx->r2, 0XF);
    // 0x80046C48: addiu       $at, $zero, -0x10
    ctx->r1 = ADD32(0, -0X10);
    // 0x80046C4C: addiu       $v1, $v1, 0x22B0
    ctx->r3 = ADD32(ctx->r3, 0X22B0);
    // 0x80046C50: sw          $t6, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r14;
    // 0x80046C54: addiu       $t7, $t7, 0x2380
    ctx->r15 = ADD32(ctx->r15, 0X2380);
    // 0x80046C58: lui         $t9, 0x800D
    ctx->r25 = S32(0X800D << 16);
    // 0x80046C5C: lui         $t1, 0x800F
    ctx->r9 = S32(0X800F << 16);
    // 0x80046C60: lui         $t3, 0x8004
    ctx->r11 = S32(0X8004 << 16);
    // 0x80046C64: and         $t5, $v0, $at
    ctx->r13 = ctx->r2 & ctx->r1;
    // 0x80046C68: lui         $a1, 0x8015
    ctx->r5 = S32(0X8015 << 16);
    // 0x80046C6C: subu        $t8, $t7, $v1
    ctx->r24 = SUB32(ctx->r15, ctx->r3);
    // 0x80046C70: addiu       $t9, $t9, 0x2380
    ctx->r25 = ADD32(ctx->r25, 0X2380);
    // 0x80046C74: addiu       $t0, $zero, 0x1000
    ctx->r8 = ADD32(0, 0X1000);
    // 0x80046C78: addiu       $t1, $t1, -0x1CF0
    ctx->r9 = ADD32(ctx->r9, -0X1CF0);
    // 0x80046C7C: addiu       $t2, $zero, 0x800
    ctx->r10 = ADD32(0, 0X800);
    // 0x80046C80: addiu       $t3, $t3, 0x6400
    ctx->r11 = ADD32(ctx->r11, 0X6400);
    // 0x80046C84: addiu       $t4, $zero, 0x400
    ctx->r12 = ADD32(0, 0X400);
    // 0x80046C88: addiu       $t6, $t5, 0x6000
    ctx->r14 = ADD32(ctx->r13, 0X6000);
    // 0x80046C8C: addiu       $a1, $a1, 0x18B8
    ctx->r5 = ADD32(ctx->r5, 0X18B8);
    // 0x80046C90: sw          $zero, 0x4($a0)
    MEM_W(0X4, ctx->r4) = 0;
    // 0x80046C94: sw          $v1, 0x8($a0)
    MEM_W(0X8, ctx->r4) = ctx->r3;
    // 0x80046C98: sw          $t8, 0xC($a0)
    MEM_W(0XC, ctx->r4) = ctx->r24;
    // 0x80046C9C: sw          $t9, 0x10($a0)
    MEM_W(0X10, ctx->r4) = ctx->r25;
    // 0x80046CA0: sw          $t0, 0x14($a0)
    MEM_W(0X14, ctx->r4) = ctx->r8;
    // 0x80046CA4: sw          $t1, 0x18($a0)
    MEM_W(0X18, ctx->r4) = ctx->r9;
    // 0x80046CA8: sw          $t2, 0x1C($a0)
    MEM_W(0X1C, ctx->r4) = ctx->r10;
    // 0x80046CAC: sw          $t3, 0x20($a0)
    MEM_W(0X20, ctx->r4) = ctx->r11;
    // 0x80046CB0: sw          $t4, 0x24($a0)
    MEM_W(0X24, ctx->r4) = ctx->r12;
    // 0x80046CB4: sw          $t5, 0x28($a0)
    MEM_W(0X28, ctx->r4) = ctx->r13;
    // 0x80046CB8: sw          $t6, 0x2C($a0)
    MEM_W(0X2C, ctx->r4) = ctx->r14;
    // 0x80046CBC: lw          $t7, 0x0($a1)
    ctx->r15 = MEM_W(ctx->r5, 0X0);
    // 0x80046CC0: lui         $t8, 0x8015
    ctx->r24 = S32(0X8015 << 16);
    // 0x80046CC4: lui         $t3, 0x8004
    ctx->r11 = S32(0X8004 << 16);
    // 0x80046CC8: sw          $t7, 0x30($a0)
    MEM_W(0X30, ctx->r4) = ctx->r15;
    // 0x80046CCC: lw          $t9, 0x0($a1)
    ctx->r25 = MEM_W(ctx->r5, 0X0);
    // 0x80046CD0: lw          $t8, 0x1944($t8)
    ctx->r24 = MEM_W(ctx->r24, 0X1944);
    // 0x80046CD4: addiu       $t3, $t3, 0x5800
    ctx->r11 = ADD32(ctx->r11, 0X5800);
    // 0x80046CD8: addiu       $t4, $zero, 0xC00
    ctx->r12 = ADD32(0, 0XC00);
    // 0x80046CDC: subu        $t0, $t8, $t9
    ctx->r8 = SUB32(ctx->r24, ctx->r25);
    // 0x80046CE0: sra         $t1, $t0, 3
    ctx->r9 = S32(SIGNED(ctx->r8) >> 3);
    // 0x80046CE4: sll         $t2, $t1, 3
    ctx->r10 = S32(ctx->r9 << 3);
    // 0x80046CE8: sw          $t2, 0x34($a0)
    MEM_W(0X34, ctx->r4) = ctx->r10;
    // 0x80046CEC: sw          $t3, 0x38($a0)
    MEM_W(0X38, ctx->r4) = ctx->r11;
    // 0x80046CF0: jr          $ra
    // 0x80046CF4: sw          $t4, 0x3C($a0)
    MEM_W(0X3C, ctx->r4) = ctx->r12;
    return;
    // 0x80046CF4: sw          $t4, 0x3C($a0)
    MEM_W(0X3C, ctx->r4) = ctx->r12;
;}
RECOMP_FUNC void SysMain_SendGfxTaskSetMesg(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x80046CF8: lui         $at, 0x8015
    ctx->r1 = S32(0X8015 << 16);
    // 0x80046CFC: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x80046D00: sw          $a0, 0x42B4($at)
    MEM_W(0X42B4, ctx->r1) = ctx->r4;
    // 0x80046D04: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x80046D08: lui         $a0, 0x8015
    ctx->r4 = S32(0X8015 << 16);
    // 0x80046D0C: addiu       $a0, $a0, 0x4130
    ctx->r4 = ADD32(ctx->r4, 0X4130);
    // 0x80046D10: addiu       $a1, $zero, 0x15
    ctx->r5 = ADD32(0, 0X15);
    // 0x80046D14: jal         0x800C57A0
    // 0x80046D18: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    osSendMesg_recomp(rdram, ctx);
        goto after_0;
    // 0x80046D18: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    after_0:
    // 0x80046D1C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x80046D20: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x80046D24: jr          $ra
    // 0x80046D28: nop

    return;
    // 0x80046D28: nop

;}
RECOMP_FUNC void SysMain_GfxInitBuffers(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x80046D2C: lui         $v1, 0x8012
    ctx->r3 = S32(0X8012 << 16);
    // 0x80046D30: addiu       $v1, $v1, -0x720
    ctx->r3 = ADD32(ctx->r3, -0X720);
    // 0x80046D34: lw          $t6, 0x0($v1)
    ctx->r14 = MEM_W(ctx->r3, 0X0);
    // 0x80046D38: lui         $t9, 0x8015
    ctx->r25 = S32(0X8015 << 16);
    // 0x80046D3C: addiu       $t9, $t9, 0x18C0
    ctx->r25 = ADD32(ctx->r25, 0X18C0);
    // 0x80046D40: xori        $t7, $t6, 0x1
    ctx->r15 = ctx->r14 ^ 0X1;
    // 0x80046D44: sll         $t1, $t7, 2
    ctx->r9 = S32(ctx->r15 << 2);
    // 0x80046D48: subu        $t1, $t1, $t7
    ctx->r9 = SUB32(ctx->r9, ctx->r15);
    // 0x80046D4C: sll         $t1, $t1, 3
    ctx->r9 = S32(ctx->r9 << 3);
    // 0x80046D50: addu        $t1, $t1, $t7
    ctx->r9 = ADD32(ctx->r9, ctx->r15);
    // 0x80046D54: sll         $t1, $t1, 7
    ctx->r9 = S32(ctx->r9 << 7);
    // 0x80046D58: subu        $t1, $t1, $t7
    ctx->r9 = SUB32(ctx->r9, ctx->r15);
    // 0x80046D5C: sll         $t8, $t7, 6
    ctx->r24 = S32(ctx->r15 << 6);
    // 0x80046D60: sll         $t1, $t1, 2
    ctx->r9 = S32(ctx->r9 << 2);
    // 0x80046D64: sw          $t7, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r15;
    // 0x80046D68: addu        $t0, $t8, $t9
    ctx->r8 = ADD32(ctx->r24, ctx->r25);
    // 0x80046D6C: lui         $at, 0x8015
    ctx->r1 = S32(0X8015 << 16);
    // 0x80046D70: addu        $t1, $t1, $t7
    ctx->r9 = ADD32(ctx->r9, ctx->r15);
    // 0x80046D74: lui         $t2, 0x8012
    ctx->r10 = S32(0X8012 << 16);
    // 0x80046D78: lui         $a0, 0x8015
    ctx->r4 = S32(0X8015 << 16);
    // 0x80046D7C: sw          $t0, 0x1940($at)
    MEM_W(0X1940, ctx->r1) = ctx->r8;
    // 0x80046D80: addiu       $t2, $t2, -0x718
    ctx->r10 = ADD32(ctx->r10, -0X718);
    // 0x80046D84: sll         $t1, $t1, 3
    ctx->r9 = S32(ctx->r9 << 3);
    // 0x80046D88: addiu       $a0, $a0, 0x18B8
    ctx->r4 = ADD32(ctx->r4, 0X18B8);
    // 0x80046D8C: addu        $t3, $t1, $t2
    ctx->r11 = ADD32(ctx->r9, ctx->r10);
    // 0x80046D90: sw          $t3, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r11;
    // 0x80046D94: lui         $at, 0x8015
    ctx->r1 = S32(0X8015 << 16);
    // 0x80046D98: jr          $ra
    // 0x80046D9C: sw          $t3, 0x1944($at)
    MEM_W(0X1944, ctx->r1) = ctx->r11;
    return;
    // 0x80046D9C: sw          $t3, 0x1944($at)
    MEM_W(0X1944, ctx->r1) = ctx->r11;
;}
RECOMP_FUNC void SysMain_Thread(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x80046DA0: addiu       $sp, $sp, -0xA0
    ctx->r29 = ADD32(ctx->r29, -0XA0);
    // 0x80046DA4: sw          $a0, 0xA0($sp)
    MEM_W(0XA0, ctx->r29) = ctx->r4;
    // 0x80046DA8: sw          $ra, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r31;
    // 0x80046DAC: lui         $a0, 0x8004
    ctx->r4 = S32(0X8004 << 16);
    // 0x80046DB0: sw          $s1, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r17;
    // 0x80046DB4: sw          $s0, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r16;
    // 0x80046DB8: jal         0x800C5720
    // 0x80046DBC: addiu       $a0, $a0, 0x6850
    ctx->r4 = ADD32(ctx->r4, 0X6850);
    osVirtualToPhysical_recomp(rdram, ctx);
        goto after_0;
    // 0x80046DBC: addiu       $a0, $a0, 0x6850
    ctx->r4 = ADD32(ctx->r4, 0X6850);
    after_0:
    // 0x80046DC0: lui         $at, 0x8015
    ctx->r1 = S32(0X8015 << 16);
    // 0x80046DC4: lui         $a0, 0x801E
    ctx->r4 = S32(0X801E << 16);
    // 0x80046DC8: sw          $v0, 0x1964($at)
    MEM_W(0X1964, ctx->r1) = ctx->r2;
    // 0x80046DCC: jal         0x800C5720
    // 0x80046DD0: addiu       $a0, $a0, -0x5060
    ctx->r4 = ADD32(ctx->r4, -0X5060);
    osVirtualToPhysical_recomp(rdram, ctx);
        goto after_1;
    // 0x80046DD0: addiu       $a0, $a0, -0x5060
    ctx->r4 = ADD32(ctx->r4, -0X5060);
    after_1:
    // 0x80046DD4: lui         $t7, 0x8023
    ctx->r15 = S32(0X8023 << 16);
    // 0x80046DD8: lui         $t8, 0x801E
    ctx->r24 = S32(0X801E << 16);
    // 0x80046DDC: lui         $a1, 0x8015
    ctx->r5 = S32(0X8015 << 16);
    // 0x80046DE0: lui         $a2, 0x8015
    ctx->r6 = S32(0X8015 << 16);
    // 0x80046DE4: addiu       $t8, $t8, -0x5060
    ctx->r24 = ADD32(ctx->r24, -0X5060);
    // 0x80046DE8: addiu       $t7, $t7, -0x71F0
    ctx->r15 = ADD32(ctx->r15, -0X71F0);
    // 0x80046DEC: addiu       $a2, $a2, 0x196C
    ctx->r6 = ADD32(ctx->r6, 0X196C);
    // 0x80046DF0: addiu       $a1, $a1, 0x1968
    ctx->r5 = ADD32(ctx->r5, 0X1968);
    // 0x80046DF4: subu        $t9, $t7, $t8
    ctx->r25 = SUB32(ctx->r15, ctx->r24);
    // 0x80046DF8: sw          $v0, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r2;
    // 0x80046DFC: sw          $v0, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r2;
    // 0x80046E00: addu        $t2, $t9, $v0
    ctx->r10 = ADD32(ctx->r25, ctx->r2);
    // 0x80046E04: lui         $at, 0x8015
    ctx->r1 = S32(0X8015 << 16);
    // 0x80046E08: lui         $a0, 0x802A
    ctx->r4 = S32(0X802A << 16);
    // 0x80046E0C: sw          $t2, 0x1970($at)
    MEM_W(0X1970, ctx->r1) = ctx->r10;
    // 0x80046E10: jal         0x800C5720
    // 0x80046E14: addiu       $a0, $a0, 0x0
    ctx->r4 = ADD32(ctx->r4, 0X0);
    osVirtualToPhysical_recomp(rdram, ctx);
        goto after_2;
    // 0x80046E14: addiu       $a0, $a0, 0x0
    ctx->r4 = ADD32(ctx->r4, 0X0);
    after_2:
    // 0x80046E18: lui         $at, 0x8015
    ctx->r1 = S32(0X8015 << 16);
    // 0x80046E1C: lui         $a0, 0x802C
    ctx->r4 = S32(0X802C << 16);
    // 0x80046E20: sw          $v0, 0x1974($at)
    MEM_W(0X1974, ctx->r1) = ctx->r2;
    // 0x80046E24: jal         0x800C5720
    // 0x80046E28: addiu       $a0, $a0, 0x5800
    ctx->r4 = ADD32(ctx->r4, 0X5800);
    osVirtualToPhysical_recomp(rdram, ctx);
        goto after_3;
    // 0x80046E28: addiu       $a0, $a0, 0x5800
    ctx->r4 = ADD32(ctx->r4, 0X5800);
    after_3:
    // 0x80046E2C: lui         $at, 0x8015
    ctx->r1 = S32(0X8015 << 16);
    // 0x80046E30: lui         $a0, 0x8039
    ctx->r4 = S32(0X8039 << 16);
    // 0x80046E34: sw          $v0, 0x1978($at)
    MEM_W(0X1978, ctx->r1) = ctx->r2;
    // 0x80046E38: jal         0x800C5720
    // 0x80046E3C: addiu       $a0, $a0, -0x800
    ctx->r4 = ADD32(ctx->r4, -0X800);
    osVirtualToPhysical_recomp(rdram, ctx);
        goto after_4;
    // 0x80046E3C: addiu       $a0, $a0, -0x800
    ctx->r4 = ADD32(ctx->r4, -0X800);
    after_4:
    // 0x80046E40: lui         $at, 0x8015
    ctx->r1 = S32(0X8015 << 16);
    // 0x80046E44: lui         $a0, 0x8040
    ctx->r4 = S32(0X8040 << 16);
    // 0x80046E48: sw          $v0, 0x197C($at)
    MEM_W(0X197C, ctx->r1) = ctx->r2;
    // 0x80046E4C: jal         0x800C5720
    // 0x80046E50: addiu       $a0, $a0, 0x0
    ctx->r4 = ADD32(ctx->r4, 0X0);
    osVirtualToPhysical_recomp(rdram, ctx);
        goto after_5;
    // 0x80046E50: addiu       $a0, $a0, 0x0
    ctx->r4 = ADD32(ctx->r4, 0X0);
    after_5:
    // 0x80046E54: lui         $at, 0x8015
    ctx->r1 = S32(0X8015 << 16);
    // 0x80046E58: lui         $a0, 0x8000
    ctx->r4 = S32(0X8000 << 16);
    // 0x80046E5C: sw          $v0, 0x1980($at)
    MEM_W(0X1980, ctx->r1) = ctx->r2;
    // 0x80046E60: jal         0x800C5720
    // 0x80046E64: addiu       $a0, $a0, 0x1000
    ctx->r4 = ADD32(ctx->r4, 0X1000);
    osVirtualToPhysical_recomp(rdram, ctx);
        goto after_6;
    // 0x80046E64: addiu       $a0, $a0, 0x1000
    ctx->r4 = ADD32(ctx->r4, 0X1000);
    after_6:
    // 0x80046E68: lui         $at, 0x8015
    ctx->r1 = S32(0X8015 << 16);
    // 0x80046E6C: lui         $a0, 0x8004
    ctx->r4 = S32(0X8004 << 16);
    // 0x80046E70: sw          $v0, 0x19A4($at)
    MEM_W(0X19A4, ctx->r1) = ctx->r2;
    // 0x80046E74: jal         0x800C5720
    // 0x80046E78: addiu       $a0, $a0, 0x5650
    ctx->r4 = ADD32(ctx->r4, 0X5650);
    osVirtualToPhysical_recomp(rdram, ctx);
        goto after_7;
    // 0x80046E78: addiu       $a0, $a0, 0x5650
    ctx->r4 = ADD32(ctx->r4, 0X5650);
    after_7:
    // 0x80046E7C: lui         $t3, 0x8015
    ctx->r11 = S32(0X8015 << 16);
    // 0x80046E80: lw          $t3, 0x1970($t3)
    ctx->r11 = MEM_W(ctx->r11, 0X1970);
    // 0x80046E84: lui         $t6, 0x101
    ctx->r14 = S32(0X101 << 16);
    // 0x80046E88: lui         $t7, 0x100
    ctx->r15 = S32(0X100 << 16);
    // 0x80046E8C: addiu       $s0, $zero, -0x10
    ctx->r16 = ADD32(0, -0X10);
    // 0x80046E90: addiu       $t7, $t7, 0x0
    ctx->r15 = ADD32(ctx->r15, 0X0);
    // 0x80046E94: addiu       $t6, $t6, -0x7D70
    ctx->r14 = ADD32(ctx->r14, -0X7D70);
    // 0x80046E98: addiu       $t4, $t3, 0xF
    ctx->r12 = ADD32(ctx->r11, 0XF);
    // 0x80046E9C: and         $t5, $t4, $s0
    ctx->r13 = ctx->r12 & ctx->r16;
    // 0x80046EA0: subu        $t8, $t6, $t7
    ctx->r24 = SUB32(ctx->r14, ctx->r15);
    // 0x80046EA4: lui         $t0, 0x8015
    ctx->r8 = S32(0X8015 << 16);
    // 0x80046EA8: lui         $at, 0x8015
    ctx->r1 = S32(0X8015 << 16);
    // 0x80046EAC: addiu       $t9, $t8, 0xF
    ctx->r25 = ADD32(ctx->r24, 0XF);
    // 0x80046EB0: sw          $v0, 0x19A8($at)
    MEM_W(0X19A8, ctx->r1) = ctx->r2;
    // 0x80046EB4: addiu       $t0, $t0, 0x1984
    ctx->r8 = ADD32(ctx->r8, 0X1984);
    // 0x80046EB8: and         $s1, $t9, $s0
    ctx->r17 = ctx->r25 & ctx->r16;
    // 0x80046EBC: sw          $t5, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r13;
    // 0x80046EC0: addu        $t2, $s1, $t5
    ctx->r10 = ADD32(ctx->r17, ctx->r13);
    // 0x80046EC4: lui         $t5, 0x101
    ctx->r13 = S32(0X101 << 16);
    // 0x80046EC8: lui         $t4, 0x107
    ctx->r12 = S32(0X107 << 16);
    // 0x80046ECC: addiu       $t4, $t4, -0x490
    ctx->r12 = ADD32(ctx->r12, -0X490);
    // 0x80046ED0: addiu       $t5, $t5, -0x7D70
    ctx->r13 = ADD32(ctx->r13, -0X7D70);
    // 0x80046ED4: subu        $t6, $t4, $t5
    ctx->r14 = SUB32(ctx->r12, ctx->r13);
    // 0x80046ED8: lui         $a1, 0x8015
    ctx->r5 = S32(0X8015 << 16);
    // 0x80046EDC: lui         $a3, 0x8015
    ctx->r7 = S32(0X8015 << 16);
    // 0x80046EE0: addiu       $t7, $t6, 0xF
    ctx->r15 = ADD32(ctx->r14, 0XF);
    // 0x80046EE4: addiu       $a3, $a3, 0x198C
    ctx->r7 = ADD32(ctx->r7, 0X198C);
    // 0x80046EE8: addiu       $a1, $a1, 0x1988
    ctx->r5 = ADD32(ctx->r5, 0X1988);
    // 0x80046EEC: and         $a2, $t7, $s0
    ctx->r6 = ctx->r15 & ctx->r16;
    // 0x80046EF0: sw          $t2, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r10;
    // 0x80046EF4: sw          $t2, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r10;
    // 0x80046EF8: addu        $t9, $a2, $t2
    ctx->r25 = ADD32(ctx->r6, ctx->r10);
    // 0x80046EFC: lui         $at, 0x8015
    ctx->r1 = S32(0X8015 << 16);
    // 0x80046F00: lui         $a0, 0x802C
    ctx->r4 = S32(0X802C << 16);
    // 0x80046F04: sw          $t9, 0x1990($at)
    MEM_W(0X1990, ctx->r1) = ctx->r25;
    // 0x80046F08: ori         $a0, $a0, 0x5800
    ctx->r4 = ctx->r4 | 0X5800;
    // 0x80046F0C: jal         0x800C5720
    // 0x80046F10: sw          $a2, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r6;
    osVirtualToPhysical_recomp(rdram, ctx);
        goto after_8;
    // 0x80046F10: sw          $a2, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r6;
    after_8:
    // 0x80046F14: lui         $at, 0x1
    ctx->r1 = S32(0X1 << 16);
    // 0x80046F18: lui         $a1, 0x8015
    ctx->r5 = S32(0X8015 << 16);
    // 0x80046F1C: ori         $at, $at, 0x1000
    ctx->r1 = ctx->r1 | 0X1000;
    // 0x80046F20: addiu       $a1, $a1, 0x19CC
    ctx->r5 = ADD32(ctx->r5, 0X19CC);
    // 0x80046F24: addu        $t2, $v0, $at
    ctx->r10 = ADD32(ctx->r2, ctx->r1);
    // 0x80046F28: sw          $v0, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r2;
    // 0x80046F2C: lui         $at, 0x8015
    ctx->r1 = S32(0X8015 << 16);
    // 0x80046F30: lui         $a0, 0x802D
    ctx->r4 = S32(0X802D << 16);
    // 0x80046F34: sw          $t2, 0x19D0($at)
    MEM_W(0X19D0, ctx->r1) = ctx->r10;
    // 0x80046F38: jal         0x800C5720
    // 0x80046F3C: ori         $a0, $a0, 0x6800
    ctx->r4 = ctx->r4 | 0X6800;
    osVirtualToPhysical_recomp(rdram, ctx);
        goto after_9;
    // 0x80046F3C: ori         $a0, $a0, 0x6800
    ctx->r4 = ctx->r4 | 0X6800;
    after_9:
    // 0x80046F40: lui         $a1, 0x8015
    ctx->r5 = S32(0X8015 << 16);
    // 0x80046F44: lui         $at, 0x4
    ctx->r1 = S32(0X4 << 16);
    // 0x80046F48: addiu       $a1, $a1, 0x19BC
    ctx->r5 = ADD32(ctx->r5, 0X19BC);
    // 0x80046F4C: addu        $t4, $v0, $at
    ctx->r12 = ADD32(ctx->r2, ctx->r1);
    // 0x80046F50: sw          $v0, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r2;
    // 0x80046F54: lui         $at, 0x8015
    ctx->r1 = S32(0X8015 << 16);
    // 0x80046F58: lui         $a0, 0x802D
    ctx->r4 = S32(0X802D << 16);
    // 0x80046F5C: sw          $t4, 0x19C0($at)
    MEM_W(0X19C0, ctx->r1) = ctx->r12;
    // 0x80046F60: jal         0x800C5720
    // 0x80046F64: ori         $a0, $a0, 0x6800
    ctx->r4 = ctx->r4 | 0X6800;
    osVirtualToPhysical_recomp(rdram, ctx);
        goto after_10;
    // 0x80046F64: ori         $a0, $a0, 0x6800
    ctx->r4 = ctx->r4 | 0X6800;
    after_10:
    // 0x80046F68: lui         $at, 0x3
    ctx->r1 = S32(0X3 << 16);
    // 0x80046F6C: addu        $t5, $v0, $at
    ctx->r13 = ADD32(ctx->r2, ctx->r1);
    // 0x80046F70: lui         $a1, 0x8015
    ctx->r5 = S32(0X8015 << 16);
    // 0x80046F74: lui         $at, 0x1
    ctx->r1 = S32(0X1 << 16);
    // 0x80046F78: addiu       $a1, $a1, 0x19C4
    ctx->r5 = ADD32(ctx->r5, 0X19C4);
    // 0x80046F7C: addu        $t7, $t5, $at
    ctx->r15 = ADD32(ctx->r13, ctx->r1);
    // 0x80046F80: sw          $t5, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r13;
    // 0x80046F84: lui         $at, 0x8015
    ctx->r1 = S32(0X8015 << 16);
    // 0x80046F88: lui         $a0, 0x8031
    ctx->r4 = S32(0X8031 << 16);
    // 0x80046F8C: sw          $t7, 0x19C8($at)
    MEM_W(0X19C8, ctx->r1) = ctx->r15;
    // 0x80046F90: jal         0x800C5720
    // 0x80046F94: ori         $a0, $a0, 0x6800
    ctx->r4 = ctx->r4 | 0X6800;
    osVirtualToPhysical_recomp(rdram, ctx);
        goto after_11;
    // 0x80046F94: ori         $a0, $a0, 0x6800
    ctx->r4 = ctx->r4 | 0X6800;
    after_11:
    // 0x80046F98: lui         $at, 0x7
    ctx->r1 = S32(0X7 << 16);
    // 0x80046F9C: lui         $a1, 0x8015
    ctx->r5 = S32(0X8015 << 16);
    // 0x80046FA0: ori         $at, $at, 0x9000
    ctx->r1 = ctx->r1 | 0X9000;
    // 0x80046FA4: addiu       $a1, $a1, 0x19B4
    ctx->r5 = ADD32(ctx->r5, 0X19B4);
    // 0x80046FA8: addu        $t9, $v0, $at
    ctx->r25 = ADD32(ctx->r2, ctx->r1);
    // 0x80046FAC: sw          $v0, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r2;
    // 0x80046FB0: lui         $at, 0x8015
    ctx->r1 = S32(0X8015 << 16);
    // 0x80046FB4: lui         $a0, 0x8012
    ctx->r4 = S32(0X8012 << 16);
    // 0x80046FB8: sw          $t9, 0x19B8($at)
    MEM_W(0X19B8, ctx->r1) = ctx->r25;
    // 0x80046FBC: jal         0x800C5720
    // 0x80046FC0: addiu       $a0, $a0, -0x1220
    ctx->r4 = ADD32(ctx->r4, -0X1220);
    osVirtualToPhysical_recomp(rdram, ctx);
        goto after_12;
    // 0x80046FC0: addiu       $a0, $a0, -0x1220
    ctx->r4 = ADD32(ctx->r4, -0X1220);
    after_12:
    // 0x80046FC4: lui         $at, 0x8015
    ctx->r1 = S32(0X8015 << 16);
    // 0x80046FC8: lui         $a0, 0x8012
    ctx->r4 = S32(0X8012 << 16);
    // 0x80046FCC: sw          $v0, 0x1994($at)
    MEM_W(0X1994, ctx->r1) = ctx->r2;
    // 0x80046FD0: jal         0x800C5720
    // 0x80046FD4: addiu       $a0, $a0, -0x720
    ctx->r4 = ADD32(ctx->r4, -0X720);
    osVirtualToPhysical_recomp(rdram, ctx);
        goto after_13;
    // 0x80046FD4: addiu       $a0, $a0, -0x720
    ctx->r4 = ADD32(ctx->r4, -0X720);
    after_13:
    // 0x80046FD8: lui         $at, 0x8015
    ctx->r1 = S32(0X8015 << 16);
    // 0x80046FDC: lui         $a0, 0x8012
    ctx->r4 = S32(0X8012 << 16);
    // 0x80046FE0: sw          $v0, 0x1998($at)
    MEM_W(0X1998, ctx->r1) = ctx->r2;
    // 0x80046FE4: jal         0x800C5720
    // 0x80046FE8: addiu       $a0, $a0, -0x718
    ctx->r4 = ADD32(ctx->r4, -0X718);
    osVirtualToPhysical_recomp(rdram, ctx);
        goto after_14;
    // 0x80046FE8: addiu       $a0, $a0, -0x718
    ctx->r4 = ADD32(ctx->r4, -0X718);
    after_14:
    // 0x80046FEC: lui         $at, 0x8015
    ctx->r1 = S32(0X8015 << 16);
    // 0x80046FF0: lui         $a0, 0x8015
    ctx->r4 = S32(0X8015 << 16);
    // 0x80046FF4: sw          $v0, 0x199C($at)
    MEM_W(0X199C, ctx->r1) = ctx->r2;
    // 0x80046FF8: jal         0x800C5720
    // 0x80046FFC: addiu       $a0, $a0, 0x18B8
    ctx->r4 = ADD32(ctx->r4, 0X18B8);
    osVirtualToPhysical_recomp(rdram, ctx);
        goto after_15;
    // 0x80046FFC: addiu       $a0, $a0, 0x18B8
    ctx->r4 = ADD32(ctx->r4, 0X18B8);
    after_15:
    // 0x80047000: lui         $t1, 0x8015
    ctx->r9 = S32(0X8015 << 16);
    // 0x80047004: lw          $t1, 0x197C($t1)
    ctx->r9 = MEM_W(ctx->r9, 0X197C);
    // 0x80047008: lui         $at, 0x8015
    ctx->r1 = S32(0X8015 << 16);
    // 0x8004700C: sw          $v0, 0x19A0($at)
    MEM_W(0X19A0, ctx->r1) = ctx->r2;
    // 0x80047010: lui         $at, 0x8015
    ctx->r1 = S32(0X8015 << 16);
    // 0x80047014: lui         $t2, 0x8015
    ctx->r10 = S32(0X8015 << 16);
    // 0x80047018: lw          $t2, 0x1980($t2)
    ctx->r10 = MEM_W(ctx->r10, 0X1980);
    // 0x8004701C: sw          $t1, 0x19AC($at)
    MEM_W(0X19AC, ctx->r1) = ctx->r9;
    // 0x80047020: lui         $at, 0x8015
    ctx->r1 = S32(0X8015 << 16);
    // 0x80047024: lui         $a0, 0x8029
    ctx->r4 = S32(0X8029 << 16);
    // 0x80047028: ori         $a0, $a0, 0xA200
    ctx->r4 = ctx->r4 | 0XA200;
    // 0x8004702C: jal         0x800C5720
    // 0x80047030: sw          $t2, 0x19B0($at)
    MEM_W(0X19B0, ctx->r1) = ctx->r10;
    osVirtualToPhysical_recomp(rdram, ctx);
        goto after_16;
    // 0x80047030: sw          $t2, 0x19B0($at)
    MEM_W(0X19B0, ctx->r1) = ctx->r10;
    after_16:
    // 0x80047034: lui         $t3, 0x8015
    ctx->r11 = S32(0X8015 << 16);
    // 0x80047038: lw          $t3, 0x1970($t3)
    ctx->r11 = MEM_W(ctx->r11, 0X1970);
    // 0x8004703C: lw          $t6, 0x40($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X40);
    // 0x80047040: lui         $at, 0x8015
    ctx->r1 = S32(0X8015 << 16);
    // 0x80047044: subu        $t4, $v0, $t3
    ctx->r12 = SUB32(ctx->r2, ctx->r11);
    // 0x80047048: subu        $t5, $t4, $s1
    ctx->r13 = SUB32(ctx->r12, ctx->r17);
    // 0x8004704C: subu        $t7, $t5, $t6
    ctx->r15 = SUB32(ctx->r13, ctx->r14);
    // 0x80047050: jal         0x80098190
    // 0x80047054: sw          $t7, 0x19D4($at)
    MEM_W(0X19D4, ctx->r1) = ctx->r15;
    GameLoad_LoadCodeseg(rdram, ctx);
        goto after_17;
    // 0x80047054: sw          $t7, 0x19D4($at)
    MEM_W(0X19D4, ctx->r1) = ctx->r15;
    after_17:
    // 0x80047058: lui         $a0, 0xF
    ctx->r4 = S32(0XF << 16);
    // 0x8004705C: lui         $t8, 0x10
    ctx->r24 = S32(0X10 << 16);
    // 0x80047060: addiu       $a0, $a0, 0x6090
    ctx->r4 = ADD32(ctx->r4, 0X6090);
    // 0x80047064: addiu       $t8, $t8, -0x1CE0
    ctx->r24 = ADD32(ctx->r24, -0X1CE0);
    // 0x80047068: subu        $t9, $t8, $a0
    ctx->r25 = SUB32(ctx->r24, ctx->r4);
    // 0x8004706C: addiu       $t1, $t9, 0xF
    ctx->r9 = ADD32(ctx->r25, 0XF);
    // 0x80047070: lui         $a1, 0x8015
    ctx->r5 = S32(0X8015 << 16);
    // 0x80047074: lw          $a1, 0x1984($a1)
    ctx->r5 = MEM_W(ctx->r5, 0X1984);
    // 0x80047078: jal         0x80097EC8
    // 0x8004707C: and         $a2, $t1, $s0
    ctx->r6 = ctx->r9 & ctx->r16;
    func_80097EC8(rdram, ctx);
        goto after_18;
    // 0x8004707C: and         $a2, $t1, $s0
    ctx->r6 = ctx->r9 & ctx->r16;
    after_18:
    // 0x80047080: lui         $a0, 0x10
    ctx->r4 = S32(0X10 << 16);
    // 0x80047084: lui         $t2, 0x16
    ctx->r10 = S32(0X16 << 16);
    // 0x80047088: addiu       $a0, $a0, -0x1CE0
    ctx->r4 = ADD32(ctx->r4, -0X1CE0);
    // 0x8004708C: addiu       $t2, $t2, 0x5C00
    ctx->r10 = ADD32(ctx->r10, 0X5C00);
    // 0x80047090: subu        $t3, $t2, $a0
    ctx->r11 = SUB32(ctx->r10, ctx->r4);
    // 0x80047094: addiu       $t4, $t3, 0xF
    ctx->r12 = ADD32(ctx->r11, 0XF);
    // 0x80047098: and         $a2, $t4, $s0
    ctx->r6 = ctx->r12 & ctx->r16;
    // 0x8004709C: lui         $a1, 0x8015
    ctx->r5 = S32(0X8015 << 16);
    // 0x800470A0: lw          $a1, 0x198C($a1)
    ctx->r5 = MEM_W(ctx->r5, 0X198C);
    // 0x800470A4: jal         0x80097EC8
    // 0x800470A8: sw          $a2, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r6;
    func_80097EC8(rdram, ctx);
        goto after_19;
    // 0x800470A8: sw          $a2, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r6;
    after_19:
    // 0x800470AC: lui         $at, 0x8012
    ctx->r1 = S32(0X8012 << 16);
    // 0x800470B0: sw          $zero, -0x720($at)
    MEM_W(-0X720, ctx->r1) = 0;
    // 0x800470B4: lui         $at, 0x8015
    ctx->r1 = S32(0X8015 << 16);
    // 0x800470B8: addiu       $t5, $zero, 0x2
    ctx->r13 = ADD32(0, 0X2);
    // 0x800470BC: lui         $s1, 0x8015
    ctx->r17 = S32(0X8015 << 16);
    // 0x800470C0: sw          $t5, 0x194C($at)
    MEM_W(0X194C, ctx->r1) = ctx->r13;
    // 0x800470C4: addiu       $s1, $s1, 0x1948
    ctx->r17 = ADD32(ctx->r17, 0X1948);
    // 0x800470C8: sw          $zero, 0x0($s1)
    MEM_W(0X0, ctx->r17) = 0;
    // 0x800470CC: lui         $at, 0x8015
    ctx->r1 = S32(0X8015 << 16);
    // 0x800470D0: addiu       $t6, $zero, 0x1
    ctx->r14 = ADD32(0, 0X1);
    // 0x800470D4: jal         0x80047C38
    // 0x800470D8: sw          $t6, 0x1950($at)
    MEM_W(0X1950, ctx->r1) = ctx->r14;
    SysUtils_TaylorSeries(rdram, ctx);
        goto after_20;
    // 0x800470D8: sw          $t6, 0x1950($at)
    MEM_W(0X1950, ctx->r1) = ctx->r14;
    after_20:
    // 0x800470DC: mtc1        $zero, $f0
    ctx->f0.u32l = 0;
    // 0x800470E0: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x800470E4: mtc1        $at, $f2
    ctx->f2.u32l = ctx->r1;
    // 0x800470E8: lui         $a0, 0x8012
    ctx->r4 = S32(0X8012 << 16);
    // 0x800470EC: mfc1        $a2, $f0
    ctx->r6 = (int32_t)ctx->f0.u32l;
    // 0x800470F0: mfc1        $a3, $f0
    ctx->r7 = (int32_t)ctx->f0.u32l;
    // 0x800470F4: addiu       $a0, $a0, -0x7E0
    ctx->r4 = ADD32(ctx->r4, -0X7E0);
    // 0x800470F8: addiu       $a1, $sp, 0x5C
    ctx->r5 = ADD32(ctx->r29, 0X5C);
    // 0x800470FC: swc1        $f0, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->f0.u32l;
    // 0x80047100: swc1        $f0, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->f0.u32l;
    // 0x80047104: swc1        $f0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->f0.u32l;
    // 0x80047108: swc1        $f0, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->f0.u32l;
    // 0x8004710C: swc1        $f0, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->f0.u32l;
    // 0x80047110: swc1        $f2, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f2.u32l;
    // 0x80047114: jal         0x80048854
    // 0x80047118: swc1        $f2, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->f2.u32l;
    SysUtils_MatrixLookAt(rdram, ctx);
        goto after_21;
    // 0x80047118: swc1        $f2, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->f2.u32l;
    after_21:
    // 0x8004711C: jal         0x800C58F0
    // 0x80047120: nop

    osGetTime_recomp(rdram, ctx);
        goto after_22;
    // 0x80047120: nop

    after_22:
    // 0x80047124: jal         0x80047E44
    // 0x80047128: or          $a0, $v1, $zero
    ctx->r4 = ctx->r3 | 0;
    SysUtils_Srand(rdram, ctx);
        goto after_23;
    // 0x80047128: or          $a0, $v1, $zero
    ctx->r4 = ctx->r3 | 0;
    after_23:
    // 0x8004712C: addiu       $a0, $zero, 0x0
    ctx->r4 = ADD32(0, 0X0);
    // 0x80047130: jal         0x800C5980
    // 0x80047134: addiu       $a1, $zero, 0x0
    ctx->r5 = ADD32(0, 0X0);
    osSetTime_recomp(rdram, ctx);
        goto after_24;
    // 0x80047134: addiu       $a1, $zero, 0x0
    ctx->r5 = ADD32(0, 0X0);
    after_24:
    // 0x80047138: lw          $t7, 0x0($s1)
    ctx->r15 = MEM_W(ctx->r17, 0X0);
    // 0x8004713C: lui         $s0, 0x8015
    ctx->r16 = S32(0X8015 << 16);
    // 0x80047140: addiu       $s0, $s0, 0x42C0
    ctx->r16 = ADD32(ctx->r16, 0X42C0);
    // 0x80047144: sll         $t8, $t7, 2
    ctx->r24 = S32(ctx->r15 << 2);
    // 0x80047148: addu        $t9, $s0, $t8
    ctx->r25 = ADD32(ctx->r16, ctx->r24);
    // 0x8004714C: jal         0x800C59B0
    // 0x80047150: lw          $a0, 0x0($t9)
    ctx->r4 = MEM_W(ctx->r25, 0X0);
    osViSwapBuffer_recomp(rdram, ctx);
        goto after_25;
    // 0x80047150: lw          $a0, 0x0($t9)
    ctx->r4 = MEM_W(ctx->r25, 0X0);
    after_25:
    // 0x80047154: jal         0x8004A130
    // 0x80047158: nop

    SysUtils_ContInitialize(rdram, ctx);
        goto after_26;
    // 0x80047158: nop

    after_26:
    // 0x8004715C: jal         0x80046D2C
    // 0x80047160: nop

    SysMain_GfxInitBuffers(rdram, ctx);
        goto after_27;
    // 0x80047160: nop

    after_27:
    // 0x80047164: jal         0x80046850
    // 0x80047168: nop

    func_80046850(rdram, ctx);
        goto after_28;
    // 0x80047168: nop

    after_28:
    // 0x8004716C: jal         0x800468E0
    // 0x80047170: nop

    func_800468E0(rdram, ctx);
        goto after_29;
    // 0x80047170: nop

    after_29:
    // 0x80047174: jal         0x80046BF4
    // 0x80047178: nop

    SysMain_GfxFullSync(rdram, ctx);
        goto after_30;
    // 0x80047178: nop

    after_30:
    // 0x8004717C: lui         $a0, 0x8015
    ctx->r4 = S32(0X8015 << 16);
    // 0x80047180: jal         0x80046C30
    // 0x80047184: lw          $a0, 0x1940($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X1940);
    SysMain_CreateGfxTask(rdram, ctx);
        goto after_31;
    // 0x80047184: lw          $a0, 0x1940($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X1940);
    after_31:
    // 0x80047188: lui         $a0, 0x8015
    ctx->r4 = S32(0X8015 << 16);
    // 0x8004718C: jal         0x80046CF8
    // 0x80047190: lw          $a0, 0x1940($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X1940);
    SysMain_SendGfxTaskSetMesg(rdram, ctx);
        goto after_32;
    // 0x80047190: lw          $a0, 0x1940($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X1940);
    after_32:
    // 0x80047194: jal         0x80091F50
    // 0x80047198: nop

    func_80091F50(rdram, ctx);
        goto after_33;
    // 0x80047198: nop

    after_33:
    // 0x8004719C: lui         $at, 0x8015
    ctx->r1 = S32(0X8015 << 16);
    // 0x800471A0: lui         $s1, 0x801D
    ctx->r17 = S32(0X801D << 16);
    // 0x800471A4: addiu       $s1, $s1, -0x19C4
    ctx->r17 = ADD32(ctx->r17, -0X19C4);
    // 0x800471A8: sw          $zero, 0x1960($at)
    MEM_W(0X1960, ctx->r1) = 0;
L_800471AC:
    // 0x800471AC: lui         $a0, 0x8015
    ctx->r4 = S32(0X8015 << 16);
    // 0x800471B0: jal         0x800C5A00
    // 0x800471B4: addiu       $a0, $a0, 0x40D0
    ctx->r4 = ADD32(ctx->r4, 0X40D0);
    osContStartReadData_recomp(rdram, ctx);
        goto after_34;
    // 0x800471B4: addiu       $a0, $a0, 0x40D0
    ctx->r4 = ADD32(ctx->r4, 0X40D0);
    after_34:
    // 0x800471B8: lui         $a0, 0x8015
    ctx->r4 = S32(0X8015 << 16);
    // 0x800471BC: lui         $a1, 0x8015
    ctx->r5 = S32(0X8015 << 16);
    // 0x800471C0: addiu       $a1, $a1, 0x1958
    ctx->r5 = ADD32(ctx->r5, 0X1958);
    // 0x800471C4: addiu       $a0, $a0, 0x4100
    ctx->r4 = ADD32(ctx->r4, 0X4100);
    // 0x800471C8: jal         0x800C5C60
    // 0x800471CC: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    osRecvMesg_recomp(rdram, ctx);
        goto after_35;
    // 0x800471CC: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    after_35:
    // 0x800471D0: jal         0x80047B00
    // 0x800471D4: nop

    n_alSeqpDelete(rdram, ctx);
        goto after_36;
    // 0x800471D4: nop

    after_36:
    // 0x800471D8: jal         0x80046D2C
    // 0x800471DC: nop

    SysMain_GfxInitBuffers(rdram, ctx);
        goto after_37;
    // 0x800471DC: nop

    after_37:
    // 0x800471E0: jal         0x800922E4
    // 0x800471E4: nop

    func_800922E4(rdram, ctx);
        goto after_38;
    // 0x800471E4: nop

    after_38:
    // 0x800471E8: jal         0x80046850
    // 0x800471EC: nop

    func_80046850(rdram, ctx);
        goto after_39;
    // 0x800471EC: nop

    after_39:
    // 0x800471F0: jal         0x800468E0
    // 0x800471F4: nop

    func_800468E0(rdram, ctx);
        goto after_40;
    // 0x800471F4: nop

    after_40:
    // 0x800471F8: lui         $a0, 0x8015
    ctx->r4 = S32(0X8015 << 16);
    // 0x800471FC: jal         0x80092CF0
    // 0x80047200: lw          $a0, 0x1944($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X1944);
    func_80092CF0(rdram, ctx);
        goto after_41;
    // 0x80047200: lw          $a0, 0x1944($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X1944);
    after_41:
    // 0x80047204: lui         $at, 0x8015
    ctx->r1 = S32(0X8015 << 16);
    // 0x80047208: jal         0x80046BF4
    // 0x8004720C: sw          $v0, 0x1944($at)
    MEM_W(0X1944, ctx->r1) = ctx->r2;
    SysMain_GfxFullSync(rdram, ctx);
        goto after_42;
    // 0x8004720C: sw          $v0, 0x1944($at)
    MEM_W(0X1944, ctx->r1) = ctx->r2;
    after_42:
    // 0x80047210: lui         $a0, 0x8015
    ctx->r4 = S32(0X8015 << 16);
    // 0x80047214: lui         $a1, 0x8015
    ctx->r5 = S32(0X8015 << 16);
    // 0x80047218: addiu       $a1, $a1, 0x195C
    ctx->r5 = ADD32(ctx->r5, 0X195C);
    // 0x8004721C: addiu       $a0, $a0, 0x4118
    ctx->r4 = ADD32(ctx->r4, 0X4118);
    // 0x80047220: jal         0x800C5C60
    // 0x80047224: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    osRecvMesg_recomp(rdram, ctx);
        goto after_43;
    // 0x80047224: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    after_43:
    // 0x80047228: jal         0x800C5DA0
    // 0x8004722C: nop

    osDpGetStatus_recomp(rdram, ctx);
        goto after_44;
    // 0x8004722C: nop

    after_44:
    // 0x80047230: andi        $t1, $v0, 0x170
    ctx->r9 = ctx->r2 & 0X170;
    // 0x80047234: beq         $t1, $zero, L_80047250
    if (ctx->r9 == 0) {
        // 0x80047238: nop
    
            goto L_80047250;
    }
    // 0x80047238: nop

L_8004723C:
    // 0x8004723C: jal         0x800C5DA0
    // 0x80047240: nop

    osDpGetStatus_recomp(rdram, ctx);
        goto after_45;
    // 0x80047240: nop

    after_45:
    // 0x80047244: andi        $t2, $v0, 0x170
    ctx->r10 = ctx->r2 & 0X170;
    // 0x80047248: bne         $t2, $zero, L_8004723C
    if (ctx->r10 != 0) {
        // 0x8004724C: nop
    
            goto L_8004723C;
    }
    // 0x8004724C: nop

L_80047250:
    // 0x80047250: lui         $t3, 0x801D
    ctx->r11 = S32(0X801D << 16);
    // 0x80047254: lw          $t3, -0x19CC($t3)
    ctx->r11 = MEM_W(ctx->r11, -0X19CC);
    // 0x80047258: addiu       $at, $zero, 0x6
    ctx->r1 = ADD32(0, 0X6);
    // 0x8004725C: bnel        $t3, $at, L_80047288
    if (ctx->r11 != ctx->r1) {
        // 0x80047260: lw          $v0, 0x0($s1)
        ctx->r2 = MEM_W(ctx->r17, 0X0);
            goto L_80047288;
    }
    goto skip_0;
    // 0x80047260: lw          $v0, 0x0($s1)
    ctx->r2 = MEM_W(ctx->r17, 0X0);
    skip_0:
    // 0x80047264: lw          $t4, 0x0($s1)
    ctx->r12 = MEM_W(ctx->r17, 0X0);
    // 0x80047268: lui         $a0, 0x10
    ctx->r4 = S32(0X10 << 16);
    // 0x8004726C: addiu       $a0, $a0, -0x1CE0
    ctx->r4 = ADD32(ctx->r4, -0X1CE0);
    // 0x80047270: beq         $t4, $zero, L_80047284
    if (ctx->r12 == 0) {
        // 0x80047274: lui         $a1, 0x8015
        ctx->r5 = S32(0X8015 << 16);
            goto L_80047284;
    }
    // 0x80047274: lui         $a1, 0x8015
    ctx->r5 = S32(0X8015 << 16);
    // 0x80047278: lw          $a1, 0x198C($a1)
    ctx->r5 = MEM_W(ctx->r5, 0X198C);
    // 0x8004727C: jal         0x80097EC8
    // 0x80047280: lw          $a2, 0x44($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X44);
    func_80097EC8(rdram, ctx);
        goto after_46;
    // 0x80047280: lw          $a2, 0x44($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X44);
    after_46:
L_80047284:
    // 0x80047284: lw          $v0, 0x0($s1)
    ctx->r2 = MEM_W(ctx->r17, 0X0);
L_80047288:
    // 0x80047288: beq         $v0, $zero, L_8004729C
    if (ctx->r2 == 0) {
        // 0x8004728C: nop
    
            goto L_8004729C;
    }
    // 0x8004728C: nop

    // 0x80047290: jal         0x80095050
    // 0x80047294: nop

    unk_game_load(rdram, ctx);
        goto after_47;
    // 0x80047294: nop

    after_47:
    // 0x80047298: lw          $v0, 0x0($s1)
    ctx->r2 = MEM_W(ctx->r17, 0X0);
L_8004729C:
    // 0x8004729C: beq         $v0, $zero, L_800472AC
    if (ctx->r2 == 0) {
        // 0x800472A0: nop
    
            goto L_800472AC;
    }
    // 0x800472A0: nop

    // 0x800472A4: jal         0x80098208
    // 0x800472A8: nop

    GameLoad_LoadOverlay(rdram, ctx);
        goto after_48;
    // 0x800472A8: nop

    after_48:
L_800472AC:
    // 0x800472AC: jal         0x80097E68
    // 0x800472B0: nop

    func_80097E68(rdram, ctx);
        goto after_49;
    // 0x800472B0: nop

    after_49:
    // 0x800472B4: lui         $a0, 0x8015
    ctx->r4 = S32(0X8015 << 16);
    // 0x800472B8: jal         0x80046C30
    // 0x800472BC: lw          $a0, 0x1940($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X1940);
    SysMain_CreateGfxTask(rdram, ctx);
        goto after_50;
    // 0x800472BC: lw          $a0, 0x1940($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X1940);
    after_50:
    // 0x800472C0: lui         $t5, 0x800E
    ctx->r13 = S32(0X800E << 16);
    // 0x800472C4: lw          $t5, -0x54E4($t5)
    ctx->r13 = MEM_W(ctx->r13, -0X54E4);
    // 0x800472C8: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x800472CC: lui         $t6, 0x8015
    ctx->r14 = S32(0X8015 << 16);
    // 0x800472D0: bne         $t5, $at, L_80047328
    if (ctx->r13 != ctx->r1) {
        // 0x800472D4: nop
    
            goto L_80047328;
    }
    // 0x800472D4: nop

    // 0x800472D8: lw          $t6, 0x194C($t6)
    ctx->r14 = MEM_W(ctx->r14, 0X194C);
    // 0x800472DC: lw          $a0, 0xC($s0)
    ctx->r4 = MEM_W(ctx->r16, 0XC);
    // 0x800472E0: lui         $at, 0x2
    ctx->r1 = S32(0X2 << 16);
    // 0x800472E4: sll         $t7, $t6, 2
    ctx->r15 = S32(ctx->r14 << 2);
    // 0x800472E8: addu        $t8, $s0, $t7
    ctx->r24 = ADD32(ctx->r16, ctx->r15);
    // 0x800472EC: lw          $v1, 0x0($t8)
    ctx->r3 = MEM_W(ctx->r24, 0X0);
    // 0x800472F0: ori         $at, $at, 0x57FC
    ctx->r1 = ctx->r1 | 0X57FC;
    // 0x800472F4: addu        $v0, $a0, $at
    ctx->r2 = ADD32(ctx->r4, ctx->r1);
    // 0x800472F8: addu        $v1, $v1, $at
    ctx->r3 = ADD32(ctx->r3, ctx->r1);
    // 0x800472FC: sltu        $at, $v0, $a0
    ctx->r1 = ctx->r2 < ctx->r4 ? 1 : 0;
    // 0x80047300: bne         $at, $zero, L_80047328
    if (ctx->r1 != 0) {
        // 0x80047304: nop
    
            goto L_80047328;
    }
    // 0x80047304: nop

    // 0x80047308: lw          $t9, 0x0($v1)
    ctx->r25 = MEM_W(ctx->r3, 0X0);
L_8004730C:
    // 0x8004730C: addiu       $v0, $v0, -0x4
    ctx->r2 = ADD32(ctx->r2, -0X4);
    // 0x80047310: addiu       $v1, $v1, -0x4
    ctx->r3 = ADD32(ctx->r3, -0X4);
    // 0x80047314: sw          $t9, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r25;
    // 0x80047318: lw          $t1, 0xC($s0)
    ctx->r9 = MEM_W(ctx->r16, 0XC);
    // 0x8004731C: sltu        $at, $v0, $t1
    ctx->r1 = ctx->r2 < ctx->r9 ? 1 : 0;
    // 0x80047320: beql        $at, $zero, L_8004730C
    if (ctx->r1 == 0) {
        // 0x80047324: lw          $t9, 0x0($v1)
        ctx->r25 = MEM_W(ctx->r3, 0X0);
            goto L_8004730C;
    }
    goto skip_1;
    // 0x80047324: lw          $t9, 0x0($v1)
    ctx->r25 = MEM_W(ctx->r3, 0X0);
    skip_1:
L_80047328:
    // 0x80047328: lui         $a0, 0x8015
    ctx->r4 = S32(0X8015 << 16);
    // 0x8004732C: jal         0x80046CF8
    // 0x80047330: lw          $a0, 0x1940($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X1940);
    SysMain_SendGfxTaskSetMesg(rdram, ctx);
        goto after_51;
    // 0x80047330: lw          $a0, 0x1940($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X1940);
    after_51:
    // 0x80047334: lui         $t2, 0x800E
    ctx->r10 = S32(0X800E << 16);
    // 0x80047338: lw          $t2, -0x54E4($t2)
    ctx->r10 = MEM_W(ctx->r10, -0X54E4);
    // 0x8004733C: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x80047340: lui         $t3, 0x800E
    ctx->r11 = S32(0X800E << 16);
    // 0x80047344: bne         $t2, $at, L_800473C8
    if (ctx->r10 != ctx->r1) {
        // 0x80047348: lui         $t8, 0x801D
        ctx->r24 = S32(0X801D << 16);
            goto L_800473C8;
    }
    // 0x80047348: lui         $t8, 0x801D
    ctx->r24 = S32(0X801D << 16);
    // 0x8004734C: lw          $t3, -0x54DC($t3)
    ctx->r11 = MEM_W(ctx->r11, -0X54DC);
    // 0x80047350: addiu       $at, $zero, 0x5
    ctx->r1 = ADD32(0, 0X5);
    // 0x80047354: bne         $t3, $at, L_800473A4
    if (ctx->r11 != ctx->r1) {
        // 0x80047358: nop
    
            goto L_800473A4;
    }
    // 0x80047358: nop

    // 0x8004735C: lw          $t4, 0x0($s1)
    ctx->r12 = MEM_W(ctx->r17, 0X0);
    // 0x80047360: lui         $t5, 0x8000
    ctx->r13 = S32(0X8000 << 16);
    // 0x80047364: beq         $t4, $zero, L_800473A4
    if (ctx->r12 == 0) {
        // 0x80047368: nop
    
            goto L_800473A4;
    }
    // 0x80047368: nop

    // 0x8004736C: lw          $t5, 0x300($t5)
    ctx->r13 = MEM_W(ctx->r13, 0X300);
    // 0x80047370: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x80047374: lui         $a0, 0x800F
    ctx->r4 = S32(0X800F << 16);
    // 0x80047378: bne         $t5, $at, L_80047394
    if (ctx->r13 != ctx->r1) {
        // 0x8004737C: nop
    
            goto L_80047394;
    }
    // 0x8004737C: nop

    // 0x80047380: lui         $a0, 0x800F
    ctx->r4 = S32(0X800F << 16);
    // 0x80047384: jal         0x800C5DF0
    // 0x80047388: addiu       $a0, $a0, -0x7660
    ctx->r4 = ADD32(ctx->r4, -0X7660);
    osViSetMode_recomp(rdram, ctx);
        goto after_52;
    // 0x80047388: addiu       $a0, $a0, -0x7660
    ctx->r4 = ADD32(ctx->r4, -0X7660);
    after_52:
    // 0x8004738C: b           L_8004739C
    // 0x80047390: nop

        goto L_8004739C;
    // 0x80047390: nop

L_80047394:
    // 0x80047394: jal         0x800C5DF0
    // 0x80047398: addiu       $a0, $a0, -0x7200
    ctx->r4 = ADD32(ctx->r4, -0X7200);
    osViSetMode_recomp(rdram, ctx);
        goto after_53;
    // 0x80047398: addiu       $a0, $a0, -0x7200
    ctx->r4 = ADD32(ctx->r4, -0X7200);
    after_53:
L_8004739C:
    // 0x8004739C: jal         0x800C5E60
    // 0x800473A0: addiu       $a0, $zero, 0x6
    ctx->r4 = ADD32(0, 0X6);
    osViSetSpecialFeatures_recomp(rdram, ctx);
        goto after_54;
    // 0x800473A0: addiu       $a0, $zero, 0x6
    ctx->r4 = ADD32(0, 0X6);
    after_54:
L_800473A4:
    // 0x800473A4: lui         $t6, 0x800D
    ctx->r14 = S32(0X800D << 16);
    // 0x800473A8: lw          $t6, 0x45D8($t6)
    ctx->r14 = MEM_W(ctx->r14, 0X45D8);
    // 0x800473AC: lui         $a0, 0x800D
    ctx->r4 = S32(0X800D << 16);
    // 0x800473B0: sll         $t7, $t6, 2
    ctx->r15 = S32(ctx->r14 << 2);
    // 0x800473B4: addu        $a0, $a0, $t7
    ctx->r4 = ADD32(ctx->r4, ctx->r15);
    // 0x800473B8: jal         0x800C59B0
    // 0x800473BC: lw          $a0, 0x45DC($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X45DC);
    osViSwapBuffer_recomp(rdram, ctx);
        goto after_55;
    // 0x800473BC: lw          $a0, 0x45DC($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X45DC);
    after_55:
    // 0x800473C0: b           L_80047438
    // 0x800473C4: nop

        goto L_80047438;
    // 0x800473C4: nop

L_800473C8:
    // 0x800473C8: lw          $t8, -0x19CC($t8)
    ctx->r24 = MEM_W(ctx->r24, -0X19CC);
    // 0x800473CC: addiu       $at, $zero, 0x6
    ctx->r1 = ADD32(0, 0X6);
    // 0x800473D0: bne         $t8, $at, L_80047420
    if (ctx->r24 != ctx->r1) {
        // 0x800473D4: nop
    
            goto L_80047420;
    }
    // 0x800473D4: nop

    // 0x800473D8: lw          $t9, 0x0($s1)
    ctx->r25 = MEM_W(ctx->r17, 0X0);
    // 0x800473DC: lui         $t1, 0x8000
    ctx->r9 = S32(0X8000 << 16);
    // 0x800473E0: beq         $t9, $zero, L_80047420
    if (ctx->r25 == 0) {
        // 0x800473E4: nop
    
            goto L_80047420;
    }
    // 0x800473E4: nop

    // 0x800473E8: lw          $t1, 0x300($t1)
    ctx->r9 = MEM_W(ctx->r9, 0X300);
    // 0x800473EC: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x800473F0: lui         $a0, 0x800F
    ctx->r4 = S32(0X800F << 16);
    // 0x800473F4: bne         $t1, $at, L_80047410
    if (ctx->r9 != ctx->r1) {
        // 0x800473F8: nop
    
            goto L_80047410;
    }
    // 0x800473F8: nop

    // 0x800473FC: lui         $a0, 0x800F
    ctx->r4 = S32(0X800F << 16);
    // 0x80047400: jal         0x800C5DF0
    // 0x80047404: addiu       $a0, $a0, -0x7890
    ctx->r4 = ADD32(ctx->r4, -0X7890);
    osViSetMode_recomp(rdram, ctx);
        goto after_56;
    // 0x80047404: addiu       $a0, $a0, -0x7890
    ctx->r4 = ADD32(ctx->r4, -0X7890);
    after_56:
    // 0x80047408: b           L_80047418
    // 0x8004740C: nop

        goto L_80047418;
    // 0x8004740C: nop

L_80047410:
    // 0x80047410: jal         0x800C5DF0
    // 0x80047414: addiu       $a0, $a0, -0x7430
    ctx->r4 = ADD32(ctx->r4, -0X7430);
    osViSetMode_recomp(rdram, ctx);
        goto after_57;
    // 0x80047414: addiu       $a0, $a0, -0x7430
    ctx->r4 = ADD32(ctx->r4, -0X7430);
    after_57:
L_80047418:
    // 0x80047418: jal         0x800C5E60
    // 0x8004741C: addiu       $a0, $zero, 0x66
    ctx->r4 = ADD32(0, 0X66);
    osViSetSpecialFeatures_recomp(rdram, ctx);
        goto after_58;
    // 0x8004741C: addiu       $a0, $zero, 0x66
    ctx->r4 = ADD32(0, 0X66);
    after_58:
L_80047420:
    // 0x80047420: lui         $t2, 0x8015
    ctx->r10 = S32(0X8015 << 16);
    // 0x80047424: lw          $t2, 0x194C($t2)
    ctx->r10 = MEM_W(ctx->r10, 0X194C);
    // 0x80047428: sll         $t3, $t2, 2
    ctx->r11 = S32(ctx->r10 << 2);
    // 0x8004742C: addu        $t4, $s0, $t3
    ctx->r12 = ADD32(ctx->r16, ctx->r11);
    // 0x80047430: jal         0x800C59B0
    // 0x80047434: lw          $a0, 0x0($t4)
    ctx->r4 = MEM_W(ctx->r12, 0X0);
    osViSwapBuffer_recomp(rdram, ctx);
        goto after_59;
    // 0x80047434: lw          $a0, 0x0($t4)
    ctx->r4 = MEM_W(ctx->r12, 0X0);
    after_59:
L_80047438:
    // 0x80047438: lui         $v0, 0x8015
    ctx->r2 = S32(0X8015 << 16);
    // 0x8004743C: addiu       $v0, $v0, 0x1960
    ctx->r2 = ADD32(ctx->r2, 0X1960);
    // 0x80047440: lw          $t5, 0x0($v0)
    ctx->r13 = MEM_W(ctx->r2, 0X0);
    // 0x80047444: addiu       $t6, $t5, 0x1
    ctx->r14 = ADD32(ctx->r13, 0X1);
    // 0x80047448: b           L_800471AC
    // 0x8004744C: sw          $t6, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r14;
        goto L_800471AC;
    // 0x8004744C: sw          $t6, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r14;
    // 0x80047450: lw          $ra, 0x3C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X3C);
    // 0x80047454: lw          $s0, 0x34($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X34);
    // 0x80047458: lw          $s1, 0x38($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X38);
    // 0x8004745C: jr          $ra
    // 0x80047460: addiu       $sp, $sp, 0xA0
    ctx->r29 = ADD32(ctx->r29, 0XA0);
    return;
    // 0x80047460: addiu       $sp, $sp, 0xA0
    ctx->r29 = ADD32(ctx->r29, 0XA0);
    // 0x80047464: nop

    // 0x80047468: nop

    // 0x8004746C: nop

;}
RECOMP_FUNC void func_80047470(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x80047470: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x80047474: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x80047478: jal         0x800C6020
    // 0x8004747C: nop

    osSpTaskYield_recomp(rdram, ctx);
        goto after_0;
    // 0x8004747C: nop

    after_0:
    // 0x80047480: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x80047484: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
    // 0x80047488: lui         $at, 0x800D
    ctx->r1 = S32(0X800D << 16);
    // 0x8004748C: sw          $v0, 0x4600($at)
    MEM_W(0X4600, ctx->r1) = ctx->r2;
    // 0x80047490: lui         $at, 0x800D
    ctx->r1 = S32(0X800D << 16);
    // 0x80047494: sw          $v0, 0x4604($at)
    MEM_W(0X4604, ctx->r1) = ctx->r2;
    // 0x80047498: jr          $ra
    // 0x8004749C: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    return;
    // 0x8004749C: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
;}
RECOMP_FUNC void func_800474A0(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800474A0: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800474A4: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800474A8: lui         $a0, 0x8015
    ctx->r4 = S32(0X8015 << 16);
    // 0x800474AC: jal         0x800C615C
    // 0x800474B0: lw          $a0, 0x42B8($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X42B8);
    osSpTaskLoad_recomp(rdram, ctx);
        goto after_0;
    // 0x800474B0: lw          $a0, 0x42B8($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X42B8);
    after_0:
    // 0x800474B4: lui         $a0, 0x8015
    ctx->r4 = S32(0X8015 << 16);
    // 0x800474B8: jal         0x800C62BC
    // 0x800474BC: lw          $a0, 0x42B8($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X42B8);
    osSpTaskStartGo_recomp(rdram, ctx);
        goto after_1;
    // 0x800474BC: lw          $a0, 0x42B8($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X42B8);
    after_1:
    // 0x800474C0: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800474C4: addiu       $t6, $zero, 0x2
    ctx->r14 = ADD32(0, 0X2);
    // 0x800474C8: lui         $at, 0x800D
    ctx->r1 = S32(0X800D << 16);
    // 0x800474CC: sw          $t6, 0x4600($at)
    MEM_W(0X4600, ctx->r1) = ctx->r14;
    // 0x800474D0: lui         $at, 0x800D
    ctx->r1 = S32(0X800D << 16);
    // 0x800474D4: addiu       $t7, $zero, 0x1
    ctx->r15 = ADD32(0, 0X1);
    // 0x800474D8: sw          $t7, 0x4604($at)
    MEM_W(0X4604, ctx->r1) = ctx->r15;
    // 0x800474DC: jr          $ra
    // 0x800474E0: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    return;
    // 0x800474E0: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
;}
RECOMP_FUNC void func_800474E4(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800474E4: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800474E8: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800474EC: jal         0x800C6300
    // 0x800474F0: addiu       $a0, $zero, 0x3C0
    ctx->r4 = ADD32(0, 0X3C0);
    osDpSetStatus_recomp(rdram, ctx);
        goto after_0;
    // 0x800474F0: addiu       $a0, $zero, 0x3C0
    ctx->r4 = ADD32(0, 0X3C0);
    after_0:
    // 0x800474F4: lui         $a0, 0x8015
    ctx->r4 = S32(0X8015 << 16);
    // 0x800474F8: jal         0x800C615C
    // 0x800474FC: lw          $a0, 0x42B4($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X42B4);
    osSpTaskLoad_recomp(rdram, ctx);
        goto after_1;
    // 0x800474FC: lw          $a0, 0x42B4($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X42B4);
    after_1:
    // 0x80047500: lui         $a0, 0x8015
    ctx->r4 = S32(0X8015 << 16);
    // 0x80047504: jal         0x800C62BC
    // 0x80047508: lw          $a0, 0x42B4($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X42B4);
    osSpTaskStartGo_recomp(rdram, ctx);
        goto after_2;
    // 0x80047508: lw          $a0, 0x42B4($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X42B4);
    after_2:
    // 0x8004750C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x80047510: addiu       $t6, $zero, 0x3
    ctx->r14 = ADD32(0, 0X3);
    // 0x80047514: lui         $at, 0x800D
    ctx->r1 = S32(0X800D << 16);
    // 0x80047518: sw          $t6, 0x4600($at)
    MEM_W(0X4600, ctx->r1) = ctx->r14;
    // 0x8004751C: lui         $at, 0x800D
    ctx->r1 = S32(0X800D << 16);
    // 0x80047520: addiu       $t7, $zero, 0x1
    ctx->r15 = ADD32(0, 0X1);
    // 0x80047524: sw          $t7, 0x4604($at)
    MEM_W(0X4604, ctx->r1) = ctx->r15;
    // 0x80047528: jr          $ra
    // 0x8004752C: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    return;
    // 0x8004752C: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
;}
RECOMP_FUNC void main_thread(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x80047530: addiu       $sp, $sp, -0x50
    ctx->r29 = ADD32(ctx->r29, -0X50);
    // 0x80047534: sw          $a0, 0x50($sp)
    MEM_W(0X50, ctx->r29) = ctx->r4;
    // 0x80047538: sw          $ra, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r31;
    // 0x8004753C: lui         $a0, 0x8015
    ctx->r4 = S32(0X8015 << 16);
    // 0x80047540: lui         $a1, 0x8015
    ctx->r5 = S32(0X8015 << 16);
    // 0x80047544: sw          $s7, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r23;
    // 0x80047548: sw          $s6, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r22;
    // 0x8004754C: sw          $s5, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r21;
    // 0x80047550: sw          $s4, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r20;
    // 0x80047554: sw          $s3, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r19;
    // 0x80047558: sw          $s2, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r18;
    // 0x8004755C: sw          $s1, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r17;
    // 0x80047560: sw          $s0, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r16;
    // 0x80047564: addiu       $a1, $a1, 0x4248
    ctx->r5 = ADD32(ctx->r5, 0X4248);
    // 0x80047568: addiu       $a0, $a0, 0x40B8
    ctx->r4 = ADD32(ctx->r4, 0X40B8);
    // 0x8004756C: jal         0x800C6310
    // 0x80047570: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    osCreateMesgQueue_recomp(rdram, ctx);
        goto after_0;
    // 0x80047570: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    after_0:
    // 0x80047574: lui         $s0, 0x8015
    ctx->r16 = S32(0X8015 << 16);
    // 0x80047578: addiu       $s0, $s0, 0x40D0
    ctx->r16 = ADD32(ctx->r16, 0X40D0);
    // 0x8004757C: lui         $a1, 0x8015
    ctx->r5 = S32(0X8015 << 16);
    // 0x80047580: addiu       $a1, $a1, 0x424C
    ctx->r5 = ADD32(ctx->r5, 0X424C);
    // 0x80047584: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x80047588: jal         0x800C6310
    // 0x8004758C: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    osCreateMesgQueue_recomp(rdram, ctx);
        goto after_1;
    // 0x8004758C: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    after_1:
    // 0x80047590: lui         $a0, 0x8015
    ctx->r4 = S32(0X8015 << 16);
    // 0x80047594: lui         $a1, 0x8015
    ctx->r5 = S32(0X8015 << 16);
    // 0x80047598: addiu       $a1, $a1, 0x4250
    ctx->r5 = ADD32(ctx->r5, 0X4250);
    // 0x8004759C: addiu       $a0, $a0, 0x40E8
    ctx->r4 = ADD32(ctx->r4, 0X40E8);
    // 0x800475A0: jal         0x800C6310
    // 0x800475A4: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    osCreateMesgQueue_recomp(rdram, ctx);
        goto after_2;
    // 0x800475A4: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    after_2:
    // 0x800475A8: lui         $a0, 0x8015
    ctx->r4 = S32(0X8015 << 16);
    // 0x800475AC: lui         $a1, 0x8015
    ctx->r5 = S32(0X8015 << 16);
    // 0x800475B0: addiu       $a1, $a1, 0x4254
    ctx->r5 = ADD32(ctx->r5, 0X4254);
    // 0x800475B4: addiu       $a0, $a0, 0x4100
    ctx->r4 = ADD32(ctx->r4, 0X4100);
    // 0x800475B8: jal         0x800C6310
    // 0x800475BC: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    osCreateMesgQueue_recomp(rdram, ctx);
        goto after_3;
    // 0x800475BC: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    after_3:
    // 0x800475C0: lui         $a0, 0x8015
    ctx->r4 = S32(0X8015 << 16);
    // 0x800475C4: lui         $a1, 0x8015
    ctx->r5 = S32(0X8015 << 16);
    // 0x800475C8: addiu       $a1, $a1, 0x4258
    ctx->r5 = ADD32(ctx->r5, 0X4258);
    // 0x800475CC: addiu       $a0, $a0, 0x4118
    ctx->r4 = ADD32(ctx->r4, 0X4118);
    // 0x800475D0: jal         0x800C6310
    // 0x800475D4: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    osCreateMesgQueue_recomp(rdram, ctx);
        goto after_4;
    // 0x800475D4: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    after_4:
    // 0x800475D8: lui         $a0, 0x8015
    ctx->r4 = S32(0X8015 << 16);
    // 0x800475DC: lui         $a1, 0x8015
    ctx->r5 = S32(0X8015 << 16);
    // 0x800475E0: addiu       $a1, $a1, 0x4260
    ctx->r5 = ADD32(ctx->r5, 0X4260);
    // 0x800475E4: addiu       $a0, $a0, 0x4130
    ctx->r4 = ADD32(ctx->r4, 0X4130);
    // 0x800475E8: jal         0x800C6310
    // 0x800475EC: addiu       $a2, $zero, 0x10
    ctx->r6 = ADD32(0, 0X10);
    osCreateMesgQueue_recomp(rdram, ctx);
        goto after_5;
    // 0x800475EC: addiu       $a2, $zero, 0x10
    ctx->r6 = ADD32(0, 0X10);
    after_5:
    // 0x800475F0: addiu       $a0, $zero, 0x5
    ctx->r4 = ADD32(0, 0X5);
    // 0x800475F4: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    // 0x800475F8: jal         0x800C6340
    // 0x800475FC: addiu       $a2, $zero, 0xB
    ctx->r6 = ADD32(0, 0XB);
    osSetEventMesg_recomp(rdram, ctx);
        goto after_6;
    // 0x800475FC: addiu       $a2, $zero, 0xB
    ctx->r6 = ADD32(0, 0XB);
    after_6:
    // 0x80047600: lui         $a1, 0x8015
    ctx->r5 = S32(0X8015 << 16);
    // 0x80047604: addiu       $a1, $a1, 0x4130
    ctx->r5 = ADD32(ctx->r5, 0X4130);
    // 0x80047608: addiu       $a0, $zero, 0x4
    ctx->r4 = ADD32(0, 0X4);
    // 0x8004760C: jal         0x800C6340
    // 0x80047610: addiu       $a2, $zero, 0x17
    ctx->r6 = ADD32(0, 0X17);
    osSetEventMesg_recomp(rdram, ctx);
        goto after_7;
    // 0x80047610: addiu       $a2, $zero, 0x17
    ctx->r6 = ADD32(0, 0X17);
    after_7:
    // 0x80047614: lui         $a1, 0x8015
    ctx->r5 = S32(0X8015 << 16);
    // 0x80047618: addiu       $a1, $a1, 0x4130
    ctx->r5 = ADD32(ctx->r5, 0X4130);
    // 0x8004761C: addiu       $a0, $zero, 0x9
    ctx->r4 = ADD32(0, 0X9);
    // 0x80047620: jal         0x800C6340
    // 0x80047624: addiu       $a2, $zero, 0x18
    ctx->r6 = ADD32(0, 0X18);
    osSetEventMesg_recomp(rdram, ctx);
        goto after_8;
    // 0x80047624: addiu       $a2, $zero, 0x18
    ctx->r6 = ADD32(0, 0X18);
    after_8:
    // 0x80047628: lui         $a0, 0x8015
    ctx->r4 = S32(0X8015 << 16);
    // 0x8004762C: addiu       $a0, $a0, 0x4130
    ctx->r4 = ADD32(ctx->r4, 0X4130);
    // 0x80047630: addiu       $a1, $zero, 0x19
    ctx->r5 = ADD32(0, 0X19);
    // 0x80047634: jal         0x800C63B0
    // 0x80047638: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    osViSetEvent_recomp(rdram, ctx);
        goto after_9;
    // 0x80047638: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    after_9:
    // 0x8004763C: jal         0x800980C8
    // 0x80047640: nop

    func_800980C8(rdram, ctx);
        goto after_10;
    // 0x80047640: nop

    after_10:
    // 0x80047644: lui         $s0, 0x8015
    ctx->r16 = S32(0X8015 << 16);
    // 0x80047648: lui         $t6, 0x8015
    ctx->r14 = S32(0X8015 << 16);
    // 0x8004764C: addiu       $s0, $s0, 0x3D40
    ctx->r16 = ADD32(ctx->r16, 0X3D40);
    // 0x80047650: addiu       $t6, $t6, 0x39E0
    ctx->r14 = ADD32(ctx->r14, 0X39E0);
    // 0x80047654: lui         $a2, 0x8004
    ctx->r6 = S32(0X8004 << 16);
    // 0x80047658: addiu       $t7, $zero, 0x14
    ctx->r15 = ADD32(0, 0X14);
    // 0x8004765C: sw          $t7, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r15;
    // 0x80047660: addiu       $a2, $a2, 0x7B20
    ctx->r6 = ADD32(ctx->r6, 0X7B20);
    // 0x80047664: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x80047668: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x8004766C: addiu       $a1, $zero, 0x4
    ctx->r5 = ADD32(0, 0X4);
    // 0x80047670: jal         0x800C6420
    // 0x80047674: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    osCreateThread_recomp(rdram, ctx);
        goto after_11;
    // 0x80047674: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_11:
    // 0x80047678: lui         $t8, 0x800D
    ctx->r24 = S32(0X800D << 16);
    // 0x8004767C: lb          $t8, 0x4628($t8)
    ctx->r24 = MEM_B(ctx->r24, 0X4628);
    // 0x80047680: beq         $t8, $zero, L_80047690
    if (ctx->r24 == 0) {
        // 0x80047684: nop
    
            goto L_80047690;
    }
    // 0x80047684: nop

    // 0x80047688: jal         0x800C6570
    // 0x8004768C: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    osStartThread_recomp(rdram, ctx);
        goto after_12;
    // 0x8004768C: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_12:
L_80047690:
    // 0x80047690: lui         $s0, 0x8015
    ctx->r16 = S32(0X8015 << 16);
    // 0x80047694: lui         $t9, 0x8015
    ctx->r25 = S32(0X8015 << 16);
    // 0x80047698: addiu       $s0, $s0, 0x3EF0
    ctx->r16 = ADD32(ctx->r16, 0X3EF0);
    // 0x8004769C: addiu       $t9, $t9, 0x31E0
    ctx->r25 = ADD32(ctx->r25, 0X31E0);
    // 0x800476A0: lui         $a2, 0x8004
    ctx->r6 = S32(0X8004 << 16);
    // 0x800476A4: addiu       $t0, $zero, 0xA
    ctx->r8 = ADD32(0, 0XA);
    // 0x800476A8: sw          $t0, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r8;
    // 0x800476AC: addiu       $a2, $a2, 0x6DA0
    ctx->r6 = ADD32(ctx->r6, 0X6DA0);
    // 0x800476B0: sw          $t9, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r25;
    // 0x800476B4: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x800476B8: addiu       $a1, $zero, 0x5
    ctx->r5 = ADD32(0, 0X5);
    // 0x800476BC: jal         0x800C6420
    // 0x800476C0: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    osCreateThread_recomp(rdram, ctx);
        goto after_13;
    // 0x800476C0: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_13:
    // 0x800476C4: lui         $t1, 0x800D
    ctx->r9 = S32(0X800D << 16);
    // 0x800476C8: lb          $t1, 0x4624($t1)
    ctx->r9 = MEM_B(ctx->r9, 0X4624);
    // 0x800476CC: beq         $t1, $zero, L_800476DC
    if (ctx->r9 == 0) {
        // 0x800476D0: nop
    
            goto L_800476DC;
    }
    // 0x800476D0: nop

    // 0x800476D4: jal         0x800C6570
    // 0x800476D8: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    osStartThread_recomp(rdram, ctx);
        goto after_14;
    // 0x800476D8: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_14:
L_800476DC:
    // 0x800476DC: lui         $s7, 0x800D
    ctx->r23 = S32(0X800D << 16);
    // 0x800476E0: lui         $s6, 0x800D
    ctx->r22 = S32(0X800D << 16);
    // 0x800476E4: lui         $s5, 0x800D
    ctx->r21 = S32(0X800D << 16);
    // 0x800476E8: lui         $s4, 0x800D
    ctx->r20 = S32(0X800D << 16);
    // 0x800476EC: lui         $s3, 0x800D
    ctx->r19 = S32(0X800D << 16);
    // 0x800476F0: lui         $s2, 0x800D
    ctx->r18 = S32(0X800D << 16);
    // 0x800476F4: lui         $s0, 0x800D
    ctx->r16 = S32(0X800D << 16);
    // 0x800476F8: addiu       $s0, $s0, 0x4600
    ctx->r16 = ADD32(ctx->r16, 0X4600);
    // 0x800476FC: addiu       $s2, $s2, 0x4604
    ctx->r18 = ADD32(ctx->r18, 0X4604);
    // 0x80047700: addiu       $s3, $s3, 0x4610
    ctx->r19 = ADD32(ctx->r19, 0X4610);
    // 0x80047704: addiu       $s4, $s4, 0x4608
    ctx->r20 = ADD32(ctx->r20, 0X4608);
    // 0x80047708: addiu       $s5, $s5, 0x460C
    ctx->r21 = ADD32(ctx->r21, 0X460C);
    // 0x8004770C: addiu       $s6, $s6, 0x4614
    ctx->r22 = ADD32(ctx->r22, 0X4614);
    // 0x80047710: addiu       $s7, $s7, 0x4618
    ctx->r23 = ADD32(ctx->r23, 0X4618);
    // 0x80047714: addiu       $s1, $zero, 0x1
    ctx->r17 = ADD32(0, 0X1);
L_80047718:
    // 0x80047718: lui         $a0, 0x8015
    ctx->r4 = S32(0X8015 << 16);
    // 0x8004771C: addiu       $a0, $a0, 0x4130
    ctx->r4 = ADD32(ctx->r4, 0X4130);
    // 0x80047720: addiu       $a1, $sp, 0x4C
    ctx->r5 = ADD32(ctx->r29, 0X4C);
    // 0x80047724: jal         0x800C5C60
    // 0x80047728: or          $a2, $s1, $zero
    ctx->r6 = ctx->r17 | 0;
    osRecvMesg_recomp(rdram, ctx);
        goto after_15;
    // 0x80047728: or          $a2, $s1, $zero
    ctx->r6 = ctx->r17 | 0;
    after_15:
    // 0x8004772C: lw          $v1, 0x4C($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X4C);
    // 0x80047730: addiu       $at, $zero, 0x19
    ctx->r1 = ADD32(0, 0X19);
    // 0x80047734: lui         $a0, 0x8015
    ctx->r4 = S32(0X8015 << 16);
    // 0x80047738: bne         $v1, $at, L_80047798
    if (ctx->r3 != ctx->r1) {
        // 0x8004773C: addiu       $a0, $a0, 0x40E8
        ctx->r4 = ADD32(ctx->r4, 0X40E8);
            goto L_80047798;
    }
    // 0x8004773C: addiu       $a0, $a0, 0x40E8
    ctx->r4 = ADD32(ctx->r4, 0X40E8);
    { extern void wr64_achievements_native_frame(uint8_t*); wr64_achievements_native_frame(rdram); }
    // 0x80047740: addiu       $a1, $zero, 0x1F
    ctx->r5 = ADD32(0, 0X1F);
    // 0x80047744: jal         0x800C57A0
    // 0x80047748: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    osSendMesg_recomp(rdram, ctx);
        goto after_16;
    // 0x80047748: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    after_16:
    // 0x8004774C: lw          $t2, 0x0($s3)
    ctx->r10 = MEM_W(ctx->r19, 0X0);
    // 0x80047750: lw          $t4, 0x0($s6)
    ctx->r12 = MEM_W(ctx->r22, 0X0);
    // 0x80047754: lw          $t6, 0x0($s7)
    ctx->r14 = MEM_W(ctx->r23, 0X0);
    // 0x80047758: addiu       $t3, $t2, 0x1
    ctx->r11 = ADD32(ctx->r10, 0X1);
    // 0x8004775C: subu        $t5, $t3, $t4
    ctx->r13 = SUB32(ctx->r11, ctx->r12);
    // 0x80047760: slt         $at, $t5, $t6
    ctx->r1 = SIGNED(ctx->r13) < SIGNED(ctx->r14) ? 1 : 0;
    // 0x80047764: bne         $at, $zero, L_80047718
    if (ctx->r1 != 0) {
        // 0x80047768: sw          $t3, 0x0($s3)
        MEM_W(0X0, ctx->r19) = ctx->r11;
            goto L_80047718;
    }
    // 0x80047768: sw          $t3, 0x0($s3)
    MEM_W(0X0, ctx->r19) = ctx->r11;
    // 0x8004776C: sw          $t3, 0x0($s6)
    MEM_W(0X0, ctx->r22) = ctx->r11;
    // 0x80047770: lui         $t7, 0x800D
    ctx->r15 = S32(0X800D << 16);
    // 0x80047774: lw          $t7, 0x461C($t7)
    ctx->r15 = MEM_W(ctx->r15, 0X461C);
    // 0x80047778: lui         $a0, 0x8015
    ctx->r4 = S32(0X8015 << 16);
    // 0x8004777C: addiu       $a0, $a0, 0x4100
    ctx->r4 = ADD32(ctx->r4, 0X4100);
    // 0x80047780: addiu       $a1, $zero, 0x29
    ctx->r5 = ADD32(0, 0X29);
    // 0x80047784: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x80047788: jal         0x800C57A0
    // 0x8004778C: sw          $t7, 0x0($s7)
    MEM_W(0X0, ctx->r23) = ctx->r15;
    osSendMesg_recomp(rdram, ctx);
        goto after_17;
    // 0x8004778C: sw          $t7, 0x0($s7)
    MEM_W(0X0, ctx->r23) = ctx->r15;
    after_17:
    // 0x80047790: b           L_80047718
    // 0x80047794: nop

        goto L_80047718;
    // 0x80047794: nop

L_80047798:
    // 0x80047798: addiu       $at, $zero, 0x17
    ctx->r1 = ADD32(0, 0X17);
    // 0x8004779C: bnel        $v1, $at, L_80047848
    if (ctx->r3 != ctx->r1) {
        // 0x800477A0: addiu       $at, $zero, 0x16
        ctx->r1 = ADD32(0, 0X16);
            goto L_80047848;
    }
    goto skip_0;
    // 0x800477A0: addiu       $at, $zero, 0x16
    ctx->r1 = ADD32(0, 0X16);
    skip_0:
    // 0x800477A4: lw          $v0, 0x0($s0)
    ctx->r2 = MEM_W(ctx->r16, 0X0);
    // 0x800477A8: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x800477AC: lui         $a0, 0x8015
    ctx->r4 = S32(0X8015 << 16);
    // 0x800477B0: beq         $v0, $s1, L_800477D0
    if (ctx->r2 == ctx->r17) {
        // 0x800477B4: nop
    
            goto L_800477D0;
    }
    // 0x800477B4: nop

    // 0x800477B8: beq         $v0, $at, L_800477F4
    if (ctx->r2 == ctx->r1) {
        // 0x800477BC: addiu       $at, $zero, 0x3
        ctx->r1 = ADD32(0, 0X3);
            goto L_800477F4;
    }
    // 0x800477BC: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x800477C0: beql        $v0, $at, L_8004783C
    if (ctx->r2 == ctx->r1) {
        // 0x800477C4: sw          $zero, 0x0($s0)
        MEM_W(0X0, ctx->r16) = 0;
            goto L_8004783C;
    }
    goto skip_1;
    // 0x800477C4: sw          $zero, 0x0($s0)
    MEM_W(0X0, ctx->r16) = 0;
    skip_1:
    // 0x800477C8: b           L_80047718
    // 0x800477CC: nop

        goto L_80047718;
    // 0x800477CC: nop

L_800477D0:
    // 0x800477D0: jal         0x800C66C0
    // 0x800477D4: lw          $a0, 0x42B4($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X42B4);
    osSpTaskYielded_recomp(rdram, ctx);
        goto after_18;
    // 0x800477D4: lw          $a0, 0x42B4($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X42B4);
    after_18:
    // 0x800477D8: beq         $v0, $zero, L_800477E4
    if (ctx->r2 == 0) {
        // 0x800477DC: nop
    
            goto L_800477E4;
    }
    // 0x800477DC: nop

    // 0x800477E0: sw          $s1, 0x0($s4)
    MEM_W(0X0, ctx->r20) = ctx->r17;
L_800477E4:
    // 0x800477E4: jal         0x800474A0
    // 0x800477E8: nop

    func_800474A0(rdram, ctx);
        goto after_19;
    // 0x800477E8: nop

    after_19:
    // 0x800477EC: b           L_80047718
    // 0x800477F0: nop

        goto L_80047718;
    // 0x800477F0: nop

L_800477F4:
    // 0x800477F4: lw          $t8, 0x0($s4)
    ctx->r24 = MEM_W(ctx->r20, 0X0);
    // 0x800477F8: beql        $t8, $zero, L_80047814
    if (ctx->r24 == 0) {
        // 0x800477FC: lw          $t9, 0x0($s5)
        ctx->r25 = MEM_W(ctx->r21, 0X0);
            goto L_80047814;
    }
    goto skip_2;
    // 0x800477FC: lw          $t9, 0x0($s5)
    ctx->r25 = MEM_W(ctx->r21, 0X0);
    skip_2:
    // 0x80047800: jal         0x800474E4
    // 0x80047804: sw          $zero, 0x0($s4)
    MEM_W(0X0, ctx->r20) = 0;
    func_800474E4(rdram, ctx);
        goto after_20;
    // 0x80047804: sw          $zero, 0x0($s4)
    MEM_W(0X0, ctx->r20) = 0;
    after_20:
    // 0x80047808: b           L_80047718
    // 0x8004780C: nop

        goto L_80047718;
    // 0x8004780C: nop

    // 0x80047810: lw          $t9, 0x0($s5)
    ctx->r25 = MEM_W(ctx->r21, 0X0);
L_80047814:
    // 0x80047814: beql        $t9, $zero, L_80047830
    if (ctx->r25 == 0) {
        // 0x80047818: sw          $zero, 0x0($s0)
        MEM_W(0X0, ctx->r16) = 0;
            goto L_80047830;
    }
    goto skip_3;
    // 0x80047818: sw          $zero, 0x0($s0)
    MEM_W(0X0, ctx->r16) = 0;
    skip_3:
    // 0x8004781C: jal         0x800474E4
    // 0x80047820: sw          $zero, 0x0($s5)
    MEM_W(0X0, ctx->r21) = 0;
    func_800474E4(rdram, ctx);
        goto after_21;
    // 0x80047820: sw          $zero, 0x0($s5)
    MEM_W(0X0, ctx->r21) = 0;
    after_21:
    // 0x80047824: b           L_80047718
    // 0x80047828: nop

        goto L_80047718;
    // 0x80047828: nop

    // 0x8004782C: sw          $zero, 0x0($s0)
    MEM_W(0X0, ctx->r16) = 0;
L_80047830:
    // 0x80047830: b           L_80047718
    // 0x80047834: sw          $zero, 0x0($s2)
    MEM_W(0X0, ctx->r18) = 0;
        goto L_80047718;
    // 0x80047834: sw          $zero, 0x0($s2)
    MEM_W(0X0, ctx->r18) = 0;
    // 0x80047838: sw          $zero, 0x0($s0)
    MEM_W(0X0, ctx->r16) = 0;
L_8004783C:
    // 0x8004783C: b           L_80047718
    // 0x80047840: sw          $zero, 0x0($s2)
    MEM_W(0X0, ctx->r18) = 0;
        goto L_80047718;
    // 0x80047840: sw          $zero, 0x0($s2)
    MEM_W(0X0, ctx->r18) = 0;
    // 0x80047844: addiu       $at, $zero, 0x16
    ctx->r1 = ADD32(0, 0X16);
L_80047848:
    // 0x80047848: bnel        $v1, $at, L_80047894
    if (ctx->r3 != ctx->r1) {
        // 0x8004784C: addiu       $at, $zero, 0x15
        ctx->r1 = ADD32(0, 0X15);
            goto L_80047894;
    }
    goto skip_4;
    // 0x8004784C: addiu       $at, $zero, 0x15
    ctx->r1 = ADD32(0, 0X15);
    skip_4:
    // 0x80047850: jal         0x800C6740
    // 0x80047854: nop

    osWritebackDCacheAll_recomp(rdram, ctx);
        goto after_22;
    // 0x80047854: nop

    after_22:
    // 0x80047858: lw          $t0, 0x0($s2)
    ctx->r8 = MEM_W(ctx->r18, 0X0);
    // 0x8004785C: beq         $t0, $zero, L_80047880
    if (ctx->r8 == 0) {
        // 0x80047860: nop
    
            goto L_80047880;
    }
    // 0x80047860: nop

    // 0x80047864: lw          $t1, 0x0($s0)
    ctx->r9 = MEM_W(ctx->r16, 0X0);
    // 0x80047868: beq         $s1, $t1, L_80047718
    if (ctx->r17 == ctx->r9) {
        // 0x8004786C: nop
    
            goto L_80047718;
    }
    // 0x8004786C: nop

    // 0x80047870: jal         0x80047470
    // 0x80047874: nop

    func_80047470(rdram, ctx);
        goto after_23;
    // 0x80047874: nop

    after_23:
    // 0x80047878: b           L_80047718
    // 0x8004787C: nop

        goto L_80047718;
    // 0x8004787C: nop

L_80047880:
    // 0x80047880: jal         0x800474A0
    // 0x80047884: nop

    func_800474A0(rdram, ctx);
        goto after_24;
    // 0x80047884: nop

    after_24:
    // 0x80047888: b           L_80047718
    // 0x8004788C: nop

        goto L_80047718;
    // 0x8004788C: nop

    // 0x80047890: addiu       $at, $zero, 0x15
    ctx->r1 = ADD32(0, 0X15);
L_80047894:
    // 0x80047894: bnel        $v1, $at, L_800478CC
    if (ctx->r3 != ctx->r1) {
        // 0x80047898: addiu       $at, $zero, 0x18
        ctx->r1 = ADD32(0, 0X18);
            goto L_800478CC;
    }
    goto skip_5;
    // 0x80047898: addiu       $at, $zero, 0x18
    ctx->r1 = ADD32(0, 0X18);
    skip_5:
    // 0x8004789C: jal         0x800C6740
    // 0x800478A0: nop

    osWritebackDCacheAll_recomp(rdram, ctx);
        goto after_25;
    // 0x800478A0: nop

    after_25:
    // 0x800478A4: lw          $t2, 0x0($s2)
    ctx->r10 = MEM_W(ctx->r18, 0X0);
    // 0x800478A8: beq         $t2, $zero, L_800478B8
    if (ctx->r10 == 0) {
        // 0x800478AC: nop
    
            goto L_800478B8;
    }
    // 0x800478AC: nop

    // 0x800478B0: b           L_80047718
    // 0x800478B4: sw          $s1, 0x0($s5)
    MEM_W(0X0, ctx->r21) = ctx->r17;
        goto L_80047718;
    // 0x800478B4: sw          $s1, 0x0($s5)
    MEM_W(0X0, ctx->r21) = ctx->r17;
L_800478B8:
    // 0x800478B8: jal         0x800474E4
    // 0x800478BC: nop

    func_800474E4(rdram, ctx);
        goto after_26;
    // 0x800478BC: nop

    after_26:
    // 0x800478C0: b           L_80047718
    // 0x800478C4: nop

        goto L_80047718;
    // 0x800478C4: nop

    // 0x800478C8: addiu       $at, $zero, 0x18
    ctx->r1 = ADD32(0, 0X18);
L_800478CC:
    // 0x800478CC: bne         $v1, $at, L_80047718
    if (ctx->r3 != ctx->r1) {
        // 0x800478D0: lui         $a0, 0x8015
        ctx->r4 = S32(0X8015 << 16);
            goto L_80047718;
    }
    // 0x800478D0: lui         $a0, 0x8015
    ctx->r4 = S32(0X8015 << 16);
    // 0x800478D4: addiu       $a0, $a0, 0x4118
    ctx->r4 = ADD32(ctx->r4, 0X4118);
    // 0x800478D8: addiu       $a1, $zero, 0x33
    ctx->r5 = ADD32(0, 0X33);
    // 0x800478DC: jal         0x800C57A0
    // 0x800478E0: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    osSendMesg_recomp(rdram, ctx);
        goto after_27;
    // 0x800478E0: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    after_27:
    // 0x800478E4: b           L_80047718
    // 0x800478E8: nop

        goto L_80047718;
    // 0x800478E8: nop

    // 0x800478EC: nop

    // 0x800478F0: lw          $ra, 0x3C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X3C);
    // 0x800478F4: lw          $s0, 0x1C($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X1C);
    // 0x800478F8: lw          $s1, 0x20($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X20);
    // 0x800478FC: lw          $s2, 0x24($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X24);
    // 0x80047900: lw          $s3, 0x28($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X28);
    // 0x80047904: lw          $s4, 0x2C($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X2C);
    // 0x80047908: lw          $s5, 0x30($sp)
    ctx->r21 = MEM_W(ctx->r29, 0X30);
    // 0x8004790C: lw          $s6, 0x34($sp)
    ctx->r22 = MEM_W(ctx->r29, 0X34);
    // 0x80047910: lw          $s7, 0x38($sp)
    ctx->r23 = MEM_W(ctx->r29, 0X38);
    // 0x80047914: jr          $ra
    // 0x80047918: addiu       $sp, $sp, 0x50
    ctx->r29 = ADD32(ctx->r29, 0X50);
    return;
    // 0x80047918: addiu       $sp, $sp, 0x50
    ctx->r29 = ADD32(ctx->r29, 0X50);
;}
RECOMP_FUNC void Main_IdleThread(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8004791C: addiu       $sp, $sp, -0x28
    ctx->r29 = ADD32(ctx->r29, -0X28);
    // 0x80047920: sw          $s0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r16;
    // 0x80047924: lui         $s0, 0x8015
    ctx->r16 = S32(0X8015 << 16);
    // 0x80047928: addiu       $s0, $s0, 0x42C0
    ctx->r16 = ADD32(ctx->r16, 0X42C0);
    // 0x8004792C: sw          $ra, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r31;
    // 0x80047930: sw          $a0, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r4;
    // 0x80047934: lui         $t6, 0x8040
    ctx->r14 = S32(0X8040 << 16);
    // 0x80047938: ori         $t6, $t6, 0x0
    ctx->r14 = ctx->r14 | 0X0;
    // 0x8004793C: lui         $t7, 0x8043
    ctx->r15 = S32(0X8043 << 16);
    // 0x80047940: ori         $t7, $t7, 0x1B00
    ctx->r15 = ctx->r15 | 0X1B00;
    // 0x80047944: lui         $t8, 0x8046
    ctx->r24 = S32(0X8046 << 16);
    // 0x80047948: ori         $t8, $t8, 0x3600
    ctx->r24 = ctx->r24 | 0X3600;
    // 0x8004794C: sw          $t6, 0x0($s0)
    MEM_W(0X0, ctx->r16) = ctx->r14;
    // 0x80047950: sw          $t7, 0x4($s0)
    MEM_W(0X4, ctx->r16) = ctx->r15;
    // 0x80047954: sw          $t8, 0x8($s0)
    MEM_W(0X8, ctx->r16) = ctx->r24;
    // 0x80047958: jal         0x800C6770
    // 0x8004795C: addiu       $a0, $zero, 0xFE
    ctx->r4 = ADD32(0, 0XFE);
    osCreateViManager_recomp(rdram, ctx);
        goto after_0;
    // 0x8004795C: addiu       $a0, $zero, 0xFE
    ctx->r4 = ADD32(0, 0XFE);
    after_0:
    // 0x80047960: lui         $t9, 0x8000
    ctx->r25 = S32(0X8000 << 16);
    // 0x80047964: lw          $t9, 0x300($t9)
    ctx->r25 = MEM_W(ctx->r25, 0X300);
    // 0x80047968: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x8004796C: bne         $t9, $at, L_80047984
    if (ctx->r25 != ctx->r1) {
        // 0x80047970: lui         $a0, 0x800F
        ctx->r4 = S32(0X800F << 16);
            goto L_80047984;
    }
    // 0x80047970: lui         $a0, 0x800F
    ctx->r4 = S32(0X800F << 16);
    // 0x80047974: jal         0x800C5DF0
    // 0x80047978: addiu       $a0, $a0, -0x7890
    ctx->r4 = ADD32(ctx->r4, -0X7890);
    osViSetMode_recomp(rdram, ctx);
        goto after_1;
    // 0x80047978: addiu       $a0, $a0, -0x7890
    ctx->r4 = ADD32(ctx->r4, -0X7890);
    after_1:
    // 0x8004797C: b           L_80047990
    // 0x80047980: nop

        goto L_80047990;
    // 0x80047980: nop

L_80047984:
    // 0x80047984: lui         $a0, 0x800F
    ctx->r4 = S32(0X800F << 16);
    // 0x80047988: jal         0x800C5DF0
    // 0x8004798C: addiu       $a0, $a0, -0x7430
    ctx->r4 = ADD32(ctx->r4, -0X7430);
    osViSetMode_recomp(rdram, ctx);
        goto after_2;
    // 0x8004798C: addiu       $a0, $a0, -0x7430
    ctx->r4 = ADD32(ctx->r4, -0X7430);
    after_2:
L_80047990:
    // 0x80047990: jal         0x800C6AD0
    // 0x80047994: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    osViBlack_recomp(rdram, ctx);
        goto after_3;
    // 0x80047994: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    after_3:
    // 0x80047998: jal         0x800C59B0
    // 0x8004799C: lw          $a0, 0x4($s0)
    ctx->r4 = MEM_W(ctx->r16, 0X4);
    osViSwapBuffer_recomp(rdram, ctx);
        goto after_4;
    // 0x8004799C: lw          $a0, 0x4($s0)
    ctx->r4 = MEM_W(ctx->r16, 0X4);
    after_4:
    // 0x800479A0: jal         0x800C6B40
    // 0x800479A4: nop

    osViGetCurrentFramebuffer_recomp(rdram, ctx);
        goto after_5;
    // 0x800479A4: nop

    after_5:
    // 0x800479A8: lw          $t0, 0x4($s0)
    ctx->r8 = MEM_W(ctx->r16, 0X4);
    // 0x800479AC: beq         $v0, $t0, L_800479C8
    if (ctx->r2 == ctx->r8) {
        // 0x800479B0: nop
    
            goto L_800479C8;
    }
    // 0x800479B0: nop

L_800479B4:
    // 0x800479B4: jal         0x800C6B40
    // 0x800479B8: nop

    osViGetCurrentFramebuffer_recomp(rdram, ctx);
        goto after_6;
    // 0x800479B8: nop

    after_6:
    // 0x800479BC: lw          $t1, 0x4($s0)
    ctx->r9 = MEM_W(ctx->r16, 0X4);
    // 0x800479C0: bne         $v0, $t1, L_800479B4
    if (ctx->r2 != ctx->r9) {
        // 0x800479C4: nop
    
            goto L_800479B4;
    }
    // 0x800479C4: nop

L_800479C8:
    // 0x800479C8: jal         0x800980D0
    // 0x800479CC: lw          $a0, 0x0($s0)
    ctx->r4 = MEM_W(ctx->r16, 0X0);
    func_800980D0(rdram, ctx);
        goto after_7;
    // 0x800479CC: lw          $a0, 0x0($s0)
    ctx->r4 = MEM_W(ctx->r16, 0X0);
    after_7:
    // 0x800479D0: jal         0x800C59B0
    // 0x800479D4: lw          $a0, 0x0($s0)
    ctx->r4 = MEM_W(ctx->r16, 0X0);
    osViSwapBuffer_recomp(rdram, ctx);
        goto after_8;
    // 0x800479D4: lw          $a0, 0x0($s0)
    ctx->r4 = MEM_W(ctx->r16, 0X0);
    after_8:
    // 0x800479D8: jal         0x800C6B40
    // 0x800479DC: nop

    osViGetCurrentFramebuffer_recomp(rdram, ctx);
        goto after_9;
    // 0x800479DC: nop

    after_9:
    // 0x800479E0: lw          $t2, 0x0($s0)
    ctx->r10 = MEM_W(ctx->r16, 0X0);
    // 0x800479E4: beq         $v0, $t2, L_80047A00
    if (ctx->r2 == ctx->r10) {
        // 0x800479E8: nop
    
            goto L_80047A00;
    }
    // 0x800479E8: nop

L_800479EC:
    // 0x800479EC: jal         0x800C6B40
    // 0x800479F0: nop

    osViGetCurrentFramebuffer_recomp(rdram, ctx);
        goto after_10;
    // 0x800479F0: nop

    after_10:
    // 0x800479F4: lw          $t3, 0x0($s0)
    ctx->r11 = MEM_W(ctx->r16, 0X0);
    // 0x800479F8: bne         $v0, $t3, L_800479EC
    if (ctx->r2 != ctx->r11) {
        // 0x800479FC: nop
    
            goto L_800479EC;
    }
    // 0x800479FC: nop

L_80047A00:
    // 0x80047A00: jal         0x800C6AD0
    // 0x80047A04: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    osViBlack_recomp(rdram, ctx);
        goto after_11;
    // 0x80047A04: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    after_11:
    // 0x80047A08: jal         0x800C5E60
    // 0x80047A0C: addiu       $a0, $zero, 0x66
    ctx->r4 = ADD32(0, 0X66);
    osViSetSpecialFeatures_recomp(rdram, ctx);
        goto after_12;
    // 0x80047A0C: addiu       $a0, $zero, 0x66
    ctx->r4 = ADD32(0, 0X66);
    after_12:
    { extern void wr64_wait_for_rt_startup(uint8_t*); wr64_wait_for_rt_startup(rdram); }
    // 0x80047A10: lui         $a1, 0x8015
    ctx->r5 = S32(0X8015 << 16);
    // 0x80047A14: lui         $a2, 0x8015
    ctx->r6 = S32(0X8015 << 16);
    // 0x80047A18: addiu       $a2, $a2, 0x4148
    ctx->r6 = ADD32(ctx->r6, 0X4148);
    // 0x80047A1C: addiu       $a1, $a1, 0x40A0
    ctx->r5 = ADD32(ctx->r5, 0X40A0);
    // 0x80047A20: addiu       $a0, $zero, 0x96
    ctx->r4 = ADD32(0, 0X96);
    // 0x80047A24: jal         0x800C6B80
    // 0x80047A28: addiu       $a3, $zero, 0x40
    ctx->r7 = ADD32(0, 0X40);
    osCreatePiManager_recomp(rdram, ctx);
        goto after_13;
    // 0x80047A28: addiu       $a3, $zero, 0x40
    ctx->r7 = ADD32(0, 0X40);
    after_13:
    // 0x80047A2C: lui         $s0, 0x8015
    ctx->r16 = S32(0X8015 << 16);
    // 0x80047A30: lui         $t4, 0x8015
    ctx->r12 = S32(0X8015 << 16);
    // 0x80047A34: addiu       $s0, $s0, 0x3B90
    ctx->r16 = ADD32(ctx->r16, 0X3B90);
    // 0x80047A38: addiu       $t4, $t4, 0x21E0
    ctx->r12 = ADD32(ctx->r12, 0X21E0);
    // 0x80047A3C: lui         $a2, 0x8004
    ctx->r6 = S32(0X8004 << 16);
    // 0x80047A40: addiu       $t5, $zero, 0x64
    ctx->r13 = ADD32(0, 0X64);
    // 0x80047A44: sw          $t5, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r13;
    // 0x80047A48: addiu       $a2, $a2, 0x7530
    ctx->r6 = ADD32(ctx->r6, 0X7530);
    // 0x80047A4C: sw          $t4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r12;
    // 0x80047A50: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x80047A54: addiu       $a1, $zero, 0x3
    ctx->r5 = ADD32(0, 0X3);
    // 0x80047A58: jal         0x800C6420
    // 0x80047A5C: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    osCreateThread_recomp(rdram, ctx);
        goto after_14;
    // 0x80047A5C: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_14:
    // 0x80047A60: lui         $t6, 0x800D
    ctx->r14 = S32(0X800D << 16);
    // 0x80047A64: lb          $t6, 0x4620($t6)
    ctx->r14 = MEM_B(ctx->r14, 0X4620);
    // 0x80047A68: beql        $t6, $zero, L_80047A7C
    if (ctx->r14 == 0) {
        // 0x80047A6C: or          $a0, $zero, $zero
        ctx->r4 = 0 | 0;
            goto L_80047A7C;
    }
    goto skip_0;
    // 0x80047A6C: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    skip_0:
    // 0x80047A70: jal         0x800C6570
    // 0x80047A74: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    osStartThread_recomp(rdram, ctx);
        goto after_15;
    // 0x80047A74: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_15:
    // 0x80047A78: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
L_80047A7C:
    // 0x80047A7C: jal         0x800C6D00
    // 0x80047A80: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    osSetThreadPri_recomp(rdram, ctx);
        goto after_16;
    // 0x80047A80: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_16:
L_80047A84:
    // 0x80047A84: b           L_80047A84
    pause_self(rdram);
    // 0x80047A88: nop

    // 0x80047A8C: nop

    // 0x80047A90: lw          $ra, 0x24($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X24);
    // 0x80047A94: lw          $s0, 0x20($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X20);
    // 0x80047A98: addiu       $sp, $sp, 0x28
    ctx->r29 = ADD32(ctx->r29, 0X28);
    // 0x80047A9C: jr          $ra
    // 0x80047AA0: nop

    return;
    // 0x80047AA0: nop

;}
RECOMP_FUNC void bootproc(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x80047AA4: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x80047AA8: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x80047AAC: jal         0x800C6DE0
    // 0x80047AB0: nop

    osInitialize_recomp(rdram, ctx);
        goto after_0;
    // 0x80047AB0: nop

    after_0:
    // 0x80047AB4: lui         $t6, 0x8015
    ctx->r14 = S32(0X8015 << 16);
    // 0x80047AB8: addiu       $t6, $t6, 0x1DE0
    ctx->r14 = ADD32(ctx->r14, 0X1DE0);
    // 0x80047ABC: lui         $a0, 0x8015
    ctx->r4 = S32(0X8015 << 16);
    // 0x80047AC0: lui         $a2, 0x8004
    ctx->r6 = S32(0X8004 << 16);
    // 0x80047AC4: addiu       $t7, $zero, 0x64
    ctx->r15 = ADD32(0, 0X64);
    // 0x80047AC8: sw          $t7, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r15;
    // 0x80047ACC: addiu       $a2, $a2, 0x791C
    ctx->r6 = ADD32(ctx->r6, 0X791C);
    // 0x80047AD0: addiu       $a0, $a0, 0x39E0
    ctx->r4 = ADD32(ctx->r4, 0X39E0);
    // 0x80047AD4: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x80047AD8: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x80047ADC: jal         0x800C6420
    // 0x80047AE0: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    osCreateThread_recomp(rdram, ctx);
        goto after_1;
    // 0x80047AE0: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_1:
    // 0x80047AE4: lui         $a0, 0x8015
    ctx->r4 = S32(0X8015 << 16);
    // 0x80047AE8: jal         0x800C6570
    // 0x80047AEC: addiu       $a0, $a0, 0x39E0
    ctx->r4 = ADD32(ctx->r4, 0X39E0);
    osStartThread_recomp(rdram, ctx);
        goto after_2;
    // 0x80047AEC: addiu       $a0, $a0, 0x39E0
    ctx->r4 = ADD32(ctx->r4, 0X39E0);
    after_2:
    // 0x80047AF0: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    // 0x80047AF4: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x80047AF8: jr          $ra
    // 0x80047AFC: nop

    return;
    // 0x80047AFC: nop

;}
RECOMP_FUNC void n_alSeqpDelete(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x80047B00: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x80047B04: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x80047B08: jal         0x800BF370
    // 0x80047B0C: nop

    n_alSynRemovePlayer(rdram, ctx);
        goto after_0;
    // 0x80047B0C: nop

    after_0:
    // 0x80047B10: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x80047B14: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x80047B18: jr          $ra
    // 0x80047B1C: nop

    return;
    // 0x80047B1C: nop

;}
RECOMP_FUNC void SysAudio_AudioThreadEntry(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x80047B20: addiu       $sp, $sp, -0x28
    ctx->r29 = ADD32(ctx->r29, -0X28);
    // 0x80047B24: sw          $ra, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r31;
    // 0x80047B28: sw          $s3, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r19;
    // 0x80047B2C: sw          $s2, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r18;
    // 0x80047B30: sw          $s1, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r17;
    // 0x80047B34: sw          $s0, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r16;
    // 0x80047B38: jal         0x800BA100
    // 0x80047B3C: sw          $a0, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r4;
    AudioLoad_Init(rdram, ctx);
        goto after_0;
    // 0x80047B3C: sw          $a0, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r4;
    after_0:
    // 0x80047B40: lui         $s3, 0x8015
    ctx->r19 = S32(0X8015 << 16);
    // 0x80047B44: lui         $s2, 0x8015
    ctx->r18 = S32(0X8015 << 16);
    // 0x80047B48: lui         $s1, 0x8015
    ctx->r17 = S32(0X8015 << 16);
    // 0x80047B4C: lui         $s0, 0x8015
    ctx->r16 = S32(0X8015 << 16);
    // 0x80047B50: addiu       $s0, $s0, 0x40E8
    ctx->r16 = ADD32(ctx->r16, 0X40E8);
    // 0x80047B54: addiu       $s1, $s1, 0x42D0
    ctx->r17 = ADD32(ctx->r17, 0X42D0);
    // 0x80047B58: addiu       $s2, $s2, 0x42B8
    ctx->r18 = ADD32(ctx->r18, 0X42B8);
    // 0x80047B5C: addiu       $s3, $s3, 0x4130
    ctx->r19 = ADD32(ctx->r19, 0X4130);
L_80047B60:
    // 0x80047B60: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x80047B64: or          $a1, $s1, $zero
    ctx->r5 = ctx->r17 | 0;
    // 0x80047B68: jal         0x800C5C60
    // 0x80047B6C: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    osRecvMesg_recomp(rdram, ctx);
        goto after_1;
    // 0x80047B6C: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    after_1:
    // 0x80047B70: lui         $t6, 0x800D
    ctx->r14 = S32(0X800D << 16);
    // 0x80047B74: lw          $t6, 0x4630($t6)
    ctx->r14 = MEM_W(ctx->r14, 0X4630);
    // 0x80047B78: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
    // 0x80047B7C: addiu       $a1, $zero, 0x16
    ctx->r5 = ADD32(0, 0X16);
    // 0x80047B80: beq         $t6, $zero, L_80047B90
    if (ctx->r14 == 0) {
        // 0x80047B84: or          $a2, $zero, $zero
        ctx->r6 = 0 | 0;
            goto L_80047B90;
    }
    // 0x80047B84: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x80047B88: jal         0x800C57A0
    // 0x80047B8C: sw          $t6, 0x0($s2)
    MEM_W(0X0, ctx->r18) = ctx->r14;
    osSendMesg_recomp(rdram, ctx);
        goto after_2;
    // 0x80047B8C: sw          $t6, 0x0($s2)
    MEM_W(0X0, ctx->r18) = ctx->r14;
    after_2:
L_80047B90:
    // 0x80047B90: jal         0x800C4C40
    // 0x80047B94: nop

    AudioThread_CreateTask(rdram, ctx);
        goto after_3;
    // 0x80047B94: nop

    after_3:
    // 0x80047B98: lui         $at, 0x800D
    ctx->r1 = S32(0X800D << 16);
    // 0x80047B9C: b           L_80047B60
    // 0x80047BA0: sw          $v0, 0x4630($at)
    MEM_W(0X4630, ctx->r1) = ctx->r2;
        goto L_80047B60;
    // 0x80047BA0: sw          $v0, 0x4630($at)
    MEM_W(0X4630, ctx->r1) = ctx->r2;
    // 0x80047BA4: nop

    // 0x80047BA8: nop

    // 0x80047BAC: nop

    // 0x80047BB0: nop

    // 0x80047BB4: nop

    // 0x80047BB8: nop

    // 0x80047BBC: nop

    // 0x80047BC0: lw          $ra, 0x24($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X24);
    // 0x80047BC4: lw          $s0, 0x14($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X14);
    // 0x80047BC8: lw          $s1, 0x18($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X18);
    // 0x80047BCC: lw          $s2, 0x1C($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X1C);
    // 0x80047BD0: lw          $s3, 0x20($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X20);
    // 0x80047BD4: jr          $ra
    // 0x80047BD8: addiu       $sp, $sp, 0x28
    ctx->r29 = ADD32(ctx->r29, 0X28);
    return;
    // 0x80047BD8: addiu       $sp, $sp, 0x28
    ctx->r29 = ADD32(ctx->r29, 0X28);
    // 0x80047BDC: nop

;}
RECOMP_FUNC void SysUtils_Round(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x80047BE0: mtc1        $zero, $f4
    ctx->f4.u32l = 0;
    // 0x80047BE4: lui         $at, 0x3F00
    ctx->r1 = S32(0X3F00 << 16);
    // 0x80047BE8: c.lt.s      $f12, $f4
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    c1cs = ctx->f12.fl < ctx->f4.fl;
    // 0x80047BEC: nop

    // 0x80047BF0: bc1fl       L_80047C1C
    if (!c1cs) {
        // 0x80047BF4: mtc1        $at, $f16
        ctx->f16.u32l = ctx->r1;
            goto L_80047C1C;
    }
    goto skip_0;
    // 0x80047BF4: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
    skip_0:
    // 0x80047BF8: lui         $at, 0x3F00
    ctx->r1 = S32(0X3F00 << 16);
    // 0x80047BFC: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x80047C00: nop

    // 0x80047C04: sub.s       $f8, $f12, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = ctx->f12.fl - ctx->f6.fl;
    // 0x80047C08: trunc.w.s   $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.u32l = TRUNC_W_S(ctx->f8.fl);
    // 0x80047C0C: mfc1        $v0, $f10
    ctx->r2 = (int32_t)ctx->f10.u32l;
    // 0x80047C10: jr          $ra
    // 0x80047C14: nop

    return;
    // 0x80047C14: nop

    // 0x80047C18: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
L_80047C1C:
    // 0x80047C1C: nop

    // 0x80047C20: add.s       $f18, $f12, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f18.fl = ctx->f12.fl + ctx->f16.fl;
    // 0x80047C24: trunc.w.s   $f4, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    ctx->f4.u32l = TRUNC_W_S(ctx->f18.fl);
    // 0x80047C28: mfc1        $v0, $f4
    ctx->r2 = (int32_t)ctx->f4.u32l;
    // 0x80047C2C: nop

    // 0x80047C30: jr          $ra
    // 0x80047C34: nop

    return;
    // 0x80047C34: nop

;}
RECOMP_FUNC void SysUtils_TaylorSeries(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x80047C38: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x80047C3C: sdc1        $f22, 0x10($sp)
    CHECK_FR(ctx, 22);
    SD(ctx->f22.u64, 0X10, ctx->r29);
    // 0x80047C40: lui         $at, 0x4018
    ctx->r1 = S32(0X4018 << 16);
    // 0x80047C44: mtc1        $at, $f23
    ctx->f_odd[(23 - 1) * 2] = ctx->r1;
    // 0x80047C48: sdc1        $f20, 0x8($sp)
    CHECK_FR(ctx, 20);
    SD(ctx->f20.u64, 0X8, ctx->r29);
    // 0x80047C4C: lui         $at, 0x40B0
    ctx->r1 = S32(0X40B0 << 16);
    // 0x80047C50: mtc1        $at, $f21
    ctx->f_odd[(21 - 1) * 2] = ctx->r1;
    // 0x80047C54: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x80047C58: lui         $a1, 0x8015
    ctx->r5 = S32(0X8015 << 16);
    // 0x80047C5C: mtc1        $zero, $f20
    ctx->f20.u32l = 0;
    // 0x80047C60: mtc1        $zero, $f22
    ctx->f22.u32l = 0;
    // 0x80047C64: addiu       $a1, $a1, 0x4350
    ctx->r5 = ADD32(ctx->r5, 0X4350);
    // 0x80047C68: ldc1        $f18, -0x6DE0($at)
    CHECK_FR(ctx, 18);
    ctx->f18.u64 = LD(ctx->r1, -0X6DE0);
    // 0x80047C6C: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    // 0x80047C70: addiu       $t1, $zero, 0x1000
    ctx->r9 = ADD32(0, 0X1000);
    // 0x80047C74: addiu       $t0, $zero, 0xE
    ctx->r8 = ADD32(0, 0XE);
L_80047C78:
    // 0x80047C78: mtc1        $v0, $f4
    ctx->f4.u32l = ctx->r2;
    // 0x80047C7C: mov.d       $f16, $f22
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 22);
    ctx->f16.d = ctx->f22.d;
    // 0x80047C80: addiu       $v1, $zero, 0x2
    ctx->r3 = ADD32(0, 0X2);
    // 0x80047C84: cvt.d.w     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.d = CVT_D_W(ctx->f4.u32l);
    // 0x80047C88: mul.d       $f8, $f6, $f18
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f6.d); NAN_CHECK(ctx->f18.d); 
    ctx->f8.d = MUL_D(ctx->f6.d, ctx->f18.d);
    // 0x80047C8C: div.d       $f0, $f8, $f20
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f8.d); NAN_CHECK(ctx->f20.d); 
    ctx->f0.d = DIV_D(ctx->f8.d, ctx->f20.d);
    // 0x80047C90: neg.d       $f10, $f0
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f0.d); 
    ctx->f10.d = -ctx->f0.d;
    // 0x80047C94: mul.d       $f14, $f10, $f0
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f10.d); NAN_CHECK(ctx->f0.d); 
    ctx->f14.d = MUL_D(ctx->f10.d, ctx->f0.d);
    // 0x80047C98: nop

    // 0x80047C9C: mul.d       $f12, $f14, $f0
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f14.d); NAN_CHECK(ctx->f0.d); 
    ctx->f12.d = MUL_D(ctx->f14.d, ctx->f0.d);
    // 0x80047CA0: nop

    // 0x80047CA4: addiu       $t0, $t0, -0x4
    ctx->r8 = ADD32(ctx->r8, -0X4);
    // 0x80047CA8: sll         $t6, $v1, 2
    ctx->r14 = S32(ctx->r3 << 2);
    // 0x80047CAC: beq         $v1, $t0, L_80047D70
    if (ctx->r3 == ctx->r8) {
        // 0x80047CB0: addiu       $t7, $t6, 0x2
        ctx->r15 = ADD32(ctx->r14, 0X2);
            goto L_80047D70;
    }
    // 0x80047CB0: addiu       $t7, $t6, 0x2
    ctx->r15 = ADD32(ctx->r14, 0X2);
L_80047CB4:
    // 0x80047CB4: div.d       $f10, $f12, $f16
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f12.d); NAN_CHECK(ctx->f16.d); 
    ctx->f10.d = DIV_D(ctx->f12.d, ctx->f16.d);
    // 0x80047CB8: multu       $v1, $t7
    result = U64(U32(ctx->r3)) * U64(U32(ctx->r15)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80047CBC: addiu       $a0, $v1, 0x1
    ctx->r4 = ADD32(ctx->r3, 0X1);
    // 0x80047CC0: mul.d       $f12, $f12, $f14
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f12.d); NAN_CHECK(ctx->f14.d); 
    ctx->f12.d = MUL_D(ctx->f12.d, ctx->f14.d);
    // 0x80047CC4: sll         $t9, $a0, 2
    ctx->r25 = S32(ctx->r4 << 2);
    // 0x80047CC8: addiu       $t2, $t9, 0x2
    ctx->r10 = ADD32(ctx->r25, 0X2);
    // 0x80047CCC: addiu       $a2, $v1, 0x2
    ctx->r6 = ADD32(ctx->r3, 0X2);
    // 0x80047CD0: sll         $t4, $a2, 2
    ctx->r12 = S32(ctx->r6 << 2);
    // 0x80047CD4: addiu       $t5, $t4, 0x2
    ctx->r13 = ADD32(ctx->r12, 0X2);
    // 0x80047CD8: addiu       $a3, $v1, 0x3
    ctx->r7 = ADD32(ctx->r3, 0X3);
    // 0x80047CDC: sll         $t7, $a3, 2
    ctx->r15 = S32(ctx->r7 << 2);
    // 0x80047CE0: mflo        $t8
    ctx->r24 = lo;
    // 0x80047CE4: mtc1        $t8, $f8
    ctx->f8.u32l = ctx->r24;
    // 0x80047CE8: addiu       $t8, $t7, 0x2
    ctx->r24 = ADD32(ctx->r15, 0X2);
    // 0x80047CEC: multu       $a0, $t2
    result = U64(U32(ctx->r4)) * U64(U32(ctx->r10)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80047CF0: cvt.d.w     $f8, $f8
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 8);
    ctx->f8.d = CVT_D_W(ctx->f8.u32l);
    // 0x80047CF4: addiu       $v1, $v1, 0x4
    ctx->r3 = ADD32(ctx->r3, 0X4);
    // 0x80047CF8: mul.d       $f16, $f16, $f8
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f16.d); NAN_CHECK(ctx->f8.d); 
    ctx->f16.d = MUL_D(ctx->f16.d, ctx->f8.d);
    // 0x80047CFC: mflo        $t3
    ctx->r11 = lo;
    // 0x80047D00: mtc1        $t3, $f8
    ctx->f8.u32l = ctx->r11;
    // 0x80047D04: nop

    // 0x80047D08: multu       $a2, $t5
    result = U64(U32(ctx->r6)) * U64(U32(ctx->r13)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80047D0C: div.d       $f6, $f12, $f16
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f12.d); NAN_CHECK(ctx->f16.d); 
    ctx->f6.d = DIV_D(ctx->f12.d, ctx->f16.d);
    // 0x80047D10: mul.d       $f12, $f12, $f14
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f12.d); NAN_CHECK(ctx->f14.d); 
    ctx->f12.d = MUL_D(ctx->f12.d, ctx->f14.d);
    // 0x80047D14: mflo        $t6
    ctx->r14 = lo;
    // 0x80047D18: mtc1        $t6, $f4
    ctx->f4.u32l = ctx->r14;
    // 0x80047D1C: add.d       $f0, $f0, $f10
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f0.d); NAN_CHECK(ctx->f10.d); 
    ctx->f0.d = ctx->f0.d + ctx->f10.d;
    // 0x80047D20: multu       $a3, $t8
    result = U64(U32(ctx->r7)) * U64(U32(ctx->r24)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80047D24: sll         $t6, $v1, 2
    ctx->r14 = S32(ctx->r3 << 2);
    // 0x80047D28: addiu       $t7, $t6, 0x2
    ctx->r15 = ADD32(ctx->r14, 0X2);
    // 0x80047D2C: cvt.d.w     $f8, $f8
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 8);
    ctx->f8.d = CVT_D_W(ctx->f8.u32l);
    // 0x80047D30: cvt.d.w     $f4, $f4
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 4);
    ctx->f4.d = CVT_D_W(ctx->f4.u32l);
    // 0x80047D34: mul.d       $f16, $f16, $f8
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f16.d); NAN_CHECK(ctx->f8.d); 
    ctx->f16.d = MUL_D(ctx->f16.d, ctx->f8.d);
    // 0x80047D38: mflo        $t9
    ctx->r25 = lo;
    // 0x80047D3C: mtc1        $t9, $f8
    ctx->f8.u32l = ctx->r25;
    // 0x80047D40: nop

    // 0x80047D44: cvt.d.w     $f8, $f8
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 8);
    ctx->f8.d = CVT_D_W(ctx->f8.u32l);
    // 0x80047D48: div.d       $f10, $f12, $f16
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f12.d); NAN_CHECK(ctx->f16.d); 
    ctx->f10.d = DIV_D(ctx->f12.d, ctx->f16.d);
    // 0x80047D4C: mul.d       $f12, $f12, $f14
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f12.d); NAN_CHECK(ctx->f14.d); 
    ctx->f12.d = MUL_D(ctx->f12.d, ctx->f14.d);
    // 0x80047D50: add.d       $f0, $f0, $f6
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f0.d); NAN_CHECK(ctx->f6.d); 
    ctx->f0.d = ctx->f0.d + ctx->f6.d;
    // 0x80047D54: mul.d       $f16, $f16, $f4
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f16.d); NAN_CHECK(ctx->f4.d); 
    ctx->f16.d = MUL_D(ctx->f16.d, ctx->f4.d);
    // 0x80047D58: div.d       $f4, $f12, $f16
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f12.d); NAN_CHECK(ctx->f16.d); 
    ctx->f4.d = DIV_D(ctx->f12.d, ctx->f16.d);
    // 0x80047D5C: mul.d       $f12, $f12, $f14
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f12.d); NAN_CHECK(ctx->f14.d); 
    ctx->f12.d = MUL_D(ctx->f12.d, ctx->f14.d);
    // 0x80047D60: add.d       $f0, $f0, $f10
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f0.d); NAN_CHECK(ctx->f10.d); 
    ctx->f0.d = ctx->f0.d + ctx->f10.d;
    // 0x80047D64: mul.d       $f16, $f16, $f8
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f16.d); NAN_CHECK(ctx->f8.d); 
    ctx->f16.d = MUL_D(ctx->f16.d, ctx->f8.d);
    // 0x80047D68: bne         $v1, $t0, L_80047CB4
    if (ctx->r3 != ctx->r8) {
        // 0x80047D6C: add.d       $f0, $f0, $f4
        CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f0.d); NAN_CHECK(ctx->f4.d); 
    ctx->f0.d = ctx->f0.d + ctx->f4.d;
            goto L_80047CB4;
    }
    // 0x80047D6C: add.d       $f0, $f0, $f4
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f0.d); NAN_CHECK(ctx->f4.d); 
    ctx->f0.d = ctx->f0.d + ctx->f4.d;
L_80047D70:
    // 0x80047D70: multu       $v1, $t7
    result = U64(U32(ctx->r3)) * U64(U32(ctx->r15)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80047D74: div.d       $f10, $f12, $f16
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f12.d); NAN_CHECK(ctx->f16.d); 
    ctx->f10.d = DIV_D(ctx->f12.d, ctx->f16.d);
    // 0x80047D78: addiu       $a0, $v1, 0x1
    ctx->r4 = ADD32(ctx->r3, 0X1);
    // 0x80047D7C: sll         $t9, $a0, 2
    ctx->r25 = S32(ctx->r4 << 2);
    // 0x80047D80: addiu       $t2, $t9, 0x2
    ctx->r10 = ADD32(ctx->r25, 0X2);
    // 0x80047D84: mul.d       $f12, $f12, $f14
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f12.d); NAN_CHECK(ctx->f14.d); 
    ctx->f12.d = MUL_D(ctx->f12.d, ctx->f14.d);
    // 0x80047D88: addiu       $a2, $v1, 0x2
    ctx->r6 = ADD32(ctx->r3, 0X2);
    // 0x80047D8C: sll         $t4, $a2, 2
    ctx->r12 = S32(ctx->r6 << 2);
    // 0x80047D90: addiu       $t5, $t4, 0x2
    ctx->r13 = ADD32(ctx->r12, 0X2);
    // 0x80047D94: addiu       $a3, $v1, 0x3
    ctx->r7 = ADD32(ctx->r3, 0X3);
    // 0x80047D98: mflo        $t8
    ctx->r24 = lo;
    // 0x80047D9C: mtc1        $t8, $f8
    ctx->f8.u32l = ctx->r24;
    // 0x80047DA0: sll         $t7, $a3, 2
    ctx->r15 = S32(ctx->r7 << 2);
    // 0x80047DA4: multu       $a0, $t2
    result = U64(U32(ctx->r4)) * U64(U32(ctx->r10)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80047DA8: cvt.d.w     $f8, $f8
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 8);
    ctx->f8.d = CVT_D_W(ctx->f8.u32l);
    // 0x80047DAC: addiu       $t8, $t7, 0x2
    ctx->r24 = ADD32(ctx->r15, 0X2);
    // 0x80047DB0: addiu       $t0, $t0, 0x4
    ctx->r8 = ADD32(ctx->r8, 0X4);
    // 0x80047DB4: addiu       $v1, $v1, 0x4
    ctx->r3 = ADD32(ctx->r3, 0X4);
    // 0x80047DB8: mul.d       $f16, $f16, $f8
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f16.d); NAN_CHECK(ctx->f8.d); 
    ctx->f16.d = MUL_D(ctx->f16.d, ctx->f8.d);
    // 0x80047DBC: mflo        $t3
    ctx->r11 = lo;
    // 0x80047DC0: mtc1        $t3, $f8
    ctx->f8.u32l = ctx->r11;
    // 0x80047DC4: nop

    // 0x80047DC8: multu       $a2, $t5
    result = U64(U32(ctx->r6)) * U64(U32(ctx->r13)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80047DCC: cvt.d.w     $f8, $f8
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 8);
    ctx->f8.d = CVT_D_W(ctx->f8.u32l);
    // 0x80047DD0: mflo        $t6
    ctx->r14 = lo;
    // 0x80047DD4: mtc1        $t6, $f4
    ctx->f4.u32l = ctx->r14;
    // 0x80047DD8: div.d       $f6, $f12, $f16
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f12.d); NAN_CHECK(ctx->f16.d); 
    ctx->f6.d = DIV_D(ctx->f12.d, ctx->f16.d);
    // 0x80047DDC: mul.d       $f12, $f12, $f14
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f12.d); NAN_CHECK(ctx->f14.d); 
    ctx->f12.d = MUL_D(ctx->f12.d, ctx->f14.d);
    // 0x80047DE0: add.d       $f0, $f0, $f10
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f0.d); NAN_CHECK(ctx->f10.d); 
    ctx->f0.d = ctx->f0.d + ctx->f10.d;
    // 0x80047DE4: mul.d       $f16, $f16, $f8
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f16.d); NAN_CHECK(ctx->f8.d); 
    ctx->f16.d = MUL_D(ctx->f16.d, ctx->f8.d);
    // 0x80047DE8: cvt.d.w     $f4, $f4
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 4);
    ctx->f4.d = CVT_D_W(ctx->f4.u32l);
    // 0x80047DEC: multu       $a3, $t8
    result = U64(U32(ctx->r7)) * U64(U32(ctx->r24)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80047DF0: mflo        $t9
    ctx->r25 = lo;
    // 0x80047DF4: mtc1        $t9, $f8
    ctx->f8.u32l = ctx->r25;
    // 0x80047DF8: div.d       $f10, $f12, $f16
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f12.d); NAN_CHECK(ctx->f16.d); 
    ctx->f10.d = DIV_D(ctx->f12.d, ctx->f16.d);
    // 0x80047DFC: mul.d       $f12, $f12, $f14
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f12.d); NAN_CHECK(ctx->f14.d); 
    ctx->f12.d = MUL_D(ctx->f12.d, ctx->f14.d);
    // 0x80047E00: add.d       $f0, $f0, $f6
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f0.d); NAN_CHECK(ctx->f6.d); 
    ctx->f0.d = ctx->f0.d + ctx->f6.d;
    // 0x80047E04: mul.d       $f16, $f16, $f4
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f16.d); NAN_CHECK(ctx->f4.d); 
    ctx->f16.d = MUL_D(ctx->f16.d, ctx->f4.d);
    // 0x80047E08: cvt.d.w     $f8, $f8
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 8);
    ctx->f8.d = CVT_D_W(ctx->f8.u32l);
    // 0x80047E0C: div.d       $f4, $f12, $f16
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f12.d); NAN_CHECK(ctx->f16.d); 
    ctx->f4.d = DIV_D(ctx->f12.d, ctx->f16.d);
    // 0x80047E10: mul.d       $f12, $f12, $f14
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f12.d); NAN_CHECK(ctx->f14.d); 
    ctx->f12.d = MUL_D(ctx->f12.d, ctx->f14.d);
    // 0x80047E14: add.d       $f0, $f0, $f10
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f0.d); NAN_CHECK(ctx->f10.d); 
    ctx->f0.d = ctx->f0.d + ctx->f10.d;
    // 0x80047E18: mul.d       $f16, $f16, $f8
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f16.d); NAN_CHECK(ctx->f8.d); 
    ctx->f16.d = MUL_D(ctx->f16.d, ctx->f8.d);
    // 0x80047E1C: add.d       $f0, $f0, $f4
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f0.d); NAN_CHECK(ctx->f4.d); 
    ctx->f0.d = ctx->f0.d + ctx->f4.d;
    // 0x80047E20: cvt.s.d     $f4, $f0
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f0.d); 
    ctx->f4.fl = CVT_S_D(ctx->f0.d);
    // 0x80047E24: addiu       $v0, $v0, 0x1
    ctx->r2 = ADD32(ctx->r2, 0X1);
    // 0x80047E28: addiu       $a1, $a1, 0x4
    ctx->r5 = ADD32(ctx->r5, 0X4);
    // 0x80047E2C: bne         $v0, $t1, L_80047C78
    if (ctx->r2 != ctx->r9) {
        // 0x80047E30: swc1        $f4, -0x4($a1)
        MEM_W(-0X4, ctx->r5) = ctx->f4.u32l;
            goto L_80047C78;
    }
    // 0x80047E30: swc1        $f4, -0x4($a1)
    MEM_W(-0X4, ctx->r5) = ctx->f4.u32l;
    // 0x80047E34: ldc1        $f20, 0x8($sp)
    CHECK_FR(ctx, 20);
    ctx->f20.u64 = LD(ctx->r29, 0X8);
    // 0x80047E38: ldc1        $f22, 0x10($sp)
    CHECK_FR(ctx, 22);
    ctx->f22.u64 = LD(ctx->r29, 0X10);
    // 0x80047E3C: jr          $ra
    // 0x80047E40: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    return;
    // 0x80047E40: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
;}
RECOMP_FUNC void SysUtils_Srand(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x80047E44: lui         $at, 0x800D
    ctx->r1 = S32(0X800D << 16);
    // 0x80047E48: jr          $ra
    // 0x80047E4C: sw          $a0, 0x4640($at)
    MEM_W(0X4640, ctx->r1) = ctx->r4;
    return;
    // 0x80047E4C: sw          $a0, 0x4640($at)
    MEM_W(0X4640, ctx->r1) = ctx->r4;
;}
RECOMP_FUNC void SysUtils_Rand(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x80047E50: lui         $v1, 0x800D
    ctx->r3 = S32(0X800D << 16);
    // 0x80047E54: addiu       $v1, $v1, 0x4640
    ctx->r3 = ADD32(ctx->r3, 0X4640);
    // 0x80047E58: lw          $t6, 0x0($v1)
    ctx->r14 = MEM_W(ctx->r3, 0X0);
    // 0x80047E5C: lui         $at, 0x41C6
    ctx->r1 = S32(0X41C6 << 16);
    // 0x80047E60: ori         $at, $at, 0x4E6D
    ctx->r1 = ctx->r1 | 0X4E6D;
    // 0x80047E64: multu       $t6, $at
    result = U64(U32(ctx->r14)) * U64(U32(ctx->r1)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80047E68: mflo        $t7
    ctx->r15 = lo;
    // 0x80047E6C: addiu       $v0, $t7, 0x3039
    ctx->r2 = ADD32(ctx->r15, 0X3039);
    // 0x80047E70: jr          $ra
    // 0x80047E74: sw          $v0, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r2;
    return;
    // 0x80047E74: sw          $v0, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r2;
;}
RECOMP_FUNC void SysUtils_MtxToMtxF(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x80047E78: lui         $at, 0x4780
    ctx->r1 = S32(0X4780 << 16);
    // 0x80047E7C: mtc1        $at, $f0
    ctx->f0.u32l = ctx->r1;
    // 0x80047E80: addiu       $v0, $zero, 0x3
    ctx->r2 = ADD32(0, 0X3);
    // 0x80047E84: addiu       $a2, $a1, 0x30
    ctx->r6 = ADD32(ctx->r5, 0X30);
    // 0x80047E88: addiu       $a3, $a0, 0x18
    ctx->r7 = ADD32(ctx->r4, 0X18);
L_80047E8C:
    // 0x80047E8C: addiu       $v1, $zero, 0x3
    ctx->r3 = ADD32(0, 0X3);
    // 0x80047E90: addiu       $a1, $a2, 0xC
    ctx->r5 = ADD32(ctx->r6, 0XC);
    // 0x80047E94: addiu       $t0, $a3, 0x6
    ctx->r8 = ADD32(ctx->r7, 0X6);
L_80047E98:
    // 0x80047E98: lh          $t7, 0x0($t0)
    ctx->r15 = MEM_H(ctx->r8, 0X0);
    // 0x80047E9C: lhu         $t6, 0x20($t0)
    ctx->r14 = MEM_HU(ctx->r8, 0X20);
    // 0x80047EA0: addiu       $v1, $v1, -0x1
    ctx->r3 = ADD32(ctx->r3, -0X1);
    // 0x80047EA4: sll         $t8, $t7, 16
    ctx->r24 = S32(ctx->r15 << 16);
    // 0x80047EA8: or          $t9, $t6, $t8
    ctx->r25 = ctx->r14 | ctx->r24;
    // 0x80047EAC: mtc1        $t9, $f4
    ctx->f4.u32l = ctx->r25;
    // 0x80047EB0: addiu       $a1, $a1, -0x4
    ctx->r5 = ADD32(ctx->r5, -0X4);
    // 0x80047EB4: addiu       $t0, $t0, -0x2
    ctx->r8 = ADD32(ctx->r8, -0X2);
    // 0x80047EB8: cvt.s.w     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
    // 0x80047EBC: div.s       $f8, $f6, $f0
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f8.fl = DIV_S(ctx->f6.fl, ctx->f0.fl);
    // 0x80047EC0: bgez        $v1, L_80047E98
    if (SIGNED(ctx->r3) >= 0) {
        // 0x80047EC4: swc1        $f8, 0x4($a1)
        MEM_W(0X4, ctx->r5) = ctx->f8.u32l;
            goto L_80047E98;
    }
    // 0x80047EC4: swc1        $f8, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->f8.u32l;
    // 0x80047EC8: addiu       $v0, $v0, -0x1
    ctx->r2 = ADD32(ctx->r2, -0X1);
    // 0x80047ECC: addiu       $a2, $a2, -0x10
    ctx->r6 = ADD32(ctx->r6, -0X10);
    // 0x80047ED0: bgez        $v0, L_80047E8C
    if (SIGNED(ctx->r2) >= 0) {
        // 0x80047ED4: addiu       $a3, $a3, -0x8
        ctx->r7 = ADD32(ctx->r7, -0X8);
            goto L_80047E8C;
    }
    // 0x80047ED4: addiu       $a3, $a3, -0x8
    ctx->r7 = ADD32(ctx->r7, -0X8);
    // 0x80047ED8: jr          $ra
    // 0x80047EDC: nop

    return;
    // 0x80047EDC: nop

;}
RECOMP_FUNC void SysUtils_MtxFToMtx(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x80047EE0: lui         $at, 0x4780
    ctx->r1 = S32(0X4780 << 16);
    // 0x80047EE4: mtc1        $at, $f0
    ctx->f0.u32l = ctx->r1;
    // 0x80047EE8: addiu       $v0, $zero, 0x3
    ctx->r2 = ADD32(0, 0X3);
    // 0x80047EEC: addiu       $a2, $a0, 0x30
    ctx->r6 = ADD32(ctx->r4, 0X30);
    // 0x80047EF0: addiu       $t0, $a1, 0x18
    ctx->r8 = ADD32(ctx->r5, 0X18);
L_80047EF4:
    // 0x80047EF4: addiu       $v1, $zero, 0x3
    ctx->r3 = ADD32(0, 0X3);
    // 0x80047EF8: addiu       $a3, $a2, 0xC
    ctx->r7 = ADD32(ctx->r6, 0XC);
    // 0x80047EFC: addiu       $t1, $t0, 0x6
    ctx->r9 = ADD32(ctx->r8, 0X6);
L_80047F00:
    // 0x80047F00: lwc1        $f4, 0x0($a3)
    ctx->f4.u32l = MEM_W(ctx->r7, 0X0);
    // 0x80047F04: addiu       $v1, $v1, -0x1
    ctx->r3 = ADD32(ctx->r3, -0X1);
    // 0x80047F08: addiu       $a3, $a3, -0x4
    ctx->r7 = ADD32(ctx->r7, -0X4);
    // 0x80047F0C: mul.s       $f6, $f4, $f0
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f6.fl = MUL_S(ctx->f4.fl, ctx->f0.fl);
    // 0x80047F10: addiu       $t1, $t1, -0x2
    ctx->r9 = ADD32(ctx->r9, -0X2);
    // 0x80047F14: trunc.w.s   $f8, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    ctx->f8.u32l = TRUNC_W_S(ctx->f6.fl);
    // 0x80047F18: mfc1        $t8, $f8
    ctx->r24 = (int32_t)ctx->f8.u32l;
    // 0x80047F1C: nop

    // 0x80047F20: sra         $t7, $t8, 16
    ctx->r15 = S32(SIGNED(ctx->r24) >> 16);
    // 0x80047F24: sh          $t7, 0x2($t1)
    MEM_H(0X2, ctx->r9) = ctx->r15;
    // 0x80047F28: bgez        $v1, L_80047F00
    if (SIGNED(ctx->r3) >= 0) {
        // 0x80047F2C: sh          $t8, 0x22($t1)
        MEM_H(0X22, ctx->r9) = ctx->r24;
            goto L_80047F00;
    }
    // 0x80047F2C: sh          $t8, 0x22($t1)
    MEM_H(0X22, ctx->r9) = ctx->r24;
    // 0x80047F30: addiu       $v0, $v0, -0x1
    ctx->r2 = ADD32(ctx->r2, -0X1);
    // 0x80047F34: addiu       $a2, $a2, -0x10
    ctx->r6 = ADD32(ctx->r6, -0X10);
    // 0x80047F38: bgez        $v0, L_80047EF4
    if (SIGNED(ctx->r2) >= 0) {
        // 0x80047F3C: addiu       $t0, $t0, -0x8
        ctx->r8 = ADD32(ctx->r8, -0X8);
            goto L_80047EF4;
    }
    // 0x80047F3C: addiu       $t0, $t0, -0x8
    ctx->r8 = ADD32(ctx->r8, -0X8);
    // 0x80047F40: jr          $ra
    // 0x80047F44: nop

    return;
    // 0x80047F44: nop

;}
RECOMP_FUNC void SysUtils_LightsSetAmbient(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x80047F48: sb          $a1, 0x4($a0)
    MEM_B(0X4, ctx->r4) = ctx->r5;
    // 0x80047F4C: sb          $a1, 0x0($a0)
    MEM_B(0X0, ctx->r4) = ctx->r5;
    // 0x80047F50: sb          $a2, 0x5($a0)
    MEM_B(0X5, ctx->r4) = ctx->r6;
    // 0x80047F54: sb          $a2, 0x1($a0)
    MEM_B(0X1, ctx->r4) = ctx->r6;
    // 0x80047F58: sb          $a3, 0x6($a0)
    MEM_B(0X6, ctx->r4) = ctx->r7;
    // 0x80047F5C: jr          $ra
    // 0x80047F60: sb          $a3, 0x2($a0)
    MEM_B(0X2, ctx->r4) = ctx->r7;
    return;
    // 0x80047F60: sb          $a3, 0x2($a0)
    MEM_B(0X2, ctx->r4) = ctx->r7;
;}
RECOMP_FUNC void SysUtils_LightsSetColor(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x80047F64: sb          $a1, 0x4($a0)
    MEM_B(0X4, ctx->r4) = ctx->r5;
    // 0x80047F68: sb          $a1, 0x0($a0)
    MEM_B(0X0, ctx->r4) = ctx->r5;
    // 0x80047F6C: sb          $a2, 0x5($a0)
    MEM_B(0X5, ctx->r4) = ctx->r6;
    // 0x80047F70: sb          $a2, 0x1($a0)
    MEM_B(0X1, ctx->r4) = ctx->r6;
    // 0x80047F74: sb          $a3, 0x6($a0)
    MEM_B(0X6, ctx->r4) = ctx->r7;
    // 0x80047F78: jr          $ra
    // 0x80047F7C: sb          $a3, 0x2($a0)
    MEM_B(0X2, ctx->r4) = ctx->r7;
    return;
    // 0x80047F7C: sb          $a3, 0x2($a0)
    MEM_B(0X2, ctx->r4) = ctx->r7;
;}
RECOMP_FUNC void SysUtils_LightsSetDirection(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x80047F80: sb          $a1, 0x8($a0)
    MEM_B(0X8, ctx->r4) = ctx->r5;
    // 0x80047F84: sb          $a2, 0x9($a0)
    MEM_B(0X9, ctx->r4) = ctx->r6;
    // 0x80047F88: jr          $ra
    // 0x80047F8C: sb          $a3, 0xA($a0)
    MEM_B(0XA, ctx->r4) = ctx->r7;
    return;
    // 0x80047F8C: sb          $a3, 0xA($a0)
    MEM_B(0XA, ctx->r4) = ctx->r7;
;}
RECOMP_FUNC void SysUtils_LightsSetSource(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x80047F90: addiu       $sp, $sp, -0x28
    ctx->r29 = ADD32(ctx->r29, -0X28);
    // 0x80047F94: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x80047F98: sw          $s0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r16;
    // 0x80047F9C: sb          $zero, 0x13($a0)
    MEM_B(0X13, ctx->r4) = 0;
    // 0x80047FA0: lb          $v0, 0x13($a0)
    ctx->r2 = MEM_B(ctx->r4, 0X13);
    // 0x80047FA4: or          $s0, $a0, $zero
    ctx->r16 = ctx->r4 | 0;
    // 0x80047FA8: sb          $v0, 0xF($a0)
    MEM_B(0XF, ctx->r4) = ctx->r2;
    // 0x80047FAC: sb          $v0, 0xB($a0)
    MEM_B(0XB, ctx->r4) = ctx->r2;
    // 0x80047FB0: sb          $v0, 0x7($a0)
    MEM_B(0X7, ctx->r4) = ctx->r2;
    // 0x80047FB4: jal         0x80047F48
    // 0x80047FB8: sb          $v0, 0x3($a0)
    MEM_B(0X3, ctx->r4) = ctx->r2;
    SysUtils_LightsSetAmbient(rdram, ctx);
        goto after_0;
    // 0x80047FB8: sb          $v0, 0x3($a0)
    MEM_B(0X3, ctx->r4) = ctx->r2;
    after_0:
    // 0x80047FBC: addiu       $a0, $s0, 0x8
    ctx->r4 = ADD32(ctx->r16, 0X8);
    // 0x80047FC0: sw          $a0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r4;
    // 0x80047FC4: lw          $a1, 0x38($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X38);
    // 0x80047FC8: lw          $a2, 0x3C($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X3C);
    // 0x80047FCC: jal         0x80047F64
    // 0x80047FD0: lw          $a3, 0x40($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X40);
    SysUtils_LightsSetColor(rdram, ctx);
        goto after_1;
    // 0x80047FD0: lw          $a3, 0x40($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X40);
    after_1:
    // 0x80047FD4: lw          $a0, 0x20($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X20);
    // 0x80047FD8: lw          $a1, 0x44($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X44);
    // 0x80047FDC: lw          $a2, 0x48($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X48);
    // 0x80047FE0: jal         0x80047F80
    // 0x80047FE4: lw          $a3, 0x4C($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X4C);
    SysUtils_LightsSetDirection(rdram, ctx);
        goto after_2;
    // 0x80047FE4: lw          $a3, 0x4C($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X4C);
    after_2:
    // 0x80047FE8: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    // 0x80047FEC: lw          $s0, 0x18($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X18);
    // 0x80047FF0: addiu       $sp, $sp, 0x28
    ctx->r29 = ADD32(ctx->r29, 0X28);
    // 0x80047FF4: jr          $ra
    // 0x80047FF8: nop

    return;
    // 0x80047FF8: nop

;}
RECOMP_FUNC void func_80047FFC(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x80047FFC: sra         $v0, $a0, 8
    ctx->r2 = S32(SIGNED(ctx->r4) >> 8);
    // 0x80048000: andi        $t6, $v0, 0x1
    ctx->r14 = ctx->r2 & 0X1;
    // 0x80048004: beq         $t6, $zero, L_8004801C
    if (ctx->r14 == 0) {
        // 0x80048008: sltiu       $at, $v0, 0x6
        ctx->r1 = ctx->r2 < 0X6 ? 1 : 0;
            goto L_8004801C;
    }
    // 0x80048008: sltiu       $at, $v0, 0x6
    ctx->r1 = ctx->r2 < 0X6 ? 1 : 0;
    // 0x8004800C: addiu       $t1, $zero, 0xFF
    ctx->r9 = ADD32(0, 0XFF);
    // 0x80048010: andi        $t7, $a0, 0xFF
    ctx->r15 = ctx->r4 & 0XFF;
    // 0x80048014: b           L_80048024
    // 0x80048018: subu        $v1, $t1, $t7
    ctx->r3 = SUB32(ctx->r9, ctx->r15);
        goto L_80048024;
    // 0x80048018: subu        $v1, $t1, $t7
    ctx->r3 = SUB32(ctx->r9, ctx->r15);
L_8004801C:
    // 0x8004801C: andi        $v1, $a0, 0xFF
    ctx->r3 = ctx->r4 & 0XFF;
    // 0x80048020: addiu       $t1, $zero, 0xFF
    ctx->r9 = ADD32(0, 0XFF);
L_80048024:
    // 0x80048024: beq         $at, $zero, L_800480D0
    if (ctx->r1 == 0) {
        // 0x80048028: nop
    
            goto L_800480D0;
    }
    // 0x80048028: nop

    // 0x8004802C: sll         $t8, $v0, 2
    ctx->r24 = S32(ctx->r2 << 2);
    // 0x80048030: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x80048034: addu        $at, $at, $t8
    gpr jr_addend_8004803C = ctx->r24;
    ctx->r1 = ADD32(ctx->r1, ctx->r24);
    // 0x80048038: lw          $t8, -0x6DD8($at)
    ctx->r24 = ADD32(ctx->r1, -0X6DD8);
    // 0x8004803C: jr          $t8
    // 0x80048040: nop

    switch (jr_addend_8004803C >> 2) {
        case 0: goto L_80048044; break;
        case 1: goto L_8004805C; break;
        case 2: goto L_80048074; break;
        case 3: goto L_8004808C; break;
        case 4: goto L_800480A4; break;
        case 5: goto L_800480BC; break;
        default: switch_error(__func__, 0x8004803C, 0x800E9228);
    }
    // 0x80048040: nop

L_80048044:
    // 0x80048044: lw          $v0, 0x10($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X10);
    // 0x80048048: lw          $a0, 0x14($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X14);
    // 0x8004804C: sw          $t1, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r9;
    // 0x80048050: sw          $v1, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r3;
    // 0x80048054: b           L_800480D0
    // 0x80048058: sw          $zero, 0x0($a0)
    MEM_W(0X0, ctx->r4) = 0;
        goto L_800480D0;
    // 0x80048058: sw          $zero, 0x0($a0)
    MEM_W(0X0, ctx->r4) = 0;
L_8004805C:
    // 0x8004805C: lw          $v0, 0x10($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X10);
    // 0x80048060: lw          $a0, 0x14($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X14);
    // 0x80048064: sw          $v1, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r3;
    // 0x80048068: sw          $t1, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r9;
    // 0x8004806C: b           L_800480D0
    // 0x80048070: sw          $zero, 0x0($a0)
    MEM_W(0X0, ctx->r4) = 0;
        goto L_800480D0;
    // 0x80048070: sw          $zero, 0x0($a0)
    MEM_W(0X0, ctx->r4) = 0;
L_80048074:
    // 0x80048074: lw          $v0, 0x10($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X10);
    // 0x80048078: lw          $a0, 0x14($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X14);
    // 0x8004807C: sw          $zero, 0x0($a3)
    MEM_W(0X0, ctx->r7) = 0;
    // 0x80048080: sw          $t1, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r9;
    // 0x80048084: b           L_800480D0
    // 0x80048088: sw          $v1, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r3;
        goto L_800480D0;
    // 0x80048088: sw          $v1, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r3;
L_8004808C:
    // 0x8004808C: lw          $v0, 0x10($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X10);
    // 0x80048090: lw          $a0, 0x14($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X14);
    // 0x80048094: sw          $zero, 0x0($a3)
    MEM_W(0X0, ctx->r7) = 0;
    // 0x80048098: sw          $v1, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r3;
    // 0x8004809C: b           L_800480D0
    // 0x800480A0: sw          $t1, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r9;
        goto L_800480D0;
    // 0x800480A0: sw          $t1, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r9;
L_800480A4:
    // 0x800480A4: lw          $v0, 0x10($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X10);
    // 0x800480A8: lw          $a0, 0x14($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X14);
    // 0x800480AC: sw          $v1, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r3;
    // 0x800480B0: sw          $zero, 0x0($v0)
    MEM_W(0X0, ctx->r2) = 0;
    // 0x800480B4: b           L_800480D0
    // 0x800480B8: sw          $t1, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r9;
        goto L_800480D0;
    // 0x800480B8: sw          $t1, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r9;
L_800480BC:
    // 0x800480BC: lw          $v0, 0x10($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X10);
    // 0x800480C0: lw          $a0, 0x14($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X14);
    // 0x800480C4: sw          $t1, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r9;
    // 0x800480C8: sw          $zero, 0x0($v0)
    MEM_W(0X0, ctx->r2) = 0;
    // 0x800480CC: sw          $v1, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r3;
L_800480D0:
    // 0x800480D0: multu       $a1, $a2
    result = U64(U32(ctx->r5)) * U64(U32(ctx->r6)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x800480D4: ori         $t2, $zero, 0xFE01
    ctx->r10 = 0 | 0XFE01;
    // 0x800480D8: lw          $t4, 0x0($a3)
    ctx->r12 = MEM_W(ctx->r7, 0X0);
    // 0x800480DC: lw          $v0, 0x10($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X10);
    // 0x800480E0: lw          $a0, 0x14($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X14);
    // 0x800480E4: mflo        $v1
    ctx->r3 = lo;
    // 0x800480E8: nop

    // 0x800480EC: nop

    // 0x800480F0: multu       $a2, $t2
    result = U64(U32(ctx->r6)) * U64(U32(ctx->r10)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x800480F4: mflo        $t9
    ctx->r25 = lo;
    // 0x800480F8: nop

    // 0x800480FC: nop

    // 0x80048100: multu       $v1, $t1
    result = U64(U32(ctx->r3)) * U64(U32(ctx->r9)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80048104: mflo        $t3
    ctx->r11 = lo;
    // 0x80048108: subu        $t0, $t9, $t3
    ctx->r8 = SUB32(ctx->r25, ctx->r11);
    // 0x8004810C: nop

    // 0x80048110: multu       $t4, $v1
    result = U64(U32(ctx->r12)) * U64(U32(ctx->r3)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80048114: mflo        $t5
    ctx->r13 = lo;
    // 0x80048118: addu        $t6, $t5, $t0
    ctx->r14 = ADD32(ctx->r13, ctx->r8);
    // 0x8004811C: nop

    // 0x80048120: div         $zero, $t6, $t2
    lo = S32(S64(S32(ctx->r14)) / S64(S32(ctx->r10))); hi = S32(S64(S32(ctx->r14)) % S64(S32(ctx->r10)));
    // 0x80048124: mflo        $t7
    ctx->r15 = lo;
    // 0x80048128: sw          $t7, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r15;
    // 0x8004812C: lw          $t8, 0x0($v0)
    ctx->r24 = MEM_W(ctx->r2, 0X0);
    // 0x80048130: bne         $t2, $zero, L_8004813C
    if (ctx->r10 != 0) {
        // 0x80048134: nop
    
            goto L_8004813C;
    }
    // 0x80048134: nop

    // 0x80048138: break       7
    do_break(2147778872);
L_8004813C:
    // 0x8004813C: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x80048140: bne         $t2, $at, L_80048154
    if (ctx->r10 != ctx->r1) {
        // 0x80048144: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_80048154;
    }
    // 0x80048144: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x80048148: bne         $t6, $at, L_80048154
    if (ctx->r14 != ctx->r1) {
        // 0x8004814C: nop
    
            goto L_80048154;
    }
    // 0x8004814C: nop

    // 0x80048150: break       6
    do_break(2147778896);
L_80048154:
    // 0x80048154: multu       $t8, $v1
    result = U64(U32(ctx->r24)) * U64(U32(ctx->r3)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80048158: mflo        $t9
    ctx->r25 = lo;
    // 0x8004815C: addu        $t3, $t9, $t0
    ctx->r11 = ADD32(ctx->r25, ctx->r8);
    // 0x80048160: nop

    // 0x80048164: div         $zero, $t3, $t2
    lo = S32(S64(S32(ctx->r11)) / S64(S32(ctx->r10))); hi = S32(S64(S32(ctx->r11)) % S64(S32(ctx->r10)));
    // 0x80048168: mflo        $t4
    ctx->r12 = lo;
    // 0x8004816C: sw          $t4, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r12;
    // 0x80048170: lw          $t5, 0x0($a0)
    ctx->r13 = MEM_W(ctx->r4, 0X0);
    // 0x80048174: bne         $t2, $zero, L_80048180
    if (ctx->r10 != 0) {
        // 0x80048178: nop
    
            goto L_80048180;
    }
    // 0x80048178: nop

    // 0x8004817C: break       7
    do_break(2147778940);
L_80048180:
    // 0x80048180: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x80048184: bne         $t2, $at, L_80048198
    if (ctx->r10 != ctx->r1) {
        // 0x80048188: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_80048198;
    }
    // 0x80048188: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x8004818C: bne         $t3, $at, L_80048198
    if (ctx->r11 != ctx->r1) {
        // 0x80048190: nop
    
            goto L_80048198;
    }
    // 0x80048190: nop

    // 0x80048194: break       6
    do_break(2147778964);
L_80048198:
    // 0x80048198: multu       $t5, $v1
    result = U64(U32(ctx->r13)) * U64(U32(ctx->r3)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x8004819C: mflo        $t6
    ctx->r14 = lo;
    // 0x800481A0: addu        $t7, $t6, $t0
    ctx->r15 = ADD32(ctx->r14, ctx->r8);
    // 0x800481A4: nop

    // 0x800481A8: div         $zero, $t7, $t2
    lo = S32(S64(S32(ctx->r15)) / S64(S32(ctx->r10))); hi = S32(S64(S32(ctx->r15)) % S64(S32(ctx->r10)));
    // 0x800481AC: mflo        $t8
    ctx->r24 = lo;
    // 0x800481B0: sw          $t8, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r24;
    // 0x800481B4: bne         $t2, $zero, L_800481C0
    if (ctx->r10 != 0) {
        // 0x800481B8: nop
    
            goto L_800481C0;
    }
    // 0x800481B8: nop

    // 0x800481BC: break       7
    do_break(2147779004);
L_800481C0:
    // 0x800481C0: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x800481C4: bne         $t2, $at, L_800481D8
    if (ctx->r10 != ctx->r1) {
        // 0x800481C8: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_800481D8;
    }
    // 0x800481C8: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x800481CC: bne         $t7, $at, L_800481D8
    if (ctx->r15 != ctx->r1) {
        // 0x800481D0: nop
    
            goto L_800481D8;
    }
    // 0x800481D0: nop

    // 0x800481D4: break       6
    do_break(2147779028);
L_800481D8:
    // 0x800481D8: jr          $ra
    // 0x800481DC: nop

    return;
    // 0x800481DC: nop

;}
RECOMP_FUNC void func_800481E0(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800481E0: lui         $at, 0x4434
    ctx->r1 = S32(0X4434 << 16);
    // 0x800481E4: mtc1        $a2, $f14
    ctx->f14.u32l = ctx->r6;
    // 0x800481E8: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x800481EC: lui         $at, 0x4580
    ctx->r1 = S32(0X4580 << 16);
    // 0x800481F0: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x800481F4: div.s       $f6, $f14, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = DIV_S(ctx->f14.fl, ctx->f4.fl);
    // 0x800481F8: addiu       $sp, $sp, -0x60
    ctx->r29 = ADD32(ctx->r29, -0X60);
    // 0x800481FC: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x80048200: sw          $s0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r16;
    // 0x80048204: or          $s0, $a0, $zero
    ctx->r16 = ctx->r4 | 0;
    // 0x80048208: sw          $a1, 0x64($sp)
    MEM_W(0X64, ctx->r29) = ctx->r5;
    // 0x8004820C: sw          $a3, 0x6C($sp)
    MEM_W(0X6C, ctx->r29) = ctx->r7;
    // 0x80048210: mul.s       $f12, $f6, $f8
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f12.fl = MUL_S(ctx->f6.fl, ctx->f8.fl);
    // 0x80048214: jal         0x80047BE0
    // 0x80048218: nop

    SysUtils_Round(rdram, ctx);
        goto after_0;
    // 0x80048218: nop

    after_0:
    // 0x8004821C: lui         $v1, 0x8015
    ctx->r3 = S32(0X8015 << 16);
    // 0x80048220: addiu       $t9, $v0, 0x400
    ctx->r25 = ADD32(ctx->r2, 0X400);
    // 0x80048224: addiu       $v1, $v1, 0x4350
    ctx->r3 = ADD32(ctx->r3, 0X4350);
    // 0x80048228: andi        $t0, $t9, 0xFFF
    ctx->r8 = ctx->r25 & 0XFFF;
    // 0x8004822C: andi        $t6, $v0, 0xFFF
    ctx->r14 = ctx->r2 & 0XFFF;
    // 0x80048230: sll         $t7, $t6, 2
    ctx->r15 = S32(ctx->r14 << 2);
    // 0x80048234: sll         $t1, $t0, 2
    ctx->r9 = S32(ctx->r8 << 2);
    // 0x80048238: addu        $t2, $v1, $t1
    ctx->r10 = ADD32(ctx->r3, ctx->r9);
    // 0x8004823C: addu        $t8, $v1, $t7
    ctx->r24 = ADD32(ctx->r3, ctx->r15);
    // 0x80048240: lwc1        $f10, 0x0($t8)
    ctx->f10.u32l = MEM_W(ctx->r24, 0X0);
    // 0x80048244: lwc1        $f4, 0x0($t2)
    ctx->f4.u32l = MEM_W(ctx->r10, 0X0);
    // 0x80048248: lwc1        $f2, 0x70($sp)
    ctx->f2.u32l = MEM_W(ctx->r29, 0X70);
    // 0x8004824C: lwc1        $f14, 0x7C($sp)
    ctx->f14.u32l = MEM_W(ctx->r29, 0X7C);
    // 0x80048250: div.s       $f6, $f10, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = DIV_S(ctx->f10.fl, ctx->f4.fl);
    // 0x80048254: lwc1        $f4, 0x6C($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X6C);
    // 0x80048258: lwc1        $f18, 0x78($sp)
    ctx->f18.u32l = MEM_W(ctx->r29, 0X78);
    // 0x8004825C: lui         $at, 0x4800
    ctx->r1 = S32(0X4800 << 16);
    // 0x80048260: mul.s       $f0, $f6, $f2
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f0.fl = MUL_S(ctx->f6.fl, ctx->f2.fl);
    // 0x80048264: add.s       $f8, $f14, $f0
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f8.fl = ctx->f14.fl + ctx->f0.fl;
    // 0x80048268: sub.s       $f10, $f14, $f0
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f10.fl = ctx->f14.fl - ctx->f0.fl;
    // 0x8004826C: mul.s       $f0, $f0, $f4
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f0.fl = MUL_S(ctx->f0.fl, ctx->f4.fl);
    // 0x80048270: swc1        $f8, 0x4C($sp)
    MEM_W(0X4C, ctx->r29) = ctx->f8.u32l;
    // 0x80048274: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x80048278: swc1        $f10, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->f10.u32l;
    // 0x8004827C: mul.s       $f10, $f8, $f2
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f10.fl = MUL_S(ctx->f8.fl, ctx->f2.fl);
    // 0x80048280: sub.s       $f6, $f18, $f0
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f6.fl = ctx->f18.fl - ctx->f0.fl;
    // 0x80048284: add.s       $f16, $f18, $f0
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f16.fl = ctx->f18.fl + ctx->f0.fl;
    // 0x80048288: swc1        $f6, 0x54($sp)
    MEM_W(0X54, ctx->r29) = ctx->f6.u32l;
    // 0x8004828C: lwc1        $f4, 0x54($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X54);
    // 0x80048290: swc1        $f10, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->f10.u32l;
    // 0x80048294: swc1        $f16, 0x50($sp)
    MEM_W(0X50, ctx->r29) = ctx->f16.u32l;
    // 0x80048298: sub.s       $f6, $f16, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = ctx->f16.fl - ctx->f4.fl;
    // 0x8004829C: swc1        $f6, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->f6.u32l;
    // 0x800482A0: lwc1        $f8, 0x24($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X24);
    // 0x800482A4: jal         0x80047BE0
    // 0x800482A8: div.s       $f12, $f10, $f8
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f12.fl = DIV_S(ctx->f10.fl, ctx->f8.fl);
    SysUtils_Round(rdram, ctx);
        goto after_1;
    // 0x800482A8: div.s       $f12, $f10, $f8
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f12.fl = DIV_S(ctx->f10.fl, ctx->f8.fl);
    after_1:
    // 0x800482AC: lui         $at, 0xFFFF
    ctx->r1 = S32(0XFFFF << 16);
    // 0x800482B0: and         $t3, $v0, $at
    ctx->r11 = ctx->r2 & ctx->r1;
    // 0x800482B4: sll         $t4, $v0, 16
    ctx->r12 = S32(ctx->r2 << 16);
    // 0x800482B8: sw          $t3, 0x0($s0)
    MEM_W(0X0, ctx->r16) = ctx->r11;
    // 0x800482BC: sw          $t4, 0x20($s0)
    MEM_W(0X20, ctx->r16) = ctx->r12;
    // 0x800482C0: lwc1        $f6, 0x48($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X48);
    // 0x800482C4: lwc1        $f4, 0x4C($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X4C);
    // 0x800482C8: lwc1        $f10, 0x28($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0X28);
    // 0x800482CC: sub.s       $f0, $f4, $f6
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f0.fl = ctx->f4.fl - ctx->f6.fl;
    // 0x800482D0: swc1        $f0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->f0.u32l;
    // 0x800482D4: jal         0x80047BE0
    // 0x800482D8: div.s       $f12, $f10, $f0
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f12.fl = DIV_S(ctx->f10.fl, ctx->f0.fl);
    SysUtils_Round(rdram, ctx);
        goto after_2;
    // 0x800482D8: div.s       $f12, $f10, $f0
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f12.fl = DIV_S(ctx->f10.fl, ctx->f0.fl);
    after_2:
    // 0x800482DC: srl         $t5, $v0, 16
    ctx->r13 = S32(U32(ctx->r2) >> 16);
    // 0x800482E0: andi        $t6, $v0, 0xFFFF
    ctx->r14 = ctx->r2 & 0XFFFF;
    // 0x800482E4: sw          $t5, 0x8($s0)
    MEM_W(0X8, ctx->r16) = ctx->r13;
    // 0x800482E8: sw          $t6, 0x28($s0)
    MEM_W(0X28, ctx->r16) = ctx->r14;
    // 0x800482EC: lwc1        $f4, 0x54($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X54);
    // 0x800482F0: lwc1        $f8, 0x50($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X50);
    // 0x800482F4: lui         $at, 0x4780
    ctx->r1 = S32(0X4780 << 16);
    // 0x800482F8: mtc1        $at, $f10
    ctx->f10.u32l = ctx->r1;
    // 0x800482FC: add.s       $f6, $f8, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = ctx->f8.fl + ctx->f4.fl;
    // 0x80048300: lwc1        $f4, 0x24($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X24);
    // 0x80048304: mul.s       $f8, $f6, $f10
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f8.fl = MUL_S(ctx->f6.fl, ctx->f10.fl);
    // 0x80048308: jal         0x80047BE0
    // 0x8004830C: div.s       $f12, $f8, $f4
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f12.fl = DIV_S(ctx->f8.fl, ctx->f4.fl);
    SysUtils_Round(rdram, ctx);
        goto after_3;
    // 0x8004830C: div.s       $f12, $f8, $f4
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f12.fl = DIV_S(ctx->f8.fl, ctx->f4.fl);
    after_3:
    // 0x80048310: lwc1        $f6, 0x4C($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X4C);
    // 0x80048314: lwc1        $f10, 0x48($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0X48);
    // 0x80048318: lui         $at, 0x4780
    ctx->r1 = S32(0X4780 << 16);
    // 0x8004831C: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x80048320: add.s       $f8, $f6, $f10
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f8.fl = ctx->f6.fl + ctx->f10.fl;
    // 0x80048324: lwc1        $f10, 0x20($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0X20);
    // 0x80048328: sw          $v0, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r2;
    // 0x8004832C: mul.s       $f6, $f8, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = MUL_S(ctx->f8.fl, ctx->f4.fl);
    // 0x80048330: jal         0x80047BE0
    // 0x80048334: div.s       $f12, $f6, $f10
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f12.fl = DIV_S(ctx->f6.fl, ctx->f10.fl);
    SysUtils_Round(rdram, ctx);
        goto after_4;
    // 0x80048334: div.s       $f12, $f6, $f10
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f12.fl = DIV_S(ctx->f6.fl, ctx->f10.fl);
    after_4:
    // 0x80048338: lw          $v1, 0x44($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X44);
    // 0x8004833C: lwc1        $f14, 0x74($sp)
    ctx->f14.u32l = MEM_W(ctx->r29, 0X74);
    // 0x80048340: lwc1        $f16, 0x70($sp)
    ctx->f16.u32l = MEM_W(ctx->r29, 0X70);
    // 0x80048344: lui         $at, 0xFFFF
    ctx->r1 = S32(0XFFFF << 16);
    // 0x80048348: and         $t7, $v1, $at
    ctx->r15 = ctx->r3 & ctx->r1;
    // 0x8004834C: add.s       $f0, $f14, $f16
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f0.fl = ctx->f14.fl + ctx->f16.fl;
    // 0x80048350: lui         $at, 0x4780
    ctx->r1 = S32(0X4780 << 16);
    // 0x80048354: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x80048358: sub.s       $f2, $f16, $f14
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f2.fl = ctx->f16.fl - ctx->f14.fl;
    // 0x8004835C: srl         $t8, $v0, 16
    ctx->r24 = S32(U32(ctx->r2) >> 16);
    // 0x80048360: mul.s       $f4, $f0, $f8
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f4.fl = MUL_S(ctx->f0.fl, ctx->f8.fl);
    // 0x80048364: andi        $t1, $v0, 0xFFFF
    ctx->r9 = ctx->r2 & 0XFFFF;
    // 0x80048368: sll         $t0, $v1, 16
    ctx->r8 = S32(ctx->r3 << 16);
    // 0x8004836C: or          $t9, $t7, $t8
    ctx->r25 = ctx->r15 | ctx->r24;
    // 0x80048370: or          $t2, $t0, $t1
    ctx->r10 = ctx->r8 | ctx->r9;
    // 0x80048374: sw          $t9, 0x10($s0)
    MEM_W(0X10, ctx->r16) = ctx->r25;
    // 0x80048378: sw          $t2, 0x30($s0)
    MEM_W(0X30, ctx->r16) = ctx->r10;
    // 0x8004837C: swc1        $f2, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->f2.u32l;
    // 0x80048380: swc1        $f0, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->f0.u32l;
    // 0x80048384: jal         0x80047BE0
    // 0x80048388: div.s       $f12, $f4, $f2
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f12.fl = DIV_S(ctx->f4.fl, ctx->f2.fl);
    SysUtils_Round(rdram, ctx);
        goto after_5;
    // 0x80048388: div.s       $f12, $f4, $f2
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f12.fl = DIV_S(ctx->f4.fl, ctx->f2.fl);
    after_5:
    // 0x8004838C: lui         $at, 0xFFFF
    ctx->r1 = S32(0XFFFF << 16);
    // 0x80048390: lwc1        $f2, 0x20($sp)
    ctx->f2.u32l = MEM_W(ctx->r29, 0X20);
    // 0x80048394: and         $t3, $v0, $at
    ctx->r11 = ctx->r2 & ctx->r1;
    // 0x80048398: ori         $t4, $t3, 0xFFFF
    ctx->r12 = ctx->r11 | 0XFFFF;
    // 0x8004839C: sll         $t5, $v0, 16
    ctx->r13 = S32(ctx->r2 << 16);
    // 0x800483A0: sw          $t4, 0x14($s0)
    MEM_W(0X14, ctx->r16) = ctx->r12;
    // 0x800483A4: sw          $t5, 0x34($s0)
    MEM_W(0X34, ctx->r16) = ctx->r13;
    // 0x800483A8: lwc1        $f10, 0x74($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0X74);
    // 0x800483AC: lwc1        $f6, 0x28($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X28);
    // 0x800483B0: mul.s       $f8, $f6, $f10
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f8.fl = MUL_S(ctx->f6.fl, ctx->f10.fl);
    // 0x800483B4: jal         0x80047BE0
    // 0x800483B8: div.s       $f12, $f8, $f2
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f12.fl = DIV_S(ctx->f8.fl, ctx->f2.fl);
    SysUtils_Round(rdram, ctx);
        goto after_6;
    // 0x800483B8: div.s       $f12, $f8, $f2
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f12.fl = DIV_S(ctx->f8.fl, ctx->f2.fl);
    after_6:
    // 0x800483BC: lui         $at, 0xFFFF
    ctx->r1 = S32(0XFFFF << 16);
    // 0x800483C0: and         $t6, $v0, $at
    ctx->r14 = ctx->r2 & ctx->r1;
    // 0x800483C4: lwc1        $f0, 0x24($sp)
    ctx->f0.u32l = MEM_W(ctx->r29, 0X24);
    // 0x800483C8: lui         $at, 0x4000
    ctx->r1 = S32(0X4000 << 16);
    // 0x800483CC: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x800483D0: sll         $t7, $v0, 16
    ctx->r15 = S32(ctx->r2 << 16);
    // 0x800483D4: sw          $t6, 0x1C($s0)
    MEM_W(0X1C, ctx->r16) = ctx->r14;
    // 0x800483D8: c.lt.s      $f4, $f0
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    c1cs = ctx->f4.fl < ctx->f0.fl;
    // 0x800483DC: sw          $t7, 0x3C($s0)
    MEM_W(0X3C, ctx->r16) = ctx->r15;
    // 0x800483E0: sw          $zero, 0x4($s0)
    MEM_W(0X4, ctx->r16) = 0;
    // 0x800483E4: sw          $zero, 0x24($s0)
    MEM_W(0X24, ctx->r16) = 0;
    // 0x800483E8: sw          $zero, 0xC($s0)
    MEM_W(0XC, ctx->r16) = 0;
    // 0x800483EC: sw          $zero, 0x2C($s0)
    MEM_W(0X2C, ctx->r16) = 0;
    // 0x800483F0: sw          $zero, 0x18($s0)
    MEM_W(0X18, ctx->r16) = 0;
    // 0x800483F4: bc1f        L_800484A8
    if (!c1cs) {
        // 0x800483F8: sw          $zero, 0x38($s0)
        MEM_W(0X38, ctx->r16) = 0;
            goto L_800484A8;
    }
    // 0x800483F8: sw          $zero, 0x38($s0)
    MEM_W(0X38, ctx->r16) = 0;
    // 0x800483FC: lui         $at, 0x4800
    ctx->r1 = S32(0X4800 << 16);
    // 0x80048400: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x80048404: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
    // 0x80048408: lw          $v1, 0x64($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X64);
    // 0x8004840C: div.s       $f10, $f6, $f0
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f10.fl = DIV_S(ctx->f6.fl, ctx->f0.fl);
    // 0x80048410: lui         $at, 0x4F00
    ctx->r1 = S32(0X4F00 << 16);
    // 0x80048414: addiu       $t0, $zero, 0x1
    ctx->r8 = ADD32(0, 0X1);
    // 0x80048418: cfc1        $t8, $FpcCsr
    ctx->r24 = get_cop1_cs();
    // 0x8004841C: ctc1        $v0, $FpcCsr
    set_cop1_cs(ctx->r2);
    // 0x80048420: nop

    // 0x80048424: cvt.w.s     $f8, $f10
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    ctx->f8.u32l = CVT_W_S(ctx->f10.fl);
    // 0x80048428: cfc1        $v0, $FpcCsr
    ctx->r2 = get_cop1_cs();
    // 0x8004842C: nop

    // 0x80048430: andi        $v0, $v0, 0x78
    ctx->r2 = ctx->r2 & 0X78;
    // 0x80048434: beql        $v0, $zero, L_80048484
    if (ctx->r2 == 0) {
        // 0x80048438: mfc1        $v0, $f8
        ctx->r2 = (int32_t)ctx->f8.u32l;
            goto L_80048484;
    }
    goto skip_0;
    // 0x80048438: mfc1        $v0, $f8
    ctx->r2 = (int32_t)ctx->f8.u32l;
    skip_0:
    // 0x8004843C: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x80048440: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
    // 0x80048444: sub.s       $f8, $f10, $f8
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f8.fl = ctx->f10.fl - ctx->f8.fl;
    // 0x80048448: ctc1        $v0, $FpcCsr
    set_cop1_cs(ctx->r2);
    // 0x8004844C: nop

    // 0x80048450: cvt.w.s     $f8, $f8
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 8);
    ctx->f8.u32l = CVT_W_S(ctx->f8.fl);
    // 0x80048454: cfc1        $v0, $FpcCsr
    ctx->r2 = get_cop1_cs();
    // 0x80048458: nop

    // 0x8004845C: andi        $v0, $v0, 0x78
    ctx->r2 = ctx->r2 & 0X78;
    // 0x80048460: bne         $v0, $zero, L_80048478
    if (ctx->r2 != 0) {
        // 0x80048464: nop
    
            goto L_80048478;
    }
    // 0x80048464: nop

    // 0x80048468: mfc1        $v0, $f8
    ctx->r2 = (int32_t)ctx->f8.u32l;
    // 0x8004846C: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x80048470: b           L_80048490
    // 0x80048474: or          $v0, $v0, $at
    ctx->r2 = ctx->r2 | ctx->r1;
        goto L_80048490;
    // 0x80048474: or          $v0, $v0, $at
    ctx->r2 = ctx->r2 | ctx->r1;
L_80048478:
    // 0x80048478: b           L_80048490
    // 0x8004847C: addiu       $v0, $zero, -0x1
    ctx->r2 = ADD32(0, -0X1);
        goto L_80048490;
    // 0x8004847C: addiu       $v0, $zero, -0x1
    ctx->r2 = ADD32(0, -0X1);
    // 0x80048480: mfc1        $v0, $f8
    ctx->r2 = (int32_t)ctx->f8.u32l;
L_80048484:
    // 0x80048484: nop

    // 0x80048488: bltz        $v0, L_80048478
    if (SIGNED(ctx->r2) < 0) {
        // 0x8004848C: nop
    
            goto L_80048478;
    }
    // 0x8004848C: nop

L_80048490:
    // 0x80048490: ctc1        $t8, $FpcCsr
    set_cop1_cs(ctx->r24);
    // 0x80048494: andi        $t9, $v0, 0xFFFF
    ctx->r25 = ctx->r2 & 0XFFFF;
    // 0x80048498: bne         $t9, $zero, L_800484B4
    if (ctx->r25 != 0) {
        // 0x8004849C: sh          $v0, 0x0($v1)
        MEM_H(0X0, ctx->r3) = ctx->r2;
            goto L_800484B4;
    }
    // 0x8004849C: sh          $v0, 0x0($v1)
    MEM_H(0X0, ctx->r3) = ctx->r2;
    // 0x800484A0: b           L_800484B4
    // 0x800484A4: sh          $t0, 0x0($v1)
    MEM_H(0X0, ctx->r3) = ctx->r8;
        goto L_800484B4;
    // 0x800484A4: sh          $t0, 0x0($v1)
    MEM_H(0X0, ctx->r3) = ctx->r8;
L_800484A8:
    // 0x800484A8: lw          $t2, 0x64($sp)
    ctx->r10 = MEM_W(ctx->r29, 0X64);
    // 0x800484AC: ori         $t1, $zero, 0xFFFF
    ctx->r9 = 0 | 0XFFFF;
    // 0x800484B0: sh          $t1, 0x0($t2)
    MEM_H(0X0, ctx->r10) = ctx->r9;
L_800484B4:
    // 0x800484B4: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    // 0x800484B8: lw          $s0, 0x18($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X18);
    // 0x800484BC: addiu       $sp, $sp, 0x60
    ctx->r29 = ADD32(ctx->r29, 0X60);
    // 0x800484C0: jr          $ra
    // 0x800484C4: nop

    return;
    // 0x800484C4: nop

;}
RECOMP_FUNC void func_800484C8(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800484C8: addiu       $sp, $sp, -0x98
    ctx->r29 = ADD32(ctx->r29, -0X98);
    // 0x800484CC: sw          $a2, 0xA0($sp)
    MEM_W(0XA0, ctx->r29) = ctx->r6;
    // 0x800484D0: lwc1        $f4, 0xA0($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0XA0);
    // 0x800484D4: lwc1        $f8, 0xAC($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0XAC);
    // 0x800484D8: sw          $a3, 0xA4($sp)
    MEM_W(0XA4, ctx->r29) = ctx->r7;
    // 0x800484DC: lwc1        $f10, 0xA4($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0XA4);
    // 0x800484E0: lwc1        $f6, 0xB0($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0XB0);
    // 0x800484E4: sub.s       $f14, $f4, $f8
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f14.fl = ctx->f4.fl - ctx->f8.fl;
    // 0x800484E8: lwc1        $f8, 0xB4($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0XB4);
    // 0x800484EC: lwc1        $f4, 0xA8($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0XA8);
    // 0x800484F0: sub.s       $f16, $f10, $f6
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f16.fl = ctx->f10.fl - ctx->f6.fl;
    // 0x800484F4: mul.s       $f10, $f14, $f14
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f10.fl = MUL_S(ctx->f14.fl, ctx->f14.fl);
    // 0x800484F8: sdc1        $f24, 0x20($sp)
    CHECK_FR(ctx, 24);
    SD(ctx->f24.u64, 0X20, ctx->r29);
    // 0x800484FC: sub.s       $f18, $f4, $f8
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f18.fl = ctx->f4.fl - ctx->f8.fl;
    // 0x80048500: mul.s       $f6, $f16, $f16
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f6.fl = MUL_S(ctx->f16.fl, ctx->f16.fl);
    // 0x80048504: sdc1        $f22, 0x18($sp)
    CHECK_FR(ctx, 22);
    SD(ctx->f22.u64, 0X18, ctx->r29);
    // 0x80048508: sdc1        $f20, 0x10($sp)
    CHECK_FR(ctx, 20);
    SD(ctx->f20.u64, 0X10, ctx->r29);
    // 0x8004850C: mul.s       $f8, $f18, $f18
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f8.fl = MUL_S(ctx->f18.fl, ctx->f18.fl);
    // 0x80048510: sw          $ra, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r31;
    // 0x80048514: sw          $a0, 0x98($sp)
    MEM_W(0X98, ctx->r29) = ctx->r4;
    // 0x80048518: sw          $a1, 0x9C($sp)
    MEM_W(0X9C, ctx->r29) = ctx->r5;
    // 0x8004851C: mov.s       $f20, $f14
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 14);
    ctx->f20.fl = ctx->f14.fl;
    // 0x80048520: add.s       $f4, $f10, $f6
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f4.fl = ctx->f10.fl + ctx->f6.fl;
    // 0x80048524: mtc1        $zero, $f10
    ctx->f10.u32l = 0;
    // 0x80048528: mov.s       $f22, $f16
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 16);
    ctx->f22.fl = ctx->f16.fl;
    // 0x8004852C: mov.s       $f24, $f18
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 18);
    ctx->f24.fl = ctx->f18.fl;
    // 0x80048530: add.s       $f12, $f4, $f8
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f12.fl = ctx->f4.fl + ctx->f8.fl;
    // 0x80048534: c.le.s      $f12, $f10
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 10);
    c1cs = ctx->f12.fl <= ctx->f10.fl;
    // 0x80048538: nop

    // 0x8004853C: bc1tl       L_80048840
    if (c1cs) {
        // 0x80048540: lw          $ra, 0x2C($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X2C);
            goto L_80048840;
    }
    goto skip_0;
    // 0x80048540: lw          $ra, 0x2C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X2C);
    skip_0:
    // 0x80048544: sw          $a1, 0x9C($sp)
    MEM_W(0X9C, ctx->r29) = ctx->r5;
    // 0x80048548: swc1        $f14, 0x60($sp)
    MEM_W(0X60, ctx->r29) = ctx->f14.u32l;
    // 0x8004854C: swc1        $f16, 0x5C($sp)
    MEM_W(0X5C, ctx->r29) = ctx->f16.u32l;
    // 0x80048550: jal         0x800C7010
    // 0x80048554: swc1        $f18, 0x58($sp)
    MEM_W(0X58, ctx->r29) = ctx->f18.u32l;
    _nsqrtf(rdram, ctx);
        goto after_0;
    // 0x80048554: swc1        $f18, 0x58($sp)
    MEM_W(0X58, ctx->r29) = ctx->f18.u32l;
    after_0:
    // 0x80048558: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x8004855C: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x80048560: lw          $a2, 0x9C($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X9C);
    // 0x80048564: lwc1        $f14, 0x60($sp)
    ctx->f14.u32l = MEM_W(ctx->r29, 0X60);
    // 0x80048568: div.s       $f2, $f6, $f0
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f2.fl = DIV_S(ctx->f6.fl, ctx->f0.fl);
    // 0x8004856C: lwc1        $f16, 0x5C($sp)
    ctx->f16.u32l = MEM_W(ctx->r29, 0X5C);
    // 0x80048570: lwc1        $f18, 0x58($sp)
    ctx->f18.u32l = MEM_W(ctx->r29, 0X58);
    // 0x80048574: mul.s       $f12, $f22, $f2
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f12.fl = MUL_S(ctx->f22.fl, ctx->f2.fl);
    // 0x80048578: nop

    // 0x8004857C: mul.s       $f4, $f20, $f2
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f4.fl = MUL_S(ctx->f20.fl, ctx->f2.fl);
    // 0x80048580: nop

    // 0x80048584: mul.s       $f10, $f24, $f2
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f24.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f10.fl = MUL_S(ctx->f24.fl, ctx->f2.fl);
    // 0x80048588: swc1        $f12, 0x18($a2)
    MEM_W(0X18, ctx->r6) = ctx->f12.u32l;
    // 0x8004858C: swc1        $f4, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->f4.u32l;
    // 0x80048590: lwc1        $f8, 0x48($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X48);
    // 0x80048594: swc1        $f8, 0x8($a2)
    MEM_W(0X8, ctx->r6) = ctx->f8.u32l;
    // 0x80048598: swc1        $f10, 0x50($sp)
    MEM_W(0X50, ctx->r29) = ctx->f10.u32l;
    // 0x8004859C: lwc1        $f6, 0x50($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X50);
    // 0x800485A0: swc1        $f6, 0x28($a2)
    MEM_W(0X28, ctx->r6) = ctx->f6.u32l;
    // 0x800485A4: lwc1        $f4, 0xA0($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0XA0);
    // 0x800485A8: lwc1        $f10, 0x48($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0X48);
    // 0x800485AC: neg.s       $f8, $f4
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f4.fl); 
    ctx->f8.fl = -ctx->f4.fl;
    // 0x800485B0: lwc1        $f4, 0xA4($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0XA4);
    // 0x800485B4: mul.s       $f6, $f8, $f10
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f6.fl = MUL_S(ctx->f8.fl, ctx->f10.fl);
    // 0x800485B8: swc1        $f8, 0x54($sp)
    MEM_W(0X54, ctx->r29) = ctx->f8.u32l;
    // 0x800485BC: mul.s       $f8, $f4, $f12
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f8.fl = MUL_S(ctx->f4.fl, ctx->f12.fl);
    // 0x800485C0: lwc1        $f4, 0x50($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X50);
    // 0x800485C4: sub.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = ctx->f6.fl - ctx->f8.fl;
    // 0x800485C8: lwc1        $f6, 0xA8($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0XA8);
    // 0x800485CC: mul.s       $f8, $f4, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = MUL_S(ctx->f4.fl, ctx->f6.fl);
    // 0x800485D0: sub.s       $f4, $f10, $f8
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f4.fl = ctx->f10.fl - ctx->f8.fl;
    // 0x800485D4: swc1        $f4, 0x38($a2)
    MEM_W(0X38, ctx->r6) = ctx->f4.u32l;
    // 0x800485D8: lwc1        $f6, 0xBC($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0XBC);
    // 0x800485DC: lwc1        $f8, 0xC0($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0XC0);
    // 0x800485E0: mul.s       $f10, $f6, $f24
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 24);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f24.fl); 
    ctx->f10.fl = MUL_S(ctx->f6.fl, ctx->f24.fl);
    // 0x800485E4: swc1        $f6, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->f6.u32l;
    // 0x800485E8: lwc1        $f0, 0x30($sp)
    ctx->f0.u32l = MEM_W(ctx->r29, 0X30);
    // 0x800485EC: mul.s       $f4, $f8, $f22
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f4.fl = MUL_S(ctx->f8.fl, ctx->f22.fl);
    // 0x800485F0: swc1        $f8, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->f8.u32l;
    // 0x800485F4: sub.s       $f10, $f10, $f4
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f10.fl = ctx->f10.fl - ctx->f4.fl;
    // 0x800485F8: mul.s       $f4, $f8, $f20
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f4.fl = MUL_S(ctx->f8.fl, ctx->f20.fl);
    // 0x800485FC: swc1        $f10, 0x84($sp)
    MEM_W(0X84, ctx->r29) = ctx->f10.u32l;
    // 0x80048600: lwc1        $f10, 0xB8($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0XB8);
    // 0x80048604: mul.s       $f6, $f10, $f24
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 24);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f24.fl); 
    ctx->f6.fl = MUL_S(ctx->f10.fl, ctx->f24.fl);
    // 0x80048608: sub.s       $f4, $f4, $f6
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f4.fl = ctx->f4.fl - ctx->f6.fl;
    // 0x8004860C: mul.s       $f6, $f10, $f22
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f6.fl = MUL_S(ctx->f10.fl, ctx->f22.fl);
    // 0x80048610: nop

    // 0x80048614: mul.s       $f8, $f0, $f20
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f8.fl = MUL_S(ctx->f0.fl, ctx->f20.fl);
    // 0x80048618: swc1        $f4, 0x80($sp)
    MEM_W(0X80, ctx->r29) = ctx->f4.u32l;
    // 0x8004861C: sub.s       $f6, $f6, $f8
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f6.fl = ctx->f6.fl - ctx->f8.fl;
    // 0x80048620: lwc1        $f8, 0x30($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X30);
    // 0x80048624: swc1        $f6, 0x7C($sp)
    MEM_W(0X7C, ctx->r29) = ctx->f6.u32l;
    // 0x80048628: mul.s       $f6, $f0, $f18
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f6.fl = MUL_S(ctx->f0.fl, ctx->f18.fl);
    // 0x8004862C: nop

    // 0x80048630: mul.s       $f4, $f8, $f16
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f4.fl = MUL_S(ctx->f8.fl, ctx->f16.fl);
    // 0x80048634: sub.s       $f24, $f6, $f4
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f24.fl = ctx->f6.fl - ctx->f4.fl;
    // 0x80048638: mul.s       $f8, $f8, $f14
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f8.fl = MUL_S(ctx->f8.fl, ctx->f14.fl);
    // 0x8004863C: nop

    // 0x80048640: mul.s       $f6, $f10, $f18
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f6.fl = MUL_S(ctx->f10.fl, ctx->f18.fl);
    // 0x80048644: sub.s       $f22, $f8, $f6
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f22.fl = ctx->f8.fl - ctx->f6.fl;
    // 0x80048648: mul.s       $f4, $f10, $f16
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f4.fl = MUL_S(ctx->f10.fl, ctx->f16.fl);
    // 0x8004864C: nop

    // 0x80048650: mul.s       $f8, $f0, $f14
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f8.fl = MUL_S(ctx->f0.fl, ctx->f14.fl);
    // 0x80048654: sub.s       $f20, $f4, $f8
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f20.fl = ctx->f4.fl - ctx->f8.fl;
    // 0x80048658: mul.s       $f6, $f24, $f24
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 24);
    NAN_CHECK(ctx->f24.fl); NAN_CHECK(ctx->f24.fl); 
    ctx->f6.fl = MUL_S(ctx->f24.fl, ctx->f24.fl);
    // 0x8004865C: nop

    // 0x80048660: mul.s       $f10, $f22, $f22
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f10.fl = MUL_S(ctx->f22.fl, ctx->f22.fl);
    // 0x80048664: add.s       $f4, $f6, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f4.fl = ctx->f6.fl + ctx->f10.fl;
    // 0x80048668: mul.s       $f8, $f20, $f20
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f8.fl = MUL_S(ctx->f20.fl, ctx->f20.fl);
    // 0x8004866C: mtc1        $zero, $f6
    ctx->f6.u32l = 0;
    // 0x80048670: add.s       $f12, $f4, $f8
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f12.fl = ctx->f4.fl + ctx->f8.fl;
    // 0x80048674: c.le.s      $f12, $f6
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 6);
    c1cs = ctx->f12.fl <= ctx->f6.fl;
    // 0x80048678: nop

    // 0x8004867C: bc1t        L_8004883C
    if (c1cs) {
        // 0x80048680: nop
    
            goto L_8004883C;
    }
    // 0x80048680: nop

    // 0x80048684: sw          $a2, 0x9C($sp)
    MEM_W(0X9C, ctx->r29) = ctx->r6;
    // 0x80048688: swc1        $f14, 0x60($sp)
    MEM_W(0X60, ctx->r29) = ctx->f14.u32l;
    // 0x8004868C: swc1        $f16, 0x5C($sp)
    MEM_W(0X5C, ctx->r29) = ctx->f16.u32l;
    // 0x80048690: jal         0x800C7010
    // 0x80048694: swc1        $f18, 0x58($sp)
    MEM_W(0X58, ctx->r29) = ctx->f18.u32l;
    _nsqrtf(rdram, ctx);
        goto after_1;
    // 0x80048694: swc1        $f18, 0x58($sp)
    MEM_W(0X58, ctx->r29) = ctx->f18.u32l;
    after_1:
    // 0x80048698: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x8004869C: mtc1        $at, $f10
    ctx->f10.u32l = ctx->r1;
    // 0x800486A0: lwc1        $f4, 0x80($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X80);
    // 0x800486A4: lw          $a2, 0x9C($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X9C);
    // 0x800486A8: div.s       $f2, $f10, $f0
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f2.fl = DIV_S(ctx->f10.fl, ctx->f0.fl);
    // 0x800486AC: lwc1        $f14, 0x60($sp)
    ctx->f14.u32l = MEM_W(ctx->r29, 0X60);
    // 0x800486B0: lwc1        $f16, 0x5C($sp)
    ctx->f16.u32l = MEM_W(ctx->r29, 0X5C);
    // 0x800486B4: lwc1        $f18, 0x58($sp)
    ctx->f18.u32l = MEM_W(ctx->r29, 0X58);
    // 0x800486B8: mul.s       $f12, $f4, $f2
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f12.fl = MUL_S(ctx->f4.fl, ctx->f2.fl);
    // 0x800486BC: swc1        $f12, 0x10($a2)
    MEM_W(0X10, ctx->r6) = ctx->f12.u32l;
    // 0x800486C0: lwc1        $f8, 0x84($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X84);
    // 0x800486C4: mul.s       $f6, $f8, $f2
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f6.fl = MUL_S(ctx->f8.fl, ctx->f2.fl);
    // 0x800486C8: swc1        $f6, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->f6.u32l;
    // 0x800486CC: swc1        $f6, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->f6.u32l;
    // 0x800486D0: lwc1        $f10, 0x7C($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0X7C);
    // 0x800486D4: mul.s       $f4, $f10, $f2
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f4.fl = MUL_S(ctx->f10.fl, ctx->f2.fl);
    // 0x800486D8: swc1        $f4, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->f4.u32l;
    // 0x800486DC: swc1        $f4, 0x20($a2)
    MEM_W(0X20, ctx->r6) = ctx->f4.u32l;
    // 0x800486E0: lwc1        $f6, 0x3C($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X3C);
    // 0x800486E4: lwc1        $f8, 0x54($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X54);
    // 0x800486E8: lwc1        $f4, 0xA4($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0XA4);
    // 0x800486EC: mul.s       $f10, $f8, $f6
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f10.fl = MUL_S(ctx->f8.fl, ctx->f6.fl);
    // 0x800486F0: nop

    // 0x800486F4: mul.s       $f8, $f4, $f12
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f8.fl = MUL_S(ctx->f4.fl, ctx->f12.fl);
    // 0x800486F8: lwc1        $f4, 0x44($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X44);
    // 0x800486FC: sub.s       $f6, $f10, $f8
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f6.fl = ctx->f10.fl - ctx->f8.fl;
    // 0x80048700: lwc1        $f10, 0xA8($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0XA8);
    // 0x80048704: mul.s       $f8, $f4, $f10
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f8.fl = MUL_S(ctx->f4.fl, ctx->f10.fl);
    // 0x80048708: sub.s       $f4, $f6, $f8
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f4.fl = ctx->f6.fl - ctx->f8.fl;
    // 0x8004870C: swc1        $f4, 0x30($a2)
    MEM_W(0X30, ctx->r6) = ctx->f4.u32l;
    // 0x80048710: lwc1        $f10, 0x7C($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0X7C);
    // 0x80048714: lwc1        $f8, 0x80($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X80);
    // 0x80048718: mul.s       $f6, $f16, $f10
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f6.fl = MUL_S(ctx->f16.fl, ctx->f10.fl);
    // 0x8004871C: nop

    // 0x80048720: mul.s       $f4, $f18, $f8
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f4.fl = MUL_S(ctx->f18.fl, ctx->f8.fl);
    // 0x80048724: sub.s       $f6, $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = ctx->f6.fl - ctx->f4.fl;
    // 0x80048728: lwc1        $f4, 0x84($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X84);
    // 0x8004872C: swc1        $f6, 0x78($sp)
    MEM_W(0X78, ctx->r29) = ctx->f6.u32l;
    // 0x80048730: mul.s       $f6, $f18, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = MUL_S(ctx->f18.fl, ctx->f4.fl);
    // 0x80048734: nop

    // 0x80048738: mul.s       $f10, $f14, $f10
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f10.fl = MUL_S(ctx->f14.fl, ctx->f10.fl);
    // 0x8004873C: sub.s       $f6, $f6, $f10
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f6.fl = ctx->f6.fl - ctx->f10.fl;
    // 0x80048740: mul.s       $f10, $f14, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = MUL_S(ctx->f14.fl, ctx->f8.fl);
    // 0x80048744: swc1        $f6, 0x74($sp)
    MEM_W(0X74, ctx->r29) = ctx->f6.u32l;
    // 0x80048748: mul.s       $f6, $f16, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = MUL_S(ctx->f16.fl, ctx->f4.fl);
    // 0x8004874C: sub.s       $f8, $f10, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = ctx->f10.fl - ctx->f6.fl;
    // 0x80048750: mul.s       $f4, $f16, $f20
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f4.fl = MUL_S(ctx->f16.fl, ctx->f20.fl);
    // 0x80048754: nop

    // 0x80048758: mul.s       $f10, $f18, $f22
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f10.fl = MUL_S(ctx->f18.fl, ctx->f22.fl);
    // 0x8004875C: swc1        $f8, 0x70($sp)
    MEM_W(0X70, ctx->r29) = ctx->f8.u32l;
    // 0x80048760: mul.s       $f6, $f18, $f24
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 24);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f24.fl); 
    ctx->f6.fl = MUL_S(ctx->f18.fl, ctx->f24.fl);
    // 0x80048764: nop

    // 0x80048768: mul.s       $f8, $f14, $f20
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f8.fl = MUL_S(ctx->f14.fl, ctx->f20.fl);
    // 0x8004876C: sub.s       $f0, $f4, $f10
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f0.fl = ctx->f4.fl - ctx->f10.fl;
    // 0x80048770: mul.s       $f4, $f14, $f22
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f4.fl = MUL_S(ctx->f14.fl, ctx->f22.fl);
    // 0x80048774: nop

    // 0x80048778: mul.s       $f10, $f16, $f24
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 24);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f24.fl); 
    ctx->f10.fl = MUL_S(ctx->f16.fl, ctx->f24.fl);
    // 0x8004877C: sub.s       $f2, $f6, $f8
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f2.fl = ctx->f6.fl - ctx->f8.fl;
    // 0x80048780: mul.s       $f6, $f0, $f0
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f6.fl = MUL_S(ctx->f0.fl, ctx->f0.fl);
    // 0x80048784: nop

    // 0x80048788: mul.s       $f8, $f2, $f2
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f8.fl = MUL_S(ctx->f2.fl, ctx->f2.fl);
    // 0x8004878C: sub.s       $f12, $f4, $f10
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f12.fl = ctx->f4.fl - ctx->f10.fl;
    // 0x80048790: mul.s       $f10, $f12, $f12
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f10.fl = MUL_S(ctx->f12.fl, ctx->f12.fl);
    // 0x80048794: add.s       $f4, $f6, $f8
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f4.fl = ctx->f6.fl + ctx->f8.fl;
    // 0x80048798: mtc1        $zero, $f8
    ctx->f8.u32l = 0;
    // 0x8004879C: add.s       $f6, $f4, $f10
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f6.fl = ctx->f4.fl + ctx->f10.fl;
    // 0x800487A0: c.le.s      $f6, $f8
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    c1cs = ctx->f6.fl <= ctx->f8.fl;
    // 0x800487A4: swc1        $f6, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->f6.u32l;
    // 0x800487A8: lwc1        $f12, 0x44($sp)
    ctx->f12.u32l = MEM_W(ctx->r29, 0X44);
    // 0x800487AC: bc1t        L_8004883C
    if (c1cs) {
        // 0x800487B0: nop
    
            goto L_8004883C;
    }
    // 0x800487B0: nop

    // 0x800487B4: jal         0x800C7010
    // 0x800487B8: sw          $a2, 0x9C($sp)
    MEM_W(0X9C, ctx->r29) = ctx->r6;
    _nsqrtf(rdram, ctx);
        goto after_2;
    // 0x800487B8: sw          $a2, 0x9C($sp)
    MEM_W(0X9C, ctx->r29) = ctx->r6;
    after_2:
    // 0x800487BC: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x800487C0: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x800487C4: lwc1        $f10, 0x74($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0X74);
    // 0x800487C8: lw          $a0, 0x9C($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X9C);
    // 0x800487CC: div.s       $f2, $f4, $f0
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f2.fl = DIV_S(ctx->f4.fl, ctx->f0.fl);
    // 0x800487D0: mtc1        $zero, $f18
    ctx->f18.u32l = 0;
    // 0x800487D4: mul.s       $f12, $f10, $f2
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f12.fl = MUL_S(ctx->f10.fl, ctx->f2.fl);
    // 0x800487D8: swc1        $f12, 0x14($a0)
    MEM_W(0X14, ctx->r4) = ctx->f12.u32l;
    // 0x800487DC: lwc1        $f8, 0x78($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X78);
    // 0x800487E0: mul.s       $f14, $f8, $f2
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f14.fl = MUL_S(ctx->f8.fl, ctx->f2.fl);
    // 0x800487E4: swc1        $f14, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->f14.u32l;
    // 0x800487E8: lwc1        $f6, 0x70($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X70);
    // 0x800487EC: mul.s       $f16, $f6, $f2
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f16.fl = MUL_S(ctx->f6.fl, ctx->f2.fl);
    // 0x800487F0: swc1        $f16, 0x24($a0)
    MEM_W(0X24, ctx->r4) = ctx->f16.u32l;
    // 0x800487F4: lwc1        $f4, 0x54($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X54);
    // 0x800487F8: lwc1        $f8, 0xA4($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0XA4);
    // 0x800487FC: mul.s       $f10, $f4, $f14
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f10.fl = MUL_S(ctx->f4.fl, ctx->f14.fl);
    // 0x80048800: nop

    // 0x80048804: mul.s       $f6, $f8, $f12
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f6.fl = MUL_S(ctx->f8.fl, ctx->f12.fl);
    // 0x80048808: lwc1        $f8, 0xA8($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0XA8);
    // 0x8004880C: swc1        $f18, 0xC($a0)
    MEM_W(0XC, ctx->r4) = ctx->f18.u32l;
    // 0x80048810: swc1        $f18, 0x1C($a0)
    MEM_W(0X1C, ctx->r4) = ctx->f18.u32l;
    // 0x80048814: swc1        $f18, 0x2C($a0)
    MEM_W(0X2C, ctx->r4) = ctx->f18.u32l;
    // 0x80048818: sub.s       $f4, $f10, $f6
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f4.fl = ctx->f10.fl - ctx->f6.fl;
    // 0x8004881C: mul.s       $f10, $f16, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = MUL_S(ctx->f16.fl, ctx->f8.fl);
    // 0x80048820: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x80048824: nop

    // 0x80048828: swc1        $f8, 0x3C($a0)
    MEM_W(0X3C, ctx->r4) = ctx->f8.u32l;
    // 0x8004882C: sub.s       $f6, $f4, $f10
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f6.fl = ctx->f4.fl - ctx->f10.fl;
    // 0x80048830: swc1        $f6, 0x34($a0)
    MEM_W(0X34, ctx->r4) = ctx->f6.u32l;
    // 0x80048834: jal         0x80047EE0
    // 0x80048838: lw          $a1, 0x98($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X98);
    SysUtils_MtxFToMtx(rdram, ctx);
        goto after_3;
    // 0x80048838: lw          $a1, 0x98($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X98);
    after_3:
L_8004883C:
    // 0x8004883C: lw          $ra, 0x2C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X2C);
L_80048840:
    // 0x80048840: ldc1        $f20, 0x10($sp)
    CHECK_FR(ctx, 20);
    ctx->f20.u64 = LD(ctx->r29, 0X10);
    // 0x80048844: ldc1        $f22, 0x18($sp)
    CHECK_FR(ctx, 22);
    ctx->f22.u64 = LD(ctx->r29, 0X18);
    // 0x80048848: ldc1        $f24, 0x20($sp)
    CHECK_FR(ctx, 24);
    ctx->f24.u64 = LD(ctx->r29, 0X20);
    // 0x8004884C: jr          $ra
    // 0x80048850: addiu       $sp, $sp, 0x98
    ctx->r29 = ADD32(ctx->r29, 0X98);
    return;
    // 0x80048850: addiu       $sp, $sp, 0x98
    ctx->r29 = ADD32(ctx->r29, 0X98);
;}
RECOMP_FUNC void SysUtils_MatrixLookAt(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x80048854: addiu       $sp, $sp, -0x58
    ctx->r29 = ADD32(ctx->r29, -0X58);
    // 0x80048858: sdc1        $f20, 0x10($sp)
    CHECK_FR(ctx, 20);
    SD(ctx->f20.u64, 0X10, ctx->r29);
    // 0x8004885C: mtc1        $a2, $f20
    ctx->f20.u32l = ctx->r6;
    // 0x80048860: sdc1        $f22, 0x18($sp)
    CHECK_FR(ctx, 22);
    SD(ctx->f22.u64, 0X18, ctx->r29);
    // 0x80048864: mtc1        $a3, $f22
    ctx->f22.u32l = ctx->r7;
    // 0x80048868: mul.s       $f4, $f20, $f20
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f4.fl = MUL_S(ctx->f20.fl, ctx->f20.fl);
    // 0x8004886C: sdc1        $f24, 0x20($sp)
    CHECK_FR(ctx, 24);
    SD(ctx->f24.u64, 0X20, ctx->r29);
    // 0x80048870: lwc1        $f24, 0x68($sp)
    ctx->f24.u32l = MEM_W(ctx->r29, 0X68);
    // 0x80048874: mul.s       $f6, $f22, $f22
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f6.fl = MUL_S(ctx->f22.fl, ctx->f22.fl);
    // 0x80048878: sdc1        $f26, 0x28($sp)
    CHECK_FR(ctx, 26);
    SD(ctx->f26.u64, 0X28, ctx->r29);
    // 0x8004887C: mtc1        $zero, $f26
    ctx->f26.u32l = 0;
    // 0x80048880: mul.s       $f10, $f24, $f24
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 24);
    NAN_CHECK(ctx->f24.fl); NAN_CHECK(ctx->f24.fl); 
    ctx->f10.fl = MUL_S(ctx->f24.fl, ctx->f24.fl);
    // 0x80048884: sw          $ra, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r31;
    // 0x80048888: sw          $a0, 0x58($sp)
    MEM_W(0X58, ctx->r29) = ctx->r4;
    // 0x8004888C: sw          $a1, 0x5C($sp)
    MEM_W(0X5C, ctx->r29) = ctx->r5;
    // 0x80048890: add.s       $f8, $f4, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = ctx->f4.fl + ctx->f6.fl;
    // 0x80048894: add.s       $f12, $f8, $f10
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f12.fl = ctx->f8.fl + ctx->f10.fl;
    // 0x80048898: c.eq.s      $f26, $f12
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 12);
    c1cs = ctx->f26.fl == ctx->f12.fl;
    // 0x8004889C: nop

    // 0x800488A0: bc1tl       L_80048A70
    if (c1cs) {
        // 0x800488A4: lw          $ra, 0x34($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X34);
            goto L_80048A70;
    }
    goto skip_0;
    // 0x800488A4: lw          $ra, 0x34($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X34);
    skip_0:
    // 0x800488A8: jal         0x800C7010
    // 0x800488AC: sw          $a1, 0x5C($sp)
    MEM_W(0X5C, ctx->r29) = ctx->r5;
    _nsqrtf(rdram, ctx);
        goto after_0;
    // 0x800488AC: sw          $a1, 0x5C($sp)
    MEM_W(0X5C, ctx->r29) = ctx->r5;
    after_0:
    // 0x800488B0: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x800488B4: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x800488B8: lw          $a2, 0x5C($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X5C);
    // 0x800488BC: div.s       $f2, $f4, $f0
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f2.fl = DIV_S(ctx->f4.fl, ctx->f0.fl);
    // 0x800488C0: mul.s       $f6, $f2, $f20
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f6.fl = MUL_S(ctx->f2.fl, ctx->f20.fl);
    // 0x800488C4: nop

    // 0x800488C8: mul.s       $f8, $f2, $f22
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f8.fl = MUL_S(ctx->f2.fl, ctx->f22.fl);
    // 0x800488CC: nop

    // 0x800488D0: mul.s       $f10, $f2, $f24
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 24);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f24.fl); 
    ctx->f10.fl = MUL_S(ctx->f2.fl, ctx->f24.fl);
    // 0x800488D4: swc1        $f6, 0x20($a2)
    MEM_W(0X20, ctx->r6) = ctx->f6.u32l;
    // 0x800488D8: swc1        $f8, 0x24($a2)
    MEM_W(0X24, ctx->r6) = ctx->f8.u32l;
    // 0x800488DC: swc1        $f10, 0x28($a2)
    MEM_W(0X28, ctx->r6) = ctx->f10.u32l;
    // 0x800488E0: lwc1        $f4, 0x70($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X70);
    // 0x800488E4: lwc1        $f8, 0x74($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X74);
    // 0x800488E8: mul.s       $f6, $f4, $f24
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 24);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f24.fl); 
    ctx->f6.fl = MUL_S(ctx->f4.fl, ctx->f24.fl);
    // 0x800488EC: nop

    // 0x800488F0: mul.s       $f10, $f8, $f22
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f10.fl = MUL_S(ctx->f8.fl, ctx->f22.fl);
    // 0x800488F4: sub.s       $f12, $f6, $f10
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f12.fl = ctx->f6.fl - ctx->f10.fl;
    // 0x800488F8: mul.s       $f6, $f8, $f20
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f6.fl = MUL_S(ctx->f8.fl, ctx->f20.fl);
    // 0x800488FC: lwc1        $f10, 0x6C($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0X6C);
    // 0x80048900: swc1        $f12, 0x50($sp)
    MEM_W(0X50, ctx->r29) = ctx->f12.u32l;
    // 0x80048904: mul.s       $f8, $f10, $f24
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 24);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f24.fl); 
    ctx->f8.fl = MUL_S(ctx->f10.fl, ctx->f24.fl);
    // 0x80048908: sub.s       $f14, $f6, $f8
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f14.fl = ctx->f6.fl - ctx->f8.fl;
    // 0x8004890C: mul.s       $f6, $f10, $f22
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f6.fl = MUL_S(ctx->f10.fl, ctx->f22.fl);
    // 0x80048910: nop

    // 0x80048914: mul.s       $f8, $f4, $f20
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f8.fl = MUL_S(ctx->f4.fl, ctx->f20.fl);
    // 0x80048918: swc1        $f14, 0x4C($sp)
    MEM_W(0X4C, ctx->r29) = ctx->f14.u32l;
    // 0x8004891C: mul.s       $f10, $f12, $f12
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f10.fl = MUL_S(ctx->f12.fl, ctx->f12.fl);
    // 0x80048920: nop

    // 0x80048924: mul.s       $f4, $f14, $f14
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f4.fl = MUL_S(ctx->f14.fl, ctx->f14.fl);
    // 0x80048928: sub.s       $f16, $f6, $f8
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f16.fl = ctx->f6.fl - ctx->f8.fl;
    // 0x8004892C: mul.s       $f8, $f16, $f16
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f8.fl = MUL_S(ctx->f16.fl, ctx->f16.fl);
    // 0x80048930: add.s       $f6, $f10, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = ctx->f10.fl + ctx->f4.fl;
    // 0x80048934: swc1        $f16, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->f16.u32l;
    // 0x80048938: add.s       $f18, $f6, $f8
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f18.fl = ctx->f6.fl + ctx->f8.fl;
    // 0x8004893C: c.eq.s      $f26, $f18
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 18);
    c1cs = ctx->f26.fl == ctx->f18.fl;
    // 0x80048940: swc1        $f18, 0x54($sp)
    MEM_W(0X54, ctx->r29) = ctx->f18.u32l;
    // 0x80048944: lwc1        $f12, 0x54($sp)
    ctx->f12.u32l = MEM_W(ctx->r29, 0X54);
    // 0x80048948: bc1t        L_80048A6C
    if (c1cs) {
        // 0x8004894C: nop
    
            goto L_80048A6C;
    }
    // 0x8004894C: nop

    // 0x80048950: jal         0x800C7010
    // 0x80048954: sw          $a2, 0x5C($sp)
    MEM_W(0X5C, ctx->r29) = ctx->r6;
    _nsqrtf(rdram, ctx);
        goto after_1;
    // 0x80048954: sw          $a2, 0x5C($sp)
    MEM_W(0X5C, ctx->r29) = ctx->r6;
    after_1:
    // 0x80048958: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x8004895C: mtc1        $at, $f10
    ctx->f10.u32l = ctx->r1;
    // 0x80048960: lwc1        $f4, 0x50($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X50);
    // 0x80048964: lw          $a2, 0x5C($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X5C);
    // 0x80048968: div.s       $f2, $f10, $f0
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f2.fl = DIV_S(ctx->f10.fl, ctx->f0.fl);
    // 0x8004896C: mul.s       $f6, $f2, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = MUL_S(ctx->f2.fl, ctx->f4.fl);
    // 0x80048970: swc1        $f6, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->f6.u32l;
    // 0x80048974: lwc1        $f8, 0x4C($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X4C);
    // 0x80048978: mul.s       $f10, $f2, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = MUL_S(ctx->f2.fl, ctx->f8.fl);
    // 0x8004897C: swc1        $f10, 0x4($a2)
    MEM_W(0X4, ctx->r6) = ctx->f10.u32l;
    // 0x80048980: lwc1        $f4, 0x48($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X48);
    // 0x80048984: mul.s       $f6, $f2, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = MUL_S(ctx->f2.fl, ctx->f4.fl);
    // 0x80048988: swc1        $f6, 0x8($a2)
    MEM_W(0X8, ctx->r6) = ctx->f6.u32l;
    // 0x8004898C: lwc1        $f8, 0x48($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X48);
    // 0x80048990: lwc1        $f4, 0x4C($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X4C);
    // 0x80048994: mul.s       $f10, $f22, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = MUL_S(ctx->f22.fl, ctx->f8.fl);
    // 0x80048998: nop

    // 0x8004899C: mul.s       $f6, $f24, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f24.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = MUL_S(ctx->f24.fl, ctx->f4.fl);
    // 0x800489A0: sub.s       $f12, $f10, $f6
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f12.fl = ctx->f10.fl - ctx->f6.fl;
    // 0x800489A4: lwc1        $f10, 0x50($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0X50);
    // 0x800489A8: mul.s       $f6, $f24, $f10
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f24.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f6.fl = MUL_S(ctx->f24.fl, ctx->f10.fl);
    // 0x800489AC: swc1        $f12, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->f12.u32l;
    // 0x800489B0: mul.s       $f8, $f20, $f8
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f8.fl = MUL_S(ctx->f20.fl, ctx->f8.fl);
    // 0x800489B4: sub.s       $f14, $f6, $f8
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f14.fl = ctx->f6.fl - ctx->f8.fl;
    // 0x800489B8: mul.s       $f6, $f20, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = MUL_S(ctx->f20.fl, ctx->f4.fl);
    // 0x800489BC: nop

    // 0x800489C0: mul.s       $f8, $f22, $f10
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f8.fl = MUL_S(ctx->f22.fl, ctx->f10.fl);
    // 0x800489C4: swc1        $f14, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->f14.u32l;
    // 0x800489C8: mul.s       $f4, $f12, $f12
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f4.fl = MUL_S(ctx->f12.fl, ctx->f12.fl);
    // 0x800489CC: nop

    // 0x800489D0: mul.s       $f10, $f14, $f14
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f10.fl = MUL_S(ctx->f14.fl, ctx->f14.fl);
    // 0x800489D4: sub.s       $f16, $f6, $f8
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f16.fl = ctx->f6.fl - ctx->f8.fl;
    // 0x800489D8: mul.s       $f8, $f16, $f16
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f8.fl = MUL_S(ctx->f16.fl, ctx->f16.fl);
    // 0x800489DC: add.s       $f6, $f4, $f10
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f6.fl = ctx->f4.fl + ctx->f10.fl;
    // 0x800489E0: swc1        $f16, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->f16.u32l;
    // 0x800489E4: add.s       $f18, $f6, $f8
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f18.fl = ctx->f6.fl + ctx->f8.fl;
    // 0x800489E8: c.eq.s      $f26, $f18
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 18);
    c1cs = ctx->f26.fl == ctx->f18.fl;
    // 0x800489EC: swc1        $f18, 0x54($sp)
    MEM_W(0X54, ctx->r29) = ctx->f18.u32l;
    // 0x800489F0: lwc1        $f12, 0x54($sp)
    ctx->f12.u32l = MEM_W(ctx->r29, 0X54);
    // 0x800489F4: bc1t        L_80048A6C
    if (c1cs) {
        // 0x800489F8: nop
    
            goto L_80048A6C;
    }
    // 0x800489F8: nop

    // 0x800489FC: jal         0x800C7010
    // 0x80048A00: sw          $a2, 0x5C($sp)
    MEM_W(0X5C, ctx->r29) = ctx->r6;
    _nsqrtf(rdram, ctx);
        goto after_2;
    // 0x80048A00: sw          $a2, 0x5C($sp)
    MEM_W(0X5C, ctx->r29) = ctx->r6;
    after_2:
    // 0x80048A04: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x80048A08: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x80048A0C: lwc1        $f10, 0x44($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0X44);
    // 0x80048A10: lw          $a0, 0x5C($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X5C);
    // 0x80048A14: div.s       $f2, $f4, $f0
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f2.fl = DIV_S(ctx->f4.fl, ctx->f0.fl);
    // 0x80048A18: mul.s       $f6, $f2, $f10
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f6.fl = MUL_S(ctx->f2.fl, ctx->f10.fl);
    // 0x80048A1C: swc1        $f6, 0x10($a0)
    MEM_W(0X10, ctx->r4) = ctx->f6.u32l;
    // 0x80048A20: lwc1        $f8, 0x40($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X40);
    // 0x80048A24: mul.s       $f4, $f2, $f8
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f4.fl = MUL_S(ctx->f2.fl, ctx->f8.fl);
    // 0x80048A28: swc1        $f4, 0x14($a0)
    MEM_W(0X14, ctx->r4) = ctx->f4.u32l;
    // 0x80048A2C: lwc1        $f10, 0x3C($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0X3C);
    // 0x80048A30: mul.s       $f6, $f2, $f10
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f6.fl = MUL_S(ctx->f2.fl, ctx->f10.fl);
    // 0x80048A34: swc1        $f6, 0x18($a0)
    MEM_W(0X18, ctx->r4) = ctx->f6.u32l;
    // 0x80048A38: lwc1        $f8, 0x78($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X78);
    // 0x80048A3C: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x80048A40: swc1        $f8, 0x30($a0)
    MEM_W(0X30, ctx->r4) = ctx->f8.u32l;
    // 0x80048A44: lwc1        $f4, 0x7C($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X7C);
    // 0x80048A48: swc1        $f4, 0x34($a0)
    MEM_W(0X34, ctx->r4) = ctx->f4.u32l;
    // 0x80048A4C: lwc1        $f10, 0x80($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0X80);
    // 0x80048A50: swc1        $f26, 0xC($a0)
    MEM_W(0XC, ctx->r4) = ctx->f26.u32l;
    // 0x80048A54: swc1        $f26, 0x1C($a0)
    MEM_W(0X1C, ctx->r4) = ctx->f26.u32l;
    // 0x80048A58: swc1        $f26, 0x2C($a0)
    MEM_W(0X2C, ctx->r4) = ctx->f26.u32l;
    // 0x80048A5C: swc1        $f6, 0x3C($a0)
    MEM_W(0X3C, ctx->r4) = ctx->f6.u32l;
    // 0x80048A60: swc1        $f10, 0x38($a0)
    MEM_W(0X38, ctx->r4) = ctx->f10.u32l;
    // 0x80048A64: jal         0x80047EE0
    // 0x80048A68: lw          $a1, 0x58($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X58);
    SysUtils_MtxFToMtx(rdram, ctx);
        goto after_3;
    // 0x80048A68: lw          $a1, 0x58($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X58);
    after_3:
L_80048A6C:
    // 0x80048A6C: lw          $ra, 0x34($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X34);
L_80048A70:
    // 0x80048A70: ldc1        $f20, 0x10($sp)
    CHECK_FR(ctx, 20);
    ctx->f20.u64 = LD(ctx->r29, 0X10);
    // 0x80048A74: ldc1        $f22, 0x18($sp)
    CHECK_FR(ctx, 22);
    ctx->f22.u64 = LD(ctx->r29, 0X18);
    // 0x80048A78: ldc1        $f24, 0x20($sp)
    CHECK_FR(ctx, 24);
    ctx->f24.u64 = LD(ctx->r29, 0X20);
    // 0x80048A7C: ldc1        $f26, 0x28($sp)
    CHECK_FR(ctx, 26);
    ctx->f26.u64 = LD(ctx->r29, 0X28);
    // 0x80048A80: jr          $ra
    // 0x80048A84: addiu       $sp, $sp, 0x58
    ctx->r29 = ADD32(ctx->r29, 0X58);
    return;
    // 0x80048A84: addiu       $sp, $sp, 0x58
    ctx->r29 = ADD32(ctx->r29, 0X58);
;}
RECOMP_FUNC void func_80048A88(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x80048A88: mtc1        $a1, $f14
    ctx->f14.u32l = ctx->r5;
    // 0x80048A8C: addiu       $sp, $sp, -0x70
    ctx->r29 = ADD32(ctx->r29, -0X70);
    // 0x80048A90: sdc1        $f20, 0x10($sp)
    CHECK_FR(ctx, 20);
    SD(ctx->f20.u64, 0X10, ctx->r29);
    // 0x80048A94: mul.s       $f4, $f14, $f14
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f4.fl = MUL_S(ctx->f14.fl, ctx->f14.fl);
    // 0x80048A98: mtc1        $a2, $f20
    ctx->f20.u32l = ctx->r6;
    // 0x80048A9C: sdc1        $f22, 0x18($sp)
    CHECK_FR(ctx, 22);
    SD(ctx->f22.u64, 0X18, ctx->r29);
    // 0x80048AA0: mtc1        $a3, $f22
    ctx->f22.u32l = ctx->r7;
    // 0x80048AA4: mul.s       $f6, $f20, $f20
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f6.fl = MUL_S(ctx->f20.fl, ctx->f20.fl);
    // 0x80048AA8: sw          $ra, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r31;
    // 0x80048AAC: sdc1        $f24, 0x20($sp)
    CHECK_FR(ctx, 24);
    SD(ctx->f24.u64, 0X20, ctx->r29);
    // 0x80048AB0: mul.s       $f10, $f22, $f22
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f10.fl = MUL_S(ctx->f22.fl, ctx->f22.fl);
    // 0x80048AB4: add.s       $f8, $f4, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = ctx->f4.fl + ctx->f6.fl;
    // 0x80048AB8: mtc1        $zero, $f4
    ctx->f4.u32l = 0;
    // 0x80048ABC: add.s       $f12, $f8, $f10
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f12.fl = ctx->f8.fl + ctx->f10.fl;
    // 0x80048AC0: c.eq.s      $f4, $f12
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 12);
    c1cs = ctx->f4.fl == ctx->f12.fl;
    // 0x80048AC4: nop

    // 0x80048AC8: bc1tl       L_80048DF8
    if (c1cs) {
        // 0x80048ACC: lw          $ra, 0x2C($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X2C);
            goto L_80048DF8;
    }
    goto skip_0;
    // 0x80048ACC: lw          $ra, 0x2C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X2C);
    skip_0:
    // 0x80048AD0: sw          $a0, 0x70($sp)
    MEM_W(0X70, ctx->r29) = ctx->r4;
    // 0x80048AD4: jal         0x800C7010
    // 0x80048AD8: swc1        $f14, 0x74($sp)
    MEM_W(0X74, ctx->r29) = ctx->f14.u32l;
    _nsqrtf(rdram, ctx);
        goto after_0;
    // 0x80048AD8: swc1        $f14, 0x74($sp)
    MEM_W(0X74, ctx->r29) = ctx->f14.u32l;
    after_0:
    // 0x80048ADC: lui         $at, 0x4780
    ctx->r1 = S32(0X4780 << 16);
    // 0x80048AE0: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x80048AE4: lwc1        $f6, 0x98($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X98);
    // 0x80048AE8: lwc1        $f14, 0x74($sp)
    ctx->f14.u32l = MEM_W(ctx->r29, 0X74);
    // 0x80048AEC: lw          $a0, 0x70($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X70);
    // 0x80048AF0: mul.s       $f12, $f6, $f8
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f12.fl = MUL_S(ctx->f6.fl, ctx->f8.fl);
    // 0x80048AF4: lui         $t1, 0xFFFF
    ctx->r9 = S32(0XFFFF << 16);
    // 0x80048AF8: div.s       $f2, $f12, $f0
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f2.fl = DIV_S(ctx->f12.fl, ctx->f0.fl);
    // 0x80048AFC: mul.s       $f10, $f14, $f2
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f10.fl = MUL_S(ctx->f14.fl, ctx->f2.fl);
    // 0x80048B00: trunc.w.s   $f4, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    ctx->f4.u32l = TRUNC_W_S(ctx->f10.fl);
    // 0x80048B04: mul.s       $f6, $f20, $f2
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f6.fl = MUL_S(ctx->f20.fl, ctx->f2.fl);
    // 0x80048B08: nop

    // 0x80048B0C: mul.s       $f10, $f22, $f2
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f10.fl = MUL_S(ctx->f22.fl, ctx->f2.fl);
    // 0x80048B10: mfc1        $v0, $f4
    ctx->r2 = (int32_t)ctx->f4.u32l;
    // 0x80048B14: nop

    // 0x80048B18: and         $t8, $v0, $t1
    ctx->r24 = ctx->r2 & ctx->r9;
    // 0x80048B1C: sll         $t5, $v0, 16
    ctx->r13 = S32(ctx->r2 << 16);
    // 0x80048B20: trunc.w.s   $f8, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    ctx->f8.u32l = TRUNC_W_S(ctx->f6.fl);
    // 0x80048B24: trunc.w.s   $f4, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    ctx->f4.u32l = TRUNC_W_S(ctx->f10.fl);
    // 0x80048B28: mfc1        $v1, $f8
    ctx->r3 = (int32_t)ctx->f8.u32l;
    // 0x80048B2C: mfc1        $a1, $f4
    ctx->r5 = (int32_t)ctx->f4.u32l;
    // 0x80048B30: srl         $t9, $v1, 16
    ctx->r25 = S32(U32(ctx->r3) >> 16);
    // 0x80048B34: or          $t2, $t8, $t9
    ctx->r10 = ctx->r24 | ctx->r25;
    // 0x80048B38: andi        $t6, $v1, 0xFFFF
    ctx->r14 = ctx->r3 & 0XFFFF;
    // 0x80048B3C: or          $t7, $t5, $t6
    ctx->r15 = ctx->r13 | ctx->r14;
    // 0x80048B40: and         $t4, $a1, $t1
    ctx->r12 = ctx->r5 & ctx->r9;
    // 0x80048B44: sll         $t8, $a1, 16
    ctx->r24 = S32(ctx->r5 << 16);
    // 0x80048B48: sw          $t2, 0x10($a0)
    MEM_W(0X10, ctx->r4) = ctx->r10;
    // 0x80048B4C: sw          $t4, 0x14($a0)
    MEM_W(0X14, ctx->r4) = ctx->r12;
    // 0x80048B50: sw          $t7, 0x30($a0)
    MEM_W(0X30, ctx->r4) = ctx->r15;
    // 0x80048B54: sw          $t8, 0x34($a0)
    MEM_W(0X34, ctx->r4) = ctx->r24;
    // 0x80048B58: lwc1        $f6, 0x84($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X84);
    // 0x80048B5C: lwc1        $f10, 0x88($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0X88);
    // 0x80048B60: swc1        $f12, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->f12.u32l;
    // 0x80048B64: mul.s       $f8, $f6, $f22
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f8.fl = MUL_S(ctx->f6.fl, ctx->f22.fl);
    // 0x80048B68: nop

    // 0x80048B6C: mul.s       $f4, $f10, $f20
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f4.fl = MUL_S(ctx->f10.fl, ctx->f20.fl);
    // 0x80048B70: sub.s       $f16, $f8, $f4
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f16.fl = ctx->f8.fl - ctx->f4.fl;
    // 0x80048B74: mul.s       $f8, $f10, $f14
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f8.fl = MUL_S(ctx->f10.fl, ctx->f14.fl);
    // 0x80048B78: lwc1        $f4, 0x80($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X80);
    // 0x80048B7C: swc1        $f16, 0x68($sp)
    MEM_W(0X68, ctx->r29) = ctx->f16.u32l;
    // 0x80048B80: mul.s       $f10, $f4, $f22
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f10.fl = MUL_S(ctx->f4.fl, ctx->f22.fl);
    // 0x80048B84: sub.s       $f18, $f8, $f10
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f18.fl = ctx->f8.fl - ctx->f10.fl;
    // 0x80048B88: mul.s       $f8, $f4, $f20
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f8.fl = MUL_S(ctx->f4.fl, ctx->f20.fl);
    // 0x80048B8C: nop

    // 0x80048B90: mul.s       $f10, $f6, $f14
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f10.fl = MUL_S(ctx->f6.fl, ctx->f14.fl);
    // 0x80048B94: swc1        $f18, 0x64($sp)
    MEM_W(0X64, ctx->r29) = ctx->f18.u32l;
    // 0x80048B98: mul.s       $f4, $f16, $f16
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f4.fl = MUL_S(ctx->f16.fl, ctx->f16.fl);
    // 0x80048B9C: nop

    // 0x80048BA0: mul.s       $f6, $f18, $f18
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f6.fl = MUL_S(ctx->f18.fl, ctx->f18.fl);
    // 0x80048BA4: sub.s       $f24, $f8, $f10
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f24.fl = ctx->f8.fl - ctx->f10.fl;
    // 0x80048BA8: mul.s       $f10, $f24, $f24
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 24);
    NAN_CHECK(ctx->f24.fl); NAN_CHECK(ctx->f24.fl); 
    ctx->f10.fl = MUL_S(ctx->f24.fl, ctx->f24.fl);
    // 0x80048BAC: add.s       $f8, $f4, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = ctx->f4.fl + ctx->f6.fl;
    // 0x80048BB0: mtc1        $zero, $f4
    ctx->f4.u32l = 0;
    // 0x80048BB4: swc1        $f24, 0x60($sp)
    MEM_W(0X60, ctx->r29) = ctx->f24.u32l;
    // 0x80048BB8: add.s       $f12, $f8, $f10
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f12.fl = ctx->f8.fl + ctx->f10.fl;
    // 0x80048BBC: c.eq.s      $f4, $f12
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 12);
    c1cs = ctx->f4.fl == ctx->f12.fl;
    // 0x80048BC0: nop

    // 0x80048BC4: bc1t        L_80048DF4
    if (c1cs) {
        // 0x80048BC8: nop
    
            goto L_80048DF4;
    }
    // 0x80048BC8: nop

    // 0x80048BCC: sw          $a0, 0x70($sp)
    MEM_W(0X70, ctx->r29) = ctx->r4;
    // 0x80048BD0: swc1        $f14, 0x74($sp)
    MEM_W(0X74, ctx->r29) = ctx->f14.u32l;
    // 0x80048BD4: swc1        $f16, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->f16.u32l;
    // 0x80048BD8: jal         0x800C7010
    // 0x80048BDC: swc1        $f18, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->f18.u32l;
    _nsqrtf(rdram, ctx);
        goto after_1;
    // 0x80048BDC: swc1        $f18, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->f18.u32l;
    after_1:
    // 0x80048BE0: lwc1        $f6, 0x44($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X44);
    // 0x80048BE4: lwc1        $f12, 0x68($sp)
    ctx->f12.u32l = MEM_W(ctx->r29, 0X68);
    // 0x80048BE8: lwc1        $f4, 0x64($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X64);
    // 0x80048BEC: div.s       $f2, $f6, $f0
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f2.fl = DIV_S(ctx->f6.fl, ctx->f0.fl);
    // 0x80048BF0: lw          $a0, 0x70($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X70);
    // 0x80048BF4: lui         $t1, 0xFFFF
    ctx->r9 = S32(0XFFFF << 16);
    // 0x80048BF8: lwc1        $f14, 0x74($sp)
    ctx->f14.u32l = MEM_W(ctx->r29, 0X74);
    // 0x80048BFC: lwc1        $f16, 0x40($sp)
    ctx->f16.u32l = MEM_W(ctx->r29, 0X40);
    // 0x80048C00: lwc1        $f18, 0x3C($sp)
    ctx->f18.u32l = MEM_W(ctx->r29, 0X3C);
    // 0x80048C04: mul.s       $f8, $f12, $f2
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f8.fl = MUL_S(ctx->f12.fl, ctx->f2.fl);
    // 0x80048C08: nop

    // 0x80048C0C: mul.s       $f6, $f4, $f2
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f6.fl = MUL_S(ctx->f4.fl, ctx->f2.fl);
    // 0x80048C10: trunc.w.s   $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.u32l = TRUNC_W_S(ctx->f8.fl);
    // 0x80048C14: trunc.w.s   $f8, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    ctx->f8.u32l = TRUNC_W_S(ctx->f6.fl);
    // 0x80048C18: mfc1        $v0, $f10
    ctx->r2 = (int32_t)ctx->f10.u32l;
    // 0x80048C1C: mfc1        $v1, $f8
    ctx->r3 = (int32_t)ctx->f8.u32l;
    // 0x80048C20: and         $t3, $v0, $t1
    ctx->r11 = ctx->r2 & ctx->r9;
    // 0x80048C24: sll         $t8, $v0, 16
    ctx->r24 = S32(ctx->r2 << 16);
    // 0x80048C28: srl         $t4, $v1, 16
    ctx->r12 = S32(U32(ctx->r3) >> 16);
    // 0x80048C2C: or          $t5, $t3, $t4
    ctx->r13 = ctx->r11 | ctx->r12;
    // 0x80048C30: sw          $t5, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r13;
    // 0x80048C34: lwc1        $f10, 0x60($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0X60);
    // 0x80048C38: andi        $t9, $v1, 0xFFFF
    ctx->r25 = ctx->r3 & 0XFFFF;
    // 0x80048C3C: or          $t2, $t8, $t9
    ctx->r10 = ctx->r24 | ctx->r25;
    // 0x80048C40: mul.s       $f4, $f10, $f2
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f4.fl = MUL_S(ctx->f10.fl, ctx->f2.fl);
    // 0x80048C44: sw          $t2, 0x20($a0)
    MEM_W(0X20, ctx->r4) = ctx->r10;
    // 0x80048C48: trunc.w.s   $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.u32l = TRUNC_W_S(ctx->f4.fl);
    // 0x80048C4C: mfc1        $a1, $f6
    ctx->r5 = (int32_t)ctx->f6.u32l;
    // 0x80048C50: nop

    // 0x80048C54: and         $t7, $a1, $t1
    ctx->r15 = ctx->r5 & ctx->r9;
    // 0x80048C58: sll         $t3, $a1, 16
    ctx->r11 = S32(ctx->r5 << 16);
    // 0x80048C5C: sw          $t7, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r15;
    // 0x80048C60: sw          $t3, 0x24($a0)
    MEM_W(0X24, ctx->r4) = ctx->r11;
    // 0x80048C64: lwc1        $f8, 0x60($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X60);
    // 0x80048C68: lwc1        $f4, 0x64($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X64);
    // 0x80048C6C: mul.s       $f10, $f20, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = MUL_S(ctx->f20.fl, ctx->f8.fl);
    // 0x80048C70: nop

    // 0x80048C74: mul.s       $f6, $f22, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = MUL_S(ctx->f22.fl, ctx->f4.fl);
    // 0x80048C78: sub.s       $f10, $f10, $f6
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f10.fl = ctx->f10.fl - ctx->f6.fl;
    // 0x80048C7C: mul.s       $f6, $f22, $f12
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f6.fl = MUL_S(ctx->f22.fl, ctx->f12.fl);
    // 0x80048C80: swc1        $f10, 0x5C($sp)
    MEM_W(0X5C, ctx->r29) = ctx->f10.u32l;
    // 0x80048C84: mul.s       $f10, $f14, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = MUL_S(ctx->f14.fl, ctx->f8.fl);
    // 0x80048C88: sub.s       $f8, $f6, $f10
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f8.fl = ctx->f6.fl - ctx->f10.fl;
    // 0x80048C8C: mul.s       $f6, $f14, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = MUL_S(ctx->f14.fl, ctx->f4.fl);
    // 0x80048C90: nop

    // 0x80048C94: mul.s       $f10, $f20, $f12
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f10.fl = MUL_S(ctx->f20.fl, ctx->f12.fl);
    // 0x80048C98: swc1        $f8, 0x58($sp)
    MEM_W(0X58, ctx->r29) = ctx->f8.u32l;
    // 0x80048C9C: mul.s       $f4, $f20, $f24
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 24);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f24.fl); 
    ctx->f4.fl = MUL_S(ctx->f20.fl, ctx->f24.fl);
    // 0x80048CA0: sub.s       $f8, $f6, $f10
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f8.fl = ctx->f6.fl - ctx->f10.fl;
    // 0x80048CA4: mul.s       $f6, $f22, $f18
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f6.fl = MUL_S(ctx->f22.fl, ctx->f18.fl);
    // 0x80048CA8: nop

    // 0x80048CAC: mul.s       $f10, $f22, $f16
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f10.fl = MUL_S(ctx->f22.fl, ctx->f16.fl);
    // 0x80048CB0: swc1        $f8, 0x54($sp)
    MEM_W(0X54, ctx->r29) = ctx->f8.u32l;
    // 0x80048CB4: mul.s       $f8, $f14, $f24
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 24);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f24.fl); 
    ctx->f8.fl = MUL_S(ctx->f14.fl, ctx->f24.fl);
    // 0x80048CB8: sub.s       $f0, $f4, $f6
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f0.fl = ctx->f4.fl - ctx->f6.fl;
    // 0x80048CBC: mul.s       $f4, $f14, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f4.fl = MUL_S(ctx->f14.fl, ctx->f18.fl);
    // 0x80048CC0: nop

    // 0x80048CC4: mul.s       $f6, $f20, $f16
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f6.fl = MUL_S(ctx->f20.fl, ctx->f16.fl);
    // 0x80048CC8: sub.s       $f2, $f10, $f8
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f2.fl = ctx->f10.fl - ctx->f8.fl;
    // 0x80048CCC: mul.s       $f10, $f0, $f0
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f10.fl = MUL_S(ctx->f0.fl, ctx->f0.fl);
    // 0x80048CD0: nop

    // 0x80048CD4: mul.s       $f8, $f2, $f2
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f8.fl = MUL_S(ctx->f2.fl, ctx->f2.fl);
    // 0x80048CD8: sub.s       $f12, $f4, $f6
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f12.fl = ctx->f4.fl - ctx->f6.fl;
    // 0x80048CDC: mul.s       $f6, $f12, $f12
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f6.fl = MUL_S(ctx->f12.fl, ctx->f12.fl);
    // 0x80048CE0: add.s       $f4, $f10, $f8
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f4.fl = ctx->f10.fl + ctx->f8.fl;
    // 0x80048CE4: mtc1        $zero, $f8
    ctx->f8.u32l = 0;
    // 0x80048CE8: add.s       $f10, $f4, $f6
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f10.fl = ctx->f4.fl + ctx->f6.fl;
    // 0x80048CEC: c.eq.s      $f8, $f10
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    c1cs = ctx->f8.fl == ctx->f10.fl;
    // 0x80048CF0: swc1        $f10, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->f10.u32l;
    // 0x80048CF4: lwc1        $f12, 0x34($sp)
    ctx->f12.u32l = MEM_W(ctx->r29, 0X34);
    // 0x80048CF8: bc1t        L_80048DF4
    if (c1cs) {
        // 0x80048CFC: nop
    
            goto L_80048DF4;
    }
    // 0x80048CFC: nop

    // 0x80048D00: jal         0x800C7010
    // 0x80048D04: sw          $a0, 0x70($sp)
    MEM_W(0X70, ctx->r29) = ctx->r4;
    _nsqrtf(rdram, ctx);
        goto after_2;
    // 0x80048D04: sw          $a0, 0x70($sp)
    MEM_W(0X70, ctx->r29) = ctx->r4;
    after_2:
    // 0x80048D08: lwc1        $f4, 0x44($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X44);
    // 0x80048D0C: lwc1        $f6, 0x5C($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X5C);
    // 0x80048D10: lw          $a0, 0x70($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X70);
    // 0x80048D14: div.s       $f2, $f4, $f0
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f2.fl = DIV_S(ctx->f4.fl, ctx->f0.fl);
    // 0x80048D18: lwc1        $f4, 0x58($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X58);
    // 0x80048D1C: lui         $t1, 0xFFFF
    ctx->r9 = S32(0XFFFF << 16);
    // 0x80048D20: lui         $at, 0x4780
    ctx->r1 = S32(0X4780 << 16);
    // 0x80048D24: mtc1        $at, $f12
    ctx->f12.u32l = ctx->r1;
    // 0x80048D28: mul.s       $f8, $f6, $f2
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f8.fl = MUL_S(ctx->f6.fl, ctx->f2.fl);
    // 0x80048D2C: nop

    // 0x80048D30: mul.s       $f6, $f4, $f2
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f6.fl = MUL_S(ctx->f4.fl, ctx->f2.fl);
    // 0x80048D34: trunc.w.s   $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.u32l = TRUNC_W_S(ctx->f8.fl);
    // 0x80048D38: trunc.w.s   $f8, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    ctx->f8.u32l = TRUNC_W_S(ctx->f6.fl);
    // 0x80048D3C: mfc1        $v0, $f10
    ctx->r2 = (int32_t)ctx->f10.u32l;
    // 0x80048D40: mfc1        $v1, $f8
    ctx->r3 = (int32_t)ctx->f8.u32l;
    // 0x80048D44: and         $t6, $v0, $t1
    ctx->r14 = ctx->r2 & ctx->r9;
    // 0x80048D48: sll         $t3, $v0, 16
    ctx->r11 = S32(ctx->r2 << 16);
    // 0x80048D4C: srl         $t7, $v1, 16
    ctx->r15 = S32(U32(ctx->r3) >> 16);
    // 0x80048D50: or          $t8, $t6, $t7
    ctx->r24 = ctx->r14 | ctx->r15;
    // 0x80048D54: sw          $t8, 0x8($a0)
    MEM_W(0X8, ctx->r4) = ctx->r24;
    // 0x80048D58: lwc1        $f10, 0x54($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0X54);
    // 0x80048D5C: andi        $t4, $v1, 0xFFFF
    ctx->r12 = ctx->r3 & 0XFFFF;
    // 0x80048D60: or          $t5, $t3, $t4
    ctx->r13 = ctx->r11 | ctx->r12;
    // 0x80048D64: mul.s       $f4, $f10, $f2
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f4.fl = MUL_S(ctx->f10.fl, ctx->f2.fl);
    // 0x80048D68: sw          $t5, 0x28($a0)
    MEM_W(0X28, ctx->r4) = ctx->r13;
    // 0x80048D6C: trunc.w.s   $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.u32l = TRUNC_W_S(ctx->f4.fl);
    // 0x80048D70: mfc1        $a1, $f6
    ctx->r5 = (int32_t)ctx->f6.u32l;
    // 0x80048D74: nop

    // 0x80048D78: and         $t2, $a1, $t1
    ctx->r10 = ctx->r5 & ctx->r9;
    // 0x80048D7C: sll         $t6, $a1, 16
    ctx->r14 = S32(ctx->r5 << 16);
    // 0x80048D80: sw          $t2, 0xC($a0)
    MEM_W(0XC, ctx->r4) = ctx->r10;
    // 0x80048D84: sw          $t6, 0x2C($a0)
    MEM_W(0X2C, ctx->r4) = ctx->r14;
    // 0x80048D88: lwc1        $f8, 0x8C($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X8C);
    // 0x80048D8C: lwc1        $f6, 0x90($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X90);
    // 0x80048D90: mul.s       $f10, $f12, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = MUL_S(ctx->f12.fl, ctx->f8.fl);
    // 0x80048D94: nop

    // 0x80048D98: mul.s       $f8, $f12, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = MUL_S(ctx->f12.fl, ctx->f6.fl);
    // 0x80048D9C: trunc.w.s   $f4, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    ctx->f4.u32l = TRUNC_W_S(ctx->f10.fl);
    // 0x80048DA0: trunc.w.s   $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.u32l = TRUNC_W_S(ctx->f8.fl);
    // 0x80048DA4: mfc1        $a2, $f4
    ctx->r6 = (int32_t)ctx->f4.u32l;
    // 0x80048DA8: mfc1        $a3, $f10
    ctx->r7 = (int32_t)ctx->f10.u32l;
    // 0x80048DAC: and         $t9, $a2, $t1
    ctx->r25 = ctx->r6 & ctx->r9;
    // 0x80048DB0: sll         $t7, $a2, 16
    ctx->r15 = S32(ctx->r6 << 16);
    // 0x80048DB4: srl         $t2, $a3, 16
    ctx->r10 = S32(U32(ctx->r7) >> 16);
    // 0x80048DB8: or          $t3, $t9, $t2
    ctx->r11 = ctx->r25 | ctx->r10;
    // 0x80048DBC: sw          $t3, 0x18($a0)
    MEM_W(0X18, ctx->r4) = ctx->r11;
    // 0x80048DC0: lwc1        $f4, 0x94($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X94);
    // 0x80048DC4: andi        $t8, $a3, 0xFFFF
    ctx->r24 = ctx->r7 & 0XFFFF;
    // 0x80048DC8: or          $t9, $t7, $t8
    ctx->r25 = ctx->r15 | ctx->r24;
    // 0x80048DCC: mul.s       $f6, $f12, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = MUL_S(ctx->f12.fl, ctx->f4.fl);
    // 0x80048DD0: sw          $t9, 0x38($a0)
    MEM_W(0X38, ctx->r4) = ctx->r25;
    // 0x80048DD4: trunc.w.s   $f8, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    ctx->f8.u32l = TRUNC_W_S(ctx->f6.fl);
    // 0x80048DD8: mfc1        $t0, $f8
    ctx->r8 = (int32_t)ctx->f8.u32l;
    // 0x80048DDC: nop

    // 0x80048DE0: and         $t5, $t0, $t1
    ctx->r13 = ctx->r8 & ctx->r9;
    // 0x80048DE4: ori         $t6, $t5, 0x1
    ctx->r14 = ctx->r13 | 0X1;
    // 0x80048DE8: sll         $t2, $t0, 16
    ctx->r10 = S32(ctx->r8 << 16);
    // 0x80048DEC: sw          $t6, 0x1C($a0)
    MEM_W(0X1C, ctx->r4) = ctx->r14;
    // 0x80048DF0: sw          $t2, 0x3C($a0)
    MEM_W(0X3C, ctx->r4) = ctx->r10;
L_80048DF4:
    // 0x80048DF4: lw          $ra, 0x2C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X2C);
L_80048DF8:
    // 0x80048DF8: ldc1        $f20, 0x10($sp)
    CHECK_FR(ctx, 20);
    ctx->f20.u64 = LD(ctx->r29, 0X10);
    // 0x80048DFC: ldc1        $f22, 0x18($sp)
    CHECK_FR(ctx, 22);
    ctx->f22.u64 = LD(ctx->r29, 0X18);
    // 0x80048E00: ldc1        $f24, 0x20($sp)
    CHECK_FR(ctx, 24);
    ctx->f24.u64 = LD(ctx->r29, 0X20);
    // 0x80048E04: jr          $ra
    // 0x80048E08: addiu       $sp, $sp, 0x70
    ctx->r29 = ADD32(ctx->r29, 0X70);
    return;
    // 0x80048E08: addiu       $sp, $sp, 0x70
    ctx->r29 = ADD32(ctx->r29, 0X70);
;}
RECOMP_FUNC void SysUtils_NormalizeVertexTri(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x80048E0C: addiu       $sp, $sp, -0x70
    ctx->r29 = ADD32(ctx->r29, -0X70);
    // 0x80048E10: sll         $t7, $a2, 4
    ctx->r15 = S32(ctx->r6 << 4);
    // 0x80048E14: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x80048E18: sw          $a1, 0x74($sp)
    MEM_W(0X74, ctx->r29) = ctx->r5;
    // 0x80048E1C: addu        $v0, $t7, $a0
    ctx->r2 = ADD32(ctx->r15, ctx->r4);
    // 0x80048E20: lh          $t9, 0x2($v0)
    ctx->r25 = MEM_H(ctx->r2, 0X2);
    // 0x80048E24: lh          $ra, 0x0($v0)
    ctx->r31 = MEM_H(ctx->r2, 0X0);
    // 0x80048E28: lw          $t7, 0x80($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X80);
    // 0x80048E2C: sw          $t9, 0x68($sp)
    MEM_W(0X68, ctx->r29) = ctx->r25;
    // 0x80048E30: lh          $t8, 0x4($v0)
    ctx->r24 = MEM_H(ctx->r2, 0X4);
    // 0x80048E34: sll         $t6, $a3, 4
    ctx->r14 = S32(ctx->r7 << 4);
    // 0x80048E38: sll         $t9, $t7, 4
    ctx->r25 = S32(ctx->r15 << 4);
    // 0x80048E3C: sw          $t8, 0x64($sp)
    MEM_W(0X64, ctx->r29) = ctx->r24;
    // 0x80048E40: addu        $v1, $t6, $a0
    ctx->r3 = ADD32(ctx->r14, ctx->r4);
    // 0x80048E44: addu        $t0, $t9, $a0
    ctx->r8 = ADD32(ctx->r25, ctx->r4);
    // 0x80048E48: lh          $t8, 0x0($t0)
    ctx->r24 = MEM_H(ctx->r8, 0X0);
    // 0x80048E4C: lh          $t1, 0x0($v1)
    ctx->r9 = MEM_H(ctx->r3, 0X0);
    // 0x80048E50: lh          $t2, 0x2($v1)
    ctx->r10 = MEM_H(ctx->r3, 0X2);
    // 0x80048E54: lh          $t3, 0x4($v1)
    ctx->r11 = MEM_H(ctx->r3, 0X4);
    // 0x80048E58: sw          $t8, 0x54($sp)
    MEM_W(0X54, ctx->r29) = ctx->r24;
    // 0x80048E5C: lh          $t6, 0x2($t0)
    ctx->r14 = MEM_H(ctx->r8, 0X2);
    // 0x80048E60: lw          $t9, 0x64($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X64);
    // 0x80048E64: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x80048E68: sw          $t6, 0x50($sp)
    MEM_W(0X50, ctx->r29) = ctx->r14;
    // 0x80048E6C: subu        $t6, $t6, $t2
    ctx->r14 = SUB32(ctx->r14, ctx->r10);
    // 0x80048E70: subu        $t4, $t9, $t3
    ctx->r12 = SUB32(ctx->r25, ctx->r11);
    // 0x80048E74: multu       $t4, $t6
    result = U64(U32(ctx->r12)) * U64(U32(ctx->r14)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80048E78: lh          $t7, 0x4($t0)
    ctx->r15 = MEM_H(ctx->r8, 0X4);
    // 0x80048E7C: sw          $t6, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r14;
    // 0x80048E80: sw          $t6, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r14;
    // 0x80048E84: sw          $t7, 0x4C($sp)
    MEM_W(0X4C, ctx->r29) = ctx->r15;
    // 0x80048E88: lw          $t7, 0x68($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X68);
    // 0x80048E8C: lw          $t8, 0x4C($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X4C);
    // 0x80048E90: subu        $t9, $t7, $t2
    ctx->r25 = SUB32(ctx->r15, ctx->r10);
    // 0x80048E94: subu        $t5, $t8, $t3
    ctx->r13 = SUB32(ctx->r24, ctx->r11);
    // 0x80048E98: mflo        $t7
    ctx->r15 = lo;
    // 0x80048E9C: sw          $t9, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r25;
    // 0x80048EA0: sw          $t9, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r25;
    // 0x80048EA4: multu       $t9, $t5
    result = U64(U32(ctx->r25)) * U64(U32(ctx->r13)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80048EA8: mflo        $t8
    ctx->r24 = lo;
    // 0x80048EAC: subu        $t7, $t7, $t8
    ctx->r15 = SUB32(ctx->r15, ctx->r24);
    // 0x80048EB0: mtc1        $t7, $f4
    ctx->f4.u32l = ctx->r15;
    // 0x80048EB4: lw          $t7, 0x54($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X54);
    // 0x80048EB8: subu        $t8, $ra, $t1
    ctx->r24 = SUB32(ctx->r31, ctx->r9);
    // 0x80048EBC: sw          $t8, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r24;
    // 0x80048EC0: subu        $t8, $t7, $t1
    ctx->r24 = SUB32(ctx->r15, ctx->r9);
    // 0x80048EC4: lw          $t7, 0x28($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X28);
    // 0x80048EC8: cvt.s.w     $f16, $f4
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 4);
    ctx->f16.fl = CVT_S_W(ctx->f4.u32l);
    // 0x80048ECC: sw          $t8, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r24;
    // 0x80048ED0: multu       $t7, $t5
    result = U64(U32(ctx->r15)) * U64(U32(ctx->r13)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80048ED4: mul.s       $f10, $f16, $f16
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f10.fl = MUL_S(ctx->f16.fl, ctx->f16.fl);
    // 0x80048ED8: mflo        $t6
    ctx->r14 = lo;
    // 0x80048EDC: nop

    // 0x80048EE0: nop

    // 0x80048EE4: multu       $t4, $t8
    result = U64(U32(ctx->r12)) * U64(U32(ctx->r24)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80048EE8: mflo        $t9
    ctx->r25 = lo;
    // 0x80048EEC: subu        $t6, $t6, $t9
    ctx->r14 = SUB32(ctx->r14, ctx->r25);
    // 0x80048EF0: lw          $t9, 0x1C($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X1C);
    // 0x80048EF4: mtc1        $t6, $f6
    ctx->f6.u32l = ctx->r14;
    // 0x80048EF8: multu       $t9, $t8
    result = U64(U32(ctx->r25)) * U64(U32(ctx->r24)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80048EFC: lw          $t9, 0x18($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X18);
    // 0x80048F00: cvt.s.w     $f18, $f6
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 6);
    ctx->f18.fl = CVT_S_W(ctx->f6.u32l);
    // 0x80048F04: mul.s       $f4, $f18, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f4.fl = MUL_S(ctx->f18.fl, ctx->f18.fl);
    // 0x80048F08: mflo        $t6
    ctx->r14 = lo;
    // 0x80048F0C: nop

    // 0x80048F10: nop

    // 0x80048F14: multu       $t7, $t9
    result = U64(U32(ctx->r15)) * U64(U32(ctx->r25)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80048F18: add.s       $f6, $f10, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = ctx->f10.fl + ctx->f4.fl;
    // 0x80048F1C: lwc1        $f10, -0x6DC0($at)
    ctx->f10.u32l = MEM_W(ctx->r1, -0X6DC0);
    // 0x80048F20: mflo        $t8
    ctx->r24 = lo;
    // 0x80048F24: subu        $t7, $t6, $t8
    ctx->r15 = SUB32(ctx->r14, ctx->r24);
    // 0x80048F28: mtc1        $t7, $f8
    ctx->f8.u32l = ctx->r15;
    // 0x80048F2C: nop

    // 0x80048F30: cvt.s.w     $f0, $f8
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 8);
    ctx->f0.fl = CVT_S_W(ctx->f8.u32l);
    // 0x80048F34: mul.s       $f8, $f0, $f0
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f8.fl = MUL_S(ctx->f0.fl, ctx->f0.fl);
    // 0x80048F38: swc1        $f0, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->f0.u32l;
    // 0x80048F3C: add.s       $f2, $f6, $f8
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f2.fl = ctx->f6.fl + ctx->f8.fl;
    // 0x80048F40: c.lt.s      $f2, $f10
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 10);
    c1cs = ctx->f2.fl < ctx->f10.fl;
    // 0x80048F44: swc1        $f2, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->f2.u32l;
    // 0x80048F48: lwc1        $f12, 0x3C($sp)
    ctx->f12.u32l = MEM_W(ctx->r29, 0X3C);
    // 0x80048F4C: bc1tl       L_80049138
    if (c1cs) {
        // 0x80048F50: lw          $ra, 0x14($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X14);
            goto L_80049138;
    }
    goto skip_0;
    // 0x80048F50: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    skip_0:
    // 0x80048F54: sw          $a0, 0x70($sp)
    MEM_W(0X70, ctx->r29) = ctx->r4;
    // 0x80048F58: swc1        $f16, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->f16.u32l;
    // 0x80048F5C: jal         0x800C7010
    // 0x80048F60: swc1        $f18, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->f18.u32l;
    _nsqrtf(rdram, ctx);
        goto after_0;
    // 0x80048F60: swc1        $f18, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->f18.u32l;
    after_0:
    // 0x80048F64: lui         $at, 0x42DC
    ctx->r1 = S32(0X42DC << 16);
    // 0x80048F68: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x80048F6C: lwc1        $f16, 0x48($sp)
    ctx->f16.u32l = MEM_W(ctx->r29, 0X48);
    // 0x80048F70: addiu       $t7, $zero, 0x1
    ctx->r15 = ADD32(0, 0X1);
    // 0x80048F74: div.s       $f2, $f4, $f0
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f2.fl = DIV_S(ctx->f4.fl, ctx->f0.fl);
    // 0x80048F78: lw          $t9, 0x74($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X74);
    // 0x80048F7C: lw          $a0, 0x70($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X70);
    // 0x80048F80: lwc1        $f18, 0x44($sp)
    ctx->f18.u32l = MEM_W(ctx->r29, 0X44);
    // 0x80048F84: sll         $t6, $t9, 4
    ctx->r14 = S32(ctx->r25 << 4);
    // 0x80048F88: lui         $at, 0x4F00
    ctx->r1 = S32(0X4F00 << 16);
    // 0x80048F8C: addu        $v0, $t6, $a0
    ctx->r2 = ADD32(ctx->r14, ctx->r4);
    // 0x80048F90: mul.s       $f6, $f16, $f2
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f6.fl = MUL_S(ctx->f16.fl, ctx->f2.fl);
    // 0x80048F94: cfc1        $t8, $FpcCsr
    ctx->r24 = get_cop1_cs();
    // 0x80048F98: ctc1        $t7, $FpcCsr
    set_cop1_cs(ctx->r15);
    // 0x80048F9C: nop

    // 0x80048FA0: cvt.w.s     $f8, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    ctx->f8.u32l = CVT_W_S(ctx->f6.fl);
    // 0x80048FA4: cfc1        $t7, $FpcCsr
    ctx->r15 = get_cop1_cs();
    // 0x80048FA8: nop

    // 0x80048FAC: andi        $t7, $t7, 0x78
    ctx->r15 = ctx->r15 & 0X78;
    // 0x80048FB0: beql        $t7, $zero, L_80049000
    if (ctx->r15 == 0) {
        // 0x80048FB4: mfc1        $t7, $f8
        ctx->r15 = (int32_t)ctx->f8.u32l;
            goto L_80049000;
    }
    goto skip_1;
    // 0x80048FB4: mfc1        $t7, $f8
    ctx->r15 = (int32_t)ctx->f8.u32l;
    skip_1:
    // 0x80048FB8: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x80048FBC: addiu       $t7, $zero, 0x1
    ctx->r15 = ADD32(0, 0X1);
    // 0x80048FC0: sub.s       $f8, $f6, $f8
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f8.fl = ctx->f6.fl - ctx->f8.fl;
    // 0x80048FC4: ctc1        $t7, $FpcCsr
    set_cop1_cs(ctx->r15);
    // 0x80048FC8: nop

    // 0x80048FCC: cvt.w.s     $f8, $f8
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 8);
    ctx->f8.u32l = CVT_W_S(ctx->f8.fl);
    // 0x80048FD0: cfc1        $t7, $FpcCsr
    ctx->r15 = get_cop1_cs();
    // 0x80048FD4: nop

    // 0x80048FD8: andi        $t7, $t7, 0x78
    ctx->r15 = ctx->r15 & 0X78;
    // 0x80048FDC: bne         $t7, $zero, L_80048FF4
    if (ctx->r15 != 0) {
        // 0x80048FE0: nop
    
            goto L_80048FF4;
    }
    // 0x80048FE0: nop

    // 0x80048FE4: mfc1        $t7, $f8
    ctx->r15 = (int32_t)ctx->f8.u32l;
    // 0x80048FE8: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x80048FEC: b           L_8004900C
    // 0x80048FF0: or          $t7, $t7, $at
    ctx->r15 = ctx->r15 | ctx->r1;
        goto L_8004900C;
    // 0x80048FF0: or          $t7, $t7, $at
    ctx->r15 = ctx->r15 | ctx->r1;
L_80048FF4:
    // 0x80048FF4: b           L_8004900C
    // 0x80048FF8: addiu       $t7, $zero, -0x1
    ctx->r15 = ADD32(0, -0X1);
        goto L_8004900C;
    // 0x80048FF8: addiu       $t7, $zero, -0x1
    ctx->r15 = ADD32(0, -0X1);
    // 0x80048FFC: mfc1        $t7, $f8
    ctx->r15 = (int32_t)ctx->f8.u32l;
L_80049000:
    // 0x80049000: nop

    // 0x80049004: bltz        $t7, L_80048FF4
    if (SIGNED(ctx->r15) < 0) {
        // 0x80049008: nop
    
            goto L_80048FF4;
    }
    // 0x80049008: nop

L_8004900C:
    // 0x8004900C: ctc1        $t8, $FpcCsr
    set_cop1_cs(ctx->r24);
    // 0x80049010: addiu       $t6, $zero, 0x1
    ctx->r14 = ADD32(0, 0X1);
    // 0x80049014: sb          $t7, 0xC($v0)
    MEM_B(0XC, ctx->r2) = ctx->r15;
    // 0x80049018: mul.s       $f10, $f18, $f2
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f10.fl = MUL_S(ctx->f18.fl, ctx->f2.fl);
    // 0x8004901C: lui         $at, 0x4F00
    ctx->r1 = S32(0X4F00 << 16);
    // 0x80049020: cfc1        $t9, $FpcCsr
    ctx->r25 = get_cop1_cs();
    // 0x80049024: ctc1        $t6, $FpcCsr
    set_cop1_cs(ctx->r14);
    // 0x80049028: nop

    // 0x8004902C: cvt.w.s     $f4, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    ctx->f4.u32l = CVT_W_S(ctx->f10.fl);
    // 0x80049030: cfc1        $t6, $FpcCsr
    ctx->r14 = get_cop1_cs();
    // 0x80049034: nop

    // 0x80049038: andi        $t6, $t6, 0x78
    ctx->r14 = ctx->r14 & 0X78;
    // 0x8004903C: beql        $t6, $zero, L_8004908C
    if (ctx->r14 == 0) {
        // 0x80049040: mfc1        $t6, $f4
        ctx->r14 = (int32_t)ctx->f4.u32l;
            goto L_8004908C;
    }
    goto skip_2;
    // 0x80049040: mfc1        $t6, $f4
    ctx->r14 = (int32_t)ctx->f4.u32l;
    skip_2:
    // 0x80049044: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x80049048: addiu       $t6, $zero, 0x1
    ctx->r14 = ADD32(0, 0X1);
    // 0x8004904C: sub.s       $f4, $f10, $f4
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f4.fl = ctx->f10.fl - ctx->f4.fl;
    // 0x80049050: ctc1        $t6, $FpcCsr
    set_cop1_cs(ctx->r14);
    // 0x80049054: nop

    // 0x80049058: cvt.w.s     $f4, $f4
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 4);
    ctx->f4.u32l = CVT_W_S(ctx->f4.fl);
    // 0x8004905C: cfc1        $t6, $FpcCsr
    ctx->r14 = get_cop1_cs();
    // 0x80049060: nop

    // 0x80049064: andi        $t6, $t6, 0x78
    ctx->r14 = ctx->r14 & 0X78;
    // 0x80049068: bne         $t6, $zero, L_80049080
    if (ctx->r14 != 0) {
        // 0x8004906C: nop
    
            goto L_80049080;
    }
    // 0x8004906C: nop

    // 0x80049070: mfc1        $t6, $f4
    ctx->r14 = (int32_t)ctx->f4.u32l;
    // 0x80049074: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x80049078: b           L_80049098
    // 0x8004907C: or          $t6, $t6, $at
    ctx->r14 = ctx->r14 | ctx->r1;
        goto L_80049098;
    // 0x8004907C: or          $t6, $t6, $at
    ctx->r14 = ctx->r14 | ctx->r1;
L_80049080:
    // 0x80049080: b           L_80049098
    // 0x80049084: addiu       $t6, $zero, -0x1
    ctx->r14 = ADD32(0, -0X1);
        goto L_80049098;
    // 0x80049084: addiu       $t6, $zero, -0x1
    ctx->r14 = ADD32(0, -0X1);
    // 0x80049088: mfc1        $t6, $f4
    ctx->r14 = (int32_t)ctx->f4.u32l;
L_8004908C:
    // 0x8004908C: nop

    // 0x80049090: bltz        $t6, L_80049080
    if (SIGNED(ctx->r14) < 0) {
        // 0x80049094: nop
    
            goto L_80049080;
    }
    // 0x80049094: nop

L_80049098:
    // 0x80049098: sb          $t6, 0xD($v0)
    MEM_B(0XD, ctx->r2) = ctx->r14;
    // 0x8004909C: ctc1        $t9, $FpcCsr
    set_cop1_cs(ctx->r25);
    // 0x800490A0: lwc1        $f6, 0x40($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X40);
    // 0x800490A4: addiu       $t7, $zero, 0x1
    ctx->r15 = ADD32(0, 0X1);
    // 0x800490A8: lui         $at, 0x4F00
    ctx->r1 = S32(0X4F00 << 16);
    // 0x800490AC: mul.s       $f8, $f6, $f2
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f8.fl = MUL_S(ctx->f6.fl, ctx->f2.fl);
    // 0x800490B0: cfc1        $t8, $FpcCsr
    ctx->r24 = get_cop1_cs();
    // 0x800490B4: ctc1        $t7, $FpcCsr
    set_cop1_cs(ctx->r15);
    // 0x800490B8: nop

    // 0x800490BC: cvt.w.s     $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.u32l = CVT_W_S(ctx->f8.fl);
    // 0x800490C0: cfc1        $t7, $FpcCsr
    ctx->r15 = get_cop1_cs();
    // 0x800490C4: nop

    // 0x800490C8: andi        $t7, $t7, 0x78
    ctx->r15 = ctx->r15 & 0X78;
    // 0x800490CC: beql        $t7, $zero, L_8004911C
    if (ctx->r15 == 0) {
        // 0x800490D0: mfc1        $t7, $f10
        ctx->r15 = (int32_t)ctx->f10.u32l;
            goto L_8004911C;
    }
    goto skip_3;
    // 0x800490D0: mfc1        $t7, $f10
    ctx->r15 = (int32_t)ctx->f10.u32l;
    skip_3:
    // 0x800490D4: mtc1        $at, $f10
    ctx->f10.u32l = ctx->r1;
    // 0x800490D8: addiu       $t7, $zero, 0x1
    ctx->r15 = ADD32(0, 0X1);
    // 0x800490DC: sub.s       $f10, $f8, $f10
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f10.fl = ctx->f8.fl - ctx->f10.fl;
    // 0x800490E0: ctc1        $t7, $FpcCsr
    set_cop1_cs(ctx->r15);
    // 0x800490E4: nop

    // 0x800490E8: cvt.w.s     $f10, $f10
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 10);
    ctx->f10.u32l = CVT_W_S(ctx->f10.fl);
    // 0x800490EC: cfc1        $t7, $FpcCsr
    ctx->r15 = get_cop1_cs();
    // 0x800490F0: nop

    // 0x800490F4: andi        $t7, $t7, 0x78
    ctx->r15 = ctx->r15 & 0X78;
    // 0x800490F8: bne         $t7, $zero, L_80049110
    if (ctx->r15 != 0) {
        // 0x800490FC: nop
    
            goto L_80049110;
    }
    // 0x800490FC: nop

    // 0x80049100: mfc1        $t7, $f10
    ctx->r15 = (int32_t)ctx->f10.u32l;
    // 0x80049104: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x80049108: b           L_80049128
    // 0x8004910C: or          $t7, $t7, $at
    ctx->r15 = ctx->r15 | ctx->r1;
        goto L_80049128;
    // 0x8004910C: or          $t7, $t7, $at
    ctx->r15 = ctx->r15 | ctx->r1;
L_80049110:
    // 0x80049110: b           L_80049128
    // 0x80049114: addiu       $t7, $zero, -0x1
    ctx->r15 = ADD32(0, -0X1);
        goto L_80049128;
    // 0x80049114: addiu       $t7, $zero, -0x1
    ctx->r15 = ADD32(0, -0X1);
    // 0x80049118: mfc1        $t7, $f10
    ctx->r15 = (int32_t)ctx->f10.u32l;
L_8004911C:
    // 0x8004911C: nop

    // 0x80049120: bltz        $t7, L_80049110
    if (SIGNED(ctx->r15) < 0) {
        // 0x80049124: nop
    
            goto L_80049110;
    }
    // 0x80049124: nop

L_80049128:
    // 0x80049128: ctc1        $t8, $FpcCsr
    set_cop1_cs(ctx->r24);
    // 0x8004912C: sb          $t7, 0xE($v0)
    MEM_B(0XE, ctx->r2) = ctx->r15;
    // 0x80049130: nop

    // 0x80049134: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_80049138:
    // 0x80049138: addiu       $sp, $sp, 0x70
    ctx->r29 = ADD32(ctx->r29, 0X70);
    // 0x8004913C: jr          $ra
    // 0x80049140: nop

    return;
    // 0x80049140: nop

;}
RECOMP_FUNC void SysUtils_InterpolateMtx(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x80049144: addiu       $sp, $sp, -0x90
    ctx->r29 = ADD32(ctx->r29, -0X90);
    // 0x80049148: sw          $ra, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r31;
    // 0x8004914C: sdc1        $f30, 0x38($sp)
    CHECK_FR(ctx, 30);
    SD(ctx->f30.u64, 0X38, ctx->r29);
    // 0x80049150: sdc1        $f28, 0x30($sp)
    CHECK_FR(ctx, 28);
    SD(ctx->f28.u64, 0X30, ctx->r29);
    // 0x80049154: sdc1        $f26, 0x28($sp)
    CHECK_FR(ctx, 26);
    SD(ctx->f26.u64, 0X28, ctx->r29);
    // 0x80049158: sdc1        $f24, 0x20($sp)
    CHECK_FR(ctx, 24);
    SD(ctx->f24.u64, 0X20, ctx->r29);
    // 0x8004915C: sdc1        $f22, 0x18($sp)
    CHECK_FR(ctx, 22);
    SD(ctx->f22.u64, 0X18, ctx->r29);
    // 0x80049160: sdc1        $f20, 0x10($sp)
    CHECK_FR(ctx, 20);
    SD(ctx->f20.u64, 0X10, ctx->r29);
    // 0x80049164: lh          $t7, 0x8($a0)
    ctx->r15 = MEM_H(ctx->r4, 0X8);
    // 0x80049168: lh          $t3, 0x8($a1)
    ctx->r11 = MEM_H(ctx->r5, 0X8);
    // 0x8004916C: lhu         $t6, 0x28($a0)
    ctx->r14 = MEM_HU(ctx->r4, 0X28);
    // 0x80049170: lhu         $t2, 0x28($a1)
    ctx->r10 = MEM_HU(ctx->r5, 0X28);
    // 0x80049174: sll         $t8, $t7, 16
    ctx->r24 = S32(ctx->r15 << 16);
    // 0x80049178: sll         $t4, $t3, 16
    ctx->r12 = S32(ctx->r11 << 16);
    // 0x8004917C: or          $t9, $t6, $t8
    ctx->r25 = ctx->r14 | ctx->r24;
    // 0x80049180: or          $t5, $t2, $t4
    ctx->r13 = ctx->r10 | ctx->r12;
    // 0x80049184: mtc1        $t9, $f4
    ctx->f4.u32l = ctx->r25;
    // 0x80049188: mtc1        $t5, $f8
    ctx->f8.u32l = ctx->r13;
    // 0x8004918C: lui         $at, 0x4780
    ctx->r1 = S32(0X4780 << 16);
    // 0x80049190: cvt.s.w     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
    // 0x80049194: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
    // 0x80049198: mtc1        $a3, $f28
    ctx->f28.u32l = ctx->r7;
    // 0x8004919C: lh          $t6, 0xA($a0)
    ctx->r14 = MEM_H(ctx->r4, 0XA);
    // 0x800491A0: lh          $t2, 0xA($a1)
    ctx->r10 = MEM_H(ctx->r5, 0XA);
    // 0x800491A4: cvt.s.w     $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.fl = CVT_S_W(ctx->f8.u32l);
    // 0x800491A8: lhu         $t7, 0x2A($a0)
    ctx->r15 = MEM_HU(ctx->r4, 0X2A);
    // 0x800491AC: lhu         $t3, 0x2A($a1)
    ctx->r11 = MEM_HU(ctx->r5, 0X2A);
    // 0x800491B0: sll         $t8, $t6, 16
    ctx->r24 = S32(ctx->r14 << 16);
    // 0x800491B4: sll         $t4, $t2, 16
    ctx->r12 = S32(ctx->r10 << 16);
    // 0x800491B8: div.s       $f12, $f6, $f16
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f12.fl = DIV_S(ctx->f6.fl, ctx->f16.fl);
    // 0x800491BC: or          $t9, $t7, $t8
    ctx->r25 = ctx->r15 | ctx->r24;
    // 0x800491C0: or          $t5, $t3, $t4
    ctx->r13 = ctx->r11 | ctx->r12;
    // 0x800491C4: mtc1        $t9, $f8
    ctx->f8.u32l = ctx->r25;
    // 0x800491C8: lh          $t7, 0xC($a0)
    ctx->r15 = MEM_H(ctx->r4, 0XC);
    // 0x800491CC: lh          $t3, 0xC($a1)
    ctx->r11 = MEM_H(ctx->r5, 0XC);
    // 0x800491D0: lhu         $t6, 0x2C($a0)
    ctx->r14 = MEM_HU(ctx->r4, 0X2C);
    // 0x800491D4: lhu         $t2, 0x2C($a1)
    ctx->r10 = MEM_HU(ctx->r5, 0X2C);
    // 0x800491D8: sll         $t8, $t7, 16
    ctx->r24 = S32(ctx->r15 << 16);
    // 0x800491DC: sll         $t4, $t3, 16
    ctx->r12 = S32(ctx->r11 << 16);
    // 0x800491E0: or          $t9, $t6, $t8
    ctx->r25 = ctx->r14 | ctx->r24;
    // 0x800491E4: div.s       $f2, $f10, $f16
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f2.fl = DIV_S(ctx->f10.fl, ctx->f16.fl);
    // 0x800491E8: cvt.s.w     $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.fl = CVT_S_W(ctx->f8.u32l);
    // 0x800491EC: sub.s       $f4, $f2, $f12
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f4.fl = ctx->f2.fl - ctx->f12.fl;
    // 0x800491F0: mul.s       $f6, $f4, $f28
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 28);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f28.fl); 
    ctx->f6.fl = MUL_S(ctx->f4.fl, ctx->f28.fl);
    // 0x800491F4: mtc1        $t5, $f4
    ctx->f4.u32l = ctx->r13;
    // 0x800491F8: or          $t5, $t2, $t4
    ctx->r13 = ctx->r10 | ctx->r12;
    // 0x800491FC: add.s       $f22, $f6, $f12
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f22.fl = ctx->f6.fl + ctx->f12.fl;
    // 0x80049200: cvt.s.w     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
    // 0x80049204: mtc1        $t9, $f4
    ctx->f4.u32l = ctx->r25;
    // 0x80049208: div.s       $f12, $f10, $f16
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f12.fl = DIV_S(ctx->f10.fl, ctx->f16.fl);
    // 0x8004920C: div.s       $f2, $f6, $f16
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f2.fl = DIV_S(ctx->f6.fl, ctx->f16.fl);
    // 0x80049210: cvt.s.w     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
    // 0x80049214: sub.s       $f8, $f2, $f12
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f8.fl = ctx->f2.fl - ctx->f12.fl;
    // 0x80049218: mul.s       $f10, $f8, $f28
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 28);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f28.fl); 
    ctx->f10.fl = MUL_S(ctx->f8.fl, ctx->f28.fl);
    // 0x8004921C: mtc1        $t5, $f8
    ctx->f8.u32l = ctx->r13;
    // 0x80049220: add.s       $f24, $f10, $f12
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f24.fl = ctx->f10.fl + ctx->f12.fl;
    // 0x80049224: cvt.s.w     $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.fl = CVT_S_W(ctx->f8.u32l);
    // 0x80049228: div.s       $f12, $f6, $f16
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f12.fl = DIV_S(ctx->f6.fl, ctx->f16.fl);
    // 0x8004922C: div.s       $f2, $f10, $f16
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f2.fl = DIV_S(ctx->f10.fl, ctx->f16.fl);
    // 0x80049230: sub.s       $f4, $f2, $f12
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f4.fl = ctx->f2.fl - ctx->f12.fl;
    // 0x80049234: mul.s       $f6, $f4, $f28
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 28);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f28.fl); 
    ctx->f6.fl = MUL_S(ctx->f4.fl, ctx->f28.fl);
    // 0x80049238: add.s       $f30, $f6, $f12
    CHECK_FR(ctx, 30);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f30.fl = ctx->f6.fl + ctx->f12.fl;
    // 0x8004923C: mul.s       $f8, $f22, $f22
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f8.fl = MUL_S(ctx->f22.fl, ctx->f22.fl);
    // 0x80049240: nop

    // 0x80049244: mul.s       $f10, $f24, $f24
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 24);
    NAN_CHECK(ctx->f24.fl); NAN_CHECK(ctx->f24.fl); 
    ctx->f10.fl = MUL_S(ctx->f24.fl, ctx->f24.fl);
    // 0x80049248: add.s       $f4, $f8, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f4.fl = ctx->f8.fl + ctx->f10.fl;
    // 0x8004924C: mul.s       $f6, $f30, $f30
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 30);
    CHECK_FR(ctx, 30);
    NAN_CHECK(ctx->f30.fl); NAN_CHECK(ctx->f30.fl); 
    ctx->f6.fl = MUL_S(ctx->f30.fl, ctx->f30.fl);
    // 0x80049250: mtc1        $zero, $f8
    ctx->f8.u32l = 0;
    // 0x80049254: add.s       $f12, $f4, $f6
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f12.fl = ctx->f4.fl + ctx->f6.fl;
    // 0x80049258: c.eq.s      $f12, $f8
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 8);
    c1cs = ctx->f12.fl == ctx->f8.fl;
    // 0x8004925C: nop

    // 0x80049260: bc1t        L_800496EC
    if (c1cs) {
        // 0x80049264: nop
    
            goto L_800496EC;
    }
    // 0x80049264: nop

    // 0x80049268: sw          $a0, 0x90($sp)
    MEM_W(0X90, ctx->r29) = ctx->r4;
    // 0x8004926C: sw          $a1, 0x94($sp)
    MEM_W(0X94, ctx->r29) = ctx->r5;
    // 0x80049270: jal         0x800C7010
    // 0x80049274: sw          $a2, 0x98($sp)
    MEM_W(0X98, ctx->r29) = ctx->r6;
    _nsqrtf(rdram, ctx);
        goto after_0;
    // 0x80049274: sw          $a2, 0x98($sp)
    MEM_W(0X98, ctx->r29) = ctx->r6;
    after_0:
    // 0x80049278: lui         $at, 0x4780
    ctx->r1 = S32(0X4780 << 16);
    // 0x8004927C: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
    // 0x80049280: lw          $a2, 0x98($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X98);
    // 0x80049284: lw          $a0, 0x90($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X90);
    // 0x80049288: div.s       $f14, $f16, $f0
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f14.fl = DIV_S(ctx->f16.fl, ctx->f0.fl);
    // 0x8004928C: lw          $a1, 0x94($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X94);
    // 0x80049290: lui         $t0, 0xFFFF
    ctx->r8 = S32(0XFFFF << 16);
    // 0x80049294: mul.s       $f10, $f22, $f14
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f10.fl = MUL_S(ctx->f22.fl, ctx->f14.fl);
    // 0x80049298: trunc.w.s   $f4, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    ctx->f4.u32l = TRUNC_W_S(ctx->f10.fl);
    // 0x8004929C: mul.s       $f6, $f24, $f14
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f24.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f6.fl = MUL_S(ctx->f24.fl, ctx->f14.fl);
    // 0x800492A0: nop

    // 0x800492A4: mul.s       $f10, $f30, $f14
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 30);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f30.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f10.fl = MUL_S(ctx->f30.fl, ctx->f14.fl);
    // 0x800492A8: mfc1        $v0, $f4
    ctx->r2 = (int32_t)ctx->f4.u32l;
    // 0x800492AC: nop

    // 0x800492B0: and         $t8, $v0, $t0
    ctx->r24 = ctx->r2 & ctx->r8;
    // 0x800492B4: sll         $t5, $v0, 16
    ctx->r13 = S32(ctx->r2 << 16);
    // 0x800492B8: trunc.w.s   $f8, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    ctx->f8.u32l = TRUNC_W_S(ctx->f6.fl);
    // 0x800492BC: trunc.w.s   $f4, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    ctx->f4.u32l = TRUNC_W_S(ctx->f10.fl);
    // 0x800492C0: mfc1        $v1, $f8
    ctx->r3 = (int32_t)ctx->f8.u32l;
    // 0x800492C4: mfc1        $a3, $f4
    ctx->r7 = (int32_t)ctx->f4.u32l;
    // 0x800492C8: srl         $t9, $v1, 16
    ctx->r25 = S32(U32(ctx->r3) >> 16);
    // 0x800492CC: or          $t3, $t8, $t9
    ctx->r11 = ctx->r24 | ctx->r25;
    // 0x800492D0: andi        $t7, $v1, 0xFFFF
    ctx->r15 = ctx->r3 & 0XFFFF;
    // 0x800492D4: or          $t6, $t5, $t7
    ctx->r14 = ctx->r13 | ctx->r15;
    // 0x800492D8: and         $t4, $a3, $t0
    ctx->r12 = ctx->r7 & ctx->r8;
    // 0x800492DC: sll         $t8, $a3, 16
    ctx->r24 = S32(ctx->r7 << 16);
    // 0x800492E0: sw          $t3, 0x8($a2)
    MEM_W(0X8, ctx->r6) = ctx->r11;
    // 0x800492E4: sw          $t4, 0xC($a2)
    MEM_W(0XC, ctx->r6) = ctx->r12;
    // 0x800492E8: sw          $t6, 0x28($a2)
    MEM_W(0X28, ctx->r6) = ctx->r14;
    // 0x800492EC: sw          $t8, 0x2C($a2)
    MEM_W(0X2C, ctx->r6) = ctx->r24;
    // 0x800492F0: lh          $t3, 0x10($a0)
    ctx->r11 = MEM_H(ctx->r4, 0X10);
    // 0x800492F4: lh          $t7, 0x10($a1)
    ctx->r15 = MEM_H(ctx->r5, 0X10);
    // 0x800492F8: lhu         $t9, 0x30($a0)
    ctx->r25 = MEM_HU(ctx->r4, 0X30);
    // 0x800492FC: lhu         $t5, 0x30($a1)
    ctx->r13 = MEM_HU(ctx->r5, 0X30);
    // 0x80049300: sll         $t2, $t3, 16
    ctx->r10 = S32(ctx->r11 << 16);
    // 0x80049304: sll         $t6, $t7, 16
    ctx->r14 = S32(ctx->r15 << 16);
    // 0x80049308: or          $t4, $t9, $t2
    ctx->r12 = ctx->r25 | ctx->r10;
    // 0x8004930C: or          $t8, $t5, $t6
    ctx->r24 = ctx->r13 | ctx->r14;
    // 0x80049310: mtc1        $t4, $f6
    ctx->f6.u32l = ctx->r12;
    // 0x80049314: mtc1        $t8, $f10
    ctx->f10.u32l = ctx->r24;
    // 0x80049318: cvt.s.w     $f8, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    ctx->f8.fl = CVT_S_W(ctx->f6.u32l);
    // 0x8004931C: cvt.s.w     $f4, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    ctx->f4.fl = CVT_S_W(ctx->f10.u32l);
    // 0x80049320: div.s       $f12, $f8, $f16
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f12.fl = DIV_S(ctx->f8.fl, ctx->f16.fl);
    // 0x80049324: div.s       $f2, $f4, $f16
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f2.fl = DIV_S(ctx->f4.fl, ctx->f16.fl);
    // 0x80049328: sub.s       $f6, $f2, $f12
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f6.fl = ctx->f2.fl - ctx->f12.fl;
    // 0x8004932C: mul.s       $f8, $f6, $f28
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 28);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f28.fl); 
    ctx->f8.fl = MUL_S(ctx->f6.fl, ctx->f28.fl);
    // 0x80049330: add.s       $f10, $f8, $f12
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f10.fl = ctx->f8.fl + ctx->f12.fl;
    // 0x80049334: swc1        $f10, 0x60($sp)
    MEM_W(0X60, ctx->r29) = ctx->f10.u32l;
    // 0x80049338: lh          $t9, 0x12($a0)
    ctx->r25 = MEM_H(ctx->r4, 0X12);
    // 0x8004933C: lhu         $t3, 0x32($a0)
    ctx->r11 = MEM_HU(ctx->r4, 0X32);
    // 0x80049340: lh          $t5, 0x12($a1)
    ctx->r13 = MEM_H(ctx->r5, 0X12);
    // 0x80049344: lhu         $t7, 0x32($a1)
    ctx->r15 = MEM_HU(ctx->r5, 0X32);
    // 0x80049348: sll         $t2, $t9, 16
    ctx->r10 = S32(ctx->r25 << 16);
    // 0x8004934C: or          $t4, $t3, $t2
    ctx->r12 = ctx->r11 | ctx->r10;
    // 0x80049350: sll         $t6, $t5, 16
    ctx->r14 = S32(ctx->r13 << 16);
    // 0x80049354: mtc1        $t4, $f4
    ctx->f4.u32l = ctx->r12;
    // 0x80049358: or          $t8, $t7, $t6
    ctx->r24 = ctx->r15 | ctx->r14;
    // 0x8004935C: mtc1        $t8, $f8
    ctx->f8.u32l = ctx->r24;
    // 0x80049360: cvt.s.w     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
    // 0x80049364: lh          $t3, 0x14($a0)
    ctx->r11 = MEM_H(ctx->r4, 0X14);
    // 0x80049368: lhu         $t9, 0x34($a0)
    ctx->r25 = MEM_HU(ctx->r4, 0X34);
    // 0x8004936C: lh          $t7, 0x14($a1)
    ctx->r15 = MEM_H(ctx->r5, 0X14);
    // 0x80049370: lhu         $t5, 0x34($a1)
    ctx->r13 = MEM_HU(ctx->r5, 0X34);
    // 0x80049374: cvt.s.w     $f4, $f8
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    ctx->f4.fl = CVT_S_W(ctx->f8.u32l);
    // 0x80049378: sll         $t2, $t3, 16
    ctx->r10 = S32(ctx->r11 << 16);
    // 0x8004937C: or          $t4, $t9, $t2
    ctx->r12 = ctx->r25 | ctx->r10;
    // 0x80049380: sll         $t6, $t7, 16
    ctx->r14 = S32(ctx->r15 << 16);
    // 0x80049384: or          $t8, $t5, $t6
    ctx->r24 = ctx->r13 | ctx->r14;
    // 0x80049388: div.s       $f12, $f6, $f16
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f12.fl = DIV_S(ctx->f6.fl, ctx->f16.fl);
    // 0x8004938C: div.s       $f2, $f4, $f16
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f2.fl = DIV_S(ctx->f4.fl, ctx->f16.fl);
    // 0x80049390: mtc1        $t4, $f4
    ctx->f4.u32l = ctx->r12;
    // 0x80049394: sub.s       $f6, $f2, $f12
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f6.fl = ctx->f2.fl - ctx->f12.fl;
    // 0x80049398: mul.s       $f8, $f6, $f28
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 28);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f28.fl); 
    ctx->f8.fl = MUL_S(ctx->f6.fl, ctx->f28.fl);
    // 0x8004939C: cvt.s.w     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
    // 0x800493A0: add.s       $f14, $f8, $f12
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f14.fl = ctx->f8.fl + ctx->f12.fl;
    // 0x800493A4: mtc1        $t8, $f8
    ctx->f8.u32l = ctx->r24;
    // 0x800493A8: div.s       $f12, $f6, $f16
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f12.fl = DIV_S(ctx->f6.fl, ctx->f16.fl);
    // 0x800493AC: cvt.s.w     $f4, $f8
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    ctx->f4.fl = CVT_S_W(ctx->f8.u32l);
    // 0x800493B0: sub.s       $f26, $f14, $f24
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 24);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f24.fl); 
    ctx->f26.fl = ctx->f14.fl - ctx->f24.fl;
    // 0x800493B4: swc1        $f26, 0x54($sp)
    MEM_W(0X54, ctx->r29) = ctx->f26.u32l;
    // 0x800493B8: div.s       $f2, $f4, $f16
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f2.fl = DIV_S(ctx->f4.fl, ctx->f16.fl);
    // 0x800493BC: sub.s       $f6, $f2, $f12
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f6.fl = ctx->f2.fl - ctx->f12.fl;
    // 0x800493C0: mul.s       $f8, $f6, $f28
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 28);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f28.fl); 
    ctx->f8.fl = MUL_S(ctx->f6.fl, ctx->f28.fl);
    // 0x800493C4: add.s       $f4, $f8, $f12
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f4.fl = ctx->f8.fl + ctx->f12.fl;
    // 0x800493C8: sub.s       $f0, $f4, $f30
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 30);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f30.fl); 
    ctx->f0.fl = ctx->f4.fl - ctx->f30.fl;
    // 0x800493CC: sub.s       $f4, $f10, $f22
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f4.fl = ctx->f10.fl - ctx->f22.fl;
    // 0x800493D0: mul.s       $f6, $f0, $f24
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 24);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f24.fl); 
    ctx->f6.fl = MUL_S(ctx->f0.fl, ctx->f24.fl);
    // 0x800493D4: lwc1        $f10, 0x54($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0X54);
    // 0x800493D8: mul.s       $f8, $f30, $f26
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 30);
    CHECK_FR(ctx, 26);
    NAN_CHECK(ctx->f30.fl); NAN_CHECK(ctx->f26.fl); 
    ctx->f8.fl = MUL_S(ctx->f30.fl, ctx->f26.fl);
    // 0x800493DC: swc1        $f4, 0x50($sp)
    MEM_W(0X50, ctx->r29) = ctx->f4.u32l;
    // 0x800493E0: sub.s       $f18, $f6, $f8
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f18.fl = ctx->f6.fl - ctx->f8.fl;
    // 0x800493E4: mul.s       $f6, $f4, $f30
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 30);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f30.fl); 
    ctx->f6.fl = MUL_S(ctx->f4.fl, ctx->f30.fl);
    // 0x800493E8: nop

    // 0x800493EC: mul.s       $f8, $f22, $f0
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f8.fl = MUL_S(ctx->f22.fl, ctx->f0.fl);
    // 0x800493F0: sub.s       $f20, $f6, $f8
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f20.fl = ctx->f6.fl - ctx->f8.fl;
    // 0x800493F4: mul.s       $f6, $f10, $f22
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f6.fl = MUL_S(ctx->f10.fl, ctx->f22.fl);
    // 0x800493F8: nop

    // 0x800493FC: mul.s       $f8, $f24, $f4
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f24.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f8.fl = MUL_S(ctx->f24.fl, ctx->f4.fl);
    // 0x80049400: sub.s       $f26, $f6, $f8
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f26.fl = ctx->f6.fl - ctx->f8.fl;
    // 0x80049404: mul.s       $f10, $f18, $f18
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f10.fl = MUL_S(ctx->f18.fl, ctx->f18.fl);
    // 0x80049408: nop

    // 0x8004940C: mul.s       $f4, $f20, $f20
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f4.fl = MUL_S(ctx->f20.fl, ctx->f20.fl);
    // 0x80049410: add.s       $f6, $f10, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = ctx->f10.fl + ctx->f4.fl;
    // 0x80049414: mul.s       $f8, $f26, $f26
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 26);
    NAN_CHECK(ctx->f26.fl); NAN_CHECK(ctx->f26.fl); 
    ctx->f8.fl = MUL_S(ctx->f26.fl, ctx->f26.fl);
    // 0x80049418: mtc1        $zero, $f10
    ctx->f10.u32l = 0;
    // 0x8004941C: add.s       $f12, $f6, $f8
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f12.fl = ctx->f6.fl + ctx->f8.fl;
    // 0x80049420: c.eq.s      $f10, $f12
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 12);
    c1cs = ctx->f10.fl == ctx->f12.fl;
    // 0x80049424: nop

    // 0x80049428: bc1t        L_800496EC
    if (c1cs) {
        // 0x8004942C: nop
    
            goto L_800496EC;
    }
    // 0x8004942C: nop

    // 0x80049430: sw          $a0, 0x90($sp)
    MEM_W(0X90, ctx->r29) = ctx->r4;
    // 0x80049434: sw          $a1, 0x94($sp)
    MEM_W(0X94, ctx->r29) = ctx->r5;
    // 0x80049438: sw          $a2, 0x98($sp)
    MEM_W(0X98, ctx->r29) = ctx->r6;
    // 0x8004943C: jal         0x800C7010
    // 0x80049440: swc1        $f18, 0x78($sp)
    MEM_W(0X78, ctx->r29) = ctx->f18.u32l;
    _nsqrtf(rdram, ctx);
        goto after_1;
    // 0x80049440: swc1        $f18, 0x78($sp)
    MEM_W(0X78, ctx->r29) = ctx->f18.u32l;
    after_1:
    // 0x80049444: lui         $at, 0x4780
    ctx->r1 = S32(0X4780 << 16);
    // 0x80049448: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
    // 0x8004944C: lwc1        $f18, 0x78($sp)
    ctx->f18.u32l = MEM_W(ctx->r29, 0X78);
    // 0x80049450: sub.s       $f2, $f30, $f26
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 30);
    CHECK_FR(ctx, 26);
    NAN_CHECK(ctx->f30.fl); NAN_CHECK(ctx->f26.fl); 
    ctx->f2.fl = ctx->f30.fl - ctx->f26.fl;
    // 0x80049454: lw          $a2, 0x98($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X98);
    // 0x80049458: lw          $a0, 0x90($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X90);
    // 0x8004945C: div.s       $f14, $f16, $f0
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f14.fl = DIV_S(ctx->f16.fl, ctx->f0.fl);
    // 0x80049460: lw          $a1, 0x94($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X94);
    // 0x80049464: lui         $t0, 0xFFFF
    ctx->r8 = S32(0XFFFF << 16);
    // 0x80049468: sub.s       $f12, $f24, $f20
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f24.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f12.fl = ctx->f24.fl - ctx->f20.fl;
    // 0x8004946C: mul.s       $f4, $f18, $f14
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f4.fl = MUL_S(ctx->f18.fl, ctx->f14.fl);
    // 0x80049470: trunc.w.s   $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.u32l = TRUNC_W_S(ctx->f4.fl);
    // 0x80049474: mul.s       $f8, $f20, $f14
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f8.fl = MUL_S(ctx->f20.fl, ctx->f14.fl);
    // 0x80049478: nop

    // 0x8004947C: mul.s       $f4, $f26, $f14
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f26.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f4.fl = MUL_S(ctx->f26.fl, ctx->f14.fl);
    // 0x80049480: mfc1        $v0, $f6
    ctx->r2 = (int32_t)ctx->f6.u32l;
    // 0x80049484: nop

    // 0x80049488: and         $t2, $v0, $t0
    ctx->r10 = ctx->r2 & ctx->r8;
    // 0x8004948C: sll         $t8, $v0, 16
    ctx->r24 = S32(ctx->r2 << 16);
    // 0x80049490: trunc.w.s   $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.u32l = TRUNC_W_S(ctx->f8.fl);
    // 0x80049494: mul.s       $f8, $f2, $f20
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f8.fl = MUL_S(ctx->f2.fl, ctx->f20.fl);
    // 0x80049498: mfc1        $v1, $f10
    ctx->r3 = (int32_t)ctx->f10.u32l;
    // 0x8004949C: mul.s       $f10, $f26, $f12
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f26.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f10.fl = MUL_S(ctx->f26.fl, ctx->f12.fl);
    // 0x800494A0: andi        $t3, $v1, 0xFFFF
    ctx->r11 = ctx->r3 & 0XFFFF;
    // 0x800494A4: srl         $t4, $v1, 16
    ctx->r12 = S32(U32(ctx->r3) >> 16);
    // 0x800494A8: or          $t7, $t2, $t4
    ctx->r15 = ctx->r10 | ctx->r12;
    // 0x800494AC: or          $t9, $t8, $t3
    ctx->r25 = ctx->r24 | ctx->r11;
    // 0x800494B0: trunc.w.s   $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.u32l = TRUNC_W_S(ctx->f4.fl);
    // 0x800494B4: sw          $t7, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r15;
    // 0x800494B8: sw          $t9, 0x20($a2)
    MEM_W(0X20, ctx->r6) = ctx->r25;
    // 0x800494BC: sub.s       $f24, $f8, $f10
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f24.fl = ctx->f8.fl - ctx->f10.fl;
    // 0x800494C0: mfc1        $a3, $f6
    ctx->r7 = (int32_t)ctx->f6.u32l;
    // 0x800494C4: sub.s       $f6, $f22, $f18
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f6.fl = ctx->f22.fl - ctx->f18.fl;
    // 0x800494C8: and         $t6, $a3, $t0
    ctx->r14 = ctx->r7 & ctx->r8;
    // 0x800494CC: sll         $t2, $a3, 16
    ctx->r10 = S32(ctx->r7 << 16);
    // 0x800494D0: sw          $t6, 0x4($a2)
    MEM_W(0X4, ctx->r6) = ctx->r14;
    // 0x800494D4: sw          $t2, 0x24($a2)
    MEM_W(0X24, ctx->r6) = ctx->r10;
    // 0x800494D8: swc1        $f6, 0x4C($sp)
    MEM_W(0X4C, ctx->r29) = ctx->f6.u32l;
    // 0x800494DC: lwc1        $f8, 0x4C($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X4C);
    // 0x800494E0: swc1        $f12, 0x54($sp)
    MEM_W(0X54, ctx->r29) = ctx->f12.u32l;
    // 0x800494E4: swc1        $f24, 0x60($sp)
    MEM_W(0X60, ctx->r29) = ctx->f24.u32l;
    // 0x800494E8: mul.s       $f10, $f8, $f26
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 26);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f26.fl); 
    ctx->f10.fl = MUL_S(ctx->f8.fl, ctx->f26.fl);
    // 0x800494EC: swc1        $f24, 0x50($sp)
    MEM_W(0X50, ctx->r29) = ctx->f24.u32l;
    // 0x800494F0: mul.s       $f6, $f18, $f2
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f6.fl = MUL_S(ctx->f18.fl, ctx->f2.fl);
    // 0x800494F4: sub.s       $f14, $f10, $f6
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f14.fl = ctx->f10.fl - ctx->f6.fl;
    // 0x800494F8: lwc1        $f6, 0x54($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X54);
    // 0x800494FC: mul.s       $f10, $f6, $f18
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f10.fl = MUL_S(ctx->f6.fl, ctx->f18.fl);
    // 0x80049500: swc1        $f14, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->f14.u32l;
    // 0x80049504: swc1        $f14, 0x5C($sp)
    MEM_W(0X5C, ctx->r29) = ctx->f14.u32l;
    // 0x80049508: mul.s       $f4, $f20, $f8
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f4.fl = MUL_S(ctx->f20.fl, ctx->f8.fl);
    // 0x8004950C: sub.s       $f22, $f10, $f4
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f22.fl = ctx->f10.fl - ctx->f4.fl;
    // 0x80049510: mul.s       $f6, $f24, $f24
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 24);
    NAN_CHECK(ctx->f24.fl); NAN_CHECK(ctx->f24.fl); 
    ctx->f6.fl = MUL_S(ctx->f24.fl, ctx->f24.fl);
    // 0x80049514: nop

    // 0x80049518: mul.s       $f8, $f14, $f14
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f8.fl = MUL_S(ctx->f14.fl, ctx->f14.fl);
    // 0x8004951C: add.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = ctx->f6.fl + ctx->f8.fl;
    // 0x80049520: mul.s       $f4, $f22, $f22
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f4.fl = MUL_S(ctx->f22.fl, ctx->f22.fl);
    // 0x80049524: mtc1        $zero, $f6
    ctx->f6.u32l = 0;
    // 0x80049528: add.s       $f12, $f10, $f4
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f12.fl = ctx->f10.fl + ctx->f4.fl;
    // 0x8004952C: c.eq.s      $f6, $f12
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 12);
    c1cs = ctx->f6.fl == ctx->f12.fl;
    // 0x80049530: nop

    // 0x80049534: bc1t        L_800496EC
    if (c1cs) {
        // 0x80049538: nop
    
            goto L_800496EC;
    }
    // 0x80049538: nop

    // 0x8004953C: sw          $a0, 0x90($sp)
    MEM_W(0X90, ctx->r29) = ctx->r4;
    // 0x80049540: sw          $a1, 0x94($sp)
    MEM_W(0X94, ctx->r29) = ctx->r5;
    // 0x80049544: jal         0x800C7010
    // 0x80049548: sw          $a2, 0x98($sp)
    MEM_W(0X98, ctx->r29) = ctx->r6;
    _nsqrtf(rdram, ctx);
        goto after_2;
    // 0x80049548: sw          $a2, 0x98($sp)
    MEM_W(0X98, ctx->r29) = ctx->r6;
    after_2:
    // 0x8004954C: lui         $at, 0x4780
    ctx->r1 = S32(0X4780 << 16);
    // 0x80049550: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
    // 0x80049554: lwc1        $f8, 0x60($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X60);
    // 0x80049558: lwc1        $f6, 0x5C($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X5C);
    // 0x8004955C: div.s       $f14, $f16, $f0
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f14.fl = DIV_S(ctx->f16.fl, ctx->f0.fl);
    // 0x80049560: lw          $a2, 0x98($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X98);
    // 0x80049564: lw          $a0, 0x90($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X90);
    // 0x80049568: lw          $a1, 0x94($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X94);
    // 0x8004956C: lui         $t0, 0xFFFF
    ctx->r8 = S32(0XFFFF << 16);
    // 0x80049570: mul.s       $f10, $f8, $f14
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f10.fl = MUL_S(ctx->f8.fl, ctx->f14.fl);
    // 0x80049574: trunc.w.s   $f4, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    ctx->f4.u32l = TRUNC_W_S(ctx->f10.fl);
    // 0x80049578: mul.s       $f8, $f6, $f14
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f8.fl = MUL_S(ctx->f6.fl, ctx->f14.fl);
    // 0x8004957C: mfc1        $a3, $f4
    ctx->r7 = (int32_t)ctx->f4.u32l;
    // 0x80049580: mul.s       $f4, $f22, $f14
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f4.fl = MUL_S(ctx->f22.fl, ctx->f14.fl);
    // 0x80049584: and         $t5, $a3, $t0
    ctx->r13 = ctx->r7 & ctx->r8;
    // 0x80049588: sll         $t2, $a3, 16
    ctx->r10 = S32(ctx->r7 << 16);
    // 0x8004958C: trunc.w.s   $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.u32l = TRUNC_W_S(ctx->f8.fl);
    // 0x80049590: trunc.w.s   $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.u32l = TRUNC_W_S(ctx->f4.fl);
    // 0x80049594: mfc1        $v0, $f10
    ctx->r2 = (int32_t)ctx->f10.u32l;
    // 0x80049598: mfc1        $v1, $f6
    ctx->r3 = (int32_t)ctx->f6.u32l;
    // 0x8004959C: srl         $t6, $v0, 16
    ctx->r14 = S32(U32(ctx->r2) >> 16);
    // 0x800495A0: or          $t8, $t5, $t6
    ctx->r24 = ctx->r13 | ctx->r14;
    // 0x800495A4: andi        $t4, $v0, 0xFFFF
    ctx->r12 = ctx->r2 & 0XFFFF;
    // 0x800495A8: or          $t7, $t2, $t4
    ctx->r15 = ctx->r10 | ctx->r12;
    // 0x800495AC: and         $t9, $v1, $t0
    ctx->r25 = ctx->r3 & ctx->r8;
    // 0x800495B0: sll         $t5, $v1, 16
    ctx->r13 = S32(ctx->r3 << 16);
    // 0x800495B4: sw          $t8, 0x10($a2)
    MEM_W(0X10, ctx->r6) = ctx->r24;
    // 0x800495B8: sw          $t9, 0x14($a2)
    MEM_W(0X14, ctx->r6) = ctx->r25;
    // 0x800495BC: sw          $t7, 0x30($a2)
    MEM_W(0X30, ctx->r6) = ctx->r15;
    // 0x800495C0: sw          $t5, 0x34($a2)
    MEM_W(0X34, ctx->r6) = ctx->r13;
    // 0x800495C4: lh          $t8, 0x18($a0)
    ctx->r24 = MEM_H(ctx->r4, 0X18);
    // 0x800495C8: lh          $t4, 0x18($a1)
    ctx->r12 = MEM_H(ctx->r5, 0X18);
    // 0x800495CC: lhu         $t6, 0x38($a0)
    ctx->r14 = MEM_HU(ctx->r4, 0X38);
    // 0x800495D0: lhu         $t2, 0x38($a1)
    ctx->r10 = MEM_HU(ctx->r5, 0X38);
    // 0x800495D4: sll         $t3, $t8, 16
    ctx->r11 = S32(ctx->r24 << 16);
    // 0x800495D8: sll         $t7, $t4, 16
    ctx->r15 = S32(ctx->r12 << 16);
    // 0x800495DC: or          $t9, $t6, $t3
    ctx->r25 = ctx->r14 | ctx->r11;
    // 0x800495E0: or          $t5, $t2, $t7
    ctx->r13 = ctx->r10 | ctx->r15;
    // 0x800495E4: mtc1        $t9, $f8
    ctx->f8.u32l = ctx->r25;
    // 0x800495E8: mtc1        $t5, $f4
    ctx->f4.u32l = ctx->r13;
    // 0x800495EC: lh          $t3, 0x1A($a0)
    ctx->r11 = MEM_H(ctx->r4, 0X1A);
    // 0x800495F0: cvt.s.w     $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.fl = CVT_S_W(ctx->f8.u32l);
    // 0x800495F4: lh          $t7, 0x1A($a1)
    ctx->r15 = MEM_H(ctx->r5, 0X1A);
    // 0x800495F8: lhu         $t6, 0x3A($a0)
    ctx->r14 = MEM_HU(ctx->r4, 0X3A);
    // 0x800495FC: lhu         $t2, 0x3A($a1)
    ctx->r10 = MEM_HU(ctx->r5, 0X3A);
    // 0x80049600: sll         $t9, $t3, 16
    ctx->r25 = S32(ctx->r11 << 16);
    // 0x80049604: cvt.s.w     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
    // 0x80049608: sll         $t5, $t7, 16
    ctx->r13 = S32(ctx->r15 << 16);
    // 0x8004960C: or          $t4, $t6, $t9
    ctx->r12 = ctx->r14 | ctx->r25;
    // 0x80049610: or          $t8, $t2, $t5
    ctx->r24 = ctx->r10 | ctx->r13;
    // 0x80049614: lh          $t9, 0x1C($a0)
    ctx->r25 = MEM_H(ctx->r4, 0X1C);
    // 0x80049618: div.s       $f12, $f10, $f16
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f12.fl = DIV_S(ctx->f10.fl, ctx->f16.fl);
    // 0x8004961C: lh          $t5, 0x1C($a1)
    ctx->r13 = MEM_H(ctx->r5, 0X1C);
    // 0x80049620: lhu         $t6, 0x3C($a0)
    ctx->r14 = MEM_HU(ctx->r4, 0X3C);
    // 0x80049624: lhu         $t2, 0x3C($a1)
    ctx->r10 = MEM_HU(ctx->r5, 0X3C);
    // 0x80049628: div.s       $f2, $f6, $f16
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f2.fl = DIV_S(ctx->f6.fl, ctx->f16.fl);
    // 0x8004962C: sub.s       $f8, $f2, $f12
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f8.fl = ctx->f2.fl - ctx->f12.fl;
    // 0x80049630: mul.s       $f10, $f8, $f28
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 28);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f28.fl); 
    ctx->f10.fl = MUL_S(ctx->f8.fl, ctx->f28.fl);
    // 0x80049634: add.s       $f4, $f10, $f12
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f4.fl = ctx->f10.fl + ctx->f12.fl;
    // 0x80049638: mtc1        $t4, $f10
    ctx->f10.u32l = ctx->r12;
    // 0x8004963C: sll         $t4, $t9, 16
    ctx->r12 = S32(ctx->r25 << 16);
    // 0x80049640: or          $t7, $t6, $t4
    ctx->r15 = ctx->r14 | ctx->r12;
    // 0x80049644: mul.s       $f6, $f4, $f16
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f6.fl = MUL_S(ctx->f4.fl, ctx->f16.fl);
    // 0x80049648: cvt.s.w     $f4, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    ctx->f4.fl = CVT_S_W(ctx->f10.u32l);
    // 0x8004964C: trunc.w.s   $f8, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    ctx->f8.u32l = TRUNC_W_S(ctx->f6.fl);
    // 0x80049650: mtc1        $t8, $f6
    ctx->f6.u32l = ctx->r24;
    // 0x80049654: sll         $t8, $t5, 16
    ctx->r24 = S32(ctx->r13 << 16);
    // 0x80049658: div.s       $f12, $f4, $f16
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f12.fl = DIV_S(ctx->f4.fl, ctx->f16.fl);
    // 0x8004965C: mfc1        $t1, $f8
    ctx->r9 = (int32_t)ctx->f8.u32l;
    // 0x80049660: or          $t3, $t2, $t8
    ctx->r11 = ctx->r10 | ctx->r24;
    // 0x80049664: cvt.s.w     $f8, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    ctx->f8.fl = CVT_S_W(ctx->f6.u32l);
    // 0x80049668: and         $t9, $t1, $t0
    ctx->r25 = ctx->r9 & ctx->r8;
    // 0x8004966C: sll         $t8, $t1, 16
    ctx->r24 = S32(ctx->r9 << 16);
    // 0x80049670: div.s       $f2, $f8, $f16
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f2.fl = DIV_S(ctx->f8.fl, ctx->f16.fl);
    // 0x80049674: sub.s       $f10, $f2, $f12
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f10.fl = ctx->f2.fl - ctx->f12.fl;
    // 0x80049678: mul.s       $f4, $f10, $f28
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 28);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f28.fl); 
    ctx->f4.fl = MUL_S(ctx->f10.fl, ctx->f28.fl);
    // 0x8004967C: add.s       $f6, $f4, $f12
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f6.fl = ctx->f4.fl + ctx->f12.fl;
    // 0x80049680: mtc1        $t7, $f4
    ctx->f4.u32l = ctx->r15;
    // 0x80049684: mul.s       $f8, $f6, $f16
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f8.fl = MUL_S(ctx->f6.fl, ctx->f16.fl);
    // 0x80049688: cvt.s.w     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
    // 0x8004968C: trunc.w.s   $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.u32l = TRUNC_W_S(ctx->f8.fl);
    // 0x80049690: mtc1        $t3, $f8
    ctx->f8.u32l = ctx->r11;
    // 0x80049694: div.s       $f12, $f6, $f16
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f12.fl = DIV_S(ctx->f6.fl, ctx->f16.fl);
    // 0x80049698: mfc1        $v0, $f10
    ctx->r2 = (int32_t)ctx->f10.u32l;
    // 0x8004969C: cvt.s.w     $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.fl = CVT_S_W(ctx->f8.u32l);
    // 0x800496A0: srl         $t6, $v0, 16
    ctx->r14 = S32(U32(ctx->r2) >> 16);
    // 0x800496A4: or          $t4, $t9, $t6
    ctx->r12 = ctx->r25 | ctx->r14;
    // 0x800496A8: andi        $t3, $v0, 0xFFFF
    ctx->r11 = ctx->r2 & 0XFFFF;
    // 0x800496AC: or          $t9, $t8, $t3
    ctx->r25 = ctx->r24 | ctx->r11;
    // 0x800496B0: sw          $t4, 0x18($a2)
    MEM_W(0X18, ctx->r6) = ctx->r12;
    // 0x800496B4: sw          $t9, 0x38($a2)
    MEM_W(0X38, ctx->r6) = ctx->r25;
    // 0x800496B8: div.s       $f2, $f10, $f16
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f2.fl = DIV_S(ctx->f10.fl, ctx->f16.fl);
    // 0x800496BC: sub.s       $f4, $f2, $f12
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f4.fl = ctx->f2.fl - ctx->f12.fl;
    // 0x800496C0: mul.s       $f6, $f4, $f28
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 28);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f28.fl); 
    ctx->f6.fl = MUL_S(ctx->f4.fl, ctx->f28.fl);
    // 0x800496C4: add.s       $f8, $f6, $f12
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f8.fl = ctx->f6.fl + ctx->f12.fl;
    // 0x800496C8: mul.s       $f10, $f8, $f16
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f10.fl = MUL_S(ctx->f8.fl, ctx->f16.fl);
    // 0x800496CC: trunc.w.s   $f4, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    ctx->f4.u32l = TRUNC_W_S(ctx->f10.fl);
    // 0x800496D0: mfc1        $v1, $f4
    ctx->r3 = (int32_t)ctx->f4.u32l;
    // 0x800496D4: nop

    // 0x800496D8: and         $t5, $v1, $t0
    ctx->r13 = ctx->r3 & ctx->r8;
    // 0x800496DC: ori         $t2, $t5, 0x1
    ctx->r10 = ctx->r13 | 0X1;
    // 0x800496E0: sll         $t6, $v1, 16
    ctx->r14 = S32(ctx->r3 << 16);
    // 0x800496E4: sw          $t2, 0x1C($a2)
    MEM_W(0X1C, ctx->r6) = ctx->r10;
    // 0x800496E8: sw          $t6, 0x3C($a2)
    MEM_W(0X3C, ctx->r6) = ctx->r14;
L_800496EC:
    // 0x800496EC: lw          $ra, 0x44($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X44);
    // 0x800496F0: ldc1        $f20, 0x10($sp)
    CHECK_FR(ctx, 20);
    ctx->f20.u64 = LD(ctx->r29, 0X10);
    // 0x800496F4: ldc1        $f22, 0x18($sp)
    CHECK_FR(ctx, 22);
    ctx->f22.u64 = LD(ctx->r29, 0X18);
    // 0x800496F8: ldc1        $f24, 0x20($sp)
    CHECK_FR(ctx, 24);
    ctx->f24.u64 = LD(ctx->r29, 0X20);
    // 0x800496FC: ldc1        $f26, 0x28($sp)
    CHECK_FR(ctx, 26);
    ctx->f26.u64 = LD(ctx->r29, 0X28);
    // 0x80049700: ldc1        $f28, 0x30($sp)
    CHECK_FR(ctx, 28);
    ctx->f28.u64 = LD(ctx->r29, 0X30);
    // 0x80049704: ldc1        $f30, 0x38($sp)
    CHECK_FR(ctx, 30);
    ctx->f30.u64 = LD(ctx->r29, 0X38);
    // 0x80049708: jr          $ra
    // 0x8004970C: addiu       $sp, $sp, 0x90
    ctx->r29 = ADD32(ctx->r29, 0X90);
    return;
    // 0x8004970C: addiu       $sp, $sp, 0x90
    ctx->r29 = ADD32(ctx->r29, 0X90);
;}
RECOMP_FUNC void func_80049710(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x80049710: addiu       $sp, $sp, -0x30
    ctx->r29 = ADD32(ctx->r29, -0X30);
    // 0x80049714: sdc1        $f22, 0x18($sp)
    CHECK_FR(ctx, 22);
    SD(ctx->f22.u64, 0X18, ctx->r29);
    // 0x80049718: mtc1        $a2, $f22
    ctx->f22.u32l = ctx->r6;
    // 0x8004971C: lwc1        $f12, 0x50($sp)
    ctx->f12.u32l = MEM_W(ctx->r29, 0X50);
    // 0x80049720: sdc1        $f24, 0x20($sp)
    CHECK_FR(ctx, 24);
    SD(ctx->f24.u64, 0X20, ctx->r29);
    // 0x80049724: mtc1        $a3, $f24
    ctx->f24.u32l = ctx->r7;
    // 0x80049728: mul.s       $f4, $f22, $f12
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f4.fl = MUL_S(ctx->f22.fl, ctx->f12.fl);
    // 0x8004972C: lwc1        $f14, 0x54($sp)
    ctx->f14.u32l = MEM_W(ctx->r29, 0X54);
    // 0x80049730: sdc1        $f20, 0x10($sp)
    CHECK_FR(ctx, 20);
    SD(ctx->f20.u64, 0X10, ctx->r29);
    // 0x80049734: lwc1        $f20, 0x58($sp)
    ctx->f20.u32l = MEM_W(ctx->r29, 0X58);
    // 0x80049738: mul.s       $f6, $f24, $f14
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f24.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f6.fl = MUL_S(ctx->f24.fl, ctx->f14.fl);
    // 0x8004973C: lwc1        $f10, 0x40($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0X40);
    // 0x80049740: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x80049744: or          $a3, $a0, $zero
    ctx->r7 = ctx->r4 | 0;
    // 0x80049748: mul.s       $f18, $f10, $f20
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f18.fl = MUL_S(ctx->f10.fl, ctx->f20.fl);
    // 0x8004974C: ldc1        $f10, -0x6DB8($at)
    CHECK_FR(ctx, 10);
    ctx->f10.u64 = LD(ctx->r1, -0X6DB8);
    // 0x80049750: sw          $ra, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r31;
    // 0x80049754: sw          $a0, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r4;
    // 0x80049758: sw          $a1, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r5;
    // 0x8004975C: add.s       $f8, $f4, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = ctx->f4.fl + ctx->f6.fl;
    // 0x80049760: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x80049764: add.s       $f0, $f8, $f18
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f0.fl = ctx->f8.fl + ctx->f18.fl;
    // 0x80049768: mul.s       $f4, $f0, $f0
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f4.fl = MUL_S(ctx->f0.fl, ctx->f0.fl);
    // 0x8004976C: cvt.d.s     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f4.fl); 
    ctx->f6.d = CVT_D_S(ctx->f4.fl);
    // 0x80049770: c.lt.d      $f6, $f10
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    c1cs = ctx->f6.d < ctx->f10.d;
    // 0x80049774: nop

    // 0x80049778: bc1tl       L_80049890
    if (c1cs) {
        // 0x8004977C: lw          $ra, 0x2C($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X2C);
            goto L_80049890;
    }
    goto skip_0;
    // 0x8004977C: lw          $ra, 0x2C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X2C);
    skip_0:
    // 0x80049780: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
    // 0x80049784: lui         $at, 0xBF80
    ctx->r1 = S32(0XBF80 << 16);
    // 0x80049788: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x8004978C: lwc1        $f4, 0x44($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X44);
    // 0x80049790: neg.s       $f18, $f12
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f12.fl); 
    ctx->f18.fl = -ctx->f12.fl;
    // 0x80049794: div.s       $f2, $f8, $f0
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f2.fl = DIV_S(ctx->f8.fl, ctx->f0.fl);
    // 0x80049798: lwc1        $f10, 0x48($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0X48);
    // 0x8004979C: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x800497A0: or          $a0, $a1, $zero
    ctx->r4 = ctx->r5 | 0;
    // 0x800497A4: mul.s       $f6, $f18, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = MUL_S(ctx->f18.fl, ctx->f4.fl);
    // 0x800497A8: lwc1        $f4, 0x4C($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X4C);
    // 0x800497AC: mul.s       $f8, $f14, $f10
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f8.fl = MUL_S(ctx->f14.fl, ctx->f10.fl);
    // 0x800497B0: sub.s       $f18, $f6, $f8
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f18.fl = ctx->f6.fl - ctx->f8.fl;
    // 0x800497B4: mul.s       $f10, $f20, $f4
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f10.fl = MUL_S(ctx->f20.fl, ctx->f4.fl);
    // 0x800497B8: sub.s       $f6, $f18, $f10
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f6.fl = ctx->f18.fl - ctx->f10.fl;
    // 0x800497BC: mul.s       $f0, $f6, $f2
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f0.fl = MUL_S(ctx->f6.fl, ctx->f2.fl);
    // 0x800497C0: nop

    // 0x800497C4: mul.s       $f12, $f12, $f2
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f12.fl = MUL_S(ctx->f12.fl, ctx->f2.fl);
    // 0x800497C8: nop

    // 0x800497CC: mul.s       $f14, $f14, $f2
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f14.fl = MUL_S(ctx->f14.fl, ctx->f2.fl);
    // 0x800497D0: nop

    // 0x800497D4: mul.s       $f20, $f20, $f2
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f20.fl = MUL_S(ctx->f20.fl, ctx->f2.fl);
    // 0x800497D8: mtc1        $zero, $f2
    ctx->f2.u32l = 0;
    // 0x800497DC: mul.s       $f8, $f12, $f22
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f8.fl = MUL_S(ctx->f12.fl, ctx->f22.fl);
    // 0x800497E0: add.s       $f4, $f8, $f16
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f4.fl = ctx->f8.fl + ctx->f16.fl;
    // 0x800497E4: mul.s       $f18, $f12, $f24
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 24);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f24.fl); 
    ctx->f18.fl = MUL_S(ctx->f12.fl, ctx->f24.fl);
    // 0x800497E8: swc1        $f4, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->f4.u32l;
    // 0x800497EC: swc1        $f18, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->f18.u32l;
    // 0x800497F0: lwc1        $f10, 0x40($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0X40);
    // 0x800497F4: mul.s       $f6, $f12, $f10
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f6.fl = MUL_S(ctx->f12.fl, ctx->f10.fl);
    // 0x800497F8: nop

    // 0x800497FC: mul.s       $f8, $f14, $f22
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f8.fl = MUL_S(ctx->f14.fl, ctx->f22.fl);
    // 0x80049800: nop

    // 0x80049804: mul.s       $f4, $f14, $f24
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 24);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f24.fl); 
    ctx->f4.fl = MUL_S(ctx->f14.fl, ctx->f24.fl);
    // 0x80049808: swc1        $f6, 0x8($a1)
    MEM_W(0X8, ctx->r5) = ctx->f6.u32l;
    // 0x8004980C: swc1        $f8, 0x10($a1)
    MEM_W(0X10, ctx->r5) = ctx->f8.u32l;
    // 0x80049810: add.s       $f18, $f4, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f18.fl = ctx->f4.fl + ctx->f16.fl;
    // 0x80049814: swc1        $f18, 0x14($a1)
    MEM_W(0X14, ctx->r5) = ctx->f18.u32l;
    // 0x80049818: lwc1        $f10, 0x40($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0X40);
    // 0x8004981C: mul.s       $f6, $f14, $f10
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f6.fl = MUL_S(ctx->f14.fl, ctx->f10.fl);
    // 0x80049820: nop

    // 0x80049824: mul.s       $f8, $f20, $f22
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f8.fl = MUL_S(ctx->f20.fl, ctx->f22.fl);
    // 0x80049828: nop

    // 0x8004982C: mul.s       $f4, $f20, $f24
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 24);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f24.fl); 
    ctx->f4.fl = MUL_S(ctx->f20.fl, ctx->f24.fl);
    // 0x80049830: swc1        $f6, 0x18($a1)
    MEM_W(0X18, ctx->r5) = ctx->f6.u32l;
    // 0x80049834: swc1        $f8, 0x20($a1)
    MEM_W(0X20, ctx->r5) = ctx->f8.u32l;
    // 0x80049838: swc1        $f4, 0x24($a1)
    MEM_W(0X24, ctx->r5) = ctx->f4.u32l;
    // 0x8004983C: lwc1        $f18, 0x40($sp)
    ctx->f18.u32l = MEM_W(ctx->r29, 0X40);
    // 0x80049840: mul.s       $f10, $f20, $f18
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f10.fl = MUL_S(ctx->f20.fl, ctx->f18.fl);
    // 0x80049844: nop

    // 0x80049848: mul.s       $f8, $f0, $f22
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f8.fl = MUL_S(ctx->f0.fl, ctx->f22.fl);
    // 0x8004984C: nop

    // 0x80049850: mul.s       $f4, $f0, $f24
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 24);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f24.fl); 
    ctx->f4.fl = MUL_S(ctx->f0.fl, ctx->f24.fl);
    // 0x80049854: add.s       $f6, $f10, $f16
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f6.fl = ctx->f10.fl + ctx->f16.fl;
    // 0x80049858: swc1        $f8, 0x30($a1)
    MEM_W(0X30, ctx->r5) = ctx->f8.u32l;
    // 0x8004985C: swc1        $f6, 0x28($a1)
    MEM_W(0X28, ctx->r5) = ctx->f6.u32l;
    // 0x80049860: swc1        $f4, 0x34($a1)
    MEM_W(0X34, ctx->r5) = ctx->f4.u32l;
    // 0x80049864: lwc1        $f18, 0x40($sp)
    ctx->f18.u32l = MEM_W(ctx->r29, 0X40);
    // 0x80049868: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x8004986C: swc1        $f2, 0xC($a1)
    MEM_W(0XC, ctx->r5) = ctx->f2.u32l;
    // 0x80049870: mul.s       $f10, $f0, $f18
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f10.fl = MUL_S(ctx->f0.fl, ctx->f18.fl);
    // 0x80049874: swc1        $f2, 0x1C($a1)
    MEM_W(0X1C, ctx->r5) = ctx->f2.u32l;
    // 0x80049878: swc1        $f2, 0x2C($a1)
    MEM_W(0X2C, ctx->r5) = ctx->f2.u32l;
    // 0x8004987C: swc1        $f6, 0x3C($a1)
    MEM_W(0X3C, ctx->r5) = ctx->f6.u32l;
    // 0x80049880: swc1        $f10, 0x38($a1)
    MEM_W(0X38, ctx->r5) = ctx->f10.u32l;
    // 0x80049884: jal         0x80047EE0
    // 0x80049888: or          $a1, $a3, $zero
    ctx->r5 = ctx->r7 | 0;
    SysUtils_MtxFToMtx(rdram, ctx);
        goto after_0;
    // 0x80049888: or          $a1, $a3, $zero
    ctx->r5 = ctx->r7 | 0;
    after_0:
    // 0x8004988C: lw          $ra, 0x2C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X2C);
L_80049890:
    // 0x80049890: ldc1        $f20, 0x10($sp)
    CHECK_FR(ctx, 20);
    ctx->f20.u64 = LD(ctx->r29, 0X10);
    // 0x80049894: ldc1        $f22, 0x18($sp)
    CHECK_FR(ctx, 22);
    ctx->f22.u64 = LD(ctx->r29, 0X18);
    // 0x80049898: ldc1        $f24, 0x20($sp)
    CHECK_FR(ctx, 24);
    ctx->f24.u64 = LD(ctx->r29, 0X20);
    // 0x8004989C: jr          $ra
    // 0x800498A0: addiu       $sp, $sp, 0x30
    ctx->r29 = ADD32(ctx->r29, 0X30);
    return;
    // 0x800498A0: addiu       $sp, $sp, 0x30
    ctx->r29 = ADD32(ctx->r29, 0X30);
;}
RECOMP_FUNC void func_800498A4(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800498A4: addiu       $sp, $sp, -0x38
    ctx->r29 = ADD32(ctx->r29, -0X38);
    // 0x800498A8: sw          $a2, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r6;
    // 0x800498AC: lui         $at, 0x4580
    ctx->r1 = S32(0X4580 << 16);
    // 0x800498B0: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
    // 0x800498B4: lwc1        $f4, 0x40($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X40);
    // 0x800498B8: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x800498BC: lwc1        $f18, -0x6DB0($at)
    ctx->f18.u32l = MEM_W(ctx->r1, -0X6DB0);
    // 0x800498C0: mul.s       $f6, $f4, $f16
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f6.fl = MUL_S(ctx->f4.fl, ctx->f16.fl);
    // 0x800498C4: lui         $at, 0x3F00
    ctx->r1 = S32(0X3F00 << 16);
    // 0x800498C8: mtc1        $at, $f10
    ctx->f10.u32l = ctx->r1;
    // 0x800498CC: lui         $v0, 0x8015
    ctx->r2 = S32(0X8015 << 16);
    // 0x800498D0: addiu       $v0, $v0, 0x4350
    ctx->r2 = ADD32(ctx->r2, 0X4350);
    // 0x800498D4: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800498D8: sw          $a0, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r4;
    // 0x800498DC: div.s       $f8, $f6, $f18
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f8.fl = DIV_S(ctx->f6.fl, ctx->f18.fl);
    // 0x800498E0: sw          $a1, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r5;
    // 0x800498E4: sw          $a3, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r7;
    // 0x800498E8: or          $a0, $a1, $zero
    ctx->r4 = ctx->r5 | 0;
    // 0x800498EC: add.s       $f4, $f8, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f4.fl = ctx->f8.fl + ctx->f10.fl;
    // 0x800498F0: trunc.w.s   $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.u32l = TRUNC_W_S(ctx->f4.fl);
    // 0x800498F4: mfc1        $v1, $f6
    ctx->r3 = (int32_t)ctx->f6.u32l;
    // 0x800498F8: nop

    // 0x800498FC: andi        $t7, $v1, 0xFFF
    ctx->r15 = ctx->r3 & 0XFFF;
    // 0x80049900: sll         $t8, $t7, 2
    ctx->r24 = S32(ctx->r15 << 2);
    // 0x80049904: addu        $t9, $v0, $t8
    ctx->r25 = ADD32(ctx->r2, ctx->r24);
    // 0x80049908: lwc1        $f12, 0x0($t9)
    ctx->f12.u32l = MEM_W(ctx->r25, 0X0);
    // 0x8004990C: addiu       $t5, $v1, 0x400
    ctx->r13 = ADD32(ctx->r3, 0X400);
    // 0x80049910: andi        $t6, $t5, 0xFFF
    ctx->r14 = ctx->r13 & 0XFFF;
    // 0x80049914: neg.s       $f8, $f12
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f12.fl); 
    ctx->f8.fl = -ctx->f12.fl;
    // 0x80049918: sll         $t7, $t6, 2
    ctx->r15 = S32(ctx->r14 << 2);
    // 0x8004991C: swc1        $f8, 0x24($a1)
    MEM_W(0X24, ctx->r5) = ctx->f8.u32l;
    // 0x80049920: lwc1        $f10, 0x44($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0X44);
    // 0x80049924: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x80049928: addu        $t8, $v0, $t7
    ctx->r24 = ADD32(ctx->r2, ctx->r15);
    // 0x8004992C: mul.s       $f4, $f10, $f16
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f4.fl = MUL_S(ctx->f10.fl, ctx->f16.fl);
    // 0x80049930: lwc1        $f0, 0x0($t8)
    ctx->f0.u32l = MEM_W(ctx->r24, 0X0);
    // 0x80049934: div.s       $f6, $f4, $f18
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f6.fl = DIV_S(ctx->f4.fl, ctx->f18.fl);
    // 0x80049938: add.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = ctx->f6.fl + ctx->f8.fl;
    // 0x8004993C: trunc.w.s   $f4, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    ctx->f4.u32l = TRUNC_W_S(ctx->f10.fl);
    // 0x80049940: mfc1        $a3, $f4
    ctx->r7 = (int32_t)ctx->f4.u32l;
    // 0x80049944: nop

    // 0x80049948: andi        $t2, $a3, 0xFFF
    ctx->r10 = ctx->r7 & 0XFFF;
    // 0x8004994C: sll         $t3, $t2, 2
    ctx->r11 = S32(ctx->r10 << 2);
    // 0x80049950: addu        $t4, $v0, $t3
    ctx->r12 = ADD32(ctx->r2, ctx->r11);
    // 0x80049954: lwc1        $f2, 0x0($t4)
    ctx->f2.u32l = MEM_W(ctx->r12, 0X0);
    // 0x80049958: addiu       $t9, $a3, 0x400
    ctx->r25 = ADD32(ctx->r7, 0X400);
    // 0x8004995C: andi        $t1, $t9, 0xFFF
    ctx->r9 = ctx->r25 & 0XFFF;
    // 0x80049960: mul.s       $f6, $f0, $f2
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f6.fl = MUL_S(ctx->f0.fl, ctx->f2.fl);
    // 0x80049964: sll         $t2, $t1, 2
    ctx->r10 = S32(ctx->r9 << 2);
    // 0x80049968: swc1        $f2, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->f2.u32l;
    // 0x8004996C: addu        $t3, $v0, $t2
    ctx->r11 = ADD32(ctx->r2, ctx->r10);
    // 0x80049970: swc1        $f6, 0x20($a1)
    MEM_W(0X20, ctx->r5) = ctx->f6.u32l;
    // 0x80049974: lwc1        $f8, 0x0($t3)
    ctx->f8.u32l = MEM_W(ctx->r11, 0X0);
    // 0x80049978: swc1        $f8, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->f8.u32l;
    // 0x8004997C: lwc1        $f10, 0x24($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0X24);
    // 0x80049980: mul.s       $f4, $f10, $f0
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f4.fl = MUL_S(ctx->f10.fl, ctx->f0.fl);
    // 0x80049984: swc1        $f4, 0x28($a1)
    MEM_W(0X28, ctx->r5) = ctx->f4.u32l;
    // 0x80049988: lwc1        $f6, 0x48($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X48);
    // 0x8004998C: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x80049990: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x80049994: mul.s       $f8, $f6, $f16
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f8.fl = MUL_S(ctx->f6.fl, ctx->f16.fl);
    // 0x80049998: div.s       $f10, $f8, $f18
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f10.fl = DIV_S(ctx->f8.fl, ctx->f18.fl);
    // 0x8004999C: mtc1        $zero, $f18
    ctx->f18.u32l = 0;
    // 0x800499A0: add.s       $f6, $f10, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = ctx->f10.fl + ctx->f4.fl;
    // 0x800499A4: trunc.w.s   $f8, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    ctx->f8.u32l = TRUNC_W_S(ctx->f6.fl);
    // 0x800499A8: mfc1        $t0, $f8
    ctx->r8 = (int32_t)ctx->f8.u32l;
    // 0x800499AC: nop

    // 0x800499B0: andi        $t5, $t0, 0xFFF
    ctx->r13 = ctx->r8 & 0XFFF;
    // 0x800499B4: sll         $t6, $t5, 2
    ctx->r14 = S32(ctx->r13 << 2);
    // 0x800499B8: addu        $t7, $v0, $t6
    ctx->r15 = ADD32(ctx->r2, ctx->r14);
    // 0x800499BC: lwc1        $f14, 0x0($t7)
    ctx->f14.u32l = MEM_W(ctx->r15, 0X0);
    // 0x800499C0: addiu       $t8, $t0, 0x400
    ctx->r24 = ADD32(ctx->r8, 0X400);
    // 0x800499C4: andi        $t9, $t8, 0xFFF
    ctx->r25 = ctx->r24 & 0XFFF;
    // 0x800499C8: mul.s       $f10, $f14, $f0
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f10.fl = MUL_S(ctx->f14.fl, ctx->f0.fl);
    // 0x800499CC: sll         $t1, $t9, 2
    ctx->r9 = S32(ctx->r25 << 2);
    // 0x800499D0: addu        $t2, $v0, $t1
    ctx->r10 = ADD32(ctx->r2, ctx->r9);
    // 0x800499D4: swc1        $f10, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->f10.u32l;
    // 0x800499D8: lwc1        $f4, 0x0($t2)
    ctx->f4.u32l = MEM_W(ctx->r10, 0X0);
    // 0x800499DC: swc1        $f4, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->f4.u32l;
    // 0x800499E0: lwc1        $f6, 0x20($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X20);
    // 0x800499E4: mul.s       $f8, $f6, $f0
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f8.fl = MUL_S(ctx->f6.fl, ctx->f0.fl);
    // 0x800499E8: swc1        $f8, 0x14($a1)
    MEM_W(0X14, ctx->r5) = ctx->f8.u32l;
    // 0x800499EC: mul.s       $f2, $f2, $f14
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f2.fl = MUL_S(ctx->f2.fl, ctx->f14.fl);
    // 0x800499F0: lwc1        $f10, 0x24($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0X24);
    // 0x800499F4: lwc1        $f4, 0x20($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X20);
    // 0x800499F8: swc1        $f14, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->f14.u32l;
    // 0x800499FC: mul.s       $f0, $f10, $f4
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f0.fl = MUL_S(ctx->f10.fl, ctx->f4.fl);
    // 0x80049A00: swc1        $f2, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->f2.u32l;
    // 0x80049A04: mul.s       $f6, $f12, $f2
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f6.fl = MUL_S(ctx->f12.fl, ctx->f2.fl);
    // 0x80049A08: add.s       $f8, $f0, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = ctx->f0.fl + ctx->f6.fl;
    // 0x80049A0C: swc1        $f8, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->f8.u32l;
    // 0x80049A10: lwc1        $f4, 0x20($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X20);
    // 0x80049A14: lwc1        $f10, 0x30($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0X30);
    // 0x80049A18: lwc1        $f8, 0x24($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X24);
    // 0x80049A1C: lwc1        $f6, 0x2C($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X2C);
    // 0x80049A20: mul.s       $f14, $f10, $f4
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f14.fl = MUL_S(ctx->f10.fl, ctx->f4.fl);
    // 0x80049A24: nop

    // 0x80049A28: mul.s       $f16, $f6, $f8
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f16.fl = MUL_S(ctx->f6.fl, ctx->f8.fl);
    // 0x80049A2C: nop

    // 0x80049A30: mul.s       $f10, $f12, $f14
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f10.fl = MUL_S(ctx->f12.fl, ctx->f14.fl);
    // 0x80049A34: nop

    // 0x80049A38: mul.s       $f6, $f12, $f16
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f6.fl = MUL_S(ctx->f12.fl, ctx->f16.fl);
    // 0x80049A3C: sub.s       $f4, $f10, $f16
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f4.fl = ctx->f10.fl - ctx->f16.fl;
    // 0x80049A40: mul.s       $f10, $f12, $f0
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f10.fl = MUL_S(ctx->f12.fl, ctx->f0.fl);
    // 0x80049A44: sub.s       $f8, $f6, $f14
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f8.fl = ctx->f6.fl - ctx->f14.fl;
    // 0x80049A48: swc1        $f4, 0x10($a1)
    MEM_W(0X10, ctx->r5) = ctx->f4.u32l;
    // 0x80049A4C: swc1        $f8, 0x8($a1)
    MEM_W(0X8, ctx->r5) = ctx->f8.u32l;
    // 0x80049A50: lwc1        $f4, 0x1C($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X1C);
    // 0x80049A54: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x80049A58: swc1        $f18, 0x30($a1)
    MEM_W(0X30, ctx->r5) = ctx->f18.u32l;
    // 0x80049A5C: add.s       $f6, $f10, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = ctx->f10.fl + ctx->f4.fl;
    // 0x80049A60: swc1        $f18, 0x34($a1)
    MEM_W(0X34, ctx->r5) = ctx->f18.u32l;
    // 0x80049A64: swc1        $f18, 0x38($a1)
    MEM_W(0X38, ctx->r5) = ctx->f18.u32l;
    // 0x80049A68: swc1        $f18, 0xC($a1)
    MEM_W(0XC, ctx->r5) = ctx->f18.u32l;
    // 0x80049A6C: swc1        $f6, 0x18($a1)
    MEM_W(0X18, ctx->r5) = ctx->f6.u32l;
    // 0x80049A70: swc1        $f18, 0x1C($a1)
    MEM_W(0X1C, ctx->r5) = ctx->f18.u32l;
    // 0x80049A74: swc1        $f18, 0x2C($a1)
    MEM_W(0X2C, ctx->r5) = ctx->f18.u32l;
    // 0x80049A78: swc1        $f8, 0x3C($a1)
    MEM_W(0X3C, ctx->r5) = ctx->f8.u32l;
    // 0x80049A7C: jal         0x80047EE0
    // 0x80049A80: lw          $a1, 0x38($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X38);
    SysUtils_MtxFToMtx(rdram, ctx);
        goto after_0;
    // 0x80049A80: lw          $a1, 0x38($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X38);
    after_0:
    // 0x80049A84: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x80049A88: addiu       $sp, $sp, 0x38
    ctx->r29 = ADD32(ctx->r29, 0X38);
    // 0x80049A8C: jr          $ra
    // 0x80049A90: nop

    return;
    // 0x80049A90: nop

;}
RECOMP_FUNC void func_80049A94(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x80049A94: addiu       $sp, $sp, -0x38
    ctx->r29 = ADD32(ctx->r29, -0X38);
    // 0x80049A98: sw          $a2, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r6;
    // 0x80049A9C: lui         $at, 0x4580
    ctx->r1 = S32(0X4580 << 16);
    // 0x80049AA0: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
    // 0x80049AA4: lwc1        $f4, 0x40($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X40);
    // 0x80049AA8: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x80049AAC: lwc1        $f8, -0x6DAC($at)
    ctx->f8.u32l = MEM_W(ctx->r1, -0X6DAC);
    // 0x80049AB0: mul.s       $f6, $f4, $f16
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f6.fl = MUL_S(ctx->f4.fl, ctx->f16.fl);
    // 0x80049AB4: lui         $at, 0x3F00
    ctx->r1 = S32(0X3F00 << 16);
    // 0x80049AB8: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x80049ABC: lui         $v0, 0x8015
    ctx->r2 = S32(0X8015 << 16);
    // 0x80049AC0: addiu       $v0, $v0, 0x4350
    ctx->r2 = ADD32(ctx->r2, 0X4350);
    // 0x80049AC4: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x80049AC8: sw          $a0, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r4;
    // 0x80049ACC: div.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = DIV_S(ctx->f6.fl, ctx->f8.fl);
    // 0x80049AD0: sw          $a1, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r5;
    // 0x80049AD4: sw          $a3, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r7;
    // 0x80049AD8: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x80049ADC: or          $a0, $a1, $zero
    ctx->r4 = ctx->r5 | 0;
    // 0x80049AE0: add.s       $f6, $f10, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = ctx->f10.fl + ctx->f4.fl;
    // 0x80049AE4: trunc.w.s   $f8, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    ctx->f8.u32l = TRUNC_W_S(ctx->f6.fl);
    // 0x80049AE8: mfc1        $v1, $f8
    ctx->r3 = (int32_t)ctx->f8.u32l;
    // 0x80049AEC: nop

    // 0x80049AF0: andi        $t7, $v1, 0xFFF
    ctx->r15 = ctx->r3 & 0XFFF;
    // 0x80049AF4: sll         $t8, $t7, 2
    ctx->r24 = S32(ctx->r15 << 2);
    // 0x80049AF8: addu        $t9, $v0, $t8
    ctx->r25 = ADD32(ctx->r2, ctx->r24);
    // 0x80049AFC: lwc1        $f12, 0x0($t9)
    ctx->f12.u32l = MEM_W(ctx->r25, 0X0);
    // 0x80049B00: addiu       $t5, $v1, 0x400
    ctx->r13 = ADD32(ctx->r3, 0X400);
    // 0x80049B04: andi        $t6, $t5, 0xFFF
    ctx->r14 = ctx->r13 & 0XFFF;
    // 0x80049B08: neg.s       $f10, $f12
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f12.fl); 
    ctx->f10.fl = -ctx->f12.fl;
    // 0x80049B0C: sll         $t7, $t6, 2
    ctx->r15 = S32(ctx->r14 << 2);
    // 0x80049B10: swc1        $f10, 0x24($a1)
    MEM_W(0X24, ctx->r5) = ctx->f10.u32l;
    // 0x80049B14: lwc1        $f4, 0x44($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X44);
    // 0x80049B18: lwc1        $f8, -0x6DA8($at)
    ctx->f8.u32l = MEM_W(ctx->r1, -0X6DA8);
    // 0x80049B1C: lui         $at, 0x3F00
    ctx->r1 = S32(0X3F00 << 16);
    // 0x80049B20: mul.s       $f6, $f4, $f16
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f6.fl = MUL_S(ctx->f4.fl, ctx->f16.fl);
    // 0x80049B24: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x80049B28: addu        $t8, $v0, $t7
    ctx->r24 = ADD32(ctx->r2, ctx->r15);
    // 0x80049B2C: lwc1        $f0, 0x0($t8)
    ctx->f0.u32l = MEM_W(ctx->r24, 0X0);
    // 0x80049B30: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x80049B34: div.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = DIV_S(ctx->f6.fl, ctx->f8.fl);
    // 0x80049B38: add.s       $f6, $f10, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = ctx->f10.fl + ctx->f4.fl;
    // 0x80049B3C: trunc.w.s   $f8, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    ctx->f8.u32l = TRUNC_W_S(ctx->f6.fl);
    // 0x80049B40: mfc1        $a3, $f8
    ctx->r7 = (int32_t)ctx->f8.u32l;
    // 0x80049B44: nop

    // 0x80049B48: andi        $t2, $a3, 0xFFF
    ctx->r10 = ctx->r7 & 0XFFF;
    // 0x80049B4C: sll         $t3, $t2, 2
    ctx->r11 = S32(ctx->r10 << 2);
    // 0x80049B50: addu        $t4, $v0, $t3
    ctx->r12 = ADD32(ctx->r2, ctx->r11);
    // 0x80049B54: lwc1        $f2, 0x0($t4)
    ctx->f2.u32l = MEM_W(ctx->r12, 0X0);
    // 0x80049B58: addiu       $t9, $a3, 0x400
    ctx->r25 = ADD32(ctx->r7, 0X400);
    // 0x80049B5C: andi        $t1, $t9, 0xFFF
    ctx->r9 = ctx->r25 & 0XFFF;
    // 0x80049B60: mul.s       $f10, $f0, $f2
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f10.fl = MUL_S(ctx->f0.fl, ctx->f2.fl);
    // 0x80049B64: sll         $t2, $t1, 2
    ctx->r10 = S32(ctx->r9 << 2);
    // 0x80049B68: swc1        $f2, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->f2.u32l;
    // 0x80049B6C: addu        $t3, $v0, $t2
    ctx->r11 = ADD32(ctx->r2, ctx->r10);
    // 0x80049B70: swc1        $f10, 0x20($a1)
    MEM_W(0X20, ctx->r5) = ctx->f10.u32l;
    // 0x80049B74: lwc1        $f18, 0x0($t3)
    ctx->f18.u32l = MEM_W(ctx->r11, 0X0);
    // 0x80049B78: mul.s       $f4, $f18, $f0
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f4.fl = MUL_S(ctx->f18.fl, ctx->f0.fl);
    // 0x80049B7C: swc1        $f4, 0x28($a1)
    MEM_W(0X28, ctx->r5) = ctx->f4.u32l;
    // 0x80049B80: lwc1        $f6, 0x48($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X48);
    // 0x80049B84: lwc1        $f10, -0x6DA4($at)
    ctx->f10.u32l = MEM_W(ctx->r1, -0X6DA4);
    // 0x80049B88: lui         $at, 0x3F00
    ctx->r1 = S32(0X3F00 << 16);
    // 0x80049B8C: mul.s       $f8, $f6, $f16
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f8.fl = MUL_S(ctx->f6.fl, ctx->f16.fl);
    // 0x80049B90: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x80049B94: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x80049B98: div.s       $f4, $f8, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f4.fl = DIV_S(ctx->f8.fl, ctx->f10.fl);
    // 0x80049B9C: add.s       $f8, $f4, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = ctx->f4.fl + ctx->f6.fl;
    // 0x80049BA0: trunc.w.s   $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.u32l = TRUNC_W_S(ctx->f8.fl);
    // 0x80049BA4: mfc1        $t0, $f10
    ctx->r8 = (int32_t)ctx->f10.u32l;
    // 0x80049BA8: nop

    // 0x80049BAC: andi        $t5, $t0, 0xFFF
    ctx->r13 = ctx->r8 & 0XFFF;
    // 0x80049BB0: sll         $t6, $t5, 2
    ctx->r14 = S32(ctx->r13 << 2);
    // 0x80049BB4: addu        $t7, $v0, $t6
    ctx->r15 = ADD32(ctx->r2, ctx->r14);
    // 0x80049BB8: lwc1        $f14, 0x0($t7)
    ctx->f14.u32l = MEM_W(ctx->r15, 0X0);
    // 0x80049BBC: addiu       $t8, $t0, 0x400
    ctx->r24 = ADD32(ctx->r8, 0X400);
    // 0x80049BC0: andi        $t9, $t8, 0xFFF
    ctx->r25 = ctx->r24 & 0XFFF;
    // 0x80049BC4: mul.s       $f4, $f14, $f0
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f4.fl = MUL_S(ctx->f14.fl, ctx->f0.fl);
    // 0x80049BC8: sll         $t1, $t9, 2
    ctx->r9 = S32(ctx->r25 << 2);
    // 0x80049BCC: addu        $t2, $v0, $t1
    ctx->r10 = ADD32(ctx->r2, ctx->r9);
    // 0x80049BD0: swc1        $f4, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->f4.u32l;
    // 0x80049BD4: lwc1        $f6, 0x0($t2)
    ctx->f6.u32l = MEM_W(ctx->r10, 0X0);
    // 0x80049BD8: swc1        $f6, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->f6.u32l;
    // 0x80049BDC: lwc1        $f8, 0x20($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X20);
    // 0x80049BE0: mul.s       $f10, $f8, $f0
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f10.fl = MUL_S(ctx->f8.fl, ctx->f0.fl);
    // 0x80049BE4: swc1        $f10, 0x14($a1)
    MEM_W(0X14, ctx->r5) = ctx->f10.u32l;
    // 0x80049BE8: mul.s       $f2, $f2, $f14
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f2.fl = MUL_S(ctx->f2.fl, ctx->f14.fl);
    // 0x80049BEC: lwc1        $f4, 0x20($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X20);
    // 0x80049BF0: swc1        $f14, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->f14.u32l;
    // 0x80049BF4: mul.s       $f0, $f18, $f4
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f0.fl = MUL_S(ctx->f18.fl, ctx->f4.fl);
    // 0x80049BF8: nop

    // 0x80049BFC: mul.s       $f6, $f12, $f2
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f6.fl = MUL_S(ctx->f12.fl, ctx->f2.fl);
    // 0x80049C00: swc1        $f2, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->f2.u32l;
    // 0x80049C04: add.s       $f8, $f0, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = ctx->f0.fl + ctx->f6.fl;
    // 0x80049C08: swc1        $f8, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->f8.u32l;
    // 0x80049C0C: lwc1        $f4, 0x20($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X20);
    // 0x80049C10: lwc1        $f10, 0x30($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0X30);
    // 0x80049C14: lwc1        $f6, 0x2C($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X2C);
    // 0x80049C18: mul.s       $f14, $f10, $f4
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f14.fl = MUL_S(ctx->f10.fl, ctx->f4.fl);
    // 0x80049C1C: nop

    // 0x80049C20: mul.s       $f16, $f6, $f18
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f16.fl = MUL_S(ctx->f6.fl, ctx->f18.fl);
    // 0x80049C24: nop

    // 0x80049C28: mul.s       $f8, $f12, $f14
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f8.fl = MUL_S(ctx->f12.fl, ctx->f14.fl);
    // 0x80049C2C: nop

    // 0x80049C30: mul.s       $f4, $f12, $f16
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f4.fl = MUL_S(ctx->f12.fl, ctx->f16.fl);
    // 0x80049C34: sub.s       $f10, $f8, $f16
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f10.fl = ctx->f8.fl - ctx->f16.fl;
    // 0x80049C38: mul.s       $f8, $f12, $f0
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f8.fl = MUL_S(ctx->f12.fl, ctx->f0.fl);
    // 0x80049C3C: mtc1        $zero, $f0
    ctx->f0.u32l = 0;
    // 0x80049C40: sub.s       $f6, $f4, $f14
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f6.fl = ctx->f4.fl - ctx->f14.fl;
    // 0x80049C44: swc1        $f10, 0x10($a1)
    MEM_W(0X10, ctx->r5) = ctx->f10.u32l;
    // 0x80049C48: swc1        $f6, 0x8($a1)
    MEM_W(0X8, ctx->r5) = ctx->f6.u32l;
    // 0x80049C4C: lwc1        $f10, 0x1C($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0X1C);
    // 0x80049C50: add.s       $f4, $f8, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f4.fl = ctx->f8.fl + ctx->f10.fl;
    // 0x80049C54: swc1        $f4, 0x18($a1)
    MEM_W(0X18, ctx->r5) = ctx->f4.u32l;
    // 0x80049C58: lwc1        $f6, 0x4C($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X4C);
    // 0x80049C5C: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x80049C60: swc1        $f6, 0x30($a1)
    MEM_W(0X30, ctx->r5) = ctx->f6.u32l;
    // 0x80049C64: lwc1        $f8, 0x50($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X50);
    // 0x80049C68: swc1        $f8, 0x34($a1)
    MEM_W(0X34, ctx->r5) = ctx->f8.u32l;
    // 0x80049C6C: lwc1        $f10, 0x54($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0X54);
    // 0x80049C70: swc1        $f0, 0xC($a1)
    MEM_W(0XC, ctx->r5) = ctx->f0.u32l;
    // 0x80049C74: swc1        $f0, 0x1C($a1)
    MEM_W(0X1C, ctx->r5) = ctx->f0.u32l;
    // 0x80049C78: swc1        $f0, 0x2C($a1)
    MEM_W(0X2C, ctx->r5) = ctx->f0.u32l;
    // 0x80049C7C: swc1        $f4, 0x3C($a1)
    MEM_W(0X3C, ctx->r5) = ctx->f4.u32l;
    // 0x80049C80: swc1        $f10, 0x38($a1)
    MEM_W(0X38, ctx->r5) = ctx->f10.u32l;
    // 0x80049C84: jal         0x80047EE0
    // 0x80049C88: lw          $a1, 0x38($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X38);
    SysUtils_MtxFToMtx(rdram, ctx);
        goto after_0;
    // 0x80049C88: lw          $a1, 0x38($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X38);
    after_0:
    // 0x80049C8C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x80049C90: addiu       $sp, $sp, 0x38
    ctx->r29 = ADD32(ctx->r29, 0X38);
    // 0x80049C94: jr          $ra
    // 0x80049C98: nop

    return;
    // 0x80049C98: nop

;}
RECOMP_FUNC void func_80049C9C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x80049C9C: addiu       $sp, $sp, -0xA0
    ctx->r29 = ADD32(ctx->r29, -0XA0);
    // 0x80049CA0: sw          $a1, 0xA4($sp)
    MEM_W(0XA4, ctx->r29) = ctx->r5;
    // 0x80049CA4: lui         $at, 0x4580
    ctx->r1 = S32(0X4580 << 16);
    // 0x80049CA8: mtc1        $at, $f18
    ctx->f18.u32l = ctx->r1;
    // 0x80049CAC: lwc1        $f4, 0xA4($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0XA4);
    // 0x80049CB0: lui         $at, 0x43B4
    ctx->r1 = S32(0X43B4 << 16);
    // 0x80049CB4: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x80049CB8: mul.s       $f6, $f4, $f18
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f6.fl = MUL_S(ctx->f4.fl, ctx->f18.fl);
    // 0x80049CBC: lui         $v0, 0x8015
    ctx->r2 = S32(0X8015 << 16);
    // 0x80049CC0: addiu       $v0, $v0, 0x4350
    ctx->r2 = ADD32(ctx->r2, 0X4350);
    // 0x80049CC4: lwc1        $f12, 0xBC($sp)
    ctx->f12.u32l = MEM_W(ctx->r29, 0XBC);
    // 0x80049CC8: sw          $a2, 0xA8($sp)
    MEM_W(0XA8, ctx->r29) = ctx->r6;
    // 0x80049CCC: sw          $a3, 0xAC($sp)
    MEM_W(0XAC, ctx->r29) = ctx->r7;
    // 0x80049CD0: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x80049CD4: div.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = DIV_S(ctx->f6.fl, ctx->f8.fl);
    // 0x80049CD8: sw          $a0, 0xA0($sp)
    MEM_W(0XA0, ctx->r29) = ctx->r4;
    // 0x80049CDC: or          $a3, $a0, $zero
    ctx->r7 = ctx->r4 | 0;
    // 0x80049CE0: addiu       $a0, $sp, 0x2C
    ctx->r4 = ADD32(ctx->r29, 0X2C);
    // 0x80049CE4: trunc.w.s   $f4, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    ctx->f4.u32l = TRUNC_W_S(ctx->f10.fl);
    // 0x80049CE8: lwc1        $f10, 0xA8($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0XA8);
    // 0x80049CEC: mfc1        $v1, $f4
    ctx->r3 = (int32_t)ctx->f4.u32l;
    // 0x80049CF0: nop

    // 0x80049CF4: andi        $t7, $v1, 0xFFF
    ctx->r15 = ctx->r3 & 0XFFF;
    // 0x80049CF8: sll         $t8, $t7, 2
    ctx->r24 = S32(ctx->r15 << 2);
    // 0x80049CFC: addu        $t9, $v0, $t8
    ctx->r25 = ADD32(ctx->r2, ctx->r24);
    // 0x80049D00: lwc1        $f14, 0x0($t9)
    ctx->f14.u32l = MEM_W(ctx->r25, 0X0);
    // 0x80049D04: addiu       $t4, $v1, 0x400
    ctx->r12 = ADD32(ctx->r3, 0X400);
    // 0x80049D08: andi        $t5, $t4, 0xFFF
    ctx->r13 = ctx->r12 & 0XFFF;
    // 0x80049D0C: neg.s       $f6, $f14
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f14.fl); 
    ctx->f6.fl = -ctx->f14.fl;
    // 0x80049D10: sll         $t6, $t5, 2
    ctx->r14 = S32(ctx->r13 << 2);
    // 0x80049D14: mul.s       $f8, $f6, $f12
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f8.fl = MUL_S(ctx->f6.fl, ctx->f12.fl);
    // 0x80049D18: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x80049D1C: addu        $t7, $v0, $t6
    ctx->r15 = ADD32(ctx->r2, ctx->r14);
    // 0x80049D20: mul.s       $f4, $f10, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f4.fl = MUL_S(ctx->f10.fl, ctx->f18.fl);
    // 0x80049D24: lwc1        $f2, 0x0($t7)
    ctx->f2.u32l = MEM_W(ctx->r15, 0X0);
    // 0x80049D28: swc1        $f8, 0x50($sp)
    MEM_W(0X50, ctx->r29) = ctx->f8.u32l;
    // 0x80049D2C: div.s       $f8, $f4, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = DIV_S(ctx->f4.fl, ctx->f6.fl);
    // 0x80049D30: trunc.w.s   $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.u32l = TRUNC_W_S(ctx->f8.fl);
    // 0x80049D34: mfc1        $a1, $f10
    ctx->r5 = (int32_t)ctx->f10.u32l;
    // 0x80049D38: nop

    // 0x80049D3C: andi        $t1, $a1, 0xFFF
    ctx->r9 = ctx->r5 & 0XFFF;
    // 0x80049D40: sll         $t2, $t1, 2
    ctx->r10 = S32(ctx->r9 << 2);
    // 0x80049D44: addu        $t3, $v0, $t2
    ctx->r11 = ADD32(ctx->r2, ctx->r10);
    // 0x80049D48: lwc1        $f0, 0x0($t3)
    ctx->f0.u32l = MEM_W(ctx->r11, 0X0);
    // 0x80049D4C: addiu       $t8, $a1, 0x400
    ctx->r24 = ADD32(ctx->r5, 0X400);
    // 0x80049D50: andi        $t9, $t8, 0xFFF
    ctx->r25 = ctx->r24 & 0XFFF;
    // 0x80049D54: mul.s       $f4, $f2, $f0
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f4.fl = MUL_S(ctx->f2.fl, ctx->f0.fl);
    // 0x80049D58: sll         $t0, $t9, 2
    ctx->r8 = S32(ctx->r25 << 2);
    // 0x80049D5C: addu        $t1, $v0, $t0
    ctx->r9 = ADD32(ctx->r2, ctx->r8);
    // 0x80049D60: lwc1        $f8, 0x0($t1)
    ctx->f8.u32l = MEM_W(ctx->r9, 0X0);
    // 0x80049D64: swc1        $f0, 0x98($sp)
    MEM_W(0X98, ctx->r29) = ctx->f0.u32l;
    // 0x80049D68: or          $a1, $a3, $zero
    ctx->r5 = ctx->r7 | 0;
    // 0x80049D6C: swc1        $f8, 0x8C($sp)
    MEM_W(0X8C, ctx->r29) = ctx->f8.u32l;
    // 0x80049D70: mul.s       $f6, $f4, $f12
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f6.fl = MUL_S(ctx->f4.fl, ctx->f12.fl);
    // 0x80049D74: lwc1        $f10, 0x8C($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0X8C);
    // 0x80049D78: lwc1        $f8, 0xAC($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0XAC);
    // 0x80049D7C: mul.s       $f4, $f10, $f2
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f4.fl = MUL_S(ctx->f10.fl, ctx->f2.fl);
    // 0x80049D80: swc1        $f6, 0x4C($sp)
    MEM_W(0X4C, ctx->r29) = ctx->f6.u32l;
    // 0x80049D84: mul.s       $f6, $f4, $f12
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f6.fl = MUL_S(ctx->f4.fl, ctx->f12.fl);
    // 0x80049D88: swc1        $f6, 0x54($sp)
    MEM_W(0X54, ctx->r29) = ctx->f6.u32l;
    // 0x80049D8C: mul.s       $f4, $f8, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f4.fl = MUL_S(ctx->f8.fl, ctx->f18.fl);
    // 0x80049D90: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x80049D94: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x80049D98: div.s       $f8, $f4, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = DIV_S(ctx->f4.fl, ctx->f6.fl);
    // 0x80049D9C: trunc.w.s   $f4, $f8
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    ctx->f4.u32l = TRUNC_W_S(ctx->f8.fl);
    // 0x80049DA0: mfc1        $a2, $f4
    ctx->r6 = (int32_t)ctx->f4.u32l;
    // 0x80049DA4: nop

    // 0x80049DA8: andi        $t3, $a2, 0xFFF
    ctx->r11 = ctx->r6 & 0XFFF;
    // 0x80049DAC: sll         $t4, $t3, 2
    ctx->r12 = S32(ctx->r11 << 2);
    // 0x80049DB0: addu        $t5, $v0, $t4
    ctx->r13 = ADD32(ctx->r2, ctx->r12);
    // 0x80049DB4: lwc1        $f16, 0x0($t5)
    ctx->f16.u32l = MEM_W(ctx->r13, 0X0);
    // 0x80049DB8: addiu       $t6, $a2, 0x400
    ctx->r14 = ADD32(ctx->r6, 0X400);
    // 0x80049DBC: andi        $t7, $t6, 0xFFF
    ctx->r15 = ctx->r14 & 0XFFF;
    // 0x80049DC0: mul.s       $f6, $f16, $f2
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f6.fl = MUL_S(ctx->f16.fl, ctx->f2.fl);
    // 0x80049DC4: sll         $t8, $t7, 2
    ctx->r24 = S32(ctx->r15 << 2);
    // 0x80049DC8: addu        $t9, $v0, $t8
    ctx->r25 = ADD32(ctx->r2, ctx->r24);
    // 0x80049DCC: lwc1        $f4, 0x0($t9)
    ctx->f4.u32l = MEM_W(ctx->r25, 0X0);
    // 0x80049DD0: swc1        $f16, 0x94($sp)
    MEM_W(0X94, ctx->r29) = ctx->f16.u32l;
    // 0x80049DD4: swc1        $f4, 0x88($sp)
    MEM_W(0X88, ctx->r29) = ctx->f4.u32l;
    // 0x80049DD8: mul.s       $f8, $f6, $f12
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f8.fl = MUL_S(ctx->f6.fl, ctx->f12.fl);
    // 0x80049DDC: lwc1        $f6, 0x88($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X88);
    // 0x80049DE0: swc1        $f8, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->f8.u32l;
    // 0x80049DE4: mul.s       $f8, $f6, $f2
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f8.fl = MUL_S(ctx->f6.fl, ctx->f2.fl);
    // 0x80049DE8: lwc1        $f6, 0x88($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X88);
    // 0x80049DEC: mul.s       $f4, $f8, $f12
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f4.fl = MUL_S(ctx->f8.fl, ctx->f12.fl);
    // 0x80049DF0: nop

    // 0x80049DF4: mul.s       $f0, $f0, $f16
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f0.fl = MUL_S(ctx->f0.fl, ctx->f16.fl);
    // 0x80049DF8: nop

    // 0x80049DFC: mul.s       $f2, $f10, $f6
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f2.fl = MUL_S(ctx->f10.fl, ctx->f6.fl);
    // 0x80049E00: swc1        $f4, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->f4.u32l;
    // 0x80049E04: mul.s       $f8, $f14, $f0
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f8.fl = MUL_S(ctx->f14.fl, ctx->f0.fl);
    // 0x80049E08: swc1        $f0, 0x84($sp)
    MEM_W(0X84, ctx->r29) = ctx->f0.u32l;
    // 0x80049E0C: add.s       $f4, $f2, $f8
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f4.fl = ctx->f2.fl + ctx->f8.fl;
    // 0x80049E10: lwc1        $f8, 0x98($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X98);
    // 0x80049E14: mul.s       $f6, $f4, $f12
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f6.fl = MUL_S(ctx->f4.fl, ctx->f12.fl);
    // 0x80049E18: lwc1        $f4, 0x88($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X88);
    // 0x80049E1C: mul.s       $f16, $f8, $f4
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f16.fl = MUL_S(ctx->f8.fl, ctx->f4.fl);
    // 0x80049E20: swc1        $f6, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->f6.u32l;
    // 0x80049E24: lwc1        $f6, 0x94($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X94);
    // 0x80049E28: mul.s       $f18, $f6, $f10
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f18.fl = MUL_S(ctx->f6.fl, ctx->f10.fl);
    // 0x80049E2C: nop

    // 0x80049E30: mul.s       $f8, $f14, $f16
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f8.fl = MUL_S(ctx->f14.fl, ctx->f16.fl);
    // 0x80049E34: sub.s       $f4, $f8, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f4.fl = ctx->f8.fl - ctx->f18.fl;
    // 0x80049E38: mul.s       $f6, $f4, $f12
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f6.fl = MUL_S(ctx->f4.fl, ctx->f12.fl);
    // 0x80049E3C: nop

    // 0x80049E40: mul.s       $f10, $f14, $f18
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f10.fl = MUL_S(ctx->f14.fl, ctx->f18.fl);
    // 0x80049E44: swc1        $f6, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->f6.u32l;
    // 0x80049E48: sub.s       $f8, $f10, $f16
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f8.fl = ctx->f10.fl - ctx->f16.fl;
    // 0x80049E4C: lwc1        $f10, 0x84($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0X84);
    // 0x80049E50: mul.s       $f4, $f8, $f12
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f4.fl = MUL_S(ctx->f8.fl, ctx->f12.fl);
    // 0x80049E54: nop

    // 0x80049E58: mul.s       $f6, $f14, $f2
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f6.fl = MUL_S(ctx->f14.fl, ctx->f2.fl);
    // 0x80049E5C: swc1        $f4, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->f4.u32l;
    // 0x80049E60: add.s       $f8, $f6, $f10
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f8.fl = ctx->f6.fl + ctx->f10.fl;
    // 0x80049E64: lwc1        $f6, 0xB0($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0XB0);
    // 0x80049E68: lwc1        $f10, 0xB4($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0XB4);
    // 0x80049E6C: mul.s       $f4, $f8, $f12
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f4.fl = MUL_S(ctx->f8.fl, ctx->f12.fl);
    // 0x80049E70: swc1        $f6, 0x5C($sp)
    MEM_W(0X5C, ctx->r29) = ctx->f6.u32l;
    // 0x80049E74: lwc1        $f8, 0xB8($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0XB8);
    // 0x80049E78: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x80049E7C: swc1        $f10, 0x60($sp)
    MEM_W(0X60, ctx->r29) = ctx->f10.u32l;
    // 0x80049E80: swc1        $f8, 0x64($sp)
    MEM_W(0X64, ctx->r29) = ctx->f8.u32l;
    // 0x80049E84: swc1        $f6, 0x68($sp)
    MEM_W(0X68, ctx->r29) = ctx->f6.u32l;
    // 0x80049E88: swc1        $f4, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->f4.u32l;
    // 0x80049E8C: mtc1        $zero, $f4
    ctx->f4.u32l = 0;
    // 0x80049E90: nop

    // 0x80049E94: swc1        $f4, 0x58($sp)
    MEM_W(0X58, ctx->r29) = ctx->f4.u32l;
    // 0x80049E98: lwc1        $f0, 0x58($sp)
    ctx->f0.u32l = MEM_W(ctx->r29, 0X58);
    // 0x80049E9C: swc1        $f0, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->f0.u32l;
    // 0x80049EA0: jal         0x80047EE0
    // 0x80049EA4: swc1        $f0, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->f0.u32l;
    SysUtils_MtxFToMtx(rdram, ctx);
        goto after_0;
    // 0x80049EA4: swc1        $f0, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->f0.u32l;
    after_0:
    // 0x80049EA8: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x80049EAC: addiu       $sp, $sp, 0xA0
    ctx->r29 = ADD32(ctx->r29, 0XA0);
    // 0x80049EB0: jr          $ra
    // 0x80049EB4: nop

    return;
    // 0x80049EB4: nop

;}
RECOMP_FUNC void SysUtils_MatrixAffineMultiply(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x80049EB8: lwc1        $f4, 0x0($a0)
    ctx->f4.u32l = MEM_W(ctx->r4, 0X0);
    // 0x80049EBC: lwc1        $f6, 0x0($a1)
    ctx->f6.u32l = MEM_W(ctx->r5, 0X0);
    // 0x80049EC0: lwc1        $f10, 0x10($a0)
    ctx->f10.u32l = MEM_W(ctx->r4, 0X10);
    // 0x80049EC4: lwc1        $f16, 0x4($a1)
    ctx->f16.u32l = MEM_W(ctx->r5, 0X4);
    // 0x80049EC8: mul.s       $f8, $f4, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = MUL_S(ctx->f4.fl, ctx->f6.fl);
    // 0x80049ECC: lwc1        $f6, 0x8($a1)
    ctx->f6.u32l = MEM_W(ctx->r5, 0X8);
    // 0x80049ED0: mtc1        $zero, $f0
    ctx->f0.u32l = 0;
    // 0x80049ED4: mul.s       $f18, $f10, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f18.fl = MUL_S(ctx->f10.fl, ctx->f16.fl);
    // 0x80049ED8: lwc1        $f10, 0x20($a0)
    ctx->f10.u32l = MEM_W(ctx->r4, 0X20);
    // 0x80049EDC: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x80049EE0: mul.s       $f16, $f6, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f16.fl = MUL_S(ctx->f6.fl, ctx->f10.fl);
    // 0x80049EE4: add.s       $f4, $f8, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f4.fl = ctx->f8.fl + ctx->f18.fl;
    // 0x80049EE8: add.s       $f8, $f16, $f4
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f8.fl = ctx->f16.fl + ctx->f4.fl;
    // 0x80049EEC: swc1        $f8, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->f8.u32l;
    // 0x80049EF0: lwc1        $f18, 0x4($a0)
    ctx->f18.u32l = MEM_W(ctx->r4, 0X4);
    // 0x80049EF4: lwc1        $f6, 0x0($a1)
    ctx->f6.u32l = MEM_W(ctx->r5, 0X0);
    // 0x80049EF8: lwc1        $f16, 0x14($a0)
    ctx->f16.u32l = MEM_W(ctx->r4, 0X14);
    // 0x80049EFC: lwc1        $f4, 0x4($a1)
    ctx->f4.u32l = MEM_W(ctx->r5, 0X4);
    // 0x80049F00: mul.s       $f10, $f18, $f6
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f10.fl = MUL_S(ctx->f18.fl, ctx->f6.fl);
    // 0x80049F04: lwc1        $f6, 0x8($a1)
    ctx->f6.u32l = MEM_W(ctx->r5, 0X8);
    // 0x80049F08: mul.s       $f8, $f16, $f4
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f8.fl = MUL_S(ctx->f16.fl, ctx->f4.fl);
    // 0x80049F0C: lwc1        $f16, 0x24($a0)
    ctx->f16.u32l = MEM_W(ctx->r4, 0X24);
    // 0x80049F10: mul.s       $f4, $f6, $f16
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f4.fl = MUL_S(ctx->f6.fl, ctx->f16.fl);
    // 0x80049F14: add.s       $f18, $f10, $f8
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f18.fl = ctx->f10.fl + ctx->f8.fl;
    // 0x80049F18: add.s       $f10, $f4, $f18
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f10.fl = ctx->f4.fl + ctx->f18.fl;
    // 0x80049F1C: swc1        $f10, 0x4($a2)
    MEM_W(0X4, ctx->r6) = ctx->f10.u32l;
    // 0x80049F20: lwc1        $f8, 0x8($a0)
    ctx->f8.u32l = MEM_W(ctx->r4, 0X8);
    // 0x80049F24: lwc1        $f6, 0x0($a1)
    ctx->f6.u32l = MEM_W(ctx->r5, 0X0);
    // 0x80049F28: lwc1        $f4, 0x18($a0)
    ctx->f4.u32l = MEM_W(ctx->r4, 0X18);
    // 0x80049F2C: lwc1        $f18, 0x4($a1)
    ctx->f18.u32l = MEM_W(ctx->r5, 0X4);
    // 0x80049F30: mul.s       $f16, $f8, $f6
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f16.fl = MUL_S(ctx->f8.fl, ctx->f6.fl);
    // 0x80049F34: lwc1        $f6, 0x8($a1)
    ctx->f6.u32l = MEM_W(ctx->r5, 0X8);
    // 0x80049F38: mul.s       $f10, $f4, $f18
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f10.fl = MUL_S(ctx->f4.fl, ctx->f18.fl);
    // 0x80049F3C: lwc1        $f4, 0x28($a0)
    ctx->f4.u32l = MEM_W(ctx->r4, 0X28);
    // 0x80049F40: mul.s       $f18, $f6, $f4
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f18.fl = MUL_S(ctx->f6.fl, ctx->f4.fl);
    // 0x80049F44: add.s       $f8, $f16, $f10
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f8.fl = ctx->f16.fl + ctx->f10.fl;
    // 0x80049F48: add.s       $f16, $f18, $f8
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f16.fl = ctx->f18.fl + ctx->f8.fl;
    // 0x80049F4C: swc1        $f16, 0x8($a2)
    MEM_W(0X8, ctx->r6) = ctx->f16.u32l;
    // 0x80049F50: lwc1        $f10, 0x0($a0)
    ctx->f10.u32l = MEM_W(ctx->r4, 0X0);
    // 0x80049F54: lwc1        $f6, 0x10($a1)
    ctx->f6.u32l = MEM_W(ctx->r5, 0X10);
    // 0x80049F58: lwc1        $f18, 0x10($a0)
    ctx->f18.u32l = MEM_W(ctx->r4, 0X10);
    // 0x80049F5C: lwc1        $f8, 0x14($a1)
    ctx->f8.u32l = MEM_W(ctx->r5, 0X14);
    // 0x80049F60: mul.s       $f4, $f10, $f6
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f4.fl = MUL_S(ctx->f10.fl, ctx->f6.fl);
    // 0x80049F64: lwc1        $f6, 0x18($a1)
    ctx->f6.u32l = MEM_W(ctx->r5, 0X18);
    // 0x80049F68: mul.s       $f16, $f18, $f8
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f16.fl = MUL_S(ctx->f18.fl, ctx->f8.fl);
    // 0x80049F6C: lwc1        $f18, 0x20($a0)
    ctx->f18.u32l = MEM_W(ctx->r4, 0X20);
    // 0x80049F70: mul.s       $f8, $f6, $f18
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f8.fl = MUL_S(ctx->f6.fl, ctx->f18.fl);
    // 0x80049F74: add.s       $f10, $f4, $f16
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f10.fl = ctx->f4.fl + ctx->f16.fl;
    // 0x80049F78: add.s       $f4, $f8, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f4.fl = ctx->f8.fl + ctx->f10.fl;
    // 0x80049F7C: swc1        $f4, 0x10($a2)
    MEM_W(0X10, ctx->r6) = ctx->f4.u32l;
    // 0x80049F80: lwc1        $f16, 0x4($a0)
    ctx->f16.u32l = MEM_W(ctx->r4, 0X4);
    // 0x80049F84: lwc1        $f6, 0x10($a1)
    ctx->f6.u32l = MEM_W(ctx->r5, 0X10);
    // 0x80049F88: lwc1        $f8, 0x14($a0)
    ctx->f8.u32l = MEM_W(ctx->r4, 0X14);
    // 0x80049F8C: lwc1        $f10, 0x14($a1)
    ctx->f10.u32l = MEM_W(ctx->r5, 0X14);
    // 0x80049F90: mul.s       $f18, $f16, $f6
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f18.fl = MUL_S(ctx->f16.fl, ctx->f6.fl);
    // 0x80049F94: lwc1        $f6, 0x18($a1)
    ctx->f6.u32l = MEM_W(ctx->r5, 0X18);
    // 0x80049F98: mul.s       $f4, $f8, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f4.fl = MUL_S(ctx->f8.fl, ctx->f10.fl);
    // 0x80049F9C: lwc1        $f8, 0x24($a0)
    ctx->f8.u32l = MEM_W(ctx->r4, 0X24);
    // 0x80049FA0: mul.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = MUL_S(ctx->f6.fl, ctx->f8.fl);
    // 0x80049FA4: add.s       $f16, $f18, $f4
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f16.fl = ctx->f18.fl + ctx->f4.fl;
    // 0x80049FA8: add.s       $f18, $f10, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f18.fl = ctx->f10.fl + ctx->f16.fl;
    // 0x80049FAC: swc1        $f18, 0x14($a2)
    MEM_W(0X14, ctx->r6) = ctx->f18.u32l;
    // 0x80049FB0: lwc1        $f4, 0x8($a0)
    ctx->f4.u32l = MEM_W(ctx->r4, 0X8);
    // 0x80049FB4: lwc1        $f6, 0x10($a1)
    ctx->f6.u32l = MEM_W(ctx->r5, 0X10);
    // 0x80049FB8: lwc1        $f10, 0x18($a0)
    ctx->f10.u32l = MEM_W(ctx->r4, 0X18);
    // 0x80049FBC: lwc1        $f16, 0x14($a1)
    ctx->f16.u32l = MEM_W(ctx->r5, 0X14);
    // 0x80049FC0: mul.s       $f8, $f4, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = MUL_S(ctx->f4.fl, ctx->f6.fl);
    // 0x80049FC4: lwc1        $f6, 0x18($a1)
    ctx->f6.u32l = MEM_W(ctx->r5, 0X18);
    // 0x80049FC8: mul.s       $f18, $f10, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f18.fl = MUL_S(ctx->f10.fl, ctx->f16.fl);
    // 0x80049FCC: lwc1        $f10, 0x28($a0)
    ctx->f10.u32l = MEM_W(ctx->r4, 0X28);
    // 0x80049FD0: mul.s       $f16, $f6, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f16.fl = MUL_S(ctx->f6.fl, ctx->f10.fl);
    // 0x80049FD4: add.s       $f4, $f8, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f4.fl = ctx->f8.fl + ctx->f18.fl;
    // 0x80049FD8: add.s       $f8, $f16, $f4
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f8.fl = ctx->f16.fl + ctx->f4.fl;
    // 0x80049FDC: swc1        $f8, 0x18($a2)
    MEM_W(0X18, ctx->r6) = ctx->f8.u32l;
    // 0x80049FE0: lwc1        $f18, 0x0($a0)
    ctx->f18.u32l = MEM_W(ctx->r4, 0X0);
    // 0x80049FE4: lwc1        $f6, 0x20($a1)
    ctx->f6.u32l = MEM_W(ctx->r5, 0X20);
    // 0x80049FE8: lwc1        $f16, 0x10($a0)
    ctx->f16.u32l = MEM_W(ctx->r4, 0X10);
    // 0x80049FEC: lwc1        $f4, 0x24($a1)
    ctx->f4.u32l = MEM_W(ctx->r5, 0X24);
    // 0x80049FF0: mul.s       $f10, $f18, $f6
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f10.fl = MUL_S(ctx->f18.fl, ctx->f6.fl);
    // 0x80049FF4: lwc1        $f6, 0x28($a1)
    ctx->f6.u32l = MEM_W(ctx->r5, 0X28);
    // 0x80049FF8: mul.s       $f8, $f16, $f4
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f8.fl = MUL_S(ctx->f16.fl, ctx->f4.fl);
    // 0x80049FFC: lwc1        $f16, 0x20($a0)
    ctx->f16.u32l = MEM_W(ctx->r4, 0X20);
    // 0x8004A000: mul.s       $f4, $f6, $f16
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f4.fl = MUL_S(ctx->f6.fl, ctx->f16.fl);
    // 0x8004A004: add.s       $f18, $f10, $f8
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f18.fl = ctx->f10.fl + ctx->f8.fl;
    // 0x8004A008: add.s       $f10, $f4, $f18
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f10.fl = ctx->f4.fl + ctx->f18.fl;
    // 0x8004A00C: swc1        $f10, 0x20($a2)
    MEM_W(0X20, ctx->r6) = ctx->f10.u32l;
    // 0x8004A010: lwc1        $f8, 0x4($a0)
    ctx->f8.u32l = MEM_W(ctx->r4, 0X4);
    // 0x8004A014: lwc1        $f6, 0x20($a1)
    ctx->f6.u32l = MEM_W(ctx->r5, 0X20);
    // 0x8004A018: lwc1        $f4, 0x14($a0)
    ctx->f4.u32l = MEM_W(ctx->r4, 0X14);
    // 0x8004A01C: lwc1        $f18, 0x24($a1)
    ctx->f18.u32l = MEM_W(ctx->r5, 0X24);
    // 0x8004A020: mul.s       $f16, $f8, $f6
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f16.fl = MUL_S(ctx->f8.fl, ctx->f6.fl);
    // 0x8004A024: lwc1        $f6, 0x28($a1)
    ctx->f6.u32l = MEM_W(ctx->r5, 0X28);
    // 0x8004A028: mul.s       $f10, $f4, $f18
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f10.fl = MUL_S(ctx->f4.fl, ctx->f18.fl);
    // 0x8004A02C: lwc1        $f4, 0x24($a0)
    ctx->f4.u32l = MEM_W(ctx->r4, 0X24);
    // 0x8004A030: mul.s       $f18, $f6, $f4
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f18.fl = MUL_S(ctx->f6.fl, ctx->f4.fl);
    // 0x8004A034: add.s       $f8, $f16, $f10
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f8.fl = ctx->f16.fl + ctx->f10.fl;
    // 0x8004A038: add.s       $f16, $f18, $f8
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f16.fl = ctx->f18.fl + ctx->f8.fl;
    // 0x8004A03C: swc1        $f16, 0x24($a2)
    MEM_W(0X24, ctx->r6) = ctx->f16.u32l;
    // 0x8004A040: lwc1        $f10, 0x8($a0)
    ctx->f10.u32l = MEM_W(ctx->r4, 0X8);
    // 0x8004A044: lwc1        $f6, 0x20($a1)
    ctx->f6.u32l = MEM_W(ctx->r5, 0X20);
    // 0x8004A048: lwc1        $f18, 0x18($a0)
    ctx->f18.u32l = MEM_W(ctx->r4, 0X18);
    // 0x8004A04C: lwc1        $f8, 0x24($a1)
    ctx->f8.u32l = MEM_W(ctx->r5, 0X24);
    // 0x8004A050: mul.s       $f4, $f10, $f6
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f4.fl = MUL_S(ctx->f10.fl, ctx->f6.fl);
    // 0x8004A054: lwc1        $f6, 0x28($a1)
    ctx->f6.u32l = MEM_W(ctx->r5, 0X28);
    // 0x8004A058: mul.s       $f16, $f18, $f8
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f16.fl = MUL_S(ctx->f18.fl, ctx->f8.fl);
    // 0x8004A05C: lwc1        $f18, 0x28($a0)
    ctx->f18.u32l = MEM_W(ctx->r4, 0X28);
    // 0x8004A060: mul.s       $f8, $f6, $f18
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f8.fl = MUL_S(ctx->f6.fl, ctx->f18.fl);
    // 0x8004A064: add.s       $f10, $f4, $f16
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f10.fl = ctx->f4.fl + ctx->f16.fl;
    // 0x8004A068: add.s       $f4, $f8, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f4.fl = ctx->f8.fl + ctx->f10.fl;
    // 0x8004A06C: swc1        $f4, 0x28($a2)
    MEM_W(0X28, ctx->r6) = ctx->f4.u32l;
    // 0x8004A070: lwc1        $f6, 0x30($a1)
    ctx->f6.u32l = MEM_W(ctx->r5, 0X30);
    // 0x8004A074: lwc1        $f16, 0x0($a0)
    ctx->f16.u32l = MEM_W(ctx->r4, 0X0);
    // 0x8004A078: lwc1        $f10, 0x34($a1)
    ctx->f10.u32l = MEM_W(ctx->r5, 0X34);
    // 0x8004A07C: lwc1        $f8, 0x10($a0)
    ctx->f8.u32l = MEM_W(ctx->r4, 0X10);
    // 0x8004A080: mul.s       $f18, $f16, $f6
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f18.fl = MUL_S(ctx->f16.fl, ctx->f6.fl);
    // 0x8004A084: lwc1        $f6, 0x20($a0)
    ctx->f6.u32l = MEM_W(ctx->r4, 0X20);
    // 0x8004A088: mul.s       $f4, $f8, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f4.fl = MUL_S(ctx->f8.fl, ctx->f10.fl);
    // 0x8004A08C: lwc1        $f8, 0x38($a1)
    ctx->f8.u32l = MEM_W(ctx->r5, 0X38);
    // 0x8004A090: mul.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = MUL_S(ctx->f6.fl, ctx->f8.fl);
    // 0x8004A094: add.s       $f16, $f18, $f4
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f16.fl = ctx->f18.fl + ctx->f4.fl;
    // 0x8004A098: lwc1        $f4, 0x30($a0)
    ctx->f4.u32l = MEM_W(ctx->r4, 0X30);
    // 0x8004A09C: add.s       $f18, $f16, $f10
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f18.fl = ctx->f16.fl + ctx->f10.fl;
    // 0x8004A0A0: add.s       $f6, $f4, $f18
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f6.fl = ctx->f4.fl + ctx->f18.fl;
    // 0x8004A0A4: swc1        $f6, 0x30($a2)
    MEM_W(0X30, ctx->r6) = ctx->f6.u32l;
    // 0x8004A0A8: lwc1        $f16, 0x30($a1)
    ctx->f16.u32l = MEM_W(ctx->r5, 0X30);
    // 0x8004A0AC: lwc1        $f8, 0x4($a0)
    ctx->f8.u32l = MEM_W(ctx->r4, 0X4);
    // 0x8004A0B0: lwc1        $f18, 0x34($a1)
    ctx->f18.u32l = MEM_W(ctx->r5, 0X34);
    // 0x8004A0B4: lwc1        $f4, 0x14($a0)
    ctx->f4.u32l = MEM_W(ctx->r4, 0X14);
    // 0x8004A0B8: mul.s       $f10, $f8, $f16
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f10.fl = MUL_S(ctx->f8.fl, ctx->f16.fl);
    // 0x8004A0BC: lwc1        $f16, 0x24($a0)
    ctx->f16.u32l = MEM_W(ctx->r4, 0X24);
    // 0x8004A0C0: mul.s       $f6, $f4, $f18
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f6.fl = MUL_S(ctx->f4.fl, ctx->f18.fl);
    // 0x8004A0C4: lwc1        $f4, 0x38($a1)
    ctx->f4.u32l = MEM_W(ctx->r5, 0X38);
    // 0x8004A0C8: mul.s       $f18, $f16, $f4
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f18.fl = MUL_S(ctx->f16.fl, ctx->f4.fl);
    // 0x8004A0CC: add.s       $f8, $f10, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = ctx->f10.fl + ctx->f6.fl;
    // 0x8004A0D0: lwc1        $f6, 0x34($a0)
    ctx->f6.u32l = MEM_W(ctx->r4, 0X34);
    // 0x8004A0D4: add.s       $f10, $f8, $f18
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f10.fl = ctx->f8.fl + ctx->f18.fl;
    // 0x8004A0D8: add.s       $f16, $f6, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f16.fl = ctx->f6.fl + ctx->f10.fl;
    // 0x8004A0DC: swc1        $f16, 0x34($a2)
    MEM_W(0X34, ctx->r6) = ctx->f16.u32l;
    // 0x8004A0E0: lwc1        $f8, 0x30($a1)
    ctx->f8.u32l = MEM_W(ctx->r5, 0X30);
    // 0x8004A0E4: lwc1        $f4, 0x8($a0)
    ctx->f4.u32l = MEM_W(ctx->r4, 0X8);
    // 0x8004A0E8: lwc1        $f10, 0x34($a1)
    ctx->f10.u32l = MEM_W(ctx->r5, 0X34);
    // 0x8004A0EC: lwc1        $f6, 0x18($a0)
    ctx->f6.u32l = MEM_W(ctx->r4, 0X18);
    // 0x8004A0F0: mul.s       $f18, $f4, $f8
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f18.fl = MUL_S(ctx->f4.fl, ctx->f8.fl);
    // 0x8004A0F4: lwc1        $f8, 0x28($a0)
    ctx->f8.u32l = MEM_W(ctx->r4, 0X28);
    // 0x8004A0F8: mul.s       $f16, $f6, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f16.fl = MUL_S(ctx->f6.fl, ctx->f10.fl);
    // 0x8004A0FC: lwc1        $f6, 0x38($a1)
    ctx->f6.u32l = MEM_W(ctx->r5, 0X38);
    // 0x8004A100: mul.s       $f10, $f8, $f6
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f10.fl = MUL_S(ctx->f8.fl, ctx->f6.fl);
    // 0x8004A104: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x8004A108: add.s       $f4, $f18, $f16
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f4.fl = ctx->f18.fl + ctx->f16.fl;
    // 0x8004A10C: lwc1        $f16, 0x38($a0)
    ctx->f16.u32l = MEM_W(ctx->r4, 0X38);
    // 0x8004A110: swc1        $f0, 0xC($a2)
    MEM_W(0XC, ctx->r6) = ctx->f0.u32l;
    // 0x8004A114: swc1        $f0, 0x1C($a2)
    MEM_W(0X1C, ctx->r6) = ctx->f0.u32l;
    // 0x8004A118: add.s       $f18, $f4, $f10
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f18.fl = ctx->f4.fl + ctx->f10.fl;
    // 0x8004A11C: swc1        $f0, 0x2C($a2)
    MEM_W(0X2C, ctx->r6) = ctx->f0.u32l;
    // 0x8004A120: swc1        $f6, 0x3C($a2)
    MEM_W(0X3C, ctx->r6) = ctx->f6.u32l;
    // 0x8004A124: add.s       $f8, $f16, $f18
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f8.fl = ctx->f16.fl + ctx->f18.fl;
    // 0x8004A128: jr          $ra
    // 0x8004A12C: swc1        $f8, 0x38($a2)
    MEM_W(0X38, ctx->r6) = ctx->f8.u32l;
    return;
    // 0x8004A12C: swc1        $f8, 0x38($a2)
    MEM_W(0X38, ctx->r6) = ctx->f8.u32l;
;}
RECOMP_FUNC void SysUtils_ContInitialize(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8004A130: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x8004A134: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x8004A138: lui         $a1, 0x8015
    ctx->r5 = S32(0X8015 << 16);
    // 0x8004A13C: lui         $a0, 0x8015
    ctx->r4 = S32(0X8015 << 16);
    // 0x8004A140: lui         $a2, 0x8015
    ctx->r6 = S32(0X8015 << 16);
    // 0x8004A144: addiu       $a1, $a1, 0x4340
    ctx->r5 = ADD32(ctx->r5, 0X4340);
    // 0x8004A148: addiu       $a2, $a2, 0x42E0
    ctx->r6 = ADD32(ctx->r6, 0X42E0);
    // 0x8004A14C: addiu       $a0, $a0, 0x40D0
    ctx->r4 = ADD32(ctx->r4, 0X40D0);
    // 0x8004A150: jal         0x800C7020
    // 0x8004A154: sw          $zero, 0x18($sp)
    MEM_W(0X18, ctx->r29) = 0;
    osContInit_recomp(rdram, ctx);
        goto after_0;
    // 0x8004A154: sw          $zero, 0x18($sp)
    MEM_W(0X18, ctx->r29) = 0;
    after_0:
    // 0x8004A158: lui         $a1, 0x8015
    ctx->r5 = S32(0X8015 << 16);
    // 0x8004A15C: addiu       $a1, $a1, 0x4340
    ctx->r5 = ADD32(ctx->r5, 0X4340);
    // 0x8004A160: lbu         $a0, 0x0($a1)
    ctx->r4 = MEM_BU(ctx->r5, 0X0);
    // 0x8004A164: lw          $a3, 0x18($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X18);
    // 0x8004A168: lui         $at, 0x8015
    ctx->r1 = S32(0X8015 << 16);
    // 0x8004A16C: andi        $t6, $a0, 0x1
    ctx->r14 = ctx->r4 & 0X1;
    // 0x8004A170: beq         $t6, $zero, L_8004A180
    if (ctx->r14 == 0) {
        // 0x8004A174: sll         $t7, $a0, 30
        ctx->r15 = S32(ctx->r4 << 30);
            goto L_8004A180;
    }
    // 0x8004A174: sll         $t7, $a0, 30
    ctx->r15 = S32(ctx->r4 << 30);
    // 0x8004A178: sw          $zero, 0x4330($at)
    MEM_W(0X4330, ctx->r1) = 0;
    // 0x8004A17C: addiu       $a3, $zero, 0x1
    ctx->r7 = ADD32(0, 0X1);
L_8004A180:
    // 0x8004A180: bgez        $t7, L_8004A1A4
    if (SIGNED(ctx->r15) >= 0) {
        // 0x8004A184: addiu       $v1, $zero, 0x2
        ctx->r3 = ADD32(0, 0X2);
            goto L_8004A1A4;
    }
    // 0x8004A184: addiu       $v1, $zero, 0x2
    ctx->r3 = ADD32(0, 0X2);
    // 0x8004A188: lui         $a1, 0x8015
    ctx->r5 = S32(0X8015 << 16);
    // 0x8004A18C: addiu       $a1, $a1, 0x4330
    ctx->r5 = ADD32(ctx->r5, 0X4330);
    // 0x8004A190: sll         $t9, $a3, 2
    ctx->r25 = S32(ctx->r7 << 2);
    // 0x8004A194: addu        $t0, $a1, $t9
    ctx->r8 = ADD32(ctx->r5, ctx->r25);
    // 0x8004A198: addiu       $t8, $zero, 0x1
    ctx->r24 = ADD32(0, 0X1);
    // 0x8004A19C: sw          $t8, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r24;
    // 0x8004A1A0: addiu       $a3, $a3, 0x1
    ctx->r7 = ADD32(ctx->r7, 0X1);
L_8004A1A4:
    // 0x8004A1A4: sll         $v0, $v1, 1
    ctx->r2 = S32(ctx->r3 << 1);
    // 0x8004A1A8: andi        $v1, $v0, 0xFF
    ctx->r3 = ctx->r2 & 0XFF;
    // 0x8004A1AC: and         $t2, $a0, $v1
    ctx->r10 = ctx->r4 & ctx->r3;
    // 0x8004A1B0: lui         $a1, 0x8015
    ctx->r5 = S32(0X8015 << 16);
    // 0x8004A1B4: beq         $t2, $zero, L_8004A1D0
    if (ctx->r10 == 0) {
        // 0x8004A1B8: addiu       $a1, $a1, 0x4330
        ctx->r5 = ADD32(ctx->r5, 0X4330);
            goto L_8004A1D0;
    }
    // 0x8004A1B8: addiu       $a1, $a1, 0x4330
    ctx->r5 = ADD32(ctx->r5, 0X4330);
    // 0x8004A1BC: sll         $t4, $a3, 2
    ctx->r12 = S32(ctx->r7 << 2);
    // 0x8004A1C0: addu        $t5, $a1, $t4
    ctx->r13 = ADD32(ctx->r5, ctx->r12);
    // 0x8004A1C4: addiu       $t3, $zero, 0x2
    ctx->r11 = ADD32(0, 0X2);
    // 0x8004A1C8: sw          $t3, 0x0($t5)
    MEM_W(0X0, ctx->r13) = ctx->r11;
    // 0x8004A1CC: addiu       $a3, $a3, 0x1
    ctx->r7 = ADD32(ctx->r7, 0X1);
L_8004A1D0:
    // 0x8004A1D0: sll         $v0, $v1, 1
    ctx->r2 = S32(ctx->r3 << 1);
    // 0x8004A1D4: andi        $t6, $v0, 0xFF
    ctx->r14 = ctx->r2 & 0XFF;
    // 0x8004A1D8: and         $t7, $a0, $t6
    ctx->r15 = ctx->r4 & ctx->r14;
    // 0x8004A1DC: beq         $t7, $zero, L_8004A1F4
    if (ctx->r15 == 0) {
        // 0x8004A1E0: addiu       $t9, $zero, 0x3
        ctx->r25 = ADD32(0, 0X3);
            goto L_8004A1F4;
    }
    // 0x8004A1E0: addiu       $t9, $zero, 0x3
    ctx->r25 = ADD32(0, 0X3);
    // 0x8004A1E4: sll         $t8, $a3, 2
    ctx->r24 = S32(ctx->r7 << 2);
    // 0x8004A1E8: addu        $t0, $a1, $t8
    ctx->r8 = ADD32(ctx->r5, ctx->r24);
    // 0x8004A1EC: sw          $t9, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r25;
    // 0x8004A1F0: addiu       $a3, $a3, 0x1
    ctx->r7 = ADD32(ctx->r7, 0X1);
L_8004A1F4:
    // 0x8004A1F4: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x8004A1F8: lui         $at, 0x8015
    ctx->r1 = S32(0X8015 << 16);
    // 0x8004A1FC: sw          $a3, 0x4344($at)
    MEM_W(0X4344, ctx->r1) = ctx->r7;
    // 0x8004A200: jr          $ra
    // 0x8004A204: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    return;
    // 0x8004A204: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
;}
RECOMP_FUNC void func_8004A208(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8004A208: lui         $a0, 0x8015
    ctx->r4 = S32(0X8015 << 16);
    // 0x8004A20C: lui         $a3, 0x8015
    ctx->r7 = S32(0X8015 << 16);
    // 0x8004A210: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
    // 0x8004A214: addiu       $a3, $a3, 0x4308
    ctx->r7 = ADD32(ctx->r7, 0X4308);
    // 0x8004A218: lbu         $a0, 0x4340($a0)
    ctx->r4 = MEM_BU(ctx->r4, 0X4340);
    // 0x8004A21C: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
    // 0x8004A220: addiu       $t1, $zero, 0x4
    ctx->r9 = ADD32(0, 0X4);
    // 0x8004A224: addiu       $t0, $zero, 0xA
    ctx->r8 = ADD32(0, 0XA);
L_8004A228:
    // 0x8004A228: and         $t6, $a0, $v0
    ctx->r14 = ctx->r4 & ctx->r2;
    // 0x8004A22C: beq         $t6, $zero, L_8004A25C
    if (ctx->r14 == 0) {
        // 0x8004A230: or          $a1, $v0, $zero
        ctx->r5 = ctx->r2 | 0;
            goto L_8004A25C;
    }
    // 0x8004A230: or          $a1, $v0, $zero
    ctx->r5 = ctx->r2 | 0;
    // 0x8004A234: multu       $v1, $t0
    result = U64(U32(ctx->r3)) * U64(U32(ctx->r8)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x8004A238: mflo        $t7
    ctx->r15 = lo;
    // 0x8004A23C: addu        $v0, $a3, $t7
    ctx->r2 = ADD32(ctx->r7, ctx->r15);
    // 0x8004A240: sb          $zero, 0x9($v0)
    MEM_B(0X9, ctx->r2) = 0;
    // 0x8004A244: lb          $t8, 0x9($v0)
    ctx->r24 = MEM_B(ctx->r2, 0X9);
    // 0x8004A248: sh          $zero, 0x6($v0)
    MEM_H(0X6, ctx->r2) = 0;
    // 0x8004A24C: sh          $zero, 0x4($v0)
    MEM_H(0X4, ctx->r2) = 0;
    // 0x8004A250: sh          $zero, 0x2($v0)
    MEM_H(0X2, ctx->r2) = 0;
    // 0x8004A254: sh          $zero, 0x0($v0)
    MEM_H(0X0, ctx->r2) = 0;
    // 0x8004A258: sb          $t8, 0x8($v0)
    MEM_B(0X8, ctx->r2) = ctx->r24;
L_8004A25C:
    // 0x8004A25C: sll         $v0, $a1, 1
    ctx->r2 = S32(ctx->r5 << 1);
    // 0x8004A260: andi        $a1, $v0, 0xFF
    ctx->r5 = ctx->r2 & 0XFF;
    // 0x8004A264: and         $t2, $a0, $a1
    ctx->r10 = ctx->r4 & ctx->r5;
    // 0x8004A268: beql        $t2, $zero, L_8004A29C
    if (ctx->r10 == 0) {
        // 0x8004A26C: sll         $v0, $a1, 1
        ctx->r2 = S32(ctx->r5 << 1);
            goto L_8004A29C;
    }
    goto skip_0;
    // 0x8004A26C: sll         $v0, $a1, 1
    ctx->r2 = S32(ctx->r5 << 1);
    skip_0:
    // 0x8004A270: multu       $v1, $t0
    result = U64(U32(ctx->r3)) * U64(U32(ctx->r8)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x8004A274: mflo        $t3
    ctx->r11 = lo;
    // 0x8004A278: addu        $v0, $a3, $t3
    ctx->r2 = ADD32(ctx->r7, ctx->r11);
    // 0x8004A27C: sb          $zero, 0x13($v0)
    MEM_B(0X13, ctx->r2) = 0;
    // 0x8004A280: lb          $t4, 0x13($v0)
    ctx->r12 = MEM_B(ctx->r2, 0X13);
    // 0x8004A284: sh          $zero, 0x10($v0)
    MEM_H(0X10, ctx->r2) = 0;
    // 0x8004A288: sh          $zero, 0xE($v0)
    MEM_H(0XE, ctx->r2) = 0;
    // 0x8004A28C: sh          $zero, 0xC($v0)
    MEM_H(0XC, ctx->r2) = 0;
    // 0x8004A290: sh          $zero, 0xA($v0)
    MEM_H(0XA, ctx->r2) = 0;
    // 0x8004A294: sb          $t4, 0x12($v0)
    MEM_B(0X12, ctx->r2) = ctx->r12;
    // 0x8004A298: sll         $v0, $a1, 1
    ctx->r2 = S32(ctx->r5 << 1);
L_8004A29C:
    // 0x8004A29C: andi        $t5, $v0, 0xFF
    ctx->r13 = ctx->r2 & 0XFF;
    // 0x8004A2A0: addiu       $v1, $v1, 0x2
    ctx->r3 = ADD32(ctx->r3, 0X2);
    // 0x8004A2A4: bne         $v1, $t1, L_8004A228
    if (ctx->r3 != ctx->r9) {
        // 0x8004A2A8: or          $v0, $t5, $zero
        ctx->r2 = ctx->r13 | 0;
            goto L_8004A228;
    }
    // 0x8004A2A8: or          $v0, $t5, $zero
    ctx->r2 = ctx->r13 | 0;
    // 0x8004A2AC: jr          $ra
    // 0x8004A2B0: nop

    return;
    // 0x8004A2B0: nop

;}
RECOMP_FUNC void SysUtils_UpdateControllers(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8004A2B4: addiu       $sp, $sp, -0x28
    ctx->r29 = ADD32(ctx->r29, -0X28);
    // 0x8004A2B8: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x8004A2BC: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
    // 0x8004A2C0: lui         $a0, 0x8015
    ctx->r4 = S32(0X8015 << 16);
    // 0x8004A2C4: lui         $a1, 0x8015
    ctx->r5 = S32(0X8015 << 16);
    // 0x8004A2C8: sw          $s0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r16;
    // 0x8004A2CC: addiu       $a1, $a1, 0x4348
    ctx->r5 = ADD32(ctx->r5, 0X4348);
    // 0x8004A2D0: addiu       $a0, $a0, 0x40D0
    ctx->r4 = ADD32(ctx->r4, 0X40D0);
    // 0x8004A2D4: sb          $v0, 0x23($sp)
    MEM_B(0X23, ctx->r29) = ctx->r2;
    // 0x8004A2D8: jal         0x800C5C60
    // 0x8004A2DC: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    osRecvMesg_recomp(rdram, ctx);
        goto after_0;
    // 0x8004A2DC: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    after_0:
    // 0x8004A2E0: lui         $s0, 0x8015
    ctx->r16 = S32(0X8015 << 16);
    // 0x8004A2E4: addiu       $s0, $s0, 0x42F0
    ctx->r16 = ADD32(ctx->r16, 0X42F0);
    // 0x8004A2E8: jal         0x800C5AC4
    // 0x8004A2EC: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    osContGetReadData_recomp(rdram, ctx);
        goto after_1;
    // 0x8004A2EC: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_1:
    // 0x8004A2F0: lui         $t2, 0x8015
    ctx->r10 = S32(0X8015 << 16);
    // 0x8004A2F4: lui         $t3, 0x8015
    ctx->r11 = S32(0X8015 << 16);
    // 0x8004A2F8: lbu         $v0, 0x23($sp)
    ctx->r2 = MEM_BU(ctx->r29, 0X23);
    // 0x8004A2FC: addiu       $t3, $t3, 0x4308
    ctx->r11 = ADD32(ctx->r11, 0X4308);
    // 0x8004A300: lbu         $t2, 0x4340($t2)
    ctx->r10 = MEM_BU(ctx->r10, 0X4340);
    // 0x8004A304: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    // 0x8004A308: addiu       $ra, $zero, 0x4
    ctx->r31 = ADD32(0, 0X4);
    // 0x8004A30C: addiu       $t5, $zero, 0x6
    ctx->r13 = ADD32(0, 0X6);
    // 0x8004A310: addiu       $t4, $zero, 0xA
    ctx->r12 = ADD32(0, 0XA);
L_8004A314:
    // 0x8004A314: and         $t6, $t2, $v0
    ctx->r14 = ctx->r10 & ctx->r2;
    // 0x8004A318: beq         $t6, $zero, L_8004A36C
    if (ctx->r14 == 0) {
        // 0x8004A31C: or          $t1, $v0, $zero
        ctx->r9 = ctx->r2 | 0;
            goto L_8004A36C;
    }
    // 0x8004A31C: or          $t1, $v0, $zero
    ctx->r9 = ctx->r2 | 0;
    // 0x8004A320: multu       $a3, $t4
    result = U64(U32(ctx->r7)) * U64(U32(ctx->r12)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x8004A324: mflo        $t7
    ctx->r15 = lo;
    // 0x8004A328: addu        $v0, $t3, $t7
    ctx->r2 = ADD32(ctx->r11, ctx->r15);
    // 0x8004A32C: lhu         $a1, 0x0($v0)
    ctx->r5 = MEM_HU(ctx->r2, 0X0);
    // 0x8004A330: multu       $a3, $t5
    result = U64(U32(ctx->r7)) * U64(U32(ctx->r13)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x8004A334: sh          $a1, 0x6($v0)
    MEM_H(0X6, ctx->r2) = ctx->r5;
    // 0x8004A338: mflo        $t9
    ctx->r25 = lo;
    // 0x8004A33C: addu        $v1, $s0, $t9
    ctx->r3 = ADD32(ctx->r16, ctx->r25);
    // 0x8004A340: lhu         $a0, 0x0($v1)
    ctx->r4 = MEM_HU(ctx->r3, 0X0);
    // 0x8004A344: lb          $t6, 0x2($v1)
    ctx->r14 = MEM_B(ctx->r3, 0X2);
    // 0x8004A348: xor         $t7, $a0, $a1
    ctx->r15 = ctx->r4 ^ ctx->r5;
    // 0x8004A34C: and         $t9, $a1, $t7
    ctx->r25 = ctx->r5 & ctx->r15;
    // 0x8004A350: and         $t8, $a0, $t7
    ctx->r24 = ctx->r4 & ctx->r15;
    // 0x8004A354: lb          $t7, 0x3($v1)
    ctx->r15 = MEM_B(ctx->r3, 0X3);
    // 0x8004A358: sh          $t8, 0x2($v0)
    MEM_H(0X2, ctx->r2) = ctx->r24;
    // 0x8004A35C: sh          $t9, 0x4($v0)
    MEM_H(0X4, ctx->r2) = ctx->r25;
    // 0x8004A360: sh          $a0, 0x0($v0)
    MEM_H(0X0, ctx->r2) = ctx->r4;
    // 0x8004A364: sb          $t6, 0x8($v0)
    MEM_B(0X8, ctx->r2) = ctx->r14;
    // 0x8004A368: sb          $t7, 0x9($v0)
    MEM_B(0X9, ctx->r2) = ctx->r15;
L_8004A36C:
    // 0x8004A36C: sll         $v0, $t1, 1
    ctx->r2 = S32(ctx->r9 << 1);
    // 0x8004A370: addiu       $a3, $a3, 0x1
    ctx->r7 = ADD32(ctx->r7, 0X1);
    // 0x8004A374: andi        $t8, $v0, 0xFF
    ctx->r24 = ctx->r2 & 0XFF;
    // 0x8004A378: bne         $a3, $ra, L_8004A314
    if (ctx->r7 != ctx->r31) {
        // 0x8004A37C: or          $v0, $t8, $zero
        ctx->r2 = ctx->r24 | 0;
            goto L_8004A314;
    }
    // 0x8004A37C: or          $v0, $t8, $zero
    ctx->r2 = ctx->r24 | 0;
    // 0x8004A380: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    // 0x8004A384: lw          $s0, 0x18($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X18);
    // 0x8004A388: addiu       $sp, $sp, 0x28
    ctx->r29 = ADD32(ctx->r29, 0X28);
    // 0x8004A38C: jr          $ra
    // 0x8004A390: nop

    return;
    // 0x8004A390: nop

    // 0x8004A394: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x8004A398: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x8004A39C: lui         $a0, 0x8015
    ctx->r4 = S32(0X8015 << 16);
    // 0x8004A3A0: jal         0x800C5A00
    // 0x8004A3A4: addiu       $a0, $a0, 0x40D0
    ctx->r4 = ADD32(ctx->r4, 0X40D0);
    osContStartReadData_recomp(rdram, ctx);
        goto after_2;
    // 0x8004A3A4: addiu       $a0, $a0, 0x40D0
    ctx->r4 = ADD32(ctx->r4, 0X40D0);
    after_2:
    // 0x8004A3A8: jal         0x8004A2B4
    // 0x8004A3AC: nop

    SysUtils_UpdateControllers(rdram, ctx);
        goto after_3;
    // 0x8004A3AC: nop

    after_3:
    // 0x8004A3B0: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x8004A3B4: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x8004A3B8: jr          $ra
    // 0x8004A3BC: nop

    return;
    // 0x8004A3BC: nop

;}
RECOMP_FUNC void func_8004A3C0(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8004A3C0: addiu       $sp, $sp, -0xB0
    ctx->r29 = ADD32(ctx->r29, -0XB0);
    // 0x8004A3C4: lui         $at, 0x4580
    ctx->r1 = S32(0X4580 << 16);
    // 0x8004A3C8: lwc1        $f12, 0xC4($sp)
    ctx->f12.u32l = MEM_W(ctx->r29, 0XC4);
    // 0x8004A3CC: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x8004A3D0: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x8004A3D4: lwc1        $f8, -0x6DA0($at)
    ctx->f8.u32l = MEM_W(ctx->r1, -0X6DA0);
    // 0x8004A3D8: mul.s       $f6, $f12, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = MUL_S(ctx->f12.fl, ctx->f4.fl);
    // 0x8004A3DC: lui         $at, 0x3F00
    ctx->r1 = S32(0X3F00 << 16);
    // 0x8004A3E0: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x8004A3E4: sdc1        $f24, 0x30($sp)
    CHECK_FR(ctx, 24);
    SD(ctx->f24.u64, 0X30, ctx->r29);
    // 0x8004A3E8: mtc1        $a3, $f24
    ctx->f24.u32l = ctx->r7;
    // 0x8004A3EC: mtc1        $zero, $f0
    ctx->f0.u32l = 0;
    // 0x8004A3F0: lui         $v1, 0x8015
    ctx->r3 = S32(0X8015 << 16);
    // 0x8004A3F4: div.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = DIV_S(ctx->f6.fl, ctx->f8.fl);
    // 0x8004A3F8: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x8004A3FC: addiu       $v1, $v1, 0x4350
    ctx->r3 = ADD32(ctx->r3, 0X4350);
    // 0x8004A400: sdc1        $f26, 0x38($sp)
    CHECK_FR(ctx, 26);
    SD(ctx->f26.u64, 0X38, ctx->r29);
    // 0x8004A404: c.eq.s      $f24, $f0
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 0);
    c1cs = ctx->f24.fl == ctx->f0.fl;
    // 0x8004A408: sw          $s0, 0x50($sp)
    MEM_W(0X50, ctx->r29) = ctx->r16;
    // 0x8004A40C: sdc1        $f28, 0x40($sp)
    CHECK_FR(ctx, 28);
    SD(ctx->f28.u64, 0X40, ctx->r29);
    // 0x8004A410: mtc1        $a2, $f14
    ctx->f14.u32l = ctx->r6;
    // 0x8004A414: or          $s0, $a1, $zero
    ctx->r16 = ctx->r5 | 0;
    // 0x8004A418: sw          $ra, 0x54($sp)
    MEM_W(0X54, ctx->r29) = ctx->r31;
    // 0x8004A41C: sdc1        $f30, 0x48($sp)
    CHECK_FR(ctx, 30);
    SD(ctx->f30.u64, 0X48, ctx->r29);
    // 0x8004A420: sdc1        $f22, 0x28($sp)
    CHECK_FR(ctx, 22);
    SD(ctx->f22.u64, 0X28, ctx->r29);
    // 0x8004A424: sdc1        $f20, 0x20($sp)
    CHECK_FR(ctx, 20);
    SD(ctx->f20.u64, 0X20, ctx->r29);
    // 0x8004A428: sw          $a0, 0xB0($sp)
    MEM_W(0XB0, ctx->r29) = ctx->r4;
    // 0x8004A42C: lwc1        $f28, 0xC0($sp)
    ctx->f28.u32l = MEM_W(ctx->r29, 0XC0);
    // 0x8004A430: mul.s       $f6, $f10, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = MUL_S(ctx->f10.fl, ctx->f4.fl);
    // 0x8004A434: add.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = ctx->f6.fl + ctx->f8.fl;
    // 0x8004A438: trunc.w.s   $f4, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    ctx->f4.u32l = TRUNC_W_S(ctx->f10.fl);
    // 0x8004A43C: mfc1        $v0, $f4
    ctx->r2 = (int32_t)ctx->f4.u32l;
    // 0x8004A440: nop

    // 0x8004A444: addiu       $t7, $v0, 0x400
    ctx->r15 = ADD32(ctx->r2, 0X400);
    // 0x8004A448: andi        $t1, $v0, 0xFFF
    ctx->r9 = ctx->r2 & 0XFFF;
    // 0x8004A44C: andi        $t8, $t7, 0xFFF
    ctx->r24 = ctx->r15 & 0XFFF;
    // 0x8004A450: sll         $t2, $t1, 2
    ctx->r10 = S32(ctx->r9 << 2);
    // 0x8004A454: sll         $t9, $t8, 2
    ctx->r25 = S32(ctx->r24 << 2);
    // 0x8004A458: addu        $t3, $v1, $t2
    ctx->r11 = ADD32(ctx->r3, ctx->r10);
    // 0x8004A45C: lwc1        $f6, 0x0($t3)
    ctx->f6.u32l = MEM_W(ctx->r11, 0X0);
    // 0x8004A460: addu        $t0, $v1, $t9
    ctx->r8 = ADD32(ctx->r3, ctx->r25);
    // 0x8004A464: lwc1        $f26, 0x0($t0)
    ctx->f26.u32l = MEM_W(ctx->r8, 0X0);
    // 0x8004A468: bc1f        L_8004A570
    if (!c1cs) {
        // 0x8004A46C: swc1        $f6, 0xA0($sp)
        MEM_W(0XA0, ctx->r29) = ctx->f6.u32l;
            goto L_8004A570;
    }
    // 0x8004A46C: swc1        $f6, 0xA0($sp)
    MEM_W(0XA0, ctx->r29) = ctx->f6.u32l;
    // 0x8004A470: c.eq.s      $f14, $f0
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 0);
    c1cs = ctx->f14.fl == ctx->f0.fl;
    // 0x8004A474: lwc1        $f8, 0xC0($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0XC0);
    // 0x8004A478: bc1f        L_8004A4CC
    if (!c1cs) {
        // 0x8004A47C: nop
    
            goto L_8004A4CC;
    }
    // 0x8004A47C: nop

    // 0x8004A480: c.lt.s      $f8, $f0
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 0);
    c1cs = ctx->f8.fl < ctx->f0.fl;
    // 0x8004A484: nop

    // 0x8004A488: bc1fl       L_8004A4B0
    if (!c1cs) {
        // 0x8004A48C: mfc1        $a2, $f0
        ctx->r6 = (int32_t)ctx->f0.u32l;
            goto L_8004A4B0;
    }
    goto skip_0;
    // 0x8004A48C: mfc1        $a2, $f0
    ctx->r6 = (int32_t)ctx->f0.u32l;
    skip_0:
    // 0x8004A490: neg.s       $f10, $f12
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f12.fl); 
    ctx->f10.fl = -ctx->f12.fl;
    // 0x8004A494: mfc1        $a2, $f0
    ctx->r6 = (int32_t)ctx->f0.u32l;
    // 0x8004A498: mfc1        $a3, $f0
    ctx->r7 = (int32_t)ctx->f0.u32l;
    // 0x8004A49C: jal         0x800498A4
    // 0x8004A4A0: swc1        $f10, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f10.u32l;
    func_800498A4(rdram, ctx);
        goto after_0;
    // 0x8004A4A0: swc1        $f10, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f10.u32l;
    after_0:
    // 0x8004A4A4: b           L_8004A88C
    // 0x8004A4A8: lw          $ra, 0x54($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X54);
        goto L_8004A88C;
    // 0x8004A4A8: lw          $ra, 0x54($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X54);
    // 0x8004A4AC: mfc1        $a2, $f0
    ctx->r6 = (int32_t)ctx->f0.u32l;
L_8004A4B0:
    // 0x8004A4B0: mfc1        $a3, $f0
    ctx->r7 = (int32_t)ctx->f0.u32l;
    // 0x8004A4B4: lw          $a0, 0xB0($sp)
    ctx->r4 = MEM_W(ctx->r29, 0XB0);
    // 0x8004A4B8: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    // 0x8004A4BC: jal         0x800498A4
    // 0x8004A4C0: swc1        $f12, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f12.u32l;
    func_800498A4(rdram, ctx);
        goto after_1;
    // 0x8004A4C0: swc1        $f12, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f12.u32l;
    after_1:
    // 0x8004A4C4: b           L_8004A88C
    // 0x8004A4C8: lw          $ra, 0x54($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X54);
        goto L_8004A88C;
    // 0x8004A4C8: lw          $ra, 0x54($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X54);
L_8004A4CC:
    // 0x8004A4CC: mul.s       $f4, $f14, $f14
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f4.fl = MUL_S(ctx->f14.fl, ctx->f14.fl);
    // 0x8004A4D0: lwc1        $f0, 0xC0($sp)
    ctx->f0.u32l = MEM_W(ctx->r29, 0XC0);
    // 0x8004A4D4: swc1        $f14, 0xB8($sp)
    MEM_W(0XB8, ctx->r29) = ctx->f14.u32l;
    // 0x8004A4D8: mul.s       $f6, $f0, $f0
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f6.fl = MUL_S(ctx->f0.fl, ctx->f0.fl);
    // 0x8004A4DC: jal         0x800C7010
    // 0x8004A4E0: add.s       $f12, $f4, $f6
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f12.fl = ctx->f4.fl + ctx->f6.fl;
    _nsqrtf(rdram, ctx);
        goto after_2;
    // 0x8004A4E0: add.s       $f12, $f4, $f6
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f12.fl = ctx->f4.fl + ctx->f6.fl;
    after_2:
    // 0x8004A4E4: lwc1        $f8, 0xC0($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0XC0);
    // 0x8004A4E8: lwc1        $f24, 0xA0($sp)
    ctx->f24.u32l = MEM_W(ctx->r29, 0XA0);
    // 0x8004A4EC: div.s       $f12, $f8, $f0
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f12.fl = DIV_S(ctx->f8.fl, ctx->f0.fl);
    // 0x8004A4F0: mul.s       $f16, $f24, $f12
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f24.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f16.fl = MUL_S(ctx->f24.fl, ctx->f12.fl);
    // 0x8004A4F4: neg.s       $f10, $f16
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f16.fl); 
    ctx->f10.fl = -ctx->f16.fl;
    // 0x8004A4F8: swc1        $f16, 0x4($s0)
    MEM_W(0X4, ctx->r16) = ctx->f16.u32l;
    // 0x8004A4FC: swc1        $f10, 0x10($s0)
    MEM_W(0X10, ctx->r16) = ctx->f10.u32l;
    // 0x8004A500: lwc1        $f4, 0xB8($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0XB8);
    // 0x8004A504: swc1        $f26, 0x14($s0)
    MEM_W(0X14, ctx->r16) = ctx->f26.u32l;
    // 0x8004A508: div.s       $f2, $f4, $f0
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f2.fl = DIV_S(ctx->f4.fl, ctx->f0.fl);
    // 0x8004A50C: neg.s       $f14, $f2
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f2.fl); 
    ctx->f14.fl = -ctx->f2.fl;
    // 0x8004A510: mul.s       $f18, $f24, $f14
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f24.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f18.fl = MUL_S(ctx->f24.fl, ctx->f14.fl);
    // 0x8004A514: nop

    // 0x8004A518: mul.s       $f20, $f26, $f12
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f26.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f20.fl = MUL_S(ctx->f26.fl, ctx->f12.fl);
    // 0x8004A51C: neg.s       $f6, $f18
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f18.fl); 
    ctx->f6.fl = -ctx->f18.fl;
    // 0x8004A520: swc1        $f18, 0x24($s0)
    MEM_W(0X24, ctx->r16) = ctx->f18.u32l;
    // 0x8004A524: swc1        $f6, 0x18($s0)
    MEM_W(0X18, ctx->r16) = ctx->f6.u32l;
    // 0x8004A528: mul.s       $f8, $f20, $f12
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f8.fl = MUL_S(ctx->f20.fl, ctx->f12.fl);
    // 0x8004A52C: nop

    // 0x8004A530: mul.s       $f10, $f2, $f2
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f10.fl = MUL_S(ctx->f2.fl, ctx->f2.fl);
    // 0x8004A534: nop

    // 0x8004A538: mul.s       $f6, $f26, $f14
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f26.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f6.fl = MUL_S(ctx->f26.fl, ctx->f14.fl);
    // 0x8004A53C: add.s       $f4, $f8, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f4.fl = ctx->f8.fl + ctx->f10.fl;
    // 0x8004A540: mul.s       $f8, $f6, $f14
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f8.fl = MUL_S(ctx->f6.fl, ctx->f14.fl);
    // 0x8004A544: swc1        $f4, 0x0($s0)
    MEM_W(0X0, ctx->r16) = ctx->f4.u32l;
    // 0x8004A548: mul.s       $f10, $f12, $f12
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f10.fl = MUL_S(ctx->f12.fl, ctx->f12.fl);
    // 0x8004A54C: add.s       $f4, $f8, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f4.fl = ctx->f8.fl + ctx->f10.fl;
    // 0x8004A550: mul.s       $f6, $f20, $f14
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f6.fl = MUL_S(ctx->f20.fl, ctx->f14.fl);
    // 0x8004A554: nop

    // 0x8004A558: mul.s       $f8, $f2, $f12
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f8.fl = MUL_S(ctx->f2.fl, ctx->f12.fl);
    // 0x8004A55C: swc1        $f4, 0x28($s0)
    MEM_W(0X28, ctx->r16) = ctx->f4.u32l;
    // 0x8004A560: add.s       $f22, $f6, $f8
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f22.fl = ctx->f6.fl + ctx->f8.fl;
    // 0x8004A564: swc1        $f22, 0x20($s0)
    MEM_W(0X20, ctx->r16) = ctx->f22.u32l;
    // 0x8004A568: b           L_8004A854
    // 0x8004A56C: swc1        $f22, 0x8($s0)
    MEM_W(0X8, ctx->r16) = ctx->f22.u32l;
        goto L_8004A854;
    // 0x8004A56C: swc1        $f22, 0x8($s0)
    MEM_W(0X8, ctx->r16) = ctx->f22.u32l;
L_8004A570:
    // 0x8004A570: c.eq.s      $f28, $f0
    CHECK_FR(ctx, 28);
    CHECK_FR(ctx, 0);
    c1cs = ctx->f28.fl == ctx->f0.fl;
    // 0x8004A574: nop

    // 0x8004A578: bc1fl       L_8004A620
    if (!c1cs) {
        // 0x8004A57C: c.eq.s      $f14, $f0
        CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 0);
    c1cs = ctx->f14.fl == ctx->f0.fl;
            goto L_8004A620;
    }
    goto skip_1;
    // 0x8004A57C: c.eq.s      $f14, $f0
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 0);
    c1cs = ctx->f14.fl == ctx->f0.fl;
    skip_1:
    // 0x8004A580: mul.s       $f10, $f14, $f14
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f10.fl = MUL_S(ctx->f14.fl, ctx->f14.fl);
    // 0x8004A584: swc1        $f14, 0xB8($sp)
    MEM_W(0XB8, ctx->r29) = ctx->f14.u32l;
    // 0x8004A588: mul.s       $f4, $f24, $f24
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 24);
    NAN_CHECK(ctx->f24.fl); NAN_CHECK(ctx->f24.fl); 
    ctx->f4.fl = MUL_S(ctx->f24.fl, ctx->f24.fl);
    // 0x8004A58C: jal         0x800C7010
    // 0x8004A590: add.s       $f12, $f10, $f4
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f12.fl = ctx->f10.fl + ctx->f4.fl;
    _nsqrtf(rdram, ctx);
        goto after_3;
    // 0x8004A590: add.s       $f12, $f10, $f4
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f12.fl = ctx->f10.fl + ctx->f4.fl;
    after_3:
    // 0x8004A594: div.s       $f14, $f24, $f0
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f24.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f14.fl = DIV_S(ctx->f24.fl, ctx->f0.fl);
    // 0x8004A598: lwc1        $f28, 0xA0($sp)
    ctx->f28.u32l = MEM_W(ctx->r29, 0XA0);
    // 0x8004A59C: neg.s       $f20, $f14
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f14.fl); 
    ctx->f20.fl = -ctx->f14.fl;
    // 0x8004A5A0: mul.s       $f12, $f28, $f20
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 28);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f28.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f12.fl = MUL_S(ctx->f28.fl, ctx->f20.fl);
    // 0x8004A5A4: neg.s       $f6, $f12
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f12.fl); 
    ctx->f6.fl = -ctx->f12.fl;
    // 0x8004A5A8: swc1        $f12, 0x8($s0)
    MEM_W(0X8, ctx->r16) = ctx->f12.u32l;
    // 0x8004A5AC: swc1        $f6, 0x20($s0)
    MEM_W(0X20, ctx->r16) = ctx->f6.u32l;
    // 0x8004A5B0: lwc1        $f8, 0xB8($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0XB8);
    // 0x8004A5B4: swc1        $f26, 0x28($s0)
    MEM_W(0X28, ctx->r16) = ctx->f26.u32l;
    // 0x8004A5B8: div.s       $f2, $f8, $f0
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f2.fl = DIV_S(ctx->f8.fl, ctx->f0.fl);
    // 0x8004A5BC: mul.s       $f16, $f28, $f2
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 28);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f28.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f16.fl = MUL_S(ctx->f28.fl, ctx->f2.fl);
    // 0x8004A5C0: nop

    // 0x8004A5C4: mul.s       $f18, $f26, $f20
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f26.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f18.fl = MUL_S(ctx->f26.fl, ctx->f20.fl);
    // 0x8004A5C8: neg.s       $f10, $f16
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f16.fl); 
    ctx->f10.fl = -ctx->f16.fl;
    // 0x8004A5CC: swc1        $f16, 0x18($s0)
    MEM_W(0X18, ctx->r16) = ctx->f16.u32l;
    // 0x8004A5D0: swc1        $f10, 0x24($s0)
    MEM_W(0X24, ctx->r16) = ctx->f10.u32l;
    // 0x8004A5D4: mul.s       $f4, $f18, $f20
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f4.fl = MUL_S(ctx->f18.fl, ctx->f20.fl);
    // 0x8004A5D8: nop

    // 0x8004A5DC: mul.s       $f6, $f2, $f2
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f6.fl = MUL_S(ctx->f2.fl, ctx->f2.fl);
    // 0x8004A5E0: nop

    // 0x8004A5E4: mul.s       $f10, $f26, $f2
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f26.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f10.fl = MUL_S(ctx->f26.fl, ctx->f2.fl);
    // 0x8004A5E8: add.s       $f8, $f4, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = ctx->f4.fl + ctx->f6.fl;
    // 0x8004A5EC: mul.s       $f4, $f10, $f2
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f4.fl = MUL_S(ctx->f10.fl, ctx->f2.fl);
    // 0x8004A5F0: swc1        $f8, 0x0($s0)
    MEM_W(0X0, ctx->r16) = ctx->f8.u32l;
    // 0x8004A5F4: mul.s       $f6, $f14, $f14
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f6.fl = MUL_S(ctx->f14.fl, ctx->f14.fl);
    // 0x8004A5F8: add.s       $f8, $f4, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = ctx->f4.fl + ctx->f6.fl;
    // 0x8004A5FC: mul.s       $f10, $f18, $f2
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f10.fl = MUL_S(ctx->f18.fl, ctx->f2.fl);
    // 0x8004A600: nop

    // 0x8004A604: mul.s       $f4, $f2, $f14
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f4.fl = MUL_S(ctx->f2.fl, ctx->f14.fl);
    // 0x8004A608: swc1        $f8, 0x14($s0)
    MEM_W(0X14, ctx->r16) = ctx->f8.u32l;
    // 0x8004A60C: add.s       $f22, $f10, $f4
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f22.fl = ctx->f10.fl + ctx->f4.fl;
    // 0x8004A610: swc1        $f22, 0x10($s0)
    MEM_W(0X10, ctx->r16) = ctx->f22.u32l;
    // 0x8004A614: b           L_8004A854
    // 0x8004A618: swc1        $f22, 0x4($s0)
    MEM_W(0X4, ctx->r16) = ctx->f22.u32l;
        goto L_8004A854;
    // 0x8004A618: swc1        $f22, 0x4($s0)
    MEM_W(0X4, ctx->r16) = ctx->f22.u32l;
    // 0x8004A61C: c.eq.s      $f14, $f0
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 0);
    c1cs = ctx->f14.fl == ctx->f0.fl;
L_8004A620:
    // 0x8004A620: nop

    // 0x8004A624: bc1f        L_8004A6C0
    if (!c1cs) {
        // 0x8004A628: nop
    
            goto L_8004A6C0;
    }
    // 0x8004A628: nop

    // 0x8004A62C: mul.s       $f6, $f24, $f24
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 24);
    NAN_CHECK(ctx->f24.fl); NAN_CHECK(ctx->f24.fl); 
    ctx->f6.fl = MUL_S(ctx->f24.fl, ctx->f24.fl);
    // 0x8004A630: nop

    // 0x8004A634: mul.s       $f8, $f28, $f28
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 28);
    CHECK_FR(ctx, 28);
    NAN_CHECK(ctx->f28.fl); NAN_CHECK(ctx->f28.fl); 
    ctx->f8.fl = MUL_S(ctx->f28.fl, ctx->f28.fl);
    // 0x8004A638: jal         0x800C7010
    // 0x8004A63C: add.s       $f12, $f6, $f8
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f12.fl = ctx->f6.fl + ctx->f8.fl;
    _nsqrtf(rdram, ctx);
        goto after_4;
    // 0x8004A63C: add.s       $f12, $f6, $f8
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f12.fl = ctx->f6.fl + ctx->f8.fl;
    after_4:
    // 0x8004A640: div.s       $f12, $f28, $f0
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 28);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f28.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f12.fl = DIV_S(ctx->f28.fl, ctx->f0.fl);
    // 0x8004A644: lwc1        $f30, 0xA0($sp)
    ctx->f30.u32l = MEM_W(ctx->r29, 0XA0);
    // 0x8004A648: swc1        $f26, 0x0($s0)
    MEM_W(0X0, ctx->r16) = ctx->f26.u32l;
    // 0x8004A64C: div.s       $f14, $f24, $f0
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f24.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f14.fl = DIV_S(ctx->f24.fl, ctx->f0.fl);
    // 0x8004A650: neg.s       $f2, $f12
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f12.fl); 
    ctx->f2.fl = -ctx->f12.fl;
    // 0x8004A654: mul.s       $f16, $f30, $f2
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 30);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f30.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f16.fl = MUL_S(ctx->f30.fl, ctx->f2.fl);
    // 0x8004A658: swc1        $f16, 0x10($s0)
    MEM_W(0X10, ctx->r16) = ctx->f16.u32l;
    // 0x8004A65C: neg.s       $f10, $f16
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f16.fl); 
    ctx->f10.fl = -ctx->f16.fl;
    // 0x8004A660: mul.s       $f18, $f30, $f14
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 30);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f30.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f18.fl = MUL_S(ctx->f30.fl, ctx->f14.fl);
    // 0x8004A664: swc1        $f10, 0x4($s0)
    MEM_W(0X4, ctx->r16) = ctx->f10.u32l;
    // 0x8004A668: mul.s       $f20, $f26, $f2
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f26.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f20.fl = MUL_S(ctx->f26.fl, ctx->f2.fl);
    // 0x8004A66C: neg.s       $f4, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f18.fl); 
    ctx->f4.fl = -ctx->f18.fl;
    // 0x8004A670: swc1        $f18, 0x20($s0)
    MEM_W(0X20, ctx->r16) = ctx->f18.u32l;
    // 0x8004A674: swc1        $f4, 0x8($s0)
    MEM_W(0X8, ctx->r16) = ctx->f4.u32l;
    // 0x8004A678: mul.s       $f6, $f20, $f2
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f6.fl = MUL_S(ctx->f20.fl, ctx->f2.fl);
    // 0x8004A67C: nop

    // 0x8004A680: mul.s       $f8, $f14, $f14
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f8.fl = MUL_S(ctx->f14.fl, ctx->f14.fl);
    // 0x8004A684: nop

    // 0x8004A688: mul.s       $f4, $f26, $f14
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f26.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f4.fl = MUL_S(ctx->f26.fl, ctx->f14.fl);
    // 0x8004A68C: add.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = ctx->f6.fl + ctx->f8.fl;
    // 0x8004A690: mul.s       $f6, $f4, $f14
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f6.fl = MUL_S(ctx->f4.fl, ctx->f14.fl);
    // 0x8004A694: swc1        $f10, 0x14($s0)
    MEM_W(0X14, ctx->r16) = ctx->f10.u32l;
    // 0x8004A698: mul.s       $f8, $f12, $f12
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f8.fl = MUL_S(ctx->f12.fl, ctx->f12.fl);
    // 0x8004A69C: add.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = ctx->f6.fl + ctx->f8.fl;
    // 0x8004A6A0: mul.s       $f4, $f20, $f14
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f4.fl = MUL_S(ctx->f20.fl, ctx->f14.fl);
    // 0x8004A6A4: nop

    // 0x8004A6A8: mul.s       $f6, $f14, $f12
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f6.fl = MUL_S(ctx->f14.fl, ctx->f12.fl);
    // 0x8004A6AC: swc1        $f10, 0x28($s0)
    MEM_W(0X28, ctx->r16) = ctx->f10.u32l;
    // 0x8004A6B0: add.s       $f22, $f4, $f6
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f22.fl = ctx->f4.fl + ctx->f6.fl;
    // 0x8004A6B4: swc1        $f22, 0x24($s0)
    MEM_W(0X24, ctx->r16) = ctx->f22.u32l;
    // 0x8004A6B8: b           L_8004A854
    // 0x8004A6BC: swc1        $f22, 0x18($s0)
    MEM_W(0X18, ctx->r16) = ctx->f22.u32l;
        goto L_8004A854;
    // 0x8004A6BC: swc1        $f22, 0x18($s0)
    MEM_W(0X18, ctx->r16) = ctx->f22.u32l;
L_8004A6C0:
    // 0x8004A6C0: mul.s       $f8, $f14, $f14
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f8.fl = MUL_S(ctx->f14.fl, ctx->f14.fl);
    // 0x8004A6C4: swc1        $f14, 0xB8($sp)
    MEM_W(0XB8, ctx->r29) = ctx->f14.u32l;
    // 0x8004A6C8: mul.s       $f10, $f24, $f24
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 24);
    NAN_CHECK(ctx->f24.fl); NAN_CHECK(ctx->f24.fl); 
    ctx->f10.fl = MUL_S(ctx->f24.fl, ctx->f24.fl);
    // 0x8004A6CC: add.s       $f4, $f8, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f4.fl = ctx->f8.fl + ctx->f10.fl;
    // 0x8004A6D0: mul.s       $f6, $f28, $f28
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 28);
    CHECK_FR(ctx, 28);
    NAN_CHECK(ctx->f28.fl); NAN_CHECK(ctx->f28.fl); 
    ctx->f6.fl = MUL_S(ctx->f28.fl, ctx->f28.fl);
    // 0x8004A6D4: jal         0x800C7010
    // 0x8004A6D8: add.s       $f12, $f4, $f6
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f12.fl = ctx->f4.fl + ctx->f6.fl;
    _nsqrtf(rdram, ctx);
        goto after_5;
    // 0x8004A6D8: add.s       $f12, $f4, $f6
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f12.fl = ctx->f4.fl + ctx->f6.fl;
    after_5:
    // 0x8004A6DC: div.s       $f30, $f24, $f0
    CHECK_FR(ctx, 30);
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f24.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f30.fl = DIV_S(ctx->f24.fl, ctx->f0.fl);
    // 0x8004A6E0: lwc1        $f8, 0xB8($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0XB8);
    // 0x8004A6E4: lwc1        $f10, 0xC0($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0XC0);
    // 0x8004A6E8: div.s       $f28, $f8, $f0
    CHECK_FR(ctx, 28);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f28.fl = DIV_S(ctx->f8.fl, ctx->f0.fl);
    // 0x8004A6EC: neg.s       $f16, $f30
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 30);
    NAN_CHECK(ctx->f30.fl); 
    ctx->f16.fl = -ctx->f30.fl;
    // 0x8004A6F0: mul.s       $f4, $f16, $f16
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f4.fl = MUL_S(ctx->f16.fl, ctx->f16.fl);
    // 0x8004A6F4: swc1        $f16, 0x90($sp)
    MEM_W(0X90, ctx->r29) = ctx->f16.u32l;
    // 0x8004A6F8: div.s       $f22, $f10, $f0
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f22.fl = DIV_S(ctx->f10.fl, ctx->f0.fl);
    // 0x8004A6FC: swc1        $f28, 0x8C($sp)
    MEM_W(0X8C, ctx->r29) = ctx->f28.u32l;
    // 0x8004A700: mul.s       $f6, $f28, $f28
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 28);
    CHECK_FR(ctx, 28);
    NAN_CHECK(ctx->f28.fl); NAN_CHECK(ctx->f28.fl); 
    ctx->f6.fl = MUL_S(ctx->f28.fl, ctx->f28.fl);
    // 0x8004A704: jal         0x800C7010
    // 0x8004A708: add.s       $f12, $f4, $f6
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f12.fl = ctx->f4.fl + ctx->f6.fl;
    _nsqrtf(rdram, ctx);
        goto after_6;
    // 0x8004A708: add.s       $f12, $f4, $f6
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f12.fl = ctx->f4.fl + ctx->f6.fl;
    after_6:
    // 0x8004A70C: lwc1        $f18, 0x8C($sp)
    ctx->f18.u32l = MEM_W(ctx->r29, 0X8C);
    // 0x8004A710: lwc1        $f16, 0x90($sp)
    ctx->f16.u32l = MEM_W(ctx->r29, 0X90);
    // 0x8004A714: div.s       $f18, $f18, $f0
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f18.fl = DIV_S(ctx->f18.fl, ctx->f0.fl);
    // 0x8004A718: div.s       $f16, $f16, $f0
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f16.fl = DIV_S(ctx->f16.fl, ctx->f0.fl);
    // 0x8004A71C: sub.s       $f8, $f30, $f18
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 30);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f30.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f8.fl = ctx->f30.fl - ctx->f18.fl;
    // 0x8004A720: sub.s       $f4, $f28, $f16
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 28);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f28.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f4.fl = ctx->f28.fl - ctx->f16.fl;
    // 0x8004A724: mul.s       $f10, $f8, $f16
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f10.fl = MUL_S(ctx->f8.fl, ctx->f16.fl);
    // 0x8004A728: nop

    // 0x8004A72C: mul.s       $f6, $f18, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = MUL_S(ctx->f18.fl, ctx->f4.fl);
    // 0x8004A730: nop

    // 0x8004A734: mul.s       $f2, $f18, $f22
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f2.fl = MUL_S(ctx->f18.fl, ctx->f22.fl);
    // 0x8004A738: sub.s       $f20, $f10, $f6
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f20.fl = ctx->f10.fl - ctx->f6.fl;
    // 0x8004A73C: mul.s       $f8, $f2, $f2
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f8.fl = MUL_S(ctx->f2.fl, ctx->f2.fl);
    // 0x8004A740: swc1        $f20, 0x94($sp)
    MEM_W(0X94, ctx->r29) = ctx->f20.u32l;
    // 0x8004A744: mul.s       $f4, $f16, $f16
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f4.fl = MUL_S(ctx->f16.fl, ctx->f16.fl);
    // 0x8004A748: add.s       $f10, $f8, $f4
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f10.fl = ctx->f8.fl + ctx->f4.fl;
    // 0x8004A74C: mul.s       $f6, $f10, $f26
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 26);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f26.fl); 
    ctx->f6.fl = MUL_S(ctx->f10.fl, ctx->f26.fl);
    // 0x8004A750: neg.s       $f10, $f16
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f16.fl); 
    ctx->f10.fl = -ctx->f16.fl;
    // 0x8004A754: mul.s       $f8, $f28, $f28
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 28);
    CHECK_FR(ctx, 28);
    NAN_CHECK(ctx->f28.fl); NAN_CHECK(ctx->f28.fl); 
    ctx->f8.fl = MUL_S(ctx->f28.fl, ctx->f28.fl);
    // 0x8004A758: nop

    // 0x8004A75C: mul.s       $f12, $f10, $f22
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f12.fl = MUL_S(ctx->f10.fl, ctx->f22.fl);
    // 0x8004A760: add.s       $f4, $f6, $f8
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f4.fl = ctx->f6.fl + ctx->f8.fl;
    // 0x8004A764: mul.s       $f6, $f12, $f12
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f6.fl = MUL_S(ctx->f12.fl, ctx->f12.fl);
    // 0x8004A768: swc1        $f4, 0x0($s0)
    MEM_W(0X0, ctx->r16) = ctx->f4.u32l;
    // 0x8004A76C: mul.s       $f8, $f18, $f18
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f8.fl = MUL_S(ctx->f18.fl, ctx->f18.fl);
    // 0x8004A770: add.s       $f4, $f6, $f8
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f4.fl = ctx->f6.fl + ctx->f8.fl;
    // 0x8004A774: mul.s       $f10, $f4, $f26
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 26);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f26.fl); 
    ctx->f10.fl = MUL_S(ctx->f4.fl, ctx->f26.fl);
    // 0x8004A778: nop

    // 0x8004A77C: mul.s       $f6, $f30, $f30
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 30);
    CHECK_FR(ctx, 30);
    NAN_CHECK(ctx->f30.fl); NAN_CHECK(ctx->f30.fl); 
    ctx->f6.fl = MUL_S(ctx->f30.fl, ctx->f30.fl);
    // 0x8004A780: nop

    // 0x8004A784: mul.s       $f4, $f26, $f20
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f26.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f4.fl = MUL_S(ctx->f26.fl, ctx->f20.fl);
    // 0x8004A788: add.s       $f8, $f10, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = ctx->f10.fl + ctx->f6.fl;
    // 0x8004A78C: mul.s       $f10, $f4, $f20
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f10.fl = MUL_S(ctx->f4.fl, ctx->f20.fl);
    // 0x8004A790: swc1        $f8, 0x14($s0)
    MEM_W(0X14, ctx->r16) = ctx->f8.u32l;
    // 0x8004A794: mul.s       $f6, $f22, $f22
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f6.fl = MUL_S(ctx->f22.fl, ctx->f22.fl);
    // 0x8004A798: add.s       $f8, $f10, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = ctx->f10.fl + ctx->f6.fl;
    // 0x8004A79C: mul.s       $f4, $f2, $f12
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f4.fl = MUL_S(ctx->f2.fl, ctx->f12.fl);
    // 0x8004A7A0: nop

    // 0x8004A7A4: mul.s       $f10, $f16, $f18
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f10.fl = MUL_S(ctx->f16.fl, ctx->f18.fl);
    // 0x8004A7A8: swc1        $f8, 0x28($s0)
    MEM_W(0X28, ctx->r16) = ctx->f8.u32l;
    // 0x8004A7AC: add.s       $f6, $f4, $f10
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f6.fl = ctx->f4.fl + ctx->f10.fl;
    // 0x8004A7B0: mul.s       $f8, $f6, $f26
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 26);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f26.fl); 
    ctx->f8.fl = MUL_S(ctx->f6.fl, ctx->f26.fl);
    // 0x8004A7B4: nop

    // 0x8004A7B8: mul.s       $f4, $f28, $f30
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 28);
    CHECK_FR(ctx, 30);
    NAN_CHECK(ctx->f28.fl); NAN_CHECK(ctx->f30.fl); 
    ctx->f4.fl = MUL_S(ctx->f28.fl, ctx->f30.fl);
    // 0x8004A7BC: nop

    // 0x8004A7C0: mul.s       $f10, $f12, $f16
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f10.fl = MUL_S(ctx->f12.fl, ctx->f16.fl);
    // 0x8004A7C4: nop

    // 0x8004A7C8: mul.s       $f6, $f2, $f18
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f6.fl = MUL_S(ctx->f2.fl, ctx->f18.fl);
    // 0x8004A7CC: add.s       $f0, $f8, $f4
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f0.fl = ctx->f8.fl + ctx->f4.fl;
    // 0x8004A7D0: lwc1        $f4, 0xA0($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0XA0);
    // 0x8004A7D4: sub.s       $f8, $f10, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = ctx->f10.fl - ctx->f6.fl;
    // 0x8004A7D8: mul.s       $f14, $f8, $f4
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f14.fl = MUL_S(ctx->f8.fl, ctx->f4.fl);
    // 0x8004A7DC: add.s       $f10, $f0, $f14
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f10.fl = ctx->f0.fl + ctx->f14.fl;
    // 0x8004A7E0: mul.s       $f8, $f26, $f2
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f26.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f8.fl = MUL_S(ctx->f26.fl, ctx->f2.fl);
    // 0x8004A7E4: sub.s       $f6, $f0, $f14
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f6.fl = ctx->f0.fl - ctx->f14.fl;
    // 0x8004A7E8: swc1        $f10, 0x10($s0)
    MEM_W(0X10, ctx->r16) = ctx->f10.u32l;
    // 0x8004A7EC: swc1        $f6, 0x4($s0)
    MEM_W(0X4, ctx->r16) = ctx->f6.u32l;
    // 0x8004A7F0: lwc1        $f4, 0x94($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X94);
    // 0x8004A7F4: mul.s       $f10, $f8, $f4
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f10.fl = MUL_S(ctx->f8.fl, ctx->f4.fl);
    // 0x8004A7F8: lwc1        $f8, 0xA0($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0XA0);
    // 0x8004A7FC: mul.s       $f6, $f28, $f22
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 28);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f28.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f6.fl = MUL_S(ctx->f28.fl, ctx->f22.fl);
    // 0x8004A800: nop

    // 0x8004A804: mul.s       $f0, $f8, $f4
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f0.fl = MUL_S(ctx->f8.fl, ctx->f4.fl);
    // 0x8004A808: add.s       $f24, $f10, $f6
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f24.fl = ctx->f10.fl + ctx->f6.fl;
    // 0x8004A80C: mul.s       $f14, $f0, $f16
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f14.fl = MUL_S(ctx->f0.fl, ctx->f16.fl);
    // 0x8004A810: add.s       $f10, $f24, $f14
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f24.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f10.fl = ctx->f24.fl + ctx->f14.fl;
    // 0x8004A814: mul.s       $f8, $f26, $f12
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f26.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f8.fl = MUL_S(ctx->f26.fl, ctx->f12.fl);
    // 0x8004A818: sub.s       $f6, $f24, $f14
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f24.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f6.fl = ctx->f24.fl - ctx->f14.fl;
    // 0x8004A81C: swc1        $f10, 0x20($s0)
    MEM_W(0X20, ctx->r16) = ctx->f10.u32l;
    // 0x8004A820: swc1        $f6, 0x8($s0)
    MEM_W(0X8, ctx->r16) = ctx->f6.u32l;
    // 0x8004A824: lwc1        $f4, 0x94($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X94);
    // 0x8004A828: mul.s       $f10, $f8, $f4
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f10.fl = MUL_S(ctx->f8.fl, ctx->f4.fl);
    // 0x8004A82C: nop

    // 0x8004A830: mul.s       $f6, $f30, $f22
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 30);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f30.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f6.fl = MUL_S(ctx->f30.fl, ctx->f22.fl);
    // 0x8004A834: add.s       $f8, $f10, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = ctx->f10.fl + ctx->f6.fl;
    // 0x8004A838: mul.s       $f20, $f0, $f18
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f20.fl = MUL_S(ctx->f0.fl, ctx->f18.fl);
    // 0x8004A83C: swc1        $f8, 0x5C($sp)
    MEM_W(0X5C, ctx->r29) = ctx->f8.u32l;
    // 0x8004A840: add.s       $f4, $f8, $f20
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f4.fl = ctx->f8.fl + ctx->f20.fl;
    // 0x8004A844: swc1        $f4, 0x24($s0)
    MEM_W(0X24, ctx->r16) = ctx->f4.u32l;
    // 0x8004A848: lwc1        $f10, 0x5C($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0X5C);
    // 0x8004A84C: sub.s       $f6, $f10, $f20
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f6.fl = ctx->f10.fl - ctx->f20.fl;
    // 0x8004A850: swc1        $f6, 0x18($s0)
    MEM_W(0X18, ctx->r16) = ctx->f6.u32l;
L_8004A854:
    // 0x8004A854: mtc1        $zero, $f0
    ctx->f0.u32l = 0;
    // 0x8004A858: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x8004A85C: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x8004A860: swc1        $f0, 0x2C($s0)
    MEM_W(0X2C, ctx->r16) = ctx->f0.u32l;
    // 0x8004A864: swc1        $f0, 0x1C($s0)
    MEM_W(0X1C, ctx->r16) = ctx->f0.u32l;
    // 0x8004A868: swc1        $f0, 0xC($s0)
    MEM_W(0XC, ctx->r16) = ctx->f0.u32l;
    // 0x8004A86C: swc1        $f0, 0x38($s0)
    MEM_W(0X38, ctx->r16) = ctx->f0.u32l;
    // 0x8004A870: swc1        $f0, 0x34($s0)
    MEM_W(0X34, ctx->r16) = ctx->f0.u32l;
    // 0x8004A874: swc1        $f0, 0x30($s0)
    MEM_W(0X30, ctx->r16) = ctx->f0.u32l;
    // 0x8004A878: swc1        $f8, 0x3C($s0)
    MEM_W(0X3C, ctx->r16) = ctx->f8.u32l;
    // 0x8004A87C: lw          $a1, 0xB0($sp)
    ctx->r5 = MEM_W(ctx->r29, 0XB0);
    // 0x8004A880: jal         0x80047EE0
    // 0x8004A884: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    SysUtils_MtxFToMtx(rdram, ctx);
        goto after_7;
    // 0x8004A884: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_7:
    // 0x8004A888: lw          $ra, 0x54($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X54);
L_8004A88C:
    // 0x8004A88C: ldc1        $f20, 0x20($sp)
    CHECK_FR(ctx, 20);
    ctx->f20.u64 = LD(ctx->r29, 0X20);
    // 0x8004A890: ldc1        $f22, 0x28($sp)
    CHECK_FR(ctx, 22);
    ctx->f22.u64 = LD(ctx->r29, 0X28);
    // 0x8004A894: ldc1        $f24, 0x30($sp)
    CHECK_FR(ctx, 24);
    ctx->f24.u64 = LD(ctx->r29, 0X30);
    // 0x8004A898: ldc1        $f26, 0x38($sp)
    CHECK_FR(ctx, 26);
    ctx->f26.u64 = LD(ctx->r29, 0X38);
    // 0x8004A89C: ldc1        $f28, 0x40($sp)
    CHECK_FR(ctx, 28);
    ctx->f28.u64 = LD(ctx->r29, 0X40);
    // 0x8004A8A0: ldc1        $f30, 0x48($sp)
    CHECK_FR(ctx, 30);
    ctx->f30.u64 = LD(ctx->r29, 0X48);
    // 0x8004A8A4: lw          $s0, 0x50($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X50);
    // 0x8004A8A8: jr          $ra
    // 0x8004A8AC: addiu       $sp, $sp, 0xB0
    ctx->r29 = ADD32(ctx->r29, 0XB0);
    return;
    // 0x8004A8AC: addiu       $sp, $sp, 0xB0
    ctx->r29 = ADD32(ctx->r29, 0XB0);
;}
RECOMP_FUNC void func_8004A8B0(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8004A8B0: lui         $t6, 0x800D
    ctx->r14 = S32(0X800D << 16);
    // 0x8004A8B4: lh          $t6, 0x4644($t6)
    ctx->r14 = MEM_H(ctx->r14, 0X4644);
    // 0x8004A8B8: addiu       $sp, $sp, -0x10
    ctx->r29 = ADD32(ctx->r29, -0X10);
    // 0x8004A8BC: sw          $s2, 0xC($sp)
    MEM_W(0XC, ctx->r29) = ctx->r18;
    // 0x8004A8C0: sw          $s1, 0x8($sp)
    MEM_W(0X8, ctx->r29) = ctx->r17;
    // 0x8004A8C4: sw          $s0, 0x4($sp)
    MEM_W(0X4, ctx->r29) = ctx->r16;
    // 0x8004A8C8: beq         $t6, $zero, L_8004AB58
    if (ctx->r14 == 0) {
        // 0x8004A8CC: or          $a3, $a0, $zero
        ctx->r7 = ctx->r4 | 0;
            goto L_8004AB58;
    }
    // 0x8004A8CC: or          $a3, $a0, $zero
    ctx->r7 = ctx->r4 | 0;
    // 0x8004A8D0: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
    // 0x8004A8D4: addiu       $t3, $zero, 0x3
    ctx->r11 = ADD32(0, 0X3);
    // 0x8004A8D8: div         $zero, $v1, $t3
    lo = S32(S64(S32(ctx->r3)) / S64(S32(ctx->r11))); hi = S32(S64(S32(ctx->r3)) % S64(S32(ctx->r11)));
    // 0x8004A8DC: sll         $t7, $zero, 11
    ctx->r15 = S32(0 << 11);
    // 0x8004A8E0: bgez        $v1, L_8004A8F0
    if (SIGNED(ctx->r3) >= 0) {
        // 0x8004A8E4: sra         $t8, $v1, 1
        ctx->r24 = S32(SIGNED(ctx->r3) >> 1);
            goto L_8004A8F0;
    }
    // 0x8004A8E4: sra         $t8, $v1, 1
    ctx->r24 = S32(SIGNED(ctx->r3) >> 1);
    // 0x8004A8E8: addiu       $at, $v1, 0x1
    ctx->r1 = ADD32(ctx->r3, 0X1);
    // 0x8004A8EC: sra         $t8, $at, 1
    ctx->r24 = S32(SIGNED(ctx->r1) >> 1);
L_8004A8F0:
    // 0x8004A8F0: sll         $t9, $t8, 6
    ctx->r25 = S32(ctx->r24 << 6);
    // 0x8004A8F4: or          $t6, $t7, $t9
    ctx->r14 = ctx->r15 | ctx->r25;
    // 0x8004A8F8: bne         $t3, $zero, L_8004A904
    if (ctx->r11 != 0) {
        // 0x8004A8FC: nop
    
            goto L_8004A904;
    }
    // 0x8004A8FC: nop

    // 0x8004A900: break       7
    do_break(2147789056);
L_8004A904:
    // 0x8004A904: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x8004A908: bne         $t3, $at, L_8004A91C
    if (ctx->r11 != ctx->r1) {
        // 0x8004A90C: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_8004A91C;
    }
    // 0x8004A90C: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x8004A910: bne         $v1, $at, L_8004A91C
    if (ctx->r3 != ctx->r1) {
        // 0x8004A914: nop
    
            goto L_8004A91C;
    }
    // 0x8004A914: nop

    // 0x8004A918: break       6
    do_break(2147789080);
L_8004A91C:
    // 0x8004A91C: mflo        $t8
    ctx->r24 = lo;
    // 0x8004A920: sll         $t7, $t8, 1
    ctx->r15 = S32(ctx->r24 << 1);
    // 0x8004A924: or          $t9, $t6, $t7
    ctx->r25 = ctx->r14 | ctx->r15;
    // 0x8004A928: ori         $t8, $t9, 0x1
    ctx->r24 = ctx->r25 | 0X1;
    // 0x8004A92C: lui         $at, 0x8016
    ctx->r1 = S32(0X8016 << 16);
    // 0x8004A930: lui         $a2, 0x8016
    ctx->r6 = S32(0X8016 << 16);
    // 0x8004A934: addiu       $a2, $a2, -0x7CAE
    ctx->r6 = ADD32(ctx->r6, -0X7CAE);
    // 0x8004A938: sh          $t8, -0x7CB0($at)
    MEM_H(-0X7CB0, ctx->r1) = ctx->r24;
    // 0x8004A93C: addiu       $a0, $zero, 0x2
    ctx->r4 = ADD32(0, 0X2);
    // 0x8004A940: addiu       $a1, $zero, -0x6A
    ctx->r5 = ADD32(0, -0X6A);
    // 0x8004A944: addiu       $t0, $zero, -0x68
    ctx->r8 = ADD32(0, -0X68);
    // 0x8004A948: addiu       $t1, $zero, -0x66
    ctx->r9 = ADD32(0, -0X66);
    // 0x8004A94C: addiu       $t2, $zero, -0x64
    ctx->r10 = ADD32(0, -0X64);
    // 0x8004A950: addiu       $v0, $zero, 0x94
    ctx->r2 = ADD32(0, 0X94);
L_8004A954:
    // 0x8004A954: slti        $at, $a0, 0x8C
    ctx->r1 = SIGNED(ctx->r4) < 0X8C ? 1 : 0;
    // 0x8004A958: bne         $at, $zero, L_8004A968
    if (ctx->r1 != 0) {
        // 0x8004A95C: or          $v1, $a1, $zero
        ctx->r3 = ctx->r5 | 0;
            goto L_8004A968;
    }
    // 0x8004A95C: or          $v1, $a1, $zero
    ctx->r3 = ctx->r5 | 0;
    // 0x8004A960: b           L_8004A974
    // 0x8004A964: addiu       $v1, $zero, 0x1F
    ctx->r3 = ADD32(0, 0X1F);
        goto L_8004A974;
    // 0x8004A964: addiu       $v1, $zero, 0x1F
    ctx->r3 = ADD32(0, 0X1F);
L_8004A968:
    // 0x8004A968: bgez        $a1, L_8004A974
    if (SIGNED(ctx->r5) >= 0) {
        // 0x8004A96C: nop
    
            goto L_8004A974;
    }
    // 0x8004A96C: nop

    // 0x8004A970: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
L_8004A974:
    // 0x8004A974: div         $zero, $v1, $t3
    lo = S32(S64(S32(ctx->r3)) / S64(S32(ctx->r11))); hi = S32(S64(S32(ctx->r3)) % S64(S32(ctx->r11)));
    // 0x8004A978: sll         $t6, $v1, 11
    ctx->r14 = S32(ctx->r3 << 11);
    // 0x8004A97C: bgez        $v1, L_8004A98C
    if (SIGNED(ctx->r3) >= 0) {
        // 0x8004A980: sra         $t7, $v1, 1
        ctx->r15 = S32(SIGNED(ctx->r3) >> 1);
            goto L_8004A98C;
    }
    // 0x8004A980: sra         $t7, $v1, 1
    ctx->r15 = S32(SIGNED(ctx->r3) >> 1);
    // 0x8004A984: addiu       $at, $v1, 0x1
    ctx->r1 = ADD32(ctx->r3, 0X1);
    // 0x8004A988: sra         $t7, $at, 1
    ctx->r15 = S32(SIGNED(ctx->r1) >> 1);
L_8004A98C:
    // 0x8004A98C: sll         $t9, $t7, 6
    ctx->r25 = S32(ctx->r15 << 6);
    // 0x8004A990: or          $t8, $t6, $t9
    ctx->r24 = ctx->r14 | ctx->r25;
    // 0x8004A994: bne         $t3, $zero, L_8004A9A0
    if (ctx->r11 != 0) {
        // 0x8004A998: nop
    
            goto L_8004A9A0;
    }
    // 0x8004A998: nop

    // 0x8004A99C: break       7
    do_break(2147789212);
L_8004A9A0:
    // 0x8004A9A0: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x8004A9A4: bne         $t3, $at, L_8004A9B8
    if (ctx->r11 != ctx->r1) {
        // 0x8004A9A8: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_8004A9B8;
    }
    // 0x8004A9A8: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x8004A9AC: bne         $v1, $at, L_8004A9B8
    if (ctx->r3 != ctx->r1) {
        // 0x8004A9B0: nop
    
            goto L_8004A9B8;
    }
    // 0x8004A9B0: nop

    // 0x8004A9B4: break       6
    do_break(2147789236);
L_8004A9B8:
    // 0x8004A9B8: mflo        $t7
    ctx->r15 = lo;
    // 0x8004A9BC: sll         $t6, $t7, 1
    ctx->r14 = S32(ctx->r15 << 1);
    // 0x8004A9C0: or          $t9, $t8, $t6
    ctx->r25 = ctx->r24 | ctx->r14;
    // 0x8004A9C4: slti        $at, $a0, 0x8A
    ctx->r1 = SIGNED(ctx->r4) < 0X8A ? 1 : 0;
    // 0x8004A9C8: ori         $t7, $t9, 0x1
    ctx->r15 = ctx->r25 | 0X1;
    // 0x8004A9CC: or          $v1, $t0, $zero
    ctx->r3 = ctx->r8 | 0;
    // 0x8004A9D0: bne         $at, $zero, L_8004A9E0
    if (ctx->r1 != 0) {
        // 0x8004A9D4: sh          $t7, 0x0($a2)
        MEM_H(0X0, ctx->r6) = ctx->r15;
            goto L_8004A9E0;
    }
    // 0x8004A9D4: sh          $t7, 0x0($a2)
    MEM_H(0X0, ctx->r6) = ctx->r15;
    // 0x8004A9D8: b           L_8004A9EC
    // 0x8004A9DC: addiu       $v1, $zero, 0x1F
    ctx->r3 = ADD32(0, 0X1F);
        goto L_8004A9EC;
    // 0x8004A9DC: addiu       $v1, $zero, 0x1F
    ctx->r3 = ADD32(0, 0X1F);
L_8004A9E0:
    // 0x8004A9E0: bgez        $t0, L_8004A9EC
    if (SIGNED(ctx->r8) >= 0) {
        // 0x8004A9E4: nop
    
            goto L_8004A9EC;
    }
    // 0x8004A9E4: nop

    // 0x8004A9E8: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
L_8004A9EC:
    // 0x8004A9EC: div         $zero, $v1, $t3
    lo = S32(S64(S32(ctx->r3)) / S64(S32(ctx->r11))); hi = S32(S64(S32(ctx->r3)) % S64(S32(ctx->r11)));
    // 0x8004A9F0: sll         $t8, $v1, 11
    ctx->r24 = S32(ctx->r3 << 11);
    // 0x8004A9F4: bgez        $v1, L_8004AA04
    if (SIGNED(ctx->r3) >= 0) {
        // 0x8004A9F8: sra         $t6, $v1, 1
        ctx->r14 = S32(SIGNED(ctx->r3) >> 1);
            goto L_8004AA04;
    }
    // 0x8004A9F8: sra         $t6, $v1, 1
    ctx->r14 = S32(SIGNED(ctx->r3) >> 1);
    // 0x8004A9FC: addiu       $at, $v1, 0x1
    ctx->r1 = ADD32(ctx->r3, 0X1);
    // 0x8004AA00: sra         $t6, $at, 1
    ctx->r14 = S32(SIGNED(ctx->r1) >> 1);
L_8004AA04:
    // 0x8004AA04: sll         $t9, $t6, 6
    ctx->r25 = S32(ctx->r14 << 6);
    // 0x8004AA08: or          $t7, $t8, $t9
    ctx->r15 = ctx->r24 | ctx->r25;
    // 0x8004AA0C: bne         $t3, $zero, L_8004AA18
    if (ctx->r11 != 0) {
        // 0x8004AA10: nop
    
            goto L_8004AA18;
    }
    // 0x8004AA10: nop

    // 0x8004AA14: break       7
    do_break(2147789332);
L_8004AA18:
    // 0x8004AA18: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x8004AA1C: bne         $t3, $at, L_8004AA30
    if (ctx->r11 != ctx->r1) {
        // 0x8004AA20: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_8004AA30;
    }
    // 0x8004AA20: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x8004AA24: bne         $v1, $at, L_8004AA30
    if (ctx->r3 != ctx->r1) {
        // 0x8004AA28: nop
    
            goto L_8004AA30;
    }
    // 0x8004AA28: nop

    // 0x8004AA2C: break       6
    do_break(2147789356);
L_8004AA30:
    // 0x8004AA30: mflo        $t6
    ctx->r14 = lo;
    // 0x8004AA34: sll         $t8, $t6, 1
    ctx->r24 = S32(ctx->r14 << 1);
    // 0x8004AA38: or          $t9, $t7, $t8
    ctx->r25 = ctx->r15 | ctx->r24;
    // 0x8004AA3C: ori         $t6, $t9, 0x1
    ctx->r14 = ctx->r25 | 0X1;
    // 0x8004AA40: slti        $at, $a0, 0x88
    ctx->r1 = SIGNED(ctx->r4) < 0X88 ? 1 : 0;
    // 0x8004AA44: sh          $t6, 0x2($a2)
    MEM_H(0X2, ctx->r6) = ctx->r14;
    // 0x8004AA48: bne         $at, $zero, L_8004AA58
    if (ctx->r1 != 0) {
        // 0x8004AA4C: or          $v1, $t1, $zero
        ctx->r3 = ctx->r9 | 0;
            goto L_8004AA58;
    }
    // 0x8004AA4C: or          $v1, $t1, $zero
    ctx->r3 = ctx->r9 | 0;
    // 0x8004AA50: b           L_8004AA64
    // 0x8004AA54: addiu       $v1, $zero, 0x1F
    ctx->r3 = ADD32(0, 0X1F);
        goto L_8004AA64;
    // 0x8004AA54: addiu       $v1, $zero, 0x1F
    ctx->r3 = ADD32(0, 0X1F);
L_8004AA58:
    // 0x8004AA58: bgez        $t1, L_8004AA64
    if (SIGNED(ctx->r9) >= 0) {
        // 0x8004AA5C: nop
    
            goto L_8004AA64;
    }
    // 0x8004AA5C: nop

    // 0x8004AA60: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
L_8004AA64:
    // 0x8004AA64: div         $zero, $v1, $t3
    lo = S32(S64(S32(ctx->r3)) / S64(S32(ctx->r11))); hi = S32(S64(S32(ctx->r3)) % S64(S32(ctx->r11)));
    // 0x8004AA68: sll         $t7, $v1, 11
    ctx->r15 = S32(ctx->r3 << 11);
    // 0x8004AA6C: bgez        $v1, L_8004AA7C
    if (SIGNED(ctx->r3) >= 0) {
        // 0x8004AA70: sra         $t8, $v1, 1
        ctx->r24 = S32(SIGNED(ctx->r3) >> 1);
            goto L_8004AA7C;
    }
    // 0x8004AA70: sra         $t8, $v1, 1
    ctx->r24 = S32(SIGNED(ctx->r3) >> 1);
    // 0x8004AA74: addiu       $at, $v1, 0x1
    ctx->r1 = ADD32(ctx->r3, 0X1);
    // 0x8004AA78: sra         $t8, $at, 1
    ctx->r24 = S32(SIGNED(ctx->r1) >> 1);
L_8004AA7C:
    // 0x8004AA7C: sll         $t9, $t8, 6
    ctx->r25 = S32(ctx->r24 << 6);
    // 0x8004AA80: or          $t6, $t7, $t9
    ctx->r14 = ctx->r15 | ctx->r25;
    // 0x8004AA84: bne         $t3, $zero, L_8004AA90
    if (ctx->r11 != 0) {
        // 0x8004AA88: nop
    
            goto L_8004AA90;
    }
    // 0x8004AA88: nop

    // 0x8004AA8C: break       7
    do_break(2147789452);
L_8004AA90:
    // 0x8004AA90: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x8004AA94: bne         $t3, $at, L_8004AAA8
    if (ctx->r11 != ctx->r1) {
        // 0x8004AA98: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_8004AAA8;
    }
    // 0x8004AA98: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x8004AA9C: bne         $v1, $at, L_8004AAA8
    if (ctx->r3 != ctx->r1) {
        // 0x8004AAA0: nop
    
            goto L_8004AAA8;
    }
    // 0x8004AAA0: nop

    // 0x8004AAA4: break       6
    do_break(2147789476);
L_8004AAA8:
    // 0x8004AAA8: mflo        $t8
    ctx->r24 = lo;
    // 0x8004AAAC: sll         $t7, $t8, 1
    ctx->r15 = S32(ctx->r24 << 1);
    // 0x8004AAB0: or          $t9, $t6, $t7
    ctx->r25 = ctx->r14 | ctx->r15;
    // 0x8004AAB4: ori         $t8, $t9, 0x1
    ctx->r24 = ctx->r25 | 0X1;
    // 0x8004AAB8: slti        $at, $a0, 0x86
    ctx->r1 = SIGNED(ctx->r4) < 0X86 ? 1 : 0;
    // 0x8004AABC: sh          $t8, 0x4($a2)
    MEM_H(0X4, ctx->r6) = ctx->r24;
    // 0x8004AAC0: bne         $at, $zero, L_8004AAD0
    if (ctx->r1 != 0) {
        // 0x8004AAC4: or          $v1, $t2, $zero
        ctx->r3 = ctx->r10 | 0;
            goto L_8004AAD0;
    }
    // 0x8004AAC4: or          $v1, $t2, $zero
    ctx->r3 = ctx->r10 | 0;
    // 0x8004AAC8: b           L_8004AADC
    // 0x8004AACC: addiu       $v1, $zero, 0x1F
    ctx->r3 = ADD32(0, 0X1F);
        goto L_8004AADC;
    // 0x8004AACC: addiu       $v1, $zero, 0x1F
    ctx->r3 = ADD32(0, 0X1F);
L_8004AAD0:
    // 0x8004AAD0: bgez        $t2, L_8004AADC
    if (SIGNED(ctx->r10) >= 0) {
        // 0x8004AAD4: nop
    
            goto L_8004AADC;
    }
    // 0x8004AAD4: nop

    // 0x8004AAD8: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
L_8004AADC:
    // 0x8004AADC: div         $zero, $v1, $t3
    lo = S32(S64(S32(ctx->r3)) / S64(S32(ctx->r11))); hi = S32(S64(S32(ctx->r3)) % S64(S32(ctx->r11)));
    // 0x8004AAE0: sll         $t6, $v1, 11
    ctx->r14 = S32(ctx->r3 << 11);
    // 0x8004AAE4: bgez        $v1, L_8004AAF4
    if (SIGNED(ctx->r3) >= 0) {
        // 0x8004AAE8: sra         $t7, $v1, 1
        ctx->r15 = S32(SIGNED(ctx->r3) >> 1);
            goto L_8004AAF4;
    }
    // 0x8004AAE8: sra         $t7, $v1, 1
    ctx->r15 = S32(SIGNED(ctx->r3) >> 1);
    // 0x8004AAEC: addiu       $at, $v1, 0x1
    ctx->r1 = ADD32(ctx->r3, 0X1);
    // 0x8004AAF0: sra         $t7, $at, 1
    ctx->r15 = S32(SIGNED(ctx->r1) >> 1);
L_8004AAF4:
    // 0x8004AAF4: sll         $t9, $t7, 6
    ctx->r25 = S32(ctx->r15 << 6);
    // 0x8004AAF8: or          $t8, $t6, $t9
    ctx->r24 = ctx->r14 | ctx->r25;
    // 0x8004AAFC: mflo        $t7
    ctx->r15 = lo;
    // 0x8004AB00: sll         $t6, $t7, 1
    ctx->r14 = S32(ctx->r15 << 1);
    // 0x8004AB04: or          $t9, $t8, $t6
    ctx->r25 = ctx->r24 | ctx->r14;
    // 0x8004AB08: ori         $t7, $t9, 0x1
    ctx->r15 = ctx->r25 | 0X1;
    // 0x8004AB0C: bne         $t3, $zero, L_8004AB18
    if (ctx->r11 != 0) {
        // 0x8004AB10: nop
    
            goto L_8004AB18;
    }
    // 0x8004AB10: nop

    // 0x8004AB14: break       7
    do_break(2147789588);
L_8004AB18:
    // 0x8004AB18: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x8004AB1C: bne         $t3, $at, L_8004AB30
    if (ctx->r11 != ctx->r1) {
        // 0x8004AB20: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_8004AB30;
    }
    // 0x8004AB20: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x8004AB24: bne         $v1, $at, L_8004AB30
    if (ctx->r3 != ctx->r1) {
        // 0x8004AB28: nop
    
            goto L_8004AB30;
    }
    // 0x8004AB28: nop

    // 0x8004AB2C: break       6
    do_break(2147789612);
L_8004AB30:
    // 0x8004AB30: addiu       $t2, $t2, 0x8
    ctx->r10 = ADD32(ctx->r10, 0X8);
    // 0x8004AB34: sh          $t7, 0x6($a2)
    MEM_H(0X6, ctx->r6) = ctx->r15;
    // 0x8004AB38: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x8004AB3C: addiu       $a1, $a1, 0x8
    ctx->r5 = ADD32(ctx->r5, 0X8);
    // 0x8004AB40: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x8004AB44: addiu       $t0, $t0, 0x8
    ctx->r8 = ADD32(ctx->r8, 0X8);
    // 0x8004AB48: bne         $t2, $v0, L_8004A954
    if (ctx->r10 != ctx->r2) {
        // 0x8004AB4C: addiu       $t1, $t1, 0x8
        ctx->r9 = ADD32(ctx->r9, 0X8);
            goto L_8004A954;
    }
    // 0x8004AB4C: addiu       $t1, $t1, 0x8
    ctx->r9 = ADD32(ctx->r9, 0X8);
    // 0x8004AB50: lui         $at, 0x800D
    ctx->r1 = S32(0X800D << 16);
    // 0x8004AB54: sh          $zero, 0x4644($at)
    MEM_H(0X4644, ctx->r1) = 0;
L_8004AB58:
    // 0x8004AB58: addiu       $a3, $a3, 0x3200
    ctx->r7 = ADD32(ctx->r7, 0X3200);
    // 0x8004AB5C: lui         $a0, 0x8016
    ctx->r4 = S32(0X8016 << 16);
    // 0x8004AB60: lui         $s2, 0x1
    ctx->r18 = S32(0X1 << 16);
    // 0x8004AB64: lui         $s1, 0x8016
    ctx->r17 = S32(0X8016 << 16);
    // 0x8004AB68: lui         $t3, 0x1
    ctx->r11 = S32(0X1 << 16);
    // 0x8004AB6C: addiu       $a1, $a3, 0x10
    ctx->r5 = ADD32(ctx->r7, 0X10);
    // 0x8004AB70: addiu       $a2, $a3, 0x26E
    ctx->r6 = ADD32(ctx->r7, 0X26E);
    // 0x8004AB74: ori         $t3, $t3, 0x8000
    ctx->r11 = ctx->r11 | 0X8000;
    // 0x8004AB78: addiu       $s1, $s1, -0x7CB0
    ctx->r17 = ADD32(ctx->r17, -0X7CB0);
    // 0x8004AB7C: ori         $s2, $s2, 0xEC80
    ctx->r18 = ctx->r18 | 0XEC80;
    // 0x8004AB80: addiu       $a0, $a0, -0x7CB0
    ctx->r4 = ADD32(ctx->r4, -0X7CB0);
    // 0x8004AB84: addiu       $s0, $zero, 0x1C
    ctx->r16 = ADD32(0, 0X1C);
    // 0x8004AB88: addiu       $t5, $zero, 0x97
    ctx->r13 = ADD32(0, 0X97);
    // 0x8004AB8C: addiu       $t4, $zero, 0x4D
    ctx->r12 = ADD32(0, 0X4D);
    // 0x8004AB90: addu        $a3, $a1, $t3
    ctx->r7 = ADD32(ctx->r5, ctx->r11);
L_8004AB94:
    // 0x8004AB94: lhu         $v0, 0x6F00($a3)
    ctx->r2 = MEM_HU(ctx->r7, 0X6F00);
    // 0x8004AB98: addu        $t0, $a1, $s2
    ctx->r8 = ADD32(ctx->r5, ctx->r18);
    // 0x8004AB9C: or          $t1, $a1, $zero
    ctx->r9 = ctx->r5 | 0;
    // 0x8004ABA0: sra         $t8, $v0, 11
    ctx->r24 = S32(SIGNED(ctx->r2) >> 11);
    // 0x8004ABA4: multu       $t8, $t4
    result = U64(U32(ctx->r24)) * U64(U32(ctx->r12)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x8004ABA8: sra         $t9, $v0, 6
    ctx->r25 = S32(SIGNED(ctx->r2) >> 6);
    // 0x8004ABAC: andi        $t7, $t9, 0x1F
    ctx->r15 = ctx->r25 & 0X1F;
    // 0x8004ABB0: addiu       $a1, $a1, 0x2
    ctx->r5 = ADD32(ctx->r5, 0X2);
    // 0x8004ABB4: mflo        $t6
    ctx->r14 = lo;
    // 0x8004ABB8: nop

    // 0x8004ABBC: nop

    // 0x8004ABC0: multu       $t7, $t5
    result = U64(U32(ctx->r15)) * U64(U32(ctx->r13)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x8004ABC4: sra         $t7, $v0, 1
    ctx->r15 = S32(SIGNED(ctx->r2) >> 1);
    // 0x8004ABC8: mflo        $t8
    ctx->r24 = lo;
    // 0x8004ABCC: addu        $t9, $t6, $t8
    ctx->r25 = ADD32(ctx->r14, ctx->r24);
    // 0x8004ABD0: andi        $t6, $t7, 0x1F
    ctx->r14 = ctx->r15 & 0X1F;
    // 0x8004ABD4: multu       $t6, $s0
    result = U64(U32(ctx->r14)) * U64(U32(ctx->r16)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x8004ABD8: lhu         $t7, 0x7C($s1)
    ctx->r15 = MEM_HU(ctx->r17, 0X7C);
    // 0x8004ABDC: sh          $t7, 0x6F00($a3)
    MEM_H(0X6F00, ctx->r7) = ctx->r15;
    // 0x8004ABE0: mflo        $t8
    ctx->r24 = lo;
    // 0x8004ABE4: addu        $v1, $t9, $t8
    ctx->r3 = ADD32(ctx->r25, ctx->r24);
    // 0x8004ABE8: nop

L_8004ABEC:
    // 0x8004ABEC: lhu         $v0, 0x0($t0)
    ctx->r2 = MEM_HU(ctx->r8, 0X0);
    // 0x8004ABF0: addiu       $t0, $t0, -0x280
    ctx->r8 = ADD32(ctx->r8, -0X280);
    // 0x8004ABF4: sltu        $at, $t0, $t1
    ctx->r1 = ctx->r8 < ctx->r9 ? 1 : 0;
    // 0x8004ABF8: sra         $t6, $v0, 11
    ctx->r14 = S32(SIGNED(ctx->r2) >> 11);
    // 0x8004ABFC: multu       $t6, $t4
    result = U64(U32(ctx->r14)) * U64(U32(ctx->r12)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x8004AC00: sra         $t8, $v0, 6
    ctx->r24 = S32(SIGNED(ctx->r2) >> 6);
    // 0x8004AC04: andi        $t7, $t8, 0x1F
    ctx->r15 = ctx->r24 & 0X1F;
    // 0x8004AC08: mflo        $t9
    ctx->r25 = lo;
    // 0x8004AC0C: nop

    // 0x8004AC10: nop

    // 0x8004AC14: multu       $t7, $t5
    result = U64(U32(ctx->r15)) * U64(U32(ctx->r13)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x8004AC18: sra         $t7, $v0, 1
    ctx->r15 = S32(SIGNED(ctx->r2) >> 1);
    // 0x8004AC1C: mflo        $t6
    ctx->r14 = lo;
    // 0x8004AC20: addu        $t8, $t9, $t6
    ctx->r24 = ADD32(ctx->r25, ctx->r14);
    // 0x8004AC24: andi        $t9, $t7, 0x1F
    ctx->r25 = ctx->r15 & 0X1F;
    // 0x8004AC28: multu       $t9, $s0
    result = U64(U32(ctx->r25)) * U64(U32(ctx->r16)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x8004AC2C: mflo        $t6
    ctx->r14 = lo;
    // 0x8004AC30: addu        $a3, $t8, $t6
    ctx->r7 = ADD32(ctx->r24, ctx->r14);
    // 0x8004AC34: subu        $v0, $a3, $v1
    ctx->r2 = SUB32(ctx->r7, ctx->r3);
    // 0x8004AC38: addiu       $v0, $v0, 0x3E80
    ctx->r2 = ADD32(ctx->r2, 0X3E80);
    // 0x8004AC3C: sra         $t7, $v0, 8
    ctx->r15 = S32(SIGNED(ctx->r2) >> 8);
    // 0x8004AC40: sll         $t9, $t7, 1
    ctx->r25 = S32(ctx->r15 << 1);
    // 0x8004AC44: addu        $t8, $t9, $a0
    ctx->r24 = ADD32(ctx->r25, ctx->r4);
    // 0x8004AC48: lhu         $t6, 0x0($t8)
    ctx->r14 = MEM_HU(ctx->r24, 0X0);
    // 0x8004AC4C: or          $v1, $a3, $zero
    ctx->r3 = ctx->r7 | 0;
    // 0x8004AC50: beq         $at, $zero, L_8004ABEC
    if (ctx->r1 == 0) {
        // 0x8004AC54: sh          $t6, 0x280($t0)
        MEM_H(0X280, ctx->r8) = ctx->r14;
            goto L_8004ABEC;
    }
    // 0x8004AC54: sh          $t6, 0x280($t0)
    MEM_H(0X280, ctx->r8) = ctx->r14;
    // 0x8004AC58: sltu        $at, $a1, $a2
    ctx->r1 = ctx->r5 < ctx->r6 ? 1 : 0;
    // 0x8004AC5C: bnel        $at, $zero, L_8004AB94
    if (ctx->r1 != 0) {
        // 0x8004AC60: addu        $a3, $a1, $t3
        ctx->r7 = ADD32(ctx->r5, ctx->r11);
            goto L_8004AB94;
    }
    goto skip_0;
    // 0x8004AC60: addu        $a3, $a1, $t3
    ctx->r7 = ADD32(ctx->r5, ctx->r11);
    skip_0:
    // 0x8004AC64: lw          $s0, 0x4($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X4);
    // 0x8004AC68: lw          $s1, 0x8($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X8);
    // 0x8004AC6C: lw          $s2, 0xC($sp)
    ctx->r18 = MEM_W(ctx->r29, 0XC);
    // 0x8004AC70: jr          $ra
    // 0x8004AC74: addiu       $sp, $sp, 0x10
    ctx->r29 = ADD32(ctx->r29, 0X10);
    return;
    // 0x8004AC74: addiu       $sp, $sp, 0x10
    ctx->r29 = ADD32(ctx->r29, 0X10);
    // 0x8004AC78: nop

    // 0x8004AC7C: nop

;}
RECOMP_FUNC void func_8004AC80(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8004AC80: addiu       $sp, $sp, -0xA8
    ctx->r29 = ADD32(ctx->r29, -0XA8);
    // 0x8004AC84: sw          $ra, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r31;
    // 0x8004AC88: sw          $s3, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r19;
    // 0x8004AC8C: sw          $s2, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r18;
    // 0x8004AC90: sw          $s1, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r17;
    // 0x8004AC94: sw          $s0, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r16;
    // 0x8004AC98: sdc1        $f26, 0x28($sp)
    CHECK_FR(ctx, 26);
    SD(ctx->f26.u64, 0X28, ctx->r29);
    // 0x8004AC9C: sdc1        $f24, 0x20($sp)
    CHECK_FR(ctx, 24);
    SD(ctx->f24.u64, 0X20, ctx->r29);
    // 0x8004ACA0: sdc1        $f22, 0x18($sp)
    CHECK_FR(ctx, 22);
    SD(ctx->f22.u64, 0X18, ctx->r29);
    // 0x8004ACA4: sdc1        $f20, 0x10($sp)
    CHECK_FR(ctx, 20);
    SD(ctx->f20.u64, 0X10, ctx->r29);
    // 0x8004ACA8: lw          $v0, 0x28($a0)
    ctx->r2 = MEM_W(ctx->r4, 0X28);
    // 0x8004ACAC: mtc1        $a1, $f22
    ctx->f22.u32l = ctx->r5;
    // 0x8004ACB0: mtc1        $a2, $f24
    ctx->f24.u32l = ctx->r6;
    // 0x8004ACB4: mtc1        $a3, $f26
    ctx->f26.u32l = ctx->r7;
    // 0x8004ACB8: mtc1        $zero, $f20
    ctx->f20.u32l = 0;
    // 0x8004ACBC: bltz        $v0, L_8004AD38
    if (SIGNED(ctx->r2) < 0) {
        // 0x8004ACC0: or          $s2, $a0, $zero
        ctx->r18 = ctx->r4 | 0;
            goto L_8004AD38;
    }
    // 0x8004ACC0: or          $s2, $a0, $zero
    ctx->r18 = ctx->r4 | 0;
    // 0x8004ACC4: sll         $t6, $v0, 2
    ctx->r14 = S32(ctx->r2 << 2);
    // 0x8004ACC8: addiu       $t7, $sp, 0x6C
    ctx->r15 = ADD32(ctx->r29, 0X6C);
    // 0x8004ACCC: addu        $s0, $t6, $t7
    ctx->r16 = ADD32(ctx->r14, ctx->r15);
    // 0x8004ACD0: sll         $s1, $v0, 5
    ctx->r17 = S32(ctx->r2 << 5);
    // 0x8004ACD4: addiu       $s3, $sp, 0x6C
    ctx->r19 = ADD32(ctx->r29, 0X6C);
L_8004ACD8:
    // 0x8004ACD8: lw          $t8, 0x30($s2)
    ctx->r24 = MEM_W(ctx->r18, 0X30);
    // 0x8004ACDC: addu        $v0, $t8, $s1
    ctx->r2 = ADD32(ctx->r24, ctx->r17);
    // 0x8004ACE0: lwc1        $f4, 0x0($v0)
    ctx->f4.u32l = MEM_W(ctx->r2, 0X0);
    // 0x8004ACE4: lwc1        $f6, 0x4($v0)
    ctx->f6.u32l = MEM_W(ctx->r2, 0X4);
    // 0x8004ACE8: lwc1        $f8, 0x8($v0)
    ctx->f8.u32l = MEM_W(ctx->r2, 0X8);
    // 0x8004ACEC: sub.s       $f0, $f4, $f22
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f0.fl = ctx->f4.fl - ctx->f22.fl;
    // 0x8004ACF0: sub.s       $f2, $f6, $f24
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 24);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f24.fl); 
    ctx->f2.fl = ctx->f6.fl - ctx->f24.fl;
    // 0x8004ACF4: mul.s       $f10, $f0, $f0
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f10.fl = MUL_S(ctx->f0.fl, ctx->f0.fl);
    // 0x8004ACF8: sub.s       $f14, $f8, $f26
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 26);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f26.fl); 
    ctx->f14.fl = ctx->f8.fl - ctx->f26.fl;
    // 0x8004ACFC: mul.s       $f16, $f2, $f2
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f16.fl = MUL_S(ctx->f2.fl, ctx->f2.fl);
    // 0x8004AD00: add.s       $f18, $f10, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f18.fl = ctx->f10.fl + ctx->f16.fl;
    // 0x8004AD04: mul.s       $f4, $f14, $f14
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f4.fl = MUL_S(ctx->f14.fl, ctx->f14.fl);
    // 0x8004AD08: jal         0x800C7010
    // 0x8004AD0C: add.s       $f12, $f18, $f4
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f12.fl = ctx->f18.fl + ctx->f4.fl;
    _nsqrtf(rdram, ctx);
        goto after_0;
    // 0x8004AD0C: add.s       $f12, $f18, $f4
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f12.fl = ctx->f18.fl + ctx->f4.fl;
    after_0:
    // 0x8004AD10: c.lt.s      $f20, $f0
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 0);
    c1cs = ctx->f20.fl < ctx->f0.fl;
    // 0x8004AD14: swc1        $f0, 0x0($s0)
    MEM_W(0X0, ctx->r16) = ctx->f0.u32l;
    // 0x8004AD18: bc1fl       L_8004AD28
    if (!c1cs) {
        // 0x8004AD1C: addiu       $s0, $s0, -0x4
        ctx->r16 = ADD32(ctx->r16, -0X4);
            goto L_8004AD28;
    }
    goto skip_0;
    // 0x8004AD1C: addiu       $s0, $s0, -0x4
    ctx->r16 = ADD32(ctx->r16, -0X4);
    skip_0:
    // 0x8004AD20: lwc1        $f20, 0x0($s0)
    ctx->f20.u32l = MEM_W(ctx->r16, 0X0);
    // 0x8004AD24: addiu       $s0, $s0, -0x4
    ctx->r16 = ADD32(ctx->r16, -0X4);
L_8004AD28:
    // 0x8004AD28: sltu        $at, $s0, $s3
    ctx->r1 = ctx->r16 < ctx->r19 ? 1 : 0;
    // 0x8004AD2C: beq         $at, $zero, L_8004ACD8
    if (ctx->r1 == 0) {
        // 0x8004AD30: addiu       $s1, $s1, -0x20
        ctx->r17 = ADD32(ctx->r17, -0X20);
            goto L_8004ACD8;
    }
    // 0x8004AD30: addiu       $s1, $s1, -0x20
    ctx->r17 = ADD32(ctx->r17, -0X20);
    // 0x8004AD34: lw          $v0, 0x28($s2)
    ctx->r2 = MEM_W(ctx->r18, 0X28);
L_8004AD38:
    // 0x8004AD38: lwc1        $f6, 0x8($s2)
    ctx->f6.u32l = MEM_W(ctx->r18, 0X8);
    // 0x8004AD3C: lwc1        $f8, 0x4($s2)
    ctx->f8.u32l = MEM_W(ctx->r18, 0X4);
    // 0x8004AD40: sll         $t9, $v0, 2
    ctx->r25 = S32(ctx->r2 << 2);
    // 0x8004AD44: addiu       $t0, $sp, 0x6C
    ctx->r8 = ADD32(ctx->r29, 0X6C);
    // 0x8004AD48: sub.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = ctx->f6.fl - ctx->f8.fl;
    // 0x8004AD4C: addu        $s0, $t9, $t0
    ctx->r16 = ADD32(ctx->r25, ctx->r8);
    // 0x8004AD50: sll         $s1, $v0, 5
    ctx->r17 = S32(ctx->r2 << 5);
    // 0x8004AD54: bltz        $v0, L_8004ADC0
    if (SIGNED(ctx->r2) < 0) {
        // 0x8004AD58: div.s       $f0, $f10, $f20
        CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f0.fl = DIV_S(ctx->f10.fl, ctx->f20.fl);
            goto L_8004ADC0;
    }
    // 0x8004AD58: div.s       $f0, $f10, $f20
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f0.fl = DIV_S(ctx->f10.fl, ctx->f20.fl);
    // 0x8004AD5C: addiu       $v0, $sp, 0x6C
    ctx->r2 = ADD32(ctx->r29, 0X6C);
    // 0x8004AD60: lwc1        $f24, 0x0($s0)
    ctx->f24.u32l = MEM_W(ctx->r16, 0X0);
    // 0x8004AD64: addiu       $s0, $s0, -0x4
    ctx->r16 = ADD32(ctx->r16, -0X4);
    // 0x8004AD68: sltu        $at, $s0, $v0
    ctx->r1 = ctx->r16 < ctx->r2 ? 1 : 0;
    // 0x8004AD6C: mul.s       $f26, $f24, $f0
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f24.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f26.fl = MUL_S(ctx->f24.fl, ctx->f0.fl);
    // 0x8004AD70: bnel        $at, $zero, L_8004ADAC
    if (ctx->r1 != 0) {
        // 0x8004AD74: lwc1        $f24, 0x4($s2)
        ctx->f24.u32l = MEM_W(ctx->r18, 0X4);
            goto L_8004ADAC;
    }
    goto skip_1;
    // 0x8004AD74: lwc1        $f24, 0x4($s2)
    ctx->f24.u32l = MEM_W(ctx->r18, 0X4);
    skip_1:
    // 0x8004AD78: lwc1        $f24, 0x4($s2)
    ctx->f24.u32l = MEM_W(ctx->r18, 0X4);
L_8004AD7C:
    // 0x8004AD7C: lw          $t1, 0x30($s2)
    ctx->r9 = MEM_W(ctx->r18, 0X30);
    // 0x8004AD80: addiu       $s0, $s0, -0x4
    ctx->r16 = ADD32(ctx->r16, -0X4);
    // 0x8004AD84: add.s       $f24, $f26, $f24
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 24);
    NAN_CHECK(ctx->f26.fl); NAN_CHECK(ctx->f24.fl); 
    ctx->f24.fl = ctx->f26.fl + ctx->f24.fl;
    // 0x8004AD88: addu        $t2, $t1, $s1
    ctx->r10 = ADD32(ctx->r9, ctx->r17);
    // 0x8004AD8C: sltu        $at, $s0, $v0
    ctx->r1 = ctx->r16 < ctx->r2 ? 1 : 0;
    // 0x8004AD90: addiu       $s1, $s1, -0x20
    ctx->r17 = ADD32(ctx->r17, -0X20);
    // 0x8004AD94: swc1        $f24, 0x18($t2)
    MEM_W(0X18, ctx->r10) = ctx->f24.u32l;
    // 0x8004AD98: lwc1        $f24, 0x4($s0)
    ctx->f24.u32l = MEM_W(ctx->r16, 0X4);
    // 0x8004AD9C: mul.s       $f26, $f24, $f0
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f24.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f26.fl = MUL_S(ctx->f24.fl, ctx->f0.fl);
    // 0x8004ADA0: beql        $at, $zero, L_8004AD7C
    if (ctx->r1 == 0) {
        // 0x8004ADA4: lwc1        $f24, 0x4($s2)
        ctx->f24.u32l = MEM_W(ctx->r18, 0X4);
            goto L_8004AD7C;
    }
    goto skip_2;
    // 0x8004ADA4: lwc1        $f24, 0x4($s2)
    ctx->f24.u32l = MEM_W(ctx->r18, 0X4);
    skip_2:
    // 0x8004ADA8: lwc1        $f24, 0x4($s2)
    ctx->f24.u32l = MEM_W(ctx->r18, 0X4);
L_8004ADAC:
    // 0x8004ADAC: lw          $t1, 0x30($s2)
    ctx->r9 = MEM_W(ctx->r18, 0X30);
    // 0x8004ADB0: add.s       $f24, $f26, $f24
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 24);
    NAN_CHECK(ctx->f26.fl); NAN_CHECK(ctx->f24.fl); 
    ctx->f24.fl = ctx->f26.fl + ctx->f24.fl;
    // 0x8004ADB4: addu        $t2, $t1, $s1
    ctx->r10 = ADD32(ctx->r9, ctx->r17);
    // 0x8004ADB8: addiu       $s1, $s1, -0x20
    ctx->r17 = ADD32(ctx->r17, -0X20);
    // 0x8004ADBC: swc1        $f24, 0x18($t2)
    MEM_W(0X18, ctx->r10) = ctx->f24.u32l;
L_8004ADC0:
    // 0x8004ADC0: lw          $ra, 0x44($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X44);
    // 0x8004ADC4: ldc1        $f20, 0x10($sp)
    CHECK_FR(ctx, 20);
    ctx->f20.u64 = LD(ctx->r29, 0X10);
    // 0x8004ADC8: ldc1        $f22, 0x18($sp)
    CHECK_FR(ctx, 22);
    ctx->f22.u64 = LD(ctx->r29, 0X18);
    // 0x8004ADCC: ldc1        $f24, 0x20($sp)
    CHECK_FR(ctx, 24);
    ctx->f24.u64 = LD(ctx->r29, 0X20);
    // 0x8004ADD0: ldc1        $f26, 0x28($sp)
    CHECK_FR(ctx, 26);
    ctx->f26.u64 = LD(ctx->r29, 0X28);
    // 0x8004ADD4: lw          $s0, 0x34($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X34);
    // 0x8004ADD8: lw          $s1, 0x38($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X38);
    // 0x8004ADDC: lw          $s2, 0x3C($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X3C);
    // 0x8004ADE0: lw          $s3, 0x40($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X40);
    // 0x8004ADE4: jr          $ra
    // 0x8004ADE8: addiu       $sp, $sp, 0xA8
    ctx->r29 = ADD32(ctx->r29, 0XA8);
    return;
    // 0x8004ADE8: addiu       $sp, $sp, 0xA8
    ctx->r29 = ADD32(ctx->r29, 0XA8);
;}
RECOMP_FUNC void func_8004ADEC(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8004ADEC: lw          $t6, 0x28($a0)
    ctx->r14 = MEM_W(ctx->r4, 0X28);
    // 0x8004ADF0: lwc1        $f4, 0x20($a0)
    ctx->f4.u32l = MEM_W(ctx->r4, 0X20);
    // 0x8004ADF4: lui         $at, 0x4F80
    ctx->r1 = S32(0X4F80 << 16);
    // 0x8004ADF8: addiu       $t7, $t6, -0x1
    ctx->r15 = ADD32(ctx->r14, -0X1);
    // 0x8004ADFC: mtc1        $t7, $f6
    ctx->f6.u32l = ctx->r15;
    // 0x8004AE00: bgez        $t7, L_8004AE14
    if (SIGNED(ctx->r15) >= 0) {
        // 0x8004AE04: cvt.s.w     $f8, $f6
        CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    ctx->f8.fl = CVT_S_W(ctx->f6.u32l);
            goto L_8004AE14;
    }
    // 0x8004AE04: cvt.s.w     $f8, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    ctx->f8.fl = CVT_S_W(ctx->f6.u32l);
    // 0x8004AE08: mtc1        $at, $f10
    ctx->f10.u32l = ctx->r1;
    // 0x8004AE0C: nop

    // 0x8004AE10: add.s       $f8, $f8, $f10
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f8.fl = ctx->f8.fl + ctx->f10.fl;
L_8004AE14:
    // 0x8004AE14: mul.s       $f16, $f4, $f8
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f16.fl = MUL_S(ctx->f4.fl, ctx->f8.fl);
    // 0x8004AE18: lw          $a1, 0x2C($a0)
    ctx->r5 = MEM_W(ctx->r4, 0X2C);
    // 0x8004AE1C: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x8004AE20: mtc1        $at, $f18
    ctx->f18.u32l = ctx->r1;
    // 0x8004AE24: lw          $v1, 0x34($a0)
    ctx->r3 = MEM_W(ctx->r4, 0X34);
    // 0x8004AE28: sll         $t8, $a1, 2
    ctx->r24 = S32(ctx->r5 << 2);
    // 0x8004AE2C: lui         $at, 0x3F00
    ctx->r1 = S32(0X3F00 << 16);
    // 0x8004AE30: subu        $t8, $t8, $a1
    ctx->r24 = SUB32(ctx->r24, ctx->r5);
    // 0x8004AE34: add.s       $f6, $f16, $f18
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f6.fl = ctx->f16.fl + ctx->f18.fl;
    // 0x8004AE38: mtc1        $at, $f10
    ctx->f10.u32l = ctx->r1;
    // 0x8004AE3C: sll         $t8, $t8, 2
    ctx->r24 = S32(ctx->r24 << 2);
    // 0x8004AE40: lw          $t9, 0x38($a0)
    ctx->r25 = MEM_W(ctx->r4, 0X38);
    // 0x8004AE44: addu        $v0, $v1, $t8
    ctx->r2 = ADD32(ctx->r3, ctx->r24);
    // 0x8004AE48: sll         $t0, $a1, 2
    ctx->r8 = S32(ctx->r5 << 2);
    // 0x8004AE4C: sltu        $at, $v0, $v1
    ctx->r1 = ctx->r2 < ctx->r3 ? 1 : 0;
    // 0x8004AE50: div.s       $f0, $f10, $f6
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f0.fl = DIV_S(ctx->f10.fl, ctx->f6.fl);
    // 0x8004AE54: bne         $at, $zero, L_8004AE80
    if (ctx->r1 != 0) {
        // 0x8004AE58: addu        $a2, $t9, $t0
        ctx->r6 = ADD32(ctx->r25, ctx->r8);
            goto L_8004AE80;
    }
    // 0x8004AE58: addu        $a2, $t9, $t0
    ctx->r6 = ADD32(ctx->r25, ctx->r8);
    // 0x8004AE5C: lwc1        $f4, 0x0($a2)
    ctx->f4.u32l = MEM_W(ctx->r6, 0X0);
L_8004AE60:
    // 0x8004AE60: addiu       $v0, $v0, -0xC
    ctx->r2 = ADD32(ctx->r2, -0XC);
    // 0x8004AE64: addiu       $a2, $a2, -0x4
    ctx->r6 = ADD32(ctx->r6, -0X4);
    // 0x8004AE68: mul.s       $f8, $f4, $f0
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f8.fl = MUL_S(ctx->f4.fl, ctx->f0.fl);
    // 0x8004AE6C: swc1        $f8, 0x14($v0)
    MEM_W(0X14, ctx->r2) = ctx->f8.u32l;
    // 0x8004AE70: lw          $t1, 0x34($a0)
    ctx->r9 = MEM_W(ctx->r4, 0X34);
    // 0x8004AE74: sltu        $at, $v0, $t1
    ctx->r1 = ctx->r2 < ctx->r9 ? 1 : 0;
    // 0x8004AE78: beql        $at, $zero, L_8004AE60
    if (ctx->r1 == 0) {
        // 0x8004AE7C: lwc1        $f4, 0x0($a2)
        ctx->f4.u32l = MEM_W(ctx->r6, 0X0);
            goto L_8004AE60;
    }
    goto skip_0;
    // 0x8004AE7C: lwc1        $f4, 0x0($a2)
    ctx->f4.u32l = MEM_W(ctx->r6, 0X0);
    skip_0:
L_8004AE80:
    // 0x8004AE80: jr          $ra
    // 0x8004AE84: nop

    return;
    // 0x8004AE84: nop

;}
RECOMP_FUNC void func_8004AE88(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8004AE88: addiu       $sp, $sp, -0x30
    ctx->r29 = ADD32(ctx->r29, -0X30);
    // 0x8004AE8C: sw          $ra, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r31;
    // 0x8004AE90: sw          $s2, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r18;
    // 0x8004AE94: sw          $s1, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r17;
    // 0x8004AE98: sw          $s0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r16;
    // 0x8004AE9C: sdc1        $f20, 0x18($sp)
    CHECK_FR(ctx, 20);
    SD(ctx->f20.u64, 0X18, ctx->r29);
    // 0x8004AEA0: lw          $t6, 0x28($a0)
    ctx->r14 = MEM_W(ctx->r4, 0X28);
    // 0x8004AEA4: or          $s2, $a0, $zero
    ctx->r18 = ctx->r4 | 0;
    // 0x8004AEA8: lwc1        $f4, 0x20($a0)
    ctx->f4.u32l = MEM_W(ctx->r4, 0X20);
    // 0x8004AEAC: addiu       $t7, $t6, -0x1
    ctx->r15 = ADD32(ctx->r14, -0X1);
    // 0x8004AEB0: mtc1        $t7, $f6
    ctx->f6.u32l = ctx->r15;
    // 0x8004AEB4: lui         $at, 0x4F80
    ctx->r1 = S32(0X4F80 << 16);
    // 0x8004AEB8: bgez        $t7, L_8004AECC
    if (SIGNED(ctx->r15) >= 0) {
        // 0x8004AEBC: cvt.s.w     $f8, $f6
        CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    ctx->f8.fl = CVT_S_W(ctx->f6.u32l);
            goto L_8004AECC;
    }
    // 0x8004AEBC: cvt.s.w     $f8, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    ctx->f8.fl = CVT_S_W(ctx->f6.u32l);
    // 0x8004AEC0: mtc1        $at, $f10
    ctx->f10.u32l = ctx->r1;
    // 0x8004AEC4: nop

    // 0x8004AEC8: add.s       $f8, $f8, $f10
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f8.fl = ctx->f8.fl + ctx->f10.fl;
L_8004AECC:
    // 0x8004AECC: mul.s       $f16, $f4, $f8
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f16.fl = MUL_S(ctx->f4.fl, ctx->f8.fl);
    // 0x8004AED0: lw          $v1, 0x2C($s2)
    ctx->r3 = MEM_W(ctx->r18, 0X2C);
    // 0x8004AED4: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x8004AED8: mtc1        $at, $f18
    ctx->f18.u32l = ctx->r1;
    // 0x8004AEDC: lui         $at, 0x3F00
    ctx->r1 = S32(0X3F00 << 16);
    // 0x8004AEE0: mtc1        $at, $f10
    ctx->f10.u32l = ctx->r1;
    // 0x8004AEE4: lw          $v0, 0x34($s2)
    ctx->r2 = MEM_W(ctx->r18, 0X34);
    // 0x8004AEE8: sll         $t8, $v1, 2
    ctx->r24 = S32(ctx->r3 << 2);
    // 0x8004AEEC: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x8004AEF0: subu        $t8, $t8, $v1
    ctx->r24 = SUB32(ctx->r24, ctx->r3);
    // 0x8004AEF4: add.s       $f6, $f16, $f18
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f6.fl = ctx->f16.fl + ctx->f18.fl;
    // 0x8004AEF8: lwc1        $f4, -0x6D90($at)
    ctx->f4.u32l = MEM_W(ctx->r1, -0X6D90);
    // 0x8004AEFC: sll         $t8, $t8, 2
    ctx->r24 = S32(ctx->r24 << 2);
    // 0x8004AF00: mtc1        $zero, $f8
    ctx->f8.u32l = 0;
    // 0x8004AF04: lw          $t9, 0x38($s2)
    ctx->r25 = MEM_W(ctx->r18, 0X38);
    // 0x8004AF08: addu        $s0, $v0, $t8
    ctx->r16 = ADD32(ctx->r2, ctx->r24);
    // 0x8004AF0C: sll         $t0, $v1, 2
    ctx->r8 = S32(ctx->r3 << 2);
    // 0x8004AF10: sltu        $at, $s0, $v0
    ctx->r1 = ctx->r16 < ctx->r2 ? 1 : 0;
    // 0x8004AF14: div.s       $f20, $f10, $f6
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f20.fl = DIV_S(ctx->f10.fl, ctx->f6.fl);
    // 0x8004AF18: swc1        $f4, 0x3C($s2)
    MEM_W(0X3C, ctx->r18) = ctx->f4.u32l;
    // 0x8004AF1C: swc1        $f8, 0x40($s2)
    MEM_W(0X40, ctx->r18) = ctx->f8.u32l;
    // 0x8004AF20: bne         $at, $zero, L_8004AFCC
    if (ctx->r1 != 0) {
        // 0x8004AF24: addu        $s1, $t9, $t0
        ctx->r17 = ADD32(ctx->r25, ctx->r8);
            goto L_8004AFCC;
    }
    // 0x8004AF24: addu        $s1, $t9, $t0
    ctx->r17 = ADD32(ctx->r25, ctx->r8);
    // 0x8004AF28: lw          $v0, 0x0($s0)
    ctx->r2 = MEM_W(ctx->r16, 0X0);
L_8004AF2C:
    // 0x8004AF2C: lw          $v1, 0x4($s0)
    ctx->r3 = MEM_W(ctx->r16, 0X4);
    // 0x8004AF30: lwc1        $f18, 0x0($v0)
    ctx->f18.u32l = MEM_W(ctx->r2, 0X0);
    // 0x8004AF34: lwc1        $f16, 0x0($v1)
    ctx->f16.u32l = MEM_W(ctx->r3, 0X0);
    // 0x8004AF38: lwc1        $f6, 0x4($v0)
    ctx->f6.u32l = MEM_W(ctx->r2, 0X4);
    // 0x8004AF3C: lwc1        $f10, 0x4($v1)
    ctx->f10.u32l = MEM_W(ctx->r3, 0X4);
    // 0x8004AF40: sub.s       $f0, $f16, $f18
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f0.fl = ctx->f16.fl - ctx->f18.fl;
    // 0x8004AF44: lwc1        $f8, 0x8($v0)
    ctx->f8.u32l = MEM_W(ctx->r2, 0X8);
    // 0x8004AF48: lwc1        $f4, 0x8($v1)
    ctx->f4.u32l = MEM_W(ctx->r3, 0X8);
    // 0x8004AF4C: sub.s       $f2, $f10, $f6
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f2.fl = ctx->f10.fl - ctx->f6.fl;
    // 0x8004AF50: mul.s       $f16, $f0, $f0
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f16.fl = MUL_S(ctx->f0.fl, ctx->f0.fl);
    // 0x8004AF54: sub.s       $f14, $f4, $f8
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f14.fl = ctx->f4.fl - ctx->f8.fl;
    // 0x8004AF58: mul.s       $f18, $f2, $f2
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f18.fl = MUL_S(ctx->f2.fl, ctx->f2.fl);
    // 0x8004AF5C: add.s       $f10, $f16, $f18
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f10.fl = ctx->f16.fl + ctx->f18.fl;
    // 0x8004AF60: mul.s       $f6, $f14, $f14
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f6.fl = MUL_S(ctx->f14.fl, ctx->f14.fl);
    // 0x8004AF64: jal         0x800C7010
    // 0x8004AF68: add.s       $f12, $f10, $f6
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f12.fl = ctx->f10.fl + ctx->f6.fl;
    _nsqrtf(rdram, ctx);
        goto after_0;
    // 0x8004AF68: add.s       $f12, $f10, $f6
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f12.fl = ctx->f10.fl + ctx->f6.fl;
    after_0:
    // 0x8004AF6C: swc1        $f0, 0x0($s1)
    MEM_W(0X0, ctx->r17) = ctx->f0.u32l;
    // 0x8004AF70: lwc1        $f4, 0x3C($s2)
    ctx->f4.u32l = MEM_W(ctx->r18, 0X3C);
    // 0x8004AF74: c.lt.s      $f0, $f4
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 4);
    c1cs = ctx->f0.fl < ctx->f4.fl;
    // 0x8004AF78: nop

    // 0x8004AF7C: bc1fl       L_8004AF90
    if (!c1cs) {
        // 0x8004AF80: lwc1        $f0, 0x0($s1)
        ctx->f0.u32l = MEM_W(ctx->r17, 0X0);
            goto L_8004AF90;
    }
    goto skip_0;
    // 0x8004AF80: lwc1        $f0, 0x0($s1)
    ctx->f0.u32l = MEM_W(ctx->r17, 0X0);
    skip_0:
    // 0x8004AF84: lwc1        $f8, 0x0($s1)
    ctx->f8.u32l = MEM_W(ctx->r17, 0X0);
    // 0x8004AF88: swc1        $f8, 0x3C($s2)
    MEM_W(0X3C, ctx->r18) = ctx->f8.u32l;
    // 0x8004AF8C: lwc1        $f0, 0x0($s1)
    ctx->f0.u32l = MEM_W(ctx->r17, 0X0);
L_8004AF90:
    // 0x8004AF90: lwc1        $f16, 0x40($s2)
    ctx->f16.u32l = MEM_W(ctx->r18, 0X40);
    // 0x8004AF94: c.lt.s      $f16, $f0
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 0);
    c1cs = ctx->f16.fl < ctx->f0.fl;
    // 0x8004AF98: nop

    // 0x8004AF9C: bc1f        L_8004AFAC
    if (!c1cs) {
        // 0x8004AFA0: nop
    
            goto L_8004AFAC;
    }
    // 0x8004AFA0: nop

    // 0x8004AFA4: swc1        $f0, 0x40($s2)
    MEM_W(0X40, ctx->r18) = ctx->f0.u32l;
    // 0x8004AFA8: lwc1        $f0, 0x0($s1)
    ctx->f0.u32l = MEM_W(ctx->r17, 0X0);
L_8004AFAC:
    // 0x8004AFAC: mul.s       $f18, $f0, $f20
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f18.fl = MUL_S(ctx->f0.fl, ctx->f20.fl);
    // 0x8004AFB0: addiu       $s0, $s0, -0xC
    ctx->r16 = ADD32(ctx->r16, -0XC);
    // 0x8004AFB4: addiu       $s1, $s1, -0x4
    ctx->r17 = ADD32(ctx->r17, -0X4);
    // 0x8004AFB8: swc1        $f18, 0x14($s0)
    MEM_W(0X14, ctx->r16) = ctx->f18.u32l;
    // 0x8004AFBC: lw          $t1, 0x34($s2)
    ctx->r9 = MEM_W(ctx->r18, 0X34);
    // 0x8004AFC0: sltu        $at, $s0, $t1
    ctx->r1 = ctx->r16 < ctx->r9 ? 1 : 0;
    // 0x8004AFC4: beql        $at, $zero, L_8004AF2C
    if (ctx->r1 == 0) {
        // 0x8004AFC8: lw          $v0, 0x0($s0)
        ctx->r2 = MEM_W(ctx->r16, 0X0);
            goto L_8004AF2C;
    }
    goto skip_1;
    // 0x8004AFC8: lw          $v0, 0x0($s0)
    ctx->r2 = MEM_W(ctx->r16, 0X0);
    skip_1:
L_8004AFCC:
    // 0x8004AFCC: lw          $ra, 0x2C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X2C);
    // 0x8004AFD0: ldc1        $f20, 0x18($sp)
    CHECK_FR(ctx, 20);
    ctx->f20.u64 = LD(ctx->r29, 0X18);
    // 0x8004AFD4: lw          $s0, 0x20($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X20);
    // 0x8004AFD8: lw          $s1, 0x24($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X24);
    // 0x8004AFDC: lw          $s2, 0x28($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X28);
    // 0x8004AFE0: jr          $ra
    // 0x8004AFE4: addiu       $sp, $sp, 0x30
    ctx->r29 = ADD32(ctx->r29, 0X30);
    return;
    // 0x8004AFE4: addiu       $sp, $sp, 0x30
    ctx->r29 = ADD32(ctx->r29, 0X30);
;}
RECOMP_FUNC void func_8004AFE8(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8004AFE8: addiu       $a3, $a2, -0x1
    ctx->r7 = ADD32(ctx->r6, -0X1);
    // 0x8004AFEC: slt         $at, $a3, $a1
    ctx->r1 = SIGNED(ctx->r7) < SIGNED(ctx->r5) ? 1 : 0;
    // 0x8004AFF0: lw          $v0, 0x34($a0)
    ctx->r2 = MEM_W(ctx->r4, 0X34);
    // 0x8004AFF4: bne         $at, $zero, L_8004B0F0
    if (ctx->r1 != 0) {
        // 0x8004AFF8: or          $v1, $a1, $zero
        ctx->r3 = ctx->r5 | 0;
            goto L_8004B0F0;
    }
    // 0x8004AFF8: or          $v1, $a1, $zero
    ctx->r3 = ctx->r5 | 0;
L_8004AFFC:
    // 0x8004AFFC: addiu       $t0, $v1, 0x1
    ctx->r8 = ADD32(ctx->r3, 0X1);
    // 0x8004B000: slt         $at, $a2, $t0
    ctx->r1 = SIGNED(ctx->r6) < SIGNED(ctx->r8) ? 1 : 0;
    // 0x8004B004: bne         $at, $zero, L_8004B0E4
    if (ctx->r1 != 0) {
        // 0x8004B008: or          $a1, $t0, $zero
        ctx->r5 = ctx->r8 | 0;
            goto L_8004B0E4;
    }
    // 0x8004B008: or          $a1, $t0, $zero
    ctx->r5 = ctx->r8 | 0;
    // 0x8004B00C: subu        $t3, $a2, $t0
    ctx->r11 = SUB32(ctx->r6, ctx->r8);
    // 0x8004B010: addiu       $t3, $t3, 0x1
    ctx->r11 = ADD32(ctx->r11, 0X1);
    // 0x8004B014: andi        $t6, $t3, 0x3
    ctx->r14 = ctx->r11 & 0X3;
    // 0x8004B018: beq         $t6, $zero, L_8004B054
    if (ctx->r14 == 0) {
        // 0x8004B01C: addu        $t2, $t6, $t0
        ctx->r10 = ADD32(ctx->r14, ctx->r8);
            goto L_8004B054;
    }
    // 0x8004B01C: addu        $t2, $t6, $t0
    ctx->r10 = ADD32(ctx->r14, ctx->r8);
    // 0x8004B020: sll         $t1, $v1, 5
    ctx->r9 = S32(ctx->r3 << 5);
L_8004B024:
    // 0x8004B024: lw          $t7, 0x30($a0)
    ctx->r15 = MEM_W(ctx->r4, 0X30);
    // 0x8004B028: sll         $t4, $a1, 5
    ctx->r12 = S32(ctx->r5 << 5);
    // 0x8004B02C: addiu       $a1, $a1, 0x1
    ctx->r5 = ADD32(ctx->r5, 0X1);
    // 0x8004B030: addu        $t8, $t7, $t1
    ctx->r24 = ADD32(ctx->r15, ctx->r9);
    // 0x8004B034: sw          $t8, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r24;
    // 0x8004B038: lw          $t9, 0x30($a0)
    ctx->r25 = MEM_W(ctx->r4, 0X30);
    // 0x8004B03C: addiu       $v0, $v0, 0xC
    ctx->r2 = ADD32(ctx->r2, 0XC);
    // 0x8004B040: addu        $t5, $t9, $t4
    ctx->r13 = ADD32(ctx->r25, ctx->r12);
    // 0x8004B044: bne         $t2, $a1, L_8004B024
    if (ctx->r10 != ctx->r5) {
        // 0x8004B048: sw          $t5, -0x8($v0)
        MEM_W(-0X8, ctx->r2) = ctx->r13;
            goto L_8004B024;
    }
    // 0x8004B048: sw          $t5, -0x8($v0)
    MEM_W(-0X8, ctx->r2) = ctx->r13;
    // 0x8004B04C: addiu       $t6, $a2, 0x1
    ctx->r14 = ADD32(ctx->r6, 0X1);
    // 0x8004B050: beq         $t6, $a1, L_8004B0E4
    if (ctx->r14 == ctx->r5) {
        // 0x8004B054: sll         $t1, $v1, 5
        ctx->r9 = S32(ctx->r3 << 5);
            goto L_8004B0E4;
    }
L_8004B054:
    // 0x8004B054: sll         $t1, $v1, 5
    ctx->r9 = S32(ctx->r3 << 5);
L_8004B058:
    // 0x8004B058: lw          $t7, 0x30($a0)
    ctx->r15 = MEM_W(ctx->r4, 0X30);
    // 0x8004B05C: sll         $t4, $a1, 5
    ctx->r12 = S32(ctx->r5 << 5);
    // 0x8004B060: addiu       $v0, $v0, 0x30
    ctx->r2 = ADD32(ctx->r2, 0X30);
    // 0x8004B064: addu        $t8, $t7, $t1
    ctx->r24 = ADD32(ctx->r15, ctx->r9);
    // 0x8004B068: sw          $t8, -0x30($v0)
    MEM_W(-0X30, ctx->r2) = ctx->r24;
    // 0x8004B06C: lw          $t9, 0x30($a0)
    ctx->r25 = MEM_W(ctx->r4, 0X30);
    // 0x8004B070: addu        $t5, $t9, $t4
    ctx->r13 = ADD32(ctx->r25, ctx->r12);
    // 0x8004B074: sw          $t5, -0x2C($v0)
    MEM_W(-0X2C, ctx->r2) = ctx->r13;
    // 0x8004B078: lw          $t6, 0x30($a0)
    ctx->r14 = MEM_W(ctx->r4, 0X30);
    // 0x8004B07C: addiu       $t9, $a1, 0x1
    ctx->r25 = ADD32(ctx->r5, 0X1);
    // 0x8004B080: sll         $t4, $t9, 5
    ctx->r12 = S32(ctx->r25 << 5);
    // 0x8004B084: addu        $t7, $t6, $t1
    ctx->r15 = ADD32(ctx->r14, ctx->r9);
    // 0x8004B088: sw          $t7, -0x24($v0)
    MEM_W(-0X24, ctx->r2) = ctx->r15;
    // 0x8004B08C: lw          $t8, 0x30($a0)
    ctx->r24 = MEM_W(ctx->r4, 0X30);
    // 0x8004B090: addu        $t5, $t8, $t4
    ctx->r13 = ADD32(ctx->r24, ctx->r12);
    // 0x8004B094: sw          $t5, -0x20($v0)
    MEM_W(-0X20, ctx->r2) = ctx->r13;
    // 0x8004B098: lw          $t6, 0x30($a0)
    ctx->r14 = MEM_W(ctx->r4, 0X30);
    // 0x8004B09C: addiu       $t8, $a1, 0x2
    ctx->r24 = ADD32(ctx->r5, 0X2);
    // 0x8004B0A0: sll         $t4, $t8, 5
    ctx->r12 = S32(ctx->r24 << 5);
    // 0x8004B0A4: addu        $t7, $t6, $t1
    ctx->r15 = ADD32(ctx->r14, ctx->r9);
    // 0x8004B0A8: sw          $t7, -0x18($v0)
    MEM_W(-0X18, ctx->r2) = ctx->r15;
    // 0x8004B0AC: lw          $t9, 0x30($a0)
    ctx->r25 = MEM_W(ctx->r4, 0X30);
    // 0x8004B0B0: addu        $t5, $t9, $t4
    ctx->r13 = ADD32(ctx->r25, ctx->r12);
    // 0x8004B0B4: sw          $t5, -0x14($v0)
    MEM_W(-0X14, ctx->r2) = ctx->r13;
    // 0x8004B0B8: lw          $t6, 0x30($a0)
    ctx->r14 = MEM_W(ctx->r4, 0X30);
    // 0x8004B0BC: addiu       $t9, $a1, 0x3
    ctx->r25 = ADD32(ctx->r5, 0X3);
    // 0x8004B0C0: sll         $t4, $t9, 5
    ctx->r12 = S32(ctx->r25 << 5);
    // 0x8004B0C4: addu        $t7, $t6, $t1
    ctx->r15 = ADD32(ctx->r14, ctx->r9);
    // 0x8004B0C8: sw          $t7, -0xC($v0)
    MEM_W(-0XC, ctx->r2) = ctx->r15;
    // 0x8004B0CC: lw          $t8, 0x30($a0)
    ctx->r24 = MEM_W(ctx->r4, 0X30);
    // 0x8004B0D0: addiu       $t6, $a2, 0x1
    ctx->r14 = ADD32(ctx->r6, 0X1);
    // 0x8004B0D4: addiu       $a1, $a1, 0x4
    ctx->r5 = ADD32(ctx->r5, 0X4);
    // 0x8004B0D8: addu        $t5, $t8, $t4
    ctx->r13 = ADD32(ctx->r24, ctx->r12);
    // 0x8004B0DC: bne         $t6, $a1, L_8004B058
    if (ctx->r14 != ctx->r5) {
        // 0x8004B0E0: sw          $t5, -0x8($v0)
        MEM_W(-0X8, ctx->r2) = ctx->r13;
            goto L_8004B058;
    }
    // 0x8004B0E0: sw          $t5, -0x8($v0)
    MEM_W(-0X8, ctx->r2) = ctx->r13;
L_8004B0E4:
    // 0x8004B0E4: slt         $at, $a3, $t0
    ctx->r1 = SIGNED(ctx->r7) < SIGNED(ctx->r8) ? 1 : 0;
    // 0x8004B0E8: beq         $at, $zero, L_8004AFFC
    if (ctx->r1 == 0) {
        // 0x8004B0EC: or          $v1, $t0, $zero
        ctx->r3 = ctx->r8 | 0;
            goto L_8004AFFC;
    }
    // 0x8004B0EC: or          $v1, $t0, $zero
    ctx->r3 = ctx->r8 | 0;
L_8004B0F0:
    // 0x8004B0F0: jr          $ra
    // 0x8004B0F4: nop

    return;
    // 0x8004B0F4: nop

;}
RECOMP_FUNC void func_8004B0F8(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8004B0F8: mtc1        $zero, $f14
    ctx->f14.u32l = 0;
    // 0x8004B0FC: lw          $a1, 0x28($a0)
    ctx->r5 = MEM_W(ctx->r4, 0X28);
    // 0x8004B100: lw          $v1, 0x30($a0)
    ctx->r3 = MEM_W(ctx->r4, 0X30);
    // 0x8004B104: mov.s       $f0, $f14
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 14);
    ctx->f0.fl = ctx->f14.fl;
    // 0x8004B108: sll         $t6, $a1, 5
    ctx->r14 = S32(ctx->r5 << 5);
    // 0x8004B10C: addu        $v0, $v1, $t6
    ctx->r2 = ADD32(ctx->r3, ctx->r14);
    // 0x8004B110: sltu        $at, $v0, $v1
    ctx->r1 = ctx->r2 < ctx->r3 ? 1 : 0;
    // 0x8004B114: mov.s       $f2, $f14
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 14);
    ctx->f2.fl = ctx->f14.fl;
    // 0x8004B118: mov.s       $f12, $f14
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 14);
    ctx->f12.fl = ctx->f14.fl;
    // 0x8004B11C: swc1        $f14, 0x64($a0)
    MEM_W(0X64, ctx->r4) = ctx->f14.u32l;
    // 0x8004B120: swc1        $f14, 0x60($a0)
    MEM_W(0X60, ctx->r4) = ctx->f14.u32l;
    // 0x8004B124: swc1        $f14, 0x5C($a0)
    MEM_W(0X5C, ctx->r4) = ctx->f14.u32l;
    // 0x8004B128: swc1        $f14, 0x58($a0)
    MEM_W(0X58, ctx->r4) = ctx->f14.u32l;
    // 0x8004B12C: swc1        $f14, 0x54($a0)
    MEM_W(0X54, ctx->r4) = ctx->f14.u32l;
    // 0x8004B130: swc1        $f14, 0x50($a0)
    MEM_W(0X50, ctx->r4) = ctx->f14.u32l;
    // 0x8004B134: bne         $at, $zero, L_8004B178
    if (ctx->r1 != 0) {
        // 0x8004B138: swc1        $f14, 0x68($a0)
        MEM_W(0X68, ctx->r4) = ctx->f14.u32l;
            goto L_8004B178;
    }
    // 0x8004B138: swc1        $f14, 0x68($a0)
    MEM_W(0X68, ctx->r4) = ctx->f14.u32l;
L_8004B13C:
    // 0x8004B13C: swc1        $f14, 0x14($v0)
    MEM_W(0X14, ctx->r2) = ctx->f14.u32l;
    // 0x8004B140: swc1        $f14, 0x10($v0)
    MEM_W(0X10, ctx->r2) = ctx->f14.u32l;
    // 0x8004B144: swc1        $f14, 0xC($v0)
    MEM_W(0XC, ctx->r2) = ctx->f14.u32l;
    // 0x8004B148: sw          $zero, 0x1C($v0)
    MEM_W(0X1C, ctx->r2) = 0;
    // 0x8004B14C: lw          $t7, 0x30($a0)
    ctx->r15 = MEM_W(ctx->r4, 0X30);
    // 0x8004B150: lwc1        $f4, 0x0($v0)
    ctx->f4.u32l = MEM_W(ctx->r2, 0X0);
    // 0x8004B154: lwc1        $f6, 0x4($v0)
    ctx->f6.u32l = MEM_W(ctx->r2, 0X4);
    // 0x8004B158: lwc1        $f8, 0x8($v0)
    ctx->f8.u32l = MEM_W(ctx->r2, 0X8);
    // 0x8004B15C: addiu       $v0, $v0, -0x20
    ctx->r2 = ADD32(ctx->r2, -0X20);
    // 0x8004B160: sltu        $at, $v0, $t7
    ctx->r1 = ctx->r2 < ctx->r15 ? 1 : 0;
    // 0x8004B164: add.s       $f12, $f12, $f4
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f12.fl = ctx->f12.fl + ctx->f4.fl;
    // 0x8004B168: add.s       $f2, $f2, $f6
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f2.fl = ctx->f2.fl + ctx->f6.fl;
    // 0x8004B16C: beq         $at, $zero, L_8004B13C
    if (ctx->r1 == 0) {
        // 0x8004B170: add.s       $f0, $f0, $f8
        CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f0.fl = ctx->f0.fl + ctx->f8.fl;
            goto L_8004B13C;
    }
    // 0x8004B170: add.s       $f0, $f0, $f8
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f0.fl = ctx->f0.fl + ctx->f8.fl;
    // 0x8004B174: lw          $a1, 0x28($a0)
    ctx->r5 = MEM_W(ctx->r4, 0X28);
L_8004B178:
    // 0x8004B178: addiu       $t8, $a1, 0x1
    ctx->r24 = ADD32(ctx->r5, 0X1);
    // 0x8004B17C: mtc1        $t8, $f10
    ctx->f10.u32l = ctx->r24;
    // 0x8004B180: lui         $at, 0x4F80
    ctx->r1 = S32(0X4F80 << 16);
    // 0x8004B184: bgez        $t8, L_8004B198
    if (SIGNED(ctx->r24) >= 0) {
        // 0x8004B188: cvt.s.w     $f14, $f10
        CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 10);
    ctx->f14.fl = CVT_S_W(ctx->f10.u32l);
            goto L_8004B198;
    }
    // 0x8004B188: cvt.s.w     $f14, $f10
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 10);
    ctx->f14.fl = CVT_S_W(ctx->f10.u32l);
    // 0x8004B18C: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
    // 0x8004B190: nop

    // 0x8004B194: add.s       $f14, $f14, $f16
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f14.fl = ctx->f14.fl + ctx->f16.fl;
L_8004B198:
    // 0x8004B198: div.s       $f18, $f12, $f14
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f18.fl = DIV_S(ctx->f12.fl, ctx->f14.fl);
    // 0x8004B19C: div.s       $f4, $f2, $f14
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f4.fl = DIV_S(ctx->f2.fl, ctx->f14.fl);
    // 0x8004B1A0: swc1        $f18, 0x44($a0)
    MEM_W(0X44, ctx->r4) = ctx->f18.u32l;
    // 0x8004B1A4: div.s       $f6, $f0, $f14
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f6.fl = DIV_S(ctx->f0.fl, ctx->f14.fl);
    // 0x8004B1A8: swc1        $f4, 0x48($a0)
    MEM_W(0X48, ctx->r4) = ctx->f4.u32l;
    // 0x8004B1AC: jr          $ra
    // 0x8004B1B0: swc1        $f6, 0x4C($a0)
    MEM_W(0X4C, ctx->r4) = ctx->f6.u32l;
    return;
    // 0x8004B1B0: swc1        $f6, 0x4C($a0)
    MEM_W(0X4C, ctx->r4) = ctx->f6.u32l;
;}
RECOMP_FUNC void func_8004B1B4(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8004B1B4: addiu       $sp, $sp, -0xB8
    ctx->r29 = ADD32(ctx->r29, -0XB8);
    // 0x8004B1B8: sw          $ra, 0x5C($sp)
    MEM_W(0X5C, ctx->r29) = ctx->r31;
    // 0x8004B1BC: sw          $s5, 0x58($sp)
    MEM_W(0X58, ctx->r29) = ctx->r21;
    // 0x8004B1C0: sw          $s4, 0x54($sp)
    MEM_W(0X54, ctx->r29) = ctx->r20;
    // 0x8004B1C4: sw          $s3, 0x50($sp)
    MEM_W(0X50, ctx->r29) = ctx->r19;
    // 0x8004B1C8: sw          $s2, 0x4C($sp)
    MEM_W(0X4C, ctx->r29) = ctx->r18;
    // 0x8004B1CC: sw          $s1, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r17;
    // 0x8004B1D0: sw          $s0, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r16;
    // 0x8004B1D4: sdc1        $f30, 0x38($sp)
    CHECK_FR(ctx, 30);
    SD(ctx->f30.u64, 0X38, ctx->r29);
    // 0x8004B1D8: sdc1        $f28, 0x30($sp)
    CHECK_FR(ctx, 28);
    SD(ctx->f28.u64, 0X30, ctx->r29);
    // 0x8004B1DC: sdc1        $f26, 0x28($sp)
    CHECK_FR(ctx, 26);
    SD(ctx->f26.u64, 0X28, ctx->r29);
    // 0x8004B1E0: sdc1        $f24, 0x20($sp)
    CHECK_FR(ctx, 24);
    SD(ctx->f24.u64, 0X20, ctx->r29);
    // 0x8004B1E4: sdc1        $f22, 0x18($sp)
    CHECK_FR(ctx, 22);
    SD(ctx->f22.u64, 0X18, ctx->r29);
    // 0x8004B1E8: sdc1        $f20, 0x10($sp)
    CHECK_FR(ctx, 20);
    SD(ctx->f20.u64, 0X10, ctx->r29);
    // 0x8004B1EC: lw          $a1, 0x28($a0)
    ctx->r5 = MEM_W(ctx->r4, 0X28);
    // 0x8004B1F0: addiu       $s5, $zero, 0xC
    ctx->r21 = ADD32(0, 0XC);
    // 0x8004B1F4: lw          $v0, 0x30($a0)
    ctx->r2 = MEM_W(ctx->r4, 0X30);
    // 0x8004B1F8: multu       $a1, $s5
    result = U64(U32(ctx->r5)) * U64(U32(ctx->r21)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x8004B1FC: sll         $t6, $a1, 5
    ctx->r14 = S32(ctx->r5 << 5);
    // 0x8004B200: lui         $t8, 0x8016
    ctx->r24 = S32(0X8016 << 16);
    // 0x8004B204: addu        $s1, $v0, $t6
    ctx->r17 = ADD32(ctx->r2, ctx->r14);
    // 0x8004B208: addiu       $t8, $t8, -0x7BB0
    ctx->r24 = ADD32(ctx->r24, -0X7BB0);
    // 0x8004B20C: sltu        $at, $s1, $v0
    ctx->r1 = ctx->r17 < ctx->r2 ? 1 : 0;
    // 0x8004B210: or          $s3, $a0, $zero
    ctx->r19 = ctx->r4 | 0;
    // 0x8004B214: lwc1        $f30, 0xC($a0)
    ctx->f30.u32l = MEM_W(ctx->r4, 0XC);
    // 0x8004B218: mflo        $t7
    ctx->r15 = lo;
    // 0x8004B21C: addu        $v1, $t7, $t8
    ctx->r3 = ADD32(ctx->r15, ctx->r24);
    // 0x8004B220: bnel        $at, $zero, L_8004B298
    if (ctx->r1 != 0) {
        // 0x8004B224: addiu       $t0, $a1, -0x1
        ctx->r8 = ADD32(ctx->r5, -0X1);
            goto L_8004B298;
    }
    goto skip_0;
    // 0x8004B224: addiu       $t0, $a1, -0x1
    ctx->r8 = ADD32(ctx->r5, -0X1);
    skip_0:
    // 0x8004B228: lwc1        $f2, 0x0($s1)
    ctx->f2.u32l = MEM_W(ctx->r17, 0X0);
L_8004B22C:
    // 0x8004B22C: addiu       $s1, $s1, -0x20
    ctx->r17 = ADD32(ctx->r17, -0X20);
    // 0x8004B230: addiu       $v1, $v1, -0xC
    ctx->r3 = ADD32(ctx->r3, -0XC);
    // 0x8004B234: swc1        $f2, 0xC($v1)
    MEM_W(0XC, ctx->r3) = ctx->f2.u32l;
    // 0x8004B238: lwc1        $f4, 0x2C($s1)
    ctx->f4.u32l = MEM_W(ctx->r17, 0X2C);
    // 0x8004B23C: mul.s       $f6, $f30, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 30);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f30.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = MUL_S(ctx->f30.fl, ctx->f4.fl);
    // 0x8004B240: add.s       $f8, $f2, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = ctx->f2.fl + ctx->f6.fl;
    // 0x8004B244: lwc1        $f2, 0x24($s1)
    ctx->f2.u32l = MEM_W(ctx->r17, 0X24);
    // 0x8004B248: swc1        $f8, 0x20($s1)
    MEM_W(0X20, ctx->r17) = ctx->f8.u32l;
    // 0x8004B24C: swc1        $f2, 0x10($v1)
    MEM_W(0X10, ctx->r3) = ctx->f2.u32l;
    // 0x8004B250: lwc1        $f10, 0x30($s1)
    ctx->f10.u32l = MEM_W(ctx->r17, 0X30);
    // 0x8004B254: mul.s       $f4, $f30, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 30);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f30.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f4.fl = MUL_S(ctx->f30.fl, ctx->f10.fl);
    // 0x8004B258: add.s       $f6, $f2, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = ctx->f2.fl + ctx->f4.fl;
    // 0x8004B25C: lwc1        $f2, 0x28($s1)
    ctx->f2.u32l = MEM_W(ctx->r17, 0X28);
    // 0x8004B260: swc1        $f6, 0x24($s1)
    MEM_W(0X24, ctx->r17) = ctx->f6.u32l;
    // 0x8004B264: swc1        $f2, 0x14($v1)
    MEM_W(0X14, ctx->r3) = ctx->f2.u32l;
    // 0x8004B268: lwc1        $f8, 0x34($s1)
    ctx->f8.u32l = MEM_W(ctx->r17, 0X34);
    // 0x8004B26C: mul.s       $f10, $f30, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 30);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f30.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = MUL_S(ctx->f30.fl, ctx->f8.fl);
    // 0x8004B270: add.s       $f4, $f2, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f4.fl = ctx->f2.fl + ctx->f10.fl;
    // 0x8004B274: swc1        $f4, 0x28($s1)
    MEM_W(0X28, ctx->r17) = ctx->f4.u32l;
    // 0x8004B278: lw          $v0, 0x30($s3)
    ctx->r2 = MEM_W(ctx->r19, 0X30);
    // 0x8004B27C: sltu        $at, $s1, $v0
    ctx->r1 = ctx->r17 < ctx->r2 ? 1 : 0;
    // 0x8004B280: beql        $at, $zero, L_8004B22C
    if (ctx->r1 == 0) {
        // 0x8004B284: lwc1        $f2, 0x0($s1)
        ctx->f2.u32l = MEM_W(ctx->r17, 0X0);
            goto L_8004B22C;
    }
    goto skip_1;
    // 0x8004B284: lwc1        $f2, 0x0($s1)
    ctx->f2.u32l = MEM_W(ctx->r17, 0X0);
    skip_1:
    // 0x8004B288: lw          $a1, 0x28($s3)
    ctx->r5 = MEM_W(ctx->r19, 0X28);
    // 0x8004B28C: sll         $t9, $a1, 5
    ctx->r25 = S32(ctx->r5 << 5);
    // 0x8004B290: addu        $s1, $v0, $t9
    ctx->r17 = ADD32(ctx->r2, ctx->r25);
    // 0x8004B294: addiu       $t0, $a1, -0x1
    ctx->r8 = ADD32(ctx->r5, -0X1);
L_8004B298:
    // 0x8004B298: mtc1        $t0, $f8
    ctx->f8.u32l = ctx->r8;
    // 0x8004B29C: lwc1        $f6, 0x20($s3)
    ctx->f6.u32l = MEM_W(ctx->r19, 0X20);
    // 0x8004B2A0: bgez        $t0, L_8004B2B8
    if (SIGNED(ctx->r8) >= 0) {
        // 0x8004B2A4: cvt.s.w     $f10, $f8
        CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.fl = CVT_S_W(ctx->f8.u32l);
            goto L_8004B2B8;
    }
    // 0x8004B2A4: cvt.s.w     $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.fl = CVT_S_W(ctx->f8.u32l);
    // 0x8004B2A8: lui         $at, 0x4F80
    ctx->r1 = S32(0X4F80 << 16);
    // 0x8004B2AC: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x8004B2B0: nop

    // 0x8004B2B4: add.s       $f10, $f10, $f4
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f10.fl = ctx->f10.fl + ctx->f4.fl;
L_8004B2B8:
    // 0x8004B2B8: mul.s       $f8, $f6, $f10
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f8.fl = MUL_S(ctx->f6.fl, ctx->f10.fl);
    // 0x8004B2BC: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x8004B2C0: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x8004B2C4: lw          $s4, 0x24($s3)
    ctx->r20 = MEM_W(ctx->r19, 0X24);
    // 0x8004B2C8: lui         $at, 0x3F00
    ctx->r1 = S32(0X3F00 << 16);
    // 0x8004B2CC: mtc1        $at, $f10
    ctx->f10.u32l = ctx->r1;
    // 0x8004B2D0: add.s       $f6, $f8, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = ctx->f8.fl + ctx->f4.fl;
    // 0x8004B2D4: beq         $s4, $zero, L_8004B468
    if (ctx->r20 == 0) {
        // 0x8004B2D8: div.s       $f30, $f10, $f6
        CHECK_FR(ctx, 30);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f30.fl = DIV_S(ctx->f10.fl, ctx->f6.fl);
            goto L_8004B468;
    }
    // 0x8004B2D8: div.s       $f30, $f10, $f6
    CHECK_FR(ctx, 30);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f30.fl = DIV_S(ctx->f10.fl, ctx->f6.fl);
    // 0x8004B2DC: mtc1        $zero, $f28
    ctx->f28.u32l = 0;
    // 0x8004B2E0: nop

    // 0x8004B2E4: sltu        $at, $s1, $v0
    ctx->r1 = ctx->r17 < ctx->r2 ? 1 : 0;
L_8004B2E8:
    // 0x8004B2E8: bnel        $at, $zero, L_8004B314
    if (ctx->r1 != 0) {
        // 0x8004B2EC: lw          $t1, 0x2C($s3)
        ctx->r9 = MEM_W(ctx->r19, 0X2C);
            goto L_8004B314;
    }
    goto skip_2;
    // 0x8004B2EC: lw          $t1, 0x2C($s3)
    ctx->r9 = MEM_W(ctx->r19, 0X2C);
    skip_2:
    // 0x8004B2F0: swc1        $f28, 0x14($s1)
    MEM_W(0X14, ctx->r17) = ctx->f28.u32l;
L_8004B2F4:
    // 0x8004B2F4: swc1        $f28, 0x10($s1)
    MEM_W(0X10, ctx->r17) = ctx->f28.u32l;
    // 0x8004B2F8: swc1        $f28, 0xC($s1)
    MEM_W(0XC, ctx->r17) = ctx->f28.u32l;
    // 0x8004B2FC: lw          $v0, 0x30($s3)
    ctx->r2 = MEM_W(ctx->r19, 0X30);
    // 0x8004B300: addiu       $s1, $s1, -0x20
    ctx->r17 = ADD32(ctx->r17, -0X20);
    // 0x8004B304: sltu        $at, $s1, $v0
    ctx->r1 = ctx->r17 < ctx->r2 ? 1 : 0;
    // 0x8004B308: beql        $at, $zero, L_8004B2F4
    if (ctx->r1 == 0) {
        // 0x8004B30C: swc1        $f28, 0x14($s1)
        MEM_W(0X14, ctx->r17) = ctx->f28.u32l;
            goto L_8004B2F4;
    }
    goto skip_3;
    // 0x8004B30C: swc1        $f28, 0x14($s1)
    MEM_W(0X14, ctx->r17) = ctx->f28.u32l;
    skip_3:
    // 0x8004B310: lw          $t1, 0x2C($s3)
    ctx->r9 = MEM_W(ctx->r19, 0X2C);
L_8004B314:
    // 0x8004B314: lw          $v1, 0x34($s3)
    ctx->r3 = MEM_W(ctx->r19, 0X34);
    // 0x8004B318: multu       $t1, $s5
    result = U64(U32(ctx->r9)) * U64(U32(ctx->r21)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x8004B31C: mflo        $t2
    ctx->r10 = lo;
    // 0x8004B320: addu        $s2, $v1, $t2
    ctx->r18 = ADD32(ctx->r3, ctx->r10);
    // 0x8004B324: sltu        $at, $s2, $v1
    ctx->r1 = ctx->r18 < ctx->r3 ? 1 : 0;
    // 0x8004B328: bnel        $at, $zero, L_8004B3F8
    if (ctx->r1 != 0) {
        // 0x8004B32C: lw          $a1, 0x28($s3)
        ctx->r5 = MEM_W(ctx->r19, 0X28);
            goto L_8004B3F8;
    }
    goto skip_4;
    // 0x8004B32C: lw          $a1, 0x28($s3)
    ctx->r5 = MEM_W(ctx->r19, 0X28);
    skip_4:
L_8004B330:
    // 0x8004B330: lw          $s1, 0x0($s2)
    ctx->r17 = MEM_W(ctx->r18, 0X0);
    // 0x8004B334: lw          $s0, 0x4($s2)
    ctx->r16 = MEM_W(ctx->r18, 0X4);
    // 0x8004B338: lwc1        $f4, 0x0($s1)
    ctx->f4.u32l = MEM_W(ctx->r17, 0X0);
    // 0x8004B33C: lwc1        $f8, 0x0($s0)
    ctx->f8.u32l = MEM_W(ctx->r16, 0X0);
    // 0x8004B340: lwc1        $f6, 0x4($s1)
    ctx->f6.u32l = MEM_W(ctx->r17, 0X4);
    // 0x8004B344: lwc1        $f10, 0x4($s0)
    ctx->f10.u32l = MEM_W(ctx->r16, 0X4);
    // 0x8004B348: sub.s       $f22, $f8, $f4
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f22.fl = ctx->f8.fl - ctx->f4.fl;
    // 0x8004B34C: lwc1        $f4, 0x8($s1)
    ctx->f4.u32l = MEM_W(ctx->r17, 0X8);
    // 0x8004B350: lwc1        $f8, 0x8($s0)
    ctx->f8.u32l = MEM_W(ctx->r16, 0X8);
    // 0x8004B354: sub.s       $f24, $f10, $f6
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f24.fl = ctx->f10.fl - ctx->f6.fl;
    // 0x8004B358: mul.s       $f10, $f22, $f22
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f10.fl = MUL_S(ctx->f22.fl, ctx->f22.fl);
    // 0x8004B35C: sub.s       $f26, $f8, $f4
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f26.fl = ctx->f8.fl - ctx->f4.fl;
    // 0x8004B360: mul.s       $f6, $f24, $f24
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 24);
    NAN_CHECK(ctx->f24.fl); NAN_CHECK(ctx->f24.fl); 
    ctx->f6.fl = MUL_S(ctx->f24.fl, ctx->f24.fl);
    // 0x8004B364: add.s       $f8, $f10, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = ctx->f10.fl + ctx->f6.fl;
    // 0x8004B368: mul.s       $f4, $f26, $f26
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 26);
    NAN_CHECK(ctx->f26.fl); NAN_CHECK(ctx->f26.fl); 
    ctx->f4.fl = MUL_S(ctx->f26.fl, ctx->f26.fl);
    // 0x8004B36C: jal         0x800C7010
    // 0x8004B370: add.s       $f12, $f8, $f4
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f12.fl = ctx->f8.fl + ctx->f4.fl;
    _nsqrtf(rdram, ctx);
        goto after_0;
    // 0x8004B370: add.s       $f12, $f8, $f4
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f12.fl = ctx->f8.fl + ctx->f4.fl;
    after_0:
    // 0x8004B374: lwc1        $f10, 0x8($s2)
    ctx->f10.u32l = MEM_W(ctx->r18, 0X8);
    // 0x8004B378: lwc1        $f8, 0xC($s0)
    ctx->f8.u32l = MEM_W(ctx->r16, 0XC);
    // 0x8004B37C: addiu       $s2, $s2, -0xC
    ctx->r18 = ADD32(ctx->r18, -0XC);
    // 0x8004B380: div.s       $f6, $f10, $f0
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f6.fl = DIV_S(ctx->f10.fl, ctx->f0.fl);
    // 0x8004B384: lwc1        $f10, 0x10($s0)
    ctx->f10.u32l = MEM_W(ctx->r16, 0X10);
    // 0x8004B388: sub.s       $f20, $f6, $f30
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 30);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f30.fl); 
    ctx->f20.fl = ctx->f6.fl - ctx->f30.fl;
    // 0x8004B38C: mul.s       $f12, $f22, $f20
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f12.fl = MUL_S(ctx->f22.fl, ctx->f20.fl);
    // 0x8004B390: nop

    // 0x8004B394: mul.s       $f14, $f24, $f20
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f24.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f14.fl = MUL_S(ctx->f24.fl, ctx->f20.fl);
    // 0x8004B398: nop

    // 0x8004B39C: mul.s       $f16, $f26, $f20
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f26.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f16.fl = MUL_S(ctx->f26.fl, ctx->f20.fl);
    // 0x8004B3A0: add.s       $f4, $f8, $f12
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f4.fl = ctx->f8.fl + ctx->f12.fl;
    // 0x8004B3A4: lwc1        $f8, 0x14($s0)
    ctx->f8.u32l = MEM_W(ctx->r16, 0X14);
    // 0x8004B3A8: add.s       $f6, $f10, $f14
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f6.fl = ctx->f10.fl + ctx->f14.fl;
    // 0x8004B3AC: swc1        $f4, 0xC($s0)
    MEM_W(0XC, ctx->r16) = ctx->f4.u32l;
    // 0x8004B3B0: add.s       $f4, $f8, $f16
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f4.fl = ctx->f8.fl + ctx->f16.fl;
    // 0x8004B3B4: swc1        $f6, 0x10($s0)
    MEM_W(0X10, ctx->r16) = ctx->f6.u32l;
    // 0x8004B3B8: swc1        $f4, 0x14($s0)
    MEM_W(0X14, ctx->r16) = ctx->f4.u32l;
    // 0x8004B3BC: lwc1        $f10, 0xC($s1)
    ctx->f10.u32l = MEM_W(ctx->r17, 0XC);
    // 0x8004B3C0: lwc1        $f8, 0x10($s1)
    ctx->f8.u32l = MEM_W(ctx->r17, 0X10);
    // 0x8004B3C4: sub.s       $f6, $f10, $f12
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f6.fl = ctx->f10.fl - ctx->f12.fl;
    // 0x8004B3C8: lwc1        $f10, 0x14($s1)
    ctx->f10.u32l = MEM_W(ctx->r17, 0X14);
    // 0x8004B3CC: sub.s       $f4, $f8, $f14
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f4.fl = ctx->f8.fl - ctx->f14.fl;
    // 0x8004B3D0: swc1        $f6, 0xC($s1)
    MEM_W(0XC, ctx->r17) = ctx->f6.u32l;
    // 0x8004B3D4: sub.s       $f6, $f10, $f16
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f6.fl = ctx->f10.fl - ctx->f16.fl;
    // 0x8004B3D8: swc1        $f4, 0x10($s1)
    MEM_W(0X10, ctx->r17) = ctx->f4.u32l;
    // 0x8004B3DC: swc1        $f6, 0x14($s1)
    MEM_W(0X14, ctx->r17) = ctx->f6.u32l;
    // 0x8004B3E0: lw          $t3, 0x34($s3)
    ctx->r11 = MEM_W(ctx->r19, 0X34);
    // 0x8004B3E4: sltu        $at, $s2, $t3
    ctx->r1 = ctx->r18 < ctx->r11 ? 1 : 0;
    // 0x8004B3E8: beq         $at, $zero, L_8004B330
    if (ctx->r1 == 0) {
        // 0x8004B3EC: nop
    
            goto L_8004B330;
    }
    // 0x8004B3EC: nop

    // 0x8004B3F0: lw          $v0, 0x30($s3)
    ctx->r2 = MEM_W(ctx->r19, 0X30);
    // 0x8004B3F4: lw          $a1, 0x28($s3)
    ctx->r5 = MEM_W(ctx->r19, 0X28);
L_8004B3F8:
    // 0x8004B3F8: addiu       $s4, $s4, -0x1
    ctx->r20 = ADD32(ctx->r20, -0X1);
    // 0x8004B3FC: sll         $t4, $a1, 5
    ctx->r12 = S32(ctx->r5 << 5);
    // 0x8004B400: addu        $s1, $v0, $t4
    ctx->r17 = ADD32(ctx->r2, ctx->r12);
    // 0x8004B404: sltu        $at, $s1, $v0
    ctx->r1 = ctx->r17 < ctx->r2 ? 1 : 0;
    // 0x8004B408: bne         $at, $zero, L_8004B460
    if (ctx->r1 != 0) {
        // 0x8004B40C: nop
    
            goto L_8004B460;
    }
    // 0x8004B40C: nop

    // 0x8004B410: lwc1        $f8, 0x0($s1)
    ctx->f8.u32l = MEM_W(ctx->r17, 0X0);
L_8004B414:
    // 0x8004B414: lwc1        $f4, 0xC($s1)
    ctx->f4.u32l = MEM_W(ctx->r17, 0XC);
    // 0x8004B418: lwc1        $f6, 0x4($s1)
    ctx->f6.u32l = MEM_W(ctx->r17, 0X4);
    // 0x8004B41C: addiu       $s1, $s1, -0x20
    ctx->r17 = ADD32(ctx->r17, -0X20);
    // 0x8004B420: add.s       $f10, $f8, $f4
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f10.fl = ctx->f8.fl + ctx->f4.fl;
    // 0x8004B424: lwc1        $f8, 0x30($s1)
    ctx->f8.u32l = MEM_W(ctx->r17, 0X30);
    // 0x8004B428: add.s       $f4, $f6, $f8
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f4.fl = ctx->f6.fl + ctx->f8.fl;
    // 0x8004B42C: swc1        $f10, 0x20($s1)
    MEM_W(0X20, ctx->r17) = ctx->f10.u32l;
    // 0x8004B430: lwc1        $f10, 0x28($s1)
    ctx->f10.u32l = MEM_W(ctx->r17, 0X28);
    // 0x8004B434: lwc1        $f6, 0x34($s1)
    ctx->f6.u32l = MEM_W(ctx->r17, 0X34);
    // 0x8004B438: swc1        $f4, 0x24($s1)
    MEM_W(0X24, ctx->r17) = ctx->f4.u32l;
    // 0x8004B43C: add.s       $f8, $f10, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = ctx->f10.fl + ctx->f6.fl;
    // 0x8004B440: swc1        $f8, 0x28($s1)
    MEM_W(0X28, ctx->r17) = ctx->f8.u32l;
    // 0x8004B444: lw          $v0, 0x30($s3)
    ctx->r2 = MEM_W(ctx->r19, 0X30);
    // 0x8004B448: sltu        $at, $s1, $v0
    ctx->r1 = ctx->r17 < ctx->r2 ? 1 : 0;
    // 0x8004B44C: beql        $at, $zero, L_8004B414
    if (ctx->r1 == 0) {
        // 0x8004B450: lwc1        $f8, 0x0($s1)
        ctx->f8.u32l = MEM_W(ctx->r17, 0X0);
            goto L_8004B414;
    }
    goto skip_5;
    // 0x8004B450: lwc1        $f8, 0x0($s1)
    ctx->f8.u32l = MEM_W(ctx->r17, 0X0);
    skip_5:
    // 0x8004B454: lw          $a1, 0x28($s3)
    ctx->r5 = MEM_W(ctx->r19, 0X28);
    // 0x8004B458: sll         $t5, $a1, 5
    ctx->r13 = S32(ctx->r5 << 5);
    // 0x8004B45C: addu        $s1, $v0, $t5
    ctx->r17 = ADD32(ctx->r2, ctx->r13);
L_8004B460:
    // 0x8004B460: bnel        $s4, $zero, L_8004B2E8
    if (ctx->r20 != 0) {
        // 0x8004B464: sltu        $at, $s1, $v0
        ctx->r1 = ctx->r17 < ctx->r2 ? 1 : 0;
            goto L_8004B2E8;
    }
    goto skip_6;
    // 0x8004B464: sltu        $at, $s1, $v0
    ctx->r1 = ctx->r17 < ctx->r2 ? 1 : 0;
    skip_6:
L_8004B468:
    // 0x8004B468: multu       $a1, $s5
    result = U64(U32(ctx->r5)) * U64(U32(ctx->r21)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x8004B46C: mtc1        $zero, $f18
    ctx->f18.u32l = 0;
    // 0x8004B470: lui         $t7, 0x8016
    ctx->r15 = S32(0X8016 << 16);
    // 0x8004B474: addiu       $t7, $t7, -0x7BB0
    ctx->r15 = ADD32(ctx->r15, -0X7BB0);
    // 0x8004B478: sltu        $at, $s1, $v0
    ctx->r1 = ctx->r17 < ctx->r2 ? 1 : 0;
    // 0x8004B47C: mov.s       $f14, $f18
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 18);
    ctx->f14.fl = ctx->f18.fl;
    // 0x8004B480: mov.s       $f16, $f18
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 18);
    ctx->f16.fl = ctx->f18.fl;
    // 0x8004B484: mflo        $t6
    ctx->r14 = lo;
    // 0x8004B488: addu        $v1, $t6, $t7
    ctx->r3 = ADD32(ctx->r14, ctx->r15);
    // 0x8004B48C: bnel        $at, $zero, L_8004B560
    if (ctx->r1 != 0) {
        // 0x8004B490: addiu       $t9, $a1, 0x1
        ctx->r25 = ADD32(ctx->r5, 0X1);
            goto L_8004B560;
    }
    goto skip_7;
    // 0x8004B490: addiu       $t9, $a1, 0x1
    ctx->r25 = ADD32(ctx->r5, 0X1);
    skip_7:
L_8004B494:
    // 0x8004B494: lwc1        $f2, 0x0($s1)
    ctx->f2.u32l = MEM_W(ctx->r17, 0X0);
    // 0x8004B498: lwc1        $f4, 0x0($v1)
    ctx->f4.u32l = MEM_W(ctx->r3, 0X0);
    // 0x8004B49C: lwc1        $f10, 0x4($v1)
    ctx->f10.u32l = MEM_W(ctx->r3, 0X4);
    // 0x8004B4A0: add.s       $f18, $f18, $f2
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f18.fl = ctx->f18.fl + ctx->f2.fl;
    // 0x8004B4A4: lwc1        $f12, 0x5C($s3)
    ctx->f12.u32l = MEM_W(ctx->r19, 0X5C);
    // 0x8004B4A8: lwc1        $f6, 0x8($v1)
    ctx->f6.u32l = MEM_W(ctx->r3, 0X8);
    // 0x8004B4AC: sub.s       $f22, $f2, $f4
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f22.fl = ctx->f2.fl - ctx->f4.fl;
    // 0x8004B4B0: lwc1        $f2, 0x4($s1)
    ctx->f2.u32l = MEM_W(ctx->r17, 0X4);
    // 0x8004B4B4: lwc1        $f4, 0x60($s3)
    ctx->f4.u32l = MEM_W(ctx->r19, 0X60);
    // 0x8004B4B8: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x8004B4BC: sub.s       $f24, $f2, $f10
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f24.fl = ctx->f2.fl - ctx->f10.fl;
    // 0x8004B4C0: mul.s       $f8, $f22, $f12
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f8.fl = MUL_S(ctx->f22.fl, ctx->f12.fl);
    // 0x8004B4C4: lwc1        $f0, 0x18($s1)
    ctx->f0.u32l = MEM_W(ctx->r17, 0X18);
    // 0x8004B4C8: add.s       $f16, $f16, $f2
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f16.fl = ctx->f16.fl + ctx->f2.fl;
    // 0x8004B4CC: mul.s       $f10, $f24, $f4
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f24.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f10.fl = MUL_S(ctx->f24.fl, ctx->f4.fl);
    // 0x8004B4D0: lwc1        $f2, 0x8($s1)
    ctx->f2.u32l = MEM_W(ctx->r17, 0X8);
    // 0x8004B4D4: lwc1        $f4, 0x64($s3)
    ctx->f4.u32l = MEM_W(ctx->r19, 0X64);
    // 0x8004B4D8: addiu       $s1, $s1, -0x20
    ctx->r17 = ADD32(ctx->r17, -0X20);
    // 0x8004B4DC: addiu       $v1, $v1, -0xC
    ctx->r3 = ADD32(ctx->r3, -0XC);
    // 0x8004B4E0: sub.s       $f26, $f2, $f6
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f26.fl = ctx->f2.fl - ctx->f6.fl;
    // 0x8004B4E4: add.s       $f6, $f8, $f10
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f6.fl = ctx->f8.fl + ctx->f10.fl;
    // 0x8004B4E8: mul.s       $f8, $f26, $f4
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f26.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f8.fl = MUL_S(ctx->f26.fl, ctx->f4.fl);
    // 0x8004B4EC: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x8004B4F0: add.s       $f14, $f14, $f2
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f14.fl = ctx->f14.fl + ctx->f2.fl;
    // 0x8004B4F4: add.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = ctx->f6.fl + ctx->f8.fl;
    // 0x8004B4F8: sub.s       $f6, $f4, $f0
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f6.fl = ctx->f4.fl - ctx->f0.fl;
    // 0x8004B4FC: mul.s       $f20, $f6, $f10
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f20.fl = MUL_S(ctx->f6.fl, ctx->f10.fl);
    // 0x8004B500: nop

    // 0x8004B504: mul.s       $f8, $f12, $f20
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f8.fl = MUL_S(ctx->f12.fl, ctx->f20.fl);
    // 0x8004B508: nop

    // 0x8004B50C: mul.s       $f4, $f0, $f22
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f4.fl = MUL_S(ctx->f0.fl, ctx->f22.fl);
    // 0x8004B510: add.s       $f6, $f8, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = ctx->f8.fl + ctx->f4.fl;
    // 0x8004B514: swc1        $f6, 0x2C($s1)
    MEM_W(0X2C, ctx->r17) = ctx->f6.u32l;
    // 0x8004B518: lwc1        $f10, 0x60($s3)
    ctx->f10.u32l = MEM_W(ctx->r19, 0X60);
    // 0x8004B51C: mul.s       $f8, $f10, $f20
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f8.fl = MUL_S(ctx->f10.fl, ctx->f20.fl);
    // 0x8004B520: nop

    // 0x8004B524: mul.s       $f4, $f0, $f24
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 24);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f24.fl); 
    ctx->f4.fl = MUL_S(ctx->f0.fl, ctx->f24.fl);
    // 0x8004B528: add.s       $f6, $f8, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = ctx->f8.fl + ctx->f4.fl;
    // 0x8004B52C: swc1        $f6, 0x30($s1)
    MEM_W(0X30, ctx->r17) = ctx->f6.u32l;
    // 0x8004B530: lwc1        $f10, 0x64($s3)
    ctx->f10.u32l = MEM_W(ctx->r19, 0X64);
    // 0x8004B534: mul.s       $f8, $f10, $f20
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f8.fl = MUL_S(ctx->f10.fl, ctx->f20.fl);
    // 0x8004B538: nop

    // 0x8004B53C: mul.s       $f4, $f0, $f26
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 26);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f26.fl); 
    ctx->f4.fl = MUL_S(ctx->f0.fl, ctx->f26.fl);
    // 0x8004B540: add.s       $f6, $f8, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = ctx->f8.fl + ctx->f4.fl;
    // 0x8004B544: swc1        $f6, 0x34($s1)
    MEM_W(0X34, ctx->r17) = ctx->f6.u32l;
    // 0x8004B548: lw          $t8, 0x30($s3)
    ctx->r24 = MEM_W(ctx->r19, 0X30);
    // 0x8004B54C: sltu        $at, $s1, $t8
    ctx->r1 = ctx->r17 < ctx->r24 ? 1 : 0;
    // 0x8004B550: beq         $at, $zero, L_8004B494
    if (ctx->r1 == 0) {
        // 0x8004B554: nop
    
            goto L_8004B494;
    }
    // 0x8004B554: nop

    // 0x8004B558: lw          $a1, 0x28($s3)
    ctx->r5 = MEM_W(ctx->r19, 0X28);
    // 0x8004B55C: addiu       $t9, $a1, 0x1
    ctx->r25 = ADD32(ctx->r5, 0X1);
L_8004B560:
    // 0x8004B560: mtc1        $t9, $f10
    ctx->f10.u32l = ctx->r25;
    // 0x8004B564: lui         $at, 0x4F80
    ctx->r1 = S32(0X4F80 << 16);
    // 0x8004B568: bgez        $t9, L_8004B57C
    if (SIGNED(ctx->r25) >= 0) {
        // 0x8004B56C: cvt.s.w     $f20, $f10
        CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 10);
    ctx->f20.fl = CVT_S_W(ctx->f10.u32l);
            goto L_8004B57C;
    }
    // 0x8004B56C: cvt.s.w     $f20, $f10
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 10);
    ctx->f20.fl = CVT_S_W(ctx->f10.u32l);
    // 0x8004B570: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x8004B574: nop

    // 0x8004B578: add.s       $f20, $f20, $f8
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f20.fl = ctx->f20.fl + ctx->f8.fl;
L_8004B57C:
    // 0x8004B57C: div.s       $f28, $f18, $f20
    CHECK_FR(ctx, 28);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f28.fl = DIV_S(ctx->f18.fl, ctx->f20.fl);
    // 0x8004B580: lwc1        $f4, 0x44($s3)
    ctx->f4.u32l = MEM_W(ctx->r19, 0X44);
    // 0x8004B584: swc1        $f4, 0xA0($sp)
    MEM_W(0XA0, ctx->r29) = ctx->f4.u32l;
    // 0x8004B588: lwc1        $f10, 0x48($s3)
    ctx->f10.u32l = MEM_W(ctx->r19, 0X48);
    // 0x8004B58C: div.s       $f30, $f16, $f20
    CHECK_FR(ctx, 30);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f30.fl = DIV_S(ctx->f16.fl, ctx->f20.fl);
    // 0x8004B590: swc1        $f28, 0x44($s3)
    MEM_W(0X44, ctx->r19) = ctx->f28.u32l;
    // 0x8004B594: lwc1        $f6, 0xA0($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0XA0);
    // 0x8004B598: sub.s       $f22, $f28, $f6
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 28);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f28.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f22.fl = ctx->f28.fl - ctx->f6.fl;
    // 0x8004B59C: swc1        $f22, 0x50($s3)
    MEM_W(0X50, ctx->r19) = ctx->f22.u32l;
    // 0x8004B5A0: swc1        $f10, 0x9C($sp)
    MEM_W(0X9C, ctx->r29) = ctx->f10.u32l;
    // 0x8004B5A4: lwc1        $f4, 0x4C($s3)
    ctx->f4.u32l = MEM_W(ctx->r19, 0X4C);
    // 0x8004B5A8: div.s       $f6, $f14, $f20
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f6.fl = DIV_S(ctx->f14.fl, ctx->f20.fl);
    // 0x8004B5AC: swc1        $f30, 0x48($s3)
    MEM_W(0X48, ctx->r19) = ctx->f30.u32l;
    // 0x8004B5B0: lwc1        $f8, 0x9C($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X9C);
    // 0x8004B5B4: sub.s       $f24, $f30, $f8
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 30);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f30.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f24.fl = ctx->f30.fl - ctx->f8.fl;
    // 0x8004B5B8: swc1        $f24, 0x54($s3)
    MEM_W(0X54, ctx->r19) = ctx->f24.u32l;
    // 0x8004B5BC: swc1        $f4, 0x98($sp)
    MEM_W(0X98, ctx->r29) = ctx->f4.u32l;
    // 0x8004B5C0: swc1        $f6, 0x60($sp)
    MEM_W(0X60, ctx->r29) = ctx->f6.u32l;
    // 0x8004B5C4: lwc1        $f10, 0x60($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0X60);
    // 0x8004B5C8: mul.s       $f6, $f22, $f22
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f6.fl = MUL_S(ctx->f22.fl, ctx->f22.fl);
    // 0x8004B5CC: swc1        $f10, 0x4C($s3)
    MEM_W(0X4C, ctx->r19) = ctx->f10.u32l;
    // 0x8004B5D0: lwc1        $f4, 0x98($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X98);
    // 0x8004B5D4: lwc1        $f8, 0x60($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X60);
    // 0x8004B5D8: mul.s       $f10, $f24, $f24
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 24);
    NAN_CHECK(ctx->f24.fl); NAN_CHECK(ctx->f24.fl); 
    ctx->f10.fl = MUL_S(ctx->f24.fl, ctx->f24.fl);
    // 0x8004B5DC: sub.s       $f26, $f8, $f4
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f26.fl = ctx->f8.fl - ctx->f4.fl;
    // 0x8004B5E0: mul.s       $f4, $f26, $f26
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 26);
    NAN_CHECK(ctx->f26.fl); NAN_CHECK(ctx->f26.fl); 
    ctx->f4.fl = MUL_S(ctx->f26.fl, ctx->f26.fl);
    // 0x8004B5E4: add.s       $f8, $f6, $f10
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f8.fl = ctx->f6.fl + ctx->f10.fl;
    // 0x8004B5E8: mtc1        $zero, $f6
    ctx->f6.u32l = 0;
    // 0x8004B5EC: swc1        $f26, 0x58($s3)
    MEM_W(0X58, ctx->r19) = ctx->f26.u32l;
    // 0x8004B5F0: add.s       $f20, $f8, $f4
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f20.fl = ctx->f8.fl + ctx->f4.fl;
    // 0x8004B5F4: c.eq.s      $f20, $f6
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 6);
    c1cs = ctx->f20.fl == ctx->f6.fl;
    // 0x8004B5F8: nop

    // 0x8004B5FC: bc1tl       L_8004B630
    if (c1cs) {
        // 0x8004B600: mtc1        $zero, $f0
        ctx->f0.u32l = 0;
            goto L_8004B630;
    }
    goto skip_8;
    // 0x8004B600: mtc1        $zero, $f0
    ctx->f0.u32l = 0;
    skip_8:
    // 0x8004B604: jal         0x800C7010
    // 0x8004B608: mov.s       $f12, $f20
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 20);
    ctx->f12.fl = ctx->f20.fl;
    _nsqrtf(rdram, ctx);
        goto after_1;
    // 0x8004B608: mov.s       $f12, $f20
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 20);
    ctx->f12.fl = ctx->f20.fl;
    after_1:
    // 0x8004B60C: div.s       $f10, $f22, $f0
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f10.fl = DIV_S(ctx->f22.fl, ctx->f0.fl);
    // 0x8004B610: swc1        $f0, 0x68($s3)
    MEM_W(0X68, ctx->r19) = ctx->f0.u32l;
    // 0x8004B614: div.s       $f8, $f24, $f0
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f24.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f8.fl = DIV_S(ctx->f24.fl, ctx->f0.fl);
    // 0x8004B618: swc1        $f10, 0x5C($s3)
    MEM_W(0X5C, ctx->r19) = ctx->f10.u32l;
    // 0x8004B61C: div.s       $f4, $f26, $f0
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f26.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f4.fl = DIV_S(ctx->f26.fl, ctx->f0.fl);
    // 0x8004B620: swc1        $f8, 0x60($s3)
    MEM_W(0X60, ctx->r19) = ctx->f8.u32l;
    // 0x8004B624: b           L_8004B644
    // 0x8004B628: swc1        $f4, 0x64($s3)
    MEM_W(0X64, ctx->r19) = ctx->f4.u32l;
        goto L_8004B644;
    // 0x8004B628: swc1        $f4, 0x64($s3)
    MEM_W(0X64, ctx->r19) = ctx->f4.u32l;
    // 0x8004B62C: mtc1        $zero, $f0
    ctx->f0.u32l = 0;
L_8004B630:
    // 0x8004B630: nop

    // 0x8004B634: swc1        $f0, 0x64($s3)
    MEM_W(0X64, ctx->r19) = ctx->f0.u32l;
    // 0x8004B638: swc1        $f0, 0x60($s3)
    MEM_W(0X60, ctx->r19) = ctx->f0.u32l;
    // 0x8004B63C: swc1        $f0, 0x5C($s3)
    MEM_W(0X5C, ctx->r19) = ctx->f0.u32l;
    // 0x8004B640: swc1        $f0, 0x68($s3)
    MEM_W(0X68, ctx->r19) = ctx->f0.u32l;
L_8004B644:
    // 0x8004B644: lw          $ra, 0x5C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X5C);
    // 0x8004B648: ldc1        $f20, 0x10($sp)
    CHECK_FR(ctx, 20);
    ctx->f20.u64 = LD(ctx->r29, 0X10);
    // 0x8004B64C: ldc1        $f22, 0x18($sp)
    CHECK_FR(ctx, 22);
    ctx->f22.u64 = LD(ctx->r29, 0X18);
    // 0x8004B650: ldc1        $f24, 0x20($sp)
    CHECK_FR(ctx, 24);
    ctx->f24.u64 = LD(ctx->r29, 0X20);
    // 0x8004B654: ldc1        $f26, 0x28($sp)
    CHECK_FR(ctx, 26);
    ctx->f26.u64 = LD(ctx->r29, 0X28);
    // 0x8004B658: ldc1        $f28, 0x30($sp)
    CHECK_FR(ctx, 28);
    ctx->f28.u64 = LD(ctx->r29, 0X30);
    // 0x8004B65C: ldc1        $f30, 0x38($sp)
    CHECK_FR(ctx, 30);
    ctx->f30.u64 = LD(ctx->r29, 0X38);
    // 0x8004B660: lw          $s0, 0x44($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X44);
    // 0x8004B664: lw          $s1, 0x48($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X48);
    // 0x8004B668: lw          $s2, 0x4C($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X4C);
    // 0x8004B66C: lw          $s3, 0x50($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X50);
    // 0x8004B670: lw          $s4, 0x54($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X54);
    // 0x8004B674: lw          $s5, 0x58($sp)
    ctx->r21 = MEM_W(ctx->r29, 0X58);
    // 0x8004B678: jr          $ra
    // 0x8004B67C: addiu       $sp, $sp, 0xB8
    ctx->r29 = ADD32(ctx->r29, 0XB8);
    return;
    // 0x8004B67C: addiu       $sp, $sp, 0xB8
    ctx->r29 = ADD32(ctx->r29, 0XB8);
;}
