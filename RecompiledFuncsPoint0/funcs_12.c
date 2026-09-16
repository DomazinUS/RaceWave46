#include "recomp.h"
#include "funcs.h"

RECOMP_FUNC void Audio_FindNodeWithPrioLessThan(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800BB708: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x800BB70C: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800BB710: lw          $v0, 0x4($a0)
    ctx->r2 = MEM_W(ctx->r4, 0X4);
    // 0x800BB714: or          $a2, $a0, $zero
    ctx->r6 = ctx->r4 | 0;
    // 0x800BB718: bne         $v0, $a0, L_800BB728
    if (ctx->r2 != ctx->r4) {
        // 0x800BB71C: nop
    
            goto L_800BB728;
    }
    // 0x800BB71C: nop

    // 0x800BB720: b           L_800BB798
    // 0x800BB724: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
        goto L_800BB798;
    // 0x800BB724: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_800BB728:
    // 0x800BB728: beq         $v0, $a2, L_800BB75C
    if (ctx->r2 == ctx->r6) {
        // 0x800BB72C: or          $a0, $v0, $zero
        ctx->r4 = ctx->r2 | 0;
            goto L_800BB75C;
    }
    // 0x800BB72C: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x800BB730: lw          $t6, 0x8($a0)
    ctx->r14 = MEM_W(ctx->r4, 0X8);
L_800BB734:
    // 0x800BB734: lw          $t8, 0x8($v0)
    ctx->r24 = MEM_W(ctx->r2, 0X8);
    // 0x800BB738: lbu         $t7, 0x30($t6)
    ctx->r15 = MEM_BU(ctx->r14, 0X30);
    // 0x800BB73C: lbu         $t9, 0x30($t8)
    ctx->r25 = MEM_BU(ctx->r24, 0X30);
    // 0x800BB740: slt         $at, $t7, $t9
    ctx->r1 = SIGNED(ctx->r15) < SIGNED(ctx->r25) ? 1 : 0;
    // 0x800BB744: bnel        $at, $zero, L_800BB754
    if (ctx->r1 != 0) {
        // 0x800BB748: lw          $v0, 0x4($v0)
        ctx->r2 = MEM_W(ctx->r2, 0X4);
            goto L_800BB754;
    }
    goto skip_0;
    // 0x800BB748: lw          $v0, 0x4($v0)
    ctx->r2 = MEM_W(ctx->r2, 0X4);
    skip_0:
    // 0x800BB74C: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x800BB750: lw          $v0, 0x4($v0)
    ctx->r2 = MEM_W(ctx->r2, 0X4);
L_800BB754:
    // 0x800BB754: bnel        $v0, $a2, L_800BB734
    if (ctx->r2 != ctx->r6) {
        // 0x800BB758: lw          $t6, 0x8($a0)
        ctx->r14 = MEM_W(ctx->r4, 0X8);
            goto L_800BB734;
    }
    goto skip_1;
    // 0x800BB758: lw          $t6, 0x8($a0)
    ctx->r14 = MEM_W(ctx->r4, 0X8);
    skip_1:
L_800BB75C:
    // 0x800BB75C: bnel        $a0, $zero, L_800BB770
    if (ctx->r4 != 0) {
        // 0x800BB760: lw          $t0, 0x8($a0)
        ctx->r8 = MEM_W(ctx->r4, 0X8);
            goto L_800BB770;
    }
    goto skip_2;
    // 0x800BB760: lw          $t0, 0x8($a0)
    ctx->r8 = MEM_W(ctx->r4, 0X8);
    skip_2:
    // 0x800BB764: b           L_800BB798
    // 0x800BB768: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
        goto L_800BB798;
    // 0x800BB768: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    // 0x800BB76C: lw          $t0, 0x8($a0)
    ctx->r8 = MEM_W(ctx->r4, 0X8);
L_800BB770:
    // 0x800BB770: lbu         $t1, 0x30($t0)
    ctx->r9 = MEM_BU(ctx->r8, 0X30);
    // 0x800BB774: slt         $at, $t1, $a1
    ctx->r1 = SIGNED(ctx->r9) < SIGNED(ctx->r5) ? 1 : 0;
    // 0x800BB778: bne         $at, $zero, L_800BB788
    if (ctx->r1 != 0) {
        // 0x800BB77C: nop
    
            goto L_800BB788;
    }
    // 0x800BB77C: nop

    // 0x800BB780: b           L_800BB798
    // 0x800BB784: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
        goto L_800BB798;
    // 0x800BB784: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_800BB788:
    // 0x800BB788: jal         0x800BB6DC
    // 0x800BB78C: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    Audio_AudioListRemove(rdram, ctx);
        goto after_0;
    // 0x800BB78C: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    after_0:
    // 0x800BB790: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
    // 0x800BB794: lw          $v0, 0x8($a0)
    ctx->r2 = MEM_W(ctx->r4, 0X8);
L_800BB798:
    // 0x800BB798: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800BB79C: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x800BB7A0: jr          $ra
    // 0x800BB7A4: nop

    return;
    // 0x800BB7A4: nop

;}
RECOMP_FUNC void Audio_NoteInitForLayer(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800BB7A8: addiu       $sp, $sp, -0x38
    ctx->r29 = ADD32(ctx->r29, -0X38);
    // 0x800BB7AC: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800BB7B0: addiu       $t6, $zero, -0x1
    ctx->r14 = ADD32(0, -0X1);
    // 0x800BB7B4: sw          $t6, 0x40($a0)
    MEM_W(0X40, ctx->r4) = ctx->r14;
    // 0x800BB7B8: sw          $a1, 0x44($a0)
    MEM_W(0X44, ctx->r4) = ctx->r5;
    // 0x800BB7BC: lw          $t7, 0x4C($a1)
    ctx->r15 = MEM_W(ctx->r5, 0X4C);
    // 0x800BB7C0: addiu       $t2, $zero, 0x3
    ctx->r10 = ADD32(0, 0X3);
    // 0x800BB7C4: mtc1        $zero, $f4
    ctx->f4.u32l = 0;
    // 0x800BB7C8: lbu         $t8, 0x5($t7)
    ctx->r24 = MEM_BU(ctx->r15, 0X5);
    // 0x800BB7CC: sb          $t8, 0x30($a0)
    MEM_B(0X30, ctx->r4) = ctx->r24;
    // 0x800BB7D0: lbu         $t0, 0x0($a1)
    ctx->r8 = MEM_BU(ctx->r5, 0X0);
    // 0x800BB7D4: lw          $t3, 0x4C($a1)
    ctx->r11 = MEM_W(ctx->r5, 0X4C);
    // 0x800BB7D8: sb          $t2, 0x2($a1)
    MEM_B(0X2, ctx->r5) = ctx->r10;
    // 0x800BB7DC: ori         $t1, $t0, 0x4
    ctx->r9 = ctx->r8 | 0X4;
    // 0x800BB7E0: sb          $t1, 0x0($a1)
    MEM_B(0X0, ctx->r5) = ctx->r9;
    // 0x800BB7E4: sw          $a0, 0x40($a1)
    MEM_W(0X40, ctx->r5) = ctx->r4;
    // 0x800BB7E8: sw          $a0, 0x38($t3)
    MEM_W(0X38, ctx->r11) = ctx->r4;
    // 0x800BB7EC: lw          $t4, 0x4C($a1)
    ctx->r12 = MEM_W(ctx->r5, 0X4C);
    // 0x800BB7F0: sw          $a1, 0x3C($t4)
    MEM_W(0X3C, ctx->r12) = ctx->r5;
    // 0x800BB7F4: swc1        $f4, 0x2C($a1)
    MEM_W(0X2C, ctx->r5) = ctx->f4.u32l;
    // 0x800BB7F8: sw          $a1, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r5;
    // 0x800BB7FC: jal         0x800BAA84
    // 0x800BB800: sw          $a0, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r4;
    Audio_NoteInit(rdram, ctx);
        goto after_0;
    // 0x800BB800: sw          $a0, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r4;
    after_0:
    // 0x800BB804: lw          $a1, 0x3C($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X3C);
    // 0x800BB808: lw          $a0, 0x38($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X38);
    // 0x800BB80C: addiu       $at, $zero, 0xFF
    ctx->r1 = ADD32(0, 0XFF);
    // 0x800BB810: lbu         $a2, 0x1($a1)
    ctx->r6 = MEM_BU(ctx->r5, 0X1);
    // 0x800BB814: addiu       $v0, $a0, 0xB0
    ctx->r2 = ADD32(ctx->r4, 0XB0);
    // 0x800BB818: bnel        $a2, $at, L_800BB82C
    if (ctx->r6 != ctx->r1) {
        // 0x800BB81C: lw          $t6, 0x48($a1)
        ctx->r14 = MEM_W(ctx->r5, 0X48);
            goto L_800BB82C;
    }
    goto skip_0;
    // 0x800BB81C: lw          $t6, 0x48($a1)
    ctx->r14 = MEM_W(ctx->r5, 0X48);
    skip_0:
    // 0x800BB820: lw          $t5, 0x4C($a1)
    ctx->r13 = MEM_W(ctx->r5, 0X4C);
    // 0x800BB824: lh          $a2, 0x1C($t5)
    ctx->r6 = MEM_H(ctx->r13, 0X1C);
    // 0x800BB828: lw          $t6, 0x48($a1)
    ctx->r14 = MEM_W(ctx->r5, 0X48);
L_800BB82C:
    // 0x800BB82C: slti        $at, $a2, 0x80
    ctx->r1 = SIGNED(ctx->r6) < 0X80 ? 1 : 0;
    // 0x800BB830: bne         $at, $zero, L_800BB848
    if (ctx->r1 != 0) {
        // 0x800BB834: sw          $t6, 0xC($v0)
        MEM_W(0XC, ctx->r2) = ctx->r14;
            goto L_800BB848;
    }
    // 0x800BB834: sw          $t6, 0xC($v0)
    MEM_W(0XC, ctx->r2) = ctx->r14;
    // 0x800BB838: lbu         $t8, 0x1($v0)
    ctx->r24 = MEM_BU(ctx->r2, 0X1);
    // 0x800BB83C: ori         $t9, $t8, 0x2
    ctx->r25 = ctx->r24 | 0X2;
    // 0x800BB840: b           L_800BB854
    // 0x800BB844: sb          $t9, 0x1($v0)
    MEM_B(0X1, ctx->r2) = ctx->r25;
        goto L_800BB854;
    // 0x800BB844: sb          $t9, 0x1($v0)
    MEM_B(0X1, ctx->r2) = ctx->r25;
L_800BB848:
    // 0x800BB848: lbu         $t0, 0x1($v0)
    ctx->r8 = MEM_BU(ctx->r2, 0X1);
    // 0x800BB84C: andi        $t1, $t0, 0xFFFD
    ctx->r9 = ctx->r8 & 0XFFFD;
    // 0x800BB850: sb          $t1, 0x1($v0)
    MEM_B(0X1, ctx->r2) = ctx->r9;
L_800BB854:
    // 0x800BB854: lw          $t2, 0x0($v0)
    ctx->r10 = MEM_W(ctx->r2, 0X0);
    // 0x800BB858: sll         $t4, $t2, 14
    ctx->r12 = S32(ctx->r10 << 14);
    // 0x800BB85C: bgezl       $t4, L_800BB87C
    if (SIGNED(ctx->r12) >= 0) {
        // 0x800BB860: lw          $t5, 0x4C($a1)
        ctx->r13 = MEM_W(ctx->r5, 0X4C);
            goto L_800BB87C;
    }
    goto skip_1;
    // 0x800BB860: lw          $t5, 0x4C($a1)
    ctx->r13 = MEM_W(ctx->r5, 0X4C);
    skip_1:
    // 0x800BB864: sw          $v0, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r2;
    // 0x800BB868: jal         0x800BB148
    // 0x800BB86C: sw          $a1, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r5;
    Audio_BuildSyntheticWave(rdram, ctx);
        goto after_1;
    // 0x800BB86C: sw          $a1, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r5;
    after_1:
    // 0x800BB870: lw          $v0, 0x1C($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X1C);
    // 0x800BB874: lw          $a1, 0x3C($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X3C);
    // 0x800BB878: lw          $t5, 0x4C($a1)
    ctx->r13 = MEM_W(ctx->r5, 0X4C);
L_800BB87C:
    // 0x800BB87C: lbu         $t3, 0x0($v0)
    ctx->r11 = MEM_BU(ctx->r2, 0X0);
    // 0x800BB880: lbu         $t6, 0x6($t5)
    ctx->r14 = MEM_BU(ctx->r13, 0X6);
    // 0x800BB884: andi        $t4, $t3, 0xFFFD
    ctx->r12 = ctx->r11 & 0XFFFD;
    // 0x800BB888: lbu         $t3, 0x1($v0)
    ctx->r11 = MEM_BU(ctx->r2, 0X1);
    // 0x800BB88C: sb          $t6, 0x2($v0)
    MEM_B(0X2, ctx->r2) = ctx->r14;
    // 0x800BB890: lw          $t7, 0x4C($a1)
    ctx->r15 = MEM_W(ctx->r5, 0X4C);
    // 0x800BB894: lw          $t8, 0x0($t7)
    ctx->r24 = MEM_W(ctx->r15, 0X0);
    // 0x800BB898: sll         $t9, $t8, 5
    ctx->r25 = S32(ctx->r24 << 5);
    // 0x800BB89C: srl         $t0, $t9, 31
    ctx->r8 = S32(U32(ctx->r25) >> 31);
    // 0x800BB8A0: sll         $t1, $t0, 1
    ctx->r9 = S32(ctx->r8 << 1);
    // 0x800BB8A4: andi        $t2, $t1, 0x2
    ctx->r10 = ctx->r9 & 0X2;
    // 0x800BB8A8: or          $t5, $t2, $t4
    ctx->r13 = ctx->r10 | ctx->r12;
    // 0x800BB8AC: sb          $t5, 0x0($v0)
    MEM_B(0X0, ctx->r2) = ctx->r13;
    // 0x800BB8B0: lw          $t6, 0x4C($a1)
    ctx->r14 = MEM_W(ctx->r5, 0X4C);
    // 0x800BB8B4: andi        $t2, $t3, 0xFF1F
    ctx->r10 = ctx->r11 & 0XFF1F;
    // 0x800BB8B8: lbu         $t7, 0x7($t6)
    ctx->r15 = MEM_BU(ctx->r14, 0X7);
    // 0x800BB8BC: andi        $t9, $t7, 0x3
    ctx->r25 = ctx->r15 & 0X3;
    // 0x800BB8C0: sll         $t1, $t9, 5
    ctx->r9 = S32(ctx->r25 << 5);
    // 0x800BB8C4: or          $t4, $t1, $t2
    ctx->r12 = ctx->r9 | ctx->r10;
    // 0x800BB8C8: sb          $t4, 0x1($v0)
    MEM_B(0X1, ctx->r2) = ctx->r12;
    // 0x800BB8CC: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800BB8D0: addiu       $sp, $sp, 0x38
    ctx->r29 = ADD32(ctx->r29, 0X38);
    // 0x800BB8D4: jr          $ra
    // 0x800BB8D8: nop

    return;
    // 0x800BB8D8: nop

;}
RECOMP_FUNC void func_800BB8DC(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800BB8DC: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800BB8E0: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800BB8E4: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    // 0x800BB8E8: sw          $a1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r5;
    // 0x800BB8EC: jal         0x800BB128
    // 0x800BB8F0: lw          $a0, 0x44($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X44);
    Audio_SeqLayerNoteRelease(rdram, ctx);
        goto after_0;
    // 0x800BB8F0: lw          $a0, 0x44($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X44);
    after_0:
    // 0x800BB8F4: lw          $t7, 0x1C($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X1C);
    // 0x800BB8F8: lw          $t8, 0x18($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X18);
    // 0x800BB8FC: sw          $t7, 0x48($t8)
    MEM_W(0X48, ctx->r24) = ctx->r15;
    // 0x800BB900: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800BB904: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800BB908: jr          $ra
    // 0x800BB90C: nop

    return;
    // 0x800BB90C: nop

;}
RECOMP_FUNC void Audio_NoteReleaseAndTakeOwnership(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800BB910: lbu         $t7, 0x58($a0)
    ctx->r15 = MEM_BU(ctx->r4, 0X58);
    // 0x800BB914: addiu       $t6, $zero, 0x1
    ctx->r14 = ADD32(0, 0X1);
    // 0x800BB918: sw          $a1, 0x48($a0)
    MEM_W(0X48, ctx->r4) = ctx->r5;
    // 0x800BB91C: sb          $t6, 0x30($a0)
    MEM_B(0X30, ctx->r4) = ctx->r14;
    // 0x800BB920: lui         $at, 0x8004
    ctx->r1 = S32(0X8004 << 16);
    // 0x800BB924: lwc1        $f4, 0x5538($at)
    ctx->f4.u32l = MEM_W(ctx->r1, 0X5538);
    // 0x800BB928: ori         $t8, $t7, 0x10
    ctx->r24 = ctx->r15 | 0X10;
    // 0x800BB92C: sb          $t8, 0x58($a0)
    MEM_B(0X58, ctx->r4) = ctx->r24;
    // 0x800BB930: jr          $ra
    // 0x800BB934: swc1        $f4, 0x68($a0)
    MEM_W(0X68, ctx->r4) = ctx->f4.u32l;
    return;
    // 0x800BB934: swc1        $f4, 0x68($a0)
    MEM_W(0X68, ctx->r4) = ctx->f4.u32l;
;}
RECOMP_FUNC void Audio_AllocNoteFromDisabled(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800BB938: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x800BB93C: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800BB940: sw          $a0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r4;
    // 0x800BB944: jal         0x800BCFEC
    // 0x800BB948: sw          $a1, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r5;
    AudioSeq_AudioListPopBack(rdram, ctx);
        goto after_0;
    // 0x800BB948: sw          $a1, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r5;
    after_0:
    // 0x800BB94C: beq         $v0, $zero, L_800BB970
    if (ctx->r2 == 0) {
        // 0x800BB950: sw          $v0, 0x1C($sp)
        MEM_W(0X1C, ctx->r29) = ctx->r2;
            goto L_800BB970;
    }
    // 0x800BB950: sw          $v0, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r2;
    // 0x800BB954: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x800BB958: jal         0x800BB7A8
    // 0x800BB95C: lw          $a1, 0x24($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X24);
    Audio_NoteInitForLayer(rdram, ctx);
        goto after_1;
    // 0x800BB95C: lw          $a1, 0x24($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X24);
    after_1:
    // 0x800BB960: lw          $a0, 0x20($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X20);
    // 0x800BB964: lw          $a1, 0x1C($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X1C);
    // 0x800BB968: jal         0x800BB69C
    // 0x800BB96C: addiu       $a0, $a0, 0x30
    ctx->r4 = ADD32(ctx->r4, 0X30);
    Audio_AudioListPushFront(rdram, ctx);
        goto after_2;
    // 0x800BB96C: addiu       $a0, $a0, 0x30
    ctx->r4 = ADD32(ctx->r4, 0X30);
    after_2:
L_800BB970:
    // 0x800BB970: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800BB974: lw          $v0, 0x1C($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X1C);
    // 0x800BB978: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x800BB97C: jr          $ra
    // 0x800BB980: nop

    return;
    // 0x800BB980: nop

;}
RECOMP_FUNC void Audio_AllocNoteFromDecaying(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800BB984: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x800BB988: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800BB98C: sw          $a0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r4;
    // 0x800BB990: sw          $a1, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r5;
    // 0x800BB994: jal         0x800BCFEC
    // 0x800BB998: addiu       $a0, $a0, 0x10
    ctx->r4 = ADD32(ctx->r4, 0X10);
    AudioSeq_AudioListPopBack(rdram, ctx);
        goto after_0;
    // 0x800BB998: addiu       $a0, $a0, 0x10
    ctx->r4 = ADD32(ctx->r4, 0X10);
    after_0:
    // 0x800BB99C: beq         $v0, $zero, L_800BB9C0
    if (ctx->r2 == 0) {
        // 0x800BB9A0: sw          $v0, 0x1C($sp)
        MEM_W(0X1C, ctx->r29) = ctx->r2;
            goto L_800BB9C0;
    }
    // 0x800BB9A0: sw          $v0, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r2;
    // 0x800BB9A4: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x800BB9A8: jal         0x800BB910
    // 0x800BB9AC: lw          $a1, 0x24($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X24);
    Audio_NoteReleaseAndTakeOwnership(rdram, ctx);
        goto after_1;
    // 0x800BB9AC: lw          $a1, 0x24($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X24);
    after_1:
    // 0x800BB9B0: lw          $a0, 0x20($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X20);
    // 0x800BB9B4: lw          $a1, 0x1C($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X1C);
    // 0x800BB9B8: jal         0x800BCFAC
    // 0x800BB9BC: addiu       $a0, $a0, 0x20
    ctx->r4 = ADD32(ctx->r4, 0X20);
    AudioSeq_AudioListPushBack(rdram, ctx);
        goto after_2;
    // 0x800BB9BC: addiu       $a0, $a0, 0x20
    ctx->r4 = ADD32(ctx->r4, 0X20);
    after_2:
L_800BB9C0:
    // 0x800BB9C0: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800BB9C4: lw          $v0, 0x1C($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X1C);
    // 0x800BB9C8: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x800BB9CC: jr          $ra
    // 0x800BB9D0: nop

    return;
    // 0x800BB9D0: nop

;}
RECOMP_FUNC void Audio_AllocNoteFromActive(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800BB9D4: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x800BB9D8: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800BB9DC: sw          $a0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r4;
    // 0x800BB9E0: sw          $a1, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r5;
    // 0x800BB9E4: lw          $t7, 0x4C($a1)
    ctx->r15 = MEM_W(ctx->r5, 0X4C);
    // 0x800BB9E8: addiu       $a0, $a0, 0x30
    ctx->r4 = ADD32(ctx->r4, 0X30);
    // 0x800BB9EC: jal         0x800BB708
    // 0x800BB9F0: lbu         $a1, 0x5($t7)
    ctx->r5 = MEM_BU(ctx->r15, 0X5);
    Audio_FindNodeWithPrioLessThan(rdram, ctx);
        goto after_0;
    // 0x800BB9F0: lbu         $a1, 0x5($t7)
    ctx->r5 = MEM_BU(ctx->r15, 0X5);
    after_0:
    // 0x800BB9F4: beq         $v0, $zero, L_800BBA18
    if (ctx->r2 == 0) {
        // 0x800BB9F8: sw          $v0, 0x1C($sp)
        MEM_W(0X1C, ctx->r29) = ctx->r2;
            goto L_800BBA18;
    }
    // 0x800BB9F8: sw          $v0, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r2;
    // 0x800BB9FC: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x800BBA00: jal         0x800BB8DC
    // 0x800BBA04: lw          $a1, 0x24($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X24);
    func_800BB8DC(rdram, ctx);
        goto after_1;
    // 0x800BBA04: lw          $a1, 0x24($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X24);
    after_1:
    // 0x800BBA08: lw          $a0, 0x20($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X20);
    // 0x800BBA0C: lw          $a1, 0x1C($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X1C);
    // 0x800BBA10: jal         0x800BCFAC
    // 0x800BBA14: addiu       $a0, $a0, 0x20
    ctx->r4 = ADD32(ctx->r4, 0X20);
    AudioSeq_AudioListPushBack(rdram, ctx);
        goto after_2;
    // 0x800BBA14: addiu       $a0, $a0, 0x20
    ctx->r4 = ADD32(ctx->r4, 0X20);
    after_2:
L_800BBA18:
    // 0x800BBA18: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800BBA1C: lw          $v0, 0x1C($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X1C);
    // 0x800BBA20: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x800BBA24: jr          $ra
    // 0x800BBA28: nop

    return;
    // 0x800BBA28: nop

;}
RECOMP_FUNC void Audio_AllocNote(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800BBA2C: addiu       $sp, $sp, -0x28
    ctx->r29 = ADD32(ctx->r29, -0X28);
    // 0x800BBA30: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x800BBA34: sw          $s0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r16;
    // 0x800BBA38: lw          $v1, 0x4C($a0)
    ctx->r3 = MEM_W(ctx->r4, 0X4C);
    // 0x800BBA3C: or          $s0, $a0, $zero
    ctx->r16 = ctx->r4 | 0;
    // 0x800BBA40: lbu         $v0, 0x2($v1)
    ctx->r2 = MEM_BU(ctx->r3, 0X2);
    // 0x800BBA44: andi        $t6, $v0, 0x1
    ctx->r14 = ctx->r2 & 0X1;
    // 0x800BBA48: beq         $t6, $zero, L_800BBAA4
    if (ctx->r14 == 0) {
        // 0x800BBA4C: andi        $t9, $v0, 0x2
        ctx->r25 = ctx->r2 & 0X2;
            goto L_800BBAA4;
    }
    // 0x800BBA4C: andi        $t9, $v0, 0x2
    ctx->r25 = ctx->r2 & 0X2;
    // 0x800BBA50: lw          $a2, 0x40($a0)
    ctx->r6 = MEM_W(ctx->r4, 0X40);
    // 0x800BBA54: beq         $a2, $zero, L_800BBAA4
    if (ctx->r6 == 0) {
        // 0x800BBA58: nop
    
            goto L_800BBAA4;
    }
    // 0x800BBA58: nop

    // 0x800BBA5C: lw          $t7, 0x40($a2)
    ctx->r15 = MEM_W(ctx->r6, 0X40);
    // 0x800BBA60: bne         $a0, $t7, L_800BBAA4
    if (ctx->r4 != ctx->r15) {
        // 0x800BBA64: nop
    
            goto L_800BBAA4;
    }
    // 0x800BBA64: nop

    // 0x800BBA68: lw          $t8, 0x48($a2)
    ctx->r24 = MEM_W(ctx->r6, 0X48);
    // 0x800BBA6C: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x800BBA70: or          $a0, $a2, $zero
    ctx->r4 = ctx->r6 | 0;
    // 0x800BBA74: bne         $t8, $at, L_800BBAA4
    if (ctx->r24 != ctx->r1) {
        // 0x800BBA78: or          $a1, $s0, $zero
        ctx->r5 = ctx->r16 | 0;
            goto L_800BBAA4;
    }
    // 0x800BBA78: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    // 0x800BBA7C: jal         0x800BB910
    // 0x800BBA80: sw          $a2, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r6;
    Audio_NoteReleaseAndTakeOwnership(rdram, ctx);
        goto after_0;
    // 0x800BBA80: sw          $a2, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r6;
    after_0:
    // 0x800BBA84: jal         0x800BB6DC
    // 0x800BBA88: lw          $a0, 0x24($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X24);
    Audio_AudioListRemove(rdram, ctx);
        goto after_1;
    // 0x800BBA88: lw          $a0, 0x24($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X24);
    after_1:
    // 0x800BBA8C: lw          $a1, 0x24($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X24);
    // 0x800BBA90: lw          $a0, 0xC($a1)
    ctx->r4 = MEM_W(ctx->r5, 0XC);
    // 0x800BBA94: jal         0x800BCFAC
    // 0x800BBA98: addiu       $a0, $a0, 0x20
    ctx->r4 = ADD32(ctx->r4, 0X20);
    AudioSeq_AudioListPushBack(rdram, ctx);
        goto after_2;
    // 0x800BBA98: addiu       $a0, $a0, 0x20
    ctx->r4 = ADD32(ctx->r4, 0X20);
    after_2:
    // 0x800BBA9C: b           L_800BBD08
    // 0x800BBAA0: lw          $v0, 0x24($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X24);
        goto L_800BBD08;
    // 0x800BBAA0: lw          $v0, 0x24($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X24);
L_800BBAA4:
    // 0x800BBAA4: beq         $t9, $zero, L_800BBB04
    if (ctx->r25 == 0) {
        // 0x800BBAA8: andi        $t0, $v0, 0x4
        ctx->r8 = ctx->r2 & 0X4;
            goto L_800BBB04;
    }
    // 0x800BBAA8: andi        $t0, $v0, 0x4
    ctx->r8 = ctx->r2 & 0X4;
    // 0x800BBAAC: addiu       $a0, $v1, 0x84
    ctx->r4 = ADD32(ctx->r3, 0X84);
    // 0x800BBAB0: jal         0x800BB938
    // 0x800BBAB4: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    Audio_AllocNoteFromDisabled(rdram, ctx);
        goto after_3;
    // 0x800BBAB4: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    after_3:
    // 0x800BBAB8: bne         $v0, $zero, L_800BBAFC
    if (ctx->r2 != 0) {
        // 0x800BBABC: or          $a2, $v0, $zero
        ctx->r6 = ctx->r2 | 0;
            goto L_800BBAFC;
    }
    // 0x800BBABC: or          $a2, $v0, $zero
    ctx->r6 = ctx->r2 | 0;
    // 0x800BBAC0: lw          $a0, 0x4C($s0)
    ctx->r4 = MEM_W(ctx->r16, 0X4C);
    // 0x800BBAC4: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    // 0x800BBAC8: jal         0x800BB984
    // 0x800BBACC: addiu       $a0, $a0, 0x84
    ctx->r4 = ADD32(ctx->r4, 0X84);
    Audio_AllocNoteFromDecaying(rdram, ctx);
        goto after_4;
    // 0x800BBACC: addiu       $a0, $a0, 0x84
    ctx->r4 = ADD32(ctx->r4, 0X84);
    after_4:
    // 0x800BBAD0: bne         $v0, $zero, L_800BBAFC
    if (ctx->r2 != 0) {
        // 0x800BBAD4: or          $a2, $v0, $zero
        ctx->r6 = ctx->r2 | 0;
            goto L_800BBAFC;
    }
    // 0x800BBAD4: or          $a2, $v0, $zero
    ctx->r6 = ctx->r2 | 0;
    // 0x800BBAD8: lw          $a0, 0x4C($s0)
    ctx->r4 = MEM_W(ctx->r16, 0X4C);
    // 0x800BBADC: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    // 0x800BBAE0: jal         0x800BB9D4
    // 0x800BBAE4: addiu       $a0, $a0, 0x84
    ctx->r4 = ADD32(ctx->r4, 0X84);
    Audio_AllocNoteFromActive(rdram, ctx);
        goto after_5;
    // 0x800BBAE4: addiu       $a0, $a0, 0x84
    ctx->r4 = ADD32(ctx->r4, 0X84);
    after_5:
    // 0x800BBAE8: bne         $v0, $zero, L_800BBAFC
    if (ctx->r2 != 0) {
        // 0x800BBAEC: or          $a2, $v0, $zero
        ctx->r6 = ctx->r2 | 0;
            goto L_800BBAFC;
    }
    // 0x800BBAEC: or          $a2, $v0, $zero
    ctx->r6 = ctx->r2 | 0;
    // 0x800BBAF0: sb          $zero, 0x2($s0)
    MEM_B(0X2, ctx->r16) = 0;
    // 0x800BBAF4: b           L_800BBD08
    // 0x800BBAF8: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
        goto L_800BBD08;
    // 0x800BBAF8: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_800BBAFC:
    // 0x800BBAFC: b           L_800BBD08
    // 0x800BBB00: or          $v0, $a2, $zero
    ctx->r2 = ctx->r6 | 0;
        goto L_800BBD08;
    // 0x800BBB00: or          $v0, $a2, $zero
    ctx->r2 = ctx->r6 | 0;
L_800BBB04:
    // 0x800BBB04: beq         $t0, $zero, L_800BBBB8
    if (ctx->r8 == 0) {
        // 0x800BBB08: andi        $t4, $v0, 0x8
        ctx->r12 = ctx->r2 & 0X8;
            goto L_800BBBB8;
    }
    // 0x800BBB08: andi        $t4, $v0, 0x8
    ctx->r12 = ctx->r2 & 0X8;
    // 0x800BBB0C: addiu       $a0, $v1, 0x84
    ctx->r4 = ADD32(ctx->r3, 0X84);
    // 0x800BBB10: jal         0x800BB938
    // 0x800BBB14: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    Audio_AllocNoteFromDisabled(rdram, ctx);
        goto after_6;
    // 0x800BBB14: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    after_6:
    // 0x800BBB18: bne         $v0, $zero, L_800BBBB0
    if (ctx->r2 != 0) {
        // 0x800BBB1C: or          $a2, $v0, $zero
        ctx->r6 = ctx->r2 | 0;
            goto L_800BBBB0;
    }
    // 0x800BBB1C: or          $a2, $v0, $zero
    ctx->r6 = ctx->r2 | 0;
    // 0x800BBB20: lw          $t1, 0x4C($s0)
    ctx->r9 = MEM_W(ctx->r16, 0X4C);
    // 0x800BBB24: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    // 0x800BBB28: lw          $a0, 0x44($t1)
    ctx->r4 = MEM_W(ctx->r9, 0X44);
    // 0x800BBB2C: jal         0x800BB938
    // 0x800BBB30: addiu       $a0, $a0, 0x94
    ctx->r4 = ADD32(ctx->r4, 0X94);
    Audio_AllocNoteFromDisabled(rdram, ctx);
        goto after_7;
    // 0x800BBB30: addiu       $a0, $a0, 0x94
    ctx->r4 = ADD32(ctx->r4, 0X94);
    after_7:
    // 0x800BBB34: bne         $v0, $zero, L_800BBBB0
    if (ctx->r2 != 0) {
        // 0x800BBB38: or          $a2, $v0, $zero
        ctx->r6 = ctx->r2 | 0;
            goto L_800BBBB0;
    }
    // 0x800BBB38: or          $a2, $v0, $zero
    ctx->r6 = ctx->r2 | 0;
    // 0x800BBB3C: lw          $a0, 0x4C($s0)
    ctx->r4 = MEM_W(ctx->r16, 0X4C);
    // 0x800BBB40: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    // 0x800BBB44: jal         0x800BB984
    // 0x800BBB48: addiu       $a0, $a0, 0x84
    ctx->r4 = ADD32(ctx->r4, 0X84);
    Audio_AllocNoteFromDecaying(rdram, ctx);
        goto after_8;
    // 0x800BBB48: addiu       $a0, $a0, 0x84
    ctx->r4 = ADD32(ctx->r4, 0X84);
    after_8:
    // 0x800BBB4C: bne         $v0, $zero, L_800BBBB0
    if (ctx->r2 != 0) {
        // 0x800BBB50: or          $a2, $v0, $zero
        ctx->r6 = ctx->r2 | 0;
            goto L_800BBBB0;
    }
    // 0x800BBB50: or          $a2, $v0, $zero
    ctx->r6 = ctx->r2 | 0;
    // 0x800BBB54: lw          $t2, 0x4C($s0)
    ctx->r10 = MEM_W(ctx->r16, 0X4C);
    // 0x800BBB58: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    // 0x800BBB5C: lw          $a0, 0x44($t2)
    ctx->r4 = MEM_W(ctx->r10, 0X44);
    // 0x800BBB60: jal         0x800BB984
    // 0x800BBB64: addiu       $a0, $a0, 0x94
    ctx->r4 = ADD32(ctx->r4, 0X94);
    Audio_AllocNoteFromDecaying(rdram, ctx);
        goto after_9;
    // 0x800BBB64: addiu       $a0, $a0, 0x94
    ctx->r4 = ADD32(ctx->r4, 0X94);
    after_9:
    // 0x800BBB68: bne         $v0, $zero, L_800BBBB0
    if (ctx->r2 != 0) {
        // 0x800BBB6C: or          $a2, $v0, $zero
        ctx->r6 = ctx->r2 | 0;
            goto L_800BBBB0;
    }
    // 0x800BBB6C: or          $a2, $v0, $zero
    ctx->r6 = ctx->r2 | 0;
    // 0x800BBB70: lw          $a0, 0x4C($s0)
    ctx->r4 = MEM_W(ctx->r16, 0X4C);
    // 0x800BBB74: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    // 0x800BBB78: jal         0x800BB9D4
    // 0x800BBB7C: addiu       $a0, $a0, 0x84
    ctx->r4 = ADD32(ctx->r4, 0X84);
    Audio_AllocNoteFromActive(rdram, ctx);
        goto after_10;
    // 0x800BBB7C: addiu       $a0, $a0, 0x84
    ctx->r4 = ADD32(ctx->r4, 0X84);
    after_10:
    // 0x800BBB80: bne         $v0, $zero, L_800BBBB0
    if (ctx->r2 != 0) {
        // 0x800BBB84: or          $a2, $v0, $zero
        ctx->r6 = ctx->r2 | 0;
            goto L_800BBBB0;
    }
    // 0x800BBB84: or          $a2, $v0, $zero
    ctx->r6 = ctx->r2 | 0;
    // 0x800BBB88: lw          $t3, 0x4C($s0)
    ctx->r11 = MEM_W(ctx->r16, 0X4C);
    // 0x800BBB8C: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    // 0x800BBB90: lw          $a0, 0x44($t3)
    ctx->r4 = MEM_W(ctx->r11, 0X44);
    // 0x800BBB94: jal         0x800BB9D4
    // 0x800BBB98: addiu       $a0, $a0, 0x94
    ctx->r4 = ADD32(ctx->r4, 0X94);
    Audio_AllocNoteFromActive(rdram, ctx);
        goto after_11;
    // 0x800BBB98: addiu       $a0, $a0, 0x94
    ctx->r4 = ADD32(ctx->r4, 0X94);
    after_11:
    // 0x800BBB9C: bne         $v0, $zero, L_800BBBB0
    if (ctx->r2 != 0) {
        // 0x800BBBA0: or          $a2, $v0, $zero
        ctx->r6 = ctx->r2 | 0;
            goto L_800BBBB0;
    }
    // 0x800BBBA0: or          $a2, $v0, $zero
    ctx->r6 = ctx->r2 | 0;
    // 0x800BBBA4: sb          $zero, 0x2($s0)
    MEM_B(0X2, ctx->r16) = 0;
    // 0x800BBBA8: b           L_800BBD08
    // 0x800BBBAC: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
        goto L_800BBD08;
    // 0x800BBBAC: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_800BBBB0:
    // 0x800BBBB0: b           L_800BBD08
    // 0x800BBBB4: or          $v0, $a2, $zero
    ctx->r2 = ctx->r6 | 0;
        goto L_800BBD08;
    // 0x800BBBB4: or          $v0, $a2, $zero
    ctx->r2 = ctx->r6 | 0;
L_800BBBB8:
    // 0x800BBBB8: beq         $t4, $zero, L_800BBC1C
    if (ctx->r12 == 0) {
        // 0x800BBBBC: addiu       $a0, $v1, 0x84
        ctx->r4 = ADD32(ctx->r3, 0X84);
            goto L_800BBC1C;
    }
    // 0x800BBBBC: addiu       $a0, $v1, 0x84
    ctx->r4 = ADD32(ctx->r3, 0X84);
    // 0x800BBBC0: lui         $a0, 0x8004
    ctx->r4 = S32(0X8004 << 16);
    // 0x800BBBC4: addiu       $a0, $a0, 0x4760
    ctx->r4 = ADD32(ctx->r4, 0X4760);
    // 0x800BBBC8: jal         0x800BB938
    // 0x800BBBCC: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    Audio_AllocNoteFromDisabled(rdram, ctx);
        goto after_12;
    // 0x800BBBCC: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    after_12:
    // 0x800BBBD0: bne         $v0, $zero, L_800BBC14
    if (ctx->r2 != 0) {
        // 0x800BBBD4: or          $a2, $v0, $zero
        ctx->r6 = ctx->r2 | 0;
            goto L_800BBC14;
    }
    // 0x800BBBD4: or          $a2, $v0, $zero
    ctx->r6 = ctx->r2 | 0;
    // 0x800BBBD8: lui         $a0, 0x8004
    ctx->r4 = S32(0X8004 << 16);
    // 0x800BBBDC: addiu       $a0, $a0, 0x4760
    ctx->r4 = ADD32(ctx->r4, 0X4760);
    // 0x800BBBE0: jal         0x800BB984
    // 0x800BBBE4: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    Audio_AllocNoteFromDecaying(rdram, ctx);
        goto after_13;
    // 0x800BBBE4: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    after_13:
    // 0x800BBBE8: bne         $v0, $zero, L_800BBC14
    if (ctx->r2 != 0) {
        // 0x800BBBEC: or          $a2, $v0, $zero
        ctx->r6 = ctx->r2 | 0;
            goto L_800BBC14;
    }
    // 0x800BBBEC: or          $a2, $v0, $zero
    ctx->r6 = ctx->r2 | 0;
    // 0x800BBBF0: lui         $a0, 0x8004
    ctx->r4 = S32(0X8004 << 16);
    // 0x800BBBF4: addiu       $a0, $a0, 0x4760
    ctx->r4 = ADD32(ctx->r4, 0X4760);
    // 0x800BBBF8: jal         0x800BB9D4
    // 0x800BBBFC: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    Audio_AllocNoteFromActive(rdram, ctx);
        goto after_14;
    // 0x800BBBFC: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    after_14:
    // 0x800BBC00: bne         $v0, $zero, L_800BBC14
    if (ctx->r2 != 0) {
        // 0x800BBC04: or          $a2, $v0, $zero
        ctx->r6 = ctx->r2 | 0;
            goto L_800BBC14;
    }
    // 0x800BBC04: or          $a2, $v0, $zero
    ctx->r6 = ctx->r2 | 0;
    // 0x800BBC08: sb          $zero, 0x2($s0)
    MEM_B(0X2, ctx->r16) = 0;
    // 0x800BBC0C: b           L_800BBD08
    // 0x800BBC10: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
        goto L_800BBD08;
    // 0x800BBC10: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_800BBC14:
    // 0x800BBC14: b           L_800BBD08
    // 0x800BBC18: or          $v0, $a2, $zero
    ctx->r2 = ctx->r6 | 0;
        goto L_800BBD08;
    // 0x800BBC18: or          $v0, $a2, $zero
    ctx->r2 = ctx->r6 | 0;
L_800BBC1C:
    // 0x800BBC1C: jal         0x800BB938
    // 0x800BBC20: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    Audio_AllocNoteFromDisabled(rdram, ctx);
        goto after_15;
    // 0x800BBC20: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    after_15:
    // 0x800BBC24: bne         $v0, $zero, L_800BBD04
    if (ctx->r2 != 0) {
        // 0x800BBC28: or          $a2, $v0, $zero
        ctx->r6 = ctx->r2 | 0;
            goto L_800BBD04;
    }
    // 0x800BBC28: or          $a2, $v0, $zero
    ctx->r6 = ctx->r2 | 0;
    // 0x800BBC2C: lw          $t5, 0x4C($s0)
    ctx->r13 = MEM_W(ctx->r16, 0X4C);
    // 0x800BBC30: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    // 0x800BBC34: lw          $a0, 0x44($t5)
    ctx->r4 = MEM_W(ctx->r13, 0X44);
    // 0x800BBC38: jal         0x800BB938
    // 0x800BBC3C: addiu       $a0, $a0, 0x94
    ctx->r4 = ADD32(ctx->r4, 0X94);
    Audio_AllocNoteFromDisabled(rdram, ctx);
        goto after_16;
    // 0x800BBC3C: addiu       $a0, $a0, 0x94
    ctx->r4 = ADD32(ctx->r4, 0X94);
    after_16:
    // 0x800BBC40: bne         $v0, $zero, L_800BBD04
    if (ctx->r2 != 0) {
        // 0x800BBC44: or          $a2, $v0, $zero
        ctx->r6 = ctx->r2 | 0;
            goto L_800BBD04;
    }
    // 0x800BBC44: or          $a2, $v0, $zero
    ctx->r6 = ctx->r2 | 0;
    // 0x800BBC48: lui         $a0, 0x8004
    ctx->r4 = S32(0X8004 << 16);
    // 0x800BBC4C: addiu       $a0, $a0, 0x4760
    ctx->r4 = ADD32(ctx->r4, 0X4760);
    // 0x800BBC50: jal         0x800BB938
    // 0x800BBC54: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    Audio_AllocNoteFromDisabled(rdram, ctx);
        goto after_17;
    // 0x800BBC54: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    after_17:
    // 0x800BBC58: bne         $v0, $zero, L_800BBD04
    if (ctx->r2 != 0) {
        // 0x800BBC5C: or          $a2, $v0, $zero
        ctx->r6 = ctx->r2 | 0;
            goto L_800BBD04;
    }
    // 0x800BBC5C: or          $a2, $v0, $zero
    ctx->r6 = ctx->r2 | 0;
    // 0x800BBC60: lw          $a0, 0x4C($s0)
    ctx->r4 = MEM_W(ctx->r16, 0X4C);
    // 0x800BBC64: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    // 0x800BBC68: jal         0x800BB984
    // 0x800BBC6C: addiu       $a0, $a0, 0x84
    ctx->r4 = ADD32(ctx->r4, 0X84);
    Audio_AllocNoteFromDecaying(rdram, ctx);
        goto after_18;
    // 0x800BBC6C: addiu       $a0, $a0, 0x84
    ctx->r4 = ADD32(ctx->r4, 0X84);
    after_18:
    // 0x800BBC70: bne         $v0, $zero, L_800BBD04
    if (ctx->r2 != 0) {
        // 0x800BBC74: or          $a2, $v0, $zero
        ctx->r6 = ctx->r2 | 0;
            goto L_800BBD04;
    }
    // 0x800BBC74: or          $a2, $v0, $zero
    ctx->r6 = ctx->r2 | 0;
    // 0x800BBC78: lw          $t6, 0x4C($s0)
    ctx->r14 = MEM_W(ctx->r16, 0X4C);
    // 0x800BBC7C: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    // 0x800BBC80: lw          $a0, 0x44($t6)
    ctx->r4 = MEM_W(ctx->r14, 0X44);
    // 0x800BBC84: jal         0x800BB984
    // 0x800BBC88: addiu       $a0, $a0, 0x94
    ctx->r4 = ADD32(ctx->r4, 0X94);
    Audio_AllocNoteFromDecaying(rdram, ctx);
        goto after_19;
    // 0x800BBC88: addiu       $a0, $a0, 0x94
    ctx->r4 = ADD32(ctx->r4, 0X94);
    after_19:
    // 0x800BBC8C: bne         $v0, $zero, L_800BBD04
    if (ctx->r2 != 0) {
        // 0x800BBC90: or          $a2, $v0, $zero
        ctx->r6 = ctx->r2 | 0;
            goto L_800BBD04;
    }
    // 0x800BBC90: or          $a2, $v0, $zero
    ctx->r6 = ctx->r2 | 0;
    // 0x800BBC94: lui         $a0, 0x8004
    ctx->r4 = S32(0X8004 << 16);
    // 0x800BBC98: addiu       $a0, $a0, 0x4760
    ctx->r4 = ADD32(ctx->r4, 0X4760);
    // 0x800BBC9C: jal         0x800BB984
    // 0x800BBCA0: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    Audio_AllocNoteFromDecaying(rdram, ctx);
        goto after_20;
    // 0x800BBCA0: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    after_20:
    // 0x800BBCA4: bne         $v0, $zero, L_800BBD04
    if (ctx->r2 != 0) {
        // 0x800BBCA8: or          $a2, $v0, $zero
        ctx->r6 = ctx->r2 | 0;
            goto L_800BBD04;
    }
    // 0x800BBCA8: or          $a2, $v0, $zero
    ctx->r6 = ctx->r2 | 0;
    // 0x800BBCAC: lw          $a0, 0x4C($s0)
    ctx->r4 = MEM_W(ctx->r16, 0X4C);
    // 0x800BBCB0: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    // 0x800BBCB4: jal         0x800BB9D4
    // 0x800BBCB8: addiu       $a0, $a0, 0x84
    ctx->r4 = ADD32(ctx->r4, 0X84);
    Audio_AllocNoteFromActive(rdram, ctx);
        goto after_21;
    // 0x800BBCB8: addiu       $a0, $a0, 0x84
    ctx->r4 = ADD32(ctx->r4, 0X84);
    after_21:
    // 0x800BBCBC: bne         $v0, $zero, L_800BBD04
    if (ctx->r2 != 0) {
        // 0x800BBCC0: or          $a2, $v0, $zero
        ctx->r6 = ctx->r2 | 0;
            goto L_800BBD04;
    }
    // 0x800BBCC0: or          $a2, $v0, $zero
    ctx->r6 = ctx->r2 | 0;
    // 0x800BBCC4: lw          $t7, 0x4C($s0)
    ctx->r15 = MEM_W(ctx->r16, 0X4C);
    // 0x800BBCC8: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    // 0x800BBCCC: lw          $a0, 0x44($t7)
    ctx->r4 = MEM_W(ctx->r15, 0X44);
    // 0x800BBCD0: jal         0x800BB9D4
    // 0x800BBCD4: addiu       $a0, $a0, 0x94
    ctx->r4 = ADD32(ctx->r4, 0X94);
    Audio_AllocNoteFromActive(rdram, ctx);
        goto after_22;
    // 0x800BBCD4: addiu       $a0, $a0, 0x94
    ctx->r4 = ADD32(ctx->r4, 0X94);
    after_22:
    // 0x800BBCD8: bne         $v0, $zero, L_800BBD04
    if (ctx->r2 != 0) {
        // 0x800BBCDC: or          $a2, $v0, $zero
        ctx->r6 = ctx->r2 | 0;
            goto L_800BBD04;
    }
    // 0x800BBCDC: or          $a2, $v0, $zero
    ctx->r6 = ctx->r2 | 0;
    // 0x800BBCE0: lui         $a0, 0x8004
    ctx->r4 = S32(0X8004 << 16);
    // 0x800BBCE4: addiu       $a0, $a0, 0x4760
    ctx->r4 = ADD32(ctx->r4, 0X4760);
    // 0x800BBCE8: jal         0x800BB9D4
    // 0x800BBCEC: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    Audio_AllocNoteFromActive(rdram, ctx);
        goto after_23;
    // 0x800BBCEC: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    after_23:
    // 0x800BBCF0: bne         $v0, $zero, L_800BBD04
    if (ctx->r2 != 0) {
        // 0x800BBCF4: or          $a2, $v0, $zero
        ctx->r6 = ctx->r2 | 0;
            goto L_800BBD04;
    }
    // 0x800BBCF4: or          $a2, $v0, $zero
    ctx->r6 = ctx->r2 | 0;
    // 0x800BBCF8: sb          $zero, 0x2($s0)
    MEM_B(0X2, ctx->r16) = 0;
    // 0x800BBCFC: b           L_800BBD08
    // 0x800BBD00: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
        goto L_800BBD08;
    // 0x800BBD00: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_800BBD04:
    // 0x800BBD04: or          $v0, $a2, $zero
    ctx->r2 = ctx->r6 | 0;
L_800BBD08:
    // 0x800BBD08: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    // 0x800BBD0C: lw          $s0, 0x18($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X18);
    // 0x800BBD10: addiu       $sp, $sp, 0x28
    ctx->r29 = ADD32(ctx->r29, 0X28);
    // 0x800BBD14: jr          $ra
    // 0x800BBD18: nop

    return;
    // 0x800BBD18: nop

;}
RECOMP_FUNC void Audio_NoteInitAll(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800BBD1C: addiu       $sp, $sp, -0x40
    ctx->r29 = ADD32(ctx->r29, -0X40);
    // 0x800BBD20: sw          $s4, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r20;
    // 0x800BBD24: lui         $s4, 0x8004
    ctx->r20 = S32(0X8004 << 16);
    // 0x800BBD28: addiu       $s4, $s4, 0x5548
    ctx->r20 = ADD32(ctx->r20, 0X5548);
    // 0x800BBD2C: lw          $t6, 0x0($s4)
    ctx->r14 = MEM_W(ctx->r20, 0X0);
    // 0x800BBD30: sw          $s1, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r17;
    // 0x800BBD34: sw          $ra, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r31;
    // 0x800BBD38: sw          $s7, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r23;
    // 0x800BBD3C: sw          $s6, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r22;
    // 0x800BBD40: sw          $s5, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r21;
    // 0x800BBD44: sw          $s3, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r19;
    // 0x800BBD48: sw          $s2, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r18;
    // 0x800BBD4C: sw          $s0, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r16;
    // 0x800BBD50: sdc1        $f20, 0x10($sp)
    CHECK_FR(ctx, 20);
    SD(ctx->f20.u64, 0X10, ctx->r29);
    // 0x800BBD54: blez        $t6, L_800BBE00
    if (SIGNED(ctx->r14) <= 0) {
        // 0x800BBD58: or          $s1, $zero, $zero
        ctx->r17 = 0 | 0;
            goto L_800BBE00;
    }
    // 0x800BBD58: or          $s1, $zero, $zero
    ctx->r17 = 0 | 0;
    // 0x800BBD5C: lui         $s7, 0x8004
    ctx->r23 = S32(0X8004 << 16);
    // 0x800BBD60: lui         $s6, 0x800F
    ctx->r22 = S32(0X800F << 16);
    // 0x800BBD64: lui         $s5, 0x8004
    ctx->r21 = S32(0X8004 << 16);
    // 0x800BBD68: mtc1        $zero, $f20
    ctx->f20.u32l = 0;
    // 0x800BBD6C: addiu       $s5, $s5, -0x340
    ctx->r21 = ADD32(ctx->r21, -0X340);
    // 0x800BBD70: addiu       $s6, $s6, -0x2FF0
    ctx->r22 = ADD32(ctx->r22, -0X2FF0);
    // 0x800BBD74: addiu       $s7, $s7, -0x1A90
    ctx->r23 = ADD32(ctx->r23, -0X1A90);
    // 0x800BBD78: or          $s2, $zero, $zero
    ctx->r18 = 0 | 0;
    // 0x800BBD7C: addiu       $s3, $zero, -0x1
    ctx->r19 = ADD32(0, -0X1);
    // 0x800BBD80: lw          $t7, 0x0($s5)
    ctx->r15 = MEM_W(ctx->r21, 0X0);
L_800BBD84:
    // 0x800BBD84: lw          $at, 0x0($s6)
    ctx->r1 = MEM_W(ctx->r22, 0X0);
    // 0x800BBD88: or          $a0, $s7, $zero
    ctx->r4 = ctx->r23 | 0;
    // 0x800BBD8C: addu        $s0, $s2, $t7
    ctx->r16 = ADD32(ctx->r18, ctx->r15);
    // 0x800BBD90: sw          $at, 0xB0($s0)
    MEM_W(0XB0, ctx->r16) = ctx->r1;
    // 0x800BBD94: lw          $t9, 0x4($s6)
    ctx->r25 = MEM_W(ctx->r22, 0X4);
    // 0x800BBD98: addiu       $a1, $zero, 0x110
    ctx->r5 = ADD32(0, 0X110);
    // 0x800BBD9C: sw          $t9, 0xB4($s0)
    MEM_W(0XB4, ctx->r16) = ctx->r25;
    // 0x800BBDA0: lw          $at, 0x8($s6)
    ctx->r1 = MEM_W(ctx->r22, 0X8);
    // 0x800BBDA4: sw          $at, 0xB8($s0)
    MEM_W(0XB8, ctx->r16) = ctx->r1;
    // 0x800BBDA8: lw          $t9, 0xC($s6)
    ctx->r25 = MEM_W(ctx->r22, 0XC);
    // 0x800BBDAC: sb          $zero, 0x30($s0)
    MEM_B(0X30, ctx->r16) = 0;
    // 0x800BBDB0: sw          $s3, 0x44($s0)
    MEM_W(0X44, ctx->r16) = ctx->r19;
    // 0x800BBDB4: sw          $s3, 0x48($s0)
    MEM_W(0X48, ctx->r16) = ctx->r19;
    // 0x800BBDB8: sw          $s3, 0x40($s0)
    MEM_W(0X40, ctx->r16) = ctx->r19;
    // 0x800BBDBC: sb          $zero, 0x31($s0)
    MEM_B(0X31, ctx->r16) = 0;
    // 0x800BBDC0: swc1        $f20, 0x54($s0)
    MEM_W(0X54, ctx->r16) = ctx->f20.u32l;
    // 0x800BBDC4: sh          $zero, 0x34($s0)
    MEM_H(0X34, ctx->r16) = 0;
    // 0x800BBDC8: sb          $zero, 0x59($s0)
    MEM_B(0X59, ctx->r16) = 0;
    // 0x800BBDCC: sb          $zero, 0x58($s0)
    MEM_B(0X58, ctx->r16) = 0;
    // 0x800BBDD0: sb          $zero, 0xA0($s0)
    MEM_B(0XA0, ctx->r16) = 0;
    // 0x800BBDD4: swc1        $f20, 0x80($s0)
    MEM_W(0X80, ctx->r16) = ctx->f20.u32l;
    // 0x800BBDD8: swc1        $f20, 0x84($s0)
    MEM_W(0X84, ctx->r16) = ctx->f20.u32l;
    // 0x800BBDDC: jal         0x800B7760
    // 0x800BBDE0: sw          $t9, 0xBC($s0)
    MEM_W(0XBC, ctx->r16) = ctx->r25;
    AudioHeap_AllocZeroed(rdram, ctx);
        goto after_0;
    // 0x800BBDE0: sw          $t9, 0xBC($s0)
    MEM_W(0XBC, ctx->r16) = ctx->r25;
    after_0:
    // 0x800BBDE4: sw          $v0, 0x1C($s0)
    MEM_W(0X1C, ctx->r16) = ctx->r2;
    // 0x800BBDE8: lw          $t0, 0x0($s4)
    ctx->r8 = MEM_W(ctx->r20, 0X0);
    // 0x800BBDEC: addiu       $s1, $s1, 0x1
    ctx->r17 = ADD32(ctx->r17, 0X1);
    // 0x800BBDF0: addiu       $s2, $s2, 0xC0
    ctx->r18 = ADD32(ctx->r18, 0XC0);
    // 0x800BBDF4: slt         $at, $s1, $t0
    ctx->r1 = SIGNED(ctx->r17) < SIGNED(ctx->r8) ? 1 : 0;
    // 0x800BBDF8: bnel        $at, $zero, L_800BBD84
    if (ctx->r1 != 0) {
        // 0x800BBDFC: lw          $t7, 0x0($s5)
        ctx->r15 = MEM_W(ctx->r21, 0X0);
            goto L_800BBD84;
    }
    goto skip_0;
    // 0x800BBDFC: lw          $t7, 0x0($s5)
    ctx->r15 = MEM_W(ctx->r21, 0X0);
    skip_0:
L_800BBE00:
    // 0x800BBE00: lw          $ra, 0x3C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X3C);
    // 0x800BBE04: ldc1        $f20, 0x10($sp)
    CHECK_FR(ctx, 20);
    ctx->f20.u64 = LD(ctx->r29, 0X10);
    // 0x800BBE08: lw          $s0, 0x1C($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X1C);
    // 0x800BBE0C: lw          $s1, 0x20($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X20);
    // 0x800BBE10: lw          $s2, 0x24($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X24);
    // 0x800BBE14: lw          $s3, 0x28($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X28);
    // 0x800BBE18: lw          $s4, 0x2C($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X2C);
    // 0x800BBE1C: lw          $s5, 0x30($sp)
    ctx->r21 = MEM_W(ctx->r29, 0X30);
    // 0x800BBE20: lw          $s6, 0x34($sp)
    ctx->r22 = MEM_W(ctx->r29, 0X34);
    // 0x800BBE24: lw          $s7, 0x38($sp)
    ctx->r23 = MEM_W(ctx->r29, 0X38);
    // 0x800BBE28: jr          $ra
    // 0x800BBE2C: addiu       $sp, $sp, 0x40
    ctx->r29 = ADD32(ctx->r29, 0X40);
    return;
    // 0x800BBE2C: addiu       $sp, $sp, 0x40
    ctx->r29 = ADD32(ctx->r29, 0X40);
;}
RECOMP_FUNC void Audio_SequenceChannelProcessSound(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800BBE30: lw          $v0, 0x0($a0)
    ctx->r2 = MEM_W(ctx->r4, 0X0);
    // 0x800BBE34: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x800BBE38: or          $a3, $a0, $zero
    ctx->r7 = ctx->r4 | 0;
    // 0x800BBE3C: sll         $t7, $v0, 9
    ctx->r15 = S32(ctx->r2 << 9);
    // 0x800BBE40: bltz        $t7, L_800BBE50
    if (SIGNED(ctx->r15) < 0) {
        // 0x800BBE44: addiu       $t1, $zero, 0x10
        ctx->r9 = ADD32(0, 0X10);
            goto L_800BBE50;
    }
    // 0x800BBE44: addiu       $t1, $zero, 0x10
    ctx->r9 = ADD32(0, 0X10);
    // 0x800BBE48: beql        $a1, $zero, L_800BBEA0
    if (ctx->r5 == 0) {
        // 0x800BBE4C: sll         $t6, $v0, 10
        ctx->r14 = S32(ctx->r2 << 10);
            goto L_800BBEA0;
    }
    goto skip_0;
    // 0x800BBE4C: sll         $t6, $v0, 10
    ctx->r14 = S32(ctx->r2 << 10);
    skip_0:
L_800BBE50:
    // 0x800BBE50: lwc1        $f4, 0x24($a0)
    ctx->f4.u32l = MEM_W(ctx->r4, 0X24);
    // 0x800BBE54: lwc1        $f6, 0x20($a0)
    ctx->f6.u32l = MEM_W(ctx->r4, 0X20);
    // 0x800BBE58: lw          $v0, 0x44($a0)
    ctx->r2 = MEM_W(ctx->r4, 0X44);
    // 0x800BBE5C: mul.s       $f8, $f4, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = MUL_S(ctx->f4.fl, ctx->f6.fl);
    // 0x800BBE60: lwc1        $f10, 0x2C($v0)
    ctx->f10.u32l = MEM_W(ctx->r2, 0X2C);
    // 0x800BBE64: lw          $t8, 0x0($v0)
    ctx->r24 = MEM_W(ctx->r2, 0X0);
    // 0x800BBE68: sll         $t2, $t8, 2
    ctx->r10 = S32(ctx->r24 << 2);
    // 0x800BBE6C: mul.s       $f0, $f8, $f10
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f0.fl = MUL_S(ctx->f8.fl, ctx->f10.fl);
    // 0x800BBE70: bgezl       $t2, L_800BBE98
    if (SIGNED(ctx->r10) >= 0) {
        // 0x800BBE74: swc1        $f0, 0x2C($a0)
        MEM_W(0X2C, ctx->r4) = ctx->f0.u32l;
            goto L_800BBE98;
    }
    goto skip_1;
    // 0x800BBE74: swc1        $f0, 0x2C($a0)
    MEM_W(0X2C, ctx->r4) = ctx->f0.u32l;
    skip_1:
    // 0x800BBE78: lbu         $t3, 0x3($a0)
    ctx->r11 = MEM_BU(ctx->r4, 0X3);
    // 0x800BBE7C: andi        $t4, $t3, 0x20
    ctx->r12 = ctx->r11 & 0X20;
    // 0x800BBE80: beql        $t4, $zero, L_800BBE98
    if (ctx->r12 == 0) {
        // 0x800BBE84: swc1        $f0, 0x2C($a0)
        MEM_W(0X2C, ctx->r4) = ctx->f0.u32l;
            goto L_800BBE98;
    }
    goto skip_2;
    // 0x800BBE84: swc1        $f0, 0x2C($a0)
    MEM_W(0X2C, ctx->r4) = ctx->f0.u32l;
    skip_2:
    // 0x800BBE88: lwc1        $f16, 0x24($v0)
    ctx->f16.u32l = MEM_W(ctx->r2, 0X24);
    // 0x800BBE8C: mul.s       $f0, $f16, $f0
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f0.fl = MUL_S(ctx->f16.fl, ctx->f0.fl);
    // 0x800BBE90: nop

    // 0x800BBE94: swc1        $f0, 0x2C($a0)
    MEM_W(0X2C, ctx->r4) = ctx->f0.u32l;
L_800BBE98:
    // 0x800BBE98: lw          $v0, 0x0($a0)
    ctx->r2 = MEM_W(ctx->r4, 0X0);
    // 0x800BBE9C: sll         $t6, $v0, 10
    ctx->r14 = S32(ctx->r2 << 10);
L_800BBEA0:
    // 0x800BBEA0: bgez        $t6, L_800BBEC0
    if (SIGNED(ctx->r14) >= 0) {
        // 0x800BBEA4: addiu       $t0, $zero, 0x80
        ctx->r8 = ADD32(0, 0X80);
            goto L_800BBEC0;
    }
    // 0x800BBEA4: addiu       $t0, $zero, 0x80
    ctx->r8 = ADD32(0, 0X80);
    // 0x800BBEA8: lbu         $t7, 0x9($a0)
    ctx->r15 = MEM_BU(ctx->r4, 0X9);
    // 0x800BBEAC: lbu         $t8, 0xA($a0)
    ctx->r24 = MEM_BU(ctx->r4, 0XA);
    // 0x800BBEB0: multu       $t7, $t8
    result = U64(U32(ctx->r15)) * U64(U32(ctx->r24)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x800BBEB4: mflo        $t9
    ctx->r25 = lo;
    // 0x800BBEB8: sw          $t9, 0x28($a0)
    MEM_W(0X28, ctx->r4) = ctx->r25;
    // 0x800BBEBC: nop

L_800BBEC0:
    // 0x800BBEC0: lw          $v1, 0x48($a3)
    ctx->r3 = MEM_W(ctx->r7, 0X48);
    // 0x800BBEC4: addiu       $a2, $a2, 0x4
    ctx->r6 = ADD32(ctx->r6, 0X4);
    // 0x800BBEC8: beq         $v1, $zero, L_800BBFC4
    if (ctx->r3 == 0) {
        // 0x800BBECC: nop
    
            goto L_800BBFC4;
    }
    // 0x800BBECC: nop

    // 0x800BBED0: lw          $v0, 0x0($v1)
    ctx->r2 = MEM_W(ctx->r3, 0X0);
    // 0x800BBED4: srl         $t2, $v0, 31
    ctx->r10 = S32(U32(ctx->r2) >> 31);
    // 0x800BBED8: beq         $t2, $zero, L_800BBFC4
    if (ctx->r10 == 0) {
        // 0x800BBEDC: nop
    
            goto L_800BBFC4;
    }
    // 0x800BBEDC: nop

    // 0x800BBEE0: lw          $t3, 0x40($v1)
    ctx->r11 = MEM_W(ctx->r3, 0X40);
    // 0x800BBEE4: sll         $t5, $v0, 5
    ctx->r13 = S32(ctx->r2 << 5);
    // 0x800BBEE8: beq         $t3, $zero, L_800BBFC4
    if (ctx->r11 == 0) {
        // 0x800BBEEC: nop
    
            goto L_800BBFC4;
    }
    // 0x800BBEEC: nop

    // 0x800BBEF0: bgezl       $t5, L_800BBF50
    if (SIGNED(ctx->r13) >= 0) {
        // 0x800BBEF4: lb          $t8, 0x1($a0)
        ctx->r24 = MEM_B(ctx->r4, 0X1);
            goto L_800BBF50;
    }
    goto skip_3;
    // 0x800BBEF4: lb          $t8, 0x1($a0)
    ctx->r24 = MEM_B(ctx->r4, 0X1);
    skip_3:
    // 0x800BBEF8: lwc1        $f18, 0x24($v1)
    ctx->f18.u32l = MEM_W(ctx->r3, 0X24);
    // 0x800BBEFC: lwc1        $f4, 0x30($a0)
    ctx->f4.u32l = MEM_W(ctx->r4, 0X30);
    // 0x800BBF00: lwc1        $f8, 0x28($v1)
    ctx->f8.u32l = MEM_W(ctx->r3, 0X28);
    // 0x800BBF04: lbu         $t6, 0x5($v1)
    ctx->r14 = MEM_BU(ctx->r3, 0X5);
    // 0x800BBF08: mul.s       $f6, $f18, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = MUL_S(ctx->f18.fl, ctx->f4.fl);
    // 0x800BBF0C: lbu         $t5, 0x0($v1)
    ctx->r13 = MEM_BU(ctx->r3, 0X0);
    // 0x800BBF10: swc1        $f6, 0x30($v1)
    MEM_W(0X30, ctx->r3) = ctx->f6.u32l;
    // 0x800BBF14: lwc1        $f10, 0x2C($a0)
    ctx->f10.u32l = MEM_W(ctx->r4, 0X2C);
    // 0x800BBF18: mul.s       $f16, $f8, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f16.fl = MUL_S(ctx->f8.fl, ctx->f10.fl);
    // 0x800BBF1C: swc1        $f16, 0x2C($v1)
    MEM_W(0X2C, ctx->r3) = ctx->f16.u32l;
    // 0x800BBF20: lbu         $t7, 0xA($a0)
    ctx->r15 = MEM_BU(ctx->r4, 0XA);
    // 0x800BBF24: lw          $t2, 0x28($a0)
    ctx->r10 = MEM_W(ctx->r4, 0X28);
    // 0x800BBF28: subu        $t8, $t0, $t7
    ctx->r24 = SUB32(ctx->r8, ctx->r15);
    // 0x800BBF2C: multu       $t6, $t8
    result = U64(U32(ctx->r14)) * U64(U32(ctx->r24)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x800BBF30: andi        $t7, $t5, 0xFFFB
    ctx->r15 = ctx->r13 & 0XFFFB;
    // 0x800BBF34: sb          $t7, 0x0($v1)
    MEM_B(0X0, ctx->r3) = ctx->r15;
    // 0x800BBF38: mflo        $t9
    ctx->r25 = lo;
    // 0x800BBF3C: addu        $t3, $t2, $t9
    ctx->r11 = ADD32(ctx->r10, ctx->r25);
    // 0x800BBF40: sra         $t4, $t3, 7
    ctx->r12 = S32(SIGNED(ctx->r11) >> 7);
    // 0x800BBF44: b           L_800BBFC4
    // 0x800BBF48: sb          $t4, 0x6($v1)
    MEM_B(0X6, ctx->r3) = ctx->r12;
        goto L_800BBFC4;
    // 0x800BBF48: sb          $t4, 0x6($v1)
    MEM_B(0X6, ctx->r3) = ctx->r12;
    // 0x800BBF4C: lb          $t8, 0x1($a0)
    ctx->r24 = MEM_B(ctx->r4, 0X1);
L_800BBF50:
    // 0x800BBF50: bgezl       $t8, L_800BBF6C
    if (SIGNED(ctx->r24) >= 0) {
        // 0x800BBF54: lw          $v0, 0x0($a0)
        ctx->r2 = MEM_W(ctx->r4, 0X0);
            goto L_800BBF6C;
    }
    goto skip_4;
    // 0x800BBF54: lw          $v0, 0x0($a0)
    ctx->r2 = MEM_W(ctx->r4, 0X0);
    skip_4:
    // 0x800BBF58: lwc1        $f18, 0x24($v1)
    ctx->f18.u32l = MEM_W(ctx->r3, 0X24);
    // 0x800BBF5C: lwc1        $f4, 0x30($a0)
    ctx->f4.u32l = MEM_W(ctx->r4, 0X30);
    // 0x800BBF60: mul.s       $f6, $f18, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = MUL_S(ctx->f18.fl, ctx->f4.fl);
    // 0x800BBF64: swc1        $f6, 0x30($v1)
    MEM_W(0X30, ctx->r3) = ctx->f6.u32l;
    // 0x800BBF68: lw          $v0, 0x0($a0)
    ctx->r2 = MEM_W(ctx->r4, 0X0);
L_800BBF6C:
    // 0x800BBF6C: sll         $t9, $v0, 9
    ctx->r25 = S32(ctx->r2 << 9);
    // 0x800BBF70: bltzl       $t9, L_800BBF84
    if (SIGNED(ctx->r25) < 0) {
        // 0x800BBF74: lwc1        $f8, 0x28($v1)
        ctx->f8.u32l = MEM_W(ctx->r3, 0X28);
            goto L_800BBF84;
    }
    goto skip_5;
    // 0x800BBF74: lwc1        $f8, 0x28($v1)
    ctx->f8.u32l = MEM_W(ctx->r3, 0X28);
    skip_5:
    // 0x800BBF78: beql        $a1, $zero, L_800BBF98
    if (ctx->r5 == 0) {
        // 0x800BBF7C: sll         $t4, $v0, 10
        ctx->r12 = S32(ctx->r2 << 10);
            goto L_800BBF98;
    }
    goto skip_6;
    // 0x800BBF7C: sll         $t4, $v0, 10
    ctx->r12 = S32(ctx->r2 << 10);
    skip_6:
    // 0x800BBF80: lwc1        $f8, 0x28($v1)
    ctx->f8.u32l = MEM_W(ctx->r3, 0X28);
L_800BBF84:
    // 0x800BBF84: lwc1        $f10, 0x2C($a0)
    ctx->f10.u32l = MEM_W(ctx->r4, 0X2C);
    // 0x800BBF88: mul.s       $f16, $f8, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f16.fl = MUL_S(ctx->f8.fl, ctx->f10.fl);
    // 0x800BBF8C: swc1        $f16, 0x2C($v1)
    MEM_W(0X2C, ctx->r3) = ctx->f16.u32l;
    // 0x800BBF90: lw          $v0, 0x0($a0)
    ctx->r2 = MEM_W(ctx->r4, 0X0);
    // 0x800BBF94: sll         $t4, $v0, 10
    ctx->r12 = S32(ctx->r2 << 10);
L_800BBF98:
    // 0x800BBF98: bgez        $t4, L_800BBFC4
    if (SIGNED(ctx->r12) >= 0) {
        // 0x800BBF9C: nop
    
            goto L_800BBFC4;
    }
    // 0x800BBF9C: nop

    // 0x800BBFA0: lbu         $t7, 0xA($a0)
    ctx->r15 = MEM_BU(ctx->r4, 0XA);
    // 0x800BBFA4: lbu         $t5, 0x5($v1)
    ctx->r13 = MEM_BU(ctx->r3, 0X5);
    // 0x800BBFA8: lw          $t2, 0x28($a0)
    ctx->r10 = MEM_W(ctx->r4, 0X28);
    // 0x800BBFAC: subu        $t6, $t0, $t7
    ctx->r14 = SUB32(ctx->r8, ctx->r15);
    // 0x800BBFB0: multu       $t5, $t6
    result = U64(U32(ctx->r13)) * U64(U32(ctx->r14)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x800BBFB4: mflo        $t8
    ctx->r24 = lo;
    // 0x800BBFB8: addu        $t9, $t2, $t8
    ctx->r25 = ADD32(ctx->r10, ctx->r24);
    // 0x800BBFBC: sra         $t3, $t9, 7
    ctx->r11 = S32(SIGNED(ctx->r25) >> 7);
    // 0x800BBFC0: sb          $t3, 0x6($v1)
    MEM_B(0X6, ctx->r3) = ctx->r11;
L_800BBFC4:
    // 0x800BBFC4: bne         $a2, $t1, L_800BBEC0
    if (ctx->r6 != ctx->r9) {
        // 0x800BBFC8: addiu       $a3, $a3, 0x4
        ctx->r7 = ADD32(ctx->r7, 0X4);
            goto L_800BBEC0;
    }
    // 0x800BBFC8: addiu       $a3, $a3, 0x4
    ctx->r7 = ADD32(ctx->r7, 0X4);
    // 0x800BBFCC: jr          $ra
    // 0x800BBFD0: sb          $zero, 0x1($a0)
    MEM_B(0X1, ctx->r4) = 0;
    return;
    // 0x800BBFD0: sb          $zero, 0x1($a0)
    MEM_B(0X1, ctx->r4) = 0;
;}
RECOMP_FUNC void Audio_SequencePlayerProcessSound(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800BBFD4: addiu       $sp, $sp, -0x30
    ctx->r29 = ADD32(ctx->r29, -0X30);
    // 0x800BBFD8: sw          $ra, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r31;
    // 0x800BBFDC: sw          $s5, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r21;
    // 0x800BBFE0: sw          $s4, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r20;
    // 0x800BBFE4: sw          $s3, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r19;
    // 0x800BBFE8: sw          $s2, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r18;
    // 0x800BBFEC: sw          $s1, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r17;
    // 0x800BBFF0: sw          $s0, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r16;
    // 0x800BBFF4: lhu         $t6, 0x10($a0)
    ctx->r14 = MEM_HU(ctx->r4, 0X10);
    // 0x800BBFF8: lui         $s5, 0x8004
    ctx->r21 = S32(0X8004 << 16);
    // 0x800BBFFC: or          $s3, $a0, $zero
    ctx->r19 = ctx->r4 | 0;
    // 0x800BC000: beq         $t6, $zero, L_800BC098
    if (ctx->r14 == 0) {
        // 0x800BC004: addiu       $s5, $s5, 0x4688
        ctx->r21 = ADD32(ctx->r21, 0X4688);
            goto L_800BC098;
    }
    // 0x800BC004: addiu       $s5, $s5, 0x4688
    ctx->r21 = ADD32(ctx->r21, 0X4688);
    // 0x800BC008: lwc1        $f4, 0x18($a0)
    ctx->f4.u32l = MEM_W(ctx->r4, 0X18);
    // 0x800BC00C: lwc1        $f6, 0x1C($a0)
    ctx->f6.u32l = MEM_W(ctx->r4, 0X1C);
    // 0x800BC010: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x800BC014: mtc1        $at, $f2
    ctx->f2.u32l = ctx->r1;
    // 0x800BC018: add.s       $f8, $f4, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = ctx->f4.fl + ctx->f6.fl;
    // 0x800BC01C: lbu         $t8, 0x0($a0)
    ctx->r24 = MEM_BU(ctx->r4, 0X0);
    // 0x800BC020: swc1        $f8, 0x18($a0)
    MEM_W(0X18, ctx->r4) = ctx->f8.u32l;
    // 0x800BC024: lwc1        $f0, 0x18($a0)
    ctx->f0.u32l = MEM_W(ctx->r4, 0X18);
    // 0x800BC028: ori         $t9, $t8, 0x4
    ctx->r25 = ctx->r24 | 0X4;
    // 0x800BC02C: sb          $t9, 0x0($a0)
    MEM_B(0X0, ctx->r4) = ctx->r25;
    // 0x800BC030: c.lt.s      $f2, $f0
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 0);
    c1cs = ctx->f2.fl < ctx->f0.fl;
    // 0x800BC034: nop

    // 0x800BC038: bc1fl       L_800BC04C
    if (!c1cs) {
        // 0x800BC03C: mtc1        $zero, $f2
        ctx->f2.u32l = 0;
            goto L_800BC04C;
    }
    goto skip_0;
    // 0x800BC03C: mtc1        $zero, $f2
    ctx->f2.u32l = 0;
    skip_0:
    // 0x800BC040: swc1        $f2, 0x18($a0)
    MEM_W(0X18, ctx->r4) = ctx->f2.u32l;
    // 0x800BC044: lwc1        $f0, 0x18($a0)
    ctx->f0.u32l = MEM_W(ctx->r4, 0X18);
    // 0x800BC048: mtc1        $zero, $f2
    ctx->f2.u32l = 0;
L_800BC04C:
    // 0x800BC04C: nop

    // 0x800BC050: c.lt.s      $f0, $f2
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    c1cs = ctx->f0.fl < ctx->f2.fl;
    // 0x800BC054: nop

    // 0x800BC058: bc1fl       L_800BC068
    if (!c1cs) {
        // 0x800BC05C: lhu         $t0, 0x10($s3)
        ctx->r8 = MEM_HU(ctx->r19, 0X10);
            goto L_800BC068;
    }
    goto skip_1;
    // 0x800BC05C: lhu         $t0, 0x10($s3)
    ctx->r8 = MEM_HU(ctx->r19, 0X10);
    skip_1:
    // 0x800BC060: swc1        $f2, 0x18($s3)
    MEM_W(0X18, ctx->r19) = ctx->f2.u32l;
    // 0x800BC064: lhu         $t0, 0x10($s3)
    ctx->r8 = MEM_HU(ctx->r19, 0X10);
L_800BC068:
    // 0x800BC068: addiu       $t1, $t0, -0x1
    ctx->r9 = ADD32(ctx->r8, -0X1);
    // 0x800BC06C: andi        $t2, $t1, 0xFFFF
    ctx->r10 = ctx->r9 & 0XFFFF;
    // 0x800BC070: bne         $t2, $zero, L_800BC098
    if (ctx->r10 != 0) {
        // 0x800BC074: sh          $t1, 0x10($s3)
        MEM_H(0X10, ctx->r19) = ctx->r9;
            goto L_800BC098;
    }
    // 0x800BC074: sh          $t1, 0x10($s3)
    MEM_H(0X10, ctx->r19) = ctx->r9;
    // 0x800BC078: lbu         $t3, 0x1($s3)
    ctx->r11 = MEM_BU(ctx->r19, 0X1);
    // 0x800BC07C: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x800BC080: bnel        $t3, $at, L_800BC09C
    if (ctx->r11 != ctx->r1) {
        // 0x800BC084: lw          $t4, 0x0($s3)
        ctx->r12 = MEM_W(ctx->r19, 0X0);
            goto L_800BC09C;
    }
    goto skip_2;
    // 0x800BC084: lw          $t4, 0x0($s3)
    ctx->r12 = MEM_W(ctx->r19, 0X0);
    skip_2:
    // 0x800BC088: jal         0x800BCEE0
    // 0x800BC08C: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
    AudioSeq_SequencePlayerDisable(rdram, ctx);
        goto after_0;
    // 0x800BC08C: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
    after_0:
    // 0x800BC090: b           L_800BC114
    // 0x800BC094: lw          $ra, 0x2C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X2C);
        goto L_800BC114;
    // 0x800BC094: lw          $ra, 0x2C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X2C);
L_800BC098:
    // 0x800BC098: lw          $t4, 0x0($s3)
    ctx->r12 = MEM_W(ctx->r19, 0X0);
L_800BC09C:
    // 0x800BC09C: or          $s0, $zero, $zero
    ctx->r16 = 0 | 0;
    // 0x800BC0A0: or          $s1, $s3, $zero
    ctx->r17 = ctx->r19 | 0;
    // 0x800BC0A4: sll         $t6, $t4, 5
    ctx->r14 = S32(ctx->r12 << 5);
    // 0x800BC0A8: bgez        $t6, L_800BC0C0
    if (SIGNED(ctx->r14) >= 0) {
        // 0x800BC0AC: addiu       $s4, $zero, 0x40
        ctx->r20 = ADD32(0, 0X40);
            goto L_800BC0C0;
    }
    // 0x800BC0AC: addiu       $s4, $zero, 0x40
    ctx->r20 = ADD32(0, 0X40);
    // 0x800BC0B0: lwc1        $f10, 0x18($s3)
    ctx->f10.u32l = MEM_W(ctx->r19, 0X18);
    // 0x800BC0B4: lwc1        $f16, 0x28($s3)
    ctx->f16.u32l = MEM_W(ctx->r19, 0X28);
    // 0x800BC0B8: mul.s       $f18, $f10, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f18.fl = MUL_S(ctx->f10.fl, ctx->f16.fl);
    // 0x800BC0BC: swc1        $f18, 0x2C($s3)
    MEM_W(0X2C, ctx->r19) = ctx->f18.u32l;
L_800BC0C0:
    // 0x800BC0C0: addiu       $s2, $zero, 0x1
    ctx->r18 = ADD32(0, 0X1);
L_800BC0C4:
    // 0x800BC0C4: lw          $a0, 0x30($s1)
    ctx->r4 = MEM_W(ctx->r17, 0X30);
    // 0x800BC0C8: xor         $t7, $s5, $a0
    ctx->r15 = ctx->r21 ^ ctx->r4;
    // 0x800BC0CC: sltu        $t7, $zero, $t7
    ctx->r15 = 0 < ctx->r15 ? 1 : 0;
    // 0x800BC0D0: bnel        $s2, $t7, L_800BC0FC
    if (ctx->r18 != ctx->r15) {
        // 0x800BC0D4: addiu       $s0, $s0, 0x4
        ctx->r16 = ADD32(ctx->r16, 0X4);
            goto L_800BC0FC;
    }
    goto skip_3;
    // 0x800BC0D4: addiu       $s0, $s0, 0x4
    ctx->r16 = ADD32(ctx->r16, 0X4);
    skip_3:
    // 0x800BC0D8: lw          $t8, 0x0($a0)
    ctx->r24 = MEM_W(ctx->r4, 0X0);
    // 0x800BC0DC: srl         $t9, $t8, 31
    ctx->r25 = S32(U32(ctx->r24) >> 31);
    // 0x800BC0E0: bnel        $s2, $t9, L_800BC0FC
    if (ctx->r18 != ctx->r25) {
        // 0x800BC0E4: addiu       $s0, $s0, 0x4
        ctx->r16 = ADD32(ctx->r16, 0X4);
            goto L_800BC0FC;
    }
    goto skip_4;
    // 0x800BC0E4: addiu       $s0, $s0, 0x4
    ctx->r16 = ADD32(ctx->r16, 0X4);
    skip_4:
    // 0x800BC0E8: lw          $a1, 0x0($s3)
    ctx->r5 = MEM_W(ctx->r19, 0X0);
    // 0x800BC0EC: sll         $t0, $a1, 5
    ctx->r8 = S32(ctx->r5 << 5);
    // 0x800BC0F0: jal         0x800BBE30
    // 0x800BC0F4: srl         $a1, $t0, 31
    ctx->r5 = S32(U32(ctx->r8) >> 31);
    Audio_SequenceChannelProcessSound(rdram, ctx);
        goto after_1;
    // 0x800BC0F4: srl         $a1, $t0, 31
    ctx->r5 = S32(U32(ctx->r8) >> 31);
    after_1:
    // 0x800BC0F8: addiu       $s0, $s0, 0x4
    ctx->r16 = ADD32(ctx->r16, 0X4);
L_800BC0FC:
    // 0x800BC0FC: bne         $s0, $s4, L_800BC0C4
    if (ctx->r16 != ctx->r20) {
        // 0x800BC100: addiu       $s1, $s1, 0x4
        ctx->r17 = ADD32(ctx->r17, 0X4);
            goto L_800BC0C4;
    }
    // 0x800BC100: addiu       $s1, $s1, 0x4
    ctx->r17 = ADD32(ctx->r17, 0X4);
    // 0x800BC104: lbu         $t2, 0x0($s3)
    ctx->r10 = MEM_BU(ctx->r19, 0X0);
    // 0x800BC108: andi        $t3, $t2, 0xFFFB
    ctx->r11 = ctx->r10 & 0XFFFB;
    // 0x800BC10C: sb          $t3, 0x0($s3)
    MEM_B(0X0, ctx->r19) = ctx->r11;
    // 0x800BC110: lw          $ra, 0x2C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X2C);
L_800BC114:
    // 0x800BC114: lw          $s0, 0x14($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X14);
    // 0x800BC118: lw          $s1, 0x18($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X18);
    // 0x800BC11C: lw          $s2, 0x1C($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X1C);
    // 0x800BC120: lw          $s3, 0x20($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X20);
    // 0x800BC124: lw          $s4, 0x24($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X24);
    // 0x800BC128: lw          $s5, 0x28($sp)
    ctx->r21 = MEM_W(ctx->r29, 0X28);
    // 0x800BC12C: jr          $ra
    // 0x800BC130: addiu       $sp, $sp, 0x30
    ctx->r29 = ADD32(ctx->r29, 0X30);
    return;
    // 0x800BC130: addiu       $sp, $sp, 0x30
    ctx->r29 = ADD32(ctx->r29, 0X30);
;}
RECOMP_FUNC void Audio_GetPortamentoFreqScale(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800BC134: lwc1        $f4, 0x4($a0)
    ctx->f4.u32l = MEM_W(ctx->r4, 0X4);
    // 0x800BC138: lwc1        $f6, 0x8($a0)
    ctx->f6.u32l = MEM_W(ctx->r4, 0X8);
    // 0x800BC13C: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
    // 0x800BC140: lui         $at, 0x4F00
    ctx->r1 = S32(0X4F00 << 16);
    // 0x800BC144: add.s       $f8, $f4, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = ctx->f4.fl + ctx->f6.fl;
    // 0x800BC148: swc1        $f8, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->f8.u32l;
    // 0x800BC14C: cfc1        $t6, $FpcCsr
    ctx->r14 = get_cop1_cs();
    // 0x800BC150: ctc1        $v0, $FpcCsr
    set_cop1_cs(ctx->r2);
    // 0x800BC154: lwc1        $f10, 0x4($a0)
    ctx->f10.u32l = MEM_W(ctx->r4, 0X4);
    // 0x800BC158: cvt.w.s     $f16, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    ctx->f16.u32l = CVT_W_S(ctx->f10.fl);
    // 0x800BC15C: cfc1        $v0, $FpcCsr
    ctx->r2 = get_cop1_cs();
    // 0x800BC160: nop

    // 0x800BC164: andi        $v0, $v0, 0x78
    ctx->r2 = ctx->r2 & 0X78;
    // 0x800BC168: beql        $v0, $zero, L_800BC1B8
    if (ctx->r2 == 0) {
        // 0x800BC16C: mfc1        $v0, $f16
        ctx->r2 = (int32_t)ctx->f16.u32l;
            goto L_800BC1B8;
    }
    goto skip_0;
    // 0x800BC16C: mfc1        $v0, $f16
    ctx->r2 = (int32_t)ctx->f16.u32l;
    skip_0:
    // 0x800BC170: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
    // 0x800BC174: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
    // 0x800BC178: sub.s       $f16, $f10, $f16
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f16.fl = ctx->f10.fl - ctx->f16.fl;
    // 0x800BC17C: ctc1        $v0, $FpcCsr
    set_cop1_cs(ctx->r2);
    // 0x800BC180: nop

    // 0x800BC184: cvt.w.s     $f16, $f16
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 16);
    ctx->f16.u32l = CVT_W_S(ctx->f16.fl);
    // 0x800BC188: cfc1        $v0, $FpcCsr
    ctx->r2 = get_cop1_cs();
    // 0x800BC18C: nop

    // 0x800BC190: andi        $v0, $v0, 0x78
    ctx->r2 = ctx->r2 & 0X78;
    // 0x800BC194: bne         $v0, $zero, L_800BC1AC
    if (ctx->r2 != 0) {
        // 0x800BC198: nop
    
            goto L_800BC1AC;
    }
    // 0x800BC198: nop

    // 0x800BC19C: mfc1        $v0, $f16
    ctx->r2 = (int32_t)ctx->f16.u32l;
    // 0x800BC1A0: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x800BC1A4: b           L_800BC1C4
    // 0x800BC1A8: or          $v0, $v0, $at
    ctx->r2 = ctx->r2 | ctx->r1;
        goto L_800BC1C4;
    // 0x800BC1A8: or          $v0, $v0, $at
    ctx->r2 = ctx->r2 | ctx->r1;
L_800BC1AC:
    // 0x800BC1AC: b           L_800BC1C4
    // 0x800BC1B0: addiu       $v0, $zero, -0x1
    ctx->r2 = ADD32(0, -0X1);
        goto L_800BC1C4;
    // 0x800BC1B0: addiu       $v0, $zero, -0x1
    ctx->r2 = ADD32(0, -0X1);
    // 0x800BC1B4: mfc1        $v0, $f16
    ctx->r2 = (int32_t)ctx->f16.u32l;
L_800BC1B8:
    // 0x800BC1B8: nop

    // 0x800BC1BC: bltz        $v0, L_800BC1AC
    if (SIGNED(ctx->r2) < 0) {
        // 0x800BC1C0: nop
    
            goto L_800BC1AC;
    }
    // 0x800BC1C0: nop

L_800BC1C4:
    // 0x800BC1C4: ctc1        $t6, $FpcCsr
    set_cop1_cs(ctx->r14);
    // 0x800BC1C8: sltiu       $at, $v0, 0x80
    ctx->r1 = ctx->r2 < 0X80 ? 1 : 0;
    // 0x800BC1CC: bnel        $at, $zero, L_800BC1DC
    if (ctx->r1 != 0) {
        // 0x800BC1D0: lui         $at, 0x3F80
        ctx->r1 = S32(0X3F80 << 16);
            goto L_800BC1DC;
    }
    goto skip_1;
    // 0x800BC1D0: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    skip_1:
    // 0x800BC1D4: addiu       $v0, $zero, 0x7F
    ctx->r2 = ADD32(0, 0X7F);
    // 0x800BC1D8: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
L_800BC1DC:
    // 0x800BC1DC: mtc1        $at, $f12
    ctx->f12.u32l = ctx->r1;
    // 0x800BC1E0: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x800BC1E4: sll         $t7, $v0, 2
    ctx->r15 = S32(ctx->r2 << 2);
    // 0x800BC1E8: addu        $at, $at, $t7
    ctx->r1 = ADD32(ctx->r1, ctx->r15);
    // 0x800BC1EC: lwc1        $f18, -0x341C($at)
    ctx->f18.u32l = MEM_W(ctx->r1, -0X341C);
    // 0x800BC1F0: lwc1        $f6, 0xC($a0)
    ctx->f6.u32l = MEM_W(ctx->r4, 0XC);
    // 0x800BC1F4: sub.s       $f4, $f18, $f12
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f4.fl = ctx->f18.fl - ctx->f12.fl;
    // 0x800BC1F8: mul.s       $f8, $f4, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = MUL_S(ctx->f4.fl, ctx->f6.fl);
    // 0x800BC1FC: add.s       $f2, $f8, $f12
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f2.fl = ctx->f8.fl + ctx->f12.fl;
    // 0x800BC200: jr          $ra
    // 0x800BC204: mov.s       $f0, $f2
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    ctx->f0.fl = ctx->f2.fl;
    return;
    // 0x800BC204: mov.s       $f0, $f2
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    ctx->f0.fl = ctx->f2.fl;
;}
RECOMP_FUNC void Audio_GetVibratoPitchChange(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800BC208: lwc1        $f4, 0x10($a0)
    ctx->f4.u32l = MEM_W(ctx->r4, 0X10);
    // 0x800BC20C: lw          $t6, 0x4($a0)
    ctx->r14 = MEM_W(ctx->r4, 0X4);
    // 0x800BC210: lw          $t2, 0x8($a0)
    ctx->r10 = MEM_W(ctx->r4, 0X8);
    // 0x800BC214: trunc.w.s   $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.u32l = TRUNC_W_S(ctx->f4.fl);
    // 0x800BC218: mfc1        $t8, $f6
    ctx->r24 = (int32_t)ctx->f6.u32l;
    // 0x800BC21C: nop

    // 0x800BC220: addu        $t9, $t6, $t8
    ctx->r25 = ADD32(ctx->r14, ctx->r24);
    // 0x800BC224: srl         $t0, $t9, 10
    ctx->r8 = S32(U32(ctx->r25) >> 10);
    // 0x800BC228: andi        $t1, $t0, 0x3F
    ctx->r9 = ctx->r8 & 0X3F;
    // 0x800BC22C: sll         $t3, $t1, 1
    ctx->r11 = S32(ctx->r9 << 1);
    // 0x800BC230: sw          $t9, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r25;
    // 0x800BC234: addu        $t4, $t2, $t3
    ctx->r12 = ADD32(ctx->r10, ctx->r11);
    // 0x800BC238: lh          $v0, 0x0($t4)
    ctx->r2 = MEM_H(ctx->r12, 0X0);
    // 0x800BC23C: sra         $t5, $v0, 8
    ctx->r13 = S32(SIGNED(ctx->r2) >> 8);
    // 0x800BC240: sll         $t7, $t5, 16
    ctx->r15 = S32(ctx->r13 << 16);
    // 0x800BC244: jr          $ra
    // 0x800BC248: sra         $v0, $t7, 16
    ctx->r2 = S32(SIGNED(ctx->r15) >> 16);
    return;
    // 0x800BC248: sra         $v0, $t7, 16
    ctx->r2 = S32(SIGNED(ctx->r15) >> 16);
;}
RECOMP_FUNC void Audio_GetVibratoFreqScale(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800BC24C: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800BC250: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800BC254: lhu         $v0, 0x1A($a0)
    ctx->r2 = MEM_HU(ctx->r4, 0X1A);
    // 0x800BC258: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x800BC25C: beq         $v0, $zero, L_800BC270
    if (ctx->r2 == 0) {
        // 0x800BC260: addiu       $t6, $v0, -0x1
        ctx->r14 = ADD32(ctx->r2, -0X1);
            goto L_800BC270;
    }
    // 0x800BC260: addiu       $t6, $v0, -0x1
    ctx->r14 = ADD32(ctx->r2, -0X1);
    // 0x800BC264: mtc1        $at, $f0
    ctx->f0.u32l = ctx->r1;
    // 0x800BC268: b           L_800BC434
    // 0x800BC26C: sh          $t6, 0x1A($a0)
    MEM_H(0X1A, ctx->r4) = ctx->r14;
        goto L_800BC434;
    // 0x800BC26C: sh          $t6, 0x1A($a0)
    MEM_H(0X1A, ctx->r4) = ctx->r14;
L_800BC270:
    // 0x800BC270: lhu         $v0, 0x18($a0)
    ctx->r2 = MEM_HU(ctx->r4, 0X18);
    // 0x800BC274: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x800BC278: beql        $v0, $zero, L_800BC2EC
    if (ctx->r2 == 0) {
        // 0x800BC27C: lwc1        $f10, 0xC($a0)
        ctx->f10.u32l = MEM_W(ctx->r4, 0XC);
            goto L_800BC2EC;
    }
    goto skip_0;
    // 0x800BC27C: lwc1        $f10, 0xC($a0)
    ctx->f10.u32l = MEM_W(ctx->r4, 0XC);
    skip_0:
    // 0x800BC280: bne         $v0, $at, L_800BC2A8
    if (ctx->r2 != ctx->r1) {
        // 0x800BC284: or          $v1, $v0, $zero
        ctx->r3 = ctx->r2 | 0;
            goto L_800BC2A8;
    }
    // 0x800BC284: or          $v1, $v0, $zero
    ctx->r3 = ctx->r2 | 0;
    // 0x800BC288: lw          $t7, 0x0($a0)
    ctx->r15 = MEM_W(ctx->r4, 0X0);
    // 0x800BC28C: lhu         $v0, 0x18($a0)
    ctx->r2 = MEM_HU(ctx->r4, 0X18);
    // 0x800BC290: lhu         $t8, 0x12($t7)
    ctx->r24 = MEM_HU(ctx->r15, 0X12);
    // 0x800BC294: mtc1        $t8, $f4
    ctx->f4.u32l = ctx->r24;
    // 0x800BC298: nop

    // 0x800BC29C: cvt.s.w     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
    // 0x800BC2A0: b           L_800BC2D8
    // 0x800BC2A4: swc1        $f6, 0xC($a0)
    MEM_W(0XC, ctx->r4) = ctx->f6.u32l;
        goto L_800BC2D8;
    // 0x800BC2A4: swc1        $f6, 0xC($a0)
    MEM_W(0XC, ctx->r4) = ctx->f6.u32l;
L_800BC2A8:
    // 0x800BC2A8: lw          $t9, 0x0($a0)
    ctx->r25 = MEM_W(ctx->r4, 0X0);
    // 0x800BC2AC: mtc1        $v1, $f18
    ctx->f18.u32l = ctx->r3;
    // 0x800BC2B0: lwc1        $f0, 0xC($a0)
    ctx->f0.u32l = MEM_W(ctx->r4, 0XC);
    // 0x800BC2B4: lhu         $t0, 0x12($t9)
    ctx->r8 = MEM_HU(ctx->r25, 0X12);
    // 0x800BC2B8: cvt.s.w     $f4, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    ctx->f4.fl = CVT_S_W(ctx->f18.u32l);
    // 0x800BC2BC: mtc1        $t0, $f8
    ctx->f8.u32l = ctx->r8;
    // 0x800BC2C0: nop

    // 0x800BC2C4: cvt.s.w     $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.fl = CVT_S_W(ctx->f8.u32l);
    // 0x800BC2C8: sub.s       $f16, $f10, $f0
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f16.fl = ctx->f10.fl - ctx->f0.fl;
    // 0x800BC2CC: div.s       $f6, $f16, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = DIV_S(ctx->f16.fl, ctx->f4.fl);
    // 0x800BC2D0: add.s       $f8, $f0, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = ctx->f0.fl + ctx->f6.fl;
    // 0x800BC2D4: swc1        $f8, 0xC($a0)
    MEM_W(0XC, ctx->r4) = ctx->f8.u32l;
L_800BC2D8:
    // 0x800BC2D8: addiu       $t1, $v0, -0x1
    ctx->r9 = ADD32(ctx->r2, -0X1);
    // 0x800BC2DC: sh          $t1, 0x18($a0)
    MEM_H(0X18, ctx->r4) = ctx->r9;
    // 0x800BC2E0: b           L_800BC328
    // 0x800BC2E4: lw          $v1, 0x0($a0)
    ctx->r3 = MEM_W(ctx->r4, 0X0);
        goto L_800BC328;
    // 0x800BC2E4: lw          $v1, 0x0($a0)
    ctx->r3 = MEM_W(ctx->r4, 0X0);
    // 0x800BC2E8: lwc1        $f10, 0xC($a0)
    ctx->f10.u32l = MEM_W(ctx->r4, 0XC);
L_800BC2EC:
    // 0x800BC2EC: lw          $v1, 0x0($a0)
    ctx->r3 = MEM_W(ctx->r4, 0X0);
    // 0x800BC2F0: trunc.w.s   $f18, $f10
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 10);
    ctx->f18.u32l = TRUNC_W_S(ctx->f10.fl);
    // 0x800BC2F4: lhu         $t4, 0x12($v1)
    ctx->r12 = MEM_HU(ctx->r3, 0X12);
    // 0x800BC2F8: mfc1        $t3, $f18
    ctx->r11 = (int32_t)ctx->f18.u32l;
    // 0x800BC2FC: nop

    // 0x800BC300: beql        $t3, $t4, L_800BC32C
    if (ctx->r11 == ctx->r12) {
        // 0x800BC304: lhu         $v0, 0x16($a0)
        ctx->r2 = MEM_HU(ctx->r4, 0X16);
            goto L_800BC32C;
    }
    goto skip_1;
    // 0x800BC304: lhu         $v0, 0x16($a0)
    ctx->r2 = MEM_HU(ctx->r4, 0X16);
    skip_1:
    // 0x800BC308: lhu         $v0, 0x16($v1)
    ctx->r2 = MEM_HU(ctx->r3, 0X16);
    // 0x800BC30C: bne         $v0, $zero, L_800BC328
    if (ctx->r2 != 0) {
        // 0x800BC310: sh          $v0, 0x18($a0)
        MEM_H(0X18, ctx->r4) = ctx->r2;
            goto L_800BC328;
    }
    // 0x800BC310: sh          $v0, 0x18($a0)
    MEM_H(0X18, ctx->r4) = ctx->r2;
    // 0x800BC314: lhu         $t5, 0x12($v1)
    ctx->r13 = MEM_HU(ctx->r3, 0X12);
    // 0x800BC318: mtc1        $t5, $f16
    ctx->f16.u32l = ctx->r13;
    // 0x800BC31C: nop

    // 0x800BC320: cvt.s.w     $f4, $f16
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 16);
    ctx->f4.fl = CVT_S_W(ctx->f16.u32l);
    // 0x800BC324: swc1        $f4, 0xC($a0)
    MEM_W(0XC, ctx->r4) = ctx->f4.u32l;
L_800BC328:
    // 0x800BC328: lhu         $v0, 0x16($a0)
    ctx->r2 = MEM_HU(ctx->r4, 0X16);
L_800BC32C:
    // 0x800BC32C: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x800BC330: beql        $v0, $zero, L_800BC394
    if (ctx->r2 == 0) {
        // 0x800BC334: lwc1        $f18, 0x10($a0)
        ctx->f18.u32l = MEM_W(ctx->r4, 0X10);
            goto L_800BC394;
    }
    goto skip_2;
    // 0x800BC334: lwc1        $f18, 0x10($a0)
    ctx->f18.u32l = MEM_W(ctx->r4, 0X10);
    skip_2:
    // 0x800BC338: bne         $v0, $at, L_800BC35C
    if (ctx->r2 != ctx->r1) {
        // 0x800BC33C: or          $a1, $v0, $zero
        ctx->r5 = ctx->r2 | 0;
            goto L_800BC35C;
    }
    // 0x800BC33C: or          $a1, $v0, $zero
    ctx->r5 = ctx->r2 | 0;
    // 0x800BC340: lhu         $t6, 0x10($v1)
    ctx->r14 = MEM_HU(ctx->r3, 0X10);
    // 0x800BC344: lhu         $v0, 0x16($a0)
    ctx->r2 = MEM_HU(ctx->r4, 0X16);
    // 0x800BC348: mtc1        $t6, $f6
    ctx->f6.u32l = ctx->r14;
    // 0x800BC34C: nop

    // 0x800BC350: cvt.s.w     $f8, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    ctx->f8.fl = CVT_S_W(ctx->f6.u32l);
    // 0x800BC354: b           L_800BC384
    // 0x800BC358: swc1        $f8, 0x10($a0)
    MEM_W(0X10, ctx->r4) = ctx->f8.u32l;
        goto L_800BC384;
    // 0x800BC358: swc1        $f8, 0x10($a0)
    MEM_W(0X10, ctx->r4) = ctx->f8.u32l;
L_800BC35C:
    // 0x800BC35C: lhu         $t7, 0x10($v1)
    ctx->r15 = MEM_HU(ctx->r3, 0X10);
    // 0x800BC360: mtc1        $a1, $f4
    ctx->f4.u32l = ctx->r5;
    // 0x800BC364: lwc1        $f0, 0x10($a0)
    ctx->f0.u32l = MEM_W(ctx->r4, 0X10);
    // 0x800BC368: mtc1        $t7, $f10
    ctx->f10.u32l = ctx->r15;
    // 0x800BC36C: cvt.s.w     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
    // 0x800BC370: cvt.s.w     $f18, $f10
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 10);
    ctx->f18.fl = CVT_S_W(ctx->f10.u32l);
    // 0x800BC374: sub.s       $f16, $f18, $f0
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f16.fl = ctx->f18.fl - ctx->f0.fl;
    // 0x800BC378: div.s       $f8, $f16, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = DIV_S(ctx->f16.fl, ctx->f6.fl);
    // 0x800BC37C: add.s       $f10, $f0, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = ctx->f0.fl + ctx->f8.fl;
    // 0x800BC380: swc1        $f10, 0x10($a0)
    MEM_W(0X10, ctx->r4) = ctx->f10.u32l;
L_800BC384:
    // 0x800BC384: addiu       $t8, $v0, -0x1
    ctx->r24 = ADD32(ctx->r2, -0X1);
    // 0x800BC388: b           L_800BC3CC
    // 0x800BC38C: sh          $t8, 0x16($a0)
    MEM_H(0X16, ctx->r4) = ctx->r24;
        goto L_800BC3CC;
    // 0x800BC38C: sh          $t8, 0x16($a0)
    MEM_H(0X16, ctx->r4) = ctx->r24;
    // 0x800BC390: lwc1        $f18, 0x10($a0)
    ctx->f18.u32l = MEM_W(ctx->r4, 0X10);
L_800BC394:
    // 0x800BC394: lhu         $t1, 0x10($v1)
    ctx->r9 = MEM_HU(ctx->r3, 0X10);
    // 0x800BC398: trunc.w.s   $f4, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    ctx->f4.u32l = TRUNC_W_S(ctx->f18.fl);
    // 0x800BC39C: mfc1        $t0, $f4
    ctx->r8 = (int32_t)ctx->f4.u32l;
    // 0x800BC3A0: nop

    // 0x800BC3A4: beql        $t0, $t1, L_800BC3D0
    if (ctx->r8 == ctx->r9) {
        // 0x800BC3A8: mtc1        $zero, $f8
        ctx->f8.u32l = 0;
            goto L_800BC3D0;
    }
    goto skip_3;
    // 0x800BC3A8: mtc1        $zero, $f8
    ctx->f8.u32l = 0;
    skip_3:
    // 0x800BC3AC: lhu         $v0, 0x14($v1)
    ctx->r2 = MEM_HU(ctx->r3, 0X14);
    // 0x800BC3B0: bne         $v0, $zero, L_800BC3CC
    if (ctx->r2 != 0) {
        // 0x800BC3B4: sh          $v0, 0x16($a0)
        MEM_H(0X16, ctx->r4) = ctx->r2;
            goto L_800BC3CC;
    }
    // 0x800BC3B4: sh          $v0, 0x16($a0)
    MEM_H(0X16, ctx->r4) = ctx->r2;
    // 0x800BC3B8: lhu         $t2, 0x10($v1)
    ctx->r10 = MEM_HU(ctx->r3, 0X10);
    // 0x800BC3BC: mtc1        $t2, $f16
    ctx->f16.u32l = ctx->r10;
    // 0x800BC3C0: nop

    // 0x800BC3C4: cvt.s.w     $f6, $f16
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 16);
    ctx->f6.fl = CVT_S_W(ctx->f16.u32l);
    // 0x800BC3C8: swc1        $f6, 0x10($a0)
    MEM_W(0X10, ctx->r4) = ctx->f6.u32l;
L_800BC3CC:
    // 0x800BC3CC: mtc1        $zero, $f8
    ctx->f8.u32l = 0;
L_800BC3D0:
    // 0x800BC3D0: lwc1        $f10, 0xC($a0)
    ctx->f10.u32l = MEM_W(ctx->r4, 0XC);
    // 0x800BC3D4: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x800BC3D8: c.eq.s      $f8, $f10
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    c1cs = ctx->f8.fl == ctx->f10.fl;
    // 0x800BC3DC: nop

    // 0x800BC3E0: bc1f        L_800BC3F4
    if (!c1cs) {
        // 0x800BC3E4: nop
    
            goto L_800BC3F4;
    }
    // 0x800BC3E4: nop

    // 0x800BC3E8: mtc1        $at, $f0
    ctx->f0.u32l = ctx->r1;
    // 0x800BC3EC: b           L_800BC438
    // 0x800BC3F0: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_800BC438;
    // 0x800BC3F0: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_800BC3F4:
    // 0x800BC3F4: jal         0x800BC208
    // 0x800BC3F8: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    Audio_GetVibratoPitchChange(rdram, ctx);
        goto after_0;
    // 0x800BC3F8: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    after_0:
    // 0x800BC3FC: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x800BC400: mtc1        $at, $f14
    ctx->f14.u32l = ctx->r1;
    // 0x800BC404: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
    // 0x800BC408: lui         $at, 0x3980
    ctx->r1 = S32(0X3980 << 16);
    // 0x800BC40C: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x800BC410: lwc1        $f18, 0xC($a0)
    ctx->f18.u32l = MEM_W(ctx->r4, 0XC);
    // 0x800BC414: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x800BC418: sll         $t3, $v0, 2
    ctx->r11 = S32(ctx->r2 << 2);
    // 0x800BC41C: addu        $at, $at, $t3
    ctx->r1 = ADD32(ctx->r1, ctx->r11);
    // 0x800BC420: mul.s       $f2, $f18, $f4
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f2.fl = MUL_S(ctx->f18.fl, ctx->f4.fl);
    // 0x800BC424: lwc1        $f16, -0x341C($at)
    ctx->f16.u32l = MEM_W(ctx->r1, -0X341C);
    // 0x800BC428: sub.s       $f6, $f16, $f14
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f6.fl = ctx->f16.fl - ctx->f14.fl;
    // 0x800BC42C: mul.s       $f8, $f6, $f2
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f8.fl = MUL_S(ctx->f6.fl, ctx->f2.fl);
    // 0x800BC430: add.s       $f0, $f8, $f14
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f0.fl = ctx->f8.fl + ctx->f14.fl;
L_800BC434:
    // 0x800BC434: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_800BC438:
    // 0x800BC438: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800BC43C: jr          $ra
    // 0x800BC440: nop

    return;
    // 0x800BC440: nop

;}
RECOMP_FUNC void Audio_NoteVibratoUpdate(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800BC444: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800BC448: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800BC44C: lbu         $t6, 0x7C($a0)
    ctx->r14 = MEM_BU(ctx->r4, 0X7C);
    // 0x800BC450: or          $a1, $a0, $zero
    ctx->r5 = ctx->r4 | 0;
    // 0x800BC454: addiu       $a0, $a0, 0x7C
    ctx->r4 = ADD32(ctx->r4, 0X7C);
    // 0x800BC458: beql        $t6, $zero, L_800BC474
    if (ctx->r14 == 0) {
        // 0x800BC45C: lbu         $t7, 0xA0($a1)
        ctx->r15 = MEM_BU(ctx->r5, 0XA0);
            goto L_800BC474;
    }
    goto skip_0;
    // 0x800BC45C: lbu         $t7, 0xA0($a1)
    ctx->r15 = MEM_BU(ctx->r5, 0XA0);
    skip_0:
    // 0x800BC460: jal         0x800BC134
    // 0x800BC464: sw          $a1, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r5;
    Audio_GetPortamentoFreqScale(rdram, ctx);
        goto after_0;
    // 0x800BC464: sw          $a1, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r5;
    after_0:
    // 0x800BC468: lw          $a1, 0x18($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X18);
    // 0x800BC46C: swc1        $f0, 0x38($a1)
    MEM_W(0X38, ctx->r5) = ctx->f0.u32l;
    // 0x800BC470: lbu         $t7, 0xA0($a1)
    ctx->r15 = MEM_BU(ctx->r5, 0XA0);
L_800BC474:
    // 0x800BC474: beql        $t7, $zero, L_800BC4A4
    if (ctx->r15 == 0) {
        // 0x800BC478: lw          $ra, 0x14($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X14);
            goto L_800BC4A4;
    }
    goto skip_1;
    // 0x800BC478: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    skip_1:
    // 0x800BC47C: lw          $t8, 0x44($a1)
    ctx->r24 = MEM_W(ctx->r5, 0X44);
    // 0x800BC480: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x800BC484: addiu       $a0, $a1, 0x8C
    ctx->r4 = ADD32(ctx->r5, 0X8C);
    // 0x800BC488: beql        $t8, $at, L_800BC4A4
    if (ctx->r24 == ctx->r1) {
        // 0x800BC48C: lw          $ra, 0x14($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X14);
            goto L_800BC4A4;
    }
    goto skip_2;
    // 0x800BC48C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    skip_2:
    // 0x800BC490: jal         0x800BC24C
    // 0x800BC494: sw          $a1, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r5;
    Audio_GetVibratoFreqScale(rdram, ctx);
        goto after_1;
    // 0x800BC494: sw          $a1, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r5;
    after_1:
    // 0x800BC498: lw          $a1, 0x18($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X18);
    // 0x800BC49C: swc1        $f0, 0x3C($a1)
    MEM_W(0X3C, ctx->r5) = ctx->f0.u32l;
    // 0x800BC4A0: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_800BC4A4:
    // 0x800BC4A4: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800BC4A8: jr          $ra
    // 0x800BC4AC: nop

    return;
    // 0x800BC4AC: nop

;}
RECOMP_FUNC void Audio_NoteVibratoInit(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800BC4B0: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x800BC4B4: mtc1        $at, $f0
    ctx->f0.u32l = ctx->r1;
    // 0x800BC4B8: addiu       $t6, $zero, 0x1
    ctx->r14 = ADD32(0, 0X1);
    // 0x800BC4BC: sb          $t6, 0xA0($a0)
    MEM_B(0XA0, ctx->r4) = ctx->r14;
    // 0x800BC4C0: sw          $zero, 0x90($a0)
    MEM_W(0X90, ctx->r4) = 0;
    // 0x800BC4C4: lui         $t7, 0x800F
    ctx->r15 = S32(0X800F << 16);
    // 0x800BC4C8: swc1        $f0, 0x3C($a0)
    MEM_W(0X3C, ctx->r4) = ctx->f0.u32l;
    // 0x800BC4CC: swc1        $f0, 0x38($a0)
    MEM_W(0X38, ctx->r4) = ctx->f0.u32l;
    // 0x800BC4D0: lw          $t7, -0x23C8($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X23C8);
    // 0x800BC4D4: lw          $t8, 0x44($a0)
    ctx->r24 = MEM_W(ctx->r4, 0X44);
    // 0x800BC4D8: addiu       $v1, $a0, 0x8C
    ctx->r3 = ADD32(ctx->r4, 0X8C);
    // 0x800BC4DC: sw          $t7, 0x94($a0)
    MEM_W(0X94, ctx->r4) = ctx->r15;
    // 0x800BC4E0: lw          $t9, 0x4C($t8)
    ctx->r25 = MEM_W(ctx->r24, 0X4C);
    // 0x800BC4E4: sw          $t9, 0x8C($a0)
    MEM_W(0X8C, ctx->r4) = ctx->r25;
    // 0x800BC4E8: lhu         $v0, 0x16($t9)
    ctx->r2 = MEM_HU(ctx->r25, 0X16);
    // 0x800BC4EC: bne         $v0, $zero, L_800BC514
    if (ctx->r2 != 0) {
        // 0x800BC4F0: sh          $v0, 0xA4($a0)
        MEM_H(0XA4, ctx->r4) = ctx->r2;
            goto L_800BC514;
    }
    // 0x800BC4F0: sh          $v0, 0xA4($a0)
    MEM_H(0XA4, ctx->r4) = ctx->r2;
    // 0x800BC4F4: addiu       $v1, $a0, 0x8C
    ctx->r3 = ADD32(ctx->r4, 0X8C);
    // 0x800BC4F8: lw          $a1, 0x0($v1)
    ctx->r5 = MEM_W(ctx->r3, 0X0);
    // 0x800BC4FC: lhu         $t1, 0x12($a1)
    ctx->r9 = MEM_HU(ctx->r5, 0X12);
    // 0x800BC500: mtc1        $t1, $f4
    ctx->f4.u32l = ctx->r9;
    // 0x800BC504: nop

    // 0x800BC508: cvt.s.w     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
    // 0x800BC50C: b           L_800BC52C
    // 0x800BC510: swc1        $f6, 0xC($v1)
    MEM_W(0XC, ctx->r3) = ctx->f6.u32l;
        goto L_800BC52C;
    // 0x800BC510: swc1        $f6, 0xC($v1)
    MEM_W(0XC, ctx->r3) = ctx->f6.u32l;
L_800BC514:
    // 0x800BC514: lw          $a1, 0x0($v1)
    ctx->r5 = MEM_W(ctx->r3, 0X0);
    // 0x800BC518: lhu         $t2, 0xE($a1)
    ctx->r10 = MEM_HU(ctx->r5, 0XE);
    // 0x800BC51C: mtc1        $t2, $f8
    ctx->f8.u32l = ctx->r10;
    // 0x800BC520: nop

    // 0x800BC524: cvt.s.w     $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.fl = CVT_S_W(ctx->f8.u32l);
    // 0x800BC528: swc1        $f10, 0xC($v1)
    MEM_W(0XC, ctx->r3) = ctx->f10.u32l;
L_800BC52C:
    // 0x800BC52C: lhu         $v0, 0x14($a1)
    ctx->r2 = MEM_HU(ctx->r5, 0X14);
    // 0x800BC530: bne         $v0, $zero, L_800BC550
    if (ctx->r2 != 0) {
        // 0x800BC534: sh          $v0, 0x16($v1)
        MEM_H(0X16, ctx->r3) = ctx->r2;
            goto L_800BC550;
    }
    // 0x800BC534: sh          $v0, 0x16($v1)
    MEM_H(0X16, ctx->r3) = ctx->r2;
    // 0x800BC538: lhu         $t3, 0x10($a1)
    ctx->r11 = MEM_HU(ctx->r5, 0X10);
    // 0x800BC53C: mtc1        $t3, $f16
    ctx->f16.u32l = ctx->r11;
    // 0x800BC540: nop

    // 0x800BC544: cvt.s.w     $f18, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    ctx->f18.fl = CVT_S_W(ctx->f16.u32l);
    // 0x800BC548: b           L_800BC564
    // 0x800BC54C: swc1        $f18, 0x10($v1)
    MEM_W(0X10, ctx->r3) = ctx->f18.u32l;
        goto L_800BC564;
    // 0x800BC54C: swc1        $f18, 0x10($v1)
    MEM_W(0X10, ctx->r3) = ctx->f18.u32l;
L_800BC550:
    // 0x800BC550: lhu         $t4, 0xC($a1)
    ctx->r12 = MEM_HU(ctx->r5, 0XC);
    // 0x800BC554: mtc1        $t4, $f4
    ctx->f4.u32l = ctx->r12;
    // 0x800BC558: nop

    // 0x800BC55C: cvt.s.w     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
    // 0x800BC560: swc1        $f6, 0x10($v1)
    MEM_W(0X10, ctx->r3) = ctx->f6.u32l;
L_800BC564:
    // 0x800BC564: lhu         $t5, 0x18($a1)
    ctx->r13 = MEM_HU(ctx->r5, 0X18);
    // 0x800BC568: addiu       $v0, $a0, 0x30
    ctx->r2 = ADD32(ctx->r4, 0X30);
    // 0x800BC56C: sh          $t5, 0x1A($v1)
    MEM_H(0X1A, ctx->r3) = ctx->r13;
    // 0x800BC570: lw          $t6, 0x14($v0)
    ctx->r14 = MEM_W(ctx->r2, 0X14);
    // 0x800BC574: lw          $at, 0x8($t6)
    ctx->r1 = MEM_W(ctx->r14, 0X8);
    // 0x800BC578: sw          $at, 0x4C($v0)
    MEM_W(0X4C, ctx->r2) = ctx->r1;
    // 0x800BC57C: lw          $t8, 0xC($t6)
    ctx->r24 = MEM_W(ctx->r14, 0XC);
    // 0x800BC580: sw          $t8, 0x50($v0)
    MEM_W(0X50, ctx->r2) = ctx->r24;
    // 0x800BC584: lw          $at, 0x10($t6)
    ctx->r1 = MEM_W(ctx->r14, 0X10);
    // 0x800BC588: sw          $at, 0x54($v0)
    MEM_W(0X54, ctx->r2) = ctx->r1;
    // 0x800BC58C: lw          $t8, 0x14($t6)
    ctx->r24 = MEM_W(ctx->r14, 0X14);
    // 0x800BC590: jr          $ra
    // 0x800BC594: sw          $t8, 0x58($v0)
    MEM_W(0X58, ctx->r2) = ctx->r24;
    return;
    // 0x800BC594: sw          $t8, 0x58($v0)
    MEM_W(0X58, ctx->r2) = ctx->r24;
;}
RECOMP_FUNC void Audio_AdsrInit(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800BC598: sw          $a2, 0x8($sp)
    MEM_W(0X8, ctx->r29) = ctx->r6;
    // 0x800BC59C: mtc1        $zero, $f4
    ctx->f4.u32l = 0;
    // 0x800BC5A0: sb          $zero, 0x0($a0)
    MEM_B(0X0, ctx->r4) = 0;
    // 0x800BC5A4: sb          $zero, 0x1($a0)
    MEM_B(0X1, ctx->r4) = 0;
    // 0x800BC5A8: sh          $zero, 0x4($a0)
    MEM_H(0X4, ctx->r4) = 0;
    // 0x800BC5AC: sw          $a1, 0x20($a0)
    MEM_W(0X20, ctx->r4) = ctx->r5;
    // 0x800BC5B0: jr          $ra
    // 0x800BC5B4: swc1        $f4, 0x14($a0)
    MEM_W(0X14, ctx->r4) = ctx->f4.u32l;
    return;
    // 0x800BC5B4: swc1        $f4, 0x14($a0)
    MEM_W(0X14, ctx->r4) = ctx->f4.u32l;
;}
RECOMP_FUNC void Audio_AdsrUpdate(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800BC5B8: lbu         $v1, 0x1($a0)
    ctx->r3 = MEM_BU(ctx->r4, 0X1);
    // 0x800BC5BC: lbu         $v0, 0x0($a0)
    ctx->r2 = MEM_BU(ctx->r4, 0X0);
    // 0x800BC5C0: sltiu       $at, $v1, 0x9
    ctx->r1 = ctx->r3 < 0X9 ? 1 : 0;
    // 0x800BC5C4: beq         $at, $zero, L_800BC7F8
    if (ctx->r1 == 0) {
        // 0x800BC5C8: or          $a1, $v1, $zero
        ctx->r5 = ctx->r3 | 0;
            goto L_800BC7F8;
    }
    // 0x800BC5C8: or          $a1, $v1, $zero
    ctx->r5 = ctx->r3 | 0;
    // 0x800BC5CC: sll         $t6, $v1, 2
    ctx->r14 = S32(ctx->r3 << 2);
    // 0x800BC5D0: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x800BC5D4: addu        $at, $at, $t6
    gpr jr_addend_800BC5DC = ctx->r14;
    ctx->r1 = ADD32(ctx->r1, ctx->r14);
    // 0x800BC5D8: lw          $t6, -0x4370($at)
    ctx->r14 = ADD32(ctx->r1, -0X4370);
    // 0x800BC5DC: jr          $t6
    // 0x800BC5E0: nop

    switch (jr_addend_800BC5DC >> 2) {
        case 0: goto L_800BC5E4; break;
        case 1: goto L_800BC5F0; break;
        case 2: goto L_800BC604; break;
        case 3: goto L_800BC610; break;
        case 4: goto L_800BC728; break;
        case 5: goto L_800BC7F8; break;
        case 6: goto L_800BC758; break;
        case 7: goto L_800BC758; break;
        case 8: goto L_800BC7D8; break;
        default: switch_error(__func__, 0x800BC5DC, 0x800EBC90);
    }
    // 0x800BC5E0: nop

L_800BC5E4:
    // 0x800BC5E4: mtc1        $zero, $f0
    ctx->f0.u32l = 0;
    // 0x800BC5E8: jr          $ra
    // 0x800BC5EC: nop

    return;
    // 0x800BC5EC: nop

L_800BC5F0:
    // 0x800BC5F0: andi        $t7, $v0, 0x40
    ctx->r15 = ctx->r2 & 0X40;
    // 0x800BC5F4: beq         $t7, $zero, L_800BC604
    if (ctx->r15 == 0) {
        // 0x800BC5F8: addiu       $t8, $zero, 0x5
        ctx->r24 = ADD32(0, 0X5);
            goto L_800BC604;
    }
    // 0x800BC5F8: addiu       $t8, $zero, 0x5
    ctx->r24 = ADD32(0, 0X5);
    // 0x800BC5FC: b           L_800BC7F8
    // 0x800BC600: sb          $t8, 0x1($a0)
    MEM_B(0X1, ctx->r4) = ctx->r24;
        goto L_800BC7F8;
    // 0x800BC600: sb          $t8, 0x1($a0)
    MEM_B(0X1, ctx->r4) = ctx->r24;
L_800BC604:
    // 0x800BC604: addiu       $t9, $zero, 0x3
    ctx->r25 = ADD32(0, 0X3);
    // 0x800BC608: sh          $zero, 0x2($a0)
    MEM_H(0X2, ctx->r4) = 0;
    // 0x800BC60C: sb          $t9, 0x1($a0)
    MEM_B(0X1, ctx->r4) = ctx->r25;
L_800BC610:
    // 0x800BC610: lh          $t1, 0x2($a0)
    ctx->r9 = MEM_H(ctx->r4, 0X2);
    // 0x800BC614: lw          $t0, 0x20($a0)
    ctx->r8 = MEM_W(ctx->r4, 0X20);
    // 0x800BC618: addiu       $at, $zero, -0x3
    ctx->r1 = ADD32(0, -0X3);
    // 0x800BC61C: sll         $t2, $t1, 2
    ctx->r10 = S32(ctx->r9 << 2);
    // 0x800BC620: addu        $v1, $t0, $t2
    ctx->r3 = ADD32(ctx->r8, ctx->r10);
    // 0x800BC624: lh          $t3, 0x0($v1)
    ctx->r11 = MEM_H(ctx->r3, 0X0);
    // 0x800BC628: addiu       $t6, $zero, 0x1
    ctx->r14 = ADD32(0, 0X1);
    // 0x800BC62C: sh          $t3, 0x4($a0)
    MEM_H(0X4, ctx->r4) = ctx->r11;
    // 0x800BC630: lh          $a2, 0x4($a0)
    ctx->r6 = MEM_H(ctx->r4, 0X4);
    // 0x800BC634: beq         $a2, $at, L_800BC670
    if (ctx->r6 == ctx->r1) {
        // 0x800BC638: addiu       $at, $zero, -0x2
        ctx->r1 = ADD32(0, -0X2);
            goto L_800BC670;
    }
    // 0x800BC638: addiu       $at, $zero, -0x2
    ctx->r1 = ADD32(0, -0X2);
    // 0x800BC63C: beq         $a2, $at, L_800BC664
    if (ctx->r6 == ctx->r1) {
        // 0x800BC640: addiu       $at, $zero, -0x1
        ctx->r1 = ADD32(0, -0X1);
            goto L_800BC664;
    }
    // 0x800BC640: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x800BC644: beq         $a2, $at, L_800BC65C
    if (ctx->r6 == ctx->r1) {
        // 0x800BC648: addiu       $t4, $zero, 0x5
        ctx->r12 = ADD32(0, 0X5);
            goto L_800BC65C;
    }
    // 0x800BC648: addiu       $t4, $zero, 0x5
    ctx->r12 = ADD32(0, 0X5);
    // 0x800BC64C: bne         $a2, $zero, L_800BC678
    if (ctx->r6 != 0) {
        // 0x800BC650: slti        $at, $a2, 0x4
        ctx->r1 = SIGNED(ctx->r6) < 0X4 ? 1 : 0;
            goto L_800BC678;
    }
    // 0x800BC650: slti        $at, $a2, 0x4
    ctx->r1 = SIGNED(ctx->r6) < 0X4 ? 1 : 0;
    // 0x800BC654: b           L_800BC718
    // 0x800BC658: sb          $zero, 0x1($a0)
    MEM_B(0X1, ctx->r4) = 0;
        goto L_800BC718;
    // 0x800BC658: sb          $zero, 0x1($a0)
    MEM_B(0X1, ctx->r4) = 0;
L_800BC65C:
    // 0x800BC65C: b           L_800BC718
    // 0x800BC660: sb          $t4, 0x1($a0)
    MEM_B(0X1, ctx->r4) = ctx->r12;
        goto L_800BC718;
    // 0x800BC660: sb          $t4, 0x1($a0)
    MEM_B(0X1, ctx->r4) = ctx->r12;
L_800BC664:
    // 0x800BC664: lh          $t5, 0x2($v1)
    ctx->r13 = MEM_H(ctx->r3, 0X2);
    // 0x800BC668: b           L_800BC718
    // 0x800BC66C: sh          $t5, 0x2($a0)
    MEM_H(0X2, ctx->r4) = ctx->r13;
        goto L_800BC718;
    // 0x800BC66C: sh          $t5, 0x2($a0)
    MEM_H(0X2, ctx->r4) = ctx->r13;
L_800BC670:
    // 0x800BC670: b           L_800BC718
    // 0x800BC674: sb          $t6, 0x1($a0)
    MEM_B(0X1, ctx->r4) = ctx->r14;
        goto L_800BC718;
    // 0x800BC674: sb          $t6, 0x1($a0)
    MEM_B(0X1, ctx->r4) = ctx->r14;
L_800BC678:
    // 0x800BC678: bne         $at, $zero, L_800BC6A4
    if (ctx->r1 != 0) {
        // 0x800BC67C: lui         $t7, 0x8004
        ctx->r15 = S32(0X8004 << 16);
            goto L_800BC6A4;
    }
    // 0x800BC67C: lui         $t7, 0x8004
    ctx->r15 = S32(0X8004 << 16);
    // 0x800BC680: lh          $t7, 0x552C($t7)
    ctx->r15 = MEM_H(ctx->r15, 0X552C);
    // 0x800BC684: multu       $a2, $t7
    result = U64(U32(ctx->r6)) * U64(U32(ctx->r15)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x800BC688: mflo        $t8
    ctx->r24 = lo;
    // 0x800BC68C: bgez        $t8, L_800BC69C
    if (SIGNED(ctx->r24) >= 0) {
        // 0x800BC690: sra         $t9, $t8, 2
        ctx->r25 = S32(SIGNED(ctx->r24) >> 2);
            goto L_800BC69C;
    }
    // 0x800BC690: sra         $t9, $t8, 2
    ctx->r25 = S32(SIGNED(ctx->r24) >> 2);
    // 0x800BC694: addiu       $at, $t8, 0x3
    ctx->r1 = ADD32(ctx->r24, 0X3);
    // 0x800BC698: sra         $t9, $at, 2
    ctx->r25 = S32(SIGNED(ctx->r1) >> 2);
L_800BC69C:
    // 0x800BC69C: sh          $t9, 0x4($a0)
    MEM_H(0X4, ctx->r4) = ctx->r25;
    // 0x800BC6A0: lh          $a2, 0x4($a0)
    ctx->r6 = MEM_H(ctx->r4, 0X4);
L_800BC6A4:
    // 0x800BC6A4: bne         $a2, $zero, L_800BC6B4
    if (ctx->r6 != 0) {
        // 0x800BC6A8: addiu       $t1, $zero, 0x1
        ctx->r9 = ADD32(0, 0X1);
            goto L_800BC6B4;
    }
    // 0x800BC6A8: addiu       $t1, $zero, 0x1
    ctx->r9 = ADD32(0, 0X1);
    // 0x800BC6AC: sh          $t1, 0x4($a0)
    MEM_H(0X4, ctx->r4) = ctx->r9;
    // 0x800BC6B0: lh          $a2, 0x4($a0)
    ctx->r6 = MEM_H(ctx->r4, 0X4);
L_800BC6B4:
    // 0x800BC6B4: lh          $v1, 0x2($a0)
    ctx->r3 = MEM_H(ctx->r4, 0X2);
    // 0x800BC6B8: lw          $t0, 0x20($a0)
    ctx->r8 = MEM_W(ctx->r4, 0X20);
    // 0x800BC6BC: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x800BC6C0: sll         $t2, $v1, 2
    ctx->r10 = S32(ctx->r3 << 2);
    // 0x800BC6C4: addu        $t3, $t0, $t2
    ctx->r11 = ADD32(ctx->r8, ctx->r10);
    // 0x800BC6C8: lh          $t4, 0x2($t3)
    ctx->r12 = MEM_H(ctx->r11, 0X2);
    // 0x800BC6CC: lwc1        $f8, -0x434C($at)
    ctx->f8.u32l = MEM_W(ctx->r1, -0X434C);
    // 0x800BC6D0: addiu       $t5, $zero, 0x4
    ctx->r13 = ADD32(0, 0X4);
    // 0x800BC6D4: mtc1        $t4, $f4
    ctx->f4.u32l = ctx->r12;
    // 0x800BC6D8: addiu       $t6, $v1, 0x1
    ctx->r14 = ADD32(ctx->r3, 0X1);
    // 0x800BC6DC: sb          $t5, 0x1($a0)
    MEM_B(0X1, ctx->r4) = ctx->r13;
    // 0x800BC6E0: cvt.s.w     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
    // 0x800BC6E4: lwc1        $f4, 0x14($a0)
    ctx->f4.u32l = MEM_W(ctx->r4, 0X14);
    // 0x800BC6E8: sh          $t6, 0x2($a0)
    MEM_H(0X2, ctx->r4) = ctx->r14;
    // 0x800BC6EC: div.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = DIV_S(ctx->f6.fl, ctx->f8.fl);
    // 0x800BC6F0: mtc1        $a2, $f8
    ctx->f8.u32l = ctx->r6;
    // 0x800BC6F4: swc1        $f10, 0x18($a0)
    MEM_W(0X18, ctx->r4) = ctx->f10.u32l;
    // 0x800BC6F8: lwc1        $f0, 0x18($a0)
    ctx->f0.u32l = MEM_W(ctx->r4, 0X18);
    // 0x800BC6FC: cvt.s.w     $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.fl = CVT_S_W(ctx->f8.u32l);
    // 0x800BC700: mul.s       $f16, $f0, $f0
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f16.fl = MUL_S(ctx->f0.fl, ctx->f0.fl);
    // 0x800BC704: swc1        $f16, 0x18($a0)
    MEM_W(0X18, ctx->r4) = ctx->f16.u32l;
    // 0x800BC708: lwc1        $f18, 0x18($a0)
    ctx->f18.u32l = MEM_W(ctx->r4, 0X18);
    // 0x800BC70C: sub.s       $f6, $f18, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = ctx->f18.fl - ctx->f4.fl;
    // 0x800BC710: div.s       $f16, $f6, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f16.fl = DIV_S(ctx->f6.fl, ctx->f10.fl);
    // 0x800BC714: swc1        $f16, 0xC($a0)
    MEM_W(0XC, ctx->r4) = ctx->f16.u32l;
L_800BC718:
    // 0x800BC718: lbu         $t7, 0x1($a0)
    ctx->r15 = MEM_BU(ctx->r4, 0X1);
    // 0x800BC71C: addiu       $at, $zero, 0x4
    ctx->r1 = ADD32(0, 0X4);
    // 0x800BC720: bnel        $t7, $at, L_800BC7FC
    if (ctx->r15 != ctx->r1) {
        // 0x800BC724: mtc1        $zero, $f12
        ctx->f12.u32l = 0;
            goto L_800BC7FC;
    }
    goto skip_0;
    // 0x800BC724: mtc1        $zero, $f12
    ctx->f12.u32l = 0;
    skip_0:
L_800BC728:
    // 0x800BC728: lh          $t8, 0x4($a0)
    ctx->r24 = MEM_H(ctx->r4, 0X4);
    // 0x800BC72C: lwc1        $f18, 0x14($a0)
    ctx->f18.u32l = MEM_W(ctx->r4, 0X14);
    // 0x800BC730: lwc1        $f4, 0xC($a0)
    ctx->f4.u32l = MEM_W(ctx->r4, 0XC);
    // 0x800BC734: addiu       $t9, $t8, -0x1
    ctx->r25 = ADD32(ctx->r24, -0X1);
    // 0x800BC738: sh          $t9, 0x4($a0)
    MEM_H(0X4, ctx->r4) = ctx->r25;
    // 0x800BC73C: add.s       $f8, $f18, $f4
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f8.fl = ctx->f18.fl + ctx->f4.fl;
    // 0x800BC740: lh          $t1, 0x4($a0)
    ctx->r9 = MEM_H(ctx->r4, 0X4);
    // 0x800BC744: addiu       $t0, $zero, 0x3
    ctx->r8 = ADD32(0, 0X3);
    // 0x800BC748: bgtz        $t1, L_800BC7F8
    if (SIGNED(ctx->r9) > 0) {
        // 0x800BC74C: swc1        $f8, 0x14($a0)
        MEM_W(0X14, ctx->r4) = ctx->f8.u32l;
            goto L_800BC7F8;
    }
    // 0x800BC74C: swc1        $f8, 0x14($a0)
    MEM_W(0X14, ctx->r4) = ctx->f8.u32l;
    // 0x800BC750: b           L_800BC7F8
    // 0x800BC754: sb          $t0, 0x1($a0)
    MEM_B(0X1, ctx->r4) = ctx->r8;
        goto L_800BC7F8;
    // 0x800BC754: sb          $t0, 0x1($a0)
    MEM_B(0X1, ctx->r4) = ctx->r8;
L_800BC758:
    // 0x800BC758: mtc1        $zero, $f12
    ctx->f12.u32l = 0;
    // 0x800BC75C: lwc1        $f0, 0x8($a0)
    ctx->f0.u32l = MEM_W(ctx->r4, 0X8);
    // 0x800BC760: lwc1        $f6, 0x14($a0)
    ctx->f6.u32l = MEM_W(ctx->r4, 0X14);
    // 0x800BC764: lwc1        $f10, 0x10($a0)
    ctx->f10.u32l = MEM_W(ctx->r4, 0X10);
    // 0x800BC768: c.eq.s      $f12, $f0
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 0);
    c1cs = ctx->f12.fl == ctx->f0.fl;
    // 0x800BC76C: addiu       $at, $zero, 0x6
    ctx->r1 = ADD32(0, 0X6);
    // 0x800BC770: sub.s       $f16, $f6, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f16.fl = ctx->f6.fl - ctx->f10.fl;
    // 0x800BC774: bc1t        L_800BC7B0
    if (c1cs) {
        // 0x800BC778: swc1        $f16, 0x14($a0)
        MEM_W(0X14, ctx->r4) = ctx->f16.u32l;
            goto L_800BC7B0;
    }
    // 0x800BC778: swc1        $f16, 0x14($a0)
    MEM_W(0X14, ctx->r4) = ctx->f16.u32l;
    // 0x800BC77C: bnel        $a1, $at, L_800BC7B4
    if (ctx->r5 != ctx->r1) {
        // 0x800BC780: lwc1        $f4, 0x14($a0)
        ctx->f4.u32l = MEM_W(ctx->r4, 0X14);
            goto L_800BC7B4;
    }
    goto skip_1;
    // 0x800BC780: lwc1        $f4, 0x14($a0)
    ctx->f4.u32l = MEM_W(ctx->r4, 0X14);
    skip_1:
    // 0x800BC784: lwc1        $f18, 0x14($a0)
    ctx->f18.u32l = MEM_W(ctx->r4, 0X14);
    // 0x800BC788: addiu       $t2, $zero, 0x80
    ctx->r10 = ADD32(0, 0X80);
    // 0x800BC78C: addiu       $t3, $zero, 0x8
    ctx->r11 = ADD32(0, 0X8);
    // 0x800BC790: c.lt.s      $f18, $f0
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 0);
    c1cs = ctx->f18.fl < ctx->f0.fl;
    // 0x800BC794: nop

    // 0x800BC798: bc1fl       L_800BC7FC
    if (!c1cs) {
        // 0x800BC79C: mtc1        $zero, $f12
        ctx->f12.u32l = 0;
            goto L_800BC7FC;
    }
    goto skip_2;
    // 0x800BC79C: mtc1        $zero, $f12
    ctx->f12.u32l = 0;
    skip_2:
    // 0x800BC7A0: swc1        $f0, 0x14($a0)
    MEM_W(0X14, ctx->r4) = ctx->f0.u32l;
    // 0x800BC7A4: sh          $t2, 0x4($a0)
    MEM_H(0X4, ctx->r4) = ctx->r10;
    // 0x800BC7A8: b           L_800BC7F8
    // 0x800BC7AC: sb          $t3, 0x1($a0)
    MEM_B(0X1, ctx->r4) = ctx->r11;
        goto L_800BC7F8;
    // 0x800BC7AC: sb          $t3, 0x1($a0)
    MEM_B(0X1, ctx->r4) = ctx->r11;
L_800BC7B0:
    // 0x800BC7B0: lwc1        $f4, 0x14($a0)
    ctx->f4.u32l = MEM_W(ctx->r4, 0X14);
L_800BC7B4:
    // 0x800BC7B4: mtc1        $zero, $f8
    ctx->f8.u32l = 0;
    // 0x800BC7B8: nop

    // 0x800BC7BC: c.lt.s      $f4, $f8
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    c1cs = ctx->f4.fl < ctx->f8.fl;
    // 0x800BC7C0: nop

    // 0x800BC7C4: bc1fl       L_800BC7FC
    if (!c1cs) {
        // 0x800BC7C8: mtc1        $zero, $f12
        ctx->f12.u32l = 0;
            goto L_800BC7FC;
    }
    goto skip_3;
    // 0x800BC7C8: mtc1        $zero, $f12
    ctx->f12.u32l = 0;
    skip_3:
    // 0x800BC7CC: swc1        $f12, 0x14($a0)
    MEM_W(0X14, ctx->r4) = ctx->f12.u32l;
    // 0x800BC7D0: b           L_800BC7F8
    // 0x800BC7D4: sb          $zero, 0x1($a0)
    MEM_B(0X1, ctx->r4) = 0;
        goto L_800BC7F8;
    // 0x800BC7D4: sb          $zero, 0x1($a0)
    MEM_B(0X1, ctx->r4) = 0;
L_800BC7D8:
    // 0x800BC7D8: lh          $t4, 0x4($a0)
    ctx->r12 = MEM_H(ctx->r4, 0X4);
    // 0x800BC7DC: addiu       $t7, $zero, 0x7
    ctx->r15 = ADD32(0, 0X7);
    // 0x800BC7E0: addiu       $t5, $t4, -0x1
    ctx->r13 = ADD32(ctx->r12, -0X1);
    // 0x800BC7E4: sh          $t5, 0x4($a0)
    MEM_H(0X4, ctx->r4) = ctx->r13;
    // 0x800BC7E8: lh          $t6, 0x4($a0)
    ctx->r14 = MEM_H(ctx->r4, 0X4);
    // 0x800BC7EC: bnel        $t6, $zero, L_800BC7FC
    if (ctx->r14 != 0) {
        // 0x800BC7F0: mtc1        $zero, $f12
        ctx->f12.u32l = 0;
            goto L_800BC7FC;
    }
    goto skip_4;
    // 0x800BC7F0: mtc1        $zero, $f12
    ctx->f12.u32l = 0;
    skip_4:
    // 0x800BC7F4: sb          $t7, 0x1($a0)
    MEM_B(0X1, ctx->r4) = ctx->r15;
L_800BC7F8:
    // 0x800BC7F8: mtc1        $zero, $f12
    ctx->f12.u32l = 0;
L_800BC7FC:
    // 0x800BC7FC: andi        $t8, $v0, 0x20
    ctx->r24 = ctx->r2 & 0X20;
    // 0x800BC800: beq         $t8, $zero, L_800BC818
    if (ctx->r24 == 0) {
        // 0x800BC804: or          $v1, $v0, $zero
        ctx->r3 = ctx->r2 | 0;
            goto L_800BC818;
    }
    // 0x800BC804: or          $v1, $v0, $zero
    ctx->r3 = ctx->r2 | 0;
    // 0x800BC808: addiu       $t9, $zero, 0x6
    ctx->r25 = ADD32(0, 0X6);
    // 0x800BC80C: andi        $t1, $v0, 0xFFDF
    ctx->r9 = ctx->r2 & 0XFFDF;
    // 0x800BC810: sb          $t9, 0x1($a0)
    MEM_B(0X1, ctx->r4) = ctx->r25;
    // 0x800BC814: sb          $t1, 0x0($a0)
    MEM_B(0X0, ctx->r4) = ctx->r9;
L_800BC818:
    // 0x800BC818: andi        $t0, $v1, 0x10
    ctx->r8 = ctx->r3 & 0X10;
    // 0x800BC81C: beq         $t0, $zero, L_800BC830
    if (ctx->r8 == 0) {
        // 0x800BC820: addiu       $t2, $zero, 0x7
        ctx->r10 = ADD32(0, 0X7);
            goto L_800BC830;
    }
    // 0x800BC820: addiu       $t2, $zero, 0x7
    ctx->r10 = ADD32(0, 0X7);
    // 0x800BC824: andi        $t3, $v1, 0xFFEF
    ctx->r11 = ctx->r3 & 0XFFEF;
    // 0x800BC828: sb          $t2, 0x1($a0)
    MEM_B(0X1, ctx->r4) = ctx->r10;
    // 0x800BC82C: sb          $t3, 0x0($a0)
    MEM_B(0X0, ctx->r4) = ctx->r11;
L_800BC830:
    // 0x800BC830: lwc1        $f2, 0x14($a0)
    ctx->f2.u32l = MEM_W(ctx->r4, 0X14);
    // 0x800BC834: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x800BC838: c.lt.s      $f2, $f12
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 12);
    c1cs = ctx->f2.fl < ctx->f12.fl;
    // 0x800BC83C: nop

    // 0x800BC840: bc1fl       L_800BC854
    if (!c1cs) {
        // 0x800BC844: mtc1        $at, $f12
        ctx->f12.u32l = ctx->r1;
            goto L_800BC854;
    }
    goto skip_5;
    // 0x800BC844: mtc1        $at, $f12
    ctx->f12.u32l = ctx->r1;
    skip_5:
    // 0x800BC848: jr          $ra
    // 0x800BC84C: mov.s       $f0, $f12
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 12);
    ctx->f0.fl = ctx->f12.fl;
    return;
    // 0x800BC84C: mov.s       $f0, $f12
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 12);
    ctx->f0.fl = ctx->f12.fl;
    // 0x800BC850: mtc1        $at, $f12
    ctx->f12.u32l = ctx->r1;
L_800BC854:
    // 0x800BC854: nop

    // 0x800BC858: c.lt.s      $f12, $f2
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 2);
    c1cs = ctx->f12.fl < ctx->f2.fl;
    // 0x800BC85C: nop

    // 0x800BC860: bc1fl       L_800BC874
    if (!c1cs) {
        // 0x800BC864: mov.s       $f0, $f2
        CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    ctx->f0.fl = ctx->f2.fl;
            goto L_800BC874;
    }
    goto skip_6;
    // 0x800BC864: mov.s       $f0, $f2
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    ctx->f0.fl = ctx->f2.fl;
    skip_6:
    // 0x800BC868: jr          $ra
    // 0x800BC86C: mov.s       $f0, $f12
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 12);
    ctx->f0.fl = ctx->f12.fl;
    return;
    // 0x800BC86C: mov.s       $f0, $f12
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 12);
    ctx->f0.fl = ctx->f12.fl;
    // 0x800BC870: mov.s       $f0, $f2
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    ctx->f0.fl = ctx->f2.fl;
L_800BC874:
    // 0x800BC874: jr          $ra
    // 0x800BC878: nop

    return;
    // 0x800BC878: nop

    // 0x800BC87C: nop

;}
RECOMP_FUNC void AudioSeq_InitSequenceChannel(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800BC880: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800BC884: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800BC888: lbu         $t6, 0x0($a0)
    ctx->r14 = MEM_BU(ctx->r4, 0X0);
    // 0x800BC88C: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x800BC890: mtc1        $at, $f0
    ctx->f0.u32l = ctx->r1;
    // 0x800BC894: andi        $t8, $t6, 0xFF7F
    ctx->r24 = ctx->r14 & 0XFF7F;
    // 0x800BC898: andi        $t0, $t8, 0xBF
    ctx->r8 = ctx->r24 & 0XBF;
    // 0x800BC89C: sb          $t8, 0x0($a0)
    MEM_B(0X0, ctx->r4) = ctx->r24;
    // 0x800BC8A0: andi        $t2, $t0, 0xDF
    ctx->r10 = ctx->r8 & 0XDF;
    // 0x800BC8A4: sb          $t0, 0x0($a0)
    MEM_B(0X0, ctx->r4) = ctx->r8;
    // 0x800BC8A8: andi        $t4, $t2, 0xEF
    ctx->r12 = ctx->r10 & 0XEF;
    // 0x800BC8AC: sb          $t2, 0x0($a0)
    MEM_B(0X0, ctx->r4) = ctx->r10;
    // 0x800BC8B0: andi        $t6, $t4, 0xF7
    ctx->r14 = ctx->r12 & 0XF7;
    // 0x800BC8B4: sb          $t4, 0x0($a0)
    MEM_B(0X0, ctx->r4) = ctx->r12;
    // 0x800BC8B8: andi        $t8, $t6, 0xFB
    ctx->r24 = ctx->r14 & 0XFB;
    // 0x800BC8BC: addiu       $v0, $zero, 0x800
    ctx->r2 = ADD32(0, 0X800);
    // 0x800BC8C0: sb          $t6, 0x0($a0)
    MEM_B(0X0, ctx->r4) = ctx->r14;
    // 0x800BC8C4: lui         $t4, 0x800F
    ctx->r12 = S32(0X800F << 16);
    // 0x800BC8C8: or          $a1, $a0, $zero
    ctx->r5 = ctx->r4 | 0;
    // 0x800BC8CC: sb          $t8, 0x0($a0)
    MEM_B(0X0, ctx->r4) = ctx->r24;
    // 0x800BC8D0: andi        $t9, $t8, 0xFD
    ctx->r25 = ctx->r24 & 0XFD;
    // 0x800BC8D4: addiu       $t0, $zero, 0xFF
    ctx->r8 = ADD32(0, 0XFF);
    // 0x800BC8D8: addiu       $t1, $zero, 0x40
    ctx->r9 = ADD32(0, 0X40);
    // 0x800BC8DC: addiu       $t2, $zero, 0x80
    ctx->r10 = ADD32(0, 0X80);
    // 0x800BC8E0: addiu       $t3, $zero, 0x3
    ctx->r11 = ADD32(0, 0X3);
    // 0x800BC8E4: addiu       $t4, $t4, -0x2FFC
    ctx->r12 = ADD32(ctx->r12, -0X2FFC);
    // 0x800BC8E8: addiu       $t5, $zero, 0x20
    ctx->r13 = ADD32(0, 0X20);
    // 0x800BC8EC: sh          $v0, 0x10($a0)
    MEM_H(0X10, ctx->r4) = ctx->r2;
    // 0x800BC8F0: sh          $v0, 0xC($a0)
    MEM_H(0XC, ctx->r4) = ctx->r2;
    // 0x800BC8F4: sh          $zero, 0x1E($a0)
    MEM_H(0X1E, ctx->r4) = 0;
    // 0x800BC8F8: sb          $t9, 0x0($a0)
    MEM_B(0X0, ctx->r4) = ctx->r25;
    // 0x800BC8FC: sb          $zero, 0x8($a0)
    MEM_B(0X8, ctx->r4) = 0;
    // 0x800BC900: sb          $t0, 0x1($a0)
    MEM_B(0X1, ctx->r4) = ctx->r8;
    // 0x800BC904: sb          $zero, 0x78($a0)
    MEM_B(0X78, ctx->r4) = 0;
    // 0x800BC908: sb          $t1, 0x9($a0)
    MEM_B(0X9, ctx->r4) = ctx->r9;
    // 0x800BC90C: sb          $t2, 0xA($a0)
    MEM_B(0XA, ctx->r4) = ctx->r10;
    // 0x800BC910: sw          $zero, 0x38($a0)
    MEM_W(0X38, ctx->r4) = 0;
    // 0x800BC914: sb          $zero, 0x7($a0)
    MEM_B(0X7, ctx->r4) = 0;
    // 0x800BC918: sb          $zero, 0x4($a0)
    MEM_B(0X4, ctx->r4) = 0;
    // 0x800BC91C: sb          $t3, 0x5($a0)
    MEM_B(0X5, ctx->r4) = ctx->r11;
    // 0x800BC920: sh          $zero, 0x1A($a0)
    MEM_H(0X1A, ctx->r4) = 0;
    // 0x800BC924: sw          $t4, 0x80($a0)
    MEM_W(0X80, ctx->r4) = ctx->r12;
    // 0x800BC928: sb          $t5, 0x7C($a0)
    MEM_B(0X7C, ctx->r4) = ctx->r13;
    // 0x800BC92C: sb          $zero, 0x7D($a0)
    MEM_B(0X7D, ctx->r4) = 0;
    // 0x800BC930: sh          $zero, 0x12($a0)
    MEM_H(0X12, ctx->r4) = 0;
    // 0x800BC934: sh          $zero, 0xE($a0)
    MEM_H(0XE, ctx->r4) = 0;
    // 0x800BC938: sh          $zero, 0x14($a0)
    MEM_H(0X14, ctx->r4) = 0;
    // 0x800BC93C: sh          $zero, 0x16($a0)
    MEM_H(0X16, ctx->r4) = 0;
    // 0x800BC940: sh          $zero, 0x18($a0)
    MEM_H(0X18, ctx->r4) = 0;
    // 0x800BC944: swc1        $f0, 0x24($a0)
    MEM_W(0X24, ctx->r4) = ctx->f0.u32l;
    // 0x800BC948: swc1        $f0, 0x20($a0)
    MEM_W(0X20, ctx->r4) = ctx->f0.u32l;
    // 0x800BC94C: swc1        $f0, 0x30($a0)
    MEM_W(0X30, ctx->r4) = ctx->f0.u32l;
    // 0x800BC950: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    // 0x800BC954: addiu       $v0, $zero, -0x1
    ctx->r2 = ADD32(0, -0X1);
    // 0x800BC958: or          $v1, $a1, $zero
    ctx->r3 = ctx->r5 | 0;
    // 0x800BC95C: addiu       $a2, $zero, 0x8
    ctx->r6 = ADD32(0, 0X8);
L_800BC960:
    // 0x800BC960: addiu       $a0, $a0, 0x4
    ctx->r4 = ADD32(ctx->r4, 0X4);
    // 0x800BC964: sb          $v0, 0x59($v1)
    MEM_B(0X59, ctx->r3) = ctx->r2;
    // 0x800BC968: sb          $v0, 0x5A($v1)
    MEM_B(0X5A, ctx->r3) = ctx->r2;
    // 0x800BC96C: sb          $v0, 0x5B($v1)
    MEM_B(0X5B, ctx->r3) = ctx->r2;
    // 0x800BC970: addiu       $v1, $v1, 0x4
    ctx->r3 = ADD32(ctx->r3, 0X4);
    // 0x800BC974: bne         $a0, $a2, L_800BC960
    if (ctx->r4 != ctx->r6) {
        // 0x800BC978: sb          $v0, 0x54($v1)
        MEM_B(0X54, ctx->r3) = ctx->r2;
            goto L_800BC960;
    }
    // 0x800BC978: sb          $v0, 0x54($v1)
    MEM_B(0X54, ctx->r3) = ctx->r2;
    // 0x800BC97C: lbu         $t6, 0x0($a1)
    ctx->r14 = MEM_BU(ctx->r5, 0X0);
    // 0x800BC980: addiu       $a0, $a1, 0x84
    ctx->r4 = ADD32(ctx->r5, 0X84);
    // 0x800BC984: andi        $t7, $t6, 0xFFFE
    ctx->r15 = ctx->r14 & 0XFFFE;
    // 0x800BC988: jal         0x800BB300
    // 0x800BC98C: sb          $t7, 0x0($a1)
    MEM_B(0X0, ctx->r5) = ctx->r15;
    Audio_InitNoteLists(rdram, ctx);
        goto after_0;
    // 0x800BC98C: sb          $t7, 0x0($a1)
    MEM_B(0X0, ctx->r5) = ctx->r15;
    after_0:
    // 0x800BC990: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800BC994: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800BC998: jr          $ra
    // 0x800BC99C: nop

    return;
    // 0x800BC99C: nop

;}
RECOMP_FUNC void AudioSeq_SeqChannelSetLayer(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800BC9A0: addiu       $sp, $sp, -0x28
    ctx->r29 = ADD32(ctx->r29, -0X28);
    // 0x800BC9A4: sll         $t7, $a1, 2
    ctx->r15 = S32(ctx->r5 << 2);
    // 0x800BC9A8: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800BC9AC: sw          $a0, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r4;
    // 0x800BC9B0: addu        $a2, $a0, $t7
    ctx->r6 = ADD32(ctx->r4, ctx->r15);
    // 0x800BC9B4: lw          $a3, 0x48($a2)
    ctx->r7 = MEM_W(ctx->r6, 0X48);
    // 0x800BC9B8: bne         $a3, $zero, L_800BC9E8
    if (ctx->r7 != 0) {
        // 0x800BC9BC: or          $a0, $a3, $zero
        ctx->r4 = ctx->r7 | 0;
            goto L_800BC9E8;
    }
    // 0x800BC9BC: or          $a0, $a3, $zero
    ctx->r4 = ctx->r7 | 0;
    // 0x800BC9C0: lui         $a0, 0x8004
    ctx->r4 = S32(0X8004 << 16);
    // 0x800BC9C4: addiu       $a0, $a0, 0x4750
    ctx->r4 = ADD32(ctx->r4, 0X4750);
    // 0x800BC9C8: jal         0x800BCFEC
    // 0x800BC9CC: sw          $a2, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r6;
    AudioSeq_AudioListPopBack(rdram, ctx);
        goto after_0;
    // 0x800BC9CC: sw          $a2, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r6;
    after_0:
    // 0x800BC9D0: lw          $a2, 0x1C($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X1C);
    // 0x800BC9D4: bne         $v0, $zero, L_800BC9F4
    if (ctx->r2 != 0) {
        // 0x800BC9D8: sw          $v0, 0x48($a2)
        MEM_W(0X48, ctx->r6) = ctx->r2;
            goto L_800BC9F4;
    }
    // 0x800BC9D8: sw          $v0, 0x48($a2)
    MEM_W(0X48, ctx->r6) = ctx->r2;
    // 0x800BC9DC: sw          $zero, 0x48($a2)
    MEM_W(0X48, ctx->r6) = 0;
    // 0x800BC9E0: b           L_800BCA98
    // 0x800BC9E4: addiu       $v0, $zero, -0x1
    ctx->r2 = ADD32(0, -0X1);
        goto L_800BCA98;
    // 0x800BC9E4: addiu       $v0, $zero, -0x1
    ctx->r2 = ADD32(0, -0X1);
L_800BC9E8:
    // 0x800BC9E8: jal         0x800BB108
    // 0x800BC9EC: sw          $a2, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r6;
    Audio_SeqLayerNoteDecay(rdram, ctx);
        goto after_1;
    // 0x800BC9EC: sw          $a2, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r6;
    after_1:
    // 0x800BC9F0: lw          $a2, 0x1C($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X1C);
L_800BC9F4:
    // 0x800BC9F4: lw          $v1, 0x48($a2)
    ctx->r3 = MEM_W(ctx->r6, 0X48);
    // 0x800BC9F8: lw          $t8, 0x28($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X28);
    // 0x800BC9FC: mtc1        $zero, $f6
    ctx->f6.u32l = 0;
    // 0x800BCA00: lbu         $t3, 0x0($v1)
    ctx->r11 = MEM_BU(ctx->r3, 0X0);
    // 0x800BCA04: sw          $t8, 0x4C($v1)
    MEM_W(0X4C, ctx->r3) = ctx->r24;
    // 0x800BCA08: lw          $t9, 0x28($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X28);
    // 0x800BCA0C: ori         $t5, $t3, 0x80
    ctx->r13 = ctx->r11 | 0X80;
    // 0x800BCA10: andi        $t7, $t5, 0xDF
    ctx->r15 = ctx->r13 & 0XDF;
    // 0x800BCA14: lw          $at, 0x7C($t9)
    ctx->r1 = MEM_W(ctx->r25, 0X7C);
    // 0x800BCA18: andi        $t0, $t7, 0xEF
    ctx->r8 = ctx->r15 & 0XEF;
    // 0x800BCA1C: addiu       $t3, $zero, 0x80
    ctx->r11 = ADD32(0, 0X80);
    // 0x800BCA20: sw          $at, 0x18($v1)
    MEM_W(0X18, ctx->r3) = ctx->r1;
    // 0x800BCA24: lw          $t1, 0x80($t9)
    ctx->r9 = MEM_W(ctx->r25, 0X80);
    // 0x800BCA28: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x800BCA2C: sb          $t5, 0x0($v1)
    MEM_B(0X0, ctx->r3) = ctx->r13;
    // 0x800BCA30: sw          $t1, 0x1C($v1)
    MEM_W(0X1C, ctx->r3) = ctx->r9;
    // 0x800BCA34: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x800BCA38: andi        $t1, $t0, 0xBF
    ctx->r9 = ctx->r8 & 0XBF;
    // 0x800BCA3C: sb          $t7, 0x0($v1)
    MEM_B(0X0, ctx->r3) = ctx->r15;
    // 0x800BCA40: sb          $t0, 0x0($v1)
    MEM_B(0X0, ctx->r3) = ctx->r8;
    // 0x800BCA44: andi        $t2, $t1, 0xFD
    ctx->r10 = ctx->r9 & 0XFD;
    // 0x800BCA48: addiu       $t4, $zero, 0x40
    ctx->r12 = ADD32(0, 0X40);
    // 0x800BCA4C: addiu       $t5, $zero, 0xFF
    ctx->r13 = ADD32(0, 0XFF);
    // 0x800BCA50: sb          $t1, 0x0($v1)
    MEM_B(0X0, ctx->r3) = ctx->r9;
    // 0x800BCA54: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    // 0x800BCA58: sb          $zero, 0x18($v1)
    MEM_B(0X18, ctx->r3) = 0;
    // 0x800BCA5C: sb          $t2, 0x0($v1)
    MEM_B(0X0, ctx->r3) = ctx->r10;
    // 0x800BCA60: sb          $zero, 0x8($v1)
    MEM_B(0X8, ctx->r3) = 0;
    // 0x800BCA64: sb          $zero, 0x68($v1)
    MEM_B(0X68, ctx->r3) = 0;
    // 0x800BCA68: sb          $zero, 0x2($v1)
    MEM_B(0X2, ctx->r3) = 0;
    // 0x800BCA6C: sb          $t3, 0x3($v1)
    MEM_B(0X3, ctx->r3) = ctx->r11;
    // 0x800BCA70: sb          $t4, 0x5($v1)
    MEM_B(0X5, ctx->r3) = ctx->r12;
    // 0x800BCA74: sh          $zero, 0x22($v1)
    MEM_H(0X22, ctx->r3) = 0;
    // 0x800BCA78: sh          $zero, 0x38($v1)
    MEM_H(0X38, ctx->r3) = 0;
    // 0x800BCA7C: sh          $zero, 0x3A($v1)
    MEM_H(0X3A, ctx->r3) = 0;
    // 0x800BCA80: sh          $zero, 0x3C($v1)
    MEM_H(0X3C, ctx->r3) = 0;
    // 0x800BCA84: sw          $zero, 0x40($v1)
    MEM_W(0X40, ctx->r3) = 0;
    // 0x800BCA88: sw          $zero, 0x44($v1)
    MEM_W(0X44, ctx->r3) = 0;
    // 0x800BCA8C: sb          $t5, 0x1($v1)
    MEM_B(0X1, ctx->r3) = ctx->r13;
    // 0x800BCA90: swc1        $f6, 0x28($v1)
    MEM_W(0X28, ctx->r3) = ctx->f6.u32l;
    // 0x800BCA94: swc1        $f4, 0x24($v1)
    MEM_W(0X24, ctx->r3) = ctx->f4.u32l;
L_800BCA98:
    // 0x800BCA98: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800BCA9C: addiu       $sp, $sp, 0x28
    ctx->r29 = ADD32(ctx->r29, 0X28);
    // 0x800BCAA0: jr          $ra
    // 0x800BCAA4: nop

    return;
    // 0x800BCAA4: nop

;}
RECOMP_FUNC void AudioSeq_SeqLayerDisable(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800BCAA8: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800BCAAC: beq         $a0, $zero, L_800BCAD4
    if (ctx->r4 == 0) {
        // 0x800BCAB0: sw          $ra, 0x14($sp)
        MEM_W(0X14, ctx->r29) = ctx->r31;
            goto L_800BCAD4;
    }
    // 0x800BCAB0: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800BCAB4: jal         0x800BB108
    // 0x800BCAB8: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    Audio_SeqLayerNoteDecay(rdram, ctx);
        goto after_0;
    // 0x800BCAB8: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    after_0:
    // 0x800BCABC: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
    // 0x800BCAC0: lbu         $t6, 0x0($a0)
    ctx->r14 = MEM_BU(ctx->r4, 0X0);
    // 0x800BCAC4: andi        $t9, $t6, 0xFF7F
    ctx->r25 = ctx->r14 & 0XFF7F;
    // 0x800BCAC8: ori         $t0, $t9, 0x40
    ctx->r8 = ctx->r25 | 0X40;
    // 0x800BCACC: sb          $t9, 0x0($a0)
    MEM_B(0X0, ctx->r4) = ctx->r25;
    // 0x800BCAD0: sb          $t0, 0x0($a0)
    MEM_B(0X0, ctx->r4) = ctx->r8;
L_800BCAD4:
    // 0x800BCAD4: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800BCAD8: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800BCADC: jr          $ra
    // 0x800BCAE0: nop

    return;
    // 0x800BCAE0: nop

;}
RECOMP_FUNC void AudioSeq_SeqLayerFree(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800BCAE4: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x800BCAE8: sll         $t6, $a1, 2
    ctx->r14 = S32(ctx->r5 << 2);
    // 0x800BCAEC: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800BCAF0: addu        $v0, $a0, $t6
    ctx->r2 = ADD32(ctx->r4, ctx->r14);
    // 0x800BCAF4: lw          $a2, 0x48($v0)
    ctx->r6 = MEM_W(ctx->r2, 0X48);
    // 0x800BCAF8: lui         $a0, 0x8004
    ctx->r4 = S32(0X8004 << 16);
    // 0x800BCAFC: addiu       $a0, $a0, 0x4750
    ctx->r4 = ADD32(ctx->r4, 0X4750);
    // 0x800BCB00: beq         $a2, $zero, L_800BCB24
    if (ctx->r6 == 0) {
        // 0x800BCB04: addiu       $a1, $a2, 0x6C
        ctx->r5 = ADD32(ctx->r6, 0X6C);
            goto L_800BCB24;
    }
    // 0x800BCB04: addiu       $a1, $a2, 0x6C
    ctx->r5 = ADD32(ctx->r6, 0X6C);
    // 0x800BCB08: sw          $v0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r2;
    // 0x800BCB0C: jal         0x800BCFAC
    // 0x800BCB10: sw          $a2, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r6;
    AudioSeq_AudioListPushBack(rdram, ctx);
        goto after_0;
    // 0x800BCB10: sw          $a2, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r6;
    after_0:
    // 0x800BCB14: jal         0x800BCAA8
    // 0x800BCB18: lw          $a0, 0x1C($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X1C);
    AudioSeq_SeqLayerDisable(rdram, ctx);
        goto after_1;
    // 0x800BCB18: lw          $a0, 0x1C($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X1C);
    after_1:
    // 0x800BCB1C: lw          $v0, 0x18($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X18);
    // 0x800BCB20: sw          $zero, 0x48($v0)
    MEM_W(0X48, ctx->r2) = 0;
L_800BCB24:
    // 0x800BCB24: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800BCB28: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x800BCB2C: jr          $ra
    // 0x800BCB30: nop

    return;
    // 0x800BCB30: nop

;}
RECOMP_FUNC void AudioSeq_SequenceChannelDisable(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800BCB34: addiu       $sp, $sp, -0x28
    ctx->r29 = ADD32(ctx->r29, -0X28);
    // 0x800BCB38: sw          $s2, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r18;
    // 0x800BCB3C: sw          $s1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r17;
    // 0x800BCB40: sw          $s0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r16;
    // 0x800BCB44: or          $s1, $a0, $zero
    ctx->r17 = ctx->r4 | 0;
    // 0x800BCB48: sw          $ra, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r31;
    // 0x800BCB4C: or          $s0, $zero, $zero
    ctx->r16 = 0 | 0;
    // 0x800BCB50: addiu       $s2, $zero, 0x4
    ctx->r18 = ADD32(0, 0X4);
    // 0x800BCB54: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
L_800BCB58:
    // 0x800BCB58: jal         0x800BCAE4
    // 0x800BCB5C: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    AudioSeq_SeqLayerFree(rdram, ctx);
        goto after_0;
    // 0x800BCB5C: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    after_0:
    // 0x800BCB60: addiu       $s0, $s0, 0x1
    ctx->r16 = ADD32(ctx->r16, 0X1);
    // 0x800BCB64: bnel        $s0, $s2, L_800BCB58
    if (ctx->r16 != ctx->r18) {
        // 0x800BCB68: or          $a0, $s1, $zero
        ctx->r4 = ctx->r17 | 0;
            goto L_800BCB58;
    }
    goto skip_0;
    // 0x800BCB68: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    skip_0:
    // 0x800BCB6C: jal         0x800BB400
    // 0x800BCB70: addiu       $a0, $s1, 0x84
    ctx->r4 = ADD32(ctx->r17, 0X84);
    Audio_NotePoolClear(rdram, ctx);
        goto after_1;
    // 0x800BCB70: addiu       $a0, $s1, 0x84
    ctx->r4 = ADD32(ctx->r17, 0X84);
    after_1:
    // 0x800BCB74: lbu         $t6, 0x0($s1)
    ctx->r14 = MEM_BU(ctx->r17, 0X0);
    // 0x800BCB78: andi        $t9, $t6, 0xFF7F
    ctx->r25 = ctx->r14 & 0XFF7F;
    // 0x800BCB7C: sb          $t9, 0x0($s1)
    MEM_B(0X0, ctx->r17) = ctx->r25;
    // 0x800BCB80: ori         $t0, $t9, 0x40
    ctx->r8 = ctx->r25 | 0X40;
    // 0x800BCB84: sb          $t0, 0x0($s1)
    MEM_B(0X0, ctx->r17) = ctx->r8;
    // 0x800BCB88: lw          $ra, 0x24($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X24);
    // 0x800BCB8C: lw          $s2, 0x20($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X20);
    // 0x800BCB90: lw          $s1, 0x1C($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X1C);
    // 0x800BCB94: lw          $s0, 0x18($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X18);
    // 0x800BCB98: jr          $ra
    // 0x800BCB9C: addiu       $sp, $sp, 0x28
    ctx->r29 = ADD32(ctx->r29, 0X28);
    return;
    // 0x800BCB9C: addiu       $sp, $sp, 0x28
    ctx->r29 = ADD32(ctx->r29, 0X28);
;}
RECOMP_FUNC void AudioSeq_RequestFreeSeqChannel(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800BCBA0: lui         $v1, 0x8004
    ctx->r3 = S32(0X8004 << 16);
    // 0x800BCBA4: lui         $v0, 0x8004
    ctx->r2 = S32(0X8004 << 16);
    // 0x800BCBA8: addiu       $v0, $v0, 0x2688
    ctx->r2 = ADD32(ctx->r2, 0X2688);
    // 0x800BCBAC: addiu       $v1, $v1, 0x1C8
    ctx->r3 = ADD32(ctx->r3, 0X1C8);
    // 0x800BCBB0: lw          $t6, 0x44($v1)
    ctx->r14 = MEM_W(ctx->r3, 0X44);
L_800BCBB4:
    // 0x800BCBB4: bnel        $t6, $zero, L_800BCBC8
    if (ctx->r14 != 0) {
        // 0x800BCBB8: lw          $t7, 0x108($v1)
        ctx->r15 = MEM_W(ctx->r3, 0X108);
            goto L_800BCBC8;
    }
    goto skip_0;
    // 0x800BCBB8: lw          $t7, 0x108($v1)
    ctx->r15 = MEM_W(ctx->r3, 0X108);
    skip_0:
    // 0x800BCBBC: jr          $ra
    // 0x800BCBC0: or          $v0, $v1, $zero
    ctx->r2 = ctx->r3 | 0;
    return;
    // 0x800BCBC0: or          $v0, $v1, $zero
    ctx->r2 = ctx->r3 | 0;
    // 0x800BCBC4: lw          $t7, 0x108($v1)
    ctx->r15 = MEM_W(ctx->r3, 0X108);
L_800BCBC8:
    // 0x800BCBC8: bnel        $t7, $zero, L_800BCBDC
    if (ctx->r15 != 0) {
        // 0x800BCBCC: lw          $t8, 0x1CC($v1)
        ctx->r24 = MEM_W(ctx->r3, 0X1CC);
            goto L_800BCBDC;
    }
    goto skip_1;
    // 0x800BCBCC: lw          $t8, 0x1CC($v1)
    ctx->r24 = MEM_W(ctx->r3, 0X1CC);
    skip_1:
    // 0x800BCBD0: jr          $ra
    // 0x800BCBD4: addiu       $v0, $v1, 0xC4
    ctx->r2 = ADD32(ctx->r3, 0XC4);
    return;
    // 0x800BCBD4: addiu       $v0, $v1, 0xC4
    ctx->r2 = ADD32(ctx->r3, 0XC4);
    // 0x800BCBD8: lw          $t8, 0x1CC($v1)
    ctx->r24 = MEM_W(ctx->r3, 0X1CC);
L_800BCBDC:
    // 0x800BCBDC: bnel        $t8, $zero, L_800BCBF0
    if (ctx->r24 != 0) {
        // 0x800BCBE0: lw          $t9, 0x290($v1)
        ctx->r25 = MEM_W(ctx->r3, 0X290);
            goto L_800BCBF0;
    }
    goto skip_2;
    // 0x800BCBE0: lw          $t9, 0x290($v1)
    ctx->r25 = MEM_W(ctx->r3, 0X290);
    skip_2:
    // 0x800BCBE4: jr          $ra
    // 0x800BCBE8: addiu       $v0, $v1, 0x188
    ctx->r2 = ADD32(ctx->r3, 0X188);
    return;
    // 0x800BCBE8: addiu       $v0, $v1, 0x188
    ctx->r2 = ADD32(ctx->r3, 0X188);
    // 0x800BCBEC: lw          $t9, 0x290($v1)
    ctx->r25 = MEM_W(ctx->r3, 0X290);
L_800BCBF0:
    // 0x800BCBF0: bnel        $t9, $zero, L_800BCC04
    if (ctx->r25 != 0) {
        // 0x800BCBF4: addiu       $v1, $v1, 0x310
        ctx->r3 = ADD32(ctx->r3, 0X310);
            goto L_800BCC04;
    }
    goto skip_3;
    // 0x800BCBF4: addiu       $v1, $v1, 0x310
    ctx->r3 = ADD32(ctx->r3, 0X310);
    skip_3:
    // 0x800BCBF8: jr          $ra
    // 0x800BCBFC: addiu       $v0, $v1, 0x24C
    ctx->r2 = ADD32(ctx->r3, 0X24C);
    return;
    // 0x800BCBFC: addiu       $v0, $v1, 0x24C
    ctx->r2 = ADD32(ctx->r3, 0X24C);
    // 0x800BCC00: addiu       $v1, $v1, 0x310
    ctx->r3 = ADD32(ctx->r3, 0X310);
L_800BCC04:
    // 0x800BCC04: bnel        $v1, $v0, L_800BCBB4
    if (ctx->r3 != ctx->r2) {
        // 0x800BCC08: lw          $t6, 0x44($v1)
        ctx->r14 = MEM_W(ctx->r3, 0X44);
            goto L_800BCBB4;
    }
    goto skip_4;
    // 0x800BCC08: lw          $t6, 0x44($v1)
    ctx->r14 = MEM_W(ctx->r3, 0X44);
    skip_4:
    // 0x800BCC0C: lui         $v0, 0x8004
    ctx->r2 = S32(0X8004 << 16);
    // 0x800BCC10: addiu       $v0, $v0, 0x4688
    ctx->r2 = ADD32(ctx->r2, 0X4688);
    // 0x800BCC14: jr          $ra
    // 0x800BCC18: nop

    return;
    // 0x800BCC18: nop

;}
RECOMP_FUNC void AudioSeq_SequencePlayerSetupChannels(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800BCC1C: addiu       $sp, $sp, -0x40
    ctx->r29 = ADD32(ctx->r29, -0X40);
    // 0x800BCC20: sw          $fp, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r30;
    // 0x800BCC24: sw          $s7, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r23;
    // 0x800BCC28: sw          $s6, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r22;
    // 0x800BCC2C: sw          $s3, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r19;
    // 0x800BCC30: sw          $s1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r17;
    // 0x800BCC34: sw          $a1, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r5;
    // 0x800BCC38: andi        $t6, $a1, 0xFFFF
    ctx->r14 = ctx->r5 & 0XFFFF;
    // 0x800BCC3C: lui         $s7, 0x8004
    ctx->r23 = S32(0X8004 << 16);
    // 0x800BCC40: lui         $fp, 0x8004
    ctx->r30 = S32(0X8004 << 16);
    // 0x800BCC44: or          $a1, $t6, $zero
    ctx->r5 = ctx->r14 | 0;
    // 0x800BCC48: or          $s1, $a0, $zero
    ctx->r17 = ctx->r4 | 0;
    // 0x800BCC4C: sw          $ra, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r31;
    // 0x800BCC50: sw          $s5, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r21;
    // 0x800BCC54: sw          $s4, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r20;
    // 0x800BCC58: sw          $s2, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r18;
    // 0x800BCC5C: sw          $s0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r16;
    // 0x800BCC60: addiu       $fp, $fp, 0x5630
    ctx->r30 = ADD32(ctx->r30, 0X5630);
    // 0x800BCC64: addiu       $s7, $s7, 0x4688
    ctx->r23 = ADD32(ctx->r23, 0X4688);
    // 0x800BCC68: or          $s3, $zero, $zero
    ctx->r19 = 0 | 0;
    // 0x800BCC6C: addiu       $s6, $zero, 0x1
    ctx->r22 = ADD32(0, 0X1);
L_800BCC70:
    // 0x800BCC70: andi        $t7, $a1, 0x1
    ctx->r15 = ctx->r5 & 0X1;
    // 0x800BCC74: beq         $t7, $zero, L_800BCD00
    if (ctx->r15 == 0) {
        // 0x800BCC78: or          $s5, $a1, $zero
        ctx->r21 = ctx->r5 | 0;
            goto L_800BCD00;
    }
    // 0x800BCC78: or          $s5, $a1, $zero
    ctx->r21 = ctx->r5 | 0;
    // 0x800BCC7C: sll         $t8, $s3, 2
    ctx->r24 = S32(ctx->r19 << 2);
    // 0x800BCC80: addu        $s2, $s1, $t8
    ctx->r18 = ADD32(ctx->r17, ctx->r24);
    // 0x800BCC84: lw          $s0, 0x30($s2)
    ctx->r16 = MEM_W(ctx->r18, 0X30);
    // 0x800BCC88: or          $s4, $s7, $zero
    ctx->r20 = ctx->r23 | 0;
    // 0x800BCC8C: xor         $t9, $s0, $s7
    ctx->r25 = ctx->r16 ^ ctx->r23;
    // 0x800BCC90: sltu        $t9, $zero, $t9
    ctx->r25 = 0 < ctx->r25 ? 1 : 0;
    // 0x800BCC94: bne         $s6, $t9, L_800BCCB4
    if (ctx->r22 != ctx->r25) {
        // 0x800BCC98: nop
    
            goto L_800BCCB4;
    }
    // 0x800BCC98: nop

    // 0x800BCC9C: lw          $t0, 0x44($s0)
    ctx->r8 = MEM_W(ctx->r16, 0X44);
    // 0x800BCCA0: bne         $s1, $t0, L_800BCCB4
    if (ctx->r17 != ctx->r8) {
        // 0x800BCCA4: nop
    
            goto L_800BCCB4;
    }
    // 0x800BCCA4: nop

    // 0x800BCCA8: jal         0x800BCB34
    // 0x800BCCAC: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    AudioSeq_SequenceChannelDisable(rdram, ctx);
        goto after_0;
    // 0x800BCCAC: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_0:
    // 0x800BCCB0: sw          $zero, 0x44($s0)
    MEM_W(0X44, ctx->r16) = 0;
L_800BCCB4:
    // 0x800BCCB4: jal         0x800BCBA0
    // 0x800BCCB8: nop

    AudioSeq_RequestFreeSeqChannel(rdram, ctx);
        goto after_1;
    // 0x800BCCB8: nop

    after_1:
    // 0x800BCCBC: bne         $v0, $s4, L_800BCCD8
    if (ctx->r2 != ctx->r20) {
        // 0x800BCCC0: or          $s0, $v0, $zero
        ctx->r16 = ctx->r2 | 0;
            goto L_800BCCD8;
    }
    // 0x800BCCC0: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
    // 0x800BCCC4: lui         $at, 0x1
    ctx->r1 = S32(0X1 << 16);
    // 0x800BCCC8: addu        $t2, $s3, $at
    ctx->r10 = ADD32(ctx->r19, ctx->r1);
    // 0x800BCCCC: sw          $t2, 0x0($fp)
    MEM_W(0X0, ctx->r30) = ctx->r10;
    // 0x800BCCD0: b           L_800BCD00
    // 0x800BCCD4: sw          $v0, 0x30($s2)
    MEM_W(0X30, ctx->r18) = ctx->r2;
        goto L_800BCD00;
    // 0x800BCCD4: sw          $v0, 0x30($s2)
    MEM_W(0X30, ctx->r18) = ctx->r2;
L_800BCCD8:
    // 0x800BCCD8: jal         0x800BC880
    // 0x800BCCDC: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    AudioSeq_InitSequenceChannel(rdram, ctx);
        goto after_2;
    // 0x800BCCDC: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_2:
    // 0x800BCCE0: sw          $s0, 0x30($s2)
    MEM_W(0X30, ctx->r18) = ctx->r16;
    // 0x800BCCE4: sw          $s1, 0x44($s0)
    MEM_W(0X44, ctx->r16) = ctx->r17;
    // 0x800BCCE8: lbu         $t3, 0x5($s1)
    ctx->r11 = MEM_BU(ctx->r17, 0X5);
    // 0x800BCCEC: sb          $t3, 0x6($s0)
    MEM_B(0X6, ctx->r16) = ctx->r11;
    // 0x800BCCF0: lbu         $t4, 0x3($s1)
    ctx->r12 = MEM_BU(ctx->r17, 0X3);
    // 0x800BCCF4: sb          $t4, 0x3($s0)
    MEM_B(0X3, ctx->r16) = ctx->r12;
    // 0x800BCCF8: lbu         $t5, 0x2($s1)
    ctx->r13 = MEM_BU(ctx->r17, 0X2);
    // 0x800BCCFC: sb          $t5, 0x2($s0)
    MEM_B(0X2, ctx->r16) = ctx->r13;
L_800BCD00:
    // 0x800BCD00: sra         $a1, $s5, 1
    ctx->r5 = S32(SIGNED(ctx->r21) >> 1);
    // 0x800BCD04: addiu       $s3, $s3, 0x1
    ctx->r19 = ADD32(ctx->r19, 0X1);
    // 0x800BCD08: addiu       $at, $zero, 0x10
    ctx->r1 = ADD32(0, 0X10);
    // 0x800BCD0C: andi        $t6, $a1, 0xFFFF
    ctx->r14 = ctx->r5 & 0XFFFF;
    // 0x800BCD10: bne         $s3, $at, L_800BCC70
    if (ctx->r19 != ctx->r1) {
        // 0x800BCD14: or          $a1, $t6, $zero
        ctx->r5 = ctx->r14 | 0;
            goto L_800BCC70;
    }
    // 0x800BCD14: or          $a1, $t6, $zero
    ctx->r5 = ctx->r14 | 0;
    // 0x800BCD18: lw          $ra, 0x3C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X3C);
    // 0x800BCD1C: lw          $s0, 0x18($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X18);
    // 0x800BCD20: lw          $s1, 0x1C($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X1C);
    // 0x800BCD24: lw          $s2, 0x20($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X20);
    // 0x800BCD28: lw          $s3, 0x24($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X24);
    // 0x800BCD2C: lw          $s4, 0x28($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X28);
    // 0x800BCD30: lw          $s5, 0x2C($sp)
    ctx->r21 = MEM_W(ctx->r29, 0X2C);
    // 0x800BCD34: lw          $s6, 0x30($sp)
    ctx->r22 = MEM_W(ctx->r29, 0X30);
    // 0x800BCD38: lw          $s7, 0x34($sp)
    ctx->r23 = MEM_W(ctx->r29, 0X34);
    // 0x800BCD3C: lw          $fp, 0x38($sp)
    ctx->r30 = MEM_W(ctx->r29, 0X38);
    // 0x800BCD40: jr          $ra
    // 0x800BCD44: addiu       $sp, $sp, 0x40
    ctx->r29 = ADD32(ctx->r29, 0X40);
    return;
    // 0x800BCD44: addiu       $sp, $sp, 0x40
    ctx->r29 = ADD32(ctx->r29, 0X40);
;}
RECOMP_FUNC void AudioSeq_SequencePlayerDisableChannels(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800BCD48: addiu       $sp, $sp, -0x38
    ctx->r29 = ADD32(ctx->r29, -0X38);
    // 0x800BCD4C: sw          $s5, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r21;
    // 0x800BCD50: sw          $s7, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r23;
    // 0x800BCD54: sw          $s6, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r22;
    // 0x800BCD58: sw          $s4, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r20;
    // 0x800BCD5C: sw          $s1, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r17;
    // 0x800BCD60: sw          $a1, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r5;
    // 0x800BCD64: andi        $t6, $a1, 0xFFFF
    ctx->r14 = ctx->r5 & 0XFFFF;
    // 0x800BCD68: lui         $s5, 0x8004
    ctx->r21 = S32(0X8004 << 16);
    // 0x800BCD6C: or          $a1, $t6, $zero
    ctx->r5 = ctx->r14 | 0;
    // 0x800BCD70: or          $s4, $a0, $zero
    ctx->r20 = ctx->r4 | 0;
    // 0x800BCD74: sw          $ra, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r31;
    // 0x800BCD78: sw          $s3, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r19;
    // 0x800BCD7C: sw          $s2, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r18;
    // 0x800BCD80: sw          $s0, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r16;
    // 0x800BCD84: addiu       $s5, $s5, 0x4688
    ctx->r21 = ADD32(ctx->r21, 0X4688);
    // 0x800BCD88: or          $s1, $zero, $zero
    ctx->r17 = 0 | 0;
    // 0x800BCD8C: addiu       $s6, $zero, 0x1
    ctx->r22 = ADD32(0, 0X1);
    // 0x800BCD90: addiu       $s7, $zero, 0x10
    ctx->r23 = ADD32(0, 0X10);
L_800BCD94:
    // 0x800BCD94: andi        $t7, $a1, 0x1
    ctx->r15 = ctx->r5 & 0X1;
    // 0x800BCD98: beq         $t7, $zero, L_800BCDD8
    if (ctx->r15 == 0) {
        // 0x800BCD9C: or          $s2, $a1, $zero
        ctx->r18 = ctx->r5 | 0;
            goto L_800BCDD8;
    }
    // 0x800BCD9C: or          $s2, $a1, $zero
    ctx->r18 = ctx->r5 | 0;
    // 0x800BCDA0: sll         $t8, $s1, 2
    ctx->r24 = S32(ctx->r17 << 2);
    // 0x800BCDA4: addu        $s3, $s4, $t8
    ctx->r19 = ADD32(ctx->r20, ctx->r24);
    // 0x800BCDA8: lw          $s0, 0x30($s3)
    ctx->r16 = MEM_W(ctx->r19, 0X30);
    // 0x800BCDAC: xor         $t9, $s0, $s5
    ctx->r25 = ctx->r16 ^ ctx->r21;
    // 0x800BCDB0: sltu        $t9, $zero, $t9
    ctx->r25 = 0 < ctx->r25 ? 1 : 0;
    // 0x800BCDB4: bnel        $s6, $t9, L_800BCDDC
    if (ctx->r22 != ctx->r25) {
        // 0x800BCDB8: sra         $a1, $s2, 1
        ctx->r5 = S32(SIGNED(ctx->r18) >> 1);
            goto L_800BCDDC;
    }
    goto skip_0;
    // 0x800BCDB8: sra         $a1, $s2, 1
    ctx->r5 = S32(SIGNED(ctx->r18) >> 1);
    skip_0:
    // 0x800BCDBC: lw          $t0, 0x44($s0)
    ctx->r8 = MEM_W(ctx->r16, 0X44);
    // 0x800BCDC0: bnel        $s4, $t0, L_800BCDD8
    if (ctx->r20 != ctx->r8) {
        // 0x800BCDC4: sw          $s5, 0x30($s3)
        MEM_W(0X30, ctx->r19) = ctx->r21;
            goto L_800BCDD8;
    }
    goto skip_1;
    // 0x800BCDC4: sw          $s5, 0x30($s3)
    MEM_W(0X30, ctx->r19) = ctx->r21;
    skip_1:
    // 0x800BCDC8: jal         0x800BCB34
    // 0x800BCDCC: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    AudioSeq_SequenceChannelDisable(rdram, ctx);
        goto after_0;
    // 0x800BCDCC: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_0:
    // 0x800BCDD0: sw          $zero, 0x44($s0)
    MEM_W(0X44, ctx->r16) = 0;
    // 0x800BCDD4: sw          $s5, 0x30($s3)
    MEM_W(0X30, ctx->r19) = ctx->r21;
L_800BCDD8:
    // 0x800BCDD8: sra         $a1, $s2, 1
    ctx->r5 = S32(SIGNED(ctx->r18) >> 1);
L_800BCDDC:
    // 0x800BCDDC: addiu       $s1, $s1, 0x1
    ctx->r17 = ADD32(ctx->r17, 0X1);
    // 0x800BCDE0: andi        $t1, $a1, 0xFFFF
    ctx->r9 = ctx->r5 & 0XFFFF;
    // 0x800BCDE4: bne         $s1, $s7, L_800BCD94
    if (ctx->r17 != ctx->r23) {
        // 0x800BCDE8: or          $a1, $t1, $zero
        ctx->r5 = ctx->r9 | 0;
            goto L_800BCD94;
    }
    // 0x800BCDE8: or          $a1, $t1, $zero
    ctx->r5 = ctx->r9 | 0;
    // 0x800BCDEC: lw          $ra, 0x34($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X34);
    // 0x800BCDF0: lw          $s0, 0x14($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X14);
    // 0x800BCDF4: lw          $s1, 0x18($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X18);
    // 0x800BCDF8: lw          $s2, 0x1C($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X1C);
    // 0x800BCDFC: lw          $s3, 0x20($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X20);
    // 0x800BCE00: lw          $s4, 0x24($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X24);
    // 0x800BCE04: lw          $s5, 0x28($sp)
    ctx->r21 = MEM_W(ctx->r29, 0X28);
    // 0x800BCE08: lw          $s6, 0x2C($sp)
    ctx->r22 = MEM_W(ctx->r29, 0X2C);
    // 0x800BCE0C: lw          $s7, 0x30($sp)
    ctx->r23 = MEM_W(ctx->r29, 0X30);
    // 0x800BCE10: jr          $ra
    // 0x800BCE14: addiu       $sp, $sp, 0x38
    ctx->r29 = ADD32(ctx->r29, 0X38);
    return;
    // 0x800BCE14: addiu       $sp, $sp, 0x38
    ctx->r29 = ADD32(ctx->r29, 0X38);
;}
RECOMP_FUNC void AudioSeq_SequenceChannelEnable(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800BCE18: addiu       $sp, $sp, -0x28
    ctx->r29 = ADD32(ctx->r29, -0X28);
    // 0x800BCE1C: andi        $t6, $a1, 0xFF
    ctx->r14 = ctx->r5 & 0XFF;
    // 0x800BCE20: sll         $t7, $t6, 2
    ctx->r15 = S32(ctx->r14 << 2);
    // 0x800BCE24: sw          $ra, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r31;
    // 0x800BCE28: sw          $s3, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r19;
    // 0x800BCE2C: sw          $s2, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r18;
    // 0x800BCE30: sw          $s1, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r17;
    // 0x800BCE34: sw          $s0, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r16;
    // 0x800BCE38: sw          $a1, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r5;
    // 0x800BCE3C: addu        $t8, $a0, $t7
    ctx->r24 = ADD32(ctx->r4, ctx->r15);
    // 0x800BCE40: lw          $s2, 0x30($t8)
    ctx->r18 = MEM_W(ctx->r24, 0X30);
    // 0x800BCE44: lui         $t9, 0x8004
    ctx->r25 = S32(0X8004 << 16);
    // 0x800BCE48: addiu       $t9, $t9, 0x4688
    ctx->r25 = ADD32(ctx->r25, 0X4688);
    // 0x800BCE4C: bne         $s2, $t9, L_800BCE78
    if (ctx->r18 != ctx->r25) {
        // 0x800BCE50: or          $s0, $zero, $zero
        ctx->r16 = 0 | 0;
            goto L_800BCE78;
    }
    // 0x800BCE50: or          $s0, $zero, $zero
    ctx->r16 = 0 | 0;
    // 0x800BCE54: lui         $t1, 0x8004
    ctx->r9 = S32(0X8004 << 16);
    // 0x800BCE58: addiu       $t1, $t1, -0x338
    ctx->r9 = ADD32(ctx->r9, -0X338);
    // 0x800BCE5C: beq         $a0, $t1, L_800BCEC4
    if (ctx->r4 == ctx->r9) {
        // 0x800BCE60: lui         $t2, 0x8004
        ctx->r10 = S32(0X8004 << 16);
            goto L_800BCEC4;
    }
    // 0x800BCE60: lui         $t2, 0x8004
    ctx->r10 = S32(0X8004 << 16);
    // 0x800BCE64: addiu       $t2, $t2, -0x1F8
    ctx->r10 = ADD32(ctx->r10, -0X1F8);
    // 0x800BCE68: bnel        $a0, $t2, L_800BCEC8
    if (ctx->r4 != ctx->r10) {
        // 0x800BCE6C: lw          $ra, 0x24($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X24);
            goto L_800BCEC8;
    }
    goto skip_0;
    // 0x800BCE6C: lw          $ra, 0x24($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X24);
    skip_0:
    // 0x800BCE70: b           L_800BCEC8
    // 0x800BCE74: lw          $ra, 0x24($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X24);
        goto L_800BCEC8;
    // 0x800BCE74: lw          $ra, 0x24($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X24);
L_800BCE78:
    // 0x800BCE78: lbu         $t4, 0x0($s2)
    ctx->r12 = MEM_BU(ctx->r18, 0X0);
    // 0x800BCE7C: sb          $zero, 0x78($s2)
    MEM_B(0X78, ctx->r18) = 0;
    // 0x800BCE80: sw          $a2, 0x60($s2)
    MEM_W(0X60, ctx->r18) = ctx->r6;
    // 0x800BCE84: ori         $t6, $t4, 0x80
    ctx->r14 = ctx->r12 | 0X80;
    // 0x800BCE88: sb          $t6, 0x0($s2)
    MEM_B(0X0, ctx->r18) = ctx->r14;
    // 0x800BCE8C: andi        $t7, $t6, 0xBF
    ctx->r15 = ctx->r14 & 0XBF;
    // 0x800BCE90: sb          $t7, 0x0($s2)
    MEM_B(0X0, ctx->r18) = ctx->r15;
    // 0x800BCE94: sh          $zero, 0x1A($s2)
    MEM_H(0X1A, ctx->r18) = 0;
    // 0x800BCE98: or          $s1, $s2, $zero
    ctx->r17 = ctx->r18 | 0;
    // 0x800BCE9C: addiu       $s3, $zero, 0x4
    ctx->r19 = ADD32(0, 0X4);
L_800BCEA0:
    // 0x800BCEA0: lw          $t8, 0x48($s1)
    ctx->r24 = MEM_W(ctx->r17, 0X48);
    // 0x800BCEA4: or          $a0, $s2, $zero
    ctx->r4 = ctx->r18 | 0;
    // 0x800BCEA8: beql        $t8, $zero, L_800BCEBC
    if (ctx->r24 == 0) {
        // 0x800BCEAC: addiu       $s0, $s0, 0x1
        ctx->r16 = ADD32(ctx->r16, 0X1);
            goto L_800BCEBC;
    }
    goto skip_1;
    // 0x800BCEAC: addiu       $s0, $s0, 0x1
    ctx->r16 = ADD32(ctx->r16, 0X1);
    skip_1:
    // 0x800BCEB0: jal         0x800BCAE4
    // 0x800BCEB4: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    AudioSeq_SeqLayerFree(rdram, ctx);
        goto after_0;
    // 0x800BCEB4: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    after_0:
    // 0x800BCEB8: addiu       $s0, $s0, 0x1
    ctx->r16 = ADD32(ctx->r16, 0X1);
L_800BCEBC:
    // 0x800BCEBC: bne         $s0, $s3, L_800BCEA0
    if (ctx->r16 != ctx->r19) {
        // 0x800BCEC0: addiu       $s1, $s1, 0x4
        ctx->r17 = ADD32(ctx->r17, 0X4);
            goto L_800BCEA0;
    }
    // 0x800BCEC0: addiu       $s1, $s1, 0x4
    ctx->r17 = ADD32(ctx->r17, 0X4);
L_800BCEC4:
    // 0x800BCEC4: lw          $ra, 0x24($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X24);
L_800BCEC8:
    // 0x800BCEC8: lw          $s0, 0x14($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X14);
    // 0x800BCECC: lw          $s1, 0x18($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X18);
    // 0x800BCED0: lw          $s2, 0x1C($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X1C);
    // 0x800BCED4: lw          $s3, 0x20($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X20);
    // 0x800BCED8: jr          $ra
    // 0x800BCEDC: addiu       $sp, $sp, 0x28
    ctx->r29 = ADD32(ctx->r29, 0X28);
    return;
    // 0x800BCEDC: addiu       $sp, $sp, 0x28
    ctx->r29 = ADD32(ctx->r29, 0X28);
;}
RECOMP_FUNC void AudioSeq_SequencePlayerDisable(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800BCEE0: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800BCEE4: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800BCEE8: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    // 0x800BCEEC: jal         0x800BCD48
    // 0x800BCEF0: ori         $a1, $zero, 0xFFFF
    ctx->r5 = 0 | 0XFFFF;
    AudioSeq_SequencePlayerDisableChannels(rdram, ctx);
        goto after_0;
    // 0x800BCEF0: ori         $a1, $zero, 0xFFFF
    ctx->r5 = 0 | 0XFFFF;
    after_0:
    // 0x800BCEF4: lw          $a2, 0x18($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X18);
    // 0x800BCEF8: jal         0x800BB400
    // 0x800BCEFC: addiu       $a0, $a2, 0x94
    ctx->r4 = ADD32(ctx->r6, 0X94);
    Audio_NotePoolClear(rdram, ctx);
        goto after_1;
    // 0x800BCEFC: addiu       $a0, $a2, 0x94
    ctx->r4 = ADD32(ctx->r6, 0X94);
    after_1:
    // 0x800BCF00: lw          $a2, 0x18($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X18);
    // 0x800BCF04: lui         $t2, 0x8004
    ctx->r10 = S32(0X8004 << 16);
    // 0x800BCF08: addiu       $t2, $t2, -0x1448
    ctx->r10 = ADD32(ctx->r10, -0X1448);
    // 0x800BCF0C: lbu         $t7, 0x0($a2)
    ctx->r15 = MEM_BU(ctx->r6, 0X0);
    // 0x800BCF10: lbu         $t1, 0x4($a2)
    ctx->r9 = MEM_BU(ctx->r6, 0X4);
    // 0x800BCF14: lui         $a0, 0x8004
    ctx->r4 = S32(0X8004 << 16);
    // 0x800BCF18: ori         $t9, $t7, 0x40
    ctx->r25 = ctx->r15 | 0X40;
    // 0x800BCF1C: andi        $t0, $t9, 0x7F
    ctx->r8 = ctx->r25 & 0X7F;
    // 0x800BCF20: sb          $t9, 0x0($a2)
    MEM_B(0X0, ctx->r6) = ctx->r25;
    // 0x800BCF24: sb          $t0, 0x0($a2)
    MEM_B(0X0, ctx->r6) = ctx->r8;
    // 0x800BCF28: addu        $v0, $t1, $t2
    ctx->r2 = ADD32(ctx->r9, ctx->r10);
    // 0x800BCF2C: lbu         $t3, 0x0($v0)
    ctx->r11 = MEM_BU(ctx->r2, 0X0);
    // 0x800BCF30: addiu       $t4, $zero, 0x3
    ctx->r12 = ADD32(0, 0X3);
    // 0x800BCF34: addiu       $t7, $zero, 0x4
    ctx->r15 = ADD32(0, 0X4);
    // 0x800BCF38: slti        $at, $t3, 0x2
    ctx->r1 = SIGNED(ctx->r11) < 0X2 ? 1 : 0;
    // 0x800BCF3C: bne         $at, $zero, L_800BCF48
    if (ctx->r1 != 0) {
        // 0x800BCF40: addiu       $a0, $a0, -0x1860
        ctx->r4 = ADD32(ctx->r4, -0X1860);
            goto L_800BCF48;
    }
    // 0x800BCF40: addiu       $a0, $a0, -0x1860
    ctx->r4 = ADD32(ctx->r4, -0X1860);
    // 0x800BCF44: sb          $t4, 0x0($v0)
    MEM_B(0X0, ctx->r2) = ctx->r12;
L_800BCF48:
    // 0x800BCF48: lbu         $v0, 0x5($a2)
    ctx->r2 = MEM_BU(ctx->r6, 0X5);
    // 0x800BCF4C: lui         $t5, 0x8004
    ctx->r13 = S32(0X8004 << 16);
    // 0x800BCF50: addiu       $t5, $t5, -0x1488
    ctx->r13 = ADD32(ctx->r13, -0X1488);
    // 0x800BCF54: addu        $v1, $v0, $t5
    ctx->r3 = ADD32(ctx->r2, ctx->r13);
    // 0x800BCF58: lbu         $t6, 0x0($v1)
    ctx->r14 = MEM_BU(ctx->r3, 0X0);
    // 0x800BCF5C: addiu       $t9, $zero, 0x1
    ctx->r25 = ADD32(0, 0X1);
    // 0x800BCF60: slti        $at, $t6, 0x2
    ctx->r1 = SIGNED(ctx->r14) < 0X2 ? 1 : 0;
    // 0x800BCF64: bnel        $at, $zero, L_800BCF78
    if (ctx->r1 != 0) {
        // 0x800BCF68: lw          $t8, 0x1B0($a0)
        ctx->r24 = MEM_W(ctx->r4, 0X1B0);
            goto L_800BCF78;
    }
    goto skip_0;
    // 0x800BCF68: lw          $t8, 0x1B0($a0)
    ctx->r24 = MEM_W(ctx->r4, 0X1B0);
    skip_0:
    // 0x800BCF6C: sb          $t7, 0x0($v1)
    MEM_B(0X0, ctx->r3) = ctx->r15;
    // 0x800BCF70: lbu         $v0, 0x5($a2)
    ctx->r2 = MEM_BU(ctx->r6, 0X5);
    // 0x800BCF74: lw          $t8, 0x1B0($a0)
    ctx->r24 = MEM_W(ctx->r4, 0X1B0);
L_800BCF78:
    // 0x800BCF78: or          $v1, $v0, $zero
    ctx->r3 = ctx->r2 | 0;
    // 0x800BCF7C: bnel        $v0, $t8, L_800BCF90
    if (ctx->r2 != ctx->r24) {
        // 0x800BCF80: lw          $t0, 0x1BC($a0)
        ctx->r8 = MEM_W(ctx->r4, 0X1BC);
            goto L_800BCF90;
    }
    goto skip_1;
    // 0x800BCF80: lw          $t0, 0x1BC($a0)
    ctx->r8 = MEM_W(ctx->r4, 0X1BC);
    skip_1:
    // 0x800BCF84: b           L_800BCF9C
    // 0x800BCF88: sw          $t9, 0x194($a0)
    MEM_W(0X194, ctx->r4) = ctx->r25;
        goto L_800BCF9C;
    // 0x800BCF88: sw          $t9, 0x194($a0)
    MEM_W(0X194, ctx->r4) = ctx->r25;
    // 0x800BCF8C: lw          $t0, 0x1BC($a0)
    ctx->r8 = MEM_W(ctx->r4, 0X1BC);
L_800BCF90:
    // 0x800BCF90: bnel        $v1, $t0, L_800BCFA0
    if (ctx->r3 != ctx->r8) {
        // 0x800BCF94: lw          $ra, 0x14($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X14);
            goto L_800BCFA0;
    }
    goto skip_2;
    // 0x800BCF94: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    skip_2:
    // 0x800BCF98: sw          $zero, 0x194($a0)
    MEM_W(0X194, ctx->r4) = 0;
L_800BCF9C:
    // 0x800BCF9C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_800BCFA0:
    // 0x800BCFA0: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800BCFA4: jr          $ra
    // 0x800BCFA8: nop

    return;
    // 0x800BCFA8: nop

;}
RECOMP_FUNC void AudioSeq_AudioListPushBack(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800BCFAC: lw          $t6, 0x0($a1)
    ctx->r14 = MEM_W(ctx->r5, 0X0);
    // 0x800BCFB0: bne         $t6, $zero, L_800BCFE4
    if (ctx->r14 != 0) {
        // 0x800BCFB4: nop
    
            goto L_800BCFE4;
    }
    // 0x800BCFB4: nop

    // 0x800BCFB8: lw          $t7, 0x0($a0)
    ctx->r15 = MEM_W(ctx->r4, 0X0);
    // 0x800BCFBC: sw          $a1, 0x4($t7)
    MEM_W(0X4, ctx->r15) = ctx->r5;
    // 0x800BCFC0: lw          $t8, 0x0($a0)
    ctx->r24 = MEM_W(ctx->r4, 0X0);
    // 0x800BCFC4: sw          $a0, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r4;
    // 0x800BCFC8: sw          $t8, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r24;
    // 0x800BCFCC: lw          $t9, 0x8($a0)
    ctx->r25 = MEM_W(ctx->r4, 0X8);
    // 0x800BCFD0: lw          $t1, 0xC($a0)
    ctx->r9 = MEM_W(ctx->r4, 0XC);
    // 0x800BCFD4: sw          $a1, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r5;
    // 0x800BCFD8: addiu       $t0, $t9, 0x1
    ctx->r8 = ADD32(ctx->r25, 0X1);
    // 0x800BCFDC: sw          $t0, 0x8($a0)
    MEM_W(0X8, ctx->r4) = ctx->r8;
    // 0x800BCFE0: sw          $t1, 0xC($a1)
    MEM_W(0XC, ctx->r5) = ctx->r9;
L_800BCFE4:
    // 0x800BCFE4: jr          $ra
    // 0x800BCFE8: nop

    return;
    // 0x800BCFE8: nop

;}
RECOMP_FUNC void AudioSeq_AudioListPopBack(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800BCFEC: lw          $v1, 0x0($a0)
    ctx->r3 = MEM_W(ctx->r4, 0X0);
    // 0x800BCFF0: bnel        $v1, $a0, L_800BD004
    if (ctx->r3 != ctx->r4) {
        // 0x800BCFF4: lw          $t6, 0x0($v1)
        ctx->r14 = MEM_W(ctx->r3, 0X0);
            goto L_800BD004;
    }
    goto skip_0;
    // 0x800BCFF4: lw          $t6, 0x0($v1)
    ctx->r14 = MEM_W(ctx->r3, 0X0);
    skip_0:
    // 0x800BCFF8: jr          $ra
    // 0x800BCFFC: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    return;
    // 0x800BCFFC: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    // 0x800BD000: lw          $t6, 0x0($v1)
    ctx->r14 = MEM_W(ctx->r3, 0X0);
L_800BD004:
    // 0x800BD004: sw          $a0, 0x4($t6)
    MEM_W(0X4, ctx->r14) = ctx->r4;
    // 0x800BD008: lw          $t7, 0x0($v1)
    ctx->r15 = MEM_W(ctx->r3, 0X0);
    // 0x800BD00C: sw          $t7, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r15;
    // 0x800BD010: sw          $zero, 0x0($v1)
    MEM_W(0X0, ctx->r3) = 0;
    // 0x800BD014: lw          $t8, 0x8($a0)
    ctx->r24 = MEM_W(ctx->r4, 0X8);
    // 0x800BD018: addiu       $t9, $t8, -0x1
    ctx->r25 = ADD32(ctx->r24, -0X1);
    // 0x800BD01C: sw          $t9, 0x8($a0)
    MEM_W(0X8, ctx->r4) = ctx->r25;
    // 0x800BD020: lw          $v0, 0x8($v1)
    ctx->r2 = MEM_W(ctx->r3, 0X8);
    // 0x800BD024: jr          $ra
    // 0x800BD028: nop

    return;
    // 0x800BD028: nop

;}
RECOMP_FUNC void AudioSeq_InitLayerFreelist(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800BD02C: addiu       $sp, $sp, -0x28
    ctx->r29 = ADD32(ctx->r29, -0X28);
    // 0x800BD030: sw          $s2, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r18;
    // 0x800BD034: lui         $s2, 0x8004
    ctx->r18 = S32(0X8004 << 16);
    // 0x800BD038: addiu       $s2, $s2, 0x4750
    ctx->r18 = ADD32(ctx->r18, 0X4750);
    // 0x800BD03C: sw          $s3, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r19;
    // 0x800BD040: sw          $s1, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r17;
    // 0x800BD044: sw          $s0, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r16;
    // 0x800BD048: lui         $s0, 0x8004
    ctx->r16 = S32(0X8004 << 16);
    // 0x800BD04C: lui         $s1, 0x8004
    ctx->r17 = S32(0X8004 << 16);
    // 0x800BD050: lui         $s3, 0x8004
    ctx->r19 = S32(0X8004 << 16);
    // 0x800BD054: sw          $ra, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r31;
    // 0x800BD058: sw          $s2, 0x0($s2)
    MEM_W(0X0, ctx->r18) = ctx->r18;
    // 0x800BD05C: sw          $s2, 0x4($s2)
    MEM_W(0X4, ctx->r18) = ctx->r18;
    // 0x800BD060: sw          $zero, 0x8($s2)
    MEM_W(0X8, ctx->r18) = 0;
    // 0x800BD064: sw          $zero, 0xC($s2)
    MEM_W(0XC, ctx->r18) = 0;
    // 0x800BD068: addiu       $s3, $s3, 0x46F4
    ctx->r19 = ADD32(ctx->r19, 0X46F4);
    // 0x800BD06C: addiu       $s1, $s1, 0x26F4
    ctx->r17 = ADD32(ctx->r17, 0X26F4);
    // 0x800BD070: addiu       $s0, $s0, 0x2688
    ctx->r16 = ADD32(ctx->r16, 0X2688);
L_800BD074:
    // 0x800BD074: sw          $s0, 0x74($s0)
    MEM_W(0X74, ctx->r16) = ctx->r16;
    // 0x800BD078: sw          $zero, 0x6C($s0)
    MEM_W(0X6C, ctx->r16) = 0;
    // 0x800BD07C: or          $a0, $s2, $zero
    ctx->r4 = ctx->r18 | 0;
    // 0x800BD080: jal         0x800BCFAC
    // 0x800BD084: or          $a1, $s1, $zero
    ctx->r5 = ctx->r17 | 0;
    AudioSeq_AudioListPushBack(rdram, ctx);
        goto after_0;
    // 0x800BD084: or          $a1, $s1, $zero
    ctx->r5 = ctx->r17 | 0;
    after_0:
    // 0x800BD088: addiu       $s1, $s1, 0x80
    ctx->r17 = ADD32(ctx->r17, 0X80);
    // 0x800BD08C: bne         $s1, $s3, L_800BD074
    if (ctx->r17 != ctx->r19) {
        // 0x800BD090: addiu       $s0, $s0, 0x80
        ctx->r16 = ADD32(ctx->r16, 0X80);
            goto L_800BD074;
    }
    // 0x800BD090: addiu       $s0, $s0, 0x80
    ctx->r16 = ADD32(ctx->r16, 0X80);
    // 0x800BD094: lw          $ra, 0x24($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X24);
    // 0x800BD098: lw          $s0, 0x14($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X14);
    // 0x800BD09C: lw          $s1, 0x18($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X18);
    // 0x800BD0A0: lw          $s2, 0x1C($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X1C);
    // 0x800BD0A4: lw          $s3, 0x20($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X20);
    // 0x800BD0A8: jr          $ra
    // 0x800BD0AC: addiu       $sp, $sp, 0x28
    ctx->r29 = ADD32(ctx->r29, 0X28);
    return;
    // 0x800BD0AC: addiu       $sp, $sp, 0x28
    ctx->r29 = ADD32(ctx->r29, 0X28);
;}
RECOMP_FUNC void AudioSeq_ScriptReadU8(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800BD0B0: lw          $a1, 0x0($a0)
    ctx->r5 = MEM_W(ctx->r4, 0X0);
    // 0x800BD0B4: lbu         $v0, 0x0($a1)
    ctx->r2 = MEM_BU(ctx->r5, 0X0);
    // 0x800BD0B8: addiu       $t6, $a1, 0x1
    ctx->r14 = ADD32(ctx->r5, 0X1);
    // 0x800BD0BC: jr          $ra
    // 0x800BD0C0: sw          $t6, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r14;
    return;
    // 0x800BD0C0: sw          $t6, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r14;
;}
RECOMP_FUNC void AudioSeq_ScriptReadS16(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800BD0C4: lw          $a1, 0x0($a0)
    ctx->r5 = MEM_W(ctx->r4, 0X0);
    // 0x800BD0C8: lbu         $v1, 0x0($a1)
    ctx->r3 = MEM_BU(ctx->r5, 0X0);
    // 0x800BD0CC: addiu       $t9, $a1, 0x1
    ctx->r25 = ADD32(ctx->r5, 0X1);
    // 0x800BD0D0: sw          $t9, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r25;
    // 0x800BD0D4: lbu         $t0, 0x0($t9)
    ctx->r8 = MEM_BU(ctx->r25, 0X0);
    // 0x800BD0D8: sll         $t8, $v1, 8
    ctx->r24 = S32(ctx->r3 << 8);
    // 0x800BD0DC: addiu       $t3, $t9, 0x1
    ctx->r11 = ADD32(ctx->r25, 0X1);
    // 0x800BD0E0: or          $v1, $t0, $t8
    ctx->r3 = ctx->r8 | ctx->r24;
    // 0x800BD0E4: sll         $t1, $v1, 16
    ctx->r9 = S32(ctx->r3 << 16);
    // 0x800BD0E8: sra         $v0, $t1, 16
    ctx->r2 = S32(SIGNED(ctx->r9) >> 16);
    // 0x800BD0EC: jr          $ra
    // 0x800BD0F0: sw          $t3, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r11;
    return;
    // 0x800BD0F0: sw          $t3, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r11;
;}
RECOMP_FUNC void AudioSeq_ScriptReadCompressedU16(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800BD0F4: lw          $v0, 0x0($a0)
    ctx->r2 = MEM_W(ctx->r4, 0X0);
    // 0x800BD0F8: lbu         $v1, 0x0($v0)
    ctx->r3 = MEM_BU(ctx->r2, 0X0);
    // 0x800BD0FC: addiu       $t6, $v0, 0x1
    ctx->r14 = ADD32(ctx->r2, 0X1);
    // 0x800BD100: sw          $t6, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r14;
    // 0x800BD104: andi        $t7, $v1, 0x80
    ctx->r15 = ctx->r3 & 0X80;
    // 0x800BD108: beq         $t7, $zero, L_800BD130
    if (ctx->r15 == 0) {
        // 0x800BD10C: or          $a1, $v1, $zero
        ctx->r5 = ctx->r3 | 0;
            goto L_800BD130;
    }
    // 0x800BD10C: or          $a1, $v1, $zero
    ctx->r5 = ctx->r3 | 0;
    // 0x800BD110: lbu         $t0, 0x0($t6)
    ctx->r8 = MEM_BU(ctx->r14, 0X0);
    // 0x800BD114: sll         $v1, $a1, 8
    ctx->r3 = S32(ctx->r5 << 8);
    // 0x800BD118: andi        $t9, $v1, 0x7F00
    ctx->r25 = ctx->r3 & 0X7F00;
    // 0x800BD11C: or          $v1, $t0, $t9
    ctx->r3 = ctx->r8 | ctx->r25;
    // 0x800BD120: andi        $t1, $v1, 0xFFFF
    ctx->r9 = ctx->r3 & 0XFFFF;
    // 0x800BD124: addiu       $t2, $t6, 0x1
    ctx->r10 = ADD32(ctx->r14, 0X1);
    // 0x800BD128: sw          $t2, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r10;
    // 0x800BD12C: or          $v1, $t1, $zero
    ctx->r3 = ctx->r9 | 0;
L_800BD130:
    // 0x800BD130: jr          $ra
    // 0x800BD134: or          $v0, $v1, $zero
    ctx->r2 = ctx->r3 | 0;
    return;
    // 0x800BD134: or          $v0, $v1, $zero
    ctx->r2 = ctx->r3 | 0;
;}
RECOMP_FUNC void AudioSeq_SeqLayerProcessScript(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800BD138: addiu       $sp, $sp, -0x70
    ctx->r29 = ADD32(ctx->r29, -0X70);
    // 0x800BD13C: addiu       $t6, $zero, 0x1
    ctx->r14 = ADD32(0, 0X1);
    // 0x800BD140: sw          $ra, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r31;
    // 0x800BD144: sw          $s4, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r20;
    // 0x800BD148: sw          $s3, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r19;
    // 0x800BD14C: sw          $s2, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r18;
    // 0x800BD150: sw          $s1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r17;
    // 0x800BD154: sw          $s0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r16;
    // 0x800BD158: sw          $t6, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r14;
    // 0x800BD15C: lw          $v0, 0x0($a0)
    ctx->r2 = MEM_W(ctx->r4, 0X0);
    // 0x800BD160: or          $s1, $a0, $zero
    ctx->r17 = ctx->r4 | 0;
    // 0x800BD164: srl         $t7, $v0, 31
    ctx->r15 = S32(U32(ctx->r2) >> 31);
    // 0x800BD168: beql        $t7, $zero, L_800BDBD0
    if (ctx->r15 == 0) {
        // 0x800BD16C: lw          $ra, 0x2C($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X2C);
            goto L_800BDBD0;
    }
    goto skip_0;
    // 0x800BD16C: lw          $ra, 0x2C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X2C);
    skip_0:
    // 0x800BD170: lh          $v1, 0x38($a0)
    ctx->r3 = MEM_H(ctx->r4, 0X38);
    // 0x800BD174: sll         $t0, $v0, 2
    ctx->r8 = S32(ctx->r2 << 2);
    // 0x800BD178: sll         $t7, $v0, 3
    ctx->r15 = S32(ctx->r2 << 3);
    // 0x800BD17C: slti        $at, $v1, 0x2
    ctx->r1 = SIGNED(ctx->r3) < 0X2 ? 1 : 0;
    // 0x800BD180: bne         $at, $zero, L_800BD1BC
    if (ctx->r1 != 0) {
        // 0x800BD184: addiu       $t8, $v1, -0x1
        ctx->r24 = ADD32(ctx->r3, -0X1);
            goto L_800BD1BC;
    }
    // 0x800BD184: addiu       $t8, $v1, -0x1
    ctx->r24 = ADD32(ctx->r3, -0X1);
    // 0x800BD188: bltz        $t0, L_800BDBCC
    if (SIGNED(ctx->r8) < 0) {
        // 0x800BD18C: sh          $t8, 0x38($a0)
        MEM_H(0X38, ctx->r4) = ctx->r24;
            goto L_800BDBCC;
    }
    // 0x800BD18C: sh          $t8, 0x38($a0)
    MEM_H(0X38, ctx->r4) = ctx->r24;
    // 0x800BD190: lh          $t1, 0x3A($a0)
    ctx->r9 = MEM_H(ctx->r4, 0X3A);
    // 0x800BD194: lh          $t2, 0x38($a0)
    ctx->r10 = MEM_H(ctx->r4, 0X38);
    // 0x800BD198: slt         $at, $t1, $t2
    ctx->r1 = SIGNED(ctx->r9) < SIGNED(ctx->r10) ? 1 : 0;
    // 0x800BD19C: bnel        $at, $zero, L_800BDBD0
    if (ctx->r1 != 0) {
        // 0x800BD1A0: lw          $ra, 0x2C($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X2C);
            goto L_800BDBD0;
    }
    goto skip_1;
    // 0x800BD1A0: lw          $ra, 0x2C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X2C);
    skip_1:
    // 0x800BD1A4: jal         0x800BB108
    // 0x800BD1A8: nop

    Audio_SeqLayerNoteDecay(rdram, ctx);
        goto after_0;
    // 0x800BD1A8: nop

    after_0:
    // 0x800BD1AC: lbu         $t4, 0x0($s1)
    ctx->r12 = MEM_BU(ctx->r17, 0X0);
    // 0x800BD1B0: ori         $t5, $t4, 0x20
    ctx->r13 = ctx->r12 | 0X20;
    // 0x800BD1B4: b           L_800BDBCC
    // 0x800BD1B8: sb          $t5, 0x0($s1)
    MEM_B(0X0, ctx->r17) = ctx->r13;
        goto L_800BDBCC;
    // 0x800BD1B8: sb          $t5, 0x0($s1)
    MEM_B(0X0, ctx->r17) = ctx->r13;
L_800BD1BC:
    // 0x800BD1BC: bltzl       $t7, L_800BD1D0
    if (SIGNED(ctx->r15) < 0) {
        // 0x800BD1C0: lbu         $v0, 0x8($s1)
        ctx->r2 = MEM_BU(ctx->r17, 0X8);
            goto L_800BD1D0;
    }
    goto skip_2;
    // 0x800BD1C0: lbu         $v0, 0x8($s1)
    ctx->r2 = MEM_BU(ctx->r17, 0X8);
    skip_2:
    // 0x800BD1C4: jal         0x800BB108
    // 0x800BD1C8: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    Audio_SeqLayerNoteDecay(rdram, ctx);
        goto after_1;
    // 0x800BD1C8: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    after_1:
    // 0x800BD1CC: lbu         $v0, 0x8($s1)
    ctx->r2 = MEM_BU(ctx->r17, 0X8);
L_800BD1D0:
    // 0x800BD1D0: addiu       $at, $zero, -0x81
    ctx->r1 = ADD32(0, -0X81);
    // 0x800BD1D4: and         $t8, $v0, $at
    ctx->r24 = ctx->r2 & ctx->r1;
    // 0x800BD1D8: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x800BD1DC: beq         $t8, $at, L_800BD1EC
    if (ctx->r24 == ctx->r1) {
        // 0x800BD1E0: addiu       $at, $zero, 0x2
        ctx->r1 = ADD32(0, 0X2);
            goto L_800BD1EC;
    }
    // 0x800BD1E0: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x800BD1E4: bnel        $t8, $at, L_800BD1F4
    if (ctx->r24 != ctx->r1) {
        // 0x800BD1E8: lw          $v0, 0x4C($s1)
        ctx->r2 = MEM_W(ctx->r17, 0X4C);
            goto L_800BD1F4;
    }
    goto skip_3;
    // 0x800BD1E8: lw          $v0, 0x4C($s1)
    ctx->r2 = MEM_W(ctx->r17, 0X4C);
    skip_3:
L_800BD1EC:
    // 0x800BD1EC: sb          $zero, 0x8($s1)
    MEM_B(0X8, ctx->r17) = 0;
    // 0x800BD1F0: lw          $v0, 0x4C($s1)
    ctx->r2 = MEM_W(ctx->r17, 0X4C);
L_800BD1F4:
    // 0x800BD1F4: lbu         $t0, 0x0($s1)
    ctx->r8 = MEM_BU(ctx->r17, 0X0);
    // 0x800BD1F8: addiu       $s0, $s1, 0x50
    ctx->r16 = ADD32(ctx->r17, 0X50);
    // 0x800BD1FC: lw          $s4, 0x44($v0)
    ctx->r20 = MEM_W(ctx->r2, 0X44);
    // 0x800BD200: ori         $t1, $t0, 0x4
    ctx->r9 = ctx->r8 | 0X4;
    // 0x800BD204: sb          $t1, 0x0($s1)
    MEM_B(0X0, ctx->r17) = ctx->r9;
    // 0x800BD208: lhu         $s3, 0x4A($sp)
    ctx->r19 = MEM_HU(ctx->r29, 0X4A);
    // 0x800BD20C: sw          $v0, 0x68($sp)
    MEM_W(0X68, ctx->r29) = ctx->r2;
L_800BD210:
    // 0x800BD210: jal         0x800BD0B0
    // 0x800BD214: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    AudioSeq_ScriptReadU8(rdram, ctx);
        goto after_2;
    // 0x800BD214: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_2:
    // 0x800BD218: slti        $at, $v0, 0xC1
    ctx->r1 = SIGNED(ctx->r2) < 0XC1 ? 1 : 0;
    // 0x800BD21C: andi        $s2, $v0, 0xFF
    ctx->r18 = ctx->r2 & 0XFF;
    // 0x800BD220: bne         $at, $zero, L_800BD600
    if (ctx->r1 != 0) {
        // 0x800BD224: or          $a1, $v0, $zero
        ctx->r5 = ctx->r2 | 0;
            goto L_800BD600;
    }
    // 0x800BD224: or          $a1, $v0, $zero
    ctx->r5 = ctx->r2 | 0;
    // 0x800BD228: slti        $at, $v0, 0xCD
    ctx->r1 = SIGNED(ctx->r2) < 0XCD ? 1 : 0;
    // 0x800BD22C: bne         $at, $zero, L_800BD258
    if (ctx->r1 != 0) {
        // 0x800BD230: addiu       $t3, $a1, -0xC1
        ctx->r11 = ADD32(ctx->r5, -0XC1);
            goto L_800BD258;
    }
    // 0x800BD230: addiu       $t3, $a1, -0xC1
    ctx->r11 = ADD32(ctx->r5, -0XC1);
    // 0x800BD234: addiu       $t2, $v0, -0xF4
    ctx->r10 = ADD32(ctx->r2, -0XF4);
    // 0x800BD238: sltiu       $at, $t2, 0xC
    ctx->r1 = ctx->r10 < 0XC ? 1 : 0;
    // 0x800BD23C: beq         $at, $zero, L_800BD59C
    if (ctx->r1 == 0) {
        // 0x800BD240: sll         $t2, $t2, 2
        ctx->r10 = S32(ctx->r10 << 2);
            goto L_800BD59C;
    }
    // 0x800BD240: sll         $t2, $t2, 2
    ctx->r10 = S32(ctx->r10 << 2);
    // 0x800BD244: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x800BD248: addu        $at, $at, $t2
    gpr jr_addend_800BD250 = ctx->r10;
    ctx->r1 = ADD32(ctx->r1, ctx->r10);
    // 0x800BD24C: lw          $t2, -0x4340($at)
    ctx->r10 = ADD32(ctx->r1, -0X4340);
    // 0x800BD250: jr          $t2
    // 0x800BD254: nop

    switch (jr_addend_800BD250 >> 2) {
        case 0: goto L_800BD390; break;
        case 1: goto L_800BD59C; break;
        case 2: goto L_800BD59C; break;
        case 3: goto L_800BD328; break;
        case 4: goto L_800BD2F0; break;
        case 5: goto L_800BD59C; break;
        case 6: goto L_800BD59C; break;
        case 7: goto L_800BD370; break;
        case 8: goto L_800BD2B0; break;
        case 9: goto L_800BD59C; break;
        case 10: goto L_800BD59C; break;
        case 11: goto L_800BD278; break;
        default: switch_error(__func__, 0x800BD250, 0x800EBCC0);
    }
    // 0x800BD254: nop

L_800BD258:
    // 0x800BD258: sltiu       $at, $t3, 0xC
    ctx->r1 = ctx->r11 < 0XC ? 1 : 0;
    // 0x800BD25C: beq         $at, $zero, L_800BD59C
    if (ctx->r1 == 0) {
        // 0x800BD260: sll         $t3, $t3, 2
        ctx->r11 = S32(ctx->r11 << 2);
            goto L_800BD59C;
    }
    // 0x800BD260: sll         $t3, $t3, 2
    ctx->r11 = S32(ctx->r11 << 2);
    // 0x800BD264: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x800BD268: addu        $at, $at, $t3
    gpr jr_addend_800BD270 = ctx->r11;
    ctx->r1 = ADD32(ctx->r1, ctx->r11);
    // 0x800BD26C: lw          $t3, -0x4310($at)
    ctx->r11 = ADD32(ctx->r1, -0X4310);
    // 0x800BD270: jr          $t3
    // 0x800BD274: nop

    switch (jr_addend_800BD270 >> 2) {
        case 0: goto L_800BD3B0; break;
        case 1: goto L_800BD3EC; break;
        case 2: goto L_800BD44C; break;
        case 3: goto L_800BD414; break;
        case 4: goto L_800BD414; break;
        case 5: goto L_800BD460; break;
        case 6: goto L_800BD4D0; break;
        case 7: goto L_800BD558; break;
        case 8: goto L_800BD3EC; break;
        case 9: goto L_800BD3B0; break;
        case 10: goto L_800BD560; break;
        case 11: goto L_800BD58C; break;
        default: switch_error(__func__, 0x800BD270, 0x800EBCF0);
    }
    // 0x800BD274: nop

L_800BD278:
    // 0x800BD278: lbu         $v1, 0x18($s0)
    ctx->r3 = MEM_BU(ctx->r16, 0X18);
    // 0x800BD27C: bne         $v1, $zero, L_800BD294
    if (ctx->r3 != 0) {
        // 0x800BD280: addiu       $v0, $v1, -0x1
        ctx->r2 = ADD32(ctx->r3, -0X1);
            goto L_800BD294;
    }
    // 0x800BD280: addiu       $v0, $v1, -0x1
    ctx->r2 = ADD32(ctx->r3, -0X1);
    // 0x800BD284: jal         0x800BCAA8
    // 0x800BD288: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    AudioSeq_SeqLayerDisable(rdram, ctx);
        goto after_3;
    // 0x800BD288: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    after_3:
    // 0x800BD28C: b           L_800BDBD0
    // 0x800BD290: lw          $ra, 0x2C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X2C);
        goto L_800BDBD0;
    // 0x800BD290: lw          $ra, 0x2C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X2C);
L_800BD294:
    // 0x800BD294: andi        $t4, $v0, 0xFF
    ctx->r12 = ctx->r2 & 0XFF;
    // 0x800BD298: sll         $t5, $t4, 2
    ctx->r13 = S32(ctx->r12 << 2);
    // 0x800BD29C: addu        $t6, $s0, $t5
    ctx->r14 = ADD32(ctx->r16, ctx->r13);
    // 0x800BD2A0: sb          $t4, 0x18($s0)
    MEM_B(0X18, ctx->r16) = ctx->r12;
    // 0x800BD2A4: lw          $t7, 0x4($t6)
    ctx->r15 = MEM_W(ctx->r14, 0X4);
    // 0x800BD2A8: b           L_800BD210
    // 0x800BD2AC: sw          $t7, 0x0($s0)
    MEM_W(0X0, ctx->r16) = ctx->r15;
        goto L_800BD210;
    // 0x800BD2AC: sw          $t7, 0x0($s0)
    MEM_W(0X0, ctx->r16) = ctx->r15;
L_800BD2B0:
    // 0x800BD2B0: jal         0x800BD0C4
    // 0x800BD2B4: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    AudioSeq_ScriptReadS16(rdram, ctx);
        goto after_4;
    // 0x800BD2B4: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_4:
    // 0x800BD2B8: lbu         $t9, 0x18($s0)
    ctx->r25 = MEM_BU(ctx->r16, 0X18);
    // 0x800BD2BC: lw          $t8, 0x0($s0)
    ctx->r24 = MEM_W(ctx->r16, 0X0);
    // 0x800BD2C0: andi        $t5, $v0, 0xFFFF
    ctx->r13 = ctx->r2 & 0XFFFF;
    // 0x800BD2C4: sll         $t0, $t9, 2
    ctx->r8 = S32(ctx->r25 << 2);
    // 0x800BD2C8: addu        $t1, $s0, $t0
    ctx->r9 = ADD32(ctx->r16, ctx->r8);
    // 0x800BD2CC: sw          $t8, 0x4($t1)
    MEM_W(0X4, ctx->r9) = ctx->r24;
    // 0x800BD2D0: lbu         $t2, 0x18($s0)
    ctx->r10 = MEM_BU(ctx->r16, 0X18);
    // 0x800BD2D4: andi        $s3, $v0, 0xFFFF
    ctx->r19 = ctx->r2 & 0XFFFF;
    // 0x800BD2D8: addiu       $t3, $t2, 0x1
    ctx->r11 = ADD32(ctx->r10, 0X1);
    // 0x800BD2DC: sb          $t3, 0x18($s0)
    MEM_B(0X18, ctx->r16) = ctx->r11;
    // 0x800BD2E0: lw          $t4, 0x14($s4)
    ctx->r12 = MEM_W(ctx->r20, 0X14);
    // 0x800BD2E4: addu        $t6, $t4, $t5
    ctx->r14 = ADD32(ctx->r12, ctx->r13);
    // 0x800BD2E8: b           L_800BD210
    // 0x800BD2EC: sw          $t6, 0x0($s0)
    MEM_W(0X0, ctx->r16) = ctx->r14;
        goto L_800BD210;
    // 0x800BD2EC: sw          $t6, 0x0($s0)
    MEM_W(0X0, ctx->r16) = ctx->r14;
L_800BD2F0:
    // 0x800BD2F0: jal         0x800BD0B0
    // 0x800BD2F4: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    AudioSeq_ScriptReadU8(rdram, ctx);
        goto after_5;
    // 0x800BD2F4: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_5:
    // 0x800BD2F8: lbu         $t7, 0x18($s0)
    ctx->r15 = MEM_BU(ctx->r16, 0X18);
    // 0x800BD2FC: addu        $t9, $s0, $t7
    ctx->r25 = ADD32(ctx->r16, ctx->r15);
    // 0x800BD300: sb          $v0, 0x14($t9)
    MEM_B(0X14, ctx->r25) = ctx->r2;
    // 0x800BD304: lbu         $t8, 0x18($s0)
    ctx->r24 = MEM_BU(ctx->r16, 0X18);
    // 0x800BD308: lw          $t0, 0x0($s0)
    ctx->r8 = MEM_W(ctx->r16, 0X0);
    // 0x800BD30C: sll         $t1, $t8, 2
    ctx->r9 = S32(ctx->r24 << 2);
    // 0x800BD310: addu        $t2, $s0, $t1
    ctx->r10 = ADD32(ctx->r16, ctx->r9);
    // 0x800BD314: sw          $t0, 0x4($t2)
    MEM_W(0X4, ctx->r10) = ctx->r8;
    // 0x800BD318: lbu         $t3, 0x18($s0)
    ctx->r11 = MEM_BU(ctx->r16, 0X18);
    // 0x800BD31C: addiu       $t4, $t3, 0x1
    ctx->r12 = ADD32(ctx->r11, 0X1);
    // 0x800BD320: b           L_800BD210
    // 0x800BD324: sb          $t4, 0x18($s0)
    MEM_B(0X18, ctx->r16) = ctx->r12;
        goto L_800BD210;
    // 0x800BD324: sb          $t4, 0x18($s0)
    MEM_B(0X18, ctx->r16) = ctx->r12;
L_800BD328:
    // 0x800BD328: lbu         $t5, 0x18($s0)
    ctx->r13 = MEM_BU(ctx->r16, 0X18);
    // 0x800BD32C: addu        $v0, $s0, $t5
    ctx->r2 = ADD32(ctx->r16, ctx->r13);
    // 0x800BD330: lbu         $t6, 0x13($v0)
    ctx->r14 = MEM_BU(ctx->r2, 0X13);
    // 0x800BD334: addiu       $t7, $t6, -0x1
    ctx->r15 = ADD32(ctx->r14, -0X1);
    // 0x800BD338: sb          $t7, 0x13($v0)
    MEM_B(0X13, ctx->r2) = ctx->r15;
    // 0x800BD33C: lbu         $v1, 0x18($s0)
    ctx->r3 = MEM_BU(ctx->r16, 0X18);
    // 0x800BD340: addu        $t9, $s0, $v1
    ctx->r25 = ADD32(ctx->r16, ctx->r3);
    // 0x800BD344: lbu         $t8, 0x13($t9)
    ctx->r24 = MEM_BU(ctx->r25, 0X13);
    // 0x800BD348: or          $a0, $v1, $zero
    ctx->r4 = ctx->r3 | 0;
    // 0x800BD34C: sll         $t1, $a0, 2
    ctx->r9 = S32(ctx->r4 << 2);
    // 0x800BD350: beq         $t8, $zero, L_800BD368
    if (ctx->r24 == 0) {
        // 0x800BD354: addiu       $t3, $v1, -0x1
        ctx->r11 = ADD32(ctx->r3, -0X1);
            goto L_800BD368;
    }
    // 0x800BD354: addiu       $t3, $v1, -0x1
    ctx->r11 = ADD32(ctx->r3, -0X1);
    // 0x800BD358: addu        $t0, $s0, $t1
    ctx->r8 = ADD32(ctx->r16, ctx->r9);
    // 0x800BD35C: lw          $t2, 0x0($t0)
    ctx->r10 = MEM_W(ctx->r8, 0X0);
    // 0x800BD360: b           L_800BD210
    // 0x800BD364: sw          $t2, 0x0($s0)
    MEM_W(0X0, ctx->r16) = ctx->r10;
        goto L_800BD210;
    // 0x800BD364: sw          $t2, 0x0($s0)
    MEM_W(0X0, ctx->r16) = ctx->r10;
L_800BD368:
    // 0x800BD368: b           L_800BD210
    // 0x800BD36C: sb          $t3, 0x18($s0)
    MEM_B(0X18, ctx->r16) = ctx->r11;
        goto L_800BD210;
    // 0x800BD36C: sb          $t3, 0x18($s0)
    MEM_B(0X18, ctx->r16) = ctx->r11;
L_800BD370:
    // 0x800BD370: jal         0x800BD0C4
    // 0x800BD374: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    AudioSeq_ScriptReadS16(rdram, ctx);
        goto after_6;
    // 0x800BD374: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_6:
    // 0x800BD378: lw          $t4, 0x14($s4)
    ctx->r12 = MEM_W(ctx->r20, 0X14);
    // 0x800BD37C: andi        $t5, $v0, 0xFFFF
    ctx->r13 = ctx->r2 & 0XFFFF;
    // 0x800BD380: andi        $s3, $v0, 0xFFFF
    ctx->r19 = ctx->r2 & 0XFFFF;
    // 0x800BD384: addu        $t6, $t4, $t5
    ctx->r14 = ADD32(ctx->r12, ctx->r13);
    // 0x800BD388: b           L_800BD210
    // 0x800BD38C: sw          $t6, 0x0($s0)
    MEM_W(0X0, ctx->r16) = ctx->r14;
        goto L_800BD210;
    // 0x800BD38C: sw          $t6, 0x0($s0)
    MEM_W(0X0, ctx->r16) = ctx->r14;
L_800BD390:
    // 0x800BD390: jal         0x800BD0B0
    // 0x800BD394: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    AudioSeq_ScriptReadU8(rdram, ctx);
        goto after_7;
    // 0x800BD394: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_7:
    // 0x800BD398: lw          $t7, 0x0($s0)
    ctx->r15 = MEM_W(ctx->r16, 0X0);
    // 0x800BD39C: sll         $t9, $v0, 24
    ctx->r25 = S32(ctx->r2 << 24);
    // 0x800BD3A0: sra         $t8, $t9, 24
    ctx->r24 = S32(SIGNED(ctx->r25) >> 24);
    // 0x800BD3A4: addu        $t1, $t7, $t8
    ctx->r9 = ADD32(ctx->r15, ctx->r24);
    // 0x800BD3A8: b           L_800BD210
    // 0x800BD3AC: sw          $t1, 0x0($s0)
    MEM_W(0X0, ctx->r16) = ctx->r9;
        goto L_800BD210;
    // 0x800BD3AC: sw          $t1, 0x0($s0)
    MEM_W(0X0, ctx->r16) = ctx->r9;
L_800BD3B0:
    // 0x800BD3B0: lw          $v1, 0x0($s0)
    ctx->r3 = MEM_W(ctx->r16, 0X0);
    // 0x800BD3B4: addiu       $at, $zero, 0xC1
    ctx->r1 = ADD32(0, 0XC1);
    // 0x800BD3B8: lbu         $a0, 0x0($v1)
    ctx->r4 = MEM_BU(ctx->r3, 0X0);
    // 0x800BD3BC: addiu       $t0, $v1, 0x1
    ctx->r8 = ADD32(ctx->r3, 0X1);
    // 0x800BD3C0: bne         $a1, $at, L_800BD3E4
    if (ctx->r5 != ctx->r1) {
        // 0x800BD3C4: sw          $t0, 0x0($s0)
        MEM_W(0X0, ctx->r16) = ctx->r8;
            goto L_800BD3E4;
    }
    // 0x800BD3C4: sw          $t0, 0x0($s0)
    MEM_W(0X0, ctx->r16) = ctx->r8;
    // 0x800BD3C8: multu       $a0, $a0
    result = U64(U32(ctx->r4)) * U64(U32(ctx->r4)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x800BD3CC: mflo        $t2
    ctx->r10 = lo;
    // 0x800BD3D0: mtc1        $t2, $f4
    ctx->f4.u32l = ctx->r10;
    // 0x800BD3D4: nop

    // 0x800BD3D8: cvt.s.w     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
    // 0x800BD3DC: b           L_800BD210
    // 0x800BD3E0: swc1        $f6, 0x28($s1)
    MEM_W(0X28, ctx->r17) = ctx->f6.u32l;
        goto L_800BD210;
    // 0x800BD3E0: swc1        $f6, 0x28($s1)
    MEM_W(0X28, ctx->r17) = ctx->f6.u32l;
L_800BD3E4:
    // 0x800BD3E4: b           L_800BD210
    // 0x800BD3E8: sb          $a0, 0x5($s1)
    MEM_B(0X5, ctx->r17) = ctx->r4;
        goto L_800BD210;
    // 0x800BD3E8: sb          $a0, 0x5($s1)
    MEM_B(0X5, ctx->r17) = ctx->r4;
L_800BD3EC:
    // 0x800BD3EC: lw          $v1, 0x0($s0)
    ctx->r3 = MEM_W(ctx->r16, 0X0);
    // 0x800BD3F0: addiu       $at, $zero, 0xC9
    ctx->r1 = ADD32(0, 0XC9);
    // 0x800BD3F4: lbu         $a0, 0x0($v1)
    ctx->r4 = MEM_BU(ctx->r3, 0X0);
    // 0x800BD3F8: addiu       $t3, $v1, 0x1
    ctx->r11 = ADD32(ctx->r3, 0X1);
    // 0x800BD3FC: bne         $a1, $at, L_800BD40C
    if (ctx->r5 != ctx->r1) {
        // 0x800BD400: sw          $t3, 0x0($s0)
        MEM_W(0X0, ctx->r16) = ctx->r11;
            goto L_800BD40C;
    }
    // 0x800BD400: sw          $t3, 0x0($s0)
    MEM_W(0X0, ctx->r16) = ctx->r11;
    // 0x800BD404: b           L_800BD210
    // 0x800BD408: sb          $a0, 0x3($s1)
    MEM_B(0X3, ctx->r17) = ctx->r4;
        goto L_800BD210;
    // 0x800BD408: sb          $a0, 0x3($s1)
    MEM_B(0X3, ctx->r17) = ctx->r4;
L_800BD40C:
    // 0x800BD40C: b           L_800BD210
    // 0x800BD410: sh          $a0, 0x22($s1)
    MEM_H(0X22, ctx->r17) = ctx->r4;
        goto L_800BD210;
    // 0x800BD410: sh          $a0, 0x22($s1)
    MEM_H(0X22, ctx->r17) = ctx->r4;
L_800BD414:
    // 0x800BD414: addiu       $at, $zero, 0xC4
    ctx->r1 = ADD32(0, 0XC4);
    // 0x800BD418: bnel        $a1, $at, L_800BD434
    if (ctx->r5 != ctx->r1) {
        // 0x800BD41C: lbu         $t9, 0x0($s1)
        ctx->r25 = MEM_BU(ctx->r17, 0X0);
            goto L_800BD434;
    }
    goto skip_4;
    // 0x800BD41C: lbu         $t9, 0x0($s1)
    ctx->r25 = MEM_BU(ctx->r17, 0X0);
    skip_4:
    // 0x800BD420: lbu         $t5, 0x0($s1)
    ctx->r13 = MEM_BU(ctx->r17, 0X0);
    // 0x800BD424: ori         $t6, $t5, 0x10
    ctx->r14 = ctx->r13 | 0X10;
    // 0x800BD428: b           L_800BD43C
    // 0x800BD42C: sb          $t6, 0x0($s1)
    MEM_B(0X0, ctx->r17) = ctx->r14;
        goto L_800BD43C;
    // 0x800BD42C: sb          $t6, 0x0($s1)
    MEM_B(0X0, ctx->r17) = ctx->r14;
    // 0x800BD430: lbu         $t9, 0x0($s1)
    ctx->r25 = MEM_BU(ctx->r17, 0X0);
L_800BD434:
    // 0x800BD434: andi        $t7, $t9, 0xFFEF
    ctx->r15 = ctx->r25 & 0XFFEF;
    // 0x800BD438: sb          $t7, 0x0($s1)
    MEM_B(0X0, ctx->r17) = ctx->r15;
L_800BD43C:
    // 0x800BD43C: jal         0x800BB108
    // 0x800BD440: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    Audio_SeqLayerNoteDecay(rdram, ctx);
        goto after_8;
    // 0x800BD440: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    after_8:
    // 0x800BD444: b           L_800BD210
    // 0x800BD448: nop

        goto L_800BD210;
    // 0x800BD448: nop

L_800BD44C:
    // 0x800BD44C: jal         0x800BD0F4
    // 0x800BD450: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    AudioSeq_ScriptReadCompressedU16(rdram, ctx);
        goto after_9;
    // 0x800BD450: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_9:
    // 0x800BD454: andi        $s3, $v0, 0xFFFF
    ctx->r19 = ctx->r2 & 0XFFFF;
    // 0x800BD458: b           L_800BD210
    // 0x800BD45C: sh          $v0, 0x34($s1)
    MEM_H(0X34, ctx->r17) = ctx->r2;
        goto L_800BD210;
    // 0x800BD45C: sh          $v0, 0x34($s1)
    MEM_H(0X34, ctx->r17) = ctx->r2;
L_800BD460:
    // 0x800BD460: jal         0x800BD0B0
    // 0x800BD464: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    AudioSeq_ScriptReadU8(rdram, ctx);
        goto after_10;
    // 0x800BD464: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_10:
    // 0x800BD468: slti        $at, $v0, 0x7F
    ctx->r1 = SIGNED(ctx->r2) < 0X7F ? 1 : 0;
    // 0x800BD46C: andi        $s2, $v0, 0xFF
    ctx->r18 = ctx->r2 & 0XFF;
    // 0x800BD470: bne         $at, $zero, L_800BD4A8
    if (ctx->r1 != 0) {
        // 0x800BD474: or          $a1, $v0, $zero
        ctx->r5 = ctx->r2 | 0;
            goto L_800BD4A8;
    }
    // 0x800BD474: or          $a1, $v0, $zero
    ctx->r5 = ctx->r2 | 0;
    // 0x800BD478: addiu       $at, $zero, 0x7F
    ctx->r1 = ADD32(0, 0X7F);
    // 0x800BD47C: bnel        $v0, $at, L_800BD490
    if (ctx->r2 != ctx->r1) {
        // 0x800BD480: sb          $v0, 0x1($s1)
        MEM_B(0X1, ctx->r17) = ctx->r2;
            goto L_800BD490;
    }
    goto skip_5;
    // 0x800BD480: sb          $v0, 0x1($s1)
    MEM_B(0X1, ctx->r17) = ctx->r2;
    skip_5:
    // 0x800BD484: b           L_800BD494
    // 0x800BD488: sb          $zero, 0x1($s1)
    MEM_B(0X1, ctx->r17) = 0;
        goto L_800BD494;
    // 0x800BD488: sb          $zero, 0x1($s1)
    MEM_B(0X1, ctx->r17) = 0;
    // 0x800BD48C: sb          $v0, 0x1($s1)
    MEM_B(0X1, ctx->r17) = ctx->r2;
L_800BD490:
    // 0x800BD490: sw          $zero, 0x44($s1)
    MEM_W(0X44, ctx->r17) = 0;
L_800BD494:
    // 0x800BD494: addiu       $at, $zero, 0xFF
    ctx->r1 = ADD32(0, 0XFF);
    // 0x800BD498: bne         $a1, $at, L_800BD210
    if (ctx->r5 != ctx->r1) {
        // 0x800BD49C: nop
    
            goto L_800BD210;
    }
    // 0x800BD49C: nop

    // 0x800BD4A0: b           L_800BD210
    // 0x800BD4A4: sb          $zero, 0x18($s1)
    MEM_B(0X18, ctx->r17) = 0;
        goto L_800BD210;
    // 0x800BD4A4: sb          $zero, 0x18($s1)
    MEM_B(0X18, ctx->r17) = 0;
L_800BD4A8:
    // 0x800BD4A8: lw          $a0, 0x68($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X68);
    // 0x800BD4AC: andi        $a1, $s2, 0xFF
    ctx->r5 = ctx->r18 & 0XFF;
    // 0x800BD4B0: addiu       $a2, $s1, 0x44
    ctx->r6 = ADD32(ctx->r17, 0X44);
    // 0x800BD4B4: jal         0x800BDBEC
    // 0x800BD4B8: addiu       $a3, $s1, 0x18
    ctx->r7 = ADD32(ctx->r17, 0X18);
    AudioSeq_GetInstrument(rdram, ctx);
        goto after_11;
    // 0x800BD4B8: addiu       $a3, $s1, 0x18
    ctx->r7 = ADD32(ctx->r17, 0X18);
    after_11:
    // 0x800BD4BC: bne         $v0, $zero, L_800BD210
    if (ctx->r2 != 0) {
        // 0x800BD4C0: sb          $v0, 0x1($s1)
        MEM_B(0X1, ctx->r17) = ctx->r2;
            goto L_800BD210;
    }
    // 0x800BD4C0: sb          $v0, 0x1($s1)
    MEM_B(0X1, ctx->r17) = ctx->r2;
    // 0x800BD4C4: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x800BD4C8: b           L_800BD210
    // 0x800BD4CC: sb          $t8, 0x1($s1)
    MEM_B(0X1, ctx->r17) = ctx->r24;
        goto L_800BD210;
    // 0x800BD4CC: sb          $t8, 0x1($s1)
    MEM_B(0X1, ctx->r17) = ctx->r24;
L_800BD4D0:
    // 0x800BD4D0: jal         0x800BD0B0
    // 0x800BD4D4: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    AudioSeq_ScriptReadU8(rdram, ctx);
        goto after_12;
    // 0x800BD4D4: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_12:
    // 0x800BD4D8: sb          $v0, 0x8($s1)
    MEM_B(0X8, ctx->r17) = ctx->r2;
    // 0x800BD4DC: jal         0x800BD0B0
    // 0x800BD4E0: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    AudioSeq_ScriptReadU8(rdram, ctx);
        goto after_13;
    // 0x800BD4E0: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_13:
    // 0x800BD4E4: lw          $t1, 0x68($sp)
    ctx->r9 = MEM_W(ctx->r29, 0X68);
    // 0x800BD4E8: lh          $t3, 0x22($s1)
    ctx->r11 = MEM_H(ctx->r17, 0X22);
    // 0x800BD4EC: lh          $t5, 0xC($s4)
    ctx->r13 = MEM_H(ctx->r20, 0XC);
    // 0x800BD4F0: lh          $t0, 0x1E($t1)
    ctx->r8 = MEM_H(ctx->r9, 0X1E);
    // 0x800BD4F4: addu        $t2, $v0, $t0
    ctx->r10 = ADD32(ctx->r2, ctx->r8);
    // 0x800BD4F8: addu        $t4, $t2, $t3
    ctx->r12 = ADD32(ctx->r10, ctx->r11);
    // 0x800BD4FC: addu        $s2, $t4, $t5
    ctx->r18 = ADD32(ctx->r12, ctx->r13);
    // 0x800BD500: andi        $t6, $s2, 0xFF
    ctx->r14 = ctx->r18 & 0XFF;
    // 0x800BD504: slti        $at, $t6, 0x80
    ctx->r1 = SIGNED(ctx->r14) < 0X80 ? 1 : 0;
    // 0x800BD508: bne         $at, $zero, L_800BD514
    if (ctx->r1 != 0) {
        // 0x800BD50C: or          $s2, $t6, $zero
        ctx->r18 = ctx->r14 | 0;
            goto L_800BD514;
    }
    // 0x800BD50C: or          $s2, $t6, $zero
    ctx->r18 = ctx->r14 | 0;
    // 0x800BD510: or          $s2, $zero, $zero
    ctx->r18 = 0 | 0;
L_800BD514:
    // 0x800BD514: lbu         $t9, 0x8($s1)
    ctx->r25 = MEM_BU(ctx->r17, 0X8);
    // 0x800BD518: sb          $s2, 0x4($s1)
    MEM_B(0X4, ctx->r17) = ctx->r18;
    // 0x800BD51C: andi        $t7, $t9, 0x80
    ctx->r15 = ctx->r25 & 0X80;
    // 0x800BD520: beq         $t7, $zero, L_800BD544
    if (ctx->r15 == 0) {
        // 0x800BD524: nop
    
            goto L_800BD544;
    }
    // 0x800BD524: nop

    // 0x800BD528: lw          $t8, 0x0($s0)
    ctx->r24 = MEM_W(ctx->r16, 0X0);
    // 0x800BD52C: lbu         $t1, 0x0($t8)
    ctx->r9 = MEM_BU(ctx->r24, 0X0);
    // 0x800BD530: sh          $t1, 0x20($s1)
    MEM_H(0X20, ctx->r17) = ctx->r9;
    // 0x800BD534: lw          $t0, 0x0($s0)
    ctx->r8 = MEM_W(ctx->r16, 0X0);
    // 0x800BD538: addiu       $t2, $t0, 0x1
    ctx->r10 = ADD32(ctx->r8, 0X1);
    // 0x800BD53C: b           L_800BD210
    // 0x800BD540: sw          $t2, 0x0($s0)
    MEM_W(0X0, ctx->r16) = ctx->r10;
        goto L_800BD210;
    // 0x800BD540: sw          $t2, 0x0($s0)
    MEM_W(0X0, ctx->r16) = ctx->r10;
L_800BD544:
    // 0x800BD544: jal         0x800BD0F4
    // 0x800BD548: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    AudioSeq_ScriptReadCompressedU16(rdram, ctx);
        goto after_14;
    // 0x800BD548: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_14:
    // 0x800BD54C: andi        $s3, $v0, 0xFFFF
    ctx->r19 = ctx->r2 & 0XFFFF;
    // 0x800BD550: b           L_800BD210
    // 0x800BD554: sh          $v0, 0x20($s1)
    MEM_H(0X20, ctx->r17) = ctx->r2;
        goto L_800BD210;
    // 0x800BD554: sh          $v0, 0x20($s1)
    MEM_H(0X20, ctx->r17) = ctx->r2;
L_800BD558:
    // 0x800BD558: b           L_800BD210
    // 0x800BD55C: sb          $zero, 0x8($s1)
    MEM_B(0X8, ctx->r17) = 0;
        goto L_800BD210;
    // 0x800BD55C: sb          $zero, 0x8($s1)
    MEM_B(0X8, ctx->r17) = 0;
L_800BD560:
    // 0x800BD560: jal         0x800BD0C4
    // 0x800BD564: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    AudioSeq_ScriptReadS16(rdram, ctx);
        goto after_15;
    // 0x800BD564: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_15:
    // 0x800BD568: lw          $t3, 0x14($s4)
    ctx->r11 = MEM_W(ctx->r20, 0X14);
    // 0x800BD56C: andi        $t4, $v0, 0xFFFF
    ctx->r12 = ctx->r2 & 0XFFFF;
    // 0x800BD570: andi        $s3, $v0, 0xFFFF
    ctx->r19 = ctx->r2 & 0XFFFF;
    // 0x800BD574: addu        $t5, $t3, $t4
    ctx->r13 = ADD32(ctx->r11, ctx->r12);
    // 0x800BD578: sw          $t5, 0x1C($s1)
    MEM_W(0X1C, ctx->r17) = ctx->r13;
    // 0x800BD57C: jal         0x800BD0B0
    // 0x800BD580: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    AudioSeq_ScriptReadU8(rdram, ctx);
        goto after_16;
    // 0x800BD580: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_16:
    // 0x800BD584: b           L_800BD210
    // 0x800BD588: sb          $v0, 0x18($s1)
    MEM_B(0X18, ctx->r17) = ctx->r2;
        goto L_800BD210;
    // 0x800BD588: sb          $v0, 0x18($s1)
    MEM_B(0X18, ctx->r17) = ctx->r2;
L_800BD58C:
    // 0x800BD58C: lbu         $t9, 0x0($s1)
    ctx->r25 = MEM_BU(ctx->r17, 0X0);
    // 0x800BD590: ori         $t7, $t9, 0x2
    ctx->r15 = ctx->r25 | 0X2;
    // 0x800BD594: b           L_800BD210
    // 0x800BD598: sb          $t7, 0x0($s1)
    MEM_B(0X0, ctx->r17) = ctx->r15;
        goto L_800BD210;
    // 0x800BD598: sb          $t7, 0x0($s1)
    MEM_B(0X0, ctx->r17) = ctx->r15;
L_800BD59C:
    // 0x800BD59C: andi        $v1, $a1, 0xF0
    ctx->r3 = ctx->r5 & 0XF0;
    // 0x800BD5A0: addiu       $at, $zero, 0xD0
    ctx->r1 = ADD32(0, 0XD0);
    // 0x800BD5A4: beq         $v1, $at, L_800BD5BC
    if (ctx->r3 == ctx->r1) {
        // 0x800BD5A8: addiu       $at, $zero, 0xE0
        ctx->r1 = ADD32(0, 0XE0);
            goto L_800BD5BC;
    }
    // 0x800BD5A8: addiu       $at, $zero, 0xE0
    ctx->r1 = ADD32(0, 0XE0);
    // 0x800BD5AC: beql        $v1, $at, L_800BD5EC
    if (ctx->r3 == ctx->r1) {
        // 0x800BD5B0: lw          $t3, 0x90($s4)
        ctx->r11 = MEM_W(ctx->r20, 0X90);
            goto L_800BD5EC;
    }
    goto skip_6;
    // 0x800BD5B0: lw          $t3, 0x90($s4)
    ctx->r11 = MEM_W(ctx->r20, 0X90);
    skip_6:
    // 0x800BD5B4: b           L_800BD210
    // 0x800BD5B8: nop

        goto L_800BD210;
    // 0x800BD5B8: nop

L_800BD5BC:
    // 0x800BD5BC: lw          $t8, 0x8C($s4)
    ctx->r24 = MEM_W(ctx->r20, 0X8C);
    // 0x800BD5C0: andi        $t1, $a1, 0xF
    ctx->r9 = ctx->r5 & 0XF;
    // 0x800BD5C4: addu        $t0, $t8, $t1
    ctx->r8 = ADD32(ctx->r24, ctx->r9);
    // 0x800BD5C8: lbu         $s3, 0x0($t0)
    ctx->r19 = MEM_BU(ctx->r8, 0X0);
    // 0x800BD5CC: multu       $s3, $s3
    result = U64(U32(ctx->r19)) * U64(U32(ctx->r19)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x800BD5D0: mflo        $t2
    ctx->r10 = lo;
    // 0x800BD5D4: mtc1        $t2, $f8
    ctx->f8.u32l = ctx->r10;
    // 0x800BD5D8: nop

    // 0x800BD5DC: cvt.s.w     $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.fl = CVT_S_W(ctx->f8.u32l);
    // 0x800BD5E0: b           L_800BD210
    // 0x800BD5E4: swc1        $f10, 0x28($s1)
    MEM_W(0X28, ctx->r17) = ctx->f10.u32l;
        goto L_800BD210;
    // 0x800BD5E4: swc1        $f10, 0x28($s1)
    MEM_W(0X28, ctx->r17) = ctx->f10.u32l;
    // 0x800BD5E8: lw          $t3, 0x90($s4)
    ctx->r11 = MEM_W(ctx->r20, 0X90);
L_800BD5EC:
    // 0x800BD5EC: andi        $t4, $a1, 0xF
    ctx->r12 = ctx->r5 & 0XF;
    // 0x800BD5F0: addu        $t5, $t3, $t4
    ctx->r13 = ADD32(ctx->r11, ctx->r12);
    // 0x800BD5F4: lbu         $t6, 0x0($t5)
    ctx->r14 = MEM_BU(ctx->r13, 0X0);
    // 0x800BD5F8: b           L_800BD210
    // 0x800BD5FC: sb          $t6, 0x3($s1)
    MEM_B(0X3, ctx->r17) = ctx->r14;
        goto L_800BD210;
    // 0x800BD5FC: sb          $t6, 0x3($s1)
    MEM_B(0X3, ctx->r17) = ctx->r14;
L_800BD600:
    // 0x800BD600: addiu       $at, $zero, 0xC0
    ctx->r1 = ADD32(0, 0XC0);
    // 0x800BD604: bne         $a1, $at, L_800BD628
    if (ctx->r5 != ctx->r1) {
        // 0x800BD608: andi        $v1, $a1, 0xC0
        ctx->r3 = ctx->r5 & 0XC0;
            goto L_800BD628;
    }
    // 0x800BD608: andi        $v1, $a1, 0xC0
    ctx->r3 = ctx->r5 & 0XC0;
    // 0x800BD60C: jal         0x800BD0F4
    // 0x800BD610: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    AudioSeq_ScriptReadCompressedU16(rdram, ctx);
        goto after_17;
    // 0x800BD610: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_17:
    // 0x800BD614: lbu         $t7, 0x0($s1)
    ctx->r15 = MEM_BU(ctx->r17, 0X0);
    // 0x800BD618: sh          $v0, 0x38($s1)
    MEM_H(0X38, ctx->r17) = ctx->r2;
    // 0x800BD61C: ori         $t8, $t7, 0x20
    ctx->r24 = ctx->r15 | 0X20;
    // 0x800BD620: b           L_800BDAE4
    // 0x800BD624: sb          $t8, 0x0($s1)
    MEM_B(0X0, ctx->r17) = ctx->r24;
        goto L_800BDAE4;
    // 0x800BD624: sb          $t8, 0x0($s1)
    MEM_B(0X0, ctx->r17) = ctx->r24;
L_800BD628:
    // 0x800BD628: lbu         $t1, 0x0($s1)
    ctx->r9 = MEM_BU(ctx->r17, 0X0);
    // 0x800BD62C: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x800BD630: andi        $t0, $t1, 0xFFDF
    ctx->r8 = ctx->r9 & 0XFFDF;
    // 0x800BD634: sb          $t0, 0x0($s1)
    MEM_B(0X0, ctx->r17) = ctx->r8;
    // 0x800BD638: lw          $t2, 0x68($sp)
    ctx->r10 = MEM_W(ctx->r29, 0X68);
    // 0x800BD63C: lw          $t3, 0x0($t2)
    ctx->r11 = MEM_W(ctx->r10, 0X0);
    // 0x800BD640: sll         $t4, $t3, 6
    ctx->r12 = S32(ctx->r11 << 6);
    // 0x800BD644: srl         $t5, $t4, 31
    ctx->r13 = S32(U32(ctx->r12) >> 31);
    // 0x800BD648: bne         $t5, $at, L_800BD744
    if (ctx->r13 != ctx->r1) {
        // 0x800BD64C: nop
    
            goto L_800BD744;
    }
    // 0x800BD64C: nop

    // 0x800BD650: andi        $v1, $a1, 0xC0
    ctx->r3 = ctx->r5 & 0XC0;
    // 0x800BD654: beq         $v1, $zero, L_800BD674
    if (ctx->r3 == 0) {
        // 0x800BD658: addiu       $at, $zero, 0x40
        ctx->r1 = ADD32(0, 0X40);
            goto L_800BD674;
    }
    // 0x800BD658: addiu       $at, $zero, 0x40
    ctx->r1 = ADD32(0, 0X40);
    // 0x800BD65C: beq         $v1, $at, L_800BD6B0
    if (ctx->r3 == ctx->r1) {
        // 0x800BD660: addiu       $at, $zero, 0x80
        ctx->r1 = ADD32(0, 0X80);
            goto L_800BD6B0;
    }
    // 0x800BD660: addiu       $at, $zero, 0x80
    ctx->r1 = ADD32(0, 0X80);
    // 0x800BD664: beq         $v1, $at, L_800BD6DC
    if (ctx->r3 == ctx->r1) {
        // 0x800BD668: or          $a0, $s3, $zero
        ctx->r4 = ctx->r19 | 0;
            goto L_800BD6DC;
    }
    // 0x800BD668: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
    // 0x800BD66C: b           L_800BD708
    // 0x800BD670: lw          $a2, 0x34($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X34);
        goto L_800BD708;
    // 0x800BD670: lw          $a2, 0x34($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X34);
L_800BD674:
    // 0x800BD674: jal         0x800BD0F4
    // 0x800BD678: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    AudioSeq_ScriptReadCompressedU16(rdram, ctx);
        goto after_18;
    // 0x800BD678: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_18:
    // 0x800BD67C: lw          $v1, 0x0($s0)
    ctx->r3 = MEM_W(ctx->r16, 0X0);
    // 0x800BD680: andi        $s3, $v0, 0xFFFF
    ctx->r19 = ctx->r2 & 0XFFFF;
    // 0x800BD684: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
    // 0x800BD688: lbu         $a2, 0x0($v1)
    ctx->r6 = MEM_BU(ctx->r3, 0X0);
    // 0x800BD68C: addiu       $t6, $v1, 0x1
    ctx->r14 = ADD32(ctx->r3, 0X1);
    // 0x800BD690: sw          $t6, 0x0($s0)
    MEM_W(0X0, ctx->r16) = ctx->r14;
    // 0x800BD694: lbu         $t7, 0x0($t6)
    ctx->r15 = MEM_BU(ctx->r14, 0X0);
    // 0x800BD698: sb          $t7, 0x3($s1)
    MEM_B(0X3, ctx->r17) = ctx->r15;
    // 0x800BD69C: lw          $t8, 0x0($s0)
    ctx->r24 = MEM_W(ctx->r16, 0X0);
    // 0x800BD6A0: addiu       $t1, $t8, 0x1
    ctx->r9 = ADD32(ctx->r24, 0X1);
    // 0x800BD6A4: sw          $t1, 0x0($s0)
    MEM_W(0X0, ctx->r16) = ctx->r9;
    // 0x800BD6A8: b           L_800BD708
    // 0x800BD6AC: sh          $v0, 0x36($s1)
    MEM_H(0X36, ctx->r17) = ctx->r2;
        goto L_800BD708;
    // 0x800BD6AC: sh          $v0, 0x36($s1)
    MEM_H(0X36, ctx->r17) = ctx->r2;
L_800BD6B0:
    // 0x800BD6B0: jal         0x800BD0F4
    // 0x800BD6B4: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    AudioSeq_ScriptReadCompressedU16(rdram, ctx);
        goto after_19;
    // 0x800BD6B4: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_19:
    // 0x800BD6B8: lw          $v1, 0x0($s0)
    ctx->r3 = MEM_W(ctx->r16, 0X0);
    // 0x800BD6BC: andi        $s3, $v0, 0xFFFF
    ctx->r19 = ctx->r2 & 0XFFFF;
    // 0x800BD6C0: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
    // 0x800BD6C4: lbu         $a2, 0x0($v1)
    ctx->r6 = MEM_BU(ctx->r3, 0X0);
    // 0x800BD6C8: addiu       $t0, $v1, 0x1
    ctx->r8 = ADD32(ctx->r3, 0X1);
    // 0x800BD6CC: sw          $t0, 0x0($s0)
    MEM_W(0X0, ctx->r16) = ctx->r8;
    // 0x800BD6D0: sb          $zero, 0x3($s1)
    MEM_B(0X3, ctx->r17) = 0;
    // 0x800BD6D4: b           L_800BD708
    // 0x800BD6D8: sh          $v0, 0x36($s1)
    MEM_H(0X36, ctx->r17) = ctx->r2;
        goto L_800BD708;
    // 0x800BD6D8: sh          $v0, 0x36($s1)
    MEM_H(0X36, ctx->r17) = ctx->r2;
L_800BD6DC:
    // 0x800BD6DC: lw          $v1, 0x0($s0)
    ctx->r3 = MEM_W(ctx->r16, 0X0);
    // 0x800BD6E0: lhu         $s3, 0x36($s1)
    ctx->r19 = MEM_HU(ctx->r17, 0X36);
    // 0x800BD6E4: lbu         $a2, 0x0($v1)
    ctx->r6 = MEM_BU(ctx->r3, 0X0);
    // 0x800BD6E8: addiu       $t2, $v1, 0x1
    ctx->r10 = ADD32(ctx->r3, 0X1);
    // 0x800BD6EC: sw          $t2, 0x0($s0)
    MEM_W(0X0, ctx->r16) = ctx->r10;
    // 0x800BD6F0: lbu         $t4, 0x0($t2)
    ctx->r12 = MEM_BU(ctx->r10, 0X0);
    // 0x800BD6F4: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
    // 0x800BD6F8: sb          $t4, 0x3($s1)
    MEM_B(0X3, ctx->r17) = ctx->r12;
    // 0x800BD6FC: lw          $t5, 0x0($s0)
    ctx->r13 = MEM_W(ctx->r16, 0X0);
    // 0x800BD700: addiu       $t6, $t5, 0x1
    ctx->r14 = ADD32(ctx->r13, 0X1);
    // 0x800BD704: sw          $t6, 0x0($s0)
    MEM_W(0X0, ctx->r16) = ctx->r14;
L_800BD708:
    // 0x800BD708: slti        $at, $a2, 0x80
    ctx->r1 = SIGNED(ctx->r6) < 0X80 ? 1 : 0;
    // 0x800BD70C: beql        $at, $zero, L_800BD720
    if (ctx->r1 == 0) {
        // 0x800BD710: addiu       $a2, $zero, 0x7F
        ctx->r6 = ADD32(0, 0X7F);
            goto L_800BD720;
    }
    goto skip_7;
    // 0x800BD710: addiu       $a2, $zero, 0x7F
    ctx->r6 = ADD32(0, 0X7F);
    skip_7:
    // 0x800BD714: bgezl       $a2, L_800BD724
    if (SIGNED(ctx->r6) >= 0) {
        // 0x800BD718: mtc1        $a2, $f16
        ctx->f16.u32l = ctx->r6;
            goto L_800BD724;
    }
    goto skip_8;
    // 0x800BD718: mtc1        $a2, $f16
    ctx->f16.u32l = ctx->r6;
    skip_8:
    // 0x800BD71C: addiu       $a2, $zero, 0x7F
    ctx->r6 = ADD32(0, 0X7F);
L_800BD720:
    // 0x800BD720: mtc1        $a2, $f16
    ctx->f16.u32l = ctx->r6;
L_800BD724:
    // 0x800BD724: andi        $t9, $s2, 0xC0
    ctx->r25 = ctx->r18 & 0XC0;
    // 0x800BD728: subu        $s2, $s2, $t9
    ctx->r18 = SUB32(ctx->r18, ctx->r25);
    // 0x800BD72C: cvt.s.w     $f0, $f16
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 16);
    ctx->f0.fl = CVT_S_W(ctx->f16.u32l);
    // 0x800BD730: andi        $t7, $s2, 0xFF
    ctx->r15 = ctx->r18 & 0XFF;
    // 0x800BD734: or          $s2, $t7, $zero
    ctx->r18 = ctx->r15 | 0;
    // 0x800BD738: mul.s       $f18, $f0, $f0
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f18.fl = MUL_S(ctx->f0.fl, ctx->f0.fl);
    // 0x800BD73C: b           L_800BD7A0
    // 0x800BD740: swc1        $f18, 0x28($s1)
    MEM_W(0X28, ctx->r17) = ctx->f18.u32l;
        goto L_800BD7A0;
    // 0x800BD740: swc1        $f18, 0x28($s1)
    MEM_W(0X28, ctx->r17) = ctx->f18.u32l;
L_800BD744:
    // 0x800BD744: beq         $v1, $zero, L_800BD764
    if (ctx->r3 == 0) {
        // 0x800BD748: addiu       $at, $zero, 0x40
        ctx->r1 = ADD32(0, 0X40);
            goto L_800BD764;
    }
    // 0x800BD748: addiu       $at, $zero, 0x40
    ctx->r1 = ADD32(0, 0X40);
    // 0x800BD74C: beq         $v1, $at, L_800BD77C
    if (ctx->r3 == ctx->r1) {
        // 0x800BD750: addiu       $at, $zero, 0x80
        ctx->r1 = ADD32(0, 0X80);
            goto L_800BD77C;
    }
    // 0x800BD750: addiu       $at, $zero, 0x80
    ctx->r1 = ADD32(0, 0X80);
    // 0x800BD754: beql        $v1, $at, L_800BD78C
    if (ctx->r3 == ctx->r1) {
        // 0x800BD758: lhu         $s3, 0x36($s1)
        ctx->r19 = MEM_HU(ctx->r17, 0X36);
            goto L_800BD78C;
    }
    goto skip_9;
    // 0x800BD758: lhu         $s3, 0x36($s1)
    ctx->r19 = MEM_HU(ctx->r17, 0X36);
    skip_9:
    // 0x800BD75C: b           L_800BD790
    // 0x800BD760: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
        goto L_800BD790;
    // 0x800BD760: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
L_800BD764:
    // 0x800BD764: jal         0x800BD0F4
    // 0x800BD768: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    AudioSeq_ScriptReadCompressedU16(rdram, ctx);
        goto after_20;
    // 0x800BD768: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_20:
    // 0x800BD76C: andi        $s3, $v0, 0xFFFF
    ctx->r19 = ctx->r2 & 0XFFFF;
    // 0x800BD770: sh          $v0, 0x36($s1)
    MEM_H(0X36, ctx->r17) = ctx->r2;
    // 0x800BD774: b           L_800BD790
    // 0x800BD778: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
        goto L_800BD790;
    // 0x800BD778: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
L_800BD77C:
    // 0x800BD77C: lhu         $s3, 0x34($s1)
    ctx->r19 = MEM_HU(ctx->r17, 0X34);
    // 0x800BD780: b           L_800BD790
    // 0x800BD784: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
        goto L_800BD790;
    // 0x800BD784: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
    // 0x800BD788: lhu         $s3, 0x36($s1)
    ctx->r19 = MEM_HU(ctx->r17, 0X36);
L_800BD78C:
    // 0x800BD78C: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
L_800BD790:
    // 0x800BD790: andi        $t8, $s2, 0xC0
    ctx->r24 = ctx->r18 & 0XC0;
    // 0x800BD794: subu        $s2, $s2, $t8
    ctx->r18 = SUB32(ctx->r18, ctx->r24);
    // 0x800BD798: andi        $t1, $s2, 0xFF
    ctx->r9 = ctx->r18 & 0XFF;
    // 0x800BD79C: or          $s2, $t1, $zero
    ctx->r18 = ctx->r9 | 0;
L_800BD7A0:
    // 0x800BD7A0: lbu         $t0, 0x3($s1)
    ctx->r8 = MEM_BU(ctx->r17, 0X3);
    // 0x800BD7A4: sh          $a0, 0x38($s1)
    MEM_H(0X38, ctx->r17) = ctx->r4;
    // 0x800BD7A8: multu       $t0, $a0
    result = U64(U32(ctx->r8)) * U64(U32(ctx->r4)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x800BD7AC: mflo        $t2
    ctx->r10 = lo;
    // 0x800BD7B0: sra         $t3, $t2, 8
    ctx->r11 = S32(SIGNED(ctx->r10) >> 8);
    // 0x800BD7B4: sh          $t3, 0x3A($s1)
    MEM_H(0X3A, ctx->r17) = ctx->r11;
    // 0x800BD7B8: lw          $t4, 0x0($s4)
    ctx->r12 = MEM_W(ctx->r20, 0X0);
    // 0x800BD7BC: lw          $t9, 0x68($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X68);
    // 0x800BD7C0: lw          $t1, 0x68($sp)
    ctx->r9 = MEM_W(ctx->r29, 0X68);
    // 0x800BD7C4: sll         $t6, $t4, 2
    ctx->r14 = S32(ctx->r12 << 2);
    // 0x800BD7C8: bgezl       $t6, L_800BD7E4
    if (SIGNED(ctx->r14) >= 0) {
        // 0x800BD7CC: lw          $v1, 0x0($t1)
        ctx->r3 = MEM_W(ctx->r9, 0X0);
            goto L_800BD7E4;
    }
    goto skip_10;
    // 0x800BD7CC: lw          $v1, 0x0($t1)
    ctx->r3 = MEM_W(ctx->r9, 0X0);
    skip_10:
    // 0x800BD7D0: lbu         $t7, 0x3($t9)
    ctx->r15 = MEM_BU(ctx->r25, 0X3);
    // 0x800BD7D4: andi        $t8, $t7, 0x40
    ctx->r24 = ctx->r15 & 0X40;
    // 0x800BD7D8: bnel        $t8, $zero, L_800BD7FC
    if (ctx->r24 != 0) {
        // 0x800BD7DC: lbu         $t4, 0x0($s1)
        ctx->r12 = MEM_BU(ctx->r17, 0X0);
            goto L_800BD7FC;
    }
    goto skip_11;
    // 0x800BD7DC: lbu         $t4, 0x0($s1)
    ctx->r12 = MEM_BU(ctx->r17, 0X0);
    skip_11:
    // 0x800BD7E0: lw          $v1, 0x0($t1)
    ctx->r3 = MEM_W(ctx->r9, 0X0);
L_800BD7E4:
    // 0x800BD7E4: lw          $t7, 0x68($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X68);
    // 0x800BD7E8: lw          $t6, 0x68($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X68);
    // 0x800BD7EC: sll         $t2, $v1, 3
    ctx->r10 = S32(ctx->r3 << 3);
    // 0x800BD7F0: bgez        $t2, L_800BD808
    if (SIGNED(ctx->r10) >= 0) {
        // 0x800BD7F4: sll         $t9, $v1, 4
        ctx->r25 = S32(ctx->r3 << 4);
            goto L_800BD808;
    }
    // 0x800BD7F4: sll         $t9, $v1, 4
    ctx->r25 = S32(ctx->r3 << 4);
    // 0x800BD7F8: lbu         $t4, 0x0($s1)
    ctx->r12 = MEM_BU(ctx->r17, 0X0);
L_800BD7FC:
    // 0x800BD7FC: ori         $t5, $t4, 0x20
    ctx->r13 = ctx->r12 | 0X20;
    // 0x800BD800: b           L_800BDAE4
    // 0x800BD804: sb          $t5, 0x0($s1)
    MEM_B(0X0, ctx->r17) = ctx->r13;
        goto L_800BDAE4;
    // 0x800BD804: sb          $t5, 0x0($s1)
    MEM_B(0X0, ctx->r17) = ctx->r13;
L_800BD808:
    // 0x800BD808: lbu         $a0, 0x1($s1)
    ctx->r4 = MEM_BU(ctx->r17, 0X1);
    // 0x800BD80C: addiu       $at, $zero, 0xFF
    ctx->r1 = ADD32(0, 0XFF);
    // 0x800BD810: bne         $a0, $at, L_800BD824
    if (ctx->r4 != ctx->r1) {
        // 0x800BD814: or          $v0, $a0, $zero
        ctx->r2 = ctx->r4 | 0;
            goto L_800BD824;
    }
    // 0x800BD814: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x800BD818: bgezl       $t9, L_800BDBD0
    if (SIGNED(ctx->r25) >= 0) {
        // 0x800BD81C: lw          $ra, 0x2C($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X2C);
            goto L_800BDBD0;
    }
    goto skip_12;
    // 0x800BD81C: lw          $ra, 0x2C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X2C);
    skip_12:
    // 0x800BD820: lh          $v0, 0x1C($t7)
    ctx->r2 = MEM_H(ctx->r15, 0X1C);
L_800BD824:
    // 0x800BD824: bnel        $v0, $zero, L_800BD8A4
    if (ctx->r2 != 0) {
        // 0x800BD828: lh          $t4, 0xC($s4)
        ctx->r12 = MEM_H(ctx->r20, 0XC);
            goto L_800BD8A4;
    }
    goto skip_13;
    // 0x800BD828: lh          $t4, 0xC($s4)
    ctx->r12 = MEM_H(ctx->r20, 0XC);
    skip_13:
    // 0x800BD82C: lw          $t8, 0x68($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X68);
    // 0x800BD830: lh          $t2, 0x22($s1)
    ctx->r10 = MEM_H(ctx->r17, 0X22);
    // 0x800BD834: lh          $t1, 0x1E($t8)
    ctx->r9 = MEM_H(ctx->r24, 0X1E);
    // 0x800BD838: lbu         $a0, 0x6($t8)
    ctx->r4 = MEM_BU(ctx->r24, 0X6);
    // 0x800BD83C: addu        $t0, $s2, $t1
    ctx->r8 = ADD32(ctx->r18, ctx->r9);
    // 0x800BD840: addu        $s2, $t0, $t2
    ctx->r18 = ADD32(ctx->r8, ctx->r10);
    // 0x800BD844: jal         0x800BAA08
    // 0x800BD848: andi        $a1, $s2, 0xFF
    ctx->r5 = ctx->r18 & 0XFF;
    Audio_GetDrum(rdram, ctx);
        goto after_21;
    // 0x800BD848: andi        $a1, $s2, 0xFF
    ctx->r5 = ctx->r18 & 0XFF;
    after_21:
    // 0x800BD84C: bne         $v0, $zero, L_800BD86C
    if (ctx->r2 != 0) {
        // 0x800BD850: addiu       $v1, $v0, 0x4
        ctx->r3 = ADD32(ctx->r2, 0X4);
            goto L_800BD86C;
    }
    // 0x800BD850: addiu       $v1, $v0, 0x4
    ctx->r3 = ADD32(ctx->r2, 0X4);
    // 0x800BD854: lbu         $t5, 0x0($s1)
    ctx->r13 = MEM_BU(ctx->r17, 0X0);
    // 0x800BD858: lh          $t9, 0x38($s1)
    ctx->r25 = MEM_H(ctx->r17, 0X38);
    // 0x800BD85C: ori         $t6, $t5, 0x20
    ctx->r14 = ctx->r13 | 0X20;
    // 0x800BD860: sb          $t6, 0x0($s1)
    MEM_B(0X0, ctx->r17) = ctx->r14;
    // 0x800BD864: b           L_800BDBCC
    // 0x800BD868: sh          $t9, 0x3C($s1)
    MEM_H(0X3C, ctx->r17) = ctx->r25;
        goto L_800BDBCC;
    // 0x800BD868: sh          $t9, 0x3C($s1)
    MEM_H(0X3C, ctx->r17) = ctx->r25;
L_800BD86C:
    // 0x800BD86C: lw          $t7, 0xC($v0)
    ctx->r15 = MEM_W(ctx->r2, 0XC);
    // 0x800BD870: lw          $t0, 0x0($s1)
    ctx->r8 = MEM_W(ctx->r17, 0X0);
    // 0x800BD874: sw          $t7, 0x1C($s1)
    MEM_W(0X1C, ctx->r17) = ctx->r15;
    // 0x800BD878: lbu         $t1, 0x0($v0)
    ctx->r9 = MEM_BU(ctx->r2, 0X0);
    // 0x800BD87C: sll         $t3, $t0, 6
    ctx->r11 = S32(ctx->r8 << 6);
    // 0x800BD880: bltz        $t3, L_800BD890
    if (SIGNED(ctx->r11) < 0) {
        // 0x800BD884: sb          $t1, 0x18($s1)
        MEM_B(0X18, ctx->r17) = ctx->r9;
            goto L_800BD890;
    }
    // 0x800BD884: sb          $t1, 0x18($s1)
    MEM_B(0X18, ctx->r17) = ctx->r9;
    // 0x800BD888: lbu         $t8, 0x1($v0)
    ctx->r24 = MEM_BU(ctx->r2, 0X1);
    // 0x800BD88C: sb          $t8, 0x5($s1)
    MEM_B(0X5, ctx->r17) = ctx->r24;
L_800BD890:
    // 0x800BD890: sw          $v1, 0x48($s1)
    MEM_W(0X48, ctx->r17) = ctx->r3;
    // 0x800BD894: lwc1        $f4, 0x4($v1)
    ctx->f4.u32l = MEM_W(ctx->r3, 0X4);
    // 0x800BD898: b           L_800BDADC
    // 0x800BD89C: swc1        $f4, 0x24($s1)
    MEM_W(0X24, ctx->r17) = ctx->f4.u32l;
        goto L_800BDADC;
    // 0x800BD89C: swc1        $f4, 0x24($s1)
    MEM_W(0X24, ctx->r17) = ctx->f4.u32l;
    // 0x800BD8A0: lh          $t4, 0xC($s4)
    ctx->r12 = MEM_H(ctx->r20, 0XC);
L_800BD8A4:
    // 0x800BD8A4: lh          $t9, 0x1E($t6)
    ctx->r25 = MEM_H(ctx->r14, 0X1E);
    // 0x800BD8A8: lh          $t1, 0x22($s1)
    ctx->r9 = MEM_H(ctx->r17, 0X22);
    // 0x800BD8AC: addu        $t5, $s2, $t4
    ctx->r13 = ADD32(ctx->r18, ctx->r12);
    // 0x800BD8B0: addu        $t7, $t5, $t9
    ctx->r15 = ADD32(ctx->r13, ctx->r25);
    // 0x800BD8B4: addu        $s2, $t7, $t1
    ctx->r18 = ADD32(ctx->r15, ctx->r9);
    // 0x800BD8B8: andi        $a1, $s2, 0xFF
    ctx->r5 = ctx->r18 & 0XFF;
    // 0x800BD8BC: slti        $at, $a1, 0x80
    ctx->r1 = SIGNED(ctx->r5) < 0X80 ? 1 : 0;
    // 0x800BD8C0: bne         $at, $zero, L_800BD8D8
    if (ctx->r1 != 0) {
        // 0x800BD8C4: or          $s2, $a1, $zero
        ctx->r18 = ctx->r5 | 0;
            goto L_800BD8D8;
    }
    // 0x800BD8C4: or          $s2, $a1, $zero
    ctx->r18 = ctx->r5 | 0;
    // 0x800BD8C8: lbu         $t3, 0x0($s1)
    ctx->r11 = MEM_BU(ctx->r17, 0X0);
    // 0x800BD8CC: ori         $t8, $t3, 0x20
    ctx->r24 = ctx->r11 | 0X20;
    // 0x800BD8D0: b           L_800BDADC
    // 0x800BD8D4: sb          $t8, 0x0($s1)
    MEM_B(0X0, ctx->r17) = ctx->r24;
        goto L_800BDADC;
    // 0x800BD8D4: sb          $t8, 0x0($s1)
    MEM_B(0X0, ctx->r17) = ctx->r24;
L_800BD8D8:
    // 0x800BD8D8: addiu       $at, $zero, 0xFF
    ctx->r1 = ADD32(0, 0XFF);
    // 0x800BD8DC: bne         $a0, $at, L_800BD8EC
    if (ctx->r4 != ctx->r1) {
        // 0x800BD8E0: lw          $t4, 0x68($sp)
        ctx->r12 = MEM_W(ctx->r29, 0X68);
            goto L_800BD8EC;
    }
    // 0x800BD8E0: lw          $t4, 0x68($sp)
    ctx->r12 = MEM_W(ctx->r29, 0X68);
    // 0x800BD8E4: b           L_800BD8F0
    // 0x800BD8E8: lw          $a0, 0x40($t4)
    ctx->r4 = MEM_W(ctx->r12, 0X40);
        goto L_800BD8F0;
    // 0x800BD8E8: lw          $a0, 0x40($t4)
    ctx->r4 = MEM_W(ctx->r12, 0X40);
L_800BD8EC:
    // 0x800BD8EC: lw          $a0, 0x44($s1)
    ctx->r4 = MEM_W(ctx->r17, 0X44);
L_800BD8F0:
    // 0x800BD8F0: lbu         $t6, 0x8($s1)
    ctx->r14 = MEM_BU(ctx->r17, 0X8);
    // 0x800BD8F4: beq         $t6, $zero, L_800BDA7C
    if (ctx->r14 == 0) {
        // 0x800BD8F8: nop
    
            goto L_800BDA7C;
    }
    // 0x800BD8F8: nop

    // 0x800BD8FC: lbu         $v0, 0x4($s1)
    ctx->r2 = MEM_BU(ctx->r17, 0X4);
    // 0x800BD900: slt         $at, $v0, $a1
    ctx->r1 = SIGNED(ctx->r2) < SIGNED(ctx->r5) ? 1 : 0;
    // 0x800BD904: beq         $at, $zero, L_800BD914
    if (ctx->r1 == 0) {
        // 0x800BD908: or          $a2, $v0, $zero
        ctx->r6 = ctx->r2 | 0;
            goto L_800BD914;
    }
    // 0x800BD908: or          $a2, $v0, $zero
    ctx->r6 = ctx->r2 | 0;
    // 0x800BD90C: b           L_800BD914
    // 0x800BD910: or          $a2, $a1, $zero
    ctx->r6 = ctx->r5 | 0;
        goto L_800BD914;
    // 0x800BD910: or          $a2, $a1, $zero
    ctx->r6 = ctx->r5 | 0;
L_800BD914:
    // 0x800BD914: beq         $a0, $zero, L_800BD940
    if (ctx->r4 == 0) {
        // 0x800BD918: lui         $at, 0x3F80
        ctx->r1 = S32(0X3F80 << 16);
            goto L_800BD940;
    }
    // 0x800BD918: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x800BD91C: jal         0x800BA8AC
    // 0x800BD920: or          $a1, $a2, $zero
    ctx->r5 = ctx->r6 | 0;
    Audio_GetInstrumentTunedSample(rdram, ctx);
        goto after_22;
    // 0x800BD920: or          $a1, $a2, $zero
    ctx->r5 = ctx->r6 | 0;
    after_22:
    // 0x800BD924: lw          $t5, 0x48($s1)
    ctx->r13 = MEM_W(ctx->r17, 0X48);
    // 0x800BD928: xor         $t9, $v0, $t5
    ctx->r25 = ctx->r2 ^ ctx->r13;
    // 0x800BD92C: sltiu       $t9, $t9, 0x1
    ctx->r25 = ctx->r25 < 0X1 ? 1 : 0;
    // 0x800BD930: sw          $t9, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r25;
    // 0x800BD934: sw          $v0, 0x48($s1)
    MEM_W(0X48, ctx->r17) = ctx->r2;
    // 0x800BD938: b           L_800BD948
    // 0x800BD93C: lwc1        $f0, 0x4($v0)
    ctx->f0.u32l = MEM_W(ctx->r2, 0X4);
        goto L_800BD948;
    // 0x800BD93C: lwc1        $f0, 0x4($v0)
    ctx->f0.u32l = MEM_W(ctx->r2, 0X4);
L_800BD940:
    // 0x800BD940: mtc1        $at, $f0
    ctx->f0.u32l = ctx->r1;
    // 0x800BD944: sw          $zero, 0x48($s1)
    MEM_W(0X48, ctx->r17) = 0;
L_800BD948:
    // 0x800BD948: lui         $v1, 0x800F
    ctx->r3 = S32(0X800F << 16);
    // 0x800BD94C: lbu         $t0, 0x4($s1)
    ctx->r8 = MEM_BU(ctx->r17, 0X4);
    // 0x800BD950: addiu       $v1, $v1, -0x321C
    ctx->r3 = ADD32(ctx->r3, -0X321C);
    // 0x800BD954: sll         $t7, $s2, 2
    ctx->r15 = S32(ctx->r18 << 2);
    // 0x800BD958: addu        $t1, $v1, $t7
    ctx->r9 = ADD32(ctx->r3, ctx->r15);
    // 0x800BD95C: lwc1        $f6, 0x0($t1)
    ctx->f6.u32l = MEM_W(ctx->r9, 0X0);
    // 0x800BD960: lbu         $t8, 0x8($s1)
    ctx->r24 = MEM_BU(ctx->r17, 0X8);
    // 0x800BD964: sll         $t2, $t0, 2
    ctx->r10 = S32(ctx->r8 << 2);
    // 0x800BD968: addu        $t3, $v1, $t2
    ctx->r11 = ADD32(ctx->r3, ctx->r10);
    // 0x800BD96C: lwc1        $f8, 0x0($t3)
    ctx->f8.u32l = MEM_W(ctx->r11, 0X0);
    // 0x800BD970: mul.s       $f2, $f6, $f0
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f2.fl = MUL_S(ctx->f6.fl, ctx->f0.fl);
    // 0x800BD974: addiu       $at, $zero, -0x81
    ctx->r1 = ADD32(0, -0X81);
    // 0x800BD978: and         $t4, $t8, $at
    ctx->r12 = ctx->r24 & ctx->r1;
    // 0x800BD97C: addiu       $t6, $t4, -0x1
    ctx->r14 = ADD32(ctx->r12, -0X1);
    // 0x800BD980: sltiu       $at, $t6, 0x5
    ctx->r1 = ctx->r14 < 0X5 ? 1 : 0;
    // 0x800BD984: mul.s       $f12, $f8, $f0
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f12.fl = MUL_S(ctx->f8.fl, ctx->f0.fl);
    // 0x800BD988: beq         $at, $zero, L_800BD9AC
    if (ctx->r1 == 0) {
        // 0x800BD98C: sll         $t6, $t6, 2
        ctx->r14 = S32(ctx->r14 << 2);
            goto L_800BD9AC;
    }
    // 0x800BD98C: sll         $t6, $t6, 2
    ctx->r14 = S32(ctx->r14 << 2);
    // 0x800BD990: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x800BD994: addu        $at, $at, $t6
    gpr jr_addend_800BD99C = ctx->r14;
    ctx->r1 = ADD32(ctx->r1, ctx->r14);
    // 0x800BD998: lw          $t6, -0x42E0($at)
    ctx->r14 = ADD32(ctx->r1, -0X42E0);
    // 0x800BD99C: jr          $t6
    // 0x800BD9A0: nop

    switch (jr_addend_800BD99C >> 2) {
        case 0: goto L_800BD9A4; break;
        case 1: goto L_800BD9AC; break;
        case 2: goto L_800BD9A4; break;
        case 3: goto L_800BD9AC; break;
        case 4: goto L_800BD9A4; break;
        default: switch_error(__func__, 0x800BD99C, 0x800EBD20);
    }
    // 0x800BD9A0: nop

L_800BD9A4:
    // 0x800BD9A4: b           L_800BD9B0
    // 0x800BD9A8: mov.s       $f0, $f12
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 12);
    ctx->f0.fl = ctx->f12.fl;
        goto L_800BD9B0;
    // 0x800BD9A8: mov.s       $f0, $f12
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 12);
    ctx->f0.fl = ctx->f12.fl;
L_800BD9AC:
    // 0x800BD9AC: mov.s       $f0, $f2
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    ctx->f0.fl = ctx->f2.fl;
L_800BD9B0:
    // 0x800BD9B0: div.s       $f10, $f2, $f0
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f10.fl = DIV_S(ctx->f2.fl, ctx->f0.fl);
    // 0x800BD9B4: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x800BD9B8: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
    // 0x800BD9BC: addiu       $v0, $s1, 0x8
    ctx->r2 = ADD32(ctx->r17, 0X8);
    // 0x800BD9C0: lui         $at, 0x46FE
    ctx->r1 = S32(0X46FE << 16);
    // 0x800BD9C4: sub.s       $f18, $f10, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f18.fl = ctx->f10.fl - ctx->f16.fl;
    // 0x800BD9C8: swc1        $f18, 0xC($v0)
    MEM_W(0XC, ctx->r2) = ctx->f18.u32l;
    // 0x800BD9CC: lbu         $t5, 0x8($s1)
    ctx->r13 = MEM_BU(ctx->r17, 0X8);
    // 0x800BD9D0: andi        $t9, $t5, 0x80
    ctx->r25 = ctx->r13 & 0X80;
    // 0x800BD9D4: beql        $t9, $zero, L_800BDA34
    if (ctx->r25 == 0) {
        // 0x800BD9D8: lhu         $t3, 0x20($s1)
        ctx->r11 = MEM_HU(ctx->r17, 0X20);
            goto L_800BDA34;
    }
    goto skip_14;
    // 0x800BD9D8: lhu         $t3, 0x20($s1)
    ctx->r11 = MEM_HU(ctx->r17, 0X20);
    skip_14:
    // 0x800BD9DC: lhu         $t7, 0x8($s4)
    ctx->r15 = MEM_HU(ctx->r20, 0X8);
    // 0x800BD9E0: lui         $t0, 0x8004
    ctx->r8 = S32(0X8004 << 16);
    // 0x800BD9E4: lh          $t0, 0x554C($t0)
    ctx->r8 = MEM_H(ctx->r8, 0X554C);
    // 0x800BD9E8: mtc1        $t7, $f4
    ctx->f4.u32l = ctx->r15;
    // 0x800BD9EC: lh          $t1, 0x38($s1)
    ctx->r9 = MEM_H(ctx->r17, 0X38);
    // 0x800BD9F0: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x800BD9F4: cvt.s.w     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
    // 0x800BD9F8: mtc1        $t0, $f4
    ctx->f4.u32l = ctx->r8;
    // 0x800BD9FC: mtc1        $t1, $f16
    ctx->f16.u32l = ctx->r9;
    // 0x800BDA00: lhu         $t2, 0x20($s1)
    ctx->r10 = MEM_HU(ctx->r17, 0X20);
    // 0x800BDA04: cvt.s.w     $f18, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    ctx->f18.fl = CVT_S_W(ctx->f16.u32l);
    // 0x800BDA08: mul.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = MUL_S(ctx->f6.fl, ctx->f8.fl);
    // 0x800BDA0C: mtc1        $t2, $f16
    ctx->f16.u32l = ctx->r10;
    // 0x800BDA10: cvt.s.w     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
    // 0x800BDA14: cvt.s.w     $f4, $f16
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 16);
    ctx->f4.fl = CVT_S_W(ctx->f16.u32l);
    // 0x800BDA18: mul.s       $f8, $f18, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = MUL_S(ctx->f18.fl, ctx->f6.fl);
    // 0x800BDA1C: nop

    // 0x800BDA20: mul.s       $f18, $f8, $f4
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f18.fl = MUL_S(ctx->f8.fl, ctx->f4.fl);
    // 0x800BDA24: div.s       $f6, $f10, $f18
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f6.fl = DIV_S(ctx->f10.fl, ctx->f18.fl);
    // 0x800BDA28: b           L_800BDA50
    // 0x800BDA2C: swc1        $f6, 0x8($v0)
    MEM_W(0X8, ctx->r2) = ctx->f6.u32l;
        goto L_800BDA50;
    // 0x800BDA2C: swc1        $f6, 0x8($v0)
    MEM_W(0X8, ctx->r2) = ctx->f6.u32l;
    // 0x800BDA30: lhu         $t3, 0x20($s1)
    ctx->r11 = MEM_HU(ctx->r17, 0X20);
L_800BDA34:
    // 0x800BDA34: lui         $at, 0x42FE
    ctx->r1 = S32(0X42FE << 16);
    // 0x800BDA38: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
    // 0x800BDA3C: mtc1        $t3, $f8
    ctx->f8.u32l = ctx->r11;
    // 0x800BDA40: nop

    // 0x800BDA44: cvt.s.w     $f4, $f8
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    ctx->f4.fl = CVT_S_W(ctx->f8.u32l);
    // 0x800BDA48: div.s       $f10, $f16, $f4
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f10.fl = DIV_S(ctx->f16.fl, ctx->f4.fl);
    // 0x800BDA4C: swc1        $f10, 0x8($v0)
    MEM_W(0X8, ctx->r2) = ctx->f10.u32l;
L_800BDA50:
    // 0x800BDA50: mtc1        $zero, $f18
    ctx->f18.u32l = 0;
    // 0x800BDA54: addiu       $at, $zero, -0x81
    ctx->r1 = ADD32(0, -0X81);
    // 0x800BDA58: swc1        $f18, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->f18.u32l;
    // 0x800BDA5C: lbu         $t8, 0x8($s1)
    ctx->r24 = MEM_BU(ctx->r17, 0X8);
    // 0x800BDA60: swc1        $f0, 0x24($s1)
    MEM_W(0X24, ctx->r17) = ctx->f0.u32l;
    // 0x800BDA64: and         $t4, $t8, $at
    ctx->r12 = ctx->r24 & ctx->r1;
    // 0x800BDA68: addiu       $at, $zero, 0x5
    ctx->r1 = ADD32(0, 0X5);
    // 0x800BDA6C: bnel        $t4, $at, L_800BDAE0
    if (ctx->r12 != ctx->r1) {
        // 0x800BDA70: lh          $t2, 0x38($s1)
        ctx->r10 = MEM_H(ctx->r17, 0X38);
            goto L_800BDAE0;
    }
    goto skip_15;
    // 0x800BDA70: lh          $t2, 0x38($s1)
    ctx->r10 = MEM_H(ctx->r17, 0X38);
    skip_15:
    // 0x800BDA74: b           L_800BDADC
    // 0x800BDA78: sb          $s2, 0x4($s1)
    MEM_B(0X4, ctx->r17) = ctx->r18;
        goto L_800BDADC;
    // 0x800BDA78: sb          $s2, 0x4($s1)
    MEM_B(0X4, ctx->r17) = ctx->r18;
L_800BDA7C:
    // 0x800BDA7C: beq         $a0, $zero, L_800BDAC4
    if (ctx->r4 == 0) {
        // 0x800BDA80: lui         $v1, 0x800F
        ctx->r3 = S32(0X800F << 16);
            goto L_800BDAC4;
    }
    // 0x800BDA80: lui         $v1, 0x800F
    ctx->r3 = S32(0X800F << 16);
    // 0x800BDA84: jal         0x800BA8AC
    // 0x800BDA88: nop

    Audio_GetInstrumentTunedSample(rdram, ctx);
        goto after_23;
    // 0x800BDA88: nop

    after_23:
    // 0x800BDA8C: lw          $t6, 0x48($s1)
    ctx->r14 = MEM_W(ctx->r17, 0X48);
    // 0x800BDA90: lui         $v1, 0x800F
    ctx->r3 = S32(0X800F << 16);
    // 0x800BDA94: addiu       $v1, $v1, -0x321C
    ctx->r3 = ADD32(ctx->r3, -0X321C);
    // 0x800BDA98: xor         $t5, $v0, $t6
    ctx->r13 = ctx->r2 ^ ctx->r14;
    // 0x800BDA9C: sltiu       $t5, $t5, 0x1
    ctx->r13 = ctx->r13 < 0X1 ? 1 : 0;
    // 0x800BDAA0: sw          $t5, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r13;
    // 0x800BDAA4: sw          $v0, 0x48($s1)
    MEM_W(0X48, ctx->r17) = ctx->r2;
    // 0x800BDAA8: sll         $t9, $s2, 2
    ctx->r25 = S32(ctx->r18 << 2);
    // 0x800BDAAC: addu        $t7, $v1, $t9
    ctx->r15 = ADD32(ctx->r3, ctx->r25);
    // 0x800BDAB0: lwc1        $f6, 0x0($t7)
    ctx->f6.u32l = MEM_W(ctx->r15, 0X0);
    // 0x800BDAB4: lwc1        $f8, 0x4($v0)
    ctx->f8.u32l = MEM_W(ctx->r2, 0X4);
    // 0x800BDAB8: mul.s       $f16, $f6, $f8
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f16.fl = MUL_S(ctx->f6.fl, ctx->f8.fl);
    // 0x800BDABC: b           L_800BDADC
    // 0x800BDAC0: swc1        $f16, 0x24($s1)
    MEM_W(0X24, ctx->r17) = ctx->f16.u32l;
        goto L_800BDADC;
    // 0x800BDAC0: swc1        $f16, 0x24($s1)
    MEM_W(0X24, ctx->r17) = ctx->f16.u32l;
L_800BDAC4:
    // 0x800BDAC4: addiu       $v1, $v1, -0x321C
    ctx->r3 = ADD32(ctx->r3, -0X321C);
    // 0x800BDAC8: sll         $t1, $s2, 2
    ctx->r9 = S32(ctx->r18 << 2);
    // 0x800BDACC: sw          $zero, 0x48($s1)
    MEM_W(0X48, ctx->r17) = 0;
    // 0x800BDAD0: addu        $t0, $v1, $t1
    ctx->r8 = ADD32(ctx->r3, ctx->r9);
    // 0x800BDAD4: lwc1        $f4, 0x0($t0)
    ctx->f4.u32l = MEM_W(ctx->r8, 0X0);
    // 0x800BDAD8: swc1        $f4, 0x24($s1)
    MEM_W(0X24, ctx->r17) = ctx->f4.u32l;
L_800BDADC:
    // 0x800BDADC: lh          $t2, 0x38($s1)
    ctx->r10 = MEM_H(ctx->r17, 0X38);
L_800BDAE0:
    // 0x800BDAE0: sh          $t2, 0x3C($s1)
    MEM_H(0X3C, ctx->r17) = ctx->r10;
L_800BDAE4:
    // 0x800BDAE4: lw          $v0, 0x0($s1)
    ctx->r2 = MEM_W(ctx->r17, 0X0);
    // 0x800BDAE8: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x800BDAEC: sll         $t3, $v0, 2
    ctx->r11 = S32(ctx->r2 << 2);
    // 0x800BDAF0: srl         $t8, $t3, 31
    ctx->r24 = S32(U32(ctx->r11) >> 31);
    // 0x800BDAF4: bne         $t8, $at, L_800BDB24
    if (ctx->r24 != ctx->r1) {
        // 0x800BDAF8: sll         $t7, $v0, 3
        ctx->r15 = S32(ctx->r2 << 3);
            goto L_800BDB24;
    }
    // 0x800BDAF8: sll         $t7, $v0, 3
    ctx->r15 = S32(ctx->r2 << 3);
    // 0x800BDAFC: lw          $t4, 0x40($s1)
    ctx->r12 = MEM_W(ctx->r17, 0X40);
    // 0x800BDB00: sll         $t5, $v0, 3
    ctx->r13 = S32(ctx->r2 << 3);
    // 0x800BDB04: bne         $t4, $zero, L_800BDB14
    if (ctx->r12 != 0) {
        // 0x800BDB08: nop
    
            goto L_800BDB14;
    }
    // 0x800BDB08: nop

    // 0x800BDB0C: bgezl       $t5, L_800BDBD0
    if (SIGNED(ctx->r13) >= 0) {
        // 0x800BDB10: lw          $ra, 0x2C($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X2C);
            goto L_800BDBD0;
    }
    goto skip_16;
    // 0x800BDB10: lw          $ra, 0x2C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X2C);
    skip_16:
L_800BDB14:
    // 0x800BDB14: jal         0x800BB108
    // 0x800BDB18: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    Audio_SeqLayerNoteDecay(rdram, ctx);
        goto after_24;
    // 0x800BDB18: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    after_24:
    // 0x800BDB1C: b           L_800BDBD0
    // 0x800BDB20: lw          $ra, 0x2C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X2C);
        goto L_800BDBD0;
    // 0x800BDB20: lw          $ra, 0x2C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X2C);
L_800BDB24:
    // 0x800BDB24: bltz        $t7, L_800BDB34
    if (SIGNED(ctx->r15) < 0) {
        // 0x800BDB28: or          $s2, $zero, $zero
        ctx->r18 = 0 | 0;
            goto L_800BDB34;
    }
    // 0x800BDB28: or          $s2, $zero, $zero
    ctx->r18 = 0 | 0;
    // 0x800BDB2C: b           L_800BDB98
    // 0x800BDB30: addiu       $s2, $zero, 0x1
    ctx->r18 = ADD32(0, 0X1);
        goto L_800BDB98;
    // 0x800BDB30: addiu       $s2, $zero, 0x1
    ctx->r18 = ADD32(0, 0X1);
L_800BDB34:
    // 0x800BDB34: lw          $a0, 0x40($s1)
    ctx->r4 = MEM_W(ctx->r17, 0X40);
    // 0x800BDB38: beq         $a0, $zero, L_800BDB50
    if (ctx->r4 == 0) {
        // 0x800BDB3C: nop
    
            goto L_800BDB50;
    }
    // 0x800BDB3C: nop

    // 0x800BDB40: lbu         $t1, 0x2($s1)
    ctx->r9 = MEM_BU(ctx->r17, 0X2);
    // 0x800BDB44: lw          $t0, 0x44($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X44);
    // 0x800BDB48: bne         $t1, $zero, L_800BDB58
    if (ctx->r9 != 0) {
        // 0x800BDB4C: nop
    
            goto L_800BDB58;
    }
    // 0x800BDB4C: nop

L_800BDB50:
    // 0x800BDB50: b           L_800BDB98
    // 0x800BDB54: addiu       $s2, $zero, 0x1
    ctx->r18 = ADD32(0, 0X1);
        goto L_800BDB98;
    // 0x800BDB54: addiu       $s2, $zero, 0x1
    ctx->r18 = ADD32(0, 0X1);
L_800BDB58:
    // 0x800BDB58: bnel        $t0, $zero, L_800BDB74
    if (ctx->r8 != 0) {
        // 0x800BDB5C: lw          $t2, 0x44($a0)
        ctx->r10 = MEM_W(ctx->r4, 0X44);
            goto L_800BDB74;
    }
    goto skip_17;
    // 0x800BDB5C: lw          $t2, 0x44($a0)
    ctx->r10 = MEM_W(ctx->r4, 0X44);
    skip_17:
    // 0x800BDB60: jal         0x800BB108
    // 0x800BDB64: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    Audio_SeqLayerNoteDecay(rdram, ctx);
        goto after_25;
    // 0x800BDB64: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    after_25:
    // 0x800BDB68: b           L_800BDB98
    // 0x800BDB6C: addiu       $s2, $zero, 0x1
    ctx->r18 = ADD32(0, 0X1);
        goto L_800BDB98;
    // 0x800BDB6C: addiu       $s2, $zero, 0x1
    ctx->r18 = ADD32(0, 0X1);
    // 0x800BDB70: lw          $t2, 0x44($a0)
    ctx->r10 = MEM_W(ctx->r4, 0X44);
L_800BDB74:
    // 0x800BDB74: beql        $s1, $t2, L_800BDB88
    if (ctx->r17 == ctx->r10) {
        // 0x800BDB78: lw          $t3, 0x48($s1)
        ctx->r11 = MEM_W(ctx->r17, 0X48);
            goto L_800BDB88;
    }
    goto skip_18;
    // 0x800BDB78: lw          $t3, 0x48($s1)
    ctx->r11 = MEM_W(ctx->r17, 0X48);
    skip_18:
    // 0x800BDB7C: b           L_800BDB98
    // 0x800BDB80: addiu       $s2, $zero, 0x1
    ctx->r18 = ADD32(0, 0X1);
        goto L_800BDB98;
    // 0x800BDB80: addiu       $s2, $zero, 0x1
    ctx->r18 = ADD32(0, 0X1);
    // 0x800BDB84: lw          $t3, 0x48($s1)
    ctx->r11 = MEM_W(ctx->r17, 0X48);
L_800BDB88:
    // 0x800BDB88: bne         $t3, $zero, L_800BDB98
    if (ctx->r11 != 0) {
        // 0x800BDB8C: nop
    
            goto L_800BDB98;
    }
    // 0x800BDB8C: nop

    // 0x800BDB90: jal         0x800BB24C
    // 0x800BDB94: or          $a1, $s1, $zero
    ctx->r5 = ctx->r17 | 0;
    Audio_InitSyntheticWave(rdram, ctx);
        goto after_26;
    // 0x800BDB94: or          $a1, $s1, $zero
    ctx->r5 = ctx->r17 | 0;
    after_26:
L_800BDB98:
    // 0x800BDB98: beql        $s2, $zero, L_800BDBB0
    if (ctx->r18 == 0) {
        // 0x800BDB9C: lw          $a0, 0x40($s1)
        ctx->r4 = MEM_W(ctx->r17, 0X40);
            goto L_800BDBB0;
    }
    goto skip_19;
    // 0x800BDB9C: lw          $a0, 0x40($s1)
    ctx->r4 = MEM_W(ctx->r17, 0X40);
    skip_19:
    // 0x800BDBA0: jal         0x800BBA2C
    // 0x800BDBA4: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    Audio_AllocNote(rdram, ctx);
        goto after_27;
    // 0x800BDBA4: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    after_27:
    // 0x800BDBA8: sw          $v0, 0x40($s1)
    MEM_W(0X40, ctx->r17) = ctx->r2;
    // 0x800BDBAC: lw          $a0, 0x40($s1)
    ctx->r4 = MEM_W(ctx->r17, 0X40);
L_800BDBB0:
    // 0x800BDBB0: beql        $a0, $zero, L_800BDBD0
    if (ctx->r4 == 0) {
        // 0x800BDBB4: lw          $ra, 0x2C($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X2C);
            goto L_800BDBD0;
    }
    goto skip_20;
    // 0x800BDBB4: lw          $ra, 0x2C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X2C);
    skip_20:
    // 0x800BDBB8: lw          $t8, 0x44($a0)
    ctx->r24 = MEM_W(ctx->r4, 0X44);
    // 0x800BDBBC: bnel        $s1, $t8, L_800BDBD0
    if (ctx->r17 != ctx->r24) {
        // 0x800BDBC0: lw          $ra, 0x2C($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X2C);
            goto L_800BDBD0;
    }
    goto skip_21;
    // 0x800BDBC0: lw          $ra, 0x2C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X2C);
    skip_21:
    // 0x800BDBC4: jal         0x800BC4B0
    // 0x800BDBC8: nop

    Audio_NoteVibratoInit(rdram, ctx);
        goto after_28;
    // 0x800BDBC8: nop

    after_28:
L_800BDBCC:
    // 0x800BDBCC: lw          $ra, 0x2C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X2C);
L_800BDBD0:
    // 0x800BDBD0: lw          $s0, 0x18($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X18);
    // 0x800BDBD4: lw          $s1, 0x1C($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X1C);
    // 0x800BDBD8: lw          $s2, 0x20($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X20);
    // 0x800BDBDC: lw          $s3, 0x24($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X24);
    // 0x800BDBE0: lw          $s4, 0x28($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X28);
    // 0x800BDBE4: jr          $ra
    // 0x800BDBE8: addiu       $sp, $sp, 0x70
    ctx->r29 = ADD32(ctx->r29, 0X70);
    return;
    // 0x800BDBE8: addiu       $sp, $sp, 0x70
    ctx->r29 = ADD32(ctx->r29, 0X70);
;}
RECOMP_FUNC void func_800BD8F4(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800BD8F4: beq         $t6, $zero, L_800BDA7C
    if (ctx->r14 == 0) {
        // 0x800BD8F8: nop
    
            goto L_800BDA7C;
    }
    // 0x800BD8F8: nop

    // 0x800BD8FC: lbu         $v0, 0x4($s1)
    ctx->r2 = MEM_BU(ctx->r17, 0X4);
    // 0x800BD900: slt         $at, $v0, $a1
    ctx->r1 = SIGNED(ctx->r2) < SIGNED(ctx->r5) ? 1 : 0;
    // 0x800BD904: beq         $at, $zero, L_800BD914
    if (ctx->r1 == 0) {
        // 0x800BD908: or          $a2, $v0, $zero
        ctx->r6 = ctx->r2 | 0;
            goto L_800BD914;
    }
    // 0x800BD908: or          $a2, $v0, $zero
    ctx->r6 = ctx->r2 | 0;
    // 0x800BD90C: b           L_800BD914
    // 0x800BD910: or          $a2, $a1, $zero
    ctx->r6 = ctx->r5 | 0;
        goto L_800BD914;
    // 0x800BD910: or          $a2, $a1, $zero
    ctx->r6 = ctx->r5 | 0;
L_800BD914:
    // 0x800BD914: beq         $a0, $zero, L_800BD940
    if (ctx->r4 == 0) {
        // 0x800BD918: lui         $at, 0x3F80
        ctx->r1 = S32(0X3F80 << 16);
            goto L_800BD940;
    }
    // 0x800BD918: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x800BD91C: jal         0x800BA8AC
    // 0x800BD920: or          $a1, $a2, $zero
    ctx->r5 = ctx->r6 | 0;
    Audio_GetInstrumentTunedSample(rdram, ctx);
        goto after_0;
    // 0x800BD920: or          $a1, $a2, $zero
    ctx->r5 = ctx->r6 | 0;
    after_0:
    // 0x800BD924: lw          $t5, 0x48($s1)
    ctx->r13 = MEM_W(ctx->r17, 0X48);
    // 0x800BD928: xor         $t9, $v0, $t5
    ctx->r25 = ctx->r2 ^ ctx->r13;
    // 0x800BD92C: sltiu       $t9, $t9, 0x1
    ctx->r25 = ctx->r25 < 0X1 ? 1 : 0;
    // 0x800BD930: sw          $t9, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r25;
    // 0x800BD934: sw          $v0, 0x48($s1)
    MEM_W(0X48, ctx->r17) = ctx->r2;
    // 0x800BD938: b           L_800BD948
    // 0x800BD93C: lwc1        $f0, 0x4($v0)
    ctx->f0.u32l = MEM_W(ctx->r2, 0X4);
        goto L_800BD948;
    // 0x800BD93C: lwc1        $f0, 0x4($v0)
    ctx->f0.u32l = MEM_W(ctx->r2, 0X4);
L_800BD940:
    // 0x800BD940: mtc1        $at, $f0
    ctx->f0.u32l = ctx->r1;
    // 0x800BD944: sw          $zero, 0x48($s1)
    MEM_W(0X48, ctx->r17) = 0;
L_800BD948:
    // 0x800BD948: lui         $v1, 0x800F
    ctx->r3 = S32(0X800F << 16);
    // 0x800BD94C: lbu         $t0, 0x4($s1)
    ctx->r8 = MEM_BU(ctx->r17, 0X4);
    // 0x800BD950: addiu       $v1, $v1, -0x321C
    ctx->r3 = ADD32(ctx->r3, -0X321C);
    // 0x800BD954: sll         $t7, $s2, 2
    ctx->r15 = S32(ctx->r18 << 2);
    // 0x800BD958: addu        $t1, $v1, $t7
    ctx->r9 = ADD32(ctx->r3, ctx->r15);
    // 0x800BD95C: lwc1        $f6, 0x0($t1)
    ctx->f6.u32l = MEM_W(ctx->r9, 0X0);
    // 0x800BD960: lbu         $t8, 0x8($s1)
    ctx->r24 = MEM_BU(ctx->r17, 0X8);
    // 0x800BD964: sll         $t2, $t0, 2
    ctx->r10 = S32(ctx->r8 << 2);
    // 0x800BD968: addu        $t3, $v1, $t2
    ctx->r11 = ADD32(ctx->r3, ctx->r10);
    // 0x800BD96C: lwc1        $f8, 0x0($t3)
    ctx->f8.u32l = MEM_W(ctx->r11, 0X0);
    // 0x800BD970: mul.s       $f2, $f6, $f0
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f2.fl = MUL_S(ctx->f6.fl, ctx->f0.fl);
    // 0x800BD974: addiu       $at, $zero, -0x81
    ctx->r1 = ADD32(0, -0X81);
    // 0x800BD978: and         $t4, $t8, $at
    ctx->r12 = ctx->r24 & ctx->r1;
    // 0x800BD97C: addiu       $t6, $t4, -0x1
    ctx->r14 = ADD32(ctx->r12, -0X1);
    // 0x800BD980: sltiu       $at, $t6, 0x5
    ctx->r1 = ctx->r14 < 0X5 ? 1 : 0;
    // 0x800BD984: mul.s       $f12, $f8, $f0
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f12.fl = MUL_S(ctx->f8.fl, ctx->f0.fl);
    // 0x800BD988: beq         $at, $zero, L_800BD9AC
    if (ctx->r1 == 0) {
        // 0x800BD98C: sll         $t6, $t6, 2
        ctx->r14 = S32(ctx->r14 << 2);
            goto L_800BD9AC;
    }
    // 0x800BD98C: sll         $t6, $t6, 2
    ctx->r14 = S32(ctx->r14 << 2);
    // 0x800BD990: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x800BD994: addu        $at, $at, $t6
    gpr jr_addend_800BD99C = ctx->r14;
    ctx->r1 = ADD32(ctx->r1, ctx->r14);
    // 0x800BD998: lw          $t6, -0x42E0($at)
    ctx->r14 = ADD32(ctx->r1, -0X42E0);
    // 0x800BD99C: jr          $t6
    // 0x800BD9A0: nop

    switch (jr_addend_800BD99C >> 2) {
        case 0: goto L_800BD9A4; break;
        case 1: goto L_800BD9AC; break;
        case 2: goto L_800BD9A4; break;
        case 3: goto L_800BD9AC; break;
        case 4: goto L_800BD9A4; break;
        default: switch_error(__func__, 0x800BD99C, 0x800EBD20);
    }
    // 0x800BD9A0: nop

L_800BD9A4:
    // 0x800BD9A4: b           L_800BD9B0
    // 0x800BD9A8: mov.s       $f0, $f12
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 12);
    ctx->f0.fl = ctx->f12.fl;
        goto L_800BD9B0;
    // 0x800BD9A8: mov.s       $f0, $f12
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 12);
    ctx->f0.fl = ctx->f12.fl;
L_800BD9AC:
    // 0x800BD9AC: mov.s       $f0, $f2
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    ctx->f0.fl = ctx->f2.fl;
L_800BD9B0:
    // 0x800BD9B0: div.s       $f10, $f2, $f0
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f10.fl = DIV_S(ctx->f2.fl, ctx->f0.fl);
    // 0x800BD9B4: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x800BD9B8: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
    // 0x800BD9BC: addiu       $v0, $s1, 0x8
    ctx->r2 = ADD32(ctx->r17, 0X8);
    // 0x800BD9C0: lui         $at, 0x46FE
    ctx->r1 = S32(0X46FE << 16);
    // 0x800BD9C4: sub.s       $f18, $f10, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f18.fl = ctx->f10.fl - ctx->f16.fl;
    // 0x800BD9C8: swc1        $f18, 0xC($v0)
    MEM_W(0XC, ctx->r2) = ctx->f18.u32l;
    // 0x800BD9CC: lbu         $t5, 0x8($s1)
    ctx->r13 = MEM_BU(ctx->r17, 0X8);
    // 0x800BD9D0: andi        $t9, $t5, 0x80
    ctx->r25 = ctx->r13 & 0X80;
    // 0x800BD9D4: beql        $t9, $zero, L_800BDA34
    if (ctx->r25 == 0) {
        // 0x800BD9D8: lhu         $t3, 0x20($s1)
        ctx->r11 = MEM_HU(ctx->r17, 0X20);
            goto L_800BDA34;
    }
    goto skip_0;
    // 0x800BD9D8: lhu         $t3, 0x20($s1)
    ctx->r11 = MEM_HU(ctx->r17, 0X20);
    skip_0:
    // 0x800BD9DC: lhu         $t7, 0x8($s4)
    ctx->r15 = MEM_HU(ctx->r20, 0X8);
    // 0x800BD9E0: lui         $t0, 0x8004
    ctx->r8 = S32(0X8004 << 16);
    // 0x800BD9E4: lh          $t0, 0x554C($t0)
    ctx->r8 = MEM_H(ctx->r8, 0X554C);
    // 0x800BD9E8: mtc1        $t7, $f4
    ctx->f4.u32l = ctx->r15;
    // 0x800BD9EC: lh          $t1, 0x38($s1)
    ctx->r9 = MEM_H(ctx->r17, 0X38);
    // 0x800BD9F0: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x800BD9F4: cvt.s.w     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
    // 0x800BD9F8: mtc1        $t0, $f4
    ctx->f4.u32l = ctx->r8;
    // 0x800BD9FC: mtc1        $t1, $f16
    ctx->f16.u32l = ctx->r9;
    // 0x800BDA00: lhu         $t2, 0x20($s1)
    ctx->r10 = MEM_HU(ctx->r17, 0X20);
    // 0x800BDA04: cvt.s.w     $f18, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    ctx->f18.fl = CVT_S_W(ctx->f16.u32l);
    // 0x800BDA08: mul.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = MUL_S(ctx->f6.fl, ctx->f8.fl);
    // 0x800BDA0C: mtc1        $t2, $f16
    ctx->f16.u32l = ctx->r10;
    // 0x800BDA10: cvt.s.w     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
    // 0x800BDA14: cvt.s.w     $f4, $f16
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 16);
    ctx->f4.fl = CVT_S_W(ctx->f16.u32l);
    // 0x800BDA18: mul.s       $f8, $f18, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = MUL_S(ctx->f18.fl, ctx->f6.fl);
    // 0x800BDA1C: nop

    // 0x800BDA20: mul.s       $f18, $f8, $f4
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f18.fl = MUL_S(ctx->f8.fl, ctx->f4.fl);
    // 0x800BDA24: div.s       $f6, $f10, $f18
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f6.fl = DIV_S(ctx->f10.fl, ctx->f18.fl);
    // 0x800BDA28: b           L_800BDA50
    // 0x800BDA2C: swc1        $f6, 0x8($v0)
    MEM_W(0X8, ctx->r2) = ctx->f6.u32l;
        goto L_800BDA50;
    // 0x800BDA2C: swc1        $f6, 0x8($v0)
    MEM_W(0X8, ctx->r2) = ctx->f6.u32l;
    // 0x800BDA30: lhu         $t3, 0x20($s1)
    ctx->r11 = MEM_HU(ctx->r17, 0X20);
L_800BDA34:
    // 0x800BDA34: lui         $at, 0x42FE
    ctx->r1 = S32(0X42FE << 16);
    // 0x800BDA38: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
    // 0x800BDA3C: mtc1        $t3, $f8
    ctx->f8.u32l = ctx->r11;
    // 0x800BDA40: nop

    // 0x800BDA44: cvt.s.w     $f4, $f8
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    ctx->f4.fl = CVT_S_W(ctx->f8.u32l);
    // 0x800BDA48: div.s       $f10, $f16, $f4
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f10.fl = DIV_S(ctx->f16.fl, ctx->f4.fl);
    // 0x800BDA4C: swc1        $f10, 0x8($v0)
    MEM_W(0X8, ctx->r2) = ctx->f10.u32l;
L_800BDA50:
    // 0x800BDA50: mtc1        $zero, $f18
    ctx->f18.u32l = 0;
    // 0x800BDA54: addiu       $at, $zero, -0x81
    ctx->r1 = ADD32(0, -0X81);
    // 0x800BDA58: swc1        $f18, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->f18.u32l;
    // 0x800BDA5C: lbu         $t8, 0x8($s1)
    ctx->r24 = MEM_BU(ctx->r17, 0X8);
    // 0x800BDA60: swc1        $f0, 0x24($s1)
    MEM_W(0X24, ctx->r17) = ctx->f0.u32l;
    // 0x800BDA64: and         $t4, $t8, $at
    ctx->r12 = ctx->r24 & ctx->r1;
    // 0x800BDA68: addiu       $at, $zero, 0x5
    ctx->r1 = ADD32(0, 0X5);
    // 0x800BDA6C: bnel        $t4, $at, L_800BDAE0
    if (ctx->r12 != ctx->r1) {
        // 0x800BDA70: lh          $t2, 0x38($s1)
        ctx->r10 = MEM_H(ctx->r17, 0X38);
            goto L_800BDAE0;
    }
    goto skip_1;
    // 0x800BDA70: lh          $t2, 0x38($s1)
    ctx->r10 = MEM_H(ctx->r17, 0X38);
    skip_1:
    // 0x800BDA74: b           L_800BDADC
    // 0x800BDA78: sb          $s2, 0x4($s1)
    MEM_B(0X4, ctx->r17) = ctx->r18;
        goto L_800BDADC;
    // 0x800BDA78: sb          $s2, 0x4($s1)
    MEM_B(0X4, ctx->r17) = ctx->r18;
L_800BDA7C:
    // 0x800BDA7C: beq         $a0, $zero, L_800BDAC4
    if (ctx->r4 == 0) {
        // 0x800BDA80: lui         $v1, 0x800F
        ctx->r3 = S32(0X800F << 16);
            goto L_800BDAC4;
    }
    // 0x800BDA80: lui         $v1, 0x800F
    ctx->r3 = S32(0X800F << 16);
    // 0x800BDA84: jal         0x800BA8AC
    // 0x800BDA88: nop

    Audio_GetInstrumentTunedSample(rdram, ctx);
        goto after_1;
    // 0x800BDA88: nop

    after_1:
    // 0x800BDA8C: lw          $t6, 0x48($s1)
    ctx->r14 = MEM_W(ctx->r17, 0X48);
    // 0x800BDA90: lui         $v1, 0x800F
    ctx->r3 = S32(0X800F << 16);
    // 0x800BDA94: addiu       $v1, $v1, -0x321C
    ctx->r3 = ADD32(ctx->r3, -0X321C);
    // 0x800BDA98: xor         $t5, $v0, $t6
    ctx->r13 = ctx->r2 ^ ctx->r14;
    // 0x800BDA9C: sltiu       $t5, $t5, 0x1
    ctx->r13 = ctx->r13 < 0X1 ? 1 : 0;
    // 0x800BDAA0: sw          $t5, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r13;
    // 0x800BDAA4: sw          $v0, 0x48($s1)
    MEM_W(0X48, ctx->r17) = ctx->r2;
    // 0x800BDAA8: sll         $t9, $s2, 2
    ctx->r25 = S32(ctx->r18 << 2);
    // 0x800BDAAC: addu        $t7, $v1, $t9
    ctx->r15 = ADD32(ctx->r3, ctx->r25);
    // 0x800BDAB0: lwc1        $f6, 0x0($t7)
    ctx->f6.u32l = MEM_W(ctx->r15, 0X0);
    // 0x800BDAB4: lwc1        $f8, 0x4($v0)
    ctx->f8.u32l = MEM_W(ctx->r2, 0X4);
    // 0x800BDAB8: mul.s       $f16, $f6, $f8
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f16.fl = MUL_S(ctx->f6.fl, ctx->f8.fl);
    // 0x800BDABC: b           L_800BDADC
    // 0x800BDAC0: swc1        $f16, 0x24($s1)
    MEM_W(0X24, ctx->r17) = ctx->f16.u32l;
        goto L_800BDADC;
    // 0x800BDAC0: swc1        $f16, 0x24($s1)
    MEM_W(0X24, ctx->r17) = ctx->f16.u32l;
L_800BDAC4:
    // 0x800BDAC4: addiu       $v1, $v1, -0x321C
    ctx->r3 = ADD32(ctx->r3, -0X321C);
    // 0x800BDAC8: sll         $t1, $s2, 2
    ctx->r9 = S32(ctx->r18 << 2);
    // 0x800BDACC: sw          $zero, 0x48($s1)
    MEM_W(0X48, ctx->r17) = 0;
    // 0x800BDAD0: addu        $t0, $v1, $t1
    ctx->r8 = ADD32(ctx->r3, ctx->r9);
    // 0x800BDAD4: lwc1        $f4, 0x0($t0)
    ctx->f4.u32l = MEM_W(ctx->r8, 0X0);
    // 0x800BDAD8: swc1        $f4, 0x24($s1)
    MEM_W(0X24, ctx->r17) = ctx->f4.u32l;
L_800BDADC:
    // 0x800BDADC: lh          $t2, 0x38($s1)
    ctx->r10 = MEM_H(ctx->r17, 0X38);
L_800BDAE0:
    // 0x800BDAE0: sh          $t2, 0x3C($s1)
    MEM_H(0X3C, ctx->r17) = ctx->r10;
    // 0x800BDAE4: lw          $v0, 0x0($s1)
    ctx->r2 = MEM_W(ctx->r17, 0X0);
    // 0x800BDAE8: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x800BDAEC: sll         $t3, $v0, 2
    ctx->r11 = S32(ctx->r2 << 2);
    // 0x800BDAF0: srl         $t8, $t3, 31
    ctx->r24 = S32(U32(ctx->r11) >> 31);
    // 0x800BDAF4: bne         $t8, $at, L_800BDB24
    if (ctx->r24 != ctx->r1) {
        // 0x800BDAF8: sll         $t7, $v0, 3
        ctx->r15 = S32(ctx->r2 << 3);
            goto L_800BDB24;
    }
    // 0x800BDAF8: sll         $t7, $v0, 3
    ctx->r15 = S32(ctx->r2 << 3);
    // 0x800BDAFC: lw          $t4, 0x40($s1)
    ctx->r12 = MEM_W(ctx->r17, 0X40);
    // 0x800BDB00: sll         $t5, $v0, 3
    ctx->r13 = S32(ctx->r2 << 3);
    // 0x800BDB04: bne         $t4, $zero, L_800BDB14
    if (ctx->r12 != 0) {
        // 0x800BDB08: nop
    
            goto L_800BDB14;
    }
    // 0x800BDB08: nop

    // 0x800BDB0C: bgezl       $t5, L_800BDBD0
    if (SIGNED(ctx->r13) >= 0) {
        // 0x800BDB10: lw          $ra, 0x2C($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X2C);
            goto L_800BDBD0;
    }
    goto skip_2;
    // 0x800BDB10: lw          $ra, 0x2C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X2C);
    skip_2:
L_800BDB14:
    // 0x800BDB14: jal         0x800BB108
    // 0x800BDB18: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    Audio_SeqLayerNoteDecay(rdram, ctx);
        goto after_2;
    // 0x800BDB18: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    after_2:
    // 0x800BDB1C: b           L_800BDBD0
    // 0x800BDB20: lw          $ra, 0x2C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X2C);
        goto L_800BDBD0;
    // 0x800BDB20: lw          $ra, 0x2C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X2C);
L_800BDB24:
    // 0x800BDB24: bltz        $t7, L_800BDB34
    if (SIGNED(ctx->r15) < 0) {
        // 0x800BDB28: or          $s2, $zero, $zero
        ctx->r18 = 0 | 0;
            goto L_800BDB34;
    }
    // 0x800BDB28: or          $s2, $zero, $zero
    ctx->r18 = 0 | 0;
    // 0x800BDB2C: b           L_800BDB98
    // 0x800BDB30: addiu       $s2, $zero, 0x1
    ctx->r18 = ADD32(0, 0X1);
        goto L_800BDB98;
    // 0x800BDB30: addiu       $s2, $zero, 0x1
    ctx->r18 = ADD32(0, 0X1);
L_800BDB34:
    // 0x800BDB34: lw          $a0, 0x40($s1)
    ctx->r4 = MEM_W(ctx->r17, 0X40);
    // 0x800BDB38: beq         $a0, $zero, L_800BDB50
    if (ctx->r4 == 0) {
        // 0x800BDB3C: nop
    
            goto L_800BDB50;
    }
    // 0x800BDB3C: nop

    // 0x800BDB40: lbu         $t1, 0x2($s1)
    ctx->r9 = MEM_BU(ctx->r17, 0X2);
    // 0x800BDB44: lw          $t0, 0x44($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X44);
    // 0x800BDB48: bne         $t1, $zero, L_800BDB58
    if (ctx->r9 != 0) {
        // 0x800BDB4C: nop
    
            goto L_800BDB58;
    }
    // 0x800BDB4C: nop

L_800BDB50:
    // 0x800BDB50: b           L_800BDB98
    // 0x800BDB54: addiu       $s2, $zero, 0x1
    ctx->r18 = ADD32(0, 0X1);
        goto L_800BDB98;
    // 0x800BDB54: addiu       $s2, $zero, 0x1
    ctx->r18 = ADD32(0, 0X1);
L_800BDB58:
    // 0x800BDB58: bnel        $t0, $zero, L_800BDB74
    if (ctx->r8 != 0) {
        // 0x800BDB5C: lw          $t2, 0x44($a0)
        ctx->r10 = MEM_W(ctx->r4, 0X44);
            goto L_800BDB74;
    }
    goto skip_3;
    // 0x800BDB5C: lw          $t2, 0x44($a0)
    ctx->r10 = MEM_W(ctx->r4, 0X44);
    skip_3:
    // 0x800BDB60: jal         0x800BB108
    // 0x800BDB64: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    Audio_SeqLayerNoteDecay(rdram, ctx);
        goto after_3;
    // 0x800BDB64: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    after_3:
    // 0x800BDB68: b           L_800BDB98
    // 0x800BDB6C: addiu       $s2, $zero, 0x1
    ctx->r18 = ADD32(0, 0X1);
        goto L_800BDB98;
    // 0x800BDB6C: addiu       $s2, $zero, 0x1
    ctx->r18 = ADD32(0, 0X1);
    // 0x800BDB70: lw          $t2, 0x44($a0)
    ctx->r10 = MEM_W(ctx->r4, 0X44);
L_800BDB74:
    // 0x800BDB74: beql        $s1, $t2, L_800BDB88
    if (ctx->r17 == ctx->r10) {
        // 0x800BDB78: lw          $t3, 0x48($s1)
        ctx->r11 = MEM_W(ctx->r17, 0X48);
            goto L_800BDB88;
    }
    goto skip_4;
    // 0x800BDB78: lw          $t3, 0x48($s1)
    ctx->r11 = MEM_W(ctx->r17, 0X48);
    skip_4:
    // 0x800BDB7C: b           L_800BDB98
    // 0x800BDB80: addiu       $s2, $zero, 0x1
    ctx->r18 = ADD32(0, 0X1);
        goto L_800BDB98;
    // 0x800BDB80: addiu       $s2, $zero, 0x1
    ctx->r18 = ADD32(0, 0X1);
    // 0x800BDB84: lw          $t3, 0x48($s1)
    ctx->r11 = MEM_W(ctx->r17, 0X48);
L_800BDB88:
    // 0x800BDB88: bne         $t3, $zero, L_800BDB98
    if (ctx->r11 != 0) {
        // 0x800BDB8C: nop
    
            goto L_800BDB98;
    }
    // 0x800BDB8C: nop

    // 0x800BDB90: jal         0x800BB24C
    // 0x800BDB94: or          $a1, $s1, $zero
    ctx->r5 = ctx->r17 | 0;
    Audio_InitSyntheticWave(rdram, ctx);
        goto after_4;
    // 0x800BDB94: or          $a1, $s1, $zero
    ctx->r5 = ctx->r17 | 0;
    after_4:
L_800BDB98:
    // 0x800BDB98: beql        $s2, $zero, L_800BDBB0
    if (ctx->r18 == 0) {
        // 0x800BDB9C: lw          $a0, 0x40($s1)
        ctx->r4 = MEM_W(ctx->r17, 0X40);
            goto L_800BDBB0;
    }
    goto skip_5;
    // 0x800BDB9C: lw          $a0, 0x40($s1)
    ctx->r4 = MEM_W(ctx->r17, 0X40);
    skip_5:
    // 0x800BDBA0: jal         0x800BBA2C
    // 0x800BDBA4: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    Audio_AllocNote(rdram, ctx);
        goto after_5;
    // 0x800BDBA4: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    after_5:
    // 0x800BDBA8: sw          $v0, 0x40($s1)
    MEM_W(0X40, ctx->r17) = ctx->r2;
    // 0x800BDBAC: lw          $a0, 0x40($s1)
    ctx->r4 = MEM_W(ctx->r17, 0X40);
L_800BDBB0:
    // 0x800BDBB0: beql        $a0, $zero, L_800BDBD0
    if (ctx->r4 == 0) {
        // 0x800BDBB4: lw          $ra, 0x2C($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X2C);
            goto L_800BDBD0;
    }
    goto skip_6;
    // 0x800BDBB4: lw          $ra, 0x2C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X2C);
    skip_6:
    // 0x800BDBB8: lw          $t8, 0x44($a0)
    ctx->r24 = MEM_W(ctx->r4, 0X44);
    // 0x800BDBBC: bnel        $s1, $t8, L_800BDBD0
    if (ctx->r17 != ctx->r24) {
        // 0x800BDBC0: lw          $ra, 0x2C($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X2C);
            goto L_800BDBD0;
    }
    goto skip_7;
    // 0x800BDBC0: lw          $ra, 0x2C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X2C);
    skip_7:
    // 0x800BDBC4: jal         0x800BC4B0
    // 0x800BDBC8: nop

    Audio_NoteVibratoInit(rdram, ctx);
        goto after_6;
    // 0x800BDBC8: nop

    after_6:
    // 0x800BDBCC: lw          $ra, 0x2C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X2C);
L_800BDBD0:
    // 0x800BDBD0: lw          $s0, 0x18($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X18);
    // 0x800BDBD4: lw          $s1, 0x1C($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X1C);
    // 0x800BDBD8: lw          $s2, 0x20($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X20);
    // 0x800BDBDC: lw          $s3, 0x24($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X24);
    // 0x800BDBE0: lw          $s4, 0x28($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X28);
    // 0x800BDBE4: jr          $ra
    // 0x800BDBE8: addiu       $sp, $sp, 0x70
    ctx->r29 = ADD32(ctx->r29, 0X70);
    return;
    // 0x800BDBE8: addiu       $sp, $sp, 0x70
    ctx->r29 = ADD32(ctx->r29, 0X70);
;}
RECOMP_FUNC void AudioSeq_GetInstrument(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800BDBEC: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800BDBF0: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800BDBF4: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    // 0x800BDBF8: sw          $a1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r5;
    // 0x800BDBFC: sw          $a2, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r6;
    // 0x800BDC00: sw          $a3, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r7;
    // 0x800BDC04: lbu         $a0, 0x6($a0)
    ctx->r4 = MEM_BU(ctx->r4, 0X6);
    // 0x800BDC08: jal         0x800BA8E8
    // 0x800BDC0C: lbu         $a1, 0x1F($sp)
    ctx->r5 = MEM_BU(ctx->r29, 0X1F);
    Audio_GetInstrument(rdram, ctx);
        goto after_0;
    // 0x800BDC0C: lbu         $a1, 0x1F($sp)
    ctx->r5 = MEM_BU(ctx->r29, 0X1F);
    after_0:
    // 0x800BDC10: lbu         $a0, 0x1F($sp)
    ctx->r4 = MEM_BU(ctx->r29, 0X1F);
    // 0x800BDC14: lw          $a1, 0x20($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X20);
    // 0x800BDC18: lw          $a2, 0x24($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X24);
    // 0x800BDC1C: bne         $v0, $zero, L_800BDC30
    if (ctx->r2 != 0) {
        // 0x800BDC20: or          $v1, $v0, $zero
        ctx->r3 = ctx->r2 | 0;
            goto L_800BDC30;
    }
    // 0x800BDC20: or          $v1, $v0, $zero
    ctx->r3 = ctx->r2 | 0;
    // 0x800BDC24: sw          $zero, 0x0($a1)
    MEM_W(0X0, ctx->r5) = 0;
    // 0x800BDC28: b           L_800BDC4C
    // 0x800BDC2C: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
        goto L_800BDC4C;
    // 0x800BDC2C: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_800BDC30:
    // 0x800BDC30: lw          $t7, 0x4($v1)
    ctx->r15 = MEM_W(ctx->r3, 0X4);
    // 0x800BDC34: addiu       $a0, $a0, 0x1
    ctx->r4 = ADD32(ctx->r4, 0X1);
    // 0x800BDC38: andi        $v0, $a0, 0xFF
    ctx->r2 = ctx->r4 & 0XFF;
    // 0x800BDC3C: sw          $t7, 0x4($a2)
    MEM_W(0X4, ctx->r6) = ctx->r15;
    // 0x800BDC40: lbu         $t8, 0x3($v1)
    ctx->r24 = MEM_BU(ctx->r3, 0X3);
    // 0x800BDC44: sb          $t8, 0x0($a2)
    MEM_B(0X0, ctx->r6) = ctx->r24;
    // 0x800BDC48: sw          $v1, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r3;
L_800BDC4C:
    // 0x800BDC4C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800BDC50: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800BDC54: jr          $ra
    // 0x800BDC58: nop

    return;
    // 0x800BDC58: nop

;}
RECOMP_FUNC void AudioSeq_SetInstrument(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800BDC5C: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800BDC60: andi        $t6, $a1, 0xFF
    ctx->r14 = ctx->r5 & 0XFF;
    // 0x800BDC64: sw          $a1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r5;
    // 0x800BDC68: slti        $at, $t6, 0x80
    ctx->r1 = SIGNED(ctx->r14) < 0X80 ? 1 : 0;
    // 0x800BDC6C: or          $a1, $t6, $zero
    ctx->r5 = ctx->r14 | 0;
    // 0x800BDC70: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800BDC74: bne         $at, $zero, L_800BDC88
    if (ctx->r1 != 0) {
        // 0x800BDC78: or          $v0, $t6, $zero
        ctx->r2 = ctx->r14 | 0;
            goto L_800BDC88;
    }
    // 0x800BDC78: or          $v0, $t6, $zero
    ctx->r2 = ctx->r14 | 0;
    // 0x800BDC7C: sh          $t6, 0x1C($a0)
    MEM_H(0X1C, ctx->r4) = ctx->r14;
    // 0x800BDC80: b           L_800BDCD4
    // 0x800BDC84: sw          $zero, 0x40($a0)
    MEM_W(0X40, ctx->r4) = 0;
        goto L_800BDCD4;
    // 0x800BDC84: sw          $zero, 0x40($a0)
    MEM_W(0X40, ctx->r4) = 0;
L_800BDC88:
    // 0x800BDC88: addiu       $at, $zero, 0x7F
    ctx->r1 = ADD32(0, 0X7F);
    // 0x800BDC8C: bne         $v0, $at, L_800BDCA4
    if (ctx->r2 != ctx->r1) {
        // 0x800BDC90: addiu       $a2, $a0, 0x40
        ctx->r6 = ADD32(ctx->r4, 0X40);
            goto L_800BDCA4;
    }
    // 0x800BDC90: addiu       $a2, $a0, 0x40
    ctx->r6 = ADD32(ctx->r4, 0X40);
    // 0x800BDC94: addiu       $t7, $zero, 0x1
    ctx->r15 = ADD32(0, 0X1);
    // 0x800BDC98: sh          $zero, 0x1C($a0)
    MEM_H(0X1C, ctx->r4) = 0;
    // 0x800BDC9C: b           L_800BDCD4
    // 0x800BDCA0: sw          $t7, 0x40($a0)
    MEM_W(0X40, ctx->r4) = ctx->r15;
        goto L_800BDCD4;
    // 0x800BDCA0: sw          $t7, 0x40($a0)
    MEM_W(0X40, ctx->r4) = ctx->r15;
L_800BDCA4:
    // 0x800BDCA4: addiu       $a3, $a0, 0x7C
    ctx->r7 = ADD32(ctx->r4, 0X7C);
    // 0x800BDCA8: jal         0x800BDBEC
    // 0x800BDCAC: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    AudioSeq_GetInstrument(rdram, ctx);
        goto after_0;
    // 0x800BDCAC: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    after_0:
    // 0x800BDCB0: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
    // 0x800BDCB4: sll         $t8, $v0, 16
    ctx->r24 = S32(ctx->r2 << 16);
    // 0x800BDCB8: sra         $t9, $t8, 16
    ctx->r25 = S32(SIGNED(ctx->r24) >> 16);
    // 0x800BDCBC: bne         $t9, $zero, L_800BDCD4
    if (ctx->r25 != 0) {
        // 0x800BDCC0: sh          $v0, 0x1C($a0)
        MEM_H(0X1C, ctx->r4) = ctx->r2;
            goto L_800BDCD4;
    }
    // 0x800BDCC0: sh          $v0, 0x1C($a0)
    MEM_H(0X1C, ctx->r4) = ctx->r2;
    // 0x800BDCC4: lbu         $t0, 0x0($a0)
    ctx->r8 = MEM_BU(ctx->r4, 0X0);
    // 0x800BDCC8: andi        $t1, $t0, 0xFFF7
    ctx->r9 = ctx->r8 & 0XFFF7;
    // 0x800BDCCC: b           L_800BDCE0
    // 0x800BDCD0: sb          $t1, 0x0($a0)
    MEM_B(0X0, ctx->r4) = ctx->r9;
        goto L_800BDCE0;
    // 0x800BDCD0: sb          $t1, 0x0($a0)
    MEM_B(0X0, ctx->r4) = ctx->r9;
L_800BDCD4:
    // 0x800BDCD4: lbu         $t3, 0x0($a0)
    ctx->r11 = MEM_BU(ctx->r4, 0X0);
    // 0x800BDCD8: ori         $t4, $t3, 0x8
    ctx->r12 = ctx->r11 | 0X8;
    // 0x800BDCDC: sb          $t4, 0x0($a0)
    MEM_B(0X0, ctx->r4) = ctx->r12;
L_800BDCE0:
    // 0x800BDCE0: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800BDCE4: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800BDCE8: jr          $ra
    // 0x800BDCEC: nop

    return;
    // 0x800BDCEC: nop

;}
RECOMP_FUNC void AudioSeq_SequenceChannelSetVolume(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800BDCF0: andi        $t6, $a1, 0xFF
    ctx->r14 = ctx->r5 & 0XFF;
    // 0x800BDCF4: mtc1        $t6, $f4
    ctx->f4.u32l = ctx->r14;
    // 0x800BDCF8: lui         $at, 0x42FE
    ctx->r1 = S32(0X42FE << 16);
    // 0x800BDCFC: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x800BDD00: cvt.s.w     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
    // 0x800BDD04: sw          $a1, 0x4($sp)
    MEM_W(0X4, ctx->r29) = ctx->r5;
    // 0x800BDD08: div.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = DIV_S(ctx->f6.fl, ctx->f8.fl);
    // 0x800BDD0C: jr          $ra
    // 0x800BDD10: swc1        $f10, 0x24($a0)
    MEM_W(0X24, ctx->r4) = ctx->f10.u32l;
    return;
    // 0x800BDD10: swc1        $f10, 0x24($a0)
    MEM_W(0X24, ctx->r4) = ctx->f10.u32l;
;}
RECOMP_FUNC void AudioSeq_SequenceChannelProcessScript(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800BDD14: addiu       $sp, $sp, -0x60
    ctx->r29 = ADD32(ctx->r29, -0X60);
    // 0x800BDD18: sw          $ra, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r31;
    // 0x800BDD1C: sw          $s4, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r20;
    // 0x800BDD20: sw          $s3, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r19;
    // 0x800BDD24: sw          $s2, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r18;
    // 0x800BDD28: sw          $s1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r17;
    // 0x800BDD2C: sw          $s0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r16;
    // 0x800BDD30: lw          $v0, 0x0($a0)
    ctx->r2 = MEM_W(ctx->r4, 0X0);
    // 0x800BDD34: or          $s2, $a0, $zero
    ctx->r18 = ctx->r4 | 0;
    // 0x800BDD38: srl         $t6, $v0, 31
    ctx->r14 = S32(U32(ctx->r2) >> 31);
    // 0x800BDD3C: beq         $t6, $zero, L_800BE838
    if (ctx->r14 == 0) {
        // 0x800BDD40: sll         $t8, $v0, 2
        ctx->r24 = S32(ctx->r2 << 2);
            goto L_800BE838;
    }
    // 0x800BDD40: sll         $t8, $v0, 2
    ctx->r24 = S32(ctx->r2 << 2);
    // 0x800BDD44: bgez        $t8, L_800BDD7C
    if (SIGNED(ctx->r24) >= 0) {
        // 0x800BDD48: or          $s0, $zero, $zero
        ctx->r16 = 0 | 0;
            goto L_800BDD7C;
    }
    // 0x800BDD48: or          $s0, $zero, $zero
    ctx->r16 = 0 | 0;
    // 0x800BDD4C: or          $s1, $a0, $zero
    ctx->r17 = ctx->r4 | 0;
    // 0x800BDD50: addiu       $s2, $zero, 0x10
    ctx->r18 = ADD32(0, 0X10);
L_800BDD54:
    // 0x800BDD54: lw          $a0, 0x48($s1)
    ctx->r4 = MEM_W(ctx->r17, 0X48);
    // 0x800BDD58: beql        $a0, $zero, L_800BDD6C
    if (ctx->r4 == 0) {
        // 0x800BDD5C: addiu       $s0, $s0, 0x4
        ctx->r16 = ADD32(ctx->r16, 0X4);
            goto L_800BDD6C;
    }
    goto skip_0;
    // 0x800BDD5C: addiu       $s0, $s0, 0x4
    ctx->r16 = ADD32(ctx->r16, 0X4);
    skip_0:
    // 0x800BDD60: jal         0x800BD138
    // 0x800BDD64: nop

    AudioSeq_SeqLayerProcessScript(rdram, ctx);
        goto after_0;
    // 0x800BDD64: nop

    after_0:
    // 0x800BDD68: addiu       $s0, $s0, 0x4
    ctx->r16 = ADD32(ctx->r16, 0X4);
L_800BDD6C:
    // 0x800BDD6C: bne         $s0, $s2, L_800BDD54
    if (ctx->r16 != ctx->r18) {
        // 0x800BDD70: addiu       $s1, $s1, 0x4
        ctx->r17 = ADD32(ctx->r17, 0X4);
            goto L_800BDD54;
    }
    // 0x800BDD70: addiu       $s1, $s1, 0x4
    ctx->r17 = ADD32(ctx->r17, 0X4);
    // 0x800BDD74: b           L_800BE83C
    // 0x800BDD78: lw          $ra, 0x2C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X2C);
        goto L_800BE83C;
    // 0x800BDD78: lw          $ra, 0x2C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X2C);
L_800BDD7C:
    // 0x800BDD7C: lw          $s4, 0x44($s2)
    ctx->r20 = MEM_W(ctx->r18, 0X44);
    // 0x800BDD80: lw          $t9, 0x0($s4)
    ctx->r25 = MEM_W(ctx->r20, 0X0);
    // 0x800BDD84: sll         $t2, $t9, 2
    ctx->r10 = S32(ctx->r25 << 2);
    // 0x800BDD88: bgezl       $t2, L_800BDDA4
    if (SIGNED(ctx->r10) >= 0) {
        // 0x800BDD8C: lhu         $v1, 0x1A($s2)
        ctx->r3 = MEM_HU(ctx->r18, 0X1A);
            goto L_800BDDA4;
    }
    goto skip_1;
    // 0x800BDD8C: lhu         $v1, 0x1A($s2)
    ctx->r3 = MEM_HU(ctx->r18, 0X1A);
    skip_1:
    // 0x800BDD90: lbu         $t3, 0x3($s2)
    ctx->r11 = MEM_BU(ctx->r18, 0X3);
    // 0x800BDD94: andi        $t4, $t3, 0x80
    ctx->r12 = ctx->r11 & 0X80;
    // 0x800BDD98: bnel        $t4, $zero, L_800BE83C
    if (ctx->r12 != 0) {
        // 0x800BDD9C: lw          $ra, 0x2C($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X2C);
            goto L_800BE83C;
    }
    goto skip_2;
    // 0x800BDD9C: lw          $ra, 0x2C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X2C);
    skip_2:
    // 0x800BDDA0: lhu         $v1, 0x1A($s2)
    ctx->r3 = MEM_HU(ctx->r18, 0X1A);
L_800BDDA4:
    // 0x800BDDA4: addiu       $s1, $s2, 0x60
    ctx->r17 = ADD32(ctx->r18, 0X60);
    // 0x800BDDA8: beq         $v1, $zero, L_800BDDBC
    if (ctx->r3 == 0) {
        // 0x800BDDAC: or          $v0, $v1, $zero
        ctx->r2 = ctx->r3 | 0;
            goto L_800BDDBC;
    }
    // 0x800BDDAC: or          $v0, $v1, $zero
    ctx->r2 = ctx->r3 | 0;
    // 0x800BDDB0: addiu       $t5, $v1, -0x1
    ctx->r13 = ADD32(ctx->r3, -0X1);
    // 0x800BDDB4: sh          $t5, 0x1A($s2)
    MEM_H(0X1A, ctx->r18) = ctx->r13;
    // 0x800BDDB8: andi        $v0, $t5, 0xFFFF
    ctx->r2 = ctx->r13 & 0XFFFF;
L_800BDDBC:
    // 0x800BDDBC: bne         $v0, $zero, L_800BE80C
    if (ctx->r2 != 0) {
        // 0x800BDDC0: lb          $s3, 0x4B($sp)
        ctx->r19 = MEM_B(ctx->r29, 0X4B);
            goto L_800BE80C;
    }
    // 0x800BDDC0: lb          $s3, 0x4B($sp)
    ctx->r19 = MEM_B(ctx->r29, 0X4B);
L_800BDDC4:
    // 0x800BDDC4: jal         0x800BD0B0
    // 0x800BDDC8: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    AudioSeq_ScriptReadU8(rdram, ctx);
        goto after_1;
    // 0x800BDDC8: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    after_1:
    // 0x800BDDCC: slti        $at, $v0, 0xC1
    ctx->r1 = SIGNED(ctx->r2) < 0XC1 ? 1 : 0;
    // 0x800BDDD0: andi        $s0, $v0, 0xFF
    ctx->r16 = ctx->r2 & 0XFF;
    // 0x800BDDD4: bne         $at, $zero, L_800BE5E4
    if (ctx->r1 != 0) {
        // 0x800BDDD8: or          $v1, $v0, $zero
        ctx->r3 = ctx->r2 | 0;
            goto L_800BE5E4;
    }
    // 0x800BDDD8: or          $v1, $v0, $zero
    ctx->r3 = ctx->r2 | 0;
    // 0x800BDDDC: addiu       $t6, $v0, -0xC1
    ctx->r14 = ADD32(ctx->r2, -0XC1);
    // 0x800BDDE0: sltiu       $at, $t6, 0x3F
    ctx->r1 = ctx->r14 < 0X3F ? 1 : 0;
    // 0x800BDDE4: beq         $at, $zero, L_800BDDC4
    if (ctx->r1 == 0) {
        // 0x800BDDE8: sll         $t6, $t6, 2
        ctx->r14 = S32(ctx->r14 << 2);
            goto L_800BDDC4;
    }
    // 0x800BDDE8: sll         $t6, $t6, 2
    ctx->r14 = S32(ctx->r14 << 2);
    // 0x800BDDEC: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x800BDDF0: addu        $at, $at, $t6
    gpr jr_addend_800BDDF8 = ctx->r14;
    ctx->r1 = ADD32(ctx->r1, ctx->r14);
    // 0x800BDDF4: lw          $t6, -0x42CC($at)
    ctx->r14 = ADD32(ctx->r1, -0X42CC);
    // 0x800BDDF8: jr          $t6
    // 0x800BDDFC: nop

    switch (jr_addend_800BDDF8 >> 2) {
        case 0: goto L_800BE0AC; break;
        case 1: goto L_800BDFFC; break;
        case 2: goto L_800BE0C8; break;
        case 3: goto L_800BE0D8; break;
        case 4: goto L_800BE018; break;
        case 5: goto L_800BE2E4; break;
        case 6: goto L_800BE340; break;
        case 7: goto L_800BE378; break;
        case 8: goto L_800BE378; break;
        case 9: goto L_800BE3C4; break;
        case 10: goto L_800BE3D4; break;
        case 11: goto L_800BE378; break;
        case 12: goto L_800BDDC4; break;
        case 13: goto L_800BDDC4; break;
        case 14: goto L_800BDDC4; break;
        case 15: goto L_800BE3F4; break;
        case 16: goto L_800BE418; break;
        case 17: goto L_800BE428; break;
        case 18: goto L_800BE170; break;
        case 19: goto L_800BE2D4; break;
        case 20: goto L_800BDDC4; break;
        case 21: goto L_800BDDC4; break;
        case 22: goto L_800BE23C; break;
        case 23: goto L_800BE220; break;
        case 24: goto L_800BE210; break;
        case 25: goto L_800BE1F4; break;
        case 26: goto L_800BE1DC; break;
        case 27: goto L_800BE1C0; break;
        case 28: goto L_800BE1A4; break;
        case 29: goto L_800BE13C; break;
        case 30: goto L_800BE0E8; break;
        case 31: goto L_800BE10C; break;
        case 32: goto L_800BE28C; break;
        case 33: goto L_800BE258; break;
        case 34: goto L_800BE2C0; break;
        case 35: goto L_800BE448; break;
        case 36: goto L_800BE438; break;
        case 37: goto L_800BE4A4; break;
        case 38: goto L_800BE4B4; break;
        case 39: goto L_800BE51C; break;
        case 40: goto L_800BE5BC; break;
        case 41: goto L_800BDE48; break;
        case 42: goto L_800BE054; break;
        case 43: goto L_800BE594; break;
        case 44: goto L_800BDDC4; break;
        case 45: goto L_800BDDC4; break;
        case 46: goto L_800BE5CC; break;
        case 47: goto L_800BDFEC; break;
        case 48: goto L_800BDFC4; break;
        case 49: goto L_800BDF7C; break;
        case 50: goto L_800BDF7C; break;
        case 51: goto L_800BDF7C; break;
        case 52: goto L_800BDF24; break;
        case 53: goto L_800BDF14; break;
        case 54: goto L_800BDECC; break;
        case 55: goto L_800BDE94; break;
        case 56: goto L_800BDF24; break;
        case 57: goto L_800BDF24; break;
        case 58: goto L_800BDF24; break;
        case 59: goto L_800BDE58; break;
        case 60: goto L_800BDE38; break;
        case 61: goto L_800BE80C; break;
        case 62: goto L_800BDE00; break;
        default: switch_error(__func__, 0x800BDDF8, 0x800EBD34);
    }
    // 0x800BDDFC: nop

L_800BDE00:
    // 0x800BDE00: lbu         $a0, 0x18($s1)
    ctx->r4 = MEM_BU(ctx->r17, 0X18);
    // 0x800BDE04: bne         $a0, $zero, L_800BDE1C
    if (ctx->r4 != 0) {
        // 0x800BDE08: addiu       $v0, $a0, -0x1
        ctx->r2 = ADD32(ctx->r4, -0X1);
            goto L_800BDE1C;
    }
    // 0x800BDE08: addiu       $v0, $a0, -0x1
    ctx->r2 = ADD32(ctx->r4, -0X1);
    // 0x800BDE0C: jal         0x800BCB34
    // 0x800BDE10: or          $a0, $s2, $zero
    ctx->r4 = ctx->r18 | 0;
    AudioSeq_SequenceChannelDisable(rdram, ctx);
        goto after_2;
    // 0x800BDE10: or          $a0, $s2, $zero
    ctx->r4 = ctx->r18 | 0;
    after_2:
    // 0x800BDE14: b           L_800BE810
    // 0x800BDE18: or          $s1, $s2, $zero
    ctx->r17 = ctx->r18 | 0;
        goto L_800BE810;
    // 0x800BDE18: or          $s1, $s2, $zero
    ctx->r17 = ctx->r18 | 0;
L_800BDE1C:
    // 0x800BDE1C: andi        $t7, $v0, 0xFF
    ctx->r15 = ctx->r2 & 0XFF;
    // 0x800BDE20: sll         $t8, $t7, 2
    ctx->r24 = S32(ctx->r15 << 2);
    // 0x800BDE24: addu        $t9, $s1, $t8
    ctx->r25 = ADD32(ctx->r17, ctx->r24);
    // 0x800BDE28: sb          $t7, 0x18($s1)
    MEM_B(0X18, ctx->r17) = ctx->r15;
    // 0x800BDE2C: lw          $t1, 0x4($t9)
    ctx->r9 = MEM_W(ctx->r25, 0X4);
    // 0x800BDE30: b           L_800BDDC4
    // 0x800BDE34: sw          $t1, 0x0($s1)
    MEM_W(0X0, ctx->r17) = ctx->r9;
        goto L_800BDDC4;
    // 0x800BDE34: sw          $t1, 0x0($s1)
    MEM_W(0X0, ctx->r17) = ctx->r9;
L_800BDE38:
    // 0x800BDE38: jal         0x800BD0F4
    // 0x800BDE3C: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    AudioSeq_ScriptReadCompressedU16(rdram, ctx);
        goto after_3;
    // 0x800BDE3C: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    after_3:
    // 0x800BDE40: b           L_800BE80C
    // 0x800BDE44: sh          $v0, 0x1A($s2)
    MEM_H(0X1A, ctx->r18) = ctx->r2;
        goto L_800BE80C;
    // 0x800BDE44: sh          $v0, 0x1A($s2)
    MEM_H(0X1A, ctx->r18) = ctx->r2;
L_800BDE48:
    // 0x800BDE48: lbu         $t3, 0x0($s2)
    ctx->r11 = MEM_BU(ctx->r18, 0X0);
    // 0x800BDE4C: ori         $t4, $t3, 0x20
    ctx->r12 = ctx->r11 | 0X20;
    // 0x800BDE50: b           L_800BE80C
    // 0x800BDE54: sb          $t4, 0x0($s2)
    MEM_B(0X0, ctx->r18) = ctx->r12;
        goto L_800BE80C;
    // 0x800BDE54: sb          $t4, 0x0($s2)
    MEM_B(0X0, ctx->r18) = ctx->r12;
L_800BDE58:
    // 0x800BDE58: jal         0x800BD0C4
    // 0x800BDE5C: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    AudioSeq_ScriptReadS16(rdram, ctx);
        goto after_4;
    // 0x800BDE5C: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    after_4:
    // 0x800BDE60: lbu         $t6, 0x18($s1)
    ctx->r14 = MEM_BU(ctx->r17, 0X18);
    // 0x800BDE64: lw          $t5, 0x0($s1)
    ctx->r13 = MEM_W(ctx->r17, 0X0);
    // 0x800BDE68: andi        $t3, $v0, 0xFFFF
    ctx->r11 = ctx->r2 & 0XFFFF;
    // 0x800BDE6C: sll         $t7, $t6, 2
    ctx->r15 = S32(ctx->r14 << 2);
    // 0x800BDE70: addu        $t8, $s1, $t7
    ctx->r24 = ADD32(ctx->r17, ctx->r15);
    // 0x800BDE74: sw          $t5, 0x4($t8)
    MEM_W(0X4, ctx->r24) = ctx->r13;
    // 0x800BDE78: lbu         $t9, 0x18($s1)
    ctx->r25 = MEM_BU(ctx->r17, 0X18);
    // 0x800BDE7C: addiu       $t1, $t9, 0x1
    ctx->r9 = ADD32(ctx->r25, 0X1);
    // 0x800BDE80: sb          $t1, 0x18($s1)
    MEM_B(0X18, ctx->r17) = ctx->r9;
    // 0x800BDE84: lw          $t2, 0x14($s4)
    ctx->r10 = MEM_W(ctx->r20, 0X14);
    // 0x800BDE88: addu        $t4, $t2, $t3
    ctx->r12 = ADD32(ctx->r10, ctx->r11);
    // 0x800BDE8C: b           L_800BDDC4
    // 0x800BDE90: sw          $t4, 0x0($s1)
    MEM_W(0X0, ctx->r17) = ctx->r12;
        goto L_800BDDC4;
    // 0x800BDE90: sw          $t4, 0x0($s1)
    MEM_W(0X0, ctx->r17) = ctx->r12;
L_800BDE94:
    // 0x800BDE94: jal         0x800BD0B0
    // 0x800BDE98: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    AudioSeq_ScriptReadU8(rdram, ctx);
        goto after_5;
    // 0x800BDE98: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    after_5:
    // 0x800BDE9C: lbu         $t6, 0x18($s1)
    ctx->r14 = MEM_BU(ctx->r17, 0X18);
    // 0x800BDEA0: addu        $t7, $s1, $t6
    ctx->r15 = ADD32(ctx->r17, ctx->r14);
    // 0x800BDEA4: sb          $v0, 0x14($t7)
    MEM_B(0X14, ctx->r15) = ctx->r2;
    // 0x800BDEA8: lbu         $t8, 0x18($s1)
    ctx->r24 = MEM_BU(ctx->r17, 0X18);
    // 0x800BDEAC: lw          $t5, 0x0($s1)
    ctx->r13 = MEM_W(ctx->r17, 0X0);
    // 0x800BDEB0: sll         $t9, $t8, 2
    ctx->r25 = S32(ctx->r24 << 2);
    // 0x800BDEB4: addu        $t1, $s1, $t9
    ctx->r9 = ADD32(ctx->r17, ctx->r25);
    // 0x800BDEB8: sw          $t5, 0x4($t1)
    MEM_W(0X4, ctx->r9) = ctx->r13;
    // 0x800BDEBC: lbu         $t2, 0x18($s1)
    ctx->r10 = MEM_BU(ctx->r17, 0X18);
    // 0x800BDEC0: addiu       $t3, $t2, 0x1
    ctx->r11 = ADD32(ctx->r10, 0X1);
    // 0x800BDEC4: b           L_800BDDC4
    // 0x800BDEC8: sb          $t3, 0x18($s1)
    MEM_B(0X18, ctx->r17) = ctx->r11;
        goto L_800BDDC4;
    // 0x800BDEC8: sb          $t3, 0x18($s1)
    MEM_B(0X18, ctx->r17) = ctx->r11;
L_800BDECC:
    // 0x800BDECC: lbu         $t4, 0x18($s1)
    ctx->r12 = MEM_BU(ctx->r17, 0X18);
    // 0x800BDED0: addu        $v0, $s1, $t4
    ctx->r2 = ADD32(ctx->r17, ctx->r12);
    // 0x800BDED4: lbu         $t6, 0x13($v0)
    ctx->r14 = MEM_BU(ctx->r2, 0X13);
    // 0x800BDED8: addiu       $t7, $t6, -0x1
    ctx->r15 = ADD32(ctx->r14, -0X1);
    // 0x800BDEDC: sb          $t7, 0x13($v0)
    MEM_B(0X13, ctx->r2) = ctx->r15;
    // 0x800BDEE0: lbu         $a0, 0x18($s1)
    ctx->r4 = MEM_BU(ctx->r17, 0X18);
    // 0x800BDEE4: addu        $t8, $s1, $a0
    ctx->r24 = ADD32(ctx->r17, ctx->r4);
    // 0x800BDEE8: lbu         $t9, 0x13($t8)
    ctx->r25 = MEM_BU(ctx->r24, 0X13);
    // 0x800BDEEC: or          $v1, $a0, $zero
    ctx->r3 = ctx->r4 | 0;
    // 0x800BDEF0: sll         $t5, $v1, 2
    ctx->r13 = S32(ctx->r3 << 2);
    // 0x800BDEF4: beq         $t9, $zero, L_800BDF0C
    if (ctx->r25 == 0) {
        // 0x800BDEF8: addiu       $t3, $a0, -0x1
        ctx->r11 = ADD32(ctx->r4, -0X1);
            goto L_800BDF0C;
    }
    // 0x800BDEF8: addiu       $t3, $a0, -0x1
    ctx->r11 = ADD32(ctx->r4, -0X1);
    // 0x800BDEFC: addu        $t1, $s1, $t5
    ctx->r9 = ADD32(ctx->r17, ctx->r13);
    // 0x800BDF00: lw          $t2, 0x0($t1)
    ctx->r10 = MEM_W(ctx->r9, 0X0);
    // 0x800BDF04: b           L_800BDDC4
    // 0x800BDF08: sw          $t2, 0x0($s1)
    MEM_W(0X0, ctx->r17) = ctx->r10;
        goto L_800BDDC4;
    // 0x800BDF08: sw          $t2, 0x0($s1)
    MEM_W(0X0, ctx->r17) = ctx->r10;
L_800BDF0C:
    // 0x800BDF0C: b           L_800BDDC4
    // 0x800BDF10: sb          $t3, 0x18($s1)
    MEM_B(0X18, ctx->r17) = ctx->r11;
        goto L_800BDDC4;
    // 0x800BDF10: sb          $t3, 0x18($s1)
    MEM_B(0X18, ctx->r17) = ctx->r11;
L_800BDF14:
    // 0x800BDF14: lbu         $t4, 0x18($s1)
    ctx->r12 = MEM_BU(ctx->r17, 0X18);
    // 0x800BDF18: addiu       $t6, $t4, -0x1
    ctx->r14 = ADD32(ctx->r12, -0X1);
    // 0x800BDF1C: b           L_800BDDC4
    // 0x800BDF20: sb          $t6, 0x18($s1)
    MEM_B(0X18, ctx->r17) = ctx->r14;
        goto L_800BDDC4;
    // 0x800BDF20: sb          $t6, 0x18($s1)
    MEM_B(0X18, ctx->r17) = ctx->r14;
L_800BDF24:
    // 0x800BDF24: jal         0x800BD0C4
    // 0x800BDF28: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    AudioSeq_ScriptReadS16(rdram, ctx);
        goto after_6;
    // 0x800BDF28: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    after_6:
    // 0x800BDF2C: addiu       $at, $zero, 0xFA
    ctx->r1 = ADD32(0, 0XFA);
    // 0x800BDF30: bne         $s0, $at, L_800BDF40
    if (ctx->r16 != ctx->r1) {
        // 0x800BDF34: or          $v1, $s0, $zero
        ctx->r3 = ctx->r16 | 0;
            goto L_800BDF40;
    }
    // 0x800BDF34: or          $v1, $s0, $zero
    ctx->r3 = ctx->r16 | 0;
    // 0x800BDF38: bne         $s3, $zero, L_800BDDC4
    if (ctx->r19 != 0) {
        // 0x800BDF3C: nop
    
            goto L_800BDDC4;
    }
    // 0x800BDF3C: nop

L_800BDF40:
    // 0x800BDF40: addiu       $at, $zero, 0xF9
    ctx->r1 = ADD32(0, 0XF9);
    // 0x800BDF44: bnel        $v1, $at, L_800BDF58
    if (ctx->r3 != ctx->r1) {
        // 0x800BDF48: addiu       $at, $zero, 0xF5
        ctx->r1 = ADD32(0, 0XF5);
            goto L_800BDF58;
    }
    goto skip_3;
    // 0x800BDF48: addiu       $at, $zero, 0xF5
    ctx->r1 = ADD32(0, 0XF5);
    skip_3:
    // 0x800BDF4C: bgez        $s3, L_800BDDC4
    if (SIGNED(ctx->r19) >= 0) {
        // 0x800BDF50: nop
    
            goto L_800BDDC4;
    }
    // 0x800BDF50: nop

    // 0x800BDF54: addiu       $at, $zero, 0xF5
    ctx->r1 = ADD32(0, 0XF5);
L_800BDF58:
    // 0x800BDF58: bnel        $v1, $at, L_800BDF6C
    if (ctx->r3 != ctx->r1) {
        // 0x800BDF5C: lw          $t7, 0x14($s4)
        ctx->r15 = MEM_W(ctx->r20, 0X14);
            goto L_800BDF6C;
    }
    goto skip_4;
    // 0x800BDF5C: lw          $t7, 0x14($s4)
    ctx->r15 = MEM_W(ctx->r20, 0X14);
    skip_4:
    // 0x800BDF60: bltz        $s3, L_800BDDC4
    if (SIGNED(ctx->r19) < 0) {
        // 0x800BDF64: nop
    
            goto L_800BDDC4;
    }
    // 0x800BDF64: nop

    // 0x800BDF68: lw          $t7, 0x14($s4)
    ctx->r15 = MEM_W(ctx->r20, 0X14);
L_800BDF6C:
    // 0x800BDF6C: andi        $t8, $v0, 0xFFFF
    ctx->r24 = ctx->r2 & 0XFFFF;
    // 0x800BDF70: addu        $t9, $t7, $t8
    ctx->r25 = ADD32(ctx->r15, ctx->r24);
    // 0x800BDF74: b           L_800BDDC4
    // 0x800BDF78: sw          $t9, 0x0($s1)
    MEM_W(0X0, ctx->r17) = ctx->r25;
        goto L_800BDDC4;
    // 0x800BDF78: sw          $t9, 0x0($s1)
    MEM_W(0X0, ctx->r17) = ctx->r25;
L_800BDF7C:
    // 0x800BDF7C: jal         0x800BD0B0
    // 0x800BDF80: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    AudioSeq_ScriptReadU8(rdram, ctx);
        goto after_7;
    // 0x800BDF80: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    after_7:
    // 0x800BDF84: addiu       $at, $zero, 0xF3
    ctx->r1 = ADD32(0, 0XF3);
    // 0x800BDF88: bne         $s0, $at, L_800BDF98
    if (ctx->r16 != ctx->r1) {
        // 0x800BDF8C: or          $v1, $s0, $zero
        ctx->r3 = ctx->r16 | 0;
            goto L_800BDF98;
    }
    // 0x800BDF8C: or          $v1, $s0, $zero
    ctx->r3 = ctx->r16 | 0;
    // 0x800BDF90: bne         $s3, $zero, L_800BDDC4
    if (ctx->r19 != 0) {
        // 0x800BDF94: nop
    
            goto L_800BDDC4;
    }
    // 0x800BDF94: nop

L_800BDF98:
    // 0x800BDF98: addiu       $at, $zero, 0xF2
    ctx->r1 = ADD32(0, 0XF2);
    // 0x800BDF9C: bnel        $v1, $at, L_800BDFB0
    if (ctx->r3 != ctx->r1) {
        // 0x800BDFA0: lw          $t5, 0x0($s1)
        ctx->r13 = MEM_W(ctx->r17, 0X0);
            goto L_800BDFB0;
    }
    goto skip_5;
    // 0x800BDFA0: lw          $t5, 0x0($s1)
    ctx->r13 = MEM_W(ctx->r17, 0X0);
    skip_5:
    // 0x800BDFA4: bgez        $s3, L_800BDDC4
    if (SIGNED(ctx->r19) >= 0) {
        // 0x800BDFA8: nop
    
            goto L_800BDDC4;
    }
    // 0x800BDFA8: nop

    // 0x800BDFAC: lw          $t5, 0x0($s1)
    ctx->r13 = MEM_W(ctx->r17, 0X0);
L_800BDFB0:
    // 0x800BDFB0: sll         $t1, $v0, 24
    ctx->r9 = S32(ctx->r2 << 24);
    // 0x800BDFB4: sra         $t2, $t1, 24
    ctx->r10 = S32(SIGNED(ctx->r9) >> 24);
    // 0x800BDFB8: addu        $t3, $t5, $t2
    ctx->r11 = ADD32(ctx->r13, ctx->r10);
    // 0x800BDFBC: b           L_800BDDC4
    // 0x800BDFC0: sw          $t3, 0x0($s1)
    MEM_W(0X0, ctx->r17) = ctx->r11;
        goto L_800BDDC4;
    // 0x800BDFC0: sw          $t3, 0x0($s1)
    MEM_W(0X0, ctx->r17) = ctx->r11;
L_800BDFC4:
    // 0x800BDFC4: addiu       $s0, $s2, 0x84
    ctx->r16 = ADD32(ctx->r18, 0X84);
    // 0x800BDFC8: jal         0x800BB400
    // 0x800BDFCC: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    Audio_NotePoolClear(rdram, ctx);
        goto after_8;
    // 0x800BDFCC: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_8:
    // 0x800BDFD0: jal         0x800BD0B0
    // 0x800BDFD4: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    AudioSeq_ScriptReadU8(rdram, ctx);
        goto after_9;
    // 0x800BDFD4: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    after_9:
    // 0x800BDFD8: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x800BDFDC: jal         0x800BB560
    // 0x800BDFE0: or          $a1, $v0, $zero
    ctx->r5 = ctx->r2 | 0;
    Audio_NotePoolFill(rdram, ctx);
        goto after_10;
    // 0x800BDFE0: or          $a1, $v0, $zero
    ctx->r5 = ctx->r2 | 0;
    after_10:
    // 0x800BDFE4: b           L_800BDDC4
    // 0x800BDFE8: nop

        goto L_800BDDC4;
    // 0x800BDFE8: nop

L_800BDFEC:
    // 0x800BDFEC: jal         0x800BB400
    // 0x800BDFF0: addiu       $a0, $s2, 0x84
    ctx->r4 = ADD32(ctx->r18, 0X84);
    Audio_NotePoolClear(rdram, ctx);
        goto after_11;
    // 0x800BDFF0: addiu       $a0, $s2, 0x84
    ctx->r4 = ADD32(ctx->r18, 0X84);
    after_11:
    // 0x800BDFF4: b           L_800BDDC4
    // 0x800BDFF8: nop

        goto L_800BDDC4;
    // 0x800BDFF8: nop

L_800BDFFC:
    // 0x800BDFFC: jal         0x800BD0C4
    // 0x800BE000: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    AudioSeq_ScriptReadS16(rdram, ctx);
        goto after_12;
    // 0x800BE000: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    after_12:
    // 0x800BE004: lw          $t4, 0x14($s4)
    ctx->r12 = MEM_W(ctx->r20, 0X14);
    // 0x800BE008: andi        $t6, $v0, 0xFFFF
    ctx->r14 = ctx->r2 & 0XFFFF;
    // 0x800BE00C: addu        $t7, $t4, $t6
    ctx->r15 = ADD32(ctx->r12, ctx->r14);
    // 0x800BE010: b           L_800BDDC4
    // 0x800BE014: sw          $t7, 0x34($s2)
    MEM_W(0X34, ctx->r18) = ctx->r15;
        goto L_800BDDC4;
    // 0x800BE014: sw          $t7, 0x34($s2)
    MEM_W(0X34, ctx->r18) = ctx->r15;
L_800BE018:
    // 0x800BE018: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x800BE01C: beq         $s3, $at, L_800BDDC4
    if (ctx->r19 == ctx->r1) {
        // 0x800BE020: nop
    
            goto L_800BDDC4;
    }
    // 0x800BE020: nop

    // 0x800BE024: lw          $t8, 0x34($s2)
    ctx->r24 = MEM_W(ctx->r18, 0X34);
    // 0x800BE028: sll         $t9, $s3, 1
    ctx->r25 = S32(ctx->r19 << 1);
    // 0x800BE02C: lw          $t4, 0x14($s4)
    ctx->r12 = MEM_W(ctx->r20, 0X14);
    // 0x800BE030: addu        $v1, $t8, $t9
    ctx->r3 = ADD32(ctx->r24, ctx->r25);
    // 0x800BE034: lbu         $t5, 0x0($v1)
    ctx->r13 = MEM_BU(ctx->r3, 0X0);
    // 0x800BE038: lbu         $t1, 0x1($v1)
    ctx->r9 = MEM_BU(ctx->r3, 0X1);
    // 0x800BE03C: sll         $t2, $t5, 8
    ctx->r10 = S32(ctx->r13 << 8);
    // 0x800BE040: addu        $a3, $t1, $t2
    ctx->r7 = ADD32(ctx->r9, ctx->r10);
    // 0x800BE044: andi        $t3, $a3, 0xFFFF
    ctx->r11 = ctx->r7 & 0XFFFF;
    // 0x800BE048: addu        $t6, $t4, $t3
    ctx->r14 = ADD32(ctx->r12, ctx->r11);
    // 0x800BE04C: b           L_800BDDC4
    // 0x800BE050: sw          $t6, 0x34($s2)
    MEM_W(0X34, ctx->r18) = ctx->r14;
        goto L_800BDDC4;
    // 0x800BE050: sw          $t6, 0x34($s2)
    MEM_W(0X34, ctx->r18) = ctx->r14;
L_800BE054:
    // 0x800BE054: jal         0x800BD0B0
    // 0x800BE058: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    AudioSeq_ScriptReadU8(rdram, ctx);
        goto after_13;
    // 0x800BE058: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    after_13:
    // 0x800BE05C: lbu         $t7, 0x4($s4)
    ctx->r15 = MEM_BU(ctx->r20, 0X4);
    // 0x800BE060: lui         $v1, 0x8004
    ctx->r3 = S32(0X8004 << 16);
    // 0x800BE064: lw          $v1, 0x5510($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X5510);
    // 0x800BE068: sll         $t8, $t7, 1
    ctx->r24 = S32(ctx->r15 << 1);
    // 0x800BE06C: lui         $a0, 0x8004
    ctx->r4 = S32(0X8004 << 16);
    // 0x800BE070: addu        $t9, $v1, $t8
    ctx->r25 = ADD32(ctx->r3, ctx->r24);
    // 0x800BE074: lhu         $a3, 0x0($t9)
    ctx->r7 = MEM_HU(ctx->r25, 0X0);
    // 0x800BE078: addiu       $a0, $a0, -0x1860
    ctx->r4 = ADD32(ctx->r4, -0X1860);
    // 0x800BE07C: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x800BE080: addu        $t5, $a3, $v1
    ctx->r13 = ADD32(ctx->r7, ctx->r3);
    // 0x800BE084: lbu         $t0, 0x0($t5)
    ctx->r8 = MEM_BU(ctx->r13, 0X0);
    // 0x800BE088: addu        $t1, $a3, $t0
    ctx->r9 = ADD32(ctx->r7, ctx->r8);
    // 0x800BE08C: subu        $t2, $t1, $v0
    ctx->r10 = SUB32(ctx->r9, ctx->r2);
    // 0x800BE090: addu        $t3, $t2, $v1
    ctx->r11 = ADD32(ctx->r10, ctx->r3);
    // 0x800BE094: lbu         $s0, 0x0($t3)
    ctx->r16 = MEM_BU(ctx->r11, 0X0);
    // 0x800BE098: jal         0x800B811C
    // 0x800BE09C: or          $a2, $s0, $zero
    ctx->r6 = ctx->r16 | 0;
    AudioHeap_SearchRegularCaches(rdram, ctx);
        goto after_14;
    // 0x800BE09C: or          $a2, $s0, $zero
    ctx->r6 = ctx->r16 | 0;
    after_14:
    // 0x800BE0A0: beq         $v0, $zero, L_800BE0AC
    if (ctx->r2 == 0) {
        // 0x800BE0A4: nop
    
            goto L_800BE0AC;
    }
    // 0x800BE0A4: nop

    // 0x800BE0A8: sb          $s0, 0x6($s2)
    MEM_B(0X6, ctx->r18) = ctx->r16;
L_800BE0AC:
    // 0x800BE0AC: jal         0x800BD0B0
    // 0x800BE0B0: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    AudioSeq_ScriptReadU8(rdram, ctx);
        goto after_15;
    // 0x800BE0B0: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    after_15:
    // 0x800BE0B4: or          $a0, $s2, $zero
    ctx->r4 = ctx->r18 | 0;
    // 0x800BE0B8: jal         0x800BDC5C
    // 0x800BE0BC: andi        $a1, $v0, 0xFF
    ctx->r5 = ctx->r2 & 0XFF;
    AudioSeq_SetInstrument(rdram, ctx);
        goto after_16;
    // 0x800BE0BC: andi        $a1, $v0, 0xFF
    ctx->r5 = ctx->r2 & 0XFF;
    after_16:
    // 0x800BE0C0: b           L_800BDDC4
    // 0x800BE0C4: nop

        goto L_800BDDC4;
    // 0x800BE0C4: nop

L_800BE0C8:
    // 0x800BE0C8: lbu         $t4, 0x0($s2)
    ctx->r12 = MEM_BU(ctx->r18, 0X0);
    // 0x800BE0CC: andi        $t6, $t4, 0xFFFD
    ctx->r14 = ctx->r12 & 0XFFFD;
    // 0x800BE0D0: b           L_800BDDC4
    // 0x800BE0D4: sb          $t6, 0x0($s2)
    MEM_B(0X0, ctx->r18) = ctx->r14;
        goto L_800BDDC4;
    // 0x800BE0D4: sb          $t6, 0x0($s2)
    MEM_B(0X0, ctx->r18) = ctx->r14;
L_800BE0D8:
    // 0x800BE0D8: lbu         $t8, 0x0($s2)
    ctx->r24 = MEM_BU(ctx->r18, 0X0);
    // 0x800BE0DC: ori         $t9, $t8, 0x2
    ctx->r25 = ctx->r24 | 0X2;
    // 0x800BE0E0: b           L_800BDDC4
    // 0x800BE0E4: sb          $t9, 0x0($s2)
    MEM_B(0X0, ctx->r18) = ctx->r25;
        goto L_800BDDC4;
    // 0x800BE0E4: sb          $t9, 0x0($s2)
    MEM_B(0X0, ctx->r18) = ctx->r25;
L_800BE0E8:
    // 0x800BE0E8: jal         0x800BD0B0
    // 0x800BE0EC: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    AudioSeq_ScriptReadU8(rdram, ctx);
        goto after_17;
    // 0x800BE0EC: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    after_17:
    // 0x800BE0F0: or          $a0, $s2, $zero
    ctx->r4 = ctx->r18 | 0;
    // 0x800BE0F4: jal         0x800BDCF0
    // 0x800BE0F8: andi        $a1, $v0, 0xFF
    ctx->r5 = ctx->r2 & 0XFF;
    AudioSeq_SequenceChannelSetVolume(rdram, ctx);
        goto after_18;
    // 0x800BE0F8: andi        $a1, $v0, 0xFF
    ctx->r5 = ctx->r2 & 0XFF;
    after_18:
    // 0x800BE0FC: lbu         $t1, 0x1($s2)
    ctx->r9 = MEM_BU(ctx->r18, 0X1);
    // 0x800BE100: ori         $t2, $t1, 0x40
    ctx->r10 = ctx->r9 | 0X40;
    // 0x800BE104: b           L_800BDDC4
    // 0x800BE108: sb          $t2, 0x1($s2)
    MEM_B(0X1, ctx->r18) = ctx->r10;
        goto L_800BDDC4;
    // 0x800BE108: sb          $t2, 0x1($s2)
    MEM_B(0X1, ctx->r18) = ctx->r10;
L_800BE10C:
    // 0x800BE10C: jal         0x800BD0B0
    // 0x800BE110: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    AudioSeq_ScriptReadU8(rdram, ctx);
        goto after_19;
    // 0x800BE110: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    after_19:
    // 0x800BE114: mtc1        $v0, $f4
    ctx->f4.u32l = ctx->r2;
    // 0x800BE118: lui         $at, 0x3C00
    ctx->r1 = S32(0X3C00 << 16);
    // 0x800BE11C: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x800BE120: cvt.s.w     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
    // 0x800BE124: lbu         $t4, 0x1($s2)
    ctx->r12 = MEM_BU(ctx->r18, 0X1);
    // 0x800BE128: ori         $t6, $t4, 0x40
    ctx->r14 = ctx->r12 | 0X40;
    // 0x800BE12C: sb          $t6, 0x1($s2)
    MEM_B(0X1, ctx->r18) = ctx->r14;
    // 0x800BE130: mul.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = MUL_S(ctx->f6.fl, ctx->f8.fl);
    // 0x800BE134: b           L_800BDDC4
    // 0x800BE138: swc1        $f10, 0x20($s2)
    MEM_W(0X20, ctx->r18) = ctx->f10.u32l;
        goto L_800BDDC4;
    // 0x800BE138: swc1        $f10, 0x20($s2)
    MEM_W(0X20, ctx->r18) = ctx->f10.u32l;
L_800BE13C:
    // 0x800BE13C: jal         0x800BD0C4
    // 0x800BE140: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    AudioSeq_ScriptReadS16(rdram, ctx);
        goto after_20;
    // 0x800BE140: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    after_20:
    // 0x800BE144: andi        $t7, $v0, 0xFFFF
    ctx->r15 = ctx->r2 & 0XFFFF;
    // 0x800BE148: mtc1        $t7, $f16
    ctx->f16.u32l = ctx->r15;
    // 0x800BE14C: lui         $at, 0x4700
    ctx->r1 = S32(0X4700 << 16);
    // 0x800BE150: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x800BE154: cvt.s.w     $f18, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    ctx->f18.fl = CVT_S_W(ctx->f16.u32l);
    // 0x800BE158: lbu         $t9, 0x1($s2)
    ctx->r25 = MEM_BU(ctx->r18, 0X1);
    // 0x800BE15C: ori         $t5, $t9, 0x80
    ctx->r13 = ctx->r25 | 0X80;
    // 0x800BE160: sb          $t5, 0x1($s2)
    MEM_B(0X1, ctx->r18) = ctx->r13;
    // 0x800BE164: div.s       $f6, $f18, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = DIV_S(ctx->f18.fl, ctx->f4.fl);
    // 0x800BE168: b           L_800BDDC4
    // 0x800BE16C: swc1        $f6, 0x30($s2)
    MEM_W(0X30, ctx->r18) = ctx->f6.u32l;
        goto L_800BDDC4;
    // 0x800BE16C: swc1        $f6, 0x30($s2)
    MEM_W(0X30, ctx->r18) = ctx->f6.u32l;
L_800BE170:
    // 0x800BE170: jal         0x800BD0B0
    // 0x800BE174: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    AudioSeq_ScriptReadU8(rdram, ctx);
        goto after_21;
    // 0x800BE174: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    after_21:
    // 0x800BE178: addiu       $t1, $v0, 0x7F
    ctx->r9 = ADD32(ctx->r2, 0X7F);
    // 0x800BE17C: andi        $t2, $t1, 0xFF
    ctx->r10 = ctx->r9 & 0XFF;
    // 0x800BE180: lbu         $t6, 0x1($s2)
    ctx->r14 = MEM_BU(ctx->r18, 0X1);
    // 0x800BE184: sll         $t3, $t2, 2
    ctx->r11 = S32(ctx->r10 << 2);
    // 0x800BE188: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x800BE18C: addu        $at, $at, $t3
    ctx->r1 = ADD32(ctx->r1, ctx->r11);
    // 0x800BE190: lwc1        $f8, -0x361C($at)
    ctx->f8.u32l = MEM_W(ctx->r1, -0X361C);
    // 0x800BE194: ori         $t7, $t6, 0x80
    ctx->r15 = ctx->r14 | 0X80;
    // 0x800BE198: sb          $t7, 0x1($s2)
    MEM_B(0X1, ctx->r18) = ctx->r15;
    // 0x800BE19C: b           L_800BDDC4
    // 0x800BE1A0: swc1        $f8, 0x30($s2)
    MEM_W(0X30, ctx->r18) = ctx->f8.u32l;
        goto L_800BDDC4;
    // 0x800BE1A0: swc1        $f8, 0x30($s2)
    MEM_W(0X30, ctx->r18) = ctx->f8.u32l;
L_800BE1A4:
    // 0x800BE1A4: jal         0x800BD0B0
    // 0x800BE1A8: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    AudioSeq_ScriptReadU8(rdram, ctx);
        goto after_22;
    // 0x800BE1A8: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    after_22:
    // 0x800BE1AC: lbu         $t9, 0x1($s2)
    ctx->r25 = MEM_BU(ctx->r18, 0X1);
    // 0x800BE1B0: sb          $v0, 0x9($s2)
    MEM_B(0X9, ctx->r18) = ctx->r2;
    // 0x800BE1B4: ori         $t5, $t9, 0x20
    ctx->r13 = ctx->r25 | 0X20;
    // 0x800BE1B8: b           L_800BDDC4
    // 0x800BE1BC: sb          $t5, 0x1($s2)
    MEM_B(0X1, ctx->r18) = ctx->r13;
        goto L_800BDDC4;
    // 0x800BE1BC: sb          $t5, 0x1($s2)
    MEM_B(0X1, ctx->r18) = ctx->r13;
L_800BE1C0:
    // 0x800BE1C0: jal         0x800BD0B0
    // 0x800BE1C4: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    AudioSeq_ScriptReadU8(rdram, ctx);
        goto after_23;
    // 0x800BE1C4: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    after_23:
    // 0x800BE1C8: lbu         $t2, 0x1($s2)
    ctx->r10 = MEM_BU(ctx->r18, 0X1);
    // 0x800BE1CC: sb          $v0, 0xA($s2)
    MEM_B(0XA, ctx->r18) = ctx->r2;
    // 0x800BE1D0: ori         $t3, $t2, 0x20
    ctx->r11 = ctx->r10 | 0X20;
    // 0x800BE1D4: b           L_800BDDC4
    // 0x800BE1D8: sb          $t3, 0x1($s2)
    MEM_B(0X1, ctx->r18) = ctx->r11;
        goto L_800BDDC4;
    // 0x800BE1D8: sb          $t3, 0x1($s2)
    MEM_B(0X1, ctx->r18) = ctx->r11;
L_800BE1DC:
    // 0x800BE1DC: lw          $v0, 0x0($s1)
    ctx->r2 = MEM_W(ctx->r17, 0X0);
    // 0x800BE1E0: lb          $v1, 0x0($v0)
    ctx->r3 = MEM_B(ctx->r2, 0X0);
    // 0x800BE1E4: addiu       $t4, $v0, 0x1
    ctx->r12 = ADD32(ctx->r2, 0X1);
    // 0x800BE1E8: sw          $t4, 0x0($s1)
    MEM_W(0X0, ctx->r17) = ctx->r12;
    // 0x800BE1EC: b           L_800BDDC4
    // 0x800BE1F0: sh          $v1, 0x1E($s2)
    MEM_H(0X1E, ctx->r18) = ctx->r3;
        goto L_800BDDC4;
    // 0x800BE1F0: sh          $v1, 0x1E($s2)
    MEM_H(0X1E, ctx->r18) = ctx->r3;
L_800BE1F4:
    // 0x800BE1F4: jal         0x800BD0C4
    // 0x800BE1F8: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    AudioSeq_ScriptReadS16(rdram, ctx);
        goto after_24;
    // 0x800BE1F8: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    after_24:
    // 0x800BE1FC: lw          $t6, 0x14($s4)
    ctx->r14 = MEM_W(ctx->r20, 0X14);
    // 0x800BE200: andi        $t7, $v0, 0xFFFF
    ctx->r15 = ctx->r2 & 0XFFFF;
    // 0x800BE204: addu        $t8, $t6, $t7
    ctx->r24 = ADD32(ctx->r14, ctx->r15);
    // 0x800BE208: b           L_800BDDC4
    // 0x800BE20C: sw          $t8, 0x80($s2)
    MEM_W(0X80, ctx->r18) = ctx->r24;
        goto L_800BDDC4;
    // 0x800BE20C: sw          $t8, 0x80($s2)
    MEM_W(0X80, ctx->r18) = ctx->r24;
L_800BE210:
    // 0x800BE210: jal         0x800BD0B0
    // 0x800BE214: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    AudioSeq_ScriptReadU8(rdram, ctx);
        goto after_25;
    // 0x800BE214: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    after_25:
    // 0x800BE218: b           L_800BDDC4
    // 0x800BE21C: sb          $v0, 0x7C($s2)
    MEM_B(0X7C, ctx->r18) = ctx->r2;
        goto L_800BDDC4;
    // 0x800BE21C: sb          $v0, 0x7C($s2)
    MEM_B(0X7C, ctx->r18) = ctx->r2;
L_800BE220:
    // 0x800BE220: jal         0x800BD0B0
    // 0x800BE224: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    AudioSeq_ScriptReadU8(rdram, ctx);
        goto after_26;
    // 0x800BE224: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    after_26:
    // 0x800BE228: sll         $t9, $v0, 3
    ctx->r25 = S32(ctx->r2 << 3);
    // 0x800BE22C: sh          $t9, 0x12($s2)
    MEM_H(0X12, ctx->r18) = ctx->r25;
    // 0x800BE230: sh          $zero, 0xE($s2)
    MEM_H(0XE, ctx->r18) = 0;
    // 0x800BE234: b           L_800BDDC4
    // 0x800BE238: sh          $zero, 0x16($s2)
    MEM_H(0X16, ctx->r18) = 0;
        goto L_800BDDC4;
    // 0x800BE238: sh          $zero, 0x16($s2)
    MEM_H(0X16, ctx->r18) = 0;
L_800BE23C:
    // 0x800BE23C: jal         0x800BD0B0
    // 0x800BE240: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    AudioSeq_ScriptReadU8(rdram, ctx);
        goto after_27;
    // 0x800BE240: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    after_27:
    // 0x800BE244: sll         $v1, $v0, 5
    ctx->r3 = S32(ctx->r2 << 5);
    // 0x800BE248: sh          $v1, 0x10($s2)
    MEM_H(0X10, ctx->r18) = ctx->r3;
    // 0x800BE24C: sh          $v1, 0xC($s2)
    MEM_H(0XC, ctx->r18) = ctx->r3;
    // 0x800BE250: b           L_800BDDC4
    // 0x800BE254: sh          $zero, 0x14($s2)
    MEM_H(0X14, ctx->r18) = 0;
        goto L_800BDDC4;
    // 0x800BE254: sh          $zero, 0x14($s2)
    MEM_H(0X14, ctx->r18) = 0;
L_800BE258:
    // 0x800BE258: jal         0x800BD0B0
    // 0x800BE25C: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    AudioSeq_ScriptReadU8(rdram, ctx);
        goto after_28;
    // 0x800BE25C: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    after_28:
    // 0x800BE260: sll         $t5, $v0, 3
    ctx->r13 = S32(ctx->r2 << 3);
    // 0x800BE264: sh          $t5, 0xE($s2)
    MEM_H(0XE, ctx->r18) = ctx->r13;
    // 0x800BE268: jal         0x800BD0B0
    // 0x800BE26C: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    AudioSeq_ScriptReadU8(rdram, ctx);
        goto after_29;
    // 0x800BE26C: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    after_29:
    // 0x800BE270: sll         $t1, $v0, 3
    ctx->r9 = S32(ctx->r2 << 3);
    // 0x800BE274: sh          $t1, 0x12($s2)
    MEM_H(0X12, ctx->r18) = ctx->r9;
    // 0x800BE278: jal         0x800BD0B0
    // 0x800BE27C: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    AudioSeq_ScriptReadU8(rdram, ctx);
        goto after_30;
    // 0x800BE27C: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    after_30:
    // 0x800BE280: sll         $t2, $v0, 4
    ctx->r10 = S32(ctx->r2 << 4);
    // 0x800BE284: b           L_800BDDC4
    // 0x800BE288: sh          $t2, 0x16($s2)
    MEM_H(0X16, ctx->r18) = ctx->r10;
        goto L_800BDDC4;
    // 0x800BE288: sh          $t2, 0x16($s2)
    MEM_H(0X16, ctx->r18) = ctx->r10;
L_800BE28C:
    // 0x800BE28C: jal         0x800BD0B0
    // 0x800BE290: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    AudioSeq_ScriptReadU8(rdram, ctx);
        goto after_31;
    // 0x800BE290: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    after_31:
    // 0x800BE294: sll         $t3, $v0, 5
    ctx->r11 = S32(ctx->r2 << 5);
    // 0x800BE298: sh          $t3, 0xC($s2)
    MEM_H(0XC, ctx->r18) = ctx->r11;
    // 0x800BE29C: jal         0x800BD0B0
    // 0x800BE2A0: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    AudioSeq_ScriptReadU8(rdram, ctx);
        goto after_32;
    // 0x800BE2A0: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    after_32:
    // 0x800BE2A4: sll         $t4, $v0, 5
    ctx->r12 = S32(ctx->r2 << 5);
    // 0x800BE2A8: sh          $t4, 0x10($s2)
    MEM_H(0X10, ctx->r18) = ctx->r12;
    // 0x800BE2AC: jal         0x800BD0B0
    // 0x800BE2B0: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    AudioSeq_ScriptReadU8(rdram, ctx);
        goto after_33;
    // 0x800BE2B0: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    after_33:
    // 0x800BE2B4: sll         $t6, $v0, 4
    ctx->r14 = S32(ctx->r2 << 4);
    // 0x800BE2B8: b           L_800BDDC4
    // 0x800BE2BC: sh          $t6, 0x14($s2)
    MEM_H(0X14, ctx->r18) = ctx->r14;
        goto L_800BDDC4;
    // 0x800BE2BC: sh          $t6, 0x14($s2)
    MEM_H(0X14, ctx->r18) = ctx->r14;
L_800BE2C0:
    // 0x800BE2C0: jal         0x800BD0B0
    // 0x800BE2C4: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    AudioSeq_ScriptReadU8(rdram, ctx);
        goto after_34;
    // 0x800BE2C4: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    after_34:
    // 0x800BE2C8: sll         $t7, $v0, 4
    ctx->r15 = S32(ctx->r2 << 4);
    // 0x800BE2CC: b           L_800BDDC4
    // 0x800BE2D0: sh          $t7, 0x18($s2)
    MEM_H(0X18, ctx->r18) = ctx->r15;
        goto L_800BDDC4;
    // 0x800BE2D0: sh          $t7, 0x18($s2)
    MEM_H(0X18, ctx->r18) = ctx->r15;
L_800BE2D4:
    // 0x800BE2D4: jal         0x800BD0B0
    // 0x800BE2D8: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    AudioSeq_ScriptReadU8(rdram, ctx);
        goto after_35;
    // 0x800BE2D8: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    after_35:
    // 0x800BE2DC: b           L_800BDDC4
    // 0x800BE2E0: sb          $v0, 0x4($s2)
    MEM_B(0X4, ctx->r18) = ctx->r2;
        goto L_800BDDC4;
    // 0x800BE2E0: sb          $v0, 0x4($s2)
    MEM_B(0X4, ctx->r18) = ctx->r2;
L_800BE2E4:
    // 0x800BE2E4: jal         0x800BD0B0
    // 0x800BE2E8: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    AudioSeq_ScriptReadU8(rdram, ctx);
        goto after_36;
    // 0x800BE2E8: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    after_36:
    // 0x800BE2EC: lbu         $t8, 0x4($s4)
    ctx->r24 = MEM_BU(ctx->r20, 0X4);
    // 0x800BE2F0: lui         $v1, 0x8004
    ctx->r3 = S32(0X8004 << 16);
    // 0x800BE2F4: lw          $v1, 0x5510($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X5510);
    // 0x800BE2F8: sll         $t9, $t8, 1
    ctx->r25 = S32(ctx->r24 << 1);
    // 0x800BE2FC: lui         $a0, 0x8004
    ctx->r4 = S32(0X8004 << 16);
    // 0x800BE300: addu        $t5, $v1, $t9
    ctx->r13 = ADD32(ctx->r3, ctx->r25);
    // 0x800BE304: lhu         $a3, 0x0($t5)
    ctx->r7 = MEM_HU(ctx->r13, 0X0);
    // 0x800BE308: addiu       $a0, $a0, -0x1860
    ctx->r4 = ADD32(ctx->r4, -0X1860);
    // 0x800BE30C: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x800BE310: addu        $t1, $a3, $v1
    ctx->r9 = ADD32(ctx->r7, ctx->r3);
    // 0x800BE314: lbu         $t0, 0x0($t1)
    ctx->r8 = MEM_BU(ctx->r9, 0X0);
    // 0x800BE318: addu        $t2, $a3, $t0
    ctx->r10 = ADD32(ctx->r7, ctx->r8);
    // 0x800BE31C: subu        $t3, $t2, $v0
    ctx->r11 = SUB32(ctx->r10, ctx->r2);
    // 0x800BE320: addu        $t4, $t3, $v1
    ctx->r12 = ADD32(ctx->r11, ctx->r3);
    // 0x800BE324: lbu         $s0, 0x0($t4)
    ctx->r16 = MEM_BU(ctx->r12, 0X0);
    // 0x800BE328: jal         0x800B811C
    // 0x800BE32C: or          $a2, $s0, $zero
    ctx->r6 = ctx->r16 | 0;
    AudioHeap_SearchRegularCaches(rdram, ctx);
        goto after_37;
    // 0x800BE32C: or          $a2, $s0, $zero
    ctx->r6 = ctx->r16 | 0;
    after_37:
    // 0x800BE330: beq         $v0, $zero, L_800BDDC4
    if (ctx->r2 == 0) {
        // 0x800BE334: nop
    
            goto L_800BDDC4;
    }
    // 0x800BE334: nop

    // 0x800BE338: b           L_800BDDC4
    // 0x800BE33C: sb          $s0, 0x6($s2)
    MEM_B(0X6, ctx->r18) = ctx->r16;
        goto L_800BDDC4;
    // 0x800BE33C: sb          $s0, 0x6($s2)
    MEM_B(0X6, ctx->r18) = ctx->r16;
L_800BE340:
    // 0x800BE340: andi        $t6, $s3, 0xFF
    ctx->r14 = ctx->r19 & 0XFF;
    // 0x800BE344: sw          $t6, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r14;
    // 0x800BE348: jal         0x800BD0B0
    // 0x800BE34C: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    AudioSeq_ScriptReadU8(rdram, ctx);
        goto after_38;
    // 0x800BE34C: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    after_38:
    // 0x800BE350: andi        $s0, $v0, 0xFF
    ctx->r16 = ctx->r2 & 0XFF;
    // 0x800BE354: jal         0x800BD0C4
    // 0x800BE358: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    AudioSeq_ScriptReadS16(rdram, ctx);
        goto after_39;
    // 0x800BE358: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    after_39:
    // 0x800BE35C: lw          $t7, 0x14($s4)
    ctx->r15 = MEM_W(ctx->r20, 0X14);
    // 0x800BE360: lw          $t9, 0x34($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X34);
    // 0x800BE364: andi        $t8, $v0, 0xFFFF
    ctx->r24 = ctx->r2 & 0XFFFF;
    // 0x800BE368: addu        $v1, $t7, $t8
    ctx->r3 = ADD32(ctx->r15, ctx->r24);
    // 0x800BE36C: addu        $t5, $t9, $s0
    ctx->r13 = ADD32(ctx->r25, ctx->r16);
    // 0x800BE370: b           L_800BDDC4
    // 0x800BE374: sb          $t5, 0x0($v1)
    MEM_B(0X0, ctx->r3) = ctx->r13;
        goto L_800BDDC4;
    // 0x800BE374: sb          $t5, 0x0($v1)
    MEM_B(0X0, ctx->r3) = ctx->r13;
L_800BE378:
    // 0x800BE378: jal         0x800BD0B0
    // 0x800BE37C: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    AudioSeq_ScriptReadU8(rdram, ctx);
        goto after_40;
    // 0x800BE37C: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    after_40:
    // 0x800BE380: addiu       $at, $zero, 0xC8
    ctx->r1 = ADD32(0, 0XC8);
    // 0x800BE384: bne         $s0, $at, L_800BE39C
    if (ctx->r16 != ctx->r1) {
        // 0x800BE388: or          $v1, $s0, $zero
        ctx->r3 = ctx->r16 | 0;
            goto L_800BE39C;
    }
    // 0x800BE388: or          $v1, $s0, $zero
    ctx->r3 = ctx->r16 | 0;
    // 0x800BE38C: subu        $s3, $s3, $v0
    ctx->r19 = SUB32(ctx->r19, ctx->r2);
    // 0x800BE390: sll         $t3, $s3, 24
    ctx->r11 = S32(ctx->r19 << 24);
    // 0x800BE394: b           L_800BDDC4
    // 0x800BE398: sra         $s3, $t3, 24
    ctx->r19 = S32(SIGNED(ctx->r11) >> 24);
        goto L_800BDDC4;
    // 0x800BE398: sra         $s3, $t3, 24
    ctx->r19 = S32(SIGNED(ctx->r11) >> 24);
L_800BE39C:
    // 0x800BE39C: addiu       $at, $zero, 0xCC
    ctx->r1 = ADD32(0, 0XCC);
    // 0x800BE3A0: bne         $v1, $at, L_800BE3B8
    if (ctx->r3 != ctx->r1) {
        // 0x800BE3A4: and         $s3, $s3, $v0
        ctx->r19 = ctx->r19 & ctx->r2;
            goto L_800BE3B8;
    }
    // 0x800BE3A4: and         $s3, $s3, $v0
    ctx->r19 = ctx->r19 & ctx->r2;
    // 0x800BE3A8: sll         $s3, $v0, 24
    ctx->r19 = S32(ctx->r2 << 24);
    // 0x800BE3AC: sra         $t6, $s3, 24
    ctx->r14 = S32(SIGNED(ctx->r19) >> 24);
    // 0x800BE3B0: b           L_800BDDC4
    // 0x800BE3B4: or          $s3, $t6, $zero
    ctx->r19 = ctx->r14 | 0;
        goto L_800BDDC4;
    // 0x800BE3B4: or          $s3, $t6, $zero
    ctx->r19 = ctx->r14 | 0;
L_800BE3B8:
    // 0x800BE3B8: sll         $t9, $s3, 24
    ctx->r25 = S32(ctx->r19 << 24);
    // 0x800BE3BC: b           L_800BDDC4
    // 0x800BE3C0: sra         $s3, $t9, 24
    ctx->r19 = S32(SIGNED(ctx->r25) >> 24);
        goto L_800BDDC4;
    // 0x800BE3C0: sra         $s3, $t9, 24
    ctx->r19 = S32(SIGNED(ctx->r25) >> 24);
L_800BE3C4:
    // 0x800BE3C4: jal         0x800BD0B0
    // 0x800BE3C8: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    AudioSeq_ScriptReadU8(rdram, ctx);
        goto after_41;
    // 0x800BE3C8: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    after_41:
    // 0x800BE3CC: b           L_800BDDC4
    // 0x800BE3D0: sb          $v0, 0x3($s2)
    MEM_B(0X3, ctx->r18) = ctx->r2;
        goto L_800BDDC4;
    // 0x800BE3D0: sb          $v0, 0x3($s2)
    MEM_B(0X3, ctx->r18) = ctx->r2;
L_800BE3D4:
    // 0x800BE3D4: jal         0x800BD0C4
    // 0x800BE3D8: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    AudioSeq_ScriptReadS16(rdram, ctx);
        goto after_42;
    // 0x800BE3D8: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    after_42:
    // 0x800BE3DC: lw          $t1, 0x14($s4)
    ctx->r9 = MEM_W(ctx->r20, 0X14);
    // 0x800BE3E0: andi        $t2, $v0, 0xFFFF
    ctx->r10 = ctx->r2 & 0XFFFF;
    // 0x800BE3E4: addu        $t3, $t2, $s3
    ctx->r11 = ADD32(ctx->r10, ctx->r19);
    // 0x800BE3E8: addu        $t4, $t1, $t3
    ctx->r12 = ADD32(ctx->r9, ctx->r11);
    // 0x800BE3EC: b           L_800BDDC4
    // 0x800BE3F0: lb          $s3, 0x0($t4)
    ctx->r19 = MEM_B(ctx->r12, 0X0);
        goto L_800BDDC4;
    // 0x800BE3F0: lb          $s3, 0x0($t4)
    ctx->r19 = MEM_B(ctx->r12, 0X0);
L_800BE3F4:
    // 0x800BE3F4: jal         0x800BD0B0
    // 0x800BE3F8: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    AudioSeq_ScriptReadU8(rdram, ctx);
        goto after_43;
    // 0x800BE3F8: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    after_43:
    // 0x800BE3FC: lbu         $t9, 0x0($s2)
    ctx->r25 = MEM_BU(ctx->r18, 0X0);
    // 0x800BE400: sll         $t7, $v0, 2
    ctx->r15 = S32(ctx->r2 << 2);
    // 0x800BE404: andi        $t8, $t7, 0x4
    ctx->r24 = ctx->r15 & 0X4;
    // 0x800BE408: andi        $t5, $t9, 0xFFFB
    ctx->r13 = ctx->r25 & 0XFFFB;
    // 0x800BE40C: or          $t2, $t8, $t5
    ctx->r10 = ctx->r24 | ctx->r13;
    // 0x800BE410: b           L_800BDDC4
    // 0x800BE414: sb          $t2, 0x0($s2)
    MEM_B(0X0, ctx->r18) = ctx->r10;
        goto L_800BDDC4;
    // 0x800BE414: sb          $t2, 0x0($s2)
    MEM_B(0X0, ctx->r18) = ctx->r10;
L_800BE418:
    // 0x800BE418: jal         0x800BD0B0
    // 0x800BE41C: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    AudioSeq_ScriptReadU8(rdram, ctx);
        goto after_44;
    // 0x800BE41C: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    after_44:
    // 0x800BE420: b           L_800BDDC4
    // 0x800BE424: sb          $v0, 0x2($s2)
    MEM_B(0X2, ctx->r18) = ctx->r2;
        goto L_800BDDC4;
    // 0x800BE424: sb          $v0, 0x2($s2)
    MEM_B(0X2, ctx->r18) = ctx->r2;
L_800BE428:
    // 0x800BE428: jal         0x800BD0B0
    // 0x800BE42C: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    AudioSeq_ScriptReadU8(rdram, ctx);
        goto after_45;
    // 0x800BE42C: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    after_45:
    // 0x800BE430: b           L_800BDDC4
    // 0x800BE434: sb          $v0, 0x7D($s2)
    MEM_B(0X7D, ctx->r18) = ctx->r2;
        goto L_800BDDC4;
    // 0x800BE434: sb          $v0, 0x7D($s2)
    MEM_B(0X7D, ctx->r18) = ctx->r2;
L_800BE438:
    // 0x800BE438: jal         0x800BD0B0
    // 0x800BE43C: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    AudioSeq_ScriptReadU8(rdram, ctx);
        goto after_46;
    // 0x800BE43C: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    after_46:
    // 0x800BE440: b           L_800BDDC4
    // 0x800BE444: sb          $v0, 0x7($s2)
    MEM_B(0X7, ctx->r18) = ctx->r2;
        goto L_800BDDC4;
    // 0x800BE444: sb          $v0, 0x7($s2)
    MEM_B(0X7, ctx->r18) = ctx->r2;
L_800BE448:
    // 0x800BE448: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x800BE44C: beq         $s3, $at, L_800BDDC4
    if (ctx->r19 == ctx->r1) {
        // 0x800BE450: nop
    
            goto L_800BDDC4;
    }
    // 0x800BE450: nop

    // 0x800BE454: lbu         $a0, 0x18($s1)
    ctx->r4 = MEM_BU(ctx->r17, 0X18);
    // 0x800BE458: lw          $t3, 0x0($s1)
    ctx->r11 = MEM_W(ctx->r17, 0X0);
    // 0x800BE45C: lw          $t1, 0x34($s2)
    ctx->r9 = MEM_W(ctx->r18, 0X34);
    // 0x800BE460: sll         $t4, $a0, 2
    ctx->r12 = S32(ctx->r4 << 2);
    // 0x800BE464: addu        $t6, $s1, $t4
    ctx->r14 = ADD32(ctx->r17, ctx->r12);
    // 0x800BE468: sw          $t3, 0x4($t6)
    MEM_W(0X4, ctx->r14) = ctx->r11;
    // 0x800BE46C: lbu         $t7, 0x18($s1)
    ctx->r15 = MEM_BU(ctx->r17, 0X18);
    // 0x800BE470: sll         $v0, $s3, 1
    ctx->r2 = S32(ctx->r19 << 1);
    // 0x800BE474: addu        $v1, $t1, $v0
    ctx->r3 = ADD32(ctx->r9, ctx->r2);
    // 0x800BE478: addiu       $t9, $t7, 0x1
    ctx->r25 = ADD32(ctx->r15, 0X1);
    // 0x800BE47C: sb          $t9, 0x18($s1)
    MEM_B(0X18, ctx->r17) = ctx->r25;
    // 0x800BE480: lbu         $t5, 0x0($v1)
    ctx->r13 = MEM_BU(ctx->r3, 0X0);
    // 0x800BE484: lbu         $t8, 0x1($v1)
    ctx->r24 = MEM_BU(ctx->r3, 0X1);
    // 0x800BE488: lw          $t4, 0x14($s4)
    ctx->r12 = MEM_W(ctx->r20, 0X14);
    // 0x800BE48C: sll         $t2, $t5, 8
    ctx->r10 = S32(ctx->r13 << 8);
    // 0x800BE490: addu        $a3, $t8, $t2
    ctx->r7 = ADD32(ctx->r24, ctx->r10);
    // 0x800BE494: andi        $t1, $a3, 0xFFFF
    ctx->r9 = ctx->r7 & 0XFFFF;
    // 0x800BE498: addu        $t3, $t4, $t1
    ctx->r11 = ADD32(ctx->r12, ctx->r9);
    // 0x800BE49C: b           L_800BDDC4
    // 0x800BE4A0: sw          $t3, 0x0($s1)
    MEM_W(0X0, ctx->r17) = ctx->r11;
        goto L_800BDDC4;
    // 0x800BE4A0: sw          $t3, 0x0($s1)
    MEM_W(0X0, ctx->r17) = ctx->r11;
L_800BE4A4:
    // 0x800BE4A4: jal         0x800BD0B0
    // 0x800BE4A8: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    AudioSeq_ScriptReadU8(rdram, ctx);
        goto after_47;
    // 0x800BE4A8: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    after_47:
    // 0x800BE4AC: b           L_800BDDC4
    // 0x800BE4B0: sb          $v0, 0x8($s2)
    MEM_B(0X8, ctx->r18) = ctx->r2;
        goto L_800BDDC4;
    // 0x800BE4B0: sb          $v0, 0x8($s2)
    MEM_B(0X8, ctx->r18) = ctx->r2;
L_800BE4B4:
    // 0x800BE4B4: jal         0x800BD0C4
    // 0x800BE4B8: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    AudioSeq_ScriptReadS16(rdram, ctx);
        goto after_48;
    // 0x800BE4B8: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    after_48:
    // 0x800BE4BC: lw          $t6, 0x14($s4)
    ctx->r14 = MEM_W(ctx->r20, 0X14);
    // 0x800BE4C0: andi        $t7, $v0, 0xFFFF
    ctx->r15 = ctx->r2 & 0XFFFF;
    // 0x800BE4C4: addu        $v1, $t6, $t7
    ctx->r3 = ADD32(ctx->r14, ctx->r15);
    // 0x800BE4C8: lbu         $t9, 0x0($v1)
    ctx->r25 = MEM_BU(ctx->r3, 0X0);
    // 0x800BE4CC: addiu       $v1, $v1, 0x7
    ctx->r3 = ADD32(ctx->r3, 0X7);
    // 0x800BE4D0: sb          $t9, 0x3($s2)
    MEM_B(0X3, ctx->r18) = ctx->r25;
    // 0x800BE4D4: lbu         $t5, -0x6($v1)
    ctx->r13 = MEM_BU(ctx->r3, -0X6);
    // 0x800BE4D8: lbu         $t9, 0x1($s2)
    ctx->r25 = MEM_BU(ctx->r18, 0X1);
    // 0x800BE4DC: sb          $t5, 0x2($s2)
    MEM_B(0X2, ctx->r18) = ctx->r13;
    // 0x800BE4E0: lbu         $t8, -0x5($v1)
    ctx->r24 = MEM_BU(ctx->r3, -0X5);
    // 0x800BE4E4: ori         $t5, $t9, 0x20
    ctx->r13 = ctx->r25 | 0X20;
    // 0x800BE4E8: sb          $t8, 0x5($s2)
    MEM_B(0X5, ctx->r18) = ctx->r24;
    // 0x800BE4EC: lb          $t2, -0x4($v1)
    ctx->r10 = MEM_B(ctx->r3, -0X4);
    // 0x800BE4F0: sh          $t2, 0x1E($s2)
    MEM_H(0X1E, ctx->r18) = ctx->r10;
    // 0x800BE4F4: lbu         $t1, -0x3($v1)
    ctx->r9 = MEM_BU(ctx->r3, -0X3);
    // 0x800BE4F8: sb          $t1, 0x9($s2)
    MEM_B(0X9, ctx->r18) = ctx->r9;
    // 0x800BE4FC: lbu         $t4, -0x2($v1)
    ctx->r12 = MEM_BU(ctx->r3, -0X2);
    // 0x800BE500: sb          $t4, 0xA($s2)
    MEM_B(0XA, ctx->r18) = ctx->r12;
    // 0x800BE504: lbu         $t3, -0x1($v1)
    ctx->r11 = MEM_BU(ctx->r3, -0X1);
    // 0x800BE508: sb          $t3, 0x4($s2)
    MEM_B(0X4, ctx->r18) = ctx->r11;
    // 0x800BE50C: lbu         $t6, 0x0($v1)
    ctx->r14 = MEM_BU(ctx->r3, 0X0);
    // 0x800BE510: sb          $t5, 0x1($s2)
    MEM_B(0X1, ctx->r18) = ctx->r13;
    // 0x800BE514: b           L_800BDDC4
    // 0x800BE518: sb          $t6, 0x7($s2)
    MEM_B(0X7, ctx->r18) = ctx->r14;
        goto L_800BDDC4;
    // 0x800BE518: sb          $t6, 0x7($s2)
    MEM_B(0X7, ctx->r18) = ctx->r14;
L_800BE51C:
    // 0x800BE51C: jal         0x800BD0B0
    // 0x800BE520: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    AudioSeq_ScriptReadU8(rdram, ctx);
        goto after_49;
    // 0x800BE520: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    after_49:
    // 0x800BE524: sb          $v0, 0x3($s2)
    MEM_B(0X3, ctx->r18) = ctx->r2;
    // 0x800BE528: jal         0x800BD0B0
    // 0x800BE52C: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    AudioSeq_ScriptReadU8(rdram, ctx);
        goto after_50;
    // 0x800BE52C: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    after_50:
    // 0x800BE530: sb          $v0, 0x2($s2)
    MEM_B(0X2, ctx->r18) = ctx->r2;
    // 0x800BE534: jal         0x800BD0B0
    // 0x800BE538: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    AudioSeq_ScriptReadU8(rdram, ctx);
        goto after_51;
    // 0x800BE538: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    after_51:
    // 0x800BE53C: sb          $v0, 0x5($s2)
    MEM_B(0X5, ctx->r18) = ctx->r2;
    // 0x800BE540: jal         0x800BD0B0
    // 0x800BE544: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    AudioSeq_ScriptReadU8(rdram, ctx);
        goto after_52;
    // 0x800BE544: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    after_52:
    // 0x800BE548: sll         $t8, $v0, 24
    ctx->r24 = S32(ctx->r2 << 24);
    // 0x800BE54C: sra         $t2, $t8, 24
    ctx->r10 = S32(SIGNED(ctx->r24) >> 24);
    // 0x800BE550: sh          $t2, 0x1E($s2)
    MEM_H(0X1E, ctx->r18) = ctx->r10;
    // 0x800BE554: jal         0x800BD0B0
    // 0x800BE558: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    AudioSeq_ScriptReadU8(rdram, ctx);
        goto after_53;
    // 0x800BE558: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    after_53:
    // 0x800BE55C: sb          $v0, 0x9($s2)
    MEM_B(0X9, ctx->r18) = ctx->r2;
    // 0x800BE560: jal         0x800BD0B0
    // 0x800BE564: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    AudioSeq_ScriptReadU8(rdram, ctx);
        goto after_54;
    // 0x800BE564: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    after_54:
    // 0x800BE568: sb          $v0, 0xA($s2)
    MEM_B(0XA, ctx->r18) = ctx->r2;
    // 0x800BE56C: jal         0x800BD0B0
    // 0x800BE570: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    AudioSeq_ScriptReadU8(rdram, ctx);
        goto after_55;
    // 0x800BE570: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    after_55:
    // 0x800BE574: sb          $v0, 0x4($s2)
    MEM_B(0X4, ctx->r18) = ctx->r2;
    // 0x800BE578: jal         0x800BD0B0
    // 0x800BE57C: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    AudioSeq_ScriptReadU8(rdram, ctx);
        goto after_56;
    // 0x800BE57C: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    after_56:
    // 0x800BE580: lbu         $t4, 0x1($s2)
    ctx->r12 = MEM_BU(ctx->r18, 0X1);
    // 0x800BE584: sb          $v0, 0x7($s2)
    MEM_B(0X7, ctx->r18) = ctx->r2;
    // 0x800BE588: ori         $t3, $t4, 0x20
    ctx->r11 = ctx->r12 | 0X20;
    // 0x800BE58C: b           L_800BDDC4
    // 0x800BE590: sb          $t3, 0x1($s2)
    MEM_B(0X1, ctx->r18) = ctx->r11;
        goto L_800BDDC4;
    // 0x800BE590: sb          $t3, 0x1($s2)
    MEM_B(0X1, ctx->r18) = ctx->r11;
L_800BE594:
    // 0x800BE594: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x800BE598: mtc1        $at, $f10
    ctx->f10.u32l = ctx->r1;
    // 0x800BE59C: sh          $zero, 0x12($s2)
    MEM_H(0X12, ctx->r18) = 0;
    // 0x800BE5A0: sh          $zero, 0xE($s2)
    MEM_H(0XE, ctx->r18) = 0;
    // 0x800BE5A4: sh          $zero, 0x16($s2)
    MEM_H(0X16, ctx->r18) = 0;
    // 0x800BE5A8: sh          $zero, 0x10($s2)
    MEM_H(0X10, ctx->r18) = 0;
    // 0x800BE5AC: sh          $zero, 0xC($s2)
    MEM_H(0XC, ctx->r18) = 0;
    // 0x800BE5B0: sh          $zero, 0x14($s2)
    MEM_H(0X14, ctx->r18) = 0;
    // 0x800BE5B4: b           L_800BDDC4
    // 0x800BE5B8: swc1        $f10, 0x30($s2)
    MEM_W(0X30, ctx->r18) = ctx->f10.u32l;
        goto L_800BDDC4;
    // 0x800BE5B8: swc1        $f10, 0x30($s2)
    MEM_W(0X30, ctx->r18) = ctx->f10.u32l;
L_800BE5BC:
    // 0x800BE5BC: jal         0x800BD0B0
    // 0x800BE5C0: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    AudioSeq_ScriptReadU8(rdram, ctx);
        goto after_57;
    // 0x800BE5C0: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    after_57:
    // 0x800BE5C4: b           L_800BDDC4
    // 0x800BE5C8: sb          $v0, 0x5($s2)
    MEM_B(0X5, ctx->r18) = ctx->r2;
        goto L_800BDDC4;
    // 0x800BE5C8: sb          $v0, 0x5($s2)
    MEM_B(0X5, ctx->r18) = ctx->r2;
L_800BE5CC:
    // 0x800BE5CC: jal         0x800BD0C4
    // 0x800BE5D0: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    AudioSeq_ScriptReadS16(rdram, ctx);
        goto after_58;
    // 0x800BE5D0: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    after_58:
    // 0x800BE5D4: jal         0x800BD0B0
    // 0x800BE5D8: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    AudioSeq_ScriptReadU8(rdram, ctx);
        goto after_59;
    // 0x800BE5D8: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    after_59:
    // 0x800BE5DC: b           L_800BDDC4
    // 0x800BE5E0: nop

        goto L_800BDDC4;
    // 0x800BE5E0: nop

L_800BE5E4:
    // 0x800BE5E4: andi        $t6, $v1, 0xF0
    ctx->r14 = ctx->r3 & 0XF0;
    // 0x800BE5E8: andi        $a0, $v1, 0xF
    ctx->r4 = ctx->r3 & 0XF;
    // 0x800BE5EC: sltiu       $at, $t6, 0xB1
    ctx->r1 = ctx->r14 < 0XB1 ? 1 : 0;
    // 0x800BE5F0: beq         $at, $zero, L_800BDDC4
    if (ctx->r1 == 0) {
        // 0x800BE5F4: andi        $t0, $a0, 0xFF
        ctx->r8 = ctx->r4 & 0XFF;
            goto L_800BDDC4;
    }
    // 0x800BE5F4: andi        $t0, $a0, 0xFF
    ctx->r8 = ctx->r4 & 0XFF;
    // 0x800BE5F8: sll         $t6, $t6, 2
    ctx->r14 = S32(ctx->r14 << 2);
    // 0x800BE5FC: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x800BE600: addu        $at, $at, $t6
    gpr jr_addend_800BE608 = ctx->r14;
    ctx->r1 = ADD32(ctx->r1, ctx->r14);
    // 0x800BE604: lw          $t6, -0x41D0($at)
    ctx->r14 = ADD32(ctx->r1, -0X41D0);
    // 0x800BE608: jr          $t6
    // 0x800BE60C: nop

    switch (jr_addend_800BE608 >> 2) {
        case 0: goto L_800BE610; break;
        case 1: goto L_800BDDC4; break;
        case 2: goto L_800BDDC4; break;
        case 3: goto L_800BDDC4; break;
        case 4: goto L_800BDDC4; break;
        case 5: goto L_800BDDC4; break;
        case 6: goto L_800BDDC4; break;
        case 7: goto L_800BDDC4; break;
        case 8: goto L_800BDDC4; break;
        case 9: goto L_800BDDC4; break;
        case 10: goto L_800BDDC4; break;
        case 11: goto L_800BDDC4; break;
        case 12: goto L_800BDDC4; break;
        case 13: goto L_800BDDC4; break;
        case 14: goto L_800BDDC4; break;
        case 15: goto L_800BDDC4; break;
        case 16: goto L_800BE770; break;
        case 17: goto L_800BDDC4; break;
        case 18: goto L_800BDDC4; break;
        case 19: goto L_800BDDC4; break;
        case 20: goto L_800BDDC4; break;
        case 21: goto L_800BDDC4; break;
        case 22: goto L_800BDDC4; break;
        case 23: goto L_800BDDC4; break;
        case 24: goto L_800BDDC4; break;
        case 25: goto L_800BDDC4; break;
        case 26: goto L_800BDDC4; break;
        case 27: goto L_800BDDC4; break;
        case 28: goto L_800BDDC4; break;
        case 29: goto L_800BDDC4; break;
        case 30: goto L_800BDDC4; break;
        case 31: goto L_800BDDC4; break;
        case 32: goto L_800BE7A0; break;
        case 33: goto L_800BDDC4; break;
        case 34: goto L_800BDDC4; break;
        case 35: goto L_800BDDC4; break;
        case 36: goto L_800BDDC4; break;
        case 37: goto L_800BDDC4; break;
        case 38: goto L_800BDDC4; break;
        case 39: goto L_800BDDC4; break;
        case 40: goto L_800BDDC4; break;
        case 41: goto L_800BDDC4; break;
        case 42: goto L_800BDDC4; break;
        case 43: goto L_800BDDC4; break;
        case 44: goto L_800BDDC4; break;
        case 45: goto L_800BDDC4; break;
        case 46: goto L_800BDDC4; break;
        case 47: goto L_800BDDC4; break;
        case 48: goto L_800BE7BC; break;
        case 49: goto L_800BDDC4; break;
        case 50: goto L_800BDDC4; break;
        case 51: goto L_800BDDC4; break;
        case 52: goto L_800BDDC4; break;
        case 53: goto L_800BDDC4; break;
        case 54: goto L_800BDDC4; break;
        case 55: goto L_800BDDC4; break;
        case 56: goto L_800BDDC4; break;
        case 57: goto L_800BDDC4; break;
        case 58: goto L_800BDDC4; break;
        case 59: goto L_800BDDC4; break;
        case 60: goto L_800BDDC4; break;
        case 61: goto L_800BDDC4; break;
        case 62: goto L_800BDDC4; break;
        case 63: goto L_800BDDC4; break;
        case 64: goto L_800BE7E4; break;
        case 65: goto L_800BDDC4; break;
        case 66: goto L_800BDDC4; break;
        case 67: goto L_800BDDC4; break;
        case 68: goto L_800BDDC4; break;
        case 69: goto L_800BDDC4; break;
        case 70: goto L_800BDDC4; break;
        case 71: goto L_800BDDC4; break;
        case 72: goto L_800BDDC4; break;
        case 73: goto L_800BDDC4; break;
        case 74: goto L_800BDDC4; break;
        case 75: goto L_800BDDC4; break;
        case 76: goto L_800BDDC4; break;
        case 77: goto L_800BDDC4; break;
        case 78: goto L_800BDDC4; break;
        case 79: goto L_800BDDC4; break;
        case 80: goto L_800BE678; break;
        case 81: goto L_800BDDC4; break;
        case 82: goto L_800BDDC4; break;
        case 83: goto L_800BDDC4; break;
        case 84: goto L_800BDDC4; break;
        case 85: goto L_800BDDC4; break;
        case 86: goto L_800BDDC4; break;
        case 87: goto L_800BDDC4; break;
        case 88: goto L_800BDDC4; break;
        case 89: goto L_800BDDC4; break;
        case 90: goto L_800BDDC4; break;
        case 91: goto L_800BDDC4; break;
        case 92: goto L_800BDDC4; break;
        case 93: goto L_800BDDC4; break;
        case 94: goto L_800BDDC4; break;
        case 95: goto L_800BDDC4; break;
        case 96: goto L_800BE694; break;
        case 97: goto L_800BDDC4; break;
        case 98: goto L_800BDDC4; break;
        case 99: goto L_800BDDC4; break;
        case 100: goto L_800BDDC4; break;
        case 101: goto L_800BDDC4; break;
        case 102: goto L_800BDDC4; break;
        case 103: goto L_800BDDC4; break;
        case 104: goto L_800BDDC4; break;
        case 105: goto L_800BDDC4; break;
        case 106: goto L_800BDDC4; break;
        case 107: goto L_800BDDC4; break;
        case 108: goto L_800BDDC4; break;
        case 109: goto L_800BDDC4; break;
        case 110: goto L_800BDDC4; break;
        case 111: goto L_800BDDC4; break;
        case 112: goto L_800BE648; break;
        case 113: goto L_800BDDC4; break;
        case 114: goto L_800BDDC4; break;
        case 115: goto L_800BDDC4; break;
        case 116: goto L_800BDDC4; break;
        case 117: goto L_800BDDC4; break;
        case 118: goto L_800BDDC4; break;
        case 119: goto L_800BDDC4; break;
        case 120: goto L_800BDDC4; break;
        case 121: goto L_800BDDC4; break;
        case 122: goto L_800BDDC4; break;
        case 123: goto L_800BDDC4; break;
        case 124: goto L_800BDDC4; break;
        case 125: goto L_800BDDC4; break;
        case 126: goto L_800BDDC4; break;
        case 127: goto L_800BDDC4; break;
        case 128: goto L_800BE658; break;
        case 129: goto L_800BDDC4; break;
        case 130: goto L_800BDDC4; break;
        case 131: goto L_800BDDC4; break;
        case 132: goto L_800BDDC4; break;
        case 133: goto L_800BDDC4; break;
        case 134: goto L_800BDDC4; break;
        case 135: goto L_800BDDC4; break;
        case 136: goto L_800BDDC4; break;
        case 137: goto L_800BDDC4; break;
        case 138: goto L_800BDDC4; break;
        case 139: goto L_800BDDC4; break;
        case 140: goto L_800BDDC4; break;
        case 141: goto L_800BDDC4; break;
        case 142: goto L_800BDDC4; break;
        case 143: goto L_800BDDC4; break;
        case 144: goto L_800BE6A0; break;
        case 145: goto L_800BDDC4; break;
        case 146: goto L_800BDDC4; break;
        case 147: goto L_800BDDC4; break;
        case 148: goto L_800BDDC4; break;
        case 149: goto L_800BDDC4; break;
        case 150: goto L_800BDDC4; break;
        case 151: goto L_800BDDC4; break;
        case 152: goto L_800BDDC4; break;
        case 153: goto L_800BDDC4; break;
        case 154: goto L_800BDDC4; break;
        case 155: goto L_800BDDC4; break;
        case 156: goto L_800BDDC4; break;
        case 157: goto L_800BDDC4; break;
        case 158: goto L_800BDDC4; break;
        case 159: goto L_800BDDC4; break;
        case 160: goto L_800BE6EC; break;
        case 161: goto L_800BDDC4; break;
        case 162: goto L_800BDDC4; break;
        case 163: goto L_800BDDC4; break;
        case 164: goto L_800BDDC4; break;
        case 165: goto L_800BDDC4; break;
        case 166: goto L_800BDDC4; break;
        case 167: goto L_800BDDC4; break;
        case 168: goto L_800BDDC4; break;
        case 169: goto L_800BDDC4; break;
        case 170: goto L_800BDDC4; break;
        case 171: goto L_800BDDC4; break;
        case 172: goto L_800BDDC4; break;
        case 173: goto L_800BDDC4; break;
        case 174: goto L_800BDDC4; break;
        case 175: goto L_800BDDC4; break;
        case 176: goto L_800BE708; break;
        default: switch_error(__func__, 0x800BE608, 0x800EBE30);
    }
    // 0x800BE60C: nop

L_800BE610:
    // 0x800BE610: andi        $t7, $a0, 0xFF
    ctx->r15 = ctx->r4 & 0XFF;
    // 0x800BE614: sll         $t9, $t7, 2
    ctx->r25 = S32(ctx->r15 << 2);
    // 0x800BE618: addu        $t5, $s2, $t9
    ctx->r13 = ADD32(ctx->r18, ctx->r25);
    // 0x800BE61C: lw          $v1, 0x48($t5)
    ctx->r3 = MEM_W(ctx->r13, 0X48);
    // 0x800BE620: beq         $v1, $zero, L_800BE640
    if (ctx->r3 == 0) {
        // 0x800BE624: nop
    
            goto L_800BE640;
    }
    // 0x800BE624: nop

    // 0x800BE628: lw          $s3, 0x0($v1)
    ctx->r19 = MEM_W(ctx->r3, 0X0);
    // 0x800BE62C: sll         $t8, $s3, 1
    ctx->r24 = S32(ctx->r19 << 1);
    // 0x800BE630: srl         $t2, $t8, 31
    ctx->r10 = S32(U32(ctx->r24) >> 31);
    // 0x800BE634: sll         $t1, $t2, 24
    ctx->r9 = S32(ctx->r10 << 24);
    // 0x800BE638: b           L_800BDDC4
    // 0x800BE63C: sra         $s3, $t1, 24
    ctx->r19 = S32(SIGNED(ctx->r9) >> 24);
        goto L_800BDDC4;
    // 0x800BE63C: sra         $s3, $t1, 24
    ctx->r19 = S32(SIGNED(ctx->r9) >> 24);
L_800BE640:
    // 0x800BE640: b           L_800BDDC4
    // 0x800BE644: addiu       $s3, $zero, -0x1
    ctx->r19 = ADD32(0, -0X1);
        goto L_800BDDC4;
    // 0x800BE644: addiu       $s3, $zero, -0x1
    ctx->r19 = ADD32(0, -0X1);
L_800BE648:
    // 0x800BE648: andi        $t3, $a0, 0xFF
    ctx->r11 = ctx->r4 & 0XFF;
    // 0x800BE64C: addu        $t6, $s2, $t3
    ctx->r14 = ADD32(ctx->r18, ctx->r11);
    // 0x800BE650: b           L_800BDDC4
    // 0x800BE654: sb          $s3, 0x58($t6)
    MEM_B(0X58, ctx->r14) = ctx->r19;
        goto L_800BDDC4;
    // 0x800BE654: sb          $s3, 0x58($t6)
    MEM_B(0X58, ctx->r14) = ctx->r19;
L_800BE658:
    // 0x800BE658: andi        $v1, $a0, 0xFF
    ctx->r3 = ctx->r4 & 0XFF;
    // 0x800BE65C: addu        $a1, $s2, $v1
    ctx->r5 = ADD32(ctx->r18, ctx->r3);
    // 0x800BE660: slti        $at, $v1, 0x4
    ctx->r1 = SIGNED(ctx->r3) < 0X4 ? 1 : 0;
    // 0x800BE664: beq         $at, $zero, L_800BDDC4
    if (ctx->r1 == 0) {
        // 0x800BE668: lb          $s3, 0x58($a1)
        ctx->r19 = MEM_B(ctx->r5, 0X58);
            goto L_800BDDC4;
    }
    // 0x800BE668: lb          $s3, 0x58($a1)
    ctx->r19 = MEM_B(ctx->r5, 0X58);
    // 0x800BE66C: addiu       $t7, $zero, -0x1
    ctx->r15 = ADD32(0, -0X1);
    // 0x800BE670: b           L_800BDDC4
    // 0x800BE674: sb          $t7, 0x58($a1)
    MEM_B(0X58, ctx->r5) = ctx->r15;
        goto L_800BDDC4;
    // 0x800BE674: sb          $t7, 0x58($a1)
    MEM_B(0X58, ctx->r5) = ctx->r15;
L_800BE678:
    // 0x800BE678: andi        $t9, $a0, 0xFF
    ctx->r25 = ctx->r4 & 0XFF;
    // 0x800BE67C: addu        $t5, $s2, $t9
    ctx->r13 = ADD32(ctx->r18, ctx->r25);
    // 0x800BE680: lb          $t8, 0x58($t5)
    ctx->r24 = MEM_B(ctx->r13, 0X58);
    // 0x800BE684: subu        $s3, $s3, $t8
    ctx->r19 = SUB32(ctx->r19, ctx->r24);
    // 0x800BE688: sll         $t2, $s3, 24
    ctx->r10 = S32(ctx->r19 << 24);
    // 0x800BE68C: b           L_800BDDC4
    // 0x800BE690: sra         $s3, $t2, 24
    ctx->r19 = S32(SIGNED(ctx->r10) >> 24);
        goto L_800BDDC4;
    // 0x800BE690: sra         $s3, $t2, 24
    ctx->r19 = S32(SIGNED(ctx->r10) >> 24);
L_800BE694:
    // 0x800BE694: andi        $t4, $a0, 0xFF
    ctx->r12 = ctx->r4 & 0XFF;
    // 0x800BE698: b           L_800BE80C
    // 0x800BE69C: sh          $t4, 0x1A($s2)
    MEM_H(0X1A, ctx->r18) = ctx->r12;
        goto L_800BE80C;
    // 0x800BE69C: sh          $t4, 0x1A($s2)
    MEM_H(0X1A, ctx->r18) = ctx->r12;
L_800BE6A0:
    // 0x800BE6A0: jal         0x800BD0C4
    // 0x800BE6A4: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    AudioSeq_ScriptReadS16(rdram, ctx);
        goto after_60;
    // 0x800BE6A4: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    after_60:
    // 0x800BE6A8: or          $a2, $s0, $zero
    ctx->r6 = ctx->r16 | 0;
    // 0x800BE6AC: andi        $a1, $a2, 0xF
    ctx->r5 = ctx->r6 & 0XF;
    // 0x800BE6B0: or          $a2, $a1, $zero
    ctx->r6 = ctx->r5 | 0;
    // 0x800BE6B4: sw          $a1, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r5;
    // 0x800BE6B8: or          $a0, $s2, $zero
    ctx->r4 = ctx->r18 | 0;
    // 0x800BE6BC: jal         0x800BC9A0
    // 0x800BE6C0: sh          $v0, 0x52($sp)
    MEM_H(0X52, ctx->r29) = ctx->r2;
    AudioSeq_SeqChannelSetLayer(rdram, ctx);
        goto after_61;
    // 0x800BE6C0: sh          $v0, 0x52($sp)
    MEM_H(0X52, ctx->r29) = ctx->r2;
    after_61:
    // 0x800BE6C4: lw          $a2, 0x34($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X34);
    // 0x800BE6C8: bne         $v0, $zero, L_800BDDC4
    if (ctx->r2 != 0) {
        // 0x800BE6CC: lhu         $a3, 0x52($sp)
        ctx->r7 = MEM_HU(ctx->r29, 0X52);
            goto L_800BDDC4;
    }
    // 0x800BE6CC: lhu         $a3, 0x52($sp)
    ctx->r7 = MEM_HU(ctx->r29, 0X52);
    // 0x800BE6D0: lw          $t6, 0x14($s4)
    ctx->r14 = MEM_W(ctx->r20, 0X14);
    // 0x800BE6D4: sll         $t9, $a2, 2
    ctx->r25 = S32(ctx->r6 << 2);
    // 0x800BE6D8: addu        $t5, $s2, $t9
    ctx->r13 = ADD32(ctx->r18, ctx->r25);
    // 0x800BE6DC: lw          $t8, 0x48($t5)
    ctx->r24 = MEM_W(ctx->r13, 0X48);
    // 0x800BE6E0: addu        $t7, $t6, $a3
    ctx->r15 = ADD32(ctx->r14, ctx->r7);
    // 0x800BE6E4: b           L_800BDDC4
    // 0x800BE6E8: sw          $t7, 0x50($t8)
    MEM_W(0X50, ctx->r24) = ctx->r15;
        goto L_800BDDC4;
    // 0x800BE6E8: sw          $t7, 0x50($t8)
    MEM_W(0X50, ctx->r24) = ctx->r15;
L_800BE6EC:
    // 0x800BE6EC: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    // 0x800BE6F0: andi        $t2, $a1, 0xF
    ctx->r10 = ctx->r5 & 0XF;
    // 0x800BE6F4: or          $a1, $t2, $zero
    ctx->r5 = ctx->r10 | 0;
    // 0x800BE6F8: jal         0x800BCAE4
    // 0x800BE6FC: or          $a0, $s2, $zero
    ctx->r4 = ctx->r18 | 0;
    AudioSeq_SeqLayerFree(rdram, ctx);
        goto after_62;
    // 0x800BE6FC: or          $a0, $s2, $zero
    ctx->r4 = ctx->r18 | 0;
    after_62:
    // 0x800BE700: b           L_800BDDC4
    // 0x800BE704: nop

        goto L_800BDDC4;
    // 0x800BE704: nop

L_800BE708:
    // 0x800BE708: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x800BE70C: beq         $s3, $at, L_800BDDC4
    if (ctx->r19 == ctx->r1) {
        // 0x800BE710: or          $a0, $s2, $zero
        ctx->r4 = ctx->r18 | 0;
            goto L_800BDDC4;
    }
    // 0x800BE710: or          $a0, $s2, $zero
    ctx->r4 = ctx->r18 | 0;
    // 0x800BE714: or          $a2, $s0, $zero
    ctx->r6 = ctx->r16 | 0;
    // 0x800BE718: andi        $a1, $a2, 0xF
    ctx->r5 = ctx->r6 & 0XF;
    // 0x800BE71C: or          $a2, $a1, $zero
    ctx->r6 = ctx->r5 | 0;
    // 0x800BE720: jal         0x800BC9A0
    // 0x800BE724: sw          $a1, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r5;
    AudioSeq_SeqChannelSetLayer(rdram, ctx);
        goto after_63;
    // 0x800BE724: sw          $a1, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r5;
    after_63:
    // 0x800BE728: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x800BE72C: beq         $v0, $at, L_800BDDC4
    if (ctx->r2 == ctx->r1) {
        // 0x800BE730: lw          $a2, 0x34($sp)
        ctx->r6 = MEM_W(ctx->r29, 0X34);
            goto L_800BDDC4;
    }
    // 0x800BE730: lw          $a2, 0x34($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X34);
    // 0x800BE734: lw          $t4, 0x34($s2)
    ctx->r12 = MEM_W(ctx->r18, 0X34);
    // 0x800BE738: sll         $t3, $s3, 1
    ctx->r11 = S32(ctx->r19 << 1);
    // 0x800BE73C: lw          $t8, 0x14($s4)
    ctx->r24 = MEM_W(ctx->r20, 0X14);
    // 0x800BE740: addu        $v1, $t4, $t3
    ctx->r3 = ADD32(ctx->r12, ctx->r11);
    // 0x800BE744: lbu         $t9, 0x0($v1)
    ctx->r25 = MEM_BU(ctx->r3, 0X0);
    // 0x800BE748: lbu         $t6, 0x1($v1)
    ctx->r14 = MEM_BU(ctx->r3, 0X1);
    // 0x800BE74C: sll         $t1, $a2, 2
    ctx->r9 = S32(ctx->r6 << 2);
    // 0x800BE750: sll         $t5, $t9, 8
    ctx->r13 = S32(ctx->r25 << 8);
    // 0x800BE754: addu        $t4, $s2, $t1
    ctx->r12 = ADD32(ctx->r18, ctx->r9);
    // 0x800BE758: addu        $a3, $t6, $t5
    ctx->r7 = ADD32(ctx->r14, ctx->r13);
    // 0x800BE75C: lw          $t3, 0x48($t4)
    ctx->r11 = MEM_W(ctx->r12, 0X48);
    // 0x800BE760: andi        $t7, $a3, 0xFFFF
    ctx->r15 = ctx->r7 & 0XFFFF;
    // 0x800BE764: addu        $t2, $t8, $t7
    ctx->r10 = ADD32(ctx->r24, ctx->r15);
    // 0x800BE768: b           L_800BDDC4
    // 0x800BE76C: sw          $t2, 0x50($t3)
    MEM_W(0X50, ctx->r11) = ctx->r10;
        goto L_800BDDC4;
    // 0x800BE76C: sw          $t2, 0x50($t3)
    MEM_W(0X50, ctx->r11) = ctx->r10;
L_800BE770:
    // 0x800BE770: jal         0x800BD0C4
    // 0x800BE774: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    AudioSeq_ScriptReadS16(rdram, ctx);
        goto after_64;
    // 0x800BE774: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    after_64:
    // 0x800BE778: lw          $t6, 0x14($s4)
    ctx->r14 = MEM_W(ctx->r20, 0X14);
    // 0x800BE77C: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    // 0x800BE780: andi        $t9, $a1, 0xF
    ctx->r25 = ctx->r5 & 0XF;
    // 0x800BE784: andi        $t5, $v0, 0xFFFF
    ctx->r13 = ctx->r2 & 0XFFFF;
    // 0x800BE788: or          $a1, $t9, $zero
    ctx->r5 = ctx->r25 | 0;
    // 0x800BE78C: or          $a0, $s4, $zero
    ctx->r4 = ctx->r20 | 0;
    // 0x800BE790: jal         0x800BCE18
    // 0x800BE794: addu        $a2, $t6, $t5
    ctx->r6 = ADD32(ctx->r14, ctx->r13);
    AudioSeq_SequenceChannelEnable(rdram, ctx);
        goto after_65;
    // 0x800BE794: addu        $a2, $t6, $t5
    ctx->r6 = ADD32(ctx->r14, ctx->r13);
    after_65:
    // 0x800BE798: b           L_800BDDC4
    // 0x800BE79C: nop

        goto L_800BDDC4;
    // 0x800BE79C: nop

L_800BE7A0:
    // 0x800BE7A0: andi        $t8, $s0, 0xF
    ctx->r24 = ctx->r16 & 0XF;
    // 0x800BE7A4: sll         $t1, $t8, 2
    ctx->r9 = S32(ctx->r24 << 2);
    // 0x800BE7A8: addu        $t4, $s4, $t1
    ctx->r12 = ADD32(ctx->r20, ctx->r9);
    // 0x800BE7AC: jal         0x800BCB34
    // 0x800BE7B0: lw          $a0, 0x30($t4)
    ctx->r4 = MEM_W(ctx->r12, 0X30);
    AudioSeq_SequenceChannelDisable(rdram, ctx);
        goto after_66;
    // 0x800BE7B0: lw          $a0, 0x30($t4)
    ctx->r4 = MEM_W(ctx->r12, 0X30);
    after_66:
    // 0x800BE7B4: b           L_800BDDC4
    // 0x800BE7B8: nop

        goto L_800BDDC4;
    // 0x800BE7B8: nop

L_800BE7BC:
    // 0x800BE7BC: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    // 0x800BE7C0: jal         0x800BD0B0
    // 0x800BE7C4: sb          $t0, 0x55($sp)
    MEM_B(0X55, ctx->r29) = ctx->r8;
    AudioSeq_ScriptReadU8(rdram, ctx);
        goto after_67;
    // 0x800BE7C4: sb          $t0, 0x55($sp)
    MEM_B(0X55, ctx->r29) = ctx->r8;
    after_67:
    // 0x800BE7C8: lbu         $t0, 0x55($sp)
    ctx->r8 = MEM_BU(ctx->r29, 0X55);
    // 0x800BE7CC: sll         $t2, $t0, 2
    ctx->r10 = S32(ctx->r8 << 2);
    // 0x800BE7D0: addu        $t3, $s4, $t2
    ctx->r11 = ADD32(ctx->r20, ctx->r10);
    // 0x800BE7D4: lw          $t9, 0x30($t3)
    ctx->r25 = MEM_W(ctx->r11, 0X30);
    // 0x800BE7D8: addu        $t6, $t9, $v0
    ctx->r14 = ADD32(ctx->r25, ctx->r2);
    // 0x800BE7DC: b           L_800BDDC4
    // 0x800BE7E0: sb          $s3, 0x58($t6)
    MEM_B(0X58, ctx->r14) = ctx->r19;
        goto L_800BDDC4;
    // 0x800BE7E0: sb          $s3, 0x58($t6)
    MEM_B(0X58, ctx->r14) = ctx->r19;
L_800BE7E4:
    // 0x800BE7E4: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    // 0x800BE7E8: jal         0x800BD0B0
    // 0x800BE7EC: sb          $t0, 0x55($sp)
    MEM_B(0X55, ctx->r29) = ctx->r8;
    AudioSeq_ScriptReadU8(rdram, ctx);
        goto after_68;
    // 0x800BE7EC: sb          $t0, 0x55($sp)
    MEM_B(0X55, ctx->r29) = ctx->r8;
    after_68:
    // 0x800BE7F0: lbu         $t0, 0x55($sp)
    ctx->r8 = MEM_BU(ctx->r29, 0X55);
    // 0x800BE7F4: sll         $t5, $t0, 2
    ctx->r13 = S32(ctx->r8 << 2);
    // 0x800BE7F8: addu        $t7, $s4, $t5
    ctx->r15 = ADD32(ctx->r20, ctx->r13);
    // 0x800BE7FC: lw          $t8, 0x30($t7)
    ctx->r24 = MEM_W(ctx->r15, 0X30);
    // 0x800BE800: addu        $t1, $t8, $v0
    ctx->r9 = ADD32(ctx->r24, ctx->r2);
    // 0x800BE804: b           L_800BDDC4
    // 0x800BE808: lb          $s3, 0x58($t1)
    ctx->r19 = MEM_B(ctx->r9, 0X58);
        goto L_800BDDC4;
    // 0x800BE808: lb          $s3, 0x58($t1)
    ctx->r19 = MEM_B(ctx->r9, 0X58);
L_800BE80C:
    // 0x800BE80C: or          $s1, $s2, $zero
    ctx->r17 = ctx->r18 | 0;
L_800BE810:
    // 0x800BE810: addiu       $s2, $zero, 0x10
    ctx->r18 = ADD32(0, 0X10);
    // 0x800BE814: or          $s0, $zero, $zero
    ctx->r16 = 0 | 0;
L_800BE818:
    // 0x800BE818: lw          $a0, 0x48($s1)
    ctx->r4 = MEM_W(ctx->r17, 0X48);
    // 0x800BE81C: beql        $a0, $zero, L_800BE830
    if (ctx->r4 == 0) {
        // 0x800BE820: addiu       $s0, $s0, 0x4
        ctx->r16 = ADD32(ctx->r16, 0X4);
            goto L_800BE830;
    }
    goto skip_6;
    // 0x800BE820: addiu       $s0, $s0, 0x4
    ctx->r16 = ADD32(ctx->r16, 0X4);
    skip_6:
    // 0x800BE824: jal         0x800BD138
    // 0x800BE828: nop

    AudioSeq_SeqLayerProcessScript(rdram, ctx);
        goto after_69;
    // 0x800BE828: nop

    after_69:
    // 0x800BE82C: addiu       $s0, $s0, 0x4
    ctx->r16 = ADD32(ctx->r16, 0X4);
L_800BE830:
    // 0x800BE830: bne         $s0, $s2, L_800BE818
    if (ctx->r16 != ctx->r18) {
        // 0x800BE834: addiu       $s1, $s1, 0x4
        ctx->r17 = ADD32(ctx->r17, 0X4);
            goto L_800BE818;
    }
    // 0x800BE834: addiu       $s1, $s1, 0x4
    ctx->r17 = ADD32(ctx->r17, 0X4);
L_800BE838:
    // 0x800BE838: lw          $ra, 0x2C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X2C);
L_800BE83C:
    // 0x800BE83C: lw          $s0, 0x18($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X18);
    // 0x800BE840: lw          $s1, 0x1C($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X1C);
    // 0x800BE844: lw          $s2, 0x20($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X20);
    // 0x800BE848: lw          $s3, 0x24($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X24);
    // 0x800BE84C: lw          $s4, 0x28($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X28);
    // 0x800BE850: jr          $ra
    // 0x800BE854: addiu       $sp, $sp, 0x60
    ctx->r29 = ADD32(ctx->r29, 0X60);
    return;
    // 0x800BE854: addiu       $sp, $sp, 0x60
    ctx->r29 = ADD32(ctx->r29, 0X60);
;}
RECOMP_FUNC void AudioSeq_SequencePlayerProcessSequence(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800BE858: addiu       $sp, $sp, -0x60
    ctx->r29 = ADD32(ctx->r29, -0X60);
    // 0x800BE85C: sw          $ra, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r31;
    // 0x800BE860: sw          $s3, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r19;
    // 0x800BE864: sw          $s2, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r18;
    // 0x800BE868: sw          $s1, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r17;
    // 0x800BE86C: sw          $s0, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r16;
    // 0x800BE870: lw          $v0, 0x0($a0)
    ctx->r2 = MEM_W(ctx->r4, 0X0);
    // 0x800BE874: or          $s1, $a0, $zero
    ctx->r17 = ctx->r4 | 0;
    // 0x800BE878: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x800BE87C: srl         $t6, $v0, 31
    ctx->r14 = S32(U32(ctx->r2) >> 31);
    // 0x800BE880: beq         $t6, $zero, L_800BF0A8
    if (ctx->r14 == 0) {
        // 0x800BE884: sll         $t7, $v0, 4
        ctx->r15 = S32(ctx->r2 << 4);
            goto L_800BF0A8;
    }
    // 0x800BE884: sll         $t7, $v0, 4
    ctx->r15 = S32(ctx->r2 << 4);
    // 0x800BE888: srl         $t8, $t7, 31
    ctx->r24 = S32(U32(ctx->r15) >> 31);
    // 0x800BE88C: bne         $t8, $at, L_800BE950
    if (ctx->r24 != ctx->r1) {
        // 0x800BE890: sll         $t0, $v0, 3
        ctx->r8 = S32(ctx->r2 << 3);
            goto L_800BE950;
    }
    // 0x800BE890: sll         $t0, $v0, 3
    ctx->r8 = S32(ctx->r2 << 3);
    // 0x800BE894: addiu       $s0, $a0, 0x104
    ctx->r16 = ADD32(ctx->r4, 0X104);
    // 0x800BE898: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x800BE89C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x800BE8A0: jal         0x800C5C60
    // 0x800BE8A4: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    osRecvMesg_recomp(rdram, ctx);
        goto after_0;
    // 0x800BE8A4: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    after_0:
    // 0x800BE8A8: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x800BE8AC: beql        $v0, $at, L_800BF0AC
    if (ctx->r2 == ctx->r1) {
        // 0x800BE8B0: lw          $ra, 0x2C($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X2C);
            goto L_800BF0AC;
    }
    goto skip_0;
    // 0x800BE8B0: lw          $ra, 0x2C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X2C);
    skip_0:
    // 0x800BE8B4: lw          $t9, 0x13C($s1)
    ctx->r25 = MEM_W(ctx->r17, 0X13C);
    // 0x800BE8B8: lui         $t2, 0x8004
    ctx->r10 = S32(0X8004 << 16);
    // 0x800BE8BC: bnel        $t9, $zero, L_800BE930
    if (ctx->r25 != 0) {
        // 0x800BE8C0: addiu       $t9, $s1, 0x120
        ctx->r25 = ADD32(ctx->r17, 0X120);
            goto L_800BE930;
    }
    goto skip_1;
    // 0x800BE8C0: addiu       $t9, $s1, 0x120
    ctx->r25 = ADD32(ctx->r17, 0X120);
    skip_1:
    // 0x800BE8C4: lbu         $t0, 0x0($s1)
    ctx->r8 = MEM_BU(ctx->r17, 0X0);
    // 0x800BE8C8: lbu         $v1, 0x6($s1)
    ctx->r3 = MEM_BU(ctx->r17, 0X6);
    // 0x800BE8CC: lui         $t4, 0x8004
    ctx->r12 = S32(0X8004 << 16);
    // 0x800BE8D0: andi        $t1, $t0, 0xFFF7
    ctx->r9 = ctx->r8 & 0XFFF7;
    // 0x800BE8D4: sb          $t1, 0x0($s1)
    MEM_B(0X0, ctx->r17) = ctx->r9;
    // 0x800BE8D8: lw          $t2, 0x5518($t2)
    ctx->r10 = MEM_W(ctx->r10, 0X5518);
    // 0x800BE8DC: sll         $t3, $v1, 2
    ctx->r11 = S32(ctx->r3 << 2);
    // 0x800BE8E0: subu        $t3, $t3, $v1
    ctx->r11 = SUB32(ctx->r11, ctx->r3);
    // 0x800BE8E4: lw          $t4, 0x550C($t4)
    ctx->r12 = MEM_W(ctx->r12, 0X550C);
    // 0x800BE8E8: sll         $t3, $t3, 2
    ctx->r11 = S32(ctx->r11 << 2);
    // 0x800BE8EC: addu        $v0, $t2, $t3
    ctx->r2 = ADD32(ctx->r10, ctx->r11);
    // 0x800BE8F0: lw          $a0, 0x4($v0)
    ctx->r4 = MEM_W(ctx->r2, 0X4);
    // 0x800BE8F4: sll         $t5, $v1, 3
    ctx->r13 = S32(ctx->r3 << 3);
    // 0x800BE8F8: addu        $t6, $t4, $t5
    ctx->r14 = ADD32(ctx->r12, ctx->r13);
    // 0x800BE8FC: lw          $a1, 0x4($t6)
    ctx->r5 = MEM_W(ctx->r14, 0X4);
    // 0x800BE900: lbu         $a2, 0x1($v0)
    ctx->r6 = MEM_BU(ctx->r2, 0X1);
    // 0x800BE904: lbu         $a3, 0x2($v0)
    ctx->r7 = MEM_BU(ctx->r2, 0X2);
    // 0x800BE908: jal         0x800B9618
    // 0x800BE90C: addiu       $a0, $a0, -0x4
    ctx->r4 = ADD32(ctx->r4, -0X4);
    Audio_PatchBank(rdram, ctx);
        goto after_1;
    // 0x800BE90C: addiu       $a0, $a0, -0x4
    ctx->r4 = ADD32(ctx->r4, -0X4);
    after_1:
    // 0x800BE910: lbu         $t7, 0x6($s1)
    ctx->r15 = MEM_BU(ctx->r17, 0X6);
    // 0x800BE914: lui         $v1, 0x8004
    ctx->r3 = S32(0X8004 << 16);
    // 0x800BE918: addiu       $v1, $v1, -0x1488
    ctx->r3 = ADD32(ctx->r3, -0X1488);
    // 0x800BE91C: addiu       $a0, $zero, 0x2
    ctx->r4 = ADD32(0, 0X2);
    // 0x800BE920: addu        $t8, $v1, $t7
    ctx->r24 = ADD32(ctx->r3, ctx->r15);
    // 0x800BE924: b           L_800BF0A8
    // 0x800BE928: sb          $a0, 0x0($t8)
    MEM_B(0X0, ctx->r24) = ctx->r4;
        goto L_800BF0A8;
    // 0x800BE928: sb          $a0, 0x0($t8)
    MEM_B(0X0, ctx->r24) = ctx->r4;
    // 0x800BE92C: addiu       $t9, $s1, 0x120
    ctx->r25 = ADD32(ctx->r17, 0X120);
L_800BE930:
    // 0x800BE930: sw          $t9, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r25;
    // 0x800BE934: addiu       $a0, $s1, 0x138
    ctx->r4 = ADD32(ctx->r17, 0X138);
    // 0x800BE938: addiu       $a1, $s1, 0x134
    ctx->r5 = ADD32(ctx->r17, 0X134);
    // 0x800BE93C: addiu       $a2, $s1, 0x13C
    ctx->r6 = ADD32(ctx->r17, 0X13C);
    // 0x800BE940: jal         0x800B8D88
    // 0x800BE944: or          $a3, $s0, $zero
    ctx->r7 = ctx->r16 | 0;
    Audio_DmaPartialCopyAsync(rdram, ctx);
        goto after_2;
    // 0x800BE944: or          $a3, $s0, $zero
    ctx->r7 = ctx->r16 | 0;
    after_2:
    // 0x800BE948: b           L_800BF0AC
    // 0x800BE94C: lw          $ra, 0x2C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X2C);
        goto L_800BF0AC;
    // 0x800BE94C: lw          $ra, 0x2C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X2C);
L_800BE950:
    // 0x800BE950: srl         $t1, $t0, 31
    ctx->r9 = S32(U32(ctx->r8) >> 31);
    // 0x800BE954: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x800BE958: bne         $t1, $at, L_800BE994
    if (ctx->r9 != ctx->r1) {
        // 0x800BE95C: addiu       $a0, $s1, 0xD4
        ctx->r4 = ADD32(ctx->r17, 0XD4);
            goto L_800BE994;
    }
    // 0x800BE95C: addiu       $a0, $s1, 0xD4
    ctx->r4 = ADD32(ctx->r17, 0XD4);
    // 0x800BE960: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x800BE964: jal         0x800C5C60
    // 0x800BE968: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    osRecvMesg_recomp(rdram, ctx);
        goto after_3;
    // 0x800BE968: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    after_3:
    // 0x800BE96C: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x800BE970: beq         $v0, $at, L_800BF0A8
    if (ctx->r2 == ctx->r1) {
        // 0x800BE974: addiu       $a0, $zero, 0x2
        ctx->r4 = ADD32(0, 0X2);
            goto L_800BF0A8;
    }
    // 0x800BE974: addiu       $a0, $zero, 0x2
    ctx->r4 = ADD32(0, 0X2);
    // 0x800BE978: lbu         $t2, 0x0($s1)
    ctx->r10 = MEM_BU(ctx->r17, 0X0);
    // 0x800BE97C: lbu         $t4, 0x4($s1)
    ctx->r12 = MEM_BU(ctx->r17, 0X4);
    // 0x800BE980: lui         $at, 0x8004
    ctx->r1 = S32(0X8004 << 16);
    // 0x800BE984: andi        $t3, $t2, 0xFFEF
    ctx->r11 = ctx->r10 & 0XFFEF;
    // 0x800BE988: sb          $t3, 0x0($s1)
    MEM_B(0X0, ctx->r17) = ctx->r11;
    // 0x800BE98C: addu        $at, $at, $t4
    ctx->r1 = ADD32(ctx->r1, ctx->r12);
    // 0x800BE990: sb          $a0, -0x1448($at)
    MEM_B(-0X1448, ctx->r1) = ctx->r4;
L_800BE994:
    // 0x800BE994: lbu         $t5, 0x4($s1)
    ctx->r13 = MEM_BU(ctx->r17, 0X4);
    // 0x800BE998: lui         $t6, 0x8004
    ctx->r14 = S32(0X8004 << 16);
    // 0x800BE99C: addiu       $t6, $t6, -0x1448
    ctx->r14 = ADD32(ctx->r14, -0X1448);
    // 0x800BE9A0: addu        $v0, $t5, $t6
    ctx->r2 = ADD32(ctx->r13, ctx->r14);
    // 0x800BE9A4: lbu         $t7, 0x0($v0)
    ctx->r15 = MEM_BU(ctx->r2, 0X0);
    // 0x800BE9A8: addiu       $a0, $zero, 0x2
    ctx->r4 = ADD32(0, 0X2);
    // 0x800BE9AC: slti        $t8, $t7, 0x2
    ctx->r24 = SIGNED(ctx->r15) < 0X2 ? 1 : 0;
    // 0x800BE9B0: bne         $t8, $zero, L_800BE9D8
    if (ctx->r24 != 0) {
        // 0x800BE9B4: nop
    
            goto L_800BE9D8;
    }
    // 0x800BE9B4: nop

    // 0x800BE9B8: lbu         $t9, 0x5($s1)
    ctx->r25 = MEM_BU(ctx->r17, 0X5);
    // 0x800BE9BC: lui         $v1, 0x8004
    ctx->r3 = S32(0X8004 << 16);
    // 0x800BE9C0: addiu       $v1, $v1, -0x1488
    ctx->r3 = ADD32(ctx->r3, -0X1488);
    // 0x800BE9C4: addu        $t0, $v1, $t9
    ctx->r8 = ADD32(ctx->r3, ctx->r25);
    // 0x800BE9C8: lbu         $t1, 0x0($t0)
    ctx->r9 = MEM_BU(ctx->r8, 0X0);
    // 0x800BE9CC: slti        $t2, $t1, 0x2
    ctx->r10 = SIGNED(ctx->r9) < 0X2 ? 1 : 0;
    // 0x800BE9D0: beql        $t2, $zero, L_800BE9EC
    if (ctx->r10 == 0) {
        // 0x800BE9D4: sb          $a0, 0x0($v0)
        MEM_B(0X0, ctx->r2) = ctx->r4;
            goto L_800BE9EC;
    }
    goto skip_2;
    // 0x800BE9D4: sb          $a0, 0x0($v0)
    MEM_B(0X0, ctx->r2) = ctx->r4;
    skip_2:
L_800BE9D8:
    // 0x800BE9D8: jal         0x800BCEE0
    // 0x800BE9DC: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    AudioSeq_SequencePlayerDisable(rdram, ctx);
        goto after_4;
    // 0x800BE9DC: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    after_4:
    // 0x800BE9E0: b           L_800BF0AC
    // 0x800BE9E4: lw          $ra, 0x2C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X2C);
        goto L_800BF0AC;
    // 0x800BE9E4: lw          $ra, 0x2C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X2C);
    // 0x800BE9E8: sb          $a0, 0x0($v0)
    MEM_B(0X0, ctx->r2) = ctx->r4;
L_800BE9EC:
    // 0x800BE9EC: lbu         $t3, 0x5($s1)
    ctx->r11 = MEM_BU(ctx->r17, 0X5);
    // 0x800BE9F0: addu        $t4, $v1, $t3
    ctx->r12 = ADD32(ctx->r3, ctx->r11);
    // 0x800BE9F4: sb          $a0, 0x0($t4)
    MEM_B(0X0, ctx->r12) = ctx->r4;
    // 0x800BE9F8: lw          $t5, 0x0($s1)
    ctx->r13 = MEM_W(ctx->r17, 0X0);
    // 0x800BE9FC: sll         $t7, $t5, 2
    ctx->r15 = S32(ctx->r13 << 2);
    // 0x800BEA00: bgezl       $t7, L_800BEA1C
    if (SIGNED(ctx->r15) >= 0) {
        // 0x800BEA04: lhu         $t0, 0xA($s1)
        ctx->r8 = MEM_HU(ctx->r17, 0XA);
            goto L_800BEA1C;
    }
    goto skip_3;
    // 0x800BEA04: lhu         $t0, 0xA($s1)
    ctx->r8 = MEM_HU(ctx->r17, 0XA);
    skip_3:
    // 0x800BEA08: lbu         $t8, 0x3($s1)
    ctx->r24 = MEM_BU(ctx->r17, 0X3);
    // 0x800BEA0C: andi        $t9, $t8, 0x80
    ctx->r25 = ctx->r24 & 0X80;
    // 0x800BEA10: bnel        $t9, $zero, L_800BF0AC
    if (ctx->r25 != 0) {
        // 0x800BEA14: lw          $ra, 0x2C($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X2C);
            goto L_800BF0AC;
    }
    goto skip_4;
    // 0x800BEA14: lw          $ra, 0x2C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X2C);
    skip_4:
    // 0x800BEA18: lhu         $t0, 0xA($s1)
    ctx->r8 = MEM_HU(ctx->r17, 0XA);
L_800BEA1C:
    // 0x800BEA1C: lhu         $t1, 0x8($s1)
    ctx->r9 = MEM_HU(ctx->r17, 0X8);
    // 0x800BEA20: lui         $v1, 0x8004
    ctx->r3 = S32(0X8004 << 16);
    // 0x800BEA24: addu        $t2, $t0, $t1
    ctx->r10 = ADD32(ctx->r8, ctx->r9);
    // 0x800BEA28: sh          $t2, 0xA($s1)
    MEM_H(0XA, ctx->r17) = ctx->r10;
    // 0x800BEA2C: lh          $v1, 0x554C($v1)
    ctx->r3 = MEM_H(ctx->r3, 0X554C);
    // 0x800BEA30: andi        $v0, $t2, 0xFFFF
    ctx->r2 = ctx->r10 & 0XFFFF;
    // 0x800BEA34: slt         $at, $v0, $v1
    ctx->r1 = SIGNED(ctx->r2) < SIGNED(ctx->r3) ? 1 : 0;
    // 0x800BEA38: bnel        $at, $zero, L_800BF0AC
    if (ctx->r1 != 0) {
        // 0x800BEA3C: lw          $ra, 0x2C($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X2C);
            goto L_800BF0AC;
    }
    goto skip_5;
    // 0x800BEA3C: lw          $ra, 0x2C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X2C);
    skip_5:
    // 0x800BEA40: lhu         $a0, 0xE($s1)
    ctx->r4 = MEM_HU(ctx->r17, 0XE);
    // 0x800BEA44: subu        $t4, $v0, $v1
    ctx->r12 = SUB32(ctx->r2, ctx->r3);
    // 0x800BEA48: sh          $t4, 0xA($s1)
    MEM_H(0XA, ctx->r17) = ctx->r12;
    // 0x800BEA4C: slti        $at, $a0, 0x2
    ctx->r1 = SIGNED(ctx->r4) < 0X2 ? 1 : 0;
    // 0x800BEA50: bne         $at, $zero, L_800BEA60
    if (ctx->r1 != 0) {
        // 0x800BEA54: addiu       $t5, $a0, -0x1
        ctx->r13 = ADD32(ctx->r4, -0X1);
            goto L_800BEA60;
    }
    // 0x800BEA54: addiu       $t5, $a0, -0x1
    ctx->r13 = ADD32(ctx->r4, -0X1);
    // 0x800BEA58: b           L_800BF05C
    // 0x800BEA5C: sh          $t5, 0xE($s1)
    MEM_H(0XE, ctx->r17) = ctx->r13;
        goto L_800BF05C;
    // 0x800BEA5C: sh          $t5, 0xE($s1)
    MEM_H(0XE, ctx->r17) = ctx->r13;
L_800BEA60:
    // 0x800BEA60: lbu         $t7, 0x0($s1)
    ctx->r15 = MEM_BU(ctx->r17, 0X0);
    // 0x800BEA64: addiu       $s0, $s1, 0x70
    ctx->r16 = ADD32(ctx->r17, 0X70);
    // 0x800BEA68: ori         $t8, $t7, 0x4
    ctx->r24 = ctx->r15 | 0X4;
    // 0x800BEA6C: sb          $t8, 0x0($s1)
    MEM_B(0X0, ctx->r17) = ctx->r24;
    // 0x800BEA70: lw          $s3, 0x58($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X58);
L_800BEA74:
    // 0x800BEA74: jal         0x800BD0B0
    // 0x800BEA78: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    AudioSeq_ScriptReadU8(rdram, ctx);
        goto after_5;
    // 0x800BEA78: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_5:
    // 0x800BEA7C: addiu       $at, $zero, 0xFF
    ctx->r1 = ADD32(0, 0XFF);
    // 0x800BEA80: bne         $v0, $at, L_800BEABC
    if (ctx->r2 != ctx->r1) {
        // 0x800BEA84: andi        $s2, $v0, 0xFF
        ctx->r18 = ctx->r2 & 0XFF;
            goto L_800BEABC;
    }
    // 0x800BEA84: andi        $s2, $v0, 0xFF
    ctx->r18 = ctx->r2 & 0XFF;
    // 0x800BEA88: lbu         $a0, 0x18($s0)
    ctx->r4 = MEM_BU(ctx->r16, 0X18);
    // 0x800BEA8C: bne         $a0, $zero, L_800BEAA4
    if (ctx->r4 != 0) {
        // 0x800BEA90: addiu       $v1, $a0, -0x1
        ctx->r3 = ADD32(ctx->r4, -0X1);
            goto L_800BEAA4;
    }
    // 0x800BEA90: addiu       $v1, $a0, -0x1
    ctx->r3 = ADD32(ctx->r4, -0X1);
    // 0x800BEA94: jal         0x800BCEE0
    // 0x800BEA98: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    AudioSeq_SequencePlayerDisable(rdram, ctx);
        goto after_6;
    // 0x800BEA98: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    after_6:
    // 0x800BEA9C: b           L_800BF05C
    // 0x800BEAA0: nop

        goto L_800BF05C;
    // 0x800BEAA0: nop

L_800BEAA4:
    // 0x800BEAA4: andi        $t9, $v1, 0xFF
    ctx->r25 = ctx->r3 & 0XFF;
    // 0x800BEAA8: sll         $t0, $t9, 2
    ctx->r8 = S32(ctx->r25 << 2);
    // 0x800BEAAC: addu        $t1, $s0, $t0
    ctx->r9 = ADD32(ctx->r16, ctx->r8);
    // 0x800BEAB0: sb          $t9, 0x18($s0)
    MEM_B(0X18, ctx->r16) = ctx->r25;
    // 0x800BEAB4: lw          $t2, 0x4($t1)
    ctx->r10 = MEM_W(ctx->r9, 0X4);
    // 0x800BEAB8: sw          $t2, 0x0($s0)
    MEM_W(0X0, ctx->r16) = ctx->r10;
L_800BEABC:
    // 0x800BEABC: andi        $v1, $v0, 0xFF
    ctx->r3 = ctx->r2 & 0XFF;
    // 0x800BEAC0: addiu       $at, $zero, 0xFD
    ctx->r1 = ADD32(0, 0XFD);
    // 0x800BEAC4: bne         $v1, $at, L_800BEADC
    if (ctx->r3 != ctx->r1) {
        // 0x800BEAC8: andi        $v0, $v1, 0xF0
        ctx->r2 = ctx->r3 & 0XF0;
            goto L_800BEADC;
    }
    // 0x800BEAC8: andi        $v0, $v1, 0xF0
    ctx->r2 = ctx->r3 & 0XF0;
    // 0x800BEACC: jal         0x800BD0F4
    // 0x800BEAD0: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    AudioSeq_ScriptReadCompressedU16(rdram, ctx);
        goto after_7;
    // 0x800BEAD0: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_7:
    // 0x800BEAD4: b           L_800BF05C
    // 0x800BEAD8: sh          $v0, 0xE($s1)
    MEM_H(0XE, ctx->r17) = ctx->r2;
        goto L_800BF05C;
    // 0x800BEAD8: sh          $v0, 0xE($s1)
    MEM_H(0XE, ctx->r17) = ctx->r2;
L_800BEADC:
    // 0x800BEADC: addiu       $at, $zero, 0xFE
    ctx->r1 = ADD32(0, 0XFE);
    // 0x800BEAE0: bne         $v1, $at, L_800BEAF4
    if (ctx->r3 != ctx->r1) {
        // 0x800BEAE4: addiu       $t4, $v1, -0xC8
        ctx->r12 = ADD32(ctx->r3, -0XC8);
            goto L_800BEAF4;
    }
    // 0x800BEAE4: addiu       $t4, $v1, -0xC8
    ctx->r12 = ADD32(ctx->r3, -0XC8);
    // 0x800BEAE8: addiu       $t3, $zero, 0x1
    ctx->r11 = ADD32(0, 0X1);
    // 0x800BEAEC: b           L_800BF05C
    // 0x800BEAF0: sh          $t3, 0xE($s1)
    MEM_H(0XE, ctx->r17) = ctx->r11;
        goto L_800BF05C;
    // 0x800BEAF0: sh          $t3, 0xE($s1)
    MEM_H(0XE, ctx->r17) = ctx->r11;
L_800BEAF4:
    // 0x800BEAF4: slti        $at, $v1, 0xC0
    ctx->r1 = SIGNED(ctx->r3) < 0XC0 ? 1 : 0;
    // 0x800BEAF8: bne         $at, $zero, L_800BEF90
    if (ctx->r1 != 0) {
        // 0x800BEAFC: sltiu       $at, $t4, 0x38
        ctx->r1 = ctx->r12 < 0X38 ? 1 : 0;
            goto L_800BEF90;
    }
    // 0x800BEAFC: sltiu       $at, $t4, 0x38
    ctx->r1 = ctx->r12 < 0X38 ? 1 : 0;
    // 0x800BEB00: beq         $at, $zero, L_800BEA74
    if (ctx->r1 == 0) {
        // 0x800BEB04: sll         $t4, $t4, 2
        ctx->r12 = S32(ctx->r12 << 2);
            goto L_800BEA74;
    }
    // 0x800BEB04: sll         $t4, $t4, 2
    ctx->r12 = S32(ctx->r12 << 2);
    // 0x800BEB08: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x800BEB0C: addu        $at, $at, $t4
    gpr jr_addend_800BEB14 = ctx->r12;
    ctx->r1 = ADD32(ctx->r1, ctx->r12);
    // 0x800BEB10: lw          $t4, -0x3F0C($at)
    ctx->r12 = ADD32(ctx->r1, -0X3F0C);
    // 0x800BEB14: jr          $t4
    // 0x800BEB18: nop

    switch (jr_addend_800BEB14 >> 2) {
        case 0: goto L_800BEF80; break;
        case 1: goto L_800BEF70; break;
        case 2: goto L_800BEA74; break;
        case 3: goto L_800BEA74; break;
        case 4: goto L_800BEF60; break;
        case 5: goto L_800BEA74; break;
        case 6: goto L_800BEA74; break;
        case 7: goto L_800BEA74; break;
        case 8: goto L_800BEF50; break;
        case 9: goto L_800BEF24; break;
        case 10: goto L_800BEF24; break;
        case 11: goto L_800BEF14; break;
        case 12: goto L_800BEF04; break;
        case 13: goto L_800BEED8; break;
        case 14: goto L_800BEEBC; break;
        case 15: goto L_800BEEA0; break;
        case 16: goto L_800BEA74; break;
        case 17: goto L_800BEE74; break;
        case 18: goto L_800BED60; break;
        case 19: goto L_800BEDDC; break;
        case 20: goto L_800BECDC; break;
        case 21: goto L_800BECDC; break;
        case 22: goto L_800BECBC; break;
        case 23: goto L_800BECB8; break;
        case 24: goto L_800BEA74; break;
        case 25: goto L_800BEA74; break;
        case 26: goto L_800BEA74; break;
        case 27: goto L_800BEA74; break;
        case 28: goto L_800BEA74; break;
        case 29: goto L_800BEA74; break;
        case 30: goto L_800BEA74; break;
        case 31: goto L_800BEA74; break;
        case 32: goto L_800BEA74; break;
        case 33: goto L_800BEA74; break;
        case 34: goto L_800BEA74; break;
        case 35: goto L_800BEA74; break;
        case 36: goto L_800BEA74; break;
        case 37: goto L_800BEA74; break;
        case 38: goto L_800BEA74; break;
        case 39: goto L_800BEA74; break;
        case 40: goto L_800BECA8; break;
        case 41: goto L_800BEC80; break;
        case 42: goto L_800BEC38; break;
        case 43: goto L_800BEC38; break;
        case 44: goto L_800BEC38; break;
        case 45: goto L_800BEBE0; break;
        case 46: goto L_800BEA74; break;
        case 47: goto L_800BEB98; break;
        case 48: goto L_800BEB60; break;
        case 49: goto L_800BEBE0; break;
        case 50: goto L_800BEBE0; break;
        case 51: goto L_800BEBE0; break;
        case 52: goto L_800BEB1C; break;
        case 53: goto L_800BEA74; break;
        case 54: goto L_800BEA74; break;
        case 55: goto L_800BEA74; break;
        default: switch_error(__func__, 0x800BEB14, 0x800EC0F4);
    }
    // 0x800BEB18: nop

L_800BEB1C:
    // 0x800BEB1C: jal         0x800BD0C4
    // 0x800BEB20: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    AudioSeq_ScriptReadS16(rdram, ctx);
        goto after_8;
    // 0x800BEB20: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_8:
    // 0x800BEB24: lbu         $t6, 0x18($s0)
    ctx->r14 = MEM_BU(ctx->r16, 0X18);
    // 0x800BEB28: lw          $t5, 0x0($s0)
    ctx->r13 = MEM_W(ctx->r16, 0X0);
    // 0x800BEB2C: andi        $t2, $v0, 0xFFFF
    ctx->r10 = ctx->r2 & 0XFFFF;
    // 0x800BEB30: sll         $t7, $t6, 2
    ctx->r15 = S32(ctx->r14 << 2);
    // 0x800BEB34: addu        $t8, $s0, $t7
    ctx->r24 = ADD32(ctx->r16, ctx->r15);
    // 0x800BEB38: sw          $t5, 0x4($t8)
    MEM_W(0X4, ctx->r24) = ctx->r13;
    // 0x800BEB3C: lbu         $t9, 0x18($s0)
    ctx->r25 = MEM_BU(ctx->r16, 0X18);
    // 0x800BEB40: addiu       $t0, $t9, 0x1
    ctx->r8 = ADD32(ctx->r25, 0X1);
    // 0x800BEB44: sb          $t0, 0x18($s0)
    MEM_B(0X18, ctx->r16) = ctx->r8;
    // 0x800BEB48: lw          $t1, 0x14($s1)
    ctx->r9 = MEM_W(ctx->r17, 0X14);
    // 0x800BEB4C: addu        $t3, $t1, $t2
    ctx->r11 = ADD32(ctx->r9, ctx->r10);
    // 0x800BEB50: b           L_800BEA74
    // 0x800BEB54: sw          $t3, 0x0($s0)
    MEM_W(0X0, ctx->r16) = ctx->r11;
        goto L_800BEA74;
    // 0x800BEB54: sw          $t3, 0x0($s0)
    MEM_W(0X0, ctx->r16) = ctx->r11;
    // 0x800BEB58: b           L_800BEA74
    // 0x800BEB5C: nop

        goto L_800BEA74;
    // 0x800BEB5C: nop

L_800BEB60:
    // 0x800BEB60: jal         0x800BD0B0
    // 0x800BEB64: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    AudioSeq_ScriptReadU8(rdram, ctx);
        goto after_9;
    // 0x800BEB64: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_9:
    // 0x800BEB68: lbu         $t4, 0x18($s0)
    ctx->r12 = MEM_BU(ctx->r16, 0X18);
    // 0x800BEB6C: addu        $t6, $s0, $t4
    ctx->r14 = ADD32(ctx->r16, ctx->r12);
    // 0x800BEB70: sb          $v0, 0x14($t6)
    MEM_B(0X14, ctx->r14) = ctx->r2;
    // 0x800BEB74: lbu         $t5, 0x18($s0)
    ctx->r13 = MEM_BU(ctx->r16, 0X18);
    // 0x800BEB78: lw          $t7, 0x0($s0)
    ctx->r15 = MEM_W(ctx->r16, 0X0);
    // 0x800BEB7C: sll         $t8, $t5, 2
    ctx->r24 = S32(ctx->r13 << 2);
    // 0x800BEB80: addu        $t9, $s0, $t8
    ctx->r25 = ADD32(ctx->r16, ctx->r24);
    // 0x800BEB84: sw          $t7, 0x4($t9)
    MEM_W(0X4, ctx->r25) = ctx->r15;
    // 0x800BEB88: lbu         $t0, 0x18($s0)
    ctx->r8 = MEM_BU(ctx->r16, 0X18);
    // 0x800BEB8C: addiu       $t1, $t0, 0x1
    ctx->r9 = ADD32(ctx->r8, 0X1);
    // 0x800BEB90: b           L_800BEA74
    // 0x800BEB94: sb          $t1, 0x18($s0)
    MEM_B(0X18, ctx->r16) = ctx->r9;
        goto L_800BEA74;
    // 0x800BEB94: sb          $t1, 0x18($s0)
    MEM_B(0X18, ctx->r16) = ctx->r9;
L_800BEB98:
    // 0x800BEB98: lbu         $t2, 0x18($s0)
    ctx->r10 = MEM_BU(ctx->r16, 0X18);
    // 0x800BEB9C: addu        $v0, $s0, $t2
    ctx->r2 = ADD32(ctx->r16, ctx->r10);
    // 0x800BEBA0: lbu         $t3, 0x13($v0)
    ctx->r11 = MEM_BU(ctx->r2, 0X13);
    // 0x800BEBA4: addiu       $t4, $t3, -0x1
    ctx->r12 = ADD32(ctx->r11, -0X1);
    // 0x800BEBA8: sb          $t4, 0x13($v0)
    MEM_B(0X13, ctx->r2) = ctx->r12;
    // 0x800BEBAC: lbu         $a0, 0x18($s0)
    ctx->r4 = MEM_BU(ctx->r16, 0X18);
    // 0x800BEBB0: addu        $t6, $s0, $a0
    ctx->r14 = ADD32(ctx->r16, ctx->r4);
    // 0x800BEBB4: lbu         $t5, 0x13($t6)
    ctx->r13 = MEM_BU(ctx->r14, 0X13);
    // 0x800BEBB8: or          $v1, $a0, $zero
    ctx->r3 = ctx->r4 | 0;
    // 0x800BEBBC: sll         $t8, $v1, 2
    ctx->r24 = S32(ctx->r3 << 2);
    // 0x800BEBC0: beq         $t5, $zero, L_800BEBD8
    if (ctx->r13 == 0) {
        // 0x800BEBC4: addiu       $t0, $a0, -0x1
        ctx->r8 = ADD32(ctx->r4, -0X1);
            goto L_800BEBD8;
    }
    // 0x800BEBC4: addiu       $t0, $a0, -0x1
    ctx->r8 = ADD32(ctx->r4, -0X1);
    // 0x800BEBC8: addu        $t7, $s0, $t8
    ctx->r15 = ADD32(ctx->r16, ctx->r24);
    // 0x800BEBCC: lw          $t9, 0x0($t7)
    ctx->r25 = MEM_W(ctx->r15, 0X0);
    // 0x800BEBD0: b           L_800BEA74
    // 0x800BEBD4: sw          $t9, 0x0($s0)
    MEM_W(0X0, ctx->r16) = ctx->r25;
        goto L_800BEA74;
    // 0x800BEBD4: sw          $t9, 0x0($s0)
    MEM_W(0X0, ctx->r16) = ctx->r25;
L_800BEBD8:
    // 0x800BEBD8: b           L_800BEA74
    // 0x800BEBDC: sb          $t0, 0x18($s0)
    MEM_B(0X18, ctx->r16) = ctx->r8;
        goto L_800BEA74;
    // 0x800BEBDC: sb          $t0, 0x18($s0)
    MEM_B(0X18, ctx->r16) = ctx->r8;
L_800BEBE0:
    // 0x800BEBE0: jal         0x800BD0C4
    // 0x800BEBE4: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    AudioSeq_ScriptReadS16(rdram, ctx);
        goto after_10;
    // 0x800BEBE4: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_10:
    // 0x800BEBE8: addiu       $at, $zero, 0xFA
    ctx->r1 = ADD32(0, 0XFA);
    // 0x800BEBEC: bne         $s2, $at, L_800BEBFC
    if (ctx->r18 != ctx->r1) {
        // 0x800BEBF0: or          $v1, $s2, $zero
        ctx->r3 = ctx->r18 | 0;
            goto L_800BEBFC;
    }
    // 0x800BEBF0: or          $v1, $s2, $zero
    ctx->r3 = ctx->r18 | 0;
    // 0x800BEBF4: bne         $s3, $zero, L_800BEA74
    if (ctx->r19 != 0) {
        // 0x800BEBF8: nop
    
            goto L_800BEA74;
    }
    // 0x800BEBF8: nop

L_800BEBFC:
    // 0x800BEBFC: addiu       $at, $zero, 0xF9
    ctx->r1 = ADD32(0, 0XF9);
    // 0x800BEC00: bnel        $v1, $at, L_800BEC14
    if (ctx->r3 != ctx->r1) {
        // 0x800BEC04: addiu       $at, $zero, 0xF5
        ctx->r1 = ADD32(0, 0XF5);
            goto L_800BEC14;
    }
    goto skip_6;
    // 0x800BEC04: addiu       $at, $zero, 0xF5
    ctx->r1 = ADD32(0, 0XF5);
    skip_6:
    // 0x800BEC08: bgez        $s3, L_800BEA74
    if (SIGNED(ctx->r19) >= 0) {
        // 0x800BEC0C: nop
    
            goto L_800BEA74;
    }
    // 0x800BEC0C: nop

    // 0x800BEC10: addiu       $at, $zero, 0xF5
    ctx->r1 = ADD32(0, 0XF5);
L_800BEC14:
    // 0x800BEC14: bnel        $v1, $at, L_800BEC28
    if (ctx->r3 != ctx->r1) {
        // 0x800BEC18: lw          $t1, 0x14($s1)
        ctx->r9 = MEM_W(ctx->r17, 0X14);
            goto L_800BEC28;
    }
    goto skip_7;
    // 0x800BEC18: lw          $t1, 0x14($s1)
    ctx->r9 = MEM_W(ctx->r17, 0X14);
    skip_7:
    // 0x800BEC1C: bltz        $s3, L_800BEA74
    if (SIGNED(ctx->r19) < 0) {
        // 0x800BEC20: nop
    
            goto L_800BEA74;
    }
    // 0x800BEC20: nop

    // 0x800BEC24: lw          $t1, 0x14($s1)
    ctx->r9 = MEM_W(ctx->r17, 0X14);
L_800BEC28:
    // 0x800BEC28: andi        $t2, $v0, 0xFFFF
    ctx->r10 = ctx->r2 & 0XFFFF;
    // 0x800BEC2C: addu        $t3, $t1, $t2
    ctx->r11 = ADD32(ctx->r9, ctx->r10);
    // 0x800BEC30: b           L_800BEA74
    // 0x800BEC34: sw          $t3, 0x0($s0)
    MEM_W(0X0, ctx->r16) = ctx->r11;
        goto L_800BEA74;
    // 0x800BEC34: sw          $t3, 0x0($s0)
    MEM_W(0X0, ctx->r16) = ctx->r11;
L_800BEC38:
    // 0x800BEC38: jal         0x800BD0B0
    // 0x800BEC3C: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    AudioSeq_ScriptReadU8(rdram, ctx);
        goto after_11;
    // 0x800BEC3C: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_11:
    // 0x800BEC40: addiu       $at, $zero, 0xF3
    ctx->r1 = ADD32(0, 0XF3);
    // 0x800BEC44: bne         $s2, $at, L_800BEC54
    if (ctx->r18 != ctx->r1) {
        // 0x800BEC48: or          $v1, $s2, $zero
        ctx->r3 = ctx->r18 | 0;
            goto L_800BEC54;
    }
    // 0x800BEC48: or          $v1, $s2, $zero
    ctx->r3 = ctx->r18 | 0;
    // 0x800BEC4C: bne         $s3, $zero, L_800BEA74
    if (ctx->r19 != 0) {
        // 0x800BEC50: nop
    
            goto L_800BEA74;
    }
    // 0x800BEC50: nop

L_800BEC54:
    // 0x800BEC54: addiu       $at, $zero, 0xF2
    ctx->r1 = ADD32(0, 0XF2);
    // 0x800BEC58: bnel        $v1, $at, L_800BEC6C
    if (ctx->r3 != ctx->r1) {
        // 0x800BEC5C: lw          $t4, 0x0($s0)
        ctx->r12 = MEM_W(ctx->r16, 0X0);
            goto L_800BEC6C;
    }
    goto skip_8;
    // 0x800BEC5C: lw          $t4, 0x0($s0)
    ctx->r12 = MEM_W(ctx->r16, 0X0);
    skip_8:
    // 0x800BEC60: bgez        $s3, L_800BEA74
    if (SIGNED(ctx->r19) >= 0) {
        // 0x800BEC64: nop
    
            goto L_800BEA74;
    }
    // 0x800BEC64: nop

    // 0x800BEC68: lw          $t4, 0x0($s0)
    ctx->r12 = MEM_W(ctx->r16, 0X0);
L_800BEC6C:
    // 0x800BEC6C: sll         $t6, $v0, 24
    ctx->r14 = S32(ctx->r2 << 24);
    // 0x800BEC70: sra         $t5, $t6, 24
    ctx->r13 = S32(SIGNED(ctx->r14) >> 24);
    // 0x800BEC74: addu        $t8, $t4, $t5
    ctx->r24 = ADD32(ctx->r12, ctx->r13);
    // 0x800BEC78: b           L_800BEA74
    // 0x800BEC7C: sw          $t8, 0x0($s0)
    MEM_W(0X0, ctx->r16) = ctx->r24;
        goto L_800BEA74;
    // 0x800BEC7C: sw          $t8, 0x0($s0)
    MEM_W(0X0, ctx->r16) = ctx->r24;
L_800BEC80:
    // 0x800BEC80: addiu       $a0, $s1, 0x94
    ctx->r4 = ADD32(ctx->r17, 0X94);
    // 0x800BEC84: jal         0x800BB400
    // 0x800BEC88: sw          $a0, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r4;
    Audio_NotePoolClear(rdram, ctx);
        goto after_12;
    // 0x800BEC88: sw          $a0, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r4;
    after_12:
    // 0x800BEC8C: jal         0x800BD0B0
    // 0x800BEC90: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    AudioSeq_ScriptReadU8(rdram, ctx);
        goto after_13;
    // 0x800BEC90: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_13:
    // 0x800BEC94: lw          $a0, 0x38($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X38);
    // 0x800BEC98: jal         0x800BB560
    // 0x800BEC9C: or          $a1, $v0, $zero
    ctx->r5 = ctx->r2 | 0;
    Audio_NotePoolFill(rdram, ctx);
        goto after_14;
    // 0x800BEC9C: or          $a1, $v0, $zero
    ctx->r5 = ctx->r2 | 0;
    after_14:
    // 0x800BECA0: b           L_800BEA74
    // 0x800BECA4: nop

        goto L_800BEA74;
    // 0x800BECA4: nop

L_800BECA8:
    // 0x800BECA8: jal         0x800BB400
    // 0x800BECAC: addiu       $a0, $s1, 0x94
    ctx->r4 = ADD32(ctx->r17, 0X94);
    Audio_NotePoolClear(rdram, ctx);
        goto after_15;
    // 0x800BECAC: addiu       $a0, $s1, 0x94
    ctx->r4 = ADD32(ctx->r17, 0X94);
    after_15:
    // 0x800BECB0: b           L_800BEA74
    // 0x800BECB4: nop

        goto L_800BEA74;
    // 0x800BECB4: nop

L_800BECB8:
    // 0x800BECB8: sh          $zero, 0xC($s1)
    MEM_H(0XC, ctx->r17) = 0;
L_800BECBC:
    // 0x800BECBC: jal         0x800BD0B0
    // 0x800BECC0: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    AudioSeq_ScriptReadU8(rdram, ctx);
        goto after_16;
    // 0x800BECC0: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_16:
    // 0x800BECC4: lh          $t7, 0xC($s1)
    ctx->r15 = MEM_H(ctx->r17, 0XC);
    // 0x800BECC8: sll         $t9, $v0, 24
    ctx->r25 = S32(ctx->r2 << 24);
    // 0x800BECCC: sra         $t0, $t9, 24
    ctx->r8 = S32(SIGNED(ctx->r25) >> 24);
    // 0x800BECD0: addu        $t1, $t7, $t0
    ctx->r9 = ADD32(ctx->r15, ctx->r8);
    // 0x800BECD4: b           L_800BEA74
    // 0x800BECD8: sh          $t1, 0xC($s1)
    MEM_H(0XC, ctx->r17) = ctx->r9;
        goto L_800BEA74;
    // 0x800BECD8: sh          $t1, 0xC($s1)
    MEM_H(0XC, ctx->r17) = ctx->r9;
L_800BECDC:
    // 0x800BECDC: jal         0x800BD0B0
    // 0x800BECE0: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    AudioSeq_ScriptReadU8(rdram, ctx);
        goto after_17;
    // 0x800BECE0: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_17:
    // 0x800BECE4: addiu       $at, $zero, 0xDD
    ctx->r1 = ADD32(0, 0XDD);
    // 0x800BECE8: bne         $s2, $at, L_800BED08
    if (ctx->r18 != ctx->r1) {
        // 0x800BECEC: lui         $v1, 0x8004
        ctx->r3 = S32(0X8004 << 16);
            goto L_800BED08;
    }
    // 0x800BECEC: lui         $v1, 0x8004
    ctx->r3 = S32(0X8004 << 16);
    // 0x800BECF0: andi        $t2, $v0, 0xFF
    ctx->r10 = ctx->r2 & 0XFF;
    // 0x800BECF4: sll         $t3, $t2, 2
    ctx->r11 = S32(ctx->r10 << 2);
    // 0x800BECF8: subu        $t3, $t3, $t2
    ctx->r11 = SUB32(ctx->r11, ctx->r10);
    // 0x800BECFC: sll         $t3, $t3, 4
    ctx->r11 = S32(ctx->r11 << 4);
    // 0x800BED00: b           L_800BED28
    // 0x800BED04: sh          $t3, 0x8($s1)
    MEM_H(0X8, ctx->r17) = ctx->r11;
        goto L_800BED28;
    // 0x800BED04: sh          $t3, 0x8($s1)
    MEM_H(0X8, ctx->r17) = ctx->r11;
L_800BED08:
    // 0x800BED08: sll         $t4, $v0, 24
    ctx->r12 = S32(ctx->r2 << 24);
    // 0x800BED0C: sra         $t5, $t4, 24
    ctx->r13 = S32(SIGNED(ctx->r12) >> 24);
    // 0x800BED10: lhu         $t6, 0x8($s1)
    ctx->r14 = MEM_HU(ctx->r17, 0X8);
    // 0x800BED14: sll         $t8, $t5, 2
    ctx->r24 = S32(ctx->r13 << 2);
    // 0x800BED18: subu        $t8, $t8, $t5
    ctx->r24 = SUB32(ctx->r24, ctx->r13);
    // 0x800BED1C: sll         $t8, $t8, 4
    ctx->r24 = S32(ctx->r24 << 4);
    // 0x800BED20: addu        $t9, $t6, $t8
    ctx->r25 = ADD32(ctx->r14, ctx->r24);
    // 0x800BED24: sh          $t9, 0x8($s1)
    MEM_H(0X8, ctx->r17) = ctx->r25;
L_800BED28:
    // 0x800BED28: lh          $v1, 0x554C($v1)
    ctx->r3 = MEM_H(ctx->r3, 0X554C);
    // 0x800BED2C: lhu         $v0, 0x8($s1)
    ctx->r2 = MEM_HU(ctx->r17, 0X8);
    // 0x800BED30: addiu       $t1, $zero, 0x1
    ctx->r9 = ADD32(0, 0X1);
    // 0x800BED34: slt         $at, $v1, $v0
    ctx->r1 = SIGNED(ctx->r3) < SIGNED(ctx->r2) ? 1 : 0;
    // 0x800BED38: beql        $at, $zero, L_800BED4C
    if (ctx->r1 == 0) {
        // 0x800BED3C: sll         $t7, $v0, 16
        ctx->r15 = S32(ctx->r2 << 16);
            goto L_800BED4C;
    }
    goto skip_9;
    // 0x800BED3C: sll         $t7, $v0, 16
    ctx->r15 = S32(ctx->r2 << 16);
    skip_9:
    // 0x800BED40: sh          $v1, 0x8($s1)
    MEM_H(0X8, ctx->r17) = ctx->r3;
    // 0x800BED44: andi        $v0, $v1, 0xFFFF
    ctx->r2 = ctx->r3 & 0XFFFF;
    // 0x800BED48: sll         $t7, $v0, 16
    ctx->r15 = S32(ctx->r2 << 16);
L_800BED4C:
    // 0x800BED4C: sra         $t0, $t7, 16
    ctx->r8 = S32(SIGNED(ctx->r15) >> 16);
    // 0x800BED50: bgtz        $t0, L_800BEA74
    if (SIGNED(ctx->r8) > 0) {
        // 0x800BED54: nop
    
            goto L_800BEA74;
    }
    // 0x800BED54: nop

    // 0x800BED58: b           L_800BEA74
    // 0x800BED5C: sh          $t1, 0x8($s1)
    MEM_H(0X8, ctx->r17) = ctx->r9;
        goto L_800BEA74;
    // 0x800BED5C: sh          $t1, 0x8($s1)
    MEM_H(0X8, ctx->r17) = ctx->r9;
L_800BED60:
    // 0x800BED60: jal         0x800BD0B0
    // 0x800BED64: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    AudioSeq_ScriptReadU8(rdram, ctx);
        goto after_18;
    // 0x800BED64: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_18:
    // 0x800BED68: andi        $s2, $v0, 0xFF
    ctx->r18 = ctx->r2 & 0XFF;
    // 0x800BED6C: jal         0x800BD0C4
    // 0x800BED70: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    AudioSeq_ScriptReadS16(rdram, ctx);
        goto after_19;
    // 0x800BED70: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_19:
    // 0x800BED74: beq         $s2, $zero, L_800BED98
    if (ctx->r18 == 0) {
        // 0x800BED78: or          $v1, $s2, $zero
        ctx->r3 = ctx->r18 | 0;
            goto L_800BED98;
    }
    // 0x800BED78: or          $v1, $s2, $zero
    ctx->r3 = ctx->r18 | 0;
    // 0x800BED7C: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x800BED80: beq         $v1, $at, L_800BED98
    if (ctx->r3 == ctx->r1) {
        // 0x800BED84: addiu       $at, $zero, 0x2
        ctx->r1 = ADD32(0, 0X2);
            goto L_800BED98;
    }
    // 0x800BED84: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x800BED88: beq         $v1, $at, L_800BEDB4
    if (ctx->r3 == ctx->r1) {
        // 0x800BED8C: andi        $t3, $v0, 0xFFFF
        ctx->r11 = ctx->r2 & 0XFFFF;
            goto L_800BEDB4;
    }
    // 0x800BED8C: andi        $t3, $v0, 0xFFFF
    ctx->r11 = ctx->r2 & 0XFFFF;
    // 0x800BED90: b           L_800BEA74
    // 0x800BED94: nop

        goto L_800BEA74;
    // 0x800BED94: nop

L_800BED98:
    // 0x800BED98: lbu         $t2, 0x1($s1)
    ctx->r10 = MEM_BU(ctx->r17, 0X1);
    // 0x800BED9C: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x800BEDA0: beq         $t2, $at, L_800BEA74
    if (ctx->r10 == ctx->r1) {
        // 0x800BEDA4: nop
    
            goto L_800BEA74;
    }
    // 0x800BEDA4: nop

    // 0x800BEDA8: sh          $v0, 0x12($s1)
    MEM_H(0X12, ctx->r17) = ctx->r2;
    // 0x800BEDAC: b           L_800BEA74
    // 0x800BEDB0: sb          $s2, 0x1($s1)
    MEM_B(0X1, ctx->r17) = ctx->r18;
        goto L_800BEA74;
    // 0x800BEDB0: sb          $s2, 0x1($s1)
    MEM_B(0X1, ctx->r17) = ctx->r18;
L_800BEDB4:
    // 0x800BEDB4: mtc1        $t3, $f10
    ctx->f10.u32l = ctx->r11;
    // 0x800BEDB8: mtc1        $zero, $f4
    ctx->f4.u32l = 0;
    // 0x800BEDBC: lwc1        $f6, 0x18($s1)
    ctx->f6.u32l = MEM_W(ctx->r17, 0X18);
    // 0x800BEDC0: cvt.s.w     $f16, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    ctx->f16.fl = CVT_S_W(ctx->f10.u32l);
    // 0x800BEDC4: sh          $v0, 0x10($s1)
    MEM_H(0X10, ctx->r17) = ctx->r2;
    // 0x800BEDC8: sb          $s2, 0x1($s1)
    MEM_B(0X1, ctx->r17) = ctx->r18;
    // 0x800BEDCC: sub.s       $f8, $f4, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = ctx->f4.fl - ctx->f6.fl;
    // 0x800BEDD0: div.s       $f18, $f8, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f18.fl = DIV_S(ctx->f8.fl, ctx->f16.fl);
    // 0x800BEDD4: b           L_800BEA74
    // 0x800BEDD8: swc1        $f18, 0x1C($s1)
    MEM_W(0X1C, ctx->r17) = ctx->f18.u32l;
        goto L_800BEA74;
    // 0x800BEDD8: swc1        $f18, 0x1C($s1)
    MEM_W(0X1C, ctx->r17) = ctx->f18.u32l;
L_800BEDDC:
    // 0x800BEDDC: jal         0x800BD0B0
    // 0x800BEDE0: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    AudioSeq_ScriptReadU8(rdram, ctx);
        goto after_20;
    // 0x800BEDE0: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_20:
    // 0x800BEDE4: lbu         $v1, 0x1($s1)
    ctx->r3 = MEM_BU(ctx->r17, 0X1);
    // 0x800BEDE8: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x800BEDEC: beql        $v1, $zero, L_800BEE1C
    if (ctx->r3 == 0) {
        // 0x800BEDF0: lhu         $v1, 0x12($s1)
        ctx->r3 = MEM_HU(ctx->r17, 0X12);
            goto L_800BEE1C;
    }
    goto skip_10;
    // 0x800BEDF0: lhu         $v1, 0x12($s1)
    ctx->r3 = MEM_HU(ctx->r17, 0X12);
    skip_10:
    // 0x800BEDF4: beq         $v1, $at, L_800BEE0C
    if (ctx->r3 == ctx->r1) {
        // 0x800BEDF8: addiu       $at, $zero, 0x2
        ctx->r1 = ADD32(0, 0X2);
            goto L_800BEE0C;
    }
    // 0x800BEDF8: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x800BEDFC: beq         $v1, $at, L_800BEA74
    if (ctx->r3 == ctx->r1) {
        // 0x800BEE00: nop
    
            goto L_800BEA74;
    }
    // 0x800BEE00: nop

    // 0x800BEE04: b           L_800BEA74
    // 0x800BEE08: nop

        goto L_800BEA74;
    // 0x800BEE08: nop

L_800BEE0C:
    // 0x800BEE0C: mtc1        $zero, $f4
    ctx->f4.u32l = 0;
    // 0x800BEE10: sb          $zero, 0x1($s1)
    MEM_B(0X1, ctx->r17) = 0;
    // 0x800BEE14: swc1        $f4, 0x18($s1)
    MEM_W(0X18, ctx->r17) = ctx->f4.u32l;
    // 0x800BEE18: lhu         $v1, 0x12($s1)
    ctx->r3 = MEM_HU(ctx->r17, 0X12);
L_800BEE1C:
    // 0x800BEE1C: beq         $v1, $zero, L_800BEE58
    if (ctx->r3 == 0) {
        // 0x800BEE20: sh          $v1, 0x10($s1)
        MEM_H(0X10, ctx->r17) = ctx->r3;
            goto L_800BEE58;
    }
    // 0x800BEE20: sh          $v1, 0x10($s1)
    MEM_H(0X10, ctx->r17) = ctx->r3;
    // 0x800BEE24: mtc1        $v0, $f6
    ctx->f6.u32l = ctx->r2;
    // 0x800BEE28: lui         $at, 0x42FE
    ctx->r1 = S32(0X42FE << 16);
    // 0x800BEE2C: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x800BEE30: cvt.s.w     $f10, $f6
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    ctx->f10.fl = CVT_S_W(ctx->f6.u32l);
    // 0x800BEE34: andi        $t4, $v1, 0xFFFF
    ctx->r12 = ctx->r3 & 0XFFFF;
    // 0x800BEE38: mtc1        $t4, $f6
    ctx->f6.u32l = ctx->r12;
    // 0x800BEE3C: lwc1        $f18, 0x18($s1)
    ctx->f18.u32l = MEM_W(ctx->r17, 0X18);
    // 0x800BEE40: div.s       $f16, $f10, $f8
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f16.fl = DIV_S(ctx->f10.fl, ctx->f8.fl);
    // 0x800BEE44: cvt.s.w     $f10, $f6
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    ctx->f10.fl = CVT_S_W(ctx->f6.u32l);
    // 0x800BEE48: sub.s       $f4, $f16, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f4.fl = ctx->f16.fl - ctx->f18.fl;
    // 0x800BEE4C: div.s       $f8, $f4, $f10
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f8.fl = DIV_S(ctx->f4.fl, ctx->f10.fl);
    // 0x800BEE50: b           L_800BEA74
    // 0x800BEE54: swc1        $f8, 0x1C($s1)
    MEM_W(0X1C, ctx->r17) = ctx->f8.u32l;
        goto L_800BEA74;
    // 0x800BEE54: swc1        $f8, 0x1C($s1)
    MEM_W(0X1C, ctx->r17) = ctx->f8.u32l;
L_800BEE58:
    // 0x800BEE58: mtc1        $v0, $f16
    ctx->f16.u32l = ctx->r2;
    // 0x800BEE5C: lui         $at, 0x42FE
    ctx->r1 = S32(0X42FE << 16);
    // 0x800BEE60: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x800BEE64: cvt.s.w     $f18, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    ctx->f18.fl = CVT_S_W(ctx->f16.u32l);
    // 0x800BEE68: div.s       $f4, $f18, $f6
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f4.fl = DIV_S(ctx->f18.fl, ctx->f6.fl);
    // 0x800BEE6C: b           L_800BEA74
    // 0x800BEE70: swc1        $f4, 0x18($s1)
    MEM_W(0X18, ctx->r17) = ctx->f4.u32l;
        goto L_800BEA74;
    // 0x800BEE70: swc1        $f4, 0x18($s1)
    MEM_W(0X18, ctx->r17) = ctx->f4.u32l;
L_800BEE74:
    // 0x800BEE74: jal         0x800BD0B0
    // 0x800BEE78: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    AudioSeq_ScriptReadU8(rdram, ctx);
        goto after_21;
    // 0x800BEE78: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_21:
    // 0x800BEE7C: sll         $t5, $v0, 24
    ctx->r13 = S32(ctx->r2 << 24);
    // 0x800BEE80: sra         $t6, $t5, 24
    ctx->r14 = S32(SIGNED(ctx->r13) >> 24);
    // 0x800BEE84: mtc1        $t6, $f10
    ctx->f10.u32l = ctx->r14;
    // 0x800BEE88: lui         $at, 0x42FE
    ctx->r1 = S32(0X42FE << 16);
    // 0x800BEE8C: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
    // 0x800BEE90: cvt.s.w     $f8, $f10
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    ctx->f8.fl = CVT_S_W(ctx->f10.u32l);
    // 0x800BEE94: div.s       $f18, $f8, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f18.fl = DIV_S(ctx->f8.fl, ctx->f16.fl);
    // 0x800BEE98: b           L_800BEA74
    // 0x800BEE9C: swc1        $f18, 0x28($s1)
    MEM_W(0X28, ctx->r17) = ctx->f18.u32l;
        goto L_800BEA74;
    // 0x800BEE9C: swc1        $f18, 0x28($s1)
    MEM_W(0X28, ctx->r17) = ctx->f18.u32l;
L_800BEEA0:
    // 0x800BEEA0: jal         0x800BD0C4
    // 0x800BEEA4: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    AudioSeq_ScriptReadS16(rdram, ctx);
        goto after_22;
    // 0x800BEEA4: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_22:
    // 0x800BEEA8: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    // 0x800BEEAC: jal         0x800BCC1C
    // 0x800BEEB0: andi        $a1, $v0, 0xFFFF
    ctx->r5 = ctx->r2 & 0XFFFF;
    AudioSeq_SequencePlayerSetupChannels(rdram, ctx);
        goto after_23;
    // 0x800BEEB0: andi        $a1, $v0, 0xFFFF
    ctx->r5 = ctx->r2 & 0XFFFF;
    after_23:
    // 0x800BEEB4: b           L_800BEA74
    // 0x800BEEB8: nop

        goto L_800BEA74;
    // 0x800BEEB8: nop

L_800BEEBC:
    // 0x800BEEBC: jal         0x800BD0C4
    // 0x800BEEC0: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    AudioSeq_ScriptReadS16(rdram, ctx);
        goto after_24;
    // 0x800BEEC0: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_24:
    // 0x800BEEC4: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    // 0x800BEEC8: jal         0x800BCD48
    // 0x800BEECC: andi        $a1, $v0, 0xFFFF
    ctx->r5 = ctx->r2 & 0XFFFF;
    AudioSeq_SequencePlayerDisableChannels(rdram, ctx);
        goto after_25;
    // 0x800BEECC: andi        $a1, $v0, 0xFFFF
    ctx->r5 = ctx->r2 & 0XFFFF;
    after_25:
    // 0x800BEED0: b           L_800BEA74
    // 0x800BEED4: nop

        goto L_800BEA74;
    // 0x800BEED4: nop

L_800BEED8:
    // 0x800BEED8: jal         0x800BD0B0
    // 0x800BEEDC: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    AudioSeq_ScriptReadU8(rdram, ctx);
        goto after_26;
    // 0x800BEEDC: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_26:
    // 0x800BEEE0: sll         $t8, $v0, 24
    ctx->r24 = S32(ctx->r2 << 24);
    // 0x800BEEE4: sra         $t9, $t8, 24
    ctx->r25 = S32(SIGNED(ctx->r24) >> 24);
    // 0x800BEEE8: mtc1        $t9, $f6
    ctx->f6.u32l = ctx->r25;
    // 0x800BEEEC: lui         $at, 0x42FE
    ctx->r1 = S32(0X42FE << 16);
    // 0x800BEEF0: mtc1        $at, $f10
    ctx->f10.u32l = ctx->r1;
    // 0x800BEEF4: cvt.s.w     $f4, $f6
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    ctx->f4.fl = CVT_S_W(ctx->f6.u32l);
    // 0x800BEEF8: div.s       $f8, $f4, $f10
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f8.fl = DIV_S(ctx->f4.fl, ctx->f10.fl);
    // 0x800BEEFC: b           L_800BEA74
    // 0x800BEF00: swc1        $f8, 0x24($s1)
    MEM_W(0X24, ctx->r17) = ctx->f8.u32l;
        goto L_800BEA74;
    // 0x800BEF00: swc1        $f8, 0x24($s1)
    MEM_W(0X24, ctx->r17) = ctx->f8.u32l;
L_800BEF04:
    // 0x800BEF04: lbu         $t0, 0x0($s1)
    ctx->r8 = MEM_BU(ctx->r17, 0X0);
    // 0x800BEF08: ori         $t1, $t0, 0x20
    ctx->r9 = ctx->r8 | 0X20;
    // 0x800BEF0C: b           L_800BEA74
    // 0x800BEF10: sb          $t1, 0x0($s1)
    MEM_B(0X0, ctx->r17) = ctx->r9;
        goto L_800BEA74;
    // 0x800BEF10: sb          $t1, 0x0($s1)
    MEM_B(0X0, ctx->r17) = ctx->r9;
L_800BEF14:
    // 0x800BEF14: jal         0x800BD0B0
    // 0x800BEF18: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    AudioSeq_ScriptReadU8(rdram, ctx);
        goto after_27;
    // 0x800BEF18: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_27:
    // 0x800BEF1C: b           L_800BEA74
    // 0x800BEF20: sb          $v0, 0x3($s1)
    MEM_B(0X3, ctx->r17) = ctx->r2;
        goto L_800BEA74;
    // 0x800BEF20: sb          $v0, 0x3($s1)
    MEM_B(0X3, ctx->r17) = ctx->r2;
L_800BEF24:
    // 0x800BEF24: jal         0x800BD0C4
    // 0x800BEF28: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    AudioSeq_ScriptReadS16(rdram, ctx);
        goto after_28;
    // 0x800BEF28: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_28:
    // 0x800BEF2C: lw          $t2, 0x14($s1)
    ctx->r10 = MEM_W(ctx->r17, 0X14);
    // 0x800BEF30: andi        $t3, $v0, 0xFFFF
    ctx->r11 = ctx->r2 & 0XFFFF;
    // 0x800BEF34: addiu       $at, $zero, 0xD2
    ctx->r1 = ADD32(0, 0XD2);
    // 0x800BEF38: bne         $s2, $at, L_800BEF48
    if (ctx->r18 != ctx->r1) {
        // 0x800BEF3C: addu        $v1, $t2, $t3
        ctx->r3 = ADD32(ctx->r10, ctx->r11);
            goto L_800BEF48;
    }
    // 0x800BEF3C: addu        $v1, $t2, $t3
    ctx->r3 = ADD32(ctx->r10, ctx->r11);
    // 0x800BEF40: b           L_800BEA74
    // 0x800BEF44: sw          $v1, 0x8C($s1)
    MEM_W(0X8C, ctx->r17) = ctx->r3;
        goto L_800BEA74;
    // 0x800BEF44: sw          $v1, 0x8C($s1)
    MEM_W(0X8C, ctx->r17) = ctx->r3;
L_800BEF48:
    // 0x800BEF48: b           L_800BEA74
    // 0x800BEF4C: sw          $v1, 0x90($s1)
    MEM_W(0X90, ctx->r17) = ctx->r3;
        goto L_800BEA74;
    // 0x800BEF4C: sw          $v1, 0x90($s1)
    MEM_W(0X90, ctx->r17) = ctx->r3;
L_800BEF50:
    // 0x800BEF50: jal         0x800BD0B0
    // 0x800BEF54: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    AudioSeq_ScriptReadU8(rdram, ctx);
        goto after_29;
    // 0x800BEF54: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_29:
    // 0x800BEF58: b           L_800BEA74
    // 0x800BEF5C: sb          $v0, 0x2($s1)
    MEM_B(0X2, ctx->r17) = ctx->r2;
        goto L_800BEA74;
    // 0x800BEF5C: sb          $v0, 0x2($s1)
    MEM_B(0X2, ctx->r17) = ctx->r2;
L_800BEF60:
    // 0x800BEF60: jal         0x800BD0B0
    // 0x800BEF64: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    AudioSeq_ScriptReadU8(rdram, ctx);
        goto after_30;
    // 0x800BEF64: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_30:
    // 0x800BEF68: b           L_800BEA74
    // 0x800BEF6C: or          $s3, $v0, $zero
    ctx->r19 = ctx->r2 | 0;
        goto L_800BEA74;
    // 0x800BEF6C: or          $s3, $v0, $zero
    ctx->r19 = ctx->r2 | 0;
L_800BEF70:
    // 0x800BEF70: jal         0x800BD0B0
    // 0x800BEF74: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    AudioSeq_ScriptReadU8(rdram, ctx);
        goto after_31;
    // 0x800BEF74: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_31:
    // 0x800BEF78: b           L_800BEA74
    // 0x800BEF7C: and         $s3, $s3, $v0
    ctx->r19 = ctx->r19 & ctx->r2;
        goto L_800BEA74;
    // 0x800BEF7C: and         $s3, $s3, $v0
    ctx->r19 = ctx->r19 & ctx->r2;
L_800BEF80:
    // 0x800BEF80: jal         0x800BD0B0
    // 0x800BEF84: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    AudioSeq_ScriptReadU8(rdram, ctx);
        goto after_32;
    // 0x800BEF84: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_32:
    // 0x800BEF88: b           L_800BEA74
    // 0x800BEF8C: subu        $s3, $s3, $v0
    ctx->r19 = SUB32(ctx->r19, ctx->r2);
        goto L_800BEA74;
    // 0x800BEF8C: subu        $s3, $s3, $v0
    ctx->r19 = SUB32(ctx->r19, ctx->r2);
L_800BEF90:
    // 0x800BEF90: slti        $at, $v0, 0x11
    ctx->r1 = SIGNED(ctx->r2) < 0X11 ? 1 : 0;
    // 0x800BEF94: bne         $at, $zero, L_800BEFD8
    if (ctx->r1 != 0) {
        // 0x800BEF98: slti        $at, $v0, 0x21
        ctx->r1 = SIGNED(ctx->r2) < 0X21 ? 1 : 0;
            goto L_800BEFD8;
    }
    // 0x800BEF98: slti        $at, $v0, 0x21
    ctx->r1 = SIGNED(ctx->r2) < 0X21 ? 1 : 0;
    // 0x800BEF9C: bne         $at, $zero, L_800BEFC4
    if (ctx->r1 != 0) {
        // 0x800BEFA0: addiu       $t4, $v0, -0x40
        ctx->r12 = ADD32(ctx->r2, -0X40);
            goto L_800BEFC4;
    }
    // 0x800BEFA0: addiu       $t4, $v0, -0x40
    ctx->r12 = ADD32(ctx->r2, -0X40);
    // 0x800BEFA4: sltiu       $at, $t4, 0x61
    ctx->r1 = ctx->r12 < 0X61 ? 1 : 0;
    // 0x800BEFA8: beq         $at, $zero, L_800BEA74
    if (ctx->r1 == 0) {
        // 0x800BEFAC: sll         $t4, $t4, 2
        ctx->r12 = S32(ctx->r12 << 2);
            goto L_800BEA74;
    }
    // 0x800BEFAC: sll         $t4, $t4, 2
    ctx->r12 = S32(ctx->r12 << 2);
    // 0x800BEFB0: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x800BEFB4: addu        $at, $at, $t4
    gpr jr_addend_800BEFBC = ctx->r12;
    ctx->r1 = ADD32(ctx->r1, ctx->r12);
    // 0x800BEFB8: lw          $t4, -0x3E2C($at)
    ctx->r12 = ADD32(ctx->r1, -0X3E2C);
    // 0x800BEFBC: jr          $t4
    // 0x800BEFC0: nop

    switch (jr_addend_800BEFBC >> 2) {
        case 0: goto L_800BEA74; break;
        case 1: goto L_800BEA74; break;
        case 2: goto L_800BEA74; break;
        case 3: goto L_800BEA74; break;
        case 4: goto L_800BEA74; break;
        case 5: goto L_800BEA74; break;
        case 6: goto L_800BEA74; break;
        case 7: goto L_800BEA74; break;
        case 8: goto L_800BEA74; break;
        case 9: goto L_800BEA74; break;
        case 10: goto L_800BEA74; break;
        case 11: goto L_800BEA74; break;
        case 12: goto L_800BEA74; break;
        case 13: goto L_800BEA74; break;
        case 14: goto L_800BEA74; break;
        case 15: goto L_800BEA74; break;
        case 16: goto L_800BF010; break;
        case 17: goto L_800BEA74; break;
        case 18: goto L_800BEA74; break;
        case 19: goto L_800BEA74; break;
        case 20: goto L_800BEA74; break;
        case 21: goto L_800BEA74; break;
        case 22: goto L_800BEA74; break;
        case 23: goto L_800BEA74; break;
        case 24: goto L_800BEA74; break;
        case 25: goto L_800BEA74; break;
        case 26: goto L_800BEA74; break;
        case 27: goto L_800BEA74; break;
        case 28: goto L_800BEA74; break;
        case 29: goto L_800BEA74; break;
        case 30: goto L_800BEA74; break;
        case 31: goto L_800BEA74; break;
        case 32: goto L_800BEA74; break;
        case 33: goto L_800BEA74; break;
        case 34: goto L_800BEA74; break;
        case 35: goto L_800BEA74; break;
        case 36: goto L_800BEA74; break;
        case 37: goto L_800BEA74; break;
        case 38: goto L_800BEA74; break;
        case 39: goto L_800BEA74; break;
        case 40: goto L_800BEA74; break;
        case 41: goto L_800BEA74; break;
        case 42: goto L_800BEA74; break;
        case 43: goto L_800BEA74; break;
        case 44: goto L_800BEA74; break;
        case 45: goto L_800BEA74; break;
        case 46: goto L_800BEA74; break;
        case 47: goto L_800BEA74; break;
        case 48: goto L_800BF01C; break;
        case 49: goto L_800BEA74; break;
        case 50: goto L_800BEA74; break;
        case 51: goto L_800BEA74; break;
        case 52: goto L_800BEA74; break;
        case 53: goto L_800BEA74; break;
        case 54: goto L_800BEA74; break;
        case 55: goto L_800BEA74; break;
        case 56: goto L_800BEA74; break;
        case 57: goto L_800BEA74; break;
        case 58: goto L_800BEA74; break;
        case 59: goto L_800BEA74; break;
        case 60: goto L_800BEA74; break;
        case 61: goto L_800BEA74; break;
        case 62: goto L_800BEA74; break;
        case 63: goto L_800BEA74; break;
        case 64: goto L_800BF024; break;
        case 65: goto L_800BEA74; break;
        case 66: goto L_800BEA74; break;
        case 67: goto L_800BEA74; break;
        case 68: goto L_800BEA74; break;
        case 69: goto L_800BEA74; break;
        case 70: goto L_800BEA74; break;
        case 71: goto L_800BEA74; break;
        case 72: goto L_800BEA74; break;
        case 73: goto L_800BEA74; break;
        case 74: goto L_800BEA74; break;
        case 75: goto L_800BEA74; break;
        case 76: goto L_800BEA74; break;
        case 77: goto L_800BEA74; break;
        case 78: goto L_800BEA74; break;
        case 79: goto L_800BEA74; break;
        case 80: goto L_800BF02C; break;
        case 81: goto L_800BEA74; break;
        case 82: goto L_800BEA74; break;
        case 83: goto L_800BEA74; break;
        case 84: goto L_800BEA74; break;
        case 85: goto L_800BEA74; break;
        case 86: goto L_800BEA74; break;
        case 87: goto L_800BEA74; break;
        case 88: goto L_800BEA74; break;
        case 89: goto L_800BEA74; break;
        case 90: goto L_800BEA74; break;
        case 91: goto L_800BEA74; break;
        case 92: goto L_800BEA74; break;
        case 93: goto L_800BEA74; break;
        case 94: goto L_800BEA74; break;
        case 95: goto L_800BEA74; break;
        case 96: goto L_800BEA74; break;
        default: switch_error(__func__, 0x800BEFBC, 0x800EC1D4);
    }
    // 0x800BEFC0: nop

L_800BEFC4:
    // 0x800BEFC4: addiu       $at, $zero, 0x20
    ctx->r1 = ADD32(0, 0X20);
    // 0x800BEFC8: beq         $v0, $at, L_800BEA74
    if (ctx->r2 == ctx->r1) {
        // 0x800BEFCC: nop
    
            goto L_800BEA74;
    }
    // 0x800BEFCC: nop

    // 0x800BEFD0: b           L_800BEA74
    // 0x800BEFD4: nop

        goto L_800BEA74;
    // 0x800BEFD4: nop

L_800BEFD8:
    // 0x800BEFD8: beq         $v0, $zero, L_800BEFF4
    if (ctx->r2 == 0) {
        // 0x800BEFDC: andi        $t6, $v1, 0xF
        ctx->r14 = ctx->r3 & 0XF;
            goto L_800BEFF4;
    }
    // 0x800BEFDC: andi        $t6, $v1, 0xF
    ctx->r14 = ctx->r3 & 0XF;
    // 0x800BEFE0: addiu       $at, $zero, 0x10
    ctx->r1 = ADD32(0, 0X10);
    // 0x800BEFE4: beq         $v0, $at, L_800BEA74
    if (ctx->r2 == ctx->r1) {
        // 0x800BEFE8: nop
    
            goto L_800BEA74;
    }
    // 0x800BEFE8: nop

    // 0x800BEFEC: b           L_800BEA74
    // 0x800BEFF0: nop

        goto L_800BEA74;
    // 0x800BEFF0: nop

L_800BEFF4:
    // 0x800BEFF4: sll         $t8, $t6, 2
    ctx->r24 = S32(ctx->r14 << 2);
    // 0x800BEFF8: addu        $t9, $s1, $t8
    ctx->r25 = ADD32(ctx->r17, ctx->r24);
    // 0x800BEFFC: lw          $t7, 0x30($t9)
    ctx->r15 = MEM_W(ctx->r25, 0X30);
    // 0x800BF000: lw          $s3, 0x0($t7)
    ctx->r19 = MEM_W(ctx->r15, 0X0);
    // 0x800BF004: sll         $t0, $s3, 1
    ctx->r8 = S32(ctx->r19 << 1);
    // 0x800BF008: b           L_800BEA74
    // 0x800BF00C: srl         $s3, $t0, 31
    ctx->r19 = S32(U32(ctx->r8) >> 31);
        goto L_800BEA74;
    // 0x800BF00C: srl         $s3, $t0, 31
    ctx->r19 = S32(U32(ctx->r8) >> 31);
L_800BF010:
    // 0x800BF010: lb          $t2, 0x7($s1)
    ctx->r10 = MEM_B(ctx->r17, 0X7);
    // 0x800BF014: b           L_800BEA74
    // 0x800BF018: subu        $s3, $s3, $t2
    ctx->r19 = SUB32(ctx->r19, ctx->r10);
        goto L_800BEA74;
    // 0x800BF018: subu        $s3, $s3, $t2
    ctx->r19 = SUB32(ctx->r19, ctx->r10);
L_800BF01C:
    // 0x800BF01C: b           L_800BEA74
    // 0x800BF020: sb          $s3, 0x7($s1)
    MEM_B(0X7, ctx->r17) = ctx->r19;
        goto L_800BEA74;
    // 0x800BF020: sb          $s3, 0x7($s1)
    MEM_B(0X7, ctx->r17) = ctx->r19;
L_800BF024:
    // 0x800BF024: b           L_800BEA74
    // 0x800BF028: lb          $s3, 0x7($s1)
    ctx->r19 = MEM_B(ctx->r17, 0X7);
        goto L_800BEA74;
    // 0x800BF028: lb          $s3, 0x7($s1)
    ctx->r19 = MEM_B(ctx->r17, 0X7);
L_800BF02C:
    // 0x800BF02C: jal         0x800BD0C4
    // 0x800BF030: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    AudioSeq_ScriptReadS16(rdram, ctx);
        goto after_33;
    // 0x800BF030: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_33:
    // 0x800BF034: lw          $t4, 0x14($s1)
    ctx->r12 = MEM_W(ctx->r17, 0X14);
    // 0x800BF038: or          $a1, $s2, $zero
    ctx->r5 = ctx->r18 | 0;
    // 0x800BF03C: andi        $t3, $a1, 0xF
    ctx->r11 = ctx->r5 & 0XF;
    // 0x800BF040: andi        $t5, $v0, 0xFFFF
    ctx->r13 = ctx->r2 & 0XFFFF;
    // 0x800BF044: or          $a1, $t3, $zero
    ctx->r5 = ctx->r11 | 0;
    // 0x800BF048: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    // 0x800BF04C: jal         0x800BCE18
    // 0x800BF050: addu        $a2, $t4, $t5
    ctx->r6 = ADD32(ctx->r12, ctx->r13);
    AudioSeq_SequenceChannelEnable(rdram, ctx);
        goto after_34;
    // 0x800BF050: addu        $a2, $t4, $t5
    ctx->r6 = ADD32(ctx->r12, ctx->r13);
    after_34:
    // 0x800BF054: b           L_800BEA74
    // 0x800BF058: nop

        goto L_800BEA74;
    // 0x800BF058: nop

L_800BF05C:
    // 0x800BF05C: lui         $s0, 0x8004
    ctx->r16 = S32(0X8004 << 16);
    // 0x800BF060: or          $v1, $s1, $zero
    ctx->r3 = ctx->r17 | 0;
    // 0x800BF064: addiu       $s1, $zero, 0x40
    ctx->r17 = ADD32(0, 0X40);
    // 0x800BF068: addiu       $s0, $s0, 0x4688
    ctx->r16 = ADD32(ctx->r16, 0X4688);
    // 0x800BF06C: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_800BF070:
    // 0x800BF070: lw          $a0, 0x30($v1)
    ctx->r4 = MEM_W(ctx->r3, 0X30);
    // 0x800BF074: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x800BF078: xor         $t6, $s0, $a0
    ctx->r14 = ctx->r16 ^ ctx->r4;
    // 0x800BF07C: sltu        $t6, $zero, $t6
    ctx->r14 = 0 < ctx->r14 ? 1 : 0;
    // 0x800BF080: bnel        $t6, $at, L_800BF0A0
    if (ctx->r14 != ctx->r1) {
        // 0x800BF084: addiu       $v0, $v0, 0x4
        ctx->r2 = ADD32(ctx->r2, 0X4);
            goto L_800BF0A0;
    }
    goto skip_11;
    // 0x800BF084: addiu       $v0, $v0, 0x4
    ctx->r2 = ADD32(ctx->r2, 0X4);
    skip_11:
    // 0x800BF088: sw          $v0, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r2;
    // 0x800BF08C: jal         0x800BDD14
    // 0x800BF090: sw          $v1, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r3;
    AudioSeq_SequenceChannelProcessScript(rdram, ctx);
        goto after_35;
    // 0x800BF090: sw          $v1, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r3;
    after_35:
    // 0x800BF094: lw          $v0, 0x34($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X34);
    // 0x800BF098: lw          $v1, 0x30($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X30);
    // 0x800BF09C: addiu       $v0, $v0, 0x4
    ctx->r2 = ADD32(ctx->r2, 0X4);
L_800BF0A0:
    // 0x800BF0A0: bne         $v0, $s1, L_800BF070
    if (ctx->r2 != ctx->r17) {
        // 0x800BF0A4: addiu       $v1, $v1, 0x4
        ctx->r3 = ADD32(ctx->r3, 0X4);
            goto L_800BF070;
    }
    // 0x800BF0A4: addiu       $v1, $v1, 0x4
    ctx->r3 = ADD32(ctx->r3, 0X4);
L_800BF0A8:
    // 0x800BF0A8: lw          $ra, 0x2C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X2C);
L_800BF0AC:
    // 0x800BF0AC: lw          $s0, 0x1C($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X1C);
    // 0x800BF0B0: lw          $s1, 0x20($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X20);
    // 0x800BF0B4: lw          $s2, 0x24($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X24);
    // 0x800BF0B8: lw          $s3, 0x28($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X28);
    // 0x800BF0BC: jr          $ra
    // 0x800BF0C0: addiu       $sp, $sp, 0x60
    ctx->r29 = ADD32(ctx->r29, 0X60);
    return;
    // 0x800BF0C0: addiu       $sp, $sp, 0x60
    ctx->r29 = ADD32(ctx->r29, 0X60);
;}
RECOMP_FUNC void AudioSeq_ProcessSequences(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800BF0C4: addiu       $sp, $sp, -0x28
    ctx->r29 = ADD32(ctx->r29, -0X28);
    // 0x800BF0C8: sw          $s2, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r18;
    // 0x800BF0CC: sw          $s0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r16;
    // 0x800BF0D0: sw          $s1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r17;
    // 0x800BF0D4: lui         $s0, 0x8004
    ctx->r16 = S32(0X8004 << 16);
    // 0x800BF0D8: lui         $s2, 0x8004
    ctx->r18 = S32(0X8004 << 16);
    // 0x800BF0DC: sw          $ra, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r31;
    // 0x800BF0E0: sw          $a0, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r4;
    // 0x800BF0E4: addiu       $s2, $s2, 0x1C8
    ctx->r18 = ADD32(ctx->r18, 0X1C8);
    // 0x800BF0E8: addiu       $s0, $s0, -0x338
    ctx->r16 = ADD32(ctx->r16, -0X338);
    // 0x800BF0EC: addiu       $s1, $zero, 0x1
    ctx->r17 = ADD32(0, 0X1);
    // 0x800BF0F0: lw          $t6, 0x0($s0)
    ctx->r14 = MEM_W(ctx->r16, 0X0);
L_800BF0F4:
    // 0x800BF0F4: srl         $t7, $t6, 31
    ctx->r15 = S32(U32(ctx->r14) >> 31);
    // 0x800BF0F8: bnel        $s1, $t7, L_800BF114
    if (ctx->r17 != ctx->r15) {
        // 0x800BF0FC: addiu       $s0, $s0, 0x140
        ctx->r16 = ADD32(ctx->r16, 0X140);
            goto L_800BF114;
    }
    goto skip_0;
    // 0x800BF0FC: addiu       $s0, $s0, 0x140
    ctx->r16 = ADD32(ctx->r16, 0X140);
    skip_0:
    // 0x800BF100: jal         0x800BE858
    // 0x800BF104: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    AudioSeq_SequencePlayerProcessSequence(rdram, ctx);
        goto after_0;
    // 0x800BF104: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_0:
    // 0x800BF108: jal         0x800BBFD4
    // 0x800BF10C: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    Audio_SequencePlayerProcessSound(rdram, ctx);
        goto after_1;
    // 0x800BF10C: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_1:
    // 0x800BF110: addiu       $s0, $s0, 0x140
    ctx->r16 = ADD32(ctx->r16, 0X140);
L_800BF114:
    // 0x800BF114: bnel        $s0, $s2, L_800BF0F4
    if (ctx->r16 != ctx->r18) {
        // 0x800BF118: lw          $t6, 0x0($s0)
        ctx->r14 = MEM_W(ctx->r16, 0X0);
            goto L_800BF0F4;
    }
    goto skip_1;
    // 0x800BF118: lw          $t6, 0x0($s0)
    ctx->r14 = MEM_W(ctx->r16, 0X0);
    skip_1:
    // 0x800BF11C: jal         0x800BAB94
    // 0x800BF120: nop

    Audio_ProcessNotes(rdram, ctx);
        goto after_2;
    // 0x800BF120: nop

    after_2:
    // 0x800BF124: lw          $ra, 0x24($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X24);
    // 0x800BF128: lw          $s0, 0x18($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X18);
    // 0x800BF12C: lw          $s1, 0x1C($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X1C);
    // 0x800BF130: lw          $s2, 0x20($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X20);
    // 0x800BF134: jr          $ra
    // 0x800BF138: addiu       $sp, $sp, 0x28
    ctx->r29 = ADD32(ctx->r29, 0X28);
    return;
    // 0x800BF138: addiu       $sp, $sp, 0x28
    ctx->r29 = ADD32(ctx->r29, 0X28);
;}
RECOMP_FUNC void AudioSeq_ResetSequencePlayer(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800BF13C: sll         $t6, $a0, 2
    ctx->r14 = S32(ctx->r4 << 2);
    // 0x800BF140: addu        $t6, $t6, $a0
    ctx->r14 = ADD32(ctx->r14, ctx->r4);
    // 0x800BF144: lui         $t7, 0x8004
    ctx->r15 = S32(0X8004 << 16);
    // 0x800BF148: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x800BF14C: addiu       $t7, $t7, -0x338
    ctx->r15 = ADD32(ctx->r15, -0X338);
    // 0x800BF150: sll         $t6, $t6, 6
    ctx->r14 = S32(ctx->r14 << 6);
    // 0x800BF154: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800BF158: addu        $a0, $t6, $t7
    ctx->r4 = ADD32(ctx->r14, ctx->r15);
    // 0x800BF15C: jal         0x800BCEE0
    // 0x800BF160: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    AudioSeq_SequencePlayerDisable(rdram, ctx);
        goto after_0;
    // 0x800BF160: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    after_0:
    // 0x800BF164: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
    // 0x800BF168: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x800BF16C: mtc1        $at, $f0
    ctx->f0.u32l = ctx->r1;
    // 0x800BF170: mtc1        $zero, $f2
    ctx->f2.u32l = 0;
    // 0x800BF174: lbu         $t8, 0x0($a0)
    ctx->r24 = MEM_BU(ctx->r4, 0X0);
    // 0x800BF178: lui         $at, 0x3F00
    ctx->r1 = S32(0X3F00 << 16);
    // 0x800BF17C: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x800BF180: lui         $t3, 0x800F
    ctx->r11 = S32(0X800F << 16);
    // 0x800BF184: lui         $t4, 0x800F
    ctx->r12 = S32(0X800F << 16);
    // 0x800BF188: addiu       $t0, $zero, 0x1
    ctx->r8 = ADD32(0, 0X1);
    // 0x800BF18C: addiu       $t1, $zero, 0x1680
    ctx->r9 = ADD32(0, 0X1680);
    // 0x800BF190: addiu       $t2, $zero, 0xE0
    ctx->r10 = ADD32(0, 0XE0);
    // 0x800BF194: addiu       $t3, $t3, -0x301C
    ctx->r11 = ADD32(ctx->r11, -0X301C);
    // 0x800BF198: addiu       $t4, $t4, -0x300C
    ctx->r12 = ADD32(ctx->r12, -0X300C);
    // 0x800BF19C: andi        $t9, $t8, 0xFFDF
    ctx->r25 = ctx->r24 & 0XFFDF;
    // 0x800BF1A0: sb          $t9, 0x0($a0)
    MEM_B(0X0, ctx->r4) = ctx->r25;
    // 0x800BF1A4: sh          $zero, 0xE($a0)
    MEM_H(0XE, ctx->r4) = 0;
    // 0x800BF1A8: sb          $t0, 0x1($a0)
    MEM_B(0X1, ctx->r4) = ctx->r8;
    // 0x800BF1AC: sh          $zero, 0x10($a0)
    MEM_H(0X10, ctx->r4) = 0;
    // 0x800BF1B0: sh          $zero, 0x12($a0)
    MEM_H(0X12, ctx->r4) = 0;
    // 0x800BF1B4: sh          $zero, 0xA($a0)
    MEM_H(0XA, ctx->r4) = 0;
    // 0x800BF1B8: sh          $t1, 0x8($a0)
    MEM_H(0X8, ctx->r4) = ctx->r9;
    // 0x800BF1BC: sh          $zero, 0xC($a0)
    MEM_H(0XC, ctx->r4) = 0;
    // 0x800BF1C0: sb          $t2, 0x3($a0)
    MEM_B(0X3, ctx->r4) = ctx->r10;
    // 0x800BF1C4: sb          $zero, 0x2($a0)
    MEM_B(0X2, ctx->r4) = 0;
    // 0x800BF1C8: sw          $t3, 0x8C($a0)
    MEM_W(0X8C, ctx->r4) = ctx->r11;
    // 0x800BF1CC: sw          $t4, 0x90($a0)
    MEM_W(0X90, ctx->r4) = ctx->r12;
    // 0x800BF1D0: swc1        $f0, 0x18($a0)
    MEM_W(0X18, ctx->r4) = ctx->f0.u32l;
    // 0x800BF1D4: swc1        $f0, 0x28($a0)
    MEM_W(0X28, ctx->r4) = ctx->f0.u32l;
    // 0x800BF1D8: swc1        $f2, 0x1C($a0)
    MEM_W(0X1C, ctx->r4) = ctx->f2.u32l;
    // 0x800BF1DC: swc1        $f2, 0x20($a0)
    MEM_W(0X20, ctx->r4) = ctx->f2.u32l;
    // 0x800BF1E0: swc1        $f4, 0x24($a0)
    MEM_W(0X24, ctx->r4) = ctx->f4.u32l;
    // 0x800BF1E4: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800BF1E8: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x800BF1EC: jr          $ra
    // 0x800BF1F0: nop

    return;
    // 0x800BF1F0: nop

;}
RECOMP_FUNC void AudioSeq_InitSequencePlayers(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800BF1F4: addiu       $sp, $sp, -0x38
    ctx->r29 = ADD32(ctx->r29, -0X38);
    // 0x800BF1F8: lui         $t6, 0x8004
    ctx->r14 = S32(0X8004 << 16);
    // 0x800BF1FC: addiu       $a2, $t6, 0x1C8
    ctx->r6 = ADD32(ctx->r14, 0X1C8);
    // 0x800BF200: lui         $a3, 0x8004
    ctx->r7 = S32(0X8004 << 16);
    // 0x800BF204: sw          $ra, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r31;
    // 0x800BF208: sw          $s7, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r23;
    // 0x800BF20C: sw          $s6, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r22;
    // 0x800BF210: sw          $s5, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r21;
    // 0x800BF214: sw          $s4, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r20;
    // 0x800BF218: sw          $s3, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r19;
    // 0x800BF21C: sw          $s2, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r18;
    // 0x800BF220: sw          $s1, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r17;
    // 0x800BF224: sw          $s0, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r16;
    // 0x800BF228: addiu       $a3, $a3, 0x2688
    ctx->r7 = ADD32(ctx->r7, 0X2688);
    // 0x800BF22C: or          $a1, $a2, $zero
    ctx->r5 = ctx->r6 | 0;
    // 0x800BF230: addiu       $a0, $zero, 0x40
    ctx->r4 = ADD32(0, 0X40);
L_800BF234:
    // 0x800BF234: lbu         $t7, 0x0($a1)
    ctx->r15 = MEM_BU(ctx->r5, 0X0);
    // 0x800BF238: sw          $zero, 0x44($a1)
    MEM_W(0X44, ctx->r5) = 0;
    // 0x800BF23C: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    // 0x800BF240: andi        $t8, $t7, 0xFF7F
    ctx->r24 = ctx->r15 & 0XFF7F;
    // 0x800BF244: sb          $t8, 0x0($a1)
    MEM_B(0X0, ctx->r5) = ctx->r24;
    // 0x800BF248: or          $v1, $a2, $zero
    ctx->r3 = ctx->r6 | 0;
L_800BF24C:
    // 0x800BF24C: addiu       $v0, $v0, 0x4
    ctx->r2 = ADD32(ctx->r2, 0X4);
    // 0x800BF250: sw          $zero, 0x4C($v1)
    MEM_W(0X4C, ctx->r3) = 0;
    // 0x800BF254: sw          $zero, 0x50($v1)
    MEM_W(0X50, ctx->r3) = 0;
    // 0x800BF258: sw          $zero, 0x54($v1)
    MEM_W(0X54, ctx->r3) = 0;
    // 0x800BF25C: addiu       $v1, $v1, 0x10
    ctx->r3 = ADD32(ctx->r3, 0X10);
    // 0x800BF260: bne         $v0, $a0, L_800BF24C
    if (ctx->r2 != ctx->r4) {
        // 0x800BF264: sw          $zero, 0x38($v1)
        MEM_W(0X38, ctx->r3) = 0;
            goto L_800BF24C;
    }
    // 0x800BF264: sw          $zero, 0x38($v1)
    MEM_W(0X38, ctx->r3) = 0;
    // 0x800BF268: addiu       $a2, $a2, 0xC4
    ctx->r6 = ADD32(ctx->r6, 0XC4);
    // 0x800BF26C: sltu        $at, $a2, $a3
    ctx->r1 = ctx->r6 < ctx->r7 ? 1 : 0;
    // 0x800BF270: bne         $at, $zero, L_800BF234
    if (ctx->r1 != 0) {
        // 0x800BF274: addiu       $a1, $a1, 0xC4
        ctx->r5 = ADD32(ctx->r5, 0XC4);
            goto L_800BF234;
    }
    // 0x800BF274: addiu       $a1, $a1, 0xC4
    ctx->r5 = ADD32(ctx->r5, 0XC4);
    // 0x800BF278: jal         0x800BD02C
    // 0x800BF27C: nop

    AudioSeq_InitLayerFreelist(rdram, ctx);
        goto after_0;
    // 0x800BF27C: nop

    after_0:
    // 0x800BF280: lui         $v0, 0x8004
    ctx->r2 = S32(0X8004 << 16);
    // 0x800BF284: lui         $v1, 0x8004
    ctx->r3 = S32(0X8004 << 16);
    // 0x800BF288: addiu       $v1, $v1, 0x4688
    ctx->r3 = ADD32(ctx->r3, 0X4688);
    // 0x800BF28C: addiu       $v0, $v0, 0x2688
    ctx->r2 = ADD32(ctx->r2, 0X2688);
L_800BF290:
    // 0x800BF290: lbu         $t9, 0x0($v0)
    ctx->r25 = MEM_BU(ctx->r2, 0X0);
    // 0x800BF294: addiu       $v0, $v0, 0x80
    ctx->r2 = ADD32(ctx->r2, 0X80);
    // 0x800BF298: sltu        $at, $v0, $v1
    ctx->r1 = ctx->r2 < ctx->r3 ? 1 : 0;
    // 0x800BF29C: andi        $t0, $t9, 0xFF7F
    ctx->r8 = ctx->r25 & 0XFF7F;
    // 0x800BF2A0: sw          $zero, -0x34($v0)
    MEM_W(-0X34, ctx->r2) = 0;
    // 0x800BF2A4: bne         $at, $zero, L_800BF290
    if (ctx->r1 != 0) {
        // 0x800BF2A8: sb          $t0, -0x80($v0)
        MEM_B(-0X80, ctx->r2) = ctx->r8;
            goto L_800BF290;
    }
    // 0x800BF2A8: sb          $t0, -0x80($v0)
    MEM_B(-0X80, ctx->r2) = ctx->r8;
    // 0x800BF2AC: lui         $t1, 0x8004
    ctx->r9 = S32(0X8004 << 16);
    // 0x800BF2B0: addiu       $s2, $t1, -0x338
    ctx->r18 = ADD32(ctx->r9, -0X338);
    // 0x800BF2B4: lui         $s5, 0x8004
    ctx->r21 = S32(0X8004 << 16);
    // 0x800BF2B8: lui         $s0, 0x8004
    ctx->r16 = S32(0X8004 << 16);
    // 0x800BF2BC: addiu       $s0, $s0, 0x4688
    ctx->r16 = ADD32(ctx->r16, 0X4688);
    // 0x800BF2C0: addiu       $s5, $s5, -0x2A4
    ctx->r21 = ADD32(ctx->r21, -0X2A4);
    // 0x800BF2C4: or          $s4, $s2, $zero
    ctx->r20 = ctx->r18 | 0;
    // 0x800BF2C8: or          $s3, $zero, $zero
    ctx->r19 = 0 | 0;
    // 0x800BF2CC: addiu       $s7, $zero, 0x4
    ctx->r23 = ADD32(0, 0X4);
    // 0x800BF2D0: addiu       $s6, $zero, -0x1
    ctx->r22 = ADD32(0, -0X1);
    // 0x800BF2D4: addiu       $s1, $zero, 0x10
    ctx->r17 = ADD32(0, 0X10);
L_800BF2D8:
    // 0x800BF2D8: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    // 0x800BF2DC: or          $v1, $s4, $zero
    ctx->r3 = ctx->r20 | 0;
L_800BF2E0:
    // 0x800BF2E0: addiu       $v0, $v0, 0x4
    ctx->r2 = ADD32(ctx->r2, 0X4);
    // 0x800BF2E4: sw          $s0, 0x34($v1)
    MEM_W(0X34, ctx->r3) = ctx->r16;
    // 0x800BF2E8: sw          $s0, 0x38($v1)
    MEM_W(0X38, ctx->r3) = ctx->r16;
    // 0x800BF2EC: sw          $s0, 0x3C($v1)
    MEM_W(0X3C, ctx->r3) = ctx->r16;
    // 0x800BF2F0: addiu       $v1, $v1, 0x10
    ctx->r3 = ADD32(ctx->r3, 0X10);
    // 0x800BF2F4: bne         $v0, $s1, L_800BF2E0
    if (ctx->r2 != ctx->r17) {
        // 0x800BF2F8: sw          $s0, 0x20($v1)
        MEM_W(0X20, ctx->r3) = ctx->r16;
            goto L_800BF2E0;
    }
    // 0x800BF2F8: sw          $s0, 0x20($v1)
    MEM_W(0X20, ctx->r3) = ctx->r16;
    // 0x800BF2FC: lbu         $t2, 0x0($s2)
    ctx->r10 = MEM_BU(ctx->r18, 0X0);
    // 0x800BF300: sb          $s6, 0x7($s2)
    MEM_B(0X7, ctx->r18) = ctx->r22;
    // 0x800BF304: or          $a0, $s5, $zero
    ctx->r4 = ctx->r21 | 0;
    // 0x800BF308: andi        $t4, $t2, 0xFFF7
    ctx->r12 = ctx->r10 & 0XFFF7;
    // 0x800BF30C: sb          $t4, 0x0($s2)
    MEM_B(0X0, ctx->r18) = ctx->r12;
    // 0x800BF310: andi        $t5, $t4, 0xEF
    ctx->r13 = ctx->r12 & 0XEF;
    // 0x800BF314: jal         0x800BB300
    // 0x800BF318: sb          $t5, 0x0($s2)
    MEM_B(0X0, ctx->r18) = ctx->r13;
    Audio_InitNoteLists(rdram, ctx);
        goto after_1;
    // 0x800BF318: sb          $t5, 0x0($s2)
    MEM_B(0X0, ctx->r18) = ctx->r13;
    after_1:
    // 0x800BF31C: jal         0x800BF13C
    // 0x800BF320: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
    AudioSeq_ResetSequencePlayer(rdram, ctx);
        goto after_2;
    // 0x800BF320: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
    after_2:
    // 0x800BF324: addiu       $s3, $s3, 0x1
    ctx->r19 = ADD32(ctx->r19, 0X1);
    // 0x800BF328: addiu       $s4, $s4, 0x140
    ctx->r20 = ADD32(ctx->r20, 0X140);
    // 0x800BF32C: addiu       $s2, $s2, 0x140
    ctx->r18 = ADD32(ctx->r18, 0X140);
    // 0x800BF330: bne         $s3, $s7, L_800BF2D8
    if (ctx->r19 != ctx->r23) {
        // 0x800BF334: addiu       $s5, $s5, 0x140
        ctx->r21 = ADD32(ctx->r21, 0X140);
            goto L_800BF2D8;
    }
    // 0x800BF334: addiu       $s5, $s5, 0x140
    ctx->r21 = ADD32(ctx->r21, 0X140);
    // 0x800BF338: lw          $ra, 0x34($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X34);
    // 0x800BF33C: lw          $s0, 0x14($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X14);
    // 0x800BF340: lw          $s1, 0x18($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X18);
    // 0x800BF344: lw          $s2, 0x1C($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X1C);
    // 0x800BF348: lw          $s3, 0x20($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X20);
    // 0x800BF34C: lw          $s4, 0x24($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X24);
    // 0x800BF350: lw          $s5, 0x28($sp)
    ctx->r21 = MEM_W(ctx->r29, 0X28);
    // 0x800BF354: lw          $s6, 0x2C($sp)
    ctx->r22 = MEM_W(ctx->r29, 0X2C);
    // 0x800BF358: lw          $s7, 0x30($sp)
    ctx->r23 = MEM_W(ctx->r29, 0X30);
    // 0x800BF35C: jr          $ra
    // 0x800BF360: addiu       $sp, $sp, 0x38
    ctx->r29 = ADD32(ctx->r29, 0X38);
    return;
    // 0x800BF360: addiu       $sp, $sp, 0x38
    ctx->r29 = ADD32(ctx->r29, 0X38);
    // 0x800BF364: nop

    // 0x800BF368: nop

    // 0x800BF36C: nop

;}
RECOMP_FUNC void n_alSynRemovePlayer(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800BF370: lui         $t6, 0x800E
    ctx->r14 = S32(0X800E << 16);
    // 0x800BF374: lb          $t6, 0x7C94($t6)
    ctx->r14 = MEM_B(ctx->r14, 0X7C94);
    // 0x800BF378: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x800BF37C: addiu       $at, $zero, 0xB
    ctx->r1 = ADD32(0, 0XB);
    // 0x800BF380: bne         $t6, $at, L_800BF390
    if (ctx->r14 != ctx->r1) {
        // 0x800BF384: sw          $ra, 0x14($sp)
        MEM_W(0X14, ctx->r29) = ctx->r31;
            goto L_800BF390;
    }
    // 0x800BF384: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800BF388: jal         0x800C40B0
    // 0x800BF38C: nop

    func_800C40B0(rdram, ctx);
        goto after_0;
    // 0x800BF38C: nop

    after_0:
L_800BF390:
    // 0x800BF390: lui         $t7, 0x800E
    ctx->r15 = S32(0X800E << 16);
    // 0x800BF394: lw          $t7, 0x7CE0($t7)
    ctx->r15 = MEM_W(ctx->r15, 0X7CE0);
    // 0x800BF398: beq         $t7, $zero, L_800BF3A8
    if (ctx->r15 == 0) {
        // 0x800BF39C: nop
    
            goto L_800BF3A8;
    }
    // 0x800BF39C: nop

    // 0x800BF3A0: jal         0x800BF964
    // 0x800BF3A4: nop

    func_800BF964(rdram, ctx);
        goto after_1;
    // 0x800BF3A4: nop

    after_1:
L_800BF3A8:
    // 0x800BF3A8: lui         $v1, 0x800E
    ctx->r3 = S32(0X800E << 16);
    // 0x800BF3AC: addiu       $v1, $v1, 0x7CDC
    ctx->r3 = ADD32(ctx->r3, 0X7CDC);
    // 0x800BF3B0: lw          $v0, 0x0($v1)
    ctx->r2 = MEM_W(ctx->r3, 0X0);
    // 0x800BF3B4: beq         $v0, $zero, L_800BF3D4
    if (ctx->r2 == 0) {
        // 0x800BF3B8: addiu       $t8, $v0, -0x1
        ctx->r24 = ADD32(ctx->r2, -0X1);
            goto L_800BF3D4;
    }
    // 0x800BF3B8: addiu       $t8, $v0, -0x1
    ctx->r24 = ADD32(ctx->r2, -0X1);
    // 0x800BF3BC: bne         $t8, $zero, L_800BF3D4
    if (ctx->r24 != 0) {
        // 0x800BF3C0: sw          $t8, 0x0($v1)
        MEM_W(0X0, ctx->r3) = ctx->r24;
            goto L_800BF3D4;
    }
    // 0x800BF3C0: sw          $t8, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r24;
    // 0x800BF3C4: lui         $a0, 0x801D
    ctx->r4 = S32(0X801D << 16);
    // 0x800BF3C8: lw          $a0, 0x7DCC($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X7DCC);
    // 0x800BF3CC: jal         0x800C15C8
    // 0x800BF3D0: addiu       $a1, $zero, 0xA
    ctx->r5 = ADD32(0, 0XA);
    func_800C15C8(rdram, ctx);
        goto after_2;
    // 0x800BF3D0: addiu       $a1, $zero, 0xA
    ctx->r5 = ADD32(0, 0XA);
    after_2:
L_800BF3D4:
    // 0x800BF3D4: lui         $v1, 0x800E
    ctx->r3 = S32(0X800E << 16);
    // 0x800BF3D8: addiu       $v1, $v1, 0x7CE4
    ctx->r3 = ADD32(ctx->r3, 0X7CE4);
    // 0x800BF3DC: lw          $v0, 0x0($v1)
    ctx->r2 = MEM_W(ctx->r3, 0X0);
    // 0x800BF3E0: beq         $v0, $zero, L_800BF3FC
    if (ctx->r2 == 0) {
        // 0x800BF3E4: addiu       $t0, $v0, -0x1
        ctx->r8 = ADD32(ctx->r2, -0X1);
            goto L_800BF3FC;
    }
    // 0x800BF3E4: addiu       $t0, $v0, -0x1
    ctx->r8 = ADD32(ctx->r2, -0X1);
    // 0x800BF3E8: bne         $t0, $zero, L_800BF3FC
    if (ctx->r8 != 0) {
        // 0x800BF3EC: sw          $t0, 0x0($v1)
        MEM_W(0X0, ctx->r3) = ctx->r8;
            goto L_800BF3FC;
    }
    // 0x800BF3EC: sw          $t0, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r8;
    // 0x800BF3F0: lui         $a0, 0x801D
    ctx->r4 = S32(0X801D << 16);
    // 0x800BF3F4: jal         0x800C377C
    // 0x800BF3F8: lw          $a0, 0x7E1C($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X7E1C);
    func_800C377C(rdram, ctx);
        goto after_3;
    // 0x800BF3F8: lw          $a0, 0x7E1C($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X7E1C);
    after_3:
L_800BF3FC:
    // 0x800BF3FC: lui         $t2, 0x800E
    ctx->r10 = S32(0X800E << 16);
    // 0x800BF400: lb          $t2, 0x7C94($t2)
    ctx->r10 = MEM_B(ctx->r10, 0X7C94);
    // 0x800BF404: bne         $t2, $zero, L_800BF47C
    if (ctx->r10 != 0) {
        // 0x800BF408: nop
    
            goto L_800BF47C;
    }
    // 0x800BF408: nop

    // 0x800BF40C: jal         0x800BF8C8
    // 0x800BF410: nop

    func_800BF8C8(rdram, ctx);
        goto after_4;
    // 0x800BF410: nop

    after_4:
    // 0x800BF414: lui         $v0, 0x8004
    ctx->r2 = S32(0X8004 << 16);
    // 0x800BF418: lw          $v0, -0x19C($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X19C);
    // 0x800BF41C: lui         $t3, 0x8004
    ctx->r11 = S32(0X8004 << 16);
    // 0x800BF420: addiu       $t3, $t3, 0x4688
    ctx->r11 = ADD32(ctx->r11, 0X4688);
    // 0x800BF424: beq         $v0, $t3, L_800BF47C
    if (ctx->r2 == ctx->r11) {
        // 0x800BF428: nop
    
            goto L_800BF47C;
    }
    // 0x800BF428: nop

    // 0x800BF42C: lb          $v1, 0x58($v0)
    ctx->r3 = MEM_B(ctx->r2, 0X58);
    // 0x800BF430: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x800BF434: lui         $a0, 0x601
    ctx->r4 = S32(0X601 << 16);
    // 0x800BF438: beq         $v1, $at, L_800BF47C
    if (ctx->r3 == ctx->r1) {
        // 0x800BF43C: ori         $a0, $a0, 0xB00
        ctx->r4 = ctx->r4 | 0XB00;
            goto L_800BF47C;
    }
    // 0x800BF43C: ori         $a0, $a0, 0xB00
    ctx->r4 = ctx->r4 | 0XB00;
    // 0x800BF440: addiu       $a1, $zero, -0x1
    ctx->r5 = ADD32(0, -0X1);
    // 0x800BF444: jal         0x800C53D4
    // 0x800BF448: sw          $v1, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r3;
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_5;
    // 0x800BF448: sw          $v1, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r3;
    after_5:
    // 0x800BF44C: lw          $v1, 0x18($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X18);
    // 0x800BF450: addiu       $at, $zero, 0xE
    ctx->r1 = ADD32(0, 0XE);
    // 0x800BF454: bnel        $v1, $at, L_800BF46C
    if (ctx->r3 != ctx->r1) {
        // 0x800BF458: addiu       $at, $zero, 0x1
        ctx->r1 = ADD32(0, 0X1);
            goto L_800BF46C;
    }
    goto skip_0;
    // 0x800BF458: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    skip_0:
    // 0x800BF45C: jal         0x80094ABC
    // 0x800BF460: sw          $v1, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r3;
    func_80094ABC(rdram, ctx);
        goto after_6;
    // 0x800BF460: sw          $v1, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r3;
    after_6:
    // 0x800BF464: lw          $v1, 0x18($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X18);
    // 0x800BF468: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
L_800BF46C:
    // 0x800BF46C: bne         $v1, $at, L_800BF47C
    if (ctx->r3 != ctx->r1) {
        // 0x800BF470: nop
    
            goto L_800BF47C;
    }
    // 0x800BF470: nop

    // 0x800BF474: jal         0x8009D320
    // 0x800BF478: nop

    func_8009D320(rdram, ctx);
        goto after_7;
    // 0x800BF478: nop

    after_7:
L_800BF47C:
    // 0x800BF47C: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x800BF480: lw          $v0, 0x7CB0($v0)
    ctx->r2 = MEM_W(ctx->r2, 0X7CB0);
    // 0x800BF484: beq         $v0, $zero, L_800BF4C4
    if (ctx->r2 == 0) {
        // 0x800BF488: andi        $t4, $v0, 0xF
        ctx->r12 = ctx->r2 & 0XF;
            goto L_800BF4C4;
    }
    // 0x800BF488: andi        $t4, $v0, 0xF
    ctx->r12 = ctx->r2 & 0XF;
    // 0x800BF48C: bne         $t4, $zero, L_800BF4B8
    if (ctx->r12 != 0) {
        // 0x800BF490: lui         $a0, 0x100
        ctx->r4 = S32(0X100 << 16);
            goto L_800BF4B8;
    }
    // 0x800BF490: lui         $a0, 0x100
    ctx->r4 = S32(0X100 << 16);
    // 0x800BF494: ori         $a0, $a0, 0x500
    ctx->r4 = ctx->r4 | 0X500;
    // 0x800BF498: jal         0x800C538C
    // 0x800BF49C: lui         $a1, 0x3F80
    ctx->r5 = S32(0X3F80 << 16);
    AudioThread_QueueCmdF32(rdram, ctx);
        goto after_8;
    // 0x800BF49C: lui         $a1, 0x3F80
    ctx->r5 = S32(0X3F80 << 16);
    after_8:
    // 0x800BF4A0: addiu       $a0, $zero, 0x5
    ctx->r4 = ADD32(0, 0X5);
    // 0x800BF4A4: addiu       $a1, $zero, 0xA
    ctx->r5 = ADD32(0, 0XA);
    // 0x800BF4A8: jal         0x800BFFEC
    // 0x800BF4AC: addiu       $a2, $zero, 0x7F
    ctx->r6 = ADD32(0, 0X7F);
    func_800BFFEC(rdram, ctx);
        goto after_9;
    // 0x800BF4AC: addiu       $a2, $zero, 0x7F
    ctx->r6 = ADD32(0, 0X7F);
    after_9:
    // 0x800BF4B0: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x800BF4B4: lw          $v0, 0x7CB0($v0)
    ctx->r2 = MEM_W(ctx->r2, 0X7CB0);
L_800BF4B8:
    // 0x800BF4B8: addiu       $t5, $v0, -0x1
    ctx->r13 = ADD32(ctx->r2, -0X1);
    // 0x800BF4BC: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x800BF4C0: sw          $t5, 0x7CB0($at)
    MEM_W(0X7CB0, ctx->r1) = ctx->r13;
L_800BF4C4:
    // 0x800BF4C4: lui         $t6, 0x800E
    ctx->r14 = S32(0X800E << 16);
    // 0x800BF4C8: lw          $t6, 0x7CC4($t6)
    ctx->r14 = MEM_W(ctx->r14, 0X7CC4);
    // 0x800BF4CC: lui         $v1, 0x800E
    ctx->r3 = S32(0X800E << 16);
    // 0x800BF4D0: addiu       $v1, $v1, 0x7CE8
    ctx->r3 = ADD32(ctx->r3, 0X7CE8);
    // 0x800BF4D4: bne         $t6, $zero, L_800BF68C
    if (ctx->r14 != 0) {
        // 0x800BF4D8: lui         $a0, 0xF100
        ctx->r4 = S32(0XF100 << 16);
            goto L_800BF68C;
    }
    // 0x800BF4D8: lui         $a0, 0xF100
    ctx->r4 = S32(0XF100 << 16);
    // 0x800BF4DC: lw          $v0, 0x0($v1)
    ctx->r2 = MEM_W(ctx->r3, 0X0);
    // 0x800BF4E0: beq         $v0, $zero, L_800BF4EC
    if (ctx->r2 == 0) {
        // 0x800BF4E4: addiu       $t7, $v0, -0x1
        ctx->r15 = ADD32(ctx->r2, -0X1);
            goto L_800BF4EC;
    }
    // 0x800BF4E4: addiu       $t7, $v0, -0x1
    ctx->r15 = ADD32(ctx->r2, -0X1);
    // 0x800BF4E8: sw          $t7, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r15;
L_800BF4EC:
    // 0x800BF4EC: lui         $v1, 0x800E
    ctx->r3 = S32(0X800E << 16);
    // 0x800BF4F0: addiu       $v1, $v1, 0x7CD8
    ctx->r3 = ADD32(ctx->r3, 0X7CD8);
    // 0x800BF4F4: lw          $v0, 0x0($v1)
    ctx->r2 = MEM_W(ctx->r3, 0X0);
    // 0x800BF4F8: beq         $v0, $zero, L_800BF528
    if (ctx->r2 == 0) {
        // 0x800BF4FC: addiu       $t8, $v0, -0x1
        ctx->r24 = ADD32(ctx->r2, -0X1);
            goto L_800BF528;
    }
    // 0x800BF4FC: addiu       $t8, $v0, -0x1
    ctx->r24 = ADD32(ctx->r2, -0X1);
    // 0x800BF500: bne         $t8, $zero, L_800BF528
    if (ctx->r24 != 0) {
        // 0x800BF504: sw          $t8, 0x0($v1)
        MEM_W(0X0, ctx->r3) = ctx->r24;
            goto L_800BF528;
    }
    // 0x800BF504: sw          $t8, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r24;
    // 0x800BF508: lui         $t0, 0x800E
    ctx->r8 = S32(0X800E << 16);
    // 0x800BF50C: lw          $t0, 0x7C98($t0)
    ctx->r8 = MEM_W(ctx->r8, 0X7C98);
    // 0x800BF510: lui         $a0, 0x801D
    ctx->r4 = S32(0X801D << 16);
    // 0x800BF514: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x800BF518: beq         $t0, $zero, L_800BF528
    if (ctx->r8 == 0) {
        // 0x800BF51C: or          $a2, $zero, $zero
        ctx->r6 = 0 | 0;
            goto L_800BF528;
    }
    // 0x800BF51C: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x800BF520: jal         0x800C1540
    // 0x800BF524: lw          $a0, 0x7DCC($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X7DCC);
    func_800C1540(rdram, ctx);
        goto after_10;
    // 0x800BF524: lw          $a0, 0x7DCC($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X7DCC);
    after_10:
L_800BF528:
    // 0x800BF528: lui         $v1, 0x800E
    ctx->r3 = S32(0X800E << 16);
    // 0x800BF52C: addiu       $v1, $v1, 0x7CF0
    ctx->r3 = ADD32(ctx->r3, 0X7CF0);
    // 0x800BF530: lw          $v0, 0x0($v1)
    ctx->r2 = MEM_W(ctx->r3, 0X0);
    // 0x800BF534: beq         $v0, $zero, L_800BF54C
    if (ctx->r2 == 0) {
        // 0x800BF538: addiu       $t1, $v0, -0x1
        ctx->r9 = ADD32(ctx->r2, -0X1);
            goto L_800BF54C;
    }
    // 0x800BF538: addiu       $t1, $v0, -0x1
    ctx->r9 = ADD32(ctx->r2, -0X1);
    // 0x800BF53C: bne         $t1, $zero, L_800BF54C
    if (ctx->r9 != 0) {
        // 0x800BF540: sw          $t1, 0x0($v1)
        MEM_W(0X0, ctx->r3) = ctx->r9;
            goto L_800BF54C;
    }
    // 0x800BF540: sw          $t1, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r9;
    // 0x800BF544: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x800BF548: sw          $zero, 0x7CF4($at)
    MEM_W(0X7CF4, ctx->r1) = 0;
L_800BF54C:
    // 0x800BF54C: lui         $v1, 0x800E
    ctx->r3 = S32(0X800E << 16);
    // 0x800BF550: addiu       $v1, $v1, 0x7C9C
    ctx->r3 = ADD32(ctx->r3, 0X7C9C);
    // 0x800BF554: lw          $v0, 0x0($v1)
    ctx->r2 = MEM_W(ctx->r3, 0X0);
    // 0x800BF558: beq         $v0, $zero, L_800BF570
    if (ctx->r2 == 0) {
        // 0x800BF55C: addiu       $t3, $v0, -0x1
        ctx->r11 = ADD32(ctx->r2, -0X1);
            goto L_800BF570;
    }
    // 0x800BF55C: addiu       $t3, $v0, -0x1
    ctx->r11 = ADD32(ctx->r2, -0X1);
    // 0x800BF560: bne         $t3, $zero, L_800BF570
    if (ctx->r11 != 0) {
        // 0x800BF564: sw          $t3, 0x0($v1)
        MEM_W(0X0, ctx->r3) = ctx->r11;
            goto L_800BF570;
    }
    // 0x800BF564: sw          $t3, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r11;
    // 0x800BF568: jal         0x800C1B98
    // 0x800BF56C: nop

    func_800C1B98(rdram, ctx);
        goto after_11;
    // 0x800BF56C: nop

    after_11:
L_800BF570:
    // 0x800BF570: lui         $v1, 0x800E
    ctx->r3 = S32(0X800E << 16);
    // 0x800BF574: addiu       $v1, $v1, 0x7CD4
    ctx->r3 = ADD32(ctx->r3, 0X7CD4);
    // 0x800BF578: lw          $v0, 0x0($v1)
    ctx->r2 = MEM_W(ctx->r3, 0X0);
    // 0x800BF57C: lui         $t5, 0x800E
    ctx->r13 = S32(0X800E << 16);
    // 0x800BF580: beq         $v0, $zero, L_800BF638
    if (ctx->r2 == 0) {
        // 0x800BF584: nop
    
            goto L_800BF638;
    }
    // 0x800BF584: nop

    // 0x800BF588: lw          $t5, 0x7CC4($t5)
    ctx->r13 = MEM_W(ctx->r13, 0X7CC4);
    // 0x800BF58C: addiu       $t6, $v0, -0x1
    ctx->r14 = ADD32(ctx->r2, -0X1);
    // 0x800BF590: lui         $t7, 0x801D
    ctx->r15 = S32(0X801D << 16);
    // 0x800BF594: bne         $t5, $zero, L_800BF5A4
    if (ctx->r13 != 0) {
        // 0x800BF598: nop
    
            goto L_800BF5A4;
    }
    // 0x800BF598: nop

    // 0x800BF59C: sw          $t6, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r14;
    // 0x800BF5A0: or          $v0, $t6, $zero
    ctx->r2 = ctx->r14 | 0;
L_800BF5A4:
    // 0x800BF5A4: bne         $v0, $zero, L_800BF638
    if (ctx->r2 != 0) {
        // 0x800BF5A8: nop
    
            goto L_800BF638;
    }
    // 0x800BF5A8: nop

    // 0x800BF5AC: lw          $t7, 0x7DC0($t7)
    ctx->r15 = MEM_W(ctx->r15, 0X7DC0);
    // 0x800BF5B0: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x800BF5B4: bne         $t7, $zero, L_800BF638
    if (ctx->r15 != 0) {
        // 0x800BF5B8: nop
    
            goto L_800BF638;
    }
    // 0x800BF5B8: nop

    // 0x800BF5BC: lb          $v0, 0x7DFA($v0)
    ctx->r2 = MEM_B(ctx->r2, 0X7DFA);
    // 0x800BF5C0: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x800BF5C4: lui         $a0, 0x8004
    ctx->r4 = S32(0X8004 << 16);
    // 0x800BF5C8: beq         $v0, $zero, L_800BF5E0
    if (ctx->r2 == 0) {
        // 0x800BF5CC: nop
    
            goto L_800BF5E0;
    }
    // 0x800BF5CC: nop

    // 0x800BF5D0: beq         $v0, $at, L_800BF600
    if (ctx->r2 == ctx->r1) {
        // 0x800BF5D4: lui         $a0, 0x8004
        ctx->r4 = S32(0X8004 << 16);
            goto L_800BF600;
    }
    // 0x800BF5D4: lui         $a0, 0x8004
    ctx->r4 = S32(0X8004 << 16);
    // 0x800BF5D8: b           L_800BF620
    // 0x800BF5DC: lui         $a0, 0x8004
    ctx->r4 = S32(0X8004 << 16);
        goto L_800BF620;
    // 0x800BF5DC: lui         $a0, 0x8004
    ctx->r4 = S32(0X8004 << 16);
L_800BF5E0:
    // 0x800BF5E0: lw          $a0, 0x562C($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X562C);
    // 0x800BF5E4: addiu       $a1, $zero, 0x5A
    ctx->r5 = ADD32(0, 0X5A);
    // 0x800BF5E8: addiu       $a2, $zero, 0x3C
    ctx->r6 = ADD32(0, 0X3C);
    // 0x800BF5EC: andi        $t8, $a0, 0x1
    ctx->r24 = ctx->r4 & 0X1;
    // 0x800BF5F0: jal         0x800C3320
    // 0x800BF5F4: addiu       $a0, $t8, 0x24
    ctx->r4 = ADD32(ctx->r24, 0X24);
    func_800C3320(rdram, ctx);
        goto after_12;
    // 0x800BF5F4: addiu       $a0, $t8, 0x24
    ctx->r4 = ADD32(ctx->r24, 0X24);
    after_12:
    // 0x800BF5F8: b           L_800BF638
    // 0x800BF5FC: nop

        goto L_800BF638;
    // 0x800BF5FC: nop

L_800BF600:
    // 0x800BF600: lw          $a0, 0x562C($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X562C);
    // 0x800BF604: addiu       $a1, $zero, 0x5A
    ctx->r5 = ADD32(0, 0X5A);
    // 0x800BF608: addiu       $a2, $zero, 0x3C
    ctx->r6 = ADD32(0, 0X3C);
    // 0x800BF60C: andi        $t9, $a0, 0x1
    ctx->r25 = ctx->r4 & 0X1;
    // 0x800BF610: jal         0x800C3320
    // 0x800BF614: addiu       $a0, $t9, 0x27
    ctx->r4 = ADD32(ctx->r25, 0X27);
    func_800C3320(rdram, ctx);
        goto after_13;
    // 0x800BF614: addiu       $a0, $t9, 0x27
    ctx->r4 = ADD32(ctx->r25, 0X27);
    after_13:
    // 0x800BF618: b           L_800BF638
    // 0x800BF61C: nop

        goto L_800BF638;
    // 0x800BF61C: nop

L_800BF620:
    // 0x800BF620: lw          $a0, 0x562C($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X562C);
    // 0x800BF624: addiu       $a1, $zero, 0x5A
    ctx->r5 = ADD32(0, 0X5A);
    // 0x800BF628: addiu       $a2, $zero, 0x3C
    ctx->r6 = ADD32(0, 0X3C);
    // 0x800BF62C: andi        $t0, $a0, 0x1
    ctx->r8 = ctx->r4 & 0X1;
    // 0x800BF630: jal         0x800C3320
    // 0x800BF634: addiu       $a0, $t0, 0x2A
    ctx->r4 = ADD32(ctx->r8, 0X2A);
    func_800C3320(rdram, ctx);
        goto after_14;
    // 0x800BF634: addiu       $a0, $t0, 0x2A
    ctx->r4 = ADD32(ctx->r8, 0X2A);
    after_14:
L_800BF638:
    // 0x800BF638: jal         0x800C3494
    // 0x800BF63C: nop

    func_800C3494(rdram, ctx);
        goto after_15;
    // 0x800BF63C: nop

    after_15:
    // 0x800BF640: lui         $v1, 0x800E
    ctx->r3 = S32(0X800E << 16);
    // 0x800BF644: addiu       $v1, $v1, 0x7CEC
    ctx->r3 = ADD32(ctx->r3, 0X7CEC);
    // 0x800BF648: lw          $v0, 0x0($v1)
    ctx->r2 = MEM_W(ctx->r3, 0X0);
    // 0x800BF64C: lui         $t1, 0x800E
    ctx->r9 = S32(0X800E << 16);
    // 0x800BF650: beq         $v0, $zero, L_800BF694
    if (ctx->r2 == 0) {
        // 0x800BF654: nop
    
            goto L_800BF694;
    }
    // 0x800BF654: nop

    // 0x800BF658: lw          $t1, 0x7C98($t1)
    ctx->r9 = MEM_W(ctx->r9, 0X7C98);
    // 0x800BF65C: addiu       $t2, $v0, -0x1
    ctx->r10 = ADD32(ctx->r2, -0X1);
    // 0x800BF660: beq         $t1, $zero, L_800BF694
    if (ctx->r9 == 0) {
        // 0x800BF664: nop
    
            goto L_800BF694;
    }
    // 0x800BF664: nop

    // 0x800BF668: bne         $t2, $zero, L_800BF694
    if (ctx->r10 != 0) {
        // 0x800BF66C: sw          $t2, 0x0($v1)
        MEM_W(0X0, ctx->r3) = ctx->r10;
            goto L_800BF694;
    }
    // 0x800BF66C: sw          $t2, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r10;
    // 0x800BF670: lui         $a0, 0x801D
    ctx->r4 = S32(0X801D << 16);
    // 0x800BF674: lw          $a0, 0x7DCC($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X7DCC);
    // 0x800BF678: addiu       $a1, $zero, 0x78
    ctx->r5 = ADD32(0, 0X78);
    // 0x800BF67C: jal         0x800C1540
    // 0x800BF680: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    func_800C1540(rdram, ctx);
        goto after_16;
    // 0x800BF680: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    after_16:
    // 0x800BF684: b           L_800BF694
    // 0x800BF688: nop

        goto L_800BF694;
    // 0x800BF688: nop

L_800BF68C:
    // 0x800BF68C: jal         0x800C53B0
    // 0x800BF690: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    AudioThread_QueueCmdS32(rdram, ctx);
        goto after_17;
    // 0x800BF690: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_17:
L_800BF694:
    // 0x800BF694: jal         0x800C5404
    // 0x800BF698: nop

    AudioThread_ScheduleProcessCmds(rdram, ctx);
        goto after_18;
    // 0x800BF698: nop

    after_18:
    // 0x800BF69C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800BF6A0: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x800BF6A4: jr          $ra
    // 0x800BF6A8: nop

    return;
    // 0x800BF6A8: nop

;}
RECOMP_FUNC void func_800BF6AC(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800BF6AC: lui         $t6, 0x800E
    ctx->r14 = S32(0X800E << 16);
    // 0x800BF6B0: lb          $t6, 0x7C94($t6)
    ctx->r14 = MEM_B(ctx->r14, 0X7C94);
    // 0x800BF6B4: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x800BF6B8: addiu       $at, $zero, 0x7
    ctx->r1 = ADD32(0, 0X7);
    // 0x800BF6BC: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800BF6C0: bne         $t6, $at, L_800BF774
    if (ctx->r14 != ctx->r1) {
        // 0x800BF6C4: sw          $a1, 0x24($sp)
        MEM_W(0X24, ctx->r29) = ctx->r5;
            goto L_800BF774;
    }
    // 0x800BF6C4: sw          $a1, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r5;
    // 0x800BF6C8: lui         $at, 0x42FE
    ctx->r1 = S32(0X42FE << 16);
    // 0x800BF6CC: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x800BF6D0: lui         $a0, 0x100
    ctx->r4 = S32(0X100 << 16);
    // 0x800BF6D4: lui         $at, 0x4180
    ctx->r1 = S32(0X4180 << 16);
    // 0x800BF6D8: c.le.s      $f4, $f12
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 12);
    c1cs = ctx->f4.fl <= ctx->f12.fl;
    // 0x800BF6DC: ori         $a0, $a0, 0x700
    ctx->r4 = ctx->r4 | 0X700;
    // 0x800BF6E0: lui         $a1, 0x3F80
    ctx->r5 = S32(0X3F80 << 16);
    // 0x800BF6E4: bc1tl       L_800BF778
    if (c1cs) {
        // 0x800BF6E8: lw          $ra, 0x14($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X14);
            goto L_800BF778;
    }
    goto skip_0;
    // 0x800BF6E8: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    skip_0:
    // 0x800BF6EC: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x800BF6F0: nop

    // 0x800BF6F4: c.le.s      $f12, $f6
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 6);
    c1cs = ctx->f12.fl <= ctx->f6.fl;
    // 0x800BF6F8: nop

    // 0x800BF6FC: bc1fl       L_800BF710
    if (!c1cs) {
        // 0x800BF700: trunc.w.s   $f8, $f12
        CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 12);
    ctx->f8.u32l = TRUNC_W_S(ctx->f12.fl);
            goto L_800BF710;
    }
    goto skip_1;
    // 0x800BF700: trunc.w.s   $f8, $f12
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 12);
    ctx->f8.u32l = TRUNC_W_S(ctx->f12.fl);
    skip_1:
    // 0x800BF704: b           L_800BF720
    // 0x800BF708: addiu       $v0, $zero, 0x7F
    ctx->r2 = ADD32(0, 0X7F);
        goto L_800BF720;
    // 0x800BF708: addiu       $v0, $zero, 0x7F
    ctx->r2 = ADD32(0, 0X7F);
    // 0x800BF70C: trunc.w.s   $f8, $f12
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 12);
    ctx->f8.u32l = TRUNC_W_S(ctx->f12.fl);
L_800BF710:
    // 0x800BF710: addiu       $t9, $zero, 0x7F
    ctx->r25 = ADD32(0, 0X7F);
    // 0x800BF714: mfc1        $t8, $f8
    ctx->r24 = (int32_t)ctx->f8.u32l;
    // 0x800BF718: nop

    // 0x800BF71C: subu        $v0, $t9, $t8
    ctx->r2 = SUB32(ctx->r25, ctx->r24);
L_800BF720:
    // 0x800BF720: jal         0x800C538C
    // 0x800BF724: sw          $v0, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r2;
    AudioThread_QueueCmdF32(rdram, ctx);
        goto after_0;
    // 0x800BF724: sw          $v0, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r2;
    after_0:
    // 0x800BF728: lui         $a0, 0x600
    ctx->r4 = S32(0X600 << 16);
    // 0x800BF72C: ori         $a0, $a0, 0x700
    ctx->r4 = ctx->r4 | 0X700;
    // 0x800BF730: jal         0x800C53D4
    // 0x800BF734: addiu       $a1, $zero, -0x1
    ctx->r5 = ADD32(0, -0X1);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_1;
    // 0x800BF734: addiu       $a1, $zero, -0x1
    ctx->r5 = ADD32(0, -0X1);
    after_1:
    // 0x800BF738: lw          $v0, 0x1C($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X1C);
    // 0x800BF73C: lui         $a0, 0x600
    ctx->r4 = S32(0X600 << 16);
    // 0x800BF740: ori         $a0, $a0, 0x701
    ctx->r4 = ctx->r4 | 0X701;
    // 0x800BF744: sll         $a1, $v0, 24
    ctx->r5 = S32(ctx->r2 << 24);
    // 0x800BF748: sra         $t0, $a1, 24
    ctx->r8 = S32(SIGNED(ctx->r5) >> 24);
    // 0x800BF74C: jal         0x800C53D4
    // 0x800BF750: or          $a1, $t0, $zero
    ctx->r5 = ctx->r8 | 0;
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_2;
    // 0x800BF750: or          $a1, $t0, $zero
    ctx->r5 = ctx->r8 | 0;
    after_2:
    // 0x800BF754: lui         $a0, 0x600
    ctx->r4 = S32(0X600 << 16);
    // 0x800BF758: ori         $a0, $a0, 0x702
    ctx->r4 = ctx->r4 | 0X702;
    // 0x800BF75C: jal         0x800C53D4
    // 0x800BF760: lb          $a1, 0x27($sp)
    ctx->r5 = MEM_B(ctx->r29, 0X27);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_3;
    // 0x800BF760: lb          $a1, 0x27($sp)
    ctx->r5 = MEM_B(ctx->r29, 0X27);
    after_3:
    // 0x800BF764: lui         $a0, 0x600
    ctx->r4 = S32(0X600 << 16);
    // 0x800BF768: ori         $a0, $a0, 0x700
    ctx->r4 = ctx->r4 | 0X700;
    // 0x800BF76C: jal         0x800C53D4
    // 0x800BF770: addiu       $a1, $zero, 0x14
    ctx->r5 = ADD32(0, 0X14);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_4;
    // 0x800BF770: addiu       $a1, $zero, 0x14
    ctx->r5 = ADD32(0, 0X14);
    after_4:
L_800BF774:
    // 0x800BF774: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_800BF778:
    // 0x800BF778: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x800BF77C: jr          $ra
    // 0x800BF780: nop

    return;
    // 0x800BF780: nop

;}
RECOMP_FUNC void func_800BF784(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800BF784: lui         $t6, 0x800E
    ctx->r14 = S32(0X800E << 16);
    // 0x800BF788: lb          $t6, 0x7C94($t6)
    ctx->r14 = MEM_B(ctx->r14, 0X7C94);
    // 0x800BF78C: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800BF790: addiu       $at, $zero, 0x7
    ctx->r1 = ADD32(0, 0X7);
    // 0x800BF794: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800BF798: bne         $t6, $at, L_800BF834
    if (ctx->r14 != ctx->r1) {
        // 0x800BF79C: sw          $a1, 0x1C($sp)
        MEM_W(0X1C, ctx->r29) = ctx->r5;
            goto L_800BF834;
    }
    // 0x800BF79C: sw          $a1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r5;
    // 0x800BF7A0: lui         $at, 0x4300
    ctx->r1 = S32(0X4300 << 16);
    // 0x800BF7A4: mtc1        $at, $f2
    ctx->f2.u32l = ctx->r1;
    // 0x800BF7A8: lui         $at, 0x4140
    ctx->r1 = S32(0X4140 << 16);
    // 0x800BF7AC: lui         $a0, 0x100
    ctx->r4 = S32(0X100 << 16);
    // 0x800BF7B0: c.le.s      $f2, $f12
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 12);
    c1cs = ctx->f2.fl <= ctx->f12.fl;
    // 0x800BF7B4: nop

    // 0x800BF7B8: bc1tl       L_800BF838
    if (c1cs) {
        // 0x800BF7BC: lw          $ra, 0x14($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X14);
            goto L_800BF838;
    }
    goto skip_0;
    // 0x800BF7BC: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    skip_0:
    // 0x800BF7C0: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x800BF7C4: lui         $at, 0x42E8
    ctx->r1 = S32(0X42E8 << 16);
    // 0x800BF7C8: c.le.s      $f12, $f4
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    c1cs = ctx->f12.fl <= ctx->f4.fl;
    // 0x800BF7CC: nop

    // 0x800BF7D0: bc1fl       L_800BF7EC
    if (!c1cs) {
        // 0x800BF7D4: sub.s       $f6, $f2, $f12
        CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f6.fl = ctx->f2.fl - ctx->f12.fl;
            goto L_800BF7EC;
    }
    goto skip_1;
    // 0x800BF7D4: sub.s       $f6, $f2, $f12
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f6.fl = ctx->f2.fl - ctx->f12.fl;
    skip_1:
    // 0x800BF7D8: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x800BF7DC: mtc1        $at, $f0
    ctx->f0.u32l = ctx->r1;
    // 0x800BF7E0: b           L_800BF7FC
    // 0x800BF7E4: mfc1        $a1, $f0
    ctx->r5 = (int32_t)ctx->f0.u32l;
        goto L_800BF7FC;
    // 0x800BF7E4: mfc1        $a1, $f0
    ctx->r5 = (int32_t)ctx->f0.u32l;
    // 0x800BF7E8: sub.s       $f6, $f2, $f12
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f6.fl = ctx->f2.fl - ctx->f12.fl;
L_800BF7EC:
    // 0x800BF7EC: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x800BF7F0: nop

    // 0x800BF7F4: div.s       $f0, $f6, $f8
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f0.fl = DIV_S(ctx->f6.fl, ctx->f8.fl);
    // 0x800BF7F8: mfc1        $a1, $f0
    ctx->r5 = (int32_t)ctx->f0.u32l;
L_800BF7FC:
    // 0x800BF7FC: jal         0x800C538C
    // 0x800BF800: ori         $a0, $a0, 0x700
    ctx->r4 = ctx->r4 | 0X700;
    AudioThread_QueueCmdF32(rdram, ctx);
        goto after_0;
    // 0x800BF800: ori         $a0, $a0, 0x700
    ctx->r4 = ctx->r4 | 0X700;
    after_0:
    // 0x800BF804: lui         $a0, 0x600
    ctx->r4 = S32(0X600 << 16);
    // 0x800BF808: ori         $a0, $a0, 0x701
    ctx->r4 = ctx->r4 | 0X701;
    // 0x800BF80C: jal         0x800C53D4
    // 0x800BF810: addiu       $a1, $zero, 0x7F
    ctx->r5 = ADD32(0, 0X7F);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_1;
    // 0x800BF810: addiu       $a1, $zero, 0x7F
    ctx->r5 = ADD32(0, 0X7F);
    after_1:
    // 0x800BF814: lui         $a0, 0x600
    ctx->r4 = S32(0X600 << 16);
    // 0x800BF818: ori         $a0, $a0, 0x702
    ctx->r4 = ctx->r4 | 0X702;
    // 0x800BF81C: jal         0x800C53D4
    // 0x800BF820: lb          $a1, 0x1F($sp)
    ctx->r5 = MEM_B(ctx->r29, 0X1F);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_2;
    // 0x800BF820: lb          $a1, 0x1F($sp)
    ctx->r5 = MEM_B(ctx->r29, 0X1F);
    after_2:
    // 0x800BF824: lui         $a0, 0x600
    ctx->r4 = S32(0X600 << 16);
    // 0x800BF828: ori         $a0, $a0, 0x700
    ctx->r4 = ctx->r4 | 0X700;
    // 0x800BF82C: jal         0x800C53D4
    // 0x800BF830: addiu       $a1, $zero, 0x15
    ctx->r5 = ADD32(0, 0X15);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_3;
    // 0x800BF830: addiu       $a1, $zero, 0x15
    ctx->r5 = ADD32(0, 0X15);
    after_3:
L_800BF834:
    // 0x800BF834: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_800BF838:
    // 0x800BF838: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800BF83C: jr          $ra
    // 0x800BF840: nop

    return;
    // 0x800BF840: nop

;}
RECOMP_FUNC void func_800BF844(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800BF844: lui         $t6, 0x8004
    ctx->r14 = S32(0X8004 << 16);
    // 0x800BF848: lw          $t6, 0x562C($t6)
    ctx->r14 = MEM_W(ctx->r14, 0X562C);
    // 0x800BF84C: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x800BF850: sw          $a0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r4;
    // 0x800BF854: andi        $t7, $t6, 0x7000
    ctx->r15 = ctx->r14 & 0X7000;
    // 0x800BF858: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800BF85C: sw          $a1, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r5;
    // 0x800BF860: srl         $t8, $t7, 12
    ctx->r24 = S32(U32(ctx->r15) >> 12);
    // 0x800BF864: lui         $a0, 0x600
    ctx->r4 = S32(0X600 << 16);
    // 0x800BF868: sw          $t8, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r24;
    // 0x800BF86C: ori         $a0, $a0, 0x700
    ctx->r4 = ctx->r4 | 0X700;
    // 0x800BF870: jal         0x800C53D4
    // 0x800BF874: addiu       $a1, $zero, -0x1
    ctx->r5 = ADD32(0, -0X1);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_0;
    // 0x800BF874: addiu       $a1, $zero, -0x1
    ctx->r5 = ADD32(0, -0X1);
    after_0:
    // 0x800BF878: lui         $a0, 0x600
    ctx->r4 = S32(0X600 << 16);
    // 0x800BF87C: ori         $a0, $a0, 0x701
    ctx->r4 = ctx->r4 | 0X701;
    // 0x800BF880: jal         0x800C53D4
    // 0x800BF884: lb          $a1, 0x23($sp)
    ctx->r5 = MEM_B(ctx->r29, 0X23);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_1;
    // 0x800BF884: lb          $a1, 0x23($sp)
    ctx->r5 = MEM_B(ctx->r29, 0X23);
    after_1:
    // 0x800BF888: lui         $a0, 0x600
    ctx->r4 = S32(0X600 << 16);
    // 0x800BF88C: ori         $a0, $a0, 0x702
    ctx->r4 = ctx->r4 | 0X702;
    // 0x800BF890: jal         0x800C53D4
    // 0x800BF894: lb          $a1, 0x27($sp)
    ctx->r5 = MEM_B(ctx->r29, 0X27);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_2;
    // 0x800BF894: lb          $a1, 0x27($sp)
    ctx->r5 = MEM_B(ctx->r29, 0X27);
    after_2:
    // 0x800BF898: lui         $a0, 0x600
    ctx->r4 = S32(0X600 << 16);
    // 0x800BF89C: ori         $a0, $a0, 0x703
    ctx->r4 = ctx->r4 | 0X703;
    // 0x800BF8A0: jal         0x800C53D4
    // 0x800BF8A4: lb          $a1, 0x1F($sp)
    ctx->r5 = MEM_B(ctx->r29, 0X1F);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_3;
    // 0x800BF8A4: lb          $a1, 0x1F($sp)
    ctx->r5 = MEM_B(ctx->r29, 0X1F);
    after_3:
    // 0x800BF8A8: lui         $a0, 0x600
    ctx->r4 = S32(0X600 << 16);
    // 0x800BF8AC: ori         $a0, $a0, 0x700
    ctx->r4 = ctx->r4 | 0X700;
    // 0x800BF8B0: jal         0x800C53D4
    // 0x800BF8B4: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_4;
    // 0x800BF8B4: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_4:
    // 0x800BF8B8: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800BF8BC: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x800BF8C0: jr          $ra
    // 0x800BF8C4: nop

    return;
    // 0x800BF8C4: nop

;}
RECOMP_FUNC void func_800BF8C8(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800BF8C8: lui         $v0, 0x8004
    ctx->r2 = S32(0X8004 << 16);
    // 0x800BF8CC: lw          $v0, 0x562C($v0)
    ctx->r2 = MEM_W(ctx->r2, 0X562C);
    // 0x800BF8D0: addiu       $sp, $sp, -0x28
    ctx->r29 = ADD32(ctx->r29, -0X28);
    // 0x800BF8D4: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800BF8D8: andi        $v1, $v0, 0xF
    ctx->r3 = ctx->r2 & 0XF;
    // 0x800BF8DC: bne         $v1, $zero, L_800BF954
    if (ctx->r3 != 0) {
        // 0x800BF8E0: sll         $t6, $v1, 2
        ctx->r14 = S32(ctx->r3 << 2);
            goto L_800BF954;
    }
    // 0x800BF8E0: sll         $t6, $v1, 2
    ctx->r14 = S32(ctx->r3 << 2);
    // 0x800BF8E4: andi        $t8, $v0, 0x7F0
    ctx->r24 = ctx->r2 & 0X7F0;
    // 0x800BF8E8: andi        $t0, $v0, 0x7000
    ctx->r8 = ctx->r2 & 0X7000;
    // 0x800BF8EC: addiu       $t7, $t6, 0x3C
    ctx->r15 = ADD32(ctx->r14, 0X3C);
    // 0x800BF8F0: srl         $t9, $t8, 4
    ctx->r25 = S32(U32(ctx->r24) >> 4);
    // 0x800BF8F4: srl         $t1, $t0, 12
    ctx->r9 = S32(U32(ctx->r8) >> 12);
    // 0x800BF8F8: lui         $a0, 0x600
    ctx->r4 = S32(0X600 << 16);
    // 0x800BF8FC: sw          $t7, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r15;
    // 0x800BF900: sw          $t9, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r25;
    // 0x800BF904: sw          $t1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r9;
    // 0x800BF908: ori         $a0, $a0, 0x700
    ctx->r4 = ctx->r4 | 0X700;
    // 0x800BF90C: jal         0x800C53D4
    // 0x800BF910: addiu       $a1, $zero, -0x1
    ctx->r5 = ADD32(0, -0X1);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_0;
    // 0x800BF910: addiu       $a1, $zero, -0x1
    ctx->r5 = ADD32(0, -0X1);
    after_0:
    // 0x800BF914: lui         $a0, 0x600
    ctx->r4 = S32(0X600 << 16);
    // 0x800BF918: ori         $a0, $a0, 0x701
    ctx->r4 = ctx->r4 | 0X701;
    // 0x800BF91C: jal         0x800C53D4
    // 0x800BF920: lb          $a1, 0x27($sp)
    ctx->r5 = MEM_B(ctx->r29, 0X27);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_1;
    // 0x800BF920: lb          $a1, 0x27($sp)
    ctx->r5 = MEM_B(ctx->r29, 0X27);
    after_1:
    // 0x800BF924: lui         $a0, 0x600
    ctx->r4 = S32(0X600 << 16);
    // 0x800BF928: ori         $a0, $a0, 0x702
    ctx->r4 = ctx->r4 | 0X702;
    // 0x800BF92C: jal         0x800C53D4
    // 0x800BF930: lb          $a1, 0x23($sp)
    ctx->r5 = MEM_B(ctx->r29, 0X23);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_2;
    // 0x800BF930: lb          $a1, 0x23($sp)
    ctx->r5 = MEM_B(ctx->r29, 0X23);
    after_2:
    // 0x800BF934: lui         $a0, 0x600
    ctx->r4 = S32(0X600 << 16);
    // 0x800BF938: ori         $a0, $a0, 0x703
    ctx->r4 = ctx->r4 | 0X703;
    // 0x800BF93C: jal         0x800C53D4
    // 0x800BF940: lb          $a1, 0x1F($sp)
    ctx->r5 = MEM_B(ctx->r29, 0X1F);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_3;
    // 0x800BF940: lb          $a1, 0x1F($sp)
    ctx->r5 = MEM_B(ctx->r29, 0X1F);
    after_3:
    // 0x800BF944: lui         $a0, 0x600
    ctx->r4 = S32(0X600 << 16);
    // 0x800BF948: ori         $a0, $a0, 0x700
    ctx->r4 = ctx->r4 | 0X700;
    // 0x800BF94C: jal         0x800C53D4
    // 0x800BF950: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_4;
    // 0x800BF950: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_4:
L_800BF954:
    // 0x800BF954: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800BF958: addiu       $sp, $sp, 0x28
    ctx->r29 = ADD32(ctx->r29, 0X28);
    // 0x800BF95C: jr          $ra
    // 0x800BF960: nop

    return;
    // 0x800BF960: nop

;}
RECOMP_FUNC void func_800BF964(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800BF964: addiu       $sp, $sp, -0x38
    ctx->r29 = ADD32(ctx->r29, -0X38);
    // 0x800BF968: lui         $t6, 0x8004
    ctx->r14 = S32(0X8004 << 16);
    // 0x800BF96C: lw          $t6, -0xB8($t6)
    ctx->r14 = MEM_W(ctx->r14, -0XB8);
    // 0x800BF970: sw          $ra, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r31;
    // 0x800BF974: sw          $s4, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r20;
    // 0x800BF978: srl         $t7, $t6, 31
    ctx->r15 = S32(U32(ctx->r14) >> 31);
    // 0x800BF97C: sw          $s3, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r19;
    // 0x800BF980: sw          $s2, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r18;
    // 0x800BF984: sw          $s1, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r17;
    // 0x800BF988: sw          $s0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r16;
    // 0x800BF98C: bne         $t7, $zero, L_800BF9A4
    if (ctx->r15 != 0) {
        // 0x800BF990: sdc1        $f20, 0x18($sp)
        CHECK_FR(ctx, 20);
    SD(ctx->f20.u64, 0X18, ctx->r29);
            goto L_800BF9A4;
    }
    // 0x800BF990: sdc1        $f20, 0x18($sp)
    CHECK_FR(ctx, 20);
    SD(ctx->f20.u64, 0X18, ctx->r29);
    // 0x800BF994: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x800BF998: addiu       $v0, $v0, 0x7CE0
    ctx->r2 = ADD32(ctx->r2, 0X7CE0);
    // 0x800BF99C: b           L_800BFA14
    // 0x800BF9A0: sw          $zero, 0x0($v0)
    MEM_W(0X0, ctx->r2) = 0;
        goto L_800BFA14;
    // 0x800BF9A0: sw          $zero, 0x0($v0)
    MEM_W(0X0, ctx->r2) = 0;
L_800BF9A4:
    // 0x800BF9A4: lui         $s1, 0x8004
    ctx->r17 = S32(0X8004 << 16);
    // 0x800BF9A8: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x800BF9AC: lui         $s2, 0x8004
    ctx->r18 = S32(0X8004 << 16);
    // 0x800BF9B0: addiu       $s2, $s2, 0x4688
    ctx->r18 = ADD32(ctx->r18, 0X4688);
    // 0x800BF9B4: lwc1        $f20, -0x3CA0($at)
    ctx->f20.u32l = MEM_W(ctx->r1, -0X3CA0);
    // 0x800BF9B8: addiu       $s1, $s1, -0x338
    ctx->r17 = ADD32(ctx->r17, -0X338);
    // 0x800BF9BC: or          $s0, $zero, $zero
    ctx->r16 = 0 | 0;
    // 0x800BF9C0: addiu       $s4, $zero, 0x10
    ctx->r20 = ADD32(0, 0X10);
    // 0x800BF9C4: lui         $s3, 0x402
    ctx->r19 = S32(0X402 << 16);
L_800BF9C8:
    // 0x800BF9C8: lw          $v0, 0x2B0($s1)
    ctx->r2 = MEM_W(ctx->r17, 0X2B0);
    // 0x800BF9CC: beql        $v0, $s2, L_800BF9F8
    if (ctx->r2 == ctx->r18) {
        // 0x800BF9D0: addiu       $s0, $s0, 0x1
        ctx->r16 = ADD32(ctx->r16, 0X1);
            goto L_800BF9F8;
    }
    goto skip_0;
    // 0x800BF9D0: addiu       $s0, $s0, 0x1
    ctx->r16 = ADD32(ctx->r16, 0X1);
    skip_0:
    // 0x800BF9D4: lwc1        $f4, 0x30($v0)
    ctx->f4.u32l = MEM_W(ctx->r2, 0X30);
    // 0x800BF9D8: andi        $t8, $s0, 0xFF
    ctx->r24 = ctx->r16 & 0XFF;
    // 0x800BF9DC: sll         $t9, $t8, 8
    ctx->r25 = S32(ctx->r24 << 8);
    // 0x800BF9E0: mul.s       $f6, $f4, $f20
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f6.fl = MUL_S(ctx->f4.fl, ctx->f20.fl);
    // 0x800BF9E4: or          $a0, $t9, $s3
    ctx->r4 = ctx->r25 | ctx->r19;
    // 0x800BF9E8: mfc1        $a1, $f6
    ctx->r5 = (int32_t)ctx->f6.u32l;
    // 0x800BF9EC: jal         0x800C538C
    // 0x800BF9F0: nop

    AudioThread_QueueCmdF32(rdram, ctx);
        goto after_0;
    // 0x800BF9F0: nop

    after_0:
    // 0x800BF9F4: addiu       $s0, $s0, 0x1
    ctx->r16 = ADD32(ctx->r16, 0X1);
L_800BF9F8:
    // 0x800BF9F8: bne         $s0, $s4, L_800BF9C8
    if (ctx->r16 != ctx->r20) {
        // 0x800BF9FC: addiu       $s1, $s1, 0x4
        ctx->r17 = ADD32(ctx->r17, 0X4);
            goto L_800BF9C8;
    }
    // 0x800BF9FC: addiu       $s1, $s1, 0x4
    ctx->r17 = ADD32(ctx->r17, 0X4);
    // 0x800BFA00: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x800BFA04: addiu       $v0, $v0, 0x7CE0
    ctx->r2 = ADD32(ctx->r2, 0X7CE0);
    // 0x800BFA08: lw          $t0, 0x0($v0)
    ctx->r8 = MEM_W(ctx->r2, 0X0);
    // 0x800BFA0C: addiu       $t1, $t0, -0x1
    ctx->r9 = ADD32(ctx->r8, -0X1);
    // 0x800BFA10: sw          $t1, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r9;
L_800BFA14:
    // 0x800BFA14: lw          $ra, 0x34($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X34);
    // 0x800BFA18: ldc1        $f20, 0x18($sp)
    CHECK_FR(ctx, 20);
    ctx->f20.u64 = LD(ctx->r29, 0X18);
    // 0x800BFA1C: lw          $s0, 0x20($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X20);
    // 0x800BFA20: lw          $s1, 0x24($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X24);
    // 0x800BFA24: lw          $s2, 0x28($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X28);
    // 0x800BFA28: lw          $s3, 0x2C($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X2C);
    // 0x800BFA2C: lw          $s4, 0x30($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X30);
    // 0x800BFA30: jr          $ra
    // 0x800BFA34: addiu       $sp, $sp, 0x38
    ctx->r29 = ADD32(ctx->r29, 0X38);
    return;
    // 0x800BFA34: addiu       $sp, $sp, 0x38
    ctx->r29 = ADD32(ctx->r29, 0X38);
    // 0x800BFA38: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800BFA3C: sw          $a1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r5;
    // 0x800BFA40: andi        $t6, $a0, 0xFF
    ctx->r14 = ctx->r4 & 0XFF;
    // 0x800BFA44: andi        $t0, $a1, 0xFF
    ctx->r8 = ctx->r5 & 0XFF;
    // 0x800BFA48: sll         $a1, $a2, 24
    ctx->r5 = S32(ctx->r6 << 24);
    // 0x800BFA4C: sll         $t7, $t6, 16
    ctx->r15 = S32(ctx->r14 << 16);
    // 0x800BFA50: lui         $at, 0x800
    ctx->r1 = S32(0X800 << 16);
    // 0x800BFA54: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800BFA58: or          $t8, $t7, $at
    ctx->r24 = ctx->r15 | ctx->r1;
    // 0x800BFA5C: sra         $t2, $a1, 24
    ctx->r10 = S32(SIGNED(ctx->r5) >> 24);
    // 0x800BFA60: sll         $t1, $t0, 8
    ctx->r9 = S32(ctx->r8 << 8);
    // 0x800BFA64: or          $a0, $t8, $t1
    ctx->r4 = ctx->r24 | ctx->r9;
    // 0x800BFA68: jal         0x800C53D4
    // 0x800BFA6C: or          $a1, $t2, $zero
    ctx->r5 = ctx->r10 | 0;
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_1;
    // 0x800BFA6C: or          $a1, $t2, $zero
    ctx->r5 = ctx->r10 | 0;
    after_1:
    // 0x800BFA70: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800BFA74: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800BFA78: jr          $ra
    // 0x800BFA7C: nop

    return;
    // 0x800BFA7C: nop

;}
